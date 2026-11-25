/* INSPACE.EXE segment 11 (selector 1050). */
#include "game.h"

/* inspace.h declares g_1e4c as long; here it is used as a far pointer. */
                                              
                                         

/* inspace.h declares g_05a0 as long; here it is two ints (world width and
 * height [inferred]). */
                                       
                                    

/* 0xad-byte records; lowest field seen at DS:96ea (seg04.c bases them at
 * 96f0) [inferred]. */

                                          

#define SC(n) ((int16_t)((n) << g_9156) >> 1)

/* Redraw the four system status lights of the player's ship and play the
 * damage/repair messages [inferred]. */
/* 11:05fe */
void fn_11_05fe(int16_t a)
{
    int16_t i;
    int16_t st;
    HDC dc;
    HBITMAP oldbmp;
    HBRUSH oldbrush;
    HPALETTE oldpal;
    int16_t said;

    if (g_934e < 4)
        said = 1;
    else
        said = 0;
    for (i = 0; i < 4; i++) {
        if (VIEWP(int16_t *, g_96d2[g_7090[main_ship].f_04e].f_22, 0)[i] == -1)
            st = 42;
        else if (g_7090[main_ship].f_026[i] > 75)
            st = 0;
        else if (g_7090[main_ship].f_026[i] > 50)
            st = 1;
        else if (g_7090[main_ship].f_026[i] > 25)
            st = 2;
        else if (g_7090[main_ship].f_026[i] > 0)
            st = 30;
        else
            st = 42;
        if (st != g_0aa2[i]) {
            if (st > g_0aa2[i]) {
                if (st == 30 && i == 0) {
                    if (!said) {
                        said = 1;
                        fn_03_06ec(main_ship, 7, 0, 10);
                    }
                } else if (st == 42) {
                    switch (i) {
                    case 1:
                        if (!said)
                            fn_03_06ec(main_ship, 7, 0, 11);
                        break;
                    case 2:
                        if (!said)
                            fn_03_06ec(main_ship, 7, 0, 12);
                        break;
                    }
                }
                switch (st) {       /* empty cases kept from the original */
                case 2:
                    break;
                case 30:
                    break;
                case 42:
                    break;
                }
            } else if (g_951a == 0 && g_952e != main_ship) {
                switch (st) {
                default:
                    break;
                case 0:
                    switch (i) {
                    case 1:
                        if (!said)
                            fn_03_06ec(main_ship, 7, 0, 0x52);
                        break;
                    case 2:
                        if (!said)
                            fn_03_06ec(main_ship, 7, 0, 0x53);
                        break;
                    }
                }
            }
        }
        if (a || st == 30 || g_0aa2[i] != st) {
            g_0aa2[i] = st;
            if (st == 30) {
                if (g_93fe)
                    st = 2;
                else
                    st = 42;
            }
            if (st == 42) {
                oldbrush = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
                PatBlt(g_13dc, g_93c0 + 6, g_8e5a + i * 14 + 30, 27, 6, PATCOPY);
                SelectObject(g_13dc, oldbrush);
            } else {
                dc = CreateCompatibleDC(g_13dc);
                oldbmp = SelectObject(dc, g_5030[2]);
                if (g_920e)
                    oldpal = SelectPalette(dc, g_920e, 0);
                BitBlt(g_13dc, g_93c0 + 6, g_8e5a + i * 14 + 30, 27, 6, dc,
                       0, st * 6, SRCCOPY);
                SelectObject(dc, oldbmp);
                if (oldpal)
                    SelectPalette(dc, oldpal, 0);
                DeleteDC(dc);
            }
        }
    }
}

/* Fire the ship's weapon n: checks the reload time and aim, then fills a
 * free 0x94-byte shot record [inferred]. */
/* 11:4e0a */
void fn_11_4e0a(int16_t n)
{
    int16_t i;
    int16_t k;
    int16_t j;
    int16_t t;
    int16_t facing;
    int16_t ang;
    int16_t cnt;
    int32_t ldx;
    int32_t ldy;
    int32_t len;
    int16_t ok;
    int16_t flag;
    int16_t found;
    POINT from;
    POINT to;

    g_0594 = 7;
    if (n == g_952e && g_9e49 >= 3 && g_9e49 <= 6 && subgame_active == 0)
        return;
    if (g_7090[n].f_026[1] == 0)
        return;
    if (g_7090[n].f_08c != 0 && g_7090[n].f_08c + g_7090[n].f_0a0 > g_1e68
        || g_7090[n].f_0a0 + 5 > g_1e68)
        return;
    if (g_1df8[g_9324][n].f_1a == 0 && g_7090[n].f_032.a != 0
        && g_7090[n].f_032.a != 9 && g_7090[n].f_032.a != g_9324)
        return;
    if (n != main_ship || g_9134 != 0) {
        if (g_1df8[g_9324][n].f_1a == 0)
            from = fn_08_29ea(g_1df8[g_9324][n].f_04);
        else
            from = g_1df8[g_9324][n].f_00;
        if (g_1df8[g_7090[n].f_032.a][g_7090[n].f_032.b].f_1a == 0)
            to = fn_08_29ea(g_1df8[g_7090[n].f_032.a][g_7090[n].f_032.b].f_04);
        else
            to = g_1df8[g_7090[n].f_032.a][g_7090[n].f_032.b].f_00;
        ang = fn_08_19b0(to.x - from.x, to.y - from.y);
        facing = g_1df8[g_9324][n].f_28;
        if (g_7090[n].f_032.a == g_9324 && g_7090[g_7090[n].f_032.b].f_0e8 != 0)
            ang = facing;
        if (ang != facing)
            return;
        fn_11_5ab6(n, 5);
    }
    if (n == main_ship)
        g_8e28 = g_1e50;
    ok = 1;
    found = flag = 0;
    cnt = 0;
    for (i = 0; i < g_0594; i++) {
        if (g_6098[i].z[1][5] == -1)
            cnt++;
        else if (g_6098[i].f_7a == g_9324 && g_6098[i].f_7c == n) {
            flag = 1;
            if (LO16(g_90ea) / ((g_0594 - 2) * 10) >= g_6098[i].z[1][5]) {
                ok = 0;
                break;
            }
        }
        if (g_6098[i].f_7a == g_9324 && g_6098[i].f_7c == main_ship)
            found = 1;
    }
    if (cnt < 2 && found == 0 && n != main_ship)
        return;
    if (ok == 0)
        return;
    g_7090[n].f_0cc = max(7 - g_9000 * 2 - g_9334, 1);
    g_7090[n].f_0a0 = g_1e68;
    g_7090[n].f_14a = g_1df8[g_9324][n].f_04;
    g_7090[n].f_14e = g_1e50;
    if (n == main_ship && g_9134 != 0)
        fn_07_1208();
    for (i = 0; i < g_0594; i++) {
        if (g_6098[i].z[1][5] == -1) {
            k = g_6098[i].f_80 = g_6098[i].f_7e = g_6098[i].z[1][5] = 0;
            for (; k < g_0594; k++)
                for (j = 0; j < g_7090[n].f_024; j++) {
                    g_6098[i].f_30[j][k] = -100;
                    g_6098[i].f_48[j][k] = -100;
                    fn_08_0764(i, k);
                }
            g_6098[i].f_30[0][0] = g_6098[i].f_30[1][0] = g_1df8[g_9324][n].f_04.x;
            g_6098[i].f_48[0][0] = g_6098[i].f_48[1][0] = g_1df8[g_9324][n].f_04.y;
            g_6098[i].f_7a = g_9324;
            g_6098[i].f_7c = n;
            g_6098[i].count = g_7090[n].f_024;
            VIEWP(int16_t *, g_6098[i].f_84, 0)[0] = g_7090[n].f_0e0;
            VIEWP(int16_t *, g_6098[i].f_84, 0)[1] = g_7090[n].f_0e1;
            g_6098[i].z[1][2] = g_1050[g_1df8[g_9324][n].f_28].x * 3;
            g_6098[i].z[1][3] = g_1050[g_1df8[g_9324][n].f_28].y * 3;
            g_6098[i].z[1][2] += g_1df8[g_9324][n].f_0c / 10 * 10 / g_9006;
            g_6098[i].z[1][3] += g_1df8[g_9324][n].f_0e / 10 * 10 / g_9006;
            g_6098[i].f_90 = 0;
            if (subgame_active == 0) {
                if (n == main_ship) {
                    g_6098[i].f_30[0][0] -= g_1df8[g_9324][n].f_0c;
                    g_6098[i].f_48[0][0] -= g_1df8[g_9324][n].f_0e;
                    g_6098[i].f_30[1][0] -= g_1df8[g_9324][n].f_0c;
                    g_6098[i].f_48[1][0] -= g_1df8[g_9324][n].f_0e;
                } else {
                    g_6098[i].f_30[0][0] += g_1df8[g_9324][n].f_0c;
                    g_6098[i].f_48[0][0] += g_1df8[g_9324][n].f_0e;
                    g_6098[i].f_30[1][0] += g_1df8[g_9324][n].f_0c;
                    g_6098[i].f_48[1][0] += g_1df8[g_9324][n].f_0e;
                }
            }
            g_6098[i].z[1][4] = LO16(g_90ea) / 10;
            if (n == main_ship && g_7090[main_ship].f_032.a != 9)
                g_9432++;
            fn_13_4eec(n, 1);
            g_6098[i].f_82 = 0;
            for (t = g_9326; t <= g_9324; t++)
                for (k = 0; k < g_9406[t]; k++)
                    g_1df8[t][k].f_55[i] = 0;
            if (g_7090[n].f_024 == 1) {
                g_6098[i].f_30[0][0] += g_7b60[g_7090[n].f_04e][g_1df8[g_9324][n].f_28].x << 3;
                g_6098[i].f_48[0][0] += g_7b60[g_7090[n].f_04e][g_1df8[g_9324][n].f_28].y << 3;
                g_6098[i].f_30[0][0] = ((int32_t)g_6098[i].f_30[0][0] + ((int32_t)(LO16(g_05a0)) << 3))
                                     % (int16_t)((LO16(g_05a0)) << 3);
                g_6098[i].f_48[0][0] = ((int32_t)g_6098[i].f_48[0][0] + ((int32_t)(HI16(g_05a0)) << 3))
                                     % (int16_t)((HI16(g_05a0)) << 3);
                if (n == main_ship)
                    fn_10_744c(0x69);
                fn_10_754a(3, 0x1e, i, 2);
                if (flag)
                    g_6098[i].z[1][5] = 15;
                if (subgame_active != 0)
                    fn_18_49d8(i, g_6098[i].z[1][4] - g_6098[i].z[1][5]);
                else if (g_9320 == 6 && g_9eb5 == 0)
                    fn_11_5626(i);
            } else {
                for (j = 0; j < 2; j++) {
                    g_6098[i].f_30[j][0] += g_7be0[g_7090[n].f_04e][j][g_1df8[g_9324][n].f_28].x << 3;
                    g_6098[i].f_48[j][0] += g_7be0[g_7090[n].f_04e][j][g_1df8[g_9324][n].f_28].y << 3;
                    g_6098[i].f_30[j][0] = ((int32_t)g_6098[i].f_30[j][0] + ((int32_t)(LO16(g_05a0)) << 3))
                                         % (int16_t)((LO16(g_05a0)) << 3);
                    g_6098[i].f_48[j][0] = ((int32_t)g_6098[i].f_48[j][0] + ((int32_t)(HI16(g_05a0)) << 3))
                                         % (int16_t)((HI16(g_05a0)) << 3);
                }
                ldx = g_6098[i].f_30[1][0] - g_6098[i].f_30[0][0];
                ldy = g_6098[i].f_48[1][0] - g_6098[i].f_48[0][0];
                g_6098[i].z[0][4] = (int16_t)ldx << 4;
                g_6098[i].z[0][5] = (int16_t)ldy << 4;
                len = (int16_t)fn_08_1290(ldx * ldx + ldy * ldy, abs32(ldx) + abs32(ldy));
                if (len <= 1)
                    len = 1;
                g_6098[i].z[0][4] = g_6098[i].z[0][4] / len;
                g_6098[i].z[0][5] = g_6098[i].z[0][5] / len;
                g_6098[i].z[1][0] = 0x1c;
                g_6098[i].z[1][1] = 0x3e;
                if (n == main_ship)
                    fn_10_744c(0x69);
                if (g_7090[n].f_0e0 && g_7090[n].f_0e1)
                    fn_10_754a(4, 0x1e, i, 2);
                else
                    fn_10_754a(3, 0x1e, i, 2);
                if (flag)
                    g_6098[i].z[1][5] = 15;
                if (subgame_active != 0)
                    fn_18_49d8(i, g_6098[i].z[1][4] - g_6098[i].z[1][5]);
                else if (g_9320 == 6 && g_9eb5 == 0)
                    fn_11_5626(i);
            }
            return;
        }
    }
}

/* Steering/thrust of ship n for command k: autopilot speed limit, then fire
 * (6874), turn (63b4) or brake [inferred]. */
/* 11:5ab6 */
void fn_11_5ab6(int16_t n, int16_t k)
{
    int16_t j;
    int16_t u6;
    int16_t u8;
    int16_t lim;
    int16_t ang;
    int16_t pa;
    int16_t pb;
    int16_t dist;
    POINT dv;
    int16_t canfire;
    int16_t strong;
    int16_t pl;
    int16_t autoon;
    int16_t u20;
    int32_t speed;
    int16_t facing;
    int16_t tf;
    int16_t ang2;
    int16_t a1;
    int16_t a2;
    int16_t accel;

    pl = 0;
    if (g_9320 == 6 && g_9eb4 == 0)
        return;
    if ((n != main_ship || g_9134 != 0) && g_9e49 == 0 && n == g_952e)
        pl = 1;
    if (g_951a != 0 && n == main_ship)
        pl = 1;
    if (n == g_952e && g_9e49 >= 3 && g_9e49 <= 6 && subgame_active == 0)
        return;
    if (g_7090[n].f_026[2] == 0)
        canfire = 0;
    else
        canfire = 1;
    if (g_7090[n].f_026[2] < 50 && (g_9320 != 6 && g_9320 != 7 || g_7090[n].f_01e > 50)
        && g_95f6 < 4)
        canfire = 0;
    if (g_7090[n].f_01e < 50) {
        canfire = 0;
        /* Both arms equal (sic): the test is dropped, its imul stays. */
        if ((g_7090[n].f_01e / 12 < 2 ? 2 : g_7090[n].f_01e / 12) >= g_95f6 / 2 || k == 1) {
            if (g_7090[n].f_01e)
                canfire = 1;
            else
                canfire = 1;
        }
        if ((n != main_ship || g_9134 != 0) && g_7090[n].f_032.a == 4 && g_7090[n].f_038 == 2)
            canfire = 1;
    }
    if (g_7090[n].f_084 > g_1e50 || g_9320 == 6 && g_7090[n].f_084 + 400 > g_1e50)
        canfire = 0;
    g_7090[n].f_01c = g_7090[n].f_01c - 1 < 1 ? 1 : g_7090[n].f_01c - 1;
    if (k == 2)
        k = g_952a = 1;
    else
        g_952a = 0;
    strong = 0;
    autoon = 1;
    if (g_7090[n].f_061 && g_7090[n].f_026[2] > 75)
        autoon = 0;
    if (g_7090[n].f_032.a == 12)
        autoon = 1;
    if (g_9320 == 6) {
        if (g_1df8[14][n].f_51)
            autoon = 1;
        else
            autoon = 0;
    }
    if (n == main_ship && g_9134 == 0 || autoon == 0) {
        if (g_9320 != 6)
            g_7090[n].f_0da = g_7090[n].f_00c * 19 / g_7090[n].f_00e;
    } else {
        if (g_96d2[g_7090[n].f_04e].f_38 == 5)
            g_7090[n].f_0da = 120;
        else
            g_7090[n].f_0da = 90;
        if (g_9208 > 1) {
            for (j = 0; j < g_9344; j++) {
                dist = fn_08_285a(&pa, &pb, g_1df8[g_9324][n].f_04, g_4f2c[j].f_0a);
                if ((g_4f2c[j].radius >> 3) + 100 > dist) {
                    if ((g_4f2c[j].radius >> 3) - 40 < dist && (g_4f2c[j].radius >> 3) + 40 > dist)
                        g_7090[n].f_0da = g_7090[n].f_0da * 7 / 3;
                    else
                        g_7090[n].f_0da = g_7090[n].f_0da * 2 / 3;
                    break;
                }
            }
        }
        if (n != main_ship || g_9134 != 0) {
            if (fn_09_88ba(g_1df8[g_9324][n].f_0c) + fn_09_88ba(g_1df8[g_9324][n].f_0e)
                > g_7090[n].f_0da) {
                if (g_94e2 < 30)
                    g_7090[n].f_0da = g_7090[n].f_0da * 5 / 4;
                else if (g_94e2 > 70 && g_94e2 < 100)
                    g_7090[n].f_0da = g_7090[n].f_0da * 4 / 5;
                else if (g_94e2 >= 100)
                    g_7090[n].f_0da = g_7090[n].f_0da * 3 / 4;
                g_7090[n].f_0da = g_7090[n].f_0da * 3 / 4;
                if (g_9156 == 2)
                    g_7090[n].f_0da = g_7090[n].f_0da * 4 / 5;
                else if (g_9156 == 0)
                    g_7090[n].f_0da = g_7090[n].f_0da * 5 / 4;
                if (g_7090[n].f_014 > 30)
                    g_7090[n].f_0da = g_7090[n].f_0da * 35 / (g_7090[n].f_014 + 10);
                lim = fn_08_35d0((int32_t)g_1df8[g_9324][n].f_0c, (int32_t)g_1df8[g_9324][n].f_0e);
                if (g_7090[n].f_0da < lim) {
                    ang = fn_08_19b0(g_1df8[g_9324][n].f_0c, g_1df8[g_9324][n].f_0e);
                    if (g_1df8[g_9324][n].f_28 == ang && g_7090[n].f_0da > (int16_t)(lim * 3) / 2)
                        strong = 1;
                    else
                        k = 5;
                }
            }
        }
    }
    if (pl) {
        g_7090[n].f_0da = g_7090[n].f_0da / 2 > 40 ? 40 : g_7090[n].f_0da / 2;
        strong = 1;
        if (fn_09_88ba(g_1df8[g_9324][n].f_0c) > 30 || fn_09_88ba(g_1df8[g_9324][n].f_0e) > 30)
            k = 1;
    }
    if ((GetAsyncKeyState(VK_DOWN) & 0x8001) && g_9134 == 0 && n == main_ship && canfire
        || k == 5 && canfire) {
        fn_11_6874(n);
    } else if ((GetAsyncKeyState(VK_UP) & 0x8001 || g_1040) && g_9134 == 0 && k == 4
               && canfire && !strong) {
        fn_11_63b4(n, k);
    } else if ((g_7090[n].f_002 && k == 3 || k == 1) && canfire && !strong) {
        fn_11_63b4(n, k);
    } else {
        if (g_7090[n].f_0e2 && subgame_active == 0)
            goto done;
        if (g_7090[n].f_002) {
            fn_11_b09c(n, g_7090[n].f_002 = 0);
            fn_13_6716(n);
        }
        accel = g_7090[n].f_00e;
        if (subgame_active != 0) {
            dv.x = -((int16_t)(accel * g_1df8[g_9324][n].f_0c) / (int16_t)(g_1df8[g_9324][n].f_44 << 2));
            dv.y = -((int16_t)(g_1df8[g_9324][n].f_0e * accel) / (int16_t)(g_1df8[g_9324][n].f_44 << 2));
        } else if (g_8ff6 && n == main_ship && g_9134 == 0) {
            dv.x = (g_1df8[g_9324][n].f_44 / -60 - g_7090[n].f_002 / 8 - g_7090[n].f_00e - 30)
                   * g_1df8[g_9324][n].f_0c / g_1df8[g_9324][n].f_44;
            dv.y = (g_1df8[g_9324][n].f_44 / -60 - g_7090[n].f_002 / 8 - g_7090[n].f_00e - 30)
                   * g_1df8[g_9324][n].f_0e / g_1df8[g_9324][n].f_44;
        } else if (g_9208 > 2) {
            speed = fn_08_35d0((int32_t)g_1df8[g_9324][n].f_0c, (int32_t)g_1df8[g_9324][n].f_0e);
            ang2 = fn_08_19b0(g_1df8[g_9324][n].f_0c, g_1df8[g_9324][n].f_0e);
            facing = g_1df8[g_9324][n].f_28;
            tf = (ang2 - facing) * 23 + 360;
            a1 = (int32_t)fn_06_720c(tf) * accel * speed / ((int32_t)g_1df8[g_9324][n].f_44 << 9);
            a2 = (int32_t)fn_06_71b2(tf) * accel * speed / (178L * g_1df8[g_9324][n].f_44);
            if (strong) {
                a1 = (int16_t)(a1 * 4) / 3;
                a2 = (int16_t)(a2 * 4) / 3;
            }
            dv.x = (g_1050[facing].x * a1 + g_1050[(int16_t)(facing + 4) % 16].x * a2) / -20;
            dv.y = (g_1050[facing].y * a1 + g_1050[(int16_t)(facing + 4) % 16].y * a2) / -20;
        } else {
            dv.x = -((int16_t)(g_1df8[g_9324][n].f_0c * accel) / (int16_t)(g_1df8[g_9324][n].f_44 << 3));
            dv.y = -((int16_t)(g_1df8[g_9324][n].f_0e * accel) / (int16_t)(g_1df8[g_9324][n].f_44 << 3));
        }
        g_1df8[g_9324][n].f_0c += dv.x;
        g_1df8[g_9324][n].f_0e += dv.y;
    }
done:
    if ((n != main_ship || g_9134 != 0) && g_7090[n].f_03a == 2 && g_7090[n].f_038 == 3) {
        if (g_7090[n].f_052 == 0 || g_7090[n].f_052 == 2) {
            if (fn_08_285a(&pa, &pb, g_1df8[g_7090[n].f_032.a][g_7090[n].f_032.b].f_04,
                           g_1df8[g_9324][n].f_04) < 400) {
                g_1df8[g_9324][n].f_0c = (int16_t)(g_1df8[g_9324][n].f_0c * 3) / 4;
                g_1df8[g_9324][n].f_0e = (int16_t)(g_1df8[g_9324][n].f_0e * 3) / 4;
            }
        }
    }
}

/* 11:2120 */
int16_t fn_11_2120(void)
{
    if (g_500a == 0 || subgame_active != 0 || g_90f4 != 1 && g_90f4 != 7)
        return 0;
    return 1;
}

/* 11:72b2 */
void fn_11_72b2(void)
{
    if (g_7090[main_ship].f_0e2 == 0 && fn_10_6b54() == 0xa7)
        g_8ff4 = 0;
}

/* 11:3396 */
void fn_11_3396(void)
{
    if (++g_93de >= ((8 - g_9208) * 16 >> 6) * g_93d6) {
        g_93de = 0;
        fn_11_33cc();
    }
}

/* 11:ae94 */
void fn_11_ae94(void)
{
    if (g_92e4 == 0) {
        if (g_7090[main_ship].cnt > 1)
            g_7090[main_ship].f_018 = 1;
        else
            g_7090[main_ship].f_018 = 0;
    }
}

/* 11:7b7a */
void fn_11_7b7a(int16_t msg, int16_t key, int32_t lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1)
                    fn_06_1c72(1);
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* 11:78bc */
void fn_11_78bc(int16_t msg, int16_t key, int32_t lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 0) {
                    g_13de = 1;
                    g_968e = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* 11:7b30 */
void fn_11_7b30(int16_t msg, int16_t key, int32_t lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 4) {
                    fn_09_0d6c();
                    fn_06_626c();
                    g_001a = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* 11:7bbc */
void fn_11_7bbc(int16_t msg, int16_t key, int32_t lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1 && g_90f4 != 7)
                    g_93aa = 0x12;
                break;
            case 0x20:
                g_9462 = -1;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* 11:b306 */
int16_t fn_11_b306(int16_t c)
{
    int16_t i;

    if (g_94fa[0] != 'Y') {
        for (i = 1; i < 0x16; i++)
            if (g_94fa[i] == c)
                return g_94e4[i];
    }
    return c;
}

/* 11:04ea */
void fn_11_04ea(void)
{
    char buf[20];
    int32_t color;
    int16_t k;

    if (g_5018 != g_1e58) {
        g_5018 = g_1e58;
        if (g_5018 == 0)
            lstrcpy(buf, "000");
        else
            fn_06_0eb8(g_1e58, buf);
        if (g_951c) {
            if (g_104c[0].a)
                color = 0x02ffc800L;
            else
                color = 0x02ffffffL;
        } else if (g_90f0)
            color = 0x0200a0ffL;
        else
            color = 0x000080ffL;
        if (LO16(g_90ea) < 0x294) {
            k = 2;
            fn_11_2154(2, color, g_93dc + g_93b8 - k, g_8e5a + 0x2d, buf);
        } else if (LO16(g_90ea) < 0x2f8) {
            k = 1;
            fn_10_94c4(k, 2, color, g_93dc + g_93b8 - k, g_8e5a + 0x31, buf);
        } else {
            k = 3;
            fn_10_94c4(0, 2, color, g_93dc + g_93b8 - k, g_8e5a + 0x31, buf);
        }
    }
}

/* 11:04a0 */
void fn_11_04a0(int16_t a)
{
    if (fn_11_2120()) {
        switch (a) {
        case 0:
            fn_11_04ea();
            break;
        case 1:
            fn_11_05fe(0);
            break;
        case 6:
            fn_11_0978();
            break;
        case 7:
            fn_11_1ef6(0);
            break;
        }
    }
}

/* 11:02f0 */
void fn_11_02f0(void)
{
    if (g_0a7a) {
        DestroyWindow(g_0a7a);
        g_0a7a = 0;
    }
    if (g_0a7c) {
        DestroyWindow(g_0a7c);
        g_0a7c = 0;
    }
    if (g_0a7e) {
        DestroyWindow(g_0a7e);
        g_0a7e = 0;
    }
}

/* 11:2ce6 */
void fn_11_2ce6(HDC dc, int16_t i)
{
    switch (i) {
    case 0:
        g_6e38[i].f_16.x = 2;
        g_6e38[i].f_16.y = 0x11;
        break;
    case 1:
        g_6e38[i].f_16.x = g_5024 - 0x38;
        g_6e38[i].f_16.y = 2;
        break;
    case 2:
        g_6e38[i].f_16.x = 2;
        g_6e38[i].f_16.y = 2;
        break;
    }
    if (g_6e38[i].f_04) {
        if (g_6e38[i].f_02 != g_6e38[i].f_00) {
            fn_11_2dac(dc, g_6e38[i].f_02, 0, i);
            g_6e38[i].f_02 = g_6e38[i].f_00;
        }
        fn_11_2dac(dc, g_6e38[i].f_00, 1, i);
    } else {
        if (g_6e38[i].f_02 != g_6e38[i].f_00) {
            fn_11_2dac(dc, g_6e38[i].f_02, 0, i);
            g_6e38[i].f_02 = g_6e38[i].f_00;
        }
        fn_11_2dac(dc, g_6e38[i].f_00, 0, i);
    }
}

/* 11:3ed8 */
void fn_11_3ed8(int16_t i)
{
    HDC dc;
    HWND hwnd;

    g_6e38[i].f_04 = g_6e38[i].f_04 == 0;
    if (i == 2)
        hwnd = g_95fc;
    else
        hwnd = g_0a7c;
    fn_11_2ce6(dc = GetDC(hwnd), i);
    ReleaseDC(hwnd, dc);
}

/* 11:4db0 */
void fn_11_4db0(void)
{
    if (g_9134 == 0 && g_7090[main_ship].f_084 < g_1e50) {
        if (GetAsyncKeyState(0x10) & 0x8000 || GetAsyncKeyState(0x20) & 0x8000
            || g_1042)
            fn_11_4e0a(main_ship);
    }
}

/* 11:785e */
void fn_11_785e(int16_t msg, int16_t key, int32_t lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_93a6 == 0)
                    fn_16_638a(0, 0L, 1);
                break;
            }
            break;
        }
        if (g_952c)
            fn_16_614c(msg, key, lparam);
        g_8e62 = 0;
    }
}

/* 11:170a */
int16_t fn_11_170a(int16_t reset)
{
    int16_t r;

    if (reset)
        g_1852 = -1;
    if (++g_1852 > 6)
        g_1852 = 0;
    switch (g_1852) {
    case 0:
    case 4:
        r = 0;
        break;
    case 2:
    case 5:
        r = 2;
        break;
    case 1:
    case 3:
    case 6:
        r = 1;
        break;
    }
    return r;
}

/* 11:2f8c */
void fn_11_2f8c(void)
{
    int16_t unused;

    if (g_5030[8]) {
        DeleteObject(g_5030[8]);
        g_5030[8] = 0;
    }
    if (g_7090[main_ship].f_018)
        g_5030[8] = fn_11_2ff6(g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]);
    if (g_0a7e)
        PostMessage(g_0a7e, WM_PAINT, 0, 0L);
}

/* 11:3e6e */
void fn_11_3e6e(void)
{
    HDC dc;
    RECT rc;

    if (g_0a76 != 4) {
        dc = GetDC(g_0a7c);
        GetClientRect(g_0a7c, &rc);
        PatBlt(dc, 0, 0, rc.right, rc.bottom, WHITENESS);
        ReleaseDC(g_0a7c, dc);
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    }
}

/* 11:772e */
void fn_11_772e(int16_t a, int16_t b)
{
    g_0a62 = 1;
    if (g_0a76 != 2) {
        g_0a76 = 2;
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        if (fn_03_065e(g_6e38[0].f_1a.b, g_6e38[0].f_1a.a, b) == 0)
            goto done;
        return;
    } else if (a) {
        g_6e38[0].f_1a.b = 3;
        g_6e38[0].f_1a.a = 0;
    }
done:
    fn_03_045a(b);
}

/* 11:7588 */
void fn_11_7588(int16_t n)
{
    if (((g_1e4c) + 4)[n] == g_6b54[n] && g_1dcc[n] != 0 && g_1dcc[n] != 3)
        return;
    g_6b54[n] = ((g_1e4c) + 4)[n];
    if (g_6b54[n] == 0)
        return;
    switch (g_1dcc[n]) {
    case 0:
        g_1042 = 1;
        break;
    case 1:
        PostMessage(g_0016, 0x101, 0xd, 0L);
        break;
    case 2:
        PostMessage(g_0016, 0x100, 9, 0L);
        break;
    case 3:
        g_103e = 1;
        break;
    case 4:
        PostMessage(g_0016, 0x100, 0x48, 0L);
        break;
    case 5:
        PostMessage(g_0016, 0x100, 0x52, 0L);
        break;
    case 6:
        PostMessage(g_0016, 0x101, 0x14, 0L);
        break;
    }
}

/* 11:7650 */
void fn_11_7650(int16_t a, int16_t b)
{
    int16_t unused;

    if (g_9134 == 0 && (b != 0 || g_1034 == 0)) {
        if (a > -1 && g_1df8[g_9324][main_ship].f_28 == a)
            g_1040 = 1;
        else {
            g_1040 = 0;
            if (a > -1 && g_1df8[g_9324][main_ship].f_28 != a) {
                if (fn_09_88ba(g_1df8[g_9324][main_ship].f_28 - a) > 8) {
                    if (g_1df8[g_9324][main_ship].f_28 < a)
                        g_1044 = 1;
                    else
                        g_1046 = 1;
                } else {
                    if (g_1df8[g_9324][main_ship].f_28 < a)
                        g_1046 = 1;
                    else
                        g_1044 = 1;
                }
            }
        }
    }
}

/* 11:7504 */
void fn_11_7504(void)
{
    uint16_t a, b;
    int16_t i;
    uint16_t x, y;
    int16_t v;

    if (g_8ff4) {
        g_103e = 0;
        g_1042 = 0;
        g_1044 = 0;
        g_1046 = 0;
        for (i = 0; i < 4; i++)
            fn_11_7588(i);
        a = (VIEW(uint16_t *, g_1e4c, 0))[0];
        b = (VIEW(uint16_t *, g_1e4c, 0))[1];
        x = a / 0x3444 > 4 ? 4 : a / 0x3444;
        y = b / 0x3444 > 4 ? 4 : b / 0x3444;
        v = g_1018[y][x];
        fn_11_7650(v, 1);
    }
}

/* 11:22fa */
LONG fn_11_22fa(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    PAINTSTRUCT ps;
    HDC dc;
    int16_t id;

    switch (msg) {
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        dc = BeginPaint(hwnd, &ps);
        fn_11_238e(hwnd, dc);
        EndPaint(hwnd, &ps);
        break;
    case WM_LBUTTONDBLCLK:
        id = GetDlgCtrlID(hwnd);
        if (id == 0xd2)
            g_93c6 = 1;
        else
            g_93c6 = 0;
        fn_02_088e();
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0L;
}

/* 11:488c */
void race_radar_background(int16_t a)
{
    int16_t i;

    world_map(g_0a72, g_0a74, a, g_9322, -1, -1, 1);
    if (g_94a8 == 0) {
        for (i = 0; i < g_9ebc[g_9322]; i++)
            world_map(g_0a72, g_0a74, a, g_9322, 8,
                      g_9eb9[g_9322] + g_9318 * 2 + i, 0);
    }
    BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
}

/* 11:adf0 */
void fn_11_adf0(void)
{
    int16_t old;
    int16_t unused;

    old = g_9524 = g_7090[main_ship].f_018;
    if (g_7090[main_ship].cnt > 1) {
        g_9524++;
        if (g_7090[main_ship].f_0b8[g_9524] == 0)
            g_9524++;
        if (g_7090[main_ship].cnt <= g_9524) {
            if (g_9134)
                g_9524 = 0;
            else
                g_9524 = 1;
        }
        g_7090[main_ship].f_018 = g_9524;
    } else
        g_7090[main_ship].f_018 = 0;
    if (g_7090[main_ship].f_0b8[old] == 3)
        g_1df8[g_9324][main_ship].f_50 = 0;
}

/* 11:3f2e */
void fn_11_3f2e(int16_t v)
{
    char buf[8];

    if (v < -250)
        LoadString(g_9212, 0x244, g_93e0, 40);
    else if (v < -80)
        LoadString(g_9212, 0x245, g_93e0, 40);
    else if (v < 80)
        LoadString(g_9212, 0x246, g_93e0, 40);
    else if (v < 250)
        LoadString(g_9212, 0x247, g_93e0, 40);
    else
        LoadString(g_9212, 0x248, g_93e0, 40);
    if (v > 0)
        lstrcat(g_93e0, " +");
    else
        lstrcat(g_93e0, " ");
    fn_06_0f1a(v / 10, buf);
    lstrcat(g_93e0, buf);
}

/* 11:4108 */
void lap_timer(void)
{
    HDC dc;
    HFONT oldfont;
    COLORREF oldtext;
    COLORREF oldbk;

    dc = GetDC(g_0a7c);
    oldfont = SelectObject(dc, g_90fe);
    SetTextAlign(dc, 0);
    if (g_90ee == 1)
        oldtext = SetTextColor(dc, 0xffffffL);
    else
        oldtext = SetTextColor(dc, 0xff00L);
    oldbk = SetBkColor(dc, 0L);
    if (g_0a76 != 2)
        fn_11_41bc(dc, 0, 0);
    else
        fn_11_41bc(dc, 0, 1);
    SetBkColor(dc, oldbk);
    SetTextColor(dc, oldtext);
    SelectObject(dc, oldfont);
    ReleaseDC(g_0a7c, dc);
}

/* 11:6aa8 */
void fn_11_6aa8(int16_t msg, int16_t wparam, int32_t lparam)
{
    if (g_8e62) {
        if (subgame_active)
            fn_18_0d4e(msg, wparam, lparam);
        else {
            if (msg == 0x101 || msg == 0x100)
                wparam = fn_11_b306(wparam);
            switch (g_90f4) {
            case 0:
                fn_11_7902(msg, wparam, lparam);
                break;
            case 1:
                fn_11_6b64(msg, wparam, lparam);
                break;
            case 3:
                fn_11_7bbc(msg, wparam, lparam);
                break;
            case 2:
                fn_11_7b7a(msg, wparam, lparam);
                break;
            case 6:
                fn_11_785e(msg, wparam, lparam);
                break;
            }
        }
        g_8e62 = 0;
    }
}

/* 11:3914 */
void fn_11_3914(int16_t type, int16_t n, HDC dc)
{
    POINT pt;

    pt.x = fn_11_1ab6(g_1df8[type][n].f_04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f_04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt))
        SetPixel(dc, pt.x, pt.y, g_1df8[type][n].f_4c);
}

/* 11:0894 */
void fn_11_0894(void)
{
    HDC dc;
    HBITMAP oldbmp;
    HPALETTE oldpal;

    if (g_1e50 >= g_5028) {
        g_5028 = g_1e50 + 300;
        if (g_9e49 == 0 && main_ship == g_952e)
            g_93d8 = g_93d8 == 0;
        else
            g_93d8 = 1;
        if (g_93da != g_93d8) {
            dc = CreateCompatibleDC(g_13dc);
            oldbmp = SelectObject(dc, g_5030[3]);
            if (g_920e)
                oldpal = SelectPalette(dc, g_920e, 0);
            BitBlt(g_13dc, g_93c0, g_8e5a + 2, 20, 20, dc, g_93d8 * 20, 0,
                   SRCCOPY);
            if (oldpal)
                SelectPalette(dc, oldpal, 0);
            SelectObject(dc, oldbmp);
            DeleteDC(dc);
            g_93da = g_93d8;
        }
    }
}

/* 11:39d8 */
void fn_11_39d8(int16_t type, int16_t n, HDC dc)
{
    POINT pt;

    pt.x = fn_11_1ab6(g_1df8[type][n].f_04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f_04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt)) {
        SelectObject(dc, g_5004[g_1df8[type][n].f_46]);
        PatBlt(dc, pt.x, pt.y, (int16_t)((int16_t)g_0a6c - 200) / 150 + 2,
               (int16_t)((int16_t)g_0a6c - 200) / 200 + 2, PATCOPY);
    }
}

/* 11:3aca */
void fn_11_3aca(int16_t type, int16_t n, HDC dc)
{
    POINT pt;
    int16_t first;

    if (n == -1) {
        n = g_9318 * 2;
        first = 1;
    } else
        first = 0;
    pt.x = fn_11_1ab6(g_1df8[type][n].f_04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f_04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (g_9318 * 2 == n && !first)
        MoveTo(dc, pt.x, pt.y);
    else
        LineTo(dc, pt.x, pt.y);
}

/* 11:3bae */
void fn_11_3bae(int16_t type, int16_t n, HDC dc)
{
    POINT pt;

    pt.x = fn_11_1ab6(g_1df8[type][n].f_04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f_04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt)) {
        if (g_0a6c > 200) {
            SelectObject(dc, g_5004[g_1df8[type][n].f_46]);
            PatBlt(dc, pt.x, pt.y, (int16_t)((int16_t)g_0a6c - 200) / 150 + 2,
                   (int16_t)((int16_t)g_0a6c - 200) / 150 + 2, PATCOPY);
        } else
            SetPixel(dc, pt.x, pt.y, g_1df8[type][n].f_4c);
    }
}

/* 11:01e0 */
void fn_11_01e0(void)
{
    int16_t i;

    for (i = 0; i < 8; i++) {
        if (g_5004[i]) {
            DeleteObject(g_5004[i]);
            g_5004[i] = 0;
        }
    }
    if (g_93cc) {
        SelectObject(g_93cc, g_9400);
        DeleteDC(g_93cc);
        g_93cc = 0;
    }
    if (g_93ce) {
        if (g_9404)
            SelectPalette(g_93ce, g_9404, 0);
        SelectObject(g_93ce, g_9402);
        DeleteDC(g_93ce);
        g_93ce = 0;
    }
    if (g_93d0) {
        SelectObject(g_93d0, g_93ca);
        if (g_920e)
            SelectPalette(g_93d0, g_93d2, 0);
        DeleteDC(g_93d0);
        DeleteObject(g_93c8);
        g_93d0 = 0;
        g_93c8 = 0;
    }
    for (i = 0; i < 12; i++) {
        if (g_5030[i]) {
            DeleteObject(g_5030[i]);
            g_5030[i] = 0;
        }
    }
    fn_11_02f0();
}

/* 11:367c */
void fn_11_367c(void)
{
    HBRUSH old;
    int16_t unused;
    int16_t type;
    int16_t i;

    SetRect(&g_5048, g_5050 - g_0a72 / 2 + 1, g_5052 - g_0a74 / 2 + 1,
            g_0a72 / 2 + g_5050 - 1, g_0a74 / 2 + g_5052 - 1);
    g_0a6c = 100;
    old = SelectObject(g_93ce, g_5004[0]);
    for (i = 0; i <= g_9316; i++)
        BitBlt(g_93ce, g_5054[i].x - 2, g_5054[i].y - 2, 5, 5,
               g_93d0, g_5054[i].x - 2, g_5054[i].y - 2, SRCCOPY);
    for (type = g_9326; type <= g_9324; type++) {
        if (type == 0xe) {
            for (i = 0; i < g_9406[type]; i++) {
                if (g_1df8[type][i].f_18 == 0
                    && (type != 8 || g_9318 * 2 + g_9ea2 > i))
                    g_1df8[type][i].f_62(type, i, g_93ce);
            }
        }
    }
    SelectObject(g_93ce, old);
}

/* 11:4c72 */
int16_t fn_11_4c72(int16_t n)
{
    if (g_7090[n].f_0e7 == 0)
        return 0;
    if ((n != main_ship || g_9134) && g_1e68 - g_7090[n].f_152 < 150)
        return 0;
    if (g_7090[n].f_0e8 == 0 && g_7090[n].f_01e < 0x78)
        return 0;
    if (g_7090[n].f_0eb == 0) {
        if (g_7090[n].f_0e8) {
            fn_12_2556(g_9324, n);
            g_7090[n].f_026[4] = 2;
            fn_07_13b2(2, g_9324, n);
            g_7090[n].f_0e8 = 0;
            g_7090[n].f_152 = g_1e68;
            return 1;
        }
        if (g_7090[n].f_026[3] == 0)
            return 0;
        if ((n != main_ship || g_9134) && g_7090[n].f_026[3] <= 0x28)
            return 0;
        g_7090[n].f_14a = g_1df8[g_9324][n].f_04;
        g_7090[n].f_14e = g_1e50;
        fn_12_2556(g_9324, n);
        g_7090[n].f_026[4] = 2;
        fn_07_13b2(1, g_9324, n);
        g_7090[n].f_0e8 = 1;
        g_7090[n].f_152 = g_1e68;
        return 1;
    }
    return 0;
}

/* Changes letter case in place by mode [inferred]. */
/* 11:3fd4 */
void fn_11_3fd4(LPSTR s, int16_t mode)
{
    int16_t i;
    int16_t unused;
    int16_t j;
    int16_t cap;

    cap = 1;
    for (i = unused = 0; i < lstrlen(s); i++) {
        switch (mode) {
        case 0:
            cap = 0;
            break;
        case 1:
            cap = 1;
            break;
        }
        if (cap) {
            if (s[i] < 0x7b && s[i] > 0x60)
                s[i] -= 0x20;
        } else {
            if (s[i] < 0x5b && s[i] > 0x40)
                s[i] += 0x20;
        }
        cap = 0;
        if (mode == 2 && s[i] == ' ')
            cap = 1;
        if ((int16_t)(lstrlen(s) - 3) > i && s[i] == ' ' && s[i + 1] == 'I' && s[i + 2] == ' ')
            cap = 1;
        if (mode == 3 && (s[i] == '.' || s[i] == '!' || s[i] == '\r' || s[i] == '\n')) {
            cap = 1;
            for (j = i + 1; j < lstrlen(s); j++) {
                if (s[j] == ' ')
                    i++;
                else
                    break;
            }
        }
        if (s[i] == '(')
            i++;
    }
}

/* Builds two small bitmaps at start-up [inferred]. */
/* 11:0344 */
void fn_11_0344(void)
{
    int16_t unused;
    HBITMAP old2;
    HBITMAP old1;
    HDC dc2;
    HDC dc1;
    int16_t i;

    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, g_5030[0]);
    dc2 = CreateCompatibleDC(dc1);
    old2 = SelectObject(dc2, g_5030[6] = CreateCompatibleBitmap(dc1, 0x54, 0x3d));
    fn_10_949c(dc2, 0, 0, 0x53, 0x3c, 2);
    for (i = 0; i < 4; i++) {
        fn_10_949c(dc2, 5, i * 14 + 5, 0x1c, 7, 3);
        BitBlt(dc2, 0x29, i * 14 + 5, 0x20, 0xb, dc1, 0, (i + 1) * 11, SRCCOPY);
    }
    SelectObject(dc2, old2);
    DeleteDC(dc2);
    dc2 = CreateCompatibleDC(dc1);
    old2 = SelectObject(dc2, g_5030[7] = CreateCompatibleBitmap(dc1, 0x1e, 0x55));
    fn_10_949c(dc2, 0, 0, 0x1d, 0x54, 2);
    fn_10_949c(dc2, 6, 0x12, 0x10, 0x3e, 3);
    BitBlt(dc2, 5, 5, 0x15, 0xb, dc1, 0, 0, SRCCOPY);
    SelectObject(dc2, old2);
    DeleteDC(dc2);
    SelectObject(dc1, old1);
    DeleteDC(dc1);
}

/* Fire the current weapon of the player's ship [inferred]. */
/* 11:ac86 */
void fn_11_ac86(void)
{
    if (g_7090[main_ship].f_0ea || g_7090[main_ship].f_0e8
        || g_1df8[g_9324][main_ship].f_2e)
        return;
    if (g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_4e == 0
        && g_7090[main_ship].f_032.a != 9)
        g_9432 += 3;
    fn_13_4eec(main_ship, 4);
    g_8e28 = g_1e50;
    if (g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_12) {
        fn_11_7c12(g_7090[main_ship].f_0b8[g_7090[main_ship].f_018], g_9324, main_ship);
        return;
    }
    switch (g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]) {
    case 5:
        fn_13_1318(g_9324, main_ship, 0x1e, 5);
        break;
    case 4:
        fn_13_1318(g_9324, main_ship, 0x1e, 4);
        break;
    case 1:
        fn_11_8a42(g_9324, main_ship);
        break;
    case 2:
        fn_11_947a(g_9324, main_ship, 2);
        break;
    case 15:
        fn_11_947a(g_9324, main_ship, 15);
        break;
    case 3:
        fn_11_9fdc(g_9324, main_ship);
        break;
    case 23:
        fn_11_9daa(g_9324, main_ship);
        break;
    case 13:
        fn_11_9078(g_9324, main_ship);
        break;
    }
}

/* 11:4b00 */
int16_t fn_11_4b00(int16_t n)
{
    if (g_7090[n].f_026[3] < 0x32 && g_7090[n].f_0ea == 0)
        return 0;
    if (g_7090[n].f_010 < 7 && g_7090[n].f_010 > 0)
        return 0;
    if ((n != main_ship || g_9134 != 0) && g_1e68 - g_7090[n].f_152 < 0x96)
        return 0;
    if (g_7090[n].f_0ea) {
        g_7090[n].f_010 = 6;
        g_9522 = -1;
        g_7090[n].f_020 = g_1df8[g_9324][n].f_22 - 2;
        g_7090[n].f_022 = 1;
        g_7090[n].f_0ea = 0;
    } else {
        g_9522 = g_7090[n].f_010 = 1;
        g_7090[n].f_020 = g_1df8[g_9324][n].f_22 - 12;
        g_7090[n].f_022 = 7;
        g_7090[n].f_0ea = 1;
    }
    fn_10_7328(g_96d2[g_7090[n].f_04e].f_36, g_96d2[g_7090[n].f_04e].f_84, LO16(g_96d2[g_7090[n].f_04e].f_a9), HI16(g_96d2[g_7090[n].f_04e].f_a9), LO8(g_96d2[g_7090[n].f_04e].f_18), LO8(g_96d2[g_7090[n].f_04e].f_1a), g_1df8[g_9324][n].f_28, g_3a38[n], 1, 0x63);
    g_7090[n].f_152 = g_1e68;
    if (g_7090[n].f_002)
        fn_11_b09c(n, 1);
    fn_10_754a(5, g_9324, n, 1);
    return 1;
}

/* 11:37a0 */
void fn_11_37a0(int16_t type, int16_t n, HDC dc)
{
    POINT pt;

    if (type == 14 && g_7090[n].f_147)
        return;
    pt.x = fn_11_1ab6(g_1df8[type][n].f_04.x) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f_04.y) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt)) {
        if (type == 14 && n == main_ship)
            SelectObject(dc, GetStockObject(WHITE_BRUSH));
        else
            SelectObject(dc, g_5004[g_1df8[type][n].f_46]);
        switch (type) {
        case 7:
            BitBlt(dc, pt.x - 2, pt.y - 2, 4, 4, g_93cc, 0x50, 0, MERGECOPY);
            break;
        default:
            BitBlt(dc, pt.x - 2, pt.y - 2, 5, 5, g_93cc,
                   g_1df8[type][n].f_28 * 5, 0, MERGECOPY);
            break;
        }
    }
    if (g_094e)
        g_5054[n] = pt;
}

/* 11:1d7c */
void fn_11_1d7c(void)
{
    int16_t j;
    int16_t i;

    if (g_5014 >= g_1e68)
        return;
    g_5014 = g_1e68 + 180;
    for (i = 0; i <= g_9316; i++) {
        if (g_1858[i] > 0) {
            if (g_96d2[g_7090[i].f_04e].f_4c != 0 && (i == main_ship || subgame_active == 0)
                && g_7090[i].f_01e > 0x5a) {
                for (j = 0; j < 4; j++) {
                    if (VIEWP(int16_t *, g_96d2[g_7090[i].f_04e].f_22, 0)[j] != -1
                        && g_7090[i].f_026[j] < 0x52
                        && (j != 3 || g_7090[i].f_026[j] != 0 && g_7090[i].f_026[j] != 0x32)) {
                        if (i != main_ship || j == 3)
                            g_7090[i].f_026[j]++;
                        else
                            g_7090[i].f_026[j] += 2;
                        if (g_9320 == 6)
                            g_7090[i].f_026[j]++;
                        g_7090[i].f_01e -= 2;
                    }
                }
            }
            g_7090[i].f_08c = max((0x4b - g_7090[i].f_026[1]) * 4, 0x1b) / 0x1b;
            g_1858[i]--;
        } else
            g_1858[i] = max(g_1df8[14][i].f_44 / -75 + 9, 1);
    }
}

/* 11:0978 */
void fn_11_0978(void)
{
    int16_t i;
    int16_t v;
    HBRUSH oldbrush;
    HDC dc;
    HBITMAP oldbmp;
    HPALETTE oldpal;

    v = min(g_7090[main_ship].f_01e / (g_96d2[g_7090[main_ship].f_04e].f_1e / 60), 59);
    if (v == g_93d4)
        return;
    g_93d4 = v;
    if (g_502c < g_1e50) {
        for (i = 250; i > 60; i -= 60) {
            if (g_1840[main_ship] >= i && g_7090[main_ship].f_01e < i) {
                fn_03_06ec(main_ship, 7, 0, 9);
                g_502c = g_1e50 + 30000;
            }
        }
    }
    g_1840[main_ship] = g_7090[main_ship].f_01e;
    if (g_93d4 < 60) {
        oldbrush = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
        PatBlt(g_13dc, g_93bc + 8, g_8e5a + 0x13, 0xe, 60 - g_93d4, PATCOPY);
        SelectObject(g_13dc, oldbrush);
    }
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_5030[5]);
    if (g_920e)
        oldpal = SelectPalette(dc, g_920e, 0);
    BitBlt(g_13dc, g_93bc + 8, g_8e5a - g_93d4 + 0x4f, 0xd, g_93d4, dc, 0,
           60 - g_93d4, SRCCOPY);
    if (oldpal)
        SelectPalette(dc, oldpal, 0);
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
}

/* Turn the player's ship with the arrow keys [inferred]. */
/* 11:592a */
void fn_11_592a(void)
{
    int16_t key;                    /* stored value is never read */

    if (g_1034 == 0)
        return;
    if (g_9320 == 6 && g_9eb4 == 0 || g_9134 || g_7090[main_ship].f_0eb
        || g_7090[main_ship].f_084 >= g_1e50)
        return;
    if ((key = GetAsyncKeyState(VK_RIGHT) & 0x8000) || g_1046) {
        if (GetAsyncKeyState(VK_MENU) & 0x8000) {
            g_7090[main_ship].f_012++;
            if (g_7090[main_ship].f_012 > 1)
                g_7090[main_ship].f_012 = 1;
        } else {
            g_1df8[g_9324][main_ship].f_26 = 0;
            g_7090[main_ship].f_012 = 0;
            g_1df8[g_9324][main_ship].f_28++;
            if (g_1df8[g_9324][main_ship].f_28 > 15)
                g_1df8[g_9324][main_ship].f_28 = 0;
        }
        if (g_238e == 0)
            fn_07_1208();
        g_9138 = 1;
    }
    if ((key = GetAsyncKeyState(VK_LEFT) & 0x8000) || g_1044) {
        if (GetAsyncKeyState(VK_MENU) & 0x8000) {
            g_7090[main_ship].f_012--;
            if (g_7090[main_ship].f_012 < -1)
                g_7090[main_ship].f_012 = -1;
        } else {
            g_1df8[g_9324][main_ship].f_26 = 0;
            g_7090[main_ship].f_012 = 0;
            g_1df8[g_9324][main_ship].f_28--;
            if (g_1df8[g_9324][main_ship].f_28 < 0)
                g_1df8[g_9324][main_ship].f_28 = 15;
        }
        if (g_238e == 0)
            fn_07_1208();
        g_9138 = 1;
    }
}

/* Draw a string with the digit/letter bitmap font [inferred].
 * Callers see a char first parameter (they push the literal), the body
 * reads it as int: old-style definition (warning C4028 expected). */
/* 11:2154 */
void fn_11_2154(int16_t align, int32_t color, int16_t x, int16_t y, LPSTR s)
{
    HBRUSH oldbrush;
    HDC dc;
    HBITMAP oldbmp;
    int16_t unused;
    int16_t x0;
    int16_t i;
    int16_t w;
    int16_t c;
    int16_t cw;

    w = 10;
    switch (align) {
    case 0:
        x0 = x;
        break;
    case 6:
        x0 = x - (int16_t)(lstrlen(s) * w) / 2;
        break;
    case 2:
        x0 = x - lstrlen(s) * w;
        break;
    }
    oldbrush = SelectObject(g_13dc, CreateSolidBrush(color));
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_5030[4]);
    for (i = 0; i < lstrlen(s); i++) {
        cw = 10;
        c = s[i];
        if (c > '/' && c < ':') {
            c -= '0';
            BitBlt(g_13dc, i * 10 + x0, y, 10, 10, dc, c * 10, 0, 0xc00746L);
        } else {
            switch (c) {
            case 'S':
                c = 5;
                break;
            case 'C':
                c = 0xb;
                break;
            case 'O':
                c = 0;
                break;
            case 'R':
                c = 0xc;
                break;
            case 'E':
                c = 0xd;
                break;
            default:
                c = 100;
                break;
            }
            if (c == 100)
                PatBlt(g_13dc, (i + 1) * 10 - cw + x0, y, cw, 10, BLACKNESS);
            else
                BitBlt(g_13dc, (i + 1) * 10 - cw + x0, y, cw, 10, dc,
                       (c + 1) * 10 - cw, 0, 0xc00746L);
        }
    }
    DeleteObject(SelectObject(g_13dc, oldbrush));
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
}

/* Redraw the weapon panel of ship n [inferred]. */
/* 11:3cc2 */
void fn_11_3cc2(int16_t n)
{
    HDC dc1;
    HDC dc2;
    HBITMAP old1;
    HBITMAP old2;
    HBRUSH oldbrush;
    int16_t i;
    int16_t k;
    HDC dc3;
    HBITMAP old3;

    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, g_5030[0]);
    dc2 = CreateCompatibleDC(dc1);
    old2 = SelectObject(dc2, g_5030[6]);
    for (i = 0; i < 4; i++) {
        if (i == 3) {
            if (g_7090[n].f_0e9)
                k = 5;
            else if (g_7090[n].f_0e7)
                k = 4;
            else
                k = VIEWP(int16_t *, g_96d2[g_7090[n].f_04e].f_22, 0)[i];
        } else
            k = VIEWP(int16_t *, g_96d2[g_7090[n].f_04e].f_22, 0)[i];
        if (k == -1) {
            oldbrush = SelectObject(dc2, GetStockObject(LTGRAY_BRUSH));
            PatBlt(dc2, 0x29, i * 14 + 5, 0x20, 0xb, PATCOPY);
            SelectObject(dc2, oldbrush);
        } else
            BitBlt(dc2, 0x29, i * 14 + 5, 0x20, 0xb, dc1, 0, (k + 1) * 11,
                   SRCCOPY);
    }
    SelectObject(dc2, old2);
    DeleteDC(dc2);
    SelectObject(dc1, old1);
    DeleteDC(dc1);
    if (g_951a) {
        dc3 = CreateCompatibleDC(g_13dc);
        old3 = SelectObject(dc3, g_5030[6]);
        BitBlt(g_13dc, g_93c0, g_8e5a + 0x18, 0x54, 0x3d, dc3, 0, 0, SRCCOPY);
        SelectObject(dc3, old3);
        DeleteDC(dc3);
        fn_11_05fe(1);
    } else {
        fn_11_0afe();
        if (fn_13_65f2(0))
            g_8f64 = 1;
        else
            g_8f64 = 0;
    }
}

/* Format a race time (t in ticks [inferred]) as m:ss:cc or s.cc. */
/* 11:4928 */
void fn_11_4928(int16_t mode, DWORD t, LPSTR out)
{
    DWORD mins;
    DWORD secs;
    DWORD t2;
    DWORD m;
    char buf[40];

    if (t == 0) {
        if (mode)
            lstrcpy(out, "---.---  ");
        else
            lstrcpy(out, "---:---:---  ");
        return;
    }
    t *= 278;
    t /= 10;
    lstrcpy(out, "");
    if (mode == 0) {
        mins = t / 60000;
        m = mins * 60000;
        t -= m;
        fn_06_0ef8(mins, buf);
        if (mins < 10)
            lstrcat(out, "0");
        lstrcat(out, buf);
        lstrcat(out, ":");
    }
    secs = t / 1000;
    m = secs * 1000;
    t -= m;
    fn_06_0ef8(secs, buf);
    if (secs < 10 && mode == 0)
        lstrcat(out, "0");
    lstrcat(out, buf);
    if (mode)
        lstrcat(out, ".");
    else
        lstrcat(out, ":");
    t2 = t;
    fn_06_0ef8(t2 / 10, buf);
    if (t < 100)
        lstrcat(out, "0");
    lstrcat(out, buf);
    if (mode == 1) {
        LoadString(g_9212, 0x30df, buf, 40);
        lstrcat(out, " ");
        lstrcat(out, buf);
    } else if (mode == 0)
        lstrcat(out, "  ");
}

/* Load the bitmaps and brushes of the cockpit panel [inferred]. */
/* 11:0000 */
void fn_11_0000(void)
{
    int16_t unused;
    int16_t g;

    if (g_5030[9] == 0) {
        fn_10_740c();
        g_501c = (int32_t)(LO16(g_05a0)) * 100;
        g_5020 = (int32_t)(HI16(g_05a0)) * 100;
        g_5030[9] = CreateCompatibleBitmap(g_13dc, g_0a72, g_0a74);
        g_5030[1] = fn_10_6d38("METAL");
        g_5030[2] = fn_10_6c02(0xfa, 0, -1);
        g_5030[3] = fn_10_6c02(0xf0, 0, -1);
        fn_10_740c();
        g_5030[10] = fn_10_6c02(0x2d, 0, -1);
        if (g_90f0)
            g_5030[5] = fn_10_6c02(0x104, 0, -1);
        else
            g_5030[5] = fn_10_6c02(0x104, 3, -1);
        g_5030[4] = fn_10_6d38("DIGITAL");
        g_5030[11] = fn_10_6d38("RADSHIP");
        g_5030[0] = fn_10_6d38("SYSTEMS");
        fn_10_740c();
        g_500a = CreatePatternBrush(g_5030[1]);
        if (g_90f0)
            g = 0x60;
        else
            g = 0x40;
        g_5004[0] = CreateSolidBrush(PALETTERGB(0, g, 0));
        g_5004[7] = CreateSolidBrush(PALETTERGB(0, 0xc8, 0xff));
        g_5004[6] = CreateSolidBrush(RGB(0x80, 0xa0, 0xff));
        if (g_90f0)
            g = 0x80;
        else
            g = 0x3f;
        g_5004[2] = CreateSolidBrush(PALETTERGB(0, g, 0xff));
        g_5004[4] = CreateSolidBrush(RGB(0xc0, 0xc0, 0xc0));
        g_5004[1] = CreateSolidBrush(RGB(0xff, 0xc0, 0x40));
        g_5004[5] = CreateSolidBrush(PALETTERGB(0xff, 0x40, 0));
        g_93ce = CreateCompatibleDC(g_13dc);
        g_9402 = SelectObject(g_93ce, g_5030[9]);
        g_93cc = CreateCompatibleDC(g_13dc);
        g_9400 = SelectObject(g_93cc, g_5030[11]);
        if (g_920e)
            g_9404 = SelectPalette(g_93ce, g_920e, 0);
        fn_10_740c();
        fn_11_0344();
        g_93d8 = 1;
    }
}

/* Draw one segment of a seven-segment digit [inferred]. */
/* 11:2dac */
void fn_11_2dac(HDC dc, int16_t seg, int16_t on, int16_t i)
{
    POINT pt;
    HPEN old;

    pt = g_6e38[i].f_16;
    if (on)
        old = SelectObject(dc, CreatePen(PS_SOLID, 1, g_6e38[i].f_0c));
    else
        old = SelectObject(dc, GetStockObject(BLACK_PEN));
    switch (seg) {
    case 0:
        MoveTo(dc, pt.x + 14, pt.y);
        LineTo(dc, pt.x + 29, pt.y);
        break;
    case 1:
        MoveTo(dc, pt.x + 29, pt.y);
        LineTo(dc, pt.x + 43, pt.y);
        LineTo(dc, pt.x + 43, pt.y + 14);
        break;
    case 2:
        MoveTo(dc, pt.x + 43, pt.y + 14);
        LineTo(dc, pt.x + 43, pt.y + 29);
        break;
    case 3:
        MoveTo(dc, pt.x + 29, pt.y + 43);
        LineTo(dc, pt.x + 43, pt.y + 43);
        LineTo(dc, pt.x + 43, pt.y + 29);
        break;
    case 4:
        MoveTo(dc, pt.x + 14, pt.y + 43);
        LineTo(dc, pt.x + 29, pt.y + 43);
        break;
    case 5:
        MoveTo(dc, pt.x + 14, pt.y + 43);
        LineTo(dc, pt.x, pt.y + 43);
        LineTo(dc, pt.x, pt.y + 29);
        break;
    case 6:
        MoveTo(dc, pt.x, pt.y + 14);
        LineTo(dc, pt.x, pt.y + 29);
        break;
    case 7:
        MoveTo(dc, pt.x + 14, pt.y);
        LineTo(dc, pt.x, pt.y);
        LineTo(dc, pt.x, pt.y + 14);
        break;
    }
    if (on)
        DeleteObject(SelectObject(dc, old));
    else
        SelectObject(dc, old);
}

/* Cheat keys [inferred]. */
/* 11:72e0 */
int16_t handle_cheat_key(int16_t key)
{
    switch (key) {
    case 'r':
        g_6e24[g_931c].f_32 = 6;
        fn_10_754a(0x20, g_9324, main_ship, 1);
        break;
    case 's':
        g_913e = 2;
        break;
    case 't':
        if (g_9316 < 8)
            fn_13_adbe(main_ship, 0x16, 0x6d);
        break;
    case 'u':
        g_104a = 1;
        report_crime(main_ship, rand() % 10);
        break;
    case 'v':
        fn_12_6d64(main_ship, 0x16);
        fn_12_6d64(main_ship, 0x17);
        fn_12_6d64(main_ship, 0x1a);
        fn_10_744c(0x25);
        break;
    case 'w':
        g_104c[0].a = g_104c[0].a == 0;
        g_5018 = -1;
        break;
    case 'x':
        g_1048 = 0;
        break;
    case '1':
        if (g_9320 == 6) {
            fn_04_2da2();
            return g_7090[main_ship].f_0da - g_9ea0 - 1;
        }
        break;
    case '2':
        if (g_9320 == 7)
            g_6670[0].f_1a = -1;
        break;
    case '3':
        if (g_9316 < 8)
            fn_13_adbe(main_ship, 4, 0x6a);
        break;
    case '4':
        if (g_9316 < 8)
            fn_13_adbe(main_ship, 3, 0x69);
        break;
    case '5':
        if (g_92e8) {
            g_1318 = 1;
            g_1df8[14][main_ship].f_54 = 0;
            g_913e = 1;
            fn_03_06ec(main_ship, 7, 0, 0xb5);
        }
        break;
    case '6':
        g_7090[main_ship].f_01e = min(g_96d2[g_7090[main_ship].f_04e].f_1e,
                                 g_7090[main_ship].f_01e + 250);
        fn_10_754a(0x71, g_9324, main_ship, 1);
        break;
    case '7':
        g_104c[0].b = g_104c[0].b == 0;
        break;
    case '8':
        g_7090[main_ship].f_0ce += 100;
        fn_10_754a(0x23, g_9324, main_ship, 1);
        break;
    case '9':
        g_6e24[g_931c].f_33 = 6;
        fn_10_754a(0x20, g_9324, main_ship, 1);
        break;
    }
}

/* Draw the race clock (minutes and seconds) [inferred]. */
/* 11:1ef6 */
void fn_11_1ef6(int16_t force)
{
    char buf[4];
    char sbuf[4];
    char mbuf[4];
    HBRUSH oldbrush;
    HDC dc;
    HBITMAP oldbmp;
    int16_t unused;
    int16_t i;
    int16_t sec;
    int16_t min;
    int16_t a;
    int16_t b;

    if (!fn_11_2120())
        return;
    g_934e = g_1e68 / 36;
    min = g_934e / 60;
    sec = g_934e % 60;
    if (sec != g_1868)
        force = 1;
    if (!force)
        return;
    g_1868 = sec;
    fn_06_0f1a(min, buf);
    if (min < 10) {
        lstrcpy(mbuf, " ");
        lstrcat(mbuf, buf);
    } else
        lstrcpy(mbuf, buf);
    fn_06_0f1a(sec, buf);
    if (sec < 10) {
        lstrcpy(sbuf, "0");
        lstrcat(sbuf, buf);
    } else
        lstrcpy(sbuf, buf);
    oldbrush = SelectObject(g_13dc, CreateSolidBrush(RGB(0, 0xff, 0)));
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_5030[4]);
    for (i = 0; i < lstrlen(mbuf); i++) {
        b = 10;
        a = mbuf[i];
        if (a > '/' && a < ':')
            BitBlt(g_13dc, i * 10 + g_93c2 + 5, g_8e5a + 4, 10, 10, dc,
                   (a -= '0') * 10, 0, 0xc00746L);
        else
            PatBlt(g_13dc, i * 10 - b + g_93c2 + 15, g_8e5a + 4, b, 10,
                   BLACKNESS);
    }
    for (i = 0; i < lstrlen(sbuf); i++) {
        b = sbuf[i];
        if (b > '/' && b < ':') {
            b -= '0';
            BitBlt(g_13dc, (i + 3) * 10 + g_93c2, g_8e5a + 4, 10, 10, dc,
                   b * 10, 0, MERGECOPY);
        }
    }
    DeleteObject(SelectObject(g_13dc, oldbrush));
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
}

/* Key handler of the debriefing screen [inferred]. */
/* 11:7902 */
void fn_11_7902(int16_t msg, int16_t key, int32_t lparam)
{
    int16_t v;
    int16_t r;

    if (g_8e62) {
        switch (msg) {
        case 0x101:
            if (g_90f8 && g_8e5e == 0)
                g_90f8 = 0;
            switch (key) {
            case 'S':
                fn_10_744c(0x6e);
                fn_10_744c(0x13);
                if (!fn_10_82a2(4))
                    break;
                fn_06_92b8();
            case 'D':
                fn_10_38e0();
            case 'C':
                g_939a = fn_10_804c(1);
                g_939e = fn_10_804c(0);
                if (g_95b8 >= 6 || g_120e != 0)
                    break;
                g_6e28 = g_1e50;
                g_95b8 = 5;
                if (key == 'D')
                    g_9516 = 1;
                else
                    g_9516 = 0;
                break;
            case 'R':
                if (g_920c == 0 || g_920c == 1) {
                    fn_10_744c(0x51);
                    if (fn_10_80a8())
                        fn_10_885e(0);
                }
                break;
            case 0x1b:
                fn_10_744c(0x6e);
                if (g_95b8 == 6) {
                    g_92d4 = 9;
                    break;
                }
                v = GetPrivateProfileInt(g_9690, "Accept", 0, g_96a9);
                if (g_920c == 2 && v != 42) {
                    fn_10_744c(0x13);
                    fn_10_82a2(0xb);
                    break;
                }
                if (g_90f4 == 1)
                    break;
                if (g_120e != 0 || g_1212 == 0)
                    break;
                if (g_95b8 < 6) {
                    g_92e4 = 0;
                    fn_10_744c(0x13);
                    r = fn_10_82a2(1);
                    if (r == 0)
                        break;
                    if (r == 2) {
                        if (!fn_06_930a())
                            return;
                    } else
                        fn_10_38e0();
                    fn_10_7480(-1, 1);
                    if (g_8f70 < 2) {
                        g_95b8 = 6;
                        fn_15_0cb0();
                    } else {
                        g_95b8 = 7;
                        if (g_92e4 == 0)
                            g_91f8 = 0;
                        fn_06_1d9a();
                        fn_06_1c72(1);
                    }
                } else if (g_95b8 == 6)
                    g_92d4 = 9;
                break;
            case ' ':
                if (g_95b8 < 6 && g_120e == 0)
                    g_6e28 = g_1e50;
                else if (g_92d4 < 2 && g_92d4 > 0)
                    fn_15_1584(1);
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* 11:9daa */
void fn_11_9daa(int16_t type, int16_t n)
{
    int16_t i;

    if (g_238c)
        return;
    if (type == g_9324 && g_7090[n].f_01e < 250)
        return;
    g_2408 = g_1e50 + 2000;
    VIEW(int32_t, g_238c, 0) = 0x60009L;    /* g_238c = 9, g_238e = 6 */
    for (i = 0; i <= g_9316; i++) {
        if (i == n && type == g_9324)
            continue;
        if (subgame_active && i != 0)
            continue;
        if (i & 1)
            g_1df8[g_9324][i].f_26 = 1;
        else
            g_1df8[g_9324][i].f_26 = -1;
        g_7090[i].f_0e2 = 1;
        g_7090[i].f_084 = g_1e50 + 3500;
    }
    if (!subgame_active) {
        for (i = 0; i < g_9406[8]; i++) {
            if (i == n && type == 8)
                continue;
            if (i & 1)
                g_1df8[8][i].f_26 = 1;
            else
                g_1df8[8][i].f_26 = -1;
            g_3d50[i].f_04 = g_1e50 + 3000;
        }
        fn_11_9078(type, n);
        if (g_92e8) {
            if (g_9316 == 0) {
                g_1df8[14][main_ship].f_54 = 1;
                fn_13_adbe(main_ship, 0x13, 0xb4);
                for (i = 1; i < g_7090[main_ship].cnt; i++)
                    if (g_7090[main_ship].f_0b8[i] < 0x16)
                        fn_12_6d64(1, g_7090[main_ship].f_0b8[i]);
                g_7090[1].f_024 = g_7090[1].f_00a = g_7090[main_ship].f_00a;
                g_1df8[14][1].f_0c = g_1df8[14][1].f_0e = g_7090[1].f_01e = 0;
                g_8e30 = g_1e50 + 15000;
                g_7090[1].f_000 = 0;
            } else {
                g_1df8[14][main_ship].f_54 = 0;
                g_7090[1].f_01e = g_96d2[g_7090[1].f_04e].f_1e;
                g_7090[1].f_054 = 14;
                g_7090[1].f_056 = main_ship;
                g_7090[1].f_052 = 2;
                g_7090[1].f_094 = g_1e50 + 300;
            }
        }
    }
    if (type == g_9324)
        g_7090[n].f_01e -= 200;
}

/* Slow down object n [inferred]. */
/* 11:6874 */
void fn_11_6874(int16_t n)
{
    POINT d;

    if (g_1df8[g_9324][n].f_0c == 0 && g_1df8[g_9324][n].f_0e == 0)
        return;
    g_1df8[g_9324][n].f_26 = 0;
    if (g_7090[n].f_090 < g_1e50) {
        g_7090[n].f_090 = g_1e50 + 250;
        if (g_7090[n].f_002)
            fn_11_b09c(n, g_7090[n].f_002 = 0);
    }
    d.x = -((int32_t)(g_1df8[g_9324][n].f_44 / 30 + g_7090[n].f_00c / 8
                  + g_7090[n].f_00e + 30) * g_1df8[g_9324][n].f_0c
           / g_1df8[g_9324][n].f_44);
    d.y = -((int32_t)(g_1df8[g_9324][n].f_44 / 30 + g_7090[n].f_00c / 8
                  + g_7090[n].f_00e + 30) * g_1df8[g_9324][n].f_0e
           / g_1df8[g_9324][n].f_44);
    if (fn_09_88ba(g_1df8[g_9324][n].f_0c) < fn_09_88ba(d.x))
        d.x = -g_1df8[g_9324][n].f_0c;
    if (fn_09_88ba(g_1df8[g_9324][n].f_0e) < fn_09_88ba(d.y))
        d.y = -g_1df8[g_9324][n].f_0e;
    if (d.x == 0 && d.y == 0) {
        if (g_1df8[g_9324][n].f_0c > 0)
            d.x = -1;
        else if (g_1df8[g_9324][n].f_0c < 0)
            d.x = 1;
        if (g_1df8[g_9324][n].f_0e > 0)
            d.y = -1;
        else if (g_1df8[g_9324][n].f_0e < 0)
            d.y = 1;
    }
    g_1df8[g_9324][n].f_0c += d.x;
    g_1df8[g_9324][n].f_0e += d.y;
}

/* Builds a bitmap for 0x50-record a [inferred]. */
/* 11:2ff6 */
HBITMAP fn_11_2ff6(int16_t a)
{
    int16_t u4;
    HDC dc;
    HDC sdc;
    HBITMAP bmp;
    int16_t uc;
    HBITMAP src;
    HBITMAP oldsrc;
    HBITMAP old;
    int16_t u14;
    HPALETTE oldpal;
    HPALETTE oldspal;
    int16_t kind;
    int16_t h;
    int16_t w;
    int16_t s;
    int16_t bw;
    int16_t width;
    int16_t height;
    int16_t s2;
    int16_t bh;
    int16_t dy;
    int16_t by;
    int16_t sy;
    int16_t sx;
    BITMAP bm;

    if (a == 0)
        return 0;
    if ((g_2f4c[a].f_12 == 0 || g_2f4c[a].f_06 == -1) && a != 0x18) {
        bmp = fn_10_6c02(g_2f4c[a].f_0a, 0, -1);
    } else {
        if (g_2f4c[a].f_12) {
            w = g_2f4c[a].f_00;
            h = g_2f4c[a].f_02;
        } else if (a == 0x18) {
            w = (g_6e24)[g_931c].f_7a;
            h = (g_6e24)[g_931c].f_7b;
        }
        if (g_2f4c[a].f_1c) {
            switch (g_2f4c[a].f_1c) {
            case 1:
            case 4:
                src = fn_10_6c02(0xbf, 0, -1);
                break;
            case 2:
                src = fn_10_6c02(0xc4, 0, -1);
                break;
            case 3:
                src = fn_10_6c02(0xc5, 0, -1);
                break;
            }
        } else if (a == 0x18)
            src = fn_10_6c02(0xbd, 0, -1);
        else
            src = 0;
        if (src) {
            GetObject(src, sizeof bm, &bm);
            bw = bm.bmWidth;
            bh = bm.bmHeight;
            if (a == 0x18)
                s = w;
            else
                s = w + w;
            height = max(bh, s);
            s2 = s;
            if (height > s2) {
                dy = (int16_t)(height - s2) / 2;
                by = 0;
            } else {
                by = (int16_t)(height - bh) / 2;
                dy = 0;
            }
            width = bw + s;
            sdc = CreateCompatibleDC(g_13dc);
            if (g_920e)
                oldspal = SelectPalette(sdc, g_920e, 0);
            oldsrc = SelectObject(sdc, src);
        } else {
            kind = g_2f4c[a].f_08;
            s2 = height = s = width =
                kind == 0xc4 || kind == 0xc6 || kind == 0xc3
                ? g_2f4c[a].f_00 * 4 / 3 : g_2f4c[a].f_00 * 2;
            dy = by = bw = bh = 0;
        }
        bmp = CreateCompatibleBitmap(g_13dc, width, height);
        dc = CreateCompatibleDC(g_13dc);
        if (g_920e)
            oldpal = SelectPalette(dc, g_920e, 0);
        old = SelectObject(dc, bmp);
        PatBlt(dc, 0, 0, width, height, BLACKNESS);
        kind = g_2f4c[a].f_08;
        if (w & 1) {
            w++;
            h = 4;
        } else
            h = 6;
        h = (h << g_9156) >> 1;
        w = (w << g_9156) >> 1;
        if (g_2f4c[a].f_0e == 5 || kind == 0xc6 || kind == 0xc3) {
            sx = sy = h;
        } else {
            if (g_2f4c[a].f_0e == 4)
                sx = (g_2f4c[a].f_2e - 1) * (w + h) + h;
            else
                sx = w * 4 + h * 5;
            sy = h;
        }
        SetStretchBltMode(dc, 3);
        if (a == 0x18)
            StretchBlt(dc, 0, dy, s, s2, g_3a38[main_ship], sx, sy, w, w,
                       SRCCOPY);
        else
            StretchBlt(dc, 0, dy, s, s2, g_39e8[g_2f4c[a].f_04], sx, sy, w, w,
                       SRCCOPY);
        if (src) {
            BitBlt(dc, s, by, bw, bh, sdc, 0, 0, SRCCOPY);
            if (g_920e)
                SelectPalette(sdc, oldspal, 0);
            SelectObject(sdc, oldsrc);
            DeleteDC(sdc);
            DeleteObject(src);
            src = 0;
        }
        if (g_920e)
            SelectPalette(dc, oldpal, 0);
        SelectObject(dc, old);
        DeleteDC(dc);
        dc = 0;
    }
    return bmp;
}

/* Redraws the radar view [inferred]. */
/* 11:33cc */
void fn_11_33cc(void)
{
    int16_t i;
    int16_t j;
    HBRUSH old;
    RECT r;
    int16_t got;

    if (g_93ce == 0 || !fn_11_2120())
        return;
    g_93d6 = g_9008 * 1000 / (g_0a6c + 500);
    g_93d6 = g_93d6 > 26 ? 26 : g_93d6;
    got = 0;
    if (g_13dc == 0) {
        got = 1;
        g_13dc = GetDC(g_0016);
    }
    if (g_094e)
        fn_11_367c();
    else {
        PatBlt(g_93ce, 0, 0, g_0a72, g_0a74, BLACKNESS);
        for (i = 0; i < g_9158; i++) {
            r.left = fn_11_1ab6(g_2400) * g_0a6c * g_0a64 / g_501c + g_5050;
            r.top = fn_11_1b44(g_2402) * g_0a6c * g_0a68 / g_5020 + g_5052;
            r.right = fn_11_1ab6((int32_t)g_2400 + (LO16(g_90ea) << g_9150))
                      * g_0a6c * g_0a64 / g_501c + g_5050;
            r.bottom = fn_11_1b44((int32_t)g_2402 + (HI16(g_90ea) << g_9150))
                       * g_0a6c * g_0a68 / g_5020 + g_5052;
            FrameRect(g_93ce, &r, g_5004[0]);
        }
        SetRect(&g_5048, g_5050 - g_0a72 / 2 + 1, g_5052 - g_0a74 / 2 + 1,
                g_0a72 / 2 + g_5050 - 1, g_0a74 / 2 + g_5052 - 1);
        old = SelectObject(g_93ce, g_5004[0]);
        for (i = g_9326; i <= g_9324; i++)
            for (j = 0; j < g_9406[i]; j++)
                if (g_1df8[i][j].f_18 == 0 && g_1df8[i][j].f_44 > 0)
                    g_1df8[i][j].f_62(i, j, g_93ce);
        SelectObject(g_93ce, old);
    }
    BitBlt(g_13dc, LO16(g_90ea) / 2 - 0x2b, g_8e5a + 7, g_0a72, g_0a74, g_93ce,
           0, 0, SRCCOPY);
    if (got) {
        ReleaseDC(g_0016, g_13dc);
        g_13dc = 0;
    }
}

/* Draws a bevelled frame of depth c around (l, t, rt, b); c == -1 gives a
 * depth-2 frame with a light grey fill [inferred]. */
/* 11:1774 */
void fn_11_1774(int16_t c, int16_t l, int16_t t, int16_t rt, int16_t b)
{
    RECT r;
    HPEN old;
    HBRUSH oldbr;
    int16_t i;
    int16_t fill;

    if (c == -1) {
        c = 2;
        fill = 1;
    } else
        fill = 0;
    SetRect(&r, l, t, rt, b);
    old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, PALETTERGB(128, 128, 128)));
    MoveTo(g_13dc, r.left, r.bottom);
    LineTo(g_13dc, r.right, r.bottom);
    MoveTo(g_13dc, r.left + 1, r.bottom - 1);
    LineTo(g_13dc, r.right - 1, r.bottom - 1);
    LineTo(g_13dc, r.right - 1, r.top);
    MoveTo(g_13dc, r.left + c + 2, r.bottom - c - 3);
    LineTo(g_13dc, r.left + c + 2, r.top + c + 2);
    LineTo(g_13dc, r.right - c - 2, r.top + c + 2);
    if (c == 4) {
        MoveTo(g_13dc, r.right, r.bottom);
        LineTo(g_13dc, r.right, r.top);
    }
    DeleteObject(SelectObject(g_13dc, old));
    if (c != 4) {
        old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
        MoveTo(g_13dc, r.right, r.bottom);
        LineTo(g_13dc, r.right, r.top);
        SelectObject(g_13dc, old);
    }
    old = SelectObject(g_13dc, GetStockObject(WHITE_PEN));
    MoveTo(g_13dc, r.left + c + 2, r.bottom - c - 2);
    LineTo(g_13dc, r.right - c - 2, r.bottom - c - 2);
    LineTo(g_13dc, r.right - c - 2, r.top + c + 1);
    MoveTo(g_13dc, r.left, r.bottom);
    LineTo(g_13dc, r.left, r.top);
    LineTo(g_13dc, r.right, r.top);
    MoveTo(g_13dc, r.left + 1, r.bottom - 1);
    LineTo(g_13dc, r.left + 1, r.top + 1);
    LineTo(g_13dc, r.right - 1, r.top + 1);
    SelectObject(g_13dc, old);
    old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, PALETTERGB(192, 192, 192)));
    if (fill)
        oldbr = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
    else
        oldbr = SelectObject(g_13dc, GetStockObject(NULL_BRUSH));
    for (i = 0; i < c; i++)
        Rectangle(g_13dc, i + r.left + 2, i + r.top + 2, r.right - i - 1,
                  r.bottom - i - 1);
    DeleteObject(SelectObject(g_13dc, old));
    SelectObject(g_13dc, oldbr);
    SetPixel(g_13dc, r.right, r.top, PALETTERGB(128, 128, 128));
    SetPixel(g_13dc, r.right - 1, r.top + 1, PALETTERGB(192, 192, 192));
    SetPixel(g_13dc, r.left, r.bottom, PALETTERGB(192, 192, 192));
    SetPixel(g_13dc, r.left + 1, r.bottom - 1, PALETTERGB(192, 192, 192));
}

/* Draws the line sets at DS:6b5c, 6bbc and 6cfc [inferred]. */
/* 11:a9ea */
void fn_11_a9ea(int16_t a)
{
    HPEN old;
    int16_t u6;
    int16_t i;
    int16_t j;

    SetBkMode(g_13dc, OPAQUE);
    if (g_1016 > 0)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
    else {
        if (a) {
            if (g_1318 > 1)
                fn_10_754a(0x22, g_6b5c[0].x, g_6b5c[0].y, 4);
            else
                fn_10_754a(0x22, g_951e, g_9520, 1);
        }
        if (a && g_951e == 9)
            old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
        else
            old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(127, 255, 255)));
    }
    for (i = 1; i < fn_09_88ba(g_1016); i++)
        fn_12_7256(g_13dc, g_6b5c[i - 1], g_6b5c[i]);
    DeleteObject(SelectObject(g_13dc, old));
    if (g_1016 > 0)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
    else if (a && g_951e == 9)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));
    else
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(127, 255, 255)));
    for (i = 0; i < g_9526; i++)
        for (j = 1; j < 5; j++)
            fn_12_7256(g_13dc, g_6bbc[i][j - 1], g_6bbc[i][j]);
    for (i = 0; i < g_9528; i++)
        for (j = 1; j < 3; j++)
            fn_12_7256(g_13dc, g_6cfc[i][j - 1], g_6cfc[i][j]);
    DeleteObject(SelectObject(g_13dc, old));
    if (g_1016 > 0 && g_1036 == 0) {
        old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
        for (i = 0; i < g_9526; i++)
            for (j = 1; j < 5; j++)
                fn_12_7256(g_13dc, g_6bbc[i][j - 1], g_6bbc[i][j]);
        for (i = 0; i < g_9528; i++)
            for (j = 1; j < 3; j++)
                fn_12_7256(g_13dc, g_6cfc[i][j - 1], g_6cfc[i][j]);
        SelectObject(g_13dc, old);
        g_1016 = -g_1016;
    } else if (g_1036 == 0) {
        g_1036 = 1;
        g_1016 = -g_1016;
    } else
        g_1036 = g_1016 = 0;
}

/* Spawns rings of 20-byte effect records around object n [inferred]. */
/* 11:8a42 */
void fn_11_8a42(int16_t type, int16_t n)
{
    int16_t w;
    int16_t m;
    int16_t j;
    int16_t i;
    int16_t k;
    int16_t sk;
    int16_t r;
    int16_t sr;
    int16_t k8;
    int16_t r8;
    int16_t step;
    int16_t delay;
    struct { POINT a, b; } rc;
    int16_t ok;

    w = 0x50;
    delay = 0x1e;
    ok = j = 0;
    if (type == g_9324) {
        for (j = 1; j < g_7090[n].cnt; j++)
            if (g_7090[n].f_0b8[j] == 1) {
                if (g_7090[n].f_01e > 70)
                    ok = 1;
                break;
            }
    } else
        ok = 1;
    if (!ok)
        return;
    if (type == g_9324)
        g_7090[n].f_01e += -70L * g_1df8[14][n].f_44 / 250;
    rc.b = g_1df8[type][n].f_04;
    rc.a = g_1df8[type][n].f_00;
    for (k = 11, step = 0; k < (int16_t)(w * 10) / 14; k += 21, step++) {
        r = fn_08_1290((int32_t)(int16_t)(w * w - k * k), (int32_t)(int16_t)(w - k / 4));
        k8 = k * 8;
        sk = SC(k);
        r8 = r * 8;
        sr = SC(r);
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x + k8;
                g_5170[i].x = rc.a.x + sk;
                g_5224[i].y = rc.b.y - r8;
                g_5170[i].y = rc.a.y - sr;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = delay * step + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x + r8;
                g_5170[i].x = rc.a.x + sr;
                g_5224[i].y = rc.b.y - k8;
                g_5170[i].y = rc.a.y - sk;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = (5 - step) * delay + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x + r8;
                g_5170[i].x = rc.a.x + sr;
                g_5224[i].y = rc.b.y + k8;
                g_5170[i].y = rc.a.y + sk;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = (step + 5) * delay + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x + k8;
                g_5170[i].x = rc.a.x + sk;
                g_5224[i].y = rc.b.y + r8;
                g_5170[i].y = rc.a.y + sr;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = (10 - step) * delay + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x - k8;
                g_5170[i].x = rc.a.x - sk;
                g_5224[i].y = rc.b.y - r8;
                g_5170[i].y = rc.a.y - sr;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = (20 - step) * delay + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x - r8;
                g_5170[i].x = rc.a.x - sr;
                g_5224[i].y = rc.b.y - k8;
                g_5170[i].y = rc.a.y - sk;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = (step + 15) * delay + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x - r8;
                g_5170[i].x = rc.a.x - sr;
                g_5224[i].y = rc.b.y + k8;
                g_5170[i].y = rc.a.y + sk;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = (15 - step) * delay + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x - k8;
                g_5170[i].x = rc.a.x - sk;
                g_5224[i].y = rc.b.y + r8;
                g_5170[i].y = rc.a.y + sr;
                g_1e90[i].f_00 = g_1e90[i].f_0a = 1;
                g_1e90[i].f_02 = 10;
                g_1e90[i].f_10 = (step + 10) * delay + g_1e50;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_9430++;
                break;
            }
        j = i + 1;
    }
    for (m = 0; m < 2; m++) {
        for (i = j; i < 45; i++)
            if (g_1e90[i].f_00 == -1) {
                g_5224[i].x = rc.b.x;
                g_5170[i].x = rc.a.x;
                g_5224[i].y = rc.b.y;
                g_5170[i].y = rc.a.y;
                g_1e90[i].f_0a = -250;
                if (i > g_9434)
                    g_9434 = i;
                g_1e90[i].f_06 = type;
                g_1e90[i].f_08 = n;
                g_1e90[i].f_00 = 1;
                g_1e90[i].f_02 = 13;
                g_1e90[i].f_10 = (15 - step) * delay * m + g_1e50;
                g_9430++;
                break;
            }
        j = i + 1;
    }
}

/* Turns nearby 0x1c-records into kind 0x1b and builds its bitmap
 * [inferred]. */
/* 11:9078 */
void fn_11_9078(int16_t type, int16_t n)
{
    int16_t i;
    int16_t pa;
    int16_t pb;
    int16_t dist;
    int16_t kind;
    int16_t j;
    BITMAP bm;
    HDC dc;
    HBITMAP bmp;
    HBITMAP oldbmp;
    HPALETTE oldpal;
    int16_t found;
    int16_t ok;

    ok = 0;
    if (type == g_9324) {
        for (j = 1; j < g_7090[n].cnt; j++)
            if (g_7090[n].f_0b8[j] == 0xd || g_7090[n].f_0b8[j] == 0x17) {
                ok = 1;
                break;
            }
    } else
        ok = 1;
    if (!ok)
        return;
    for (i = 0; i < g_9406[6]; i++) {
        if (g_6670[i + 4].r.right > 0 && g_2f4c[g_6670[i + 4].f_04.x].f_26 > g_6670[i + 4].r.right
            && g_6670[i + 4].f_04.x != 0x1b
            && (dist = fn_08_285a(&pa, &pb, g_1df8[type][n].f_04,
                                  g_1df8[6][i].f_04)) < 0x28a) {
            PatBlt(g_13dc, g_1df8[6][i].f_00.x, g_1df8[6][i].f_00.y, g_1df8[6][i].f_22,
                   g_1df8[6][i].f_22, BLACKNESS);
            kind = g_6670[i + 4].f_04.x;
            found = -1;
            for (j = 0; j < g_9406[6]; j++)
                if (g_6670[j + 4].r.right > 0 && g_2f4c[g_6670[j + 4].f_04.x].f_26 > g_6670[j + 4].r.right
                    && g_6670[j + 4].f_04.x == 0x1b)
                    found = j;
            g_6670[i + 4].f_04.x = 0x1b;
            g_6670[i + 4].r.right = 1;
            g_6670[i + 4].r.bottom = g_2f4c[0x1b].f_26;
            g_2f4c[0x1b].f_04 = 0x39;
            g_2f4c[0x1b].f_2c = 5;
            g_1df8[6][i].f_66 = fn_12_6a60;
            if (found == -1) {
                if (g_39e8[g_2f4c[0x1b].f_04]) {
                    SelectObject(g_39e8[g_2f4c[0x1b].f_04], g_3974[g_2f4c[0x1b].f_04]);
                    if (g_920e)
                        SelectPalette(g_39e8[g_2f4c[0x1b].f_04],
                                      g_3a5c[g_2f4c[0x1b].f_04], 0);
                    DeleteDC(g_39e8[g_2f4c[0x1b].f_04]);
                    g_39e8[g_2f4c[0x1b].f_04] = 0;
                    DeleteObject(g_3ad0[g_2f4c[0x1b].f_04]);
                    g_3ad0[g_2f4c[0x1b].f_04] = 0;
                }
                bmp = fn_10_6c02(rand() % 3 + 0x294, 0, -1);
                dc = CreateCompatibleDC(g_13dc);
                g_39e8[g_2f4c[0x1b].f_04] = CreateCompatibleDC(g_13dc);
                if (g_920e) {
                    g_3a5c[g_2f4c[0x1b].f_04] =
                        SelectPalette(g_39e8[g_2f4c[0x1b].f_04], g_920e, 0);
                    oldpal = SelectPalette(dc, g_920e, 0);
                }
                GetObject(bmp, sizeof bm, &bm);
                g_1df8[6][i].f_22 = bm.bmHeight;
                if (bm.bmHeight & 1)
                    g_1df8[6][i].f_24 = 5;
                else
                    g_1df8[6][i].f_24 = 6;
                g_3ad0[g_2f4c[0x1b].f_04] = CreateCompatibleBitmap(g_13dc,
                    g_1df8[6][i].f_24 * 2 + g_1df8[6][i].f_22,
                    g_1df8[6][i].f_24 * 2 + g_1df8[6][i].f_22);
                oldbmp = SelectObject(dc, bmp);
                g_3974[g_2f4c[0x1b].f_04] = SelectObject(g_39e8[g_2f4c[0x1b].f_04],
                                                        g_3ad0[g_2f4c[0x1b].f_04]);
                PatBlt(g_39e8[g_2f4c[0x1b].f_04], 0, 0,
                       g_1df8[6][i].f_24 * 2 + g_1df8[6][i].f_22,
                       g_1df8[6][i].f_24 * 2 + g_1df8[6][i].f_22, BLACKNESS);
                BitBlt(g_39e8[g_2f4c[0x1b].f_04], g_1df8[6][i].f_24,
                       g_1df8[6][i].f_24, g_1df8[6][i].f_22, g_1df8[6][i].f_22, dc,
                       0, 0, SRCCOPY);
                SelectObject(dc, oldbmp);
                if (g_920e)
                    SelectPalette(dc, oldpal, 0);
                DeleteDC(dc);
                DeleteObject(bmp);
                fn_10_6308(g_2f4c[0x1b].f_04, -1, -1, -1);
                g_1df8[6][i].f_20 = g_1df8[6][i].f_22 * 8;
                if (g_1df8[6][i].f_22 & 1) {
                    g_1df8[6][i].f_22 = (g_1df8[6][i].f_22 + 1 << g_9156) >> 1;
                    g_1df8[6][i].f_24 = (4 << g_9156) >> 1;
                } else
                    g_1df8[6][i].f_24 = (6 << g_9156) >> 1;
            } else {
                g_1df8[6][i].f_22 = g_1df8[6][found].f_22;
                g_1df8[6][i].f_24 = g_1df8[6][found].f_24;
            }
        }
    }
}

/* Paints the target panel (control 0xd2) and the weapon panel (control
 * 0xdc) [inferred]. */
/* 11:238e */
void fn_11_238e(HWND hwnd, HDC dc)
{
    BITMAP bm;
    HFONT oldfont;
    HPEN oldpen;
    COLORREF oldcolor;
    char buf[140];
    char tmp[48];
    HDC memdc;
    HBITMAP oldbmp;
    HPALETTE oldpal2;
    HPALETTE oldpal;
    RECT rc;
    int16_t id;
    int16_t rel;
    int16_t xoff;
    int16_t yoff;
    int16_t type;
    int16_t n;
    int16_t got;
    int16_t kind;

    got = 0;
    if (dc == 0) {
        got = 1;
        dc = GetDC(hwnd);
    }
    if (g_920e)
        oldpal = SelectPalette(dc, g_920e, 0);
    id = GetDlgCtrlID(hwnd);
    GetClientRect(hwnd, &rc);
    PatBlt(dc, 0, 0, rc.right, rc.bottom, BLACKNESS);
    switch (id) {
    case 0xd2:
        oldfont = SelectObject(dc, g_90fe);
        SetTextAlign(dc, TA_LEFT);
        SetBkMode(dc, TRANSPARENT);
        if (g_90ee == 1)
            oldcolor = SetTextColor(dc, RGB(255, 255, 255));
        else
            oldcolor = SetTextColor(dc, RGB(0, 255, 0));
        switch (g_0a76) {
        case 2:
            if (g_094e) {
                fn_11_41bc(dc, 1, 1);
                break;
            }
            if (!fn_03_0000(type = g_6e38[0].f_1a.b, n = g_6e38[0].f_1a.a) && !fn_13_371c(type, n))
                g_9498++;
            fn_11_2ce6(dc, 0);
            fn_13_58dc(dc, 1);
            if (LO16(g_90ea) < 700) {
                xoff = 12;
                lstrcpy(buf, "");
            } else {
                xoff = 15;
                LoadString(g_9212, 0x3a2, tmp, 40);
                lstrcpy(buf, tmp);
            }
            LoadString(g_9212, 0x3a3, tmp, 40);
            lstrcat(buf, tmp);
            if (g_0a62 == 0)
                LoadString(g_9212, 0x3a4, tmp, 40);
            else
                LoadString(g_9212, 0x3a5, tmp, 40);
            lstrcat(buf, tmp);
            lstrcat(buf, ")");
            TextOut(dc, 1, 0, buf, lstrlen(buf));
            SetTextAlign(dc, TA_RIGHT);
            TextOut(dc, g_5024 - xoff, 0x12, g_9628, lstrlen(g_9628));
            if (g_9324 == g_6e38[0].f_1a.b) {
                rel = fn_13_2688(g_6e38[0].f_1a.a, main_ship);
                if (rel > 80)
                    SetTextColor(dc, PALETTERGB(0, 0xb9, 0xff));
                else if (rel < -80)
                    SetTextColor(dc, PALETTERGB(0xff, 0x6e, 0));
                else
                    SetTextColor(dc, PALETTERGB(0xaa, 0xaa, 0xaa));
            } else
                SetTextColor(dc, RGB(0, 128, 0));
            TextOut(dc, g_5024 - xoff, 0x20, g_8718, lstrlen(g_8718));
            TextOut(dc, g_5024 - xoff, 0x2e, g_960a, lstrlen(g_960a));
            if (g_6e38[0].f_1a.b == g_9324) {
                fn_11_3f2e(rel);
                TextOut(dc, g_5024 - xoff, 0x3c, g_93e0, lstrlen(g_93e0));
            }
            break;
        case 3:
            fn_11_2ce6(dc, 1);
            fn_13_58dc(dc, 1);
            if (LO16(g_90ea) < 700)
                xoff = 12;
            else
                xoff = 15;
            LoadString(g_9212, 0x3a1, tmp, 40);
            lstrcpy(buf, tmp);
            TextOut(dc, 1, 0, buf, lstrlen(buf));
            SetTextAlign(dc, TA_LEFT);
            if (g_6e38[1].f_1a.b == g_9324) {
                rel = fn_13_2688(g_6e38[1].f_1a.a, main_ship);
                if (rel > 80)
                    SetTextColor(dc, PALETTERGB(0, 0xb9, 0xff));
                else if (rel < -80)
                    SetTextColor(dc, PALETTERGB(0xff, 0x6e, 0));
                else
                    SetTextColor(dc, PALETTERGB(0xaa, 0xaa, 0xaa));
                TextOut(dc, 1, 0x12, g_8740, lstrlen(g_8740));
                fn_11_3f2e(rel);
                if (g_6e38[1].f_1a.a != main_ship)
                    TextOut(dc, 1, 0x20, g_93e0, lstrlen(g_93e0));
            } else {
                SetTextColor(dc, RGB(0, 128, 0));
                TextOut(dc, 1, 0x12, g_8740, lstrlen(g_8740));
            }
            SetTextColor(dc, RGB(255, 255, 0));
            TextOut(dc, 1, 0x2e, g_8768, lstrlen(g_8768));
            TextOut(dc, 1, 0x3c, g_87b8, lstrlen(g_87b8));
            oldpen = SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(0, 128, 0)));
            MoveTo(dc, 0, 14);
            LineTo(dc, 80, 14);
            DeleteObject(SelectObject(dc, oldpen));
            break;
        case 4:
            LoadString(g_9212, 0x3a0, tmp, 40);
            lstrcpy(buf, tmp);
            TextOut(dc, 1, 0, buf, lstrlen(buf));
            if (g_059c == 1200) {
                LoadString(g_9212, 0x88f, buf, 140);
                lstrcpy(buf, buf);
            } else {
                fn_06_0f1a(g_059c, buf);
                LoadString(g_9212, 0x39f, tmp, 40);
                lstrcat(buf, tmp);
                LoadString(g_9212, 0x890, tmp, 40);
                lstrcat(buf, tmp);
            }
            TextOut(dc, 1, 0x16, buf, lstrlen(buf));
            fn_06_0f1a(g_059a, buf);
            LoadString(g_9212, 0x39f, tmp, 40);
            lstrcat(buf, tmp);
            LoadString(g_9212, 0x891, tmp, 40);
            lstrcat(buf, tmp);
            TextOut(dc, 1, 0x26, buf, lstrlen(buf));
            break;
        }
        SetTextColor(dc, oldcolor);
        SelectObject(dc, oldfont);
        if (g_0a76 != 3) {
            oldpen = SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(0, 128, 0)));
            MoveTo(dc, 0, 14);
            LineTo(dc, rc.right, 14);
            DeleteObject(SelectObject(dc, oldpen));
        }
        break;
    case 0xdc:
        oldfont = SelectObject(dc, g_90fe);
        SetTextAlign(dc, TA_LEFT);
        SetBkMode(dc, TRANSPARENT);
        oldcolor = SetTextColor(dc, RGB(255, 0, 0));
        LoadString(g_9212, 0x3a6, tmp, 40);
        lstrcpy(buf, tmp);
        TextOut(dc, 1, 0, buf, lstrlen(buf));
        if (g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_12
            && g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_36 == 0) {
            fn_06_0f1a(g_7090[main_ship].f_0ae[g_7090[main_ship].f_018], buf);
            lstrcat(buf, " - ");
            LoadString(g_9212,
                       g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_08,
                       tmp, 40);
            lstrcat(buf, tmp);
        } else {
            kind = g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_08;
            if (kind != 0xc9 && kind != 0xba && kind != 0xbc)
                LoadString(g_9212, 0x3a7, buf, 40);
            else
                lstrcpy(buf, "");
            LoadString(g_9212, kind, tmp, 40);
            lstrcat(buf, tmp);
        }
        TextOut(dc, 1, 0x11, buf, lstrlen(buf));
        SetTextColor(dc, oldcolor);
        SelectObject(dc, oldfont);
        oldpen = SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(255, 0, 255)));
        MoveTo(dc, 0, 15);
        LineTo(dc, rc.right, 15);
        DeleteObject(SelectObject(dc, oldpen));
        if (g_5030[8]) {
            GetObject(g_5030[8], sizeof bm, &bm);
            memdc = CreateCompatibleDC(g_13dc);
            oldbmp = SelectObject(memdc, g_5030[8]);
            if (g_920e)
                oldpal2 = SelectPalette(memdc, g_920e, 0);
            kind = g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_08;
            if (g_2f4c[g_7090[main_ship].f_0b8[g_7090[main_ship].f_018]].f_12
                && kind != 0xc4 && kind != 0xc6 && kind != 0xcb)
                yoff = 0x1c;
            else if (kind == 0xcb)
                yoff = 0x28;
            else
                yoff = 0x23;
            BitBlt(dc, g_5026 / 2 - bm.bmWidth / 2, yoff, bm.bmWidth,
                   bm.bmHeight, memdc, 0, 0, SRCPAINT);
            SelectObject(memdc, oldbmp);
            if (oldpal2)
                SelectPalette(memdc, oldpal2, 0);
            DeleteDC(memdc);
        }
        break;
    }
    if (oldpal)
        SelectPalette(dc, oldpal, 0);
    if (got) {
        ReleaseDC(hwnd, dc);
        dc = 0;
    }
}

/* Picks the best target in range and in the facing direction of object
 * (type, n), for weapon kind 3 [inferred]. */
/* 11:9fdc */
void fn_11_9fdc(int16_t type, int16_t n)
{
    int16_t bt;
    int16_t bn;
    int16_t best;
    int16_t i;
    int16_t j;
    int16_t dir;
    int16_t range;
    int16_t pa;
    int16_t pb;
    int16_t dist;
    int16_t val;
    int16_t u1a;
    int16_t u1c;
    int16_t u1e;
    int16_t u20;
    int16_t ok;

    ok = 0;
    if (type == g_9324) {
        for (i = 1; i < g_7090[n].cnt; i++)
            if (g_7090[n].f_0b8[i] == 3 && g_7090[n].f_01e > g_2f4c[3].f_36) {
                ok = 1;
                break;
            }
    } else
        ok = 1;
    if (!ok)
        return;
    range = min(g_1df8[type][n].f_50 * 4, LO16(g_90ea) / 2);
    if (type == g_9324 && n == main_ship)
        range = max(range, 150);
    bt = -1;
    best = 0;
    for (i = g_9326; i <= g_9324; i++) {
        if (i != 5 && i != 12) {
            for (j = 0; j < g_9406[i]; j++) {
                if (g_1df8[i][j].f_18 == 0 && (i != type || j != n)
                    && (dist = fn_08_285a(&pa, &pb, g_1df8[type][n].f_04,
                                          g_1df8[i][j].f_04)) < range
                    && g_1df8[type][n].f_28 >= (int16_t)((dir = fn_08_19b0(pa, pb)) - 1)
                    && g_1df8[type][n].f_28 <= (int16_t)(dir + 1)) {
                    val = g_1df8[i][j].f_44;
                    if (type == 14 && g_7090[n].f_038 == 1 && g_7090[n].f_032.a == i
                        && g_7090[n].f_032.b == j)
                        val *= 4;
                    val = (int32_t)(int16_t)(range - dist) * val / range;
                    if (g_1df8[i][j].f_44 > best) {
                        bt = i;
                        bn = j;
                        best = g_1df8[i][j].f_44;
                    }
                }
            }
        }
    }
    if (bt >= 0) {
        if (type == 14)
            g_7090[n].f_01e = max(g_7090[n].f_01e - g_2f4c[3].f_36, 0);
        fn_11_a234(type, n, bt, bn);
    }
    if (type == 6 && g_6670[n + 4].r.left == bt && bt == g_9324
        && g_6670[n + 4].r.top == bn)
        g_6670[n + 4].r.right = g_2f4c[g_6670[n + 4].f_04.x].f_26 - 1;
}

/* Object (type, n) hits object (tt, tn) with its beam [inferred]. */
/* 11:a234 */
void fn_11_a234(int16_t type, int16_t n, int16_t tt, int16_t tn)
{
    POINT a;
    POINT b;
    POINT pa;
    POINT pb;
    POINT u14;
    int16_t dmg;
    POINT u1a;
    POINT c;

    if (g_1016)
        return;
    c.x = g_2400 >> 3;
    c.y = g_2402 >> 3;
    g_9520 = n;
    g_951e = type;
    if (g_9406[type] <= n) {
        g_9498++;
        return;
    }
    fn_10_754a(0x22, g_951e, g_9520, 1);
    if (type == g_9324) {
        a.x = g_7b60[g_7090[n].f_04e][g_1df8[type][n].f_28].x * 8
              + g_1df8[type][n].f_04.x;
        a.y = g_7b60[g_7090[n].f_04e][g_1df8[type][n].f_28].y * 8
              + g_1df8[type][n].f_04.y;
    } else {
        a.x = g_1df8[type][n].f_20 / 2 + g_1df8[type][n].f_04.x;
        a.y = g_1df8[type][n].f_20 / 2 + g_1df8[type][n].f_04.y;
    }
    b.x = g_1df8[tt][tn].f_20 / 2 + g_1df8[tt][tn].f_04.x;
    b.y = g_1df8[tt][tn].f_20 / 2 + g_1df8[tt][tn].f_04.y;
    pa = fn_08_29ea(a);
    fn_11_a4a6(pa, pb = fn_08_29ea(b), type);
    if (type == 9)
        dmg = rand() % (g_1df8[type][n].f_50 / 2) + g_1df8[type][n].f_50 / 3;
    else
        dmg = g_1df8[type][n].f_50;
    if (type == 9 && tt == 0)
        fn_07_2512(tn, 0);
    fn_08_5df2(tt, tn, g_943a = type, g_943c = n, dmg / 2 + 2000);
    if (tt != g_9324)
        g_1df8[tt][tn].f_50 = (int16_t)(dmg * 3) / 5;
    if (type == g_9324 && n == main_ship)
        dmg /= 3;
    g_1df8[type][n].f_50 -= dmg;
    if (type == g_9324 && g_96d2[g_7090[n].f_04e].f_38 == 7) {
        g_1df8[tt][tn].f_50 = 0;
        g_1df8[type][n].f_50 = 0;
    }
}

/* Blits the 16 cells of object n's ring sprite (a: second row) [inferred]. */
/* 11:b09c */
void fn_11_b09c(int16_t n, int16_t a)
{
    int16_t i;
    int16_t h;
    int16_t g;
    int16_t x;
    int16_t y;
    int16_t cls;
    int16_t idx;
    int16_t unused;
    int16_t off;
    int16_t sz;
    int16_t flag;
    int16_t unused2;

    flag = 1;
    cls = g_7090[n].f_04e;
    g = g_1df8[g_9324][n].f_24;
    h = g_1df8[g_9324][n].f_22;
    if (a)
        g_1df8[g_9324][n].f_2f = g_7090[n].f_00c / 20;
    else
        g_1df8[g_9324][n].f_2f = 0;
    if (g_7090[n].f_010 > 0 && g_7090[n].f_010 < 7)
        flag = 0;
    if (g_7090[n].f_0e4) {
        if (subgame_active)
            sz = g_9156 * 6 + 3;
        else
            sz = SC(9);
        for (i = 0; i < 16; i++) {
            if (flag || g_1df8[g_9324][n].f_28 == i) {
                if (i < 5) {
                    x = g_96d2[cls].f_50[i].x;
                    y = g_96d2[cls].f_50[i].y;
                } else if (i < 9) {
                    x = g_96d2[cls].f_50[8 - i].x;
                    y = h - g_96d2[cls].f_50[8 - i].y - sz;
                } else if (i < 12) {
                    x = h - g_96d2[cls].f_50[i - 8].x - sz;
                    y = h - g_96d2[cls].f_50[i - 8].y - sz;
                } else {
                    x = h - g_96d2[cls].f_50[16 - i].x - sz;
                    y = g_96d2[cls].f_50[16 - i].y;
                }
                idx = n + 40;
                if (g_7090[n].f_010 > 3)
                    off = g + h;
                else
                    off = 0;
                if (flag == 0) {
                    BitBlt(g_39e8[idx], h * 16 + g * 17 + x, y + g, sz, sz,
                           g_39e8[34], sz * i, (n * 2 + a) * sz, SRCCOPY);
                    BitBlt(g_39e8[idx], h * 16 + g * 17 + x, g * 2 + y + h, sz, sz,
                           g_39e8[34], sz * i, (n * 2 + a) * sz, SRCCOPY);
                } else
                    BitBlt(g_39e8[idx], (g + h) * i + x + g, off + y + g, sz, sz,
                           g_39e8[34], sz * i, (n * 2 + a) * sz, SRCCOPY);
            }
        }
    }
}

/* Builds and draws a random lightning bolt from a to b with side branches (type 9: green) [inferred]. */
/* 11:a4a6 */
void fn_11_a4a6(POINT a, POINT b, int16_t type)
{
    POINT d;
    POINT p;
    int16_t i;
    int16_t len;
    int16_t seg;
    int16_t j;
    int16_t k;
    HGDIOBJ old;
    int16_t unused;

    srand((uint16_t)GetCurrentTime());
    g_9526 = g_9528 = 0;
    seg = 30;
    p.x = -(d.y = b.y - a.y);
    p.y = d.x = b.x - a.x;
    len = fn_08_1290((int32_t)d.y * d.y + (int32_t)d.x * d.x,
                     (int32_t)(int16_t)(fn_09_88ba(d.x) + fn_09_88ba(d.y)));
    if (len / seg > 22) {
        seg = 50;
        if (len / seg > 22)
            return;
    }
    for (i = 0; i < len / seg; i++) {
        if (i > 0) {
            g_6b5c[i].x = (int32_t)(int16_t)(rand() % 10 + (i + 1) * seg - 5) * d.x / len
                        + (int32_t)(rand() % 26 - 13) * p.x / len + a.x;
            g_6b5c[i].y = (int32_t)(int16_t)(rand() % 10 + (i + 1) * seg - 5) * d.y / len
                        + (int32_t)(rand() % 26 - 13) * p.y / len + a.y;
        } else
            g_6b5c[0] = a;
        if (rand() % 3 == 0) {
            g_6bbc[g_9526][0] = g_6b5c[i];
            for (j = 1; j < 5; j++) {
                g_6bbc[g_9526][j].x = (int32_t)(int16_t)((i % 2 * 32 - 16) * j + rand() % 24 - 12) * p.x / len
                    + (int32_t)(int16_t)(rand() % 15 + j * 15) * d.x / len + g_6b5c[i].x;
                g_6bbc[g_9526][j].y = (int32_t)(int16_t)(rand() % 24 + (i % 2 * 32 - 16) * j - 12) * p.y / len
                    + (int32_t)(int16_t)(rand() % 15 + j * 15) * d.y / len + g_6b5c[i].y;
            }
            g_9526++;
            if (g_9526 > 16)
                return;
            if (rand() % 5 <= 3) {
                g_6cfc[g_9528][0] = g_6bbc[g_9526 - 1][2];
                for (k = 1; k < 3; k++) {
                    g_6cfc[g_9528][k].x = (int32_t)(int16_t)(((k + 2) * (i % 2) * 2 - k) * 12 + rand() % 16 - 32) * p.x / len
                        + (int32_t)(int16_t)(rand() % 15 + (k + 2) * 15) * d.x / len + g_6cfc[g_9528][0].x;
                    g_6cfc[g_9528][k].y = (int32_t)(int16_t)(rand() % 16 + ((k + 2) * (i % 2) * 2 - k) * 12 - 32) * p.y / len
                        + (int32_t)(int16_t)(rand() % 15 + (k + 2) * 15) * d.y / len + g_6cfc[g_9528][0].y;
                }
                g_9528++;
            }
        }
    }
    g_6b5c[i] = b;
    if (type == 9)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
    else
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(195, 255, 255)));
    for (j = 1; j < (int16_t)(i + 1); j++)
        fn_12_7256(g_13dc, g_6b5c[j - 1], g_6b5c[j]);
    DeleteObject(SelectObject(g_13dc, old));
    if (type == 9)
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(0, 255, 0)));
    else
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(195, 255, 255)));
    for (j = 0; j < g_9526; j++)
        for (k = 1; k < 5; k++)
            fn_12_7256(g_13dc, g_6bbc[j][k - 1], g_6bbc[j][k]);
    for (j = 0; j < g_9528; j++)
        for (k = 1; k < 3; k++)
            fn_12_7256(g_13dc, g_6cfc[j][k - 1], g_6cfc[j][k]);
    DeleteObject(SelectObject(g_13dc, old));
    g_1016 = i + 1;
}

/* Finds the earliest crossing of ship i's path with a link segment (best time into f90) and reflects its velocity into f88/f8a [inferred]. */
/* 11:5626 */
void fn_11_5626(int16_t i)
{
    int32_t A;
    int32_t B;
    int32_t C;
    int32_t D;
    int32_t E;
    int32_t F;
    int32_t G;
    int32_t dummy;
    int32_t t;
    int32_t H;
    int32_t best;
    int32_t den;
    int32_t u;
    int16_t j;
    int16_t unused;

    best = 50000L;
    if (g_9320 != 6 || g_9eb5 != 0)
        return;
    C = (int32_t)g_6098[i].z[1][2];
    D = (int32_t)g_6098[i].z[1][3];
    if (C == 0)
        C = 1;
    if (D == 0)
        D = 1;
    dummy = fn_08_35d0(C, D);
    for (j = 0; j < g_9eb9[g_9322]; j++) {
        if (g_9ec2[g_9322][j] != j) {
            A = (int32_t)(g_1df8[8][j + 2].f_04.x - g_6098[i].f_30[0][0] + 56);
            B = (int32_t)(g_1df8[8][j + 2].f_04.y - g_6098[i].f_48[0][0] + 56);
            E = (int32_t)(int16_t)(g_1df8[8][g_9ec2[g_9322][j] + 2].f_04.x - g_1df8[8][j + 2].f_04.x + 56);
            F = (int32_t)(int16_t)(g_1df8[8][g_9ec2[g_9322][j] + 2].f_04.y - g_1df8[8][j + 2].f_04.y + 56);
            G = (int32_t)fn_08_35d0(E, F);
            den = E * D - F * C;
            if (den == 0)
                den = 1;
            H = (C * B - D * A) / 20 * G / den * 20;
            if (H >= 0 && H <= G) {
                if (abs32(D) < abs32(C))
                    t = (H * E / G + A) / C;
                else
                    t = (H * F / G + B) / D;
                if (t >= 0 && t < best) {
                    best = t;
                    u = (F * C - E * D) / G;
                    g_6098[i].f_88 = C - u * F * 2 / G;
                    g_6098[i].f_8a = u * E * 2 / G + D;
                }
            }
        }
    }
    if (best != 50000L)
        g_6098[i].f_90 = best + g_05cc;
}

/* Ship n's thrust step: afterburner on Ctrl (a != 1 also applies thrust to the velocity and checks for a hard turn) [inferred]. */
/* 11:63b4 */
void fn_11_63b4(int16_t n, int16_t a)
{
    int16_t u1;
    int16_t u2;
    int16_t j;
    int16_t k;
    int16_t key;
    int16_t e;
    int16_t p;
    int16_t m;
    int16_t s;
    int16_t t;
    POINT v;
    POINT dv;
    char buf[40];
    int32_t len;
    int32_t cr;
    int32_t tq;

    if (g_9e49 >= 1 && g_9e49 <= 6 && n == g_952e && subgame_active == 0)
        return;
    if (g_7090[n].f_090 < g_1e50) {
        g_7090[n].f_090 = g_1e50 + 250;
        if (g_7090[n].f_002 == 0) {
            fn_11_b09c(n, g_7090[n].f_002 = 1);
            g_1df8[g_9324][n].f_26 = 0;
            g_7090[n].f_012 = 0;
            fn_13_6716(n);
        }
    }
    if (g_9134)
        key = 0;
    else
        key = GetAsyncKeyState(VK_CONTROL);
    if (n == main_ship && g_103e)
        g_952a = 1;
    if (g_7090[n].f_060 < 4) {
        if (((key & 0x8000) && n == main_ship || g_952a) && g_7090[n].f_01e >= 30) {
            if (g_1df8[g_9324][n].f_1a != 0) {
                fn_10_754a(0x29, g_9324, n, 1);
                for (j = 0; j < 10; j++)
                    for (k = 0; k < 4; k++) {
                        g_5b28[j][k].f_0c = 0;
                        g_5b28[j][k].q.x = g_5b28[j][k].q.y = -100;
                    }
                g_9512 = g_9324;
                g_9514 = n;
                g_9510 = 0;
                if (g_9134 != 0 && g_9134 != 2 && n == main_ship && g_7090[n].f_03a == 5
                    && g_7090[n].f_006 == 8 && g_3d50[g_7090[n].f_008].f_0a == -3) {
                    LoadString(g_9212, 0x203, buf, 40);
                    lstrcpy(g_8630, buf);
                    LoadString(g_9212, 0x204, buf, 40);
                    lstrcat(g_8630, buf);
                    g_058c = 1;
                    g_05c0 = g_1e50 + 1200;
                }
                if (g_7090[n].f_060 && (n != main_ship || g_9134))
                    g_7090[n].f_060 = 0x1c;
                else
                    g_7090[n].f_060 = 8;
            }
            g_7090[n].f_01c = 5;
            g_7090[n].f_01e -= 25;
        }
    }
    if (a != 1) {
        e = g_1df8[g_9324][n].f_28;
        m = g_1df8[g_9324][n].f_44;
        p = g_7090[n].f_01c;
        if (p > 1 && g_7090[n].f_03a == 5)
            p += 2;
        s = g_7090[n].f_00c;
        if (g_7090[n].f_0d6 != -1)
            s = (int32_t)((g_6e24[g_7090[n].f_0d6].f_33 + 10) * 10) * s / 100;
        if (g_7090[n].f_026[2] == 0)
            s /= 3;
        else if (g_7090[n].f_01e == 0)
            s /= 3;
        else if (g_7090[n].f_026[2] < 35)
            s -= (40 - g_7090[n].f_026[2]) * s >> 6;
        if (s < 1)
            s = 1;
        t = g_7090[n].f_00e;
        v = VIEW(POINT, g_1df8[g_9324][n].f_0c, 0);
        dv.x = (g_1050[e].x * s * p - t * v.x) / m;
        dv.y = (g_1050[e].y * s * p - t * v.y) / m;
        g_1df8[g_9324][n].f_0c += dv.x;
        g_1df8[g_9324][n].f_0e += dv.y;
        if (g_9320 == 6 && g_1c3e < g_1e50 && g_9eb5 == 0) {
            len = fn_08_35d0((int32_t)v.x, (int32_t)v.y);
            cr = ((int32_t)dv.y * v.x - (int32_t)dv.x * v.y) / len;
            tq = cr * g_1df8[14][n].f_44;
            if (p > 2)
                tq /= 3;
            if (abs32(tq) > 2950 && abs32(cr * 5) < len) {
                if (rand() % 1000 + 3100 < abs32(tq))
                    fn_10_754a(0x28, 0xe, n, 1);
                g_1c3e = g_1e50 + 1500;
            }
        }
    }
    g_1df8[g_9324][n].f_2f = (int16_t)(s * p) / 20;
}

/* Race HUD: lap count, position line, lap times and the start countdown [inferred]. */
/* 11:41bc */
void fn_11_41bc(HDC dc, int16_t a, int16_t b)
{
    char buf1[240];
    char buf2[200];
    int16_t i;
    int16_t rank;
    int16_t left;
    int16_t laps;
    DWORD tm;
    int32_t col;
    POINT pt;
    char buf3[6];

    if (b) {
        if (a)
            SetBkMode(dc, TRANSPARENT);
        else
            SetBkMode(dc, OPAQUE);
        if (a) {
            fn_06_0f1a(g_9ea0, buf1);
            fn_09_9580(0x892, buf1);
            lstrcat(buf1, g_38c8);
            for (i = lstrlen(g_38c8) - 1; i > 2; i--)
                if (g_38c8[i] == '-') {
                    g_38c8[i - 1] = 0;
                    break;
                }
            TextOut(dc, 1, 0, buf1, lstrlen(buf1));
        }
        SetTextColor(dc, RGB(255, 255, 0));
        race_position();
        fn_17_7ba6(g_9684, buf1);
        fn_09_9580(0x893, buf1);
        if (g_9eb4 == 0)
            rank = 1;
        else if (g_7090[main_ship].f_0da < 0)
            rank = -g_7090[main_ship].f_0da;
        else
            rank = g_7090[main_ship].f_0da + 1;
        left = g_9ea0 - rank + 1;
        if (left != 0 && g_1df8[14][main_ship].f_51 == 0) {
            lstrcat(buf1, " ");
            if (left == 1)
                fn_09_9580(0x894, buf1);
            else {
                fn_06_0f1a(left, buf2);
                lstrcat(buf1, buf2);
                fn_09_9580(0x895, buf1);
            }
        }
        if (lstrcmp(g_9628, buf1) != 0) {
            buf1[30] = 0;
            lstrcpy(g_9628, buf1);
            PatBlt(dc, 1, 18, 270, 14, BLACKNESS);
        }
        TextOut(dc, 1, 18, g_9628, lstrlen(g_9628));
        SetTextColor(dc, RGB(0, 255, 0));
    }
    if (g_9eb4 != 0 && b != 0) {
        if (g_9e90[main_ship] != 0) {
            LoadString(g_9212, 0x896, buf1, 240);
            fn_11_4928(0, g_9e90[main_ship], buf2);
            lstrcat(buf1, buf2);
            TextOut(dc, 1, 32, buf1, lstrlen(buf1));
        }
        if (g_1df8[14][main_ship].f_51)
            laps = g_9ea0;
        else if (g_7090[main_ship].f_0da < 0)
            laps = -g_7090[main_ship].f_0da;
        else
            laps = g_7090[main_ship].f_0da + 1;
        if (g_9e70[main_ship] + 140 > g_1e68 && g_9e90[main_ship] != 0
            || g_1df8[14][main_ship].f_51 != 0) {
            if (g_1df8[14][main_ship].f_51 == 0)
                laps--;
            tm = g_9e70[main_ship] - g_9e80[main_ship];
        } else
            tm = g_1e68 - g_9e70[main_ship];
        fn_09_955c(0x897, buf1);
        fn_06_0f1a(laps, buf2);
        lstrcat(buf1, buf2);
        fn_09_9580(0x898, buf1);
        fn_11_4928(0, tm, buf2);
    l_reset:    /* bare label: resets register tracking */
        lstrcat(buf1, buf2);
        TextOut(dc, 1, 60, buf1, lstrlen(buf1));
        if (g_1df8[14][main_ship].f_51 == 0) {
            fn_09_955c(0x899, buf1);
            fn_11_4928(0, g_1e68 - g_9e60[main_ship], buf2);
            lstrcat(buf1, buf2);
            TextOut(dc, 1, 46, buf1, lstrlen(buf1));
        } else {
            fn_09_955c(0x89a, buf1);
            fn_11_4928(0, g_9e60[main_ship], buf2);
            lstrcat(buf1, buf2);
            TextOut(dc, 1, 46, buf1, lstrlen(buf1));
        }
    } else if (g_9eb4 == 0) {
        if (b) {
            fn_09_955c(0x89b, buf1);
            TextOut(dc, 1, 46, buf1, lstrlen(buf1));
        }
        if (g_1df8[14][g_9316].f_28 == 4) {
            if (g_13dc)
                g_186a++;
            if (g_9eb5) {
                fn_10_744c(20);
                race_radar_background(1);
            }
            g_9eb5 = 0;
            if (g_186a == 5 || g_186a == 9 || g_186a == 13 || g_186a == 16
                || g_186a == 17) {
                fn_10_744c(110);
                col = RGB(255, 0, 0);
                pt.x = ((int16_t)(g_1df8[12][1].f_04.x - g_1df8[14][main_ship].f_04.x) >> 4 << g_9156)
                     + g_1df8[14][main_ship].f_00.x + (25 << g_9156);
                pt.y = g_1df8[14][main_ship].f_22 / 4 + g_1df8[14][main_ship].f_00.y;
                switch (g_186a) {
                case 5:
                    fn_10_754a(0x75, -80, HI16(g_90ea) / 2, 4);
                    lstrcpy(buf3, "3");
                    fn_10_94c4(1, 0, col, pt.x, pt.y, buf3);
                    break;
                case 9:
                    fn_10_754a(0x75, LO16(g_90ea) + 40, HI16(g_90ea) / 2, 4);
                    lstrcpy(buf3, "2");
                    fn_10_94c4(1, 0, col, pt.x, pt.y, buf3);
                    break;
                case 13:
                    fn_10_754a(0x75, LO16(g_90ea) / 2, HI16(g_90ea) / 2, 4);
                    lstrcpy(buf3, "1");
                    fn_10_94c4(1, 0, col = RGB(255, 128, 0), pt.x, pt.y, buf3);
                    break;
                case 16:
                    LoadString(g_9212, 0x89c, buf3, 5);
                    fn_10_94c4(1, 0, col = RGB(128, 255, 0), pt.x, pt.y, buf3);
                    break;
                case 17:
                    PatBlt(g_13dc, pt.x, pt.y, 50, 30, BLACKNESS);
                    break;
                }
            }
            if (g_186a == 17) {
                fn_10_7480(4, 1);
                fn_10_744c(31);
                g_9eb4 = 1;
                for (i = 0; i <= g_9316; i++) {
                    g_9e80[i] = g_9e70[i] = g_9e60[i] = g_1e68;
                    g_9e90[i] = 0;
                }
            }
        } else
            g_186a = 0;
    }
}

/* Fire or release the tow tether of object (type, n), weapon k: picks the
 * best target in range and launches a type-10 tether object [inferred]. */
/* 11:947a */
void fn_11_947a(int16_t type, int16_t n, int16_t k)
{
    int16_t unused1[4];             /* frame slots never used */
    int16_t t;
    int16_t speed;
    int16_t tt;
    int16_t tn;
    int16_t best;
    int16_t v16;                    /* set, never read */
    int16_t j;
    int16_t dx;
    int16_t dy;
    int16_t dist;
    int16_t dir;
    int16_t unused3;
    int16_t slot;
    int16_t maxd;
    int16_t score;
    int16_t unused2[4];             /* frame slots never used */
    HGDIOBJ old;
    int16_t ok;

    if (g_1df8[type][n].f_1a == 0)
        return;
    ok = 0;
    if (type == g_9324) {
        for (j = 1; j < g_7090[n].cnt; j++)
            if (g_7090[n].f_0b8[j] == 2 || g_7090[n].f_0b8[j] == 15) {
                ok = 1;
                break;
            }
    } else
        ok = 1;
    if (type == g_9324) {
        if (g_2f4c[k].f_36 > g_7090[n].f_01e)
            ok = 0;
        else
            g_7090[n].f_01e -= g_2f4c[k].f_36;
    }
    if (ok == 0)
        return;
    if (g_1df8[type][n].f_36 == -1) {
        slot = -1;
        for (t = 0; t < g_92ec[10]; t++)
            if (g_1df8[10][t].f_18 != 0 && g_65cc[t].f_00 == -1) {
                slot = t;
                break;
            }
        if (slot == -1)
            return;
        g_65cc[slot].f_0a = k;
        g_1df8[10][slot].f_00.y = -1000;
        g_1df8[10][slot].f_00.x = g_1df8[10][slot].f_00.y;
        fn_10_754a(29, type, n, 1);
        if (type == g_9324 && g_96d2[g_7090[n].f_04e].f_38 == 7 && k == 15) {
            tt = g_7090[n].f_054;
            tn = g_7090[n].f_056;
            v16 = 200;
        } else {
            tt = -1;
            best = 0;
            maxd = 300;
            for (t = g_9326; t <= g_9324; t++) {
                if (t != 5 && t != 12 && t != 2)
                    for (j = 0; j < g_9406[t]; j++) {
                        if (g_1df8[t][j].f_18 == 0 && (t != type || j != n)
                            && (g_1df8[t][j].f_54 == 0 || t == 4)
                            && (dist = fn_08_285a(&dx, &dy, g_1df8[type][n].f_04, g_1df8[t][j].f_04)) < maxd) {
                            score = (int16_t)(g_1df8[t][j].f_44 + 400) > 1200 ? 1200 : g_1df8[t][j].f_44 + 400;
                            dir = fn_08_19b0(dx, dy);
                            if (g_1df8[type][n].f_28 >= (int16_t)(dir - 1) && g_1df8[type][n].f_28 <= (int16_t)(dir + 1))
                                score *= 2;
                            if (type == 14 && t == g_7090[n].f_032.a && j == g_7090[n].f_032.b) {
                                score *= 2;
                                if (g_1df8[g_7090[n].f_032.a][g_7090[n].f_032.b].f_53 != 0)
                                    score *= 3;
                            } else if (type == 14 && t == 14 && g_7090[n].f_032.a == 14)
                                score /= 8;
                            else if (type == 14 && g_1df8[t][j].f_53 == 1 && g_7090[n].f_038 != 1)
                                score *= 2;
                            if (t == 6)
                                score *= 6;
                            score = (int32_t)score * (int16_t)(maxd * 2 - dist) / ((int32_t)maxd * 2);
                            if (score > best) {
                                tt = t;
                                tn = j;
                                best = score;
                            }
                        }
                    }
            }
        }
        g_1df8[type][n].f_31 = slot;
        if (tt != -1 && g_92e8 == 0) {
            g_1df8[10][slot].f_04 = g_1df8[type][n].f_04;
            VIEW(int32_t, g_1df8[10][slot].f_0c, 0) = VIEW(int32_t, g_1df8[type][n].f_0c, 0);
            if (type == g_9324) {
                g_1df8[10][slot].f_04.x += g_7b60[g_7090[n].f_04e][g_1df8[10][slot].f_28].x * 4 / 3 << 3;
                g_1df8[10][slot].f_04.y += g_7b60[g_7090[n].f_04e][g_1df8[10][slot].f_28].y * 4 / 3 << 3;
            } else {
                g_1df8[10][slot].f_04.x += g_1df8[type][n].f_20 / 2 * g_1050[g_1df8[10][slot].f_28].x / 16
                    + (g_1050[g_1df8[10][slot].f_28 + 32].x << 3);
                g_1df8[10][slot].f_04.y += g_1df8[type][n].f_20 / 2 * g_1050[g_1df8[10][slot].f_28].y / 16
                    + (g_1050[g_1df8[10][slot].f_28 + 32].y << 3);
            }
            if (tt == g_9324)
                speed = 160;
            else
                speed = 110;
            fn_08_348e(10, slot, tt, tn, speed);
            if (g_1df8[type][n].f_0c == g_1df8[10][slot].f_0c
                && g_1df8[type][n].f_0e == g_1df8[10][slot].f_0e) {
                g_1df8[10][slot].f_0c = g_1050[g_1df8[type][n].f_28].x * 7 + g_1df8[type][n].f_0c;
                g_1df8[10][slot].f_0e = g_1050[g_1df8[type][n].f_28].y * 7 + g_1df8[type][n].f_0e;
            }
            g_1df8[10][slot].f_28 = fn_08_19b0(g_1df8[10][slot].f_0c, g_1df8[10][slot].f_0e);
            g_1df8[10][slot].f_18 = 0;
            g_1df8[10][slot].f_2e = 0;
            g_1df8[10][slot].f_32 = type;
            g_1df8[10][slot].f_34 = n;
            g_65cc[slot].f_08 = 0;
            g_65cc[slot].f_00 = 10;
            g_65cc[slot].f_02 = slot;
            g_65cc[slot].f_04 = type;
            g_65cc[slot].f_06 = n;
            g_1df8[type][n].f_36 = 10;
            g_1df8[type][n].f_38 = slot;
        } else {
            g_1df8[10][slot].f_18 = 0;
            g_1df8[10][slot].f_2e = 0;
            g_1df8[10][slot].f_0c = g_1050[g_1df8[type][n].f_28].x * 7 + g_1df8[type][n].f_0c;
            g_1df8[10][slot].f_0e = g_1050[g_1df8[type][n].f_28].y * 7 + g_1df8[type][n].f_0e;
            g_1df8[10][slot].f_28 = g_1df8[type][n].f_28;
            g_1df8[10][slot].f_04 = g_1df8[type][n].f_04;
            if (type == g_9324) {
                g_1df8[10][slot].f_04.x += g_7b60[g_7090[n].f_04e][g_1df8[10][slot].f_28].x * 4 / 3 << 3;
                g_1df8[10][slot].f_04.y += g_7b60[g_7090[n].f_04e][g_1df8[10][slot].f_28].y * 4 / 3 << 3;
            } else {
                g_1df8[10][slot].f_04.x += g_1df8[type][n].f_20 / 2 * g_1050[g_1df8[10][slot].f_28].x / 16
                    + (g_1050[g_1df8[10][slot].f_28 + 32].x << 3);
                g_1df8[10][slot].f_04.y += g_1df8[type][n].f_20 / 2 * g_1050[g_1df8[10][slot].f_28].y / 16
                    + (g_1050[g_1df8[10][slot].f_28 + 32].y << 3);
            }
            g_1df8[10][slot].f_32 = type;
            g_1df8[10][slot].f_34 = n;
            g_1df8[type][n].f_36 = 10;
            g_1df8[type][n].f_38 = slot;
            g_65cc[slot].f_08 = 0;
            g_65cc[slot].f_00 = 10;
            g_65cc[slot].f_02 = slot;
            g_65cc[slot].f_04 = type;
            g_65cc[slot].f_06 = n;
        }
    } else {
        if (g_1df8[type][n].f_36 == g_9324) {
            g_7090[g_1df8[type][n].f_38].f_084 = g_1e50 + 800;
            g_1df8[g_9324][g_1df8[type][n].f_38].f_26 = 1;
            g_7090[g_1df8[type][n].f_38].f_0e2 = 1;
        }
        g_1df8[g_1df8[type][n].f_36][g_1df8[type][n].f_38].f_32 = -1;
        g_1df8[type][n].f_36 = -1;
        g_65cc[g_1df8[type][n].f_31].f_00 = -1;
        g_65cc[g_1df8[type][n].f_31].f_04 = -1;
        g_1df8[10][g_1df8[type][n].f_31].f_18 = 1;
        old = SelectObject(g_13dc, GetStockObject(7));
        fn_12_7256(g_13dc, g_65cc[g_1df8[type][n].f_31].f_1c, g_65cc[g_1df8[type][n].f_31].f_14);
        SelectObject(g_13dc, old);
        PatBlt(g_13dc, g_1df8[10][g_1df8[type][n].f_31].f_00.x, g_1df8[10][g_1df8[type][n].f_31].f_00.y,
               g_1df8[10][g_1df8[type][n].f_31].f_22, g_1df8[10][g_1df8[type][n].f_31].f_22, BLACKNESS);
        if (type == g_9324 && n == main_ship && g_951a == 0)
            fn_07_1208();
    }
    fn_07_2080(10);
}

/* Lay out and draw the control panel below the play view: info windows,
 * zoom scroll bar, stone frame, panel bitmaps; then redraw the current
 * screen [inferred]. */
/* 11:0afe */
void fn_11_0afe(void)
{
    HDC memdc;
    HPEN oldpen;
    HBITMAP oldbmp;
    HBRUSH oldbrush;
    HPALETTE oldpal;
    int16_t i;
    int16_t unused1[7];             /* frame slots never used */
    int16_t h;
    int16_t unused2[2];             /* frame slots never used */
    int16_t gotdc;
    char buf[8];
    char s[4];
    RECT r2;
    RECT r1;                    /* computed, never used */
    int16_t off;
    int16_t n;
    int16_t rem;
    int16_t tile;
    int16_t h2;
    COLORREF col;               /* set, never read */

    g_5050 = g_0a72 / 2;
    g_5052 = g_0a74 / 2;
    srand((uint16_t)GetCurrentTime());
    gotdc = 0;
    if (g_13dc == 0) {
        gotdc = 1;
        g_13dc = GetDC(g_0016);
    }
    if (g_920e) {
        oldpal = SelectPalette(g_13dc, g_920e, 0);
        RealizePalette(g_13dc);
    }
    if (fn_11_2120()) {
        if (LO16(g_90ea) < 660) {
            g_93b8 = 1;
            g_93dc = 73;
        } else if (LO16(g_90ea) < 760) {
            g_93b8 = 1;
            g_93dc = 90;
        } else {
            g_93b8 = 4;
            g_93dc = 134;
        }
        g_5024 = LO16(g_90ea) / 2 - g_93dc - 96;
        if (LO16(g_90ea) < 700)
            g_5024 += 9;
        g_93ba = g_93dc + g_93b8 + 4;
        if (LO16(g_90ea) < 700)
            g_93ba -= 2;
        g_93be = LO16(g_90ea) / 2 - 50;
        g_93bc = g_93be - 30;
        if (LO16(g_90ea) >= 700)
            g_93bc -= 4;
        g_93c0 = LO16(g_90ea) / 2 + 68;
        if (g_094e)
            g_93c0 -= 14;
        g_93c2 = g_93c0 + 28;
        g_93c4 = g_93c0 + 88;
        g_5026 = LO16(g_90ea) / 2 - 160;
        if (LO16(g_90ea) < 700)
            g_5026 += 4;
        if (g_094e)
            g_5026 += 14;
        if (g_0a7a) {
            GetWindowRect(g_0a7a, &r1);
            GetWindowRect(g_0016, &r2);
            r1.left -= r2.left;
            r1.top -= r2.top;
        }
        if (g_0a7a) {
            DestroyWindow(g_0a7a);
            g_0a7a = 0;
        }
        if (g_094e == 0) {
            g_0a7a = CreateWindow("scrollbar", "", WS_CHILD | WS_VISIBLE | SBS_VERT,
                                  LO16(g_90ea) / 2 + 50, g_8e5a, 14, 85, g_0016, (HMENU)200, g_8e66, NULL);
            SetScrollRange(g_0a7a, SB_CTL, 100, 500, FALSE);
            SetScrollPos(g_0a7a, SB_CTL, 600 - (int16_t)g_0a6c, TRUE);
        }
        if (g_0a7c) {
            DestroyWindow(g_0a7c);
            g_0a7c = 0;
        }
        g_0a7c = CreateWindow("IS_INFO", "", WS_CHILD | WS_VISIBLE,
                              g_93ba + 5, g_8e5a + 5, g_5024 - 9, 76, g_0016, (HMENU)210, g_8e66, NULL);
        if (g_0a7e) {
            DestroyWindow(g_0a7e);
            g_0a7e = 0;
        }
        g_0a7e = CreateWindow("IS_INFO", "", WS_CHILD | WS_VISIBLE,
                              g_93c4 + 5, g_8e5a + 5, g_5026 - 9, 76, g_0016, (HMENU)220, g_8e66, NULL);
        oldbrush = SelectObject(g_13dc, g_500a);
        PatBlt(g_13dc, 0, g_8e5a, LO16(g_90ea), 85, PATCOPY);
        SelectObject(g_13dc, oldbrush);
        if (g_0a78) {
            h2 = g_8e5a;
            off = (58 - LO16(g_90ea) % 58) / 2;
            n = LO16(g_90ea) / 58;
            if (off)
                n++;
            fn_11_170a(1);
            memdc = CreateCompatibleDC(g_13dc);
            oldbmp = SelectObject(memdc, g_5030[10]);
            for (i = 0; i < (int16_t)(n + 1); i++) {
                tile = fn_11_170a(0);
                BitBlt(g_13dc, i * 58 - off, 0, 58, 58, memdc, tile * 58, 0, SRCCOPY);
            }
            n = h2 / 58;
            rem = h2 % 58;
            for (i = 1; i < n; i++) {
                tile = fn_11_170a(0);
                BitBlt(g_13dc, -off, i * 58, 58, 58, memdc, tile * 58, 0, SRCCOPY);
            }
            tile = fn_11_170a(0);
            BitBlt(g_13dc, -off, i * 58, 58, rem, memdc, tile * 58, 0, SRCCOPY);
            for (i = 1; i < n; i++) {
                tile = fn_11_170a(0);
                BitBlt(g_13dc, off + LO16(g_90ea) - 58, i * 58, 58, 58, memdc, tile * 58, 0, SRCCOPY);
            }
            tile = fn_11_170a(0);
            BitBlt(g_13dc, off + LO16(g_90ea) - 58, i * 58, 58, rem, memdc, tile * 58, 0, SRCCOPY);
            SelectObject(memdc, oldbmp);
            DeleteDC(memdc);
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((14 - i) * 10, (14 - i) * 10, (14 - i) * 10)));
                PatBlt(g_13dc, (i + 29) * 2 - off, (i + 29) * 2,
                       LO16(g_90ea) - ((i + 29) * 2 - off) * 2, 2, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((12 - i) * 20, (12 - i) * 20, (12 - i) * 20)));
                PatBlt(g_13dc, (i + 29) * 2 - off, h2 - (i + 1) * 2,
                       LO16(g_90ea) - ((i + 29) * 2 - off) * 2, 2, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((14 - i) * 10, (14 - i) * 10, (14 - i) * 10)));
                PatBlt(g_13dc, (i + 29) * 2 - off, (i + 29) * 2,
                       2, h2 - i * 4 - 58, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
            for (i = 0; i < 10; i++) {
                oldbrush = SelectObject(g_13dc, CreateSolidBrush(
                    PALETTERGB((12 - i) * 20, (12 - i) * 20, (12 - i) * 20)));
                PatBlt(g_13dc, LO16(g_90ea) + off - (i + 30) * 2, (i + 29) * 2,
                       2, h2 - i * 4 - 58, PATCOPY);
                DeleteObject(SelectObject(g_13dc, oldbrush));
            }
        }
        oldpen = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
        MoveTo(g_13dc, 0, g_8e5a);
        LineTo(g_13dc, LO16(g_90ea), g_8e5a);
        DeleteObject(SelectObject(g_13dc, oldpen));
        LoadString(g_9212, 0x80f, buf, 6);
        s[0] = buf[0];
        s[1] = 0;
        if (LO16(g_90ea) < 660) {
            PatBlt(g_13dc, g_93b8, g_8e5a + 12, g_93dc, h = 45, BLACKNESS);
            if (g_90f0)
                col = 0x200a0ffL;
            else
                col = 0x80ffL;
            for (i = 0; i < 5; i++) {
                s[0] = buf[i];
                fn_11_2154(0, 0xffL, i * 14 + g_93b8 + 6, g_8e5a + 16, s);
            }
        } else if (LO16(g_90ea) < 760) {
            PatBlt(g_13dc, g_93b8, g_8e5a + 12, g_93dc, h = 60, BLACKNESS);
            for (i = 0; i < 5; i++) {
                s[0] = buf[i];
                fn_10_94c4(0, 0, 0xffL, i * 18 + g_93b8, g_8e5a + 16, s);
            }
        } else {
            PatBlt(g_13dc, g_93b8, g_8e5a + 12, g_93dc, h = 60, BLACKNESS);
            for (i = 0; i < 5; i++) {
                s[0] = buf[i];
                fn_10_94c4(0, 0, 0xffL, i * 22 + g_93b8 + 25, g_8e5a + 16, s);
            }
        }
        g_5018 = -1;
        fn_11_04ea();
        oldpen = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
        MoveTo(g_13dc, g_93dc + g_93b8, g_8e5a + 12);
        LineTo(g_13dc, g_93dc + g_93b8, h + g_8e5a + 12);
        LineTo(g_13dc, g_93b8, h + g_8e5a + 12);
        DeleteObject(SelectObject(g_13dc, oldpen));
        fn_11_1774(2, g_93ba, g_8e5a, g_93ba + g_5024, g_8e5a + 84);
        memdc = CreateCompatibleDC(g_13dc);
        oldbmp = SelectObject(memdc, g_5030[7]);
        BitBlt(g_13dc, g_93bc, g_8e5a, 30, 85, memdc, 0, 0, SRCCOPY);
        SelectObject(memdc, oldbmp);
        DeleteDC(memdc);
        g_93d4 = -1;
        fn_11_0978();
        fn_11_1774(4, g_93be, g_8e5a, g_93be + 99, g_8e5a + 84);
        memdc = CreateCompatibleDC(g_13dc);
        oldbmp = SelectObject(memdc, g_5030[6]);
        BitBlt(g_13dc, g_93c0, g_8e5a + 24, 84, 61, memdc, 0, 0, SRCCOPY);
        SelectObject(memdc, oldbmp);
        DeleteDC(memdc);
        fn_11_05fe(1);
        g_5028 = g_1e50;
        g_93da = g_93d8 == 0;
        fn_11_0894();
        fn_10_949c(g_13dc, g_93c2, g_8e5a + 1, 55, 17, 0);
        memdc = CreateCompatibleDC(g_13dc);
        oldbrush = SelectObject(g_13dc, CreateSolidBrush(RGB(0, 255, 0)));
        oldbmp = SelectObject(memdc, g_5030[4]);
        BitBlt(g_13dc, g_93c2 + 23, g_8e5a + 4, 10, 10, memdc, 100, 0, MERGECOPY);
        SelectObject(memdc, oldbmp);
        DeleteDC(memdc);
        DeleteObject(SelectObject(g_13dc, oldbrush));
        fn_11_1ef6(1);
        fn_11_1774(2, g_93c4, g_8e5a, g_93c4 + g_5026, g_8e5a + 84);
    }
    switch (g_90f4) {
    case 1:
    case 7:
        if (g_951a == 0) {
            if (subgame_active) {
                if (g_6da4 != 0)
                    g_6da4->f_1c = 1;
            } else {
                fn_07_11cc();
                fn_07_1208();
                g_058c = 1;
                fn_07_1f38();
                fn_11_33cc();
            }
        }
        break;
    case 0:
        if (g_95b8 >= 6) {
            if (g_92d4 >= 2)
                g_92d4 = 9;
            else
                BitBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, g_929a, 0, 0, SRCCOPY);
        } else if (g_95b8 != 0) {
            if (g_95b8 < 3)
                g_6e28 = GetCurrentTime();
            else if (g_6e28 != g_1e50)
                g_6e28 = GetCurrentTime() + 15000;
        }
        fn_15_5962(1);
        break;
    case 6:
        fn_16_0cfe(1);
        if (subgame_active && g_6da4 != 0)
            g_6da4->f_1c = 1;
        break;
    case 8:
        fn_16_6928(1);
        break;
    case 2:
        fn_09_6dec(1);
        break;
    case 3:
        if (g_93aa != 18)
            draw_briefing_panel_with_esc_prompt(0);
        break;
    case 5:
        fn_06_5f7a(1);
        break;
    case 4:
        fn_09_6a12();
        break;
    }
    if (oldpal)
        SelectPalette(g_13dc, oldpal, 0);
    if (gotdc) {
        ReleaseDC(g_0016, g_13dc);
        g_13dc = 0;
    }
}

/* Fire weapon k from object (type, n): find or grow a free shot slot
 * (type 6 objects), pay the ammo or energy cost, aim the shot (homing
 * target search for kind 5) and launch it [inferred]. */
/* 11:7c12 */
void fn_11_7c12(int16_t k, int16_t type, int16_t n)
{
    int16_t s;
    int16_t i;
    int16_t unused08;               /* frame slot never used */
    int16_t w;
    int16_t tt;
    int16_t tn;
    int16_t bestd;
    int16_t dx;
    int16_t dy;
    int16_t dist;
    int16_t dir;
    int16_t ang;
    int16_t unused1c;               /* frame slot never used */
    int16_t ok;
    int16_t done;

    s = -1;
    done = 0;
    if (g_9406[6] >= 10)
        return;
    do {
        if (++s >= g_92ec[6]) {
            g_92ec[6] = s + 1;
            GlobalUnlock(g_9100[6]);
            g_9100[6] = GlobalReAlloc(g_9100[6], (int32_t)(g_92ec[6] < 1 ? 1 : g_92ec[6]) * (int32_t)sizeof *g_1df8[0], 0x42);
            g_1df8[6] = (REC_70 *)GlobalLock(g_9100[6]);
            g_1df8[6][s].f_18 = 1;
            g_1df8[6][s].f_44 = 20;
            g_1df8[6][s].f_42 = 100;
            g_1df8[6][s].f_4c = 0x7f00;
            g_1df8[6][s].f_2c = -1;
            g_1df8[6][s].f_48 = 5;
            g_1df8[6][s].f_62 = fn_11_3914;
            g_1df8[6][s].f_5e = fn_07_2652;
            if (k == 16)
                g_1df8[6][s].f_53 = 1;
            else
                g_1df8[6][s].f_53 = 0;
            g_1df8[6][s].f_54 = 0;
            g_1df8[6][s].f_32 = -1;
            g_1df8[6][s].f_12 = g_1df8[6][s].f_24;
            g_1df8[6][s].f_2e = 0;
            g_6670[s + 4].f_04.x = -1;
            g_9406[6] = s + 1;
        }
        if ((g_1df8[6][s].f_18 != 0
             || g_2f4c[g_6670[s + 4].f_04.x].f_26 <= g_6670[s + 4].r.right && g_2f4c[g_6670[s + 4].f_04.x].f_2c != 6
             || g_6670[s + 4].r.right == 0)
            && g_1df8[6][s].f_51 == 0)
            g_6670[s + 4].f_04.x = -1;
        ok = 0;
        if (type == g_9324) {
            for (i = 1; i < g_7090[n].cnt; i++)
                if (g_7090[n].f_0b8[i] == k) {
                    if (g_7090[n].f_0ae[i] > 0 && g_2f4c[k].f_36 == 0
                        || g_2f4c[k].f_36 > 0
                           && (type != 14 || g_2f4c[k].f_36 < g_7090[n].f_01e))
                        ok = 1;
                    w = i;
                    break;
                }
        } else
            ok = 1;
        if (g_6670[s + 4].f_04.x == -1 && ok != 0) {
            done = 1;
            for (i = 0; i < g_9406[6]; i++)
                if (g_6670[i + 4].r.right > 0 && g_6670[i + 4].r.right < 15 && g_6670[i + 4].r.left == type
                    && g_6670[i + 4].r.top == n && g_6670[i + 4].f_04.x != -1)
                    return;
            if (type == g_9324) {
                if (g_2f4c[k].f_36 == 0)
                    g_7090[n].f_0ae[w]--;
                else
                    g_7090[n].f_01e = max(g_7090[n].f_01e - g_2f4c[k].f_36, 0);
            }
            PostMessage(g_0a7e, WM_PAINT, 0, 0L);
            g_6670[s + 4].r.right = 0;
            g_6670[s + 4].f_18 = 0;
            g_6670[s + 4].f_04.x = k;
            g_6670[s + 4].f_16 = 0;
            g_6670[s + 4].f_14 = 2;
            g_1df8[6][s].f_00.x = -1000;
            g_1df8[6][s].f_00.y = -1000;
            g_1df8[6][s].f_08.x = -1000;
            g_1df8[6][s].f_08.y = -1000;
            if (g_2f4c[k].f_12 == 2 && type == g_9324) {
                if (n != main_ship || flow_interactive == 0)
                    fn_03_00f4(n, g_7090[n].f_032.a, g_7090[n].f_032.b);
                g_6670[s + 4].f_00.x = LO16(g_7090[n].f_03e);
                g_6670[s + 4].f_00.y = HI16(g_7090[n].f_03e);
                g_6670[s + 4].f_1a = 0;
            } else {
                g_6670[s + 4].f_00.x = -1;
                g_6670[s + 4].f_1a = 0;
            }
            g_1df8[6][s].f_18 = 0;
            g_1df8[6][s].f_2e = 0;
            g_1df8[6][s].f_22 = SC(g_2f4c[k].f_00);
            if (g_2f4c[k].f_00 & 1) {
                g_1df8[6][s].f_22 = SC(g_2f4c[k].f_00 + 1);
                g_1df8[6][s].f_24 = SC(4);
            } else
                g_1df8[6][s].f_24 = SC(6);
            g_1df8[6][s].f_12 = g_1df8[6][s].f_24;
            g_1df8[6][s].f_20 = g_2f4c[k].f_00 * 8;
            g_1df8[6][s].f_48 = g_2f4c[k].f_2a;
            g_1df8[6][s].f_50 = 0;
            g_1df8[6][s].f_44 = g_2f4c[k].f_18;
            g_1df8[6][s].f_2c = g_2f4c[k].f_10;
            g_1df8[6][s].f_1e = 0;
            g_1df8[6][s].f_28 = g_1df8[type][n].f_28;
            g_1df8[6][s].f_04.x = g_1df8[type][n].f_04.x;
            g_1df8[6][s].f_04.y = g_1df8[type][n].f_04.y;
            if (g_2f4c[k].f_06 == -1) {
                if (g_92e8)
                    g_6670[s + 4].r.right = g_2f4c[k].f_26 / 4;
                fn_06_84fc((rand() % 2 + 1) * 10, 0, 0, 0, 0, 0, 0, 0, g_2f4c[k].f_26 - 1, s);
            }
            if (g_2f4c[k].f_2c == 4 || g_2f4c[k].f_2c == 6)
                g_1df8[6][s].f_66 = fn_07_2e02;
            else
                g_1df8[6][s].f_66 = fn_12_274a;
            if (k == 16) {
                g_1df8[6][s].f_53 = 1;
                for (i = 0; i < g_9316; i++)
                    if (g_96d2[g_7090[i].f_04e].f_38 == 7) {
                        g_7090[i].f_006 = 6;
                        g_7090[i].f_008 = s;
                        g_7090[i].f_036 = g_7090[i].f_03a = 2;
                        g_7090[i].f_094 = g_1e50 + 100;
                    }
            } else
                g_1df8[6][s].f_53 = 0;
            if (g_2f4c[k].f_12 == 5) {
                g_1df8[6][s].f_0c = g_1df8[type][n].f_0c;
                g_1df8[6][s].f_0e = g_1df8[type][n].f_0e;
                g_1df8[6][s].f_04.x += g_1df8[type][n].f_20 / 2 - g_1df8[6][s].f_20 / 2;
                g_1df8[6][s].f_04.y += g_1df8[type][n].f_20 / 2 - g_1df8[6][s].f_20 / 2;
                tt = -1;
                if (g_2f4c[k].f_4e != 0)
                    for (i = 0; i < g_9406[6]; i++)
                        if (g_6670[i + 4].r.left != type || g_6670[i + 4].r.top != n) {
                            dist = fn_08_285a(&dx, &dy, g_1df8[6][s].f_04, g_1df8[6][i].f_04);
                            if (dist < 350) {
                                tt = 6;
                                tn = i;
                            }
                        }
                if (tt == -1) {
                    tt = -1;    /* sic */
                    bestd = 20000;
                    for (i = 0; i < g_9146; i++) {
                        if ((g_507c[i] != type || g_50e0[i] != n)
                            && g_1df8[g_507c[i]][g_50e0[i]].f_44 > 1) {
                            dist = fn_08_285a(&dx, &dy, g_1df8[g_507c[i]][g_50e0[i]].f_04,
                                              g_1df8[type][n].f_04);
                            if (g_507c[i] == g_9324) {
                                dist = (int16_t)(dist * 3) / 4;
                                if (type == g_9324 && g_7090[n].f_032.a == g_9324
                                    && g_7090[n].f_032.b == g_50e0[i])
                                    dist /= 6;
                                else if (type == g_9324
                                         && (fn_13_2688(n, g_50e0[i]) > 150
                                             || g_96d2[g_7090[g_50e0[i]].f_04e].f_38
                                                == g_96d2[g_7090[n].f_04e].f_38))
                                    dist = (dist + 50) * 5;
                            }
                            dir = fn_08_19b0(-dx, -dy);
                            ang = g_1df8[type][n].f_28;
                            if ((int16_t)(ang - 1) <= dir && (int16_t)(ang + 1) >= dir)
                                dist = (int16_t)(dist * 2) / 3;
                            if (dist < bestd) {
                                tt = g_507c[i];
                                tn = g_50e0[i];
                                bestd = dist;
                            }
                        }
                    }
                }
                if (tt != -1) {
                    fn_08_348e(6, s, tt, tn, g_2f4c[k].f_16);
                    ang = fn_08_19b0(g_1df8[6][s].f_0c - g_1df8[type][n].f_0c,
                                     g_1df8[6][s].f_0e - g_1df8[type][n].f_0e);
                    g_1df8[6][s].f_04.x += (g_1df8[6][s].f_20 / 2 + g_1df8[type][n].f_20 / 8)
                                          * g_1050[ang].x * 5 / 20;
                    g_1df8[6][s].f_04.y += (g_1df8[6][s].f_20 / 2 + g_1df8[type][n].f_20 / 8)
                                          * g_1050[ang].y * 5 / 20;
                }
                if (g_1df8[type][n].f_0c == g_1df8[6][s].f_0c
                    && g_1df8[type][n].f_0e == g_1df8[6][s].f_0e) {
                    g_1df8[6][s].f_0c = g_1050[g_1df8[type][n].f_28].x * 8 + g_1df8[type][n].f_0c;
                    g_1df8[6][s].f_0e = g_1050[g_1df8[type][n].f_28].y * 8 + g_1df8[type][n].f_0e;
                    ang = fn_08_19b0(g_1df8[6][s].f_0c - g_1df8[type][n].f_0c,
                                     g_1df8[6][s].f_0e - g_1df8[type][n].f_0e);
                    g_1df8[6][s].f_04.x += (g_1df8[6][s].f_20 / 2 + g_1df8[type][n].f_20 / 2)
                                          * g_1050[ang].x / 20;
                    g_1df8[6][s].f_04.y += (g_1df8[6][s].f_20 / 2 + g_1df8[type][n].f_20 / 2)
                                          * g_1050[ang].y / 20;
                }
            } else if (g_2f4c[k].f_0c == 1 || type != g_9324) {
                g_1df8[6][s].f_04.x += (int16_t)(g_1df8[type][n].f_20 - g_1df8[6][s].f_20) / 2
                    + (int16_t)(g_1df8[type][n].f_20 + g_1df8[6][s].f_20) / 2
                      * g_1050[g_1df8[type][n].f_28].x / 15;
                g_1df8[6][s].f_04.y += (int16_t)(g_1df8[type][n].f_20 - g_1df8[6][s].f_20) / 2
                    + (int16_t)(g_1df8[type][n].f_20 + g_1df8[6][s].f_20) / 2
                      * g_1050[g_1df8[type][n].f_28].y / 15;
                g_1df8[6][s].f_0c = g_1050[g_1df8[type][n].f_28].x * 4;
                g_1df8[6][s].f_0e = g_1050[g_1df8[type][n].f_28].y * 4;
                if (type == g_9324)
                    g_7090[n].f_0a0 = g_1e68 + 36;
            } else if (g_2f4c[k].f_0c == 2 && type == g_9324) {
                g_1df8[6][s].f_04.x += (g_7ba0[g_7090[n].f_04e][g_1df8[type][n].f_28].x << 3)
                    + g_1050[(int16_t)(g_1df8[type][n].f_28 + 8) % 16].x * 11 / 4
                    - g_1df8[6][s].f_20 / 2;
                g_1df8[6][s].f_04.y += (g_7ba0[g_7090[n].f_04e][g_1df8[type][n].f_28].y << 3)
                    + g_1050[(int16_t)(g_1df8[type][n].f_28 + 8) % 16].y * 11 / 4
                    - g_1df8[6][s].f_20 / 2;
                g_1df8[6][s].f_0c = -(g_1050[g_1df8[type][n].f_28].x * 4);
                g_1df8[6][s].f_0e = -(g_1050[g_1df8[type][n].f_28].y * 4);
                g_1df8[6][s].f_04.x -= g_1df8[g_9324][n].f_0c;
                g_1df8[6][s].f_04.y -= g_1df8[g_9324][n].f_0e;
            }
            g_6670[s + 4].r.right = 0;
            if (g_2f4c[k].f_12 != 5) {
                g_1df8[6][s].f_0c += g_1df8[type][n].f_0c;
                g_1df8[6][s].f_0e += g_1df8[type][n].f_0e;
            }
            g_6670[s + 4].r.left = type;
            g_6670[s + 4].r.top = n;
            if (type == g_9324 && n == main_ship)
                fn_10_744c(0x69);
            fn_10_7944(g_2f4c[k].f_20, 6, s, 1, "");
        }
    } while (!done && ok);
    fn_07_2080(6);
    if (g_1df8[6][0].f_18 == 0 && g_6670[0 + 4].f_04.x == -1)
        g_9498++;
}
