/* INSPACE.EXE segment 2 (selector 1008). */
#include "inspace.h"
#include <stdlib.h>

extern int g_0020;
extern RECT g_1d20;
extern int g_8f6a;
extern int g_8e5e;
extern int g_8f70;
extern int g_90f8;
extern DWORD g_1d40;
extern int g_0592;
extern int g_8f68;
extern int flow_interactive;        /* DS:95bc */
extern int g_90f4;
extern int g_95b8;
extern int g_8f64;
extern int g_90f6;
extern HMENU g_90fa;
extern int g_9134;
void far fn_11_0afe(void);
void far fn_02_170e(void);
int far fn_02_1ac8(void);
void far fn_02_1b96(void);
void far fn_09_0c06(void);
int far fn_10_01fe(void);
extern HRGN g_0012;
extern int g_13de;
extern int g_968e;
extern char g_8f7a[];
int far fn_06_1290(char far *key, int def);
extern int g_0a7c;
extern HWND g_9460;
extern int g_90ea;
extern int g_90ec;
extern int g_0010;
extern int g_0a70;
extern int g_0a78;
extern int g_8e58;
extern int g_8e5a;
extern RECT g_1d28;
extern RECT g_1d30;
int far fn_10_0000(void);
void far fn_02_0ca4(void);
void far fn_07_11cc(void);
void far fn_07_1208(void);
extern int g_1038;
extern int g_9646;
typedef struct {
    int x;              /* +0x00 */
    int y;              /* +0x02 */
    char p04[0x22 - 0x04];
    int f22;            /* +0x22 */
    char rest[0x70 - 0x24];
} REC_70P;
extern REC_70P far *g_1e30;
extern int g_1dc4;
extern int g_1dc6;
extern int g_1dc8;
extern int g_1dca;
extern HINSTANCE g_8e66;
void far fn_10_7480(int a);
extern char *g_0078;
extern char *g_007a;
extern char *g_007c;
extern char *g_007e;
extern char *g_0080;
extern FARPROC g_1d4c;
extern FARPROC g_1d50;
extern FARPROC g_1d54;

/* @addr 2:094c */
int far fn_02_094c(UINT id)
{
    return LoadString(g_9212, id, g_8e68, 249);
}

/* @addr 2:1a5a */
void far fn_02_1a5a(int a, int b, long c)
{
    g_fp_1d5c(a, b, c);
}

/* @addr 2:1a7a */
int far fn_02_1a7a(int a)
{
    if (g_0024)
        return g_fp_1d58(a);
    return 0;
}

/* @addr 2:1a9e */
void far fn_02_1a9e(void)
{
    int r;

    if (g_0024) {
        FreeLibrary(g_0024);
        g_0024 = 0;
    }
}

/* @addr 2:11c0 */
void far fn_02_11c0(void)
{
    if (!IsIconic(g_0016)) {
        if (!g_0020)
            GetWindowRect(g_0016, &g_1d20);
        g_8f6a = 1;
    }
}

/* @addr 2:084c */
void far fn_02_084c(int id)
{
    switch (id) {
    case 0x9fa:
        g_8f70 = g_8e5e = 0;
        break;
    case 0x9f0:
        g_8f70 = g_8e5e = 1;
        break;
    }
    g_90f8 = 1;
    g_1d40 = GetCurrentTime();
}

/* @addr 2:09c4 */
void far fn_02_09c4(void)
{
    char buf[80];

    g_0592 = 2;
    g_8f68 = 0;
    LoadString(g_9212, 0x7fc, buf, 80);
    SetWindowText(g_0016, buf);
}

/* @addr 2:18b8 */
int far fn_02_18b8(int a)
{
    int v;
    int r;

    v = a;
    if (!flow_interactive)
        v = 0;
    switch (g_90f4) {
    case 0:
    case 4:
    case 5:
        v = 0;
        break;
    }
    if (v == 0)
        r = 0x401;
    else
        r = 0x400;
    return r;
}

/* @addr 2:0970 */
void far fn_02_0970(void)
{
    if (!g_90f4 && g_95b8 >= 4 && g_95b8 < 6)
        g_8f64 = 1;
    if (g_90f4 == 6 || g_90f4 == 8)
        g_8f64 = 1;
    if (g_8f64)
        fn_11_0afe();
    else
        g_8f64 = 1;
}

/* @addr 2:134c */
void far pascal fn_02_134c(int unused, POINT pt)
{
    HMENU hm;
    HMENU hs;

    hm = LoadMenu(g_9212, "PopupMenu");
    if (hm) {
        hs = GetSubMenu(hm, 0);
        ClientToScreen(g_0016, &pt);
        TrackPopupMenu(hs, 0, pt.x, pt.y, 0, g_0016, NULL);
        DestroyMenu(hm);
    }
}

/* @addr 2:16a2 */
void far fn_02_16a2(void)
{
    if (g_90f6)
        SetWindowWord(g_0016, -12, 0);
    fn_02_170e();
    if (g_90fa)
        DestroyMenu(g_90fa);
    if (g_9134)
        g_90fa = LoadMenu(g_9212, MAKEINTRESOURCE(0x66));
    else
        g_90fa = LoadMenu(g_9212, MAKEINTRESOURCE(0x65));
    if (g_90f6)
        SetMenu(g_0016, g_90fa);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_02_170e(void)
{
    g_90f6 = 0;
}

/* @addr 2:0a06 */
void far fn_02_0a06(void)
{
    BYTE ks[256];
    char buf[80];

    GetKeyboardState(ks);
    ks[VK_CONTROL] &= 0x7f;
    ks[VK_SHIFT] &= 0x7f;
    ks[VK_SPACE] &= 0x7f;
    ks[VK_MENU] &= 0x7f;
    ks[VK_CAPITAL] &= 0x7f;
    SetKeyboardState(ks);
    LoadString(g_9212, 0x921, buf, 80);
    SetWindowText(g_0016, buf);
    g_8f68 = 1;
}

/* @addr 2:1d58 */
void far fn_02_1d58(void)
{
    int u1;
    int u2;

    g_13dc = GetDC(g_0016);
    SelectClipRgn(g_13dc, g_0012);
    fn_10_01fe();
    ReleaseDC(g_0016, g_13dc);
    g_13dc = 0;
    if (g_0012) {
        DeleteObject(g_0012);
        g_0012 = 0;
    }
    if (g_13de) {
        g_13de = 0;
        g_90f4 = g_968e;
        if (fn_02_1ac8())
            fn_02_1b96();
    }
}

/* Measures the main window's client area (clipped to the screen) into
 * g_90ea x g_0010, sets the clip region g_0012, seeds rand and runs
 * fn_10_0000 with the window DC in g_13dc. */
/* @addr 2:1ac8 */
int far fn_02_1ac8(void)
{
    int r;
    RECT rc;

    g_13dc = GetDC(g_0016);
    GetClientRect(g_0016, &rc);
    g_90ea = rc.right < GetSystemMetrics(SM_CXSCREEN) ? rc.right : GetSystemMetrics(SM_CXSCREEN);
    g_0010 = rc.bottom < GetSystemMetrics(SM_CYSCREEN) ? rc.bottom : GetSystemMetrics(SM_CYSCREEN);
    g_90ec = g_0010 - g_0a70;
    g_8e58 = 0;
    g_8e5a = g_0010 - 0x55;
    if (g_0012) {
        DeleteObject(g_0012);
        g_0012 = 0;
    }
    g_0012 = CreateRectRgn(0, 0, g_90ea, g_90ec);
    srand(GetCurrentTime());
    r = fn_10_0000();
    ReleaseDC(g_0016, g_13dc);
    g_13dc = 0;
    return r;
}

/* @addr 2:1b96 */
void far fn_02_1b96(void)
{
    int u;
    HPALETTE old;

    g_13dc = GetDC(g_0016);
    if (g_920e) {
        old = SelectPalette(g_13dc, g_920e, 0);
        RealizePalette(g_13dc);
    }
    if (g_90f4 == 1)
        fn_09_0c06();
    if (old)
        SelectPalette(g_13dc, old, 0);
    ReleaseDC(g_0016, g_13dc);
    g_13dc = 0;
}

/* @addr 2:0fc4 */
void far fn_02_0fc4(void)
{
    long style;

    g_0020 = 1;
    style = GetWindowLong(g_0016, GWL_STYLE);
    style &= ~WS_OVERLAPPEDWINDOW;
    SetWindowLong(g_0016, GWL_STYLE, style);
    MoveWindow(g_0016, 0, 0, GetSystemMetrics(SM_CXSCREEN),
               GetSystemMetrics(SM_CYSCREEN), TRUE);
    if (fn_06_1290("OnTop", 1))
        SetWindowPos(g_0016, (HWND)-1, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

/* @addr 2:190a */
void far fn_02_190a(DWORD ctx)
{
    char path[130];
    int cmd;

    if (ctx == 0)
        cmd = HELP_INDEX;
    else
        cmd = HELP_CONTEXT;
    lstrcpy(path, g_8f7a);
    GetPrivateProfileString(g_9690, "Language", "", g_8e68, 5, g_96a9);
    lstrcat(path, g_8e68);
    lstrcat(path, "_HELP.HLP");
    WinHelp(g_0016, path, cmd, ctx);
}

/* @addr 2:088e */
void far fn_02_088e(void)
{
    int x;
    char buf[80];

    if (g_0a7c && !g_9460) {
        x = g_90ea - 80;
        x = x < 640 ? 640 : x;
        x = x > 760 ? 760 : x;
        g_1dc8 = x + g_1dc4;
        g_1dca = GetSystemMetrics(SM_CYCAPTION) + g_1dc6 + 345;
        fn_10_7480(-2);
        LoadString(g_9212, 0x886, buf, 80);
        CreateWindow("IS_HELP", buf, WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
                     g_1dc4, g_1dc6, x, GetSystemMetrics(SM_CYCAPTION) + 345,
                     g_0016, 0, g_8e66, NULL);
        SetWindowPos(g_9460, (HWND)-1, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }
}

/* @addr 2:1994 */
void far fn_02_1994(void)
{
    char path[120];
    OFSTRUCT of;

    if (!g_0024) {
        GetWindowsDirectory(path, 110);
        lstrcat(path, "\\CTL3D.DLL");
        if (OpenFile(path, &of, OF_EXIST) != HFILE_ERROR) {
            g_0024 = LoadLibrary(path);
            if (g_0024) {
                g_1d4c = GetProcAddress(g_0024, g_0078);
                g_1d50 = GetProcAddress(g_0024, g_007a);
                g_1d54 = GetProcAddress(g_0024, g_007c);
                g_fp_1d58 = (int (far pascal *)(int))GetProcAddress(g_0024, g_007e);
                g_fp_1d5c = (void (far pascal *)(int, int, long))GetProcAddress(g_0024, g_0080);
            }
        }
    }
}

/* Sets the play-view rectangle g_1d30 and its clip region g_0012; g_1d28
 * is a status strip [inferred]. */
/* @addr 2:0ca4 */
void far fn_02_0ca4(void)
{
    int t;
    int l;
    int b;
    int u;

    if (g_0a78) {
        u = (0x3a - g_90ea % 0x3a) / 2;
        l = 0x4e - u;
        t = 0x4e;
        g_1d28.left = l;
        g_1d28.right = g_90ea - l * 2;
        g_1d28.top = g_90ec - 0x28;
        g_1d28.bottom = b = 20;
    } else {
        b = l = t = 0;
        g_1d28.left = 0;
        g_1d28.right = g_90ea;
        g_1d28.top = g_0010 - 0x69;
        g_1d28.bottom = 20;
    }
    if (g_9134)
        b += 20;
    if (g_0012) {
        DeleteObject(g_0012);
        g_0012 = 0;
    }
    SetRect(&g_1d30, l, t, g_90ea - l, g_90ec - b);
    g_0012 = CreateRectRgn(g_1d30.left, g_1d30.top, g_1d30.right, g_1d30.bottom);
}

/* Re-measures the main window after a resize [inferred], clears the
 * play area and the bottom strip, and repaints. */
/* @addr 2:0ba4 */
void far fn_02_0ba4(void)
{
    RECT rc;

    g_1038 = 0;
    GetClientRect(g_0016, &rc);
    g_90ea = rc.right < GetSystemMetrics(SM_CXSCREEN) ? rc.right : GetSystemMetrics(SM_CXSCREEN);
    g_0010 = rc.bottom < GetSystemMetrics(SM_CYSCREEN) ? rc.bottom : GetSystemMetrics(SM_CYSCREEN);
    g_0a70 = 0x55;
    g_90ec = g_0010 - 0x55;
    PatBlt(g_13dc, g_1e30[g_9646].x - 20, g_1e30[g_9646].y - 20,
           g_1e30[g_9646].f22 + 40, g_1e30[g_9646].f22 + 40, BLACKNESS);
    fn_07_11cc();
    fn_07_1208();
    g_8e58 = 0;
    g_8e5a = g_0010 - 0x55;
    fn_02_0ca4();
    if (g_0a78)
        PatBlt(g_13dc, g_1d28.left, g_1d28.top, g_1d28.right, g_1d28.bottom, BLACKNESS);
    else
        PatBlt(g_13dc, 0, 0, g_90ea, g_90ec, BLACKNESS);
    PostMessage(g_0016, WM_PAINT, 0, 0L);
}
