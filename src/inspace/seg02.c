/* INSPACE.EXE segment 2 (selector 1008), 2:0000-1ac8 (one source file;
 * 2:1ac8-end is seg02b.c). */
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
int far fn_02_18b8(int a);
extern int g_95fa;
extern int g_91fc;
extern int g_940a;
typedef struct {
    char p00[0x10];
    int f10;            /* +0x10 */
    int f12;            /* +0x12 */
    char rest[0x24 - 0x14];
} REC_24;
extern REC_24 g_52f4[];
void far fn_10_744c(int a);
extern int g_93c6;
extern int g_93c0;
extern int g_93ba;
void far fn_13_4eca(LPSTR s);
void far fn_06_0f1a(int n, char far *buf);
void far fn_17_60d8(void);
void far fn_07_0000(void);
void far fn_10_8686(void);
void far fn_10_86a8(void);
extern volatile int g_968c;
extern int g_001c;
extern int g_001e;
extern int g_8f6e;
extern DWORD g_1d44;
extern DWORD g_1d3c;
extern int g_8f62;
extern int g_1d48;
extern int g_1d4a;
extern HWND g_934c;
extern HWND g_0d1e;
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
typedef struct { char b[26]; } BLOCK26;
int far pascal fn_06_12b6(HINSTANCE a, HINSTANCE b, BLOCK26 s);
int far fn_06_1c0c(int a);
void far fn_10_6b70(int a);
void far fn_11_3fd4(LPSTR s, int a);
extern int g_0018;
extern char g_1d60[];
void far fn_02_1994(void);
void far fn_02_1a9e(void);
void far fn_02_1c08(void);

/* The program's entry point (called by the C runtime start-up): sets up,
 * then runs the message loop; while the game runs (g_8f68, an inactive
 * modeless dialog g_0d1e, or g_9460) it polls with PeekMessage and calls
 * fn_02_1c08 when idle. Centres the cursor horizontally only, at the
 * bottom edge [sic]; passes an uninitialised 26-byte block to
 * fn_06_12b6 [sic]. */
/* @addr 2:0000 */
int pascal WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int show)
{
    BLOCK26 s;
    MSG msg;
    int handled;
    HACCEL acc;
    char buf[20];

    lstrcpy(g_9690, "Inner Space");
    lstrcpy(g_1d60, cmd);
    fn_11_3fd4(g_1d60, 1);
    SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN));
    GetCursorPos(&g_1d48);
    if (!fn_06_12b6(hInst, hPrev, s)) {
        fn_10_6b70(0);
        return 0;
    }
    fn_02_1994();
    if (g_0024) {
        g_1d4c(g_8e66);
        g_1d50(g_8e66);
    }
    fn_06_1c0c(1);
    g_1d3c = GetCurrentTime();
    acc = LoadAccelerators(g_9212, "MainAccel");
    handled = 0;
    while (g_0018) {
        if (g_8f68 || (g_0d1e && !flow_interactive) || g_9460) {
            g_0018 = 1;
            if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
                if (msg.message != WM_QUIT)
                    goto dispatch;
                break;
            }
            if (g_90f4 == 1) {
                fn_13_4eca("GMAIN iMainSmart = ");
                fn_06_0f1a(g_9646, buf);
                fn_13_4eca(buf);
                fn_13_4eca("\n\r");
            }
            if (g_8f66 && (g_8f68 || (g_0d1e && !flow_interactive) || g_9460))
                fn_02_1c08();
            continue;
        } else {
            g_0018 = GetMessage(&msg, 0, 0, 0);
        }
dispatch:
        handled = 0;
        if (GetActiveWindow() == g_0016)
            handled = TranslateAccelerator(g_0016, acc, &msg);
        if (!handled) {
            if (g_9460 && IsDialogMessage(g_9460, &msg))
                continue;
            if (g_0d1e && IsDialogMessage(g_0d1e, &msg))
                continue;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    if (g_0024)
        g_1d54(g_8e66);
    fn_02_1a9e();
    return msg.wParam;
}

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

/* Enables or greys the menu items (flags from fn_02_18b8) to match the
 * game state; the menu bar has one more popup when g_9134 is set. */
/* @addr 2:170e */
void far fn_02_170e(void)
{
    HMENU m;
    UINT fl;
    int n;
    int i;
    int cnt;
    int base;

    if (g_90f6) {
        if (!g_9134)
            base = 0;
        else
            base = 1;
        fl = fn_02_18b8(g_95fa);
        m = GetSubMenu(g_90fa, base + 1);
        n = GetMenuItemCount(m);
        for (i = 0; i < n; i++)
            EnableMenuItem(m, i, fl);
        m = GetSubMenu(g_90fa, base + 3);
        EnableMenuItem(m, 1, fl);
        EnableMenuItem(m, 2, fl);
        for (i = cnt = 0; i < g_940a; i++)
            if (g_52f4[i].f10 == 14 && g_52f4[i].f12 == g_9646) {
                cnt++;
                break;
            }
        fl = fn_02_18b8(cnt);
        m = GetSubMenu(g_90fa, base + 2);
        n = GetMenuItemCount(m);
        for (i = 0; i < n; i++)
            EnableMenuItem(m, i, fl);
        fl = fn_02_18b8(g_91fc);
        EnableMenuItem(GetSubMenu(g_90fa, base + 3), 3, fl);
        fl = fn_02_18b8(1);
        m = GetSubMenu(g_90fa, 0);
        EnableMenuItem(m, 0, fl);
        EnableMenuItem(m, 3, fl);
        if (!flow_interactive) {
            m = GetSubMenu(g_90fa, base);
            n = GetMenuItemCount(m);
            for (i = 0; i < n; i++)
                EnableMenuItem(m, i, fl);
        }
    }
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

/* Timer tick [inferred]: handles a pending g_001c request, wiggles the
 * mouse in attract mode every 20 s, and follows activation changes. */
/* @addr 2:11f8 */
void far fn_02_11f8(void)
{
    int u1;
    int u2;
    int u3;
    HWND act;
    HTASK task;
    int u4;

    if (g_001c) {
        g_8f6a = g_001c = 0;
        if (g_8f6e)
            PostMessage(g_0016, 0x8e2, 0, 0L);
        PostMessage(g_0016, 0x914, 0, 0L);
        g_001e = 1;
        return;
    }
    if (!flow_interactive && GetCurrentTime() > g_1d44 + 20000 &&
        GetCurrentTime() > g_1d3c + 10000) {
        g_1d44 = GetCurrentTime();
        if (++g_8f62 > 2)
            g_8f62 = 0;
        SetCursorPos(g_1d48 + g_8f62 - 1, g_1d4a);
    }
    if (g_8f66) {
        act = GetActiveWindow();
        task = GetWindowTask(g_0016);
        if (GetWindowTask(act) != task) {
            if (g_8e5c)
                fn_10_8686();
        } else if (!g_8e5c && !IsIconic(g_0016))
            fn_10_86a8();
        if (act != g_0016 && act != g_934c && act != g_0d1e) {
            if (g_8f68)
                fn_02_09c4();
        } else if (!g_8f68 && !IsIconic(g_0016))
            fn_02_0a06();
    }
}

/* Click at (x, y) on the bottom panel [inferred]: three buttons set
 * g_93c6 (6, 2, 5) and call fn_02_088e; else, with g_001e set, restores
 * the normal window frame or calls fn_02_0fc4. */
/* @addr 2:1046 */
void far fn_02_1046(int x, int y)
{
    LONG style;
    POINT pt;
    RECT rc;

    pt.x = x;
    pt.y = y;
    SetRect(&rc, g_90ea / 2 - 43, g_8e5a + 7, g_90ea / 2 + 43, g_0010 - 3);
    if (g_0a7c && PtInRect(&rc, pt)) {
        fn_10_744c(0x6e);
        fn_10_744c(0x13);
        g_93c6 = 6;
        fn_02_088e();
        return;
    }
    SetRect(&rc, g_93c0, g_8e5a + 24, g_93c0 + 84, g_0010 - 2);
    if (g_0a7c && PtInRect(&rc, pt)) {
        g_93c6 = 2;
        fn_02_088e();
        return;
    }
    SetRect(&rc, 0, g_8e5a + 5, g_93ba - 1, g_0010 - 2);
    if (g_0a7c && PtInRect(&rc, pt)) {
        fn_10_744c(0x6e);
        fn_10_744c(0x13);
        g_93c6 = 5;
        fn_02_088e();
        return;
    }
    if (g_001e) {
        if (g_0020) {
            style = GetWindowLong(g_0016, GWL_STYLE);
            style |= WS_OVERLAPPEDWINDOW;
            SetWindowLong(g_0016, GWL_STYLE, style);
            SetWindowPos(g_0016, (HWND)-2, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
            PostMessage(g_0016, WM_SYSCOMMAND, SC_RESTORE, 0L);
            g_0020 = 0;
        } else
            fn_02_0fc4();
    }
}
