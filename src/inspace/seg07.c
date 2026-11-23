/* INSPACE.EXE segment 7 (selector 1030). */
#include "inspace.h"
#include <stdlib.h>

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    int f00;
    int f02;
    int f04;                    /* +4 */
    int f06;                    /* +6 */
    char p08[0x0c - 0x08];
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
    char p26[0x28 - 0x26];
    int f28;                    /* +28 */
    char p2a[0x2c - 0x2a];
    int f2c;                    /* +2c */
    char f2e;                   /* +2e */
    signed char f2f;            /* +2f */
    char p30[0x44 - 0x30];
    int f44;                    /* +44 */
    int f46;
    int f48;                    /* +48 */
    char p4a[0x51 - 0x4a];
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
    int f02;
    char p04[0x06 - 0x04];
    int f06;
    char p08[0x0a - 0x08];
    char f0a;
    char f0b;
    char p0c[0x23 - 0x0c];
} REC_23;
#pragma pack()

typedef struct {                /* 0x15a bytes, DGROUP array at DS:7090 */
    char p00[0x4e];
    int f4e;                    /* +4e */
    char p50[0xd0 - 0x50];
    int fd0;                    /* +d0 */
    char pd2[0xe3 - 0xd2];
    char fe3;                   /* +e3 */
    char pe4[0x15a - 0xe4];
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
extern int g_92e8;
extern int g_91fa;
extern char g_8ffe;
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
extern REC_15A g_7090[];
extern POINT g_1050[];
extern POINT g_7ba0[][64];
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
extern RECT g_1de4;                 /* icon window position */
extern HMENU g_945a;
extern int g_8f72;
extern int g_8f68;
extern int g_8fee;
extern HINSTANCE g_8e66;
extern HWND g_0a7c;

/* 20-byte records at DS:1e90 [inferred]. */
typedef struct {
    int f0;
    int f2;
    int f4;
    int f6;
    int f8;
    int fa;
    int fc;
    int fe;
    long f10;
} REC_14B;
extern REC_14B g_1e90[];
extern POINT g_5170[];
extern long g_5224[];
extern HDC g_5e98[4];
extern HGDIOBJ g_5ea0[4];
extern HDC g_39e8[];
extern int g_6038[];
extern int g_9430;
typedef struct { char p00[0x14]; int f14; char p16[0x34 - 0x16]; } REC_34;
extern REC_34 g_3d5a[];         /* base as in seg03.c */
typedef struct { int f00; char p02[0x1c - 2]; } REC_1C;
extern REC_1C g_66e4[];         /* seg04.c uses base DS:66e8 */
typedef struct { int f00; char p02[0x28 - 2]; int f28; char p2a[0x50 - 0x2a]; } REC_50;
extern REC_50 g_2f50[];         /* seg04.c uses base DS:2f58 */

/* 0x16-byte records at DS:5b28, [?][4] (as in seg08.c). */
typedef struct {
    POINT p;                    /* +0 */
    POINT q;                    /* +4 */
    POINT r;                    /* +8 */
    int age;                    /* +c */
    int vx;                     /* +e */
    int vy;                     /* +10 */
    POINT s;                    /* +12 */
} REC_16;
extern REC_16 g_5b28[][4];
extern int g_9510;
extern int g_9512;
extern int g_9514;
extern HGDIOBJ g_3b4c[];
void far pascal fn_08_083e(int a, int b);

void far pascal fn_08_1d54(int a, int b);
void far pascal fn_08_1b54(int a, int b);
int far fn_07_233c(int a, int n, int amount);
int far fn_10_6d38(LPCSTR s);
void far fn_07_26c4(int unused, int n);
void far fn_07_5a46(void);
void far fn_07_4d86(int i);
void far fn_07_4a38(int a, int b, int c);
void far fn_07_4ffe(int n);
void far fn_07_5660(int n);
void far pascal fn_07_3294(int n);
void far fn_07_63f2(void);
void far fn_07_63b6(HMENU menu, LPCSTR text, int checked, UINT id);
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
void far fn_07_1208(void);
void far fn_07_2080(int t, int unused);  /* defined in seg07b.c with one arg */
int far fn_13_59e8(int a, int b);
void far fn_08_99ce(int a, int b, int c, int d, int e);
void far fn_13_6450(int a, int b, int c);
void far fn_13_58dc(int a, int b);
void far fn_13_5a6a(HDC dc, int a, int b, int c, int d, int e, int f, int g);

/* Adds cracks to a window pane and redraws it [inferred]. */
/* @addr 7:233c */
int far fn_07_233c(int unused, int n, int amount)
{
    int size;
    int gap;
    int u;
    int q;
    HDC memdc;
    HGDIOBJ old;
    HBITMAP bmp;

    if (g_57a8[n].f00 == 0 && g_1df8[0][n].f2f != -100 && g_1df8[0][n].f2f != -2) {
        g_1df8[0][n].f1e = min(amount * 3 + g_1df8[0][n].f1e, 211);
        g_69f4[g_94a2].f1d2[n] = g_1df8[0][n].f1e;
        gap = g_1df8[0][n].f24;
        size = g_1df8[0][n].f22;
        if (g_1df8[0][n].f1e > 0 && g_1df8[0][n].f2f >= 0) {
            memdc = CreateCompatibleDC(g_13dc);
            bmp = fn_10_6d38("CRACKS");
            if (amount)
                bmp = fn_10_6308(-1, -1, bmp, -1);
            else {
                gap = 6;
                size = 32;
            }
            old = SelectObject(memdc, bmp);
            q = g_1df8[0][n].f1e / 70;
            BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
                   memdc, (q + 3) * size, 0, MERGEPAINT);
            BitBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
                   memdc, q * size, 0, SRCAND);
            SelectObject(memdc, old);
            DeleteDC(memdc);
            DeleteObject(bmp);
            if (amount && g_57a8[n].f02 == 0)
                fn_10_754a(0x12, 0, n, 1);
        }
        if (amount && (g_1df8[0][n].f1e > 208 || g_1df8[0][n].f2f < 0)) {
            fn_07_26c4(0, n);
            return 1;
        }
    }
    fn_07_65aa(0, n);
    return 0;
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

/* Starts an explosion/flash on an object [inferred]. */
/* @addr 7:2e02 */
void far fn_07_2e02(int type, int idx)
{
    int u;
    int i;
    int j;
    int u2;

    if (g_1df8[type][idx].f18 == 0) {
        g_1df8[type][idx].f18 = 1;
        PatBlt(g_13dc, g_1df8[type][idx].f00, g_1df8[type][idx].f02,
               g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
        for (i = 0; i < 4; i++) {
            if (g_1e90[i].f0 == -1 || g_1e90[i].fa <= 5) {
                if (g_5e98[i]) {
                    SelectObject(g_5e98[i], g_5ea0[i]);
                    DeleteDC(g_5e98[i]);
                    g_5e98[i] = 0;
                }
                if (type == 1) {
                    g_5e98[i] = CreateCompatibleDC(g_13dc);
                    g_5ea0[i] = SelectObject(g_5e98[i], g_4e94[idx]);
                    fn_10_754a(0x1a, type, idx, 1);
                } else if (type == 8) {
                    g_5e98[i] = g_39e8[g_3d5a[idx].f14];
                    fn_10_754a(0x1a, type, idx, 1);
                } else if (type == 6) {
                    g_5e98[i] = g_39e8[g_2f50[g_66e4[idx].f00].f00];
                    if (g_2f50[g_66e4[idx].f00].f28 == 6)
                        fn_10_754a(0x1a, type, idx, 1);
                    else
                        fn_10_754a(0x1f, type, idx, 1);
                } else if (type == 4) {
                    g_5e98[i] = g_39e8[4];
                    fn_10_754a(0x1f, type, idx, 1);
                }
                if (g_1e90[i].f0 > -1)
                    for (j = 4; j < 45; j++)
                        if (g_1e90[j].f0 == -1) {
                            g_1e90[j].f0 = g_1e90[i].f0;
                            g_1e90[j].f2 = g_1e90[i].f2;
                            g_1e90[j].f6 = g_1e90[i].f6;
                            g_1e90[j].f8 = g_1e90[i].f8;
                            g_1e90[j].f10 = g_1e90[i].f10;
                            g_1e90[j].fa = g_1e90[i].fa;
                            g_5170[j] = g_5170[i];
                            g_5224[j] = g_5224[i];
                            g_1e90[j].fc = g_1e90[i].fc;
                            g_1e90[j].fe = g_1e90[i].fe;
                            break;
                        }
                g_1e90[i].f0 = 1;
                g_1e90[i].f2 = 20;
                g_9430++;
                g_1e90[i].fa = 6;
                g_1e90[i].fc = g_1df8[type][idx].f22 / 5;
                if (i > g_9208)
                    g_1e90[i].f4 = 2;
                else
                    g_1e90[i].f4 = 1;
                g_1e90[i].f6 = type;
                g_1e90[i].f8 = idx;
                g_5170[i] = *(POINT far *)&g_1df8[type][idx].f00;
                g_5224[i] = *(long far *)&g_1df8[type][idx].f04;
                break;
            }
        }
    }
    if (type == 1)
        fn_07_65aa(0, g_6038[idx]);
}

/* @addr 7:3294 */
void far pascal fn_07_3294(int n)
{
    fn_08_1d54((char)n, 0x1e);
    if (!g_1df8[0][n].f54)
        fn_08_1b54((char)n, 3);
}

/* @addr 7:309c */
void far fn_07_309c(void)
{
    int i;
    int u1;
    int r;
    int u2;
    int size;
    int gap;
    int u3[6];
    int flag;
    HDC dc;

    if (g_92e8)
        return;
    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    for (i = 0; i < g_91fa; i++) {
        if (g_1df8[0][i].f18 != 0)
            continue;
        flag = 0;
        if (g_57a8[i].f00 != 0) {
            fn_07_4d86(i);
            if (g_57a8[i].f00 < 7) {
                g_57a8[i].f00 = 0;
                flag = 1;
            }
        }
        if (g_1df8[0][i].f1a != 0) {
            if (g_57a8[i].f02 == 0) {
                g_1df8[0][i].f10 = (gap + size) * i + gap;
                dc = g_3a02;
            } else {
                dc = g_3a04[i];
                g_1df8[0][i].f10 = (g_57a8[i].f02 / 2 - 1) * (gap + size) + gap;
            }
            fn_08_1d54((char)i, 0x28);
            if (!g_1df8[0][i].f54)
                fn_08_1b54((char)i, 1);
            fn_08_0b76((char)i, 1, dc, 0);
            if (g_1df8[0][i].f1a != 0 && g_1df8[0][i].f1c == 0) {
                g_943a = 0;
                g_943c = i;
                r = fn_08_50aa((char)i);
                if (r != -1)
                    fn_07_4a38(HIBYTE(r), LOBYTE(r), i);
            }
        } else if (g_9142 % 3 == 0)
            fn_07_3294(i);
        if (g_9142 % 30 == 0 && g_1df8[0][i].f2f < 0) {
            g_1df8[0][i].f2f++;
            if (g_1df8[0][i].f2f == 0)
                g_1df8[0][i].f53 = 1;
            if (g_1df8[0][i].f2f == -2)
                fn_07_5660(i);
        }
        if (g_57a8[i].f02 != 0) {
            if (g_57a8[i].f02 > 10)
                g_57a8[i].f02 = 1;
            g_57a8[i].f02++;
        }
        if (flag)
            fn_07_4ffe(i);
    }
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

/* Moves the four sparks of each burst along curved paths [inferred]. */
/* @addr 7:375a */
void far fn_07_375a(void)
{
    int i;
    int j;
    int t;
    int k;                      /* kept in a register, never stored */
    int u2;
    int n;
    int m;

    if (g_9510 >= 50)
        return;
    n = g_9208 * 2 + 3;
    m = (g_9208 + 7) * 4;
    for (i = 0; i < n; i++) {
        if (n - 1 > g_9510 && i == g_9510)
            for (j = 0; j < 4; j++) {
                g_5b28[g_9510][j].s = *(POINT far *)&g_1df8[g_9512][g_9514].f04;
                g_5b28[g_9510][j].s.x
                    += g_7ba0[g_7090[g_9514].f4e][g_1df8[g_9512][g_9514].f28].x * 8;
                g_5b28[g_9510][j].s.y
                    += g_7ba0[g_7090[g_9514].f4e][g_1df8[g_9512][g_9514].f28].y * 8;
                g_5b28[g_9510][j].vx = -(g_1050[g_1df8[g_9512][g_9514].f28].x * 4);
                g_5b28[g_9510][j].vy = -(g_1050[g_1df8[g_9512][g_9514].f28].y * 4);
                g_5b28[g_9510][j].age = 0;
            }
        if (m + n + 1 > g_9510 && i <= g_9510) {
            for (j = 0; j < 4; j++) {
                if (g_5b28[i][j].age < m && g_5b28[i][j].age > 0) {
                    fn_08_083e(i, j);
                    k = g_7090[g_9514].fe3 * 10 + (g_5b28[i][j].age >> 2);
                    SelectObject(g_13dc, g_3b4c[k]);
                    PatBlt(g_13dc, g_5b28[i][j].p.x, g_5b28[i][j].p.y, 2, 2, PATCOPY);
                    PatBlt(g_13dc, g_5b28[i][j].q.x, g_5b28[i][j].q.y, 2, 2, BLACKNESS);
                }
                g_5b28[i][j].s.x += g_5b28[i][j].vx;
                g_5b28[i][j].s.y += g_5b28[i][j].vy;
                g_5b28[i][j].age++;
                if (g_5b28[i][j].age >= m - 1)
                    PatBlt(g_13dc, g_5b28[i][j].p.x, g_5b28[i][j].p.y, 2, 2, BLACKNESS);
            }
            if (g_5b28[i][0].age < m / 3) {
                t = g_5b28[i][0].vx;
                g_5b28[i][0].vx -= g_5b28[i][0].vy >> 2;
                g_5b28[i][0].vy += t >> 2;
                t = g_5b28[i][1].vx;
                g_5b28[i][1].vx -= g_5b28[i][1].vy >> 3;
                g_5b28[i][1].vy += t >> 3;
                t = g_5b28[i][2].vx;
                g_5b28[i][2].vx += g_5b28[i][2].vy >> 3;
                g_5b28[i][2].vy -= t >> 3;
                t = g_5b28[i][3].vx;
                g_5b28[i][3].vx += g_5b28[i][3].vy >> 2;
                g_5b28[i][3].vy -= t >> 2;
            } else {
                t = g_5b28[i][0].vx;
                g_5b28[i][0].vx -= g_5b28[i][0].vy;
                g_5b28[i][0].vy += t;
                t = g_5b28[i][1].vx;
                g_5b28[i][1].vx -= g_5b28[i][1].vy >> 1;
                g_5b28[i][1].vy += t >> 1;
                t = g_5b28[i][2].vx;
                g_5b28[i][2].vx += g_5b28[i][2].vy >> 1;
                g_5b28[i][2].vy -= t >> 1;
                t = g_5b28[i][3].vx;
                g_5b28[i][3].vx += g_5b28[i][3].vy;
                g_5b28[i][3].vy -= t;
            }
        }
    }
    if (m + n == ++g_9510)
        g_9512 = -1;
}

/* @addr 7:3a42 */
void far fn_07_3a42(int n)
{
    int size;
    int gap;

    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    g_1df8[0][n].f51 -= g_8ffe;
    if (g_1df8[0][n].f51 < 0)
        g_1df8[0][n].f51 = 0;
    if (g_1df8[0][n].f1a == 0 && !fn_13_59e8(0, n))
        return;
    SetStretchBltMode(g_3a02, COLORONCOLOR);
    StretchBlt(g_3a02, (gap + size) * n + gap, gap, size, size,
               g_3a02, (gap + size) * n + gap - 2, gap - 2, size + 4, size + 4, SRCCOPY);
    BitBlt(g_13dc, g_1df8[0][n].f00, g_1df8[0][n].f02, size, size,
           g_3a02, (gap + size) * n + gap, gap, SRCCOPY);
    if (g_1df8[0][n].f48 == g_9646 && g_9208 > 1 && (g_1df8[0][n].f51 & 1))
        fn_07_1208();
    if (g_1df8[0][n].f51 < 1) {
        PatBlt(g_13dc, g_1df8[0][n].f00, g_1df8[0][n].f02, size, size, BLACKNESS);
        PatBlt(g_3a02, (gap + size) * n + gap, gap, size, size, BLACKNESS);
        fn_07_65aa(0, n);
        fn_07_2080(0, -1);
    }
}

/* Builds the five-frame strip of a window pane in g_3a04[n] [inferred]. */
/* @addr 7:477e */
void far fn_07_477e(int n)
{
    int i;
    int size;
    int gap;
    int bmp2;
    HGDIOBJ old2;
    int bmp;
    HGDIOBJ old1;
    HDC dc2;
    HDC dc1;
    HPALETTE pal;

    fn_10_754a(0x6a, 0, n, 1);
    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    g_57a8[n].f00 = 0x59;
    bmp = fn_10_6308(-1, -1, fn_10_6c02(0xe6, 0, -1), -1);
    bmp2 = fn_10_6ec6(bmp);
    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, bmp);
    if (g_920e)
        pal = SelectPalette(dc1, g_920e, 0);
    dc2 = CreateCompatibleDC(g_13dc);
    old2 = SelectObject(dc2, bmp2);
    if (!g_3a04[n]) {
        g_3a04[n] = CreateCompatibleDC(g_13dc);
        g_3aec[n] = CreateCompatibleBitmap(g_13dc, size * 5 + gap * 6, gap * 2 + size);
        g_3990[n] = SelectObject(g_3a04[n], g_3aec[n]);
        if (g_920e)
            g_3a78[n] = SelectPalette(g_3a04[n], g_920e, 0);
    }
    PatBlt(g_3a04[n], 0, 0, size * 5 + gap * 6, gap * 2 + size, BLACKNESS);
    for (i = 0; i < 5; i++) {
        BitBlt(g_3a04[n], (gap + size) * i + gap, (12 << g_9156 >> 1) + gap, size,
               size - (12 << g_9156 >> 1), g_3a02, (gap + size) * n + gap,
               (12 << g_9156 >> 1) + gap, SRCCOPY);
        BitBlt(g_3a04[n], (gap + size) * i + gap, gap, size, size, dc2, size * i, 0, SRCAND);
        BitBlt(g_3a04[n], (gap + size) * i + gap, gap, size, size, dc1, size * i, 0, SRCPAINT);
    }
    SelectObject(dc1, old1);
    SelectObject(dc2, old2);
    if (pal)
        SelectPalette(dc1, pal, 0);
    DeleteDC(dc1);
    DeleteDC(dc2);
    DeleteObject(bmp2);
    DeleteObject(bmp);
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
            g_7090[g_57a8[a].f0b].fd0++;
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

/* Window procedure of the "IS_ICON" pilot-icon window [inferred]. */
/* @addr 7:6184 */
LONG far pascal fn_07_6184(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    RECT r;
    RECT rc;
    PAINTSTRUCT ps;
    HDC dc;
    MINMAXINFO far *mmi;
    UINT cmd;
    int res;

    switch (msg) {
    case WM_CREATE:
        g_9458 = hwnd;
        g_945a = GetSystemMenu(hwnd, FALSE);
        AppendMenu(g_945a, MF_SEPARATOR, 0, NULL);
        AppendMenu(g_945a, 0, 0xf0, "1/2x Scale");
        fn_07_63b6(g_945a, "1/2x Scale", g_0b6e, 0xf0);
        DrawMenuBar(g_9458);
        break;
    case WM_SYSCOMMAND:
        switch (cmd = wp & 0xfff0) {
        case 0xf0:
            fn_07_63b6(g_945a, "1/2x Scale", g_0b6e = !g_0b6e, 0xf0);
            GetWindowRect(g_9458, &r);
            MoveWindow(g_9458, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
            SetActiveWindow(g_0016);
            break;
        case SC_CLOSE:
            g_8f72 = 0;
        default:
            return DefWindowProc(hwnd, msg, wp, lp);
        }
        break;
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    case WM_SETFOCUS:
        g_8f68 = 1;
        break;
    case WM_MOVE:
        GetWindowRect(g_9458, &r);
        if (r.left != g_1de4.left || r.top != g_1de4.top) {
            CopyRect(&g_1de4, &r);
            g_8fee = 1;
        }
        SetActiveWindow(g_0016);
        break;
    case WM_GETMINMAXINFO:
        mmi = (MINMAXINFO far *)lp;
        mmi->ptMinTrackSize.x = mmi->ptMaxTrackSize.x = 50 >> g_0b6e;
        if (g_0b6e)
            mmi->ptMinTrackSize.y = mmi->ptMaxTrackSize.y
                = GetSystemMetrics(SM_CYCAPTION) + g_91fe * 23 + 3;
        else
            mmi->ptMinTrackSize.y = mmi->ptMaxTrackSize.y
                = GetSystemMetrics(SM_CYCAPTION) + g_91fe * 46 + 6;
        break;
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        GetClientRect(hwnd, &rc);
        dc = BeginPaint(hwnd, &ps);
        PatBlt(dc, 0, 0, rc.right, rc.bottom, BLACKNESS);
        res = fn_07_64ac(dc, 1, -1);
        EndPaint(hwnd, &ps);
        if (!res)
            fn_07_63f2();
        break;
    case WM_CLOSE:
        if (g_9458) {
            DestroyWindow(g_9458);
            g_9458 = 0;
        }
        break;
    }
    return 0L;
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
        CreateWindow("IS_ICON", "", 0x10cc0000L, g_1de4.left, g_1de4.top, 50, 150,
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


/* Spawns a spark/debris particle at an object [inferred]. */
/* @addr 7:5b68 */
void far fn_07_5b68(int type, int idx, int flag)
{
    int u1;
    int u2;
    int i;
    int r;
    int chance;

    switch (g_9208) {
    case 0:
        chance = 25;
        break;
    case 1:
        chance = 45;
        break;
    case 2:
        chance = 65;
        break;
    case 3:
        chance = 90;
        break;
    }
    if (g_9208 != 3 && rand() % 100 > chance)
        return;
    for (i = 0; i < 20; i++) {
        if (g_58bc[i].f10 == -1) {
            g_58bc[i].f10 = 0;
            if (type == g_9324) {
                g_58bc[i].c.x = (g_7ba0[g_7090[idx].f4e][g_1df8[type][idx].f28].x
                                 - g_1050[g_1df8[type][idx].f28].x / 4 - 4) * 8
                                + g_1df8[type][idx].f04;
                g_58bc[i].c.y = (g_7ba0[g_7090[idx].f4e][g_1df8[type][idx].f28].y
                                 - g_1050[g_1df8[type][idx].f28].y / 4 - 4) * 8
                                + g_1df8[type][idx].f06;
                g_58bc[i].fc = g_1df8[type][idx].f0c - g_1050[g_1df8[type][idx].f28].x / 2;
                g_58bc[i].fe = g_1df8[type][idx].f0e - g_1050[g_1df8[type][idx].f28].y / 2;
            } else {
                g_58bc[i].c.x = rand() % g_1df8[type][idx].f20 + g_1df8[type][idx].f04;
                g_58bc[i].c.y = rand() % g_1df8[type][idx].f20 + g_1df8[type][idx].f06;
                r = rand() % 16;
                g_58bc[i].fc = g_1050[r].x / 2 + g_1df8[type][idx].f0c / 2;
                g_58bc[i].fe = g_1050[r].y / 2 + g_1df8[type][idx].f0e / 2;
            }
            if (flag)
                fn_10_754a(1, type, idx, 1);
            g_9456++;
            return;
        }
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_07_2768(int n)
{
    g_0a76 = n;
}

/* Animates a window pane being cleared: shifts random columns [inferred]. */
/* @addr 7:4d86 */
void far fn_07_4d86(int n)
{
    int a;
    int b;
    int c;
    int d;
    int gap;
    int size;
    int j;
    int w;

    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    a = (rand() % 12 + 10 << g_9156) >> 1;
    b = (rand() % 12 + 10 << g_9156) >> 1;
    c = rand() % 10 << g_9156;
    d = (rand() % 10 + 22 << g_9156) >> 1;
    w = 2 << g_9156 >> 1;
    if (g_57a8[n].f02 == 0) {
        BitBlt(g_3a02, (size + gap) * n + gap + a, gap, w, size,
               g_3a02, (size + gap) * n + gap + a, gap - w, SRCCOPY);
        BitBlt(g_3a02, (size + gap) * n + gap + b, gap, w, size,
               g_3a02, (size + gap) * n + gap + b, gap - w, SRCCOPY);
        BitBlt(g_3a02, (size + gap) * n + gap + c, gap, w, size,
               g_3a02, (size + gap) * n + gap + c, gap - w, SRCCOPY);
        BitBlt(g_3a02, (size + gap) * n + gap + d, gap, w, size,
               g_3a02, (size + gap) * n + gap + d, gap - w, SRCCOPY);
        g_57a8[n].f00--;
        return;
    }
    if (rand() & 1)
        c = d;
    BitBlt(g_3a02, (size + gap) * n + gap + a, gap, w, size,
           g_3a02, (size + gap) * n + gap + a, gap - w / 2, SRCCOPY);
    BitBlt(g_3a02, (size + gap) * n + gap + c, gap, w, size,
           g_3a02, (size + gap) * n + gap + c, gap - w / 2, SRCCOPY);
    for (j = 1; j < 6; j++) {
        BitBlt(g_3a04[n], (size + gap) * (j - 1) + gap + a, gap, w, size,
               g_3a04[n], (size + gap) * (j - 1) + gap + a, gap - w / 2, SRCCOPY);
        BitBlt(g_3a04[n], (size + gap) * (j - 1) + gap + c, gap, w, size,
               g_3a04[n], (size + gap) * (j - 1) + gap + c, gap - w / 2, SRCCOPY);
    }
    if (g_57a8[n].f02 < 7)
        g_57a8[n].f00--;
    if (g_57a8[n].f00 < 50 && g_57a8[n].f00 % 5 == 0)
        fn_07_5b68(0, n, 0);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_07_4a38(int a, int b, int c)
{
    g_0a76 = a + b + c;
}
