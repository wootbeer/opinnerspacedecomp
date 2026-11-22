/* INSPACE.EXE segment 10 (selector 1048). */
#include "inspace.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

extern int g_90f4;
extern int g_9228;
extern int g_9210;
extern int g_921e;
extern long g_90ea;

typedef int (far pascal *FP7I)(int, int, int, int, int, int, int);
extern int  (far pascal *g_fp_3c34)(int, int, long, int, int, int, int, int, int, char, char);
extern int  (far pascal *g_fp_3c44)(int, int, int, int, int, int, int, int, int);
extern int  (far pascal *g_fp_3c48)(int, int, int, int, int, int, int, int, int, int, long);
extern int  (far pascal *g_fp_3c58)(POINT, int, int, long);
extern int  (far pascal *g_fp_3c68)(char far *, char far *, int);


void far fn_10_6ee6(int a, int b, char far *s, int c, int d, int e, int f,
                    int g, int h, int i, int j, int k, int l);
extern int g_9300;
extern int g_39ee;
extern HGDIOBJ g_3c60[2];
extern int g_9156;
extern int g_0592;
extern int g_8ffa;
extern int g_8ffc;
extern DWORD g_1e50;
extern DWORD g_3b94;
extern void (far pascal *g_fp_3c64)(int, int, int, int, int, int, int);
void far fn_06_0b3e(void);
void far fn_10_7480(int a, int b);
void far fn_10_7f88(void);
extern HDC g_39e8[];
extern HPALETTE g_3a5c[];
extern HBITMAP g_3974[];
extern HBITMAP g_3ad0[];
extern int g_11aa;
typedef struct {
    HDC dc1;            /* +0x00 */
    HDC dc2;            /* +0x02 */
    HBITMAP bm1;        /* +0x04 */
    HBITMAP bm2;        /* +0x06 */
    HBITMAP old1;       /* +0x08 */
    HBITMAP old2;       /* +0x0a */
    HPALETTE pal;       /* +0x0c */
    char rest[0x14];
} SURF_22;              /* 34-byte records at DS:9168 [inferred: off-screen surfaces] */
extern SURF_22 g_9168[];
typedef struct {
    char list[0x13];    /* +0x00 */
    char cnt;           /* +0x13 */
    char pad[0x20];
    char flag;          /* +0x34 */
    char rest[0x15a - 0x35];
} REC_15A;
extern REC_15A g_7148[];
extern int g_92fe;
extern int g_9316;
typedef struct {
    int id;
    char rest[0x32];
} REC_34;
extern REC_34 g_3d5a[];
extern int g_9416;
extern char g_07de[];
extern int (far pascal *g_fp_3c28)(int, int, char far *, int, int, int);
extern int g_92ec;
#pragma pack(1)
typedef struct {
    int f00;            /* +0x00 */
    int f02;            /* +0x02 */
    char p04[0x26];
    int f2a;            /* +0x2a */
    char rest[0xad - 0x2c];
} REC_AD;               /* 173-byte records at DS:96d2 */
#pragma pack()
extern REC_AD g_96d2[];
extern POINT g_7b60[][64];
extern POINT g_7ba0[][64];
int far fn_06_720c(int a);
int far fn_06_71b2(int a);
typedef struct {
    int f00;
    int f02;
    int f04;
    int f06;
    int f08;
    int f0a;
    int f0c;
    int f0e;
    char rest[0x24 - 0x10];
} REC_24;
extern REC_24 g_52f4[];
typedef struct {
    char p00[4];
    long f04;
    char p08[0x10];
    int f18;
    char rest[0x70 - 0x1a];
} REC_70;
extern REC_70 far *g_1e00;
extern int g_92f0;
extern int g_3b9c[];
typedef struct {
    int f00;
    char rest[0x15a - 2];
} REC_15A_B;
extern REC_15A_B g_7094[];
extern int g_9646;
extern int subgame_active;          /* DS:9130 */
extern int g_9324;
extern REC_70 far *g_1df8[];
extern int g_9158;
extern RECT g_23e0[];
int far pascal fn_08_285a(int far *q, int far *p, POINT pt, long a);
int far fn_10_7032(int a, int b, int c);
void far fn_10_9a2a(int d);
extern int g_92e2;
extern int g_103c;
extern int g_9220;
extern int music_pause_state;       /* DS:9222 */
extern char g_07e0[];
extern int g_073e;
extern DWORD g_2384;
extern int g_920c;
void far fn_06_0f1a(int n, char far *buf);
void far fn_10_6308(int a, int b, int c, int d);
extern void (far pascal *g_fp_3c74)(int, int, long, int, long, int, int, long);
extern void (far pascal *g_fp_3c78)(int, int, long, int, int, long, int, long,
                                    int, int, int, long, int);
extern int (far pascal *g_fp_3c30)(int, int, long, int, int, int, int, int,
                                    int, int, char, char, char, int);
extern void (far pascal *g_fp_3c6c)(long, long, long, long, long, long, long,
                                    long, long, long, long, long);
extern void (far pascal *g_fp_3c38)(int, int, long, int, int, int, int, char,
                                    char, int, int, char, char);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_10_80dc(void);
int far fn_10_82a2(int a);
void far fn_10_81b6(void);
void far fn_15_5932(void);
void far fn_10_022e(int a);
extern struct stat g_922e;
extern struct stat g_924c;
extern struct stat g_926a;
extern char g_8f7a[];
extern int g_0742;

/* @addr 10:6d38 */
int far fn_10_6d38(LPCSTR s)
{
    return g_fp_3c2c(s);
}

/* @addr 10:6e26 */
void far fn_10_6e26(void)
{
    g_fp_3c50(g_920e, 0, 0, 0, 0L, 2);
}

/* @addr 10:6ec6 */
void far fn_10_6ec6(int a)
{
    g_fp_3c40(g_920e, a, g_13dc);
}

/* @addr 10:6b54 */
void far fn_10_6b54(void)
{
    g_fp_3c84(0, g_1e4c);
}

/* @addr 10:7db8 */
void far fn_10_7db8(void)
{
    g_fp_3c54(g_05a0, 2);
}

/* @addr 10:8686 */
void far fn_10_8686(void)
{
    g_8e5c = 0;
    g_fp_3c54(g_05a0, 3);
}

/* @addr 10:86ca */
void far fn_10_86ca(void)
{
    int r;

    r = 0;
    g_fp_3c4c();
}

/* @addr 10:86a8 */
void far fn_10_86a8(void)
{
    g_8e5c = 1;
    g_fp_3c54(g_05a0, 4);
}

/* @addr 10:6e00 */
void far fn_10_6e00(void)
{
    g_920e = g_fp_3c50(0, 0, 0, 0, 0L, 0);
}

/* @addr 10:6ea0 */
void far fn_10_6ea0(unsigned a)
{
    g_fp_3c50(g_920e, 0, 0, 0, a, 7);
}

/* @addr 10:6e4c */
void far fn_10_6e4c(void)
{
    g_fp_3c50(g_920e, g_0016, g_13dc, 0, 0L, 3);
}

/* @addr 10:6e76 */
void far fn_10_6e76(long a)
{
    g_fp_3c50(g_920e, 0, 0, 0, a, 1);
    fn_10_6e4c();
}

void far fn_10_4672(int a, int b);

/* @addr 10:464a */
void far fn_10_464a(void)
{
    g_928a = fn_10_6d38("DEF");
    fn_10_4672(0, 3);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_4672(int a, int b)
{
    g_928a = a + b;
}

/* @addr 10:5c1a */
void far fn_10_5c1a(void)
{
    if (g_9288) {
        DeleteDC(g_9288);
        g_9288 = 0;
    }
}

/* @addr 10:6d52 */
void far fn_10_6d52(int a, int b, int c, int d, int e, int f)
{
    g_fp_3c80(a, b, c, d, e, f);
}

/* @addr 10:949c */
void far fn_10_949c(int a, int b, int c, int d, int e, int f)
{
    g_fp_3c70(a, b, c, d, e, f);
}

/* @addr 10:993a */
void far fn_10_993a(int a, int b)
{
    g_fp_3c7c(g_920e, a, b, g_0016, g_13dc);
}

/* @addr 10:73e2 */
void far fn_10_73e2(void)
{
    if (!g_9228) {
        g_9228 = 1;
        g_fp_3c54(g_05a0, 0);
    }
}

/* @addr 10:7d8e */
void far fn_10_7d8e(void)
{
    if (g_9228) {
        g_9228 = 0;
        g_fp_3c54(g_05a0, 1);
    }
}

/* @addr 10:6d7a */
void far fn_10_6d7a(int a, int b, int c)
{
    int r;

    ((FP7I)g_fp_3c50)(g_920e, 0, 0, a, b, c, 6);
}

/* @addr 10:6da6 */
void far fn_10_6da6(int a, int b)
{
    ((FP7I)g_fp_3c50)(g_920e, 0, g_13dc, 0, a, b, 4);
    fn_10_6e4c();
}

/* @addr 10:6dd4 */
void far fn_10_6dd4(int a)
{
    ((FP7I)g_fp_3c50)(g_920e, 0, g_13dc, 0, a, 0, 5);
    fn_10_6e4c();
}

/* @addr 10:946a */
int far fn_10_946a(char far *p)
{
    char buf[20];
    int r;

    r = g_fp_3c68(p, buf, 10);
    p[0x30] = 0;
    return r;
}

/* @addr 10:744c */
void far fn_10_744c(int a)
{
    fn_10_754a(0x69, 0, 0, 0);
    if (a != 0x69)
        fn_10_754a(a, 0, 0, 0);
}

/* @addr 10:80a8 */
int far fn_10_80a8(void)
{
    int r;

    if (g_921e < 20) {
        g_921e++;
        fn_10_80dc();
        r = fn_10_82a2(8);
        fn_10_81b6();
    }
    return r;
}

/* @addr 10:7370 */
void far fn_10_7370(int a, int b, int c, int d, int e, int f, int g)
{
    int r;

    g_fp_3c44(g_13dc, a, b, c, d, e, g_920e, f, g);
}

/* @addr 10:7d58 */
void far fn_10_7d58(int x, int y)
{
    POINT p;

    if (g_9210) {
        p.x = x;
        p.y = y;
        g_fp_3c58(p, -10, -10, g_90ea);
    }
}

/* @addr 10:6bca */
void far fn_10_6bca(int a, int b, int c, int d, int e, int f, int g, int h,
                    int i, int j, long k)
{
    g_fp_3c48(a, b, c, d, e, f, g, h, i, j, k);
}

/* @addr 10:73a6 */
void far fn_10_73a6(int a, long b, int c, int d, int e, int f, int g,
                    char h, char i)
{
    g_fp_3c34(g_920e, a, b, g_13dc, c, d, e, f, g, h, i);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_754a(int a, int b, int c, int d)
{
    g_90f4 = a + b + c + d;
}

/* Stats SYSTEM.INI and WIN.INI in the Windows directory and IGRAPHIC.DLL
 * in the game directory g_8f7a, into g_922e / g_924c / g_926a [inferred:
 * a copy-protection or change check]. */
/* @addr 10:80dc */
void far fn_10_80dc(void)
{
    char buf[120];
    int r;

    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "SYSTEM.INI");
    r = stat(buf, &g_922e);
    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "WIN.INI");
    stat(buf, &g_924c);
    lstrcpy(buf, g_8f7a);
    lstrcat(buf, "IGRAPHIC.DLL");
    r = stat(buf, &g_926a);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_81b6(void)
{
    g_90f4 = 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_10_82a2(int a)
{
    return a;
}

/* @addr 10:561a */
void far fn_10_561a(void)
{
    if (g_9300 && !g_39ee)
        fn_10_6ee6(3, 0xb4, "", 0, 0x63, 3, 0, 1, 0, 12, 12, 0, 0);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_6ee6(int a, int b, char far *s, int c, int d, int e, int f,
                    int g, int h, int i, int j, int k, int l)
{
    g_90f4 = a;
}

/* @addr 10:740c */
void far fn_10_740c(void)
{
    HWND h;
    HTASK t;
    int u;

    h = GetActiveWindow();
    t = GetWindowTask(g_0016);
    if (GetWindowTask(h) == t)
        g_fp_3c54(g_05a0, 9);
}

/* @addr 10:5cfa */
void far fn_10_5cfa(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        if (g_3c60[i]) {
            DeleteObject(g_3c60[i]);
            g_3c60[i] = 0;
        }
    }
}

/* @addr 10:9526 */
void far fn_10_9526(long a, int b, int c, long d, int e, long f, int g,
                    int h, int i, long j, int k)
{
    g_fp_3c78(g_13dc, g_920e, a, b, c, d, e, f, g, h, i, j, k);
}

/* @addr 10:6fec */
void far fn_10_6fec(int a, long b, int c, int d, int e, int f, int g, int h,
                    char i, char j, char k, int l)
{
    g_fp_3c30(g_920e, a, b, g_13dc, c, d, e, f, g, h, i, j, k, l);
}

/* @addr 10:7dd4 */
void far pascal fn_10_7dd4(long a, long b, long c, long d, long e, long f,
                           long g, long h, long i, long j, long k, long l)
{
    g_fp_3c6c(a, b, c, d, e, f, g, h, i, j, k, l);
}

/* @addr 10:7328 */
void far fn_10_7328(int a, long b, int c, int d, char e, char f, int g, int h,
                    char i, char m)
{
    int r;

    g_fp_3c38(g_920e, a, b, g_13dc, m, c, d, e, f, g, h, i, g_9156);
}

/* @addr 10:6b70 */
void far fn_10_6b70(int a)
{
    if (g_9210) {
        if (!a) {
            g_fp_3c54(g_05a0, 6);
            g_fp_3c54(g_05a0, 8);
        }
        FreeLibrary(g_9210);
        g_9210 = 0;
    }
    if (g_9212) {
        FreeLibrary(g_9212);
        g_9212 = 0;
    }
}

/* @addr 10:804c */
long far fn_10_804c(int a)
{
    struct tm *tm;
    time_t t;
    long r;
    int y;
    int md;

    time(&t);
    if (a)
        return t;
    tm = localtime(&t);
    y = tm->tm_year;
    md = (char)tm->tm_mday | ((BYTE)tm->tm_mon << 8);
    r = ((long)y << 16) | (unsigned)md;
    return r;
}

/* @addr 10:94c4 */
void far fn_10_94c4(int a, int b, long c, int d, int e, long f)
{
    long l;

    switch (a) {
    case 0:
        l = 0x140012L;
        break;
    case 1:
        l = 0x12000cL;
        break;
    case 2:
        l = 0xa0009L;
        break;
    }
    g_fp_3c74(g_13dc, g_920e, l, b, c, d, e, f);
}

/* @addr 10:9764 */
int far fn_10_9764(int a)
{
    struct tm *tm;
    time_t t;

    time(&t);
    tm = localtime(&t);
    if (a)
        return tm->tm_wday;
    if (tm->tm_hour > 2 && tm->tm_hour < 12)
        return 0;
    if (tm->tm_hour <= 2)
        return 3;
    if (tm->tm_hour >= 12 && tm->tm_hour < 18)
        return 1;
    return 2;
}

/* @addr 10:7f18 */
void far fn_10_7f18(void)
{
    g_0592 = 2;
    fn_10_744c(0x6e);
    fn_10_7480(-2, 1);
    g_fp_3c64(g_0016, 0, 0, g_8ffa, g_8ffc, 0, 0);
    fn_06_0b3e();
    fn_10_7f88();
    g_1e50 = GetCurrentTime();
    g_3b94 = GetCurrentTime() + 500;
    fn_10_7480(-3, 1);
}

/* @addr 10:7480 */
void far fn_10_7480(int a, int b)
{
    POINT pt;
    int u;

    if ((a == 9 || a == 10) && (g_9220 == 9 || g_9220 == 10))
        return;
    if (a == 10 && g_9220 == 1)
        a = 9;
    if (a == -2) {
        g_07e0[g_073e] = (char)g_9220;
        music_pause_state = -2;
    } else {
        music_pause_state = -3;
        if (a == -3 && g_07e0[g_073e] != g_9220)
            a = g_07e0[g_073e];
    }
    pt.y = b;
    pt.x = a;
    if (a == 7)
        a = 2;
    if (a >= 0) {
        g_9220 = a;
        if (g_2384 < g_1e50)
            g_2384 = g_1e50 + 9000;
    }
    if (g_9210)
        ((void (far pascal *)(POINT, int))g_fp_3c54)(pt, 11);
}

/* @addr 10:7f88 */
void far fn_10_7f88(void)
{
    int old;
    int nw;
    HPALETTE pal;

    old = g_9156;
    nw = GetPrivateProfileInt(g_9690, "Size", 1, g_96a9);
    if (nw != old) {
        if (g_39e8[40]) {
            g_13dc = GetDC(g_0016);
            if (g_920e)
                pal = SelectPalette(g_13dc, g_920e, 0);
            if (nw < old) {
                if (nw - old != -1)
                    fn_10_9a2a(-1);
                fn_10_9a2a(-1);
            } else {
                if (nw - old != 1)
                    fn_10_9a2a(1);
                fn_10_9a2a(1);
            }
            if (pal)
                SelectPalette(g_13dc, pal, 0);
            ReleaseDC(g_0016, g_13dc);
            g_13dc = 0;
        } else {
            g_103c = g_92e2 = 1;
        }
    }
}

/* @addr 10:87de */
void far fn_10_87de(void)
{
    int n;
    char buf[10];

    if (!g_11aa && (g_920c == -1 || g_920c == 3)) {
        n = GetPrivateProfileInt(g_9690, "PlusCount", 13, g_96a9);
        n++;
        if (n > 12) {
            n = 0;
            g_90f4 = 9;
            fn_10_82a2(14);
        }
        fn_06_0f1a(n, buf);
        WritePrivateProfileString(g_9690, "PlusCount", buf, g_96a9);
    }
}

/* @addr 10:39a8 */
void far fn_10_39a8(int a)
{
    if (!g_39e8[5]) {
        g_3ad0[5] = g_fp_3c30(g_920e, -1000, (long)(char far *)"", g_13dc,
                              0, 6, 0, 0, 0, 0, 0, 0, 0, 0);
        g_39e8[5] = CreateCompatibleDC(g_13dc);
        if (g_920e)
            g_3a5c[5] = SelectPalette(g_39e8[5], g_920e, 0);
        g_3974[5] = SelectObject(g_39e8[5], g_3ad0[5]);
        if (a)
            fn_10_6308(5, -1, -1, -1);
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_6308(int a, int b, int c, int d)
{
    g_90f4 = a + b + c + d;
}

/* @addr 10:5586 */
int far fn_10_5586(int a)
{
    int i;
    int j;

    if (a == 3 && g_92fe)
        return 1;
    for (i = 0; i <= g_9316; i++) {
        if (!g_7148[i].flag)
            continue;
        for (j = 0; j < g_7148[i].cnt; j++) {
            if (g_7148[i].list[j] == a)
                return 1;
        }
    }
    for (i = 0; i <= g_9416; i++) {
        if (g_3d5a[i].id == a)
            return 1;
    }
    return 0;
}

/* @addr 10:6c02 */
int far fn_10_6c02(int a, int b, int c)
{
    HPALETTE old;
    int got;
    int r;

    got = 0;
    if (!g_13dc) {
        got = 1;
        g_13dc = GetDC(g_0016);
        if (g_920e)
            old = SelectPalette(g_13dc, g_920e, 0);
    }
    r = g_fp_3c28(g_920e, a, g_07de, g_13dc, b, c);
    if (got) {
        if (old)
            SelectPalette(g_13dc, old, 0);
        ReleaseDC(g_0016, g_13dc);
        g_13dc = 0;
    }
    return r;
}

/* @addr 10:506c */
void far fn_10_506c(void)
{
    int i;
    int w;
    int h;

    w = 32;
    h = 6;
    if (!g_39e8[32]) {
        g_39e8[32] = CreateCompatibleDC(g_13dc);
        g_3ad0[32] = CreateCompatibleBitmap(g_13dc, g_92ec << 5, 32);
        g_3974[32] = SelectObject(g_39e8[32], g_3ad0[32]);
    }
    for (i = 0; i < g_92ec; i++)
        BitBlt(g_39e8[32], w * i, 0, w, w, g_39e8[13], (h + w) * i + h, h,
               SRCCOPY);
}

/* @addr 10:6c96 */
int far fn_10_6c96(int a, char far *b, int c, int d, int e)
{
    HPALETTE old;
    int got;
    int r;

    got = 0;
    if (!g_13dc) {
        got = 1;
        g_13dc = GetDC(g_0016);
        if (g_920e)
            old = SelectPalette(g_13dc, g_920e, 0);
    }
    if (e)
        c -= 150;
    r = g_fp_3c28(g_920e, a, b, g_13dc, c, d - 150);
    if (got) {
        if (old)
            SelectPalette(g_13dc, old, 0);
        ReleaseDC(g_0016, g_13dc);
        g_13dc = 0;
    }
    return r;
}

/* @addr 10:a90c */
void far sprite_dc_restore(void)
{
    int i;

    for (i = 0; i < 58; i++) {
        if (g_3b9c[i]) {
            g_39e8[i] = CreateCompatibleDC(g_13dc);
            SelectObject(g_39e8[i], g_3ad0[i]);
            if (g_920e)
                SelectPalette(g_39e8[i], g_920e, 0);
        }
    }
}

/* @addr 10:a856 */
void far sprite_dc_release(void)
{
    int i;

    for (i = 0; i < 58; i++) {
        if (g_39e8[i]) {
            if (i != g_7094[g_9646].f00 && i != 10 && i != 12 && i != 34
                && i != 7 && i != 6 && i != 9 && i != 8) {
                g_3b9c[i] = 1;
                SelectObject(g_39e8[i], g_3974[i]);
                if (g_920e)
                    SelectPalette(g_39e8[i], g_3a5c[i], 0);
                DeleteDC(g_39e8[i]);
                g_39e8[i] = 0;
            }
        } else
            g_3b9c[i] = 0;
    }
}

/* @addr 10:7896 */
int far fn_10_7896(int a, POINT pt)
{
    int res;
    int i;
    int j;
    int d;

    res = 1;
    if (!a)
        return 1;
    if (subgame_active)
        return 1;
    if (a == 4)
        return 1;
    d = fn_08_285a(&i, &j, pt, g_1df8[g_9324][g_9646].f04);
    if (d > 800)
        return -1;
    if (d > 340)
        res = 0;
    if (res) {
        res = 0;
        for (i = 0; i < g_9158; i++) {
            if (PtInRect(&g_23e0[i], pt)) {
                res = 1;
                break;
            }
        }
    }
    return res;
}

/* @addr 10:5c42 */
void far fn_10_5c42(void)
{
    int n;

    if (subgame_active)
        n = g_9156 * 6 + 3;
    else
        n = (9 << g_9156) >> 1;
    if (g_3c60[0])
        fn_10_5cfa();
    g_3c60[0] = (HGDIOBJ)fn_10_7032(0, 16, 0);
    if (!g_39e8[34]) {
        g_39e8[34] = CreateCompatibleDC(g_13dc);
        g_3ad0[34] = CreateCompatibleBitmap(g_13dc, n << 4, n << 4);
        if (g_920e)
            g_3a5c[34] = SelectPalette(g_39e8[34], g_920e, 0);
        g_3974[34] = SelectObject(g_39e8[34], g_3ad0[34]);
        PatBlt(g_39e8[34], 0, 0, n << 4, n << 4, BLACKNESS);
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_10_7032(int a, int b, int c)
{
    return a + b + c;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_9a2a(int d)
{
    g_90f4 = d;
}

/* StretchBlt, or fn_10_6bca (g_fp_3c48) for an exact 2x stretch or a
 * mirrored one when g_0742 is set and the source DC is not mono or more
 * than 8 bits deep. The first argument is unused. */
/* @addr 10:9962 */
void far fn_10_9962(int unused, HDC dst, int x, int y, int w, int h, HDC src,
                    int xs, int ys, int ws, int hs, DWORD rop)
{
    HBITMAP bm;
    BITMAP b;
    int flag;
    char pad[0x30];

    flag = 0;
    bm = CreateCompatibleBitmap(src, 2, 2);
    GetObject(bm, sizeof(BITMAP), &b);
    if (b.bmPlanes * b.bmBitsPixel == 1 || b.bmPlanes * b.bmBitsPixel > 8)
        flag = 1;
    DeleteObject(bm);
    if (g_0742 && !flag &&
        ((ws * 2 == w && hs * 2 == h) || w < 0 || h < 0))
        fn_10_6bca(dst, x, y, w, h, src, xs, ys, ws, hs, rop);
    else
        StretchBlt(dst, x, y, w, h, src, xs, ys, ws, hs, rop);
}
