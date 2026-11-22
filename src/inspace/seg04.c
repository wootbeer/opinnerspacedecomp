/* INSPACE.EXE segment 4 (selector 1018). */
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    char p00[0x18];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[0x26 - 0x1c];
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    char p2a[0x51 - 0x2a];
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
    char p014[0x32 - 0x14];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    char p036[0x38 - 0x36];
    int f38;                    /* +38 */
    char p03a[0x4e - 0x3a];
    int f4e;                    /* +4e */
    char p050[0xda - 0x50];
    int fda;                    /* +da */
    char p0dc[0xec - 0xdc];
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

extern DWORD g_1d06;
extern REC_70 far *g_1df8[16];
extern DWORD g_1e50;
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
