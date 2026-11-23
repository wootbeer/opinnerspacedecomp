/* INSPACE.EXE segment 2 (selector 1008), 2:0000-1ac8 (one source file;
 * 2:1ac8-end is seg02b.c). */
#include "game.h"

/* The program's entry point (called by the C runtime start-up): sets up,
 * then runs the message loop; while the game runs (g_8f68, an inactive
 * modeless dialog g_0d1e, or g_9460) it polls with PeekMessage and calls
 * fn_02_1c08 when idle. Centres the cursor horizontally only, at the
 * bottom edge [sic]; passes an uninitialised 26-byte block to
 * fn_06_12b6 [sic]. */
/* 2:0000 */
int16_t WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int16_t show)
{
    WNDCLASS s;
    MSG msg;
    int16_t handled;
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
    fn_06_1c0c();
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
                fn_06_0f1a(main_ship, buf);
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
        if (GetActiveWindow() == (uint16_t)g_0016)
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

/* 2:094c */
int16_t fn_02_094c(UINT id)
{
    return LoadString(g_9212, id, g_8e68, 249);
}

/* 2:1a5a */
int16_t fn_02_1a5a(int16_t a, int16_t b, int32_t c)
{
    return g_fp_1d5c(a, b, c);
}

/* 2:1a7a */
int16_t fn_02_1a7a(int16_t a)
{
    if (g_0024)
        return g_fp_1d58(a);
    return 0;
}

/* 2:1a9e */
void fn_02_1a9e(void)
{
    int16_t r;

    if (g_0024) {
        FreeLibrary(g_0024);
        g_0024 = 0;
    }
}

/* 2:11c0 */
void fn_02_11c0(void)
{
    if (!IsIconic(g_0016)) {
        if (!g_0020)
            GetWindowRect(g_0016, &g_1d20);
        g_8f6a = 1;
    }
}

/* 2:084c */
void fn_02_084c(int16_t id)
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

/* 2:09c4 */
void fn_02_09c4(void)
{
    char buf[80];

    g_0592 = 2;
    g_8f68 = 0;
    LoadString(g_9212, 0x7fc, buf, 80);
    SetWindowText(g_0016, buf);
}

/* 2:18b8 */
int16_t fn_02_18b8(int16_t a)
{
    int16_t v;
    int16_t r;

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

/* 2:0970 */
void fn_02_0970(void)
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

/* 2:134c */
void fn_02_134c(int16_t unused, POINT pt)
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

/* 2:16a2 */
void fn_02_16a2(void)
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
/* 2:170e */
void fn_02_170e(void)
{
    HMENU m;
    UINT fl;
    int16_t n;
    int16_t i;
    int16_t cnt;
    int16_t base;

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
        for (i = cnt = 0; i < g_9406[2]; i++)
            if (g_52ec[i].f_18.a == 14 && g_52ec[i].f_18.b == main_ship) {
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

/* 2:0a06 */
void fn_02_0a06(void)
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

/* 2:0fc4 */
void fn_02_0fc4(void)
{
    int32_t style;

    g_0020 = 1;
    style = GetWindowLong(g_0016, GWL_STYLE);
    style &= ~WS_OVERLAPPEDWINDOW;
    SetWindowLong(g_0016, GWL_STYLE, style);
    MoveWindow(g_0016, 0, 0, GetSystemMetrics(SM_CXSCREEN),
               GetSystemMetrics(SM_CYSCREEN), TRUE);
    if (fn_06_1290("OnTop", 1))
        SetWindowPos(g_0016, (HWND)-1, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

/* 2:190a */
void fn_02_190a(DWORD ctx)
{
    char path[130];
    int16_t cmd;

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

/* 2:088e */
void fn_02_088e(void)
{
    int16_t x;
    char buf[80];

    if (g_0a7c && !g_9460) {
        x = LO16(g_90ea) - 80;
        x = x < 640 ? 640 : x;
        x = x > 760 ? 760 : x;
        g_1dc8 = x + g_1dc4;
        g_1dca = GetSystemMetrics(SM_CYCAPTION) + g_1dc6 + 345;
        fn_10_7480(-2, 0);
        LoadString(g_9212, 0x886, buf, 80);
        CreateWindow("IS_HELP", buf, WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
                     g_1dc4, g_1dc6, x, GetSystemMetrics(SM_CYCAPTION) + 345,
                     g_0016, 0, g_8e66, NULL);
        SetWindowPos(g_9460, (HWND)-1, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    }
}

/* 2:1994 */
void fn_02_1994(void)
{
    char path[120];
    OFSTRUCT of;

    if (!g_0024) {
        GetWindowsDirectory(path, 110);
        lstrcat(path, "\\CTL3D.DLL");
        if (OpenFile(path, &of, OF_EXIST) != HFILE_ERROR) {
            g_0024 = LoadLibrary(path);
            if (g_0024) {
                g_1d4c = (void (*)(HINSTANCE))GetProcAddress(g_0024, g_0078);
                g_1d50 = (void (*)(HINSTANCE))GetProcAddress(g_0024, g_007a);
                g_1d54 = (void (*)(HINSTANCE))GetProcAddress(g_0024, g_007c);
                g_fp_1d58 = (int16_t (*)(int16_t))GetProcAddress(g_0024, g_007e);
                g_fp_1d5c = (int16_t (*)(int16_t, int16_t, int32_t))GetProcAddress(g_0024, g_0080);
            }
        }
    }
}

/* Sets the play-view rectangle g_1d30 and its clip region g_0012; g_1d28
 * is a status strip [inferred]. */
/* 2:0ca4 */
void fn_02_0ca4(void)
{
    int16_t t;
    int16_t l;
    int16_t b;
    int16_t u;

    if (g_0a78) {
        u = (0x3a - LO16(g_90ea) % 0x3a) / 2;
        l = 0x4e - u;
        t = 0x4e;
        g_1d28.left = l;
        g_1d28.right = LO16(g_90ea) - l * 2;
        g_1d28.top = HI16(g_90ea) - 0x28;
        g_1d28.bottom = b = 20;
    } else {
        b = l = t = 0;
        g_1d28.left = 0;
        g_1d28.right = LO16(g_90ea);
        g_1d28.top = g_0010 - 0x69;
        g_1d28.bottom = 20;
    }
    if (g_9134)
        b += 20;
    if (g_0012) {
        DeleteObject(g_0012);
        g_0012 = 0;
    }
    SetRect(&g_1d30, l, t, LO16(g_90ea) - l, HI16(g_90ea) - b);
    g_0012 = CreateRectRgn(g_1d30.left, g_1d30.top, g_1d30.right, g_1d30.bottom);
}

/* Re-measures the main window after a resize [inferred], clears the
 * play area and the bottom strip, and repaints. */
/* 2:0ba4 */
void fn_02_0ba4(void)
{
    RECT rc;

    g_1038 = 0;
    GetClientRect(g_0016, &rc);
    LO16(g_90ea) = rc.right < GetSystemMetrics(SM_CXSCREEN) ? rc.right : GetSystemMetrics(SM_CXSCREEN);
    g_0010 = rc.bottom < GetSystemMetrics(SM_CYSCREEN) ? rc.bottom : GetSystemMetrics(SM_CYSCREEN);
    g_0a70 = 0x55;
    HI16(g_90ea) = g_0010 - 0x55;
    PatBlt(g_13dc, g_1df8[14][main_ship].f_00.x - 20, g_1df8[14][main_ship].f_00.y - 20,
           g_1df8[14][main_ship].f_22 + 40, g_1df8[14][main_ship].f_22 + 40, BLACKNESS);
    fn_07_11cc();
    fn_07_1208();
    g_8e58 = 0;
    g_8e5a = g_0010 - 0x55;
    fn_02_0ca4();
    if (g_0a78)
        PatBlt(g_13dc, g_1d28.left, g_1d28.top, g_1d28.right, g_1d28.bottom, BLACKNESS);
    else
        PatBlt(g_13dc, 0, 0, LO16(g_90ea), HI16(g_90ea), BLACKNESS);
    PostMessage(g_0016, WM_PAINT, 0, 0L);
}

/* Timer tick [inferred]: handles a pending g_001c request, wiggles the
 * mouse in attract mode every 20 s, and follows activation changes. */
/* 2:11f8 */
void fn_02_11f8(void)
{
    int16_t u1;
    int16_t u2;
    int16_t u3;
    HWND act;
    HTASK task;
    int16_t u4;

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
        if (act != (uint16_t)g_0016 && act != g_934c && act != g_0d1e) {
            if (g_8f68)
                fn_02_09c4();
        } else if (!g_8f68 && !IsIconic(g_0016))
            fn_02_0a06();
    }
}

/* Click at (x, y) on the bottom panel [inferred]: three buttons set
 * g_93c6 (6, 2, 5) and call fn_02_088e; else, with g_001e set, restores
 * the normal window frame or calls fn_02_0fc4. */
/* 2:1046 */
void fn_02_1046(int16_t x, int16_t y)
{
    LONG style;
    POINT pt;
    RECT rc;

    pt.x = x;
    pt.y = y;
    SetRect(&rc, LO16(g_90ea) / 2 - 43, g_8e5a + 7, LO16(g_90ea) / 2 + 43, g_0010 - 3);
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

/* Sizes the play area to the window (or, maximised without a full-screen
 * window, to the screen) [inferred]. */
/* 2:0a74 */
void fn_02_0a74(UINT type, LPARAM lp)
{
    int16_t u1;
    int16_t u2;
    int16_t h;
    int16_t w;
    int16_t u3;
    int16_t u4;
    RECT r;

    if (IsIconic(g_0016))
        return;
    GetWindowRect(g_0016, &r);
    w = r.right - r.left;
    h = r.bottom - r.top;
    if (g_0020 && (r.left != 0 || r.top != 0 || GetSystemMetrics(SM_CXSCREEN) != w
                   || GetSystemMetrics(SM_CYSCREEN) != h)) {
        MoveWindow(g_0016, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 1);
    } else {
        LO16(g_90ea) = (uint16_t)GetSystemMetrics(SM_CXSCREEN) < LOWORD(lp) ? GetSystemMetrics(SM_CXSCREEN) : LOWORD(lp);
        g_0010 = HI16(g_90ea) = (uint16_t)GetSystemMetrics(SM_CYSCREEN) < HIWORD(lp) ? GetSystemMetrics(SM_CYSCREEN) : HIWORD(lp);
        HI16(g_90ea) -= g_0a70;
    }
    g_8e58 = 0;
    g_8e5a = g_0010 - 0x55;
    fn_02_0ca4();
    g_8f76 = g_8f78;
    if (g_001e)
        g_8f64 = 1;
    if (!g_0020) {
        g_8f6a = 1;
        GetWindowRect(g_0016, &g_1d20);
    }
    if (subgame_active && g_90f4 == 1)
        fn_18_270e(LO16(g_90ea), g_0010);
}

/* WM_SYSCOMMAND handler [inferred]: 0x60 toggles the menu bar (system menu
 * item), 0xc0 posts a command, SC_CLOSE asks to quit (fn_10_82a2(5)).
 * Returns 0 when handled, 1 to pass it on; the 0x60 case returns no value
 * [sic]. */
/* 2:0d78 */
int16_t fn_02_0d78(UINT wParam)
{
    int16_t u1;
    int16_t u2;
    DWORD t;
    UINT cmd;
    char buf[80];
    int16_t r;
    int16_t u3;
    HMENU hm;

    switch (cmd = wParam & 0xfff0) {
    case SC_CLOSE:
        fn_10_744c(0x6e);
        fn_10_744c(rand() % 3 + 11);
        t = GetCurrentTime() + 450;
        do
            ;
        while (GetCurrentTime() < t);
        fn_10_754a(0x50, 0, 0, 0);
        g_001a = 1;
        r = fn_10_82a2(5);
        if (r) {
            if (r == 1) {
                if (g_920c == 0 || g_920c == 1) {
                    g_90f4 = 9;
                    fn_10_82a2(12);
                }
                fn_10_87de();
                DestroyWindow(g_0016);
            }
            if (r == 0x251) {
                if (g_90f4 == 2)
                    fn_10_8568(-1);
                else
                    fn_10_8568(1);
            }
        } else
            g_001a = 0;
        return 0;
    case SC_MINIMIZE:
        fn_02_09c4();
    default:
        return 1;
    case SC_MAXIMIZE:
        if (g_001e)
            fn_02_0fc4();
        return 1;
    case SC_RESTORE:
        MoveWindow(g_0016, g_1d20.left, g_1d20.top, g_1d20.right - g_1d20.left,
                   g_1d20.bottom - g_1d20.top, g_8f68 = 1);
        if (!g_0014) {
            g_0014 = GetSystemMenu(g_0016, 0);
            AppendMenu(g_0014, MF_SEPARATOR, 0, 0L);
            LoadString(g_9212, 0x888, buf, 80);
            AppendMenu(g_0014, 0, 0x60, buf);
            if (g_90f6)
                CheckMenuItem(g_0014, 0x60, MF_CHECKED);
            DrawMenuBar(g_0016);
        }
        if (g_0020)
            fn_02_0fc4();
        if (g_8f66) {
            LoadString(g_9212, 0x921, buf, 80);
            SetWindowText(g_0016, buf);
        }
        return 1;
    case 0x60:
        hm = GetSystemMenu(g_0016, 0);
        if (g_90f6 = !g_90f6) {
            SetWindowWord(g_0016, GWW_ID, g_90fa);
            CheckMenuItem(hm, 0x60, MF_CHECKED);
        } else {
            SetWindowWord(g_0016, GWW_ID, 0);
            CheckMenuItem(hm, 0x60, MF_UNCHECKED);
        }
        DrawMenuBar(g_0016);
        break;
    case 0xc0:
        PostMessage(g_0016, WM_COMMAND, 0xc0, 0L);
        return 0;
    }
}

/* WM_COMMAND handler [inferred]: menu and accelerator ids are mostly
 * re-posted as key messages (WM_KEYUP 0x101, or the game's 0x99b/0x99e). */
/* 2:13b2 */
void fn_02_13b2(UINT id, LPARAM lParam)
{
    char buf[120];
    int32_t l;

    switch (id) {
    case 0x74:
    case 0x1eb:
        PostMessage(g_0016, 0x99b, 0x49, 0L);
        break;
    case 0x191:
        PostMessage(g_0016, 0x99b, 0x6b, 0L);
        break;
    case 0x19b:
        PostMessage(g_0016, 0x99b, 0x6d, 0L);
        break;
    case 0x75:
        PostMessage(g_0016, WM_KEYUP, 0x57, 0L);
        break;
    case 0x76:
    case 0x1d7:
        PostMessage(g_0016, 0x99b, 0x52, 0L);
        break;
    case 0x1b9:
        PostMessage(g_0016, 0x99b, 0x41, 0L);
        break;
    case 0x1c3:
        PostMessage(g_0016, 0x99b, 0x48, 0L);
        break;
    case 0x1cd:
        PostMessage(g_0016, 0x99b, 0x45, 0L);
        break;
    case 0x1e1:
        PostMessage(g_0016, 0x99b, 0x57, 0L);
        break;
    case 0x7c:
        PostMessage(g_0016, 0x99e, 0x51, 0L);
        break;
    case 0x7d:
        PostMessage(g_0016, 0x99e, 0x41, 0L);
        break;
    case 0x7e:
        PostMessage(g_0016, 0x99e, 0x44, 0L);
        break;
    case 0x7f:
        PostMessage(g_0016, 0x99e, 0x47, 0L);
        break;
    case 0x80:
        PostMessage(g_0016, 0x99e, 0x53, 0L);
        break;
    case 0x81:
        PostMessage(g_0016, 0x99e, 0x45, 0L);
        break;
    case 0x82:
        PostMessage(g_0016, 0x99e, 0x48, 0L);
        break;
    case 0x73:
        PostMessage(g_0016, 0x99e, 0x46, 0L);
        break;
    case 0x19c:
        if (g_0020) {
            l = GetWindowLong(g_0016, GWL_STYLE);
            SetWindowLong(g_0016, GWL_STYLE, l |= WS_OVERLAPPEDWINDOW);
        }
        PostMessage(g_0016, WM_SYSCOMMAND, SC_MINIMIZE, 0L);
        break;
    case 0xe0:
        PostMessage(g_0016, 0x8e2, 0, 0L);
        break;
    case 0x68:
    case 0xc0:
        fn_10_7f18();
        break;
    case 0x67:
        PostMessage(g_0016, WM_KEYUP, 0x1b, 0L);
        break;
    case 0x69:
        PostMessage(g_0016, WM_KEYUP, 0x7b, 0L);
        break;
    case 0x6a:
    case 0xb0:
        PostMessage(g_0016, WM_SYSCOMMAND, SC_CLOSE, 0L);
        break;
    case 0x6b:
    case 0x1a6:
        if (g_90f4 == 1)
            fn_10_8568(2);
        else if (g_90f4 == 2)
            fn_10_8568(0);
        break;
    case 0x6c:
        PostMessage(g_0016, WM_KEYUP, 0x51, 0L);
        break;
    case 0x6d:
        PostMessage(g_0016, WM_KEYUP, 0x41, 0L);
        break;
    case 0x6e:
        PostMessage(g_0016, WM_KEYUP, 0x44, 0L);
        break;
    case 0x6f:
        PostMessage(g_0016, WM_KEYUP, 0x47, 0L);
        break;
    case 0x70:
        PostMessage(g_0016, WM_KEYUP, 0x53, 0L);
        break;
    case 0x71:
        PostMessage(g_0016, WM_KEYUP, 0x45, 0L);
        break;
    case 0xf0:
        if (g_0a7c) {
            g_93c6 = 4;
            fn_02_088e();
        } else
            fn_02_190a(0L);
        break;
    case 0xca:
    case 0x100:
        fn_02_190a(0L);
        break;
    case 0xc9:
        fn_02_190a(0x1cL);
        break;
    case 0xcb:
        fn_02_190a(5L);
        break;
    case 0x77:
        g_93c6 = 4;
        fn_02_088e();
        break;
    case 0x78:
        g_93c6 = 5;
        fn_02_088e();
        break;
    case 0x79:
        g_93c6 = 6;
        fn_02_088e();
        break;
    case 0x7a:
        g_93c6 = 1;
        fn_02_088e();
        break;
    case 0x7b:
        g_93c6 = 0;
        fn_02_088e();
        break;
    }
}

/* The main window procedure [inferred]. With g_90f4 == 1 it traces every
 * message to the debugger ("WndProc iMainSmart = "). */
/* 2:0224 */
LONG fn_02_0224(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int16_t r;
    MINMAXINFO *mm;
    HPALETTE old;
    char buf[30];
    int16_t flag;

    if (g_90f4 == 1) {
        fn_13_4eca("WndProc iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca(": Message is ");
        fn_06_0f1a(msg, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
    }
    switch (msg) {
    case WM_CREATE:
        g_0016 = hwnd;
        fn_06_18e0();
        g_001c = 1;
        break;
    case WM_GETMINMAXINFO:
        mm = (MINMAXINFO *)lParam;
        if (g_0022) {
            mm->ptMinTrackSize.x = 600;
            mm->ptMinTrackSize.y = 400;
        } else {
            RECT rc;

            GetWindowRect(g_0016, &rc);
            mm->ptMinTrackSize.x = mm->ptMaxTrackSize.x = rc.right - rc.left;
            mm->ptMinTrackSize.y = mm->ptMaxTrackSize.y = rc.bottom - rc.top;
        }
        break;
    case WM_SIZE:
        fn_02_0a74(wParam, lParam);
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case 0x9cf:
        fn_10_6e26();
        g_13dc = GetDC(g_0016);
        fn_10_6e00();
        old = SelectPalette(g_13dc, g_920e, 0);
        fn_10_6e76(0x20008L);
        SelectPalette(g_13dc, old, 0);
        ReleaseDC(g_0016, g_13dc);
        PostMessage(g_0016, 0x9d0, g_13dc = 0, 0L);   /* g_13dc is an HDC */
        break;
    case 0x9d0:
        g_8f66 = 1;
        fn_06_1b3c();
        break;
    case 0xa04:
        fn_10_7480(wParam, 0);
        break;
    case 0x9f0:
    case 0x9fa:
        fn_02_084c(msg);
        break;
    case 0x9a0:
        fn_13_5878();
        break;
    case 0x9a5:
        fn_02_16a2();
        break;
    case 0x9aa:
        if (g_9458) {
            g_8f72 = 0;
            fn_07_63f2();
        } else {
            g_8f72 = 1;
            fn_07_641a();
        }
        break;
    case 0x9b4:
        if (g_95fe) {
            g_8f74 = 0;
            fn_13_6362();
        } else {
            g_8f74 = 1;
            fn_13_638a();
        }
        break;
    case 0x991:
        fn_10_744c(0x6e);
        fn_10_744c(0x13);
        r = fn_10_82a2(7);
        if (r) {
            if (r == 0x251)
                fn_10_8568(3);
            g_8f6c = 1;
        }
        break;
    case WM_PALETTECHANGED:
        if (g_920e && wParam != hwnd) {
            HDC hdc;
            HPALETTE op;

            hdc = GetDC(hwnd);
            op = SelectPalette(hdc, g_920e, 0);
            RealizePalette(hdc);
            UpdateColors(hdc);
            if (op)
                SelectPalette(hdc, op, 0);
            ReleaseDC(hwnd, hdc);
            hdc = 0;
        }
        break;
    case WM_QUERYNEWPALETTE:
        if (g_920e) {
            HDC hdc;
            HPALETTE op;

            hdc = GetDC(hwnd);
            op = SelectPalette(hdc, g_920e, 0);
            RealizePalette(hdc);
            InvalidateRect(hwnd, NULL, 1);
            UpdateWindow(hwnd);
            if (op)
                SelectPalette(hdc, op, 0);
            ReleaseDC(hwnd, hdc);
            hdc = 0;
            return 1L;
        }
        break;
    case WM_SYSCOMMAND:
        if (fn_02_0d78(wParam))
            return DefWindowProc(hwnd, msg, wParam, lParam);
        break;
    case WM_COMMAND:
        if (g_1212)
            fn_02_13b2(wParam, lParam);
        break;
    case WM_LBUTTONDBLCLK:
        if (g_1212 && g_0022)
            fn_02_1046(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_LBUTTONDOWN:
        fn_16_638a(wParam, lParam, 0);
        break;
    case WM_RBUTTONDOWN:
        if (g_1212)
            fn_02_134c(g_0016, MAKEPOINT(lParam));
        break;
    case WM_VSCROLL:
        fn_11_7798(wParam, lParam);
        break;
    case WM_MOUSEMOVE:
        flag = 0;
        if (g_8e5e) {
            int16_t dx;
            int16_t dy;

            dx = fn_09_88ba(g_1d48 - LOWORD(lParam));
            dy = fn_09_88ba(g_1d4a - HIWORD(lParam));
            if (dx > 6 || (dy > 6 && dx > 2))
                flag = 1;
            if (g_0d24)
                flag = 0;
        }
        if (!flag)
            return DefWindowProc(hwnd, msg, wParam, lParam);
    case WM_KEYDOWN:
    case WM_KEYUP:
    case 0x3a0:
    case 0x3b5:
    case 0x3b7:
    case 0x99b:
    case 0x99e:
    case 0x9c5:
        if (g_90f8 && g_8e5e) {
            if (GetCurrentTime() > g_1d3c + 4000)
                DestroyWindow(g_0016);
            break;
        }
        if (!g_1212 || !g_8f68 || g_3b94 > g_1e50)
            break;
        if (g_968c) {    /* not volatile here */
            fn_11_6aa8(g_8e62 = msg, wParam, lParam);
            break;
        }
        g_8e60 = 1;
        g_8e62 = msg;
        g_8e64 = wParam;
        g_1d38 = lParam;
        fn_02_1c08();
        break;
    case 0x978:
        fn_02_0970();
        break;
    case WM_PAINT:
        if (g_001e) {
            if (g_90f4 == 1 || g_90f4 == 7)
                fn_02_0970();
            else
                PostMessage(g_0016, 0x978, 0, 0L);
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case 0x914:
        ShowWindow(g_0016, SW_SHOWNORMAL);
        SetActiveWindow(g_0016);
        break;
    case WM_SETFOCUS:
        if (IsIconic(g_0016) == 0 && g_8f68 == 0)
            fn_02_0a06();
        break;
    case WM_TIMER:
        fn_02_11f8();
        break;
    case WM_MOVE:
        fn_02_11c0();
        return 0L;
    case WM_ENDSESSION:
        if (wParam)
            fn_06_19bc();
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case WM_DESTROY:
        fn_06_19bc();
        PostQuitMessage(0);
        break;
    }
    if (g_90f4 == 1) {
        fn_13_4eca("WndProc 2 iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
    }
    return 0L;
}
