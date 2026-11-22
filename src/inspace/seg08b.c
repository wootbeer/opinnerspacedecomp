/* INSPACE.EXE segment 8 (selector 1038), part compiled with /G2:
 * no 32-bit code from 8:3688 to 8:81f8 [inferred: one source file]. */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array per object type
 * [inferred, as in seg07.c]. */
typedef struct {
    char p00[4];
    POINT f04;                  /* +04 */
    char p08[4];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x1c - 0x10];
    int f1c;                    /* +1c */
    char p1e[0x44 - 0x1e];
    int f44;                    /* +44 */
    char p46[0x54 - 0x46];
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
    char p00[0xba];
    int fba;                    /* +ba */
    char pbc[0x15a - 0xbc];
} REC_15A;
extern REC_15A g_70ae[];

extern int g_9324;
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

/* near-match 73%: 8:698a (the original loads the record's word at +4 into ax
 * just before testing f54, and never uses it) */
void far pascal fn_08_698a(int a)
{
    int type;
    int idx;

    g_1df8[g_944a][g_944e].f1c = 1;
    g_1df8[g_944a][g_944e].f0c = g_52e0;
    g_1df8[g_944a][g_944e].f0e = g_52e2;
    if (a) {
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
