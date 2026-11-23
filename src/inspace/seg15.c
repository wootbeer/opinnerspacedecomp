/* INSPACE.EXE segment 15 (selector 1070). */
#include "inspace.h"
#include <dos.h>
#include <stdlib.h>

extern int g_1016;
extern int g_8ffc;
extern long g_3b98;
extern int g_95d8;
extern int g_95dc;
extern char g_87e0[];               /* run-time buffer (BSS) */
extern char g_881c[];               /* run-time buffer (BSS) */
extern DWORD g_1e50;              /* before g_6e28: compare operand order (15:5962) */
extern DWORD g_6e28;
extern long g_6e2c;

extern int g_92a8;
extern int g_92aa;
extern int g_92b6;
extern int g_92bc;
extern int g_92ac;
extern int g_92ae;
extern int g_92b8;
extern int g_92c2;
extern int g_92b0[3];
extern int g_3cc8[2];
extern int g_95d0;
extern int g_94ac;
extern int g_90ee;
extern int g_11aa;
extern char g_9078[];               /* run-time buffer (BSS) */
extern char g_96b8[];               /* run-time buffer (BSS) */

extern int g_94c4;
extern int g_90f4;
extern int g_92d4;
extern HBRUSH g_5ea8;
extern int g_90ea;
extern int g_90ec;

extern int g_920c;
extern int g_95d6;
extern HINSTANCE g_8e66;

extern RECT g_3cb8;
extern HDC g_929a;
void far fn_10_949c(HDC dc, int x, int y, int w, int h, int style);
HBITMAP far fn_10_6c02(int a, int b, int c);


extern int flow_interactive;     /* DS:95bc */
extern int g_9134;
extern DWORD g_05b4;
extern int g_91f8;
extern int g_95ba;
extern int g_95c8;
extern int g_95ca;
extern int g_95d4;
extern int g_95de;
extern BYTE g_95e0[18];
typedef struct { char p00[0x0a]; char name[0x41 - 0x0a]; } REC_41;
extern REC_41 far *g_6e20;
void far fn_15_10be(void);
void far fn_15_5e22(int a);
void far fn_15_6cdc(void);
void far fn_15_7cda(void);
void far fn_15_6890(void);
void far fn_15_6b52(void);
void far fn_15_7b34(void);
void far fn_14_3eda(void);
void far fn_14_31d0(int a, LPSTR s);
void far fn_14_4074(void);
void far fn_06_92b8(void);
void far fn_06_930a(void);
void far fn_06_1d9a(void);
void far fn_06_1c72(int a);
void far fn_06_7266(void);
void far fn_10_7d58(int x, int y);

extern int g_95da;
extern int g_9224;
extern int g_922a;
extern int g_95ce;
extern HBITMAP g_95be;
extern HDC g_95c2;
extern HGDIOBJ g_95c0;
extern HPALETTE g_95c4;
extern int g_90f0;
extern int g_8fe8;
extern int g_95c6;
extern DWORD g_1c6c;
extern HINSTANCE g_9212;
void far fn_10_6ea0(unsigned a);
void far fn_11_3fd4(LPSTR s, int a);
int far fn_09_955c(UINT id, LPSTR buf);
int far fn_10_946a(char far *p);
void far fn_10_9962(int a, HDC dst, int x, int y, int w, int h, HDC src,
                    int xs, int ys, int ws, int hs, DWORD rop);
int far fn_10_73a6(int id, LPSTR name, int a, int b, int c, int d, int e, char f, char g);
void far fn_06_72d8(int n, int m);
void far fn_06_78ea(int kind, int x, int y, int vx, int vy, int size, int n, int c);
extern DWORD g_130c;
extern int g_920a;
extern HDC g_3a14;
int far fn_15_8174(int which, int n);

extern int g_92d2;
extern RECT g_3ca8;               /* after g_92d2: load order in 15:8604 */
extern RECT g_6e30;
extern RECT g_6084;

void far fn_06_84fc(int a, int x, int y, int dx, int dy, int w, int h,
                    int c, int d, int e);
int far fn_06_73f6(void);
int far fn_06_7c14(void);
extern int g_0010;
extern int g_90f8;
extern int g_8e5e;
extern int g_95f2;
extern int g_8f70;
extern int g_001a;
extern int g_9516;
extern int g_95b8;
extern int g_95cc;
extern int g_95d2;
extern int g_9156;
extern int g_1212;
extern DWORD g_120e;
extern int g_8ffa;
extern HBITMAP g_3820;
extern HBITMAP g_3822;
extern HBRUSH g_5eaa;
extern WORD g_06c6[8];              /* 8x8 pattern bits */
extern WORD g_06b6[8];              /* 8x8 pattern bits */
void far fn_10_4b2e(void);
void far fn_10_7480(int a, int b);
void far fn_10_885e(int a);
void far fn_10_39a8(int a);
void far fn_10_73e2(void);
void far fn_10_744c(int a);
void far fn_15_5962(int a);
void far fn_15_5914(void);
extern char g_380c[];               /* run-time buffer (BSS) */
int far fn_10_9764(int a);
void far fn_15_6558(int drive, LPSTR out);
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
int far fn_14_4006(HFILE f, char huge *buf, unsigned long len);

void far fn_10_6e4c(void);
void far fn_10_6e76(int lo, int hi);   /* seg10 declares (long a) */
void far fn_10_0552(int i, int a);
void far fn_10_58ce(int a);
void far fn_10_754a(int a, int b, int c, int d);
int far fn_10_6d38(LPCSTR s);
void far fn_10_0136(void);
void far fn_11_a4a6(long a, long b, int c);
void far fn_11_a9ea(int a);


/* Reads demogame.sav and returns its word at +0x22 [inferred]; the result
 * is uninitialised when the read fails (as in the original). */
/* @addr 15:5d14 */
int far fn_15_5d14(void)
{
    HFILE hf;
    int result;
    DWORD size;
    long unused;
    HGLOBAL h;
    int far *lp;
    char path[140];
    OFSTRUCT of;

    lstrcpy(path, g_9078);
    lstrcat(path, g_96b8);
    lstrcat(path, "demogame.sav");
    h = GlobalAlloc(GHND, 425L);
    if (!h)
        return -1;
    lp = (int far *)GlobalLock(h);
    if (!lp) {
        GlobalFree(h);
        return -1;
    }
    hf = OpenFile(path, &of, 0);
    if (hf == -1) {
        GlobalUnlock(h);
        GlobalFree(h);
        return -1;
    }
    size = GlobalSize(h);
    GlobalUnlock(h);
    if (!fn_14_4006(hf, (char huge *)(lp = (int far *)GlobalLock(h = GlobalReAlloc(h, size, GHND))), size))
        MessageBeep(0);
    else
        result = lp[0x11];
    _lclose(hf);
    GlobalUnlock(h);
    GlobalFree(h);
    return result;
}

/* @addr 15:5786 */
void far fn_15_5786(void)
{
    HPALETTE oldpal;

    PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
    fn_10_4b2e();
    fn_10_7480(-1, 1);
    if (g_90f8 && g_8e5e) {
        if (!g_95f2)
            g_95f2 = g_8f70 = 1;
        else if (rand() % 6)
            g_8f70 = 1;
        else
            g_8f70 = 0;
    }
    g_9516 = g_001a = 0;
    fn_10_885e(0);
    g_95b8 = 0;
    g_1e50 = GetCurrentTime();
    g_6e28 = g_1e50 + 65000L;
    g_95cc = 0;
    g_95d0 = 0x122;
    g_95d2 = 5000;
    ShowWindow(g_0016, SW_SHOW);
    fn_15_5914();
    g_5ea8 = CreatePatternBrush(g_3820 = CreateBitmap(8, 8, 1, 1, g_06c6));
    g_5eaa = CreatePatternBrush(g_3822 = CreateBitmap(8, 8, 1, 1, g_06b6));
    if (g_920e) {
        oldpal = SelectPalette(g_13dc, g_920e, 0);
        RealizePalette(g_13dc);
    }
    if (g_9156 != 1) {
        fn_10_0552(5, 1);
        fn_10_39a8(0);
    }
    fn_15_5962(1);
    if (oldpal)
        SelectPalette(g_13dc, oldpal, 0);
    fn_10_73e2();
    fn_10_744c(0x6e);
    fn_10_7480(-5, 1);
    if (!g_1212) {
        g_120e = GetCurrentTime();
        g_8ffa = 0;
    }
}

/* @addr 15:5914 */
void far fn_15_5914(void)
{
    g_95f4 = fn_10_6d38("SD_LOGO");
}

/* @addr 15:5932 */
void far fn_15_5932(void)
{
    int unused;

    fn_10_0136();
    if (g_95f4) {
        DeleteObject(g_95f4);
        g_95f4 = 0;
    }
}

void far fn_15_80da(void);

/* @addr 15:80b0 */
void far fn_15_80b0(long a, long b)
{
    fn_15_80da();
    fn_11_a4a6(a, g_3b98 = b, 14);
}

/* @addr 15:80da */
void far fn_15_80da(void)
{
    if (g_1016) {
        if (g_8ffc < 0x578) {
            fn_11_a9ea(0);
            g_1016 = 0;
        } else {
            do
                fn_11_a9ea(0);
            while (g_1016);
        }
    }
}

void far fn_15_811a(void);

/* Builds a drive description: letter, a loaded string and the volume
 * label of the drive [inferred]. */
/* @addr 15:6558 */
void far fn_15_6558(int drive, LPSTR out)
{
    struct find_t ft;
    int j;
    unsigned rc;
    char buf[50];

    lstrcpy(out, "C");
    out[0] += g_94ac;
    LoadString(g_9212, 0x3a9, buf, 30);
    lstrcat(out, buf);
    lstrcpy(buf, "C:\\*.*");
    buf[0] += drive;
    ft.name[0] = 0;
    rc = _dos_findfirst(buf, _A_VOLID, &ft);
    if (rc != 0 || ft.name[0] == 0) {
        lstrcpy(buf, "Unknown_HD");
    } else {
        lstrcpy(buf, ft.name);
        if (lstrlen(buf) > 7 && buf[8] == '.')
            for (j = 8; lstrlen(buf) > j; j++)
                buf[j] = buf[j + 1];
    }
    lstrcat(out, buf);
}

/* @addr 15:6640 */
void far fn_15_6640(void)
{
    char buf1[100];
    char buf2[40];
    int k;

    fn_10_744c(0x6e);
    fn_10_754a(0x6f, g_90ea / 2, g_90ec / 2 - 240, 4);
    k = fn_10_9764(0);
    lstrcpy(buf1, "");
    if (k == 3) {
        LoadString(g_9212, 0x24e, buf2, 30);
        lstrcpy(buf1, buf2);
    } else {
        LoadString(g_9212, 0x137, buf2, 30);
        lstrcat(buf2, " ");
        lstrcat(buf1, buf2);
    }
    LoadString(g_9212, k + 0x27f, buf2, 30);
    lstrcat(buf1, buf2);
    lstrcat(buf1, ", ");
    lstrcat(buf1, g_380c);
    lstrcat(buf1, "!");
    fn_10_94c4(0, 6, RGB(0x80, 0xff, 0), g_90ea / 2, g_0010 / 2 - 90, buf1);
    LoadString(g_9212, 0x285, buf1, 30);
    fn_10_94c4(0, 6, RGB(0x80, 0xff, 0), g_90ea / 2, g_0010 / 2 - 55, buf1);
    LoadString(g_9212, 0x3a8, buf2, 30);
    lstrcpy(buf1, buf2);
    fn_15_6558(g_94ac, buf2);
    lstrcat(buf1, buf2);
    fn_10_94c4(0, 6, RGB(0, 0xff, 0), g_90ea / 2, g_0010 / 2, buf1);
}

/* @addr 15:681c */
void far fn_15_681c(HINSTANCE inst, LPSTR buf)
{
    char tmp[20];

    LoadString(inst, 0xa7, tmp, 10);
    lstrcpy(buf, "V0.00.00");
    buf[1] = tmp[0];
    buf[3] = tmp[1];
    buf[4] = tmp[2];
    LoadString(inst, 0xe9, tmp, 10);
    buf[6] = tmp[0];
    buf[7] = tmp[1];
    buf[8] = 0;
}

/* Shows the version line and an 11-line text page from resource 5000
 * [inferred]. */
/* @addr 15:6890 */
void far fn_15_6890(void)
{
    HGDIOBJ oldfont;
    HFONT font;
    char buf[60];
    char ver[10];
    int i;
    int off;
    int k;
    int id;
    COLORREF oldtext;
    COLORREF oldbk;
    HGLOBAL hres;
    DWORD u;
    LPSTR ptr;

    fn_15_681c(g_8e66, ver);
    if (!g_920c)
        LoadString(g_9212, 0x922, buf, 45);
    else
        LoadString(g_9212, 0x921, buf, 45);
    lstrcat(buf, " ");
    lstrcat(buf, ver);
    fn_10_94c4(0, 6, RGB(0x8c, 0, 0xff), g_90ea / 2, g_0010 / 2 - 175, buf);
    font = CreateFont(18, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    oldfont = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, TA_CENTER);
    if (g_90ee < 8)
        oldtext = SetTextColor(g_13dc, RGB(0, 0xff, 0xc8));
    else
        oldtext = SetTextColor(g_13dc, PALETTERGB(0x80, 0x80, 0xff));
    if (g_920c == 0 || g_920c == 1)
        id = 0x88;
    else
        id = 0xc8;
    hres = LoadResource(g_9212, FindResource(g_9212, MAKEINTRESOURCE(id),
                                             MAKEINTRESOURCE(5000)));
    ptr = LockResource(hres);
    for (k = 0; ptr[k]; k++)
        if (ptr[k] == '\r')
            ptr[k] = 0;
    PatBlt(g_13dc, 0, g_0010 / 2 - 115, g_90ea, g_0010 / 2 + 149, BLACKNESS);
    for (i = off = 0; i < g_95d6 * 11; i++)
        off += lstrlen(ptr + off) + 2;
    for (i = 0; i < 11; i++) {
        TextOut(g_13dc, g_90ea / 2, g_0010 / 2 + i * 24 - 115, ptr + off, lstrlen(ptr + off));
        off += lstrlen(ptr + off) + 2;
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
    if (ptr)
        GlobalUnlock(hres);
    if (hres)
        FreeResource(hres);
    LoadString(g_9212, 0x847, buf, 60);
    fn_10_94c4(0, 6, RGB(255, 255, 255), g_90ea / 2, g_0010 / 2 + ++i * 24 - 115, buf);
}

/* @addr 15:6b52 */
void far fn_15_6b52(void)
{
    char buf1[80];
    char buf2[60];
    int i;
    int id1;
    int id2;

    LoadString(g_9212, 0x848, buf1, 80);
    fn_10_94c4(0, 6, RGB(255, 0, 0), g_90ea / 2, g_0010 / 2 - 200, buf1);
    for (i = 0; i < 11; i++) {
        switch (i) {
        case 8:
            id1 = 0x4b9;
            id2 = 0x51d;
            break;
        case 9:
            id1 = 0x4bd;
            id2 = 0x521;
            break;
        case 10:
            id1 = 0x4b7;
            id2 = 0x51b;
            break;
        default:
            id1 = i + 0x4c7;
            id2 = i + 0x52b;
            break;
        }
        LoadString(g_9212, id1, buf1, 60);
        fn_10_94c4(0, 0, RGB(255 - i * 13, 0, i * 12 + 11), g_90ea / 2 - 295,
                   g_0010 / 2 + (i - 5) * 30, buf1);
        lstrcpy(buf1, "- ");
        LoadString(g_9212, id2, buf2, 60);
        lstrcat(buf1, buf2);
        fn_10_94c4(0, 0, RGB(255 - i * 13, 0, i * 12 + 11), g_90ea / 2 - 5,
                   g_0010 / 2 + (i - 5) * 30, buf1);
    }
}

/* @addr 15:7970 */
void far fn_15_7970(int x, int y, LPCSTR s)
{
    int i;
    int off;
    int len;

    len = lstrlen(s);
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            off = -1;
            SetTextColor(g_13dc, RGB(255, 255, 255));
            break;
        case 1:
            off = 1;
            if (!g_11aa)
                SetTextColor(g_13dc, PALETTERGB(0x60, 0x00, 0xc0));
            else if (g_90ee < 8)
                SetTextColor(g_13dc, RGB(0x80, 0, 0));
            else
                SetTextColor(g_13dc, PALETTERGB(0x74, 0x53, 0x19));
            break;
        case 2:
            off = 0;
            if (!g_11aa) {
                if (g_90ee < 8)
                    SetTextColor(g_13dc, RGB(255, 0, 255));
                else
                    SetTextColor(g_13dc, PALETTERGB(0xa0, 0x60, 0xff));
            } else {
                if (g_90ee < 8)
                    SetTextColor(g_13dc, RGB(255, 255, 0));
                else
                    SetTextColor(g_13dc, PALETTERGB(0xd8, 0xbc, 0x56));
            }
            break;
        }
        TextOut(g_13dc, off + x, off + y, s, len);
    }
}

/* Draws one character with a light/dark/colour emboss at the current
 * position and advances it [inferred]. */
/* @addr 15:7a62 */
void far fn_15_7a62(LPCSTR s)
{
    int i;
    int off;
    int u1;
    int ext;
    int x;
    int y;
    DWORD pos;
    int u2;
    int u3;

    pos = GetCurrentPosition(g_13dc);
    x = LOWORD(pos);
    y = HIWORD(pos);
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            off = -1;
            SetTextColor(g_13dc, RGB(255, 255, 255));
            break;
        case 1:
            off = 1;
            SetTextColor(g_13dc, PALETTERGB(0x60, 0x00, 0xc0));
            break;
        case 2:
            off = 0;
            if (g_90ee < 8)
                SetTextColor(g_13dc, RGB(255, 0, 255));
            else
                SetTextColor(g_13dc, PALETTERGB(0xa0, 0x60, 0xff));
            break;
        }
        TextOut(g_13dc, x + off, y + off, s, 1);
    }
    ext = LOWORD(GetTextExtent(g_13dc, s, 1));
    MoveTo(g_13dc, LOWORD(pos) + ext, HIWORD(pos));
}

/* @addr 15:7b34 */
void far fn_15_7b34(void)
{
    g_6e28 = g_1e50 + 90000L;
    fn_10_6e76(8, g_95dc = 0);
    fn_10_6e4c();
    fn_10_0552(0x16, 1);
    fn_10_58ce(0);
    fn_10_754a(0x13, 0, 0, 0);
    g_95d0 = 50;
    g_95d8 = 0;
    g_6e2c = 0;
    fn_15_811a();
}

/* @addr 15:7ba6 */
void far fn_15_7ba6(void)
{
    int a;
    int b;

    if (g_94c4)
        return;
    if (!g_95dc && g_6e28 - 19300 < g_1e50) {
        g_95dc = 1;
        fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2, g_90ec, 0, -2500,
                   32, 32, 25, 150, -1);
        fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2 - 30, g_90ec, 950, -2500,
                   32, 32, 25, 47, 3);
        fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2 + 30, g_90ec, -950, -2500,
                   32, 32, 25, 19, 0);
        g_6e28 = g_1e50 + 7400;
    }
    a = fn_06_73f6();
    b = fn_06_7c14();
    if (g_1e50 - g_6e28 != -500 && a && b) {
        g_6e28 = g_1e50 + 500;
        g_94c4 = 1;
    }
}

/* Demo screen: spinning logo, then the two name lines with sparks
 * [inferred]. */
/* @addr 15:7cda */
void far fn_15_7cda(void)
{
    int i;
    int size;
    int gap;
    int sz;
    POINT p1;
    int y2;
    int u;
    DWORD t;
    int n;

    gap = 4;
    size = 38;
    if (g_8ffc < 800)
        g_95d2 += 6;
    else
        g_95d2 += 3;
    if (g_95d2 >= 89)
        g_95d2 = 0;
    if (g_8ffc < 800)
        g_95d0 += 6;
    else
        g_95d0 += 3;
    if (g_95d0 > 300)
        g_95d0 = 300;
    sz = size * g_95d0 / 200;
    SetStretchBltMode(g_13dc, COLORONCOLOR);
    StretchBlt(g_13dc, g_90ea / 2 - sz / 2, g_0010 / 2 - sz / 2 - 20, sz, sz, g_3a14,
               (gap + size) * (g_95d2 / 10) + gap, gap, size, size, SRCCOPY);
    if (g_95d0 != 300)
        return;
    if (g_130c) {
        if (g_130c < g_1e50) {
            fn_15_811a();
            g_130c = 0;
        }
        return;
    }
    if (!g_6e2c) {
        if (fn_15_8174(g_95dc, g_95da)) {
            if (!g_95dc) {
                fn_15_80da();
                fn_15_8174(g_95dc, -1);
                g_95dc++;
            } else {
                g_6e2c = g_1e50 + 3000;
                fn_15_80da();
                fn_15_8174(g_95dc, -1);
            }
            g_95da = 0;
            return;
        }
        if (g_8ffc > 900 && g_920a > 1)
            g_95da += 2;
        else
            g_95da += 4;
        if (!(g_95da & 1))
            fn_10_754a(0x14, LOWORD(g_3b98), HIWORD(g_3b98), 4);
        return;
    }
    if (g_6e2c >= g_1e50)
        return;
    p1.x = g_90ea / 2;
    p1.y = g_0010 / 2 - 20;
    y2 = g_0010 / 2 - 150;
    if (g_920a == 1)
        n = 1;
    else
        n = 4;
    for (i = 0; i < n; i++) {
        fn_15_80b0(*(long *)&p1, MAKELONG(rand() % 300 + g_90ea / 2 - 150, y2));
        fn_10_754a(0x22, LOWORD(g_3b98), HIWORD(g_3b98), 4);
        t = GetCurrentTime() + 40;
        do
            ;
        while (GetCurrentTime() < t);
    }
    fn_15_80da();
    PatBlt(g_13dc, 0, g_0010 / 2 - 150, g_90ea, 40, BLACKNESS);
    StretchBlt(g_13dc, g_90ea / 2 - sz / 2, g_0010 / 2 - sz / 2 - 20, sz, sz, g_3a14,
               (gap + size) * (g_95d2 / 10) + gap, gap, size, size, SRCCOPY);
    t = GetCurrentTime() + 270;
    do
        ;
    while (GetCurrentTime() < t);
    y2 = g_0010 / 2 + 100;
    for (i = 0; i < n; i++) {
        fn_15_80b0(*(long *)&p1, MAKELONG(rand() % 300 + g_90ea / 2 - 150, y2));
        fn_10_754a(0x22, LOWORD(g_3b98), HIWORD(g_3b98), 4);
        t = GetCurrentTime() + 40;
        do
            ;
        while (GetCurrentTime() < t);
    }
    fn_15_80da();
    PatBlt(g_13dc, 0, g_0010 / 2 + 100, g_90ea, 40, BLACKNESS);
    g_1e50 = GetCurrentTime();
    if (++g_95d8 > 5) {
        g_6e28 = g_1e50 + 4000;
        g_6e2c = g_1e50 + 9000;
    } else
        g_130c = g_1e50 + 1000;
}

/* @addr 15:811a */
void far fn_15_811a(void)
{
    LoadString(g_9212, g_95d8 + 1000, g_87e0, 60);
    LoadString(g_9212, g_95d8 + 980, g_881c, 60);
    g_95dc = 0;
    g_6e2c = 0;
    g_6e28 = g_1e50 + 90000L;
}

/* Draws the first n letters of a name centred on screen, small letters
 * as smaller capitals [inferred]. */
/* @addr 15:8174 */
int far fn_15_8174(int which, int n)
{
    char buf[80];
    char buf2[80];
    int i;
    int dy;
    int w;
    int orig;
    HGDIOBJ old;
    HFONT font1;
    HFONT font2;
    COLORREF oldtext;
    COLORREF oldbk;
    POINT p1;
    POINT p2;
    char ch[2];
    extern int g_1c70;          /* block scope: makes CL load it before n */

    if (g_95d8 > 5)
        return 1;
    orig = n;
    n /= 2;
    if (!which) {
        lstrcpy(buf, g_87e0);
        dy = -150;
    } else {
        lstrcpy(buf, g_881c);
        dy = 100;
    }
    if (orig == -1)
        n = lstrlen(buf);
    else if (lstrlen(buf) < n)
        return 1;
    font1 = CreateFont(28, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    font2 = CreateFont(22, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    if (!n) {
        lstrcpy(buf2, buf);
        MoveTo(g_13dc, -2000, 0);
        SetTextAlign(g_13dc, TA_UPDATECP);
        for (i = g_1c70 = 0; i < lstrlen(buf2); i++) {
            ch[0] = buf2[i];
            ch[1] = 0;
            if (ch[0] < '{' && ch[0] > '`') {
                ch[0] -= 0x20;
                old = SelectObject(g_13dc, font2);
            } else
                old = SelectObject(g_13dc, font1);
            TextOut(g_13dc, 0, 0, ch, 1);
            SelectObject(g_13dc, old);
        }
        g_1c70 = LOWORD(GetCurrentPosition(g_13dc)) + 2000;
    }
    w = g_1c70 * n / lstrlen(buf);
    if (orig != -1) {
        p1.x = g_90ea / 2;
        p1.y = g_0010 / 2 - 20;
        p2.x = g_90ea / 2 - g_1c70 / 2 + w;
        if (orig / 2 != n)
            p2.x += 10;
        p2.y = g_0010 / 2 + dy;
        fn_15_80b0(*(long *)&p1, *(long *)&p2);
    }
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    MoveTo(g_13dc, g_90ea / 2 - g_1c70 / 2, g_0010 / 2 + dy);
    if (g_90ee < 8)
        oldtext = SetTextColor(g_13dc, RGB(0, 0xff, 0xff));
    else
        oldtext = SetTextColor(g_13dc, PALETTERGB(0, 0xa5, 0xff));
    for (i = 0; i < n; i++) {
        ch[0] = buf[i];
        ch[1] = 0;
        if (ch[0] < '{' && ch[0] > '`') {
            ch[0] -= 0x20;
            old = SelectObject(g_13dc, font2);
        } else
            old = SelectObject(g_13dc, font1);
        fn_15_7a62(ch);
        SelectObject(g_13dc, old);
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    if (font1) {
        DeleteObject(font1);
        font1 = 0;
    }
    if (font2) {
        DeleteObject(font2);
        font2 = 0;
    }
    return 0;
}

/* @addr 15:84b0 */
void far fn_15_84b0(int x, int y)
{
    int i;
    HGDIOBJ old;

    if (g_90f4 != 0 || g_92d4 != 7)
        fn_10_754a(0x14, x, y, 4);
    old = SelectObject(g_13dc, GetStockObject(WHITE_PEN));
    for (i = 2; i < 200; i++) {
        MoveTo(g_13dc, x, i / -10 + y);
        LineTo(g_13dc, x, i / 10 + y);
        MoveTo(g_13dc, i / -10 + x, y);
        LineTo(g_13dc, i / 10 + x, y);
    }
    SelectObject(g_13dc, old);
    for (i = 200; i > 0; i--) {
        SetPixel(g_13dc, x, i / -10 + y, 0L);
        SetPixel(g_13dc, x, i / 10 + y, 0L);
        SetPixel(g_13dc, i / -10 + x, y, 0L);
        SetPixel(g_13dc, i / 10 + x, y, 0L);
        PatBlt(g_13dc, x - 1, y - 1, 2, 2, BLACKNESS);
    }
}

/* Step of the demo/attract sequence, state g_95b8 [inferred]. */
/* @addr 15:5962 */
void far fn_15_5962(int a)
{
    int i;
    int k;
    char buf[30];
    char buf2[30];

    switch (g_95b8) {
    case 0:
        flow_interactive = 1;
        fn_15_5e22(a);
        break;
    case 2:
        fn_15_6cdc();
        break;
    case 3:
        fn_15_7cda();
        break;
    case 4:
        if (a)
            fn_15_6890();
        break;
    case 5:
        if (a && g_6e28 != g_1e50)
            fn_15_6b52();
        break;
    case 6:
        fn_15_10be();
        break;
    case 7:
        return;
    }
    if (g_6e28 >= g_1e50)
        return;
    if (g_95b8 == 4 && g_95d6 < 1) {
        g_95d6++;
        if (g_920c == 1 || g_920c == 0)
            g_6e28 = g_1e50 + 27000;
        else
            g_6e28 = g_1e50 + 17000;
        fn_15_6890();
        return;
    }
    fn_10_744c(0x6e);
    PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
    g_95b8++;
    if ((g_95b8 == 2 && g_90f8 && g_8f70) || g_95b8 > 5) {
        flow_interactive = 0;
        g_9134 = 1;
        g_95b8 = 7;
        g_05b4 = GetCurrentTime() + 120000L;
        g_91f8 = 0;
        if (g_90f8) {
            g_95ba = GetPrivateProfileInt(g_9690, "DemoType", 0x207, g_96a9);
            if (g_95ba == 0x207)
                g_95ba = rand() % 4 + 0x208;
            if (g_90f8 && g_95ba == 0x208) {
                GetPrivateProfileString(g_9690, "Ship1", "", buf, 20, g_96a9);
                if (!buf[0]) {
                    fn_14_3eda();
                    fn_14_31d0(0, buf);
                    fn_14_4074();
                    fn_06_92b8();
                }
                if ((k = fn_15_5d14()) != -1) {
                    fn_14_3eda();
                    lstrcpy(buf2, g_6e20[k].name);
                    fn_14_4074();
                }
                if (lstrcmp(buf, buf2) || k == -1) {
                    fn_06_92b8();
                    WritePrivateProfileString(g_9690, "MainShip", buf, g_96a9);
                }
                g_9516 = 0;
            } else
                g_9516 = 1;
        }
        if (!g_9516)
            fn_06_930a();
        fn_06_1d9a();
        fn_06_1c72(1);
        return;
    }
    switch (g_95b8) {
    case 0:
        fn_10_7d58(g_90ea / 2, g_90ec / 2);
        g_6e28 = g_1e50 + 65000;
        g_95cc = 0;
        g_95d0 = 400;
        break;
    case 1:
        if (!g_8f70 || !g_90f8)
            fn_10_7480(0, 1);
        g_6e28 = g_1e50 + 1000;
        break;
    case 2:
        fn_10_4b2e();
        fn_06_7266();
        g_6e28 = g_1e50 + 65000;
        g_95cc = 0;
        fn_10_6e76(8, g_94c4 = 1);
        if (g_0010 < 440)
            g_95de = 40;
        else if (g_0010 < 500)
            g_95de = 30;
        else
            g_95de = 0;
        for (i = g_95d4 = g_95ca = g_95c8 = 0; i < 18; i++)
            g_95e0[i] = 0;
        break;
    case 3:
        fn_15_7b34();
        break;
    case 4:
        fn_10_7d58(g_90ea / 2, g_90ec / 2);
        if (g_920c == 0 || g_920c == 1)
            g_6e28 = g_1e50 + 25000;
        else
            g_6e28 = g_1e50 + 18000;
        g_95d6 = 0;
        fn_15_6890();
        break;
    case 5:
        g_6e28 = g_1e50 + 11000;
        fn_15_6b52();
        break;
    }
}

extern HDC g_39f2;
extern int g_1214;
extern DWORD g_1d3c;
void far fn_06_0a6c(void);

/* Calibration screen (state machine on g_95cc): counter gauge, the
 * spark/laser animation and the final caption [inferred]. */
/* @addr 15:5e22 */
void far fn_15_5e22(int a)
{
    HDC mdc;
    HGDIOBJ oldm;
    HGDIOBJ oldbr;
    HGDIOBJ oldpen;
    int i;
    int r;
    int n;
    int sz;                     /* digit size */
    int m;                      /* digit margin */
    COLORREF color;

    m = 6;
    sz = 40;
    mdc = CreateCompatibleDC(g_13dc);
    oldm = SelectObject(mdc, (HGDIOBJ)g_95f4);
    if (a && g_95cc)
        BitBlt(g_13dc, g_90ea / 2 - 88, g_0010 / 2 - 60, 40, 40, g_39f2, n * 46 + 6, 6, SRCCOPY);  /* sic: n unset */
    switch (g_95cc) {
    case 0: {
        int v;

        if (g_95d2 < 9999)
            n = g_95d2 / 1000;
        else
            n = 0;
        if (g_1212 && g_120e == 0 && g_95d0 && g_95d0 < 160 && n == 5) {
            g_95d0 = g_95d2 = 0;
            fn_10_754a(0x23, 0, 0, 0);
            g_95cc++;
        }
        BitBlt(g_13dc, g_90ea / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2, (sz + m) * n + m,
               m, SRCCOPY);
        g_95d2 += g_95d0;
        if (g_95d2 > 13999) {
            g_95d2 = 0;
            if (g_120e == 0)
                g_95d0 = g_95d0 - 18 < 1 ? 1 : g_95d0 - 18;
        }
        if (g_120e) {
            if (GetCurrentTime() > g_120e + 1000) {
                v = GetPrivateProfileInt(g_9690, "Calibrate", 0, g_96a9);
                if (g_8ffa && v / 2 > g_8ffa && g_1214)
                    g_1214 = g_8ffa = 0;
                if ((g_90f8 || g_90ee < 8) && GetCurrentTime() < g_1d3c + 2000 || !g_8ffa) {
                    g_120e = GetCurrentTime();
                    g_8ffa = 0;
                } else {
                    g_1212 = 1;
                    g_95d0 = 240;
                    g_120e = 0;
                    g_8ffa = (long)g_8ffa * 23 / 10;
                    fn_06_0a6c();
                }
            } else
                g_8ffa++;
        }
        break;
    }
    case 1:
        BitBlt(g_13dc, g_90ea / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2,
               (n = g_95d2 / 1000 + 10) * (m + sz) + m, m, SRCCOPY);
        g_95d2 += 45;
        if (g_95d2 >= 3940) {
            fn_10_754a(0x68, 0, 0, 0);
            g_95d2 = 620;
            g_95cc++;
        }
        break;
    case 2:
        switch (r = rand() % 4) {
        case 0:
            color = RGB(0, 0, 255);
            break;
        case 1:
            color = RGB(0, 255, 255);
            break;
        case 2:
            color = RGB(255, 255, 255);
            break;
        case 3:
            color = RGB(0, 128, 128);
            break;
        }
        oldpen = SelectObject(g_13dc, CreatePen(PS_SOLID, 2, color));
        MoveTo(g_13dc, g_90ea / 2 - 48, g_0010 / 2 - 40);
        LineTo(g_13dc, g_90ea / 2 + g_95d2 / 5 - 38, rand() % 30 + g_0010 / 2 - 55);
        DeleteObject(SelectObject(g_13dc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0))));
        MoveTo(g_13dc, g_90ea / 2 - 48, g_0010 / 2 - 40);
        LineTo(g_13dc, g_90ea / 2 + g_95d2 / 5 - 38, rand() % 30 + g_0010 / 2 - 55);
        DeleteObject(SelectObject(g_13dc, oldpen));
        fn_10_7d58(g_90ea / 2 + g_95d2 / 2 - 38, g_90ec / 2);
        oldbr = SelectObject(g_13dc, GetStockObject(DKGRAY_BRUSH));
        BitBlt(g_13dc, g_95d2 / 5 + g_90ea / 2 - 38, g_0010 / 2 - 56, 2, 32, mdc, g_95d2 / 5, 0,
               MERGECOPY);
        SelectObject(g_13dc, oldbr);
        if ((g_95d2 -= 4) < 0) {
            PatBlt(g_13dc, g_90ea / 2 - 48, g_0010 / 2 - 56, 10, 32, BLACKNESS);
            for (i = 0; i < 630; i += 2) {
                if (i == 100)
                    fn_10_744c(0x6e);
                oldbr = SelectObject(g_13dc, CreateSolidBrush(RGB(i / 5 + 128, i / 5 - 128,
                                                                  i / -5 + 127)));
                BitBlt(g_13dc, g_90ea / 2 - 38, g_0010 / 2 - 56, 130, 32, mdc, 0, 0, MERGECOPY);
                DeleteObject(SelectObject(g_13dc, oldbr));
            }
            g_95cc++;
            g_95d2 = 3940;
            fn_10_744c(0x23);
        }
        break;
    case 3:
        BitBlt(g_13dc, g_90ea / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2,
               (n = g_95d2 / 1000 + 10) * (m + sz) + m, m, SRCCOPY);
        g_95d2 -= 45;
        if (g_95d2 <= 60) {
            BitBlt(g_13dc, g_90ea / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2, m * 6 + sz * 5,
                   m, SRCCOPY);
            g_95cc++;
            g_6e28 = g_1e50 + 3000;
        }
        break;
    case 4: {
        HGDIOBJ oldfont;
        HFONT font;
        char buf[40];
        DWORD oldtc;
        DWORD oldbk;

        fn_10_744c(0x6e);
        font = CreateFont(38, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0x22, "Times New Roman");
        oldfont = SelectObject(g_13dc, font);
        oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
        SetBkMode(g_13dc, TRANSPARENT);
        SetTextAlign(g_13dc, TA_CENTER);
        oldtc = SetTextColor(g_13dc, RGB(255, 255, 0));
        LoadString(g_9212, 0x846, buf, 40);
        TextOut(g_13dc, g_90ea / 2, g_0010 / 2 + 17, buf, lstrlen(buf));
        SetBkColor(g_13dc, oldbk);
        SetTextColor(g_13dc, oldtc);
        SelectObject(g_13dc, oldfont);
        if (font) {
            DeleteObject(font);
            font = 0;
        }
        break;
    }
    }
    SelectObject(mdc, oldm);
    DeleteDC(mdc);
}

/* Title screen: logo lines, version and CD/demo status, the logo bitmap
 * dissolving in, then the title scrolling and the end fireworks [inferred]. */
/* @addr 15:6cdc */
void far fn_15_6cdc(void)
{
    int u1;                     /* u1-u6 never used: frame layout */
    int u2;
    int u3;
    int u4;
    int u5;
    int v;                      /* fade level, stored but never read */
    int flag;
    int u6;
    int k;
    int pix;
    int ok;
    char mask;
    int bit;
    int idx;
    HGDIOBJ oldfont;
    HFONT font;
    char buf[90];
    char buf2[140];
    COLORREF textcol;
    COLORREF bkcol;

    switch (g_95cc) {
    case 0:
        if (g_95d4 == 0) {
            fn_10_6ea0(5);
            font = CreateFont(24, 11, 0, 0, 600, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(g_13dc, font);
            bkcol = SetBkColor(g_13dc, 0L);
            SetBkMode(g_13dc, TRANSPARENT);
            SetTextAlign(g_13dc, TA_CENTER);
            if (g_90ee < 8)
                textcol = SetTextColor(g_13dc, RGB(0, 0xff, 0xff));
            else
                textcol = SetTextColor(g_13dc, PALETTERGB(0, 0xa5, 0xff));
            LoadString(g_9212, 0x849, buf, 90);
            fn_15_7970(g_90ea / 2 - 90, g_0010 / 2 + g_95de - 245, buf);
            SelectObject(g_13dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(35, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(g_13dc, font);
            if (g_920c == 0)
                LoadString(g_9212, 0x922, buf, 45);
            else
                LoadString(g_9212, 0x921, buf, 45);
            fn_11_3fd4(buf, 0);
            lstrcat(buf, "\x99");
            fn_15_7970(g_90ea / 2, g_0010 / 2 + g_95de - 220, buf);
            SelectObject(g_13dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(g_13dc, font);
            if (g_11aa == 0) {
                if (g_920c == 3)
                    lstrcpy(buf, "");
                else
                    fn_09_955c(0x923, buf);
            } else
                fn_09_955c(0x924, buf);
            lstrcat(buf, " - ");
            fn_15_681c(g_8e66, buf2);
            lstrcat(buf, buf2);
            lstrcat(buf, " ");
            LoadString(g_8e66, 0x25f, buf2, 20);
            lstrcat(buf, buf2);
            SetTextColor(g_13dc, PALETTERGB(0xc0, 0xc0, 0xc0));
            fn_15_7970(g_90ea / 2, g_0010 / 2 + g_95de - 186, buf);
            fn_10_885e(0);
            flag = 0;
            SetTextColor(g_13dc, PALETTERGB(0xc0, 0xc0, 0xc0));
            if (g_920c != 3) {
                if (g_920c == -1) {
                    GetProfileString(g_9690, "CDDrive", "", buf, 40);
                    if (buf[0] == 0) {
                        fn_09_955c(0x84c, buf2);
                        fn_10_946a(buf);
                        lstrcat(buf2, buf);
                    } else {
                        lstrcpy(buf2, "CD: ");
                        lstrcat(buf2, buf);
                    }
                } else if (g_920c == 2) {
                    int n;

                    n = -g_9224;
                    fn_09_955c(0x926, buf);
                    wsprintf(buf2, buf, n);
                } else {
                    int n;

                    if (g_922a)
                        fn_09_955c(0x927, buf2);
                    else {
                        if (g_9224 < 0) {
                            n = -g_9224;
                            fn_09_955c(0x926, buf);
                        } else {
                            lstrcpy(buf, "");
                            n = g_9224;
                            fn_09_955c(0x925, buf);
                        }
                        wsprintf(buf2, buf, n);
                    }
                    flag = 1;
                }
                fn_15_7970(g_90ea / 2, g_0010 / 2 + g_95ce + 125, buf2);
            }
            if (flag) {
                SetTextColor(g_13dc, 0L);
                SetBkColor(g_13dc, PALETTERGB(0xb4, 0x80, 0xe0));
                SetBkMode(g_13dc, OPAQUE);
                if (g_922a)
                    fn_09_955c(0x928, buf2);
                else
                    fn_09_955c(0x906, buf2);
                TextOut(g_13dc, g_90ea / 2, g_0010 / 2 + g_95ce + 150, buf2, lstrlen(buf2));
                SetBkColor(g_13dc, 0L);
                SetBkMode(g_13dc, TRANSPARENT);
            }
            SelectObject(g_13dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(16, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(g_13dc, font);
            if (g_90ee != 8) {
                SetTextColor(g_13dc, 0L);
                SetBkColor(g_13dc, PALETTERGB(0xc0, 0xc0, 0xc0));
                SetBkMode(g_13dc, OPAQUE);
                lstrcpy(buf2, " For best results, change Windows to 256 color mode ");
                TextOut(g_13dc, g_90ea / 2, g_0010 / 2 + g_95ce + 86, buf2, lstrlen(buf2));
                SetBkColor(g_13dc, 0L);
                SetBkMode(g_13dc, TRANSPARENT);
            }
            SetTextColor(g_13dc, PALETTERGB(0xb4, 0x80, 0xe0));
            lstrcpy(buf, "\xa9 1994-2000 Software Dynamics, inc. All rights reserved.");
            TextOut(g_13dc, g_90ea / 2, g_0010 / 2 + g_95ce + 103, buf, lstrlen(buf));
            SelectObject(g_13dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(30, 0, 0, 0, 800, 1, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(g_13dc, font);
            SetTextColor(g_13dc, PALETTERGB(0xb4, 0x80, 0xe0));
            fn_09_955c(0x9ee, buf2);
            fn_15_7970(g_90ea / 2, g_0010 / 2 + g_95ce + 185, buf2);
            SetBkColor(g_13dc, bkcol);
            SetTextColor(g_13dc, textcol);
            SelectObject(g_13dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            g_95be = fn_10_6c02(300, 0, -1);
            g_95c2 = CreateCompatibleDC(g_13dc);
            g_95c0 = SelectObject(g_95c2, g_95be);
            if (g_920e)
                g_95c4 = SelectPalette(g_95c2, g_920e, 0);
            SetStretchBltMode(g_13dc, 3);
            fn_10_9962(1, g_13dc, g_90ea / 2 - 138, g_0010 / 2 + g_95de - 155, 276, 210,
                       g_95c2, 0, 0, 138, 105, SRCCOPY);
            if (g_920e)
                SelectPalette(g_95c2, g_95c4, 0);
            SelectObject(g_95c2, g_95c0);
            DeleteObject(g_95be);
            for (k = 0; k < 18; k++)
                g_95e0[k] = 0;
            if (g_90f0 == 0 && (g_8fe8 == 0 || g_8ffa < 800)) {
                HDC mdc;
                HBITMAP bmp;
                HGDIOBJ oldbmp;
                HPALETTE oldpal;

                bmp = fn_10_6c02(300, 3, -1);
                mdc = CreateCompatibleDC(g_13dc);
                oldbmp = SelectObject(mdc, bmp);
                if (g_920e)
                    oldpal = SelectPalette(mdc, g_920e, 0);
                g_95be = CreateCompatibleBitmap(g_13dc, 276, 276);
                g_95c0 = SelectObject(g_95c2, g_95be);
                if (g_920e)
                    g_95c4 = SelectPalette(g_95c2, g_920e, 0);
                SetStretchBltMode(g_95c2, 3);
                fn_10_9962(1, g_95c2, 0, 0, 276, 276, mdc, 0, 0, 138, 138, SRCCOPY);
                if (g_920e)
                    SelectPalette(mdc, oldpal, 0);
                SelectObject(mdc, oldbmp);
                DeleteObject(bmp);
                DeleteDC(mdc);
            } else {
                g_95be = fn_10_73a6(300, "", -2, -2, 2, 0, 1, 1, 12);
                g_95c0 = SelectObject(g_95c2, g_95be);
                if (g_920e)
                    g_95c4 = SelectPalette(g_95c2, g_920e, 0);
            }
        }
        g_6e2c = 0;
        g_95c6 = g_90ea / 2 - 400;
        ok = g_95dc = 0;
        while (!ok) {
            pix = rand() % 105;
            idx = pix >> 3;
            bit = pix & 7;
            mask = 1 << bit;
            ok = !(g_95e0[idx] & mask);
        }
        g_95e0[idx] |= mask;
        g_95d4++;
        BitBlt(g_13dc, g_90ea / 2 - 138, g_0010 / 2 + pix * 2 + g_95de - 155, 276, 2,
               g_95c2, 0, pix * 2, SRCCOPY);
        if (g_95d4 >= 105) {
            if (g_95c4)
                SelectPalette(g_95c2, g_95c4, 0);
            SelectObject(g_95c2, g_95c0);
            DeleteObject(g_95be);
            DeleteDC(g_95c2);
            g_95c2 = 0;
            for (k = 0; k < 18; k++)
                g_95e0[k] = 0;
            g_95cc++;
            g_95d4 = 0;
            g_95ca = g_95c8 = 0;
        }
        break;
    case 1:
        g_95cc++;
        g_95ce = g_95c8 = 0;
        break;
    case 2:
        g_95cc++;
        g_95ca = g_95c8 = 0;
        break;
    case 3:
        fn_10_7d58(g_95c6 += 5, g_90ec / 2);
        if (g_95ca > 190)
            v = min(g_95c8 - 190, 255);
        else
            v = max((24 - g_95c8) * 10, 0);
        g_95c8 += 2;
        g_95ca += 2;
        if (g_95ca >= 230) {
            g_95cc++;
            g_95ca = g_95c8 = 0;
        }
        break;
    case 4:
        fn_10_7d58(g_95c6 += 5, g_90ec / 2);
        g_95c8 += 4;
        g_95ce += 2;
        if (g_95ce >= 40) {
            g_6e2c = g_1e50 + 45000;
            g_6e28 = g_6e2c + 6500;
            g_95cc = 5;
            g_95ca = g_95c8 = 0;
        }
        break;
    }
    if (g_6e2c && g_6e2c < g_1e50) {
        g_94c4 = 0;
        fn_06_7266();
        fn_06_72d8(2, 3);
        fn_10_744c(0x6e);
        fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2 - 210, g_90ec, 0, -2500,
                   32, 32, 25, 178, -1);
        fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2 + 210, g_90ec, 0, -2500,
                   32, 32, 25, 165, -1);
        g_6e2c = 0;
    }
    if (g_94c4 == 0) {
        int a;
        int b;

        a = fn_06_73f6();
        b = fn_06_7c14();
        if (b && !g_95dc) {
            g_95dc = 1;
            PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
            g_1c6c = g_1e50 + 100;
            g_6e28 = g_1e50 + 2500;
        }
        if (g_6e28 - 800 > g_1e50 && g_1c6c + 100 < g_1e50 && g_95dc && rand() % 10 < 3) {
            fn_06_78ea(rand() % 2 * 10, rand() % 300 + g_90ea / 2 - 150,
                       rand() % 440 + g_90ec / 2 - 220, 0, 0, 800, 4, 50 - rand() % 10);
            g_1c6c = g_1e50;
        }
        if (g_6e28 - 200 < g_1e50)
            g_94c4 = 1;
    }
}


/* Draws the bevelled frame of the picture panel g_3ca8 [inferred]. */
/* @addr 15:8604 */
void far fn_15_8604(void)
{
    HBITMAP bmp;
    HGDIOBJ oldbmp;
    HDC dc;
    HGDIOBJ old;
    HPALETTE pal;

    g_92d2 = g_3ca8.bottom - g_3ca8.top - 15;
    FillRect(g_929a, &g_3ca8, GetStockObject(LTGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 25, g_3ca8.top + 25, g_3ca8.right - 25,
            g_3ca8.top + g_92d2 - 25);
    SetRect(&g_6084, g_3ca8.left + 25, g_3ca8.top + 25, g_3ca8.right - 25,
            g_3ca8.top + g_92d2 - 25);
    FillRect(g_929a, &g_6e30, GetStockObject(BLACK_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 20, g_3ca8.top + 20, g_3ca8.right - 20, g_3ca8.top + 25);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 20, g_3ca8.top + g_92d2 - 25, g_3ca8.right - 20,
            g_3ca8.top + g_92d2 - 20);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.right - 25, g_3ca8.top + 20, g_3ca8.right - 20,
            g_3ca8.top + g_92d2 - 20);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 20, g_3ca8.top + 20, g_3ca8.left + 25,
            g_3ca8.top + g_92d2 - 20);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left, g_3ca8.top, g_3ca8.right, g_3ca8.top + 2);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.left, g_3ca8.top, g_3ca8.left + 2, g_3ca8.bottom);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.right - 2, g_3ca8.top, g_3ca8.right, g_3ca8.bottom);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left, g_3ca8.bottom - 2, g_3ca8.right, g_3ca8.bottom);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    old = SelectObject(g_929a, GetStockObject(WHITE_PEN));
    MoveTo(g_929a, g_3ca8.left, g_3ca8.top + g_92d2 - 5);
    LineTo(g_929a, g_3ca8.right - 1, g_3ca8.top + g_92d2 - 5);
    SelectObject(g_929a, old);
    bmp = fn_10_6c02(0x122, 0, -1);
    dc = CreateCompatibleDC(g_13dc);
    if (g_920e)
        pal = SelectPalette(dc, g_920e, 0);
    oldbmp = SelectObject(dc, bmp);
    BitBlt(g_929a, g_3ca8.left + 20, g_3ca8.top + g_92d2 - 17, 44, 10, dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldbmp);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(bmp);
    SelectObject(g_929a, CreatePen(PS_SOLID, 1, RGB(0, 0xff, 0)));
    MoveTo(g_929a, g_3ca8.right - 19, g_3ca8.top + g_92d2 - 5);
    LineTo(g_929a, g_3ca8.right - 38, g_3ca8.top + g_92d2 - 5);
    DeleteObject(SelectObject(g_929a, old));
    old = SelectObject(g_929a, GetStockObject(WHITE_PEN));
    MoveTo(g_929a, g_3ca8.right - 20, g_3ca8.bottom - 16);
    LineTo(g_929a, g_3ca8.right - 20, g_3ca8.bottom - 6);
    LineTo(g_929a, g_3ca8.right - 35, g_3ca8.bottom - 6);
    SelectObject(g_929a, CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80)));   /* leaked */
    LineTo(g_929a, g_3ca8.right - 35, g_3ca8.bottom - 16);
    LineTo(g_929a, g_3ca8.right - 20, g_3ca8.bottom - 16);
    DeleteObject(SelectObject(g_929a, old));
    bmp = fn_10_6d38("CORNER");
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, bmp);
    BitBlt(g_929a, g_3ca8.left + 20, g_3ca8.top + g_92d2 - 25, 5, 5, dc, 0, 0, SRCCOPY);
    BitBlt(g_929a, g_3ca8.right - 26, g_3ca8.top + 20, 5, 5, dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
    DeleteObject(bmp);
}

/* Draws a panel with frames, a label bitmap and three lamps in g_3cb8
 * [inferred]. */
/* @addr 15:8ae6 */
void far fn_15_8ae6(void)
{
    HBITMAP bmp;
    HGDIOBJ oldbmp;
    HDC dc;
    int u;
    HGDIOBJ oldbr;
    HPALETTE pal;
    int w;
    int h;

    w = g_3cb8.right - g_3cb8.left;
    h = g_3cb8.bottom - g_3cb8.top;
    fn_10_949c(g_929a, g_3cb8.left, g_3cb8.top, w, h, 2);
    fn_10_949c(g_929a, w / 16 + g_3cb8.left, w / 16 + g_3cb8.top, w * 7 / 8, h - w / 8, 3);
    fn_10_949c(g_929a, w / 8 + g_3cb8.left, h * 5 / 8 + g_3cb8.top + 1, w * 3 / 4,
               h * 3 / 8 - w / 8, 1);
    fn_10_949c(g_929a, w / 8 + g_3cb8.left, h / 2 + g_3cb8.top, w * 3 / 4, h / 8, 1);
    bmp = fn_10_6c02(0x122, 0, -1);
    dc = CreateCompatibleDC(g_13dc);
    if (g_920e)
        pal = SelectPalette(dc, g_920e, 0);
    oldbmp = SelectObject(dc, bmp);
    BitBlt(g_929a, w / 8 + g_3cb8.left + 2, h * 5 / 8 + g_3cb8.top + 3, min(w * 3 / 4, 44), 10,
           dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldbmp);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(bmp);
    oldbr = SelectObject(g_929a, CreateSolidBrush(PALETTERGB(0, 0xff, 0)));
    PatBlt(g_929a, w * 3 / 8 + g_3cb8.left - 2, h * 17 / 32 + g_3cb8.top, 5, 3, PATCOPY);
    DeleteObject(SelectObject(g_929a, oldbr));
    oldbr = SelectObject(g_929a, CreateSolidBrush(PALETTERGB(0x7f, 0xff, 0)));
    PatBlt(g_929a, w * 4 / 8 + g_3cb8.left - 2, h * 17 / 32 + g_3cb8.top, 5, 3, PATCOPY);
    DeleteObject(SelectObject(g_929a, oldbr));
    oldbr = SelectObject(g_929a, CreateSolidBrush(PALETTERGB(0x7f, 0, 0)));
    PatBlt(g_929a, w * 5 / 8 + g_3cb8.left - 2, h * 17 / 32 + g_3cb8.top, 5, 3, PATCOPY);
    DeleteObject(SelectObject(g_929a, oldbr));
}
