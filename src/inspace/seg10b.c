/* @cflags /AM /G2 /Gw /Gs /Os */
/* INSPACE.EXE segment 10 (selector 1048): source file 21 of
 * inventory/files.tsv (10:0000..10:39a8), compiled with /G2: the long
 * conditional jumps are jcc+jmp pairs (no 386 jcc rel16) [inferred]. */
#include "inspace.h"

extern HGLOBAL g_94ae;
extern HGLOBAL g_95a4;
extern void far *g_69f4;
extern void far *g_6e24;
extern int g_94a2;
extern int g_94a4;
extern int g_931a;
extern int g_90f4;
extern HDC g_39e8[];
extern HPALETTE g_3a5c[];
extern HBITMAP g_3974[];
extern HBITMAP g_3ad0[];
typedef struct {
    HDC dc1;            /* +0x00 */
    HDC dc2;            /* +0x02 */
    HBITMAP bm1;        /* +0x04 */
    HBITMAP bm2;        /* +0x06 */
    HBITMAP old1;       /* +0x08 */
    HBITMAP old2;       /* +0x0a */
    HPALETTE pal;       /* +0x0c */
    char rest[0x14];
} SURF_22;              /* 34-byte records at DS:9168 [inferred: off-screen surfaces] */
extern SURF_22 g_9168[];
#pragma pack(1)
typedef struct {
    int f00;            /* +0x00 */
    int f02;            /* +0x02 */
    char p04[0x26];
    int f2a;            /* +0x2a */
    char p2c[0x68 - 0x2c];
    POINT f68[2];       /* +0x68 */
    char rest[0xad - 0x70];
} REC_AD;               /* 173-byte records at DS:96d2 */
#pragma pack()
extern REC_AD g_96d2[];
extern POINT g_7b60[][64];
extern POINT g_7ba0[][64];
extern POINT g_7be0[][4][16];
int far fn_06_720c(int a);
int far fn_06_71b2(int a);
typedef struct {
    int f00;
    int f02;
    int f04;
    int f06;
    int f08;
    int f0a;
    int f0c;
    int f0e;
    char rest[0x24 - 0x10];
} REC_24;
extern REC_24 g_52f4[];
typedef struct {
    char p00[4];
    long f04;
    char p08[0x10];
    int f18;
    char rest[0x70 - 0x1a];
} REC_70;
extern REC_70 far *g_1e00;
extern int g_92f0;
void far fn_15_5932(void);
void far fn_10_022e(int a);
void far fn_10_0552(int i, int a);
void far fn_10_0136(void);
void far fn_10_3864(void);
void far fn_10_37d0(int i);
void far fn_16_631c(void);
void far fn_18_03d6(void);
void far fn_15_14be(void);
void far fn_11_02f0(void);
void far fn_10_7d8e(void);
void far fn_12_26a4(int a, int b);
void far fn_09_8908(void);
void far fn_09_699e(void);
void far fn_10_5cfa(void);
void far fn_10_5c1a(void);
void far fn_09_1092(void);
void far fn_07_49b6(void);
extern int g_001a;
extern int g_92ec[];
extern HDC g_5e98[4];
extern HGDIOBJ g_5ea0[4];
void far fn_10_0522(int a);
void far fn_10_7480(int a, int b);
void far fn_15_1328(int a);
void far fn_06_626c(void);
void far fn_18_0ba0(void);
extern HDC g_929a;
extern HBITMAP g_9296;
extern HPALETTE g_92a0;
extern HBITMAP g_9294;
extern HGDIOBJ g_3820[2];
extern HGDIOBJ g_5ea8[2];
extern HINSTANCE g_9210;
extern int g_3824[8][8];
typedef struct {
    int a;
    int b;
    int c;
} REC_6;
extern REC_6 g_38a4[6];             /* keys of surfaces 23..27 [inferred] */
typedef struct {
    char p00;
    char f01;           /* +0x01 */
    char p02[0x0e - 0x02];
    int f0e;            /* +0x0e */
    int f10;            /* +0x10 */
    char rest[0x14 - 0x12];
} REC_14B;              /* = seg17's REC_14 at DS:4d92 seen 2 bytes earlier [inferred] */
extern REC_14B g_4d90[];
extern int g_4ed4[];

/* @addr 10:3864 */
void far fn_10_3864(void)
{
    if (g_94ae) {
        if (g_69f4) {
            GlobalUnlock(g_94ae);
            g_69f4 = 0;
        }
        GlobalFree(g_94ae);
        g_94ae = 0;
    }
    if (g_95a4) {
        if (g_6e24) {
            GlobalUnlock(g_95a4);
            g_6e24 = 0;
        }
        GlobalFree(g_95a4);
        g_95a4 = 0;
    }
    g_931a = g_94a2 = g_94a4 = 0;
}

/* @addr 10:01fe */
int far fn_10_01fe(void)
{
    switch (g_90f4) {
    case 0:
        fn_15_5932();
        break;
    case 1:
        fn_10_022e(1);
        break;
    }
    return 1;
}

/* Shutdown [inferred]: frees the game's surfaces, DCs and other
 * resources; a != 0 also calls fn_10_7d8e. */
/* @addr 10:022e */
void far fn_10_022e(int a)
{
    int i;
    int j;

    g_001a = 1;
    fn_16_631c();
    fn_18_03d6();
    fn_15_14be();
    fn_10_0136();
    fn_10_3864();
    fn_11_02f0();
    if (a)
        fn_10_7d8e();
    for (i = 0; i <= 14; i++)
        for (j = 0; j < g_92ec[i]; j++)
            fn_12_26a4(i, j);
    fn_09_8908();
    fn_09_699e();
    fn_10_5cfa();
    for (i = 0; i <= 5; i++)
        g_38a4[i].a = g_38a4[i].b = -1;
    for (i = 0; i < 4; i++) {
        if (g_5e98[i]) {
            SelectObject(g_5e98[i], g_5ea0[i]);
            DeleteDC(g_5e98[i]);
            g_5e98[i] = 0;
        }
    }
    for (i = 0; i < 3; i++)
        fn_10_37d0(i);
    fn_10_5c1a();
    fn_09_1092();
    fn_07_49b6();
}

/* @addr 10:0522 */
void far fn_10_0522(int a)
{
    int i;

    for (i = 0; i < 58; i++)
        fn_10_0552(i, a);
}

/* @addr 10:0552 */
void far fn_10_0552(int i, int force)
{
    if (g_39e8[i]) {
        if (!force) {
            if (i == 4 || i == 5 || i == 6 || i == 7)
                return;
            if (i >= 10 && i < 13)
                return;
            if (i == 1 || i == 2 || i == 22 || i == 8 || i == 9 || i == 34)
                return;
        }
        if (g_3a5c[i])
            SelectPalette(g_39e8[i], g_3a5c[i], 0);
        SelectObject(g_39e8[i], g_3974[i]);
        DeleteDC(g_39e8[i]);
        g_39e8[i] = 0;
        if (g_3ad0[i]) {
            DeleteObject(g_3ad0[i]);
            g_3ad0[i] = 0;
        }
    }
}

/* @addr 10:1eb6 */
void far fn_10_1eb6(int a)
{
    int i;
    int u;

    i = a + 40;
    if (g_39e8[i]) {
        if (g_3a5c[i])
            SelectPalette(g_39e8[i], g_3a5c[i], 0);
        SelectObject(g_39e8[i], g_3974[i]);
        DeleteDC(g_39e8[i]);
        g_39e8[i] = 0;
        if (g_3ad0[i]) {
            DeleteObject(g_3ad0[i]);
            g_3ad0[i] = 0;
        }
    }
}

/* @addr 10:061a */
void far fn_10_061a(void)
{
    int i;

    for (i = 0; i < 58; i++) {
        if (g_39e8[i]) {
            if (g_3a5c[i])
                SelectPalette(g_39e8[i], g_3a5c[i], 0);
            SelectObject(g_39e8[i], g_3974[i]);
            DeleteDC(g_39e8[i]);
            g_39e8[i] = 0;
            if (g_3ad0[i]) {
                DeleteObject(g_3ad0[i]);
                g_3ad0[i] = 0;
            }
        }
    }
}

/* @addr 10:1f30 */
void far fn_10_1f30(int a, int b)
{
    int i;
    int j;
    HDC dc;
    HBITMAP bm;
    HBITMAP old;
    HPALETTE pal;

    j = b + 40;
    i = a + 40;
    dc = g_39e8[i];
    bm = g_3ad0[i];
    old = g_3974[i];
    pal = g_3a5c[i];
    g_39e8[i] = g_39e8[j];
    g_3ad0[i] = g_3ad0[j];
    g_3974[i] = g_3974[j];
    g_3a5c[i] = g_3a5c[j];
    g_39e8[j] = dc;
    g_3ad0[j] = bm;
    g_3974[j] = old;
    g_3a5c[j] = pal;
}

/* @addr 10:37d0 */
void far fn_10_37d0(int i)
{
    if (g_9168[i].dc1) {
        SelectObject(g_9168[i].dc1, g_9168[i].old1);
        if (g_920e)
            SelectPalette(g_9168[i].dc1, g_9168[i].pal, 0);
        DeleteDC(g_9168[i].dc1);
        DeleteObject(g_9168[i].bm1);
        g_9168[i].dc1 = 0;
    }
    if (g_9168[i].dc2) {
        SelectObject(g_9168[i].dc2, g_9168[i].old2);
        DeleteDC(g_9168[i].dc2);
        DeleteObject(g_9168[i].bm2);
        g_9168[i].dc2 = 0;
    }
}

/* @addr 10:1620 */
void far fn_10_1620(int i)
{
    int w;
    int j;
    int r;
    int ang;

    w = g_96d2[i].f2a;
    r = g_96d2[i].f02;
    for (j = 0, ang = 270; j < 16; j++, ang -= j % 2 + 22) {
        g_7ba0[i][j].x = fn_06_720c(ang) * r / 127 + w / 2;
        g_7ba0[i][j].y = w / 2 + fn_06_71b2(ang) * r / -127;
    }
}

/* @addr 10:1460 */
void far fn_10_1460(int i)
{
    int w;
    int j;
    int r;
    int ang;

    w = g_96d2[i].f2a;
    r = g_96d2[i].f00 + 3;
    for (j = 0, ang = 450; j < 16; j++, ang -= j % 2 + 22) {
        g_7b60[i][j].x = fn_06_720c(ang) * r / 128 + w / 2;
        g_7b60[i][j].y = w / 2 - fn_06_71b2(ang) * r / 128;
    }
}

/* @addr 10:069a */
void far fn_10_069a(void)
{
    int i;

    for (i = 0; i < g_92f0; i++) {
        g_1e00[i].f18 = 1;
        g_52f4[i].f08 = -1;
        g_52f4[i].f0a = 0;
        g_52f4[i].f0c = 0;
        g_52f4[i].f00 = 0;
        g_52f4[i].f02 = 0;
        switch (i / 8) {
        case 0:
            g_52f4[i].f0e = 0x11;
            break;
        case 1:
            g_52f4[i].f0e = 0xd;
            break;
        case 2:
            g_52f4[i].f0e = 0xb;
            break;
        case 3:
            g_52f4[i].f0e = 9;
            break;
        }
    }
}

/* @addr 10:0136 */
void far fn_10_0136(void)
{
    int i;

    fn_10_7480(-1, 1);
    fn_15_1328(1);
    fn_10_0522(0);
    fn_06_626c();
    fn_18_0ba0();
    if (g_929a) {
        SelectObject(g_929a, g_9296);
        if (g_92a0)
            SelectPalette(g_929a, g_92a0, 0);
        DeleteDC(g_929a);
        DeleteObject(g_9294);
        g_929a = g_9294 = 0;
    }
    for (i = 0; i < 2; i++) {
        if (g_3820[i]) {
            DeleteObject(g_3820[i]);
            g_3820[i] = 0;
        }
        if (g_5ea8[i]) {
            DeleteObject(g_5ea8[i]);
            g_5ea8[i] = 0;
        }
    }
}

/* Loads the 8x8 int table g_3824 from resource 0x87 of type 0x15e0 in
 * library g_9210. */
/* @addr 10:38e0 */
void far fn_10_38e0(void)
{
    int i;
    int j;
    int k;
    HGLOBAL hg;
    HRSRC hr;
    int far *p;
    long size;

    p = 0;
    hr = FindResource(g_9210, MAKEINTRESOURCE(0x87), MAKEINTRESOURCE(0x15e0));
    if (hr) {
        SizeofResource(g_9210, hr);
        hg = LoadResource(g_9210, hr);
        if (hg)
            p = (int far *)LockResource(hg);
    }
    for (i = k = 0; i < 8; i++)
        for (j = 0; j < 8; j++, k++)
            g_3824[i][j] = p[k];
    if (p) {
        GlobalUnlock(hg);
        p = 0;
    }
    if (hg)
        FreeResource(hg);
}

/* Frees surfaces 23..27 (g_39e8 DCs) whose key in g_38a4 matches neither
 * of the two entries g_4ed4[0..1]. */
/* @addr 10:1dd8 */
void far fn_10_1dd8(void)
{
    int i;
    int j;
    int found;

    for (i = 23; i < 28; i++) {
        if (g_39e8[i]) {
            for (j = found = 0; j < 2; j++)
                if (g_4d90[g_4ed4[j]].f10 == g_38a4[i - 23].b &&
                    g_4d90[g_4ed4[j]].f0e == g_38a4[i - 23].a &&
                    g_4d90[g_4ed4[j]].f01 == g_38a4[i - 23].c)
                    found = 1;
            if (!found) {
                if (g_3a5c[i])
                    SelectPalette(g_39e8[i], g_3a5c[i], 0);
                SelectObject(g_39e8[i], g_3974[i]);
                DeleteDC(g_39e8[i]);
                g_38a4[i - 23].a = g_38a4[i - 23].b = g_39e8[i] = 0;
                if (g_3ad0[i]) {
                    DeleteObject(g_3ad0[i]);
                    g_3ad0[i] = 0;
                }
            }
        }
    }
}

/* Fills g_7be0[i][k] (k = 0, 1) with 16 points of an ellipse with radii
 * g_96d2[i].f68[k], centred in a g_96d2[i].f2a square. */
/* @addr 10:1502 */
void far fn_10_1502(int i)
{
    int w;
    int j;
    int k;
    int rx[2];
    int ry[2];
    int ang;

    w = g_96d2[i].f2a;
    for (j = 0; j < 2; j++) {
        rx[j] = g_96d2[i].f68[j].x;
        ry[j] = g_96d2[i].f68[j].y;
    }
    for (k = 0; k < 2; k++) {
        for (ang = j = 0; j < 16; j++, ang += j % 2 + 22) {
            g_7be0[i][k][j].x = w / 2 + (fn_06_720c(ang) * rx[k] - fn_06_71b2(ang) * ry[k]) / 128;
            g_7be0[i][k][j].y = (fn_06_71b2(ang) * rx[k] + fn_06_720c(ang) * ry[k]) / 128 + w / 2;
        }
    }
}
