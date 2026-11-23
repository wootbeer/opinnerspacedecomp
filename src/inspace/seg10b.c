/* @cflags /AM /G2 /Gw /Gs /Os */
/* INSPACE.EXE segment 10 (selector 1048): source file 21 of
 * inventory/files.tsv (10:0000..10:39a8), compiled with /G2: the long
 * conditional jumps are jcc+jmp pairs (no 386 jcc rel16) [inferred]. */
#include "inspace.h"
#include <stdlib.h>

/* g_05a0 is declared long in inspace.h; this code reads its two words
 * (world width and height [inferred]). */
#define G_05A0_LO (((int *)&g_05a0)[0])
#define G_05A0_HI (((int *)&g_05a0)[1])

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
    int f04;            /* +0x04 */
    char p06[0x24];
    int f2a;            /* +0x2a */
    char p2c[0x50 - 0x2c];
    POINT f50[5];       /* +0x50 */
    char p64[0x68 - 0x64];
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
typedef struct {
    int f00;            /* +0x00 */
    int f02;            /* +0x02 */
    POINT f04;          /* +0x04: position [inferred] */
    int f08;            /* +0x08 */
    int f0a;            /* +0x0a */
    int f0c;            /* +0x0c */
    int f0e;            /* +0x0e */
    char p10[0x18 - 0x10];
    int f18;            /* +0x18 */
    char p1a[0x26 - 0x1a];
    int f26;            /* +0x26 */
    char p28[0x2e - 0x28];
    char f2e;           /* +0x2e */
    char f2f;           /* +0x2f */
    char p30[0x50 - 0x30];
    char f50;           /* +0x50 */
    char p51[0x54 - 0x51];
    char f54;           /* +0x54 */
    char p55[0x6a - 0x55];
    void far *f6a;      /* +0x6a */
    char rest[0x70 - 0x6e];
} REC_70S;              /* the 0x70-byte records of g_1df8 */
extern REC_70S far *g_1df8[];
extern REC_70S far *g_1e1c;
extern REC_70S far *g_1e04;
int far fn_09_88ba(int a);
void far fn_11_01e0(void);
void far fn_10_061a(void);
extern HGDIOBJ g_3b88[];
extern HGDIOBJ g_3b44[4];
extern HGDIOBJ g_576c[20];
extern HGDIOBJ g_3b74[10];
extern HGDIOBJ g_3b4c[20];
extern HDC g_95c2;
extern HPALETTE g_95c4;
extern HBITMAP g_95c0;
extern HBITMAP g_95be;
extern HGLOBAL g_9100[15];
extern HGLOBAL g_92e0;
extern void far *g_3d4c;
extern HGLOBAL g_912a;
extern HGDIOBJ g_912c;
extern int g_9156;
extern int g_06d6[5];
extern int g_06e0[5];
extern int g_90ea;
extern int g_90ec;
extern int g_9150;
extern int g_1016;
extern int g_9134;
extern int flow_interactive;        /* DS:95bc */
extern int subgame_active;          /* DS:9130 */
extern char g_380c[];
extern char g_9690[];
extern char g_96a9[];
extern int g_92e6;
extern int g_91fa;
extern WORD g_06c6[8];
extern WORD g_06b6[8];
void far fn_15_5786(void);
void far fn_10_6e76(long a);
void far fn_10_6e4c(void);
void far fn_10_5c42(void);
void far fn_10_1fb2(void);
void far fn_10_73e2(void);
void far fn_15_6640(void);
void far fn_09_22b4(int a);
void far fn_10_2ffa(void);
void far fn_10_4b2e(void);
void far fn_11_0000(void);
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
    char f00;
    char f01;           /* +0x01 */
    char f02;
    char f03;
    char f04;
    char f05;
    char f06;
    char f07;
    int f08;
    int f0a;
    int f0c;
    int f0e;            /* +0x0e */
    int f10;            /* +0x10 */
    int f12;            /* +0x12: string id */
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
/* near-match 76%: 10:1502 (the y line: the original multiplies the first
 * call result at once; CL here spills it and needs 2 more stack bytes) */
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
            g_7be0[i][k][j].y = (fn_06_720c(ang) * ry[k] + fn_06_71b2(ang) * rx[k]) / 128 + w / 2;
        }
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_1fb2(void)
{
    g_90f4 = 1;
}

/* Fills in the table of 12 0x14-byte records at DS:4da4 (string ids
 * 0x87a-0x885) [inferred: weapon or device stats]. */
/* @addr 10:2ffa */
void far fn_10_2ffa(void)
{
    char buf[40];

    g_4d90[1].f12 = 0x87a;
    g_4d90[2].f12 = 0x87b;
    g_4d90[3].f12 = 0x87c;
    g_4d90[4].f12 = 0x87d;
    g_4d90[5].f0e = 0x26c;
    g_4d90[5].f0a = 0x384;
    g_4d90[5].f0c = 0xc8;
    g_4d90[5].f12 = 0x87e;
    g_4d90[6].f0a = 0x258;
    g_4d90[1].f07 = 8;
    g_4d90[2].f07 = 8;
    g_4d90[6].f07 = 8;
    g_4d90[6].f12 = 0x87f;
    g_4d90[7].f03 = 0xb;
    g_4d90[5].f10 = 0x262;
    g_4d90[6].f10 = 0x262;
    g_4d90[7].f10 = 0x262;
    g_4d90[7].f0a = 0x3e8;
    g_4d90[7].f12 = 0x880;
    g_4d90[1].f03 = 5;
    g_4d90[7].f05 = 5;
    g_4d90[7].f07 = 5;
    g_4d90[8].f03 = 5;
    g_4d90[8].f10 = 0x276;
    g_4d90[8].f0a = 0xfa;
    g_4d90[8].f07 = 7;
    g_4d90[8].f12 = 0x881;
    g_4d90[10].f10 = 0x2bc;
    g_4d90[10].f0a = 0x190;
    g_4d90[7].f0c = 0x64;
    g_4d90[8].f0c = 0x64;
    g_4d90[10].f0c = 0x64;
    g_4d90[2].f03 = 4;
    g_4d90[2].f05 = 4;
    g_4d90[5].f05 = 4;
    g_4d90[10].f03 = 4;
    g_4d90[10].f07 = 4;
    g_4d90[10].f12 = 0x882;
    g_4d90[9].f03 = -1;
    g_4d90[9].f0e = 0x352;
    g_4d90[9].f10 = -1;
    g_4d90[1].f05 = 3;
    g_4d90[5].f01 = 3;
    g_4d90[6].f01 = 3;
    g_4d90[10].f05 = 3;
    g_4d90[9].f01 = 3;
    g_4d90[1].f00 = 1;
    g_4d90[1].f06 = 1;
    g_4d90[2].f00 = 1;
    g_4d90[2].f06 = 1;
    g_4d90[3].f00 = 1;
    g_4d90[3].f07 = 1;
    g_4d90[4].f00 = 1;
    g_4d90[4].f07 = 1;
    g_4d90[5].f03 = 1;
    g_4d90[5].f02 = 1;
    g_4d90[5].f04 = 1;
    g_4d90[7].f02 = 1;
    g_4d90[10].f01 = 1;
    g_4d90[9].f02 = 1;
    g_4d90[3].f03 = 0;
    g_4d90[3].f05 = 0;
    g_4d90[3].f06 = 0;
    g_4d90[4].f03 = 0;
    g_4d90[4].f05 = 0;
    g_4d90[4].f06 = 0;
    g_4d90[6].f02 = 0;
    g_4d90[6].f04 = 0;
    g_4d90[7].f04 = 0;
    g_4d90[8].f02 = 0;
    g_4d90[8].f04 = 0;
    g_4d90[10].f02 = 0;
    g_4d90[10].f04 = 0;
    g_4d90[9].f04 = 0;
    g_4d90[9].f0a = 0x1f40;
    g_4d90[6].f0c = 0x3c;
    g_4d90[9].f0c = 0x3c;
    g_4d90[5].f07 = 6;
    g_4d90[6].f05 = 6;
    g_4d90[9].f05 = 6;
    g_4d90[6].f03 = 0xa;
    g_4d90[9].f07 = 0xa;
    g_4d90[9].f12 = 0x883;
    g_4d90[5].f00 = 2;
    g_4d90[6].f00 = 2;
    g_4d90[7].f00 = 2;
    g_4d90[7].f01 = 2;
    g_4d90[8].f00 = 2;
    g_4d90[8].f01 = 2;
    g_4d90[8].f05 = 2;
    g_4d90[10].f00 = 2;
    g_4d90[9].f00 = 2;
    g_4d90[11].f00 = 2;
    g_4d90[11].f03 = 0x10;
    g_4d90[6].f0e = 0x280;
    g_4d90[7].f0e = 0x280;
    g_4d90[8].f0e = 0x280;
    g_4d90[10].f0e = 0x280;
    g_4d90[11].f0e = 0x280;
    g_4d90[11].f10 = 0x262;
    g_4d90[11].f0a = 0x96;
    g_4d90[11].f0c = 0x64;
    g_4d90[11].f01 = 4;
    g_4d90[11].f05 = 4;
    g_4d90[11].f07 = 8;
    g_4d90[11].f12 = 0x884;
    g_4d90[12].f03 = 0xe;
    g_4d90[12].f0e = 0x280;
    g_4d90[12].f10 = 0x2bc;
    g_4d90[12].f00 = 2;
    g_4d90[12].f01 = 2;
    g_4d90[12].f02 = 1;
    g_4d90[11].f02 = 0;
    g_4d90[11].f04 = 0;
    g_4d90[12].f04 = 0;
    g_4d90[12].f0a = 0x514;
    g_4d90[12].f0c = 0x32;
    g_4d90[12].f05 = 7;
    g_4d90[12].f07 = 6;
    g_4d90[12].f12 = 0x885;
}

/* Game start-up for mode g_90f4 (1: loads the pilot name, "Otto-Pilot"
 * in a demo [inferred], waits 2 s, makes the two 8x8 pattern brushes).
 * The pattern inversion loop is never reached: its condition (an
 * unsigned GetVersion() < 0) is always false; the exact original form is
 * [inferred], a while/break gives the game's layout. */
/* @addr 10:0000 */
int far fn_10_0000(void)
{
    DWORD t;
    int u[5];
    int i;

    subgame_active = 0;
    if (g_90f4 == 0) {
        fn_15_5786();
        return 1;
    }
    if (g_90f4 == 1) {
        g_1016 = g_001a = 0;
        fn_10_6e76(8L);
        fn_10_6e4c();
        fn_10_0522(0);
        fn_10_5c42();
        fn_10_1fb2();
        fn_10_73e2();
        if (g_9134 && !flow_interactive)
            lstrcpy(g_380c, "Otto-Pilot");
        else
            GetPrivateProfileString(g_9690, "ThePlayer", "", g_380c, 12, g_96a9);
        t = GetCurrentTime() + 2000;
        fn_15_6640();
        g_92e6 = 0;
        fn_09_22b4(0);
        fn_10_2ffa();
        do
            ;
        while (GetCurrentTime() < t);
        g_91fa = 0;
        fn_10_4b2e();
        while (GetVersion() < 0) {      /* never true: DWORD < 0 */
            for (i = 0; i < 8; i++)
                g_06c6[i] ^= 0xff;
            break;
        }
        g_3820[0] = CreateBitmap(8, 8, 1, 1, g_06c6);
        g_5ea8[0] = CreatePatternBrush(g_3820[0]);
        g_3820[1] = CreateBitmap(8, 8, 1, 1, g_06b6);
        g_5ea8[1] = CreatePatternBrush(g_3820[1]);
        fn_11_0000();
    }
    return 1;
}

/* Puts object n of list 0 at a random place in the world, at least 150
 * from the left/top edge [inferred], retrying while it lands inside the
 * view centred on the world. */
/* near-match 99%: 10:0736 (two register choices differ: ax/si for the
 * record offset at the f02 store, si/bx for the rect right edge) */
void far fn_10_0736(int n)
{
    int again;
    RECT rc;

    again = 1;
    do {
        g_1df8[0][n].f54 = 0;
        g_1df8[0][n].f04.x = (rand() % (G_05A0_LO - 150) + 150) << 3;
        g_1df8[0][n].f04.y = (rand() % (G_05A0_HI - 150) + 150) << 3;
        g_1df8[0][n].f00 = g_1df8[0][n].f08 = -1000;
        g_1df8[0][n].f02 = g_1df8[0][n].f0a = -1000;
        g_1df8[0][n].f2f = 0;
        again = 0;
        SetRect(&rc, (G_05A0_LO / 2 - g_90ea / 2) << g_9150,
                (G_05A0_HI / 2 - g_90ec / 2) << g_9150,
                (g_90ea / 2 + G_05A0_LO / 2) << g_9150,
                (G_05A0_HI / 2 + g_90ec / 2) << g_9150);
        if (PtInRect(&rc, g_1df8[0][n].f04))
            again = 1;
    } while (again);
}

/* Like fn_10_0736 for object n of g_1e1c, also with a random speed
 * (-24..25 each way [inferred]) and a random f26 below 900. */
/* near-match 99%: 10:0a26 (the same two register choices as 10:0736) */
void far fn_10_0a26(int n)
{
    int again;
    RECT rc;

    again = 1;
    do {
        g_1e1c[n].f04.x = (rand() % (G_05A0_LO - 150) + 150) << 3;
        g_1e1c[n].f04.y = (rand() % (G_05A0_HI - 150) + 150) << 3;
        g_1e1c[n].f00 = g_1e1c[n].f08 = -1000;
        g_1e1c[n].f02 = g_1e1c[n].f0a = -1000;
        g_1e1c[n].f0c = 25 - rand() % 50;
        g_1e1c[n].f0e = 25 - rand() % 50;
        g_1e1c[n].f18 = 0;
        g_1e1c[n].f2e = 0;
        g_1e1c[n].f26 = rand() % 900;
        SetRect(&rc, (G_05A0_LO / 2 - g_90ea / 2) << g_9150,
                (G_05A0_HI / 2 - g_90ec / 2) << g_9150,
                (G_05A0_LO / 2 + g_90ea / 2) << g_9150,
                (G_05A0_HI / 2 + g_90ec / 2) << g_9150);
        again = 0;
        if (PtInRect(&rc, g_1e1c[n].f04))
            again = 1;
    } while (again);
}

/* Like fn_10_0a26 for object n of g_1e04; a speed too slow on both axes
 * gets 20 added to x. */
/* near-match 99%: 10:0864 (the same two register choices as 10:0736) */
void far fn_10_0864(int n)
{
    int again;
    RECT rc;

    again = 1;
    do {
        g_1e04[n].f50 = 0;
        g_1e04[n].f04.x = (rand() % (G_05A0_LO - 150) + 150) << 3;
        g_1e04[n].f04.y = (rand() % (G_05A0_HI - 150) + 150) << 3;
        g_1e04[n].f00 = g_1e04[n].f08 = -1000;
        g_1e04[n].f02 = g_1e04[n].f0a = -1000;
        g_1e04[n].f0c = 25 - rand() % 50;
        g_1e04[n].f0e = 25 - rand() % 50;
        if (fn_09_88ba(g_1e04[n].f0c) < 10 && fn_09_88ba(g_1e04[n].f0e) < 10)
            g_1e04[n].f0c += 20;
        g_1e04[n].f18 = 0;
        g_1e04[n].f2f = 0;
        g_1e04[n].f2e = 0;
        g_1e04[n].f6a = 0;
        g_1e04[n].f26 = rand() % 1700;
        SetRect(&rc, (G_05A0_LO / 2 - g_90ea / 2) << g_9150,
                (G_05A0_HI / 2 - g_90ec / 2) << g_9150,
                (G_05A0_LO / 2 + g_90ea / 2) << g_9150,
                (G_05A0_HI / 2 + g_90ec / 2) << g_9150);
        again = 0;
        if (PtInRect(&rc, g_1e04[n].f04))
            again = 1;
    } while (again);
}

/* Frees the GDI objects, the memory DC g_95c2 and the global memory
 * blocks of a mission [inferred]. */
/* @addr 10:0330 */
void far fn_10_0330(void)
{
    int i;

    fn_11_01e0();
    for (i = 1; i < 6; i++) {
        if (g_3b88[i]) {
            DeleteObject(g_3b88[i]);
            g_3b88[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_3b44[i]) {
            DeleteObject(g_3b44[i]);
            g_3b44[i] = 0;
        }
    }
    for (i = 0; i <= 19; i++) {
        if (g_576c[i]) {
            DeleteObject(g_576c[i]);
            g_576c[i] = 0;
        }
    }
    for (i = 0; i < 10; i++) {
        if (g_3b74[i]) {
            DeleteObject(g_3b74[i]);
            g_3b74[i] = 0;
        }
    }
    for (i = 0; i < 20; i++) {
        if (g_3b4c[i]) {
            DeleteObject(g_3b4c[i]);
            g_3b4c[i] = 0;
        }
    }
    if (g_95c2) {
        if (g_95c4)
            SelectPalette(g_95c2, g_95c4, 0);
        SelectObject(g_95c2, g_95c0);
        DeleteObject(g_95be);
        DeleteDC(g_95c2);
        g_95be = g_95c2 = 0;
    }
    for (i = 0; i <= 14; i++) {
        if (g_9100[i]) {
            if (g_1df8[i]) {
                GlobalUnlock(g_9100[i]);
                g_1df8[i] = 0;
            }
            GlobalFree(g_9100[i]);
            g_9100[i] = 0;
        }
    }
    fn_10_061a();
    if (g_92e0) {
        GlobalUnlock(g_92e0);
        g_3d4c = 0;
        GlobalFree(g_92e0);
        g_92e0 = 0;
    }
    if (g_912a) {
        GlobalUnlock(g_912a);
        g_1e4c = 0;
        GlobalFree(g_912a);
        g_912a = 0;
    }
    if (g_912c) {
        DeleteObject(g_912c);
        g_912c = 0;
    }
}

/* Fills the five points g_96d2[i].f50 [inferred: an arc of markers] from
 * the tables g_06d6 / g_06e0, scaled for the view size g_9156. */
/* near-match 25%: 10:16ba (the else arm and the switch match; in the
 * subgame arm the original computes (-1 - 2 * g_9156) once and keeps it,
 * CL here folds the negation differently) */
void far fn_10_16ba(int i)
{
    int w;
    int j;
    int u1;
    int u2;
    int r;
    int r0;
    int b;
    int a;

    if (subgame_active)
        w = g_96d2[i].f2a * (g_9156 * 2 + 1) / 3;
    else
        w = (g_96d2[i].f2a << g_9156) >> 1;
    r0 = (g_96d2[i].f04 + 1) * 2;
    for (j = 0; j < 5; j++) {
        r = r0;
        if (j == 0 || j == 4 || j == 3)
            r--;
        switch (j) {
        case 0:
            r--;
        case 2:
            b = a = 9;
            break;
        case 1:
            a = 7;
            b = 9;
            break;
        case 3:
            b = a = 9;
            if (g_96d2[i].f2a > 29)
                b = 10;
            break;
        case 4:
            a = 8;
            if (g_9156 < 2)
                a = 6;
            b = 9;
            break;
        }
        if (subgame_active) {
            g_96d2[i].f50[j].x = g_06d6[j] * r / 256 * (g_9156 * 2 + 1) / 6 +
                                 (-1 - g_9156 * 2) * a / 6 + w / 2;
            g_96d2[i].f50[j].y = (-1 - g_9156 * 2) * b / 6 -
                                 g_06e0[j] * r / 256 * (g_9156 * 2 + 1) / 6 + w / 2;
        } else {
            g_96d2[i].f50[j].x = (g_06d6[j] * r / 256 >> (2 - g_9156)) -
                                 (a >> (2 - g_9156)) + w / 2;
            g_96d2[i].f50[j].y = w / 2 - (g_06e0[j] * r / 256 >> (2 - g_9156)) -
                                 (b >> (2 - g_9156));
        }
    }
}
