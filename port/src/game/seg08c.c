/* INSPACE.EXE segment 8 (selector 1038), 8:8256 to the end: a separate
 * source file (inventory/files.tsv file 17; 8:9ab8 far-calls 8:285a).
 * Declarations copied from seg08.c. */
#include "game.h"

                                                                             

/* Old-style definition: 8:9b4e passes a PAIR by value, 8:99ce two ints. */
/* 8:9028 */
void fn_08_9028(int16_t i, int16_t a, int16_t kind, int16_t idx)
{
    if (g_52ec[i].f_18.a == 0xe && (g_52ec[i].f_12 == 0xf
        || kind == 0xe && g_52ec[i].f_18.b == idx))
        return;
    if (g_52ec[i].f_18.a == kind && g_52ec[i].f_18.b == idx)
        return;
    if (kind == 2 && g_52ec[idx].f_18.a == g_52ec[i].f_18.a
        && g_52ec[idx].f_18.b == g_52ec[i].f_18.b)
        return;
    if (a == 5) {
        g_52ec[i].f_14 = 0;
        if (g_52ec[i].f_12 <= 5)
            g_52ec[i].f_12 = 5;
        g_52ec[i].f_1c.a = kind;
        g_52ec[i].f_1c.b = idx;
    } else {
        g_52ec[i].f_12 = g_52ec[i].f_12 < a ? a : g_52ec[i].f_12;
        g_52ec[i].f_1c.a = kind;
        g_52ec[i].f_1c.b = idx;
        if (a == 0xf)
            g_52ec[i].f_0a = 0;
    }
}

/* 8:90fa */
void fn_08_90fa(int16_t i)
{
    int16_t k;
    int16_t j;
    int16_t d;
    int16_t dx;
    int16_t dy;
    POINT pt;

    if (g_91f8 < 4 || g_9334 < 5 || g_52ec[i].f_1c.a == 12)
        return;
    for (k = g_0594; k < g_0598 + g_0594; k++) {
        if (g_6098[k].z[1][5] == -1) {
            for (j = 0; j < 2; j++) {
                g_6098[k].f_48[0][j] = g_6098[k].f_30[0][j] = -800;
                fn_08_0764(k, j);
            }
            if (g_7090[g_52ec[i].f_1c.b].f_0e8) {
                pt.x = g_7090[g_52ec[i].f_1c.b].f_14a.x;
                pt.y = g_7090[g_52ec[i].f_1c.b].f_14a.y;
            } else {
                pt = g_1df8[g_52ec[i].f_1c.a][g_52ec[i].f_1c.b].f_04;
            }
            d = fn_08_285a(&dx, &dy, g_1df8[2][i].f_04,
                           g_1df8[g_52ec[i].f_1c.a][g_52ec[i].f_1c.b].f_04);
            if (d < 0x118 && fn_08_19b0(dx, dy) == g_1df8[2][i].f_28) {
                g_6098[k].f_30[0][0] = g_1df8[2][i].f_04.x + 0x30;
                g_6098[k].f_48[0][0] = g_1df8[2][i].f_04.y + 0x30;
                g_6098[k].count = 1;
                g_6098[k].f_84 = 1;
                g_6098[k].f_86 = 0;
                g_6098[k].f_82 = 0;
                g_6098[k].f_7a = 2;
                g_6098[k].f_7c = i;
                g_6098[k].z[1][2] = g_1050[g_1df8[2][i].f_28].x * 3;
                g_6098[k].z[1][3] = g_1050[g_1df8[2][i].f_28].y * 3;
                g_6098[k].z[1][5] = 0;
                g_6098[k].z[1][4] = 0x28;
                g_6098[k].f_80 = 0;
                fn_10_754a(3, 2, i, 1);
                return;
            }
        }
    }
}

/* 8:92a0 */
void fn_08_92a0(int16_t type, int16_t idx)
{
    int16_t k;
    int16_t j;

    g_1df8[2][idx].f_18 = 1;
    fn_10_754a(0x16, 2, idx, 1);
    g_1e58 += 400;
    PatBlt(g_13dc, g_1df8[2][idx].f_00.x - 1, g_1df8[2][idx].f_00.y - 1,
           g_1df8[2][idx].f_22 + 2, g_1df8[2][idx].f_22 + 2, BLACKNESS);
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
            g_1e90[k].f_02 = 0xe;
            g_1e90[k].f_0a = 7;
            g_1e90[k].f_0c = 2;
            if (k > g_9434)
                g_9434 = k;
            g_1e90[k].f_0e = g_52ec[idx].f_12;
            g_9430++;
            if (k > g_9208)
                g_1e90[k].f_04 = 2;
            else
                g_1e90[k].f_04 = 1;
            g_1e90[k].f_06 = 2;
            g_1e90[k].f_08 = idx;
            g_5224[k] = g_1df8[2][idx].f_04;
            g_5170[k] = g_1df8[2][idx].f_00;
            return;
        }
    }
}

/* 8:95f2 */
int16_t fn_08_95f2(int16_t unused, int16_t i, int16_t v)
{
    if (v > 0)
        v = v < 0x3c ? 0x3c : v;
    else
        v = -v;
    g_1df8[2][i].f_1e += v;
    g_57a0 = g_1e50 + 500;
    if (g_1df8[2][i].f_1e > 0x50)
        g_52ec[i].f_14 = 1;
    g_52ec[i].f_20 = g_1e50 + 0x15e;
    if (g_1df8[2][i].f_1e > (g_9334 + 0x1a) * 5) {
        fn_08_92a0(2, i);
        return 1;
    }
    return 0;
}

/* 8:9464 */
void fn_08_9464(void)
{
    int16_t i;
    int16_t j;
    int16_t unused;

    if (g_92e8 != 0 || g_1048 == 0)
        return;
    for (i = 0; i < g_9406[0]; i++) {
        if (g_1df8[0][i].f_18 == 0) {
            for (j = i; j < g_92ec[2]; j += g_9406[0]) {
                if (g_1df8[2][j].f_18 != 0) {
                    fn_10_754a(0x18, 0, i, 1);
                    VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).l = 0xff10ffd0L;
                    g_1df8[2][j].f_0c = 0x46;
                    g_1df8[2][j].f_0e = -0x82;
                    g_1df8[2][j].f_18 = 0;
                    g_1df8[2][j].f_2e = 0;
                    g_52ec[j].f_10 = -1;
                    g_1df8[2][j].f_1e = 0;
                    g_52ec[j].f_08 = 0;
                    g_52ec[j].f_18.a = 0;
                    g_52ec[j].f_18.b = i;
                    g_52ec[j].f_14 = 0;
                    g_52ec[j].f_1c.a = 0;
                    g_52ec[j].f_1c.b = i;
                    g_52ec[j].f_12 = 0;
                    j = g_92ec[2];
                    break;
                }
            }
        }
    }
    fn_07_2080(2);
}

/* 8:9564 */
void fn_08_9564(void)
{
    int16_t i;
    int16_t j;

    if (g_92e8 == 0 && g_1048 != 0) {
        for (i = 0; i < g_9406[0]; i++) {
            if (g_1df8[0][i].f_18 == 0 && g_1df8[0][i].f_1a != 0) {
                for (j = i; j < g_9406[2]; j += g_9406[0]) {
                    if (g_1df8[2][j].f_18 != 0) {
                        fn_10_754a(0x17, 0, i, 1);
                        g_914e = 1;
                        return;
                    }
                }
            }
        }
    }
}

/* 8:9ab8 */
void fn_08_9ab8(void)
{
    int16_t i;
    int16_t d;
    int16_t y;
    int16_t x;

    for (i = 0; i < g_9406[2]; i++) {
        if (g_1df8[2][i].f_18 == 0 && g_52ec[i].f_1c.a == 0xc
            && g_1df8[2][i].f_1a == 0) {
            d = fn_08_285a(&y, &x, g_1df8[2][i].f_04,
                           g_1df8[12][g_52ec[i].f_1c.b / 2].f_04);
            if (d < 0xaa)
                fn_12_2288(2, i);
        }
    }
}

/* 8:99ce */
void fn_08_99ce(int16_t a, int16_t b, int16_t kind, int16_t idx)
{
    int16_t i;
    int16_t k;
    int16_t x;

    if (a == 0 && (kind == 9 || kind == 0xe)) {
        g_57a8[b].f_0a = kind;
        g_57a8[b].f_0b = idx;
    }
    for (i = 0; i < g_9406[2]; i++) {
        if (g_1df8[2][i].f_18 == 0 && (kind == 0xe || kind == 2)) {
            x = idx;
            k = kind;
            if ((k == 0xe || k == 2 && g_52ec[x].f_12 == 0xf
                 && !(g_52ec[x].f_18.a == g_52ec[i].f_18.a
                      && g_52ec[x].f_18.b == g_52ec[i].f_18.b))
                && g_52ec[i].f_18.a == a && g_52ec[i].f_18.b == b
                && !(g_52ec[i].f_18.a == k && g_52ec[i].f_18.b == x)
                && g_52ec[i].f_12 != 0xf) {
                fn_08_9028(i, 0xf, k, x);
                break;
            }
        }
    }
}

/* 8:9b4e */
void fn_08_9b4e(void)
{
    int16_t i;

    for (i = 0; i < g_9406[2]; i++) {
        if (g_1df8[2][i].f_18 == 0 && g_52ec[i].f_18.a == 0xe
            && g_52ec[i].f_12 != 0xf) {
            if (g_7090[g_52ec[i].f_18.b].f_038 == 1)
                fn_08_9028(i, 10, g_7090[g_52ec[i].f_18.b].f_032.a, g_7090[g_52ec[i].f_18.b].f_032.b);
            else
                g_52ec[i].f_12 = 5;
        }
    }
}

/* Set up the 5x5 grid of group a around object (type, idx), with a random
 * motion formula per cell [inferred]. */
/* 8:9694 */
void fn_08_9694(int16_t a, int16_t type, int16_t idx)
{
    int16_t i;
    int16_t j;
    POINT p;

    if (type == 0x1e) {
        p.x = g_6098[idx].z[1][2];
        p.y = g_6098[idx].z[1][3];
    } else {
        p.x = g_1df8[type][idx].f_0c;
        p.y = g_1df8[type][idx].f_0e;
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            g_2414[a][i][j].s.x = (j << 4) + g_5224[a].x + 8;
            g_2414[a][i][j].s.y = (i << 4) + g_5224[a].y + 8;
            g_2414[a][i][j].f_0c = (j - 2) * 8 + p.x;
            g_2414[a][i][j].f_0e = (2 - i) * 7 + p.y;
            g_2414[a][i][j].f_10 = (i + 5) * 2 - j * 7;
            g_2414[a][i][j].f_12 = (-1 - j) * 4 + i * 6;
            type = rand() % 32;
            switch (type % 8) {
            case 0:
                g_2414[a][i][j].f_10 = (i + 5) * 2 - j * 7;
                g_2414[a][i][j].f_12 = (-1 - j) * 4 + i * 6;
                break;
            case 1:
                g_2414[a][i][j].f_10 = (2 - j) * 7 + (2 - i) * (i - 2) * 2;
                g_2414[a][i][j].f_12 = (2 - j) * (j - 2) * 4 + (i - 2) * 6;
                break;
            case 2:
                g_2414[a][i][j].f_10 = (2 - j) * 7 + (2 - i) * (i - 2) * 2;
                g_2414[a][i][j].f_12 = (j - 2) * (j - 2) * 4 + (2 - i) * 6;
                break;
            case 3:
                g_2414[a][i][j].f_10 = -(2 - i) * 2 + (2 - j) * (5 - i) * 7;
                g_2414[a][i][j].f_12 = -(2 - i) * (j - 5) * 6 + (j - 2) * 4;
                break;
            case 4:
                g_2414[a][i][j].f_10 = (2 - j) * (i - 2);
                g_2414[a][i][j].f_12 = (j - 2) * (i - 2) * 7 + (2 - j) * (2 - i) * 2;
                break;
            case 5:
                g_2414[a][i][j].f_10 = ((2 - i) * (2 - i) * (i - 2) + j - 2) * 6;
                g_2414[a][i][j].f_12 = (2 - j) * (j - 2) * 2 + (i - 2) * 5;
                break;
            case 6:
                g_2414[a][i][j].f_10 = ((i - 2) * (i - 2) * (2 - i) + (j - 2) * (j - 2) * (j - 2)) * 6;
                g_2414[a][i][j].f_12 = (2 - j) * (j - 2) * 2 + (i - 2) * (i - 2) * i * 7;
                break;
            case 7:
                g_2414[a][i][j].f_10 = j * 7 - i * 3 - 8;
                g_2414[a][i][j].f_12 = (i - 2) * (i - 2) * (i - 2) * 6;
                break;
            }
        }
    }
}

/* Move, steer and draw the type-2 objects (j indexes g_52ec) [inferred]. */
/* 8:8256 */
void fn_08_8256(void)
{
    POINT v;
    POINT pp;
    POINT pt;
    int32_t l1;
    int32_t l2;
    int32_t l3;
    int32_t l4;
    int32_t l5;
    int16_t flag;
    int16_t j;
    int16_t d;
    int16_t t;
    int16_t q;
    int16_t sy;
    int16_t sx;
    int16_t h;
    int16_t w;
    int16_t dx;
    int16_t dy;
    int16_t d2;
    HBRUSH old;
    WORD r;

    w = g_1df8[2][0].f_24;
    h = g_1df8[2][0].f_22;
    g_9452 = 0;
    if (g_186c < g_1e50) {
        t = (55 - g_91f8) * 4;
        g_186c = (t < 110 ? 110 : t) + g_1e50;
        g_9452 = 1;
    }
    if (g_1874 >= 4)
        g_1874 = 0;
    else
        g_1874++;
    if (g_1e50 - 60 > g_579c) {
        g_579c = g_1e50;
        g_0b6a += g_0b6c;
        if (g_0b6a > 3 || g_0b6a < 1)
            g_0b6c = -g_0b6c;
    }
    for (j = 0; j < g_9406[2]; j++) {
        if (g_52ec[j].f_18.a == 14 && g_52ec[j].f_18.b == main_ship || g_6e38[0].f_1a.b == 2 && j == g_6e38[0].f_1a.a)
            if (g_1e50 - 2000 > g_1870)
                g_1870 = g_1e50;
        if (g_1df8[2][j].f_1a && g_52ec[j].f_12 != 15 && g_52ec[j].f_20 < g_1e50)
            g_1df8[2][j].f_28 = fn_08_19b0(g_1df8[2][j].f_0c, g_1df8[2][j].f_0e);
        flag = 1;
        if (g_1df8[2][j].f_18)
            continue;
        if (g_52ec[j].f_12 == 15) {
            if (g_92ec[g_52ec[j].f_1c.a] < g_52ec[j].f_1c.b) {
                g_9498++;
                VIEW(int32_t, g_52ec[j].f_1c.a, 0) = 0x1000c;
            }
            if (g_1df8[g_52ec[j].f_1c.a][g_52ec[j].f_1c.b].f_18) {
                g_52ec[j].f_1c.a = 12;
                g_52ec[j].f_1c.b = 1;
            }
            if (g_9452 && g_52ec[j].f_20 < g_1e50) {
                if (g_52ec[j].f_1c.a == 14 && g_7090[g_52ec[j].f_1c.b].f_0e8) {
                    pt.x = g_7090[g_52ec[j].f_1c.b].f_14a.x;
                    pt.y = g_7090[g_52ec[j].f_1c.b].f_14a.y;
                } else
                    pt = g_1df8[g_52ec[j].f_1c.a][g_52ec[j].f_1c.b].f_04;
                d = max(4, fn_08_285a(&dx, &dy, g_1df8[2][j].f_04, pt));
                if (d == 0)
                    d = 1;
                if (g_52ec[j].f_0a == 0) {
                    v.x = dx * -100 / d;
                    v.y = dy * -100 / d;
                    if (d > 220)
                        g_52ec[j].f_0a = 1;
                } else {
                    v.x = (dx << 3) / (d >> 2);
                    v.y = (dy << 3) / (d >> 2);
                    g_1df8[2][j].f_0c += v.x;
                    g_1df8[2][j].f_0e += v.y;
                    g_1df8[2][j].f_28 = fn_08_19b0(v.x, v.y);
                    if (g_1df8[2][j].f_0c > 70)
                        g_1df8[2][j].f_0c = 70;
                    if (g_1df8[2][j].f_0e > 70)
                        g_1df8[2][j].f_0e = 70;
                    if (g_1df8[2][j].f_0c < -70)
                        g_1df8[2][j].f_0c = -70;
                    if (g_1df8[2][j].f_0e < -70)
                        g_1df8[2][j].f_0e = -70;
                }
            } else if (g_52ec[j].f_20 > g_1e50) {
                g_1df8[2][j].f_28++;
                if (g_1df8[2][j].f_28 > 15)
                    g_1df8[2][j].f_28 = 0;
            }
            if (g_1df8[2][j].f_1a) {
                sy = 0;
                old = SelectObject(g_13dc, g_576c[g_52ec[j].f_12 + g_0b6a]);
                g_1df8[2][j].f_10 = g_1df8[2][j].f_28 * (w + h) + w;
                g_1df8[2][j].f_12 = g_52ec[j].f_14 * (w + h) + w;
                fn_08_0b76((char)j | 0x200, 3, g_39e8[0], 1);
                SelectObject(g_13dc, old);
                if (g_0b6a == 4 && g_9452)
                    fn_08_90fa(j);
            }
            if (g_0b6a == 4 && g_9452 && g_52ec[j].f_1c.a == 14 && rand() % 6 == 1
                && g_52ec[j].f_18.a == 0
                && g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_18 == 0
                && (g_7090[g_52ec[j].f_1c.b].f_032.a != g_52ec[j].f_18.a
                    || g_7090[g_52ec[j].f_1c.b].f_032.b != g_52ec[j].f_18.b)) {
                g_52ec[j].f_12 = 10;
                VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x = g_1df8[2][j].f_04.x - g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_04.x;
                VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.y = g_1df8[2][j].f_04.y - g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_04.y;
            }
            if (g_52ec[j].f_18.a == 14 && g_1df8[14][g_52ec[j].f_18.b].f_18
                && g_7090[g_52ec[j].f_18.b].flag)
                fn_08_9028(j, 15, 12, 1);
            fn_08_1b54((char)j | 0x200, 1);
            if (g_1df8[2][j].f_1a) {
                g_943a = 2;
                g_943c = j;
                r = fn_08_50aa((char)j | 0x200);
                if (r != -1) {
                    fn_08_5df2(2, j, HIBYTE(r), LOBYTE(r),
                               fn_08_546c(r, &g_1df8[2][j].f_0c, &g_1df8[2][j].f_0e,
                                          g_1df8[2][j].f_22 + 2, g_1df8[2][j].f_44));
                    if (HIBYTE(r) == 0 && g_57a8[LOBYTE(r)].f_02)
                        fn_08_5df2(2, j, HIBYTE(r), LOBYTE(r), 180);
                }
            }
        } else if (flag) {
            if (g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_18) {
                g_52ec[j].f_12 = 15;
                VIEW(int32_t, g_52ec[j].f_1c.a, 0) = 0x1000c;
            }
            if (g_57a0 && g_57a0 < g_1e50) {
                l1 = VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x;
                l2 = VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.y;
                l3 = g_1df8[2][j].f_0c - g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_0c;
                l4 = g_1df8[2][j].f_0e - g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_0e;
                l5 = l1 * l4 - l2 * l3;
                if (l5 > 0) {
                    g_1df8[2][j].f_0c = -g_1df8[2][j].f_0c;
                    g_1df8[2][j].f_0e = -g_1df8[2][j].f_0e;
                }
            }
            g_1df8[2][j].f_04.x = g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_04.x + VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x;
            g_1df8[2][j].f_04.y = g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_04.y + VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.y;
            if (g_1df8[2][j].f_04.x < 0)
                g_1df8[2][j].f_04.x += (LO16(g_05a0)) * 8;
            if (g_1df8[2][j].f_04.x > (LO16(g_05a0)) * 8)
                g_1df8[2][j].f_04.x -= (LO16(g_05a0)) * 8;
            if (g_1df8[2][j].f_04.y < 0)
                g_1df8[2][j].f_04.y += HI16(g_05a0) * 8;
            if (g_1df8[2][j].f_04.y > HI16(g_05a0) * 8)
                g_1df8[2][j].f_04.y -= HI16(g_05a0) * 8;
            if (g_1df8[2][j].f_1a) {
                old = SelectObject(g_13dc, g_576c[g_52ec[j].f_12 + g_0b6a]);
                sx = g_1df8[2][j].f_28 * (w + h);
                g_1df8[2][j].f_10 = sx + w;
                sy = 0;
                g_1df8[2][j].f_12 = g_52ec[j].f_14 * (w + h) + w;
                fn_08_0b76((char)j | 0x200, 3, g_39e8[0], 1);
                SelectObject(g_13dc, old);
            }
            g_5794 = g_1df8[2][j].f_0c + VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x;
            g_5796 = g_1df8[2][j].f_0e + VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.y;
            if ((g_1874 == 0 || g_1df8[2][j].f_1a) && g_52ec[j].f_20 < g_1e50) {
                pp.x = VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x;
                pp.y = VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.y;
                l1 = -pp.x;
                l2 = -pp.y;
                d = (int16_t)fn_08_1290(l1 * l1 + l2 * l2, abs32(l1) + abs32(l2));
                if (g_1df8[2][j].f_1a == 0) {
                    g_1df8[2][j].f_0c += (int16_t)(l1 * g_52ec[j].f_16 * 4 / d);
                    g_1df8[2][j].f_0e += (int16_t)(l2 * g_52ec[j].f_16 * 4 / d);
                } else {
                    g_1df8[2][j].f_0c += (int16_t)(l1 * g_52ec[j].f_16 / d);
                    g_1df8[2][j].f_0e += (int16_t)(l2 * g_52ec[j].f_16 / d);
                }
                pp.x += g_1df8[2][j].f_0c;
                pp.y += g_1df8[2][j].f_0e;
                if (d < 600 && g_1df8[2][j].f_1a) {
                    l1 = VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x;
                    l2 = VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.y;
                    l3 = g_1df8[2][j].f_0c - g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_0c;
                    l4 = g_1df8[2][j].f_0e - g_1df8[g_52ec[j].f_18.a][g_52ec[j].f_18.b].f_0e;
                    l5 = l1 * l3 + l2 * l4;
                    if (l5 < 0) {
                        d = (int16_t)fn_08_1290(l1 * l1 + l2 * l2, abs32(l1) + abs32(l2));
                        d2 = (int16_t)fn_08_1290(l3 * l3 + l4 * l4, abs32(l3) + abs32(l4));
                        if (d2 == 0)
                            d2 = 1;
                        if (d == 0)
                            d = 1;
                        if (l5 * 100 / ((int32_t)d * d2) < -70) {
                            g_1df8[2][j].f_0c = (int16_t)(l2 * 100 / d);
                            g_1df8[2][j].f_0e = (int16_t)(l1 * -100 / d);
                        }
                    }
                }
                if (g_1df8[2][j].f_0c > 120)
                    g_1df8[2][j].f_0c = 120;
                if (g_1df8[2][j].f_0e > 120)
                    g_1df8[2][j].f_0e = 120;
                if (g_1df8[2][j].f_0c < -120)
                    g_1df8[2][j].f_0c = -120;
                if (g_1df8[2][j].f_0e < -120)
                    g_1df8[2][j].f_0e = -120;
            } else if (g_52ec[j].f_20 > g_1e50) {
                g_1df8[2][j].f_28++;
                if (g_1df8[2][j].f_28 > 15)
                    g_1df8[2][j].f_28 = 0;
            }
            fn_08_1b54((char)j | 0x200, 1);
            if (VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x < 0 && g_1df8[2][j].f_0c < 0
                || VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x > 0 && g_1df8[2][j].f_0c > 0)
                g_52ec[j].f_0e = 100;
            else
                g_52ec[j].f_0e = 50;
            if (g_52ec[j].f_12 >= 10) {
                if (g_0b6a == 4 && g_9452)
                    fn_08_90fa(j);
                if (g_0b6a == 4 && g_9452 && g_91f8 > 4 && g_52ec[j].f_1c.a == 14
                    && g_7090[g_52ec[j].f_1c.b].f_032.a == g_52ec[j].f_18.a
                    && g_7090[g_52ec[j].f_1c.b].f_032.b == g_52ec[j].f_18.b
                    && g_7090[g_52ec[j].f_1c.b].f_038 == 1) {
                    g_52ec[j].f_12 = 15;
                    g_52ec[j].f_0e = 50;
                }
            }
            if (g_1df8[2][j].f_1a) {
                g_943a = 2;
                g_943c = j;
                r = fn_08_50aa((char)j | 0x200);
                if (r != -1) {
                    q = fn_08_546c(r, &g_1df8[2][j].f_0c, &g_1df8[2][j].f_0e,
                                   g_1df8[2][j].f_22 + 2, 55);
                    if (HIBYTE(r) == 0 && g_57a8[LOBYTE(r)].f_02)
                        fn_08_5df2(2, j, HIBYTE(r), LOBYTE(r), 180);
                    else if (HIBYTE(r))
                        fn_08_5df2(2, j, HIBYTE(r), LOBYTE(r), q);
                }
            }
            VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.x = g_5794;
            VIEW(union {
        int32_t l;
        POINT p;
    }, g_52ec[j].f_00.l, 0).p.y = g_5796;
        }
    }
    if (g_57a0 && g_57a0 < g_1e50)
        g_57a0 = 0;
}
