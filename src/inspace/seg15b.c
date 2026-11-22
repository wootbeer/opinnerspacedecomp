/* @cflags /AM /G2 /Gw /Gs /Os */
/* INSPACE.EXE segment 15 (selector 1070), first source file: 15:0000-15:52e4
 * (files.tsv group 29), compiled with /G2 (no 386 long jumps). */
#include "inspace.h"
#include <dos.h>
#include <stdlib.h>

extern int g_1016;
extern int g_8ffc;
extern long g_3b98;
extern int g_95d8;
extern int g_95dc;
extern char g_87e0[];               /* run-time buffer (BSS) */
extern char g_881c[];               /* run-time buffer (BSS) */
extern DWORD g_6e28;
extern long g_6e2c;
extern DWORD g_1e50;

extern int g_92a8;
extern int g_92aa;
extern int g_92b6;
extern int g_92bc;
extern int g_92ac;
extern int g_92ae;
extern int g_92b8;
extern int g_92c2;
extern int g_92b0[3];
extern int g_3cc8[2];
extern int g_95d0;
extern char g_94ac;
extern int g_90ee;
extern int g_11aa;
extern char g_9078[];               /* run-time buffer (BSS) */
extern char g_96b8[];               /* run-time buffer (BSS) */

extern int g_94c4;
extern int g_90f4;
extern int g_92d4;
extern HGDIOBJ g_5ea8;
extern int g_90ea;
extern int g_90ec;

void far fn_06_84fc(int a, int x, int y, int dx, int dy, int w, int h,
                    int c, int d, int e);
int far fn_06_73f6(void);
int far fn_06_7c14(void);
int far fn_14_4006(HFILE f, char huge *buf, unsigned long len);

void far fn_10_6e4c(void);
void far fn_10_6e76(int lo, int hi);   /* seg10 declares (long a) */
void far fn_10_0552(int i, int a);
void far fn_10_58ce(int a);
void far fn_10_754a(int a, int b, int c, int d);
int far fn_10_6d38(LPCSTR s);
void far fn_10_0136(void);
void far fn_11_a4a6(long a, long b, int c);
void far fn_11_a9ea(int a);

void far fn_15_152e(void);


void far fn_15_152e(void);

/* @addr 15:14be */
void far fn_15_14be(void)
{
    int i;

    for (i = 0; i < 3; i++)
        if (g_92b0[i]) {
            DeleteObject(g_92b0[i]);
            g_92b0[i] = 0;
        }
    for (i = 0; i < 2; i++)
        if (g_3cc8[i]) {
            DeleteObject(g_3cc8[i]);
            g_3cc8[i] = 0;
        }
    fn_15_152e();
}

/* @addr 15:152e */
void far fn_15_152e(void)
{
    if (g_92b6) {
        SelectObject(g_92b6, g_92aa);
        if (g_92bc)
            SelectPalette(g_92b6, g_92bc, 0);
        DeleteDC(g_92b6);
        DeleteObject(g_92a8);
        g_92b6 = g_92a8 = 0;
    }
}

/* near-match 43%: 15:28b2 (orig has no 386 long jcc here and no CSE of px+sz; maybe another source file / flags) */
void far fn_15_28b2(HDC dc1, HDC dc2, int a, int b)
{
    int i;
    HGDIOBJ old1;
    HGDIOBJ old2;
    int h;
    int w;
    int sz;
    int py;
    int px;

    w = b * a - 3;
    h = (b - 8) * a;
    for (i = 0; i < 250; i++) {
        px = rand() % w + 3;
        py = rand() % h;
        if (rand() % 3) {
            sz = rand() % 4 + 2;
            old1 = SelectObject(dc1, GetStockObject(BLACK_BRUSH));
            old2 = SelectObject(dc2, GetStockObject(BLACK_BRUSH));
            Ellipse(dc1, px, py, px + sz, py + sz);
            Ellipse(dc2, px, py, px + sz, py + sz);
        } else {
            sz = rand() % 4 + 2;
            old1 = SelectObject(dc1, g_5ea8);
            old2 = SelectObject(dc2, g_5ea8);
            PatBlt(dc1, px, py, sz, sz, 0xa000c9L);
            PatBlt(dc2, px, py, sz, sz, 0xa000c9L);
        }
        SelectObject(dc1, old1);
        SelectObject(dc2, old2);
    }
}

/* @addr 15:3bfa */
void far fn_15_3bfa(int w, int h)
{
    if (g_92b8) {
        SelectObject(g_92b8, g_92ae);
        if (g_92c2)
            SelectPalette(g_92b8, g_92c2, 0);
        DeleteDC(g_92b8);
        DeleteObject(g_92ac);
        g_92b8 = g_92ac = 0;
    }
    g_92b8 = CreateCompatibleDC(g_13dc);
    g_92ac = CreateCompatibleBitmap(g_13dc, w, h);
    g_92ae = SelectObject(g_92b8, g_92ac);
    if (g_920e)
        g_92c2 = SelectPalette(g_92b8, g_920e, 0);
    PatBlt(g_92b8, 0, 0, w, h, BLACKNESS);
}
