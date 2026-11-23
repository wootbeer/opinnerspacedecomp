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
    POINT f08;                  /* +08 */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    char p14[4];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[2];
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    char p26[0x28 - 0x26];
    int f28;                    /* +28: direction */
    char p2a[0x2e - 0x2a];
    char f2e;                   /* +2e */
    char p2f;
    char f30;                   /* +30: tether index */
    char p31;
    int f32;                    /* +32: towed object type */
    int f34;                    /* +34: towed object index */
    int f36;                    /* +36 */
    char p38[0x3a - 0x38];
    HDC f3a;                    /* +3a */
    HDC f3c;                    /* +3c */
    char p3e[0x44 - 0x3e];
    int f44;                    /* +44: mass [inferred] */
    char p46[0x50 - 0x46];
    char f50;                   /* +50 */
    char p51[0x53 - 0x51];
    char f53;                   /* +53 */
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
    int f00;                    /* +00 */
    char p02[0x14 - 0x02];
    PAIR f14;                   /* +14 */
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[0x30 - 0x1c];
    int f30;                    /* +30: class */
    char p32[0x40 - 0x32];
    char f40;                   /* +40 */
    char p41[0x8e - 0x41];
    char f8e;                   /* +8e */
    char f8f;                   /* +8f */
    char p90[0xb8 - 0x90];
    int fb8;                    /* +b8 */
    char pba[0xce - 0xba];
    char fce;                   /* +ce */
    char pcf[0x138 - 0xcf];
    long f138;                  /* +138 */
    char p13c[0x15a - 0x13c];
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
/* 0x20-byte tether records at DS:65cc [inferred] (seg09.c: REC_20). */
typedef struct {
    int f00;                    /* +00 */
    char p02[2];
    int f04;                    /* +04: towed object type */
    int f06;                    /* +06: towed object index */
    char p08[2];
    int f0a;                    /* +0a: 2 = heavy */
    char p0c[2];
    int f0e;                    /* +0e: spin direction */
    POINT f10;                  /* +10: screen end, this frame */
    POINT f14;                  /* +14: screen end, last frame */
    POINT f18;                  /* +18: towed end, this frame */
    POINT f1c;                  /* +1c: towed end, last frame */
} REC_20;
extern REC_20 g_65cc[];
/* Second view of the 0x15a-byte records at their lowest base, DS:7092. */
typedef struct {
    int f00;                    /* +00 */
    char p02[0xe0 - 0x02];
    char fe0;                   /* +e0 */
    char pe1[0x15a - 0xe1];
} REC_15A_LO;
extern REC_15A_LO g_7092[];
extern int g_915a;
extern DWORD g_1e68;
extern int g_17bc;
extern int g_17be;
extern int g_8ff2;
extern HPEN g_3b44[];
void far fn_12_7256(HDC dc, POINT a, POINT b);
void far fn_11_a234(int type, int idx, int t2, int i2);
/* 0x7c-, 0x41-, 0x2c- and 0xad-byte records (see seg03.c/seg04.c). */
typedef struct { int f00; char p02[0x7c - 0x02]; } REC_7C;
typedef struct { char p00[0x1a]; char f1a; char p1b[0x2c - 0x1b]; } REC_2C;
#pragma pack(1)
typedef struct { char p00[0x21]; int f21; char p23[0x41 - 0x23]; } REC_41;
typedef struct { char p00[0x24]; int f24; char p26[0xad - 0x26]; } REC_AD;
#pragma pack()
extern REC_7C far *g_6e24;
extern REC_41 far *g_6e20;
extern REC_2C far *g_6e1c;
extern REC_AD g_96ea[];
extern int g_4ed8[];
extern int g_95a6;
extern int g_92e4;
extern int g_9316;
extern int g_3a38[];
extern POINT g_1050[];
extern POINT g_066e[];
void far fn_14_3eda(void);
void far fn_14_4074(void);
int far fn_04_5d9c(int a, int i);
void far fn_03_06ec(int n, int kind, int target, int d);
HBITMAP far fn_10_7370(int a, int b, int c, int d, int e, int f, int g);
HBITMAP far fn_10_6ec6(HBITMAP b);
extern int g_238e;
extern int g_952e;
extern int g_9e47;
extern int g_913a;
extern int g_913c;
extern HBRUSH g_5ea8;
extern int g_238e;
extern int g_952e;
extern int g_9e47;
extern int g_913a;
extern int g_913c;
extern HBRUSH g_5ea8;
extern int g_2404;
extern int g_2406;
extern DWORD g_2408;
extern RECT g_23e0[4];          /* view pieces split at the map wrap [inferred] */
extern int g_9158;              /* number of pieces in g_23e0 */
extern POINT g_6b50;
extern long g_1e80;
extern long g_1e84;
extern int g_9134;
extern int g_9378;
extern int flow_interactive;    /* DS:95bc */
extern int g_0a76;
extern HWND g_0a7c;
void far fn_11_aece(void);
void far fn_07_11cc(void);
void far fn_07_1208(void);
void far fn_10_744c(int a);
extern RECT g_1e5c;
extern char g_507c[];
extern char g_50e0[];
extern int g_9146;
/* 0x22-byte records at DS:915c [inferred: animated map objects]. */
typedef struct {
    POINT f00;                  /* +00: world position */
    POINT f04;                  /* +04: screen position */
    POINT f08;                  /* +08 */
    HDC f0c;                    /* +0c: image */
    HDC f0e;                    /* +0e: mask */
    HBITMAP f10;                /* +10: image bitmap */
    HBITMAP f12;                /* +12: mask bitmap */
    HBITMAP f14;                /* +14: old bitmap of f0c */
    HBITMAP f16;                /* +16: old bitmap of f0e */
    HPALETTE f18;               /* +18: old palette of f0c */
    int f1a;                    /* +1a */
    int f1c;                    /* +1c */
    int f1e;                    /* +1e: size */
    char p20[0x22 - 0x20];
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
long far pascal fn_08_1290(long n, long g);

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

/* Draw object ref (type << 8 | idx) with sprite DC dc: erase the uncovered
 * part of the old position, then blit [inferred]. mode 4 only moves the
 * object; 6 inverts, 7 plots a dot. Returns 0 for hidden objects.
 * The gotos reproduce the shared return blocks at the end. */
/* @addr 8:0b76 */
int far pascal fn_08_0b76(WORD ref, int mode, HDC dc, int c)
{
    int type;
    int idx;
    int u8;
    DWORD rop;
    POINT d;
    int u12;
    int u14;
    int draw;

    draw = 1;
    type = HIBYTE(ref);
    idx = LOBYTE(ref);
    if (g_1df8[type][idx].f1a == 0 && type != 7 && mode != 4 && mode != 5
        && g_1df8[type][idx].f32 == -1)
        goto hidden;
    if (type != g_9324 || idx != g_9646 || g_951a != 0 || g_238e != 0) {
        if (type != g_9324 || idx != g_9646 || g_951a != 0) {
            g_1df8[type][idx].f08.x = g_1df8[type][idx].f00.x;
            g_1df8[type][idx].f08.y = g_1df8[type][idx].f00.y;
            g_1df8[type][idx].f00 = fn_08_29ea(g_1df8[type][idx].f04);
        } else if (g_238c == 0) {
            g_1df8[type][idx].f00.x = g_90ea / 2;
            g_1df8[type][idx].f00.y = g_90ec / 2;
            g_238e = 0;
        }
        if (mode == 4)
            goto done;
        if (mode == 5 && g_1df8[type][idx].f1a == 0)
            goto done;
        g_1df8[type][idx].f3a = dc;
        if (g_1df8[type][idx].f2e != 0) {
            dc = g_1df8[type][idx].f3c;
            g_1df8[type][idx].f10 = g_1df8[type][idx].f24;
            g_1df8[type][idx].f12 = g_1df8[type][idx].f24;
            if (g_1df8[type][idx].f2e <= -1)
                draw = 0;
        }
        if (g_9e49 == 3 || g_9e49 == 6 && g_9e47 == 15) {
            if (type == g_9324 && idx == g_952e || type == 7) {
                dc = g_1df8[type][idx].f3c;
                g_1df8[type][idx].f10 = g_1df8[type][idx].f24;
                g_1df8[type][idx].f12 = g_1df8[type][idx].f24;
            }
        }
        if (c != 0)
            rop = 0xc000ca;
        else
            rop = SRCCOPY;
        if (mode == 6 && draw) {
            BitBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
                   g_1df8[type][idx].f22, g_1df8[type][idx].f22, dc,
                   g_1df8[type][idx].f10, g_1df8[type][idx].f12, 0xee0086);
        } else if (mode == 7) {
            PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
                   3, 3, WHITENESS);
        } else if (draw) {
            d.x = g_1df8[type][idx].f00.x - g_1df8[type][idx].f08.x;
            d.y = g_1df8[type][idx].f00.y - g_1df8[type][idx].f08.y;
            if (rop == 0xc000ca) {
                if (d.x < 0)
                    d.x -= 2;
                if (d.y < 0)
                    d.y -= 2;
            }
            if (g_1df8[type][idx].f24 < fn_09_88ba(d.x)
                || g_1df8[type][idx].f24 < fn_09_88ba(d.y)) {
                if (g_1df8[type][idx].f22 > fn_09_88ba(d.x)
                    && g_1df8[type][idx].f22 > fn_09_88ba(d.y)) {
                    if (d.x < 0) {
                        if (d.y < 0) {
                            PatBlt(g_13dc, g_1df8[type][idx].f22 + g_1df8[type][idx].f00.x,
                                   g_1df8[type][idx].f00.y, -d.x,
                                   g_1df8[type][idx].f22 - d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f00.x,
                                   g_1df8[type][idx].f00.y + g_1df8[type][idx].f22,
                                   g_1df8[type][idx].f22, -d.y, BLACKNESS);
                        } else {
                            PatBlt(g_13dc, g_1df8[type][idx].f22 + g_1df8[type][idx].f00.x,
                                   g_1df8[type][idx].f00.y - d.y, -d.x,
                                   g_1df8[type][idx].f22 + d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f00.x,
                                   g_1df8[type][idx].f00.y - d.y,
                                   g_1df8[type][idx].f22, d.y, BLACKNESS);
                        }
                    } else {
                        if (d.y < 0) {
                            PatBlt(g_13dc, g_1df8[type][idx].f00.x - d.x,
                                   g_1df8[type][idx].f00.y, d.x,
                                   g_1df8[type][idx].f22 - d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f00.x,
                                   g_1df8[type][idx].f00.y + g_1df8[type][idx].f22,
                                   g_1df8[type][idx].f22, -d.y, BLACKNESS);
                        } else {
                            PatBlt(g_13dc, g_1df8[type][idx].f00.x - d.x,
                                   g_1df8[type][idx].f00.y - d.y, d.x,
                                   g_1df8[type][idx].f22 + d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f00.x,
                                   g_1df8[type][idx].f00.y - d.y,
                                   g_1df8[type][idx].f22, d.y, BLACKNESS);
                        }
                    }
                } else {
                    PatBlt(g_13dc, g_1df8[type][idx].f08.x, g_1df8[type][idx].f08.y,
                           g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
                }
                BitBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
                       g_1df8[type][idx].f22, g_1df8[type][idx].f22, dc,
                       g_1df8[type][idx].f10, g_1df8[type][idx].f12, rop);
            } else {
                BitBlt(g_13dc, g_1df8[type][idx].f00.x - (d.x < 0 ? 0 : d.x),
                       g_1df8[type][idx].f00.y - (d.y < 0 ? 0 : d.y),
                       fn_09_88ba(d.x) + g_1df8[type][idx].f22,
                       fn_09_88ba(d.y) + g_1df8[type][idx].f22, dc,
                       g_1df8[type][idx].f10 - (d.x < 0 ? 0 : d.x),
                       g_1df8[type][idx].f12 - (d.y < 0 ? 0 : d.y), rop);
            }
        }
    } else {
        g_1df8[type][idx].f3a = dc;
        if (g_1df8[type][idx].f2e != 0 && g_1df8[type][idx].f2e != -2) {
            dc = g_1df8[type][idx].f3c;
            g_1df8[type][idx].f10 = g_1df8[type][idx].f24;
            g_1df8[type][idx].f12 = g_1df8[type][idx].f24;
            if (g_1df8[type][idx].f2e == -1)
                draw = 0;
        }
        if (g_952e == g_9646 && (g_9e49 == 3 || g_9e49 == 6 && g_9e47 == 15)) {
            dc = g_1df8[type][idx].f3c;
            g_1df8[type][idx].f10 = g_1df8[type][idx].f24;
            g_1df8[type][idx].f12 = g_1df8[type][idx].f24;
        }
        if (g_913a == 2 || g_913c == 2) {
            dc = g_1df8[type][idx].f3c;
            g_1df8[type][idx].f10 = g_1df8[type][idx].f24;
            g_1df8[type][idx].f12 = g_1df8[type][idx].f24;
        }
        if (draw) {
            HBRUSH old;

            BitBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
                   g_1df8[type][idx].f22, g_1df8[type][idx].f22, dc,
                   g_1df8[type][idx].f10, g_1df8[type][idx].f12, SRCCOPY);
            if (g_1df8[type][idx].f2e == -2) {
                old = SelectObject(g_13dc, g_5ea8);
                PatBlt(g_13dc, g_1df8[type][idx].f00.x, g_1df8[type][idx].f00.y,
                       g_1df8[type][idx].f22, g_1df8[type][idx].f22, 0xa000c9);
                SelectObject(g_13dc, old);
            }
        }
    }
done:
    return 1;
hidden:
    return 0;
}

/* Per-frame camera update: follow the player's object (or the free camera
 * at g_6b50 gliding toward it), apply the screen shake, then split the
 * view into 1, 2 or 4 rectangles where it crosses the map wrap
 * [inferred]. */
/* @addr 8:0000 */
void far fn_08_0000(void)
{
    int dx;
    int dy;
    int dist;
    int k;
    int m;
    POINT pos;
    POINT c;
    POINT w;
    POINT s;

    k = 0;
    s.x = g_90ea << g_9150;
    s.y = g_90ec << g_9150;
    if (g_951a == 0) {
        g_2400 = g_1df8[g_9324][g_9646].f04.x - s.x / 2;
        g_2402 = g_1df8[g_9324][g_9646].f04.y - s.y / 2;
    } else {
        if (g_1df8[g_9324][g_9646].f18 != 0 || g_70ae[g_9646].fce == 0)
            fn_11_aece();
        pos.x = g_1df8[g_9324][g_9646].f04.x;
        pos.y = g_1df8[g_9324][g_9646].f04.y;
        dist = fn_08_285a(&dx, &dy, g_6b50, pos);
        if (dist < 16) {
            g_2400 = g_1df8[g_9324][g_9646].f04.x - s.x / 2;
            g_2402 = g_1df8[g_9324][g_9646].f04.y - ((k << g_9150) + s.y) / 2;
            PatBlt(g_13dc, g_1df8[g_9324][g_9646].f00.x, g_1df8[g_9324][g_9646].f00.y,
                   g_1df8[g_9324][g_9646].f22, g_1df8[g_9324][g_9646].f22, BLACKNESS);
            fn_07_11cc();
            switch (g_9134) {
            case 2:
                g_9134 = 0;
                flow_interactive = 1;
                break;
            case 3:
                g_9134 = 1;
                flow_interactive = 1;
                break;
            case 4:
                g_9134 = 1;
                break;
            }
            g_9134 = g_9378;
            g_951a = 0;
            fn_07_1208();
            g_0a76 = 2;
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        } else {
            g_2394 = dx * 12 / dist * 8;
            g_2396 = dy * 12 / dist * 8;
            g_6b50.y += g_2396;
            g_6b50.x += g_2394;
            if (g_6b50.x < 0)
                g_6b50.x = G_05A0_INT * 8 + g_6b50.x;
            if (g_6b50.x > G_05A0_INT * 8)
                g_6b50.x -= G_05A0_INT * 8;
            if (g_6b50.y < 0)
                g_6b50.y += g_05a2 * 8;
            if (g_6b50.y > g_05a2 * 8)
                g_6b50.y -= g_05a2 * 8;
            g_2400 = g_6b50.x - s.x / 2;
            g_2402 = g_6b50.y - s.y / 2;
            if (g_1df8[g_9324][g_9646].f18 != 0) {
                g_1e80 = g_1e50 + 2000;
                if (g_1df8[g_9324][g_9646].f18 == 1)
                    g_1e84 = g_1e50 + 1500;
            }
        }
    }
    if (g_238c != 0) {
        fn_10_744c(0x69);
        fn_10_754a(8, rand() % g_90ea, rand() % g_90ec, 4);
        g_2390 += g_238c;
        g_2392 += g_238e;
        g_2390 += rand() % 3 - 2;
        g_2392 += rand() % 3 - 2;
        if (g_2390 > 5)
            g_238c = -9;
        else if (g_2390 < -5)
            g_238c = 9;
        if (g_2392 > 5)
            g_238e = -6;
        else if (g_2392 < -5)
            g_238e = 6;
        g_2402 += g_2392 * 8;
        g_2400 += g_2390 * 8;
        g_1df8[g_9324][g_9646].f08.x = g_1df8[g_9324][g_9646].f00.x;
        g_1df8[g_9324][g_9646].f08.y = g_1df8[g_9324][g_9646].f00.y;
        g_1df8[g_9324][g_9646].f00.y += g_2392;
        g_1df8[g_9324][g_9646].f00.x += g_2390;
        fn_07_1208();
        if (g_2408 < g_1e50) {
            g_238c = 0;
            g_1df8[g_9324][g_9646].f08.x = g_1df8[g_9324][g_9646].f00.x;
            g_1df8[g_9324][g_9646].f08.y = g_1df8[g_9324][g_9646].f00.y;
            fn_07_1208();
        }
    } else {
        *(long *)&g_2390 = 0;   /* g_2390 = g_2392 = 0 as one dword store */
    }
    g_2404 = s.x + g_2400;
    g_2406 = s.y + g_2402;
    if (g_951a == 0)
        c = g_1df8[g_9324][g_9646].f04;
    else
        c = g_6b50;
    w.x = G_05A0_INT * 8;
    w.y = g_05a2 * 8;
    m = 600;
    if (g_9320 == 6 && g_9eb5 != 1) {
        g_23e0[0].left = g_2400 - 600;
        g_23e0[0].right = g_2404 + 600;
        g_23e0[0].top = g_2402 - 600;
        g_23e0[0].bottom = g_2406 + 600;
        g_9158 = 1;
    } else if (s.x / 2 + m > c.x) {
        g_23e0[0].left = -m;
        g_23e0[0].right = m + g_2404;
        g_23e0[1].left = w.x - s.x / 2 - m + c.x;
        g_23e0[1].right = w.x + m;
        if (s.y / 2 + m > c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[1].top = g_23e0[0].top = -m;
            g_23e0[3].top = g_23e0[2].top = w.y - s.y / 2 - m + c.y;
            g_23e0[0].bottom = g_23e0[1].bottom = m + g_2406;
            g_23e0[2].bottom = g_23e0[3].bottom = w.y + m;
            g_9158 = 4;
        } else if (w.y - s.y / 2 - m < c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[0].top = g_23e0[1].top = -m;
            g_23e0[2].top = g_23e0[3].top = g_2402 - m;
            g_23e0[0].bottom = g_23e0[1].bottom = s.y / 2 - w.y + c.y + m;
            g_23e0[2].bottom = g_23e0[3].bottom = w.y + m;
            g_9158 = 4;
        } else {
            g_23e0[0].top = g_23e0[1].top = c.y - s.y / 2 - m;
            g_23e0[0].bottom = g_23e0[1].bottom = s.y / 2 + c.y + m;
            g_9158 = 2;
        }
    } else if (w.x - s.x / 2 - m < c.x) {
        g_23e0[0].left = g_2400 - m;
        g_23e0[0].right = w.x + m;
        g_23e0[1].left = -m;
        g_23e0[1].right = s.x / 2 - w.x + c.x + m;
        if (s.y / 2 + m > c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[1].top = g_23e0[0].top = -m;
            g_23e0[3].top = g_23e0[2].top = w.y - s.y / 2 - m + c.y;
            g_23e0[0].bottom = g_23e0[1].bottom = m + g_2406;
            g_23e0[2].bottom = g_23e0[3].bottom = w.y + m;
            g_9158 = 4;
        } else if (w.y - s.y / 2 - m < c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[0].top = g_23e0[1].top = g_2402 - m;
            g_23e0[2].top = g_23e0[3].top = -m;
            g_23e0[0].bottom = g_23e0[1].bottom = w.y + m;
            g_23e0[2].bottom = g_23e0[3].bottom = s.y / 2 - w.y + c.y + m;
            g_9158 = 4;
        } else {
            g_23e0[0].top = g_23e0[1].top = g_2402 - m;
            g_23e0[0].bottom = g_23e0[1].bottom = m + g_2406;
            g_9158 = 2;
        }
    } else if (s.y / 2 + m > c.y) {
        g_23e0[0].left = g_23e0[1].left = c.x - s.x / 2 - m;
        g_23e0[0].right = g_23e0[1].right = g_23e0[0].left + m * 2 + s.x;
        g_23e0[0].top = -m;
        g_23e0[1].top = w.y - s.y / 2 - m + c.y;
        g_23e0[0].bottom = m + g_2406;
        g_23e0[1].bottom = w.y + m;
        g_9158 = 2;
    } else if (w.y - s.y / 2 - m < c.y) {
        g_23e0[0].left = g_23e0[1].left = c.x - s.x / 2 - m;
        g_23e0[0].right = g_23e0[1].right = g_23e0[0].left + m * 2 + s.x;
        g_23e0[0].top = g_2402 - m;
        g_23e0[1].top = -m;
        g_23e0[0].bottom = w.y + m;
        g_23e0[1].bottom = s.y / 2 - w.y + c.y + m;
        g_9158 = 2;
    } else {
        g_23e0[0].left = g_2400 - m;
        g_23e0[0].right = m + g_2404;
        g_23e0[0].top = g_2402 - m;
        g_23e0[0].bottom = m + g_2406;
        g_9158 = 1;
    }
    g_240c = g_2400;
    g_2410 = g_2402;
}

/* Build the animated map icon for unit a (pieces g_915c) from its sprite
 * (fn_10_7370) and notify related units; b == 0 [inferred: side] picks
 * the other icon frame. */
/* @addr 8:2cd8 */
void far fn_08_2cd8(int a, int b)
{
    int flag;
    int done;
    int i;
    int k;
    int sz;
    int r;
    int dir;
    int h;
    HBITMAP bmp;
    HBITMAP oldbmp;
    HDC dc;
    HPALETTE oldpal;
    POINT o;
    POINT p;
    POINT q;
    POINT z;

    done = flag = 0;
    g_70ae[a].f138 = g_1e50 - 10000;
    if (b == 0) {
        g_70ae[a].f8e = 0;
        flag = 1;
    } else
        g_70ae[a].f8f = 0;
    if (g_95a6 == 0) {
        fn_14_3eda();
        if (g_70ae[a].fb8 >= 0)
            g_96ea[g_70ae[a].f30].f24 =
                (g_6e1c[g_6e20[g_6e24[g_70ae[a].fb8].f00].f21].f1a << g_9156 >> 1) / 2;
        else
            g_96ea[g_70ae[a].f30].f24 =
                (g_6e1c[g_6e20[g_4ed8[g_70ae[a].f40]].f21].f1a << g_9156 >> 1) / 2;
        fn_14_4074();
    }
    if (g_92e4 == 0) {
        for (i = 0; i <= g_9316; i++) {
            if (g_70ae[i].f14.a == g_9324 && g_70ae[i].f14.b == a && g_70ae[i].f1a == 1) {
                if (g_70ae[i].f8e == g_70ae[a].f8e && g_70ae[i].f8f == g_70ae[a].f8f)
                    fn_03_06ec(i, g_9324, a, 0x1b);
                else if (g_70ae[a].f8e != 0 || g_70ae[a].f8f != 0) {
                    if (g_70ae[i].f8e == 0 && g_70ae[i].f8f == 0)
                        fn_03_06ec(i, g_9324, a, 0x1e);
                    else if (fn_04_5d9c(a, i) > 95)
                        fn_03_06ec(i, g_9324, a, 0x1c);
                    else
                        fn_03_06ec(i, g_9324, a, 0x19);
                } else if (fn_04_5d9c(a, i) > 95)
                    fn_03_06ec(i, g_9324, a, 0x1d);
                else
                    fn_03_06ec(i, g_9324, a, 0x1a);
            }
        }
        for (i = done = 0; i < 3; i++) {
            if (g_915c[i].f1a == 0) {
                if (subgame_active == 0) {
                    sz = 0x100;
                    h = 0x100 >> g_9150;
                    r = g_96ea[g_70ae[a].f30].f24 / 2 * 8
                        + (g_1df8[g_9324][a].f20 - g_96ea[g_70ae[a].f30].f24 * 8) / 4;
                } else {
                    h = ((g_9156 << 6) + 32) / 3;
                    sz = (int)(h * g_88cc / g_88c0);
                    r = (int)(g_96ea[g_70ae[a].f30].f24 / 2 * g_88cc / g_88c0)
                        + (g_1df8[g_9324][a].f20
                           - (int)(g_96ea[g_70ae[a].f30].f24 * g_88cc / g_88c0)) / 4;
                }
                g_915c[i].f1a = 1;
                g_915c[i].f1c = 0x46;
                g_915c[i].f1e = g_1df8[g_9324][a].f20;
                g_915c[i].f00 = g_1df8[g_9324][a].f04;
                g_915c[i].f04.x = -1000;
                g_915c[i].f04.y = -1000;
                dir = g_1df8[g_9324][a].f28;
                g_915c[i].f08 = *(POINT far *)&g_1df8[g_9324][a].f0c;   /* velocity */
                g_915c[i].f08.x += g_1050[(dir + 4) % 16].x / 2;
                g_915c[i].f08.y += g_1050[(dir + 4) % 16].y / 2;
                if (flag) {
                    p.x = g_915c[i].f1e / 2 + g_066e[(dir + 12) % 16].x * r / 128;
                    p.y = g_915c[i].f1e / 2 + g_066e[(dir + 12) % 16].y * r / 128;
                } else {
                    p.x = g_915c[i].f1e / 2 + g_066e[(dir + 4) % 16].x * r / 128;
                    p.y = g_915c[i].f1e / 2 + g_066e[(dir + 4) % 16].y * r / 128;
                }
                q.x = min(sz / 2 + p.x, g_915c[i].f1e);
                z.x = max(p.x - sz / 2, 0);
                q.y = min(sz / 2 + p.y, g_915c[i].f1e);
                z.y = max(p.y - sz / 2, 0);
                o.x = max(sz / 2 - p.x, 0);
                o.y = max(sz / 2 - p.y, 0);
                g_915c[i].f00.x += p.x - sz / 2;
                g_915c[i].f00.y += p.y - sz / 2;
                bmp = fn_10_7370(g_3a38[a], flag, g_1df8[g_9324][a].f22,
                                 g_96ea[g_70ae[a].f30].f24, g_1df8[g_9324][a].f24,
                                 g_1df8[g_9324][a].f28, 1);
                dc = CreateCompatibleDC(g_13dc);
                oldbmp = SelectObject(dc, bmp);
                if (g_920e != 0)
                    oldpal = SelectPalette(dc, g_920e, 0);
                g_915c[i].f0c = CreateCompatibleDC(g_13dc);
                g_915c[i].f10 = CreateCompatibleBitmap(g_13dc, h * 5, h);
                g_915c[i].f14 = SelectObject(g_915c[i].f0c, g_915c[i].f10);
                if (g_920e != 0)
                    g_915c[i].f18 = SelectPalette(g_915c[i].f0c, g_920e, 0);
                PatBlt(g_915c[i].f0c, 0, 0, h * 5, h, BLACKNESS);
                if (subgame_active == 0) {
                    for (k = 0; k < 5; k++)
                        BitBlt(g_915c[i].f0c, (sz * k + o.x) >> g_9150, o.y >> g_9150,
                               (q.x - z.x) >> g_9150, (q.y - z.y) >> g_9150, dc,
                               z.x >> g_9150, z.y >> g_9150, SRCCOPY);
                } else {
                    o.x = (int)(o.x * (long)g_88c0 * (g_9156 * 2 + 1) / g_88cc) / 3;
                    o.y = (int)(o.y * (long)g_88c0 * (g_9156 * 2 + 1) / g_88cc) / 3;
                    for (k = 0; k < 5; k++)
                        BitBlt(g_915c[i].f0c, h * k + o.x, o.y,
                               (int)((q.x - z.x) * (long)g_88c0 * (g_9156 * 2 + 1) / g_88cc) / 3,
                               (int)((q.y - z.y) * (long)g_88c0 * (g_9156 * 2 + 1) / g_88cc) / 3,
                               dc,
                               (int)(z.x * (long)g_88c0 * (g_9156 * 2 + 1) / g_88cc) / 3,
                               (int)(z.y * (long)g_88c0 * (g_9156 * 2 + 1) / g_88cc) / 3,
                               SRCCOPY);
                }
                SelectObject(g_915c[i].f0c, g_915c[i].f14);
                g_915c[i].f12 = fn_10_6ec6(g_915c[i].f10);
                g_915c[i].f14 = SelectObject(g_915c[i].f0c, g_915c[i].f10);
                g_915c[i].f0e = CreateCompatibleDC(g_13dc);
                g_915c[i].f16 = SelectObject(g_915c[i].f0e, g_915c[i].f12);
                done = 1;
                SelectObject(dc, oldbmp);
                if (oldpal != 0)
                    SelectPalette(dc, oldpal, 0);
                DeleteDC(dc);
                DeleteObject(bmp);
                fn_10_754a(0x6a, g_9324, a, 1);
                break;
            }
        }
    }
    if (done == 0)
        fn_10_7370(g_3a38[a], flag, g_1df8[g_9324][a].f22,
                   g_96ea[g_70ae[a].f30].f24, g_1df8[g_9324][a].f24,
                   g_1df8[g_9324][a].f28, 0);
}

/* Clamp an object's velocity to [-v, v] [inferred]. */
/* @addr 8:1cbe */
void far pascal fn_08_1cbe(r, v)
OBJREF r;
int v;
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

/* Tether physics for object (type, idx) towing object f32/f34: spring
 * forces, break-off, and redraw of the tether line [inferred]. */
/* near-match 99%: 8:1e32 (only compiler temp slots differ: the original
 * puts the cx/bx spills at bp-44/-42 and the POINT return temps at bp-48
 * and bp-4c; here the return temps come first). pad keeps per at bp-48. */
void far pascal fn_08_1e32(int type, int idx)
{
    POINT c;
    POINT dv;
    POINT dp;
    HPEN old;
    int dist;
    int t2;
    int i2;
    int bi;
    int len;
    int u;
    int w;
    int m1;
    int m2;
    int f1;
    int f2;
    int px;
    int py;
    int rest;
    int heavy;
    int k;
    long dot;
    long a;
    long b;
    int force;
    int j;

    g_915a++;
    if (g_915a > 3)
        g_915a = 0;
    bi = g_1df8[type][idx].f30;
    if (g_65cc[bi].f0a == 2)
        heavy = 1;
    else
        heavy = 0;
    g_1df8[type][idx].f04.x -= g_1df8[type][idx].f0c;
    g_1df8[type][idx].f04.y -= g_1df8[type][idx].f0e;
    t2 = g_1df8[type][idx].f32;
    i2 = g_1df8[type][idx].f34;
    /* bare label: resets CL's register tracking (layout only) */
lbl:
    k = 0;
    j = i2;
    rest = 300;
    c.x = g_1df8[t2][i2].f20 / 2 + g_1df8[t2][i2].f04.x;
    c.y = g_1df8[t2][i2].f20 / 2 + g_1df8[t2][i2].f04.y;
    g_65cc[bi].f10 = fn_08_29ea(g_1df8[type][idx].f04);
    g_65cc[bi].f18 = fn_08_29ea(g_1df8[t2][i2].f04);
    dist = fn_08_285a(&px, &py, g_1df8[type][idx].f04, c);
    if (dist == 0)
        dist = 1;
    if (t2 == 14) {
        int m;
        int pad;
        int per;

        m = g_1df8[type][idx].f44;
        per = m / -200 + 8 < 3 ? 3 : m / -200 + 8;
        if (g_1e68 % per == 0) {
            g_70ae[i2].f00 -= 3;
            if (g_70ae[i2].f00 <= 0)
                dist = 1000;
        }
    }
    if (heavy * 100 + 350 < dist
        || g_1df8[g_1df8[type][idx].f32][g_1df8[type][idx].f34].f18 != 0
        || type == 7) {
        g_1df8[type][idx].f32 = -1;
        g_1df8[g_65cc[bi].f04][g_65cc[bi].f06].f36 = -1;
        g_65cc[bi].f00 = -1;
        g_65cc[bi].f04 = -1;
        old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
        fn_12_7256(g_13dc, g_65cc[bi].f1c, g_65cc[bi].f14);
        fn_12_7256(g_13dc, g_65cc[bi].f18, g_65cc[bi].f10);
        SelectObject(g_13dc, old);
        fn_07_2080(10, -1);
        fn_10_744c(0x69);
        fn_10_754a(0x14, type, idx, 1);
    }
    if (dist > 40) {
        if (heavy == 0) {
            if (rest < dist) {
                dv.x = g_1df8[type][idx].f0c - g_1df8[t2][i2].f0c;
                dv.y = g_1df8[type][idx].f0e - g_1df8[t2][i2].f0e;
                len = (int)fn_08_1290((long)(dv.x * dv.x + dv.y * dv.y),
                                      (long)(fn_09_88ba(dv.x) + fn_09_88ba(dv.y)));
                dp.x = g_65cc[bi].f18.x - g_65cc[bi].f10.x;
                dp.y = g_65cc[bi].f18.y - g_65cc[bi].f10.y;
                a = (long)dp.x * dv.x;
                b = (long)dp.y * dv.y;
                dot = a + b;
                if (len == 0)
                    len = 1;
                u = (int)((w = (int)(dot * -100 / ((long)dist * len))) * (long)len / 100);
                force = min(dist - rest, 60) * 50;
                m1 = g_1df8[type][idx].f44;
                m2 = g_1df8[t2][i2].f44;
                if (k != 0)
                    m1 /= 3;
                if (rest < 300)
                    m1 /= 3;
                if (force > 3000 && rest >= 300)
                    u = -50;
                if (force > 1800 && rest < 300 && type == g_9324
                    && g_7092[idx].fe0 == 0 && g_7092[idx].f00 != 0) {
                    g_1df8[g_9324][i2].f50 = 60;
                    fn_11_a234(g_9324, i2, type, idx);
                }
                if (dot < 0) {
                    f1 = (int)((long)u * 100 / ((long)m1 * 100 / m2 + 100));
                    f2 = u - f1;
                } else
                    f1 = f2 = 0;
                f1 += force / m1;
                g_1df8[type][idx].f0c += (g_17bc / 3 + f1) * dp.x / dist;
                g_1df8[type][idx].f0e += (g_17bc / 3 + f1) * dp.y / dist;
                f2 += force / m2;
                g_1df8[t2][i2].f0c -= (g_17be / 3 + f2) * dp.x / dist;
                g_1df8[t2][i2].f0e -= (g_17be / 3 + f2) * dp.y / dist;
                g_17bc = f1;
                g_17be = f2;
                if (rest < 300)
                    fn_08_1cbe((char)idx | type << 8, 80);
            }
        } else if (g_1df8[type][idx].f53 == 1) {
            g_1df8[type][idx].f0c += px >> 2;
            g_1df8[type][idx].f0e += py >> 2;
        } else if (g_65cc[bi].f0e != 0) {
            g_1df8[type][idx].f0c = (int)(180L * py / dist) + (px << 3) / dist;
            g_1df8[type][idx].f0e = (int)(-180L * px / dist) + (py << 3) / dist;
        } else {
            g_1df8[type][idx].f0c = (int)(-180L * py / dist) + (px << 3) / dist;
            g_1df8[type][idx].f0e = (int)(180L * px / dist) + (py << 3) / dist;
        }
    }
    g_1df8[type][idx].f04.x += g_1df8[type][idx].f0c;
    g_1df8[type][idx].f04.y += g_1df8[type][idx].f0e;
    fn_07_1208();
    old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
    fn_12_7256(g_13dc, g_65cc[bi].f1c, g_65cc[bi].f14);
    SelectObject(g_13dc, old);
    if (g_1df8[type][idx].f32 != -1) {
        g_65cc[bi].f10 = fn_08_29ea(g_1df8[type][idx].f04);
        g_65cc[bi].f10.x += (g_1df8[type][idx].f0c >> g_9150) + g_1df8[type][idx].f22 / 2;
        g_65cc[bi].f10.y += (g_1df8[type][idx].f0e >> g_9150) + g_1df8[type][idx].f22 / 2;
        g_65cc[bi].f18 = fn_08_29ea(g_1df8[t2][i2].f04);
        g_65cc[bi].f18.x += g_1df8[t2][i2].f22 / 2;
        g_65cc[bi].f18.y += g_1df8[t2][i2].f22 / 2;
        if (g_8ff2 != 0)
            old = SelectObject(g_13dc, GetStockObject(WHITE_PEN));
        else
            old = SelectObject(g_13dc, g_3b44[g_915a]);
        fn_12_7256(g_13dc, g_65cc[bi].f18, g_65cc[bi].f10);
        SelectObject(g_13dc, old);
    }
    g_65cc[bi].f14 = g_65cc[bi].f10;
    g_65cc[bi].f1c = g_65cc[bi].f18;
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

extern int g_06ae;
extern int g_8ff2;
extern RECT g_1d30;             /* play view */
extern HBRUSH g_3b4c[];

/* Stars: move them against the ship's motion (deeper stars slower),
 * wrap them round the play view and draw them twinkling; every second
 * call only [inferred]. */
/* @addr 8:158a */
void far pascal fn_08_158a(int still)
{
    int i;
    int maxsz;
    int t1;
    int t2;
    int c;
    int sz;

    g_06ae++;
    if (g_06ae > 1)
        g_06ae = 0;
    if (still)
        g_06ae = 0;
    if (g_06ae != 0)
        return;
    if (g_8ff2) {
        fn_08_1320(still);
        return;
    }
    if (g_9156 == 0)
        maxsz = 2;
    else
        maxsz = 3;
    if (g_1df8[g_9324][g_9646].f18 == 1
        || (g_1df8[g_9324][g_9646].f54 != 0 && g_92e8 != 0)) {
        g_1df8[g_9324][g_9646].f0c = 0;
        g_1df8[g_9324][g_9646].f0e = 0;
    }
    for (i = 0; i < g_9152; i++) {
        if (g_91c2[i])
            PatBlt(g_13dc, g_2398[i].x, g_2398[i].y,
                   t1 = g_91d4[i] > maxsz ? maxsz : g_91d4[i], t1, BLACKNESS);
        if (still == 0) {
            t1 = g_9156 + 1;
            t2 = 6 - g_91d4[i];
            if (g_951a) {
                g_2398[i].x -= g_2394 << t1 >> t2;
                g_2398[i].y -= g_2396 << t1 >> t2;
            } else {
                g_2398[i].x -= g_1df8[g_9324][g_9646].f0c << t1 >> t2;
                g_2398[i].y -= g_1df8[g_9324][g_9646].f0e << t1 >> t2;
            }
            if (g_238c) {
                g_2398[i].x += g_2390 << t1 >> t2;
                g_2398[i].y += g_2392 << t1 >> t2;
            }
            if (g_2398[i].x < g_1d30.left) {
                g_2398[i].x = g_1d30.right;
                g_2398[i].y = rand() % (g_1d30.bottom - g_1d30.top);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            } else if (g_2398[i].x > g_1d30.right) {
                g_2398[i].x = g_1d30.left;
                g_2398[i].y = rand() % (g_1d30.bottom - g_1d30.top);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            }
            if (g_2398[i].y < g_1d30.top) {
                g_2398[i].y = g_1d30.bottom;
                g_2398[i].x = rand() % (g_1d30.right - g_1d30.left);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            } else if (g_2398[i].y > g_1d30.bottom) {
                g_2398[i].y = g_1d30.top;
                g_2398[i].x = rand() % (g_1d30.right - g_1d30.left);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            }
        }
        if (g_9154 == g_9152) {
            if (!PtInRect(&g_1e5c, g_2398[i])) {
                t1 = g_91e6[i] / 5;
                if (t1 < 4)
                    c = t1 + 10;
                else
                    c = 18 - t1;
                sz = g_91d4[i] > maxsz ? maxsz : g_91d4[i];
                t2 = SelectObject(g_13dc, g_3b4c[c]);
                PatBlt(g_13dc, g_2398[i].x, g_2398[i].y, sz, sz, PATCOPY);
                SelectObject(g_13dc, t2);
                if (g_91e6[i] < 40)
                    g_91e6[i]++;
                else
                    g_91e6[i] = 0;
                g_91c2[i] = 1;
            } else {
                g_91c2[i] = 0;
            }
        }
    }
    if (g_9154 != g_9152)
        g_9152 = g_9154;
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
/* near-match 99%: 8:1290 (one instruction: the dead loop's g < 3 test
 * compares the low word as cmp ax,3; the original reloads it from memory) */
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
        b = (n - g * g) / (2 * g) + g;
        g = b;
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

/* Direction to aim from object (t1, i1) at the moving object (t2, i2):
 * a lead from the target's velocity and the shooter's speed [inferred]. */
/* @addr 8:2658 */
int far pascal fn_08_2658(int t1, int i1, int t2, int i2)
{
    long u4;
    long u8;
    long uc;
    long side;
    long speed;
    long diff;
    long e2;
    long e1;
    long f1;
    long f2;
    long sq;
    int dist;
    int dx;
    int dy;
    int r;

    dist = fn_08_285a(&dx, &dy, g_1df8[t1][i1].f04, g_1df8[t2][i2].f04);
    side = (long)g_1df8[t2][i2].f0c * dy / dist - (long)g_1df8[t2][i2].f0e * dx / dist;
    speed = fn_08_35d0(g_1df8[t1][i1].f0c, g_1df8[t1][i1].f0e);
    if (speed < 30)
        speed = 50;
    if (speed < side)
        return fn_08_19b0(dx, dy);
    sq = speed * speed - side * side;
    r = (int)fn_08_1290(sq, diff = abs32(speed) - abs32(side));
    e1 = (long)r * dx / dist;
    e2 = (long)dy * side / dist;
    f1 = -((long)dx * side / dist);
    f2 = (long)r * dy / dist;
    return fn_08_19b0((int)(e2 + e1), (int)(f1 + f2));
}
