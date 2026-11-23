/* INSPACE.EXE segment 2 (selector 1008), 2:1ac8-end: a second source
 * file (2:0000 far-calls 2:1c08). Declarations copied from seg02.c. */
#include "game.h"

/* Measures the main window's client area (clipped to the screen) into
 * g_90ea x g_0010, sets the clip region g_0012, seeds rand and runs
 * fn_10_0000 with the window DC in g_13dc. */
/* 2:1ac8 */
int16_t fn_02_1ac8(void)
{
    int16_t r;
    RECT rc;

    g_13dc = GetDC(g_0016);
    GetClientRect(g_0016, &rc);
    LO16(g_90ea) = rc.right < GetSystemMetrics(SM_CXSCREEN) ? rc.right : GetSystemMetrics(SM_CXSCREEN);
    g_0010 = rc.bottom < GetSystemMetrics(SM_CYSCREEN) ? rc.bottom : GetSystemMetrics(SM_CYSCREEN);
    HI16(g_90ea) = g_0010 - g_0a70;
    g_8e58 = 0;
    g_8e5a = g_0010 - 0x55;
    if (g_0012) {
        DeleteObject(g_0012);
        g_0012 = 0;
    }
    g_0012 = CreateRectRgn(0, 0, LO16(g_90ea), HI16(g_90ea));
    srand(GetCurrentTime());
    r = fn_10_0000();
    ReleaseDC(g_0016, g_13dc);
    g_13dc = 0;
    return r;
}

/* 2:1b96 */
void fn_02_1b96(void)
{
    int16_t u;
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

/* Draws one game frame [inferred] into the window DC (the pop-up g_9460
 * when open), with debug traces of g_9646 ("iMainSmart") in mode 1. */
/* 2:1c08 */
void fn_02_1c08(void)
{
    char pad[18];
    HPALETTE pal;
    char buf[20];
    HWND hwnd;

    if (g_90f4 == 1) {
        fn_13_4eca("GameFrame 2 iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
    }
    hwnd = g_9460 ? g_9460 : g_0016;
    if (g_13de) {
        fn_02_1d58();
        return;
    }
    g_968c = 1;
    g_13dc = GetDC(hwnd);
    if (g_920e)
        pal = SelectPalette(g_13dc, g_920e, 0);
    if (g_90f4 == 1) {
        fn_13_4eca("GameFrame 3 iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
    }
    if (g_9460)
        fn_17_60d8();
    else
        fn_07_0000();
    if (g_90f4 == 1) {
        fn_13_4eca("GameFrame 1 iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
    }
    if (pal)
        SelectPalette(g_13dc, pal, 0);
    ReleaseDC(hwnd, g_13dc);
    g_13dc = 0;
    g_968c = 0;
}

/* 2:1d58 */
void fn_02_1d58(void)
{
    int16_t u1;
    int16_t u2;

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
