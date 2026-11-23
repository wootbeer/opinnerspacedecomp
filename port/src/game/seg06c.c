/* INSPACE.EXE segment 6 (selector 1028): 6:12b6-6:1c72, one source file. */
#include "game.h"

/* Program initialisation: single-instance check, timers, window classes,
 * display capabilities. wc is a by-value parameter used as a local; WinMain
 * passes an uninitialised block [sic]. */
/* 6:12b6 */
int16_t fn_06_12b6(HINSTANCE hInst, HINSTANCE hPrev, WNDCLASS wc)
{
    int16_t i;
    int16_t bits;
    int16_t planes;
    int16_t res;
    HDC dc;
    TIMECAPS tc;
    char exe[120];
    char ver[80];
    char text[140];
    char title[30];

    if (hPrev) {
        GetInstanceData(hPrev, (BYTE *)&g_0016, 2);
        if (IsWindow(g_0016)) {
            fn_06_1c0c(0);
            PostMessage(g_0016, WM_SYSCOMMAND, SC_MAXIMIZE, 0L);
        } else
            MessageBox(g_90fc, "Another version of game already running.", g_9690, MB_ICONEXCLAMATION);
        return 0;
    }
    GetModuleFileName(hInst, exe, 99);
    if (exe[0] < 123 && exe[0] > 96)
        exe[0] -= 32;
    g_912e = 0;
    if (timeGetDevCaps(&tc, 4) == 0 && tc.wPeriodMin < 3)
        g_912e = 1;
    for (i = 40; i >= 8 && !SetMessageQueue(i); i--)
        ;
    if (i < 16) {
        MessageBox(g_90fc, "Insufficient memory to run game!", g_9690, MB_ICONEXCLAMATION);
        return 0;
    }
    if (!SetTimer(g_90fc, 1, 1000, NULL)) {
        MessageBox(g_90fc, "All timers used. Can't run game.", g_9690, MB_ICONEXCLAMATION);
        return 0;
    }
    KillTimer(g_0016, 1);
    g_8e66 = hInst;
    if (!fn_06_06d8(exe))
        return 0;
    if (!fn_10_6656()) {
        fn_10_6b70(1);
        return 0;
    }
    if (fn_10_885e(1) == -10)
        return 0;
    g_9132 = GetPrivateProfileInt(g_9690, "IgnoreRes", 0, g_96a9);
    if ((res = GetFreeSystemResources(GFSR_GDIRESOURCES)) < 30) {
        fn_10_a332(text, 0xbe2, 0, res);
        fn_10_a332(title, 0x9ed, 0);
        if ((i = MessageBox(g_0016, text, title, MB_YESNO | MB_ICONEXCLAMATION)) == IDYES)
            return 0;
    }
    if (!fn_06_1b62())
        return 0;
    fn_06_0000();

    wc.style = 0x300b;
    wc.lpfnWndProc = fn_02_0224;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(hInst, "GAME");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_9690;
    if (!RegisterClass(&wc))
        return 0;

    wc.style = 3;
    wc.lpfnWndProc = fn_13_4f4e;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(hInst, "GAME");
    wc.hCursor = 0;
    wc.hbrBackground = GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "IS_WATCH";
    if (!RegisterClass(&wc))
        return 0;

    wc.style = 3;
    wc.lpfnWndProc = fn_07_6184;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(hInst, "GAME");
    wc.hCursor = 0;
    wc.hbrBackground = GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "IS_ICON";
    if (!RegisterClass(&wc))
        return 0;

    wc.style = 3;
    wc.lpfnWndProc = fn_13_613a;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(hInst, "GAME");
    wc.hCursor = 0;
    wc.hbrBackground = GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "IS_SMART";
    if (!RegisterClass(&wc))
        return 0;

    wc.style = 0xb;
    wc.lpfnWndProc = fn_06_1f22;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(hInst, "GAME");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(LTGRAY_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "IS_NAV";
    if (!RegisterClass(&wc))
        return 0;

    wc.style = 3;
    wc.lpfnWndProc = fn_17_5782;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(hInst, "GAME");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "IS_HELP";
    if (!RegisterClass(&wc))
        return 0;

    wc.style = 0xb;
    wc.lpfnWndProc = fn_11_22fa;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = 0;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "IS_INFO";
    if (!RegisterClass(&wc))
        return 0;

    dc = CreateDC("DISPLAY", NULL, NULL, NULL);
    g_90e6 = GetDeviceCaps(dc, HORZRES);
    g_90e8 = GetDeviceCaps(dc, VERTRES);
    bits = GetDeviceCaps(dc, BITSPIXEL);
    planes = GetDeviceCaps(dc, PLANES);
    g_90ee = max(planes, bits);
    if (g_90ee >= 8)
        g_90f0 = 1;
    else
        g_90f0 = 0;
    g_90f2 = (GetDeviceCaps(dc, 94) & 1) != 0;
    DeleteDC(dc);
    fn_06_17e0();
    LoadString(g_9212, 0xb54, g_94e4, 40);
    LoadString(g_9212, 0xb55, g_94fa, 40);
    LoadString(g_9212, 0xb56, ver, 10);
    if (ver[0] == '2')
        g_967a = 1;
    else
        g_967a = 0;
    return 1;
}

/* 6:1b3c */
void fn_06_1b3c(void)
{
    if (g_8f66 && fn_02_1ac8())
        fn_02_1b96();
}

/* Creates the main window [inferred]. */
/* 6:17e0 */
void fn_06_17e0(void)
{
    HMENU menu;
    char title[40];
    int16_t h;
    int16_t w;
    int16_t y;
    int16_t x;
    DWORD style;

    g_90fa = LoadMenu(g_9212, MAKEINTRESOURCE(0x65));
    if (g_90f6)
        menu = g_90fa;
    else
        menu = 0;
    style = WS_POPUP;
    if (!g_0020) {
        style = WS_POPUP | WS_OVERLAPPEDWINDOW;
        x = g_1d20.left;
        w = g_1d20.right - x;
        y = g_1d20.top;
        h = g_1d20.bottom - y;
    } else {
        x = y = 0;
        w = GetSystemMetrics(SM_CXSCREEN);
        h = GetSystemMetrics(SM_CYSCREEN);
    }
    if (!g_920c)
        LoadString(g_9212, 0x922, title, 40);
    else
        LoadString(g_9212, 0x921, title, 40);
    CreateWindow(g_9690, title, style, x, y, w, h, 0, menu, g_8e66, NULL);
    if (g_0020 && fn_06_1290("OnTop", 1))
        SetWindowPos(g_0016, (HWND)-1, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

/* 6:18e0 */
void fn_06_18e0(void)
{
    fn_06_190c();
    g_049e = g_90f4 = 0;
    PostMessage(g_0016, 0x9cf, 0, 0L);
}

/* The label (no goto) resets CL's register tracking: the game stores the
 * 0 and pushes the zeros as immediates; the dead store `height = 14`
 * gives `mov ax,14; push ax`. */
/* 6:190c */
void fn_06_190c(void)
{
    int16_t height;
    int16_t unused2;
    HPALETTE old;

    g_13dc = GetDC(g_0016);
    fn_10_6e00();
    old = SelectPalette(g_13dc, g_920e, 0);
    fn_10_6e76(-1000, 2);
    SelectPalette(g_13dc, old, 0);
    ReleaseDC(g_0016, g_13dc);
    g_13dc = 0;
font:
    height = 14;
    g_90fe = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PROOF_QUALITY,
                        VARIABLE_PITCH | FF_SWISS, "Arial");
    g_912c = fn_10_6d38("ALPHABET");
    fn_06_02ca();
    if (!fn_06_09f8())
        PostQuitMessage(0);
}

/* 6:19bc */
void fn_06_19bc(void)
{
    int16_t unused;

    if (!g_049e) {
        g_049e = 1;
        fn_06_2ebc();
        fn_02_1d58();
        fn_10_022e(1);
        if (g_0012) {
            DeleteObject(g_0012);
            g_0012 = 0;
        }
        if (g_0016)
            SetMenu(g_0016, 0);
        if (g_90fa) {
            DestroyMenu(g_90fa);
            g_90fa = 0;
        }
        fn_10_0330();
        fn_06_033e();
        KillTimer(g_0016, 1);
        if (g_90fe) {
            DeleteObject(g_90fe);
            g_90fe = 0;
        }
        fn_10_6e26();
        fn_10_6b70(0);
    }
}

/* 6:1b62 */
int16_t fn_06_1b62(void)
{
    int16_t i;

    for (i = 0; i <= 14; i++) {
        if ((g_9100[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x460L)) == 0)
            return 0;
        if ((g_1df8[i] = GlobalLock(g_9100[i])) == 0) {
            GlobalFree(g_9100[i]);
            return 0;
        }
    }
    g_94a4 = 0;
    if ((g_912a = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 8L)) == 0)
        return 0;
    if ((g_1e4c = (int32_t)GlobalLock(g_912a)) == 0) {
        GlobalFree(g_912a);
        return 0;
    }
    return 1;
}

/* 6:1c0c */
int16_t fn_06_1c0c(void)
{
    g_90f8 = 0;
    if (lstrcmp(g_1d60, "DEMO") == 0) {
        g_90f8 = 1;
        PostMessage(g_0016, 0x9f0, 0, 0L);
    }
    if (lstrcmp(g_1d60, "PLAY") == 0) {
        g_90f8 = 1;
        PostMessage(g_0016, 0x9fa, 0, 0L);
    }
    return g_90f8;
}

/* Appends three digits to s, as '0' plus each value [inferred]. */

/* Nonzero when size bytes can be allocated, after compacting and
 * trying in 15000-byte blocks [inferred]. */
/* 6:1a68 */
int16_t fn_06_1a68(DWORD size)
{
    int16_t i;
    int16_t j;
    int16_t n;
    HGLOBAL h[20];

    for (i = 0; i < 10; i++)
        h[i] = 0;
    if ((h[0] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size)) != 0) {
        GlobalFree(h[0]);
        return 1;
    }
    GlobalCompact(-1L);
    GlobalCompact(0L);
    n = (int16_t)(size / 15000);
    if (n > 20)
        n = 20;
    for (i = 0; i < n; i++)
        if ((h[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 15000L)) == 0)
            break;
    for (j = 0; j < n; j++)
        if (h[j])
            GlobalFree(h[j]);
    if (i == n)
        return 1;
    return 0;
}
