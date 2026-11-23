/* INSPACE.EXE segment 12 (selector 1058). No 32-bit code anywhere in this
 * segment: compiled with /G2 [inferred, confirmed by matches]. */
#include "game.h"

/* DS:05a0 is read as an int here (map width [inferred]); inspace.h
 * declares it long. */
                                    

/* 12:0a26 */
void fn_12_0a26(int16_t a)
{
    int16_t i;

    for (i = 0; i < 45; i++) {
        if (g_1e90[i].f_00 == -1) {
            g_1e90[i].f_0a = 3;
            g_1e90[i].f_00 = 1;
            g_1e90[i].f_02 = 0xb;
            g_1e90[i].f_06 = 6;
            g_1e90[i].f_08 = a;
            if (i > g_9434)
                g_9434 = i;
            g_5170[i] = g_1df8[6][a].f_00;
            g_5224[i] = g_1df8[6][a].f_04;
            if (i > g_9434)
                g_9434 = i;
            g_9430++;
            break;
        }
    }
    fn_10_754a(0x45, 6, a, 1);
    g_6670[a + 4].f_1a = 0;
}

/* 12:0dc4 */
int16_t fn_12_0dc4(int16_t type, int16_t idx, int16_t v)
{
    g_1df8[type][idx].f_1e += v;
    if (g_1df8[type][idx].f_2f == 0)
        g_1df8[type][idx].f_2f = 1;
    g_1df8[type][idx].f_50 = g_1df8[type][idx].f_1e / 10 < 1 ? 1 : g_1df8[type][idx].f_1e / 10;
    if (g_1df8[type][idx].f_50 > 5) {
        g_1df8[type][idx].f_66(type, idx);
        fn_07_2080(type);
        return 1;
    }
    return 0;
}

/* Release an object's memory DC and bitmap [inferred]. */
/* 12:26a4 */
void fn_12_26a4(int16_t type, int16_t idx)
{
    if (g_1df8[type][idx].f_3c) {
        SelectObject(g_1df8[type][idx].f_3c, g_1df8[type][idx].f_40);
        if (g_920e)
            SelectPalette(g_1df8[type][idx].f_3c, g_1df8[type][idx].rest, 0);
        DeleteDC(g_1df8[type][idx].f_3c);
        g_1df8[type][idx].f_3c = 0;
    }
    if (g_1df8[type][idx].f_3e) {
        DeleteObject(g_1df8[type][idx].f_3e);
        g_1df8[type][idx].f_3e = 0;
    }
}

/* 12:6cf6 */
void fn_12_6cf6(void)
{
    int16_t t;
    int16_t i;

    for (t = g_9326; t <= g_9324; t++) {
        for (i = 0; i < g_9406[t]; i++) {
            if (g_1df8[t][i].f_54) {
                g_1df8[t][i].f_0e = 0;
                g_1df8[t][i].f_0c = g_1df8[t][i].f_0e;
            }
        }
    }
}

/* 12:6d64 */
void fn_12_6d64(int16_t a, int16_t b)
{
    int16_t i;

    for (i = 1; i < g_7090[a].cnt; i++)
        if (g_7090[a].f_0b8[i] == b)
            return;
    if (g_7090[a].cnt > 9)
        return;
    g_7090[a].cnt++;
    i = g_7090[a].cnt - 1;
    g_7090[a].f_0b8[i] = b;
    g_7090[a].f_0ae[i] = 20;
    if (g_2f4c[b].f_12)
        fn_10_533a(g_7090[a].f_0b8[i]);
}

/* 12:6a60 */
void fn_12_6a60(int16_t type, int16_t idx)
{
    int16_t i;

    if (fn_08_7ba8(fn_08_29ea(g_1df8[type][idx].f_04)))
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
               g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, BLACKNESS);
    if (type == 6) {
        g_6670[idx + 4].r.right = g_2f4c[g_6670[idx + 4].f_04.x].f_26;
        g_6670[idx + 4].f_04.x = -1;
    }
    for (i = 0; i < 5; i++)
        fn_07_5b68(type, idx, 1);
    g_1df8[type][idx].f_18 = 1;
}

/* Nearest live object of type g_9324 within 700 of (type, idx), as
 * (g_9324 << 8) | index, or -1 [inferred]. */
/* 12:6706 */
int16_t fn_12_6706(int16_t type, int16_t idx)
{
    int16_t i;
    int16_t d;
    int16_t best;
    int16_t bi;
    int16_t k;
    int16_t j;

    if (g_9320 == 6) {
        k = fn_04_8c80();
        if (k >= 0 && g_1df8[14][k].f_51 == 0)
            return (char)k | g_9324 << 8;
        else
            return -1;
    }
    best = 20000;
    bi = -1;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[g_9324][i].f_18 == 0) {
            d = fn_08_285a(&k, &j, g_1df8[type][idx].f_04, g_1df8[g_9324][i].f_04);
            if (d < best) {
                best = d;
                bi = i;
            }
        }
    }
    if (best >= 700)
        return -1;
    return (char)bi | g_9324 << 8;
}

/* Not yet decompiled: stubs so calls to them compile as near calls. */

/* Object (type, idx) explodes into debris particles [inferred]. */
/* 12:274a */
void fn_12_274a(int16_t type, int16_t idx)
{
    int16_t k;
    int16_t j;
    int16_t n;

    if (g_9406[type] <= idx) {
        g_9498++;
        if (g_92ec[type] <= idx)
            return;
        if (type == g_9324 && idx > g_9316)
            return;
    }
    if (type == 4)
        g_698c = g_1e50 + 10000;
    if (!(type == 8 && g_3d50[idx].f_1c == 1)
        && fn_08_7ba8(fn_08_29ea(g_1df8[type][idx].f_04)))
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
               g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, BLACKNESS);
    if (g_1df8[type][idx].f_48 == 1) {
        n = 1;
    } else {
        switch (g_9208) {
        case 0:
            n = (int16_t)(g_1df8[type][idx].f_48 * 30) / 100;
            break;
        case 1:
            n = (int16_t)(g_1df8[type][idx].f_48 * 60) / 100;
            break;
        case 2:
            n = g_1df8[type][idx].f_48;
            break;
        case 3:
            n = (int16_t)(g_1df8[type][idx].f_48 * 130) / 100;
            break;
        }
        n = n < 2 ? 2 : n;
    }
    if (g_9430 > 10)
        n = (int16_t)((35 - g_9430) * n) / 25 < 1 ? 1 : (int16_t)((35 - g_9430) * n) / 25;
    for (k = 0; k < n; k++) {
        for (j = 0; j < 45; j++) {
            if (g_1e90[j].f_00 == -1) {
                if (k == 0)
                    g_1e90[j].f_0a = 4;
                else
                    g_1e90[j].f_0a = 1;
                g_1e90[j].f_00 = 1;
                if (j > g_9434)
                    g_9434 = j;
                g_1e90[j].f_10 = (int32_t)(rand() % 110) + (int16_t)(k * 30) + g_1e50;
                g_1e90[j].f_02 = 10;
                if (k > (g_9208 >> 1) + 2 && rand() % 10 <= 6) {
                    g_1e90[j].f_02 -= rand() % 4 + 4;
                    g_1e90[j].f_10 += 60;
                }
                g_1e90[j].f_06 = type;
                g_1e90[j].f_08 = idx;
                { int16_t pad[2];
                if (k == 0) {
                    g_5224[j] = g_1df8[type][idx].f_04;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                } else {
                    g_5224[j].x = (rand() % (int16_t)((n + 40) * 2) - n - 40) * 8
                        + g_1df8[type][idx].f_20 / 2 + g_1df8[type][idx].f_04.x;
                    g_5224[j].y = (rand() % (int16_t)((n + 40) * 2) - n - 40) * 8
                        + g_1df8[type][idx].f_20 / 2 + g_1df8[type][idx].f_04.y;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                }
                }
                g_9430++;
                break;
            }
        }
    }
    if (!(type == 8 && g_3d50[idx].f_1c == 1)) {
        g_1df8[type][idx].f_18 = 1;
        if (type == g_9324 && idx == main_ship) {
            if (flow_interactive) {
                g_1e84 = g_1e50 + 1500;
            } else {
                g_1e84 = 0;
                g_1e80 = g_1e50 + 1500;
            }
        }
    }
    if (type == 6) {
        g_6670[idx + 4].r.right = g_2f4c[g_6670[idx + 4].f_04.x].f_26;
        g_6670[idx + 4].f_04.x = -1;
    }
    fn_10_754a(0x45, type, idx, 1);
}

/* Scale a size to the current zoom (g_9156) [inferred]. */
#define SC(n) ((int16_t)((n) << g_9156) >> 1)

/* Draw the type-4 object idx shrinking as its f51 counter runs down
 * [inferred]. */
/* 12:0e5c */
void fn_12_0e5c(int16_t idx)
{
    int16_t v;
    int16_t w;
    int16_t h;
    int16_t sx;
    int16_t flag;

    w = g_1df8[4][idx].f_22;
    h = g_1df8[4][idx].f_24;
    if (g_8ffe != 0 && g_1df8[4][idx].f_51 > 8)
        flag = 1;
    else
        flag = 0;
    g_1df8[4][idx].f_51 -= (char)g_8ffe;
    if (g_1df8[4][idx].f_51 < 0)
        g_1df8[4][idx].f_51 = 0;
    v = 9 - g_1df8[4][idx].f_51;
    SetStretchBltMode(g_13dc, 3);
    if (g_1df8[4][idx].f_48 == main_ship && g_9208 > 1 && (v & 1))
        fn_07_1208();
    if ((g_9214 == 3 || g_9214 == 4) && g_1df8[4][idx].f_26 != 0)
        sx = h + w;
    else
        sx = 0;
    if (g_1df8[4][idx].f_1a == 0)
        return;
    switch (v) {
    case 0:
        StretchBlt(g_13dc, g_1df8[4][idx].f_00.x, g_1df8[4][idx].f_00.y, w, w,
                   g_39e8[4], sx - SC(3) + h, h - SC(3), SC(6) + w, SC(6) + w, SRCCOPY);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        StretchBlt(g_13dc, SC(v) * 2 + g_1df8[4][idx].f_00.x, g_1df8[4][idx].f_00.y - SC(2),
                   w - SC(v) * 4, SC(3) + w,
                   g_39e8[4], sx, 0, h * 2 + w, h * 2 + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, g_1df8[4][idx].f_00.x - SC(2) + SC(v) * 2, g_1df8[4][idx].f_00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[4][idx].f_00.x - SC(v) * 2 + w, g_1df8[4][idx].f_00.y,
                   SC(2), w, BLACKNESS);
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        v -= 4;
        StretchBlt(g_13dc, SC(8) + g_1df8[4][idx].f_00.x,
                   SC(2) * v + g_1df8[4][idx].f_00.y - 1,
                   w - SC(16), w - SC(4) * v + 1,
                   g_39e8[4], sx, 0, h * 2 + w, h * 2 + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, SC(6) + g_1df8[4][idx].f_00.x, g_1df8[4][idx].f_00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[4][idx].f_00.x - SC(16) + SC(8) + w, g_1df8[4][idx].f_00.y,
                   SC(2), w, BLACKNESS);
        }
        break;
    case 9:
        PatBlt(g_13dc, g_1df8[4][idx].f_00.x, g_1df8[4][idx].f_00.y, w, w, BLACKNESS);
        fn_07_2080(4);
        fn_07_1208();
        break;
    }
    if (flag) {
        PatBlt(g_13dc, g_1df8[4][idx].f_00.x, g_1df8[4][idx].f_00.y, w, SC(3), BLACKNESS);
        PatBlt(g_13dc, g_1df8[4][idx].f_00.x, g_1df8[4][idx].f_00.y - SC(3) + w, w, SC(3),
               BLACKNESS);
        PatBlt(g_13dc, g_1df8[4][idx].f_00.x, SC(3) + g_1df8[4][idx].f_00.y, SC(3),
               w - SC(6), BLACKNESS);
        PatBlt(g_13dc, g_1df8[4][idx].f_00.x - SC(3) + w, SC(3) + g_1df8[4][idx].f_00.y,
               SC(3), w - SC(6), BLACKNESS);
    }
}

/* Draw object (type, idx) shrinking as its f51 counter runs down
 * [inferred]; the general form of fn_12_0e5c. */
/* 12:129e */
void fn_12_129e(int16_t type, int16_t idx)
{
    int16_t v;
    int16_t w;
    int16_t h;
    int16_t k;
    int16_t sx;
    int16_t flag;

    w = g_1df8[type][idx].f_22;
    h = g_1df8[type][idx].f_24;
    if (g_8ffe != 0 && g_1df8[type][idx].f_51 > 8)
        flag = 1;
    else
        flag = 0;
    g_1df8[type][idx].f_51 -= (char)g_8ffe;
    if (g_1df8[type][idx].f_51 < 0)
        g_1df8[type][idx].f_51 = 0;
    v = 9 - g_1df8[type][idx].f_51;
    SetStretchBltMode(g_13dc, 3);
    if (type == 11) {
        k = g_1df8[type][idx].f_4a;
        sx = 0;
    } else if (type == 6) {
        k = g_2f4c[g_6670[idx + 4].f_04.x].f_04;
        sx = ((int16_t)(g_2f4c[g_6670[idx + 4].f_04.x].f_2e - 1) < 0 ? 0 : g_2f4c[g_6670[idx + 4].f_04.x].f_2e - 1)
            * (h + w);
    }
    if (k > 100 || k < 0) {
        g_9498++;
        g_6670[idx + 4].f_04.x = 16;
        k = g_2f4c[16].f_04;
    }
    if (g_1df8[type][idx].f_48 == main_ship && g_9208 > 1 && (v & 1))
        fn_07_1208();
    if (g_1df8[type][idx].f_1a == 0)
        return;
    switch (v) {
    case 0:
        StretchBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y, w, w,
                   g_39e8[k], sx - SC(2) + h, h - SC(2), SC(4) + w, SC(4) + w, SRCCOPY);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        StretchBlt(g_13dc, SC(v) * 2 + g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y - SC(2),
                   w - SC(4) * v, SC(4) + w,
                   g_39e8[k], sx - SC(4) + h, h - 2, SC(8) + w, SC(4) + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, SC(2) * (v - 1) + g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[type][idx].f_00.x - SC(v) * 2 + w, g_1df8[type][idx].f_00.y,
                   SC(2), w, BLACKNESS);
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        v -= 4;
        StretchBlt(g_13dc, SC(8) + g_1df8[type][idx].f_00.x,
                   SC(2) * v + g_1df8[type][idx].f_00.y - 1,
                   w - SC(16), SC(2) - SC(4) * v + w,
                   g_39e8[k], sx - SC(4) + h, h - SC(4), SC(8) + w, SC(8) + w, SRCCOPY);
        if (g_8ffe != 0) {
            PatBlt(g_13dc, SC(6) + g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
                   SC(2), w, BLACKNESS);
            PatBlt(g_13dc, g_1df8[type][idx].f_00.x - SC(16) + SC(8) + w,
                   g_1df8[type][idx].f_00.y, SC(2), w, BLACKNESS);
        }
        break;
    case 9:
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y, w, w, BLACKNESS);
        fn_07_2080(type);
        fn_07_1208();
        break;
    }
    if (flag) {
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y, w, SC(3), BLACKNESS);
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y + w - 3, w, SC(3),
               BLACKNESS);
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x, SC(3) + g_1df8[type][idx].f_00.y, SC(3),
               w - SC(6), BLACKNESS);
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x - SC(3) + w, SC(3) + g_1df8[type][idx].f_00.y,
               SC(3), w - SC(6), BLACKNESS);
    }
}

/* A pair of type-8 objects 2a, 2a+1 (a sliding gate [inferred]): moves,
 * draws, and handles what touches it. */
/* 12:1776 */
void fn_12_1776(int16_t a)
{
    int16_t i;
    int16_t ref;
    int16_t k;
    int16_t ref2;
    int16_t w;
    int16_t w2;
    POINT pt;
    HGDIOBJ old;
    int16_t flag;
    int16_t n;

    for (i = a * 2; i < (int16_t)((a + 1) * 2); i++)
        g_1df8[8][i].f_1c = 0;
    if (g_9492 && a == 0) {
        g_9492 += g_9494;
        if (g_9492 > 4 || g_9492 < 2)
            g_9494 = -g_9494;
    }
    for (i = a * 2; i < (int16_t)((a + 1) * 2); i++) {
        if (g_6670[a].f_1a) {
            if ((int16_t)(a * 2 - i + 1) == 0)
                w2 = g_1df8[8][i].f_04.x - g_1df8[8][i].f_20 - g_1df8[8][i - 1].f_04.x + 16;
            if ((int16_t)(a * 2) == i) {
                g_1df8[8][i].f_04.x += g_6670[a].f_1a * 8;
                g_1df8[8][i].f_0c = g_6670[a].f_1a * 8;
                w = g_1df8[8][i + 1].f_04.x - g_1df8[8][i].f_04.x - g_1df8[8][i].f_20;
                g_6670[a].r.left += g_6670[a].f_1a * 8;
            } else {
                g_1df8[8][i].f_04.x -= g_6670[a].f_1a * 8;
                g_1df8[8][i].f_0c = -(g_6670[a].f_1a * 8);
                w = g_1df8[8][i].f_04.x - g_1df8[8][i].f_20 - g_1df8[8][i - 1].f_04.x;
                g_6670[a].r.right -= g_6670[a].f_1a * 8;
            }
            if (g_6670[a].f_12 < w || g_6670[a].f_16 > w) {
                if (g_9320 == 7)
                    g_6670[a].f_1a = 0;
                else
                    g_6670[a].f_1a = -g_6670[a].f_1a;
            }
        } else if ((int16_t)(a * 2 - i + 1) == 0) {
            w2 = w = g_1df8[8][i].f_04.x - g_1df8[8][i].f_20 - g_1df8[8][i - 1].f_04.x;
        }
        if (g_1df8[8][i].f_1a) {
            if (g_1df8[8][i].f_2f > 2) {
                k = 2;
                if (g_1df8[8][i].f_2f > 4)
                    old = SelectObject(g_13dc, g_3b74[max((int16_t)(g_1df8[8][i].f_2f - g_9492), 1)]);
                else
                    old = SelectObject(g_13dc, g_3b74[max((int16_t)(g_1df8[8][i].f_2f + g_9492 - 1), 1)]);
                if (g_1df8[8][i].f_6a < g_1e50) {
                    g_1df8[8][i].f_2f--;
                    g_1df8[8][i].f_6a = g_1e50 + 3000;
                }
                flag = 1;
            } else {
                old = 0;
                if (g_1df8[8][i].f_2f < 0) {
                    if (rand() % 7 == 2)
                        fn_07_5b68(8, i, 0);
                    g_1df8[8][i].f_2f++;
                }
                k = 1;
                flag = 0;
            }
            g_1df8[8][i].f_10 = (g_1df8[8][i].f_22 + g_1df8[8][i].f_24) * ((int16_t)(i - a * 2) % 2)
                + g_1df8[8][i].f_24;
            fn_08_0b76((char)i | 0x800, 1, g_39e8[k], flag);
            if (old)
                SelectObject(g_13dc, old);
        }
        if ((int16_t)(a * 2 - i + 1) == 0 && (g_1df8[8][i - 1].f_1a || g_1df8[8][i].f_1a)) {
            old = SelectObject(g_13dc, g_3b88[g_9492]);
            g_6670[a].f_00.x = g_6670[a].f_04.x;
            g_6670[a].f_00.y = g_6670[a].f_04.y;
            if (g_1df8[8][i - 1].f_1a)
                pt = g_1df8[8][i - 1].f_00;
            else
                pt = fn_08_29ea(g_1df8[8][i - 1].f_04);
            g_6670[a].f_04.x = g_1df8[8][i - 1].f_22 + pt.x;
            g_6670[a].f_04.y = SC(15) + pt.y;
            if (g_6670[a].f_04.x != g_6670[a].f_00.x || g_6670[a].f_04.y != g_6670[a].f_00.y)
                PatBlt(g_13dc, g_6670[a].f_00.x, g_6670[a].f_00.y, SC(1) + (w2 >> g_9150), SC(2),
                       BLACKNESS);
            PatBlt(g_13dc, g_6670[a].f_04.x, g_6670[a].f_04.y, w >> g_9150, SC(2), PATCOPY);
            if (old)
                SelectObject(g_13dc, old);
            if (g_91fc == 0 && g_1e50 > g_1928) {
                HBITMAP bmp;
                HGDIOBJ oldbmp;
                HDC dc;
                HPALETTE oldpal;

                g_1928 = g_1e50 + 400;
                g_0d0a = !g_0d0a;
                bmp = fn_10_6308(-1, -1, bmp = fn_10_6d38("OUT_SIGN"), -1);
                dc = CreateCompatibleDC(g_13dc);
                oldbmp = SelectObject(dc, bmp);
                if (g_920e)
                    oldpal = SelectPalette(dc, g_920e, 0);
                BitBlt(g_39ea, SC(2) + g_1df8[8][i].f_24, SC(10) + g_1df8[8][i].f_24, SC(26), SC(13),
                       dc, SC(26) * g_0d0a, 0, SRCCOPY);
                BitBlt(g_39ea, g_1df8[8][i].f_24 * 2 + g_1df8[8][i].f_22 + SC(7),
                       g_1df8[8][i].f_24 + SC(10), SC(26), SC(13),
                       dc, SC(26) * g_0d0a, 0, SRCCOPY);
                SelectObject(dc, oldbmp);
                if (oldpal)
                    SelectPalette(dc, oldpal, 0);
                DeleteDC(dc);
                if (bmp) {
                    DeleteObject(bmp);
                    bmp = 0;
                }
            }
        }
        if (g_1df8[8][i].f_1a && g_1df8[8][i].f_1c == 0) {
            g_943a = 8;
            g_943c = i;
            ref = fn_08_50aa((char)i | 0x800);
            if (ref != -1) {
                if (HIBYTE(ref) == g_9328) {
                    if (g_1df8[HIBYTE(ref)][LOBYTE(ref)].f_44 == 120) {
                        g_1df8[8][i].f_2f = min(g_1df8[8][i].f_2f + 1, 9);
                        g_1df8[8][i].f_6a = g_1e50 + 5000;
                    } else if (g_1df8[HIBYTE(ref)][LOBYTE(ref)].f_44 == 200
                               && g_1df8[8][i].f_2f > 0) {
                        g_1df8[8][i].f_2f = -(g_1df8[8][i].f_2f * 5);
                    }
                }
                fn_08_5df2(8, i, HIBYTE(ref), LOBYTE(ref),
                           fn_08_546c(ref, &g_1df8[8][i].f_0c, &g_1df8[8][i].f_0e,
                                      g_1df8[8][i].f_20 + 2, g_1df8[8][i].f_44));
            }
            ref2 = fn_12_1f7a(a);
            n = 0;
            if (HIBYTE(ref2) == g_9324)
                n = g_7090[LOBYTE(ref2)].f_0e8;
            if (HIBYTE(ref2) == g_9324 && LOBYTE(ref2) == main_ship
                && (g_1df8[HIBYTE(ref2)][LOBYTE(ref2)].f_2e == 0 || n)) {
                fn_12_2288(HIBYTE(ref2), LOBYTE(ref2));
                g_1e80 = g_1e50 + 1000;
            } else if (ref2 >= 0 && (g_1df8[HIBYTE(ref2)][LOBYTE(ref2)].f_2e == 0 || n)) {
                fn_12_2288(HIBYTE(ref2), LOBYTE(ref2));
                PatBlt(g_13dc, g_1df8[HIBYTE(ref2)][LOBYTE(ref2)].f_00.x,
                       g_1df8[HIBYTE(ref2)][LOBYTE(ref2)].f_00.y,
                       g_1df8[HIBYTE(ref2)][LOBYTE(ref2)].f_22,
                       g_1df8[HIBYTE(ref2)][LOBYTE(ref2)].f_22, BLACKNESS);
                fn_10_754a(0x27, HIBYTE(ref2), LOBYTE(ref2), 1);
            }
        }
    }
}

/* Draw the line a-b clipped to the play view (0..g_90ea, 0..g_90ec)
 * [inferred]. Slopes are 25.7 fixed point. */
/* 12:7256 */
void fn_12_7256(HDC dc, POINT a, POINT b)
{
    int16_t side;
    int32_t slope;
    int32_t icpt;
    int32_t v;
    POINT pt[2];

    pt[1].y = pt[1].x = pt[0].y = pt[0].x = -1;
    if (!(a.x >= 0 && a.x <= LO16(g_90ea) && b.x >= 0 && b.x <= LO16(g_90ea)
          && a.y >= 0 && a.y <= HI16(g_90ea) && b.y >= 0 && b.y <= HI16(g_90ea))) {
        if (b.x == a.x)
            b.x++;
        if (b.y == a.y)
            b.y++;
        if (a.y < 0 && b.y < 0)
            return;
        if (a.y > HI16(g_90ea) && b.y > HI16(g_90ea))
            return;
        if (a.x < 0 && b.x < 0)
            return;
        if (a.x > LO16(g_90ea) && b.x > LO16(g_90ea))
            return;
        slope = ((int32_t)(int16_t)(b.y - a.y) << 7) / (int16_t)(b.x - a.x);
        if ((int16_t)(a.x - b.x) == -1)
            b.x = a.x;
        icpt = a.y - (slope * a.x >> 7);
        if (a.y < 0 || b.y < 0) {
            if (a.y < 0)
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = -((icpt << 7) / slope);
            if (v > 0 && v < LO16(g_90ea)) {
                pt[side].x = (int16_t)v;
                pt[side].y = 0;
            }
        }
        if (a.y > HI16(g_90ea) || b.y > HI16(g_90ea)) {
            if (a.y > HI16(g_90ea))
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = ((HI16(g_90ea) - icpt) << 7) / slope;
            if (v > 0 && v < LO16(g_90ea)) {
                pt[side].x = (int16_t)v;
                pt[side].y = HI16(g_90ea);
            }
        }
        slope = ((int32_t)(int16_t)(b.x - a.x) << 7) / (int16_t)(b.y - a.y);
        if ((int16_t)(a.y - b.y) == -1)
            b.y = a.y;
        icpt = a.x - (slope * a.y >> 7);
        if (a.x < 0 || b.x < 0) {
            if (a.x < 0)
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = -((icpt << 7) / slope);
            if (v > 0 && v < HI16(g_90ea)) {
                pt[side].x = 0;
                pt[side].y = (int16_t)v;
            }
        }
        if (a.x > LO16(g_90ea) || b.x > LO16(g_90ea)) {
            if (a.x > LO16(g_90ea))
                side = 0;
            else
                side = 1;
            if (slope == 0)
                return;
            v = ((LO16(g_90ea) - icpt) << 7) / slope;
            if (v > 0 && v < HI16(g_90ea)) {
                pt[side].x = LO16(g_90ea);
                pt[side].y = (int16_t)v;
            }
        }
    }
    if (pt[0].x == -1 && pt[0].y == -1) {
        pt[0].x = a.x;
        pt[0].y = a.y;
    }
    if (pt[1].x == -1 && pt[1].y == -1) {
        pt[1].x = b.x;
        pt[1].y = b.y;
    }
    MoveTo(dc, pt[0].x, pt[0].y);
    LineTo(dc, pt[1].x, pt[1].y);
}

/* Launch a new object of type g_9328 from object (type, idx) in direction
 * c (g_1050) [inferred]. d is clamped to 24, so the d > 25 sound never
 * plays (as in the original). */
/* t and lim stay in registers (their two slots are the frame's top);
 * written as separate statements they give the original's order:
 * (g_9208 + 2) * 2 into ax before the g_9334 clamp in cx. */
/* 12:2db6 */
void fn_12_2db6(int16_t type, int16_t idx, int16_t c, int16_t d, int16_t kind)
{
    int16_t t, lim;
    int16_t n;
    int16_t j;
    int16_t unused2[2];
    int16_t found;

    d = min(d, 24);
    t = (g_9208 + 2) * 2;
    lim = min((int16_t)(t * (min(g_9334, 10) + 10)) / 20, 10);
    if (lim <= g_9406[g_9328])
        return;
    n = -1;
    found = 0;
    do {
        n++;
        if (g_92ec[g_9328] <= n) {
            g_92ec[g_9328] = n + 1;
            GlobalUnlock(g_9100[g_9328]);
            g_9100[g_9328] = GlobalReAlloc(g_9100[g_9328],
                (int32_t)(g_92ec[g_9328] < 1 ? 1 : g_92ec[g_9328]) * 0x70, 0x42);
            g_1df8[g_9328] = (REC_70 *)GlobalLock(g_9100[g_9328]);
            g_1df8[g_9328][n].f_44 = 0x78;
            g_1df8[g_9328][n].f_42 = 0x64;
            g_1df8[g_9328][n].f_4c = 0xff;
            g_1df8[g_9328][n].f_62 = fn_11_3914;
            g_1df8[g_9328][n].f_5e = fn_07_570a;
            g_1df8[g_9328][n].f_53 = 0;
            g_1df8[g_9328][n].f_54 = 0;
            g_1df8[g_9328][n].f_32 = -1;
            g_1df8[g_9328][n].f_12 = g_1df8[g_9328][n].f_24;
            g_1df8[g_9328][n].f_2e = 0;
            g_5a4c[n].f_00 = -1;
            g_9406[g_9328] = n + 1;
        }
        if (g_5a4c[n].f_00 == -1) {
            g_5a4c[n].f_00 = 0;
            g_5a4c[n].f_10 = 0;
            g_1df8[g_9328][n].f_18 = 0;
            g_5a4c[n].f_12 = 0;
            g_1df8[g_9328][n].f_2e = 0;
            if (kind == 5)
                g_1df8[g_9328][n].f_44 = 0x78;
            else if (kind == 4)
                g_1df8[g_9328][n].f_44 = 0xc8;
            for (j = 0; j < 5; j++)
                g_5eac[n][j + 6] = g_5eac[n][j] = -100;
            g_1df8[g_9328][n].f_04.x = g_1df8[type][idx].f_20 / 2
                + (g_1df8[type][idx].f_20 / 32 + 4) * g_1050[c].x
                + g_1df8[type][idx].f_04.x - 32;
            g_1df8[g_9328][n].f_04.y = (g_1df8[type][idx].f_20 / 32 + 4) * g_1050[c].y
                + g_1df8[type][idx].f_20 / 2 + g_1df8[type][idx].f_04.y - 32;
            g_5a4c[n].f_04 = type;
            g_5a4c[n].f_06 = idx;
            g_5a4c[n].f_08 = type;
            g_5a4c[n].f_0a = idx;
            g_1df8[g_9328][n].f_0c = g_1050[c].x * 6;
            g_1df8[g_9328][n].f_0e = g_1050[c].y * 6;
            if (d > 25)
                fn_10_754a(0x1b, g_9328, n, 1);
            else
                fn_10_754a(0x19, g_9328, n, 1);
            g_5a4c[n].f_02 = d;
            break;
        }
    } while (found == 0);
    fn_07_2080(g_9328);
}

/* Turn direction cur (0..15) one step toward the direction from a to b
 * on the wrapping map [inferred]. dir stays uninitialised when mode is
 * neither 2 nor 5 (as in the original). */
/* w is a dead temporary; it makes CL compute b.x - w as neg(w - b.x). */
/* 12:67e8 */
int16_t fn_12_67e8(POINT a, POINT b, int16_t mode, int16_t cur)
{
    int16_t dx;
    int16_t dy;
    int16_t dir;
    int16_t w;
    int16_t unused[5];

    dx = b.x - a.x;
    if (fn_09_88ba(dx) > (int16_t)((LO16(g_05a0)) >> 1 << 3))
        dx = (0 > dx ? (LO16(g_05a0)) * 8 + b.x : b.x - (w = (LO16(g_05a0)) * 8)) - a.x;
    dy = b.y - a.y;
    if (fn_09_88ba(dy) > (int16_t)(HI16(g_05a0) >> 1 << 3))
        dy = (0 > dy ? HI16(g_05a0) * 8 + b.y : b.y - (w = HI16(g_05a0) * 8)) - a.y;
    if (mode == 2)
        dir = fn_08_19b0(dx, dy);
    else if (mode == 5)
        dir = fn_08_19b0(-dx, -dy);
    if (dir < 0 || dir > 15)
        return cur;
    if (dir == cur)
        return dir;
    if (dir < cur) {
        if ((int16_t)(cur - dir) < 9) {
            cur--;
        } else {
            cur++;
            if (cur > 15)
                cur = 0;
        }
    } else {
        if ((int16_t)(dir - cur) < 9) {
            cur++;
        } else {
            cur--;
            if (cur < 0)
                cur = 15;
        }
    }
    return cur;
}

/* Dispatch on kind [inferred]. */
/* 12:6dea */
void fn_12_6dea(int16_t kind, int16_t type, int16_t idx, int16_t d)
{
    if (g_2f4c[kind].f_12)
        fn_11_7c12(kind, type, idx);
    else if (kind == 5)
        fn_12_2db6(type, idx, g_1df8[type][idx].f_28, d, 5);
    else if (kind == 4)
        fn_12_2db6(type, idx, g_1df8[type][idx].f_28, d, 4);
    else if (kind == 1)
        fn_11_8a42(type, idx);
    else if (kind == 2)
        fn_11_947a(type, idx, 2);
    else if (kind == 15)
        fn_11_947a(type, idx, 15);
    else if (kind == 3)
        fn_11_9fdc(type, idx);
    else if (kind == 23)
        fn_11_9daa(type, idx);
    else if (kind == 13)
        fn_11_9078(type, idx);
}

/* Create an object's memory DC and bitmap and copy its image in
 * [inferred]. */
/* 12:2556 */
void fn_12_2556(int16_t type, int16_t idx)
{
    int16_t y;

    if (type == 1 || g_1df8[type][idx].f_3c != 0)
        return;
    if (type == 7)
        g_1df8[7]->f_28 = 5;
    g_1df8[type][idx].f_3c = CreateCompatibleDC(g_13dc);
    g_1df8[type][idx].f_3e = CreateCompatibleBitmap(g_13dc,
        g_1df8[type][idx].f_22 + g_1df8[type][idx].f_24 * 2,
        g_1df8[type][idx].f_22 + g_1df8[type][idx].f_24 * 2);
    g_1df8[type][idx].f_40 = SelectObject(g_1df8[type][idx].f_3c, g_1df8[type][idx].f_3e);
    if (g_920e)
        g_1df8[type][idx].rest = SelectPalette(g_1df8[type][idx].f_3c, g_920e, 0);
    if (type == g_9324 && g_7090[idx].f_010 > 1)
        y = g_1df8[type][idx].f_22 + g_1df8[type][idx].f_24;
    else
        y = 0;
    BitBlt(g_1df8[type][idx].f_3c, 0, 0,
           g_1df8[type][idx].f_22 + g_1df8[type][idx].f_24 * 2,
           g_1df8[type][idx].f_22 + g_1df8[type][idx].f_24 * 2,
           g_1df8[type][idx].f_3a,
           (g_1df8[type][idx].f_22 + g_1df8[type][idx].f_24) * g_1df8[type][idx].f_28,
           y, SRCCOPY);
}

/* 12:6ed8 */
int16_t fn_12_6ed8(int16_t i)
{
    int16_t u1;
    int16_t k;
    int16_t o;
    int16_t u2;
    int16_t dot;
    int16_t u3[2];
    POINT d;
    POINT p;
    int16_t u4[2];
    int16_t flag;

    if (g_3d50[i].rest != -1) {
        k = g_3d50[i].rest;
        o = g_4f2c[k].f_06;
        if (o >= 0 && o < 8 && g_1df8[0][o].f_18 == 0)
            flag = 1;
        else
            flag = 0;
        p = fn_08_29ea(g_4f2c[k].f_0a);
        d.x = p.x - g_1df8[8][i].f_00.x;
        d.y = p.y - g_1df8[8][i].f_00.y;
        if (g_4f2c[k].f_08 == 0 && flag == 0
            && rand() % 25 < (int16_t)(g_9334 / 3 + g_9208 + 2))
            return 1;
        dot = g_1050[g_1df8[8][i].f_28].x * d.x + g_1050[g_1df8[8][i].f_28].y * d.y;
        if ((g_4f2c[k].f_08 == 1 || g_4f2c[k].f_08 == 0) && dot < 0 && flag)
            return 0;
        if (g_4f2c[k].f_08 != 2 && flag == 0)
            return 1;
        if (dot <= 0)
            return 1;
        return 0;
    }
    return 1;
}

/* 12:633e */
void fn_12_633e(void)
{
    int16_t i;

    g_94a0 = (int16_t)(g_9208 + 1) / 2 + 2;
    if (g_1c32 == 0)
        fn_12_7006();
    g_1c32++;
    if (g_1c32 > 1)
        g_1c32 = 0;
    g_0d08 += g_0d06;
    if (g_0d08 > 4 || g_0d08 < 2)
        g_0d06 = -g_0d06;
    g_949e = 1;
    g_949a = g_949c = 0;
    for (i = 0; i < g_9406[8]; i++) {
        if (g_1df8[8][i].f_18 == 0) {
            g_1df8[8][i].f_1c = 0;
            if (g_3d50[i].f_1c == 1) {
                fn_12_390e(i);
            } else if (g_3d50[i].f_1c == 2) {
                fn_12_5636(i);
            } else if (g_3d50[i].f_1c == 3) {
                fn_12_1776(i / 2);
                i++;
            }
        }
    }
    if (g_949e) {
        for (i = 0; i < g_94a0; i++) {
            if (g_6938[i].f_0c != 0 && g_6938[i].f_0c < g_6938[i].f_0e)
                PatBlt(g_13dc, g_6938[i].scr.x, g_6938[i].scr.y,
                       (int16_t)(2 << g_9156) >> 1, (int16_t)(2 << g_9156) >> 1, BLACKNESS);
        }
    }
    if (g_949a)
        g_6988 = g_1e50 + 1000;
    if (g_949c)
        g_666c = g_9320 == 6 ? g_1e68 + 3 : g_1e68 + 8;
}

/* 12:3778 */
void fn_12_3778(void)
{
    int16_t i;
    int16_t old;
    int16_t flag;

    for (i = 0; i < g_92ec[10]; i++) {
        if (g_65cc[i].f_00 != -1) {
            flag = 0;
            if (g_65cc[i].f_00 == g_9324 && (g_7090[g_65cc[i].f_02].flag == 0
                                           || g_7090[g_65cc[i].f_02].f_147 != 0))
                flag = 1;
            if (g_65cc[i].f_04 == g_9324 && (g_7090[g_65cc[i].f_06].flag == 0
                                           || g_7090[g_65cc[i].f_06].f_147 != 0))
                flag = 1;
            if (g_1df8[g_65cc[i].f_00][g_65cc[i].f_02].f_18 == 0
                && g_1df8[g_65cc[i].f_04][g_65cc[i].f_06].f_18 == 0 && flag == 0)
                continue;
            g_1df8[10][i].f_18 = 1;
            g_1df8[g_65cc[i].f_00][g_65cc[i].f_02].f_32 = -1;
            g_1df8[g_65cc[i].f_04][g_65cc[i].f_06].f_36 = -1;
            g_65cc[i].f_00 = -1;
            g_65cc[i].f_04 = -1;
            g_65cc[i].f_08 = 0;
            old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
            fn_12_7256(g_13dc, g_65cc[i].f_1c, g_65cc[i].f_14);
            g_65cc[i].f_14 = g_65cc[i].f_10;
            g_65cc[i].f_1c = g_65cc[i].f_18;
            SelectObject(g_13dc, old);
            fn_07_2080(10);
        }
    }
}

/* Turn object (8, idx) one step toward object (14, idx2) [inferred]. */
/* 12:6902 */
int16_t fn_12_6902(int16_t idx, int16_t idx2)
{
    int16_t cur;
    int16_t dir;
    int16_t speed;

    cur = g_1df8[8][idx].f_28;
    if (g_3d50[idx].f_2c > 400)
        return fn_12_67e8(g_1df8[8][idx].f_04, g_1df8[14][idx2].f_04, 2, cur);
    switch (g_3d50[idx].f_0a) {
    case 4:
    case 5:
        speed = 0x56;
        break;
    case 11:
        speed = 0x3a;
        break;
    case 10:
    case 16:
        speed = 0x2a;
        break;
    case 1:
        speed = 300;
        break;
    default:
        speed = 0x5a;
        break;
    }
    fn_08_348e(8, idx, 14, idx2, speed);
    dir = fn_08_19b0(g_1df8[8][idx].f_0c, g_1df8[8][idx].f_0e);
    g_1df8[8][idx].f_0e = 0;
    g_1df8[8][idx].f_0c = g_1df8[8][idx].f_0e;
    if (dir < 0 || dir > 15)
        return cur;
    if (dir == cur)
        return dir;
    if (dir < cur) {
        if ((int16_t)(cur - dir) < 9) {
            cur--;
        } else {
            cur++;
            if (cur > 15)
                cur = 0;
        }
    } else {
        if ((int16_t)(dir - cur) < 9) {
            cur++;
        } else {
            cur--;
            if (cur < 0)
                cur = 15;
        }
    }
    return cur;
}

/* Erase the old marker bar and draw a new one at the scaled position
 * [inferred]. */
/* near-match 26%: 12:4d8e (only the register choice when saving es around
 * the far-pointer temp differs: the original keeps the segment in ax and
 * pushes it; everything after is shifted by one byte) */
void fn_12_4d8e(void)
{
    int16_t unused;
    RECT r;
    RECT r2;

    if (g_9eb5 == 1 && g_1c2c == 0)
        return;
    if (g_9eb5 == -1)
        return;
    r.left = r.right = ((int16_t)(g_1df8[12][1].f_04.x - g_1df8[14][main_ship].f_04.x) >> 4 << g_9156)
        + g_1df8[14][main_ship].f_00.x + (0x16 << g_9156);
    r.top = ((int16_t)(g_9ea8[g_9322].y - g_1df8[14][main_ship].f_04.y + 50) >> 4 << g_9156)
        + g_1df8[14][main_ship].f_00.y;
    r.bottom = ((int16_t)(g_9ea8[g_9322].x - g_1df8[14][main_ship].f_04.y + 50) >> 4 << g_9156)
        + g_1df8[14][main_ship].f_00.y;
    if (min(g_1c18.right, g_1c18.left) < LO16(g_90ea) && max(g_1c18.right, g_1c18.left) > 0
        && min(g_1c18.bottom, g_1c18.top) < HI16(g_90ea) && max(g_1c18.bottom, g_1c18.top) > 0)
        PatBlt(g_13dc, g_1c18.right, g_1c18.bottom, 2, g_1c18.top - g_1c18.bottom, BLACKNESS);
    if (g_9eb5 != 0) {
        g_1c2c = 0;
        return;
    }
    g_1c2c = 1;
    g_1c18.top = r.top;
    g_1c18.bottom = r.bottom;
    g_1c18.right = r.right;
    g_1c18.left = r.left;
    if (min(r.right, r.left) < LO16(g_90ea) && max(r.right, r.left) > 0
        && min(r.bottom, r.top) < HI16(g_90ea) && max(r.bottom, r.top) > 0) {
        PatBlt(g_13dc, r.right, r.bottom, 2, r.top - r.bottom, WHITENESS);
        if ((int16_t)(g_1df8[14][main_ship].f_22 + g_1df8[14][main_ship].f_00.x) > g_1c18.right
            && g_1df8[14][main_ship].f_00.x < (int16_t)(g_1c18.right + 2))
            hazards_ship_redraw_pending = 1;
    }
}

/* 12:515e */
void fn_12_515e(void)
{
    int16_t k;
    int16_t i;
    int16_t j;
    int16_t dy;
    int16_t dx;
    int16_t n;
    int16_t ok;

    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f_18 == 0
            && (int32_t)g_7090[i].f_01e * 100 / g_96d2[g_7090[i].f_04e].f_1e < 40) {
            for (k = n = 0; k < g_92ec[4]; k++)
                if (g_1df8[4][k].f_18 == 0)
                    n++;
            if (n < 2) {
                n = -1;
                for (k = 0; k < g_92ec[4]; k++) {
                    if (g_1df8[4][k].f_18 != 0 && g_1df8[4][k].f_51 == 0) {
                        n = k;
                        break;
                    }
                }
                if (n != -1) {
                    g_1df8[4][n].f_04.x = rand() % (LO16(g_05a0)) * 8;
                    g_1df8[4][n].f_04.y = rand() % HI16(g_05a0) * 8;
                    ok = 1;
                    for (j = 0; j <= g_9316; j++)
                        if (fn_08_285a(&dy, &dx, g_1df8[4][n].f_04, g_1df8[14][j].f_04) < 60)
                            ok = 0;
                    if (ok) {
                        g_1df8[4][n].f_00.y = -1000;
                        g_1df8[4][n].f_00.x = g_1df8[4][n].f_00.y;
                        g_1df8[4][n].f_18 = 0;
                        g_1df8[4][n].f_54 = 1;
                        g_1df8[4][n].f_1e = 0;
                        g_1df8[4][n].f_51 = 0;
                        g_1df8[4][n].f_26 = g_1df8[4][n].f_51;
                        g_1df8[4][n].f_2f = g_1df8[4][n].f_26;
                        fn_07_2080(4);
                        return;
                    }
                }
            }
        }
    }
}

/* 12:6b1e */
void fn_12_6b1e(void)
{
    int16_t i;
    int16_t r;

    for (i = 0; i < g_9406[11]; i++) {
        if (g_1df8[11][i].f_18 == 0) {
            g_1df8[11][i].f_1c = 0;
            if (g_8560[i].f_04 > 2)
                g_1df8[11][i].f_53 = 1;
            fn_08_1b54((char)i | 0xb00, 1);
            fn_08_1d54((OBJREF){i, 11}, 0x28);
            g_1df8[11][i].f_10 = (g_1df8[11][i].f_22 + g_1df8[11][i].f_24) * (g_8560[i].f_00 - 1)
                + g_1df8[11][i].f_24;
            fn_08_0b76((char)i | 0xb00, 3, g_39e8[g_1df8[11][i].f_4a], 0);
            g_8560[i].f_04++;
            if (g_1df8[11][i].f_1a != 0 && g_1df8[11][i].f_1c == 0) {
                g_943a = 11;
                g_943c = i;
                r = fn_08_50aa((char)i | 0xb00);
                if (r != -1) {
                    if (HIBYTE(r) == g_9324 && g_7090[LOBYTE(r)].f_0ea == 0
                        && g_7090[LOBYTE(r)].f_0e8 == 0)
                        fn_13_16ac(LOBYTE(r), (char)g_943c | g_943a << 8);
                    else
                        fn_08_5df2(11, i, HIBYTE(r), LOBYTE(r),
                                   fn_08_546c(r, &g_1df8[11][i].f_0c, &g_1df8[11][i].f_0e,
                                              g_1df8[11][i].f_20 + 2, 0x6e));
                }
            }
            if (g_8560[i].f_04 > g_8560[i].f_06 && g_92e8 == 0) {
                g_1df8[11][i].f_66(11, i);
                fn_07_2080(11);
            }
        } else if (g_1df8[11][i].f_51) {
            fn_12_129e(11, i);
        }
    }
}

/* 12:4f4e */
void fn_12_4f4e(void)
{
    int16_t i;
    int16_t flag;
    int16_t j;
    int16_t dy;
    int16_t k;
    int16_t ok;

    flag = 0;
    if (g_9ebf[g_9322] == 0)
        return;
    for (i = 0; i < g_9ebf[g_9322]; i++) {
        if (g_1df8[4][i].f_18 != 0) {
            if (g_698c < g_1e50) {
                for (j = 0; j <= g_9316; j++) {
                    if (g_1df8[14][j].f_18 == 0
                        && (int32_t)g_7090[j].f_01e * 100 / g_96d2[g_7090[j].f_04e].f_1e < 40) {
                        g_1df8[4][i].f_04.x = VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[g_9322][g_9eb9[g_9322] + g_9ebc[g_9322] + i].x
                            - g_1df8[4]->f_20 / 2;
                        g_1df8[4][i].f_04.y = VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[g_9322][g_9eb9[g_9322] + g_9ebc[g_9322] + i].y
                            - g_1df8[4]->f_20 / 2;
                        ok = 1;
                        for (k = 0; k <= g_9316; k++)
                            if (fn_08_285a(&dy, &flag, g_1df8[4][i].f_04, g_1df8[14][k].f_04) < 60)
                                ok = 0;
                        if (ok) {
                            g_9406[4] = g_9ebf[g_9322];
                            g_1df8[4][i].f_00.y = -1000;
                            g_1df8[4][i].f_00.x = g_1df8[4][i].f_00.y;
                            g_1df8[4][i].f_18 = 0;
                            g_1df8[4][i].f_54 = 1;
                            g_1df8[4][i].f_1e = 0;
                            g_1df8[4][i].f_51 = 0;
                            g_1df8[4][i].f_26 = g_1df8[4][i].f_51;
                            g_1df8[4][i].f_2f = g_1df8[4][i].f_26;
                            break;
                        }
                    }
                }
            }
            flag = 1;
        }
    }
    if (flag == 0)
        g_698c = g_1e50 + 10000;
}

/* Race gates [inferred]: blink and redraw the gate lines of the current
 * track (g_9eb9[g_9322] gates, ends g_1df8[8][i + 2] and its partner), then
 * bounce every live object of types 4..14 (not 5, 8, 12) off each gate line
 * (long arithmetic), count ships pushed against the same gate (8 times in a
 * row: self destruct) and advance a ship's next gate when it passes through.
 * near-match 87%: 12:3e98. Remaining difference: in the gate bounding-box test
 * the original reads l8c, l90 and l94 back from their stack slots, while this
 * source makes CL copy them into extra temporaries (frame 0xc6, not 0xc4).
 * Labels between the statements reset that but also lose the record-address
 * CSE. U1..U4, X1, X2 and pad1/pad2 are never used: they reproduce the frame
 * layout [layout-only]. */
void fn_12_3e98(int16_t unused)
{
    int16_t u4;
    int16_t j;
    int16_t u8;
    int16_t t;
    int16_t spd;
    int16_t i;
    HGDIOBJ old;
    int16_t pad1[12];
    POINT o;
    int16_t pad2[6];
    int32_t r;

    if (g_9320 != 6)
        return;
    o.x = (g_1df8[14][main_ship].f_0c >> 4 << g_9156) + (3 << g_9156);
    o.y = (3 << g_9156) + (g_1df8[14][main_ship].f_0e >> 4 << g_9156);
    fn_12_4f4e();
    old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
    for (i = 0; i < g_9eb9[g_9322]; i++)
        if (--g_1bb8[i] == 0)
            fn_12_7256(g_13dc, g_1934[i], g_19d4[i]);
    SelectObject(g_13dc, old);
    if (g_9eb5 != 0)
        return;
    spd = (int16_t)((fn_09_88ba(g_1df8[14][main_ship].f_0c) + fn_09_88ba(g_1df8[14][main_ship].f_0e))
        << g_9156) >> 4;
    if (g_8ff2)
        old = SelectObject(g_13dc, GetStockObject(WHITE_PEN));
    else if (g_1bb4 > g_1e50) {
        g_915a++;
        if (g_915a > 3)
            g_915a = 0;
        old = SelectObject(g_13dc, g_3b44[g_915a]);
    } else
        old = SelectObject(g_13dc, g_3b44[0]);
    for (i = 0; i < g_9eb9[g_9322]; i++) {
        if ((int16_t)(g_1df8[8][i + 2].f_51 - i) != 2 && g_1bb8[i] <= 0) {
            g_1934[i].x = ((int16_t)(g_1df8[8][i + 2].f_04.x - g_1df8[14][main_ship].f_04.x) >> 4 << g_9156)
                + g_1df8[14][main_ship].f_00.x + o.x;
            g_1934[i].y = ((int16_t)(g_1df8[8][i + 2].f_04.y - g_1df8[14][main_ship].f_04.y) >> 4 << g_9156)
                + g_1df8[14][main_ship].f_00.y + o.y;
            g_19d4[i].x = ((int16_t)(g_1df8[8][g_1df8[8][i + 2].f_51].f_04.x - g_1df8[14][main_ship].f_04.x) >> 4
                           << g_9156) + g_1df8[14][main_ship].f_00.x + o.x;
            g_19d4[i].y = ((int16_t)(g_1df8[8][g_1df8[8][i + 2].f_51].f_04.y - g_1df8[14][main_ship].f_04.y) >> 4
                           << g_9156) + g_1df8[14][main_ship].f_00.y + o.y;
            if (g_1df8[g_9324][main_ship].f_04.x + (int32_t)((int16_t)(LO16(g_90ea) << g_9150) / 2) + 1500 > g_67f8[i].left
                && (int16_t)(g_1df8[14][main_ship].f_04.x - (int16_t)(LO16(g_90ea) << g_9150) / 2 - 1500) < g_67f8[i].right
                && g_1df8[14][main_ship].f_04.y + (int32_t)((int16_t)(HI16(g_90ea) << g_9150) / 2) + 1500 > g_67f8[i].top
                && (int16_t)(g_1df8[14][main_ship].f_04.y - (int16_t)(HI16(g_90ea) << g_9150) / 2 - 1500) < g_67f8[i].bottom) {
                if ((int16_t)((4 - g_9208) * 5) < spd)
                    g_1bb8[i] = 1;
                else if ((int16_t)(10 - g_9208 * 3) < spd)
                    g_1bb8[i] = 2;
                else if (spd > 0)
                    g_1bb8[i] = 3;
                else
                    g_1bb8[i] = 4;
                fn_12_7256(g_13dc, g_1934[i], g_19d4[i]);
            } else
                g_1bb8[i] = -1;
        }
    }
    for (i = 0; i < g_9eb9[g_9322]; i++) {
        if ((int16_t)(g_1df8[8][i + 2].f_51 - i) == 2)
            continue;
        for (t = 4; t <= 14; t++) {
            if (t != 8 && t != 5 && t != 12)
            for (j = 0; j < g_9406[t]; j++) {
                if (g_1df8[t][j].f_18 == 0 && g_1df8[t][j].f_54 == 0) {
                    POINT a;
                    POINT b;
                    int32_t U1;
                    int32_t U2;
                    int32_t U3;
                    int32_t U4;
                    int32_t X1;
                    POINT n;
                    int32_t dxl;
                    int32_t dyl;
                    int32_t rx;
                    int32_t ry;
                    int32_t sgn;
                    int32_t cross;
                    int32_t proj;
                    int32_t len;
                    int32_t d;
                    int32_t X2;
                    int32_t k;
                    int32_t l8c;
                    int32_t l90;
                    int32_t l94;
                    int32_t l98;
                    int32_t l9c;
                    int32_t la0;
                    int32_t la4;
                r = g_1df8[t][j].f_20 / 2;
                a = g_1df8[8][i + 2].f_04;
                b = g_1df8[8][g_1df8[8][i + 2].f_51].f_04;
                a.x += 56;
                a.y += 56;
                b.x += 56;
                b.y += 56;
                if (t == 14 && g_7090[j].f_148 != g_1c08[j])
                    g_1c10[j] = 0;
                l8c = g_1df8[t][j].f_04.x;
                l90 = (r + 150) * 2;
                l94 = l8c + l90;
                if (l94 > min(b.x, a.x)
                    && (int16_t)(g_1df8[t][j].f_04.x - 300) < max(b.x, a.x)
                    && (l98 = g_1df8[t][j].f_04.y + l90) > min(b.y, a.y)
                    && (int16_t)(g_1df8[t][j].f_04.y - 300) < max(b.y, a.y)) {
                    len = fn_08_35d0(dxl = (int16_t)(b.x - a.x), dyl = (int16_t)(b.y - a.y));
                    rx = (int16_t)(g_1df8[t][j].f_14 - a.x);
                    ry = (int16_t)(g_1df8[t][j].f_16 - a.y);
                    d = fn_08_35d0(rx, ry);
                    if (ry * dxl - dyl * rx < 0)
                        sgn = -1;
                    else
                        sgn = 1;
                    n.x = sgn * dyl * r / len;
                    n.y = -(sgn * dxl * r / len);
                    rx = g_1df8[t][j].f_04.x + (int32_t)n.x - a.x + r;
                    ry = g_1df8[t][j].f_04.y + (int32_t)n.y - a.y + r;
                    d = fn_08_35d0(rx, ry);
                    cross = ry * dxl - rx * dyl;
                    proj = (ry * dyl + rx * dxl) / len;
                    if (cross * sgn < 0 && g_9496 == 0 && proj > 0 && proj < len) {
                        k = (abs32(cross / len) << 3) / 7;
                        g_1df8[t][j].f_04.x -= n.x * k / r;
                        g_1df8[t][j].f_04.y -= n.y * k / r;
                        proj = ((int32_t)g_1df8[t][j].f_0c * n.x + (int32_t)g_1df8[t][j].f_0e * n.y) / r;
                        if (abs32(proj) <= 3) {
                            if ((int32_t)g_1df8[t][j].f_0c * n.x + (int32_t)g_1df8[t][j].f_0e * n.y > 0)
                                proj = 4;
                            else
                                proj = -4;
                        }
                        if (t == 14 && (j != main_ship || flow_interactive == 0)) {
                            if (g_7090[j].f_148 == g_1c08[j]) {
                                g_1c10[j]++;
                                if (g_1c10[j] > 8)
                                    self_destruct_ship(14, j);
                            } else
                                g_1c10[j] = 0;
                            g_1c08[j] = g_7090[j].f_148;
                        }
                        if (t != 14)
                            ((void (*)(int16_t, int16_t, int16_t))g_1df8[t][j].f_5e)(t, j, 50);
                        g_1df8[t][j].f_0c -= n.x * proj * 7 / r / 4;
                        g_1df8[t][j].f_0e -= n.y * proj * 7 / r / 4;
                        if (g_1df8[t][j].f_0c == 0 && g_1df8[t][j].f_0e == 0)
                            g_1df8[t][j].f_0c = 2;
                        if (g_1df8[t][j].f_32 != -1 && g_65cc[g_1df8[t][j].f_30].f_04 != -1)
                            fn_11_947a(g_65cc[g_1df8[t][j].f_30].f_04, g_65cc[g_1df8[t][j].f_30].f_06, 2);
                        fn_10_754a(7, t, j, 1);
                        if (t == 14) {
                            g_7090[j].f_0e2 = 1;
                            g_1df8[14][j].f_26 = 1;
                            if (g_1df8[14][j].f_1a != 0)
                                g_1bb4 = g_7090[j].f_084 = g_1e50 + 300;
                            if (j != main_ship || flow_interactive == 0) {
                                l90 = g_1df8[t][j].f_04.x - (int16_t)(n.x * 200) / r - a.x + r - 50;
                                l8c = g_1df8[t][j].f_04.y - (int16_t)(n.y * 200) / r - a.y + r - 50;
                                if (g_7090[j].f_032.a == 8 && (j != main_ship || flow_interactive == 0)) {
                                    l98 = (int16_t)(g_1df8[8][g_7090[j].f_148 + g_9318 * 2].f_04.x
                                        - g_1df8[t][j].f_04.x + 50) + (int16_t)(n.x * 200) / r - r;
                                    l94 = (int16_t)(g_1df8[8][g_7090[j].f_148 + g_9318 * 2].f_04.y
                                        - g_1df8[t][j].f_04.y + 50) + (int16_t)(n.y * 200) / r - r;
                                } else if (j != main_ship || flow_interactive == 0) {
                                    l98 = (int16_t)(g_1df8[g_7090[j].f_032.a][g_7090[j].f_032.b].f_04.x
                                        - g_1df8[t][j].f_04.x + 50) + (int16_t)(n.x * 200) / r - r;
                                    l94 = (int16_t)(g_1df8[g_7090[j].f_032.a][g_7090[j].f_032.b].f_04.y
                                        - g_1df8[t][j].f_04.y + 50) + (int16_t)(n.y * 200) / r - r;
                                }
                                d = fn_08_35d0(l98, l94);
                                if (dxl == 0)
                                    dxl = 1;
                                if (dyl == 0)
                                    dyl = 1;
                                la4 = l94 * 10 / dyl - l98 * 10 / dxl;
                                if (la4 == 0)
                                    la4 = 1;
                                l9c = (l90 * 1000 / dxl - l8c * 1000 / dyl) / la4;
                                if (abs32(dyl) < abs32(dxl))
                                    la0 = (l9c * l98 + l90 * 100) / dxl;
                                else
                                    la0 = (l9c * l94 + l8c * 100) / dyl;
                                if (l9c > 1 && l9c < 50 && la0 > 0 && la0 < 100) {
                                    if (g_7090[j].f_032.a == 8) {
                                        if (g_7090[j].f_148 > 0)
                                            g_7090[j].f_148--;
                                        else
                                            g_7090[j].f_148 = g_9ea2 - 1;
                                    } else if (g_7090[j].f_032.a == 4) {
                                        g_8e34[j] = -1;
                                        g_7090[j].f_032.a = 8;
                                        g_7090[j].f_032.b = g_7090[j].f_148 + g_9318 * 2;
                                    }
                                }
                            }
                        }
                    }
                }
                if ((int16_t)(g_9ea2 - i + g_9ea4) == 1) {
                    g_1df8[t][j].f_14 = g_1df8[t][j].f_04.x + (int16_t)r;
                    g_1df8[t][j].f_16 = (int16_t)r + g_1df8[t][j].f_04.y;
                    g_9496 = 0;
                }
                }
            }
        }
    }
    SelectObject(g_13dc, old);
}

/* Pick the nearest suitable target within range for object (6, idx)
 * [inferred]. */
/* 12:0586 */
void fn_12_0586(int16_t idx, int16_t range)
{
    int16_t best;
    int16_t bt;
    int16_t bi;
    int16_t d;
    int16_t dy;
    int16_t dx;
    int16_t kind;
    int16_t t;
    int16_t i;

    kind = g_6670[idx + 4].f_04.x;
    best = 20000;
    bt = -1;
    if (g_92e8 != 0 && kind == 0x16)
        return;
    if (g_2f4c[kind].f_12 == 2) {
        if (g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_18 == 0)
            g_6670[idx + 4].f_1a = 1;
        return;
    }
    for (t = 0; t <= g_9324; t++) {
        if ((g_2f4c[kind].f_1c != 1 || t != g_9328) && t != 2) {
            for (i = 0; i < g_9406[t]; i++) {
                if ((t != 6 || i != idx) && g_1df8[t][i].f_18 == 0
                    && g_1df8[t][i].f_44 > 0x1e
                    && (g_2f4c[kind].f_12 == 3 || g_1df8[t][i].f_2f != 0)) {
                    d = fn_08_285a(&dy, &dx, g_1df8[6][idx].f_04, g_1df8[t][i].f_04);
                    if (g_6670[idx + 4].r.left == t && g_6670[idx + 4].r.top == i)
                        d <<= 2;
                    if (g_6670[idx + 4].r.left == g_9324 && t == g_9324
                        && g_96d2[g_7090[g_6670[idx + 4].r.top].f_04e].f_38 == g_96d2[g_7090[i].f_04e].f_38
                        && g_92e8 == 0)
                        d *= 7;
                    if (g_2f4c[kind].f_12 == 4) {
                        d += -25 * g_1df8[t][i].f_2f;
                        if (t == g_9328)
                            d /= 2;
                    } else if (t == g_9324) {
                        d = (int16_t)(d * 2) / 3;
                    }
                    if (d < range && d < best) {
                        best = d;
                        bt = t;
                        bi = i;
                    }
                }
            }
        }
    }
    if (bt == -1)
        return;
    if (g_6670[idx + 4].r.left == bt && g_6670[idx + 4].r.top == bi && g_6670[idx + 4].r.right <= 0x3c)
        return;
    g_6670[idx + 4].f_1a = 1;
    g_6670[idx + 4].f_00.x = bt;
    g_6670[idx + 4].f_00.y = bi;
}

/* Turn the objects of each group round its centre [inferred]. */
/* 12:7006 */
void fn_12_7006(void)
{
    int16_t k;
    int16_t j;
    int32_t s0;
    int32_t c0;
    int32_t s1;
    int32_t c1;

    for (k = 0; k < g_9344; k++) {
        for (j = g_4f2c[k].first; j < g_4f2c[k].f_02; j++) {
            g_3d50[j].f_2e += g_4f2c[k].f_0e;
            if (g_3d50[j].f_2e < 0)
                g_3d50[j].f_2e = g_3d50[j].f_2e + 0xb40;
            if (g_3d50[j].f_2e > 0xb40)
                g_3d50[j].f_2e -= 0xb40;
            s0 = fn_06_71b2(g_3d50[j].f_2e >> 3);
            c0 = fn_06_720c(g_3d50[j].f_2e >> 3);
            s1 = fn_06_71b2((g_3d50[j].f_2e >> 3) + 1);
            c1 = fn_06_720c((g_3d50[j].f_2e >> 3) + 1);
            s0 += (s1 - s0) * (g_3d50[j].f_2e % 8) / 8;
            c0 += (c1 - c0) * (g_3d50[j].f_2e % 8) / 8;
            g_1df8[8][j].f_04.x = (int16_t)(g_4f2c[k].radius * c0 / 128) + g_4f2c[k].f_0a.x;
            g_1df8[8][j].f_04.y = (int16_t)(s0 * g_4f2c[k].radius / 128) + g_4f2c[k].f_0a.y;
            g_1df8[8][j].f_0c = (int16_t)(s0 * ((int32_t)g_4f2c[k].radius * g_4f2c[k].f_0e) / -82000L);
            g_1df8[8][j].f_0e = (int16_t)(c0 * g_4f2c[k].radius * g_4f2c[k].f_0e / 82000L);
            if (g_1df8[8][j].f_04.y > (int16_t)(HI16(g_05a0) * 8))
                g_1df8[8][j].f_04.y -= HI16(g_05a0) * 8;
            else if (g_1df8[8][j].f_04.y < 0)
                g_1df8[8][j].f_04.y += HI16(g_05a0) * 8;
            if (g_1df8[8][j].f_04.x > (int16_t)((LO16(g_05a0)) * 8))
                g_1df8[8][j].f_04.x -= (LO16(g_05a0)) * 8;
            else if (g_1df8[8][j].f_04.x < 0)
                g_1df8[8][j].f_04.x += (LO16(g_05a0)) * 8;
        }
    }
}

/* Fire for object (6, idx) when its weapon kind allows it [inferred]. */
/* 12:64aa */
void fn_12_64aa(int16_t idx, int16_t kind)
{
    int16_t i;
    int16_t dir;
    int16_t fire;

    if (g_6670[idx + 4].r.right & 3 || g_6670[idx + 4].r.right < 13)
        return;
    fire = 0;
    if (g_2f4c[kind].f_1e == 2 || g_2f4c[kind].f_1e == 1) {
        if (g_2f4c[kind].f_1e == 1)
            fire = 1;
        else if (rand() % 3 == 0)
            fire = 1;
    } else if (g_2f4c[kind].f_1e == 3 && g_1df8[6][idx].f_1a != 0) {
        for (i = 0; i <= g_9316; i++) {
            if (g_1df8[g_9324][i].f_18 == 0 && g_1df8[g_9324][i].f_1a != 0) {
                dir = fn_08_19b0(g_1df8[g_9324][i].f_00.x - g_1df8[6][idx].f_00.x,
                                 g_1df8[g_9324][i].f_00.y - g_1df8[6][idx].f_00.y);
                if (g_1df8[6][idx].f_28 <= (int16_t)(dir + 1) && g_1df8[6][idx].f_28 >= (int16_t)(dir - 1)) {
                    fire = 1;
                    break;
                }
            }
        }
    } else if (g_2f4c[kind].f_1e == 4) {
        if (g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_18 == 0
            && g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_1a != 0) {
            dir = fn_08_19b0(g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_00.x - g_1df8[6][idx].f_00.x,
                             g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_00.y - g_1df8[6][idx].f_00.y);
            if (g_1df8[6][idx].f_28 <= (int16_t)(dir + 1) && g_1df8[6][idx].f_28 >= (int16_t)(dir - 1))
                fire = 1;
        }
    }
    if (fire) {
        switch (g_2f4c[kind].f_1c) {
        case 1:
            fn_12_2db6(6, idx, g_1df8[6][idx].f_28, 11, 5);
            break;
        case 2:
            fn_12_2db6(6, idx, g_1df8[6][idx].f_28, 11, 4);
            break;
        case 4:
            spawn_gun_shot(6, idx);
            break;
        case 3:
            if (g_1df8[6][idx].f_50 > 0x19)
                fn_11_9fdc(6, idx);
            break;
        }
    }
}

/* Steer object (6, idx) toward its target and accelerate [inferred]. */
/* 12:07c0 */
void fn_12_07c0(int16_t idx)
{
    int16_t t;
    int16_t ti;
    int16_t u1;
    int16_t kind;
    int16_t dir;
    int16_t u2[9];
    POINT me;
    POINT tgt;
    POINT v;
    int16_t u3;
    int16_t jitter;
    int16_t alt;
    int16_t d;
    int16_t q1;
    int16_t q2;

    kind = g_6670[idx + 4].f_04.x;
    jitter = 0;
    me.x = (g_1df8[6][idx].f_20 >> 1) + g_1df8[6][idx].f_04.x;
    me.y = (g_1df8[6][idx].f_20 >> 1) + g_1df8[6][idx].f_04.y;
    if (g_6670[idx + 4].f_14 == 2) {
        tgt.x = (g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_22 >> 1)
            + g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_04.x;
        tgt.y = (g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_22 >> 1)
            + g_1df8[g_6670[idx + 4].f_00.x][g_6670[idx + 4].f_00.y].f_04.y;
        alt = 0;
    } else {
        tgt.x = (g_1df8[g_6670[idx + 4].f_10][g_6670[idx + 4].f_12].f_22 >> 1)
            + g_1df8[g_6670[idx + 4].f_10][g_6670[idx + 4].f_12].f_04.x;
        tgt.y = (g_1df8[g_6670[idx + 4].f_10][g_6670[idx + 4].f_12].f_22 >> 1)
            + g_1df8[g_6670[idx + 4].f_10][g_6670[idx + 4].f_12].f_04.y;
        alt = 1;
    }
    t = g_6670[idx + 4].f_00.x;
    ti = g_6670[idx + 4].f_00.y;
    if (t == g_9324 && alt == 0 && g_7090[ti].f_0e8 && g_2f4c[kind].f_46 == 0)
        jitter = 1;
    tgt.x += (rand() % 300 - 150) * jitter * 8;
    tgt.y += (rand() % 300 - 150) * jitter * 8;
    if (jitter)
        g_6670[idx + 4].f_1a = 0;
    if (g_2f4c[kind].f_0e != 2) {
        dir = steer_toward_direction(me.y, me.x, tgt.y, tgt.x, 0, g_6670[idx + 4].f_14,
                                     -100, -100, -100, 0);
    } else {
        g_1df8[6][idx].f_28 = steer_toward_direction(me.y, me.x, tgt.y, tgt.x,
                                                    g_1df8[6][idx].f_28, g_6670[idx + 4].f_14,
                                                    -1, -1, -1, 0);
        dir = g_1df8[6][idx].f_28;
    }
    if (g_2f4c[kind].f_28 && jitter == 0) {
        d = fn_08_285a(&q1, &q2, me, tgt);
        if (d < g_2f4c[kind].f_28) {
            g_1df8[6][idx].f_48 <<= 1;
            fn_12_274a(6, idx);
            fn_07_2080(6);
        }
    }
    v.x = g_1050[dir].x * g_2f4c[kind].f_14;
    v.y = g_1050[dir].y * g_2f4c[kind].f_14;
    if (alt) {
        v.x *= 2;
        v.y *= 2;
    }
    g_1df8[6][idx].f_0c += v.x;
    g_1df8[6][idx].f_0e += v.y;
    fn_08_1cbe((OBJREF){idx, 6}, g_2f4c[kind].f_16);
}

/* Break object (type, idx) up into debris particles [inferred]. */
/* An unused block-scope local in the inner loop puts the later fn_08_29ea
 * return temps at bp-0x10, as in the game. */
/* 12:2b20 */
void fn_12_2b20(int16_t type, int16_t idx)
{
    int16_t k;
    int16_t j;
    int16_t n;

    if (fn_08_7ba8(fn_08_29ea(g_1df8[type][idx].f_04)))
        PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
               g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, BLACKNESS);
    if (g_1df8[type][idx].f_48 == 1) {
        n = 1;
    } else {
        switch (g_9208) {
        case 0:
            n = (int16_t)(g_1df8[type][idx].f_48 * 30) / 100;
            break;
        case 1:
            n = (int16_t)(g_1df8[type][idx].f_48 * 60) / 100;
            break;
        case 2:
            n = g_1df8[type][idx].f_48;
            break;
        case 3:
            n = (int16_t)(g_1df8[type][idx].f_48 * 130) / 100;
            break;
        }
        n = n < 2 ? 2 : n;
    }
    for (k = 0; k < n; k++) {
        for (j = 0; j < 45; j++) {
            if (g_1e90[j].f_00 == -1) {
                if (k == 0)
                    g_1e90[j].f_0a = 4;
                else
                    g_1e90[j].f_0a = 1;
                g_1e90[j].f_00 = 1;
                if (j > g_9434)
                    g_9434 = j;
                g_1e90[j].f_10 = (int32_t)(rand() % 100) + (int16_t)(k * 20) + g_1e50;
                g_1e90[j].f_02 = 10;
                g_1e90[j].f_06 = type;
                g_1e90[j].f_08 = idx;
                { int16_t pad[2];
                if (k == 0) {
                    g_5224[j] = g_1df8[type][idx].f_04;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                } else {
                    g_5224[j].x = (-40 - rand() % (int16_t)((n + 40) * 2) - n) * 8
                        + g_1df8[type][idx].f_20 / 2 + g_1df8[type][idx].f_04.x;
                    g_5224[j].y = (-40 - rand() % (int16_t)((n + 40) * 2) - n) * 8
                        + g_1df8[type][idx].f_20 / 2 + g_1df8[type][idx].f_04.y;
                    g_5170[j] = fn_08_29ea(g_5224[j]);
                }
                }
                g_9430++;
                break;
            }
        }
    }
    fn_10_754a(0x45, type, idx, 1);
}

/* Object (type, idx) is destroyed [inferred]. */
/* 12:2288 */
void fn_12_2288(int16_t type, int16_t idx)
{
    int16_t i;
    int16_t all;

    if (type == g_9328) {
        if (g_1df8[type][idx].f_2e == 0) {
            fn_10_754a(0x27, type, idx, 1);
            g_5a4c[idx].f_00 = g_5a4c[idx].f_02 - 7;
            g_1df8[type][idx].f_2e = -1;
        }
    } else if (type == g_9324 && g_7090[idx].flag == 0) {
        fn_12_274a(g_9324, idx);
    } else {
        if (type == 14 && g_7090[idx].f_052 >= 2 && g_7090[idx].f_052 <= 4
            && g_7090[idx].f_058 == idx && g_7090[idx].f_054 == 14) {
            if (idx == main_ship) {
                if (g_1df8[14][g_7090[idx].f_056].f_18 == 0
                    && g_7090[g_7090[idx].f_056].f_0d6 != -1)
                    g_93b6 = g_7090[g_7090[idx].f_056].f_0d6;
            } else if (g_7090[idx].f_056 == main_ship && g_7090[idx].f_0d6 != -1) {
                g_93b6 = g_7090[idx].f_0d6;
            }
        }
        if (g_1df8[type][idx].f_1a)
            fn_12_2556(type, idx);
        if (type == g_9324)
            g_7090[idx].f_026[4] = 1;
        if (g_1df8[type][idx].f_1a) {
            fn_07_13b2(1, type, idx);
        } else {
            g_1df8[type][idx].f_18 = 1;
            fn_07_2080(type);
            fn_10_754a(0x27, type, idx, 1);
        }
        if (type == g_9324 && g_96d2[g_7090[idx].f_04e].f_38 == 7 && g_7090[idx].f_054 == g_9324
            && g_1df8[g_9324][idx].f_36 == g_9324
            && g_1df8[g_9324][idx].f_38 == g_7090[idx].f_056) {
            fn_12_2288(g_9324, g_1df8[g_9324][idx].f_38);
            if (g_1df8[g_9324][idx].f_38 == main_ship) {
                g_1e80 = g_1e50 + 1000;
                g_93a4 = 1;
            }
        }
        if (type == g_9324 && idx == main_ship && g_1df8[g_9324][idx].f_32 == g_9324
            && g_96d2[g_7090[g_1df8[g_9324][idx].f_34].f_04e].f_38 == 7)
            g_93a4 = 1;
        if (type == g_9324 && g_92e8 && idx == 1)
            g_1df8[14][main_ship].f_54 = 0;
        if (type == 0)
            fn_07_5ae8(idx, 0);
        if (g_9320 == 7 && type == g_9324) {
            all = 1;
            for (i = 0; i <= g_9316; i++)
                if (i != idx && i != main_ship && g_7090[i].flag && g_1df8[14][i].f_18 == 0)
                    all = 0;
            if (all)
                g_6670[0].f_1a = -1;
        }
    }
}

/* 12:0ae4 */
void fn_12_0ae4(void)
{
    int16_t i;
    int16_t u1[2];
    int16_t r;
    int16_t gap;
    int16_t size;
    int16_t u2[10];

    gap = g_1df8[4]->f_22;
    size = g_1df8[4]->f_24;
    for (i = 0; i < g_9406[4]; i++)
        g_1df8[4][i].f_1c = 0;
    for (i = 0; i < g_9406[4]; i++) {
        if (g_1df8[4][i].f_18 == 0) {
            if (g_1df8[4][i].f_54) {
                g_1df8[4][i].f_0e = 0;
                g_1df8[4][i].f_0c = g_1df8[4][i].f_0e;
            }
            if (g_1df8[4][i].f_1a) {
                fn_08_1d54((OBJREF){i, 4}, 0x28);
                fn_08_1b54((char)i | 0x400, 1);
                g_1df8[4][i].f_10 = g_1df8[4][i].f_26 / 5 * (size + gap) + size;
                fn_08_0b76((char)i | 0x400, 1, g_39e8[4], 0);
                if (g_9214 == 0) {
                    g_1df8[4][i].f_26 += g_1df8[4][i].f_2f;
                    if (g_1df8[4][i].f_2f) {
                        if (g_1df8[4][i].f_26 < 5) {
                            g_1df8[4][i].f_26 = 5;
                            g_1df8[4][i].f_2f = g_1df8[4][i].f_50;
                        }
                        if (g_1df8[4][i].f_26 > 21) {
                            g_1df8[4][i].f_26 = 21;
                            g_1df8[4][i].f_2f = -g_1df8[4][i].f_50;
                        }
                        if (g_1df8[4][i].f_50 > rand() % 120 && g_1df8[4][i].f_50 > rand() % 20) {
                            fn_12_274a(4, i);
                            fn_07_2080(4);
                        }
                    }
                }
            } else if (g_9142 % 3 == 0) {
                fn_08_1d54((OBJREF){i, 4}, 0x28);
                fn_08_1b54((char)i | 0x400, 3);
            }
            if (g_1df8[4][i].f_1a != 0 && g_1df8[4][i].f_1c == 0) {
                g_943a = 4;
                g_943c = i;
                r = fn_08_50aa((char)i | 0x400);
                if (r != -1) {
                    if (HIBYTE(r) == g_9324 && g_7090[LOBYTE(r)].f_0ea == 0
                        && g_7090[LOBYTE(r)].f_0e8 == 0)
                        fn_13_16ac(LOBYTE(r), (char)g_943c | g_943a << 8);
                    else if (HIBYTE(r) == 0 && g_57a8[LOBYTE(r)].f_02 != 0
                             || HIBYTE(r) == g_9328)
                        fn_08_5df2(4, i, HIBYTE(r), LOBYTE(r), 0x7d);
                    else
                        fn_08_5df2(4, i, HIBYTE(r), LOBYTE(r),
                                   fn_08_546c(r, &g_1df8[4][i].f_0c, &g_1df8[4][i].f_0e,
                                              g_1df8[4][i].f_20 + 2, g_1df8[4][i].f_44));
                }
            }
        } else if (g_1df8[4][i].f_51) {
            fn_12_0e5c(i);
        }
    }
}

/* Attach link k to object (type, idx); 0 when it is already attached
 * there [inferred]. */
/* 12:3498 */
int16_t fn_12_3498(int16_t type, int16_t idx, int16_t k)
{
    int16_t unused[5];
    int16_t j;
    int16_t old;

    if (g_65cc[k].f_04 == type && g_65cc[k].f_06 == idx || type == 10)
        return 0;
    old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
    fn_12_7256(g_13dc, g_65cc[k].f_1c, g_65cc[k].f_14);
    g_65cc[k].f_14 = g_65cc[k].f_10;
    g_65cc[k].f_1c = g_65cc[k].f_18;
    SelectObject(g_13dc, old);
    g_1df8[10][k].f_18 = 1;
    PatBlt(g_13dc, g_1df8[10][k].f_00.x, g_1df8[10][k].f_00.y,
           g_1df8[10][k].f_22, g_1df8[10][k].f_22, BLACKNESS);
    if (g_65cc[k].f_04 == 14 && type == 14
        && (g_7090[g_65cc[k].f_06].f_032.a != 14 || g_7090[g_65cc[k].f_06].f_032.b != idx))
        type = -1;
    if (type == 6)
        g_6670[idx + 4].r.right /= 4;
    if (type != -1 && (g_1df8[type][idx].f_54 == 0 || type == 4)) {
        fn_10_754a(6, 10, k, 1);
        g_1df8[type][idx].f_54 = 0;
        if (g_1df8[type][idx].f_32 != -1) {
            j = g_1df8[type][idx].f_30;
            g_1df8[10][j].f_18 = 1;
            g_1df8[type][idx].f_32 = -1;
            g_1df8[g_65cc[j].f_04][g_65cc[j].f_06].f_36 = -1;
            g_65cc[j].f_00 = -1;
            g_65cc[j].f_04 = -1;
            g_65cc[j].f_08 = 0;
            old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
            fn_12_7256(g_13dc, g_65cc[j].f_1c, g_65cc[j].f_14);
            g_65cc[j].f_14 = g_65cc[j].f_10;
            g_65cc[j].f_1c = g_65cc[j].f_18;
            SelectObject(g_13dc, old);
        }
        g_1df8[type][idx].f_32 = g_65cc[k].f_04;
        g_1df8[type][idx].f_34 = g_65cc[k].f_06;
        g_1df8[type][idx].f_30 = k;
        g_1df8[g_65cc[k].f_04][g_65cc[k].f_06].f_36 = type;
        g_1df8[g_65cc[k].f_04][g_65cc[k].f_06].f_38 = idx;
        g_65cc[k].f_00 = type;
        g_65cc[k].f_02 = idx;
    } else {
        g_1df8[g_65cc[k].f_04][g_65cc[k].f_06].f_36 = -1;
        g_65cc[k].f_00 = -1;
        g_65cc[k].f_04 = -1;
        fn_07_2080(10);
    }
    g_65cc[k].f_08 = 0;
    return 1;
}

/* 12:532c */
void fn_12_532c(void)
{
    int16_t i;
    int16_t r;
    int16_t t;
    int16_t dy;
    int16_t dx;
    int16_t j;
    int16_t d;
    int16_t v;

    for (i = 0; i < g_9406[9]; i++) {
        if (g_1df8[9][i].f_18 == 0) {
            if (g_1c2e < g_1e50 && g_1df8[9][i].f_50 < 100)
                g_1df8[9][i].f_50++;
            if (g_1df8[9][i].f_1a != 0 || fn_13_59e8(9, i)) {
                g_1df8[9][i].f_28 = g_1df8[9][i].f_26 / 100;
                v = g_1df8[9][i].f_50 < 12 ? 12 : g_1df8[9][i].f_50;
                if (g_1df8[9][i].f_50 < 0)
                    v = -v;
                g_1df8[9][i].f_26 += v;
                if (g_1df8[9][i].f_26 > 899)
                    g_1df8[9][i].f_26 = 0;
                if (g_1df8[9][i].f_26 < 0)
                    g_1df8[9][i].f_26 = 899;
            }
            if (g_1df8[9][i].f_1a) {
                fn_08_1d54((OBJREF){i, 9}, 0x1e);
                fn_08_1b54((char)i | 0x900, 1);
                g_1df8[9][i].f_10 = (g_1df8[9][i].f_22 + g_1df8[9][i].f_24) * g_1df8[9][i].f_28
                    + g_1df8[9][i].f_24;
                g_1df8[9][i].f_12 = g_1df8[9][i].f_24;
                fn_08_0b76((char)i | 0x900, 1, g_39e8[22], 0);
                if (g_1df8[9][i].f_50 > 20) {
                    for (t = 0; t <= g_9324; t++) {
                        for (j = 0; j < g_9406[t]; j++) {
                            if (g_1df8[t][j].f_18 == 0 && t != 9 && g_1df8[t][j].f_44 != 0
                                && (t != 0 || g_1df8[0][j].f_53 != 2)) {
                                d = fn_08_285a(&dy, &dx, g_1df8[9][i].f_04, g_1df8[t][j].f_04);
                                if (d < 200) {
                                    if (t == 6 || t == 0 || g_1df8[9][i].f_50 > rand() % 100)
                                        fn_11_a234(9, i, t, j);
                                    break;
                                }
                            }
                        }
                    }
                }
            } else if (g_9142 % 3 == 0) {
                fn_08_1d54((OBJREF){i, 9}, 0x1e);
                fn_08_1b54((char)i | 0x900, 3);
            }
            if (g_1df8[9][i].f_1a != 0 && g_1df8[9][i].f_1c == 0) {
                g_943a = 9;
                g_943c = i;
                r = fn_08_50aa((char)i | 0x900);
                if (r != -1)
                    fn_08_5df2(9, i, HIBYTE(r), LOBYTE(r),
                               fn_08_546c(r, &g_1df8[9][i].f_0c, &g_1df8[9][i].f_0e,
                                          g_1df8[9][i].f_20 + 2, g_1df8[9][i].f_44));
            }
        }
    }
    if (g_9406[9] && g_1c2e < g_1e50)
        g_1c2e = g_1e50 + 1000;
}

/* Find an object in area p; returns (type << 8) | idx or -1 [inferred]. */
/* 12:1f7a */
int16_t fn_12_1f7a(int16_t p)
{
    int16_t pad[4];
    RECT r;
    RECT r2;
    int16_t i;
    int16_t pad2[11];
    DWORD t;

    if (g_9320 == 7 && g_6670[0].f_1a == 0
        && (int16_t)(g_1df8[8][1].f_04.x - g_1df8[8][0].f_04.x - g_1df8[8][0].f_20) < 100)
        return -1;
    for (i = 0; i < g_9146; i++) {
        if (g_1df8[g_507c[i]][g_50e0[i]].f_18 == 0) {
            SetRect(&r, g_1df8[g_507c[i]][g_50e0[i]].f_04.x, g_1df8[g_507c[i]][g_50e0[i]].f_04.y,
                    g_1df8[g_507c[i]][g_50e0[i]].f_04.x + g_1df8[g_507c[i]][g_50e0[i]].f_20,
                    g_1df8[g_507c[i]][g_50e0[i]].f_04.y + g_1df8[g_507c[i]][g_50e0[i]].f_20);
            if (IntersectRect(&r2, &g_6670[p].r, &r)) {
                t = 0;
                if (g_507c[i] == g_9324) {
                    if (g_50e0[i] == main_ship)
                        t = g_7090[g_50e0[i]].f_088 + 300;
                    else
                        t = g_7090[g_50e0[i]].f_088 + 3000;
                }
                if (g_507c[i] != 7 && g_1df8[g_507c[i]][g_50e0[i]].f_44 != 0xdac
                    && (g_507c[i] != g_9324 || t < g_1e50)) {
                    if (g_1df8[g_507c[i]][g_50e0[i]].f_2e != 1
                        || (g_507c[i] == g_9324 && g_7090[g_50e0[i]].f_026[4] == 2))
                        return g_50e0[i] | g_507c[i] << 8;
                }
            }
            if (g_507c[i] == g_9324 && g_7090[g_50e0[i]].f_032.a == 12
                && g_7090[g_50e0[i]].f_032.b == g_6670[p].f_18 && g_7090[g_50e0[i]].f_038 == 2) {
                if (g_50e0[i] != main_ship || g_9134 != 0) {
                    SetRect(&r, g_1df8[g_507c[i]][g_50e0[i]].f_04.x - 320,
                            g_1df8[g_507c[i]][g_50e0[i]].f_04.y - 320,
                            g_1df8[g_507c[i]][g_50e0[i]].f_04.x + 800,
                            g_1df8[g_507c[i]][g_50e0[i]].f_04.y + 800);
                    if (PtInRect(&r, g_1df8[12][g_6670[p].f_18].f_04)) {
                        g_1df8[g_507c[i]][g_50e0[i]].f_0c = 0;
                        g_1df8[g_507c[i]][g_50e0[i]].f_0e = 0;
                        if (g_6670[p].f_1a == 0 || (g_6670[p].f_1a < 0
                            && abs((int16_t)(g_6670[p].r.right - g_6670[p].r.left - 480)) <= 16)) {
                            g_7090[g_50e0[i]].f_006 = g_7090[g_50e0[i]].f_032.a = 12;
                            g_7090[g_50e0[i]].f_008 = g_7090[g_50e0[i]].f_032.b = g_6670[p].f_18 + 1;
                            g_7090[g_50e0[i]].f_03a = g_7090[g_50e0[i]].f_03c =
                                g_7090[g_50e0[i]].f_036 = g_7090[g_50e0[i]].f_038 = 2;
                            fn_13_2f30(i);
                        }
                    }
                }
            }
        }
    }
    return -1;
}

/* Update and draw the links of the type-10 objects [inferred]. */
/* 12:3148 */
void fn_12_3148(void)
{
    int16_t t;
    int16_t x;
    int16_t v;
    int16_t i;
    int16_t a;
    int16_t b;
    HPEN old;
    HPEN pen;
    POINT p;
    POINT q;

    for (i = 0; i < g_9406[10]; i++) {
        if (g_1df8[10][i].f_18 == 0) {
            g_1df8[10][i].f_1c = 0;
            g_1df8[10][i].f_28 = fn_08_19b0(g_65cc[i].f_10.x - g_65cc[i].f_18.x,
                                           g_65cc[i].f_10.y - g_65cc[i].f_18.y);
            fn_08_1b54((char)i | 0xa00, 1);
            g_1df8[10][i].f_10 = (g_1df8[10][i].f_22 + g_1df8[10][i].f_24) * g_1df8[10][i].f_28
                + g_1df8[10][i].f_24;
            fn_08_0b76((char)i | 0xa00, 3, g_39e8[3], 0);
            t = g_65cc[i].f_04;
            x = g_65cc[i].f_06;
            if ((int16_t)(HI16(g_90ea) * 8) / 2 < fn_08_285a(&a, &b, g_1df8[10][i].f_04, g_1df8[t][x].f_04))
                g_65cc[i].f_08 += 50;
            if (g_1df8[10][i].f_1a == 0)
                p = fn_08_29ea(g_1df8[10][i].f_04);
            else
                p = g_1df8[10][i].f_00;
            if (g_1df8[t][x].f_1a == 0)
                q = fn_08_29ea(g_1df8[t][x].f_04);
            else
                q = g_1df8[t][x].f_00;
            g_65cc[i].f_10.x = g_1df8[10][i].f_22 / 2 + p.x;
            g_65cc[i].f_10.y = g_1df8[10][i].f_22 / 2 + p.y;
            g_65cc[i].f_18.x = g_1df8[t][x].f_22 / 2 + q.x;
            g_65cc[i].f_18.y = g_1df8[t][x].f_22 / 2 + q.y;
            old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
            fn_12_7256(g_13dc, g_65cc[i].f_1c, g_65cc[i].f_14);
            SelectObject(g_13dc, old);
            pen = CreatePen(PS_SOLID, 1, RGB(rand() % 128, 0, rand() % 128 + 128));
            old = SelectObject(g_13dc, pen);
            fn_12_7256(g_13dc, g_65cc[i].f_18, g_65cc[i].f_10);
            SelectObject(g_13dc, old);
            DeleteObject(pen);
            g_65cc[i].f_14 = g_65cc[i].f_10;
            g_65cc[i].f_1c = g_65cc[i].f_18;
            g_65cc[i].f_08++;
            if (g_1df8[10][i].f_1a != 0 && g_1df8[10][i].f_1c == 0) {
                g_943a = 10;
                g_943c = i;
                v = fn_08_50aa((char)i | 0xa00);
                if (v != -1)
                    fn_12_3498(HIBYTE(v), LOBYTE(v), i);
            }
            if (g_65cc[i].f_08 > 41)
                fn_12_3498(-1, -1, i);
            if (g_65cc[i].f_04 == g_9324 && g_65cc[i].f_06 == main_ship && g_951a == 0)
                fn_07_1208();
        }
    }
}

/* Update and draw the type-8 object n [inferred]. */
/* 12:390e */
void fn_12_390e(int16_t n)
{
    int16_t dead;
    int16_t dead2;
    int16_t k;
    int16_t v;
    int16_t m;
    int16_t old;
    int16_t unused[2];
    POINT p;
    int16_t unused2;
    int16_t pct;
    int16_t r;

    if (g_1df8[8][n].f_1a != 0 || g_3d50[n].f_30 == 4 || g_3d50[n].f_30 == 3) {
        if (g_3d50[n].f_30 == 3) {
            k = 30;
            old = m = 0;
        } else if (g_3d50[n].f_30 == 4) {
            k = 31;
            old = m = 0;
        } else if (g_1df8[8][n].f_2f > 2) {
            k = 2;
            if (g_1df8[8][n].f_2f > 4)
                old = SelectObject(g_13dc, g_3b74[(int16_t)(g_1df8[8][n].f_2f - g_0d08) < 1 ? 1
                                                  : g_1df8[8][n].f_2f - g_0d08]);
            else
                old = SelectObject(g_13dc, g_3b74[(int16_t)(g_1df8[8][n].f_2f + g_0d08 - 2) < 1 ? 1
                                                  : g_1df8[8][n].f_2f + g_0d08 - 2]);
            if (g_1df8[8][n].f_6a < g_1e50) {
                g_1df8[8][n].f_2f--;
                g_1df8[8][n].f_6a = g_1e50 + 3000;
            }
            m = 1;
        } else {
            dead = (g_1df8[8][n].f_22 + g_1df8[8][n].f_24) * 2;
            old = 0;
            if (g_1df8[8][n].f_2f < 0) {
                if (rand() % 7 == 2)
                    fn_07_5b68(8, n, 0);
                g_1df8[8][n].f_2f++;
            }
            k = 1;
            m = 0;
        }
        pct = min((int16_t)(g_1df8[8][n].f_1e * 100) / (g_1df8[8][n].f_2c / 2), 100);
        if (g_1df8[8][n].f_1e > g_1df8[8][n].f_2c)
            pct = 0;
        if (pct > 30 && rand() % 200 < pct && rand() % 25 < 2) {
            p = g_1df8[8][n].f_04;
            r = rand() % 4;
            p.x += ((int16_t)(g_1df8[8][n].f_22 / 2 * g_1050[r * 4].x) / 14 - 5) * 8 + g_1df8[8][n].f_20 / 2;
            p.y += ((int16_t)(g_1df8[8][n].f_22 / 2 * g_1050[r * 4].y) / 14 - 5) * 8 + g_1df8[8][n].f_20 / 2;
            fn_07_5d6a(p.x, p.y, 1, g_1050[r * 4].x * 2, g_1050[r * 4].y * 2);
        }
        if (g_3d50[n].f_30 == 3) {
            g_1df8[8][n].f_10 = (g_1df8[8][n].f_22 + g_1df8[8][n].f_24)
                * abs((int16_t)((g_1e68 >> 3 & 1) * 3 - (g_1e68 >> 1 & 3)))
                + g_1df8[8][n].f_24;
        } else if (g_3d50[n].f_30 == 4) {
            g_1df8[8][n].f_10 = (g_1df8[8][n].f_22 + g_1df8[8][n].f_24) * g_1df8[8][n].f_28
                + g_1df8[8][n].f_24;
            g_1df8[8][n].f_12 = (g_1df8[8][n].f_22 + g_1df8[8][n].f_24) * g_1df8[8][n].f_52
                + g_1df8[8][n].f_24;
        } else {
            g_1df8[8][n].f_10 = g_1df8[8][n].f_22 * 2 + g_1df8[8][n].f_24 * 3;
            if (g_1df8[8][n].f_1e > g_1df8[8][n].f_2c)
                g_1df8[8][n].f_10 += g_1df8[8][n].f_22 + g_1df8[8][n].f_24;
        }
        if (g_1df8[8][n].f_1a != 0)
            fn_08_0b76((char)n | 0x800, 3, g_39e8[k], m);
        if (old)
            SelectObject(g_13dc, old);
        if (g_3d50[n].f_00 < g_1e50 && g_3d50[n].f_0a != 0
            && g_1df8[8][n].f_1e < g_1df8[8][n].f_2c) {
            g_1df8[8][n].f_28 = rand() % 4 * 4;
            if (fn_12_6ed8(n)) {
                g_3d50[n].f_00 = (int32_t)(rand() % g_3d50[n].f_0e) + g_3d50[n].f_10 + g_1e50;
                /* dead stores: only their loads and address arithmetic remain */
                if (g_3d50[n].f_08 == 1)
                    dead2 = g_1df8[8][n].f_04.x - 64;
                else
                    dead2 = g_1df8[8][n].f_04.x + g_1df8[8][n].f_22;
                dead2 = g_1df8[8][n].f_04.x;
                fn_12_2db6(8, n, g_1df8[8][n].f_28, g_3d50[n].f_0c, g_3d50[n].f_0a);
            }
        }
    }
    if ((g_1df8[8][n].f_1a != 0 && g_1df8[8][n].f_1c == 0)
        || (g_3d50[n].f_30 == 3 && g_9208 > 1)) {
        g_943a = 8;
        g_943c = n;
        v = fn_08_50aa((char)n | 0x800);
        if (v != -1) {
            if (HIBYTE(v) == g_9328) {
                if (g_1df8[HIBYTE(v)][LOBYTE(v)].f_44 == 0x78) {
                    g_1df8[8][n].f_2f = min(g_1df8[8][n].f_2f + 1, 9);
                    g_1df8[8][n].f_6a = g_1e50 + 3000;
                } else if (g_1df8[HIBYTE(v)][LOBYTE(v)].f_44 == 0xc8 && g_1df8[8][n].f_2f > 0) {
                    g_1df8[8][n].f_2f = -(g_1df8[8][n].f_2f * 5);
                }
            }
            fn_08_5df2(8, n, HIBYTE(v), LOBYTE(v),
                       fn_08_546c(v, &g_1df8[8][n].f_0c, &g_1df8[8][n].f_0e,
                                  g_1df8[8][n].f_20 + 2, g_1df8[8][n].f_44));
        }
    }
}

/* Update every type-6 object: behaviour per class record, timers, drag,
 * collisions and expiry [inferred]. */
/* 12:0000 */
void fn_12_0000(void)
{
    int16_t i;
    int16_t ref;
    int16_t k;
    int16_t r;
    int16_t unused[7];

    for (i = 0; i < g_9406[6]; i++) {
        k = g_6670[i + 4].f_04.x;
        if ((g_2f4c[k].f_26 > g_6670[i + 4].r.right || g_2f4c[k].f_2c == 6) && k != -1
            && g_1df8[6][i].f_18 == 0) {
            switch (g_2f4c[k].f_0e) {
            case 1:
                if (++g_6670[i + 4].f_16 > g_2f4c[k].f_1a) {
                    g_6670[i + 4].f_16 = 0;
                    if (g_2f4c[k].f_1a == -1)
                        g_1df8[6][i].f_28 += 2;
                    g_1df8[6][i].f_28++;
                    if (g_1df8[6][i].f_28 > 15) {
                        g_1df8[6][i].f_28 -= 16;
                        if (g_2f4c[k].f_20 == 2)
                            fn_10_754a(2, 6, i, 1);
                    }
                }
                break;
            case 2:
                break;
            case 4:
                if (g_6670[i + 4].r.right < 50)
                    g_1df8[6][i].f_28 = (int16_t)(g_6670[i + 4].r.right * g_2f4c[k].f_2e) / 50;
                else
                    g_1df8[6][i].f_28 = g_2f4c[k].f_2e - 1;
                break;
            case 5:
                g_1df8[6][i].f_28 = 0;
                break;
            }
            if (g_2f4c[k].f_40 != 0 && !(g_6670[i + 4].r.right & 3))
                fn_04_5514(i);
            if (g_6670[i + 4].r.right % 13 == 0 && g_6670[i + 4].r.right > 8 && g_2f4c[k].f_12 != 1
                && g_2f4c[k].f_12 != 5
                && (g_2f4c[k].f_44 != 0 || g_6670[i + 4].f_00.x == -1 || g_6670[i + 4].r.right == 13))
                fn_12_0586(i, g_6670[i + 4].r.right << 3);
            if (g_6670[i + 4].f_1a == 0 && g_2f4c[k].f_26 / 2 == g_6670[i + 4].r.right)
                g_6670[i + 4].r.right = g_2f4c[k].f_26 - 5;
            if (g_2f4c[k].f_42 == 0 && g_1df8[6][i].f_1a == 0 && g_6670[i + 4].r.right > 20)
                g_6670[i + 4].r.right = g_2f4c[k].f_26;
            if (g_6670[i + 4].f_1a != 0 && (g_2f4c[k].f_12 != 1 || g_6670[i + 4].r.right > g_6670[i + 4].r.bottom))
                fn_12_07c0(i);
            if (g_2f4c[k].f_48 != 0) {
                g_1df8[6][i].f_0c -= g_1df8[6][i].f_0c >> g_2f4c[k].f_48;
                g_1df8[6][i].f_0e -= g_1df8[6][i].f_0e >> g_2f4c[k].f_48;
                if (g_1df8[6][i].f_0c > -10 && g_1df8[6][i].f_0c < 10)
                    g_1df8[6][i].f_0c = 0;
                if (g_1df8[6][i].f_0e > -10 && g_1df8[6][i].f_0e < 10)
                    g_1df8[6][i].f_0e = 0;
            }
            if (g_2f4c[k].f_2c == 5 && (int16_t)(g_2f4c[k].f_26 - 8) < g_6670[i + 4].r.right)
                fn_07_5b68(6, i, 1);
            if (g_2f4c[k].f_1c != 0) {
                if (g_2f4c[k].f_1c == 3) {
                    g_1df8[6][i].f_50 += 4;
                    if (g_1df8[6][i].f_50 > 75)
                        g_1df8[6][i].f_50 = 75;
                }
                fn_12_64aa(i, k);
            }
            fn_08_1b54((char)i | 0x600, 1);
            g_1df8[6][i].f_10 = (g_1df8[6][i].f_22 + g_1df8[6][i].f_24) * g_1df8[6][i].f_28
                + g_1df8[6][i].f_24;
            if (g_1df8[6][i].f_18 == 0) {
                if (g_2f4c[k].f_06 == -1)
                    g_1df8[6][i].f_00 = fn_08_29ea(g_1df8[6][i].f_04);
                else
                    fn_08_0b76((char)i | 0x600, 3, g_39e8[g_2f4c[k].f_04], 0);
            }
            if (g_1df8[6][i].f_1a != 0 && g_6670[i + 4].r.right > 3) {
                g_943a = 6;
                g_943c = i;
                ref = fn_08_50aa((char)i | 0x600);
                if (ref != -1) {
                    r = fn_08_546c(ref, &g_1df8[6][i].f_0c, &g_1df8[6][i].f_0e,
                                   g_1df8[6][i].f_20, g_1df8[6][i].f_44);
                    if (g_1df8[6][i].f_53 != 0 && HIBYTE(ref) == g_9324
                        && g_7090[LOBYTE(ref)].f_0ea == 0)
                        fn_13_16ac(LOBYTE(ref), (char)i | 0x600);
                    else if (g_2f4c[k].f_2c == 6 && HIBYTE(ref) == g_9324
                             && g_2f4c[g_7090[LOBYTE(ref)].f_0b8[g_7090[LOBYTE(ref)].f_018]].f_2c == 6) {
                        g_1df8[6][i].f_53 = 1;
                        fn_13_16ac(LOBYTE(ref), (char)i | 0x600);
                        g_7090[LOBYTE(ref)].f_0ae[g_7090[LOBYTE(ref)].f_018]++;
                    } else
                        fn_08_5df2(6, i, HIBYTE(ref), LOBYTE(ref), r);
                }
            }
            if (g_1df8[6][i].f_18 == 0) {
                if (++g_6670[i + 4].r.right >= g_2f4c[k].f_26) {
                    if (g_2f4c[k].f_2c == 1) {
                        fn_12_274a(6, i);
                        fn_07_2080(6);
                    } else if (g_2f4c[k].f_2c == 4) {
                        fn_07_2e02(6, i);
                        fn_07_2080(6);
                    } else if (g_2f4c[k].f_2c == 5) {
                        fn_12_6a60(6, i);
                    } else if (g_2f4c[k].f_2c == 6) {
                        g_6670[i + 4].f_00.x = g_6670[i + 4].r.left;
                        g_6670[i + 4].f_00.y = g_6670[i + 4].r.top;
                        g_6670[i + 4].f_1a = 1;
                        if (g_1df8[g_6670[i + 4].r.left][g_6670[i + 4].r.top].f_18 != 0) {
                            fn_07_2e02(6, i);
                            fn_07_2080(6);
                        }
                    }
                    if (g_2f4c[k].f_2c != 6)
                        g_1df8[6][i].f_18 = 1;
                }
            }
        } else if (g_1df8[6][i].f_51 != 0) {
            fn_12_129e(6, i);
        }
    }
}

/* Type-8 object n with behaviour 2 (a gun turret [inferred]): aims at its
 * target, fires, pushes nearby objects and particles away, draws itself. */
/* 12:5636 */
void fn_12_5636(int16_t n)
{
    int16_t pad[3];
    int16_t ref2;
    int16_t dx;
    int16_t dy;
    int16_t mode;
    int16_t pct;
    int16_t gap;
    int16_t size;
    int16_t type;
    int16_t idx;
    int16_t ref;
    POINT p;
    HGDIOBJ old;
    int32_t sp;

    if (++g_0d16 > 4)
        g_0d16 = 0;
    gap = g_1df8[8][n].f_24;
    size = g_1df8[8][n].f_22;
    type = 8;
    idx = n;
    sp = 1;
    if ((DWORD)g_6988 < g_1e50 || (g_3d50[n].f_26 != -1
        && g_1df8[g_3d50[n].f_26][g_3d50[n].f_28].f_18 != 0)) {
        g_949a = 1;
        ref = fn_12_6706(8, n);
        g_3d50[n].f_26 = HIBYTE(ref);
        g_3d50[n].f_28 = LOBYTE(ref);
        if (ref != -1) {
            g_3d50[n].f_2c = fn_08_285a(&dx, &dy, g_1df8[type][idx].f_04,
                                       g_1df8[g_3d50[n].f_26][g_3d50[n].f_28].f_04);
        } else {
            g_3d50[n].f_26 = -1;
            g_3d50[n].f_2c = 20000;
        }
        if (g_3d50[n].f_18) {
            if (rand() % 3 == 0)
                g_3d50[n].f_1a = rand() % 4 + 3;
        } else
            g_3d50[n].f_1a = 0;
    }
    if (g_1df8[8][n].f_54 == 0) {
        fn_08_1d54((OBJREF){n, 8}, 0x1e);
        fn_08_1b54((char)n | 0x800, 1);
    }
    if (g_1df8[8][n].f_1a != 0 || g_9320 == 6) {
        pct = min((int16_t)(g_1df8[8][n].f_1e * 100) / (g_1df8[8][n].f_2c / 2), 100);
        if (pct > 60 && rand() % 200 < pct && rand() % 20 == 3 && g_1df8[8][n].f_1a)
            fn_07_5b68(8, n, 1);
        if (g_1df8[8][n].f_2c / 2 < g_1df8[8][n].f_1e || g_3d50[n].f_04 > g_1e50
            || g_3d50[n].f_0a == -1 || g_3d50[n].f_0a == -3) {
            int32_t ax_;
            int32_t ay_;
            int32_t f;
            int16_t i;
            int16_t d;

            if (g_3d50[n].f_0a == -1 || g_3d50[n].f_0a == -3)
                sp = g_3d50[n].f_0a + 2L;
            else
                sp = 1;
            g_1df8[8][n].f_28 += (int16_t)sp;
            if (g_1df8[8][n].f_28 < 0)
                g_1df8[8][n].f_28 = 15;
            else if (g_1df8[8][n].f_28 > 15)
                g_1df8[8][n].f_28 = 0;
            if (g_3d50[n].f_0a == -1 || g_3d50[n].f_0a == -3) {
                for (i = 0; i < g_9146; i++) {
                    if (g_1df8[g_507c[i]][g_50e0[i]].f_54 == 0
                        && (d = fn_08_285a(&dx, &dy, g_1df8[8][n].f_04,
                                           g_1df8[g_507c[i]][g_50e0[i]].f_04)) < 400) {
                        d = max(d, 70);
                        f = sp * 2500 / d / ((int16_t)(g_1df8[g_507c[i]][g_50e0[i]].f_44 + 100) / 100);
                        if (sp < 0)
                            f = f * 2 / 3;
                        ax_ = dx * f / d;
                        ay_ = dy * f / d;
                        g_1df8[g_507c[i]][g_50e0[i]].f_0c += (int16_t)ax_;
                        g_1df8[g_507c[i]][g_50e0[i]].f_0e += (int16_t)ay_;
                    }
                }
                for (i = 0; i < (int16_t)(g_0598 + g_0594); i++) {
                    if (g_6098[i].z[1][5] > 0 && g_6098[i].z[1][4] > g_6098[i].z[1][5]) {
                        p.x = g_6098[i].f_30[0][0];
                        p.y = g_6098[i].f_48[0][0];
                        if ((d = fn_08_285a(&dx, &dy, g_1df8[8][n].f_04, p)) < 400) {
                            d = max(d, 40);
                            f = (int16_t)(max((int16_t)(g_9334 * 150), 3000) + 1500) * sp / d / 2;
                            ax_ = f * dx / d;
                            ay_ = f * dy / d;
                            g_6098[i].z[1][2] += (int16_t)ax_;
                            g_6098[i].z[1][3] += (int16_t)ay_;
                            g_6098[i].f_82 = 1;
                        }
                    }
                }
                for (i = 0; i < g_94a0; i++) {
                    if (g_6938[i].f_0c > 0 && g_6938[i].f_0c < g_6938[i].f_0e) {
                        if ((d = fn_08_285a(&dx, &dy, g_1df8[8][n].f_04, g_6938[i].pos)) < 1000) {
                            d = max(d, 40);
                            f = ((int32_t)(int16_t)(1000 - d) * (int16_t)(1000 - d)
                                 / ((12 - (int32_t)min(g_9334, 10)) * 50000L) + 1) * sp;
                            ax_ = f * dx / d;
                            ay_ = f * dy / d;
                            g_6938[i].f_08 += (int16_t)ax_;
                            g_6938[i].f_0a += (int16_t)ay_;
                        }
                        if (g_949e) {
                            g_6938[i].f_0c++;
                            g_6938[i].pos.x += g_6938[i].f_08;
                            if (g_6938[i].pos.x > (int16_t)((LO16(g_05a0)) * 8))
                                g_6938[i].pos.x = 0;
                            else if (g_6938[i].pos.x < 0)
                                g_6938[i].pos.x = (LO16(g_05a0)) * 8;
                            g_6938[i].pos.y += g_6938[i].f_0a;
                            if (g_6938[i].pos.y > (int16_t)(HI16(g_05a0) * 8))
                                g_6938[i].pos.y = 0;
                            else if (g_6938[i].pos.y < 0)
                                g_6938[i].pos.y = HI16(g_05a0) * 8;
                            p = fn_08_29ea(g_6938[i].pos);
                            PatBlt(g_13dc, g_6938[i].scr.x, g_6938[i].scr.y, SC(2), SC(2),
                                   BLACKNESS);
                            g_6938[i].scr = p;
                            if (p.x < 0 || p.x > LO16(g_90ea) || p.y < 0 || p.y > HI16(g_90ea))
                                g_6938[i].f_0c = 0;
                            else if (g_6938[i].f_0c < g_6938[i].f_0e) {
                                old = SelectObject(g_13dc, (g_3b4c + 10)[g_6938[i].f_0c % 5]);
                                PatBlt(g_13dc, g_6938[i].scr.x, g_6938[i].scr.y, SC(2), SC(2),
                                       PATCOPY);
                                SelectObject(g_13dc, old);
                            }
                        }
                    } else {
                        g_6938[i].f_0c = 1;
                        p.x = rand() % LO16(g_90ea);
                        p.y = rand() % HI16(g_90ea);
                        g_6938[i].f_0e = rand() % 30 + 90;
                        if (rand() % 10 == 2)
                            g_6938[i].f_0e += rand() % 100 + 20;
                        g_6938[i].pos = fn_08_2bbe(p);
                        g_6938[i].f_08 = rand() % 12 - 6;
                        g_6938[i].f_0a = rand() % 12 - 6;
                    }
                }
                g_949e = 0;
            }
        } else {
            int16_t lim;
            POINT dp;
            POINT v;

            if (g_3d50[n].f_26 > -1 && g_666c < g_1e68) {
                g_949c = 1;
                if (g_3d50[n].f_2c > 250 && g_1df8[8][n].f_54 == 0)
                    mode = 5;
                else
                    mode = 2;
                if (g_9320 == 6 && g_9eb5 == 0)
                    g_1df8[8][n].f_28 = fn_12_6902(n, g_3d50[n].f_28);
                else
                    g_1df8[8][n].f_28 = fn_12_67e8(g_1df8[8][n].f_04,
                                                  g_1df8[g_3d50[n].f_26][g_3d50[n].f_28].f_04,
                                                  mode, g_1df8[8][n].f_28);
                if (g_9320 == 6) {
                    if (g_9eb5)
                        lim = 0;
                    else {
                        int32_t dist;
                        int32_t t;

                        dp.x = g_1df8[8][n].f_04.x - g_1df8[14][g_3d50[n].f_28].f_04.x;
                        dp.y = g_1df8[8][n].f_04.y - g_1df8[14][g_3d50[n].f_28].f_04.y;
                        v.x = g_1df8[14][g_3d50[n].f_28].f_0c;
                        v.y = g_1df8[14][g_3d50[n].f_28].f_0e;
                        dist = fn_08_35d0(dp.x, dp.y);
                        t = ((int32_t)v.x * dp.x + (int32_t)v.y * dp.y) / dist;
                        lim = t * 3 / 2 + 300;
                    }
                } else
                    lim = 200;
                if (g_3d50[n].f_2c < lim || mode == 5) {
                    if (g_3d50[n].f_18 == 0 && (rand() & 1) && g_3d50[n].f_0a == 1)
                        spawn_gun_shot(8, n);
                    else if (((rand() & 3) == 0
                              || g_3d50[n].f_18 && g_3d50[n].f_1a && rand() % 3 < 2)
                             && g_3d50[n].f_0a != 1) {
                        if (mode == 5) {
                            fn_12_6dea(g_3d50[n].f_0a, 8, n, 16);
                            g_1df8[8][n].f_0c -= (int16_t)(g_1050[g_1df8[8][n].f_28].x << 8)
                                / g_1df8[8][n].f_44;
                            g_1df8[8][n].f_0e -= (int16_t)(g_1050[g_1df8[8][n].f_28].y << 8)
                                / g_1df8[8][n].f_44;
                        } else if (fn_12_6ed8(n)) {
                            fn_12_6dea(g_3d50[n].f_0a, 8, n, lim / 16);
                            g_1df8[8][n].f_0c -= (int16_t)(g_1050[g_1df8[8][n].f_28].x << 7)
                                / g_1df8[8][n].f_44;
                            g_1df8[8][n].f_0e -= (int16_t)(g_1050[g_1df8[8][n].f_28].y << 7)
                                / g_1df8[8][n].f_44;
                        }
                    }
                }
                if (g_0d16 == 0)
                    g_3d50[n].f_2c = fn_08_285a(&dx, &dy, g_1df8[8][n].f_04,
                                               g_1df8[g_3d50[n].f_26][g_3d50[n].f_28].f_04);
            } else if (g_3d50[n].f_26 > -1 && g_3d50[n].f_2c < 200 && g_3d50[n].f_1a
                       && rand() % 3 < 2 && fn_12_6ed8(n)) {
                spawn_gun_shot(8, n);
                g_3d50[n].f_1a--;
            }
        }
        g_1df8[8][n].f_10 = g_1df8[8][n].f_28 * (size + gap) + gap;
        fn_08_0b76((char)n | 0x800, 3, g_39e8[g_3d50[n].f_1e], 0);
    }
    if ((g_1df8[8][n].f_1a && g_1df8[8][n].f_1c == 0) || g_9320 == 6) {
        g_943a = 8;
        g_943c = n;
        ref2 = fn_08_50aa((char)n | 0x800);
        if (ref2 != -1)
            fn_08_5df2(8, n, HIBYTE(ref2), LOBYTE(ref2),
                       fn_08_546c(ref2, &g_1df8[8][n].f_0c, &g_1df8[8][n].f_0e,
                                  g_1df8[8][n].f_20 + 2, g_1df8[8][n].f_44));
    }
}
