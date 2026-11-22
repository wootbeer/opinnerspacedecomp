/* INSPACE.EXE segment 7 (selector 1030), first source file: 7:0000-7:2206
 * (files.tsv group 13). */
#include "inspace.h"
#include <stdlib.h>

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    int f00;
    int f02;
    POINT f04;                  /* +4 */
    char p08[0x0c - 0x08];
    int f0c;                    /* +c */
    int f0e;                    /* +e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    char p14[0x18 - 0x14];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    int f1c;                    /* +1c */
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    char p26[0x28 - 0x26];
    int f28;                    /* +28 */
    char p2a[0x2c - 0x2a];
    int f2c;                    /* +2c */
    char f2e;                   /* +2e */
    char p2f[0x3c - 0x2f];
    HDC f3c;                    /* +3c */
    char p3e[0x44 - 0x3e];
    int f44;                    /* +44 */
    char p46[0x51 - 0x46];
    char f51;                   /* +51 */
    char f52;
    char f53;                   /* +53 */
    char f54;                   /* +54 */
    char p55[0x66 - 0x55];
    void (far *f66)(int type, int idx);  /* +66 */
    char p6a[0x70 - 0x6a];
} REC_70;

#pragma pack(1)
typedef struct {                /* 0x297 bytes, far array at DS:69f4 */
    char p000[0x14e];
    int f14e;
    int f150;
    char p152[0x1c8 - 0x152];
    char f1c8[8];
    char f1d0;
    char p1d1;
    int f1d2[8];
    unsigned char f1e2[0x297 - 0x1e2];
} REC_297;

typedef struct {                /* 0x23 bytes, DGROUP array at DS:57a8 */
    int f00;
    char p02[0x06 - 0x02];
    int f06;
    char p08[0x0a - 0x08];
    char f0a;
    char f0b;
    char p0c[0x23 - 0x0c];
} REC_23;
#pragma pack()

typedef struct {                /* 0x15a bytes, DGROUP array at DS:7090 */
    char p00[0x10];
    int f10;                    /* +10 */
    char p12[0x32 - 0x12];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    char p36[0x38 - 0x36];
    int f38;                    /* +38 */
    char p3a[0x4e - 0x3a];
    int f4e;                    /* +4e */
    int f50;                    /* +50 */
    char p52[0x5e - 0x52];
    char f5e;                   /* +5e */
    char p5f[0x88 - 0x5f];
    DWORD f88;                  /* +88 */
    char p8c[0xd0 - 0x8c];
    int fd0;                    /* +d0 */
    char pd2[0xe4 - 0xd2];
    char fe4;                   /* +e4 */
    char pe5[0xe9 - 0xe5];
    char fe9;                   /* +e9 */
    char fea;                   /* +ea */
    char feb;                   /* +eb */
    char fec;                   /* +ec */
    char ped[0x15a - 0xed];
} REC_15A;

typedef struct { int f0, f2, f4, f6; char rest[0x1e - 8]; } REC_1E;


extern REC_70 far *g_1df8[16];
extern REC_70 far *g_1e30;     /* = g_1df8[14] */
extern int g_3a02;
extern int g_3a28;
extern int g_952e;
extern int g_9646;
extern int g_90ea;
extern int g_90ec;
extern int g_0a76;
extern int g_9208;
extern int g_9134;
extern int g_058c;
extern RECT g_1d28;
extern char g_8630[];
typedef struct { char p00[0x2a]; int f2a; } REC_6DA4;   /* far pointer at DS:6da4 */
extern REC_6DA4 far *g_6da4;
extern int g_90f4;
extern int g_952c;
extern int g_9530;
extern int g_914a;
extern int g_92a2;
extern DWORD g_1e64;
extern DWORD g_1e50;
extern DWORD g_1e8c;
/* order g_0586, g_9004, g_914c and g_1e50 before g_1e8c: operand choice in 7:2206 */
extern int g_0586;
extern int g_9004;
extern int g_914c;
extern int g_0592;
extern int g_059a;
extern HGDIOBJ g_4e94[32];
extern int g_9408;
extern int g_9142;
extern int g_943a;
extern int g_943c;
extern int g_0b6e;
extern int g_9316;
extern int g_9432;
extern DWORD g_8e28;

extern int g_9156;
extern int g_9456;
extern int g_92ec[];
extern int g_9406[];

/* 20-byte records at DS:58bc (seg08 names the first three POINTs). */
typedef struct {
    POINT a, b, c;              /* +0, +4, +8 */
    int fc;                     /* +c */
    int fe;                     /* +e */
    int f10;                    /* +10, -1 = free [inferred] */
    int f12;
} REC_14;
extern REC_14 g_58bc[];
extern REC_297 far *g_69f4;
extern REC_23 g_57a8[];
extern REC_15A g_7090[];

/* 0x5a-byte records at DS:221c, 4 of them [inferred: active dissolves]. */
typedef struct {
    char b[80];
    int type;                   /* +50, -1 = free */
    int idx;                    /* +52 */
    int r;                      /* +54 */
    int sq;                     /* +56 */
    int f58;                    /* +58 */
} REC_5A;
extern REC_5A g_221c[4];
extern int dissolve_active_count;   /* DS:9148 */
extern int g_92a4;
extern REC_1E g_6e52[];
extern REC_1E g_6ea8[];
extern int g_94a2;
extern int g_91fc;
extern int g_91fe;
extern int g_9324;
extern int g_945c;
extern int g_945e;
extern HDC g_3a04[8];
extern HGDIOBJ g_3990[8];
extern HPALETTE g_3a78[8];
extern HGDIOBJ g_3aec[8];
extern int g_1de4;
extern int g_1de6;
extern HINSTANCE g_8e66;
extern HWND g_0a7c;

/* 20-byte records at DS:1e90 [inferred]. */
typedef struct {
    int f0;
    char p2[4];
    int f6;
    int f8;
    char pa[0x14 - 0x0a];
} REC_14B;
extern REC_14B g_1e90[];
extern int g_9434;
extern int g_951a;
extern int g_9e49;
extern int g_3a38;
extern RECT g_1e5c;
extern HDC g_39e8[];
extern int subgame_active;              /* DS:9130 */
extern int hazards_ship_redraw_pending; /* DS:058a */

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    char p00[0x1a];
    int f1a;                    /* +1a */
    char p1c[0x24 - 0x1c];
    int f24;                    /* +24 */
    char p26[0xad - 0x26];
} REC_AD;
#pragma pack()
extern REC_AD g_96f0[];
extern int g_9318;
extern int g_9140;
extern int g_9320;
extern int g_668a;
extern int g_094e;
extern int g_0950;
void far fn_08_0000(void);
void far fn_12_2556(int type, int idx);
void far command_watch_ship(int a, int b);   /* 13:563c */

void far pascal fn_08_1d54(int a, int b);
void far pascal fn_08_1b54(int a, int b);
void far fn_07_233c(int a, int b, int c);
void far fn_07_5a46(void);
void far fn_07_63f2(void);
void far pascal fn_07_3400(int n);
void far fn_07_2768(int n);
void far fn_07_5ae8(int a, int b);
void far fn_07_5b68(int a, int b, int c);
int far fn_07_64ac(HDC dc, int a, int b);
void far fn_07_65aa(int a, int b);
void far pascal fn_08_0b76(int a, int b, HDC dc, int c);
int far pascal fn_08_50aa(int a);
int far pascal fn_08_546c(int a, int far *b, int far *c, int d, int e);
void far fn_08_5df2(int a, int b, int c, int d, int e);
int far fn_02_094c(UINT id);
int far fn_10_6c02(int a, int b, int c);
int far fn_10_6308(int a, int b, int c, int d);   /* seg10 declares void */
int far fn_10_6ec6(int a);                         /* seg10 declares void */
void far fn_10_754a(int a, int b, int c, int d);
void far fn_08_99ce(int a, int b, int c, int d, int e);
void far fn_13_6450(int a, int b, int c);
void far fn_13_58dc(int a, int b);
void far fn_13_5a6a(HDC dc, int a, int b, int c, int d, int e, int f, int g);


/* @addr 7:119c */
void far fn_07_119c(int a)
{
    g_0a76 = a;
    if (g_0a7c)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
}

/* @addr 7:11cc */
void far fn_07_11cc(void)
{
    g_1e30[g_9646].f00 = g_90ea / 2;
    g_1e30[g_9646].f02 = g_90ec / 2;
}

/* Updates the player ship sprite frame [inferred]. */
/* @addr 7:1208 */
void far fn_07_1208(void)
{
    int u1;
    int u2;
    int v;
    int idx;
    int i;
    int w;
    int h;
    int mode;
    int u3;

    if (g_90f4 != 1 || g_1e30[g_9646].f18 != 0 || g_951a || subgame_active)
        return;
    if (g_9e49 >= 3 && g_9e49 <= 6 && g_9646 == g_952e)
        return;
    if (!g_3a38)
        return;
    if (!g_7090[g_9646].fec)
        for (i = 0; i <= g_9434; i++)
            if (g_1e90[i].f6 == 14 && g_1e90[i].f8 == g_9646 && g_1e90[i].f0 > 0
                && g_1e90[i].f0 < 9)
                return;
    idx = g_9646;
    w = g_1e30[idx].f22;
    h = g_1e30[idx].f24;
    SetRect(&g_1e5c, g_1e30[idx].f00 + 2, g_1e30[idx].f02 + 2,
            g_1e30[idx].f00 + w - 2, g_1e30[idx].f02 + w - 2);
    mode = g_7090[idx].f10;
    u1 = g_7090[idx].fea;      /* never read: CL drops the store, keeps the load */
    v = (g_7090[idx].fe4 ? idx : g_7090[idx].f50) + 40;
    if (mode == 0 || mode == 7)
        g_1e30[g_9646].f10 = g_1e30[g_9646].f28 * (h + w) + h;
    else
        g_1e30[g_9646].f10 = w * 16 + h * 17;
    if (mode > 3)
        g_1e30[g_9646].f12 = h * 2 + w;
    else if (g_7090[idx].fe9)
        g_1e30[g_9646].f12 = h;
    fn_08_0b76((char)g_9646 | 0xe00, 1, g_39e8[v], 0);
    hazards_ship_redraw_pending = 0;
}

/* Starts a dissolve effect on an object [inferred]. */
/* @addr 7:13b2 */
void far fn_07_13b2(char kind, int type, int idx)
{
    int i;
    int j;
    int u;
    int sq;
    int r;
    int found;

    if (type < 0)
        MessageBeep(0);
    if (type <= 14) {
        if (g_1df8[type][idx].f2e > 0)
            return;
        fn_10_754a(0x27, type, idx, 1);
    }
    found = 0;
    if (type <= 14) {
        if (g_1df8[type][idx].f22 % ((2 << g_9156) >> 1) == 0)
            r = 0;
        else
            r = 1;
        r += g_1df8[type][idx].f22 >> g_9156;
    } else if (type == 20)
        r = g_92a4 / 8;
    else if (type >= 21)
        r = 24;
    sq = r * r;
    for (i = 0; i < 4; i++) {
        if (g_221c[i].type != -1)
            continue;
        if (type <= 14)
            g_1df8[type][idx].f2e = kind;
        g_221c[i].type = type;
        g_221c[i].idx = idx;
        g_221c[i].sq = sq;
        g_221c[i].f58 = 0;
        g_221c[i].r = r;
        if (type == 14)
            g_7090[idx].feb = 1;
        for (j = 0; j < 80; j++)
            g_221c[i].b[j] = 0;
        found = 1;
        dissolve_active_count++;
        if (kind == 2 && g_221c[i].type <= 14)
            PatBlt(g_1df8[g_221c[i].type][g_221c[i].idx].f3c, 0, 0,
                   g_1df8[g_221c[i].type][g_221c[i].idx].f24 * 2
                       + g_1df8[g_221c[i].type][g_221c[i].idx].f22,
                   g_1df8[g_221c[i].type][g_221c[i].idx].f24 * 2
                       + g_1df8[g_221c[i].type][g_221c[i].idx].f22,
                   BLACKNESS);
        break;
    }
    if (!found && type <= 14)
        PatBlt(g_13dc, g_1df8[type][idx].f00, g_1df8[type][idx].f02,
               g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
}

/* Respawns ships waiting in state 100 after their timer runs out [inferred].
 * The redundant `j <= g_9316` test reproduces the extra jg. */
/* @addr 7:1d0c */
void far fn_07_1d0c(void)
{
    int i;
    int t;
    int j;
    int r;

    if (g_1e30[g_9646].f18 == 100)
        fn_07_1208();
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].f88 < g_1e50) {
            t = g_96f0[g_7090[i].f4e].f1a;
            for (j = i + 1; j <= g_9316; j++)
                if (j <= g_9316 && g_1e30[i].f18 == 100 && g_1e30[j].f18 == 100) {
                    g_7090[j].f88 = g_1e50 + 5000;
                    break;
                }
            if (g_1e30[i].f18 == 100 && (t != 7 || g_7090[i].f5e != 1)) {
                r = rand() % g_9318;
                if (i == g_9646)
                    r = 0;
                g_1e30[i].f04 = g_1df8[8][r * 2].f04;
                g_1e30[i].f04.x += (g_1df8[8][r * 2 + 1].f04.x - g_1df8[8][r * 2].f04.x) / 2
                                   - g_1e30[i].f20 / 2 + g_1df8[8]->f20 / 2;
                g_1e30[i].f18 = 0;
                if (i == g_9646)
                    g_96f0[g_7090[i].f4e].f24 = 1;
                fn_08_0000();
                fn_10_754a(0x27, 14, i, 1);
                fn_12_2556(14, i);
                fn_07_13b2(2, 14, i);
                for (j = g_9140 = 0; j <= g_9316; j++)
                    if (g_1e30[j].f18 == 100 && g_7090[j].fec)
                        g_9140 = 1;
                if (!g_9140 && g_9320 == 7)
                    g_668a = 1;
                if ((g_094e || g_0950) && i != g_9646)
                    command_watch_ship(0, 0);
                return;
            }
        }
    }
}

/* @addr 7:1f38 */
void far fn_07_1f38(void)
{
    HFONT oldfont;
    HFONT font;
    COLORREF textcol;
    COLORREF bkcol;

    if (g_9134 == 1 && g_058c) {
        font = CreateFont(14, 9, g_058c = 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
        oldfont = SelectObject(g_13dc, font);
        bkcol = SetBkColor(g_13dc, 0L);
        SetBkMode(g_13dc, OPAQUE);
        SetTextAlign(g_13dc, 0);
        textcol = SetTextColor(g_13dc, PALETTERGB(0, 0xff, 0xff));
        PatBlt(g_13dc, g_1d28.left + 10, g_1d28.top, g_1d28.right - 10, g_1d28.bottom,
               BLACKNESS);
        g_1d28.bottom += g_1d28.top;
        g_1d28.right += g_1d28.left;
        fn_02_094c(0x929);
        lstrcat(g_8e68, g_8630);
        ExtTextOut(g_13dc, g_1d28.left + 10, g_1d28.top, ETO_CLIPPED, &g_1d28,
                   g_8e68, lstrlen(g_8e68), NULL);
        g_1d28.bottom -= g_1d28.top;
        g_1d28.right -= g_1d28.left;
        SetBkColor(g_13dc, bkcol);
        SetTextColor(g_13dc, textcol);
        SelectObject(g_13dc, oldfont);
        if (font)
            DeleteObject(font);
    }
}

/* @addr 7:2080 */
void far fn_07_2080(int t)
{
    int i;

    if (t == 1 || t == 2 || t == 7 || t == 5 || t == 11 || t == 9
        || t == 10 || t == 4 || t == 6 || t == 8 || t == 19) {
        for (i = g_92ec[t]; i > 0; i--)
            if (g_1df8[t][i - 1].f18 == 0 || g_1df8[t][i - 1].f51 != 0) {
                g_9406[t] = i;
                break;
            }
        if (i == 0)
            g_9406[t] = 0;
    }
}

/* @addr 7:2128 */
void far fn_07_2128(void)
{
    int i;
    char unused[72];

    if (g_9316 == 0) {
        g_9432 -= max(g_9432 / 50, 2);
        if (g_9432 < 0)
            g_9432 = 0;
        return;
    }
    for (i = 0; i < g_9316; i++)
        if (g_7090[i].f32 == 14 && g_7090[i].f34 == g_9646 && g_7090[i].f38 == 1) {
            g_9432 -= max(g_9432 / 18, 4);
            if (g_9432 < 0)
                g_9432 = 0;
            if (g_8e28 + 15000 < g_1e50) {
                g_9432 -= max(g_9432 / 14, 4);
                if (g_9432 < 0)
                    g_9432 = 0;
            }
            return;
        }
    g_9432 -= max(g_9432 / 40, 3);
    if (g_9432 < 0)
        g_9432 = 0;
    if (g_8e28 + 15000 < g_1e50) {
        g_9432 -= max(g_9432 / 36, 2);
        if (g_9432 < 0)
            g_9432 = 0;
    }
}

/* Frame-rate bookkeeping [inferred]: counts frames per 250 ms and per
 * second and rescales g_9004 when off target. */
/* @addr 7:2206 */
void far fn_07_2206(void)
{
    int a;
    int b;

    if (g_90f4 == 6 && g_952c && g_9530 == 1) {
        b = g_6da4->f2a;
        a = b / 4;
    } else if (g_90f4 == 6 && g_914a == 1 && g_92a2 == 0) {
        a = 8;
        b = 32;
    } else {
        a = 18;
        b = 72;
    }
    g_914c++;
    if (g_1e50 > g_1e64) {
        if (a + 1 < g_914c || a - 1 > g_914c) {
            if (g_914c > a && g_9004 == 0)
                g_9004 = 1;
            g_9004 = g_914c * g_9004 / a;
        }
        g_1e64 = g_1e50 + 250;
        g_914c = 0;
    }
    g_0586++;
    if (g_1e50 > g_1e8c) {
        g_1e8c = g_1e50 + 1000;
        if (b + 9 > g_0586 && b - 9 < g_0586) {
            if (b < g_0586 && g_9004 == 0)
                g_9004 = 1;
            g_9004 = g_9004 * g_0586 / b;
        }
        if (g_0592)
            g_0592--;
        g_059a = g_0586;
        g_0586 = 0;
    }
}
