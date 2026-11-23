/* INSPACE.EXE segment 11 (selector 1050): 11:1ab6 and 11:1b44, which the
 * rest of segment 11 calls far (see NOTES.md), so they live apart. */
#include "game.h"

/* inspace.h declares g_05a0 as long; here it is two ints (world width and
 * height [inferred]). */
                                       
                                    

/* Signed horizontal distance on a wrapping world [inferred]. */
/* 11:1ab6 */
int32_t fn_11_1ab6(int32_t x)
{
    int16_t d1, d2, h, w;

    if (g_094e) {
        w = (LO16(g_05a0)) << 2;
        h = (HI16(g_05a0)) << 2;
    } else
        w = LOWORD(g_951a == 0 ? VIEW(int32_t, g_1df8[g_9324][g_9646].f_04, 0) : VIEW(int32_t, g_6b50, 0));
    x >>= 3;
    w >>= 3;
    if ((int16_t)x > w) {
        d1 = w - (int16_t)x + (LO16(g_05a0));
        d2 = (int16_t)x - w;
        if (d1 < d2)
            return -d1;
        return d2;
    } else {
        d1 = (int16_t)x - w + (LO16(g_05a0));
        d2 = w - (int16_t)x;
        if (d1 < d2)
            return d1;
        return -d2;
    }
}

/* Signed vertical distance on a wrapping world [inferred]. */
/* near-match 99.3%: 11:1b44 (frame 0xc vs 8: HIWORD of the long ternary costs a temp) */
int32_t fn_11_1b44(int32_t y)
{
    int16_t d1, d2, h, w;

    if (g_094e)
        h = (HI16(g_05a0)) << 2;
    else
        h = HIWORD(g_951a == 0 ? VIEW(int32_t, g_1df8[g_9324][g_9646].f_04, 0) : VIEW(int32_t, g_6b50, 0));
    y >>= 3;
    h >>= 3;
    if ((int16_t)y > h) {
        d1 = h - (int16_t)y + (HI16(g_05a0));
        d2 = (int16_t)y - h;
        if (d1 < d2)
            return -d1;
        return d2;
    } else {
        d1 = (int16_t)y - h + (HI16(g_05a0));
        d2 = h - (int16_t)y;
        if (d1 < d2)
            return d1;
        return -d2;
    }
}
