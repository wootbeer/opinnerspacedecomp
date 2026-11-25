/* ISPACE.DLL's Game Settings: ordinal 10 mode 0 (9:1546) runs template
 * 100 of the language DLL ("Inner Space Options/Setup") with its dialog
 * procedure, ordinal 11 (9:15cc); its Display.. and Audio.. buttons run
 * templates 666 and 999 with ordinals 37 (9:2bf8) and 38 (9:2f30).  The
 * choices go into INSPACE.INI, which the game reads again when the
 * dialog ends (6:0b3e: the menu bar, the border, the play speed ...);
 * the sound settings change the DLL's sound at once. */
#include <SDL3/SDL_stdinc.h>

#include "user.h"
#include "ispace.h"

#define INI "INSPACE.INI"
#define APP "Inner Space"
#define ID_HELP 0x6a
/* Template 100. */
#define ID_SPEED 0x6b           /* play speed bar, 0-1000 */
#define ID_NORMAL_SPEED 0x6e
#define ID_VOLUME 0x6f          /* master volume bar, 0-100 */
#define ID_ZOOM 0x72
#define ID_SYSTEM 0x76
#define ID_QUICK 0x77
#define ID_VERSION 0x7a
#define ID_NAME 0x7b
#define ID_SPEED_TEXT 0x7c
#define ID_DETAIL 0x7e
#define ID_ENHANCE 0x82
#define ID_DISPLAY 0x84
#define ID_DATE 0x88
#define ID_DIFFICULTY 0x89
#define ID_AUDIO 0x8b
#define ID_LANGUAGE 0x8e
#define ID_FX_NAME 0x90
#define ID_VOICE_NAME 0x92
#define ID_JOYSTICK 0x93
#define ID_BRAKING 0x94
#define ID_ICON 0x24f
/* Template 666. */
#define ID_BRIGHT 0x83
#define ID_MENU 0x85
#define ID_BORDER 0x86
#define ID_SKIP 0x29b
#define ID_SHIP_ANIM 0x29d
#define ID_SAVE_PROMPT 0x29e
/* Template 999. */
#define ID_MUSIC 0x65
#define ID_FX 0x66
#define ID_VOICE 0x67
#define ID_CHANNELS 0x80
#define ID_BALANCE 0x3e9
#define ID_KEEP 0x3eb
#define ID_SWAP 0x3ec
#define ID_STEREO 0x3f0

#define SB_LINEUP 0
#define SB_LINEDOWN 1
#define SB_PAGEUP 2
#define SB_PAGEDOWN 3
#define SB_THUMBPOSITION 4
#define SB_THUMBTRACK 5
#define SB_TOP 6
#define SB_BOTTOM 7
#define SB_ENDSCROLL 8
#define FULL_OUT 1200           /* FrameRateSet: no frame rate */
#define TEST_SOUND 0x23         /* played when the volume bar is let go */
#define WAVEMIX_CHANNELS 8      /* offered with WAVEMIX.DLL, which the port always has */

static struct {
    HWND dlg;                   /* DS:069c: the dialog while it runs */
    int16_t speed;              /* DS:0cfe: the play speed bar's position */
    int16_t speed_shown;        /* DS:0d00 */
    int16_t volume_shown;       /* DS:0d02 */
    int16_t balance_shown;      /* DS:0d04 */
    int16_t music_was_on;       /* DS:2220 */
} opt;

static void write_int(LPCSTR key, int16_t v)
{
    char num[10];

    SDL_snprintf(num, sizeof num, "%d", v);
    WritePrivateProfileString(APP, key, num, INI);
}

/* 9:379e: language strings first.. first + n - 1 into a combo box. */
static void add_strings(HWND dlg, int16_t id, UINT first, int n)
{
    char text[0x96];
    int k;

    for (k = 0; k < n; k++) {
        LoadString(ispace_lang_module(), first + (UINT)k, text, sizeof text);
        combo_add_string(GetDlgItem(dlg, id), text);
    }
}

static int16_t selection(HWND dlg, int16_t id)
{
    return (int16_t)SendDlgItemMessage(dlg, id, CB_GETCURSEL, 0, 0);
}

static void select_item(HWND dlg, int16_t id, int16_t i)
{
    SendDlgItemMessage(dlg, id, CB_SETCURSEL, (WPARAM)i, 0);
}

static void disable(HWND dlg, int16_t id)
{
    EnableWindow(GetDlgItem(dlg, id), 0);
}

/* The dialog centred on the screen. */
static void centre(HWND dlg)
{
    RECT r;

    GetWindowRect(dlg, &r);
    MoveWindow(dlg, (int16_t)(GetSystemMetrics(SM_CXSCREEN) / 2 + (r.left - r.right) / 2),
               (int16_t)(GetSystemMetrics(SM_CYSCREEN) / 2 + (r.top - r.bottom) / 2),
               (int16_t)(r.right - r.left), (int16_t)(r.bottom - r.top), 1);
}

/* A bar's position after scroll code code (pos: the thumb's), by step
 * a line or a page, top and bottom for SB_TOP and SB_BOTTOM; codes
 * without a meaning leave it. */
static int16_t scrolled(int16_t v, int code, int16_t pos, int16_t step, int16_t top, int16_t bottom)
{
    switch (code) {
    case SB_LINEUP:
    case SB_PAGEUP: return (int16_t)(v - step);
    case SB_LINEDOWN:
    case SB_PAGEDOWN: return (int16_t)(v + step);
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK: return pos;
    case SB_TOP: return top;
    case SB_BOTTOM: return bottom;
    }
    return v;
}

/* 9:328e: topic of <SndPath><Language>_HELP.HLP (0: its contents). */
void ispace_help(int32_t topic)
{
    char path[0x80], lang[5];

    ispace_sound_path(path, sizeof path);
    GetPrivateProfileString(APP, "Language", "", lang, sizeof lang, INI);
    SDL_strlcat(path, lang, sizeof path);
    SDL_strlcat(path, "_HELP.HLP", sizeof path);
    WinHelp(0, path, topic ? HELP_CONTEXT : HELP_INDEX, (DWORD)topic);
}

/* 9:2242: the play speed bar's position as a frame rate: 4-36 over
 * 0-500, 36-106 over 500-1000, FULL_OUT at 1000 and past 104. */
static int16_t speed_rate(int16_t pos)
{
    int16_t r;

    if (pos == 1000)
        return FULL_OUT;
    r = pos <= 500 ? (int16_t)(((int32_t)pos << 5) / 500 + 4) : (int16_t)((int32_t)(pos - 500) * 70 / 500 + 36);
    return r > 104 ? FULL_OUT : r;
}

/* The bar's position for frame rate r (9:15cc). */
static int16_t speed_pos(int16_t r)
{
    if (r == FULL_OUT)
        return 1000;
    if ((uint16_t)r < 36)
        return (int16_t)((int32_t)(r - 4) * 500 / 32);
    return (int16_t)((int32_t)(r - 36) * 500 / 70 + 500);
}

/* 9:1ea8: the play speed bar at pos and its text ("Play Speed  36
 * frames/sec"). */
static void show_speed(int16_t pos)
{
    char rate[0x3c], text[0x3c];
    int16_t r;

    SetScrollPos(GetDlgItem(opt.dlg, ID_SPEED), SB_CTL, pos, 1);
    r = speed_rate(pos);
    if (r == FULL_OUT)
        SDL_strlcpy(rate, "Full Out", sizeof rate);
    else
        SDL_snprintf(rate, sizeof rate, "%d frames/sec", r);
    SDL_snprintf(text, sizeof text, "Play Speed  %s", rate);
    SetWindowText(GetDlgItem(opt.dlg, ID_SPEED_TEXT), text);
}

/* 9:1f38: "V" and the program's version strings 0xa7 and 0xe9 put
 * into "V0.00.00" (V9.99.99 for "999" and "99"). */
static void version(HINSTANCE inst, char *out)
{
    char a[10] = "", b[10] = "";

    LoadString(inst, 0xa7, a, sizeof a);
    LoadString(inst, 0xe9, b, sizeof b);
    SDL_strlcpy(out, "V0.00.00", 9);
    out[1] = a[0];
    out[3] = a[1];
    out[4] = a[2];
    out[6] = b[0];
    out[7] = b[1];
    out[8] = 0;
}

/* What sound library n holds: "NONE" (string 0x47c of the language
 * DLL) when it is not loaded, "Compressed" (0x90a) when it has a string
 * 0x90a, else the template's "Normal". */
static void library_name(HWND dlg, int16_t id, int n)
{
    HINSTANCE lib = ispace_sound_library(n);
    char text[0x14];
    int16_t len;

    if (!lib)
        len = LoadString(ispace_lang_module(), 0x47c, text, sizeof text);
    else if ((len = LoadString(lib, 0x90a, text, sizeof text)) != 0)
        len = LoadString(ispace_lang_module(), 0x90a, text, sizeof text);
    if (len)
        SetWindowText(GetDlgItem(dlg, id), text);
}

/* 9:15cc's WM_INITDIALOG. */
static void options_init(HWND dlg)
{
    static const int16_t locked_ids[] = {0x7f, 0x7d, 0x73, ID_DETAIL, ID_QUICK, ID_ZOOM, ID_ENHANCE, ID_DISPLAY,
                                         ID_DIFFICULTY, 0x8a};
    IspaceSettings *set = ispace_settings();
    HINSTANCE inst = GetWindowWord(GetParent(dlg), GWW_HINSTANCE);
    char text[0x50];
    size_t k;
    int16_t best = set->device_best;

    opt.dlg = dlg;
    ispace_dialog_fonts(1);
    SendDlgItemMessage(dlg, ID_ICON, STM_SETICON, LoadIcon(inst, "GAME"), 0);
    ispace_dialog_set_fonts(dlg);
    opt.music_was_on = ispace_music_on();
    add_strings(dlg, ID_DETAIL, 0x8ad, 4);
    select_item(dlg, ID_DETAIL, (int16_t)(3 - set->detail));
    CheckDlgButton(dlg, ID_ENHANCE, (UINT)set->enhance);
    CheckDlgButton(dlg, ID_BRAKING, (UINT)GetPrivateProfileInt(APP, "Braking", 0, INI));
    add_strings(dlg, ID_QUICK, 0x8b1, 3);
    select_item(dlg, ID_QUICK, set->quick);
    add_strings(dlg, ID_DIFFICULTY, 0x40b, 5);
    select_item(dlg, ID_DIFFICULTY, GetPrivateProfileInt(APP, "Complex", 2, INI));
    add_strings(dlg, ID_ZOOM, 0x8b6, 3);
    select_item(dlg, ID_ZOOM, (int16_t)(2 - GetPrivateProfileInt(APP, "Size", 1, INI)));
    if (ispace_dialog_word6() == 1)
        for (k = 0; k < sizeof locked_ids / sizeof locked_ids[0]; k++)
            disable(dlg, locked_ids[k]);
    add_strings(dlg, ID_SYSTEM, 0x8b9, 1 + SDL_clamp(best, 0, 3));
    if (best < 2)
        disable(dlg, ID_VOLUME);
    if (best < 1) {
        disable(dlg, ID_SYSTEM);
        disable(dlg, ID_AUDIO);
    }
    select_item(dlg, ID_SYSTEM, set->system);
    opt.speed = speed_pos(GetPrivateProfileInt(APP, "FrameRateSet", 36, INI));
    if (opt.speed < 0)
        opt.speed = 0;
    opt.speed_shown = opt.speed;
    SetScrollRange(GetDlgItem(dlg, ID_SPEED), SB_CTL, 0, 1000, 0);
    show_speed(opt.speed);
    SetScrollRange(GetDlgItem(dlg, ID_VOLUME), SB_CTL, 0, 100, 0);
    SetScrollPos(GetDlgItem(dlg, ID_VOLUME), SB_CTL, set->volume, 1);
    centre(dlg);
    SetFocus(GetDlgItem(dlg, ID_SPEED));
    library_name(dlg, ID_FX_NAME, 0);
    library_name(dlg, ID_VOICE_NAME, 1);
    LoadString(ispace_lang_module(), 0x905, text, 10);
    SetWindowText(GetDlgItem(dlg, ID_LANGUAGE), text);
    version(inst, text);
    SetWindowText(GetDlgItem(dlg, ID_VERSION), text);
    LoadString(inst, 0x708, text, 0x14);
    SetWindowText(GetDlgItem(dlg, ID_NAME), text);
    LoadString(inst, 0x25f, text, 0x14);
    SetWindowText(GetDlgItem(dlg, ID_DATE), text);
}

/* 9:1fae: OK (ok 1) puts the choices into the INI; a new sound system
 * reads the sound settings again.  Music turned on (in Audio Options)
 * or sound turned on starts the piece asked for last. */
static void options_end(HWND dlg, int ok, int16_t pos)
{
    IspaceSettings *set = ispace_settings();
    int16_t size, difficulty, old_system = set->system, braking;

    if (ok) {
        size = (int16_t)(2 - selection(dlg, ID_ZOOM));
        set->detail = (int16_t)(3 - selection(dlg, ID_DETAIL));
        set->quick = selection(dlg, ID_QUICK);
        difficulty = selection(dlg, ID_DIFFICULTY);
        set->system = selection(dlg, ID_SYSTEM);
        set->enhance = (int16_t)IsDlgButtonChecked(dlg, ID_ENHANCE);
        braking = (int16_t)IsDlgButtonChecked(dlg, ID_BRAKING);
        write_int("Complex", difficulty);
        write_int("Braking", braking);
        write_int("Enhance", set->enhance);
        write_int("SoundVolume", set->volume);
        write_int("SoundSystem", set->system);
        write_int("Quick", set->quick);
        write_int("Detail", set->detail);
        write_int("Size", size);
        write_int("SetSize", size);
        write_int("FrameRateSet", speed_rate(pos));
        if (set->system != old_system)
            ispace_sound_read_settings();
    }
    if ((ispace_music_on() && !opt.music_was_on) || (set->system && !old_system))
        ispace_music(ispace_music_piece(), 1);
    EndDialog(dlg, (int16_t)ok);
}

static void options_scroll(HWND dlg, int code, int16_t pos, HWND bar)
{
    IspaceSettings *set = ispace_settings();

    switch (GetDlgCtrlID(bar)) {
    case ID_SPEED:
        opt.speed = (int16_t)SDL_clamp(scrolled(opt.speed, code, pos, 50, 1000, 0), 0, 1000);
        if (opt.speed != opt.speed_shown) {
            show_speed(opt.speed);
            opt.speed_shown = opt.speed;
        }
        break;
    case ID_VOLUME:
        if (code == SB_ENDSCROLL)
            ispace_sound_effect(TEST_SOUND);
        set->volume = (int16_t)SDL_clamp(scrolled(set->volume, code, pos, 1, set->volume, set->volume), 0, 100);
        ispace_sound_mix_volumes();
        if (set->volume != opt.volume_shown) {
            SetScrollPos(GetDlgItem(dlg, ID_VOLUME), SB_CTL, set->volume, 1);
            opt.volume_shown = set->volume;
        }
        break;
    }
}

/* Ordinal 11 (9:15cc): the Game Settings dialog (template 100). */
BOOL ispace_options_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_INITDIALOG:
        options_init(h);
        return 0;
    case WM_HSCROLL:
        options_scroll(h, (int)wp, (int16_t)LOWORD(lp), (HWND)HIWORD(lp));
        return 0;
    case WM_COMMAND:
        break;
    default:
        return 0;
    }
    switch (wp) {
    case IDOK:
    case IDCANCEL:
        options_end(h, wp == IDOK, opt.speed);
        return 1;
    case ID_HELP:
        ispace_help(15);
        return 0;
    case ID_NORMAL_SPEED:
        opt.speed = opt.speed_shown = 500;
        show_speed(500);
        SetFocus(GetDlgItem(h, ID_SPEED));
        return 0;
    case ID_DISPLAY:
        DialogBox(ispace_lang_module(), MAKEINTRESOURCE(666), h, ispace_display_proc);
        return 0;
    case ID_AUDIO:
        DialogBox(ispace_lang_module(), MAKEINTRESOURCE(999), h, ispace_audio_proc);
        return 0;
    case ID_JOYSTICK:
        DialogBox(ispace_lang_module(), MAKEINTRESOURCE(975), h, ispace_joy_proc);
        return 0;
    }
    return 0;
}

/* 9:1546: one Game Settings dialog at a time (a second asks to close the
 * first); the dialog sounds 0x6e and 0x13.  (It keeps ordinal 10's
 * words v1 and v0, the game's speed words, at DS:2278 and DS:227a, which
 * nothing reads.) */
int16_t ispace_options(HWND owner)
{
    char text[0x50];
    int16_t r;

    if (opt.dlg) {
        LoadString(ispace_lang_module(), 0x8ac, text, sizeof text);
        MessageBox(0, text, APP, MB_ICONEXCLAMATION);
        return 0;
    }
    ispace_sound_effect(0x6e);
    ispace_sound_effect(0x13);
    r = DialogBox(ispace_lang_module(), MAKEINTRESOURCE(100), owner, ispace_options_proc);
    ispace_dialog_fonts(0);
    opt.dlg = 0;
    return r;
}

/* 9:2dc6: OK (ok 1) puts the choices into the INI. */
static void display_end(HWND dlg, int ok)
{
    if (ok) {
        write_int("ShipAnim", (int16_t)IsDlgButtonChecked(dlg, ID_SHIP_ANIM));
        write_int("QuickIntro", selection(dlg, ID_SKIP));
        write_int("Bright", (int16_t)IsDlgButtonChecked(dlg, ID_BRIGHT));
        write_int("Border", (int16_t)IsDlgButtonChecked(dlg, ID_BORDER));
        write_int("Menu", (int16_t)IsDlgButtonChecked(dlg, ID_MENU));
        write_int("SavePrompt", (int16_t)IsDlgButtonChecked(dlg, ID_SAVE_PROMPT));
    }
    EndDialog(dlg, (int16_t)ok);
}

/* Ordinal 37 (9:2bf8): Display Options (template 666), from the INI. */
BOOL ispace_display_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    (void)lp;
    if (msg == WM_INITDIALOG) {
        ispace_dialog_set_fonts(h);
        add_strings(h, ID_SKIP, 0x96a, 3);
        select_item(h, ID_SKIP, GetPrivateProfileInt(APP, "QuickIntro", 0, INI));
        CheckDlgButton(h, ID_BRIGHT, (UINT)GetPrivateProfileInt(APP, "Bright", 0, INI));
        CheckDlgButton(h, ID_MENU, (UINT)GetPrivateProfileInt(APP, "Menu", 0, INI));
        CheckDlgButton(h, ID_BORDER, (UINT)GetPrivateProfileInt(APP, "Border", 1, INI));
        CheckDlgButton(h, ID_SHIP_ANIM, (UINT)GetPrivateProfileInt(APP, "ShipAnim", 1, INI));
        CheckDlgButton(h, ID_SAVE_PROMPT, (UINT)GetPrivateProfileInt(APP, "SavePrompt", 1, INI));
        return 0;
    }
    if (msg != WM_COMMAND)
        return 0;
    switch (wp) {
    case IDOK:
    case IDCANCEL:
        display_end(h, wp == IDOK);
        return 1;
    case ID_HELP:
        ispace_help(0x20);
        break;
    }
    return 0;
}

/* 9:2f30's WM_INITDIALOG: the settings the sound has now. */
static void audio_init(HWND dlg)
{
    IspaceSettings *set = ispace_settings();
    char num[8];
    int16_t i, best = set->device_best;

    ispace_dialog_set_fonts(dlg);
    for (i = 0; i < WAVEMIX_CHANNELS; i++) {
        SDL_snprintf(num, sizeof num, "%d", i + 1);
        combo_add_string(GetDlgItem(dlg, ID_CHANNELS), num);
    }
    select_item(dlg, ID_CHANNELS, (int16_t)(ispace_sound_channels() - 1));
    add_strings(dlg, ID_STEREO, 0x96d, 4);
    select_item(dlg, ID_STEREO, set->stereo);
    if (best < 3) {
        disable(dlg, ID_SWAP);
        disable(dlg, ID_STEREO);
    }
    if (best < 2)
        disable(dlg, ID_BALANCE);
    if (best < 1) {
        disable(dlg, ID_MUSIC);
        disable(dlg, ID_FX);
        disable(dlg, ID_VOICE);
        disable(dlg, ID_CHANNELS);
        disable(dlg, ID_KEEP);
    }
    CheckDlgButton(dlg, ID_FX, (UINT)set->fx_on);
    CheckDlgButton(dlg, ID_VOICE, (UINT)set->voice_on);
    CheckDlgButton(dlg, ID_MUSIC, (UINT)ispace_music_on());
    CheckDlgButton(dlg, ID_KEEP, set->purge == 0);
    CheckDlgButton(dlg, ID_SWAP, (UINT)set->swap);
    SetScrollRange(GetDlgItem(dlg, ID_BALANCE), SB_CTL, 0, 100, 0);
    SetScrollPos(GetDlgItem(dlg, ID_BALANCE), SB_CTL, set->balance, 1);
}

/* 9:331a: OK (ok 1) puts the choices into the INI and the sound. */
static void audio_end(HWND dlg, int ok)
{
    IspaceSettings *set = ispace_settings();
    int16_t channels;

    if (ok) {
        set->stereo = selection(dlg, ID_STEREO);
        channels = (int16_t)(selection(dlg, ID_CHANNELS) + 1);
        set->fx_on = (int16_t)IsDlgButtonChecked(dlg, ID_FX);
        set->voice_on = (int16_t)IsDlgButtonChecked(dlg, ID_VOICE);
        ispace_music_set_on((int16_t)IsDlgButtonChecked(dlg, ID_MUSIC));
        set->purge = IsDlgButtonChecked(dlg, ID_KEEP) == 0;
        set->swap = (int16_t)IsDlgButtonChecked(dlg, ID_SWAP);
        write_int("StereoEffect", set->stereo);
        write_int("FXMusic", set->balance);
        write_int("Music", ispace_music_on());
        write_int("SoundFX", set->fx_on);
        write_int("VoiceFX", set->voice_on);
        write_int("MixChannels", channels);
        write_int("PurgeSound", set->purge);
        write_int("StereoSwap", set->swap);
        ispace_sound_apply(channels);
    }
    EndDialog(dlg, (int16_t)ok);
}

/* Ordinal 38 (9:2f30): Audio Options (template 999).  The effects
 * versus music bar changes the balance at once (also for Cancel); any
 * scroll bar's message moves it [sic], a page as far as a line. */
BOOL ispace_audio_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    IspaceSettings *set = ispace_settings();

    switch (msg) {
    case WM_INITDIALOG:
        audio_init(h);
        return 0;
    case WM_HSCROLL:
        set->balance = (int16_t)SDL_clamp(scrolled(set->balance, (int)wp, (int16_t)LOWORD(lp), 1, set->balance,
                                                   set->balance), 0, 100);
        ispace_sound_mix_volumes();
        if (set->balance != opt.balance_shown) {
            SetScrollPos(GetDlgItem(h, ID_BALANCE), SB_CTL, set->balance, 1);
            opt.balance_shown = set->balance;
        }
        return 0;
    case WM_COMMAND:
        break;
    default:
        return 0;
    }
    switch (wp) {
    case IDOK:
    case IDCANCEL:
        audio_end(h, wp == IDOK);
        return 1;
    case ID_HELP:
        ispace_help(15);
        break;
    }
    return 0;
}
