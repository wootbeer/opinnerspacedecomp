/* INSPACE.EXE segment 12 (selector 1058). No 32-bit code anywhere in this
 * segment: compiled with /G2 [inferred, confirmed by matches]. */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array per object type
 * [inferred, as in seg07.c]. Only the fields used here are named. */
typedef struct {
    char p00[4];
    POINT f04;                  /* +04 */
    char p08[4];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x1e - 0x10];
    int f1e;                    /* +1e */
    char p20[0x2f - 0x20];
    char f2f;                   /* +2f */
    char p30[0x3c - 0x30];
    HDC f3c;                    /* +3c */
    HBITMAP f3e;                /* +3e */
    HBITMAP f40;                /* +40 */
    char p42[0x50 - 0x42];
    char f50;                   /* +50 */
    char p51[0x54 - 0x51];
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
    char pae[0x15a - 0xae];
} REC_15A;
extern REC_15A g_70ae[];

extern int g_2f5e[];            /* 0x50-byte records, first word [inferred] */
extern int g_9324;
extern int g_9326;
extern int g_9406[];

void far fn_07_2080(int a, int b);
void far fn_10_533a(int a);

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
    if (g_2f5e[b * 0x28])
        fn_10_533a(g_70ae[a].f9a[i]);
}
