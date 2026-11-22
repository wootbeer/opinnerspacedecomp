/* INSPACE.EXE segment 11 (selector 1050). */
#include "inspace.h"

/* 0x15a-byte records at DS:7090, indexed by g_9646 (same layout as
 * seg04.c's REC_15A) [inferred]. */
typedef struct {
    char p000[0x18];
    int f18;                    /* +18 */
    char p01a[0x84 - 0x1a];
    unsigned long f84;          /* +84 */
    char p088[0xb8 - 0x88];
    char fb8[0x13];             /* +b8 */
    char fcb;                   /* +cb */
    char p0cc[0xe2 - 0xcc];
    char fe2;                   /* +e2 */
    char p0e3[0x15a - 0xe3];
} REC_15A;
extern REC_15A g_7090[];

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. */
typedef struct {
    char p00[4];
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    char p08[0x4c - 8];
    COLORREF f4c;               /* +4c */
    char f50;                   /* +50 */
    char p51[0x70 - 0x51];
} REC_70;
extern REC_70 far *g_1df8[16];

/* 0x1e-byte records at DS:6e3c [inferred]. */
typedef struct {
    int  w00;                   /* +0x00 */
    char pad02[0x1c];
} REC1E;
extern REC1E g_6e3c[];

extern int g_001a;
extern HWND g_0a7a;
extern HWND g_0a7c;
extern HWND g_0a7e;
extern int g_13de;
extern int g_500a;
extern int g_8e62;
extern int g_8ff4;
extern int g_90f4;
extern int g_9130;                  /* subgame_active */
extern int g_9208;
extern int g_92e4;
extern int g_93aa;
extern int g_93d6;
extern int g_93de;
extern int g_9462;
extern char g_94e4[22];
extern char g_94fa[22];
extern int g_9646;
extern int g_968e;

extern int g_0a62;
extern int g_0a76;
extern char g_1018[5][5];
extern int g_103e;
extern int g_1042;
extern int g_1044;
extern int g_1046;
extern unsigned long g_1e50;
extern int g_1852;
extern HBITMAP g_5040;
extern int g_6e52;
extern int g_6e54;
extern int g_9134;
extern int g_93a6;
extern int g_952c;

/* inspace.h declares g_1e4c as long; here it is used as a far pointer. */
#define g_1e4c_ptr (*(unsigned far **)&g_1e4c)

extern int g_0a72;
extern int g_0a74;
extern char g_93e0[];               /* run-time buffer (BSS) */
extern int g_9318;
extern int g_9322;
extern int g_9324;
extern int g_93c6;
extern HDC g_93ce;
extern HDC g_93d0;
extern int g_94a8;
extern int g_9524;
extern char g_9eb9[];
extern char g_9ebc[];

extern long g_0a64;
extern long g_0a68;
extern long g_0a6c;
extern int g_90ee;
extern HFONT g_90fe;
extern long g_501c;
extern long g_5020;
extern RECT g_5048;
extern int g_5050;
extern int g_5052;

long far pascal fn_11_1ab6(long x);
long far pascal fn_11_1b44(long y);
void far fn_18_0d4e(int msg, int wparam, long lparam);
HBITMAP far world_map(int w, int h, int a, int b, int c, int d, int e);
void far fn_06_0f1a(int v, LPSTR buf);
void far fn_02_088e(void);
int far fn_03_065e(int a, int b, int c);
void far fn_03_045a(int a);
void far fn_16_638a(int a, int b, int c, int d);
void far fn_16_614c(int msg, int wparam, long lparam);
int far fn_10_6b54(void);
void far fn_06_1c72(int a);
void far fn_09_0d6c(void);
void far fn_06_626c(void);

/* Not yet decompiled: stubs so calls to them compile as near calls. */
void far fn_11_04ea(void) { }
void far fn_11_05fe(int a) { }
void far fn_11_0978(void) { }
void far fn_11_1ef6(int a) { }
void far fn_11_2ce6(HDC dc, int a) { }
void far fn_11_33cc(void) { }
HBITMAP far fn_11_2ff6(int a) { return 0; }
void far pascal fn_11_4e0a(int a) { }
void far fn_11_7588(int a) { }
void far fn_11_7650(int a, int b) { }
void far fn_11_238e(HWND hwnd, HDC dc) { }
void far fn_11_41bc(HDC dc, int a, int b) { }
void far fn_11_7902(int msg, int wparam, long lparam) { }
void far pascal fn_11_6b64(int msg, int wparam, long lparam) { }

/* @addr 11:2120 */
int far fn_11_2120(void)
{
    if (g_500a == 0 || g_9130 != 0 || g_90f4 != 1 && g_90f4 != 7)
        return 0;
    return 1;
}

/* @addr 11:72b2 */
void far fn_11_72b2(void)
{
    if (g_7090[g_9646].fe2 == 0 && fn_10_6b54() == 0xa7)
        g_8ff4 = 0;
}

/* @addr 11:3396 */
void far fn_11_3396(void)
{
    if (++g_93de >= ((8 - g_9208) * 16 >> 6) * g_93d6) {
        g_93de = 0;
        fn_11_33cc();
    }
}

/* @addr 11:ae94 */
void far fn_11_ae94(void)
{
    if (g_92e4 == 0) {
        if (g_7090[g_9646].fcb > 1)
            g_7090[g_9646].f18 = 1;
        else
            g_7090[g_9646].f18 = 0;
    }
}

/* @addr 11:7b7a */
void far fn_11_7b7a(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1)
                    fn_06_1c72(1);
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:78bc */
void far fn_11_78bc(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 0) {
                    g_13de = 1;
                    g_968e = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:7b30 */
void far fn_11_7b30(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 4) {
                    fn_09_0d6c();
                    fn_06_626c();
                    g_001a = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:7bbc */
void far fn_11_7bbc(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1 && g_90f4 != 7)
                    g_93aa = 0x12;
                break;
            case 0x20:
                g_9462 = -1;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:b306 */
int far fn_11_b306(int c)
{
    int i;

    if (g_94fa[0] != 'Y') {
        for (i = 1; i < 0x16; i++)
            if (g_94fa[i] == c)
                return g_94e4[i];
    }
    return c;
}

/* @addr 11:04a0 */
void far fn_11_04a0(int a)
{
    if (fn_11_2120()) {
        switch (a) {
        case 0:
            fn_11_04ea();
            break;
        case 1:
            fn_11_05fe(0);
            break;
        case 6:
            fn_11_0978();
            break;
        case 7:
            fn_11_1ef6(0);
            break;
        }
    }
}

/* @addr 11:02f0 */
void far fn_11_02f0(void)
{
    if (g_0a7a) {
        DestroyWindow(g_0a7a);
        g_0a7a = 0;
    }
    if (g_0a7c) {
        DestroyWindow(g_0a7c);
        g_0a7c = 0;
    }
    if (g_0a7e) {
        DestroyWindow(g_0a7e);
        g_0a7e = 0;
    }
}

/* @addr 11:3ed8 */
void far fn_11_3ed8(int i)
{
    HDC dc;
    HWND hwnd;

    g_6e3c[i].w00 = g_6e3c[i].w00 == 0;
    if (i == 2)
        hwnd = g_95fc;
    else
        hwnd = g_0a7c;
    fn_11_2ce6(dc = GetDC(hwnd), i);
    ReleaseDC(hwnd, dc);
}

/* @addr 11:4db0 */
void far fn_11_4db0(void)
{
    if (g_9134 == 0 && g_7090[g_9646].f84 < g_1e50) {
        if (GetAsyncKeyState(0x10) & 0x8000 || GetAsyncKeyState(0x20) & 0x8000
            || g_1042)
            fn_11_4e0a(g_9646);
    }
}

/* @addr 11:785e */
void far fn_11_785e(int msg, int key, long lparam)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_93a6 == 0)
                    fn_16_638a(0, 0, 0, 1);
                break;
            }
            break;
        }
        if (g_952c)
            fn_16_614c(msg, key, lparam);
        g_8e62 = 0;
    }
}

/* @addr 11:170a */
int far fn_11_170a(int reset)
{
    int r;

    if (reset)
        g_1852 = -1;
    if (++g_1852 > 6)
        g_1852 = 0;
    switch (g_1852) {
    case 0:
    case 4:
        r = 0;
        break;
    case 2:
    case 5:
        r = 2;
        break;
    case 1:
    case 3:
    case 6:
        r = 1;
        break;
    }
    return r;
}

/* @addr 11:2f8c */
void far fn_11_2f8c(void)
{
    int unused;

    if (g_5040) {
        DeleteObject(g_5040);
        g_5040 = 0;
    }
    if (g_7090[g_9646].f18)
        g_5040 = fn_11_2ff6(g_7090[g_9646].fb8[g_7090[g_9646].f18]);
    if (g_0a7e)
        PostMessage(g_0a7e, WM_PAINT, 0, 0L);
}

/* @addr 11:3e6e */
void far fn_11_3e6e(void)
{
    HDC dc;
    RECT rc;

    if (g_0a76 != 4) {
        dc = GetDC(g_0a7c);
        GetClientRect(g_0a7c, &rc);
        PatBlt(dc, 0, 0, rc.right, rc.bottom, WHITENESS);
        ReleaseDC(g_0a7c, dc);
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    }
}

/* @addr 11:772e */
void far fn_11_772e(int a, int b)
{
    g_0a62 = 1;
    if (g_0a76 != 2) {
        g_0a76 = 2;
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        if (fn_03_065e(g_6e54, g_6e52, b) == 0)
            goto done;
        return;
    } else if (a) {
        g_6e54 = 3;
        g_6e52 = 0;
    }
done:
    fn_03_045a(b);
}

/* @addr 11:7504 */
void far fn_11_7504(void)
{
    unsigned a, b;
    int i;
    unsigned x, y;
    int v;

    if (g_8ff4) {
        g_103e = 0;
        g_1042 = 0;
        g_1044 = 0;
        g_1046 = 0;
        for (i = 0; i < 4; i++)
            fn_11_7588(i);
        a = g_1e4c_ptr[0];
        b = g_1e4c_ptr[1];
        x = a / 0x3444 > 4 ? 4 : a / 0x3444;
        y = b / 0x3444 > 4 ? 4 : b / 0x3444;
        v = g_1018[y][x];
        fn_11_7650(v, 1);
    }
}

/* @addr 11:22fa */
LONG far pascal fn_11_22fa(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    PAINTSTRUCT ps;
    HDC dc;
    int id;

    switch (msg) {
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        dc = BeginPaint(hwnd, &ps);
        fn_11_238e(hwnd, dc);
        EndPaint(hwnd, &ps);
        break;
    case WM_LBUTTONDBLCLK:
        id = GetDlgCtrlID(hwnd);
        if (id == 0xd2)
            g_93c6 = 1;
        else
            g_93c6 = 0;
        fn_02_088e();
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0L;
}

/* @addr 11:488c */
void far race_radar_background(int a)
{
    int i;

    world_map(g_0a72, g_0a74, a, g_9322, -1, -1, 1);
    if (g_94a8 == 0) {
        for (i = 0; i < g_9ebc[g_9322]; i++)
            world_map(g_0a72, g_0a74, a, g_9322, 8,
                      g_9eb9[g_9322] + g_9318 * 2 + i, 0);
    }
    BitBlt(g_93ce, 0, 0, g_0a72, g_0a74, g_93d0, 0, 0, SRCCOPY);
}

/* @addr 11:adf0 */
void far fn_11_adf0(void)
{
    int old;
    int unused;

    old = g_9524 = g_7090[g_9646].f18;
    if (g_7090[g_9646].fcb > 1) {
        g_9524++;
        if (g_7090[g_9646].fb8[g_9524] == 0)
            g_9524++;
        if (g_7090[g_9646].fcb <= g_9524) {
            if (g_9134)
                g_9524 = 0;
            else
                g_9524 = 1;
        }
        g_7090[g_9646].f18 = g_9524;
    } else
        g_7090[g_9646].f18 = 0;
    if (g_7090[g_9646].fb8[old] == 3)
        g_1df8[g_9324][g_9646].f50 = 0;
}

/* @addr 11:3f2e */
void far fn_11_3f2e(int v)
{
    char buf[8];

    if (v < -250)
        LoadString(g_9212, 0x244, g_93e0, 40);
    else if (v < -80)
        LoadString(g_9212, 0x245, g_93e0, 40);
    else if (v < 80)
        LoadString(g_9212, 0x246, g_93e0, 40);
    else if (v < 250)
        LoadString(g_9212, 0x247, g_93e0, 40);
    else
        LoadString(g_9212, 0x248, g_93e0, 40);
    if (v > 0)
        lstrcat(g_93e0, " +");
    else
        lstrcat(g_93e0, " ");
    fn_06_0f1a(v / 10, buf);
    lstrcat(g_93e0, buf);
}

/* @addr 11:4108 */
void far lap_timer(void)
{
    HDC dc;
    HFONT oldfont;
    COLORREF oldtext;
    COLORREF oldbk;

    dc = GetDC(g_0a7c);
    oldfont = SelectObject(dc, g_90fe);
    SetTextAlign(dc, 0);
    if (g_90ee == 1)
        oldtext = SetTextColor(dc, 0xffffffL);
    else
        oldtext = SetTextColor(dc, 0xff00L);
    oldbk = SetBkColor(dc, 0L);
    fn_11_41bc(dc, 0, g_0a76 == 2 ? 1 : 0);
    SetBkColor(dc, oldbk);
    SetTextColor(dc, oldtext);
    SelectObject(dc, oldfont);
    ReleaseDC(g_0a7c, dc);
}

/* @addr 11:6aa8 */
void far pascal fn_11_6aa8(int msg, int wparam, long lparam)
{
    if (g_8e62) {
        if (g_9130)
            fn_18_0d4e(msg, wparam, lparam);
        else {
            if (msg == 0x101 || msg == 0x100)
                wparam = fn_11_b306(wparam);
            switch (g_90f4) {
            case 0:
                fn_11_7902(msg, wparam, lparam);
                break;
            case 1:
                fn_11_6b64(msg, wparam, lparam);
                break;
            case 3:
                fn_11_7bbc(msg, wparam, lparam);
                break;
            case 2:
                fn_11_7b7a(msg, wparam, lparam);
                break;
            case 6:
                fn_11_785e(msg, wparam, lparam);
                break;
            }
        }
        g_8e62 = 0;
    }
}

/* @addr 11:3914 */
void far pascal fn_11_3914(int type, int n, HDC dc)
{
    POINT pt;

    pt.x = fn_11_1ab6(g_1df8[type][n].f04) * g_0a6c * g_0a64 / g_501c + g_5050;
    pt.y = fn_11_1b44(g_1df8[type][n].f06) * g_0a6c * g_0a68 / g_5020 + g_5052;
    if (PtInRect(&g_5048, pt))
        SetPixel(dc, pt.x, pt.y, g_1df8[type][n].f4c);
}
