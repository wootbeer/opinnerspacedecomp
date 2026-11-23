/* INSPACE.EXE segment 8 (selector 1038), 8:8256 to the end: a separate
 * source file (inventory/files.tsv file 17; 8:9ab8 far-calls 8:285a).
 * Declarations copied from seg08.c. */
#include <stdlib.h>
#include "inspace.h"

/* 20-byte records at DS:58bc [inferred: tracked positions]. */
typedef struct {
    POINT a;        /* +0 */
    POINT b;        /* +4 */
    POINT c;        /* +8 */
    char rest[8];   /* +c */
} REC_14;
extern REC_14 g_58bc[];

/* 0x94-byte records at DS:6098 [inferred]. */
typedef struct {
    int x0[2][6];   /* +0 */
    int y0[2][6];   /* +18 */
    int x1[2][6];   /* +30 */
    int y1[2][6];   /* +48 */
    int z[4];       /* +60 */
    char p68[8];
    int f70;        /* +70 */
    int f72;        /* +72 */
    int f74;        /* +74 */
    int f76;        /* +76 */
    int count;      /* +78 */
    int f7a;        /* +7a */
    int f7c;        /* +7c */
    char p7e[2];
    int f80;        /* +80 */
    int f82;        /* +82 */
    int f84;        /* +84 */
    int f86;        /* +86 */
    char p88[0x94 - 0x88];
} REC_94;
extern REC_94 g_6098[];
extern REC_94 g_6098[];

/* 0x1c-byte records at DS:2414, [?][5][5] [inferred]. */
typedef struct {
    POINT p;        /* +0 */
    POINT q;        /* +4 */
    POINT r;        /* +8 */
    int f0c;        /* +c */
    int f0e;        /* +e */
    int f10;        /* +10 */
    int f12;        /* +12 */
    char pad[4];
    POINT s;        /* +18 */
} REC_1C;
extern REC_1C g_2414[][5][5];

/* 0x16-byte records at DS:5b28, [?][4] [inferred]. */
typedef struct {
    POINT p;        /* +0 */
    POINT q;        /* +4 */
    POINT r;        /* +8 */
    char pad[6];    /* +c */
    POINT s;        /* +12 */
} REC_16;
extern REC_16 g_5b28[][4];

/* 0x70-byte records; DS:1df8 holds one far array per object type
 * [inferred, as in seg07.c]. */
typedef struct {
    POINT f00;                  /* +00 */
    POINT f04;                  /* +04 */
    char p08[4];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[8];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[2];
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    char p24[0x28 - 0x24];
    int f28;                    /* +28 */
    char p2a[0x2e - 0x2a];
    char f2e;                   /* +2e */
    char p2f[0x32 - 0x2f];
    int f32;                    /* +32 */
    char p34[0x54 - 0x34];
    char f54;                   /* +54 */
    char p55[0x70 - 0x55];
} REC_70;

/* Object reference passed by value: index, then type [inferred]. */
typedef struct { unsigned char idx, type; } OBJREF;
extern REC_70 far *g_1df8[16];

typedef struct { int a, b; } PAIR;      /* [inferred: kind + index] */

/* 0x24-byte records at DS:52ec [inferred]. */
typedef struct {
    long d00;                   /* +00 */
    char p04[4];
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    char p0c[4];
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    int f14;                    /* +14 */
    char p16[2];
    PAIR f18;                   /* +18 */
    PAIR f1c;                   /* +1c */
    long f20;                   /* +20 */
} REC_24;
extern REC_24 g_52ec[];

/* 0x15a-byte records at DS:70ae (as in seg09.c). */
typedef struct {
    char p00[0x14];
    PAIR f14;                   /* +14 */
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[0xca - 0x1c];
    char fca;                   /* +ca */
    char pcb[0x12c - 0xcb];
    int f12c;                   /* +12c */
    int f12e;                   /* +12e */
    char p130[0x15a - 0x130];
} REC_15A;
extern REC_15A g_70ae[];

extern int g_92e8;
extern int g_1048;
extern int g_9406;
extern int g_940a;
extern int g_914e;
extern long g_1e50;
extern long g_57a0;
extern int g_9334;
extern int g_92f0;
extern int g_9152;
extern POINT g_2398[];
extern COLORREF g_2f04[];
extern char g_91c2[];
extern char g_91d4[];
extern char g_91e6[];
extern int g_90ea;
extern int g_90ec;

POINT far pascal fn_08_29ea(POINT pt);

extern int subgame_active;      /* DS:9130 */
#define G_05A0_INT (*(int *)&g_05a0)    /* inspace.h declares DS:05a0 long */
extern int g_05a2;
extern int g_2400;
extern int g_2402;
extern int g_9150;
extern int g_88c0;
extern int g_88c4;
extern int g_88c6;
extern long g_88cc;
extern long g_240c;
extern long g_2410;
extern int g_9320;
extern char g_9eb5;
extern int g_9e49;
extern int g_91f8;
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
extern int g_9208;
extern long g_1e58;
extern int g_0594;
extern int g_0598;
extern POINT g_1050[];
void far pascal fn_08_0764(int a, int b);
int far pascal fn_08_19b0(int dx, int dy);
extern int g_9006;
extern int g_9328;
void far pascal fn_08_1e32(int type, int idx);
int far fn_09_88ba(int x);
long far abs32(long x);
void far fn_08_9028();       /* old-style: callers pass ints or a PAIR */
int far fn_10_754a(int a, int b, int c, int d);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
void far fn_08_92a0(int type, int idx);
void far fn_12_2288(int type, int idx);
void far fn_07_2080(int a, int b);
int far fn_08_35d0(long a, long b);

/* Old-style definition: 8:9b4e passes a PAIR by value, 8:99ce two ints. */
/* @addr 8:9028 */
void far fn_08_9028(i, a, kind, idx)
int i;
int a;
int kind;
int idx;
{
    if (g_52ec[i].f18.a == 0xe && (g_52ec[i].f12 == 0xf
        || kind == 0xe && g_52ec[i].f18.b == idx))
        return;
    if (g_52ec[i].f18.a == kind && g_52ec[i].f18.b == idx)
        return;
    if (kind == 2 && g_52ec[idx].f18.a == g_52ec[i].f18.a
        && g_52ec[idx].f18.b == g_52ec[i].f18.b)
        return;
    if (a == 5) {
        g_52ec[i].f14 = 0;
        if (g_52ec[i].f12 <= 5)
            g_52ec[i].f12 = 5;
        g_52ec[i].f1c.a = kind;
        g_52ec[i].f1c.b = idx;
    } else {
        g_52ec[i].f12 = g_52ec[i].f12 < a ? a : g_52ec[i].f12;
        g_52ec[i].f1c.a = kind;
        g_52ec[i].f1c.b = idx;
        if (a == 0xf)
            g_52ec[i].f0a = 0;
    }
}

/* @addr 8:90fa */
void far pascal fn_08_90fa(int i)
{
    int k;
    int j;
    int d;
    int dx;
    int dy;
    POINT pt;

    if (g_91f8 < 4 || g_9334 < 5 || g_52ec[i].f1c.a == 12)
        return;
    for (k = g_0594; k < g_0598 + g_0594; k++) {
        if (g_6098[k].f76 == -1) {
            for (j = 0; j < 2; j++) {
                g_6098[k].y1[0][j] = g_6098[k].x1[0][j] = -800;
                fn_08_0764(k, j);
            }
            if (g_70ae[g_52ec[i].f1c.b].fca) {
                pt.x = g_70ae[g_52ec[i].f1c.b].f12c;
                pt.y = g_70ae[g_52ec[i].f1c.b].f12e;
            } else {
                pt = g_1df8[g_52ec[i].f1c.a][g_52ec[i].f1c.b].f04;
            }
            d = fn_08_285a(&dx, &dy, g_1df8[2][i].f04,
                           g_1df8[g_52ec[i].f1c.a][g_52ec[i].f1c.b].f04);
            if (d < 0x118 && fn_08_19b0(dx, dy) == g_1df8[2][i].f28) {
                g_6098[k].x1[0][0] = g_1df8[2][i].f04.x + 0x30;
                g_6098[k].y1[0][0] = g_1df8[2][i].f04.y + 0x30;
                g_6098[k].count = 1;
                g_6098[k].f84 = 1;
                g_6098[k].f86 = 0;
                g_6098[k].f82 = 0;
                g_6098[k].f7a = 2;
                g_6098[k].f7c = i;
                g_6098[k].f70 = g_1050[g_1df8[2][i].f28].x * 3;
                g_6098[k].f72 = g_1050[g_1df8[2][i].f28].y * 3;
                g_6098[k].f76 = 0;
                g_6098[k].f74 = 0x28;
                g_6098[k].f80 = 0;
                fn_10_754a(3, 2, i, 1);
                return;
            }
        }
    }
}

/* @addr 8:92a0 */
void far fn_08_92a0(int type, int idx)
{
    int k;
    int j;

    g_1df8[2][idx].f18 = 1;
    fn_10_754a(0x16, 2, idx, 1);
    g_1e58 += 400;
    PatBlt(g_13dc, g_1df8[2][idx].f00.x - 1, g_1df8[2][idx].f00.y - 1,
           g_1df8[2][idx].f22 + 2, g_1df8[2][idx].f22 + 2, BLACKNESS);
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
            g_1e90[k].f02 = 0xe;
            g_1e90[k].f0a = 7;
            g_1e90[k].f0c = 2;
            if (k > g_9434)
                g_9434 = k;
            g_1e90[k].f0e = g_52ec[idx].f12;
            g_9430++;
            if (k > g_9208)
                g_1e90[k].f04 = 2;
            else
                g_1e90[k].f04 = 1;
            g_1e90[k].f06 = 2;
            g_1e90[k].f08 = idx;
            g_5224[k] = g_1df8[2][idx].f04;
            g_5170[k] = g_1df8[2][idx].f00;
            return;
        }
    }
}

/* @addr 8:95f2 */
int far fn_08_95f2(int unused, int i, int v)
{
    if (v > 0)
        v = v < 0x3c ? 0x3c : v;
    else
        v = -v;
    g_1df8[2][i].f1e += v;
    g_57a0 = g_1e50 + 500;
    if (g_1df8[2][i].f1e > 0x50)
        g_52ec[i].f14 = 1;
    g_52ec[i].f20 = g_1e50 + 0x15e;
    if (g_1df8[2][i].f1e > (g_9334 + 0x1a) * 5) {
        fn_08_92a0(2, i);
        return 1;
    }
    return 0;
}

/* @addr 8:9464 */
void far fn_08_9464(void)
{
    int i;
    int j;
    int unused;

    if (g_92e8 != 0 || g_1048 == 0)
        return;
    for (i = 0; i < g_9406; i++) {
        if (g_1df8[0][i].f18 == 0) {
            for (j = i; j < g_92f0; j += g_9406) {
                if (g_1df8[2][j].f18 != 0) {
                    fn_10_754a(0x18, 0, i, 1);
                    g_52ec[j].d00 = 0xff10ffd0L;
                    g_1df8[2][j].f0c = 0x46;
                    g_1df8[2][j].f0e = -0x82;
                    g_1df8[2][j].f18 = 0;
                    g_1df8[2][j].f2e = 0;
                    g_52ec[j].f10 = -1;
                    g_1df8[2][j].f1e = 0;
                    g_52ec[j].f08 = 0;
                    g_52ec[j].f18.a = 0;
                    g_52ec[j].f18.b = i;
                    g_52ec[j].f14 = 0;
                    g_52ec[j].f1c.a = 0;
                    g_52ec[j].f1c.b = i;
                    g_52ec[j].f12 = 0;
                    j = g_92f0;
                    break;
                }
            }
        }
    }
    fn_07_2080(2, -1);
}

/* @addr 8:9564 */
void far fn_08_9564(void)
{
    int i;
    int j;

    if (g_92e8 == 0 && g_1048 != 0) {
        for (i = 0; i < g_9406; i++) {
            if (g_1df8[0][i].f18 == 0 && g_1df8[0][i].f1a != 0) {
                for (j = i; j < g_940a; j += g_9406) {
                    if (g_1df8[2][j].f18 != 0) {
                        fn_10_754a(0x17, 0, i, 1);
                        g_914e = 1;
                        return;
                    }
                }
            }
        }
    }
}

/* @addr 8:9ab8 */
void far fn_08_9ab8(void)
{
    int i;
    int d;
    int y;
    int x;

    for (i = 0; i < g_940a; i++) {
        if (g_1df8[2][i].f18 == 0 && g_52ec[i].f1c.a == 0xc
            && g_1df8[2][i].f1a == 0) {
            d = fn_08_285a(&y, &x, g_1df8[2][i].f04,
                           g_1df8[12][g_52ec[i].f1c.b / 2].f04);
            if (d < 0xaa)
                fn_12_2288(2, i);
        }
    }
}

extern struct { char c0, c1; char rest[0x21]; } g_57b2[];   /* 0x23-byte records [inferred] */

/* @addr 8:99ce */
void far fn_08_99ce(int a, int b, int kind, int idx)
{
    int i;
    int k;
    int x;

    if (a == 0 && (kind == 9 || kind == 0xe)) {
        g_57b2[b].c0 = kind;
        g_57b2[b].c1 = idx;
    }
    for (i = 0; i < g_940a; i++) {
        if (g_1df8[2][i].f18 == 0 && (kind == 0xe || kind == 2)) {
            x = idx;
            k = kind;
            if ((k == 0xe || k == 2 && g_52ec[x].f12 == 0xf
                 && !(g_52ec[x].f18.a == g_52ec[i].f18.a
                      && g_52ec[x].f18.b == g_52ec[i].f18.b))
                && g_52ec[i].f18.a == a && g_52ec[i].f18.b == b
                && !(g_52ec[i].f18.a == k && g_52ec[i].f18.b == x)
                && g_52ec[i].f12 != 0xf) {
                fn_08_9028(i, 0xf, k, x);
                break;
            }
        }
    }
}

/* @addr 8:9b4e */
void far fn_08_9b4e(void)
{
    int i;

    for (i = 0; i < g_940a; i++) {
        if (g_1df8[2][i].f18 == 0 && g_52ec[i].f18.a == 0xe
            && g_52ec[i].f12 != 0xf) {
            if (g_70ae[g_52ec[i].f18.b].f1a == 1)
                fn_08_9028(i, 10, g_70ae[g_52ec[i].f18.b].f14);
            else
                g_52ec[i].f12 = 5;
        }
    }
}

/* Set up the 5x5 grid of group a around object (type, idx), with a random
 * motion formula per cell [inferred]. */
/* @addr 8:9694 */
void far fn_08_9694(int a, int type, int idx)
{
    int i;
    int j;
    POINT p;

    if (type == 0x1e) {
        p.x = g_6098[idx].f70;
        p.y = g_6098[idx].f72;
    } else {
        p.x = g_1df8[type][idx].f0c;
        p.y = g_1df8[type][idx].f0e;
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            g_2414[a][i][j].s.x = (j << 4) + g_5224[a].x + 8;
            g_2414[a][i][j].s.y = (i << 4) + g_5224[a].y + 8;
            g_2414[a][i][j].f0c = (j - 2) * 8 + p.x;
            g_2414[a][i][j].f0e = (2 - i) * 7 + p.y;
            g_2414[a][i][j].f10 = (i + 5) * 2 - j * 7;
            g_2414[a][i][j].f12 = (-1 - j) * 4 + i * 6;
            type = rand() % 32;
            switch (type % 8) {
            case 0:
                g_2414[a][i][j].f10 = (i + 5) * 2 - j * 7;
                g_2414[a][i][j].f12 = (-1 - j) * 4 + i * 6;
                break;
            case 1:
                g_2414[a][i][j].f10 = (2 - j) * 7 + (2 - i) * (i - 2) * 2;
                g_2414[a][i][j].f12 = (2 - j) * (j - 2) * 4 + (i - 2) * 6;
                break;
            case 2:
                g_2414[a][i][j].f10 = (2 - j) * 7 + (2 - i) * (i - 2) * 2;
                g_2414[a][i][j].f12 = (j - 2) * (j - 2) * 4 + (2 - i) * 6;
                break;
            case 3:
                g_2414[a][i][j].f10 = -(2 - i) * 2 + (2 - j) * (5 - i) * 7;
                g_2414[a][i][j].f12 = -(2 - i) * (j - 5) * 6 + (j - 2) * 4;
                break;
            case 4:
                g_2414[a][i][j].f10 = (2 - j) * (i - 2);
                g_2414[a][i][j].f12 = (j - 2) * (i - 2) * 7 + (2 - j) * (2 - i) * 2;
                break;
            case 5:
                g_2414[a][i][j].f10 = ((2 - i) * (2 - i) * (i - 2) + j - 2) * 6;
                g_2414[a][i][j].f12 = (2 - j) * (j - 2) * 2 + (i - 2) * 5;
                break;
            case 6:
                g_2414[a][i][j].f10 = ((i - 2) * (i - 2) * (2 - i) + (j - 2) * (j - 2) * (j - 2)) * 6;
                g_2414[a][i][j].f12 = (2 - j) * (j - 2) * 2 + (i - 2) * (i - 2) * i * 7;
                break;
            case 7:
                g_2414[a][i][j].f10 = j * 7 - i * 3 - 8;
                g_2414[a][i][j].f12 = (i - 2) * (i - 2) * (i - 2) * 6;
                break;
            }
        }
    }
}
