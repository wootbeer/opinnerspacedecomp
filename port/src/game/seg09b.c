
#include "game.h"

/* g_05a0 is declared long in inspace.h; read here as two ints (world
 * width and height [inferred]). */
                                       
                                       

#define SC(n) ((n) << g_9156 >> 1)

/* 9:0b2a */
void fn_09_0b2a(void)
{
    int16_t i;
    int16_t unused;

    for (i = 0; i < g_9406[0]; i++) {
        g_57a8[i].f_06 = -1;
        if (g_94b0) {
            g_1df8[0][i].f_1e = -1;
            g_69f4[g_94a2].f_1d2[i] = g_1df8[0][i].f_1e;
        }
        g_1df8[0][i].f_18 = 1;
    }
    for (i = 0; i < g_9406[1]; i++)
        g_1df8[1][i].f_18 = 1;
    if (g_94b0) {
        g_69f4[g_94a2].f_1d1 = 0;
        g_69f4[g_94a2].f_150 = 0;
        g_69f4[g_94a2].f_14e = g_69f4[g_94a2].f_150;
    }
    fn_09_0000(8);
}

/* 9:0c06 */
void fn_09_0c06(void)
{
    int16_t i;
    int16_t j;

    for (i = 0; i < 2; i++)
        fn_13_4eca("\n\r");
    fn_13_4eca("START OF GAME! \n\r");
    fn_02_16a2();
    g_0992 = 0;
    if (g_92e4 == 0) {
        g_1e58 = 0;
        g_5078 = 0;
        g_9346 = -1;
        g_91f8 = 0;
        g_967c = 0;
        g_94ca = 0;
        g_93ac = 0;
        for (i = 0; i < 8; i++)
            for (j = 0; j < 3; j++)
                g_4eec[i][j] = -1;
        g_9432 = 100;
        g_a1cf = 1;
        g_a1cd = 0;
        for (i = 0; i < 4; i++)
            g_a193[i] = 1;
    }
    for (i = 0; i < 6; i++)
        g_0986[i] = 1;
    g_0986[5] = 2;
    g_5018 = -1;
    for (i = 0; i < 4; i++)
        g_a18f[i] = 1;
    g_953e = g_9540 = g_953f = g_9541 = 0;
    for (j = 1; j < 27; j++)
        g_9564[j] = g_9542[j] = 0;
    g_9563 = 0;
    g_1e84 = 0;
    g_1e80 = 0;
    g_a161 = -1;
    if (g_9156 != 1) {
        fn_10_0552(5, 1);
        fn_10_39a8(1);
        fn_10_0552(0x16, 1);
    }
    fn_09_5cca();
}

/* 9:0d6c */
void fn_09_0d6c(void)
{
    int16_t i;

    fn_13_65f2(1);
    fn_11_02f0();
    if (g_13de == 0) {
        g_1e78 = g_1e50 + 25000;
        g_90f4 = 4;
    }
    g_1e88 = 0;
    fn_10_022e(0);
    for (i = 0; i < 10; i++)
        g_96d2[i].f_38 = g_96d2[i].f_4e = 0;
    PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    if (g_13de == 0)
        fn_09_6a12();
}

/* 9:1092 */
void fn_09_1092(void)
{
    int16_t i;

    for (i = 0; i < 32; i++) {
        if (g_4e94[i]) {
            DeleteObject(g_4e94[i]);
            g_4e94[i] = 0;
        }
    }
}

/* 9:225a */
PAIR fn_09_225a(int16_t a)
{
    PAIR v;
    int16_t idx;
    int16_t t;
    int16_t unused;

    v.a = g_9f40[g_9322][a].a;
    v.b = g_9f40[g_9322][a].b;
    t = g_9ec2[g_9322][a];
    g_1df8[8][g_9318 * 2 + a].f_51 = t + g_9318 * 2;
    return v;
}
/* 9:27da */
void fn_09_27da(int16_t a)
{
    if (g_92e6 == 0)
        fn_10_6d52(g_13dc, LO16(g_90ea) / 4, g_0010 * 3 / 4 - 10, LO16(g_90ea) / 2, 20, a);
}

/* 9:484c */
void fn_09_484c(void)
{
    int16_t i;

    g_9334 = 0;
    for (i = 0; i < 12; i++) {
        if (g_09bc[i] < g_5078)
            g_9334 = i + 1;
    }
}

/* 9:5be0 */
void fn_09_5be0(int16_t n, int16_t k)
{
    char buf[34];
    int16_t i;

    if (n != g_9646 && g_92e8 == 0) {
        fn_13_218a(g_6e24[k].f_64, buf);
        for (i = 0; i < 20; i++) {
            if (buf[i] == ' ') {
                buf[i] = 0;
                break;
            } else if (buf[i] == 'S' && buf[i + 1] == 0) {
                buf[i] = 0;
                break;
            }
        }
        lstrcpy(g_6e24[k].f_65, buf);
        fn_06_0f1a(k, buf);
        lstrcat(g_6e24[k].f_65, " ");
        lstrcat(g_6e24[k].f_65, buf);
    } else
        lstrcpy(g_6e24[k].f_65, g_380c);
}

/* Per-segment side flags (+52) of the track polygon at g_1df8[8] and the bounding rects g_67f8 [inferred]. */
/* 9:2012 */
void fn_09_2012(void)
{
    POINT pa;
    POINT pb;
    POINT pc;
    POINT d1;
    POINT d2;
    int16_t i;
    int32_t l1;
    int32_t l2;
    int32_t r;

    for (i = 0; i < g_9ea2; i++) {
        g_240c = g_1df8[8][g_9318 * 2 + i].f_04.x - (LO16(g_90ea) << (g_9150 - 1));
        g_2410 = g_1df8[8][g_9318 * 2 + i].f_04.y - (HI16(g_90ea) << (g_9150 - 1));
        pa = fn_08_29ea(g_1df8[8][g_9318 * 2 + i].f_04);
        if (i < g_9ea2 - 1)
            pb = fn_08_29ea(g_1df8[8][g_9318 * 2 + i + 1].f_04);
        else
            pb = fn_08_29ea(g_1df8[8][g_9318 * 2].f_04);
        if (i > 0)
            pc = fn_08_29ea(g_1df8[8][g_9318 * 2 + i - 1].f_04);
        else
            pc = fn_08_29ea(g_1df8[8][g_9318 * 2 + g_9ea2 - 1].f_04);
        d1.x = pa.x - pc.x;
        d1.y = pa.y - pc.y;
        l2 = (int16_t)fn_08_35d0(d2.x = pb.x - pa.x, d2.y = pb.y - pa.y);
        l1 = (int16_t)fn_08_35d0(d1.x, d1.y);
        r = (((int32_t)d2.y * d1.x - (int32_t)d2.x * d1.y) << 7) / (l2 * l1);
        if (r > 0)
            g_1df8[8][g_9318 * 2 + i].f_52 = 0;
        else
            g_1df8[8][g_9318 * 2 + i].f_52 = 1;
    }
    for (i = 0; i < g_9eb9[g_9322]; i++) {
        g_67f8[i].left = min(g_9f40[g_9322][g_9ec2[g_9322][i]].a, g_9f40[g_9322][i].a);
        g_67f8[i].right = max(g_9f40[g_9322][g_9ec2[g_9322][i]].a, g_9f40[g_9322][i].a);
        g_67f8[i].top = min(g_9f40[g_9322][g_9ec2[g_9322][i]].b, g_9f40[g_9322][i].b);
        g_67f8[i].bottom = max(g_9f40[g_9322][g_9ec2[g_9322][i]].b, g_9f40[g_9322][i].b);
    }
}

/* Places object n of type 4 at a random spot outside the centre rect [inferred]. */
/* 9:0df6 */
void fn_09_0df6(int16_t n)
{
    int16_t i;
    int16_t unused;
    int16_t again;
    RECT rc;

    again = 1;
    while (again) {
        g_1df8[4][n].f_04.x = (rand() % ((LO16(g_05a0)) - 150) + 150) * 8;
        g_1df8[4][n].f_04.y = (rand() % ((HI16(g_05a0)) - 150) + 150) * 8;
        g_1df8[4][n].f_00.x = g_1df8[4][n].f_08.x = -1000;
        g_1df8[4][n].f_00.y = g_1df8[4][n].f_08.y = -1000;
        g_1df8[4][n].f_0c = -(rand() % 50 - 25);
        g_1df8[4][n].f_0e = -(rand() % 50 - 25);
        g_1df8[4][n].f_26 = 0;
        if ((g_9214 == 3 || g_9214 == 4) && n % 2 == 1)
            g_1df8[4][n].f_26 = 5;
        if (g_9214 == 1 || g_9214 == 2)
            g_1df8[4][n].f_66 = fn_07_2e02;
        else if (g_9214 == 4 && n % 2 == 0)
            g_1df8[4][n].f_66 = fn_07_2e02;
        else
            g_1df8[4][n].f_66 = fn_12_274a;
        g_1df8[4][n].f_2f = 0;
        g_1df8[4][n].f_1e = 0;
        g_1df8[4][n].f_50 = 0;
        g_1df8[4][n].f_51 = 0;
        g_1df8[4][n].f_18 = 0;
        if (g_9320 == 6)
            g_1df8[4][n].f_18 = 1;
        SetRect(&rc, ((LO16(g_05a0)) / 2 - LO16(g_90ea) / 2) << g_9150, ((HI16(g_05a0)) / 2 - HI16(g_90ea) / 2) << g_9150,
                (LO16(g_90ea) / 2 + (LO16(g_05a0)) / 2) << g_9150, (HI16(g_90ea) / 2 + (HI16(g_05a0)) / 2) << g_9150);
        again = 0;
        if (PtInRect(&rc, g_1df8[4][n].f_04))
            again = 1;
        if (g_9406[4] == 17 && n == g_9406[4] - 1) {
            g_1df8[4][0].f_0c = g_1df8[4][0].f_0e = 0;
            for (i = 1; i < g_9406[4]; i++) {
                g_1df8[4][i].f_04.y = (g_104c[i].a * 208 + g_1df8[4][0].f_04.y) % ((HI16(g_05a0)) * 8);
                g_1df8[4][i].f_04.x = (g_104c[i].b * 208 + g_1df8[4][0].f_04.x) % ((LO16(g_05a0)) * 8);
                g_1df8[4][i].f_0c = g_1df8[4][i].f_0e = 0;
            }
        }
    }
}

/* End-of-wave bookkeeping: music cues, racer records (DS:6e24), ratings
 * and the wave summary in DS:69f4 [inferred]. */
/* 9:2828 */
void fn_09_2828(void)
{
    int16_t n;
    int16_t u06;
    int16_t mode;
    int16_t u0a;
    int16_t k;
    int16_t u0e;
    int16_t rank;
    int16_t u12;
    int16_t d;
    int16_t any7;
    int16_t u18;
    int16_t found;
    int16_t m;
    int16_t a;
    int16_t b;

    any7 = 0;
    for (n = 0; n <= g_9316; n++) {
        fn_13_2688(n, g_9646);
        if (g_96d2[g_7090[n].f_04e].f_38 == 7)
            any7 = 1;
    }
    if ((g_8f70 != 0 || flow_interactive == 0) && g_9320 == 6 && g_91f8 != 0) {
        fn_06_8b90(g_9322);
        switch (g_9ea0) {
        case 1:
            b = 0;
            break;
        case 5:
            b = 1;
            break;
        case 10:
            b = 2;
            break;
        }
        for (n = 0; n <= g_9316; n++) {
            if (n == g_9646 && flow_interactive)
                a = 0;
            else
                a = 1;
            if (g_1df8[14][n].f_51 != 0) {
                if (b > 0) {
                    fn_06_8cb2(g_9322, n, (uint16_t)(g_9e60[n] > 64000 ? 64000 : g_9e60[n]), b, 1);
                    if (a == 0)
                        fn_06_8cb2(g_9322, n, (uint16_t)(g_9e60[n] > 64000 ? 64000 : g_9e60[n]), b, 0);
                }
                fn_06_8cb2(g_9322, n, (uint16_t)(g_9e90[n] > 64000 ? 64000 : g_9e90[n]), 0, 1);
                if (a == 0)
                    fn_06_8cb2(g_9322, n, (uint16_t)(g_9e90[n] > 64000 ? 64000 : g_9e90[n]), 0, 0);
            }
        }
        fn_06_8dfe(g_9322);
        fn_06_8eb4();
    }
    for (n = 0; n <= g_9316; n++)
        if (g_7090[n].flag && g_96d2[g_7090[n].f_04e].f_38 == 7 && g_7090[n].f_05e == 0
            && g_7090[n].f_054 == 14 && g_7090[n].f_056 == g_9646)
            g_9346 = g_7090[g_9646].f_0d6;
    if (g_9432 < 50)
        g_9332 = 3;
    else if (g_9432 < 180)
        g_9332 = 2;
    else if (g_9432 < 400)
        g_9332 = 1;
    else
        g_9332 = 0;
    g_932c = 0;
    if (g_964a == 0)
        mode = 1;
    else if (g_964a == 0 && g_9332 < 2)
        mode = 2;
    else if (g_964a > 0 && g_964a < 5)
        mode = 2;
    else if (g_964a > 4 && g_964a < 9)
        mode = 3;
    else if (g_964a > 8 && g_964a < 16) {
        if (g_9332 < 2 || any7)
            mode = 4;
        else
            mode = 3;
    } else if (g_964a > 15)
        mode = 4;
    switch (mode) {
    case 0:
        g_932c = 0;
        break;
    case 1:
        if (rand() % 100 < 20)
            g_932c = 1;
        break;
    case 2:
        if (rand() % 100 < 50)
            g_932c = 1;
        break;
    case 3:
        if (rand() % 100 < 80)
            g_932c = 1;
        break;
    case 4:
        g_932c = 1;
        break;
    }
    if (g_91f8 == 0)
        g_932c = 0;
    if (g_91f8 > 0) {
        b = g_9214;
        fn_10_9672();
        if (b != g_9214)
            fn_10_0552(4, 1);
        fn_10_565a();
    }
    if (g_91f8 > 0) {
        for (n = 0; n <= g_9316; n++) {
            fn_11_b09c(n, 0);
            if (g_7090[n].f_0d6 == -1)
                continue;
            for (k = 0; k <= g_9316; k++)
                g_6e24[g_7090[n].f_0d6].f_3c[g_7090[k].f_0d6] = g_7090[n].f_062[k] / 10;
            for (k = 0; k < 4; k++)
                g_6e24[g_7090[n].f_0d6].f_38[k] = g_7090[n].f_026[k];
            if (g_7090[n].flag == 0)
                g_6e24[g_7090[n].f_0d6].f_38[0] = 0;
            for (k = 0; k < g_7090[n].cnt; k++) {
                g_6e24[g_7090[n].f_0d6].f_28[k] = g_7090[n].f_0b8[k];
                g_6e24[g_7090[n].f_0d6].f_1e[k] = g_7090[n].f_0ae[k];
            }
            g_6e24[g_7090[n].f_0d6].f_1d = g_7090[n].cnt;
            fn_14_421c(n);
            g_6e24[g_7090[n].f_0d6].f_06 = g_7090[n].f_082;
            g_6e24[g_7090[n].f_0d6].f_1c = g_7090[n].f_01e / 40;
            g_6e24[g_7090[n].f_0d6].f_74 = LO8(g_7090[n].f_024);
            g_6e24[g_7090[n].f_0d6].f_75 = LO8(g_7090[n].f_00a);
            g_6e24[g_7090[n].f_0d6].f_72 = g_7090[n].f_0ac;
            g_6e24[g_7090[n].f_0d6].f_73 = g_7090[n].f_0ad;
            g_6e24[g_7090[n].f_0d6].f_04 = g_7090[n].f_0ce;
            g_7090[n].f_0dc = g_7090[n].f_0dc > 327670L ? 327670L : g_7090[n].f_0dc;
            g_6e24[g_7090[n].f_0d6].f_02 = g_7090[n].f_0dc / 10;
            u12 = (g_7090[n].f_0dc * 3 + g_7090[n].f_0d8) / 100;
            for (k = 1; k < 11; k++)
                if (g_0952[k] <= u12 && g_096c[k] > u12) {
                    rank = k;
                    break;
                }
            g_6e24[g_7090[n].f_0d6].f_76 = rank;
        lbl:    /* bare label: resets register tracking (recompute g_7090[n]) */
            u0e = g_9646;
            if (g_7090[n].flag == 0 || g_7090[n].f_082 < 0 || n == u0e) {
                for (k = 0; k < 8; k++)
                    if (g_69f4[g_94a2].f_1c0[k] == g_7090[n].f_0d6)
                        g_69f4[g_94a2].f_1c0[k] = -1;
            } else {
                found = 0;
                for (k = 0; k < 8; k++)
                    if (g_69f4[g_94a2].f_1c0[k] == g_7090[n].f_0d6)
                        found = 1;
                if (!found)
                    for (k = 0; k < 8; k++)
                        if (g_69f4[g_94a2].f_1c0[k] == -1) {
                            g_69f4[g_94a2].f_1c0[k] = g_7090[n].f_0d6;
                            break;
                        }
            }
        }
        g_931c = g_7090[g_9646].f_0d6;
        for (n = 0; n <= g_931a; n++) {
            if (g_1e68 > 500) {
                if (g_6e24[n].f_76 + 3 < g_9334)
                    d = g_6e24[n].f_06 / -3;
                else if (g_6e24[n].f_76 + 1 < g_9334)
                    d = -(g_6e24[n].f_06 / 8);
                else
                    d = g_6e24[n].f_06 / -14;
                b = 0;
                if (g_95a6 == 0) {
                    fn_14_3eda();
                    b = 1;
                }
                a = fn_09_88ba(g_6e20[g_6e24[n].f_00].f_04[1] - g_9332);
                d += g_6e24[n].f_06 * a / -20;
                if (b)
                    fn_14_4074();
                g_6e24[n].f_06 = g_6e24[n].f_06 + d < 0 ? 0 : g_6e24[n].f_06 + d;
            }
        }
        for (n = m = 0; m < 8; m++, n++) {
            k = 0;
            if (g_1df8[0][m].f_18 != 0)
                for (k = m + 1; k < 8; k++)
                    if (g_1df8[0][k].f_18 == 0) {
                        m = k;
                        break;
                    }
            if (k >= 8)
                break;
            if (g_1df8[0][m].f_2f < 0)
                (g_69f4[g_94a2].f_1c0 + 8)[n] = 2;
            if (g_1df8[0][m].f_53 == 2)
                (g_69f4[g_94a2].f_1c0 + 8)[n] = 1;
            g_69f4[g_94a2].f_1d2[n] = g_1df8[0][m].f_1e;
        }
        for (; n < 8; n++) {
            g_69f4[g_94a2].f_1d2[n] = 0;
            (g_69f4[g_94a2].f_1c0 + 8)[n] = 0;
        }
        g_69f4[g_94a2].f_0a0[3] = 0;
        g_69f4[g_94a2].f_0a0[0] = 0;
        g_69f4[g_94a2].f_0a0[1] = 0;
        for (n = 0; n < g_9406[9]; n++)
            if (g_1df8[9][n].f_18 == 0)
                g_69f4[g_94a2].f_0a0[3]++;
        for (n = 0; n < g_9406[3]; n++) {
            if (g_1df8[3][n].f_44 == 350 && g_1df8[3][n].f_18 == 0)
                g_69f4[g_94a2].f_0a0[0]++;
            if (g_1df8[3][n].f_44 == 1400 && g_1df8[3][n].f_18 == 0)
                g_69f4[g_94a2].f_0a0[1]++;
        }
        for (n = 0; n < g_9406[8]; n++) {
            g_69f4[g_94a2].f_0ae[n] = g_1df8[8][n].f_1e;
            if (g_3d50[n].f_0a == -3)
                g_69f4[g_94a2].f_0ae[n] = -g_69f4[g_94a2].f_0ae[n];
            g_69f4[g_94a2].f_0fe[n] = g_3d50[n].f_2e;
        }
    }
    if (g_7090[g_9646].flag && g_91f8 > 0 && (flow_interactive || g_9516 == 0))
        fn_06_885c(0, 0);
}

/* Places the race track pieces (type 8 and 12 objects), their gates and
 * the checkpoints at the start of a race [inferred]. */
/* 9:10d4 */
void fn_09_10d4(void)
{
    int16_t i;
    int16_t j;
    int16_t k;
    int16_t t;
    int16_t u0c;
    int16_t res;
    int16_t sel;
    int16_t u12;
    int16_t a;
    int16_t b;
    int16_t d;
    int16_t cnt;
    int16_t u1c;
    RECT rcw;
    RECT rc1;
    RECT rc2;
    RECT rc3;
    POINT pos;
    int16_t ok;
    int16_t flag;
    char pad46[14];             /* frame filler [inferred] */

    SetRect(&rcw, (LO16(g_05a0)) / 2 - 150, (HI16(g_05a0)) / 2 - 100,
            (LO16(g_05a0)) / 2 + 150, (HI16(g_05a0)) / 2 + 80);
    for (i = 0; i < g_9318 * 2; i++) {
        g_1df8[8][i].f_08.x = -1000;
        g_1df8[8][i].f_00.x = g_1df8[8][i].f_08.x;
        g_1df8[8][i].f_08.y = -1000;
        g_1df8[8][i].f_00.y = g_1df8[8][i].f_08.y;
        if (!g_94b0)
            g_1df8[8][i].f_1e = g_69f4[g_94a2].f_0ae[i];
        else
            g_1df8[8][i].f_1e = 0;
        if (g_94b0) {
            pos.x = (rand() % ((LO16(g_05a0)) - 60) + 30) * 8;
            pos.y = (rand() % ((HI16(g_05a0)) - 60) + 30) * 8;
        } else
            pos = g_69f4[g_94a2].f_000[i];
        if (i >= g_9318 * 2)
            g_1df8[8][i].f_04 = pos;
        g_1df8[8][i].f_18 = 0;
        g_1df8[8][i].f_24 = SC(6);
        g_1df8[8][i].f_2f = 2;
        g_1df8[8][i].f_54 = 1;
        if (i < g_9318 * 2) {
            g_3d50[i].f_30 = -1;
            g_1df8[8][i].f_44 = 3500;
            g_1df8[8][i].f_22 = SC(0x22);
            g_1df8[8][i].f_20 = 0x110;
            g_1df8[8][i].f_42 = 8;
            g_1df8[8][i].f_46 = 1;
            g_1df8[8][i].f_62 = fn_11_39d8;
            g_1df8[8][i].f_5e = fn_07_5090;
            g_3d50[i].f_1c = 3;
            if (!(i & 1)) {
                g_6670[i / 2].f_12 = 1200;
                g_6670[i / 2].f_16 = 0x50;
                if (g_9320 == 6) {
                    pos.x = g_a120[g_9322].x - g_6670[i / 2].f_12 / 2 - 160;
                    pos.y = g_a120[g_9322].y;
                } else if (g_94b0) {
                    pos.x = rand() % ((LO16(g_05a0)) - 300) * 8;
                    pos.y = (rand() % ((HI16(g_05a0)) - 200) + 200) * 8;
                }
                if (g_94b0 && g_9320 != 6) {
                    do {
                        SetRect(&rc1, pos.x - 720, pos.y - 720, pos.x + 2400, pos.y + 1200);
                        ok = 1;
                        for (j = 0; j < g_9324; j++)
                            for (k = 0; k < (&g_9406[0])[j]; k++) {
                                SetRect(&rc2, g_1df8[j][k].f_04.x - 160, g_1df8[j][k].f_04.y - 160,
                                        g_1df8[j][k].f_04.x + 320, g_1df8[j][k].f_04.y + 320);
                                if (IntersectRect(&rc3, &rc1, &rc2)) {
                                    ok = 0;
                                    pos.x = rand() % ((LO16(g_05a0)) - 300) * 8;
                                    pos.y = (rand() % ((HI16(g_05a0)) - 200) + 200) * 8;
                                    break;
                                }
                            }
                    } while (!ok);
                } else {
                    SetRect(&rc1, pos.x - 720, pos.y - 720, pos.x + 2400, pos.y + 1200);
                    for (t = 0; t <= 9; t++)
                        if (t == 0 || t == 4 || t == 3 || t == 9)
                            for (k = 0; k < (&g_9406[0])[t]; k++) {
                                SetRect(&rc2, g_1df8[t][k].f_04.x - 160, g_1df8[t][k].f_04.y - 160,
                                        g_1df8[t][k].f_04.x + 320, g_1df8[t][k].f_04.y + 320);
                                if (IntersectRect(&rc3, &rc1, &rc2))
                                    g_1df8[t][k].f_04.y = (g_1df8[t][k].f_04.y + 1600)
                                                         % ((HI16(g_05a0)) * 8);
                            }
                }
                g_1df8[8][i].f_04 = pos;
                g_1df8[8][i + 1].f_04 = pos;
                g_1df8[8][i + 1].f_04.x += g_1df8[8][i].f_20 + g_6670[i / 2].f_12;
                g_6670[i / 2].f_18 = i;
                g_1df8[12][i].f_04 = pos;
                g_1df8[12][i + 1].f_04 = pos;
                g_1df8[12][i].f_04.x += g_6670[i / 2].f_12 / 2 + 160;
                g_1df8[12][i].f_04.y -= 150;
                g_1df8[12][i + 1].f_04.x += g_6670[i / 2].f_12 / 2 + 160;
                SetRect(&g_6670[i / 2].r, g_1df8[8][i].f_04.x + g_1df8[8][i].f_20,
                        g_1df8[8][i].f_04.y + g_1df8[8][i].f_20 / 2 - 24,
                        g_1df8[8][i].f_04.x + g_1df8[8][i].f_20 + g_6670[i / 2].f_12,
                        g_1df8[8][i].f_04.y + g_1df8[8][i].f_20 / 2 + 24);
                g_1df8[12][i].f_44 = 0;
                g_1df8[12][i].f_22 = 0;
                g_1df8[12][i].f_20 = 0;
                g_1df8[12][i + 1].f_44 = 0;
                g_1df8[12][i + 1].f_22 = 0;
                if (i == 2)
                    g_6670[i / 2].f_1a = 1;
                if (i == 4)
                    g_6670[i / 2].f_1a = 2;
            }
        }
    }
    if (g_94b0 && g_9320 != 6)
        fn_09_4896();
    for (i = g_9318 * 2; i < g_9406[8]; i++) {
        g_1df8[8][i].f_08.x = -1000;
        g_1df8[8][i].f_00.x = g_1df8[8][i].f_08.x;
        g_1df8[8][i].f_08.y = -1000;
        g_1df8[8][i].f_00.y = g_1df8[8][i].f_08.y;
        if (!g_94b0) {
            g_1df8[8][i].f_1e = g_69f4[g_94a2].f_0ae[i];
            g_3d50[i].f_2e = g_69f4[g_94a2].f_0fe[i];
        } else
            g_1df8[8][i].f_1e = 0;
        if (g_94b0 || g_9320 == 6) {
            ok = 0;
            for (j = 0; j < g_9344; j++)
                if (g_4f2c[j].first <= i && g_4f2c[j].f_02 > i) {
                    ok = 1;
                    g_3d50[i].rest = j;
                    g_1df8[8][i].f_54 = 1;
                    break;
                }
            if (!ok) {
                g_3d50[i].rest = -1;
                ok = 0;
                if (g_9320 != 6)
                    do {
                        ok = 1;
                        pos.x = rand() % (LO16(g_05a0)) * 8;
                        pos.y = rand() % (HI16(g_05a0)) * 8;
                        for (j = 0; j < g_9318; j++)
                            if (fn_08_285a(&a, &b, pos, g_1df8[12][j * 2].f_04) < 150)
                                ok = 0;
                        for (j = 0; j < g_9344; j++) {
                            d = fn_08_285a(&a, &b, pos, g_4f2c[j].f_0a);
                            if ((g_4f2c[j].radius >> 3) + 200 > d)
                                ok = 0;
                        }
                        for (j = 0; j < i; j++) {
                            d = fn_08_285a(&a, &b, pos, g_1df8[8][j].f_04);
                            if (d < 80)
                                ok = 0;
                        }
                    } while (!ok);
                else
                    *(PAIR *)&pos = fn_09_225a(i - g_9318 * 2);   /* PAIR result into a POINT */
            } else
                pos = g_1df8[8][i].f_04;
        } else {
            pos = g_69f4[g_94a2].f_000[i];
            g_3d50[i].rest = -1;
            for (j = 0; j < g_9344; j++)
                if (g_4f2c[j].first <= i && g_4f2c[j].f_02 > i)
                    g_3d50[i].rest = j;
        }
        g_1df8[8][i].f_04 = pos;
        g_1df8[8][i].f_18 = 0;
        g_1df8[8][i].f_24 = SC(5);
        g_1df8[8][i].f_54 = 1;
        if (i < g_9318 * 2 + g_933e) {
            g_1df8[8][i].f_44 = 3500;
            g_1df8[8][i].f_42 = 8;
            g_1df8[8][i].f_46 = 4;
            g_1df8[8][i].f_62 = fn_11_39d8;
            g_1df8[8][i].f_5e = fn_07_2652;
            g_1df8[8][i].f_66 = fn_12_274a;
            if (i < g_9318 * 2 + g_4ee4) {
                g_3d50[i].f_0a = g_4d90[g_4ee8[0]].f_03;
                g_3d50[i].f_30 = g_4ee8[0];
            } else {
                g_3d50[i].f_0a = g_4d90[g_4ee8[1]].f_03;
                g_3d50[i].f_30 = g_4ee8[1];
            }
            if (g_3d50[i].f_30 == 3) {
                g_1df8[8][i].f_24 = SC(4);
                g_1df8[8][i].f_22 = SC(14);
                g_1df8[8][i].f_20 = 0x70;
                g_1df8[8][i].f_2c = 12000;
                g_1df8[8][i].f_48 = 0;
            } else if (g_3d50[i].f_30 == 4) {
                g_1df8[8][i].f_24 = SC(4);
                g_1df8[8][i].f_22 = SC(20);
                g_1df8[8][i].f_20 = 0x98;
                g_1df8[8][i].f_2c = 0x78;
                g_1df8[8][i].f_48 = 8;
            } else {
                g_1df8[8][i].f_24 = SC(6);
                g_1df8[8][i].f_22 = SC(0x22);
                g_1df8[8][i].f_20 = 0x110;
                g_1df8[8][i].f_2c = 0x78;
                g_1df8[8][i].f_48 = 8;
            }
            g_3d50[i].f_1c = 1;
            if (g_3d50[i].f_0a != 4)
                g_1df8[8][i].f_2f = 2;
        } else {
            g_3d50[i].f_1c = 2;
            if (i < g_9318 * 2 + g_933e + g_4ee0[0])
                sel = 0;
            else
                sel = 1;
            g_3d50[i].f_20 = g_4d90[g_4ed4[sel]].f_0e;
            g_3d50[i].f_22 = g_4d90[g_4ed4[sel]].f_10;
            g_3d50[i].f_2a = g_4d90[g_4ed4[sel]].f_01;
            g_3d50[i].f_0a = g_4d90[g_4ed4[sel]].f_03;
            g_3d50[i].f_18 = g_4d90[g_4ed4[sel]].f_04;
            g_1df8[8][i].f_44 = g_4d90[g_4ed4[sel]].f_0a;
            if (g_9320 == 6)
                g_1df8[8][i].f_54 = 1;
            else
                g_1df8[8][i].f_54 = g_4d90[g_4ed4[sel]].f_02;
            g_1df8[8][i].f_48 = 9;
            g_1df8[8][i].f_2c = g_4d90[g_4ed4[sel]].f_0c;
            if (g_1df8[8][i].f_2c < fn_09_88ba(g_1df8[8][i].f_1e))
                g_1df8[8][i].f_18 = 1;
            if (g_3d50[i].f_0a != 4)
                g_1df8[8][i].f_2f = 5;
            if (g_4d90[g_4ed4[sel]].f_03 == -1)
                flag = 1;
            else
                flag = 0;
            if (g_94b0 && g_3d50[i].f_0a == -1 && !(rand() & 1))
                g_3d50[i].f_0a = -3;
            else if (!g_94b0 && g_3d50[i].f_0a == -1 && g_1df8[8][i].f_1e < 0) {
                g_1df8[8][i].f_1e = -g_1df8[8][i].f_1e;
                g_3d50[i].f_0a = -3;
            }
            g_3d50[i].f_30 = g_4ed4[sel];
            g_1df8[8][i].f_42 = 6;
            g_1df8[8][i].f_46 = 4;
            g_1df8[8][i].f_62 = fn_11_39d8;
            g_1df8[8][i].f_5e = fn_07_2652;
            g_1df8[8][i].f_66 = fn_07_2e02;
            res = fn_10_18b0(g_3d50[i].f_22, g_3d50[i].f_20, g_3d50[i].f_2a, flag, g_3d50[i].f_30);
            if (g_3d50[i].f_0a > 0 && g_2f4c[g_3d50[i].f_0a].f_12)
                fn_10_533a(g_3d50[i].f_0a);
            g_1df8[8][i].f_24 = SC(g_4d90[g_3d50[i].f_30].f_09);
            g_1df8[8][i].f_22 = SC(g_4d90[g_3d50[i].f_30].f_08);
            g_1df8[8][i].f_20 = g_4d90[g_3d50[i].f_30].f_08 * 8;
            g_3d50[i].f_1e = res;
        }
        if (g_3d50[i].f_0a == 1)
            g_3d50[i].f_10 = rand() % 7 * 500 + 600;
        else
            g_3d50[i].f_10 = rand() % 7 * 500 + 1200;
        g_3d50[i].f_00 = 0;
        g_3d50[i].f_0e = rand() % ((g_91f8 + 1) * 200) + 20;
        g_3d50[i].f_0c = (g_91f8 + 5) * 3;
        if (g_3d50[i].f_0c > 22)
            g_3d50[i].f_0c = 22;
        g_3d50[i].f_08 = rand() % 2;
        if (g_3d50[i].f_30 != 4 && g_3d50[i].f_30 != 3) {
            g_1df8[8][i].f_04.x -= g_1df8[8][i].f_20 / 2;
            g_1df8[8][i].f_04.y -= g_1df8[8][i].f_20 / 2;
        }
        for (j = 0; j < g_9344; j++)
            if (g_4f2c[j].first <= i && g_4f2c[j].f_02 > i) {
                g_1df8[8][i].f_54 = 1;
                break;
            }
    }
    fn_10_1dd8();
    cnt = i = 0;
    for (i = 0; i < g_9344; i++)
        if (i == 0 || (g_4f2c[i - 1].f_0a.x != g_4f2c[i].f_0a.x
                       && g_4f2c[i - 1].f_0a.y != g_4f2c[i].f_0a.y)) {
            g_1df8[0][cnt].f_54 = 1;
            g_1df8[0][cnt].f_0e = 0;
            g_1df8[0][cnt].f_0c = g_1df8[0][cnt].f_0e;
            g_1df8[0][cnt].f_04.x = g_4f2c[i].f_0a.x - 128;
            g_1df8[0][cnt].f_04.y = g_4f2c[i].f_0a.y - 128;
            cnt++;
            g_0992 += (g_4f2c[i].f_02 - g_4f2c[i].first + 5) * 2;
        }
    if (g_9320 == 6 && g_9406[0] != 0) {
        POINT p0;               /* shares the frame with CL's temporaries */

        p0.y = g_9ea8[g_9322].x - 360;
        p0.x = g_1df8[12][0].f_04.x;
        for (i = 0; i < g_9406[0]; i++) {
            g_1df8[0][i].f_54 = 1;
            g_1df8[0][i].f_0e = 0;
            g_1df8[0][i].f_0c = g_1df8[0][i].f_0e;
            g_1df8[0][i].f_04.x = ((g_9406[0] - 1) * 64 / 2 - i * 64 - 16) * 8 + p0.x;
            g_1df8[0][i].f_04.y = p0.y;
        }
    }
    g_69f4[g_94a2].f_0ad = g_9318;
    if (g_9320 == 6)
        g_69f4[g_94a2].f_0ad = 0xff - g_9322;
    for (i = 0; i < g_9406[8]; i++)
        g_69f4[g_94a2].f_000[i] = g_1df8[8][i].f_04;
    if (g_9320 == 6)
        fn_09_2012();
}

                           
/* Builds the wave's enemy groups: up to five rings of objects around random
 * centres, plus escort rings, and stores the group table [inferred]. */
/* 9:4896 */
void fn_09_4896(void)
{
    int16_t u4;
    int16_t u6;
    int16_t c;
    int16_t s;
    int16_t total;
    int16_t dir[40];
    POINT ctr[5];
    POINT pos[40];
    int16_t t112;
    int16_t t114;
    int16_t t116;
    int16_t t118;
    int16_t ang;
    int16_t d1;
    int16_t d2;
    int32_t rad[5];
    int32_t r136;
    int32_t r13a;
    int16_t cnt1[5];
    int16_t cnt2[5];
    int16_t remain;
    int16_t m;
    int16_t sum;
    int16_t cnt;
    int16_t sub[2];
    int16_t j;
    int16_t state;
    int16_t kind1[5];
    int16_t kind2[5];
    int16_t c174;
    int16_t c176;
    int16_t i;
    int16_t n;
    int16_t l;
    int16_t k;
    int16_t total2;
    int16_t ok;

    n = g_933e;
    if (g_4ee0[0] && (g_4d90[g_4ed4[0]].f_02 || rand() % 3 < 2))
        n += g_4ee0[0];
    if (g_4ee0[1] && g_4d90[g_4ed4[1]].f_02)
        n += g_4ee0[1];
    for (i = 0; i < 10; i++)
        g_4f2c[i].first = g_4f2c[i].f_02 = 0;
    k = 0;
    n = min(g_9334 / 2 + 5, 9) * n / 9;
    if (n != 0) {
        remain = n;
        for (i = 0; i < 5; i++)
            cnt1[i] = cnt2[i] = 0;
        m = g_9344 = 0;
        do {
            t112 = rand() % 6 + 3;
            t114 = 0;
            if (remain > 15 && rand() % 20 == 0)
                t112 = 16;
            if (t112 == 7)
                t112 = 4;
            t116 = rand() % 16;
            r136 = (rand() % 75 + t112 * 18 + 120) << 3;
            r13a = 0;
            rad[g_9344] = r136;
            g_4f2c[k].radius = (int16_t)r136;
            g_4f2c[k].f_0e = rand() % ((g_9334 + 7) * 2) - g_9334 - 7;
            if (g_9334 > 2 && rand() % 3 < 2 && remain - t112 > 2 && g_9208 > 0) {
                if ((g_9208 >= 2 || t112 < 3) && g_8ff8 > 1) {
                    if (t112 == 4) {
                        if (rand() % 3 < 2) {
                            t114 = 4;
                            t118 = rand() % 2 * 2 + t116;
                            r13a = r136 * 14 / 10;
                        } else {
                            t114 = 8;
                            r13a = r136 * 185 / 100;
                            t118 = t116 + 1;
                        }
                    }
                    if (t112 == 3) {
                        r136 = r136 * 3 / 4;
                        t114 = 3;
                        t118 = (rand() & 1) == 0 ? t116 + 8 : t116;
                        r13a = r136 * 2;
                    }
                    if (t112 == 5) {
                        t114 = 5;
                        t118 = t116 + 8;
                        r13a = (r136 = max(r136 * 3 / 5, 1200)) * 223 / 100;
                    }
                    if (t114 > 0) {
                        if (rand() % 4 == 1)
                            g_4f2c[k + 1].f_0e = -g_4f2c[k].f_0e;
                        else
                            g_4f2c[k + 1].f_0e = g_4f2c[k].f_0e;
                        g_4f2c[k + 1].radius = (int16_t)r13a;
                        rad[g_9344] = r13a;
                    }
                }
            }
            cnt1[g_9344] = t112;
            cnt2[g_9344] = t114;
            rad[g_9344] = r13a < r136 ? r136 : r13a;
            ok = 0;
            do {
                ctr[g_9344].x = rand() % ((int32_t)((LO16(g_05a0)) << 3) - rad[g_9344] * 2) + rad[g_9344];
                g_240c = ctr[g_9344].x;
                ctr[g_9344].y = rand() % ((int32_t)((HI16(g_05a0)) << 3) - rad[g_9344] * 2) + rad[g_9344];
                g_2410 = ctr[g_9344].y;
                ok = 1;
                for (i = 0; i < g_9318; i++)
                    if (fn_08_285a(&d1, &d2, ctr[g_9344], g_1df8[12][i].f_04) < (rad[g_9344] >> 3) + 200)
                        ok = 0;
                for (i = 0; i < g_9344; i++)
                    if (fn_08_285a(&d1, &d2, ctr[g_9344], ctr[i]) < (rad[i] + rad[g_9344] >> 3) + 200)
                        ok = 0;
            } while (!ok);
            for (i = 0; i < t112; i++) {
                ang = (int16_t)(360L * i / t112) + t116 * 22;
                c = fn_06_71b2(ang);
                s = fn_06_720c(ang);
                pos[m].y = c * r136 / 128 + ctr[g_9344].y;
                pos[m].x = s * r136 / 128 + ctr[g_9344].x;
                dir[m] = ang % 360;
                if (pos[m].y > (HI16(g_05a0)) << 3)
                    pos[m].y -= (HI16(g_05a0)) << 3;
                else if (pos[m].y < 0)
                    pos[m].y += (HI16(g_05a0)) << 3;
                if (pos[m].x > (LO16(g_05a0)) << 3)
                    pos[m].x -= (LO16(g_05a0)) << 3;
                else if (pos[m].x < 0)
                    pos[m].x += (LO16(g_05a0)) << 3;
                m++;
            }
            g_4f2c[k].f_0a = ctr[g_9344];
            k++;
            if (t114 > 0) {
                g_4f2c[k].f_0a = ctr[g_9344];
                k++;
            }
            for (i = 0; i < t114; i++) {
                ang = (int16_t)(360L * i / t114) + t118 * 22;
                c = fn_06_71b2(ang);
                s = fn_06_720c(ang);
                pos[m].y = c * r13a / 128 + ctr[g_9344].y;
                pos[m].x = s * r13a / 128 + ctr[g_9344].x;
                dir[m] = ang % 360;
                if (pos[m].y > (HI16(g_05a0)) << 3)
                    pos[m].y -= (HI16(g_05a0)) << 3;
                else if (pos[m].y < 0)
                    pos[m].y += (HI16(g_05a0)) << 3;
                if (pos[m].x > (LO16(g_05a0)) << 3)
                    pos[m].x -= (LO16(g_05a0)) << 3;
                else if (pos[m].x < 0)
                    pos[m].x += (LO16(g_05a0)) << 3;
                m++;
            }
            remain -= t114 + t112;
            g_9344++;
        } while (g_9344 < 5 && remain > 2);

        state = 1;
        sum = sub[0] = sub[1] = j = 0;
        for (i = 0; i < 5; i++)
            kind1[i] = kind2[i] = 10;
        if (g_933e != 0) {
            sum = 0;
            do {
                kind1[j] = 0;
                state = 2;
                sum += cnt1[j];
                if (sum < g_933e) {
                    if (cnt2[j] > 0) {
                        sum = sum + cnt2[j];
                        kind2[j] = 0;
                    }
                    j++;
                    state = 1;
                }
            } while (sum < g_933e && j < g_9344);
        }
        sum = sum < g_933e ? g_933e : sum;
        for (i = 0; i < 2; i++) {
            if ((&g_4ee0[0])[i] != 0) {
                sub[i] = 0;
                if (state == 2) {
                    if (cnt2[j] > 0) {
                        sub[i] = cnt2[j];
                        kind2[j] = i + 1;
                    }
                    j++;
                    state = 1;
                }
                if (sub[i] < (&g_4ee0[0])[i]) {
                    while (sub[i] < (&g_4ee0[0])[i] && j < g_9344) {
                        state = 2;
                        kind1[j] = i + 1;
                        sub[i] += cnt1[j];
                        if (sub[i] < (&g_4ee0[0])[i]) {
                            if (cnt2[j] > 0) {
                                sub[i] = sub[i] + cnt2[j];
                                kind2[j] = i + 1;
                            }
                            state = 1;
                            j++;
                        }
                    }
                    sub[i] = sub[i] < (&g_4ee0[0])[i] ? (&g_4ee0[0])[i] : sub[i];
                }
            }
        }
        for (i = 0; i < 2; i++)
            sub[i] = sub[i] < (&g_4ee0[0])[i] ? (&g_4ee0[0])[i] : sub[i];
        total = g_9318 * 2 + sub[1] + sub[0] + sum;
        if (sum > g_933e) {
            g_69f4[g_94a2].f_0a0[2] = sum;
            g_933e = sum;
            g_69f4[g_94a2].f_0a5[0] = sum;
        }
        for (i = 0; i < 2; i++) {
            if (sub[i] > (&g_4ee0[0])[i]) {
                (&g_4ee0[0])[i] = sub[i];
                g_69f4[g_94a2].f_0a7[i] = sub[i];
                g_69f4[g_94a2].f_0a0[4] = sub[1] + sub[0];
                g_9342 = g_69f4[g_94a2].f_0a0[4];
            }
        }
        if (total > g_92ec[8]) {
            g_92ec[8] = g_9406[8] = total;
            GlobalUnlock(g_9100[8]);
            g_9100[8] = GlobalReAlloc(g_9100[8], (int32_t)(g_92ec[8] < 1 ? 1 : g_92ec[8]) * 0x70, 0x42);
            g_1df8[8] = (REC_70 *)GlobalLock(g_9100[8]);
        }
        k = c176 = c174 = m = cnt = 0;
        for (i = 0; i < g_9344; i++) {
            if (kind1[i] == 0) {
                g_4f2c[k].first = g_9318 * 2 + cnt;
                for (l = 0; l < cnt1[i]; l++) {
                    g_1df8[8][g_9318 * 2 + cnt].f_04 = pos[m];
                    g_3d50[g_9318 * 2 + cnt].f_2e = dir[m] << 3;
                    m++;
                    cnt++;
                }
                g_4f2c[k].f_02 = g_9318 * 2 + cnt;
                g_4f2c[k].f_08 = 0;
                g_4f2c[k].f_06 = i;
                k++;
            }
            if (kind2[i] == 0) {
                g_4f2c[k].first = g_9318 * 2 + cnt;
                for (l = 0; l < cnt2[i]; l++) {
                    g_1df8[8][g_9318 * 2 + cnt].f_04 = pos[m];
                    g_3d50[g_9318 * 2 + cnt].f_2e = dir[m] << 3;
                    m++;
                    cnt++;
                }
                g_4f2c[k].f_02 = g_9318 * 2 + cnt;
                g_4f2c[k].f_08 = 2;
                g_4f2c[k].f_06 = i;
                k++;
            }
            if (kind1[i] == 1) {
                g_4f2c[k].first = g_9318 * 2 + c176 + g_933e;
                for (l = 0; l < cnt1[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c176 + g_933e].f_04 = pos[m];
                    g_3d50[g_9318 * 2 + c176 + g_933e].f_2e = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f_02 = g_9318 * 2 + c176 + g_933e;
                if (cnt2[i] != 0 && g_9334 < 7)
                    g_4f2c[k].f_08 = 1;
                else if (g_9334 < 2)
                    g_4f2c[k].f_08 = 2;
                else
                    g_4f2c[k].f_08 = 0;
                g_4f2c[k].f_06 = i;
                k++;
            }
            if (kind2[i] == 1) {
                g_4f2c[k].first = g_9318 * 2 + c176 + g_933e;
                for (l = 0; l < cnt2[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c176 + g_933e].f_04 = pos[m];
                    g_3d50[g_9318 * 2 + c176 + g_933e].f_2e = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f_02 = g_9318 * 2 + c176 + g_933e;
                if (g_9334 < 8 || rand() % g_9334 < 4)
                    g_4f2c[k].f_08 = 2;
                else
                    g_4f2c[k].f_08 = 0;
                g_4f2c[k].f_06 = i;
                k++;
            }
            /* sic: counts with c176 but indexes with c174 */
            if (kind1[i] == 2) {
                g_4f2c[k].first = g_9318 * 2 + c174 + g_933e + g_4ee0[0];
                for (l = 0; l < cnt1[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c174 + g_933e + g_4ee0[0]].f_04 = pos[m];
                    g_3d50[g_9318 * 2 + c174 + g_933e + g_4ee0[0]].f_2e = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f_02 = g_9318 * 2 + c174 + g_933e + g_4ee0[0];
                if (cnt2[i] != 0 && g_9334 < 7)
                    g_4f2c[k].f_08 = 1;
                else if (g_9334 < 2)
                    g_4f2c[k].f_08 = 2;
                else
                    g_4f2c[k].f_08 = 0;
                g_4f2c[k].f_06 = i;
                k++;
            }
            if (kind2[i] == 2) {
                g_4f2c[k].first = g_9318 * 2 + c174 + g_933e + g_4ee0[0];
                for (l = 0; l < cnt2[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c174 + g_933e + g_4ee0[0]].f_04 = pos[m];
                    g_3d50[g_9318 * 2 + c174 + g_933e + g_4ee0[0]].f_2e = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f_02 = g_9318 * 2 + c174 + g_933e + g_4ee0[0];
                if (g_9334 < 8 || rand() % g_9334 < 4)
                    g_4f2c[k].f_08 = 2;
                else
                    g_4f2c[k].f_08 = 0;
                g_4f2c[k].f_06 = i;
                k++;
            }
        }
    }
    do {
        total2 = g_9318 * 2;
        for (i = 0; i < g_9344; i++)
            total2 += cnt2[i] + cnt1[i];
        if (total2 > 40) {
            k--;
            if (kind1[g_9344 - 1] == 0) {
                g_69f4[g_94a2].f_0a0[2] -= cnt1[g_9344 - 1];
                g_69f4[g_94a2].f_0a5[0] -= cnt1[g_9344 - 1];
            } else if (kind1[g_9344 - 1] == 1 || kind1[g_9344 - 1] == 2) {
                g_69f4[g_94a2].f_0a0[4] -= cnt1[g_9344 - 1];
                if (kind1[g_9344 - 1] == 1)
                    g_69f4[g_94a2].f_0a7[0] -= cnt1[g_9344 - 1];
                else
                    g_69f4[g_94a2].f_0a7[1] -= cnt1[g_9344 - 1];
            }
            if (cnt2[g_9344 - 1] != 0) {
                k--;
                if (kind2[g_9344 - 1] == 0) {
                    g_69f4[g_94a2].f_0a0[2] -= cnt2[g_9344 - 1];
                    g_69f4[g_94a2].f_0a5[0] -= cnt2[g_9344 - 1];
                } else if (kind2[g_9344 - 1] == 1 || kind2[g_9344 - 1] == 2) {
                    g_69f4[g_94a2].f_0a0[4] -= cnt2[g_9344 - 1];
                    if (kind2[g_9344 - 1] == 1)
                        g_69f4[g_94a2].f_0a7[0] -= cnt2[g_9344 - 1];
                    else
                        g_69f4[g_94a2].f_0a7[1] -= cnt2[g_9344 - 1];
                }
            }
            g_9344--;
        }
    } while (total2 > 40);
    if (g_92ec[8] > 40) {
        int16_t ex;

        ex = g_92ec[8] - 40;
        if (ex < g_9342) {
            g_9342 -= ex;
            g_69f4[g_94a2].f_0a0[4] = g_9342;
            if (ex < g_4ee0[1]) {
                g_4ee0[1] -= ex;
                g_69f4[g_94a2].f_0a7[1] = g_4ee0[1];
            } else {
                g_4ee0[0] -= ex;
                g_69f4[g_94a2].f_0a7[0] = g_4ee0[0];
            }
        } else {
            g_4ee4 -= ex;
            g_69f4[g_94a2].f_0a5[0] = g_4ee4;
            g_933e -= ex;
            g_69f4[g_94a2].f_0a0[2] = g_933e;
        }
        g_92ec[8] = g_9406[8] = 40;
    }
    for (i = 0; i < 10; i++) {
        g_69f4[g_94a2].f_232[i] = g_4f2c[i].first;
        g_69f4[g_94a2].f_23c[i] = g_4f2c[i].f_02;
        g_69f4[g_94a2].f_246[i] = g_4f2c[i].radius / 80;
        g_69f4[g_94a2].f_250[i] = g_4f2c[i].f_06;
        g_69f4[g_94a2].f_25a[i] = g_4f2c[i].f_08;
        g_69f4[g_94a2].f_26f[i] = g_4f2c[i].f_0a;
        g_69f4[g_94a2].f_265[i] = g_4f2c[i].f_0e;
    }
    g_69f4[g_94a2].f_264 = k;
    g_9344 = k;
}

                                

/* Plans the next wave: budget, helper groups, wave type (g_9320), the
 * demon gate and race set-up, enemy mix per type (g_933a[5]) and escort
 * classes; or reloads them from the saved record [inferred]. */
/* 9:3202 */
void fn_09_3202(void)
{
    int16_t sumcost;
    int16_t budget;
    int16_t r;
    int16_t score;
    int16_t best;
    int16_t bestidx;
    int16_t i;
    int16_t j;
    int16_t sw;
    int16_t nfree;
    int16_t ok;
    int16_t ok2;
    int16_t flag;
    int16_t z;
    int16_t cost[5];
    int16_t cnt;
    int16_t best2;
    int16_t bestidx2;
    int16_t k;
    int16_t l;
    char unused[50];            /* never used; sizes the frame */

    cost[0] = 1;
    cost[1] = 1;
    cost[2] = 3;
    cost[3] = 5;
    cost[4] = 5;
    fn_09_484c();
    g_9344 = z = 0;
    g_967e = 100;
    fn_06_11ec();
    if (g_932a < g_0992)
        g_0992 = min((g_0992 - g_932a) / 2, g_932a / 4);
    else
        g_0992 = 0;
    if (g_7090[g_9646].f_026[0] != 0)
        g_0992 += 50 - g_7090[g_9646].f_026[0] / 2;
    if (g_9346 != -1)
        g_0992 += 100;
    g_0994 = 0;
    if (g_94b0 == 0) {
        for (i = 0; i < 4; i++)
            g_0992 += g_69f4[g_94a2].f_0a0[i] * cost[i];
        for (i = 0; i < 2; i++)
            g_0992 += g_69f4[g_94a2].f_0a7[i] * (g_4d90[g_69f4[g_94a2].f_0ab[i]].f_05 + 3);
    }
    if (g_932a * 2 / 3 > g_0992) {
        for (k = 0; k < 2; k++) {
            best2 = 0;
            bestidx2 = -1;
            if (g_6e24 == 0)
                continue;
            if (g_0994 * 100 + g_0992 >= g_932a * 2 / 3)
                continue;
            for (i = 0; i < 8; i++) {
                j = cnt = 0;
                for (; j < 3; j++)
                    if (g_6e24[g_931c].f_64 != i && g_4eec[i][j] == g_931c)
                        cnt++;
                for (l = 0; l < g_0994; l++)
                    if (g_4f1c[l] + i == 0)
                        cnt = 0;
                if (best2 <= cnt && cnt != 0 && (best2 < cnt || rand() & 1)) {
                    best2 = cnt;
                    bestidx2 = i;
                }
            }
            if (best2 > 0 && rand() % 100 < (g_91f8 - g_4fd0[bestidx2][0] - g_0994 * 3) * 10 + best2 * 35 + 25) {
                g_4f1c[g_0994] = -bestidx2;
                g_0994++;
                g_0992 += 30;
            }
        }
        best2 = 0;
        bestidx2 = -1;
        if (g_6e24 && g_0994 * 75 + g_0992 < g_932a * 2 / 3) {
            for (i = 1; i < g_931a; i++) {
                for (j = 0; j < 5; j++) {
                    if (g_6e24[i].f_17[j] == g_931c && g_6e24[i].f_12[j] <= 5 && g_6e24[i].f_08[j] > 4
                        && g_6e24[i].f_64 != g_6e24[g_9646].f_64) {
                        if (g_6e24[i].f_38[0] <= 0)
                            g_6e24[i].f_08[j] = g_6e24[i].f_17[j] = -1;
                        else if (g_6e24[i].f_08[j] > best2) {
                            bestidx2 = i;
                            best2 = g_6e24[i].f_08[j];
                        }
                    }
                }
            }
            if (best2 != 0 && rand() % 100 < best2 + 40) {
                g_4f1c[g_0994] = bestidx2;
                g_0994++;
                g_0992 += 30;
            }
        }
        if (g_7090[g_9646].f_0ce > 400 && g_932a * 3 / 5 - g_0994 * 50 > g_0992) {
            int16_t chance;

            chance = min(g_7090[g_9646].f_0ce / 25 - g_7090[g_9646].f_026[0] / 5 + (g_9334 + 10) * 2
                         - g_0992 / 5 - g_0994 * 35 + g_9000 * 3, 75);
            if (rand() % 100 < chance) {
                g_0992 += 25;
                g_4f1c[g_0994] = -100;
                g_0994++;
            }
            if (rand() % 250 < chance && g_932a * 3 / 5 - g_0994 * 45 > g_0992) {
                g_0992 += 30;
                g_4f1c[g_0994] = -100;
                g_0994++;
            }
        }
    }
    g_9320 = -1;
    if (g_9334 == 0 && g_94b0 != 0) {
        if (g_91f8 == 0) {
            g_0986[0] = g_9320 = 0;
            budget = rand() % 20 + 30;
            g_9338 = session_helper_groups = 0;
        } else if (g_0986[2] && rand() % 2 == 1) {
            g_9320 = 2;
            g_0986[2] = 0;
            budget = rand() % 20 + 20;
            g_9338 = 1;
        } else if (g_0986[4] && rand() % 2 == 1) {
            g_9320 = 4;
            g_0986[4] = 0;
            budget = rand() % 20 + 50;
            g_9338 = 0;
        } else if (g_0986[3] && rand() % 2 == 1) {
            g_9320 = 3;
            g_0986[3] = 0;
            g_9338 = rand() % 2 + 1;
            budget = rand() % ((3 - g_9338) * 10) + 20;
        } else if (g_0986[5] != 0) {
            g_9320 = 5;
            g_0986[5]--;
            g_9338 = rand() % 2 + 1;
            budget = rand() % ((3 - g_9338) * 10) + 20;
        } else if (g_0986[2]) {
            g_9320 = 2;
            g_0986[2] = 0;
            budget = rand() % 15 + 25;
            g_9338 = rand() % 2 + 1;
        } else if (g_0986[4]) {
            g_9320 = 4;
            g_0986[4] = 0;
            budget = rand() % 40 + 40;
            g_9338 = 1;
        } else
            g_9334 = 1;
    }
    if (g_91f8 < 5 && g_9320 == -1) {
        g_9320 = 5;
        g_0986[5]--;
        budget = rand() % 15 + 30;
        g_9338 = rand() % 2 + 1;
    }
    if (g_94b0 == 0 && g_9320 != 6)
        g_9320 = -1;
    if (g_9334 != 0 && g_94b0 != 0) {
        session_helper_groups = 1;
        switch (sw = rand() % 5) {
        case 1:
            g_9338 = rand() % 3;
            budget = rand() % ((6 - g_9338) * 5) + g_9334 * 4 + 9;
            if (budget > 35)
                g_9334 = g_9334 - 2 < 1 ? 1 : g_9334 - 2;
            else
                g_9334--;
            break;
        case 0:
            g_9338 = rand() % 1 + 2;
            budget = rand() % ((8 - g_9338) * 5) + g_9334 * 2 + 5;
            break;
        case 2:
            g_9338 = rand() % 2 + 2;
            budget = rand() % ((7 - g_9338) * 5) + 5;
            if (rand() & 1)
                session_helper_groups = 2;
            else
                g_9334--;
            break;
        case 3:
            budget = rand() % 25 + 10;
            g_9338 = 2;
            g_9334 += 6;
            break;
        case 4:
            g_9338 = rand() % 2 + 2;
            budget = rand() % (18 - g_9338 * 4) + (g_9334 + 4) * 3;
            g_9334++;
            break;
        }
        if (g_9332 < 2 && rand() % 6 < 4)
            session_helper_groups--;
        g_9320 = rand() % 8 - 2;
        if (g_9320 == 4) {
            budget += budget / 2;
            if (g_9338 > 2)
                g_9338--;
        }
    }
    if (g_8ff8 >= 3)
        budget = budget * g_8ff8 / 2;
    if (g_932a * 4 / 5 - 20 < g_0992)
        g_9320 = 0;
    if (g_94b0 == 0 && g_69f4[g_94a2].f_0ad < 0 && g_38c9 == ':')
        flag = 1;
    else
        flag = 0;
    if (g_94b0 != 0 && (fn_16_5f0e(g_6990, g_8f7a) != 0 || g_91f8 - g_94ca > 4 && g_38c9 == ':')
        && g_94a6 < 25 || flag) {
        if (fn_16_5f0e(g_6990, g_8f7a) != 0
            || rand() % 100 < (g_91f8 - g_94ca - 3) * 2 + g_9334 / 2
               && g_7090[g_9646].f_026[0] > 50 && g_7090[g_9646].f_026[2] > 50
            || flag) {
            int16_t kind;
            int16_t sub;

            if (flag) {
                kind = -(g_69f4[g_94a2].f_0ad + 1);
                g_69f4[g_94a2].f_0ad = 1;
            } else
                kind = rand() % 3;
            g_9320 = 6;
            sub = rand() % 3 + 1;
            g_9ea0 = ((rand() & 1) + 1) * 5;
            if (g_9ea0 == 10 && rand() % 5 == 3)
                g_9ea0 = 1;
            g_9eb4 = 0;
            g_094e = kind * 4 + sub + 1;
            if (g_967c == 0) {
                if (g_9334 < 5 && g_9000 < 2)
                    g_94aa = 5;
                else
                    g_94aa = 4;
                goto mix;   /* gotos: layout only; the game keeps the shared
                             * escort tail inside the second branch */
            } else if (g_967c < 3) {
                if (g_9000 < 2 && g_967c == 1 && rand() % 6 < 2 && g_9334 < 5)
                    g_94aa = 5;
                if (g_9334 < 9 && g_9000 == 0)
                    g_94aa = 4;
                else if (g_9334 < 7 && g_9000 == 1 || rand() % 5 == 1)
                    g_94aa = 4;
                else if (g_9334 > 7 && g_9000 == 2 && rand() % 6 < 2) {
                    g_94aa = 1;
                mix:
                    g_94a8 = 0;
                    if (g_967c > 1 && rand() % 6 < 3 && g_94aa != 0) {
                        if (sub < 3 && g_9334 > 6 && g_967c > 3 && rand() % 6 < 4) {
                            g_94a8 = 2;
                            goto out;
                        }
                        goto one;
                    }
                    goto out;
                } else if (rand() % 6 < 3)
                    g_94aa = 2;
                else
                    g_94aa = 3;
                goto mix;
            } else if (g_967c < 4) {
                if (g_9000 == 2 && g_9334 > 7 && (rand() & 1) == 0)
                    g_94aa = 1;
                else if (g_9000 < 2 && rand() % 6 < 2 && g_9334 < 5)
                    g_94aa = 4;
                else if (rand() % 6 < 3)
                    g_94aa = 3;
                else
                    g_94aa = 2;
                goto mix;
            } else {
                if (g_967c <= 6 && g_9000 != 2 || rand() % 6 >= 3)
                    g_94aa = 1;
                else
                    g_94aa = 0;
                goto mix;
            }
        one:
            g_94a8 = 1;
        }
    }
out:
    nfree = 0;
    for (i = 0; i < 8; i++)
        if (g_1df8[0][i].f_18 == 0)
            nfree++;
    if (g_9432 > 600 && g_9334 != 0 && g_9338 < 3) {
        g_9338++;
        g_9334++;
    }
    if (g_9432 > 850 && g_9334 != 0 && g_9338 < 4) {
        g_9338++;
        g_9334++;
    }
    if (nfree < 5 && g_9338 > 2) {
        g_9338--;
        if (nfree < 3 && g_9338 > 4)
            g_9338--;
    }
    budget = (g_9208 + 3) * budget * 20 / 100;
    if (g_92e8 != 0 || g_9320 == 7) {
        budget = 0;
        if (g_92e8 != 0)
            g_9320 = 0;
        g_932c = 0;
    }
    if (g_932c && g_91f8 && g_9338 < 5)
        g_9338++;
    if (g_91f8 == 1)
        session_helper_groups = g_9338 = 1;
    if (g_0994 > g_9338)
        g_9338 = g_0994;
    if (g_094e != 0) {
        g_9320 = 6;
        budget = g_932c = 0;
        g_9338 = (g_094e - 1) % 4;
        g_9322 = (g_094e - 1) / 4;
        fn_10_320a();
        g_9eb4 = 0;
        session_helper_groups = 0;
    }
    if (g_0950 != 0) {
        g_9320 = 7;
        g_9338 = (g_0950 - 1) % 4;
        session_helper_groups = 0;
        g_6670[0].f_12 = 1200;
        g_6670[0].f_16 = 80;
    }
    g_9406[4] = rand() % ((g_9338 + 1) * 4);
    if (g_9406[4] < 3)
        g_9406[4] = 3;
    if (g_9320 == 4)
        g_9406[4] += rand() % 15 + 9;
    if (rand() % 25 == 4 && g_9208 > 1)
        g_92ec[4] = g_9406[4] = 17;
    else
        g_92ec[4] = g_9406[4];
    if (g_92e8 != 0)
        g_92ec[4] = g_9406[4] = 1;
    else if (g_9320 == 6)
        g_92ec[4] = g_9406[4] = g_9ebf[g_9322];
    ok = 0;
    for (i = 0; i < 5; i++)
        (&g_933a[0])[i] = 0;
    if (g_9320 == 3)
        g_933e = 5;
    if (g_9320 == 2)
        g_9340 = 5;
    if (g_9320 == 5)
        g_9342 = 5;
    if (g_94b0 != 0 || g_094e != 0) {
        do {
            do {
                do {
                    ok = 1;
                    r = rand() % 5;
                    if (cost[r] > g_9334 + 2)
                        ok = 0;
                    if (cost[r] > g_9334 && rand() % 5 < 3)
                        ok = 0;
                    if (g_9334 == 0)
                        ok = 1;
                    if ((r == 1 || r == 0) && g_933c + g_933a[0] > 120) {
                        ok = 0;
                        sumcost = budget;
                    }
                } while (!ok);
                (&g_933a[0])[r]++;
                if ((g_9320 == 1 || g_9320 == 4) && (r == 0 || r == 1))
                    (&g_933a[0])[r] += 2;
                else if (g_9320 == 2 && r == 3)
                    (&g_933a[0])[r] += 3;
                else if (g_9320 == 3 && r == 2)
                    (&g_933a[0])[r] += 3;
                else if (g_9320 == 5 && r == 4)
                    (&g_933a[0])[r] += 3;
                else if (g_9320 == 4)
                    (&g_933a[0])[r]++;
                if (g_9320 == 0 && (r == 2 || r == 3 || r == 4)
                    || g_9320 != 2 && g_9320 != -1 && r == 3 && g_9334 < 3)
                    (&g_933a[0])[r]--;
                sumcost = 0;
                for (i = 0; i < 5; i++)
                    sumcost += cost[i] * (&g_933a[0])[i];
                if ((g_9338 * 2 + g_0994) * 15 + sumcost + g_0992 > g_932a * 3 / 4)
                    sumcost = budget + 1;
            } while (budget > sumcost);
            ok2 = 1;
            for (i = 0; i < 5; i++) {
                if ((&g_933a[0])[i] > 0 && (&g_933a[0])[i] < min(budget / 12, 5) && i != 1) {
                    cost[i] = 100;
                    ok2 = (&g_933a[0])[i] = 0;
                }
            }
        } while (!ok2);
        /* POINT views: CL zeroes each pair with one dword store [layout] */
        VIEW(POINT, g_4ee0, 0).x = VIEW(POINT, g_4ee0, 0).y = 0;
        VIEW(POINT, g_4ee0, 4).x = VIEW(POINT, g_4ee0, 4).y = 0;
        if (g_9320 == 6) {
            for (i = 0; i <= 4; i++)
                (&g_933a[0])[i] = 0;
            (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).n2 = (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).t6[g_9322];
            (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).n4 = (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).t9[g_9322] - (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).t6[g_9322];
            if (g_9000 > 1 && g_94a8 > 0)
                (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).n6 = (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).tc[g_9322];
            else
                (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).n6 = 0;
            (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).b5 = -1;
            g_933e = g_9ea2 + g_9ea4;
            g_9342 = (VIEW(struct {
        int16_t n2;
        int16_t n4;
        int16_t n6;
        char p8[12];
        char b4;
        char b5;
        char t6[3];
        char t9[3];
        char tc[3];
    }, g_9ea2, 0)).n6;
            if (g_92e0) {
                GlobalUnlock(g_92e0);
                g_3d4c = 0;
                GlobalFree(g_92e0);
                g_92e0 = 0;
            }
            g_92e0 = GlobalAlloc(0x42, ((int32_t)g_9ea0 * g_9ea2 + 1) * (g_9338 + 1) * 4);
            g_3d4c = (DWORD *)GlobalLock(g_92e0);
        }
        if (g_9342 != 0) {
            if (g_9342 > 5) {
                g_4ee0[0] = rand() % g_9342 + 1;
                g_4ee0[1] = g_9342 - g_4ee0[0];
            } else {
                g_4ee0[0] = g_9342;
                g_4ee0[1] = 0;
            }
            for (i = 0; i < 2; i++) {
                best = -1000;
                bestidx = -1;
                for (j = 1; j < 13; j++) {
                    if (g_4d90[j].f_00 == 2) {
                        score = rand() % 90 + 50;
                        if (g_9334 == 0) {
                            if (g_1822[j] == 0)
                                score += 50;
                            if (g_4d90[j].f_05 > 5)
                                score += -20 * g_4d90[j].f_05;
                        } else if (g_4d90[j].f_05 > g_9334)
                            score += (g_9334 - g_4d90[j].f_05) * 35;
                        if (g_9320 == 6 && (g_9ec2[2] + 39)[g_9322][g_94a8] == j)
                            score += 1000;
                        score += g_4d90[j].f_07 * 5;
                        if (g_4d90[j].f_03 == 5 && g_9320 == 4)
                            score += 35;
                        if (score > best) {
                            best = score;
                            bestidx = j;
                        }
                    }
                }
                g_4ed4[i] = bestidx;
                g_1822[bestidx] = 1;
            }
            if (g_4ed4[1] == g_4ed4[0]) {
                g_4ee0[0] += g_4ee0[1];
                g_4ee0[1] = g_4ed4[1] = 0;
            }
        }
        g_9342 = g_4ee0[1] + g_4ee0[0];
        if (g_933e != 0) {
            if (g_9320 == 6) {
                g_4ee4 = g_9ea2;
                *(&g_4ee4 + 1) = g_9ea4;
            } else if (g_933e > 5) {
                g_4ee4 = rand() % g_933e + 1;
                *(&g_4ee4 + 1) = g_933e - g_4ee4;
            } else {
                g_4ee4 = g_933e;
                *(&g_4ee4 + 1) = 0;
            }
            for (i = 0; i < 2; i++) {
                if (g_9320 == 6) {
                    g_4ee8[0] = 3;
                    g_4ee8[1] = 4;
                } else {
                    best = -1000;
                    bestidx = -1;
                    for (j = 1; j < 13; j++) {
                        if (g_4d90[j].f_00 == 1) {
                            score = rand() % 50 + 40;
                            if (g_4d90[j].f_05 > g_9334)
                                score += (g_9334 - g_4d90[j].f_05) * 20;
                            if (g_9320 == 4 && g_4d90[j].f_03 == 5)
                                score += 50;
                            if (j == 3 || j == 4)
                                score = -1500;
                            if (score > best) {
                                best = score;
                                bestidx = j;
                            }
                        }
                    }
                    g_4ee8[i] = bestidx;
                }
            }
        }
        for (i = 0; i < 5; i++)
            g_69f4[g_94a2].f_0a0[i] = (&g_933a[0])[i];
        for (i = 0; i < 2; i++) {
            g_69f4[g_94a2].f_0a7[i] = (&g_4ee0[0])[i];
            g_69f4[g_94a2].f_0a9[i] = g_4ee8[i];
            g_69f4[g_94a2].f_0a5[i] = (&g_4ee4)[i];
            g_69f4[g_94a2].f_0ab[i] = g_4ed4[i];
        }
        g_9318 = 1;
        if (g_91f8 > 1 && rand() & 1 && g_92e8 == 0 && g_9320 != 6 && g_9320 != 7) {
            g_9318++;
            if (g_91f8 > 3 && rand() % 10 == 1) {
                g_9318++;
                if (g_91f8 > 7 && rand() % 5 == 1)
                    g_9318++;
            }
        }
    } else {
        for (i = 0; i < 5; i++)
            (&g_933a[0])[i] = g_69f4[g_94a2].f_0a0[i];
        for (i = 0; i < 2; i++) {
            (&g_4ee0[0])[i] = g_69f4[g_94a2].f_0a7[i];
            g_4ee8[i] = g_69f4[g_94a2].f_0a9[i];
            (&g_4ee4)[i] = g_69f4[g_94a2].f_0a5[i];
            g_4ed4[i] = g_69f4[g_94a2].f_0ab[i];
        }
        for (i = 0; i < 10; i++) {
            if ((BYTE)g_69f4[g_94a2].f_232[i] > g_92ec[8])
                g_69f4[g_94a2].f_232[i] = g_69f4[g_94a2].f_23c[i] = 0;
            g_4f2c[i].first = g_69f4[g_94a2].f_232[i];
            g_4f2c[i].f_02 = g_69f4[g_94a2].f_23c[i];
            g_4f2c[i].radius = g_69f4[g_94a2].f_246[i] * 80;
            g_4f2c[i].f_06 = g_69f4[g_94a2].f_250[i];
            g_4f2c[i].f_08 = g_69f4[g_94a2].f_25a[i];
            g_4f2c[i].f_0a = g_69f4[g_94a2].f_26f[i];
            g_4f2c[i].f_0e = g_69f4[g_94a2].f_265[i];
        }
        g_9344 = g_69f4[g_94a2].f_264;
        g_9318 = g_69f4[g_94a2].f_0ad;
    }
    fn_06_72d8(5, 5);
    g_94c4 = 0;
    g_9330 = 1;
    if (g_94b0 != 0) {
        for (i = 0; i < 4; i++)
            g_0992 += cost[i] * (&g_933a[0])[i];
        for (i = 0; i < 2; i++)
            if ((&g_4ee0[0])[i])
                g_0992 += (g_4d90[g_4ed4[i]].f_05 + 3) * (&g_4ee0[0])[i];
    }
    if (g_91f8 < 1)
        g_932e = 0;
    else
        g_932e = rand() % 3 + g_9334 / 2 - 1;
    if (g_932e < 0)
        g_932e = 0;
    if (g_9208 > 2 && g_932e > 4)
        g_932e = 4;
    else if (g_9208 == 2 && g_932e > 3)
        g_932e = 3;
    else if (g_9208 <= 1 && g_932e > 2)
        g_932e = 2;
    if (g_92e8 != 0 || g_9320 == 6)
        g_932e = 0;
    if (g_9320 != 6 && g_9320 != 7 && g_92e8 == 0) {
        if (g_9338 * -40 - g_0992 + g_932a > 50)
            g_9338 += 2 >= rand() % ((g_9338 * -40 - g_0992 + g_932a + 60) / 50)
                ? rand() % ((g_9338 * -40 - g_0992 + g_932a + 60) / 50) : 2;
        if (g_9338 > 5)
            g_9338 = 5;
        if (g_9338 * 45 + g_0992 > g_932a)
            g_9338 += (g_0992 - g_932a) / 45;
        if (g_0994 > g_9338)
            g_9338 = g_0994;
    }
}

/* Sets up a level: display scale from the INI file, object tables and the
 * per-type builders, with progress steps (fn_09_27da) [inferred]. */
/* DS:9406 and DS:92ec are int[15] per-type tables [inferred]; written as
 * arrays so CL does not sink the zero stores past them. */
                                                                                  
/* 9:22b4 */
void fn_09_22b4(int16_t a)
{
    int16_t i;
    int16_t j;
    int16_t unused;
    char buf[40];
    char buf2[40];
    int16_t cur;
    int16_t v;

    g_9324 = 14;
    g_9326 = g_0d24 = 0;
    g_9328 = 5;
    g_934a = 3;
    g_6e38[1].f_1a.b = -1;
    fn_09_27da(1);
    if (g_92e6 == 0) {
        LoadString(g_9212, 0x383, buf, 40);
        lstrcat(buf, "...");
        fn_10_94c4(2, 6, 0x200ff00L, LO16(g_90ea) / 2, g_0010 * 3 / 4 + 20, buf);
        if (g_90f8 && g_8e5e) {
            cur = g_9156;
            v = GetPrivateProfileInt(g_9690, "DScale", 0, g_96a9);
            if (v == 0) {
                if ((rand() & 1) || g_9156 == 2) {
                    cur = rand() % 3;
                    if (cur == g_9156 && cur == 2)
                        cur = 1;
                }
            } else
                cur = v - 1;
            if (cur != g_9156) {
                g_92e2 = 1;
                g_9156 = cur;
                fn_06_0f1a(cur, buf2);
                WritePrivateProfileString(g_9690, "Size", buf2, g_96a9);
            }
        }
        if (g_92e2) {
            g_9156 = GetPrivateProfileInt(g_9690, "Size", 1, g_96a9);
            g_9150 = 4 - g_9156;
            fn_10_0522(1);
            fn_10_5c42();
        }
        g_92e2 = 0;
    }
    if (g_91f8 == 0)
        fn_09_2828();
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 5; j++)
            g_7090[i].f_044[j] = 0;
        for (j = 0; j < 8; j++)
            g_7090[i].f_0c2[j] = g_7090[i].f_13e[j] = 0;
    }
    for (i = 0; i < 8; i++)
        g_937a[i] = 0;
    fn_09_3202();
    if (g_9432 > 250)
        g_9432 = g_9432 * 7 / 10;
    else
        g_9432 = g_9432 * 9 / 10;
    (g_9406[0]) = 8;
    ((&g_9406[0])[g_9328]) = (g_9406[2]) = (g_9406[1]) = 0;
    g_92ea = 14;
    g_92ec[0] = 8;
    g_92ec[1] = 2;
    g_92ec[2] = g_932e * 8;
    g_92ec[g_9328] = (g_9406[13]) = (g_9406[11]) = (g_9406[10]) = (g_9406[7]) = (g_9406[6]) = 0;
    g_92ec[7] = g_92ec[6] = 1;
    g_92ec[11] = g_92ec[10] = 3;
    g_92ec[13] = 0;
    g_92ec[3] = (g_9406[3]) = g_933c + g_933a[0];
    g_92ec[8] = (g_9406[8]) = g_933e + g_9342;
    g_92ec[9] = (g_9406[9]) = g_9340;
    g_92ea = g_933a[0];
    if ((g_9406[3]) > 127) {
        (g_9406[3]) = 120;
        g_92ec[3] = 920;
        g_933c = g_933a[0] = 60;
    }
    (g_9406[8]) += g_9318 * 2;
    g_92ec[12] = (g_9406[12]) = g_9318 * 2;
    g_92ec[8] += g_9318 * 2;
    if (g_92ec[8] > 80)
        g_92ec[8] = (g_9406[8]) = 80;
    if (g_92e8) {
        g_9326 = 1;
        g_9338 = session_helper_groups = (g_9406[3]) = 0;
    }
    if (g_9320 == 6) {
        (g_9406[3]) = 0;
        (g_9406[2]) = 0;
        g_92ec[2] = 0;
        if (g_9000 == 2 || (g_9000 == 1 && g_9334 > 8))
            g_9348 = 1;
        else if ((g_9000 == 0 && g_9334 > 3) || g_9334 < 4)
            g_9348 = 2;
        else
            g_9348 = 3;
    }
    for (i = 0; i <= g_9324; i++) {
        GlobalUnlock(g_9100[i]);
        g_9100[i] = GlobalReAlloc(g_9100[i], (int32_t)(g_92ec[i] < 1 ? 1 : g_92ec[i]) * 0x70, 0x42);
        g_1df8[i] = (REC_70 *)GlobalLock(g_9100[i]);
    }
    fn_10_740c();
    fn_10_0b94();
    fn_10_069a();
    fn_09_27da(4);
    fn_10_740c();
    if (g_3a00 == 0) {
        fn_10_39a8(1);
        fn_09_27da(9);
        fn_10_740c();
        if (g_90f0)
            fn_10_5102();
        else
            fn_10_3a2e();
        fn_09_27da(0x3c);
        fn_10_740c();
        fn_10_5202();
    }
    fn_10_740c();
    fn_09_27da(0x41);
    if (g_932e && g_39e8[0] == 0)
        fn_10_464a();
    fn_10_740c();
    fn_09_27da(0x46);
    if (g_90f0 == 0)
        fn_10_5102();
    else
        fn_10_3a2e();
    fn_09_27da(0x4e);
    fn_10_740c();
    fn_10_3ea2();
    fn_09_27da(0x51);
    fn_10_740c();
    fn_10_565a();
    fn_09_27da(0x53);
    fn_10_740c();
    if (g_9406[9]) {
        fn_10_58ce(1);
        fn_10_740c();
    }
    fn_09_27da(0x58);
    fn_10_561a();
    fn_10_740c();
    fn_09_27da(0x61);
    fn_10_42ee();
    fn_10_740c();
    if (g_9320 == 6)
        race_marker_strip();
    fn_10_740c();
    if (g_103a)
        g_103a = 0;
    fn_09_27da(100);
    g_964a = 0;
    fn_10_744c(0x6e);
    if (g_92e6 == 0)
        PatBlt(g_13dc, LO16(g_90ea) / 4 - 2, g_0010 * 3 / 4 - 12, LO16(g_90ea) / 2 + 4, 0x46, BLACKNESS);
    g_92e6 = 1;
    g_94e2 = (g_9340 + g_9342) * 2 + g_933c + g_933e + g_933a[0];
}
