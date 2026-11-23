/* INSPACE.EXE segment 8 (selector 1038), /G3 parts.
 * 8:3688..81f8 was compiled with /G2: see seg08b.c; 8:8256 to the end is
 * another source file: see seg08c.c. */
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
    char p24[0x2e - 0x24];
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
extern int g_9e49;
extern int g_9324;
extern int g_9646;
extern int g_9154;
extern int g_9156;
extern int g_238c;
extern int g_2390;
extern int g_2392;
extern int g_2394;
extern int g_2396;
extern int g_951a;
extern RECT g_1e5c;
extern char g_507c[];
extern char g_50e0[];
extern int g_9146;
/* 0x22-byte records at DS:915c [inferred: animated map objects]. */
typedef struct {
    POINT f00;                  /* +00: world position */
    POINT f04;                  /* +04: screen position */
    char p08[4];
    HDC f0c;                    /* +0c: image */
    HDC f0e;                    /* +0e: mask */
    char p10[0x1a - 0x10];
    int f1a;                    /* +1a */
    char p1c[0x22 - 0x1c];
} REC_22;
extern REC_22 g_915c[];
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

/* Direction 0..15 of the vector (dx, dy) from the slope dy/dx
 * [inferred]. */
/* @addr 8:19b0 */
int far pascal fn_08_19b0(int dx, int dy)
{
    long d;
    long r;
    long ldx;
    long ldy;
    int dir;

    ldy = dy;
    ldx = dx;
    if (abs32(ldx) > 0)
        d = ldx;
    else
        d = 1;
    r = ldy * 100 / d;
    if (r > 500 || r < -500) {
        if (ldy > 0)
            dir = 8;
        else
            dir = 0;
    }
    if (r < 501 && r > 154) {
        if (ldy > 0)
            dir = 7;
        else
            dir = 15;
    } else if (r < 155 && r > 65) {
        if (ldy > 0)
            dir = 6;
        else
            dir = 14;
    } else if (r < 66 && r > 19) {
        if (ldy > 0)
            dir = 5;
        else
            dir = 13;
    } else if (r < 20 && r > -20) {
        if (ldx > 0)
            dir = 4;
        else
            dir = 12;
    } else if (r < -19 && r > -65) {
        if (ldy > 0)
            dir = 11;
        else
            dir = 3;
    } else if (r < -64 && r > -154) {
        if (ldy > 0)
            dir = 10;
        else
            dir = 2;
    } else if (r < -153 && r > -501) {
        if (ldy > 0)
            dir = 9;
        else
            dir = 1;
    }
    return dir;
}

/* r packs (type << 8) | index. Move an object by n times its velocity,
 * wrapping round the map
 * [inferred]. */
/* @addr 8:1b54 */
void far pascal fn_08_1b54(WORD r, int n)
{
    int saved;
    int type;
    int idx;

    type = HIBYTE(r);
    idx = LOBYTE(r);
    if (type == 14 && g_1df8[14][idx].f54 != 0 && g_92e8 != 0 && g_9e49 == 10)
        return;
    if (g_1df8[type][idx].f32 != -1 && type != 10)
        fn_08_1e32(type, idx);
    if (type == g_9328) {
        saved = g_9006;
        g_9006 = 10;
    }
    if (n == 1) {
        g_1df8[type][idx].f04.x += g_1df8[type][idx].f0c;
        g_1df8[type][idx].f04.y += g_1df8[type][idx].f0e;
    } else {
        g_1df8[type][idx].f04.x += g_1df8[type][idx].f0c * n;
        g_1df8[type][idx].f04.y += g_1df8[type][idx].f0e * n;
    }
    if (subgame_active)
        return;
    if (g_1df8[type][idx].f04.x > G_05A0_INT * 8)
        g_1df8[type][idx].f04.x = 0;
    if (g_1df8[type][idx].f04.x < 0)
        g_1df8[type][idx].f04.x = G_05A0_INT * 8;
    if (g_1df8[type][idx].f04.y > g_05a2 * 8)
        g_1df8[type][idx].f04.y = 0;
    if (g_1df8[type][idx].f04.y < 0)
        g_1df8[type][idx].f04.y = g_05a2 * 8;
    if (type == g_9328)
        g_9006 = saved;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far pascal fn_08_1e32(int type, int idx)
{
    g_9006 = type + idx;
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
    d = fn_08_35d0(dx, dy);
    vx += (long)dx * speed / d;
    vy += (long)dy * speed / d;
    g_1df8[type][idx].f0c = vx;
    g_1df8[type][idx].f0e = vy;
}

/* Redraw map object i, masked when something overlaps it [inferred]. */
/* @addr 8:08a6 */
void far pascal fn_08_08a6(int i)
{
    RECT r3;
    RECT r1;
    RECT r2;
    int hit;
    int mine;
    int k;
    int size;

    mine = hit = 0;
    if (g_915c[i].f1a < 2) {
        g_915c[i].f04 = fn_08_29ea(g_915c[i].f00);
        return;
    }
    if (subgame_active == 0)
        size = (32 << g_9156) >> 1;
    else
        size = ((g_9156 << 6) + 32) / 3;
    SetRect(&r1, g_915c[i].f04.x, g_915c[i].f04.y,
            g_915c[i].f04.x + size, g_915c[i].f04.y + size);
    for (k = 0; k < g_9146; k++) {
        SetRect(&r2, g_1df8[g_507c[k]][g_50e0[k]].f00.x, g_1df8[g_507c[k]][g_50e0[k]].f00.y,
                g_1df8[g_507c[k]][g_50e0[k]].f22 + g_1df8[g_507c[k]][g_50e0[k]].f00.x,
                g_1df8[g_507c[k]][g_50e0[k]].f22 + g_1df8[g_507c[k]][g_50e0[k]].f00.y);
        if (IntersectRect(&r3, &r2, &r1)) {
            hit = 1;
            if (g_507c[k] == g_9324 && g_50e0[k] == g_9646)
                mine = 1;
        }
    }
    if (hit) {
        if (g_915c[i].f04.x > -40 && g_915c[i].f04.x < g_90ea + 40
            && g_915c[i].f04.y > -40 && g_915c[i].f04.y < g_90ec + 40)
            BitBlt(g_13dc, g_915c[i].f04.x, g_915c[i].f04.y, size, size,
                   g_915c[i].f0e, 0, 0, SRCAND);
        g_915c[i].f04 = fn_08_29ea(g_915c[i].f00);
        if (g_915c[i].f04.x > -40 && g_915c[i].f04.x < g_90ea + 40
            && g_915c[i].f04.y > -40 && g_915c[i].f04.y < g_90ec + 40) {
            BitBlt(g_13dc, g_915c[i].f04.x, g_915c[i].f04.y, size, size,
                   g_915c[i].f0e, 0, 0, SRCAND);
            BitBlt(g_13dc, g_915c[i].f04.x, g_915c[i].f04.y, size, size,
                   g_915c[i].f0c, g_915c[i].f1a / 2 % 5 * size, 0, SRCPAINT);
        }
    } else {
        if (g_915c[i].f04.x > -40 && g_915c[i].f04.x < g_90ea + 40
            && g_915c[i].f04.y > -40 && g_915c[i].f04.y < g_90ec + 40)
            PatBlt(g_13dc, g_915c[i].f04.x, g_915c[i].f04.y, size, size, BLACKNESS);
        g_915c[i].f04 = fn_08_29ea(g_915c[i].f00);
        if (g_915c[i].f04.x > -40 && g_915c[i].f04.x < g_90ea + 40
            && g_915c[i].f04.y > -40 && g_915c[i].f04.y < g_90ec + 40)
            BitBlt(g_13dc, g_915c[i].f04.x, g_915c[i].f04.y, size, size,
                   g_915c[i].f0c, g_915c[i].f1a / 2 % 5 * size, 0, SRCCOPY);
    }
}

/* Move the stars against the ship's motion, wrapping round the view
 * with a new random position and colour [inferred]. */
/* @addr 8:1320 */
void far pascal fn_08_1320(int still)
{
    int i;

    if (g_1df8[g_9324][g_9646].f18 == 1) {
        g_1df8[g_9324][g_9646].f0c = 0;
        g_1df8[g_9324][g_9646].f0e = 0;
    }
    if (still == 0 && g_238c == 0 && g_1df8[g_9324][g_9646].f0c == 0
        && g_1df8[g_9324][g_9646].f0e == 0)
        return;
    for (i = 0; i < g_9152; i++) {
        if (g_91c2[i])
            PatBlt(g_13dc, g_2398[i].x, g_2398[i].y, 3, 3, BLACKNESS);
        if (still == 0) {
            if (g_951a) {
                g_2398[i].x -= (g_2394 << g_9156) >> 2;
                g_2398[i].y -= (g_2396 << g_9156) >> 2;
            } else {
                g_2398[i].x -= (g_1df8[g_9324][g_9646].f0c << g_9156) >> 2;
                g_2398[i].y -= (g_1df8[g_9324][g_9646].f0e << g_9156) >> 2;
            }
            if (g_238c) {
                g_2398[i].x += (g_2390 << g_9156) >> 2;
                g_2398[i].y += (g_2392 << g_9156) >> 2;
            }
            if (g_2398[i].x < 0) {
                g_2398[i].x = g_90ea;
                g_2398[i].y = rand() % g_90ec;
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            } else if (g_2398[i].x > g_90ea) {
                g_2398[i].x = 0;
                g_2398[i].y = rand() % g_90ec;
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            }
            if (g_2398[i].y < 0) {
                g_2398[i].y = g_90ec;
                g_2398[i].x = rand() % g_90ea;
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            } else if (g_2398[i].y > g_90ec) {
                g_2398[i].y = 0;
                g_2398[i].x = rand() % g_90ea;
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            }
        }
        if (g_9154 == g_9152) {
            if (!PtInRect(&g_1e5c, g_2398[i])) {
                PatBlt(g_13dc, g_2398[i].x, g_2398[i].y, 3, 3, WHITENESS);
                g_91c2[i] = 1;
            } else {
                g_91c2[i] = 0;
            }
        }
    }
    if (g_9154 != g_9152)
        g_9152 = g_9154;
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

/* Distance from a to b on the wrapping map (in 8-unit cells), with the
 * offsets stored to *p and *q [inferred]. */
/* @addr 8:285a */
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b)
{
    int dy;
    int dx;
    int ty;
    int tx;
    long g;
    long adx;
    long ady;

    if (subgame_active == 0) {
        b.y >>= 3;
        a.y >>= 3;
        b.x >>= 3;
        a.x >>= 3;
        dx = b.x - a.x;
        if (fn_09_88ba(dx) > G_05A0_INT >> 1) {
            tx = 0 > dx ? b.x + G_05A0_INT : b.x - G_05A0_INT;
            dx = tx - a.x;
        }
        dy = b.y - a.y;
        if (fn_09_88ba(dy) > g_05a2 >> 1) {
            ty = 0 > dy ? b.y + g_05a2 : b.y - g_05a2;
            dy = ty - a.y;
        }
    } else {
        b = fn_08_29ea(b);
        a = fn_08_29ea(a);
        dx = b.x - a.x;
        dy = b.y - a.y;
    }
    ady = fn_09_88ba(dy);
    adx = fn_09_88ba(dx);
    if (adx < ady)
        g = (adx >> 1) + ady;
    else
        g = (ady >> 1) + adx;
    *p = dx;
    *q = dy;
    return g ? ((ady * ady + adx * adx) / g + g) >> 1 : 1;
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
/* Returns int although the expression is long (the result is truncated). */
/* @addr 8:35d0 */
int far fn_08_35d0(long a, long b)
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
