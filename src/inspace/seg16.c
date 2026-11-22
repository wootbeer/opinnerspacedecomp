/* INSPACE.EXE segment 16 (selector 1078). */
#include "inspace.h"

/* 0x15a-byte object records, DGROUP array at DS:7092 (base = lowest
 * offset accessed with an index * 0x15a; same layout as seg13.c). */
typedef struct {
    char pad_000[0x8];
    int f_008;    /* DS:709a */
    int f_00a;    /* DS:709c */
    char pad_00c[0x6];
    int f_012;    /* DS:70a4 */
    char pad_014[0x8];
    int f_01c;    /* DS:70ae */
    char pad_01e[0x4];
    int f_022;    /* DS:70b4 */
    char pad_024[0x28];
    int f_04c;    /* DS:70de */
    char pad_04e[0xe];
    char f_05c;    /* DS:70ee */
    char pad_05d[0x4d];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    signed char f_0ac[10];    /* DS:713e */
    signed char f_0b6[10];    /* DS:7148 */
    char pad_0c0[0x9];
    signed char f_0c9;    /* DS:715b */
    char pad_0ca[0xa];
    int f_0d4;    /* DS:7166 */
    char pad_0d6[0x8];
    char f_0de;    /* DS:7170 */
    char f_0df;    /* DS:7171 */
    char pad_0e0[0xa];
    char f_0ea;    /* DS:717c */
    char pad_0eb[0x6f];
} OBJ15A;

typedef struct {                /* 0x70-byte records */
    char p00[0x04];
    POINT f04;
    char p08[0x18 - 0x08];
    int f18;
    char p1a[0x2e - 0x1a];
    signed char f2e;
    char p2f[0x44 - 0x2f];
    int f44;
    char p46[0x70 - 0x46];
} REC_70;

typedef struct {                /* far pointer at DS:6da4 [inferred: input event] */
    char p00[0x22];
    int f22;
    int f24;
    long f26;
} REC_6DA4;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    int f02;
    char p04[0x0a - 0x04];
    int f0a;
    char p0c[0xad - 0x0c];
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
extern int g_9406[];
typedef struct {                /* 0x7c-byte records, far pointer at DS:6e24 */
    char p00[0x32];
    signed char f32[0x7c - 0x32];
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

void far fn_03_06ec(int a, int b, int c, int d);
void far fn_07_13b2(int a, int b, int c);
void far fn_12_2556(int a, int b);
void far fn_12_26a4(int a, int b);
void far fn_11_2f8c(void);
void far fn_12_6d64(int a, int b);
void far fn_06_1010(int v, int div, int width, LPSTR buf);
void far fn_18_0378(int a);
void far fn_09_955c(int id, LPSTR buf);
void far fn_09_9580(int id, LPSTR buf);
void far fn_16_64fa(void);
void far fn_16_3784(int a, int b);
void far pascal fn_16_590c(DRAWITEMSTRUCT far *dis);
void far pascal fn_16_5ada(DRAWITEMSTRUCT far *dis);

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
int far fn_16_3f88(void)
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

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_16_64fa(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far pascal fn_16_590c(DRAWITEMSTRUCT far *dis)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_16_3784(int a, int b)
{
}
