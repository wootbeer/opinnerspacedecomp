/* INSPACE.EXE segment 12 (selector 1058). No 32-bit code anywhere in this
 * segment: compiled with /G2 [inferred, confirmed by matches]. */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include <stdlib.h>
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array per object type
 * [inferred, as in seg07.c]. Only the fields used here are named. */
typedef struct {
    POINT f00;                  /* +00 */
    POINT f04;                  /* +04 */
    char p08[4];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    char p14[0x18 - 0x14];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    int f1c;                    /* +1c */
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    int f2a;                    /* +2a */
    int f2c;                    /* +2c */
    char f2e;                   /* +2e */
    char f2f;                   /* +2f */
    char f30;                   /* +30 */
    char p31;
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    HDC f3a;                    /* +3a */
    HDC f3c;                    /* +3c */
    HBITMAP f3e;                /* +3e */
    HBITMAP f40;                /* +40 */
    int f42;                    /* +42 */
    int f44;                    /* +44 */
    char p46[2];
    int f48;                    /* +48 */
    int f4a;                    /* +4a */
    long f4c;                   /* +4c */
    char f50;                   /* +50 */
    char f51;                   /* +51 */
    char f52;                   /* +52 */
    char f53;                   /* +53 */
    char f54;                   /* +54 */
    char p55[0x5e - 0x55];
    void (far *f5e)(void);      /* +5e */
    void (far *f62)(void);      /* +62 */
    void (far *f66)(int type, int idx);  /* +66 */
    unsigned long f6a;          /* +6a */
    HPALETTE f6e;               /* +6e */
} REC_70;
extern REC_70 far *g_1df8[16];

/* 0x15a-byte records at DS:70ae (as in seg09.c). */
typedef struct {
    int f00;                    /* +00 */
    char p02[0x10 - 0x02];
    int f10;                    /* +10 */
    char p12[2];
    int f14;                    /* +14 */
    int f16;                    /* +16 */
    char p18[0x30 - 0x18];
    int f30;                    /* +30 */
    char p32[2];
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    int f3a;                    /* +3a */
    char p3c[0x90 - 0x3c];
    char f90[10];               /* +90 */
    char f9a[0x13];             /* +9a */
    char fad;                   /* +ad: entries used in f9a [inferred] */
    char pae[0xb8 - 0xae];
    int fb8;                    /* +b8 */
    char pba[0xca - 0xba];
    char fca;                   /* +ca */
    char pcb;
    char fcc;                   /* +cc */
    char pcd;
    char fce;                   /* +ce */
    char pcf[0x129 - 0xcf];
    char f129;                  /* +129 */
    char p12a[0x15a - 0x12a];
} REC_15A;
extern REC_15A g_70ae[];
/* The same records seen from DS:70a0 (0xe bytes earlier). */
extern struct { int f00; char p02[0x15a - 2]; } g_70a0[];

/* 0x50-byte records at DS:2f5e [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p04[0x0a - 0x04];
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    char p0e[0x14 - 0x0e];
    int f14;                    /* +14 */
    char p16[0x50 - 0x16];
} REC_50;
extern REC_50 g_2f5e[];

/* 0x1c-byte records at DS:66e4 [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    char p02[6];
    int f08;                    /* +08 */
    char p0a[0x16 - 0x0a];
    int f16;                    /* +16 */
    char p18[0x1c - 0x18];
} REC_1C;
extern REC_1C g_66e4[];

/* 0x14-byte records at DS:1e90 [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p04[2];
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    char p0c[4];
    long f10;                   /* +10 */
} REC_14;
extern REC_14 g_1e90[];
extern POINT g_5170[];
extern POINT g_5224[];
extern int g_9430;
extern int g_9434;
extern int g_9316;
extern int g_9320;
/* 0x34-byte records at DS:3d82 [inferred]. */
typedef struct { int f00; char p02[0x34 - 2]; } REC_34;
extern REC_34 g_3d82[];
extern REC_34 g_3d6c[];         /* the same records seen 0x16 bytes earlier */
/* The same records from their start, DS:3d5a (as in seg10.c). */
typedef struct {
    int f00;                    /* +00 */
    char p02[0x22 - 0x02];
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    char p26[0x34 - 0x26];
} REC_34B;
extern REC_34B g_3d5a[];

/* 0x10-byte records at DS:693c [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p04[4];
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    char p0c[4];
} REC_10B;
extern REC_10B g_693c[];
/* 0x20-byte records at DS:65cc: links between two objects [inferred]. */
typedef struct {
    int t1;                     /* +00 */
    int i1;                     /* +02 */
    int t2;                     /* +04 */
    int i2;                     /* +06 */
    int f08;                    /* +08 */
    char p0a[6];
    POINT f10;                  /* +10 */
    POINT f14;                  /* +14 */
    POINT f18;                  /* +18 */
    POINT f1c;                  /* +1c */
} REC_20;
extern REC_20 g_65cc[];
extern int g_9300;
extern int g_0d06;
extern int g_0d08;
extern int g_1c32;
extern int g_9156;
extern int g_9416;
extern int g_949a;
extern int g_949c;
extern int g_949e;
extern int g_94a0;
extern long g_1e50;
extern unsigned long g_1e68;
extern long g_6988;
extern long g_666c;

/* 0x10-byte records at DS:4f32 [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    POINT f04;                  /* +04 */
    char p08[8];
} REC_10;
extern REC_10 g_4f32[];
extern POINT g_1050[];
extern int g_9334;
extern int g_9208;
extern int g_9324;
extern int g_9326;
extern int g_9406[];

void far fn_07_2080(int a, int b);
void far fn_10_533a(int a);
int far fn_10_754a(int a, int b, int c, int d);
int far fn_04_8c80(void);
void far fn_07_5b68(int type, int idx, int c);
POINT far pascal fn_08_29ea(POINT pt);
BOOL far fn_08_7ba8(POINT pt);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
int far pascal fn_08_19b0(int dx, int dy);
int far fn_09_88ba(int x);
void far pascal fn_11_7c12(int kind, int type, int idx);
void far fn_11_8a42(int type, int idx);
void far fn_11_947a(int type, int idx, int kind);
void far fn_11_9fdc(int type, int idx);
void far fn_11_9daa(int type, int idx);
void far fn_11_9078(int type, int idx);
void far pascal fn_12_2db6(int type, int idx, int c, int d, int kind);
extern char g_9eb5;
extern int g_1c2c;
extern RECT g_1c18;
extern POINT g_9ea8[];
extern int g_9322;
extern int g_92f4;
extern int g_941c;
extern int g_9344;
extern int g_9418;
extern unsigned long g_1c2e;
int far fn_13_59e8(int type, int idx);
void far fn_11_a234(int type, int idx, int t2, int i2);
extern int g_9142;
extern int g_9214;
#pragma pack(1)
typedef struct { char p00[2]; int f02; char p04[0x23 - 4]; } REC_23;
#pragma pack()
extern REC_23 g_57a8[];          /* 0x23-byte records */
void far fn_12_0e5c(int idx);
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    char p0c[0x10 - 0x0c];
    int f10;                    /* +10 */
    int f12;                    /* +12 */
} REC_14C;                      /* [inferred] */
extern int g_92ec[];
extern HGLOBAL g_9100[];
extern int g_5eac[][0x12];      /* [inferred] */
void far fn_07_570a(void);
void far fn_11_3914(void);
extern REC_14C g_5a4c[];
extern int g_93b6;
extern int g_93a4;
extern long g_1e80;
extern int g_668a;
void far fn_07_13b2(int a, int type, int idx);
void far fn_07_5ae8(int idx, int a);
/* The 0x50-byte records of DS:2f5e seen from DS:2f5a [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    char p02[2];
    int f04;                    /* +04 */
    int f06;                    /* +06: thrust */
    int f08;                    /* +08: top speed */
    char p0a[0x1a - 0x0a];
    int f1a;                    /* +1a: range */
    char p1c[0x38 - 0x1c];
    int f38;                    /* +38 */
    char p3a[0x50 - 0x3a];
} REC_50B;
extern REC_50B g_2f5a[];
int far pascal steer_toward_direction(int y2, int x2, int y1, int x1, int cur,
                                      int mode, int obj, int a, int b, int c);
void far pascal fn_08_1cbe(WORD r, int v);
void far fn_12_274a(int type, int idx);
void far pascal spawn_gun_shot(int s, int k);
/* The 0x10-byte records of DS:4f32 from DS:4f2c: groups of objects
 * turning round a centre [inferred]. */
typedef struct {
    int first;                  /* +00 */
    int end;                    /* +02 */
    int radius;                 /* +04 */
    char p06[4];
    int cx;                     /* +0a */
    int cy;                     /* +0c */
    int speed;                  /* +0e */
} REC_10C;
extern REC_10C g_4f2c[];
int far fn_06_71b2(int deg);
int far fn_06_720c(int deg);
extern int g_9328;
/* The 0x1c-byte records of DS:66e4 from their start, DS:66e0 [inferred]. */
typedef struct {
    int f00;                    /* +00: target type */
    int f02;                    /* +02: target index */
    int f04;                    /* +04 */
    char p06[2];
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    int f14;                    /* +14 */
    int f16;                    /* +16 */
    char p18[0x1a - 0x18];
    int f1a;                    /* +1a */
} REC_1CB;
extern REC_1CB g_66e0[];
extern char g_9ebc[];
extern char g_9eb9[];
extern char g_9ebf[];
extern POINT g_9f40[][40];
extern int g_940e;
extern unsigned long g_698c;
extern int g_943a;
extern int g_943c;
extern int g_92e8;
extern HDC g_39e8[];
/* 0x34-byte records at DS:8560 [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    char p02[2];
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    char p08[0x34 - 0x08];
} REC_34C;
extern REC_34C g_8560[];
void far pascal fn_08_1b54(WORD r, int n);
void far pascal fn_08_1d54(WORD r, int v);
void far pascal fn_08_0b76(int a, int b, HDC dc, int c);
int far pascal fn_08_50aa(int a);
int far pascal fn_08_546c(int a, int far *b, int far *c, int d, int e);
void far fn_08_5df2(int a, int b, int c, int d, int e);
void far fn_13_16ac(int a, int b);
void far fn_12_129e(int type, int idx);
#pragma pack(1)
typedef struct {
    int f00;                    /* +00 */
    char p02[0x1a - 0x02];
    int f1a;                    /* +1a */
    char p1c[0xad - 0x1c];
} REC_AD;                       /* [inferred] */
#pragma pack()
extern REC_AD g_96f0[];
extern int g_9646;
extern int g_90ea;
extern int g_90ec;
extern int hazards_ship_redraw_pending;    /* DS:058a */
int far pascal fn_12_67e8(POINT a, POINT b, int mode, int cur);
void far fn_08_348e(int type, int idx, int type2, int idx2, int speed);
extern int g_05a2;
/* DS:05a0 is read as an int here (map width [inferred]); inspace.h
 * declares it long. */
#define G_05A0_INT (*(int *)&g_05a0)

/* @addr 12:0a26 */
void far fn_12_0a26(int a)
{
    int i;

    for (i = 0; i < 45; i++) {
        if (g_1e90[i].f00 == -1) {
            g_1e90[i].f0a = 3;
            g_1e90[i].f00 = 1;
            g_1e90[i].f02 = 0xb;
            g_1e90[i].f06 = 6;
            g_1e90[i].f08 = a;
            if (i > g_9434)
                g_9434 = i;
            g_5170[i] = g_1df8[6][a].f00;
            g_5224[i] = g_1df8[6][a].f04;
            if (i > g_9434)
                g_9434 = i;
            g_9430++;
            break;
        }
    }
    fn_10_754a(0x45, 6, a, 1);
    g_66e4[a].f16 = 0;
}

/* @addr 12:0dc4 */
int far fn_12_0dc4(int type, int idx, int v)
{
    g_1df8[type][idx].f1e += v;
    if (g_1df8[type][idx].f2f == 0)
        g_1df8[type][idx].f2f = 1;
    g_1df8[type][idx].f50 = g_1df8[type][idx].f1e / 10 < 1 ? 1 : g_1df8[type][idx].f1e / 10;
    if (g_1df8[type][idx].f50 > 5) {
        g_1df8[type][idx].f66(type, idx);
        fn_07_2080(type, idx);
        return 1;
    }
    return 0;
}

/* Release an object's memory DC and bitmap [inferred]. */
/* @addr 12:26a4 */
void far fn_12_26a4(int type, int idx)
{
    if (g_1df8[type][idx].f3c) {
        SelectObject(g_1df8[type][idx].f3c, g_1df8[type][idx].f40);
        if (g_920e)
            SelectPalette(g_1df8[type][idx].f3c, g_1df8[type][idx].f6e, 0);
        DeleteDC(g_1df8[type][idx].f3c);
        g_1df8[type][idx].f3c = 0;
    }
    if (g_1df8[type][idx].f3e) {
        DeleteObject(g_1df8[type][idx].f3e);
        g_1df8[type][idx].f3e = 0;
    }
}

/* @addr 12:6cf6 */
void far fn_12_6cf6(void)
{
    int t;
    int i;

    for (t = g_9326; t <= g_9324; t++) {
        for (i = 0; i < g_9406[t]; i++) {
            if (g_1df8[t][i].f54) {
                g_1df8[t][i].f0e = 0;
                g_1df8[t][i].f0c = g_1df8[t][i].f0e;
            }
        }
    }
}

/* @addr 12:6d64 */
void far fn_12_6d64(int a, int b)
{
    int i;

    for (i = 1; i < g_70ae[a].fad; i++)
        if (g_70ae[a].f9a[i] == b)
            return;
    if (g_70ae[a].fad > 9)
        return;
    g_70ae[a].fad++;
    i = g_70ae[a].fad - 1;
    g_70ae[a].f9a[i] = b;
    g_70ae[a].f90[i] = 20;
    if (g_2f5e[b].f00)
        fn_10_533a(g_70ae[a].f9a[i]);
}

/* @addr 12:6a60 */
void far fn_12_6a60(int type, int idx)
{
    int i;

    if (fn_08_7ba8(fn_08_29ea(g_1df8[type][idx].f04)))
        PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
               g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
    if (type == 6) {
        g_66e4[idx].f08 = g_2f5e[g_66e4[idx].f00].f14;
        g_66e4[idx].f00 = -1;
    }
    for (i = 0; i < 5; i++)
        fn_07_5b68(type, idx, 1);
    g_1df8[type][idx].f18 = 1;
}

/* Nearest live object of type g_9324 within 700 of (type, idx), as
 * (g_9324 << 8) | index, or -1 [inferred]. */
/* @addr 12:6706 */
int far pascal fn_12_6706(int type, int idx)
{
    int i;
    int d;
    int best;
    int bi;
    int k;
    int j;

    if (g_9320 == 6) {
        k = fn_04_8c80();
        if (k >= 0 && g_1df8[14][k].f51 == 0)
            return (char)k | g_9324 << 8;
        else
            return -1;
    }
    best = 20000;
    bi = -1;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[g_9324][i].f18 == 0) {
            d = fn_08_285a(&k, &j, g_1df8[type][idx].f04, g_1df8[g_9324][i].f04);
            if (d < best) {
                best = d;
                bi = i;
            }
        }
    }
    if (best >= 700)
        return -1;
    return (char)bi | g_9324 << 8;
}

/* Not yet decompiled: stubs so calls to them compile as near calls. */

extern int g_9498;
extern long g_1e84;
extern int flow_interactive;    /* DS:95bc */

/* Object (type, idx) explodes into debris particles [inferred]. */
/* @addr 12:274a */
void far fn_12_274a(int type, int idx)
{
    int k;
    int j;
    int n;

    if (g_9406[type] <= idx) {
        g_9498++;
        if (g_92ec[type] <= idx)
            return;
        if (type == g_9324 && idx > g_9316)
            return;
    }
    if (type == 4)
        g_698c = g_1e50 + 10000;
    if (!(type == 8 && g_3d6c[idx].f00 == 1)
        && fn_08_7ba8(fn_08_29ea(g_1df8[type][idx].f04)))
        PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
               g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
    if (g_1df8[type][idx].f48 == 1) {
        n = 1;
    } else {
        switch (g_9208) {
        case 0:
            n = g_1df8[type][idx].f48 * 30 / 100;
            break;
        case 1:
            n = g_1df8[type][idx].f48 * 60 / 100;
            break;
        case 2:
            n = g_1df8[type][idx].f48;
            break;
        case 3:
            n = g_1df8[type][idx].f48 * 130 / 100;
            break;
        }
        n = n < 2 ? 2 : n;
    }
    if (g_9430 > 10)
        n = (35 - g_9430) * n / 25 < 1 ? 1 : (35 - g_9430) * n / 25;
    for (k = 0; k < n; k++) {
        for (j = 0; j < 45; j++) {
            if (g_1e90[j].f00 == -1) {
                if (k == 0)
                    g_1e90[j].f0a = 4;
                else
                    g_1e90[j].f0a = 1;
                g_1e90[j].f00 = 1;
                if (j > g_9434)
                    g_9434 = j;
                g_1e90[j].f10 = (long)(rand() % 110) + k * 30 + g_1e50;
                g_1e90[j].f02 = 10;
                if (k > (g_9208 >> 1) + 2 && rand() % 10 <= 6) {
                    g_1e90[j].f02 -= rand() % 4 + 4;
                    g_1e90[j].f10 += 60;
                }
                g_1e90[j].f06 = type;
                g_1e90[j].f08 = idx;
                { int pad[2];
                if (k == 0) {
                    g_5224[j] = g_1df8[type][idx].f04;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                } else {
                    g_5224[j].x = (rand() % ((n + 40) * 2) - n - 40) * 8
                        + g_1df8[type][idx].f20 / 2 + g_1df8[type][idx].f04.x;
                    g_5224[j].y = (rand() % ((n + 40) * 2) - n - 40) * 8
                        + g_1df8[type][idx].f20 / 2 + g_1df8[type][idx].f04.y;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                }
                }
                g_9430++;
                break;
            }
        }
    }
    if (!(type == 8 && g_3d6c[idx].f00 == 1)) {
        g_1df8[type][idx].f18 = 1;
        if (type == g_9324 && idx == g_9646) {
            if (flow_interactive) {
                g_1e84 = g_1e50 + 1500;
            } else {
                g_1e84 = 0;
                g_1e80 = g_1e50 + 1500;
            }
        }
    }
    if (type == 6) {
        g_66e4[idx].f08 = g_2f5e[g_66e4[idx].f00].f14;
        g_66e4[idx].f00 = -1;
    }
    fn_10_754a(0x45, type, idx, 1);
}

extern int g_8ffe;
void far fn_07_1208(void);
/* Scale a size to the current zoom (g_9156) [inferred]. */
#define SC(n) ((n) << g_9156 >> 1)

/* Draw the type-4 object idx shrinking as its f51 counter runs down
 * [inferred]. */
/* @addr 12:0e5c */
void far fn_12_0e5c(int idx)
{
    int v;
    int w;
    int h;
    int sx;
    int flag;

    w = g_1df8[4][idx].f22;
    h = g_1df8[4][idx].f24;
    if (g_8ffe != 0 && g_1df8[4][idx].f51 > 8)
        flag = 1;
    else
        flag = 0;
    g_1df8[4][idx].f51 -= (char)g_8ffe;
    if (g_1df8[4][idx].f51 < 0)
        g_1df8[4][idx].f51 = 0;
    v = 9 - g_1df8[4][idx].f51;
    SetStretchBltMode(g_13dc, 3);
    if (g_1df8[4][idx].f48 == g_9646 && g_9208 > 1 && (v & 1))
        fn_07_1208();
    if ((g_9214 == 3 || g_9214 == 4) && g_1df8[4][idx].f26 != 0)
        sx = h + w;
    else
        sx = 0;
    if (g_1df8[4][idx].f1a == 0)
        return;
    switch (v) {
    case 0:
        StretchBlt(g_13dc, g_1df8[4][idx].f00.x, g_1df8[4][idx].f00.y, w, w,
                   g_39e8[4], sx - SC(3) + h, h - SC(3), SC(6) + w, SC(6) + w, SRCCOPY);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        StretchBlt(g_13dc, SC(v) * 2 + g_1df8[4][idx].f00.x, g_1df8[4][idx].f00.y - SC(2),
                   w - SC(v) * 4, SC(3) + w,
                   g_39e8[4], sx, 0, h * 2 + w, h * 2 + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, g_1df8[4][idx].f00.x - SC(2) + SC(v) * 2, g_1df8[4][idx].f00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[4][idx].f00.x - SC(v) * 2 + w, g_1df8[4][idx].f00.y,
                   SC(2), w, BLACKNESS);
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        v -= 4;
        StretchBlt(g_13dc, SC(8) + g_1df8[4][idx].f00.x,
                   SC(2) * v + g_1df8[4][idx].f00.y - 1,
                   w - SC(16), w - SC(4) * v + 1,
                   g_39e8[4], sx, 0, h * 2 + w, h * 2 + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, SC(6) + g_1df8[4][idx].f00.x, g_1df8[4][idx].f00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[4][idx].f00.x - SC(16) + SC(8) + w, g_1df8[4][idx].f00.y,
                   SC(2), w, BLACKNESS);
        }
        break;
    case 9:
        PatBlt(g_13dc, g_1df8[4][idx].f00.x, g_1df8[4][idx].f00.y, w, w, BLACKNESS);
        fn_07_2080(4, -1);
        fn_07_1208();
        break;
    }
    if (flag) {
        PatBlt(g_13dc, g_1df8[4][idx].f00.x, g_1df8[4][idx].f00.y, w, SC(3), BLACKNESS);
        PatBlt(g_13dc, g_1df8[4][idx].f00.x, g_1df8[4][idx].f00.y - SC(3) + w, w, SC(3),
               BLACKNESS);
        PatBlt(g_13dc, g_1df8[4][idx].f00.x, SC(3) + g_1df8[4][idx].f00.y, SC(3),
               w - SC(6), BLACKNESS);
        PatBlt(g_13dc, g_1df8[4][idx].f00.x - SC(3) + w, SC(3) + g_1df8[4][idx].f00.y,
               SC(3), w - SC(6), BLACKNESS);
    }
}

/* The 0x50-byte records of DS:2f5e from DS:2f4c [inferred]. */
typedef struct {
    char p00[4];
    int f04;                    /* +04: HDC index (g_39e8) */
    int f06;                    /* +06 */
    char p08[0x0e - 0x08];
    int f0e;                    /* +0e: behaviour */
    char p10[2];
    int f12;                    /* +12 */
    char p14[0x1a - 0x14];
    int f1a;                    /* +1a */
    int f1c;                    /* +1c */
    char p1e[2];
    int f20;                    /* +20 */
    char p22[0x26 - 0x22];
    int f26;                    /* +26 */
    char p28[0x2c - 0x28];
    int f2c;                    /* +2c */
    int f2e;                    /* +2e */
    char p30[0x40 - 0x30];
    int f40;                    /* +40 */
    int f42;                    /* +42 */
    int f44;                    /* +44 */
    char p46[2];
    int f48;                    /* +48 */
    char p4a[0x50 - 0x4a];
} REC_50C;
extern REC_50C g_2f4c[];
extern int g_3450;

/* Draw object (type, idx) shrinking as its f51 counter runs down
 * [inferred]; the general form of fn_12_0e5c. */
/* @addr 12:129e */
void far fn_12_129e(int type, int idx)
{
    int v;
    int w;
    int h;
    int k;
    int sx;
    int flag;

    w = g_1df8[type][idx].f22;
    h = g_1df8[type][idx].f24;
    if (g_8ffe != 0 && g_1df8[type][idx].f51 > 8)
        flag = 1;
    else
        flag = 0;
    g_1df8[type][idx].f51 -= (char)g_8ffe;
    if (g_1df8[type][idx].f51 < 0)
        g_1df8[type][idx].f51 = 0;
    v = 9 - g_1df8[type][idx].f51;
    SetStretchBltMode(g_13dc, 3);
    if (type == 11) {
        k = g_1df8[type][idx].f4a;
        sx = 0;
    } else if (type == 6) {
        k = g_2f4c[g_66e4[idx].f00].f04;
        sx = (g_2f4c[g_66e4[idx].f00].f2e - 1 < 0 ? 0 : g_2f4c[g_66e4[idx].f00].f2e - 1)
            * (h + w);
    }
    if (k > 100 || k < 0) {
        g_9498++;
        g_66e4[idx].f00 = 16;
        k = g_3450;
    }
    if (g_1df8[type][idx].f48 == g_9646 && g_9208 > 1 && (v & 1))
        fn_07_1208();
    if (g_1df8[type][idx].f1a == 0)
        return;
    switch (v) {
    case 0:
        StretchBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y, w, w,
                   g_39e8[k], sx - SC(2) + h, h - SC(2), SC(4) + w, SC(4) + w, SRCCOPY);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        StretchBlt(g_13dc, SC(v) * 2 + g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y - SC(2),
                   w - SC(4) * v, SC(4) + w,
                   g_39e8[k], sx - SC(4) + h, h - 2, SC(8) + w, SC(4) + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, SC(2) * (v - 1) + g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[type][idx].f00.x - SC(v) * 2 + w, g_1df8[type][idx].f00.y,
                   SC(2), w, BLACKNESS);
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        v -= 4;
        StretchBlt(g_13dc, SC(8) + g_1df8[type][idx].f00.x,
                   SC(2) * v + g_1df8[type][idx].f00.y - 1,
                   w - SC(16), SC(2) - SC(4) * v + w,
                   g_39e8[k], sx - SC(4) + h, h - SC(4), SC(8) + w, SC(8) + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, SC(6) + g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[type][idx].f00.x - SC(16) + SC(8) + w,
                   g_1df8[type][idx].f00.y, SC(2), w, BLACKNESS);
        }
        break;
    case 9:
        PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y, w, w, BLACKNESS);
        fn_07_2080(type, -1);
        fn_07_1208();
        break;
    }
    if (flag) {
        PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y, w, SC(3), BLACKNESS);
        PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y + w - 3, w, SC(3),
               BLACKNESS);
        PatBlt(g_13dc, g_1df8[type][idx].f00.x, SC(3) + g_1df8[type][idx].f00.y, SC(3),
               w - SC(6), BLACKNESS);
        PatBlt(g_13dc, g_1df8[type][idx].f00.x - SC(3) + w, SC(3) + g_1df8[type][idx].f00.y,
               SC(3), w - SC(6), BLACKNESS);
    }
}

void far pascal fn_12_1776(int a)
{
    g_9430 = a;
}

void far pascal fn_12_390e(int n);

void far pascal fn_12_5636(int a)
{
    g_9430 = a;
}


void far fn_12_7006(void);

/* Draw the line a-b clipped to the play view (0..g_90ea, 0..g_90ec)
 * [inferred]. Slopes are 25.7 fixed point. */
/* @addr 12:7256 */
void far fn_12_7256(HDC dc, POINT a, POINT b)
{
    int side;
    long slope;
    long icpt;
    long v;
    POINT pt[2];

    pt[1].y = pt[1].x = pt[0].y = pt[0].x = -1;
    if (!(a.x >= 0 && a.x <= g_90ea && b.x >= 0 && b.x <= g_90ea
          && a.y >= 0 && a.y <= g_90ec && b.y >= 0 && b.y <= g_90ec)) {
        if (b.x == a.x)
            b.x++;
        if (b.y == a.y)
            b.y++;
        if (a.y < 0 && b.y < 0)
            return;
        if (a.y > g_90ec && b.y > g_90ec)
            return;
        if (a.x < 0 && b.x < 0)
            return;
        if (a.x > g_90ea && b.x > g_90ea)
            return;
        slope = ((long)(b.y - a.y) << 7) / (b.x - a.x);
        if (a.x - b.x == -1)
            b.x = a.x;
        icpt = a.y - (slope * a.x >> 7);
        if (a.y < 0 || b.y < 0) {
            if (a.y < 0)
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = -((icpt << 7) / slope);
            if (v > 0 && v < g_90ea) {
                pt[side].x = (int)v;
                pt[side].y = 0;
            }
        }
        if (a.y > g_90ec || b.y > g_90ec) {
            if (a.y > g_90ec)
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = ((g_90ec - icpt) << 7) / slope;
            if (v > 0 && v < g_90ea) {
                pt[side].x = (int)v;
                pt[side].y = g_90ec;
            }
        }
        slope = ((long)(b.x - a.x) << 7) / (b.y - a.y);
        if (a.y - b.y == -1)
            b.y = a.y;
        icpt = a.x - (slope * a.y >> 7);
        if (a.x < 0 || b.x < 0) {
            if (a.x < 0)
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = -((icpt << 7) / slope);
            if (v > 0 && v < g_90ec) {
                pt[side].x = 0;
                pt[side].y = (int)v;
            }
        }
        if (a.x > g_90ea || b.x > g_90ea) {
            if (a.x > g_90ea)
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = ((g_90ea - icpt) << 7) / slope;
            if (v > 0 && v < g_90ec) {
                pt[side].x = g_90ea;
                pt[side].y = (int)v;
            }
        }
    }
    if (pt[0].x == -1 && pt[0].y == -1) {
        pt[0].x = a.x;
        pt[0].y = a.y;
    }
    if (pt[1].x == -1 && pt[1].y == -1) {
        pt[1].x = b.x;
        pt[1].y = b.y;
    }
    MoveTo(dc, pt[0].x, pt[0].y);
    LineTo(dc, pt[1].x, pt[1].y);
}

/* Launch a new object of type g_9328 from object (type, idx) in direction
 * c (g_1050) [inferred]. d is clamped to 24, so the d > 25 sound never
 * plays (as in the original). */
/* near-match 99%: 12:2db6 (the original computes (g_9208 + 2) * 2 into ax
 * before the g_9334 clamp in cx; CL here always evaluates the clamp first
 * and reassociates the * 2; an identical-arm ternary (g_9208 > -32767 ?
 * (g_9208 + 2) * 2 : same) gives the right order but adds a temp store) */
void far pascal fn_12_2db6(int type, int idx, int c, int d, int kind)
{
    int unused[2];
    int n;
    int j;
    int unused2[2];
    int found;

    d = min(d, 24);
    if (min((g_9208 + 2 << 1) * (min(g_9334, 10) + 10) / 20, 10) <= g_9406[g_9328])
        return;
    n = -1;
    found = 0;
    do {
        n++;
        if (g_92ec[g_9328] <= n) {
            g_92ec[g_9328] = n + 1;
            GlobalUnlock(g_9100[g_9328]);
            g_9100[g_9328] = GlobalReAlloc(g_9100[g_9328],
                (long)(g_92ec[g_9328] < 1 ? 1 : g_92ec[g_9328]) * 0x70, 0x42);
            g_1df8[g_9328] = (REC_70 far *)GlobalLock(g_9100[g_9328]);
            g_1df8[g_9328][n].f44 = 0x78;
            g_1df8[g_9328][n].f42 = 0x64;
            g_1df8[g_9328][n].f4c = 0xff;
            g_1df8[g_9328][n].f62 = fn_11_3914;
            g_1df8[g_9328][n].f5e = fn_07_570a;
            g_1df8[g_9328][n].f53 = 0;
            g_1df8[g_9328][n].f54 = 0;
            g_1df8[g_9328][n].f32 = -1;
            g_1df8[g_9328][n].f12 = g_1df8[g_9328][n].f24;
            g_1df8[g_9328][n].f2e = 0;
            g_5a4c[n].f00 = -1;
            g_9406[g_9328] = n + 1;
        }
        if (g_5a4c[n].f00 == -1) {
            g_5a4c[n].f00 = 0;
            g_5a4c[n].f10 = 0;
            g_1df8[g_9328][n].f18 = 0;
            g_5a4c[n].f12 = 0;
            g_1df8[g_9328][n].f2e = 0;
            if (kind == 5)
                g_1df8[g_9328][n].f44 = 0x78;
            else if (kind == 4)
                g_1df8[g_9328][n].f44 = 0xc8;
            for (j = 0; j < 5; j++)
                g_5eac[n][j + 6] = g_5eac[n][j] = -100;
            g_1df8[g_9328][n].f04.x = g_1df8[type][idx].f20 / 2
                + (g_1df8[type][idx].f20 / 32 + 4) * g_1050[c].x
                + g_1df8[type][idx].f04.x - 32;
            g_1df8[g_9328][n].f04.y = (g_1df8[type][idx].f20 / 32 + 4) * g_1050[c].y
                + g_1df8[type][idx].f20 / 2 + g_1df8[type][idx].f04.y - 32;
            g_5a4c[n].f04 = type;
            g_5a4c[n].f06 = idx;
            g_5a4c[n].f08 = type;
            g_5a4c[n].f0a = idx;
            g_1df8[g_9328][n].f0c = g_1050[c].x * 6;
            g_1df8[g_9328][n].f0e = g_1050[c].y * 6;
            if (d > 25)
                fn_10_754a(0x1b, g_9328, n, 1);
            else
                fn_10_754a(0x19, g_9328, n, 1);
            g_5a4c[n].f02 = d;
            break;
        }
    } while (found == 0);
    fn_07_2080(g_9328, -1);
}

/* Turn direction cur (0..15) one step toward the direction from a to b
 * on the wrapping map [inferred]. dir stays uninitialised when mode is
 * neither 2 nor 5 (as in the original). */
/* w is a dead temporary; it makes CL compute b.x - w as neg(w - b.x). */
/* @addr 12:67e8 */
int far pascal fn_12_67e8(POINT a, POINT b, int mode, int cur)
{
    int dx;
    int dy;
    int dir;
    int w;
    int unused[5];

    dx = b.x - a.x;
    if (fn_09_88ba(dx) > (G_05A0_INT >> 1 << 3))
        dx = (0 > dx ? G_05A0_INT * 8 + b.x : b.x - (w = G_05A0_INT * 8)) - a.x;
    dy = b.y - a.y;
    if (fn_09_88ba(dy) > (g_05a2 >> 1 << 3))
        dy = (0 > dy ? g_05a2 * 8 + b.y : b.y - (w = g_05a2 * 8)) - a.y;
    if (mode == 2)
        dir = fn_08_19b0(dx, dy);
    else if (mode == 5)
        dir = fn_08_19b0(-dx, -dy);
    if (dir < 0 || dir > 15)
        return cur;
    if (dir == cur)
        return dir;
    if (dir < cur) {
        if (cur - dir < 9) {
            cur--;
        } else {
            cur++;
            if (cur > 15)
                cur = 0;
        }
    } else {
        if (dir - cur < 9) {
            cur++;
        } else {
            cur--;
            if (cur < 0)
                cur = 15;
        }
    }
    return cur;
}

/* Dispatch on kind [inferred]. */
/* @addr 12:6dea */
void far fn_12_6dea(int kind, int type, int idx, int d)
{
    if (g_2f5e[kind].f00)
        fn_11_7c12(kind, type, idx);
    else if (kind == 5)
        fn_12_2db6(type, idx, g_1df8[type][idx].f28, d, 5);
    else if (kind == 4)
        fn_12_2db6(type, idx, g_1df8[type][idx].f28, d, 4);
    else if (kind == 1)
        fn_11_8a42(type, idx);
    else if (kind == 2)
        fn_11_947a(type, idx, 2);
    else if (kind == 15)
        fn_11_947a(type, idx, 15);
    else if (kind == 3)
        fn_11_9fdc(type, idx);
    else if (kind == 23)
        fn_11_9daa(type, idx);
    else if (kind == 13)
        fn_11_9078(type, idx);
}

/* Create an object's memory DC and bitmap and copy its image in
 * [inferred]. */
/* @addr 12:2556 */
void far fn_12_2556(int type, int idx)
{
    int y;

    if (type == 1 || g_1df8[type][idx].f3c != 0)
        return;
    if (type == 7)
        g_1df8[7]->f28 = 5;
    g_1df8[type][idx].f3c = CreateCompatibleDC(g_13dc);
    g_1df8[type][idx].f3e = CreateCompatibleBitmap(g_13dc,
        g_1df8[type][idx].f22 + g_1df8[type][idx].f24 * 2,
        g_1df8[type][idx].f22 + g_1df8[type][idx].f24 * 2);
    g_1df8[type][idx].f40 = SelectObject(g_1df8[type][idx].f3c, g_1df8[type][idx].f3e);
    if (g_920e)
        g_1df8[type][idx].f6e = SelectPalette(g_1df8[type][idx].f3c, g_920e, 0);
    if (type == g_9324 && g_70a0[idx].f00 > 1)
        y = g_1df8[type][idx].f22 + g_1df8[type][idx].f24;
    else
        y = 0;
    BitBlt(g_1df8[type][idx].f3c, 0, 0,
           g_1df8[type][idx].f22 + g_1df8[type][idx].f24 * 2,
           g_1df8[type][idx].f22 + g_1df8[type][idx].f24 * 2,
           g_1df8[type][idx].f3a,
           (g_1df8[type][idx].f22 + g_1df8[type][idx].f24) * g_1df8[type][idx].f28,
           y, SRCCOPY);
}

/* @addr 12:6ed8 */
int far fn_12_6ed8(int i)
{
    int u1;
    int k;
    int o;
    int u2;
    int dot;
    int u3[2];
    POINT d;
    POINT p;
    int u4[2];
    int flag;

    if (g_3d82[i].f00 != -1) {
        k = g_3d82[i].f00;
        o = g_4f32[k].f00;
        if (o >= 0 && o < 8 && g_1df8[0][o].f18 == 0)
            flag = 1;
        else
            flag = 0;
        p = fn_08_29ea(g_4f32[k].f04);
        d.x = p.x - g_1df8[8][i].f00.x;
        d.y = p.y - g_1df8[8][i].f00.y;
        if (g_4f32[k].f02 == 0 && flag == 0
            && rand() % 25 < g_9334 / 3 + g_9208 + 2)
            return 1;
        dot = g_1050[g_1df8[8][i].f28].x * d.x + g_1050[g_1df8[8][i].f28].y * d.y;
        if ((g_4f32[k].f02 == 1 || g_4f32[k].f02 == 0) && dot < 0 && flag)
            return 0;
        if (g_4f32[k].f02 != 2 && flag == 0)
            return 1;
        if (dot <= 0)
            return 1;
        return 0;
    }
    return 1;
}

/* @addr 12:633e */
void far fn_12_633e(void)
{
    int i;

    g_94a0 = (g_9208 + 1) / 2 + 2;
    if (g_1c32 == 0)
        fn_12_7006();
    g_1c32++;
    if (g_1c32 > 1)
        g_1c32 = 0;
    g_0d08 += g_0d06;
    if (g_0d08 > 4 || g_0d08 < 2)
        g_0d06 = -g_0d06;
    g_949e = 1;
    g_949a = g_949c = 0;
    for (i = 0; i < g_9416; i++) {
        if (g_1df8[8][i].f18 == 0) {
            g_1df8[8][i].f1c = 0;
            if (g_3d6c[i].f00 == 1) {
                fn_12_390e(i);
            } else if (g_3d6c[i].f00 == 2) {
                fn_12_5636(i);
            } else if (g_3d6c[i].f00 == 3) {
                fn_12_1776(i / 2);
                i++;
            }
        }
    }
    if (g_949e) {
        for (i = 0; i < g_94a0; i++) {
            if (g_693c[i].f08 != 0 && g_693c[i].f08 < g_693c[i].f0a)
                PatBlt(g_13dc, g_693c[i].f00, g_693c[i].f02,
                       (2 << g_9156) >> 1, (2 << g_9156) >> 1, BLACKNESS);
        }
    }
    if (g_949a)
        g_6988 = g_1e50 + 1000;
    if (g_949c)
        g_666c = g_9320 == 6 ? g_1e68 + 3 : g_1e68 + 8;
}

/* @addr 12:3778 */
void far fn_12_3778(void)
{
    int i;
    int old;
    int flag;

    for (i = 0; i < g_9300; i++) {
        if (g_65cc[i].t1 != -1) {
            flag = 0;
            if (g_65cc[i].t1 == g_9324 && (g_70ae[g_65cc[i].i1].fce == 0
                                           || g_70ae[g_65cc[i].i1].f129 != 0))
                flag = 1;
            if (g_65cc[i].t2 == g_9324 && (g_70ae[g_65cc[i].i2].fce == 0
                                           || g_70ae[g_65cc[i].i2].f129 != 0))
                flag = 1;
            if (g_1df8[g_65cc[i].t1][g_65cc[i].i1].f18 == 0
                && g_1df8[g_65cc[i].t2][g_65cc[i].i2].f18 == 0 && flag == 0)
                continue;
            g_1df8[10][i].f18 = 1;
            g_1df8[g_65cc[i].t1][g_65cc[i].i1].f32 = -1;
            g_1df8[g_65cc[i].t2][g_65cc[i].i2].f36 = -1;
            g_65cc[i].t1 = -1;
            g_65cc[i].t2 = -1;
            g_65cc[i].f08 = 0;
            old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
            fn_12_7256(g_13dc, g_65cc[i].f1c, g_65cc[i].f14);
            g_65cc[i].f14 = g_65cc[i].f10;
            g_65cc[i].f1c = g_65cc[i].f18;
            SelectObject(g_13dc, old);
            fn_07_2080(10, -1);
        }
    }
}

/* Turn object (8, idx) one step toward object (14, idx2) [inferred]. */
/* @addr 12:6902 */
int far fn_12_6902(int idx, int idx2)
{
    int cur;
    int dir;
    int speed;

    cur = g_1df8[8][idx].f28;
    if (g_3d5a[idx].f22 > 400)
        return fn_12_67e8(g_1df8[8][idx].f04, g_1df8[14][idx2].f04, 2, cur);
    switch (g_3d5a[idx].f00) {
    case 4:
    case 5:
        speed = 0x56;
        break;
    case 11:
        speed = 0x3a;
        break;
    case 10:
    case 16:
        speed = 0x2a;
        break;
    case 1:
        speed = 300;
        break;
    default:
        speed = 0x5a;
        break;
    }
    fn_08_348e(8, idx, 14, idx2, speed);
    dir = fn_08_19b0(g_1df8[8][idx].f0c, g_1df8[8][idx].f0e);
    g_1df8[8][idx].f0e = 0;
    g_1df8[8][idx].f0c = g_1df8[8][idx].f0e;
    if (dir < 0 || dir > 15)
        return cur;
    if (dir == cur)
        return dir;
    if (dir < cur) {
        if (cur - dir < 9) {
            cur--;
        } else {
            cur++;
            if (cur > 15)
                cur = 0;
        }
    } else {
        if (dir - cur < 9) {
            cur++;
        } else {
            cur--;
            if (cur < 0)
                cur = 15;
        }
    }
    return cur;
}

/* Erase the old marker bar and draw a new one at the scaled position
 * [inferred]. */
/* near-match 26%: 12:4d8e (only the register choice when saving es around
 * the far-pointer temp differs: the original keeps the segment in ax and
 * pushes it; everything after is shifted by one byte) */
void far fn_12_4d8e(void)
{
    int unused;
    RECT r;
    RECT r2;

    if (g_9eb5 == 1 && g_1c2c == 0)
        return;
    if (g_9eb5 == -1)
        return;
    r.left = r.right = ((g_1df8[12][1].f04.x - g_1df8[14][g_9646].f04.x) >> 4 << g_9156)
        + g_1df8[14][g_9646].f00.x + (0x16 << g_9156);
    r.top = ((g_9ea8[g_9322].y - g_1df8[14][g_9646].f04.y + 50) >> 4 << g_9156)
        + g_1df8[14][g_9646].f00.y;
    r.bottom = ((g_9ea8[g_9322].x - g_1df8[14][g_9646].f04.y + 50) >> 4 << g_9156)
        + g_1df8[14][g_9646].f00.y;
    if (min(g_1c18.right, g_1c18.left) < g_90ea && max(g_1c18.right, g_1c18.left) > 0
        && min(g_1c18.bottom, g_1c18.top) < g_90ec && max(g_1c18.bottom, g_1c18.top) > 0)
        PatBlt(g_13dc, g_1c18.right, g_1c18.bottom, 2, g_1c18.top - g_1c18.bottom, BLACKNESS);
    if (g_9eb5 != 0) {
        g_1c2c = 0;
        return;
    }
    g_1c2c = 1;
    g_1c18.top = r.top;
    g_1c18.bottom = r.bottom;
    g_1c18.right = r.right;
    g_1c18.left = r.left;
    if (min(r.right, r.left) < g_90ea && max(r.right, r.left) > 0
        && min(r.bottom, r.top) < g_90ec && max(r.bottom, r.top) > 0) {
        PatBlt(g_13dc, r.right, r.bottom, 2, r.top - r.bottom, WHITENESS);
        if (g_1df8[14][g_9646].f22 + g_1df8[14][g_9646].f00.x > g_1c18.right
            && g_1df8[14][g_9646].f00.x < g_1c18.right + 2)
            hazards_ship_redraw_pending = 1;
    }
}

/* @addr 12:515e */
void far fn_12_515e(void)
{
    int k;
    int i;
    int j;
    int dy;
    int dx;
    int n;
    int ok;

    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f18 == 0
            && (long)g_70ae[i].f00 * 100 / g_96f0[g_70ae[i].f30].f00 < 40) {
            for (k = n = 0; k < g_92f4; k++)
                if (g_1df8[4][k].f18 == 0)
                    n++;
            if (n < 2) {
                n = -1;
                for (k = 0; k < g_92f4; k++) {
                    if (g_1df8[4][k].f18 != 0 && g_1df8[4][k].f51 == 0) {
                        n = k;
                        break;
                    }
                }
                if (n != -1) {
                    g_1df8[4][n].f04.x = rand() % G_05A0_INT * 8;
                    g_1df8[4][n].f04.y = rand() % g_05a2 * 8;
                    ok = 1;
                    for (j = 0; j <= g_9316; j++)
                        if (fn_08_285a(&dy, &dx, g_1df8[4][n].f04, g_1df8[14][j].f04) < 60)
                            ok = 0;
                    if (ok) {
                        g_1df8[4][n].f00.y = -1000;
                        g_1df8[4][n].f00.x = g_1df8[4][n].f00.y;
                        g_1df8[4][n].f18 = 0;
                        g_1df8[4][n].f54 = 1;
                        g_1df8[4][n].f1e = 0;
                        g_1df8[4][n].f51 = 0;
                        g_1df8[4][n].f26 = g_1df8[4][n].f51;
                        g_1df8[4][n].f2f = g_1df8[4][n].f26;
                        fn_07_2080(4, -1);
                        return;
                    }
                }
            }
        }
    }
}

/* @addr 12:6b1e */
void far fn_12_6b1e(void)
{
    int i;
    int r;

    for (i = 0; i < g_941c; i++) {
        if (g_1df8[11][i].f18 == 0) {
            g_1df8[11][i].f1c = 0;
            if (g_8560[i].f04 > 2)
                g_1df8[11][i].f53 = 1;
            fn_08_1b54((char)i | 0xb00, 1);
            fn_08_1d54((char)i | 0xb00, 0x28);
            g_1df8[11][i].f10 = (g_1df8[11][i].f22 + g_1df8[11][i].f24) * (g_8560[i].f00 - 1)
                + g_1df8[11][i].f24;
            fn_08_0b76((char)i | 0xb00, 3, g_39e8[g_1df8[11][i].f4a], 0);
            g_8560[i].f04++;
            if (g_1df8[11][i].f1a != 0 && g_1df8[11][i].f1c == 0) {
                g_943a = 11;
                g_943c = i;
                r = fn_08_50aa((char)i | 0xb00);
                if (r != -1) {
                    if (HIBYTE(r) == g_9324 && g_70ae[LOBYTE(r)].fcc == 0
                        && g_70ae[LOBYTE(r)].fca == 0)
                        fn_13_16ac(LOBYTE(r), (char)g_943c | g_943a << 8);
                    else
                        fn_08_5df2(11, i, HIBYTE(r), LOBYTE(r),
                                   fn_08_546c(r, &g_1df8[11][i].f0c, &g_1df8[11][i].f0e,
                                              g_1df8[11][i].f20 + 2, 0x6e));
                }
            }
            if (g_8560[i].f04 > g_8560[i].f06 && g_92e8 == 0) {
                g_1df8[11][i].f66(11, i);
                fn_07_2080(11, -1);
            }
        } else if (g_1df8[11][i].f51) {
            fn_12_129e(11, i);
        }
    }
}

/* @addr 12:4f4e */
void far fn_12_4f4e(void)
{
    int i;
    int flag;
    int j;
    int dy;
    int k;
    int ok;

    flag = 0;
    if (g_9ebf[g_9322] == 0)
        return;
    for (i = 0; i < g_9ebf[g_9322]; i++) {
        if (g_1df8[4][i].f18 != 0) {
            if (g_698c < g_1e50) {
                for (j = 0; j <= g_9316; j++) {
                    if (g_1df8[14][j].f18 == 0
                        && (long)g_70ae[j].f00 * 100 / g_96f0[g_70ae[j].f30].f00 < 40) {
                        g_1df8[4][i].f04.x = g_9f40[g_9322][g_9eb9[g_9322] + g_9ebc[g_9322] + i].x
                            - g_1df8[4]->f20 / 2;
                        g_1df8[4][i].f04.y = g_9f40[g_9322][g_9eb9[g_9322] + g_9ebc[g_9322] + i].y
                            - g_1df8[4]->f20 / 2;
                        ok = 1;
                        for (k = 0; k <= g_9316; k++)
                            if (fn_08_285a(&dy, &flag, g_1df8[4][i].f04, g_1df8[14][k].f04) < 60)
                                ok = 0;
                        if (ok) {
                            g_940e = g_9ebf[g_9322];
                            g_1df8[4][i].f00.y = -1000;
                            g_1df8[4][i].f00.x = g_1df8[4][i].f00.y;
                            g_1df8[4][i].f18 = 0;
                            g_1df8[4][i].f54 = 1;
                            g_1df8[4][i].f1e = 0;
                            g_1df8[4][i].f51 = 0;
                            g_1df8[4][i].f26 = g_1df8[4][i].f51;
                            g_1df8[4][i].f2f = g_1df8[4][i].f26;
                            break;
                        }
                    }
                }
            }
            flag = 1;
        }
    }
    if (flag == 0)
        g_698c = g_1e50 + 10000;
}

/* Pick the nearest suitable target within range for object (6, idx)
 * [inferred]. */
/* @addr 12:0586 */
void far pascal fn_12_0586(int idx, int range)
{
    int best;
    int bt;
    int bi;
    int d;
    int dy;
    int dx;
    int kind;
    int t;
    int i;

    kind = g_66e0[idx].f04;
    best = 20000;
    bt = -1;
    if (g_92e8 != 0 && kind == 0x16)
        return;
    if (g_2f5e[kind].f00 == 2) {
        if (g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f18 == 0)
            g_66e0[idx].f1a = 1;
        return;
    }
    for (t = 0; t <= g_9324; t++) {
        if ((g_2f5e[kind].f0a != 1 || t != g_9328) && t != 2) {
            for (i = 0; i < g_9406[t]; i++) {
                if ((t != 6 || i != idx) && g_1df8[t][i].f18 == 0
                    && g_1df8[t][i].f44 > 0x1e
                    && (g_2f5e[kind].f00 == 3 || g_1df8[t][i].f2f != 0)) {
                    d = fn_08_285a(&dy, &dx, g_1df8[6][idx].f04, g_1df8[t][i].f04);
                    if (g_66e0[idx].f08 == t && g_66e0[idx].f0a == i)
                        d <<= 2;
                    if (g_66e0[idx].f08 == g_9324 && t == g_9324
                        && g_96f0[g_70ae[g_66e0[idx].f0a].f30].f1a == g_96f0[g_70ae[i].f30].f1a
                        && g_92e8 == 0)
                        d *= 7;
                    if (g_2f5e[kind].f00 == 4) {
                        d += -25 * g_1df8[t][i].f2f;
                        if (t == g_9328)
                            d /= 2;
                    } else if (t == g_9324) {
                        d = d * 2 / 3;
                    }
                    if (d < range && d < best) {
                        best = d;
                        bt = t;
                        bi = i;
                    }
                }
            }
        }
    }
    if (bt == -1)
        return;
    if (g_66e0[idx].f08 == bt && g_66e0[idx].f0a == bi && g_66e0[idx].f0c <= 0x3c)
        return;
    g_66e0[idx].f1a = 1;
    g_66e0[idx].f00 = bt;
    g_66e0[idx].f02 = bi;
}

/* Turn the objects of each group round its centre [inferred]. */
/* @addr 12:7006 */
void far fn_12_7006(void)
{
    int k;
    int j;
    long s0;
    long c0;
    long s1;
    long c1;

    for (k = 0; k < g_9344; k++) {
        for (j = g_4f2c[k].first; j < g_4f2c[k].end; j++) {
            g_3d5a[j].f24 += g_4f2c[k].speed;
            if (g_3d5a[j].f24 < 0)
                g_3d5a[j].f24 = g_3d5a[j].f24 + 0xb40;
            if (g_3d5a[j].f24 > 0xb40)
                g_3d5a[j].f24 -= 0xb40;
            s0 = fn_06_71b2(g_3d5a[j].f24 >> 3);
            c0 = fn_06_720c(g_3d5a[j].f24 >> 3);
            s1 = fn_06_71b2((g_3d5a[j].f24 >> 3) + 1);
            c1 = fn_06_720c((g_3d5a[j].f24 >> 3) + 1);
            s0 += (s1 - s0) * (g_3d5a[j].f24 % 8) / 8;
            c0 += (c1 - c0) * (g_3d5a[j].f24 % 8) / 8;
            g_1df8[8][j].f04.x = (int)(g_4f2c[k].radius * c0 / 128) + g_4f2c[k].cx;
            g_1df8[8][j].f04.y = (int)(s0 * g_4f2c[k].radius / 128) + g_4f2c[k].cy;
            g_1df8[8][j].f0c = (int)(s0 * ((long)g_4f2c[k].radius * g_4f2c[k].speed) / -82000L);
            g_1df8[8][j].f0e = (int)(c0 * g_4f2c[k].radius * g_4f2c[k].speed / 82000L);
            if (g_1df8[8][j].f04.y > g_05a2 * 8)
                g_1df8[8][j].f04.y -= g_05a2 * 8;
            else if (g_1df8[8][j].f04.y < 0)
                g_1df8[8][j].f04.y += g_05a2 * 8;
            if (g_1df8[8][j].f04.x > G_05A0_INT * 8)
                g_1df8[8][j].f04.x -= G_05A0_INT * 8;
            else if (g_1df8[8][j].f04.x < 0)
                g_1df8[8][j].f04.x += G_05A0_INT * 8;
        }
    }
}

/* Fire for object (6, idx) when its weapon kind allows it [inferred]. */
/* @addr 12:64aa */
void far pascal fn_12_64aa(int idx, int kind)
{
    int i;
    int dir;
    int fire;

    if (g_66e0[idx].f0c & 3 || g_66e0[idx].f0c < 13)
        return;
    fire = 0;
    if (g_2f5e[kind].f0c == 2 || g_2f5e[kind].f0c == 1) {
        if (g_2f5e[kind].f0c == 1)
            fire = 1;
        else if (rand() % 3 == 0)
            fire = 1;
    } else if (g_2f5e[kind].f0c == 3 && g_1df8[6][idx].f1a != 0) {
        for (i = 0; i <= g_9316; i++) {
            if (g_1df8[g_9324][i].f18 == 0 && g_1df8[g_9324][i].f1a != 0) {
                dir = fn_08_19b0(g_1df8[g_9324][i].f00.x - g_1df8[6][idx].f00.x,
                                 g_1df8[g_9324][i].f00.y - g_1df8[6][idx].f00.y);
                if (g_1df8[6][idx].f28 <= dir + 1 && g_1df8[6][idx].f28 >= dir - 1) {
                    fire = 1;
                    break;
                }
            }
        }
    } else if (g_2f5e[kind].f0c == 4) {
        if (g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f18 == 0
            && g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f1a != 0) {
            dir = fn_08_19b0(g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f00.x - g_1df8[6][idx].f00.x,
                             g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f00.y - g_1df8[6][idx].f00.y);
            if (g_1df8[6][idx].f28 <= dir + 1 && g_1df8[6][idx].f28 >= dir - 1)
                fire = 1;
        }
    }
    if (fire) {
        switch (g_2f5e[kind].f0a) {
        case 1:
            fn_12_2db6(6, idx, g_1df8[6][idx].f28, 11, 5);
            break;
        case 2:
            fn_12_2db6(6, idx, g_1df8[6][idx].f28, 11, 4);
            break;
        case 4:
            spawn_gun_shot(6, idx);
            break;
        case 3:
            if (g_1df8[6][idx].f50 > 0x19)
                fn_11_9fdc(6, idx);
            break;
        }
    }
}

/* Steer object (6, idx) toward its target and accelerate [inferred]. */
/* @addr 12:07c0 */
void far pascal fn_12_07c0(int idx)
{
    int t;
    int ti;
    int u1;
    int kind;
    int dir;
    int u2[9];
    POINT me;
    POINT tgt;
    POINT v;
    int u3;
    int jitter;
    int alt;
    int d;
    int q1;
    int q2;

    kind = g_66e0[idx].f04;
    jitter = 0;
    me.x = (g_1df8[6][idx].f20 >> 1) + g_1df8[6][idx].f04.x;
    me.y = (g_1df8[6][idx].f20 >> 1) + g_1df8[6][idx].f04.y;
    if (g_66e0[idx].f14 == 2) {
        tgt.x = (g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f22 >> 1)
            + g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f04.x;
        tgt.y = (g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f22 >> 1)
            + g_1df8[g_66e0[idx].f00][g_66e0[idx].f02].f04.y;
        alt = 0;
    } else {
        tgt.x = (g_1df8[g_66e0[idx].f10][g_66e0[idx].f12].f22 >> 1)
            + g_1df8[g_66e0[idx].f10][g_66e0[idx].f12].f04.x;
        tgt.y = (g_1df8[g_66e0[idx].f10][g_66e0[idx].f12].f22 >> 1)
            + g_1df8[g_66e0[idx].f10][g_66e0[idx].f12].f04.y;
        alt = 1;
    }
    t = g_66e0[idx].f00;
    ti = g_66e0[idx].f02;
    if (t == g_9324 && alt == 0 && g_70ae[ti].fca && g_2f5a[kind].f38 == 0)
        jitter = 1;
    tgt.x += (rand() % 300 - 150) * jitter * 8;
    tgt.y += (rand() % 300 - 150) * jitter * 8;
    if (jitter)
        g_66e0[idx].f1a = 0;
    if (g_2f5a[kind].f00 != 2) {
        dir = steer_toward_direction(me.y, me.x, tgt.y, tgt.x, 0, g_66e0[idx].f14,
                                     -100, -100, -100, 0);
    } else {
        g_1df8[6][idx].f28 = steer_toward_direction(me.y, me.x, tgt.y, tgt.x,
                                                    g_1df8[6][idx].f28, g_66e0[idx].f14,
                                                    -1, -1, -1, 0);
        dir = g_1df8[6][idx].f28;
    }
    if (g_2f5a[kind].f1a && jitter == 0) {
        d = fn_08_285a(&q1, &q2, me, tgt);
        if (d < g_2f5a[kind].f1a) {
            g_1df8[6][idx].f48 <<= 1;
            fn_12_274a(6, idx);
            fn_07_2080(6, idx);
        }
    }
    v.x = g_1050[dir].x * g_2f5e[kind].f02;
    v.y = g_1050[dir].y * g_2f5e[kind].f02;
    if (alt) {
        v.x *= 2;
        v.y *= 2;
    }
    g_1df8[6][idx].f0c += v.x;
    g_1df8[6][idx].f0e += v.y;
    fn_08_1cbe((char)idx | 0x600, g_2f5a[kind].f08);
}

/* Break object (type, idx) up into debris particles [inferred]. */
/* An unused block-scope local in the inner loop puts the later fn_08_29ea
 * return temps at bp-0x10, as in the game. */
/* @addr 12:2b20 */
void far fn_12_2b20(int type, int idx)
{
    int k;
    int j;
    int n;

    if (fn_08_7ba8(fn_08_29ea(g_1df8[type][idx].f04)))
        PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
               g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
    if (g_1df8[type][idx].f48 == 1) {
        n = 1;
    } else {
        switch (g_9208) {
        case 0:
            n = g_1df8[type][idx].f48 * 30 / 100;
            break;
        case 1:
            n = g_1df8[type][idx].f48 * 60 / 100;
            break;
        case 2:
            n = g_1df8[type][idx].f48;
            break;
        case 3:
            n = g_1df8[type][idx].f48 * 130 / 100;
            break;
        }
        n = n < 2 ? 2 : n;
    }
    for (k = 0; k < n; k++) {
        for (j = 0; j < 45; j++) {
            if (g_1e90[j].f00 == -1) {
                if (k == 0)
                    g_1e90[j].f0a = 4;
                else
                    g_1e90[j].f0a = 1;
                g_1e90[j].f00 = 1;
                if (j > g_9434)
                    g_9434 = j;
                g_1e90[j].f10 = (long)(rand() % 100) + k * 20 + g_1e50;
                g_1e90[j].f02 = 10;
                g_1e90[j].f06 = type;
                g_1e90[j].f08 = idx;
                { int pad[2];
                if (k == 0) {
                    g_5224[j] = g_1df8[type][idx].f04;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                } else {
                    g_5224[j].x = (-40 - rand() % ((n + 40) * 2) - n) * 8
                        + g_1df8[type][idx].f20 / 2 + g_1df8[type][idx].f04.x;
                    g_5224[j].y = (-40 - rand() % ((n + 40) * 2) - n) * 8
                        + g_1df8[type][idx].f20 / 2 + g_1df8[type][idx].f04.y;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                }
                }
                g_9430++;
                break;
            }
        }
    }
    fn_10_754a(0x45, type, idx, 1);
}

/* Object (type, idx) is destroyed [inferred]. */
/* @addr 12:2288 */
void far fn_12_2288(int type, int idx)
{
    int i;
    int all;

    if (type == g_9328) {
        if (g_1df8[type][idx].f2e == 0) {
            fn_10_754a(0x27, type, idx, 1);
            g_5a4c[idx].f00 = g_5a4c[idx].f02 - 7;
            g_1df8[type][idx].f2e = -1;
        }
    } else if (type == g_9324 && g_70ae[idx].fce == 0) {
        fn_12_274a(g_9324, idx);
    } else {
        if (type == 14 && g_70ae[idx].f34 >= 2 && g_70ae[idx].f34 <= 4
            && g_70ae[idx].f3a == idx && g_70ae[idx].f36 == 14) {
            if (idx == g_9646) {
                if (g_1df8[14][g_70ae[idx].f38].f18 == 0
                    && g_70ae[g_70ae[idx].f38].fb8 != -1)
                    g_93b6 = g_70ae[g_70ae[idx].f38].fb8;
            } else if (g_70ae[idx].f38 == g_9646 && g_70ae[idx].fb8 != -1) {
                g_93b6 = g_70ae[idx].fb8;
            }
        }
        if (g_1df8[type][idx].f1a)
            fn_12_2556(type, idx);
        if (type == g_9324)
            g_70ae[idx].f10 = 1;
        if (g_1df8[type][idx].f1a) {
            fn_07_13b2(1, type, idx);
        } else {
            g_1df8[type][idx].f18 = 1;
            fn_07_2080(type, idx);
            fn_10_754a(0x27, type, idx, 1);
        }
        if (type == g_9324 && g_96f0[g_70ae[idx].f30].f1a == 7 && g_70ae[idx].f36 == g_9324
            && g_1df8[g_9324][idx].f36 == g_9324
            && g_1df8[g_9324][idx].f38 == g_70ae[idx].f38) {
            fn_12_2288(g_9324, g_1df8[g_9324][idx].f38);
            if (g_1df8[g_9324][idx].f38 == g_9646) {
                g_1e80 = g_1e50 + 1000;
                g_93a4 = 1;
            }
        }
        if (type == g_9324 && idx == g_9646 && g_1df8[g_9324][idx].f32 == g_9324
            && g_96f0[g_70ae[g_1df8[g_9324][idx].f34].f30].f1a == 7)
            g_93a4 = 1;
        if (type == g_9324 && g_92e8 && idx == 1)
            g_1df8[14][g_9646].f54 = 0;
        if (type == 0)
            fn_07_5ae8(idx, 0);
        if (g_9320 == 7 && type == g_9324) {
            all = 1;
            for (i = 0; i <= g_9316; i++)
                if (i != idx && i != g_9646 && g_70ae[i].fce && g_1df8[14][i].f18 == 0)
                    all = 0;
            if (all)
                g_668a = -1;
        }
    }
}

/* @addr 12:0ae4 */
void far fn_12_0ae4(void)
{
    int i;
    int u1[2];
    int r;
    int gap;
    int size;
    int u2[10];

    gap = g_1df8[4]->f22;
    size = g_1df8[4]->f24;
    for (i = 0; i < g_940e; i++)
        g_1df8[4][i].f1c = 0;
    for (i = 0; i < g_940e; i++) {
        if (g_1df8[4][i].f18 == 0) {
            if (g_1df8[4][i].f54) {
                g_1df8[4][i].f0e = 0;
                g_1df8[4][i].f0c = g_1df8[4][i].f0e;
            }
            if (g_1df8[4][i].f1a) {
                fn_08_1d54((char)i | 0x400, 0x28);
                fn_08_1b54((char)i | 0x400, 1);
                g_1df8[4][i].f10 = g_1df8[4][i].f26 / 5 * (size + gap) + size;
                fn_08_0b76((char)i | 0x400, 1, g_39e8[4], 0);
                if (g_9214 == 0) {
                    g_1df8[4][i].f26 += g_1df8[4][i].f2f;
                    if (g_1df8[4][i].f2f) {
                        if (g_1df8[4][i].f26 < 5) {
                            g_1df8[4][i].f26 = 5;
                            g_1df8[4][i].f2f = g_1df8[4][i].f50;
                        }
                        if (g_1df8[4][i].f26 > 21) {
                            g_1df8[4][i].f26 = 21;
                            g_1df8[4][i].f2f = -g_1df8[4][i].f50;
                        }
                        if (g_1df8[4][i].f50 > rand() % 120 && g_1df8[4][i].f50 > rand() % 20) {
                            fn_12_274a(4, i);
                            fn_07_2080(4, i);
                        }
                    }
                }
            } else if (g_9142 % 3 == 0) {
                fn_08_1d54((char)i | 0x400, 0x28);
                fn_08_1b54((char)i | 0x400, 3);
            }
            if (g_1df8[4][i].f1a != 0 && g_1df8[4][i].f1c == 0) {
                g_943a = 4;
                g_943c = i;
                r = fn_08_50aa((char)i | 0x400);
                if (r != -1) {
                    if (HIBYTE(r) == g_9324 && g_70ae[LOBYTE(r)].fcc == 0
                        && g_70ae[LOBYTE(r)].fca == 0)
                        fn_13_16ac(LOBYTE(r), (char)g_943c | g_943a << 8);
                    else if (HIBYTE(r) == 0 && g_57a8[LOBYTE(r)].f02 != 0
                             || HIBYTE(r) == g_9328)
                        fn_08_5df2(4, i, HIBYTE(r), LOBYTE(r), 0x7d);
                    else
                        fn_08_5df2(4, i, HIBYTE(r), LOBYTE(r),
                                   fn_08_546c(r, &g_1df8[4][i].f0c, &g_1df8[4][i].f0e,
                                              g_1df8[4][i].f20 + 2, g_1df8[4][i].f44));
                }
            }
        } else if (g_1df8[4][i].f51) {
            fn_12_0e5c(i);
        }
    }
}

/* Attach link k to object (type, idx); 0 when it is already attached
 * there [inferred]. */
/* @addr 12:3498 */
int far fn_12_3498(int type, int idx, int k)
{
    int unused[5];
    int j;
    int old;

    if (g_65cc[k].t2 == type && g_65cc[k].i2 == idx || type == 10)
        return 0;
    old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
    fn_12_7256(g_13dc, g_65cc[k].f1c, g_65cc[k].f14);
    g_65cc[k].f14 = g_65cc[k].f10;
    g_65cc[k].f1c = g_65cc[k].f18;
    SelectObject(g_13dc, old);
    g_1df8[10][k].f18 = 1;
    PatBlt(g_13dc, g_1df8[10][k].f00.x, g_1df8[10][k].f00.y,
           g_1df8[10][k].f22, g_1df8[10][k].f22, BLACKNESS);
    if (g_65cc[k].t2 == 14 && type == 14
        && (g_70ae[g_65cc[k].i2].f14 != 14 || g_70ae[g_65cc[k].i2].f16 != idx))
        type = -1;
    if (type == 6)
        g_66e0[idx].f0c /= 4;
    if (type != -1 && (g_1df8[type][idx].f54 == 0 || type == 4)) {
        fn_10_754a(6, 10, k, 1);
        g_1df8[type][idx].f54 = 0;
        if (g_1df8[type][idx].f32 != -1) {
            j = g_1df8[type][idx].f30;
            g_1df8[10][j].f18 = 1;
            g_1df8[type][idx].f32 = -1;
            g_1df8[g_65cc[j].t2][g_65cc[j].i2].f36 = -1;
            g_65cc[j].t1 = -1;
            g_65cc[j].t2 = -1;
            g_65cc[j].f08 = 0;
            old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
            fn_12_7256(g_13dc, g_65cc[j].f1c, g_65cc[j].f14);
            g_65cc[j].f14 = g_65cc[j].f10;
            g_65cc[j].f1c = g_65cc[j].f18;
            SelectObject(g_13dc, old);
        }
        g_1df8[type][idx].f32 = g_65cc[k].t2;
        g_1df8[type][idx].f34 = g_65cc[k].i2;
        g_1df8[type][idx].f30 = k;
        g_1df8[g_65cc[k].t2][g_65cc[k].i2].f36 = type;
        g_1df8[g_65cc[k].t2][g_65cc[k].i2].f38 = idx;
        g_65cc[k].t1 = type;
        g_65cc[k].i1 = idx;
    } else {
        g_1df8[g_65cc[k].t2][g_65cc[k].i2].f36 = -1;
        g_65cc[k].t1 = -1;
        g_65cc[k].t2 = -1;
        fn_07_2080(10, -1);
    }
    g_65cc[k].f08 = 0;
    return 1;
}

/* @addr 12:532c */
void far fn_12_532c(void)
{
    int i;
    int r;
    int t;
    int dy;
    int dx;
    int j;
    int d;
    int v;

    for (i = 0; i < g_9418; i++) {
        if (g_1df8[9][i].f18 == 0) {
            if (g_1c2e < g_1e50 && g_1df8[9][i].f50 < 100)
                g_1df8[9][i].f50++;
            if (g_1df8[9][i].f1a != 0 || fn_13_59e8(9, i)) {
                g_1df8[9][i].f28 = g_1df8[9][i].f26 / 100;
                v = g_1df8[9][i].f50 < 12 ? 12 : g_1df8[9][i].f50;
                if (g_1df8[9][i].f50 < 0)
                    v = -v;
                g_1df8[9][i].f26 += v;
                if (g_1df8[9][i].f26 > 899)
                    g_1df8[9][i].f26 = 0;
                if (g_1df8[9][i].f26 < 0)
                    g_1df8[9][i].f26 = 899;
            }
            if (g_1df8[9][i].f1a) {
                fn_08_1d54((char)i | 0x900, 0x1e);
                fn_08_1b54((char)i | 0x900, 1);
                g_1df8[9][i].f10 = (g_1df8[9][i].f22 + g_1df8[9][i].f24) * g_1df8[9][i].f28
                    + g_1df8[9][i].f24;
                g_1df8[9][i].f12 = g_1df8[9][i].f24;
                fn_08_0b76((char)i | 0x900, 1, g_39e8[22], 0);
                if (g_1df8[9][i].f50 > 20) {
                    for (t = 0; t <= g_9324; t++) {
                        for (j = 0; j < g_9406[t]; j++) {
                            if (g_1df8[t][j].f18 == 0 && t != 9 && g_1df8[t][j].f44 != 0
                                && (t != 0 || g_1df8[0][j].f53 != 2)) {
                                d = fn_08_285a(&dy, &dx, g_1df8[9][i].f04, g_1df8[t][j].f04);
                                if (d < 200) {
                                    if (t == 6 || t == 0 || g_1df8[9][i].f50 > rand() % 100)
                                        fn_11_a234(9, i, t, j);
                                    break;
                                }
                            }
                        }
                    }
                }
            } else if (g_9142 % 3 == 0) {
                fn_08_1d54((char)i | 0x900, 0x1e);
                fn_08_1b54((char)i | 0x900, 3);
            }
            if (g_1df8[9][i].f1a != 0 && g_1df8[9][i].f1c == 0) {
                g_943a = 9;
                g_943c = i;
                r = fn_08_50aa((char)i | 0x900);
                if (r != -1)
                    fn_08_5df2(9, i, HIBYTE(r), LOBYTE(r),
                               fn_08_546c(r, &g_1df8[9][i].f0c, &g_1df8[9][i].f0e,
                                          g_1df8[9][i].f20 + 2, g_1df8[9][i].f44));
            }
        }
    }
    if (g_9418 && g_1c2e < g_1e50)
        g_1c2e = g_1e50 + 1000;
}

/* The 0x15a-byte records from DS:7090 (as in seg04.c) [inferred]. */
typedef struct {
    char p000[0x06];
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    char p00a[0x2e - 0x0a];
    int f2e;                    /* +2e */
    char p030[0x32 - 0x30];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    int f3a;                    /* +3a */
    int f3c;                    /* +3c */
    char p03e[0x88 - 0x3e];
    long f88;                   /* +88 */
    char p08c[0x15a - 0x8c];
} REC_15A90;
extern REC_15A90 g_7090[];
/* 0x1c-byte records at DS:6678 [inferred]. */
typedef struct {
    RECT r;                     /* +00 */
    char p08[0x10 - 0x08];
    int f10;                    /* +10: object index of type 12 */
    int f12;                    /* +12 */
    char p14[0x1c - 0x14];
} REC_1CC;
extern REC_1CC g_6678[];
extern char g_507c[];
extern char g_50e0[];
extern int g_9146;
extern int g_9134;
void far pascal fn_13_2f30(int i);

/* Find an object in area p; returns (type << 8) | idx or -1 [inferred]. */
/* @addr 12:1f7a */
int far pascal fn_12_1f7a(int p)
{
    int pad[4];
    RECT r;
    RECT r2;
    int i;
    int pad2[11];
    DWORD t;

    if (g_9320 == 7 && g_668a == 0
        && g_1df8[8][1].f04.x - g_1df8[8][0].f04.x - g_1df8[8][0].f20 < 100)
        return -1;
    for (i = 0; i < g_9146; i++) {
        if (g_1df8[g_507c[i]][g_50e0[i]].f18 == 0) {
            SetRect(&r, g_1df8[g_507c[i]][g_50e0[i]].f04.x, g_1df8[g_507c[i]][g_50e0[i]].f04.y,
                    g_1df8[g_507c[i]][g_50e0[i]].f04.x + g_1df8[g_507c[i]][g_50e0[i]].f20,
                    g_1df8[g_507c[i]][g_50e0[i]].f04.y + g_1df8[g_507c[i]][g_50e0[i]].f20);
            if (IntersectRect(&r2, &g_6678[p].r, &r)) {
                t = 0;
                if (g_507c[i] == g_9324) {
                    if (g_50e0[i] == g_9646)
                        t = g_7090[g_50e0[i]].f88 + 300;
                    else
                        t = g_7090[g_50e0[i]].f88 + 3000;
                }
                if (g_507c[i] != 7 && g_1df8[g_507c[i]][g_50e0[i]].f44 != 0xdac
                    && (g_507c[i] != g_9324 || t < g_1e50)) {
                    if (g_1df8[g_507c[i]][g_50e0[i]].f2e != 1
                        || (g_507c[i] == g_9324 && g_7090[g_50e0[i]].f2e == 2))
                        return g_50e0[i] | g_507c[i] << 8;
                }
            }
            if (g_507c[i] == g_9324 && g_7090[g_50e0[i]].f32 == 12
                && g_7090[g_50e0[i]].f34 == g_6678[p].f10 && g_7090[g_50e0[i]].f38 == 2) {
                if (g_50e0[i] != g_9646 || g_9134 != 0) {
                    SetRect(&r, g_1df8[g_507c[i]][g_50e0[i]].f04.x - 320,
                            g_1df8[g_507c[i]][g_50e0[i]].f04.y - 320,
                            g_1df8[g_507c[i]][g_50e0[i]].f04.x + 800,
                            g_1df8[g_507c[i]][g_50e0[i]].f04.y + 800);
                    if (PtInRect(&r, g_1df8[12][g_6678[p].f10].f04)) {
                        g_1df8[g_507c[i]][g_50e0[i]].f0c = 0;
                        g_1df8[g_507c[i]][g_50e0[i]].f0e = 0;
                        if (g_6678[p].f12 == 0 || (g_6678[p].f12 < 0
                            && abs(g_6678[p].r.right - g_6678[p].r.left - 480) <= 16)) {
                            g_7090[g_50e0[i]].f06 = g_7090[g_50e0[i]].f32 = 12;
                            g_7090[g_50e0[i]].f08 = g_7090[g_50e0[i]].f34 = g_6678[p].f10 + 1;
                            g_7090[g_50e0[i]].f3a = g_7090[g_50e0[i]].f3c =
                                g_7090[g_50e0[i]].f36 = g_7090[g_50e0[i]].f38 = 2;
                            fn_13_2f30(i);
                        }
                    }
                }
            }
        }
    }
    return -1;
}

extern int g_941a;
extern int g_951a;

/* Update and draw the links of the type-10 objects [inferred]. */
/* @addr 12:3148 */
void far fn_12_3148(void)
{
    int t;
    int x;
    int v;
    int i;
    int a;
    int b;
    HPEN old;
    HPEN pen;
    POINT p;
    POINT q;

    for (i = 0; i < g_941a; i++) {
        if (g_1df8[10][i].f18 == 0) {
            g_1df8[10][i].f1c = 0;
            g_1df8[10][i].f28 = fn_08_19b0(g_65cc[i].f10.x - g_65cc[i].f18.x,
                                           g_65cc[i].f10.y - g_65cc[i].f18.y);
            fn_08_1b54((char)i | 0xa00, 1);
            g_1df8[10][i].f10 = (g_1df8[10][i].f22 + g_1df8[10][i].f24) * g_1df8[10][i].f28
                + g_1df8[10][i].f24;
            fn_08_0b76((char)i | 0xa00, 3, g_39e8[3], 0);
            t = g_65cc[i].t2;
            x = g_65cc[i].i2;
            if (g_90ec * 8 / 2 < fn_08_285a(&a, &b, g_1df8[10][i].f04, g_1df8[t][x].f04))
                g_65cc[i].f08 += 50;
            if (g_1df8[10][i].f1a == 0)
                p = fn_08_29ea(g_1df8[10][i].f04);
            else
                p = g_1df8[10][i].f00;
            if (g_1df8[t][x].f1a == 0)
                q = fn_08_29ea(g_1df8[t][x].f04);
            else
                q = g_1df8[t][x].f00;
            g_65cc[i].f10.x = g_1df8[10][i].f22 / 2 + p.x;
            g_65cc[i].f10.y = g_1df8[10][i].f22 / 2 + p.y;
            g_65cc[i].f18.x = g_1df8[t][x].f22 / 2 + q.x;
            g_65cc[i].f18.y = g_1df8[t][x].f22 / 2 + q.y;
            old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
            fn_12_7256(g_13dc, g_65cc[i].f1c, g_65cc[i].f14);
            SelectObject(g_13dc, old);
            pen = CreatePen(PS_SOLID, 1, RGB(rand() % 128, 0, rand() % 128 + 128));
            old = SelectObject(g_13dc, pen);
            fn_12_7256(g_13dc, g_65cc[i].f18, g_65cc[i].f10);
            SelectObject(g_13dc, old);
            DeleteObject(pen);
            g_65cc[i].f14 = g_65cc[i].f10;
            g_65cc[i].f1c = g_65cc[i].f18;
            g_65cc[i].f08++;
            if (g_1df8[10][i].f1a != 0 && g_1df8[10][i].f1c == 0) {
                g_943a = 10;
                g_943c = i;
                v = fn_08_50aa((char)i | 0xa00);
                if (v != -1)
                    fn_12_3498(HIBYTE(v), LOBYTE(v), i);
            }
            if (g_65cc[i].f08 > 41)
                fn_12_3498(-1, -1, i);
            if (g_65cc[i].t2 == g_9324 && g_65cc[i].i2 == g_9646 && g_951a == 0)
                fn_07_1208();
        }
    }
}

/* 0x34-byte records from DS:3d50 (the records of DS:3d5a seen 0xa bytes
 * earlier) [inferred]. */
typedef struct {
    unsigned long f00;          /* +00: next launch time */
    char p04[0x08 - 0x04];
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    char p12[0x30 - 0x12];
    int f30;                    /* +30 */
    char p32[0x34 - 0x32];
} REC_34D;
extern REC_34D g_3d50[];
extern HBRUSH g_3b74[];
void far fn_07_5d6a(POINT p, int b, int c, int d);

/* Update and draw the type-8 object n [inferred]. */
/* @addr 12:390e */
void far pascal fn_12_390e(int n)
{
    int dead;
    int dead2;
    int k;
    int v;
    int m;
    int old;
    int unused[2];
    POINT p;
    int unused2;
    int pct;
    int r;

    if (g_1df8[8][n].f1a != 0 || g_3d50[n].f30 == 4 || g_3d50[n].f30 == 3) {
        if (g_3d50[n].f30 == 3) {
            k = 30;
            old = m = 0;
        } else if (g_3d50[n].f30 == 4) {
            k = 31;
            old = m = 0;
        } else if (g_1df8[8][n].f2f > 2) {
            k = 2;
            if (g_1df8[8][n].f2f > 4)
                old = SelectObject(g_13dc, g_3b74[g_1df8[8][n].f2f - g_0d08 < 1 ? 1
                                                  : g_1df8[8][n].f2f - g_0d08]);
            else
                old = SelectObject(g_13dc, g_3b74[g_1df8[8][n].f2f + g_0d08 - 2 < 1 ? 1
                                                  : g_1df8[8][n].f2f + g_0d08 - 2]);
            if (g_1df8[8][n].f6a < g_1e50) {
                g_1df8[8][n].f2f--;
                g_1df8[8][n].f6a = g_1e50 + 3000;
            }
            m = 1;
        } else {
            dead = (g_1df8[8][n].f22 + g_1df8[8][n].f24) * 2;
            old = 0;
            if (g_1df8[8][n].f2f < 0) {
                if (rand() % 7 == 2)
                    fn_07_5b68(8, n, 0);
                g_1df8[8][n].f2f++;
            }
            k = 1;
            m = 0;
        }
        pct = min(g_1df8[8][n].f1e * 100 / (g_1df8[8][n].f2c / 2), 100);
        if (g_1df8[8][n].f1e > g_1df8[8][n].f2c)
            pct = 0;
        if (pct > 30 && rand() % 200 < pct && rand() % 25 < 2) {
            p = g_1df8[8][n].f04;
            r = rand() % 4;
            p.x += (g_1df8[8][n].f22 / 2 * g_1050[r * 4].x / 14 - 5) * 8 + g_1df8[8][n].f20 / 2;
            p.y += (g_1df8[8][n].f22 / 2 * g_1050[r * 4].y / 14 - 5) * 8 + g_1df8[8][n].f20 / 2;
            fn_07_5d6a(p, 1, g_1050[r * 4].x * 2, g_1050[r * 4].y * 2);
        }
        if (g_3d50[n].f30 == 3) {
            g_1df8[8][n].f10 = (g_1df8[8][n].f22 + g_1df8[8][n].f24)
                * abs((int)((g_1e68 >> 3 & 1) * 3 - (g_1e68 >> 1 & 3)))
                + g_1df8[8][n].f24;
        } else if (g_3d50[n].f30 == 4) {
            g_1df8[8][n].f10 = (g_1df8[8][n].f22 + g_1df8[8][n].f24) * g_1df8[8][n].f28
                + g_1df8[8][n].f24;
            g_1df8[8][n].f12 = (g_1df8[8][n].f22 + g_1df8[8][n].f24) * g_1df8[8][n].f52
                + g_1df8[8][n].f24;
        } else {
            g_1df8[8][n].f10 = g_1df8[8][n].f22 * 2 + g_1df8[8][n].f24 * 3;
            if (g_1df8[8][n].f1e > g_1df8[8][n].f2c)
                g_1df8[8][n].f10 += g_1df8[8][n].f22 + g_1df8[8][n].f24;
        }
        if (g_1df8[8][n].f1a != 0)
            fn_08_0b76((char)n | 0x800, 3, g_39e8[k], m);
        if (old)
            SelectObject(g_13dc, old);
        if (g_3d50[n].f00 < g_1e50 && g_3d50[n].f0a != 0
            && g_1df8[8][n].f1e < g_1df8[8][n].f2c) {
            g_1df8[8][n].f28 = rand() % 4 * 4;
            if (fn_12_6ed8(n)) {
                g_3d50[n].f00 = (long)(rand() % g_3d50[n].f0e) + g_3d50[n].f10 + g_1e50;
                /* dead stores: only their loads and address arithmetic remain */
                if (g_3d50[n].f08 == 1)
                    dead2 = g_1df8[8][n].f04.x - 64;
                else
                    dead2 = g_1df8[8][n].f04.x + g_1df8[8][n].f22;
                dead2 = g_1df8[8][n].f04.x;
                fn_12_2db6(8, n, g_1df8[8][n].f28, g_3d50[n].f0c, g_3d50[n].f0a);
            }
        }
    }
    if ((g_1df8[8][n].f1a != 0 && g_1df8[8][n].f1c == 0)
        || (g_3d50[n].f30 == 3 && g_9208 > 1)) {
        g_943a = 8;
        g_943c = n;
        v = fn_08_50aa((char)n | 0x800);
        if (v != -1) {
            if (HIBYTE(v) == g_9328) {
                if (g_1df8[HIBYTE(v)][LOBYTE(v)].f44 == 0x78) {
                    g_1df8[8][n].f2f = min(g_1df8[8][n].f2f + 1, 9);
                    g_1df8[8][n].f6a = g_1e50 + 3000;
                } else if (g_1df8[HIBYTE(v)][LOBYTE(v)].f44 == 0xc8 && g_1df8[8][n].f2f > 0) {
                    g_1df8[8][n].f2f = -(g_1df8[8][n].f2f * 5);
                }
            }
            fn_08_5df2(8, n, HIBYTE(v), LOBYTE(v),
                       fn_08_546c(v, &g_1df8[8][n].f0c, &g_1df8[8][n].f0e,
                                  g_1df8[8][n].f20 + 2, g_1df8[8][n].f44));
        }
    }
}

extern int g_9412;
/* The 0x1c-byte records seen from DS:66ec; declared after g_2f4c so that CL
 * loads this operand first in 12:0000 (case 4). */
extern struct { int f00; char p02[0x1c - 2]; } g_66ec[];
void far pascal fn_04_5514(int n);
void far fn_07_2e02(int type, int idx);
/* The 0x15a-byte object records seen from DS:70a8 [inferred]. */
extern struct { int f00; char p02[0x15a - 2]; } g_70a8[];

/* Update every type-6 object: behaviour per class record, timers, drag,
 * collisions and expiry [inferred]. */
/* @addr 12:0000 */
void far fn_12_0000(void)
{
    int i;
    int ref;
    int k;
    int r;
    int unused[7];

    for (i = 0; i < g_9412; i++) {
        k = g_66e0[i].f04;
        if ((g_2f4c[k].f26 > g_66e0[i].f0c || g_2f4c[k].f2c == 6) && k != -1
            && g_1df8[6][i].f18 == 0) {
            switch (g_2f4c[k].f0e) {
            case 1:
                if (++g_66e0[i].f16 > g_2f4c[k].f1a) {
                    g_66e0[i].f16 = 0;
                    if (g_2f4c[k].f1a == -1)
                        g_1df8[6][i].f28 += 2;
                    g_1df8[6][i].f28++;
                    if (g_1df8[6][i].f28 > 15) {
                        g_1df8[6][i].f28 -= 16;
                        if (g_2f4c[k].f20 == 2)
                            fn_10_754a(2, 6, i, 1);
                    }
                }
                break;
            case 2:
                break;
            case 4:
                if (g_66e0[i].f0c < 50)
                    g_1df8[6][i].f28 = g_66ec[i].f00 * g_2f4c[k].f2e / 50;
                else
                    g_1df8[6][i].f28 = g_2f4c[k].f2e - 1;
                break;
            case 5:
                g_1df8[6][i].f28 = 0;
                break;
            }
            if (g_2f4c[k].f40 != 0 && !(g_66e0[i].f0c & 3))
                fn_04_5514(i);
            if (g_66e0[i].f0c % 13 == 0 && g_66e0[i].f0c > 8 && g_2f4c[k].f12 != 1
                && g_2f4c[k].f12 != 5
                && (g_2f4c[k].f44 != 0 || g_66e0[i].f00 == -1 || g_66e0[i].f0c == 13))
                fn_12_0586(i, g_66e0[i].f0c << 3);
            if (g_66e0[i].f1a == 0 && g_2f4c[k].f26 / 2 == g_66e0[i].f0c)
                g_66e0[i].f0c = g_2f4c[k].f26 - 5;
            if (g_2f4c[k].f42 == 0 && g_1df8[6][i].f1a == 0 && g_66e0[i].f0c > 20)
                g_66e0[i].f0c = g_2f4c[k].f26;
            if (g_66e0[i].f1a != 0 && (g_2f4c[k].f12 != 1 || g_66e0[i].f0c > g_66e0[i].f0e))
                fn_12_07c0(i);
            if (g_2f4c[k].f48 != 0) {
                g_1df8[6][i].f0c -= g_1df8[6][i].f0c >> g_2f4c[k].f48;
                g_1df8[6][i].f0e -= g_1df8[6][i].f0e >> g_2f4c[k].f48;
                if (g_1df8[6][i].f0c > -10 && g_1df8[6][i].f0c < 10)
                    g_1df8[6][i].f0c = 0;
                if (g_1df8[6][i].f0e > -10 && g_1df8[6][i].f0e < 10)
                    g_1df8[6][i].f0e = 0;
            }
            if (g_2f4c[k].f2c == 5 && g_2f4c[k].f26 - 8 < g_66e0[i].f0c)
                fn_07_5b68(6, i, 1);
            if (g_2f4c[k].f1c != 0) {
                if (g_2f4c[k].f1c == 3) {
                    g_1df8[6][i].f50 += 4;
                    if (g_1df8[6][i].f50 > 75)
                        g_1df8[6][i].f50 = 75;
                }
                fn_12_64aa(i, k);
            }
            fn_08_1b54((char)i | 0x600, 1);
            g_1df8[6][i].f10 = (g_1df8[6][i].f22 + g_1df8[6][i].f24) * g_1df8[6][i].f28
                + g_1df8[6][i].f24;
            if (g_1df8[6][i].f18 == 0) {
                if (g_2f4c[k].f06 == -1)
                    g_1df8[6][i].f00 = fn_08_29ea(g_1df8[6][i].f04);
                else
                    fn_08_0b76((char)i | 0x600, 3, g_39e8[g_2f4c[k].f04], 0);
            }
            if (g_1df8[6][i].f1a != 0 && g_66e0[i].f0c > 3) {
                g_943a = 6;
                g_943c = i;
                ref = fn_08_50aa((char)i | 0x600);
                if (ref != -1) {
                    r = fn_08_546c(ref, &g_1df8[6][i].f0c, &g_1df8[6][i].f0e,
                                   g_1df8[6][i].f20, g_1df8[6][i].f44);
                    if (g_1df8[6][i].f53 != 0 && HIBYTE(ref) == g_9324
                        && g_70ae[LOBYTE(ref)].fcc == 0)
                        fn_13_16ac(LOBYTE(ref), (char)i | 0x600);
                    else if (g_2f4c[k].f2c == 6 && HIBYTE(ref) == g_9324
                             && g_2f4c[g_70ae[LOBYTE(ref)].f9a[g_70a8[LOBYTE(ref)].f00]].f2c == 6) {
                        g_1df8[6][i].f53 = 1;
                        fn_13_16ac(LOBYTE(ref), (char)i | 0x600);
                        g_70ae[LOBYTE(ref)].f90[g_70a8[LOBYTE(ref)].f00]++;
                    } else
                        fn_08_5df2(6, i, HIBYTE(ref), LOBYTE(ref), r);
                }
            }
            if (g_1df8[6][i].f18 == 0) {
                if (++g_66e0[i].f0c >= g_2f4c[k].f26) {
                    if (g_2f4c[k].f2c == 1) {
                        fn_12_274a(6, i);
                        fn_07_2080(6, i);
                    } else if (g_2f4c[k].f2c == 4) {
                        fn_07_2e02(6, i);
                        fn_07_2080(6, i);
                    } else if (g_2f4c[k].f2c == 5) {
                        fn_12_6a60(6, i);
                    } else if (g_2f4c[k].f2c == 6) {
                        g_66e0[i].f00 = g_66e0[i].f08;
                        g_66e0[i].f02 = g_66e0[i].f0a;
                        g_66e0[i].f1a = 1;
                        if (g_1df8[g_66e0[i].f08][g_66e0[i].f0a].f18 != 0) {
                            fn_07_2e02(6, i);
                            fn_07_2080(6, i);
                        }
                    }
                    if (g_2f4c[k].f2c != 6)
                        g_1df8[6][i].f18 = 1;
                }
            }
        } else if (g_1df8[6][i].f51 != 0) {
            fn_12_129e(6, i);
        }
    }
}
