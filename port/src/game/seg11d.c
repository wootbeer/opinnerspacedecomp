/* INSPACE.EXE segment 11 (selector 1050): functions that near-call some
 * of seg11.c's functions but far-call others (11:1bcc far-calls 11:4c72,
 * 11:aece far-calls 11:3cc2 and 11:2f8c), so they cannot share seg11.c. */
#include "game.h"

/* 0xad-byte records; lowest field seen at DS:96ea [inferred]. */

/* Periodic update of the ships' energy [inferred]. */
/* 11:1bcc */
void fn_11_1bcc(void)
{
    int16_t i;
    int16_t v;
    int16_t unused;

    if (g_5018 != g_1e58)
        fn_11_04a0(0);
    if (g_1854 < g_1e50) {
        g_1854 = g_1e50 + 300;
        g_93fe = g_93fe == 0;
        fn_11_04a0(1);
    }
    if ((int16_t)(g_1e68 / 36) != g_934e)
        fn_11_04a0(7);
    if (g_5074 < g_1e50) {
        g_5074 = g_1e50 + 1000;
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].f_002) {
                v = g_7090[i].f_00c / -40 - g_7090[i].f_0e8 * 5 + g_7090[i].f_01e;
                g_7090[i].f_01e = v < 0 ? 0 : v;
            } else {
                v = g_7090[i].f_01e - g_7090[i].f_0e8 * 5;
                g_7090[i].f_01e = v < 0 ? 0 : v;
            }
            if (g_7090[i].f_0e8) {
                g_7090[i].f_01e -= 3;
                if (g_7090[i].f_01e < 0x78) {
                    fn_11_4c72(i);
                    fn_03_332e(0x409, 0x418);
                }
            }
            if (g_7090[i].f_0b8[g_7090[i].f_018] == 3) {
                if (i == main_ship)
                    g_1df8[g_9324][i].f_50 += (0x6d - g_1df8[g_9324][i].f_50) / 2;
                else
                    g_1df8[g_9324][i].f_50 += (0x6d - g_1df8[g_9324][i].f_50) / 5;
            }
            g_1df8[g_9324][i].f_44 = g_7090[i].f_01e / 20 + g_96d2[g_7090[i].f_04e].f_32;
        }
        fn_11_04a0(6);
        fn_13_2dcc();
    }
    fn_11_1d7c();
}

/* Switch control to the next ship of the same side [inferred]. */
/* 11:aece */
int16_t fn_11_aece(void)
{
    int16_t start;
    int16_t cand;
    int16_t tmp;
    int16_t ok;
    OBJREF r;

    if (g_9320 == 6 || g_9320 == 7)
        return 0;
    ok = g_1032 = 0;
    start = main_ship;
    if (g_1df8[g_9324][start].f_18 != 0)
        return 0;
    if (g_92e8 != 0)
        return 0;
    do {
        if (main_ship < g_9316)
            main_ship++;
        else
            main_ship = 0;
        ok = 1;
        if (g_1df8[g_9324][main_ship].f_18 != 0 || g_7090[main_ship].flag == 0)
            ok = 0;
        if (start == main_ship)
            ok = 1;
        else if (g_96d2[g_7090[main_ship].f_04e].f_38 != g_96d2[g_7090[start].f_04e].f_38)
            ok = 0;
    } while (!ok);
    if (start == main_ship)
        return 0;
    cand = main_ship;
    main_ship = start;
    tmp = g_7090[cand].f_0d0;
    g_7090[cand].f_0d0 = g_7090[main_ship].f_0d0;
    g_7090[main_ship].f_0d0 = tmp;
    tmp = g_7090[cand].f_0d2;
    g_7090[cand].f_0d2 = g_7090[main_ship].f_0d2;
    g_7090[main_ship].f_0d2 = tmp;
    fn_03_06ec(main_ship, g_9324, cand, 0x71);
    main_ship = cand;
    g_96d2[g_7090[cand].f_04e].f_42 = 1;
    r = objref_of(fn_13_2206());
    fn_03_00f4(main_ship, r.type, r.idx);
    fn_08_4d60(&g_7090[cand].f_0d6, &g_7090[main_ship].f_0d6);
    g_931c = g_7090[main_ship].f_0d6;
    g_1e80 = g_1e84 = 0;
    g_9134 = 1;
    if (g_951a == 0)
        VIEW(int32_t, g_6b50, 0) = VIEW(int32_t, g_1df8[g_9324][start].f_04, 0);
    g_951a = 1;
    fn_11_3cc2(main_ship);
    fn_11_ae94();
    fn_11_2f8c();
    return 1;
}
