/* INSPACE.EXE segment 14 (selector 1068). */
#include "game.h"

#define SC(n) ((int16_t)((n) << g_9156) >> 1)

/* 14:455c */
int16_t fn_14_455c(int16_t k)
{
    if (g_11aa)
        return 1;
    switch (g_6e1c[g_6e20[k].f_21].f_21) {
    case 178: case 310: case 320: case 400: case 440: case 450: case 520:
    case 550: case 560: case 590: case 600: case 604: case 605: case 710:
    case 720: case 730: case 750: case 890: case 900: case 930: case 950:
        return 0;
    }
    return 1;
}

/* Pick a random entry of the DS:6e20 table and copy its name [inferred]. */
/* 14:31d0 */
int16_t fn_14_31d0(int16_t a, LPSTR out)
{
    int16_t k, n, ok;

    ok = 0;
    n = rand() % 20 + 10;
    do {
        k = rand() % g_95aa;
        ok = 1;
        if (g_6e20[k].f_0a[0] == 0)
            ok = 0;
        if (!fn_14_455c(k))
            ok = 0;
        if (g_6e20[k].f_03 == 7 && a == 0)
            ok = 0;
        if (n > 0)
            n--;
    } while (n != 0 || !ok);
    lstrcpy(out, g_6e20[k].f_0a);
    return k;
}

/* 14:4520 */
int16_t fn_14_4520(int16_t key, int16_t last)
{
    int16_t i;

    for (i = 0; i <= last; i++)
        if (g_7090[i].f_0d6 == key)
            return i;
    return -1;
}

/* Load MASTER.BOD (ShipPath in the ini) into the REC2C table [inferred].
 * Returns 0 ok, 1 already loaded, 2 open failed, 3 no memory, 4 read failed. */
/* 14:3db6 */
int16_t fn_14_3db6(void)
{
    int16_t u;
    HFILE fh;
    OFSTRUCT of;
    uint32_t len;
    char path[128];

    if (g_95ac)
        return 1;
    GetPrivateProfileString(g_9690, "ShipPath", "", path, 0x6d, g_96a9);
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, "MASTER.BOD");
    fh = OpenFile(path, &of, OF_READ);
    if (fh == HFILE_ERROR)
        return 2;
    g_95ae = (len = _filelength(fh)) / sizeof(REC2C);
    g_95ac = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
                         len = (uint16_t)(g_95ae * sizeof(REC2C)));
    g_6e1c = (REC2C *)GlobalLock(g_95ac);
    if (!g_95ac)
        return 3;
    if (!fn_14_4006(fh, (char *)g_6e1c, len)) {
        GlobalUnlock(g_95ac);
        GlobalFree(g_95ac);
        _lclose(fh);
        return 4;
    }
    _lclose(fh);
    fh = 0;
    return 0;
}

/* Load MASTER.SHP into the REC41 table [inferred]; same results. */
/* 14:3eda */
int16_t fn_14_3eda(void)
{
    int16_t u;
    HFILE fh;
    OFSTRUCT of;
    uint32_t len;
    char path[128];

    if (g_95a6)
        return 1;
    fn_14_3db6();
    GetPrivateProfileString(g_9690, "ShipPath", "", path, 0x6d, g_96a9);
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, "MASTER.SHP");
    fh = OpenFile(path, &of, OF_READ);
    if (fh == HFILE_ERROR) {
        g_9498++;
        return 2;
    }
    g_95aa = (len = _filelength(fh)) / sizeof(REC_41);
    g_95a6 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
                         len = (uint16_t)(g_95aa * sizeof(REC_41)));
    g_6e20 = (REC_41 *)GlobalLock(g_95a6);
    if (!g_95a6)
        return 3;
    if (!fn_14_4006(fh, (char *)g_6e20, len)) {
        GlobalUnlock(g_95a6);
        GlobalFree(g_95a6);
        _lclose(fh);
        return 4;
    }
    _lclose(fh);
    fh = 0;
    return 0;
}

/* 14:4006 */
int16_t fn_14_4006(HFILE f, char *buf, uint32_t len)
{
    char *p;
    int16_t n;

    p = buf;
    while (len != 0) {
        n = len > 0x7fff ? 0x7fff : (int16_t)len;
        if (_lread(f, p, n) != (uint16_t)n)
            return 0;
        len -= n;
        p += n;
    }
    return 1;
}

/* 14:4074 */
void fn_14_4074(void)
{
    if (g_6e20) {
        GlobalUnlock(g_95a6);
        g_6e20 = 0;
        GlobalFree(g_95a6);
        g_95a6 = 0;
    }
    if (g_6e1c) {
        GlobalUnlock(g_95ac);
        g_6e1c = 0;
        GlobalFree(g_95ac);
        g_95ac = 0;
    }
}

/* Rating of record n [inferred]: class index 1..10 whose [lo, hi) range
 * holds the score; falls off the end (returns the score in ax) when none. */
/* 14:40d8 */
int16_t fn_14_40d8(int16_t n)
{
    int16_t k, a, b, u1, c, u2;

    a = g_6e20[n].f_02 * g_6e1c[g_6e20[n].f_21].f_1b / 36;
    u1 = 22 * g_6e1c[g_6e20[n].f_21].f_1d / max(g_6e20[n].f_01, 22);
    b = ((10 * g_6e20[n].f_01 - g_6e1c[g_6e20[n].f_21].f_1c)
         / g_6e1c[g_6e20[n].f_21].f_1b - u1) * 2;
    c = g_1332[g_6e20[n].f_06];
    if (!(g_6e20[n].f_09 & 4))
        a = (int16_t)(a * 3) / 4;
    if (g_6e20[n].f_09 & 8)
        a = (int16_t)(a * 6) / 5;
    if (g_6e1c[g_6e20[n].f_21].f_20 & 2)
        a = (int16_t)(a * 6) / 5;
    if (!(g_6e20[n].f_09 & 0x10))
        b = (int16_t)(b * 5) / 6;
    u2 = c + b + a;
    for (k = 1; k < 11; k++)
        if (g_0952[k] <= u2 && g_096c[k] > u2)
            return k;
}

/* (Re)load the sprite of object n [inferred]. */
/* 14:11a8 */
void fn_14_11a8(int16_t n)
{
    int16_t slot, c, j, r, v, rec, u;
    char sel;
    char buf[30];
    int16_t f2, f1;

    c = g_7090[n].f_04e;
    slot = n + 40;
    if (g_7090[n].f_050 != n && g_7090[g_7090[n].f_050].f_0ad
        && g_7090[g_7090[n].f_050].f_0ac) {
        if (g_96d2[c].f_46) {
            fn_10_86e2(n);
            fn_10_5d3c(n);
        }
        goto done;
    }
    if (g_39e8[slot] && g_7090[n].f_0ac && g_7090[n].f_0ad)
        goto done;
    if (g_39e8[slot])
        f1 = 1;
    else
        f1 = 0;
    if (g_7090[n].f_0e4)
        sel = 0;
    else
        sel = 2;
    if (g_7090[n].f_0e9)
        sel = 1;
    if (g_90f4 == 1 && g_1e68 > 0) {
        if ((g_931e == 1 && n != main_ship) || g_931e == 2)
            f2 = 1;
        else
            f2 = 0;
    } else if (g_931e == 2)
        f2 = 1;
    else
        f2 = 0;
    fn_10_6ee6(slot, g_96d2[c].f_36, g_96d2[c].f_84, 1, 0x63, LO16(g_96d2[c].f_a9), HI16(g_96d2[c].f_a9), 1, 0, LO8(g_96d2[c].f_18), LO8(g_96d2[c].f_1a), sel, f2);
    r = fn_10_86ca();
    if (r & 1)
        v = 5;
    else
        v = 6;
    if (g_7090[n].f_0d6 != -1) {
        g_6e24[g_7090[n].f_0d6].f_7a = (char)r;
        g_6e24[g_7090[n].f_0d6].f_7b = (char)v;
    } else if (!f1) {
        g_1df8[g_9324][n].f_22 = r;
        g_1df8[g_9324][n].f_24 = v;
    }
    u = g_7090[n].f_0d6;
    if (u != -1)
        rec = g_6e24[u].f_00;
    else
        rec = g_4ed8[g_7090[n].f_05e];
    if (g_95a6) {
        g_96d2[c].f_68 = g_6e1c[g_6e20[rec].f_21].f_1e - r / 2 - g_9156;
        g_96d2[c].f_6a = g_6e1c[g_6e20[rec].f_21].f_1f - r / 2;
        g_96d2[c].f_6c = -(g_96d2[c].f_68 + g_9156);
        g_96d2[c].f_6e = g_96d2[c].f_6a;
    }
done:
    g_7090[n].f_0ac = g_7090[n].f_0ad = 1;
    for (j = 0; j < g_7090[n].cnt; j++)
        if (g_2f4c[g_7090[n].f_0b8[j]].f_12)
            fn_10_533a(g_7090[n].f_0b8[j]);
}

/* Update object n's per-object scores and its top-5 list in g_6e24
 * [inferred]. */
/* 14:421c */
void fn_14_421c(int16_t n)
{
    int16_t s2, s1, j, i, m, u, flag, mx2, mx;
    char b1, b2, k;

    k = g_7090[n].f_0d6;
    if (k != -1) {
        for (i = 0; i <= g_9316; i++)
            g_7090[n].f_062[i + 8] = fn_09_88ba(g_7090[n].f_062[i + 8]);
        for (j = 0; j < 5; j++)
            for (i = 0; i <= g_9316; i++)
                if (g_6e24[k].f_17[j] == g_7090[i].f_0d6)
                    g_6e24[k].f_08[j] = g_7090[n].f_062[i + 8];
        for (j = 0; j <= g_9316; j++) {
            b2 = b1 = 0;
            mx = mx2 = 0;
            s1 = 0;
            s2 = 0;
            if (j != n && g_7090[j].flag) {
                for (i = 1; i <= 5; i++) {
                    s2 += g_7090[n].f_0f6[j][i];
                    if (g_7090[n].f_0f6[j][i] > mx && i != 2) {
                        mx = g_7090[n].f_0f6[j][i];
                        b2 = i;
                    }
                }
                for (i = 6; i <= 8; i++) {
                    s1 += g_7090[n].f_0f6[j][i];
                    if (g_7090[n].f_0f6[j][i] > mx2) {
                        mx2 = g_7090[n].f_0f6[j][i];
                        b1 = i;
                    }
                }
                if ((int16_t)((8 - g_7090[n].f_05d) * s1) < (int16_t)((8 - g_7090[n].f_05e) * s2)) {
                    if (g_7090[n].f_062[j + 8] <= s2) {
                        g_7090[n].f_0ee[j] = b2;
                        g_7090[n].f_062[j + 8] = s2;
                        flag = 1;
                    } else
                        flag = 0;
                } else {
                    if (g_7090[n].f_062[j + 8] <= s1) {
                        g_7090[n].f_0ee[j] = b1;
                        g_7090[n].f_062[j + 8] = s1;
                        flag = 1;
                    } else
                        flag = 0;
                }
            } else {
                g_7090[n].f_0ee[j] = 0;
                g_7090[n].f_062[j + 8] = 0;
            }
        }
        if (flag) {
            for (i = 0; i <= g_9316; i++)
                for (j = 0; j < 5; j++)
                    if (g_6e24[k].f_08[j] < g_7090[n].f_062[i + 8]) {
                        for (m = 4; m > j; m--) {
                            g_6e24[k].f_12[m] = g_6e24[k].f_12[m - 1];
                            g_6e24[k].f_08[m] = g_6e24[k].f_08[m - 1];
                            g_6e24[k].f_17[m] = g_6e24[k].f_17[m - 1];
                        }
                        g_6e24[k].f_12[j] = g_7090[n].f_0ee[i];
                        g_6e24[k].f_08[j] = g_7090[n].f_062[i + 8];
                        g_6e24[k].f_17[j] = g_7090[i].f_0d6;
                        j = 5;
                    }
        }
    }
}

/* Give object n a g_6e24 record (new, or the weakest unused one when
 * full) built from ship type s, or reuse k0 [inferred]. */
/* 14:0dd6 */
void fn_14_0dd6(int16_t n, int16_t s, int16_t k0)
{
    int16_t i, j, m, best, bi, k;

    if (g_95b4 > g_95b2) {
        if (g_931a > 0x26) {
            int16_t flag;

            best = 1000;
            bi = -1;
            for (j = 1; j < 40; j++)
                if (g_6e24[j].f_06 < best) {
                    flag = 1;
                    for (m = 0; m < n; m++)
                        if (g_7090[m].f_0d6 == j)
                            flag = 0;
                    if (flag) {
                        best = g_6e24[j].f_06;
                        bi = j;
                    }
                }
            if (bi == -1) {
                MessageBeep(0);
                bi = 10;
            }
            for (i = 0; i < g_94a4; i++)
                for (m = 0; m < 8; m++)
                    if (g_69f4[i].f_1c0[m] == bi)
                        g_69f4[i].f_1c0[m] = -1;
            k = bi;
        } else {
            g_931a++;
            GlobalUnlock(g_95a4);
            g_95a4 = GlobalReAlloc(g_95a4, (int32_t)(int16_t)(g_931a + 1) * 0x7c, GHND);
            g_6e24 = (REC_7C *)GlobalLock(g_95a4);
            k = g_931a;
        }
        g_6e24[k].f_00 = s;
        for (j = 0; j < 40; j++)
            g_6e24[k].f_3c[j] = 0;
        for (j = 0; j < 4; j++)
            g_6e24[k].f_38[j] = 100;
        for (j = 0; j < 5; j++) {
            g_6e24[k].f_12[j] = 0;
            g_6e24[k].f_08[j] = 0;
            g_6e24[k].f_17[j] = -1;
        }
        if (g_6e20[s].f_06) {
            g_6e24[k].f_1d = 2;
            if (g_11aa == 0 && g_2f4c[g_6e20[s].f_06].f_3e != -1)
                g_6e24[k].f_28[1] = g_2f4c[g_6e20[s].f_06].f_3e;
            else
                g_6e24[k].f_28[1] = g_6e20[s].f_06;
            g_6e24[k].f_1e[1] = 20;
        } else
            g_6e24[k].f_1d = 1;
        g_6e24[k].f_06 = 15;
        g_6e24[k].f_73 = 1;
        g_6e24[k].f_72 = g_6e24[k].f_73;
        g_6e24[k].f_74 = 1;
        g_6e24[k].f_75 = 1;
        g_6e24[k].f_1c = g_6e20[s].f_00;
        g_6e24[k].f_02 = rand() % (int16_t)((g_9334 + 1) * 10) + 10;
        g_6e24[k].f_04 = rand() % (int16_t)((g_9334 + 1) * 50) + 150;
        g_6e24[k].f_77 = 0;
        g_6e24[k].f_64 = g_6e20[s].f_03;
        fn_09_5be0(n, k);
    } else {
        k = k0;
        for (i = 0; i < g_94a4; i++)
            for (j = 0; j < 10; j++)
                if (g_69f4[i].f_1c0[j] == k) {
                    g_69f4[i].f_1c0[j] = -1;
                    break;
                }
        for (j = 0; j < 8; j++)
            if (g_69f4[g_94a2].f_1c0[j] == -1) {
                g_69f4[g_94a2].f_1c0[j] = k;
                break;
            }
        if (g_6e24[k].f_79 < (int16_t)(g_91f8 - 1))
            g_6e24[k].f_02 += min((int16_t)((g_91f8 - g_6e24[k].f_79) * (g_9334 + 15)), 200);
    }
    g_7090[n].f_0d6 = k;
    g_0992 += 40;
}

/* Set up object n for a new mission from its pilot record [inferred]. */
/* 14:1430 */
void fn_14_1430(int16_t n)
{
    int16_t i, u1, t, j, c, g;

    t = g_7090[n].f_0d6;
    if (t != -1)
        g = g_6e24[t].f_00;
    else
        g = g_4ed8[g_7090[n].f_05e];
    if ((int16_t)(g_95aa - 1) < g) {
        g_6e24[t].f_00 = 0;
        g = g_6e24[t].f_00;
    }
    c = g_7090[n].f_04e;
    if (t != -1)
        g_96d2[c].f_38 = g_6e24[t].f_64;
    else
        g_96d2[c].f_38 = g_6e20[g].f_03;
    g_7090[n].f_147 = 0;
    fn_14_1b84(n, c, t, g);
    for (j = 0; j <= 8; j++)
        for (i = 0; i <= g_9316; i++)
            g_7090[n].f_0f6[i][j] = 0;
    g_7090[n].f_004 = n + 40;
    g_7090[n].f_0b8[0] = 0;
    g_7090[n].f_0ae[0] = 1;
    if (t != -1)
        g_7090[n].cnt = g_6e24[t].f_1d;
    g_8e08[n] = 1000000L;
    for (i = g_7090[n].cnt; i < 10; i++)
        g_7090[n].f_0b8[i] = 0;
    for (i = 0; i < 2; i++)
        (&g_7090[n].f_05d)[i] = g_96d2[c].f_84[0x20 + i];
    g_7090[n].f_032.a = g_7090[n].f_006 = 8;
    g_7090[n].f_032.b = g_7090[n].f_008 = 0;
    g_7090[n].f_038 = 3;
    g_7090[n].f_03c = 2;
    g_7090[n].f_148 = g_7090[n].f_149 = -1;
    g_7090[n].f_094 = 0;
    g_7090[n].f_0ea = 0;
    g_1df8[g_9324][n].f_28 = 0;
    g_1df8[g_9324][n].f_51 = 0;
    g_7090[n].f_010 = 0;
    g_7090[n].f_002 = 0;
    g_7090[n].f_0e8 = 0;
    if (n == main_ship && g_9134 != 0)
        g_7090[n].f_052 = 7;
    else
        g_7090[n].f_052 = 0;
    if (g_96d2[c].f_38 == 7 && g_7090[n].f_05e > 1) {
        g_7090[n].f_052 = 0x14;
        g_7090[n].f_054 = g_9324;
        g_7090[n].f_056 = main_ship;
    }
    if (g_9320 == 7 && (n != main_ship || !flow_interactive)) {
        g_7090[n].f_052 = 4;
        g_7090[n].f_054 = 14;
        g_7090[n].f_056 = main_ship;
        if (n == main_ship)
            fn_03_00f4(n, 14, g_7090[n].f_056 = 1);
        else
            fn_03_00f4(n, 14, main_ship);
        g_7090[n].f_058 = n;
    }
    if (t != -1) {
        g_7090[n].cnt = g_6e24[t].f_1d;
        for (j = 1; j < g_6e24[t].f_1d; j++) {
            if (g_11aa == 0 && g_2f4c[g_6e24[t].f_28[j]].f_3e != -1)
                g_6e24[t].f_28[j] = g_2f4c[g_6e24[t].f_28[j]].f_3e;
            g_7090[n].f_0b8[j] = g_6e24[t].f_28[j];
            g_7090[n].f_0ae[j] = g_6e24[t].f_1e[j];
        }
        if (g_104c[0].b)
            fn_12_6d64(n, 13);
        for (j = 0; j < 4; j++)
            (&g_7090[n].f_026[0])[j] = g_6e24[t].f_38[j];
        for (i = 0; i <= g_9316; i++) {
            g_7090[n].f_062[i + 8] = 0;
            g_7090[n].f_0ee[i] = 0;
        }
        for (j = 0; j < 5; j++)
            for (i = 0; i <= g_9316; i++)
                if (g_6e24[t].f_17[j] == g_7090[i].f_0d6
                    && g_6e24[t].f_08[j] > 1 && i != n) {
                    g_7090[n].f_0ee[i] = g_6e24[t].f_12[j];
                    g_7090[n].f_062[i + 8] = g_6e24[t].f_08[j];
                }
        for (j = 0; j <= g_9316; j++)
            for (i = 0; i < 3; i++)
                if (g_4eec[g_96d2[c].f_38][i] == g_7090[j].f_0d6
                    && g_7090[j].f_0d6 >= 0
                    && g_7090[n].f_062[j + 8] < 15) {
                    g_7090[n].f_0ee[j] = 4;
                    g_7090[n].f_062[j + 8] += 15;
                }
        g_7090[n].f_01e = 40 * (uint8_t)g_6e24[t].f_1c;
        if (n != main_ship)
            g_7090[n].f_01e = max(g_7090[n].f_01e, (int16_t)(g_96d2[c].f_1e * 2) / 3);
        if (g_96d2[c].f_1e < g_7090[n].f_01e) {
            g_7090[n].f_01e = g_96d2[c].f_1e;
            g_6e24[t].f_1c = g_96d2[c].f_1e / 40;
        }
        if (g_7090[main_ship].f_0e4 == 0)
            g_7090[n].f_0ac = g_7090[n].f_0ad = 1;
        else {
            g_7090[n].f_0ac = g_6e24[t].f_72;
            g_7090[n].f_0ad = g_6e24[t].f_73;
        }
        g_7090[n].f_024 = g_6e24[t].f_74;
        g_7090[n].f_00a = g_6e24[t].f_75;
        g_7090[n].f_0dc = 10L * g_6e24[t].f_02;
        g_7090[n].f_0ce = g_6e24[t].f_04;
        g_7090[n].f_082 = g_6e24[t].f_06;
        g_7090[n].f_000 = 0;
        if ((int16_t)(g_6e24[t].f_79 - g_91f8) == -1)
            g_6e24[t].f_78++;
        else if (g_6e24[t].f_78 > 1) {
            g_7090[n].f_000 = 4;
            g_6e24[t].f_78 = 1;
        } else
            g_6e24[t].f_78 = 0;
        if (g_6e24[t].f_79 != g_91f8)
            g_6e24[t].f_77++;
        g_6e24[t].f_79 = (char)g_91f8;
        for (j = 0; j < g_9316; j++)
            g_7090[n].f_062[j] = 10 * g_6e24[t].f_3c[g_7090[j].f_0d6];
    } else {
        g_7090[n].cnt = 3;
        g_7090[n].f_0b8[1] = 15;
        g_7090[n].f_0ae[1] = 1;
        g_7090[n].f_0b8[2] = g_6e20[g].f_06;
        g_7090[n].f_0ae[2] = 20;
        if (g_7090[n].f_05e == 0) {
            g_7090[n].f_052 = 0x17;
            g_7090[n].f_054 = g_9324;
            g_7090[n].f_056 = fn_14_4520(g_9346, g_9316);
            g_7090[n].f_0cd = (char)g_7090[n].f_056;
            if (g_7090[n].f_0cd < 0)
                g_7090[n].f_0cd = (char)(g_7090[n].f_056 = main_ship);
            g_7090[n].f_0ed = 1;
        }
        for (j = 0; j < 4; j++)
            (&g_7090[n].f_026[0])[j] = 100;
        for (j = 0; j < 5; j++) {
            g_7090[n].f_0ee[j] = 0;
            g_7090[n].f_062[j + 8] = 0;
        }
        g_7090[n].f_01e = 40 * g_6e20[g].f_00;
        g_7090[n].f_0ad = g_7090[n].f_0ac = 1;
        g_7090[n].f_00a = g_7090[n].f_024 = 2;
        g_7090[n].f_0ce = 100;
        g_7090[n].f_0dc = 0;
        g_7090[n].f_082 = 0;
        for (j = 0; j < g_9316; j++)
            g_7090[n].f_062[j] = 0;
    }
}

/* Fill class record c (and object n) from body g and pilot t [inferred]. */
/* 14:1b84 */
void fn_14_1b84(int16_t n, int16_t c, int16_t t, int16_t g)
{
    int16_t i;

    g_96d2[c].f_4e = 1;
    g_96d2[c].f_18 = g_6e20[g].f_07;
    g_96d2[c].f_1a = g_6e20[g].f_08;
    if (g_96d2[c].f_18 == 12)
        LO16(g_96d2[c].f_a9) = g_6e1c[g_6e20[g].f_21].f_15;
    else
        LO16(g_96d2[c].f_a9) = 0;
    if (g_96d2[c].f_1a == 12)
        HI16(g_96d2[c].f_a9) = g_6e1c[g_6e20[g].f_21].f_17;
    else
        HI16(g_96d2[c].f_a9) = 0;
    lstrcpy(g_96d2[c].f_84, g_6e1c[g_6e20[g].f_21].f_23);
    lstrcpy(g_96d2[c].f_93, g_6e20[g].f_38);
    g_96d2[c].f_04 = -g_6e1c[g_6e20[g].f_21].f_19;
    g_96d2[c].f_3e = 5 * g_6e20[g].f_01;
    g_96d2[c].f_40 = g_6e1c[g_6e20[g].f_21].f_1c;
    g_96d2[c].f_0a = g_6e20[g].f_02 / 4;
    g_96d2[c].f_0c = g_6e20[g].f_02 / 5;
    g_96d2[c].f_0e = g_6e20[g].f_02 / 5;
    g_96d2[c].f_08 = g_6e20[g].f_02 / 4;
    g_96d2[c].f_12 = g_6e20[g].f_02 / 5;
    g_96d2[c].f_14 = g_6e20[g].f_02 / 4;
    g_96d2[c].f_16 = g_6e20[g].f_02 / 5;
    g_96d2[c].f_10 = g_6e20[g].f_02 / 4;
    g_96d2[c].f_a6 = g_6e20[g].f_02;
    g_96d2[c].f_1e = 40 * g_6e20[g].f_00;
    g_96d2[c].f_20 = g_6e1c[g_6e20[g].f_21].f_1d;
    g_96d2[c].f_22 = 0;
    g_96d2[c].f_24 = 1;
    g_96d2[c].f_26 = 2;
    if (g_6e1c[g_6e20[g].f_21].f_20 & 8)
        g_96d2[c].f_48 = 1;
    else
        g_96d2[c].f_48 = 0;
    if (g_6e1c[g_6e20[g].f_21].f_20 & 4)
        g_96d2[c].f_28 = 3;
    else if (g_6e20[g].f_09 & 8)
        g_96d2[c].f_28 = 4;
    else if (g_6e1c[g_6e20[g].f_21].f_20 & 2)
        g_96d2[c].f_28 = 5;
    else
        g_96d2[c].f_28 = -1;
    if (!(g_6e1c[g_6e20[g].f_21].f_20 & 4))
        g_7090[n].f_0ac = g_7090[n].f_0ad = 0;
    g_96d2[c].f_2c = 7;
    if ((g_96d2[c].f_2e = g_6e20[g].f_1f) > 0)
        fn_10_754a(g_96d2[c].f_2e, 0, 0, 5);
    g_96d2[c].f_32 = 10 * g_6e1c[g_6e20[g].f_21].f_1b;
    g_96d2[c].f_32 = g_96d2[c].f_32 * (g_6e20[g].f_02 / 4 + 100L) / 100;
    g_96d2[c].f_30 = g_96d2[c].f_32 / 22;
    g_96d2[c].f_36 = g_6e1c[g_6e20[g].f_21].f_21;
    if (g_6e20[g].f_09 & 0x10)
        g_96d2[c].f_42 = 1;
    else
        g_96d2[c].f_42 = 0;
    if (g_6e20[g].f_09 & 1)
        g_96d2[c].f_44 = 0;
    else
        g_96d2[c].f_44 = 1;
    if (g_6e20[g].f_09 & 0x20)
        g_96d2[c].f_44 |= 0x20;
    if (g_6e1c[g_6e20[g].f_21].f_20 & 4)
        g_96d2[c].f_a3 = 6;
    if (g_6e1c[g_6e20[g].f_21].f_20 & 1)
        g_96d2[c].f_46 = 0;
    else
        g_96d2[c].f_46 = 1;
    if (g_6e1c[g_6e20[g].f_21].f_20 & 0x40)
        g_96d2[c].f_a2 = 1;
    else
        g_96d2[c].f_a2 = 0;
    if (g_6e1c[g_6e20[g].f_21].f_20 & 2) {
        g_96d2[c].f_a7 = 1;
        fn_10_754a(5, 0, 0, 5);
    } else
        g_96d2[c].f_a7 = 0;
    if (g_6e20[g].f_09 & 8)
        g_96d2[c].f_4a = 1;
    else
        g_96d2[c].f_4a = 0;
    if (g_6e20[g].f_09 & 4)
        g_96d2[c].f_4c = 1;
    else
        g_96d2[c].f_4c = 0;
    g_96d2[c].f_66 = g_96d2[c].f_64 = 0;
    for (i = 0; i < 2; i++)
        g_96d2[c].f_a4[i] = g_6e20[g].f_04[i];
    g_96d2[c].f_3c = SC(g_6e1c[g_6e20[g].f_21].f_1a) / 2;
    lstrcpy(g_96d2[c].f_70, g_6e20[g].f_0a);
    g_96d2[c].f_4e = 1;
    g_1df8[g_9324][n].f_44 = g_96d2[c].f_32;
    g_1df8[g_9324][n].f_42 = g_96d2[c].f_2e;
    g_1df8[g_9324][n].f_46 = g_96d2[c].f_2c;
    g_1df8[g_9324][n].f_2c = 200;
    g_1df8[g_9324][n].f_48 = g_96d2[c].f_30;
    g_1df8[g_9324][n].f_1e = 0;
    g_1df8[g_9324][n].f_66 = (FNPTR)self_destruct_ship;
    g_1df8[g_9324][n].f_62 = fn_11_37a0;
    g_1df8[g_9324][n].f_5e = fn_08_45e0;
    g_1df8[g_9324][n].f_2e = 0;
    g_1df8[g_9324][n].f_3c = 0;
    g_1df8[g_9324][n].f_54 = 0;
    g_7090[n].flag = 1;
    g_7090[n].f_00c = g_96d2[c].f_3e;
    g_7090[n].f_00e = g_96d2[c].f_40;
    g_7090[n].f_036 = 0;
    g_7090[n].f_01c = 1;
    g_7090[n].f_084 = GetCurrentTime();
    g_7090[n].f_0e3 = g_96d2[c].f_44 & 1;
    g_7090[n].f_0e4 = g_96d2[c].f_46;
    g_7090[n].f_0e6 = g_96d2[c].f_a2;
    g_7090[n].f_0e7 = g_96d2[c].f_4a;
    g_7090[n].f_0e9 = g_96d2[c].f_a7;
    if (g_91f8 == 1 || n != main_ship)
        g_7090[n].f_00a = 1;
    g_7090[n].f_05a = 1;
    g_7090[n].f_05c = 0;
    g_7090[n].f_052 = g_7090[n].f_054 = 0;
    g_7090[n].f_0ed = 0;
    LO16(g_7090[n].f_0a0) = HI16(g_7090[n].f_0a0) = 0;
    g_7090[n].f_05f = 0;
    if (g_96d2[c].f_a3 != 0)
        g_7090[n].f_0e5 = 1;
    else
        g_7090[n].f_0e5 = 0;
    if (g_7090[n].f_0d6 != -1)
        g_7090[n].f_014 = 1200L * g_96d2[c].f_20
            / ((int32_t)g_96d2[c].f_3e * ((g_6e24[g_7090[n].f_0d6].f_33 + 10) * 10) / 100);
    else
        g_7090[n].f_014 = 1200L * g_96d2[c].f_20 / g_96d2[c].f_3e;
    if (n == main_ship && flow_interactive)
        g_7090[n].f_014 = (int16_t)(g_7090[n].f_014 * 3) / 4;
}

/* View of the class records (RECAD) at DS:96d2, 0x18 bytes below the
 * usual base DS:96ea; field w_XXX is at RECAD offset XXX. */

/* Set up the objects of a new level or wave [inferred]. */
/* 14:0000 */
void fn_14_0000(int16_t arg)
{
    /* Frame order matters; pad* are unused slots of the original frame. */
    int16_t u4, i, j, m, u0c, n, u10, t;
    int16_t pad14[3];
    int16_t s1a, s1c, s1e;                  /* saved g_95b0, g_9316, g_9646 */
    int16_t pad20[2];
    int16_t w, d26;
    int16_t c28, c2a;
    int16_t pad2c[3];
    int16_t c32;
    int16_t a42[8];                         /* old object still present */
    int16_t pad44;
    int16_t a54[8];                         /* object needs a new sprite [inferred] */
    int16_t pad56;
    int16_t f58;
    BITMAP bm;
    int16_t pad76[8];
    int16_t a86[8];                         /* old f_0d4 per object */
    int16_t h;
    int16_t pad8a[2];
    int16_t a9c[8];                         /* old f_04c (class) per object */
    int16_t s, t2;
    int16_t pada2[2];
    int16_t k;
    int16_t pada8;
    int16_t ab8[8], ac8[8], ad8[8], ae8[8]; /* old sprite DC, bitmap, old bitmap, palette */
    char buf[30];

    if (g_95a8 && g_9320 != 6 && g_9320 != 7) {
        session_helper_groups = session_helper_groups < 1 ? 1 : session_helper_groups;
        g_9338 = g_9338 < 1 ? 1 : g_9338;
        g_9338 = g_9338 > 7 ? 7 : g_9338;
        g_95a8 = 0;
    }
    g_9338 = (int16_t)(7 - g_932c) > g_9338 ? g_9338 : 7 - g_932c;
    for (i = 0; i < 8; i++)
        a54[i] = 1;
    g_95b6 = arg;
    g_4ed8[0] = g_4ed8[2] = g_4ed8[1] = g_4ed8[3] = 0;
    if (g_9338 > 2) {
        if (g_9208 < 2 && g_9320 != 6 && g_9320 != 7) {
            g_9338--;
            if (g_9334 > 0)
                g_9334++;
        }
        g_9338 = (int16_t)(g_9208 + 3) > g_9338 ? g_9338 : g_9208 + 3;
    }
    if (arg >= 0)
        n = g_9338 = g_9316 + 1;
    if (g_9320 == 6 || g_9320 == 7) {
        g_932c = 0;
        g_9346 = -1;
    }
    if (arg == -1) {
        u4 = 0;
        if (g_91f8 > 1) {
            s1a = g_95b0;
            s1c = g_9316;
            s1e = main_ship;
            for (i = 0; i <= g_931a; i++)
                for (j = 0; j <= g_931a; j++) {
                    t = (int16_t)((g_6e24[i].f_3c[j] * 10 - g_3824[g_6e24[i].f_64][g_6e24[i].f_64]) * 9) / 10;
                    g_6e24[i].f_3c[j] = (int16_t)(t + g_3824[g_6e24[i].f_64][g_6e24[i].f_64]) / 10;
                }
        } else
            s1c = 0;
        if (g_932c != 0 || g_9346 != -1) {
            if (g_9338 > 2)
                g_9338--;
            if (session_helper_groups > g_9338)
                session_helper_groups = g_9338;
        }
        u10 = g_9338;
        u0c = n = g_95b0 = 0;
        c2a = c28 = 0;
        if (g_91f8 == 1)
            g_7090[0].f_0d6 = -1;
        for (i = 0; i <= g_9316; i++) {
            a42[i] = 0;
            a86[i] = g_7090[i].f_0d6;
            a9c[i] = g_7090[i].f_04e;
            k = i + 40;
            ab8[i] = g_39e8[k];
            ac8[i] = g_3ad0[k];
            ad8[i] = g_3974[k];
            ae8[i] = g_3a5c[k];
        }
        if (g_91f8 <= 1) {
            s = fn_14_2300(main_ship = g_931c = 0, n);
            g_95a4 = GlobalAlloc(GHND, 0x7c);
            if (g_95a4 == 0)
                return;
            g_6e24 = (REC_7C *)GlobalLock(g_95a4);
            if (g_6e24 == NULL) {
                GlobalFree(g_95a4);
                return;
            }
            g_931a = 0;
            if (flow_interactive && g_9320 != 6 && g_9320 != 7)
                g_9338 = 0;
            g_6e24->f_00 = s;
            for (j = 0; j < 40; j++)
                g_6e24->f_3c[j] = 0;
            for (j = 0; j < 4; j++)
                g_6e24->f_38[j] = 100;
            for (j = 0; j < 5; j++) {
                g_6e24->f_12[j] = 0;
                g_6e24->f_08[j] = 0;
                g_6e24->f_17[j] = -1;
            }
            if (g_6e20[s].f_06) {
                g_6e24->f_1d = 2;
                if (g_11aa == 0 && g_2f4c[g_6e20[s].f_06].f_3e != -1)
                    g_6e24->f_28[1] = g_2f4c[g_6e20[s].f_06].f_3e;
                else
                    g_6e24->f_28[1] = g_6e20[s].f_06;
                g_6e24->f_1e[1] = 20;
            } else
                g_6e24->f_1d = 1;
            g_6e24->f_06 = 0;
            g_6e24->f_73 = 1;
            g_6e24->f_72 = g_6e24->f_73;
            g_6e24->f_74 = 1;
            g_6e24->f_75 = 1;
            g_6e24->f_1c = g_6e20[s].f_00;
            g_6e24->f_02 = 15;
            g_6e24->f_04 = 0;
            g_6e24->f_64 = g_96d2[0].f_38 = g_6e20[s].f_03;
            for (i = 0; i < 10; i++) {
                g_a14d[i] = 0;
                g_a157[i] = 0;
            }
            fn_09_5be0(main_ship, 0);
            a54[n] = 1;
            g_1318 = g_7090[0].f_04e = g_7090[0].f_0d6 = main_ship = 0;
        } else {
            g_7090[0].f_04e = g_7090[main_ship].f_04e;
            main_ship = 0;
            g_7090[0].f_0d6 = g_931c;
            if (g_92e4 == 0)
                a54[n] = 0;
            else
                g_7090[0].f_04e = 0;
            g_96d2[g_7090[0].f_04e].f_38 = g_6e24[g_931c].f_64;
        }
        n++;
        if (g_94b0 == 0)
            if (g_92e8 == 0 && g_9320 != 6 && g_9320 != 7)
                for (i = 0; i < 8; i++) {
                    if ((int16_t)(g_0994 * 30 + g_0992) > g_932a)
                        break;
                    if (g_69f4[g_94a2].f_1c0[i] != -1)
                        if (n < 6 && g_6e24[g_69f4[g_94a2].f_1c0[i]].f_78 < 5 && fn_14_455c(g_69f4[g_94a2].f_1c0[i])) {
                        g_7090[n].f_0d6 = g_69f4[g_94a2].f_1c0[i];
                        if (g_92e4 == 0)
                            a54[n] = 0;
                        if (g_6e24[g_7090[n].f_0d6].f_64 == g_6e24[g_931c].f_64)
                            c2a++;
                        g_0992 += 40;
                        for (j = 0; j < g_0994; j++)
                            if (g_4f1c[j] == g_7090[n].f_0d6
                                || g_4f1c[j] == -g_6e24[g_7090[n].f_0d6].f_64
                                || g_4f1c[j] == 100 && g_6e24[g_7090[n].f_0d6].f_64 == 3)
                                g_4f1c[j] = -120;
                        n++;
                        if ((int16_t)(g_0994 * 30 + g_0992 + 40) > g_932a)
                            break;
                        }
                }
    }
    if ((c2a == 0 && session_helper_groups != 0 || g_932c != 0) && arg == -1
        && g_9320 != 6 && g_9320 != 7 && g_92e8 == 0) {
        g_9338 = n < g_9338 ? g_9338 : n;
        g_9338 = g_9338 > 7 ? 7 : g_9338;
    }
    if (g_9320 != 6 && g_9320 != 7 && g_92e8 == 0) {
        for (i = c32 = 0; i < g_0994; i++)
            if (g_4f1c[i] != -120)
                c32++;
        if ((int16_t)(c32 + n - 1) > g_9338)
            g_9338 = c32 + n - 1;
    }
    if (n > g_9338 && g_9346 == -1)
        goto done;
    if (arg == -1 || g_96d2[g_7090[main_ship].f_04e].f_38 == arg) {
        if (arg != -1) {
            session_helper_groups = 1;
            c2a = 0;
        }
        for (i = c2a; i < session_helper_groups; i++)
            if (n < 7) {
                s = fn_14_2300(1, n);
                t2 = fn_14_3274(1, n);
                if (s != -1) {
                    fn_14_0dd6(n, s, t2);
                    n++;
                }
            }
    }
    if (g_9320 != 6 && g_9320 != 7 && g_92e8 == 0)
        if ((int16_t)(c32 + n - 1) > g_9338)
            g_9338 = c32 + n - 1;
    if (g_96d2[g_7090[main_ship].f_04e].f_38 != arg && arg <= 6 || arg == -1)
        for (i = n; i <= g_9338; i++) {
            s = fn_14_2300(4, n);
            if (arg == -1)
                t2 = fn_14_3274(4, n);
            if (s != -1) {
                fn_14_0dd6(n, s, t2);
                n++;
            }
        }
    if (n >= 8)
        goto done;
    if (g_92e8 == 0) {
        if (arg == -1 || arg == 20) {
            if (g_9346 != -1 && fn_14_4520(g_9346, n) != -1 || arg == 20) {
                g_4ed8[0] = s = fn_14_2300(5, n);
                g_7090[n].f_0d6 = -1;
                g_7090[n].f_05e = 0;
                n++;
                if (g_9334 > 6 && fn_14_4520(g_9346, n) == main_ship
                    && g_a14d[0] > 2 && n < 7) {
                    g_7090[n].f_0d6 = -1;
                    g_7090[n].f_05e = 0;
                    n++;
                }
            }
        }
        if (g_932c != 0 && arg == -1 && g_4ed8[0] <= 0 && (int16_t)(g_0992 + 25) < g_932a
            || arg == 22) {
            g_4ed8[3] = g_4ed8[2] = s = fn_14_2300(2, n);
            g_7090[n].f_0d6 = -1;
            g_7090[n].f_05e = 3;
            g_0992 += 40;
            n++;
        }
        if (arg == 21) {
            g_4ed8[1] = s = fn_14_2300(3, n);
            g_7090[n].f_0d6 = -1;
            g_7090[n].f_05e = 1;
            g_0992 += 50;
            n++;
        }
    }
    if (arg == 19) {
        s = fn_14_2300(0, n);
        g_95b2 = -3000;
        fn_14_0dd6(n, s, 0);
        n++;
    }
done:
    if (arg == -1 && g_92e4 == 0) {
        for (i = 0; i <= g_9316; i++) {
            if (a86[i] != -1)
                for (j = 0; j < n; j++)
                    if (a86[i] == g_7090[j].f_0d6)
                        a42[i] = 1;
            if (a42[i] == 0) {
                g_96d2[a9c[i]].f_4e = 0;
                fn_10_1eb6(i);
            }
        }
        for (i = 0; i < n; i++) {
            a54[i] = 1;
            for (j = 0; j <= g_9316; j++)
                if (a86[j] == g_7090[i].f_0d6 && g_7090[i].f_0d6 != -1) {
                    a54[i] = 0;
                    if (j != i) {
                        k = i + 40;
                        g_39e8[k] = ab8[j];
                        g_3ad0[k] = ac8[j];
                        g_3974[k] = ad8[j];
                        g_3a5c[k] = ae8[j];
                        if (ab8[j] == (int16_t)g_39e8[j + 40]) {
                            g_39e8[j + 40] = 0;
                            g_3ad0[j + 40] = 0;
                            g_3974[j + 40] = 0;
                            g_3a5c[j + 40] = 0;
                        }
                    }
                    break;
                }
        }
        for (i = n; i < 8; i++)
            fn_10_1eb6(i);
    }
    g_9316 = n - 1;
    g_92ec[g_9324] = g_9406[g_9324] = n;
    GlobalUnlock(g_9100[g_9324]);
    g_9100[g_9324] = GlobalReAlloc(g_9100[g_9324],
        (int32_t)(g_92ec[g_9324] < 1 ? 1 : g_92ec[g_9324]) * 0x70, GHND);
    g_1df8[g_9324] = (REC_70 *)GlobalLock(g_9100[g_9324]);
    if (arg == -1) {
        for (i = 0; i < n; i++) {
            if (a54[i] != 0) {
                for (j = 0; j < 10; j++) {
                    f58 = 1;
                    for (m = 0; m <= s1c; m++)
                        if (a9c[m] == j && a42[m] != 0)
                            f58 = 0;
                    for (m = 0; m < i; m++)
                        if (g_7090[m].f_04e == j)
                            f58 = 0;
                    if (f58) {
                        g_7090[i].f_04e = j;
                        break;
                    }
                }
            } else if (i != main_ship) {
                for (m = 0; m <= s1c; m++)
                    if (a86[m] == g_7090[i].f_0d6) {
                        g_7090[i].f_04e = a9c[m];
                        break;
                    }
            }
            fn_14_1430(i);
        }
        g_95b0 = 0;
    } else {
        g_7090[g_9316].f_04e = g_9316;
        fn_14_1430(g_9316);
        g_95b0 = g_9316;
    }
    for (i = g_95b0; i <= g_9316; i++) {
        g_7090[i].f_050 = i;
        g_96d2[i].f_3a = i;
        if (a54[i] != 0 || g_91f8 == 1 || arg != -1)
            fn_16_3784(i, 1);
        SelectObject(g_39e8[i + 40], g_3974[i + 40]);
        GetObject(g_3ad0[i + 40], sizeof(BITMAP), &bm);
        SelectObject(g_39e8[i + 40], g_3ad0[i + 40]);
        if (g_7090[i].f_0d6 != -1) {
            g_96d2[g_7090[i].f_04e].f_2a = w = g_6e24[g_7090[i].f_0d6].f_7a;
            h = g_6e24[g_7090[i].f_0d6].f_7b;
        } else {
            g_96d2[g_7090[i].f_04e].f_2a = w = g_1df8[g_9324][i].f_22;
            h = g_1df8[g_9324][i].f_24;
        }
        if (g_9156 == 0 && (w & 1)) {
            w++;
            h = 4;
        }
        g_1df8[g_9324][i].f_22 = SC(w);
        g_1df8[g_9324][i].f_24 = SC(h);
        d26 = (int16_t)(bm.bmHeight - g_1df8[g_9324][i].f_24)
            / (int16_t)(g_1df8[g_9324][i].f_22 + g_1df8[g_9324][i].f_24);
        g_1df8[g_9324][i].f_20 = w << 3;
        g_7090[i].f_05b = d26 - 1;
        g_96d2[g_7090[i].f_04e].f_02 = g_96d2[g_7090[i].f_04e].f_00 = w / 2;
        if (g_96d2[g_7090[i].f_04e].f_04 < 0)
            g_96d2[g_7090[i].f_04e].f_04 = 4 - g_96d2[g_7090[i].f_04e].f_04 - w / 2;
        lstrcpy(buf, "");
        fn_10_5d3c(i);
        if (g_92e4 && g_7090[i].f_0e4 && g_96d2[g_7090[i].f_04e].f_28 == 3) {
            if (g_7090[i].f_0ac == 0)
                fn_08_2cd8(i, 0);
            if (g_7090[i].f_0ad == 0)
                fn_08_2cd8(i, 1);
        }
        fn_10_1460(g_7090[i].f_04e);
        fn_10_1620(g_7090[i].f_04e);
        fn_10_1502(g_7090[i].f_04e);
    }
    if (arg == -1)
        for (i = 0; i <= 27; i++)
            fn_10_546e(i);
    g_9346 = -1;
    g_0994 = g_95b0 = 0;
}

/* Pick a ship record (index into DS:6e20) for a new object of kind t;
 * the score goes to g_95b4 [inferred]. Quirks kept: u10 is read but never
 * set, bk may be unset, and a failed search returns 1, not -1. */
/* 14:2300 */
int16_t fn_14_2300(int16_t t, int16_t n)
{
    int16_t u4, k, res, i, uc, v, u10, r, best, bk, v18, lvl, c1c, c2, c0, c1, s24, s26, j;
    char main[20], ship1[20], ship2[20];

    k = rand() % (int16_t)(g_95aa - 1);
    res = -1;
    best = -1000;
    if (g_931c > g_931a)
        g_931c = 0;
    if ((g_9320 == 6 || g_9320 == 7) && g_90f8 && g_8e5e) {
        GetPrivateProfileString(g_9690, "Ship1", "", ship1, 20, g_96a9);
        if (ship1[0] == 0)
            fn_14_31d0(0, ship1);
        GetPrivateProfileString(g_9690, "Ship2", "", ship2, 20, g_96a9);
    }
    if (g_9516 == 0) {
        GetPrivateProfileString(g_9690, "MainShip", "EAGLE", main, 20, g_96a9);
        for (i = 0; i < g_95aa; i++)
            if (lstrcmp(g_6e20[i].f_0a, main) == 0 && !fn_14_455c(i)) {
                lstrcpy(main, "TRANSFORMER");
                WritePrivateProfileString(g_9690, "MainShip", main, g_96a9);
            }
    } else
        fn_14_31d0(0, main);
    for (k = 0; k < g_95aa; k++) {
        if (g_6e20[k].f_0a[0] == 0)
            r = -1000;
        else if (!fn_14_455c(k))
            r = -1000;
        else if (n == 0 && (g_9320 == 6 || g_9320 == 7) && g_90f8 && g_8e5e
                 && lstrcmp(g_6e20[k].f_0a, ship1) == 0) {
            bk = k;
            best = 20000;
            break;
        } else if (n == 1 && (g_9320 == 6 || g_9320 == 7) && g_90f8 && g_8e5e
                   && lstrcmp(g_6e20[k].f_0a, ship2) == 0) {
            bk = k;
            best = 20000;
            break;
        } else if (t == 0 && lstrcmp(g_6e20[k].f_0a, main) == 0
                   && (!g_90f8 || !g_8e5e || g_9320 != 6 && g_9320 != 7)) {
            bk = k;
            best = 20000;
            break;
        } else if (t == 2 && g_6e20[k].f_03 == 7 && g_6e20[k].f_04[1] > 1) {
            if (g_9332 < 2 || g_964a > 7) {
                if (g_6e20[k].f_04[1] == 2)
                    r = 100;
                else
                    r = 20;
            } else if (g_6e20[k].f_04[1] == 3)
                r = 50;
            else
                r = 20;
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (t == 3 && g_6e20[k].f_03 == 7 && g_6e20[k].f_04[1] == 1) {
            r = rand() % 30 + 50;
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (t == 5 && g_6e20[k].f_03 == 7 && g_6e20[k].f_04[1] == 0) {
            r = rand() % 30 + 50;
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (g_9320 == 6 && n != main_ship && g_6e20[k].f_03 != 7 && t == 4) {
            int16_t u66, a68, a6a, u6c, u6e, me, a72, a74;
            int32_t L78;

            r = 0;
            me = g_6e24[g_931c].f_00;
            u6c = g_6e20[me].f_01 * 5;
            a6a = (int16_t)((u6c * 2 - g_6e1c[g_6e20[me].f_21].f_1c) * 10)
                / ((int16_t)((int32_t)(g_6e1c[g_6e20[me].f_21].f_1b * 10)
                         * (g_6e20[me].f_02 / 4 + 100L) / 100L)
                   + g_6e20[me].f_00 * 2);
            a72 = (int32_t)u6c * 345 / g_6e1c[g_6e20[me].f_21].f_1c;
            a72 = a72 < 1 ? 1 : a72;
            u66 = g_6e20[k].f_00 * 2;
            L78 = (int32_t)(g_6e1c[g_6e20[k].f_21].f_1b * 10)
                * (g_6e20[k].f_02 / 4 + 100L) / 100L;
            u6c = g_6e20[k].f_01 * 5;
            u6e = g_6e1c[g_6e20[k].f_21].f_1c;
            a68 = (int16_t)((u6c * 2 - u6e) * 10) / (int16_t)((int16_t)L78 + u66);
            a74 = (int32_t)u6c * 345 / u6e;
            a74 = a74 < 1 ? 1 : a74;
            switch (g_94aa) {
            case 0:
                r = rand() % 100 + a68 * 10 + a74 / 100;
                break;
            case 1:
                a6a = (int16_t)(a6a * 5) / 4;
                a72 = (int16_t)(a72 * 5) / 4;
            case 2:
                r = rand() % 150 - (int16_t)abs32((int32_t)(int16_t)(a6a - a68) * 500 / a6a) + 500;
                r += 400 - (int16_t)abs32((int32_t)(int16_t)(a72 - a74) * 400 / a72);
                break;
            case 3:
                if (me == k)
                    r = 900;
                break;
            case 4:
                a6a = (int16_t)(a6a * 3) / 4;
                a72 = (int16_t)(a72 * 3) / 4;
                r = rand() % 150 - (int16_t)abs32((int32_t)(int16_t)(a6a - a68) * 500 / a6a) + 500;
                r += 400 - (int16_t)abs32((int32_t)(int16_t)(a72 - a74) * 400 / a72);
                break;
            case 5:
                r = rand() % 100 + (100 - a68) * 10 - a74 / 100;
                break;
            }
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (g_9320 == 7 && n != main_ship && g_6e20[k].f_03 != 7) {
            int16_t u8a, a86, a82, u7e, u7c, me, a74, a72;
            int32_t L8e, L92, L96;

            r = 0;
            me = g_6e24[g_931c].f_00;
            u7e = g_6e20[me].f_01 * 5;
            u7c = g_6e1c[g_6e20[me].f_21].f_1c;
            /* The clamps are written as `x = X < 1 ? 1 : X` (CL evaluates X
             * once); u7e/u7c serve the own ship here and candidate k below,
             * which lets CL drop these first stores. */
            a82 = (int16_t)((u7e * 2 - u7c) * 10)
                / ((int16_t)((int32_t)(g_6e1c[g_6e20[me].f_21].f_1b * 10)
                         * (g_6e20[me].f_02 / 4 + 100L) / 100L)
                   + g_6e20[me].f_00 * 2) < 1 ? 1
                : (int16_t)((u7e * 2 - u7c) * 10)
                / ((int16_t)((int32_t)(g_6e1c[g_6e20[me].f_21].f_1b * 10)
                         * (g_6e20[me].f_02 / 4 + 100L) / 100L)
                   + g_6e20[me].f_00 * 2);
            a74 = (int32_t)u7e * 345 / u7c;
            a74 = a74 < 1 ? 1 : a74;
            L96 = (int32_t)(g_6e1c[g_6e20[me].f_21].f_1b * 10) * (g_6e20[me].f_02 / 4 + 100L)
                / 100L * g_6e20[me].f_02 / 360 < 1 ? 1
                : (int32_t)(g_6e1c[g_6e20[me].f_21].f_1b * 10) * (g_6e20[me].f_02 / 4 + 100L)
                / 100L * g_6e20[me].f_02 / 360;
            u8a = g_6e20[k].f_00 * 2;
            L8e = (int32_t)(g_6e1c[g_6e20[k].f_21].f_1b * 10) * (g_6e20[k].f_02 / 4 + 100L) / 100L;
            u7e = g_6e20[k].f_01 * 5;
            u7c = g_6e1c[g_6e20[k].f_21].f_1c;
            a86 = (int16_t)((u7e * 2 - u7c) * 10) / (int16_t)((int16_t)L8e + u8a) < 1 ? 1
                : (int16_t)((u7e * 2 - u7c) * 10) / (int16_t)((int16_t)L8e + u8a);
            a72 = (int32_t)u7e * 345 / u7c;
            a72 = a72 < 1 ? 1 : a72;
            L92 = (int32_t)(g_6e1c[g_6e20[k].f_21].f_1b * 10) * (g_6e20[k].f_02 / 4 + 100L) / 100L * g_6e20[k].f_02 / 360;
            L92 = L92 < 1 ? 1 : L92;
            switch (g_94aa) {
            case 0:
                r = rand() % 230 + ((int16_t)L92 + a86) * 10 + a72 / 100;
                break;
            case 1:
                a82 = (int16_t)(a82 * 6) / 4;
                a74 = (int16_t)(a74 * 6) / 4;
                L96 = L96 * 6 / 4;
            case 2:
                r = rand() % 150 - (int16_t)abs32((int32_t)(int16_t)(a82 - a86) * 300 / a82) + 300;
                r += 200 - (int16_t)abs32((int32_t)(int16_t)(a74 - a72) * 200 / a74);
                r += 700 - (int16_t)abs32((L96 - L92) * 700 / L96);
                break;
            case 3:
                if (me == k)
                    r = 900;
                break;
            case 4:
                a82 = (int16_t)(a82 * 2) / 3;
                a74 = (int16_t)(a74 * 2) / 3;
                L96 = L96 * 2 / 3;
                r = rand() % 150 - (int16_t)abs32((int32_t)(int16_t)(a82 - a86) * 300 / a82) + 300;
                r += 200 - (int16_t)abs32((int32_t)(int16_t)(a74 - a72) * 200 / a74);
                r += 700 - (int16_t)abs32((L96 - L92) * 700 / L96);
                break;
            case 5:
                r = rand() % 200 + (100 - (int16_t)L92 - a86) * 10 - a72 / 100;
                break;
            }
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (t == 1 && g_6e20[k].f_03 == g_96d2[g_7090[main_ship].f_04e].f_38) {
            r = 0;
            lvl = fn_14_40d8(k);
            v = g_6e20[k].f_04[1];
            if (v == g_9332)
                r = 52;
            if ((int16_t)(v - g_9332) == -1 || (int16_t)(v - g_9332) == 1)
                r += 30;
            r += 10;
            if (lvl == g_9334)
                r += 25;
            else if ((int16_t)(g_9334 + 1) < lvl)
                r += (g_9334 - lvl) * 32;
            if (lvl < g_9334)
                r += (lvl - g_9334) * 18;
            r += rand() % 30;
            for (i = 0; i < n; i++)
                if (g_7090[i].f_0d6 >= 0 && g_6e24[g_7090[i].f_0d6].f_00 == k)
                    r -= 25;
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (t == 4 && g_6e20[k].f_03 != g_96d2[g_7090[main_ship].f_04e].f_38
                   && g_6e20[k].f_03 != 7) {
            lvl = fn_14_40d8(k);
            v = g_6e20[k].f_04[1];
            v18 = g_3824[g_96d2[g_7090[main_ship].f_04e].f_38][g_6e20[k].f_03];
            r = 0;
            if (v == g_9332)
                r = 75;
            if ((int16_t)(v - g_9332) == -1 || (int16_t)(v - g_9332) == 1)
                r += 42;
            if (lvl == g_9334)
                r += 25;
            else if ((int16_t)(g_9334 + 1) < lvl)
                r += (g_9334 - lvl) * 16;
            if (lvl < g_9334)
                r += (lvl - g_9334) * 11;
            if (g_9332 < 2 && v18 < -150)
                r += 15;
            if (g_9332 > 2 && g_6e20[k].f_03 == 2)
                r += 30;
            c1c = 0;
            if ((g_6e20[k].f_03 == 3 || g_6e20[k].f_03 == 6 || g_6e20[k].f_03 == 1)
                && g_9432 > 300)
                r += g_9432 / 20 < 30 ? 30 : g_9432 / 20;
            if (g_6e20[k].f_03 == 3 && g_7090[main_ship].f_0ce > (int16_t)((g_9208 + 4) * 100))
                r += g_7090[main_ship].f_0ce / 20 > 40 ? 40 : g_7090[main_ship].f_0ce / 20;
            for (i = s24 = s26 = 0; i <= g_931a; i++)
                if (g_6e24[i].f_79 + 15 > g_91f8
                    && g_6e24[i].f_64 != g_6e24[g_931c].f_64) {
                    if (g_6e20[k].f_03 == g_6e24[i].f_64) {
                        s24 += g_6e24[i].f_77;
                        if (g_6e24[i].f_00 == k)
                            s24 += g_6e24[i].f_77 * 3;
                    }
                    s26 += g_6e24[i].f_77;
                }
            r += 40 - (int16_t)((int32_t)(int16_t)(s26 + 85) * s24 / (int16_t)(s26 + 1));
            for (j = 0; j < g_0994; j++)
                if (g_4f1c[j] <= 0 && g_4f1c[j] == -g_6e20[k].f_03
                    || g_4f1c[j] == -100 && g_6e20[k].f_03 == 3) {
                    r += 2000;
                    g_4f1c[j] = -120;
                }
            if (g_6e20[k].f_03 == 3 && g_95b6 != 3)
                r -= 500;
            if (g_6e20[k].f_03 == g_95b6) {
                r += 1000;
                if ((int16_t)(g_9334 + 2) < lvl)
                    r += 150;
                if (g_95b6 == 4 && u10 < 2)
                    r += 300;
                if (g_95b6 == 3 && v < 2)
                    r += 300;
                r += rand() % 80;
            }
            r += rand() % 30;
            for (i = c2 = c0 = c1 = 0; i < n; i++)
                if (g_7090[i].f_0d6 >= 0) {
                    if (g_6e24[g_7090[i].f_0d6].f_00 == k)
                        r -= 45;
                    else if (g_6e24[g_7090[i].f_0d6].f_64 == g_6e20[k].f_03)
                        r += 24;
                    if (g_6e24[g_7090[i].f_0d6].f_64 == 2)
                        c2++;
                    if (g_6e24[g_7090[i].f_0d6].f_64 == 0)
                        c0++;
                    if (g_6e24[g_7090[i].f_0d6].f_64 == 1)
                        c1++;
                }
            if (c0 == 0 && c2 != 0 && g_6e20[k].f_03 == 0)
                r += 25;
            if (c0 != 0 && c2 == 0 && g_6e20[k].f_03 == 2)
                r += 25;
            if (c1 == 0 && c2 != 0 && g_6e20[k].f_03 == 1)
                r += 25;
            if (c1 != 0 && c2 == 0 && g_6e20[k].f_03 == 2)
                r += 25;
            if (r > best) {
                bk = k;
                best = r;
            }
        }
    }
    k = bk;
    g_95b4 = best;
    if (best <= -1000)
        k = 1;
    if ((t == 4 || t == 1) && (int16_t)(g_0992 + 30) > g_932a && g_95b6 == -1 && best < 1000)
        g_95b4 = -1;
    return k;
}

/* Pick a pilot record (index into DS:6e24) for a new object of kind t;
 * returns -1 if none, the score in g_95b2 [inferred]. */
/* 14:3274 */
int16_t fn_14_3274(int16_t t, int16_t n)
{
    int16_t u4, k, u8, m, uc, ue, u10, r, best, bk, v18, lvl, c2, c0, c1, s22, s24, j;
    int32_t L2a, L2e, L32;
    int16_t u34;
    int16_t a36, a38, u3a, u3c, me, a40, a42;
    int32_t L46;                           /* never read; see below */

    k = rand() % (int16_t)(g_95aa - 1);
    best = -1000;
    if (g_9320 == 6) {
        g_95b2 = -10000;
        return 0;
    }
    for (k = 0; k <= g_931a; k++) {
        for (m = 0; m < n; m++)
            if (g_7090[m].f_0d6 == k)
                r = -888;
        /* r keeps its value into the next pass (the -888 test above) */
        if (k == g_931c || g_6e24[k].f_38[0] <= 0 || r == -888)
            r = -1000;
        else if (!fn_14_455c(g_6e24[k].f_00))
            r = -1000;
        else if (g_9320 == 6 && n != main_ship && g_6e20[g_6e24[k].f_00].f_03 != 7) {
            r = 0;
            me = g_6e24[g_931c].f_00;
            u3a = g_6e20[me].f_01 * 5;          /* rating of own ship [inferred] */
            a38 = (int16_t)((u3a * 2 - g_6e1c[g_6e20[me].f_21].f_1c) * 10)
                / ((int16_t)((int32_t)(g_6e1c[g_6e20[me].f_21].f_1b * 10)
                         * (g_6e20[me].f_02 / 4 + 100L) / 100L)
                   + g_6e20[me].f_00 * 2);
            a40 = (int32_t)u3a * 345 / g_6e1c[g_6e20[me].f_21].f_1c;
            /* Same rating for candidate k. The split into u3c/u10/uc, the
             * dead store to L46 and `u10 += u3c` reproduce the original's
             * evaluation order and registers [layout-only]. */
            u3c = g_6e20[g_6e24[k].f_00].f_00 * 2;
            u10 = (int16_t)(L46 = (int32_t)(g_6e1c[g_6e20[g_6e24[k].f_00].f_21].f_1b * 10)
                                  * (g_6e20[g_6e24[k].f_00].f_02 / 4 + 100L) / 100L);
            u3a = g_6e20[g_6e24[k].f_00].f_01 * 5;
            uc = g_6e1c[g_6e20[g_6e24[k].f_00].f_21].f_1c;
            a36 = (int16_t)((u3a * 2 - uc) * 10) / (u10 += u3c);
            a42 = (int32_t)u3a * 345 / uc;
            switch (g_94aa) {
            case 0:
                r = rand() % 100 + a36 * 10 + a42 / 100;
                break;
            case 1:
                a38 = (int16_t)(a38 * 5) / 4;
                a40 = (int16_t)(a40 * 5) / 4;
            case 2:
                r = rand() % 150 - (int16_t)abs32((int32_t)(int16_t)(a38 - a36) * 500 / a38) + 450;
                r += 350 - (int16_t)abs32((int32_t)(int16_t)(a40 - a42) * 400 / a40);
                break;
            case 3:
                if (me == k)
                    r = 800;
                break;
            case 4:
                a38 = (int16_t)(a38 * 3) / 4;
                a40 = (int16_t)(a40 * 3) / 4;
                r = rand() % 150 - (int16_t)abs32((int32_t)(int16_t)(a38 - a36) * 500 / a38) + 450;
                r += 350 - (int16_t)abs32((int32_t)(int16_t)(a40 - a42) * 400 / a40);
                break;
            case 5:
                r = rand() % 100 + (90 - a36) * 10 - a42 / 100;
                break;
            }
            r += 100 - (int16_t)abs32((int32_t)(g_6e24[g_931c].f_38[2] - g_6e24[k].f_38[2]) * 200
                                 / g_6e24[g_931c].f_38[2]);
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (g_9320 == 7 && n == 1 && k == g_93b6) {
            bk = k;
            best = 30000;
        } else if (t == 1 && g_6e24[k].f_64 == g_6e24[g_931c].f_64) {
            r = -10;
            lvl = g_6e24[k].f_76;
            ue = g_6e20[g_6e24[k].f_00].f_04[1];
            if (ue == g_9332)
                r = 42;
            if ((int16_t)(ue - g_9332) == -1 || (int16_t)(ue - g_9332) == 1)
                r += 30;
            if (lvl == g_9334)
                r += 30;
            else if ((int16_t)(g_9334 + 1) < lvl)
                r += (g_9334 - lvl) * 28;
            if (lvl < g_9334)
                r += (lvl - g_9334) * 16;
            L32 = g_6e24[k].f_06;
            if (g_6e24[k].f_79 >= (int16_t)(g_91f8 - 1)) {
                L2a = g_6e24[k].f_78 + 1;
                L32 = L32 * (L2a * L2a * 32 / -9 + (L2a << 5) / 2 + 32) / 32;
                if (L32 < 0)
                    L32 = 0;
            } else if (g_6e24[k].f_78 != -1) {
                L2e = (int16_t)(g_91f8 - g_6e24[k].f_79 - 1);
                L2a = g_6e24[k].f_78 + 1 < 4 ? 4 : g_6e24[k].f_78 + 1;
                if (L2e <= L2a / 2)
                    L32 = 0;
                else if (L2a != 0)
                    L32 = min(L32 * ((L2e << 6) / L2a - 32) / 32, L32 * 5 / 4);
            }
            r += (int16_t)(L32 / 9) + g_6e24[k].f_3c[g_931c] * 2;
            if (g_6e24[k].f_64 == g_95b6)
                r += 1000;
            r += rand() % 30;
            if (r > best) {
                bk = k;
                best = r;
            }
        } else if (t == 4 && g_6e24[k].f_64 != g_6e24[g_931c].f_64
                   && g_6e24[k].f_64 != 7) {
            lvl = g_6e24[k].f_76;
            v18 = g_6e24[k].f_3c[g_931c] * 10
                + g_3824[g_96d2[g_7090[main_ship].f_04e].f_38][g_6e24[k].f_64];
            r = -10;
            ue = g_6e20[g_6e24[k].f_00].f_04[1];
            if (ue == g_9332)
                r = 65;
            if ((int16_t)(ue - g_9332) == -1 || (int16_t)(ue - g_9332) == 1)
                r += 50;
            if (lvl == g_9334)
                r += 25;
            else if ((int16_t)(g_9334 + 1) < lvl)
                r += (g_9334 - lvl) * 16;
            if (lvl < g_9334)
                r += (lvl - g_9334) * 11;
            if (g_9332 < 2 && v18 < -150)
                r += 20;
            if (g_9332 > 2 && g_6e24[k].f_64 == 2)
                r += 25;
            if (g_9332 > 1 && g_6e24[k].f_64 == 4)
                r += 10;
            if ((g_6e24[k].f_64 == 3 || g_6e24[k].f_64 == 6 || g_6e24[k].f_64 == 1)
                && g_9432 > 300)
                r += g_9432 / 17 < 50 ? 50 : g_9432 / 17;
            L32 = g_6e24[k].f_06;
            if (g_6e24[k].f_79 >= (int16_t)(g_91f8 - 1)) {
                L2a = g_6e24[k].f_78 + 1;
                L32 = L32 * (L2a * L2a * 32 / -9 + (L2a << 5) / 2 + 32) / 32;
                if (L32 < 0)
                    L32 = 0;
            } else if (g_6e24[k].f_78 != 0) {
                L2e = (int16_t)(g_91f8 - g_6e24[k].f_79 - 1);
                L2a = g_6e24[k].f_78 + 1 < 4 ? 4 : g_6e24[k].f_78 + 1;
                if (L2e <= L2a / 2)
                    L32 = 0;
                else if (L2a != 0)
                    L32 = min(L32 * ((L2e << 6) / L2a - 32) / 32, L32 * 5 / 4);
            }
            r += (int16_t)(L32 / 10 > 60 ? 60 : L32 / 10) + fn_09_88ba(g_6e24[k].f_3c[g_931c]);
            for (j = 0; j < g_0994; j++)
                if (g_4f1c[j] <= 0 && g_4f1c[j] == -g_6e24[k].f_64
                    || g_4f1c[j] == -100 && g_6e24[k].f_64 == 3
                    || g_4f1c[j] == k) {
                    r += 2000;
                    g_4f1c[j] = -120;
                }
            if (g_6e24[k].f_64 == 3)
                r -= 500;
            for (m = s22 = s24 = 0; m <= g_931a; m++)
                if (g_6e24[m].f_79 + 15 > g_91f8
                    && g_6e24[m].f_64 != g_6e24[g_931c].f_64) {
                    if (g_6e24[m].f_64 == g_6e24[k].f_64)
                        s22 += g_6e24[m].f_77;
                    s24 += g_6e24[m].f_77;
                }
            r += 40 - (int16_t)((int32_t)(int16_t)(s24 + 85) * s22 / (int16_t)(s24 + 1));
            for (m = c2 = c0 = c1 = 0; m < n; m++)
                if (g_7090[m].f_0d6 >= 0) {
                    if (g_6e24[g_7090[m].f_0d6].f_64 == g_6e24[k].f_64)
                        r += 24;
                    if (g_6e24[g_7090[m].f_0d6].f_64 == 2)
                        c2++;
                    if (g_6e24[g_7090[m].f_0d6].f_64 == 0)
                        c0++;
                    if (g_6e24[g_7090[m].f_0d6].f_64 == 1)
                        c1++;
                }
            if (c0 == 0 && c2 != 0 && g_6e20[g_6e24[k].f_00].f_03 == 0)
                r += 25;
            if (c0 != 0 && c2 == 0 && g_6e20[g_6e24[k].f_00].f_03 == 2)
                r += 25;
            if (c1 == 0 && c2 != 0 && g_6e20[g_6e24[k].f_00].f_03 == 1)
                r += 25;
            if (c1 != 0 && c2 == 0 && g_6e20[g_6e24[k].f_00].f_03 == 2)
                r += 25;
            r += rand() % 40;
            if (r > best) {
                bk = k;
                best = r;
            }
        }
    }
    if (best > -1000)
        k = bk;
    else
        k = -1;
    g_95b2 = best;
    return k;
}
