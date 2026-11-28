/* INSPACE.EXE segment 8 (selector 1038), part compiled with /G2:
 * no 32-bit code from 8:3688 to 8:81f8 [inferred: one source file]. */
#include "game.h"

#define SC(n) ((int16_t)((n) << g_9156) >> 1)
/* 0xad-byte records; lowest field seen at DS:96ea [inferred]. */

/* 8:6a44 */
void fn_08_6a44(int16_t a)
{
    int16_t type;
    int16_t idx;

    object_records[g_944c][g_9450].f_1c = 1;
    object_records[g_944c][g_9450].f_0c = g_52dc.x;
    object_records[g_944c][g_9450].f_0e = g_52dc.y;
    if (a) {
        if (object_records[g_944c][g_9450].f_54) {
            object_records[g_944c][g_9450].f_0e = 0;
            object_records[g_944c][g_9450].f_0c = object_records[g_944c][g_9450].f_0e;
        }
        fn_08_5df2(g_944c, g_9450, g_944a, g_944e, g_9436);
    }
}

/* The original reads the record's word at +4 and drops it; a volatile
 * read reproduces that. */
/* 8:698a */
void fn_08_698a(int16_t a)
{
    int16_t type;
    int16_t idx;

    object_records[g_944a][g_944e].f_1c = 1;
    object_records[g_944a][g_944e].f_0c = g_52e0.x;
    object_records[g_944a][g_944e].f_0e = g_52e0.y;
    if (a) {
        object_records[g_944a][g_944e].f_04.x;
        if (object_records[g_944a][g_944e].f_54) {
            object_records[g_944a][g_944e].f_0e = 0;
            object_records[g_944a][g_944e].f_0c = object_records[g_944a][g_944e].f_0e;
        }
        fn_08_5df2(g_944a, g_944e, g_944c, g_9450, g_9438);
    }
}

/* Swap two ints. */
/* 8:4d60 */
void fn_08_4d60(int16_t *a, int16_t *b)
{
    int16_t t;

    t = *a;
    *a = *b;
    *b = t;
}

/* Swap two longs. */
/* 8:4d94 */
void fn_08_4d94(int32_t *a, int32_t *b)
{
    int32_t t;

    t = *a;
    *a = *b;
    *b = t;
}

/* Swap two bytes. */
/* 8:4dde */
void fn_08_4dde(uint8_t *a, uint8_t *b)
{
    int16_t t;

    t = *a;
    *a = *b;
    *b = t;
}

/* 8:7ba8 */
BOOL fn_08_7ba8(POINT pt)
{
    RECT r;

    SetRect(&r, -50, -50, LO16(g_90ea) + 50, HI16(g_90ea) + 50);
    return PtInRect(&r, pt);
}

/* Shift a 7-entry history down and record a new entry [inferred]. */
/* 8:81f8 */
void fn_08_81f8(char a, char b)
{
    int16_t i;

    for (i = 6; i >= 0; i--) {
        g_937a[i + 1] = g_937a[i];
        g_938a[i + 1] = g_938a[i];
        g_9392[i + 1] = g_9392[i];
    }
    g_937a[0] = (int16_t)(g_1e68 / 10);
    g_938a[0] = a;
    g_9392[0] = b;
}

/* Add to the score DS:5078 (capped at 500000) [inferred]. */
/* 8:7be8 */
void fn_08_7be8(int16_t a, int16_t b, int16_t c, int16_t d)
{
    if (a == g_9324 && b == main_ship)
        return;
    if (d) {
        g_5078 = g_5078 + g_0b0e[a] > 500000L ? 500000L : g_5078 + g_0b0e[a];
        g_1e58 += g_0b0e[a];
        if (a == g_9324)
            g_5078 += g_7090[b].f_0d8 * 2;
        if (a == 8 && object_records[8][b].f_54)
            g_5078 += g_0b0e[a];
    } else {
        g_5078 += g_0b38[a] * c;
        if (a == 8 && object_records[8][b].f_44 > 2000)
            g_5078 += g_0b38[a] * c * 2;
        if (a == g_9324)
            g_5078 += g_7090[b].f_0d8 / 8;
    }
}

/* 8:7ce0 */
void fn_08_7ce0(int16_t a, int16_t b, int16_t c, int16_t d)
{
    int16_t i;
    int16_t n;

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

/* 8:804a */
void fn_08_804a(int16_t a, int16_t b, int16_t c)
{
    int16_t k;
    int16_t j;

    for (k = 0; k < 4; k++) {
        if (g_1e90[k].f_00 == -1 || g_1e90[k].f_0a <= 5) {
            if (g_1e90[k].f_00 > -1) {
                for (j = 4; j < 45; j++) {
                    if (g_1e90[j].f_00 == -1) {
                        g_1e90[j].f_00 = g_1e90[k].f_00;
                        g_1e90[j].f_02 = g_1e90[k].f_02;
                        g_1e90[j].f_06 = g_1e90[k].f_06;
                        g_1e90[j].f_08 = g_1e90[k].f_08;
                        g_1e90[j].f_10 = g_1e90[k].f_10;
                        g_1e90[j].f_0a = g_1e90[k].f_0a;
                        g_5170[j] = g_5170[k];
                        g_5224[j] = g_5224[k];
                        if (j > g_9434)
                            g_9434 = j;
                        g_1e90[j].f_0c = g_1e90[k].f_0c;
                        g_1e90[j].f_0e = g_1e90[k].f_0e;
                        break;
                    }
                }
            }
            g_1e90[k].f_00 = 1;
            g_1e90[k].f_02 = min(b / 630 + 2, 14);
            g_1e90[k].f_0a = 7;
            g_1e90[k].f_0c = 2;
            if (k > g_9434)
                g_9434 = k;
            if (g_6098[a].f_7a == g_9324 && g_7090[g_6098[a].f_7c].f_0e3)
                g_1e90[k].f_0e = 10;
            else
                g_1e90[k].f_0e = 15;
            g_9430++;
            g_1e90[k].f_04 = 2;
            g_1e90[k].f_06 = 0x1e;
            g_1e90[k].f_08 = a;
            g_5224[k].x = g_6098[a].f_30[c][0];
            g_5224[k].y = g_6098[a].f_48[c][0];
            g_5170[k].x = g_6098[a].x[c][0];
            g_5170[k].y = g_6098[a].y[c][0];
            return;
        }
    }
}

/* Collect the objects inside the view rectangles into the draw list
 * DS:507c/50e0 [inferred]. */
/* 8:4e14 */
void fn_08_4e14(void)
{
    int16_t t;
    int16_t i;
    int16_t r;
    int16_t unused[6];
    int16_t found;
    int16_t mode;

    mode = 1;
    if (subgame_active == 0) {
        if (g_9e49 > 6 || g_9e49 < 3)
            mode = 0;
        for (t = g_9326; t <= g_9324; t++) {
            if (mode == 0 || t != 7) {
                if (t == 14 && mode)
                    mode = 2;
                for (i = 0; i < g_9406[t]; i++) {
                    if (object_records[t][i].f_18 == 0 && object_records[t][i].f_44 != 0
                        && (t != 8 || g_3d50[i].f_30 != 4)
                        && (mode < 2 || i != g_952e)) {
                        for (r = found = 0; r < g_9158; r++) {
                            if (PtInRect(&g_23e0[r], object_records[t][i].f_04)) {
                                object_records[t][i].f_1c = 0;
                                g_507c[g_9146] = t;
                                g_50e0[g_9146] = i;
                                g_9146++;
                                found = 1;
                                break;
                            }
                        }
                        if (found) {
                            object_records[t][i].f_1a = 1;
                        } else if (object_records[t][i].f_1a <= 0) {
                            object_records[t][i].f_1a = 0;
                            object_records[t][i].f_00.x = -1000;
                            object_records[t][i].f_00.y = -1000;
                        } else {
                            object_records[t][i].f_1a = -1;
                        }
                    }
                }
            }
        }
    } else {
        for (t = g_9326; t <= g_9324; t++) {
            for (i = 0; i < g_9406[t]; i++) {
                object_records[t][i].f_1c = 0;
                g_507c[g_9146] = t;
                g_50e0[g_9146] = i;
                g_9146++;
                object_records[t][i].f_1a = 1;
            }
        }
    }
    if (rand() % 9 == 0) {
        for (t = 0; t < g_9146; t++) {
            if (object_records[g_507c[t]][g_50e0[t]].f_50 && g_507c[t] != g_9324) {
                for (i = 0; i < g_9146; i++) {
                    if (object_records[g_507c[i]][g_50e0[i]].f_18 == 0 && i != t) {
                        fn_11_9fdc(g_507c[t], g_50e0[t]);
                        break;
                    }
                }
            }
        }
    }
}

/* Bounce of two round bodies of sizes a and b at positions *p1/*p2 and
 * *p3/*p4 with velocities (*p5 - *p7)... [inferred]; returns 0 when they
 * move apart too fast, else nothing defined (no return, as in the
 * original). */
/* The ratio goes through the dead local u14: that keeps the dot product
 * evaluated before the divisor. */
/* 8:7d70 */
int16_t fn_08_7d70(int16_t *p8, int16_t *p7, int16_t *p6, int16_t *p5,
                          int16_t *p4, int16_t *p3, int16_t *p2, int16_t *p1,
                          int16_t b, int16_t a)
{
    int16_t dx;
    int16_t dy;
    int16_t sum;
    int16_t vx;
    int16_t vy;
    int16_t c;
    int16_t d1;
    int16_t d2;
    int16_t u14;
    int16_t ux;
    int16_t uy;
    int16_t k;
    int16_t r2;
    int16_t r1;
    int32_t l;

    dx = b / 2 - a / 2 - *p2 + *p4;
    dy = b / 2 - a / 2 - *p1 + *p3;
    sum = a / 2 + b / 2;
    vx = *p8 - *p6;
    vy = *p7 - *p5;
    d1 = fn_08_35d0(dx, dy);
    if (d1 == 0)
        d1 = 1;
    if (fn_09_88ba(vx) < 10 && fn_09_88ba(vy) < 10) {
        *p8 = *p6 - (int16_t)(dx * 15) / d1;
        *p7 = *p5 - (int16_t)(dy * 15) / d1;
        vx = *p8 - *p6;
        vy = *p7 - *p5;
    }
    d2 = fn_08_35d0(vx, vy);
    if (d2 == 0)
        d2 = 1;
    l = (int32_t)vx * dx + (int32_t)vy * dy;
    if ((u14 = (int16_t)(l * 100 / ((int32_t)d2 * d1))) > 15)
        return 0;
    c = sum;
    ux = (int16_t)(vx * 100) / d2;
    uy = (int16_t)(vy * 100) / d2;
    if (vy > 0)
        r1 = (int16_t)((b / 2 - a / 2 - *p1 + *p3 + c) * 100)
            / (1 > fn_09_88ba(uy) ? 1 : fn_09_88ba(uy));
    else
        r1 = (int16_t)((a / 2 - b / 2 - *p3 + *p1 + c) * 100)
            / (1 > fn_09_88ba(uy) ? 1 : fn_09_88ba(uy));
    if (vx > 0)
        r2 = (int16_t)((b / 2 - a / 2 - *p2 + *p4 + c) * 100)
            / (1 > fn_09_88ba(ux) ? 1 : fn_09_88ba(ux));
    else
        r2 = (int16_t)((a / 2 - b / 2 - *p4 + *p2 + c) * 100)
            / (1 > fn_09_88ba(ux) ? 1 : fn_09_88ba(ux));
    k = fn_09_88ba(r1) > fn_09_88ba(r2) ? r2 : r1;
    /* dead stores: only their loads remain */
    l = (int32_t)b - (int32_t)a;
    u14 = *p3;
    *p4 += (int16_t)(k * ux) / -100;
    *p3 += (int16_t)(k * uy) / -100;
}

/* Blast wave of particle j: push and damage every object near it
 * [inferred]. */
/* 8:5ab0 */
void fn_08_5ab0(int16_t j)
{
    int16_t kind;
    int16_t st;
    int16_t si_;
    int16_t t;
    int16_t i;
    int16_t d;
    int16_t dy;
    int16_t dx;
    int16_t f;
    int32_t vx;
    int32_t vy;
    int32_t s;
    POINT pos;

    st = g_1e90[j].f_06;
    si_ = g_1e90[j].f_08;
    kind = g_1e90[j].f_0a;
    pos.x = g_5224[j].x;
    pos.y = g_5224[j].y;
    if (g_1318 > 6)
        return;
    for (t = g_9326; t <= g_9324; t++) {
        for (i = 0; i < g_9406[t]; i++) {
            if (object_records[t][i].f_18 == 0 && object_records[t][i].f_44 != 0
                && !(t == g_9324 && i == g_952e && object_records[t][i].f_1a == 0)
                && !(kind == -250 && t == st && i == si_)) {
                d = fn_08_285a(&dy, &dx, pos, object_records[t][i].f_04);
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
                if ((int16_t)((min(object_records[st][si_].f_48, 7) + 8) * 15) > d && d != 0) {
                    f = (int16_t)(object_records[st][si_].f_48 * 600) / d;
                    f = (int16_t)(f * 15) / (1 > (int16_t)fn_08_1290((int32_t)object_records[t][i].f_44, 25L) ? 1
                                  : (int16_t)fn_08_1290((int32_t)object_records[t][i].f_44, 25L));
                    if (t == 2)
                        f *= 3;
                    object_records[t][i].f_2f += 2;
                    if (d < 150)
                        object_records[t][i].f_2f += 2;
                    if (object_records[t][i].f_2f > 9)
                        object_records[t][i].f_2f = 9;
                    g_943a = st;
                    g_943c = si_;
                    g_0b0c = 1;
                    if (g_1e90[j].f_00 != 0)
                        g_0b0c = 0;
                    fn_08_5df2(t, i, st, si_, -f);
                    g_0b0c = 1;
                    s = (int16_t)(object_records[st][si_].f_48 * 250) / (d / 10) / ((int16_t)(object_records[t][i].f_44 + 100) / 100);
                    vx = s * dy / d;
                    vy = s * dx / d;
                    object_records[t][i].f_0c += vx;
                    object_records[t][i].f_0e += vy;
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
/* 8:6afa */
int16_t fn_08_6afa(WORD a, WORD b)
{
    int16_t u4;
    int16_t u6;
    int16_t u8;
    int16_t ua;
    int16_t flag;
    int16_t t1;
    int16_t i1;
    int16_t t2;
    int16_t i2;

    t1 = HIBYTE(a);
    i1 = LOBYTE(a);
    t2 = HIBYTE(b);
    i2 = LOBYTE(b);
    if (object_records[t1][i1].f_54 != 0 && object_records[t2][i2].f_54 != 0)
        return 0;
    if (object_records[t1][i1].f_18 != 0 || !PtInRect(&g_5148, object_records[t1][i1].f_00)
        || (SetRect(&g_5150, object_records[t1][i1].f_00.x, object_records[t1][i1].f_00.y,
                object_records[t1][i1].f_00.x + object_records[t1][i1].f_22,
                object_records[t1][i1].f_00.y + object_records[t1][i1].f_22), 0)
        || !IntersectRect(&g_5158, &g_5160, &g_5150)
        || t1 == 10 && object_records[t1][i1].f_32 == t2 && object_records[t1][i1].f_34 == i2)
        return 0;
    if (t2 == 10 && object_records[t2][i2].f_32 == t1 && object_records[t2][i2].f_34 == i1)
        return 0;
    if (object_records[t1][i1].f_2e != 0 && (t1 != g_9324 || g_7090[i1].f_026[4] != 2))
        return 0;
    if (object_records[t2][i2].f_2e != 0 && (t2 != g_9324 || g_7090[i2].f_026[4] != 2))
        return 0;
    if (t1 == 6 && g_6670[i1 + 4].r.right < 10 && g_6670[i1 + 4].r.left == t2 && g_6670[i1 + 4].r.top == i2)
        return 0;
    if (t2 == 6 && g_6670[i2 + 4].r.right < 10 && g_6670[i2 + 4].r.left == t1 && g_6670[i2 + 4].r.top == i1)
        return 0;
    if ((t2 == 7 || t1 == 7) && g_9e49 == 1)
        g_9e49 = 0;
    object_records[t1][i1].f_1c = 1;
    object_records[t2][i2].f_1c = object_records[t1][i1].f_1c;
    if (t1 == g_9324 && i1 == main_ship)
        flag = 1;
    if (t2 == g_9324 && i2 == main_ship)
        flag = 0;
    if (object_records[t1][i1].f_54 != 0)
        flag = 1;
    if (object_records[t2][i2].f_54 != 0)
        flag = 0;
    if (flag) {
        g_52e0.x = object_records[t1][i1].f_0c;
        g_52e0.y = object_records[t1][i1].f_0e;
        if (object_records[t1][i1].f_1a)
            g_52e4 = object_records[t1][i1].f_00;
        else
            g_52e4 = fn_08_29ea(object_records[t1][i1].f_04);
        g_944c = t2;
        g_9450 = i2;
        g_944a = t1;
        g_944e = i1;
        if (subgame_active == 0) {
            object_sizes[1] = object_records[t2][i2].f_20 + 2;
            object_sizes[0] = object_records[t1][i1].f_20 + 2;
        } else {
            object_sizes[1] = object_records[t2][i2].f_22;
            object_sizes[0] = object_records[t1][i1].f_22;
        }
        object_masses[0] = object_records[t1][i1].f_44;
    } else {
        g_52dc.x = object_records[t1][i1].f_0c;
        g_52dc.y = object_records[t1][i1].f_0e;
        if (object_records[t1][i1].f_1a)
            g_52e8 = object_records[t1][i1].f_00;
        else
            g_52e8 = fn_08_29ea(object_records[t1][i1].f_04);
        g_944c = t1;
        g_9450 = i1;
        g_944a = t2;
        g_944e = i2;
        if (subgame_active == 0) {
            object_sizes[1] = object_records[t1][i1].f_20 + 2;
            object_sizes[0] = object_records[t2][i2].f_20 + 2;
        } else {
            object_sizes[1] = object_records[t1][i1].f_22;
            object_sizes[0] = object_records[t2][i2].f_22;
        }
        object_masses[1] = object_records[t1][i1].f_44;
    }
    return 1;
}

/* Find an object that collides with r ((type << 8) | index) [inferred]:
 * returns its reference, 0x1000 for the sub-game border, or -1. */
/* 8:50aa */
int16_t fn_08_50aa(WORD r)
{
    int16_t i;
    int16_t u6;
    int16_t t;
    int16_t idx;
    WORD res;

    t = HIBYTE(r);
    idx = LOBYTE(r);
    if (object_records[t][idx].f_1c == 0) {
        if (g_9320 == 6 && object_records[t][idx].f_1a == 0 && g_9208 > 1) {
            object_records[t][idx].f_00 = fn_08_29ea(object_records[t][idx].f_04);
            SetRect(&g_5160, object_records[t][idx].f_00.x, object_records[t][idx].f_00.y,
                object_records[t][idx].f_00.x + object_records[t][idx].f_22,
                object_records[t][idx].f_00.y + object_records[t][idx].f_22);
            SetRect(&g_5148, object_records[t][idx].f_00.x - SC(70), object_records[t][idx].f_00.y - SC(70),
                object_records[t][idx].f_00.x + object_records[t][idx].f_22 + SC(15),
                object_records[t][idx].f_00.y + object_records[t][idx].f_22 + SC(15));
            for (i = 0; i <= g_9316; i++) {
                if (object_records[14][i].f_1a == 0 && object_records[14][i].f_18 == 0
                    && (t != 14 || idx != i)) {
                    object_records[14][i].f_00 = fn_08_29ea(object_records[14][i].f_04);
                    res = (char)i | 0xe00;
                    if (fn_08_6afa(res, r))
                        return res;
                }
            }
        } else {
            SetRect(&g_5160, object_records[t][idx].f_00.x, object_records[t][idx].f_00.y,
                object_records[t][idx].f_00.x + object_records[t][idx].f_22,
                object_records[t][idx].f_00.y + object_records[t][idx].f_22);
            SetRect(&g_5148, object_records[t][idx].f_00.x - SC(70), object_records[t][idx].f_00.y - SC(70),
                object_records[t][idx].f_00.x + object_records[t][idx].f_22 + SC(15),
                object_records[t][idx].f_00.y + object_records[t][idx].f_22 + SC(15));
            for (i = 0; i < g_9146; i++) {
                if (!(g_507c[i] < t || g_507c[i] <= t && g_50e0[i] == idx)) {
                    if (object_records[g_507c[i]][g_50e0[i]].f_1c == 0) {
                        res = g_50e0[i] | g_507c[i] << 8;
                        if (fn_08_6afa(res, r))
                            return res;
                    }
                }
            }
        }
    }
    if (subgame_active != 0) {
        int16_t flag;

        flag = 0;
        if (object_records[t][idx].f_00.x <= g_88c4.x) {
            object_records[16]->f_00.x = g_88c4.x - object_records[t][idx].f_22;
            object_records[16]->f_00.y = object_records[t][idx].f_00.y + g_88c4.y;
            flag = 1;
        } else if (g_88c4.x - object_records[t][idx].f_22 + g_88c0.x < object_records[t][idx].f_00.x) {
            object_records[16]->f_00.x = g_88c4.x + g_88c0.x;
            object_records[16]->f_00.y = object_records[t][idx].f_00.y + g_88c4.y;
            flag = 1;
        } else if (object_records[t][idx].f_00.y <= g_88c4.y) {
            object_records[16]->f_00.y = g_88c4.y - object_records[t][idx].f_22;
            object_records[16]->f_00.x = object_records[t][idx].f_00.x + g_88c4.x;
            flag = 1;
        } else if (g_88c4.y - object_records[t][idx].f_22 + g_88c0.y < object_records[t][idx].f_00.y) {
            object_records[16]->f_00.y = g_88c4.y + g_88c0.y;
            object_records[16]->f_00.x = object_records[t][idx].f_00.x + g_88c4.x;
            flag = 1;
        } else {
            fn_18_2c1e(t, idx);
        }
        if (flag != 0) {
            g_52e0.x = 0;
            g_52e0.y = 0;
            g_52e4 = object_records[16]->f_00;
            g_944c = t;
            g_9450 = idx;
            g_944a = 16;
            g_944e = 0;
            object_sizes[1] = object_records[t][idx].f_22;
            object_sizes[0] = object_records[t][idx].f_22;
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
int16_t fn_08_3688(int16_t n)
{
    int16_t i;
    int16_t u6;
    int16_t j;
    int16_t k;
    int16_t res;
    int16_t pad[7];

    for (j = 0; j < g_6098[n].count; j++) {
        g_5168[j].x = g_6098[n].f_30[j][0];
        g_5168[j].y = g_6098[n].f_48[j][0];
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
    if (g_6098[n].f_7a == 14
        && object_records[g_7090[g_6098[n].f_7c].f_032.a][g_7090[g_6098[n].f_7c].f_032.b].f_1a == 0) {
        res = fn_08_6f3c(g_7090[g_6098[n].f_7c].f_032.a, g_7090[g_6098[n].f_7c].f_032.b, n, k);
        if (res == 2)
            return 2;
        if (res == 1)
            return 1;
    }
    for (j = 0; j < g_6098[n].count; j++) {
        g_5168[j].x = g_6098[n].f_30[j][0];
        g_5168[j].y = g_6098[n].f_48[j][0];
    }
    for (i = 0; i < g_9318; i++) {
        RECT r;

        SetRect(&r, g_6670[i].r.left, g_6670[i].r.top - 5, g_6670[i].r.right, g_6670[i].r.bottom + 5);
        if (PtInRect(&r, g_5168[0]))
            return 2;
        if (PtInRect(&r, g_5168[1]))
            return 2;
    }
    if (subgame_active != 0) {
        int16_t flag;
        int16_t ok;
        int16_t a28;
        int16_t a2a;

        j = flag = 0;
        for (; j < g_6098[n].count; j++) {
            if (g_6098[n].x[j][0] <= g_88c4.x) {
                object_records[16]->f_00.x = g_88c4.x - 30;
                object_records[16]->f_00.y = g_6098[n].y[j][0] + g_88c4.y - 15;
                flag = 1;
            } else if (g_88c4.x + g_88c0.x - 2 < g_6098[n].x[j][0]) {
                object_records[16]->f_00.x = g_88c4.x + g_88c0.x;
                object_records[16]->f_00.y = g_6098[n].y[j][0] + g_88c4.y - 15;
                flag = 1;
            } else if (g_6098[n].y[j][0] <= g_88c4.y) {
                object_records[16]->f_00.y = g_88c4.y - 30;
                object_records[16]->f_00.x = g_6098[n].x[j][0] + g_88c4.x - 15;
                flag = 1;
            } else if (g_88c4.y + g_88c0.y - 2 < g_6098[n].y[j][0]) {
                object_records[16]->f_00.y = g_88c4.y + g_88c0.y;
                object_records[16]->f_00.x = g_6098[n].x[j][0] + g_88c4.x - 15;
                flag = 1;
            } else if (fn_18_2c1e(30, n) == 2) {
                return 2;
            }
            if (flag != 0) {
                k = 14 - g_6098[n].z[1][5] * 14 / g_6098[n].z[1][4];
                if (g_6098[n].z[1][5] < 20)
                    k = 23;
                if (g_6098[n].f_7a == g_9324
                    && (g_6098[n].f_7c == main_ship
                        || g_96d2[g_7090[g_6098[n].f_7c].f_04e].f_38 == 7
                            && g_7090[g_6098[n].f_7c].f_05e == 0))
                    k <<= 1;
                if (g_6098[n].f_7a == g_9324)
                    k = g_96d2[g_7090[g_6098[n].f_7c].f_04e].f_32 * k / 250;
                g_943c = n;
                g_944a = 16;
                g_944e = 0;
                g_9450 = n;
                a2a = g_6098[n].z[1][2] * 5;
                a28 = g_6098[n].z[1][3] * 5;
                ok = fn_10_7dd4(&a2a, &a28, &object_records[16]->f_0c, &object_records[16]->f_0e,
                    &g_6098[n].x[j][0], &g_6098[n].y[j][0], &object_records[16]->f_00.x, &object_records[16]->f_00.y,
                    2, g_944c = g_943a = 30, k, 20000, &g_9436, &g_9438);
                if (ok == 0)
                    break;
                fn_10_754a(0x11, 30, n, 2);
                g_6098[n].z[1][2] = a2a / 5;
                g_6098[n].z[1][3] = a28 / 5;
                g_6098[n].f_30[j][0] = (int16_t)(g_6098[n].x[j][0] * g_88cc / g_88c0.x);
                g_6098[n].f_48[j][0] = (int16_t)(g_6098[n].y[j][0] * g_88cc / g_88c0.x);
                if (g_9208 >= 2 && k * g_9436 > 600)
                    fn_08_804a(n, k * g_9436, j);
                return 1;
            }
        }
    }
    return 0;
}

/* Move and draw shot group n one step (s: speed factor) [inferred];
 * returns 1 while the group is alive. w is read uninitialised when the
 * group was already finished (as in the original). */
/* 8:3aec */
int16_t fn_08_3aec(int16_t n, int16_t s)
{
    int16_t u4;
    int16_t u6;
    int16_t u8;
    int16_t sz;
    int16_t w;
    int16_t m;
    int16_t j;
    int16_t v;
    int16_t res;

    if (g_6098[n].z[1][5] >= 0 && g_6098[n].z[1][4] > g_6098[n].z[1][5]) {
        sz = (g_9208 + 1 >> 1) + 3;
        if (subgame_active != 0) {
            w = g_9156 + 1;
            fn_18_4dc4(n);
        } else
            w = SC(2);
        fn_08_0764(n, 0);
        res = fn_08_3688(n);
        if (res != 0 && g_6098[n].f_7a == g_9324 && g_6098[n].f_7c == main_ship)
            g_6098[n].f_7e++;
        if (res == 2) {
            g_6098[n].z[1][5] = -1;
            for (m = sz; m > -1; m--)
                for (j = 0; j < g_6098[n].count; j++)
                    if (VIEWP(int16_t *, g_6098[n].f_84, 0)[j] != 0)
                        PatBlt(main_dc, g_6098[n].x[j][m], g_6098[n].y[j][m], w, w,
                               BLACKNESS);
            return 1;
        }
        if ((res == 1 || g_6098[n].f_90 == g_05cc) && g_05cc != 0) {
            if (g_6098[n].f_90 == g_05cc) {
                fn_10_754a(0x11, 0x1e, n, 2);
                g_6098[n].z[1][2] = g_6098[n].f_88;
                g_6098[n].z[1][3] = g_6098[n].f_8a;
                g_6098[n].f_30[0][0] += g_6098[n].z[1][2];
                g_6098[n].f_48[0][0] += g_6098[n].z[1][3];
            }
            if (g_9320 == 6)
                fn_11_5626(n);
        }
        v = g_6098[n].z[1][5] * 8 / g_6098[n].z[1][4];
        if (g_6098[n].f_7a == g_9324)
            SelectObject(main_dc, g_3b4c[v + g_7090[g_6098[n].f_7c].f_0e3 * 10]);
        else
            SelectObject(main_dc, g_3b4c[v + 10]);
        for (j = 0; j < g_6098[n].count; j++) {
            if (VIEWP(int16_t *, g_6098[n].f_84, 0)[j] != 0) {
                g_6098[n].x[j][0] += (int16_t)(object_records[g_6098[n].f_7a][g_6098[n].f_7c].f_0c * s) / -50;
                g_6098[n].y[j][0] += (int16_t)(object_records[g_6098[n].f_7a][g_6098[n].f_7c].f_0e * s) / -50;
                if (g_6098[n].x[j][0] > 0 && g_6098[n].x[j][0] < LO16(g_90ea)
                    && g_6098[n].y[j][0] > 0 && g_6098[n].y[j][0] < HI16(g_90ea)
                    || subgame_active != 0)
                    PatBlt(main_dc, g_6098[n].x[j][0], g_6098[n].y[j][0], w, w, PATCOPY);
            }
        }
        if (g_6098[n].x[0][3] != -100)
            for (j = 0; j < g_6098[n].count; j++)
                if (VIEWP(int16_t *, g_6098[n].f_84, 0)[j] != 0)
                    PatBlt(main_dc, g_6098[n].x[j][sz], g_6098[n].y[j][sz], w, w,
                           BLACKNESS);
        g_6098[n].z[1][5]++;
        for (m = sz; m > 0; m--)
            for (j = 0; j < g_6098[n].count; j++) {
                g_6098[n].x[j][m] = g_6098[n].x[j][m - 1];
                g_6098[n].y[j][m] = g_6098[n].y[j][m - 1];
            }
        for (j = 0; j < g_6098[n].count; j++) {
            if (VIEWP(int16_t *, g_6098[n].f_84, 0)[j] != 0) {
                g_6098[n].f_30[j][0] += g_6098[n].z[1][2];
                if (subgame_active == 0) {
                    if (g_6098[n].f_30[j][0] > LO16(g_05a0) * 8)
                        g_6098[n].f_30[j][0] = 0;
                    if (g_6098[n].f_30[j][0] < 0)
                        g_6098[n].f_30[j][0] = LO16(g_05a0) * 8;
                }
                g_6098[n].f_48[j][0] += g_6098[n].z[1][3];
                if (subgame_active == 0) {
                    if (g_6098[n].f_48[j][0] > HI16(g_05a0) * 8)
                        g_6098[n].f_48[j][0] = 0;
                    if (g_6098[n].f_48[j][0] < 0)
                        g_6098[n].f_48[j][0] = HI16(g_05a0) * 8;
                }
            }
        }
        v = g_6098[n].z[1][5] & 0xf;
        if (v == 0xf && g_6098[n].count == 2) {
            g_6098[n].f_30[0][0] += g_6098[n].z[0][4] >> 2;
            g_6098[n].f_30[1][0] -= g_6098[n].z[0][4] >> 2;
            g_6098[n].f_48[0][0] += g_6098[n].z[0][5] >> 2;
            g_6098[n].f_48[1][0] -= g_6098[n].z[0][5] >> 2;
        }
    }
    if (g_6098[n].z[1][4] <= g_6098[n].z[1][5]) {
        g_6098[n].z[1][5] = -1;
        for (m = 5; m > -1; m--)
            for (j = 0; j < g_6098[n].count; j++)
                PatBlt(main_dc, g_6098[n].x[j][m], g_6098[n].y[j][m], w, w, BLACKNESS);
    }
    if (g_6098[n].z[1][5] != -1 || g_9136 != 0)
        return 1;
    return 0;
}

/* Step explosion/effect i of the g_1e90 table [inferred]. */
/* 8:3fbe */
void fn_08_3fbe(int16_t i)
{
    int16_t a;
    int16_t b;
    int16_t u8;
    int16_t sz;
    int16_t c;
    int16_t m;
    int16_t w;
    int16_t t;
    int16_t k;
    int16_t v;
    POINT p;
    int16_t pad[4];
    int16_t found;

    if (g_1e90[i].f_00 >= 0 && g_1e90[i].f_02 >= g_1e90[i].f_00) {
        if (g_1e90[i].f_0a == 1 || g_1e90[i].f_0a < 0) {
            if ((DWORD)g_1e90[i].f_10 > now_ms)
                return;
            if (g_1e90[i].f_00 == 1) {
                g_5144 = g_5224[i];
                fn_10_754a(0x45, 0, 0, 3);
            }
        }
        if (g_1e90[i].f_0a <= 5) {
            m = g_1e90[i].f_00 - 1;
            sz = SC(m * 6 + 10);
            c = 0;
            if (g_1e90[i].f_02 - 1 <= g_1e90[i].f_00) {
                if (g_1e90[i].f_0a != -250) {
                    PatBlt(main_dc, g_5170[i].x - SC(26), g_5170[i].y - SC(26), SC(52), SC(52),
                           BLACKNESS);
                    if (object_records[g_9324][main_ship].f_18 == 0 && g_951a == 0 && g_7090[main_ship].flag != 0)
                        fn_07_1208();
                    if (g_1e90[i].f_06 == g_9324 && object_records[g_9324][g_1e90[i].f_08].f_18 == 0
                        && g_1e90[i].f_0a != 1)
                        fn_10_754a(0x6a, g_9324, g_1e90[i].f_08, 1);
                    if (g_1e90[i].f_0a != 1) {
                        t = g_1e90[i].f_06;
                        k = g_1e90[i].f_08;
                        p = fn_08_29ea(object_records[t][k].f_04);
                        w = object_records[t][k].f_22;
                        PatBlt(main_dc, p.x, p.y, w, w, BLACKNESS);
                    }
                }
            } else {
                if (g_1e90[i].f_0a > -1 && fn_08_7ba8(g_5170[i])) {
                    DWORD rop;

                    rop = SRCCOPY;
                    BitBlt(main_dc, g_5170[i].x - (sz >> 1), g_5170[i].y - (sz >> 1), sz, sz,
                           g_39fc, SC(g_0b70[min(m, 7)]), 0, rop);
                }
                if (g_1e90[i].f_00 % 6 == 0 && g_1e90[i].f_0a != 1)
                    fn_08_5ab0(i);
            }
        } else {
            if (g_1e90[i].f_00 == 1) {
                if (g_1e90[i].f_0a == 6)
                    fn_07_342e(i, g_1e90[i].f_06, g_1e90[i].f_08);
                else
                    fn_08_9694(i, g_1e90[i].f_06, g_1e90[i].f_08);
                if (g_1e90[i].f_06 <= g_9324)
                    PatBlt(main_dc, object_records[g_1e90[i].f_06][g_1e90[i].f_08].f_00.x,
                           object_records[g_1e90[i].f_06][g_1e90[i].f_08].f_00.y,
                           object_records[g_1e90[i].f_06][g_1e90[i].f_08].f_22,
                           object_records[g_1e90[i].f_06][g_1e90[i].f_08].f_22, BLACKNESS);
            }
            if (g_1e90[i].f_00 == 5 && g_1e90[i].f_0a == 6)
                fn_08_5ab0(i);
            for (a = 0; a < 5; a += g_1e90[i].f_04) {
                for (b = 0; b < 5; b += g_1e90[i].f_04) {
                    fn_08_07d2(i, a, b);
                    if (g_1e90[i].f_0a == 6)
                        v = object_records[g_1e90[i].f_06][g_1e90[i].f_08].f_24;
                    if (g_1e90[i].f_0a == 6) {
                        BitBlt(main_dc, g_2414[i][a][b].p.x, g_2414[i][a][b].p.y,
                               g_1e90[i].f_0c, g_1e90[i].f_0c, g_5e98[i],
                               g_1e90[i].f_0c * a + v, g_1e90[i].f_0c * b + v, SRCCOPY);
                    } else {
                        SelectObject(main_dc, g_576c[g_1e90[i].f_0e + g_0b6a]);
                        PatBlt(main_dc, g_2414[i][a][b].p.x, g_2414[i][a][b].p.y,
                               g_1e90[i].f_0c, g_1e90[i].f_0c, PATCOPY);
                    }
                    PatBlt(main_dc, g_2414[i][a][b].q.x, g_2414[i][a][b].q.y,
                           g_1e90[i].f_0c, g_1e90[i].f_0c, BLACKNESS);
                    if (g_1e90[i].f_02 - g_1e90[i].f_00 == 1) {
                        PatBlt(main_dc, g_2414[i][a][b].p.x, g_2414[i][a][b].p.y,
                               g_1e90[i].f_0c, g_1e90[i].f_0c, BLACKNESS);
                        if (g_951a == 0)
                            fn_07_1208();
                    }
                    g_2414[i][a][b].s.x += g_2414[i][a][b].f_10 * g_1e90[i].f_00 * g_1e90[i].f_00 * 9
                        / (g_1e90[i].f_02 * g_1e90[i].f_02) + g_2414[i][a][b].f_0c;
                    if (g_2414[i][a][b].s.x > LO16(g_05a0) * 8)
                        g_2414[i][a][b].s.x = 0;
                    if (g_2414[i][a][b].s.x < 0)
                        g_2414[i][a][b].s.x = LO16(g_05a0) * 8;
                    g_2414[i][a][b].s.y += g_2414[i][a][b].f_12 * g_1e90[i].f_00 * g_1e90[i].f_00 * 9
                        / (g_1e90[i].f_02 * g_1e90[i].f_02) + g_2414[i][a][b].f_0e;
                    if (g_2414[i][a][b].s.y > HI16(g_05a0) * 8)
                        g_2414[i][a][b].s.y = 0;
                    if (g_2414[i][a][b].s.y < 0)
                        g_2414[i][a][b].s.y = HI16(g_05a0) * 8;
                }
            }
        }
        g_1e90[i].f_00++;
    }
    if (g_1e90[i].f_02 <= g_1e90[i].f_00) {
        found = 0;
        g_1e90[i].f_00 = -1;
        for (a = 44; a >= 0; a--) {
            if (g_1e90[a].f_00 != -1) {
                g_9434 = a;
                found = 1;
                break;
            }
        }
        if (found == 0)
            g_9434 = 0;
        g_9430 = g_9430 - 1 < 0 ? 0 : g_9430 - 1;
        if (subgame_active != 0)
            fn_18_5350(g_5170[i].x, g_5170[i].y);
        if (i < 4 && g_1e90[i].f_0a == 6 && g_5e98[i] != 0) {
            if (g_1e90[i].f_06 == 1) {
                SelectObject(g_5e98[i], g_5ea0[i]);
                DeleteDC(g_5e98[i]);
            }
            g_5e98[i] = 0;
        }
    }
}

/* The class records (0xad bytes) seen from DS:96da [inferred]. */

/* Apply dmg points of damage to ship i, hit by object (g_943a, g_943c)
 * [inferred]; returns 1 when the ship is destroyed. */
/* 8:45e0 */
int16_t fn_08_45e0(int16_t unused, int16_t i, int16_t dmg)
{
    int16_t vx;
    int16_t vy;
    int16_t px;
    int16_t py;
    int16_t sz;
    POINT dv;
    POINT r;
    int16_t u16;
    int16_t k;
    int16_t u1a;
    int16_t cls;
    int16_t pad[2];

    if (g_7090[i].f_147 == 1 && subgame_active == 0)
        return 0;
    if (i == main_ship && g_104c[0].a != 0)
        return 0;
    if (g_7090[i].flag == 0 && !(g_943a == g_9324 && i == g_943c) && g_943a != 11) {
        if (g_7090[i].f_084 - 5500 < now_ms)
            fn_12_274a(g_9324, i);
        if (subgame_active != 0) {
            g_9530 = 6;
            fn_18_633c();
        }
        return 0;
    }
    cls = g_7090[i].f_04e;
    dmg = (int16_t)(dmg * 7) / 8;
    if (i == main_ship) {
        dmg = (g_9000 + 6) * dmg / 8;
        if (flow_interactive == 0) {
            g_5078 += (int32_t)dmg * min(g_5078, 35000) / -4000;
            if (g_5078 > 200000)
                g_5078 += (int32_t)dmg * g_5078 / -6000;
        } else
            g_5078 += (int32_t)dmg * min(g_5078, 35000) / -9000;
    } else if (g_92e8 != 0 && i == 1)
        g_8e30 = now_ms + 20000;
    if (g_943a == 0x1e) {
        vx = g_6098[g_943c].z[1][2];
        vy = g_6098[g_943c].z[1][3];
        px = g_6098[g_943c].f_30[0][0];
        py = g_6098[g_943c].f_48[0][0];
        sz = 2;
        if (g_6098[g_943c].f_7a == g_9324 && g_6098[g_943c].f_7c != i)
            fn_04_5e8e(i, g_6098[g_943c].f_7c, dmg, 1);
        if (g_6098[g_943c].f_7a == g_9324 && g_6098[g_943c].f_7c == main_ship && g_9134 == 0
            && i != main_ship) {
            g_943e = g_9324;
            g_9440 = i;
            g_52d8 = now_ms;
        }
    } else {
        vx = object_records[g_943a][g_943c].f_0c;
        vy = object_records[g_943a][g_943c].f_0e;
        px = object_records[g_943a][g_943c].f_04.x;
        py = object_records[g_943a][g_943c].f_04.y;
        sz = object_records[g_943a][g_943c].f_22;
        dmg = (int16_t)(dmg * 3) / 4;
        if (g_9320 == 6 && g_943a == 14)
            dmg /= 2;
    }
    g_7090[i].f_14a = object_records[g_9324][i].f_04;
    g_7090[i].f_14e = now_ms;
    dv.x = vx - object_records[g_9324][i].f_0c * 10;
    dv.y = object_records[g_9324][i].f_0e * 10 - vy;
    r.x = sz / 2 - object_records[g_9324][i].f_22 / 2 - object_records[g_9324][i].f_04.x + px;
    r.y = sz / 2 + (object_records[g_9324][i].f_04.y - object_records[g_9324][i].f_22 / 2) - py;
    if ((int32_t)r.y * dv.x - (int32_t)r.x * dv.y > 0)
        object_records[g_9324][i].f_26 = 1;
    else
        object_records[g_9324][i].f_26 = -1;
    if (g_0b0a != 0)
        fn_10_754a(7, g_9324, i, 1);
    if (g_7090[i].f_0ea != 0)
        object_records[g_9324][i].f_1e = max((int16_t)(dmg * 4) / 3, 1);
    else if (g_7090[i].f_0e8 != 0)
        object_records[g_9324][i].f_1e = max((int16_t)(dmg * 3), 2);
    else
        object_records[g_9324][i].f_1e = max((int16_t)(dmg * 2), 1);
    if (g_0b0a == 0)
        fn_10_7944(g_96d2[cls].f_2e, g_9324, i, 1, g_96d2[cls].f_93);
    if (sz == 2) {
        for (k = 0; k < 4; k++) {
            dmg = object_records[g_9324][i].f_1e / VIEWP(int16_t *, g_96d2[cls].f_08, 0)[k];
            if (g_7090[i].f_0d6 != -1)
                dmg = (int16_t)(dmg * (10 - (g_6e24[g_7090[i].f_0d6].f_28 + 8)[k + 4])) / 10;
            dmg = max(dmg, 1);
            g_7090[i].f_026[k] -= dmg;
        }
    } else {
        for (k = 0; k < 4; k++) {
            dmg = object_records[g_9324][i].f_1e / VIEWP(int16_t *, g_96d2[cls].f_10, 0)[k];
            if (g_7090[i].f_0d6 != -1)
                dmg = (int16_t)(dmg * (20 - (g_6e24[g_7090[i].f_0d6].f_28 + 8)[k + 4] * 3)) / 20;
            dmg = max(dmg, 1);
            g_7090[i].f_026[k] -= dmg;
        }
    }
    for (k = 0; k < 4; k++)
        g_7090[i].f_026[k] = max(g_7090[i].f_026[k], 0);
    if (g_7090[i].f_026[3] == 0 && g_96d2[cls].f_28 == 3) {
        if (g_7090[i].f_0ad != 0 || g_7090[i].f_0ac != 0) {
            g_7090[i].f_010 = 0;
            g_7090[i].f_0ea = 0;
            if (g_7090[i].f_0ad != 0)
                fn_08_2cd8(i, 1);
            if (g_7090[i].f_0ac != 0)
                fn_08_2cd8(i, 0);
            g_7090[i].f_020 = g_96d2[cls].f_2a - 14;
            g_7090[i].f_022 = 7;
            g_7090[i].f_024 = min(g_7090[i].f_024, 1);
            g_7090[i].f_0e0 = 1;
        }
    } else if (g_7090[i].f_026[3] < 50 && g_96d2[cls].f_28 == 3 && g_7090[i].f_0ac != 0
               && g_7090[i].f_0ad != 0) {
        g_7090[i].f_010 = 0;
        g_7090[i].f_0ea = 0;
        if (object_records[g_9324][i].f_26 == 1) {
            fn_08_2cd8(i, 1);
            if (g_7090[i].f_024 == 2) {
                g_7090[i].f_0e0 = 1;
                g_7090[i].f_0e1 = 0;
            }
        } else {
            fn_08_2cd8(i, 0);
            if (g_7090[i].f_024 == 2) {
                g_7090[i].f_0e1 = 1;
                g_7090[i].f_0e0 = 0;
            }
        }
        object_records[g_9324][i].f_26 = 0;
    }
    if (g_7090[i].f_026[2] == 0 && g_96d2[cls].f_26 == 2 && g_7090[i].f_002 != 0) {
        g_7090[i].f_002 = 0;
        fn_13_6716(i);
    }
    if (g_7090[i].f_026[0] < 1 && !(g_943a == g_9324 && i == g_943c) && g_943a != 11) {
        self_destruct_ship(g_9324, i);
        for (k = 0; k < g_9406[2]; k++) {
            if (g_52ec[k].f_18.a == g_9324 && g_52ec[k].f_18.b == i) {
                g_52ec[k].f_12 = 15;
                if (g_943a == 0x1e) {
                    g_52ec[k].f_1c.a = g_6098[g_943c].f_7a;
                    g_52ec[k].f_1c.b = g_6098[g_943c].f_7c;
                } else if (g_943a == 6) {
                    g_52ec[k].f_1c.a = g_6670[g_943c + 4].r.left;
                    g_52ec[k].f_1c.b = g_6670[g_943c + 4].r.top;
                }
            }
        }
        return 1;
    }
    g_0b0a = 0;
    fn_13_33d6(i);
    return 0;
}

/* Collision response between objects (g_944a, g_944e) and (g_944c, g_9450)
 * [inferred]; ref is the object the caller asks about, pvx/pvy get its new
 * speed; returns -1 when nothing happens. */
/* 8:546c */
int16_t fn_08_546c(WORD ref, int16_t *pvx, int16_t *pvy, int16_t m1, int16_t m0)
{
    POINT p;
    int16_t res;
    int16_t t;
    int16_t n;

    res = 1;
    t = HIBYTE(ref);
    n = LOBYTE(ref);
    if (g_944a == g_9328) {
        if (g_5a4c[g_944e].f_08 == g_944c && g_5a4c[g_944e].f_0a == g_9450)
            return -1;
        if (g_944c == g_9324)
            fn_10_7944(g_96d2[g_7090[g_9450].f_04e].f_2e, g_944c, g_9450, 1,
                       g_96d2[g_7090[g_9450].f_04e].f_93);
        else
            fn_10_754a(object_records[g_944c][g_9450].f_42, g_944c, g_9450, 1);
        g_5a4c[g_944e].f_08 = g_944c;
        g_5a4c[g_944e].f_0a = g_9450;
    }
    if (g_944c == g_9328) {
        if (g_5a4c[g_9450].f_08 == g_944a && g_5a4c[g_9450].f_0a == g_944e)
            return -1;
        if (g_944a == g_9324)
            fn_10_7944(g_96d2[g_7090[g_944e].f_04e].f_2e, g_944a, g_944e, 1,
                       g_96d2[g_7090[g_944e].f_04e].f_93);
        else
            fn_10_754a(object_records[g_944a][g_944e].f_42, g_944a, g_944e, 1);
        g_5a4c[g_9450].f_08 = g_944a;
        g_5a4c[g_9450].f_0a = g_944e;
    }
    if (g_9e49 >= 3 && g_9e49 <= 6) {
        if (g_944c == 7 && g_944a == g_9324 && g_944e == g_952e)
            return -1;
        if (g_944a == 7 && g_944c == g_9324 && g_9450 == g_952e)
            return -1;
    }
    if (t == g_944a && n == g_944e) {
        g_52dc = VIEW(POINT, object_records[g_944c][g_9450].f_0c, 0);
        g_52e0 = VIEW(POINT, object_records[g_944a][g_944e].f_0c, 0);
        if (object_records[g_944c][g_9450].f_1a != 0)
            g_52e8 = object_records[g_944c][g_9450].f_00;
        else
            g_52e8 = fn_08_29ea(object_records[g_944c][g_9450].f_04);
        object_masses[1] = m0;
        if (g_944a == 0 && g_944c == 2)
            object_masses[0] *= 10;
        if (object_records[g_944a][g_944e].f_54 != 0)
            object_masses[0] = 20000;
        if (g_944c == g_9324 && g_7090[g_9450].f_0ea == 0 && g_7090[g_9450].f_0e8 == 0
            && g_96d2[g_7090[g_9450].f_04e].f_42 != 0 && object_records[g_944a][g_944e].f_53 != 0
            && object_records[g_944a][g_944e].f_2f >= 0)
            return -1;
        if (g_944a == g_9324 && g_7090[g_944e].f_0ea == 0 && g_7090[g_944e].f_0e8 == 0
            && g_96d2[g_7090[g_944e].f_04e].f_42 != 0 && object_records[g_944c][g_9450].f_53 != 0
            && object_records[g_944c][g_9450].f_2f >= 0)
            return -1;
        if (subgame_active == 0) {
            object_sizes[0] = (object_sizes[0] >> g_9150) + 1;
            object_sizes[1] = (object_sizes[1] >> g_9150) + 1;
        }
        if (g_9328 != g_944c && g_9328 != g_944a)
            res = fn_10_7dd4(&g_52dc.x, &g_52dc.y, &g_52e0.x, &g_52e0.y, &g_52e8.x, &g_52e8.y,
                             &g_52e4.x, &g_52e4.y, object_sizes[1], object_sizes[0],
                             object_masses[1], object_masses[0], &g_9436, &g_9438);
        if (res == 0) {
            fn_08_698a(0);
            return -1;
        }
        *pvx = g_52dc.x;
        *pvy = g_52dc.y;
        p = object_records[g_944c][g_9450].f_04;
        if (object_records[g_944c][g_9450].f_54 == 0)
            object_records[g_944c][g_9450].f_04 = fn_08_2bbe(g_52e8);
        g_9438 += g_9454 * 5;
        fn_08_698a(1);
        return g_9436;
    } else {
        g_52dc = VIEW(POINT, object_records[g_944c][g_9450].f_0c, 0);
        g_52e0 = VIEW(POINT, object_records[g_944a][g_944e].f_0c, 0);
        if (object_records[g_944a][g_944e].f_1a != 0)
            g_52e4 = object_records[g_944a][g_944e].f_00;
        else
            g_52e4 = fn_08_29ea(object_records[g_944a][g_944e].f_04);
        object_masses[0] = m0;
        if (object_records[g_944a][g_944e].f_54 != 0)
            object_masses[0] = 20000;
        if (g_944c == g_9324 && g_7090[g_9450].f_0ea == 0 && g_7090[g_9450].f_0e8 == 0
            && g_96d2[g_7090[g_9450].f_04e].f_42 != 0 && object_records[g_944a][g_944e].f_53 != 0
            && object_records[g_944a][g_944e].f_2f >= 0)
            return -1;
        if (g_944a == g_9324 && g_7090[g_944e].f_0ea == 0 && g_7090[g_944e].f_0e8 == 0
            && g_96d2[g_7090[g_944e].f_04e].f_42 != 0 && object_records[g_944c][g_9450].f_53 != 0
            && object_records[g_944c][g_9450].f_2f >= 0)
            return -1;
        if (subgame_active == 0) {
            object_sizes[0] = (object_sizes[0] >> g_9150) + 1;
            object_sizes[1] = (object_sizes[1] >> g_9150) + 1;
        }
        if (g_9328 != g_944c && g_9328 != g_944a)
            res = fn_10_7dd4(&g_52dc.x, &g_52dc.y, &g_52e0.x, &g_52e0.y, &g_52e8.x, &g_52e8.y,
                             &g_52e4.x, &g_52e4.y, object_sizes[1], object_sizes[0],
                             object_masses[1], object_masses[0], &g_9436, &g_9438);
        if (res == 0) {
            fn_08_6a44(0);
            return -1;
        }
        *pvx = g_52e0.x;
        *pvy = g_52e0.y;
        p = object_records[g_944c][g_9450].f_04;
        if (object_records[g_944c][g_9450].f_54 == 0)
            object_records[g_944c][g_9450].f_04 = fn_08_2bbe(g_52e8);
        g_9436 += g_9454 << 2;
        fn_08_6a44(1);
        return g_9438;
    }
}

/* Object (type, idx) takes dmg points of damage from object (stype, sidx):
 * finds the responsible owner, scores, applies it through the record's
 * damage callback (f5e) and returns that callback's result [inferred]. */
/* The subgame scaling goes back into v before one shared f66 store: with a
 * store in each inner arm CL keeps the last copy of the cross-jumped f66
 * store, the game keeps the flag8 arm's. */
/* 8:5df2 */
int16_t fn_08_5df2(int16_t type, int16_t idx, int16_t stype, int16_t sidx, int16_t dmg)
{
    int16_t ret;
    int16_t ok;
    int16_t flag8;
    int16_t neg;
    int16_t mass;
    int16_t smass;
    int16_t otype;
    int16_t oidx;
    int16_t u1;
    int16_t u2;
    int16_t j;
    int16_t k;
    int16_t v;

    ok = 1;
    flag8 = 0;
    mass = object_records[type][idx].f_44;
    if (stype == 0x1f)
        smass = 20000;
    else
        smass = object_records[stype][sidx].f_44;
    neg = 0;
    if (dmg < -1) {
        neg = 1;
        dmg = -dmg;
    }
    if (stype <= g_9324) {
        if (dmg > 2000 && dmg < 3000) {
            dmg -= 2000;
            flag8 = 1;
            if (stype == g_9324 && g_96d2[g_7090[sidx].f_04e].f_38 == 7)
                dmg = 1;
        }
        if (dmg == -1)
            return 0;
        if (g_7090[main_ship].f_01c > 2 && stype == g_9324 && sidx == main_ship
            && (type == g_934a || type == 8 || type == 9) && g_9134 < 2) {
            fn_03_06ec(main_ship, 7, 0, 13);
            report_crime(main_ship, 9);
        }
        otype = -1;
        if (object_records[stype][sidx].f_32 == g_9324) {
            otype = g_9324;
            oidx = object_records[stype][sidx].f_34;
        }
        if (object_records[type][idx].f_32 == g_9324) {
            otype = g_9324;
            oidx = object_records[type][idx].f_34;
        }
        if (object_records[type][idx].f_32 != -1) {
            if ((int16_t)(smass + 100) > mass) {
                if (g_65cc[object_records[type][idx].f_30].f_0e)
                    g_65cc[object_records[type][idx].f_30].f_0e = 0;
                else
                    g_65cc[object_records[type][idx].f_30].f_0e = 1;
            }
            if (rand() % 12 + 30 < dmg && dmg != 100 && type == g_9324)
                fn_11_947a(g_65cc[object_records[type][idx].f_30].f_04, g_65cc[object_records[type][idx].f_30].f_06, 2);
        }
        if (stype == g_9328) {
            if (object_records[g_9328][sidx].f_44 == 120)
                dmg = max((int16_t)(dmg * 2), 20);
            otype = g_5a4c[sidx].f_04;
            oidx = g_5a4c[sidx].f_06;
        }
        if (stype == 6) {
            otype = g_6670[sidx + 4].r.left;
            oidx = g_6670[sidx + 4].r.top;
            if (g_2f4c[g_6670[sidx + 4].f_04.x].f_2c == 6 && type == g_9324
                && g_2f4c[g_7090[idx].f_0b8[g_7090[idx].f_018]].f_2c == 6)
                ok = 0;
        }
        if (stype == 10 || object_records[stype][sidx].f_32 != -1) {
            otype = object_records[stype][sidx].f_32;
            oidx = object_records[stype][sidx].f_34;
        }
        if (otype == -1) {
            otype = stype;
            oidx = sidx;
        }
        if (otype == 9 || otype == 2 || otype == g_9324) {
            if (otype == g_9324) {
                if (g_7090[oidx].f_038 == 1 && g_7090[oidx].f_032.a == type && g_7090[oidx].f_032.b == idx)
                    g_7090[oidx].f_0a4 = now_ms;
                for (k = 0; k <= g_9316; k++)
                    if (k != oidx && g_7090[k].flag && g_7090[k].f_032.a == type
                        && g_7090[k].f_032.b == idx && g_7090[k].f_038 == 1)
                        fn_13_2714(k, oidx, 5, 10, 0, -1);
            }
            if ((type == g_9324 || type == 0) && g_0b0c
                && (otype == g_9324
                    || otype == 2 && !(g_52ec[oidx].f_18.a == type && g_52ec[oidx].f_18.b == idx))) {
                for (k = 0; k < g_9406[2]; k++)
                    if (g_52ec[k].f_18.a == type && g_52ec[k].f_18.b == idx)
                        fn_08_9028(k, 10, otype, oidx);
                if (otype == g_9324 && type == g_9324) {
                    if (stype != g_9324 || flag8)
                        fn_04_5e8e(idx, oidx, dmg, 1);
                    if (oidx == main_ship && g_7090[idx].f_038 == 4 && g_7090[idx].f_032.b == oidx)
                        g_9432 += dmg;
                    fn_04_7d36(oidx, idx, dmg);
                }
                if (otype == g_9324 && oidx == main_ship && stype != 10 && type != g_9324)
                    /* 8:81f8 is defined with char parameters, but this
                     * call passes whole ints [inferred: the original called
                     * it before its definition, without a prototype] */
                    ((void (*)(int16_t, int16_t))fn_08_81f8)(type, idx);
            }
            if (otype == g_9324 && oidx == main_ship && !(type == g_9324 && idx == main_ship)) {
                g_943e = type;
                g_9440 = idx;
                g_52d8 = now_ms;
                if (stype != g_9324 && type == g_9324)
                    g_9432 += dmg / 2;
                if (stype != g_9324 && (type == g_934a || type == 8))
                    g_9432 += dmg / 4;
                if (stype != g_9324 && type == 0 && object_records[0][idx].f_53 == 1)
                    g_9432 += dmg / 3;
            }
        }
        if (object_records[type][idx].f_53) {
            if (stype == 2)
                ok = 0;
            if (stype == g_9324 && g_7090[sidx].f_010 < 6 && g_96d2[g_7090[sidx].f_04e].f_42
                && g_7090[sidx].f_0e8 == 0 && object_records[type][idx].f_2f >= 0 && !neg && !flag8)
                ok = 0;
            if (flag8 && otype == 9)
                ok = 1;
        }
        if (type == 11 && stype == g_9324 && g_8560[idx].f_0a == sidx && g_7090[sidx].flag == 0)
            ok = 0;
        if (type == g_9324 && g_7090[idx].flag == 0 && stype == 11 && g_8560[sidx].f_0a == idx)
            ok = 0;
        if (type == 2 && (g_52ec[idx].f_18.a == stype && g_52ec[idx].f_18.b == sidx || stype == 2))
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
            fn_10_754a(object_records[type][idx].f_42, type, idx, 1);
        ret = object_records[type][idx].f_5e(type, idx, dmg);
        if (otype == g_9324 && oidx == main_ship && !(type == g_9324 && idx == main_ship))
            fn_08_7be8(type, idx, dmg, ret);
        if (ret) {
            if (!(otype == g_9324 && oidx == main_ship) && !(type == g_9324 && idx == main_ship))
                fn_08_7ce0(type, idx, dmg, ret);
            v = 0;
            if (otype == g_9324) {
                if (stype != 10 && g_7090[oidx].f_032.a == type && g_7090[oidx].f_032.b == idx
                    && g_7090[oidx].f_038 == 1) {
                    if (type == 0 && object_records[0][idx].f_53 == 1)
                        report_crime(oidx, 1);
                    if (type == 8 && g_3d50[idx].f_0a == 16)
                        report_crime(oidx, 6);
                }
                if (g_7090[oidx].f_052 >= 2 && g_7090[oidx].f_052 <= 4
                    && g_7090[oidx].f_058 != oidx && g_7090[oidx].f_054 == type && g_0b0c) {
                    if (type == 9) {
                        fn_03_06ec(oidx, g_9324, g_7090[oidx].f_058, 0x75);
                        fn_13_2714(g_7090[oidx].f_058, oidx, 15, 40, 0, 6);
                        if (g_9134 == 0 || oidx != main_ship && flow_interactive == 0)
                            g_7090[oidx].f_052 = 0;
                        v = 1;
                    } else if (g_7090[oidx].f_056 == idx) {
                        fn_03_06ec(oidx, g_9324, g_7090[oidx].f_058, 0x76);
                        fn_13_2714(g_7090[oidx].f_058, oidx, 50, 90, 0, 6);
                        if (g_9134 == 0 || oidx != main_ship && flow_interactive == 0)
                            g_7090[oidx].f_052 = 0;
                        v = 1;
                    }
                } else if (g_7090[oidx].f_052 == 1 && type == g_9324) {
                    if (g_7090[idx].f_032.a == g_9324 && g_7090[oidx].f_058 == g_7090[idx].f_032.b
                        && g_7090[idx].f_038 == 1) {
                        fn_03_06ec(oidx, g_9324, g_7090[oidx].f_058, 0x77);
                        fn_13_2714(g_7090[oidx].f_058, oidx, 60, 120, 0, 8);
                        v = 1;
                    }
                } else {
                    for (j = 0; j <= g_9316; j++)
                        if (j != oidx && g_7090[j].flag && g_7090[j].f_032.a == type
                            && g_7090[j].f_032.b == idx && g_7090[j].f_038 == 1) {
                            fn_13_2714(j, oidx, 30, 50, 0, 6);
                            fn_03_06ec(oidx, g_9324, j, 0x77);
                        }
                }
            }
            if (type == 8 && g_9320 == 6 && g_9eb9[g_9322] + g_9318 * 2 <= idx) {
                world_map(g_0a72, g_0a74, 1 - g_9eb5, g_9322, 8, idx, 0);
                BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
            }
            if (type == 0 && object_records[0][idx].f_53 == 2 && otype == g_9324 && oidx == main_ship) {
                fn_03_06ec(oidx, 7, 0, 0x5e);
                g_1e58 += 3000;
            }
            if (type == 9 && otype == g_9324 && oidx == main_ship) {
                g_1e58 += 1000;
                if (v == 0)
                    fn_03_06ec(main_ship, 7, 0, 0x5b);
            }
            fn_07_2080(type);
            if (otype == g_9324 && type == g_9324) {
                if (oidx == main_ship)
                    g_9432 += 200;
                fn_13_2714(idx, oidx, -50, -150, 1, -1);
                for (j = 0; j < g_9316; j++)
                    if (fn_13_2688(j, idx) > 0)
                        fn_13_2e60(j, oidx, 4);
            }
            if (type == g_9324)
                fn_04_7636(idx, otype, oidx, v);
            g_7090[main_ship].f_156 = now_ms - 1;
        }
    }
    fn_08_99ce(type, idx, otype, oidx);
    if (type == g_9324) {
        if (ok && g_7090[idx].flag) {
            g_7090[idx].f_0e2 = 1;
            if (object_records[type][idx].f_26 == 0)
                object_records[type][idx].f_26 = 1;
            if (flag8)
                g_7090[idx].f_084 = max((int16_t)(dmg * 25), 900) + now_ms;
            else if (stype == 8 && g_3d50[sidx].f_0a == -3)
                g_7090[idx].f_084 = max((int16_t)(dmg * 6), 300) + now_ms;
            else {
                v = max((int16_t)(dmg * 12), 600);
                if (subgame_active) {
                    if (g_90f4 == 1)
                        v = (g_a198 + 3) * v / 6;
                    else
                        v = v * (g_a198 + 3) / 12;
                }
                g_7090[idx].f_084 = v + now_ms;
            }
        }
    } else if (type == 8) {
        if (flag8)
            g_3d50[idx].f_04 = dmg * 200 + now_ms;
        else
            g_3d50[idx].f_04 = dmg * 140 + now_ms;
    }
    return ret;
}

/* Shot group n against object (t, i), k the group's damage [inferred]:
 * 0 no hit, 1 hit and absorbed, 2 hit and the target reacted. wrap is
 * read uninitialised (as in the original). */
/* 8:6f3c */
int16_t fn_08_6f3c(int16_t t, int16_t i, int16_t n, int16_t k)
{
    POINT c;
    POINT vel;
    POINT pos;
    POINT d;
    int32_t u1;                    /* unused: frame filler */
    int32_t u2;
    int16_t ret;
    int16_t wrap;
    int16_t v;
    int16_t ok;
    int16_t hit;
    int16_t j;
    int16_t otype;
    int16_t oidx;
    int16_t m;
    int16_t dist;
    int32_t l;

    if (object_records[t][i].f_18)
        return 0;
    if (object_records[t][i].f_55[n] > 1 && g_6098[n].f_82 == 0 && subgame_active == 0) {
        object_records[t][i].f_55[n]--;
        return 0;
    }
    if (object_records[t][i].f_2e && (t != g_9324 || g_7090[i].f_026[4] != 2))
        return 0;
    otype = g_6098[n].f_7a;
    oidx = g_6098[n].f_7c;
    if (otype == t && oidx == i && g_6098[n].z[1][5] < 24)
        return 0;
    pos = fn_08_29ea(object_records[t][i].f_04);
    for (j = 0; j < g_6098[n].count; j++) {
        if (VIEWP(int16_t *, g_6098[n].f_84, 0)[j]) {
            d.x = g_5168[j].x - pos.x;
            d.y = g_5168[j].y - pos.y;
            if (object_records[t][i].f_22 > d.x && d.x > -1 && object_records[t][i].f_22 > d.y && d.y > -1)
                hit = 1;
            else {
                /* hit = 0 in each leaf: makes CL keep the else arm's copy
                 * of the merged f55 store (layout only) */
                if ((-25 << g_9156) > d.x || (40 << g_9156) < d.x
                    || (-25 << g_9156) > d.y || (40 << g_9156) < d.y) {
                    dist = fn_08_35d0((int16_t)(object_records[t][i].f_22 / 2 + d.x), (int16_t)(object_records[t][i].f_22 / 2 + d.y)) - 5;
                    if (dist == 0)
                        dist = 1;
                    l = ((object_records[t][i].f_0e / 5 - g_6098[n].z[1][3]) * d.y
                         + (object_records[t][i].f_0c / 5 - g_6098[n].z[1][2]) * d.x) / (dist * 8);
                    if (l > 0) {
                        object_records[t][i].f_55[n] = (char)(dist / l / (g_9208 + 2));
                        hit = 0;
                    } else {
                        object_records[t][i].f_55[n] = dist / ((g_9208 + 4) * 10) - g_9208 + 10;
                        hit = 0;
                    }
                } else {
                    object_records[t][i].f_55[n] = 0;
                    hit = 0;
                }
            }
            if (hit) {
                k = 14 - g_6098[n].z[1][5] * 14 / g_6098[n].z[1][4];
                if (g_6098[n].z[1][5] < 20)
                    k = 23;
                if (g_6098[n].f_7a == g_9324 && g_6098[n].f_7c == main_ship)
                    k = (int16_t)(k * 3) / 2;
                else if (g_6098[n].f_7a == g_9324 && g_96d2[g_7090[g_6098[n].f_7c].f_04e].f_38 == 7
                         && g_7090[g_6098[n].f_7c].f_05e == 0)
                    k = (int16_t)(k * 5) / 2;
                if (g_6098[n].f_7a == g_9324)
                    k = g_96d2[g_7090[g_6098[n].f_7c].f_04e].f_32 * k / 250;
                if (g_92e8 && oidx != main_ship)
                    k *= 3;
                if (g_6098[n].f_7a == g_9324 && g_7090[g_6098[n].f_7c].f_0d6 != -1)
                    k = (int16_t)(((g_6e24[g_7090[g_6098[n].f_7c].f_0d6].f_28 + 8)[2] + 5) * k * 20) / 100;
                g_944a = t;
                g_944e = i;
                g_943a = 30;
                g_944c = 30;
                g_943c = n;
                g_9450 = n;
                if (g_6098[n].f_7a == g_9324 && g_6098[n].f_7c == main_ship && t != g_9324)
                    /* as in 8:5df2: whole ints to a char-parameter function */
                    ((void (*)(int16_t, int16_t))fn_08_81f8)(t, i);
                c.x = g_6098[n].z[1][2] * 5;
                c.y = g_6098[n].z[1][3] * 5;
                if (wrap) {
                    if (g_6098[n].f_30[j][0] < 1000 && object_records[t][i].f_04.x > 5000)
                        g_6098[n].f_30[j][0] += LO16(g_05a0) * 8;
                    else if (g_6098[n].f_30[j][0] > 5000 && object_records[t][i].f_04.x < 1000)
                        g_6098[n].f_30[j][0] -= LO16(g_05a0) * 8;
                    if (g_6098[n].f_48[j][0] < 1000 && object_records[t][i].f_04.y > 5000)
                        g_6098[n].f_48[j][0] += HI16(g_05a0) * 8;
                    else if (g_6098[n].f_48[j][0] > 5000 && object_records[t][i].f_04.y < 1000)
                        g_6098[n].f_48[j][0] -= HI16(g_05a0) * 8;
                }
                vel = VIEW(POINT, object_records[t][i].f_0c, 0);
                ok = fn_10_7dd4(&c.x, &c.y, &object_records[t][i].f_0c, &object_records[t][i].f_0e,
                    &g_6098[n].f_30[j][0], &g_6098[n].f_48[j][0], &object_records[t][i].f_04.x, &object_records[t][i].f_04.y,
                    30, object_records[t][i].f_20 + 8, k, object_records[t][i].f_44, &g_9436, &g_9438);
                if (wrap) {
                    g_6098[n].f_30[j][0] = (int16_t)((g_6098[n].f_30[j][0] + ((int32_t)LO16(g_05a0) << 3))
                                               % (LO16(g_05a0) << 3));
                    g_6098[n].f_48[j][0] = (int16_t)((g_6098[n].f_48[j][0] + ((int32_t)HI16(g_05a0) << 3))
                                               % (HI16(g_05a0) << 3));
                }
                if (ok) {
                    if (object_records[t][i].f_54) {
                        object_records[t][i].f_0e = 0;
                        object_records[t][i].f_0c = object_records[t][i].f_0e;
                    } else {
                        object_records[t][i].f_0c = (int16_t)(object_records[t][i].f_0c + vel.x) / 2;
                        object_records[t][i].f_0e = (int16_t)(object_records[t][i].f_0e + vel.y) / 2;
                    }
                    g_6098[n].z[1][2] = c.x / 5;
                    g_6098[n].z[1][3] = c.y / 5;
                    if (t == 4 || t == 8 && g_3d50[i].f_1c == 2
                        && (g_4d90[g_3d50[i].f_30].f_03 == 5 || g_4d90[g_3d50[i].f_30].f_03 == 4))
                        fn_10_754a(30, t, i, 1);
                    else
                        fn_10_754a(0x11, 30, n, 2);
                    if (otype == g_9324) {
                        if (g_7090[oidx].f_038 == 1 && g_7090[oidx].f_032.a == t && g_7090[oidx].f_032.b == i)
                            g_7090[oidx].f_0a4 = now_ms;
                        for (m = 0; m <= g_9316; m++)
                            if (m != oidx && g_7090[m].flag && g_7090[m].f_032.a == t
                                && g_7090[m].f_032.b == i && g_7090[m].f_038 == 1)
                                fn_13_2714(m, oidx, 5, 10, 0, -1);
                    }
                    if (otype == g_9324 && t == g_9324)
                        fn_04_7d36(oidx, i, g_9438);
                    if (otype == g_9324 && oidx == main_ship && !(t == g_9324 && i == main_ship)) {
                        g_9440 = i;
                        g_52d8 = now_ms;
                        g_943e = t;
                        if (t == g_9324 || t == g_934a || t == 8 || t == 0 && object_records[0][i].f_53 == 1)
                            g_9432 += g_9438 / 3;
                        if (t == g_9324 && g_7090[i].f_038 == 4 && g_7090[i].f_032.b == main_ship)
                            g_9432 += g_9438 / 2;
                    }
                    ret = object_records[t][i].f_5e(t, i, g_9438);
                    if (ret == 0 && g_9208 >= 2 && k * g_9436 > 600)
                        fn_08_804a(n, k * g_9436, j);
                    fn_08_99ce(t, i, otype, oidx);
                    if (t == 15)
                        fn_18_3f02(g_6098[n].f_30[j][0], g_6098[n].f_48[j][0], g_9438);
                    v = 0;
                    if (ret && otype == g_9324) {
                        if (t == 0 && object_records[0][i].f_53 == 1 && g_7090[oidx].f_032.a == 0
                            && g_7090[oidx].f_032.b == i && g_7090[oidx].f_038 == 1)
                            report_crime(oidx, 1);
                        if (t == 8 && g_3d50[i].f_0a == 16 && g_7090[oidx].f_032.a == 8
                            && g_7090[oidx].f_032.b == i && g_7090[oidx].f_038 == 1)
                            report_crime(oidx, 6);
                        if (g_7090[oidx].f_052 >= 2 && g_7090[oidx].f_052 <= 4 && g_7090[oidx].f_058 != oidx
                            && g_7090[oidx].f_054 == t) {
                            if (t == 9) {
                                fn_03_06ec(oidx, g_9324, g_7090[oidx].f_058, 0x75);
                                fn_13_2714(g_7090[oidx].f_058, oidx, 15, 45, 0, 6);
                                if (g_9134 == 0 || oidx != main_ship && flow_interactive == 0)
                                    g_7090[oidx].f_052 = 0;
                                v = 1;
                            } else if (g_7090[oidx].f_056 == i) {
                                fn_03_06ec(oidx, g_9324, g_7090[oidx].f_058, 0x76);
                                fn_13_2714(g_7090[oidx].f_058, oidx, 40, 90, 0, 6);
                                if (g_9134 == 0 || oidx != main_ship && flow_interactive == 0)
                                    g_7090[oidx].f_052 = 0;
                                v = 1;
                            }
                        } else if ((g_7090[oidx].f_052 == 1 || g_7090[oidx].f_052 == 5) && t == g_9324) {
                            if (g_7090[i].f_032.a == g_9324 && g_7090[oidx].f_058 == g_7090[i].f_032.b
                                && g_7090[i].f_038 == 1) {
                                fn_03_06ec(oidx, g_9324, g_7090[oidx].f_058, 0x77);
                                fn_13_2714(g_7090[oidx].f_058, oidx, 60, 120, 0, 8);
                                v = 1;
                            }
                        } else {
                            for (m = 0; m <= g_9316; m++)
                                if (m != oidx && g_7090[m].flag && g_7090[m].f_032.a == t
                                    && g_7090[m].f_032.b == i && g_7090[m].f_038 == 1) {
                                    fn_13_2714(m, oidx, 25, 40, 0, 6);
                                    fn_03_06ec(oidx, g_9324, m, 0x77);
                                }
                        }
                    }
                    if (ret && t == 0 && otype == g_9324 && oidx == main_ship && object_records[t][i].f_53 == 2) {
                        fn_03_06ec(oidx, 7, 0, 0x5e);
                        g_1e58 += 3000;
                    }
                    if (ret && t == 8 && g_9320 == 6 && g_9eb9[g_9322] + g_9318 * 2 <= i) {
                        world_map(g_0a72, g_0a74, 1 - g_9eb5, g_9322, 8, i, 0);
                        BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
                    }
                    if (ret && t == g_9324) {
                        fn_04_7636(i, otype, oidx, v);
                        if (otype == g_9324 && oidx == main_ship)
                            g_9432 += 200;
                    }
                    if (ret)
                        g_7090[main_ship].f_156 = now_ms - 1;
                    if (otype == g_9324 && oidx == main_ship)
                        fn_08_7be8(t, i, g_9438, ret);
                    if (ret && t == 9 && otype == g_9324 && v == 0)
                        fn_03_06ec(oidx, 7, 0, 0x5b);
                    if (t == g_9324 && g_7090[i].flag) {
                        if (g_92e8 && i != main_ship)
                            g_9438 /= 2;
                        g_7090[i].f_0e2 = 1;
                        if (object_records[t][i].f_26 == 0)
                            object_records[t][i].f_26 = 1;
                        g_7090[i].f_084 = g_9438 * 12 + now_ms;
                    } else if (t == 8)
                        g_3d50[i].f_04 = g_9438 * 120 + now_ms;
                    if (ret)
                        return 2;
                    return 1;
                }
            }
        }
    }
    return 0;
}
