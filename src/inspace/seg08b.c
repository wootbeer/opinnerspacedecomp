/* INSPACE.EXE segment 8 (selector 1038), part compiled with /G2:
 * no 32-bit code from 8:3688 to 8:81f8 [inferred: one source file]. */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include "inspace.h"

extern int g_90ea;
extern int g_90ec;

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
