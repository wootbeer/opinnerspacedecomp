/* INSPACE.EXE segment 2 (selector 1008), 2:1ac8-end: a second source
 * file (2:0000 far-calls 2:1c08). Declarations copied from seg02.c. */
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
void far fn_02_1d58(void);

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

/* Draws one game frame [inferred] into the window DC (the pop-up g_9460
 * when open), with debug traces of g_9646 ("iMainSmart") in mode 1. */
/* @addr 2:1c08 */
void far fn_02_1c08(void)
{
    char pad[18];
    HPALETTE pal;
    char buf[20];
    HWND hwnd;

    if (g_90f4 == 1) {
        fn_13_4eca("GameFrame 2 iMainSmart = ");
        fn_06_0f1a(g_9646, buf);
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
        fn_06_0f1a(g_9646, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
    }
    if (g_9460)
        fn_17_60d8();
    else
        fn_07_0000();
    if (g_90f4 == 1) {
        fn_13_4eca("GameFrame 1 iMainSmart = ");
        fn_06_0f1a(g_9646, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
    }
    if (pal)
        SelectPalette(g_13dc, pal, 0);
    ReleaseDC(hwnd, g_13dc);
    g_13dc = 0;
    g_968c = 0;
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
