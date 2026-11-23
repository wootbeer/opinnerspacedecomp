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
int far fn_06_71b2(int a);
int far fn_06_720c(int a);   /* declared after 71b2: CL calls the later-declared one first in 10:1502's sum */
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
/* Race track tables, one entry per track (g_9322) [inferred]. */
extern POINT g_9ea8[3];
extern char g_9eb6[3];
extern char g_9eb9[3];      /* marker count [inferred] */
extern char g_9ebc[3];
extern char g_9ebf[3];
extern char g_9ec2[3][40];  /* marker order [inferred] */
extern char g_9f3a[3][2];
extern POINT g_9f40[3][40];
extern POINT g_a120[3];
extern char g_a12c[3][9];   /* track names */
extern int g_920c;
typedef struct {
    int f00;
    int f02;
    int f04;
    int f06;
    int f08;
    int f0a;
    int f0c;
    int f0e;
    int f10;
    int f12;
    int f14;
    int f16;
    int f18;
    int f1a;
    int f1c;
    int f1e;
    int f20;
    int f22;
    int f24;
    int f26;
    int f28;
    int f2a;
    int f2c;
    int f2e;
    int f30;
    int f32;
    int f34;
    int f36;
    int f38;
    int f3a;
    int f3c;
    int f3e;
    int f40;
    int f42;
    int f44;
    int f46;
    int f48;
    int f4a;
    int f4c;
    int f4e;
} REC_50;                /* 0x50-byte records at DS:2f4c (fields not yet named) */
extern REC_50 g_2f4c[28];
extern int g_92ec[12];      /* object counts per list (g_1df8) */
extern int g_92ea;
extern int g_9214;
extern int g_0740;
extern int g_238c;
extern DWORD g_2408;      /* timer [inferred] */
#define SC(n) ((n) << g_9156 >> 1)
void far fn_07_233c();
void far fn_07_2652();
void far fn_07_2e02();
void far fn_07_5090();
void far fn_07_570a();
void far fn_08_95f2();
void far fn_11_37a0();
void far fn_11_3914();
void far fn_11_39d8();
void far fn_11_3bae();
void far fn_12_0dc4();
void far fn_12_274a();
void far fn_12_6a60();
void far fn_16_085e();
int far fn_10_6c02(int a, int b, int c);
int far fn_10_86ca(void);
HBITMAP far fn_10_6ec6(int a);
int far fn_10_6308(int a, int b, int c, int d);
void far fn_10_6ee6(int a, int b, char far *s, int c, int d, int e, int f,
                    int g, int h, char i, char j, int k, int l);
extern long g_1e68;
#define G_1E68_LO (((int *)&g_1e68)[0])
#define G_1E68_HI (((int *)&g_1e68)[1])
extern int g_931e;
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
typedef void (far *FNV)();
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
    char p1a[0x1e - 0x1a];
    int f1e;            /* +0x1e */
    int f20;            /* +0x20 */
    int f22;            /* +0x22 */
    int f24;            /* +0x24 */
    int f26;            /* +0x26 */
    int f28;            /* +0x28 */
    char p2a[0x2c - 0x2a];
    int f2c;            /* +0x2c */
    char f2e;           /* +0x2e */
    char f2f;           /* +0x2f */
    char p30[0x42 - 0x30];
    int f42;            /* +0x42 */
    int f44;            /* +0x44 */
    int f46;            /* +0x46 */
    int f48;            /* +0x48 */
    char p4a[0x4c - 0x4a];
    long f4c;           /* +0x4c: colour [inferred] */
    char f50;           /* +0x50 */
    char p51[0x53 - 0x51];
    char f53;           /* +0x53 */
    char f54;           /* +0x54 */
    char p55[0x5e - 0x55];
    FNV f5e;            /* +0x5e */
    FNV f62;            /* +0x62 */
    FNV f66;            /* +0x66 */
    void far *f6a;      /* +0x6a */
    char rest[0x70 - 0x6e];
} REC_70S;              /* the 0x70-byte records of g_1df8 */
extern REC_70S far *g_1df8[];
extern REC_70S far *g_1e1c;
extern REC_70S far *g_1e04;
extern REC_70S far *g_1e18;
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
    char f08;
    char f09;
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
            g_7be0[i][k][j].y = (fn_06_720c(ang) * ry[k] + fn_06_71b2(ang) * rx[k]) / 128 + w / 2;
        }
    }
}

/* Fills the 28 0x50-byte records at DS:2f4c with their start values;
 * f3e depends on g_920c == 3 [inferred: difficulty]. Records without
 * that difference still test it with two equal arms: CL merges equal
 * constant stores within a basic block, and these tests are what keep
 * the game's per-record grouping [inferred]. */
/* @addr 10:1fb2 */
void far fn_10_1fb2(void)
{
    g_2f4c[0].f08 = 0xba;
    g_2f4c[0].f30 = 0xa;
    g_2f4c[0].f12 = 0;
    g_2f4c[0].f0c = 0;
    g_2f4c[0].f0a = 0;
    g_2f4c[0].f4a = 0;
    g_2f4c[0].f3a = 0;
    g_2f4c[0].f38 = 0;
    g_2f4c[0].f32 = 0;
    g_2f4c[0].f34 = 0;
    g_2f4c[0].f36 = 0;
    g_2f4c[0].f4e = 0;
    if (g_920c == 3)
        g_2f4c[0].f3e = -1;
    else
        g_2f4c[0].f3e = -1;
    g_2f4c[5].f0c = 1;
    g_2f4c[5].f0a = 0xbf;
    g_2f4c[5].f08 = 0xbf;
    g_2f4c[5].f30 = 7;
    g_2f4c[5].f28 = 0x15e;
    g_2f4c[5].f38 = 0x14;
    g_2f4c[5].f32 = 4;
    g_2f4c[5].f36 = 8;
    g_2f4c[5].f12 = 0;
    g_2f4c[5].f4a = 0;
    g_2f4c[5].f34 = 0;
    g_2f4c[5].f4e = 0;
    g_2f4c[5].f3c = 0x2bc;
    if (g_920c == 3)
        g_2f4c[5].f3e = -1;
    else
        g_2f4c[5].f3e = -1;
    g_2f4c[4].f0c = 1;
    g_2f4c[4].f0a = 0xc4;
    g_2f4c[4].f08 = 0xbe;
    g_2f4c[4].f30 = 7;
    g_2f4c[4].f3a = 0x15e;
    g_2f4c[4].f38 = 0x14;
    g_2f4c[4].f32 = 5;
    g_2f4c[4].f36 = 8;
    g_2f4c[4].f12 = 0;
    g_2f4c[4].f4a = 0;
    g_2f4c[4].f34 = 0;
    g_2f4c[4].f4e = 0;
    g_2f4c[4].f3c = 0x28a;
    if (g_920c == 3)
        g_2f4c[4].f3e = 5;
    else
        g_2f4c[4].f3e = -1;
    g_2f4c[3].f0a = 0xc5;
    g_2f4c[3].f08 = 0xbd;
    g_2f4c[3].f30 = 0x50;
    g_2f4c[3].f0c = 1;
    g_2f4c[3].f4a = 1;
    g_2f4c[3].f3a = 0x12c;
    g_2f4c[3].f32 = 7;
    g_2f4c[3].f34 = 4;
    g_2f4c[3].f38 = 0x14;
    g_2f4c[3].f36 = 0x14;
    g_2f4c[3].f12 = 0;
    g_2f4c[3].f4e = 0;
    g_2f4c[3].f3c = 0x3b6;
    if (g_920c == 3)
        g_2f4c[3].f3e = 5;
    else
        g_2f4c[3].f3e = 0xe;
    g_2f4c[1].f0c = 3;
    g_2f4c[1].f0a = 0xc2;
    g_2f4c[1].f08 = 0xbb;
    g_2f4c[1].f30 = 0x19;
    g_2f4c[1].f12 = 0;
    g_2f4c[1].f4a = 0;
    g_2f4c[1].f3a = 0xc8;
    g_2f4c[1].f32 = 6;
    g_2f4c[1].f34 = 1;
    g_2f4c[1].f28 = 0x14;
    g_2f4c[1].f36 = 0x14;
    g_2f4c[1].f4e = 2;
    g_2f4c[1].f3c = 0x258;
    if (g_920c == 3)
        g_2f4c[1].f3e = 5;
    else
        g_2f4c[1].f3e = 0x11;
    g_2f4c[2].f0c = 3;
    g_2f4c[2].f0a = 0xbe;
    g_2f4c[2].f08 = 0xbc;
    g_2f4c[2].f30 = 0x28;
    g_2f4c[2].f12 = 0;
    g_2f4c[2].f4a = 0;
    g_2f4c[2].f3a = 0x118;
    g_2f4c[2].f38 = 0x3c;
    g_2f4c[2].f32 = 6;
    g_2f4c[2].f34 = 2;
    g_2f4c[2].f36 = 0x19;
    g_2f4c[2].f4e = 1;
    g_2f4c[2].f3c = 0x3e8;
    if (g_920c == 3)
        g_2f4c[2].f3e = 5;
    else
        g_2f4c[2].f3e = 0xf;
    g_2f4c[15].f0c = 3;
    g_2f4c[15].f0a = 0xbe;
    g_2f4c[15].f08 = 0xc9;
    g_2f4c[15].f30 = 0x1a;
    g_2f4c[15].f3a = 0x118;
    g_2f4c[15].f38 = 0x3c;
    g_2f4c[15].f34 = 2;
    g_2f4c[15].f36 = 0x14;
    g_2f4c[15].f12 = 0;
    g_2f4c[15].f4a = 0;
    g_2f4c[15].f32 = 0;
    g_2f4c[15].f4e = 0;
    g_2f4c[15].f3c = 0x2ee;
    if (g_920c == 3)
        g_2f4c[15].f3e = 5;
    else
        g_2f4c[15].f3e = -1;
    g_2f4c[6].f14 = 8;
    g_2f4c[6].f26 = 0xc8;
    g_2f4c[6].f28 = 0x32;
    g_2f4c[6].f2a = 7;
    g_2f4c[6].f00 = 0x17;
    g_2f4c[6].f0c = 1;
    g_2f4c[6].f10 = 1;
    g_2f4c[6].f40 = 1;
    g_2f4c[6].f2c = 1;
    g_2f4c[6].f42 = 1;
    g_2f4c[6].f02 = 1;
    g_2f4c[6].f06 = 0x172;
    g_2f4c[6].f08 = 0xc0;
    g_2f4c[6].f0a = -1;
    g_2f4c[6].f04 = -1;
    g_2f4c[6].f20 = 0x1c;
    g_2f4c[6].f0e = 2;
    g_2f4c[6].f12 = 2;
    g_2f4c[6].f24 = 2;
    g_2f4c[6].f18 = 0x14;
    g_2f4c[6].f30 = 0x14;
    g_2f4c[6].f3a = 0x2bc;
    g_2f4c[6].f16 = 0x64;
    g_2f4c[6].f38 = 0x64;
    g_2f4c[6].f32 = 9;
    g_2f4c[6].f22 = 3;
    g_2f4c[6].f34 = 3;
    g_2f4c[6].f1a = 0;
    g_2f4c[6].f1c = 0;
    g_2f4c[6].f1e = 0;
    g_2f4c[6].f44 = 0;
    g_2f4c[6].f46 = 0;
    g_2f4c[6].f2e = 0;
    g_2f4c[6].f48 = 0;
    g_2f4c[6].f4a = 0;
    g_2f4c[6].f36 = 0;
    g_2f4c[6].f4e = 0;
    g_2f4c[6].f3c = 0x44c;
    if (g_920c == 3)
        g_2f4c[6].f3e = 7;
    else
        g_2f4c[6].f3e = 8;
    g_2f4c[8].f14 = 0xa;
    g_2f4c[8].f16 = 0x78;
    g_2f4c[8].f26 = 0xc8;
    g_2f4c[8].f28 = 0x28;
    g_2f4c[8].f2a = 9;
    g_2f4c[8].f00 = 0x17;
    g_2f4c[8].f0c = 1;
    g_2f4c[8].f10 = 1;
    g_2f4c[8].f2c = 1;
    g_2f4c[8].f42 = 1;
    g_2f4c[8].f44 = 1;
    g_2f4c[8].f02 = 1;
    g_2f4c[8].f06 = 0x172;
    g_2f4c[8].f08 = 0xc2;
    g_2f4c[8].f0a = -1;
    g_2f4c[8].f04 = -1;
    g_2f4c[8].f20 = 0x1c;
    g_2f4c[8].f12 = 3;
    g_2f4c[8].f22 = 3;
    g_2f4c[8].f0e = 2;
    g_2f4c[8].f24 = 2;
    g_2f4c[8].f18 = 0x14;
    g_2f4c[8].f30 = 0x14;
    g_2f4c[8].f3a = 0x17c;
    g_2f4c[8].f38 = 0x82;
    g_2f4c[8].f32 = 7;
    g_2f4c[8].f34 = 8;
    g_2f4c[8].f1a = 0;
    g_2f4c[8].f1c = 0;
    g_2f4c[8].f1e = 0;
    g_2f4c[8].f40 = 0;
    g_2f4c[8].f46 = 0;
    g_2f4c[8].f2e = 0;
    g_2f4c[8].f48 = 0;
    g_2f4c[8].f4a = 0;
    g_2f4c[8].f36 = 0;
    g_2f4c[8].f4e = 0;
    g_2f4c[8].f3c = 0x2ee;
    if (g_920c == 3)
        g_2f4c[8].f3e = 7;
    else
        g_2f4c[8].f3e = -1;
    g_2f4c[7].f12 = 4;
    g_2f4c[7].f16 = 0x64;
    g_2f4c[7].f18 = 0x14;
    g_2f4c[7].f26 = 0xc8;
    g_2f4c[7].f00 = 0x17;
    g_2f4c[7].f0c = 1;
    g_2f4c[7].f10 = 1;
    g_2f4c[7].f2c = 1;
    g_2f4c[7].f42 = 1;
    g_2f4c[7].f44 = 1;
    g_2f4c[7].f46 = 1;
    g_2f4c[7].f02 = 1;
    g_2f4c[7].f06 = 0x172;
    g_2f4c[7].f08 = 0xc1;
    g_2f4c[7].f0a = -1;
    g_2f4c[7].f04 = -1;
    g_2f4c[7].f20 = 0x1c;
    g_2f4c[7].f22 = 3;
    g_2f4c[7].f0e = 2;
    g_2f4c[7].f24 = 2;
    g_2f4c[7].f30 = 0x10;
    g_2f4c[7].f3a = 0x168;
    g_2f4c[7].f38 = 0x6e;
    g_2f4c[7].f14 = 7;
    g_2f4c[7].f2a = 7;
    g_2f4c[7].f32 = 7;
    g_2f4c[7].f34 = 8;
    g_2f4c[7].f1a = 0;
    g_2f4c[7].f1c = 0;
    g_2f4c[7].f1e = 0;
    g_2f4c[7].f40 = 0;
    g_2f4c[7].f28 = 0;
    g_2f4c[7].f2e = 0;
    g_2f4c[7].f48 = 0;
    g_2f4c[7].f4a = 0;
    g_2f4c[7].f36 = 0;
    g_2f4c[7].f4e = 0;
    g_2f4c[7].f3c = 0x320;
    if (g_920c == 3)
        g_2f4c[7].f3e = -1;
    else
        g_2f4c[7].f3e = -1;
    g_2f4c[12].f12 = 4;
    g_2f4c[12].f14 = 8;
    g_2f4c[12].f16 = 0x5a;
    g_2f4c[12].f18 = 0x14;
    g_2f4c[12].f26 = 0xc8;
    g_2f4c[12].f0c = 1;
    g_2f4c[12].f0e = 1;
    g_2f4c[12].f10 = 1;
    g_2f4c[12].f1c = 1;
    g_2f4c[12].f2c = 1;
    g_2f4c[12].f42 = 1;
    g_2f4c[12].f48 = 7;
    g_2f4c[12].f00 = 0x13;
    g_2f4c[12].f06 = 0xa0;
    g_2f4c[12].f08 = 0xc6;
    g_2f4c[12].f0a = -1;
    g_2f4c[12].f04 = -1;
    g_2f4c[12].f20 = 0x4e;
    g_2f4c[12].f1a = 2;
    g_2f4c[12].f1e = 2;
    g_2f4c[12].f22 = 2;
    g_2f4c[12].f02 = 3;
    g_2f4c[12].f24 = 3;
    g_2f4c[12].f30 = 0x10;
    g_2f4c[12].f3a = 0x12c;
    g_2f4c[12].f38 = 0x78;
    g_2f4c[12].f32 = 5;
    g_2f4c[12].f2a = 6;
    g_2f4c[12].f34 = 6;
    g_2f4c[12].f40 = 0;
    g_2f4c[12].f28 = 0;
    g_2f4c[12].f44 = 0;
    g_2f4c[12].f46 = 0;
    g_2f4c[12].f2e = 0;
    g_2f4c[12].f4a = 0;
    g_2f4c[12].f36 = 0;
    g_2f4c[12].f4e = 0;
    g_2f4c[12].f3c = 0x1f4;
    if (g_920c == 3)
        g_2f4c[12].f3e = 0xa;
    else
        g_2f4c[12].f3e = 5;
    g_2f4c[18].f14 = 6;
    g_2f4c[18].f16 = 0x4b;
    g_2f4c[18].f18 = 0x14;
    g_2f4c[18].f26 = 0x6a;
    g_2f4c[18].f00 = 0x17;
    g_2f4c[18].f06 = 0x14a;
    g_2f4c[18].f08 = 0xcc;
    g_2f4c[18].f0a = -1;
    g_2f4c[18].f04 = -1;
    g_2f4c[18].f20 = 2;
    g_2f4c[18].f02 = 3;
    g_2f4c[18].f24 = 3;
    g_2f4c[18].f30 = 0x10;
    g_2f4c[18].f3a = 0x12c;
    g_2f4c[18].f38 = 0x78;
    g_2f4c[18].f2a = 4;
    g_2f4c[18].f2c = 4;
    g_2f4c[18].f22 = 4;
    g_2f4c[18].f32 = 4;
    g_2f4c[18].f0c = 1;
    g_2f4c[18].f0e = 1;
    g_2f4c[18].f10 = 1;
    g_2f4c[18].f12 = 1;
    g_2f4c[18].f42 = 1;
    g_2f4c[18].f34 = 1;
    g_2f4c[18].f1a = 0;
    g_2f4c[18].f1c = 0;
    g_2f4c[18].f1e = 0;
    g_2f4c[18].f40 = 0;
    g_2f4c[18].f28 = 0;
    g_2f4c[18].f44 = 0;
    g_2f4c[18].f46 = 0;
    g_2f4c[18].f2e = 0;
    g_2f4c[18].f48 = 0;
    g_2f4c[18].f4a = 0;
    g_2f4c[18].f36 = 0;
    g_2f4c[18].f4e = 0;
    g_2f4c[18].f3c = 0x28a;
    if (g_920c == 3)
        g_2f4c[18].f3e = 7;
    else
        g_2f4c[18].f3e = 4;
    g_2f4c[19].f16 = 0x4b;
    g_2f4c[19].f18 = 0x14;
    g_2f4c[19].f26 = 0x6a;
    g_2f4c[19].f2a = 7;
    g_2f4c[19].f2c = 6;
    g_2f4c[19].f00 = 0x1b;
    g_2f4c[19].f06 = 0x14f;
    g_2f4c[19].f08 = 0xcd;
    g_2f4c[19].f0a = -1;
    g_2f4c[19].f04 = -1;
    g_2f4c[19].f20 = 2;
    g_2f4c[19].f02 = 3;
    g_2f4c[19].f22 = 3;
    g_2f4c[19].f24 = 3;
    g_2f4c[19].f30 = 0x10;
    g_2f4c[19].f3a = 0x12c;
    g_2f4c[19].f38 = 0x78;
    g_2f4c[19].f14 = 4;
    g_2f4c[19].f32 = 4;
    g_2f4c[19].f0c = 1;
    g_2f4c[19].f0e = 1;
    g_2f4c[19].f10 = 1;
    g_2f4c[19].f12 = 1;
    g_2f4c[19].f42 = 1;
    g_2f4c[19].f34 = 1;
    g_2f4c[19].f1a = 0;
    g_2f4c[19].f1c = 0;
    g_2f4c[19].f1e = 0;
    g_2f4c[19].f40 = 0;
    g_2f4c[19].f28 = 0;
    g_2f4c[19].f44 = 0;
    g_2f4c[19].f46 = 0;
    g_2f4c[19].f2e = 0;
    g_2f4c[19].f48 = 0;
    g_2f4c[19].f4a = 0;
    g_2f4c[19].f36 = 0;
    g_2f4c[19].f4e = 0;
    g_2f4c[19].f3c = 0x2bc;
    if (g_920c == 3)
        g_2f4c[19].f3e = 7;
    else
        g_2f4c[19].f3e = 0x15;
    g_2f4c[20].f14 = 6;
    g_2f4c[20].f16 = 0x4b;
    g_2f4c[20].f18 = 0x14;
    g_2f4c[20].f26 = 0x6a;
    g_2f4c[20].f2a = 5;
    g_2f4c[20].f00 = 0x15;
    g_2f4c[20].f06 = 0xb9;
    g_2f4c[20].f08 = 0xce;
    g_2f4c[20].f0a = -1;
    g_2f4c[20].f04 = -1;
    g_2f4c[20].f20 = 2;
    g_2f4c[20].f02 = 3;
    g_2f4c[20].f24 = 3;
    g_2f4c[20].f30 = 0x10;
    g_2f4c[20].f3a = 0x12c;
    g_2f4c[20].f38 = 0x78;
    g_2f4c[20].f2c = 4;
    g_2f4c[20].f22 = 4;
    g_2f4c[20].f32 = 4;
    g_2f4c[20].f0c = 1;
    g_2f4c[20].f0e = 1;
    g_2f4c[20].f10 = 1;
    g_2f4c[20].f12 = 1;
    g_2f4c[20].f42 = 1;
    g_2f4c[20].f34 = 1;
    g_2f4c[20].f1a = 0;
    g_2f4c[20].f1c = 0;
    g_2f4c[20].f1e = 0;
    g_2f4c[20].f40 = 0;
    g_2f4c[20].f28 = 0;
    g_2f4c[20].f44 = 0;
    g_2f4c[20].f46 = 0;
    g_2f4c[20].f2e = 0;
    g_2f4c[20].f48 = 0;
    g_2f4c[20].f4a = 0;
    g_2f4c[20].f36 = 0;
    g_2f4c[20].f4e = 0;
    g_2f4c[20].f3c = 0x226;
    if (g_920c == 3)
        g_2f4c[20].f3e = 7;
    else
        g_2f4c[20].f3e = 0xb;
    g_2f4c[10].f14 = 7;
    g_2f4c[10].f16 = 0x32;
    g_2f4c[10].f18 = 0x14;
    g_2f4c[10].f26 = 0x40;
    g_2f4c[10].f10 = 1;
    g_2f4c[10].f12 = 1;
    g_2f4c[10].f2c = 1;
    g_2f4c[10].f42 = 1;
    g_2f4c[10].f2a = 6;
    g_2f4c[10].f2e = 6;
    g_2f4c[10].f48 = 6;
    g_2f4c[10].f00 = 0x16;
    g_2f4c[10].f08 = 0xc4;
    g_2f4c[10].f06 = 0x96;
    g_2f4c[10].f0a = 0x96;
    g_2f4c[10].f04 = -1;
    g_2f4c[10].f20 = 0x18;
    g_2f4c[10].f22 = 3;
    g_2f4c[10].f0c = 2;
    g_2f4c[10].f24 = 2;
    g_2f4c[10].f30 = 0xc;
    g_2f4c[10].f3a = 0x104;
    g_2f4c[10].f38 = 0x50;
    g_2f4c[10].f0e = 4;
    g_2f4c[10].f32 = 4;
    g_2f4c[10].f02 = 5;
    g_2f4c[10].f34 = 5;
    g_2f4c[10].f1a = 0;
    g_2f4c[10].f1c = 0;
    g_2f4c[10].f1e = 0;
    g_2f4c[10].f40 = 0;
    g_2f4c[10].f28 = 0;
    g_2f4c[10].f44 = 0;
    g_2f4c[10].f46 = 0;
    g_2f4c[10].f4a = 0;
    g_2f4c[10].f36 = 0;
    g_2f4c[10].f4e = 0;
    g_2f4c[10].f3c = 0x1c2;
    if (g_920c == 3)
        g_2f4c[10].f3e = -1;
    else
        g_2f4c[10].f3e = -1;
    g_2f4c[11].f14 = 7;
    g_2f4c[11].f18 = 0x14;
    g_2f4c[11].f16 = 0x64;
    g_2f4c[11].f26 = 0x64;
    g_2f4c[11].f2a = 8;
    g_2f4c[11].f00 = 0x17;
    g_2f4c[11].f0c = 1;
    g_2f4c[11].f10 = 1;
    g_2f4c[11].f12 = 1;
    g_2f4c[11].f2c = 1;
    g_2f4c[11].f42 = 1;
    g_2f4c[11].f46 = 1;
    g_2f4c[11].f02 = 1;
    g_2f4c[11].f06 = 0x172;
    g_2f4c[11].f08 = 0xc5;
    g_2f4c[11].f0a = -1;
    g_2f4c[11].f04 = -1;
    g_2f4c[11].f20 = 0x1c;
    g_2f4c[11].f0e = 2;
    g_2f4c[11].f24 = 2;
    g_2f4c[11].f30 = 0xc;
    g_2f4c[11].f3a = 0x122;
    g_2f4c[11].f38 = 0x5a;
    g_2f4c[11].f32 = 4;
    g_2f4c[11].f22 = 3;
    g_2f4c[11].f34 = 3;
    g_2f4c[11].f1a = 0;
    g_2f4c[11].f1c = 0;
    g_2f4c[11].f1e = 0;
    g_2f4c[11].f40 = 0;
    g_2f4c[11].f28 = 0;
    g_2f4c[11].f44 = 0;
    g_2f4c[11].f2e = 0;
    g_2f4c[11].f48 = 0;
    g_2f4c[11].f4a = 0;
    g_2f4c[11].f36 = 0;
    g_2f4c[11].f4e = 0;
    g_2f4c[11].f3c = 0x1c2;
    if (g_920c == 3)
        g_2f4c[11].f3e = 7;
    else
        g_2f4c[11].f3e = -1;
    g_2f4c[9].f14 = 9;
    g_2f4c[9].f16 = 0x46;
    g_2f4c[9].f18 = 0x14;
    g_2f4c[9].f12 = 4;
    g_2f4c[9].f1c = 4;
    g_2f4c[9].f26 = 0xc8;
    g_2f4c[9].f0e = 1;
    g_2f4c[9].f10 = 1;
    g_2f4c[9].f40 = 1;
    g_2f4c[9].f2c = 1;
    g_2f4c[9].f42 = 1;
    g_2f4c[9].f46 = 1;
    g_2f4c[9].f48 = 5;
    g_2f4c[9].f00 = 0x15;
    g_2f4c[9].f06 = 0xa1;
    g_2f4c[9].f08 = 0xc3;
    g_2f4c[9].f0a = -1;
    g_2f4c[9].f04 = -1;
    g_2f4c[9].f0c = 2;
    g_2f4c[9].f1a = 2;
    g_2f4c[9].f20 = 2;
    g_2f4c[9].f22 = 2;
    g_2f4c[9].f1e = 3;
    g_2f4c[9].f02 = 3;
    g_2f4c[9].f24 = 3;
    g_2f4c[9].f30 = 0x10;
    g_2f4c[9].f3a = 0x10e;
    g_2f4c[9].f38 = 0x55;
    g_2f4c[9].f2a = 6;
    g_2f4c[9].f32 = 6;
    g_2f4c[9].f34 = 7;
    g_2f4c[9].f28 = 0;
    g_2f4c[9].f44 = 0;
    g_2f4c[9].f2e = 0;
    g_2f4c[9].f4a = 0;
    g_2f4c[9].f36 = 0;
    g_2f4c[9].f4e = 0;
    g_2f4c[9].f3c = 0x226;
    if (g_920c == 3)
        g_2f4c[9].f3e = 0xa;
    else
        g_2f4c[9].f3e = 0xa;
    g_2f4c[23].f0c = 3;
    g_2f4c[23].f0a = 0xc6;
    g_2f4c[23].f08 = 0xd1;
    g_2f4c[23].f30 = 0x2bc;
    g_2f4c[23].f4a = 1;
    g_2f4c[23].f3a = 0x384;
    g_2f4c[23].f38 = 0x32;
    g_2f4c[23].f32 = 7;
    g_2f4c[23].f36 = 0x64;
    g_2f4c[23].f12 = 0;
    g_2f4c[23].f34 = 0;
    g_2f4c[23].f4e = 0;
    g_2f4c[23].f3c = 0;
    if (g_920c == 3)
        g_2f4c[23].f3e = 5;
    else
        g_2f4c[23].f3e = -1;
    g_2f4c[13].f0c = 3;
    g_2f4c[13].f0a = 0xc3;
    g_2f4c[13].f08 = 0xc7;
    g_2f4c[13].f30 = 4;
    g_2f4c[13].f3a = 0x12c;
    g_2f4c[13].f38 = 0x28;
    g_2f4c[13].f12 = 0;
    g_2f4c[13].f4a = 0;
    g_2f4c[13].f32 = 0;
    g_2f4c[13].f34 = 0;
    g_2f4c[13].f36 = 0;
    g_2f4c[13].f4e = 1;
    g_2f4c[13].f3c = 0x2ee;
    if (g_920c == 3)
        g_2f4c[13].f3e = 0xa;
    else
        g_2f4c[13].f3e = 0x10;
    g_2f4c[27].f0e = 5;
    g_2f4c[27].f16 = 0x46;
    g_2f4c[27].f18 = 0x14;
    g_2f4c[27].f26 = 0x32;
    g_2f4c[27].f28 = 0x2d;
    g_2f4c[27].f1a = 2;
    g_2f4c[27].f2a = 2;
    g_2f4c[27].f0c = 1;
    g_2f4c[27].f10 = 1;
    g_2f4c[27].f12 = 1;
    g_2f4c[27].f2c = 1;
    g_2f4c[27].f42 = 1;
    g_2f4c[27].f14 = 9;
    g_2f4c[27].f48 = 9;
    g_2f4c[27].f02 = 3;
    g_2f4c[27].f08 = -1;
    g_2f4c[27].f0a = -1;
    g_2f4c[27].f04 = -1;
    g_2f4c[27].f1c = 0;
    g_2f4c[27].f1e = 0;
    g_2f4c[27].f40 = 0;
    g_2f4c[27].f44 = 0;
    g_2f4c[27].f46 = 0;
    g_2f4c[27].f2e = 0;
    g_2f4c[27].f00 = 0;
    g_2f4c[27].f06 = 0;
    g_2f4c[27].f20 = 0;
    g_2f4c[27].f22 = 0;
    g_2f4c[27].f24 = 0;
    g_2f4c[27].f30 = 0;
    g_2f4c[27].f4a = 0;
    g_2f4c[27].f28 = 0;
    g_2f4c[27].f38 = 0;
    g_2f4c[27].f32 = 0;
    g_2f4c[27].f34 = 0;
    g_2f4c[27].f36 = 0;
    g_2f4c[27].f4e = 0;
    if (g_920c == 3)
        g_2f4c[27].f3e = 5;
    else
        g_2f4c[27].f3e = -1;
    g_2f4c[14].f0e = 2;
    g_2f4c[14].f12 = 4;
    g_2f4c[14].f14 = 7;
    g_2f4c[14].f18 = 0x14;
    g_2f4c[14].f26 = 0xd2;
    g_2f4c[14].f0c = 1;
    g_2f4c[14].f10 = 1;
    g_2f4c[14].f1e = 1;
    g_2f4c[14].f2c = 1;
    g_2f4c[14].f42 = 1;
    g_2f4c[14].f46 = 1;
    g_2f4c[14].f00 = 0x15;
    g_2f4c[14].f06 = 0x2a8;
    g_2f4c[14].f08 = 0xc8;
    g_2f4c[14].f0a = -1;
    g_2f4c[14].f04 = -1;
    g_2f4c[14].f20 = 0x1c;
    g_2f4c[14].f2a = 6;
    g_2f4c[14].f22 = 6;
    g_2f4c[14].f1c = 3;
    g_2f4c[14].f02 = 3;
    g_2f4c[14].f24 = 3;
    g_2f4c[14].f30 = 0x1e;
    g_2f4c[14].f3a = 0x172;
    g_2f4c[14].f16 = 0x64;
    g_2f4c[14].f38 = 0x64;
    g_2f4c[14].f32 = 8;
    g_2f4c[14].f34 = 9;
    g_2f4c[14].f1a = 0;
    g_2f4c[14].f40 = 0;
    g_2f4c[14].f28 = 0;
    g_2f4c[14].f44 = 0;
    g_2f4c[14].f2e = 0;
    g_2f4c[14].f48 = 0;
    g_2f4c[14].f4a = 0;
    g_2f4c[14].f36 = 0;
    g_2f4c[14].f4e = 0;
    g_2f4c[14].f3c = 0x384;
    if (g_920c == 3)
        g_2f4c[14].f3e = 7;
    else
        g_2f4c[14].f3e = -1;
    g_2f4c[17].f0e = 4;
    g_2f4c[17].f12 = 5;
    g_2f4c[17].f14 = 7;
    g_2f4c[17].f16 = 0x78;
    g_2f4c[17].f18 = 0x14;
    g_2f4c[17].f26 = 0x3c;
    g_2f4c[17].f00 = 9;
    g_2f4c[17].f06 = 0x35c;
    g_2f4c[17].f08 = 0xcb;
    g_2f4c[17].f0a = -1;
    g_2f4c[17].f04 = -1;
    g_2f4c[17].f20 = 0x1c;
    g_2f4c[17].f22 = 6;
    g_2f4c[17].f0c = 3;
    g_2f4c[17].f02 = 3;
    g_2f4c[17].f24 = 3;
    g_2f4c[17].f30 = 8;
    g_2f4c[17].f3a = 0x172;
    g_2f4c[17].f38 = 0x64;
    g_2f4c[17].f32 = 2;
    g_2f4c[17].f1a = 0;
    g_2f4c[17].f1c = 0;
    g_2f4c[17].f1e = 0;
    g_2f4c[17].f40 = 0;
    g_2f4c[17].f28 = 0;
    g_2f4c[17].f44 = 0;
    g_2f4c[17].f48 = 0;
    g_2f4c[17].f4a = 0;
    g_2f4c[17].f36 = 0;
    g_2f4c[17].f10 = 1;
    g_2f4c[17].f2a = 1;
    g_2f4c[17].f2c = 1;
    g_2f4c[17].f42 = 1;
    g_2f4c[17].f46 = 1;
    g_2f4c[17].f2e = 1;
    g_2f4c[17].f34 = 1;
    g_2f4c[17].f4e = 1;
    g_2f4c[17].f3c = 0x258;
    if (g_920c == 3)
        g_2f4c[17].f3e = 0xa;
    else
        g_2f4c[17].f3e = -1;
    g_2f4c[21].f14 = 4;
    g_2f4c[21].f16 = 0x5f;
    g_2f4c[21].f18 = 0x14;
    g_2f4c[21].f26 = 0x55;
    g_2f4c[21].f00 = 0xf;
    g_2f4c[21].f06 = 0xbc;
    g_2f4c[21].f08 = 0xcf;
    g_2f4c[21].f1a = -1;
    g_2f4c[21].f0a = -1;
    g_2f4c[21].f04 = -1;
    g_2f4c[21].f20 = 2;
    g_2f4c[21].f10 = 3;
    g_2f4c[21].f2a = 3;
    g_2f4c[21].f02 = 3;
    g_2f4c[21].f22 = 3;
    g_2f4c[21].f24 = 3;
    g_2f4c[21].f30 = 8;
    g_2f4c[21].f3a = 0x15e;
    g_2f4c[21].f38 = 0x5a;
    g_2f4c[21].f12 = 5;
    g_2f4c[21].f32 = 5;
    g_2f4c[21].f1c = 0;
    g_2f4c[21].f1e = 0;
    g_2f4c[21].f40 = 0;
    g_2f4c[21].f28 = 0;
    g_2f4c[21].f44 = 0;
    g_2f4c[21].f46 = 0;
    g_2f4c[21].f2e = 0;
    g_2f4c[21].f48 = 0;
    g_2f4c[21].f4a = 0;
    g_2f4c[21].f36 = 0;
    g_2f4c[21].f0c = 1;
    g_2f4c[21].f0e = 1;
    g_2f4c[21].f2c = 1;
    g_2f4c[21].f42 = 1;
    g_2f4c[21].f34 = 1;
    g_2f4c[21].f4e = 1;
    g_2f4c[21].f3c = 0x28a;
    if (g_920c == 3)
        g_2f4c[21].f3e = 7;
    else
        g_2f4c[21].f3e = -1;
    g_2f4c[16].f0c = 2;
    g_2f4c[16].f14 = 7;
    g_2f4c[16].f16 = 0x32;
    g_2f4c[16].f18 = 0x14;
    g_2f4c[16].f26 = 0x15e;
    g_2f4c[16].f2e = 8;
    g_2f4c[16].f2a = 6;
    g_2f4c[16].f48 = 6;
    g_2f4c[16].f00 = 0x17;
    g_2f4c[16].f08 = 0xca;
    g_2f4c[16].f06 = 0x348;
    g_2f4c[16].f0a = 0x348;
    g_2f4c[16].f04 = -1;
    g_2f4c[16].f20 = 0x18;
    g_2f4c[16].f30 = 0xe;
    g_2f4c[16].f10 = 1;
    g_2f4c[16].f12 = 1;
    g_2f4c[16].f2c = 1;
    g_2f4c[16].f42 = 1;
    g_2f4c[16].f4a = 1;
    g_2f4c[16].f3a = 0x104;
    g_2f4c[16].f38 = 0x50;
    g_2f4c[16].f0e = 4;
    g_2f4c[16].f22 = 4;
    g_2f4c[16].f24 = 4;
    g_2f4c[16].f32 = 4;
    g_2f4c[16].f02 = 5;
    g_2f4c[16].f34 = 5;
    g_2f4c[16].f1a = 0;
    g_2f4c[16].f1c = 0;
    g_2f4c[16].f1e = 0;
    g_2f4c[16].f40 = 0;
    g_2f4c[16].f28 = 0;
    g_2f4c[16].f44 = 0;
    g_2f4c[16].f46 = 0;
    g_2f4c[16].f36 = 0;
    g_2f4c[16].f4e = 0;
    g_2f4c[16].f3c = 0x1f4;
    if (g_920c == 3)
        g_2f4c[16].f3e = 0xa;
    else
        g_2f4c[16].f3e = -1;
    g_2f4c[22].f14 = 5;
    g_2f4c[22].f16 = 0x50;
    g_2f4c[22].f26 = 0xc8;
    g_2f4c[22].f18 = 0x14;
    g_2f4c[22].f2a = 0x14;
    g_2f4c[22].f0c = 1;
    g_2f4c[22].f10 = 1;
    g_2f4c[22].f2c = 1;
    g_2f4c[22].f42 = 1;
    g_2f4c[22].f44 = 1;
    g_2f4c[22].f46 = 1;
    g_2f4c[22].f08 = 0xd0;
    g_2f4c[22].f0a = 0xc7;
    g_2f4c[22].f06 = -1;
    g_2f4c[22].f04 = -1;
    g_2f4c[22].f20 = 0x1c;
    g_2f4c[22].f12 = 3;
    g_2f4c[22].f22 = 3;
    g_2f4c[22].f0e = 2;
    g_2f4c[22].f00 = 2;
    g_2f4c[22].f24 = 2;
    g_2f4c[22].f30 = 0x1e;
    g_2f4c[22].f3a = 0x168;
    g_2f4c[22].f38 = 0x6e;
    g_2f4c[22].f32 = 7;
    g_2f4c[22].f34 = 8;
    g_2f4c[22].f36 = 0x96;
    g_2f4c[22].f1a = 0;
    g_2f4c[22].f1c = 0;
    g_2f4c[22].f1e = 0;
    g_2f4c[22].f40 = 0;
    g_2f4c[22].f28 = 0;
    g_2f4c[22].f2e = 0;
    g_2f4c[22].f48 = 0;
    g_2f4c[22].f02 = 0;
    g_2f4c[22].f4a = 0;
    g_2f4c[22].f4e = 0;
    g_2f4c[22].f3c = 0;
    if (g_920c == 3)
        g_2f4c[22].f3e = 7;
    else
        g_2f4c[22].f3e = -1;
    g_2f4c[24].f0e = 2;
    g_2f4c[24].f0a = 0xbd;
    g_2f4c[24].f08 = 0xd2;
    g_2f4c[24].f30 = 3;
    g_2f4c[24].f28 = 0x28;
    g_2f4c[24].f38 = 0x14;
    g_2f4c[24].f0c = 1;
    g_2f4c[24].f4e = 1;
    g_2f4c[24].f12 = 0;
    g_2f4c[24].f4a = 0;
    g_2f4c[24].f32 = 0;
    g_2f4c[24].f34 = 0;
    g_2f4c[24].f36 = 0;
    g_2f4c[24].f3c = 0;
    if (g_920c == 3)
        g_2f4c[24].f3e = 5;
    else
        g_2f4c[24].f3e = -1;
    g_2f4c[25].f0e = 2;
    g_2f4c[25].f0c = 1;
    g_2f4c[25].f0a = 0xc0;
    g_2f4c[25].f08 = 0xd3;
    g_2f4c[25].f30 = 3;
    g_2f4c[25].f28 = 0x28;
    g_2f4c[25].f38 = 0x14;
    g_2f4c[25].f12 = 0;
    g_2f4c[25].f4a = 0;
    g_2f4c[25].f32 = 0;
    g_2f4c[25].f34 = 0;
    g_2f4c[25].f36 = 0;
    g_2f4c[25].f4e = 0;
    g_2f4c[25].f3c = 0;
    if (g_920c == 3)
        g_2f4c[25].f3e = 7;
    else
        g_2f4c[25].f3e = -1;
    g_2f4c[26].f0e = 2;
    g_2f4c[26].f0a = 0xc1;
    g_2f4c[26].f08 = 0xd4;
    g_2f4c[26].f30 = 3;
    g_2f4c[26].f28 = 0x28;
    g_2f4c[26].f38 = 0x14;
    g_2f4c[26].f0c = 1;
    g_2f4c[26].f4e = 1;
    g_2f4c[26].f12 = 0;
    g_2f4c[26].f4a = 0;
    g_2f4c[26].f32 = 0;
    g_2f4c[26].f34 = 0;
    g_2f4c[26].f36 = 0;
    g_2f4c[26].f3c = 0;
    if (g_920c == 3)
        g_2f4c[26].f3e = 5;
    else
        g_2f4c[26].f3e = -1;
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
/* @addr 10:16ba */
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
            /* u1, u2 are never read: the assignments only fix CL's
             * evaluation order (no stores are emitted) */
            g_96d2[i].f50[j].x = g_06d6[j] * r / 256 * (g_9156 * 2 + 1) / 6 +
                                 (u1 = -1 - g_9156 * 2) * a / 6 + w / 2;
            g_96d2[i].f50[j].y = (-1 - g_9156 * 2) * b / 6 -
                                 (u2 = g_06e0[j] * r / 256 * (g_9156 * 2 + 1) / 6) + w / 2;
        } else {
            g_96d2[i].f50[j].x = (g_06d6[j] * r / 256 >> (2 - g_9156)) -
                                 (a >> (2 - g_9156)) + w / 2;
            g_96d2[i].f50[j].y = w / 2 - (g_06e0[j] * r / 256 >> (2 - g_9156)) -
                                 (b >> (2 - g_9156));
        }
    }
}

/* Fills the three race tracks' tables (LAZYLOOP, SDISPEED, GRANDPRI):
 * the same kind of constant table initialiser as fn_10_2ffa. */
/* @addr 10:320a */
void far fn_10_320a(void)
{
    lstrcpy(g_a12c[0], "LAZYLOOP");
    g_9eb9[0] = 0x16;
    g_9eb6[0] = 8;
    g_9ec2[0][0] = 8;
    g_9ec2[0][1] = 0xd;
    g_9f3a[0][1] = 0xa;
    g_9ec2[0][3] = 0xa;
    g_9f40[0][4].y = 0x4074;
    g_9ec2[0][4] = 0x12;
    g_9f40[0][6].y = 0x2328;
    g_9f40[0][7].x = 0x2328;
    g_9ec2[0][7] = 0;
    g_9f40[0][1].y = 0x2af8;
    g_9f40[0][4].x = 0x2af8;
    g_9f40[0][8].y = 0x2af8;
    g_9ec2[0][8] = 9;
    g_9f40[0][8].x = 0x3e80;
    g_9f40[0][9].x = 0x3e80;
    g_9ec2[0][10] = 5;
    g_9ec2[0][11] = 0xc;
    g_9f40[0][3].x = 0x36b0;
    g_9f40[0][13].y = 0x36b0;
    g_9ec2[0][13] = 0xe;
    g_9f40[0][14].y = 0x4268;
    g_9ec2[0][14] = 0xf;
    g_9ec2[0][15] = 0x10;
    g_9ec2[0][16] = 0x11;
    g_9f40[0][11].x = 0x55f0;
    g_9f40[0][12].x = 0x55f0;
    g_9f40[0][14].x = 0x55f0;
    g_9f40[0][15].x = 0x55f0;
    g_9f40[0][16].y = 0x55f0;
    g_9f40[0][17].y = 0x55f0;
    g_9f40[0][18].x = 0x1388;
    g_9f40[0][18].y = 0x4650;
    g_9ec2[0][18] = 0x13;
    g_9ec2[0][19] = 0x14;
    g_9ec2[0][20] = 0x15;
    g_9f3a[0][0] = 0xb;
    g_9ec2[0][21] = 0xb;
    g_9f40[0][13].x = 0x5208;
    g_9f40[0][22].x = 0x5208;
    g_9f40[0][12].y = 0x1f40;
    g_9f40[0][22].y = 0x1f40;
    g_9f40[0][23].x = 0x38a4;
    g_9f40[0][0].x = 0x4c2c;
    g_9f40[0][2].x = 0x4c2c;
    g_9f40[0][23].y = 0x4c2c;
    g_9ec2[0][9] = 2;
    g_9ec2[0][23] = 2;
    g_9f40[0][1].x = 0x4a38;
    g_9f40[0][2].y = 0x4a38;
    g_9f40[0][3].y = 0x4a38;
    g_9f40[0][15].y = 0x4a38;
    g_9f40[0][16].x = 0x4a38;
    g_9f40[0][24].x = 0x4a38;
    g_9f40[0][24].y = 0x53fc;
    g_9ebf[0] = 3;
    g_9ec2[0][2] = 3;
    g_9ec2[0][24] = 3;
    g_9f40[0][25].x = 0x157c;
    g_9ec2[0][5] = 6;
    g_9ec2[0][25] = 6;
    g_9f40[0][26].x = 0x4844;
    g_9f40[0][26].y = 0x2710;
    g_9ec2[0][12] = 1;
    g_9ec2[0][22] = 1;
    g_9ec2[0][26] = 1;
    g_9f40[0][17].x = 0x2ee0;
    g_9f40[0][25].y = 0x2ee0;
    g_9f40[0][27].x = 0x2ee0;
    g_9f40[0][5].y = 0x3a98;
    g_9f40[0][9].y = 0x3a98;
    g_9f40[0][19].y = 0x3a98;
    g_9f40[0][27].y = 0x3a98;
    g_9ebc[0] = 4;
    g_9ec2[0][17] = 4;
    g_9ec2[0][27] = 4;
    g_9ec2[0][6] = 7;
    g_9ec2[0][28] = 7;
    g_9f40[0][10].x = 0x32c8;
    g_9f40[0][10].y = 0x32c8;
    g_a120[0].x = 0x32c8;
    g_9f40[0][20].y = 0x1b58;
    g_9f40[0][21].x = 0x1b58;
    g_9f40[0][28].x = 0x1b58;
    g_9f40[0][28].y = 0x1b58;
    g_a120[0].y = 0x1b58;
    g_9f40[0][11].y = 0xbb8;
    g_9f40[0][19].x = 0xbb8;
    g_9f40[0][20].x = 0xbb8;
    g_9f40[0][21].y = 0xbb8;
    g_9ea8[0].x = 0xbb8;
    g_9f40[0][0].y = 0x1770;
    g_9f40[0][5].x = 0x1770;
    g_9f40[0][6].x = 0x1770;
    g_9f40[0][7].y = 0x1770;
    g_9ea8[0].y = 0x1770;
    lstrcpy(g_a12c[1], "SDISPEED");
    g_9eb9[1] = 0x19;
    g_9eb6[1] = 0xa;
    g_9ec2[1][0] = 0xa;
    g_9f40[1][2].x = 0x53fc;
    g_9f40[1][3].y = 0x55f0;
    g_9ec2[1][6] = 7;
    g_9ec2[1][7] = 0xe;
    g_9ec2[1][8] = 0x17;
    g_9f40[1][7].x = 0xdac;
    g_9f40[1][9].x = 0xdac;
    g_9ec2[1][9] = 0;
    g_9ec2[1][3] = 0xb;
    g_9ec2[1][10] = 0xb;
    g_9f40[1][2].y = 0x4a38;
    g_9f40[1][11].y = 0x4a38;
    g_9ec2[1][2] = 2;
    g_9ec2[1][11] = 2;
    g_9f40[1][3].x = 0x4650;
    g_9f40[1][10].x = 0x4650;
    g_9f40[1][11].x = 0x4650;
    g_9f40[1][12].x = 0x4650;
    g_9ec2[1][12] = 0xd;
    g_9ec2[1][13] = 6;
    g_9f40[1][14].x = 0x1d4c;
    g_9f40[1][5].x = 0x2ee0;
    g_9f40[1][8].y = 0x2ee0;
    g_9f40[1][10].y = 0x2ee0;
    g_9f40[1][12].y = 0x2ee0;
    g_9f40[1][13].y = 0x2ee0;
    g_9f40[1][14].y = 0x2ee0;
    g_9ec2[1][14] = 9;
    g_9ec2[1][1] = 0x10;
    g_9ec2[1][15] = 0x10;
    g_9ec2[1][16] = 0x11;
    g_9ec2[1][17] = 0x12;
    g_9ec2[1][18] = 0x15;
    g_9ec2[1][5] = 0x14;
    g_9ec2[1][19] = 0x14;
    g_9f40[1][0].x = 0x5208;
    g_9f40[1][6].y = 0x5208;
    g_9f40[1][7].y = 0x5208;
    g_9f40[1][17].y = 0x5208;
    g_9f40[1][18].x = 0x5208;
    g_9f40[1][20].y = 0x5208;
    g_9ebc[1] = 4;
    g_9ec2[1][20] = 4;
    g_9f40[1][15].x = 0x5dc0;
    g_9f40[1][16].x = 0x5dc0;
    g_9f40[1][17].x = 0x5dc0;
    g_9f40[1][18].y = 0x5dc0;
    g_9f40[1][19].y = 0x5dc0;
    g_9f40[1][21].y = 0x5dc0;
    g_9ec2[1][21] = 0x16;
    g_9f40[1][1].y = 0x3e80;
    g_9f40[1][16].y = 0x3e80;
    g_9f40[1][22].y = 0x3e80;
    g_9f40[1][13].x = 0x1f40;
    g_9f40[1][23].y = 0x1f40;
    g_9ec2[1][23] = 0x18;
    g_9f40[1][15].y = 0x3e8;
    g_9f40[1][21].x = 0x3e8;
    g_9f40[1][22].x = 0x3e8;
    g_9f40[1][23].x = 0x3e8;
    g_9f40[1][24].x = 0x3e8;
    g_9f40[1][24].y = 0x3e8;
    g_9ec2[1][24] = 0xf;
    g_9f40[1][25].x = 0x4844;
    g_9f40[1][25].y = 0x30d4;
    g_9ec2[1][25] = 1;
    g_9f40[1][26].x = 0x34bc;
    g_9f40[1][26].y = 0x396c;
    g_9f40[1][27].x = 0xbb8;
    g_9f40[1][4].x = 0x3a98;
    g_9f40[1][4].y = 0x3a98;
    g_9f40[1][5].y = 0x3a98;
    g_9f40[1][19].x = 0x3a98;
    g_9f40[1][20].x = 0x3a98;
    g_9f40[1][27].y = 0x3a98;
    g_9f40[1][0].y = 0xfa0;
    g_9f40[1][8].x = 0xfa0;
    g_9f40[1][9].y = 0xfa0;
    g_9f40[1][28].x = 0xfa0;
    g_9f40[1][28].y = 0x3520;
    g_9f3a[1][1] = 8;
    g_9ec2[1][22] = 8;
    g_9ec2[1][27] = 8;
    g_9ec2[1][28] = 8;
    g_9f40[1][29].x = 0x3afc;
    g_9f40[1][29].y = 0x3840;
    g_9f3a[1][0] = 5;
    g_9ec2[1][4] = 5;
    g_9ec2[1][26] = 5;
    g_9ec2[1][29] = 5;
    g_9f40[1][30].x = 0x5460;
    g_9f40[1][1].x = 0x5014;
    g_9f40[1][30].y = 0x5014;
    g_9ebf[1] = 3;
    g_9ec2[1][30] = 3;
    g_9f40[1][31].x = 0x125c;
    g_9f40[1][6].x = 0x2af8;
    g_9f40[1][31].y = 0x2af8;
    g_9ec2[1][31] = 9;
    g_a120[1].x = 0x2ee0;
    g_a120[1].y = 0x1388;
    g_9ea8[1].x = 0x3e8;
    g_9ea8[1].y = 0xfa0;
    lstrcpy(g_a12c[2], "GRANDPRI");
    g_9eb9[2] = 0x1f;
    g_9ebc[2] = 5;
    g_9f3a[2][1] = 0xc;
    g_9ec2[2][0] = 1;
    g_9f40[2][1].y = 0x251c;
    g_9ec2[2][2] = 3;
    g_9ebf[2] = 4;
    g_9ec2[2][3] = 4;
    g_9f40[2][5].y = 0x1770;
    g_9ec2[2][6] = 7;
    g_9f3a[2][0] = 0xa;
    g_9ec2[2][9] = 0xa;
    g_9ec2[2][12] = 0x1e;
    g_9f40[2][2].x = 0x1388;
    g_9f40[2][3].x = 0x1388;
    g_9f40[2][3].y = 0x1388;
    g_9f40[2][4].y = 0x1388;
    g_9f40[2][6].y = 0x1388;
    g_9f40[2][13].x = 0x1388;
    g_9f40[2][14].x = 0x1c52;
    g_9ec2[2][14] = 0;
    g_9f40[2][0].y = 0x2af8;
    g_9f40[2][14].y = 0x2af8;
    g_9f40[2][15].y = 0x2af8;
    g_9eb6[2] = 0xe;
    g_9ec2[2][1] = 0xe;
    g_9ec2[2][15] = 0xe;
    g_9ec2[2][16] = 0x12;
    g_9ec2[2][5] = 0x11;
    g_9ec2[2][17] = 0x11;
    g_9ec2[2][18] = 0x14;
    g_9f40[2][0].x = 0x4268;
    g_9f40[2][5].x = 0x4268;
    g_9f40[2][8].y = 0x4268;
    g_9f40[2][17].x = 0x4268;
    g_9f40[2][19].y = 0x4268;
    g_9ec2[2][8] = 0x13;
    g_9ec2[2][19] = 0x13;
    g_9ec2[2][20] = 0x16;
    g_9f40[2][1].x = 0x2710;
    g_9f40[2][11].x = 0x2710;
    g_9f40[2][21].x = 0x2710;
    g_9ec2[2][11] = 0x15;
    g_9ec2[2][21] = 0x15;
    g_9f40[2][22].x = 0xfa0;
    g_9f40[2][18].x = 0x59d8;
    g_9f40[2][19].x = 0x59d8;
    g_9f40[2][20].x = 0x59d8;
    g_9f40[2][20].y = 0x59d8;
    g_9f40[2][21].y = 0x59d8;
    g_9f40[2][22].y = 0x59d8;
    g_9ec2[2][22] = 0x17;
    g_9f40[2][15].x = 0x7d0;
    g_9f40[2][16].x = 0x7d0;
    g_9f40[2][16].y = 0x7d0;
    g_9f40[2][17].y = 0x7d0;
    g_9f40[2][18].y = 0x7d0;
    g_9f40[2][23].x = 0x7d0;
    g_9f40[2][11].y = 0x4a38;
    g_9f40[2][23].y = 0x4a38;
    g_9ec2[2][23] = 0x10;
    g_9f40[2][6].x = 0x4e20;
    g_9f40[2][7].x = 0x4e20;
    g_9f40[2][9].x = 0x4e20;
    g_9f40[2][9].y = 0x4e20;
    g_9f40[2][10].y = 0x4e20;
    g_9f40[2][12].y = 0x4e20;
    g_9f40[2][24].x = 0x4e20;
    g_9f40[2][2].y = 0x2328;
    g_9f40[2][24].y = 0x2328;
    g_9ec2[2][4] = 0x19;
    g_9ec2[2][24] = 0x19;
    g_9ec2[2][25] = 0x1a;
    g_9f40[2][25].y = 0x1f40;
    g_9f40[2][26].x = 0x1f40;
    g_9ec2[2][26] = 2;
    g_9ec2[2][27] = 0x1d;
    g_9f40[2][10].x = 0x32c8;
    g_9f40[2][27].x = 0x32c8;
    g_9f40[2][28].x = 0x32c8;
    g_9f40[2][4].x = 0x36b0;
    g_9f40[2][7].y = 0x36b0;
    g_9f40[2][13].y = 0x36b0;
    g_9f40[2][25].x = 0x36b0;
    g_9f40[2][28].y = 0x36b0;
    g_9ec2[2][7] = 0x1c;
    g_9ec2[2][10] = 0x1c;
    g_9ec2[2][13] = 0x1c;
    g_9ec2[2][28] = 0x1c;
    g_9f40[2][12].x = 0x1b58;
    g_9f40[2][26].y = 0x1b58;
    g_9f40[2][29].x = 0x1b58;
    g_9f40[2][8].x = 0x3e80;
    g_9f40[2][27].y = 0x3e80;
    g_9f40[2][29].y = 0x3e80;
    g_9ec2[2][29] = 0xc;
    g_9ec2[2][31] = 1;
    g_9f40[2][32].x = 0xfa0;
    g_9ec2[2][32] = 3;
    g_9f40[2][33].y = 0x38a4;
    g_9ec2[2][33] = 8;
    g_9f40[2][33].x = 0x4268;
    g_9f40[2][34].x = 0x4268;
    g_9f40[2][34].y = 0x4c2c;
    g_9ec2[2][34] = 9;
    g_9f40[2][35].x = 0x1194;
    g_9f40[2][35].y = 0x4a38;
    g_9f40[2][30].x = 0x1388;
    g_9f40[2][36].y = 0x1388;
    g_9ec2[2][36] = 5;
    g_9f40[2][37].x = 0x55f0;
    g_9f40[2][30].y = 0x3e80;
    g_9f40[2][36].x = 0x3e80;
    g_9f40[2][37].y = 0x3e80;
    g_9ec2[2][37] = 7;
    g_9f40[2][38].y = 0x445c;
    g_9ec2[2][38] = 0xb;
    g_9f40[2][32].y = 0xbb8;
    g_9f40[2][39].x = 0xbb8;
    g_9ec2[2][30] = 0xd;
    g_9ec2[2][35] = 0xd;
    g_9ec2[2][39] = 0xd;
    g_9f40[2][31].y = 0x2710;
    g_9f40[2][38].x = 0x2710;
    g_a120[2].x = 0x2710;
    g_a120[2].y = 0x3a98;
    g_9ea8[2].x = 0x2af8;
    g_9f40[2][31].x = 0x36b0;
    g_9f40[2][39].y = 0x36b0;
    g_9ea8[2].y = 0x36b0;
}

/* Finds or builds the sprite surface (23..27) for the key (k1, k2, type)
 * kept in g_38a4: returns its index (1 when none is free). Draws 16 cells
 * of bitmap k1 as background and bitmap k2 rotated round a circle (or,
 * with flag, 16 straight frames) on top, then stores the cell size and
 * border in g_4d90[rec] [inferred]. pal0 is read uninitialised when
 * g_920e is 0 (as in the original). */
/* @addr 10:18b0 */
int far fn_10_18b0(int k1, int k2, int type, int flag, int rec)
{
    int sz0;
    int sz;
    int m;
    int half;
    int cell;
    int i;
    int free;
    int k;
    int u14;
    char col;
    HDC dc0;
    HDC dc1;
    HBITMAP bm0;
    HBITMAP old0;
    HBITMAP bm1;
    HBITMAP old1;
    HBITMAP bm2;
    HPALETTE pal0;
    int r;
    int ang;
    POINT d;
    BITMAP bmp;
    int mode;

    free = 0;
    for (i = 23; i < 28; i++) {
        if (!g_39e8[i])
            free = i;
        if (g_38a4[i - 23].b == k1 && g_38a4[i - 23].a == k2 && g_38a4[i - 23].c == type)
            return i;
    }
    if (free == 0)
        return 1;
    if (free >= 28)
        return 1;
    k = free - 23;
    g_38a4[k].b = k1;
    g_38a4[k].a = k2;
    g_38a4[k].c = type;
    if (k1 != -1) {
        bm0 = fn_10_6c02(k1, 3, -1);
        GetObject(bm0, 14, &bmp);
        dc0 = CreateCompatibleDC(g_13dc);
        old0 = SelectObject(dc0, bm0);
        sz0 = fn_10_86ca();
    } else {
        sz0 = 0;
        dc0 = 0;
    }
    cell = g_1e18->f24;
    if (g_90f4 == 1 && (G_1E68_HI || G_1E68_LO)) {
        if (g_931e == 1 || g_931e == 2)
            mode = 1;
        else
            mode = 0;
    } else if (g_931e == 2)
        mode = 1;
    else
        mode = 0;
    if (type == 1)
        col = 9;
    else if (type == 4)
        col = 15;
    else
        col = 12;
    fn_10_6ee6(28, k2, "", 1, 100, type, type, 1, -1, col, col, 0, mode);
    SelectObject(g_39e8[28], g_3974[28]);
    bm1 = fn_10_6ec6(g_3ad0[28]);
    SelectObject(g_39e8[28], g_3ad0[28]);
    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, bm1);
    bm2 = fn_10_6c02(k2, 0, -1);
    GetObject(bm2, 14, &bmp);
    sz = fn_10_86ca();
    DeleteObject(bm2);
    if (sz * 2 > sz0 && !flag)
        m = sz * 2 - 1;
    else if (sz > sz0 && flag)
        m = sz;
    else
        m = sz0;
    for (i = 23; i < 28; i++)
        if (!g_39e8[i])
            free = i;
    u14 = m;
    if (m & 1)
        cell = 5;
    else
        cell = 6;
    g_39e8[free] = CreateCompatibleDC(g_13dc);
    g_3ad0[free] = CreateCompatibleBitmap(g_13dc, m * 16 + cell * 17, cell * 2 + m);
    g_3974[free] = SelectObject(g_39e8[free], g_3ad0[free]);
    if (g_920e) {
        if (dc0)
            pal0 = SelectPalette(dc0, g_920e, 0);
        g_3a5c[free] = SelectPalette(g_39e8[free], g_920e, 0);
    }
    PatBlt(g_39e8[free], 0, 0, m * 16 + cell * 17, cell * 2 + m, BLACKNESS);
    if (k1 != -1) {
        for (i = 0; i < 16; i++)
            BitBlt(g_39e8[free], (m - sz0) / 2 + (cell + m) * i + cell, (m - sz0) / 2 + cell,
                   sz0, sz0, dc0, 0, 0, SRCCOPY);
        SelectObject(dc0, old0);
        if (pal0)
            SelectPalette(dc0, pal0, 0);
        DeleteDC(dc0);
        if (bm0) {
            DeleteObject(bm0);
            bm0 = 0;
        }
    }
    r = half = sz / 2;
    if (!flag) {
        for (i = 0, ang = 270; i < 16; i++, ang -= i % 2 + 22) {
            d.x = fn_06_720c(ang) * r / 128 + half;
            d.y = half - fn_06_71b2(ang) * r / 128;
            BitBlt(g_39e8[free], (cell + m) * i + m / 2 - d.x + cell, m / 2 - d.y + cell,
                   sz, sz, dc1, i * sz, 0, SRCAND);
            BitBlt(g_39e8[free], (cell + m) * i + m / 2 - d.x + cell, m / 2 - d.y + cell,
                   sz, sz, g_39e8[28], i * sz, 0, SRCPAINT);
        }
    } else {
        for (i = 0; i < 16; i++)
            BitBlt(g_39e8[free], (cell + m) * i + (m - sz) / 2 + cell, (m - sz) / 2 + cell,
                   sz, sz, g_39e8[28], i * sz, 0, SRCCOPY);
    }
    fn_10_0552(28, 0);
    SelectObject(dc1, old1);
    DeleteDC(dc1);
    DeleteObject(bm1);
    fn_10_6308(free, 1, 1, 1);
    if (m & 1) {
        cell = 4;
        m++;
    } else
        cell = 6;
    g_4d90[rec].f08 = m;
    g_4d90[rec].f09 = cell;
    return free;
}

/* Sets the per-list object defaults (sizes scaled by the zoom g_9156,
 * draw/collision handlers f5e/f62/f66) for every object of lists 0..11,
 * then clears g_2408 and g_238c. f28 is stored twice for list 0 (as in
 * the original). */
/* @addr 10:0b94 */
void far fn_10_0b94(void)
{
    int i;
    int v6;
    int v8;

    for (i = 0; i < g_92ec[0]; i++) {
        g_1df8[0][i].f22 = SC(32);
        g_1df8[0][i].f20 = 256;
        g_1df8[0][i].f24 = SC(6);
        g_1df8[0][i].f28 = i;
        g_1df8[0][i].f44 = 160;
        g_1df8[0][i].f42 = 18;
        g_1df8[0][i].f46 = 2;
        g_1df8[0][i].f62 = fn_11_39d8;
        g_1df8[0][i].f5e = fn_07_233c;
        g_1df8[0][i].f53 = 1;
        g_1df8[0][i].f28 = i;
    }
    for (i = 0; i < g_92ec[1]; i++) {
        g_1df8[1][i].f22 = SC(20);
        g_1df8[1][i].f24 = SC(6);
        g_1df8[1][i].f20 = 160;
        g_1df8[1][i].f44 = 60;
        g_1df8[1][i].f42 = 18;
        g_1df8[1][i].f4c = 0x808000L;
        g_1df8[1][i].f2c = 14;
        g_1df8[1][i].f1e = 0;
        g_1df8[1][i].f18 = 1;
        g_1df8[1][i].f04.x = -1000;
        g_1df8[1][i].f04.y = -1000;
        g_1df8[1][i].f66 = fn_07_2e02;
        g_1df8[1][i].f62 = fn_11_3914;
        g_1df8[1][i].f5e = fn_07_2652;
        g_1df8[1][i].f53 = 0;
        g_1df8[1][i].f48 = 1;
    }
    for (i = 0; i < g_92ec[2]; i++) {
        g_1df8[2][i].f22 = SC(14);
        g_1df8[2][i].f24 = SC(2);
        g_1df8[2][i].f20 = 104;
        g_1df8[2][i].f44 = 55;
        g_1df8[2][i].f48 = 0;
        g_1df8[2][i].f42 = 7;
        g_1df8[2][i].f2f = 4;
        g_1df8[2][i].f4c = 0xffffL;
        g_1df8[2][i].f62 = fn_11_3914;
        g_1df8[2][i].f5e = fn_08_95f2;
        g_1df8[2][i].f53 = 0;
    }
    for (i = 0; i < g_92ec[3]; i++) {
        if (i < g_92ec[3] - g_92ea) {
            g_1df8[3][i].f22 = SC(44);
            g_1df8[3][i].f20 = 344;
            g_1df8[3][i].f44 = 1400;
            g_1df8[3][i].f62 = fn_11_3bae;
            g_1df8[3][i].f2c = 60;
            g_1df8[3][i].f24 = SC(4);
        } else {
            g_1df8[3][i].f22 = SC(22);
            g_1df8[3][i].f20 = 168;
            g_1df8[3][i].f44 = 350;
            g_1df8[3][i].f62 = fn_11_3914;
            g_1df8[3][i].f2c = 200;
            g_1df8[3][i].f24 = SC(4);
            if (g_9156 == 2)
                g_1df8[3][i].f24 = 4;
            if (g_9156 == 1 && g_0740)
                g_1df8[3][i].f24 = 2;
            if (g_9156 == 0 && g_0740)
                g_1df8[3][i].f24 = 1;
        }
        g_1df8[3][i].f48 = 9;
        g_1df8[3][i].f42 = 8;
        g_1df8[3][i].f46 = 4;
        g_1df8[3][i].f4c = 0xc0c0c0L;
        g_1df8[3][i].f5e = fn_07_5090;
        g_1df8[3][i].f53 = 0;
        g_1df8[3][i].f54 = 0;
    }
    if (!g_9214) {
        v6 = 36;
        v8 = 6;
    } else {
        v6 = 30;
        v8 = 4;
    }
    for (i = 0; i < g_92ec[4]; i++) {
        g_1df8[4][i].f22 = SC(v6);
        g_1df8[4][i].f20 = v6 * 8;
        g_1df8[4][i].f24 = SC(v8);
        g_1df8[4][i].f44 = 110;
        g_1df8[4][i].f42 = 30;
        g_1df8[4][i].f4c = 0xffL;
        g_1df8[4][i].f48 = 10;
        g_1df8[4][i].f46 = 5;
        g_1df8[4][i].f62 = fn_11_3bae;
        g_1df8[4][i].f5e = fn_12_0dc4;
        g_1df8[4][i].f53 = 1;
        g_1df8[4][i].f54 = 0;
    }
    for (i = 0; i < g_92ec[5]; i++) {
        g_1df8[5][i].f44 = 120;
        g_1df8[5][i].f42 = 100;
        g_1df8[5][i].f4c = 0xffL;
        g_1df8[5][i].f62 = fn_11_3914;
        g_1df8[5][i].f5e = fn_07_570a;
        g_1df8[5][i].f53 = 0;
        g_1df8[5][i].f54 = 0;
    }
    for (i = 0; i < g_92ec[6]; i++) {
        g_1df8[6][i].f44 = 20;
        g_1df8[6][i].f42 = 6;
        g_1df8[6][i].f4c = 0x7f00L;
        g_1df8[6][i].f2c = -1;
        g_1df8[6][i].f48 = 5;
        g_1df8[6][i].f62 = fn_11_3914;
        g_1df8[6][i].f5e = fn_07_2652;
        g_1df8[6][i].f53 = 0;
        g_1df8[6][i].f54 = 0;
    }
    g_1df8[7][0].f22 = SC(40);
    g_1df8[7][0].f20 = 320;
    g_1df8[7][0].f24 = SC(6);
    g_1df8[7][0].f44 = 800;
    g_1df8[7][0].f42 = 8;
    g_1df8[7][0].f18 = 1;
    g_1df8[7][0].f2c = 800;
    g_1df8[7][0].f46 = 1;
    g_1df8[7][0].f48 = 7;
    g_1df8[7][0].f66 = fn_12_274a;
    g_1df8[7][0].f62 = fn_11_37a0;
    g_1df8[7][0].f5e = fn_16_085e;
    g_1df8[7][0].f53 = 0;
    g_1df8[7][0].f54 = 0;
    for (i = 0; i < g_92ec[8]; i++) {
        g_1df8[8][i].f0c = 0;
        g_1df8[8][i].f0e = 0;
        g_1df8[8][i].f53 = 0;
    }
    for (i = 0; i < g_92ec[9]; i++) {
        g_1df8[9][i].f22 = SC(38);
        g_1df8[9][i].f20 = 296;
        g_1df8[9][i].f24 = SC(4);
        g_1df8[9][i].f44 = 360;
        g_1df8[9][i].f18 = 1;
        g_1df8[9][i].f42 = 18;
        g_1df8[9][i].f46 = 6;
        g_1df8[9][i].f2c = 80;
        g_1df8[9][i].f48 = 4;
        g_1df8[9][i].f62 = fn_11_39d8;
        g_1df8[9][i].f5e = fn_07_2652;
        g_1df8[9][i].f66 = fn_12_274a;
        g_1df8[9][i].f53 = 0;
        g_1df8[9][i].f54 = 0;
        g_1df8[9][i].f2f = 7;
    }
    for (i = 0; i < g_92ec[10]; i++) {
        g_1df8[10][i].f22 = SC(12);
        g_1df8[10][i].f20 = 96;
        g_1df8[10][i].f24 = SC(6);
        g_1df8[10][i].f0c = 0;
        g_1df8[10][i].f0e = 0;
        g_1df8[10][i].f44 = 11;
        g_1df8[10][i].f18 = 1;
        g_1df8[10][i].f42 = 6;
        g_1df8[10][i].f46 = 4;
        g_1df8[10][i].f4c = 0x7f7f7fL;
        g_1df8[10][i].f2c = -1;
        g_1df8[10][i].f48 = 0;
        g_1df8[10][i].f66 = fn_12_274a;
        g_1df8[10][i].f62 = fn_11_3914;
        g_1df8[10][i].f5e = fn_07_2652;
        g_1df8[10][i].f53 = 0;
        g_1df8[10][i].f54 = 0;
    }
    for (i = 0; i < g_92ec[11]; i++) {
        g_1df8[11][i].f24 = SC(4);
        g_1df8[11][i].f44 = 101;
        g_1df8[11][i].f18 = 1;
        g_1df8[11][i].f42 = 18;
        g_1df8[11][i].f46 = 2;
        g_1df8[11][i].f2c = 400;
        g_1df8[11][i].f48 = 5;
        g_1df8[11][i].f62 = fn_11_39d8;
        g_1df8[11][i].f5e = fn_07_2652;
        g_1df8[11][i].f66 = fn_12_6a60;
        g_1df8[11][i].f53 = 1;
        g_1df8[11][i].f54 = 0;
    }
    g_238c = g_2408 = 0;
}
