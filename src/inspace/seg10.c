/* INSPACE.EXE segment 10 (selector 1048). */
#include "inspace.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include <stdarg.h>
#include <stdlib.h>

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
    int f14;            /* +0x14 */
    int f16;            /* +0x16 */
    int f18;            /* +0x18 */
    char p1a[0x20 - 0x1a];
    int f20;            /* +0x20 */
    char p22[0x26 - 0x22];
    int f26;            /* +0x26: class [inferred] */
    char rest[0x34 - 0x28];
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
    int f04;            /* +0x04 */
    char p06[0x24];
    int f2a;            /* +0x2a */
    char p2c[0x44 - 0x2c];
    int f44;            /* +0x44 */
    char p46[2];
    int f48;            /* +0x48 */
    char p4a[6];
    POINT f50[5];       /* +0x50 */
    char rest[0xad - 0x64];
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
    int f00;
    int f02;
    union { long l; POINT pt; } f04;
    char p08[0x12 - 0x08];
    int f12;            /* +0x12 */
    char p14[0x18 - 0x14];
    int f18;
    char p1a[0x20 - 0x1a];
    int f20;            /* +0x20 */
    int f22;            /* +0x22 */
    int f24;            /* +0x24 */
    char rest[0x70 - 0x26];
} REC_70;
extern REC_70 far *g_1e00;
extern HDC g_93d0;
extern HDC g_93cc;
extern HDC g_3a24;
extern HDC g_39f0;
extern HDC g_3a38[];
extern HBRUSH g_5006;
extern HBRUSH g_5008;
extern HBRUSH g_500c;
extern REC_70 far *g_1e08;
extern REC_70 far *g_1e30;
extern int g_0a72;
extern int g_9318;
extern int g_9322;
extern int g_05a2;
extern char g_9eb6[];
extern char g_9ebc[];
extern char g_9eb9[];
extern char g_9ebf[];
extern char g_9ec2[][40];
extern POINT g_9f40[][40];
extern POINT g_a120[];
extern POINT g_9ea8[];
extern int g_92f0;
extern int g_3b9c[];
typedef struct {
    int f00;
    char p02[0x4a - 0x02];
    int f4a;            /* +0x4a */
    int f4c;            /* +0x4c */
    char p4e[0xe0 - 0x4e];
    char fe0;           /* +0xe0 */
    char rest[0x15a - 0xe1];
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
extern int (far pascal *g_fp_3c3c)(int, int, int, int, int, int);
void far fn_10_9a2a(int d);
void far fn_10_5c42(void);
void far fn_10_5b30(void);
void far fn_10_9568(void);
void far fn_10_533a(int a);
void far fn_10_5d3c(int n);
void far fn_10_1502(int i);
int far fn_10_18b0(int k1, int k2, int type, int flag, int rec);
void far fn_14_11a8(int i);
void far fn_08_2cd8(int a, int b);
void far fn_07_233c(int a, int n, int c);
void far fn_09_94ba(void);
BOOL far pascal fn_09_90fe(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
extern int g_9408;
extern int g_9326;
extern int g_92e4;
extern int g_103a;
extern int g_9518;
extern HWND g_934c;
extern HDC g_3a02;
extern HDC g_3a28;
extern int g_4e94[];
typedef struct { int f0, f2, f4; } REC_6;
extern REC_6 g_381a[];
typedef struct {                /* 0x14-byte records at DS:4d92 */
    char f00;
    char f01;
    char p02[4];
    char f06;
    char f07;
    char rest[0x14 - 8];
} REC_14;
extern REC_14 g_4d92[];
typedef struct {                /* 0x7c bytes, far array at DS:6e24 */
    char p00[0x7a];
    char f7a;
    char f7b;
} REC_7C;
extern REC_7C far *g_6e24;
typedef struct {                /* 0x15a-byte object records at DS:7092 */
    char p00[0x4c];
    int f4c;            /* +0x4c: class record index */
    char p4e[0xaa - 0x4e];
    char faa;
    char fab;
    char pac[0xd4 - 0xac];
    int fd4;            /* +0xd4 */
    char rest[0x15a - 0xd6];
} REC_15A_C;
extern REC_15A_C g_7092[];
extern int g_92e2;
extern int g_103c;
extern int g_9220;
extern int music_pause_state;       /* DS:9222 */
extern char g_07e0[];
extern int g_073e;
extern DWORD g_2384;
extern int g_920c;
void far fn_06_0f1a(int n, char far *buf);
void far fn_06_0eb8(long v, LPSTR buf);
void far fn_03_1542(int a, int type, int n, LPSTR buf, int mode);
void far fn_03_3498(LPSTR s, LPSTR a, LPSTR b);
extern int g_93aa;
extern char g_8768[], g_87b8[], g_8db0[];
int far fn_10_6308(int a, int b, int c, int d);
extern int g_0740;
void far fn_10_9962(int unused, HDC dst, int x, int y, int w, int h, HDC src,
                    int xs, int ys, int ws, int hs, DWORD rop);
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
int far fn_10_7896(int a, POINT pt);
POINT far pascal fn_08_29ea(POINT pt);
typedef struct { int f0; int f2; } PAIR;
extern int (far pascal *g_fp_3c5c)(int, POINT, int, long, long, DWORD, LPCSTR);
typedef int (far pascal *FP3C5C)(int, POINT, int, int, int, long, DWORD, LPCSTR);
#pragma pack(1)
typedef struct {
    int x0[2][6];       /* +0x00 */
    int y0[2][6];       /* +0x18 */
    int x1[2][6];       /* +0x30 */
    int y1[2][6];       /* +0x48 */
    int z[2][6];        /* +0x60 */
    int count;          /* +0x78 */
    char p7a[0x84 - 0x7a];
    int f84;            /* +0x84 */
    char rest[0x94 - 0x86];
} REC_94;
#pragma pack()
extern REC_94 g_6098[];
extern POINT g_5144;
extern long g_88c0;
extern int g_90ec;
extern int g_9150;
extern int g_9292;
extern DWORD g_3c88;
extern int g_928c;
extern int g_928e;
extern int g_9216;
extern int g_9218;
extern int g_921a;
extern int g_921c;
extern int g_9290;
extern POINT g_3b98;
extern int g_9226;
extern int g_920a;
extern HBRUSH g_3b4c[20];
extern HBRUSH g_3b74[10];
extern HBRUSH g_576c[20];
extern HBRUSH g_3b88[6];
extern HPEN g_3b44[4];
void far fn_10_4dfe(void);
extern int g_8ff2;
extern int g_90f0;
void far fn_10_740c(void);
extern REC_70 far *g_1e18;
extern REC_70 far *g_1e1c;
extern HDC g_9656;
extern HBITMAP g_9658;
extern HBITMAP g_965a;
extern HPALETTE g_965c;
#pragma pack(1)
typedef struct {
    char p00[4];
    char name[0x24 - 4];    /* +0x04 */
    int f24;                /* +0x24 */
    char p26[0x32 - 0x26];
    int f32;                /* +0x32 */
    char p34[0x146 - 0x34];
    int f146[8];            /* +0x146 */
    int f156;               /* +0x156 */
    int f158;               /* +0x158 */
    int f15a;               /* +0x15a */
    int f15c;               /* +0x15c */
    int f15e;               /* +0x15e */
    int f160;               /* +0x160 */
    int f162;               /* +0x162 */
    char p164[0x18b - 0x164];
    DWORD time;             /* +0x18b */
} REC_PILOT;
#pragma pack()
void far pascal fn_10_a118(REC_PILOT far *src, LPSTR dst);
void far fn_10_a332(LPSTR out, int id, int n, ...);
void far fn_11_3fd4(LPSTR s, int a);
int far fn_09_88ba(int x);
extern int g_9460;
void far fn_10_80dc(void);
int far fn_10_82a2(int a);
int far fn_10_885e(int a);
long far fn_10_804c(int a);
void far fn_10_744c(int a);
int far fn_10_80a8(void);
extern HWND g_9532;
extern int g_922a;
extern int g_9224;
extern int flow_interactive;        /* DS:95bc */
extern char g_380c[];
extern DWORD g_6e28;
extern long g_939a;
extern long g_939e;
extern int g_104e;
extern int g_104c;
extern int g_951c;
extern int g_94ac;
extern int g_9516;
extern int g_95b8;
extern int g_9134;
extern int g_8f64;
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
HBITMAP far fn_10_6ec6(int a)
{
    return ((HBITMAP (far pascal *)(int, int, int))g_fp_3c40)(g_920e, a, g_13dc);
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
void far fn_10_740c(void);

/* @addr 10:464a */
void far fn_10_464a(void)
{
    g_928a = fn_10_6d38("DEF");
    fn_10_4672(0, 3);
}

/* Builds surface a from the strip g_928a (5 cells across, square cells):
 * per row, 16 directions made of the first n/4 + 1 cells and their mirror
 * images, b pixels apart; frees g_928a [inferred]. */
/* @addr 10:4672 */
void far fn_10_4672(int a, int b)
{
    int j;
    int i;
    int bits;
    int rows;
    int cell;
    int n;
    int ys;
    int yd;
    HDC dc;
    int u16;
    HBITMAP ob;
    int u1a;
    int u1c;
    HPALETTE pal;
    BITMAP bmp;

    GetObject(g_928a, sizeof(BITMAP), &bmp);
    cell = bmp.bmWidth / 5;
    rows = bmp.bmHeight / cell;
    n = 16;
    bits = bmp.bmPlanes * bmp.bmBitsPixel;
    dc = CreateCompatibleDC(g_13dc);
    ob = SelectObject(dc, g_928a);
    if (g_920e)
        pal = SelectPalette(dc, g_920e, 0);
    if (!g_39e8[a]) {
        g_39e8[a] = CreateCompatibleDC(g_13dc);
        g_3ad0[a] = CreateCompatibleBitmap(g_13dc, (cell + b) * n + b,
                                           (cell + b) * rows + b);
        g_3974[a] = SelectObject(g_39e8[a], g_3ad0[a]);
        if (g_920e)
            g_3a5c[a] = SelectPalette(g_39e8[a], g_920e, 0);
    }
    PatBlt(g_39e8[a], 0, 0, (cell + b) * n + b, (cell + b) * rows + b,
           BLACKNESS);
    yd = ys = 0;
    for (i = 0; i < rows; i++, ys += cell, yd += cell + b) {
        for (j = 0; j < n / 4 + 1; j++) {
            BitBlt(g_39e8[a], (cell + b) * j + b, yd + b, cell, cell, dc,
                   cell * j, ys, SRCCOPY);
            if (j == 0) {
                fn_10_9962(0, g_39e8[a], n / 2 * (cell + b) + b,
                           yd + cell + b - 1, cell, -cell, dc, cell * j, ys,
                           cell, cell, SRCCOPY);
            } else if (n / 4 == j) {
                fn_10_9962(0, g_39e8[a], n * 3 / 4 * (cell + b) + cell + b - 1,
                           yd + b, -cell, cell, dc, cell * j, ys, cell, cell,
                           SRCCOPY);
            } else {
                fn_10_9962(0, g_39e8[a], (n / 2 - j) * (cell + b) + b,
                           yd + cell + b - 1, cell, -cell, dc, cell * j, ys,
                           cell, cell, SRCCOPY);
                fn_10_9962(0, g_39e8[a], (n / 2 + j) * (cell + b) + cell + b - 1,
                           yd + cell + b - 1, -cell, -cell, dc, cell * j, ys,
                           cell, cell, SRCCOPY);
                fn_10_9962(0, g_39e8[a], (n - j) * (cell + b) + cell + b - 1,
                           yd + b, -cell, cell, dc, cell * j, ys, cell, cell,
                           SRCCOPY);
            }
        }
        fn_10_740c();
    }
    SelectObject(dc, ob);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(g_928a);
    fn_10_6308(a, -1, -1, -1);
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

/* Plays sound a at a position given by mode d (0 none, 1 object c of
 * group b, 2 record c of g_6098, 3 g_5144, 4 point (b, c), 5 -11111)
 * through g_fp_3c5c [inferred]. Some sounds set a follow-up in g_9292
 * due at g_3c88. vx/vy are computed and then overwritten [sic]. */
/* @addr 10:754a */
void far fn_10_754a(int a, int b, int c, int d)
{
    int r;
    POINT p;
    POINT saved;
    POINT dd;
    long pos;
    union { long l; PAIR p; } q;
    int k;

    if (a == 0x6e)
        d = 0;
    if (g_920c == 3)
        return;
    if (d != 5) {
        if (a >= 0x6a) {
            switch (a) {
            case 0x6a:
                a = 0x20;
                g_9292 = 0x21;
                g_3c88 = g_1e50 + 1000;
                break;
            case 0x6b:
                a = 0x39;
                g_9292 = 0x3a;
                g_3c88 = g_1e50 + 420;
                break;
            case 0x6c:
                a = 0x38;
                g_9292 = 0x39;
                g_3c88 = g_1e50 + 385;
                break;
            case 0x6d:
                a = 0x35;
                g_9292 = 0x39;
                g_3c88 = g_1e50 + 385;
                break;
            case 0x71:
                a = 0x24;
                g_9292 = 0x25;
                g_3c88 = g_1e50 + 660;
                break;
            case 0x72:
                a = 0x1a;
                g_9292 = 0x1a;
                g_3c88 = g_1e50 + 200;
                break;
            case 0x73:
                a = 0x42;
                g_9292 = 0x43;
                g_3c88 = g_1e50 + 700;
                break;
            case 0x74:
                a = 0x42;
                g_9292 = 0x66;
                g_3c88 = g_1e50 + 400;
                break;
            case 0x76:
                a = 0x23;
                g_9292 = 0x25;
                g_3c88 = g_1e50 + 400;
                break;
            default:
                g_3c88 = 0;
                break;
            }
            if (g_3c88) {
                g_9216 = a;
                g_9218 = b;
                g_921a = c;
            }
        }
        q.p.f2 = (g_1df8[g_9324][g_9646].f04.pt.x - ((int)g_90ea / 2 << g_9150)) >> 3;
        q.p.f0 = (g_1df8[g_9324][g_9646].f04.pt.y - (g_90ec / 2 << g_9150)) >> 3;
    }
    switch (d) {
    case 1:
        if (b > g_9324)
            return;
        p = g_1df8[b][c].f04.pt;
        break;
    case 2:
        if (g_6098[c].f84)
            k = 0;
        else
            k = 1;
        p.y = g_6098[c].y1[k][0];
        p.x = g_6098[c].x1[k][0];
        break;
    case 3:
        p = g_5144;
        break;
    case 0:
        p.y = -6000;
        p.x = -6000;
        break;
    case 4:
        p.x = b;
        p.y = c;
        q.p.f0 = -1;
        q.p.f2 = -1;
        break;
    case 5:
        p.x = -11111;
        p.y = -11111;
        q.p.f0 = -1;
        q.p.f2 = -1;
        break;
    }
    saved = p;
    r = fn_10_7896(d, saved);
    if (r == -1) {
        g_3c88 = 0;
        g_9216 = 0;
        g_9292 = 0;
        return;
    }
    if (d != 0 && d != 4 && d != 5) {
        p = fn_08_29ea(p);
        if (g_9156 != 1 && !subgame_active) {
            dd.x = p.x - g_1df8[g_9324][g_9646].f00;
            dd.y = p.y - g_1df8[g_9324][g_9646].f02;
            p.x = (dd.x * 2 >> g_9156) + g_1df8[g_9324][g_9646].f00;
            p.y = (dd.y * 2 >> g_9156) + g_1df8[g_9324][g_9646].f02;
        }
    }
    q.l = 0x10001L;
    if (subgame_active)
        pos = g_88c0;
    else
        pos = g_90ea;
    if (g_fp_3c5c(a, p, r, q.l, pos, g_1e50, "")) {
        g_921c = a;
        g_928c = b;
        g_928e = c;
        g_9290 = d;
        g_3b98 = saved;
        g_9226 = r;
    }
}

/* Like fn_10_754a with a name e [inferred: a sound file]; also plays
 * sound 0x69 when the source is the player's own object. */
/* @addr 10:7944 */
void far fn_10_7944(int a, int b, int c, int d, LPCSTR e)
{
    int r;
    POINT p;
    POINT saved;
    union { long l; PAIR p; } q;
    POINT dd;
    int unused[3];
    int k;

    if (g_920c == 3)
        return;
    if (subgame_active) {
        q.l = 0;
    } else {
        q.p.f0 = (g_1df8[g_9324][g_9646].f04.pt.x - ((int)g_90ea / 2 << g_9150)) >> 3;
        q.p.f2 = (g_1df8[g_9324][g_9646].f04.pt.y - (g_90ec / 2 << g_9150)) >> 3;
    }
    switch (d) {
    case 1:
        if (b > g_9324)
            return;
        p = g_1df8[b][c].f04.pt;
        break;
    case 2:
        if (g_6098[c].f84)
            k = 0;
        else
            k = 1;
        p.y = g_6098[c].y1[k][0];
        p.x = g_6098[c].x1[k][0];
        break;
    case 3:
        p = g_5144;
        break;
    case 0:
        p.y = -6000;
        p.x = -6000;
        break;
    }
    saved = p;
    r = fn_10_7896(d, saved);
    if (r == -1)
        return;
    q.p.f0 = 1;
    q.p.f2 = 1;
    if (d != 0) {
        p = fn_08_29ea(p);
        if (g_9156 != 1) {
            dd.x = p.x - g_1df8[g_9324][g_9646].f00;
            dd.y = p.y - g_1df8[g_9324][g_9646].f02;
            p.x = (dd.x * 2 >> g_9156) + g_1df8[g_9324][g_9646].f00;
            p.y = (dd.y * 2 >> g_9156) + g_1df8[g_9324][g_9646].f02;
        }
    }
    if (b == g_9324 && c == g_9646 && g_7148[g_9646].flag)
        ((FP3C5C)g_fp_3c5c)(0x69, p, 1, q.p.f0, q.p.f2, g_90ea, g_1e50, "");
    if (((FP3C5C)g_fp_3c5c)(a, p, r, q.p.f0, q.p.f2, g_90ea, g_1e50, e)) {
        g_921c = a;
        g_928c = b;
        g_928e = c;
        g_9290 = d;
        g_3b98 = saved;
        g_9226 = r;
    }
}

/* Per-frame sound update [inferred]: fires the follow-up sound g_9292 when
 * g_3c88 is due, then repositions the last sound through g_fp_3c58. */
/* @addr 10:7b48 */
void far fn_10_7b48(void)
{
    POINT p;
    PAIR q;
    POINT dd;
    int k;

    q.f0 = (g_1df8[g_9324][g_9646].f04.pt.x - ((int)g_90ea / 2 << g_9150)) >> 3;
    q.f2 = (g_1df8[g_9324][g_9646].f04.pt.y - (g_90ec / 2 << g_9150)) >> 3;
    if (g_3c88 && GetCurrentTime() > g_3c88) {
        if (g_920a > 1 || (g_9218 == 14 && g_921a == g_9646)
            || (g_921c == g_9216 && g_9218 == g_928c && g_921a == g_928e)
            || g_9292 == 0x66 || g_9216 >= 0x38) {
            fn_10_754a(0x69, g_928c, g_928e, g_9290);
            fn_10_754a(g_9292, g_928c, g_928e, g_9290);
            g_9216 = 0;
        }
        g_3c88 = 0;
        g_9292 = 0;
    }
    switch (g_9290) {
    case 1:
        if (g_928c > g_9324)
            return;
        p = g_1df8[g_928c][g_928e].f04.pt;
        if (g_928c == 5)
            k++;
        break;
    case 2:
        if (g_6098[g_928e].f84)
            k = 0;
        else
            k = 1;
        p.y = g_6098[g_928e].y1[k][0];
        p.x = g_6098[g_928e].x1[k][0];
        break;
    case 3:
        p = g_5144;
        break;
    case 0:
        p.y = -6000;
        p.x = -6000;
        break;
    case 4:
        return;
    }
    q.f0 = 1;
    q.f2 = 1;
    if (g_9290 != 0) {
        p = fn_08_29ea(p);
        if (g_9156 != 1) {
            dd.x = p.x - g_1df8[g_9324][g_9646].f00;
            dd.y = p.y - g_1df8[g_9324][g_9646].f02;
            p.x = (dd.x * 2 >> g_9156) + g_1df8[g_9324][g_9646].f00;
            p.y = (dd.y * 2 >> g_9156) + g_1df8[g_9324][g_9646].f02;
        }
    }
    if (g_fp_3c58(p, q.f0, q.f2, g_90ea))
        g_3b98 = p;
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

/* Runs dialog/screen a through g_fp_3c64 [inferred]. Modes 8 and 10 first
 * pass today's date (days since 1993); mode 1 reloads the INI player
 * settings. -100 is mode 6 owned by g_9532. Returns the dialog's result. */
/* @addr 10:82a2 */
int far fn_10_82a2(int a)
{
    int r;
    char buf[20];
    int v1;
    int v0;
    HWND hwnd;

    if (a != 10)
        fn_10_7480(-2, 1);
    v0 = 0;
    if (a == 8 || a == 10) {
        struct tm *tm;
        int yr;
        int day;
        time_t t;

        time(&t);
        tm = localtime(&t);
        yr = tm->tm_year - 93;
        v0 = day = yr * 365 + tm->tm_yday;
        g_fp_3c64(0, 0, tm->tm_mday, tm->tm_mon + 1, tm->tm_year, 0, 15);
        if (a == 10) {
            fn_10_80dc();
            g_fp_3c64(0, 0, 0, day, 0x9d, 0, 9);
            fn_10_81b6();
            fn_10_885e(0);
            return 1;
        }
    }
    if (a == -100) {
        a = 6;
        hwnd = g_9532;
    } else {
        hwnd = g_0016;
    }
    if (a == 5 || a == 7) {
        v1 = g_90f4;
        v0 = flow_interactive;
    } else if (a == 6) {
        v1 = flow_interactive;
    } else if (a == 8) {
        if (g_922a)
            v1 = 0;
        else
            v1 = g_9224;
    } else {
        v1 = 0;
    }
    if (a == 6 || a == 1 || a == 4) {
        if (g_920c == 0)
            v0 = 1;
        else if (g_920c == 3)
            v0 = 3;
        else
            v0 = 0;
    }
    r = g_fp_3c64(hwnd, g_39e8[5], g_920e, v1, v0, 0, a);
    g_1e50 = GetCurrentTime();
    g_3b94 = GetCurrentTime() + 500;
    fn_10_7f88();
    if (a == 5 || a == 6) {
        fn_10_7480(-3, 1);
        return r;
    }
    if (a == 12) {
        if (r) {
            fn_10_744c(0x13);
            fn_10_80a8();
        }
        return r;
    }
    if (r) {
        g_8f64 = 0;
        g_6e28 = GetCurrentTime() + 40000;
        if (a == 1) {
            int flag;
            int i;

            g_9134 = GetPrivateProfileInt(g_9690, "PlayMode", 0, g_96a9);
            GetPrivateProfileString(g_9690, "ThePlayer", "", g_380c, 20, g_96a9);
            GetPrivateProfileString(g_9690, "Restore", "", buf, 9, g_96a9);
            flag = 0;
            for (i = 0; lstrlen(buf) > i; i++)
                if (buf[i] == ' ')
                    flag = 1;
            if (flag) {
                g_939a = fn_10_804c(1);
                g_939e = fn_10_804c(0);
            }
        }
        g_104e = 0;
        g_104c = 0;
        g_951c = 0;
        GetPrivateProfileString(g_9690, "Drive", "C", buf, 20, g_96a9);
        g_94ac = buf[0] - 'C';
        g_9516 = 0;
    } else {
        if (g_95b8 < 4)
            g_6e28 = GetCurrentTime();
        else
            g_6e28 = GetCurrentTime() + 15000;
    }
    fn_10_7480(-3, 1);
    return r;
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

/* Rescales a bitmap for the display scale g_9156 (1 = as is): surface a's
 * bitmap, or bitmap c when a is -1 (then returns the new bitmap). In scale
 * mode 2 surfaces 7 and 6 are first copied to 9 and 8. b is unused. */
/* @addr 10:6308 */
int far fn_10_6308(int a, int b, int c, int d)
{
    HDC dc2;
    HDC dc1;
    HBITMAP ob2;
    HBITMAP nbm;
    HBITMAP ob1;
    HPALETTE pal2;
    HPALETTE pal1;
    BITMAP bmp;
    int unused;
    int w;
    int h;

    if (!g_39e8[a] && a != -1)
        return 0;
    if (g_9156 == 1 && d != 2)
        return c;
    if (a != -1)
        c = g_3ad0[a];
    if (g_9156 == 2) {
        if (a == 9)
            return 0;
        if (a == 8)
            return 0;
        if (a == 7) {
            fn_10_0552(9, 1);
            g_39e8[9] = g_39e8[7];
            g_3ad0[9] = g_3ad0[7];
            g_3974[9] = g_3974[7];
            g_3a5c[9] = g_3a5c[7];
            g_0740 = 1;
        }
        if (a == 6) {
            fn_10_0552(8, 1);
            g_39e8[8] = g_39e8[6];
            g_3ad0[8] = g_3ad0[6];
            g_3974[8] = g_3974[6];
            g_3a5c[8] = g_3a5c[6];
            g_0740 = 1;
        }
    }
    GetObject(c, sizeof(BITMAP), &bmp);
    w = bmp.bmWidth;
    h = bmp.bmHeight;
    if (a != -1) {
        dc1 = CreateCompatibleDC(g_39e8[a]);
        dc2 = CreateCompatibleDC(g_39e8[a]);
        nbm = CreateCompatibleBitmap(g_39e8[a], (w << g_9156) >> 1,
                                     (h << g_9156) >> 1);
        if ((a != 7 && a != 6) || g_9156 != 2) {
            SelectObject(g_39e8[a], g_3974[a]);
            if (g_920e && g_3a5c[a])
                SelectPalette(g_39e8[a], g_3a5c[a], 0);
            DeleteDC(g_39e8[a]);
        } else {
            SelectObject(g_39e8[a], g_3974[a]);
        }
    } else {
        dc1 = CreateCompatibleDC(g_13dc);
        dc2 = CreateCompatibleDC(g_13dc);
        nbm = CreateCompatibleBitmap(g_13dc, (w << g_9156) >> 1,
                                     (h << g_9156) >> 1);
    }
    if (g_920e)
        pal1 = SelectPalette(dc1, g_920e, 0);
    if (g_920e)
        pal2 = SelectPalette(dc2, g_920e, 0);
    ob2 = SelectObject(dc2, c);
    ob1 = SelectObject(dc1, nbm);
    PatBlt(dc1, 0, 0, (w << g_9156) >> 1, (h << g_9156) >> 1, BLACKNESS);
    if (a != 8 && a != 6)
        SetStretchBltMode(dc1, 3);
    else
        SetStretchBltMode(dc1, 2);
    fn_10_9962(1, dc1, 0, 0, (w << g_9156) >> 1, (h << g_9156) >> 1, dc2,
               0, 0, w, h, SRCCOPY);
    SelectObject(dc2, ob2);
    if (g_920e)
        SelectPalette(dc2, pal2, 0);
    DeleteDC(dc2);
    if ((a != 7 && a != 6) || g_9156 != 2) {
        DeleteObject(c);
    } else if (a == 7) {
        g_3974[9] = SelectObject(g_39e8[9], g_3ad0[9]);
    } else if (a == 6) {
        g_3974[8] = SelectObject(g_39e8[8], g_3ad0[8]);
    }
    if (a != -1) {
        g_39e8[a] = dc1;
        g_3ad0[a] = nbm;
        g_3974[a] = ob1;
        g_3a5c[a] = pal1;
        return 0;
    }
    SelectObject(dc1, ob1);
    if (g_920e)
        SelectObject(dc1, pal1);
    DeleteDC(dc1);
    return nbm;
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
    d = fn_08_285a(&i, &j, pt, g_1df8[g_9324][g_9646].f04.l);
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

/* Loads bitmap a through g_fp_3c3c and, when b >= 16, builds a 16 x 2
 * cell sheet of mirrored copies of its cells [inferred]. */
/* @addr 10:7032 */
int far fn_10_7032(int a, int b, int c)
{
    HBITMAP bm;
    HBITMAP ob1;
    HBITMAP nbm;
    HBITMAP ob2;
    HDC dc1;
    HDC dc2;
    HPALETTE pal1;
    HPALETTE pal2;
    int i;
    int j;
    int s;
    int t;

    bm = g_fp_3c3c(g_920e, 1, 1, a, 5, c);
    if (subgame_active) {
        s = g_9156 * 6 + 3;
        t = 9;
    } else {
        s = (9 << g_9156) >> 1;
        bm = fn_10_6308(-1, -1, bm, -1);
        t = s;
    }
    if (b < 16)
        return bm;
    dc1 = CreateCompatibleDC(g_13dc);
    if (g_920e)
        pal1 = SelectPalette(dc1, g_920e, 0);
    ob1 = SelectObject(dc1, bm);
    dc2 = CreateCompatibleDC(g_13dc);
    nbm = CreateCompatibleBitmap(g_13dc, s << 4, s * 2);
    if (g_920e)
        pal2 = SelectPalette(dc2, g_920e, 0);
    ob2 = SelectObject(dc2, nbm);
    PatBlt(dc2, 0, 0, s << 4, s * 2, BLACKNESS);
    fn_10_9962(0, dc2, 0, 0, s * 5, s * 2, dc1, 0, 0, t * 5, t * 2, SRCCOPY);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            if (i == 0) {
                fn_10_9962(1, dc2, s << 3, (j + 1) * s - 1, s, -s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
            } else if (i == 4) {
                fn_10_9962(1, dc2, s * 13 - 1, s * j, -s, s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
            } else {
                fn_10_9962(1, dc2, (8 - i) * s, (j + 1) * s - 1, s, -s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
                fn_10_9962(1, dc2, (i + 9) * s - 1, (j + 1) * s - 1, -s, -s,
                           dc1, t * i, t * j, t, t, SRCCOPY);
                fn_10_9962(1, dc2, (17 - i) * s - 1, s * j, -s, s, dc1,
                           t * i, t * j, t, t, SRCCOPY);
            }
        }
    }
    if (dc1) {
        if (g_920e)
            SelectPalette(dc1, pal1, 0);
        SelectObject(dc1, ob1);
        if (bm)
            DeleteObject(bm);
        DeleteDC(dc1);
        dc1 = bm = 0;
    }
    if (dc2) {
        if (g_920e)
            SelectPalette(dc2, pal2, 0);
        SelectObject(dc2, ob2);
        DeleteDC(dc2);
        dc2 = 0;
    }
    return nbm;
}

/* Zoom change [inferred] by d (-1/+1): new level d + g_9156 must be 0..2.
 * Rescales the sprites (fn_10_6308), every object's size fields
 * (g_1df8[type][n].f22/f24, f12), on the largest zoom with g_8fe8 the
 * ships ("Loading Ship # ", strings built but not shown) and the 0x34-byte
 * records, then the class records' sizes; saves "Size" (and "SetSize" when
 * a person plays) to the INI file. The early MessageBeep return leaves
 * g_931e at 0 (kept). */
/* @addr 10:9a2a */
void far fn_10_9a2a(int d)
{
    int i;
    int j;
    int nz;
    int v;
    int w;
    int res;
    int saved;
    int unused;         /* never used; keeps the frame */
    int flag;
    int a;
    int b;
    int t;
    char buf3[8];
    char buf1[40];
    char buf2[30];

    if (g_90f4 != 1 || subgame_active) {
        g_103c = 1;
        return;
    }
    saved = g_931e;
    g_931e = 0;
    if (d + g_9156 > 2 || d + g_9156 < 0) {
        MessageBeep(0);
        return;
    }
    if (g_934c == 0) {
        g_9518 = 1;
        g_934c = CreateDialog(g_9212, MAKEINTRESOURCE(0x65), g_0016, fn_09_90fe);
    }
    if ((nz = d + g_9156) == 1 && d == 1)
        g_103a = flag = 1;
    else if (nz == 1 && d == -1 && g_8fe8 && !g_90f0)
        g_103a = flag = 1;
    else
        flag = 0;
    g_9156 = d + 1;
    if (!flag) {
        for (i = 0; i < 0x3a; i++) {
            if (i == 0x20)
                continue;
            if (g_9156 == 2 && i > 0x27 && i < 0x30 && flag)
                continue;
            fn_10_6308(i, -1, -1, -2);
        }
    } else {
        for (i = 0xe; i < g_92ec + 0xe; i++)
            fn_10_6308(i, -1, -1, -2);
    }
    for (i = 0; i < g_9408; i++)
        if (g_4e94[i])
            g_4e94[i] = fn_10_6308(-1, -1, g_4e94[i], -1);
    g_9156 = nz;
    g_9150 = 4 - nz;
    fn_10_0552(0x22, 1);
    fn_10_5c42();
    for (i = g_9326; i <= g_9324; i++) {
        for (j = 0; j < (&g_92ec)[i]; j++) {
            if (g_9156 == 0 && i == g_9324 && (g_1df8[i][j].f22 & 1)) {
                g_1df8[i][j].f22++;
                g_1df8[i][j].f24--;
            }
            g_1df8[i][j].f22 = g_1df8[i][j].f22 << (d + 1) >> 1;
            g_1df8[i][j].f24 = g_1df8[i][j].f24 << (d + 1) >> 1;
            if (i == 3 && d == 1 && g_9156 > 0
                && g_1df8[i][j].f22 < 12 << g_9156)
                g_1df8[i][j].f24 = 4;
            if (i == 3 && g_9156 == 1 && g_1df8[i][j].f22 < 12 << g_9156
                && g_8fe8 && !g_90f0)
                g_1df8[i][j].f24 = 4;
            g_1df8[i][j].f12 = g_1df8[i][j].f24;
        }
    }
    if (flag || g_9156 == 2 && g_8fe8) {
        for (i = 0x30; i < 0x3a; i++)
            fn_10_0552(i, 1);
        for (i = 0; i <= g_9316; i++) {
            fn_10_0552(i + 0x28, 1);
            a = g_7092[i].faa;
            b = g_7092[i].fab;
            lstrcpy(buf1, "Loading Ship # ");
            fn_06_0f1a(i, buf2);
            lstrcat(buf1, buf2);
            fn_14_11a8(i);
            if (g_7092[i].fd4 != -1) {
                v = g_6e24[g_7092[i].fd4].f7a;
                g_96d2[g_7092[i].f4c].f2a = v;
                w = g_6e24[g_7092[i].fd4].f7b;
            } else {
                v = g_1df8[g_9324][i].f22;
                g_96d2[g_7092[i].f4c].f2a = v;
                w = g_1df8[g_9324][i].f24;
            }
            g_92e4 = 1;
            g_1df8[g_9324][i].f22 = v << g_9156 >> 1;
            g_1df8[g_9324][i].f24 = w << g_9156 >> 1;
            g_1df8[g_9324][i].f12 = g_1df8[g_9324][i].f24;
            if (!a)
                fn_08_2cd8(i, 0);
            if (!b)
                fn_08_2cd8(i, 1);
            g_92e4 = 0;
        }
        for (i = 0x17; i < 0x1c; i++) {
            fn_10_0552(i, 1);
            g_381a[i].f4 = g_381a[i].f0 = g_381a[i].f2 = -1;
        }
        for (i = 0; i < g_9416; i++) {
            if (g_3d5a[i].f12 == 2) {
                if (g_3d5a[i].f26 <= 2)
                    g_3d5a[i].f12 = 1;
                else if (g_3d5a[i].f26 >= 5) {
                    if (g_4d92[g_3d5a[i].f26].f01 == -1)
                        t = 1;
                    else
                        t = 0;
                    res = fn_10_18b0(g_3d5a[i].f18, g_3d5a[i].f16, g_3d5a[i].f20,
                                     t, g_3d5a[i].f26);
                    g_1e18[i].f24 = g_4d92[g_3d5a[i].f26].f07 << g_9156 >> 1;
                    g_1e18[i].f22 = g_4d92[g_3d5a[i].f26].f06 << g_9156 >> 1;
                    g_1e18[i].f20 = g_1e18[i].f22 << 3;
                    if (g_3d5a[i].id > 0 && g_2f4c[g_3d5a[i].id].f12)
                        fn_10_533a(g_3d5a[i].id);
                    g_3d5a[i].f14 = res;
                }
            }
        }
    }
    if (flag) {
        fn_10_9568();
        fn_10_0552(0xd, 1);
        fn_10_5b30();
        for (i = 0; i < g_92ec; i++)
            BitBlt(g_3a02, i * 0x26 + 6, 6, 0x20, 0x20, g_3a28, i << 5, 0, SRCCOPY);
        fn_09_94ba();
        for (i = 0; i < g_92ec; i++)
            fn_07_233c(0, i, 0);
    }
    for (i = 0; i <= g_9316; i++) {
        v = g_96d2[g_7092[i].f4c].f2a;
        if (v & 1)
            w = 5;
        else
            w = 6;
        if (g_9156 == 0 && (v & 1)) {
            v++;
            w = 4;
        }
        g_96d2[g_7092[i].f4c].f02 = g_96d2[g_7092[i].f4c].f00 = (v >> g_9156) * 2 / 2;
        if (g_96d2[g_7092[i].f4c].f04 < 0)
            g_96d2[g_7092[i].f4c].f04 = 4 - g_96d2[g_7092[i].f4c].f04 - v / 2;
        fn_10_1502(g_7092[i].f4c);
        fn_10_5d3c(i);
    }
    fn_06_0f1a(g_9156, buf3);
    WritePrivateProfileString(g_9690, "Size", buf3, g_96a9);
    if (flow_interactive)
        WritePrivateProfileString(g_9690, "SetSize", buf3, g_96a9);
    if (g_934c) {
        g_8f64 = 0;
        DestroyWindow(g_934c);
        g_9518 = 0;
        g_934c = 0;
        PostMessage(g_0016, 0x978, 0, 0L);
    }
    PatBlt(g_13dc, 0, 0, g_90ea, g_90ec, BLACKNESS);
    g_931e = saved;
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

/* Builds surfaces 1 and 2: blocks from bitmaps 0xd2 / 0x334 (colour) and
 * the monochrome BW_BLOCKS / BW_MBLOCKS, each with mirrored copies, and
 * the OUT_SIGN marks on surface 1 [inferred]. */
/* @addr 10:3ea2 */
void far fn_10_3ea2(void)
{
    int u4;
    int u6;
    HBITMAP ob1;
    int ua;
    HBITMAP ob2;
    HBITMAP bm1;
    int u10;
    HBITMAP bm2;
    HDC dc1;
    int u16;
    HDC dc2;
    HPALETTE pal1;
    HPALETTE pal2;
    int i;
    int j;
    int w;
    int m;
    int u26;
    int u28;
    BITMAP bmp;
    int u;

    if (g_39e8[1])
        return;
    for (i = 0; i < 2; i++) {
        g_1e18->f24 = 6;
        m = g_1e18->f24;
        w = g_1e18->f22 = 0x22;
        u = (w + m) * 2;
        g_39e8[i + 1] = CreateCompatibleDC(g_13dc);
        dc1 = CreateCompatibleDC(g_13dc);
        dc2 = CreateCompatibleDC(g_13dc);
        if (i == 0) {
            bm1 = fn_10_6c02(0xd2, 3, -1);
            bm2 = fn_10_6c02(0x334, 0, -1);
            GetObject(bm2, sizeof(BITMAP), &bmp);
            g_3ad0[1] = CreateCompatibleBitmap(g_13dc, w * 4 + m * 5, m * 2 + w);
        } else {
            bm1 = fn_10_6d38("BW_BLOCKS");
            bm2 = fn_10_6d38("BW_MBLOCKS");
            g_3ad0[2] = CreateBitmap(w * 4 + m * 5, m * 2 + w, 1, 1, NULL);
        }
        ob1 = SelectObject(dc1, bm1);
        ob2 = SelectObject(dc2, bm2);
        g_3974[i + 1] = SelectObject(g_39e8[i + 1], g_3ad0[i + 1]);
        if (i == 0 && g_920e) {
            pal1 = SelectPalette(dc1, g_920e, 0);
            pal2 = SelectPalette(dc2, g_920e, 0);
            g_3a5c[1] = SelectPalette(g_39e8[1], g_920e, 0);
        }
        PatBlt(g_39e8[i + 1], 0, 0, w * 4 + m * 5, m * 2 + w, BLACKNESS);
        for (j = 0; j < 2; j++) {
            BitBlt(g_39e8[i + 1], m, m, w, w, dc1, 0, 0, SRCCOPY);
            BitBlt(g_39e8[i + 1], w * 2 + m * 3, m, w, w, dc2, 0, 0, SRCCOPY);
            BitBlt(g_39e8[i + 1], m * 4 + w * 3, m, w, w, dc2, w, 0, SRCCOPY);
        }
        if (dc1) {
            SelectObject(dc1, ob1);
            if (pal1)
                SelectPalette(dc1, pal1, 0);
            DeleteDC(dc1);
            dc1 = 0;
            if (bm1) {
                DeleteObject(bm1);
                bm1 = 0;
            }
        }
        if (dc2) {
            SelectObject(dc2, ob2);
            if (pal2)
                SelectPalette(dc2, pal2, 0);
            DeleteDC(dc2);
            dc2 = 0;
            if (bm2) {
                DeleteObject(bm2);
                bm2 = 0;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        SetStretchBltMode(g_39e8[i + 1], 3);
        fn_10_9962(0, g_39e8[i + 1], (m + w) * 2 - 1, m, -w, w, g_39e8[i + 1],
                   m, m, w, w, SRCCOPY);
        fn_10_9962(0, g_39e8[i + 1], (m + w) * 2 - 1, m, 5 - w, w,
                   g_39e8[i + 1], (m + 2) * 2 + w, m, w - 5, w, SRCCOPY);
    }
    bm1 = fn_10_6d38("OUT_SIGN");
    dc1 = CreateCompatibleDC(g_13dc);
    ob1 = SelectObject(dc1, bm1);
    if (g_920e)
        pal1 = SelectPalette(dc1, g_920e, 0);
    BitBlt(g_39e8[1], m + 2, m + 10, 26, 13, dc1, 26, 0, SRCCOPY);
    BitBlt(g_39e8[1], (m + 3) * 2 + w, m + 10, 26, 13, dc1, 26, 0, SRCCOPY);
    SelectObject(dc1, ob1);
    if (pal1)
        SelectPalette(dc1, pal1, 0);
    DeleteDC(dc1);
    if (bm1) {
        DeleteObject(bm1);
        bm1 = 0;
    }
    fn_10_6308(1, -1, -1, -1);
    fn_10_6308(2, -1, -1, -1);
}

/* Builds surface 22 (nine 37-pixel cells of bitmap 0x154) or, in the
 * sub-game, the scaled strip g_9656 [inferred]. */
/* j is a dead store: CL drops the load but keeps its `les bx,[g_1e1c]`. */
/* @addr 10:58ce */
void far fn_10_58ce(int a)
{
    int i;
    int j;
    int w;
    int m;
    int v;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;

    if (g_39e8[22] && !subgame_active)
        return;
    if (g_9656 && subgame_active)
        return;
    j = g_1e1c->f00;
    w = 0x25;
    m = 5;
    if (g_8fe8)
        v = 3;
    else
        v = 0;
    g_928a = fn_10_6c02(0x154, v, -1);
    dc = CreateCompatibleDC(g_13dc);
    ob = SelectObject(dc, g_928a);
    if (g_920e)
        pal = SelectPalette(dc, g_920e, 0);
    if (!subgame_active) {
        g_3ad0[22] = CreateCompatibleBitmap(g_13dc, w * 9 + m * 10, m * 2 + w);
        g_39e8[22] = CreateCompatibleDC(g_13dc);
        g_3974[22] = SelectObject(g_39e8[22], g_3ad0[22]);
        if (g_920e)
            g_3a5c[22] = SelectPalette(g_39e8[22], g_920e, 0);
        PatBlt(g_39e8[22], 0, 0, w * 9 + m * 10, m * 2 + w, BLACKNESS);
        for (i = 0; i < 9; i++)
            BitBlt(g_39e8[22], (m + w) * i + m, m, w, w, dc, w * i, 0, SRCCOPY);
    } else {
        g_9658 = CreateCompatibleBitmap(g_13dc, 0xfc / (4 - g_9156 * 3),
                                        0x1c / (4 - g_9156 * 3));
        g_9656 = CreateCompatibleDC(g_13dc);
        g_965a = SelectObject(g_9656, g_9658);
        if (g_920e)
            g_965c = SelectPalette(g_9656, g_920e, 0);
        PatBlt(g_9656, 0, 0, 0xfc / (4 - g_9156 * 3), 0x1c / (4 - g_9156 * 3),
               BLACKNESS);
        SetStretchBltMode(g_9656, 3);
        fn_10_9962(0, g_9656, 0, 0, 0xfc / (4 - g_9156 * 3),
                   0x1c / (4 - g_9156 * 3), dc, 0, 0, w * 9, w, SRCCOPY);
    }
    SelectObject(dc, ob);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(g_928a);
    if (a)
        fn_10_6308(22, -1, -1, -1);
}

/* Builds surface 4 for the current g_9214 (cached in g_17c0): five cells
 * of bitmap 0x10e, or one or two frames of 0x110 / 0x112 / 0x116 / 0x48. */
/* @addr 10:565a */
void far fn_10_565a(void)
{
    int i;
    int w;
    int m;
    int id;
    int n;
    int k;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;
    BITMAP bmp;
    static int last;    /* DS:17c0 */

    if (g_39e8[4]) {
        if (last == g_9214)
            return;
        fn_10_0552(4, 1);
    }
    n = 1;
    last = g_9214;
    if (g_9214 == 0) {
        id = 0x10e;
        w = 0x24;
        m = 6;
    } else {
        if (g_9214 == 1)
            id = 0x110;
        if (g_9214 == 2)
            id = 0x112;
        if (g_9214 == 3) {
            id = 0x116;
            n = 2;
        }
        if (g_9214 == 4) {
            id = 0x48;
            n = 2;
            fn_10_6ea0(9);
        }
        w = 0x1e;
        m = 4;
    }
    for (k = 0; k < n; k++) {
        g_928a = fn_10_6c02(id - k * 2, 0, -1);
        dc = CreateCompatibleDC(g_13dc);
        ob = SelectObject(dc, g_928a);
        if (g_920e)
            pal = SelectPalette(dc, g_920e, 0);
        if (k == 0) {
            if (g_9214 == 0)
                g_3ad0[4] = CreateCompatibleBitmap(g_13dc, w * 5 + m * 6, m * 2 + w);
            else if (g_9214 == 3 || g_9214 == 4)
                g_3ad0[4] = CreateCompatibleBitmap(g_13dc, w * 2 + m * 3, m * 2 + w);
            else
                g_3ad0[4] = CreateCompatibleBitmap(g_13dc, m * 2 + w, m * 2 + w);
            g_39e8[4] = CreateCompatibleDC(g_13dc);
            g_3974[4] = SelectObject(g_39e8[4], g_3ad0[4]);
            if (g_920e)
                g_3a5c[4] = SelectPalette(g_39e8[4], g_920e, 0);
        }
        if (g_9214 == 0) {
            PatBlt(g_39e8[4], 0, 0, w * 5 + m * 6, m * 2 + w, BLACKNESS);
            for (i = 0; i < 5; i++)
                BitBlt(g_39e8[4], (m + w) * i + m, m, w, w, dc, w * i, 0, SRCCOPY);
        } else {
            PatBlt(g_39e8[4], (m * 2 + w) * k, 0, m * 2 + w, m * 2 + w, BLACKNESS);
            BitBlt(g_39e8[4], (m + w) * k + m, m, w - 1, w - 1, dc, 0, 0, SRCCOPY);
        }
        SelectObject(dc, ob);
        if (pal)
            SelectPalette(dc, pal, 0);
        DeleteDC(dc);
        DeleteObject(g_928a);
    }
    fn_10_6308(4, -1, -1, -1);
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

/* Builds surfaces 6..9: eighteen rock frames from the monochrome ROCKS
 * bitmap (6, and 8 at size 21) and coloured ones (7, 9) from bitmap 0x32
 * when g_90f0 or g_8fe8 is set, else grey through a MERGECOPY brush. */
/* @addr 10:3a2e */
void far fn_10_3a2e(void)
{
    HBRUSH br1;
    HBRUSH br2;
    HBITMAP ob2;
    HBITMAP ob1;
    int u0c;
    HBITMAP bm2;
    HBITMAP bm1;
    int u12;
    HDC dc2;
    HDC dc1;
    int u18;
    HPALETTE pal1;
    int u1c;
    BITMAP bmp;
    int i;
    int u2e;
    int a;
    int m;
    int b;
    int u36;

    if (g_39e8[6])
        return;
    a = 0x2b;
    b = 0x15;
    m = 5;
    if (g_90f0 || g_8fe8) {
        bm1 = fn_10_6c02(0x32, 3, -1);
        dc1 = CreateCompatibleDC(g_13dc);
        ob1 = SelectObject(dc1, bm1);
        if (g_920e)
            pal1 = SelectPalette(dc1, g_920e, 0);
    }
    g_0740 = 0;
    bm2 = fn_10_6d38("ROCKS");
    dc2 = CreateCompatibleDC(g_13dc);
    ob2 = SelectObject(dc2, bm2);
    g_3ad0[6] = CreateBitmap(m * 19 + a * 18, m * 2 + a, 1, 1, NULL);
    g_3ad0[7] = CreateCompatibleBitmap(g_13dc, m * 19 + a * 18, m * 2 + a);
    g_3ad0[8] = CreateBitmap(b * 18 + m * 19, m * 2 + b, 1, 1, NULL);
    g_3ad0[9] = CreateCompatibleBitmap(g_13dc, b * 18 + m * 19, m * 2 + b);
    for (i = 0; i < 2; i++) {
        g_39e8[i + 6] = CreateCompatibleDC(g_13dc);
        g_3974[i + 6] = SelectObject(g_39e8[i + 6], g_3ad0[i + 6]);
        if (g_920e && i)
            g_3a5c[7] = SelectPalette(g_39e8[7], g_920e, 0);
        PatBlt(g_39e8[i + 6], 0, 0, m * 19 + a * 18, m * 2 + a, BLACKNESS);
    }
    for (i = 0; i < 2; i++) {
        g_39e8[i + 8] = CreateCompatibleDC(g_13dc);
        g_3974[i + 8] = SelectObject(g_39e8[i + 8], g_3ad0[i + 8]);
        if (g_920e && i)
            g_3a5c[9] = SelectPalette(g_39e8[9], g_920e, 0);
        PatBlt(g_39e8[i + 8], 0, 0, b * 18 + m * 19, m * 2 + b, BLACKNESS);
    }
    for (i = 0; i < 18; i++) {
        BitBlt(g_39e8[6], (m + a) * i + m, m, a, a, dc2, a * i, 0, SRCCOPY);
        SetStretchBltMode(g_39e8[8], 2);
        fn_10_9962(0, g_39e8[8], (b + m) * i + m, m, b, b, dc2, a * i, 0, a, a,
                   SRCCOPY);
    }
    fn_10_740c();
    if (g_90f0 || g_8fe8) {
        for (i = 0; i < 18; i++) {
            BitBlt(g_39e8[7], (m + a) * i + m, m, a, a, dc1, a * i, 0, SRCCOPY);
            SetStretchBltMode(g_39e8[9], 3);
            fn_10_9962(0, g_39e8[9], (b + m) * i + m, m, b, b, dc1, a * i, 0,
                       a, a, SRCCOPY);
        }
    } else {
        br1 = SelectObject(g_39e8[7], CreateSolidBrush(RGB(128, 128, 128)));
        br2 = SelectObject(g_39e8[9], CreateSolidBrush(RGB(128, 128, 128)));
        BitBlt(g_39e8[7], 0, 0, m * 19 + a * 18, m * 2 + a, g_39e8[6], 0, 0,
               MERGECOPY);
        BitBlt(g_39e8[9], 0, 0, b * 18 + m * 19, m * 2 + b, g_39e8[8], 0, 0,
               MERGECOPY);
        DeleteObject(SelectObject(g_39e8[7], br1));
        DeleteObject(SelectObject(g_39e8[9], br2));
    }
    if (g_90f0 || g_8fe8) {
        if (pal1)
            SelectPalette(dc1, pal1, 0);
        SelectObject(dc1, ob1);
        DeleteDC(dc1);
        if (bm1)
            DeleteObject(bm1);
    }
    SelectObject(dc2, ob2);
    DeleteDC(dc2);
    if (bm2)
        DeleteObject(bm2);
    fn_10_6308(7, -1, -1, -1);
    fn_10_6308(6, -1, -1, -1);
    fn_10_6308(9, -1, -1, -1);
    fn_10_6308(8, -1, -1, -1);
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

/* Builds surface 30 for the race: four markers of bitmap 0x1a4 in a row. */
/* @addr 10:49d4 */
void far race_marker_strip(void)
{
    int w;
    int h;
    int i;
    HBITMAP bm;
    HBITMAP ob;
    HDC dc;
    HPALETTE pal;

    if (!g_39e8[30]) {
        bm = fn_10_6c02(0x1a4, 0, -1);
        w = 14;
        h = 4;
        dc = CreateCompatibleDC(g_13dc);
        ob = SelectObject(dc, bm);
        if (g_920e)
            pal = SelectPalette(dc, g_920e, 0);
        g_3ad0[30] = CreateCompatibleBitmap(g_13dc, w * 4 + h * 5, h * 2 + w);
        g_39e8[30] = CreateCompatibleDC(g_13dc);
        g_3974[30] = SelectObject(g_39e8[30], g_3ad0[30]);
        if (g_920e)
            g_3a5c[30] = SelectPalette(g_39e8[30], g_920e, 0);
        PatBlt(g_39e8[30], 0, 0, w * 4 + h * 5, h * 2 + w, BLACKNESS);
        for (i = 0; i < 4; i++)
            BitBlt(g_39e8[30], (h + w) * i + h, h, w, w, dc, i * w, 0, SRCCOPY);
        SelectObject(dc, ob);
        if (g_920e)
            SelectPalette(dc, pal, 0);
        DeleteDC(dc);
        DeleteObject(bm);
        fn_10_6308(30, -1, -1, -1);
    }
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

/* Formats a pilot record's summary lines into dst with fn_10_a332 (string
 * ids 0xbb8..0xbba, 0xbd3) [inferred: a saved-game / champion entry].
 * Divides the record's time by 36 in place [sic]. */
/* @addr 10:a118 */
void far pascal fn_10_a118(REC_PILOT far *src, LPSTR dst)
{
    int mins;
    int secs;
    int v;
    int sum;
    int i;
    int same;
    char line[60];
    char name[20];

    src->time /= 36;
    mins = (int)src->time / 60;
    secs = (int)src->time - mins * 60;
    v = src->f162;
    if (src->f15e < 100) {
        if (v < -15000)
            v = (unsigned)v / 10;
        else
            v = v / 10;
    } else {
        src->f15e -= 100;
    }
    for (i = sum = 0; i < 8; i++)
        sum += src->f146[i];
    lstrcpy(name, src->name);
    same = lstrcmp(src->name, g_380c) == 0;
    fn_11_3fd4(name, 1);
    if (src->f32 == src->f160) {
        if (src->f160 == 1)
            LoadString(g_9212, 0x9c7, line, 60);
        else
            LoadString(g_9212, 0x9c5, line, 60);
    } else if (src->f160 == 0) {
        LoadString(g_9212, 0x9c6, line, 60);
    } else {
        fn_10_a332(line, 0x9c4, 1, src->f160);
    }
    fn_10_a332(dst, 0xbb8, 1, 1, src->f24, mins, 0x9c9, secs, 0x9c8,
               src->f32, 0x13e, (LPSTR)line);
    if (src->f15a || src->f15c)
        fn_10_a332(dst, 0xbb9, 0, src->f156 + src->f158, 0x9d3, src->f15a,
                   src->f15a, 0x9d3, src->f15c, src->f15c, 0x9d3);
    fn_10_a332(dst, 0xbba, 0, v / 10, fn_09_88ba(v % 10), src->f15e + 0x137);
    if (g_9460)
        fn_10_a332(dst, 0xbd3, 0, same, !same, (LPSTR)name, !sum, sum, sum,
                   0x130);
}

/* Message formatter [inferred]: loads string resource id into a format
 * and expands it into out (appending when n is 0; n == 2 also calls
 * fn_03_3498). Codes: %s/%a/%v far string, %A/%S/%V string id, %l long,
 * %d int, %# int plus a unit string id (+10000 unless the int is 1),
 * %< %> optional section (an int switches it on; sections are joined
 * with ", " and a final string 0x31d), %N/%n line break, %? pick one of
 * two ids, %D fn_03_1542 text, %R random string id, %% percent; ^F ^M
 * ^N ^P markers are skipped. */
/* @addr 10:a332 */
void far fn_10_a332(LPSTR out, int id, int n, ...)
{
    int i;
    int len;
    int outpos;
    int count;
    int k;
    int j;
    int val;
    int ids[2];
    long l;
    char buf[80];
    char c;
    char fmt[200];
    LPSTR s;
    int on;
    int flag;
    va_list ap;

    on = 1;
    i = 0;
    count = outpos = 0;
    va_start(ap, n);
    LoadString(g_9212, id, fmt, 0x82);
    len = lstrlen(fmt);
    if (n == 0)
        outpos = lstrlen(out);
    for (k = 0; k < len && i <= len; k++) {
        if (fmt[i] != '%') {
            flag = 0;
            if (fmt[i] == '^') {
                switch (fmt[i + 1]) {
                case 'F':
                case 'M':
                case 'N':
                case 'P':
                    flag = 1;
                    i++;
                }
            }
            if (on && !flag) {
                out[outpos] = fmt[i];
                outpos++;
            }
            i++;
        } else {
            switch (c = fmt[i + 1]) {
            case 's':
            case 'a':
            case 'v':
                s = va_arg(ap, LPSTR);
                if (on) {
                    out[outpos] = 0;
                    lstrcat(out + outpos, s);
                    outpos += lstrlen(s);
                }
                i += 2;
                break;
            case 'A':
            case 'S':
            case 'V':
                LoadString(g_9212, va_arg(ap, int), buf, 0x50);
                if (on) {
                    if (buf[lstrlen(buf) - 2] == '^')
                        buf[lstrlen(buf) - 2] = 0;
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            case '%':
                if (on) {
                    out[outpos] = '%';
                    outpos++;
                }
                i += 2;
                break;
            case 'l':
                l = va_arg(ap, long);
                if (on) {
                    fn_06_0eb8(l, buf);
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            case '#':
            case 'd':
                val = va_arg(ap, int);
                if (on) {
                    fn_06_0f1a(val, buf);
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                if (c != 'd') {
                    if (val != 1)
                        val = 10000;
                    else
                        val = 0;
                    val += va_arg(ap, int);
                    if (on) {
                        out[outpos++] = ' ';
                        LoadString(g_9212, val, buf, 0x50);
                        out[outpos] = 0;
                        lstrcat(out + outpos, buf);
                        outpos = lstrlen(buf) + outpos;
                    }
                }
                i += 2;
                break;
            case '<':
                on = va_arg(ap, int);
                if (on) {
                    for (j = i + 1 + 1; j < len; j++) {
                        if (fmt[j] == '%') {
                            if (fmt[j + 1] == '<') {
                                if (count >= 1) {
                                    out[outpos] = ',';
                                    out[outpos + 1] = ' ';
                                    outpos += 2;
                                }
                                count++;
                                break;
                            } else if (fmt[j + 1] == '>') {
                                if (count > 0) {
                                    LoadString(g_9212, 0x31d, buf, 0x14);
                                    out[outpos] = 0;
                                    lstrcat(out + outpos, buf);
                                    outpos += lstrlen(buf);
                                    out[outpos] = ' ';
                                    outpos = outpos + 1;
                                }
                                count++;
                                break;
                            }
                        }
                    }
                }
                i += 2;
                break;
            case '>':
                on = 1;
                i += 2;
                count = 0;
                break;
            case 'N':
            case 'n':
                if (on && !(g_93aa == 11 && c == 0)) {
                    out[outpos] = '\r';
                    out[outpos + 1] = '\n';
                    outpos += 2;
                }
                i += 2;
                break;
            case '?':
                val = va_arg(ap, int);
                ids[0] = va_arg(ap, int);
                ids[1] = va_arg(ap, int);
                if (val > 1)
                    val = 1;
                LoadString(g_9212, ids[val], buf, 0x50);
                if (on) {
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            case 'D':
                {
                    int a, b, t;

                    a = va_arg(ap, int);
                    b = va_arg(ap, int);
                    t = va_arg(ap, int);
                    if (on) {
                        fn_03_1542(t == 0 || t == 4 || t == 2 || t == 7 ? 1 : 0,
                                   a, b, buf, t);
                        out[outpos] = 0;
                        lstrcat(out + outpos, buf);
                        outpos += lstrlen(buf);
                    }
                }
                i += 2;
                break;
            case 'R':
                val = rand() % va_arg(ap, int);
                val += va_arg(ap, int);
                LoadString(g_9212, val, buf, 0x50);
                if (on) {
                    out[outpos] = 0;
                    lstrcat(out + outpos, buf);
                    outpos += lstrlen(buf);
                }
                i += 2;
                break;
            default:
                i += 3;
                break;
            }
        }
    }
    out[outpos] = 0;
    va_end(ap);
    if (n == 2)
        fn_03_3498(g_8db0, g_8768, g_87b8);
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

/* Builds surface a: d frames of bitmap c, shrinking by 2 pixels each,
 * spaced by object b's margin f24 (5 for an odd height, else 6). */
/* @addr 10:4412 */
void far fn_10_4412(int a, int b, int c, int d)
{
    HDC dc;
    HBITMAP bm;
    HBITMAP ob;
    HPALETTE pal;
    int i;
    int w;
    int x;
    int u;
    BITMAP bmp;
    int h;

    bm = fn_10_6c02(c, 3, -1);
    GetObject(bm, sizeof(BITMAP), &bmp);
    h = bmp.bmHeight;
    if (h & 1)
        g_1df8[b]->f24 = 5;
    else
        g_1df8[b]->f24 = 6;
    dc = CreateCompatibleDC(g_13dc);
    ob = SelectObject(dc, bm);
    w = h * d + g_1df8[b]->f24 * (d + 1);
    g_39e8[a] = CreateCompatibleDC(g_13dc);
    g_3ad0[a] = CreateCompatibleBitmap(g_13dc, w, g_1df8[b]->f24 * 2 + h);
    g_3974[a] = SelectObject(g_39e8[a], g_3ad0[a]);
    if (g_920e) {
        pal = SelectPalette(dc, g_920e, 0);
        g_3a5c[a] = SelectPalette(g_39e8[a], g_920e, 0);
    }
    PatBlt(g_39e8[a], 0, 0, w, g_1df8[b]->f24 * 2 + h, BLACKNESS);
    if (d == 1) {
        BitBlt(g_39e8[a], g_1df8[b]->f24, g_1df8[b]->f24, h, h, dc, 0, 0,
               SRCCOPY);
    } else {
        SetStretchBltMode(g_39e8[a], 3);
        x = g_1df8[b]->f24;
        for (i = 0; i < d; i++) {
            fn_10_9962(0, g_39e8[a], x, g_1df8[b]->f24, u = (i - d) * 2 + h, u,
                       dc, 0, 0, h, h, SRCCOPY);
            x += g_1df8[b]->f24 + h;
        }
    }
    SelectObject(dc, ob);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    if (bm) {
        DeleteObject(bm);
        bm = 0;
    }
    fn_10_6308(a, -1, -1, -1);
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

/* Writes the current time and date into s as "h:mmAM m/d/yy". */
/* @addr 10:97ce */
void far fn_10_97ce(char far *s)
{
    struct tm *tm;
    time_t t;
    char buf[80];
    int h;
    int pm;

    time(&t);
    tm = localtime(&t);
    lstrcpy(s, "");
    h = tm->tm_hour;
    if (h > 11) {
        h -= 12;
        pm = 1;
    } else
        pm = 0;
    if (h == 0)
        h = 12;
    fn_06_0f1a(h, buf);
    lstrcat(s, buf);
    lstrcat(s, ":");
    if (tm->tm_min < 10)
        lstrcat(s, "0");
    fn_06_0f1a(tm->tm_min, buf);
    lstrcat(s, buf);
    if (pm)
        lstrcat(s, "PM");
    else
        lstrcat(s, "AM");
    lstrcat(s, " ");
    fn_06_0f1a(tm->tm_mon + 1, buf);
    lstrcat(s, buf);
    lstrcat(s, "/");
    fn_06_0f1a(tm->tm_mday, buf);
    lstrcat(s, buf);
    lstrcat(s, "/");
    fn_06_0f1a(tm->tm_year, buf);
    lstrcat(s, buf);
}

/* (Re)creates the game's brush and pen tables g_3b74 (1..9), g_576c,
 * g_3b88 (1..5) and g_3b44, and the g_3b4c ramps. */
/* @addr 10:4b2e */
void far fn_10_4b2e(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        if (g_3b74[i]) {
            DeleteObject(g_3b74[i]);
            g_3b74[i] = 0;
        }
    }
    g_3b74[9] = CreateSolidBrush(RGB(255, 114, 0));
    g_3b74[8] = CreateSolidBrush(RGB(255, 96, 0));
    g_3b74[7] = CreateSolidBrush(RGB(234, 64, 0));
    g_3b74[6] = CreateSolidBrush(RGB(224, 48, 0));
    g_3b74[5] = CreateSolidBrush(RGB(208, 32, 0));
    g_3b74[4] = CreateSolidBrush(RGB(192, 32, 16));
    g_3b74[3] = CreateSolidBrush(RGB(176, 32, 32));
    g_3b74[2] = CreateSolidBrush(RGB(127, 48, 48));
    g_3b74[1] = CreateSolidBrush(RGB(127, 64, 64));
    fn_10_4dfe();
    for (i = 0; i < 20; i++) {
        if (g_576c[i]) {
            DeleteObject(g_576c[i]);
            g_576c[i] = 0;
        }
    }
    g_576c[0] = CreateSolidBrush(RGB(128, 128, 128));
    g_576c[1] = CreateSolidBrush(RGB(160, 160, 160));
    g_576c[2] = CreateSolidBrush(RGB(192, 192, 192));
    g_576c[3] = CreateSolidBrush(RGB(224, 224, 224));
    g_576c[4] = CreateSolidBrush(RGB(255, 255, 255));
    g_576c[5] = CreateSolidBrush(RGB(192, 192, 192));
    g_576c[6] = CreateSolidBrush(RGB(160, 223, 160));
    g_576c[7] = CreateSolidBrush(RGB(96, 224, 96));
    g_576c[8] = CreateSolidBrush(RGB(64, 255, 64));
    g_576c[9] = CreateSolidBrush(RGB(0, 255, 0));
    g_576c[10] = CreateSolidBrush(RGB(0, 0, 128));
    g_576c[11] = CreateSolidBrush(RGB(0, 40, 138));
    g_576c[12] = CreateSolidBrush(RGB(0, 80, 160));
    g_576c[13] = CreateSolidBrush(RGB(0, 160, 196));
    g_576c[14] = CreateSolidBrush(RGB(0, 196, 255));
    g_576c[15] = CreateSolidBrush(RGB(160, 0, 0));
    g_576c[16] = CreateSolidBrush(RGB(196, 0, 0));
    g_576c[17] = CreateSolidBrush(RGB(223, 32, 0));
    g_576c[18] = CreateSolidBrush(RGB(255, 96, 0));
    g_576c[19] = CreateSolidBrush(RGB(255, 128, 0));
    for (i = 0; i < 6; i++) {
        if (g_3b88[i]) {
            DeleteObject(g_3b88[i]);
            g_3b88[i] = 0;
        }
    }
    g_3b88[1] = CreateSolidBrush(RGB(0, 0, 127));
    g_3b88[2] = CreateSolidBrush(RGB(0, 127, 196));
    g_3b88[3] = CreateSolidBrush(RGB(0, 196, 255));
    g_3b88[4] = CreateSolidBrush(RGB(0, 255, 255));
    g_3b88[5] = CreateSolidBrush(RGB(255, 255, 255));
    for (i = 0; i < 4; i++) {
        if (g_3b44[i]) {
            DeleteObject(g_3b44[i]);
            g_3b44[i] = 0;
        }
    }
    g_3b44[0] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    g_3b44[1] = CreatePen(PS_SOLID, 1, RGB(127, 0, 127));
    g_3b44[2] = CreatePen(PS_SOLID, 1, RGB(255, 0, 127));
    g_3b44[3] = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
}

/* (Re)creates the 20 brushes g_3b4c: yellow-to-red and cyan-to-blue
 * ramps, finer when g_8ff2 is set [inferred]. */
/* @addr 10:4dfe */
void far fn_10_4dfe(void)
{
    int i;

    for (i = 0; i < 20; i++) {
        if (g_3b4c[i]) {
            DeleteObject(g_3b4c[i]);
            g_3b4c[i] = 0;
        }
    }
    if (g_8ff2) {
        g_3b4c[0] = CreateSolidBrush(PALETTERGB(255, 255, 0));
        g_3b4c[1] = CreateSolidBrush(PALETTERGB(235, 235, 0));
        g_3b4c[2] = CreateSolidBrush(PALETTERGB(220, 215, 0));
        g_3b4c[3] = CreateSolidBrush(PALETTERGB(210, 180, 0));
        g_3b4c[4] = CreateSolidBrush(PALETTERGB(200, 140, 0));
        g_3b4c[5] = CreateSolidBrush(PALETTERGB(185, 120, 0));
        g_3b4c[6] = CreateSolidBrush(PALETTERGB(175, 100, 0));
        g_3b4c[7] = CreateSolidBrush(PALETTERGB(135, 65, 0));
        g_3b4c[8] = CreateSolidBrush(PALETTERGB(135, 65, 0));
        g_3b4c[9] = CreateSolidBrush(PALETTERGB(105, 25, 0));
        g_3b4c[10] = CreateSolidBrush(PALETTERGB(0, 255, 255));
        g_3b4c[11] = CreateSolidBrush(PALETTERGB(0, 235, 240));
        g_3b4c[12] = CreateSolidBrush(PALETTERGB(0, 215, 230));
        g_3b4c[13] = CreateSolidBrush(PALETTERGB(0, 205, 215));
        g_3b4c[14] = CreateSolidBrush(PALETTERGB(0, 175, 205));
        g_3b4c[15] = CreateSolidBrush(PALETTERGB(0, 165, 198));
        g_3b4c[16] = CreateSolidBrush(PALETTERGB(0, 155, 190));
        g_3b4c[17] = CreateSolidBrush(PALETTERGB(0, 130, 160));
        g_3b4c[18] = CreateSolidBrush(PALETTERGB(0, 100, 130));
        g_3b4c[19] = CreateSolidBrush(PALETTERGB(0, 100, 130));
    } else {
        g_3b4c[0] = CreateSolidBrush(PALETTERGB(255, 255, 0));
        g_3b4c[1] = CreateSolidBrush(PALETTERGB(220, 215, 0));
        g_3b4c[2] = CreateSolidBrush(PALETTERGB(200, 140, 0));
        g_3b4c[3] = CreateSolidBrush(PALETTERGB(175, 100, 0));
        g_3b4c[4] = CreateSolidBrush(PALETTERGB(135, 65, 0));
        g_3b4c[5] = CreateSolidBrush(PALETTERGB(105, 25, 0));
        g_3b4c[6] = CreateSolidBrush(PALETTERGB(80, 5, 0));
        g_3b4c[7] = CreateSolidBrush(PALETTERGB(50, 0, 0));
        g_3b4c[8] = CreateSolidBrush(PALETTERGB(25, 0, 0));
        g_3b4c[9] = CreateSolidBrush(PALETTERGB(10, 0, 0));
        g_3b4c[10] = CreateSolidBrush(PALETTERGB(0, 255, 255));
        g_3b4c[11] = CreateSolidBrush(PALETTERGB(0, 215, 230));
        g_3b4c[12] = CreateSolidBrush(PALETTERGB(0, 175, 205));
        g_3b4c[13] = CreateSolidBrush(PALETTERGB(0, 130, 160));
        g_3b4c[14] = CreateSolidBrush(PALETTERGB(0, 100, 130));
        g_3b4c[15] = CreateSolidBrush(PALETTERGB(0, 60, 110));
        g_3b4c[16] = CreateSolidBrush(PALETTERGB(0, 30, 90));
        g_3b4c[17] = CreateSolidBrush(PALETTERGB(0, 0, 60));
        g_3b4c[18] = CreateSolidBrush(PALETTERGB(0, 0, 26));
        g_3b4c[19] = CreateSolidBrush(PALETTERGB(0, 0, 10));
    }
}

extern int g_05d0;
extern int g_1120;
extern int g_1122;
extern int g_922c;
int far fn_02_094c(UINT id);

/* Copy-protection and evaluation-period check [inferred]: with a != 0
 * checks the CD drive named in WIN.INI ("CDDrive"); then checks a key
 * through g_fp_3c68 and derives a day count from SYSTEM.INI/WIN.INI
 * values (g_9224 = days left [inferred]). Sets g_920c (-1, 0..3). */
/* @addr 10:885e */
int far fn_10_885e(int a)
{
    char msg[150];
    char buf[100];
    char drv[80];
    int r;
    int yr;
    int day;
    int y;
    int v1;
    int v3;
    int v2;
    int chk;
    int pad;
    struct tm *tm;
    time_t t;
    long lv3;
    long l;
    int r2;
    int flag;
    char path[120];
    int pad2;
    register int u;

    if (g_920c == -1)
        return 1;
    time(&t);
    tm = localtime(&t);
    yr = tm->tm_year - 93;
    day = yr * 365 + tm->tm_yday;
    g_922c = 1;
    g_922a = g_11aa = g_920c = flag = 0;
    if (a != 0) {
        GetProfileString(g_9690, "CDDrive", "", drv, 40);
        if (drv[0]) {
            r = g_fp_3c68(drv, buf, 21);
            if (r == 0) {
                g_920c = -1;
                g_11aa = 1;
                return 0;
            }
            switch (r) {
            case 1:
                fn_02_094c(0x9ef);
                break;
            case 2:
                fn_02_094c(0x9f0);
                break;
            }
            wsprintf(msg, g_8e68, (LPSTR)drv);
            MessageBox(0, msg, g_9690, MB_ICONEXCLAMATION);
            return -10;
        }
    }
    if (g_05d0 == 1 && (g_1122 + 1) / 2 == g_1120) {
        flag = 1;
    } else if (g_05d0 == 2 && g_1122 == 8 && g_1120 == 0x16a0) {
        g_920c = 3;
        return 0;
    }
    r2 = g_fp_3c68(msg, buf, 2);
    if (r2 == 0 && flag == 0) {
        g_920c = -1;
        if (fn_10_946a(msg))
            g_11aa = 1;
        return 0;
    }
    if (r2 >= 1) {
        GetWindowsDirectory(path, 110);
        u = lstrlen(path);
        if (path[u - 1] != '\\')
            lstrcat(path, "\\");
        lstrcat(path, "SYSTEM.INI");
        v1 = GetPrivateProfileInt("386Enh", "vidsp", 0, path);
        v2 = GetPrivateProfileInt("386Enh", "32BitSP", 0, path);
        v3 = GetProfileInt("windows", "PDev", 0);
        lv3 = v3;
        l = (long)v1 * 2 - lv3 - 0x4cf;
        chk = (int)l;
        v3 -= v1;
        y = v3 ^ 0xff;
        day -= y;
        g_9224 = day + 1;
        if (g_9224 < 1)
            g_9224 = 200;
        if (chk == v2) {
            g_9224 = -1 - day;
            if (day >= 0 && day < 35) {
                g_920c = 2;
                flag = 0;
                return 0;
            }
        }
        if (!flag && day >= 0 && day < 14) {
            g_920c = 1;
            return 0;
        }
    }
    if (r2 == 1000)
        g_922a = 1;
    g_920c = 0;
    return 1;
}

/* Stores GetProcAddress(g_9210, ord) into the function pointer fp and
 * clears ok when the DLL lacks it. */
#define GETPROC(fp, ord) \
    *(FARPROC *)&(fp) = GetProcAddress((HINSTANCE)g_9210, MAKEINTRESOURCE(ord)); \
    if (!(fp)) \
        ok = 0

/* Loads the language DLL (<Language>_LANG.DLL, g_9212) and ISPACE.DLL
 * (g_9210) from the game directory g_8f7a and fetches the ISPACE.DLL entry
 * points by ordinal; returns 0 after a message box when anything fails.
 * A missing ISPACE.DLL only warns [sic]. */
/* @addr 10:6656 */
int far fn_10_6656(void)
{
    OFSTRUCT of;
    int ok;
    char path[110];
    char text[150];
    char msg[40];

    lstrcpy(path, g_8f7a);
    GetPrivateProfileString(g_9690, "Language", "", text, 5, g_96a9);
    lstrcat(path, text);
    lstrcat(path, "_LANG.DLL");
    if (OpenFile(path, &of, OF_EXIST) == -1) {
        lstrcpy(text, "Can't find ");
        lstrcat(text, path);
        lstrcat(text, ". Try reinstalling, do not preserve previous settings.");
        MessageBox(0, text, g_9690, MB_ICONEXCLAMATION);
        return 0;
    }
    g_9212 = LoadLibrary(path);
    if (g_9212 < 32) {
        lstrcpy(text, path);
        lstrcat(text, " is faulty");
        MessageBox(0, text, g_9690, MB_ICONEXCLAMATION);
        return 0;
    }
    lstrcpy(path, g_8f7a);
    lstrcat(path, "ISPACE.DLL");
    if (OpenFile(path, &of, OF_EXIST) == -1) {
        LoadString(g_9212, 0x845, text, 40);
        lstrcat(text, path);
        lstrcat(text, "!");
        MessageBox(0, text, g_9690, MB_ICONEXCLAMATION);
    }
    g_9210 = LoadLibrary(path);
    if ((HINSTANCE)g_9210 < 32) {
        lstrcpy(text, path);
        LoadString(g_9212, 0x7ea, msg, 40);
        lstrcat(text, msg);
        MessageBox(0, text, g_9690, MB_ICONEXCLAMATION);
        return 0;
    }
    ok = 1;
    GETPROC(g_fp_3c28, 1);
    GETPROC(g_fp_3c2c, 3);
    GETPROC(g_fp_3c30, 2);
    GETPROC(g_fp_3c3c, 0x12);
    GETPROC(g_fp_3c38, 0x11);
    GETPROC(g_fp_3c50, 4);
    GETPROC(g_fp_3c4c, 5);
    GETPROC(g_fp_3c40, 6);
    GETPROC(g_fp_3c34, 0xc);
    GETPROC(g_fp_3c44, 0xf);
    GETPROC(g_fp_3c54, 7);
    GETPROC(g_fp_3c68, 0x18);
    GETPROC(g_fp_3c58, 8);
    GETPROC(g_fp_3c5c, 9);
    GETPROC(g_fp_3c6c, 0x1d);
    GETPROC(g_fp_3c70, 0x22);
    GETPROC(g_fp_3c74, 0x21);
    GETPROC(g_fp_3c64, 0xa);
    GETPROC(g_fp_3c7c, 0xe);
    GETPROC(g_fp_3c48, 0x24);
    GETPROC(g_fp_3c80, 0x23);
    GETPROC(g_fp_3c78, 0x20);
    GETPROC(g_fp_3c84, 0x29);
    if (!ok) {
        lstrcpy(text, path);
        LoadString(g_9212, 0x7ea, msg, 40);
        lstrcat(text, msg);
        MessageBox(0, text, g_9690, MB_ICONEXCLAMATION);
        return 0;
    }
    /* g_fp_3c54 returns int here */
    if (!((int (far pascal *)(long, int))g_fp_3c54)(g_05a0, 5)
        || !((int (far pascal *)(long, int))g_fp_3c54)(g_05a0, 7))
        return 0;
    return 1;
}

void far fn_10_16ba(int i);

/* Builds object n's two rows in sprite surface 34 (g_39e8[34]): five
 * cells copied from its surface 40 + n at the class's f50 offsets, the
 * class's f44 frame from the g_3c60 bitmaps masked over them, black
 * borders, then mirrored copies via fn_10_9962 [inferred]. pal1/pal2 are
 * read uninitialised when g_920e is 0 (as in the original). */
/* @addr 10:5d3c */
void far fn_10_5d3c(int n)
{
    int i;
    int j;
    int u8;
    int sz;
    int u;
    int w;
    int lst;
    HDC dc3;
    HDC dc2[2];
    HDC dc1[2];
    HBITMAP bm[2];
    HBITMAP old1[2];
    HBITMAP old2[2];
    HBITMAP bm3;
    HBITMAP old3;
    HPALETTE pal2[2];
    HPALETTE pal1[2];
    int v;
    int z;
    POINT pt;

    sz = 9;
    z = 0;
    if (subgame_active) {
        sz = g_9156 * 6 + 3;
        lst = 20;
    } else {
        sz = (sz << g_9156) >> 1;
        lst = g_9324;
    }
    i = 0;
    w = g_1df8[lst][n].f22;
    v = g_96d2[g_7094[n].f4a].f44;
    dc1[i] = CreateCompatibleDC(g_13dc);
    if (g_920e)
        pal1[i] = SelectPalette(dc1[i], g_920e, 0);
    old1[i] = SelectObject(dc1[i], bm[i] = fn_10_6ec6(g_3c60[i]));
    dc2[i] = CreateCompatibleDC(g_13dc);
    old2[i] = SelectObject(dc2[i], g_3c60[i]);
    if (g_920e)
        pal2[i] = SelectPalette(dc2[i], g_920e, 0);
    if (g_7094[n].fe0) {
        fn_10_16ba(g_7094[n].f4a);
        for (i = 0; i < 5; i++) {
            if (i < 5)
                pt = g_96d2[g_7094[n].f4a].f50[i];
            BitBlt(g_39e8[34], sz * i, sz * n * 2, sz, sz, g_39e8[40 + n],
                   g_1df8[g_9324][n].f24 + (g_1df8[g_9324][n].f24 + w) * i + pt.x,
                   g_1df8[g_9324][n].f24 + pt.y, SRCCOPY);
        }
        if (g_96d2[g_7094[n].f4a].f48) {
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc2[0], 0, v * sz, SRCCOPY);
            SelectObject(g_39e8[34], g_3974[34]);
            bm3 = fn_10_6ec6(g_3ad0[34]);
            dc3 = CreateCompatibleDC(g_13dc);
            old3 = SelectObject(dc3, bm3);
            g_3974[34] = SelectObject(g_39e8[34], g_3ad0[34]);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc3, 0, 0, SRCAND);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, g_39e8[34], 0, sz * n * 2, SRCPAINT);
            SelectObject(dc3, old3);
            DeleteDC(dc3);
            DeleteObject(bm3);
        } else {
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, g_39e8[34], 0, sz * n * 2, SRCCOPY);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc1[0], 0, v * sz, SRCAND);
            BitBlt(g_39e8[34], 0, (n * 2 + 1) * sz, sz * 5, sz, dc2[0], 0, v * sz, SRCPAINT);
        }
        for (i = 0; i < 5; i++) {
            if (i < 5)
                pt = g_96d2[g_7094[n].f4a].f50[i];
            PatBlt(g_39e8[34], sz * i, (n * 2 + 1) * sz, sz, max(-pt.y, 0), BLACKNESS);
            PatBlt(g_39e8[34], sz * i, (n * 2 + 1) * sz, max(-pt.x, 0), sz, BLACKNESS);
            PatBlt(g_39e8[34], sz * i, (n * 2 + 1) * sz + max(w - pt.y, 0), sz,
                   max(pt.y - w + sz, 0), BLACKNESS);
            PatBlt(g_39e8[34], sz * i + min(w - pt.x - 1, sz), (n * 2 + 1) * sz,
                   u = max(pt.x - w + sz + 1, 0), sz, BLACKNESS);
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            if (i == 0)
                fn_10_9962(1, g_39e8[34], sz * 8, (n * 2 + j + 1) * sz - 1, sz, -sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
            else if (i == 4)
                fn_10_9962(1, g_39e8[34], sz * 13 - 1, (n * 2 + j) * sz, -sz, sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
            else {
                fn_10_9962(1, g_39e8[34], (8 - i) * sz, (n * 2 + j + 1) * sz - 1, sz, -sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
                fn_10_9962(1, g_39e8[34], (i + 9) * sz - 1, (n * 2 + j + 1) * sz - 1, -sz, -sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
                fn_10_9962(1, g_39e8[34], (17 - i) * sz - 1, (n * 2 + j) * sz, -sz, sz,
                           g_39e8[34], sz * i, (n * 2 + j) * sz, sz, sz, SRCCOPY);
            }
        }
    }
    for (i = 0; i < 1; i++) {
        if (dc2[i]) {
            if (pal2[i])
                SelectPalette(dc2[i], pal2[i], 0);
            SelectObject(dc2[i], old2[i]);
            DeleteDC(dc2[i]);
            dc2[i] = 0;
        }
        if (dc1[i]) {
            if (pal1[i])
                SelectPalette(dc1[i], pal1[i], 0);
            SelectObject(dc1[i], old1[i]);
            DeleteDC(dc1[i]);
            dc1[i] = 0;
            if (bm[i]) {
                DeleteObject(bm[i]);
                bm[i] = 0;
            }
        }
    }
}
/* map position (world units / 8) scaled to the w x h picture */
#define MAP_W (*(int *)&g_05a0)     /* inspace.h declares DS:05a0 long */
#define MX(px) (int)((long)((px) / 8 - MAP_W / 2) * w / MAP_W) + w / 2
#define MXO(px, o) (int)((long)((px) / 8 - MAP_W / 2 + (o)) * w / MAP_W) + w / 2
#define SC(n) ((n) << g_9156 >> 1)
#define MY(py) (int)((long)((py) / 8 - g_05a2 / 2) * h / g_05a2) + h / 2

/* World map of map `map`, scaled to w x h. c == -1 (and !e): into a new
   bitmap (returned); otherwise into g_93d0, and c == 8 marks only marker d
   [inferred]. */
/* @addr 10:8b1c */
HBITMAP far world_map(int w, int h, int a, int map, int c, int d, int e)
{
    HDC dc;
    HBITMAP bm;
    int unused;         /* never used */
    HPALETTE oldpal;
    HGDIOBJ oldpen;
    HGDIOBJ oldbr;
    int y;
    int x;
    int y2;
    int x2;
    int i;

    if (c == -1 && !e) {
        dc = CreateCompatibleDC(g_13dc);
        SelectObject(dc, bm = CreateCompatibleBitmap(g_13dc, w, h));
        if (g_920e)
            oldpal = SelectPalette(dc, g_920e, 0);
        PatBlt(dc, 0, 0, w, h, BLACKNESS);
    } else
        dc = g_93d0;
    if (a)
        oldpen = SelectObject(dc, g_3b44[0]);
    else
        oldpen = SelectObject(dc, GetStockObject(BLACK_PEN));
    oldbr = SelectObject(dc, g_500c);
    for (i = 0; i < g_9ebc[map]; i++) {
        if (c == -1 || c == 8 && d - g_9eb9[g_9322] - g_9318 * 2 == i) {
            x = MX(g_9f40[map][g_9eb9[map] + i].x);
            y = MY(g_9f40[map][g_9eb9[map] + i].y);
            if (c == 8 && !e)
                PatBlt(dc, x + w / -80, y + w / -80, max(w / 50, 4), max(w / 50, 4),
                       BLACKNESS);
            else
                StretchBlt(dc, x + w / -80, y + w / -80, max(w / 50, 4), max(w / 50, 4),
                           g_93cc, 80, 0, 4, 4, MERGECOPY);
        }
    }
    if (c != 8) {
        SetStretchBltMode(dc, COLORONCOLOR);
        for (i = 0; i < g_9eb6[map]; i++) {
            x = MX(g_9f40[map][i].x);
            y = MY(g_9f40[map][i].y);
            StretchBlt(dc, x - max(w / 100, 1), y - max(w / 100, 1),
                       max(w / 50, 3), max(w / 50, 3),
                       g_3a24, SC(4), SC(4), SC(14), SC(14), SRCCOPY);
        }
        SelectObject(dc, g_5006);
        x = MXO(g_a120[map].x, -170);
        x2 = MXO(g_a120[map].x, 170);
        y = MY(g_a120[map].y);
        PatBlt(dc, x + w / -80, y + w / -80, max(w / 50, 3), max(w / 50, 3), PATCOPY);
        PatBlt(dc, x2 + w / -80, y + w / -80, max(w / 50, 3), max(w / 50, 3), PATCOPY);
        SelectObject(dc, g_5008);
        PatBlt(dc, x + w / 80, y + w / -280, x2 - max(w / 50, 3) - x,
               max(w / 140, 1), PATCOPY);
        if (w != g_0a72) {
            for (i = 0; i < g_9ebf[map]; i++) {
                x = MX(g_9f40[map][g_9eb9[map] + g_9ebc[map] + i].x);
                y = MY(g_9f40[map][g_9eb9[map] + g_9ebc[map] + i].y);
                StretchBlt(dc, x - max(w / 100, 2), y - max(w / 100, 2),
                           max(w / 50, 3), max(w / 50, 3),
                           g_39f0, g_1e08->f24, g_1e08->f24, g_1e08->f22, g_1e08->f22,
                           SRCCOPY);
            }
            x = MX(g_a120[map].x);
            y = MY(g_9f40[map][0].y);
            StretchBlt(dc, x - g_1e30[g_9646].f20 / 8 * w / 3200,
                       y - g_1e30[g_9646].f20 / 8 * w / 800,
                       g_1e30[g_9646].f20 / 8 * w / 1600, g_1e30[g_9646].f20 / 8 * w / 1600,
                       g_3a38[g_9646], g_1e30[g_9646].f22 * 4 + g_1e30[g_9646].f24 * 5,
                       g_1e30[g_9646].f24, g_1e30[g_9646].f22, g_1e30[g_9646].f22, SRCCOPY);
        }
        SelectObject(dc, g_500c);
        x = MXO(g_a120[map].x, 40);
        y = MY(g_9ea8[map].y);
        y2 = MY(g_9ea8[map].x);
        PatBlt(dc, x, y2, max(w / 140, 1), y - y2, PATCOPY);
    }
    if (c == -1 || a) {
        for (i = 0; i < g_9eb9[map]; i++) {
            if (g_9ec2[map][i] != i) {
                x2 = MX(g_9f40[map][i].x);
                y2 = MY(g_9f40[map][i].y);
                MoveTo(dc, x2, y2);
                x = MX(g_9f40[map][g_9ec2[map][i]].x);
                y = MY(g_9f40[map][g_9ec2[map][i]].y);
                LineTo(dc, x, y);
            }
        }
    }
    SelectObject(dc, oldbr);
    SelectObject(dc, oldpen);
    if (c == -1 && !e) {
        SelectObject(dc, bm);
        if (g_920e)
            SelectPalette(dc, oldpal, 0);
        DeleteDC(dc);
    }
    return bm;
}
