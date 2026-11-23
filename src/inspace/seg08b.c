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
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    int f26;                    /* +26 */
    char p28[0x2e - 0x28];
    char f2e;                   /* +2e */
    char f2f;                   /* +2f */
    char f30;                   /* +30 */
    char p31;
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    char p36[0x42 - 0x36];
    int f42;                    /* +42 */
    int f44;                    /* +44 */
    char p46[0x48 - 0x46];
    int f48;                    /* +48 */
    char p4a[0x50 - 0x4a];
    char f50;                   /* +50 */
    char p51[0x53 - 0x51];
    char f53;                   /* +53 */
    char f54;                   /* +54 */
    char f55[0x5e - 0x55];      /* +55: per shot group n [inferred] */
    int (far *f5e)(int type, int idx, int dmg);  /* +5e: damage callback */
    char p62[0x70 - 0x62];
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
    char p00[2];
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08[4];                 /* +08 */
    int f10;                    /* +10 */
    char p12[2];
    int f14;                    /* +14 */
    int f16;                    /* +16 */
    char p18[2];
    int f1a;                    /* +1a */
    char p1c[0x30 - 0x1c];
    int f30;                    /* +30 */
    char p32[2];
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    int f3a;                    /* +3a */
    char p3c[0x40 - 0x3c];
    char f40;                   /* +40 */
    char p41[0x66 - 0x41];
    DWORD f66;                  /* +66 */
    char p6a[0x86 - 0x6a];
    DWORD f86;                  /* +86 */
    char p8a[0x8e - 0x8a];
    char f8e;                   /* +8e */
    char f8f;                   /* +8f */
    char p90[0x9a - 0x90];
    char f9a[0x13];             /* +9a */
    char pad[0xb8 - 0xad];
    int fb8;                    /* +b8 */
    int fba;                    /* +ba */
    char pbc[0xc2 - 0xbc];
    char fc2;                   /* +c2 */
    char fc3;                   /* +c3 */
    char fc4;                   /* +c4 */
    char fc5;                   /* +c5 */
    char pc6[0xca - 0xc6];
    char fca;                   /* +ca */
    char pcb;
    char fcc;                   /* +cc */
    char pcd;
    char fce;                   /* +ce */
    char pcf[0x129 - 0xcf];
    char f129;                  /* +129 */
    char p12a[2];
    POINT f12c;                 /* +12c */
    DWORD f130;                 /* +130 */
    char p134[4];
    DWORD f138;                 /* +138 */
    char p13c[0x15a - 0x13c];
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
typedef struct {
    int f00;                    /* +00 */
    char p02[0x12 - 0x02];
    int f12;                    /* +12 */
    char p14[0x26 - 0x14];
    int f26;                    /* +26 */
    char p28[0x34 - 0x28];
} REC_34;
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
    char p60[0x68 - 0x60];
    int f68;        /* +68 */
    int f6a;        /* +6a */
    char p6c[0x70 - 0x6c];
    int f70;        /* +70 */
    int f72;        /* +72 */
    int f74;        /* +74 */
    int f76;        /* +76 */
    int f78;        /* +78: count */
    int f7a;        /* +7a */
    int f7c;        /* +7c */
    int f7e;        /* +7e */
    int f80;        /* +80 */
    int f82;        /* +82 */
    int f84[2];     /* +84 */
    int f88;        /* +88 */
    int f8a;        /* +8a */
    char p8c[0x90 - 0x8c];
    long f90;       /* +90 */
} REC_94;
extern REC_94 g_6098[];
extern int g_9646;
extern int g_0b0e[];
extern int g_0b38[];
extern long g_5078;
extern long g_1e58;
extern int g_9436;
extern int g_9438;
extern int g_9328;
extern int g_944a;
extern int g_944c;
extern int g_944e;
extern int g_9450;

int far fn_08_5df2(int a, int b, int c, int d, int e);
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
int far fn_18_2c1e(int type, int idx);
int far pascal fn_08_6afa(WORD a, WORD b);
#define SC(n) ((n) << g_9156 >> 1)
/* 0xad-byte records; lowest field seen at DS:96ea [inferred]. */
#pragma pack(1)
typedef struct {
    char p00[0x1a];
    int f1a;                    /* +1a */
    char p1c[0x20 - 0x1c];
    int f20;                    /* +20 */
    char p22[0x2a - 0x22];
    int f2a;                    /* +2a */
    char p2c[0xad - 0x2c];
} REC_AD;
#pragma pack()
extern REC_AD g_96ea[];
/* 0x1c-byte records at DS:6678 [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    char p08[0x1c - 0x08];
} REC_1CB;
extern REC_1CB g_6678[];
extern int g_9318;
extern POINT g_5168[];
extern int g_943a;
extern int g_943c;
extern long g_88cc;
int far pascal fn_10_7dd4(int far *a, int far *b, int far *c, int far *d,
                          int far *e, int far *f, int far *g, int far *h,
                          int i, int j, int k, int l, int far *m, int far *n);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_08_804a(int a, int b, int c);
int far pascal fn_08_6f3c(int t, int i, int n, int k);
void far fn_08_7be8(int a, int b, int c, int d);


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

/* Collision test of shot group n [inferred]: 2 when it hits an object or
 * a wall rect, 1 when it bounces off the sub-game border, else 0. k is
 * passed to fn_08_6f3c before it is set (as in the original). */
/* near-match 74%: 8:3688 (the original keeps g_1e38, n * 0x94 and the
 * x0/y0 addresses as CSEs across the fn_10_7dd4 call and stores g_943c
 * before the constants; here they are recomputed) */
int far pascal fn_08_3688(int n)
{
    int i;
    int u6;
    int j;
    int k;
    int res;
    int pad[7];

    for (j = 0; j < g_6098[n].f78; j++) {
        g_5168[j].x = g_6098[n].x1[j][0];
        g_5168[j].y = g_6098[n].y1[j][0];
        g_5168[j] = fn_08_29ea(g_5168[j]);
    }
    for (i = 0; i < g_9146; i++) {
        if (g_507c[i] != g_9328) {
            res = fn_08_6f3c(g_507c[i], g_50e0[i], n, k);
            if (res == 2)
                return 2;
            if (res == 1)
                return 1;
        }
    }
    if (g_6098[n].f7a == 14
        && g_1df8[g_70ae[g_6098[n].f7c].f14][g_70ae[g_6098[n].f7c].f16].f1a == 0) {
        res = fn_08_6f3c(g_70ae[g_6098[n].f7c].f14, g_70ae[g_6098[n].f7c].f16, n, k);
        if (res == 2)
            return 2;
        if (res == 1)
            return 1;
    }
    for (j = 0; j < g_6098[n].f78; j++) {
        g_5168[j].x = g_6098[n].x1[j][0];
        g_5168[j].y = g_6098[n].y1[j][0];
    }
    for (i = 0; i < g_9318; i++) {
        RECT r;

        SetRect(&r, g_6678[i].f00, g_6678[i].f02 - 5, g_6678[i].f04, g_6678[i].f06 + 5);
        if (PtInRect(&r, g_5168[0]))
            return 2;
        if (PtInRect(&r, g_5168[1]))
            return 2;
    }
    if (subgame_active != 0) {
        int flag;
        int ok;
        int a28;
        int a2a;

        j = flag = 0;
        for (; j < g_6098[n].f78; j++) {
            if (g_6098[n].x0[j][0] <= g_88c4) {
                g_1e38->x = g_88c4 - 30;
                g_1e38->y = g_6098[n].y0[j][0] + g_88c6 - 15;
                flag = 1;
            } else if (g_88c4 + g_88c0 - 2 < g_6098[n].x0[j][0]) {
                g_1e38->x = g_88c4 + g_88c0;
                g_1e38->y = g_6098[n].y0[j][0] + g_88c6 - 15;
                flag = 1;
            } else if (g_6098[n].y0[j][0] <= g_88c6) {
                g_1e38->y = g_88c6 - 30;
                g_1e38->x = g_6098[n].x0[j][0] + g_88c4 - 15;
                flag = 1;
            } else if (g_88c6 + g_88c2 - 2 < g_6098[n].y0[j][0]) {
                g_1e38->y = g_88c6 + g_88c2;
                g_1e38->x = g_6098[n].x0[j][0] + g_88c4 - 15;
                flag = 1;
            } else if (fn_18_2c1e(30, n) == 2) {
                return 2;
            }
            if (flag != 0) {
                k = 14 - g_6098[n].f76 * 14 / g_6098[n].f74;
                if (g_6098[n].f76 < 20)
                    k = 23;
                if (g_6098[n].f7a == g_9324
                    && (g_6098[n].f7c == g_9646
                        || g_96ea[g_70ae[g_6098[n].f7c].f30].f20 == 7
                            && g_70ae[g_6098[n].f7c].f40 == 0))
                    k <<= 1;
                if (g_6098[n].f7a == g_9324)
                    k = g_96ea[g_70ae[g_6098[n].f7c].f30].f1a * k / 250;
                g_943c = n;
                g_944a = 16;
                g_944e = 0;
                g_9450 = n;
                a2a = g_6098[n].f70 * 5;
                a28 = g_6098[n].f72 * 5;
                ok = fn_10_7dd4(&a2a, &a28, &g_1e38[3].x, &g_1e38[3].y,
                    &g_6098[n].x0[j][0], &g_6098[n].y0[j][0], &g_1e38->x, &g_1e38->y,
                    2, g_944c = g_943a = 30, k, 20000, &g_9436, &g_9438);
                if (ok == 0)
                    break;
                fn_10_754a(0x11, 30, n, 2);
                g_6098[n].f70 = a2a / 5;
                g_6098[n].f72 = a28 / 5;
                g_6098[n].x1[j][0] = (int)(g_6098[n].x0[j][0] * g_88cc / g_88c0);
                g_6098[n].y1[j][0] = (int)(g_6098[n].y0[j][0] * g_88cc / g_88c0);
                if (g_9208 >= 2 && k * g_9436 > 600)
                    fn_08_804a(n, k * g_9436, j);
                return 1;
            }
        }
    }
    return 0;
}

extern long g_05cc;
extern int g_05a2;
extern int g_9136;
extern HBRUSH g_3b4c[20];
int far pascal fn_18_4dc4(int n);
void far pascal fn_08_0764(int a, int b);
void far fn_11_5626(int i);

/* Move and draw shot group n one step (s: speed factor) [inferred];
 * returns 1 while the group is alive. w is read uninitialised when the
 * group was already finished (as in the original). */
/* @addr 8:3aec */
int far pascal fn_08_3aec(int n, int s)
{
    int u4;
    int u6;
    int u8;
    int sz;
    int w;
    int m;
    int j;
    int v;
    int res;

    if (g_6098[n].f76 >= 0 && g_6098[n].f74 > g_6098[n].f76) {
        sz = (g_9208 + 1 >> 1) + 3;
        if (subgame_active != 0) {
            w = g_9156 + 1;
            fn_18_4dc4(n);
        } else
            w = SC(2);
        fn_08_0764(n, 0);
        res = fn_08_3688(n);
        if (res != 0 && g_6098[n].f7a == g_9324 && g_6098[n].f7c == g_9646)
            g_6098[n].f7e++;
        if (res == 2) {
            g_6098[n].f76 = -1;
            for (m = sz; m > -1; m--)
                for (j = 0; j < g_6098[n].f78; j++)
                    if (g_6098[n].f84[j] != 0)
                        PatBlt(g_13dc, g_6098[n].x0[j][m], g_6098[n].y0[j][m], w, w,
                               BLACKNESS);
            return 1;
        }
        if ((res == 1 || g_6098[n].f90 == g_05cc) && g_05cc != 0) {
            if (g_6098[n].f90 == g_05cc) {
                fn_10_754a(0x11, 0x1e, n, 2);
                g_6098[n].f70 = g_6098[n].f88;
                g_6098[n].f72 = g_6098[n].f8a;
                g_6098[n].x1[0][0] += g_6098[n].f70;
                g_6098[n].y1[0][0] += g_6098[n].f72;
            }
            if (g_9320 == 6)
                fn_11_5626(n);
        }
        v = g_6098[n].f76 * 8 / g_6098[n].f74;
        if (g_6098[n].f7a == g_9324)
            SelectObject(g_13dc, g_3b4c[v + g_70ae[g_6098[n].f7c].fc5 * 10]);
        else
            SelectObject(g_13dc, g_3b4c[v + 10]);
        for (j = 0; j < g_6098[n].f78; j++) {
            if (g_6098[n].f84[j] != 0) {
                g_6098[n].x0[j][0] += g_1df8[g_6098[n].f7a][g_6098[n].f7c].f0c * s / -50;
                g_6098[n].y0[j][0] += g_1df8[g_6098[n].f7a][g_6098[n].f7c].f0e * s / -50;
                if (g_6098[n].x0[j][0] > 0 && g_6098[n].x0[j][0] < g_90ea
                    && g_6098[n].y0[j][0] > 0 && g_6098[n].y0[j][0] < g_90ec
                    || subgame_active != 0)
                    PatBlt(g_13dc, g_6098[n].x0[j][0], g_6098[n].y0[j][0], w, w, PATCOPY);
            }
        }
        if (g_6098[n].x0[0][3] != -100)
            for (j = 0; j < g_6098[n].f78; j++)
                if (g_6098[n].f84[j] != 0)
                    PatBlt(g_13dc, g_6098[n].x0[j][sz], g_6098[n].y0[j][sz], w, w,
                           BLACKNESS);
        g_6098[n].f76++;
        for (m = sz; m > 0; m--)
            for (j = 0; j < g_6098[n].f78; j++) {
                g_6098[n].x0[j][m] = g_6098[n].x0[j][m - 1];
                g_6098[n].y0[j][m] = g_6098[n].y0[j][m - 1];
            }
        for (j = 0; j < g_6098[n].f78; j++) {
            if (g_6098[n].f84[j] != 0) {
                g_6098[n].x1[j][0] += g_6098[n].f70;
                if (subgame_active == 0) {
                    if (g_6098[n].x1[j][0] > *(int *)&g_05a0 * 8)
                        g_6098[n].x1[j][0] = 0;
                    if (g_6098[n].x1[j][0] < 0)
                        g_6098[n].x1[j][0] = *(int *)&g_05a0 * 8;
                }
                g_6098[n].y1[j][0] += g_6098[n].f72;
                if (subgame_active == 0) {
                    if (g_6098[n].y1[j][0] > g_05a2 * 8)
                        g_6098[n].y1[j][0] = 0;
                    if (g_6098[n].y1[j][0] < 0)
                        g_6098[n].y1[j][0] = g_05a2 * 8;
                }
            }
        }
        v = g_6098[n].f76 & 0xf;
        if (v == 0xf && g_6098[n].f78 == 2) {
            g_6098[n].x1[0][0] += g_6098[n].f68 >> 2;
            g_6098[n].x1[1][0] -= g_6098[n].f68 >> 2;
            g_6098[n].y1[0][0] += g_6098[n].f6a >> 2;
            g_6098[n].y1[1][0] -= g_6098[n].f6a >> 2;
        }
    }
    if (g_6098[n].f74 <= g_6098[n].f76) {
        g_6098[n].f76 = -1;
        for (m = 5; m > -1; m--)
            for (j = 0; j < g_6098[n].f78; j++)
                PatBlt(g_13dc, g_6098[n].x0[j][m], g_6098[n].y0[j][m], w, w, BLACKNESS);
    }
    if (g_6098[n].f76 != -1 || g_9136 != 0)
        return 1;
    return 0;
}

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
} REC_1CC;
extern REC_1CC g_2414[][5][5];
extern int g_05a2;
extern POINT g_5144;
extern DWORD g_1e50;
extern int g_951a;
extern HDC g_5e98[4];
extern HGDIOBJ g_5ea0[4];
extern HBRUSH g_576c[20];
extern int g_0b6a;
extern int g_0b70[];
extern HDC g_39fc;
void far fn_07_342e(int n, int type, int idx);
void far fn_08_9694(int a, int type, int idx);
void far fn_07_1208(void);
void far fn_18_5350(POINT pt);
void far pascal fn_08_07d2(int a, int b, int c);
void far pascal fn_08_5ab0(int j);

/* Step explosion/effect i of the g_1e90 table [inferred]. */
/* @addr 8:3fbe */
void far pascal fn_08_3fbe(int i)
{
    int a;
    int b;
    int u8;
    int sz;
    int c;
    int m;
    int w;
    int t;
    int k;
    int v;
    POINT p;
    int pad[4];
    int found;

    if (g_1e90[i].f00 >= 0 && g_1e90[i].f02 >= g_1e90[i].f00) {
        if (g_1e90[i].f0a == 1 || g_1e90[i].f0a < 0) {
            if ((DWORD)g_1e90[i].f10 > g_1e50)
                return;
            if (g_1e90[i].f00 == 1) {
                g_5144 = g_5224[i];
                fn_10_754a(0x45, 0, 0, 3);
            }
        }
        if (g_1e90[i].f0a <= 5) {
            m = g_1e90[i].f00 - 1;
            sz = SC(m * 6 + 10);
            c = 0;
            if (g_1e90[i].f02 - 1 <= g_1e90[i].f00) {
                if (g_1e90[i].f0a != -250) {
                    PatBlt(g_13dc, g_5170[i].x - SC(26), g_5170[i].y - SC(26), SC(52), SC(52),
                           BLACKNESS);
                    if (g_1df8[g_9324][g_9646].f18 == 0 && g_951a == 0 && g_70ae[g_9646].fce != 0)
                        fn_07_1208();
                    if (g_1e90[i].f06 == g_9324 && g_1df8[g_9324][g_1e90[i].f08].f18 == 0
                        && g_1e90[i].f0a != 1)
                        fn_10_754a(0x6a, g_9324, g_1e90[i].f08, 1);
                    if (g_1e90[i].f0a != 1) {
                        t = g_1e90[i].f06;
                        k = g_1e90[i].f08;
                        p = fn_08_29ea(g_1df8[t][k].f04);
                        w = g_1df8[t][k].f22;
                        PatBlt(g_13dc, p.x, p.y, w, w, BLACKNESS);
                    }
                }
            } else {
                if (g_1e90[i].f0a > -1 && fn_08_7ba8(g_5170[i])) {
                    DWORD rop;

                    rop = SRCCOPY;
                    BitBlt(g_13dc, g_5170[i].x - (sz >> 1), g_5170[i].y - (sz >> 1), sz, sz,
                           g_39fc, SC(g_0b70[min(m, 7)]), 0, rop);
                }
                if (g_1e90[i].f00 % 6 == 0 && g_1e90[i].f0a != 1)
                    fn_08_5ab0(i);
            }
        } else {
            if (g_1e90[i].f00 == 1) {
                if (g_1e90[i].f0a == 6)
                    fn_07_342e(i, g_1e90[i].f06, g_1e90[i].f08);
                else
                    fn_08_9694(i, g_1e90[i].f06, g_1e90[i].f08);
                if (g_1e90[i].f06 <= g_9324)
                    PatBlt(g_13dc, g_1df8[g_1e90[i].f06][g_1e90[i].f08].f00.x,
                           g_1df8[g_1e90[i].f06][g_1e90[i].f08].f00.y,
                           g_1df8[g_1e90[i].f06][g_1e90[i].f08].f22,
                           g_1df8[g_1e90[i].f06][g_1e90[i].f08].f22, BLACKNESS);
            }
            if (g_1e90[i].f00 == 5 && g_1e90[i].f0a == 6)
                fn_08_5ab0(i);
            for (a = 0; a < 5; a += g_1e90[i].f04) {
                for (b = 0; b < 5; b += g_1e90[i].f04) {
                    fn_08_07d2(i, a, b);
                    if (g_1e90[i].f0a == 6)
                        v = g_1df8[g_1e90[i].f06][g_1e90[i].f08].f24;
                    if (g_1e90[i].f0a == 6) {
                        BitBlt(g_13dc, g_2414[i][a][b].p.x, g_2414[i][a][b].p.y,
                               g_1e90[i].f0c, g_1e90[i].f0c, g_5e98[i],
                               g_1e90[i].f0c * a + v, g_1e90[i].f0c * b + v, SRCCOPY);
                    } else {
                        SelectObject(g_13dc, g_576c[g_1e90[i].f0e + g_0b6a]);
                        PatBlt(g_13dc, g_2414[i][a][b].p.x, g_2414[i][a][b].p.y,
                               g_1e90[i].f0c, g_1e90[i].f0c, PATCOPY);
                    }
                    PatBlt(g_13dc, g_2414[i][a][b].q.x, g_2414[i][a][b].q.y,
                           g_1e90[i].f0c, g_1e90[i].f0c, BLACKNESS);
                    if (g_1e90[i].f02 - g_1e90[i].f00 == 1) {
                        PatBlt(g_13dc, g_2414[i][a][b].p.x, g_2414[i][a][b].p.y,
                               g_1e90[i].f0c, g_1e90[i].f0c, BLACKNESS);
                        if (g_951a == 0)
                            fn_07_1208();
                    }
                    g_2414[i][a][b].s.x += g_2414[i][a][b].f10 * g_1e90[i].f00 * g_1e90[i].f00 * 9
                        / (g_1e90[i].f02 * g_1e90[i].f02) + g_2414[i][a][b].f0c;
                    if (g_2414[i][a][b].s.x > *(int *)&g_05a0 * 8)
                        g_2414[i][a][b].s.x = 0;
                    if (g_2414[i][a][b].s.x < 0)
                        g_2414[i][a][b].s.x = *(int *)&g_05a0 * 8;
                    g_2414[i][a][b].s.y += g_2414[i][a][b].f12 * g_1e90[i].f00 * g_1e90[i].f00 * 9
                        / (g_1e90[i].f02 * g_1e90[i].f02) + g_2414[i][a][b].f0e;
                    if (g_2414[i][a][b].s.y > g_05a2 * 8)
                        g_2414[i][a][b].s.y = 0;
                    if (g_2414[i][a][b].s.y < 0)
                        g_2414[i][a][b].s.y = g_05a2 * 8;
                }
            }
        }
        g_1e90[i].f00++;
    }
    if (g_1e90[i].f02 <= g_1e90[i].f00) {
        found = 0;
        g_1e90[i].f00 = -1;
        for (a = 44; a >= 0; a--) {
            if (g_1e90[a].f00 != -1) {
                g_9434 = a;
                found = 1;
                break;
            }
        }
        if (found == 0)
            g_9434 = 0;
        g_9430 = g_9430 - 1 < 0 ? 0 : g_9430 - 1;
        if (subgame_active != 0)
            fn_18_5350(g_5170[i]);
        if (i < 4 && g_1e90[i].f0a == 6 && g_5e98[i] != 0) {
            if (g_1e90[i].f06 == 1) {
                SelectObject(g_5e98[i], g_5ea0[i]);
                DeleteDC(g_5e98[i]);
            }
            g_5e98[i] = 0;
        }
    }
}

/* The object records seen from DS:70a0 and DS:7092 (below g_70ae). */
extern struct { int f00; char p02[0x15a - 2]; } g_70a0[];
extern struct { int f00; char p02[0x15a - 2]; } g_7092[];
/* The class records (0xad bytes) seen from DS:96da [inferred]. */
#pragma pack(1)
typedef struct {
    int f00[4];                 /* +00 */
    int f08[4];                 /* +08 */
    char p10[0x1e - 0x10];
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    char p24[2];
    int f26;                    /* +26 */
    char p28[0x3a - 0x28];
    int f3a;                    /* +3a */
    char p3c[0x8b - 0x3c];
    char f8b[0xad - 0x8b];      /* +8b: name */
} REC_ADB;
#pragma pack()
extern REC_ADB g_96da[];
typedef struct {
    char p00[0x30];
    char f30[8];                /* +30 (read as f30[k + 4]) */
    char p38[0x7c - 0x38];
} REC_7C;
extern REC_7C far *g_6e24;
typedef struct {
    int f00;                    /* +00 */
    char p02[4];
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    char p0e[0x24 - 0xe];
} REC_24;
extern REC_24 g_52fe[];
extern int g_940a;
extern int g_0b0a;
extern int g_9134;
extern int g_943e;
extern int g_9440;
extern DWORD g_52d8;
extern DWORD g_8e30;
extern int g_92e8;
extern int g_9000;
extern int flow_interactive;        /* DS:95bc */
extern int g_104c;
extern int g_9530;
void far fn_04_5e8e(int i, int n, int a, int b);
void far fn_10_7944(int a, int b, int c, int d, LPCSTR e);
void far fn_13_6716(int n);
void far self_destruct_ship(int unused, int i);
void far fn_13_33d6(int n);
void far fn_18_633c(void);
void far fn_08_2cd8(int a, int b);
void far fn_12_274a(int type, int idx);

/* Apply dmg points of damage to ship i, hit by object (g_943a, g_943c)
 * [inferred]; returns 1 when the ship is destroyed. */
/* @addr 8:45e0 */
int far fn_08_45e0(int unused, int i, int dmg)
{
    int vx;
    int vy;
    int px;
    int py;
    int sz;
    POINT dv;
    POINT r;
    int u16;
    int k;
    int u1a;
    int cls;
    int pad[2];

    if (g_70ae[i].f129 == 1 && subgame_active == 0)
        return 0;
    if (i == g_9646 && g_104c != 0)
        return 0;
    if (g_70ae[i].fce == 0 && !(g_943a == g_9324 && i == g_943c) && g_943a != 11) {
        if (g_70ae[i].f66 - 5500 < g_1e50)
            fn_12_274a(g_9324, i);
        if (subgame_active != 0) {
            g_9530 = 6;
            fn_18_633c();
        }
        return 0;
    }
    cls = g_70ae[i].f30;
    dmg = dmg * 7 / 8;
    if (i == g_9646) {
        dmg = (g_9000 + 6) * dmg / 8;
        if (flow_interactive == 0) {
            g_5078 += (long)dmg * min(g_5078, 35000) / -4000;
            if (g_5078 > 200000)
                g_5078 += (long)dmg * g_5078 / -6000;
        } else
            g_5078 += (long)dmg * min(g_5078, 35000) / -9000;
    } else if (g_92e8 != 0 && i == 1)
        g_8e30 = g_1e50 + 20000;
    if (g_943a == 0x1e) {
        vx = g_6098[g_943c].f70;
        vy = g_6098[g_943c].f72;
        px = g_6098[g_943c].x1[0][0];
        py = g_6098[g_943c].y1[0][0];
        sz = 2;
        if (g_6098[g_943c].f7a == g_9324 && g_6098[g_943c].f7c != i)
            fn_04_5e8e(i, g_6098[g_943c].f7c, dmg, 1);
        if (g_6098[g_943c].f7a == g_9324 && g_6098[g_943c].f7c == g_9646 && g_9134 == 0
            && i != g_9646) {
            g_943e = g_9324;
            g_9440 = i;
            g_52d8 = g_1e50;
        }
    } else {
        vx = g_1df8[g_943a][g_943c].f0c;
        vy = g_1df8[g_943a][g_943c].f0e;
        px = g_1df8[g_943a][g_943c].f04.x;
        py = g_1df8[g_943a][g_943c].f04.y;
        sz = g_1df8[g_943a][g_943c].f22;
        dmg = dmg * 3 / 4;
        if (g_9320 == 6 && g_943a == 14)
            dmg /= 2;
    }
    g_70ae[i].f12c = g_1df8[g_9324][i].f04;
    g_70ae[i].f130 = g_1e50;
    dv.x = vx - g_1df8[g_9324][i].f0c * 10;
    dv.y = g_1df8[g_9324][i].f0e * 10 - vy;
    r.x = sz / 2 - g_1df8[g_9324][i].f22 / 2 - g_1df8[g_9324][i].f04.x + px;
    r.y = sz / 2 + (g_1df8[g_9324][i].f04.y - g_1df8[g_9324][i].f22 / 2) - py;
    if ((long)r.y * dv.x - (long)r.x * dv.y > 0)
        g_1df8[g_9324][i].f26 = 1;
    else
        g_1df8[g_9324][i].f26 = -1;
    if (g_0b0a != 0)
        fn_10_754a(7, g_9324, i, 1);
    if (g_70ae[i].fcc != 0)
        g_1df8[g_9324][i].f1e = max(dmg * 4 / 3, 1);
    else if (g_70ae[i].fca != 0)
        g_1df8[g_9324][i].f1e = max(dmg * 3, 2);
    else
        g_1df8[g_9324][i].f1e = max(dmg * 2, 1);
    if (g_0b0a == 0)
        fn_10_7944(g_96da[cls].f26, g_9324, i, 1, g_96da[cls].f8b);
    if (sz == 2) {
        for (k = 0; k < 4; k++) {
            dmg = g_1df8[g_9324][i].f1e / g_96da[cls].f00[k];
            if (g_70ae[i].fb8 != -1)
                dmg = dmg * (10 - g_6e24[g_70ae[i].fb8].f30[k + 4]) / 10;
            dmg = max(dmg, 1);
            g_70ae[i].f08[k] -= dmg;
        }
    } else {
        for (k = 0; k < 4; k++) {
            dmg = g_1df8[g_9324][i].f1e / g_96da[cls].f08[k];
            if (g_70ae[i].fb8 != -1)
                dmg = dmg * (20 - g_6e24[g_70ae[i].fb8].f30[k + 4] * 3) / 20;
            dmg = max(dmg, 1);
            g_70ae[i].f08[k] -= dmg;
        }
    }
    for (k = 0; k < 4; k++)
        g_70ae[i].f08[k] = max(g_70ae[i].f08[k], 0);
    if (g_70ae[i].f08[3] == 0 && g_96da[cls].f20 == 3) {
        if (g_70ae[i].f8f != 0 || g_70ae[i].f8e != 0) {
            g_70a0[i].f00 = 0;
            g_70ae[i].fcc = 0;
            if (g_70ae[i].f8f != 0)
                fn_08_2cd8(i, 1);
            if (g_70ae[i].f8e != 0)
                fn_08_2cd8(i, 0);
            g_70ae[i].f02 = g_96da[cls].f22 - 14;
            g_70ae[i].f04 = 7;
            g_70ae[i].f06 = min(g_70ae[i].f06, 1);
            g_70ae[i].fc2 = 1;
        }
    } else if (g_70ae[i].f08[3] < 50 && g_96da[cls].f20 == 3 && g_70ae[i].f8e != 0
               && g_70ae[i].f8f != 0) {
        g_70a0[i].f00 = 0;
        g_70ae[i].fcc = 0;
        if (g_1df8[g_9324][i].f26 == 1) {
            fn_08_2cd8(i, 1);
            if (g_70ae[i].f06 == 2) {
                g_70ae[i].fc2 = 1;
                g_70ae[i].fc3 = 0;
            }
        } else {
            fn_08_2cd8(i, 0);
            if (g_70ae[i].f06 == 2) {
                g_70ae[i].fc3 = 1;
                g_70ae[i].fc2 = 0;
            }
        }
        g_1df8[g_9324][i].f26 = 0;
    }
    if (g_70ae[i].f08[2] == 0 && g_96da[cls].f1e == 2 && g_7092[i].f00 != 0) {
        g_7092[i].f00 = 0;
        fn_13_6716(i);
    }
    if (g_70ae[i].f08[0] < 1 && !(g_943a == g_9324 && i == g_943c) && g_943a != 11) {
        self_destruct_ship(g_9324, i);
        for (k = 0; k < g_940a; k++) {
            if (g_52fe[k].f06 == g_9324 && g_52fe[k].f08 == i) {
                g_52fe[k].f00 = 15;
                if (g_943a == 0x1e) {
                    g_52fe[k].f0a = g_6098[g_943c].f7a;
                    g_52fe[k].f0c = g_6098[g_943c].f7c;
                } else if (g_943a == 6) {
                    g_52fe[k].f0a = g_66e4[g_943c].f04;
                    g_52fe[k].f0c = g_66e4[g_943c].f06;
                }
            }
        }
        return 1;
    }
    g_0b0a = 0;
    fn_13_33d6(i);
    return 0;
}

extern int g_9150;
extern int g_9454;
/* 0x14-byte records at DS:5a4c [inferred]. */
typedef struct {
    char p00[4];
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    char p0c[0x14 - 0x0c];
} REC_14C;
extern REC_14C g_5a4c[];
void far fn_10_7944(int a, int b, int c, int d, LPCSTR e);
POINT far pascal fn_08_2bbe(POINT pt);
void far pascal fn_08_698a(int a);
void far pascal fn_08_6a44(int a);

/* Collision response between objects (g_944a, g_944e) and (g_944c, g_9450)
 * [inferred]; ref is the object the caller asks about, pvx/pvy get its new
 * speed; returns -1 when nothing happens. */
/* @addr 8:546c */
int far pascal fn_08_546c(WORD ref, int far *pvx, int far *pvy, int m1, int m0)
{
    POINT p;
    int res;
    int t;
    int n;

    res = 1;
    t = HIBYTE(ref);
    n = LOBYTE(ref);
    if (g_944a == g_9328) {
        if (g_5a4c[g_944e].f08 == g_944c && g_5a4c[g_944e].f0a == g_9450)
            return -1;
        if (g_944c == g_9324)
            fn_10_7944(g_96da[g_70ae[g_9450].f30].f26, g_944c, g_9450, 1,
                       g_96da[g_70ae[g_9450].f30].f8b);
        else
            fn_10_754a(g_1df8[g_944c][g_9450].f42, g_944c, g_9450, 1);
        g_5a4c[g_944e].f08 = g_944c;
        g_5a4c[g_944e].f0a = g_9450;
    }
    if (g_944c == g_9328) {
        if (g_5a4c[g_9450].f08 == g_944a && g_5a4c[g_9450].f0a == g_944e)
            return -1;
        if (g_944a == g_9324)
            fn_10_7944(g_96da[g_70ae[g_944e].f30].f26, g_944a, g_944e, 1,
                       g_96da[g_70ae[g_944e].f30].f8b);
        else
            fn_10_754a(g_1df8[g_944a][g_944e].f42, g_944a, g_944e, 1);
        g_5a4c[g_9450].f08 = g_944a;
        g_5a4c[g_9450].f0a = g_944e;
    }
    if (g_9e49 >= 3 && g_9e49 <= 6) {
        if (g_944c == 7 && g_944a == g_9324 && g_944e == g_952e)
            return -1;
        if (g_944a == 7 && g_944c == g_9324 && g_9450 == g_952e)
            return -1;
    }
    if (t == g_944a && n == g_944e) {
        *(POINT *)&g_52dc = *(POINT far *)&g_1df8[g_944c][g_9450].f0c;
        *(POINT *)&g_52e0 = *(POINT far *)&g_1df8[g_944a][g_944e].f0c;
        if (g_1df8[g_944c][g_9450].f1a != 0)
            g_52e8 = g_1df8[g_944c][g_9450].f00;
        else
            g_52e8 = fn_08_29ea(g_1df8[g_944c][g_9450].f04);
        object_masses[1] = m0;
        if (g_944a == 0 && g_944c == 2)
            object_masses[0] *= 10;
        if (g_1df8[g_944a][g_944e].f54 != 0)
            object_masses[0] = 20000;
        if (g_944c == g_9324 && g_70ae[g_9450].fcc == 0 && g_70ae[g_9450].fca == 0
            && g_96da[g_70ae[g_9450].f30].f3a != 0 && g_1df8[g_944a][g_944e].f53 != 0
            && g_1df8[g_944a][g_944e].f2f >= 0)
            return -1;
        if (g_944a == g_9324 && g_70ae[g_944e].fcc == 0 && g_70ae[g_944e].fca == 0
            && g_96da[g_70ae[g_944e].f30].f3a != 0 && g_1df8[g_944c][g_9450].f53 != 0
            && g_1df8[g_944c][g_9450].f2f >= 0)
            return -1;
        if (subgame_active == 0) {
            object_sizes[0] = (object_sizes[0] >> g_9150) + 1;
            object_sizes[1] = (object_sizes[1] >> g_9150) + 1;
        }
        if (g_9328 != g_944c && g_9328 != g_944a)
            res = fn_10_7dd4(&g_52dc, &g_52de, &g_52e0, &g_52e2, &g_52e8.x, &g_52e8.y,
                             &g_52e4.x, &g_52e4.y, object_sizes[1], object_sizes[0],
                             object_masses[1], object_masses[0], &g_9436, &g_9438);
        if (res == 0) {
            fn_08_698a(0);
            return -1;
        }
        *pvx = g_52dc;
        *pvy = g_52de;
        p = g_1df8[g_944c][g_9450].f04;
        if (g_1df8[g_944c][g_9450].f54 == 0)
            g_1df8[g_944c][g_9450].f04 = fn_08_2bbe(g_52e8);
        g_9438 += g_9454 * 5;
        fn_08_698a(1);
        return g_9436;
    } else {
        *(POINT *)&g_52dc = *(POINT far *)&g_1df8[g_944c][g_9450].f0c;
        *(POINT *)&g_52e0 = *(POINT far *)&g_1df8[g_944a][g_944e].f0c;
        if (g_1df8[g_944a][g_944e].f1a != 0)
            g_52e4 = g_1df8[g_944a][g_944e].f00;
        else
            g_52e4 = fn_08_29ea(g_1df8[g_944a][g_944e].f04);
        object_masses[0] = m0;
        if (g_1df8[g_944a][g_944e].f54 != 0)
            object_masses[0] = 20000;
        if (g_944c == g_9324 && g_70ae[g_9450].fcc == 0 && g_70ae[g_9450].fca == 0
            && g_96da[g_70ae[g_9450].f30].f3a != 0 && g_1df8[g_944a][g_944e].f53 != 0
            && g_1df8[g_944a][g_944e].f2f >= 0)
            return -1;
        if (g_944a == g_9324 && g_70ae[g_944e].fcc == 0 && g_70ae[g_944e].fca == 0
            && g_96da[g_70ae[g_944e].f30].f3a != 0 && g_1df8[g_944c][g_9450].f53 != 0
            && g_1df8[g_944c][g_9450].f2f >= 0)
            return -1;
        if (subgame_active == 0) {
            object_sizes[0] = (object_sizes[0] >> g_9150) + 1;
            object_sizes[1] = (object_sizes[1] >> g_9150) + 1;
        }
        if (g_9328 != g_944c && g_9328 != g_944a)
            res = fn_10_7dd4(&g_52dc, &g_52de, &g_52e0, &g_52e2, &g_52e8.x, &g_52e8.y,
                             &g_52e4.x, &g_52e4.y, object_sizes[1], object_sizes[0],
                             object_masses[1], object_masses[0], &g_9436, &g_9438);
        if (res == 0) {
            fn_08_6a44(0);
            return -1;
        }
        *pvx = g_52e0;
        *pvy = g_52e2;
        p = g_1df8[g_944c][g_9450].f04;
        if (g_1df8[g_944c][g_9450].f54 == 0)
            g_1df8[g_944c][g_9450].f04 = fn_08_2bbe(g_52e8);
        g_9436 += g_9454 << 2;
        fn_08_6a44(1);
        return g_9438;
    }
}

/* Views and declarations for fn_08_5df2. */
extern struct { int f00; char p02[0x15a - 2]; } g_70ac[];  /* object records from DS:70ac */
extern struct { int f00; char p02[0x15a - 2]; } g_70a8[];  /* object records from DS:70a8 */
/* 0x20-byte records at DS:65cc: links between two objects [inferred]. */
typedef struct {
    char p00[4];
    int t2;                     /* +04 */
    int i2;                     /* +06 */
    char p08[0x0e - 0x08];
    int f0e;                    /* +0e */
    char p10[0x20 - 0x10];
} REC_20;
extern REC_20 g_65cc[];
/* 0x50-byte records at DS:2f4c [inferred]. */
typedef struct {
    char p00[0x2c];
    int f2c;                    /* +2c */
    char p2e[0x50 - 0x2e];
} REC_50;
extern REC_50 g_2f4c[];
/* 0x34-byte records at DS:8560 [inferred]. */
typedef struct { char p00[0x0a]; int f0a; char p0c[0x34 - 0x0c]; } REC_34C;
extern REC_34C g_8560[];
/* The 0x34-byte records of DS:3d5a from DS:3d50 [inferred]. */
typedef struct { char p00[4]; DWORD f04; char p08[0x34 - 0x08]; } REC_34D;
extern REC_34D g_3d50[];
extern char g_9eb9[];
extern int g_9322;
extern int g_0a72;
extern int g_0a74;
extern HDC g_93ce;
extern HDC g_93d0;
extern char g_a198;
extern int g_9432;
extern int g_934a;
extern char g_9eb5;
void far fn_03_06ec(int n, int kind, int target, int d);
void far fn_13_b6f2(int a, int t);
void far fn_11_947a(int type, int n, int k);
void far fn_13_2714(int a, int b, int c, int d, int e, int f);
void far fn_04_7d36(int a, int b, int c);
void far fn_12_3498(int a, int b, int c);
HBITMAP far world_map(int w, int h, int a, int b, int c, int d, int e);
int far fn_13_2688(int a, int b);
void far pascal fn_13_2e60(int a, int b, int c);
void far fn_04_7636(int n, int type, int idx, int quiet);
void far fn_08_99ce(int a, int b, int c, int d, int e);
void far fn_07_2080(int a, int b);
void far fn_08_9028();       /* old-style: callers pass ints or a PAIR */

/* Object (type, idx) takes dmg points of damage from object (stype, sidx):
 * finds the responsible owner, scores, applies it through the record's
 * damage callback (f5e) and returns that callback's result [inferred]. */
/* near-match 94%: 8:5df2. Only the cross-jumped f66 store at the end
 * differs: the game keeps the copy in the flag8 arm, CL here the last. */
int far fn_08_5df2(int type, int idx, int stype, int sidx, int dmg)
{
    int ret;
    int ok;
    int flag8;
    int neg;
    int mass;
    int smass;
    int otype;
    int oidx;
    int u1;
    int u2;
    int j;
    int k;
    int v;

    ok = 1;
    flag8 = 0;
    mass = g_1df8[type][idx].f44;
    if (stype == 0x1f)
        smass = 20000;
    else
        smass = g_1df8[stype][sidx].f44;
    neg = 0;
    if (dmg < -1) {
        neg = 1;
        dmg = -dmg;
    }
    if (stype <= g_9324) {
        if (dmg > 2000 && dmg < 3000) {
            dmg -= 2000;
            flag8 = 1;
            if (stype == g_9324 && g_96ea[g_70ae[sidx].f30].f20 == 7)
                dmg = 1;
        }
        if (dmg == -1)
            return 0;
        if (g_70ac[g_9646].f00 > 2 && stype == g_9324 && sidx == g_9646
            && (type == g_934a || type == 8 || type == 9) && g_9134 < 2) {
            fn_03_06ec(g_9646, 7, 0, 13);
            fn_13_b6f2(g_9646, 9);
        }
        otype = -1;
        if (g_1df8[stype][sidx].f32 == g_9324) {
            otype = g_9324;
            oidx = g_1df8[stype][sidx].f34;
        }
        if (g_1df8[type][idx].f32 == g_9324) {
            otype = g_9324;
            oidx = g_1df8[type][idx].f34;
        }
        if (g_1df8[type][idx].f32 != -1) {
            if (smass + 100 > mass) {
                if (g_65cc[g_1df8[type][idx].f30].f0e)
                    g_65cc[g_1df8[type][idx].f30].f0e = 0;
                else
                    g_65cc[g_1df8[type][idx].f30].f0e = 1;
            }
            if (rand() % 12 + 30 < dmg && dmg != 100 && type == g_9324)
                fn_11_947a(g_65cc[g_1df8[type][idx].f30].t2, g_65cc[g_1df8[type][idx].f30].i2, 2);
        }
        if (stype == g_9328) {
            if (g_1df8[g_9328][sidx].f44 == 120)
                dmg = max(dmg * 2, 20);
            otype = g_5a4c[sidx].f04;
            oidx = g_5a4c[sidx].f06;
        }
        if (stype == 6) {
            otype = g_66e4[sidx].f04;
            oidx = g_66e4[sidx].f06;
            if (g_2f4c[g_66e4[sidx].f00].f2c == 6 && type == g_9324
                && g_2f4c[g_70ae[idx].f9a[g_70a8[idx].f00]].f2c == 6)
                ok = 0;
        }
        if (stype == 10 || g_1df8[stype][sidx].f32 != -1) {
            otype = g_1df8[stype][sidx].f32;
            oidx = g_1df8[stype][sidx].f34;
        }
        if (otype == -1) {
            otype = stype;
            oidx = sidx;
        }
        if (otype == 9 || otype == 2 || otype == g_9324) {
            if (otype == g_9324) {
                if (g_70ae[oidx].f1a == 1 && g_70ae[oidx].f14 == type && g_70ae[oidx].f16 == idx)
                    g_70ae[oidx].f86 = g_1e50;
                for (k = 0; k <= g_9316; k++)
                    if (k != oidx && g_70ae[k].fce && g_70ae[k].f14 == type
                        && g_70ae[k].f16 == idx && g_70ae[k].f1a == 1)
                        fn_13_2714(k, oidx, 5, 10, 0, -1);
            }
            if ((type == g_9324 || type == 0) && g_0b0c
                && (otype == g_9324
                    || otype == 2 && !(g_52fe[oidx].f06 == type && g_52fe[oidx].f08 == idx))) {
                for (k = 0; k < g_940a; k++)
                    if (g_52fe[k].f06 == type && g_52fe[k].f08 == idx)
                        fn_08_9028(k, 10, otype, oidx);
                if (otype == g_9324 && type == g_9324) {
                    if (stype != g_9324 || flag8)
                        fn_04_5e8e(idx, oidx, dmg, 1);
                    if (oidx == g_9646 && g_70ae[idx].f1a == 4 && g_70ae[idx].f16 == oidx)
                        g_9432 += dmg;
                    fn_04_7d36(oidx, idx, dmg);
                }
                if (otype == g_9324 && oidx == g_9646 && stype != 10 && type != g_9324)
                    /* 8:81f8 is defined with char parameters, but this
                     * call passes whole ints [inferred: the original called
                     * it before its definition, without a prototype] */
                    ((void (far *)(int, int))fn_08_81f8)(type, idx);
            }
            if (otype == g_9324 && oidx == g_9646 && !(type == g_9324 && idx == g_9646)) {
                g_943e = type;
                g_9440 = idx;
                g_52d8 = g_1e50;
                if (stype != g_9324 && type == g_9324)
                    g_9432 += dmg / 2;
                if (stype != g_9324 && (type == g_934a || type == 8))
                    g_9432 += dmg / 4;
                if (stype != g_9324 && type == 0 && g_1df8[0][idx].f53 == 1)
                    g_9432 += dmg / 3;
            }
        }
        if (g_1df8[type][idx].f53) {
            if (stype == 2)
                ok = 0;
            if (stype == g_9324 && g_70a0[sidx].f00 < 6 && g_96ea[g_70ae[sidx].f30].f2a
                && g_70ae[sidx].fca == 0 && g_1df8[type][idx].f2f >= 0 && !neg && !flag8)
                ok = 0;
            if (flag8 && otype == 9)
                ok = 1;
        }
        if (type == 11 && stype == g_9324 && g_8560[idx].f0a == sidx && g_70ae[sidx].fce == 0)
            ok = 0;
        if (type == g_9324 && g_70ae[idx].fce == 0 && stype == 11 && g_8560[sidx].f0a == idx)
            ok = 0;
        if (type == 2 && (g_52fe[idx].f06 == stype && g_52fe[idx].f08 == sidx || stype == 2))
            ok = 0;
        if (type == 2)
            dmg = -dmg;
        ret = 0;
        if (stype == 10) {
            fn_12_3498(type, idx, sidx);
            ok = 0;
        }
    } else
        otype = stype;
    if (ok) {
        if (type != g_9324)
            fn_10_754a(g_1df8[type][idx].f42, type, idx, 1);
        ret = g_1df8[type][idx].f5e(type, idx, dmg);
        if (otype == g_9324 && oidx == g_9646 && !(type == g_9324 && idx == g_9646))
            fn_08_7be8(type, idx, dmg, ret);
        if (ret) {
            if (!(otype == g_9324 && oidx == g_9646) && !(type == g_9324 && idx == g_9646))
                fn_08_7ce0(type, idx, dmg, ret);
            v = 0;
            if (otype == g_9324) {
                if (stype != 10 && g_70ae[oidx].f14 == type && g_70ae[oidx].f16 == idx
                    && g_70ae[oidx].f1a == 1) {
                    if (type == 0 && g_1df8[0][idx].f53 == 1)
                        fn_13_b6f2(oidx, 1);
                    if (type == 8 && g_3d5a[idx].f00 == 16)
                        fn_13_b6f2(oidx, 6);
                }
                if (g_70ae[oidx].f34 >= 2) {
                    if (g_70ae[oidx].f34 <= 4 && g_70ae[oidx].f3a != oidx
                        && g_70ae[oidx].f36 == type && g_0b0c) {
                        if (type == 9) {
                            fn_03_06ec(oidx, g_9324, g_70ae[oidx].f3a, 0x75);
                            fn_13_2714(g_70ae[oidx].f3a, oidx, 15, 40, 0, 6);
                            if (g_9134 == 0 || oidx != g_9646 && flow_interactive == 0)
                                g_70ae[oidx].f34 = 0;
                            v = 1;
                        } else if (g_70ae[oidx].f38 == idx) {
                            fn_03_06ec(oidx, g_9324, g_70ae[oidx].f3a, 0x76);
                            fn_13_2714(g_70ae[oidx].f3a, oidx, 50, 90, 0, 6);
                            if (g_9134 == 0 || oidx != g_9646 && flow_interactive == 0)
                                g_70ae[oidx].f34 = 0;
                            v = 1;
                        }
                    }
                } else if (g_70ae[oidx].f34 == 1 && type == g_9324) {
                    if (g_70ae[idx].f14 == g_9324 && g_70ae[oidx].f3a == g_70ae[idx].f16
                        && g_70ae[idx].f1a == 1) {
                        fn_03_06ec(oidx, g_9324, g_70ae[oidx].f3a, 0x77);
                        fn_13_2714(g_70ae[oidx].f3a, oidx, 60, 120, 0, 8);
                        v = 1;
                    }
                } else {
                    for (j = 0; j <= g_9316; j++)
                        if (j != oidx && g_70ae[j].fce && g_70ae[j].f14 == type
                            && g_70ae[j].f16 == idx && g_70ae[j].f1a == 1) {
                            fn_13_2714(j, oidx, 30, 50, 0, 6);
                            fn_03_06ec(oidx, g_9324, j, 0x77);
                        }
                }
            }
            if (type == 8 && g_9320 == 6 && g_9eb9[g_9322] + g_9318 * 2 <= idx) {
                world_map(g_0a72, g_0a74, 1 - g_9eb5, g_9322, 8, idx, 0);
                BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
            }
            if (type == 0 && g_1df8[0][idx].f53 == 2 && otype == g_9324 && oidx == g_9646) {
                fn_03_06ec(oidx, 7, 0, 0x5e);
                g_1e58 += 3000;
            }
            if (type == 9 && otype == g_9324 && oidx == g_9646) {
                g_1e58 += 1000;
                if (v == 0)
                    fn_03_06ec(g_9646, 7, 0, 0x5b);
            }
            fn_07_2080(type, idx);
            if (otype == g_9324 && type == g_9324) {
                if (oidx == g_9646)
                    g_9432 += 200;
                fn_13_2714(idx, oidx, -50, -150, 1, -1);
                for (j = 0; j < g_9316; j++)
                    if (fn_13_2688(j, idx) > 0)
                        fn_13_2e60(j, oidx, 4);
            }
            if (type == g_9324)
                fn_04_7636(idx, otype, oidx, v);
            g_70ae[g_9646].f138 = g_1e50 - 1;
        }
    }
    fn_08_99ce(type, idx, otype, oidx, ret);
    if (type == g_9324) {
        if (ok && g_70ae[idx].fce) {
            g_70ae[idx].fc4 = 1;
            if (g_1df8[type][idx].f26 == 0)
                g_1df8[type][idx].f26 = 1;
            if (flag8)
                g_70ae[idx].f66 = max(dmg * 25, 900) + g_1e50;
            else if (stype == 8 && g_3d5a[sidx].f00 == -3)
                g_70ae[idx].f66 = max(dmg * 6, 300) + g_1e50;
            else {
                v = max(dmg * 12, 600);
                if (subgame_active) {
                    if (g_90f4 == 1)
                        g_70ae[idx].f66 = (g_a198 + 3) * v / 6 + g_1e50;
                    else
                        g_70ae[idx].f66 = v * (g_a198 + 3) / 12 + g_1e50;
                } else
                    g_70ae[idx].f66 = v + g_1e50;
            }
        }
    } else if (type == 8) {
        if (flag8)
            g_3d50[idx].f04 = dmg * 200 + g_1e50;
        else
            g_3d50[idx].f04 = dmg * 140 + g_1e50;
    }
    return ret;
}

/* 0x14-byte records at DS:4d90 (as in seg09b.c) [inferred]. */
typedef struct { char p00[3]; char f03; char p04[0x14 - 4]; } REC_14D;
extern REC_14D g_4d90[];
void far fn_18_3f02(int x, int y, int k);

/* Shot group n against object (t, i), k the group's damage [inferred]:
 * 0 no hit, 1 hit and absorbed, 2 hit and the target reacted. wrap is
 * read uninitialised (as in the original). */
/* @addr 8:6f3c */
int far pascal fn_08_6f3c(int t, int i, int n, int k)
{
    POINT c;
    POINT vel;
    POINT pos;
    POINT d;
    long u1;
    long u2;
    int ret;
    int wrap;
    int v;
    int ok;
    int hit;
    int j;
    int otype;
    int oidx;
    int m;
    int dist;
    long l;

    if (g_1df8[t][i].f18)
        return 0;
    if (g_1df8[t][i].f55[n] > 1 && g_6098[n].f82 == 0 && subgame_active == 0) {
        g_1df8[t][i].f55[n]--;
        return 0;
    }
    if (g_1df8[t][i].f2e && (t != g_9324 || g_70ae[i].f10 != 2))
        return 0;
    otype = g_6098[n].f7a;
    oidx = g_6098[n].f7c;
    if (otype == t && oidx == i && g_6098[n].f76 < 24)
        return 0;
    pos = fn_08_29ea(g_1df8[t][i].f04);
    for (j = 0; j < g_6098[n].f78; j++) {
        if (g_6098[n].f84[j]) {
        d.x = g_5168[j].x - pos.x;
        d.y = g_5168[j].y - pos.y;
        if (g_1df8[t][i].f22 > d.x && d.x > -1 && g_1df8[t][i].f22 > d.y && d.y > -1)
            hit = 1;
        else {
            if ((-25 << g_9156) > d.x || (40 << g_9156) < d.x
                || (-25 << g_9156) > d.y || (40 << g_9156) < d.y) {
                dist = fn_08_35d0(g_1df8[t][i].f22 / 2 + d.x, g_1df8[t][i].f22 / 2 + d.y) - 5;
                if (dist == 0)
                    dist = 1;
                l = ((g_1df8[t][i].f0e / 5 - g_6098[n].f72) * d.y
                     + (g_1df8[t][i].f0c / 5 - g_6098[n].f70) * d.x) / (dist * 8);
                if (l > 0) {
                    g_1df8[t][i].f55[n] = (char)(dist / l / (g_9208 + 2));
                    hit = 0;
                } else {
                    g_1df8[t][i].f55[n] = dist / ((g_9208 + 4) * 10) - g_9208 + 10;
                    hit = 0;
                }
            } else {
                g_1df8[t][i].f55[n] = 0;
                hit = 0;
            }
        }
        if (hit) {
        k = 14 - g_6098[n].f76 * 14 / g_6098[n].f74;
        if (g_6098[n].f76 < 20)
            k = 23;
        if (g_6098[n].f7a == g_9324 && g_6098[n].f7c == g_9646)
            k = k * 3 / 2;
        else if (g_6098[n].f7a == g_9324 && g_96ea[g_70ae[g_6098[n].f7c].f30].f20 == 7
                 && g_70ae[g_6098[n].f7c].f40 == 0)
            k = k * 5 / 2;
        if (g_6098[n].f7a == g_9324)
            k = g_96ea[g_70ae[g_6098[n].f7c].f30].f1a * k / 250;
        if (g_92e8 && oidx != g_9646)
            k *= 3;
        if (g_6098[n].f7a == g_9324 && g_70ae[g_6098[n].f7c].fb8 != -1)
            k = (g_6e24[g_70ae[g_6098[n].f7c].fb8].f30[2] + 5) * k * 20 / 100;
        g_944a = t;
        g_944e = i;
        g_943a = 30;
        g_944c = 30;
        g_943c = n;
        g_9450 = n;
        if (g_6098[n].f7a == g_9324 && g_6098[n].f7c == g_9646 && t != g_9324)
            /* as in 8:5df2: whole ints to a char-parameter function */
            ((void (far *)(int, int))fn_08_81f8)(t, i);
        c.x = g_6098[n].f70 * 5;
        c.y = g_6098[n].f72 * 5;
        if (wrap) {
            if (g_6098[n].x1[j][0] < 1000 && g_1df8[t][i].f04.x > 5000)
                g_6098[n].x1[j][0] += *(int *)&g_05a0 * 8;
            else if (g_6098[n].x1[j][0] > 5000 && g_1df8[t][i].f04.x < 1000)
                g_6098[n].x1[j][0] -= *(int *)&g_05a0 * 8;
            if (g_6098[n].y1[j][0] < 1000 && g_1df8[t][i].f04.y > 5000)
                g_6098[n].y1[j][0] += g_05a2 * 8;
            else if (g_6098[n].y1[j][0] > 5000 && g_1df8[t][i].f04.y < 1000)
                g_6098[n].y1[j][0] -= g_05a2 * 8;
        }
        vel = *(POINT far *)&g_1df8[t][i].f0c;
        ok = fn_10_7dd4(&c.x, &c.y, &g_1df8[t][i].f0c, &g_1df8[t][i].f0e,
            &g_6098[n].x1[j][0], &g_6098[n].y1[j][0], &g_1df8[t][i].f04.x, &g_1df8[t][i].f04.y,
            30, g_1df8[t][i].f20 + 8, k, g_1df8[t][i].f44, &g_9436, &g_9438);
        if (wrap) {
            g_6098[n].x1[j][0] = (int)((g_6098[n].x1[j][0] + ((long)*(int *)&g_05a0 << 3))
                                       % (*(int *)&g_05a0 << 3));
            g_6098[n].y1[j][0] = (int)((g_6098[n].y1[j][0] + ((long)g_05a2 << 3))
                                       % (g_05a2 << 3));
        }
        if (ok) {
        if (g_1df8[t][i].f54) {
            g_1df8[t][i].f0e = 0;
            g_1df8[t][i].f0c = g_1df8[t][i].f0e;
        } else {
            g_1df8[t][i].f0c = (g_1df8[t][i].f0c + vel.x) / 2;
            g_1df8[t][i].f0e = (g_1df8[t][i].f0e + vel.y) / 2;
        }
        g_6098[n].f70 = c.x / 5;
        g_6098[n].f72 = c.y / 5;
        if (t == 4 || t == 8 && g_3d5a[i].f12 == 2
            && (g_4d90[g_3d5a[i].f26].f03 == 5 || g_4d90[g_3d5a[i].f26].f03 == 4))
            fn_10_754a(30, t, i, 1);
        else
            fn_10_754a(0x11, 30, n, 2);
        if (otype == g_9324) {
            if (g_70ae[oidx].f1a == 1 && g_70ae[oidx].f14 == t && g_70ae[oidx].f16 == i)
                g_70ae[oidx].f86 = g_1e50;
            for (m = 0; m <= g_9316; m++)
                if (m != oidx && g_70ae[m].fce && g_70ae[m].f14 == t
                    && g_70ae[m].f16 == i && g_70ae[m].f1a == 1)
                    fn_13_2714(m, oidx, 5, 10, 0, -1);
        }
        if (otype == g_9324 && t == g_9324)
            fn_04_7d36(oidx, i, g_9438);
        if (otype == g_9324 && oidx == g_9646 && !(t == g_9324 && i == g_9646)) {
            g_9440 = i;
            g_52d8 = g_1e50;
            g_943e = t;
            if (t == g_9324 || t == g_934a || t == 8 || t == 0 && g_1df8[0][i].f53 == 1)
                g_9432 += g_9438 / 3;
            if (t == g_9324 && g_70ae[i].f1a == 4 && g_70ae[i].f16 == g_9646)
                g_9432 += g_9438 / 2;
        }
        ret = g_1df8[t][i].f5e(t, i, g_9438);
        if (ret == 0 && g_9208 >= 2 && k * g_9436 > 600)
            fn_08_804a(n, k * g_9436, j);
        fn_08_99ce(t, i, otype, oidx, ret + 2);
        if (t == 15)
            fn_18_3f02(g_6098[n].x1[j][0], g_6098[n].y1[j][0], g_9438);
        v = 0;
        if (ret && otype == g_9324) {
            if (t == 0 && g_1df8[0][i].f53 == 1 && g_70ae[oidx].f14 == 0
                && g_70ae[oidx].f16 == i && g_70ae[oidx].f1a == 1)
                fn_13_b6f2(oidx, 1);
            if (t == 8 && g_3d5a[i].f00 == 16 && g_70ae[oidx].f14 == 8
                && g_70ae[oidx].f16 == i && g_70ae[oidx].f1a == 1)
                fn_13_b6f2(oidx, 6);
            if (g_70ae[oidx].f34 >= 2 && g_70ae[oidx].f34 <= 4 && g_70ae[oidx].f3a != oidx
                && g_70ae[oidx].f36 == t) {
                if (t == 9) {
                    fn_03_06ec(oidx, g_9324, g_70ae[oidx].f3a, 0x75);
                    fn_13_2714(g_70ae[oidx].f3a, oidx, 15, 45, 0, 6);
                    if (g_9134 == 0 || oidx != g_9646 && flow_interactive == 0)
                        g_70ae[oidx].f34 = 0;
                    v = 1;
                } else if (g_70ae[oidx].f38 == i) {
                    fn_03_06ec(oidx, g_9324, g_70ae[oidx].f3a, 0x76);
                    fn_13_2714(g_70ae[oidx].f3a, oidx, 40, 90, 0, 6);
                    if (g_9134 == 0 || oidx != g_9646 && flow_interactive == 0)
                        g_70ae[oidx].f34 = 0;
                    v = 1;
                }
            } else if ((g_70ae[oidx].f34 == 1 || g_70ae[oidx].f34 == 5) && t == g_9324) {
                if (g_70ae[i].f14 == g_9324 && g_70ae[oidx].f3a == g_70ae[i].f16
                    && g_70ae[i].f1a == 1) {
                    fn_03_06ec(oidx, g_9324, g_70ae[oidx].f3a, 0x77);
                    fn_13_2714(g_70ae[oidx].f3a, oidx, 60, 120, 0, 8);
                    v = 1;
                }
            } else {
                for (m = 0; m <= g_9316; m++)
                    if (m != oidx && g_70ae[m].fce && g_70ae[m].f14 == t
                        && g_70ae[m].f16 == i && g_70ae[m].f1a == 1) {
                        fn_13_2714(m, oidx, 25, 40, 0, 6);
                        fn_03_06ec(oidx, g_9324, m, 0x77);
                    }
            }
        }
        if (ret && t == 0 && otype == g_9324 && oidx == g_9646 && g_1df8[t][i].f53 == 2) {
            fn_03_06ec(oidx, 7, 0, 0x5e);
            g_1e58 += 3000;
        }
        if (ret && t == 8 && g_9320 == 6 && g_9eb9[g_9322] + g_9318 * 2 <= i) {
            world_map(g_0a72, g_0a74, 1 - g_9eb5, g_9322, 8, i, 0);
            BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
        }
        if (ret && t == g_9324) {
            fn_04_7636(i, otype, oidx, v);
            if (otype == g_9324 && oidx == g_9646)
                g_9432 += 200;
        }
        if (ret)
            g_70ae[g_9646].f138 = g_1e50 - 1;
        if (otype == g_9324 && oidx == g_9646)
            fn_08_7be8(t, i, g_9438, ret);
        if (ret && t == 9 && otype == g_9324 && v == 0)
            fn_03_06ec(oidx, 7, 0, 0x5b);
        if (t == g_9324 && g_70ae[i].fce) {
            if (g_92e8 && i != g_9646)
                g_9438 /= 2;
            g_70ae[i].fc4 = 1;
            if (g_1df8[t][i].f26 == 0)
                g_1df8[t][i].f26 = 1;
            g_70ae[i].f66 = g_9438 * 12 + g_1e50;
        } else if (t == 8)
            g_3d50[i].f04 = g_9438 * 120 + g_1e50;
        if (ret)
            return 2;
        return 1;
        }
        }
        }
    }
    return 0;
}
