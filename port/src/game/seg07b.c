/* INSPACE.EXE segment 7 (selector 1030), first source file: 7:0000-7:2206
 * (files.tsv group 13). */
#include "game.h"

static unsigned char dissolve_map[4][0x800];

/* Main per-tick dispatcher on the game state g_90f4 [inferred].
 * Remaining difference: the original places the flow_interactive arm of
 * the g_1e80 timer test (9134 clamp, g_1e84 = g_1e50 / fn_09_6bc2) after
 * the g_1e84 block instead of right after the other arm; no source form
 * tried (if/else, gotos, if (0) blocks, while/break) reproduces it.
 * The `goto ret` exits of cases 6, 8, 9 and of case 0's last call are
 * layout-only: they make CL keep case 0's `pop bx; jmp` tail as the
 * shared copy, as the original does. */
/* near-match 48%: 7:0000 (one block placed differently, same instructions) */
void fn_07_0000(void)
{
    int16_t i;
    int16_t j;
    int16_t r;
    int16_t skip;
    char buf[34];
    int16_t res;
    char text[144];
    char title[30];

    if (g_001a) {
    ret:                        /* layout-only, see above */
        return;
    }
    g_0022 = 1;
    now_ms = GetCurrentTime();
    if (now_ms > g_1e54 && !g_9132) {
        res = GetFreeSystemResources(GFSR_GDIRESOURCES);
        if (res <= 10 && g_058e) {
            format_string(text, 0xbe3, 1, res);
            format_string(title, 0x9ed, 1);
            MessageBox(main_window, text, title, MB_ICONEXCLAMATION);
            g_058e = 0;
        } else if (res > 40)
            g_058e = 1;
        g_1e54 += 5000;
    }
    if (g_912e)
        g_2214 = timeGetTime();
    if (g_965e && !g_913a)
        fn_16_619e();
    if (g_8f6c) {
        g_13de = 1;
        g_8f6c = 0;
        g_968e = 0;
        g_1e84 = 0;
        g_1e80 = 0;
        fn_09_0d6c();
    }
    switch (g_90f4) {
    case 6:
        g_0022 = 0;
        if (g_8e62)
            fn_11_785e(g_8e62, g_8e64, g_1d38);
        skip = 0;
        if (g_952c && g_9530 == 1 && g_912e) {
            if (g_2218 + frame_ms < g_2214)
                g_9144 = g_9004;
            else if (g_2218 + frame_min_ms > g_2214)
                skip = 1;
        }
        g_9144++;
        if (skip)
            goto ret;
        if (g_9144 < g_9004)
            goto ret;
        fn_07_2206();
        g_2218 = g_2214;
        g_9144 = 0;
        fn_16_0cfe(0);
        goto ret;
    case 8:
        g_0022 = 0;
        g_9144++;
        if (g_9144 < g_9004)
            goto ret;
        fn_07_2206();
        g_9144 = 0;
        fn_16_6928(0);
        goto ret;
    case 9:
        g_0022 = 0;
        if (g_1e84 && g_1e84 <= now_ms) {
            g_1e84 = 0;
            fn_06_5d58();
            goto ret;
        }
        g_9144++;
        if (g_9144 < g_9004)
            goto ret;
        fn_07_2206();
        g_9144 = 0;
        fn_16_7210();
        goto ret;
    case 0:
        if (g_9294)
            g_0022 = 0;
        if (g_8e62)
            fn_11_7902(g_8e62, g_8e64, g_1d38);
        if (g_0d1e && g_9134 && !flow_interactive) {
            fn_06_1e68(0);
            return;
        }
        skip = 0;
        if (g_912e && g_1212) {
            if (g_2218 + 14 < g_2214)
                g_9144 = g_9004;
            else if (g_2218 + 13 > g_2214)
                skip = 1;
        }
        g_9144++;
        if (skip)
            return;
        if (g_9144 < g_9004)
            return;
        if (g_1212)
            fn_07_2206();
        g_2218 = g_2214;
        g_9144 = 0;
        fn_15_5962(0);
        goto ret;
    case 3:
        if (g_05ac && g_05ac <= now_ms) {
            g_05ac = 0;
            fn_09_60bc();
            fn_13_4eca("iMainSmart = ");
            fn_06_0f1a(main_ship, buf);
            fn_13_4eca(buf);
            fn_13_4eca("\n\r");
            return;
        }
        if (g_8e62)
            fn_11_7bbc(g_8e62, g_8e64, g_1d38);
        g_9144++;
        if (g_9144 < g_9004)
            return;
        fn_07_2206();
        g_9144 = 0;
        fn_17_0000(0, 0);
        return;
    case 2:
        if (g_0d1e && !flow_interactive) {
            fn_06_1e68(0);
            return;
        }
        if (g_1e70 && g_1e70 <= now_ms) {
            g_1e70 = 0;
            fn_09_5cca();
            return;
        }
        if (g_1e74 && g_1e74 <= now_ms) {
            fn_06_1c72(1);
            return;
        }
        if (g_8e62)
            fn_11_7b7a(g_8e62, g_8e64, g_1d38);
        g_9144++;
        if (g_9144 < g_9004)
            return;
        fn_07_2206();
        g_9144 = 0;
        fn_09_6dec(0);
        return;
    case 4:
        if (g_1e78 <= now_ms) {
            g_13de = 1;
            g_968e = 0;
            return;
        }
        if (g_8e62)
            fn_11_78bc(g_8e62, g_8e64, g_1d38);
        return;
    case 5:
        if (g_1e7c <= now_ms) {
            fn_09_0d6c();
            fn_06_626c();
            g_001a = 0;
            g_13de = 1;
            g_968e = 4;
            return;
        }
        if (g_8e62)
            fn_11_7b30(g_8e62, g_8e64, g_1d38);
        g_9144++;
        if (g_9144 < g_9002)
            return;
        g_9144 = 0;
        fn_06_5f7a(0);
        return;
    }
    fn_13_4eca("Frame iMainSmart = ");
    fn_06_0f1a(main_ship, buf);
    fn_13_4eca(buf);
    fn_13_4eca("\n\r");
    if (g_8e60) {
        SelectClipRgn(main_dc, g_0012);
        if (g_8e62)
            fn_11_6aa8(g_8e62, g_8e64, g_1d38);
        g_8e60 = 0;
        return;
    }
    fn_13_4eca("Before Timer iMainSmart = ");
    fn_06_0f1a(main_ship, buf);
    fn_13_4eca(buf);
    fn_13_4eca("\n\r");
    skip = 0;
    if (g_912e) {
        if (g_2218 + frame_ms < g_2214)
            g_9144 = g_8f76;
        else if (g_2218 + frame_min_ms > g_2214)
            skip = 1;
    }
    g_9144++;
    if (!subgame_active) {
        fn_13_4eca("AMB? iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
        if (g_1e88 && g_1e88 <= now_ms) {
            g_1e88 = 0;
            if (main_ship == g_952e && !g_951a) {
                g_90f4 = 6;
                g_914a = 0;
                fn_16_0cfe(1);
                return;
            }
            fn_16_32a0();
        }
        if (g_1e80 && g_1e80 <= now_ms) {
            if (!flow_interactive) {
                if (g_69f4[g_94a2].f_1d0 == 2 && g_0d26)
                    fn_06_92b8();
                if (g_93a4) {
                    g_90f4 = 8;
                    g_929c = 0;
                    fn_16_6928(1);
                    return;
                }
                fn_09_2828();
                if (g_7090[main_ship].flag && !g_9516)
                    fn_06_885c(0, 0);
                fn_09_0d6c();
                g_13de = 1;
                g_968e = 0;
            } else {
                if (g_9134 > 1)
                    g_9134 = 1;
                if (g_7090[main_ship].flag)
                    fn_09_6bc2();
                else
                    g_1e84 = now_ms;
            }
            g_1e80 = 0;
            return;
        }
        if (g_1e84 && g_1e84 <= now_ms) {
            if (!g_920c)
                fn_16_68d6(main_window, 0x918, 0x919);
            g_1e84 = 0;
            fn_06_5d58();
            return;
        }
        if (g_05b4 && !flow_interactive && g_05b4 <= now_ms && g_9320 != 7) {
            g_7090[main_ship].f_052 = 10;
            g_7090[main_ship].f_0ed = 1;
        }
        if (g_05b0 && g_05b0 <= now_ms) {
            g_05b0 = 0;
            fn_09_0d6c();
            return;
        }
        fn_13_4eca("Change Clip? iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
        if (g_1038)
            fn_02_0ba4();
        fn_13_4eca("Change Persp? iMainSmart = ");
        fn_06_0f1a(main_ship, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
        if (g_1032)
            fn_11_aece();
        if (g_058c && !g_951a && g_05bc < now_ms)
            fn_07_1f38();
        if (g_9138 || (g_9144 >= g_8f76 && g_8f76) || (!g_8f76 && g_05a8 % 3 == 0)) {
            g_9138 = 0;
            fn_11_1bcc();
            fn_11_0894();
            fn_11_3396();
        }
        SelectClipRgn(main_dc, g_0012);
        if (g_8e62)
            fn_11_6aa8(g_8e62, g_8e64, g_1d38);
        if (g_001a)
            return;
        if (!object_records[14][main_ship].f_18)
            fn_11_4db0();
        if (g_1048) {
            if (now_ms >= g_1e6c && g_92ec[2]) {
                g_1e6c = now_ms + 10000;
                fn_08_9464();
                g_914e = 0;
            }
            if (g_1e6c - 500 <= now_ms && !g_914e)
                fn_08_9564();
        }
        if (!object_records[g_9324][main_ship].f_18) {
            if (now_ms >= g_05a4)
                g_05a4 = now_ms + 50;
            if (g_05b8 < now_ms) {
                g_05b8 = now_ms + 10000;
                fn_07_2128();
            }
        }
        if (skip)
            return;
        if (g_9144 >= g_8f76) {
            for (j = g_9136 = 0; j < 5; j++) {
                for (i = 0; i < g_0598 + g_0594; i++)
                    g_9136 = fn_08_3aec(i, j);
                g_05cc++;
            }
            if (g_9430 > 0)
                for (i = 0; i <= g_9434; i++)
                    fn_08_3fbe(i);
            fn_07_375a();
        }
    } else {
        if (g_8e62)
            fn_11_6aa8(g_8e62, g_8e64, g_1d38);
        if (g_001a)
            return;
        if (skip)
            return;
    }
    if (g_9144 < g_8f76)
        return;
    g_2218 = g_2214;
    g_9144 = 0;
    g_9142++;
    if (g_9142 > 54)
        g_9142 = 0;
    if (frame_rate > 1000)
        g_8f76 = 0;
    else {
        g_914c++;
        if (now_ms > g_1e64) {
            if (!g_0592 && (g_059e + 1 < g_914c || g_059e - 1 > g_914c)) {
                if (g_914c > g_059e && !g_8f76)
                    g_8f76 = 1;
                g_8f76 = g_914c * g_8f76 / g_059e;
            }
            g_1e64 = now_ms + 250;
            g_914c = 0;
        }
    }
    g_0586++;
    if (now_ms > g_1e8c) {
        g_1e8c = now_ms + 1000;
        if (!g_0592 && frame_rate < 1000 && frame_rate + 9 > g_0586 && frame_rate - 9 < g_0586) {
            if (frame_rate < g_0586 && !g_8f76)
                g_8f76 = 1;
            g_8f76 = g_8f76 * g_0586 / frame_rate;
        }
        if (g_0592)
            g_0592--;
        g_059a = g_0586;
        if (g_0a76 == 4)
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        g_0586 = 0;
    }
    g_17b6++;
    if (g_17b6 >= 8)
        for (i = g_17b6 = 0; i <= g_9316; i++)
            if (g_7090[i].f_060)
                g_7090[i].f_060--;
    g_05a8++;
    g_1e68++;
    if (g_8ff4) {
        if (g_2388 < now_ms) {
            g_2388 = now_ms + 50;
            fn_11_72b2();
        }
        fn_11_7504();
    }
    if (subgame_active) {
        fn_16_64fa();
        return;
    }
    if (g_103c) {
        fn_10_7f88();
        g_103c = 0;
    }
    fn_08_158a(0);
    fn_08_0000();
    if (g_9140)
        fn_07_1d0c();
    g_9146 = 0;
    fn_08_4e14();
    if (g_870c && now_ms > g_870c) {
        g_870c = 0;
        if (g_9608)
            fn_03_06ec(main_ship, 14, g_7090[main_ship].f_058, 2);
        else
            fn_07_119c(2);
    }
    fn_12_3778();
    for (i = 0; i < g_9406[0]; i++)
        if (object_records[0][i].f_51)
            fn_07_3a42(i);
    if (g_17b8 < now_ms) {
        g_17b8 = now_ms + 280;
        if (g_0a76 == 2)
            fn_13_24aa(0);
        else if (g_0a76 == 3)
            fn_13_24aa(1);
        if (g_95fc)
            fn_13_24aa(2);
    }
    if (!object_records[7]->f_18)
        fn_16_00a2();
    else if (now_ms > g_6da8 && g_6da8 && fn_16_33a2())
        fn_16_3306();
    g_05d2 = !g_05d2;
    if (g_1016)
        fn_11_a9ea(1);
    fn_10_7b48();
    if (g_9320 == 6)
        fn_12_4d8e();
    if (g_913a || g_913c)
        fn_18_0d94();
    fn_13_0000();
    fn_07_3bae();
    fn_12_532c();
    fn_12_633e();
    fn_08_8256();
    fn_07_309c();
    fn_07_32d0();
    fn_07_40c4();
    fn_12_0000();
    fn_06_73f6();
    fn_06_7c14();
    if (g_9456 > 0)
        fn_07_5e04();
    fn_12_3148();
    fn_12_6b1e();
    if (g_9600)
        fn_12_0ae4();
    fn_12_3e98(0);
    if (g_2384 < now_ms && !g_0950 && !g_094e && !g_92e8 && !subgame_active)
        fn_13_ba04();
    if (g_1e68 % 300 == 0)
        fn_13_b93a();
    if ((hazards_ship_redraw_pending || g_0588 || g_7090[main_ship].f_0eb) && !g_951a) {
        if (!g_238c)
            fn_07_1208();
    } else if (g_7090[main_ship].f_156 <= now_ms) {
        if (!g_951a) {
            g_7090[main_ship].f_156 = now_ms + 1500;
            fn_13_6716(main_ship);
            if (g_913e)
                fn_18_5cec();
            if (!g_6da8 && g_952e >= 0 && g_9e49 >= 0 && g_9e49 < 9
                && (g_9e49 >= 6 || (!g_1e88 && object_records[7]->f_18)))
                g_6da8 = 1;
            for (i = 0; i <= g_9316; i++)
                if (g_7090[i].f_0eb && !object_records[14][i].f_2e)
                    g_7090[i].f_0eb = 0;
            if (g_9320 == 7)
                fn_12_515e();
            if (g_92e8 && flow_interactive) {
                g_9134 = 0;
                if (g_94b2 && !g_9316 && g_1e68 > 100) {
                    fn_13_adbe(main_ship, 0x13, 0xb4);
                    for (i = 1; i < g_7090[main_ship].cnt; i++)
                        if (g_7090[main_ship].f_0b8[i] < 0x16)
                            fn_12_6d64(1, g_7090[main_ship].f_0b8[i]);
                    g_7090[1].f_00a = g_7090[1].f_024 = g_7090[main_ship].f_00a;
                }
            }
            if (!g_9134) {
                r = fn_04_59bc();
                g_7090[main_ship].f_032.a = g_7090[main_ship].f_006;
                g_7090[main_ship].f_032.b = g_7090[main_ship].f_008;
                g_7090[main_ship].f_038 = g_7090[main_ship].f_036;
                g_7090[main_ship].f_03c = g_7090[main_ship].f_03a;
                if (g_7090[main_ship].f_032.a == 9 && g_7090[main_ship].f_038 == 1)
                    g_8714 = g_1e68;
                if (g_7090[main_ship].f_038 == 1
                    && (g_7090[main_ship].f_052 == 1 || g_7090[main_ship].f_052 == 5)
                    && !object_records[14][g_7090[main_ship].f_056].f_18) {
                    if (g_7090[main_ship].f_032.a == 14) {
                        if (g_7090[g_7090[main_ship].f_032.b].f_038 == 1
                            && g_7090[g_7090[main_ship].f_032.b].f_032.a == 14
                            && g_7090[g_7090[main_ship].f_032.b].f_032.b == g_7090[main_ship].f_056)
                            fn_13_7b40(g_7090[main_ship].f_056);
                    }
                } else if (g_7090[main_ship].f_032.a == 14 && g_7090[main_ship].f_038 == 1
                    && g_7090[g_7090[main_ship].f_032.b].f_038 == 1
                    && g_7090[g_7090[main_ship].f_032.b].f_032.a == 14
                    && g_7090[g_7090[main_ship].f_032.b].f_032.b != main_ship) {
                    g_0596++;
                    if (g_0596 > 1) {
                        fn_13_2714(g_7090[g_7090[main_ship].f_032.b].f_032.b, main_ship,
                            (10 - min((g_7090[g_7090[main_ship].f_032.b].f_0f6[0] + 7)[main_ship * 9], 10)) * 2,
                            (10 - min((g_7090[g_7090[main_ship].f_032.b].f_0f6[0] + 7)[main_ship * 9], 10)) * 5,
                            0, 7);
                        g_0596 = -4;
                    }
                } else if (g_7090[main_ship].f_032.a != 14 || g_7090[main_ship].f_038 == 1)
                    g_0596 = 0;
                if ((g_7090[main_ship].f_032.a == 0 || g_7090[main_ship].f_032.a == 4 || g_7090[main_ship].f_032.a == 11)
                    && g_7090[main_ship].f_038 == 2)
                    fn_04_6700(main_ship);
            }
            fn_08_9ab8();
            fn_13_3302();
            for (i = 0; i <= g_9324; i++)
                if (g_9406[i] < 0 || g_92ec[i] < g_9406[i])
                    g_9406[i] = g_92ec[i];
            for (i = 0; i <= g_9316; i++) {
                if (i != main_ship && g_7090[i].f_0c2[main_ship] > 0 && g_7090[i].f_0c2[main_ship] < 20
                    && g_1e68 / 10 - g_7090[i].f_044[0] > 60) {
                    g_7090[i].f_0c2[main_ship]--;
                    g_7090[main_ship].f_13e[i] = g_7090[i].f_13e[main_ship] = 0;
                }
                if (object_records[g_9324][i].f_18 == 1 && g_96d2[g_7090[i].f_04e].f_38 == 7
                    && g_7090[i].f_05e == 1) {
                    object_records[g_9324][i].f_18 = 100;
                    g_7090[i].flag = 1;
                }
            }
            fn_04_7e2a();
            fn_04_83ae();
            fn_08_9b4e();
        }
        fn_13_2f30(main_ship);
    }
    if (dissolve_active_count > 0)
        fn_07_158e();
    fn_13_447a();
}

/* 7:119c */
void fn_07_119c(int16_t a)
{
    g_0a76 = a;
    if (g_0a7c)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
}

/* 7:11cc */
void fn_07_11cc(void)
{
    object_records[14][main_ship].f_00.x = LO16(g_90ea) / 2;
    object_records[14][main_ship].f_00.y = HI16(g_90ea) / 2;
}

/* Updates the player ship sprite frame [inferred]. */
/* 7:1208 */
void fn_07_1208(void)
{
    int16_t u1;
    int16_t u2;
    int16_t v;
    int16_t idx;
    int16_t i;
    int16_t w;
    int16_t h;
    int16_t mode;
    int16_t u3;

    if (g_90f4 != 1 || object_records[14][main_ship].f_18 != 0 || g_951a || subgame_active)
        return;
    if (g_9e49 >= 3 && g_9e49 <= 6 && main_ship == g_952e)
        return;
    if (!g_3a38[0])
        return;
    if (!g_7090[main_ship].flag)
        for (i = 0; i <= g_9434; i++)
            if (g_1e90[i].f_06 == 14 && g_1e90[i].f_08 == main_ship && g_1e90[i].f_00 > 0
                && g_1e90[i].f_00 < 9)
                return;
    idx = main_ship;
    w = object_records[14][idx].f_22;
    h = object_records[14][idx].f_24;
    SetRect(&g_1e5c, object_records[14][idx].f_00.x + 2, object_records[14][idx].f_00.y + 2,
            object_records[14][idx].f_00.x + w - 2, object_records[14][idx].f_00.y + w - 2);
    mode = g_7090[idx].f_010;
    u1 = g_7090[idx].f_0ea;      /* never read: CL drops the store, keeps the load */
    v = (g_7090[idx].f_0e4 ? idx : g_7090[idx].f_050) + 40;
    if (mode == 0 || mode == 7)
        object_records[14][main_ship].f_10 = object_records[14][main_ship].f_28 * (h + w) + h;
    else
        object_records[14][main_ship].f_10 = w * 16 + h * 17;
    if (mode > 3)
        object_records[14][main_ship].f_12 = h * 2 + w;
    else if (g_7090[idx].f_0e9)
        object_records[14][main_ship].f_12 = h;
    fn_08_0b76((char)main_ship | 0xe00, 1, g_39e8[v], 0);
    hazards_ship_redraw_pending = 0;
}

/* Starts a dissolve effect on an object [inferred]. */
/* 7:13b2 */
void fn_07_13b2(char kind, int16_t type, int16_t idx)
{
    int16_t i;
    int16_t j;
    int16_t u;
    int16_t sq;
    int16_t r;
    int16_t found;

    if (type < 0)
        MessageBeep(0);
    if (type <= 14) {
        if (object_records[type][idx].f_2e > 0)
            return;
        fn_10_754a(0x27, type, idx, 1);
    }
    found = 0;
    if (type <= 14) {
        if (object_records[type][idx].f_22 % ((2 << g_9156) >> 1) == 0)
            r = 0;
        else
            r = 1;
        r += object_records[type][idx].f_22 >> g_9156;
    } else if (type == 20)
        r = g_92a4 / 8;
    else if (type >= 21)
        r = 24;
    sq = r * r;
    for (i = 0; i < 4; i++) {
        if (g_221c[i].type != -1)
            continue;
        if (type <= 14)
            object_records[type][idx].f_2e = kind;
        g_221c[i].type = type;
        g_221c[i].idx = idx;
        g_221c[i].sq = sq;
        g_221c[i].f_58 = 0;
        g_221c[i].r = r;
        if (type == 14)
            g_7090[idx].f_0eb = 1;
        for (j = 0; j < (int16_t)sizeof dissolve_map[i]; j++)
            dissolve_map[i][j] = 0;
        found = 1;
        dissolve_active_count++;
        if (kind == 2 && g_221c[i].type <= 14)
            PatBlt(object_records[g_221c[i].type][g_221c[i].idx].f_3c, 0, 0,
                   object_records[g_221c[i].type][g_221c[i].idx].f_24 * 2
                       + object_records[g_221c[i].type][g_221c[i].idx].f_22,
                   object_records[g_221c[i].type][g_221c[i].idx].f_24 * 2
                       + object_records[g_221c[i].type][g_221c[i].idx].f_22,
                   BLACKNESS);
        break;
    }
    if (!found && type <= 14)
        PatBlt(main_dc, object_records[type][idx].f_00.x, object_records[type][idx].f_00.y,
               object_records[type][idx].f_22, object_records[type][idx].f_22, BLACKNESS);
}

/* Advances the active dissolves by a few pixels each [inferred]. */
                                                     
/* 7:158e */
void fn_07_158e(void)
{
    int16_t i;
    int16_t j;
    int16_t pix;
    int16_t y;
    int16_t x;
    int16_t k;
    int16_t bit;
    int16_t ok;
    char mask;
    char unused[44];            /* never used: frame size */
    int16_t n;

    for (i = 0; i < 4; i++) {
        if (g_221c[i].type != -1) {
            if (g_221c[i].type <= 14)
                n = 10;
            else if (g_221c[i].type == 20)
                n = g_221c[i].sq / 9;
            else if (g_221c[i].type >= 21)
                n = 5;
            for (j = 0; j < n; j++) {
                do {
                    pix = rand() % g_221c[i].sq;
                    k = pix >> 3;
                    bit = pix & 7;
                    mask = 1 << bit;
                    ok = !(mask & dissolve_map[i][k]);
                } while (!ok);
                dissolve_map[i][k] |= mask;
                g_221c[i].f_58++;
                if (g_221c[i].type <= 14) {
                    x = pix % g_221c[i].r << g_9156;
                    y = pix / g_221c[i].r << g_9156;
                } else if (g_221c[i].type == 20) {
                    x = pix % g_221c[i].r << 3;
                    y = pix / g_221c[i].r << 3;
                } else if (g_221c[i].type == 21) {
                    x = (int32_t)(pix % g_221c[i].r) * LO16(g_90ea) / g_221c[i].r;
                    y = (int32_t)(pix / g_221c[i].r) * HI16(g_90ea) / g_221c[i].r;
                } else if (g_221c[i].type == 22) {
                    x = (int32_t)(pix % g_221c[i].r) * LO16(g_90ea) / g_221c[i].r / 2;
                    y = (int32_t)(pix / g_221c[i].r) * HI16(g_90ea) / g_221c[i].r / 2;
                } else if (g_221c[i].type == 23) {
                    x = (int32_t)(pix % g_221c[i].r) * LO16(g_90ea) / g_221c[i].r / 2 + LO16(g_90ea) / 2;
                    y = (int32_t)(pix / g_221c[i].r) * HI16(g_90ea) / g_221c[i].r / 2;
                } else if (g_221c[i].type == 24) {
                    x = (int32_t)(pix % g_221c[i].r) * LO16(g_90ea) / g_221c[i].r / 2 + LO16(g_90ea) / 2;
                    y = (int32_t)(pix / g_221c[i].r) * HI16(g_90ea) / g_221c[i].r / 2 + HI16(g_90ea) / 2;
                } else if (g_221c[i].type == 25) {
                    x = (int32_t)(pix % g_221c[i].r) * LO16(g_90ea) / g_221c[i].r / 2;
                    y = (int32_t)(pix / g_221c[i].r) * HI16(g_90ea) / g_221c[i].r / 2 + HI16(g_90ea) / 2;
                }
                if (g_221c[i].f_58 >= g_221c[i].sq) {
                    if (g_221c[i].type <= 14) {
                        if (object_records[g_221c[i].type][g_221c[i].idx].f_2e == 1) {
                            PatBlt(main_dc, object_records[g_221c[i].type][g_221c[i].idx].f_00.x, object_records[g_221c[i].type][g_221c[i].idx].f_00.y, object_records[g_221c[i].type][g_221c[i].idx].f_22, object_records[g_221c[i].type][g_221c[i].idx].f_22,
                                   BLACKNESS);
                            if (g_221c[i].type == 14 && g_7090[g_221c[i].idx].f_026[4] == 2) {
                                object_records[g_221c[i].type][g_221c[i].idx].f_2e = -2;
                                if (g_9134 && g_7090[main_ship].f_032.a == g_221c[i].type
                                    && g_7090[main_ship].f_032.b == g_221c[i].idx
                                    && g_7090[main_ship].f_038 == 1) {
                                    g_05c0 = now_ms + 1200;
                                    format_string(g_8630, 0x58e, g_058c = 1);
                                }
                            } else {
                                object_records[g_221c[i].type][g_221c[i].idx].f_18 = 1;
                                fn_07_65aa(g_221c[i].type, g_221c[i].idx);
                                if (g_221c[i].type != 14 && g_221c[i].type != 6
                                    && g_221c[i].type != 7 && g_221c[i].type != 2)
                                    for (j = 0; j < 8 && g_1e68 / 10 - g_937a[j] < 20; j++) {
                                        if (g_938a[j] == g_221c[i].type && g_9392[j] == g_221c[i].idx) {
                                            fn_10_754a(0x73, g_221c[i].type, g_221c[i].idx, 1);
                                            fn_03_06ec(main_ship, 7, 0, 0x70);
                                            g_1e58 += 800;
                                            break;
                                        }
                                    }
                                if (g_221c[i].type == 6) {
                                    g_6670[g_221c[i].idx + 4].r.right = g_2f4c[g_6670[g_221c[i].idx + 4].f_04.x].f_26;
                                    g_6670[g_221c[i].idx + 4].f_04.x = -1;
                                    object_records[g_221c[i].type][g_221c[i].idx].f_2e = 0;
                                } else {
                                    object_records[g_221c[i].type][g_221c[i].idx].f_2e = -1;
                                    fn_12_3778();
                                }
                                fn_12_26a4(g_221c[i].type, g_221c[i].idx);
                                fn_07_2080(g_221c[i].type);  /* sic: 2 args */
                                fn_02_170e();
                            }
                        } else {
                            if (object_records[g_221c[i].type][g_221c[i].idx].f_1a)
                                BitBlt(main_dc, object_records[g_221c[i].type][g_221c[i].idx].f_00.x, object_records[g_221c[i].type][g_221c[i].idx].f_00.y, object_records[g_221c[i].type][g_221c[i].idx].f_22, object_records[g_221c[i].type][g_221c[i].idx].f_22,
                                       object_records[g_221c[i].type][g_221c[i].idx].f_3c,
                                       (object_records[g_221c[i].type][g_221c[i].idx].f_22 + object_records[g_221c[i].type][g_221c[i].idx].f_24) * object_records[g_221c[i].type][g_221c[i].idx].f_28 + object_records[g_221c[i].type][g_221c[i].idx].f_24,
                                       object_records[g_221c[i].type][g_221c[i].idx].f_24, SRCCOPY);
                            object_records[g_221c[i].type][g_221c[i].idx].f_2e = 0;
                            if (g_221c[i].type == 14 && g_221c[i].idx == main_ship
                                && g_7090[main_ship].f_026[4] != 2)
                                fn_10_754a(0x65, 0, 0, 0);
                            fn_12_26a4(g_221c[i].type, g_221c[i].idx);
                        }
                        if (g_221c[i].type == 14) {
                            g_7090[g_221c[i].idx].f_0eb = 0;
                            fn_02_170e();
                        }
                        g_221c[i].type = -1;
                        dissolve_active_count--;
                        return;
                    } else if (g_221c[i].type == 20) {
                        PatBlt(g_929e, 0, 0, g_92a4, g_92a4, BLACKNESS);
                        g_221c[i].type = -1;
                        dissolve_active_count--;
                        return;
                    } else if (g_221c[i].type >= 21) {
                        g_221c[i].type = -1;
                        dissolve_active_count--;
                        return;
                    }
                } else if (g_221c[i].type <= 14) {
                    if (object_records[g_221c[i].type][g_221c[i].idx].f_2e == 1)
                        PatBlt(object_records[g_221c[i].type][g_221c[i].idx].f_3c, x + object_records[g_221c[i].type][g_221c[i].idx].f_24, y + object_records[g_221c[i].type][g_221c[i].idx].f_24,
                               (2 << g_9156) >> 1, (2 << g_9156) >> 1, BLACKNESS);
                    else
                        BitBlt(object_records[g_221c[i].type][g_221c[i].idx].f_3c, x + object_records[g_221c[i].type][g_221c[i].idx].f_24, y + object_records[g_221c[i].type][g_221c[i].idx].f_24,
                               (2 << g_9156) >> 1, (2 << g_9156) >> 1, object_records[g_221c[i].type][g_221c[i].idx].f_3a,
                               (object_records[g_221c[i].type][g_221c[i].idx].f_22 + object_records[g_221c[i].type][g_221c[i].idx].f_24) * object_records[g_221c[i].type][g_221c[i].idx].f_28 + object_records[g_221c[i].type][g_221c[i].idx].f_24 + x,
                               y + object_records[g_221c[i].type][g_221c[i].idx].f_24, SRCCOPY);
                } else if (g_221c[i].type == 20)
                    PatBlt(g_929e, x, y, 8, 8, BLACKNESS);
                else if (g_221c[i].type == 21)
                    BitBlt(main_dc, x, y, LO16(g_90ea) / g_221c[i].r + 1, HI16(g_90ea) / g_221c[i].r + 1,
                           g_9580, x, y, SRCCOPY);
                else if (g_221c[i].type > 21)
                    BitBlt(main_dc, x, y, LO16(g_90ea) / g_221c[i].r / 2 + 1,
                           HI16(g_90ea) / g_221c[i].r / 2 + 1, g_9580, x, y, SRCCOPY);
            }
        }
    }
}

/* Respawns ships waiting in state 100 after their timer runs out [inferred].
 * The redundant `j <= g_9316` test reproduces the extra jg. */
/* 7:1d0c */
void fn_07_1d0c(void)
{
    int16_t i;
    int16_t t;
    int16_t j;
    int16_t r;

    if (object_records[14][main_ship].f_18 == 100)
        fn_07_1208();
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].f_088 < now_ms) {
            t = g_96d2[g_7090[i].f_04e].f_38;
            for (j = i + 1; j <= g_9316; j++)
                if (j <= g_9316 && object_records[14][i].f_18 == 100 && object_records[14][j].f_18 == 100) {
                    g_7090[j].f_088 = now_ms + 5000;
                    break;
                }
            if (object_records[14][i].f_18 == 100 && (t != 7 || g_7090[i].f_05e != 1)) {
                r = rand() % g_9318;
                if (i == main_ship)
                    r = 0;
                object_records[14][i].f_04 = object_records[8][r * 2].f_04;
                object_records[14][i].f_04.x += (int16_t)(object_records[8][r * 2 + 1].f_04.x - object_records[8][r * 2].f_04.x) / 2
                                   - object_records[14][i].f_20 / 2 + object_records[8]->f_20 / 2;
                object_records[14][i].f_18 = 0;
                if (i == main_ship)
                    g_96d2[g_7090[i].f_04e].f_42 = 1;
                fn_08_0000();
                fn_10_754a(0x27, 14, i, 1);
                fn_12_2556(14, i);
                fn_07_13b2(2, 14, i);
                for (j = g_9140 = 0; j <= g_9316; j++)
                    if (object_records[14][j].f_18 == 100 && g_7090[j].flag)
                        g_9140 = 1;
                if (!g_9140 && g_9320 == 7)
                    g_6670[0].f_1a = 1;
                if ((g_094e || g_0950) && i != main_ship)
                    fn_13_563c(0, 0);
                return;
            }
        }
    }
}

/* 7:1f38 */
void fn_07_1f38(void)
{
    HFONT oldfont;
    HFONT font;
    COLORREF textcol;
    COLORREF bkcol;

    if (g_9134 == 1 && g_058c) {
        font = CreateFont(14, 9, g_058c = 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
        oldfont = SelectObject(main_dc, font);
        bkcol = SetBkColor(main_dc, 0L);
        SetBkMode(main_dc, OPAQUE);
        SetTextAlign(main_dc, 0);
        textcol = SetTextColor(main_dc, PALETTERGB(0, 0xff, 0xff));
        PatBlt(main_dc, g_1d28.left + 10, g_1d28.top, g_1d28.right - 10, g_1d28.bottom,
               BLACKNESS);
        g_1d28.bottom += g_1d28.top;
        g_1d28.right += g_1d28.left;
        fn_02_094c(0x929);
        lstrcat(g_8e68, g_8630);
        ExtTextOut(main_dc, g_1d28.left + 10, g_1d28.top, ETO_CLIPPED, &g_1d28,
                   g_8e68, lstrlen(g_8e68), NULL);
        g_1d28.bottom -= g_1d28.top;
        g_1d28.right -= g_1d28.left;
        SetBkColor(main_dc, bkcol);
        SetTextColor(main_dc, textcol);
        SelectObject(main_dc, oldfont);
        if (font)
            DeleteObject(font);
    }
}

/* 7:2080 */
void fn_07_2080(int16_t t)
{
    int16_t i;

    if (t == 1 || t == 2 || t == 7 || t == 5 || t == 11 || t == 9
        || t == 10 || t == 4 || t == 6 || t == 8 || t == 19) {
        for (i = g_92ec[t]; i > 0; i--)
            if (object_records[t][i - 1].f_18 == 0 || object_records[t][i - 1].f_51 != 0) {
                g_9406[t] = i;
                break;
            }
        if (i == 0)
            g_9406[t] = 0;
    }
}

/* 7:2128 */
void fn_07_2128(void)
{
    int16_t i;
    char unused[72];

    if (g_9316 == 0) {
        g_9432 -= max(g_9432 / 50, 2);
        if (g_9432 < 0)
            g_9432 = 0;
        return;
    }
    for (i = 0; i < g_9316; i++)
        if (g_7090[i].f_032.a == 14 && g_7090[i].f_032.b == main_ship && g_7090[i].f_038 == 1) {
            g_9432 -= max(g_9432 / 18, 4);
            if (g_9432 < 0)
                g_9432 = 0;
            if (g_8e28 + 15000 < now_ms) {
                g_9432 -= max(g_9432 / 14, 4);
                if (g_9432 < 0)
                    g_9432 = 0;
            }
            return;
        }
    g_9432 -= max(g_9432 / 40, 3);
    if (g_9432 < 0)
        g_9432 = 0;
    if (g_8e28 + 15000 < now_ms) {
        g_9432 -= max(g_9432 / 36, 2);
        if (g_9432 < 0)
            g_9432 = 0;
    }
}

/* Frame-rate bookkeeping [inferred]: counts frames per 250 ms and per
 * second and rescales g_9004 when off target. */
/* 7:2206 */
void fn_07_2206(void)
{
    int16_t a;
    int16_t b;

    if (g_90f4 == 6 && g_952c && g_9530 == 1) {
        b = g_6da4->f_2a;
        a = b / 4;
    } else if (g_90f4 == 6 && g_914a == 1 && g_92a2 == 0) {
        a = 8;
        b = 32;
    } else {
        a = 18;
        b = 72;
    }
    g_914c++;
    if (now_ms > g_1e64) {
        if (a + 1 < g_914c || a - 1 > g_914c) {
            if (g_914c > a && g_9004 == 0)
                g_9004 = 1;
            g_9004 = g_914c * g_9004 / a;
        }
        g_1e64 = now_ms + 250;
        g_914c = 0;
    }
    g_0586++;
    if (now_ms > g_1e8c) {
        g_1e8c = now_ms + 1000;
        if (b + 9 > g_0586 && b - 9 < g_0586) {
            if (b < g_0586 && g_9004 == 0)
                g_9004 = 1;
            g_9004 = g_9004 * g_0586 / b;
        }
        if (g_0592)
            g_0592--;
        g_059a = g_0586;
        g_0586 = 0;
    }
}
