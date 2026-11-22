/* INSPACE.EXE segment 4 (selector 1018). */
#include <stdlib.h>
#include "inspace.h"

/* g_05a0 is declared long in inspace.h; this code reads its two words
 * separately (world width and height [inferred]). */
#define G_05A0_LO (((int *)&g_05a0)[0])
#define G_05A0_HI (((int *)&g_05a0)[1])

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    POINT f00;                  /* +00 */
    POINT f04;                  /* +04: position [inferred] */
    char p08[0x0c - 0x08];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x18 - 0x10];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[0x26 - 0x1c];
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    char p2a[0x2e - 0x2a];
    char f2e;                   /* +2e */
    char f2f;                   /* +2f */
    char p30[0x51 - 0x30];
    char f51;                   /* +51 */
    char p52;
    char f53;                   /* +53 */
    char p54[0x70 - 0x54];
} REC_70;

/* 0x15a-byte records at DS:7090, indexed like the object records
 * [inferred]. */
typedef struct {
    char p000[0x10];
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    char p014[0x18 - 0x14];
    int f18;                    /* +18 */
    char p01a[0x1e - 0x1a];
    int f1e;                    /* +1e */
    char p020[0x26 - 0x20];
    int f26;                    /* +26 */
    char p028[0x32 - 0x28];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    char p036[0x38 - 0x36];
    int f38;                    /* +38 */
    char p03a[0x3c - 0x3a];
    int f3c;                    /* +3c */
    char p03e[0x44 - 0x3e];
    int f44[5];                 /* +44: history [inferred] */
    int f4e;                    /* +4e */
    char p050[0x5e - 0x50];
    char f5e;                   /* +5e */
    char f5f;                   /* +5f */
    char p060[0xae - 0x60];
    char fae[10];               /* +ae, indexed by slot [inferred] */
    char fb8[0x12];             /* +b8, indexed by slot [inferred] */
    char fca;                   /* +ca */
    char fcb;                   /* +cb: slot count [inferred] */
    char p0cc[0xce - 0xcc];
    int fce;                    /* +ce */
    char p0d0[0xd4 - 0xd0];
    int fd4;                    /* +d4 */
    char p0d6[0xd8 - 0xd6];
    int fd8;                    /* +d8 */
    int fda;                    /* +da */
    long fdc;                   /* +dc */
    char p0e0[0xe2 - 0xe0];
    char fe2;                   /* +e2 */
    char p0e3[0xe8 - 0xe3];
    char fe8;                   /* +e8 */
    char p0e9[0xec - 0xe9];
    char fec;                   /* +ec */
    char p0ed[0x13e - 0xed];
    char f13e[8];               /* +13e, indexed by object [inferred] */
    char f146;                  /* +146 */
    char p147;
    char f148;                  /* +148 */
    char p149;
    POINT f14a;                 /* +14a */
    char p14e[0x15a - 0x14e];
} REC_15A;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    char p00[0x1a];
    int f1a;                    /* +1a */
    char p1c[0xad - 0x1c];
} REC_AD;
#pragma pack()

typedef struct {                /* 0x1c bytes, DGROUP array at DS:66e8 */
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p04[0x08 - 0x04];
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    char p0e[0x1c - 0x0e];
} REC_1C;

typedef struct {                /* 0x50 bytes, DGROUP array at DS:2f58 */
    int f00;                    /* +00 */
    char p02[0x06 - 0x02];
    int f06;                    /* +06 */
    char p08[0x24 - 0x08];
    int f24;                    /* +24 */
    char p26[0x28 - 0x26];
    int f28;                    /* +28 */
    int f2a;                    /* +2a */
    char p2c[0x3e - 0x2c];
    int f3e;                    /* +3e */
    char p40[0x50 - 0x40];
} REC_50;

extern REC_50 g_2f58[];
extern REC_1C g_66e8[];
extern DWORD g_1d06;
extern REC_70 far *g_1df8[16];
extern DWORD g_1e50;
extern DWORD g_1e68;
extern DWORD g_8e28;
extern int g_9000;
extern long g_1e58;
extern long g_5078;
extern int g_9318;
extern int g_91fc;
extern int g_94a8;
extern int g_94aa;
extern int g_967c;
extern int g_9684;
extern int g_9ea0;
extern int g_9ea4;
extern char g_9eb5;
extern int g_9134;
extern int g_9334;
extern int g_9524;
extern int g_967e;
extern REC_AD g_96f0[];
extern int g_238c;
extern REC_15A g_7090[];
extern int g_9316;
extern int g_9646;
extern int g_8e48[];
extern int g_9ea2;
extern int flow_interactive;        /* DS:95bc */
extern unsigned long g_9e60[];
extern long g_8e00;
extern long g_8e04;
extern int g_9680;
extern int g_9682;

void far fn_03_06ec(int a, int b, int n, int id);
void far fn_07_1208(void);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
void far fn_10_744c(int a);
void far race_radar_background(int a);
void far fn_12_3e98(int i);
int far fn_04_6a78(int n, int i);
int far fn_13_2688(int n, int m);
int far fn_13_1076(int n, int type);
void far pascal fn_11_7c12(int k, int type, int n);
void far fn_11_8a42(int type, int n);
void far fn_11_9078(int type, int n);
void far fn_11_947a(int type, int n, int k);
void far fn_11_9daa(int type, int n);
void far fn_11_9fdc(int type, int n);
void far fn_11_2f8c(void);
void far pascal fn_13_1318(int type, int n, int t, int k);
void far fn_13_4eec(int i, int d);
void far fn_13_9a18(int n, int x, int y);
POINT far pascal fn_08_29ea(POINT pt);
int far pascal fn_08_19b0(int dx, int dy);
void far pascal fn_03_332e(int a, int b);
int far fn_11_4c72(int n);
int far fn_11_4b00(int n);
void far pascal fn_04_584c(int s, int n, int t);
void far fn_04_6e70(int n);

/* @addr 4:0000 */
void far pascal fn_04_0000(int n)
{
    if (g_1df8[14][n].f26 && g_238c == 0)
        fn_07_1208();
    if (g_7090[n].f12) {
        g_1df8[14][n].f28 += g_7090[n].f12;
        if (g_1df8[14][n].f28 > 15)
            g_1df8[14][n].f28 = 0;
        if (g_1df8[14][n].f28 < 0)
            g_1df8[14][n].f28 = 15;
        fn_07_1208();
    }
}

/* @addr 4:2da2 */
void far fn_04_2da2(void)
{
    int v;
    int i;

    g_9eb5 = 1;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f18 != 0)
            continue;
        if (g_7090[i].fda < 0)
            v = -1 - g_7090[i].fda;
        else
            v = g_7090[i].fda;
        if (v < g_9ea0)
            g_9eb5 = 0;
    }
    if (g_7090[g_9646].fda - g_9ea0 == 1)
        g_9eb5 = 1;
    else {
        if (g_9684 == 1) {
            fn_10_744c(0x74);
            if (g_91fc) {
                fn_03_06ec(g_9646, 7, 0, 0xba);
                g_967c++;
            }
        } else {
            fn_10_744c(0x42);
            if (g_91fc)
                fn_03_06ec(g_9646, 7, 0, 0xbb);
        }
        g_9e60[g_9646] = g_1e68 - g_9e60[g_9646];
        if (g_91fc)
            g_9eb5 = 1;
        if (g_9684 == 1 && g_9316 != 0) {
            g_5078 += ((9 - g_94aa) * g_9316 + (g_94a8 + 5) * 4) * 500;
            g_1e58 += ((9 - g_94aa) * g_9316 + (g_94a8 + 5) * 4) * 500;
        } else if (g_9684 == 2 && g_9316 > 1) {
            g_5078 += (g_94a8 + 8) * 500 + (8 - g_94aa) * g_9316 * 200;
            g_1e58 += (g_94a8 + 8) * 500 + (8 - g_94aa) * g_9316 * 200;
        }
    }
    if (g_9eb5) {
        fn_10_744c(20);
        race_radar_background(0);
        for (i = g_9318 * 2; i < g_9318 * 2 + g_9ea2 + g_9ea4; i++)
            fn_12_3e98(i);
        for (i = 0; i <= g_9316; i++) {
            g_7090[i].f148 = -2;
            g_7090[i].f32 = 12;
            g_7090[i].f34 = 0;
            g_7090[i].f3c = g_7090[i].f38 = 2;
            if (g_1df8[14][i].f51 == 0)
                g_1df8[14][i].f51 = 1;
        }
    }
    g_1df8[14][g_9646].f51 = 2;
}

/* near-match 81%: 4:474c (the original keeps g_1e50 in eax/dx:ax across the
 * test and adds 20000 with add/adc; not reproduced yet) */
void far fn_04_474c(int n, int kind, int m, int ev)
{
    if (g_1d06 > g_1e50 || g_1df8[14][n].f1a == 0)
        return;
    g_1d06 = g_1e50 + 20000;
    if (ev == 5)
        fn_03_06ec(g_9646, 14, n, 0xa5);
    else if (ev == 2) {
        if (kind == 3 || kind == 8 || kind == 1)
            fn_03_06ec(g_9646, 14, n, 0xa6);
        else if (kind == 9)
            fn_03_06ec(g_9646, 14, n, 0xa7);
        else if (kind == 0 && g_1df8[0][m].f53 == 1)
            fn_03_06ec(g_9646, 14, n, 0xa8);
        else if (kind == 0)
            fn_03_06ec(g_9646, 14, n, 0xa9);
        else if (kind == 2)
            fn_03_06ec(g_9646, 14, n, 0xaa);
        else if (kind == 14 && fn_13_2688(n, m) < 0 && g_96f0[g_7090[m].f4e].f1a == 3)
            fn_03_06ec(g_9646, 14, n, 0xad);
        else if (kind == 14 && fn_13_2688(n, m) < 0)
            fn_03_06ec(g_9646, 14, n, 0xab);
        else if (kind == 14)
            fn_03_06ec(g_9646, 14, n, 0xac);
    }
}

/* near-match 22%: 4:5514 (control flow right; register/temp allocation and the
 * cwd before the -1 test differ) */
void far pascal fn_04_5514(int n)
{
    char unused[36];
    int v;
    long ax_;
    long ay;
    long bx_;
    long by;

    if (g_1df8[6][n].f1a == 0)
        goto none;
    v = fn_13_1076(n, 6);
    if (v == -1L)
        goto none;
    g_66e8[n].f08 = HIBYTE(v);
    g_66e8[n].f0a = LOBYTE(v);
    if (g_66e8[n].f00 == g_66e8[n].f08 && g_66e8[n].f02 == g_66e8[n].f0a)
        goto none;
    ax_ = g_1df8[HIBYTE(v)][LOBYTE(v)].f04.x - g_1df8[6][n].f04.x;
    ay = g_1df8[HIBYTE(v)][LOBYTE(v)].f04.y - g_1df8[6][n].f04.y;
    bx_ = g_1df8[HIBYTE(v)][LOBYTE(v)].f0c - g_1df8[6][n].f0c;
    by = g_1df8[HIBYTE(v)][LOBYTE(v)].f0e - g_1df8[6][n].f0e;
    if (ax_ * by - ay * bx_ > 0)
        g_66e8[n].f0c = 4;
    else
        g_66e8[n].f0c = 3;
    return;
none:
    g_66e8[n].f0c = 2;
}

/* @addr 4:584c */
void far pascal fn_04_584c(int s, int n, int t)
{
    int k;

    if (g_1df8[14][n].f2e)
        return;
    if (n == g_9646 && g_9134 == 0)
        g_8e28 = g_1e50;
    k = g_7090[n].fb8[s];
    if (g_2f58[k].f3e == 0)
        g_7090[n].fca = g_7090[n].f5e * 4 + g_2f58[k].f24;
    else {
        g_7090[n].fca = 2;
        g_7090[n].fd4 = g_2f58[k].f24 * 3;
    }
    fn_13_4eec(n, 5);
    if (g_2f58[k].f06)
        fn_11_7c12(k, 14, n);
    else if (k == 5)
        fn_13_1318(14, n, t, 5);
    else if (k == 4)
        fn_13_1318(14, n, t, 4);
    else if (k == 1)
        fn_11_8a42(14, n);
    else if (k == 2)
        fn_11_947a(14, n, 2);
    else if (k == 15)
        fn_11_947a(14, n, 15);
    else if (k == 3)
        fn_11_9fdc(14, n);
    else if (k == 23)
        fn_11_9daa(14, n);
    else if (k == 13)
        fn_11_9078(14, n);
    if (n == g_9646 && g_9134 && g_7090[n].f18 != s) {
        g_9524 = s;
        g_7090[n].f18 = s;
        fn_11_2f8c();
    }
    g_7090[n].f18 = s;
}

/* Not yet decompiled. */
int far fn_04_6a78(int n, int i)
{
    return 0;
}

/* near-match 18%: 4:6e70 (control flow and layout right; the original indexes
 * fae[i]/fb8[i] as (row + i) in bx, this picks bx+si) */
void far fn_04_6e70(int n)
{
    int i;
    int best;
    int sel;
    int v;
    int j;

    i = g_7090[n].f18;
    g_7090[n].f5f = 0;
    best = -1000;
    sel = -1;
    if (g_7090[n].fcb <= 1)
        return;
    for (i = 1; i < g_7090[n].fcb; i++) {
        if (g_7090[n].fae[i] <= 0)
            continue;
        if (g_7090[n].f32 == 0 && g_1df8[0][g_7090[n].f34].f2f < 0 && g_7090[n].fb8[i] == 5)
            v = 10000;
        else
            v = fn_04_6a78(n, i);
        if (v > best) {
            sel = i;
            best = v;
        }
    }
    if (best > 0) {
        if (g_2f58[g_7090[n].fb8[sel]].f00 == 2)
            g_7090[n].f5f = 2;
        else if (g_2f58[g_7090[n].fb8[sel]].f00 == 3)
            g_7090[n].f5f = 3;
        else
            g_7090[n].f5f = 1;
        g_7090[n].f18 = sel;
    } else if (best == -100) {
        best = 100;
        for (j = 1; j < g_7090[n].fcb; j++) {
            if (g_7090[n].fae[j] < 0)
                continue;
            if (g_2f58[g_7090[n].fb8[j]].f2a < g_7090[n].f1e
                && g_2f58[g_7090[n].fb8[j]].f28 < best) {
                best = g_2f58[g_7090[n].fb8[j]].f28;
                sel = j;
            }
        }
        if (best < 100) {
            if (g_2f58[g_7090[n].fb8[sel]].f00 == 2)
                g_7090[n].f5f = 2;
            else if (g_2f58[g_7090[n].fb8[sel]].f00 == 3)
                g_7090[n].f5f = 3;
            else
                g_7090[n].f5f = 1;
            g_7090[n].f18 = sel;
        } else {
            g_7090[n].f18 = 0;
            g_7090[n].f5f = 1;
        }
    } else {
        g_7090[n].f18 = 0;
        g_7090[n].f5f = 1;
    }
    if (n == g_9646)
        fn_11_2f8c();
}

/* @addr 4:8346 */
int far fn_04_8346(int n, int x, int y, int v)
{
    if (v == 3 && g_7090[n].f38 == 1 && g_7090[n].f32 == x && g_7090[n].f34 == y)
        v = g_7090[n].f146;
    if (n != g_9646 || flow_interactive == 0)
        fn_13_9a18(n, x, y);
    g_7090[n].f146 = v;
    return 1;
}

/* @addr 4:83ae */
void far fn_04_83ae(void)
{
    int i;
    int j;
    int a;
    int b;
    int d;

    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].fec && g_7090[i].fe8) {
            for (j = 0; j <= g_9316; j++) {
                if (j != i && g_7090[j].fec && g_7090[j].f32 == 14 && g_7090[j].f34 == i) {
                    d = fn_08_285a(&a, &b, g_1df8[14][i].f04, g_7090[i].f14a);
                    if (d > 350) {
                        g_7090[i].f14a.x = rand() % 4000 + g_1df8[14][i].f04.x - 2000;
                        g_7090[i].f14a.y = rand() % 4000 + g_1df8[14][i].f04.y - 2000;
                        if (g_7090[i].f14a.x < 0)
                            g_7090[i].f14a.x += G_05A0_LO * 8;
                        else if (g_7090[i].f14a.x > G_05A0_LO * 8)
                            g_7090[i].f14a.x -= G_05A0_LO * 8;
                        if (g_7090[i].f14a.y < 0)
                            g_7090[i].f14a.y += G_05A0_HI * 8;
                        else if (g_7090[i].f14a.y > G_05A0_HI * 8)
                            g_7090[i].f14a.y -= G_05A0_HI * 8;
                    }
                }
            }
        }
    }
}

/* @addr 4:84de */
void far fn_04_84de(void)
{
    int i;
    int count;
    int r;

    g_967e = min(g_9334 * 7 + 45, 100);
    if (g_1e68 < 500)
        g_967e -= (700 - g_1e68) / 8;
    else
        g_967e = min(g_967e + g_1e68 / 100, 100);
    if (g_967e < 3)
        g_967e = 3;
    if (g_7090[g_9646].fce + g_7090[g_9646].fdc < 100)
        g_967e -= 20;
    if (g_7090[g_9646].fce + g_7090[g_9646].fdc > 250)
        g_967e += 20;
    if (g_7090[g_9646].fce + g_7090[g_9646].fdc > 1000)
        g_967e += 30;
    count = 0;
    for (i = 0; i < 8; i++)
        if (g_1df8[0][i].f18 == 0)
            count++;
    r = count * 10 / (g_9316 + 1);
    if (r < 15)
        g_967e -= 10;
    if (r < 10)
        g_967e -= 10;
    if (r < 5)
        g_967e -= 10;
    if (g_9000 == 0)
        g_967e = -10;
}

/* @addr 4:8c80 */
int far fn_04_8c80(void)
{
    int i;
    int best;
    int max;
    int a;
    int score;

    best = -1;
    max = -1;
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].fec && g_1df8[14][i].f18 == 0) {
            if (g_7090[i].fda < 0)
                a = -g_7090[i].fda;
            else
                a = g_7090[i].fda;
            score = a * g_9ea2 + g_7090[i].f148;
            if (score > max) {
                max = score;
                best = i;
            }
            if (score == max && g_8e48[best] > g_8e48[i]) {
                max = score;
                best = i;
            }
        }
    }
    return best;
}

/* @addr 4:8d3a */
int far fn_04_8d3a(void)
{
    unsigned long best;
    int i;
    int found;

    best = 1000000;
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].fec && g_1df8[14][i].f18 == 0 && g_1df8[14][i].f51 == 2
            && g_9e60[i] < best) {
            found = i;
            best = g_9e60[i];
        }
    }
    return found;
}
/* @addr 4:5d9c */
int far fn_04_5d9c(int a, int b)
{
    long a26;
    long ad8;
    long b26;
    long bd8;
    long x;
    long y;

    if (a >= 0 && a <= g_9316 && b >= 0 && b <= g_9316) {
        ad8 = g_7090[a].fd8;
        bd8 = g_7090[b].fd8;
        a26 = g_7090[a].f26;
        b26 = g_7090[b].f26;
        x = (long)g_7090[a].f26 * ad8 / (a26 / 2 + 50);
        y = (long)g_7090[b].f26 * bd8 / (b26 / 2 + 50);
        if (y == 0)
            y = 10;
        return x * 100 / y;
    }
    return 100;
}

/* @addr 4:7d36 */
void far fn_04_7d36(int a, int b, int c)
{
    int k;
    int i;

    if ((g_7090[a].f32 == 14 && g_7090[a].f34 == b)
        || (g_7090[b].f32 == 14 && g_7090[b].f34 == a)) {
        k = 1;
        if (c > 30)
            k = 2;
        g_7090[a].f13e[b] = g_7090[a].f13e[b] + k > 6 ? 6 : g_7090[a].f13e[b] + k;
        g_7090[b].f13e[a] = g_7090[b].f13e[a] - k < -6 ? -6 : g_7090[b].f13e[a] - k;
        if (a == g_9646) {
            g_9680++;
            g_8e00 += c;
        } else if (b == g_9646) {
            g_9682++;
            g_8e04 += c;
        }
    }
    if (c > 0 && a == g_9646) {
        for (i = 3; i >= 0; i--)
            g_7090[b].f44[i + 1] = g_7090[b].f44[i];
        g_7090[b].f44[0] = g_1e68 / 10;
    }
}

/* Updates g_9684 with the player's race standing [inferred]. */
/* @addr 4:8b82 */
void far race_position(void)
{
    int i;
    int score;
    int mine;
    int a;

    if (g_1df8[14][g_9646].f51 == 0) {
        if (g_7090[g_9646].fda < 0)
            a = -g_7090[g_9646].fda;
        else
            a = g_7090[g_9646].fda;
        mine = a * g_9ea2 + g_7090[g_9646].f148;
        g_9684 = 1;
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].fec && g_1df8[14][i].f18 == 0 && i != g_9646) {
                if (g_7090[i].fda < 0)
                    a = -g_7090[i].fda;
                else
                    a = g_7090[i].fda;
                score = a * g_9ea2 + g_7090[i].f148;
                if (score > mine)
                    g_9684++;
                if (mine == score && g_8e48[i] < g_8e48[g_9646])
                    g_9684++;
            }
        }
    }
}
