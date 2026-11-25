/* ISPACE.DLL ordinal 10 (9:145e): the game's dialogs (new game, restore,
 * options, ...), run by 10:42c6 from ENG_LANG.DLL's templates with
 * dialog procedures in the DLL's segment 10.  Ported so far: mode 1's
 * Restore Game (10:0ec2) and New Game (10:0f26) dialogs with the ship
 * preview window class LevClass (10:309c), and the exit question. */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "ispace.h"

#define INI "INSPACE.INI"
#define APP "Inner Space"
#define ID_COMBO 0x14c          /* the saved games */
#define ID_CANCEL 0x14d
#define ID_PREVIEW 0x64
#define ID_SAVE_EXIT 0x251
#define ID_PILOT 0x142          /* New Game: the pilot's name */
#define ID_SHIP 0x144
#define ID_PLAY 0x145
#define ID_TEAM 0x146
#define ID_DRIVE 0x14a
#define ID_ZOOM 0x14c
#define SHIP_SIZE 0x41          /* a MASTER.SHP record: type +3, colour sets +7 +8, name +0xa, body +0x21 */
#define BODY_SIZE 0x2c          /* a MASTER.BOD record: size +0x1a, image id +0x21, image file +0x23 */
#define NAME_SIZE 0x14

static struct {
    int16_t ds_01aa, ds_204e, ds_2134, ds_2136, ds_2138, ds_213a, ds_213c;
    int16_t date[3];            /* DS:2050: day, month, year (mode 15) */
    int16_t ds_1f90;            /* the mode running */
    int16_t ds_1f92;            /* slot of the dialog's palette (3: none) */
    int16_t ds_2012;            /* the DC passed */
    int16_t ds_1f7a;            /* the new game dialog runs for mode 4 */
    int16_t ds_1f7e;            /* INI BadVideo */
    int16_t ds_1f8c;            /* the saved game shown (-1: none) */
    int16_t ds_0cea;            /* the saved game last picked */
    int16_t ds_0cec;            /* the ship last picked */
    int16_t ds_1f82, ds_2296;   /* set by dialogs not ported: 0 here */
    int16_t ds_1f78;            /* set: no team shown (by a dialog not ported; 0 here) */
    int16_t ds_1f88;            /* height of the last ship picture */
    BITMAP ds_2014;             /* the last ship picture's */
    char ship_name[NAME_SIZE];  /* DS:1554 */
    char player[NAME_SIZE];     /* DS:1568 */
    HFONT font[2];              /* DS:1714 Arial 14x6, DS:1716 the same bold */
    uint8_t *ships, *bodies;    /* DS:14e4 MASTER.SHP, DS:14e0 MASTER.BOD */
    int16_t ship_count, body_count;     /* DS:1f84, DS:1f86 */
    HWND preview[2];            /* DS:1540: LevClass windows */
    struct {
        HBITMAP bm, old_bm;     /* DS:157c, DS:1580 */
        HDC dc;                 /* DS:1588 */
        HPALETTE old_pal;       /* DS:158c */
        int16_t size;           /* DS:1544: the picture's height */
    } slot[2];
} st;

static void not_ported(const char *what)
{
    win_stub(what);
}

/* DS:0690: <Language>_LANG.DLL, which ordinal 7 (9:0174) loads. */
HINSTANCE ispace_lang_module(void)
{
    static HINSTANCE h;
    char name[128], lang[5];

    if (!h) {
        GetPrivateProfileString(APP, "Language", "", lang, sizeof lang, INI);
        SDL_snprintf(name, sizeof name, GAME_DIR "%s_LANG.DLL", lang);
        h = LoadLibrary(name);
    }
    return h;
}

static HPALETTE dialog_palette(void)
{
    return st.ds_1f92 < 3 ? ispace_pal_handle(st.ds_1f92) : 0;
}

/* 9:29c0 (make) and 9:2a1e: the dialogs' fonts. */
void ispace_dialog_fonts(int make)
{
    int i;

    for (i = 0; i < 2; i++)
        if (st.font[i]) {
            DeleteObject(st.font[i]);
            st.font[i] = 0;
        }
    if (!make)
        return;
    st.font[0] = CreateFont(14, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    st.font[1] = CreateFont(14, 6, 0, 0, 730, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
}

/* 10:3f70 and 10:406a: <ShipPath>\name read whole as records of size
 * bytes; the count is the file's length over size. */
static uint8_t *read_records(const char *name, long size, int16_t *count)
{
    char path[128];
    OFSTRUCT of;
    HFILE f;
    uint8_t *data;
    long len;

    GetPrivateProfileString(APP, "ShipPath", "", path, 0x6d, INI);
    if (path[0] && path[SDL_strlen(path) - 1] != '\\')
        SDL_strlcat(path, "\\", sizeof path);
    SDL_strlcat(path, name, sizeof path);
    *count = 0;
    if ((f = OpenFile(path, &of, 0)) == -1)
        return NULL;
    len = (int16_t)_filelength(f) / size;   /* the DLL divides the low word, sign-extended */
    data = len > 0 ? malloc((size_t)(len * size)) : NULL;
    if (data && _lread(f, data, (UINT)(len * size)) != (UINT)(len * size)) {
        free(data);
        data = NULL;
    }
    _lclose(f);
    if (data)
        *count = (int16_t)len;
    return data;
}

static void load_ships(void)
{
    st.bodies = read_records("MASTER.BOD", BODY_SIZE, &st.body_count);
    st.ships = read_records("MASTER.SHP", SHIP_SIZE, &st.ship_count);
}

/* 10:4168 */
static void free_ships(void)
{
    free(st.ships);
    free(st.bodies);
    st.ships = st.bodies = NULL;
}

/* 10:602a: the dialog's controls get the DLL's fonts (push buttons the
 * bold one) and are shown. */
void ispace_dialog_set_fonts(HWND dlg)
{
    HWND c;
    char cls[20];

    for (c = GetWindow(dlg, GW_CHILD); c; c = GetWindow(c, GW_HWNDNEXT)) {
        int bold;
        GetClassName(c, cls, sizeof cls);
        bold = !lstrcmp(cls, "Button") && (GetWindowLong(c, GWL_STYLE) & 0xff) <= 1;
        SendMessage(c, WM_SETFONT, st.font[bold], 1);
        ShowWindow(c, SW_SHOW);
    }
}

/* 10:2d3c: StretchBlt, through ordinal 36 for an exact 2x or a mirror
 * when INI BadVideo is set and the display has 2-8 bits a pixel. */
static void stretch(HDC dst, int16_t x, int16_t y, int16_t w, int16_t h, HDC src, int16_t xs, int16_t ys,
                    int16_t ws, int16_t hs, DWORD rop)
{
    HBITMAP probe = CreateCompatibleBitmap(src, 2, 2);
    BITMAP b;
    int bits, doubled, mirrored;

    memset(&b, 0, sizeof b);
    GetObject(probe, sizeof b, &b);
    bits = b.bmPlanes * b.bmBitsPixel;
    DeleteObject(probe);
    doubled = (int16_t)(2 * ws) == w && (int16_t)(2 * hs) == h;
    mirrored = (w < 0 || h < 0) && ws != 0 && w % ws == 0;     /* the DLL divides by 0 */
    if (st.ds_1f7e && bits != 1 && bits <= 8 && (doubled || mirrored))
        ispace_blit_double(dst, x, y, w, h, src, xs, ys, ws, hs, (int32_t)rop);
    else
        StretchBlt(dst, x, y, w, h, src, xs, ys, ws, hs, rop);
}

/* 10:2c68: slot's preview window cleared inside its frame and the ship
 * drawn at twice its size in the middle. */
static void draw_preview(int slot)
{
    HPALETTE old = 0;
    HDC dc;
    int16_t n = st.slot[slot].size;

    if (!st.preview[slot])
        return;
    dc = GetDC(st.preview[slot]);
    if (dialog_palette())
        old = SelectPalette(dc, dialog_palette(), 0);
    PatBlt(dc, 3, 3, 0x5a, 0x5a, BLACKNESS);
    if (st.slot[slot].dc)
        stretch(dc, (int16_t)(0x30 - n), (int16_t)(0x30 - n), (int16_t)(2 * n), (int16_t)(2 * n), st.slot[slot].dc,
                0, 0, n, n, SRCCOPY);
    if (old)
        SelectPalette(dc, old, 0);
    ReleaseDC(st.preview[slot], dc);
}

static void free_slot(int slot)
{
    if (!st.slot[slot].dc)
        return;
    if (st.slot[slot].old_pal)
        SelectPalette(st.slot[slot].dc, st.slot[slot].old_pal, 0);
    SelectObject(st.slot[slot].dc, st.slot[slot].old_bm);
    DeleteDC(st.slot[slot].dc);
    st.slot[slot].dc = 0;
    DeleteObject(st.slot[slot].bm);
    st.slot[slot].bm = 0;
}

static const uint8_t *ship_rec(int16_t i)
{
    return st.ships + (size_t)i * SHIP_SIZE;
}

/* Ship i's body, NULL when its index is outside MASTER.BOD (the DLL
 * reads past the table). */
static const uint8_t *body_of(int16_t i)
{
    const uint8_t *ship = ship_rec(i);
    int16_t k = (int16_t)(ship[0x21] | ship[0x22] << 8);

    return k >= 0 && k < st.body_count ? st.bodies + (size_t)k * BODY_SIZE : NULL;
}

static int16_t body_image(const uint8_t *body)
{
    return (int16_t)(body[0x21] | body[0x22] << 8);
}

/* 10:2aac: shows ship i (-1: none) in slot's preview (slot 2: slot 0
 * with the ramps of mode 2, see ispace_ship_image).  fill 1 and 2
 * blacken the picture left and right of a body of its size. */
static void show_ship(int16_t i, int16_t slot, int16_t fill)
{
    int16_t mode = slot, half;
    HPALETTE pal = dialog_palette();
    const uint8_t *ship, *body;
    HDC dc;

    if (slot == 2)
        slot = 0;
    free_slot(slot);
    if (i > -1 && (body = body_of(i)) != NULL) {
        ship = ship_rec(i);
        st.slot[slot].bm = ispace_ship_image(pal, body_image(body), (char *)body + 0x23,
                                             (signed char)ship[7], (signed char)ship[8], mode);
        GetObject(st.slot[slot].bm, sizeof st.ds_2014, &st.ds_2014);
        dc = st.slot[slot].dc = CreateCompatibleDC((HDC)st.ds_2012);
        st.slot[slot].old_bm = SelectObject(dc, st.slot[slot].bm);
        st.slot[slot].old_pal = pal ? SelectPalette(dc, pal, 0) : 0;
        st.ds_1f88 = st.slot[slot].size = st.ds_2014.bmHeight;
        half = (int16_t)((st.ds_2014.bmHeight - (signed char)body[0x1a]) / 2);
        if (fill >= 2) {
            PatBlt(dc, (int16_t)(st.ds_2014.bmHeight - half), 0, half, st.ds_2014.bmHeight, BLACKNESS);
            fill = (int16_t)(fill - 2);
        }
        if (fill)
            PatBlt(dc, 0, 0, half, st.slot[slot].size, BLACKNESS);
    }
    draw_preview(slot);
}

/* 10:309c: the preview window, a bevelled frame. */
static LRESULT preview_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    PAINTSTRUCT ps;
    RECT rc, r;
    HDC dc;
    HPEN old;
    int i;

    switch (msg) {
    case WM_PAINT:
        InvalidateRect(h, NULL, 1);
        GetClientRect(h, &rc);
        dc = BeginPaint(h, &ps);
        if (!st.ds_1f82) {
            SetRect(&r, rc.left, rc.top, (int16_t)(rc.left + 3), rc.bottom);
            FillRect(dc, &r, GetStockObject(LTGRAY_BRUSH));
            SetRect(&r, rc.left, rc.top, rc.right, (int16_t)(rc.top + 3));
            FillRect(dc, &r, GetStockObject(LTGRAY_BRUSH));
            SetRect(&r, (int16_t)(rc.left + 2), (int16_t)(rc.bottom - 3), rc.right, rc.bottom);
            FillRect(dc, &r, GetStockObject(DKGRAY_BRUSH));
            SetRect(&r, (int16_t)(rc.right - 3), (int16_t)(rc.top + 1), rc.right, (int16_t)(rc.bottom - 1));
            FillRect(dc, &r, GetStockObject(DKGRAY_BRUSH));
            for (i = 0; i < 3; i++) {
                SetPixel(dc, (int16_t)(rc.right - i - 2), (int16_t)(rc.top + i), RGB(192, 192, 192));
                SetPixel(dc, (int16_t)(rc.right - i - 1), (int16_t)(rc.top + i), RGB(128, 128, 128));
                SetPixel(dc, (int16_t)(rc.left - i + 2), (int16_t)(rc.bottom + i - 3), RGB(192, 192, 192));
                SetPixel(dc, (int16_t)(rc.left - i + 3), (int16_t)(rc.bottom + i - 3), RGB(0, 0, 0));
            }
            old = SelectObject(dc, GetStockObject(WHITE_PEN));
            MoveTo(dc, rc.left, (int16_t)(rc.bottom - 1));
            LineTo(dc, rc.left, rc.top);
            LineTo(dc, (int16_t)(rc.right - 1), rc.top);
            SelectObject(dc, GetStockObject(BLACK_PEN));
            LineTo(dc, (int16_t)(rc.right - 1), (int16_t)(rc.bottom - 1));
            LineTo(dc, (int16_t)(rc.left - 1), (int16_t)(rc.bottom - 1));
            SelectObject(dc, old);
        }
        EndPaint(h, &ps);
        if (st.ds_2296)
            not_ported("ispace dialog: 9:48f8");
        else if (st.ds_1f82)
            not_ported("ispace dialog: 10:02f4");
        else
            for (i = 0; i < 2; i++)
                draw_preview(i);
        return 0;
    case WM_NCPAINT:
        return 0;
    case WM_COMMAND:
        PostMessage(GetParent(h), WM_COMMAND, wp, lp);
        return 0;
    }
    return DefWindowProc(h, msg, wp, lp);
}

/* 10:4250: the preview's window class; nonzero null_brush leaves the
 * background unpainted. */
static ATOM register_preview(int null_brush)
{
    WNDCLASS wc;

    memset(&wc, 0, sizeof wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = preview_proc;
    wc.hInstance = ispace_module();
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = GetStockObject(null_brush ? NULL_BRUSH : BLACK_BRUSH);
    wc.lpszClassName = "LevClass";
    return RegisterClass(&wc);
}

/* The height of "Test" in the dialogs' font: a list item's. */
static int16_t text_height(HWND dlg)
{
    HDC dc = GetDC(dlg);
    HFONT old = SelectObject(dc, st.font[0]);
    int16_t h = (int16_t)HIWORD(GetTextExtent(dc, "Test", 4));

    SelectObject(dc, old);
    ReleaseDC(dlg, dc);
    return h;
}

/* 10:1a80: the saved game's details (i 0: " NEW GAME"). */
static void restore_show(HWND dlg, int16_t i)
{
    char text[0x3c];

    if (i != 0) {
        not_ported("ispace dialog: saved game details (10:1b13)");
        return;
    }
    SetWindowText(GetDlgItem(dlg, 331), "?");
    SetWindowText(GetDlgItem(dlg, 329), "?");
    SetWindowText(GetDlgItem(dlg, 269), "?");
    LoadString(ispace_lang_module(), 0x47d, text, sizeof text);
    SetWindowText(GetDlgItem(dlg, 330), text);
    st.ds_1f8c = -1;
    show_ship(-1, 0, 0);
}

/* 10:1438: centres the dialog, lists " NEW GAME" and the saved games
 * (GAMES\*.SAV but DEMOGAME), sizes the list to them, adds the preview
 * and picks the game of INI Restore. */
static void restore_init(HWND dlg)
{
    RECT client, win, combo_r;
    POINT org = {0, 0};
    struct _find_t ff;
    char name[0x14 + 0x80], pattern[160];
    HWND combo = GetDlgItem(dlg, ID_COMBO);
    int16_t item_h, count = 1, x, y, i;
    uint16_t r;

    GetClientRect(dlg, &client);
    GetWindowRect(dlg, &win);
    item_h = text_height(dlg);
    ClientToScreen(dlg, &org);
    x = (int16_t)(GetSystemMetrics(SM_CXSCREEN) / 2 + (win.left - win.right) / 2);
    y = (int16_t)(GetSystemMetrics(SM_CYSCREEN) / 2 + (win.top - win.bottom) / 2);
    load_ships();
    ispace_dialog_set_fonts(dlg);
    combo_add_string(combo, " NEW GAME");
    GetPrivateProfileString(APP, "LocalPath", "", pattern, 0x6d, INI);
    if (pattern[0] && pattern[SDL_strlen(pattern) - 1] != '\\')
        SDL_strlcat(pattern, "\\", sizeof pattern);
    SDL_strlcat(pattern, "GAMES\\*.SAV", sizeof pattern);
    for (r = _dos_findfirst(pattern, 1, &ff); r == 0; r = _dos_findnext(&ff)) {
        count++;
        SDL_strlcpy(name, ff.name, sizeof name);
        for (i = 0; i < 4 && name[0]; i++)
            name[lstrlen(name) - 1] = 0;
        if (lstrcmp(name, "DEMOGAME"))
            combo_add_string(combo, name);
    }
    SendMessage(combo, CB_SETCURSEL, 0, 0);
    GetWindowRect(combo, &combo_r);
    MoveWindow(combo, (int16_t)(combo_r.left - org.x), (int16_t)(combo_r.top - org.y),
               (int16_t)(combo_r.right - combo_r.left), (int16_t)(item_h * count + 0x1e), 1);
    if (register_preview(0))
        st.preview[0] = CreateWindow("LevClass", NULL, WS_CHILD | WS_VISIBLE, 4, (int16_t)(client.bottom - 0x71),
                                     0x60, 0x60, dlg, ID_PREVIEW, ispace_module(), NULL);
    GetPrivateProfileString(APP, "Restore", "", name, 0x14, INI);
    st.ds_1f7e = GetPrivateProfileInt(APP, "BadVideo", 1, INI);
    i = combo_find_string(combo, -1, name);
    if (i < 0)
        i = 0;
    SendMessage(combo, CB_SETCURSEL, (WPARAM)i, 0);
    restore_show(dlg, i);
    SetFocus(combo);
    MoveWindow(dlg, x, y, (int16_t)(win.right - win.left), (int16_t)(win.bottom - win.top), 1);
}

/* 10:1d36: OK (ok 1) remembers the choice in the INI; the dialog ends
 * with 1 for " NEW GAME", 2 for a saved game, 0 for Cancel. */
static void restore_end(HWND dlg, int ok)
{
    HWND combo = GetDlgItem(dlg, ID_COMBO);
    char name[0x34];
    int16_t sel = 0;

    if (ok) {
        sel = (int16_t)SendMessage(combo, CB_GETCURSEL, 0, 0);
        combo_get_text(combo, sel, name, sizeof name);
        WritePrivateProfileString(APP, "Restore", name, INI);
        if (st.ds_1f8c >= 0)
            not_ported("ispace dialog: restore ship and player (10:1da2)");
    }
    free_slot(0);
    if (st.preview[0]) {
        DestroyWindow(st.preview[0]);
        st.preview[0] = 0;
    }
    UnregisterClass("LevClass", ispace_module());
    free_ships();
    EndDialog(dlg, (int16_t)(ok ? (sel == 0 ? 1 : 2) : 0));
}

/* 10:0ec2 */
static BOOL restore_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_INITDIALOG) {
        restore_init(h);
        return 0;
    }
    if (msg != WM_COMMAND)
        return 0;
    switch (wp) {
    case IDOK:
        restore_end(h, 1);
        return 1;
    case ID_COMBO:
        if (HIWORD(lp) == CBN_SELCHANGE) {      /* 10:1a38 */
            int16_t i = (int16_t)SendMessage((HWND)LOWORD(lp), CB_GETCURSEL, 0, 0);
            if (i != -1) {
                restore_show(h, i);
                st.ds_0cea = i;
            }
        }
        return 0;
    case ID_CANCEL:
        restore_end(h, 0);
        return 1;
    }
    return 0;
}

/* 10:611c: ship i may be played.  The registered flag (DS:01ac) is
 * worked out once: the CD of WIN.INI CDDrive, else the key and the
 * registered name in INSPACE.EXE (ordinal 24).  Unregistered, or in the
 * mode 3 version (DS:01aa), some bodies are not offered. */
static int ship_allowed(int16_t i)
{
    static const int16_t full_only[] = {
        178, 310, 320, 400, 440, 450, 520, 550, 560, 590, 600, 604, 605, 710, 720, 730, 750, 890, 900, 930, 950
    };
    int16_t *registered = ispace_ds_01ac(), id;
    char drive[0x50], name[0x3e], key[10];
    size_t k;

    if (*registered == -1) {
        memset(name, 0, sizeof name);
        GetProfileString(APP, "CDDrive", "", drive, 0x28);
        if (drive[0] && ispace_check(drive, key, 21) == 0)
            return 1;
        *registered = ispace_check(name, key, 2) ? 0 : ispace_check(name, key, 10);
    }
    if (*registered && st.ds_01aa != 3)
        return 1;
    if (st.ds_01aa == 3 && i != 1)
        return 0;
    if (!body_of(i))
        return 1;
    id = body_image(body_of(i));
    for (k = 0; k < sizeof full_only / sizeof full_only[0]; k++)
        if (id == full_only[k])
            return 0;
    return 1;
}

/* 10:41cc: the name of team type (INI [Teams] Team<type + 1>). */
static void team_name(int16_t type, char *out)
{
    char section[0x28], key[0x28], num[8];

    LoadString(ispace_lang_module(), 0x8e7, key, sizeof key);
    lstrcpy(section, key);
    lstrcat(section, "s");
    SDL_snprintf(num, sizeof num, "%d", type + 1);
    lstrcat(key, num);
    GetPrivateProfileString(section, key, "", out, NAME_SIZE, INI);
}

static void show_team(HWND dlg, int16_t i)
{
    char text[0x24];

    team_name((signed char)ship_rec(i)[3], text);
    SetWindowText(GetDlgItem(dlg, ID_TEAM), text);
}

static void add_strings(HWND combo, int16_t first, int n)
{
    char text[0x24];
    int k;

    for (k = 0; k < n; k++) {
        LoadString(ispace_lang_module(), (UINT)(first + k), text, 0x1e);
        combo_add_string(combo, text);
    }
}

/* The drives C-Z with their volume labels ("C: LABEL"); the one of INI
 * Drive is picked.  Returns how many. */
static int16_t list_drives(HWND combo, int16_t *pick)
{
    struct _find_t ff;
    char want[0xa], pattern[8], item[0x24];
    int16_t saved = _getdrive(), d, count = 0, k;

    SetErrorMode(1);
    GetPrivateProfileString(APP, "Drive", "C", want, sizeof want, INI);
    *pick = 0;
    for (d = 3; d <= 26; d++) {
        if (_chdrive(d))
            continue;
        lstrcpy(pattern, "A:\\*.*");
        pattern[0] = (char)(pattern[0] + d - 1);
        memset(&ff, 0, sizeof ff);
        if (_dos_findfirst(pattern, _A_VOLID, &ff))
            lstrcpy(ff.name, "Unknown_HD");
        count++;
        if (want[0] == pattern[0])
            *pick = (int16_t)(count - 1);
        lstrcpy(item, "C: ");
        item[0] = (char)(item[0] + d - 3);
        if (lstrlen(ff.name) > 7 && ff.name[8] == '.')
            for (k = 8; lstrlen(ff.name) > k; k++)
                ff.name[k] = ff.name[k + 1];
        lstrcat(item, ff.name);
        combo_add_string(combo, item);
    }
    _chdrive(saved);
    return count;
}

/* MainShip, unless it may not be played (then TRANSFORMER, written
 * back); the mode 1 version always plays TRANSFORMER. */
static void ini_main_ship(char *name)
{
    int16_t i;

    GetPrivateProfileString(APP, "MainShip", "EAGLE", name, NAME_SIZE, INI);
    if (st.ds_01aa) {
        lstrcpy(name, "TRANSFORMER");
        return;
    }
    for (i = 0; i < st.ship_count; i++) {
        if (lstrcmp((LPCSTR)ship_rec(i) + 0xa, name))
            continue;
        if (ship_rec(i)[3] == 7 || !ship_allowed(i)) {
            lstrcpy(name, "TRANSFORMER");
            WritePrivateProfileString(APP, "MainShip", name, INI);
            return;
        }
    }
}

/* 10:1e7c: zoom levels, the ships that may be played, the drives, play
 * modes and the pilot's name from the INI; the preview at the bottom
 * right; the dialog centred. */
static void newgame_init(HWND dlg)
{
    RECT client, win, r = {0, 0, 0, 0};
    POINT org = {0, 0};
    HWND c;
    char name[NAME_SIZE];
    int16_t item_h, x, y, i, n, pick;

    GetClientRect(dlg, &client);
    GetWindowRect(dlg, &win);
    item_h = text_height(dlg);
    ClientToScreen(dlg, &org);
    x = (int16_t)(GetSystemMetrics(SM_CXSCREEN) / 2 + (win.left - win.right) / 2);
    y = (int16_t)(GetSystemMetrics(SM_CYSCREEN) / 2 + (win.top - win.bottom) / 2);
    load_ships();
    ispace_dialog_set_fonts(dlg);
    add_strings(GetDlgItem(dlg, ID_ZOOM), 0x8b6, 3);
    SendMessage(GetDlgItem(dlg, ID_ZOOM), CB_SETCURSEL, (WPARAM)(2 - GetPrivateProfileInt(APP, "SetSize", 1, INI)), 0);
    for (i = 0; i < st.ship_count; i++)
        if (ship_rec(i)[0xa] && ship_rec(i)[3] != 7 && ship_allowed(i))
            combo_add_string(GetDlgItem(dlg, ID_SHIP), (LPCSTR)ship_rec(i) + 0xa);
    n = list_drives(GetDlgItem(dlg, ID_DRIVE), &pick);
    c = GetDlgItem(dlg, ID_DRIVE);
    GetWindowRect(c, &r);
    MoveWindow(c, (int16_t)(r.left - org.x), (int16_t)(r.top - org.y), (int16_t)(r.right - r.left),
               (int16_t)(item_h * n + 0x1e), 1);
    c = GetDlgItem(dlg, ID_PLAY);
    GetWindowRect(c, &r);
    MoveWindow(c, (int16_t)(r.left - org.x), (int16_t)(r.top - org.y), (int16_t)(r.right - r.left),
               (int16_t)((item_h + 0xf) * 2), 1);
    if (!st.ds_1f7a)
        add_strings(c, 0x8e3, 2);
    if (register_preview(0))
        st.preview[0] = CreateWindow("LevClass", NULL, WS_CHILD | WS_VISIBLE, (int16_t)(client.right - 0x68),
                                     (int16_t)(client.bottom - 0x67), 0x60, 0x60, dlg, ID_PREVIEW, ispace_module(), NULL);
    MoveWindow(dlg, x, y, (int16_t)(win.right - win.left), (int16_t)(win.bottom - win.top), 1);
    SendMessage(GetDlgItem(dlg, ID_DRIVE), CB_SETCURSEL, (WPARAM)pick, 0);
    GetPrivateProfileString(APP, "ThePlayer", "AutoPilot", st.player, NAME_SIZE, INI);
    ini_main_ship(name);
    if (!st.ds_1f7a) {
        SendMessage(GetDlgItem(dlg, ID_PLAY), CB_SETCURSEL, (WPARAM)GetPrivateProfileInt(APP, "PlayMode", 0, INI), 0);
        SetWindowText(GetDlgItem(dlg, ID_PILOT), st.player);
    }
    i = combo_find_string(GetDlgItem(dlg, ID_SHIP), -1, name);
    SendMessage(GetDlgItem(dlg, ID_SHIP), CB_SETCURSEL, (WPARAM)(i < 0 ? 0 : i), 0);
    lstrcpy(st.ship_name, name);
    for (i = 0; i < st.ship_count; i++)
        if (!lstrcmp((LPCSTR)ship_rec(i) + 0xa, st.ship_name)) {
            show_ship(i, 0, 0);
            show_team(dlg, i);
            break;
        }
    SetFocus(GetDlgItem(dlg, ID_SHIP));
}

/* 10:2978: a ship picked in the list (id 0x144 here; 0xa8 and 0x1b3 in
 * dialogs not ported show it in slot 2 and 1). */
static void ship_picked(HWND dlg, int16_t id, HWND combo)
{
    int16_t sel = (int16_t)SendMessage(combo, CB_GETCURSEL, 0, 0), slot, i, found = 0;

    if (sel == -1)
        return;
    combo_get_text(combo, sel, st.ship_name, NAME_SIZE);
    slot = id == 0xa8 ? 2 : id == 0x1b3 ? 1 : 0;
    for (i = 0; i < st.ship_count; i++) {
        if (lstrcmp((LPCSTR)ship_rec(i) + 0xa, st.ship_name))
            continue;
        show_ship(i, slot, 0);
        found = 1;
        if (!st.ds_1f78 && slot != 2)
            show_team(dlg, i);
    }
    if (!found)
        show_ship(-1, slot, 0);
    st.ds_0cec = sel;
}

/* A message box of language strings first..first + n - 1. */
static int16_t ask(HWND dlg, UINT first, int n, int16_t size, UINT type)
{
    char text[0xfa], part[0xc8];
    int k;

    text[0] = 0;
    for (k = 0; k < n; k++) {
        LoadString(ispace_lang_module(), first + (UINT)k, part, size);
        SDL_strlcat(text, part, sizeof text);
    }
    return MessageBox(dlg, text, APP, type);
}

static void write_int(LPCSTR key, int16_t v)
{
    char num[8];

    SDL_snprintf(num, sizeof num, "%d", v);
    WritePrivateProfileString(APP, key, num, INI);
}

/* 10:250c (ok 1): the choices go into the INI; the first time Command
 * mode is picked (and the tenth) it asks to be sure.  Returns 0 while
 * the dialog stays. */
static int newgame_end(HWND dlg, int ok)
{
    char drive[0x24] = "";
    int16_t play, n;

    if (ok) {
        if (st.ds_01aa && lstrcmp(st.ship_name, "TRANSFORMER")) {
            ask(dlg, 0x916, 2, 0x8c, MB_ICONEXCLAMATION);
            return 0;
        }
        WritePrivateProfileString(APP, "MainShip", st.ship_name, INI);
        combo_get_text(GetDlgItem(dlg, ID_DRIVE), (int16_t)SendMessage(GetDlgItem(dlg, ID_DRIVE), CB_GETCURSEL, 0, 0),
                       drive, sizeof drive);
        drive[1] = 0;
        WritePrivateProfileString(APP, "Drive", drive, INI);
    }
    if (ok && !st.ds_1f7a) {
        n = (int16_t)(2 - SendMessage(GetDlgItem(dlg, ID_ZOOM), CB_GETCURSEL, 0, 0));
        write_int("Size", n);
        write_int("SetSize", n);
        GetWindowText(GetDlgItem(dlg, ID_PILOT), st.player, NAME_SIZE);
        WritePrivateProfileString(APP, "ThePlayer", st.player, INI);
        play = (int16_t)SendMessage(GetDlgItem(dlg, ID_PLAY), CB_GETCURSEL, 0, 0);
        write_int("PlayMode", play);
        if (play) {
            ispace_sound_effect(0x6e);
            ispace_sound_effect(0x2c);
            n = GetPrivateProfileInt(APP, "StratAsk", 0, INI);
            if (n == 0 || n == 10) {
                if (ask(dlg, 0xb22, 4, 0xc8, MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
                    return 1;
                write_int("StratAsk", (int16_t)(n + 1));
            }
        }
    }
    free_slot(0);
    if (st.preview[0]) {
        DestroyWindow(st.preview[0]);
        st.preview[0] = 0;
    }
    UnregisterClass("LevClass", ispace_module());
    free_ships();
    st.ds_1f7a = 0;
    EndDialog(dlg, (int16_t)ok);
    return 1;
}

/* 10:0f26 */
static BOOL newgame_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_INITDIALOG) {
        newgame_init(h);
        return 0;
    }
    if (msg != WM_COMMAND)
        return 0;
    switch (wp) {
    case IDOK:
        return newgame_end(h, 1) != 0;
    case ID_SHIP:
        if (HIWORD(lp) == CBN_SELCHANGE)
            ship_picked(h, (int16_t)wp, (HWND)LOWORD(lp));
        return 0;
    case ID_CANCEL:
        newgame_end(h, 0);
        return 1;
    }
    return 0;
}

/* 10:109a: the exit question (mode 5: leave the game, 7: back to the
 * intro); Save & Exit only for game modes 1-3 while someone plays. */
static void exit_init(HWND h)
{
    RECT win;
    HINSTANCE inst = GetWindowWord(GetParent(h), GWW_HINSTANCE);
    char name[0x14], text[0x50];
    int16_t x, y;

    GetWindowRect(h, &win);
    x = (int16_t)(GetSystemMetrics(SM_CXSCREEN) / 2 + (win.left - win.right) / 2);
    y = (int16_t)(GetSystemMetrics(SM_CYSCREEN) / 2 + (win.top - win.bottom) / 2);
    SendDlgItemMessage(h, 0x24f, STM_SETICON, LoadIcon(inst, "GAME"), 0);
    if (st.ds_213c == 5) {
        LoadString(inst, 0x708, name, sizeof name);
        LoadString(ispace_lang_module(), 0xb4, text, sizeof text);
        lstrcat(text, name);
    } else {
        LoadString(ispace_lang_module(), 0xae, text, sizeof text);
    }
    lstrcat(text, "?");
    SetWindowText(GetDlgItem(h, 0x24e), text);
    EnableWindow(GetDlgItem(h, ID_SAVE_EXIT), 0);
    if (st.ds_2136 == 1)
        ShowWindow(GetDlgItem(h, ID_SAVE_EXIT), SW_HIDE);
    else if (st.ds_2134 && st.ds_2138 >= 1 && st.ds_2138 <= 3)
        EnableWindow(GetDlgItem(h, ID_SAVE_EXIT), 1);
    ispace_dialog_set_fonts(h);
    SetFocus(GetDlgItem(h, ID_CANCEL));
    MoveWindow(h, x, y, (int16_t)(win.right - win.left), (int16_t)(win.bottom - win.top), 1);
}

/* 10:103c: ends with 1 (Exit), 0x251 (Save & Exit) or 0 (Cancel). */
static BOOL exit_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    (void)lp;
    if (msg == WM_INITDIALOG) {
        exit_init(h);
        return 0;
    }
    if (msg != WM_COMMAND || (wp != IDOK && wp != ID_CANCEL && wp != ID_SAVE_EXIT))
        return 0;
    EndDialog(h, (int16_t)(wp == ID_CANCEL ? 0 : wp));
    return 1;
}

/* One of the DLL's dialogs, or a note that it is not ported yet. */
static int16_t run(HWND owner, int id, DLGPROC proc, const char *what)
{
    if (!proc) {
        not_ported(what);
        return 0;
    }
    return DialogBox(ispace_lang_module(), MAKEINTRESOURCE(id), owner, proc);
}

/* 10:42c6 */
static int16_t dialogs(HWND owner, int16_t dc, HPALETTE pal, int16_t mode)
{
    int16_t r;

    for (st.ds_1f92 = 0; st.ds_1f92 < 3 && ispace_pal_handle(st.ds_1f92) != pal; st.ds_1f92++)
        ;
    st.ds_2012 = dc;
    ispace_dialog_fonts(1);
    st.ds_1f90 = mode;
    switch (mode) {
    case 12:
    case 14:
        r = run(owner, mode == 12 ? 0x31f : 0x750, NULL, "ispace dialog: 10:5f96");
        break;
    case 8:
        r = run(owner, 0x2b5, NULL, "ispace dialog: 10:0664");
        if (r == 1)
            r = run(owner, 0x3dc, NULL, "ispace dialog: 10:124a");
        break;
    case 11:
        r = run(owner, 0x3dc, NULL, "ispace dialog: 10:124a");
        break;
    case 1:
        r = run(owner, 0x10b, restore_proc, "");
        if (r == 1) {
            st.ds_1f7a = 0;
            r = run(owner, 0x141, newgame_proc, "");
        }
        break;
    case 4:
        st.ds_1f7a = 1;
        r = run(owner, 0x24d, newgame_proc, "");
        break;
    case 6:
        r = run(owner, 0x11e, NULL, "ispace dialog: 10:0f9c");
        break;
    case 5:
    case 7:
        r = run(owner, 0xf4, exit_proc, "");
        break;
    case 2:
        r = run(owner, 0x1b0, NULL, "ispace dialog: 10:3346");
        break;
    default:
        r = run(owner, 0xa7, NULL, "ispace dialog: 10:0dc0");
        break;
    }
    ispace_dialog_fonts(0);
    return r;
}

/* Ordinal 10 (9:145e): seven words, the mode last.  Modes 1-8 keep some
 * of the words for their dialogs; 15 sets the date the dialogs show. */
int16_t ispace_dialog(int16_t hwnd, int16_t dc, int16_t pal, int16_t v1, int16_t v0, int16_t w6,
                      int16_t mode)
{
    st.ds_2136 = w6;
    st.ds_213c = mode;
    switch (mode) {
    case 6:
        st.ds_2134 = v1;
        st.ds_01aa = v0;
        break;
    case 1:
    case 4:
        st.ds_01aa = v0;
        break;
    case 5:
    case 7:
        st.ds_2138 = v1;
        st.ds_2134 = v0;
        break;
    case 8:
        st.ds_213a = v0;
        st.ds_204e = v1;
        break;
    }
    switch (mode) {
    case 15:
        st.date[0] = pal;
        st.date[1] = v1;
        st.date[2] = v0;
        return 1;
    case 0:
        return ispace_options((HWND)hwnd);
    case 9:
        not_ported("ispace dialog: mode 9 (10:5b24)");
        return 0;
    case 10:
    case 13:
        return 0;               /* the DLL returns what AX holds: not modelled */
    default:
        return mode > 15 ? 0 : dialogs((HWND)hwnd, dc, (HPALETTE)pal, mode);
    }
}

int16_t ispace_dialog_word6(void)
{
    return st.ds_2136;
}

/* The palette slot of the last dialog (DS:1f92), which ordinal 36
 * draws with; 0 before any. */
int ispace_dialog_slot(void)
{
    return st.ds_1f92 < 3 ? st.ds_1f92 : 0;
}
