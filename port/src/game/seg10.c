/* INSPACE.EXE segment 10 (selector 1048). */
#include "game.h"

/* 10:6d38 */
int16_t fn_10_6d38(LPCSTR s)
{
    return g_fp_3c2c(s);
}

/* 10:6e26 */
void fn_10_6e26(void)
{
    g_fp_3c50(game_palette, 0, 0, 0, 0, 0, 2);
}

/* 10:6ec6 */
HBITMAP fn_10_6ec6(int16_t a)
{
    return ((HBITMAP (*)(int16_t, int16_t, int16_t))g_fp_3c40)(game_palette, a, main_dc);
}

/* 10:6b54 */
int16_t fn_10_6b54(void)
{
    return g_fp_3c84(0, g_1e4c);
}

/* 10:7db8 */
void fn_10_7db8(void)
{
    g_fp_3c54(g_05a0, 2);
}

/* 10:8686 */
void fn_10_8686(void)
{
    g_8e5c = 0;
    g_fp_3c54(g_05a0, 3);
}

/* 10:86ca */
int16_t fn_10_86ca(void)
{
    int16_t r;

    r = 0;
    return g_fp_3c4c();
}

/* 10:86a8 */
void fn_10_86a8(void)
{
    g_8e5c = 1;
    g_fp_3c54(g_05a0, 4);
}

/* 10:6e00 */
void fn_10_6e00(void)
{
    game_palette = g_fp_3c50(0, 0, 0, 0, 0, 0, 0);
}

/* 10:6ea0 */
void fn_10_6ea0(uint16_t a)
{
    g_fp_3c50(game_palette, 0, 0, 0, 0, a, 7);
}

/* 10:6e4c */
void fn_10_6e4c(void)
{
    g_fp_3c50(game_palette, main_window, main_dc, 0, 0, 0, 3);
}

/* 10:6e76 */
void fn_10_6e76(int32_t a)
{
    g_fp_3c50(game_palette, 0, 0, 0, HI16(a), LO16(a), 1);
    fn_10_6e4c();
}

/* 10:464a */
void fn_10_464a(void)
{
    g_928a = fn_10_6d38("DEF");
    fn_10_4672(0, 3);
}

/* Builds surface a from the strip g_928a (5 cells across, square cells):
 * per row, 16 directions made of the first n/4 + 1 cells and their mirror
 * images, b pixels apart; frees g_928a [inferred]. */
/* 10:4672 */
void fn_10_4672(int16_t a, int16_t b)
{
    int16_t j;
    int16_t i;
    int16_t bits;
    int16_t rows;
    int16_t cell;
    int16_t n;
    int16_t ys;
    int16_t yd;
    HDC dc;
    int16_t u16;
    HBITMAP ob;
    int16_t u1a;
    int16_t u1c;
    HPALETTE pal;
    BITMAP bmp;

    GetObject(g_928a, sizeof(BITMAP), &bmp);
    cell = bmp.bmWidth / 5;
    rows = bmp.bmHeight / cell;
    n = 16;
    bits = bmp.bmPlanes * bmp.bmBitsPixel;
    dc = CreateCompatibleDC(main_dc);
    ob = SelectObject(dc, g_928a);
    if (game_palette)
        pal = SelectPalette(dc, game_palette, 0);
    if (!g_39e8[a]) {
        g_39e8[a] = CreateCompatibleDC(main_dc);
        g_3ad0[a] = CreateCompatibleBitmap(main_dc, (cell + b) * n + b,
                                           (cell + b) * rows + b);
        g_3974[a] = SelectObject(g_39e8[a], g_3ad0[a]);
        if (game_palette)
            g_3a5c[a] = SelectPalette(g_39e8[a], game_palette, 0);
    }
    PatBlt(g_39e8[a], 0, 0, (cell + b) * n + b, (cell + b) * rows + b,
           BLACKNESS);
    yd = ys = 0;
    for (i = 0; i < rows; i++, ys += cell, yd += cell + b) {
        for (j = 0; j < n / 4 + 1; j++) {
            BitBlt(g_39e8[a], (cell + b) * j + b, yd + b, cell, cell, dc,
                   cell * j, ys, SRCCOPY);
            if (j == 0) {
                fn_10_9962(0, g_39e8[a], n / 2 * (cell + b) + b,
                           yd + cell + b - 1, cell, -cell, dc, cell * j, ys,
                           cell, cell, SRCCOPY);
            } else if (n / 4 == j) {
                fn_10_9962(0, g_39e8[a], (int16_t)(n * 3) / 4 * (cell + b) + cell + b - 1,
                           yd + b, -cell, cell, dc, cell * j, ys, cell, cell,
                           SRCCOPY);
            } else {
                fn_10_9962(0, g_39e8[a], (n / 2 - j) * (cell + b) + b,
                           yd + cell + b - 1, cell, -cell, dc, cell * j, ys,
                           cell, cell, SRCCOPY);
                fn_10_9962(0, g_39e8[a], (n / 2 + j) * (cell + b) + cell + b - 1,
                           yd + cell + b - 1, -cell, -cell, dc, cell * j, ys,
                           cell, cell, SRCCOPY);
                fn_10_9962(0, g_39e8[a], (n - j) * (cell + b) + cell + b - 1,
                           yd + b, -cell, cell, dc, cell * j, ys, cell, cell,
                           SRCCOPY);
            }
        }
        fn_10_740c();
    }
    SelectObject(dc, ob);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(g_928a);
    fn_10_6308(a, -1, -1, -1);
}

/* 10:5c1a */
void fn_10_5c1a(void)
{
    if (g_9288) {
        DeleteDC(g_9288);
        g_9288 = 0;
    }
}

/* 10:6d52 */
void fn_10_6d52(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f)
{
    g_fp_3c80(a, b, c, d, e, f);
}

/* 10:949c */
void fn_10_949c(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f)
{
    g_fp_3c70(a, b, c, d, e, f);
}

/* 10:993a */
void fn_10_993a(int16_t a, int16_t b)
{
    g_fp_3c7c(game_palette, a, b, main_window, main_dc);
}

/* 10:73e2 */
void fn_10_73e2(void)
{
    if (!g_9228) {
        g_9228 = 1;
        g_fp_3c54(g_05a0, 0);
    }
}

/* 10:7d8e */
void fn_10_7d8e(void)
{
    if (g_9228) {
        g_9228 = 0;
        g_fp_3c54(g_05a0, 1);
    }
}

/* 10:6d7a */
void fn_10_6d7a(int16_t a, int16_t b, int16_t c)
{
    int16_t r;

    ((FP7I)g_fp_3c50)(game_palette, 0, 0, a, b, c, 6);
}

/* 10:6da6 */
void fn_10_6da6(int16_t a, int16_t b)
{
    ((FP7I)g_fp_3c50)(game_palette, 0, main_dc, 0, a, b, 4);
    fn_10_6e4c();
}

/* 10:6dd4 */
void fn_10_6dd4(int16_t a)
{
    ((FP7I)g_fp_3c50)(game_palette, 0, main_dc, 0, a, 0, 5);
    fn_10_6e4c();
}

/* 10:946a */
int16_t fn_10_946a(char *p)
{
    char buf[20];
    int16_t r;

    r = g_fp_3c68(p, buf, 10);
    p[0x30] = 0;
    return r;
}

/* 10:744c */
void fn_10_744c(int16_t a)
{
    fn_10_754a(0x69, 0, 0, 0);
    if (a != 0x69)
        fn_10_754a(a, 0, 0, 0);
}

/* 10:80a8 */
int16_t fn_10_80a8(void)
{
    int16_t r;

    if (g_921e < 20) {
        g_921e++;
        fn_10_80dc();
        r = fn_10_82a2(8);
        fn_10_81b6();
    }
    return r;
}

/* 10:7370 */
HBITMAP fn_10_7370(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g)
{
    int16_t r;

    return g_fp_3c44(main_dc, a, b, c, d, e, game_palette, f, g);
}

/* 10:7d58 */
void fn_10_7d58(int16_t x, int16_t y)
{
    POINT p;

    if (g_9210) {
        p.x = x;
        p.y = y;
        g_fp_3c58(p, -10, -10, g_90ea);
    }
}

/* 10:6bca */
void fn_10_6bca(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h,
                    int16_t i, int16_t j, int32_t k)
{
    g_fp_3c48(a, b, c, d, e, f, g, h, i, j, k);
}

/* 10:73a6 */
int16_t fn_10_73a6(int16_t a, char *b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, char h, char i)
{
    return g_fp_3c34(game_palette, a, b, main_dc, c, d, e, f, g, h, i);
}

/* Plays sound a at a position given by mode d (0 none, 1 object c of
 * group b, 2 record c of g_6098, 3 g_5144, 4 point (b, c), 5 -11111)
 * through g_fp_3c5c [inferred]. Some sounds set a follow-up in g_9292
 * due at g_3c88. vx/vy are computed and then overwritten [sic]. */
/* 10:754a */
void fn_10_754a(int16_t a, int16_t b, int16_t c, int16_t d)
{
    int16_t r;
    POINT p;
    POINT saved;
    POINT dd;
    int32_t pos;
    union { int32_t l; PAIR p; } q;
    int16_t k;

    if (a == 0x6e)
        d = 0;
    if (g_920c == 3)
        return;
    if (d != 5) {
        if (a >= 0x6a) {
            switch (a) {
            case 0x6a:
                a = 0x20;
                g_9292 = 0x21;
                g_3c88 = now_ms + 1000;
                break;
            case 0x6b:
                a = 0x39;
                g_9292 = 0x3a;
                g_3c88 = now_ms + 420;
                break;
            case 0x6c:
                a = 0x38;
                g_9292 = 0x39;
                g_3c88 = now_ms + 385;
                break;
            case 0x6d:
                a = 0x35;
                g_9292 = 0x39;
                g_3c88 = now_ms + 385;
                break;
            case 0x71:
                a = 0x24;
                g_9292 = 0x25;
                g_3c88 = now_ms + 660;
                break;
            case 0x72:
                a = 0x1a;
                g_9292 = 0x1a;
                g_3c88 = now_ms + 200;
                break;
            case 0x73:
                a = 0x42;
                g_9292 = 0x43;
                g_3c88 = now_ms + 700;
                break;
            case 0x74:
                a = 0x42;
                g_9292 = 0x66;
                g_3c88 = now_ms + 400;
                break;
            case 0x76:
                a = 0x23;
                g_9292 = 0x25;
                g_3c88 = now_ms + 400;
                break;
            default:
                g_3c88 = 0;
                break;
            }
            if (g_3c88) {
                g_9216 = a;
                g_9218 = b;
                g_921a = c;
            }
        }
        q.p.b = (VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[g_9324][main_ship].f_04, 0).pt.x - ((int16_t)g_90ea / 2 << g_9150)) >> 3;
        q.p.a = (VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[g_9324][main_ship].f_04, 0).pt.y - (HI16(g_90ea) / 2 << g_9150)) >> 3;
    }
    switch (d) {
    case 1:
        if (b > g_9324)
            return;
        p = VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[b][c].f_04, 0).pt;
        break;
    case 2:
        if (g_6098[c].f_84)
            k = 0;
        else
            k = 1;
        p.y = g_6098[c].f_48[k][0];
        p.x = g_6098[c].f_30[k][0];
        break;
    case 3:
        p = g_5144;
        break;
    case 0:
        p.y = -6000;
        p.x = -6000;
        break;
    case 4:
        p.x = b;
        p.y = c;
        q.p.a = -1;
        q.p.b = -1;
        break;
    case 5:
        p.x = -11111;
        p.y = -11111;
        q.p.a = -1;
        q.p.b = -1;
        break;
    }
    saved = p;
    r = fn_10_7896(d, saved);
    if (r == -1) {
        g_3c88 = 0;
        g_9216 = 0;
        g_9292 = 0;
        return;
    }
    if (d != 0 && d != 4 && d != 5) {
        p = fn_08_29ea(p);
        if (g_9156 != 1 && !subgame_active) {
            dd.x = p.x - object_records[g_9324][main_ship].f_00.x;
            dd.y = p.y - object_records[g_9324][main_ship].f_00.y;
            p.x = (dd.x * 2 >> g_9156) + object_records[g_9324][main_ship].f_00.x;
            p.y = (dd.y * 2 >> g_9156) + object_records[g_9324][main_ship].f_00.y;
        }
    }
    q.l = 0x10001L;
    if (subgame_active)
        pos = VIEW(int32_t, g_88c0, 0);
    else
        pos = g_90ea;
    if (g_fp_3c5c(a, p, r, q.l, pos, now_ms, "")) {
        g_921c = a;
        g_928c = b;
        g_928e = c;
        g_9290 = d;
        g_3b98 = saved;
        g_9226 = r;
    }
}

/* Like fn_10_754a with a name e [inferred: a sound file]; also plays
 * sound 0x69 when the source is the player's own object. */
/* 10:7944 */
void fn_10_7944(int16_t a, int16_t b, int16_t c, int16_t d, LPCSTR e)
{
    int16_t r;
    POINT p;
    POINT saved;
    union { int32_t l; PAIR p; } q;
    POINT dd;
    int16_t unused[3];
    int16_t k;

    if (g_920c == 3)
        return;
    if (subgame_active) {
        q.l = 0;
    } else {
        q.p.a = (VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[g_9324][main_ship].f_04, 0).pt.x - ((int16_t)g_90ea / 2 << g_9150)) >> 3;
        q.p.b = (VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[g_9324][main_ship].f_04, 0).pt.y - (HI16(g_90ea) / 2 << g_9150)) >> 3;
    }
    switch (d) {
    case 1:
        if (b > g_9324)
            return;
        p = VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[b][c].f_04, 0).pt;
        break;
    case 2:
        if (g_6098[c].f_84)
            k = 0;
        else
            k = 1;
        p.y = g_6098[c].f_48[k][0];
        p.x = g_6098[c].f_30[k][0];
        break;
    case 3:
        p = g_5144;
        break;
    case 0:
        p.y = -6000;
        p.x = -6000;
        break;
    }
    saved = p;
    r = fn_10_7896(d, saved);
    if (r == -1)
        return;
    q.p.a = 1;
    q.p.b = 1;
    if (d != 0) {
        p = fn_08_29ea(p);
        if (g_9156 != 1) {
            dd.x = p.x - object_records[g_9324][main_ship].f_00.x;
            dd.y = p.y - object_records[g_9324][main_ship].f_00.y;
            p.x = (dd.x * 2 >> g_9156) + object_records[g_9324][main_ship].f_00.x;
            p.y = (dd.y * 2 >> g_9156) + object_records[g_9324][main_ship].f_00.y;
        }
    }
    if (b == g_9324 && c == main_ship && g_7090[main_ship].flag)
        g_fp_3c5c(0x69, p, 1, MAKELONG(q.p.b, q.p.a), g_90ea, now_ms, "");
    if (g_fp_3c5c(a, p, r, MAKELONG(q.p.b, q.p.a), g_90ea, now_ms, e)) {
        g_921c = a;
        g_928c = b;
        g_928e = c;
        g_9290 = d;
        g_3b98 = saved;
        g_9226 = r;
    }
}

/* Per-frame sound update [inferred]: fires the follow-up sound g_9292 when
 * g_3c88 is due, then repositions the last sound through g_fp_3c58. */
/* 10:7b48 */
void fn_10_7b48(void)
{
    POINT p;
    PAIR q;
    POINT dd;
    int16_t k;

    q.a = (VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[g_9324][main_ship].f_04, 0).pt.x - ((int16_t)g_90ea / 2 << g_9150)) >> 3;
    q.b = (VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[g_9324][main_ship].f_04, 0).pt.y - (HI16(g_90ea) / 2 << g_9150)) >> 3;
    if (g_3c88 && GetCurrentTime() > g_3c88) {
        if (g_920a > 1 || (g_9218 == 14 && g_921a == main_ship)
            || (g_921c == g_9216 && g_9218 == g_928c && g_921a == g_928e)
            || g_9292 == 0x66 || g_9216 >= 0x38) {
            fn_10_754a(0x69, g_928c, g_928e, g_9290);
            fn_10_754a(g_9292, g_928c, g_928e, g_9290);
            g_9216 = 0;
        }
        g_3c88 = 0;
        g_9292 = 0;
    }
    switch (g_9290) {
    case 1:
        if (g_928c > g_9324)
            return;
        p = VIEW(union {
        int32_t l;
        POINT pt;
    }, object_records[g_928c][g_928e].f_04, 0).pt;
        if (g_928c == 5)
            k++;
        break;
    case 2:
        if (g_6098[g_928e].f_84)
            k = 0;
        else
            k = 1;
        p.y = g_6098[g_928e].f_48[k][0];
        p.x = g_6098[g_928e].f_30[k][0];
        break;
    case 3:
        p = g_5144;
        break;
    case 0:
        p.y = -6000;
        p.x = -6000;
        break;
    case 4:
        return;
    }
    q.a = 1;
    q.b = 1;
    if (g_9290 != 0) {
        p = fn_08_29ea(p);
        if (g_9156 != 1) {
            dd.x = p.x - object_records[g_9324][main_ship].f_00.x;
            dd.y = p.y - object_records[g_9324][main_ship].f_00.y;
            p.x = (dd.x * 2 >> g_9156) + object_records[g_9324][main_ship].f_00.x;
            p.y = (dd.y * 2 >> g_9156) + object_records[g_9324][main_ship].f_00.y;
        }
    }
    if (g_fp_3c58(p, q.a, q.b, g_90ea))
        g_3b98 = p;
}

/* Stats SYSTEM.INI and WIN.INI in the Windows directory and IGRAPHIC.DLL
 * in the game directory g_8f7a, into g_922e / g_924c / g_926a [inferred:
 * a copy-protection or change check]. */
/* 10:80dc */
void fn_10_80dc(void)
{
    char buf[120];
    int16_t r;

    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "SYSTEM.INI");
    r = stat(buf, &g_922e);
    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "WIN.INI");
    stat(buf, &g_924c);
    lstrcpy(buf, g_8f7a);
    lstrcat(buf, "IGRAPHIC.DLL");
    r = stat(buf, &g_926a);
}

/* Puts back the modification times fn_10_80dc saved for SYSTEM.INI,
 * WIN.INI and IGRAPHIC.DLL. */
/* 10:81b6 */
void fn_10_81b6(void)
{
    char buf[120];

    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "SYSTEM.INI");
    g_3c10[0].modtime = g_922e.st_mtime;
    utime(buf, &g_3c10[0]);
    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "WIN.INI");
    g_3c10[1].modtime = g_924c.st_mtime;
    utime(buf, &g_3c10[1]);
    lstrcpy(buf, g_8f7a);
    lstrcat(buf, "IGRAPHIC.DLL");
    g_3c10[2].modtime = g_926a.st_mtime;
    utime(buf, &g_3c10[2]);
}

/* Runs dialog/screen a through g_fp_3c64 [inferred]. Modes 8 and 10 first
 * pass today's date (days since 1993); mode 1 reloads the INI player
 * settings. -100 is mode 6 owned by g_9532. Returns the dialog's result. */
/* 10:82a2 */
int16_t fn_10_82a2(int16_t a)
{
    int16_t r;
    char buf[20];
    int16_t v1;
    int16_t v0;
    HWND hwnd;

    if (a != 10)
        fn_10_7480(-2, 1);
    v0 = 0;
    if (a == 8 || a == 10) {
        struct tm *tm;
        int16_t yr;
        int16_t day;
        time_t t;

        time(&t);
        tm = localtime(&t);
        yr = tm->tm_year - 93;
        v0 = day = yr * 365 + tm->tm_yday;
        g_fp_3c64(0, 0, tm->tm_mday, tm->tm_mon + 1, tm->tm_year, 0, 15);
        if (a == 10) {
            fn_10_80dc();
            g_fp_3c64(0, 0, 0, day, 0x9d, 0, 9);
            fn_10_81b6();
            fn_10_885e(0);
            return 1;
        }
    }
    if (a == -100) {
        a = 6;
        hwnd = g_9532;
    } else {
        hwnd = main_window;
    }
    if (a == 5 || a == 7) {
        v1 = g_90f4;
        v0 = flow_interactive;
    } else if (a == 6) {
        v1 = flow_interactive;
    } else if (a == 8) {
        if (g_922a)
            v1 = 0;
        else
            v1 = g_9224;
    } else {
        v1 = 0;
    }
    if (a == 6 || a == 1 || a == 4) {
        if (g_920c == 0)
            v0 = 1;
        else if (g_920c == 3)
            v0 = 3;
        else
            v0 = 0;
    }
    r = g_fp_3c64(hwnd, g_39e8[5], game_palette, v1, v0, 0, a);
    now_ms = GetCurrentTime();
    g_3b94 = GetCurrentTime() + 500;
    fn_10_7f88();
    if (a == 5 || a == 6) {
        fn_10_7480(-3, 1);
        return r;
    }
    if (a == 12) {
        if (r) {
            fn_10_744c(0x13);
            fn_10_80a8();
        }
        return r;
    }
    if (r) {
        g_8f64 = 0;
        g_6e28 = GetCurrentTime() + 40000;
        if (a == 1) {
            int16_t flag;
            int16_t i;

            g_9134 = GetPrivateProfileInt(app_name, "PlayMode", 0, ini_name);
            GetPrivateProfileString(app_name, "ThePlayer", "", g_380c, 20, ini_name);
            GetPrivateProfileString(app_name, "Restore", "", buf, 9, ini_name);
            flag = 0;
            for (i = 0; lstrlen(buf) > i; i++)
                if (buf[i] == ' ')
                    flag = 1;
            if (flag) {
                g_939a = fn_10_804c(1);
                g_939e = fn_10_804c(0);
            }
        }
        g_104c[0].b = 0;
        g_104c[0].a = 0;
        g_951c = 0;
        GetPrivateProfileString(app_name, "Drive", "C", buf, 20, ini_name);
        g_94ac = buf[0] - 'C';
        g_9516 = 0;
    } else {
        if (g_95b8 < 4)
            g_6e28 = GetCurrentTime();
        else
            g_6e28 = GetCurrentTime() + 15000;
    }
    fn_10_7480(-3, 1);
    return r;
}

/* 10:561a */
void fn_10_561a(void)
{
    if (g_92ec[10] && !g_39ee)
        fn_10_6ee6(3, 0xb4, "", 0, 0x63, 3, 0, 1, 0, 12, 12, 0, 0);
}

/* Builds surface a with g_fp_3c30 (a d >= 100 means d - 100 and no
 * fn_10_6308 afterwards); h becomes a 0/1 flag. */
/* 10:6ee6 */
void fn_10_6ee6(int16_t a, int16_t b, char *s, int16_t c, int16_t d, int16_t e, int16_t f,
                    int16_t g, int16_t h, int16_t i, int16_t j, int16_t k, int16_t l)
{
    int16_t u[8];
    int16_t flag;

    flag = 1;
    if (g_39e8[a])
        fn_10_0552(a, 0);
    if (d >= 100) {
        d -= 100;
        flag = 0;
    }
    if ((g_9156 >= 2 && h != -1 && !l) || h > 1)
        h = 1;
    else
        h = 0;
    g_3ad0[a] = g_fp_3c30(game_palette, b, s, main_dc, c, d, e, f, g, h,
                          (char)i, (char)j, (char)k, l);
    g_39e8[a] = CreateCompatibleDC(main_dc);
    g_3974[a] = SelectObject(g_39e8[a], g_3ad0[a]);
    if (game_palette)
        g_3a5c[a] = SelectPalette(g_39e8[a], game_palette, 0);
    if (!subgame_active && flag && (g_9156 != 2 || l))
        fn_10_6308(a, -1, -1, -1);
}

/* 10:740c */
void fn_10_740c(void)
{
    HWND h;
    HTASK t;
    int16_t u;

    h = GetActiveWindow();
    t = GetWindowTask(main_window);
    if (GetWindowTask(h) == t)
        g_fp_3c54(g_05a0, 9);
}

/* 10:5cfa */
void fn_10_5cfa(void)
{
    int16_t i;

    for (i = 0; i < 2; i++) {
        if (g_3c60[i]) {
            DeleteObject(g_3c60[i]);
            g_3c60[i] = 0;
        }
    }
}

/* 10:9526 */
HBITMAP fn_10_9526(RECT *a, HGLOBAL b, int16_t c, int32_t d, int16_t e, int32_t f,
    int16_t g, int16_t h, int16_t i, int16_t x, int16_t y, int16_t k)
{
    return g_fp_3c78(main_dc, game_palette, a, b, c, d, e, f, g, h, i, x, y, k);
}

/* 10:6fec */
HBITMAP fn_10_6fec(int16_t a, char *b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h,
    char i, char j, char k, int16_t l)
{
    return g_fp_3c30(game_palette, a, b, main_dc, c, d, e, f, g, h, i, j, k, l);
}

/* 10:7dd4 */
int16_t fn_10_7dd4(int16_t *a, int16_t *b, int16_t *c, int16_t *d, int16_t *e, int16_t *f, int16_t *g, int16_t *h, int16_t i, int16_t j, int16_t k, int16_t l, int16_t *m, int16_t *n)
{
    return g_fp_3c6c(a, b, c, d, e, f, g, h, i, j, k, l, m, n);
}

/* 10:7328 */
void fn_10_7328(int16_t a, char *b, int16_t c, int16_t d, char e, char f, int16_t g, int16_t h,
    char i, char m)
{
    int16_t r;

    g_fp_3c38(game_palette, a, b, main_dc, m, c, d, e, f, g, h, i, g_9156);
}

/* 10:6b70 */
void fn_10_6b70(int16_t a)
{
    if (g_9210) {
        if (!a) {
            g_fp_3c54(g_05a0, 6);
            g_fp_3c54(g_05a0, 8);
        }
        FreeLibrary(g_9210);
        g_9210 = 0;
    }
    if (lang_module) {
        FreeLibrary(lang_module);
        lang_module = 0;
    }
}

/* 10:804c */
int32_t fn_10_804c(int16_t a)
{
    struct tm *tm;
    time_t t;
    int32_t r;
    int16_t y;
    int16_t md;

    time(&t);
    if (a)
        return t;
    tm = localtime(&t);
    y = tm->tm_year;
    md = (char)tm->tm_mday | ((BYTE)tm->tm_mon << 8);
    r = ((int32_t)y << 16) | (uint16_t)md;
    return r;
}

/* 10:94c4 */
void fn_10_94c4(int16_t a, int16_t b, int32_t c, int16_t d, int16_t e, char *f)
{
    int32_t l;

    switch (a) {
    case 0:
        l = 0x140012L;
        break;
    case 1:
        l = 0x12000cL;
        break;
    case 2:
        l = 0xa0009L;
        break;
    }
    g_fp_3c74(main_dc, game_palette, l, b, c, d, e, f);
}

/* 10:9764 */
int16_t fn_10_9764(int16_t a)
{
    struct tm *tm;
    time_t t;

    time(&t);
    tm = localtime(&t);
    if (a)
        return tm->tm_wday;
    if (tm->tm_hour > 2 && tm->tm_hour < 12)
        return 0;
    if (tm->tm_hour <= 2)
        return 3;
    if (tm->tm_hour >= 12 && tm->tm_hour < 18)
        return 1;
    return 2;
}

/* 10:7f18 */
void fn_10_7f18(void)
{
    g_0592 = 2;
    fn_10_744c(0x6e);
    fn_10_7480(-2, 1);
    g_fp_3c64(main_window, 0, 0, g_8ffa, g_8ffc, 0, 0);
    fn_06_0b3e();
    fn_10_7f88();
    now_ms = GetCurrentTime();
    g_3b94 = GetCurrentTime() + 500;
    fn_10_7480(-3, 1);
}

/* 10:7480 */
void fn_10_7480(int16_t a, int16_t b)
{
    POINT pt;
    int16_t u;

    if ((a == 9 || a == 10) && (g_9220 == 9 || g_9220 == 10))
        return;
    if (a == 10 && g_9220 == 1)
        a = 9;
    if (a == -2) {
        g_07e0[g_073e] = (char)g_9220;
        music_pause_state = -2;
    } else {
        music_pause_state = -3;
        if (a == -3 && g_07e0[g_073e] != g_9220)
            a = g_07e0[g_073e];
    }
    pt.y = b;
    pt.x = a;
    if (a == 7)
        a = 2;
    if (a >= 0) {
        g_9220 = a;
        if (g_2384 < now_ms)
            g_2384 = now_ms + 9000;
    }
    if (g_9210)
        g_fp_3c54(MAKELONG(pt.x, pt.y), 11);
}

/* 10:7f88 */
void fn_10_7f88(void)
{
    int16_t old;
    int16_t nw;
    HPALETTE pal;

    old = g_9156;
    nw = GetPrivateProfileInt(app_name, "Size", 1, ini_name);
    if (nw != old) {
        if (g_39e8[40]) {
            main_dc = GetDC(main_window);
            if (game_palette)
                pal = SelectPalette(main_dc, game_palette, 0);
            if (nw < old) {
                if ((int16_t)(nw - old) != -1)
                    fn_10_9a2a(-1);
                fn_10_9a2a(-1);
            } else {
                if ((int16_t)(nw - old) != 1)
                    fn_10_9a2a(1);
                fn_10_9a2a(1);
            }
            if (pal)
                SelectPalette(main_dc, pal, 0);
            ReleaseDC(main_window, main_dc);
            main_dc = 0;
        } else {
            g_103c = g_92e2 = 1;
        }
    }
}

/* 10:87de */
void fn_10_87de(void)
{
    int16_t n;
    char buf[10];

    if (!g_11aa && (g_920c == -1 || g_920c == 3)) {
        n = GetPrivateProfileInt(app_name, "PlusCount", 13, ini_name);
        n++;
        if (n > 12) {
            n = 0;
            g_90f4 = 9;
            fn_10_82a2(14);
        }
        fn_06_0f1a(n, buf);
        WritePrivateProfileString(app_name, "PlusCount", buf, ini_name);
    }
}

/* 10:39a8 */
void fn_10_39a8(int16_t a)
{
    if (!g_39e8[5]) {
        g_3ad0[5] = g_fp_3c30(game_palette, -1000, "", main_dc,
                              0, 6, 0, 0, 0, 0, 0, 0, 0, 0);
        g_39e8[5] = CreateCompatibleDC(main_dc);
        if (game_palette)
            g_3a5c[5] = SelectPalette(g_39e8[5], game_palette, 0);
        g_3974[5] = SelectObject(g_39e8[5], g_3ad0[5]);
        if (a)
            fn_10_6308(5, -1, -1, -1);
    }
}

/* Rescales a bitmap for the display scale g_9156 (1 = as is): surface a's
 * bitmap, or bitmap c when a is -1 (then returns the new bitmap). In scale
 * mode 2 surfaces 7 and 6 are first copied to 9 and 8. b is unused. */
/* 10:6308 */
int16_t fn_10_6308(int16_t a, int16_t b, int16_t c, int16_t d)
{
    HDC dc2;
    HDC dc1;
    HBITMAP ob2;
    HBITMAP nbm;
    HBITMAP ob1;
    HPALETTE pal2;
    HPALETTE pal1;
    BITMAP bmp;
    int16_t unused;
    int16_t w;
    int16_t h;

    if (!g_39e8[a] && a != -1)
        return 0;
    if (g_9156 == 1 && d != 2)
        return c;
    if (a != -1)
        c = g_3ad0[a];
    if (g_9156 == 2) {
        if (a == 9)
            return 0;
        if (a == 8)
            return 0;
        if (a == 7) {
            fn_10_0552(9, 1);
            g_39e8[9] = g_39e8[7];
            g_3ad0[9] = g_3ad0[7];
            g_3974[9] = g_3974[7];
            g_3a5c[9] = g_3a5c[7];
            g_0740 = 1;
        }
        if (a == 6) {
            fn_10_0552(8, 1);
            g_39e8[8] = g_39e8[6];
            g_3ad0[8] = g_3ad0[6];
            g_3974[8] = g_3974[6];
            g_3a5c[8] = g_3a5c[6];
            g_0740 = 1;
        }
    }
    GetObject(c, sizeof(BITMAP), &bmp);
    w = bmp.bmWidth;
    h = bmp.bmHeight;
    if (a != -1) {
        dc1 = CreateCompatibleDC(g_39e8[a]);
        dc2 = CreateCompatibleDC(g_39e8[a]);
        nbm = CreateCompatibleBitmap(g_39e8[a], (w << g_9156) >> 1,
                                     (h << g_9156) >> 1);
        if ((a != 7 && a != 6) || g_9156 != 2) {
            SelectObject(g_39e8[a], g_3974[a]);
            if (game_palette && g_3a5c[a])
                SelectPalette(g_39e8[a], g_3a5c[a], 0);
            DeleteDC(g_39e8[a]);
        } else {
            SelectObject(g_39e8[a], g_3974[a]);
        }
    } else {
        dc1 = CreateCompatibleDC(main_dc);
        dc2 = CreateCompatibleDC(main_dc);
        nbm = CreateCompatibleBitmap(main_dc, (w << g_9156) >> 1,
                                     (h << g_9156) >> 1);
    }
    if (game_palette)
        pal1 = SelectPalette(dc1, game_palette, 0);
    if (game_palette)
        pal2 = SelectPalette(dc2, game_palette, 0);
    ob2 = SelectObject(dc2, c);
    ob1 = SelectObject(dc1, nbm);
    PatBlt(dc1, 0, 0, (w << g_9156) >> 1, (h << g_9156) >> 1, BLACKNESS);
    if (a != 8 && a != 6)
        SetStretchBltMode(dc1, 3);
    else
        SetStretchBltMode(dc1, 2);
    fn_10_9962(1, dc1, 0, 0, (w << g_9156) >> 1, (h << g_9156) >> 1, dc2,
               0, 0, w, h, SRCCOPY);
    SelectObject(dc2, ob2);
    if (game_palette)
        SelectPalette(dc2, pal2, 0);
    DeleteDC(dc2);
    if ((a != 7 && a != 6) || g_9156 != 2) {
        DeleteObject(c);
    } else if (a == 7) {
        g_3974[9] = SelectObject(g_39e8[9], g_3ad0[9]);
    } else if (a == 6) {
        g_3974[8] = SelectObject(g_39e8[8], g_3ad0[8]);
    }
    if (a != -1) {
        g_39e8[a] = dc1;
        g_3ad0[a] = nbm;
        g_3974[a] = ob1;
        g_3a5c[a] = pal1;
        return 0;
    }
    SelectObject(dc1, ob1);
    if (game_palette)
        SelectObject(dc1, pal1);
    DeleteDC(dc1);
    return nbm;
}

/* 10:5586 */
int16_t fn_10_5586(int16_t a)
{
    int16_t i;
    int16_t j;

    if (a == 3 && g_92ec[9])
        return 1;
    for (i = 0; i <= g_9316; i++) {
        if (!g_7090[i].flag)
            continue;
        for (j = 0; j < g_7090[i].cnt; j++) {
            if (g_7090[i].f_0b8[j] == a)
                return 1;
        }
    }
    for (i = 0; i <= g_9406[8]; i++) {
        if (g_3d50[i].f_0a == a)
            return 1;
    }
    return 0;
}

/* 10:6c02 */
int16_t fn_10_6c02(int16_t a, int16_t b, int16_t c)
{
    HPALETTE old;
    int16_t got;
    int16_t r;

    got = 0;
    if (!main_dc) {
        got = 1;
        main_dc = GetDC(main_window);
        if (game_palette)
            old = SelectPalette(main_dc, game_palette, 0);
    }
    r = g_fp_3c28(game_palette, a, g_07de, main_dc, b, c);
    if (got) {
        if (old)
            SelectPalette(main_dc, old, 0);
        ReleaseDC(main_window, main_dc);
        main_dc = 0;
    }
    return r;
}

/* 10:506c */
void fn_10_506c(void)
{
    int16_t i;
    int16_t w;
    int16_t h;

    w = 32;
    h = 6;
    if (!g_39e8[32]) {
        g_39e8[32] = CreateCompatibleDC(main_dc);
        g_3ad0[32] = CreateCompatibleBitmap(main_dc, g_92ec[0] << 5, 32);
        g_3974[32] = SelectObject(g_39e8[32], g_3ad0[32]);
    }
    for (i = 0; i < g_92ec[0]; i++)
        BitBlt(g_39e8[32], w * i, 0, w, w, g_39e8[13], (h + w) * i + h, h,
               SRCCOPY);
}

/* 10:6c96 */
int16_t fn_10_6c96(int16_t a, char *b, int16_t c, int16_t d, int16_t e)
{
    HPALETTE old;
    int16_t got;
    int16_t r;

    got = 0;
    if (!main_dc) {
        got = 1;
        main_dc = GetDC(main_window);
        if (game_palette)
            old = SelectPalette(main_dc, game_palette, 0);
    }
    if (e)
        c -= 150;
    r = g_fp_3c28(game_palette, a, b, main_dc, c, d - 150);
    if (got) {
        if (old)
            SelectPalette(main_dc, old, 0);
        ReleaseDC(main_window, main_dc);
        main_dc = 0;
    }
    return r;
}

/* 10:a90c */
void sprite_dc_restore(void)
{
    int16_t i;

    for (i = 0; i < 58; i++) {
        if (g_3b9c[i]) {
            g_39e8[i] = CreateCompatibleDC(main_dc);
            SelectObject(g_39e8[i], g_3ad0[i]);
            if (game_palette)
                SelectPalette(g_39e8[i], game_palette, 0);
        }
    }
}

/* 10:a856 */
void sprite_dc_release(void)
{
    int16_t i;

    for (i = 0; i < 58; i++) {
        if (g_39e8[i]) {
            if (i != g_7090[main_ship].f_004 && i != 10 && i != 12 && i != 34
                && i != 7 && i != 6 && i != 9 && i != 8) {
                g_3b9c[i] = 1;
                SelectObject(g_39e8[i], g_3974[i]);
                if (game_palette)
                    SelectPalette(g_39e8[i], g_3a5c[i], 0);
                DeleteDC(g_39e8[i]);
                g_39e8[i] = 0;
            }
        } else
            g_3b9c[i] = 0;
    }
}

/* 10:7896 */
int16_t fn_10_7896(int16_t a, POINT pt)
{
    int16_t res;
    int16_t i;
    int16_t j;
    int16_t d;

    res = 1;
    if (!a)
        return 1;
    if (subgame_active)
        return 1;
    if (a == 4)
        return 1;
    d = fn_08_285a(&i, &j, pt, object_records[g_9324][main_ship].f_04);
    if (d > 800)
        return -1;
    if (d > 340)
        res = 0;
    if (res) {
        res = 0;
        for (i = 0; i < g_9158; i++) {
            if (PtInRect(&g_23e0[i], pt)) {
                res = 1;
                break;
            }
        }
    }
    return res;
}

/* 10:5c42 */
void fn_10_5c42(void)
{
    int16_t n;

    if (subgame_active)
        n = g_9156 * 6 + 3;
    else
        n = (9 << g_9156) >> 1;
    if (g_3c60[0])
        fn_10_5cfa();
    g_3c60[0] = (HGDIOBJ)fn_10_7032(0, 16, 0);
    if (!g_39e8[34]) {
        g_39e8[34] = CreateCompatibleDC(main_dc);
        g_3ad0[34] = CreateCompatibleBitmap(main_dc, n << 4, n << 4);
        if (game_palette)
            g_3a5c[34] = SelectPalette(g_39e8[34], game_palette, 0);
        g_3974[34] = SelectObject(g_39e8[34], g_3ad0[34]);
        PatBlt(g_39e8[34], 0, 0, n << 4, n << 4, BLACKNESS);
    }
}

/* Loads bitmap a through g_fp_3c3c and, when b >= 16, builds a 16 x 2
 * cell sheet of mirrored copies of its cells [inferred]. */
/* 10:7032 */
int16_t fn_10_7032(int16_t a, int16_t b, int16_t c)
{
    HBITMAP bm;
    HBITMAP ob1;
    HBITMAP nbm;
    HBITMAP ob2;
    HDC dc1;
    HDC dc2;
    HPALETTE pal1;
    HPALETTE pal2;
    int16_t i;
    int16_t j;
    int16_t s;
    int16_t t;

    bm = g_fp_3c3c(game_palette, 1, 1, a, 5, c);
    if (subgame_active) {
        s = g_9156 * 6 + 3;
        t = 9;
    } else {
        s = (9 << g_9156) >> 1;
        bm = fn_10_6308(-1, -1, bm, -1);
        t = s;
    }
    if (b < 16)
        return bm;
    dc1 = CreateCompatibleDC(main_dc);
    if (game_palette)
        pal1 = SelectPalette(dc1, game_palette, 0);
    ob1 = SelectObject(dc1, bm);
    dc2 = CreateCompatibleDC(main_dc);
    nbm = CreateCompatibleBitmap(main_dc, s << 4, s * 2);
    if (game_palette)
        pal2 = SelectPalette(dc2, game_palette, 0);
    ob2 = SelectObject(dc2, nbm);
    PatBlt(dc2, 0, 0, s << 4, s * 2, BLACKNESS);
    fn_10_9962(0, dc2, 0, 0, s * 5, s * 2, dc1, 0, 0, t * 5, t * 2, SRCCOPY);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            if (i == 0) {
                fn_10_9962(1, dc2, s << 3, (j + 1) * s - 1, s, -s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
            } else if (i == 4) {
                fn_10_9962(1, dc2, s * 13 - 1, s * j, -s, s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
            } else {
                fn_10_9962(1, dc2, (8 - i) * s, (j + 1) * s - 1, s, -s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
                fn_10_9962(1, dc2, (i + 9) * s - 1, (j + 1) * s - 1, -s, -s,
                           dc1, t * i, t * j, t, t, SRCCOPY);
                fn_10_9962(1, dc2, (17 - i) * s - 1, s * j, -s, s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
            }
        }
    }
    if (dc1) {
        if (game_palette)
            SelectPalette(dc1, pal1, 0);
        SelectObject(dc1, ob1);
        if (bm)
            DeleteObject(bm);
        DeleteDC(dc1);
        dc1 = bm = 0;
    }
    if (dc2) {
        if (game_palette)
            SelectPalette(dc2, pal2, 0);
        SelectObject(dc2, ob2);
        DeleteDC(dc2);
        dc2 = 0;
    }
    return nbm;
}

/* Zoom change [inferred] by d (-1/+1): new level d + g_9156 must be 0..2.
 * Rescales the sprites (fn_10_6308), every object's size fields
 * (g_1df8[type][n].f22/f24, f12), on the largest zoom with g_8fe8 the
 * ships ("Loading Ship # ", strings built but not shown) and the 0x34-byte
 * records, then the class records' sizes; saves "Size" (and "SetSize" when
 * a person plays) to the INI file. The early MessageBeep return leaves
 * g_931e at 0 (kept). */
/* 10:9a2a */
void fn_10_9a2a(int16_t d)
{
    int16_t i;
    int16_t j;
    int16_t nz;
    int16_t v;
    int16_t w;
    int16_t res;
    int16_t saved;
    int16_t unused;         /* never used; keeps the frame */
    int16_t flag;
    int16_t a;
    int16_t b;
    int16_t t;
    char buf3[8];
    char buf1[40];
    char buf2[30];

    if (g_90f4 != 1 || subgame_active) {
        g_103c = 1;
        return;
    }
    saved = g_931e;
    g_931e = 0;
    if (d + g_9156 > 2 || d + g_9156 < 0) {
        MessageBeep(0);
        return;
    }
    if (g_934c == 0) {
        g_9518 = 1;
        g_934c = CreateDialog(lang_module, MAKEINTRESOURCE(0x65), main_window, fn_09_90fe);
    }
    if ((nz = d + g_9156) == 1 && d == 1)
        g_103a = flag = 1;
    else if (nz == 1 && d == -1 && g_8fe8 && !g_90f0)
        g_103a = flag = 1;
    else
        flag = 0;
    g_9156 = d + 1;
    if (!flag) {
        for (i = 0; i < 0x3a; i++) {
            if (i == 0x20)
                continue;
            if (g_9156 == 2 && i > 0x27 && i < 0x30 && flag)
                continue;
            fn_10_6308(i, -1, -1, -2);
        }
    } else {
        for (i = 0xe; i < g_92ec[0] + 0xe; i++)
            fn_10_6308(i, -1, -1, -2);
    }
    for (i = 0; i < g_9406[1]; i++)
        if (g_4e94[i])
            g_4e94[i] = fn_10_6308(-1, -1, g_4e94[i], -1);
    g_9156 = nz;
    g_9150 = 4 - nz;
    fn_10_0552(0x22, 1);
    fn_10_5c42();
    for (i = g_9326; i <= g_9324; i++) {
        for (j = 0; j < (&g_92ec[0])[i]; j++) {
            if (g_9156 == 0 && i == g_9324 && (object_records[i][j].f_22 & 1)) {
                object_records[i][j].f_22++;
                object_records[i][j].f_24--;
            }
            object_records[i][j].f_22 = (int16_t)(object_records[i][j].f_22 << (d + 1)) >> 1;
            object_records[i][j].f_24 = (int16_t)(object_records[i][j].f_24 << (d + 1)) >> 1;
            if (i == 3 && d == 1 && g_9156 > 0
                && object_records[i][j].f_22 < 12 << g_9156)
                object_records[i][j].f_24 = 4;
            if (i == 3 && g_9156 == 1 && object_records[i][j].f_22 < 12 << g_9156
                && g_8fe8 && !g_90f0)
                object_records[i][j].f_24 = 4;
            object_records[i][j].f_12 = object_records[i][j].f_24;
        }
    }
    if (flag || g_9156 == 2 && g_8fe8) {
        for (i = 0x30; i < 0x3a; i++)
            fn_10_0552(i, 1);
        for (i = 0; i <= g_9316; i++) {
            fn_10_0552(i + 0x28, 1);
            a = g_7090[i].f_0ac;
            b = g_7090[i].f_0ad;
            lstrcpy(buf1, "Loading Ship # ");
            fn_06_0f1a(i, buf2);
            lstrcat(buf1, buf2);
            fn_14_11a8(i);
            if (g_7090[i].f_0d6 != -1) {
                v = g_6e24[g_7090[i].f_0d6].f_7a;
                g_96d2[g_7090[i].f_04e].f_2a = v;
                w = g_6e24[g_7090[i].f_0d6].f_7b;
            } else {
                v = object_records[g_9324][i].f_22;
                g_96d2[g_7090[i].f_04e].f_2a = v;
                w = object_records[g_9324][i].f_24;
            }
            g_92e4 = 1;
            object_records[g_9324][i].f_22 = v << g_9156 >> 1;
            object_records[g_9324][i].f_24 = w << g_9156 >> 1;
            object_records[g_9324][i].f_12 = object_records[g_9324][i].f_24;
            if (!a)
                fn_08_2cd8(i, 0);
            if (!b)
                fn_08_2cd8(i, 1);
            g_92e4 = 0;
        }
        for (i = 0x17; i < 0x1c; i++) {
            fn_10_0552(i, 1);
            g_381a[i].f_04 = g_381a[i].f_00 = g_381a[i].f_02 = -1;
        }
        for (i = 0; i < g_9406[8]; i++) {
            if (g_3d50[i].f_1c == 2) {
                if (g_3d50[i].f_30 <= 2)
                    g_3d50[i].f_1c = 1;
                else if (g_3d50[i].f_30 >= 5) {
                    if (g_4d90[g_3d50[i].f_30].f_03 == -1)
                        t = 1;
                    else
                        t = 0;
                    res = fn_10_18b0(g_3d50[i].f_22, g_3d50[i].f_20, g_3d50[i].f_2a,
                                     t, g_3d50[i].f_30);
                    object_records[8][i].f_24 = g_4d90[g_3d50[i].f_30].f_09 << g_9156 >> 1;
                    object_records[8][i].f_22 = g_4d90[g_3d50[i].f_30].f_08 << g_9156 >> 1;
                    object_records[8][i].f_20 = object_records[8][i].f_22 << 3;
                    if (g_3d50[i].f_0a > 0 && g_2f4c[g_3d50[i].f_0a].f_12)
                        fn_10_533a(g_3d50[i].f_0a);
                    g_3d50[i].f_1e = res;
                }
            }
        }
    }
    if (flag) {
        fn_10_9568();
        fn_10_0552(0xd, 1);
        fn_10_5b30();
        for (i = 0; i < g_92ec[0]; i++)
            BitBlt(g_3a02, i * 0x26 + 6, 6, 0x20, 0x20, g_3a28, i << 5, 0, SRCCOPY);
        fn_09_94ba();
        for (i = 0; i < g_92ec[0]; i++)
            fn_07_233c(0, i, 0);
    }
    for (i = 0; i <= g_9316; i++) {
        v = g_96d2[g_7090[i].f_04e].f_2a;
        if (v & 1)
            w = 5;
        else
            w = 6;
        if (g_9156 == 0 && (v & 1)) {
            v++;
            w = 4;
        }
        g_96d2[g_7090[i].f_04e].f_02 = g_96d2[g_7090[i].f_04e].f_00 = (v >> g_9156) * 2 / 2;
        if (g_96d2[g_7090[i].f_04e].f_04 < 0)
            g_96d2[g_7090[i].f_04e].f_04 = 4 - g_96d2[g_7090[i].f_04e].f_04 - v / 2;
        fn_10_1502(g_7090[i].f_04e);
        fn_10_5d3c(i);
    }
    fn_06_0f1a(g_9156, buf3);
    WritePrivateProfileString(app_name, "Size", buf3, ini_name);
    if (flow_interactive)
        WritePrivateProfileString(app_name, "SetSize", buf3, ini_name);
    if (g_934c) {
        g_8f64 = 0;
        DestroyWindow(g_934c);
        g_9518 = 0;
        g_934c = 0;
        PostMessage(main_window, 0x978, 0, 0L);
    }
    PatBlt(main_dc, 0, 0, g_90ea, HI16(g_90ea), BLACKNESS);
    g_931e = saved;
}

/* StretchBlt, or fn_10_6bca (g_fp_3c48) for an exact 2x stretch or a
 * mirrored one when g_0742 is set and the source DC is not mono or more
 * than 8 bits deep. The first argument is unused. */
/* 10:9962 */
void fn_10_9962(int16_t unused, HDC dst, int16_t x, int16_t y, int16_t w, int16_t h, HDC src,
                    int16_t xs, int16_t ys, int16_t ws, int16_t hs, DWORD rop)
{
    HBITMAP bm;
    BITMAP b;
    int16_t flag;
    char pad[0x30];

    flag = 0;
    bm = CreateCompatibleBitmap(src, 2, 2);
    GetObject(bm, sizeof(BITMAP), &b);
    if (b.bmPlanes * b.bmBitsPixel == 1 || (int16_t)(b.bmPlanes * b.bmBitsPixel) > 8)
        flag = 1;
    DeleteObject(bm);
    if (g_0742 && !flag &&
        (((int16_t)(ws * 2) == w && (int16_t)(hs * 2) == h) || w < 0 || h < 0))
        fn_10_6bca(dst, x, y, w, h, src, xs, ys, ws, hs, rop);
    else
        StretchBlt(dst, x, y, w, h, src, xs, ys, ws, hs, rop);
}

/* Recreates surface 13: a (32 + 6) * g_9406 + 6 by 6 * 2 + 32 bitmap,
 * cleared to black. */
/* 10:5b30 */
void fn_10_5b30(void)
{
    int16_t a;
    int16_t b;

    a = 6;
    b = 32;
    if (!g_9288)
        g_9288 = CreateCompatibleDC(main_dc);
    if (g_39e8[13]) {
        SelectObject(g_39e8[13], g_3974[13]);
        if (game_palette)
            SelectPalette(g_39e8[13], g_3a5c[13], 0);
        DeleteObject(g_3ad0[13]);
        DeleteDC(g_39e8[13]);
    }
    g_39e8[13] = CreateCompatibleDC(main_dc);
    g_3ad0[13] = CreateCompatibleBitmap(main_dc, (b + a) * g_9406[0] + a, a * 2 + b);
    g_3974[13] = SelectObject(g_39e8[13], g_3ad0[13]);
    if (game_palette)
        g_3a5c[13] = SelectPalette(g_39e8[13], game_palette, 0);
    PatBlt(g_39e8[13], 0, 0, (b + a) * g_9406[0] + a, b * a * 2, BLACKNESS);
}

/* Meal break check: g_9214 = 3 (Lunch, default 12:00), 4 (Breakfast,
 * 8:00), 1 (Coffee, 10:00), 2 (Tea, 15:30) when the time read from the
 * INI file lies in the half hour before now (hhmm + 1), else 0. */
/* 10:9672 */
int16_t fn_10_9672(void)
{
    struct tm *tm;
    time_t t;
    int16_t v;
    int16_t now;

    time(&t);
    tm = localtime(&t);
    now = tm->tm_hour * 100 + tm->tm_min + 1;
    if ((v = GetPrivateProfileInt(app_name, "Lunch", 1200, ini_name)) < now && (int16_t)(v + 30) > now)
        g_9214 = 3;
    else if ((v = GetPrivateProfileInt(app_name, "Breakfast", 800, ini_name)) < now && (int16_t)(v + 30) > now)
        g_9214 = 4;
    else if ((v = GetPrivateProfileInt(app_name, "Coffee", 1000, ini_name)) < now && (int16_t)(v + 30) > now)
        g_9214 = 1;
    else if ((v = GetPrivateProfileInt(app_name, "Tea", 1530, ini_name)) < now && (int16_t)(v + 30) > now)
        g_9214 = 2;
    else
        g_9214 = 0;
    return g_9214;
}

/* Changes the frame delay g_059c by 2 * d (clamped to 4..104, wrapping
 * past 104 to 1200 [sic]), derives the frame rate values and saves
 * "FrameRateSet" to the INI file. */
/* 10:7e1c */
void fn_10_7e1c(int16_t d)
{
    int16_t u;
    char buf[8];
    int32_t l1;
    int32_t l2;
    int16_t q;
    int16_t r;
    int16_t u2;

    if (g_0a7c) {
        g_870c = now_ms + 5000;
        g_0a76 = 4;
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    }
    frame_rate += d * 2;
    if (d < 0 && frame_rate > 1000)
        frame_rate = 104;
    frame_rate = frame_rate < 4 ? 4 : frame_rate;
    if (frame_rate > 104)
        frame_rate = 1200;
    g_059e = frame_rate / 4;
    frame_ms = 1000 / frame_rate;
    q = 10000 / frame_rate;
    r = q % 10;
    if (r > 4)
        frame_ms++;
    frame_min_ms = frame_ms - 1;
    fn_06_0f1a(frame_rate, buf);
    WritePrivateProfileString(app_name, "FrameRateSet", buf, ini_name);
}

/* Copies surface 40 + g_7094[i].f4c into a new surface 40 + i sized from
 * g_96d2[g_7094[i].f4a].f2a and the current ship's f24 [inferred]. */
/* 10:86e2 */
void fn_10_86e2(int16_t i)
{
    int16_t d;
    int16_t w;
    int16_t n;
    int16_t s;

    w = g_96d2[g_7090[i].f_04e].f_2a;
    n = object_records[g_9324]->f_24;
    d = i + 40;
    s = g_7090[i].f_050 + 40;
    if (g_39e8[d])
        fn_10_0552(d, 0);
    g_3ad0[d] = CreateCompatibleBitmap(main_dc, w * 16 + n * 17, n * 2 + w);
    g_39e8[d] = CreateCompatibleDC(main_dc);
    g_3974[d] = SelectObject(g_39e8[d], g_3ad0[d]);
    if (game_palette)
        g_3a5c[d] = SelectPalette(g_39e8[d], game_palette, 0);
    BitBlt(g_39e8[d], 0, 0, w * 16 + n * 17, n * 2 + w, g_39e8[s], 0, 0, SRCCOPY);
}

/* Creates surfaces 10 and 11 (bitmaps 0xaa and 0xaf, the second mirrored
 * [inferred]) when either is missing. */
/* 10:5102 */
void fn_10_5102(void)
{
    int16_t a;
    int16_t i;
    int16_t b, c, d, e;
    int16_t n;
    int16_t f;
    int16_t id;
    int16_t x;
    int16_t y;
    int16_t g, h, k, m;

    if (!g_39e8[10] || !g_39e8[11]) {
        for (i = 0; i < 2; i++) {
            fn_10_740c();
            if (i == 0) {
                n = 10;
                id = 0xaa;
                if (g_8fe8)
                    x = 2;
                else
                    x = 0;
                y = 1;
            } else if (i == 1) {
                n = 11;
                id = 0xaf;
                x = 0;
                y = -1;
                if (!g_1e68)
                    fn_09_27da(50);
            }
            if (!g_39e8[n]) {
                g_3ad0[n] = fn_10_6c02(id, x, y);
                g_39e8[n] = CreateCompatibleDC(main_dc);
                g_3974[n] = SelectObject(g_39e8[n], g_3ad0[n]);
                if (game_palette)
                    g_3a5c[n] = SelectPalette(g_39e8[n], game_palette, 0);
                fn_10_740c();
                fn_10_6308(n, -1, -1, -1);
            }
        }
    }
}

/* Builds surfaces 1 and 2: blocks from bitmaps 0xd2 / 0x334 (colour) and
 * the monochrome BW_BLOCKS / BW_MBLOCKS, each with mirrored copies, and
 * the OUT_SIGN marks on surface 1 [inferred]. */
/* 10:3ea2 */
void fn_10_3ea2(void)
{
    int16_t u4;
    int16_t u6;
    HBITMAP ob1;
    int16_t ua;
    HBITMAP ob2;
    HBITMAP bm1;
    int16_t u10;
    HBITMAP bm2;
    HDC dc1;
    int16_t u16;
    HDC dc2;
    HPALETTE pal1;
    HPALETTE pal2;
    int16_t i;
    int16_t j;
    int16_t w;
    int16_t m;
    int16_t u26;
    int16_t u28;
    BITMAP bmp;
    int16_t u;

    if (g_39e8[1])
        return;
    for (i = 0; i < 2; i++) {
        object_records[8]->f_24 = 6;
        m = object_records[8]->f_24;
        w = object_records[8]->f_22 = 0x22;
        u = (w + m) * 2;
        g_39e8[i + 1] = CreateCompatibleDC(main_dc);
        dc1 = CreateCompatibleDC(main_dc);
        dc2 = CreateCompatibleDC(main_dc);
        if (i == 0) {
            bm1 = fn_10_6c02(0xd2, 3, -1);
            bm2 = fn_10_6c02(0x334, 0, -1);
            GetObject(bm2, sizeof(BITMAP), &bmp);
            g_3ad0[1] = CreateCompatibleBitmap(main_dc, w * 4 + m * 5, m * 2 + w);
        } else {
            bm1 = fn_10_6d38("BW_BLOCKS");
            bm2 = fn_10_6d38("BW_MBLOCKS");
            g_3ad0[2] = CreateBitmap(w * 4 + m * 5, m * 2 + w, 1, 1, NULL);
        }
        ob1 = SelectObject(dc1, bm1);
        ob2 = SelectObject(dc2, bm2);
        g_3974[i + 1] = SelectObject(g_39e8[i + 1], g_3ad0[i + 1]);
        if (i == 0 && game_palette) {
            pal1 = SelectPalette(dc1, game_palette, 0);
            pal2 = SelectPalette(dc2, game_palette, 0);
            g_3a5c[1] = SelectPalette(g_39e8[1], game_palette, 0);
        }
        PatBlt(g_39e8[i + 1], 0, 0, w * 4 + m * 5, m * 2 + w, BLACKNESS);
        for (j = 0; j < 2; j++) {
            BitBlt(g_39e8[i + 1], m, m, w, w, dc1, 0, 0, SRCCOPY);
            BitBlt(g_39e8[i + 1], w * 2 + m * 3, m, w, w, dc2, 0, 0, SRCCOPY);
            BitBlt(g_39e8[i + 1], m * 4 + w * 3, m, w, w, dc2, w, 0, SRCCOPY);
        }
        if (dc1) {
            SelectObject(dc1, ob1);
            if (pal1)
                SelectPalette(dc1, pal1, 0);
            DeleteDC(dc1);
            dc1 = 0;
            if (bm1) {
                DeleteObject(bm1);
                bm1 = 0;
            }
        }
        if (dc2) {
            SelectObject(dc2, ob2);
            if (pal2)
                SelectPalette(dc2, pal2, 0);
            DeleteDC(dc2);
            dc2 = 0;
            if (bm2) {
                DeleteObject(bm2);
                bm2 = 0;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        SetStretchBltMode(g_39e8[i + 1], 3);
        fn_10_9962(0, g_39e8[i + 1], (m + w) * 2 - 1, m, -w, w, g_39e8[i + 1],
                   m, m, w, w, SRCCOPY);
        fn_10_9962(0, g_39e8[i + 1], (m + w) * 2 - 1, m, 5 - w, w,
                   g_39e8[i + 1], (m + 2) * 2 + w, m, w - 5, w, SRCCOPY);
    }
    bm1 = fn_10_6d38("OUT_SIGN");
    dc1 = CreateCompatibleDC(main_dc);
    ob1 = SelectObject(dc1, bm1);
    if (game_palette)
        pal1 = SelectPalette(dc1, game_palette, 0);
    BitBlt(g_39e8[1], m + 2, m + 10, 26, 13, dc1, 26, 0, SRCCOPY);
    BitBlt(g_39e8[1], (m + 3) * 2 + w, m + 10, 26, 13, dc1, 26, 0, SRCCOPY);
    SelectObject(dc1, ob1);
    if (pal1)
        SelectPalette(dc1, pal1, 0);
    DeleteDC(dc1);
    if (bm1) {
        DeleteObject(bm1);
        bm1 = 0;
    }
    fn_10_6308(1, -1, -1, -1);
    fn_10_6308(2, -1, -1, -1);
}

/* Builds surface 22 (nine 37-pixel cells of bitmap 0x154) or, in the
 * sub-game, the scaled strip g_9656 [inferred]. */
/* j is a dead store: CL drops the load but keeps its `les bx,[g_1e1c]`. */
/* 10:58ce */
void fn_10_58ce(int16_t a)
{
    int16_t i;
    int16_t j;
    int16_t w;
    int16_t m;
    int16_t v;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;

    if (g_39e8[22] && !subgame_active)
        return;
    if (g_9656 && subgame_active)
        return;
    j = object_records[9]->f_00.x;
    w = 0x25;
    m = 5;
    if (g_8fe8)
        v = 3;
    else
        v = 0;
    g_928a = fn_10_6c02(0x154, v, -1);
    dc = CreateCompatibleDC(main_dc);
    ob = SelectObject(dc, g_928a);
    if (game_palette)
        pal = SelectPalette(dc, game_palette, 0);
    if (!subgame_active) {
        g_3ad0[22] = CreateCompatibleBitmap(main_dc, w * 9 + m * 10, m * 2 + w);
        g_39e8[22] = CreateCompatibleDC(main_dc);
        g_3974[22] = SelectObject(g_39e8[22], g_3ad0[22]);
        if (game_palette)
            g_3a5c[22] = SelectPalette(g_39e8[22], game_palette, 0);
        PatBlt(g_39e8[22], 0, 0, w * 9 + m * 10, m * 2 + w, BLACKNESS);
        for (i = 0; i < 9; i++)
            BitBlt(g_39e8[22], (m + w) * i + m, m, w, w, dc, w * i, 0, SRCCOPY);
    } else {
        g_9658 = CreateCompatibleBitmap(main_dc, 0xfc / (4 - g_9156 * 3),
                                        0x1c / (4 - g_9156 * 3));
        g_9656 = CreateCompatibleDC(main_dc);
        g_965a = SelectObject(g_9656, g_9658);
        if (game_palette)
            g_965c = SelectPalette(g_9656, game_palette, 0);
        PatBlt(g_9656, 0, 0, 0xfc / (4 - g_9156 * 3), 0x1c / (4 - g_9156 * 3),
               BLACKNESS);
        SetStretchBltMode(g_9656, 3);
        fn_10_9962(0, g_9656, 0, 0, 0xfc / (4 - g_9156 * 3),
                   0x1c / (4 - g_9156 * 3), dc, 0, 0, w * 9, w, SRCCOPY);
    }
    SelectObject(dc, ob);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(g_928a);
    if (a)
        fn_10_6308(22, -1, -1, -1);
}

/* Builds surface 4 for the current g_9214 (cached in g_17c0): five cells
 * of bitmap 0x10e, or one or two frames of 0x110 / 0x112 / 0x116 / 0x48. */
/* 10:565a */
void fn_10_565a(void)
{
    int16_t i;
    int16_t w;
    int16_t m;
    int16_t id;
    int16_t n;
    int16_t k;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;
    BITMAP bmp;
    static int16_t last;    /* DS:17c0 */

    if (g_39e8[4]) {
        if (last == g_9214)
            return;
        fn_10_0552(4, 1);
    }
    n = 1;
    last = g_9214;
    if (g_9214 == 0) {
        id = 0x10e;
        w = 0x24;
        m = 6;
    } else {
        if (g_9214 == 1)
            id = 0x110;
        if (g_9214 == 2)
            id = 0x112;
        if (g_9214 == 3) {
            id = 0x116;
            n = 2;
        }
        if (g_9214 == 4) {
            id = 0x48;
            n = 2;
            fn_10_6ea0(9);
        }
        w = 0x1e;
        m = 4;
    }
    for (k = 0; k < n; k++) {
        g_928a = fn_10_6c02(id - k * 2, 0, -1);
        dc = CreateCompatibleDC(main_dc);
        ob = SelectObject(dc, g_928a);
        if (game_palette)
            pal = SelectPalette(dc, game_palette, 0);
        if (k == 0) {
            if (g_9214 == 0)
                g_3ad0[4] = CreateCompatibleBitmap(main_dc, w * 5 + m * 6, m * 2 + w);
            else if (g_9214 == 3 || g_9214 == 4)
                g_3ad0[4] = CreateCompatibleBitmap(main_dc, w * 2 + m * 3, m * 2 + w);
            else
                g_3ad0[4] = CreateCompatibleBitmap(main_dc, m * 2 + w, m * 2 + w);
            g_39e8[4] = CreateCompatibleDC(main_dc);
            g_3974[4] = SelectObject(g_39e8[4], g_3ad0[4]);
            if (game_palette)
                g_3a5c[4] = SelectPalette(g_39e8[4], game_palette, 0);
        }
        if (g_9214 == 0) {
            PatBlt(g_39e8[4], 0, 0, w * 5 + m * 6, m * 2 + w, BLACKNESS);
            for (i = 0; i < 5; i++)
                BitBlt(g_39e8[4], (m + w) * i + m, m, w, w, dc, w * i, 0, SRCCOPY);
        } else {
            PatBlt(g_39e8[4], (m * 2 + w) * k, 0, m * 2 + w, m * 2 + w, BLACKNESS);
            BitBlt(g_39e8[4], (m + w) * k + m, m, w - 1, w - 1, dc, 0, 0, SRCCOPY);
        }
        SelectObject(dc, ob);
        if (pal)
            SelectPalette(dc, pal, 0);
        DeleteDC(dc);
        DeleteObject(g_928a);
    }
    fn_10_6308(4, -1, -1, -1);
}

/* Builds surface 12: a 270 x 22 strip of six pieces of bitmap 200,
 * growing in size [inferred]. */
/* 10:5202 */
void fn_10_5202(void)
{
    int16_t i;
    int16_t h;
    int16_t u;
    int16_t x;
    HBITMAP bm;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;

    bm = fn_10_6c02(200, 0, -1);
    dc = CreateCompatibleDC(main_dc);
    ob = SelectObject(dc, bm);
    if (game_palette)
        pal = SelectPalette(dc, game_palette, 0);
    x = 0;
    g_3ad0[12] = CreateCompatibleBitmap(main_dc, 270, h = 22);
    g_39e8[12] = CreateCompatibleDC(main_dc);
    g_3974[12] = SelectObject(g_39e8[12], g_3ad0[12]);
    if (game_palette)
        g_3a5c[12] = SelectPalette(g_39e8[12], game_palette, 0);
    PatBlt(g_39e8[12], 0, 0, 270, h, BLACKNESS);
    for (i = 0; i <= 5; i++) {
        u = (i + 5) * 6;
        BitBlt(g_39e8[12], x * 3, 0, u, u / 3, dc, 0, x, SRCCOPY);
        x += u / 3;
    }
    SelectObject(dc, ob);
    DeleteObject(bm);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    fn_10_6308(12, -1, -1, -1);
}

/* Builds surfaces 6..9: eighteen rock frames from the monochrome ROCKS
 * bitmap (6, and 8 at size 21) and coloured ones (7, 9) from bitmap 0x32
 * when g_90f0 or g_8fe8 is set, else grey through a MERGECOPY brush. */
/* 10:3a2e */
void fn_10_3a2e(void)
{
    HBRUSH br1;
    HBRUSH br2;
    HBITMAP ob2;
    HBITMAP ob1;
    int16_t u0c;
    HBITMAP bm2;
    HBITMAP bm1;
    int16_t u12;
    HDC dc2;
    HDC dc1;
    int16_t u18;
    HPALETTE pal1;
    int16_t u1c;
    BITMAP bmp;
    int16_t i;
    int16_t u2e;
    int16_t a;
    int16_t m;
    int16_t b;
    int16_t u36;

    if (g_39e8[6])
        return;
    a = 0x2b;
    b = 0x15;
    m = 5;
    if (g_90f0 || g_8fe8) {
        bm1 = fn_10_6c02(0x32, 3, -1);
        dc1 = CreateCompatibleDC(main_dc);
        ob1 = SelectObject(dc1, bm1);
        if (game_palette)
            pal1 = SelectPalette(dc1, game_palette, 0);
    }
    g_0740 = 0;
    bm2 = fn_10_6d38("ROCKS");
    dc2 = CreateCompatibleDC(main_dc);
    ob2 = SelectObject(dc2, bm2);
    g_3ad0[6] = CreateBitmap(m * 19 + a * 18, m * 2 + a, 1, 1, NULL);
    g_3ad0[7] = CreateCompatibleBitmap(main_dc, m * 19 + a * 18, m * 2 + a);
    g_3ad0[8] = CreateBitmap(b * 18 + m * 19, m * 2 + b, 1, 1, NULL);
    g_3ad0[9] = CreateCompatibleBitmap(main_dc, b * 18 + m * 19, m * 2 + b);
    for (i = 0; i < 2; i++) {
        g_39e8[i + 6] = CreateCompatibleDC(main_dc);
        g_3974[i + 6] = SelectObject(g_39e8[i + 6], g_3ad0[i + 6]);
        if (game_palette && i)
            g_3a5c[7] = SelectPalette(g_39e8[7], game_palette, 0);
        PatBlt(g_39e8[i + 6], 0, 0, m * 19 + a * 18, m * 2 + a, BLACKNESS);
    }
    for (i = 0; i < 2; i++) {
        g_39e8[i + 8] = CreateCompatibleDC(main_dc);
        g_3974[i + 8] = SelectObject(g_39e8[i + 8], g_3ad0[i + 8]);
        if (game_palette && i)
            g_3a5c[9] = SelectPalette(g_39e8[9], game_palette, 0);
        PatBlt(g_39e8[i + 8], 0, 0, b * 18 + m * 19, m * 2 + b, BLACKNESS);
    }
    for (i = 0; i < 18; i++) {
        BitBlt(g_39e8[6], (m + a) * i + m, m, a, a, dc2, a * i, 0, SRCCOPY);
        SetStretchBltMode(g_39e8[8], 2);
        fn_10_9962(0, g_39e8[8], (b + m) * i + m, m, b, b, dc2, a * i, 0, a, a,
                   SRCCOPY);
    }
    fn_10_740c();
    if (g_90f0 || g_8fe8) {
        for (i = 0; i < 18; i++) {
            BitBlt(g_39e8[7], (m + a) * i + m, m, a, a, dc1, a * i, 0, SRCCOPY);
            SetStretchBltMode(g_39e8[9], 3);
            fn_10_9962(0, g_39e8[9], (b + m) * i + m, m, b, b, dc1, a * i, 0,
                       a, a, SRCCOPY);
        }
    } else {
        br1 = SelectObject(g_39e8[7], CreateSolidBrush(RGB(128, 128, 128)));
        br2 = SelectObject(g_39e8[9], CreateSolidBrush(RGB(128, 128, 128)));
        BitBlt(g_39e8[7], 0, 0, m * 19 + a * 18, m * 2 + a, g_39e8[6], 0, 0,
               MERGECOPY);
        BitBlt(g_39e8[9], 0, 0, b * 18 + m * 19, m * 2 + b, g_39e8[8], 0, 0,
               MERGECOPY);
        DeleteObject(SelectObject(g_39e8[7], br1));
        DeleteObject(SelectObject(g_39e8[9], br2));
    }
    if (g_90f0 || g_8fe8) {
        if (pal1)
            SelectPalette(dc1, pal1, 0);
        SelectObject(dc1, ob1);
        DeleteDC(dc1);
        if (bm1)
            DeleteObject(bm1);
    }
    SelectObject(dc2, ob2);
    DeleteDC(dc2);
    if (bm2)
        DeleteObject(bm2);
    fn_10_6308(7, -1, -1, -1);
    fn_10_6308(6, -1, -1, -1);
    fn_10_6308(9, -1, -1, -1);
    fn_10_6308(8, -1, -1, -1);
}

/* Builds surface 29 (89 x 33) from bitmaps 0x2b2..0x2b4. Selects the
 * palette into g_13dc instead of the new DC and frees its temporary DC
 * with DeleteObject [sic]. */
/* 10:42ee */
void fn_10_42ee(void)
{
    HDC dc;
    HPALETTE old;
    HBITMAP bm;
    HBITMAP ob;
    int16_t i;
    int16_t u;
    int16_t u2;

    if (!g_39e8[29]) {
        dc = CreateCompatibleDC(main_dc);
        if (game_palette)
            old = SelectPalette(dc, game_palette, 0);
        g_39e8[29] = CreateCompatibleDC(main_dc);
        if (game_palette)
            g_3a5c[29] = SelectPalette(main_dc, game_palette, 0);
        g_3ad0[29] = CreateCompatibleBitmap(main_dc, 0x59, 0x21);
        g_3974[29] = SelectObject(g_39e8[29], g_3ad0[29]);
        PatBlt(g_39e8[29], 0, 0, 0x59, 0x21, BLACKNESS);
        for (i = 0; i < 3; i++) {
            ob = SelectObject(dc, bm = fn_10_6c02(i + 0x2b2, 3, -1));
            BitBlt(g_39e8[29], i * 0x1c + 5, u = 5, 0x17, 0x17, dc, 0, 0, SRCCOPY);
            SelectObject(dc, ob);
            DeleteObject(bm);
        }
        if (game_palette)
            SelectPalette(dc, old, 0);
        DeleteObject(dc);
        fn_10_6308(29, -1, -1, -1);
    }
}

/* Builds surface 30 for the race: four markers of bitmap 0x1a4 in a row. */
/* 10:49d4 */
void race_marker_strip(void)
{
    int16_t w;
    int16_t h;
    int16_t i;
    HBITMAP bm;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;

    if (!g_39e8[30]) {
        bm = fn_10_6c02(0x1a4, 0, -1);
        w = 14;
        h = 4;
        dc = CreateCompatibleDC(main_dc);
        ob = SelectObject(dc, bm);
        if (game_palette)
            pal = SelectPalette(dc, game_palette, 0);
        g_3ad0[30] = CreateCompatibleBitmap(main_dc, w * 4 + h * 5, h * 2 + w);
        g_39e8[30] = CreateCompatibleDC(main_dc);
        g_3974[30] = SelectObject(g_39e8[30], g_3ad0[30]);
        if (game_palette)
            g_3a5c[30] = SelectPalette(g_39e8[30], game_palette, 0);
        PatBlt(g_39e8[30], 0, 0, w * 4 + h * 5, h * 2 + w, BLACKNESS);
        for (i = 0; i < 4; i++)
            BitBlt(g_39e8[30], (h + w) * i + h, h, w, w, dc, i * w, 0, SRCCOPY);
        SelectObject(dc, ob);
        if (game_palette)
            SelectPalette(dc, pal, 0);
        DeleteDC(dc);
        DeleteObject(bm);
        fn_10_6308(30, -1, -1, -1);
    }
}

/* Rebuilds the game's surfaces: frees each and calls its builder. */
/* 10:9568 */
void fn_10_9568(void)
{
    fn_10_0552(1, 1);
    fn_10_0552(2, 1);
    fn_10_3ea2();
    fn_10_0552(22, 1);
    fn_10_58ce(1);
    fn_10_0552(4, 1);
    fn_10_565a();
    fn_10_0552(12, 1);
    fn_10_5202();
    fn_10_0552(5, 1);
    fn_10_39a8(1);
    fn_10_0552(6, 1);
    fn_10_0552(8, 1);
    fn_10_0552(7, 1);
    fn_10_0552(9, 1);
    fn_10_3a2e();
    fn_10_0552(10, 1);
    fn_10_0552(11, 1);
    fn_10_5102();
    fn_10_0552(29, 1);
    fn_10_42ee();
    fn_10_0552(3, 1);
    fn_10_561a();
    fn_10_0552(0, 1);
    fn_10_464a();
    fn_10_0552(30, 1);
    if (g_9320 == 6)
        race_marker_strip();
}

/* Formats a pilot record's summary lines into dst with fn_10_a332 (string
 * ids 0xbb8..0xbba, 0xbd3) [inferred: a saved-game / champion entry].
 * Divides the record's time by 36 in place [sic]. */
/* 10:a118 */
void fn_10_a118(REC_PILOT *src, LPSTR dst)
{
    int16_t mins;
    int16_t secs;
    int16_t v;
    int16_t sum;
    int16_t i;
    int16_t same;
    char line[60];
    char name[20];

    src->f_18b /= 36;
    mins = (int16_t)src->f_18b / 60;
    secs = (int16_t)src->f_18b - mins * 60;
    v = src->f_162;
    if (src->f_15e < 100) {
        if (v < -15000)
            v = (uint16_t)v / 10;
        else
            v = v / 10;
    } else {
        src->f_15e -= 100;
    }
    for (i = sum = 0; i < 8; i++)
        sum += src->f_146[i];
    lstrcpy(name, src->f_004);
    same = lstrcmp(src->f_004, g_380c) == 0;
    fn_11_3fd4(name, 1);
    if (src->f_032 == src->f_160) {
        if (src->f_160 == 1)
            LoadString(lang_module, 0x9c7, line, 60);
        else
            LoadString(lang_module, 0x9c5, line, 60);
    } else if (src->f_160 == 0) {
        LoadString(lang_module, 0x9c6, line, 60);
    } else {
        format_string(line, 0x9c4, 1, src->f_160);
    }
    format_string(dst, 0xbb8, 1, 1, src->f_024, mins, 0x9c9, secs, 0x9c8,
               src->f_032, 0x13e, (LPSTR)line);
    if (src->f_15a || src->f_15c)
        format_string(dst, 0xbb9, 0, src->f_156 + src->f_158, 0x9d3, src->f_15a,
                   src->f_15a, 0x9d3, src->f_15c, src->f_15c, 0x9d3);
    format_string(dst, 0xbba, 0, v / 10, fn_09_88ba(v % 10), src->f_15e + 0x137);
    if (g_9460)
        format_string(dst, 0xbd3, 0, same, !same, (LPSTR)name, !sum, sum, sum,
                   0x130);
}

/* Message formatter [inferred]: loads string resource id into a format
 * and expands it into out (appending when n is 0; n == 2 also calls
 * fn_03_3498). Codes: %s/%a/%v far string, %A/%S/%V string id, %l long,
 * %d int, %# int plus a unit string id (+10000 unless the int is 1),
 * %< %> optional section (an int switches it on; sections are joined
 * with ", " and a final string 0x31d), %N/%n line break, %? pick one of
 * two ids, %D fn_03_1542 text, %R random string id, %% percent; ^F ^M
 * ^N ^P markers are skipped. */
/* 10:a332 */
void format_string(LPSTR out, int16_t id, int16_t n, ...)
{
    int16_t i;
    int16_t len;
    int16_t outpos;
    int16_t count;
    int16_t k;
    int16_t j;
    int16_t val;
    int16_t ids[2];
    int32_t l;
    char buf[80];
    char c;
    char fmt[200];
    LPSTR s;
    int16_t on;
    int16_t flag;
    va_list ap;

    on = 1;
    i = 0;
    count = outpos = 0;
    va_start(ap, n);
    LoadString(lang_module, id, fmt, 0x82);
    len = lstrlen(fmt);
    if (n == 0)
        outpos = lstrlen(out);
    for (k = 0; k < len && i <= len; k++) {
        if (fmt[i] != '%') {
            flag = 0;
            if (fmt[i] == '^') {
                switch (fmt[i + 1]) {
                case 'F':
                case 'M':
                case 'N':
                case 'P':
                    flag = 1;
                    i++;
                }
            }
            if (on && !flag) {
                out[outpos] = fmt[i];
                outpos++;
            }
            i++;
        } else {
            switch (c = fmt[i + 1]) {
            case 's':
            case 'a':
            case 'v':
                s = va_arg(ap, LPSTR);
                if (on) {
                    out[outpos] = 0;
                    lstrcat(out + outpos, s);
                    outpos += lstrlen(s);
                }
                i += 2;
                break;
            case 'A':
            case 'S':
            case 'V':
                LoadString(lang_module, (int16_t)va_arg(ap, int), buf, 0x50);
                if (on) {
                    if (buf[lstrlen(buf) - 2] == '^')
                        buf[lstrlen(buf) - 2] = 0;
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            case '%':
                if (on) {
                    out[outpos] = '%';
                    outpos++;
                }
                i += 2;
                break;
            case 'l':
                l = va_arg(ap, int32_t);
                if (on) {
                    fn_06_0eb8(l, buf);
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            case '#':
            case 'd':
                val = (int16_t)va_arg(ap, int);
                if (on) {
                    fn_06_0f1a(val, buf);
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                if (c != 'd') {
                    if (val != 1)
                        val = 10000;
                    else
                        val = 0;
                    val += (int16_t)va_arg(ap, int);
                    if (on) {
                        out[outpos++] = ' ';
                        LoadString(lang_module, val, buf, 0x50);
                        out[outpos] = 0;
                        lstrcat(out + outpos, buf);
                        outpos = lstrlen(buf) + outpos;
                    }
                }
                i += 2;
                break;
            case '<':
                on = (int16_t)va_arg(ap, int);
                if (on) {
                    for (j = i + 1 + 1; j < len; j++) {
                        if (fmt[j] == '%') {
                            if (fmt[j + 1] == '<') {
                                if (count >= 1) {
                                    out[outpos] = ',';
                                    out[outpos + 1] = ' ';
                                    outpos += 2;
                                }
                                count++;
                                break;
                            } else if (fmt[j + 1] == '>') {
                                if (count > 0) {
                                    LoadString(lang_module, 0x31d, buf, 0x14);
                                    out[outpos] = 0;
                                    lstrcat(out + outpos, buf);
                                    outpos += lstrlen(buf);
                                    out[outpos] = ' ';
                                    outpos = outpos + 1;
                                }
                                count++;
                                break;
                            }
                        }
                    }
                }
                i += 2;
                break;
            case '>':
                on = 1;
                i += 2;
                count = 0;
                break;
            case 'N':
            case 'n':
                if (on && !(g_93aa == 11 && c == 0)) {
                    out[outpos] = '\r';
                    out[outpos + 1] = '\n';
                    outpos += 2;
                }
                i += 2;
                break;
            case '?':
                val = (int16_t)va_arg(ap, int);
                ids[0] = (int16_t)va_arg(ap, int);
                ids[1] = (int16_t)va_arg(ap, int);
                if (val > 1)
                    val = 1;
                LoadString(lang_module, ids[val], buf, 0x50);
                if (on) {
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            case 'D':
                {
                    int16_t a, b, t;

                    a = (int16_t)va_arg(ap, int);
                    b = (int16_t)va_arg(ap, int);
                    t = (int16_t)va_arg(ap, int);
                    if (on) {
                        fn_03_1542(t == 0 || t == 4 || t == 2 || t == 7 ? 1 : 0,
                                   a, b, buf, t);
                        out[outpos] = 0;
                        lstrcat(out + outpos, buf);
                        outpos += lstrlen(buf);
                    }
                }
                i += 2;
                break;
            case 'R':
                val = rand() % (int16_t)va_arg(ap, int);
                val += (int16_t)va_arg(ap, int);
                LoadString(lang_module, val, buf, 0x50);
                if (on) {
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            default:
                i += 3;
                break;
            }
        }
    }
    out[outpos] = 0;
    va_end(ap);
    if (n == 2)
        fn_03_3498(g_8db0, g_8768, g_87b8);
}

/* "StratAsk": while the INI value is 0 or 1, asks (strings 0xb22..0xb25)
 * with a yes/no box; yes adds 10 to the value and saves it, no returns 0. */
/* 10:a96c */
int16_t fn_10_a96c(void)
{
    int16_t r;
    int16_t v;
    char b0[200];
    char b1[400];
    char b2[200];

    v = GetPrivateProfileInt(app_name, "StratAsk", 0, ini_name);
    if (v == 0 || v == 1) {
        fn_10_744c(0x2c);
        LoadString(lang_module, 0xb22, b1, 200);
        LoadString(lang_module, 0xb23, b2, 200);
        lstrcat(b1, b2);
        LoadString(lang_module, 0xb24, b2, 200);
        lstrcat(b1, b2);
        LoadString(lang_module, 0xb25, b2, 200);
        lstrcat(b1, b2);
        r = MessageBox(main_window, b1, app_name, MB_YESNO | MB_ICONEXCLAMATION);
        if (r != IDYES)
            return 0;
        fn_06_0f1a(v += 10, b1);
        WritePrivateProfileString(app_name, "StratAsk", b1, ini_name);
    }
    return 1;
}

/* Frees the surface of g_2f4c[a] unless another active entry of g_7148
 * or g_3d5a (state 2) still uses it, or a is 22. */
/* 10:546e */
void fn_10_546e(int16_t a)
{
    int16_t i;
    int16_t j;
    int16_t s;

    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].flag) {
            for (j = 0; j < g_7090[i].cnt; j++)
                if (g_2f4c[g_7090[i].f_0b8[j]].f_04 == g_2f4c[a].f_04)
                    return;
        }
    }
    for (i = 0; i <= g_9406[8]; i++)
        if (g_3d50[i].f_1c == 2 && g_2f4c[g_3d50[i].f_0a].f_04 == g_2f4c[a].f_04)
            return;
    if (a == 22)
        return;
    s = g_2f4c[a].f_04;
    if (s < 0)
        return;
    if (g_39e8[s]) {
        if (g_3a5c[s])
            SelectPalette(g_39e8[s], g_3a5c[s], 0);
        SelectObject(g_39e8[s], g_3974[s]);
        DeleteDC(g_39e8[s]);
        g_39e8[s] = 0;
        g_2f4c[a].f_04 = 0;
        if (g_3ad0[s]) {
            DeleteObject(g_3ad0[s]);
            g_3ad0[s] = 0;
        }
    }
}

/* Quit/leave confirmation [inferred]: for a = 1, -1 or 3 asks only when
 * "SavePrompt" is set or the "Restore" entry looks unused; shows the
 * g_fp_3c64 dialog and on yes ends (a = 1 or -1 destroys the window). */
/* 10:8568 */
int16_t fn_10_8568(int16_t a)
{
    int16_t r;
    int16_t ask;
    char buf[80];

    ask = 1;
    fn_10_7480(-2, 1);
    if (a == 1 || a == -1 || a == 3) {
        ask = GetPrivateProfileInt(app_name, "SavePrompt", 1, ini_name);
        if (!ask) {
            GetPrivateProfileString(app_name, "Restore", "", buf, 9, ini_name);
            if (buf[3] == ' ' || !buf[0])
                ask = 1;
        }
    }
    if (ask) {
        fn_10_744c(0x6e);
        fn_10_744c(0x13);
        r = g_fp_3c64(main_window, g_39e8[5], game_palette, 0, 0, 0, 3);
        now_ms = GetCurrentTime();
        g_3b94 = GetCurrentTime() + 500;
    } else
        r = 1;
    if (r) {
        switch (a) {
        case 1:
        case 2:
        case 3:
            fn_06_99b6();
            if (a == 1)
                DestroyWindow(main_window);
            break;
        case -1:
        case 0:
            fn_06_885c(1, 0);
            if (a == -1)
                DestroyWindow(main_window);
            break;
        }
    }
    fn_10_7480(-3, 1);
    return r;
}

/* Builds surface a: d frames of bitmap c, shrinking by 2 pixels each,
 * spaced by object b's margin f24 (5 for an odd height, else 6). */
/* 10:4412 */
void fn_10_4412(int16_t a, int16_t b, int16_t c, int16_t d)
{
    HDC dc;
    HBITMAP bm;
    HBITMAP ob;
    HPALETTE pal;
    int16_t i;
    int16_t w;
    int16_t x;
    int16_t u;
    BITMAP bmp;
    int16_t h;

    bm = fn_10_6c02(c, 3, -1);
    GetObject(bm, sizeof(BITMAP), &bmp);
    h = bmp.bmHeight;
    if (h & 1)
        object_records[b]->f_24 = 5;
    else
        object_records[b]->f_24 = 6;
    dc = CreateCompatibleDC(main_dc);
    ob = SelectObject(dc, bm);
    w = h * d + object_records[b]->f_24 * (d + 1);
    g_39e8[a] = CreateCompatibleDC(main_dc);
    g_3ad0[a] = CreateCompatibleBitmap(main_dc, w, object_records[b]->f_24 * 2 + h);
    g_3974[a] = SelectObject(g_39e8[a], g_3ad0[a]);
    if (game_palette) {
        pal = SelectPalette(dc, game_palette, 0);
        g_3a5c[a] = SelectPalette(g_39e8[a], game_palette, 0);
    }
    PatBlt(g_39e8[a], 0, 0, w, object_records[b]->f_24 * 2 + h, BLACKNESS);
    if (d == 1) {
        BitBlt(g_39e8[a], object_records[b]->f_24, object_records[b]->f_24, h, h, dc, 0, 0,
               SRCCOPY);
    } else {
        SetStretchBltMode(g_39e8[a], 3);
        x = object_records[b]->f_24;
        for (i = 0; i < d; i++) {
            u = (i - d) * 2 + h;
            fn_10_9962(0, g_39e8[a], x, object_records[b]->f_24, u, u, dc, 0, 0, h, h, SRCCOPY);
            x += object_records[b]->f_24 + h;
        }
    }
    SelectObject(dc, ob);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    if (bm) {
        DeleteObject(bm);
        bm = 0;
    }
    fn_10_6308(a, -1, -1, -1);
}

/* Gives g_2f4c[a] a surface in 48..56: shares one already built for the
 * same f06, else builds a new one (fn_10_4412 for kind 4, else
 * fn_10_6ee6). Entries 22 and 27 are skipped. */
/* 10:533a */
void fn_10_533a(int16_t a)
{
    int16_t i;
    int16_t j;
    int16_t u;
    int16_t f;

    if (a == 27 || a == 22)
        return;
    for (i = 0x30; i < 0x39; i++) {
        if (g_39e8[i]) {
            for (j = 0; j <= 27; j++)
                if (g_2f4c[j].f_12 && g_2f4c[j].f_04 == i &&
                    g_2f4c[j].f_06 == g_2f4c[a].f_06) {
                    g_2f4c[a].f_04 = i;
                    return;
                }
        }
    }
    for (i = 0x30; i < 0x39; i++) {
        if (!g_39e8[i]) {
            g_2f4c[a].f_04 = i;
            object_records[6]->f_22 = g_2f4c[a].f_00;
            object_records[6]->f_24 = g_2f4c[a].f_02;
            if (g_2f4c[a].f_0e == 4) {
                fn_10_4412(i, 6, g_2f4c[a].f_06, g_2f4c[a].f_2e);
            } else {
                if (g_90f4 == 1 && g_1e68) {
                    if (g_931e == 1 || g_931e == 2)
                        f = 1;
                    else
                        f = 0;
                } else if (g_931e == 2)
                    f = 1;
                else
                    f = 0;
                fn_10_6ee6(i, g_2f4c[a].f_06, "", 2, 0x63, g_2f4c[a].f_22,
                           g_2f4c[a].f_24, 1, 0, 12, 12, 0, f);
            }
            return;
        }
    }
}

/* Writes the current time and date into s as "h:mmAM m/d/yy". */
/* 10:97ce */
void fn_10_97ce(char *s)
{
    struct tm *tm;
    time_t t;
    char buf[80];
    int16_t h;
    int16_t pm;

    time(&t);
    tm = localtime(&t);
    lstrcpy(s, "");
    h = tm->tm_hour;
    if (h > 11) {
        h -= 12;
        pm = 1;
    } else
        pm = 0;
    if (h == 0)
        h = 12;
    fn_06_0f1a(h, buf);
    lstrcat(s, buf);
    lstrcat(s, ":");
    if (tm->tm_min < 10)
        lstrcat(s, "0");
    fn_06_0f1a(tm->tm_min, buf);
    lstrcat(s, buf);
    if (pm)
        lstrcat(s, "PM");
    else
        lstrcat(s, "AM");
    lstrcat(s, " ");
    fn_06_0f1a(tm->tm_mon + 1, buf);
    lstrcat(s, buf);
    lstrcat(s, "/");
    fn_06_0f1a(tm->tm_mday, buf);
    lstrcat(s, buf);
    lstrcat(s, "/");
    fn_06_0f1a(tm->tm_year, buf);
    lstrcat(s, buf);
}

/* (Re)creates the game's brush and pen tables g_3b74 (1..9), g_576c,
 * g_3b88 (1..5) and g_3b44, and the g_3b4c ramps. */
/* 10:4b2e */
void fn_10_4b2e(void)
{
    int16_t i;

    for (i = 0; i < 10; i++) {
        if (g_3b74[i]) {
            DeleteObject(g_3b74[i]);
            g_3b74[i] = 0;
        }
    }
    g_3b74[9] = CreateSolidBrush(RGB(255, 114, 0));
    g_3b74[8] = CreateSolidBrush(RGB(255, 96, 0));
    g_3b74[7] = CreateSolidBrush(RGB(234, 64, 0));
    g_3b74[6] = CreateSolidBrush(RGB(224, 48, 0));
    g_3b74[5] = CreateSolidBrush(RGB(208, 32, 0));
    g_3b74[4] = CreateSolidBrush(RGB(192, 32, 16));
    g_3b74[3] = CreateSolidBrush(RGB(176, 32, 32));
    g_3b74[2] = CreateSolidBrush(RGB(127, 48, 48));
    g_3b74[1] = CreateSolidBrush(RGB(127, 64, 64));
    fn_10_4dfe();
    for (i = 0; i < 20; i++) {
        if (g_576c[i]) {
            DeleteObject(g_576c[i]);
            g_576c[i] = 0;
        }
    }
    g_576c[0] = CreateSolidBrush(RGB(128, 128, 128));
    g_576c[1] = CreateSolidBrush(RGB(160, 160, 160));
    g_576c[2] = CreateSolidBrush(RGB(192, 192, 192));
    g_576c[3] = CreateSolidBrush(RGB(224, 224, 224));
    g_576c[4] = CreateSolidBrush(RGB(255, 255, 255));
    g_576c[5] = CreateSolidBrush(RGB(192, 192, 192));
    g_576c[6] = CreateSolidBrush(RGB(160, 223, 160));
    g_576c[7] = CreateSolidBrush(RGB(96, 224, 96));
    g_576c[8] = CreateSolidBrush(RGB(64, 255, 64));
    g_576c[9] = CreateSolidBrush(RGB(0, 255, 0));
    g_576c[10] = CreateSolidBrush(RGB(0, 0, 128));
    g_576c[11] = CreateSolidBrush(RGB(0, 40, 138));
    g_576c[12] = CreateSolidBrush(RGB(0, 80, 160));
    g_576c[13] = CreateSolidBrush(RGB(0, 160, 196));
    g_576c[14] = CreateSolidBrush(RGB(0, 196, 255));
    g_576c[15] = CreateSolidBrush(RGB(160, 0, 0));
    g_576c[16] = CreateSolidBrush(RGB(196, 0, 0));
    g_576c[17] = CreateSolidBrush(RGB(223, 32, 0));
    g_576c[18] = CreateSolidBrush(RGB(255, 96, 0));
    g_576c[19] = CreateSolidBrush(RGB(255, 128, 0));
    for (i = 0; i < 6; i++) {
        if (g_3b88[i]) {
            DeleteObject(g_3b88[i]);
            g_3b88[i] = 0;
        }
    }
    g_3b88[1] = CreateSolidBrush(RGB(0, 0, 127));
    g_3b88[2] = CreateSolidBrush(RGB(0, 127, 196));
    g_3b88[3] = CreateSolidBrush(RGB(0, 196, 255));
    g_3b88[4] = CreateSolidBrush(RGB(0, 255, 255));
    g_3b88[5] = CreateSolidBrush(RGB(255, 255, 255));
    for (i = 0; i < 4; i++) {
        if (g_3b44[i]) {
            DeleteObject(g_3b44[i]);
            g_3b44[i] = 0;
        }
    }
    g_3b44[0] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    g_3b44[1] = CreatePen(PS_SOLID, 1, RGB(127, 0, 127));
    g_3b44[2] = CreatePen(PS_SOLID, 1, RGB(255, 0, 127));
    g_3b44[3] = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
}

/* (Re)creates the 20 brushes g_3b4c: yellow-to-red and cyan-to-blue
 * ramps, finer when g_8ff2 is set [inferred]. */
/* 10:4dfe */
void fn_10_4dfe(void)
{
    int16_t i;

    for (i = 0; i < 20; i++) {
        if (g_3b4c[i]) {
            DeleteObject(g_3b4c[i]);
            g_3b4c[i] = 0;
        }
    }
    if (g_8ff2) {
        g_3b4c[0] = CreateSolidBrush(PALETTERGB(255, 255, 0));
        g_3b4c[1] = CreateSolidBrush(PALETTERGB(235, 235, 0));
        g_3b4c[2] = CreateSolidBrush(PALETTERGB(220, 215, 0));
        g_3b4c[3] = CreateSolidBrush(PALETTERGB(210, 180, 0));
        g_3b4c[4] = CreateSolidBrush(PALETTERGB(200, 140, 0));
        g_3b4c[5] = CreateSolidBrush(PALETTERGB(185, 120, 0));
        g_3b4c[6] = CreateSolidBrush(PALETTERGB(175, 100, 0));
        g_3b4c[7] = CreateSolidBrush(PALETTERGB(135, 65, 0));
        g_3b4c[8] = CreateSolidBrush(PALETTERGB(135, 65, 0));
        g_3b4c[9] = CreateSolidBrush(PALETTERGB(105, 25, 0));
        g_3b4c[10] = CreateSolidBrush(PALETTERGB(0, 255, 255));
        g_3b4c[11] = CreateSolidBrush(PALETTERGB(0, 235, 240));
        g_3b4c[12] = CreateSolidBrush(PALETTERGB(0, 215, 230));
        g_3b4c[13] = CreateSolidBrush(PALETTERGB(0, 205, 215));
        g_3b4c[14] = CreateSolidBrush(PALETTERGB(0, 175, 205));
        g_3b4c[15] = CreateSolidBrush(PALETTERGB(0, 165, 198));
        g_3b4c[16] = CreateSolidBrush(PALETTERGB(0, 155, 190));
        g_3b4c[17] = CreateSolidBrush(PALETTERGB(0, 130, 160));
        g_3b4c[18] = CreateSolidBrush(PALETTERGB(0, 100, 130));
        g_3b4c[19] = CreateSolidBrush(PALETTERGB(0, 100, 130));
    } else {
        g_3b4c[0] = CreateSolidBrush(PALETTERGB(255, 255, 0));
        g_3b4c[1] = CreateSolidBrush(PALETTERGB(220, 215, 0));
        g_3b4c[2] = CreateSolidBrush(PALETTERGB(200, 140, 0));
        g_3b4c[3] = CreateSolidBrush(PALETTERGB(175, 100, 0));
        g_3b4c[4] = CreateSolidBrush(PALETTERGB(135, 65, 0));
        g_3b4c[5] = CreateSolidBrush(PALETTERGB(105, 25, 0));
        g_3b4c[6] = CreateSolidBrush(PALETTERGB(80, 5, 0));
        g_3b4c[7] = CreateSolidBrush(PALETTERGB(50, 0, 0));
        g_3b4c[8] = CreateSolidBrush(PALETTERGB(25, 0, 0));
        g_3b4c[9] = CreateSolidBrush(PALETTERGB(10, 0, 0));
        g_3b4c[10] = CreateSolidBrush(PALETTERGB(0, 255, 255));
        g_3b4c[11] = CreateSolidBrush(PALETTERGB(0, 215, 230));
        g_3b4c[12] = CreateSolidBrush(PALETTERGB(0, 175, 205));
        g_3b4c[13] = CreateSolidBrush(PALETTERGB(0, 130, 160));
        g_3b4c[14] = CreateSolidBrush(PALETTERGB(0, 100, 130));
        g_3b4c[15] = CreateSolidBrush(PALETTERGB(0, 60, 110));
        g_3b4c[16] = CreateSolidBrush(PALETTERGB(0, 30, 90));
        g_3b4c[17] = CreateSolidBrush(PALETTERGB(0, 0, 60));
        g_3b4c[18] = CreateSolidBrush(PALETTERGB(0, 0, 26));
        g_3b4c[19] = CreateSolidBrush(PALETTERGB(0, 0, 10));
    }
}

/* Copy-protection and evaluation-period check [inferred]: with a != 0
 * checks the CD drive named in WIN.INI ("CDDrive"); then checks a key
 * through g_fp_3c68 and derives a day count from SYSTEM.INI/WIN.INI
 * values (g_9224 = days left [inferred]). Sets g_920c (-1, 0..3). */
/* 10:885e */
int16_t fn_10_885e(int16_t a)
{
    char msg[150];
    char buf[100];
    char drv[80];
    int16_t r;
    int16_t yr;
    int16_t day;
    int16_t y;
    int16_t v1;
    int16_t v3;
    int16_t v2;
    int16_t chk;
    int16_t pad;
    struct tm *tm;
    time_t t;
    int32_t lv3;
    int32_t l;
    int16_t r2;
    int16_t flag;
    char path[120];
    int16_t pad2;
    int16_t u;

    if (g_920c == -1)
        return 1;
    time(&t);
    tm = localtime(&t);
    yr = tm->tm_year - 93;
    day = yr * 365 + tm->tm_yday;
    g_922c = 1;
    g_922a = g_11aa = g_920c = flag = 0;
    if (a != 0) {
        GetProfileString(app_name, "CDDrive", "", drv, 40);
        if (drv[0]) {
            r = g_fp_3c68(drv, buf, 21);
            if (r == 0) {
                g_920c = -1;
                g_11aa = 1;
                return 0;
            }
            switch (r) {
            case 1:
                fn_02_094c(0x9ef);
                break;
            case 2:
                fn_02_094c(0x9f0);
                break;
            }
            wsprintf(msg, g_8e68, (LPSTR)drv);
            MessageBox(0, msg, app_name, MB_ICONEXCLAMATION);
            return -10;
        }
    }
    if (g_05d0 == 1 && (g_1122 + 1) / 2 == g_1120) {
        flag = 1;
    } else if (g_05d0 == 2 && g_1122 == 8 && g_1120 == 0x16a0) {
        g_920c = 3;
        return 0;
    }
    r2 = g_fp_3c68(msg, buf, 2);
    if (r2 == 0 && flag == 0) {
        g_920c = -1;
        if (fn_10_946a(msg))
            g_11aa = 1;
        return 0;
    }
    if (r2 >= 1) {
        GetWindowsDirectory(path, 110);
        u = lstrlen(path);
        if (path[u - 1] != '\\')
            lstrcat(path, "\\");
        lstrcat(path, "SYSTEM.INI");
        v1 = GetPrivateProfileInt("386Enh", "vidsp", 0, path);
        v2 = GetPrivateProfileInt("386Enh", "32BitSP", 0, path);
        v3 = GetProfileInt("windows", "PDev", 0);
        lv3 = v3;
        l = (int32_t)v1 * 2 - lv3 - 0x4cf;
        chk = (int16_t)l;
        v3 -= v1;
        y = v3 ^ 0xff;
        day -= y;
        g_9224 = day + 1;
        if (g_9224 < 1)
            g_9224 = 200;
        if (chk == v2) {
            g_9224 = -1 - day;
            if (day >= 0 && day < 35) {
                g_920c = 2;
                flag = 0;
                return 0;
            }
        }
        if (!flag && day >= 0 && day < 14) {
            g_920c = 1;
            return 0;
        }
    }
    if (r2 == 1000)
        g_922a = 1;
    g_920c = 0;
    return 1;
}

/* Stores GetProcAddress(g_9210, ord) into the function pointer fp and
 * clears ok when the DLL lacks it. */
#define GETPROC(fp, ord) \
    *(FARPROC *)&(fp) = GetProcAddress((HINSTANCE)g_9210, MAKEINTRESOURCE(ord)); \
    if (!(fp)) \
        ok = 0

/* Loads the language DLL (<Language>_LANG.DLL, g_9212) and ISPACE.DLL
 * (g_9210) from the game directory g_8f7a and fetches the ISPACE.DLL entry
 * points by ordinal; returns 0 after a message box when anything fails.
 * A missing ISPACE.DLL only warns [sic]. */
/* 10:6656 */
int16_t fn_10_6656(void)
{
    OFSTRUCT of;
    int16_t ok;
    char path[110];
    char text[150];
    char msg[40];

    lstrcpy(path, g_8f7a);
    GetPrivateProfileString(app_name, "Language", "", text, 5, ini_name);
    lstrcat(path, text);
    lstrcat(path, "_LANG.DLL");
    if (OpenFile(path, &of, OF_EXIST) == -1) {
        lstrcpy(text, "Can't find ");
        lstrcat(text, path);
        lstrcat(text, ". Try reinstalling, do not preserve previous settings.");
        MessageBox(0, text, app_name, MB_ICONEXCLAMATION);
        return 0;
    }
    lang_module = LoadLibrary(path);
    if (lang_module < 32) {
        lstrcpy(text, path);
        lstrcat(text, " is faulty");
        MessageBox(0, text, app_name, MB_ICONEXCLAMATION);
        return 0;
    }
    lstrcpy(path, g_8f7a);
    lstrcat(path, "ISPACE.DLL");
    if (OpenFile(path, &of, OF_EXIST) == -1) {
        LoadString(lang_module, 0x845, text, 40);
        lstrcat(text, path);
        lstrcat(text, "!");
        MessageBox(0, text, app_name, MB_ICONEXCLAMATION);
    }
    g_9210 = LoadLibrary(path);
    if ((HINSTANCE)g_9210 < 32) {
        lstrcpy(text, path);
        LoadString(lang_module, 0x7ea, msg, 40);
        lstrcat(text, msg);
        MessageBox(0, text, app_name, MB_ICONEXCLAMATION);
        return 0;
    }
    ok = 1;
    GETPROC(g_fp_3c28, 1);
    GETPROC(g_fp_3c2c, 3);
    GETPROC(g_fp_3c30, 2);
    GETPROC(g_fp_3c3c, 0x12);
    GETPROC(g_fp_3c38, 0x11);
    GETPROC(g_fp_3c50, 4);
    GETPROC(g_fp_3c4c, 5);
    GETPROC(g_fp_3c40, 6);
    GETPROC(g_fp_3c34, 0xc);
    GETPROC(g_fp_3c44, 0xf);
    GETPROC(g_fp_3c54, 7);
    GETPROC(g_fp_3c68, 0x18);
    GETPROC(g_fp_3c58, 8);
    GETPROC(g_fp_3c5c, 9);
    GETPROC(g_fp_3c6c, 0x1d);
    GETPROC(g_fp_3c70, 0x22);
    GETPROC(g_fp_3c74, 0x21);
    GETPROC(g_fp_3c64, 0xa);
    GETPROC(g_fp_3c7c, 0xe);
    GETPROC(g_fp_3c48, 0x24);
    GETPROC(g_fp_3c80, 0x23);
    GETPROC(g_fp_3c78, 0x20);
    GETPROC(g_fp_3c84, 0x29);
    if (!ok) {
        lstrcpy(text, path);
        LoadString(lang_module, 0x7ea, msg, 40);
        lstrcat(text, msg);
        MessageBox(0, text, app_name, MB_ICONEXCLAMATION);
        return 0;
    }
    /* g_fp_3c54 returns int here */
    if (!((int16_t (*)(int32_t, int16_t))g_fp_3c54)(g_05a0, 5)
        || !((int16_t (*)(int32_t, int16_t))g_fp_3c54)(g_05a0, 7))
        return 0;
    return 1;
}

/* Builds object n's two rows in sprite surface 34 (g_39e8[34]): five
 * cells copied from its surface 40 + n at the class's f50 offsets, the
 * class's f44 frame from the g_3c60 bitmaps masked over them, black
 * borders, then mirrored copies via fn_10_9962 [inferred]. pal1/pal2 are
 * read uninitialised when g_920e is 0 (as in the original). */
/* 10:5d3c */
void fn_10_5d3c(int16_t n)
{
    int16_t i;
    int16_t j;
    int16_t u8;
    int16_t sz;
    int16_t u;
    int16_t w;
    int16_t lst;
    HDC dc3;
    HDC dc2[2];
    HDC dc1[2];
    HBITMAP bm[2];
    HBITMAP old1[2];
    HBITMAP old2[2];
    HBITMAP bm3;
    HBITMAP old3;
    HPALETTE pal2[2];
    HPALETTE pal1[2];
    int16_t v;
    int16_t z;
    POINT pt;

    sz = 9;
    z = 0;
    if (subgame_active) {
        sz = g_9156 * 6 + 3;
        lst = 20;
    } else {
        sz = (sz << g_9156) >> 1;
        lst = g_9324;
    }
    i = 0;
    w = object_records[lst][n].f_22;
    v = g_96d2[g_7090[n].f_04e].f_44;
    dc1[i] = CreateCompatibleDC(main_dc);
    if (game_palette)
        pal1[i] = SelectPalette(dc1[i], game_palette, 0);
    old1[i] = SelectObject(dc1[i], bm[i] = fn_10_6ec6(g_3c60[i]));
    dc2[i] = CreateCompatibleDC(main_dc);
    old2[i] = SelectObject(dc2[i], g_3c60[i]);
    if (game_palette)
        pal2[i] = SelectPalette(dc2[i], game_palette, 0);
    if (g_7090[n].f_0e4) {
        fn_10_16ba(g_7090[n].f_04e);
        for (i = 0; i < 5; i++) {
            if (i < 5)
                pt = g_96d2[g_7090[n].f_04e].f_50[i];
            BitBlt(g_39e8[34], sz * i, sz * n * 2, sz, sz, g_39e8[40 + n],
                   object_records[g_9324][n].f_24 + (object_records[g_9324][n].f_24 + w) * i + pt.x,
                   object_records[g_9324][n].f_24 + pt.y, SRCCOPY);
        }
        if (g_96d2[g_7090[n].f_04e].f_48) {
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc2[0], 0, v * sz, SRCCOPY);
            SelectObject(g_39e8[34], g_3974[34]);
            bm3 = fn_10_6ec6(g_3ad0[34]);
            dc3 = CreateCompatibleDC(main_dc);
            old3 = SelectObject(dc3, bm3);
            g_3974[34] = SelectObject(g_39e8[34], g_3ad0[34]);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc3, 0, 0, SRCAND);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, g_39e8[34], 0, sz * n * 2, SRCPAINT);
            SelectObject(dc3, old3);
            DeleteDC(dc3);
            DeleteObject(bm3);
        } else {
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, g_39e8[34], 0, sz * n * 2, SRCCOPY);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc1[0], 0, v * sz, SRCAND);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc2[0], 0, v * sz, SRCPAINT);
        }
        for (i = 0; i < 5; i++) {
            if (i < 5)
                pt = g_96d2[g_7090[n].f_04e].f_50[i];
            PatBlt(g_39e8[34], sz * i, (n * 2 + 1) * sz, sz, max((int16_t)(-pt.y), 0), BLACKNESS);
            PatBlt(g_39e8[34], sz * i, (n * 2 + 1) * sz, max((int16_t)(-pt.x), 0), sz, BLACKNESS);
            PatBlt(g_39e8[34], sz * i, (n * 2 + 1) * sz + max((int16_t)(w - pt.y), 0), sz,
                   max((int16_t)(pt.y - w + sz), 0), BLACKNESS);
            PatBlt(g_39e8[34], sz * i + min((int16_t)(w - pt.x - 1), sz), (n * 2 + 1) * sz,
                   u = max((int16_t)(pt.x - w + sz + 1), 0), sz, BLACKNESS);
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            if (i == 0)
                fn_10_9962(1, g_39e8[34], sz * 8, (n * 2 + j + 1) * sz - 1, sz, -sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
            else if (i == 4)
                fn_10_9962(1, g_39e8[34], sz * 13 - 1, (n * 2 + j) * sz, -sz, sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
            else {
                fn_10_9962(1, g_39e8[34], (8 - i) * sz, (n * 2 + j + 1) * sz - 1, sz, -sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
                fn_10_9962(1, g_39e8[34], (i + 9) * sz - 1, (n * 2 + j + 1) * sz - 1, -sz, -sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
                fn_10_9962(1, g_39e8[34], (17 - i) * sz - 1, (n * 2 + j) * sz, -sz, sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
            }
        }
    }
    for (i = 0; i < 1; i++) {
        if (dc2[i]) {
            if (pal2[i])
                SelectPalette(dc2[i], pal2[i], 0);
            SelectObject(dc2[i], old2[i]);
            DeleteDC(dc2[i]);
            dc2[i] = 0;
        }
        if (dc1[i]) {
            if (pal1[i])
                SelectPalette(dc1[i], pal1[i], 0);
            SelectObject(dc1[i], old1[i]);
            DeleteDC(dc1[i]);
            dc1[i] = 0;
            if (bm[i]) {
                DeleteObject(bm[i]);
                bm[i] = 0;
            }
        }
    }
}
/* map position (world units / 8) scaled to the w x h picture */
                                                                         
                                                                      
                                                                                
#define SC(n) ((int16_t)((n) << g_9156) >> 1)
                                                                        

/* World map of map `map`, scaled to w x h. c == -1 (and !e): into a new
   bitmap (returned); otherwise into g_93d0, and c == 8 marks only marker d
   [inferred]. */
/* 10:8b1c */
HBITMAP world_map(int16_t w, int16_t h, int16_t a, int16_t map, int16_t c, int16_t d, int16_t e)
{
    HDC dc;
    HBITMAP bm;
    int16_t unused;         /* never used */
    HPALETTE oldpal;
    HGDIOBJ oldpen;
    HGDIOBJ oldbr;
    int16_t y;
    int16_t x;
    int16_t y2;
    int16_t x2;
    int16_t i;

    if (c == -1 && !e) {
        dc = CreateCompatibleDC(main_dc);
        SelectObject(dc, bm = CreateCompatibleBitmap(main_dc, w, h));
        if (game_palette)
            oldpal = SelectPalette(dc, game_palette, 0);
        PatBlt(dc, 0, 0, w, h, BLACKNESS);
    } else
        dc = g_93d0;
    if (a)
        oldpen = SelectObject(dc, g_3b44[0]);
    else
        oldpen = SelectObject(dc, GetStockObject(BLACK_PEN));
    oldbr = SelectObject(dc, g_500c);
    for (i = 0; i < g_9ebc[map]; i++) {
        if (c == -1 || c == 8 && d - g_9eb9[g_9322] - g_9318 * 2 == i) {
            x = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][g_9eb9[map] + i].x)) / 8 - (LO16(g_05a0)) / 2) * w / (LO16(g_05a0))) + w / 2;
            y = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][g_9eb9[map] + i].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
            if (c == 8 && !e)
                PatBlt(dc, x + w / -80, y + w / -80, max(w / 50, 4), max(w / 50, 4),
                       BLACKNESS);
            else
                StretchBlt(dc, x + w / -80, y + w / -80, max(w / 50, 4), max(w / 50, 4),
                           g_93cc, 80, 0, 4, 4, MERGECOPY);
        }
    }
    if (c != 8) {
        SetStretchBltMode(dc, COLORONCOLOR);
        for (i = 0; i < g_9eb6[map]; i++) {
            x = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][i].x)) / 8 - (LO16(g_05a0)) / 2) * w / (LO16(g_05a0))) + w / 2;
            y = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][i].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
            StretchBlt(dc, x - max(w / 100, 1), y - max(w / 100, 1),
                       max(w / 50, 3), max(w / 50, 3),
                       g_3a24, SC(4), SC(4), SC(14), SC(14), SRCCOPY);
        }
        SelectObject(dc, g_5006);
        x = (int16_t)((int32_t)(((g_a120[map].x)) / 8 - (LO16(g_05a0)) / 2 + ((-170))) * w / (LO16(g_05a0))) + w / 2;
        x2 = (int16_t)((int32_t)(((g_a120[map].x)) / 8 - (LO16(g_05a0)) / 2 + ((170))) * w / (LO16(g_05a0))) + w / 2;
        y = (int16_t)((int32_t)(((g_a120[map].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
        PatBlt(dc, x + w / -80, y + w / -80, max(w / 50, 3), max(w / 50, 3), PATCOPY);
        PatBlt(dc, x2 + w / -80, y + w / -80, max(w / 50, 3), max(w / 50, 3), PATCOPY);
        SelectObject(dc, g_5008);
        PatBlt(dc, x + w / 80, y + w / -280, x2 - max(w / 50, 3) - x,
               max(w / 140, 1), PATCOPY);
        if (w != g_0a72) {
            for (i = 0; i < g_9ebf[map]; i++) {
                x = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][g_9eb9[map] + g_9ebc[map] + i].x)) / 8 - (LO16(g_05a0)) / 2) * w / (LO16(g_05a0))) + w / 2;
                y = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][g_9eb9[map] + g_9ebc[map] + i].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
                StretchBlt(dc, x - max(w / 100, 2), y - max(w / 100, 2),
                           max(w / 50, 3), max(w / 50, 3),
                           g_39f0, object_records[4]->f_24, object_records[4]->f_24, object_records[4]->f_22, object_records[4]->f_22,
                           SRCCOPY);
            }
            x = (int16_t)((int32_t)(((g_a120[map].x)) / 8 - (LO16(g_05a0)) / 2) * w / (LO16(g_05a0))) + w / 2;
            y = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][0].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
            StretchBlt(dc, x - (int16_t)(object_records[14][main_ship].f_20 / 8 * w) / 3200,
                       y - (int16_t)(object_records[14][main_ship].f_20 / 8 * w) / 800,
                       (int16_t)(object_records[14][main_ship].f_20 / 8 * w) / 1600, (int16_t)(object_records[14][main_ship].f_20 / 8 * w) / 1600,
                       g_3a38[main_ship], object_records[14][main_ship].f_22 * 4 + object_records[14][main_ship].f_24 * 5,
                       object_records[14][main_ship].f_24, object_records[14][main_ship].f_22, object_records[14][main_ship].f_22, SRCCOPY);
        }
        SelectObject(dc, g_500c);
        x = (int16_t)((int32_t)(((g_a120[map].x)) / 8 - (LO16(g_05a0)) / 2 + ((40))) * w / (LO16(g_05a0))) + w / 2;
        y = (int16_t)((int32_t)(((g_9ea8[map].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
        y2 = (int16_t)((int32_t)(((g_9ea8[map].x)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
        PatBlt(dc, x, y2, max(w / 140, 1), y - y2, PATCOPY);
    }
    if (c == -1 || a) {
        for (i = 0; i < g_9eb9[map]; i++) {
            if (g_9ec2[map][i] != i) {
                x2 = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][i].x)) / 8 - (LO16(g_05a0)) / 2) * w / (LO16(g_05a0))) + w / 2;
                y2 = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][i].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
                MoveTo(dc, x2, y2);
                x = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][g_9ec2[map][i]].x)) / 8 - (LO16(g_05a0)) / 2) * w / (LO16(g_05a0))) + w / 2;
                y = (int16_t)((int32_t)(((VIEWP(POINT (*)[0x28], g_9f40[0][0].a, 0)[map][g_9ec2[map][i]].y)) / 8 - HI16(g_05a0) / 2) * h / HI16(g_05a0)) + h / 2;
                LineTo(dc, x, y);
            }
        }
    }
    SelectObject(dc, oldbr);
    SelectObject(dc, oldpen);
    if (c == -1 && !e) {
        SelectObject(dc, bm);
        if (game_palette)
            SelectPalette(dc, oldpal, 0);
        DeleteDC(dc);
    }
    return bm;
}
