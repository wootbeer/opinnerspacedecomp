/* INSPACE.EXE segment 8 (selector 1038), part compiled with /G2:
 * no 32-bit code from 8:3688 to 8:81f8 [inferred: one source file]. */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include <stdlib.h>
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array per object type
 * [inferred, as in seg07.c]. */
typedef struct {
    POINT f00;                  /* +00 */
    POINT f04;                  /* +04 */
    char p08[4];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x18 - 0x10];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    int f1c;                    /* +1c */
    char p1e[2];
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    char p24[0x2e - 0x24];
    char f2e;                   /* +2e */
    char f2f;                   /* +2f */
    char p30[2];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    char p36[0x44 - 0x36];
    int f44;                    /* +44 */
    char p46[0x48 - 0x46];
    int f48;                    /* +48 */
    char p4a[0x50 - 0x4a];
    char f50;                   /* +50 */
    char p51[0x54 - 0x51];
    char f54;                   /* +54 */
    char p55[0x70 - 0x55];
} REC_70;
extern REC_70 far *g_1df8[16];

extern int g_90ea;
extern int g_90ec;
extern int g_52dc;
extern int g_52de;
extern int g_52e0;
extern int g_52e2;
/* 0x15a-byte records at DS:70ae (as in seg09.c). */
typedef struct {
    char p00[0x10];
    int f10;                    /* +10 */
    char p12[0xba - 0x12];
    int fba;                    /* +ba */
    char pbc[0xc5 - 0xbc];
    char fc5;                   /* +c5 */
    char pc6[0x15a - 0xc6];
} REC_15A;
extern REC_15A g_70ae[];

extern int g_9324;
extern int g_9326;
extern int g_9e49;
extern int g_9158;
extern int g_9146;
extern int g_952e;
extern int g_9406[];
extern RECT g_23e0[];
extern char g_507c[];
extern char g_50e0[];
extern int subgame_active;      /* DS:9130 */
/* 0x34-byte records at DS:3d5a (as in seg10.c) [inferred]. */
typedef struct { char p00[0x26]; int f26; char p28[0x34 - 0x28]; } REC_34;
extern REC_34 g_3d5a[];
void far fn_11_9fdc(int type, int idx);
/* 0x14-byte records at DS:1e90 (as in seg12.c) [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    long f10;                   /* +10 */
} REC_14B;
extern REC_14B g_1e90[];
extern POINT g_5170[];
extern POINT g_5224[];
extern int g_9430;
extern int g_9434;
/* 0x94-byte records at DS:6098 (as in seg08c.c) [inferred]. */
typedef struct {
    int x0[2][6];   /* +0 */
    int y0[2][6];   /* +18 */
    int x1[2][6];   /* +30 */
    int y1[2][6];   /* +48 */
    char p60[0x7a - 0x60];
    int f7a;        /* +7a */
    int f7c;        /* +7c */
    char p7e[0x94 - 0x7e];
} REC_94;
extern REC_94 g_6098[];
extern int g_9646;
extern int g_0b0e[];
extern int g_0b38[];
extern long g_5078;
extern long g_1e58;
extern int g_9436;
extern int g_9438;
extern int g_944a;
extern int g_944c;
extern int g_944e;
extern int g_9450;

void far fn_08_5df2(int a, int b, int c, int d, int e);
/* 0x1c-byte records at DS:66e4 [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    char p0a[0x1c - 0x0a];
} REC_1C;
extern REC_1C g_66e4[];
extern RECT g_5148;
extern RECT g_5150;
extern RECT g_5158;
extern RECT g_5160;
extern POINT g_52e4;
extern POINT g_52e8;
extern int object_sizes[2];     /* DS:9442 */
extern int object_masses[2];    /* DS:9446 */
POINT far pascal fn_08_29ea(POINT pt);
extern int g_9320;
extern int g_9208;
extern int g_9316;
extern int g_9156;
extern int g_88c0;
extern int g_88c2;
extern int g_88c4;
extern int g_88c6;
extern POINT far *g_1e38;
void far fn_18_2c1e(int type, int idx);
int far pascal fn_08_6afa(WORD a, WORD b);
#define SC(n) ((n) << g_9156 >> 1)
void far fn_08_7be8(int a, int b, int c, int d);

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_08_5df2(int a, int b, int c, int d, int e)
{
    g_9436 = a + b + c + d + e;
}

/* @addr 8:6a44 */
void far pascal fn_08_6a44(int a)
{
    int type;
    int idx;

    g_1df8[g_944c][g_9450].f1c = 1;
    g_1df8[g_944c][g_9450].f0c = g_52dc;
    g_1df8[g_944c][g_9450].f0e = g_52de;
    if (a) {
        if (g_1df8[g_944c][g_9450].f54) {
            g_1df8[g_944c][g_9450].f0e = 0;
            g_1df8[g_944c][g_9450].f0c = g_1df8[g_944c][g_9450].f0e;
        }
        fn_08_5df2(g_944c, g_9450, g_944a, g_944e, g_9436);
    }
}

/* The original reads the record's word at +4 and drops it; a volatile
 * read reproduces that. */
/* @addr 8:698a */
void far pascal fn_08_698a(int a)
{
    int type;
    int idx;

    g_1df8[g_944a][g_944e].f1c = 1;
    g_1df8[g_944a][g_944e].f0c = g_52e0;
    g_1df8[g_944a][g_944e].f0e = g_52e2;
    if (a) {
        *(volatile int far *)&g_1df8[g_944a][g_944e].f04.x;
        if (g_1df8[g_944a][g_944e].f54) {
            g_1df8[g_944a][g_944e].f0e = 0;
            g_1df8[g_944a][g_944e].f0c = g_1df8[g_944a][g_944e].f0e;
        }
        fn_08_5df2(g_944a, g_944e, g_944c, g_9450, g_9438);
    }
}

/* Swap two ints. */
/* @addr 8:4d60 */
void far pascal fn_08_4d60(int far *a, int far *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;
}

/* Swap two longs. */
/* @addr 8:4d94 */
void far pascal fn_08_4d94(long far *a, long far *b)
{
    long t;

    t = *a;
    *a = *b;
    *b = t;
}

/* Swap two bytes. */
/* @addr 8:4dde */
void far pascal fn_08_4dde(unsigned char far *a, unsigned char far *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;
}

/* @addr 8:7ba8 */
BOOL far fn_08_7ba8(POINT pt)
{
    RECT r;

    SetRect(&r, -50, -50, g_90ea + 50, g_90ec + 50);
    return PtInRect(&r, pt);
}

extern int g_937a[];
extern char g_938a[];
extern char g_9392[];
extern unsigned long g_1e68;

/* Shift a 7-entry history down and record a new entry [inferred]. */
/* @addr 8:81f8 */
void far fn_08_81f8(char a, char b)
{
    int i;

    for (i = 6; i >= 0; i--) {
        g_937a[i + 1] = g_937a[i];
        g_938a[i + 1] = g_938a[i];
        g_9392[i + 1] = g_9392[i];
    }
    g_937a[0] = (int)(g_1e68 / 10);
    g_938a[0] = a;
    g_9392[0] = b;
}

/* Add to the score DS:5078 (capped at 500000) [inferred]. */
/* @addr 8:7be8 */
void far fn_08_7be8(int a, int b, int c, int d)
{
    if (a == g_9324 && b == g_9646)
        return;
    if (d) {
        g_5078 = g_5078 + g_0b0e[a] > 500000L ? 500000L : g_5078 + g_0b0e[a];
        g_1e58 += g_0b0e[a];
        if (a == g_9324)
            g_5078 += g_70ae[b].fba * 2;
        if (a == 8 && g_1df8[8][b].f54)
            g_5078 += g_0b0e[a];
    } else {
        g_5078 += g_0b38[a] * c;
        if (a == 8 && g_1df8[8][b].f44 > 2000)
            g_5078 += g_0b38[a] * c * 2;
        if (a == g_9324)
            g_5078 += g_70ae[b].fba / 8;
    }
}

/* @addr 8:7ce0 */
void far fn_08_7ce0(int a, int b, int c, int d)
{
    int i;
    int n;

    n = 0;
    for (i = 0; i < 8; i++) {
        if (g_938a[i] == a && g_9392[i] == b) {
            if (g_937a[i] == 0)
                n++;
            if (g_1e68 / 10 - g_937a[i] < 20)
                n += 3;
        }
    }
    if (n > 6)
        fn_08_7be8(a, b, c, d);
}

/* @addr 8:804a */
void far fn_08_804a(int a, int b, int c)
{
    int k;
    int j;

    for (k = 0; k < 4; k++) {
        if (g_1e90[k].f00 == -1 || g_1e90[k].f0a <= 5) {
            if (g_1e90[k].f00 > -1) {
                for (j = 4; j < 45; j++) {
                    if (g_1e90[j].f00 == -1) {
                        g_1e90[j].f00 = g_1e90[k].f00;
                        g_1e90[j].f02 = g_1e90[k].f02;
                        g_1e90[j].f06 = g_1e90[k].f06;
                        g_1e90[j].f08 = g_1e90[k].f08;
                        g_1e90[j].f10 = g_1e90[k].f10;
                        g_1e90[j].f0a = g_1e90[k].f0a;
                        g_5170[j] = g_5170[k];
                        g_5224[j] = g_5224[k];
                        if (j > g_9434)
                            g_9434 = j;
                        g_1e90[j].f0c = g_1e90[k].f0c;
                        g_1e90[j].f0e = g_1e90[k].f0e;
                        break;
                    }
                }
            }
            g_1e90[k].f00 = 1;
            g_1e90[k].f02 = min(b / 630 + 2, 14);
            g_1e90[k].f0a = 7;
            g_1e90[k].f0c = 2;
            if (k > g_9434)
                g_9434 = k;
            if (g_6098[a].f7a == g_9324 && g_70ae[g_6098[a].f7c].fc5)
                g_1e90[k].f0e = 10;
            else
                g_1e90[k].f0e = 15;
            g_9430++;
            g_1e90[k].f04 = 2;
            g_1e90[k].f06 = 0x1e;
            g_1e90[k].f08 = a;
            g_5224[k].x = g_6098[a].x1[c][0];
            g_5224[k].y = g_6098[a].y1[c][0];
            g_5170[k].x = g_6098[a].x0[c][0];
            g_5170[k].y = g_6098[a].y0[c][0];
            return;
        }
    }
}

/* Collect the objects inside the view rectangles into the draw list
 * DS:507c/50e0 [inferred]. */
/* @addr 8:4e14 */
void far fn_08_4e14(void)
{
    int t;
    int i;
    int r;
    int unused[6];
    int found;
    int mode;

    mode = 1;
    if (subgame_active == 0) {
        if (g_9e49 > 6 || g_9e49 < 3)
            mode = 0;
        for (t = g_9326; t <= g_9324; t++) {
            if (mode == 0 || t != 7) {
                if (t == 14 && mode)
                    mode = 2;
                for (i = 0; i < g_9406[t]; i++) {
                    if (g_1df8[t][i].f18 == 0 && g_1df8[t][i].f44 != 0
                        && (t != 8 || g_3d5a[i].f26 != 4)
                        && (mode < 2 || i != g_952e)) {
                        for (r = found = 0; r < g_9158; r++) {
                            if (PtInRect(&g_23e0[r], g_1df8[t][i].f04)) {
                                g_1df8[t][i].f1c = 0;
                                g_507c[g_9146] = t;
                                g_50e0[g_9146] = i;
                                g_9146++;
                                found = 1;
                                break;
                            }
                        }
                        if (found) {
                            g_1df8[t][i].f1a = 1;
                        } else if (g_1df8[t][i].f1a <= 0) {
                            g_1df8[t][i].f1a = 0;
                            g_1df8[t][i].f00.x = -1000;
                            g_1df8[t][i].f00.y = -1000;
                        } else {
                            g_1df8[t][i].f1a = -1;
                        }
                    }
                }
            }
        }
    } else {
        for (t = g_9326; t <= g_9324; t++) {
            for (i = 0; i < g_9406[t]; i++) {
                g_1df8[t][i].f1c = 0;
                g_507c[g_9146] = t;
                g_50e0[g_9146] = i;
                g_9146++;
                g_1df8[t][i].f1a = 1;
            }
        }
    }
    if (rand() % 9 == 0) {
        for (t = 0; t < g_9146; t++) {
            if (g_1df8[g_507c[t]][g_50e0[t]].f50 && g_507c[t] != g_9324) {
                for (i = 0; i < g_9146; i++) {
                    if (g_1df8[g_507c[i]][g_50e0[i]].f18 == 0 && i != t) {
                        fn_11_9fdc(g_507c[t], g_50e0[t]);
                        break;
                    }
                }
            }
        }
    }
}

int far fn_08_35d0(long a, long b);
int far fn_09_88ba(int x);

/* Bounce of two round bodies of sizes a and b at positions *p1/*p2 and
 * *p3/*p4 with velocities (*p5 - *p7)... [inferred]; returns 0 when they
 * move apart too fast, else nothing defined (no return, as in the
 * original). */
/* The ratio goes through the dead local u14: that keeps the dot product
 * evaluated before the divisor. */
/* @addr 8:7d70 */
int far pascal fn_08_7d70(int far *p8, int far *p7, int far *p6, int far *p5,
                          int far *p4, int far *p3, int far *p2, int far *p1,
                          int b, int a)
{
    int dx;
    int dy;
    int sum;
    int vx;
    int vy;
    int c;
    int d1;
    int d2;
    int u14;
    int ux;
    int uy;
    int k;
    int r2;
    int r1;
    long l;

    dx = b / 2 - a / 2 - *p2 + *p4;
    dy = b / 2 - a / 2 - *p1 + *p3;
    sum = a / 2 + b / 2;
    vx = *p8 - *p6;
    vy = *p7 - *p5;
    d1 = fn_08_35d0(dx, dy);
    if (d1 == 0)
        d1 = 1;
    if (fn_09_88ba(vx) < 10 && fn_09_88ba(vy) < 10) {
        *p8 = *p6 - dx * 15 / d1;
        *p7 = *p5 - dy * 15 / d1;
        vx = *p8 - *p6;
        vy = *p7 - *p5;
    }
    d2 = fn_08_35d0(vx, vy);
    if (d2 == 0)
        d2 = 1;
    l = (long)vx * dx + (long)vy * dy;
    if ((u14 = (int)(l * 100 / ((long)d2 * d1))) > 15)
        return 0;
    c = sum;
    ux = vx * 100 / d2;
    uy = vy * 100 / d2;
    if (vy > 0)
        r1 = (b / 2 - a / 2 - *p1 + *p3 + c) * 100
            / (1 > fn_09_88ba(uy) ? 1 : fn_09_88ba(uy));
    else
        r1 = (a / 2 - b / 2 - *p3 + *p1 + c) * 100
            / (1 > fn_09_88ba(uy) ? 1 : fn_09_88ba(uy));
    if (vx > 0)
        r2 = (b / 2 - a / 2 - *p2 + *p4 + c) * 100
            / (1 > fn_09_88ba(ux) ? 1 : fn_09_88ba(ux));
    else
        r2 = (a / 2 - b / 2 - *p4 + *p2 + c) * 100
            / (1 > fn_09_88ba(ux) ? 1 : fn_09_88ba(ux));
    k = fn_09_88ba(r1) > fn_09_88ba(r2) ? r2 : r1;
    /* dead stores: only their loads remain */
    l = (long)b - (long)a;
    u14 = *p3;
    *p4 += k * ux / -100;
    *p3 += k * uy / -100;
}

extern int g_1318;
extern int g_0b0c;
extern int g_90f4;
extern int g_9156;
extern int g_943a;
extern int g_943c;
long far pascal fn_08_1290(long n, long g);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);

/* Blast wave of particle j: push and damage every object near it
 * [inferred]. */
/* @addr 8:5ab0 */
void far pascal fn_08_5ab0(int j)
{
    int kind;
    int st;
    int si_;
    int t;
    int i;
    int d;
    int dy;
    int dx;
    int f;
    long vx;
    long vy;
    long s;
    POINT pos;

    st = g_1e90[j].f06;
    si_ = g_1e90[j].f08;
    kind = g_1e90[j].f0a;
    pos.x = g_5224[j].x;
    pos.y = g_5224[j].y;
    if (g_1318 > 6)
        return;
    for (t = g_9326; t <= g_9324; t++) {
        for (i = 0; i < g_9406[t]; i++) {
            if (g_1df8[t][i].f18 == 0 && g_1df8[t][i].f44 != 0
                && !(t == g_9324 && i == g_952e && g_1df8[t][i].f1a == 0)
                && !(kind == -250 && t == st && i == si_)) {
                d = fn_08_285a(&dy, &dx, pos, g_1df8[t][i].f04);
                d = d * 2 >> g_9156;
                dy = dy * 2 >> g_9156;
                dx = dx * 2 >> g_9156;
                if (subgame_active && g_90f4 == 6) {
                    d <<= 1;
                    dy <<= 1;
                    dx <<= 1;
                }
                if (d < 100)
                    d = 100;
                if ((min(g_1df8[st][si_].f48, 7) + 8) * 15 > d && d != 0) {
                    f = g_1df8[st][si_].f48 * 600 / d;
                    f = f * 15 / (1 > (int)fn_08_1290((long)g_1df8[t][i].f44, 25L) ? 1
                                  : (int)fn_08_1290((long)g_1df8[t][i].f44, 25L));
                    if (t == 2)
                        f *= 3;
                    g_1df8[t][i].f2f += 2;
                    if (d < 150)
                        g_1df8[t][i].f2f += 2;
                    if (g_1df8[t][i].f2f > 9)
                        g_1df8[t][i].f2f = 9;
                    g_943a = st;
                    g_943c = si_;
                    g_0b0c = 1;
                    if (g_1e90[j].f00 != 0)
                        g_0b0c = 0;
                    fn_08_5df2(t, i, st, si_, -f);
                    g_0b0c = 1;
                    s = g_1df8[st][si_].f48 * 250 / (d / 10) / ((g_1df8[t][i].f44 + 100) / 100);
                    vx = s * dy / d;
                    vy = s * dx / d;
                    g_1df8[t][i].f0c += vx;
                    g_1df8[t][i].f0e += vy;
                }
            }
        }
    }
}

/* Collision test of objects a and b, each (type << 8) | index [inferred]:
 * 0 if they cannot or do not touch, else sets up the collision globals
 * and returns 1. The SetRect sits inside the || chain. flag is
 * uninitialised unless one of the four tests sets it (as in the
 * original). */
/* @addr 8:6afa */
int far pascal fn_08_6afa(WORD a, WORD b)
{
    int u4;
    int u6;
    int u8;
    int ua;
    int flag;
    int t1;
    int i1;
    int t2;
    int i2;

    t1 = HIBYTE(a);
    i1 = LOBYTE(a);
    t2 = HIBYTE(b);
    i2 = LOBYTE(b);
    if (g_1df8[t1][i1].f54 != 0 && g_1df8[t2][i2].f54 != 0)
        return 0;
    if (g_1df8[t1][i1].f18 != 0 || !PtInRect(&g_5148, g_1df8[t1][i1].f00)
        || (SetRect(&g_5150, g_1df8[t1][i1].f00.x, g_1df8[t1][i1].f00.y,
                g_1df8[t1][i1].f00.x + g_1df8[t1][i1].f22,
                g_1df8[t1][i1].f00.y + g_1df8[t1][i1].f22), 0)
        || !IntersectRect(&g_5158, &g_5160, &g_5150)
        || t1 == 10 && g_1df8[t1][i1].f32 == t2 && g_1df8[t1][i1].f34 == i2)
        return 0;
    if (t2 == 10 && g_1df8[t2][i2].f32 == t1 && g_1df8[t2][i2].f34 == i1)
        return 0;
    if (g_1df8[t1][i1].f2e != 0 && (t1 != g_9324 || g_70ae[i1].f10 != 2))
        return 0;
    if (g_1df8[t2][i2].f2e != 0 && (t2 != g_9324 || g_70ae[i2].f10 != 2))
        return 0;
    if (t1 == 6 && g_66e4[i1].f08 < 10 && g_66e4[i1].f04 == t2 && g_66e4[i1].f06 == i2)
        return 0;
    if (t2 == 6 && g_66e4[i2].f08 < 10 && g_66e4[i2].f04 == t1 && g_66e4[i2].f06 == i1)
        return 0;
    if ((t2 == 7 || t1 == 7) && g_9e49 == 1)
        g_9e49 = 0;
    g_1df8[t1][i1].f1c = 1;
    g_1df8[t2][i2].f1c = g_1df8[t1][i1].f1c;
    if (t1 == g_9324 && i1 == g_9646)
        flag = 1;
    if (t2 == g_9324 && i2 == g_9646)
        flag = 0;
    if (g_1df8[t1][i1].f54 != 0)
        flag = 1;
    if (g_1df8[t2][i2].f54 != 0)
        flag = 0;
    if (flag) {
        g_52e0 = g_1df8[t1][i1].f0c;
        g_52e2 = g_1df8[t1][i1].f0e;
        if (g_1df8[t1][i1].f1a)
            g_52e4 = g_1df8[t1][i1].f00;
        else
            g_52e4 = fn_08_29ea(g_1df8[t1][i1].f04);
        g_944c = t2;
        g_9450 = i2;
        g_944a = t1;
        g_944e = i1;
        if (subgame_active == 0) {
            object_sizes[1] = g_1df8[t2][i2].f20 + 2;
            object_sizes[0] = g_1df8[t1][i1].f20 + 2;
        } else {
            object_sizes[1] = g_1df8[t2][i2].f22;
            object_sizes[0] = g_1df8[t1][i1].f22;
        }
        object_masses[0] = g_1df8[t1][i1].f44;
    } else {
        g_52dc = g_1df8[t1][i1].f0c;
        g_52de = g_1df8[t1][i1].f0e;
        if (g_1df8[t1][i1].f1a)
            g_52e8 = g_1df8[t1][i1].f00;
        else
            g_52e8 = fn_08_29ea(g_1df8[t1][i1].f04);
        g_944c = t1;
        g_9450 = i1;
        g_944a = t2;
        g_944e = i2;
        if (subgame_active == 0) {
            object_sizes[1] = g_1df8[t1][i1].f20 + 2;
            object_sizes[0] = g_1df8[t2][i2].f20 + 2;
        } else {
            object_sizes[1] = g_1df8[t1][i1].f22;
            object_sizes[0] = g_1df8[t2][i2].f22;
        }
        object_masses[1] = g_1df8[t1][i1].f44;
    }
    return 1;
}

/* Find an object that collides with r ((type << 8) | index) [inferred]:
 * returns its reference, 0x1000 for the sub-game border, or -1. */
/* @addr 8:50aa */
int far pascal fn_08_50aa(WORD r)
{
    int i;
    int u6;
    int t;
    int idx;
    WORD res;

    t = HIBYTE(r);
    idx = LOBYTE(r);
    if (g_1df8[t][idx].f1c == 0) {
        if (g_9320 == 6 && g_1df8[t][idx].f1a == 0 && g_9208 > 1) {
            g_1df8[t][idx].f00 = fn_08_29ea(g_1df8[t][idx].f04);
            SetRect(&g_5160, g_1df8[t][idx].f00.x, g_1df8[t][idx].f00.y,
                g_1df8[t][idx].f00.x + g_1df8[t][idx].f22,
                g_1df8[t][idx].f00.y + g_1df8[t][idx].f22);
            SetRect(&g_5148, g_1df8[t][idx].f00.x - SC(70), g_1df8[t][idx].f00.y - SC(70),
                g_1df8[t][idx].f00.x + g_1df8[t][idx].f22 + SC(15),
                g_1df8[t][idx].f00.y + g_1df8[t][idx].f22 + SC(15));
            for (i = 0; i <= g_9316; i++) {
                if (g_1df8[14][i].f1a == 0 && g_1df8[14][i].f18 == 0
                    && (t != 14 || idx != i)) {
                    g_1df8[14][i].f00 = fn_08_29ea(g_1df8[14][i].f04);
                    res = (char)i | 0xe00;
                    if (fn_08_6afa(res, r))
                        return res;
                }
            }
        } else {
            SetRect(&g_5160, g_1df8[t][idx].f00.x, g_1df8[t][idx].f00.y,
                g_1df8[t][idx].f00.x + g_1df8[t][idx].f22,
                g_1df8[t][idx].f00.y + g_1df8[t][idx].f22);
            SetRect(&g_5148, g_1df8[t][idx].f00.x - SC(70), g_1df8[t][idx].f00.y - SC(70),
                g_1df8[t][idx].f00.x + g_1df8[t][idx].f22 + SC(15),
                g_1df8[t][idx].f00.y + g_1df8[t][idx].f22 + SC(15));
            for (i = 0; i < g_9146; i++) {
                if (!(g_507c[i] < t || g_507c[i] <= t && g_50e0[i] == idx)) {
                    if (g_1df8[g_507c[i]][g_50e0[i]].f1c == 0) {
                        res = g_50e0[i] | g_507c[i] << 8;
                        if (fn_08_6afa(res, r))
                            return res;
                    }
                }
            }
        }
    }
    if (subgame_active != 0) {
        int flag;

        flag = 0;
        if (g_1df8[t][idx].f00.x <= g_88c4) {
            g_1e38->x = g_88c4 - g_1df8[t][idx].f22;
            g_1e38->y = g_1df8[t][idx].f00.y + g_88c6;
            flag = 1;
        } else if (g_88c4 - g_1df8[t][idx].f22 + g_88c0 < g_1df8[t][idx].f00.x) {
            g_1e38->x = g_88c4 + g_88c0;
            g_1e38->y = g_1df8[t][idx].f00.y + g_88c6;
            flag = 1;
        } else if (g_1df8[t][idx].f00.y <= g_88c6) {
            g_1e38->y = g_88c6 - g_1df8[t][idx].f22;
            g_1e38->x = g_1df8[t][idx].f00.x + g_88c4;
            flag = 1;
        } else if (g_88c6 - g_1df8[t][idx].f22 + g_88c2 < g_1df8[t][idx].f00.y) {
            g_1e38->y = g_88c6 + g_88c2;
            g_1e38->x = g_1df8[t][idx].f00.x + g_88c4;
            flag = 1;
        } else {
            fn_18_2c1e(t, idx);
        }
        if (flag != 0) {
            g_52e0 = 0;
            g_52e2 = 0;
            g_52e4 = *g_1e38;
            g_944c = t;
            g_9450 = idx;
            g_944a = 16;
            g_944e = 0;
            object_sizes[1] = g_1df8[t][idx].f22;
            object_sizes[0] = g_1df8[t][idx].f22;
            object_masses[0] = 20000;
            return res = 0x1000;
        }
    }
    return -1;
}
