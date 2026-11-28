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

    main_dc = GetDC(main_window);
    GetClientRect(main_window, &rc);
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
    ReleaseDC(main_window, main_dc);
    main_dc = 0;
    return r;
}

/* 2:1b96 */
void fn_02_1b96(void)
{
    int16_t u;
    HPALETTE old;

    main_dc = GetDC(main_window);
    if (game_palette) {
        old = SelectPalette(main_dc, game_palette, 0);
        RealizePalette(main_dc);
    }
    if (g_90f4 == 1)
        fn_09_0c06();
    if (old)
        SelectPalette(main_dc, old, 0);
    ReleaseDC(main_window, main_dc);
    main_dc = 0;
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
    hwnd = g_9460 ? g_9460 : main_window;
    if (g_13de) {
        fn_02_1d58();
        return;
    }
    g_968c = 1;
    main_dc = GetDC(hwnd);
    if (game_palette)
        pal = SelectPalette(main_dc, game_palette, 0);
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
        SelectPalette(main_dc, pal, 0);
    ReleaseDC(hwnd, main_dc);
    main_dc = 0;
    g_968c = 0;
}

/* 2:1d58 */
void fn_02_1d58(void)
{
    int16_t u1;
    int16_t u2;

    main_dc = GetDC(main_window);
    SelectClipRgn(main_dc, g_0012);
    fn_10_01fe();
    ReleaseDC(main_window, main_dc);
    main_dc = 0;
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
