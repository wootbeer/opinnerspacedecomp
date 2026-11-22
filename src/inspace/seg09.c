/* INSPACE.EXE segment 9 (selector 1040). */
#include <stdlib.h>
#include "inspace.h"

/* Records reached through far pointers or DGROUP arrays; only the fields
 * this file uses are named (offset in the name). */
typedef struct {                /* 0x70 bytes, far array at DS:1df8 / 1e18 */
    char p00[0x12];
    int f12;                    /* +12 */
    char p14[0x18 - 0x14];
    int f18;
    char p1a[0x1e - 0x1a];
    int f1e;
    char p20[0x24 - 0x20];
    int f24;                    /* +24 */
    char p26[0x2e - 0x26];
    char f2e;                   /* +2e */
    char f2f;
    char p30[0x32 - 0x30];
    int f32;                    /* +32 */
    char p34[0x36 - 0x34];
    int f36;                    /* +36 */
    char p38[0x51 - 0x38];
    char f51;
    char p52[0x70 - 0x52];
} REC_70;

#pragma pack(1)
typedef struct {                /* 0x297 bytes, far array at DS:69f4 */
    char p000[0x14e];
    int f14e;                   /* +14e */
    int f150;                   /* +150 */
    char p152[0x1c8 - 0x152];
    char f1c8[8];               /* +1c8 */
    char f1d0;                  /* +1d0 */
    char f1d1;                  /* +1d1 */
    int f1d2[8];                /* +1d2 */
    unsigned char f1e2[0x297 - 0x1e2];
} REC_297;
#pragma pack()

typedef struct {                /* 0x15a bytes, DGROUP array at DS:7090 */
    char p000[0x1e];
    int f1e;                    /* +1e */
    char p020[0x32 - 0x20];
    int f32;                    /* +32 */
    char p034[0x4e - 0x34];
    int f4e;                    /* +4e */
    char p050[0x56 - 0x50];
    int f56;                    /* +56 */
    char p058[0x5e - 0x58];
    char f5e;                   /* +5e */
    char p05f[0xce - 0x5f];
    int fce;                    /* +ce */
    int fd0;                    /* +d0 */
    int fd2;                    /* +d2 */
    char p0d4[0xec - 0xd4];
    char fec;                   /* +ec */
    char p0ed;
    char fee[0x146 - 0xee];     /* +ee, indexed by object [inferred] */
    char p146[0x15a - 0x146];
} REC_15A;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    char p02[0x1a - 0x02];
    int f1a;                    /* +1a */
    char p1c[0x30 - 0x1c];
    int f30;                    /* +30 */
    char p32[0xad - 0x32];
} REC_AD;

typedef struct {                /* 0x23 bytes, DGROUP array at DS:57a8 */
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p04[2];
    int f06;                    /* +06 */
    char p08[2];
    char f0a;                   /* +0a */
    char f0b;                   /* +0b */
    char f0c[13];               /* +0c: name [inferred] */
    int f19;                    /* +19 */
    char p1b[0x23 - 0x1b];
} REC_23;
#pragma pack()

extern int g_0010;
extern int g_13de;
extern long g_1e70;
extern long g_1e50;
extern long g_1e78;
extern long g_1e88;
extern long g_1e74;
extern int g_5000;
extern int g_5002;
extern int g_90ea;
extern RECT g_607c;
extern RECT g_6084;
extern char g_38c8[];
extern int g_8f70;
extern int g_90f8;
extern int g_91fe;
extern int g_93aa;
extern int g_9134;
extern void far *g_3d4c;
extern REC_70 far *g_1df8[16];
extern int g_3a02;
extern char g_3966[];
extern HGDIOBJ g_4e94[32];
extern REC_23 g_57a8[];
extern void far *g_4fcc;
extern long g_5078;
extern LPSTR g_6078;
extern REC_297 far *g_69f4;
extern REC_15A g_7090[];
extern long g_09bc[12];
extern int g_9200;
extern int g_9206;
extern int g_92e6;
extern int g_9316;
extern int g_9318;
extern int g_9322;
extern int g_91f8;
extern long g_1e58;
extern int g_929c;
extern HGLOBAL g_92e0;
extern int g_92e4;
extern int g_92ec[15];
extern int g_9320;
extern int g_9330;
extern int g_9332;
extern int g_9346;
extern int g_93a4;
extern int g_93b2;
extern int g_94c4;
extern int g_9334;
extern int g_9406;
extern int g_9408;
extern int g_94b0;
extern int g_94a2;
extern int g_9518;
extern int g_9646;
extern int flow_interactive;        /* DS:95bc */
extern int g_90f4;
extern HGLOBAL g_93a8;
extern HGDIOBJ g_93ae;
extern HGLOBAL g_93b4;
extern REC_AD g_96f0[];

/* Records only seen being reset by fn_09_6624; first fields only. */
typedef struct { int f00; char p02[0x08 - 0x02]; int f08; char p0a[0x1c - 0x0a]; } REC_1C;  /* DS:66e4 */
typedef struct { int f00; int f02; int f04; char p06[0x20 - 0x06]; } REC_20;  /* DS:65cc */
typedef struct { int f00; char p02[0x5a - 0x02]; } REC_5A;     /* DS:226c */
typedef struct { int f00; int f02; char p04[0x94 - 0x04]; } REC_94;  /* DS:610c */
typedef struct { int f00; char p02[0x14 - 0x02]; } REC_14;     /* DS:1e90, 58cc, 5a4c */
typedef struct { int f00; int f02; char p04[0x08 - 0x04]; int f08; char p0a[0x16 - 0x0a]; } REC_16;  /* DS:5b2c */
extern int g_93b0;
extern HWND g_934c;
extern int g_8f64;
extern long g_1e68;
extern long g_5014;
extern int g_9510;
extern int g_92f8;
extern REC_1C g_66e4[];
extern int g_9300;
extern REC_20 g_65cc[];
extern REC_5A g_226c[];
extern int g_9456;
extern int g_9430;
extern REC_94 g_610c[];
extern REC_14 g_1e90[];
extern REC_14 g_58cc[];
extern REC_14 g_5a4c[];
extern int g_9328;
extern REC_16 g_5b2c[];
extern int g_9e49;
extern int g_9494;
extern int g_9492;
extern int g_940c;
extern int g_9418;
extern int g_9600;
extern int g_940e;
extern int g_9e5b;
extern int g_9e4b;
extern int g_9e45;
extern int g_9414;
extern int g_9140;
extern long g_1e6c;
extern long g_6da8;
extern long g_8e2c;
extern int g_9378;
extern int g_103a;
void far fn_10_0864(int n);
void far fn_10_0a26(int n);
void far fn_09_0df6(int n);
void far fn_09_10d4(void);
int far fn_14_3eda(void);
void far fn_14_0000(int a);
void far fn_14_4074(void);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_11_ae94(void);
void far fn_11_2f8c(void);
BOOL far pascal fn_09_90fe(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void far fn_10_6d52(int a, int b, int c, int d, int e, int f);
void far fn_17_306e(void);
void far fn_11_1774(int c, int l, int t, int r, int b);
void far fn_17_30b0(int a, int b, int c);
int far fn_17_2c5a(int a, int b);
void far fn_17_0000(int a, int b);
void far fn_03_1542(int a, int b, int n, LPSTR buf, int c);
void far fn_07_2512(int i, int v);
void far fn_09_6a12(void);
void far fn_09_0000(int a);
void far fn_10_022e(int a);
void far fn_11_02f0(void);
void far fn_13_65f2(int a);
void far fn_06_7266(void);
void far fn_07_49b6(void);
void far fn_07_5ae8(int j, int a);
void far fn_09_1092(void);
void far fn_09_2828(void);
void far fn_10_7480(int a, int b);
void far fn_10_7db8(void);
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
void far fn_10_a332(LPSTR buf, int id, int n, ...);
void far fn_12_26a4(int i, int j);
void far fn_16_6928(int a);

int far fn_09_094c(void);
void far fn_09_0352(HDC hdc, int x, int flags, int w, int h, LPSTR name);
void far fn_09_09b0(int slot);
int far fn_09_955c(UINT id, LPSTR buf);
void far fn_09_95ba(UINT id);
void far fn_09_6cc4(int flag);
void far fn_09_6db0(void);
void far fn_09_6dec(int a);
void far fn_09_8bec(HDC hdc, int x, int y, int size, int width, UINT align, LPSTR s);

/* @addr 9:699e */
void far fn_09_699e(void)
{
    if (g_93b4) {
        if (g_4fcc) {
            GlobalUnlock(g_93b4);
            g_4fcc = 0;
        }
        FreeResource(g_93b4);
        g_93b4 = 0;
    } else if (g_93a8) {
        if (g_4fcc) {
            GlobalUnlock(g_93a8);
            g_4fcc = 0;
        }
        GlobalFree(g_93a8);
        g_93a8 = 0;
    }
}

/* @addr 9:6a12 */
void far fn_09_6a12(void)
{
    char buf[80];
    char buf2[60];

    if (flow_interactive == 0)
        return;
    fn_09_955c(0x145, buf);
    fn_10_94c4(0, 6, 0x020080ffL, g_90ea / 2, g_0010 / 2 - 175, buf);
    fn_10_a332(buf, 0x9e4, 1, g_91f8);
    fn_10_94c4(0, 0, 0x8000L, g_90ea / 2 - 240, g_0010 / 2 - 115, buf);
    fn_10_a332(buf, 0x9e5, 1);
    fn_10_94c4(0, 0, 0x8000L, g_90ea / 2 - 240, g_0010 / 2 - 85, buf);
    fn_10_a332(buf, 0x9e6, 1, g_7090[g_9646].fd2);
    fn_10_94c4(0, 2, 0x8000L, g_90ea / 2 + 124, g_0010 / 2 - 85, buf);
    fn_10_a332(buf, 0x9e7, 1, g_7090[g_9646].fd0);
    fn_10_94c4(0, 2, 0x8000L, g_90ea / 2 + 124, g_0010 / 2 - 55, buf);
    fn_10_a332(buf, 0x9e8, 1, g_1e58);
    fn_10_94c4(0, 6, 0xffL, g_90ea / 2, g_0010 / 2 + 65, buf);
}

/* @addr 9:6bc2 */
void far fn_09_6bc2(void)
{
    int i;
    int j;
    int unused;

    fn_10_7480(-1, 1);
    g_1e74 = 0;
    if (g_9320 == 6) {
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].f32 == 0 && i != g_9646) {
                for (j = 0; j < g_9406; j++) {
                    if (g_1df8[0][j].f18 == 0) {
                        g_7090[i].fce += g_1df8[0][j].f1e * -90 / 210 + 100;
                        g_7090[i].fd2++;
                        fn_07_5ae8(j, 1);
                    }
                }
            }
        }
    }
    if (g_93a4) {
        g_90f4 = 8;
        g_929c = 0;
        fn_16_6928(0);
        g_9346 = -1;
        for (i = 0; i <= g_9316; i++) {
            if (g_96f0[g_7090[i].f4e].f1a == 7 && g_7090[i].f5e == 0
                && g_7090[i].f56 == g_9646)
                g_7090[i].fec = 0;
        }
    } else
        fn_09_6cc4(0);
}

/* @addr 9:6cc4 */
void far fn_09_6cc4(int flag)
{
    int i;
    int j;

    fn_10_7db8();
    fn_13_65f2(1);
    g_1e74 = 0;
    g_90f4 = 2;
    g_92e4 = 0;
    if (g_9320 == 6)
        fn_09_6db0();
    if (g_92e0) {
        GlobalUnlock(g_92e0);
        g_3d4c = 0;
        GlobalFree(g_92e0);
        g_92e0 = 0;
    }
    fn_09_1092();
    for (i = 0; i <= 14; i++)
        for (j = 0; j < g_92ec[i]; j++)
            fn_12_26a4(i, j);
    fn_11_02f0();
    fn_07_49b6();
    PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
    g_93b2 = g_9332;
    fn_09_2828();
    fn_06_7266();
    g_94c4 = 1;
    g_9330 = 0;
    if (flag)
        fn_09_6dec(1);
}

/* @addr 9:6db0 */
void far fn_09_6db0(void)
{
    int i;

    for (i = 0; i <= g_9316; i++)
        g_7090[i].f1e = g_96f0[g_7090[i].f4e].f00;
}

/* @addr 9:6dec */
void far fn_09_6dec(int force)
{
    char buf[140];
    char unused[40];
    int r;
    int left;
    int right;
    int clip;

    clip = 0;
    if (flow_interactive == 0 || g_1e70 == g_1e50)
        return;
    if (force || g_6078 == 0) {
        SetRect(&g_6084, g_90ea / 2 - 290, g_0010 / 2 - 173, g_90ea / 2 + 290, g_0010 / 2 + 173);
        left = max(g_6084.left - 6, 0);
        right = min(g_6084.right + 6, g_90ea);
        fn_11_1774(2, g_6084.left - 6, g_6084.top - 15, g_6084.right + 6, g_6084.bottom + 6);
        fn_11_1774(-1, left, g_6084.top - 15, right, g_6084.top + 10);
        fn_10_a332(buf, 0xbbb, 1, g_91f8);
        fn_09_8bec(g_13dc, left + 5, g_6084.top - 13, 22, 10, 0, buf);
        fn_09_955c(0x8be, buf);
        fn_09_8bec(g_13dc, right - 7, g_6084.top - 6, 14, 0, 2, buf);
        g_5000 = g_6084.left + 14;
        g_5002 = g_6084.top + 18;
        if (g_93ae) {
            DeleteObject(g_93ae);
            g_93ae = 0;
        }
        g_93ae = CreateRectRgn(g_6084.left, g_5002, g_6084.right, g_6084.bottom);
        clip = 1;
        SelectClipRgn(g_13dc, g_93ae);
        if (g_6078 == 0)
            fn_17_30b0(11, 0xdac, 0);
        else
            fn_17_2c5a(1, 1);
    }
    if (clip == 0)
        SelectClipRgn(g_13dc, g_93ae);
    if (g_6078)
        r = fn_17_2c5a(0, 0);
    if (g_9134 && r == 1)
        g_1e74 = g_1e50 + 3000;
}


/* @addr 9:8838 */
void far fn_09_8838(int n)
{
    int v;
    char buf[50];

    v = g_96f0[g_7090[g_9646].f4e].f1a;
    if (g_7090[n].fec) {
        fn_03_1542(0, 14, n, buf, 1);
        lstrcat(g_6078, buf);
        if (g_7090[n].fee[g_9646] <= 5)
            fn_09_95ba(0x372);
        else
            fn_09_95ba(0x371);
        lstrcat(g_6078, ". ");
    }
}

/* @addr 9:88ba */
int far fn_09_88ba(int x)
{
    if (x >= 0)
        return x;
    return -x;
}

/* @addr 9:88dc */
long far abs32(long x)
{
    if (x >= 0)
        return x;
    return -x;
}

/* @addr 9:8908 */
void far fn_09_8908(void)
{
    fn_17_306e();
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
}

/* @addr 9:8934 */
void far draw_briefing_panel_with_esc_prompt(int a)
{
    char buf[120];
    char unused[82];
    int left;
    int right;
    int y;
    int x;
    int h;
    int w;
    int unused2;

    if (g_90ea < 640)
        w = g_90ea + 20;
    else
        w = min(g_90ea - 20, 620);
    if (g_0010 < 440)
        h = g_0010 + 20;
    else
        h = min(g_0010 - 20, 460);
    g_6084.left = g_90ea / 2 - w / 2;
    g_6084.right = g_6084.left + w;
    g_6084.top = g_0010 / 2 - h / 2;
    g_6084.bottom = g_6084.top + h - 180;
    if (g_0010 > 400)
        g_6084.top = max(g_6084.top, 15);
    g_607c.left = g_90ea / 2 - w / 2;
    g_607c.right = g_607c.left + w;
    g_607c.top = g_6084.bottom;
    g_607c.bottom = g_607c.top + 180;
    left = max(g_6084.left, 0);
    right = min(g_6084.right, g_90ea);
    if (g_8f70 == 0 && g_90f8 == 0) {
        fn_11_1774(2, g_6084.left, g_6084.top - 15, g_6084.right, g_607c.bottom);
        fn_11_1774(-1, left, g_6084.top - 15, right, g_6084.top + 10);
        fn_11_1774(-1, left, g_607c.top + 20, right, g_607c.top + 40);
        fn_10_a332(buf, 0x9e9, 1, g_91f8);
        fn_09_8bec(g_13dc, left + 5, g_6084.top - 13, 22, 10, 0, buf);
        fn_09_955c(0x8dc, buf);
        fn_09_8bec(g_13dc, right - 7, g_6084.top - 6, 14, 0, 2, buf);
        x = g_607c.left + 15;
        y = g_607c.top + 22;
        lstrcpy(buf, g_38c8);
        fn_09_8bec(g_13dc, left + 5, y, 15, 8, 0, buf);
        if (g_91fe) {
            fn_10_a332(buf, 0x90c, 1, g_91fe, 0x9d3);
            fn_09_8bec(g_13dc, right - 5, y, 15, 8, 2, buf);
        }
    }
    g_6084.left += 6;
    g_6084.right -= 6;
    g_6084.top += 11;
    g_6084.bottom = g_607c.top + 9;
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
    g_93ae = CreateRectRgn(g_6084.left, g_6084.top, g_6084.right, g_6084.bottom);
    g_93aa = 0;
    fn_17_0000(a == 0, 1);
}

/* @addr 9:8bec */
void far fn_09_8bec(HDC hdc, int x, int y, int size, int width, UINT align, LPSTR s)
{
    HFONT old;
    HFONT font;
    char buf[80];
    COLORREF text;
    COLORREF bk;
    int shadow;

    shadow = 1;
    if (size == 13) {
        size = 14;
        shadow = 0;
    }
    if (size < 14)
        shadow = 0;
    old = SelectObject(hdc, font = CreateFont(size, width, 0, 0, 600, 0, 0, 0, 0, 0, 0,
                                              2, 0x22, "Arial"));
    bk = SetBkColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);
    SetTextAlign(hdc, align);
    if (shadow) {
        text = SetTextColor(hdc, 0x02ffffffL);
        TextOut(hdc, x + 2, y + 2, s, lstrlen(s));
    }
    text = SetTextColor(hdc, 0x025a5a5aL);
    TextOut(hdc, x, y, s, lstrlen(s));
    SetBkColor(hdc, bk);
    SetTextColor(hdc, text);
    SelectObject(hdc, old);
    if (font)
        DeleteObject(font);
}

/* @addr 9:90fe */
BOOL far pascal fn_09_90fe(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    RECT r;
    int w;
    int h;
    char buf[80];

    switch (msg) {
    case WM_INITDIALOG:
        GetWindowRect(hDlg, &r);
        w = r.right - r.left;
        h = r.bottom - r.top;
        if (g_9518) {
            fn_09_955c(0x8dd, buf);
            SetWindowText(GetDlgItem(hDlg, 0x72), buf);
        }
        MoveWindow(hDlg, GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2,
                   GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2, w, h, TRUE);
        break;
    }
    return FALSE;
}

/* @addr 9:94ba */
void far fn_09_94ba(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (g_69f4[g_94a2].f1c8[i])
            fn_07_2512(i, g_69f4[g_94a2].f1c8[i] - 1);
        if (g_69f4[g_94a2].f1c8[i] == 2)
            g_1df8[0][i].f2f = (char)0x9c;
        if (g_9320 == 2 && (g_9334 == 0 || rand() % 3 == 0))
            fn_07_2512(i, 0);
    }
}

/* @addr 9:955c */
int far fn_09_955c(UINT id, LPSTR buf)
{
    return LoadString(g_9212, id, buf, 160);
}

/* @addr 9:9580 */
void far fn_09_9580(UINT id, LPSTR dst)
{
    char buf[200];

    LoadString(g_9212, id, buf, 199);
    lstrcat(dst, buf);
}

/* @addr 9:95ba */
void far fn_09_95ba(UINT id)
{
    char buf[200];

    LoadString(g_9212, id, buf, 199);
    lstrcat(g_6078, buf);
}

/* @addr 9:95f4 */
void far fn_09_95f4(UINT id)
{
    char buf[100];

    LoadString(g_9212, id, ambulance_line, 90);
}

/* @addr 9:961a */
void far fn_09_961a(UINT id)
{
    char buf[100];

    LoadString(g_9212, id, buf, 90);
    lstrcat(ambulance_line, buf);
}

/* Resets the race/session state and builds the level objects [inferred]. */
/* @addr 9:6624 */
void far fn_09_6624(void)
{
    int i;
    int j;
    char unused[40];

    if (g_93b0)
        return;
    g_93b0 = 1;
    if (g_934c) {
        g_8f64 = 0;
        DestroyWindow(g_934c);
        g_934c = 0;
    }
    if (g_90f4 != 3 && g_934c == 0)
        g_934c = CreateDialog(g_9212, MAKEINTRESOURCE(0x65), (HWND)g_0016, fn_09_90fe);
    g_5014 = g_1e68 = 0;
    g_9510 = 0x65;
    for (i = 0; i < g_92f8; i++) {
        g_66e4[i].f08 = 0x191;
        g_1df8[6][i].f18 = 1;
    }
    for (i = 0; i < g_9300; i++) {
        g_1df8[10][i].f18 = 1;
        g_65cc[i].f04 = g_65cc[i].f00 = -1;
    }
    for (i = 0; i < 4; i++)
        g_226c[i].f00 = -1;
    g_9430 = g_9456 = 0;
    for (i = 0; i < 9; i++) {
        g_610c[i].f02 = -1;
        g_610c[i].f00 = 50;
    }
    for (i = 0; i < 45; i++)
        g_1e90[i].f00 = -1;
    for (i = 0; i < 20; i++)
        g_58cc[i].f00 = -1;
    for (i = 0; i < g_92f8; i++)
        g_66e4[i].f00 = -1;
    for (i = 0; i < g_92ec[g_9328]; i++) {
        g_5a4c[i].f00 = -1;
        g_1df8[g_9328][i].f18 = 1;
    }
    for (i = 0; i < 10; i++)
        for (j = 0; j < 4; j++) {
            g_5b2c[i * 4 + j].f08 = 0;
            g_5b2c[i * 4 + j].f02 = -100;
            g_5b2c[i * 4 + j].f00 = -100;
        }
    g_9e49 = 10;
    g_9492 = g_9494 = 1;
    for (i = 0; i < g_940c; i++)
        fn_10_0864(i);
    for (i = 0; i < g_9418; i++)
        fn_10_0a26(i);
    g_9600 = 1;
    for (i = 0; i < g_940e; i++)
        fn_09_0df6(i);
    fn_09_10d4();
    g_1e50 = GetCurrentTime();
    g_9e45 = g_9e4b = g_9e5b = 0;
    g_9e49 = 10;
    g_1df8[7][0].f18 = 1;
    g_9414 = 0;
    fn_14_3eda();
    fn_14_0000(-1);
    fn_14_4074();
    g_9140 = 1;
    for (i = 0; i <= 14; i++)
        for (j = 0; j < g_92ec[i]; j++) {
            g_1df8[i][j].f12 = g_1df8[i][j].f24;
            g_1df8[i][j].f2e = 0;
            g_1df8[i][j].f32 = -1;
            g_1df8[i][j].f36 = -1;
        }
    if (g_9320 == 6) {
        fn_09_6db0();
        fn_10_754a(0x4f, 0, 0, 5);
        fn_10_754a(0x28, 0, 0, 5);
        fn_10_754a(0x42, 0, 0, 5);
    }
    g_1e6c = g_1e50 + 10000;
    g_6da8 = 0;
    if (g_91f8 == 1 || g_92e4 != 0) {
        fn_11_ae94();
        fn_11_2f8c();
    }
    g_8e2c = 0;
    if (g_934c) {
        g_8f64 = 0;
        DestroyWindow(g_934c);
        g_934c = 0;
    }
    g_9378 = g_9134;
    g_103a = g_92e4 = 0;
}
