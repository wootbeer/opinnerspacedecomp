/* INSPACE.EXE segment 13 (selector 1060), first source file (13:0000-68ff).
 * Functions from 13:6900 on were a separate source file (they call
 * 2688/2714/4eec far, and are called far): see seg13b.c. */
#include "inspace.h"
#include <stdlib.h>

extern int g_131a;                 /* debug output on when nonzero */

/* BEGIN STRUCTS */
typedef void (far *FNPTR)(int, int);  /* REC70 handler [inferred] */
#pragma pack(1)
/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record. Generated layout; keep in sync between seg13.c/seg14.c. */
typedef struct {
    char pad_000[0x4];
    int f_004;    /* DS:7096 */
    int f_006;    /* DS:7098 */
    char pad_008[0x6];
    int f_00e;    /* DS:70a0 */
    char pad_010[0x14];
    int f_024;    /* DS:70b6 */
    int f_026;    /* DS:70b8 */
    int f_028;    /* DS:70ba */
    char pad_02a[0x6];
    int f_030;    /* DS:70c2 */
    int f_032;    /* DS:70c4 */
    char pad_034[0x2];
    int f_036;    /* DS:70c8 */
    char pad_038[0x2];
    int f_03a;    /* DS:70cc */
    int f_03c;    /* DS:70ce */
    int f_03e;    /* DS:70d0 */
    char pad_040[0xc];
    int f_04c;    /* DS:70de */
    char pad_04e[0x2];
    int f_050;    /* DS:70e2 */
    int f_052;    /* DS:70e4 */
    int f_054;    /* DS:70e6 */
    int f_056;    /* DS:70e8 */
    char pad_058[0x3];
    char f_05b;    /* DS:70ed */
    char f_05c;    /* DS:70ee */
    char pad_05d[0x3];
    int f_060[16];    /* DS:70f2 */
    int f_080;    /* DS:7112 */
    char pad_082[0x10];
    long f_092;    /* DS:7124 */
    unsigned long f_096;    /* DS:7128 */
    unsigned long f_09a;    /* DS:712c */
    char pad_09e[0x4];
    long f_0a2;    /* DS:7134 */
    char pad_0a6[0x4];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    char pad_0ac[0x20];
    int f_0cc;    /* DS:715e */
    char pad_0ce[0x6];
    int f_0d4;    /* DS:7166 */
    char pad_0d6[0x4];
    int f_0da;    /* DS:716c */
    char pad_0dc[0xd];
    char f_0e9;    /* DS:717b */
    char f_0ea;    /* DS:717c */
    char f_0eb;    /* DS:717d */
    char pad_0ec[0x8];
    char f_0f4[9][9];    /* DS:7186 */
    char pad_145[0x1];
    char f_146;    /* DS:71d8 */
    char f_147;    /* DS:71d9 */
    char pad_148[0xc];
    unsigned long f_154;    /* DS:71e6 */
    char pad_158[0x2];
} OBJ15A;

/* 0x70-byte records reached through far pointers (DS:1e30, DS:1df8[]). */
typedef struct {
    char pad_000[0x4];
    POINT f_004;
    char pad_008[0x4];
    int f_00c;
    int f_00e;
    char pad_010[0x8];
    int f_018;
    int f_01a;
    char pad_01c[0x2];
    int f_01e;
    char pad_020[0x6];
    int f_026;
    char pad_028[0x1e];
    int f_046;
    char pad_048[0x1e];
    FNPTR f_066;
    char pad_06a[0x6];
} REC70;

/* 0x41-byte records through the far pointer at DS:6e20 [inferred]. */
typedef struct {
    char pad_000[0x1];
    char f_001;
    char f_002;
    char f_003;
    char pad_004[0x2];
    char f_006;
    char pad_007[0x2];
    char f_009;
    char f_00a[23];
    int f_021;
    char pad_023[0x1e];
} REC41;

/* 0x2c-byte records through the far pointer at DS:6e1c [inferred]. */
typedef struct {
    char pad_000[0x1b];
    char f_01b;
    char f_01c;
    char f_01d;
    char pad_01e[0x2];
    char f_020;
    int f_021;
    char pad_023[0x9];
} REC2C;

/* 0xad-byte records at DS:970a [inferred base]. */
typedef struct {
    int f_000;
    char pad_002[0xab];
} RECAD;
#pragma pack()
/* END STRUCTS */
extern OBJ15A g_7092[];

/* 0x1e-byte records at DS:6e3e [inferred base], three of them (one per
 * child window [inferred], see fn_13_59e8). */
typedef struct {
    int f_00;                       /* DS:6e3e */
    long f_02;                      /* DS:6e40: colour */
    char pad_06[0x0a - 0x06];
    int f_0a;                       /* DS:6e48 */
    int f_0c;                       /* DS:6e4a */
    char pad_0e[0x10 - 0x0e];
    int f_10;                       /* DS:6e4e */
    int f_12;                       /* DS:6e50 */
    int f_14;                       /* DS:6e52 */
    int f_16;                       /* DS:6e54 */
    char pad_18[0x1e - 0x18];
} REC1E;
extern REC1E g_6e3e[];

extern RECAD g_970a[];

/* 0x1e-byte records at DS:6f98, eight of them [inferred: smart-window
 * entries, see fn_13_638a]. */
typedef struct {
    int f_00;                       /* DS:6f98 */
    int f_02;
    int f_04;
    int f_06;
    char pad_08[0x1e - 0x08];
} REC1E2;
extern REC1E2 g_6f98[];
extern int g_131e[];
extern int g_1dec;
extern int g_1dee;
extern int g_95fa;
extern int g_9320;
extern char g_8630[];               /* run-time buffer (BSS) */
extern int g_058c;
extern int g_8680[];
extern char g_a152;
extern char g_a163;

extern int g_3824[][8];
extern REC70 far *g_1e30;
extern REC70 far *g_1df8[];

extern long g_1e50;
extern HWND g_0a7c;
extern int g_8f72;
extern int g_8f74;
extern int g_131c;
extern REC70 far *g_1e24;
extern int g_9302;
extern int g_2390;
extern int g_2392;

/* 0x34-byte records at DS:8564 [inferred base]. */
typedef struct {
    int f_00;
    char pad_02[0x34 - 0x02];
} REC34;
extern REC34 g_8564[];
extern int g_1ddc;
extern int g_1dde;
extern int g_1de0;
extern int g_9134;
extern int g_0a76;
extern int g_9316;
extern int g_92e8;
extern int g_9324;
extern int g_6e8e;
extern int g_6e90;
extern HINSTANCE g_8e66;
extern int g_238c;
extern int g_951a;
extern int g_9646;
extern int g_8f68;
extern int g_940a;
extern int g_6e8a;
extern int g_6e8c;
extern REC70 far *g_1e00;

/* 0x24-byte records at DS:52ec [inferred base] (as in seg13b.c). */
typedef struct {
    int f_00;                       /* DS:52ec */
    int f_02;
    char pad_04[0x0a - 0x04];
    int f_0a;                       /* DS:52f6 */
    char pad_0c[0x12 - 0x0c];
    int f_12;                       /* DS:52fe */
    char pad_14[0x18 - 0x14];
    int f_18;                       /* DS:5304 */
    int f_1a;
    int f_1c;
    int f_1e;
    char pad_20[0x24 - 0x20];
} REC24;
extern REC24 g_52ec[];
extern int g_8fea;
extern char g_8694[];               /* run-time buffer (BSS) */
extern char g_86d0[];               /* run-time buffer (BSS) */

/* Functions of this file (called near). */
void far fn_13_4eca(LPCSTR text);
int far fn_13_371c(int a, int b);
void far fn_13_4eec(int i, int d);
int far fn_13_2688(int i, int j);
void far fn_13_498e(int a, int b);
void far fn_13_4ba0(int a, int i, int b);
void far fn_13_50b0(HDC hdc, int b);
void far fn_13_57ac(void);
void far fn_13_5850(void);
void far fn_13_58dc(HDC hdc, int b);
void far fn_13_5a6a(HDC hdc, int x, int y, int s, int k, int w, int b, int c);
void far fn_13_6362(void);
void far fn_13_6450(int a, int b, int c);
void far fn_13_6890(int i);

void far fn_07_1208(void);
void far fn_03_045a(int a);
void far fn_07_63f2(void);
void far fn_07_2080(int a, int b);
void far fn_07_64ac(int a, int b, int c);
int far fn_03_0000(int a, int b);
void far fn_03_06ec(int, int, int, int);
void far fn_03_1d0a(int a, int b, int c);
void far fn_06_0f1a(int v, char far *buf);
int far pascal fn_08_285a(int far *py, int far *px, POINT a, POINT b);
int far pascal fn_08_19b0(int dy, int dx);
void far fn_03_1542(int a, int b, int c, char far *buf, int d);
void far fn_11_3fd4(char far *s, int n);
void far fn_17_8e60(int a, char far *buf);

/* @addr 13:4eca */
void far fn_13_4eca(LPCSTR text)
{
    if (g_131a)
        OutputDebugString(text);
}

/* @addr 13:2da4 */
void far fn_13_2da4(void)
{
    char buf[110];
}

/* @addr 13:2db8 */
void far fn_13_2db8(void)
{
    char buf[110];
}

/* @addr 13:5850 */
void far fn_13_5850(void)
{
    if (g_95fc) {
        DestroyWindow(g_95fc);
        g_95fc = 0;
    }
}

/* @addr 13:6362 */
void far fn_13_6362(void)
{
    if (g_95fe) {
        DestroyWindow(g_95fe);
        g_95fe = 0;
    }
}

/* @addr 13:371c */
int far fn_13_371c(int a, int b)
{
    int unused;

    if (a != 12)
        return 0;
    if (!(b & 1))
        return 1;
    return 2;
}

/* @addr 13:6716 */
void far fn_13_6716(int i)
{
    if (i == g_9646 && !g_951a && !g_238c)
        fn_07_1208();
    else
        g_7092[i].f_154 = g_1e50 - 1;
}

/* @addr 13:4eec */
void far fn_13_4eec(int i, int d)
{
    if (d > 0)
        g_7092[i].f_080 += (long)(1000 - g_7092[i].f_080) * d / 1000;
    else
        g_7092[i].f_080 = (long)(g_7092[i].f_080 + d) * 1000 / (d + 1000);
}

/* @addr 13:5878 */
void far fn_13_5878(void)
{
    if (g_0a7c && !g_95fc)
        CreateWindow("IS_WATCH", "Ship - Pilot", 0x10cc0000L,
                     g_1ddc, g_1dde, g_1de0 - g_1ddc,
                     GetSystemMetrics(SM_CYCAPTION) + 0x36,
                     g_0016, 0, g_8e66, NULL);
    SetActiveWindow(g_0016);
}

/* @addr 13:100c */
int far pascal fn_13_100c(int i, int v)
{
    if (g_7092[i].f_0e9 != 0)
        return v;
    if (g_7092[i].f_00e > 0 && g_7092[i].f_00e < 7)
        return v;
    v += g_1df8[g_9324][i].f_026;
    if (v >= 16)
        v = 0;
    else if (v <= 0)
        v = 15;
    return v;
}

/* @addr 13:5460 */
void far fn_13_5460(HDC hdc, int a, int k, int j, int i, int shift)
{
    int x, y;

    if (a == 0 && g_238c == 0 && g_1df8[j][i].f_00c == 0
        && g_1df8[j][i].f_00e == 0)
        return;
    if (g_6e3e[k].f_00) {
        x = (g_6e3e[k].f_0a + g_6e3e[k].f_10) >> shift;
        y = (g_6e3e[k].f_0c + g_6e3e[k].f_12) >> shift;
        SetPixel(hdc, x, y, 0L);
        g_6e3e[k].f_00 = 0;
    }
}

/* @addr 13:218a */
void far fn_13_218a(int n, LPSTR out)
{
    char key[40];
    char buf[40];

    LoadString(g_9212, 0xaf, key, 40);
    key[4] = 0;
    fn_06_0f1a(n + 1, buf);
    lstrcat(key, buf);
    LoadString(g_9212, 0xaf, buf, 40);
    GetPrivateProfileString(buf, key, "", out, 20, g_96a9);
}

/* @addr 13:59e8 */
int far fn_13_59e8(int k, int i)
{
    int w;

    if (k == 0 && g_9458)
        return 1;
    if (k == g_9324 && g_95fe)
        return 1;
    for (w = 0; w < 3; w++) {
        if ((w == 0 && g_0a76 == 2) || (w == 1 && g_0a76 == 3)
            || (w == 2 && g_95fc)) {
            if (g_6e3e[w].f_16 == k && g_6e3e[w].f_14 == i)
                return 1;
        }
    }
    return 0;
}

/* Attitude of object i towards object j [inferred]: relation table plus
 * class-vs-class table, adjusted by i's temperament bytes.
 * near-match 44%: 13:2688 (the game loads f_060[j] before indexing
 * g_3824; CL keeps evaluating g_3824 first) */
int far fn_13_2688(int i, int j)
{
    int a, b, u;
    int r;

    a = g_970a[g_7092[i].f_04c].f_000;
    b = g_970a[g_7092[j].f_04c].f_000;
    r = g_7092[i].f_060[j] + g_3824[a][b];
    if (r > 0)
        r += (3 - g_7092[i].f_05b) * 20;
    else
        r += (g_7092[i].f_05c - 3) * 20;
    if (g_92e8)
        return -300;
    return r;
}

/* @addr 13:2dcc */
void far fn_13_2dcc(void)
{
    int i;
    int r;

    for (i = 0; i <= g_9316; i++) {
        if (i == g_9646)
            r = 500;
        else
            r = fn_13_2688(i, g_9646);
        if (r < -80)
            g_1df8[g_9324][i].f_046 = 5;
        else if (r < 80)
            g_1df8[g_9324][i].f_046 = 4;
        else
            g_1df8[g_9324][i].f_046 = 7;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_13_6450(int a, int b, int c)
{
}

/* @addr 13:675e */
void far fn_13_675e(void)
{
    int i;

    for (i = 0; i <= g_9316; i++) {
        if (g_131c || g_7092[i].f_154 + 10000 < g_1e50) {
            if ((g_7092[i].f_154 < g_1e50 && i != g_9646)
                || g_1df8[g_9324][i].f_018 != 0) {
                g_7092[i].f_154 = g_1e50 + 5000;
                fn_13_6890(i);
            }
        }
    }
    fn_13_50b0(0, 0);
    if (g_6e3e[g_0a76 - 2].f_16 != g_9324)
        fn_13_58dc(0, 0);
    fn_07_64ac(0, 0, -1);
    if (!g_95fe && g_9316 && g_8f74) {
        i = 0;
        g_95fa = 0;
        for (; i <= g_9316; i++)
            if (i != g_9646 && fn_03_0000(g_9324, i))
                g_95fa++;
        if (g_95fa)
            PostMessage(g_0016, 0x9b4, 0, 0L);
    }
}

/* Window procedure of the pilot window, class "IS_WATCH" [inferred]. */
/* @addr 13:4f4e */
LRESULT far pascal fn_13_4f4e(HWND hwnd, UINT msg, WPARAM wParam,
                              LPARAM lParam)
{
    RECT r;
    RECT rc;
    PAINTSTRUCT ps;
    HDC hdc;
    MINMAXINFO far *mm;

    switch (msg) {
    case WM_CREATE:
        g_95fc = hwnd;
        fn_13_57ac();
        break;
    case WM_SETFOCUS:
        g_8f68 = 1;
        break;
    case WM_MOVE:
        GetWindowRect(g_95fc, &r);
        if (r.left != g_1ddc || r.top != g_1dde) {
            CopyRect((LPRECT)&g_1ddc, &r);
            g_8fea = 1;
        }
        SetActiveWindow(g_0016);
        break;
    case WM_GETMINMAXINFO:
        mm = (MINMAXINFO far *)lParam;
        mm->ptMinTrackSize.x = 0x36;
        ((MINMAXINFO far *)lParam)->ptMinTrackSize.y
            = GetSystemMetrics(SM_CYCAPTION) + 0x36;
        ((MINMAXINFO far *)lParam)->ptMaxTrackSize.y
            = GetSystemMetrics(SM_CYCAPTION) + 0x36;
        break;
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        PatBlt(hdc, 0, 0, rc.right, rc.bottom, BLACKNESS);
        lstrcpy(g_8694, "");
        lstrcpy(g_86d0, "");
        fn_13_50b0(hdc, 1);
        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        if (g_95fc) {
            DestroyWindow(g_95fc);
            g_95fc = 0;
        }
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0L;
}

/* Open or refresh the pilot window on the player's target [inferred]. */
/* @addr 13:563c */
int far command_watch_ship(int a, int b)
{
    char buf[80];
    char title[100];
    int i, s, k;

    if (!g_95fc && !a && !b) {
        g_6e90 = g_9324;
        g_6e8e = 0;
        g_6e8a = 2;
        g_6e8c = 2;
    }
    if (a && !b && g_95fc) {
        fn_13_5850();
        return 0;
    }
    s = g_7092[g_9646].f_03c;
    k = g_7092[g_9646].f_03e;
    if (!b)
        goto skip;
    if (s != 2) {
        for (i = 0; i < g_940a; i++) {
            if (g_52ec[i].f_18 == g_9324 && g_52ec[i].f_1a == g_9646
                && g_1e00[i].f_018 == 0) {
                s = 2;
                k = i;
                break;
            }
        }
    }
skip:
    if (a || b || !g_95fc) {
        if (a && b) {
            s = g_9324;
            k = g_9646;
        }
        a = 0;
        if (s == g_9324 || s == 2) {
            g_6e90 = s;
            g_6e8e = k;
            a = 1;
        }
    }
    if (!a) {
        fn_03_045a(6);
        if (g_6e90 != g_9324 && g_6e90 != 2)
            return 0;
    }
    if (!g_95fc) {
        PostMessage(g_0016, 0x9a0, 0, 0L);
    } else {
        PostMessage(g_95fc, WM_PAINT, 0, 0L);
        fn_13_57ac();
    }
    return 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_13_50b0(HDC hdc, int b)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_13_5a6a(HDC hdc, int x, int y, int s, int k, int w, int b, int c)
{
}

/* Redraw the map child window [inferred: g_0a7c, modes 2/3 in g_0a76]. */
/* @addr 13:58dc */
void far fn_13_58dc(HDC hdc, int b)
{
    int u1, k, s, w, got, u2;
    HPALETTE pal;

    if (!g_0a7c)
        return;
    if (g_0a76 != 2 && g_0a76 != 3)
        return;
    if (g_9320 == 6 && g_0a76 == 2)
        return;
    w = g_0a76 - 2;
    s = g_6e3e[w].f_16;
    k = g_6e3e[w].f_14;
    if (s != 7 && s != 12 && !fn_03_0000(s, k)) {
        if (g_0a76 == 3) {
            g_0a76 = 2;
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        }
        return;
    }
    got = 0;
    if (hdc == 0) {
        got = 1;
        hdc = GetDC(g_0a7c);
    }
    if (g_920e)
        pal = SelectPalette(hdc, g_920e, 0);
    fn_13_5a6a(hdc, g_6e3e[w].f_10, g_6e3e[w].f_12, s, k, w, b, 0);
    if (pal)
        SelectPalette(hdc, pal, 0);
    if (got) {
        ReleaseDC(g_0a7c, hdc);
        hdc = 0;
    }
}

/* @addr 13:6890 */
void far fn_13_6890(int i)
{
    if (g_95fe && i != g_9646)
        fn_13_6450(0, 2, i);
    if (g_95fc && g_6e90 == g_9324 && g_6e8e == i)
        fn_13_50b0(0, 2);
    if (g_6e3e[g_0a76 - 2].f_16 == g_9324 && g_6e3e[g_0a76 - 2].f_14 == i)
        fn_13_58dc(0, 2);
}

/* @addr 13:3678 */
void far fn_13_3678(int i)
{
    int e;
    int d;
    int y;
    int x;

    d = fn_08_285a(&y, &x, g_1df8[g_9324][i].f_004,
                   g_1df8[g_7092[i].f_030][g_7092[i].f_032].f_004);
    e = fn_08_19b0(y, x);
    if (d > 90) {
        if ((e > 10 && e < 14) || (e > 2 && e < 6)) {
            if (fn_13_371c(g_7092[i].f_030, g_7092[i].f_032) == 2)
                g_7092[i].f_032--;
        }
    }
}

/* Set the pilot window's title [inferred]. */
/* @addr 13:57ac */
void far fn_13_57ac(void)
{
    char buf[80];
    char title[100];

    fn_03_1542(0, g_6e90, g_6e8e, buf, 0);
    fn_11_3fd4(buf, 2);
    lstrcpy(title, buf);
    if (g_9324 == g_6e90) {
        lstrcat(title, " - ");
        fn_17_8e60(g_6e8e, buf);
        fn_11_3fd4(buf, 2);
        lstrcat(title, buf);
    }
    SetWindowText(g_95fc, title);
}

/* @addr 13:638a */
void far fn_13_638a(void)
{
    int i;

    if (g_0a7c && !g_95fe) {
        i = 0;
        g_95fa = 0;
        for (; i <= g_9316; i++)
            if (i != g_9646 && fn_03_0000(g_9324, i))
                g_95fa++;
        if (!g_95fa)
            return;
        for (i = 0; i < 8; i++) {
            g_6f98[i].f_06 = g_9324;
            g_6f98[i].f_04 = i;
            g_6f98[i].f_00 = 2;
            g_6f98[i].f_02 = i * 0x2e + 2;
        }
        CreateWindow("IS_SMART", "", 0x10cc0000L, g_1dec, g_1dee, 50, 150,
                     g_0016, 0, g_8e66, NULL);
    }
    SetActiveWindow(g_0016);
}

/* @addr 13:2e60 */
void far pascal fn_13_2e60(int p, int q, int t)
{
    int u;

    if (t == -1)
        t = 9;
    if (q != g_9646) {
        fn_13_4eec(p, g_131e[t] * 5);
        fn_13_4eec(q, g_131e[t] * 5);
    } else {
        fn_13_4eec(p, g_131e[t] * 12);
        fn_13_4eec(q, g_131e[t] * 12);
    }
    if (t == 9)
        return;
    if (t == 2 || t == 3) {
        if (g_970a[g_7092[q].f_04c].f_000 == g_970a[g_7092[p].f_04c].f_000)
            return;
        if (fn_13_2688(p, q) > 70)
            return;
    }
    g_7092[p].f_0f4[q][t] += (char)g_131e[t];
}

/* @addr 13:3302 */
void far fn_13_3302(void)
{
    int i, u;

    if (g_9320 == 6)
        return;
    for (i = 0; i <= g_9316; i++) {
        if (g_7092[i].f_036 == 2 && g_7092[i].f_146 == g_7092[i].f_030
            && g_7092[i].f_147 == g_7092[i].f_032)
            continue;
        if (g_7092[g_9646].f_036 != 1
            && g_7092[i].f_146 == g_7092[g_9646].f_030
            && g_7092[i].f_147 == g_7092[g_9646].f_032 && i != g_9646
            && (fn_13_2688(i, g_9646) > 0
                || g_970a[g_7092[i].f_04c].f_000
                   == g_970a[g_7092[g_9646].f_04c].f_000))
            fn_03_06ec(g_9646, 14, i, 0xb8);
        g_7092[i].f_146 = g_7092[i].f_147 = -1;
    }
}

/* @addr 13:2f30 */
void far pascal fn_13_2f30(int i)
{
    int u1, u2, flag;
    char buf[162];
    char buf2[218];

    flag = 1;
    if (i != g_9646)
        return;
    if (g_7092[i].f_004 < 0) {
        g_7092[i].f_004 = 0;
        return;
    }
    lstrcpy(buf, g_8630);
    if (g_1df8[g_9324][i].f_01a != 0 || i == g_9646)
        fn_03_1d0a(100, i, (i != g_9646 || g_9134) ? 1 : 0);
    if (lstrcmp(buf, g_8630)) {
        g_058c = 1;
        fn_13_4eca(g_8630);
        lstrcpy(buf, "\n\r");
        fn_13_4eca(buf);
    }
}

/* near-match 78%: 13:498e (the game lays out the last loop with its test
 * at the top; CL puts it at the bottom here) */
void far fn_13_498e(int a, int b)
{
    int i, best, bi, sel, found;

    found = 0;
    for (i = 0; i < g_9302; i++) {
        if (g_1e24[i].f_018 != 0) {
            fn_13_4ba0(a, i, b);
            sel = i;
            found = 1;
            break;
        }
    }
    if (!found) {
        best = 0;
        for (i = 0; i < g_9302; i++) {
            if (g_8564[i].f_00 > best) {
                best = g_8564[i].f_00;
                bi = i;
            }
        }
        g_1e24[bi].f_066(11, bi);
        fn_13_4ba0(a, bi, b);
        sel = bi;
        fn_07_2080(11, -1);
    }
    if (b) {
        for (i = 0; i <= g_9316; i++) {
            if (g_7092[i].f_0ea
                && ((g_970a[g_7092[i].f_04c].f_000 == 7 && g_7092[i].f_05c > 1)
                    || g_970a[g_7092[i].f_04c].f_000 == 3)) {
                g_7092[i].f_050 = 0;
                g_7092[i].f_004 = g_7092[i].f_030 = 11;
                g_7092[i].f_032 = g_7092[i].f_006 = sel;
                g_7092[i].f_03a = g_7092[i].f_036 = 2;
            }
        }
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_13_4ba0(int a, int i, int b)
{
}

/* @addr 13:4ac4 */
void far fn_13_4ac4(int a)
{
    int j;

    fn_13_498e(a, 0);
    for (j = 0; j <= g_9316; j++) {
        if (g_1e30[j].f_018 == 0 && j != a && g_7092[j].f_036 == 1
            && g_7092[j].f_030 == 14 && g_7092[j].f_032 == a) {
            if (g_7092[j].f_0d4 == -1) {
            g_8680[a] = j;
            g_7092[j].f_050 = 0x16;
            g_7092[j].f_052 = 14;
            g_7092[j].f_054 = a;
            g_7092[j].f_096 = g_1e50 + 50000;
            g_7092[j].f_0eb = 1;
            g_7092[j].f_092 = g_1e50 + 500;
            if (a == g_9646) {
                g_a163 = 5;
                g_a152++;
            }
            return;
            } else {
            g_8680[a] = j;
            g_7092[a].f_036 = 2;
            g_7092[a].f_030 = 11;
            g_7092[a].f_032 = 0;
            }
        }
    }
}

/* Show/hide the game's child windows [inferred]. */
/* @addr 13:65f2 */
int far fn_13_65f2(int cmd)
{
    int r;

    r = 1;
    switch (cmd) {
    case 3:
        if (g_95fc)
            ShowWindow(g_95fc, SW_HIDE);
        if (g_9458)
            ShowWindow(g_9458, SW_HIDE);
        if (g_95fe)
            ShowWindow(g_95fe, SW_HIDE);
        break;
    case 2:
        if (g_95fc)
            ShowWindow(g_95fc, SW_SHOW);
        if (g_9458)
            ShowWindow(g_9458, SW_SHOW);
        if (g_95fe)
            ShowWindow(g_95fe, SW_SHOW);
        if (g_95fc || g_9458 || g_95fe)
            SetActiveWindow(g_0016);
        break;
    case 1:
        fn_13_5850();
        fn_07_63f2();
        fn_13_6362();
        break;
    case 0:
        r = 0;
        if (g_8f72 && !g_9458) {
            PostMessage(g_0016, 0x9aa, 0, 0L);
            r = 1;
        }
        if (g_8f74 && !g_95fe) {
            PostMessage(g_0016, 0x9b4, 0, 0L);
            r = 1;
        }
        break;
    }
    return r;
}

/* @addr 13:54da */
void far fn_13_54da(HDC hdc, int a, int k, int j, int i, int shift)
{
    int y, x;

    if (a == 0 && g_238c == 0 && g_1df8[j][i].f_00c == 0
        && g_1df8[j][i].f_00e == 0)
        return;
    if (a == 0) {
        g_6e3e[k].f_0a -= g_1df8[j][i].f_00c >> 2;
        g_6e3e[k].f_0c -= g_1df8[j][i].f_00e >> 2;
        if (g_238c) {
            g_6e3e[k].f_0a += g_2390 >> 2;
            g_6e3e[k].f_0c += g_2392 >> 2;
        }
        if (g_6e3e[k].f_0a < 0) {
            g_6e3e[k].f_0a = 43;
            g_6e3e[k].f_0c = rand() % 43;
            g_6e3e[k].f_02 = 0xffff00L;
        } else if (g_6e3e[k].f_0a > 43) {
            g_6e3e[k].f_0a = 0;
            g_6e3e[k].f_0c = rand() % 43;
            g_6e3e[k].f_02 = 0xffff00L;
        }
        if (g_6e3e[k].f_0c < 0) {
            g_6e3e[k].f_0c = 43;
            g_6e3e[k].f_0a = rand() % 43;
            g_6e3e[k].f_02 = 0xffff00L;
        } else if (g_6e3e[k].f_0c > 43) {
            g_6e3e[k].f_0c = 0;
            g_6e3e[k].f_0a = rand() % 43;
            g_6e3e[k].f_02 = 0xffff00L;
        }
    }
    x = (g_6e3e[k].f_0a + g_6e3e[k].f_10) >> shift;
    y = (g_6e3e[k].f_0c + g_6e3e[k].f_12) >> shift;
    if (GetPixel(hdc, x, y) == 0) {
        SetPixel(hdc, x, y, g_6e3e[k].f_02);
        g_6e3e[k].f_00 = 1;
    } else {
        g_6e3e[k].f_00 = 0;
    }
}
