/* @cflags /AM /G2 /Gw /Gs /Os */
/* INSPACE.EXE segment 15 (selector 1070), first source file: 15:0000-15:52e4
 * (files.tsv group 29), compiled with /G2 (no 386 long jumps). */
#include "inspace.h"
#include <mmsystem.h>
#include <stdlib.h>

extern int g_9214;
extern int g_9580;
extern int g_6dac, g_6dae, g_6db0, g_6db2;   /* RECT [inferred] */
extern int g_6db4, g_6db6;                   /* POINT offset [inferred] */
extern int g_92c6;
extern int g_92c8;
extern int g_9208;
extern HDC g_929e;
extern HBITMAP g_92b2;
extern int g_92a4;
void far fn_07_13b2(int a, int b, int c);
void far fn_07_158e(void);
void far fn_15_20ca(void);
extern char far *g_4fcc;
extern HGLOBAL g_93a8;
extern char g_380c[];
int far fn_10_9764(int a);
void far fn_10_a332(LPSTR buf, int id, int n, ...);
void far fn_11_3fd4(LPSTR s, int mode);

#pragma pack(1)
typedef struct {                /* 0x1a9 bytes: a saved game file [inferred] */
    char p000[0x24];
    int f24;
    char p026[0x32 - 0x26];
    int f32;
    char p034[0x156 - 0x34];
    int f156;
    int f158;
    int f15a;
    int f15c;
    int f15e;
    int f160;
    char p162[2];
    int f164;
    char p166[0x18b - 0x166];
    DWORD f18b;
    char p18f[0x1a9 - 0x18f];
} REC_1A9;
#pragma pack()
extern int g_3ce4;
extern int g_92dc;
extern int g_3c9c, g_3c9e, g_3ca0, g_3ca2;
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

/* 0x7c-byte records, far array at DS:6e24 [inferred]. */
typedef struct {
    char p00[0x7a];
    char f7a;
    char f7b;
} REC_7C;
extern REC_7C far *g_6e24;
typedef struct {                /* 0x15a bytes, DGROUP array at DS:7090 */
    char p00[0xd6];
    int fd6;                    /* +d6 */
    char pd8[0x15a - 0xd8];
} REC_15A;
extern REC_15A g_7090[];
extern int g_9646;
extern POINT g_3d08[16];
extern int g_3ce8[16];
extern char g_9563;
extern int g_92da;
int far fn_15_2a08(void);

extern POINT g_3c8c[4];         /* polygon; [3] also used as offset/size [inferred] */
extern int g_3ce6;

extern int g_92d4;
extern DWORD g_3cc4;
extern int g_3ca4;
extern int g_3ca6;
extern RECT g_3ca8;
extern RECT g_3cb8;
extern RECT far *g_3cc0;          /* GlobalLock of g_92a6 */
extern HGLOBAL g_92a6;
extern int g_9298;
extern int g_92de;
extern int g_92d6;
extern int g_3cea;
extern int g_92ba;
extern int g_92d8;
extern DWORD g_6e28;
void far fn_15_8604(void);
void far fn_15_8ae6(void);
/* seg10 declares it void, with (long a, ..., long j, int k) */
HBITMAP far fn_10_9526(RECT far *a, HGLOBAL b, int c, long d, int e, long f, int g,
                       int h, int i, int jx, int jy, int k);
extern int g_92d2;
extern int g_3d48;
extern int g_3d4a;
extern int g_95b8;
extern int g_92e4;
extern int g_91f8;
void far fn_10_7480(int a, int b);
void far fn_10_740c(void);
void far fn_06_1d9a(void);
void far fn_06_1c72(int a);
int far fn_15_0000(int a);
void far fn_15_09e6(void);
void far fn_15_4c76(int a, int b);
void far fn_15_1584(int a);
void far fn_15_52e4(void);
void far fn_15_14be(void);
void far fn_15_0f2e(void);

void far fn_15_152e(void);


void far fn_15_152e(void);

/* px, py, size live in a struct: CL does not keep struct fields in
 * registers, which gives the game's [bp-8] pushes. */
/* @addr 15:0760 */
void far fn_15_0760(void)
{
    int y;
    int x;
    struct { int px, py, size; } r;     /* icon position and size [inferred] */

    y = x = 0;
    if (g_929a) {
        if ((g_929c >= 2 || g_92a2 >= 1) && g_92d6 != -1) {
            BitBlt(g_13dc, 0, 0, g_90ea, g_0010, g_929a, 0, 0, SRCCOPY);
            if ((g_92a2 != 1 || g_92d8 == -1) && g_929c <= 6) {
                r.size = (g_6e24[g_7090[g_9646].fd6].f7a
                        + (g_6e24[g_7090[g_9646].fd6].f7b - 6) / 2) * 4;
                r.px = g_90ea / 2 - r.size / 2;
                BitBlt(g_13dc, r.px, r.py = g_92d6 + 5, r.size, r.size, g_3cdc[1], 0, g_3cea, SRCAND);
                BitBlt(g_13dc, r.px, r.py, r.size, r.size, g_3cdc[0], 0, g_3cea, SRCPAINT);
            }
            return;
        }
        SelectObject(g_929a, g_9296);
        if (g_92a0)
            SelectPalette(g_929a, g_92a0, 0);
        DeleteDC(g_929a);
        DeleteObject(g_9294);
        g_929a = g_9294 = 0;
    } else if (g_929c >= 6)
        return;
    if (!g_92a6) {
        g_92a6 = GlobalAlloc(GHND, 8L);
        if (!g_92a6)
            return;
        g_3cc0 = (RECT far *)GlobalLock(g_92a6);
        if (!g_3cc0) {
            GlobalFree(g_92a6);
            return;
        }
    }
    g_9294 = fn_10_9526(g_3cc0, g_92a6, 0x73, 0L, 0, 0L, 0, g_90ea, g_0010, x, y, 0);
    g_929a = CreateCompatibleDC(g_13dc);
    g_9296 = SelectObject(g_929a, g_9294);
    if (g_920e)
        g_92a0 = SelectPalette(g_929a, g_920e, 0);
    SetRect(&g_3ca8, g_3cc0[0].left, g_3cc0[0].top, g_3cc0[0].right, g_3cc0[0].bottom);
    g_3d48 = g_3ca4 = g_3cc0[0].left;
    g_3d4a = g_3ca6 = g_3cc0[0].top;
    g_92ba = g_3cc0[1].top;
    g_92de = g_0010;
    fn_15_8604();
    BitBlt(g_13dc, 0, 0, g_90ea, g_0010, g_929a, 0, 0, SRCCOPY);
    if (g_3cc0) {
        GlobalUnlock(g_92a6);
        g_3cc0 = 0;
        GlobalFree(g_92a6);
        g_92a6 = 0;
    }
}

/* Builds the 16-row perspective strip in g_3ccc[] from bitmap g_92b0[1]
 * [inferred]. */
/* @addr 15:09e6 */
void far fn_15_09e6(void)
{
    HGDIOBJ oldbmp;
    HDC dc;
    HPALETTE pal;
    int i;
    int size;
    int dy;
    int pct;
    int scale;
    int unit;
    int y;
    int unit2;
    int u;
    int j;
    BITMAP bm;

    if (g_90ee < 8)
        scale = 4;
    else
        scale = 2;
    if (g_90f4 == 0 || g_9563 == 0)
        unit = fn_15_2a08();
    else {
        GetObject(g_92b0[0], sizeof(BITMAP), &bm);
        unit = bm.bmHeight / scale;
    }
    g_92da = unit;
    size = unit * scale;
    unit2 = unit * 2;
    g_3d08[0].y = g_3d08[0].x = unit * 4;
    dy = (unit2 * -27 / 100 + unit * 4) / 15;
    y = unit * 4;
    g_3ce8[0] = 0;
    pct = 95;
    for (i = 1; i < 10; i++, pct -= 6) {
        g_3ce8[i] = y;
        g_3d08[i].x = g_3d08[i - 1].x - dy;
        g_3d08[i].y = g_3d08[i].x * pct / 100;
        y += g_3d08[i].y;
    }
    for (; i < 16; i++, pct += 13) {
        g_3ce8[i] = y;
        g_3d08[i].x = g_3d08[i - 1].x - dy;
        g_3d08[i].y = g_3d08[i].x * pct / 100;
        y += g_3d08[i].y;
    }
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_92b0[1]);
    if (g_920e)
        pal = SelectPalette(dc, g_920e, 0);
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
    g_3ccc[0] = CreateCompatibleBitmap(dc, g_3d08[0].x, y);
    g_3cdc[0] = CreateCompatibleDC(dc);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    if (g_920e)
        g_3ce0[0] = SelectPalette(g_3cdc[0], g_920e, 0);
    PatBlt(g_3cdc[0], 0, 0, g_3d08[0].x, y, BLACKNESS);
    SetStretchBltMode(g_3cdc[0], COLORONCOLOR);
    for (i = 0; i < 16; i++) {
        fn_10_740c();
        fn_10_9962(0, g_3cdc[0], 0, g_3ce8[i], g_3d08[i].x, g_3d08[i].y, dc, 0, 0,
                   size, size, SRCCOPY);
    }
    SelectObject(g_3cdc[0], g_3cd0[0]);
    g_3ccc[1] = fn_10_6ec6(g_3ccc[0]);
    g_3cdc[1] = CreateCompatibleDC(g_13dc);
    g_3cd0[1] = SelectObject(g_3cdc[1], g_3ccc[1]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    SelectObject(dc, oldbmp);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
}

/* @addr 15:0cb0 */
void far fn_15_0cb0(void)
{
    DWORD u;
    int y;
    int x;
    DWORD t;

    y = x = 0;
    fn_10_744c(0x6e);
    g_6e28 = g_1e50 + 90000L;
    if (g_90f4 == 0)
        PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
    if (g_90f4 == 0 && g_95b8 == 6) {
        if (!g_9298)
            g_92d4 = 9;
        else {
            fn_10_6da6(0, 1);
            fn_10_6e76(0x6d, 2);
            if (!g_92a6) {
                g_92a6 = GlobalAlloc(GHND, 8L);
                if (!g_92a6)
                    return;
                g_3cc0 = (RECT far *)GlobalLock(g_92a6);
                if (!g_3cc0) {
                    GlobalFree(g_92a6);
                    return;
                }
            }
            timeGetTime();
            g_9294 = fn_10_9526(g_3cc0, g_92a6, 100, 0L, 0, 0L, 0, g_90ea, g_0010, x, y, 0);
            g_929a = CreateCompatibleDC(g_13dc);
            g_9296 = SelectObject(g_929a, g_9294);
            if (g_920e)
                g_92a0 = SelectPalette(g_929a, g_920e, 0);
            timeGetTime();
            SetRect(&g_3ca8, g_3cc0[0].left, g_3cc0[0].top, g_3cc0[0].right, g_3cc0[0].bottom);
            SetRect(&g_3cb8, g_3cc0[1].left, g_3cc0[1].top, g_3cc0[1].right, g_3cc0[1].bottom);
            SetRect(&g_3cd4, g_3cc0[4].left, g_3cc0[4].top, g_3cc0[4].right, g_3cc0[4].bottom);
            g_3d48 = g_3ca4 = g_3cc0[0].left;
            g_3d4a = g_3ca6 = g_3cc0[0].top;
            g_92de = max(g_3cc0[2].bottom, g_3cc0[3].bottom);
            fn_15_8604();
            fn_15_8ae6();
            fn_15_0f2e();
            BitBlt(g_13dc, 0, 0, g_90ea, g_0010, g_929a, 0, 0, SRCCOPY);
            if (g_3cc0) {
                GlobalUnlock(g_92a6);
                g_3cc0 = 0;
                GlobalFree(g_92a6);
                g_92a6 = 0;
            }
            g_92d4 = 0;
            g_3cc4 = g_1e50 + 1100;
        }
    } else
        g_92d4 = 5;
    if (g_90f4) {
        fn_10_744c(0x4b);
        t = GetCurrentTime() + 1550;
        do
            fn_10_740c();
        while (GetCurrentTime() < t);
        g_92d8 = g_92d6;
        g_92d6 = 10;
    }
}

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

/* Step of a timed screen sequence, state g_92d4 [inferred]. */
/* @addr 15:10be */
void far fn_15_10be(void)
{
    DWORD u;
    DWORD t;
    DWORD t2;

    switch (g_92d4) {
    case 0:
        if (g_90f4 != 9)
            fn_10_7480(-1, 1);
        if (GetCurrentTime() > g_3cc4) {
            fn_15_52e4();
            g_92d4++;
        }
        break;
    case 2:
        fn_10_744c(0x4b);
        t = GetCurrentTime() + 1460;
        do
            fn_10_740c();
        while (GetCurrentTime() < t - 400);
        fn_15_482e();
        fn_10_740c();
        fn_15_09e6();
        do
            fn_10_740c();
        while (GetCurrentTime() < t);
        fn_15_4c76(1, 0);
        g_92d4++;
        break;
    case 3:
        fn_15_4c76(0, 0);
        break;
    case 4:
        if (g_90f4) {
            g_92d4++;
            break;
        }
    case 1:
        fn_15_1584(0);
        break;
    case 5:
        if (g_90f4 == 0) {
            BitBlt(g_929a, g_3ca4 + 29, g_3ca6 + 29, g_3ca8.right - g_3ca8.left - 58, g_92d2 - 58,
                   g_13dc, g_3d48 + 29, g_3d4a + 29, SRCCOPY);
            t = GetCurrentTime() + 800;
            do
                ;
            while (GetCurrentTime() < t);
        } else
            fn_15_09e6();
        fn_15_0000(2);
        g_3cc4 = GetCurrentTime() + 950;
        g_92d4++;
        break;
    case 6:
        if (GetCurrentTime() > g_3cc4) {
            g_92d4++;
            fn_15_0000(1);
        }
        break;
    case 7:
        if (!fn_15_0000(0))
            break;
    case 8:
        fn_10_740c();
        g_92d4++;
        break;
    case 9:
        fn_10_740c();
        fn_15_1328(1);
        fn_15_14be();
        if (g_90f4 == 0) {
            PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
            t2 = GetCurrentTime();
            do
                fn_10_740c();
            while (GetCurrentTime() - t2 < 450);
            fn_10_6e76(8, 0);
            fn_10_6dd4(0);
            g_95b8 = 7;
            if (!g_92e4)
                g_91f8 = 0;
            fn_06_1d9a();
            fn_06_1c72(1);
        } else if (g_90f4 == 6)
            g_914a++;
        else if (g_90f4 == 8)
            g_929c++;
        break;
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

/* Builds the two-frame bitmap pair g_3ccc[] from the bitmaps g_92b0[1..2]
 * [inferred]. */
/* @addr 15:1eac */
void far fn_15_1eac(void)
{
    int u1[2];
    HGDIOBJ old[2];
    HDC dc[2];
    HPALETTE pal[2];
    int i;
    int u2[2];
    int size;
    int scale;
    int h;

    if (g_90ee < 8)
        scale = 4;
    else
        scale = 2;
    size = (g_6e24[g_7090[g_9646].fd6].f7a + (g_6e24[g_7090[g_9646].fd6].f7b - 6) / 2) * scale;
    for (i = g_3ce8[0] = h = 0; i < 2; i++) {
        g_3d08[i].x = g_3d08[i].y = (g_6e24[g_7090[g_9646].fd6].f7a
                                     + (g_6e24[g_7090[g_9646].fd6].f7b - 6) / 2) * 4;
        g_3ce8[i] = h;
        h += g_3d08[i].y;
        dc[i] = CreateCompatibleDC(g_13dc);
        old[i] = SelectObject(dc[i], g_92b0[i + 1]);
        if (g_920e)
            pal[i] = SelectPalette(dc[i], g_920e, 0);
    }
    g_3ccc[0] = CreateCompatibleBitmap(dc[0], g_3d08[0].x, h);
    g_3cdc[0] = CreateCompatibleDC(dc[0]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    if (g_920e)
        g_3ce0[0] = SelectPalette(g_3cdc[0], g_920e, 0);
    PatBlt(g_3cdc[0], 0, 0, g_3d08[0].x, h, BLACKNESS);
    SetStretchBltMode(g_3cdc[0], COLORONCOLOR);
    for (i = 0; i < 2; i++)
        fn_10_9962(0, g_3cdc[0], 0, g_3ce8[i], g_3d08[i].x, g_3d08[i].y, dc[i], 0, 0,
                   size, size, SRCCOPY);
    SelectObject(g_3cdc[0], g_3cd0[0]);
    g_3ccc[1] = fn_10_6ec6(g_3ccc[0]);
    g_3cdc[1] = CreateCompatibleDC(g_13dc);
    g_3cd0[1] = SelectObject(g_3cdc[1], g_3ccc[1]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    for (i = 0; i < 2; i++) {
        SelectObject(dc[i], old[i]);
        if (pal[i])
            SelectPalette(dc[i], pal[i], 0);
        DeleteDC(dc[i]);
    }
}

/* Draws the grey-shaded backdrop into g_92b6 [inferred]. */
/* @addr 15:4a2e */
void far fn_15_4a2e(void)
{
    HGDIOBJ oldbr;
    HDC dc;
    HBITMAP bmp;
    HGDIOBJ oldbmp;
    int i;
    int step;
    int c;
    int u;

    dc = CreateCompatibleDC(g_92b6);
    oldbmp = SelectObject(dc, bmp = CreateCompatibleBitmap(dc, g_3ce6, g_3c8c[3].y));
    PatBlt(dc, 0, 0, g_3ce6, g_3c8c[3].y, BLACKNESS);
    oldbr = SelectObject(dc, GetStockObject(WHITE_BRUSH));
    Polygon(dc, g_3c8c, 4);
    SelectObject(dc, oldbr);
    step = 1700 / g_3c8c[3].y;
    c = 450;
    for (i = 0; i < g_3c8c[3].y - 2; i += 2) {
        oldbr = SelectObject(g_92b6, CreateSolidBrush(PALETTERGB(c / 10, c / 10, c / 10)));
        BitBlt(g_92b6, 0, i, g_3ce6, 2, dc, 0, i, MERGECOPY);
        DeleteObject(SelectObject(g_92b6, oldbr));
        c = min(2550, c += step);
    }
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
    DeleteObject(bmp);
    oldbr = SelectObject(g_92b6, CreateSolidBrush(PALETTERGB(0x80, 0x80, 0x80)));
    PatBlt(g_92b6, g_3c8c[3].x + 1, g_3c8c[3].y, g_3ce6 - 2, 10, PATCOPY);
    DeleteObject(SelectObject(g_92b6, oldbr));
    step = 227;
    c = 450;
    for (i = 0; i < 18; i += 2) {
        oldbr = SelectObject(g_92b6, CreateSolidBrush(PALETTERGB(c / 10, c / 10, c / 10)));
        PatBlt(g_92b6, g_3ce6 / 2 + i + g_3c8c[3].x - 18, g_3c8c[3].y + 10, 2, 42, PATCOPY);
        PatBlt(g_92b6, g_3ce6 / 2 - i + g_3c8c[3].x + 16, g_3c8c[3].y + 10, 2, 42, PATCOPY);
        DeleteObject(SelectObject(g_92b6, oldbr));
        c = min(c + step, 2550);
    }
}

/* Builds the 16-row strip bitmaps g_3ccc[] at the sizes for g_9208 (or the
 * g_92be variants when g_90f4 == 9) [inferred]. */
/* @addr 15:1a42 */
void far fn_15_1a42(void)
{
    int u;
    HGDIOBJ oldbmp;
    HPALETTE oldpal;
    int i;
    int a;
    int b;
    int size;
    int mult;
    int sum;
    int div;
    int step;
    int k;

    if (g_90ee < 8)
        mult = 4;
    else
        mult = 2;
    g_92a4 = size = (g_6e24[g_7090[g_9646].fd6].f7a
                     + (g_6e24[g_7090[g_9646].fd6].f7b - 6) / 2) * mult;
    if (g_90f4 != 9 || !g_92be || g_92be == 2)
        fn_15_20ca();
    g_3d08[0].x = g_92c6;
    sum = g_3d08[0].y = g_92c8;
    g_3ce8[0] = 0;
    switch (g_9208) {
    case 0:
        a = 350;
        step = 16;
        div = 4;
        break;
    case 1:
        a = 450;
        step = 27;
        div = 5;
        break;
    case 2:
        a = 550;
        step = 39;
        div = 6;
        break;
    case 3:
        a = 650;
        step = 50;
        div = 7;
        break;
    }
    if (g_90f4 == 9) {
        k = g_3d08[0].x;
        i = sum = 0;
        for (; i < 16; i++) {
            if (!g_92be) {
                g_3d08[i].x = (i * i + 125L) * k * 12 / 7200;
                g_3d08[i].y = g_3d08[i].x * (i * 6 + 10) / 100;
            } else if (g_92be == 2) {
                g_3d08[i].x = ((long)(i * i) * 14 + 1800) * k / 6000;
                g_3d08[i].y = g_3d08[i].x * 40 / 100;
            }
            g_3ce8[i] = sum;
            sum += g_3d08[i].y;
        }
        k = 15;
    } else {
        for (i = 1; i < 10; i++, a -= step) {
            g_3ce8[i] = sum;
            g_3d08[i].x = g_3d08[0].x / div * (a / 10) / 10;
            g_3d08[i].y = g_3d08[i].x * 40 / 100;
            sum += g_3d08[i].y;
        }
        b = 100;
        a = 10;
        for (i = 0; i < 6; i++, a += 2, b -= 12) {
            g_3ce8[15 - i] = sum;
            g_3d08[15 - i].x = g_3d08[0].x / div * a / 10;
            g_3d08[15 - i].y = g_3d08[15 - i].x * b / 100;
            sum += g_3d08[15 - i].y;
        }
        k = 0;
    }
    g_929e = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(g_929e, g_92b2);
    if (g_920e)
        oldpal = SelectPalette(g_929e, g_920e, 0);
    if (g_3ccc[0]) {
        SelectObject(g_3cdc[0], g_3cd0[0]);
        SelectPalette(g_3cdc[0], g_3ce0[0], 0);
        DeleteDC(g_3cdc[0]);
        g_3cdc[0] = 0;
        DeleteObject(g_3ccc[0]);
        g_3ccc[0] = 0;
    }
    g_3ccc[0] = CreateCompatibleBitmap(g_929e, g_3d08[k].x, sum);
    g_3cdc[0] = CreateCompatibleDC(g_929e);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    if (g_920e)
        g_3ce0[0] = SelectPalette(g_3cdc[0], g_920e, 0);
    PatBlt(g_3cdc[0], 0, 0, g_3d08[k].x, sum, BLACKNESS);
    SetStretchBltMode(g_3cdc[0], 3);
    if (g_90f4 == 9 && g_92be == 2)
        fn_07_13b2(1, 20, 0);
    if (!g_0928) {
        for (i = 0; i < 16; i++) {
            fn_10_9962(0, g_3cdc[0], 0, g_3ce8[i], g_3d08[i].x, g_3d08[i].y, g_929e, 0, 0,
                       size, size, SRCCOPY);
            if (g_90f4 == 9 && g_92be == 2 && i > 6)
                fn_07_158e();
        }
    }
    SelectObject(g_3cdc[0], g_3cd0[0]);
    g_3ccc[1] = fn_10_6ec6(g_3ccc[0]);
    g_3cdc[1] = CreateCompatibleDC(g_13dc);
    g_3cd0[1] = SelectObject(g_3cdc[1], g_3ccc[1]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    SelectObject(g_929e, oldbmp);
    if (oldpal)
        SelectPalette(g_929e, oldpal, 0);
    DeleteDC(g_929e);
    if (k == 15) {
        g_92d6 -= g_3d08[15].y + 10;
        fn_10_993a(3, 0x31);
        fn_10_993a(2, 0x49);
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_15_20ca(void)
{
    g_92a2 = 4;
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

/* Sets up the trapezoid view geometry (g_3c8c) and its memory DC [inferred]. */
/* @addr 15:482e */
void far fn_15_482e(void)
{
    long l1, l2;
    g_3ce4 = (g_90ec * 4 / 3 - 1100) / 22 + 139;
    g_3ce6 = (g_90ec * 4 / 3 - 1100) / 36 + 164;
    g_92dc = 200;
    g_3c8c[0].x = g_3ce6 / 2 - g_3ce4 / 2;
    g_3c8c[0].y = 1;
    g_3c8c[1].x = g_3ce4 / 2 + g_3ce6 / 2;
    g_3c8c[1].y = 1;
    g_3c8c[2].x = g_3ce6;
    g_3c8c[2].y = (g_90ec * 4 / 3 - 1100) / 30 + 80;
    g_3c8c[3].x = 0;
    g_3c8c[3].y = g_3c8c[2].y;
    l1 = (g_3c8c[0].y - g_3c8c[3].y) * 100 / (g_3c8c[0].x - g_3c8c[3].x);
    l2 = (g_3c8c[1].y - g_3c8c[2].y) * 100 / (g_3c8c[1].x - g_3c8c[2].x);
    g_3c9c = g_90ec * 4 / 3 / 2 - g_3ce6 / 2;
    g_3c9e = 0;
    g_3ca0 = ((l1 - l2) * g_3c9c - l2 * g_3ce6) / (l1 - l2);
    g_3ca2 = l1 * (g_3ca0 - g_3c9c) / 100 + g_0010 - 0x34;
    if (g_92b6) {
        SelectObject(g_92b6, g_92aa);
        if (g_920e)
            SelectPalette(g_92b6, g_92bc, 0);
        DeleteObject(g_92a8);
        DeleteDC(g_92b6);
        g_92b6 = g_92a8 = 0;
    }
    g_92b6 = CreateCompatibleDC(g_13dc);
    g_92a8 = CreateCompatibleBitmap(g_13dc, g_3ce6, g_3c8c[3].y + 0x34);
    g_92aa = SelectObject(g_92b6, g_92a8);
    if (g_920e)
        g_92bc = SelectPalette(g_92b6, g_920e, 0);
    PatBlt(g_92b6, 0, 0, g_3ce6, g_3c8c[3].y + 0x34, BLACKNESS);
    fn_15_4a2e();
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_15_0000(int a)
{
    return a;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_15_2a08(void)
{
    return g_92a2;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_15_4c76(int a, int b)
{
    g_92a2 = a + b;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_15_1584(int a)
{
    g_92a2 = a;
}

/* Builds the briefing text in g_4fcc: header, restored-game summary or
 * the default text resource, then the difficulty line [inferred]. */
/* @addr 15:52e4 */
void far fn_15_52e4(void)
{
    HGLOBAL hres;
    char far *lp;
    int v2;
    int i;
    int len2;
    int len1;
    int v1;
    int id;
    char buf[200];
    char name[220];
    char str[40];
    int space;
    HFILE hf;
    int min;
    int sec;
    int pad[8];
    DWORD size;
    long pad2;
    HGLOBAL hmem;
    REC_1A9 far *rec;
    OFSTRUCT of;

    g_93a8 = GlobalAlloc(GHND, 2000L);
    g_4fcc = GlobalLock(g_93a8);
    LoadString(g_9212, 0x24e, buf, 30);
    lstrcpy(g_4fcc, buf);
    v1 = fn_10_9764(1);
    v2 = fn_10_9764(0);
    if (v2 == 2)
        v2 = -41;
    fn_10_a332(g_4fcc, 0xbd8, 1, v2 != 3, v1 + 0x24f, v2 + 0x27f, v2 == 3, 0x282,
               (LPSTR)g_380c);
    lstrcpy(buf, g_9078);
    lstrcat(buf, g_96b8);
    GetPrivateProfileString(g_9690, "Restore", "", name, 9, g_96a9);
    for (i = space = 0; i < lstrlen(name); i++)
        if (name[i] == ' ')
            space = 1;
    if (!space) {
        lstrcat(buf, name);
        lstrcat(buf, ".sav");
        hf = OpenFile(buf, &of, 0);
        if (hf == -1)
            return;
        hmem = GlobalAlloc(GHND, 0x1a9L);
        GlobalLock(hmem);
        size = GlobalSize(hmem);
        GlobalUnlock(hmem);
        fn_14_4006(hf, (char huge *)(rec = (REC_1A9 far *)GlobalLock(
                                         hmem = GlobalReAlloc(hmem, size, GHND))), size);
        _lclose(hf);
        rec->f18b = rec->f18b / 36;
        min = (int)rec->f18b / 60;
        sec = (int)rec->f18b - min * 60;
        if (rec->f15e >= 100)
            rec->f15e -= 100;
        if (rec->f32 == rec->f160) {
            if (rec->f160 == 1)
                LoadString(g_9212, 0x9c7, str, 40);
            else
                LoadString(g_9212, 0x9c5, str, 40);
        } else if (rec->f160 == 0) {
            if (rec->f32 > 1)
                LoadString(g_9212, 0x9c6, str, 40);
            else
                LoadString(g_9212, 0x9e1, str, 40);
        } else
            fn_10_a332(str, 0x9c4, 1, rec->f160);
        fn_10_a332(g_4fcc, 0xbb8, 0, 0, rec->f24, min, 0x9c9, sec, 0x9c8, rec->f32, 0x13e,
                   (LPSTR)str);
        if (rec->f15a || rec->f15c)
            fn_10_a332(g_4fcc, 0xbb9, 0, rec->f156 + rec->f158, 0x9d3, rec->f15a, rec->f15a,
                       0x9d3, rec->f15c, rec->f15c, 0x9d3);
        fn_10_a332(g_4fcc, 0xbd7, 0, rec->f164 > 400, rec->f15e + 0x137);
        GlobalUnlock(hmem);
        GlobalFree(hmem);
    } else {
        lp = 0;
        hres = LoadResource(g_9212, FindResource(g_9212, MAKEINTRESOURCE(210),
                                                 MAKEINTRESOURCE(5000)));
        if (hres)
            lp = LockResource(hres);
        len1 = lstrlen(lp);
        len2 = lstrlen(g_4fcc);
        for (i = 0; i < len1; i++, len2++)
            g_4fcc[len2] = lp[i];
        if (lp) {
            GlobalUnlock(hres);
            lp = 0;
        }
        if (hres) {
            FreeResource(hres);
            hres = 0;
        }
    }
    switch (g_9214) {
    case 1:
        id = 0xeb;
        break;
    case 2:
        id = 0xec;
        break;
    case 4:
        id = 0xf0;
    case 3:
        id = 0x288;
        break;
    default:
        id = 0x288;
        break;
    }
    fn_10_a332(g_4fcc, 0xbd6, 0, g_9214 != 3, g_9214 == 3, !g_9214, g_9214 != 0, id,
               (LPSTR)g_380c);
    fn_11_3fd4(g_4fcc, 1);
    fn_15_1584(1);
}

/* near-match 41%: 15:454c (draws the shaded side walls and the four
 * perspective lines [inferred]). Frame and first 0xad bytes match; the game
 * subtracts the spilled x0 straight from memory, and in the loop keeps
 * (int)i in dx/si where CL 8 picks cx and recomputes. */
void far fn_15_454c(void)
{
    HGDIOBJ oldbrush;
    int c[3];
    int k;
    int x0;                     /* x0, xa, mid, xb, h, y1, y2: register locals */
    POINT pt;
    int ytop;
    int xa, mid, xb, h, y1;
    int ybot;
    int y2;
    long i;
    long dy1;
    long dy2;
    long w;
    long dh;
    HGDIOBJ oldpen;
    HDC dc;

    dc = g_9580 ? g_9580 : g_13dc;
    x0 = g_6dac + g_6db4;
    xa = x0 + 2;
    ytop = g_6dae + g_6db6;
    mid = g_90ea / 2;
    xb = mid - 90;
    y1 = (long)(mid - xa - 90) * (g_3ca2 - g_6db6) / (mid - xa) + g_6db6;
    y2 = ytop + (long)(mid - xa - 90) * (g_3ca2 - ytop) / (mid - xa);
    w = xb - x0;
    dh = ytop - (ybot = g_6db6);
    dy1 = y1 - g_6db6;
    dy2 = y2 - ytop;
    for (i = 0; i < w; i += 2) {
        for (k = 0; k < 3; k++)
            c[k] = i * -150 / w + 170;
        pt.x = g_6dac + g_6db4 + (int)i;
        pt.y = dy1 * i / w + ybot;
        h = (dy2 - dy1) * i / w + dh;
        oldbrush = SelectObject(dc, CreateSolidBrush(PALETTERGB(c[0], c[1], c[2])));
        PatBlt(dc, pt.x, pt.y, 2, h, PATCOPY);
        pt.x = g_6db0 - 2 - (int)i;
        PatBlt(dc, pt.x, pt.y, 2, h + 2, PATCOPY);
        DeleteObject(SelectObject(dc, oldbrush));
    }
    oldpen = SelectObject(dc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
    MoveTo(dc, g_6dac + g_6db4 + 2, ybot - 1);
    LineTo(dc, g_90ea / 2, g_3ca2);
    MoveTo(dc, g_6dac + g_6db4 + 2, ytop);
    LineTo(dc, g_90ea / 2, g_3ca2 + 2);
    MoveTo(dc, g_6db0 - 2, ybot);
    LineTo(dc, g_90ea / 2, g_3ca2);
    MoveTo(dc, g_6db0 - 2, ytop);
    LineTo(dc, g_90ea / 2, g_3ca2);
    DeleteObject(SelectObject(dc, oldpen));
}
