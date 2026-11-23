/* INSPACE.EXE segment 16 (selector 1078), source file 32 of
 * inventory/files.tsv: 16:7210-end. */
#include "inspace.h"

extern int g_0010;
extern int g_90ea;
#pragma pack(1)
typedef struct {                /* 0x1a9-byte save summary [inferred] */
    char p00[0x18];
    signed char f18;
    signed char f19;
    signed char f1a;
    signed char f1b;
    signed char f1c;
    signed char f1d;
    DWORD f1e;
    char p22[0x24 - 0x22];
    int f24;
    char p26[0x32 - 0x26];
    int f32;
    char p34[0x15a - 0x34];
    int f15a;
    int f15c;
    char p15e[0x18b - 0x15e];
    DWORD f18b;
    char p18f[0x1a9 - 0x18f];
} REC_1A9;
#pragma pack()
extern HGLOBAL g_93a8;
extern char far *g_4fcc;
extern char g_09f2[];
extern char g_380c[];
extern int g_94ac;
extern int g_92d4;
void far fn_06_8eea(REC_1A9 far *p);
void far fn_06_0f1a(int n, LPSTR buf);
void far fn_15_6558(int a, LPSTR buf);
void far fn_11_3fd4(LPSTR s, int a);
void far fn_06_1010(int v, int div, int width, LPSTR buf);
extern long g_1e58;
extern DWORD g_1c68;
extern DWORD g_1e84;
extern int g_92be;
extern DWORD g_1e50;
void far fn_11_02f0(void);
void far fn_06_885c(int a, int b);
void far fn_15_302e(void);
void far fn_15_3590(void);
void far fn_10_740c(void);
void far fn_15_1584(int a);
void far fn_10_744c(int a);
void far fn_15_1328(int a);
void far fn_15_14be(void);
void far fn_10_6e76(int a, int b);
void far fn_10_6dd4(int a);
void far fn_10_a332(LPSTR text, char *cls, int a, ...);
void far fn_16_7396(void);

/* @addr 16:7210 */
void far fn_16_7210(void)
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
            PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
            g_92be++;
        }
        break;
    case 9:
        PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
        fn_15_1328(1);
        fn_15_14be();
        fn_10_6e76(8, 0);
        fn_10_6dd4(0);
        g_1e84 = g_1e50;
        break;
    }
}

/* Builds the save-game summary text (age, flight time) [inferred]. */
/* @addr 16:7396 */
void far fn_16_7396(void)
{
    char pad0[14];
    int days;
    int m;
    DWORD size;
    char pad1[6];
    HGLOBAL h;
    REC_1A9 far *p;
    char bufbc[152];
    char buf184[200];
    char buf288[260];
    char buf2a6[30];
    int pad2;
    long d2;
    long d1;
    long c;
    long s;
    long t;
    long hours;
    long mins;

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
    p = (REC_1A9 far *)GlobalLock(h);
    fn_06_8eea(p);
    d1 = p->f1d;
    if (d1 < 90)
        d1 += 100;
    d1 *= 365;
    d1 += p->f1b * 30;
    d1 += p->f1c;
    d2 = p->f1a;
    if (d2 < 90)
        d2 += 100;
    d2 *= 365;
    d2 += p->f18 * 30;
    d2 += p->f19;
    d1 -= d2;
    days = (int)d1 < 1 ? 1 : (int)d1;
    if (days > 30)
        m = days * 10 / 30;
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
    fn_10_a332(g_4fcc, (char *)0x84f, 0, (LPSTR)buf184, p->f24, 0x9d6, (LPSTR)buf288);
    if (p->f15a || p->f15c)
        fn_10_a332(g_4fcc, (char *)0xbcd, 0, p->f15a, p->f15a, 0x9d3, p->f15c, p->f15c, 0x9d3);
    fn_15_6558(g_94ac, buf184);
    fn_10_a332(g_4fcc, (char *)0xbce, 0, p->f32, 0x13e, p->f1e);
    t = p->f18b / 36;
    mins = t / 60;
    hours = mins / 60;
    c = mins - hours * 60;
    s = t - mins * 60;
    if (hours >= 1)
        fn_10_a332(g_4fcc, (char *)0xbe4, 0, (int)hours, (int)hours, g_09f2, (int)c, 0x9ce,
                   (LPSTR)buf184, 4, 0x2b0, (LPSTR)g_380c);
    else
        fn_10_a332(g_4fcc, (char *)0xbe4, 0, (int)mins, (int)mins, 0x9ce, (int)s, 0x9cf,
                   (LPSTR)buf184, 4, 0x2b0, (LPSTR)g_380c);
    GlobalUnlock(h);
    GlobalFree(h);
    fn_11_3fd4(g_4fcc, 1);
    g_92d4 = 0;
    fn_15_1584(1);
}

