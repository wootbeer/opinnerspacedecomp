/* INSPACE.EXE segment 16 (selector 1078). */
#include "inspace.h"

/* 0x15a-byte object records, DGROUP array at DS:7092 (base = lowest
 * offset accessed with an index * 0x15a; same layout as seg13.c). */
typedef struct {
    int f_000;    /* DS:7092 */
    char pad_002[0x6];
    int f_008;    /* DS:709a */
    int f_00a;    /* DS:709c */
    char pad_00c[0x6];
    int f_012;    /* DS:70a4 */
    char pad_014[0x2];
    int f_016;    /* DS:70a8 */
    char pad_018[0x4];
    int f_01c;    /* DS:70ae */
    int f_01e;    /* DS:70b0 */
    int f_020;    /* DS:70b2 */
    int f_022;    /* DS:70b4 */
    int f_024[5];    /* DS:70b6 */
    char pad_02e[0x1e];
    int f_04c;    /* DS:70de */
    char pad_04e[0xb];
    char f_059;    /* DS:70eb */
    char pad_05a[0x2];
    char f_05c;    /* DS:70ee */
    char pad_05d[0x25];
    DWORD f_082;    /* DS:7114 */
    char pad_086[0x4];
    long f_08a;    /* DS:711c */
    char pad_08e[0x1c];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    signed char f_0ac[10];    /* DS:713e */
    signed char f_0b6[10];    /* DS:7148 */
    char pad_0c0[0x9];
    signed char f_0c9;    /* DS:715b */
    char pad_0ca[0x2];
    int f_0cc;    /* DS:715e */
    char pad_0ce[0x6];
    int f_0d4;    /* DS:7166 */
    int f_0d6;    /* DS:7168 */
    char pad_0d8[0x2];
    long f_0da;    /* DS:716c */
    char f_0de;    /* DS:7170 */
    char f_0df;    /* DS:7171 */
    char f_0e0;    /* DS:7172 */
    char pad_0e1[0x9];
    char f_0ea;    /* DS:717c */
    char pad_0eb[0x5a];
    char f_145;    /* DS:71d7 */
    char pad_146[0x14];
} OBJ15A;

typedef struct {                /* 0x70-byte records */
    int f00;
    int f02;
    POINT f04;
    int f08;
    int f0a;
    int f0c;
    int f0e;
    char p10[0x18 - 0x10];
    int f18;
    int f1a;
    char p1c[0x20 - 0x1c];
    int f20;
    int f22;
    int f24;
    int f26;
    char p28[0x2e - 0x28];
    signed char f2e;
    char p2f[0x3a - 0x2f];
    int f3a;
    char p3c[0x44 - 0x3c];
    int f44;
    char p46[0x70 - 0x46];
} REC_70;

typedef struct {                /* 0x2e bytes (GlobalAlloc), far pointer at DS:6da4 */
    HWND f00;
    POINT f02;
    int f06;
    char f08[0x1c - 0x08];
    int f1c;
    int f1e;
    int f20;
    int f22;
    int f24;
    long f26;
    int f2a;
    int f2c;
} REC_6DA4;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    int f02;
    int f04[3];    /* indexed up to [3], which is f0a */
    int f0a;
    int f0c;
    char p0e[0x14 - 0x0e];
    int f14;
    char p16[0x52 - 0x16];
    char f52[0x8f - 0x52];    /* name [inferred] */
    int f8f;    /* seen only as [n - 1].f8f: the true base is lower [inferred] */
    int f91;
    int f93;
    char p95[0xad - 0x95];
} REC_AD;
#pragma pack()

extern OBJ15A g_7092[];
extern REC_AD g_96f0[];
extern int g_92e4;
extern int g_111e;
extern REC_70 far *g_1e14;
extern REC_70 far *g_1df8[16];
extern int g_9324;
extern int g_9646;
extern HWND g_9532;
extern int g_0010;
extern RECT g_6e08;
extern int g_9004;
extern int g_914a;
extern int g_920c;
extern int g_958a;
extern int g_958c;
extern int g_95bc;              /* flow.interactive */
extern int g_9660;
extern HFONT g_90fe;
extern char g_9564[];
extern int g_959c;
extern int g_90ea;
extern int g_9210;
extern int g_93a6;
extern HRGN g_9536;
extern int g_965e;
extern POINT g_6e14;
extern int g_9e55;
extern long g_9e57;
extern int g_9e5d;
extern int g_9406[];
typedef struct {                /* 0x7c-byte records, far pointer at DS:6e24 */
    int f00;
    char p02[0x1c - 0x02];
    unsigned char f1c;
    char p1d[0x32 - 0x1d];
    signed char f32[0x72 - 0x32];
    signed char f72;
    signed char f73;
    char p74[0x7a - 0x74];
    signed char f7a;
    signed char f7b;
} REC_7C;
extern REC_7C far *g_6e24;
extern REC_6DA4 far *g_6da4;
extern HBITMAP g_9590;
extern HGDIOBJ g_9592;
extern HPALETTE g_9594;
extern HDC g_95a0;
extern char g_9690[];
extern int g_9e41[5];
extern int g_952c;
extern HINSTANCE g_9588;
extern int g_959a;
extern HGLOBAL g_95a2;
extern long g_6da8;
extern int g_90f4;
extern int g_952e;
extern int g_9530;
extern int g_958e;
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
extern int music_pause_state;
extern int g_8ff4;
extern HRGN g_9538;
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
void far fn_10_7480(int a, int b);
void far fn_18_0000(void);
void far fn_11_72b2(void);
void far fn_11_7504(void);
extern int g_940e;
extern int g_91f8;
extern int g_11aa;
#pragma pack(1)
typedef struct {                /* 0x41-byte records, far pointer at DS:6e20 */
    char p00[0x0a];
    char f0a[0x41 - 0x0a];      /* name [inferred] */
} REC_41;
#pragma pack()
extern REC_41 far *g_6e20;
extern int g_95aa;
void far fn_14_3eda(void);
void far fn_14_4074(void);
void far fn_16_5f78(int i, int v);
extern HWND g_0a7e;
extern HWND g_0a7c;
void far fn_13_33d6(int i);
int far fn_10_82a2(int a);

void far fn_03_06ec(int a, int b, int c, int d);
void far fn_07_13b2(int a, int b, int c);
void far fn_12_2556(int a, int b);
void far fn_12_26a4(int a, int b);
void far fn_11_2f8c(void);
void far fn_12_6d64(int a, int b);
void far fn_06_1010(int v, int div, int width, LPSTR buf);
void far fn_06_0f54(long v, int div, int width, LPSTR buf);
void far fn_18_0be2(void);
void far fn_16_541c(HWND hDlg);
void far fn_16_44fa(HWND hDlg);
void far fn_16_4900(HWND hDlg);
void far fn_16_5db0(HWND hDlg);
void far fn_16_43f2(HWND hDlg);
int far fn_16_5f0e(LPSTR a, LPSTR b);
void far fn_18_0c5c(void);
void far fn_18_0378(int a);
void far fn_09_955c(int id, LPSTR buf);
void far fn_09_9580(int id, LPSTR buf);
void far fn_16_64fa(void);
void far fn_16_3784(int a, int b);
void far pascal fn_16_590c(DRAWITEMSTRUCT far *dis);
void far pascal fn_16_5ada(DRAWITEMSTRUCT far *dis);
extern long g_1e58;
extern DWORD g_1c68;
extern DWORD g_1e84;
extern int g_92be;
extern DWORD g_1e50;
extern DWORD g_2388;
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
void far fn_16_7396(void);
void far fn_16_5820(HWND hDlg);
void far pascal fn_16_5a8a(DRAWITEMSTRUCT far *dis);
void far fn_16_51d6(HWND hDlg);
void far fn_16_5b24(HWND hDlg);
BOOL far pascal fn_16_42a2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
extern int g_934e;
extern int g_913a;
extern int g_913c;
extern int g_92e8;
extern int g_94b2;
extern int g_9320;
extern int g_9e49;
extern int g_9e4b;
extern int g_9318;
extern REC_70 far *g_1e18;
extern REC_70 far *g_1e28;
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
void far fn_07_2080(int a, int b);
extern int g_3ca8;
extern int g_3caa;
extern int g_3cac;
extern int g_3cae;
extern int g_3ce6;
extern int g_3d48;
extern int g_3d4a;
extern int g_6dac;
extern int g_6dae;
extern int g_6db0;
extern int g_6db2;
extern int g_6db4;
extern int g_6db6;
extern int g_959e;
extern HBITMAP g_953c;
extern REC_70 far *g_1e30;
void far fn_16_27ea(void);
void far fn_16_2144(void);
extern int g_9156;
extern HBITMAP g_39c4[];
extern HDC g_3a38[];
extern HBITMAP g_3b20[];
void far fn_10_0552(int i, int a);
void far fn_14_1b84(int i, int n, int k, int t);
void far fn_14_11a8(int i);
void far fn_10_5d3c(int i);
void far fn_10_1460(int i);
void far fn_10_1620(int i);
void far fn_10_1502(int i);
extern int g_0928;
extern int g_929c;
extern int g_92a2;
extern int g_8f70;
extern DWORD g_1c64;
extern int g_93a4;
void far fn_09_6cc4(int flag);
void far fn_15_0760(void);
void far fn_15_0cb0(void);
void far fn_15_10be(void);
void far fn_16_6afe(void);
extern int g_9e5b;
void far fn_16_4bd8(HWND hDlg);
void far fn_16_5762(HWND hwnd, int n, int kind, LPSTR suffix);
typedef struct {                /* 0x50-byte records, DGROUP array at DS:2f54 */
    char p00[0x0a];
    int f0a;
    char p0c[0x34 - 0x0c];
    int f34;
    int f36;
    char p38[0x50 - 0x38];
} REC_50;
extern REC_50 g_2f54[];
void far fn_10_a332(LPSTR text, char *cls, int a, ...);
extern char g_953e;
extern char g_953f;
extern char g_9540;
extern char g_9541;
extern char g_9542[];
extern char g_955d[];
extern char g_9563;
extern char g_957f;
#include <stdlib.h>
extern int g_9316;
typedef struct {                /* 0x14-byte records, DGROUP array at DS:1e90 */
    int f00;
    int f02;
    char p04[0x06 - 0x04];
    int f06;
    int f08;
    int f0a;
    char p0c[0x10 - 0x0c];
    long f10;
} REC_14;
extern REC_14 g_1e90[45];
extern POINT g_5170[45];
extern POINT g_5224[45];
extern int g_9430;
extern int g_9130;              /* subgame_active */
extern int g_668a;
extern DWORD g_1e80;
extern int g_95a8;
extern long g_5078;
extern int g_951a;
void far fn_13_4710(int k);
void far fn_10_754a(int a, int b, int c, int d);
int far fn_11_aece(void);
void far fn_13_498e(int a, int b);
extern char g_06b0[];
extern POINT g_6e18;
extern POINT g_1c54;            /* ambulance text cursor [inferred] */
extern POINT g_1c58;            /* previous cursor [inferred] */
extern int g_1c5c;              /* index into ambulance_line */
extern int g_1c5e;              /* lines typed */
extern DWORD g_1c60;            /* next character time */
extern HRGN g_9534;
void far fn_15_84b0(int x, int y);

/* Parses a number from a short digit string [inferred]. */
/* near-match 48%: 16:0000 (CL refactors the digit sums: (a-48)*10+(b-48)*100 -> ((b*10+a)-528)*10) */
int far fn_16_0000(LPSTR s)
{
    int unused1;
    int r;
    int k;

    k = 0;
    if (s[0] == ' ' || s[0] == 'a') {
        k = 1;
        if (s[1] == ' ' || s[1] == 'a')
            k = 2;
    }
    if (s[k + 1] == '.') {
        r = (s[k + 2] - '0') * 10;
        r += (s[k] - '0') * 100;
    } else {
        r = (s[k] - '0') * 1000;
        r += (s[k + 3] - '0') * 10;
        r += (s[k + 1] - '0') * 100;
    }
    return r;
}

/* @addr 16:085e */
int far fn_16_085e(void)
{
    return 0;
}

/* @addr 16:0872 */
void far fn_16_0872(void)
{
    fn_16_3784(g_952e, 0);
    fn_03_06ec(g_952e, 7, 0, 0x54);
}

/* @addr 16:08a0 */
void far fn_16_08a0(void)
{
    fn_12_2556(7, 0);
    fn_07_13b2(1, 7, 0);
    g_9e41[4] = 10;
    g_952e = -1;
    g_111e = 0;
    g_6da8 = 0;
}

/* @addr 16:64c8 */
int far fn_16_64c8(void)
{
    char buf[398];

    g_9530 = 3;
    if (g_90f4 == 1)
        fn_18_0378(1);
    else
        fn_18_0378(0);
    return 1;
}

/* @addr 16:3e80 */
int far fn_16_3e80(int i)
{
    int d;

    d = (g_96f0[g_7092[i].f_04c].f00 - g_7092[i].f_01c) / 7;
    if (g_92e4 == 0)
        g_7092[i].f_01c = g_96f0[g_7092[i].f_04c].f00;
    return d / 10 * 10;
}

/* Owner-draw item handler [inferred]. */
/* @addr 16:5a8a */
void far pascal fn_16_5a8a(DRAWITEMSTRUCT far *dis)
{
    RECT rc;

    CopyRect(&rc, &dis->rcItem);
    if (dis->itemID == -1 || (dis->itemState & ODS_FOCUS))
        DrawFocusRect(dis->hDC, &rc);
    else
        fn_16_5ada(dis);
}

/* @addr 16:5ada */
void far pascal fn_16_5ada(DRAWITEMSTRUCT far *dis)
{
    RECT rc;

    fn_16_590c(dis);
    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_FOCUS)
        DrawFocusRect(dis->hDC, &rc);
}

/* @addr 16:614c */
void far fn_16_614c(int msg, int b, long c)
{
    if (g_9530 == 1) {
        if (msg == 0x9c5)
            msg = WM_LBUTTONDOWN;
        g_6da4->f22 = msg;
        g_6da4->f24 = b;
        g_6da4->f26 = c;
        g_9530 = 5;
        fn_16_64fa();
    }
}

/* @addr 16:68d6 */
void far fn_16_68d6(HWND hwnd, int id, int id2)
{
    char buf[280];

    fn_09_955c(id, buf);
    if (id2 != -1)
        fn_09_9580(id2, buf);
    MessageBox(hwnd, buf, g_9690, MB_ICONEXCLAMATION);
}

/* @addr 16:1f24 */
void far fn_16_1f24(void)
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

/* @addr 16:3730 */
int far fn_16_3730(int i, int j)
{
    int t;

    if (g_7092[i].f_0ac[j] == -1)
        return 0;
    t = (20 - g_7092[i].f_0ac[j]) * 10;
    g_7092[i].f_0ac[j] = 20;
    g_7092[i].f_0ac[0] = -1;
    return t / 10 * 10;
}

/* @addr 16:32a0 */
void far fn_16_32a0(void)
{
    g_9e41[0] = -1;
    g_9e41[1] = 50;
    g_9e41[2] = 5;
    g_9e41[3] = 15;
    fn_16_0872();
    g_1e14->f18 = 0;
    if (g_1e14->f2e == -1) {
        fn_12_2556(7, 0);
        fn_07_13b2(2, 7, 0);
        g_9e41[0] = 1;
    }
    g_9e41[4] = 6;
    g_111e = 0;
}

/* Nonzero when string a ends with string b [inferred]. */
/* @addr 16:5f0e */
int far fn_16_5f0e(LPSTR a, LPSTR b)
{
    int k;
    int i;
    int j;

    i = lstrlen(a) - 1;
    j = lstrlen(b) - 1;
    for (k = 0; k < lstrlen(b); k++, i--, j--)
        if (a[i] != b[j])
            return 0;
    return 1;
}

/* @addr 16:71a2 */
int far fn_16_71a2(int i, int j)
{
    int k;
    int r;

    r = g_7092[i].f_0b6[j];
    g_7092[i].f_0ac[j] = g_7092[i].f_0b6[j] = 0;
    for (k = j; k < 9; k++) {
        g_7092[i].f_0b6[k] = g_7092[i].f_0b6[k + 1];
        g_7092[i].f_0ac[k] = g_7092[i].f_0ac[k + 1];
    }
    g_7092[i].f_0ac[9] = g_7092[i].f_0b6[9] = 0;
    g_7092[i].f_0c9--;
    return r;
}

/* @addr 16:631c */
void far fn_16_631c(void)
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

/* @addr 16:3306 */
void far fn_16_3306(void)
{
    g_1df8[g_9324][g_952e].f18 = 0;
    g_1e14->f18 = 0;
    g_6da8 = 0;
    fn_12_26a4(g_9324, g_952e);
    fn_12_2556(g_9324, g_952e);
    fn_11_2f8c();
    if (g_1e14->f2e == -1) {
        fn_12_2556(7, 0);
        fn_07_13b2(2, 7, 0);
        g_9e41[3] = g_9e41[0] = 1;
        g_1e14->f44 = 800;
    }
    g_9e41[4] = 6;
}

/* @addr 16:3f88 */
int far fn_16_3f88(int i)
{
    int a;
    int b;
    int c;

    for (a = 24; a <= 25; a++) {
        for (b = 1; b < g_7092[g_9646].f_0c9; b++) {
            if (g_7092[g_9646].f_0b6[b] == a) {
                g_7092[g_9646].f_0ac[b] = g_7092[g_9646].f_0b6[b] = 0;
                for (c = b; c < 9; c++) {
                    g_7092[g_9646].f_0b6[c] = g_7092[g_9646].f_0b6[c + 1];
                    g_7092[g_9646].f_0ac[c] = g_7092[g_9646].f_0ac[c + 1];
                }
                g_7092[g_9646].f_0ac[9] = g_7092[g_9646].f_0b6[9] = 0;
                break;
            }
        }
    }
    g_7092[g_9646].f_0c9 -= 2;
    fn_12_6d64(g_9646, 0x1a);
    return 250;
}

/* @addr 16:3ece */
int far fn_16_3ece(int i)
{
    if (g_7092[i].f_008 == 2)
        return 0;
    g_7092[i].f_022 = g_7092[i].f_008 = 2;
    if (g_7092[i].f_0aa != 0 || g_96f0[g_7092[i].f_04c].f0a != 3)
        g_7092[i].f_0de = 1;
    else
        g_7092[i].f_0de = 0;
    if (g_7092[i].f_0ab != 0 || g_96f0[g_7092[i].f_04c].f0a != 3)
        g_7092[i].f_0df = 1;
    else
        g_7092[i].f_0df = 0;
    if (g_7092[i].f_0aa == 0 && g_7092[i].f_0ab == 0
        && g_96f0[g_7092[i].f_04c].f0a == 3) {
        g_7092[i].f_022 = 1;
        g_7092[i].f_0de = 1;
    }
    return 250;
}

/* @addr 16:5762 */
void far fn_16_5762(HWND hwnd, int n, int kind, LPSTR suffix)
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
/* @addr 16:33a2 */
int far fn_16_33a2(void)
{
    POINT pt;
    RECT rc;
    int g;
    int j;
    int r;

    pt = g_1e14->f04;
    r = 1;
    SetRect(&rc, pt.x - 560, pt.y - 640, pt.x + 1600, pt.y + 640);
    for (g = 0; g <= g_9324; g++) {
        if (g == 7)
            continue;
        for (j = 0; j < g_9406[g]; j++) {
            if (g == g_9324 && j == g_952e)
                continue;
            if (g_1df8[g][j].f18 == 0 && PtInRect(&rc, g_1df8[g][j].f04)) {
                return r = 0;
            }
        }
    }
    return r;
}

/* @addr 16:4030 */
int far fn_16_4030(int i, int j)
{
    g_6e24[g_7092[i].f_0d4].f32[j]++;
    if (g_7092[i].f_0d4 != -1)
        g_7092[i].f_012 = (int)(1200L * g_96f0[g_7092[i].f_04c].f02
            / ((long)((g_6e24[g_7092[i].f_0d4].f32[1] + 10) * 10) * g_7092[i].f_00a / 100));
    if (j > 1)
        return (g_6e24[g_7092[i].f_0d4].f32[j] + 1) * 100;
    return (g_6e24[g_7092[i].f_0d4].f32[j] + 3) * 100;
}

/* @addr 16:5820 */
void far fn_16_5820(HWND hDlg)
{
    char num[50];
    char text[50];
    int v;

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

/* @addr 16:43f2 */
void far fn_16_43f2(HWND hDlg)
{
    int i;
    int v;
    int n;
    int items[100];
    int enable;
    char text[60];

    n = (int)SendMessage(GetDlgItem(hDlg, 0x65), LB_GETSELCOUNT, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), LB_GETSELITEMS, n, (LPARAM)(int far *)items);
    enable = 0;
    for (i = 0; i < n; i++) {
        SendMessage(GetDlgItem(hDlg, 0x65), LB_GETTEXT, items[i], (LPARAM)(LPSTR)text);
        v = fn_16_0000(text);
        if (v <= g_9e57 || text[0] == ' ')
            enable = 1;
    }
    EnableWindow(GetDlgItem(hDlg, 0x69), enable);
    n = (int)SendMessage(GetDlgItem(hDlg, 0x66), LB_GETSELCOUNT, 0, 0L);
    if (n)
        EnableWindow(GetDlgItem(hDlg, 0x6a), 1);
    else
        EnableWindow(GetDlgItem(hDlg, 0x6a), 0);
}

/* Mouse click handler [inferred]. */
/* @addr 16:638a */
void far fn_16_638a(int w, LPARAM lParam, int flag)
{
    POINT pt;
    int hit;
    RECT rc;

    if (!g_95bc)
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
            CopyRect(&rc, &g_6e08);
        else
            SetRect(&rc, 0, 0, g_6e08.right, g_0010);
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
/* @addr 16:42a2 */
BOOL far pascal fn_16_42a2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    DRAWITEMSTRUCT far *dis;
    TEXTMETRIC tm;
    HDC hdc;
    HFONT old;
    MEASUREITEMSTRUCT far *mis;

    switch (msg) {
    case WM_INITDIALOG:
        fn_16_541c(hDlg);
        break;
    case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT far *)lParam;
        if (dis->itemID == -1)
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
        mis = (MEASUREITEMSTRUCT far *)lParam;
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

/* @addr 16:619e */
int far fn_16_619e(void)
{
    POINT sz;

    if (g_93a6)
        return 0;
    if (!(g_95a2 = GlobalAlloc(GHND, 0x2eL)))
        return 0;
    g_6da4 = (REC_6DA4 far *)GlobalLock(g_95a2);
    if (g_6da4 == NULL) {
        GlobalFree(g_95a2);
        return 0;
    }
    if (g_90f4 == 6) {
        g_6da4->f02 = g_6e14;
    } else {
        if (g_9536) {
            DeleteObject(g_9536);
            g_9536 = 0;
        }
        if (g_965e == 1) {
            sz.x = g_90ea;
            sz.y = g_0010;
        } else {
            sz.x = 0xa0;
            sz.y = 0x82;
        }
        SetRect(&g_6e08, g_90ea / 2 - sz.x / 2, g_0010 / 2 - sz.y / 2,
                g_90ea / 2 + sz.x / 2, g_0010 / 2 + sz.y / 2);
        g_6da4->f02 = sz;
        PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
        g_9536 = CreateRectRgn(g_6e08.left, g_6e08.top, g_6e08.right, g_6e08.bottom);
    }
    g_6da4->f06 = 0;
    g_6da4->f00 = g_0016;
    g_6da4->f1e = g_920e;
    g_6da4->f20 = g_9210;
    g_6da4->f2a = 0x24;
    g_6da4->f2c = 0;
    lstrcpy(g_6da4->f08, "...");
    g_959a = 0;
    fn_16_64c8();
    g_958a = 1;
    return 1;
}

/* @addr 16:44fa */
void far fn_16_44fa(HWND hDlg)
{
    int i;
    int j;
    int k;
    int v;
    int n;
    WORD sel[100];
    char buf[50];
    char buf2[80];
    int ok;
    int flag;
    int match;
    char buf3[20];
    char c;
    char msg[180];

    n = SendMessage(GetDlgItem(hDlg, 0x65), 0x411, 0, 0L);
    SendMessage(GetDlgItem(hDlg, 0x65), 0x412, n, (LPARAM)(LPSTR)sel);
    if (g_95bc == 0)
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
            if (g_95bc) {
                fn_09_955c(0x7e7, msg);
                fn_09_9580(0x7e8, msg);
                MessageBox(g_9532, msg, g_9690, MB_ICONEXCLAMATION);
            }
            g_958e--;
            ok = 0;
        }
        if (hDlg == g_9532 && g_920c == 0 && (flag || match) && g_95bc) {
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
    if (g_95bc == 0)
        PostMessage(hDlg, WM_COMMAND, 1, 0L);
}

/* @addr 16:4900 */
void far fn_16_4900(HWND hDlg)
{
    int i;
    int v;
    int n;
    WORD sel[100];
    int j;
    int k;
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
                    g_96f0[g_7092[g_952e].f_04c].f52, g_96a9);
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

/* @addr 16:5db0 */
void far fn_16_5db0(HWND hDlg)
{
    int i;
    int j;
    int n;
    char a[50];
    char b[50];
    char c[50];
    int m;

    n = (int)SendMessage(GetDlgItem(hDlg, 0x66), LB_GETCOUNT, 0, 0L);
    for (i = 0; i < n; i++) {
        SendMessage(GetDlgItem(hDlg, 0x66), LB_GETTEXT, i, (LPARAM)(LPSTR)a);
        for (j = 1; j < 27; j++) {
            fn_09_955c(j + 0xba, b);
            if (fn_16_5f0e(a, b)) {
                g_9564[j] = 1;
                m = (int)SendMessage(GetDlgItem(g_9532, 0x65), LB_GETCOUNT, 0, 0L);
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
/* @addr 16:64fa */
void far fn_16_64fa(void)
{
    char buf[110];
    DWORD org;
    int done;

    if (g_13dc == 0 && g_9530 == 2) {
        fn_18_0000();
        return;
    }
    if (g_90f4 == 6) {
        SelectClipRgn(g_13dc, g_9536);
        org = SetWindowOrg(g_13dc, -g_6e08.left, -g_6e08.top);
    }
    done = 0;
    switch (g_9530) {
    case 3:
        PatBlt(g_13dc, 0, 0, g_6da4->f02.x, g_6da4->f02.y, BLACKNESS);
        if (g_920c == 0)
            fn_09_955c(0x91a, buf);
        else
            fn_09_955c(0x7eb, buf);
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f02.x / 2, g_6da4->f02.y / 2 - 18, buf);
        if (g_920c == 0)
            fn_09_955c(0x91b, buf);
        else
            lstrcpy(buf, g_6da4->f08);
        lstrcat(buf, "...");
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f02.x / 2, g_6da4->f02.y / 2, buf);
        break;
    case 4:
        if (music_pause_state != -2)
            fn_10_7480(-2, 1);
        PatBlt(g_13dc, 0, 0, g_6da4->f02.x, g_6da4->f02.y, BLACKNESS);
        lstrcpy(buf, g_6da4->f08);
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f02.x / 2, g_6da4->f02.y / 2 - 18, buf);
        fn_09_955c(0x7ec, buf);
        fn_10_94c4(2, 6, 0xff00L, g_6da4->f02.x / 2, g_6da4->f02.y / 2, buf);
        g_6da4->f1c = 1;
        break;
    case 1:
    case 2:
    case 5:
    case 6:
        if (g_6da4 == NULL)
            break;
        if (g_959a == 0) {
            g_959a = 1;
            PatBlt(g_13dc, 0, 0, g_6da4->f02.x, g_6da4->f02.y, BLACKNESS);
            if (g_90f4 == 1) {
                fn_09_955c(0x7ed, buf);
                lstrcat(buf, "...");
                fn_10_94c4(0, 6, 0xff00L, g_6da4->f02.x / 2, g_6da4->f02.y / 2, buf);
            } else {
                lstrcpy(buf, g_6da4->f08);
                fn_10_94c4(2, 6, 0xff00L, g_6da4->f02.x / 2, g_6da4->f02.y / 2 - 18, buf);
                fn_09_955c(0x7ee, buf);
                lstrcat(buf, "...");
                fn_10_94c4(2, 6, 0xff00L, g_6da4->f02.x / 2, g_6da4->f02.y / 2, buf);
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
        SelectClipRgn(g_13dc, g_9538);
    }
}

/* Owner-draw list item [inferred]. */
/* @addr 16:590c */
void far pascal fn_16_590c(DRAWITEMSTRUCT far *dis)
{
    RECT rc;
    HBRUSH hbr;
    char text[80];
    HFONT old;
    int v;

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
/* @addr 16:3468 */
int far fn_16_3468(int idx, int j)
{
    int r;
    int n;
    int b2;
    int b1;
    char name[20];

    if (g_9563 == 0 && g_96f0[g_7092[idx].f_04c].f04[j] == -1
        && (j != 3 || g_3a38[idx] != 0))
        return 0;
    if (j == 0 && g_7092[idx].f_024[0] < 40)
        g_5078 = g_5078 * (g_7092[idx].f_024[0] + 200) / 300;
    r = 100 - g_7092[idx].f_024[j];
    if (g_92e4 == 0)
        g_7092[idx].f_024[j] = 100;
    g_7092[idx].f_0ea = 1;
    switch (j) {
    case 1:
        g_7092[idx].f_08a = 2;
        break;
    case 3:
        if (g_9563) {
            fn_14_3eda();
            if (idx == g_9646)
                GetPrivateProfileString(g_9690, "MainShip", "EAGLE", name, 20, g_96a9);
            else
                lstrcpy(name, g_96f0[g_7092[idx].f_04c].f52);
            for (n = 0; n < g_95aa; n++)
                if (lstrcmp(g_6e20[n].f0a, name) == 0)
                    break;
            fn_16_5f78(idx, n);
            fn_14_4074();
        } else {
            g_7092[idx].f_01e = g_1df8[g_9324][idx].f22 - 2;
            g_7092[idx].f_020 = 1;
            g_1df8[g_9324][idx].f44 = g_96f0[g_7092[idx].f_04c].f14;
            b1 = g_7092[idx].f_0aa;
            b2 = g_7092[idx].f_0ab;
            g_7092[idx].f_0aa = 0;
            fn_14_11a8(idx);
            g_1df8[g_9324][idx].f3a = g_3a38[idx];
            if (g_92e4) {
                g_7092[idx].f_0aa = b1;
                g_7092[idx].f_0ab = b2;
            }
            if (g_7092[idx].f_0d4 >= 0) {
                g_6e24[g_7092[idx].f_0d4].f72 = g_7092[idx].f_0aa;
                g_6e24[g_7092[idx].f_0d4].f73 = g_7092[idx].f_0ab;
            }
        }
        break;
    }
    g_7092[idx].f_022 = g_7092[idx].f_008;
    if (g_7092[idx].f_0aa)
        g_7092[idx].f_0de = 1;
    else if (g_96f0[g_7092[idx].f_04c].f0a == 3)
        g_7092[idx].f_0de = 0;
    if (g_7092[idx].f_0ab)
        g_7092[idx].f_0df = 1;
    else if (g_96f0[g_7092[idx].f_04c].f0a == 3)
        g_7092[idx].f_0df = 0;
    if (g_7092[idx].f_008 == 1 || (!g_7092[idx].f_0aa && !g_7092[idx].f_0ab
        && g_96f0[g_7092[idx].f_04c].f0a == 3)) {
        g_7092[idx].f_0de = 1;
        g_7092[idx].f_022 = 1;
    }
    fn_13_33d6(idx);
    return r / 10 * 10;
}

/* Picks what the computer buys for object idx [inferred]. */
/* @addr 16:3b18 */
void far fn_16_3b18(int idx, int flag)
{
    int i;
    int j;
    int r;
    int k;
    int found;
    long money;
    int cost;

    if (flag != 2) {
        g_953e = g_9540 = g_953f = g_9541 = g_9563 = 0;
        for (j = 1; j < 27; j++)
            g_9564[j] = g_9542[j] = 0;
        for (j = 0; j <= 5; j++)
            g_955d[j] = 0;
    }
    if (g_92e4 && idx == g_9646)
        return;
    if (g_9e5b == 0 && flag == 0) {
        g_9563 = 1;
        return;
    }
    if (idx == g_9646 && g_95bc)
        return;
    money = g_7092[idx].f_0da;
    if (g_7092[idx].f_024[0] < 60 || g_7092[idx].f_024[2] < 40) {
        g_953e = 1;
        for (i = 0; i < 3; i++) {
            g_9e55 += 100 - g_7092[idx].f_024[i];
            money -= 100 - g_7092[idx].f_024[i];
        }
    }
    if ((g_96f0[g_7092[idx].f_04c].f00 / 5 > g_7092[idx].f_01c && g_940e < 7)
        || g_96f0[g_7092[idx].f_04c].f00 / 12 > g_7092[idx].f_01c) {
        g_9540 = 1;
        g_9e55 += (g_96f0[g_7092[idx].f_04c].f00 - g_7092[idx].f_01c) / 70 * 10;
        money -= (g_96f0[g_7092[idx].f_04c].f00 - g_7092[idx].f_01c) / 70 * 10;
    }
    if (money > 100) {
        if (g_91f8 > 2 && g_7092[idx].f_008 < 2) {
            g_9541 = 1;
            g_9e55 += 250;
            money -= 250;
        }
        r = rand() % 3;
        if (r == 0 && money >= 700) {
            for (i = 0; i < 10; i++) {
                k = rand() % 20 + 1;
                found = 0;
                if (g_11aa || g_2f54[k].f36 == -1) {
                    for (j = 1; j < g_7092[idx].f_0c9; j++) {
                        if (g_7092[idx].f_0b6[j] == k) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found && g_2f54[k].f34 <= money) {
                        g_9542[k] = 1;
                        money -= g_2f54[k].f34;
                        g_9e55 += g_2f54[k].f34;
                    } else if (found && g_7092[idx].f_0ac[i] != -1 && g_7092[idx].f_0ac[i] < 20
                        && (20 - g_7092[idx].f_0ac[i]) * 10 <= money) {
                        g_9542[k] = 1;
                        money -= (20 - g_7092[idx].f_0ac[i]) * 10;
                        g_9e55 += (20 - g_7092[idx].f_0ac[i]) * 10;
                    }
                }
            }
        } else if (r == 1 && money >= 400 && g_7092[idx].f_0d4 >= 0) {
            for (i = 0; i < 3; i++) {
                k = rand() % 6;
                cost = (g_6e24[g_7092[idx].f_0d4].f32[k] + 2) * 100;
                if (k < 2)
                    cost += 200;
                if (cost <= money && g_6e24[g_7092[idx].f_0d4].f32[k] < 5
                    && (k < 5 || g_96f0[g_7092[idx].f_04c].f0a != -1)) {
                    g_955d[k]++;
                    money -= cost;
                    g_9e55 += cost;
                }
            }
        }
    }
    if (g_7092[idx].f_0da > 250 && g_96f0[g_7092[idx].f_04c].f0c != -1
        && (!g_7092[idx].f_0aa || !g_7092[idx].f_0ab)) {
        g_953f = 1;
        g_9e55 += 100 - g_7092[idx].f_024[4];
    }
}

/* Applies the shop's purchases to object idx [inferred]. */
/* @addr 16:3784 */
void far fn_16_3784(int idx, int flag)
{
    int i;
    int j;
    int k;
    int unused;
    long saved;
    int m;
    int unused2;

    if (flag == 0) {
        g_7092[idx].f_0da += g_7092[idx].f_0cc;
        g_7092[idx].f_0cc = 0;
    }
    if (idx != g_9646 || flag)
        fn_16_3b18(idx, flag);
    if (flag || idx == g_9646)
        saved = g_7092[idx].f_0da;
    if (g_9541)
        g_7092[idx].f_0da -= fn_16_3ece(idx);
    if (g_957f)
        g_7092[idx].f_0da -= fn_16_3f88(idx);
    for (i = 0; i <= 5; i++)
        if (g_955d[i])
            for (j = 0; j < g_955d[i]; j++)
                g_7092[idx].f_0da -= fn_16_4030(idx, i);
    if (g_953e || (flag && g_92e4 == 0))
        for (i = 0; i < 3; i++)
            g_7092[idx].f_0da -= fn_16_3468(idx, i);
    if (g_953f || flag) {
        if (idx == g_9646 || g_7092[idx].f_0da > 100 || flag)
            g_7092[idx].f_0da -= fn_16_3468(idx, 3);
    } else if (g_9563) {
        g_7092[idx].f_0aa = 0;
        for (i = 0; i < 4; i++)
            fn_16_3468(idx, i);
    }
    for (i = 1; i < 27; i++) {
        if (g_9564[i]) {
            for (j = 0; j < g_7092[idx].f_0c9; j++) {
                if (g_7092[idx].f_0b6[j] == i) {
                    g_7092[idx].f_0ac[j] = g_7092[idx].f_0b6[j] = 0;
                    for (k = j; k < 9; k++) {
                        g_7092[idx].f_0b6[k] = g_7092[idx].f_0b6[k + 1];
                        g_7092[idx].f_0ac[k] = g_7092[idx].f_0ac[k + 1];
                    }
                    g_7092[idx].f_0ac[9] = g_7092[idx].f_0b6[9] = 0;
                    g_7092[idx].f_0c9--;
                    break;
                }
            }
        } else if (g_9542[i]) {
            for (m = 0; m < g_7092[idx].f_0c9; m++) {
                if (g_7092[idx].f_0b6[m] == i) {
                    g_7092[idx].f_0da -= fn_16_3730(idx, m);
                    break;
                }
            }
            if (g_7092[idx].f_0c9 == m) {
                fn_12_6d64(idx, i);
                g_7092[idx].f_0da -= g_2f54[i].f34;
            }
        }
    }
    if (g_9540 || flag)
        g_7092[idx].f_0da -= fn_16_3e80(idx);
    if (flag || idx == g_9646)
        g_7092[idx].f_0da = saved;
    fn_13_33d6(idx);
    g_7092[idx].f_000 = 0;
    g_1df8[g_9324][idx].f26 = 0;
    if (g_90f4 == 1 && idx == g_9646) {
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
    *(long *)&g_9e5b = 1;
}

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

/* Dialog procedure [inferred]. */
/* @addr 16:4104 */
BOOL far pascal fn_16_4104(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    DRAWITEMSTRUCT far *dis;
    TEXTMETRIC tm;
    HDC hdc;
    HFONT old;
    MEASUREITEMSTRUCT far *mis;

    switch (msg) {
    case WM_INITDIALOG:
        fn_16_51d6(hDlg);
        break;
    case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT far *)lParam;
        if (dis->itemID == -1)
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
        mis = (MEASUREITEMSTRUCT far *)lParam;
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

/* @addr 16:0b4e */
int far fn_16_0b4e(int i)
{
    int k;
    int bk;
    int d;
    int b;
    int a;
    int best;
    long v;

    if (g_934e < 3)
        return 0;
    if (g_913a != 0 || g_913c != 0)
        return 0;
    if (g_92e8 != 0 && g_94b2 == 0)
        return 0;
    if (g_9320 == 6 || g_9320 == 7)
        return 0;
    v = g_7092[i].f_0cc + g_7092[i].f_0da;
    if (v < -350L && g_7092[i].f_0cc < 200)
        return 0;
    if (i != g_9646 && v < 200)
        return 0;
    if ((g_1e14->f2e != 0 && g_1e14->f18 == 0) || g_9e49 < 9)
        return 0;
    g_9e4b = 0x578;
    g_952e = i;
    g_9e49 = 0;
    if (g_1e14->f18 != 0) {
        g_1e14->f18 = 0;
        g_1e14->f2e = 0;
        best = 20000;
        for (k = 0; k < g_9318 * 2; k += 2) {
            d = fn_08_285a(&b, &a, g_1df8[g_9324][g_952e].f04, g_1e28[k].f04);
            if (d < best) {
                bk = k;
                best = d;
            }
        }
        g_1e14->f04.x = g_1e18[bk].f04.x + 480;
        g_1e14->f04.y = g_1e18[bk].f04.y - g_1e14->f20;
        g_1e14->f1a = 0;
        g_1e14->f00 = -1000;
        g_1e14->f02 = -1000;
        g_1e14->f08 = 100;
        g_1e14->f0a = 100;
        g_1e14->f0c = -20;
        g_1e14->f0e = -70;
        fn_07_2080(7, -1);
    }
    return 1;
}

/* @addr 16:1f78 */
void far fn_16_1f78(void)
{
    HDC hdc;
    HBITMAP old;
    int h;
    HPALETTE oldpal;

    g_3caa = g_3ca8 = 0;
    g_3cac = (g_90ea - g_3ce6) / 2 - 20;
    g_3cac = min(g_3cac, 260);
    g_3cae = 200;
    g_3d48 = g_90ea - g_3cac;
    g_3d4a = min(g_0010 * 2 / 5, g_0010 - 370);
    g_6dac = g_3cac;
    g_6db2 = g_6db6 = g_3d4a;
    if (g_90ea > 700)
        g_6db6 = g_6db2 = g_3d4a - 10;
    g_6dae = max(g_0010 / 2, 370);
    g_6db0 = min(g_90ea / 13 + g_90ea / 2 + 90, g_90ea - g_6dac);
    g_6db4 = max(g_90ea / 2 - g_90ea / 13 - g_6dac - 90, 0);
    g_3d48 = g_6db0;
    g_3d4a = g_6db2;
    fn_16_27ea();
    fn_16_2144();
    h = (g_1e30[g_9646].f22 << 3) >> g_959e;
    if (g_953c == 0)
        g_953c = CreateCompatibleBitmap(g_13dc, g_3ce6, h + 0x43);
    hdc = CreateCompatibleDC(g_13dc);
    if (g_920e)
        oldpal = SelectPalette(hdc, g_920e, 0);
    old = SelectObject(hdc, g_953c);
    PatBlt(hdc, 0, 0, g_3ce6, h + 0x43, BLACKNESS);
    BitBlt(hdc, 0, 5, g_3ce6, h + 0x3e, g_13dc, g_90ea / 2 - g_3ce6 / 2,
           g_0010 - h - 0x3e, SRCCOPY);
    SelectObject(hdc, old);
    if (oldpal)
        SelectPalette(hdc, oldpal, 0);
    DeleteDC(hdc);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_16_27ea(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_16_2144(void)
{
}

/* @addr 16:5f78 */
void far fn_16_5f78(int i, int v)
{
    int a;
    int b;
    int n;
    int k;
    int t;
    int q;
    BITMAP bm;

    fn_10_0552(i + 40, 1);
    k = g_7092[i].f_0d4;
    g_6e24[k].f00 = v;
    t = g_6e24[k].f00;
    n = g_7092[i].f_04c;
    fn_14_1b84(i, n, k, t);
    g_7092[i].f_01c = g_6e24[k].f1c * 40;
    g_7092[i].f_0aa = g_7092[i].f_0ab = 1;
    fn_14_11a8(i);
    a = g_6e24[k].f7a;
    g_96f0[n].f0c = a;
    b = g_6e24[k].f7b;
    if (g_9156 == 0 && (a & 1)) {
        a++;
        b = 4;
    }
    g_1df8[g_9324][i].f22 = (a << g_9156) >> 1;
    g_1df8[g_9324][i].f24 = (b << g_9156) >> 1;
    SelectObject(g_3a38[i], g_39c4[i]);
    GetObject(g_3b20[i], sizeof(BITMAP), &bm);
    SelectObject(g_3a38[i], g_3b20[i]);
    q = (bm.bmHeight - g_1df8[g_9324][i].f24) /
        (g_1df8[g_9324][i].f22 + g_1df8[g_9324][i].f24);
    g_1df8[g_9324][i].f20 = a << 3;
    g_7092[i].f_059 = q - 1;
    g_96f0[n - 1].f91 = g_96f0[n - 1].f8f = a / 2;
    if (g_96f0[n - 1].f93 < 0)
        g_96f0[n - 1].f93 = 4 - g_96f0[n - 1].f93 - a / 2;
    fn_10_5d3c(i);
    fn_10_1460(n);
    fn_10_1620(n);
    fn_10_1502(n);
    g_1df8[g_9324][i].f3a = g_3a38[i];
}

/* @addr 16:6928 */
void far fn_16_6928(int a)
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
        PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
        t = GetCurrentTime();
        g_0928 = 0;
        fn_15_1328(0);
        do
            fn_10_740c();
        while (GetCurrentTime() - t < 2000);
        fn_10_6e76(8, 0);
        fn_10_6dd4(0);
        if (g_95bc)
            fn_09_6cc4(1);
        else {
            g_90f4 = 1;
            g_93a4 = 0;
        }
        break;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_16_6afe(void)
{
}

/* WM_INITDIALOG handler of dialog 16:4104 [inferred]. */
/* @addr 16:51d6 */
void far fn_16_51d6(HWND hDlg)
{
    int unused0;
    char buf[120];
    int unused1;
    int w;
    int h;
    int unused2;
    int unused3;
    int y;
    int unused4;
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
    g_9e57 = g_7092[g_952e].f_0da;
    g_9e55 = 0;
    fn_16_5820(hDlg);
    fn_06_0f54(g_7092[g_952e].f_0da, 100, 2, buf);
    lstrcat(buf, " ");
    fn_09_9580(0x30e3, buf);
    SetWindowText(GetDlgItem(hDlg, 0x6e), buf);
    fn_16_4bd8(hDlg);
    fn_16_43f2(hDlg);
    SetFocus(GetDlgItem(hDlg, 0x65));
    if (g_95bc == 0 || g_9e5b == 0)
        PostMessage(hDlg, WM_COMMAND, 0x69, 0L);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_16_4bd8(HWND hDlg)
{
}

/* WM_INITDIALOG handler of dialog 16:42a2 [inferred]. */
/* @addr 16:541c */
void far fn_16_541c(HWND hDlg)
{
    HWND hList;
    char buf[120];
    int i;
    int w;
    int h;
    int v;
    int unused1;
    int y;
    int unused2;
    RECT rc;
    int k;
    int price;
    int q;
    int owned;
    int found;

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
    fn_06_0f54(g_7092[g_952e].f_0da, 100, 2, buf);
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
            if (g_7092[g_9646].f_0b6[k] == i) {
                found = 1;
                if (g_2f54[i].f0a != 0)
                    owned = 1;
                break;
            }
        }
        if (found && (price = g_2f54[i].f34) != 0) {
            if (owned) {
                q = g_7092[g_9646].f_0ac[k];
                price = price * q / 20;
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
/* @addr 16:5b24 */
void far fn_16_5b24(HWND hDlg)
{
    int i;
    int j;
    int n;
    char buf1[50];
    char buf2[50];
    char buf3[50];
    DWORD t;

    if (g_95bc == 0) {
        t = GetCurrentTime();
        while (GetCurrentTime() - t < 1500)
            ;
    }
    g_9563 = g_9541 = g_957f = g_953e = g_9540 = g_953f = 0;
    for (j = 1; j < 27; j++)
        g_9542[j] = 0;
    for (j = 0; j <= 5; j++)
        g_955d[j] = 0;
    n = (int)SendMessage(GetDlgItem(hDlg, 0x66), 0x40c, 0, 0L);
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

/* @addr 16:08e4 */
void far self_destruct_ship(int unused, int i)
{
    int k;
    int j;
    int dy;
    int dx;

    if (g_7092[i].f_145 == 1 && g_9130 == 0)
        return;
    for (k = 0; k < 8; k++) {
        for (j = 0; j < 45; j++) {
            if (g_1e90[j].f00 == -1) {
                if (k == 0)
                    g_1e90[j].f0a = 5;
                else
                    g_1e90[j].f0a = 1;
                g_1e90[j].f00 = 1;
                g_1e90[j].f10 = g_1e50 + k * 20;
                g_1e90[j].f02 = 10;
                g_1e90[j].f06 = g_9324;
                g_1e90[j].f08 = i;
                if (k == 0) {
                    dy = 16;
                    dx = 16;
                } else {
                    dx = rand() % 60 - 12;
                    dy = rand() % 60 - 12;
                }
                g_5170[j].x = g_1df8[g_9324][i].f00 + dx;
                g_5170[j].y = g_1df8[g_9324][i].f02 + dy;
                g_5224[j].x = g_1df8[g_9324][i].f04.x + 128;
                g_5224[j].y = g_1df8[g_9324][i].f04.y + 128;
                g_9430++;
                break;
            }
        }
    }
    g_7092[i].f_0e0 = 1;
    g_1df8[g_9324][i].f26 = 1;
    g_7092[i].f_082 = g_1e50 + 6000;
    fn_13_4710(i);
    g_7092[i].f_0ea = 0;
    if (g_9320 == 7) {
        dx = 1;
        for (k = 0; k <= g_9316; k++) {
            if (k != g_9646 && g_7092[k].f_0ea != 0 && g_1e30[k].f18 == 0)
                dx = 0;
        }
        if (i == g_9646)
            dx = 1;
        if (dx)
            g_668a = -1;
    }
    fn_10_754a(0x45, g_9324, i, 1);
    if (i == g_9646) {
        if (g_95bc) {
            g_1e84 = g_1e50 + 8000;
        } else {
            g_1e84 = 0;
            g_1e80 = g_1e50 + 8000;
            g_95a8 = 1;
        }
        g_5078 = g_95bc == 0 ? g_5078 / 2 : g_5078 * 4 / 5;
        if (g_95bc == 0 && g_951a == 0)
            fn_11_aece();
    }
    if (g_9130 == 0)
        fn_13_498e(i, 1);
}

/* Types the ambulance line (DS:6db8) into the demon host window [inferred]. */
/* @addr 16:2e3c */
void far fn_16_2e3c(int a, int b)
{
    HFONT oldfont;
    HFONT hfont;
    DWORD oldtext;
    DWORD oldbk;
    DWORD ext;
    int i;
    int n;
    int h;
    RECT rc;
    RECT rc2;
    char word[80];
    int wrap;
    int margin;
    int j;
    int len;
    int w;

    if (g_90ea < 700)
        h = 12;
    else if (g_90ea < 860)
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
    SelectClipRgn(g_13dc, g_9534);
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
            if (rc.right - margin < w)
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
