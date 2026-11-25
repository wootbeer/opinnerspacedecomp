/* ISPACE.DLL's joystick: ordinal 41 (9:3e8a) reads joystick A on the
 * game port (9:3ffe times the port's one-shots in a loop; the port
 * takes the loop counts from the game controller, pad.c), scales the
 * counts and, once calibrated, maps the INI's corners (JMinX, JMinY,
 * JRangeX, JRangeY) to 0-0xffff.  The Joystick dialog (template 975,
 * 9:40da), opened from Game Settings, turns it on (INI JoyStick),
 * calibrates it, shows where the stick points and which buttons are
 * held, and gives each button an action (INI JBtn0-3), which the game
 * carries out (11:7588). */
#include <SDL3/SDL_stdinc.h>

#include "user.h"
#include "ispace.h"

#define INI "INSPACE.INI"
#define APP "Inner Space"
#define NO_JOYSTICK 0xa7        /* ordinal 41: nothing answers */
#define BAD_JOYSTICK 0xa5       /* ordinal 41: n is not 0 or 1 */
/* Template 975. */
#define ID_CANCEL 0x14d
#define ID_HELP 0x3d0
#define ID_CALIBRATE 0x3d1
#define ID_ENABLED 0x3d4
#define ID_STATUS 0x3d5
#define ID_FOUR 0x3d9           /* "4 Buttons": buttons 3 and 4 can be set */
#define ID_BUTTON 0x44c         /* Button 1-4, shown pressed while held */
#define ID_ACTION 0x4b0         /* the four buttons' actions */
#define ACTIONS 7               /* strings 0x974-0x97a: Fire Gun ... Cloak/Shield */
#define STATUS_TEXT 0x960       /* + state: strings 0x95f-0x964 */

enum { ABSENT = -1, UNCALIBRATED, UPPER_LEFT, LOWER_RIGHT, CALIBRATED, DISABLED };

static struct {
    HWND dlg;                   /* DS:2296 */
    int16_t enabled;            /* DS:228e INI JoyStick */
    int16_t four;               /* DS:2290 INI 4Btns */
    int16_t state;              /* DS:2294: ABSENT ... DISABLED */
    int16_t min[2];             /* DS:19e8 JMinX, JMinY: the upper left corner */
    int16_t range[2];           /* DS:19ec JRangeX, JRangeY: to the lower right one */
    int16_t action[4];          /* DS:19f0 JBtn0-3 */
    int16_t held[4];            /* DS:19f8: the buttons at the last drawing */
    int16_t reach[2];           /* DS:1a14: the most the upper left corner had */
    POINT cross;                /* DS:1a10: where the cross was drawn */
    char reading[8];            /* DS:19e4, 9:35ba's block: ordinal 41's for the dialog */
} joy;

static uint16_t word_at(const char *p)
{
    return (uint16_t)((uint8_t)p[0] | (uint8_t)p[1] << 8);
}

static void put_word(char *p, uint16_t v)
{
    p[0] = (char)(v & 0xff);
    p[1] = (char)(v >> 8);
}

/* 9:3e8a's mapping of a count to 0-0xffff between the corners.  An axis
 * never calibrated (range 0: the DLL divides by zero) reads as centred. */
static uint16_t calibrated(uint16_t v, int axis)
{
    int16_t scale;              /* DS:1a0c */
    int32_t p;

    if (!joy.range[axis])
        return 0x8000;
    scale = (int16_t)(0xffffL / joy.range[axis]);
    v = v < (uint16_t)joy.min[axis] ? 0 : (uint16_t)(v - joy.min[axis]);
    p = (int32_t)(uint32_t)((int64_t)v * scale);
    return p > 0xffff ? 0xffff : (uint16_t)p;
}

/* Ordinal 41 (9:3e8a).  n is not used further: joystick A is read,
 * with buttons 3 and 4 when "4 Buttons" is set (pad.c). */
int16_t ispace_joystick(int16_t n, char *out)
{
    uint16_t count[2], buttons, v;
    int i;

    if ((uint16_t)n > 1)
        return BAD_JOYSTICK;
    if (!pad_game_port(count, &buttons, joy.four ? 4 : 2)) {
        MessageBeep(0);
        return NO_JOYSTICK;
    }
    for (i = 0; i < 4; i++)
        out[4 + i] = (char)(buttons >> i & 1);
    for (i = 0; i < 2; i++) {
        v = (uint16_t)((uint32_t)count[i] * 771 / 1000 + 14);
        put_word(out + 2 * i, joy.state == CALIBRATED ? calibrated(v, i) : v);
    }
    return 0;
}

/* 9:22ca's part: the INI's joystick settings, taken as calibrated. */
void ispace_joy_read_settings(void)
{
    static const char *const keys[2][2] = {{"JMinX", "JMinY"}, {"JRangeX", "JRangeY"}};
    int i;

    joy.state = CALIBRATED;
    joy.enabled = GetPrivateProfileInt(APP, "JoyStick", 0, INI);
    joy.four = GetPrivateProfileInt(APP, "4Btns", 0, INI);
    for (i = 0; i < 2; i++) {
        joy.min[i] = GetPrivateProfileInt(APP, keys[0][i], 0, INI);
        joy.range[i] = GetPrivateProfileInt(APP, keys[1][i], 0, INI);
    }
}

HWND ispace_joy_dialog(void)
{
    return joy.dlg;
}

static void write_int(LPCSTR key, int16_t v)
{
    char num[10];

    SDL_snprintf(num, sizeof num, "%d", v);
    WritePrivateProfileString(APP, key, num, INI);
}

static void enable(int16_t id, int on)
{
    EnableWindow(GetDlgItem(joy.dlg, id), on);
}

/* 9:4f00: the text for the state. */
static void show_status(void)
{
    char text[0xbe];

    LoadString(ispace_lang_module(), (UINT)(STATUS_TEXT + joy.state), text, sizeof text);
    SetWindowText(GetDlgItem(joy.dlg, ID_STATUS), text);
}

/* 9:4e02: the controls a turned-on joystick has; buttons 3 and 4 also
 * need "4 Buttons". */
static void enable_controls(void)
{
    static const int16_t two[] = {ID_CALIBRATE, ID_BUTTON, ID_BUTTON + 1, ID_FOUR, ID_ACTION, ID_ACTION + 1};
    static const int16_t four[] = {ID_BUTTON + 2, ID_BUTTON + 3, ID_ACTION + 2, ID_ACTION + 3};
    size_t i;

    for (i = 0; i < SDL_arraysize(two); i++)
        enable(two[i], joy.enabled);
    for (i = 0; i < SDL_arraysize(four); i++)
        enable(four[i], joy.four & joy.enabled);
}

/* 9:4f46: a button newly held plays its action's sound. */
static void action_sound(int16_t action)
{
    static const int16_t sounds[ACTIONS] = {3, 0x1c, 0x14, 0x29, 0x33, 0x39, 0x27};

    if ((uint16_t)action >= ACTIONS)
        return;
    ispace_sound_effect(0x6e);
    ispace_sound_effect(sounds[action]);
}

/* 9:48f8's text: a corner's two values ("123,456") at (x, y). */
static void corner_text(HDC dc, int16_t x, int16_t y, UINT align, int16_t a, int16_t b)
{
    char text[16];

    SDL_snprintf(text, sizeof text, "%d,%d", a, b);
    SetTextAlign(dc, align);
    SetTextColor(dc, RGB(255, 255, 255));
    SetBkColor(dc, RGB(0, 0, 0));
    PatBlt(dc, (int16_t)(align == TA_RIGHT ? x - 100 : x), y, 100, 16, BLACKNESS);
    TextOut(dc, x, y, text, (int16_t)SDL_strlen(text));
}

/* The lower right corner while calibrating: the range from the upper
 * left one, at least 1 (unsigned). */
static void take_range(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        uint16_t d = (uint16_t)(word_at(joy.reading + 2 * i) - joy.min[i]);
        joy.range[i] = (int16_t)(d < 1 ? 1 : d);
    }
}

/* 9:48f8: the test area (cleared first with clear 1).  Calibrating, the
 * corners read so far; calibrated, the buttons held and a cross where the
 * stick points. */
static void draw(int clear)
{
    HWND area = ispace_preview_window();
    int16_t w, h, s, x, y, cx, cy;
    RECT rc;
    HRGN rgn;
    HDC dc;
    int i;

    if (!area)
        return;
    GetClientRect(area, &rc);
    w = (int16_t)(rc.right - 8);
    h = (int16_t)(rc.bottom - 8);
    s = (int16_t)(0xffffL / (w + 4));
    x = (int16_t)((int32_t)word_at(joy.reading) / s);
    y = (int16_t)((int32_t)word_at(joy.reading + 2) / s);
    x = (int16_t)SDL_min(SDL_max(x, 5), 2 * w + 1) - w / 2;
    y = (int16_t)SDL_min(SDL_max(y, 5), 2 * h + 1) - h / 2;
    rgn = CreateRectRgn(4, 4, (int16_t)(w + 4), (int16_t)(h + 4));
    dc = GetDC(area);
    SelectClipRgn(dc, rgn);
    if (clear)
        PatBlt(dc, 4, 4, w, h, BLACKNESS);
    if (joy.enabled && joy.state == CALIBRATED) {
        for (i = 0; i < 4; i++) {
            SendDlgItemMessage(joy.dlg, (int16_t)(ID_BUTTON + i), BM_SETSTATE, (WPARAM)(int16_t)joy.reading[4 + i], 0);
            if (joy.reading[4 + i] && !joy.held[i])
                action_sound(joy.action[i]);
            joy.held[i] = joy.reading[4 + i];
        }
        PatBlt(dc, joy.cross.x, joy.cross.y, 21, 21, BLACKNESS);
        cx = (int16_t)(w / 2 + x);
        cy = (int16_t)(h / 2 + y);
        joy.cross.x = (int16_t)(cx - 10);
        joy.cross.y = (int16_t)(cy - 10);
        PatBlt(dc, (int16_t)(cx - 1), (int16_t)(cy - 10), 3, 21, WHITENESS);
        PatBlt(dc, joy.cross.x, (int16_t)(cy - 1), 21, 3, WHITENESS);
    } else if (joy.enabled && (joy.state == UPPER_LEFT || joy.state == LOWER_RIGHT)) {
        if (joy.state == UPPER_LEFT)
            for (i = 0; i < 2; i++) {
                joy.min[i] = (int16_t)word_at(joy.reading + 2 * i);
                joy.reach[i] = SDL_max(joy.reach[i], joy.min[i]);
            }
        else
            take_range();
        corner_text(dc, 5, 5, TA_LEFT, joy.min[0], joy.min[1]);
        if (joy.state == LOWER_RIGHT)
            corner_text(dc, (int16_t)(w - 1), (int16_t)(h - 0x11), TA_RIGHT, (int16_t)(joy.range[0] + joy.min[0]),
                        (int16_t)(joy.range[1] + joy.min[1]));
    }
    ReleaseDC(area, dc);
    DeleteObject(rgn);
}

void ispace_joy_paint(void)
{
    draw(1);
}

/* Whether nothing answers: then the joystick is gone, and turned off. */
static int read_reading(void)
{
    if (ispace_joystick(0, joy.reading) != NO_JOYSTICK)
        return 1;
    joy.state = ABSENT;
    return 0;
}

/* 9:4d02 (WM_TIMER of the NotifyClass window, every 50 ms while the
 * dialog runs): a turned-on joystick read and drawn; a button takes the
 * calibration to its next corner, the lower right one only once the
 * stick is at least as far as the upper left corner went. */
void ispace_joy_timer(void)
{
    int i, any = 0;

    if (!joy.enabled)
        return;
    if (!read_reading()) {
        joy.enabled = 0;
        CheckDlgButton(joy.dlg, ID_ENABLED, 0);
        return;
    }
    draw(0);
    for (i = 0; i < 4; i++)
        any |= joy.reading[4 + i];
    if (!any || (joy.state != UPPER_LEFT && joy.state != LOWER_RIGHT))
        return;
    if (joy.state == LOWER_RIGHT && ((int16_t)(joy.range[0] + joy.min[0]) < joy.reach[0] ||
                                     (int16_t)(joy.range[1] + joy.min[1]) < joy.reach[1]))
        return;
    joy.state++;
    show_status();
    draw(1);
    if (joy.state == CALIBRATED) {
        ispace_sound_effect(0x2a);
        enable(IDOK, 1);
        enable(ID_CALIBRATE, 1);
    } else {
        ispace_sound_effect(0x15);
    }
}

/* The state for a joystick turned on: calibrated when the INI has its
 * corner (x only). */
static int16_t on_state(void)
{
    return joy.min[0] && joy.range[0] ? CALIBRATED : UNCALIBRATED;
}

/* 9:4298: WM_INITDIALOG. */
static void joy_init(HWND dlg)
{
    static const int16_t bold[] = {IDOK, ID_CANCEL, ID_CALIBRATE, ID_BUTTON, ID_BUTTON + 1, ID_BUTTON + 2,
                                   ID_BUTTON + 3, ID_HELP};
    char text[0x50];
    RECT win, r;
    POINT org = {0, 0};
    int16_t x, y, item_h;
    HFONT old;
    HDC dc;
    size_t k;
    int i, j;

    joy.dlg = dlg;
    GetWindowRect(dlg, &win);
    x = (int16_t)(GetSystemMetrics(SM_CXSCREEN) / 2 + (win.left - win.right) / 2);
    y = (int16_t)(GetSystemMetrics(SM_CYSCREEN) / 2 + (win.top - win.bottom) / 2);
    dc = GetDC(dlg);
    old = SelectObject(dc, ispace_dialog_font(0));
    item_h = (int16_t)HIWORD(GetTextExtent(dc, "Test", 4));
    SelectObject(dc, old);
    ReleaseDC(dlg, dc);
    ClientToScreen(dlg, &org);
    SendDlgItemMessage(dlg, ID_ENABLED, WM_SETFONT, ispace_dialog_font(0), 1);
    SendDlgItemMessage(dlg, ID_STATUS, WM_SETFONT, ispace_dialog_font(0), 1);
    for (k = 0; k < SDL_arraysize(bold); k++)
        SendDlgItemMessage(dlg, bold[k], WM_SETFONT, ispace_dialog_font(1), 1);
    SendDlgItemMessage(dlg, ID_FOUR, WM_SETFONT, ispace_dialog_font(0), 1);
    for (i = 0; i < 4; i++) {
        HWND combo = GetDlgItem(dlg, (int16_t)(ID_ACTION + i));
        char key[8];
        GetWindowRect(combo, &r);
        MoveWindow(combo, (int16_t)(r.left - org.x), (int16_t)(r.top - org.y), (int16_t)(r.right - r.left),
                   (int16_t)(item_h * 7 + 30), 1);
        SendMessage(combo, WM_SETFONT, ispace_dialog_font(0), 1);
        for (j = 0; j < ACTIONS; j++) {
            LoadString(ispace_lang_module(), (UINT)(0x974 + j), text, sizeof text);
            combo_add_string(combo, text);
        }
        SDL_snprintf(key, sizeof key, "JBtn%d", i);
        joy.action[i] = GetPrivateProfileInt(APP, key, (int16_t)i, INI);
        SendMessage(combo, CB_SETCURSEL, (WPARAM)joy.action[i], 0);
    }
    joy.four = GetPrivateProfileInt(APP, "4Btns", 0, INI);
    joy.enabled = GetPrivateProfileInt(APP, "JoyStick", 0, INI);
    joy.state = DISABLED;
    if (!read_reading())
        joy.enabled = 0;
    CheckDlgButton(dlg, ID_FOUR, (UINT)joy.four);
    CheckDlgButton(dlg, ID_ENABLED, (UINT)joy.enabled);
    if (joy.enabled)
        joy.state = on_state();
    enable_controls();
    show_status();
    ispace_preview_open(dlg, 40, 88, 160, 160);
    SetTimer(ispace_sound_window(), 1, 50, NULL);
    SetFocus(GetDlgItem(dlg, ID_CANCEL));
    MoveWindow(dlg, x, y, (int16_t)(win.right - win.left), (int16_t)(win.bottom - win.top), 1);
}

/* 9:4712: OK (ok 1) puts the settings into the INI: the joystick's
 * corners as they are now, also after Cancel (and for the game until
 * the INI is read again). */
static void joy_end(HWND dlg, int ok)
{
    char key[8];
    int i;

    if (ok) {
        write_int("JoyStick", joy.enabled = (int16_t)IsDlgButtonChecked(dlg, ID_ENABLED));
        write_int("4Btns", joy.four = (int16_t)IsDlgButtonChecked(dlg, ID_FOUR));
        write_int("JMinX", joy.min[0]);
        write_int("JMinY", joy.min[1]);
        write_int("JRangeX", joy.range[0]);
        write_int("JRangeY", joy.range[1]);
        for (i = 0; i < 4; i++) {
            joy.action[i] = (int16_t)SendDlgItemMessage(dlg, (int16_t)(ID_ACTION + i), CB_GETCURSEL, 0, 0);
            SDL_snprintf(key, sizeof key, "JBtn%d", i);
            write_int(key, joy.action[i]);
        }
    }
    ispace_preview_close();
    KillTimer(ispace_sound_window(), 1);
    joy.dlg = 0;
    EndDialog(dlg, (int16_t)ok);
}

/* 9:4213: Calibrate: the upper left corner first. */
static void calibrate(void)
{
    joy.reach[0] = joy.reach[1] = 0;
    put_word(joy.reading + 2, 0);
    put_word(joy.reading, 0);
    joy.state = UPPER_LEFT;
    show_status();
    enable(ID_CALIBRATE, 0);
    enable(IDOK, 0);
    draw(1);
}

/* 9:4168: "Joystick Enabled" clicked; with nothing answering it is
 * unchecked again. */
static void enabled_clicked(HWND dlg)
{
    if (!read_reading()) {
        if (joy.enabled) {
            joy.enabled = 0;
            CheckDlgButton(dlg, ID_ENABLED, 0);
        }
    } else {
        joy.enabled = (int16_t)IsDlgButtonChecked(dlg, ID_ENABLED);
        enable_controls();
        joy.state = joy.enabled ? on_state() : DISABLED;
    }
    show_status();
}

/* 9:40da: the Joystick dialog (template 975). */
BOOL ispace_joy_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    char path[0x80];

    (void)lp;
    if (msg == WM_INITDIALOG) {
        joy_init(h);
        return 0;
    }
    if (msg != WM_COMMAND)
        return 0;
    switch (wp) {
    case IDOK:
    case ID_CANCEL:
        joy_end(h, wp == IDOK);
        return 1;
    case ID_HELP:
        ispace_sound_path(path, sizeof path);
        SDL_strlcat(path, "INSPACE.HLP", sizeof path);
        WinHelp(0, path, HELP_CONTEXT, 0x23);
        return 0;
    case ID_CALIBRATE:
        calibrate();
        return 0;
    case ID_ENABLED:
        enabled_clicked(h);
        return 0;
    case ID_FOUR:
        joy.four = (int16_t)IsDlgButtonChecked(h, ID_FOUR);
        enable_controls();
        return 0;
    }
    if (wp >= ID_ACTION && wp < ID_ACTION + 4)
        joy.action[wp - ID_ACTION] = (int16_t)SendDlgItemMessage(h, (int16_t)wp, CB_GETCURSEL, 0, 0);
    return 0;
}
