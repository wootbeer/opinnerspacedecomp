/* INSPACE.EXE segment 18 (selector 1088). */
#include "game.h"

/* 18:034c */
void fn_18_034c(void)
{
    if (g_9668) {
        SelectClipRgn(g_13dc, g_9668);
        g_9672 = 1;
    }
}

/* 18:0378 */
void fn_18_0378(int16_t demon)
{
    int32_t unused;

    g_8d34 = 0;
    g_965e = g_9660 = 0;
    if (demon) {
        subgame_active = 1;
        sprite_dc_release();
    }
    fn_13_65f2(3);
    fn_11_02f0();
    lstrcpy(g_6da4->f_08, "Inner Demon");
    if (g_90f4 != 6)
        g_9530 = 1;
}

/* Creates the eight solid brushes [inferred]. */
/* 18:0b1e */
void fn_18_0b1e(void)
{
    if (!g_88d8[0]) {
        g_88d8[0] = CreateSolidBrush(RGB(255, 0, 0));
        g_88d8[1] = CreateSolidBrush(RGB(128, 0, 0));
        g_88d8[2] = CreateSolidBrush(RGB(255, 255, 0));
        g_88d8[3] = CreateSolidBrush(RGB(128, 128, 0));
        g_88d8[4] = CreateSolidBrush(RGB(0, 255, 255));
        g_88d8[5] = CreateSolidBrush(RGB(0, 128, 128));
        g_88d8[6] = CreateSolidBrush(RGB(255, 255, 255));
        g_88d8[7] = CreateSolidBrush(RGB(192, 192, 192));
    }
}

/* 18:0ba0 */
void fn_18_0ba0(void)
{
    int16_t i;

    for (i = 0; i < 8; i++) {
        if (g_88d8[i]) {
            DeleteObject(g_88d8[i]);
            g_88d8[i] = 0;
        }
    }
}

/* 18:0d4e */
void fn_18_0d4e(int16_t msg, int16_t key, LPARAM lp)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 == 1 && g_1318 <= 1)
                    g_9530 = 2;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* 18:633c */
void fn_18_633c(void)
{
    int16_t i;

    g_a1cf = g_a1cd = 0;
    for (i = 0; i < 4; i++)
        g_a18f[i] = g_a193[i] = 1;
}

/* 18:1784 */
void fn_18_1784(int16_t left, int16_t top, int16_t right, int16_t bottom)
{
    DWORD org;

    if (g_90f4 != 1) {
        if (g_9668) {
            DeleteObject(g_9668);
            g_9668 = 0;
        }
        org = GetWindowOrg(g_13dc);
        g_88ec = LOWORD(org);
        g_88ee = HIWORD(org);
        g_88ec = -g_88ec;
        g_88ee = -g_88ee;
        g_9668 = CreateRectRgn(left + g_88ec, top + g_88ee,
                               right + g_88ec, bottom + g_88ee);
    }
}

/* 18:1e46 */
void fn_18_1e46(void)
{
    int16_t i;

    for (i = 15; i <= 20; i++) {
        if (g_9100[i]) {
            if (g_1df8[i]) {
                GlobalUnlock(g_9100[i]);
                g_1df8[i] = 0;
            }
            GlobalFree(g_9100[i]);
            g_9100[i] = 0;
        }
    }
}

/* 18:0be2 */
void fn_18_0be2(void)
{
    int16_t i;

    if (g_6da4)
        g_6da4->f_1c = 1;
    for (i = 0; i < 4; i++)
        g_7090[main_ship].f_026[i] = g_a172[i];
    g_7090[main_ship].f_01e = g_a176 * 10;
    g_7090[main_ship].f_024 = g_a177;
    g_7090[main_ship].f_0ac = g_a178;
    g_7090[main_ship].f_0ad = g_a179;
    g_7090[main_ship].flag = g_a17a;
}

/* 18:1dd0 */
int16_t fn_18_1dd0(void)
{
    int16_t i;

    for (i = 15; i <= 20; i++) {
        if ((g_9100[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x70L)) == 0)
            return 0;
        if ((g_1df8[i] = (REC_70 *)GlobalLock(g_9100[i])) == 0) {
            GlobalFree(g_9100[i]);
            return 0;
        }
    }
    return 1;
}

/* Moves object (type << 8 | idx) to its scaled map position and redraws
 * it from src: erases the uncovered part of the old square, then blits
 * the new one [inferred]. */
/* 18:1934 */
int16_t fn_18_1934(int16_t key, int16_t unused, HDC src)
{
    int16_t type;
    int16_t idx;
    int16_t u0;
    int16_t u5;
    int16_t u1;
    POINT d;
    int16_t u2;
    int16_t u3;
    int16_t u4;

    type = (uint8_t)(key >> 8);
    idx = (uint8_t)key;
    g_1df8[type][idx].f_08.x = g_1df8[type][idx].f_00.x;
    g_1df8[type][idx].f_08.y = g_1df8[type][idx].f_00.y;
    g_1df8[type][idx].f_00.x =
        (int16_t)((int32_t)g_1df8[type][idx].f_04.x * g_88c0.x / g_88cc) + g_88c4.x;
    g_1df8[type][idx].f_00.y =
        (int16_t)((int32_t)g_1df8[type][idx].f_04.y * g_88c0.x / g_88cc) + g_88c4.y;
    if (type != 15) {
        g_1df8[type][idx].f_00.x += g_2390;
        g_1df8[type][idx].f_00.y += g_2392;
    }
    d.x = g_1df8[type][idx].f_00.x - g_1df8[type][idx].f_08.x;
    d.y = g_1df8[type][idx].f_00.y - g_1df8[type][idx].f_08.y;
    if (g_1df8[type][idx].f_24 < fn_09_88ba(d.x)
        || g_1df8[type][idx].f_24 < fn_09_88ba(d.y)) {
        if (fn_09_88ba(d.x) < g_1df8[type][idx].f_22
            && fn_09_88ba(d.y) < g_1df8[type][idx].f_22) {
            if (d.x < 0) {
                if (d.y < 0) {
                    PatBlt(g_13dc, g_1df8[type][idx].f_22 + g_1df8[type][idx].f_00.x,
                           g_1df8[type][idx].f_00.y, -d.x,
                           g_1df8[type][idx].f_22 - d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                           g_1df8[type][idx].f_00.y + g_1df8[type][idx].f_22,
                           g_1df8[type][idx].f_22, -d.y, BLACKNESS);
                } else {
                    PatBlt(g_13dc, g_1df8[type][idx].f_22 + g_1df8[type][idx].f_00.x,
                           g_1df8[type][idx].f_00.y - d.y, -d.x,
                           g_1df8[type][idx].f_22 + d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                           g_1df8[type][idx].f_00.y - d.y,
                           g_1df8[type][idx].f_22, d.y, BLACKNESS);
                }
            } else {
                if (d.y < 0) {
                    PatBlt(g_13dc, g_1df8[type][idx].f_00.x - d.x,
                           g_1df8[type][idx].f_00.y, d.x,
                           g_1df8[type][idx].f_22 - d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                           g_1df8[type][idx].f_00.y + g_1df8[type][idx].f_22,
                           g_1df8[type][idx].f_22, -d.y, BLACKNESS);
                } else {
                    PatBlt(g_13dc, g_1df8[type][idx].f_00.x - d.x,
                           g_1df8[type][idx].f_00.y - d.y, d.x,
                           g_1df8[type][idx].f_22 + d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                           g_1df8[type][idx].f_00.y - d.y,
                           g_1df8[type][idx].f_22, d.y, BLACKNESS);
                }
            }
        } else
            PatBlt(g_13dc, g_1df8[type][idx].f_08.x, g_1df8[type][idx].f_08.y,
                   g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, BLACKNESS);
        BitBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
               g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, src,
               g_1df8[type][idx].f_10, g_1df8[type][idx].f_12, SRCCOPY);
    } else {
        BitBlt(g_13dc, g_1df8[type][idx].f_00.x - (d.x < 0 ? 0 : d.x), g_1df8[type][idx].f_00.y - (d.y < 0 ? 0 : d.y),
               fn_09_88ba(d.x) + g_1df8[type][idx].f_22,
               fn_09_88ba(d.y) + g_1df8[type][idx].f_22, src,
               g_1df8[type][idx].f_10 - (d.x < 0 ? 0 : d.x), g_1df8[type][idx].f_12 - (d.y < 0 ? 0 : d.y),
               SRCCOPY);
    }
    return 1;
}

/* 18:17f6 */
void fn_18_17f6(void)
{
    int16_t unused1;
    int16_t unused2;

    g_9672 = 0;
    PatBlt(g_13dc, 0, 0, g_88c0.x, g_88c0.y + g_88ea, BLACKNESS);
    fn_18_1cbe(1);
    fn_18_034c();
    PatBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
           7 << g_9156 * 2, 7 << g_9156 * 2, BLACKNESS);
    if (g_1318 <= 1) {
        BitBlt(g_13dc, g_88f4[0].x, g_88f4[0].y, g_9678, g_9678,
               g_966a, 0, g_9678, SRCCOPY);
        BitBlt(g_13dc, g_88f4[1].x, g_88f4[1].y, g_9678, g_9678,
               g_966a, g_9678, g_9678, SRCCOPY);
        BitBlt(g_13dc, g_88f4[2].x, g_88f4[2].y, g_9678, g_9678,
               g_966a, g_9678, 0, SRCCOPY);
        BitBlt(g_13dc, g_88f4[3].x, g_88f4[3].y, g_9678, g_9678,
               g_966a, 0, 0, SRCCOPY);
    }
    g_1df8[15]->f_10 = (g_1df8[15]->f_22 + g_1df8[15]->f_24) * g_1df8[15]->f_28 + g_1df8[15]->f_24;
    g_1df8[15]->f_12 = g_1df8[15]->f_24;
    fn_18_1934(0xf00, 1, g_3a36);
}

/* Draws the two score lines when they changed [inferred]. */
/* 18:1cbe */
void fn_18_1cbe(int16_t force)
{
    char buf[80];

    if ((g_1ca2 != g_a1cd || force) && !g_9672) {
        g_1ca2 = g_a1cd;
        g_1ca4 = g_a1cf;
        if (force)
            PatBlt(g_13dc, 0, g_88c0.y, g_88e8, g_88ea, BLACKNESS);
        if (!g_9156) {
            LoadString(g_9212, 0x7f0, buf, 80);
            if (g_a1cd) {
                fn_06_0f1a(g_a1cd, g_a1d5);
                lstrcat(buf, g_a1d5);
            } else
                lstrcat(buf, "0");
            fn_10_94c4(2, 0, PALETTERGB(255, 128, 0), 0, g_88c0.y, buf);
            LoadString(g_9212, 0x7f1, buf, 80);
            fn_06_0f1a(g_a1cf, g_a1d5);
            lstrcat(buf, g_a1d5);
            fn_10_94c4(2, 2, PALETTERGB(0, 255, 0), g_88c0.x - 6, g_88c0.y, buf);
        }
    }
}

/* 18:5220 */
void fn_18_5220(int16_t a)
{
    int16_t i;

    if (g_90f4 == 1) {
        g_8d34 = GetCurrentTime() + 4000;
        fn_12_6d64(main_ship, a + 0x16);
        fn_10_744c(0x66);
    } else {
        g_a1cd += 10;
        g_a1d3++;
        fn_10_744c(0x25);
    }
    g_1df8[18]->f_1a = 0;
    g_942a = 0;
    for (i = 0; i < 12; i++)
        fn_06_7c14();
    if (g_90f4 == 6)
        fn_18_52a0();
}

/* 18:52a0 */
void fn_18_52a0(void)
{
    int16_t ok;
    int16_t i;

    ok = 1;
    for (i = 0; i < 4; i++)
        if (g_a18f[i])
            ok = 0;
    if (ok) {
        for (i = 0; i < 45; i++)
            g_1e90[i].f_00 = -1;
        for (i = 0; i < 9; i++)
            g_6098[i].z[1][5] = -1;
        for (i = 0; i < 20; i++)
            g_58bc[i].f_10 = -1;
        g_9510 = 100;
        g_a1cf++;
        fn_10_7480(-2, 1);
        fn_18_17f6();
        fn_18_1cbe(1);
        g_88d0 = 2;
    }
}

/* 18:591c */
void fn_18_591c(void)
{
    if (g_238c) {
        fn_10_754a(8, rand() % LO16(g_90ea), rand() % HI16(g_90ea), 4);
        g_2390 += g_238c;
        g_2392 += g_238e;
        g_2390 += rand() % 3 - 2;
        g_2392 += rand() % 3 - 2;
        if (g_2390 > 5)
            g_238c = -9;
        else if (g_2390 < -5)
            g_238c = 9;
        if (g_2392 > 5)
            g_238e = -6;
        else if (g_2392 < -5)
            g_238e = 6;
        if (g_2408 < g_1e50)
            g_238c = 0;
        if (g_90f4 == 6) {
            g_2390 >>= 1;
            g_2392 >>= 1;
        }
    } else {
        VIEW(int32_t, g_2390, 0) = 0;   /* clears g_2390 and g_2392 in one dword store */
    }
}

/* 18:5f74 */
void fn_18_5f74(void)
{
    int16_t x;
    int16_t t;

    fn_10_744c(0x48);
    g_1df8[g_9324][main_ship].f_0e = 0;
    g_1df8[g_9324][main_ship].f_0c = g_1df8[g_9324][main_ship].f_0e;
    g_1318 = 2;
    t = ((int16_t)(HI16(g_90ea) * 4) / 3 - 1100) / 36 + 164;
    x = min((int16_t)(LO16(g_90ea) - t) / 2 - 20, 260);
    g_8d14 = x - 18;
    g_8d16 = 164;
    g_8d1a = min(g_0010 * 2 / 5, g_0010 - 370);
    g_8d18 = max((int16_t)(LO16(g_90ea) / -13 - x + LO16(g_90ea) / 2 - 90), 0);
}

/* 18:0c5c */
void fn_18_0c5c(void)
{
    int16_t i;

    for (i = 0; i < 4; i++)
        g_a172[i] = (uint8_t)g_7090[main_ship].f_026[i];
    g_a176 = g_7090[main_ship].f_01e / 10;
    g_a177 = (uint8_t)g_7090[main_ship].f_024;
    g_a178 = g_7090[main_ship].f_0ac;
    g_a179 = g_7090[main_ship].f_0ad;
    g_a17a = g_7090[main_ship].flag;
    for (i = 0; i < 4; i++)
        g_7090[main_ship].f_026[i] = g_6e24[g_7090[main_ship].f_0d6].f_38[i];
    g_7090[main_ship].f_01e = 40 * g_6e24[g_7090[main_ship].f_0d6].f_1c;
    g_7090[main_ship].f_024 = g_6e24[g_7090[main_ship].f_0d6].f_74;
    g_7090[main_ship].f_0ac = g_6e24[g_7090[main_ship].f_0d6].f_72;
    g_7090[main_ship].f_0ad = g_6e24[g_7090[main_ship].f_0d6].f_73;
    g_7090[main_ship].flag = 1;
}

/* 18:337c */
void fn_18_337c(void)
{
    g_1df8[15]->f_20 = (int16_t)(g_1df8[15]->f_22 * g_88cc / g_88c0.x);
    g_1df8[15]->f_04.x = (int16_t)g_88cc / 2 - g_1df8[15]->f_20 / 2;
    g_1df8[15]->f_04.y = (int16_t)(g_88c0.y * g_88cc / g_88c0.x) / 2 - g_1df8[15]->f_20 / 2;
    g_1df8[15]->f_00.x = g_88c0.x / 2 - g_1df8[15]->f_22 / 2;
    g_1df8[15]->f_08.x = g_1df8[15]->f_00.x;
    g_1df8[15]->f_00.y = g_88c0.y / 2 - g_1df8[15]->f_22 / 2;
    g_1df8[15]->f_08.y = g_1df8[15]->f_00.y;
    g_1df8[15]->f_0c = 0;
    g_1df8[15]->f_0e = 0;
}

/* 18:4faa */
void fn_18_4faa(int16_t k)
{
    POINT pt;
    int16_t r;

    if (k == 0 || k == 3)
        pt.x = g_8870[k].f_00.right + 2;
    else
        pt.x = g_8870[k].f_00.left - 2;
    pt.y = (g_8870[k].f_00.bottom - g_8870[k].f_00.top) / 2 + g_8870[k].f_00.top;
    r = (int16_t)((4 - k) * 4) % 16;
    g_1df8[18]->f_04 = fn_08_2bbe(pt);
    g_1df8[18]->f_0c = g_1050[r].x * 5;
    g_1df8[18]->f_0e = g_1050[r].y * 5;
    g_1df8[18]->f_28 = k;
    g_1df8[18]->f_1a = 1;
    g_1df8[18]->f_18 = 1;
    g_1df8[18]->f_24 = 0;
    g_942a = 1;
    fn_10_744c(0x6e);
    fn_06_84fc((rand() % 2 + 1) * 10, 0, 0, 0, 0, 0, 0, 0, 400, k);
}

/* 18:07b2 */
void fn_18_07b2(void)
{
    int16_t b;
    int16_t a;
    int16_t i;

    g_7090[main_ship].f_0ac = g_6e24[g_7090[main_ship].f_0d6].f_72;
    g_7090[main_ship].f_0ad = g_6e24[g_7090[main_ship].f_0d6].f_73;
    a = g_7090[main_ship].f_0ac;
    b = g_7090[main_ship].f_0ad;
    g_9156 = g_959e;
    fn_10_1eb6(main_ship);
    fn_10_0552(0x22, 1);
    fn_10_0552(0xc, 1);
    fn_10_0552(0xa, 1);
    fn_10_5102();
    fn_10_5202();
    fn_10_5c42();
    fn_16_3784(main_ship, 2);
    for (i = 0; i <= g_9316; i++)
        fn_10_5d3c(i);
    if (g_7090[main_ship].f_0e4 && g_96d2[g_7090[main_ship].f_04e].f_28 == 3) {
        if (!a)
            fn_08_2cd8(main_ship, 0);
        if (!b)
            fn_08_2cd8(main_ship, 1);
    }
}

/* Resets the Demon sub-game objects and their arrays [inferred]. */
/* 18:1eac */
void fn_18_1eac(void)
{
    int16_t i;
    int16_t j;
    int16_t k;

    g_9424 = g_930a = 1;
    g_930e = g_942c = g_9312 = g_942a = g_9428 = 0;
    g_942e = g_9314 = g_9316 + 1;
    for (i = 15; i <= 20; i++) {
        GlobalUnlock(g_9100[i]);
        g_9100[i] = GlobalReAlloc(g_9100[i], (int32_t)max(g_92ec[i], 1) * 0x70, GHND);
        g_1df8[i] = (REC_70 *)GlobalLock(g_9100[i]);
    }
    g_1df8[17]->f_44 = 120;
    g_1df8[17]->f_42 = 100;
    g_1df8[17]->f_4c = 0xff;
    g_1df8[17]->f_62 = fn_11_3914;
    g_1df8[17]->f_5e = fn_07_570a;
    g_1df8[17]->f_53 = 0;
    g_1df8[17]->f_54 = 0;
    g_1df8[18]->f_44 = 100;
    g_1df8[18]->f_42 = 100;
    g_1df8[18]->f_4c = 0xff;
    g_1df8[18]->f_62 = fn_11_3914;
    g_1df8[18]->f_5e = fn_07_570a;
    g_1df8[18]->f_53 = 0;
    g_1df8[18]->f_54 = 0;
    g_1df8[18]->f_18 = 1;
    g_1df8[18]->f_1a = 0;
    g_1df8[15]->f_44 = 1000;
    g_1df8[15]->f_18 = 0;
    g_1df8[15]->f_42 = 18;
    g_1df8[15]->f_46 = 6;
    g_1df8[15]->f_2c = 500;
    g_1df8[15]->f_48 = 10;
    g_1df8[15]->f_5e = fn_07_2652;
    g_1df8[15]->f_66 = fn_12_274a;
    g_1df8[15]->f_53 = 0;
    g_1df8[15]->f_54 = 1;
    g_1df8[15]->f_2f = 7;
    g_1df8[16]->f_44 = 20000;
    g_1df8[16]->f_18 = 1;
    g_1df8[16]->f_1a = 0;
    g_1df8[16]->f_42 = 6;
    g_1df8[16]->f_54 = 1;
    g_1df8[16]->f_22 = 2;
    g_1df8[16]->f_0e = 0;
    g_1df8[16]->f_0c = g_1df8[16]->f_0e;
    g_1df8[16]->f_46 = 1;
    g_1df8[16]->f_62 = fn_11_39d8;
    g_1df8[16]->f_5e = fn_07_5090;
    for (i = g_9326; i <= g_9324; i++)
        for (j = 0; j < g_92ec[i]; j++) {
            g_1df8[i][j].f_12 = g_1df8[i][j].f_24;
            g_1df8[i][j].f_2e = 0;
            g_1df8[i][j].f_32 = -1;
            g_1df8[i][j].f_36 = -1;
        }
    for (i = k = 0; i < 4; i++)
        g_a18f[i] = 1;
    for (i = 0; i < 4; i++) {
        for (j = 0; j <= g_7090[main_ship].cnt; j++) {
            if (g_90f4 == 1) {
                if (g_7090[main_ship].f_0b8[j] == 0x1a)
                    g_a18f[2] = g_a18f[3] = 0;
                else if (g_7090[main_ship].f_0b8[j] - i == 0x16)
                    g_a18f[i] = 0;
            }
        }
        if (g_90f4 == 6 && !g_a193[i]) {
            g_a18f[i] = 0;
            k++;
        }
    }
    if (k > 3)
        fn_18_633c();
    g_a198 = 0;
    if (g_90f4 == 1) {
        for (i = 0; i < 4; i++)
            if (!g_a18f[i])
                g_a198++;
    } else
        g_a198 = min(g_a1cf, 3);
    for (i = 0; i < 4; i++)
        if (g_a18f[i]) {
            g_a16a[i] = 0;
            g_a17b[i] = 5;
        }
    for (i = 0; i < 4; i++)
        g_a17f[i] = -1;
}

/* Rebuilds the sprite sheet of object n at the current zoom [inferred]. */
/* 18:2fee */
void fn_18_2fee(int16_t n)
{
    int16_t idx;
    int16_t cls;
    int16_t r;
    int16_t c;
    int16_t size;
    int16_t gap;
    int16_t t;
    int16_t unused;
    int16_t rows;
    int16_t cell;
    HBITMAP hbm;
    HBITMAP oldbm;
    HDC hdc;
    HPALETTE oldpal;
    char mode;
    char pad[32];
    BITMAP bm;

    cls = g_7090[n].f_04e;
    idx = n + 40;
    if (!g_39e8[idx] || !g_7090[n].f_0ac || !g_7090[n].f_0ad) {
        if (g_7090[n].f_0e4)
            mode = 0;
        else
            mode = 2;
        if (g_7090[n].f_0e9)
            mode = 1;
        fn_10_6ee6(idx, g_96d2[cls].f_36, g_96d2[cls].f_84, 1, 0, LO16(g_96d2[cls].f_a9), HI16(g_96d2[cls].f_a9), 1, -1, LO8(g_96d2[cls].f_18), LO8(g_96d2[cls].f_1a), mode, 0);
        g_96d2[cls].f_2a = size = fn_10_86ca();
        gap = 4;
        SelectObject(g_39e8[idx], g_3974[idx]);
        GetObject(g_3ad0[idx], sizeof(BITMAP), &bm);
        SelectObject(g_39e8[idx], g_3ad0[idx]);
        rows = bm.bmHeight / size;
        hdc = CreateCompatibleDC(g_13dc);
        cell = size * (g_9156 * 2 + 1) / 3;
        hbm = CreateCompatibleBitmap(g_13dc, cell * 16 + 68,
                                     (cell + 4) * rows + 4);
        if (g_920e)
            oldpal = SelectPalette(hdc, g_920e, 0);
        oldbm = SelectObject(hdc, hbm);
        PatBlt(hdc, 0, 0, cell * 16 + gap * 17,
               cell * rows + (rows + 1) * gap, BLACKNESS);
        SetStretchBltMode(hdc, 3);
        for (r = 0; r < rows; r++)
            for (c = 0; c < 16; c++)
                fn_10_9962(0, hdc, cell * c + (c + 1) * gap,
                           cell * r + (r + 1) * gap, cell, cell,
                           g_39e8[idx], size * c, size * r, size, size,
                           SRCCOPY);
        SelectObject(g_39e8[idx], g_3974[idx]);
        if (g_920e)
            SelectPalette(g_39e8[idx], g_3a5c[idx], 0);
        DeleteDC(g_39e8[idx]);
        DeleteObject(g_3ad0[idx]);
        g_39e8[idx] = hdc;
        g_3ad0[idx] = hbm;
        g_3974[idx] = oldbm;
        g_3a5c[idx] = oldpal;
        g_1df8[20][n].f_22 = cell;
        g_1df8[20][n].f_24 = gap;
        g_1df8[20][n].f_20 = (int16_t)(g_1df8[20][n].f_22 * g_88cc / g_88c0.x);
        g_7090[n].f_05b = rows - 1;
        if (g_96d2[cls].f_04 < 0)
            g_96d2[cls].f_04 = 4 - g_96d2[cls].f_04 - size / 2;
        t = g_6e24[g_931c].f_00;
        fn_14_3eda();
        g_96d2[cls].f_3c = g_6e1c[g_6e20[t].f_21].f_1a * (g_9156 * 2 + 1) / 6;
        g_96d2[cls].f_68 = g_6e1c[g_6e20[t].f_21].f_1e - size / 2;
        g_96d2[cls].f_6a = g_6e1c[g_6e20[t].f_21].f_1f - size / 2;
        g_96d2[cls].f_6c = -g_96d2[cls].f_68;
        g_96d2[cls].f_6e = g_96d2[cls].f_6a;
        fn_14_4074();
    }
    g_7090[n].f_0ac = g_7090[n].f_0ad = 1;
}

/* 18:621e */
void fn_18_621e(void)
{
    int16_t i;

    g_a1d1 = g_a1cd;
    g_a1d3 = 0;
    g_6da4->f_1c = 1;
    for (i = 0; i < 4; i++)
        g_a18f[i] = g_a193[i] = 1;
    fn_18_1eac();
    g_1df8[20][main_ship].f_04.x = (int16_t)g_88cc / 2;
    g_1df8[20][main_ship].f_04.y = 150;
    g_1df8[20][main_ship].f_00.x = -1000;
    g_1df8[20][main_ship].f_00.y = -1000;
    g_1df8[20][main_ship].f_0c = 50;
    g_1df8[20][main_ship].f_0e = 0;
    for (i = 0; i < 4; i++)
        g_7090[main_ship].f_026[i] = 100;
    g_7090[main_ship].f_01e = g_96d2[g_7090[main_ship].f_04e].f_1e;
    if (!g_7090[main_ship].f_0ac || !g_7090[main_ship].f_0ad)
        fn_18_2fee(main_ship);
    if ((g_7090[main_ship].f_024 = g_7090[main_ship].f_00a) == 2)
        g_7090[main_ship].f_0e0 = g_7090[main_ship].f_0e1 = 1;
    fn_10_7480(-3, 1);
}

/* 18:3f02 */
void fn_18_3f02(int16_t x, int16_t y, int16_t k)
{
    int16_t unused1;
    int16_t a;
    int16_t dir;
    int16_t t;
    int16_t t1;
    int16_t t2;
    POINT d;

    fn_10_754a(0x10, x, y, 4);
    a = g_1df8[15]->f_28;
    d.x = x - g_1df8[15]->f_20 / 2 - g_1df8[15]->f_04.x;
    d.y = y - g_1df8[15]->f_20 / 2 - g_1df8[15]->f_04.y;
    dir = (int16_t)(fn_08_19b0(d.x, d.y) + 8) % 16;
    t1 = fn_09_88ba(dir - a);
    if (dir > a)
        t2 = fn_09_88ba(dir - a - 16);
    else
        t2 = fn_09_88ba(dir - a + 16);
    t = min(t2, t1);
    if (g_90f4 == 1)
        g_9676 = min(max((21 - g_a198 * 5) * t * k * 2 / 20, (6 - g_a198) * 4) + g_9676,
                     (10 - g_a198) * 12);
    else {
        g_9676 = min(max((8 - g_a198) * t * k * 6 / 20, (13 - g_a198) * 2) + g_9676,
                     (15 - g_a198) * 8);
        g_9676 = max(g_9676, 18);
    }
}

/* 18:50ac */
void fn_18_50ac(void)
{
    int16_t unused1;
    int16_t unused2;
    POINT pt;
    int16_t d;
    int16_t b;
    int16_t a;

    if (g_1df8[18]->f_1a) {
        g_1df8[18]->f_00 = fn_08_29ea(g_1df8[18]->f_04);
        g_1df8[18]->f_24++;
        if (g_1df8[18]->f_24 % 5 == 1) {
            int16_t m;

            m = max(10 - g_a198, 0);
            g_1df8[18]->f_0c = (int16_t)((m + 28) * g_1df8[18]->f_0c) / (int16_t)(m + 29);
            g_1df8[18]->f_0e = (int16_t)(g_1df8[18]->f_0e * (m + 28)) / (int16_t)(m + 29);
        }
        g_1df8[18]->f_00 = fn_08_29ea(g_1df8[18]->f_04);
        g_1df8[18]->f_04.x += g_1df8[18]->f_0c;
        g_1df8[18]->f_04.y += g_1df8[18]->f_0e;
        if (fn_06_7c14()) {
            g_1df8[18]->f_1a = 0;
            g_942a = 0;
            if (g_90f4 == 6)
                fn_18_52a0();
        }
        pt.x = g_1df8[g_9324][main_ship].f_20 / 2 + g_1df8[g_9324][main_ship].f_04.x;
        pt.y = g_1df8[g_9324][main_ship].f_20 / 2 + g_1df8[g_9324][main_ship].f_04.y;
        d = fn_08_285a(&b, &a, g_1df8[18]->f_04, pt);
        if (g_1df8[18]->f_24 > 40 && g_1df8[g_9324][main_ship].f_22 > d)
            fn_18_5220(g_1df8[18]->f_28);
    }
}

/* 18:5350 */
void fn_18_5350(int16_t x, int16_t y)
{
    int16_t k;
    int16_t sy;
    int16_t sx;

    if (g_1318 <= 6) {
        k = 5;
        if (y == -1 && x < 0 && x > -5)
            k = -x;
        else if (x < g_88c0.x / 3) {
            if (y < g_88c0.y / 2) {
                k = 3;
                sy = sx = 0;
            } else {
                sx = k = 0;
                sy = g_9678;
            }
        } else if (x > g_88c0.x * 2 / 3) {
            if (y < g_88c0.y / 2) {
                k = 2;
                sx = g_9678;
                sy = 0;
            } else {
                k = 1;
                sy = sx = g_9678;
            }
        }
        if (k < 5) {
            PatBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                   7 << g_9156 * 2, 7 << g_9156 * 2, BLACKNESS);
            BitBlt(g_13dc, g_88f4[k].x, g_88f4[k].y, g_9678, g_9678,
                   g_966a, sx, sy, SRCCOPY);
            BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                   7 << g_9156 * 2, 7 << g_9156 * 2,
                   g_966a, g_8914[k].x, g_8914[k].y, SRCCOPY);
            if (g_a18f[k])
                BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                       7 << g_9156 * 2, 7 << g_9156 * 2,
                       g_9656, g_a16a[k] / 40 * 7 << g_9156 * 2, 0, SRCPAINT);
            BitBlt(g_13dc, g_8904[k].x, g_8904[k].y, 7 << g_9156 * 2, 7 << g_9156 * 2,
                   g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678, SRCCOPY);
        } else
            fn_18_1934(0xf00, 1, g_3a36);
    }
}

/* Draws the end-of-level score screen [inferred]. */
/* 18:6046 */
void fn_18_6046(void)
{
    char buf[100];

    PatBlt(g_13dc, 0, 0, g_6da4->f_02.x, g_6da4->f_02.y, BLACKNESS);
    fn_10_744c(0x6e);
    fn_10_744c(0x66);
    fn_09_955c(0x7f1, buf);
    fn_06_0f1a(g_a1cf, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_09_9580(0x7f3, buf);
    fn_10_94c4(2, 6, PALETTERGB(255, 255, 0), g_6da4->f_02.x / 2, g_6da4->f_02.y / 2 - 46, buf);
    LoadString(g_9212, 0x7f2, buf, 100);
    fn_06_0f1a(g_a1cd - g_a1d1, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_10_94c4(2, 6, PALETTERGB(245, 61, 0), g_6da4->f_02.x / 2, g_6da4->f_02.y / 2 - 18, buf);
    LoadString(g_9212, 0x7f4, buf, 100);
    fn_06_0f1a(g_a1d3, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_10_94c4(2, 6, PALETTERGB(245, 61, 0), g_6da4->f_02.x / 2, g_6da4->f_02.y / 2, buf);
    LoadString(g_9212, 0x7f5, buf, 100);
    fn_06_0f1a(g_a1cd, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_10_94c4(2, 6, PALETTERGB(245, 61, 0), g_6da4->f_02.x / 2, g_6da4->f_02.y / 2 + 18, buf);
}

/* 18:4dc4 */
int16_t fn_18_4dc4(int16_t n)
{
    int16_t unused1;
    int16_t unused2;
    int16_t unused3;
    int16_t unused4;
    int16_t w;
    int16_t k;
    int16_t j;
    int16_t unused5;
    int16_t unused6;
    HGDIOBJ old;

    w = 2 << g_9156;
    if (g_a17f[n] >= 0 && g_a17f[n] < g_a187[n]) {
        MoveTo(g_13dc, g_a1b9[n].x, g_a1b9[n].y);
        g_a1b9[n].x = (int16_t)(g_a199[n].x * (int32_t)g_88c0.x / g_88cc);
        g_a1b9[n].y = (int16_t)(g_a199[n].y * (int32_t)g_88c0.x / g_88cc);
        old = SelectObject(g_13dc, g_3b44[rand() % 3]);
        if (g_a17f[n] > 0)
            LineTo(g_13dc, g_a1b9[n].x, g_a1b9[n].y);
        SelectObject(g_13dc, old);
        g_a199[n].x += g_a1a9[n].x;
        g_a199[n].y += g_a1a9[n].y;
        g_a17f[n]++;
    }
    if (g_a17f[n] >= g_a187[n]) {
        g_6098[n].z[1][5] = g_6098[n].z[1][4];
        g_a17f[n] = -1;
        for (k = 5; k > -1; k--)
            for (j = 0; j < g_6098[n].count; j++)
                PatBlt(g_13dc, g_6098[n].x[j][k], g_6098[n].y[j][k], w, w, BLACKNESS);
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));
        MoveTo(g_13dc, g_a1c9, g_a1cb);
        LineTo(g_13dc, g_a1b9[n].x, g_a1b9[n].y);
        SelectObject(g_13dc, old);
        fn_10_744c(0x16);
        g_a17f[n] = -1;
    }
    return 0;
}

/* Builds the Demon's sprite sheet (DC 39) and the 2x2 corner bitmap at
 * DS:966a [inferred]. */
/* 18:2272 */
void fn_18_2272(void)
{
    int16_t size;
    int16_t cell;
    int16_t sz2;
    int16_t w35;
    int16_t rows;
    int16_t r;
    int16_t c;
    int16_t gap;
    HBITMAP hbm;
    HBITMAP oldbm;
    HDC hdc;
    HPALETTE oldpal;
    BITMAP bm;

    fn_10_6ee6(0x27, 0x42, "", 1, 0, 1, 1, 1, g_9156 + 1, 12, 12, 2, 0);
    size = fn_10_86ca();
    cell = g_9156 > 0 ? size * 2 : size;
    gap = 4;
    SelectObject(g_39e8[39], g_3974[39]);
    GetObject(g_3ad0[39], sizeof(BITMAP), &bm);
    SelectObject(g_39e8[39], g_3ad0[39]);
    rows = bm.bmHeight / cell;
    sz2 = (g_9156 + 1) * size;
    hdc = CreateCompatibleDC(g_13dc);
    hbm = CreateCompatibleBitmap(g_13dc, sz2 * 16 + 68, (sz2 + 4) * rows + 4);
    if (g_920e)
        oldpal = SelectPalette(hdc, g_920e, 0);
    oldbm = SelectObject(hdc, hbm);
    PatBlt(hdc, 0, 0, sz2 * 16 + gap * 17, rows * sz2 + (rows + 1) * gap,
           BLACKNESS);
    SetStretchBltMode(hdc, 3);
    for (r = 0; r < rows; r++)
        for (c = 0; c < 16; c++)
            fn_10_9962(0, hdc, c * sz2 + (c + 1) * gap,
                       r * sz2 + (r + 1) * gap, sz2, sz2, g_39e8[39],
                       c * cell, r * cell, cell, cell, SRCCOPY);
    SelectObject(g_39e8[39], g_3974[39]);
    if (g_920e)
        SelectPalette(g_39e8[39], g_3a5c[39], 0);
    DeleteDC(g_39e8[39]);
    DeleteObject(g_3ad0[39]);
    g_39e8[39] = hdc;
    g_3ad0[39] = hbm;
    g_3974[39] = oldbm;
    g_3a5c[39] = oldpal;
    g_1df8[15]->f_22 = sz2;
    g_1df8[15]->f_24 = gap;
    w35 = 0x35 << g_9156;
    g_9678 = 0x35 << g_9156 * 2 >> 1;
    g_966a = CreateCompatibleDC(g_13dc);
    g_966c = CreateCompatibleBitmap(g_13dc, g_9678 * 2, g_9678 * 2);
    hdc = CreateCompatibleDC(g_13dc);
    if (g_920e) {
        g_9670 = SelectPalette(g_966a, g_920e, 0);
        oldpal = SelectPalette(hdc, g_920e, 0);
    }
    g_966e = SelectObject(g_966a, g_966c);
    PatBlt(g_966a, 0, 0, g_9678 * 2, g_9678 * 2, BLACKNESS);
    SetStretchBltMode(g_966a, 3);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 4, 12, 2, 0));
    fn_10_9962(0, g_966a, 0, g_9678, g_9678, g_9678, hdc, 0, 0, w35, w35,
               SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 16, 12, 2, 0));
    fn_10_9962(0, g_966a, g_9678 * 2 - 1, g_9678, -g_9678, g_9678, hdc, 0, 0,
               w35, w35, SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 9, 12, 2, 0));
    fn_10_9962(0, g_966a, g_9678 * 2 - 1, g_9678 - 1, -g_9678, -g_9678, hdc,
               0, 0, w35, w35, SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 2, 12, 2, 0));
    fn_10_9962(0, g_966a, 0, g_9678 - 1, g_9678, -g_9678, hdc, 0, 0, w35, w35,
               SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    if (g_920e)
        SelectPalette(hdc, oldpal, 0);
    DeleteDC(hdc);
    fn_18_270e(g_6da4->f_02.x, g_6da4->f_02.y);
}

#define SC(n) ((n) << g_9156)

/* Sets the Demon arena size and lays out its wall rectangles, bounce
 * points and corner pieces [inferred]. */
/* 18:270e */
void fn_18_270e(int16_t w, int16_t h)
{
    g_6da4->f_02.x = w;
    g_6da4->f_02.y = h;
    g_88c0.x = w;
    g_88c0.y = h - g_88ea;
    g_88f4[0].x = 0;
    g_88f4[0].y = g_88c0.y - g_9678;
    g_88f4[1].x = g_88c0.x - g_9678;
    g_88f4[1].y = g_88c0.y - g_9678;
    g_88f4[2].x = g_88c0.x - g_9678;
    g_88f4[2].y = 0;
    g_88f4[3].x = 0;
    g_88f4[3].y = 0;
    g_9156 <<= 1;
    SetRect(&g_8860[0], 0, g_88c0.y - g_9678, SC(5), g_88c0.y + SC(9) - g_9678);
    SetRect(&g_8860[1], 0, SC(9) - g_9678 + g_88c0.y, SC(14), g_88c0.y);
    SetRect(&g_8860[2], SC(14), SC(-12) + g_88c0.y, g_9678, SC(-2) + g_88c0.y);
    g_8ce4[0].x = SC(-15);
    g_8ce4[0].y = SC(-2) - g_9678 + g_88c0.y;
    g_8d1c[0] = SC(20);
    g_8ce4[1].x = SC(-3);
    g_8ce4[1].y = SC(9) - g_9678 + g_88c0.y;
    g_8d1c[1] = SC(18);
    g_8ce4[2].x = SC(14);
    g_8ce4[2].y = SC(14) - g_9678 + g_88c0.y;
    g_8d1c[2] = SC(13);
    SetRect(&g_8860[3], SC(-5) + g_88c0.x, g_88c0.y - g_9678, g_88c0.x, SC(9) - g_9678 + g_88c0.y);
    SetRect(&g_8860[4], SC(-14) + g_88c0.x, SC(9) - g_9678 + g_88c0.y, g_88c0.x, g_88c0.y);
    SetRect(&g_8860[5], g_88c0.x - g_9678, SC(-12) + g_88c0.y, SC(-14) + g_88c0.x, SC(-2) + g_88c0.y);
    g_8ce4[3].x = SC(-5) + g_88c0.x;
    g_8ce4[3].y = SC(-2) - g_9678 + g_88c0.y;
    g_8d1c[3] = SC(20);
    g_8ce4[4].x = SC(-16) + g_88c0.x;
    g_8ce4[4].y = SC(9) - g_9678 + g_88c0.y;
    g_8d1c[4] = SC(19);
    g_8ce4[5].x = SC(-27) + g_88c0.x;
    g_8ce4[5].y = SC(15) - g_9678 + g_88c0.y;
    g_8d1c[5] = SC(13);
    SetRect(&g_8860[6], SC(-5) + g_88c0.x, SC(-9) + g_9678, g_88c0.x, g_9678);
    SetRect(&g_8860[7], SC(-14) + g_88c0.x, 0, g_88c0.x, SC(-9) + g_9678);
    SetRect(&g_8860[8], g_88c0.x - g_9678, SC(2), SC(-14) + g_88c0.x, SC(12));
    g_8ce4[6].x = SC(-5) + g_88c0.x;
    g_8ce4[6].y = SC(-18) + g_9678;
    g_8d1c[6] = SC(20);
    g_8ce4[7].x = SC(-16) + g_88c0.x;
    g_8ce4[7].y = SC(-28) + g_9678;
    g_8d1c[7] = SC(19);
    g_8ce4[8].x = SC(-27) + g_88c0.x;
    g_8ce4[8].y = SC(-29) + g_9678;
    g_8d1c[8] = SC(15);
    SetRect(&g_8860[9], 0, SC(-9) + g_9678, SC(5), g_9678);
    SetRect(&g_8860[10], 0, 0, SC(14), SC(-9) + g_9678);
    SetRect(&g_8860[11], SC(14), SC(2), g_9678, SC(12));
    g_8ce4[9].x = SC(-15);
    g_8ce4[9].y = SC(-18) + g_9678;
    g_8d1c[9] = SC(20);
    g_8ce4[10].x = SC(-3);
    g_8ce4[10].y = SC(-28) + g_9678;
    g_8d1c[10] = SC(19);
    g_8ce4[11].x = SC(13);
    g_8ce4[11].y = SC(-28) + g_9678;
    g_8d1c[11] = SC(14);
    g_9156 /= 2;
    g_8904[0].x = 18 / (4 - g_9156 * 3);
    g_8904[0].y = 52 / (4 - g_9156 * 3) - g_9678 + g_88c0.y;
    g_8904[1].x = -46 / (4 - g_9156 * 3) + g_88c0.x;
    g_8904[1].y = 52 / (4 - g_9156 * 3) - g_9678 + g_88c0.y;
    g_8904[2].x = -46 / (4 - g_9156 * 3) + g_88c0.x;
    g_8904[2].y = 26 / (4 - g_9156 * 3);
    g_8904[3].x = 18 / (4 - g_9156 * 3);
    g_8904[3].y = 26 / (4 - g_9156 * 3);
    g_8914[0].x = 18 / (4 - g_9156 * 3);
    g_8914[0].y = 52 / (4 - g_9156 * 3) + g_9678;
    g_8914[1].x = -46 / (4 - g_9156 * 3) + g_9678 * 2;
    g_8914[1].y = 52 / (4 - g_9156 * 3) + g_9678;
    g_8914[2].x = -46 / (4 - g_9156 * 3) + g_9678 * 2;
    g_8914[2].y = 26 / (4 - g_9156 * 3);
    g_8914[3].x = 18 / (4 - g_9156 * 3);
    g_8914[3].y = 26 / (4 - g_9156 * 3);
    g_1df8[15]->f_20 = (int16_t)(g_1df8[15]->f_22 * g_88cc / g_88c0.x);
    g_1df8[15]->f_04.x = (int16_t)g_88cc / 2 - g_1df8[15]->f_20 / 2;
    g_1df8[15]->f_04.y = (int16_t)(g_88c0.y * g_88cc / g_88c0.x) / 2 - g_1df8[15]->f_20 / 2;
    g_1df8[15]->f_00.x = g_88c0.x / 2 - g_1df8[15]->f_22 / 2;
    g_1df8[15]->f_00.y = g_88c0.y / 2 - g_1df8[15]->f_22 / 2;
    g_1df8[15]->f_0c = 0;
    g_1df8[15]->f_0e = 0;
}

/* Builds the scaled copies (DCs 35-38) of the sprite sheets 6-8 for the
 * Demon view [inferred]. */
/* 18:6374 */
void fn_18_6374(void)
{
    int16_t sw;
    int16_t sg;
    int16_t dg;
    int16_t dw;
    int16_t i;

    sw = 0x2c << g_959e >> 1;
    sg = 4 << g_959e >> 1;
    dw = 0x2c << g_9156 >> 1;
    dg = 4 << g_9156 >> 1;
    if (!g_9156)
        dw = (int16_t)(dw * 2) / 3;
    g_39e8[35] = CreateCompatibleDC(g_13dc);
    g_3ad0[35] = CreateCompatibleBitmap(g_13dc, dw * 18 + dg * 19, dg * 2 + dw);
    if (g_920e)
        g_3a5c[35] = SelectPalette(g_39e8[35], g_920e, 0);
    g_3974[35] = SelectObject(g_39e8[35], g_3ad0[35]);
    PatBlt(g_39e8[35], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[35], 3);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[35], (dw + dg) * i + dg, dg, dw, dw, g_39e8[7],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
    g_39e8[36] = CreateCompatibleDC(g_39e8[6]);
    g_3ad0[36] = CreateCompatibleBitmap(g_39e8[6], dw * 18 + dg * 19, dg * 2 + dw);
    g_3974[36] = SelectObject(g_39e8[36], g_3ad0[36]);
    PatBlt(g_39e8[36], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[36], 2);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[36], (dw + dg) * i + dg, dg, dw, dw, g_39e8[6],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
    dw /= 2;
    dg /= 2;
    g_39e8[37] = CreateCompatibleDC(g_13dc);
    g_3ad0[37] = CreateCompatibleBitmap(g_13dc, dw * 18 + dg * 19, dg * 2 + dw);
    if (g_920e)
        g_3a5c[37] = SelectPalette(g_13dc, g_920e, 0);
    g_3974[37] = SelectObject(g_39e8[37], g_3ad0[37]);
    PatBlt(g_39e8[37], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[37], 3);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[37], (dw + dg) * i + dg, dg, dw, dw, g_39e8[7],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
    g_39e8[38] = CreateCompatibleDC(g_39e8[8]);
    g_3ad0[38] = CreateCompatibleBitmap(g_39e8[8], dw * 18 + dg * 19, dg * 2 + dw);
    g_3974[38] = SelectObject(g_39e8[38], g_3ad0[38]);
    PatBlt(g_39e8[38], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[38], 2);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[38], (dw + dg) * i + dg, dg, dw, dw, g_39e8[6],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
}

/* 18:3474 */
void fn_18_3474(void)
{
    int16_t i;
    int16_t a;
    int16_t b;

    g_6e24[g_7090[main_ship].f_0d6].f_74 = g_7090[main_ship].f_024;
    g_6e24[g_7090[main_ship].f_0d6].f_72 = g_7090[main_ship].f_0ac;
    g_6e24[g_7090[main_ship].f_0d6].f_73 = g_7090[main_ship].f_0ad;
    if (g_959e != 1 || !g_9156) {
        a = g_7090[main_ship].f_0ac;
        b = g_7090[main_ship].f_0ad;
        fn_18_2fee(main_ship);
        fn_10_5d3c(main_ship);
        if (g_7090[main_ship].f_0e4 && g_96d2[g_7090[main_ship].f_04e].f_28 == 3) {
            g_92e4 = 1;
            if (!a)
                fn_08_2cd8(main_ship, 0);
            if (!b)
                fn_08_2cd8(main_ship, 1);
            g_92e4 = 0;
        }
    } else {
        g_1df8[20][main_ship].f_22 = g_1df8[14][main_ship].f_22;
        g_1df8[20][main_ship].f_24 = g_1df8[14][main_ship].f_24;
        g_1df8[20][main_ship].f_20 =
            (int16_t)(g_1df8[20][main_ship].f_22 * g_88cc / g_88c0.x);
    }
    for (i = 0; i < 4; i++)
        g_6e24[g_7090[main_ship].f_0d6].f_38[i] = g_7090[main_ship].f_026[i];
    g_6e24[g_7090[main_ship].f_0d6].f_1c = g_7090[main_ship].f_01e / 40;
    g_6e24[g_7090[main_ship].f_0d6].f_74 = g_7090[main_ship].f_024;
    g_6e24[g_7090[main_ship].f_0d6].f_72 = g_7090[main_ship].f_0ac;
    g_6e24[g_7090[main_ship].f_0d6].f_73 = g_7090[main_ship].f_0ad;
    g_1df8[20][main_ship].f_04.x = (int16_t)g_88cc / 2;
    g_1df8[20][main_ship].f_04.y = 150;
    g_1df8[20][main_ship].f_00.x = -1000;
    g_1df8[20][main_ship].f_00.y = -1000;
    g_1df8[20][main_ship].f_0c = 50;
    g_1df8[20][main_ship].f_0e = 0;
    g_1df8[20][main_ship].f_12 = g_1df8[20][main_ship].f_24;
    g_1df8[20][main_ship].f_44 = g_1df8[14][main_ship].f_44;
    g_1df8[20][main_ship].f_42 = g_1df8[14][main_ship].f_42;
    g_1df8[20][main_ship].f_46 = g_1df8[14][main_ship].f_46;
    g_1df8[20][main_ship].f_2c = g_1df8[14][main_ship].f_2c;
    g_1df8[20][main_ship].f_48 = g_1df8[14][main_ship].f_48;
    g_1df8[20][main_ship].f_66 = g_1df8[14][main_ship].f_66;
    g_1df8[20][main_ship].f_62 = g_1df8[14][main_ship].f_62;
    g_1df8[20][main_ship].f_5e = g_1df8[14][main_ship].f_5e;
    g_1df8[20][main_ship].f_3c = g_1df8[14][main_ship].f_3c;
    g_1df8[20][main_ship].f_54 = 0;
    g_1df8[20][main_ship].f_48 = g_1df8[14][main_ship].f_48;
    g_1df8[20][main_ship].f_28 = 8;
    for (i = 0; i < 4; i++)
        g_a187[i] = 0;
}

/* Starts the Demon sub-game [inferred]. */
/* 18:08bc */
void fn_18_08bc(int16_t big)
{
    int16_t i;

    if (!g_9660) {
        g_073e = 1;
        fn_10_7480(10, 1);
    }
    subgame_active = 1;
    g_959e = g_9156;
    g_9664 = g_9674 = 0;
    g_88d0 = 0;
    if (big) {
        g_9156 = 1;
        g_a197 = 1;
    } else
        g_9156 = 0;
    fn_18_0b1e();
    if (g_959e != 1 || !g_9156) {
        fn_10_1eb6(main_ship);
        fn_10_0552(0x22, 1);
        fn_10_0552(0xc, 1);
        fn_10_0552(0xa, 1);
    }
    /* two int stores through one view: CL merges them into one immediate
     * dword store instead of sharing a zeroed eax with g_88d4 */
    g_a1d1 = VIEW(int16_t, g_a1d1, 2) = 0;
    g_88d4 = 0;
    g_9324 = 0x14;
    g_9326 = 0xf;
    g_9328 = 0x11;
    g_934a = 0x13;
    fn_06_7266();
    g_94c4 = 1;
    fn_06_72d8(2, 2);
    g_9330 = 1;
    for (i = g_94c4 = 0; i < 45; i++)
        g_1e90[i].f_00 = -1;
    for (i = 0; i < 9; i++)
        g_6098[i].z[1][5] = -1;
    for (i = 0; i < 20; i++)
        g_58bc[i].f_10 = -1;
    g_88c0.x = g_6da4->f_02.x;
    g_88c0.y = g_6da4->f_02.y;
    g_88c4.x = g_88c4.y = 0;
    g_88f0 = g_88c0.x * 10 / 255;
    g_88f2 = g_88c0.y * 10 / 164;
    g_88f0 = max(g_88f0 / 3 * 3, 6);
    g_88f2 = max(g_88f2 / 4 * 4, 8);
    g_88e8 = g_88c0.x;
    g_88ea = g_88f2 + 2;
    if (g_90f4 == 1)
        g_88ea = 0;
    g_88c0.y -= g_88ea;
    g_88cc = 8000;
    fn_18_1dd0();
    fn_18_1eac();
    if (g_959e != 1 || !g_9156) {
        fn_10_5c42();
        fn_10_5202();
        fn_10_5102();
    }
    fn_18_2272();
    fn_10_58ce(0);
    fn_18_6374();
    if (!g_9660) {
        fn_10_7480(-1, 1);
        g_13a0 = 0x10;
    }
    fn_18_337c();
    fn_18_3474();
    fn_18_1784(0, 0, g_6da4->f_02.x, g_6da4->f_02.y - g_88ea);
    fn_18_17f6();
    if (g_90f4 == 1)
        fn_10_744c(0x30);
    g_9660 = 1;
}

/* Decides whether the Demon appears now and picks its position
 * [inferred]. */
/* 18:5cec */
int16_t fn_18_5cec(void)
{
    int16_t i;
    int16_t j;
    int16_t tries;
    int16_t unused;
    int16_t b;
    int16_t a;
    int16_t ok;
    POINT pt;
    POINT unused2;
    POINT unused3;

    ok = 1;
    if (!flow_interactive)
        return 0;
    if (g_9320 == 6)
        return 0;
    if (g_1e68 - g_8e2c < 400)
        return 0;
    for (i = 0; i < g_9318; i++)
        if (g_1df8[8][i].f_1a || g_1df8[8][i + 1].f_1a)
            ok = 0;
    if (g_7090[main_ship].cnt > 9)
        ok = 0;
    if (!g_1df8[7]->f_18)
        ok = 0;
    if (g_0992 + 60 > g_932a && g_91f8 - g_93ac < 15)
        ok = 0;
    if (g_92e8 || g_913e > 1)
        ok = 1;
    if (ok) {
        if (rand() % 200 < (int16_t)((int16_t)g_1e68 - 300) / 8 || g_92e8) {
            tries = 0;
            do {
                tries++;
                ok = 1;
                pt.x = rand() % (int16_t)(LO16(g_90ea) * 2) - LO16(g_90ea) / 2;
                pt.y = rand() % (int16_t)(HI16(g_90ea) * 2) - HI16(g_90ea) / 2;
                for (i = 8; i <= 14; i++) {
                    if (i == 8 || i == 14)
                    for (j = 0; j < g_9406[i]; j++) {
                        if (!g_1df8[i][j].f_18
                            && (g_1df8[i][j].f_54 || i == 14 && j == main_ship)
                            && ((int16_t)(LO16(g_90ea) * 4) / 5 >> g_9156)
                               > fn_08_285a(&b, &a, g_1df8[i][j].f_04,
                                            fn_08_2bbe(pt)))
                            ok = 0;
                    }
                }
                if (tries > 10)
                    ok = 2;
            } while (!ok);
            if (ok == 2)
                return 0;
            g_88c8 = fn_08_2bbe(pt);
            fn_18_0b1e();
            g_9666 = 0;
            g_9664 = 0;
            g_913a = 1;
            fn_10_754a(0x27, g_88c8.x, g_88c8.y, 4);
            g_913e = 0;
            g_93ac = g_91f8;
            g_965e = 1;
            fn_10_7480(-2, 1);
            fn_10_7480(10, 1);
            g_2384 = g_1e50 + 70000;
            g_0992 += 50;
            return 1;
        }
    }
}

/* Per-tick update of the Demon sub-game [inferred]. */
/* 18:0000 */
void fn_18_0000(void)
{
    int16_t j;
    int16_t i;

    g_9672 = 0;
    if (g_8d34 && g_8d34 < g_1e50) {
        g_8d34 = 0;
        g_9530 = 2;
        fn_10_744c(0x22);
    }
    if (g_13a0 != -1)
        g_13a0--;
    if (g_13a0 == 1)
        fn_10_7480(6, 1);
    if (g_9530 == 2) {
        if (g_1318 > 1 && g_90f4 == 1) {
            if (g_966a) {
                if (g_920e)
                    SelectPalette(g_966a, g_9670, 0);
                SelectObject(g_966a, g_966e);
                DeleteObject(g_966c);
                DeleteDC(g_966a);
                g_966a = 0;
            }
            if (g_9656) {
                if (g_920e)
                    SelectPalette(g_9656, g_965c, 0);
                SelectObject(g_9656, g_965a);
                DeleteObject(g_9658);
                DeleteDC(g_9656);
                g_9656 = 0;
            }
            sprite_dc_restore();
            g_90f4 = 6;
            g_952e = main_ship;
            fn_10_7480(g_913e = g_88c4.x = g_88c4.y = g_914a = 0,
                       g_9530 = g_0928 = g_93a6 = g_9e5b = 1);
            g_9156 = 0;
        } else if (g_9660)
            fn_18_03d6();
    } else if (g_88d0) {
        if (g_88d0 == 2) {
            g_88d0 = g_1e50 + 12000;
            fn_18_6046();
        } else if (g_88d0 < g_1e50) {
            g_88d0 = 0;
            fn_18_621e();
        }
    } else {
        if (!g_9660) {
            if (g_90f4 == 1)
                fn_18_08bc(1);
            else
                fn_18_08bc(0);
        }
        if (g_6da4->f_1c) {
            fn_18_17f6();
            g_6da4->f_1c = 0;
        }
        fn_18_1cbe(0);
        fn_11_1d7c();
        fn_18_034c();
        if (g_9530 == 1 && music_pause_state == -2)
            fn_10_7480(-3, 1);
        if (g_8e62)
            fn_18_0d4e(g_8e62, g_8e64, g_1d38);
        if (!g_1df8[g_9324][main_ship].f_18) {
            if (g_05a4 <= g_1e50) {
                g_05a4 = g_1e50 + 50;
                fn_11_592a();
            }
            if (g_05b8 < g_1e50) {
                g_05b8 = g_1e50 + 10000;
                fn_07_2128();
            }
        }
        if (!g_1df8[g_9324][main_ship].f_18)
            fn_11_4db0();
        for (i = g_9136 = 0; i < 5; i++)
            for (j = 0; j < g_0598 + g_0594; j++)
                g_9136 = fn_08_3aec(j, i);
        if (g_9430 > 0)
            for (j = 0; j <= g_9434; j++)
                fn_08_3fbe(j);
        fn_07_375a();
        g_1c9e++;
        if (g_1c9e >= 8 && g_90f4 == 6) {
            g_1c9e = 0;
            if (g_7090[main_ship].f_060)
                g_7090[main_ship].f_060--;
        }
        g_9146 = 0;
        fn_08_4e14();
        if (g_1016)
            fn_11_a9ea(1);
        fn_18_0d94();
        fn_18_37d8();
        fn_18_403e();
        fn_07_40c4();
        fn_07_3bae();
        fn_18_50ac();
        if (g_9456 > 0)
            fn_07_5e04();
        fn_13_447a();
    }
}

/* Ends the Demon sub-game and restores the normal view [inferred]. */
/* 18:03d6 */
void fn_18_03d6(void)
{
    int16_t i;
    int16_t j;
    int16_t changed;
    int16_t scaled;
    int16_t b0;
    int16_t b1;

    scaled = changed = 0;
    if (subgame_active) {
        if (g_9156 == 1)
            scaled = 1;
        subgame_active = 0;
        if (g_9156 == 1)
            fn_16_631c();
        PatBlt(g_13dc, 0, 0, g_88c0.x, g_88c0.y, BLACKNESS);
        g_9326 = 0;
        if (g_92e8)
            g_9326 = 1;
        g_9324 = 14;
        g_9328 = 5;
        g_934a = 3;
        if (g_9156 == 1) {
            g_913c = 1;
            g_9666 = 0;
            g_9664 = 0;
            fn_10_754a(0x27, g_88c8.x, g_88c8.y, 4);
            g_1df8[14][main_ship].f_18 = 1;
            g_073e = 0;
            fn_10_7480(-3, 1);
        } else
            fn_18_0ba0();
        for (j = 0; j < 4; j++)
            g_7090[main_ship].f_026[j] = g_6e24[g_7090[main_ship].f_0d6].f_38[j];
        g_7090[main_ship].f_01e = 40 * g_6e24[g_7090[main_ship].f_0d6].f_1c;
        g_7090[main_ship].f_024 = g_6e24[g_7090[main_ship].f_0d6].f_74;
        if (g_6e24[g_7090[main_ship].f_0d6].f_72 != g_7090[main_ship].f_0ac ||
            g_6e24[g_7090[main_ship].f_0d6].f_73 != g_7090[main_ship].f_0ad)
            changed = 1;
        if (!g_7090[main_ship].flag)
            changed = 1;
        g_7090[main_ship].f_0ac = g_6e24[g_7090[main_ship].f_0d6].f_72;
        g_7090[main_ship].f_0ad = g_6e24[g_7090[main_ship].f_0d6].f_73;
        b0 = g_7090[main_ship].f_0ac;
        b1 = g_7090[main_ship].f_0ad;
        g_7090[main_ship].flag = 1;
        g_1e84 = 0;
        g_2408 = 0;
        g_238c = 0;
        fn_06_7266();
        g_94c4 = 1;
        fn_06_72d8(5, 5);
        g_94c4 = 0;
        g_92e4 = g_9330 = 1;
        if (g_966a) {
            if (g_920e)
                SelectPalette(g_966a, g_9670, 0);
            SelectObject(g_966a, g_966e);
            DeleteObject(g_966c);
            DeleteDC(g_966a);
            g_966a = 0;
        }
        if (g_9656) {
            if (g_920e)
                SelectPalette(g_9656, g_965c, 0);
            SelectObject(g_9656, g_965a);
            DeleteObject(g_9658);
            DeleteDC(g_9656);
            g_9656 = 0;
        }
        if (g_9156 == 1)
            sprite_dc_restore();
        if (g_959e != 1 || !g_9156) {
            if (g_90f4 == 1)
                fn_18_07b2();
            else
                g_9662 = 1;
        } else if (changed) {
            fn_10_1eb6(main_ship);
            fn_16_3784(main_ship, 2);
            if (g_7090[main_ship].f_0e4 && g_96d2[g_7090[main_ship].f_04e].f_28 == 3) {
                if (!b0)
                    fn_08_2cd8(main_ship, 0);
                if (!b1)
                    fn_08_2cd8(main_ship, 1);
            }
        }
        fn_10_0552(0x27, 1);
        fn_10_0552(0x23, 1);
        fn_10_0552(0x24, 1);
        fn_10_0552(0x25, 1);
        fn_10_0552(0x26, 1);
        if (g_9668) {
            DeleteObject(g_9668);
            g_9668 = 0;
        }
        fn_18_1e46();
        g_92e4 = 0;
        g_9156 = g_959e;
        if (scaled) {
            fn_13_65f2(2);
            fn_11_1bcc();
            fn_11_0894();
            fn_11_3396();
            fn_11_0afe();
        }
        for (i = 0; i < 45; i++)
            g_1e90[i].f_00 = -1;
        for (i = 0; i < 9; i++)
            g_6098[i].z[1][5] = -1;
        for (i = 0; i < 20; i++)
            g_58bc[i].f_10 = -1;
        g_9510 = 100;
        g_9660 = 0;
    }
}

/* Moves and draws the 15 x 4 particle beam (tractor/teleport effect)
 * [inferred]. */
/* 18:0d94 */
void fn_18_0d94(void)
{
    int16_t a;
    int16_t b;
    int16_t k;
    int16_t c3;
    int16_t dist;
    int16_t cnt;
    int16_t bi;
    int16_t sh;
    int16_t level;
    POINT d;
    int16_t unused1;
    int16_t unused2;
    HGDIOBJ old;
    DWORD color;
    int16_t vis;

    if (!g_9666)
        for (a = 0; a < 15; a++)
            for (b = 0; b < 4; b++)
                g_8924[a][b].x = g_8924[a][b].y = 0;
    g_9666++;
    cnt = g_9664;
    if (g_9674)
        cnt = g_9208 * 2 + 9;
    for (b = 0; b < cnt; b++)
        for (a = 0; a < 4; a++) {
            if (a < 3) {
                d.x = g_8924[b][a + 1].x - g_8924[b][a].x;
                d.y = g_8924[b][a + 1].y - g_8924[b][a].y;
            } else {
                d.x = g_8924[b][0].x - g_8924[b][a].x;
                d.y = g_8924[b][0].y - g_8924[b][a].y;
            }
            if (a == 0)
                dist = fn_08_35d0(d.x, d.y);
            if (dist == 0)
                dist = 1;
            if (g_913a)
                level = 2;
            else if (g_913c)
                level = 1;
            else
                level = 0;
            if (!subgame_active || ((int32_t)g_1df8[15]->f_22 << 13) / g_88c0.x - 250 < dist
                || g_93a6 && dist > 50) {
                if ((0x708 >> level) > dist)
                    SetPixel(g_13dc, g_8a14[b][a][2].x, g_8a14[b][a][2].y, PALETTEINDEX(0));
                else
                    PatBlt(g_13dc, g_8a14[b][a][2].x, g_8a14[b][a][2].y, 2, 2, BLACKNESS);
            }
            if (subgame_active)
                sh = 6;
            else if (g_913a)
                sh = 4;
            else
                sh = 5;
            if (g_913c) {
                g_8924[b][a].x -= ((int32_t)d.x << sh) / dist;
                g_8924[b][a].y -= ((int32_t)d.y << sh) / dist;
            } else {
                g_8924[b][a].x += ((int32_t)d.x << sh) / dist;
                g_8924[b][a].y += ((int32_t)d.y << sh) / dist;
            }
            g_8a14[b][a][0] = fn_08_29ea(g_8924[b][a]);
            if (subgame_active) {
                g_8a14[b][a][0].x += g_2390;
                g_8a14[b][a][0].y += g_2392;
            }
            vis = 1;
            if (subgame_active && g_1318 < 2
                && (g_8a14[b][a][0].x < g_9678 || g_8a14[b][a][0].x > g_88c0.x - g_9678)
                && (g_8a14[b][a][0].y < g_9678 || g_8a14[b][a][0].y > g_88c0.y - g_9678))
                vis = 0;
            for (k = 2; k > 0; k--) {
                g_8a14[b][a][k].x = g_8a14[b][a][k - 1].x;
                g_8a14[b][a][k].y = g_8a14[b][a][k - 1].y;
            }
            if ((!subgame_active || ((int32_t)g_1df8[15]->f_22 << 13) / g_88c0.x < dist
                 || g_93a6 && dist > 100) && vis) {
                if ((0x898 >> level) > dist) {
                    if (g_90f0)
                        color = PALETTEINDEX(g_13ae[a]);
                    else
                        switch (a) {
                        case 0:
                            color = RGB(191, 0, 0);
                            break;
                        case 1:
                            color = RGB(191, 191, 0);
                            break;
                        case 2:
                            color = RGB(0, 191, 191);
                            break;
                        case 3:
                            color = RGB(191, 191, 191);
                            break;
                        }
                    SetPixel(g_13dc, g_8a14[b][a][0].x, g_8a14[b][a][0].y, color);
                } else {
                    bi = a * 2;
                    if ((0xdac >> level) > dist)
                        bi++;
                    old = SelectObject(g_13dc, g_88d8[bi]);
                    PatBlt(g_13dc, g_8a14[b][a][0].x, g_8a14[b][a][0].y, 2, 2, PATCOPY);
                    SelectObject(g_13dc, old);
                }
            }
        }
    if (g_9666 % (13 - g_9208 * 2) == 0) {
        POINT c;
        POINT d2;
        int16_t spd;
        int16_t lim;

        if (++g_9664 >= g_9208 * 2 + 9) {
            g_9664 = 0;
            if (g_913c)
                g_9664 = (g_9208 + 5) * 2;
            g_9674 = 1;
        }
        g_1ca0++;
        if (subgame_active) {
            c.x = (int16_t)(g_88cc >> 1);
            c.y = (int16_t)(g_88c0.y * g_88cc / (g_88c0.x * 2));
            g_8924[g_9664][0].x = c.x + (g_1050[g_1ca0 & 15].x << 8);
            g_8924[g_9664][0].y = c.y + (g_1050[g_1ca0 & 15].y << 8);
            g_8924[g_9664][1].x = c.x + (g_1050[g_1ca0 + 4 & 15].x << 8);
            g_8924[g_9664][1].y = c.y + (g_1050[g_1ca0 + 4 & 15].y << 8);
            g_8924[g_9664][2].x = c.x + (g_1050[g_1ca0 + 8 & 15].x << 8);
            g_8924[g_9664][2].y = c.y + (g_1050[g_1ca0 + 8 & 15].y << 8);
            g_8924[g_9664][3].x = c.x + (g_1050[g_1ca0 - 4 & 15].x << 8);
            g_8924[g_9664][3].y = c.y + (g_1050[g_1ca0 - 4 & 15].y << 8);
            for (a = 0; a < 4; a++)
                for (b = 0; b < 3; b++)
                    g_8a14[g_9664][a][b].x = g_8a14[g_9664][a][b].y = -100;
        } else if (g_913a) {
            /* c assigned inside the first two sums: reproduces the store order */
            g_8924[g_9664][0].x = (g_1050[g_1ca0 & 15].x << 6) + (c.x = g_88c8.x);
            g_8924[g_9664][0].y = (g_1050[g_1ca0 & 15].y << 6) + (c.y = g_88c8.y);
            g_8924[g_9664][1].x = (g_1050[g_1ca0 + 4 & 15].x << 6) + c.x;
            g_8924[g_9664][1].y = (g_1050[g_1ca0 + 4 & 15].y << 6) + c.y;
            g_8924[g_9664][2].x = (g_1050[g_1ca0 + 8 & 15].x << 6) + g_88c8.x;
            g_8924[g_9664][2].y = (g_1050[g_1ca0 + 8 & 15].y << 6) + g_88c8.y;
            g_8924[g_9664][3].x = (g_1050[g_1ca0 - 4 & 15].x << 6) + g_88c8.x;
            g_8924[g_9664][3].y = (g_1050[g_1ca0 - 4 & 15].y << 6) + g_88c8.y;
            d2 = fn_08_29ea(c);
            d.x = g_1df8[14][main_ship].f_22 / 2 + g_1df8[14][main_ship].f_00.x - d2.x << LO8(g_9150);
            d.y = g_1df8[14][main_ship].f_22 / 2 + g_1df8[14][main_ship].f_00.y - d2.y << LO8(g_9150);
            dist = fn_08_35d0(d.x, d.y);
            if (dist == 0)
                dist = 1;
            if (dist < 200)
                g_913a = 0;
            g_1df8[14][main_ship].f_0c -= (int32_t)d.x * (g_9666 / 20) / dist;
            g_1df8[14][main_ship].f_0e -= (int32_t)d.y * (g_9666 / 20) / dist;
            spd = fn_08_35d0(g_1df8[14][main_ship].f_0c, g_1df8[14][main_ship].f_0e);
            lim = 150;
            if (dist < 2000)
                lim = dist / 20 + 50;
            if (dist < 1200 && g_913a == 1) {
                fn_10_744c(0x23);
                g_913a = 2;
                fn_12_2556(0xe, main_ship);
            }
            if (lim < spd) {
                g_1df8[14][main_ship].f_0c = (int32_t)g_1df8[14][main_ship].f_0c * lim / spd;
                g_1df8[14][main_ship].f_0e = (int32_t)g_1df8[14][main_ship].f_0e * lim / spd;
            }
        } else if (g_913c) {
            if (g_9664 < 16) {
                g_8924[g_9664][0].x = (g_1050[g_1ca0 & 15].x << 1) + (c.x = g_88c8.x);
                g_8924[g_9664][0].y = (g_1050[g_1ca0 & 15].y << 1) + (c.y = g_88c8.y);
                g_8924[g_9664][1].x = (g_1050[g_1ca0 + 4 & 15].x << 1) + c.x;
                g_8924[g_9664][1].y = (g_1050[g_1ca0 + 4 & 15].y << 1) + c.y;
                g_8924[g_9664][2].x = (g_1050[g_1ca0 + 8 & 15].x << 1) + g_88c8.x;
                g_8924[g_9664][2].y = (g_1050[g_1ca0 + 8 & 15].y << 1) + g_88c8.y;
                g_8924[g_9664][3].x = (g_1050[g_1ca0 - 4 & 15].x << 1) + g_88c8.x;
                g_8924[g_9664][3].y = (g_1050[g_1ca0 - 4 & 15].y << 1) + g_88c8.y;
                if ((g_9208 + 4) * 2 == g_9664 && g_913c == 1) {
                    fn_10_744c(0x23);
                    g_1df8[14][main_ship].f_18 = 0;
                    g_913c = 2;
                    fn_12_2556(0xe, main_ship);
                }
            }
            if (g_9666 > 200) {
                g_913c = 0;
                for (a = 0; a < 15; a++)
                    for (b = 0; b < 4; b++)
                        for (c3 = 0; c3 < 3; c3++)
                            PatBlt(g_13dc, g_8a14[a][b][c3].x, g_8a14[a][b][c3].y, 2, 2,
                                   BLACKNESS);
                fn_18_0ba0();
            }
        }
    }
}

/* Per-frame update of the Demon (object 15:0): turns toward the player and
 * shoots, grows into view while g_1318 counts down, collides, and spins
 * the four gate gauges [inferred]. */
/* 18:37d8 */
void fn_18_37d8(void)
{
    int16_t obj;                    /* assigned, never read */
    int16_t i;
    int16_t old;
    WORD r;
    int16_t mode;
    int16_t dir;
    int16_t target;
    int16_t ty;
    POINT s;                    /* s, t, rc as structs: CL then recomputes */
    POINT t;                    /* f22 / 2 like the game; t.y unused */
    RECT rc;                    /* the Demon's previous screen rect */

    if (g_90f4 == 6 && g_1318 > 1)
        return;
    g_1ca6++;
    g_9676 = g_9676 - 1 < 0 ? 0 : g_9676 - 1;
    if (g_90f4 == 1) {
        if (g_1ca6 % (12 - g_a198) == 0)
            mode = 1;
        else
            mode = 0;
        if (g_1318 >= 30)
            mode = 2;
    } else {
        if (g_1ca6 % max(18 - g_a198, 5) == 0)
            mode = 1;
        else
            mode = 0;
    }
    g_1df8[15]->f_0e = 0;
    g_1df8[15]->f_0c = g_1df8[15]->f_0e;
    fn_08_1b54(0xf00, 1);
    if (mode && g_7090[main_ship].flag && !g_9676) {
        target = g_9324;
        obj = main_ship;
        if (mode == 1) {
            dir = g_1df8[15]->f_28;
            s.x = g_1df8[15]->f_22 / 2 + g_1df8[15]->f_04.x;
            s.y = g_1df8[15]->f_22 / 2 + g_1df8[15]->f_04.y;
            t.x = g_1df8[g_9324][main_ship].f_22 / 2 + g_1df8[g_9324][main_ship].f_04.x;
            g_1df8[15]->f_28 = steer_toward_direction(s.y, s.x,
                    ty = g_1df8[g_9324][main_ship].f_04.y + g_1df8[g_9324][main_ship].f_22 / 2, t.x,
                    g_1df8[15]->f_28, 5, -1, g_9324, main_ship, 0);
            if (g_7090[main_ship].f_084 < g_1e50 && g_1318 < 2 && g_1df8[15]->f_28 == dir &&
                target == g_9324) {
                if ((g_90f4 == 1 && rand() % 9 < g_a198 + 3) ||
                    (g_90f4 == 6 && rand() % 27 < g_a198 + 7))
                    fn_12_2db6(15, 0, (int16_t)(g_1df8[15]->f_28 + 8) % 16, (g_a198 + 9) * 2, 5);
                else if (g_90f4 == 1) {
                    if (g_7090[main_ship].f_026[0] < 50) {
                        if (rand() % 6 < g_a198)
                            fn_18_66e0();
                    } else if (rand() % 13 < g_a198)
                        fn_18_66e0();
                } else {
                    if (g_7090[main_ship].f_026[0] < 50) {
                        if (rand() % 10 < g_a198 - 1)
                            fn_18_66e0();
                    } else if (rand() % 18 < g_a198 - 1)
                        fn_18_66e0();
                }
            }
        } else
            g_1df8[15]->f_28 = (int16_t)(g_1df8[15]->f_28 + 1) % 16;
        g_1df8[15]->f_10 = (g_1df8[15]->f_22 + g_1df8[15]->f_24) * g_1df8[15]->f_28 + g_1df8[15]->f_24;
        g_1df8[15]->f_12 = g_1df8[15]->f_24;
        if (mode == 1)
            fn_18_1934(0xf00, 1, g_3a36);
        else {
            if (g_1318 == 30)
                g_1ca8 = 0;
            rc.right = g_1df8[15]->f_22 - g_1df8[15]->f_22 / 2 + g_1ca8 / 2 + g_88c0.x / 2 - g_1ca8 + g_88c4.x;
            rc.top = g_1ca8 / 2 - g_1df8[15]->f_22 / 2 + g_88c0.y / 2 + g_88c4.y;
            rc.bottom = g_1df8[15]->f_22 - g_1ca8 + rc.top;
            g_88c0.x = g_6da4->f_02.x + (g_8d14 - (int32_t)g_6da4->f_02.x) * ((int32_t)g_1318 - 30) / 59;
            g_88c0.y = g_6da4->f_02.y + (g_8d16 - (int32_t)g_6da4->f_02.y) * ((int32_t)g_1318 - 30) / 59;
            g_88c4.x = (int16_t)(g_8d18 * ((int32_t)g_1318 - 30) / 59);
            g_88c4.y = (int16_t)(g_8d1a * ((int32_t)g_1318 - 30) / 59);
            SetStretchBltMode(g_13dc, 3);
            g_1ca8 = g_1df8[15]->f_22 * (g_1318 - 30) / 59;
            g_1caa.x = g_1ca8 / 2 - g_1df8[15]->f_22 / 2 + g_88c0.x / 2 + g_88c4.x;
            g_1caa.y = g_1ca8 / 2 - g_1df8[15]->f_22 / 2 + g_88c0.y / 2 + g_88c4.y;
            (*g_1df8[15]).f_00 = g_1caa;
            StretchBlt(g_13dc, g_1caa.x, g_1caa.y, g_1df8[15]->f_22 - g_1ca8, g_1df8[15]->f_22 - g_1ca8,
                       g_3a36, g_1df8[15]->f_10, g_1df8[15]->f_12, g_1df8[15]->f_22, g_1df8[15]->f_22, SRCCOPY);
            rc.left = g_1df8[15]->f_22 - g_1ca8 + g_1caa.x;
            PatBlt(g_13dc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, BLACKNESS);
            PatBlt(g_13dc, g_1caa.x, rc.top, g_1df8[15]->f_22 - g_1ca8, g_1caa.y - rc.top, BLACKNESS);
            PatBlt(g_13dc, g_1caa.x, g_1df8[15]->f_22 - g_1ca8 + g_1caa.y, g_1df8[15]->f_22 - g_1ca8,
                   rc.bottom - (g_1df8[15]->f_22 - g_1ca8 + g_1caa.y), BLACKNESS);
        }
    }
    if (g_1318 > 5)
        return;
    g_943a = 15;
    g_943c = 0;
    r = fn_08_50aa(0xf00);
    if (HIBYTE(r) == g_9324 && g_1318 == 1 && g_90f4 != 6)
        fn_18_5f74();
    if (r != 0xffff)
        fn_08_5df2(15, 0, HIBYTE(r), LOBYTE(r),
                   fn_08_546c(r, &g_1df8[15]->f_0c, &g_1df8[15]->f_0e, g_1df8[15]->f_22 + 1, g_1df8[15]->f_44));
    if (g_1318 > 1)
        return;
    for (i = 0; i < 4; i++) {
        old = g_a16a[i] / 40;
        g_a16a[i] = (((uint8_t)g_a17b[i] >> 1) + g_a16a[i]) % 360;
        if (g_a16a[i] / 40 == old || mode) {
            BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                   7 << g_9156 * 2, 7 << g_9156 * 2, g_966a, g_8914[i].x, g_8914[i].y, SRCCOPY);
            if (g_a18f[i])
                BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                       7 << g_9156 * 2, 7 << g_9156 * 2, g_9656,
                       g_a16a[i] / 40 * 7 << g_9156 * 2, 0, SRCPAINT);
            BitBlt(g_13dc, g_8904[i].x, g_8904[i].y, 7 << g_9156 * 2, 7 << g_9156 * 2,
                   g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678, SRCCOPY);
        }
    }
    if (g_90f4 == 1)
        repulsive_force_weapon(15, 0);
    fn_18_591c();
    if (g_90f4 == 1) {
        if (!g_9676 && rand() % 26000 < (g_a198 + 2) * 2 + g_9334 / 2)
            fn_11_9daa(15, 0);
    } else {
        if (!g_9676 && rand() % 4000 < g_a198 - 2)
            fn_11_9daa(15, 0);
    }
    if (g_1ca6 % 7 == 0)
        attractive_force_weapon(15, 0);
}

/* Per-frame update of the player's ship (object 20:g_9646) in the Demon
 * sub-game [inferred]: shield and animation state, then the scripted flight
 * while g_1318 runs the sequence (2-4 steer to the arena centre, 6 turn,
 * 7..0x58 draw the gate lines, 0x59 done), then collisions. */
/* 18:403e */
void fn_18_403e(void)
{
    int16_t d;
    int16_t w22;
    int16_t w24;
    int16_t i;
    WORD r;

    if (++g_95f6 > 8)
        g_95f6 = 0;
    w24 = g_1df8[g_9324][main_ship].f_24;
    w22 = g_1df8[g_9324][main_ship].f_22;
    if (g_90f4 == 6 && g_1318 > 1)
        return;
    if (!g_7090[main_ship].flag) {
        if (!g_7090[main_ship].f_0e2)
            return;
        g_1df8[g_9324][main_ship].f_26 = 1;
        if (g_7090[main_ship].f_016 < 1) {
            g_1df8[g_9324][main_ship].f_28 = fn_13_100c(main_ship, g_1df8[g_9324][main_ship].f_28);
            fn_13_6716(main_ship);
            g_7090[main_ship].f_016 = 1;
        } else
            g_7090[main_ship].f_016--;
        if (!g_7090[main_ship].flag && g_7090[main_ship].f_084 < g_1e50) {
            g_7090[main_ship].f_0e2 = 0;
            g_1df8[g_9324][main_ship].f_26 = 0;
            g_9530 = 6;
            fn_10_7480(-2, 1);
            fn_18_633c();
        }
        g_7090[main_ship].f_05c = 0;
        g_1df8[g_9324][main_ship].f_12 = w24;
    } else if (g_7090[main_ship].f_0e2) {
        g_1df8[g_9324][main_ship].f_28 = fn_13_100c(main_ship, g_1df8[g_9324][main_ship].f_28);
        if (g_7090[main_ship].f_084 < g_1e50) {
            g_7090[main_ship].f_0e2 = 0;
            g_1df8[g_9324][main_ship].f_26 = 0;
        }
    }
    if (!g_7090[main_ship].f_0e4) {
        if (g_7090[main_ship].f_002 && ++g_1cae > 1) {
            g_1cae = 0;
            if (g_7090[main_ship].flag) {
                g_7090[main_ship].f_05c += g_7090[main_ship].f_05a;
                if (g_7090[main_ship].f_05a == 1 && g_7090[main_ship].f_05b < g_7090[main_ship].f_05c) {
                    g_7090[main_ship].f_05c--;
                    g_7090[main_ship].f_05a = -1;
                } else if (g_7090[main_ship].f_05c < 0) {
                    g_7090[main_ship].f_05c++;
                    g_7090[main_ship].f_05a = 1;
                }
            } else
                g_7090[main_ship].f_05c = 0;
            g_1df8[g_9324][main_ship].f_12 = g_7090[main_ship].f_05c * (w24 + w22) + w24;
        }
    }
    if (g_1318 >= 2) {
        POINT p0;
        POINT p1;
        int16_t dir;
        int16_t a;
        int16_t b;
        int16_t dist;

        dir = g_1df8[g_9324][main_ship].f_28;
        p1.x = g_1df8[g_9324][main_ship].f_22 / 2 + g_1df8[g_9324][main_ship].f_04.x;
        p1.y = g_1df8[g_9324][main_ship].f_22 / 2 + g_1df8[g_9324][main_ship].f_04.y;
        p0.x = (int16_t)(g_88cc / 2);
        p0.y = (int16_t)((int32_t)g_88c0.y * g_88cc / g_88c0.x / 2);
        if (g_1318 >= 6) {
            if (g_1318 >= 7) {
                POINT p2;

                if (g_1318 == 7) {
                    p1.x = g_88c0.x / 2;
                    p1.y = g_88c0.y / 2;
                    p2.y = g_8870[0].f_00.top + 10;
                    p2.x = g_8870[0].f_00.right - 10;
                    fn_11_a4a6(p1, p2, 15);
                } else if (g_1318 == 0x23) {
                    p1.y = g_8870[0].f_00.top + 10;
                    p1.x = g_8870[0].f_00.right - 10;
                    p2.y = g_8870[3].f_00.top + 10;
                    p2.x = g_8870[3].f_00.right - 10;
                    fn_11_a4a6(p1, p2, 15);
                } else if (g_1318 == 0x24) {
                    p1.y = g_8870[0].f_00.top + 10;
                    p1.x = g_8870[0].f_00.right - 10;
                    p2.y = g_8870[1].f_00.top + 10;
                    p2.x = g_8870[1].f_00.right - 10;
                    fn_11_a4a6(p1, p2, 15);
                    PatBlt(g_13dc, g_88f4[0].x, g_88f4[0].y, g_9678, g_9678, BLACKNESS);
                } else if (g_1318 == 0x35) {
                    p1.y = g_8870[3].f_00.top + 10;
                    p1.x = g_8870[3].f_00.right - 10;
                    p2.y = g_8870[2].f_00.top + 10;
                    p2.x = g_8870[2].f_00.right - 10;
                    fn_11_a4a6(p1, p2, 15);
                } else if (g_1318 == 0x36) {
                    p1.y = g_8870[1].f_00.top + 10;
                    p1.x = g_8870[1].f_00.right - 10;
                    p2.y = g_8870[2].f_00.top + 10;
                    p2.x = g_8870[2].f_00.right - 10;
                    fn_11_a4a6(p1, p2, 15);
                    PatBlt(g_13dc, g_88f4[1].x, g_88f4[1].y, g_9678, g_9678, BLACKNESS);
                    PatBlt(g_13dc, g_88f4[3].x, g_88f4[3].y, g_9678, g_9678, BLACKNESS);
                } else if (g_1318 == 0x47) {
                    p1.y = g_8870[2].f_00.top + 10;
                    p1.x = g_8870[2].f_00.right - 10;
                    p2.x = g_88c0.x / 2 + g_88c4.x;
                    p2.y = g_88c0.y / 2 + g_88c4.y;
                    fn_11_a4a6(p1, p2, 15);
                    PatBlt(g_13dc, g_88f4[2].x, g_88f4[2].y, g_9678, g_9678, BLACKNESS);
                    for (i = 0; i < g_9406[g_934a]; i++)
                        if (g_1df8[g_934a][i].f_18 == 0)
                            fn_12_274a(g_934a, i);
                } else if (g_1318 == 0x55) {
                    p2.x = g_88c0.x / 2 + g_88c4.x;
                    p2.y = g_88c0.y / 2 + g_88c4.y;
                    fn_11_a4a6(p2, p1 = fn_08_29ea(p1), 15);
                }
                if (++g_1318 == 0x59)
                    g_9530 = 2;
            } else {
                g_1df8[g_9324][main_ship].f_0e = 0;
                g_1df8[g_9324][main_ship].f_0c = g_1df8[g_9324][main_ship].f_0e;
                if (g_1df8[g_9324][main_ship].f_28 <= 8)
                    g_1df8[g_9324][main_ship].f_28--;
                else
                    g_1df8[g_9324][main_ship].f_28++;
                if (!(g_1df8[g_9324][main_ship].f_28 & 15))
                    g_1318 = 7;
            }
        } else {
            if (g_1318 == 2)
                g_1df8[g_9324][main_ship].f_28 = steer_toward_direction(p1.y, p1.x, p0.y, p0.x,
                        g_1df8[g_9324][main_ship].f_28, 5, main_ship, -1, -1, 0);
            if (g_1318 == 3)
                g_1df8[g_9324][main_ship].f_28 = steer_toward_direction(p1.y, p1.x, p0.y, p0.x,
                        g_1df8[g_9324][main_ship].f_28, 2, main_ship, -1, -1, 0);
            if (g_1318 == 4)
                g_1df8[g_9324][main_ship].f_28 = steer_toward_direction(p1.y, p1.x, p0.y, p0.x,
                        g_1df8[g_9324][main_ship].f_28, 3, main_ship, -1, -1, 0);
            dist = fn_08_285a(&a, &b, p1, p0);
            if (g_88c0.x / 12 < dist && g_1318 == 2)
                g_1318 = 4;
            else if (g_88c0.x / 5 < dist && g_1318 == 4)
                g_1318 = 3;
            else if (g_88c0.x / 6 > dist && g_1318 == 3)
                g_1318 = 4;
            if (g_1df8[g_9324][main_ship].f_28 == dir) {
                int16_t ok;

                ok = 1;
                if (g_1318 == 3) {
                    int32_t dx;
                    int32_t dy;
                    int32_t dot;

                    dx = (int16_t)(p0.x - p1.x);
                    dy = (int16_t)(p0.y - p1.y);
                    dot = dx * g_1df8[g_9324][main_ship].f_0c + dy * g_1df8[g_9324][main_ship].f_0e;
                    if (dot > 0)
                        ok = 0;
                }
                if (ok) {
                    if (g_7090[main_ship].f_002 == 0)
                        fn_11_5ab6(main_ship, 1);
                    if (!(g_95f6 & 1))
                        fn_11_5ab6(main_ship, 3);
                } else if (g_7090[main_ship].f_002)
                    fn_11_5ab6(main_ship, 6);
            }
            if (g_1df8[g_9324][main_ship].f_22 / 2 + g_1df8[g_9324][main_ship].f_00.x > g_88c0.x * 9 / 20
                && g_1df8[g_9324][main_ship].f_22 / 2 + g_1df8[g_9324][main_ship].f_00.x < g_88c0.x * 11 / 20
                && g_1df8[g_9324][main_ship].f_00.y > g_88c0.y * 12 / 20)
                g_1318 = 6;
        }
    } else if (!(g_95f6 & 1))
        fn_11_5ab6(main_ship, 4);
    if (g_1df8[g_9324][main_ship].f_1a && g_7090[main_ship].f_026[0] < 50
        && rand() % (g_7090[main_ship].f_026[0] + 20) < 2)
        fn_07_5b68(g_9324, main_ship, 1);
    fn_08_1b54((char)main_ship | 0x1400, 1);
    g_1df8[20][main_ship].f_10 = (g_1df8[20][main_ship].f_22 + g_1df8[20][main_ship].f_24) * g_1df8[20][main_ship].f_28
        + g_1df8[20][main_ship].f_24;
    fn_18_1934((char)main_ship | 0x1400, 1, g_3a38[main_ship]);
    if (g_1318 == 0x59)
        PatBlt(g_13dc, g_1df8[g_9324][main_ship].f_00.x, g_1df8[g_9324][main_ship].f_00.y,
               g_1df8[g_9324][main_ship].f_22, g_1df8[g_9324][main_ship].f_22, BLACKNESS);
    if (g_1318 >= 6)
        return;
    g_943a = 20;
    g_943c = main_ship;
    r = fn_08_50aa((char)main_ship | 0x1400);
    if (HIBYTE(r) == 15 && g_1318 == 1 && g_90f4 == 1)
        fn_18_5f74();
    if (r != 0xffff)
        fn_08_5df2(20, main_ship, HIBYTE(r), LOBYTE(r),
                   d = fn_08_546c(r, &g_1df8[20][main_ship].f_0c, &g_1df8[20][main_ship].f_0e,
                                  g_1df8[20][main_ship].f_22 + 1, g_1df8[20][main_ship].f_44));
}

/* Checks an object against the Demon arena's wall rectangles and bounces
 * it [inferred]. unused8 stands for a temporary the original drops. */
/* near-match 71%: 18:2c1e (CL stores the unused8 temporary; the game keeps
 * g_88c0 - g_9678 in ax only, and its frame is 2 bytes larger, the extra
 * slot below the POINT return temporary; block-scope temps, casts and
 * extern order tried) */
int16_t fn_18_2c1e(int16_t type, int16_t idx)
{
    int16_t i;
    int16_t j;
    int16_t unused8;
    int16_t n;
    int16_t k;
    POINT pos;
    POINT unused14;
    RECT rc1;
    RECT rc;
    int16_t hit;

    if (type == 30 && g_7090[main_ship].f_024 == 2)
        n = 2;
    else
        n = 1;
    for (k = 0; k < n; k++) {
        if (type == 30) {
            pos.x = g_6098[idx].x[k][0];
            pos.y = g_6098[idx].y[k][0];
            object_sizes[1] = 4;
        } else {
            pos = g_1df8[type][idx].f_00;
            object_sizes[1] = g_1df8[type][idx].f_22 + 2;
        }
        if ((pos.x <= g_9678 || pos.x >= (unused8 = g_88c0.x - g_9678) - object_sizes[1]) &&
            (pos.y >= g_88c0.y - g_9678 - object_sizes[1] || pos.y <= g_9678)) {
        SetRect(&rc, pos.x, pos.y, pos.x + object_sizes[1], pos.y + object_sizes[1]);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 3; j++) {
                if (!IntersectRect(&rc1, &g_8860[i * 3 + j], &rc))
                    continue;
                if (type == 30) {
                    object_masses[1] = 14 - g_6098[idx].z[1][5] * 14 / g_6098[idx].z[1][4];
                    if (g_6098[idx].z[1][5] < 20)
                        object_masses[1] = 18;
                    object_masses[1] *= 2;
                    object_masses[1] = g_96d2[g_7090[g_6098[idx].f_7c].f_04e].f_32 * object_masses[1] / 250;
                    if (g_90f4 == 1)
                        /* g_9448 = object_masses[1]: a second name stops CL
                         * merging this product with the else arm's [layout] */
                        object_masses[1] = (24 - 5 * g_a198) * object_masses[1] * 3 / 20;
                    else
                        object_masses[1] = (9 - g_a198) * object_masses[1] * 3 / 20;
                    k = n;
                } else
                    object_masses[1] = g_1df8[type][idx].f_44;
                g_944a = 0x1f;
                g_944e = i;
                g_943a = g_944c = type;
                g_943c = g_9450 = idx;
                if (type == 30) {
                    g_52dc.x = g_6098[idx].z[1][2] * 5;
                    g_52dc.y = g_6098[idx].z[1][3] * 5;
                } else
                    g_52dc = VIEW(POINT, g_1df8[type][idx].f_0c, 0);
                VIEW(int32_t, g_52e0, 0) = 0;
                g_52e8 = pos;
                g_52e4 = g_8ce4[i * 3 + j];
                object_sizes[0] = g_8d1c[i * 3 + j] + 2;
                if (type == 30)
                    object_masses[0] = 800;
                else
                    object_masses[0] = 20000;
                hit = fn_10_7dd4(&g_52dc.x, &g_52dc.y, &g_52e0.x, &g_52e0.y,
                                 &g_52e8.x, &g_52e8.y, &g_52e4.x, &g_52e4.y,
                                 object_sizes[1] + 1, object_sizes[0],
                                 object_masses[1], object_masses[0],
                                 &g_9436, &g_9438);
                g_9438 = g_9438 < 3 ? 3 : g_9438;
                if (hit) {
                    if (type == 30) {
                        pos = fn_08_2bbe(g_52e8);
                        g_6098[idx].f_30[0][0] = pos.x;
                        g_6098[idx].f_48[0][0] = pos.y;
                        g_6098[idx].z[1][2] = g_52dc.x / 5;
                        g_6098[idx].z[1][3] = g_52dc.y / 5;
                        if (j == 2 && g_a18f[i] && !g_1df8[18]->f_1a) {
                            fn_10_754a(0x24, 0x1e, idx, 2);
                            if (g_90f4 == 6)
                                g_a1cd++;
                            ((uint8_t *)g_a17b)[i] += (char)g_9438;
                            if (((uint8_t *)g_a17b)[i] < 200 &&
                                ((uint8_t *)g_a17b)[i] > 70) {
                                g_a18f[i] = 0;
                                if (g_90f4 == 6)
                                    g_a193[i] = 0;
                                fn_18_4faa(i);
                                ((uint8_t *)g_a17b)[i] = 0xdc;
                            }
                            return 2;
                        }
                        fn_10_754a(0x11, 0x1e, idx, 2);
                    } else {
                        g_1df8[g_944c][g_9450].f_04 = fn_08_2bbe(g_52e8);
                        fn_08_6a44(1);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* Pulls every other object toward object (type, idx) [inferred]. */
/* 18:59ec */
void attractive_force_weapon(int16_t type, int16_t idx)
{
    POINT c;
    POINT d;
    POINT p;
    int16_t dist;
    int16_t t;
    int16_t i;
    int16_t force;

    if (g_1318 <= 1 && g_1df8[type][idx].f_1a) {
    if (subgame_active) {
        c.x = g_1df8[type][idx].f_20 / 2 + g_1df8[type][idx].f_04.x;
        c.y = g_1df8[type][idx].f_20 / 2 + g_1df8[type][idx].f_04.y;
    } else {
        if (!g_7090[idx].f_01e)
            return;
        if (type == 14 && !g_1df8[14][idx].f_54)
            g_7090[idx].f_01e--;
        c.x = g_1df8[type][idx].f_22 / 2 + g_1df8[type][idx].f_00.x;
        c.y = g_1df8[type][idx].f_22 / 2 + g_1df8[type][idx].f_00.y;
    }
    for (t = g_9326; t <= g_9324; t++) {
        if (t == 5)
            continue;
        for (i = 0; i < g_9406[t]; i++) {
            if ((!g_1df8[t][i].f_18 && (g_92e8 || g_1df8[t][i].f_1a) &&
                 !g_1df8[t][i].f_54 && (t != type || i != idx)) || t == 18) {
                if (subgame_active) {
                    d.x = g_1df8[t][i].f_20 / 2 + g_1df8[t][i].f_04.x - c.x;
                    d.y = g_1df8[t][i].f_20 / 2 + g_1df8[t][i].f_04.y - c.y;
                } else {
                    p.x = g_1df8[t][i].f_20 / 2 + g_1df8[t][i].f_04.x;
                    p.y = g_1df8[t][i].f_20 / 2 + g_1df8[t][i].f_04.y;
                    p = fn_08_29ea(p);
                    d.x = p.x - c.x << LO8(g_9150);
                    d.y = p.y - c.y << LO8(g_9150);
                }
                dist = fn_08_35d0(d.x, d.y);
                if (subgame_active) {
                    force = 13;
                    if (t == 19)
                        force = 7;
                } else {
                    force = 11L * g_1df8[type][idx].f_44 / max(g_1df8[t][i].f_44, 50);
                    force = force > 14 ? 14 : force;
                }
                if (g_92e8 && !g_1df8[t][i].f_1a)
                    force *= 2;
                if (subgame_active || dist < 7000 || g_92e8) {
                    g_1df8[t][i].f_0c -= (int32_t)d.x * force / dist;
                    g_1df8[t][i].f_0e -= (int32_t)d.y * force / dist;
                }
            }
        }
    }
    }
}

/* Pushes every nearby object away from a point ahead of object
 * (type, idx) [inferred]. */
/* 18:551a */
void repulsive_force_weapon(int16_t type, int16_t idx)
{
    int16_t dir;
    int16_t dist;
    int16_t force;
    int16_t a;
    int16_t b;
    int16_t i;
    int16_t r;
    int16_t k;
    POINT tp;
    POINT src;
    POINT pp;

    if (type == 14 && !g_1df8[14][idx].f_54) {
        if (!g_7090[idx].f_01e)
            return;
        if (g_1e68 % 14 == 0)
            g_7090[idx].f_01e--;
    }
    dir = g_1df8[type][idx].f_28;
    if (type == 15)
        dir = (dir + 8) & 0xf;
    if (subgame_active)
        r = g_88cc * (15 * g_a198 + 85) / g_88c0.x;
    else
        r = 800;
    src.x = (g_1050[dir].x * r >> 4) + (g_1df8[type][idx].f_20 >> 1) + g_1df8[type][idx].f_04.x;
    src.y = (g_1050[dir].y * r >> 4) + (g_1df8[type][idx].f_20 >> 1) + g_1df8[type][idx].f_04.y;
    pp = fn_08_29ea(src);
    for (i = 0; i < 5; i++) {
        if (g_6098[i].z[1][5] >= 0 && g_6098[i].z[1][4] >= g_6098[i].z[1][5] &&
            (g_6098[i].f_7a != type || g_6098[i].f_7c != idx)) {
            tp.x = g_6098[i].f_30[0][0];
            tp.y = g_6098[i].f_48[0][0];
            dist = fn_08_285a(&a, &b, src, tp);
            if (!dist)
                dist = 1;
            if (dist < 90) {
                force = (int16_t)(dist * 15) / -90 + 20;
                g_6098[i].z[1][2] += (int32_t)a * force / dist;
                g_6098[i].z[1][3] += (int32_t)b * force / dist;
                g_6098[i].f_82 = 1;
            }
        }
    }
    if (!subgame_active)
        for (i = 0; i < g_9406[6]; i++) {
            k = g_6670[i + 4].f_04.x;
            if ((g_2f4c[k].f_26 > g_6670[i + 4].r.right || g_2f4c[k].f_2c == 6) && k != -1 &&
                !g_1df8[6][i].f_18 &&
                (g_6670[i + 4].r.left != type || g_6670[i + 4].r.top != idx)) {
                tp.x = g_1df8[6][i].f_04.x;
                tp.y = g_1df8[6][i].f_04.y;
                dist = fn_08_285a(&a, &b, src, tp);
                if (!dist)
                    dist = 1;
                if (dist < 90) {
                    force = (int16_t)(dist * 15) / -90 + 20;
                    g_1df8[6][i].f_0c += (int32_t)a * force / dist;
                    g_1df8[6][i].f_0e += (int32_t)b * force / dist;
                }
            }
        }
    if (!subgame_active)
        for (i = 0; i < g_9406[5]; i++) {
            if (!g_1df8[5][i].f_18 &&
                (g_5a4c[i].f_04 != type || g_5a4c[i].f_06 != idx)) {
                tp.x = g_1df8[5][i].f_04.x;
                tp.y = g_1df8[5][i].f_04.y;
                dist = fn_08_285a(&a, &b, src, tp);
                if (!dist)
                    dist = 1;
                if (dist < 90) {
                    force = (int16_t)(dist * 15) / -90 + 20;
                    g_1df8[5][i].f_0c += (int32_t)a * force / dist;
                    g_1df8[5][i].f_0e += (int32_t)b * force / dist;
                }
            }
        }
}

/* A wall gun n aims at the player ship and fires when lined up
 * [inferred]. */
/* near-match 26%: 18:49d8 (the game keeps the second q.x/q.y in si/cx and
 * reuses them for d; here they are reloaded from q; layout otherwise the
 * same) */
void fn_18_49d8(int16_t n, int16_t m)
{
    int16_t i;
    int16_t dist;
    int16_t speed;
    int16_t unused_a;
    POINT pos;
    POINT d;
    POINT v;
    POINT c;
    POINT q;
    RECT rc;

    if (g_90f4 == 6 && g_a198 < 6)
        return;
    if (g_a17f[n] < 0) {
        pos.x = g_6098[n].f_30[0][0];
        pos.y = g_6098[n].f_48[0][0];
        v.x = g_6098[n].z[1][2];
        v.y = g_6098[n].z[1][3];
        for (i = 0; i < 4; i++) {
            c.x = (g_8870[i].f_00.right - g_8870[i].f_00.left) / 2 + g_8870[i].f_00.left;
            c.y = (g_8870[i].f_00.bottom - g_8870[i].f_00.top) / 2 + g_8870[i].f_00.top;
            c = fn_08_2bbe(c);
            dist = fn_08_35d0(d.x = c.x - pos.x, d.y = c.y - pos.y);
            speed = fn_08_35d0(v.x, v.y);
            if (!speed)
                speed = 1;
            q.x = (int32_t)dist * v.x / speed + pos.x;
            q.y = (int32_t)dist * v.y / speed + pos.y;
            q = fn_08_29ea(q);
            SetRect(&rc, g_8870[i].f_00.left - 7, g_8870[i].f_00.top - 7,
                    g_8870[i].f_00.right + 7, g_8870[i].f_00.bottom + 7);
            if (PtInRect(&rc, q)) {
            POINT s;
            int16_t steps;
            int16_t dir1;
            int16_t dir2;

            dir1 = (int16_t)(g_1df8[15]->f_28 + 8) % 16;
            s.x = g_1df8[15]->f_22 / 2 + g_1df8[15]->f_04.x;
            s.y = g_1df8[15]->f_22 / 2 + g_1df8[15]->f_04.y;
            dir2 = fn_08_19b0(c.x - s.x, c.y - s.y);
            if (g_9676)
                return;
            if (fn_09_88ba(dir1 - dir2) < 3) {
                if (g_90f4 == 1)
                    dist = (8 - g_a198) * dist / 10;
                else
                    dist = (14 - g_a198) * dist / 10;
                q.x = (int32_t)dist * v.x / speed + pos.x;
                q.y = (int32_t)dist * v.y / speed + pos.y;
                s.x = g_1df8[15]->f_20 / 2 + g_1df8[15]->f_04.x;
                s.y = g_1df8[15]->f_20 / 2 + g_1df8[15]->f_04.y;
                steps = dist / speed;
                if (steps >= (int16_t)(m - 1))
                    return;
                dist = fn_08_35d0(d.x = q.x - s.x, d.y = q.y - s.y);
                if (!dist)
                    dist = 1;
                speed = dist / steps;
                g_a17f[n] = 0;
                g_a199[n].x = s.x;
                g_a199[n].y = s.y;
                VIEW(POINT, g_a1c9, 0) = fn_08_29ea(s);
                MoveTo(g_13dc, g_a1c9, g_a1cb);
                g_a1a9[n].x = (int32_t)d.x * speed / dist;
                g_a1a9[n].y = (int32_t)d.y * speed / dist;
                g_a187[n] = steps;
                return;
            }
            if ((g_90f4 == 1 && (g_a198 + 1) * 2 > rand() % 27) ||
                (g_90f4 == 6 && g_a198 - 1 > rand() % 12))
                fn_11_9daa(15, 0);
            return;
            }
        }
        g_a187[n] = 0;
    }
}

/* Spawns one Demon-arena missile of type g_934a aimed at the player ship
 * [inferred]. Its size f20 is scaled from record 0, not the new one (as in
 * the original). */
/* 18:66e0 */
void fn_18_66e0(void)
{
    POINT p;
    POINT d;
    int16_t i;
    int16_t found;
    POINT unused;
    int16_t speed;
    int16_t dist;

    if (g_9406[g_934a] < 1) {
        for (i = 0; i < g_92ec[g_934a]; i++)
            g_1df8[g_934a][i].f_18 = 1;
        i = -1;
        found = 0;
        do {
            i++;
            if (i < 4) {
                if (g_92ec[g_934a] <= i) {
                    g_92ec[g_934a] = i + 1;
                    GlobalUnlock(g_9100[g_934a]);
                    g_9100[g_934a] = GlobalReAlloc(g_9100[g_934a],
                        (int32_t)(g_92ec[g_934a] < 1 ? 1 : g_92ec[g_934a]) * 0x70,
                        GMEM_MOVEABLE | GMEM_ZEROINIT);
                    g_1df8[g_934a] = (REC_70 *)GlobalLock(g_9100[g_934a]);
                    g_1df8[g_934a][i].f_48 = 9;
                    g_1df8[g_934a][i].f_42 = 8;
                    g_1df8[g_934a][i].f_46 = 4;
                    g_1df8[g_934a][i].f_4c = 0xc0c0c0;
                    g_1df8[g_934a][i].f_5e = fn_07_5090;
                    g_1df8[g_934a][i].f_53 = 0;
                    g_1df8[g_934a][i].f_54 = 0;
                    g_1df8[g_934a][i].f_32 = -1;
                    g_1df8[g_934a][i].f_2e = 0;
                    g_1df8[g_934a][i].f_18 = 1;
                    g_9406[g_934a] = i + 1;
                }
                if (g_1df8[g_934a][i].f_18) {
                    if (g_7090[main_ship].f_026[0] < 50)
                        g_1df8[g_934a][i].f_44 = 1400;
                    else
                        g_1df8[g_934a][i].f_44 = 466;
                    g_1df8[g_934a][i].f_22 = (44 << g_9156) >> 1;
                    if (!g_9156)
                        g_1df8[g_934a][i].f_22 = (int16_t)(g_1df8[g_934a][i].f_22 * 2) / 3;
                    g_1df8[g_934a][i].f_20 = (int16_t)(g_1df8[g_934a]->f_22 * g_88cc / g_88c0.x);
                    g_1df8[g_934a][i].f_24 = (4 << g_9156) >> 1;
                    g_1df8[g_934a][i].f_12 = g_1df8[g_934a][i].f_24;
                    g_1df8[g_934a][i].f_62 = fn_11_3914;
                    g_1df8[g_934a][i].f_2c = 40;
                    g_1df8[g_934a][i].f_1e = 0;
                    g_1df8[g_934a][i].f_2f = 0;
                    g_1df8[g_934a][i].f_18 = 0;
                    p.x = g_1050[(int16_t)(g_1df8[15]->f_28 + 8) % 16].x * (g_1df8[15]->f_22 / 2 + ((44 << g_9156) >> 2)) / 16
                        + g_1df8[15]->f_22 / 2 - ((44 << g_9156) >> 2) + g_1df8[15]->f_00.x;
                    p.y = g_1050[(int16_t)(g_1df8[15]->f_28 + 8) % 16].y * (g_1df8[15]->f_22 / 2 + ((44 << g_9156) >> 2)) / 16
                        + g_1df8[15]->f_22 / 2 - ((44 << g_9156) >> 2) + g_1df8[15]->f_00.y;
                    g_1df8[g_934a][i].f_04 = p = fn_08_2bbe(p);
                    g_1df8[g_934a][i].f_00.x = -1000;
                    g_1df8[g_934a][i].f_08.x = g_1df8[g_934a][i].f_00.x;
                    g_1df8[g_934a][i].f_00.y = -1000;
                    g_1df8[g_934a][i].f_08.y = g_1df8[g_934a][i].f_00.y;
                    d.x = (rand() % (50 - g_a198 * 4) + g_a198 * 3) * g_1df8[g_9324][main_ship].f_0c
                        + g_1df8[g_9324][main_ship].f_22 / 2 + g_1df8[g_9324][main_ship].f_04.x
                        - g_1df8[15]->f_22 / 2 - p.x;
                    d.y = (rand() % (50 - g_a198 * 4) + g_a198 * 3) * g_1df8[g_9324][main_ship].f_0e
                        + g_1df8[g_9324][main_ship].f_22 / 2 + g_1df8[g_9324][main_ship].f_04.y
                        - g_1df8[15]->f_22 / 2 - p.y;
                    dist = fn_08_35d0(d.x, d.y);
                    if (g_90f4 == 1)
                        speed = (g_a198 + 10) * 7;
                    else
                        speed = (g_a198 + 15) * 4;
                    g_1df8[g_934a][i].f_0c = (int32_t)d.x * speed / dist;
                    g_1df8[g_934a][i].f_0e = (int32_t)d.y * speed / dist;
                    g_9406[g_934a] = i + 1;
                    fn_10_754a(0x1c, g_934a, i, found = 1);
                }
            }
        } while (!found && i < 126);
    } else
        fn_07_2080(g_934a);
}
