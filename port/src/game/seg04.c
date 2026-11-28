/* INSPACE.EXE segment 4 (selector 1018). */
#include "game.h"

/* g_05a0 is declared long in inspace.h; this code reads its two words
 * separately (world width and height [inferred]). */
                                       
                                       

/* DS:66e4: a word 4 bytes before each g_66e8 record [inferred] */
                                           

/* word 0x0e bytes below each class record [inferred] */
                                           

/* 4:0000 */
void fn_04_0000(int16_t n)
{
    if (object_records[14][n].f_26 && g_238c == 0)
        fn_07_1208();
    if (g_7090[n].f_012) {
        object_records[14][n].f_28 += g_7090[n].f_012;
        if (object_records[14][n].f_28 > 15)
            object_records[14][n].f_28 = 0;
        if (object_records[14][n].f_28 < 0)
            object_records[14][n].f_28 = 15;
        fn_07_1208();
    }
}

/* 4:2da2 */
void fn_04_2da2(void)
{
    int16_t v;
    int16_t i;

    g_9eb5 = 1;
    for (i = 0; i <= g_9316; i++) {
        if (object_records[14][i].f_18 != 0)
            continue;
        if (g_7090[i].f_0da < 0)
            v = -1 - g_7090[i].f_0da;
        else
            v = g_7090[i].f_0da;
        if (v < g_9ea0)
            g_9eb5 = 0;
    }
    if (g_7090[main_ship].f_0da - g_9ea0 == 1)
        g_9eb5 = 1;
    else {
        if (g_9684 == 1) {
            fn_10_744c(0x74);
            if (g_91fc) {
                fn_03_06ec(main_ship, 7, 0, 0xba);
                g_967c++;
            }
        } else {
            fn_10_744c(0x42);
            if (g_91fc)
                fn_03_06ec(main_ship, 7, 0, 0xbb);
        }
        g_9e60[main_ship] = g_1e68 - g_9e60[main_ship];
        if (g_91fc)
            g_9eb5 = 1;
        if (g_9684 == 1 && g_9316 != 0) {
            g_5078 += ((9 - g_94aa) * g_9316 + (g_94a8 + 5) * 4) * 500;
            g_1e58 += ((9 - g_94aa) * g_9316 + (g_94a8 + 5) * 4) * 500;
        } else if (g_9684 == 2 && g_9316 > 1) {
            g_5078 += (g_94a8 + 8) * 500 + (8 - g_94aa) * g_9316 * 200;
            g_1e58 += (g_94a8 + 8) * 500 + (8 - g_94aa) * g_9316 * 200;
        }
    }
    if (g_9eb5) {
        fn_10_744c(20);
        race_radar_background(0);
        for (i = g_9318 * 2; i < g_9318 * 2 + g_9ea2 + g_9ea4; i++)
            fn_12_3e98(i);
        for (i = 0; i <= g_9316; i++) {
            g_7090[i].f_148 = -2;
            g_7090[i].f_032.a = 12;
            g_7090[i].f_032.b = 0;
            g_7090[i].f_03c = g_7090[i].f_038 = 2;
            if (object_records[14][i].f_51 == 0)
                object_records[14][i].f_51 = 1;
        }
    }
    object_records[14][main_ship].f_51 = 2;
}

/* Per-frame order and target update for racer n [inferred]. */
/* 4:0078 */
void fn_04_0078(int16_t n)
{
    int16_t u04;
    int16_t r;
    int16_t hd;
    int16_t i;
    int16_t u0c;
    int16_t a;
    int16_t b;
    int16_t dist;
    char pad14[14];             /* frame filler [inferred] */
    POINT pos;
    char pad26[0x18];
    int16_t type;
    int16_t idx;
    char pad42[8];
    int16_t flag;

    if (g_9320 == 6 && g_9eb5 == 0)
        return;
    g_7090[n].f_061 = 0;
    if (g_96d2[g_7090[n].f_04e].f_38 == 7 && g_7090[n].f_032.a == 14
        && g_96d2[g_7090[g_7090[n].f_032.b].f_04e].f_38 == 7) {
        g_7090[n].f_032.b = 0;
        g_7090[n].f_032.a = 0;
        g_7090[n].f_094 = 0;
        g_7090[n].f_052 = g_7090[n].f_054 = g_7090[n].f_056 = 0;
    }
    if (g_7090[n].f_032.a == 14 && g_7090[g_7090[n].f_032.b].flag == 0)
        g_7090[n].f_094 = 0;
    if (g_9134 >= 2 && n == main_ship && g_8690 < now_ms && g_7090[main_ship].f_026[0] < 40)
        g_7090[main_ship].f_094 = 0;
    if (g_7090[n].f_038 == 1 && g_7090[n].f_032.a == 14 && g_8680[g_7090[n].f_032.b] == n
        && g_96d2[g_7090[n].f_04e].f_38 != 7) {
        g_7090[n].f_052 = 0;
        g_7090[n].f_094 = 0;
    }
    if (g_92e8 != 0) {
        if (object_records[14][main_ship].f_54 == 0 && g_7090[n].f_026[0] < 60) {
            fn_03_06ec(main_ship, 14, 1, 0xb7);
            g_7090[1].f_032.a = 12;
            g_7090[1].f_038 = 2;
            g_7090[1].f_032.b = 0;
            g_7090[1].f_052 = 0;
        } else if (object_records[14][main_ship].f_54 != 0 && g_7090[1].f_01e == 0) {
            if (g_8e30 < now_ms) {
                object_records[14][main_ship].f_54 = 0;
                g_7090[1].f_01e = g_96d2[g_7090[1].f_04e].f_1e;
                fn_03_06ec(main_ship, 14, 1, 0xb7);
                g_7090[1].f_032.a = 12;
                g_7090[1].f_038 = 2;
                g_7090[1].f_032.b = 0;
                g_7090[1].f_052 = 0;
            }
            if (g_8e30 - 13000 < now_ms && g_7090[1].f_000 == 0) {
                fn_03_06ec(main_ship, 14, 1, 0xb6);
                g_7090[1].f_000 = 1;
            }
        }
    }
    if (g_9320 == 7 && (!flow_interactive || n != main_ship)
        && (g_7090[n].f_052 != 4 || g_7090[n].f_032.a != 14)
        && (g_7090[n].f_032.a != 4 || object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_18 != 0)) {
        g_7090[n].f_052 = 4;
        if (object_records[g_7090[n].f_054][g_7090[n].f_056].f_18 == 1 && n == main_ship) {
            for (i = 0; i <= g_9316; i++)
                if (i != n && object_records[14][i].f_18 != 1 && g_7090[i].flag != 0) {
                    g_7090[n].f_056 = i;
                    break;
                }
            if (i == g_9316 + 1 && g_7090[n].f_032.a != 12) {
                if (g_7090[n].f_032.a != 12)        /* sic: tested twice */
                    fn_03_06ec(main_ship, 14, n, 0xb7);
                g_7090[n].f_032.a = 12;
                g_7090[n].f_032.b = 0;
                g_7090[n].f_038 = 2;
                g_7090[n].f_052 = 0;
            }
        } else {
            g_7090[n].f_032.a = g_7090[n].f_054;
            g_7090[n].f_032.b = g_7090[n].f_056;
            g_7090[n].f_038 = 1;
            g_7090[n].f_03c = 2;
        }
    }
    if (g_9320 == 6 && g_7090[n].f_032.a != 12 && g_96d2[g_7090[n].f_04e].f_38 != 7)
        g_7090[n].f_094 = now_ms;
    if (g_7090[n].f_094 < now_ms || object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_18 != 0) {
        if (object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_18 != 0 && g_7090[n].f_052 != 0
            && g_7090[n].f_052 != 7 && g_7090[n].f_054 != -1
            && object_records[g_7090[n].f_054][g_7090[n].f_056].f_18 != 0) {
            if (g_9320 == 7) {
                if (object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_18 != 1)
                    goto skip;
                for (i = 0; i <= g_9316; i++)
                    if (i != n && object_records[14][i].f_18 != 1) {
                        g_7090[n].f_056 = i;
                        break;
                    }
                if (i != g_9316 + 1)
                    goto skip;
            }
            g_7090[n].f_052 = 0;
        }
    skip:
        if (n == main_ship && g_9134 >= 2) {
            switch (g_9134) {
            case 2:
                g_9134 = 0;
                flow_interactive = 1;
                break;
            case 3:
                g_9134 = 1;
                flow_interactive = 1;
                break;
            case 4:
                g_9134 = 1;
                break;
            }
            g_8690 = 0;
            fn_03_06ec(main_ship, 7, 0, 0xa4);
        }
        if (fn_04_702e(n) == 0
            && (!fn_13_371c(g_7090[n].f_032.a, g_7090[n].f_032.b) || g_7090[n].f_03c != 2
                || g_7090[n].f_038 != 2 || (n == main_ship && flow_interactive)
                || g_96d2[g_7090[n].f_04e].f_38 == 7)) {
            fn_13_7ba2(n);
            if (g_7090[n].f_09c == 1)
                g_7090[n].f_09c = now_ms + 5000;
            if (g_7090[n].f_038 != 4 && (g_9320 != 6 || g_96d2[g_7090[n].f_04e].f_38 == 7)) {
                if (g_7090[n].f_052 < 1 && (n != main_ship || g_9134 == 0 || !flow_interactive)) {
                    g_7090[n].f_0ed = 0;
                    if (g_7090[n].f_036 != 4)
                        fn_04_2f98(n, 1);
                    fn_04_485c(n, -1);
                } else
                    fn_13_6900(n);
                if (g_7090[n].f_006 < 0) {
                    g_7090[n].f_008 = 0;
                    g_7090[n].f_006 = 0;
                }
                if (n == main_ship && !flow_interactive
                    && fn_03_0000(g_7090[n].f_006, g_7090[n].f_008)) {
                    g_0a62 = 1;
                    fn_03_00f4(n, g_7090[n].f_006, g_7090[n].f_008);
                }
                if (g_9320 != 6) {
                    if (((g_7090[n].f_052 != 3 && g_7090[n].f_052 != 4) || g_9320 == 7)
                        && (n != main_ship || g_9134 == 0 || !flow_interactive))
                        fn_04_4d00(n);
                    else
                        fn_13_a65a();
                }
                if (g_7090[n].f_006 != g_7090[n].f_032.a || g_7090[n].f_008 != g_7090[n].f_032.b
                    || g_7090[n].f_036 != g_7090[n].f_038 || g_7090[n].f_03a != g_7090[n].f_03c) {
                    g_7090[n].f_0a4 = g_7090[n].f_0a8 = now_ms;
                    g_7090[n].f_032.a = g_7090[n].f_006;
                    g_7090[n].f_032.b = g_7090[n].f_008;
                    g_7090[n].f_038 = g_7090[n].f_036;
                    g_7090[n].f_03c = g_7090[n].f_03a;
                }
            }
            if (g_96d2[g_7090[n].f_04e].f_38 == 7 && g_7090[n].f_052 < 20
                && g_7090[n].f_032.a != 11 && g_7090[n].f_032.a != 12 && g_7090[n].f_032.a != 4) {
                g_7090[n].f_052 = 22;
                if (g_7090[n].f_0cd >= 0 && g_7090[n].f_05e < 2) {
                    if (g_7090[g_7090[n].f_0cd].flag == 0) {
                        fn_03_06ec(main_ship, 14, n, 0xb7);
                        g_7090[n].f_006 = 12;
                        g_7090[n].f_008 = 0;
                        g_7090[n].f_036 = 2;
                        g_7090[n].f_03a = 2;
                    } else {
                        g_7090[n].f_054 = 14;
                        g_7090[n].f_056 = g_7090[n].f_0cd;
                    }
                } else if (g_7090[n].f_032.a == 14 || g_7090[n].f_05e == 0) {
                    g_7090[n].f_054 = 14;
                    g_7090[n].f_056 = g_7090[n].f_032.b;
                    if (g_7090[n].f_05e == 0)
                        g_7090[n].f_052 = 23;
                } else if (g_7090[n].f_054 == 14) {
                    if (g_7090[n].f_05e == 0)
                        g_7090[n].f_052 = 23;
                    else if (g_7090[n].f_05e == 1)
                        g_7090[n].f_052 = 22;
                    else
                        g_7090[n].f_052 = 20;
                } else
                    g_7090[n].f_052 = 20;
                g_7090[n].f_0ed = 2;
                g_7090[n].f_058 = n;
                g_7090[n].f_094 = now_ms;
                g_7090[n].f_038 = 3;
                fn_13_6900(n);
            }
        } else {
            if (fn_13_371c(g_7090[n].f_032.a, g_7090[n].f_032.b) == 2)
                fn_13_3678(n);
            fn_03_00f4(n, g_7090[n].f_032.a, g_7090[n].f_032.b);
            g_7090[n].f_094 = now_ms + 3000;
        }
        fn_04_79ae(n);
    }
    g_7090[n].f_030++;
    if (g_9134 != 2)
        fn_04_4fc8(n);
    type = g_7090[n].f_006;
    idx = g_7090[n].f_008;
    if (type == 14 && g_7090[idx].f_0e8 && g_92e8 == 0)
        pos = g_7090[idx].f_14a;
    else
        pos = object_records[type][idx].f_04;
    dist = fn_08_285a(&a, &b, object_records[14][n].f_04, pos);
    if (g_7090[n].f_038 == 4) {
        if (dist < 400 && type == 14 && g_7090[n].f_032.a == type && g_7090[n].f_032.b == idx
            && (n != g_952e || g_9e49 < 1 || g_9e49 > 6)) {
            if (g_7090[n].f_0ca <= 0)
                fn_04_5654(n);
            g_7090[n].f_0ca += 4 - g_9208;
            if (dist < 100)
                fn_11_5ab6(n, 2);
        }
        g_7090[n].f_061 = 1;
        g_7090[n].f_03a = 5;
    }
    hd = object_records[14][n].f_28;
    if (n == g_952e && g_9e49 >= 1 && g_9e49 <= 6)
        return;
    if (g_7090[n].f_05f == 2 && g_7090[n].f_038 != 4) {
        if (g_7090[n].f_038 == 1) {
            if (dist < 160) {
                flag = 1;
                for (i = 0; i < g_9406[6]; i++)
                    if (object_records[6][i].f_18 == 0 && g_6670[i + 4].r.left == 14 && g_6670[i + 4].r.top == n)
                        flag = 0;
                if (flag) {
                    g_7090[n].f_03a = 5;
                    g_7090[n].f_03c = 5;
                    g_7090[n].f_0ca = 0;
                } else {
                    g_7090[n].f_03a = 2;
                    g_7090[n].f_03c = 2;
                }
            } else if (dist > 210) {
                g_7090[n].f_03a = 2;
                g_7090[n].f_03c = 2;
            } else if (g_7090[n].f_03c == 5)
                g_7090[n].f_03a = 5;
        } else
            g_7090[n].f_05f = 0;
    }
    g_7090[n].f_0ca = g_7090[n].f_0ca - 1 < 0 ? 0 : g_7090[n].f_0ca - 1;
    g_7090[n].f_0cc = g_7090[n].f_0cc - 1 < 0 ? 0 : g_7090[n].f_0cc - 1;
    g_7090[n].f_0d4 = g_7090[n].f_0d4 - 1 < 0 ? 0 : g_7090[n].f_0d4 - 1;
    if (g_7090[n].f_036 == 1) {
        if (dist < 400 && (g_9208 > 1 || object_records[14][n].f_1a != 0)) {
            if (n != main_ship && g_7090[n].f_0a4 + 19000 < now_ms
                && (g_7090[n].f_052 == 0
                    || (g_7090[n].f_098 < now_ms && g_7090[n].f_052 != 4
                        && g_7090[n].f_052 != 1 && g_7090[n].f_052 != 23))) {
                if (g_7090[n].f_032.a == 14)
                    g_7090[n].f_0c2[g_7090[n].f_032.b] = -1;
                g_7090[n].f_094 = 0;
                g_7090[n].f_052 = -1;
                fn_04_2f98(n, 1);
                g_7090[n].f_0a4 = g_7090[n].f_0a8 = now_ms;
                g_7090[n].f_032.a = g_7090[n].f_006;
                g_7090[n].f_032.b = g_7090[n].f_008;
                g_7090[n].f_038 = g_7090[n].f_036;
                g_7090[n].f_03c = g_7090[n].f_03a;
            }
            r = 0;
            if (g_7090[n].f_0ca <= 0 && object_records[14][n].f_1a != 0)
                r = fn_04_5654(n);
            if (g_7090[n].f_03a == 2 && r == 0 && g_7090[n].f_0cc <= 0
                && (type != 0 || g_7090[n].f_0b8[g_7090[n].f_018] != 5))
                fn_11_4e0a(n);
        } else if (g_7090[n].f_01e > 150 && dist > 700) {
            fn_11_5ab6(n, 2);
            g_7090[n].f_061 = 1;
        }
    }
}

/* Current waypoint record of racer n [inferred]. */
                                                         

/* Race AI: steer racer n along the track's waypoints [inferred]. */
/* 4:144c */
void fn_04_144c(int16_t n, int16_t flag)
{
    POINT pos;
    POINT d1;
    POINT wp;
    POINT vel;
    POINT next;
    POINT prev;
    POINT d2;
    int32_t unused;                /* never used; keeps the frame size */
    int32_t dist2;
    int32_t spd;
    int32_t dist;
    int32_t r1;
    int32_t r3;
    int32_t r2;
    int16_t i;
    int16_t turn;

    if (g_7090[n].f_148 < 0) {
        if (g_7090[n].f_148 == -2) {
            if (g_7090[n].f_032.a == 0) {
                if (object_records[0][g_7090[n].f_032.b].f_18) {
                    for (i = 0; i < g_9406[0]; i++)
                        if (object_records[0][i].f_18 == 0) {
                            g_7090[n].f_032.b = i;
                            break;
                        }
                    if (object_records[0][g_7090[n].f_032.b].f_18) {
                        g_7090[n].f_032.a = 12;
                        g_7090[n].f_032.b = 0;
                    }
                }
            } else {
                g_7090[n].f_032.a = 12;
                g_7090[n].f_032.b = 0;
            }
            g_7090[n].f_038 = 2;
            g_7090[n].f_03c = 2;
            return;
        }
        g_7090[n].f_148 = 0;
        g_7090[n].f_0da = 0;
    }
    pos = fn_08_29ea(object_records[14][n].f_04);
    pos.x += object_records[14][n].f_22 / 2;
    pos.y += object_records[14][n].f_22 / 2;
    if (g_8e34[n] != -1)
        wp = fn_08_29ea(object_records[4][g_8e34[n]].f_04);
    else
        wp = fn_08_29ea(object_records[8][g_7090[n].f_148 + g_9318 * 2].f_04);
    wp.x += 7 << g_9156;
    wp.y += 7 << g_9156;
    if (g_7090[n].f_148 < g_9ea2 - 1)
        next = fn_08_29ea(object_records[8][g_7090[n].f_148 + g_9318 * 2 + 1].f_04);
    else
        next = fn_08_29ea(object_records[8][g_9318 * 2].f_04);
    if (g_7090[n].f_148 > 0)
        prev = fn_08_29ea(object_records[8][g_7090[n].f_148 + g_9318 * 2 - 1].f_04);
    else
        prev = fn_08_29ea(object_records[8][g_9318 * 2 + g_9ea2 - 1].f_04);
    vel = VIEW(POINT, object_records[14][n].f_0c, 0);
    g_8e48[n] = dist = fn_08_35d0(d1.x = (pos.x - wp.x) * 2 >> g_9156,
                                  d1.y = (pos.y - wp.y) * 2 >> g_9156);
    spd = fn_08_35d0(vel.x, vel.y);
    r1 = -((((int32_t)vel.x * d1.x + (int32_t)vel.y * d1.y) << 7) / (dist * spd));
    r2 = (((int32_t)vel.y * d1.x - (int32_t)vel.x * d1.y) << 7) / (dist * spd);
    turn = 0;
    if (flag) {
        if (g_9eb4) {
            if (!object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && r2 < 0 || object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && r2 > 0) {
                /* both arms equal: CL drops the test but keeps the
                 * operand's (dead) computation, as the game does */
                if (dist < (spd + 250) * 2)
                    turn = 2;
                else
                    turn = 2;
                if (!object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && r2 < -35 || object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && r2 > 35)
                    turn = 3;
                if ((!object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && dist / -7 + 5 > r2 || object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && dist / 7 - 5 < r2)
                    && dist < 400) {
                    turn = 4;
                    object_records[14][n].f_0c = (int16_t)(object_records[14][n].f_0c * 5) / 6;
                    object_records[14][n].f_0e = (int16_t)(object_records[14][n].f_0e * 5) / 6;
                }
            } else {
                turn = 0;
                if ((!object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && 1000 / dist + g_8e3c[n] * 6 + 14 > r2
                     || object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && -1000 / dist - g_8e3c[n] * 6 - 14 < r2) && dist < 800)
                    turn = 2;
                else if ((!object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && g_8e3c[n] * 6 + 40 > r2
                          || object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && -40 - g_8e3c[n] * 6 < r2) && dist < 1000)
                    turn = 1;
                if ((!object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && g_8e3c[n] * 6 + 52 < r2
                     || object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && -52 - g_8e3c[n] * 6 > r2) && dist > 70)
                    turn = -1;
                if ((!object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && g_8e3c[n] * 6 + 65 < r2
                     || object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52 && -65 - g_8e3c[n] * 6 > r2) && dist > 70)
                    turn = -2;
            }
        }
        if (dist / 4 - g_8e3c[n] * 7 + 80 < r1 && 140 - spd / 2 > dist && g_8e34[n] == -1) {
            if (object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52)
                g_7090[n].f_03c = 3;
            else
                g_7090[n].f_03c = 4;
            g_7090[n].f_149 = 0;
        } else {
            if (turn) {             /* f3c in both arms: shared tail */
                g_7090[n].f_149 = turn;
                g_7090[n].f_03c = 2;
            } else {
                g_7090[n].f_149 = 0;
                g_7090[n].f_03c = 2;
            }
        }
        if (g_8e34[n] != -1) {
            wp = fn_08_29ea(object_records[8][g_7090[n].f_148 + g_9318 * 2].f_04);
            g_8e48[n] = dist = fn_08_35d0(d1.x = (pos.x - wp.x) * 2 >> g_9156,
                                          d1.y = (pos.y - wp.y) * 2 >> g_9156);
            if (object_records[4][g_8e34[n]].f_18)
                g_8e34[n] = -1;
            if (r1 < 0 && (int32_t)g_7090[n].f_01e * 100 / g_96d2[g_7090[n].f_04e].f_1e > 20)
                g_8e34[n] = -1;
        }
        if (g_8e34[n] != -1) {
            g_7090[n].f_032.a = 4;
            g_7090[n].f_032.b = g_8e34[n];
        } else {
            g_7090[n].f_032.a = 8;
            g_7090[n].f_032.b = g_7090[n].f_148 + g_9318 * 2;
        }
        g_7090[n].f_038 = 2;
        if (spd / 3 - g_8e3c[n] * 5 + 37 < r1 && g_7090[n].f_03c == 2
            && g_8e3c[n] * 15 + 130 > dist && g_8e34[n] == -1)
            g_7090[n].f_038 = 5;
    }
    if ((dist < 350 || rand() % 5 == 0) && g_8e34[n] == -1) {
        dist2 = fn_08_35d0(d2.x = (prev.x - wp.x) * 2 >> g_9156,
                           d2.y = (prev.y - wp.y) * 2 >> g_9156);
        r1 = (((int32_t)d2.x * d1.x + (int32_t)d2.y * d1.y) << 7) / (dist * dist2);
        if (r1 < g_8e3c[n] - 2) {
            dist2 = fn_08_35d0(d2.x = (next.x - wp.x) * 2 >> g_9156,
                               d2.y = (next.y - wp.y) * 2 >> g_9156);
            r3 = (((int32_t)d2.x * d1.x + (int32_t)d2.y * d1.y) << 7) / (dist * dist2);
            r2 = (((int32_t)d2.y * d1.x - (int32_t)d2.x * d1.y) << 7) / (dist * dist2);
            if (r3 > spd / -24 + r1 - 2) {
                fn_10_754a(2, 8, g_7090[n].f_148 + g_9318 * 2, 1);
                if (object_records[14][n].f_51 == 0) {
                    int16_t v;

                    if (g_7090[n].f_0da < 0)
                        v = -1 - g_7090[n].f_0da;
                    else
                        v = g_7090[n].f_0da;
                    g_3d4c[(n * g_9ea0 + v) * g_9ea2 + g_7090[n].f_148 + 1] = g_1e68;
                    if (n == main_ship) {
                        for (i = 0; i <= g_9316; i++)
                            if (object_records[14][i].f_18 == 0 && i != n
                                && g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[n].f_148 + 1] != 0)
                                g_8e08[i] = g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[n].f_148 + 1]
                                    - g_3d4c[(n * g_9ea0 + v) * g_9ea2 + g_7090[n].f_148 + 1];
                            else if (g_8e08[i] < 0)
                                g_8e08[i] = 50000;
                    } else if (g_3d4c[(main_ship * g_9ea0 + v) * g_9ea2 + g_7090[n].f_148 + 1] != 0)
                        g_8e08[n] = g_3d4c[(n * g_9ea0 + v) * g_9ea2 + g_7090[n].f_148 + 1]
                            - g_3d4c[(main_ship * g_9ea0 + v) * g_9ea2 + g_7090[n].f_148 + 1];
                    else if (g_8e08[n] > 0)
                        g_8e08[n] = -50000;
                    if (flow_interactive == 0)
                        g_8e3c[n] = 0;
                    else if (g_8e08[n] < -210)
                        g_8e3c[n] = g_9348 + 3;
                    else if (g_8e08[n] < -90)
                        g_8e3c[n] = g_9348 + 2;
                    else if (g_8e08[n] < -10)
                        g_8e3c[n] = g_9348 + 1;
                    else if (g_8e08[n] > 40)
                        g_8e3c[n] = g_9348 - 1;
                    else if (g_8e08[n] > 100)
                        g_8e3c[n] = g_9348 - 2 < 0 ? 0 : g_9348 - 2;
                    else
                        g_8e3c[n] = g_9348;
                }
                if (g_7090[n].f_148 < g_9ea2 - 1) {
                    g_7090[n].f_148++;
                    g_7090[n].f_032.a = 8;
                    g_7090[n].f_032.b = g_7090[n].f_148 + g_9318 * 2;
                } else {
                    g_7090[n].f_148 = 0;
                    g_7090[n].f_032.a = 8;
                    g_7090[n].f_032.b = g_9318 * 2;
                    g_7090[n].f_0da = -1 - g_7090[n].f_0da;
                }
                dist = fn_08_35d0(d1.x = (pos.x - next.x) * 2 >> g_9156,
                                  d1.y = (pos.y - next.y) * 2 >> g_9156);
                if (g_8e3c[n] * 40 + 700 < dist
                    && (int16_t)((int32_t)g_7090[n].f_01e * 100 / g_96d2[g_7090[n].f_04e].f_1e) > rand() % 110) {
                    dist = fn_08_35d0(d1.x = (wp.x - pos.x) * 2 >> g_9156,
                                      d1.y = (wp.y - pos.y) * 2 >> g_9156);
                    r1 = ((int32_t)g_1050[object_records[14][n].f_28].y * d1.y
                          + (int32_t)g_1050[object_records[14][n].f_28].x * d1.x) * 10 / (dist * 8 / 5);
                    r3 = ((int32_t)object_records[14][n].f_0e * d1.y + (int32_t)object_records[14][n].f_0c * d1.x) * 10
                         / (dist * spd / 10);
                    if (object_records[14][n].f_51 == 0 && g_7090[n].f_01e > 200
                        && r1 < (8 - g_8e3c[n]) * 7 && r3 < 38 - g_8e3c[n] * 5)
                        fn_11_5ab6(n, 2);
                }
                g_8e34[n] = -1;
                if ((int32_t)g_7090[n].f_01e * 100 / g_96d2[g_7090[n].f_04e].f_1e < rand() % 27 + 20)
                    for (i = 0; i < g_9ebf[g_9322]; i++)
                        if (object_records[4][i].f_18 == 0
                            && g_9ec2[g_9322][g_9eb9[g_9322] + g_9ebc[g_9322] + i] == g_7090[n].f_148)
                            g_8e34[n] = i;
            }
            g_1cca[n] = r2;
        }
    }
    if (n == main_ship && object_records[14][n].f_51 && g_1e68 - g_9e70[n] > 600)
        g_7090[n].f_0da = -1 - g_9ea0;
    if (g_7090[n].f_0da < 0) {
        if ((int16_t)(object_records[14][n].f_04.x + object_records[14][n].f_20) > (int16_t)(object_records[12][1].f_04.x + 350)
            && object_records[14][n].f_04.x < (int16_t)(object_records[12][1].f_04.x + 2000)
            && object_records[14][n].f_04.y + object_records[14][n].f_20 > g_9ea8[g_9322].x
            && object_records[14][n].f_04.y < g_9ea8[g_9322].y
            && (object_records[14][n].f_0c > 0 || g_7090[n].f_0da + g_9ea0 == -1)) {
            fn_10_754a(0x72, 14, n, 1);
            if (object_records[14][n].f_51 == 0) {
                g_9e80[n] = g_9e70[n];
                g_9e70[n] = g_1e68;
                if (g_9e90[n] == 0 || g_1e68 - g_9e80[n] < g_9e90[n])
                    g_9e90[n] = g_9e70[n] - g_9e80[n];
            }
            g_7090[n].f_0da = -g_7090[n].f_0da;
            if (g_7090[n].f_0da >= g_9ea0 && g_9eb5 == 0) {
                g_9eb5 = 1;
                for (i = 0; i <= g_9316; i++)
                    if (object_records[14][i].f_18 == 0) {
                        int16_t v;

                        if (g_7090[i].f_0da < 0)
                            v = -1 - g_7090[i].f_0da;
                        else
                            v = g_7090[i].f_0da;
                        if (v < g_9ea0)
                            g_9eb5 = 0;
                    }
                if (n == main_ship) {
                    if (g_7090[n].f_0da - g_9ea0 == 1)
                        g_9eb5 = 1;
                    else {
                        if (g_9684 == 1)
                            fn_10_744c(0x74);
                        else
                            fn_10_744c(0x42);
                        g_9e60[n] = g_1e68 - g_9e60[n];
                    }
                } else if (g_7090[n].f_0da == g_9ea0) {
                    fn_10_744c(0x69);
                    fn_10_754a(0x42, 14, n, 1);
                    g_9e60[n] = g_1e68 - g_9e60[n];
                }
                if (g_91fc) {
                    g_7090[n].f_148 = -2;
                    g_7090[n].f_032.a = 0;
                    g_7090[n].f_032.b = 0;
                    g_7090[n].f_038 = 2;
                    g_7090[n].f_03c = 2;
                    g_9eb5 = 1;
                }
                object_records[14][n].f_51 = 2;
                if (g_9eb5) {
                    fn_10_744c(0x14);
                    race_radar_background(0);
                    for (i = g_9318 * 2; i < g_9318 * 2 + g_9ea2 + g_9ea4; i++)
                        fn_12_3e98(i);
                    for (i = 0; i <= g_9316; i++)
                        if (i != n || g_7090[i].f_032.a != 0) {
                            g_7090[i].f_148 = -2;
                            g_7090[i].f_032.a = 12;
                            g_7090[i].f_032.b = 0;
                            g_7090[i].f_038 = 2;
                            g_7090[i].f_03c = 2;
                            if (object_records[14][i].f_51 == 0)
                                object_records[14][i].f_51 = 1;
                        }
                }
            }
        }
    }
    g_7090[n].f_094 = now_ms + 60;
}

/* Chooses racer n's next target: another racer, a pickup or object, or
 * the checkpoint route (f06/f08 = target type/index, f36 = mode)
 * [inferred]. k is unused. */
/* 4:2f98 */
void fn_04_2f98(int16_t n, int16_t k)
{
    int16_t t;
    int16_t i;
    int16_t j;
    int16_t a;
    int16_t b;
    int16_t ratio;
    int16_t rel;
    int16_t cls;
    int16_t arr[8];
    int32_t best1;
    int32_t best2;
    int32_t best4;
    int32_t best3;
    int32_t sc;
    int32_t c[4];
    int32_t best5;
    int16_t sel1;
    int16_t sel2;
    int16_t sel4t;
    int16_t sel4i;
    int16_t sel3t;
    int16_t sel3i;
    int16_t sel5;
    int16_t sel6;
    int16_t unused;                 /* frame filler [inferred] */
    int16_t first;
    int16_t ok;

    if (g_7090[n].f_052 == -1) {
        first = 1;
        g_7090[n].f_052 = 0;
    } else
        first = 0;
    g_7090[n].f_094 = now_ms + 3000;
    cls = g_96d2[g_7090[n].f_04e].f_38;
    if (object_records[7][0].f_18 == 0 && n == g_952e) {
        g_7090[n].f_052 = 7;
        g_7090[n].f_098 = now_ms + 10000;
        g_7090[n].f_058 = n;
        g_7090[n].f_09c = now_ms + 5000;
        g_7090[n].f_0ed = 0;
        return;
    }
    if (cls == 7) {
        do {                    /* break = the out-of-line block after it */
            if (g_7090[n].f_05e < 2) {
                if (g_7090[n].f_054 == 14 && g_913c == 0 && g_913a == 0)
                    break;
                if (g_7090[n].f_05e == 1)
                    g_7090[n].f_052 = 0x16;
                else
                    g_7090[n].f_052 = 0x17;
                g_7090[n].f_054 = 14;
                if (g_7090[n].f_0cd >= 0)
                    g_7090[n].f_056 = g_7090[n].f_0cd;
                else if (g_7090[n].f_056 < 0 || g_7090[n].f_056 > g_9316) {
                    g_7090[n].f_056 = main_ship;
                    g_7090[n].f_052 = 0x14;
                }
                g_7090[n].f_0ed = 1;
                return;
            }
            if (g_7090[n].f_032.a != 11 || object_records[11][g_7090[n].f_032.b].f_18) {
                g_7090[n].f_052 = 0x14;
                return;
            }
            g_7090[n].f_006 = 11;
            g_7090[n].f_008 = 0;
            g_7090[n].f_036 = 2;
            g_7090[n].f_03a = 2;
            fn_04_6700(n);
            return;
        } while (0);
        fn_03_06ec(main_ship, 14, n, 0xb7);
        g_7090[n].f_006 = 12;
        g_7090[n].f_008 = 0;
        g_7090[n].f_036 = 2;
        g_7090[n].f_03a = 2;
        return;
    }
    best2 = best1 = 80000;
    sel1 = -1;
    sel2 = -1;
    for (i = 0; i <= g_9316; i++) {
        arr[i] = rand() % 2 + 1;
        arr[i] -= g_7090[n].f_05e;
        if (first && g_7090[n].f_032.a == 14 && g_7090[n].f_032.b == i)
            ok = 0;
        else
            ok = 1;
        if (object_records[14][i].f_18 == 0 && g_7090[i].flag && i != n && ok) {
            sc = (int16_t)(fn_08_285a(&a, &b, object_records[14][i].f_04, object_records[14][n].f_04) + 300);
            if (sc < 250)
                arr[i]++;
            ratio = fn_04_5d9c(n, i);
            rel = fn_13_2688(n, i);
            if (i == main_ship)
                sc -= sc >> 2;
            if (fn_09_88ba(rel) > 160)
                sc -= sc >> 2;
            arr[i] -= rel / 100;
            if ((g_7090[n].f_062 + 8)[i] > 3) {
                sc -= sc >> 2;
                arr[i]++;
            }
            if (n == main_ship)
                arr[i]++;
            if (g_7090[n].f_032.a == 14 && g_7090[n].f_032.b == i) {
                if (g_7090[n].f_038 == 1) {
                    sc >>= 1;
                    arr[i] += 2;
                    if (g_7090[n].f_146 == 8) {
                        arr[i] += 2;
                        sc = min(sc >> 3, 70);
                    }
                } else {
                    arr[i]++;
                    sc -= sc >> 2;
                }
            }
            if (g_7090[i].f_032.a == 14 && g_7090[i].f_032.b == n) {
                if (g_7090[i].f_038 == 1) {
                    if (g_7090[n].f_13e[i] < -2)
                        sc *= -(g_7090[n].f_13e[i] / 2);
                    else {
                        sc >>= 1;
                        arr[i] += 2;
                        rel -= 300;
                    }
                } else {
                    arr[i]++;
                    sc >>= 1;
                }
            }
            if (g_7090[n].f_0c2[i] == -1)
                sc = (sc + 1000) * 5;
            else if (g_7090[n].f_0c2[i] > 0 && g_7090[n].f_0c2[i] < 9) {
                sc = sc * (9 - g_7090[n].f_0c2[i]) / 10;
                arr[i] += g_7090[n].f_0c2[i] / 2;
            }
            if ((g_7090[n].f_05d - 1) * 50 < rel || cls == 4 && rel > -100
                || g_96d2[g_7090[i].f_04e].f_38 == cls) {
                if (g_7090[i].f_038 == 1) {
                    sc >>= 1;
                    if (g_7090[i].f_032.a == g_7090[n].f_032.a && g_7090[i].f_032.b == g_7090[n].f_032.b)
                        sc = sc * 2 / 3;
                }
                sc = sc * (g_7090[n].f_05d * 3 + 4) / 6;
                if (cls == 4)
                    sc -= sc >> 2;
                if (sc < best1) {
                    best1 = sc;
                    sel1 = i;
                }
            } else {
                sc = sc * ((g_7090[n].f_05e + 2) * 2) / 6;
                arr[i] -= g_7090[n].f_05e;
                if (ratio > 300 || ratio < 50) {
                    sc = (sc + 100) * 2;
                    arr[i]--;
                }
                if (g_8680[i] == n)
                    sc += 100000;
                if (ratio < 25 || g_7090[n].f_026[0] < 40) {
                    sc = (sc + 150) * 2;
                    arr[i] -= 2;
                }
                if (cls == 2 || cls == 4 || cls == 5) {
                    sc = (sc + 500) * 2;
                    arr[i] -= 2;
                }
                if (cls == 3 || cls == 6) {
                    sc -= sc >> 2;
                    arr[i]++;
                    if (cls == 3) {
                        if (g_7090[i].f_0ce > 250)
                            sc -= sc >> 2;
                        if (g_7090[n].f_0cd == i)
                            sc += sc / -3;
                    }
                }
                if (cls == 1 && g_96d2[g_7090[i].f_04e].f_38 == 2) {
                    sc /= 2;
                    arr[i] += 2;
                }
                if (g_7090[n].f_0ee[i] > 5)
                    sc += 80000;
                if (g_7090[i].f_0e8)
                    sc <<= 2;
                if (g_7090[n].f_032.a == 14 && g_7090[n].f_032.b == i)
                    sc = sc * 2 / 3;
                if (sc < best2) {
                    best2 = sc;
                    sel2 = i;
                }
            }
        }
    }
    best4 = best3 = 80000;
    sel4t = sel4i = sel3t = sel3i = -1;
    for (t = 0; t < 14; t++)
        if (t == 0 || t == 3 || t == 4 || t == 9 || t == 11 || t == 8)
            for (i = 0; i < g_9406[t]; i++) {
                if (first && g_7090[n].f_032.a == t && g_7090[n].f_032.b == i)
                    ok = 0;
                else
                    ok = 1;
                if (object_records[t][i].f_18 == 0 && ok) {
                    sc = (int16_t)(fn_08_285a(&a, &b, object_records[t][i].f_04, object_records[14][n].f_04) + 300);
                    if (g_7090[n].f_032.a == t && g_7090[n].f_032.b == i)
                        sc = max(1, sc - 100) * 2 / 3;
                    switch (t) {
                    case 3:
                        sc = (sc + 450) << 2;
                        break;
                    case 8:
                        if (g_9318 * 2 > i)
                            sc = (sc + 1500) << 3;
                        else if (g_3d50[t].f_1c != 2)
                            sc = (sc + 350) * 2;
                        else if (g_3d50[t].f_0a == -3)
                            sc = (sc + 2500) << 3;
                        break;
                    case 0:
                    case 4:
                    case 11:
                        if (t == 0) {
                            if (object_records[0][i].f_54 && g_7090[n].f_026[0] < 50)
                                sc = (sc + 200) * 2;
                            if (g_9000 > 1)
                                sc -= sc / 4;
                        } else if (t == 11) {
                            if (g_8560[i].f_00 == 3 || g_9320 == 7) {
                                if (g_8680[g_8560[i].f_0a] == n)
                                    sc /= 5;
                                if (cls == 3)
                                    sc = sc / 3;
                            } else if (cls == 3)
                                sc = sc / 3;
                            else
                                sc = sc * 3;
                        } else if (g_7090[n].f_01e > 200) {
                            sc <<= 2;
                            if (g_96d2[g_7090[n].f_04e].f_1e - 100 < g_7090[n].f_01e)
                                sc += 80000;
                        } else if (g_7090[n].f_01e < 150)
                            sc >>= 3;
                        if (object_records[t][i].f_53 == 1) {
                            if (cls == 2 || cls == 5)
                                sc >>= 2;
                            if (cls == 6)
                                sc -= sc >> 2;
                            if (g_9000 < 2 && n != main_ship) {
                                if (t == 0)
                                    sc = (sc - g_967e * 5 + 300) * 100 / max(10, g_967e);
                                else
                                    sc = sc * max(10, g_967e) / 100;
                            }
                            for (j = 0; j <= g_9316; j++)
                                if (j != n && g_7090[j].f_148 == t && g_7090[j].f_149 == i
                                    && g_7090[j].flag && object_records[14][j].f_18 == 0 && cls != 6
                                    && (g_96d2[g_7090[j].f_04e].f_38 == cls || fn_13_2688(n, j) > -200)) {
                                    sc = (800 > fn_13_2688(n, j) + sc + 300 ? 800 : fn_13_2688(n, j) + sc + 300)
                                         * ((6 - g_7090[n].f_05d) * 2);
                                    if (fn_13_2688(n, j) > 100)
                                        sc += 80000;
                                }
                            if (sc < best4) {
                                best4 = sc;
                                sel4t = t;
                                sel4i = i;
                            }
                        }
                        break;
                    }
                    if (object_records[t][i].f_53 != 1) {
                        sc += 100;
                        if (n != main_ship)
                            sc = sc * max(10, g_967e) / 100;
                        else
                            sc = (sc + 400) * 2;
                        sc = sc * ((g_7090[n].f_05e + 2) * 2) / 6;
                        if (cls == 6)
                            sc -= sc >> 2;
                        else if (cls == 2)
                            sc += sc >> 1;
                        if ((g_7090[n].f_05e + 6) * 5 > g_7090[n].f_026[0]
                            || (int32_t)g_7090[n].f_0ce + g_7090[n].f_0dc <= 200) {
                            if (t == 0)
                                sc *= 3;
                            else if ((9 - g_9334) * 20 < g_967e * 2)
                                sc += 80000;
                            else
                                sc <<= 2;
                        }
                        if (sc < best3) {
                            best3 = sc;
                            sel3t = t;
                            sel3i = i;
                        }
                    }
                }
            }
    best1 += best1 >> 2;
    sel5 = -1;
    for (t = 0; t <= g_9316; t++)
        if (object_records[14][t].f_18 == 0 && g_7090[t].flag && t != n && t != sel1 && g_7090[t].f_038 == 1
            && g_7090[t].f_032.a == 14 && g_7090[t].f_032.b == sel1 && g_8680[t] != n) {
            sel5 = t;
            if (fn_04_5d9c(sel1, t) < 60)
                best1 >>= 2;
            else
                best1 -= best1 >> 2;
            if (g_96d2[g_7090[sel5].f_04e].f_38 == cls)
                best1 += 80000;
            if (g_96d2[g_7090[sel5].f_04e].f_38 == cls || (int16_t)(fn_13_2688(n, sel5) + 100) > fn_13_2688(n, sel1))
                best1 += 80000;
            if ((g_7090[n].f_05d + 3) * 10 > g_7090[n].f_026[0])
                best1 += 80000;
            if ((int32_t)g_7090[n].f_0ce + g_7090[n].f_0dc < -50 && g_7090[n].f_05e > 0 && g_7090[n].f_026[0] < 65)
                best1 += 80000;
            if (cls == 4)
                best1 -= best1 >> 2;
        }
    c[0] = best1;
    c[1] = best2;
    c[2] = best4;
    c[3] = best3;
    if (c[0] > 20000 && c[1] > 20000 && c[2] > 20000) {
        c[0] = c[1] = c[2] = c[3] = 90000;
        for (t = 0; t < g_9406[0]; t++)
            if (object_records[0][t].f_18 == 0) {
                if (object_records[0][t].f_53 == 1)
                    c[2] = 100;
                else
                    c[3] = 100;
                break;
            }
    }
    best5 = 80000;
    sel6 = -1;
    for (t = 0; t < 4; t++)
        if (c[t] < best5) {
            best5 = c[t];
            sel6 = t;
        }
    if (sel6 == 0 && sel1 != -1) {
        if (sel5 != -1 && fn_04_5d9c(n, sel5) > g_7090[n].f_05d * 32
            && g_7090[n].f_0c2[sel5] != -1
            && !(first && g_7090[n].f_032.a == 14 && g_7090[n].f_032.b == sel5)) {
            g_7090[n].f_006 = 14;
            g_7090[n].f_008 = sel5;
            g_7090[n].f_036 = 1;
            g_7090[n].f_03a = 2;
            if (sel1 == main_ship)
                fn_04_474c(n, 14, sel5, 5);
            fn_04_8346(n, 14, sel5, 1);
            return;
        }
        if (g_7090[sel1].f_038 == 1
            && (g_7090[sel1].f_032.a != 14
                || g_96d2[g_7090[g_7090[sel1].f_032.b].f_04e].f_38 != cls
                   && (int16_t)(fn_13_2688(n, g_7090[sel1].f_032.b) + 100) < fn_13_2688(n, sel1))
            && g_7090[n].f_026[0] > 35
            && object_records[g_7090[sel1].f_032.a][g_7090[sel1].f_032.b].f_18 == 0
            && !(first && g_7090[sel1].f_032.a == g_7090[n].f_032.a && g_7090[sel1].f_032.b == g_7090[n].f_032.b)
            && (n != main_ship || g_7090[sel1].f_032.a != 3 && g_7090[sel1].f_032.a != 8
                || g_7090[sel1].f_032.a == g_7090[n].f_032.a && g_7090[sel1].f_032.b == g_7090[n].f_032.b
                || rand() % 30 == 2)) {
            g_7090[n].f_006 = g_7090[sel1].f_032.a;
            g_7090[n].f_008 = g_7090[sel1].f_032.b;
            g_7090[n].f_036 = 1;
            g_7090[n].f_03a = 2;
            if (sel1 == main_ship)
                fn_04_474c(n, g_7090[sel1].f_032.a, g_7090[sel1].f_032.b, 2);
            if (fn_04_8346(n, g_7090[n].f_006, g_7090[n].f_008, 2))
                return;
        }
        if (c[2] < 80000
            && (rand() % 30 + g_967e * 2 > 190 - g_9334 * 20 || n == main_ship || g_9000 == 2
                || g_7090[n].f_032.a == 0 && g_7090[n].f_038 == 2))
            sel6 = 2;
        else
            goto d1;
    }
d0:
    if (sel6 == 1 && sel2 != -1) {
        if (rand() % 3 + 1 < arr[sel2] && (g_7090[n].f_05e + 2) * 10 < g_7090[n].f_026[0]
            && (int32_t)g_7090[n].f_0ce + g_7090[n].f_0dc > -50) {
            g_7090[n].f_006 = 14;
            g_7090[n].f_008 = sel2;
            g_7090[n].f_036 = 1;
            g_7090[n].f_03a = 2;
            fn_03_00f4(n, 14, sel2);
            if (cls == 3 && g_7090[sel2].f_0ce > 400) {
                g_7090[n].f_054 = 14;
                g_7090[n].f_056 = sel2;
                g_7090[n].f_0cd = sel2;
                fn_04_8346(n, 14, sel2, 13);
                g_7090[n].f_052 = 4;
                g_7090[n].f_098 = now_ms + 30000;
                g_7090[n].f_058 = n;
                g_8e00 = g_8e04 = g_9680 = g_9682 = g_7090[n].f_0ed = 0;
                fn_03_06ec(sel2, 14, n, 0x67);
                g_7090[n].f_094 = now_ms + 500;
                return;
            /* Reached only by `goto d1`; CL places it after the block
             * above [layout-only, inferred: the original may have used
             * plain gotos, which make CL 8.00c crash here (C1001)]. */
            if (0) {
d1:
                if (c[2] < 80000
                    && ((g_7090[n].f_05e + 6) * 5 > g_7090[n].f_026[0]
                        || (int32_t)g_7090[n].f_0ce + g_7090[n].f_0dc <= 200))
                    sel6 = 2;
                else if (c[3] < 80000)
                    sel6 = 3;
                else if (c[1] < 80000)
                    sel6 = 1;
                else if (c[2] < 80000)
                    sel6 = 2;
                else {
                    best5 = 30000;
                    for (t = 0; t < g_9318 * 2; t += 2) {
                        sc = fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[12][t].f_04);
                        if (sc < best5) {
                            fn_13_9ae8(n);
                            best5 = sc;
                            fn_03_06ec(main_ship, 14, n, 0xb7);
                            g_7090[n].f_006 = 12;
                            g_7090[n].f_008 = t;
                            g_7090[n].f_036 = 2;
                            g_7090[n].f_03a = 2;
                        }
                    }
                    return;
                }
                goto d0;
            }
            }
            fn_04_8346(n, 14, sel2, 3);
            return;
        }
        if (c[2] < 80000
            && ((9 - g_9334) * 20 < g_967e * 2 || n == main_ship || g_9000 == 2 || c[3] >= 80000))
            sel6 = 2;
        else if (c[3] < 80000)
            sel6 = 3;
    }
    if (sel6 == 2) {
        if (sel4t != -1 && sel4i != -1) {
            if ((cls == 6 || g_7090[n].f_05e < 1) && cls == 4
                && (g_7090[n].f_05e + 2) * 150 + rand() % 600 < (int32_t)g_7090[n].f_0ce + g_7090[n].f_0dc
                && g_7090[n].f_026[0] > 50) {
                g_7090[n].f_006 = sel4t;
                g_7090[n].f_008 = sel4i;
                g_7090[n].f_036 = 1;
                g_7090[n].f_03a = 2;
                fn_04_8346(n, sel4t, sel4i, 4);
                return;
            }
            fn_13_9ae8(n);
            if (g_7090[n].f_026[0] < 40 && sel4t == 0 && object_records[0][sel4i].f_54) {
                fn_03_00f4(n, sel4t, sel4i);
                fn_13_9ce0(n);
                if (c[1] < 20000) {
                    g_7090[n].f_006 = 14;
                    g_7090[n].f_008 = sel2;
                    g_7090[n].f_036 = 3;
                    g_7090[n].f_03a = 2;
                    return;
                }
                if (c[0] < 20000) {
                    g_7090[n].f_006 = 14;
                    g_7090[n].f_008 = sel1;
                    g_7090[n].f_036 = 3;
                    g_7090[n].f_03a = 2;
                    return;
                }
            }
            g_7090[n].f_006 = sel4t;
            g_7090[n].f_008 = sel4i;
            g_7090[n].f_036 = 2;
            if ((9 - g_9334) * 20 > g_967e * 2 && n != main_ship && g_9000 < 2)
                g_7090[n].f_036 = 3;
            g_7090[n].f_03a = 2;
            if (sel4t == 0 && object_records[0][sel4i].f_2f < 0) {
                g_7090[n].f_036 = 1;
                fn_04_6e70(n);
            }
            fn_04_6700(n);
            return;
        }
    }
    if (sel6 == 3) {
        if (n != main_ship || !flow_interactive || best3 < 600 && g_7090[n].f_026[0] > 45
            || best4 < 80000 || sel3t == 0 || sel3t == 9 || sel3t == 2) {
            if (sel3t != -1 && sel3i != -1 && sel3t <= 14) {
                if ((cls == 6 || rand() % (g_7090[n].f_05e + 2) < 2 || g_7090[n].f_036 == 1
                     || sel3t != 3 && sel3t != 8)
                    && (g_7090[n].f_05e + 2) * 10 < g_7090[n].f_026[0]) {
                    g_7090[n].f_006 = sel3t;
                    g_7090[n].f_008 = sel3i;
                    g_7090[n].f_036 = 1;
                    g_7090[n].f_03a = 2;
                    fn_04_8346(n, sel3t, sel3i, 5);
                    return;
                }
                if (g_1e68 < 1200 && best4 < 40000 && (best1 < 10000 || best2 < 10000)) {
                    fn_13_9ae8(n);
                    g_7090[n].f_006 = sel3t;
                    g_7090[n].f_008 = sel3i;
                    g_7090[n].f_036 = 3;
                    g_7090[n].f_03a = 2;
                    return;
                }
            }
        }
    }
    best5 = 20000;
    if (g_1e68 > 800 || g_7090[n].f_006 == 8 && g_7090[n].f_008 == 0 && g_7090[n].f_036 == 3) {
        for (t = 0; t < g_9318 * 2; t += 2) {
            sc = fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[12][t].f_04);
            if (sc < best5) {
                best5 = sc;
                fn_03_06ec(main_ship, 14, n, 0xb7);
                g_7090[n].f_006 = 12;
                g_7090[n].f_008 = t;
                g_7090[n].f_036 = 2;
                g_7090[n].f_03a = 2;
            }
        }
    } else {
        if (g_7090[n].f_036)      /* empty: leaves the dead imul [layout-only] */
            ;
        g_7090[n].f_098 = now_ms + 3000;
        g_7090[n].f_058 = n;
        g_7090[n].f_006 = 8;
        g_7090[n].f_008 = 0;
        g_7090[n].f_036 = 3;
        g_7090[n].f_03a = 2;
    }
}

/* Per-frame steering of racer n toward its current target [inferred]. */
/* 4:0bde */
void fn_04_0bde(int16_t n)
{
    int16_t d;
    int16_t a;
    int16_t b;
    int16_t kind;
    int16_t idx;
    int16_t old;
    int16_t i;
    int16_t mode;
    int16_t same;
    int16_t ok;
    POINT tgt;
    POINT scr;
    RECT r1;
    RECT r2;
    RECT r3;

    if (n == g_952e && g_9e49 >= 1 && g_9e49 <= 6)
        return;
    g_1cb8[n]++;
    ok = 1;
    if (g_9320 == 6 && (g_9eb5 == 0 || g_7090[n].f_032.a == 0)) {
        fn_04_144c(n, g_9208 > 0 || g_1cb8[n] & 1);
        g_7090[n].f_006 = g_7090[n].f_032.a;
        g_7090[n].f_008 = g_7090[n].f_032.b;
        g_7090[n].f_03a = g_7090[n].f_03c;
        g_7090[n].f_036 = g_7090[n].f_038;
        if (g_9134 != 2)
            fn_04_4fc8(n);
    }
    if (g_7090[n].f_036 == 1 || g_7090[n].f_006 != g_7090[n].f_032.a || g_7090[n].f_008 != g_7090[n].f_032.b)
        same = 0;
    else
        same = 1;
    kind = g_7090[n].f_006;
    idx = g_7090[n].f_008;
    if (kind == -1)
        fn_04_0078(n);
    if (kind == 14 && g_7090[idx].f_0e8) {
        tgt.x = g_7090[idx].f_14a.x;
        tgt.y = g_7090[idx].f_14a.y;
    } else if (kind == 12 && !(idx & 1) && object_records[14][n].f_1a && object_records[8][idx].f_1a
               && object_records[8][idx].f_00.y < object_records[14][n].f_00.y) {
        tgt.y = object_records[kind][idx].f_04.y - 400;
        scr = fn_08_29ea(object_records[12][idx].f_04);
        if (object_records[14][n].f_00.x > scr.x)
            tgt.x = object_records[kind][idx].f_04.x + 1400;
        else
            tgt.x = object_records[kind][idx].f_04.x - 1400;
        if (tgt.x < 0)
            tgt.x += (LO16(g_05a0)) * 8;
        else if (tgt.x > (int16_t)((LO16(g_05a0)) * 8))
            tgt.x -= (LO16(g_05a0)) * 8;
    } else
        tgt = object_records[kind][idx].f_04;
    d = fn_08_285a(&a, &b, object_records[14][n].f_04, tgt);
    if (g_7090[n].f_036 != 2 && d < 220) {
        if (kind == 14 && g_7090[n].f_052 == 5 || g_7090[n].f_052 == 20)
            g_7090[n].f_03a = 7;
        else if (kind == 9 && d < 180 && g_7090[n].f_032.a == 9 && g_7090[n].f_036 == 1
                 || kind == 14 && g_7090[idx].f_006 == 14 && g_7090[idx].f_008 == n
                    && (fn_09_88ba(object_records[14][n].f_0c) > 34 || fn_09_88ba(object_records[14][n].f_0e) > 34)) {
            fn_11_5ab6(n, 5);
            ok = 0;
        }
    }
    if (g_7090[n].f_036 == 1 && d > 100 && g_9208 > 1
        && ((int32_t)object_records[14][n].f_0e * b + (int32_t)object_records[14][n].f_0c * a) / d < -50) {
        fn_11_5ab6(n, 5);
        ok = 0;
    }
    mode = g_7090[n].f_03a;
    if (mode == 7) {
        mode = 3;
        g_7090[n].f_03a = 2;
    }
    if (g_9320 == 6 && (g_7090[n].f_03a == 3 || g_7090[n].f_03a == 4) && g_9eb5 == 0) {
        g_7090[n].f_006 = kind = g_7090[n].f_032.a;
        g_7090[n].f_008 = idx = g_7090[n].f_032.b;
        if (g_7090[n].f_03a == 3) {
            if (object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52)
                g_7090[n].f_149 += 2;
            else
                g_7090[n].f_149 -= 2;
        } else if (g_7090[n].f_03a == 4) {
            if (object_records[8][g_7090[n].f_148 + g_9318 * 2].f_52)
                g_7090[n].f_149 -= 2;
            else
                g_7090[n].f_149 += 2;
        }
        g_7090[n].f_036 = g_7090[n].f_03a = mode = 2;
        g_7090[n].f_061 = 1;
        tgt = object_records[kind][idx].f_04;
    }
    old = object_records[14][n].f_28;
    object_records[14][n].f_28 = steer_toward_direction(object_records[14][n].f_04.y, object_records[14][n].f_04.x,
                                               tgt.y, tgt.x, object_records[14][n].f_28, mode, n,
                                               kind, idx, same);
    if (object_records[14][n].f_28 != old)
        fn_13_6716(n);
    if ((object_records[14][n].f_28 == old || (int16_t)(object_records[14][n].f_28 - old) == 1 || (int16_t)(object_records[14][n].f_28 - old) == -1
         || g_9320 == 6 && g_7090[n].f_03c == 2 && fn_09_88ba(g_7090[n].f_149 < 5) && g_9eb5 == 0)
        && g_7090[n].f_038 != 5 && ok) {
        if (g_9320 != 6 || g_7090[n].f_061 || g_9eb5)
            fn_11_5ab6(n, 1);
        else
            fn_11_5ab6(n, 6);
    } else if (g_7090[n].f_03a == 3 || g_7090[n].f_03a == 4) {
        fn_11_5ab6(n, 1);
        g_7090[n].f_061 = 1;
    } else {
        fn_11_5ab6(n, 6);
        if (g_9320 == 6) {
            if (g_8e3c[n] < 2)
                g_7090[n].f_016 = g_7090[n].f_014 / 3;
            else if (g_8e3c[n] < 4)
                g_7090[n].f_016 = g_7090[n].f_014 / 2;
        }
    }
    if (g_7090[n].f_03a == 3 || g_7090[n].f_03a == 4)
        g_7090[n].f_016 = g_7090[n].f_014 / 3;
    if (g_7090[n].f_03a == 5 && d < 70 && ok)
        fn_11_5ab6(n, 2);
    if (g_7090[n].f_03a == 2 && g_7090[n].f_036 == 2) {
        if (!(g_7090[n].f_030 & 1) && g_932e > 1 && d < 220 && g_7090[n].f_01e > 200
            && object_records[14][n].f_28 == old && kind == 0)
            fn_11_5ab6(n, 2);
        else if ((d > 800 && g_7090[n].f_026[0] > 50 && g_7090[n].f_01e > 200 && ok
                  || g_9320 == 6 && d > 500 && object_records[14][n].f_51 == 0 && g_7090[n].f_01e > 200)
                 && object_records[14][n].f_28 == old) {
            if (rand() % 18 == 0 && g_9320 != 6
                || g_9320 == 6 && object_records[14][n].f_51 == 0 && (!(rand() & 7) || g_7090[n].f_149 > 2))
                fn_11_5ab6(n, 2);
            g_7090[n].f_061 = 1;
        } else if (d < 400 && d > 80 && g_9208 > 1) {
            if (object_records[kind][idx].f_53 && (object_records[kind][idx].f_54 == 0 || kind == 4))
                for (i = 1; i < g_7090[n].cnt; i++)
                    if (g_7090[n].f_0b8[i] == 2) {
                        if (object_records[14][n].f_36 != 10 && object_records[14][n].f_36 != g_7090[n].f_032.a
                            && (kind != 0 || (int32_t)g_7090[n].f_0ce + g_7090[n].f_0dc >= 400)
                            && (kind != 4 || g_96d2[g_7090[n].f_04e].f_1e - 50 >= g_7090[n].f_01e))
                            fn_04_584c(i, n, 0);
                        break;
                    }
        } else if (g_9134 == 2 && d < 100)
            fn_11_5ab6(n, 2);
        if (object_records[14][n].f_1a == 0) {
            SetRect(&r1, object_records[kind][idx].f_04.x - 0x90, object_records[kind][idx].f_04.y - 0x90,
                    object_records[kind][idx].f_04.x + 0x180, object_records[kind][idx].f_04.y + 0x180);
            SetRect(&r2, object_records[14][n].f_04.x, object_records[14][n].f_04.y,
                    object_records[14][n].f_04.x + object_records[14][n].f_20, object_records[14][n].f_04.y + object_records[14][n].f_20);
            if (IntersectRect(&r3, &r1, &r2))
                fn_13_16ac(n, kind << 8 | (char)idx);
        }
    }
}

/* Race checkpoint progress for the player's ship [inferred]. */
/* 4:277a */
void fn_04_277a(void)
{
    int16_t u4;
    POINT pos;
    POINT d1;
    POINT vel;
    POINT d2;
    POINT save;
    int32_t u1c;
    int16_t i;
    int32_t dist2;
    int32_t u26;
    int32_t dist;
    int32_t r1;
    int32_t r2;
    int32_t r3;

    if (g_9eb5 == 1)
        return;
    if (g_7090[main_ship].f_148 < 0) {
        g_7090[main_ship].f_148 = 0;
        g_7090[main_ship].f_0da = 0;
    }
    save.x = g_240c;
    save.y = g_2410;
    g_240c = object_records[8][g_7090[main_ship].f_148 + g_9318 * 2].f_04.x - (LO16(g_90ea) << (g_9150 - 1));
    g_2410 = object_records[8][g_7090[main_ship].f_148 + g_9318 * 2].f_04.y - (HI16(g_90ea) << (g_9150 - 1));
    pos = fn_08_29ea(object_records[14][main_ship].f_04);
    g_1cea = fn_08_29ea(object_records[8][g_7090[main_ship].f_148 + g_9318 * 2].f_04);
    if (g_7090[main_ship].f_148 < g_9ea2 - 1)
        g_1cee = fn_08_29ea(object_records[8][g_7090[main_ship].f_148 + g_9318 * 2 + 1].f_04);
    else
        g_1cee = fn_08_29ea(object_records[8][g_9318 * 2].f_04);
    if (g_7090[main_ship].f_148 > 0)
        g_1cf2 = fn_08_29ea(object_records[8][g_7090[main_ship].f_148 + g_9318 * 2 - 1].f_04);
    else
        g_1cf2 = fn_08_29ea(object_records[8][g_9318 * 2 + g_9ea2 - 1].f_04);
    vel = VIEW(POINT, object_records[14][main_ship].f_0c, 0);
    g_8e48[main_ship] = dist = fn_08_35d0(d1.x = (pos.x - g_1cea.x) * 2 >> g_9156,
                                       d1.y = (pos.y - g_1cea.y) * 2 >> g_9156);
    if (dist < 350 || rand() % 5 == 0) {
        dist2 = fn_08_35d0(d2.x = (g_1cf2.x - g_1cea.x) * 2 >> g_9156,
                           d2.y = (g_1cf2.y - g_1cea.y) * 2 >> g_9156);
        r1 = (((int32_t)d2.x * d1.x + (int32_t)d2.y * d1.y) << 7) / (dist * dist2);
        if (r1 < 0) {
            dist2 = fn_08_35d0(d2.x = (g_1cee.x - g_1cea.x) * 2 >> g_9156,
                               d2.y = (g_1cee.y - g_1cea.y) * 2 >> g_9156);
            r2 = (((int32_t)d2.x * d1.x + (int32_t)d2.y * d1.y) << 7) / (dist * dist2);
            r3 = (((int32_t)d2.y * d1.x - (int32_t)d2.x * d1.y) << 7) / (dist * dist2);
            if (r2 > r1) {
                fn_10_744c(2);
                if (object_records[14][main_ship].f_51 == 0) {
                    int16_t v;

                    if (g_7090[main_ship].f_0da < 0)
                        v = -1 - g_7090[main_ship].f_0da;
                    else
                        v = g_7090[main_ship].f_0da;
                    g_3d4c[(main_ship * g_9ea0 + v) * g_9ea2 + g_7090[main_ship].f_148 + 1] = g_1e68;
                    for (i = 0; i <= g_9316; i++)
                        if (object_records[14][i].f_18 == 0 && i != main_ship
                            && g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[main_ship].f_148 + 1] != 0)
                            g_8e08[i] = g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[main_ship].f_148 + 1]
                                - g_3d4c[(main_ship * g_9ea0 + v) * g_9ea2 + g_7090[main_ship].f_148 + 1];
                        else if (g_8e08[i] < 0)
                            g_8e08[i] = 50000;
                    if (g_7090[main_ship].f_148 < g_9ea2 - 1)
                        g_7090[main_ship].f_148++;
                    else {
                        g_7090[main_ship].f_148 = 0;
                        g_7090[main_ship].f_0da = -1 - g_7090[main_ship].f_0da;
                    }
                }
            }
            g_1d02 = r3;
        }
    }
    if (object_records[14][main_ship].f_51 && g_1e68 - g_9e70[main_ship] > 600 && g_9eb5 == 0)
        g_7090[main_ship].f_0da = -1 - g_9ea0;
    if (g_7090[main_ship].f_0da < 0) {
        if ((int16_t)(object_records[14][main_ship].f_04.x + object_records[14][main_ship].f_20) > (int16_t)(object_records[12][1].f_04.x + 350)
            && object_records[14][main_ship].f_04.x < (int16_t)(object_records[12][1].f_04.x + 2000)
            && object_records[14][main_ship].f_04.y + object_records[14][main_ship].f_20 > g_9ea8[g_9322].x
            && object_records[14][main_ship].f_04.y < g_9ea8[g_9322].y
            && (object_records[14][main_ship].f_0c > 0 || g_7090[main_ship].f_0da + g_9ea0 == -1)) {
            fn_10_744c(0x72);
            if (object_records[14][main_ship].f_51 == 0) {
                g_9e80[main_ship] = g_9e70[main_ship];
                g_9e70[main_ship] = g_1e68;
                if (g_9e90[main_ship] == 0 || g_1e68 - g_9e80[main_ship] < g_9e90[main_ship])
                    g_9e90[main_ship] = g_9e70[main_ship] - g_9e80[main_ship];
            }
            g_7090[main_ship].f_0da = -g_7090[main_ship].f_0da;
            if (g_7090[main_ship].f_0da - g_9ea0 == -1)
                fn_10_744c(0x4f);
            if (g_7090[main_ship].f_0da >= g_9ea0 && g_9eb5 == 0)
                fn_04_2da2();
        }
    }
    g_240c = save.x;
    g_2410 = save.y;
}

/* Racer n reports what hit it (event ev, attacker kind/m) [inferred]. */
/* 4:474c */
void fn_04_474c(int16_t n, int16_t kind, int16_t m, int16_t ev)
{
    if (g_1d06 > now_ms || object_records[14][n].f_1a == 0)
        return;
    g_1d06 = now_ms + 20000;
    if (ev == 5)
        fn_03_06ec(main_ship, 14, n, 0xa5);
    else if (ev == 2) {
        if (kind == 3 || kind == 8 || kind == 1)
            fn_03_06ec(main_ship, 14, n, 0xa6);
        else if (kind == 9)
            fn_03_06ec(main_ship, 14, n, 0xa7);
        else if (kind == 0 && object_records[0][m].f_53 == 1)
            fn_03_06ec(main_ship, 14, n, 0xa8);
        else if (kind == 0)
            fn_03_06ec(main_ship, 14, n, 0xa9);
        else if (kind == 2)
            fn_03_06ec(main_ship, 14, n, 0xaa);
        else if (kind == 14 && fn_13_2688(n, m) < 0 && g_96d2[g_7090[m].f_04e].f_38 == 3)
            fn_03_06ec(main_ship, 14, n, 0xad);
        else if (kind == 14 && fn_13_2688(n, m) < 0)
            fn_03_06ec(main_ship, 14, n, 0xab);
        else if (kind == 14)
            fn_03_06ec(main_ship, 14, n, 0xac);
    }
}

/* Picks ship n's current target and its approach side [inferred]. */
/* 4:4fc8 */
void fn_04_4fc8(int16_t n)
{
    int16_t size;
    int16_t d;
    int16_t a;
    int16_t b;
    int16_t best;
    int16_t sel;
    int16_t i;
    int32_t dx;
    int32_t dy;
    int32_t ex;
    int32_t ey;
    int32_t c;
    int32_t v;
    int16_t changed;
    RECT rc2;
    RECT rc;

    size = object_records[14][n].f_22;
    changed = 1;
    if (object_records[14][n].f_1a == 0) {
        g_7090[n].f_006 = g_7090[n].f_032.a;
        g_7090[n].f_008 = g_7090[n].f_032.b;
        g_7090[n].f_036 = g_7090[n].f_038;
        g_7090[n].f_03a = g_7090[n].f_03c;
    } else {
        v = fn_13_1076(14, n);
        if (v != -1) {
            if (HIBYTE(v) == g_7090[n].f_006 && LOBYTE(v) == g_7090[n].f_008)
                changed = 0;
            g_7090[n].f_006 = HIBYTE(v);
            g_7090[n].f_008 = LOBYTE(v);
            g_7090[n].f_036 = 3;
            if (HIBYTE(v) == 8 && g_3d50[LOBYTE(v)].f_0a == -3)
                g_7090[n].f_03a = 5;
            else if (g_7090[n].f_032.a == 12 && g_7090[n].f_038 == 2 && HIBYTE(v) == 8
                     && LOBYTE(v) < g_9318 * 2) {
                if (!(LOBYTE(v) & 1))
                    g_7090[n].f_03a = 4;
                else
                    g_7090[n].f_03a = 3;
            } else {
                dx = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_04.x - object_records[14][n].f_04.x);
                dy = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_04.y - object_records[14][n].f_04.y);
                ex = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_0c - object_records[14][n].f_0c);
                ey = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_0e - object_records[14][n].f_0e);
                if ((c = dx * ey - dy * ex) > 0)
                    g_7090[n].f_03a = 4;
                else
                    g_7090[n].f_03a = 3;
            }
        } else {
            best = 350;
            for (i = 0; i < g_9406[9]; i++)
                if (object_records[9][i].f_18 == 0 && object_records[9][i].f_1a != 0
                    && (g_7090[n].f_032.a != 9 || g_7090[n].f_032.b != i)) {
                    d = fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[9][i].f_04);
                    if (d < best) {
                        best = d;
                        sel = i;
                    }
                }
            if (best < 250) {
                g_7090[n].f_006 = 9;
                g_7090[n].f_008 = sel;
                g_7090[n].f_036 = 3;
                dx = (int16_t)(object_records[9][sel].f_04.x - object_records[14][n].f_04.x);
                dy = (int16_t)(object_records[9][sel].f_04.y - object_records[14][n].f_04.y);
                ex = (int16_t)(object_records[9][sel].f_0c - object_records[14][n].f_0c);
                ey = (int16_t)(object_records[9][sel].f_0e - object_records[14][n].f_0e);
                if ((c = dx * ey - dy * ex) > 0)
                    g_7090[n].f_03a = 4;
                else
                    g_7090[n].f_03a = 3;
                best = 20000;
            } else
                best = 18888;
            for (i = 0; i < g_9406[6]; i++)
                if (object_records[6][i].f_18 == 0 && (g_6670[i + 4].r.left != 14 || g_6670[i + 4].r.top != n)
                    && (g_6670[i + 4].f_04.x) != 0x1b) {
                    d = fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[6][i].f_04);
                    if (d < best) {
                        best = d;
                        sel = i;
                    }
                }
            if (best < 160) {
                for (i = 1; i <= g_7090[n].cnt; i++)
                    if (g_2f4c[g_7090[n].f_0b8[i]].f_4e) {
                        if (g_7090[n].f_0b8[i] != 2
                            || object_records[14][n].f_36 == -1 && (g_2f4c[(g_6670[i + 4].f_04.x)].f_12 == 1
                                                           || g_2f4c[(g_6670[i + 4].f_04.x)].f_12 == 5))
                            fn_04_584c(i, n, 0);
                        break;
                    }
            }
            if (best < 400) {
                if (g_7090[n].f_05e * 15 + 40 > g_7090[n].f_026[0]) {
                    g_7090[n].f_006 = 6;
                    g_7090[n].f_008 = sel;
                    g_7090[n].f_036 = 3;
                    g_7090[n].f_03a = 5;
                }
            } else if (best == 18888) {
                g_7090[n].f_006 = g_7090[n].f_032.a;
                g_7090[n].f_008 = g_7090[n].f_032.b;
                g_7090[n].f_036 = g_7090[n].f_038;
                g_7090[n].f_03a = g_7090[n].f_03c;
            }
        }
    }
    if (fn_13_371c(g_7090[n].f_032.a, g_7090[n].f_032.b) && object_records[14][n].f_1a == 0) {
        SetRect(&rc, object_records[14][n].f_04.x - 800, object_records[14][n].f_04.y - 800,
                object_records[14][n].f_04.x + object_records[14][n].f_22 + 800,
                object_records[14][n].f_04.y + object_records[14][n].f_22 + 800);
        if (IntersectRect(&rc2, (RECT *)&g_6670[g_7090[n].f_032.b / 2 - 4 + 4], &rc)
            && g_7090[n].f_088 + 3000 < now_ms)
            fn_12_2288(14, n);
    }
}

/* Sets g_66e8[n].f0c from the side of the targeted object [inferred]. */
/* 4:5514 */
void fn_04_5514(int16_t n)
{
     /* same records seen from DS:66e4: makes CL
                                 * load f08 first in the compare [layout-only] */
    int32_t dx;
    int32_t dy;
    int32_t ex;
    int32_t ey;
    int16_t size;                   /* never read: its load puts the record
                                 * address add before the es load */
    int16_t unused3;                /* frame filler [inferred] */
    int32_t l;
    char unused[10];           /* frame filler [inferred] */
    int32_t v;
    char unused2[16];

    size = object_records[6][n].f_22;
    if (object_records[6][n].f_1a) {
        v = l = fn_13_1076(6, n);
        if (l != -1) {
            g_6670[n + 4].f_10 = HIBYTE(l);
            g_6670[n + 4].f_12 = LOBYTE(l);
            if (g_6670[n + 4].r.left != g_6670[n + 4].f_10 || g_6670[n + 4].r.top != g_6670[n + 4].f_12) {
                dx = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_04.x - object_records[6][n].f_04.x);
                dy = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_04.y - object_records[6][n].f_04.y);
                ex = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_0c - object_records[6][n].f_0c);
                ey = (int16_t)(object_records[HIBYTE(v)][LOBYTE(v)].f_0e - object_records[6][n].f_0e);
                if (dx * ey - dy * ex > 0)
                    g_6670[n + 4].f_14 = 4;
                else
                    g_6670[n + 4].f_14 = 3;
                return;
            }
        }
    }
    g_6670[n + 4].f_14 = 2;
}

/* 4:584c */
void fn_04_584c(int16_t s, int16_t n, int16_t t)
{
    int16_t k;

    if (object_records[14][n].f_2e)
        return;
    if (n == main_ship && g_9134 == 0)
        g_8e28 = now_ms;
    k = g_7090[n].f_0b8[s];
    if (g_2f4c[k].f_4a == 0)
        g_7090[n].f_0ca = g_7090[n].f_05e * 4 + g_2f4c[k].f_30;
    else {
        g_7090[n].f_0ca = 2;
        g_7090[n].f_0d4 = g_2f4c[k].f_30 * 3;
    }
    fn_13_4eec(n, 5);
    if (g_2f4c[k].f_12)
        fn_11_7c12(k, 14, n);
    else if (k == 5)
        fn_13_1318(14, n, t, 5);
    else if (k == 4)
        fn_13_1318(14, n, t, 4);
    else if (k == 1)
        fn_11_8a42(14, n);
    else if (k == 2)
        fn_11_947a(14, n, 2);
    else if (k == 15)
        fn_11_947a(14, n, 15);
    else if (k == 3)
        fn_11_9fdc(14, n);
    else if (k == 23)
        fn_11_9daa(14, n);
    else if (k == 13)
        fn_11_9078(14, n);
    if (n == main_ship && g_9134 && g_7090[n].f_018 != s) {
        g_9524 = s;
        g_7090[n].f_018 = s;
        fn_11_2f8c();
    }
    g_7090[n].f_018 = s;
}

/* Scores how useful weapon slot s of racer n is against its current
 * target (-2000 / -100 / 0 = not usable) [inferred]. */
/* 4:6a78 */
int16_t fn_04_6a78(int16_t n, int16_t s)
{
    int16_t w;
    int16_t type;
    int16_t idx;
    int16_t unused;
    int16_t a;
    int16_t b;
    int16_t rel;
    int16_t ratio;
    int16_t v;
    int16_t score;
    int16_t i;
    int16_t count;

    w = g_7090[n].f_0b8[s];
    type = g_7090[n].f_032.a;
    idx = g_7090[n].f_032.b;
    if (g_2f4c[w].f_32 == 0)
        return -2000;
    if (type != 14
        && ((g_7090[n].f_0ae[s] < 14 && g_2f4c[g_7090[n].f_0b8[s]].f_12)
            || g_2f4c[g_7090[n].f_0b8[s]].f_34 > 3))
        return -2000;
    score = 0;
    if (type == 14) {
        rel = fn_13_2688(n, idx);
        ratio = fn_04_5d9c(n, idx);
    } else {
        rel = -100;
        ratio = 100;
    }
    v = 7;
    if (rel < 0)
        v = 8;
    else
        v--;
    if (rel < -60)
        v++;
    if (rel > 60)
        v--;
    if (rel < -270)
        v++;
    if (rel > 250)
        v--;
    v -= g_7090[n].f_05e;
    if (ratio < 60)
        v++;
    if (ratio < 25)
        v++;
    if (g_96d2[g_7090[n].f_04e].f_38 == 3 || g_96d2[g_7090[n].f_04e].f_38 == 1
        || g_96d2[g_7090[n].f_04e].f_38 == 4)
        v += 2;
    v -= g_7090[n].f_13e[g_7090[n].f_032.b] / 2;
    if (g_7090[n].f_052 == 3 || g_7090[n].f_052 == 4)
        v += 2;
    if (g_2f4c[w].f_32 < v)
        v += -(v - g_2f4c[w].f_32) * 3 / 4;
    if (type == 14 && g_7090[idx].f_0e2 && g_2f4c[w].f_4a == 0)
        score += 7;
    if (g_2f4c[w].f_4a && type != 14)
        return 0;
    if (g_2f4c[w].f_32 < 3)
        return 0;
    if (g_2f4c[w].f_32 - 3 > v)
        return 0;
    score += rand() % 3 - fn_09_88ba(v - g_2f4c[w].f_32) + 12;
    if (w == 2) {
        count = 0;
        for (i = 0; i < g_9406[3]; i++) {
            if (object_records[3][i].f_18 == 0 && object_records[3][i].f_44 > 500
                && fn_08_285a(&a, &b, object_records[3][i].f_04, object_records[14][n].f_04) < 320) {
                count++;
                if (count > 1)
                    break;
            }
        }
        for (i = 0; i < g_9406[8]; i++) {
            if (object_records[8][i].f_18 == 0 && object_records[8][i].f_44 > 500
                && fn_08_285a(&a, &b, object_records[8][i].f_04, object_records[14][n].f_04) < 320) {
                count++;
                if (count > 1)
                    break;
            }
        }
        if (count == 0)
            return 0;
        if (count > 1)
            score += 2;
    }
    if (g_7090[n].f_038 == 4) {
        if (g_2f4c[w].f_0c == 2)
            score += 12;
        if (g_2f4c[w].f_0c == 3)
            score += 7;
    }
    if (g_7090[n].f_01e < 250 && g_2f4c[w].f_36 != 0) {
        score -= 2;
        if (g_7090[n].f_01e < 75)
            score -= 2;
        if (g_2f4c[w].f_36 > 50)
            score -= 2;
        if (g_2f4c[w].f_36 * 2 > g_7090[n].f_01e)
            return 0;
    }
    if (g_2f4c[w].f_34 != 0 && (g_2f4c[w].f_34 + 5) * 5 > g_7090[n].f_026[0]) {
        score -= g_2f4c[w].f_34;
        if (g_2f4c[w].f_34 * 3 + 13 > g_7090[n].f_026[0] || g_7090[n].f_032.a != 14)
            return -100;
    }
    if (score > 0 && g_2f4c[w].f_4a && g_7090[n].f_032.a == 14) {
        if (g_7090[n].f_0d4 > 0)
            return 0;
        if (g_7090[n].f_038 == 4)
            score += 3;
        if (ratio > 250)
            return 0;
        if (type != 14)
            return 0;
        if (g_7090[n].f_13e[g_7090[n].f_032.b] < 0)
            score += -(g_7090[n].f_13e[g_7090[n].f_032.b] * 2 - 3);
    }
    return score;
}

/* 4:6e70 */
void fn_04_6e70(int16_t n)
{
    int16_t i;
    int16_t best;
    int16_t sel;
    int16_t v;
    int16_t j;

    i = g_7090[n].f_018;
    g_7090[n].f_05f = 0;
    best = -1000;
    sel = -1;
    if (g_7090[n].cnt <= 1)
        return;
    for (i = 1; i < g_7090[n].cnt; i++) {
        if (g_7090[n].f_0ae[i] > 0) {
            if (g_7090[n].f_032.a == 0 && object_records[0][g_7090[n].f_032.b].f_2f < 0 && g_7090[n].f_0b8[i] == 5)
                v = 10000;
            else
                v = fn_04_6a78(n, i);
            if (v > best) {
                sel = i;
                best = v;
            }
        }
    }

    if (best > 0) {
        if (g_2f4c[g_7090[n].f_0b8[sel]].f_0c == 2)
            g_7090[n].f_05f = 2;
        else if (g_2f4c[g_7090[n].f_0b8[sel]].f_0c == 3)
            g_7090[n].f_05f = 3;
        else
            g_7090[n].f_05f = 1;
        g_7090[n].f_018 = sel;
    } else if (best == -100) {
        best = 100;
        for (j = 1; j < g_7090[n].cnt; j++) {
            if (g_7090[n].f_0ae[j] >= 0 && g_2f4c[g_7090[n].f_0b8[j]].f_36 < g_7090[n].f_01e
                && g_2f4c[g_7090[n].f_0b8[j]].f_34 < best) {
                best = g_2f4c[g_7090[n].f_0b8[j]].f_34;
                sel = j;
            }
        }

        if (best < 100) {
            if (g_2f4c[g_7090[n].f_0b8[sel]].f_0c == 2)
                g_7090[n].f_05f = 2;
            else if (g_2f4c[g_7090[n].f_0b8[sel]].f_0c == 3)
                g_7090[n].f_05f = 3;
            else
                g_7090[n].f_05f = 1;
            g_7090[n].f_018 = sel;
        } else {
            g_7090[n].f_018 = 0;
            g_7090[n].f_05f = 1;
        }
    } else {
        g_7090[n].f_018 = 0;
        g_7090[n].f_05f = 1;
    }
    if (n == main_ship)
        fn_11_2f8c();
}

/* Decides whether the police or other enforcers are summoned against
 * the player (two warning stages via g_1d0a / g_1d0e) [inferred]. */
/* Racer n reacts to a grudge against racer j (f72 / fee): radio
 * message, then attack orders, ganging up for class 2 [inferred].
 * Returns 1 when it acted. */
/* 4:702e */
int16_t fn_04_702e(int16_t n)
{
    char buf[40];
    char name[20];
    int16_t j;
    int16_t k;
    int16_t age;
    int16_t mode;
    int16_t found;
    int16_t locked;
    int16_t alt;

    locked = found = 0;
    if (g_7090[n].f_0ee[main_ship] == 0)
        return 0;
    if ((g_7090[n].f_062 + 8)[main_ship] == 0)
        return 0;
    if (g_92e8 || g_9320 == 7 || g_9320 == 6)
        return 0;
    if (g_7090[n].f_000 != 0 && g_7090[n].f_000 < 4)
        g_7090[n].f_000--;
    if ((n == main_ship && !flow_interactive) || object_records[14][n].f_1a == 0)
        return 0;
    if (g_7090[n].f_000 != 0) {
        if (g_7090[n].f_000 == 4)
            fn_03_06ec(main_ship, 14, n, 0x88);
        g_7090[n].f_000--;
        return 0;
    }
    if (g_7090[n].f_026[0] < 45)
        return 0;
    if (g_96d2[g_7090[n].f_04e].f_38 == 4 || g_934e < 7)
        return 0;
    for (j = 0; j < g_9316; j++) {
        if (object_records[14][j].f_1a != 0 && j != n && (g_7090[n].f_062 + 8)[j] > 5
            && g_96d2[g_7090[n].f_04e].f_38 != 7) {
            if (g_96d2[g_7090[j].f_04e].f_38 == g_96d2[g_7090[n].f_04e].f_38
                && g_7090[n].f_0ee[j] <= 8 && g_7090[n].f_0ee[j] != 4) {
                g_7090[n].f_0ee[j] = 0;
                return (g_7090[n].f_062 + 8)[j] = 0;
            } else {
                if (g_7090[n].f_0ee[j] <= 5) {
                    mode = 1;
                    if (rand() % 3 == 0)
                        lstrcpy(buf, g_380c);
                    else if (g_7090[n].f_05e == 0)
                        LoadString(lang_module, 0x29c, buf, 40);
                    else if (g_7090[n].f_05e < 3)
                        LoadString(lang_module, 0x29d, buf, 40);
                    else if (g_7090[n].f_05e == 3)
                        LoadString(lang_module, 0x29e, buf, 40);
                } else {
                    mode = 0;
                    if (rand() % 3 == 0)
                        lstrcpy(buf, g_380c);
                    else if (g_7090[n].f_05d == 0)
                        LoadString(lang_module, 0x29f, buf, 40);
                    else if (g_7090[n].f_05d < 2)
                        LoadString(lang_module, 0x2a0, buf, 40);
                    else if (g_7090[n].f_05d == 3)
                        LoadString(lang_module, 0x2a1, buf, 40);
                }
                if (g_7090[n].f_0ee[j] == 4) {
                    for (k = 0; k < 3; k++) {
                        if (g_4eec[g_96d2[g_7090[n].f_04e].f_38][k] == g_7090[j].f_0d6) {
                            found = 1;
                            if (g_6e20 == 0) {
                                fn_14_3eda();
                                locked = 1;
                            }
                            lstrcpy(name, g_6e20[g_6b10[g_96d2[g_7090[n].f_04e].f_38][k]].f_0a);
                            age = g_91f8 - g_4fd0[g_96d2[g_7090[n].f_04e].f_38][k];
                        }
                    }
                }
                if (!found && !(rand() & 1))
                    alt = 1;
                else
                    alt = 0;
                format_string(g_8d38, 0xbd9, 1, !(rand() & 1), (LPSTR)buf, alt, !found,
                           g_7090[n].f_0ee[j] + 0x351, found, (LPSTR)name, age, g_09d6);
                if (locked && found)
                    fn_14_4074();
                fn_03_06ec(j, 14, n, mode + 0x4f);
                if (mode) {
                    if ((g_7090[n].f_062 + 8)[j] < 9 || g_96d2[g_7090[n].f_04e].f_38 == 2) {
                        g_7090[n].f_052 = 0;
                        g_7090[n].f_006 = g_7090[n].f_032.a = 14;
                        g_7090[n].f_008 = g_7090[n].f_032.b = j;
                        g_7090[n].f_094 = now_ms + 8000;
                        g_7090[n].f_038 = 1;
                        g_7090[n].f_036 = 1;
                        g_7090[n].f_03c = 2;
                        g_7090[n].f_03a = 2;
                        if (g_96d2[g_7090[n].f_04e].f_38 == 2) {
                            for (k = 0; k <= g_9316; k++) {
                                if (g_96d2[g_7090[k].f_04e].f_38 == 2 && k != j) {
                                    g_7090[k].f_038 = 3;
                                    g_7090[k].f_036 = 3;
                                    g_7090[k].f_03c = 2;
                                    g_7090[k].f_03a = 2;
                                    g_7090[k].f_052 = 0;
                                    g_7090[k].f_006 = g_7090[k].f_032.a = 14;
                                    g_7090[k].f_008 = g_7090[k].f_032.b = j;
                                    g_7090[k].f_094 = now_ms + 15000;
                                }
                                if (g_96d2[g_7090[k].f_04e].f_38 == 0
                                    && (g_7090[n].f_0ee[j] == 3 || g_7090[n].f_0ee[j] == 1)) {
                                    g_7090[k].f_052 = 2;
                                    g_7090[k].f_098 = now_ms + 20000;
                                    g_7090[k].f_054 = 14;
                                    g_7090[k].f_056 = j;
                                    g_7090[k].f_058 = n;
                                    g_7090[k].f_0ed = 1;
                                    fn_03_00f4(n, g_7090[n].f_054, g_7090[n].f_056);
                                    fn_04_8346(k, 14, j, 8);
                                    g_7090[k].f_0ee[j] = 3;
                                    (g_7090[k].f_062 + 8)[j] = 0;
                                }
                            }
                        } else
                            fn_04_8346(n, 14, j, 8);
                    } else {
                        if ((g_7090[n].f_062 + 8)[j] < 14)
                            g_7090[n].f_052 = 2;
                        else if ((g_7090[n].f_062 + 8)[j] < 18)
                            g_7090[n].f_052 = 3;
                        else
                            g_7090[n].f_052 = 4;
                        fn_04_8346(n, 14, j, 8);
                        g_7090[n].f_098 = now_ms + 20000;
                        g_7090[n].f_054 = 14;
                        g_7090[n].f_056 = j;
                        g_7090[n].f_058 = n;
                        g_7090[n].f_0ed = 1;
                        fn_03_00f4(n, g_7090[n].f_054, g_7090[n].f_056);
                    }
                    if (g_7090[n].f_0ee[j] == 4) {
                        for (k = 0; k < 3; k++)
                            if (g_4eec[g_96d2[g_7090[n].f_04e].f_38][k] == g_7090[j].f_0d6)
                                g_4eec[g_96d2[g_7090[n].f_04e].f_38][k] = -1;
                    }
                }
                (g_7090[n].f_062 + 8)[j] = 0;
                return 1;
            }
        }
    }
    return 0;
}

/* 4:7e2a */
void fn_04_7e2a(void)
{
    int16_t i;
    int16_t c6;
    int16_t c8;
    int16_t v;
    int16_t chance;
    int16_t ce;
    int16_t f;

    if (g_913a || g_913c || g_1e68 - g_8e2c < 400)
        return;
    if (g_1e68 < 500) {
        g_1d0e = g_1d12 = 0;
        g_1d0a = 0;
        return;
    }
    if (g_92e8 || g_9320 == 6 || g_9320 == 7 || g_0992 + 20 > g_932a)
        return;
    if (g_3824[3][g_96d2[g_7090[main_ship].f_04e].f_38] < 150
        && (g_1d0a < now_ms || g_1d0a == 0)
        && g_9208 / 2 + 3 > g_9316 && g_7090[main_ship].f_0ce > 398) {
        f = 2;
        for (i = ce = c8 = 0; i <= g_9316; i++) {
            if (g_96d2[g_7090[i].f_04e].f_38 == 3) {
                f--;
                if (g_7090[i].f_0cd == main_ship)
                    f = 0;
            }
            if (g_7090[i].f_038 == 1 && g_7090[i].f_032.a == 14 && object_records[14][i].f_1a != 0) {
                ce++;
                if (g_7090[i].f_032.b == main_ship)
                    ce++;
            }
        }
        if (f > 0) {
            v = (g_7090[main_ship].f_0ce - 220) / 32 + g_3824[3][g_96d2[g_7090[main_ship].f_04e].f_38] / -100
                + g_9334 / 3 - ce - g_9316;
            if (g_7090[main_ship].f_026[0] < 40)
                v++;
            if ((v = (int16_t)(f * v) / 2) > rand() % 720 && g_9334 > 0) {
                if (g_1d0a != 0 && g_1d0a < now_ms) {
                    fn_13_adbe(main_ship, 3, 0x69);
                    g_1d0a = 0;
                    return;
                }
                if (g_1d0a == 0) {
                    fn_03_06ec(main_ship, 7, 0, 0x6b);
                    g_1d0a = now_ms + 7000;
                    return;
                }
            }
        }
    }
    if (g_3824[4][g_96d2[g_7090[main_ship].f_04e].f_38] > -50
        && (g_1d0e < now_ms || g_1d0e == 0)
        && g_9208 / 2 + 3 > g_9316 && g_7090[main_ship].f_026[0] < 60) {
        f = 2;
        for (i = c6 = c8 = 0; i <= g_9316; i++) {
            if (i != main_ship && g_7090[i].flag) {
                if (g_96d2[g_7090[main_ship].f_04e].f_38 == 2) {
                    if (g_96d2[g_7090[i].f_04e].f_38 == 0) {
                        f--;
                        if (g_7090[i].f_0cd == main_ship)
                            f = 0;
                    }
                } else if (g_96d2[g_7090[main_ship].f_04e].f_38 == 3) {
                    if (g_96d2[g_7090[i].f_04e].f_38 == 3) {
                        f--;
                        if (g_7090[i].f_0cd == main_ship)
                            f = 0;
                    }
                } else if (g_96d2[g_7090[i].f_04e].f_38 == 4) {
                    f--;
                    if (g_7090[i].f_0cd == main_ship)
                        f = 0;
                }
                if (g_96d2[g_7090[i].f_04e].f_38 == g_96d2[g_7090[main_ship].f_04e].f_38)
                    c8++;
                if (g_7090[i].f_038 == 1 && g_7090[i].f_032.a == 14 && g_7090[i].f_032.b == main_ship) {
                    c6++;
                    if (fn_04_5d9c(main_ship, i) < 40)
                        c6++;
                }
            }
        }
        for (i = 0; i < g_9406[2]; i++)
            if (object_records[2][i].f_18 == 0 && g_52ec[i].f_1c.a == 14 && g_52ec[i].f_1c.b == main_ship
                && g_52ec[i].f_12 == 10)
                c6++;
        if (f > 0) {
            chance = (g_3824[4][g_96d2[g_7090[main_ship].f_04e].f_38] / 120 + (c6 * 2 - c8) * 2
                      - g_7090[main_ship].f_026[0] / 15 + g_9334 / 2 - g_9316 + 5) * f / 2;
            if (c6 != 0 && rand() % 300 < chance) {
                if (g_1d0e != 0 && g_1d0e < now_ms) {
                    fn_13_adbe(main_ship, 4, 0x6a);
                    g_1d0e = 0;
                    return;
                }
                if (g_1d0e == 0) {
                    fn_03_06ec(main_ship, 7, 0, 0x6c);
                    g_1d0e = now_ms + 7000;
                    return;
                }
            }
        }
    }
    if (g_9208 / 2 + 4 > g_9316 && g_964a > 6 && g_9648 > 4 && g_9208 > 0) {
        f = 1;
        for (i = c8 = 0; i <= g_9316; i++)
            if (g_96d2[g_7090[i].f_04e].f_38 == 7)
                f = 0;
        chance = g_964a / 2 + g_3824[7][g_96d2[g_7090[main_ship].f_04e].f_38] / -140 + g_9334 / 2;
        if (f && rand() % 300 < chance)
            fn_13_adbe(main_ship, 0x16, 0x6d);
    }
}

/* 4:8346 */
int16_t fn_04_8346(int16_t n, int16_t x, int16_t y, int16_t v)
{
    if (v == 3 && g_7090[n].f_038 == 1 && g_7090[n].f_032.a == x && g_7090[n].f_032.b == y)
        v = g_7090[n].f_146;
    if (n != main_ship || flow_interactive == 0)
        fn_13_9a18(n, x, y);
    g_7090[n].f_146 = v;
    return 1;
}

/* 4:83ae */
void fn_04_83ae(void)
{
    int16_t i;
    int16_t j;
    int16_t a;
    int16_t b;
    int16_t d;

    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].flag && g_7090[i].f_0e8) {
            for (j = 0; j <= g_9316; j++) {
                if (j != i && g_7090[j].flag && g_7090[j].f_032.a == 14 && g_7090[j].f_032.b == i) {
                    d = fn_08_285a(&a, &b, object_records[14][i].f_04, g_7090[i].f_14a);
                    if (d > 350) {
                        g_7090[i].f_14a.x = rand() % 4000 + object_records[14][i].f_04.x - 2000;
                        g_7090[i].f_14a.y = rand() % 4000 + object_records[14][i].f_04.y - 2000;
                        if (g_7090[i].f_14a.x < 0)
                            g_7090[i].f_14a.x += (LO16(g_05a0)) * 8;
                        else if (g_7090[i].f_14a.x > (LO16(g_05a0)) * 8)
                            g_7090[i].f_14a.x -= (LO16(g_05a0)) * 8;
                        if (g_7090[i].f_14a.y < 0)
                            g_7090[i].f_14a.y += (HI16(g_05a0)) * 8;
                        else if (g_7090[i].f_14a.y > (HI16(g_05a0)) * 8)
                            g_7090[i].f_14a.y -= (HI16(g_05a0)) * 8;
                    }
                }
            }
        }
    }
}

/* 4:84de */
void fn_04_84de(void)
{
    int16_t i;
    int16_t count;
    int16_t r;

    g_967e = min(g_9334 * 7 + 45, 100);
    if (g_1e68 < 500)
        g_967e -= (700 - g_1e68) / 8;
    else
        g_967e = min(g_967e + g_1e68 / 100, 100);
    if (g_967e < 3)
        g_967e = 3;
    if (g_7090[main_ship].f_0ce + g_7090[main_ship].f_0dc < 100)
        g_967e -= 20;
    if (g_7090[main_ship].f_0ce + g_7090[main_ship].f_0dc > 250)
        g_967e += 20;
    if (g_7090[main_ship].f_0ce + g_7090[main_ship].f_0dc > 1000)
        g_967e += 30;
    count = 0;
    for (i = 0; i < 8; i++)
        if (object_records[0][i].f_18 == 0)
            count++;
    r = count * 10 / (g_9316 + 1);
    if (r < 15)
        g_967e -= 10;
    if (r < 10)
        g_967e -= 10;
    if (r < 5)
        g_967e -= 10;
    if (g_9000 == 0)
        g_967e = -10;
}

/* 4:8c80 */
int16_t fn_04_8c80(void)
{
    int16_t i;
    int16_t best;
    int16_t max;
    int16_t a;
    int16_t score;

    best = -1;
    max = -1;
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].flag && object_records[14][i].f_18 == 0) {
            if (g_7090[i].f_0da < 0)
                a = -g_7090[i].f_0da;
            else
                a = g_7090[i].f_0da;
            score = a * g_9ea2 + g_7090[i].f_148;
            if (score > max) {
                max = score;
                best = i;
            }
            if (score == max && g_8e48[best] > g_8e48[i]) {
                max = score;
                best = i;
            }
        }
    }
    return best;
}

/* 4:8d3a */
int16_t fn_04_8d3a(void)
{
    uint32_t best;
    int16_t i;
    int16_t found;

    best = 1000000;
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].flag && object_records[14][i].f_18 == 0 && object_records[14][i].f_51 == 2
            && g_9e60[i] < best) {
            found = i;
            best = g_9e60[i];
        }
    }
    return found;
}
/* 4:5d9c */
int16_t fn_04_5d9c(int16_t a, int16_t b)
{
    int32_t a26;
    int32_t ad8;
    int32_t b26;
    int32_t bd8;
    int32_t x;
    int32_t y;

    if (a >= 0 && a <= g_9316 && b >= 0 && b <= g_9316) {
        ad8 = g_7090[a].f_0d8;
        bd8 = g_7090[b].f_0d8;
        a26 = g_7090[a].f_026[0];
        b26 = g_7090[b].f_026[0];
        x = (int32_t)g_7090[a].f_026[0] * ad8 / (a26 / 2 + 50);
        y = (int32_t)g_7090[b].f_026[0] * bd8 / (b26 / 2 + 50);
        if (y == 0)
            y = 10;
        return x * 100 / y;
    }
    return 100;
}

/* Racer n reacts to being hit by m (damage dmg, kind) [inferred]. */
/* 4:5e8e */
void fn_04_5e8e(int16_t n, int16_t m, int16_t dmg, int16_t kind)
{
    int16_t r;
    int16_t i;
    int16_t cn;
    int16_t cm;
    int16_t k;
    int16_t d;
    int16_t c;
    int16_t u12;
    int16_t ok;

    if (dmg == 90)
        dmg = 50;
    fn_13_2714(n, m, -(dmg / 4 + 4), -8 - dmg, 0, -1);
    if (kind == 1 && m == main_ship
        && !(g_7090[main_ship].f_038 == 1 && g_7090[main_ship].f_032.a == 14 && g_7090[main_ship].f_032.b == n)
        && g_7090[n].f_0c2[m] == 0
        && (dmg < 33 || g_7090[n].f_044[1] == 0 || g_1e68 / 10 - g_7090[n].f_044[1] > 80))
        return;
    if (g_92e8 || g_9320 == 7)
        return;
    if (kind == 1 && VIEWP(char (*)[9], g_7090[n].f_0f6, 1)[m][0] < 9)
        fn_13_2714(n, m, -8, -10 - dmg, 0, 1);
    if (g_7090[n].f_038 == 4) {
        if (g_3824[7][g_96d2[g_7090[n].f_04e].f_38] > -100
            && g_3824[7][g_96d2[g_7090[m].f_04e].f_38] < 100) {
            if (dmg > 10 && rand() % 4 <= 1 && g_7090[n].f_026[0] < 40)
                report_crime(m, 3);
            else
                for (i = 0; i < g_9316; i++)
                    if (g_96d2[g_7090[i].f_04e].f_38 == 7) {
                        fn_03_06ec(m, 14, i, 0x5c);
                        break;
                    }
        }
        fn_13_2714(n, m, -13, -dmg, 0, kind);
        return;
    }
    c = 0;
    cn = g_96d2[g_7090[n].f_04e].f_38;
    cm = g_96d2[g_7090[m].f_04e].f_38;
    if (g_7090[n].f_026[0] < 41 && kind != 1)
        return;
    if (kind == 2 && (cm == cn || g_7090[n].f_052 == 9 || fn_13_2688(n, m) > 100))
        return;
    if (m == n)
        return;
    if (g_7090[n].f_052 >= 2 && g_7090[n].f_052 <= 4 && g_7090[n].f_058 == n
        && g_7090[n].f_054 == 14 && g_7090[n].f_056 == m)
        return;
    if (kind == 2 && fn_13_2688(n, m) > 130)
        return;
    if (cn == 5 || cm == cn)
        c++;
    if (cn == 4)
        c++;
    if (g_7090[n].f_0c2[m] >= 20) {
        g_7090[n].f_0c2[m] = 0;
        return;
    }
    if (g_7090[n].f_032.a == 14 && g_7090[n].f_032.b == m && g_7090[n].f_038 == 1 && cn != 7)
        return;
    if (g_96d2[g_7090[n].f_04e].f_1e / 10 > g_7090[n].f_01e && m == main_ship) {
        fn_03_06ec(m, 14, n, 0xbe);
        if (g_7090[n].f_0c2[m] == 4) {
            dmg *= 2;
            if (g_3824[7][g_96d2[g_7090[n].f_04e].f_38] > -100
                && g_3824[7][g_96d2[g_7090[m].f_04e].f_38] < 100)
                report_crime(m, 3);
        } else
            fn_10_744c(0x3d);
        g_7090[n].f_0c2[m] = 4;
        return;
    }
    if (kind != 1 || VIEWP(char (*)[9], g_7090[n].f_0f6, 1)[m][0] > 8)
        fn_13_2714(n, m, -(dmg / 2 + 7), -10 - dmg, 1, kind);
    if (n == main_ship && (g_9134 == 0 || flow_interactive))
        return;
    d = fn_04_5d9c(n, m);
    if (g_7090[n].f_05e > 1 && (d < 15 || d > 700) && cn != 7)
        return;
    if (d < 30 || d > 300)
        c++;
    if (g_7090[n].f_0c2[m] == 0 && m == main_ship)
        fn_10_754a(0x3d, 0, 0, 0);
    g_7090[n].f_0c2[m]++;
    if (m == main_ship && kind == 1)
        g_9432 += dmg / 2;
    r = fn_13_2688(n, m);
    k = 0;
    if (g_7090[n].f_026[0] - dmg / (g_96d2[g_7090[n].f_04e].f_10) < 65)
        k = 1;
    if (g_7090[n].f_026[0] - dmg / (g_96d2[g_7090[n].f_04e].f_10) < 45)
        k++;
    if (dmg > 24)
        k++;
    if (dmg > 36)
        k++;
    if (dmg == 90) {
        if (g_7090[n].f_05e == 3)
            k += 3;
        else
            k++;
    }
    if (r < -100)
        k++;
    if (r < -210)
        k++;
    if (cn == 7 && g_96d2[g_7090[m].f_04e].f_38 != 7) {
        if (g_7090[n].f_05e > 1) {
            if (g_7090[n].f_0c2[m] < 2) {
                ok = 1;
                for (i = 0; i <= g_9316; i++)
                    if (g_7090[i].f_05e == 1 && g_96d2[g_7090[i].f_04e].f_38 == 7
                        && object_records[14][i].f_18 == 0 && g_7090[i].flag != 0)
                        ok = 0;
                if (ok)
                    fn_03_06ec(m, 14, n, 0x3b);
                g_7090[n].f_052 = 0x15;
                g_7090[n].f_054 = 14;
                g_7090[n].f_056 = m;
                g_7090[n].f_0ed = 1;
                g_7090[n].f_094 = now_ms;
                g_964a++;
                g_9648 += 3;
            } else {
                if (fn_13_adbe(m, 0x15, 0x3c))
                    g_a163 = 5;
                else
                    fn_03_06ec(m, 14, n, 0x43);
                if (m == main_ship && g_a14d[5] - 1 < g_a157[5])
                    g_a14d[5]++;
                g_964a += 3;
                g_9648 += 3;
                g_7090[n].f_052 = 0x14;
                for (i = 0; i <= g_9316; i++)
                    g_7090[n].f_0c2[i] = 0;
            }
        } else if (g_7090[n].f_054 != 14 || g_7090[n].f_056 != m && g_7090[n].f_05e == 1) {
            if (g_7090[n].f_0c2[m] > 2) {
                g_7090[n].f_052 = 0x3e;
                g_7090[n].f_0ed = 2;
                g_7090[n].f_098 = now_ms + 20000;
                g_7090[n].f_054 = 14;
                g_7090[n].f_056 = m;
            } else
                fn_03_06ec(m, 14, n, 0x41);
        }
    } else if (r > 0) {
        if (c - g_7090[n].f_05d + 4 >= g_7090[n].f_0c2[m]) {
            if (dmg != 90) {
                if (g_7090[n].f_0c2[m] > 1)
                    fn_03_06ec(m, 14, n, 0x2a);
                else
                    fn_03_06ec(m, 14, n, 0x29);
                if (c - g_7090[n].f_0c2[m] - g_7090[n].f_05d == -5 && m == main_ship) {
                    fn_03_06ec(m, 14, n, 0x2b);
                    fn_10_754a(0x3e, 0, 0, 0);
                }
            }
        } else {
            if (g_96d2[g_7090[n].f_04e].f_38 == 2)
                for (i = 0; i <= g_9316; i++)
                    if (g_96d2[g_7090[i].f_04e].f_38 == 0 && i != main_ship && g_7090[i].flag
                        && object_records[14][i].f_18 == 0 && g_7090[i].f_026[0] > 40 && i != m)
                        n = i;
            fn_03_00f4(n, 14, m);
            fn_13_915c(n);
        }
    } else {
        if (g_7090[n].f_05e + c + 1 >= g_7090[n].f_0c2[m]) {
            if (dmg != 90) {
                if (g_7090[n].f_0c2[m] > 1)
                    fn_03_06ec(m, 14, n, 0x2e);
                else
                    fn_03_06ec(m, 14, n, 0x2d);
                if (g_7090[n].f_05e - g_7090[n].f_0c2[m] + c == -2 && m == main_ship) {
                    fn_03_06ec(m, 14, n, 0x2f);
                    fn_10_754a(0x3e, 0, 0, 0);
                }
            }
        } else {
            if (g_96d2[g_7090[n].f_04e].f_38 == 2)
                for (i = 0; i <= g_9316; i++)
                    if (g_96d2[g_7090[i].f_04e].f_38 == 0 && i != main_ship && g_7090[i].flag
                        && object_records[14][i].f_18 == 0 && g_7090[i].f_026[0] > 40 && i != m)
                        n = i;
            fn_03_00f4(n, 14, m);
            fn_13_915c(n);
        }
    }
    g_7090[n].f_0c2[m] += k;
}

/* 4:7d36 */
void fn_04_7d36(int16_t a, int16_t b, int16_t c)
{
    int16_t k;
    int16_t i;

    if ((g_7090[a].f_032.a == 14 && g_7090[a].f_032.b == b)
        || (g_7090[b].f_032.a == 14 && g_7090[b].f_032.b == a)) {
        k = 1;
        if (c > 30)
            k = 2;
        g_7090[a].f_13e[b] = g_7090[a].f_13e[b] + k > 6 ? 6 : g_7090[a].f_13e[b] + k;
        g_7090[b].f_13e[a] = g_7090[b].f_13e[a] - k < -6 ? -6 : g_7090[b].f_13e[a] - k;
        if (a == main_ship) {
            g_9680++;
            g_8e00 += c;
        } else if (b == main_ship) {
            g_9682++;
            g_8e04 += c;
        }
    }
    if (c > 0 && a == main_ship) {
        for (i = 3; i >= 0; i--)
            g_7090[b].f_044[i + 1] = g_7090[b].f_044[i];
        g_7090[b].f_044[0] = g_1e68 / 10;
    }
}

/* Updates g_9684 with the player's race standing [inferred]. */
/* 4:8b82 */
void race_position(void)
{
    int16_t i;
    int16_t score;
    int16_t mine;
    int16_t a;

    if (object_records[14][main_ship].f_51 == 0) {
        if (g_7090[main_ship].f_0da < 0)
            a = -g_7090[main_ship].f_0da;
        else
            a = g_7090[main_ship].f_0da;
        mine = a * g_9ea2 + g_7090[main_ship].f_148;
        g_9684 = 1;
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].flag && object_records[14][i].f_18 == 0 && i != main_ship) {
                if (g_7090[i].f_0da < 0)
                    a = -g_7090[i].f_0da;
                else
                    a = g_7090[i].f_0da;
                score = a * g_9ea2 + g_7090[i].f_148;
                if (score > mine)
                    g_9684++;
                if (mine == score && g_8e48[i] < g_8e48[main_ship])
                    g_9684++;
            }
        }
    }
}

/* Checks whether object n may act now (facing test, timers) and then calls fn_04_584c [inferred]. */
/* 4:5654 */
int16_t fn_04_5654(int16_t n)
{
    int16_t u1;
    int16_t u2;
    int16_t r;
    int16_t dir;
    int16_t c;
    int16_t m;
    char pad[18];
    POINT p2;
    POINT p1;
    POINT p3;
    int16_t u3;

    if (g_7090[n].f_018 == 0)
        return 0;
    if (g_7090[n].f_032.a == 14 && g_2f4c[g_7090[n].f_018].f_4a && g_7090[g_7090[n].f_032.b].f_0e2)
        fn_04_6e70(n);
    if (g_7090[n].f_05f != 3) {
        if (object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_1a)
            p1 = object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_00;
        else
            p1 = fn_08_29ea(object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_04);
        if (object_records[14][n].f_1a)
            p2 = object_records[14][n].f_00;
        else
            p2 = fn_08_29ea(object_records[14][n].f_04);
        dir = fn_08_19b0(p1.x - p2.x, p1.y - p2.y);
        c = object_records[14][n].f_28;
        m = (int16_t)(c + 8) % 16;
        if (c == dir)
            r = 1;
        else if (m == dir)
            r = 2;
        if (g_7090[n].f_05f != r)
            return 0;
    }
    if (g_7090[n].f_0e8 || g_7090[n].f_010 > 0) {
        if (g_8e28 + 3000 > now_ms) {
            if (object_records[14][n].f_2e == -2 && fn_11_4c72(n) && n == main_ship)
                fn_03_332e(0x409, 0x416);
            if (g_7090[n].f_010 == 7 && fn_11_4b00(n) && n == main_ship)
                fn_03_332e(0x408, 0x416);
            return 0;
        }
    }
    fn_04_584c(g_7090[n].f_018, n, 0x19);
    return 1;
}

/* Picks a new goal (f06/f08) for racer n [inferred]. */
/* 4:4d00 */
void fn_04_4d00(int16_t n)
{
    int16_t d;
    int16_t i;
    int16_t j;
    int16_t a;
    int16_t b;
    int16_t best;
    int16_t sel;
    int16_t count;

    if (g_7090[n].f_006 == 12 && g_7090[n].f_036 == 2)
        return;
    if (g_92e8)
        return;
    if (g_9406[2]) {
        if (g_96d2[g_7090[n].f_04e].f_38 != 7 && g_9208 >= 2) {
            if (g_7090[n].f_052 == 0 || g_7090[n].f_052 == 7) {
                best = 20000;
                sel = -1;
                count = 0;
                for (i = 0; i < g_9406[2]; i++) {
                    if (object_records[2][i].f_18 == 0 && g_52ec[i].f_1c.a == 14 && g_52ec[i].f_1c.b == n
                        && g_52ec[i].f_12 == 15) {
                        count++;
                        d = fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[2][i].f_04);
                        if (d < best)
                            sel = i;
                    }
                }
                if (count > 1 || best < 180) {
                    g_7090[n].f_006 = 2;
                    g_7090[n].f_008 = sel;
                    g_7090[n].f_036 = 1;
                    fn_04_8346(n, g_7090[n].f_03a = 2, sel, 6);
                }
            }
        }
    }
    if (g_96d2[g_7090[n].f_04e].f_1e / 10 > g_7090[n].f_01e) {
        if (g_7090[n].f_01e != 0 && rand() % g_7090[n].f_01e > 150)
            return;
        best = 20000;
        sel = -1;
        for (j = 0; j < g_9406[4]; j++) {
            if (object_records[4][j].f_18 == 0) {
                d = fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[4][j].f_04);
                if (d < best) {
                    best = d;
                    sel = j;
                }
            }
        }
        if (sel >= 0) {
            g_7090[n].f_006 = 4;
            g_7090[n].f_008 = sel;
            g_7090[n].f_036 = 2;
            g_7090[n].f_094 = now_ms + 4000;
            g_7090[n].f_03a = 2;
            g_7090[n].f_052 = 0;
            return;
        }
        if (g_7090[n].f_0ce + g_7090[n].f_0dc >= 200) {
            if (fn_16_0b4e(n)) {
                g_7090[n].f_006 = 7;
                g_7090[n].f_008 = 0;
                g_7090[n].f_036 = 3;
                g_7090[n].f_03a = 2;
            }
        } else if (g_9320 != 7) {
            fn_03_06ec(main_ship, 14, n, 0xb7);
            g_7090[n].f_006 = 12;
            g_7090[n].f_008 = 0;
            g_7090[n].f_03a = g_7090[n].f_036 = 2;
        }
    }
    if (object_records[14][n].f_32 == 14 && g_7090[n].f_036 != 4
        && !(g_7090[n].f_006 == 14 && object_records[14][n].f_34 == g_7090[n].f_008)) {
        g_7090[n].f_006 = 14;
        g_7090[n].f_008 = object_records[14][n].f_34;
        g_7090[n].f_03a = 2;
        g_7090[n].f_036 = 1;
        g_7090[n].f_052 = 0;
    }
}

/* Racers that reach the goal object of n react: messages and new goals [inferred]. */
/* 4:6700 */
void fn_04_6700(int16_t n)
{
    int16_t i;
    int16_t k;
    int16_t a;
    int16_t b;
    int16_t type;
    int16_t idx;
    int16_t done;
    char buf[40];

    type = g_7090[n].f_006;
    idx = g_7090[n].f_008;
    if (object_records[type][idx].f_18 != 0)
        return;
    done = 0;
    for (i = 0; i <= g_9316; i++) {
        if (object_records[14][i].f_18 == 0 && g_7090[i].flag && g_7090[i].f_052 != 14
            && g_7090[i].f_032.a == type && g_9320 != 6 && i != n && g_7090[i].f_032.b == idx
            && object_records[type][idx].f_53 != 0
            && !(g_7090[i].f_148 == type && g_7090[i].f_149 == idx)) {
            if (g_96d2[g_7090[i].f_04e].f_38 == 7)
                fn_03_06ec(i, 14, n, 0xbf);
            else
                fn_03_06ec(i, 14, n, 0x66);
            g_7090[i].f_148 = type;
            g_7090[i].f_149 = idx;
        }
        k = g_96d2[g_7090[i].f_04e].f_38;
        if (g_7090[i].f_052 != 14 && !done
            && (k == 2 || k == 5) && object_records[14][i].f_18 == 0 && g_7090[i].flag && i != n
            && !(i == main_ship && flow_interactive)
            && !(g_7090[i].f_052 == 2 && k != 2)
            && (fn_13_2688(i, n) < 160 || g_7090[i].f_0c2[n] > 0)) {
            if (g_96d2[g_7090[n].f_04e].f_38 != k
                && !(g_7090[i].f_032.a == type && g_7090[i].f_032.b == idx)
                && !(k == 2 && g_96d2[g_7090[n].f_04e].f_38 == 0)) {
                g_7090[i].f_006 = g_7090[i].f_032.a = type;
                g_7090[i].f_008 = g_7090[i].f_032.b = idx;
                if (fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[14][i].f_04) < 1900) {
                    g_7090[i].f_038 = 2;
                    g_7090[i].f_036 = 2;
                    fn_03_06ec(n, 14, i, 0x17);
                } else
                    g_7090[i].f_036 = g_7090[i].f_038 = 3;
                g_7090[i].f_03a = g_7090[i].f_03c = 2;
                g_7090[i].f_054 = g_7090[i].f_052 = 14;
                g_7090[i].f_056 = n;
                g_7090[i].f_094 = now_ms + 500;
                if (i == main_ship) {
                    LoadString(lang_module, 0x585, buf, 40);
                    lstrcpy(g_8630, buf);
                    fn_03_1542(0, g_7090[i].f_006, g_7090[i].f_008, buf, 0);
                    lstrcat(g_8630, buf);
                    LoadString(lang_module, 0x586, buf, 40);
                    lstrcat(g_8630, buf);
                    fn_03_1542(0, 14, n, buf, 0);
                    lstrcat(g_8630, buf);
                    lstrcat(g_8630, ".");
                    g_058c = 1;
                    g_05c0 = now_ms + 1200;
                }
                done = 1;
            }
            if (g_7090[i].f_032.a == type && g_7090[i].f_032.b == idx)
                done = 1;
        }
    }
}

/* Racer n chooses whom to attack (f06/f08), with messages to the player [inferred]. */
/* 4:7636 */
void fn_04_7636(int16_t n, int16_t type, int16_t idx, int16_t quiet)
{
    int16_t k;
    int16_t i;
    int16_t v;
    int16_t sel;
    int16_t best;
    int16_t found;

    found = 0;
    g_2384 = now_ms + 5000;
    k = g_96d2[g_7090[n].f_04e].f_38;
    if (type == 14 && g_96d2[g_7090[idx].f_04e].f_38 == 7) {
        g_7090[n].f_006 = type;
        g_7090[n].f_008 = idx;
        return;
    }
    if (g_7090[n].f_032.a == 14 && VIEWP(char (*)[9], g_7090[n].f_0f6, 1)[g_7090[n].f_032.b][0] > 3) {
        type = 14;
        idx = g_7090[n].f_032.b;
    }
    best = 7;
    sel = -1;
    for (i = 0; i <= g_9316; i++) {
        if (i != n) {
            v = VIEWP(char (*)[9], g_7090[n].f_0f6, 1)[i][0];
            if (type == 14 && i == idx) {
                v += 5;
                if (v > 12)
                    v += 100;
            }
            if (v > best) {
                best = v;
                sel = i;
            }
        }
    }
    if (sel != -1) {
        type = 14;
        idx = sel;
    }
    if (type == 14) {
        g_7090[n].f_006 = type;
        g_7090[n].f_008 = idx;
        if (idx == main_ship)
            g_6b40[g_96d2[g_7090[n].f_04e].f_38]++;
        if (k == 7) {
            if (g_7090[n].f_05e > 0) {
                g_9346 = g_7090[idx].f_0d6;
                if (idx == main_ship) {
                    g_a14d[0]++;
                    g_a147 = g_1e68;
                    g_a14b = g_91f8;
                }
            } else {
                for (i = 0; i <= 9; i++)
                    g_a157[i] = g_a14d[i];
            }
        }
        if (g_7090[n].f_0ee[idx] <= 5 && g_7090[n].f_038 != 4)
            type = 0;
        else if (g_96d2[g_7090[n].f_04e].f_38 == 3 && g_7090[n].f_0cd == idx)
            type = 0;
        else if (g_9320 == 7)
            type = 0;
        else {
            for (i = 0; i < 3; i++) {
                if (g_4eec[k][i] == -1) {
                    g_4eec[k][i] = g_7090[idx].f_0d6;
                    g_4fd0[k][i] = g_91f8;
                    if (g_7090[n].f_0d6 != -1)
                        g_6b10[k][i] = g_6e24[g_7090[n].f_0d6].f_00;
                    else
                        g_6b10[k][i] = g_4ed8[g_7090[n].f_05e];
                    found = 1;
                    break;
                }
            }
            if (!found) {
                g_4eec[k][0] = g_7090[idx].f_0d6;
                g_4fd0[k][i] = g_91f8;
                if (g_7090[n].f_0d6 != -1)
                    g_6b10[k][i] = g_6e24[g_7090[n].f_0d6].f_00;
                else
                    g_6b10[k][i] = g_4ed8[g_7090[n].f_05e];
            }
        }
        if (n == main_ship)
            return;
        if (idx == n)
            fn_03_06ec(main_ship, 14, n, 0x89);
        else if (idx == main_ship) {
            if (g_96d2[g_7090[n].f_04e].f_38 == g_96d2[g_7090[main_ship].f_04e].f_38 && !quiet)
                fn_03_06ec(main_ship, 14, n, 0x63);
            else if (!quiet)
                fn_03_06ec(main_ship, 14, n, 0x5f);
        } else if (g_96d2[g_7090[n].f_04e].f_38 == g_96d2[g_7090[main_ship].f_04e].f_38) {
            g_7090[n].f_006 = 14;
            g_7090[n].f_008 = idx;
            if (!quiet)
                fn_03_06ec(main_ship, 14, n, 0x60);
        } else {
            g_7090[n].f_006 = 14;
            g_7090[n].f_008 = idx;
            if (!quiet)
                fn_03_06ec(main_ship, 14, n, 0x61);
        }
    } else {
        if (n == main_ship)
            return;
        g_7090[n].f_006 = type;
        g_7090[n].f_008 = idx;
        fn_03_06ec(main_ship, 14, n, 0x62);
    }
}

/* Racer n may shout a taunt/warning message (0x406-0x415) [inferred]. */
/* 4:79ae */
void fn_04_79ae(int16_t n)
{
    int16_t i;
    int16_t sel;
    int16_t a;
    int16_t b;
    int16_t msg;
    int16_t msg2;
    int16_t flag;

    if (g_7090[n].f_0e7 == 0 && g_7090[n].f_0e9 == 0)
        return;
    msg = 0;
    if (g_7090[n].f_0e9 && (g_7090[n].f_0ac == 0 || g_7090[n].f_0ac == 0))  /* sic: same test twice */
        return;
    if (g_7090[n].f_0e7 && g_7090[n].f_01e < 100)
        return;
    if (g_7090[n].f_010 != 0 || g_7090[n].f_0e8 != 0)
        flag = 0;
    else
        flag = 1;
    sel = -1;
    for (i = 0; i <= g_9316; i++) {
        if (object_records[14][i].f_18 == 0 && i != n && g_7090[i].f_032.a == 14 && g_7090[i].f_032.b == n
            && g_7090[i].f_038 == 1
            && fn_08_285a(&a, &b, object_records[14][i].f_04, object_records[14][n].f_04) < 500)
            sel = i;
    }
    if (!flag && g_7090[n].f_038 == 2
        && fn_08_285a(&a, &b, object_records[14][n].f_04,
                      object_records[g_7090[n].f_032.a][g_7090[n].f_032.b].f_04) < 150) {
        if (g_7090[n].f_0e9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x410;
    }
    if (flag && sel == -1 && g_96d2[g_7090[n].f_04e].f_38 != 3)
        return;
    if (!flag && sel == -1 && rand() % 3 == 0 && g_96d2[g_7090[n].f_04e].f_38 != 3) {
        if (g_7090[n].f_0e9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x411;
    } else if (flag && sel != -1 && (rand() % 5 == 0 || g_7090[n].f_13e[sel] < -1)
               && g_7090[n].f_13e[sel] < 2) {
        if (g_7090[n].f_0e9) {
            if (fn_11_4b00(n))
                msg = 0x406;
        } else {
            if (fn_11_4c72(n))
                msg = 0x407;
        }
        msg2 = 0x412;
    } else if (flag && g_96d2[g_7090[n].f_04e].f_38 == 3 && sel == -1 && g_7090[n].f_038 == 1
               && g_7090[n].f_032.a == 14 && rand() % 4 <= 2 && g_7090[n].f_13e[sel] < 2) {
        if (g_7090[n].f_0e9) {
            if (fn_11_4b00(n))
                msg = 0x406;
        } else {
            if (fn_11_4c72(n))
                msg = 0x407;
        }
        msg2 = 0x413;
    } else if (!flag && sel == -1 && g_7090[n].f_038 != 1) {
        if (g_7090[n].f_0e9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x414;
    } else if (!flag && g_7090[n].f_13e[sel] > 2) {
        if (g_7090[n].f_0e9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x415;
    }
    if (n == main_ship && msg)
        fn_03_332e(msg, msg2);
}

/* Scores object (type, idx) as a goal for the player's racer; sets
 * g_9686 / g_9688 / g_968a as hints for the chosen approach [inferred].
 * flag is unused. */
/* 4:8626 */
int16_t fn_04_8626(int16_t type, int16_t idx, int16_t flag)
{
    int16_t unused;
    int16_t v;
    int16_t k;
    int16_t dx;
    int16_t dy;
    int16_t dist;
    int16_t heading;
    int16_t ang;
    int16_t rel;
    int16_t c16;
    int16_t c18;
    int16_t c1a;
    int16_t i;
    int32_t speed;
    int32_t cosv;
    int32_t appr;
    int32_t vx;
    int32_t vy;
    int32_t closing;
    int16_t near_;

    k = 10;
    g_968a = v = 0;
    near_ = g_9686 = g_8e28 + 2000 > now_ms;
    if (g_7090[main_ship].f_038 == 1 && g_8e28 + 3000 > now_ms
        && g_7090[main_ship].f_032.a == type && g_7090[main_ship].f_032.b == idx)
        near_ = g_9686 = 1;
    v = g_9688 = 0;
    if (type == 14 || object_records[type][idx].f_53 != 0)
        v = 30;
    else if (type == 9 || (type == 8 && g_3d50[idx].f_1c == 2)
             || (type == 2 && g_52ec[idx].f_12 == 15))
        v = 20;
    else if (type == 5)
        v = -200;
    if (v != 0 && near_ != 0)
        v += 25;
    dist = fn_08_285a(&dx, &dy, object_records[type][idx].f_04, object_records[14][main_ship].f_04);
    heading = object_records[14][main_ship].f_28;
    ang = fn_08_19b0(-dx, -dy);
    rel = (int16_t)((heading - ang) * 360) / 16;
    cosv = fn_06_720c(rel);
    vx = object_records[14][main_ship].f_0c;
    vy = object_records[14][main_ship].f_0e;
    speed = fn_08_35d0(vx, vy);
    closing = -((dx * vx + dy * vy) / dist);
    appr = closing * 128 / speed;
    c16 = c18 = c1a = 0;
    if (type == 14) {
        for (i = 0; i < 5; i++) {
            if (g_7090[idx].f_044[i] != 0) {
                c1a++;
                if (g_1e68 / 10 - g_7090[idx].f_044[i] < 36)
                    c16++;
                if (g_1e68 / 10 - g_7090[idx].f_044[i] < 300)
                    c18++;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            if (g_938a[i] == type && (g_9392[i] == idx || type == 3) && g_937a[i] != 0) {
                c1a++;
                if (g_1e68 / 10 - g_937a[i] < 36)
                    c16++;
                if (g_1e68 / 10 - g_937a[i] < 300)
                    c18++;
            }
        }
    }
    if (near_) {
        v += (int16_t)(((c18 - 3) * 2 + c1a) * 4) + cosv / 2 + appr / 8 + (int16_t)(c16 * 11);
        if (c1a == 0)
            v -= 30;
        if (c1a == 1)
            v -= 15;
        if (c18 == 0)
            v -= 15;
    } else {
        v += (int16_t)(appr / 3 + cosv / 5) + c18 * 2 + c16 * 3 + c1a;
        if (type == 12 && appr > 75 && cosv > 75)
            v += (int16_t)(appr / 3 + cosv / 5) + 10;
        if (appr > 105 || cosv > 105 || (appr > 80 && cosv > 80)
            || (appr > 55 && cosv > 55 && object_records[type][idx].f_53 == 1)) {
            if (dist < 360) {
                g_9688 = 1;
                if (object_records[type][idx].f_53 == 1)
                    v += (int16_t)(appr / 3 + cosv / 5);
            }
        }
    }
    if (appr < -60 && cosv < -70 && closing < -30 && type == 14
        && g_7090[idx].f_032.a == 14 && g_7090[idx].f_032.b == main_ship
        && (g_7090[idx].f_038 == 1
            || (g_7090[idx].f_052 >= 2 && g_7090[idx].f_052 <= 4
                && g_7090[idx].f_054 == 14 && g_7090[idx].f_056 == main_ship))) {
        g_968a = 1;
        near_ = 0;
        v += 25 - closing;
    }
    v += type == 12 ? dist / -7 + 55 : dist / -10 + 40;
    if (g_7090[main_ship].f_006 == type && g_7090[main_ship].f_008 == idx && v > 0)
        k = 12;
    if (g_7090[main_ship].f_052 >= 2 && g_7090[main_ship].f_052 <= 4
        && g_7090[main_ship].f_054 == type && g_7090[main_ship].f_056 == idx)
        v += 15;
    if (type == g_6e38[0].f_1a.b && idx == g_6e38[0].f_1a.a)
        v += 30;
    v = (int16_t)(k * v) / 10;
    return v;
}

/* Chooses the player's autopilot goal (f06/f08/f36) [inferred]; pt and j
 * are dead stores kept for the code shape. */
/* 4:59bc */
int16_t fn_04_59bc(void)
{
    int16_t v;
    int16_t i;
    POINT pt;
    int16_t j;
    char pad1[28];
    int16_t best;
    int16_t flag;
    int16_t s9686;
    int16_t s968a;
    int16_t s9688;
    char pad2[166];
    int16_t type;
    int16_t idx;
    char pad3[88];
    int32_t dt1;
    int32_t dt2;
    int32_t dt3;
    int16_t btype;
    int16_t bidx;

    dt1 = now_ms - g_52d8;
    dt2 = now_ms - g_8e44;
    dt3 = now_ms - g_8e28;
    flag = 1;
    if (g_7090[main_ship].f_052 == 1) {
        for (i = 0; i <= g_9316; i++)
            if (g_7090[i].f_032.a == g_7090[main_ship].f_054 && g_7090[i].f_032.b == g_7090[main_ship].f_056)
                flag = 0;
    }
    fn_04_84de();
    if (g_7090[main_ship].f_052 >= 2 && g_7090[main_ship].f_052 <= 4) {
        flag = 0;
        if (g_7090[main_ship].f_006 == g_7090[main_ship].f_054
            && (g_7090[main_ship].f_008 == g_7090[main_ship].f_056
                || (g_7090[main_ship].f_006 == 9 && rand() % 5 == 1))
            && g_7090[main_ship].f_036 == 1) {
            g_7090[main_ship].f_052++;
            if (g_7090[main_ship].f_054 == 14
                && g_1e68 / 10 - g_7090[g_7090[main_ship].f_056].f_044[2] < 40)
                g_7090[main_ship].f_052 = 4;
            if (g_7090[main_ship].f_052 >= 4) {
                if (g_7090[main_ship].f_058 != main_ship)
                    fn_13_7b40(g_7090[main_ship].f_058);
                else {
                    type = g_7090[main_ship].f_054;
                    idx = g_7090[main_ship].f_056;
                    if (type == 14 && g_7090[idx].f_052 == 2 && g_7090[idx].f_056 == main_ship
                        && g_7090[idx].f_058 == idx)
                        fn_03_06ec(main_ship, type, idx, 0x1f);
                }
                g_7090[main_ship].f_052 = 0;
            }
        }
    }
    if (g_7090[main_ship].f_052 != 0) {
        if ((g_7090[main_ship].f_098 + 20000 < now_ms
             && g_1e68 / 10 - g_7090[g_7090[main_ship].f_056].f_044[0] > 25) || flag)
            g_7090[main_ship].f_052 = -1;
    }
    if (g_7090[main_ship].f_052 == -1)
        g_7090[main_ship].f_052 = 0;
    pt = object_records[14][main_ship].f_04;
    best = -40;
    j = 0;
    for (i = 0; i < g_9146; i++) {
        if (g_507c[i] == 14 && g_50e0[i] == main_ship)
            continue;
        v = fn_04_8626(g_507c[i], g_50e0[i], 1);
        if (v > best) {
            best = v;
            btype = g_507c[i];
            bidx = g_50e0[i];
            s9686 = g_9686;
            s968a = g_968a;
            s9688 = g_9688;
        }
    }
    for (i = 0; i < g_9318; i++) {
        v = fn_04_8626(12, i * 2 + 1, 1);
        if (v > best) {
            best = v;
            btype = 12;
            bidx = i * 2 + 1;
            s9686 = g_9686;
            s968a = g_968a;
            s9688 = g_9688;
        }
    }
    g_9686 = s9686;
    if (best > 0 || (s9686 == 0 && best > -40)) {
        g_7090[main_ship].f_006 = btype;
        g_7090[main_ship].f_008 = bidx;
        g_7090[main_ship].f_03a = 2;
        if (g_9686 == 0 && btype == 14
            && ((g_7090[bidx].f_044[1] != 0 && g_1e68 / 36 - g_7090[bidx].f_044[1] < 10)
                || g_7090[bidx].f_0c2[main_ship] > 2))
            g_9686 = 1;
        if (g_9686)
            g_7090[main_ship].f_036 = 1;
        else if ((object_records[btype][bidx].f_53 || btype == 12) && s9688)
            g_7090[main_ship].f_036 = 2;
        else if (s968a) {
            g_7090[main_ship].f_036 = 4;
            g_7090[main_ship].f_03a = 5;
        } else
            g_7090[main_ship].f_036 = 3;
        return best;
    }
    g_7090[main_ship].f_03a = 0;
    g_7090[main_ship].f_006 = 8;
    g_7090[main_ship].f_008 = 0;
    g_7090[main_ship].f_036 = 3;
    g_7090[main_ship].f_03a = 2;
    return 0;
}

/* Racer n looks for a rival j to gang up on (f52 = 1, f54 = 14, f56 = j)
 * [inferred]. */
/* 4:485c */
void fn_04_485c(int16_t n, int16_t unused)
{
    int16_t j;
    int16_t i;
    int16_t thr;
    int16_t d;
    int16_t a;
    int16_t b;
    int16_t c1;
    int16_t sel;
    int16_t c2;
    int16_t skip;
    int16_t score;

    sel = -1;
    if (g_96d2[g_7090[n].f_04e].f_38 == 7)
        return;
    if (g_96d2[g_7090[n].f_04e].f_38 == 6)
        return;
    for (j = 0; j <= g_9316; j++) {
        if (object_records[14][j].f_18 == 0 && j != n && g_7090[j].flag) {
        for (i = skip = 0; i <= g_9316; i++) {
            if ((g_7090[i].f_052 == 5 || g_7090[i].f_052 == 1) && g_7090[i].f_056 == j) {
                skip = 1;
                break;
            }
        }
        if (g_96d2[g_7090[n].f_04e].f_38 == 3 && g_96d2[g_7090[j].f_04e].f_38 != 3)
            skip = 1;
        if (g_7090[n].f_0c2[j] > 0)
            skip = 1;
        if (g_7090[n].f_0ee[j] > 0 && g_7090[n].f_0ee[j] <= 5)
            skip = 1;
        if (g_7090[j].f_032.a == 14 && g_7090[j].f_032.b == n && g_7090[j].f_038 == 1)
            skip = 1;
        for (i = 1; i <= 5; i++)
            if (VIEWP(char (*)[9], g_7090[n].f_0f6, 1)[j][i - 1] > 5)
                skip = 1;
        if (!skip) {
            thr = 10;
            score = 0;
            if (g_7090[j].f_026[0] < 50)
                score = 1;
            if (g_7090[j].f_038 == 4)
                score++;
            for (i = c2 = c1 = 0; i <= g_9316; i++) {
                if (object_records[14][i].f_18 == 0 && i != n && i != j && g_7090[i].flag
                    && g_7090[i].f_032.a == 14 && g_7090[i].f_032.b == j && g_7090[i].f_038 == 1) {
                    thr += fn_13_2688(n, i) / 45;
                    if (fn_04_5d9c(j, i) < (int16_t)(++c1 * 40))
                        sel = j;
                }
                if (fn_13_2688(i, j) < -50 && i != j && g_7090[i].flag)
                    c2++;
            }
            if (sel != -1)
                score++;
            if (c1 > 1)
                score++;
            if (c1 != 0)
                score++;
            if (g_7090[n].f_05e + g_7090[n].f_05d < 3)
                score++;
            if (score > 1) {
                d = fn_08_285a(&a, &b, object_records[14][n].f_04, object_records[14][j].f_04);
                if (d < 1000)
                    thr -= 10;
                if (g_96d2[g_7090[j].f_04e].f_38 == g_96d2[g_7090[n].f_04e].f_38
                    || g_96d2[g_7090[n].f_04e].f_38 == 4)
                    thr -= 15;
                thr += g_7090[n].f_05d * 4;
                if (fn_13_2688(n, j) >= (int16_t)(thr * 10)) {
                    for (i = 0; i < g_9406[2]; i++)
                        if (g_52ec[i].f_12 == 15 && g_52ec[i].f_1c.a == 14 && g_52ec[i].f_1c.b == j)
                            c1++;
                    if ((int16_t)(c2 + c1) > 0) {
                        if (c1 > 2)
                            sel = j;
                        if (g_7090[j].f_026[1] < c1 * 9 + 14 || g_7090[j].f_026[2] < c1 * 9 + 14)
                            sel = j;
                        if (c2 * 4 + c1 * 10 + 21 > g_7090[j].f_026[0])
                            sel = j;
                        if (fn_13_2688(n, j) >= (int16_t)(((thr += 15) - c1 * 6) * 10) && c1) {
                            if (g_7090[j].f_05e > 0 && g_7090[j].f_05d < 3) {
                                if (c1 > 1)
                                    sel = j;
                                if (g_7090[j].f_026[1] < 30 || g_7090[j].f_026[2] < 30)
                                    sel = j;
                                if ((g_7090[j].f_026[0] < 45 || fn_13_2688(n, j) > (int16_t)((thr + 12) * 10))
                                    && j == main_ship)
                                    sel = j;
                            }
                        } else if (c2 > 2 && g_7090[j].f_026[0] < 35
                                   && fn_13_2688(n, j) > (int16_t)((thr + 10) * 10))
                            sel = j;
                    }
                }
                if (sel >= 0 && fn_13_78b8(n, j) >= -1) {
                    g_7090[n].f_0ed = 1;
                    g_7090[n].f_052 = 1;
                    g_7090[n].f_054 = 14;
                    g_7090[n].f_056 = j;
                    g_7090[n].f_058 = n;
                    g_7090[n].f_098 = now_ms + 18000;
                    g_7090[n].f_094 = now_ms + 300;
                    return;
                }
            }
        }
        }
    }
}
