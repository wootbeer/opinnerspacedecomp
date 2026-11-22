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
    char p10[0x18 - 0x10];
    int f18;                    /* +18 */
    char p1a[2];
    int f1c;                    /* +1c */
    int f1e;                    /* +1e */
    char p20[0x22 - 0x20];
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    char p26[0x28 - 0x26];
    int f28;                    /* +28 */
    char p2a[0x2f - 0x2a];
    char f2f;                   /* +2f */
    char p30[0x32 - 0x30];
    int f32;                    /* +32 */
    char p34[2];
    int f36;                    /* +36 */
    char p38[2];
    HDC f3a;                    /* +3a */
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
    char pae[0xce - 0xae];
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
/* 0x34-byte records at DS:3d82 [inferred]. */
typedef struct { int f00; char p02[0x34 - 2]; } REC_34;
extern REC_34 g_3d82[];
extern REC_34 g_3d6c[];         /* the same records seen 0x16 bytes earlier */

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
void far pascal fn_12_1776(int a)
{
    g_9430 = a;
}

void far pascal fn_12_390e(int a)
{
    g_9430 = a;
}

void far pascal fn_12_5636(int a)
{
    g_9430 = a;
}

void far fn_12_7006(void)
{
    g_9430 = 0;
}

void far fn_12_7256(HDC dc, POINT a, POINT b)
{
    g_9430 = a.x + b.x;
}

void far pascal fn_12_2db6(int type, int idx, int c, int d, int kind)
{
    g_9430 = type + idx + c + d + kind;
}

/* Turn direction cur (0..15) one step toward the direction from a to b
 * on the wrapping map [inferred]. dir stays uninitialised when mode is
 * neither 2 nor 5 (as in the original). */
/* near-match 25%: 12:67e8 (only the - case of the wrap differs: the original
 * computes it as neg(W*8 - b.x)) */
int far pascal fn_12_67e8(POINT a, POINT b, int mode, int cur)
{
    int dx;
    int dy;
    int dir;
    int unused[6];

    dx = b.x - a.x;
    if (fn_09_88ba(dx) > (G_05A0_INT >> 1 << 3))
        dx = (0 > dx ? G_05A0_INT * 8 + b.x : b.x - G_05A0_INT * 8) - a.x;
    dy = b.y - a.y;
    if (fn_09_88ba(dy) > (g_05a2 >> 1 << 3))
        dy = (0 > dy ? g_05a2 * 8 + b.y : b.y - g_05a2 * 8) - a.y;
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
    HGDIOBJ old;
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
