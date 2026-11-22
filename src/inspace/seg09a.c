/* INSPACE.EXE segment 9 (selector 1040), 9:0000-0ac4: one source file
 * (functions near-call each other) [inferred]. */
#include <stdlib.h>
#include "inspace.h"
#include <shellapi.h>
#include <dos.h>

/* Records reached through far pointers or DGROUP arrays; only the fields
 * this file uses are named (offset in the name). */
typedef struct {                /* 0x70 bytes; DS:1df8 holds far arrays of them */
    char p00[0x0c];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x18 - 0x10];
    int f18;
    char p1a[0x1e - 0x1a];
    int f1e;
    char p20[0x2f - 0x20];
    char f2f;
    char p30[0x51 - 0x30];
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
    char p020[0x4e - 0x20];
    int f4e;                    /* +4e */
    char p050[0xec - 0x50];
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
extern char g_94ac;
extern int g_13de;
extern long g_1e50;
extern long g_1e78;
extern long g_1e88;
extern REC_70 far *g_1df8[16];
extern int g_3a02;
extern char g_38c8[];                /* directory path [inferred] */
extern struct _find_t g_3948;       /* name at DS:3966 */
extern HGDIOBJ g_4e94[32];
extern REC_23 g_57a8[];
extern void far *g_4fcc;
extern long g_5078;
extern LPSTR g_6078;
extern REC_297 far *g_69f4;
extern REC_15A g_7090[];
extern long g_09bc[12];
extern int g_90ea;
extern int g_9200;
extern int g_9202;
extern int g_9204;
extern int g_9206;
extern int g_91fa;
extern int g_91fc;
extern int g_91fe;
extern HINSTANCE g_8e66;
extern int g_92e6;
extern int g_9316;
extern int g_9318;
extern int g_9322;
extern int g_9320;
extern int g_9334;
extern int g_9406;
extern int g_9408;
extern int g_94b0;
extern int g_94a2;
extern int g_9518;
extern int g_9646;
extern int g_90f4;
extern HGLOBAL g_93a8;
extern HGDIOBJ g_93ae;
extern HGLOBAL g_93b4;
extern REC_AD g_96f0[];

void far fn_10_6d52(int a, int b, int c, int d, int e, int f);
void far fn_17_306e(void);
void far fn_03_1542(int a, int b, int n, LPSTR buf, int c);
void far fn_07_2512(int i, int v);
void far fn_09_6a12(void);
void far fn_09_0000(int a);
void far fn_10_022e(int a);
void far fn_10_0736(int slot);
void far fn_11_02f0(void);
void far fn_13_65f2(int a);

int far fn_09_094c(void);
int far fn_09_08da(int x, int y);
int far fn_09_0ac4(int n, int count);
void far fn_09_0278(UINT kind, int slot);
void far pascal fn_09_0156(LPSTR file);
void far fn_09_0352(HDC hdc, int x, int flags, int w, int h, LPSTR name);
void far fn_09_09b0(int slot);
int far fn_09_955c(UINT id, LPSTR buf);
void far fn_09_95ba(UINT id);

/* @addr 9:0000 */
void far fn_09_0000(int max)
{
    char path[128];
    int r;

    g_9204 = max;
    g_9206 = g_9200 = g_9202 = 0;
    g_69f4[g_94a2].f1d0 = 2;
    lstrcpy(path, g_38c8);
    lstrcat(path, "*.exe");
    for (r = _dos_findfirst(path, _A_RDONLY, &g_3948); r == 0; r = _dos_findnext(&g_3948)) {
        if (g_9206 > 9)
            goto doneexe;
        lstrcpy(path, g_38c8);
        lstrcat(path, g_3948.name);
        fn_09_0156(path);
    }
doneexe:
    lstrcpy(path, g_38c8);
    lstrcat(path, "*.dll");
    for (r = _dos_findfirst(path, _A_RDONLY, &g_3948); r == 0; r = _dos_findnext(&g_3948)) {
        if (g_9206 > 9)
            goto donedll;
        lstrcpy(path, g_38c8);
        lstrcat(path, g_3948.name);
        fn_09_0156(path);
    }
donedll:
    if (g_9202 && g_69f4[g_94a2].f1d0 != 1)
        g_69f4[g_94a2].f1d0 = 0;
    g_91fe = g_91fc = g_91fa = min(g_9206, g_9204);
    g_9204 = 8;
}

/* @addr 9:0156 */
void far pascal fn_09_0156(LPSTR file)
{
    int i;
    int n;
    int slot;
    int w;
    int h;
    HICON icon;

    w = 32;
    h = 6;
    n = (int)ExtractIcon(g_8e66, file, -1);
    if (n) {
        for (i = 0; g_9206 <= 9 && i < n; i++) {
            if (fn_09_0ac4(g_9200, 0))
                g_9200++;
            else {
                slot = fn_09_094c();
                if (slot == -1)
                    return;
                icon = ExtractIcon(g_8e66, file, i);
                if ((UINT)icon > 1) {
                    PatBlt((HDC)g_3a02, (h + w) * slot + h, h, w, w, BLACKNESS);
                    DrawIcon((HDC)g_3a02, (h + w) * slot + h, h, icon);
                    DestroyIcon(icon);
                }
                if (fn_09_08da((h + w) * slot + h, h))
                    fn_09_0278(0, slot);
                else
                    fn_09_09b0(slot);
            }
        }
    } else {
        n = (int)ExtractIcon(g_8e66, file, 0);
        if (n == 0)
            fn_09_0278(0, -1);
        else
            fn_09_0278(0x107, -1);
    }
}

/* @addr 9:0278 */
void far fn_09_0278(UINT kind, int slot)
{
    int i;
    int j;
    int flags;
    int w;
    int h;
    int ok;
    int unused;
    char name[12];
    char ext[6];

    w = 32;
    h = 6;
    lstrcpy(name, g_3948.name);
    lstrcpy(ext, ".DLL");
    ok = 1;
    for (i = 0; i < 4; i++) {
        j = lstrlen(name) + i - 4;
        if (name[j] != ext[i])
            ok = 0;
    }
    name[lstrlen(name) - 4] = 0;
    flags = 32;
    switch (kind) {
    case 0x106:
    case 0x107:
        flags = 0;
    }
    if (slot == -1) {
        slot = fn_09_094c();
        if (slot == -1)
            return;
    }
    fn_09_0352((HDC)g_3a02, (h + w) * slot + h, flags, w, h, name);
    fn_09_09b0(slot);
}

/* Draws a drive/file icon at (x, y) with its caption: name without a
 * 4-character extension [inferred]. */
/* @addr 9:0352 */
void far fn_09_0352(HDC hdc, int x, int flags, int w, int y, LPSTR name)
{
    HGDIOBJ oldfont;
    HFONT hfont;
    DWORD tc;
    DWORD bk;
    int unused;
    HGDIOBJ oldbrush;
    HGDIOBJ oldpen;
    char drv[10];
    char buf[110];

    lstrcpy(buf, name);
    if (lstrlen(buf) > 4 && buf[lstrlen(buf) - 4] == '.')
        buf[lstrlen(buf) - 4] = 0;
    if (hdc == 0)
        drv[1] = 0;
    PatBlt(hdc, x, y, w, w, BLACKNESS);
    if (flags) {
        oldbrush = SelectObject(hdc, GetStockObject(GRAY_BRUSH));
        PatBlt(hdc, x, y, 32, 21, PATCOPY);
        SelectObject(hdc, CreateSolidBrush(0x800000L));
        PatBlt(hdc, x, y, 32, 9, PATCOPY);
        DeleteObject(SelectObject(hdc, GetStockObject(LTGRAY_BRUSH)));
        PatBlt(hdc, x, y, 8, 8, PATCOPY);
        SelectObject(hdc, oldbrush);
        oldpen = SelectObject(hdc, GetStockObject(WHITE_PEN));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, x, y);
        LineTo(hdc, x + 32, y);
        SelectObject(hdc, CreatePen(PS_SOLID, 1, 0xc0c0c0L));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, w + x - 1, y + 20);
        LineTo(hdc, w + x - 1, y);
        DeleteObject(SelectObject(hdc, GetStockObject(BLACK_PEN)));
        MoveTo(hdc, x + 1, y + 8);
        LineTo(hdc, x + 8, y + 8);
        LineTo(hdc, x + 8, y + 1);
        MoveTo(hdc, x + 1, y + 5);
        LineTo(hdc, x + 7, y + 5);
        SelectObject(hdc, CreatePen(PS_SOLID, 1, 0x808080L));
        MoveTo(hdc, x + 1, y + 3);
        LineTo(hdc, x + 7, y + 3);
        DeleteObject(SelectObject(hdc, oldpen));
        SetPixel(hdc, x + 1, y + 4, 0);
        SetPixel(hdc, x + 6, y + 4, 0);
    } else {
        oldpen = SelectObject(hdc, GetStockObject(WHITE_PEN));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, x, y);
        LineTo(hdc, x + 32, y);
        SelectObject(hdc, CreatePen(PS_SOLID, 1, 0x808080L));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, w + x - 1, y + 20);
        LineTo(hdc, w + x - 1, y);
        DeleteObject(SelectObject(hdc, oldpen));
        SetPixel(hdc, x, y, 0);
        SetPixel(hdc, x, y + 20, 0);
        SetPixel(hdc, w + x - 1, y, 0);
        SetPixel(hdc, w + x - 1, y + 20, 0);
        SetPixel(hdc, x + 1, y + 1, 0xc0c0c0L);
        SetPixel(hdc, x + 1, y + 19, 0xc0c0c0L);
        SetPixel(hdc, w + x - 2, y + 1, 0xc0c0c0L);
        SetPixel(hdc, w + x - 2, y + 19, 0xc0c0c0L);
        hfont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
        oldfont = SelectObject(hdc, hfont);
        SetBkMode(hdc, OPAQUE);
        bk = SetBkColor(hdc, 0);
        SetTextAlign(hdc, 0);
        tc = SetTextColor(hdc, 0xff00L);
        lstrcpy(drv, "C:>");
        drv[0] += g_94ac;
        TextOut(hdc, x + 2, y + 2, drv, lstrlen(drv));
        SetTextColor(hdc, tc);
        SetBkColor(hdc, bk);
        SelectObject(hdc, oldfont);
        if (hfont) {
            DeleteObject(hfont);
            hfont = 0;
        }
    }
    hfont = CreateFont(7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Small Fonts");
    oldfont = SelectObject(hdc, hfont);
    bk = SetBkColor(hdc, 0);
    SetTextAlign(hdc, TA_CENTER);
    tc = SetTextColor(hdc, 0xffffffL);
    TextOut(hdc, x + 16, y + 26, buf, lstrlen(buf));
    SetTextColor(hdc, tc);
    SetBkColor(hdc, bk);
    SelectObject(hdc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
    PatBlt(hdc, x - y, y, y, w, BLACKNESS);
    PatBlt(hdc, w + x, y, y, w, BLACKNESS);
}

/* @addr 9:08da */
int far fn_09_08da(int x, int y)
{
    int i;
    int j;
    COLORREF c;

    c = GetPixel((HDC)g_3a02, 0, 0);
    for (i = x; i < x + 32; i++)
        for (j = y; j < y + 32; j++)
            if (GetPixel((HDC)g_3a02, i, j) != c)
                return 0;
    return 1;
}

/* @addr 9:094c */
int far fn_09_094c(void)
{
    int i;
    int unused;
    int found;

    for (i = 0; i < g_9406; i++) {
        found = 1;
        if (g_1df8[0][i].f18 == 0)
            found = 0;
        if (found)
            return i;
    }
    g_69f4[g_94a2].f1d0 = 1;
    g_9206++;
    return -1;
}

/* @addr 9:09b0 */
void far fn_09_09b0(int slot)
{
    int unused;

    if (fn_09_0ac4(g_9200, 1))
        return;
    if (g_9206 < g_9204) {
        g_57a8[slot].f02 = g_57a8[slot].f00 = 0;
        g_57a8[slot].f0a = g_57a8[slot].f0b = -1;
        g_57a8[slot].f19 = 0;
        if (g_69f4[g_94a2].f1d2[slot] < 0)
            g_69f4[g_94a2].f1d2[slot] = 0;
        g_1df8[0][slot].f1e = g_69f4[g_94a2].f1d2[slot];
        g_57a8[slot].f06 = g_9200 - 1;
        lstrcpy(g_57a8[slot].f0c, g_3948.name);
        g_1df8[0][slot].f18 = 0;
        fn_10_0736(slot);
        g_1df8[0][slot].f0c = rand() % 60 - 30;
        g_1df8[0][slot].f0e = rand() % 60 - 30;
        g_9202++;
    } else
        g_69f4[g_94a2].f1d0 = 1;
    g_9206++;
}

/* @addr 9:0ac4 */
int far fn_09_0ac4(int n, int count)
{
    unsigned char mask;
    int unused;
    int idx;

    idx = n / 8;
    mask = 1 << (n % 8);
    if (count)
        g_9200++;
    if (g_69f4[g_94a2].f1e2[idx] & mask)
        return 1;
    return 0;
}


