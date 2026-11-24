/* ISPACE.DLL ordinal 10 (9:145e): the game's dialogs (new game, restore,
 * options, ...), run by 10:42c6 from ENG_LANG.DLL's templates with
 * dialog procedures in the DLL's segment 10.  Ported so far: the
 * Restore Game dialog (mode 1's first, 10:0ec2), with its ship preview
 * window class LevClass (10:309c) as far as " NEW GAME" shows it. */
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
#define STM_SETICON (WM_USER + 0)
#define SHIP_SIZE 0x41          /* a MASTER.SHP record */
#define BODY_SIZE 0x2c          /* a MASTER.BOD record */

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
    int16_t ds_1f82, ds_2296;   /* set by dialogs not ported: 0 here */
    HFONT font[2];              /* DS:1714 Arial 14x6, DS:1716 the same bold */
    uint8_t *ships, *bodies;    /* DS:14e4 MASTER.SHP, DS:14e0 MASTER.BOD */
    int16_t ship_count, body_count;     /* DS:1f84, DS:1f86 */
    HWND preview[2];            /* DS:1540: LevClass windows */
    struct {
        HBITMAP bm, old_bm;     /* DS:157c, DS:1580 */
        HDC dc;                 /* DS:1588 */
        HPALETTE old_pal;       /* DS:158c */
    } slot[2];
} st;

static void not_ported(const char *what)
{
    win_stub(what);
}

/* DS:0690: <Language>_LANG.DLL, which ordinal 7 (9:0174) loads. */
static HINSTANCE lang_module(void)
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

/* 9:29c0 and 9:2a1e: the dialogs' fonts. */
static void make_fonts(void)
{
    st.font[0] = CreateFont(14, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    st.font[1] = CreateFont(14, 6, 0, 0, 730, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
}

static void free_fonts(void)
{
    int i;

    for (i = 0; i < 2; i++)
        if (st.font[i]) {
            DeleteObject(st.font[i]);
            st.font[i] = 0;
        }
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
    if ((f = OpenFile(path, &of, 0)) == -1)
        return NULL;
    len = (int16_t)_filelength(f) / size;   /* the DLL divides the low word, sign-extended */
    *count = (int16_t)len;
    data = len > 0 ? malloc((size_t)(len * size)) : NULL;
    if (data && _lread(f, data, (UINT)(len * size)) != (UINT)(len * size)) {
        free(data);
        data = NULL;
    }
    _lclose(f);
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
static void set_fonts(HWND dlg)
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

/* 10:2c68: slot's preview window cleared inside its frame (and the
 * ship drawn, not ported). */
static void draw_preview(int slot)
{
    HPALETTE old = 0;
    HDC dc;

    if (!st.preview[slot])
        return;
    dc = GetDC(st.preview[slot]);
    if (dialog_palette())
        old = SelectPalette(dc, dialog_palette(), 0);
    PatBlt(dc, 3, 3, 0x5a, 0x5a, BLACKNESS);
    if (st.slot[slot].dc)
        not_ported("ispace dialog: ship picture (10:2d3c)");
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

/* 10:2aac: shows ship i (-1: none) in slot's preview. */
static void show_ship(int i, int slot)
{
    if (slot == 2)
        slot = 0;
    free_slot(slot);
    if (i > -1)
        not_ported("ispace dialog: ship preview (10:2b2f)");
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
    LoadString(lang_module(), 0x47d, text, sizeof text);
    SetWindowText(GetDlgItem(dlg, 330), text);
    st.ds_1f8c = -1;
    show_ship(-1, 0);
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
    HFONT old;
    HDC dc;
    int16_t item_h, count = 1, x, y, i;
    uint16_t r;

    GetClientRect(dlg, &client);
    GetWindowRect(dlg, &win);
    dc = GetDC(dlg);
    old = SelectObject(dc, st.font[0]);
    item_h = (int16_t)HIWORD(GetTextExtent(dc, "Test", 4));
    SelectObject(dc, old);
    ReleaseDC(dlg, dc);
    ClientToScreen(dlg, &org);
    x = (int16_t)(GetSystemMetrics(SM_CXSCREEN) / 2 + (win.left - win.right) / 2);
    y = (int16_t)(GetSystemMetrics(SM_CYSCREEN) / 2 + (win.top - win.bottom) / 2);
    load_ships();
    set_fonts(dlg);
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
        LoadString(lang_module(), 0xb4, text, sizeof text);
        lstrcat(text, name);
    } else {
        LoadString(lang_module(), 0xae, text, sizeof text);
    }
    lstrcat(text, "?");
    SetWindowText(GetDlgItem(h, 0x24e), text);
    EnableWindow(GetDlgItem(h, ID_SAVE_EXIT), 0);
    if (st.ds_2136 == 1)
        ShowWindow(GetDlgItem(h, ID_SAVE_EXIT), SW_HIDE);
    else if (st.ds_2134 && st.ds_2138 >= 1 && st.ds_2138 <= 3)
        EnableWindow(GetDlgItem(h, ID_SAVE_EXIT), 1);
    set_fonts(h);
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
    return DialogBox(lang_module(), MAKEINTRESOURCE(id), owner, proc);
}

/* 10:42c6 */
static int16_t dialogs(HWND owner, int16_t dc, HPALETTE pal, int16_t mode)
{
    int16_t r;

    for (st.ds_1f92 = 0; st.ds_1f92 < 3 && ispace_pal_handle(st.ds_1f92) != pal; st.ds_1f92++)
        ;
    st.ds_2012 = dc;
    make_fonts();
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
            r = run(owner, 0x141, NULL, "ispace dialog: New Game (10:0f26)");
        }
        break;
    case 4:
        st.ds_1f7a = 1;
        r = run(owner, 0x24d, NULL, "ispace dialog: New Game (10:0f26)");
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
    free_fonts();
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
        not_ported("ispace dialog: mode 0 (9:1546)");
        return 0;
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

/* The palette slot of the last dialog (DS:1f92), which ordinal 36
 * draws with; 0 before any. */
int ispace_dialog_slot(void)
{
    return st.ds_1f92 < 3 ? st.ds_1f92 : 0;
}
