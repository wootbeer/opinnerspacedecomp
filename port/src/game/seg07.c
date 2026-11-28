/* INSPACE.EXE segment 7 (selector 1030). */
#include "game.h"

/* Adds cracks to a window pane and redraws it [inferred]. */
/* 7:233c */
int16_t fn_07_233c(int16_t unused, int16_t n, int16_t amount)
{
    int16_t size;
    int16_t gap;
    int16_t u;
    int16_t q;
    HDC memdc;
    HGDIOBJ old;
    HBITMAP bmp;

    if (g_57a8[n].f_00 == 0 && object_records[0][n].f_2f != -100 && object_records[0][n].f_2f != -2) {
        object_records[0][n].f_1e = min((int16_t)(amount * 3 + object_records[0][n].f_1e), 211);
        g_69f4[g_94a2].f_1d2[n] = object_records[0][n].f_1e;
        gap = object_records[0][n].f_24;
        size = object_records[0][n].f_22;
        if (object_records[0][n].f_1e > 0 && object_records[0][n].f_2f >= 0) {
            memdc = CreateCompatibleDC(main_dc);
            bmp = fn_10_6d38("CRACKS");
            if (amount)
                bmp = fn_10_6308(-1, -1, bmp, -1);
            else {
                gap = 6;
                size = 32;
            }
            old = SelectObject(memdc, bmp);
            q = object_records[0][n].f_1e / 70;
            BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
                   memdc, (q + 3) * size, 0, MERGEPAINT);
            BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
                   memdc, q * size, 0, SRCAND);
            SelectObject(memdc, old);
            DeleteDC(memdc);
            DeleteObject(bmp);
            if (amount && g_57a8[n].f_02 == 0)
                fn_10_754a(0x12, 0, n, 1);
        }
        if (amount && (object_records[0][n].f_1e > 208 || object_records[0][n].f_2f < 0)) {
            fn_07_26c4(0, n);
            return 1;
        }
    }
    fn_07_65aa(0, n);
    return 0;
}

/* 7:2512 */
void fn_07_2512(int16_t n, int16_t m)
{
    int16_t size;
    int16_t gap;
    HDC memdc;
    HGDIOBJ old;
    HBITMAP bmp;
    HBITMAP bmp2;

    if (g_57a8[n].f_00 == 0) {
        gap = object_records[0][n].f_24;
        size = object_records[0][n].f_22;
        memdc = CreateCompatibleDC(main_dc);
        old = SelectObject(memdc, bmp2 = fn_10_6ec6(bmp = fn_10_6308(-1, -1,
                                    fn_10_6c02(0x168, 0, -1), -1)));
        BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
               memdc, size * m, 0, SRCAND);
        SelectObject(memdc, bmp);
        BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
               memdc, size * m, 0, SRCPAINT);
        SelectObject(memdc, old);
        DeleteDC(memdc);
        DeleteObject(bmp);
        DeleteObject(bmp2);
        (g_69f4[g_94a2].f_1c0 + 8)[n] = m + 1;
        if (m == 0)
            object_records[0][n].f_53 = 2;
    }
    fn_07_65aa(0, n);
}

/* 7:2652 */
int16_t fn_07_2652(int16_t type, int16_t idx, int16_t amount)
{
    if (type == 15)
        return 0;
    if (object_records[type][idx].f_1e > object_records[type][idx].f_2c && type != 9)
        return 0;
    object_records[type][idx].f_1e += amount;
    if (object_records[type][idx].f_1e > object_records[type][idx].f_2c) {
        object_records[type][idx].f_66(type, idx);
        return 1;
    }
    return 0;
}

/* 7:26c4 */
void fn_07_26c4(int16_t unused, int16_t n)
{
    object_records[0][n].f_1e = -1;
    g_69f4[g_94a2].f_1d2[n] = object_records[0][n].f_1e;
    fn_10_754a(0x1f, 0, n, 1);
    fn_07_2768(n);
    object_records[0][n].f_18 = 1;
    fn_07_65aa(0, n);
    PatBlt(main_dc, object_records[0][n].f_00.x, object_records[0][n].f_00.y,
           (32 << g_9156) >> 1, (32 << g_9156) >> 1, BLACKNESS);
    fn_07_5ae8(n, 0);
}

/* Starts an explosion/flash on an object [inferred]. */
/* 7:2e02 */
void fn_07_2e02(int16_t type, int16_t idx)
{
    int16_t u;
    int16_t i;
    int16_t j;
    int16_t u2;

    if (object_records[type][idx].f_18 == 0) {
        object_records[type][idx].f_18 = 1;
        PatBlt(main_dc, object_records[type][idx].f_00.x, object_records[type][idx].f_00.y,
               object_records[type][idx].f_22, object_records[type][idx].f_22, BLACKNESS);
        for (i = 0; i < 4; i++) {
            if (g_1e90[i].f_00 == -1 || g_1e90[i].f_0a <= 5) {
                if (g_5e98[i]) {
                    SelectObject(g_5e98[i], g_5ea0[i]);
                    DeleteDC(g_5e98[i]);
                    g_5e98[i] = 0;
                }
                if (type == 1) {
                    g_5e98[i] = CreateCompatibleDC(main_dc);
                    g_5ea0[i] = SelectObject(g_5e98[i], g_4e94[idx]);
                    fn_10_754a(0x1a, type, idx, 1);
                } else if (type == 8) {
                    g_5e98[i] = g_39e8[g_3d50[idx].f_1e];
                    fn_10_754a(0x1a, type, idx, 1);
                } else if (type == 6) {
                    g_5e98[i] = g_39e8[g_2f4c[g_6670[idx + 4].f_04.x].f_04];
                    if (g_2f4c[g_6670[idx + 4].f_04.x].f_2c == 6)
                        fn_10_754a(0x1a, type, idx, 1);
                    else
                        fn_10_754a(0x1f, type, idx, 1);
                } else if (type == 4) {
                    g_5e98[i] = g_39e8[4];
                    fn_10_754a(0x1f, type, idx, 1);
                }
                if (g_1e90[i].f_00 > -1)
                    for (j = 4; j < 45; j++)
                        if (g_1e90[j].f_00 == -1) {
                            g_1e90[j].f_00 = g_1e90[i].f_00;
                            g_1e90[j].f_02 = g_1e90[i].f_02;
                            g_1e90[j].f_06 = g_1e90[i].f_06;
                            g_1e90[j].f_08 = g_1e90[i].f_08;
                            g_1e90[j].f_10 = g_1e90[i].f_10;
                            g_1e90[j].f_0a = g_1e90[i].f_0a;
                            g_5170[j] = g_5170[i];
                            VIEWP(int32_t *, g_5224[0], 0)[j] = VIEWP(int32_t *, g_5224[0], 0)[i];
                            g_1e90[j].f_0c = g_1e90[i].f_0c;
                            g_1e90[j].f_0e = g_1e90[i].f_0e;
                            break;
                        }
                g_1e90[i].f_00 = 1;
                g_1e90[i].f_02 = 20;
                g_9430++;
                g_1e90[i].f_0a = 6;
                g_1e90[i].f_0c = object_records[type][idx].f_22 / 5;
                if (i > g_9208)
                    g_1e90[i].f_04 = 2;
                else
                    g_1e90[i].f_04 = 1;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = idx;
                g_5170[i] = object_records[type][idx].f_00;
                VIEWP(int32_t *, g_5224[0], 0)[i] = VIEW(int32_t, object_records[type][idx].f_04, 0);
                break;
            }
        }
    }
    if (type == 1)
        fn_07_65aa(0, g_6038[idx]);
}

/* 7:3294 */
void fn_07_3294(int16_t n)
{
    fn_08_1d54((OBJREF){n, 0}, 0x1e);
    if (!object_records[0][n].f_54)
        fn_08_1b54((char)n, 3);
}

/* 7:309c */
void fn_07_309c(void)
{
    int16_t i;
    int16_t u1;
    int16_t r;
    int16_t u2;
    int16_t size;
    int16_t gap;
    int16_t u3[6];
    int16_t flag;
    HDC dc;

    if (g_92e8)
        return;
    size = object_records[0]->f_22;
    gap = object_records[0]->f_24;
    for (i = 0; i < g_91fa; i++) {
        if (object_records[0][i].f_18 != 0)
            continue;
        flag = 0;
        if (g_57a8[i].f_00 != 0) {
            fn_07_4d86(i);
            if (g_57a8[i].f_00 < 7) {
                g_57a8[i].f_00 = 0;
                flag = 1;
            }
        }
        if (object_records[0][i].f_1a != 0) {
            if (g_57a8[i].f_02 == 0) {
                object_records[0][i].f_10 = (gap + size) * i + gap;
                dc = g_3a02;
            } else {
                dc = g_3a04[i];
                object_records[0][i].f_10 = (g_57a8[i].f_02 / 2 - 1) * (gap + size) + gap;
            }
            fn_08_1d54((OBJREF){i, 0}, 0x28);
            if (!object_records[0][i].f_54)
                fn_08_1b54((char)i, 1);
            fn_08_0b76((char)i, 1, dc, 0);
            if (object_records[0][i].f_1a != 0 && object_records[0][i].f_1c == 0) {
                g_943a = 0;
                g_943c = i;
                r = fn_08_50aa((char)i);
                if (r != -1)
                    fn_07_4a38(HIBYTE(r), LOBYTE(r), i);
            }
        } else if (g_9142 % 3 == 0)
            fn_07_3294(i);
        if (g_9142 % 30 == 0 && object_records[0][i].f_2f < 0) {
            object_records[0][i].f_2f++;
            if (object_records[0][i].f_2f == 0)
                object_records[0][i].f_53 = 1;
            if (object_records[0][i].f_2f == -2)
                fn_07_5660(i);
        }
        if (g_57a8[i].f_02 != 0) {
            if (g_57a8[i].f_02 > 10)
                g_57a8[i].f_02 = 1;
            g_57a8[i].f_02++;
        }
        if (flag)
            fn_07_4ffe(i);
    }
}

/* 7:32d0 */
void fn_07_32d0(void)
{
    int16_t i;
    int16_t u1;
    int16_t r;
    int16_t size;
    int16_t u2[6];
    HGDIOBJ old;

    size = (6 << g_9156) >> 1;
    for (i = 0; i < g_9406[1]; i++) {
        if (object_records[1][i].f_18 == 0) {
            if (object_records[1][i].f_1a != 0 && g_4e94[i] != 0) {
                old = SelectObject(g_9288, g_4e94[i]);
                object_records[1][i].f_10 = size;
                fn_08_1d54((OBJREF){i, 1}, 0x28);
                fn_08_1b54((char)i | 0x100, 1);
                fn_08_0b76((char)i | 0x100, 3, g_9288, 0);
                SelectObject(g_9288, old);
                if (object_records[1][i].f_1c == 0) {
                    g_943a = 1;
                    g_943c = i;
                    r = fn_08_50aa((char)i | 0x100);
                    if (r != -1)
                        fn_08_5df2(1, i, HIBYTE(r), LOBYTE(r),
                                   fn_08_546c(r, &object_records[1][i].f_0c, &object_records[1][i].f_0e,
                                              object_records[1][i].f_20 + 2, object_records[1][i].f_44));
                }
            } else if (g_9142 % 3 == 0)
                fn_07_3400(i);
        }
    }
}

/* 7:3400 */
void fn_07_3400(int16_t n)
{
    fn_08_1d54((OBJREF){n, 1}, 0x28);
    fn_08_1b54((char)n | 0x100, 3);
}

/* Breaks an object into 5x5 flying pieces with one of 8 motion
 * patterns [inferred]. */
/* 7:342e */
void fn_07_342e(int16_t n, int16_t type, int16_t idx)
{
    int16_t i;
    int16_t j;
    int16_t u;
    int16_t u2;

    u = object_records[type][idx].f_22 / 5;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++) {
            g_2414[n][i][j].s.x = u * j * 8 + object_records[type][idx].f_04.x;
            g_2414[n][i][j].s.y = u * i * 8 + object_records[type][idx].f_04.y;
            g_2414[n][i][j].f_0c = object_records[type][idx].f_0c / 10 + (j - 2) * 8;
            g_2414[n][i][j].f_0e = object_records[type][idx].f_0e / 10 + (2 - i) * 7;
            g_2414[n][i][j].f_10 = (i + 5) * 2 - j * 7;
            g_2414[n][i][j].f_12 = (-1 - j) * 4 + i * 6;
            switch (rand() % 8) {
            case 0:
                g_2414[n][i][j].f_10 = (i + 5) * 2 - j * 7;
                g_2414[n][i][j].f_12 = (-1 - j) * 4 + i * 6;
                break;
            case 1:
                g_2414[n][i][j].f_10 = (2 - j) * 7 + (2 - i) * (i - 2) * 2;
                g_2414[n][i][j].f_12 = (2 - j) * (j - 2) * 4 + (i - 2) * 6;
                break;
            case 2:
                g_2414[n][i][j].f_10 = (2 - j) * 7 + (2 - i) * (i - 2) * 2;
                g_2414[n][i][j].f_12 = (j - 2) * (j - 2) * 4 + (2 - i) * 6;
                break;
            case 3:
                g_2414[n][i][j].f_10 = -(2 - i) * 2 + (2 - j) * (5 - i) * 7;
                g_2414[n][i][j].f_12 = -(2 - i) * (j - 5) * 6 + (j - 2) * 4;
                break;
            case 4:
                g_2414[n][i][j].f_10 = (2 - j) * (i - 2);
                g_2414[n][i][j].f_12 = (j - 2) * (i - 2) * 7 + (2 - j) * (2 - i) * 2;
                break;
            case 5:
                g_2414[n][i][j].f_10 = ((2 - i) * (2 - i) * (i - 2) + j - 2) * 6;
                g_2414[n][i][j].f_12 = (2 - j) * (j - 2) * 2 + (i - 2) * 5;
                break;
            case 6:
                g_2414[n][i][j].f_10 = ((i - 2) * (i - 2) * (2 - i)
                                       + (j - 2) * (j - 2) * (j - 2)) * 6;
                g_2414[n][i][j].f_12 = (2 - j) * (j - 2) * 2 + (i - 2) * (i - 2) * i * 7;
                break;
            case 7:
                g_2414[n][i][j].f_10 = j * 7 - i * 3 - 8;
                g_2414[n][i][j].f_12 = (i - 2) * (i - 2) * (i - 2) * 6;
                break;
            }
        }
}

/* Moves the four sparks of each burst along curved paths [inferred]. */
/* 7:375a */
void fn_07_375a(void)
{
    int16_t i;
    int16_t j;
    int16_t t;
    int16_t k;                      /* kept in a register, never stored */
    int16_t u2;
    int16_t n;
    int16_t m;

    if (g_9510 >= 50)
        return;
    n = g_9208 * 2 + 3;
    m = (g_9208 + 7) * 4;
    for (i = 0; i < n; i++) {
        if (n - 1 > g_9510 && i == g_9510)
            for (j = 0; j < 4; j++) {
                g_5b28[g_9510][j].s = object_records[g_9512][g_9514].f_04;
                g_5b28[g_9510][j].s.x
                    += g_7ba0[g_7090[g_9514].f_04e][object_records[g_9512][g_9514].f_28].x * 8;
                g_5b28[g_9510][j].s.y
                    += g_7ba0[g_7090[g_9514].f_04e][object_records[g_9512][g_9514].f_28].y * 8;
                g_5b28[g_9510][j].vx = -(g_1050[object_records[g_9512][g_9514].f_28].x * 4);
                g_5b28[g_9510][j].vy = -(g_1050[object_records[g_9512][g_9514].f_28].y * 4);
                g_5b28[g_9510][j].f_0c = 0;
            }
        if (m + n + 1 > g_9510 && i <= g_9510) {
            for (j = 0; j < 4; j++) {
                if (g_5b28[i][j].f_0c < m && g_5b28[i][j].f_0c > 0) {
                    fn_08_083e(i, j);
                    k = g_7090[g_9514].f_0e3 * 10 + (g_5b28[i][j].f_0c >> 2);
                    SelectObject(main_dc, g_3b4c[k]);
                    PatBlt(main_dc, g_5b28[i][j].p.x, g_5b28[i][j].p.y, 2, 2, PATCOPY);
                    PatBlt(main_dc, g_5b28[i][j].q.x, g_5b28[i][j].q.y, 2, 2, BLACKNESS);
                }
                g_5b28[i][j].s.x += g_5b28[i][j].vx;
                g_5b28[i][j].s.y += g_5b28[i][j].vy;
                g_5b28[i][j].f_0c++;
                if (g_5b28[i][j].f_0c >= m - 1)
                    PatBlt(main_dc, g_5b28[i][j].p.x, g_5b28[i][j].p.y, 2, 2, BLACKNESS);
            }
            if (g_5b28[i][0].f_0c < m / 3) {
                t = g_5b28[i][0].vx;
                g_5b28[i][0].vx -= g_5b28[i][0].vy >> 2;
                g_5b28[i][0].vy += t >> 2;
                t = g_5b28[i][1].vx;
                g_5b28[i][1].vx -= g_5b28[i][1].vy >> 3;
                g_5b28[i][1].vy += t >> 3;
                t = g_5b28[i][2].vx;
                g_5b28[i][2].vx += g_5b28[i][2].vy >> 3;
                g_5b28[i][2].vy -= t >> 3;
                t = g_5b28[i][3].vx;
                g_5b28[i][3].vx += g_5b28[i][3].vy >> 2;
                g_5b28[i][3].vy -= t >> 2;
            } else {
                t = g_5b28[i][0].vx;
                g_5b28[i][0].vx -= g_5b28[i][0].vy;
                g_5b28[i][0].vy += t;
                t = g_5b28[i][1].vx;
                g_5b28[i][1].vx -= g_5b28[i][1].vy >> 1;
                g_5b28[i][1].vy += t >> 1;
                t = g_5b28[i][2].vx;
                g_5b28[i][2].vx += g_5b28[i][2].vy >> 1;
                g_5b28[i][2].vy -= t >> 1;
                t = g_5b28[i][3].vx;
                g_5b28[i][3].vx += g_5b28[i][3].vy;
                g_5b28[i][3].vy -= t;
            }
        }
    }
    if (m + n == ++g_9510)
        g_9512 = -1;
}

/* 7:3a42 */
void fn_07_3a42(int16_t n)
{
    int16_t size;
    int16_t gap;

    size = object_records[0]->f_22;
    gap = object_records[0]->f_24;
    object_records[0][n].f_51 -= LO8(g_8ffe);
    if (object_records[0][n].f_51 < 0)
        object_records[0][n].f_51 = 0;
    if (object_records[0][n].f_1a == 0 && !fn_13_59e8(0, n))
        return;
    SetStretchBltMode(g_3a02, COLORONCOLOR);
    StretchBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
               g_3a02, (gap + size) * n + gap - 2, gap - 2, size + 4, size + 4, SRCCOPY);
    BitBlt(main_dc, object_records[0][n].f_00.x, object_records[0][n].f_00.y, size, size,
           g_3a02, (gap + size) * n + gap, gap, SRCCOPY);
    if (object_records[0][n].f_48 == main_ship && g_9208 > 1 && (object_records[0][n].f_51 & 1))
        fn_07_1208();
    if (object_records[0][n].f_51 < 1) {
        PatBlt(main_dc, object_records[0][n].f_00.x, object_records[0][n].f_00.y, size, size, BLACKNESS);
        PatBlt(g_3a02, (gap + size) * n + gap, gap, size, size, BLACKNESS);
        fn_07_65aa(0, n);
        fn_07_2080(0);
    }
}

/* Updates the objects of type g_934a: animation frame, glow and hits [inferred]. */
/* 7:3bae */
void fn_07_3bae(void)
{
    int16_t i;
    int16_t r;
    int16_t k;
    int16_t u[10];
    HGDIOBJ old;
    int16_t flag;
    int16_t u2[2];
    int16_t d;

    for (i = 0; i < g_9406[g_934a]; i++) {
        if (object_records[g_934a][i].f_18 == 0) {
            if (object_records[g_934a][i].f_1a != 0) {
                if (object_records[g_934a][i].f_2f > 0) {
                    if (subgame_active)
                        k = 0x24;
                    else
                        k = 6;
                    old = SelectObject(main_dc, g_3b74[object_records[g_934a][i].f_2f]);
                    flag = 1;
                    if (object_records[g_934a][i].f_6a < now_ms) {
                        object_records[g_934a][i].f_2f--;
                        object_records[g_934a][i].f_6a = now_ms + 3000;
                    }
                } else {
                    if (object_records[g_934a][i].f_2f < 0) {
                        if (rand() % 7 == 2)
                            fn_07_5b68(g_934a, i, 0);
                        object_records[g_934a][i].f_2f++;
                    }
                    if (subgame_active)
                        k = 0x23;
                    else
                        k = 7;
                    flag = 0;
                }
                if (!subgame_active && object_records[g_934a][i].f_22 < (30 << g_9156 >> 1))
                    k += 2;
                if (subgame_active && (g_9156 == 0 && object_records[g_934a][i].f_22 < 12
                               || g_9156 == 1 && object_records[g_934a][i].f_22 < 30))
                    k += 2;
                fn_08_1d54((OBJREF){i, g_934a}, 0x28);
                fn_08_1b54((char)i | g_934a << 8, 1);
                object_records[g_934a][i].f_28 = object_records[g_934a][i].f_26 / 100;
                object_records[g_934a][i].f_10 = (object_records[g_934a][i].f_22 + object_records[g_934a][i].f_24)
                    * (object_records[g_934a][i].f_26 / 100) + object_records[g_934a][i].f_24;
                fn_08_0b76((char)i | g_934a << 8, 1, g_39e8[k], flag);
                if (object_records[g_934a][i].f_2f > 0)
                    SelectObject(main_dc, old);
                d = fn_09_88ba(object_records[g_934a][i].f_0c) + fn_09_88ba(object_records[g_934a][i].f_0e);
                if (object_records[g_934a][i].f_0c < 0)
                    d = -d;
                object_records[g_934a][i].f_26 += d;
                if (object_records[g_934a][i].f_26 > 0x707)
                    object_records[g_934a][i].f_26 = 0;
                if (object_records[g_934a][i].f_26 < 0)
                    object_records[g_934a][i].f_26 = 0x707;
            } else if (g_9142 % 3 == 0) {
                fn_08_1d54((OBJREF){i, g_934a}, 0x28);
                fn_08_1b54((char)i | g_934a << 8, 3);
                if (object_records[g_934a][i].f_2f > 0) {
                    if (object_records[g_934a][i].f_6a < now_ms) {
                        object_records[g_934a][i].f_2f--;
                        object_records[g_934a][i].f_6a = now_ms + 3000;
                    }
                } else if (object_records[g_934a][i].f_2f < 0)
                    object_records[g_934a][i].f_2f++;
            }
            if (object_records[g_934a][i].f_1a != 0 && object_records[g_934a][i].f_1c == 0) {
                g_943c = i;
                g_943a = g_934a;
                r = fn_08_50aa((char)i | g_934a << 8);
                if (r != -1) {
                    if (HIBYTE(r) == g_9328) {
                        if (object_records[HIBYTE(r)][LOBYTE(r)].f_44 == 120) {
                            object_records[g_934a][i].f_2f = min(object_records[g_934a][i].f_2f + 1, 9);
                            object_records[g_934a][i].f_6a = now_ms + 5000;
                        } else if (object_records[HIBYTE(r)][LOBYTE(r)].f_44 == 200
                                   && object_records[g_934a][i].f_2f > 0) {
                            object_records[g_934a][i].f_2f = -(object_records[g_934a][i].f_2f * 5);
                            fn_07_5b68(g_934a, i, 0);
                        }
                    }
                    g_9454 = object_records[g_934a][i].f_2f;
                    fn_08_5df2(g_934a, i, HIBYTE(r), LOBYTE(r),
                               fn_08_546c(r, &object_records[g_934a][i].f_0c, &object_records[g_934a][i].f_0e,
                                          object_records[g_934a][i].f_20 + 2, object_records[g_934a][i].f_44));
                    g_9454 = 0;
                }
            }
        }
    }
}

/* Builds the five-frame strip of a window pane in g_3a04[n] [inferred]. */
/* 7:477e */
void fn_07_477e(int16_t n)
{
    int16_t i;
    int16_t size;
    int16_t gap;
    int16_t bmp2;
    HGDIOBJ old2;
    int16_t bmp;
    HGDIOBJ old1;
    HDC dc2;
    HDC dc1;
    HPALETTE pal;

    fn_10_754a(0x6a, 0, n, 1);
    size = object_records[0]->f_22;
    gap = object_records[0]->f_24;
    g_57a8[n].f_00 = 0x59;
    bmp = fn_10_6308(-1, -1, fn_10_6c02(0xe6, 0, -1), -1);
    bmp2 = fn_10_6ec6(bmp);
    dc1 = CreateCompatibleDC(main_dc);
    old1 = SelectObject(dc1, bmp);
    if (game_palette)
        pal = SelectPalette(dc1, game_palette, 0);
    dc2 = CreateCompatibleDC(main_dc);
    old2 = SelectObject(dc2, bmp2);
    if (!g_3a04[n]) {
        g_3a04[n] = CreateCompatibleDC(main_dc);
        g_3aec[n] = CreateCompatibleBitmap(main_dc, size * 5 + gap * 6, gap * 2 + size);
        g_3990[n] = SelectObject(g_3a04[n], g_3aec[n]);
        if (game_palette)
            g_3a78[n] = SelectPalette(g_3a04[n], game_palette, 0);
    }
    PatBlt(g_3a04[n], 0, 0, size * 5 + gap * 6, gap * 2 + size, BLACKNESS);
    for (i = 0; i < 5; i++) {
        BitBlt(g_3a04[n], (gap + size) * i + gap, (12 << g_9156 >> 1) + gap, size,
               size - (12 << g_9156 >> 1), g_3a02, (gap + size) * n + gap,
               (12 << g_9156 >> 1) + gap, SRCCOPY);
        BitBlt(g_3a04[n], (gap + size) * i + gap, gap, size, size, dc2, size * i, 0, SRCAND);
        BitBlt(g_3a04[n], (gap + size) * i + gap, gap, size, size, dc1, size * i, 0, SRCPAINT);
    }
    SelectObject(dc1, old1);
    SelectObject(dc2, old2);
    if (pal)
        SelectPalette(dc1, pal, 0);
    DeleteDC(dc1);
    DeleteDC(dc2);
    DeleteObject(bmp2);
    DeleteObject(bmp);
}

/* 7:49b6 */
void fn_07_49b6(void)
{
    int16_t i;

    for (i = 0; i < 8; i++)
        if (g_3a04[i]) {
            SelectObject(g_3a04[i], g_3990[i]);
            if (g_3a78[i])
                SelectPalette(g_3a04[i], g_3a78[i], 0);
            DeleteDC(g_3a04[i]);
            g_3a04[i] = 0;
            if (g_3aec[i]) {
                DeleteObject(g_3aec[i]);
                g_3aec[i] = 0;
            }
        }
}

/* 7:4ffe */
void fn_07_4ffe(int16_t n)
{
    int16_t i;

    PatBlt(main_dc, object_records[0][n].f_00.x, object_records[0][n].f_00.y,
           object_records[0][n].f_22, object_records[0][n].f_22, BLACKNESS);
    object_records[0][n].f_18 = 1;
    for (i = 0; i < 2; i++)
        fn_07_5b68(0, n, 1);
    fn_07_5ae8(n, 0);
    fn_07_65aa(0, n);
    fn_08_99ce(0, n, -1, -1);
}

/* Counts empty slots in g_91fc and marks used ones in a bit set
 * [inferred]. */
/* 7:5a46 */
void fn_07_5a46(void)
{
    int16_t i;
    int16_t n, byte;
    uint8_t bit;

    for (i = g_91fc = 0; i < 8; i++) {
        if (object_records[0][i].f_18 != 0 || object_records[0][i].f_2e != 0 || object_records[0][i].f_51 != 0) {
            if (g_57a8[i].f_06 > -1) {
                n = g_57a8[i].f_06;
                byte = n / 8;
                bit = 1 << (n % 8);
                g_69f4[g_94a2].f_1e2[byte] |= bit;
            }
        } else
            g_91fc++;
    }
}

/* 7:5ae8 */
void fn_07_5ae8(int16_t a, int16_t b)
{
    fn_07_5a46();
    if (b) {
        g_69f4[g_94a2].f_150++;
        g_945c++;
    } else {
        g_69f4[g_94a2].f_14e++;
        if (g_57a8[a].f_0a == g_9324)
            g_7090[g_57a8[a].f_0b].f_0d0++;
        g_945e++;
    }
    if (g_91fc == 0 && g_69f4[g_94a2].f_1d0 != 1)
        g_69f4[g_94a2].f_1d0 = 2;
}

/* 7:5660 */
void fn_07_5660(int16_t n)
{
    int16_t size, gap;

    size = object_records[0]->f_22;
    gap = object_records[0]->f_24;
    StretchBlt(g_3a02, (size + gap) * n + gap, gap, size, size,
               g_3a28, n * 32, 0, 32, 32, SRCCOPY);
    fn_07_233c(0, n, 0);
}

/* 7:56ba */
void fn_07_56ba(int16_t n)
{
    int16_t size, gap;

    size = object_records[0]->f_22;
    gap = object_records[0]->f_24;
    StretchBlt(g_3a28, n * 32, 0, 32, 32,
               g_3a02, (size + gap) * n + gap, gap, size, size, SRCCOPY);
}

/* 7:5d6a */
void fn_07_5d6a(int16_t a, int16_t b, int16_t unused, int16_t c, int16_t d)
{
    int16_t i;
    int16_t pct;

    switch (g_9208) {
    case 0:
        pct = 20;
        break;
    case 1:
        pct = 45;
        break;
    case 2:
        pct = 70;
        break;
    case 3:
        pct = 100;
        break;
    }
    if (g_9208 != 3 && rand() % 100 < pct)
        return;
    for (i = 0; i < 20; i++)
        if (g_58bc[i].f_10 == -1) {
            g_58bc[i].f_10 = 0;
            g_58bc[i].c.x = a;
            g_58bc[i].c.y = b;
            g_58bc[i].f_0c = c;
            g_58bc[i].f_0e = d;
            g_9456++;
            return;
        }
}

/* Animates the up-to-20 sparkle bursts in g_58bc and checks them for overlap [inferred]. */
/* 7:5e04 */
void fn_07_5e04(void)
{
    int16_t i;
    int16_t w;
    int16_t off;
    int16_t q;
    int16_t srcx;
    int16_t j;
    int16_t k = 0;
    int16_t tbl[6];
    RECT r2;
    RECT r1;
    RECT r3;
    int16_t flag;
    RECT r4;

    tbl[2] = 6;
    tbl[3] = 18;
    tbl[4] = 36;
    tbl[5] = 60;
    for (i = tbl[1] = tbl[0] = 0; i < 20; i++) {
        if (g_58bc[i].f_10 < 55 && g_58bc[i].f_10 > -1) {
            q = g_58bc[i].f_10 / 9;
            if (g_58bc[i].f_10 % 4 <= g_9208 + 2) {
                w = (q + 5) * 2 << g_9156 >> 1;
                srcx = q * (30 << g_9156 >> 1) + ((q < 6 ? tbl[q] : k) << g_9156 >> 1)
                    + w * (g_58bc[i].f_10 / 3 % 3);
                off = q;
                fn_08_124a(i);
                flag = 1;
                if (g_9208 >= 2) {
                    SetRect(&r3, g_58bc[i].a.x - (off << g_9156 >> 1),
                            g_58bc[i].a.y - (off << g_9156 >> 1),
                            g_58bc[i].a.x - (off << g_9156 >> 1) + w,
                            g_58bc[i].a.y - (off << g_9156 >> 1) + w);
                    for (j = 0; j < g_9146; j++) {
                        SetRect(&r1, object_records[g_507c[j]][g_50e0[j]].f_00.x,
                                object_records[g_507c[j]][g_50e0[j]].f_00.y,
                                object_records[g_507c[j]][g_50e0[j]].f_22 + object_records[g_507c[j]][g_50e0[j]].f_00.x,
                                object_records[g_507c[j]][g_50e0[j]].f_22 + object_records[g_507c[j]][g_50e0[j]].f_00.y);
                        if (IntersectRect(&r2, &r3, &r1))
                            flag = 0;
                    }
                }
                g_58bc[i].c.x += g_58bc[i].f_0c;
                g_58bc[i].c.y += g_58bc[i].f_0e;
                if (g_58bc[i].f_12)
                    PatBlt(main_dc, g_58bc[i].b.x - (off << g_9156 >> 1),
                           g_58bc[i].b.y - (off << g_9156 >> 1), w, w, BLACKNESS);
                if (subgame_active) {
                    SetRect(&r3, g_58bc[i].a.x - (off << g_9156 >> 1),
                            g_58bc[i].a.y - (off << g_9156 >> 1),
                            g_58bc[i].a.x - (off << g_9156 >> 1) + w,
                            g_58bc[i].a.y - (off << g_9156 >> 1) + w);
                    for (k = 0; k < 4; k++)
                        for (j = 0; j < 3; j++)
                            if (IntersectRect(&r2, &r3, &g_8860[k * 3 + j])) {
                                flag = 0;
                                g_58bc[i].f_10 = 0x36;
                                fn_18_5350(g_58bc[k].a.x, g_58bc[k].a.y);   /* sic: k, not i */
                                break;
                            }
                }
                if (flag) {
                    BitBlt(main_dc, g_58bc[i].a.x - (off << g_9156 >> 1),
                           g_58bc[i].a.y - (off << g_9156 >> 1), w, w,
                           g_3a00, srcx, 0, SRCCOPY);
                    g_58bc[i].f_12 = 1;
                } else
                    g_58bc[i].f_12 = 0;
                SetRect(&r4, object_records[g_9324][main_ship].f_00.x - w, object_records[g_9324][main_ship].f_00.y - w,
                        object_records[g_9324][main_ship].f_00.x + object_records[g_9324][main_ship].f_22 + w,
                        object_records[g_9324][main_ship].f_00.y + object_records[g_9324][main_ship].f_22 + w);
                if (PtInRect(&r4, g_58bc[i].a))
                    hazards_ship_redraw_pending = 1;
            }
            g_58bc[i].f_10++;
        }
        if (g_58bc[i].f_10 == 55) {
            PatBlt(main_dc, g_58bc[i].a.x - (6 << g_9156 >> 1), g_58bc[i].a.y - (6 << g_9156 >> 1),
                   24 << g_9156 >> 1, 24 << g_9156 >> 1, BLACKNESS);
            g_58bc[i].f_10 = -1;
            if (subgame_active)
                fn_18_5350(g_58bc[i].a.x, g_58bc[i].a.y);
            g_9456--;
        }
    }
}

/* Window procedure of the "IS_ICON" pilot-icon window [inferred]. */
/* 7:6184 */
LONG fn_07_6184(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    RECT r;
    RECT rc;
    PAINTSTRUCT ps;
    HDC dc;
    MINMAXINFO *mmi;
    UINT cmd;
    int16_t res;

    switch (msg) {
    case WM_CREATE:
        g_9458 = hwnd;
        g_945a = GetSystemMenu(hwnd, FALSE);
        AppendMenu(g_945a, MF_SEPARATOR, 0, NULL);
        AppendMenu(g_945a, 0, 0xf0, "1/2x Scale");
        fn_07_63b6(g_945a, "1/2x Scale", g_0b6e, 0xf0);
        DrawMenuBar(g_9458);
        break;
    case WM_SYSCOMMAND:
        switch (cmd = wp & 0xfff0) {
        case 0xf0:
            fn_07_63b6(g_945a, "1/2x Scale", g_0b6e = !g_0b6e, 0xf0);
            GetWindowRect(g_9458, &r);
            MoveWindow(g_9458, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
            SetActiveWindow(main_window);
            break;
        case SC_CLOSE:
            g_8f72 = 0;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
        }
        break;
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    case WM_SETFOCUS:
        g_8f68 = 1;
        break;
    case WM_MOVE:
        GetWindowRect(g_9458, &r);
        if (r.left != g_1de4.left || r.top != g_1de4.top) {
            CopyRect(&g_1de4, &r);
            g_8fee = 1;
        }
        SetActiveWindow(main_window);
        break;
    case WM_GETMINMAXINFO:
        mmi = (MINMAXINFO *)lp;
        mmi->ptMinTrackSize.x = mmi->ptMaxTrackSize.x = 50 >> g_0b6e;
        if (g_0b6e)
            mmi->ptMinTrackSize.y = mmi->ptMaxTrackSize.y
                = GetSystemMetrics(SM_CYCAPTION) + g_91fe * 23 + 3;
        else
            mmi->ptMinTrackSize.y = mmi->ptMaxTrackSize.y
                = GetSystemMetrics(SM_CYCAPTION) + g_91fe * 46 + 6;
        break;
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        GetClientRect(hwnd, &rc);
        dc = BeginPaint(hwnd, &ps);
        PatBlt(dc, 0, 0, rc.right, rc.bottom, BLACKNESS);
        res = fn_07_64ac(dc, 1, -1);
        EndPaint(hwnd, &ps);
        if (!res)
            fn_07_63f2();
        break;
    case WM_CLOSE:
        if (g_9458) {
            DestroyWindow(g_9458);
            g_9458 = 0;
        }
        break;
    }
    return 0L;
}

/* 7:63b6 */
void fn_07_63b6(HMENU menu, LPCSTR text, int16_t checked, UINT id)
{
    UINT flags;

    if (checked)
        flags = MF_CHECKED;
    else
        flags = 0;
    ModifyMenu(menu, id, flags, id, text);
}

/* 7:641a */
void fn_07_641a(void)
{
    int16_t i;

    if (g_0a7c && !g_9458 && g_91fc) {
        for (i = 0; i < g_91fe; i++) {
            g_6e38[i + 3].f_1a.b = 0;
            g_6e38[i + 3].f_1a.a = i;
            g_6e38[i + 3].f_16.x = 2;
            g_6e38[i + 3].f_16.y = i * 0x2e + 2;
        }
        CreateWindow("IS_ICON", "", 0x10cc0000L, g_1de4.left, g_1de4.top, 50, 150,
                     main_window, 0, g_8e66, 0L);
    }
    SetActiveWindow(main_window);
}

/* 7:64ac */
int16_t fn_07_64ac(HDC dc, int16_t a, int16_t idx)
{
    int16_t i;
    int16_t u1, u2;
    int16_t release;
    HPALETTE old;

    if (!g_9458)
        return 1;
    release = 0;
    if (!dc) {
        release = 1;
        dc = GetDC(g_9458);
    }
    if (game_palette)
        old = SelectPalette(dc, game_palette, 0);
    if (idx == -1) {
        for (i = 0; i < g_91fe; i++)
            fn_13_5a6a(dc, 0, i * 0x2e + 4, 0, i, i + 3, a, g_0b6e);
    } else
        fn_13_5a6a(dc, 0, idx * 0x2e + 4, 0, idx, idx + 3, a, g_0b6e);
    if (old)
        SelectPalette(dc, old, 0);
    if (release) {
        ReleaseDC(g_9458, dc);
        dc = 0;
    }
    if (g_91fc)
        return 1;
    if (!dc)
        fn_07_63f2();
    return 0;
}

/* 7:65aa */
void fn_07_65aa(int16_t a, int16_t b)
{
    int16_t k;

    if (a == 0)
        fn_07_64ac(0, 1, b);
    if (a == g_9324 && b != main_ship)
        fn_13_6450(0, 1, b);
    if (g_0a76 == 2 || g_0a76 == 3) {
        k = g_0a76 - 2;
        if (g_6e38[k].f_1a.b == a && g_6e38[k].f_1a.a == b)
            fn_13_58dc(0, 1);
    }
}

/* 7:63f2 */
void fn_07_63f2(void)
{
    if (g_9458) {
        DestroyWindow(g_9458);
        g_9458 = 0;
    }
}

/* Spawns a spark/debris particle at an object [inferred]. */
/* 7:5b68 */
void fn_07_5b68(int16_t type, int16_t idx, int16_t flag)
{
    int16_t u1;
    int16_t u2;
    int16_t i;
    int16_t r;
    int16_t chance;

    switch (g_9208) {
    case 0:
        chance = 25;
        break;
    case 1:
        chance = 45;
        break;
    case 2:
        chance = 65;
        break;
    case 3:
        chance = 90;
        break;
    }
    if (g_9208 != 3 && rand() % 100 > chance)
        return;
    for (i = 0; i < 20; i++) {
        if (g_58bc[i].f_10 == -1) {
            g_58bc[i].f_10 = 0;
            if (type == g_9324) {
                g_58bc[i].c.x = (g_7ba0[g_7090[idx].f_04e][object_records[type][idx].f_28].x
                                 - g_1050[object_records[type][idx].f_28].x / 4 - 4) * 8
                                + object_records[type][idx].f_04.x;
                g_58bc[i].c.y = (g_7ba0[g_7090[idx].f_04e][object_records[type][idx].f_28].y
                                 - g_1050[object_records[type][idx].f_28].y / 4 - 4) * 8
                                + object_records[type][idx].f_04.y;
                g_58bc[i].f_0c = object_records[type][idx].f_0c - g_1050[object_records[type][idx].f_28].x / 2;
                g_58bc[i].f_0e = object_records[type][idx].f_0e - g_1050[object_records[type][idx].f_28].y / 2;
            } else {
                g_58bc[i].c.x = rand() % object_records[type][idx].f_20 + object_records[type][idx].f_04.x;
                g_58bc[i].c.y = rand() % object_records[type][idx].f_20 + object_records[type][idx].f_04.y;
                r = rand() % 16;
                g_58bc[i].f_0c = g_1050[r].x / 2 + object_records[type][idx].f_0c / 2;
                g_58bc[i].f_0e = g_1050[r].y / 2 + object_records[type][idx].f_0e / 2;
            }
            if (flag)
                fn_10_754a(1, type, idx, 1);
            g_9456++;
            return;
        }
    }
}

/* Breaks window pane n into four pieces of type 1 [inferred]. */
/* 7:2768 */
void fn_07_2768(int16_t n)
{
    int16_t i;
    int16_t j;
    int16_t k;
    int16_t size;
    int16_t gap;
    int16_t s32;
    int16_t g2;
    int16_t idx[4];
    int16_t found;
    HDC dc[2];
    HGDIOBJ old[2];
    int16_t bmp;

    size = 20 << g_9156 >> 1;
    gap = 6 << g_9156 >> 1;
    s32 = 32 << g_9156 >> 1;
    g2 = 6 << g_9156 >> 1;
    g_57a8[n].f_19 = 1;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < g_92ec[1]; j++) {
            found = 0;
            if (object_records[1][j].f_18 != 0) {
                object_records[1][j].f_18 = 0;
                object_records[1][j].f_1e = 0;
                if (g_4e94[j]) {
                    DeleteObject(g_4e94[j]);
                    g_4e94[j] = 0;
                }
                g_4e94[j] = CreateCompatibleBitmap(main_dc, gap * 2 + size, gap * 2 + size);
                idx[i] = j;
                g_6038[j] = n;
                g_57a8[n].f_1b[i] = j;
                found = 1;
                break;
            }
        }
        if (!found) {
            g_92ec[1] = j + 1;
            GlobalUnlock(g_9100[1]);
            g_9100[1] = GlobalReAlloc(g_9100[1], (int32_t)max(g_92ec[1], 1) * (int32_t)sizeof *object_records[0], 0x42);
            object_records[1] = (REC_70 *)GlobalLock(g_9100[1]);
            object_records[1][j].f_22 = 20 << g_9156 >> 1;
            object_records[1][j].f_20 = 0xa0;
            object_records[1][j].f_24 = 6 << g_9156 >> 1;
            object_records[1][j].f_44 = 0x3c;
            object_records[1][j].f_42 = 0x12;
            object_records[1][j].f_4c = 0x808000;
            object_records[1][j].f_2c = 0xe;
            object_records[1][j].f_18 = 1;
            object_records[1][j].f_66 = fn_07_2e02;
            object_records[1][j].f_62 = fn_11_3914;
            object_records[1][j].f_5e = fn_07_2652;
            object_records[1][j].f_53 = 0;
            object_records[1][j].f_1e = 0;
            object_records[1][j].f_18 = 0;
            object_records[1][j].f_32 = -1;
            object_records[1][j].f_12 = object_records[1][j].f_24;
            object_records[1][j].f_2e = 0;
            if (g_4e94[j]) {
                DeleteObject(g_4e94[j]);
                g_4e94[j] = 0;
            }
            g_4e94[j] = CreateCompatibleBitmap(main_dc, gap * 2 + size, gap * 2 + size);
            idx[i] = j;
            g_6038[j] = n;
            g_57a8[n].f_1b[i] = j;
        }
        if (j >= g_9406[1])
            g_9406[1] = j + 1;
    }
    bmp = fn_10_6308(-1, -1, fn_10_6d38("piece"), -1);
    for (k = 0; k < 2; k++)
        dc[k] = CreateCompatibleDC(main_dc);
    old[0] = SelectObject(dc[0], bmp);
    old[1] = SelectObject(dc[1], g_4e94[0]);

    SelectObject(dc[0], bmp);
    SelectObject(dc[1], g_4e94[idx[0]]);
    PatBlt(dc[1], 0, 0, g2 * 2 + s32, g2 * 2 + s32, BLACKNESS);
    BitBlt(dc[1], gap, gap, size, size, dc[0], 0, 0, SRCCOPY);
    BitBlt(dc[1], (2 << g_9156 >> 1) + gap, (2 << g_9156 >> 1) + gap,
           size - (4 << g_9156 >> 1), size - (4 << g_9156 >> 1), g_3a02,
           (g2 + s32) * n + (3 << g_9156 >> 1) + g2, (3 << g_9156 >> 1) + g2, SRCCOPY);

    SelectObject(dc[0], bmp);
    SelectObject(dc[1], g_4e94[idx[1]]);
    PatBlt(dc[1], 0, 0, g2 * 2 + s32, g2 * 2 + s32, BLACKNESS);
    BitBlt(dc[1], gap, gap, size, size, dc[0], 0, 0, SRCCOPY);
    BitBlt(dc[1], (2 << g_9156 >> 1) + gap, (2 << g_9156 >> 1) + gap,
           size - (4 << g_9156 >> 1), size - (4 << g_9156 >> 1), g_3a02,
           (g2 + s32) * n + s32 / 2 + g2, (3 << g_9156 >> 1) + g2, SRCCOPY);

    SelectObject(dc[0], bmp);
    SelectObject(dc[1], g_4e94[idx[2]]);
    PatBlt(dc[1], 0, 0, g2 * 2 + s32, g2 * 2 + s32, BLACKNESS);
    BitBlt(dc[1], gap, gap, size, size, dc[0], 0, 0, SRCCOPY);
    BitBlt(dc[1], (2 << g_9156 >> 1) + gap, (2 << g_9156 >> 1) + gap,
           size - (4 << g_9156 >> 1), size - (4 << g_9156 >> 1), g_3a02,
           (g2 + s32) * n + (3 << g_9156 >> 1) + g2, g2 + size, SRCCOPY);

    SelectObject(dc[0], bmp);
    SelectObject(dc[1], g_4e94[idx[3]]);
    PatBlt(dc[1], 0, 0, g2 * 2 + s32, g2 * 2 + s32, BLACKNESS);
    BitBlt(dc[1], gap, gap, size, size, dc[0], 0, 0, SRCCOPY);
    BitBlt(dc[1], (2 << g_9156 >> 1) + gap, (2 << g_9156 >> 1) + gap,
           size - (4 << g_9156 >> 1), size - (4 << g_9156 >> 1), g_3a02,
           (g2 + s32) * n + g2 + size, g2 + size, SRCCOPY);

    for (k = 0; k < 2; k++) {
        SelectObject(dc[k], old[k]);
        DeleteDC(dc[k]);
    }
    if (bmp) {
        DeleteObject(bmp);
        bmp = 0;
    }
    object_records[1][idx[0]].f_04.x = object_records[0][n].f_04.x;
    object_records[1][idx[0]].f_04.y = object_records[0][n].f_04.y;
    object_records[1][idx[0]].f_0c = object_records[0][n].f_0c - 10;
    object_records[1][idx[0]].f_0e = object_records[0][n].f_0e - 10;
    object_records[1][idx[1]].f_04.x = object_records[0][n].f_04.x + 0xb0;
    object_records[1][idx[1]].f_04.y = object_records[0][n].f_04.y;
    object_records[1][idx[1]].f_0c = object_records[0][n].f_0c + 20;
    object_records[1][idx[1]].f_0e = object_records[0][n].f_0e - 10;
    object_records[1][idx[2]].f_04.x = object_records[0][n].f_04.x;
    object_records[1][idx[2]].f_04.y = object_records[0][n].f_04.y + 0xb0;
    object_records[1][idx[2]].f_0c = object_records[0][n].f_0c - 10;
    object_records[1][idx[2]].f_0e = object_records[0][n].f_0e + 20;
    object_records[1][idx[3]].f_04.x = object_records[0][n].f_04.x + 0xb0;
    object_records[1][idx[3]].f_04.y = object_records[0][n].f_04.y + 0xb0;
    object_records[1][idx[3]].f_0c = object_records[0][n].f_0c + 10;
    object_records[1][idx[3]].f_0e = object_records[0][n].f_0e + 10;
}

/* Animates a window pane being cleared: shifts random columns [inferred]. */
/* 7:4d86 */
void fn_07_4d86(int16_t n)
{
    int16_t a;
    int16_t b;
    int16_t c;
    int16_t d;
    int16_t gap;
    int16_t size;
    int16_t j;
    int16_t w;

    size = object_records[0]->f_22;
    gap = object_records[0]->f_24;
    a = (rand() % 12 + 10 << g_9156) >> 1;
    b = (rand() % 12 + 10 << g_9156) >> 1;
    c = rand() % 10 << g_9156;
    d = (rand() % 10 + 22 << g_9156) >> 1;
    w = 2 << g_9156 >> 1;
    if (g_57a8[n].f_02 == 0) {
        BitBlt(g_3a02, (size + gap) * n + gap + a, gap, w, size,
               g_3a02, (size + gap) * n + gap + a, gap - w, SRCCOPY);
        BitBlt(g_3a02, (size + gap) * n + gap + b, gap, w, size,
               g_3a02, (size + gap) * n + gap + b, gap - w, SRCCOPY);
        BitBlt(g_3a02, (size + gap) * n + gap + c, gap, w, size,
               g_3a02, (size + gap) * n + gap + c, gap - w, SRCCOPY);
        BitBlt(g_3a02, (size + gap) * n + gap + d, gap, w, size,
               g_3a02, (size + gap) * n + gap + d, gap - w, SRCCOPY);
        g_57a8[n].f_00--;
        return;
    }
    if (rand() & 1)
        c = d;
    BitBlt(g_3a02, (size + gap) * n + gap + a, gap, w, size,
           g_3a02, (size + gap) * n + gap + a, gap - w / 2, SRCCOPY);
    BitBlt(g_3a02, (size + gap) * n + gap + c, gap, w, size,
           g_3a02, (size + gap) * n + gap + c, gap - w / 2, SRCCOPY);
    for (j = 1; j < 6; j++) {
        BitBlt(g_3a04[n], (size + gap) * (j - 1) + gap + a, gap, w, size,
               g_3a04[n], (size + gap) * (j - 1) + gap + a, gap - w / 2, SRCCOPY);
        BitBlt(g_3a04[n], (size + gap) * (j - 1) + gap + c, gap, w, size,
               g_3a04[n], (size + gap) * (j - 1) + gap + c, gap - w / 2, SRCCOPY);
    }
    if (g_57a8[n].f_02 < 7)
        g_57a8[n].f_00--;
    if (g_57a8[n].f_00 < 50 && g_57a8[n].f_00 % 5 == 0)
        fn_07_5b68(0, n, 0);
}

/* Collision of object (type, idx) with window pane n [inferred]. */
/* 7:4a38 */
void fn_07_4a38(int16_t type, int16_t idx, int16_t n)
{
    int16_t i;
    int16_t k;                      /* kept in ax, never stored */
    int16_t u2;
    int16_t u3;
    int16_t u4;

    if (type == g_9324 && g_96d2[g_7090[idx].f_04e].f_42 && !g_7090[idx].f_0ea
        && !object_records[0][n].f_51)
        fn_13_16ac(idx, (char)n);
    else if (type == g_9328) {
        if (object_records[g_9328][idx].f_44 == 120) {
            if (object_records[0][n].f_2f < 0) {
                for (i = 0; i < 4; i++)
                    fn_07_5b68(0, n, 1);
                if (object_records[0][n].f_2f < -2)
                    fn_10_754a(0x76, 0, n, 1);
                object_records[0][n].f_2f = -2;
                fn_07_5660(n);
                if (g_5a4c[idx].f_04 == g_9324)
                    g_7090[g_5a4c[idx].f_06].f_038 = g_7090[g_5a4c[idx].f_06].f_036 = 2;
            } else if (g_57a8[n].f_02 == 0) {
                g_57a8[n].f_02 = 2;
                g_57a8[n - 1].f_1f = now_ms + 4000;
                if (!object_records[0][n].f_1e && object_records[0][n].f_53 == 1 && g_5a4c[idx].f_04 == 14
                    && g_7090[k = g_5a4c[idx].f_06].f_032.a == 0 && g_7090[k].f_032.b == n
                    && g_7090[k].f_038 == 1)
                    report_crime(k, 1);
                fn_07_477e(n);
                object_records[0][n].f_53 = 0;
            }
        } else if (object_records[g_9328][idx].f_44 == 200) {
            if (g_57a8[n].f_02 > 0) {
                g_57a8[n].f_02 = g_57a8[n].f_00 = 0;
                object_records[0][n].f_2f = -2;
                for (i = 0; i < 4; i++)
                    fn_07_5b68(0, n, 1);
                object_records[0][n].f_53 = 1;
                fn_10_754a(0x76, 0, n, 1);
                fn_07_56ba(n);
            } else if (object_records[0][n].f_2f >= 0) {
                fn_07_2512(n, 1);
                object_records[0][n].f_2f = -100;
                object_records[0][n].f_53 = 0;
            }
        }
    }
    if (type != g_9328 || object_records[g_9328][idx].f_44 != 120)
        fn_08_5df2(0, n, type, idx,
                   fn_08_546c((type << 8) | (char)idx, &object_records[0][n].f_0c, &object_records[0][n].f_0e,
                              object_records[0][n].f_20 + 2, object_records[0][n].f_44));
    if (type == g_934a && object_records[g_934a][idx].f_2f > 4) {
        g_57a8[n].f_00 = 80;
        fn_10_754a(0x6a, 0, n, 1);
    }
    if (g_57a8[n].f_02 > 0) {
        switch (type) {
        case 3:
            object_records[type][idx].f_2f = min(object_records[type][idx].f_2f + 2, 9);
            object_records[type][idx].f_6a = now_ms + 5000;
            break;
        case 0:
            g_57a8[idx].f_02 = 2;
            fn_07_477e(idx);
            break;
        }
        if (type == g_9324 && idx == main_ship)
            fn_08_45e0(g_9324, main_ship, 25);
    }
}

/* Splits object idx of the given type in two, growing the g_9328 object
 * array when no free slot is left [inferred]. */
/* 7:570a */
int16_t fn_07_570a(int16_t type, int16_t idx, int16_t amount)
{
    int16_t n;
    int16_t j;
    int16_t found;

    if (g_5a4c[idx].f_12 == 0 && object_records[type][idx].f_44 == 200) {
        n = -1;
        found = 0;
        do {
            n++;
            if (g_92ec[g_9328] <= n) {
                g_92ec[g_9328] = n + 1;
                GlobalUnlock(g_9100[g_9328]);
                g_9100[g_9328] = GlobalReAlloc(g_9100[g_9328],
                                               (int32_t)max(g_92ec[g_9328], 1) * (int32_t)sizeof *object_records[0], GHND);
                object_records[g_9328] = (REC_70 *)GlobalLock(g_9100[g_9328]);
                object_records[g_9328][n].f_44 = 120;
                object_records[g_9328][n].f_42 = 100;
                object_records[g_9328][n].f_4c = 0xff;
                object_records[g_9328][n].f_62 = fn_11_3914;
                object_records[g_9328][n].f_5e = fn_07_570a;
                object_records[g_9328][n].f_53 = 0;
                object_records[g_9328][n].f_54 = 0;
                object_records[g_9328][n].f_32 = -1;
                object_records[g_9328][n].f_12 = object_records[g_9328][n].f_24;
                object_records[g_9328][n].f_2e = 0;
                g_5a4c[n].f_00 = -1;
                g_9406[g_9328] = n + 1;
            }
            if (g_5a4c[n].f_00 == -1) {
                object_records[type][n].f_18 = g_5a4c[n].f_10 = g_5a4c[n].f_00 = 0;
                g_5a4c[n].f_12 = found = 1;
                object_records[type][n].f_2e = 0;
                object_records[type][n].f_44 = 200;
                for (j = 0; j < 5; j++)
                    g_5eac[n][j + 6] = g_5eac[n][j] = -100;
                object_records[type][n].f_04.x = object_records[type][idx].f_04.x;
                object_records[type][n].f_04.y = object_records[type][idx].f_04.y;
                g_5a4c[n].f_04 = g_5a4c[idx].f_04;
                g_5a4c[n].f_06 = g_5a4c[idx].f_06;
                g_5a4c[n].f_08 = g_5a4c[idx].f_08;
                g_5a4c[n].f_0a = g_5a4c[idx].f_0a;
                object_records[type][n].f_0c = g_5a4c[idx].f_0e / 3 + g_5a4c[idx].f_0c;
                object_records[type][n].f_0e = g_5a4c[idx].f_0c / -3 + g_5a4c[idx].f_0e;
                g_5a4c[n].f_02 = 16;
                break;
            }
        } while (!found);
        fn_07_2080(g_9328);
        object_records[type][idx].f_0c = g_5a4c[idx].f_0e / -3 + g_5a4c[idx].f_0c;
        object_records[type][idx].f_0e = g_5a4c[idx].f_0c / 3 + g_5a4c[idx].f_0e;
        g_5a4c[idx].f_12 = 1;
        g_5a4c[idx].f_02 = 16;
    } else {
        VIEW(POINT, object_records[type][idx].f_0c, 0) = VIEW(POINT, g_5a4c[idx].f_0c, 0);
    }
    return 0;
}

/* Hit callback of the g_934a objects: big hits split one into three
 * pieces spread around it [inferred]. */
/* 7:5090 */
int16_t fn_07_5090(int16_t type, int16_t idx, int16_t amount)
{
    int16_t k;
    int16_t n;
    int16_t lvl;
    int16_t cnt;
    int16_t found;
    POINT d;

    if (g_9406[g_944c] < g_9450)
        return 0;
    if (type == g_934a && amount > 1) {
        amount = (int16_t)(amount * 3) / 2;
        lvl = object_records[type][idx].f_2f;
        if (g_9328 != g_944c || object_records[g_944c][g_9450].f_44 != 200)
            object_records[type][idx].f_2f = min(amount / 4 + object_records[type][idx].f_2f, 9);
        object_records[type][idx].f_6a = now_ms + 3000;
        object_records[type][idx].f_1e += amount;
        if (object_records[type][idx].f_1e > object_records[type][idx].f_2c && (lvl > 6 || subgame_active)) {
            if (object_records[type][idx].f_44 == 350) {
                fn_12_274a(type, idx);
                fn_07_2080(type);
                return 1;
            }
            object_records[g_934a][idx].f_18 = 1;
            PatBlt(main_dc, object_records[type][idx].f_00.x, object_records[type][idx].f_00.y, object_records[type][idx].f_22,
                   object_records[type][idx].f_22, BLACKNESS);
            fn_10_754a(0x45, g_934a, idx, 1);
            for (k = cnt = 0; k < 3; k++) {
                n = -1;
                found = 0;
                do {
                    n++;
                    if (n < 126) {
                        if (g_92ec[g_934a] <= n) {
                            g_92ec[g_934a] = n + 1;
                            GlobalUnlock(g_9100[g_934a]);
                            g_9100[g_934a] = GlobalReAlloc(g_9100[g_934a],
                                                           (int32_t)max(g_92ec[g_934a], 1) * (int32_t)sizeof *object_records[0],
                                                           GHND);
                            object_records[g_934a] = (REC_70 *)GlobalLock(g_9100[g_934a]);
                            object_records[g_934a][n].f_48 = 9;
                            if (subgame_active)
                                object_records[g_934a][n].f_48 = 5;
                            object_records[g_934a][n].f_42 = 8;
                            object_records[g_934a][n].f_46 = 4;
                            object_records[g_934a][n].f_4c = 0xc0c0c0;
                            object_records[g_934a][n].f_5e = fn_07_5090;
                            object_records[g_934a][n].f_53 = 0;
                            object_records[g_934a][n].f_54 = 0;
                            object_records[g_934a][n].f_32 = -1;
                            object_records[g_934a][n].f_24 = 5 << g_9156 >> 1;
                            object_records[g_934a][n].f_12 = object_records[g_934a][n].f_24;
                            object_records[g_934a][n].f_2e = 0;
                            object_records[g_934a][n].f_18 = 1;
                            g_9406[g_934a] = n + 1;
                        }
                        if (object_records[g_934a][n].f_18) {
                            cnt++;
                            object_records[g_934a][n].f_44 = 350;
                            object_records[g_934a][n].f_22 = 22 << g_9156 >> 1;
                            object_records[g_934a][n].f_20 = 0xa8;
                            object_records[g_934a][n].f_2e = 0;
                            object_records[g_934a][n].f_24 = 4 << g_9156 >> 1;
                            object_records[g_934a][n].f_12 = object_records[g_934a][n].f_24;
                            if (g_9156 == 0 && subgame_active)
                                object_records[g_934a][n].f_22 = (int16_t)(object_records[g_934a][n].f_22 * 2) / 3;
                            if (g_9156 == 2 && g_0740) {
                                object_records[g_934a][n].f_24 = 4;
                                object_records[g_934a][n].f_12 = 4;
                            }
                            if (g_9156 == 1 && (g_0740 || subgame_active)) {
                                object_records[g_934a][n].f_24 = 2;
                                object_records[g_934a][n].f_12 = 2;
                            }
                            if (g_9156 == 0 && (g_0740 || subgame_active)) {
                                object_records[g_934a][n].f_24 = 1;
                                object_records[g_934a][n].f_12 = 1;
                            }
                            object_records[g_934a][n].f_62 = fn_11_3914;
                            object_records[g_934a][n].f_2c = 300;
                            if (subgame_active)
                                object_records[g_934a][n].f_2c = 100;
                            object_records[g_934a][n].f_1e = 0;
                            object_records[g_934a][n].f_2f = 9;
                            switch (cnt) {
                            case 1:
                                d.x = 0;
                                d.y = -10;
                                break;
                            case 2:
                                d.x = 15;
                                d.y = 12;
                                break;
                            case 3:
                                d.x = -15;
                                d.y = 13;
                                break;
                            }
                            object_records[g_934a][n].f_04.x = d.x * 8 + object_records[type][idx].f_04.x;
                            object_records[g_934a][n].f_04.y = d.y * 8 + object_records[type][idx].f_04.y;
                            object_records[g_934a][n].f_18 = 0;
                            found = 1;
                        }
                    }
                } while (!found && n < 126);
            }
            return 1;
        }
    }
    object_records[type][idx].f_1e += amount;
    return 0;
}

#define SC(n) ((int16_t)((n) << g_9156) >> 1)
/* Steps the g_5a4c effect of each g_9328 object (size from its counter,
 * a 6-point trail in g_5eac) and applies its hit to what it touches
 * [inferred]. */
/* near-match 58%: 7:40c4 (bytes shift; only the first f2f clamp differs: the
 * game keeps &g_1df8[type] in bx, this keeps type * 4) */
void fn_07_40c4(void)
{
    int16_t n;
    int16_t k;
    int16_t j;
    int16_t r;
    int16_t c;
    int16_t e;
    int16_t t;
    int16_t dci;
    int16_t unused[9];      /* frame filler */

    for (n = 0; n < g_9406[g_9328]; n++) {
        if (g_5a4c[n].f_00 > -1) {
            if (g_5a4c[n].f_00 < 28) {
                e = g_5a4c[n].f_00 / 5;
                c = e * 6 + 10;
                t = e * 3;
            } else if (g_5a4c[n].f_00 < 30) {
                e = 7;
                c = 52;
                t = 21;
            } else
                t = c = e = 0;
            c = SC(c);
            for (k = 5; k > 0; k--) {
                g_5eac[n][k] = g_5eac[n][k - 1];
                g_5eac[n][k + 6] = g_5eac[n][k + 5];
                g_5eac[n][k + 12] = g_5eac[n][k + 11];
            }
            object_records[g_9328][n].f_04.x -= t * 8;
            object_records[g_9328][n].f_04.y -= t * 8;
            object_records[g_9328][n].f_00 =
                fn_08_29ea(object_records[g_9328][n].f_04);
            g_5eac[n][0] = object_records[g_9328][n].f_00.x;
            g_5eac[n][6] = object_records[g_9328][n].f_00.y;
            object_records[g_9328][n].f_22 = g_5eac[n][12] = c;
            object_records[g_9328][n].f_20 = c << g_9150;
            object_records[g_9328][n].f_10 = SC(g_0b70[e]);
            object_records[g_9328][n].f_12 = 0;
            if (object_records[g_9328][n].f_44 == 120)
                dci = 10;
            else if (object_records[g_9328][n].f_44 == 200)
                dci = 11;
            fn_08_0b76((char)n | g_9328 << 8, 6, g_39e8[dci], 0);
            object_records[g_9328][n].f_04.x += t * 8;
            object_records[g_9328][n].f_04.y += t * 8;
            PatBlt(main_dc, g_5eac[n][5] - 1, g_5eac[n][11] - 1,
                   g_5eac[n][17] + 2, g_5eac[n][17] + 2, BLACKNESS);
            if (LO16(g_90ea) / 2 - g_5eac[n][17] < g_5eac[n][5]
                && HI16(g_90ea) / 2 - g_5eac[n][17] < g_5eac[n][11]
                && LO16(g_90ea) / 2 + SC(40) > g_5eac[n][5]
                && HI16(g_90ea) / 2 + SC(40) > g_5eac[n][11])
                g_7090[main_ship].f_156 = now_ms - 1;
            for (j = 0; j < 2; j++) {
                HGDIOBJ old = SelectObject(main_dc, g_5ea8[j]);

                PatBlt(main_dc, g_5eac[n][4 - j] - 1, g_5eac[n][10 - j] - 1,
                       g_5eac[n][16 - j] + 2, g_5eac[n][16 - j] + 2, 0xa000c9L);
                SelectObject(main_dc, old);
            }
            VIEW(POINT, g_5a4c[n].f_0c, 0) = VIEW(POINT, object_records[g_9328][n].f_0c, 0);
            fn_08_1b54((char)n | g_9328 << 8, 1);
            if (object_records[g_9328][n].f_1a != 0 || g_9320 == 6) {
                g_943c = n;
                g_943a = g_9328;
                r = fn_08_50aa((char)n | g_9328 << 8);
                if (r != -1) {
                    fn_08_5df2(g_9328, n, HIBYTE(r), LOBYTE(r),
                               fn_08_546c(r, &object_records[g_9328][n].f_0c, &object_records[g_9328][n].f_0e,
                                          object_records[g_9328][n].f_20 + 2, object_records[g_9328][n].f_44));
                    if (HIBYTE(r) == g_934a) {
                        if (object_records[g_9328][n].f_44 == 120) {
                            object_records[HIBYTE(r)][LOBYTE(r)].f_2f =
                                min(object_records[HIBYTE(r)][LOBYTE(r)].f_2f + 1, 9);
                            object_records[HIBYTE(r)][LOBYTE(r)].f_6a = now_ms + 5000;
                        } else if (object_records[g_9328][n].f_44 == 200
                                   && object_records[HIBYTE(r)][LOBYTE(r)].f_2f > 0)
                            object_records[HIBYTE(r)][LOBYTE(r)].f_2f =
                                -(object_records[HIBYTE(r)][LOBYTE(r)].f_2f * 5);
                    }
                    if (HIBYTE(r) == 8 && object_records[HIBYTE(r)][LOBYTE(r)].f_44 == 3500) {
                        if (object_records[g_9328][n].f_44 == 120) {
                            object_records[HIBYTE(r)][LOBYTE(r)].f_2f =
                                min(object_records[HIBYTE(r)][LOBYTE(r)].f_2f + 1, 9);
                            object_records[HIBYTE(r)][LOBYTE(r)].f_6a = now_ms + 5000;
                        } else if (object_records[g_9328][n].f_44 == 200
                                   && object_records[HIBYTE(r)][LOBYTE(r)].f_2f > 0)
                            object_records[HIBYTE(r)][LOBYTE(r)].f_2f =
                                -(object_records[HIBYTE(r)][LOBYTE(r)].f_2f * 5);
                    }
                    if (object_records[HIBYTE(r)][LOBYTE(r)].f_44 == 160) {
                        if (object_records[g_9328][n].f_44 == 120) {
                            if (g_57a8[LOBYTE(r)].f_02 == 0) {
                                g_57a8[LOBYTE(r)].f_02 = 2;
                                g_57a8[LOBYTE(r) - 1].f_1f = now_ms + 4000;
                                fn_07_477e(LOBYTE(r));
                            }
                        } else if (object_records[g_9328][n].f_44 == 200
                                   && g_57a8[LOBYTE(r)].f_02 > 0) {
                            g_57a8[LOBYTE(r)].f_00 = g_57a8[LOBYTE(r)].f_02 = 0;
                            for (j = 0; j < 4; j++)
                                fn_07_5b68(HIBYTE(r), LOBYTE(r), 1);
                        }
                    }
                }
            }
            g_5a4c[n].f_00++;
            if (g_5a4c[n].f_02 + 4 < g_5a4c[n].f_00) {
                if (fn_08_7ba8(object_records[g_9328][n].f_00))
                    PatBlt(main_dc, object_records[g_9328][n].f_00.x - 1, object_records[g_9328][n].f_00.y - 1,
                           54, 54, BLACKNESS);
                for (k = 0; k < 6; k++)
                    PatBlt(main_dc, g_5eac[n][k] - 1, g_5eac[n][k + 6] - 1,
                           object_records[g_9328][n].f_22 + 2, object_records[g_9328][n].f_22 + 2, BLACKNESS);
                g_5a4c[n].f_00 = -1;
                object_records[g_9328][n].f_18 = 1;
                if (subgame_active)
                    fn_18_5350(object_records[g_9328][n].f_00.x, object_records[g_9328][n].f_00.y);
                fn_07_2080(g_9328);
            }
        }
    }
}
