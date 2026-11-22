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
extern DWORD g_6e28;
extern long g_6e2c;
extern DWORD g_1e50;

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

/* @addr 15:811a */
void far fn_15_811a(void)
{
    LoadString(g_9212, g_95d8 + 1000, g_87e0, 60);
    LoadString(g_9212, g_95d8 + 980, g_881c, 60);
    g_95dc = 0;
    g_6e2c = 0;
    g_6e28 = g_1e50 + 90000L;
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

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_15_5962(int a)
{
    g_95b8 = a;
}
