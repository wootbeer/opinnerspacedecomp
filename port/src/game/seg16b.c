/* INSPACE.EXE segment 16 (selector 1078), source file 32 of
 * inventory/files.tsv: 16:7210-end. */
#include "game.h"

/* 16:7210 */
void fn_16_7210(void)
{
    char unused[96];
    DWORD t;

    switch (g_92be) {
    case 0:
        fn_11_02f0();
        g_1e58 += 50000;
        fn_06_885c(1, 2);
        fn_15_302e();
        g_92be++;
        break;
    case 1:
        fn_15_3590();
        break;
    case 2:
        fn_15_302e();
        g_92be++;
        break;
    case 3:
        fn_15_3590();
        break;
    case 4:
        t = GetCurrentTime();
        do
            fn_10_740c();
        while (GetCurrentTime() < t + 1500);
        fn_16_7396();
        g_92be++;
        break;
    case 5:
        fn_15_1584(0);
        break;
    case 6:
        fn_10_744c(0x66);
        t = GetCurrentTime();
        do
            fn_10_740c();
        while (GetCurrentTime() < t + 3500);
        g_92be++;
        break;
    case 7:
        fn_15_1584(0);
        g_1c68 = 0;
        g_92be++;
        break;
    case 8:
        if (g_1c68 == 0) {
            g_1c68 = GetCurrentTime() + 7000;
        } else if (GetCurrentTime() > g_1c68) {
            PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
            g_92be++;
        }
        break;
    case 9:
        PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
        fn_15_1328(1);
        fn_15_14be();
        fn_10_6e76(8L);
        fn_10_6dd4(0);
        g_1e84 = g_1e50;
        break;
    }
}

/* Builds the save-game summary text (age, flight time) [inferred]. */
/* 16:7396 */
void fn_16_7396(void)
{
    char pad0[14];
    int16_t days;
    int16_t m;
    DWORD size;
    char pad1[6];
    HGLOBAL h;
    REC_1A9_seg16 *p;
    char bufbc[152];
    char buf184[200];
    char buf288[260];
    char buf2a6[30];
    int16_t pad2;
    int32_t d2;
    int32_t d1;
    int32_t c;
    int32_t s;
    int32_t t;
    int32_t hours;
    int32_t mins;

    g_93a8 = GlobalAlloc(GHND, 2000L);
    g_4fcc = GlobalLock(g_93a8);
    lstrcpy(g_4fcc, "");
    LoadString(g_9212, 0x84e, buf184, 40);
    lstrcat(g_4fcc, buf184);
    lstrcat(g_4fcc, g_09f2);
    lstrcat(g_4fcc, g_380c);
    lstrcat(g_4fcc, "!!");
    lstrcat(g_4fcc, "\r\n");
    h = GlobalAlloc(GHND, 0x1a9L);
    GlobalLock(h);
    size = GlobalSize(h);
    GlobalUnlock(h);
    h = GlobalReAlloc(h, size, GHND);
    p = (REC_1A9_seg16 *)GlobalLock(h);
    fn_06_8eea(p);
    d1 = p->f_01d;
    if (d1 < 90)
        d1 += 100;
    d1 *= 365;
    d1 += p->f_01b * 30;
    d1 += p->f_01c;
    d2 = p->f_01a;
    if (d2 < 90)
        d2 += 100;
    d2 *= 365;
    d2 += p->f_018 * 30;
    d2 += p->f_019;
    d1 -= d2;
    days = (int16_t)d1 < 1 ? 1 : (int16_t)d1;
    if (days > 30)
        m = (int16_t)(days * 10) / 30;
    else
        m = 0;
    if (m > 9) {
        fn_06_1010(m, 10, 1, buf184);
        LoadString(g_9212, 0x850, buf2a6, 200);
        lstrcat(buf184, buf2a6);
        if (m != 10)
            lstrcat(buf184, "S");
    } else {
        fn_06_0f1a(days, bufbc);
        lstrcpy(buf184, bufbc);
        LoadString(g_9212, 0x851, buf2a6, 200);
        lstrcat(buf184, buf2a6);
        if (days != 1)
            lstrcat(buf184, "S");
    }
    fn_15_6558(g_94ac, buf288);
    fn_10_a332(g_4fcc, (char *)0x84f, 0, (LPSTR)buf184, p->f_024, 0x9d6, (LPSTR)buf288);
    if (p->f_15a || p->f_15c)
        fn_10_a332(g_4fcc, (char *)0xbcd, 0, p->f_15a, p->f_15a, 0x9d3, p->f_15c, p->f_15c, 0x9d3);
    fn_15_6558(g_94ac, buf184);
    fn_10_a332(g_4fcc, (char *)0xbce, 0, p->f_032, 0x13e, p->f_01e);
    t = p->f_18b / 36;
    mins = t / 60;
    hours = mins / 60;
    c = mins - hours * 60;
    s = t - mins * 60;
    if (hours >= 1)
        fn_10_a332(g_4fcc, (char *)0xbe4, 0, (int16_t)hours, (int16_t)hours, g_09f2, (int16_t)c, 0x9ce,
                   (LPSTR)buf184, 4, 0x2b0, (LPSTR)g_380c);
    else
        fn_10_a332(g_4fcc, (char *)0xbe4, 0, (int16_t)mins, (int16_t)mins, 0x9ce, (int16_t)s, 0x9cf,
                   (LPSTR)buf184, 4, 0x2b0, (LPSTR)g_380c);
    GlobalUnlock(h);
    GlobalFree(h);
    fn_11_3fd4(g_4fcc, 1);
    g_92d4 = 0;
    fn_15_1584(1);
}

