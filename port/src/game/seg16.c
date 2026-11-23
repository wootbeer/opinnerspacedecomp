/* INSPACE.EXE segment 16 (selector 1078). */
#include "game.h"

/* Parses a number from a short digit string [inferred]. */
/* near-match 82%: 16:0000 (game: sub 0x30; mov cx,1000; imul cx for the
 * thousands digit and r kept in si until one store; here CL folds (d-48)*1000
 * into imul+add 0x4480 and stores r early. Never-read locals u1/u2 stop the
 * Horner refactoring of the other terms. Round 6: the game's thousands form
 * comes from a long multiply, `(long)(s[k] - 48) * 1000` assigned to a long
 * `struct { long v; } r` (frame 0xa, only the low word stored), but then CL keeps
 * r in registers instead of the single [bp-6] store; best such variant 66%.) */
int16_t fn_16_0000(LPSTR s)
{
    int16_t u0;
    int16_t r;
    int16_t k;
    int16_t u1, u2;

    k = 0;
    if (s[0] == ' ' || s[0] == 'a') {
        k = 1;
        if (s[1] == ' ' || s[1] == 'a')
            k = 2;
    }
    if (s[k + 1] == '.') {
        r = (u1 = (s[k + 2] - 48) * 10) + (u2 = (s[k] - 48) * 100);
    } else {
        r = (s[k] - 48) * 1000;
lab:    r += (u1 = (s[k + 3] - 48) * 10) + (u2 = (s[k + 1] - 48) * 100);
    }
    return r;
}

/* 16:00a2 */
void fn_16_00a2(void)
{
    int16_t i;
    int16_t idx;
    int16_t u1;
    int16_t u2;
    int16_t u3;
    int16_t s22;
    int16_t s24;
    int16_t seg;
    int16_t obj;
    WORD r;
    int16_t a;
    int16_t b;
    int16_t d;
    POINT dd;
    POINT v;

    s22 = g_1df8[7]->f_22;
    s24 = g_1df8[7]->f_24;
    g_9e51++;
    if (g_9e51 > 7)
        g_9e51 = 0;
    if (g_9e49 >= 1 && g_9e49 < 6)
        g_111e = 1;
    else
        g_111e = 0;
    if (g_9e49 == 0)
        VIEWP(int16_t *, g_9e41.f_00, 0)[3] = 0;
    if (VIEWP(int16_t *, g_9e41.f_00, 0)[3] && g_1df8[7]->f_2e == 0) {
        VIEWP(int16_t *, g_9e41.f_00, 0)[2] = min(VIEWP(int16_t *, g_9e41.f_00, 0)[3] / 5, 3) + 10;
        VIEWP(int16_t *, g_9e41.f_00, 0)[3] += VIEWP(int16_t *, g_9e41.f_00, 0)[0];
        if (VIEWP(int16_t *, g_9e41.f_00, 0)[3] > 15) {
            VIEWP(int16_t *, g_9e41.f_00, 0)[0] = 0;
            VIEWP(int16_t *, g_9e41.f_00, 0)[3] = 15;
        } else if (VIEWP(int16_t *, g_9e41.f_00, 0)[3] <= 0) {
            VIEWP(int16_t *, g_9e41.f_00, 0)[3] = VIEWP(int16_t *, g_9e41.f_00, 0)[0] = 0;
            if (g_9e49 == 8) {
                g_9e49 = 9;
                g_1df8[g_9324][g_952e].f_54 = 0;
                g_1df8[7]->f_54 = 0;
            }
        }
    } else {
        if (g_9e49 == 4)
            VIEWP(int16_t *, g_9e41.f_00, 0)[1] = 50;
        if (VIEWP(int16_t *, g_9e41.f_00, 0)[1] < 99)
            VIEWP(int16_t *, g_9e41.f_00, 0)[2] = VIEWP(int16_t *, g_9e41.f_00, 0)[1] / 10;
        else
            VIEWP(int16_t *, g_9e41.f_00, 0)[2] = 0;
    }
    if ((g_9e49 != 3 && (g_9e49 != 6 || VIEWP(int16_t *, g_9e41.f_00, 0)[3] != 15)) || g_1df8[7]->f_2e != 0) {
        g_1df8[7]->f_10 = (s24 + s22) * VIEWP(int16_t *, g_9e41.f_00, 0)[2] + s24;
        fn_08_0b76(0x700, 1, g_39f2, 0);
    }
    g_9e4f = g_1df8[7]->f_0c / 8;
    if (g_9e4f == 0)
        g_9e4f = 1;
    else if (g_9e4f > 7)
        g_9e4f = 7;
    VIEWP(int16_t *, g_9e41.f_00, 0)[1] += g_9e4f;
    if (VIEWP(int16_t *, g_9e41.f_00, 0)[1] > 130)
        VIEWP(int16_t *, g_9e41.f_00, 0)[1] = 0;
    else if (VIEWP(int16_t *, g_9e41.f_00, 0)[1] < 0)
        VIEWP(int16_t *, g_9e41.f_00, 0)[1] = 130;
    if (g_9e49 != 9 && g_952e >= 0
        && (g_1df8[g_9324][g_952e].f_18 != 0 || g_1df8[g_9324][g_952e].f_2e == 1)) {
        VIEWP(int16_t *, g_9e41.f_00, 0)[4] = 9;     /* g_9e49, g_9e4b: one dword store */
        VIEWP(int16_t *, g_9e41.f_00, 0)[5] = 1200;
    }
    switch (g_9e49) {
    case 0:
        if (g_9e4b < 120) {
            g_1df8[7]->f_0c /= 3;
            g_1df8[7]->f_0e /= 3;
            if (fn_09_88ba(g_1df8[7]->f_0c) < 10 && fn_09_88ba(g_1df8[7]->f_0e) < 10) {
                g_1df8[7]->f_0e = 0;
                g_1df8[7]->f_0c = g_1df8[7]->f_0e;
                g_1df8[g_9324][g_952e].f_54 = 1;
                g_1df8[7]->f_44 = 100;
                VIEWP(int16_t *, g_9e41.f_00, 0)[2] = 5;
                g_9e4f = 0;
                g_9e49 = 1;
                g_1c42 = -1;
            }
        }
        if (g_9e4b < 250 && VIEWP(int16_t *, g_9e41.f_00, 0)[2] == 5)
            g_9e4f = 0;
        break;
    case 1:
        if (VIEWP(int16_t *, g_9e41.f_00, 0)[2] == 5)
            g_9e4f = 0;
        g_111e = 1;
        fn_11_6874(g_952e);
        g_1df8[g_9324][g_952e].f_0e = 0;
        g_1df8[g_9324][g_952e].f_0c = g_1df8[g_9324][g_952e].f_0e;
        if (g_9e51 == 0 || g_9e51 == 4) {
            if (g_7090[g_952e].flag) {
                g_1c42 = g_1df8[g_9324][g_952e].f_28;
                g_1df8[g_9324][g_952e].f_28 = steer_toward_direction(
                    g_1df8[g_9324][g_952e].f_04.y, g_1df8[g_9324][g_952e].f_04.x,
                    g_1df8[7]->f_04.y, g_1df8[7]->f_04.x, g_1df8[g_9324][g_952e].f_28,
                    2, g_952e, -1, -1, 0);
            }
            if ((g_1df8[g_9324][g_952e].f_28 == g_1c42 || !g_7090[g_952e].flag)
                && VIEWP(int16_t *, g_9e41.f_00, 0)[3] == 0) {
                g_9e4f = 0;
                VIEWP(int16_t *, g_9e41.f_00, 0)[1] = 50;
                VIEWP(int16_t *, g_9e41.f_00, 0)[2] = 5;
                VIEWP(int16_t *, g_9e41.f_00, 0)[0] = VIEWP(int16_t *, g_9e41.f_00, 0)[3] = 1;
                g_9e5b = g_7090[g_952e].flag;
                g_7090[g_952e].flag = g_7090[g_952e].f_147 = 1;
                if (g_952e == main_ship)
                    g_1e80 = g_1e84 = 0;
                fn_10_754a(0x23, 7, 0, 1);
                g_6e10 = g_1e50 + 750;
                g_9e49 = 2;
                g_1df8[7]->f_54 = 1;
                g_959e = g_9156;
            }
        } else
            g_1c42 = g_1df8[g_9324][g_952e].f_28;
        break;
    case 2:
        if (g_6e10 < g_1e50) {
            fn_10_754a(0x2f, 7, 0, 1);
            g_6e10 = g_1e50 + 1300;
            g_9e49 = 3;
            g_9596 = 1;
            fn_12_2556(g_9324, g_952e);
            fn_12_2556(7, 0);
            g_9e53 = g_9e4b;
        }
        break;
    case 3:
    case 4:
        if (VIEWP(int16_t *, g_9e41.f_00, 0)[3] == 0 && g_6e10 < g_1e50) {
            if (g_1df8[7]->f_2e == 0) {
                fn_12_2556(7, 0);
                fn_07_13b2(1, 7, 0);
            }
            if (g_952e == main_ship)
                g_1e88 = g_1e50 + 1000;
            else
                g_1e88 = g_1e50 + 4000;
        }
        break;
    case 6:
        if (g_1df8[g_9324][g_952e].f_3c == 0)
            fn_12_2556(g_9324, g_952e);
        if (g_1df8[7]->f_3c == 0)
            fn_12_2556(7, 0);
        break;
    case 9:
        g_111e = 0;
        if ((g_1df8[7]->f_1a == 0 && g_9e4b < 200) || g_9e4b < 110)
            fn_16_08a0();
        break;
    }
    if (g_9e49 < 3 && g_9e4b > 140 && g_9e49 != 0) {
        VIEWP(int16_t *, g_9e41.f_00, 0)[0] = -1;
        VIEWP(int16_t *, g_9e41.f_00, 0)[1] = 50;
        VIEWP(int16_t *, g_9e41.f_00, 0)[2] = 5;
        g_9e49 = g_111e = 0;
    }
    seg = g_9324;
    obj = g_952e;
    if (g_9e49 == 9) {
        seg = 12;
        obj = 1;
    }
    switch (g_9e49) {
    case 0:
    case 9:
        if (g_9e4d == 0 && g_9e51 < 2) {
            idx = fn_08_2658(7, 0, seg, obj);
            v = VIEW(POINT, (*g_1df8[7]).f_0c, 0);
            dd.x = (g_1050[idx].x * 500 - v.x * 40) / g_1df8[7]->f_44;
            dd.y = (g_1050[idx].y * 500 - v.y * 40) / g_1df8[7]->f_44;
            g_1df8[7]->f_0c += dd.x;
            g_1df8[7]->f_0e += dd.y;
            if (g_9e49 == 0) {
                for (i = 0; i < g_9318; i++) {
                    d = fn_08_285a(&a, &b, g_1df8[12][i * 2 + 1].f_04, g_1df8[7]->f_04);
                    if (d < 150) {
                        g_1df8[7]->f_0c -= g_1050[idx].x * 3 / 4;
                        g_1df8[7]->f_0e -= g_1050[idx].y * 3 / 4;
                        g_1df8[7]->f_0c += (int16_t)(a * 42) / d;
                        g_1df8[7]->f_0e += (int16_t)(b * 42) / d;
                        g_1df8[7]->f_0c += (int16_t)(b * -25) / d;
                        g_1df8[7]->f_0e += (int16_t)(a * 25) / d;
                    }
                }
            }
        }
        g_9e4b = fn_08_285a(&a, &b, g_1df8[7]->f_04, g_1df8[seg][obj].f_04);
        break;
    case 1:
    case 2:
        g_9e4b = fn_08_285a(&a, &b, g_1df8[7]->f_04, g_1df8[seg][obj].f_04);
        break;
    }
    if (VIEWP(int16_t *, g_9e41.f_00, 0)[3] == 0)
        fn_08_1b54(0x700, 1);
    if (g_9e4d)
        g_9e4d--;
    if (g_1df8[7]->f_1a) {
        g_943a = 7;
        g_943c = 0;
        r = fn_08_50aa(0x700);
        if (r != 0xffff) {
            g_9e4d = 10;
            fn_08_5df2(7, 0, HIBYTE(r), LOBYTE(r),
                       fn_08_546c(r, &g_1df8[7]->f_0c, &g_1df8[7]->f_0e, g_1df8[7]->f_20 + 2, 800));
            fn_10_754a(8, 7, 0, 1);
        }
    }
}

/* 16:085e is the C runtime's ___ExportedStub (library code); kept for reference, not counted */
int16_t fn_16_085e(int16_t type, int16_t idx, int16_t amount)
{
    return 0;
}

/* 16:0872 */
void fn_16_0872(void)
{
    fn_16_3784(g_952e, 0);
    fn_03_06ec(g_952e, 7, 0, 0x54);
}

/* 16:08a0 */
void fn_16_08a0(void)
{
    fn_12_2556(7, 0);
    fn_07_13b2(1, 7, 0);
    VIEWP(int16_t *, g_9e41.f_00, 0)[4] = 10;
    g_952e = -1;
    g_111e = 0;
    g_6da8 = 0;
}

/* 16:64c8 */
int16_t fn_16_64c8(void)
{
    char buf[398];

    g_9530 = 3;
    if (g_90f4 == 1)
        fn_18_0378(1);
    else
        fn_18_0378(0);
    return 1;
}

/* 16:3e80 */
int16_t fn_16_3e80(int16_t i)
{
    int16_t d;

    d = (g_96d2[g_7090[i].f_04e].f_1e - g_7090[i].f_01e) / 7;
    if (g_92e4 == 0)
        g_7090[i].f_01e = g_96d2[g_7090[i].f_04e].f_1e;
    return d / 10 * 10;
}

/* Owner-draw item handler [inferred]. */
/* 16:5a8a */
void fn_16_5a8a(DRAWITEMSTRUCT *dis)
{
    RECT rc;

    CopyRect(&rc, &dis->rcItem);
    if (dis->itemID == 0xffff || (dis->itemState & ODS_FOCUS))
        DrawFocusRect(dis->hDC, &rc);
    else
        fn_16_5ada(dis);
}

/* 16:5ada */
void fn_16_5ada(DRAWITEMSTRUCT *dis)
{
    RECT rc;

    fn_16_590c(dis);
    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_FOCUS)
        DrawFocusRect(dis->hDC, &rc);
}

/* 16:614c */
void fn_16_614c(int16_t msg, int16_t b, int32_t c)
{
    if (g_9530 == 1) {
        if (msg == 0x9c5)
            msg = WM_LBUTTONDOWN;
        g_6da4->f_22 = msg;
        g_6da4->f_24 = b;
        g_6da4->f_26 = c;
        g_9530 = 5;
        fn_16_64fa();
    }
}

/* 16:68d6 */
void fn_16_68d6(HWND hwnd, int16_t id, int16_t id2)
{
    char buf[280];

    fn_09_955c(id, buf);
    if (id2 != -1)
        fn_09_9580(id2, buf);
    MessageBox(hwnd, buf, g_9690, MB_ICONEXCLAMATION);
}

/* 16:1f24 */
void fn_16_1f24(void)
{
    if (g_9590) {
        SelectObject(g_95a0, g_9592);
        if (g_9594)
            SelectPalette(g_95a0, g_9594, 0);
        DeleteDC(g_95a0);
        DeleteObject(g_9590);
        g_9590 = 0;
    }
}

/* 16:3730 */
int16_t fn_16_3730(int16_t i, int16_t j)
{
    int16_t t;

    if (g_7090[i].f_0ae[j] == -1)
        return 0;
    t = (20 - g_7090[i].f_0ae[j]) * 10;
    g_7090[i].f_0ae[j] = 20;
    g_7090[i].f_0ae[0] = -1;
    return t / 10 * 10;
}

/* 16:32a0 */
void fn_16_32a0(void)
{
    VIEWP(int16_t *, g_9e41.f_00, 0)[0] = -1;
    VIEWP(int16_t *, g_9e41.f_00, 0)[1] = 50;
    VIEWP(int16_t *, g_9e41.f_00, 0)[2] = 5;
    VIEWP(int16_t *, g_9e41.f_00, 0)[3] = 15;
    fn_16_0872();
    g_1df8[7]->f_18 = 0;
    if (g_1df8[7]->f_2e == -1) {
        fn_12_2556(7, 0);
        fn_07_13b2(2, 7, 0);
        VIEWP(int16_t *, g_9e41.f_00, 0)[0] = 1;
    }
    VIEWP(int16_t *, g_9e41.f_00, 0)[4] = 6;
    g_111e = 0;
}

/* Nonzero when string a ends with string b [inferred]. */
/* 16:5f0e */
int16_t fn_16_5f0e(LPSTR a, LPSTR b)
{
    int16_t k;
    int16_t i;
    int16_t j;

    i = lstrlen(a) - 1;
    j = lstrlen(b) - 1;
    for (k = 0; k < lstrlen(b); k++, i--, j--)
        if (a[i] != b[j])
            return 0;
    return 1;
}

/* 16:71a2 */
int16_t fn_16_71a2(int16_t i, int16_t j)
{
    int16_t k;
    int16_t r;

    r = g_7090[i].f_0b8[j];
    g_7090[i].f_0ae[j] = g_7090[i].f_0b8[j] = 0;
    for (k = j; k < 9; k++) {
        g_7090[i].f_0b8[k] = g_7090[i].f_0b8[k + 1];
        g_7090[i].f_0ae[k] = g_7090[i].f_0ae[k + 1];
    }
    g_7090[i].f_0ae[9] = g_7090[i].f_0b8[9] = 0;
    g_7090[i].cnt--;
    return r;
}

/* 16:631c */
void fn_16_631c(void)
{
    if (g_95a2) {
        g_9530 = 2;
        if (g_959a)
            fn_16_64fa();
        if (g_9588) {
            FreeLibrary(g_9588);
            g_9588 = 0;
        }
        if (g_6da4) {
            GlobalUnlock(g_95a2);
            g_6da4 = 0;
        }
        GlobalFree(g_95a2);
        g_95a2 = 0;
    }
    g_952c = 0;
}

/* 16:3306 */
void fn_16_3306(void)
{
    g_1df8[g_9324][g_952e].f_18 = 0;
    g_1df8[7]->f_18 = 0;
    g_6da8 = 0;
    fn_12_26a4(g_9324, g_952e);
    fn_12_2556(g_9324, g_952e);
    fn_11_2f8c();
    if (g_1df8[7]->f_2e == -1) {
        fn_12_2556(7, 0);
        fn_07_13b2(2, 7, 0);
        VIEWP(int16_t *, g_9e41.f_00, 0)[3] = VIEWP(int16_t *, g_9e41.f_00, 0)[0] = 1;
        g_1df8[7]->f_44 = 800;
    }
    VIEWP(int16_t *, g_9e41.f_00, 0)[4] = 6;
}

/* 16:3f88 */
int16_t fn_16_3f88(int16_t i)
{
    int16_t a;
    int16_t b;
    int16_t c;

    for (a = 24; a <= 25; a++) {
        for (b = 1; b < g_7090[main_ship].cnt; b++) {
            if (g_7090[main_ship].f_0b8[b] == a) {
                g_7090[main_ship].f_0ae[b] = g_7090[main_ship].f_0b8[b] = 0;
                for (c = b; c < 9; c++) {
                    g_7090[main_ship].f_0b8[c] = g_7090[main_ship].f_0b8[c + 1];
                    g_7090[main_ship].f_0ae[c] = g_7090[main_ship].f_0ae[c + 1];
                }
                g_7090[main_ship].f_0ae[9] = g_7090[main_ship].f_0b8[9] = 0;
                break;
            }
        }
    }
    g_7090[main_ship].cnt -= 2;
    fn_12_6d64(main_ship, 0x1a);
    return 250;
}

/* 16:3ece */
int16_t fn_16_3ece(int16_t i)
{
    if (g_7090[i].f_00a == 2)
        return 0;
    g_7090[i].f_024 = g_7090[i].f_00a = 2;
    if (g_7090[i].f_0ac != 0 || g_96d2[g_7090[i].f_04e].f_28 != 3)
        g_7090[i].f_0e0 = 1;
    else
        g_7090[i].f_0e0 = 0;
    if (g_7090[i].f_0ad != 0 || g_96d2[g_7090[i].f_04e].f_28 != 3)
        g_7090[i].f_0e1 = 1;
    else
        g_7090[i].f_0e1 = 0;
    if (g_7090[i].f_0ac == 0 && g_7090[i].f_0ad == 0
        && g_96d2[g_7090[i].f_04e].f_28 == 3) {
        g_7090[i].f_024 = 1;
        g_7090[i].f_0e0 = 1;
    }
    return 250;
}

/* 16:5762 */
void fn_16_5762(HWND hwnd, int16_t n, int16_t kind, LPSTR suffix)
{
    char text[80];
    char num[20];

    if (n > 0) {
        lstrcpy(text, "");
        if (kind != -1) {
            if (kind != 0)
                lstrcat(text, " ");
            if (kind == 2)
                lstrcat(text, " ");
        }
        if (n > 999)
            lstrcat(text, "a");
        fn_06_1010(n, 100, 1, num);
        lstrcat(text, num);
        lstrcat(text, " - ");
        lstrcat(text, suffix);
        SendMessage(hwnd, WM_USER + 1, 0, (LPARAM)(LPSTR)text);
    }
}

/* 1 when no other live object lies near the player [inferred]. */
/* 16:33a2 */
int16_t fn_16_33a2(void)
{
    POINT pt;
    RECT rc;
    int16_t g;
    int16_t j;
    int16_t r;

    pt = g_1df8[7]->f_04;
    r = 1;
    SetRect(&rc, pt.x - 560, pt.y - 640, pt.x + 1600, pt.y + 640);
    for (g = 0; g <= g_9324; g++) {
        if (g == 7)
            continue;
        for (j = 0; j < g_9406[g]; j++) {
            if (g == g_9324 && j == g_952e)
                continue;
            if (g_1df8[g][j].f_18 == 0 && PtInRect(&rc, g_1df8[g][j].f_04)) {
                return r = 0;
            }
        }
    }
    return r;
}

/* 16:4030 */
int16_t fn_16_4030(int16_t i, int16_t j)
{
    VIEWP(signed char *, g_6e24[g_7090[i].f_0d6].f_32, 0)[j]++;
    if (g_7090[i].f_0d6 != -1)
        g_7090[i].f_014 = (int16_t)(1200L * g_96d2[g_7090[i].f_04e].f_20
            / ((int32_t)((VIEWP(signed char *, g_6e24[g_7090[i].f_0d6].f_32, 0)[1] + 10) * 10) * g_7090[i].f_00c / 100));
    if (j > 1)
        return (VIEWP(signed char *, g_6e24[g_7090[i].f_0d6].f_32, 0)[j] + 1) * 100;
    return (VIEWP(signed char *, g_6e24[g_7090[i].f_0d6].f_32, 0)[j] + 3) * 100;
}

/* 16:5820 */
void fn_16_5820(HWND hDlg)
{
    char num[50];
    char text[50];
    int16_t v;

    text[0] = 0;
    fn_06_0f54(g_9e57, 100, 2, num);
    lstrcat(text, num);
    lstrcat(text, " ");
    fn_09_9580(0x30e3, text);
    if (hDlg == g_9532)
        SetWindowText(GetDlgItem(hDlg, 0x71), text);
    else
        SetWindowText(GetDlgItem(hDlg, 0x6e), text);
    text[0] = 0;
    if (hDlg == g_9532)
        v = g_9e55;
    else
        v = g_9e5d;
    fn_06_1010(v, 100, 2, num);
    lstrcat(text, num);
    lstrcat(text, " ");
    fn_09_9580(0x30e3, text);
    SetWindowText(GetDlgItem(hDlg, 0x6d), text);
}

/* 16:43f2 */
void fn_16_43f2(HWND hDlg)
{
    int16_t i;
    int16_t v;
    int16_t n;
    int16_t items[100];
    int16_t enable;
    char text[60];

    n = (int16_t)SendMessage(GetDlgItem(hDlg, 0x65), LB_GETSELCOUNT, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), LB_GETSELITEMS, n, (LPARAM)(int16_t *)items);
    enable = 0;
    for (i = 0; i < n; i++) {
        SendMessage(GetDlgItem(hDlg, 0x65), LB_GETTEXT, items[i], (LPARAM)(LPSTR)text);
        v = fn_16_0000(text);
        if (v <= g_9e57 || text[0] == ' ')
            enable = 1;
    }
    EnableWindow(GetDlgItem(hDlg, 0x69), enable);
    n = (int16_t)SendMessage(GetDlgItem(hDlg, 0x66), LB_GETSELCOUNT, 0, 0L);
    if (n)
        EnableWindow(GetDlgItem(hDlg, 0x6a), 1);
    else
        EnableWindow(GetDlgItem(hDlg, 0x6a), 0);
}

/* Mouse click handler [inferred]. */
/* 16:638a */
void fn_16_638a(int16_t w, LPARAM lParam, int16_t flag)
{
    POINT pt;
    int16_t hit;
    RECT rc;

    if (!flow_interactive)
        return;
    pt.x = LOWORD(lParam);
    pt.y = HIWORD(lParam);
    if (!g_952c)
        return;
    if (flag) {
        if (g_9530 == 1)
            hit = 0;
        else
            hit = 1;
    } else {
        if (g_9530 != 1)
            CopyRect(&rc, &demon_host_rect);
        else
            SetRect(&rc, 0, 0, demon_host_rect.right, g_0010);
        if (PtInRect(&rc, pt))
            hit = 1;
        else
            hit = 0;
    }
    if (!g_920c && hit) {
        fn_16_68d6(g_9532, 0x912, -1);
    } else if (hit) {
        switch (g_9530) {
        case 3:
        case 4:
            if (g_9004)
                g_9004 *= 2;
            else
                g_9004 = 250;
            g_9004 = g_9004 < 250 ? 250 : g_9004;
            g_958c = g_914a;
            g_914a = -1;
            g_9530 = 1;
            if (g_9660)
                fn_18_0be2();
            break;
        case 1:
            PostMessage(g_0016, 0x9c5, w, lParam);
            break;
        }
    } else if (!hit) {
        switch (g_9530) {
        case 1:
            g_9530 = 4;
            g_914a = g_958c;
            fn_18_0c5c();
            break;
        }
    }
    g_958a = 1;
}

/* Dialog procedure [inferred]. */
/* 16:42a2 */
BOOL fn_16_42a2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    DRAWITEMSTRUCT *dis;
    TEXTMETRIC tm;
    HDC hdc;
    HFONT old;
    MEASUREITEMSTRUCT *mis;

    switch (msg) {
    case WM_INITDIALOG:
        fn_16_541c(hDlg);
        break;
    case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT *)lParam;
        if (dis->itemID == 0xffff)
            fn_16_5a8a(dis);
        else
            switch (dis->itemAction) {
            case ODA_DRAWENTIRE:
                fn_16_5ada(dis);
                break;
            case ODA_SELECT:
                fn_16_590c(dis);
                break;
            case ODA_FOCUS:
                fn_16_5a8a(dis);
                break;
            }
        return TRUE;
    case WM_MEASUREITEM:
        hdc = GetDC(g_0016);
        old = SelectObject(hdc, g_90fe);
        GetTextMetrics(hdc, &tm);
        SelectObject(hdc, old);
        ReleaseDC(g_0016, hdc);
        mis = (MEASUREITEMSTRUCT *)lParam;
        mis->itemHeight = tm.tmHeight + tm.tmExternalLeading;
        break;
    case WM_COMMAND:
        switch (wParam) {
        case 0x69:
            fn_16_44fa(hDlg);
            break;
        case 0x6a:
            fn_16_4900(hDlg);
            break;
        case 0x65:
            fn_16_43f2(hDlg);
            if (HIWORD(lParam) == LBN_DBLCLK)
                PostMessage(hDlg, WM_COMMAND, 0x69, 0L);
            break;
        case 0x66:
            fn_16_43f2(hDlg);
            if (HIWORD(lParam) == LBN_DBLCLK)
                PostMessage(hDlg, WM_COMMAND, 0x6a, 0L);
            break;
        case 1:
            fn_16_5db0(hDlg);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

/* 16:619e */
int16_t fn_16_619e(void)
{
    POINT sz;

    if (g_93a6)
        return 0;
    if (!(g_95a2 = GlobalAlloc(GHND, 0x2eL)))
        return 0;
    g_6da4 = (REC_6DA4 *)GlobalLock(g_95a2);
    if (g_6da4 == NULL) {
        GlobalFree(g_95a2);
        return 0;
    }
    if (g_90f4 == 6) {
        g_6da4->f_02 = g_6e14;
    } else {
        if (g_9534[1]) {
            DeleteObject(g_9534[1]);
            g_9534[1] = 0;
        }
        if (g_965e == 1) {
            sz.x = LO16(g_90ea);
            sz.y = g_0010;
        } else {
            sz.x = 0xa0;
            sz.y = 0x82;
        }
        SetRect(&demon_host_rect, LO16(g_90ea) / 2 - sz.x / 2, g_0010 / 2 - sz.y / 2,
                LO16(g_90ea) / 2 + sz.x / 2, g_0010 / 2 + sz.y / 2);
        g_6da4->f_02 = sz;
        PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
        g_9534[1] = CreateRectRgn(demon_host_rect.left, demon_host_rect.top, demon_host_rect.right, demon_host_rect.bottom);
    }
    g_6da4->f_06 = 0;
    g_6da4->f_00 = g_0016;
    g_6da4->f_1e = g_920e;
    g_6da4->f_20 = g_9210;
    g_6da4->f_2a = 0x24;
    g_6da4->f_00 = 0;
    lstrcpy(g_6da4->f_08, "...");
    g_959a = 0;
    fn_16_64c8();
    g_958a = 1;
    return 1;
}

/* 16:44fa */
void fn_16_44fa(HWND hDlg)
{
    int16_t i;
    int16_t j;
    int16_t k;
    int16_t v;
    int16_t n;
    WORD sel[100];
    char buf[50];
    char buf2[80];
    int16_t ok;
    int16_t flag;
    int16_t match;
    char buf3[20];
    char c;
    char msg[180];

    n = SendMessage(GetDlgItem(hDlg, 0x65), 0x411, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), 0x412, n, (LPARAM)(LPSTR)sel);
    if (flow_interactive == 0)
        n = 0;
    SendMessage(GetDlgItem(hDlg, 0x66), WM_SETREDRAW, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), WM_SETREDRAW, 0, 0L);
    for (i = 0; i < n; i++) {
        SendMessage(GetDlgItem(hDlg, 0x65), 0x40a, sel[i], (LPARAM)(LPSTR)buf);
        v = fn_16_0000(buf);
        if (g_9e5b && fn_16_5f0e(buf, "BODY")) {
            fn_10_82a2(-100);
            SetActiveWindow(g_9532);
        }
        flag = 0;
        j = ok = 1;
        for (; j < 27; j++) {
            fn_09_955c(j + 0xba, buf2);
            if (fn_16_5f0e(buf, buf2)) {
                for (k = 2; k < 8; k++) {
                    if (buf[k - 1] == '-') {
                        LoadString(g_9212, 0x4a2, buf3, 40);
                        for (c = 0; c < lstrlen(buf3); c++) {
                            if (buf[c + k + 1] != buf3[c]) {
                                flag = 1;
                                if (hDlg == g_9532)
                                    g_958e++;
                                else
                                    g_958e--;
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
        fn_09_955c(0x7b1, buf2);
        j = match = 0;
        for (; j < 12; j++) {
            if (buf[j] == buf2[0]) {
                match = 1;
                break;
            } else if (buf[j] == 0)
                break;
        }
        if (match)
            for (; j < 4; j++)
                if (buf[i + j] != buf2[i])
                    match = 0;
        if (hDlg == g_9532 && g_958e > 10 && flag) {
            if (flow_interactive) {
                fn_09_955c(0x7e7, msg);
                fn_09_9580(0x7e8, msg);
                MessageBox(g_9532, msg, g_9690, MB_ICONEXCLAMATION);
            }
            g_958e--;
            ok = 0;
        }
        if (hDlg == g_9532 && g_920c == 0 && (flag || match) && flow_interactive) {
            fn_16_68d6(g_9532, 0x910, 0x911);
            ok = 0;
        }
        if (hDlg == g_959c)
            ok = 1;
        if (ok && (v <= g_9e57 || buf[0] == ' ')) {
            if (hDlg == g_9532) {
                g_9e57 -= v;
                g_9e55 += v;
            } else {
                g_9e57 += v;
                g_9e5d += v;
            }
            SendMessage(GetDlgItem(hDlg, 0x66), 0x401, 0, (LPARAM)(LPSTR)buf);
        } else
            SendMessage(GetDlgItem(hDlg, 0x65), 0x406, 0, (LPARAM)sel[i]);
    }
    n = SendMessage(GetDlgItem(hDlg, 0x65), 0x411, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), 0x412, n, (LPARAM)(LPSTR)sel);
    for (i = 0; i < n; i++)
        SendMessage(GetDlgItem(hDlg, 0x65), 0x403, sel[n - i - 1], 0L);
    SendMessage(GetDlgItem(hDlg, 0x66), WM_SETREDRAW, 1, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), WM_SETREDRAW, 1, 0L);
    fn_16_5820(hDlg);
    fn_16_43f2(hDlg);
    if (flow_interactive == 0)
        PostMessage(hDlg, WM_COMMAND, 1, 0L);
}

/* 16:4900 */
void fn_16_4900(HWND hDlg)
{
    int16_t i;
    int16_t v;
    int16_t n;
    WORD sel[100];
    int16_t j;
    int16_t k;
    char buf[50];
    char buf2[50];
    char buf3[20];
    char c;

    n = SendMessage(GetDlgItem(hDlg, 0x66), 0x411, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x66), 0x412, n, (LPARAM)(LPSTR)sel);
    SendMessage(GetDlgItem(hDlg, 0x66), WM_SETREDRAW, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), WM_SETREDRAW, 0, 0L);
    for (i = 0; i < n; i++) {
        SendMessage(GetDlgItem(hDlg, 0x66), 0x40a, sel[i], (LPARAM)(LPSTR)buf);
        if (buf[0] == ' ' && buf[1] == ' ') {
            SendMessage(GetDlgItem(hDlg, 0x66), 0x406, 0, (LPARAM)sel[i]);
        } else {
            SendMessage(GetDlgItem(hDlg, 0x65), 0x401, 0, (LPARAM)(LPSTR)buf);
            if (fn_16_5f0e(buf, "BODY"))
                WritePrivateProfileString(g_9690, "MainShip",
                    g_96d2[g_7090[g_952e].f_04e].f_70, g_96a9);
            v = fn_16_0000(buf);
            if (hDlg == g_9532) {
                g_9e57 += v;
                g_9e55 -= v;
            } else {
                g_9e57 -= v;
                g_9e5d -= v;
            }
            for (j = 1; j < 27; j++) {
                fn_09_955c(j + 0xba, buf2);
                if (fn_16_5f0e(buf, buf2)) {
                    for (k = 2; k < 8; k++) {
                        if (buf[k - 1] == '-') {
                            LoadString(g_9212, 0x4a2, buf3, 40);
                            for (c = 0; c < lstrlen(buf3); c++) {
                                if (buf[c + k + 1] != buf3[c]) {
                                    if (hDlg == g_9532)
                                        g_958e--;
                                    else
                                        g_958e++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    n = SendMessage(GetDlgItem(hDlg, 0x66), 0x411, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x66), 0x412, n, (LPARAM)(LPSTR)sel);
    for (i = 0; i < n; i++)
        SendMessage(GetDlgItem(hDlg, 0x66), 0x403, sel[n - i - 1], 0L);
    SendMessage(GetDlgItem(hDlg, 0x66), WM_SETREDRAW, 1, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), WM_SETREDRAW, 1, 0L);
    fn_16_5820(hDlg);
    fn_16_43f2(hDlg);
}

/* 16:5db0 */
void fn_16_5db0(HWND hDlg)
{
    int16_t i;
    int16_t j;
    int16_t n;
    char a[50];
    char b[50];
    char c[50];
    int16_t m;

    n = (int16_t)SendMessage(GetDlgItem(hDlg, 0x66), LB_GETCOUNT, 0, 0L);
    for (i = 0; i < n; i++) {
        SendMessage(GetDlgItem(hDlg, 0x66), LB_GETTEXT, i, (LPARAM)(LPSTR)a);
        for (j = 1; j < 27; j++) {
            fn_09_955c(j + 0xba, b);
            if (fn_16_5f0e(a, b)) {
                g_9564[j] = 1;
                m = (int16_t)SendMessage(GetDlgItem(g_9532, 0x65), LB_GETCOUNT, 0, 0L);
                for (j = 0; j < m; j++) {
                    SendMessage(GetDlgItem(g_9532, 0x65), LB_GETTEXT, j, (LPARAM)(LPSTR)c);
                    if (fn_16_5f0e(c, b))
                        SendMessage(GetDlgItem(g_9532, 0x65), LB_DELETESTRING, j, 0L);
                }
                break;
            }
        }
    }
    InvalidateRect(GetDlgItem(g_9532, 0x65), NULL, TRUE);
    UpdateWindow(GetDlgItem(g_9532, 0x65));
    g_959c = 0;
    EndDialog(hDlg, 1);
}

/* Paints the message panel for state g_9530 [inferred]. */
/* 16:64fa */
void fn_16_64fa(void)
{
    char buf[110];
    DWORD org;
    int16_t done;

    if (g_13dc == 0 && g_9530 == 2) {
        fn_18_0000();
        return;
    }
    if (g_90f4 == 6) {
        SelectClipRgn(g_13dc, g_9534[1]);
        org = SetWindowOrg(g_13dc, -demon_host_rect.left, -demon_host_rect.top);
    }
    done = 0;
    switch (g_9530) {
    case 3:
        PatBlt(g_13dc, 0, 0, g_6da4->f_02.x, g_6da4->f_02.y, BLACKNESS);
        if (g_920c == 0)
            fn_09_955c(0x91a, buf);
        else
            fn_09_955c(0x7eb, buf);
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f_02.x / 2, g_6da4->f_02.y / 2 - 18, buf);
        if (g_920c == 0)
            fn_09_955c(0x91b, buf);
        else
            lstrcpy(buf, g_6da4->f_08);
        lstrcat(buf, "...");
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f_02.x / 2, g_6da4->f_02.y / 2, buf);
        break;
    case 4:
        if (music_pause_state != -2)
            fn_10_7480(-2, 1);
        PatBlt(g_13dc, 0, 0, g_6da4->f_02.x, g_6da4->f_02.y, BLACKNESS);
        lstrcpy(buf, g_6da4->f_08);
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f_02.x / 2, g_6da4->f_02.y / 2 - 18, buf);
        fn_09_955c(0x7ec, buf);
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f_02.x / 2, g_6da4->f_02.y / 2, buf);
        g_6da4->f_1c = 1;
        break;
    case 1:
    case 2:
    case 5:
    case 6:
        if (g_6da4 == NULL)
            break;
        if (g_959a == 0) {
            g_959a = 1;
            PatBlt(g_13dc, 0, 0, g_6da4->f_02.x, g_6da4->f_02.y, BLACKNESS);
            if (g_90f4 == 1) {
                fn_09_955c(0x7ed, buf);
                lstrcat(buf, "...");
                fn_10_94c4(0, 6, 0xff00L, g_6da4->f_02.x / 2, g_6da4->f_02.y / 2, buf);
            } else {
                lstrcpy(buf, g_6da4->f_08);
                fn_10_94c4(2, 6, 0xff00L, g_6da4->f_02.x / 2, g_6da4->f_02.y / 2 - 18, buf);
                fn_09_955c(0x7ee, buf);
                lstrcat(buf, "...");
                fn_10_94c4(2, 6, 0xff00L, g_6da4->f_02.x / 2, g_6da4->f_02.y / 2, buf);
            }
        }
        if (g_9530 == 6) {
            g_9530 = 2;
            if (g_90f4 != 1)
                done = 1;
        }
        if (g_9530 != 5) {
            if (g_8ff4) {
                if (g_2388 < g_1e50) {
                    g_2388 = g_1e50 + 50;
                    fn_11_72b2();
                }
                fn_11_7504();
            }
            fn_18_0000();
        }
        if (g_9530 == 5)
            g_9530 = 1;
        if (done) {
            g_959a = 0;
            g_9530 = 3;
            g_914a = g_958c;
        }
        break;
    }
    if (done)
        g_958a = 1;
    else
        g_958a = 0;
    if (g_90f4 == 6) {
        SetWindowOrg(g_13dc, LOWORD(org), HIWORD(org));
        SelectClipRgn(g_13dc, g_9534[2]);
    }
}

/* Owner-draw list item [inferred]. */
/* 16:590c */
void fn_16_590c(DRAWITEMSTRUCT *dis)
{
    RECT rc;
    HBRUSH hbr;
    char text[80];
    HFONT old;
    int16_t v;

    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_SELECTED) {
        hbr = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
        SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
    } else {
        hbr = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
    }
    SetBkMode(dis->hDC, TRANSPARENT);
    SendMessage(dis->hwndItem, LB_GETTEXT, dis->itemID, (LPARAM)(LPSTR)text);
    FillRect(dis->hDC, &rc, hbr);
    old = SelectObject(dis->hDC, g_90fe);
    if (dis->CtlID == 0x65) {
        v = fn_16_0000(text);
        if (v > g_9e57 && text[0] != ' ')
            SetTextColor(dis->hDC, GetSysColor(COLOR_GRAYTEXT));
    }
    if (text[1] == ' ' || text[0] == 'a' || text[1] == 'a') {
        for (v = 0; v < lstrlen(text); v++)
            text[v] = text[v + 1];
        if (text[0] == 'a')
            text[0] = ' ';
    }
    TextOut(dis->hDC, rc.left + 2, rc.top, text, lstrlen(text));
    SelectObject(dis->hDC, old);
    DeleteObject(hbr);
}

/* Installs part j of object idx; returns the repair cost [inferred]. */
/* 16:3468 */
int16_t fn_16_3468(int16_t idx, int16_t j)
{
    int16_t r;
    int16_t n;
    int16_t b2;
    int16_t b1;
    char name[20];

    if (g_9563 == 0 && VIEWP(int16_t *, g_96d2[g_7090[idx].f_04e].f_22, 0)[j] == -1
        && (j != 3 || g_3a38[idx] != 0))
        return 0;
    if (j == 0 && g_7090[idx].f_026[0] < 40)
        g_5078 = g_5078 * (g_7090[idx].f_026[0] + 200) / 300;
    r = 100 - g_7090[idx].f_026[j];
    if (g_92e4 == 0)
        g_7090[idx].f_026[j] = 100;
    g_7090[idx].flag = 1;
    switch (j) {
    case 1:
        g_7090[idx].f_08c = 2;
        break;
    case 3:
        if (g_9563) {
            fn_14_3eda();
            if (idx == main_ship)
                GetPrivateProfileString(g_9690, "MainShip", "EAGLE", name, 20, g_96a9);
            else
                lstrcpy(name, g_96d2[g_7090[idx].f_04e].f_70);
            for (n = 0; n < g_95aa; n++)
                if (lstrcmp(g_6e20[n].f_0a, name) == 0)
                    break;
            fn_16_5f78(idx, n);
            fn_14_4074();
        } else {
            g_7090[idx].f_020 = g_1df8[g_9324][idx].f_22 - 2;
            g_7090[idx].f_022 = 1;
            g_1df8[g_9324][idx].f_44 = g_96d2[g_7090[idx].f_04e].f_32;
            b1 = g_7090[idx].f_0ac;
            b2 = g_7090[idx].f_0ad;
            g_7090[idx].f_0ac = 0;
            fn_14_11a8(idx);
            g_1df8[g_9324][idx].f_3a = g_3a38[idx];
            if (g_92e4) {
                g_7090[idx].f_0ac = b1;
                g_7090[idx].f_0ad = b2;
            }
            if (g_7090[idx].f_0d6 >= 0) {
                g_6e24[g_7090[idx].f_0d6].f_72 = g_7090[idx].f_0ac;
                g_6e24[g_7090[idx].f_0d6].f_73 = g_7090[idx].f_0ad;
            }
        }
        break;
    }
    g_7090[idx].f_024 = g_7090[idx].f_00a;
    if (g_7090[idx].f_0ac)
        g_7090[idx].f_0e0 = 1;
    else if (g_96d2[g_7090[idx].f_04e].f_28 == 3)
        g_7090[idx].f_0e0 = 0;
    if (g_7090[idx].f_0ad)
        g_7090[idx].f_0e1 = 1;
    else if (g_96d2[g_7090[idx].f_04e].f_28 == 3)
        g_7090[idx].f_0e1 = 0;
    if (g_7090[idx].f_00a == 1 || (!g_7090[idx].f_0ac && !g_7090[idx].f_0ad
        && g_96d2[g_7090[idx].f_04e].f_28 == 3)) {
        g_7090[idx].f_0e0 = 1;
        g_7090[idx].f_024 = 1;
    }
    fn_13_33d6(idx);
    return r / 10 * 10;
}

/* Picks what the computer buys for object idx [inferred]. */
/* 16:3b18 */
void fn_16_3b18(int16_t idx, int16_t flag)
{
    int16_t i;
    int16_t j;
    int16_t r;
    int16_t k;
    int16_t found;
    int32_t money;
    int16_t cost;

    if (flag != 2) {
        g_953e = g_9540 = g_953f = g_9541 = g_9563 = 0;
        for (j = 1; j < 27; j++)
            g_9564[j] = g_9542[j] = 0;
        for (j = 0; j <= 5; j++)
            g_955d[j] = 0;
    }
    if (g_92e4 && idx == main_ship)
        return;
    if (g_9e5b == 0 && flag == 0) {
        g_9563 = 1;
        return;
    }
    if (idx == main_ship && flow_interactive)
        return;
    money = g_7090[idx].f_0dc;
    if (g_7090[idx].f_026[0] < 60 || g_7090[idx].f_026[2] < 40) {
        g_953e = 1;
        for (i = 0; i < 3; i++) {
            g_9e55 += 100 - g_7090[idx].f_026[i];
            money -= 100 - g_7090[idx].f_026[i];
        }
    }
    if ((g_96d2[g_7090[idx].f_04e].f_1e / 5 > g_7090[idx].f_01e && g_9406[4] < 7)
        || g_96d2[g_7090[idx].f_04e].f_1e / 12 > g_7090[idx].f_01e) {
        g_9540 = 1;
        g_9e55 += (g_96d2[g_7090[idx].f_04e].f_1e - g_7090[idx].f_01e) / 70 * 10;
        money -= (g_96d2[g_7090[idx].f_04e].f_1e - g_7090[idx].f_01e) / 70 * 10;
    }
    if (money > 100) {
        if (g_91f8 > 2 && g_7090[idx].f_00a < 2) {
            g_9541 = 1;
            g_9e55 += 250;
            money -= 250;
        }
        r = rand() % 3;
        if (r == 0 && money >= 700) {
            for (i = 0; i < 10; i++) {
                k = rand() % 20 + 1;
                found = 0;
                if (g_11aa || g_2f4c[k].f_3e == -1) {
                    for (j = 1; j < g_7090[idx].cnt; j++) {
                        if (g_7090[idx].f_0b8[j] == k) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found && g_2f4c[k].f_3c <= money) {
                        g_9542[k] = 1;
                        money -= g_2f4c[k].f_3c;
                        g_9e55 += g_2f4c[k].f_3c;
                    } else if (found && g_7090[idx].f_0ae[i] != -1 && g_7090[idx].f_0ae[i] < 20
                        && (20 - g_7090[idx].f_0ae[i]) * 10 <= money) {
                        g_9542[k] = 1;
                        money -= (20 - g_7090[idx].f_0ae[i]) * 10;
                        g_9e55 += (20 - g_7090[idx].f_0ae[i]) * 10;
                    }
                }
            }
        } else if (r == 1 && money >= 400 && g_7090[idx].f_0d6 >= 0) {
            for (i = 0; i < 3; i++) {
                k = rand() % 6;
                cost = (VIEWP(signed char *, g_6e24[g_7090[idx].f_0d6].f_32, 0)[k] + 2) * 100;
                if (k < 2)
                    cost += 200;
                if (cost <= money && VIEWP(signed char *, g_6e24[g_7090[idx].f_0d6].f_32, 0)[k] < 5
                    && (k < 5 || g_96d2[g_7090[idx].f_04e].f_28 != -1)) {
                    g_955d[k]++;
                    money -= cost;
                    g_9e55 += cost;
                }
            }
        }
    }
    if (g_7090[idx].f_0dc > 250 && g_96d2[g_7090[idx].f_04e].f_2a != -1
        && (!g_7090[idx].f_0ac || !g_7090[idx].f_0ad)) {
        g_953f = 1;
        g_9e55 += 100 - g_7090[idx].f_026[4];
    }
}

/* Applies the shop's purchases to object idx [inferred]. */
/* 16:3784 */
void fn_16_3784(int16_t idx, int16_t flag)
{
    int16_t i;
    int16_t j;
    int16_t k;
    int16_t unused;
    int32_t saved;
    int16_t m;
    int16_t unused2;

    if (flag == 0) {
        g_7090[idx].f_0dc += g_7090[idx].f_0ce;
        g_7090[idx].f_0ce = 0;
    }
    if (idx != main_ship || flag)
        fn_16_3b18(idx, flag);
    if (flag || idx == main_ship)
        saved = g_7090[idx].f_0dc;
    if (g_9541)
        g_7090[idx].f_0dc -= fn_16_3ece(idx);
    if (g_957f)
        g_7090[idx].f_0dc -= fn_16_3f88(idx);
    for (i = 0; i <= 5; i++)
        if (g_955d[i])
            for (j = 0; j < g_955d[i]; j++)
                g_7090[idx].f_0dc -= fn_16_4030(idx, i);
    if (g_953e || (flag && g_92e4 == 0))
        for (i = 0; i < 3; i++)
            g_7090[idx].f_0dc -= fn_16_3468(idx, i);
    if (g_953f || flag) {
        if (idx == main_ship || g_7090[idx].f_0dc > 100 || flag)
            g_7090[idx].f_0dc -= fn_16_3468(idx, 3);
    } else if (g_9563) {
        g_7090[idx].f_0ac = 0;
        for (i = 0; i < 4; i++)
            fn_16_3468(idx, i);
    }
    for (i = 1; i < 27; i++) {
        if (g_9564[i]) {
            for (j = 0; j < g_7090[idx].cnt; j++) {
                if (g_7090[idx].f_0b8[j] == i) {
                    g_7090[idx].f_0ae[j] = g_7090[idx].f_0b8[j] = 0;
                    for (k = j; k < 9; k++) {
                        g_7090[idx].f_0b8[k] = g_7090[idx].f_0b8[k + 1];
                        g_7090[idx].f_0ae[k] = g_7090[idx].f_0ae[k + 1];
                    }
                    g_7090[idx].f_0ae[9] = g_7090[idx].f_0b8[9] = 0;
                    g_7090[idx].cnt--;
                    break;
                }
            }
        } else if (g_9542[i]) {
            for (m = 0; m < g_7090[idx].cnt; m++) {
                if (g_7090[idx].f_0b8[m] == i) {
                    g_7090[idx].f_0dc -= fn_16_3730(idx, m);
                    break;
                }
            }
            if (g_7090[idx].cnt == m) {
                fn_12_6d64(idx, i);
                g_7090[idx].f_0dc -= g_2f4c[i].f_3c;
            }
        }
    }
    if (g_9540 || flag)
        g_7090[idx].f_0dc -= fn_16_3e80(idx);
    if (flag || idx == main_ship)
        g_7090[idx].f_0dc = saved;
    fn_13_33d6(idx);
    g_7090[idx].f_002 = 0;
    g_1df8[g_9324][idx].f_26 = 0;
    if (g_90f4 == 1 && idx == main_ship) {
        if (g_0a7e)
            PostMessage(g_0a7e, WM_PAINT, 0, 0L);
        if (g_0a7c)
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    }
    g_953e = g_9540 = g_953f = g_9541 = g_957f = 0;
    for (j = 1; j < 27; j++)
        g_9564[j] = g_9542[j] = 0;
    for (j = 0; j <= 5; j++)
        g_955d[j] = 0;
    g_9563 = 0;
    VIEW(int32_t, g_9e5b, 0) = 1;
}

/* Dialog procedure [inferred]. */
/* 16:4104 */
BOOL fn_16_4104(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    DRAWITEMSTRUCT *dis;
    TEXTMETRIC tm;
    HDC hdc;
    HFONT old;
    MEASUREITEMSTRUCT *mis;

    switch (msg) {
    case WM_INITDIALOG:
        fn_16_51d6(hDlg);
        break;
    case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT *)lParam;
        if (dis->itemID == 0xffff)
            fn_16_5a8a(dis);
        else
            switch (dis->itemAction) {
            case ODA_DRAWENTIRE:
                fn_16_5ada(dis);
                break;
            case ODA_SELECT:
                fn_16_590c(dis);
                break;
            case ODA_FOCUS:
                fn_16_5a8a(dis);
                break;
            }
        return TRUE;
    case WM_MEASUREITEM:
        hdc = GetDC(g_0016);
        old = SelectObject(hdc, g_90fe);
        GetTextMetrics(hdc, &tm);
        SelectObject(hdc, old);
        ReleaseDC(g_0016, hdc);
        mis = (MEASUREITEMSTRUCT *)lParam;
        mis->itemHeight = tm.tmHeight + tm.tmExternalLeading;
        break;
    case WM_COMMAND:
        switch (wParam) {
        case 0x69:
            fn_16_44fa(hDlg);
            break;
        case 0x6a:
            fn_16_4900(hDlg);
            break;
        case 0xc3:
            fn_10_744c(0x13);
            DialogBox(g_9212, MAKEINTRESOURCE(0x17a), g_9532, (DLGPROC)fn_16_42a2);
            fn_16_5820(hDlg);
            fn_16_43f2(hDlg);
            UpdateWindow(GetDlgItem(hDlg, 0x65));
            break;
        case 0x65:
            fn_16_43f2(hDlg);
            if (HIWORD(lParam) == LBN_DBLCLK)
                PostMessage(hDlg, WM_COMMAND, 0x69, 0L);
            break;
        case 0x66:
            fn_16_43f2(hDlg);
            if (HIWORD(lParam) == LBN_DBLCLK)
                PostMessage(hDlg, WM_COMMAND, 0x6a, 0L);
            break;
        case 1:
            fn_16_5b24(hDlg);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

/* 16:0b4e */
int16_t fn_16_0b4e(int16_t i)
{
    int16_t k;
    int16_t bk;
    int16_t d;
    int16_t b;
    int16_t a;
    int16_t best;
    int32_t v;

    if (g_934e < 3)
        return 0;
    if (g_913a != 0 || g_913c != 0)
        return 0;
    if (g_92e8 != 0 && g_94b2 == 0)
        return 0;
    if (g_9320 == 6 || g_9320 == 7)
        return 0;
    v = g_7090[i].f_0ce + g_7090[i].f_0dc;
    if (v < -350L && g_7090[i].f_0ce < 200)
        return 0;
    if (i != main_ship && v < 200)
        return 0;
    if ((g_1df8[7]->f_2e != 0 && g_1df8[7]->f_18 == 0) || g_9e49 < 9)
        return 0;
    g_9e4b = 0x578;
    g_952e = i;
    g_9e49 = 0;
    if (g_1df8[7]->f_18 != 0) {
        g_1df8[7]->f_18 = 0;
        g_1df8[7]->f_2e = 0;
        best = 20000;
        for (k = 0; k < g_9318 * 2; k += 2) {
            d = fn_08_285a(&b, &a, g_1df8[g_9324][g_952e].f_04, g_1df8[12][k].f_04);
            if (d < best) {
                bk = k;
                best = d;
            }
        }
        g_1df8[7]->f_04.x = g_1df8[8][bk].f_04.x + 480;
        g_1df8[7]->f_04.y = g_1df8[8][bk].f_04.y - g_1df8[7]->f_20;
        g_1df8[7]->f_1a = 0;
        g_1df8[7]->f_00.x = -1000;
        g_1df8[7]->f_00.y = -1000;
        g_1df8[7]->f_08.x = 100;
        g_1df8[7]->f_08.y = 100;
        g_1df8[7]->f_0c = -20;
        g_1df8[7]->f_0e = -70;
        fn_07_2080(7);
    }
    return 1;
}

/* Step of the end-of-mission sequence (state g_914a) [inferred].
 * Case 58 is written as two statements: `f_0da -= (long)g_9e55 - g_9e5d`
 * always compiles as add/adc of the negated difference, while CL combines
 * `f += b; f -= a;` into the game's sub/sbb of (a - b). Block-scope slots
 * follow a LIFO reuse of freed slots: case 2's x/y must be one POINT so that
 * the later 4-byte locals (t, l) reuse it at bp-0x72. */
/* 16:0cfe */
void fn_16_0cfe(int16_t a)
{
    int16_t i;
    int16_t j;
    int16_t n;
    int16_t s;
    int16_t r;
    char buf[70];
    int16_t ok;
    int16_t flag;
    POINT pt;
    RECT rc;
    DWORD t0;

    if (a && (g_914a > 0 || g_914a == -1) && (g_914a >= 2 || g_92a2 >= 1))
        fn_16_2144();
    if (a || g_9532)
        return;
    if ((GetKeyState(VK_CONTROL) & 0x8000) && !g_952c && g_92a2 != 1)
        g_0928 = 1;
    if (g_8f70 > 1)
        g_0928 = 1;
    switch (g_914a) {
    case 0:
        sprite_dc_release();
        if (!g_93a6)
            g_9662 = g_952c = 0;
        else
            g_959a = g_952c = 1;
        fn_11_02f0();
        fn_15_302e();
        if (g_952e == main_ship)
            g_1e80 = g_1e84 = 0;
        g_914a++;
        break;
    case 1:
        fn_15_3590();
    brk:    /* layout-only, see case 3 */
        break;
    case 2: {
        HDC dc;
        HBITMAP old;
        int16_t w;
        HPALETTE pal;
        POINT p;

        BitBlt(g_13dc,
               p.x = LO16(g_90ea) / 2
                   - (w = (g_6e24[g_7090[main_ship].f_0d6].f_7a
                           + (g_6e24[g_7090[main_ship].f_0d6].f_7b - 6) / 2) * 4) / 2,
               p.y = g_92d6 + 2, w, w,
               g_3cdc[1], 0, g_3ce8[1], SRCAND);
        BitBlt(g_13dc, p.x, p.y, w, w, g_3cdc[0], 0, g_3ce8[1], SRCPAINT);
        w = g_1df8[14][main_ship].f_22 << 3 >> g_959e;
        if (!g_953c)
            g_953c = CreateCompatibleBitmap(g_13dc, g_3ce6, w + 0x43);
        dc = CreateCompatibleDC(g_13dc);
        if (g_920e)
            pal = SelectPalette(dc, g_920e, 0);
        old = SelectObject(dc, g_953c);
        PatBlt(dc, 0, 0, g_3ce6, w + 0x43, BLACKNESS);
        BitBlt(dc, 0, 5, g_3ce6, w + 0x3e, g_13dc,
               LO16(g_90ea) / 2 - g_3ce6 / 2, g_0010 - w - 0x3e, SRCCOPY);
        SelectObject(dc, old);
        if (pal)
            SelectPalette(dc, pal, 0);
        DeleteDC(dc);
        fn_10_a332(ambulance_line, (char *)0x4a0, 1, 0xe, g_952e, 1);
        fn_16_2e3c(1, 0);
        g_914a++;
        break;
    }
    case 4: {
        int16_t id;

        if (g_93a6)
            fn_10_a332(ambulance_line, (char *)0x7e4, 1, (LPSTR)g_380c);
        else {
            if (g_96d2[g_7090[g_952e].f_04e].f_28 == -1)
                n = 3;
            else
                n = 4;
            for (i = s = 0; i < n; i++)
                s += g_7090[g_952e].f_026[i];
            s /= n;
            if (!g_9e5b)
                fn_10_a332(ambulance_line, (char *)0x7e5, 1, (LPSTR)g_380c);
            else {
                if (s > 0x46)
                    id = 0x137;
                else if (s > 0x2d)
                    id = 0x138;
                else if (s > 0x1b)
                    id = 0x139;
                else
                    id = 0x13a;
                fn_10_a332(ambulance_line, (char *)0x49f, 1, id, (LPSTR)g_380c);
            }
        }
        fn_11_3fd4(ambulance_line, 1);
        if (s > 0x1b && g_9e5b)
            lstrcat(ambulance_line, g_09ee);
        else
            lstrcat(ambulance_line, "!");
        g_914a++;
        break;
    }
    case 6: {
        int16_t id;

        if (g_93a6) {
            g_1c48 = 0;
            g_914a = 0x3c;
            break;
        }
        for (i = s = 0; i < 3; i++)
            s += g_7090[g_952e].f_026[i];
        s /= 3;
        if (g_96d2[g_7090[g_952e].f_04e].f_1e / 5 > g_7090[g_952e].f_01e)
            id = 0x499;
        else if (s < 0x32)
            id = 0x9d4;
        else if (g_96d2[g_7090[g_952e].f_04e].f_28 != -1
                 && g_7090[g_952e].f_026[3] < 0x32)
            id = 0x9d5;
        else if (g_96d2[g_7090[g_952e].f_04e].f_1e / 2 > g_7090[g_952e].f_01e)
            id = 0x499;
        else {
            g_914a = 8;
            break;
        }
        fn_10_a332(ambulance_line, (char *)0x485, 1, id);
        lstrcat(ambulance_line, g_09ee);
        g_914a++;
        break;
    }
    case 8:
        g_914a++;
        if (g_7090[g_952e].f_0ce > 0) {
            fn_06_1010(g_7090[g_952e].f_0ce, 100, 2, buf);
            fn_10_a332(ambulance_line, (char *)0x495, 1, (LPSTR)buf);
        } else
            fn_10_a332(ambulance_line, (char *)0x9df, 1, 0xe, g_952e, 1);
        break;
    case 10:
        fn_10_744c(0x6e);
        VIEWP(int16_t *, g_9e41.f_00, 0)[0] = -1;
        VIEWP(int16_t *, g_9e41.f_00, 0)[1] = 0x32;
        VIEWP(int16_t *, g_9e41.f_00, 0)[2] = 5;
        VIEWP(int16_t *, g_9e41.f_00, 0)[3] = 0xf;
        g_111e = 0;
        g_1c44 = g_1e50 + 2500;
        g_958e = g_7090[g_952e].cnt;
        if (g_7090[g_952e].f_0ce > 0) {
            g_914a++;
            break;
        }
        g_914a = 0xd;
        break;
    case 11:
        if (g_1c44 < g_1e50) {
            g_914a++;
            g_1c44 = g_1e50 + 1000;
            fn_09_95f4(0x496);
        }
        break;
    case 13:
        g_7090[g_952e].f_0dc += g_7090[g_952e].f_0ce;
        g_7090[g_952e].f_0ce = 0;
        fn_06_0f54(g_7090[g_952e].f_0dc, 100, 2, buf);
        fn_10_a332(ambulance_line, (char *)0x486, 1, (LPSTR)buf);
        g_914a++;
        break;
    case 15: {
        DWORD t; HDC dc; HBITMAP old;
        if (!g_9532) {
            t = GetCurrentTime();
            while (GetCurrentTime() - t < 1300)
                ;
            if (!g_953a)
                g_953a = CreateCompatibleBitmap(g_13dc, g_6e14.x - 4, g_6e14.y - 4);
            dc = CreateCompatibleDC(g_13dc);
            old = SelectObject(dc, g_953a);
            BitBlt(dc, 0, 0, g_6e14.x - 4, g_6e14.y - 4, g_13dc,
                   g_6e18.x + g_3d48 + 7, g_6e18.y + g_3d4a + 7, SRCCOPY);
            SelectObject(dc, old);
            DeleteDC(dc);
            if (flow_interactive)
                fn_10_744c(0x13);
            if (g_7090[main_ship].f_0e5
                && (!g_7090[main_ship].f_0ac || !g_7090[main_ship].f_0ad))
                g_9598 = 1;
            else
                g_9598 = 0;
            if (g_9530 == 1)
                g_9530 = 4;
            if (g_9e5b) {
                DialogBox(g_9212, MAKEINTRESOURCE(0xc2), g_0016, fn_16_4104);
                if (!flow_interactive)
                    fn_16_3b18(main_ship, 0);
            } else {
                g_9532 = 1;
                r = fn_10_82a2(6);
                g_953e = g_9540 = g_953f = g_9541 = g_957f = 0;
                for (j = 1; j < 0x1b; j++) {
                    g_9542[j] = 0;
                    g_9564[j] = 0;
                }
                g_9563 = 1;
                g_9e55 = 600;
                for (i = 0; i < 4; i++)
                    if (VIEWP(int16_t *, g_96d2[g_7090[g_952e].f_04e].f_22, 0)[i] != -1)
                        fn_10_6d52(g_13dc, g_3d48 + 0x3b,
                                   i * 25 + g_3d4a + g_3ca8.bottom + 0x16,
                                   g_3ca8.right - 0x50, 10,
                                   g_7090[g_952e].f_026[i] = 100);
                g_9532 = 0;
            }
            fn_16_2144();
        }
        if (g_9563) {
            fn_09_95f4(0x362);
            g_914a++;
            break;
        }
        g_914a = 0x16;
        break;
    }
    case 5: case 9: case 16: case 23: case 34: case 39: case 42: case 55:
    case 57: case 62:
        fn_16_2e3c(0, 1);
        break;
    case 22:
        if (g_953e) {
            fn_10_a332(ambulance_line, (char *)0x497, 1, 0x9d4);
            g_914a++;
        } else
            g_914a = 0x19;
        break;
    case 24:
        if (g_1c48 < g_1e50) {
            for (i = 0; i < 3; i++)
                VIEWP(signed char *, g_6e24[g_931c].f_32, 0)[i + 6] = 100;
            g_1c48 = g_1e50 + 50;
            flag = 1;
            for (i = 0; i < 3; i++)
                if (g_7090[g_952e].f_026[i] < 100
                    && VIEWP(int16_t *, g_96d2[g_7090[g_952e].f_04e].f_22, 0)[i] != -1) {
                    if (g_7090[g_952e].f_026[i]++ <= 100)
                        g_7090[g_952e].f_026[i]++;
                    else
                        g_7090[g_952e].f_026[i] = 100;
                    fn_10_6d52(g_13dc, g_3d48 + 0x3b,
                               i * 25 + g_3d4a + g_3ca8.bottom + 0x16,
                               g_3ca8.right - 0x50, 10, g_7090[g_952e].f_026[i]);
                    flag = 0;
                }
            if (flag)
                g_914a++;
        }
        break;
    case 25:
        if (g_953f) {
            fn_10_a332(ambulance_line, (char *)0x497, 1, 0x9d5);
            g_6e24[g_931c].f_73 = g_7090[main_ship].f_0ac = g_7090[main_ship].f_0ad = 1;
            g_6e24[g_931c].f_72 = g_6e24[g_931c].f_73;
            g_6e24[g_931c].f_74 = g_7090[main_ship].f_024 = g_7090[main_ship].f_00a;
            if (g_7090[main_ship].f_024 == 2)
                g_7090[main_ship].f_0e0 = g_7090[main_ship].f_0e1 = 1;
            VIEWP(signed char *, g_6e24[g_931c].f_32, 0)[9] = 100;
            g_914a++;
        } else
            g_914a = 0x1f;
        break;
    case 26:
        fn_16_2e3c(0, !g_953e);
        break;
    case 27:
        if (g_9598) {
            fn_15_4c76(1, 1);
            g_914a++;
        } else
            g_914a += 2;
        break;
    case 17:
        fn_15_4c76(1, 1);
        g_914a++;
        break;
    case 18: case 28:
        fn_15_4c76(0, 1);
        break;
    case 29:
        if (g_1c48 < g_1e50) {
            VIEWP(signed char *, g_6e24[g_931c].f_32, 0)[9] = 100;
            g_1c48 = g_1e50 + 50;
            flag = 1;
            i = 3;
            if (g_7090[g_952e].f_026[i] < 100
                && VIEWP(int16_t *, g_96d2[g_7090[g_952e].f_04e].f_22, 0)[i] != -1) {
                if (g_7090[g_952e].f_026[i]++ <= 100)
                    g_7090[g_952e].f_026[i]++;
                else
                    g_7090[g_952e].f_026[i] = 100;
                fn_10_6d52(g_13dc, g_3d48 + 0x3b,
                           i * 25 + g_3d4a + g_3ca8.bottom + 0x16,
                           g_3ca8.right - 0x50, 10, g_7090[g_952e].f_026[i]);
                flag = 0;
            }
            if (flag) {
                if (g_9598) {
                    fn_15_4c76(1, 0);
                    g_914a++;
                } else
                    g_914a += 2;
            }
        }
        break;
    case 20:
        fn_15_4c76(1, 0);
        g_914a++;
        break;
    case 21: case 30:
        fn_15_4c76(0, 0);
        break;
    case 31:
        if (g_953e || g_953f || g_9563) {
            fn_09_95f4(0x482);
            g_914a++;
        } else
            g_914a = 0x21;
        break;
    case 3: case 7: case 12: case 14: case 32: case 37:
        fn_16_2e3c(0, 0);
        goto brk;   /* layout-only: a jump via another case's break makes CL
                       keep this copy of the shared fn_16_2e3c(0, ...) tail */
    case 33:
        if (g_9540) {
            fn_10_a332(ambulance_line, (char *)0x9ec, 1, 0xe, g_952e, 1);
            g_914a++;
        } else
            g_914a = 0x26;
        break;
    case 35: {
        int32_t l;

        if (g_1c48 < g_1e50) {
            g_1c48 = g_1e50 + 50;
            flag = 1;
            i = 4;
            if (g_96d2[g_7090[main_ship].f_04e].f_1e > g_7090[g_952e].f_01e) {
                g_7090[g_952e].f_01e = min(g_96d2[g_7090[main_ship].f_04e].f_1e,
                                           g_7090[g_952e].f_01e + 16);
                fn_10_6d52(g_13dc, g_3d48 + 0x3b,
                           i * 25 + g_3d4a + g_3ca8.bottom + 0x16,
                           g_3ca8.right - 0x50, 10,
                           (int16_t)(l = (int32_t)g_7090[main_ship].f_01e * 100
                                 / g_96d2[g_7090[main_ship].f_04e].f_1e));
                flag = 0;
            }
            if (flag)
                g_914a++;
        }
        break;
    }
    case 19:
        g_914a++;
        break;
    case 36:
        fn_10_a332(ambulance_line, (char *)0x498, 1, 1);
        g_914a++;
        break;
    case 38:
        g_1c50 = g_1c4c = 1;
        if (g_9541) {
            fn_10_a332(ambulance_line, (char *)0x4a1, 1, 1);
            lstrcat(ambulance_line, g_111a);
            g_1c50 = 0;
            g_914a++;
        } else
            g_914a = 0x29;
        break;
    case 40:
        t0 = GetCurrentTime();
        do
            ;
        while (GetCurrentTime() - t0 < 800);
        g_914a++;
        break;
    case 41:
        if (g_957f) {
            fn_09_95f4(0x7b3);
            lstrcat(ambulance_line, g_111a);
            g_1c50 = 0;
            g_914a++;
        } else
            g_914a = 0x2c;
        break;
    case 43:
        t0 = GetCurrentTime();
        fn_10_744c(0x22);
        do
            fn_10_740c();
        while (GetCurrentTime() - t0 < 800);
        g_914a++;
        break;
    case 44:
        g_1c52 = 1;
        g_1c4e = 0;
        g_914a++;
        break;
    case 45:
        if (g_955d[g_1c4e]) {
            fn_10_a332(ambulance_line, (char *)0x7b4, 1, g_1c4e + 0x7b5);
            g_914a++;
        } else if (g_1c4e == 5)
            g_914a = 0x30;
        else
            g_1c4e++;
        break;
    case 46:
        fn_16_2e3c(0, g_1c52);
        break;
    case 47:
        g_1c52 = 0;
        t0 = GetCurrentTime();
        do
            fn_10_740c();
        while (GetCurrentTime() - t0 < 800);
        if (g_1c4e < 5) {
            g_1c4e++;
            g_914a = 0x2d;
        } else
            g_914a++;
        break;
    case 48:
        if (g_9564[g_1c4c]) {
            fn_10_a332(ambulance_line, (char *)0x4af, 1, g_1c4c + 0xba);
            g_914a++;
        } else
            g_914a = 0x32;
        break;
    case 50:
        if (g_1c4c < 0x1a) {
            if (g_9564[g_1c4c]) {
                t0 = GetCurrentTime();
                while (GetCurrentTime() - t0 < 800)
                    ;
            }
            g_1c4c++;
            g_914a = 0x30;
        } else {
            g_914a++;
            g_1c4c = 1;
        }
        break;
    case 51: {
        int16_t found;

        if (g_9542[g_1c4c]) {
            found = 0;
            for (j = 0; j < 10; j++)
                if (g_7090[main_ship].f_0b8[j] == g_1c4c) {
                    found = 1;
                    break;
                }
            if (found)
                fn_10_a332(ambulance_line, (char *)0x49e, 1, g_1c4c + 0xba);
            else
                fn_10_a332(ambulance_line, (char *)0x49d, 1, g_1c4c + 0xba);
            g_914a++;
        } else
            g_914a = 0x35;
        break;
    }
    case 49: case 52:
        fn_16_2e3c(0, g_1c50);
        g_1c50 = 0;
        break;
    case 53:
        if (g_1c4c < 0x1a) {
            if (g_9542[g_1c4c]) {
                t0 = GetCurrentTime();
                while (GetCurrentTime() - t0 < 800)
                    ;
            }
            g_1c4c++;
            g_914a = 0x33;
        } else
            g_914a++;
        break;
    case 54:
        if (!g_9e5d)
            g_914a = 0x38;
        else {
            fn_06_1010(g_9e5d, 100, 2, buf);
            fn_10_a332(ambulance_line, (char *)0x487, 1, (LPSTR)buf);
            g_914a++;
        }
        break;
    case 56:
        if (!g_9e55)
            g_914a = 0x3a;
        else {
            fn_06_1010(g_9e55, 100, 2, buf);
            fn_10_a332(ambulance_line, (char *)0x49b, 1, (LPSTR)buf);
            g_914a++;
        }
        break;
    case 58:
        if (!g_9e55 && !g_9e5d) {
            g_1c48 = 0;
            g_914a = 0x3c;
        } else {
            g_7090[g_952e].f_0dc += g_9e5d;
            g_7090[g_952e].f_0dc -= g_9e55;
            g_9e55 = 0;
            fn_06_0f54(g_7090[g_952e].f_0dc, 100, 2, buf);
            fn_10_a332(ambulance_line, (char *)0x486, 1, (LPSTR)buf);
            g_914a++;
        }
        break;
    case 59:
        fn_16_2e3c(0, 0);
        g_1c48 = 0;
        break;
    case 60:
        if (g_1c48 == 0) {
            if (g_93a6)
                g_1c48 = GetCurrentTime() + 6000;
            else
                g_1c48 = GetCurrentTime() + 1000;
        } else if (g_1c48 < g_1e50)
            g_914a++;
        break;
    case 61:
        if (g_93a6)
            fn_09_95f4(0x7e6);
        else
            fn_09_95f4(0x49c);
        lstrcat(ambulance_line, g_111a);
        fn_15_0cb0();
        g_914a++;
        break;
    case 63:
        fn_15_10be();
        break;
    case 64:
        PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
        fn_15_1328(0);
        fn_16_1f24();
        fn_10_6dd4(0);
        fn_10_6e76(8L);
        if (g_93a6)
            g_90f4 = 9;
        else
            g_90f4 = 1;
        fn_16_631c();
        g_0928 = 0;
        if (g_93a6 == 1) {
            sprite_dc_restore();
            g_92be = 0;
            fn_16_7210();
            break;
        }
        g_9e4b = 0x4b0;
        g_1df8[g_9324][g_952e].f_18 = 1;
        g_1df8[7]->f_18 = 1;
        g_6da8 = g_1e50 + 3000;
        sprite_dc_restore();
        if (g_9662) {
            g_92e4 = 1;
            fn_18_07b2();
            g_92e4 = 0;
        }
        pt = g_1df8[7]->f_04;
        do {
            ok = 1;
            SetRect(&rc, pt.x - 800, pt.y - 1200, pt.x + 2240, pt.y + 1200);
            for (i = 0; i <= g_9324; i++) {
                if (i != 7)
                    for (j = 0; j < g_9406[i]; j++) {
                        if (i == g_9324 && j == g_952e)
                            continue;
                        if (PtInRect(&rc, g_1df8[i][j].f_04) || pt.x < 0x410
                            || pt.y < 0x2d0
                            || (int16_t)((LO16(g_05a0) - 0x82) * 8) < pt.x
                            || (int16_t)((HI16(g_05a0) - 0x5a) * 8) < pt.y) {
                            ok = 0;
                            break;
                        }
                    }
                if (!ok)
                    break;
            }
            if (!ok) {
                pt.x += (rand() % 150 + 100) * 8;
                pt.y += (rand() % 150 + 100) * 8;
                if ((int16_t)(LO16(g_05a0) * 8) < pt.x)
                    pt.x = 0;
                if ((int16_t)(HI16(g_05a0) * 8) < pt.y)
                    pt.y = 0;
            }
        } while (!ok);
        g_1df8[g_9324][g_952e].f_04 = pt;
        g_1df8[7]->f_04 = pt;
        g_1df8[g_9324][g_952e].f_00 = fn_08_29ea(pt);
        (*g_1df8[7]).f_00 = g_1df8[g_9324][g_952e].f_00;
        g_1df8[g_9324][g_952e].f_04.x += 8;
        g_1df8[g_9324][g_952e].f_00.x++;
        fn_13_65f2(2);
        if (flow_interactive)
            SetCursorPos(g_1d48, g_0010);
        g_073e = 0;
        if (g_9220 == 1 || g_9220 != 2)
            fn_10_7480(1, 1);
        else
            fn_10_7480(2, 1);
        fn_16_0872();
        fn_11_0afe();
        break;
    }
    if (g_958a || g_914a == -1 || g_93a6 && g_914a >= 2) {
        g_05a8++;
        g_1e68++;
        fn_16_64fa();
    }
}

/* 16:1f78 */
void fn_16_1f78(void)
{
    HDC hdc;
    HBITMAP old;
    int16_t h;
    HPALETTE oldpal;

    g_3ca8.top = g_3ca8.left = 0;
    g_3ca8.right = (LO16(g_90ea) - g_3ce6) / 2 - 20;
    g_3ca8.right = min(g_3ca8.right, 260);
    g_3ca8.bottom = 200;
    g_3d48 = LO16(g_90ea) - g_3ca8.right;
    g_3d4a = min(g_0010 * 2 / 5, g_0010 - 370);
    g_6dac = g_3ca8.right;
    g_6db2 = g_6db6 = g_3d4a;
    if (LO16(g_90ea) > 700)
        g_6db6 = g_6db2 = g_3d4a - 10;
    g_6dae = max(g_0010 / 2, 370);
    g_6db0 = min(LO16(g_90ea) / 13 + LO16(g_90ea) / 2 + 90, LO16(g_90ea) - g_6dac);
    g_6db4 = max(LO16(g_90ea) / 2 - LO16(g_90ea) / 13 - g_6dac - 90, 0);
    g_3d48 = g_6db0;
    g_3d4a = g_6db2;
    fn_16_27ea();
    fn_16_2144();
    h = (g_1df8[14][main_ship].f_22 << 3) >> g_959e;
    if (g_953c == 0)
        g_953c = CreateCompatibleBitmap(g_13dc, g_3ce6, h + 0x43);
    hdc = CreateCompatibleDC(g_13dc);
    if (g_920e)
        oldpal = SelectPalette(hdc, g_920e, 0);
    old = SelectObject(hdc, g_953c);
    PatBlt(hdc, 0, 0, g_3ce6, h + 0x43, BLACKNESS);
    BitBlt(hdc, 0, 5, g_3ce6, h + 0x3e, g_13dc, LO16(g_90ea) / 2 - g_3ce6 / 2,
           g_0010 - h - 0x3e, SRCCOPY);
    SelectObject(hdc, old);
    if (oldpal)
        SelectPalette(hdc, oldpal, 0);
    DeleteDC(hdc);
}

/* 16:27ea */
void fn_16_27ea(void)
{
    HBITMAP bmp;
    HBITMAP oldbm;
    HDC dc;
    HPEN oldpen;
    RECT r;
    int16_t i;
    int16_t t;
    HPALETTE oldpal;

    g_6e18.x = 12;
    g_6e18.y = 10;
    t = 20;
    g_6e14.x = g_3ca8.right - 30;
    g_6e14.y = g_3ca8.bottom - 36;
    if (g_93a6) {
        g_6da4->f_02 = g_6e14;
        g_88c0 = g_6da4->f_02;
    }
    g_95a0 = CreateCompatibleDC(g_13dc);
    g_9590 = CreateCompatibleBitmap(g_13dc, g_3ca8.right, g_3ca8.bottom);
    g_9592 = SelectObject(g_95a0, g_9590);
    if (g_920e)
        g_9594 = SelectPalette(g_95a0, g_920e, 0);
    FillRect(g_95a0, (LPRECT)&g_3ca8.left, GetStockObject(LTGRAY_BRUSH));
    SetRect(&r, g_6e18.x + g_3ca8.left, g_6e18.y, g_3ca8.right - g_6e18.x, g_6e18.y + 3);
    FillRect(g_95a0, &r, GetStockObject(DKGRAY_BRUSH));
    SetRect(&r, g_6e18.x + g_3ca8.left, g_3ca8.bottom - t - 3, g_3ca8.right - g_6e18.x, g_3ca8.bottom - t);
    FillRect(g_95a0, &r, GetStockObject(WHITE_BRUSH));
    SetRect(&r, g_3ca8.right - g_6e18.x - 3, g_6e18.y, g_3ca8.right - g_6e18.x, g_3ca8.bottom - t);
    FillRect(g_95a0, &r, GetStockObject(WHITE_BRUSH));
    SetRect(&r, g_6e18.x + g_3ca8.left, g_6e18.y, g_6e18.x + g_3ca8.left + 3, g_3ca8.bottom - t);
    FillRect(g_95a0, &r, GetStockObject(DKGRAY_BRUSH));
    SetRect(&r, g_3ca8.left, 0, g_3ca8.right, 2);
    FillRect(g_95a0, &r, GetStockObject(WHITE_BRUSH));
    SetRect(&r, g_3ca8.left, 0, g_3ca8.left + 2, g_3ca8.bottom);
    FillRect(g_95a0, &r, GetStockObject(WHITE_BRUSH));
    SetRect(&r, g_3ca8.right - 2, 0, g_3ca8.right, g_3ca8.bottom);
    FillRect(g_95a0, &r, GetStockObject(DKGRAY_BRUSH));
    SetRect(&r, g_3ca8.left, g_3ca8.bottom - 2, g_3ca8.right, g_3ca8.bottom);
    FillRect(g_95a0, &r, GetStockObject(DKGRAY_BRUSH));
    oldpen = SelectObject(g_95a0, GetStockObject(WHITE_PEN));
    MoveTo(g_95a0, g_6e18.x + g_3ca8.left + 28, g_3ca8.bottom - 15);
    LineTo(g_95a0, g_6e18.x + g_3ca8.left + 28, g_3ca8.bottom - 8);
    LineTo(g_95a0, g_6e18.x + g_3ca8.left, g_3ca8.bottom - 8);
    SelectObject(g_95a0, CreatePen(PS_SOLID, 1, RGB(128, 128, 128)));
    LineTo(g_95a0, g_6e18.x + g_3ca8.left, g_3ca8.bottom - 15);
    LineTo(g_95a0, g_6e18.x + g_3ca8.left + 28, g_3ca8.bottom - 15);
    DeleteObject(SelectObject(g_95a0, oldpen));
    bmp = fn_10_6c02(250, 0, -1);
    dc = CreateCompatibleDC(g_13dc);
    if (g_920e)
        oldpal = SelectPalette(dc, g_920e, 0);
    oldbm = SelectObject(dc, bmp);
    BitBlt(g_95a0, g_6e18.x + g_3ca8.left + 1, g_3ca8.bottom - 14, 27, 6, dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldbm);
    if (oldpal)
        SelectPalette(dc, oldpal, 0);
    DeleteDC(dc);
    DeleteObject(bmp);
    oldpen = SelectObject(g_95a0, GetStockObject(WHITE_PEN));
    MoveTo(g_95a0, g_3ca8.right - g_6e18.x, g_3ca8.bottom - 17);
    LineTo(g_95a0, g_3ca8.right - g_6e18.x, g_3ca8.bottom - 7);
    LineTo(g_95a0, g_3ca8.right - g_6e18.x - 15, g_3ca8.bottom - 7);
    SelectObject(g_95a0, CreatePen(PS_SOLID, 1, RGB(128, 128, 128)));
    LineTo(g_95a0, g_3ca8.right - g_6e18.x - 15, g_3ca8.bottom - 17);
    LineTo(g_95a0, g_3ca8.right - g_6e18.x, g_3ca8.bottom - 17);
    DeleteObject(SelectObject(g_95a0, oldpen));
    bmp = fn_10_6d38("CORNER");
    dc = CreateCompatibleDC(g_13dc);
    oldbm = SelectObject(dc, bmp);
    BitBlt(g_95a0, g_6e18.x + g_3ca8.left, g_3ca8.bottom - t - 3, 3, 3, dc, 5, 0, SRCCOPY);
    BitBlt(g_95a0, g_3ca8.right - g_6e18.x - 3, g_6e18.y, 3, 3, dc, 5, 0, SRCCOPY);
    SelectObject(dc, oldbm);
    DeleteDC(dc);
    DeleteObject(bmp);
    PatBlt(g_95a0, g_6e18.x + g_3ca8.left + 3, g_6e18.y + g_3ca8.top + 3,
           g_6e14.x, g_6e14.y, BLACKNESS);
    if (g_93a6)
        BitBlt(g_95a0, g_6e18.x + g_3ca8.left + 6, g_6e18.y + g_3ca8.top + 6,
               g_6e14.x - 6, g_6e14.y - 6, g_13dc, g_6db4 + 3, g_3d4a + 3,
               SRCCOPY);
    for (i = 0; i < 3; i++)
        if ((&g_9534[0])[i]) {
            DeleteObject((&g_9534[0])[i]);
            (&g_9534[0])[i] = 0;
        }
    g_9534[0] = CreateRectRgn(g_6e18.x + g_3d48 + 3, g_6e18.y + g_3d4a + 3,
                           g_6e18.x + g_6e14.x + g_3d48 + 3,
                           g_6e18.y + g_6e14.y + g_3d4a + 3);
    SetRect(&demon_host_rect, g_6db4 + g_6e18.x + 3, g_6e18.y + g_3d4a + 3,
            g_6db4 + g_6e18.x + g_6e14.x + 3, g_6e18.y + g_6e14.y + g_3d4a + 3);
    g_9534[1] = CreateRectRgn(demon_host_rect.left, demon_host_rect.top, demon_host_rect.right, demon_host_rect.bottom);
    g_9534[2] = CreateRectRgn(0, 0, LO16(g_90ea), g_0010);
    if (!g_93a6)
        g_952c = fn_16_619e();
}

/* 16:2144 */
void fn_16_2144(void)
{
    HPEN pen;
    HBRUSH oldbr;
    HBITMAP oldbm2;
    HBITMAP oldbm;
    HDC dc2;
    HDC dc;
    HDC hdc;
    HPALETTE oldpal;
    int16_t i;
    int16_t sy;
    int16_t v;
    int16_t u;
    int16_t h;

    hdc = g_9580 ? g_9580 : g_13dc;
    oldbr = SelectObject(hdc, g_500a);
    PatBlt(hdc, g_6db0, g_6db2, g_6dac, g_6dae, PATCOPY);
    SelectObject(hdc, oldbr);
    fn_10_6da6(1, 0);
    fn_10_6e76(0x20000L);
    for (i = 40; i < 228; i += 4)
        fn_10_6d7a(i, i, i);
    fn_10_6e4c();
    fn_15_454c();
    fn_10_6e76(0x10000L);
    fn_10_6dd4(1);
    pen = SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
    MoveTo(hdc, g_6db0 + g_6dac, g_6db2);
    LineTo(hdc, g_6db0, g_6db2);
    LineTo(hdc, g_6db0, g_6db2 + g_6dae);
    LineTo(hdc, g_6db0 + g_6dac, g_6db2 + g_6dae);
    DeleteObject(SelectObject(hdc, pen));
    oldbr = SelectObject(hdc, g_500a);
    PatBlt(hdc, g_6db4, g_6db6, g_6dac, g_6dae, PATCOPY);
    SelectObject(hdc, oldbr);
    pen = SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
    MoveTo(hdc, g_6db4, g_6db6);
    LineTo(hdc, g_6db4 + g_6dac, g_6db6);
    LineTo(hdc, g_6db4 + g_6dac, g_6db6 + g_6dae);
    LineTo(hdc, g_6db4, g_6db6 + g_6dae);
    DeleteObject(SelectObject(hdc, pen));
    BitBlt(hdc, g_6db4, g_3d4a, g_3ca8.right, g_3ca8.bottom, g_95a0, 0, 0, SRCCOPY);
    PatBlt(g_95a0, g_6e18.x + g_3ca8.left + 3, g_6e18.y + g_3ca8.top + 3,
           g_6e14.x, g_6e14.y, BLACKNESS);
    BitBlt(hdc, g_3d48, g_3d4a, g_3ca8.right, g_3ca8.bottom, g_95a0, 0, 0, SRCCOPY);
    if (g_953a) {
        dc = CreateCompatibleDC(g_13dc);
        oldbm = SelectObject(dc, g_953a);
        BitBlt(hdc, g_6e18.x + g_3d48 + 7, g_6e18.y + g_3d4a + 7,
               g_6e14.x - 4, g_6e14.y - 4, dc, 0, 0, SRCCOPY);
        SelectObject(dc, oldbm);
        DeleteDC(dc);
    }
    PatBlt(hdc, g_6db4 + g_6e18.x + 7, g_6db6 + g_6e18.y + 7,
           g_6e14.x - 4, g_6e14.y - 4, BLACKNESS);
    dc2 = CreateCompatibleDC(g_13dc);
    oldbm2 = SelectObject(dc2, g_5030[0]);
    fn_10_949c(hdc, g_3d48 + 4, g_3d4a + g_3ca8.bottom + 15, g_3ca8.right - 20, 0x80, 1);
    for (i = 0; i < 5; i++) {
        if (i == 3) {
            if (g_7090[main_ship].f_0e9)
                v = 5;
            else if (g_7090[main_ship].f_0e7)
                v = 4;
            else
                v = VIEWP(int16_t *, g_96d2[g_7090[main_ship].f_04e].f_22, 0)[i];
            if (VIEWP(int16_t *, g_96d2[g_7090[main_ship].f_04e].f_22, 0)[i] == -1)
                sy = 0;
            else
                sy = (v + 1) * 11;
        } else if (i == 4) {
            sy = v = 0;
        } else {
            v = VIEWP(int16_t *, g_96d2[g_7090[main_ship].f_04e].f_22, 0)[i];
            sy = (v + 1) * 11;
        }
        if (i != 3 || sy != 0) {
            BitBlt(hdc, g_3d48 + 8, i * 25 + g_3d4a + g_3ca8.bottom + 23, 32, 11,
                   dc2, 0, sy, SRCCOPY);
            fn_10_949c(hdc, g_3d48 + 57, i * 25 + g_3d4a + g_3ca8.bottom + 20,
                       g_3ca8.right - 76, 14, 0);
        }
        if (i != 4) {
            if (i != 3 || sy != 0)
                fn_10_6d52(hdc, g_3d48 + 59, i * 25 + g_3d4a + g_3ca8.bottom + 22,
                               g_3ca8.right - 80, 10, g_7090[main_ship].f_026[i]);
        } else
            fn_10_6d52(hdc, g_3d48 + 59, i * 25 + g_3d4a + g_3ca8.bottom + 22,
                       g_3ca8.right - 80, 10,
                       h = 100L * g_7090[main_ship].f_01e
                           / g_96d2[g_7090[main_ship].f_04e].f_1e);
    }
    SelectObject(dc2, oldbm2);
    DeleteDC(dc2);
    if (g_953c) {
        h = (g_1df8[14][main_ship].f_22 << 3) >> g_959e;
        if (g_914a >= 63 || (g_914a == -1 && g_958c >= 63)) {
            BitBlt(hdc, LO16(g_90ea) / 2 - g_3ce6 / 2, g_0010 - g_3c9a - 52,
                   g_3ce6, g_3c9a + 52, g_92b6, 0, 0, SRCCOPY);
        } else {
            dc = CreateCompatibleDC(g_13dc);
            if (g_920e)
                oldpal = SelectPalette(dc, g_920e, 0);
            oldbm = SelectObject(dc, g_953c);
            BitBlt(hdc, LO16(g_90ea) / 2 - g_3ce6 / 2, g_0010 - h - 62,
                   g_3ce6, h + 62, dc, 0, 5, SRCCOPY);
            SelectObject(dc, oldbm);
            if (oldpal)
                SelectPalette(dc, oldpal, 0);
            DeleteDC(dc);
        }
    }
    if (g_9580) {
        if (g_93a6) {
            if (g_8ffc < 300)
                fn_07_13b2(2, 0x15, 0);
            else
                for (i = 0; i < 4; i++)
                    fn_07_13b2(2, i + 0x16, 0);
        }
        for (i = 0; i < 120; i++)
            fn_07_158e();
        BitBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, g_9580, 0, 0, SRCCOPY);
        SelectObject(g_9580, g_9586);
        if (g_920e)
            SelectPalette(g_9580, g_9582, 0);
        DeleteObject(g_9584);
        DeleteDC(g_9580);
        g_9580 = g_9584 = 0;
    }
    if (g_952c)
        fn_16_64fa();
}

/* 16:5f78 */
void fn_16_5f78(int16_t i, int16_t v)
{
    int16_t a;
    int16_t b;
    int16_t n;
    int16_t k;
    int16_t t;
    int16_t q;
    BITMAP bm;

    fn_10_0552(i + 40, 1);
    k = g_7090[i].f_0d6;
    g_6e24[k].f_00 = v;
    t = g_6e24[k].f_00;
    n = g_7090[i].f_04e;
    fn_14_1b84(i, n, k, t);
    g_7090[i].f_01e = g_6e24[k].f_1c * 40;
    g_7090[i].f_0ac = g_7090[i].f_0ad = 1;
    fn_14_11a8(i);
    a = g_6e24[k].f_7a;
    g_96d2[n].f_2a = a;
    b = g_6e24[k].f_7b;
    if (g_9156 == 0 && (a & 1)) {
        a++;
        b = 4;
    }
    g_1df8[g_9324][i].f_22 = (a << g_9156) >> 1;
    g_1df8[g_9324][i].f_24 = (b << g_9156) >> 1;
    SelectObject(g_3a38[i], g_39c4[i]);
    GetObject(g_3b20[i], sizeof(BITMAP), &bm);
    SelectObject(g_3a38[i], g_3b20[i]);
    q = (int16_t)(bm.bmHeight - g_1df8[g_9324][i].f_24) /
        (int16_t)(g_1df8[g_9324][i].f_22 + g_1df8[g_9324][i].f_24);
    g_1df8[g_9324][i].f_20 = a << 3;
    g_7090[i].f_05b = q - 1;
    g_96d2[n - 1 + 1].f_02 = g_96d2[n - 1 + 1].f_00 = a / 2;
    if (g_96d2[n - 1 + 1].f_04 < 0)
        g_96d2[n - 1 + 1].f_04 = 4 - g_96d2[n - 1 + 1].f_04 - a / 2;
    fn_10_5d3c(i);
    fn_10_1460(n);
    fn_10_1620(n);
    fn_10_1502(n);
    g_1df8[g_9324][i].f_3a = g_3a38[i];
}

/* 16:6928 */
void fn_16_6928(int16_t a)
{
    char unused[96];
    DWORD t;

    if ((GetKeyState(VK_CONTROL) & 0x8000) && g_92a2 != 1)
        g_0928 = 1;
    if (g_8f70 > 1)
        g_0928 = 1;
    if (a != 0 && (g_929c > 1 || g_92a2 >= 1))
        fn_15_0760();
    switch (g_929c) {
    case 0:
        fn_11_02f0();
        fn_15_302e();
        g_929c++;
        break;
    case 1:
        fn_15_3590();
        break;
    case 2:
        fn_16_6afe();
        g_929c++;
        break;
    case 4:
        t = GetCurrentTime();
        do
            fn_10_740c();
        while (GetCurrentTime() < t + 1500);
        g_929c++;
        break;
    case 5:
        fn_15_1584(0);
        g_1c64 = 0;
        break;
    case 6:
        if (g_1c64 == 0)
            g_1c64 = GetCurrentTime() + 4000;
        if (GetCurrentTime() > g_1c64) {
            fn_15_0cb0();
            g_929c++;
        }
        break;
    case 3:
    case 7:
        fn_15_1584(0);
        break;
    case 8:
        t = GetCurrentTime();
        do
            fn_10_740c();
        while (GetCurrentTime() < t + 1500);
        g_929c++;
        break;
    case 9:
        fn_15_10be();
        break;
    case 10:
        PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
        t = GetCurrentTime();
        g_0928 = 0;
        fn_15_1328(0);
        do
            fn_10_740c();
        while (GetCurrentTime() - t < 2000);
        fn_10_6e76(8L);
        fn_10_6dd4(0);
        if (flow_interactive)
            fn_09_6cc4(1);
        else {
            g_90f4 = 1;
            g_93a4 = 0;
        }
        break;
    }
}

/* 16:6afe */
void fn_16_6afe(void)
{
    char buf[200];
    int16_t i;
    int16_t cnt;
    int16_t sum1;
    int16_t r;
    int16_t d;
    int16_t sum2;
    int32_t money;
    int16_t flag;
    int16_t j;

    g_92d4 = 0;
    g_93a8 = GlobalAlloc(GHND, 2000L);
    g_4fcc = GlobalLock(g_93a8);
    i = sum1 = 0;
    for (; i < 10; i++)
        sum1 += g_a14d[i];
    i = sum2 = 0;
    for (; i < 10; i++)
        sum2 += g_a157[i];
    g_7090[main_ship].f_0dc += g_7090[main_ship].f_0ce;
    g_7090[main_ship].f_0ce = 0;
    if (sum2 == 0)
        fn_10_a332(g_4fcc, (char *)0x38c, 1, (LPSTR)g_380c);
    else {
        fn_17_7ba6(sum1, buf);
        fn_10_a332(g_4fcc, (char *)0x38d, 1, (LPSTR)buf, g_91f8, 0x9d6, (LPSTR)g_380c);
    }
    if (sum2 == 0)
        fn_10_a332(g_4fcc, (char *)0x38f, 0);
    if (g_a161 < 0)
        LoadString(g_9212, 0x123, buf, 150);
    else {
        if (g_a161 == 8)
            LoadString(g_9212, 0x449, buf, 150);
        else
            LoadString(g_9212, 0x390, buf, 150);
        lstrcat(g_4fcc, buf);
        if (g_a161 == 9)
            LoadString(g_9212, 0x445, buf, 150);
        else
            LoadString(g_9212, g_a161 + 0x44a, buf, 150);
        lstrcat(g_4fcc, buf);
    }
    lstrcat(g_4fcc, g_09f2);
    fn_17_8e60(g_a162, buf);
    lstrcat(g_4fcc, buf);
    lstrcat(g_4fcc, " (");
    lstrcat(g_4fcc, g_96d2[g_7090[g_a162].f_04e].f_70);
    lstrcat(g_4fcc, ")");
    LoadString(g_9212, 0x391, buf, 150);
    lstrcat(g_4fcc, buf);
    fn_10_97ce(buf);
    lstrcat(g_4fcc, buf);
    lstrcat(g_4fcc, g_09ee);
    lstrcat(g_4fcc, "\r\n\r\n");
    LoadString(g_9212, 0x392, buf, 150);
    lstrcat(g_4fcc, buf);
    i = cnt = money = 0;
    for (; i < 10; i++) {
        d = g_a14d[i] - g_a157[i];
        if (d != 0) {
            flag = 0;
            if (cnt) {
                flag = 1;
                for (j = i + 1; j < 10; j++)
                    if (g_a157[j] != g_a14d[j])
                        flag = 0;
            }
            if (cnt && !flag)
                j = 1;
            else
                j = 0;
            fn_10_a332(g_4fcc, (char *)0xea, 0, flag, j, d, 0x9d7, i + 0x44a);
            cnt++;
            money += g_116a[i];
            if (d > 1)
                money += (d - 1) * (g_116a[i] / 5);
        }
    }
    lstrcat(g_4fcc, g_09ee);
    lstrcat(g_4fcc, "\r\n \r\n");
    LoadString(g_9212, 0x393, buf, 150);
    lstrcat(g_4fcc, buf);
    lstrcat(g_4fcc, g_09ee);
    lstrcat(g_4fcc, "\r\n\r\n");
    if (sum2 == 0 && money > 0) {
        money /= 3;
        money = money < 100 ? 100 : money;
        if (g_7090[main_ship].f_0dc > 0)
            money = g_7090[main_ship].f_0dc > money ? money : g_7090[main_ship].f_0dc;
    }
    if (g_7090[main_ship].f_0dc + 100 < money && money != 0) {
        if (g_7090[main_ship].cnt > 1) {
            money = 0;
            r = fn_16_71a2(main_ship, 1);
        } else
            money /= 2;
    }
    g_7090[main_ship].f_0dc -= money;
    fn_17_7ba6(sum1, buf);
    fn_10_a332(g_4fcc, (char *)0x2d3, 0, (LPSTR)buf);
    if ((money != 0 || r < 0 || r > 27) && money != 0) {
        fn_06_1010((int16_t)money, 100, 2, buf);
        fn_10_a332(g_4fcc, (char *)0x2d5, 0, (LPSTR)buf);
    } else if (r > 0 && r <= 27)
        fn_10_a332(g_4fcc, (char *)0x2d6, 0, r + 0xba);
    else
        fn_10_a332(g_4fcc, (char *)0x276, 0, (g_a157[9] > 3 ? 3 : g_a157[9]) + 0x278);
    lstrcat(g_4fcc, g_09ee);
    lstrcat(g_4fcc, "\r\n\r\n");
    fn_06_0f54(g_7090[main_ship].f_0dc, 100, 2, buf);
    fn_10_a332(g_4fcc, (char *)0x486, 0, (LPSTR)buf);
    lstrcat(g_4fcc, "\r\n \r\n");
    if (money == 0 && (r <= 0 || r > 27)) {
        if (g_a157[9] < 4)
            LoadString(g_9212, 0x27c, buf, 150);
        else
            LoadString(g_9212, 0x27d, buf, 150);
    } else
        LoadString(g_9212, 0x394, buf, 150);
    lstrcat(g_4fcc, buf);
    lstrcat(g_4fcc, g_09f2);
    lstrcat(g_4fcc, g_380c);
    lstrcat(g_4fcc, g_09ee);
    if (sum2) {
        LoadString(g_9212, rand() % 4 + 0x35c, buf, 150);
        lstrcat(g_4fcc, buf);
    }
    for (i = 0; i < 10; i++)
        g_a157[i] = g_a14d[i];
    fn_11_3fd4(g_4fcc, 1);
    fn_15_1584(1);
}

/* WM_INITDIALOG handler of dialog 16:4104 [inferred]. */
/* 16:51d6 */
void fn_16_51d6(HWND hDlg)
{
    int16_t unused0;
    char buf[120];
    int16_t unused1;
    int16_t w;
    int16_t h;
    int16_t unused2;
    int16_t unused3;
    int16_t y;
    int16_t unused4;
    RECT rc;

    g_9532 = hDlg;
    GetWindowRect(hDlg, &rc);
    w = rc.right - rc.left;
    h = rc.bottom - rc.top;
    y = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2 - 150;
    if (y < 50)
        y = 50;
    MoveWindow(hDlg, GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2, y, w, h, TRUE);
    SendMessage(GetDlgItem(hDlg, 0x65), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x66), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x67), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x68), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6b), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6c), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6d), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6e), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x70), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x71), WM_SETFONT, g_90fe, 1L);
    g_9e57 = g_7090[g_952e].f_0dc;
    g_9e55 = 0;
    fn_16_5820(hDlg);
    fn_06_0f54(g_7090[g_952e].f_0dc, 100, 2, buf);
    lstrcat(buf, " ");
    fn_09_9580(0x30e3, buf);
    SetWindowText(GetDlgItem(hDlg, 0x6e), buf);
    fn_16_4bd8(hDlg);
    fn_16_43f2(hDlg);
    SetFocus(GetDlgItem(hDlg, 0x65));
    if (flow_interactive == 0 || g_9e5b == 0)
        PostMessage(hDlg, WM_COMMAND, 0x69, 0L);
}

/* 16:4bd8 */
void fn_16_4bd8(HWND hDlg)
{
    HWND hList;
    char buf2[60];
    char buf[60];
    int16_t i;
    int16_t u1;
    int16_t u2;
    int16_t v;
    int16_t kind;
    int16_t u3;
    int16_t cnt;
    int16_t n;
    int16_t k;
    int16_t val;
    int16_t z;
    int16_t f2;
    int16_t f1;

    hList = GetDlgItem(hDlg, 0x65);
    SendMessage(hList, WM_SETREDRAW, 0, 0L);
    SendMessage(hList, 0x405, 0, (LPARAM)(LPSTR)"");
    if (g_9e5b == 0 && (g_11aa || g_920c != 3)) {
        fn_09_955c(0x361, buf);
        fn_16_5762(hList, v = 600, 2, buf);
    } else {
        if (flow_interactive && (g_11aa || g_920c != 3)) {
            fn_09_955c(0x361, buf);
            fn_16_5762(hList, v = 600, 0, buf);
        }
        i = v = 0;
        for (; i < 3; i++)
            v += 100 - g_7090[main_ship].f_026[i];
        if (flow_interactive || v > 100) {
            lstrcpy(buf, "");
            if (flow_interactive == 0)
                k = 2;
            else
                k = 1;
            if (g_9e57 < -350)
                k = 0;
            fn_09_9580(0x9d4, buf);
            fn_16_5762(hList, v, k, buf);
        }
    }
    if (flow_interactive || g_96d2[g_7090[main_ship].f_04e].f_1e / 4 > g_7090[main_ship].f_01e) {
        v = (g_96d2[g_7090[main_ship].f_04e].f_1e - g_7090[main_ship].f_01e) / 7;
        fn_10_a332(buf2, (char *)0x498, 1, 0);
        if (flow_interactive == 0)
            k = 2;
        else
            k = 1;
        fn_16_5762(hList, v, k, buf2);
    }
    if (g_9e57 > -350 && g_9e5b && flow_interactive) {
        if (g_7090[main_ship].f_0e5 && (!g_7090[main_ship].f_0ac || !g_7090[main_ship].f_0ad))
            k = 1;
        else
            k = 0;
        i = 3;
        if (VIEWP(int16_t *, g_96d2[g_7090[main_ship].f_04e].f_22, 0)[i] != -1)
            v = 100 - g_7090[main_ship].f_026[i];
        if (g_7090[main_ship].f_0e9) {
            kind = 5;
            v += 100 - g_7090[main_ship].f_026[i];
        } else if (g_7090[main_ship].f_0e7) {
            kind = 4;
            v += 100 - g_7090[main_ship].f_026[i];
        } else
            kind = VIEWP(int16_t *, g_96d2[g_7090[main_ship].f_04e].f_22, 0)[i];
        if ((flow_interactive || v > 50 || k) && kind != -1) {
            lstrcpy(buf, "");
            if (VIEWP(int16_t *, g_96d2[g_7090[main_ship].f_04e].f_22, 0)[i] != -1) {
                fn_09_9580(0x480, buf);
                if (kind == 5 || kind == 4)
                    lstrcat(buf, "\\");
            }
            if (kind == 5)
                fn_09_9580(0x483, buf);
            else if (kind == 4)
                fn_09_9580(0x484, buf);
            fn_09_9580(0x481, buf);
            fn_16_5762(hList, v, 1, buf);
        }
    }
    if (g_7090[main_ship].f_00a != 2) {
        fn_10_a332(buf2, (char *)0x4a1, 1, 0);
        fn_16_5762(hList, v = 250, 0, buf2);
    }
    n = 0;
    for (i = 1; i <= g_7090[main_ship].cnt; i++)
        if (g_7090[main_ship].f_0b8[i] == 0x19 || g_7090[main_ship].f_0b8[i] == 0x18)
            n++;
    if (n == 2) {
        fn_09_955c(0x7b2, buf2);
        fn_16_5762(hList, v = 250, 0, buf2);
    }
    for (i = 0; i <= 5; i++) {
        if (VIEWP(signed char *, g_6e24[g_7090[main_ship].f_0d6].f_32, 0)[i] < 5
            && (i < 5 || g_96d2[g_7090[main_ship].f_04e].f_28 != -1)) {
            v = (VIEWP(signed char *, g_6e24[g_7090[main_ship].f_0d6].f_32, 0)[i] + 4) * 100;
            if (i > 1)
                v -= 200;
            fn_09_955c(0x7b1, buf2);
            fn_09_9580(i + 0x7b5, buf2);
            fn_16_5762(hList, v, 0, buf2);
        }
    }
    for (i = 1; i < 27; i++) {
        if (g_11aa || g_2f4c[i].f_3e == -1) {
            f1 = f2 = 0;
            k = 0;
            for (; k < g_7090[main_ship].cnt; k++) {
                if (g_7090[main_ship].f_0b8[k] == i) {
                    f1 = 1;
                    if (g_2f4c[g_7090[main_ship].f_0b8[k]].f_12)
                        f2 = 1;
                    break;
                }
            }
            val = f1 ? (20 - g_7090[main_ship].f_0ae[k]) * 10 : g_2f4c[i].f_3c;
            if (!f1 || f2) {
                lstrcpy(buf, "");
                if (f1)
                    fn_09_9580(0x4a2, buf);
                fn_09_9580(i + 0xba, buf);
                v = val;
                z = 0;
                if (!f1 || g_7090[main_ship].f_00a == 2 || flow_interactive)
                    fn_16_5762(hList, v, z, buf);
            }
        }
    }
    SendMessage(hList, WM_SETREDRAW, 1, 0L);
    cnt = (int16_t)SendMessage(hList, 0x40c, 0, 0L);
    cnt = cnt > 6 ? 6 : cnt;
    SendMessage(hList, 0x406, 1, 0L);
}

/* WM_INITDIALOG handler of dialog 16:42a2 [inferred]. */
/* 16:541c */
void fn_16_541c(HWND hDlg)
{
    HWND hList;
    char buf[120];
    int16_t i;
    int16_t w;
    int16_t h;
    int16_t v;
    int16_t unused1;
    int16_t y;
    int16_t unused2;
    RECT rc;
    int16_t k;
    int16_t price;
    int16_t q;
    int16_t owned;
    int16_t found;

    g_959c = hDlg;
    GetWindowRect(hDlg, &rc);
    w = rc.right - rc.left;
    h = rc.bottom - rc.top;
    y = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2 - 150;
    if (y < 50)
        y = 50;
    MoveWindow(hDlg, GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2, y, w, h, TRUE);
    SendMessage(GetDlgItem(hDlg, 0x65), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x66), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x67), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x68), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6b), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6c), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6d), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x6e), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x70), WM_SETFONT, g_90fe, 1L);
    SendMessage(GetDlgItem(hDlg, 0x71), WM_SETFONT, g_90fe, 1L);
    g_9e5d = 0;
    fn_16_5820(hDlg);
    fn_06_0f54(g_7090[g_952e].f_0dc, 100, 2, buf);
    lstrcat(buf, " ");
    fn_09_9580(0x30e3, buf);
    SetWindowText(GetDlgItem(hDlg, 0x6e), buf);
    hList = GetDlgItem(hDlg, 0x65);
    SendMessage(hList, WM_SETREDRAW, 0, 0L);
    SendMessage(hList, 0x405, 0, (LPARAM)(LPSTR)"");
    for (i = 1; i < 27; i++) {
        if (g_9564[i] != 0)
            continue;
        k = found = owned = 0;
        for (; k < 10; k++) {
            if (g_7090[main_ship].f_0b8[k] == i) {
                found = 1;
                if (g_2f4c[i].f_12 != 0)
                    owned = 1;
                break;
            }
        }
        if (found && (price = g_2f4c[i].f_3c) != 0) {
            if (owned) {
                q = g_7090[main_ship].f_0ae[k];
                price = (int16_t)(price * q) / 20;
            }
            lstrcpy(buf, "");
            fn_09_9580(i + 0xba, buf);
            v = price = price < 250 ? 250 : price;
            fn_16_5762(hList, v, 1, buf);
        }
    }
    SendMessage(hList, WM_SETREDRAW, 1, 0L);
    SendMessage(hList, 0x406, 1, 0L);
    fn_16_43f2(hDlg);
    SetFocus(GetDlgItem(hDlg, 0x65));
}

/* OK handler of dialog 16:4104: marks which list entries are chosen [inferred]. */
/* 16:5b24 */
void fn_16_5b24(HWND hDlg)
{
    int16_t i;
    int16_t j;
    int16_t n;
    char buf1[50];
    char buf2[50];
    char buf3[50];
    DWORD t;

    if (flow_interactive == 0) {
        t = GetCurrentTime();
        while (GetCurrentTime() - t < 1500)
            ;
    }
    g_9563 = g_9541 = g_957f = g_953e = g_9540 = g_953f = 0;
    for (j = 1; j < 27; j++)
        g_9542[j] = 0;
    for (j = 0; j <= 5; j++)
        g_955d[j] = 0;
    n = (int16_t)SendMessage(GetDlgItem(hDlg, 0x66), 0x40c, 0, 0L);
    for (i = 0; i < n; i++) {
        SendMessage(GetDlgItem(hDlg, 0x66), 0x40a, i, (LPARAM)(LPSTR)buf1);
        fn_09_955c(0x9d4, buf2);
        if (fn_16_5f0e(buf1, buf2)) {
            g_953e = 1;
            continue;
        }
        fn_10_a332(buf2, (char *)0x498, 1, 0);
        if (fn_16_5f0e(buf1, buf2)) {
            g_9540 = 1;
            continue;
        }
        fn_09_955c(0x481, buf3);
        if (fn_16_5f0e(buf1, buf3)) {
            g_953f = 1;
            continue;
        }
        fn_10_a332(buf3, (char *)0x4a1, 1, 0);
        if (fn_16_5f0e(buf1, buf3)) {
            g_9541 = 1;
            continue;
        }
        fn_09_955c(0x7b2, buf3);
        if (fn_16_5f0e(buf1, buf3)) {
            g_957f = 1;
            continue;
        }
        fn_09_955c(0x904, buf3);
        if (fn_16_5f0e(buf1, buf3)) {
            g_9563 = 1;
            continue;
        }
        for (j = 0; j <= 5; j++) {
            fn_09_955c(0x7b1, buf2);
            fn_09_9580(j + 0x7b5, buf2);
            if (fn_16_5f0e(buf1, buf2)) {
                g_955d[j] = 1;
                break;
            }
        }
        for (j = 1; j < 27; j++) {
            fn_09_955c(j + 0xba, buf2);
            if (fn_16_5f0e(buf1, buf2)) {
                g_9542[j] = 1;
                break;
            }
        }
    }
    g_9532 = 0;
    EndDialog(hDlg, 1);
}

/* 16:08e4 */
void self_destruct_ship(int16_t unused, int16_t i)
{
    int16_t k;
    int16_t j;
    int16_t dy;
    int16_t dx;

    if (g_7090[i].f_147 == 1 && subgame_active == 0)
        return;
    for (k = 0; k < 8; k++) {
        for (j = 0; j < 45; j++) {
            if (g_1e90[j].f_00 == -1) {
                if (k == 0)
                    g_1e90[j].f_0a = 5;
                else
                    g_1e90[j].f_0a = 1;
                g_1e90[j].f_00 = 1;
                g_1e90[j].f_10 = g_1e50 + k * 20;
                g_1e90[j].f_02 = 10;
                g_1e90[j].f_06 = g_9324;
                g_1e90[j].f_08 = i;
                if (k == 0) {
                    dy = 16;
                    dx = 16;
                } else {
                    dx = rand() % 60 - 12;
                    dy = rand() % 60 - 12;
                }
                g_5170[j].x = g_1df8[g_9324][i].f_00.x + dx;
                g_5170[j].y = g_1df8[g_9324][i].f_00.y + dy;
                g_5224[j].x = g_1df8[g_9324][i].f_04.x + 128;
                g_5224[j].y = g_1df8[g_9324][i].f_04.y + 128;
                g_9430++;
                break;
            }
        }
    }
    g_7090[i].f_0e2 = 1;
    g_1df8[g_9324][i].f_26 = 1;
    g_7090[i].f_084 = g_1e50 + 6000;
    fn_13_4710(i);
    g_7090[i].flag = 0;
    if (g_9320 == 7) {
        dx = 1;
        for (k = 0; k <= g_9316; k++) {
            if (k != main_ship && g_7090[k].flag != 0 && g_1df8[14][k].f_18 == 0)
                dx = 0;
        }
        if (i == main_ship)
            dx = 1;
        if (dx)
            g_6670[0].f_1a = -1;
    }
    fn_10_754a(0x45, g_9324, i, 1);
    if (i == main_ship) {
        if (flow_interactive) {
            g_1e84 = g_1e50 + 8000;
        } else {
            g_1e84 = 0;
            g_1e80 = g_1e50 + 8000;
            g_95a8 = 1;
        }
        g_5078 = flow_interactive == 0 ? g_5078 / 2 : g_5078 * 4 / 5;
        if (flow_interactive == 0 && g_951a == 0)
            fn_11_aece();
    }
    if (subgame_active == 0)
        fn_13_498e(i, 1);
}

/* Types the ambulance line (DS:6db8) into the demon host window [inferred]. */
/* 16:2e3c */
void fn_16_2e3c(int16_t a, int16_t b)
{
    HFONT oldfont;
    HFONT hfont;
    DWORD oldtext;
    DWORD oldbk;
    DWORD ext;
    int16_t i;
    int16_t n;
    int16_t h;
    RECT rc;
    RECT rc2;
    char word[80];
    int16_t wrap;
    int16_t margin;
    int16_t j;
    int16_t len;
    int16_t w;

    if (LO16(g_90ea) < 700)
        h = 12;
    else if (LO16(g_90ea) < 860)
        h = 13;
    else
        h = 14;
    n = 4;
    if (a) {
        fn_15_84b0(g_6e14.x / 2 + g_6e18.x + g_3d48 + 3, g_6e14.y / 2 + g_6e18.y + g_3d4a + 3);
        g_1c5c = 0;
        g_1c5e = 0;
        g_1c54.x = g_6e18.x + g_3d48 + 8;
        g_1c54.y = g_6e18.y + g_3d4a + 7;
        g_1c60 = g_1e50 + 500;
        return;
    }
    if (g_1c60 > g_1e50)
        return;
    g_1c60 = g_1e50 + 40;
    SelectClipRgn(g_13dc, g_9534[0]);
    hfont = CreateFont(h - 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    oldtext = SetTextColor(g_13dc, RGB(0, 255, 0));
    for (i = 0; i < n; i++) {
        wrap = 0;
        if (ambulance_line[g_1c5c] == ' ') {
            SetRect(&rc, g_6e18.x + g_3d48 + 6, g_6e18.y + g_3d4a + 7,
                    g_6e18.x + g_6e14.x + g_3d48 + 3, g_6e18.y + g_6e14.y + g_3d4a + 3);
            len = 0;
            j = g_1c5c;
            do {
                j++;
                word[++len] = ambulance_line[j];
            } while (ambulance_line[j] != 0 && ambulance_line[j] != ' ' && ambulance_line[j] != 13);
            word[len + 1] = 0;
            w = LOWORD(GetTextExtent(g_13dc, word, len)) + g_1c54.x;
            if (len > 5)
                margin = 9;
            else
                margin = 22;
            if ((int16_t)(rc.right - margin) < w)
                wrap = 1;
        }
        if (ambulance_line[g_1c5c] == 0 || wrap) {
            g_1c54.x = g_6e18.x + g_3d48 + 8;
            if (ambulance_line[g_1c5c] == 0) {
                g_914a++;
                g_1c5c = 0;
            }
            g_1c5e++;
            if (g_6e18.y + g_6e14.y + g_3d4a - 13 <= g_1c54.y) {
                SetRect(&rc, g_6e18.x + g_3d48 + 6, g_6e18.y + g_3d4a + 7,
                        g_6e18.x + g_6e14.x + g_3d48 + 3, g_6e18.y + g_6e14.y + g_3d4a + 3);
                for (w = 0; w < 12; w++)
                    ScrollDC(g_13dc, 0, -1, &rc, &rc, 0, &rc2);
                g_1c58.y -= 12;
            } else
                g_1c54.y += 12;
            break;
        }
        if (g_1c5e || g_1c5c)
            PatBlt(g_13dc, g_1c58.x + 2, g_1c58.y, 6, 10, BLACKNESS);
        if (!g_1c5c && b) {
            g_1c5e++;
            if (g_1c5e >= 9) {
                SetRect(&rc, g_6e18.x + g_3d48 + 7, g_6e18.y + g_3d4a + 7,
                        g_6e18.x + g_6e14.x + g_3d48 + 3, g_6e18.y + g_6e14.y + g_3d4a + 3);
                for (len = 0; len < 12; len++)
                    ScrollDC(g_13dc, 0, -1, &rc, &rc, 0, &rc2);
                g_1c58.y -= 12;
            } else
                g_1c54.y += 12;
        }
        TextOut(g_13dc, g_1c54.x, g_1c54.y, ambulance_line + g_1c5c, 1);
        ext = GetTextExtent(g_13dc, ambulance_line + g_1c5c, 1);
        g_1c54.x += LOWORD(ext);
        w = SelectObject(g_13dc, CreateSolidBrush(RGB(0x80, 0xff, 0)));
        PatBlt(g_13dc, g_1c54.x + 2, g_1c54.y, 6, 10, PATCOPY);
        DeleteObject(SelectObject(g_13dc, w));
        g_1c58 = g_1c54;
        g_1c5c++;
        fn_10_754a(0x2b, 0, 0, 0);
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
}
