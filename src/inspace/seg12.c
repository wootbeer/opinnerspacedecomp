/* INSPACE.EXE segment 12 (selector 1058). No 32-bit code anywhere in this
 * segment: compiled with /G2 [inferred, confirmed by matches]. */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array per object type
 * [inferred, as in seg07.c]. Only the fields used here are named. */
typedef struct {
    POINT f00;                  /* +00 */
    POINT f04;                  /* +04 */
    char p08[4];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x18 - 0x10];
    int f18;                    /* +18 */
    char p1a[0x1e - 0x1a];
    int f1e;                    /* +1e */
    char p20[0x22 - 0x20];
    int f22;                    /* +22 */
    char p24[0x28 - 0x24];
    int f28;                    /* +28 */
    char p2a[0x2f - 0x2a];
    char f2f;                   /* +2f */
    char p30[0x3c - 0x30];
    HDC f3c;                    /* +3c */
    HBITMAP f3e;                /* +3e */
    HBITMAP f40;                /* +40 */
    char p42[0x50 - 0x42];
    char f50;                   /* +50 */
    char f51;                   /* +51 */
    char p52[0x54 - 0x52];
    char f54;                   /* +54 */
    char p55[0x66 - 0x55];
    void (far *f66)(int type, int idx);  /* +66 */
    char p6a[0x6e - 0x6a];
    HPALETTE f6e;               /* +6e */
} REC_70;
extern REC_70 far *g_1df8[16];

/* 0x15a-byte records at DS:70ae (as in seg09.c). */
typedef struct {
    char p00[0x90];
    char f90[10];               /* +90 */
    char f9a[0x13];             /* +9a */
    char fad;                   /* +ad: entries used in f9a [inferred] */
    char pae[0x15a - 0xae];
} REC_15A;
extern REC_15A g_70ae[];

/* 0x50-byte records at DS:2f5e [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    char p02[0x14 - 0x02];
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
    char p0c[0x14 - 0x0c];
} REC_14;
extern REC_14 g_1e90[];
extern POINT g_5170[];
extern POINT g_5224[];
extern int g_9430;
extern int g_9434;
extern int g_9316;
extern int g_9320;
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
extern int g_05a2;

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
        if (k >= 0 && g_1df8[12][k].f51 == 0)
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

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far pascal fn_12_2db6(int type, int idx, int c, int d, int kind)
{
    g_9430 = type + idx + c + d + kind;
}

/* Turn direction cur (0..15) one step toward the direction from a to b
 * on the wrapping map [inferred]. dir stays uninitialised when mode is
 * neither 2 nor 5 (as in the original). */
/* @addr 12:67e8 */
int far pascal fn_12_67e8(POINT a, POINT b, int mode, int cur)
{
    int dx;
    int dy;
    int dir;
    int unused[7];

    dx = b.x - a.x;
    if (fn_09_88ba(dx) > ((int)g_05a0 & ~1) * 4)
        dx = (dx < 0 ? (int)g_05a0 * 8 + b.x : -((int)g_05a0 * 8 - b.x)) - a.x;
    dy = b.y - a.y;
    if (fn_09_88ba(dy) > (g_05a2 & ~1) * 4)
        dy = (dy < 0 ? g_05a2 * 8 + b.y : -(g_05a2 * 8 - b.y)) - a.y;
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
