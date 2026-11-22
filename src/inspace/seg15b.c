/* @cflags /AM /G2 /Gw /Gs /Os */
/* INSPACE.EXE segment 15 (selector 1070), first source file: 15:0000-15:52e4
 * (files.tsv group 29), compiled with /G2 (no 386 long jumps). */
#include "inspace.h"
#include <stdlib.h>

extern int g_9214;
extern HDC g_929a;
extern RECT g_3cd4;
void far fn_10_9672(void);
void far fn_09_699e(void);
void far fn_10_993a(int a, int b);
void far fn_10_6e76(int lo, int hi);   /* seg10 declares (long a) */
void far fn_10_6d7a(int a, int b, int c);
void far fn_10_6e4c(void);
void far fn_10_6da6(int a, int b);
void far fn_10_6dd4(int a);
void far fn_10_744c(int a);
int far fn_15_3caa(int a);
void far fn_15_1328(int full);
void far fn_15_1eac(void);
void far fn_15_482e(void);
int far fn_15_374c(int a);
extern int g_92a2;
extern int g_0010;
extern DWORD g_1e50;             /* declared before g_17f2: compare operand order (15:3590) */
extern DWORD g_17f2;
extern int g_93a6;
extern int g_0928;
extern int g_914a;
extern int g_929c;
extern int g_92be;
extern int g_90f4;
extern int g_9534[3];
extern int g_953a;
extern int g_953c;
extern HBITMAP g_3ccc[2];
extern HDC g_3cdc[2];
extern HGDIOBJ g_3cd0[2];
extern HPALETTE g_3ce0[2];
extern HGDIOBJ g_9296;
extern HPALETTE g_92a0;
extern HBITMAP g_9294;
HBITMAP far fn_10_6c02(int a, int b, int c);
HBITMAP far fn_10_6ec6(HBITMAP a);
void far fn_10_9962(int a, HDC dc, int x, int y, int w, int h, HDC src, int sx, int sy,
                    int sw, int sh, DWORD rop);
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
extern int g_94ac;
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

/* @addr 15:0f2e */
void far fn_15_0f2e(void)
{
    HBITMAP bmp;
    HGDIOBJ old1;
    HBITMAP bmp2;
    HGDIOBJ old2;
    HDC dc1;
    HDC dc2;
    HPALETTE oldpal;
    int id;

    g_9214 = 0;
    fn_10_9672();
    if (!g_9214)
        return;
    if (g_9214 == 1)
        id = 0x110;
    if (g_9214 == 2)
        id = 0x112;
    if (g_9214 == 3)
        id = 0x116;
    if (g_9214 == 4)
        id = (rand() % 2 + 35) * 2;
    bmp = fn_10_6c02(id, 0, -1);
    bmp2 = fn_10_6ec6(bmp);
    dc1 = CreateCompatibleDC(g_13dc);
    dc2 = CreateCompatibleDC(g_13dc);
    old2 = SelectObject(dc2, bmp2);
    old1 = SelectObject(dc1, bmp);
    if (g_920e)
        oldpal = SelectPalette(dc1, g_920e, 0);
    fn_10_9962(0, g_929a, g_3cd4.left, g_3cd4.top, g_3cd4.right - g_3cd4.left,
               g_3cd4.bottom - g_3cd4.top, dc2, 0, 0, 29, 29, SRCAND);
    SetStretchBltMode(g_929a, COLORONCOLOR);
    fn_10_9962(0, g_929a, g_3cd4.left, g_3cd4.top, g_3cd4.right - g_3cd4.left,
               g_3cd4.bottom - g_3cd4.top, dc1, 0, 0, 29, 29, SRCPAINT);
    SelectObject(dc1, old1);
    SelectObject(dc2, old2);
    if (oldpal)
        SelectPalette(dc1, oldpal, 0);
    DeleteDC(dc1);
    DeleteObject(bmp);
    DeleteDC(dc2);
    DeleteObject(bmp2);
}

/* @addr 15:1328 */
void far fn_15_1328(int full)
{
    int i;
    int j;
    DWORD t;

    fn_09_699e();
    if (g_92ac) {
        SelectObject(g_92b8, g_92ae);
        if (g_92c2)
            SelectPalette(g_92b8, g_92c2, 0);
        DeleteDC(g_92b8);
        DeleteObject(g_92ac);
        g_92ac = g_92b8 = 0;
        if (g_90f4 == 0 && g_3ccc[0] != 0) {
            t = GetCurrentTime();
            while (GetCurrentTime() - t < 1300)
                ;
        }
    }
    if (full) {
        for (i = 0; i < 3; i++)
            if (g_9534[i]) {
                DeleteObject(g_9534[i]);
                g_9534[i] = 0;
            }
        if (g_953a) {
            DeleteObject(g_953a);
            g_953a = 0;
        }
        if (g_953c) {
            DeleteObject(g_953c);
            g_953c = 0;
        }
    }
    for (j = 0; j < 2; j++)
        if (g_3ccc[j]) {
            SelectObject(g_3cdc[j], g_3cd0[j]);
            if (j == 0)
                SelectPalette(g_3cdc[j], g_3ce0[j], 0);
            DeleteDC(g_3cdc[j]);
            g_3cdc[j] = 0;
            DeleteObject(g_3ccc[j]);
            g_3ccc[j] = 0;
        }
    if (g_90f4 != 8 && g_929a) {
        SelectObject(g_929a, g_9296);
        if (g_92a0)
            SelectPalette(g_929a, g_92a0, 0);
        DeleteDC(g_929a);
        DeleteObject(g_9294);
        g_929a = g_9294 = 0;
    }
}

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

/* Scatters 250 random dots into two DCs [inferred]. POINT, not two ints:
 * CL does not CSE struct members across the calls. */
/* @addr 15:28b2 */
void far fn_15_28b2(HDC dc1, HDC dc2, int a, int b)
{
    int i;
    HGDIOBJ old1;
    HGDIOBJ old2;
    int h;
    int w;
    int sz;
    POINT pt;

    w = b * a - 3;
    h = (b - 8) * a;
    for (i = 0; i < 250; i++) {
        pt.x = rand() % w + 3;
        pt.y = rand() % h;
        if (rand() % 3) {
            sz = rand() % 4 + 2;
            old1 = SelectObject(dc1, GetStockObject(BLACK_BRUSH));
            old2 = SelectObject(dc2, GetStockObject(BLACK_BRUSH));
            Ellipse(dc1, pt.x, pt.y, pt.x + sz, pt.y + sz);
            Ellipse(dc2, pt.x, pt.y, pt.x + sz, pt.y + sz);
        } else {
            sz = rand() % 4 + 2;
            old1 = SelectObject(dc1, g_5ea8);
            old2 = SelectObject(dc2, g_5ea8);
            PatBlt(dc1, pt.x, pt.y, sz, sz, 0xa000c9L);
            PatBlt(dc2, pt.x, pt.y, sz, sz, 0xa000c9L);
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
        g_92ac = g_92b8 = 0;
    }
    g_92b8 = CreateCompatibleDC(g_13dc);
    g_92ac = CreateCompatibleBitmap(g_13dc, w, h);
    g_92ae = SelectObject(g_92b8, g_92ac);
    if (g_920e)
        g_92c2 = SelectPalette(g_92b8, g_920e, 0);
    PatBlt(g_92b8, 0, 0, w, h, BLACKNESS);
}

/* @addr 15:3590 */
void far fn_15_3590(void)
{
    int i;

    switch (g_92a2) {
    case 0:
        if (!fn_15_3caa(0))
            break;
        if (g_90f4 == 9) {
            g_92a2 = 2;
            break;
        }
        g_17f2 = 0;
        g_92a2++;
        fn_15_1328(1);
        fn_15_1eac();
        if (!g_93a6)
            PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
        if (!g_0928) {
            fn_10_993a(3, 0xcc);
            fn_10_993a(2, 0x89);
        }
        if (g_90f4 == 6) {
            fn_10_6e76(-1, 1);
            for (i = 40; i < 228; i += 4)
                fn_10_6d7a(i, i, i);
            fn_10_6e4c();
            fn_10_6da6(1, 0);
            fn_10_6e76(0, 2);
            for (i = 40; i < 228; i += 4)
                fn_10_6d7a(i, i, i);
            fn_10_6e4c();
            fn_15_482e();
            fn_10_6e76(-1, 1);
            fn_10_6dd4(1);
        } else
            fn_10_6e76(-2, 2);
        fn_15_374c(1);
        break;
    case 1:
        if (g_17f2 == 0) {
            if (fn_15_374c(0)) {
                fn_10_744c(9);
                g_17f2 = g_1e50 + 1000;
            }
        } else if (g_1e50 > g_17f2)
            g_92a2++;
        break;
    case 2:
        if (g_90f4 == 6)
            g_914a++;
        else if (g_90f4 == 8)
            g_929c++;
        else if (g_90f4 == 9)
            g_92be++;
        break;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_15_1eac(void)
{
    g_92a2 = 0;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_15_374c(int a)
{
    return a;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_15_3caa(int a)
{
    return a;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_15_482e(void)
{
    g_92a2 = 1;
}
