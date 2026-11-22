/* INSPACE.EXE segment 8 (selector 1038), /G3 parts.
 * 8:3688..81f8 was compiled with /G2: see seg08b.c. */
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
    int z[2][6];    /* +60 */
    int count;      /* +78 */
    char rest[0x1a];
} REC_94;
extern REC_94 g_6098[];

/* 0x1c-byte records at DS:2414, [?][5][5] [inferred]. */
typedef struct {
    POINT p;        /* +0 */
    POINT q;        /* +4 */
    POINT r;        /* +8 */
    char pad[0xc];  /* +c */
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
    char p00[4];
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
    char p22[0x2e - 0x22];
    char f2e;                   /* +2e */
    char p2f[0x70 - 0x2f];
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
    char p1c[0x15a - 0x1c];
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
int far fn_09_88ba(int x);
long far abs32(long x);
void far fn_08_9028();       /* old-style: callers pass ints or a PAIR */
int far fn_10_754a(int a, int b, int c, int d);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
void far fn_08_92a0(int type, int idx);
void far fn_12_2288(int type, int idx);
void far fn_07_2080(int a, int b);
long far fn_08_35d0(long a, long b);

/* @addr 8:0764 */
void far pascal fn_08_0764(int a, int b)
{
    int i;
    POINT pt;

    for (i = 0; i < g_6098[a].count; i++) {
        pt.x = g_6098[a].x1[i][b];
        pt.y = g_6098[a].y1[i][b];
        pt = fn_08_29ea(pt);
        g_6098[a].x0[i][b] = pt.x;
        g_6098[a].y0[i][b] = pt.y;
    }
}

/* @addr 8:07d2 */
void far pascal fn_08_07d2(int a, int b, int c)
{
    POINT u;
    POINT t;

    t = fn_08_29ea(g_2414[a][b][c].s);
    g_2414[a][b][c].p.x = t.x;
    g_2414[a][b][c].p.y = t.y;
    g_2414[a][b][c].q.x = g_2414[a][b][c].r.x;
    g_2414[a][b][c].q.y = g_2414[a][b][c].r.y;
    g_2414[a][b][c].r.x = g_2414[a][b][c].p.x;
    g_2414[a][b][c].r.y = g_2414[a][b][c].p.y;
}

/* @addr 8:083e */
void far pascal fn_08_083e(int a, int b)
{
    POINT u;
    POINT t;

    t = fn_08_29ea(g_5b28[a][b].s);
    g_5b28[a][b].p.x = t.x;
    g_5b28[a][b].p.y = t.y;
    g_5b28[a][b].q.x = g_5b28[a][b].r.x;
    g_5b28[a][b].q.y = g_5b28[a][b].r.y;
    g_5b28[a][b].r.x = g_5b28[a][b].p.x;
    g_5b28[a][b].r.y = g_5b28[a][b].p.y;
}

/* @addr 8:124a */
void far pascal fn_08_124a(int i)
{
    g_58bc[i].b.x = g_58bc[i].a.x;
    g_58bc[i].b.y = g_58bc[i].a.y;
    g_58bc[i].a = fn_08_29ea(g_58bc[i].c);
}

/* Clamp an object's velocity to [-v, v] [inferred]. */
/* @addr 8:1cbe */
void far pascal fn_08_1cbe(OBJREF r, int v)
{
    int type;
    int idx;

    type = r.type;
    idx = r.idx;
    if (g_1df8[type][idx].f0c > v)
        g_1df8[type][idx].f0c = v;
    if (g_1df8[type][idx].f0e > v)
        g_1df8[type][idx].f0e = v;
    if (g_1df8[type][idx].f0c < -v)
        g_1df8[type][idx].f0c = -v;
    if (g_1df8[type][idx].f0e < -v)
        g_1df8[type][idx].f0e = -v;
}

/* Slow an object down by one unit per axis once |vx|+|vy| reaches v
 * [inferred: friction]. */
/* @addr 8:1d54 */
void far pascal fn_08_1d54(OBJREF r, int v)
{
    int sum;
    int sx;
    int sy;
    int type;
    int idx;

    type = r.type;
    idx = r.idx;
    if (g_1df8[type][idx].f0c > 0) {
        sum = g_1df8[type][idx].f0c;
        sx = 1;
    } else {
        sum = -g_1df8[type][idx].f0c;
        sx = -1;
    }
    if (g_1df8[type][idx].f0e > 0) {
        sum += g_1df8[type][idx].f0e;
        sy = 1;
    } else {
        sum -= g_1df8[type][idx].f0e;
        sy = -1;
    }
    if (sum >= v) {
        if (g_1df8[type][idx].f0c != 0)
            g_1df8[type][idx].f0c -= sx;
        if (g_1df8[type][idx].f0e != 0)
            g_1df8[type][idx].f0e -= sy;
    }
}

/* Steer object (type, idx) toward the centre of object (type2, idx2)
 * [inferred]. */
/* @addr 8:348e */
void far fn_08_348e(int type, int idx, int type2, int idx2, int speed)
{
    POINT p1;
    POINT p2;
    int dx;
    int dy;
    int vx;
    int vy;
    int d;

    p1 = fn_08_29ea(g_1df8[type][idx].f04);
    p2 = fn_08_29ea(g_1df8[type2][idx2].f04);
    p1.x <<= g_9150;
    p1.y <<= g_9150;
    p2.x <<= g_9150;
    p2.y <<= g_9150;
    p2.x += g_1df8[type2][idx2].f20 / 2;
    p2.y += g_1df8[type2][idx2].f20 / 2;
    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    vx = g_1df8[type2][idx2].f0c;
    vy = g_1df8[type2][idx2].f0e;
    d = (int)fn_08_35d0(dx, dy);
    vx += (long)d * speed / dx;
    vy += (long)dy * speed / d;
    g_1df8[type][idx].f0c = vx;
    g_1df8[type][idx].f0e = vy;
}

/* Random positions and colours for g_9152 entries [inferred: stars]. */
/* @addr 8:190e */
void far fn_08_190e(void)
{
    int i;

    for (i = 0; i < g_9152; i++) {
        g_2398[i].x = rand() % g_90ea;
        g_2398[i].y = rand() % g_90ec;
        g_2f04[i] = PALETTERGB(255, rand() % 255, rand() % 255);
        g_91d4[i] = rand() % 3 + 1;
        g_91e6[i] = rand() % 40;
        g_91c2[i] = 1;
    }
}

/* World point to screen point [inferred]: relative to the view origin
 * DS:240c/2410, wrapped the short way round the map, scaled down by
 * g_9150; in the sub-game a linear map (inverse of 8:2bbe). */
/* @addr 8:29ea */
POINT far pascal fn_08_29ea(POINT pt)
{
    POINT r;
    long u1;
    long lx;
    long ly;
    int u2[1];

    lx = pt.x;
    ly = pt.y;
    if (subgame_active == 0) {
        r.x = (int)((lx - g_240c) >> g_9150);
        if (fn_09_88ba((int)lx - (g_90ea << (g_9150 - 1)) - (int)g_240c) > G_05A0_INT * 4
            && (g_9320 != 6 || g_9eb5 == 1))
            r.x = (int)(((0 > r.x ? (long)pt.x + G_05A0_INT * 8 : (long)pt.x - G_05A0_INT * 8)
                         - g_240c) >> g_9150);
        r.y = (int)((ly - g_2410) >> g_9150);
        if (abs32(ly - (g_90ec << (g_9150 - 1)) - g_2410) > g_05a2 * 4
            && (g_9320 != 6 || g_9eb5 == 1))
            r.y = (int)(((0 > r.y ? (long)pt.y + g_05a2 * 8 : (long)pt.y - g_05a2 * 8)
                         - g_2410) >> g_9150);
    } else {
        r.x = (int)(pt.x * (long)g_88c0 / g_88cc) + g_88c4;
        r.y = (int)(pt.y * (long)g_88c0 / g_88cc) + g_88c6;
    }
    return r;
}

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

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_08_92a0(int type, int idx)
{
    g_914e = type + idx;
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

/* Integer square root, one Newton step from guess g [inferred]. The loop
 * after the return is dead code in the original. */
/* near-match 47%: 8:1290 (the dead loop's update compiles to an add-to-memory;
 * the original adds in registers and stores) */
long far pascal fn_08_1290(long n, long g)
{
    int i;
    long a;
    long b;

    if (g < 3)
        g = 3;
    return (n / g + g) >> 1;
    do {
        if (g < 3)
            g = 3;
        g = (n - g * g) / (2 * g) + g;
        i++;
    } while (i < 1);
}

/* Distance approximation: start from max + min/2, one Newton step of the
 * square root of a*a + b*b [inferred]. */
/* near-match 94%: 8:35d0 (the original returns 1 as `mov ax,1` with no
 * dx set; every phrasing tried here adds a cwd) */
long far fn_08_35d0(long a, long b)
{
    long aa;
    long ab;
    long g;

    ab = abs32(b);
    aa = abs32(a);
    if (aa < ab)
        g = (aa >> 1) + ab;
    else
        g = (ab >> 1) + aa;
    return g ? ((b * b + a * a) / g + g) >> 1 : 1;
}

/* Screen point to world point [inferred]: scaled by g_9150 and offset by
 * the view origin, wrapped to the map; in the sub-game a linear map. */
/* @addr 8:2bbe */
POINT far pascal fn_08_2bbe(POINT pt)
{
    POINT r;
    int oy;
    int ox;
    long lx;
    long ly;

    if (subgame_active == 0) {
        oy = g_2402;
        ox = g_2400;
        if (ox < 0)
            ox += G_05A0_INT * 8;
        if (oy < 0)
            oy += g_05a2 * 8;
        lx = (long)ox + (pt.x << g_9150);
        ly = (long)oy + (pt.y << g_9150);
        if (lx > G_05A0_INT * 8)
            lx -= G_05A0_INT * 8;
        if (ly > g_05a2 * 8)
            ly -= g_05a2 * 8;
        r.x = (int)lx;
        r.y = (int)ly;
        return r;
    }
    r.x = (int)((pt.x - g_88c4) * g_88cc / g_88c0);
    r.y = (int)((pt.y - g_88c6) * g_88cc / g_88c0);
    return r;
}
