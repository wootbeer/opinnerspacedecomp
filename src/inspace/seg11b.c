/* INSPACE.EXE segment 11 (selector 1050): 11:1ab6 and 11:1b44, which the
 * rest of segment 11 calls far (see NOTES.md), so they live apart. */
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. */
typedef struct {
    char p00[4];
    long f04;                   /* +04: two ints [inferred] */
    char p08[0x70 - 8];
} REC_70;
extern REC_70 far *g_1df8[16];

extern int g_094e;
extern long g_6b50;
extern int g_9324;
extern int g_951a;
extern int g_9646;

/* inspace.h declares g_05a0 as long; here it is two ints (world width and
 * height [inferred]). */
#define g_05a0_lo (((int *)&g_05a0)[0])
#define g_05a2 (((int *)&g_05a0)[1])

/* Signed horizontal distance on a wrapping world [inferred]. */
/* @addr 11:1ab6 */
long far pascal fn_11_1ab6(long x)
{
    int d1, d2, h, w;

    if (g_094e) {
        w = g_05a0_lo << 2;
        h = g_05a2 << 2;
    } else
        w = LOWORD(g_951a == 0 ? g_1df8[g_9324][g_9646].f04 : g_6b50);
    x >>= 3;
    w >>= 3;
    if ((int)x > w) {
        d1 = w - (int)x + g_05a0_lo;
        d2 = (int)x - w;
        if (d1 < d2)
            return -d1;
        return d2;
    } else {
        d1 = (int)x - w + g_05a0_lo;
        d2 = w - (int)x;
        if (d1 < d2)
            return d1;
        return -d2;
    }
}

/* Signed vertical distance on a wrapping world [inferred]. */
/* near-match 99.3%: 11:1b44 (frame 0xc vs 8: HIWORD of the long ternary costs a temp) */
long far pascal fn_11_1b44(long y)
{
    int d1, d2, h, w;

    if (g_094e)
        h = g_05a2 << 2;
    else
        h = HIWORD(g_951a == 0 ? g_1df8[g_9324][g_9646].f04 : g_6b50);
    y >>= 3;
    h >>= 3;
    if ((int)y > h) {
        d1 = h - (int)y + g_05a2;
        d2 = (int)y - h;
        if (d1 < d2)
            return -d1;
        return d2;
    } else {
        d1 = (int)y - h + g_05a2;
        d2 = h - (int)y;
        if (d1 < d2)
            return d1;
        return -d2;
    }
}
