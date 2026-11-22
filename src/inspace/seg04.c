/* INSPACE.EXE segment 4 (selector 1018). */
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    char p00[0x04];
    int f04;                    /* +04 */
    int f06;                    /* +06 */
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
    char p2f[0x51 - 0x2f];
    char f51;                   /* +51 */
    char p52;
    char f53;                   /* +53 */
    char p54[0x70 - 0x54];
} REC_70;

/* 0x15a-byte records at DS:7090, indexed like the object records
 * [inferred]. */
typedef struct {
    char p000[0x12];
    int f12;                    /* +12 */
    char p014[0x18 - 0x14];
    int f18;                    /* +18 */
    char p01a[0x32 - 0x1a];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    char p036[0x38 - 0x36];
    int f38;                    /* +38 */
    char p03a[0x4e - 0x3a];
    int f4e;                    /* +4e */
    char p050[0x5e - 0x50];
    char f5e;                   /* +5e */
    char p05f[0xb8 - 0x5f];
    char fb8[0x12];             /* +b8, indexed by slot [inferred] */
    char fca;                   /* +ca */
    char p0cb[0xce - 0xcb];
    int fce;                    /* +ce */
    char p0d0[0xd4 - 0xd0];
    int fd4;                    /* +d4 */
    char p0d6[0xda - 0xd6];
    int fda;                    /* +da */
    long fdc;                   /* +dc */
    char p0e0[0xec - 0xe0];
    char fec;                   /* +ec */
    char p0ed[0x146 - 0xed];
    char f146;                  /* +146 */
    char p147;
    char f148;                  /* +148 */
    char p149[0x15a - 0x149];
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

typedef struct {                /* 0x50 bytes, DGROUP array at DS:2f5e */
    int f00;                    /* +00 */
    char p02[0x1e - 0x02];
    int f1e;                    /* +1e */
    char p20[0x38 - 0x20];
    int f38;                    /* +38 */
    char p3a[0x50 - 0x3a];
} REC_50;

extern REC_50 g_2f5e[];
extern REC_1C g_66e8[];
extern DWORD g_1d06;
extern REC_70 far *g_1df8[16];
extern DWORD g_1e50;
extern DWORD g_1e68;
extern DWORD g_8e28;
extern int g_9000;
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

void far fn_03_06ec(int a, int b, int n, int id);
void far fn_07_1208(void);
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
    ax_ = g_1df8[HIBYTE(v)][LOBYTE(v)].f04 - g_1df8[6][n].f04;
    ay = g_1df8[HIBYTE(v)][LOBYTE(v)].f06 - g_1df8[6][n].f06;
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
    if (g_2f5e[k].f38 == 0)
        g_7090[n].fca = g_7090[n].f5e * 4 + g_2f5e[k].f1e;
    else {
        g_7090[n].fca = 2;
        g_7090[n].fd4 = g_2f5e[k].f1e * 3;
    }
    fn_13_4eec(n, 5);
    if (g_2f5e[k].f00)
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
