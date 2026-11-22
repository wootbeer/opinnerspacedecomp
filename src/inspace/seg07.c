/* INSPACE.EXE segment 7 (selector 1030). */
#include "inspace.h"
#include <stdlib.h>

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    int f00;
    int f02;
    char p04[0x0c - 0x04];
    int f0c;                    /* +c */
    int f0e;                    /* +e */
    int f10;                    /* +10 */
    char p12[0x18 - 0x12];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    int f1c;                    /* +1c */
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    char p26[0x2c - 0x26];
    int f2c;                    /* +2c */
    char f2e;                   /* +2e */
    char p2f[0x44 - 0x2f];
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

typedef struct {                /* 0x15a bytes, DGROUP array at DS:70ae */
    char p00[0x14];
    int f14;
    int f16;
    char p18[0x1a - 0x18];
    int f1a;
    char p1c[0xb2 - 0x1c];
    int fb2;
    char pb4[0x15a - 0xb4];
} REC_15A;

typedef struct { int f0, f2, f4, f6; char rest[0x1e - 8]; } REC_1E;

typedef struct { int x, y; char rest[0x70 - 4]; } REC_70P;

extern REC_70 far *g_1df8[16];
extern REC_70P far *g_1e30;
extern int g_3a02;
extern int g_3a28;
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
extern int g_914c;
extern DWORD g_1e64;
extern DWORD g_1e8c;
extern int g_9004;
extern int g_0586;
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
extern DWORD g_1e50;
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
extern REC_15A g_70ae[];
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

/* @addr 7:11cc */
void far fn_07_11cc(void)
{
    g_1e30[g_9646].x = g_90ea / 2;
    g_1e30[g_9646].y = g_90ec / 2;
}

/* @addr 7:119c */
void far fn_07_119c(int a)
{
    g_0a76 = a;
    if (g_0a7c)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
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
        if (g_70ae[i].f14 == 14 && g_70ae[i].f16 == g_9646 && g_70ae[i].f1a == 1) {
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
/* near-match 76%: 7:2206 */
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

/* @addr 7:2512 */
void far fn_07_2512(int n, int m)
{
    int size;
    int gap;
    HDC memdc;
    HGDIOBJ old;
    HBITMAP bmp;
    HBITMAP bmp2;

    if (g_57a8[n].f00 == 0) {
        gap = g_1df8[0][n].f24;
        size = g_1df8[0][n].f22;
        memdc = CreateCompatibleDC(g_13dc);
        old = SelectObject(memdc, bmp2 = fn_10_6ec6(bmp = fn_10_6308(-1, -1,
                                    fn_10_6c02(0x168, 0, -1), -1)));
        BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
               memdc, size * m, 0, SRCAND);
        SelectObject(memdc, bmp);
        BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
               memdc, size * m, 0, SRCPAINT);
        SelectObject(memdc, old);
        DeleteDC(memdc);
        DeleteObject(bmp);
        DeleteObject(bmp2);
        g_69f4[g_94a2].f1c8[n] = m + 1;
        if (m == 0)
            g_1df8[0][n].f53 = 2;
    }
    fn_07_65aa(0, n);
}

/* @addr 7:2652 */
int far fn_07_2652(int type, int idx, int amount)
{
    if (type == 15)
        return 0;
    if (g_1df8[type][idx].f1e > g_1df8[type][idx].f2c && type != 9)
        return 0;
    g_1df8[type][idx].f1e += amount;
    if (g_1df8[type][idx].f1e > g_1df8[type][idx].f2c) {
        g_1df8[type][idx].f66(type, idx);
        return 1;
    }
    return 0;
}

/* @addr 7:26c4 */
void far fn_07_26c4(int unused, int n)
{
    g_1df8[0][n].f1e = -1;
    g_69f4[g_94a2].f1d2[n] = g_1df8[0][n].f1e;
    fn_10_754a(0x1f, 0, n, 1);
    fn_07_2768(n);
    g_1df8[0][n].f18 = 1;
    fn_07_65aa(0, n);
    PatBlt(g_13dc, g_1df8[0][n].f00, g_1df8[0][n].f02,
           (32 << g_9156) >> 1, (32 << g_9156) >> 1, BLACKNESS);
    fn_07_5ae8(n, 0);
}

/* @addr 7:3294 */
void far pascal fn_07_3294(int n)
{
    fn_08_1d54((char)n, 0x1e);
    if (!g_1df8[0][n].f54)
        fn_08_1b54((char)n, 3);
}

/* @addr 7:32d0 */
void far fn_07_32d0(void)
{
    int i;
    int u1;
    int r;
    int size;
    int u2[6];
    HGDIOBJ old;

    size = (6 << g_9156) >> 1;
    for (i = 0; i < g_9408; i++) {
        if (g_1df8[1][i].f18 == 0) {
            if (g_1df8[1][i].f1a != 0 && g_4e94[i] != 0) {
                old = SelectObject(g_9288, g_4e94[i]);
                g_1df8[1][i].f10 = size;
                fn_08_1d54((char)i | 0x100, 0x28);
                fn_08_1b54((char)i | 0x100, 1);
                fn_08_0b76((char)i | 0x100, 3, g_9288, 0);
                SelectObject(g_9288, old);
                if (g_1df8[1][i].f1c == 0) {
                    g_943a = 1;
                    g_943c = i;
                    r = fn_08_50aa((char)i | 0x100);
                    if (r != -1)
                        fn_08_5df2(1, i, HIBYTE(r), LOBYTE(r),
                                   fn_08_546c(r, &g_1df8[1][i].f0c, &g_1df8[1][i].f0e,
                                              g_1df8[1][i].f20 + 2, g_1df8[1][i].f44));
                }
            } else if (g_9142 % 3 == 0)
                fn_07_3400(i);
        }
    }
}

/* @addr 7:3400 */
void far pascal fn_07_3400(int n)
{
    fn_08_1d54((char)n | 0x100, 0x28);
    fn_08_1b54((char)n | 0x100, 3);
}

/* @addr 7:49b6 */
void far fn_07_49b6(void)
{
    int i;

    for (i = 0; i < 8; i++)
        if (g_3a04[i]) {
            SelectObject(g_3a04[i], g_3990[i]);
            if (g_3a78[i])
                SelectPalette(g_3a04[i], g_3a78[i], 0);
            DeleteDC(g_3a04[i]);
            g_3a04[i] = 0;
            if (g_3aec[i]) {
                DeleteObject(g_3aec[i]);
                g_3aec[i] = 0;
            }
        }
}

/* @addr 7:4ffe */
void far fn_07_4ffe(int n)
{
    int i;

    PatBlt(g_13dc, g_1df8[0][n].f00, g_1df8[0][n].f02,
           g_1df8[0][n].f22, g_1df8[0][n].f22, BLACKNESS);
    g_1df8[0][n].f18 = 1;
    for (i = 0; i < 2; i++)
        fn_07_5b68(0, n, 1);
    fn_07_5ae8(n, 0);
    fn_07_65aa(0, n);
    fn_08_99ce(0, n, -1, -1, 1);
}

/* Counts empty slots in g_91fc and marks used ones in a bit set
 * [inferred]. */
/* @addr 7:5a46 */
void far fn_07_5a46(void)
{
    int i;
    int n, byte;
    unsigned char bit;

    for (i = g_91fc = 0; i < 8; i++) {
        if (g_1df8[0][i].f18 != 0 || g_1df8[0][i].f2e != 0 || g_1df8[0][i].f51 != 0) {
            if (g_57a8[i].f06 > -1) {
                n = g_57a8[i].f06;
                byte = n / 8;
                bit = 1 << (n % 8);
                g_69f4[g_94a2].f1e2[byte] |= bit;
            }
        } else
            g_91fc++;
    }
}

/* @addr 7:5ae8 */
void far fn_07_5ae8(int a, int b)
{
    fn_07_5a46();
    if (b) {
        g_69f4[g_94a2].f150++;
        g_945c++;
    } else {
        g_69f4[g_94a2].f14e++;
        if (g_57a8[a].f0a == g_9324)
            g_70ae[g_57a8[a].f0b].fb2++;
        g_945e++;
    }
    if (g_91fc == 0 && g_69f4[g_94a2].f1d0 != 1)
        g_69f4[g_94a2].f1d0 = 2;
}

/* @addr 7:5660 */
void far fn_07_5660(int n)
{
    int size, gap;

    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    StretchBlt(g_3a02, (size + gap) * n + gap, gap, size, size,
               g_3a28, n * 32, 0, 32, 32, SRCCOPY);
    fn_07_233c(0, n, 0);
}

/* @addr 7:56ba */
void far fn_07_56ba(int n)
{
    int size, gap;

    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    StretchBlt(g_3a28, n * 32, 0, 32, 32,
               g_3a02, (size + gap) * n + gap, gap, size, size, SRCCOPY);
}

/* @addr 7:5d6a */
void far fn_07_5d6a(int a, int b, int unused, int c, int d)
{
    int i;
    int pct;

    switch (g_9208) {
    case 0:
        pct = 20;
        break;
    case 1:
        pct = 45;
        break;
    case 2:
        pct = 70;
        break;
    case 3:
        pct = 100;
        break;
    }
    if (g_9208 != 3 && rand() % 100 < pct)
        return;
    for (i = 0; i < 20; i++)
        if (g_58bc[i].f10 == -1) {
            g_58bc[i].f10 = 0;
            g_58bc[i].c.x = a;
            g_58bc[i].c.y = b;
            g_58bc[i].fc = c;
            g_58bc[i].fe = d;
            g_9456++;
            return;
        }
}

/* @addr 7:63b6 */
void far fn_07_63b6(HMENU menu, LPCSTR text, int checked, UINT id)
{
    UINT flags;

    if (checked)
        flags = MF_CHECKED;
    else
        flags = 0;
    ModifyMenu(menu, id, flags, id, text);
}

/* @addr 7:641a */
void far fn_07_641a(void)
{
    int i;

    if (g_0a7c && !g_9458 && g_91fc) {
        for (i = 0; i < g_91fe; i++) {
            g_6ea8[i].f6 = 0;
            g_6ea8[i].f4 = i;
            g_6ea8[i].f0 = 2;
            g_6ea8[i].f2 = i * 0x2e + 2;
        }
        CreateWindow("IS_ICON", "", 0x10cc0000L, g_1de4, g_1de6, 50, 150,
                     g_0016, 0, g_8e66, 0L);
    }
    SetActiveWindow(g_0016);
}

/* @addr 7:64ac */
int far fn_07_64ac(HDC dc, int a, int idx)
{
    int i;
    int u1, u2;
    int release;
    HPALETTE old;

    if (!g_9458)
        return 1;
    release = 0;
    if (!dc) {
        release = 1;
        dc = GetDC(g_9458);
    }
    if (g_920e)
        old = SelectPalette(dc, g_920e, 0);
    if (idx == -1) {
        for (i = 0; i < g_91fe; i++)
            fn_13_5a6a(dc, 0, i * 0x2e + 4, 0, i, i + 3, a, g_0b6e);
    } else
        fn_13_5a6a(dc, 0, idx * 0x2e + 4, 0, idx, idx + 3, a, g_0b6e);
    if (old)
        SelectPalette(dc, old, 0);
    if (release) {
        ReleaseDC(g_9458, dc);
        dc = 0;
    }
    if (g_91fc)
        return 1;
    if (!dc)
        fn_07_63f2();
    return 0;
}

/* @addr 7:65aa */
void far fn_07_65aa(int a, int b)
{
    int k;

    if (a == 0)
        fn_07_64ac(0, 1, b);
    if (a == g_9324 && b != g_9646)
        fn_13_6450(0, 1, b);
    if (g_0a76 == 2 || g_0a76 == 3) {
        k = g_0a76 - 2;
        if (g_6e52[k].f2 == a && g_6e52[k].f0 == b)
            fn_13_58dc(0, 1);
    }
}

/* @addr 7:63f2 */
void far fn_07_63f2(void)
{
    if (g_9458) {
        DestroyWindow(g_9458);
        g_9458 = 0;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_07_233c(int a, int b, int c)
{
    g_0a76 = a + b + c;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_07_5b68(int a, int b, int c)
{
    g_0a76 = a + b + c;
}


/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_07_2768(int n)
{
    g_0a76 = n;
}
