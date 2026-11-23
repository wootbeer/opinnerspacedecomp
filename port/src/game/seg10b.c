#include "game.h"

/* g_05a0 is declared long in inspace.h; this code reads its two words
 * (world width and height [inferred]). */
                                       
                                       

#define SC(n) ((n) << g_9156 >> 1)
                                       
                                       

/* 10:3864 */
void fn_10_3864(void)
{
    if (g_94ae) {
        if (g_69f4) {
            GlobalUnlock(g_94ae);
            g_69f4 = 0;
        }
        GlobalFree(g_94ae);
        g_94ae = 0;
    }
    if (g_95a4) {
        if (g_6e24) {
            GlobalUnlock(g_95a4);
            g_6e24 = 0;
        }
        GlobalFree(g_95a4);
        g_95a4 = 0;
    }
    g_931a = g_94a2 = g_94a4 = 0;
}

/* 10:01fe */
int16_t fn_10_01fe(void)
{
    switch (g_90f4) {
    case 0:
        fn_15_5932();
        break;
    case 1:
        fn_10_022e(1);
        break;
    }
    return 1;
}

/* Shutdown [inferred]: frees the game's surfaces, DCs and other
 * resources; a != 0 also calls fn_10_7d8e. */
/* 10:022e */
void fn_10_022e(int16_t a)
{
    int16_t i;
    int16_t j;

    g_001a = 1;
    fn_16_631c();
    fn_18_03d6();
    fn_15_14be();
    fn_10_0136();
    fn_10_3864();
    fn_11_02f0();
    if (a)
        fn_10_7d8e();
    for (i = 0; i <= 14; i++)
        for (j = 0; j < g_92ec[i]; j++)
            fn_12_26a4(i, j);
    fn_09_8908();
    fn_09_699e();
    fn_10_5cfa();
    for (i = 0; i <= 5; i++)
        g_38a4[i].a = g_38a4[i].b = -1;
    for (i = 0; i < 4; i++) {
        if (g_5e98[i]) {
            SelectObject(g_5e98[i], g_5ea0[i]);
            DeleteDC(g_5e98[i]);
            g_5e98[i] = 0;
        }
    }
    for (i = 0; i < 3; i++)
        fn_10_37d0(i);
    fn_10_5c1a();
    fn_09_1092();
    fn_07_49b6();
}

/* 10:0522 */
void fn_10_0522(int16_t a)
{
    int16_t i;

    for (i = 0; i < 58; i++)
        fn_10_0552(i, a);
}

/* 10:0552 */
void fn_10_0552(int16_t i, int16_t force)
{
    if (g_39e8[i]) {
        if (!force) {
            if (i == 4 || i == 5 || i == 6 || i == 7)
                return;
            if (i >= 10 && i < 13)
                return;
            if (i == 1 || i == 2 || i == 22 || i == 8 || i == 9 || i == 34)
                return;
        }
        if (g_3a5c[i])
            SelectPalette(g_39e8[i], g_3a5c[i], 0);
        SelectObject(g_39e8[i], g_3974[i]);
        DeleteDC(g_39e8[i]);
        g_39e8[i] = 0;
        if (g_3ad0[i]) {
            DeleteObject(g_3ad0[i]);
            g_3ad0[i] = 0;
        }
    }
}

/* 10:1eb6 */
void fn_10_1eb6(int16_t a)
{
    int16_t i;
    int16_t u;

    i = a + 40;
    if (g_39e8[i]) {
        if (g_3a5c[i])
            SelectPalette(g_39e8[i], g_3a5c[i], 0);
        SelectObject(g_39e8[i], g_3974[i]);
        DeleteDC(g_39e8[i]);
        g_39e8[i] = 0;
        if (g_3ad0[i]) {
            DeleteObject(g_3ad0[i]);
            g_3ad0[i] = 0;
        }
    }
}

/* 10:061a */
void fn_10_061a(void)
{
    int16_t i;

    for (i = 0; i < 58; i++) {
        if (g_39e8[i]) {
            if (g_3a5c[i])
                SelectPalette(g_39e8[i], g_3a5c[i], 0);
            SelectObject(g_39e8[i], g_3974[i]);
            DeleteDC(g_39e8[i]);
            g_39e8[i] = 0;
            if (g_3ad0[i]) {
                DeleteObject(g_3ad0[i]);
                g_3ad0[i] = 0;
            }
        }
    }
}

/* 10:1f30 */
void fn_10_1f30(int16_t a, int16_t b)
{
    int16_t i;
    int16_t j;
    HDC dc;
    HBITMAP bm;
    HBITMAP old;
    HPALETTE pal;

    j = b + 40;
    i = a + 40;
    dc = g_39e8[i];
    bm = g_3ad0[i];
    old = g_3974[i];
    pal = g_3a5c[i];
    g_39e8[i] = g_39e8[j];
    g_3ad0[i] = g_3ad0[j];
    g_3974[i] = g_3974[j];
    g_3a5c[i] = g_3a5c[j];
    g_39e8[j] = dc;
    g_3ad0[j] = bm;
    g_3974[j] = old;
    g_3a5c[j] = pal;
}

/* 10:37d0 */
void fn_10_37d0(int16_t i)
{
    if (g_915c[i].f_0c) {
        SelectObject(g_915c[i].f_0c, g_915c[i].f_14);
        if (g_920e)
            SelectPalette(g_915c[i].f_0c, g_915c[i].pal, 0);
        DeleteDC(g_915c[i].f_0c);
        DeleteObject(g_915c[i].f_10);
        g_915c[i].f_0c = 0;
    }
    if (g_915c[i].f_0e) {
        SelectObject(g_915c[i].f_0e, g_915c[i].f_16);
        DeleteDC(g_915c[i].f_0e);
        DeleteObject(g_915c[i].f_12);
        g_915c[i].f_0e = 0;
    }
}

/* 10:1620 */
void fn_10_1620(int16_t i)
{
    int16_t w;
    int16_t j;
    int16_t r;
    int16_t ang;

    w = g_96d2[i].f_2a;
    r = g_96d2[i].f_02;
    for (j = 0, ang = 270; j < 16; j++, ang -= j % 2 + 22) {
        g_7ba0[i][j].x = fn_06_720c(ang) * r / 127 + w / 2;
        g_7ba0[i][j].y = w / 2 + fn_06_71b2(ang) * r / -127;
    }
}

/* 10:1460 */
void fn_10_1460(int16_t i)
{
    int16_t w;
    int16_t j;
    int16_t r;
    int16_t ang;

    w = g_96d2[i].f_2a;
    r = g_96d2[i].f_00 + 3;
    for (j = 0, ang = 450; j < 16; j++, ang -= j % 2 + 22) {
        g_7b60[i][j].x = fn_06_720c(ang) * r / 128 + w / 2;
        g_7b60[i][j].y = w / 2 - fn_06_71b2(ang) * r / 128;
    }
}

/* 10:069a */
void fn_10_069a(void)
{
    int16_t i;

    for (i = 0; i < g_92ec[2]; i++) {
        g_1df8[2][i].f_18 = 1;
        g_52ec[i].f_10 = -1;
        g_52ec[i].f_12 = 0;
        g_52ec[i].f_14 = 0;
        g_52ec[i].f_08 = 0;
        g_52ec[i].f_0a = 0;
        switch (i / 8) {
        case 0:
            g_52ec[i].f_16 = 0x11;
            break;
        case 1:
            g_52ec[i].f_16 = 0xd;
            break;
        case 2:
            g_52ec[i].f_16 = 0xb;
            break;
        case 3:
            g_52ec[i].f_16 = 9;
            break;
        }
    }
}

/* 10:0136 */
void fn_10_0136(void)
{
    int16_t i;

    fn_10_7480(-1, 1);
    fn_15_1328(1);
    fn_10_0522(0);
    fn_06_626c();
    fn_18_0ba0();
    if (g_929a) {
        SelectObject(g_929a, g_9296);
        if (g_92a0)
            SelectPalette(g_929a, g_92a0, 0);
        DeleteDC(g_929a);
        DeleteObject(g_9294);
        g_929a = g_9294 = 0;
    }
    for (i = 0; i < 2; i++) {
        if (g_3820[i]) {
            DeleteObject(g_3820[i]);
            g_3820[i] = 0;
        }
        if (g_5ea8[i]) {
            DeleteObject(g_5ea8[i]);
            g_5ea8[i] = 0;
        }
    }
}

/* Loads the 8x8 int table g_3824 from resource 0x87 of type 0x15e0 in
 * library g_9210. */
/* 10:38e0 */
void fn_10_38e0(void)
{
    int16_t i;
    int16_t j;
    int16_t k;
    HGLOBAL hg;
    HRSRC hr;
    int16_t *p;
    int32_t size;

    p = 0;
    hr = FindResource(g_9210, MAKEINTRESOURCE(0x87), MAKEINTRESOURCE(0x15e0));
    if (hr) {
        SizeofResource(g_9210, hr);
        hg = LoadResource(g_9210, hr);
        if (hg)
            p = (int16_t *)LockResource(hg);
    }
    for (i = k = 0; i < 8; i++)
        for (j = 0; j < 8; j++, k++)
            g_3824[i][j] = p[k];
    if (p) {
        GlobalUnlock(hg);
        p = 0;
    }
    if (hg)
        FreeResource(hg);
}

/* Frees surfaces 23..27 (g_39e8 DCs) whose key in g_38a4 matches neither
 * of the two entries g_4ed4[0..1]. */
/* 10:1dd8 */
void fn_10_1dd8(void)
{
    int16_t i;
    int16_t j;
    int16_t found;

    for (i = 23; i < 28; i++) {
        if (g_39e8[i]) {
            for (j = found = 0; j < 2; j++)
                if (g_4d90[g_4ed4[j]].f_10 == g_38a4[i - 23].b &&
                    g_4d90[g_4ed4[j]].f_0e == g_38a4[i - 23].a &&
                    g_4d90[g_4ed4[j]].f_01 == g_38a4[i - 23].c)
                    found = 1;
            if (!found) {
                if (g_3a5c[i])
                    SelectPalette(g_39e8[i], g_3a5c[i], 0);
                SelectObject(g_39e8[i], g_3974[i]);
                DeleteDC(g_39e8[i]);
                g_38a4[i - 23].a = g_38a4[i - 23].b = g_39e8[i] = 0;
                if (g_3ad0[i]) {
                    DeleteObject(g_3ad0[i]);
                    g_3ad0[i] = 0;
                }
            }
        }
    }
}

/* Fills g_7be0[i][k] (k = 0, 1) with 16 points of an ellipse with radii
 * g_96d2[i].f68[k], centred in a g_96d2[i].f2a square. */
/* 10:1502 */
void fn_10_1502(int16_t i)
{
    int16_t w;
    int16_t j;
    int16_t k;
    int16_t rx[2];
    int16_t ry[2];
    int16_t ang;

    w = g_96d2[i].f_2a;
    for (j = 0; j < 2; j++) {
        rx[j] = VIEWP(POINT *, g_96d2[i].f_68, 0)[j].x;
        ry[j] = VIEWP(POINT *, g_96d2[i].f_68, 0)[j].y;
    }
    for (k = 0; k < 2; k++) {
        for (ang = j = 0; j < 16; j++, ang += j % 2 + 22) {
            g_7be0[i][k][j].x = w / 2 + (fn_06_720c(ang) * rx[k] - fn_06_71b2(ang) * ry[k]) / 128;
            g_7be0[i][k][j].y = (fn_06_720c(ang) * ry[k] + fn_06_71b2(ang) * rx[k]) / 128 + w / 2;
        }
    }
}

/* Fills the 28 0x50-byte records at DS:2f4c with their start values;
 * f3e depends on g_920c == 3 [inferred: difficulty]. Records without
 * that difference still test it with two equal arms: CL merges equal
 * constant stores within a basic block, and these tests are what keep
 * the game's per-record grouping [inferred]. */
/* 10:1fb2 */
void fn_10_1fb2(void)
{
    g_2f4c[0].f_08 = 0xba;
    g_2f4c[0].f_30 = 0xa;
    g_2f4c[0].f_12 = 0;
    g_2f4c[0].f_0c = 0;
    g_2f4c[0].f_0a = 0;
    g_2f4c[0].f_4a = 0;
    g_2f4c[0].f_3a = 0;
    g_2f4c[0].f_38 = 0;
    g_2f4c[0].f_32 = 0;
    g_2f4c[0].f_34 = 0;
    g_2f4c[0].f_36 = 0;
    g_2f4c[0].f_4e = 0;
    if (g_920c == 3)
        g_2f4c[0].f_3e = -1;
    else
        g_2f4c[0].f_3e = -1;
    g_2f4c[5].f_0c = 1;
    g_2f4c[5].f_0a = 0xbf;
    g_2f4c[5].f_08 = 0xbf;
    g_2f4c[5].f_30 = 7;
    g_2f4c[5].f_28 = 0x15e;
    g_2f4c[5].f_38 = 0x14;
    g_2f4c[5].f_32 = 4;
    g_2f4c[5].f_36 = 8;
    g_2f4c[5].f_12 = 0;
    g_2f4c[5].f_4a = 0;
    g_2f4c[5].f_34 = 0;
    g_2f4c[5].f_4e = 0;
    g_2f4c[5].f_3c = 0x2bc;
    if (g_920c == 3)
        g_2f4c[5].f_3e = -1;
    else
        g_2f4c[5].f_3e = -1;
    g_2f4c[4].f_0c = 1;
    g_2f4c[4].f_0a = 0xc4;
    g_2f4c[4].f_08 = 0xbe;
    g_2f4c[4].f_30 = 7;
    g_2f4c[4].f_3a = 0x15e;
    g_2f4c[4].f_38 = 0x14;
    g_2f4c[4].f_32 = 5;
    g_2f4c[4].f_36 = 8;
    g_2f4c[4].f_12 = 0;
    g_2f4c[4].f_4a = 0;
    g_2f4c[4].f_34 = 0;
    g_2f4c[4].f_4e = 0;
    g_2f4c[4].f_3c = 0x28a;
    if (g_920c == 3)
        g_2f4c[4].f_3e = 5;
    else
        g_2f4c[4].f_3e = -1;
    g_2f4c[3].f_0a = 0xc5;
    g_2f4c[3].f_08 = 0xbd;
    g_2f4c[3].f_30 = 0x50;
    g_2f4c[3].f_0c = 1;
    g_2f4c[3].f_4a = 1;
    g_2f4c[3].f_3a = 0x12c;
    g_2f4c[3].f_32 = 7;
    g_2f4c[3].f_34 = 4;
    g_2f4c[3].f_38 = 0x14;
    g_2f4c[3].f_36 = 0x14;
    g_2f4c[3].f_12 = 0;
    g_2f4c[3].f_4e = 0;
    g_2f4c[3].f_3c = 0x3b6;
    if (g_920c == 3)
        g_2f4c[3].f_3e = 5;
    else
        g_2f4c[3].f_3e = 0xe;
    g_2f4c[1].f_0c = 3;
    g_2f4c[1].f_0a = 0xc2;
    g_2f4c[1].f_08 = 0xbb;
    g_2f4c[1].f_30 = 0x19;
    g_2f4c[1].f_12 = 0;
    g_2f4c[1].f_4a = 0;
    g_2f4c[1].f_3a = 0xc8;
    g_2f4c[1].f_32 = 6;
    g_2f4c[1].f_34 = 1;
    g_2f4c[1].f_28 = 0x14;
    g_2f4c[1].f_36 = 0x14;
    g_2f4c[1].f_4e = 2;
    g_2f4c[1].f_3c = 0x258;
    if (g_920c == 3)
        g_2f4c[1].f_3e = 5;
    else
        g_2f4c[1].f_3e = 0x11;
    g_2f4c[2].f_0c = 3;
    g_2f4c[2].f_0a = 0xbe;
    g_2f4c[2].f_08 = 0xbc;
    g_2f4c[2].f_30 = 0x28;
    g_2f4c[2].f_12 = 0;
    g_2f4c[2].f_4a = 0;
    g_2f4c[2].f_3a = 0x118;
    g_2f4c[2].f_38 = 0x3c;
    g_2f4c[2].f_32 = 6;
    g_2f4c[2].f_34 = 2;
    g_2f4c[2].f_36 = 0x19;
    g_2f4c[2].f_4e = 1;
    g_2f4c[2].f_3c = 0x3e8;
    if (g_920c == 3)
        g_2f4c[2].f_3e = 5;
    else
        g_2f4c[2].f_3e = 0xf;
    g_2f4c[15].f_0c = 3;
    g_2f4c[15].f_0a = 0xbe;
    g_2f4c[15].f_08 = 0xc9;
    g_2f4c[15].f_30 = 0x1a;
    g_2f4c[15].f_3a = 0x118;
    g_2f4c[15].f_38 = 0x3c;
    g_2f4c[15].f_34 = 2;
    g_2f4c[15].f_36 = 0x14;
    g_2f4c[15].f_12 = 0;
    g_2f4c[15].f_4a = 0;
    g_2f4c[15].f_32 = 0;
    g_2f4c[15].f_4e = 0;
    g_2f4c[15].f_3c = 0x2ee;
    if (g_920c == 3)
        g_2f4c[15].f_3e = 5;
    else
        g_2f4c[15].f_3e = -1;
    g_2f4c[6].f_14 = 8;
    g_2f4c[6].f_26 = 0xc8;
    g_2f4c[6].f_28 = 0x32;
    g_2f4c[6].f_2a = 7;
    g_2f4c[6].f_00 = 0x17;
    g_2f4c[6].f_0c = 1;
    g_2f4c[6].f_10 = 1;
    g_2f4c[6].f_40 = 1;
    g_2f4c[6].f_2c = 1;
    g_2f4c[6].f_42 = 1;
    g_2f4c[6].f_02 = 1;
    g_2f4c[6].f_06 = 0x172;
    g_2f4c[6].f_08 = 0xc0;
    g_2f4c[6].f_0a = -1;
    g_2f4c[6].f_04 = -1;
    g_2f4c[6].f_20 = 0x1c;
    g_2f4c[6].f_0e = 2;
    g_2f4c[6].f_12 = 2;
    g_2f4c[6].f_24 = 2;
    g_2f4c[6].f_18 = 0x14;
    g_2f4c[6].f_30 = 0x14;
    g_2f4c[6].f_3a = 0x2bc;
    g_2f4c[6].f_16 = 0x64;
    g_2f4c[6].f_38 = 0x64;
    g_2f4c[6].f_32 = 9;
    g_2f4c[6].f_22 = 3;
    g_2f4c[6].f_34 = 3;
    g_2f4c[6].f_1a = 0;
    g_2f4c[6].f_1c = 0;
    g_2f4c[6].f_1e = 0;
    g_2f4c[6].f_44 = 0;
    g_2f4c[6].f_46 = 0;
    g_2f4c[6].f_2e = 0;
    g_2f4c[6].f_48 = 0;
    g_2f4c[6].f_4a = 0;
    g_2f4c[6].f_36 = 0;
    g_2f4c[6].f_4e = 0;
    g_2f4c[6].f_3c = 0x44c;
    if (g_920c == 3)
        g_2f4c[6].f_3e = 7;
    else
        g_2f4c[6].f_3e = 8;
    g_2f4c[8].f_14 = 0xa;
    g_2f4c[8].f_16 = 0x78;
    g_2f4c[8].f_26 = 0xc8;
    g_2f4c[8].f_28 = 0x28;
    g_2f4c[8].f_2a = 9;
    g_2f4c[8].f_00 = 0x17;
    g_2f4c[8].f_0c = 1;
    g_2f4c[8].f_10 = 1;
    g_2f4c[8].f_2c = 1;
    g_2f4c[8].f_42 = 1;
    g_2f4c[8].f_44 = 1;
    g_2f4c[8].f_02 = 1;
    g_2f4c[8].f_06 = 0x172;
    g_2f4c[8].f_08 = 0xc2;
    g_2f4c[8].f_0a = -1;
    g_2f4c[8].f_04 = -1;
    g_2f4c[8].f_20 = 0x1c;
    g_2f4c[8].f_12 = 3;
    g_2f4c[8].f_22 = 3;
    g_2f4c[8].f_0e = 2;
    g_2f4c[8].f_24 = 2;
    g_2f4c[8].f_18 = 0x14;
    g_2f4c[8].f_30 = 0x14;
    g_2f4c[8].f_3a = 0x17c;
    g_2f4c[8].f_38 = 0x82;
    g_2f4c[8].f_32 = 7;
    g_2f4c[8].f_34 = 8;
    g_2f4c[8].f_1a = 0;
    g_2f4c[8].f_1c = 0;
    g_2f4c[8].f_1e = 0;
    g_2f4c[8].f_40 = 0;
    g_2f4c[8].f_46 = 0;
    g_2f4c[8].f_2e = 0;
    g_2f4c[8].f_48 = 0;
    g_2f4c[8].f_4a = 0;
    g_2f4c[8].f_36 = 0;
    g_2f4c[8].f_4e = 0;
    g_2f4c[8].f_3c = 0x2ee;
    if (g_920c == 3)
        g_2f4c[8].f_3e = 7;
    else
        g_2f4c[8].f_3e = -1;
    g_2f4c[7].f_12 = 4;
    g_2f4c[7].f_16 = 0x64;
    g_2f4c[7].f_18 = 0x14;
    g_2f4c[7].f_26 = 0xc8;
    g_2f4c[7].f_00 = 0x17;
    g_2f4c[7].f_0c = 1;
    g_2f4c[7].f_10 = 1;
    g_2f4c[7].f_2c = 1;
    g_2f4c[7].f_42 = 1;
    g_2f4c[7].f_44 = 1;
    g_2f4c[7].f_46 = 1;
    g_2f4c[7].f_02 = 1;
    g_2f4c[7].f_06 = 0x172;
    g_2f4c[7].f_08 = 0xc1;
    g_2f4c[7].f_0a = -1;
    g_2f4c[7].f_04 = -1;
    g_2f4c[7].f_20 = 0x1c;
    g_2f4c[7].f_22 = 3;
    g_2f4c[7].f_0e = 2;
    g_2f4c[7].f_24 = 2;
    g_2f4c[7].f_30 = 0x10;
    g_2f4c[7].f_3a = 0x168;
    g_2f4c[7].f_38 = 0x6e;
    g_2f4c[7].f_14 = 7;
    g_2f4c[7].f_2a = 7;
    g_2f4c[7].f_32 = 7;
    g_2f4c[7].f_34 = 8;
    g_2f4c[7].f_1a = 0;
    g_2f4c[7].f_1c = 0;
    g_2f4c[7].f_1e = 0;
    g_2f4c[7].f_40 = 0;
    g_2f4c[7].f_28 = 0;
    g_2f4c[7].f_2e = 0;
    g_2f4c[7].f_48 = 0;
    g_2f4c[7].f_4a = 0;
    g_2f4c[7].f_36 = 0;
    g_2f4c[7].f_4e = 0;
    g_2f4c[7].f_3c = 0x320;
    if (g_920c == 3)
        g_2f4c[7].f_3e = -1;
    else
        g_2f4c[7].f_3e = -1;
    g_2f4c[12].f_12 = 4;
    g_2f4c[12].f_14 = 8;
    g_2f4c[12].f_16 = 0x5a;
    g_2f4c[12].f_18 = 0x14;
    g_2f4c[12].f_26 = 0xc8;
    g_2f4c[12].f_0c = 1;
    g_2f4c[12].f_0e = 1;
    g_2f4c[12].f_10 = 1;
    g_2f4c[12].f_1c = 1;
    g_2f4c[12].f_2c = 1;
    g_2f4c[12].f_42 = 1;
    g_2f4c[12].f_48 = 7;
    g_2f4c[12].f_00 = 0x13;
    g_2f4c[12].f_06 = 0xa0;
    g_2f4c[12].f_08 = 0xc6;
    g_2f4c[12].f_0a = -1;
    g_2f4c[12].f_04 = -1;
    g_2f4c[12].f_20 = 0x4e;
    g_2f4c[12].f_1a = 2;
    g_2f4c[12].f_1e = 2;
    g_2f4c[12].f_22 = 2;
    g_2f4c[12].f_02 = 3;
    g_2f4c[12].f_24 = 3;
    g_2f4c[12].f_30 = 0x10;
    g_2f4c[12].f_3a = 0x12c;
    g_2f4c[12].f_38 = 0x78;
    g_2f4c[12].f_32 = 5;
    g_2f4c[12].f_2a = 6;
    g_2f4c[12].f_34 = 6;
    g_2f4c[12].f_40 = 0;
    g_2f4c[12].f_28 = 0;
    g_2f4c[12].f_44 = 0;
    g_2f4c[12].f_46 = 0;
    g_2f4c[12].f_2e = 0;
    g_2f4c[12].f_4a = 0;
    g_2f4c[12].f_36 = 0;
    g_2f4c[12].f_4e = 0;
    g_2f4c[12].f_3c = 0x1f4;
    if (g_920c == 3)
        g_2f4c[12].f_3e = 0xa;
    else
        g_2f4c[12].f_3e = 5;
    g_2f4c[18].f_14 = 6;
    g_2f4c[18].f_16 = 0x4b;
    g_2f4c[18].f_18 = 0x14;
    g_2f4c[18].f_26 = 0x6a;
    g_2f4c[18].f_00 = 0x17;
    g_2f4c[18].f_06 = 0x14a;
    g_2f4c[18].f_08 = 0xcc;
    g_2f4c[18].f_0a = -1;
    g_2f4c[18].f_04 = -1;
    g_2f4c[18].f_20 = 2;
    g_2f4c[18].f_02 = 3;
    g_2f4c[18].f_24 = 3;
    g_2f4c[18].f_30 = 0x10;
    g_2f4c[18].f_3a = 0x12c;
    g_2f4c[18].f_38 = 0x78;
    g_2f4c[18].f_2a = 4;
    g_2f4c[18].f_2c = 4;
    g_2f4c[18].f_22 = 4;
    g_2f4c[18].f_32 = 4;
    g_2f4c[18].f_0c = 1;
    g_2f4c[18].f_0e = 1;
    g_2f4c[18].f_10 = 1;
    g_2f4c[18].f_12 = 1;
    g_2f4c[18].f_42 = 1;
    g_2f4c[18].f_34 = 1;
    g_2f4c[18].f_1a = 0;
    g_2f4c[18].f_1c = 0;
    g_2f4c[18].f_1e = 0;
    g_2f4c[18].f_40 = 0;
    g_2f4c[18].f_28 = 0;
    g_2f4c[18].f_44 = 0;
    g_2f4c[18].f_46 = 0;
    g_2f4c[18].f_2e = 0;
    g_2f4c[18].f_48 = 0;
    g_2f4c[18].f_4a = 0;
    g_2f4c[18].f_36 = 0;
    g_2f4c[18].f_4e = 0;
    g_2f4c[18].f_3c = 0x28a;
    if (g_920c == 3)
        g_2f4c[18].f_3e = 7;
    else
        g_2f4c[18].f_3e = 4;
    g_2f4c[19].f_16 = 0x4b;
    g_2f4c[19].f_18 = 0x14;
    g_2f4c[19].f_26 = 0x6a;
    g_2f4c[19].f_2a = 7;
    g_2f4c[19].f_2c = 6;
    g_2f4c[19].f_00 = 0x1b;
    g_2f4c[19].f_06 = 0x14f;
    g_2f4c[19].f_08 = 0xcd;
    g_2f4c[19].f_0a = -1;
    g_2f4c[19].f_04 = -1;
    g_2f4c[19].f_20 = 2;
    g_2f4c[19].f_02 = 3;
    g_2f4c[19].f_22 = 3;
    g_2f4c[19].f_24 = 3;
    g_2f4c[19].f_30 = 0x10;
    g_2f4c[19].f_3a = 0x12c;
    g_2f4c[19].f_38 = 0x78;
    g_2f4c[19].f_14 = 4;
    g_2f4c[19].f_32 = 4;
    g_2f4c[19].f_0c = 1;
    g_2f4c[19].f_0e = 1;
    g_2f4c[19].f_10 = 1;
    g_2f4c[19].f_12 = 1;
    g_2f4c[19].f_42 = 1;
    g_2f4c[19].f_34 = 1;
    g_2f4c[19].f_1a = 0;
    g_2f4c[19].f_1c = 0;
    g_2f4c[19].f_1e = 0;
    g_2f4c[19].f_40 = 0;
    g_2f4c[19].f_28 = 0;
    g_2f4c[19].f_44 = 0;
    g_2f4c[19].f_46 = 0;
    g_2f4c[19].f_2e = 0;
    g_2f4c[19].f_48 = 0;
    g_2f4c[19].f_4a = 0;
    g_2f4c[19].f_36 = 0;
    g_2f4c[19].f_4e = 0;
    g_2f4c[19].f_3c = 0x2bc;
    if (g_920c == 3)
        g_2f4c[19].f_3e = 7;
    else
        g_2f4c[19].f_3e = 0x15;
    g_2f4c[20].f_14 = 6;
    g_2f4c[20].f_16 = 0x4b;
    g_2f4c[20].f_18 = 0x14;
    g_2f4c[20].f_26 = 0x6a;
    g_2f4c[20].f_2a = 5;
    g_2f4c[20].f_00 = 0x15;
    g_2f4c[20].f_06 = 0xb9;
    g_2f4c[20].f_08 = 0xce;
    g_2f4c[20].f_0a = -1;
    g_2f4c[20].f_04 = -1;
    g_2f4c[20].f_20 = 2;
    g_2f4c[20].f_02 = 3;
    g_2f4c[20].f_24 = 3;
    g_2f4c[20].f_30 = 0x10;
    g_2f4c[20].f_3a = 0x12c;
    g_2f4c[20].f_38 = 0x78;
    g_2f4c[20].f_2c = 4;
    g_2f4c[20].f_22 = 4;
    g_2f4c[20].f_32 = 4;
    g_2f4c[20].f_0c = 1;
    g_2f4c[20].f_0e = 1;
    g_2f4c[20].f_10 = 1;
    g_2f4c[20].f_12 = 1;
    g_2f4c[20].f_42 = 1;
    g_2f4c[20].f_34 = 1;
    g_2f4c[20].f_1a = 0;
    g_2f4c[20].f_1c = 0;
    g_2f4c[20].f_1e = 0;
    g_2f4c[20].f_40 = 0;
    g_2f4c[20].f_28 = 0;
    g_2f4c[20].f_44 = 0;
    g_2f4c[20].f_46 = 0;
    g_2f4c[20].f_2e = 0;
    g_2f4c[20].f_48 = 0;
    g_2f4c[20].f_4a = 0;
    g_2f4c[20].f_36 = 0;
    g_2f4c[20].f_4e = 0;
    g_2f4c[20].f_3c = 0x226;
    if (g_920c == 3)
        g_2f4c[20].f_3e = 7;
    else
        g_2f4c[20].f_3e = 0xb;
    g_2f4c[10].f_14 = 7;
    g_2f4c[10].f_16 = 0x32;
    g_2f4c[10].f_18 = 0x14;
    g_2f4c[10].f_26 = 0x40;
    g_2f4c[10].f_10 = 1;
    g_2f4c[10].f_12 = 1;
    g_2f4c[10].f_2c = 1;
    g_2f4c[10].f_42 = 1;
    g_2f4c[10].f_2a = 6;
    g_2f4c[10].f_2e = 6;
    g_2f4c[10].f_48 = 6;
    g_2f4c[10].f_00 = 0x16;
    g_2f4c[10].f_08 = 0xc4;
    g_2f4c[10].f_06 = 0x96;
    g_2f4c[10].f_0a = 0x96;
    g_2f4c[10].f_04 = -1;
    g_2f4c[10].f_20 = 0x18;
    g_2f4c[10].f_22 = 3;
    g_2f4c[10].f_0c = 2;
    g_2f4c[10].f_24 = 2;
    g_2f4c[10].f_30 = 0xc;
    g_2f4c[10].f_3a = 0x104;
    g_2f4c[10].f_38 = 0x50;
    g_2f4c[10].f_0e = 4;
    g_2f4c[10].f_32 = 4;
    g_2f4c[10].f_02 = 5;
    g_2f4c[10].f_34 = 5;
    g_2f4c[10].f_1a = 0;
    g_2f4c[10].f_1c = 0;
    g_2f4c[10].f_1e = 0;
    g_2f4c[10].f_40 = 0;
    g_2f4c[10].f_28 = 0;
    g_2f4c[10].f_44 = 0;
    g_2f4c[10].f_46 = 0;
    g_2f4c[10].f_4a = 0;
    g_2f4c[10].f_36 = 0;
    g_2f4c[10].f_4e = 0;
    g_2f4c[10].f_3c = 0x1c2;
    if (g_920c == 3)
        g_2f4c[10].f_3e = -1;
    else
        g_2f4c[10].f_3e = -1;
    g_2f4c[11].f_14 = 7;
    g_2f4c[11].f_18 = 0x14;
    g_2f4c[11].f_16 = 0x64;
    g_2f4c[11].f_26 = 0x64;
    g_2f4c[11].f_2a = 8;
    g_2f4c[11].f_00 = 0x17;
    g_2f4c[11].f_0c = 1;
    g_2f4c[11].f_10 = 1;
    g_2f4c[11].f_12 = 1;
    g_2f4c[11].f_2c = 1;
    g_2f4c[11].f_42 = 1;
    g_2f4c[11].f_46 = 1;
    g_2f4c[11].f_02 = 1;
    g_2f4c[11].f_06 = 0x172;
    g_2f4c[11].f_08 = 0xc5;
    g_2f4c[11].f_0a = -1;
    g_2f4c[11].f_04 = -1;
    g_2f4c[11].f_20 = 0x1c;
    g_2f4c[11].f_0e = 2;
    g_2f4c[11].f_24 = 2;
    g_2f4c[11].f_30 = 0xc;
    g_2f4c[11].f_3a = 0x122;
    g_2f4c[11].f_38 = 0x5a;
    g_2f4c[11].f_32 = 4;
    g_2f4c[11].f_22 = 3;
    g_2f4c[11].f_34 = 3;
    g_2f4c[11].f_1a = 0;
    g_2f4c[11].f_1c = 0;
    g_2f4c[11].f_1e = 0;
    g_2f4c[11].f_40 = 0;
    g_2f4c[11].f_28 = 0;
    g_2f4c[11].f_44 = 0;
    g_2f4c[11].f_2e = 0;
    g_2f4c[11].f_48 = 0;
    g_2f4c[11].f_4a = 0;
    g_2f4c[11].f_36 = 0;
    g_2f4c[11].f_4e = 0;
    g_2f4c[11].f_3c = 0x1c2;
    if (g_920c == 3)
        g_2f4c[11].f_3e = 7;
    else
        g_2f4c[11].f_3e = -1;
    g_2f4c[9].f_14 = 9;
    g_2f4c[9].f_16 = 0x46;
    g_2f4c[9].f_18 = 0x14;
    g_2f4c[9].f_12 = 4;
    g_2f4c[9].f_1c = 4;
    g_2f4c[9].f_26 = 0xc8;
    g_2f4c[9].f_0e = 1;
    g_2f4c[9].f_10 = 1;
    g_2f4c[9].f_40 = 1;
    g_2f4c[9].f_2c = 1;
    g_2f4c[9].f_42 = 1;
    g_2f4c[9].f_46 = 1;
    g_2f4c[9].f_48 = 5;
    g_2f4c[9].f_00 = 0x15;
    g_2f4c[9].f_06 = 0xa1;
    g_2f4c[9].f_08 = 0xc3;
    g_2f4c[9].f_0a = -1;
    g_2f4c[9].f_04 = -1;
    g_2f4c[9].f_0c = 2;
    g_2f4c[9].f_1a = 2;
    g_2f4c[9].f_20 = 2;
    g_2f4c[9].f_22 = 2;
    g_2f4c[9].f_1e = 3;
    g_2f4c[9].f_02 = 3;
    g_2f4c[9].f_24 = 3;
    g_2f4c[9].f_30 = 0x10;
    g_2f4c[9].f_3a = 0x10e;
    g_2f4c[9].f_38 = 0x55;
    g_2f4c[9].f_2a = 6;
    g_2f4c[9].f_32 = 6;
    g_2f4c[9].f_34 = 7;
    g_2f4c[9].f_28 = 0;
    g_2f4c[9].f_44 = 0;
    g_2f4c[9].f_2e = 0;
    g_2f4c[9].f_4a = 0;
    g_2f4c[9].f_36 = 0;
    g_2f4c[9].f_4e = 0;
    g_2f4c[9].f_3c = 0x226;
    if (g_920c == 3)
        g_2f4c[9].f_3e = 0xa;
    else
        g_2f4c[9].f_3e = 0xa;
    g_2f4c[23].f_0c = 3;
    g_2f4c[23].f_0a = 0xc6;
    g_2f4c[23].f_08 = 0xd1;
    g_2f4c[23].f_30 = 0x2bc;
    g_2f4c[23].f_4a = 1;
    g_2f4c[23].f_3a = 0x384;
    g_2f4c[23].f_38 = 0x32;
    g_2f4c[23].f_32 = 7;
    g_2f4c[23].f_36 = 0x64;
    g_2f4c[23].f_12 = 0;
    g_2f4c[23].f_34 = 0;
    g_2f4c[23].f_4e = 0;
    g_2f4c[23].f_3c = 0;
    if (g_920c == 3)
        g_2f4c[23].f_3e = 5;
    else
        g_2f4c[23].f_3e = -1;
    g_2f4c[13].f_0c = 3;
    g_2f4c[13].f_0a = 0xc3;
    g_2f4c[13].f_08 = 0xc7;
    g_2f4c[13].f_30 = 4;
    g_2f4c[13].f_3a = 0x12c;
    g_2f4c[13].f_38 = 0x28;
    g_2f4c[13].f_12 = 0;
    g_2f4c[13].f_4a = 0;
    g_2f4c[13].f_32 = 0;
    g_2f4c[13].f_34 = 0;
    g_2f4c[13].f_36 = 0;
    g_2f4c[13].f_4e = 1;
    g_2f4c[13].f_3c = 0x2ee;
    if (g_920c == 3)
        g_2f4c[13].f_3e = 0xa;
    else
        g_2f4c[13].f_3e = 0x10;
    g_2f4c[27].f_0e = 5;
    g_2f4c[27].f_16 = 0x46;
    g_2f4c[27].f_18 = 0x14;
    g_2f4c[27].f_26 = 0x32;
    g_2f4c[27].f_28 = 0x2d;
    g_2f4c[27].f_1a = 2;
    g_2f4c[27].f_2a = 2;
    g_2f4c[27].f_0c = 1;
    g_2f4c[27].f_10 = 1;
    g_2f4c[27].f_12 = 1;
    g_2f4c[27].f_2c = 1;
    g_2f4c[27].f_42 = 1;
    g_2f4c[27].f_14 = 9;
    g_2f4c[27].f_48 = 9;
    g_2f4c[27].f_02 = 3;
    g_2f4c[27].f_08 = -1;
    g_2f4c[27].f_0a = -1;
    g_2f4c[27].f_04 = -1;
    g_2f4c[27].f_1c = 0;
    g_2f4c[27].f_1e = 0;
    g_2f4c[27].f_40 = 0;
    g_2f4c[27].f_44 = 0;
    g_2f4c[27].f_46 = 0;
    g_2f4c[27].f_2e = 0;
    g_2f4c[27].f_00 = 0;
    g_2f4c[27].f_06 = 0;
    g_2f4c[27].f_20 = 0;
    g_2f4c[27].f_22 = 0;
    g_2f4c[27].f_24 = 0;
    g_2f4c[27].f_30 = 0;
    g_2f4c[27].f_4a = 0;
    g_2f4c[27].f_28 = 0;
    g_2f4c[27].f_38 = 0;
    g_2f4c[27].f_32 = 0;
    g_2f4c[27].f_34 = 0;
    g_2f4c[27].f_36 = 0;
    g_2f4c[27].f_4e = 0;
    if (g_920c == 3)
        g_2f4c[27].f_3e = 5;
    else
        g_2f4c[27].f_3e = -1;
    g_2f4c[14].f_0e = 2;
    g_2f4c[14].f_12 = 4;
    g_2f4c[14].f_14 = 7;
    g_2f4c[14].f_18 = 0x14;
    g_2f4c[14].f_26 = 0xd2;
    g_2f4c[14].f_0c = 1;
    g_2f4c[14].f_10 = 1;
    g_2f4c[14].f_1e = 1;
    g_2f4c[14].f_2c = 1;
    g_2f4c[14].f_42 = 1;
    g_2f4c[14].f_46 = 1;
    g_2f4c[14].f_00 = 0x15;
    g_2f4c[14].f_06 = 0x2a8;
    g_2f4c[14].f_08 = 0xc8;
    g_2f4c[14].f_0a = -1;
    g_2f4c[14].f_04 = -1;
    g_2f4c[14].f_20 = 0x1c;
    g_2f4c[14].f_2a = 6;
    g_2f4c[14].f_22 = 6;
    g_2f4c[14].f_1c = 3;
    g_2f4c[14].f_02 = 3;
    g_2f4c[14].f_24 = 3;
    g_2f4c[14].f_30 = 0x1e;
    g_2f4c[14].f_3a = 0x172;
    g_2f4c[14].f_16 = 0x64;
    g_2f4c[14].f_38 = 0x64;
    g_2f4c[14].f_32 = 8;
    g_2f4c[14].f_34 = 9;
    g_2f4c[14].f_1a = 0;
    g_2f4c[14].f_40 = 0;
    g_2f4c[14].f_28 = 0;
    g_2f4c[14].f_44 = 0;
    g_2f4c[14].f_2e = 0;
    g_2f4c[14].f_48 = 0;
    g_2f4c[14].f_4a = 0;
    g_2f4c[14].f_36 = 0;
    g_2f4c[14].f_4e = 0;
    g_2f4c[14].f_3c = 0x384;
    if (g_920c == 3)
        g_2f4c[14].f_3e = 7;
    else
        g_2f4c[14].f_3e = -1;
    g_2f4c[17].f_0e = 4;
    g_2f4c[17].f_12 = 5;
    g_2f4c[17].f_14 = 7;
    g_2f4c[17].f_16 = 0x78;
    g_2f4c[17].f_18 = 0x14;
    g_2f4c[17].f_26 = 0x3c;
    g_2f4c[17].f_00 = 9;
    g_2f4c[17].f_06 = 0x35c;
    g_2f4c[17].f_08 = 0xcb;
    g_2f4c[17].f_0a = -1;
    g_2f4c[17].f_04 = -1;
    g_2f4c[17].f_20 = 0x1c;
    g_2f4c[17].f_22 = 6;
    g_2f4c[17].f_0c = 3;
    g_2f4c[17].f_02 = 3;
    g_2f4c[17].f_24 = 3;
    g_2f4c[17].f_30 = 8;
    g_2f4c[17].f_3a = 0x172;
    g_2f4c[17].f_38 = 0x64;
    g_2f4c[17].f_32 = 2;
    g_2f4c[17].f_1a = 0;
    g_2f4c[17].f_1c = 0;
    g_2f4c[17].f_1e = 0;
    g_2f4c[17].f_40 = 0;
    g_2f4c[17].f_28 = 0;
    g_2f4c[17].f_44 = 0;
    g_2f4c[17].f_48 = 0;
    g_2f4c[17].f_4a = 0;
    g_2f4c[17].f_36 = 0;
    g_2f4c[17].f_10 = 1;
    g_2f4c[17].f_2a = 1;
    g_2f4c[17].f_2c = 1;
    g_2f4c[17].f_42 = 1;
    g_2f4c[17].f_46 = 1;
    g_2f4c[17].f_2e = 1;
    g_2f4c[17].f_34 = 1;
    g_2f4c[17].f_4e = 1;
    g_2f4c[17].f_3c = 0x258;
    if (g_920c == 3)
        g_2f4c[17].f_3e = 0xa;
    else
        g_2f4c[17].f_3e = -1;
    g_2f4c[21].f_14 = 4;
    g_2f4c[21].f_16 = 0x5f;
    g_2f4c[21].f_18 = 0x14;
    g_2f4c[21].f_26 = 0x55;
    g_2f4c[21].f_00 = 0xf;
    g_2f4c[21].f_06 = 0xbc;
    g_2f4c[21].f_08 = 0xcf;
    g_2f4c[21].f_1a = -1;
    g_2f4c[21].f_0a = -1;
    g_2f4c[21].f_04 = -1;
    g_2f4c[21].f_20 = 2;
    g_2f4c[21].f_10 = 3;
    g_2f4c[21].f_2a = 3;
    g_2f4c[21].f_02 = 3;
    g_2f4c[21].f_22 = 3;
    g_2f4c[21].f_24 = 3;
    g_2f4c[21].f_30 = 8;
    g_2f4c[21].f_3a = 0x15e;
    g_2f4c[21].f_38 = 0x5a;
    g_2f4c[21].f_12 = 5;
    g_2f4c[21].f_32 = 5;
    g_2f4c[21].f_1c = 0;
    g_2f4c[21].f_1e = 0;
    g_2f4c[21].f_40 = 0;
    g_2f4c[21].f_28 = 0;
    g_2f4c[21].f_44 = 0;
    g_2f4c[21].f_46 = 0;
    g_2f4c[21].f_2e = 0;
    g_2f4c[21].f_48 = 0;
    g_2f4c[21].f_4a = 0;
    g_2f4c[21].f_36 = 0;
    g_2f4c[21].f_0c = 1;
    g_2f4c[21].f_0e = 1;
    g_2f4c[21].f_2c = 1;
    g_2f4c[21].f_42 = 1;
    g_2f4c[21].f_34 = 1;
    g_2f4c[21].f_4e = 1;
    g_2f4c[21].f_3c = 0x28a;
    if (g_920c == 3)
        g_2f4c[21].f_3e = 7;
    else
        g_2f4c[21].f_3e = -1;
    g_2f4c[16].f_0c = 2;
    g_2f4c[16].f_14 = 7;
    g_2f4c[16].f_16 = 0x32;
    g_2f4c[16].f_18 = 0x14;
    g_2f4c[16].f_26 = 0x15e;
    g_2f4c[16].f_2e = 8;
    g_2f4c[16].f_2a = 6;
    g_2f4c[16].f_48 = 6;
    g_2f4c[16].f_00 = 0x17;
    g_2f4c[16].f_08 = 0xca;
    g_2f4c[16].f_06 = 0x348;
    g_2f4c[16].f_0a = 0x348;
    g_2f4c[16].f_04 = -1;
    g_2f4c[16].f_20 = 0x18;
    g_2f4c[16].f_30 = 0xe;
    g_2f4c[16].f_10 = 1;
    g_2f4c[16].f_12 = 1;
    g_2f4c[16].f_2c = 1;
    g_2f4c[16].f_42 = 1;
    g_2f4c[16].f_4a = 1;
    g_2f4c[16].f_3a = 0x104;
    g_2f4c[16].f_38 = 0x50;
    g_2f4c[16].f_0e = 4;
    g_2f4c[16].f_22 = 4;
    g_2f4c[16].f_24 = 4;
    g_2f4c[16].f_32 = 4;
    g_2f4c[16].f_02 = 5;
    g_2f4c[16].f_34 = 5;
    g_2f4c[16].f_1a = 0;
    g_2f4c[16].f_1c = 0;
    g_2f4c[16].f_1e = 0;
    g_2f4c[16].f_40 = 0;
    g_2f4c[16].f_28 = 0;
    g_2f4c[16].f_44 = 0;
    g_2f4c[16].f_46 = 0;
    g_2f4c[16].f_36 = 0;
    g_2f4c[16].f_4e = 0;
    g_2f4c[16].f_3c = 0x1f4;
    if (g_920c == 3)
        g_2f4c[16].f_3e = 0xa;
    else
        g_2f4c[16].f_3e = -1;
    g_2f4c[22].f_14 = 5;
    g_2f4c[22].f_16 = 0x50;
    g_2f4c[22].f_26 = 0xc8;
    g_2f4c[22].f_18 = 0x14;
    g_2f4c[22].f_2a = 0x14;
    g_2f4c[22].f_0c = 1;
    g_2f4c[22].f_10 = 1;
    g_2f4c[22].f_2c = 1;
    g_2f4c[22].f_42 = 1;
    g_2f4c[22].f_44 = 1;
    g_2f4c[22].f_46 = 1;
    g_2f4c[22].f_08 = 0xd0;
    g_2f4c[22].f_0a = 0xc7;
    g_2f4c[22].f_06 = -1;
    g_2f4c[22].f_04 = -1;
    g_2f4c[22].f_20 = 0x1c;
    g_2f4c[22].f_12 = 3;
    g_2f4c[22].f_22 = 3;
    g_2f4c[22].f_0e = 2;
    g_2f4c[22].f_00 = 2;
    g_2f4c[22].f_24 = 2;
    g_2f4c[22].f_30 = 0x1e;
    g_2f4c[22].f_3a = 0x168;
    g_2f4c[22].f_38 = 0x6e;
    g_2f4c[22].f_32 = 7;
    g_2f4c[22].f_34 = 8;
    g_2f4c[22].f_36 = 0x96;
    g_2f4c[22].f_1a = 0;
    g_2f4c[22].f_1c = 0;
    g_2f4c[22].f_1e = 0;
    g_2f4c[22].f_40 = 0;
    g_2f4c[22].f_28 = 0;
    g_2f4c[22].f_2e = 0;
    g_2f4c[22].f_48 = 0;
    g_2f4c[22].f_02 = 0;
    g_2f4c[22].f_4a = 0;
    g_2f4c[22].f_4e = 0;
    g_2f4c[22].f_3c = 0;
    if (g_920c == 3)
        g_2f4c[22].f_3e = 7;
    else
        g_2f4c[22].f_3e = -1;
    g_2f4c[24].f_0e = 2;
    g_2f4c[24].f_0a = 0xbd;
    g_2f4c[24].f_08 = 0xd2;
    g_2f4c[24].f_30 = 3;
    g_2f4c[24].f_28 = 0x28;
    g_2f4c[24].f_38 = 0x14;
    g_2f4c[24].f_0c = 1;
    g_2f4c[24].f_4e = 1;
    g_2f4c[24].f_12 = 0;
    g_2f4c[24].f_4a = 0;
    g_2f4c[24].f_32 = 0;
    g_2f4c[24].f_34 = 0;
    g_2f4c[24].f_36 = 0;
    g_2f4c[24].f_3c = 0;
    if (g_920c == 3)
        g_2f4c[24].f_3e = 5;
    else
        g_2f4c[24].f_3e = -1;
    g_2f4c[25].f_0e = 2;
    g_2f4c[25].f_0c = 1;
    g_2f4c[25].f_0a = 0xc0;
    g_2f4c[25].f_08 = 0xd3;
    g_2f4c[25].f_30 = 3;
    g_2f4c[25].f_28 = 0x28;
    g_2f4c[25].f_38 = 0x14;
    g_2f4c[25].f_12 = 0;
    g_2f4c[25].f_4a = 0;
    g_2f4c[25].f_32 = 0;
    g_2f4c[25].f_34 = 0;
    g_2f4c[25].f_36 = 0;
    g_2f4c[25].f_4e = 0;
    g_2f4c[25].f_3c = 0;
    if (g_920c == 3)
        g_2f4c[25].f_3e = 7;
    else
        g_2f4c[25].f_3e = -1;
    g_2f4c[26].f_0e = 2;
    g_2f4c[26].f_0a = 0xc1;
    g_2f4c[26].f_08 = 0xd4;
    g_2f4c[26].f_30 = 3;
    g_2f4c[26].f_28 = 0x28;
    g_2f4c[26].f_38 = 0x14;
    g_2f4c[26].f_0c = 1;
    g_2f4c[26].f_4e = 1;
    g_2f4c[26].f_12 = 0;
    g_2f4c[26].f_4a = 0;
    g_2f4c[26].f_32 = 0;
    g_2f4c[26].f_34 = 0;
    g_2f4c[26].f_36 = 0;
    g_2f4c[26].f_3c = 0;
    if (g_920c == 3)
        g_2f4c[26].f_3e = 5;
    else
        g_2f4c[26].f_3e = -1;
}

/* Fills in the table of 12 0x14-byte records at DS:4da4 (string ids
 * 0x87a-0x885) [inferred: weapon or device stats]. */
/* 10:2ffa */
void fn_10_2ffa(void)
{
    char buf[40];

    g_4d90[1].f_12 = 0x87a;
    g_4d90[2].f_12 = 0x87b;
    g_4d90[3].f_12 = 0x87c;
    g_4d90[4].f_12 = 0x87d;
    g_4d90[5].f_0e = 0x26c;
    g_4d90[5].f_0a = 0x384;
    g_4d90[5].f_0c = 0xc8;
    g_4d90[5].f_12 = 0x87e;
    g_4d90[6].f_0a = 0x258;
    g_4d90[1].f_07 = 8;
    g_4d90[2].f_07 = 8;
    g_4d90[6].f_07 = 8;
    g_4d90[6].f_12 = 0x87f;
    g_4d90[7].f_03 = 0xb;
    g_4d90[5].f_10 = 0x262;
    g_4d90[6].f_10 = 0x262;
    g_4d90[7].f_10 = 0x262;
    g_4d90[7].f_0a = 0x3e8;
    g_4d90[7].f_12 = 0x880;
    g_4d90[1].f_03 = 5;
    g_4d90[7].f_05 = 5;
    g_4d90[7].f_07 = 5;
    g_4d90[8].f_03 = 5;
    g_4d90[8].f_10 = 0x276;
    g_4d90[8].f_0a = 0xfa;
    g_4d90[8].f_07 = 7;
    g_4d90[8].f_12 = 0x881;
    g_4d90[10].f_10 = 0x2bc;
    g_4d90[10].f_0a = 0x190;
    g_4d90[7].f_0c = 0x64;
    g_4d90[8].f_0c = 0x64;
    g_4d90[10].f_0c = 0x64;
    g_4d90[2].f_03 = 4;
    g_4d90[2].f_05 = 4;
    g_4d90[5].f_05 = 4;
    g_4d90[10].f_03 = 4;
    g_4d90[10].f_07 = 4;
    g_4d90[10].f_12 = 0x882;
    g_4d90[9].f_03 = -1;
    g_4d90[9].f_0e = 0x352;
    g_4d90[9].f_10 = -1;
    g_4d90[1].f_05 = 3;
    g_4d90[5].f_01 = 3;
    g_4d90[6].f_01 = 3;
    g_4d90[10].f_05 = 3;
    g_4d90[9].f_01 = 3;
    g_4d90[1].f_00 = 1;
    g_4d90[1].f_06 = 1;
    g_4d90[2].f_00 = 1;
    g_4d90[2].f_06 = 1;
    g_4d90[3].f_00 = 1;
    g_4d90[3].f_07 = 1;
    g_4d90[4].f_00 = 1;
    g_4d90[4].f_07 = 1;
    g_4d90[5].f_03 = 1;
    g_4d90[5].f_02 = 1;
    g_4d90[5].f_04 = 1;
    g_4d90[7].f_02 = 1;
    g_4d90[10].f_01 = 1;
    g_4d90[9].f_02 = 1;
    g_4d90[3].f_03 = 0;
    g_4d90[3].f_05 = 0;
    g_4d90[3].f_06 = 0;
    g_4d90[4].f_03 = 0;
    g_4d90[4].f_05 = 0;
    g_4d90[4].f_06 = 0;
    g_4d90[6].f_02 = 0;
    g_4d90[6].f_04 = 0;
    g_4d90[7].f_04 = 0;
    g_4d90[8].f_02 = 0;
    g_4d90[8].f_04 = 0;
    g_4d90[10].f_02 = 0;
    g_4d90[10].f_04 = 0;
    g_4d90[9].f_04 = 0;
    g_4d90[9].f_0a = 0x1f40;
    g_4d90[6].f_0c = 0x3c;
    g_4d90[9].f_0c = 0x3c;
    g_4d90[5].f_07 = 6;
    g_4d90[6].f_05 = 6;
    g_4d90[9].f_05 = 6;
    g_4d90[6].f_03 = 0xa;
    g_4d90[9].f_07 = 0xa;
    g_4d90[9].f_12 = 0x883;
    g_4d90[5].f_00 = 2;
    g_4d90[6].f_00 = 2;
    g_4d90[7].f_00 = 2;
    g_4d90[7].f_01 = 2;
    g_4d90[8].f_00 = 2;
    g_4d90[8].f_01 = 2;
    g_4d90[8].f_05 = 2;
    g_4d90[10].f_00 = 2;
    g_4d90[9].f_00 = 2;
    g_4d90[11].f_00 = 2;
    g_4d90[11].f_03 = 0x10;
    g_4d90[6].f_0e = 0x280;
    g_4d90[7].f_0e = 0x280;
    g_4d90[8].f_0e = 0x280;
    g_4d90[10].f_0e = 0x280;
    g_4d90[11].f_0e = 0x280;
    g_4d90[11].f_10 = 0x262;
    g_4d90[11].f_0a = 0x96;
    g_4d90[11].f_0c = 0x64;
    g_4d90[11].f_01 = 4;
    g_4d90[11].f_05 = 4;
    g_4d90[11].f_07 = 8;
    g_4d90[11].f_12 = 0x884;
    g_4d90[12].f_03 = 0xe;
    g_4d90[12].f_0e = 0x280;
    g_4d90[12].f_10 = 0x2bc;
    g_4d90[12].f_00 = 2;
    g_4d90[12].f_01 = 2;
    g_4d90[12].f_02 = 1;
    g_4d90[11].f_02 = 0;
    g_4d90[11].f_04 = 0;
    g_4d90[12].f_04 = 0;
    g_4d90[12].f_0a = 0x514;
    g_4d90[12].f_0c = 0x32;
    g_4d90[12].f_05 = 7;
    g_4d90[12].f_07 = 6;
    g_4d90[12].f_12 = 0x885;
}

/* Game start-up for mode g_90f4 (1: loads the pilot name, "Otto-Pilot"
 * in a demo [inferred], waits 2 s, makes the two 8x8 pattern brushes).
 * The pattern inversion loop is never reached: its condition (an
 * unsigned GetVersion() < 0) is always false; the exact original form is
 * [inferred], a while/break gives the game's layout. */
/* 10:0000 */
int16_t fn_10_0000(void)
{
    DWORD t;
    int16_t u[5];
    int16_t i;

    subgame_active = 0;
    if (g_90f4 == 0) {
        fn_15_5786();
        return 1;
    }
    if (g_90f4 == 1) {
        g_1016 = g_001a = 0;
        fn_10_6e76(8L);
        fn_10_6e4c();
        fn_10_0522(0);
        fn_10_5c42();
        fn_10_1fb2();
        fn_10_73e2();
        if (g_9134 && !flow_interactive)
            lstrcpy(g_380c, "Otto-Pilot");
        else
            GetPrivateProfileString(g_9690, "ThePlayer", "", g_380c, 12, g_96a9);
        t = GetCurrentTime() + 2000;
        fn_15_6640();
        g_92e6 = 0;
        fn_09_22b4(0);
        fn_10_2ffa();
        do
            ;
        while (GetCurrentTime() < t);
        g_91fa = 0;
        fn_10_4b2e();
        while (GetVersion() < 0) {      /* never true: DWORD < 0 */
            for (i = 0; i < 8; i++)
                g_06c6[i] ^= 0xff;
            break;
        }
        g_3820[0] = CreateBitmap(8, 8, 1, 1, g_06c6);
        g_5ea8[0] = CreatePatternBrush(g_3820[0]);
        g_3820[1] = CreateBitmap(8, 8, 1, 1, g_06b6);
        g_5ea8[1] = CreatePatternBrush(g_3820[1]);
        fn_11_0000();
    }
    return 1;
}

/* Puts object n of list 0 at a random place in the world, at least 150
 * from the left/top edge [inferred], retrying while it lands inside the
 * view centred on the world. */
/* near-match 99%: 10:0736 (one register choice differs: CL adds the
 * record offset from si at the f02 store, the game from ax (the same
 * value); about 30 forms of the f00/f02 stores tried) */
void fn_10_0736(int16_t n)
{
    int16_t again;
    RECT rc;

    again = 1;
    do {
        g_1df8[0][n].f_54 = 0;
        g_1df8[0][n].f_04.x = (rand() % ((LO16(g_05a0)) - 150) + 150) << 3;
        g_1df8[0][n].f_04.y = (rand() % ((HI16(g_05a0)) - 150) + 150) << 3;
        g_1df8[0][n].f_00.x = g_1df8[0][n].f_08.x = -1000;
        g_1df8[0][n].f_00.y = g_1df8[0][n].f_08.y = -1000;
        g_1df8[0][n].f_2f = 0;
        again = 0;
        SetRect(&rc, ((LO16(g_05a0)) / 2 - LO16(g_90ea) / 2) << g_9150,
                ((HI16(g_05a0)) / 2 - HI16(g_90ea) / 2) << g_9150,
                (LO16(g_90ea) / 2 + (LO16(g_05a0)) / 2) << g_9150,
                ((HI16(g_05a0)) / 2 + HI16(g_90ea) / 2) << g_9150);
        if (PtInRect(&rc, g_1df8[0][n].f_04))
            again = 1;
    } while (again);
}

/* Like fn_10_0736 for object n of g_1e1c, also with a random speed
 * (-24..25 each way [inferred]) and a random f26 below 900. */
/* near-match 99%: 10:0a26 (the same f02 register choice as 10:0736) */
void fn_10_0a26(int16_t n)
{
    int16_t again;
    RECT rc;

    again = 1;
    do {
        g_1df8[9][n].f_04.x = (rand() % ((LO16(g_05a0)) - 150) + 150) << 3;
        g_1df8[9][n].f_04.y = (rand() % ((HI16(g_05a0)) - 150) + 150) << 3;
        g_1df8[9][n].f_00.x = g_1df8[9][n].f_08.x = -1000;
        g_1df8[9][n].f_00.y = g_1df8[9][n].f_08.y = -1000;
        g_1df8[9][n].f_0c = 25 - rand() % 50;
        g_1df8[9][n].f_0e = 25 - rand() % 50;
        g_1df8[9][n].f_18 = 0;
        g_1df8[9][n].f_2e = 0;
        g_1df8[9][n].f_26 = rand() % 900;
        SetRect(&rc, ((LO16(g_05a0)) / 2 - LO16(g_90ea) / 2) << g_9150,
                ((HI16(g_05a0)) / 2 - HI16(g_90ea) / 2) << g_9150,
                ((LO16(g_05a0)) / 2 + LO16(g_90ea) / 2) << g_9150,
                ((HI16(g_05a0)) / 2 + HI16(g_90ea) / 2) << g_9150);
        again = 0;
        if (PtInRect(&rc, g_1df8[9][n].f_04))
            again = 1;
    } while (again);
}

/* Like fn_10_0a26 for object n of g_1e04; a speed too slow on both axes
 * gets 20 added to x. */
/* near-match 99%: 10:0864 (the same f02 register choice as 10:0736) */
void fn_10_0864(int16_t n)
{
    int16_t again;
    RECT rc;

    again = 1;
    do {
        g_1df8[3][n].f_50 = 0;
        g_1df8[3][n].f_04.x = (rand() % ((LO16(g_05a0)) - 150) + 150) << 3;
        g_1df8[3][n].f_04.y = (rand() % ((HI16(g_05a0)) - 150) + 150) << 3;
        g_1df8[3][n].f_00.x = g_1df8[3][n].f_08.x = -1000;
        g_1df8[3][n].f_00.y = g_1df8[3][n].f_08.y = -1000;
        g_1df8[3][n].f_0c = 25 - rand() % 50;
        g_1df8[3][n].f_0e = 25 - rand() % 50;
        if (fn_09_88ba(g_1df8[3][n].f_0c) < 10 && fn_09_88ba(g_1df8[3][n].f_0e) < 10)
            g_1df8[3][n].f_0c += 20;
        g_1df8[3][n].f_18 = 0;
        g_1df8[3][n].f_2f = 0;
        g_1df8[3][n].f_2e = 0;
        VIEW(void *, g_1df8[3][n].f_6a, 0) = 0;
        g_1df8[3][n].f_26 = rand() % 1700;
        SetRect(&rc, ((LO16(g_05a0)) / 2 - LO16(g_90ea) / 2) << g_9150,
                ((HI16(g_05a0)) / 2 - HI16(g_90ea) / 2) << g_9150,
                ((LO16(g_05a0)) / 2 + LO16(g_90ea) / 2) << g_9150,
                ((HI16(g_05a0)) / 2 + HI16(g_90ea) / 2) << g_9150);
        again = 0;
        if (PtInRect(&rc, g_1df8[3][n].f_04))
            again = 1;
    } while (again);
}

/* Frees the GDI objects, the memory DC g_95c2 and the global memory
 * blocks of a mission [inferred]. */
/* 10:0330 */
void fn_10_0330(void)
{
    int16_t i;

    fn_11_01e0();
    for (i = 1; i < 6; i++) {
        if (g_3b88[i]) {
            DeleteObject(g_3b88[i]);
            g_3b88[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_3b44[i]) {
            DeleteObject(g_3b44[i]);
            g_3b44[i] = 0;
        }
    }
    for (i = 0; i <= 19; i++) {
        if (g_576c[i]) {
            DeleteObject(g_576c[i]);
            g_576c[i] = 0;
        }
    }
    for (i = 0; i < 10; i++) {
        if (g_3b74[i]) {
            DeleteObject(g_3b74[i]);
            g_3b74[i] = 0;
        }
    }
    for (i = 0; i < 20; i++) {
        if (g_3b4c[i]) {
            DeleteObject(g_3b4c[i]);
            g_3b4c[i] = 0;
        }
    }
    if (g_95c2) {
        if (g_95c4)
            SelectPalette(g_95c2, g_95c4, 0);
        SelectObject(g_95c2, g_95c0);
        DeleteObject(g_95be);
        DeleteDC(g_95c2);
        g_95be = g_95c2 = 0;
    }
    for (i = 0; i <= 14; i++) {
        if (g_9100[i]) {
            if (g_1df8[i]) {
                GlobalUnlock(g_9100[i]);
                g_1df8[i] = 0;
            }
            GlobalFree(g_9100[i]);
            g_9100[i] = 0;
        }
    }
    fn_10_061a();
    if (g_92e0) {
        GlobalUnlock(g_92e0);
        g_3d4c = 0;
        GlobalFree(g_92e0);
        g_92e0 = 0;
    }
    if (g_912a) {
        GlobalUnlock(g_912a);
        g_1e4c = 0;
        GlobalFree(g_912a);
        g_912a = 0;
    }
    if (g_912c) {
        DeleteObject(g_912c);
        g_912c = 0;
    }
}

/* Fills the five points g_96d2[i].f50 [inferred: an arc of markers] from
 * the tables g_06d6 / g_06e0, scaled for the view size g_9156. */
/* 10:16ba */
void fn_10_16ba(int16_t i)
{
    int16_t w;
    int16_t j;
    int16_t u1;
    int16_t u2;
    int16_t r;
    int16_t r0;
    int16_t b;
    int16_t a;

    if (subgame_active)
        w = g_96d2[i].f_2a * (g_9156 * 2 + 1) / 3;
    else
        w = (g_96d2[i].f_2a << g_9156) >> 1;
    r0 = (g_96d2[i].f_04 + 1) * 2;
    for (j = 0; j < 5; j++) {
        r = r0;
        if (j == 0 || j == 4 || j == 3)
            r--;
        switch (j) {
        case 0:
            r--;
        case 2:
            b = a = 9;
            break;
        case 1:
            a = 7;
            b = 9;
            break;
        case 3:
            b = a = 9;
            if (g_96d2[i].f_2a > 29)
                b = 10;
            break;
        case 4:
            a = 8;
            if (g_9156 < 2)
                a = 6;
            b = 9;
            break;
        }
        if (subgame_active) {
            /* u1, u2 are never read: the assignments only fix CL's
             * evaluation order (no stores are emitted) */
            g_96d2[i].f_50[j].x = g_06d6[j] * r / 256 * (g_9156 * 2 + 1) / 6 +
                                 (u1 = -1 - g_9156 * 2) * a / 6 + w / 2;
            g_96d2[i].f_50[j].y = (-1 - g_9156 * 2) * b / 6 -
                                 (u2 = g_06e0[j] * r / 256 * (g_9156 * 2 + 1) / 6) + w / 2;
        } else {
            g_96d2[i].f_50[j].x = (g_06d6[j] * r / 256 >> (2 - g_9156)) -
                                 (a >> (2 - g_9156)) + w / 2;
            g_96d2[i].f_50[j].y = w / 2 - (g_06e0[j] * r / 256 >> (2 - g_9156)) -
                                 (b >> (2 - g_9156));
        }
    }
}

/* Fills the three race tracks' tables (LAZYLOOP, SDISPEED, GRANDPRI):
 * the same kind of constant table initialiser as fn_10_2ffa. */
/* 10:320a */
void fn_10_320a(void)
{
    lstrcpy(g_a12c[0], "LAZYLOOP");
    g_9eb9[0] = 0x16;
    g_9eb6[0] = 8;
    g_9ec2[0][0] = 8;
    g_9ec2[0][1] = 0xd;
    g_9f3a[0][1] = 0xa;
    g_9ec2[0][3] = 0xa;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][4].y = 0x4074;
    g_9ec2[0][4] = 0x12;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][6].y = 0x2328;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][7].x = 0x2328;
    g_9ec2[0][7] = 0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][1].y = 0x2af8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][4].x = 0x2af8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][8].y = 0x2af8;
    g_9ec2[0][8] = 9;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][8].x = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][9].x = 0x3e80;
    g_9ec2[0][10] = 5;
    g_9ec2[0][11] = 0xc;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][3].x = 0x36b0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][13].y = 0x36b0;
    g_9ec2[0][13] = 0xe;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][14].y = 0x4268;
    g_9ec2[0][14] = 0xf;
    g_9ec2[0][15] = 0x10;
    g_9ec2[0][16] = 0x11;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][11].x = 0x55f0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][12].x = 0x55f0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][14].x = 0x55f0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][15].x = 0x55f0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][16].y = 0x55f0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][17].y = 0x55f0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][18].x = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][18].y = 0x4650;
    g_9ec2[0][18] = 0x13;
    g_9ec2[0][19] = 0x14;
    g_9ec2[0][20] = 0x15;
    g_9f3a[0][0] = 0xb;
    g_9ec2[0][21] = 0xb;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][13].x = 0x5208;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][22].x = 0x5208;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][12].y = 0x1f40;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][22].y = 0x1f40;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][23].x = 0x38a4;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][0].x = 0x4c2c;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][2].x = 0x4c2c;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][23].y = 0x4c2c;
    g_9ec2[0][9] = 2;
    g_9ec2[0][23] = 2;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][1].x = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][2].y = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][3].y = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][15].y = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][16].x = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][24].x = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][24].y = 0x53fc;
    g_9ebf[0] = 3;
    g_9ec2[0][2] = 3;
    g_9ec2[0][24] = 3;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][25].x = 0x157c;
    g_9ec2[0][5] = 6;
    g_9ec2[0][25] = 6;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][26].x = 0x4844;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][26].y = 0x2710;
    g_9ec2[0][12] = 1;
    g_9ec2[0][22] = 1;
    g_9ec2[0][26] = 1;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][17].x = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][25].y = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][27].x = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][5].y = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][9].y = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][19].y = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][27].y = 0x3a98;
    g_9ebc[0] = 4;
    g_9ec2[0][17] = 4;
    g_9ec2[0][27] = 4;
    g_9ec2[0][6] = 7;
    g_9ec2[0][28] = 7;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][10].x = 0x32c8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][10].y = 0x32c8;
    g_a120[0].x = 0x32c8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][20].y = 0x1b58;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][21].x = 0x1b58;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][28].x = 0x1b58;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][28].y = 0x1b58;
    g_a120[0].y = 0x1b58;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][11].y = 0xbb8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][19].x = 0xbb8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][20].x = 0xbb8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][21].y = 0xbb8;
    g_9ea8[0].x = 0xbb8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][0].y = 0x1770;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][5].x = 0x1770;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][6].x = 0x1770;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[0][7].y = 0x1770;
    g_9ea8[0].y = 0x1770;
    lstrcpy(g_a12c[1], "SDISPEED");
    g_9eb9[1] = 0x19;
    g_9eb6[1] = 0xa;
    g_9ec2[1][0] = 0xa;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][2].x = 0x53fc;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][3].y = 0x55f0;
    g_9ec2[1][6] = 7;
    g_9ec2[1][7] = 0xe;
    g_9ec2[1][8] = 0x17;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][7].x = 0xdac;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][9].x = 0xdac;
    g_9ec2[1][9] = 0;
    g_9ec2[1][3] = 0xb;
    g_9ec2[1][10] = 0xb;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][2].y = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][11].y = 0x4a38;
    g_9ec2[1][2] = 2;
    g_9ec2[1][11] = 2;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][3].x = 0x4650;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][10].x = 0x4650;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][11].x = 0x4650;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][12].x = 0x4650;
    g_9ec2[1][12] = 0xd;
    g_9ec2[1][13] = 6;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][14].x = 0x1d4c;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][5].x = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][8].y = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][10].y = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][12].y = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][13].y = 0x2ee0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][14].y = 0x2ee0;
    g_9ec2[1][14] = 9;
    g_9ec2[1][1] = 0x10;
    g_9ec2[1][15] = 0x10;
    g_9ec2[1][16] = 0x11;
    g_9ec2[1][17] = 0x12;
    g_9ec2[1][18] = 0x15;
    g_9ec2[1][5] = 0x14;
    g_9ec2[1][19] = 0x14;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][0].x = 0x5208;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][6].y = 0x5208;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][7].y = 0x5208;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][17].y = 0x5208;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][18].x = 0x5208;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][20].y = 0x5208;
    g_9ebc[1] = 4;
    g_9ec2[1][20] = 4;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][15].x = 0x5dc0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][16].x = 0x5dc0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][17].x = 0x5dc0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][18].y = 0x5dc0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][19].y = 0x5dc0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][21].y = 0x5dc0;
    g_9ec2[1][21] = 0x16;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][1].y = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][16].y = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][22].y = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][13].x = 0x1f40;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][23].y = 0x1f40;
    g_9ec2[1][23] = 0x18;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][15].y = 0x3e8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][21].x = 0x3e8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][22].x = 0x3e8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][23].x = 0x3e8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][24].x = 0x3e8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][24].y = 0x3e8;
    g_9ec2[1][24] = 0xf;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][25].x = 0x4844;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][25].y = 0x30d4;
    g_9ec2[1][25] = 1;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][26].x = 0x34bc;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][26].y = 0x396c;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][27].x = 0xbb8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][4].x = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][4].y = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][5].y = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][19].x = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][20].x = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][27].y = 0x3a98;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][0].y = 0xfa0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][8].x = 0xfa0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][9].y = 0xfa0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][28].x = 0xfa0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][28].y = 0x3520;
    g_9f3a[1][1] = 8;
    g_9ec2[1][22] = 8;
    g_9ec2[1][27] = 8;
    g_9ec2[1][28] = 8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][29].x = 0x3afc;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][29].y = 0x3840;
    g_9f3a[1][0] = 5;
    g_9ec2[1][4] = 5;
    g_9ec2[1][26] = 5;
    g_9ec2[1][29] = 5;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][30].x = 0x5460;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][1].x = 0x5014;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][30].y = 0x5014;
    g_9ebf[1] = 3;
    g_9ec2[1][30] = 3;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][31].x = 0x125c;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][6].x = 0x2af8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[1][31].y = 0x2af8;
    g_9ec2[1][31] = 9;
    g_a120[1].x = 0x2ee0;
    g_a120[1].y = 0x1388;
    g_9ea8[1].x = 0x3e8;
    g_9ea8[1].y = 0xfa0;
    lstrcpy(g_a12c[2], "GRANDPRI");
    g_9eb9[2] = 0x1f;
    g_9ebc[2] = 5;
    g_9f3a[2][1] = 0xc;
    g_9ec2[2][0] = 1;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][1].y = 0x251c;
    g_9ec2[2][2] = 3;
    g_9ebf[2] = 4;
    g_9ec2[2][3] = 4;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][5].y = 0x1770;
    g_9ec2[2][6] = 7;
    g_9f3a[2][0] = 0xa;
    g_9ec2[2][9] = 0xa;
    g_9ec2[2][12] = 0x1e;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][2].x = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][3].x = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][3].y = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][4].y = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][6].y = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][13].x = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][14].x = 0x1c52;
    g_9ec2[2][14] = 0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][0].y = 0x2af8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][14].y = 0x2af8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][15].y = 0x2af8;
    g_9eb6[2] = 0xe;
    g_9ec2[2][1] = 0xe;
    g_9ec2[2][15] = 0xe;
    g_9ec2[2][16] = 0x12;
    g_9ec2[2][5] = 0x11;
    g_9ec2[2][17] = 0x11;
    g_9ec2[2][18] = 0x14;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][0].x = 0x4268;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][5].x = 0x4268;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][8].y = 0x4268;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][17].x = 0x4268;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][19].y = 0x4268;
    g_9ec2[2][8] = 0x13;
    g_9ec2[2][19] = 0x13;
    g_9ec2[2][20] = 0x16;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][1].x = 0x2710;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][11].x = 0x2710;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][21].x = 0x2710;
    g_9ec2[2][11] = 0x15;
    g_9ec2[2][21] = 0x15;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][22].x = 0xfa0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][18].x = 0x59d8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][19].x = 0x59d8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][20].x = 0x59d8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][20].y = 0x59d8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][21].y = 0x59d8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][22].y = 0x59d8;
    g_9ec2[2][22] = 0x17;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][15].x = 0x7d0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][16].x = 0x7d0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][16].y = 0x7d0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][17].y = 0x7d0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][18].y = 0x7d0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][23].x = 0x7d0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][11].y = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][23].y = 0x4a38;
    g_9ec2[2][23] = 0x10;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][6].x = 0x4e20;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][7].x = 0x4e20;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][9].x = 0x4e20;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][9].y = 0x4e20;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][10].y = 0x4e20;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][12].y = 0x4e20;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][24].x = 0x4e20;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][2].y = 0x2328;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][24].y = 0x2328;
    g_9ec2[2][4] = 0x19;
    g_9ec2[2][24] = 0x19;
    g_9ec2[2][25] = 0x1a;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][25].y = 0x1f40;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][26].x = 0x1f40;
    g_9ec2[2][26] = 2;
    g_9ec2[2][27] = 0x1d;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][10].x = 0x32c8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][27].x = 0x32c8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][28].x = 0x32c8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][4].x = 0x36b0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][7].y = 0x36b0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][13].y = 0x36b0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][25].x = 0x36b0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][28].y = 0x36b0;
    g_9ec2[2][7] = 0x1c;
    g_9ec2[2][10] = 0x1c;
    g_9ec2[2][13] = 0x1c;
    g_9ec2[2][28] = 0x1c;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][12].x = 0x1b58;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][26].y = 0x1b58;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][29].x = 0x1b58;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][8].x = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][27].y = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][29].y = 0x3e80;
    g_9ec2[2][29] = 0xc;
    g_9ec2[2][31] = 1;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][32].x = 0xfa0;
    g_9ec2[2][32] = 3;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][33].y = 0x38a4;
    g_9ec2[2][33] = 8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][33].x = 0x4268;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][34].x = 0x4268;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][34].y = 0x4c2c;
    g_9ec2[2][34] = 9;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][35].x = 0x1194;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][35].y = 0x4a38;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][30].x = 0x1388;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][36].y = 0x1388;
    g_9ec2[2][36] = 5;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][37].x = 0x55f0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][30].y = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][36].x = 0x3e80;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][37].y = 0x3e80;
    g_9ec2[2][37] = 7;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][38].y = 0x445c;
    g_9ec2[2][38] = 0xb;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][32].y = 0xbb8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][39].x = 0xbb8;
    g_9ec2[2][30] = 0xd;
    g_9ec2[2][35] = 0xd;
    g_9ec2[2][39] = 0xd;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][31].y = 0x2710;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][38].x = 0x2710;
    g_a120[2].x = 0x2710;
    g_a120[2].y = 0x3a98;
    g_9ea8[2].x = 0x2af8;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][31].x = 0x36b0;
    VIEWP(POINT (*)[0x28], g_9f40, 0)[2][39].y = 0x36b0;
    g_9ea8[2].y = 0x36b0;
}

/* Finds or builds the sprite surface (23..27) for the key (k1, k2, type)
 * kept in g_38a4: returns its index (1 when none is free). Draws 16 cells
 * of bitmap k1 as background and bitmap k2 rotated round a circle (or,
 * with flag, 16 straight frames) on top, then stores the cell size and
 * border in g_4d90[rec] [inferred]. pal0 is read uninitialised when
 * g_920e is 0 (as in the original). */
/* 10:18b0 */
int16_t fn_10_18b0(int16_t k1, int16_t k2, int16_t type, int16_t flag, int16_t rec)
{
    int16_t sz0;
    int16_t sz;
    int16_t m;
    int16_t half;
    int16_t cell;
    int16_t i;
    int16_t free;
    int16_t k;
    int16_t u14;
    char col;
    HDC dc0;
    HDC dc1;
    HBITMAP bm0;
    HBITMAP old0;
    HBITMAP bm1;
    HBITMAP old1;
    HBITMAP bm2;
    HPALETTE pal0;
    int16_t r;
    int16_t ang;
    POINT d;
    BITMAP bmp;
    int16_t mode;

    free = 0;
    for (i = 23; i < 28; i++) {
        if (!g_39e8[i])
            free = i;
        if (g_38a4[i - 23].b == k1 && g_38a4[i - 23].a == k2 && g_38a4[i - 23].c == type)
            return i;
    }
    if (free == 0)
        return 1;
    if (free >= 28)
        return 1;
    k = free - 23;
    g_38a4[k].b = k1;
    g_38a4[k].a = k2;
    g_38a4[k].c = type;
    if (k1 != -1) {
        bm0 = fn_10_6c02(k1, 3, -1);
        GetObject(bm0, 14, &bmp);
        dc0 = CreateCompatibleDC(g_13dc);
        old0 = SelectObject(dc0, bm0);
        sz0 = fn_10_86ca();
    } else {
        sz0 = 0;
        dc0 = 0;
    }
    cell = g_1df8[8]->f_24;
    if (g_90f4 == 1 && ((HI16(g_1e68)) || (LO16(g_1e68)))) {
        if (g_931e == 1 || g_931e == 2)
            mode = 1;
        else
            mode = 0;
    } else if (g_931e == 2)
        mode = 1;
    else
        mode = 0;
    if (type == 1)
        col = 9;
    else if (type == 4)
        col = 15;
    else
        col = 12;
    fn_10_6ee6(28, k2, "", 1, 100, type, type, 1, -1, col, col, 0, mode);
    SelectObject(g_39e8[28], g_3974[28]);
    bm1 = fn_10_6ec6(g_3ad0[28]);
    SelectObject(g_39e8[28], g_3ad0[28]);
    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, bm1);
    bm2 = fn_10_6c02(k2, 0, -1);
    GetObject(bm2, 14, &bmp);
    sz = fn_10_86ca();
    DeleteObject(bm2);
    if (sz * 2 > sz0 && !flag)
        m = sz * 2 - 1;
    else if (sz > sz0 && flag)
        m = sz;
    else
        m = sz0;
    for (i = 23; i < 28; i++)
        if (!g_39e8[i])
            free = i;
    u14 = m;
    if (m & 1)
        cell = 5;
    else
        cell = 6;
    g_39e8[free] = CreateCompatibleDC(g_13dc);
    g_3ad0[free] = CreateCompatibleBitmap(g_13dc, m * 16 + cell * 17, cell * 2 + m);
    g_3974[free] = SelectObject(g_39e8[free], g_3ad0[free]);
    if (g_920e) {
        if (dc0)
            pal0 = SelectPalette(dc0, g_920e, 0);
        g_3a5c[free] = SelectPalette(g_39e8[free], g_920e, 0);
    }
    PatBlt(g_39e8[free], 0, 0, m * 16 + cell * 17, cell * 2 + m, BLACKNESS);
    if (k1 != -1) {
        for (i = 0; i < 16; i++)
            BitBlt(g_39e8[free], (m - sz0) / 2 + (cell + m) * i + cell, (m - sz0) / 2 + cell,
                   sz0, sz0, dc0, 0, 0, SRCCOPY);
        SelectObject(dc0, old0);
        if (pal0)
            SelectPalette(dc0, pal0, 0);
        DeleteDC(dc0);
        if (bm0) {
            DeleteObject(bm0);
            bm0 = 0;
        }
    }
    r = half = sz / 2;
    if (!flag) {
        for (i = 0, ang = 270; i < 16; i++, ang -= i % 2 + 22) {
            d.x = fn_06_720c(ang) * r / 128 + half;
            d.y = half - fn_06_71b2(ang) * r / 128;
            BitBlt(g_39e8[free], (cell + m) * i + m / 2 - d.x + cell, m / 2 - d.y + cell,
                   sz, sz, dc1, i * sz, 0, SRCAND);
            BitBlt(g_39e8[free], (cell + m) * i + m / 2 - d.x + cell, m / 2 - d.y + cell,
                   sz, sz, g_39e8[28], i * sz, 0, SRCPAINT);
        }
    } else {
        for (i = 0; i < 16; i++)
            BitBlt(g_39e8[free], (cell + m) * i + (m - sz) / 2 + cell, (m - sz) / 2 + cell,
                   sz, sz, g_39e8[28], i * sz, 0, SRCCOPY);
    }
    fn_10_0552(28, 0);
    SelectObject(dc1, old1);
    DeleteDC(dc1);
    DeleteObject(bm1);
    fn_10_6308(free, 1, 1, 1);
    if (m & 1) {
        cell = 4;
        m++;
    } else
        cell = 6;
    g_4d90[rec].f_08 = m;
    g_4d90[rec].f_09 = cell;
    return free;
}

/* Sets the per-list object defaults (sizes scaled by the zoom g_9156,
 * draw/collision handlers f5e/f62/f66) for every object of lists 0..11,
 * then clears g_2408 and g_238c. f28 is stored twice for list 0 (as in
 * the original). */
/* 10:0b94 */
void fn_10_0b94(void)
{
    int16_t i;
    int16_t v6;
    int16_t v8;

    for (i = 0; i < g_92ec[0]; i++) {
        g_1df8[0][i].f_22 = SC(32);
        g_1df8[0][i].f_20 = 256;
        g_1df8[0][i].f_24 = SC(6);
        g_1df8[0][i].f_28 = i;
        g_1df8[0][i].f_44 = 160;
        g_1df8[0][i].f_42 = 18;
        g_1df8[0][i].f_46 = 2;
        g_1df8[0][i].f_62 = fn_11_39d8;
        g_1df8[0][i].f_5e = fn_07_233c;
        g_1df8[0][i].f_53 = 1;
        g_1df8[0][i].f_28 = i;
    }
    for (i = 0; i < g_92ec[1]; i++) {
        g_1df8[1][i].f_22 = SC(20);
        g_1df8[1][i].f_24 = SC(6);
        g_1df8[1][i].f_20 = 160;
        g_1df8[1][i].f_44 = 60;
        g_1df8[1][i].f_42 = 18;
        g_1df8[1][i].f_4c = 0x808000L;
        g_1df8[1][i].f_2c = 14;
        g_1df8[1][i].f_1e = 0;
        g_1df8[1][i].f_18 = 1;
        g_1df8[1][i].f_04.x = -1000;
        g_1df8[1][i].f_04.y = -1000;
        g_1df8[1][i].f_66 = fn_07_2e02;
        g_1df8[1][i].f_62 = fn_11_3914;
        g_1df8[1][i].f_5e = fn_07_2652;
        g_1df8[1][i].f_53 = 0;
        g_1df8[1][i].f_48 = 1;
    }
    for (i = 0; i < g_92ec[2]; i++) {
        g_1df8[2][i].f_22 = SC(14);
        g_1df8[2][i].f_24 = SC(2);
        g_1df8[2][i].f_20 = 104;
        g_1df8[2][i].f_44 = 55;
        g_1df8[2][i].f_48 = 0;
        g_1df8[2][i].f_42 = 7;
        g_1df8[2][i].f_2f = 4;
        g_1df8[2][i].f_4c = 0xffffL;
        g_1df8[2][i].f_62 = fn_11_3914;
        g_1df8[2][i].f_5e = fn_08_95f2;
        g_1df8[2][i].f_53 = 0;
    }
    for (i = 0; i < g_92ec[3]; i++) {
        if (i < g_92ec[3] - g_92ea) {
            g_1df8[3][i].f_22 = SC(44);
            g_1df8[3][i].f_20 = 344;
            g_1df8[3][i].f_44 = 1400;
            g_1df8[3][i].f_62 = fn_11_3bae;
            g_1df8[3][i].f_2c = 60;
            g_1df8[3][i].f_24 = SC(4);
        } else {
            g_1df8[3][i].f_22 = SC(22);
            g_1df8[3][i].f_20 = 168;
            g_1df8[3][i].f_44 = 350;
            g_1df8[3][i].f_62 = fn_11_3914;
            g_1df8[3][i].f_2c = 200;
            g_1df8[3][i].f_24 = SC(4);
            if (g_9156 == 2)
                g_1df8[3][i].f_24 = 4;
            if (g_9156 == 1 && g_0740)
                g_1df8[3][i].f_24 = 2;
            if (g_9156 == 0 && g_0740)
                g_1df8[3][i].f_24 = 1;
        }
        g_1df8[3][i].f_48 = 9;
        g_1df8[3][i].f_42 = 8;
        g_1df8[3][i].f_46 = 4;
        g_1df8[3][i].f_4c = 0xc0c0c0L;
        g_1df8[3][i].f_5e = fn_07_5090;
        g_1df8[3][i].f_53 = 0;
        g_1df8[3][i].f_54 = 0;
    }
    if (!g_9214) {
        v6 = 36;
        v8 = 6;
    } else {
        v6 = 30;
        v8 = 4;
    }
    for (i = 0; i < g_92ec[4]; i++) {
        g_1df8[4][i].f_22 = SC(v6);
        g_1df8[4][i].f_20 = v6 * 8;
        g_1df8[4][i].f_24 = SC(v8);
        g_1df8[4][i].f_44 = 110;
        g_1df8[4][i].f_42 = 30;
        g_1df8[4][i].f_4c = 0xffL;
        g_1df8[4][i].f_48 = 10;
        g_1df8[4][i].f_46 = 5;
        g_1df8[4][i].f_62 = fn_11_3bae;
        g_1df8[4][i].f_5e = fn_12_0dc4;
        g_1df8[4][i].f_53 = 1;
        g_1df8[4][i].f_54 = 0;
    }
    for (i = 0; i < g_92ec[5]; i++) {
        g_1df8[5][i].f_44 = 120;
        g_1df8[5][i].f_42 = 100;
        g_1df8[5][i].f_4c = 0xffL;
        g_1df8[5][i].f_62 = fn_11_3914;
        g_1df8[5][i].f_5e = fn_07_570a;
        g_1df8[5][i].f_53 = 0;
        g_1df8[5][i].f_54 = 0;
    }
    for (i = 0; i < g_92ec[6]; i++) {
        g_1df8[6][i].f_44 = 20;
        g_1df8[6][i].f_42 = 6;
        g_1df8[6][i].f_4c = 0x7f00L;
        g_1df8[6][i].f_2c = -1;
        g_1df8[6][i].f_48 = 5;
        g_1df8[6][i].f_62 = fn_11_3914;
        g_1df8[6][i].f_5e = fn_07_2652;
        g_1df8[6][i].f_53 = 0;
        g_1df8[6][i].f_54 = 0;
    }
    g_1df8[7][0].f_22 = SC(40);
    g_1df8[7][0].f_20 = 320;
    g_1df8[7][0].f_24 = SC(6);
    g_1df8[7][0].f_44 = 800;
    g_1df8[7][0].f_42 = 8;
    g_1df8[7][0].f_18 = 1;
    g_1df8[7][0].f_2c = 800;
    g_1df8[7][0].f_46 = 1;
    g_1df8[7][0].f_48 = 7;
    g_1df8[7][0].f_66 = fn_12_274a;
    g_1df8[7][0].f_62 = fn_11_37a0;
    g_1df8[7][0].f_5e = fn_16_085e;
    g_1df8[7][0].f_53 = 0;
    g_1df8[7][0].f_54 = 0;
    for (i = 0; i < g_92ec[8]; i++) {
        g_1df8[8][i].f_0c = 0;
        g_1df8[8][i].f_0e = 0;
        g_1df8[8][i].f_53 = 0;
    }
    for (i = 0; i < g_92ec[9]; i++) {
        g_1df8[9][i].f_22 = SC(38);
        g_1df8[9][i].f_20 = 296;
        g_1df8[9][i].f_24 = SC(4);
        g_1df8[9][i].f_44 = 360;
        g_1df8[9][i].f_18 = 1;
        g_1df8[9][i].f_42 = 18;
        g_1df8[9][i].f_46 = 6;
        g_1df8[9][i].f_2c = 80;
        g_1df8[9][i].f_48 = 4;
        g_1df8[9][i].f_62 = fn_11_39d8;
        g_1df8[9][i].f_5e = fn_07_2652;
        g_1df8[9][i].f_66 = fn_12_274a;
        g_1df8[9][i].f_53 = 0;
        g_1df8[9][i].f_54 = 0;
        g_1df8[9][i].f_2f = 7;
    }
    for (i = 0; i < g_92ec[10]; i++) {
        g_1df8[10][i].f_22 = SC(12);
        g_1df8[10][i].f_20 = 96;
        g_1df8[10][i].f_24 = SC(6);
        g_1df8[10][i].f_0c = 0;
        g_1df8[10][i].f_0e = 0;
        g_1df8[10][i].f_44 = 11;
        g_1df8[10][i].f_18 = 1;
        g_1df8[10][i].f_42 = 6;
        g_1df8[10][i].f_46 = 4;
        g_1df8[10][i].f_4c = 0x7f7f7fL;
        g_1df8[10][i].f_2c = -1;
        g_1df8[10][i].f_48 = 0;
        g_1df8[10][i].f_66 = fn_12_274a;
        g_1df8[10][i].f_62 = fn_11_3914;
        g_1df8[10][i].f_5e = fn_07_2652;
        g_1df8[10][i].f_53 = 0;
        g_1df8[10][i].f_54 = 0;
    }
    for (i = 0; i < g_92ec[11]; i++) {
        g_1df8[11][i].f_24 = SC(4);
        g_1df8[11][i].f_44 = 101;
        g_1df8[11][i].f_18 = 1;
        g_1df8[11][i].f_42 = 18;
        g_1df8[11][i].f_46 = 2;
        g_1df8[11][i].f_2c = 400;
        g_1df8[11][i].f_48 = 5;
        g_1df8[11][i].f_62 = fn_11_39d8;
        g_1df8[11][i].f_5e = fn_07_2652;
        g_1df8[11][i].f_66 = fn_12_6a60;
        g_1df8[11][i].f_53 = 1;
        g_1df8[11][i].f_54 = 0;
    }
    g_238c = g_2408 = 0;
}
