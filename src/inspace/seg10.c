/* INSPACE.EXE segment 10 (selector 1048). */
#include "inspace.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utime.h>

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
extern int (far pascal *g_fp_3c64)(int, int, int, int, int, int, int);
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
    char p02[0x12 - 0x02];
    int f12;            /* +0x12 */
    char rest[0x34 - 0x14];
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
    char p1a[0x22 - 0x1a];
    int f22;            /* +0x22 */
    int f24;            /* +0x24 */
    char rest[0x70 - 0x26];
} REC_70;
extern REC_70 far *g_1e00;
extern int g_92f0;
extern int g_3b9c[];
typedef struct {
    int f00;
    char p02[0x4a - 0x02];
    int f4a;            /* +0x4a */
    int f4c;            /* +0x4c */
    char rest[0x15a - 0x4e];
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
void far fn_10_0552(int i, int force);
extern struct stat g_922e;
typedef struct {
    int f00;            /* +0x00 */
    int f02;            /* +0x02 */
    int f04;            /* +0x04: surface index */
    int f06;            /* +0x06 */
    char p08[0x0e - 0x08];
    int f0e;            /* +0x0e */
    char p10[0x12 - 0x10];
    int f12;            /* +0x12 */
    char p14[0x22 - 0x14];
    int f22;            /* +0x22 */
    int f24;            /* +0x24 */
    char p26[0x2e - 0x26];
    int f2e;            /* +0x2e */
    char rest[0x50 - 0x30];
} REC_50;
extern REC_50 g_2f4c[];
extern int g_931e;
extern REC_70 far *g_1e10;
void far fn_10_4412(int a, int b, int c, int d);
void far fn_06_99b6(void);
void far fn_06_885c(int a, int b);
extern int g_9320;
void far fn_10_3ea2(void);
void far fn_10_58ce(int a);
void far fn_10_565a(void);
void far fn_10_5202(void);
void far fn_10_3a2e(void);
void far fn_10_42ee(void);
void far race_marker_strip(void);
extern long g_1e68;
extern int g_8fe8;
void far fn_09_27da(int a);
extern HWND g_0a7c;
extern int g_0a76;
extern DWORD g_870c;
extern int g_059c;
extern int g_059e;
extern long g_05c4;
extern long g_05c8;
extern int g_9214;
extern int g_9406;
extern struct utimbuf g_3c10[3];
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

/* Puts back the modification times fn_10_80dc saved for SYSTEM.INI,
 * WIN.INI and IGRAPHIC.DLL. */
/* @addr 10:81b6 */
void far fn_10_81b6(void)
{
    char buf[120];

    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "SYSTEM.INI");
    g_3c10[0].modtime = g_922e.st_mtime;
    utime(buf, &g_3c10[0]);
    GetWindowsDirectory(buf, 110);
    if (buf[lstrlen(buf) - 1] != '\\')
        lstrcat(buf, "\\");
    lstrcat(buf, "WIN.INI");
    g_3c10[1].modtime = g_924c.st_mtime;
    utime(buf, &g_3c10[1]);
    lstrcpy(buf, g_8f7a);
    lstrcat(buf, "IGRAPHIC.DLL");
    g_3c10[2].modtime = g_926a.st_mtime;
    utime(buf, &g_3c10[2]);
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

/* Builds surface a with g_fp_3c30 (a d >= 100 means d - 100 and no
 * fn_10_6308 afterwards); h becomes a 0/1 flag. */
/* @addr 10:6ee6 */
void far fn_10_6ee6(int a, int b, char far *s, int c, int d, int e, int f,
                    int g, int h, int i, int j, int k, int l)
{
    int u[8];
    int flag;

    flag = 1;
    if (g_39e8[a])
        fn_10_0552(a, 0);
    if (d >= 100) {
        d -= 100;
        flag = 0;
    }
    if ((g_9156 >= 2 && h != -1 && !l) || h > 1)
        h = 1;
    else
        h = 0;
    g_3ad0[a] = g_fp_3c30(g_920e, b, (long)s, g_13dc, c, d, e, f, g, h,
                          (char)i, (char)j, (char)k, l);
    g_39e8[a] = CreateCompatibleDC(g_13dc);
    g_3974[a] = SelectObject(g_39e8[a], g_3ad0[a]);
    if (g_920e)
        g_3a5c[a] = SelectPalette(g_39e8[a], g_920e, 0);
    if (!subgame_active && flag && (g_9156 != 2 || l))
        fn_10_6308(a, -1, -1, -1);
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

/* Recreates surface 13: a (32 + 6) * g_9406 + 6 by 6 * 2 + 32 bitmap,
 * cleared to black. */
/* @addr 10:5b30 */
void far fn_10_5b30(void)
{
    int a;
    int b;

    a = 6;
    b = 32;
    if (!g_9288)
        g_9288 = CreateCompatibleDC(g_13dc);
    if (g_39e8[13]) {
        SelectObject(g_39e8[13], g_3974[13]);
        if (g_920e)
            SelectPalette(g_39e8[13], g_3a5c[13], 0);
        DeleteObject(g_3ad0[13]);
        DeleteDC(g_39e8[13]);
    }
    g_39e8[13] = CreateCompatibleDC(g_13dc);
    g_3ad0[13] = CreateCompatibleBitmap(g_13dc, (b + a) * g_9406 + a, a * 2 + b);
    g_3974[13] = SelectObject(g_39e8[13], g_3ad0[13]);
    if (g_920e)
        g_3a5c[13] = SelectPalette(g_39e8[13], g_920e, 0);
    PatBlt(g_39e8[13], 0, 0, (b + a) * g_9406 + a, b * a * 2, BLACKNESS);
}

/* Meal break check: g_9214 = 3 (Lunch, default 12:00), 4 (Breakfast,
 * 8:00), 1 (Coffee, 10:00), 2 (Tea, 15:30) when the time read from the
 * INI file lies in the half hour before now (hhmm + 1), else 0. */
/* @addr 10:9672 */
int far fn_10_9672(void)
{
    struct tm *tm;
    time_t t;
    int v;
    int now;

    time(&t);
    tm = localtime(&t);
    now = tm->tm_hour * 100 + tm->tm_min + 1;
    if ((v = GetPrivateProfileInt(g_9690, "Lunch", 1200, g_96a9)) < now && v + 30 > now)
        g_9214 = 3;
    else if ((v = GetPrivateProfileInt(g_9690, "Breakfast", 800, g_96a9)) < now && v + 30 > now)
        g_9214 = 4;
    else if ((v = GetPrivateProfileInt(g_9690, "Coffee", 1000, g_96a9)) < now && v + 30 > now)
        g_9214 = 1;
    else if ((v = GetPrivateProfileInt(g_9690, "Tea", 1530, g_96a9)) < now && v + 30 > now)
        g_9214 = 2;
    else
        g_9214 = 0;
    return g_9214;
}

/* Changes the frame delay g_059c by 2 * d (clamped to 4..104, wrapping
 * past 104 to 1200 [sic]), derives the frame rate values and saves
 * "FrameRateSet" to the INI file. */
/* @addr 10:7e1c */
void far fn_10_7e1c(int d)
{
    int u;
    char buf[8];
    long l1;
    long l2;
    int q;
    int r;
    int u2;

    if (g_0a7c) {
        g_870c = g_1e50 + 5000;
        g_0a76 = 4;
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    }
    g_059c += d * 2;
    if (d < 0 && g_059c > 1000)
        g_059c = 104;
    g_059c = g_059c < 4 ? 4 : g_059c;
    if (g_059c > 104)
        g_059c = 1200;
    g_059e = g_059c / 4;
    g_05c4 = 1000 / g_059c;
    q = 10000 / g_059c;
    r = q % 10;
    if (r > 4)
        g_05c4++;
    g_05c8 = g_05c4 - 1;
    fn_06_0f1a(g_059c, buf);
    WritePrivateProfileString(g_9690, "FrameRateSet", buf, g_96a9);
}

/* Copies surface 40 + g_7094[i].f4c into a new surface 40 + i sized from
 * g_96d2[g_7094[i].f4a].f2a and the current ship's f24 [inferred]. */
/* @addr 10:86e2 */
void far fn_10_86e2(int i)
{
    int d;
    int w;
    int n;
    int s;

    w = g_96d2[g_7094[i].f4a].f2a;
    n = g_1df8[g_9324]->f24;
    d = i + 40;
    s = g_7094[i].f4c + 40;
    if (g_39e8[d])
        fn_10_0552(d, 0);
    g_3ad0[d] = CreateCompatibleBitmap(g_13dc, w * 16 + n * 17, n * 2 + w);
    g_39e8[d] = CreateCompatibleDC(g_13dc);
    g_3974[d] = SelectObject(g_39e8[d], g_3ad0[d]);
    if (g_920e)
        g_3a5c[d] = SelectPalette(g_39e8[d], g_920e, 0);
    BitBlt(g_39e8[d], 0, 0, w * 16 + n * 17, n * 2 + w, g_39e8[s], 0, 0, SRCCOPY);
}

/* Creates surfaces 10 and 11 (bitmaps 0xaa and 0xaf, the second mirrored
 * [inferred]) when either is missing. */
/* @addr 10:5102 */
void far fn_10_5102(void)
{
    int a;
    int i;
    int b, c, d, e;
    int n;
    int f;
    int id;
    int x;
    int y;
    int g, h, k, m;

    if (!g_39e8[10] || !g_39e8[11]) {
        for (i = 0; i < 2; i++) {
            fn_10_740c();
            if (i == 0) {
                n = 10;
                id = 0xaa;
                if (g_8fe8)
                    x = 2;
                else
                    x = 0;
                y = 1;
            } else if (i == 1) {
                n = 11;
                id = 0xaf;
                x = 0;
                y = -1;
                if (!g_1e68)
                    fn_09_27da(50);
            }
            if (!g_39e8[n]) {
                g_3ad0[n] = fn_10_6c02(id, x, y);
                g_39e8[n] = CreateCompatibleDC(g_13dc);
                g_3974[n] = SelectObject(g_39e8[n], g_3ad0[n]);
                if (g_920e)
                    g_3a5c[n] = SelectPalette(g_39e8[n], g_920e, 0);
                fn_10_740c();
                fn_10_6308(n, -1, -1, -1);
            }
        }
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_3ea2(void)
{
    g_90f4 = 2;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_58ce(int a)
{
    g_90f4 = a;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_565a(void)
{
    g_90f4 = 3;
}

/* Builds surface 12: a 270 x 22 strip of six pieces of bitmap 200,
 * growing in size [inferred]. */
/* @addr 10:5202 */
void far fn_10_5202(void)
{
    int i;
    int h;
    int u;
    int x;
    HBITMAP bm;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;

    bm = fn_10_6c02(200, 0, -1);
    dc = CreateCompatibleDC(g_13dc);
    ob = SelectObject(dc, bm);
    if (g_920e)
        pal = SelectPalette(dc, g_920e, 0);
    x = 0;
    g_3ad0[12] = CreateCompatibleBitmap(g_13dc, 270, h = 22);
    g_39e8[12] = CreateCompatibleDC(g_13dc);
    g_3974[12] = SelectObject(g_39e8[12], g_3ad0[12]);
    if (g_920e)
        g_3a5c[12] = SelectPalette(g_39e8[12], g_920e, 0);
    PatBlt(g_39e8[12], 0, 0, 270, h, BLACKNESS);
    for (i = 0; i <= 5; i++) {
        u = (i + 5) * 6;
        BitBlt(g_39e8[12], x * 3, 0, u, u / 3, dc, 0, x, SRCCOPY);
        x += u / 3;
    }
    SelectObject(dc, ob);
    DeleteObject(bm);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    fn_10_6308(12, -1, -1, -1);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_3a2e(void)
{
    g_90f4 = 5;
}

/* Builds surface 29 (89 x 33) from bitmaps 0x2b2..0x2b4. Selects the
 * palette into g_13dc instead of the new DC and frees its temporary DC
 * with DeleteObject [sic]. */
/* @addr 10:42ee */
void far fn_10_42ee(void)
{
    HDC dc;
    HPALETTE old;
    HBITMAP bm;
    HBITMAP ob;
    int i;
    int u;
    int u2;

    if (!g_39e8[29]) {
        dc = CreateCompatibleDC(g_13dc);
        if (g_920e)
            old = SelectPalette(dc, g_920e, 0);
        g_39e8[29] = CreateCompatibleDC(g_13dc);
        if (g_920e)
            g_3a5c[29] = SelectPalette(g_13dc, g_920e, 0);
        g_3ad0[29] = CreateCompatibleBitmap(g_13dc, 0x59, 0x21);
        g_3974[29] = SelectObject(g_39e8[29], g_3ad0[29]);
        PatBlt(g_39e8[29], 0, 0, 0x59, 0x21, BLACKNESS);
        for (i = 0; i < 3; i++) {
            ob = SelectObject(dc, bm = fn_10_6c02(i + 0x2b2, 3, -1));
            BitBlt(g_39e8[29], i * 0x1c + 5, u = 5, 0x17, 0x17, dc, 0, 0, SRCCOPY);
            SelectObject(dc, ob);
            DeleteObject(bm);
        }
        if (g_920e)
            SelectPalette(dc, old, 0);
        DeleteObject(dc);
        fn_10_6308(29, -1, -1, -1);
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far race_marker_strip(void)
{
    g_90f4 = 7;
}

/* Rebuilds the game's surfaces: frees each and calls its builder. */
/* @addr 10:9568 */
void far fn_10_9568(void)
{
    fn_10_0552(1, 1);
    fn_10_0552(2, 1);
    fn_10_3ea2();
    fn_10_0552(22, 1);
    fn_10_58ce(1);
    fn_10_0552(4, 1);
    fn_10_565a();
    fn_10_0552(12, 1);
    fn_10_5202();
    fn_10_0552(5, 1);
    fn_10_39a8(1);
    fn_10_0552(6, 1);
    fn_10_0552(8, 1);
    fn_10_0552(7, 1);
    fn_10_0552(9, 1);
    fn_10_3a2e();
    fn_10_0552(10, 1);
    fn_10_0552(11, 1);
    fn_10_5102();
    fn_10_0552(29, 1);
    fn_10_42ee();
    fn_10_0552(3, 1);
    fn_10_561a();
    fn_10_0552(0, 1);
    fn_10_464a();
    fn_10_0552(30, 1);
    if (g_9320 == 6)
        race_marker_strip();
}

/* "StratAsk": while the INI value is 0 or 1, asks (strings 0xb22..0xb25)
 * with a yes/no box; yes adds 10 to the value and saves it, no returns 0. */
/* @addr 10:a96c */
int far fn_10_a96c(void)
{
    int r;
    int v;
    char b0[200];
    char b1[200];
    char b2[200];

    v = GetPrivateProfileInt(g_9690, "StratAsk", 0, g_96a9);
    if (v == 0 || v == 1) {
        fn_10_744c(0x2c);
        LoadString(g_9212, 0xb22, b1, 200);
        LoadString(g_9212, 0xb23, b2, 200);
        lstrcat(b1, b2);
        LoadString(g_9212, 0xb24, b2, 200);
        lstrcat(b1, b2);
        LoadString(g_9212, 0xb25, b2, 200);
        lstrcat(b1, b2);
        r = MessageBox(g_0016, b1, g_9690, MB_YESNO | MB_ICONEXCLAMATION);
        if (r != IDYES)
            return 0;
        fn_06_0f1a(v += 10, b1);
        WritePrivateProfileString(g_9690, "StratAsk", b1, g_96a9);
    }
    return 1;
}

/* Frees the surface of g_2f4c[a] unless another active entry of g_7148
 * or g_3d5a (state 2) still uses it, or a is 22. */
/* @addr 10:546e */
void far fn_10_546e(int a)
{
    int i;
    int j;
    int s;

    for (i = 0; i <= g_9316; i++) {
        if (g_7148[i].flag) {
            for (j = 0; j < g_7148[i].cnt; j++)
                if (g_2f4c[g_7148[i].list[j]].f04 == g_2f4c[a].f04)
                    return;
        }
    }
    for (i = 0; i <= g_9416; i++)
        if (g_3d5a[i].f12 == 2 && g_2f4c[g_3d5a[i].id].f04 == g_2f4c[a].f04)
            return;
    if (a == 22)
        return;
    s = g_2f4c[a].f04;
    if (s < 0)
        return;
    if (g_39e8[s]) {
        if (g_3a5c[s])
            SelectPalette(g_39e8[s], g_3a5c[s], 0);
        SelectObject(g_39e8[s], g_3974[s]);
        DeleteDC(g_39e8[s]);
        g_39e8[s] = 0;
        g_2f4c[a].f04 = 0;
        if (g_3ad0[s]) {
            DeleteObject(g_3ad0[s]);
            g_3ad0[s] = 0;
        }
    }
}

/* Quit/leave confirmation [inferred]: for a = 1, -1 or 3 asks only when
 * "SavePrompt" is set or the "Restore" entry looks unused; shows the
 * g_fp_3c64 dialog and on yes ends (a = 1 or -1 destroys the window). */
/* @addr 10:8568 */
int far fn_10_8568(int a)
{
    int r;
    int ask;
    char buf[80];

    ask = 1;
    fn_10_7480(-2, 1);
    if (a == 1 || a == -1 || a == 3) {
        ask = GetPrivateProfileInt(g_9690, "SavePrompt", 1, g_96a9);
        if (!ask) {
            GetPrivateProfileString(g_9690, "Restore", "", buf, 9, g_96a9);
            if (buf[3] == ' ' || !buf[0])
                ask = 1;
        }
    }
    if (ask) {
        fn_10_744c(0x6e);
        fn_10_744c(0x13);
        r = g_fp_3c64(g_0016, g_39e8[5], g_920e, 0, 0, 0, 3);
        g_1e50 = GetCurrentTime();
        g_3b94 = GetCurrentTime() + 500;
    } else
        r = 1;
    if (r) {
        switch (a) {
        case 1:
        case 2:
        case 3:
            fn_06_99b6();
            if (a == 1)
                DestroyWindow(g_0016);
            break;
        case -1:
        case 0:
            fn_06_885c(1, 0);
            if (a == -1)
                DestroyWindow(g_0016);
            break;
        }
    }
    fn_10_7480(-3, 1);
    return r;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_4412(int a, int b, int c, int d)
{
    g_90f4 = a + b + c + d;
}

/* Gives g_2f4c[a] a surface in 48..56: shares one already built for the
 * same f06, else builds a new one (fn_10_4412 for kind 4, else
 * fn_10_6ee6). Entries 22 and 27 are skipped. */
/* @addr 10:533a */
void far fn_10_533a(int a)
{
    int i;
    int j;
    int u;
    int f;

    if (a == 27 || a == 22)
        return;
    for (i = 0x30; i < 0x39; i++) {
        if (g_39e8[i]) {
            for (j = 0; j <= 27; j++)
                if (g_2f4c[j].f12 && g_2f4c[j].f04 == i &&
                    g_2f4c[j].f06 == g_2f4c[a].f06) {
                    g_2f4c[a].f04 = i;
                    return;
                }
        }
    }
    for (i = 0x30; i < 0x39; i++) {
        if (!g_39e8[i]) {
            g_2f4c[a].f04 = i;
            g_1e10->f22 = g_2f4c[a].f00;
            g_1e10->f24 = g_2f4c[a].f02;
            if (g_2f4c[a].f0e == 4) {
                fn_10_4412(i, 6, g_2f4c[a].f06, g_2f4c[a].f2e);
            } else {
                if (g_90f4 == 1 && g_1e68) {
                    if (g_931e == 1 || g_931e == 2)
                        f = 1;
                    else
                        f = 0;
                } else if (g_931e == 2)
                    f = 1;
                else
                    f = 0;
                fn_10_6ee6(i, g_2f4c[a].f06, "", 2, 0x63, g_2f4c[a].f22,
                           g_2f4c[a].f24, 1, 0, 12, 12, 0, f);
            }
            return;
        }
    }
}
