/* INSPACE.EXE segment 9 (selector 1040). */
#include "game.h"

/* g_05a0 is declared long in inspace.h; read here as two ints (world
 * width and height [inferred]). */
                                       
                                       

/* Starts a wave: resets per-wave state, picks the wave's script
 * resource and builds the world map bitmap [inferred]. */
/* 9:5cca */
void fn_09_5cca(void)
{
    int16_t i;
    int16_t n;

    fn_09_8908();
    ShowWindow(g_0016, SW_SHOW);
    PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    if (flow_interactive)
        SetCursorPos(g_1d48, g_0010);
    fn_02_0ba4();
    g_90f4 = 3;
    fn_02_170e();
    g_93b0 = 0;
    g_8710 = g_8714 = 0;
    fn_09_22b4(g_9e5b = 1);
    g_1df8[7][0].f_18 = 1;
    g_9e49 = 10;
    g_952e = -1;
    g_1e88 = 0;
    fn_10_5b30();
    fn_09_0b2a();
    fn_10_506c();
    for (i = 0; i < 8; i++)
        fn_07_233c(0, i, 0);
    for (i = 0; i < 4; i++)
        g_8e34[i] = -1;
    fn_10_6308(13, -1, -1, -1);
    fn_09_94ba();
    g_9496 = 1;
    for (i = n = g_9434 = dissolve_active_count = g_9146 = g_1016 = g_951a = g_965e
             = g_913c = g_913a = g_9666 = subgame_active = g_93a6 = g_666c = 0;
         i < 8; i++) {
        g_938a[i] = -1;
        g_9392[i] = 0;
        g_937a[i] = 0;
        if (g_1df8[0][i].f_18 == 0)
            n++;
    }
    g_0992 += n * 4;
    for (i = 0; i < 8; i++)
        g_8680[i] = -1;
    g_9680 = g_9682 = 0;
    g_8e00 = g_8e04 = 0;
    g_91f8++;
    fn_09_6624();
    g_91f8--;
    if (n != 0) {
        if (n * g_932e * 4 + g_0992 > g_932a + 10)
            g_932e = max(0, (g_932a - g_0992 + 20) / (n * 4));
    } else
        g_932e = 0;
    if (g_8ff8 == 0)
        g_932e = min(g_932e, 1);
    else if (g_8ff8 == 1)
        g_932e = min(g_932e, 2);
    g_0992 += n * g_932e * 4;
    g_92ec[2] = g_932e * 8;
    if (g_92e8) {
        g_93b4 = LoadResource(g_9212, FindResource(g_9212, MAKEINTRESOURCE(0x66), MAKEINTRESOURCE(5000)));
        g_4fcc = LockResource(g_93b4);
    } else if (g_094e) {
        g_93b4 = LoadResource(g_9212, FindResource(g_9212, MAKEINTRESOURCE(0x67), MAKEINTRESOURCE(5000)));
        g_4fcc = LockResource(g_93b4);
    } else if (g_0950) {
        g_93b4 = LoadResource(g_9212, FindResource(g_9212, MAKEINTRESOURCE(0x68), MAKEINTRESOURCE(5000)));
        g_4fcc = LockResource(g_93b4);
    } else if (g_91f8 == 0) {
        g_93b4 = LoadResource(g_9212, FindResource(g_9212, MAKEINTRESOURCE(0x65), MAKEINTRESOURCE(5000)));
        g_4fcc = LockResource(g_93b4);
    } else {
        g_93a8 = GlobalAlloc(GHND, 2000);
        g_4fcc = GlobalLock(g_93a8);
        fn_09_91b0();
    }
    if (g_93d0) {
        SelectObject(g_93d0, g_93ca);
        if (g_920e)
            SelectPalette(g_93d0, g_93d2, 0);
        DeleteDC(g_93d0);
        DeleteObject(g_93c8);
        g_93c8 = g_93d0 = 0;
    }
    g_91f8++;
    if (g_9320 == 6) {
        g_93c8 = world_map(g_0a72, g_0a74, 0, g_9322, -1, -1, 0);
        g_93d0 = CreateCompatibleDC(g_13dc);
        g_93ca = SelectObject(g_93d0, g_93c8);
        if (g_920e)
            g_93d2 = SelectPalette(g_93d0, (HPALETTE)g_920e, 0);
        if (g_94a8 == 0)
            for (i = 0; i < g_9ebc[g_9322]; i++)
                world_map(g_0a72, g_0a74, 0, g_9322, 8, g_9eb9[g_9322] + g_9318 * 2 + i, 0);
        BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
        if (flow_interactive)
            g_9134 = 0;
        g_94ca = g_91f8;
    }
    if (g_92e8 && flow_interactive)
        g_9134 = 0;
    draw_briefing_panel_with_esc_prompt(1);
}

/* Starts a race wave: start positions (or random free spots) for the
 * racers, the weapon-pickup chance g_913e and the player's tables
 * [inferred]. */
/* 9:60bc */
void fn_09_60bc(void)
{
    int16_t i;
    int16_t t;
    int16_t j;
    int16_t cls;
    int16_t music;
    RECT r1;
    RECT r2;
    RECT r3;
    int16_t hit;
    char buf[20];
    int16_t chance;
    int16_t cnt;
    int16_t w;

    fn_09_699e();
    lstrcpy(g_8630, "");
    ShowWindow(g_0016, SW_SHOW);
    PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    g_90f4 = 1;
    g_0a76 = 2;
    g_9e49 = 10;
    g_93a4 = 0;
    fn_08_190e();
    fn_13_2dcc();
    g_a197 = 0;
    g_913e = 0;
    if (g_9334 > 4 && g_92e8 == 0 && g_9320 != 6 && g_9320 != 7 && g_920c != 0 && g_920c != 3
        && (g_0992 + 30 < g_932a || g_91f8 - g_93ac > 15)) {
        for (i = cnt = 0; i < g_7090[main_ship].cnt; i++) {
            w = g_7090[main_ship].f_0b8[i];
            if (w == 0x18 || w == 0x19 || w == 0x17 || w == 0x16)
                cnt++;
            if (w == 0x1a)
                cnt += 2;
        }
        if (g_91f8 - g_93ac > 4 && cnt < 4) {
            chance = ((g_91f8 - g_93ac - 3) * 2 + g_9334) * 2;
            for (i = 1; i <= g_7090[main_ship].cnt; i++)
                if (g_7090[main_ship].f_0b8[i] >= 0x16 && g_7090[main_ship].f_0b8[i] <= 0x1a)
                    chance = chance * 4 / 5;
            if (rand() % 100 < chance)
                g_913e = 1;
        }
    }
    for (i = 0; i <= g_9316; i++) {
        g_1df8[14][i].f_00.y = -100;
        hit = 0;
        if (g_94b0 == 0) {
            for (t = 0; t <= 8; t++)
                if (i != main_ship && g_69f4[g_94a2].f_1c0[t] == g_7090[i].f_0d6)
                    hit = 1;
        }
        if (hit != 0 && g_9320 != 6) {
            do {
                g_1df8[14][i].f_04.x = rand() % (LO16(g_05a0)) * 8;
                g_1df8[14][i].f_04.y = rand() % (HI16(g_05a0)) * 8;
                SetRect(&r1, g_1df8[14][i].f_04.x, g_1df8[14][i].f_04.y,
                        g_1df8[14][i].f_04.x + g_1df8[14][i].f_20, g_1df8[14][i].f_04.y + g_1df8[14][i].f_20);
                for (t = hit = 0; t < 14; t++)
                    for (j = 0; j < (&g_9406[0])[t]; j++) {
                        SetRect(&r2, g_1df8[t][j].f_04.x, g_1df8[t][j].f_04.y,
                                g_1df8[t][j].f_04.x + g_1df8[t][j].f_20,
                                g_1df8[t][j].f_04.y + g_1df8[t][j].f_20);
                        if (IntersectRect(&r3, &r1, &r2))
                            hit = 1;
                    }
            } while (hit);
            g_1df8[14][i].f_18 = 0;
            g_1df8[14][i].f_0c = rand() % 60 - 30;
            g_1df8[14][i].f_0e = rand() % 60 - 30;
            g_7090[i].f_088 = GetCurrentTime();
        } else {
            g_1df8[14][i].f_04.x = -1000;
            g_1df8[14][i].f_04.y = (-10 - i) * 100;
            if (i == main_ship) {
                g_1df8[14][i].f_04 = g_1df8[12][0].f_04;
                fn_08_0000();
            }
            g_1df8[14][i].f_18 = 100;
            g_7090[i].f_088 = GetCurrentTime() + (int32_t)i * 500000;
            g_1df8[14][i].f_0c = 0;
            g_1df8[14][i].f_0e = -30;
        }
        if (g_96d2[g_7090[i].f_04e].f_38 != 7 || g_7090[i].f_05e != 0)
            g_7090[i].f_0cd = -1;
    }
    fn_08_4d94(&g_7090[main_ship].f_088, &g_7090[0].f_088);
    fn_03_045a(2);
    fn_11_3cc2(main_ship);
    g_0a76 = 2;
    g_9648 = 0;
    if (g_91f8 <= 1) {
        for (i = 0; i < 2; i++)
            (&g_7090[main_ship].f_05d)[i] = 2;
        g_7090[main_ship].f_0d0 = g_7090[main_ship].f_0d2 = 0;
    }
    if (g_9320 == 7)
        g_6670[0].f_1a = 0;
    g_9370 = g_7090[main_ship].f_0d2;
    g_9372 = g_7090[main_ship].f_0d0;
    for (i = g_964c = g_934e = 0; i < 2; i++)
        g_9374[i] = (&g_7090[main_ship].f_05d)[i];
    cls = g_96d2[g_7090[main_ship].f_04e].f_38;
    for (i = 0; i < 8; i++)
        g_9350[i] = g_3824[i][cls];
    for (i = 0; i < 8; i++)
        g_9360[i] = fn_13_2688(i, main_ship);
    g_93b6 = -1;
    if (g_094e)
        music = 3;
    else if (g_92e8)
        music = 7;
    else if (g_0950)
        music = 7;
    else
        music = 1;
    fn_10_7480(music, 1);
    fn_13_4eca("start wave iMainSmart = ");
    fn_06_0f1a(main_ship, buf);
    fn_13_4eca(buf);
    fn_13_4eca("\n\r");
}

/* 9:699e */
void fn_09_699e(void)
{
    if (g_93b4) {
        if (g_4fcc) {
            GlobalUnlock(g_93b4);
            g_4fcc = 0;
        }
        FreeResource(g_93b4);
        g_93b4 = 0;
    } else if (g_93a8) {
        if (g_4fcc) {
            GlobalUnlock(g_93a8);
            g_4fcc = 0;
        }
        GlobalFree(g_93a8);
        g_93a8 = 0;
    }
}

/* 9:6a12 */
void fn_09_6a12(void)
{
    char buf[80];
    char buf2[60];

    if (flow_interactive == 0)
        return;
    fn_09_955c(0x145, buf);
    fn_10_94c4(0, 6, 0x020080ffL, LO16(g_90ea) / 2, g_0010 / 2 - 175, buf);
    fn_10_a332(buf, 0x9e4, 1, g_91f8);
    fn_10_94c4(0, 0, 0x8000L, LO16(g_90ea) / 2 - 240, g_0010 / 2 - 115, buf);
    fn_10_a332(buf, 0x9e5, 1);
    fn_10_94c4(0, 0, 0x8000L, LO16(g_90ea) / 2 - 240, g_0010 / 2 - 85, buf);
    fn_10_a332(buf, 0x9e6, 1, g_7090[main_ship].f_0d2);
    fn_10_94c4(0, 2, 0x8000L, LO16(g_90ea) / 2 + 124, g_0010 / 2 - 85, buf);
    fn_10_a332(buf, 0x9e7, 1, g_7090[main_ship].f_0d0);
    fn_10_94c4(0, 2, 0x8000L, LO16(g_90ea) / 2 + 124, g_0010 / 2 - 55, buf);
    fn_10_a332(buf, 0x9e8, 1, g_1e58);
    fn_10_94c4(0, 6, 0xffL, LO16(g_90ea) / 2, g_0010 / 2 + 65, buf);
}

/* 9:6bc2 */
void fn_09_6bc2(void)
{
    int16_t i;
    int16_t j;
    int16_t unused;

    fn_10_7480(-1, 1);
    g_1e74 = 0;
    if (g_9320 == 6) {
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].f_032.a == 0 && i != main_ship) {
                for (j = 0; j < g_9406[0]; j++) {
                    if (g_1df8[0][j].f_18 == 0) {
                        g_7090[i].f_0ce += g_1df8[0][j].f_1e * -90 / 210 + 100;
                        g_7090[i].f_0d2++;
                        fn_07_5ae8(j, 1);
                    }
                }
            }
        }
    }
    if (g_93a4) {
        g_90f4 = 8;
        g_929c = 0;
        fn_16_6928(0);
        g_9346 = -1;
        for (i = 0; i <= g_9316; i++) {
            if (g_96d2[g_7090[i].f_04e].f_38 == 7 && g_7090[i].f_05e == 0
                && g_7090[i].f_056 == main_ship)
                g_7090[i].flag = 0;
        }
    } else
        fn_09_6cc4(0);
}

/* 9:6cc4 */
void fn_09_6cc4(int16_t flag)
{
    int16_t i;
    int16_t j;

    fn_10_7db8();
    fn_13_65f2(1);
    g_1e74 = 0;
    g_90f4 = 2;
    g_92e4 = 0;
    if (g_9320 == 6)
        fn_09_6db0();
    if (g_92e0) {
        GlobalUnlock(g_92e0);
        g_3d4c = 0;
        GlobalFree(g_92e0);
        g_92e0 = 0;
    }
    fn_09_1092();
    for (i = 0; i <= 14; i++)
        for (j = 0; j < g_92ec[i]; j++)
            fn_12_26a4(i, j);
    fn_11_02f0();
    fn_07_49b6();
    PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    g_93b2 = g_9332;
    fn_09_2828();
    fn_06_7266();
    g_94c4 = 1;
    g_9330 = 0;
    if (flag)
        fn_09_6dec(1);
}

/* 9:6db0 */
void fn_09_6db0(void)
{
    int16_t i;

    for (i = 0; i <= g_9316; i++)
        g_7090[i].f_01e = g_96d2[g_7090[i].f_04e].f_1e;
}

/* 9:6dec */
void fn_09_6dec(int16_t force)
{
    char buf[140];
    char unused[40];
    int16_t r;
    int16_t left;
    int16_t right;
    int16_t clip;

    clip = 0;
    if (flow_interactive == 0 || g_1e70 == g_1e50)
        return;
    if (force || g_6078 == 0) {
        SetRect(&g_6084, LO16(g_90ea) / 2 - 290, g_0010 / 2 - 173, LO16(g_90ea) / 2 + 290, g_0010 / 2 + 173);
        left = max(g_6084.left - 6, 0);
        right = min(g_6084.right + 6, LO16(g_90ea));
        fn_11_1774(2, g_6084.left - 6, g_6084.top - 15, g_6084.right + 6, g_6084.bottom + 6);
        fn_11_1774(-1, left, g_6084.top - 15, right, g_6084.top + 10);
        fn_10_a332(buf, 0xbbb, 1, g_91f8);
        fn_09_8bec(g_13dc, left + 5, g_6084.top - 13, 22, 10, 0, buf);
        fn_09_955c(0x8be, buf);
        fn_09_8bec(g_13dc, right - 7, g_6084.top - 6, 14, 0, 2, buf);
        g_5000 = g_6084.left + 14;
        g_5002 = g_6084.top + 18;
        if (g_93ae) {
            DeleteObject(g_93ae);
            g_93ae = 0;
        }
        g_93ae = CreateRectRgn(g_6084.left, g_5002, g_6084.right, g_6084.bottom);
        clip = 1;
        SelectClipRgn(g_13dc, g_93ae);
        if (g_6078 == 0)
            fn_17_30b0(11, 3500L);
        else
            fn_17_2c5a(1, 1);
    }
    if (clip == 0)
        SelectClipRgn(g_13dc, g_93ae);
    if (g_6078)
        r = fn_17_2c5a(0, 0);
    if (g_9134 && r == 1)
        g_1e74 = g_1e50 + 3000;
}

/* Builds the end-of-race / end-of-level report text in g_6078 [inferred]. */
/* 9:6fee */
void fn_09_6fee(void)
{
    /* pad_* are unused slots in the original frame. */
    int16_t i;
    int16_t j;
    int16_t k;
    int16_t pad_a;
    int16_t diff;
    int16_t pad_e;
    int16_t dx;
    int16_t dy;
    int16_t best[2];
    int16_t val[2];
    int16_t cls;
    int16_t count;
    int16_t idx[3];
    int16_t score[3];
    int16_t nfound;
    int16_t rank[3];
    int16_t used[8];
    int16_t pad_5c[13];
    int16_t count2;
    int16_t pad_60;
    int16_t n;
    int16_t d;
    int16_t c;
    int16_t b;
    int16_t a;
    char buf[100];
    char buf2[10];
    int16_t show;
    int16_t flag2;
    int16_t cnt[2];
    int16_t best2[2];
    int16_t pad_e6;
    int16_t pad_e8;
    int16_t f3;
    int16_t has[8];
    WORD mins[4][2];
    int16_t v;
    int16_t order[4];
    int16_t k3;
    int16_t n4;
    int16_t flag4;

    lstrcpy(g_6078, "");
    cls = g_96d2[g_7090[main_ship].f_04e].f_38;
    dx = g_7090[main_ship].f_0d2 - g_9370;
    dy = g_7090[main_ship].f_0d0 - g_9372;
    if (g_38c8[1] != ':' && g_9320 == 6) {
        fn_09_95ba(0x8bf);
        show = 1;
    } else if (g_38c8[1] != ':' && g_9320 == 7) {
        fn_09_95ba(0x862);
        show = 0;
    } else {
        fn_09_95ba(0x13e);
        show = 0;
        if (g_9320 == 6)
            show = 1;
    }
    fn_09_95ba(0x221);
    lstrcat(g_6078, g_38c8);
    fn_17_42ea(1);
    fn_10_a332(g_6078, 0xbbc, 0, g_094e == 0, g_1e58);
    if (g_38c8[1] == ':' && g_9320 != 6) {
        v = g_94a6 - g_69f4[g_94a2].f_14e - g_69f4[g_94a2].f_150;
        if (g_69f4[g_94a2].f_1d0 == 2) {
            fn_10_a332(g_6078, 0xbbd, 0, (LPSTR)g_38c8, (LPSTR)g_380c, g_94a6 > 20,
                       g_94a6 < 50, 0x8c2, 0x8c3);
            fn_10_a332(g_6078, 0xbbe, 0, g_94a6 > 1, g_94a6, 0x9d3, g_69f4[g_94a2].f_150,
                       0x9ca, g_69f4[g_94a2].f_14e, 0x9ca);
        } else {
            fn_10_a332(g_6078, 0xbbf, 0, g_69f4[g_94a2].f_150, 0x9cb, g_69f4[g_94a2].f_14e,
                       0x9cb, v == 1, 0x9cd, 0x9cc, v, 0x9d3);
        }
        fn_17_42ea(1);
        fn_17_42ea(1);
    }
    if (show) {
        DWORD ldiff;
        DWORD times[4];
        int16_t flag5;
        char buf3[60];

        n4 = (g_094e - 1) % 4;
        fn_06_8b90(g_9322);
        switch (g_9ea0) {
        case 1:
            k3 = 0;
            break;
        case 5:
            k3 = 1;
            break;
        case 10:
            k3 = 2;
            break;
        }
        n = fn_06_8cb2(g_9322, main_ship, 0, k3, 1);
        for (i = 0; i <= n4; i++) {
            order[i] = i;
            if (g_1df8[14][i].f_51 == 2)
                times[i] = g_9e60[i];
            else
                times[i] = g_1e68 - g_9e60[i];
        }
        for (i = 0; i <= n4; i++)
            for (j = 0; j <= n4 - i - 1; j++)
                if (times[order[j]] > times[order[j + 1]])
                    fn_08_4d60(&order[j], &order[j + 1]);
        for (i = 0; i <= n4; i++) {
            if (g_96d2[g_7090[i].f_04e].f_38 != 7) {
                if (g_1df8[14][order[i]].f_51 == 2) {
                    fn_11_4928(0, g_9e60[order[i]], buf);
                    lstrcat(g_6078, buf);
                    lstrcat(g_6078, "- ");
                    fn_17_7ba6(i + 1, buf);
                    lstrcat(g_6078, buf);
                    fn_09_95ba(0x8c9);
                } else {
                    fn_11_4928(0, g_1e68 - g_9e60[order[i]], buf);
                    lstrcat(g_6078, buf);
                    lstrcat(g_6078, "- ");
                    fn_09_95ba(0x8ca);
                }
                fn_03_1542(0, 14, order[i], buf, 0);
                lstrcat(g_6078, buf);
                if (order[i] == main_ship)
                    fn_09_95ba(0x8a6);
                lstrcat(g_6078, "\t350");
                fn_09_95ba(0x896);
                fn_11_4928(1, g_9e90[order[i]], buf);
                lstrcat(g_6078, buf);
                fn_17_42ea(0);
            }
        }
        fn_17_42ea(1);
        i = mins[3][0] = mins[3][1] = mins[2][0] = mins[2][1] = mins[1][0] = mins[1][1] =
            mins[0][0] = mins[0][1] = 0;
        for (; i < g_94c8; i++)
            for (j = 0; j < 2; j++) {
                if (k3 > 0 && g_6afc[i].f_32[k3][j] &&
                    (g_6afc[i].f_32[k3][j] < mins[0][j] || mins[0][j] == 0))
                    mins[0][j] = g_6afc[i].f_32[k3][j];
                if (g_6afc[i].f_32[0][j] &&
                    (g_6afc[i].f_32[0][j] < mins[1][j] || mins[1][j] == 0))
                    mins[1][j] = g_6afc[i].f_32[0][j];
            }
        for (j = 0; j < 2; j++) {
            if (k3 > 0)
                mins[2][j] = g_6afc[n].f_32[k3][j];
            mins[3][j] = g_6afc[n].f_32[0][j];
        }
        for (i = 0; i <= n4; i++) {
            if (i == main_ship && flow_interactive != 0)
                flag4 = 0;
            else
                flag4 = 1;
            if (g_1df8[14][i].f_51 != 0) {
                if (k3 > 0) {
                    fn_06_8cb2(g_9322, i, min(g_9e60[i], 0xfa00), k3, 1);
                    if (!flag4)
                        fn_06_8cb2(g_9322, i, min(g_9e60[i], 0xfa00), k3, 0);
                }
                fn_06_8cb2(g_9322, i, min(g_9e90[i], 0xfa00), 0, 1);
                if (!flag4)
                    fn_06_8cb2(g_9322, i, min(g_9e90[i], 0xfa00), 0, 0);
            }
        }
        fn_09_95ba(0x8d0);
        fn_17_42ea(1);
        if (k3 > 0) {
            fn_09_95ba(0x8cf);
            fn_09_95ba(0x8cc);
            fn_06_0f1a(g_9ea0, buf2);
            lstrcat(g_6078, buf2);
            fn_09_95ba(0x8cb);
            lstrcat(g_6078, "S):\t350");
            fn_11_4928(0, mins[0][1], buf);
            lstrcat(g_6078, buf);
            lstrcat(g_6078, "\t435");
            fn_11_4928(0, mins[0][0], buf);
            lstrcat(g_6078, buf);
            fn_17_42ea(1);
            fn_03_1542(0, 14, main_ship, buf, 0);
            lstrcat(g_6078, buf);
            fn_09_95ba(0x8cc);
            lstrcat(g_6078, buf2);
            fn_09_95ba(0x8cb);
            lstrcat(g_6078, "S):\t350");
            fn_11_4928(0, mins[2][1], buf);
            lstrcat(g_6078, buf);
            lstrcat(g_6078, "\t435");
            fn_11_4928(0, mins[2][0], buf);
            lstrcat(g_6078, buf);
            fn_17_42ea(1);
        }
        fn_09_95ba(0x8cf);
        fn_09_95ba(0x8cd);
        fn_09_95ba(0x221);
        lstrcat(g_6078, "\t350");
        fn_11_4928(0, mins[1][1], buf);
        lstrcat(g_6078, buf);
        lstrcat(g_6078, "\t435");
        fn_11_4928(0, mins[1][0], buf);
        lstrcat(g_6078, buf);
        fn_17_42ea(1);
        fn_03_1542(0, 14, main_ship, buf, 0);
        lstrcat(g_6078, buf);
        fn_09_95ba(0x8cd);
        fn_09_95ba(0x221);
        lstrcat(g_6078, "\t350");
        fn_11_4928(0, mins[3][1], buf);
        lstrcat(g_6078, buf);
        lstrcat(g_6078, "\t435");
        fn_11_4928(0, mins[3][0], buf);
        lstrcat(g_6078, buf);
        fn_17_42ea(1);
        fn_17_42ea(1);
        if (n4 != 0 && g_1df8[14][main_ship].f_51 == 2) {
            flag5 = 0;
            if (order[0] == main_ship) {
                if (g_1df8[14][order[1]].f_51 == 2) {
                    ldiff = g_9e60[order[1]] - g_9e60[order[0]];
                    fn_11_4928(1, ldiff, buf);
                    fn_03_1542(0, 14, order[1], buf3, 0);
                    flag5 = 1;
                }
                fn_10_a332(g_6078, 0xbc0, 0, (LPSTR)g_380c, flag5, (LPSTR)buf3, (LPSTR)buf);
            } else {
                ldiff = g_9e60[main_ship] - g_9e60[order[0]];
                fn_11_4928(1, ldiff, buf);
                fn_03_1542(0, 14, order[0], buf3, 0);
                fn_10_a332(g_6078, 0xbc1, 0, (LPSTR)buf3, (LPSTR)buf);
            }
        }
        if (g_1df8[14][main_ship].f_51 == 2) {
            i = mins[3][0] = mins[3][1] = mins[2][0] = mins[2][1] = mins[1][0] = mins[1][1] =
                mins[0][0] = mins[0][1] = 0;
            for (; i < g_94c8; i++)
                for (j = 0; j < 2; j++) {
                    if (k3 > 0 && g_6afc[i].f_32[k3][j] &&
                        (g_6afc[i].f_32[k3][j] < mins[0][j] || mins[0][j] == 0))
                        mins[0][j] = g_6afc[i].f_32[k3][j];
                    if (g_6afc[i].f_32[0][j] &&
                        (g_6afc[i].f_32[0][j] < mins[1][j] || mins[1][j] == 0))
                        mins[1][j] = g_6afc[i].f_32[0][j];
                }
            for (j = 0; j < 2; j++) {
                if (k3 > 0)
                    mins[2][j] = g_6afc[n].f_32[k3][j];
                mins[3][j] = g_6afc[n].f_32[0][j];
            }
            a = b = d = 0;
            if (k3 > 0) {
                if (g_9e60[main_ship] <= mins[0][1]) {
                    a = 1;
                    d++;
                } else if (g_9e60[main_ship] <= mins[0][0]) {
                    a = 1;
                    b = 1;
                    d++;
                }
                if (g_9e60[main_ship] <= mins[2][1])
                    d++;
                else if (g_9e60[main_ship] <= mins[2][0]) {
                    b = 1;
                    d++;
                }
                if (d != 0) {
                    if (a != 0)
                        LoadString(g_9212, 0x8d7, buf, 40);
                    else {
                        fn_03_1542(0, 14, main_ship, buf, 0);
                        lstrcat(buf, "S!  ");
                    }
                    fn_10_a332(g_6078, 0xbc7, 0, g_9ea0, b, (LPSTR)buf);
                }
            }
            a = b = c = 0;
            if (g_9e90[main_ship] <= mins[1][1]) {
                a = 1;
                c++;
            } else if (g_9e90[main_ship] <= mins[1][0]) {
                a = 1;
                b = 1;
                c++;
            }
            if (g_9e90[main_ship] <= mins[3][1])
                c++;
            else if (g_9e90[main_ship] <= mins[3][0]) {
                b = 1;
                c++;
            }
            if (c != 0) {
                if (a != 0)
                    LoadString(g_9212, 0x8d7, buf, 40);
                else {
                    fn_03_1542(0, 14, main_ship, buf, 0);
                    lstrcat(buf, "S!  ");
                }
                fn_10_a332(g_6078, 0xbc8, 0, d, b, (LPSTR)buf);
            }
        } else if (g_1df8[14][main_ship].f_51 == 0)
            fn_09_95ba(0x8db);
        fn_06_8dfe(g_9322);
        fn_06_8eb4();
    } else {

        fn_10_a332(g_6078, 0xbc2, 0, g_9320 == 7, 0x366, 0x7cd, g_934e >= 60, g_934e / 60,
                   0x9ce, g_934e - g_934e / 60 * 60, 0x9cf);
        if (g_9320 == 7) {
            fn_10_a332(g_6078, 0xbc3, 0);
            fn_10_a332(g_6078, 0xbca, 0, g_9680, 0x9d0, g_8e00, g_9682, 0x9d1, g_8e04);
            if (g_8e00 / g_9316 < g_8e04 * 3 / 4) {
                fn_09_95ba(0x7cb);
                f3 = 0;
            } else if (g_8e00 / g_9316 > g_8e04 * 6) {
                if (g_9316 == 1)
                    fn_09_95ba(0x7c3);
                else
                    fn_09_95ba(0x7c4);
                f3 = 1;
            } else if (g_8e00 / g_9316 > g_8e04 * 3) {
                if (g_9316 == 1)
                    fn_09_95ba(0x7c1);
                else
                    fn_09_95ba(0x7c2);
                f3 = 1;
            } else if (g_8e00 / g_9316 > g_8e04 * 3 / 2) {
                if (g_9316 == 1)
                    fn_09_95ba(0x7bf);
                else
                    fn_09_95ba(0x7c0);
                f3 = 1;
            } else {
                fn_09_95ba(0x7cc);
                f3 = 0;
            }
            if (g_7090[main_ship].f_026[0] < 40)
                fn_09_95ba(f3 + 0x646);
            else if (g_7090[main_ship].f_026[0] < 70)
                fn_09_95ba(f3 + 0x648);
            else
                fn_09_95ba(f3 + 0x64a);
            return;
        }
        fn_10_a332(g_6078, 0xbc4, 0, dx, dx, 0x9d3, dy, dy, 0x9d3, dx == 0 && dy == 0);
        for (i = 0; i < 8; i++)
            used[i] = -1;
        for (j = f3 = count2 = 0; j <= g_9316; j++)
            if (g_96d2[g_7090[j].f_04e].f_38 == 7 && g_1df8[14][j].f_18 != 100) {
                f3 = 1;
                break;
            }
        if (f3) {
            for (i = 0; i < 3; i++)
                if (g_4eec[7][i] == g_931c && g_4fd0[7][i] == g_91f8)
                    count2++;
            if (count2) {
                fn_13_218a(7, buf);
                fn_10_a332(g_6078, 0xbc5, 0, buf);
            }
        }
        for (i = count2 = 0; i <= g_9316; i++) {
            if (g_96d2[g_7090[i].f_04e].f_38 != 7 && g_7090[i].flag == 0) {
                fn_03_1542(0, 14, i, buf, 1);
                fn_10_a332(g_6078, 0xbc6, 0, g_96d2[g_7090[i].f_04e].f_38 == cls, (LPSTR)buf,
                           g_96d2[g_7090[i].f_04e].f_38 == cls);
                /* The three copies of the lstrcat tail are merged by the
                 * compiler; one shared tail (join or goto) gives other code. */
                if (g_7090[i].f_006 != 14 || g_7090[i].f_008 != i) {
                    char buf3[60];

                    LoadString(g_9212, 0x36f, buf, 40);
                    if (g_7090[i].f_006 == 14) {
                        if (g_7090[i].f_008 == main_ship) {
                            LoadString(g_9212, 0x375, buf3, 40);
                            lstrcat(buf, buf3);
                            lstrcat(buf, g_09ee);
                            lstrcat(g_6078, buf);
                            continue;
                        }
                        fn_03_1542(1, g_7090[i].f_006, g_7090[i].f_008, buf3, 1);
                        lstrcat(buf, buf3);
                        lstrcat(buf, g_09ee);
                        lstrcat(g_6078, buf);
                        continue;
                    }
                    fn_03_1542(1, g_7090[i].f_006, g_7090[i].f_008, buf3, 2);
                    lstrcat(buf, buf3);
                    lstrcat(buf, g_09ee);
                    lstrcat(g_6078, buf);
                    continue;
                }
                fn_09_95ba(rand() % 3 + 0x907);
                lstrcat(g_6078, g_09ee);
            }
        }
        idx[0] = idx[1] = idx[2] = -1;
        for (k = nfound = 0; k < 3; k++)
            for (i = score[k] = 0; i <= g_9316; i++) {
                int16_t sum;
                int16_t ok;

                if (i != main_ship && g_96d2[g_7090[i].f_04e].f_38 != 7) {
                    for (j = sum = 0; j < 8; j++)
                        sum += g_7090[i].f_0f6[main_ship][j];
                    if (score[k] < sum && i != idx[0] && i != idx[1] &&
                        g_7090[i].f_0ee[main_ship] != 3 && g_7090[i].f_0ee[main_ship] != 0) {
                        ok = 1;
                        for (j = 0; j < 8; j++)
                            if (used[j] == i)
                                ok = 0;
                        if (ok) {
                            score[k] = sum;
                            idx[k] = i;
                            nfound = k + 1;
                        }
                    }
                }
            }
        if (nfound) {
            for (i = 0; i < nfound; i++) {
                char buf3[60];
                int16_t strid;

                switch (g_7090[idx[i]].f_0ee[main_ship]) {
                case 8:
                    strid = 0x385;
                    break;
                case 7:
                    strid = 0x38b;
                    break;
                case 5:
                    strid = 0x386;
                    break;
                case 1:
                    if (g_7090[idx[i]].flag == 0 && g_7090[idx[i]].f_006 == 14 &&
                        g_7090[idx[i]].f_008 == main_ship)
                        strid = 0x37d;
                    else
                        strid = 0x384;
                    break;
                case 2:
                    strid = 0x38a;
                    break;
                case 3:
                    strid = 0x387;
                    break;
                case 4:
                    strid = 0x388;
                    break;
                case 6:
                    strid = 0x389;
                    break;
                }
                fn_03_1542(0, 14, idx[i], buf, 1);
                fn_13_218a(g_96d2[g_7090[idx[i]].f_04e].f_38, buf3);
                fn_10_a332(g_6078, 0xbc9, 0, strid, g_96d2[g_7090[idx[i]].f_04e].f_38 == cls,
                           (LPSTR)buf, g_96d2[g_7090[idx[i]].f_04e].f_38 != cls, (LPSTR)buf3);
                if ((g_7090[idx[i]].f_062 + 8)[main_ship] > 5)
                    fn_09_8838(idx[i]);
            }
        }
        fn_17_42ea(1);
        fn_17_42ea(1);
        for (i = 0; i < 2; i++) {
            val[i] = 0;
            best[i] = -1;
        }
        for (i = 0; i < 8; i++)
            for (j = has[i] = 0; j <= g_9316; j++)
                if (g_96d2[g_7090[j].f_04e].f_38 == i)
                    has[i] = 1;
        cls = g_96d2[g_7090[main_ship].f_04e].f_38;
        for (j = count = 0; j < 2; j++)
            for (i = 0; i < 8; i++) {
                if (i != cls && has[i] && (j == 0 || best[0] != i)) {
                    diff = g_3824[i][cls] - g_9350[i];
                    if (g_3824[i][cls] < -250)
                        rank[j] = 4;
                    else if (g_3824[i][cls] < -80)
                        rank[j] = 3;
                    else if (g_3824[i][cls] < 80)
                        rank[j] = 2;
                    else if (g_3824[i][cls] < 250)
                        rank[j] = 1;
                    else
                        rank[j] = 0;
                    for (k = cnt[j] = 0; k < 3; k++)
                        if (g_4eec[i][k] == g_931c && g_4fd0[i][k] == g_91f8)
                            cnt[j]++;
                    if (fn_09_88ba(diff - cnt[j] * 50) > fn_09_88ba(val[j]) || cnt[j] != 0) {
                        best2[j] = cnt[j];
                        val[j] = diff;
                        best[j] = i;
                        count++;
                    }
                }
            }
        if (count) {
            fn_09_95ba(0x9d2);
            fn_13_218a(best[0], buf);
            lstrcat(g_6078, buf);
            if (count > 1 && ((val[0] < 0 && val[1] < 0) || (val[0] > 0 && val[1] > 0) ||
                              (best2[0] != 0 && best2[1] == best2[0]))) {
                flag2 = 1;
                lstrcat(g_6078, " ");
                fn_09_95ba(0x31b);
                fn_09_95ba(0x9d2);
                fn_13_218a(best[1], buf);
                lstrcat(g_6078, buf);
            } else
                flag2 = 0;
            if (best2[0] != 0) {
                fn_09_95ba(0x395);
                if (best2[0] == 2)
                    fn_09_95ba(0x396);
                else if (best2[0] > 2)
                    fn_09_95ba(0x397);
                fn_09_95ba(0x374);
            } else {
                fn_09_95ba(0x31e);
                if (val[0] < 0)
                    fn_09_95ba(0x36e);
                else
                    fn_09_95ba(0x31f);
                fn_09_95ba(0xf8);
            }
            if (!flag2 && count > 1) {
                lstrcat(g_6078, " ");
                fn_09_95ba(0x31b);
                fn_09_95ba(0x9d2);
                fn_13_218a(best[1], buf);
                lstrcat(g_6078, buf);
                if (best2[1] != 0) {
                    if (best2[1] == 2)
                        fn_09_95ba(0x396);
                    else if (best2[1] > 2)
                        fn_09_95ba(0x397);
                    fn_09_95ba(0x374);
                } else {
                    fn_09_95ba(0x31e);
                    if (val[1] < 0)
                        fn_09_95ba(0x36e);
                    else
                        fn_09_95ba(0x31f);
                    fn_09_95ba(0xf8);
                }
            }
            lstrcat(g_6078, g_09ee);
        } else
            fn_09_95ba(0x315);
        if (g_93b6 != -1) {
            fn_17_42ea(1);
            fn_17_42ea(1);
            fn_03_1542(1, 14, fn_14_4520(g_93b6, g_9316), buf, 1);
            lstrcat(g_6078, buf);
            fn_09_95ba(0x275);
        }
    }
}

/* 9:8838 */
void fn_09_8838(int16_t n)
{
    int16_t v;
    char buf[50];

    v = g_96d2[g_7090[main_ship].f_04e].f_38;
    if (g_7090[n].flag) {
        fn_03_1542(0, 14, n, buf, 1);
        lstrcat(g_6078, buf);
        if (g_7090[n].f_0ee[main_ship] <= 5)
            fn_09_95ba(0x372);
        else
            fn_09_95ba(0x371);
        lstrcat(g_6078, ". ");
    }
}

/* 9:88ba */
int16_t fn_09_88ba(int16_t x)
{
    if (x >= 0)
        return x;
    return -x;
}

/* 9:88dc */
int32_t abs32(int32_t x)
{
    if (x >= 0)
        return x;
    return -x;
}

/* 9:8908 */
void fn_09_8908(void)
{
    fn_17_306e();
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
}

/* 9:8934 */
void draw_briefing_panel_with_esc_prompt(int16_t a)
{
    char buf[120];
    char unused[82];
    int16_t left;
    int16_t right;
    int16_t y;
    int16_t x;
    int16_t h;
    int16_t w;
    int16_t unused2;

    if (LO16(g_90ea) < 640)
        w = LO16(g_90ea) + 20;
    else
        w = min(LO16(g_90ea) - 20, 620);
    if (g_0010 < 440)
        h = g_0010 + 20;
    else
        h = min(g_0010 - 20, 460);
    g_6084.left = LO16(g_90ea) / 2 - w / 2;
    g_6084.right = g_6084.left + w;
    g_6084.top = g_0010 / 2 - h / 2;
    g_6084.bottom = g_6084.top + h - 180;
    if (g_0010 > 400)
        g_6084.top = max(g_6084.top, 15);
    g_607c.left = LO16(g_90ea) / 2 - w / 2;
    g_607c.right = g_607c.left + w;
    g_607c.top = g_6084.bottom;
    g_607c.bottom = g_607c.top + 180;
    left = max(g_6084.left, 0);
    right = min(g_6084.right, LO16(g_90ea));
    if (g_8f70 == 0 && g_90f8 == 0) {
        fn_11_1774(2, g_6084.left, g_6084.top - 15, g_6084.right, g_607c.bottom);
        fn_11_1774(-1, left, g_6084.top - 15, right, g_6084.top + 10);
        fn_11_1774(-1, left, g_607c.top + 20, right, g_607c.top + 40);
        fn_10_a332(buf, 0x9e9, 1, g_91f8);
        fn_09_8bec(g_13dc, left + 5, g_6084.top - 13, 22, 10, 0, buf);
        fn_09_955c(0x8dc, buf);
        fn_09_8bec(g_13dc, right - 7, g_6084.top - 6, 14, 0, 2, buf);
        x = g_607c.left + 15;
        y = g_607c.top + 22;
        lstrcpy(buf, g_38c8);
        fn_09_8bec(g_13dc, left + 5, y, 15, 8, 0, buf);
        if (g_91fe) {
            fn_10_a332(buf, 0x90c, 1, g_91fe, 0x9d3);
            fn_09_8bec(g_13dc, right - 5, y, 15, 8, 2, buf);
        }
    }
    g_6084.left += 6;
    g_6084.right -= 6;
    g_6084.top += 11;
    g_6084.bottom = g_607c.top + 9;
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
    g_93ae = CreateRectRgn(g_6084.left, g_6084.top, g_6084.right, g_6084.bottom);
    g_93aa = 0;
    fn_17_0000(a == 0, 1);
}

/* 9:8bec */
void fn_09_8bec(HDC hdc, int16_t x, int16_t y, int16_t size, int16_t width, UINT align, LPSTR s)
{
    HFONT old;
    HFONT font;
    char buf[80];
    COLORREF text;
    COLORREF bk;
    int16_t shadow;

    shadow = 1;
    if (size == 13) {
        size = 14;
        shadow = 0;
    }
    if (size < 14)
        shadow = 0;
    old = SelectObject(hdc, font = CreateFont(size, width, 0, 0, 600, 0, 0, 0, 0, 0, 0,
                                              2, 0x22, "Arial"));
    bk = SetBkColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);
    SetTextAlign(hdc, align);
    if (shadow) {
        text = SetTextColor(hdc, 0x02ffffffL);
        TextOut(hdc, x + 2, y + 2, s, lstrlen(s));
    }
    text = SetTextColor(hdc, 0x025a5a5aL);
    TextOut(hdc, x, y, s, lstrlen(s));
    SetBkColor(hdc, bk);
    SetTextColor(hdc, text);
    SelectObject(hdc, old);
    if (font)
        DeleteObject(font);
}

/* Types the briefing text g_4fcc one character per call (all of it with
 * quiet), wrapping words at the panel edge; returns 1 when the text has
 * ended [inferred]. */
/* 9:8d18 */
int16_t fn_09_8d18(int16_t init, int16_t quiet)
{
    HFONT oldfont;
    HFONT font;
    DWORD oldtext;
    DWORD oldbk;
    char buf[54];
    int16_t k;
    int16_t steps;
    char pad[16];
    int16_t h;
    int16_t margin;
    int16_t p;
    int16_t n;
    int16_t w;

    if (g_9460)
        return 1;
    steps = 2;
    if (init) {
        g_1830.x = g_607c.left + 25;
        g_1830.y = g_607c.top + 55;
        if (!quiet)
            fn_15_84b0(g_1830.x + 10, g_1830.y + 10);
        g_183c = g_1e50 + 500;
        g_183a = g_1838 = g_0a5a = 0;
        return 0;
    }
    if (!quiet) {
        if (g_183c > g_1e50)
            return g_0a5a;
        g_183c = g_1e50 + 50;
    } else {
        steps = 2000;
        PatBlt(g_13dc, g_607c.left + 6, g_607c.top + 55, g_607c.right - g_607c.left - 12,
               g_607c.bottom - g_607c.top - 61, BLACKNESS);
    }
    if (g_0a5a) {
        g_183c = g_1e50 + 400;
        if (g_0a5c) {
            h = SelectObject(g_13dc, CreateSolidBrush(RGB(255, 255, 0)));
            PatBlt(g_13dc, g_1830.x + 4, g_1830.y + 2, 12, 15, PATCOPY);
            DeleteObject(SelectObject(g_13dc, h));
        } else
            PatBlt(g_13dc, g_1830.x + 4, g_1830.y + 2, 12, 15, BLACKNESS);
        g_0a5c = !g_0a5c;
        return g_0a5a;
    }
    font = CreateFont(17, 11, 0, 0, 520, 0, 0, 0, 0, 0, 0, PROOF_QUALITY,
                      VARIABLE_PITCH | FF_SWISS, "Arial");
    oldfont = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, 0);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    oldtext = SetTextColor(g_13dc, RGB(255, 255, 0));
    for (k = 0; k < steps; k++) {
        h = 0;
        if (g_4fcc[g_1838] == ' ') {
            n = 0;
            p = g_1838;
            do
                buf[++n] = g_4fcc[++p];
            while (g_4fcc[p] != 0 && g_4fcc[p] != ' ' && g_4fcc[p] != 13);
            buf[n + 1] = 0;
            w = GetTextExtent(g_13dc, buf, n) + g_1830.x;
            if (n > 5)
                margin = 9;
            else
                margin = 22;
            if (g_6084.right - margin < w)
                h = 1;
        }
        if (g_4fcc[g_1838] == 13 || h) {
            g_1830.x = g_607c.left + 25;
            g_1830.y += 25;
            if (g_4fcc[g_1838] == 13)
                g_1838++;
        } else {
            if (g_1838 != 0)
                PatBlt(g_13dc, g_1834.x + 4, g_1834.y + 2, 12, 15, BLACKNESS);
            TextOut(g_13dc, g_1830.x, g_1830.y, g_4fcc + g_1838, 1);
            g_1830.x += GetTextExtent(g_13dc, g_4fcc + g_1838, 1);
            if (!quiet) {
                w = SelectObject(g_13dc, CreateSolidBrush(RGB(255, 255, 0)));
                PatBlt(g_13dc, g_1830.x + 4, g_1830.y + 2, 12, 15, PATCOPY);
                DeleteObject(SelectObject(g_13dc, w));
            }
            g_1834 = g_1830;
        }
        g_1838++;
        if (!quiet)
            ((void (*)(int16_t, POINT, int16_t))fn_10_754a)(0x2b, g_1834, 4);
        if (g_4fcc[g_1838] == 13 && g_4fcc[g_1838 - 1] == 10) {
            g_183c = g_1e50 + 2000;
            break;
        }
        if (g_4fcc[g_1838] == 0) {
            g_0a5a = 1;
            break;
        }
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
    return g_0a5a;
}

/* 9:90fe */
BOOL fn_09_90fe(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    RECT r;
    int16_t w;
    int16_t h;
    char buf[80];

    switch (msg) {
    case WM_INITDIALOG:
        GetWindowRect(hDlg, &r);
        w = r.right - r.left;
        h = r.bottom - r.top;
        if (g_9518) {
            fn_09_955c(0x8dd, buf);
            SetWindowText(GetDlgItem(hDlg, 0x72), buf);
        }
        MoveWindow(hDlg, GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2,
                   GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2, w, h, TRUE);
        break;
    }
    return FALSE;
}

/* 9:94ba */
void fn_09_94ba(void)
{
    int16_t i;

    for (i = 0; i < 8; i++) {
        if ((g_69f4[g_94a2].f_1c0 + 8)[i])
            fn_07_2512(i, (g_69f4[g_94a2].f_1c0 + 8)[i] - 1);
        if ((g_69f4[g_94a2].f_1c0 + 8)[i] == 2)
            g_1df8[0][i].f_2f = (char)0x9c;
        if (g_9320 == 2 && (g_9334 == 0 || rand() % 3 == 0))
            fn_07_2512(i, 0);
    }
}

/* 9:955c */
int16_t fn_09_955c(UINT id, LPSTR buf)
{
    return LoadString(g_9212, id, buf, 160);
}

/* 9:9580 */
void fn_09_9580(UINT id, LPSTR dst)
{
    char buf[200];

    LoadString(g_9212, id, buf, 199);
    lstrcat(dst, buf);
}

/* 9:95ba */
void fn_09_95ba(UINT id)
{
    char buf[200];

    LoadString(g_9212, id, buf, 199);
    lstrcat(g_6078, buf);
}

/* 9:95f4 */
void fn_09_95f4(UINT id)
{
    char buf[100];

    LoadString(g_9212, id, ambulance_line, 90);
}

/* 9:961a */
void fn_09_961a(UINT id)
{
    char buf[100];

    LoadString(g_9212, id, buf, 90);
    lstrcat(ambulance_line, buf);
}

/* Resets the race/session state and builds the level objects [inferred]. */
/* 9:6624 */
void fn_09_6624(void)
{
    int16_t i;
    int16_t j;
    char unused[40];

    if (g_93b0)
        return;
    g_93b0 = 1;
    if (g_934c) {
        g_8f64 = 0;
        DestroyWindow(g_934c);
        g_934c = 0;
    }
    if (g_90f4 != 3 && g_934c == 0)
        g_934c = CreateDialog(g_9212, MAKEINTRESOURCE(0x65), (HWND)g_0016, fn_09_90fe);
    g_5014 = g_1e68 = 0;
    g_9510 = 0x65;
    for (i = 0; i < g_92ec[6]; i++) {
        g_6670[i + 4].r.right = 0x191;
        g_1df8[6][i].f_18 = 1;
    }
    for (i = 0; i < g_92ec[10]; i++) {
        g_1df8[10][i].f_18 = 1;
        g_65cc[i].f_04 = g_65cc[i].f_00 = -1;
    }
    for (i = 0; i < 4; i++)
        g_221c[i].type = -1;
    g_9430 = g_9456 = 0;
    for (i = 0; i < 9; i++) {
        g_6098[i].z[1][5] = -1;
        g_6098[i].z[1][4] = 50;
    }
    for (i = 0; i < 45; i++)
        g_1e90[i].f_00 = -1;
    for (i = 0; i < 20; i++)
        g_58bc[i].f_10 = -1;
    for (i = 0; i < g_92ec[6]; i++)
        g_6670[i + 4].f_04.x = -1;
    for (i = 0; i < g_92ec[g_9328]; i++) {
        g_5a4c[i].f_00 = -1;
        g_1df8[g_9328][i].f_18 = 1;
    }
    for (i = 0; i < 10; i++)
        for (j = 0; j < 4; j++) {
            g_5b28[i][j].f_0c = 0;
            g_5b28[i][j].q.y = -100;
            g_5b28[i][j].q.x = -100;
        }
    g_9e49 = 10;
    g_9492 = g_9494 = 1;
    for (i = 0; i < g_9406[3]; i++)
        fn_10_0864(i);
    for (i = 0; i < g_9406[9]; i++)
        fn_10_0a26(i);
    g_9600 = 1;
    for (i = 0; i < g_9406[4]; i++)
        fn_09_0df6(i);
    fn_09_10d4();
    g_1e50 = GetCurrentTime();
    g_9e45 = g_9e4b = g_9e5b = 0;
    g_9e49 = 10;
    g_1df8[7][0].f_18 = 1;
    g_9406[7] = 0;
    fn_14_3eda();
    fn_14_0000(-1);
    fn_14_4074();
    g_9140 = 1;
    for (i = 0; i <= 14; i++)
        for (j = 0; j < g_92ec[i]; j++) {
            g_1df8[i][j].f_12 = g_1df8[i][j].f_24;
            g_1df8[i][j].f_2e = 0;
            g_1df8[i][j].f_32 = -1;
            g_1df8[i][j].f_36 = -1;
        }
    if (g_9320 == 6) {
        fn_09_6db0();
        fn_10_754a(0x4f, 0, 0, 5);
        fn_10_754a(0x28, 0, 0, 5);
        fn_10_754a(0x42, 0, 0, 5);
    }
    g_1e6c = g_1e50 + 10000;
    g_6da8 = 0;
    if (g_91f8 == 1 || g_92e4 != 0) {
        fn_11_ae94();
        fn_11_2f8c();
    }
    g_8e2c = 0;
    if (g_934c) {
        g_8f64 = 0;
        DestroyWindow(g_934c);
        g_934c = 0;
    }
    g_9378 = g_9134;
    g_103a = g_92e4 = 0;
}

/* Builds the generated briefing text in g_4fcc: mission intro, up to three
 * objectives and the count of hostile racers [inferred]. */
/* 9:91b0 */
void fn_09_91b0(void)
{
    char buf[90];
    int16_t hostile;
    int16_t best[3];
    int16_t pick[3];
    int16_t count;
    int16_t i;
    int16_t j;
    int16_t saved;
    int16_t v;
    int16_t kind[3];
    int16_t arg[3];
    int16_t ok;

    lstrcpy((LPSTR)g_4fcc, "");
    switch (g_9320) {
    case 0:
        fn_09_9580(0x4a5, (LPSTR)g_4fcc);
        break;
    case 2:
        if (g_1df8[0][0].f_53 == 2)
            fn_09_9580(0x7ce, (LPSTR)g_4fcc);
        else
            fn_09_9580(0x4a6, (LPSTR)g_4fcc);
        break;
    case 4:
        fn_09_9580(0x4a7, (LPSTR)g_4fcc);
        break;
    case 3:
        fn_09_9580(0x4a8, (LPSTR)g_4fcc);
        break;
    case 5:
        fn_09_9580(0x4a9, (LPSTR)g_4fcc);
        break;
    }
    if (g_9320 != -1)
        lstrcat((LPSTR)g_4fcc, " ");
    saved = g_933a[0];
    g_933c += saved;
    for (i = g_933a[0] = 0; i < 3; i++) {
        best[i] = 0;
        pick[i] = -1;
    }
    for (j = count = 0; j < 3; j++) {
        for (i = 0; i < 6; i++) {
            ok = 1;
            if (j > 0) {
                if (i == pick[0])
                    ok = 0;
                if (j > 1 && i == pick[1])
                    ok = 0;
            }
            switch (i) {
            case 4:
                v = g_4ee0[0];
                break;
            default:
                v = g_933a[i];
                break;
            case 5:
                v = g_4ee0[1];
                break;
            case 1:
                v = 0;
                break;
            }
            if (ok && best[j] < v) {
                count = j + 1;
                pick[j] = i;
                best[j] = v;
            }
        }
    }
    if (count < 3) {
        if (g_933c > 15 || (count == 0 && g_933c > 0)) {
            count++;
            pick[count - 1] = 1;
        }
    } else if (pick[count - 1] != 3 && best[count - 1] < g_933c && g_933c > 15)
        pick[count - 1] = 1;
    for (i = 0; i < 3; i++)
        kind[i] = 0;
    for (i = 0; i < count; i++) {
        switch (pick[i]) {
        case 1:
            kind[i] = 3;
            arg[i] = 0;
            break;
        case 2:
            kind[i] = 8;
            arg[i] = g_9318 * 2;
            break;
        case 3:
            kind[i] = 9;
            arg[i] = 0;
            break;
        case 4:
            kind[i] = 8;
            arg[i] = g_9318 * 2 + g_933e;
            break;
        case 5:
            kind[i] = 8;
            arg[i] = g_9318 * 2 + g_4ee6 + g_4ee4 + g_4ee0[0];
            break;
        }
    }
    if (kind[2] == 0 && kind[1] == 0 && kind[0] == 0)
        fn_09_9580(0x4a5, (LPSTR)g_4fcc);
    else
        fn_10_a332((LPSTR)g_4fcc, 0xbdc, 0, kind[2], kind[2], arg[2], 7, kind[1], kind[1], arg[1], 7,
                   kind[0], kind[0], arg[0], 7);
    g_933a[0] = saved;
    g_933c -= saved;
    for (i = hostile = 0; i <= g_9316; i++)
        if ((g_7090[i].f_062 + 8)[main_ship] && g_7090[i].f_0ee[main_ship] <= 5)
            hostile++;
    if (hostile)
        fn_10_a332((LPSTR)g_4fcc, 0xbdd, 0, hostile, 0x9ea);
}
