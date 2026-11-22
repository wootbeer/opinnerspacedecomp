/* INSPACE.EXE segment 18 (selector 1088). */
#include "inspace.h"
#include <stdlib.h>

extern int g_9668;
extern int g_9672;
extern int g_a1cd;
extern int g_a1cf;
extern char g_a18f[4];
extern char g_a193[4];
extern HANDLE g_88d8[8];
extern int g_8e62;
extern int g_90f4;
extern int g_9530;
extern long g_8d34;
extern int g_965e;
extern int g_9660;
extern int g_9130;                  /* subgame_active */
#pragma pack(1)
typedef struct {                /* far pointer at DS:6da4 */
    int f00;
    int f02;                    /* width [inferred] */
    int f04;                    /* height [inferred] */
    char p06[0x08 - 0x06];
    char f08[0x1c - 0x08];      /* name, "Inner Demon" [inferred] */
    int f1c;
} REC_6DA4;

typedef struct {                /* 0x15a bytes, DGROUP array at DS:70ae */
    int f00;
    char p02[0x06 - 0x02];
    int f06;
    int f08[4];
    char p10[0x30 - 0x10];
    int f30;
    char p32[0x8e - 0x32];
    char f8e;
    char f8f;
    char p90[0xb8 - 0x90];
    int fb8;
    char pba[0xc2 - 0xba];
    char fc2;
    char fc3;
    char pc4[0xc6 - 0xc4];
    char fc6;
    char pc7[0xce - 0xc7];
    char fce;
    char pcf[0x15a - 0xcf];
} REC_15A;

typedef struct {                /* 0x7c-byte records at far DS:6e24 */
    char p00[0x1c];
    unsigned char f1c;
    char p1d[0x38 - 0x1d];
    signed char f38[4];
    char p3c[0x72 - 0x3c];
    char f72;
    char f73;
    signed char f74;
    char p75[0x7c - 0x75];
} REC_7C;
#pragma pack()

extern REC_7C far *g_6e24;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    char p02[0x0a - 0x02];
    int f0a;
    char p0c[0xad - 0x0c];
} REC_AD;
#pragma pack()
extern REC_AD g_96f0[];
extern int g_959e;
extern int g_9156;
extern int g_9316;

void far fn_10_1eb6();              /* called with 3 args; the callee reads 1 */
void far fn_10_0552(int i, int a);
void far fn_10_5102(void);
void far fn_10_5202(void);
void far fn_10_5c42(void);
void far fn_16_3784(int a, int b);
void far fn_10_5d3c(int i);
void far fn_08_2cd8(int a, int b);
void far fn_06_0f1a(int v, char far *buf);
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
extern int g_1ca2;
extern int g_1ca4;
extern int g_88e8;
extern int g_88ea;
extern char g_a1d5[];

typedef struct {                /* far pointer at DS:1e34 */
    int f00;
    int f02;
    int f04;
    int f06;
    int f08;
    int f0a;
    int f0c;
    int f0e;
    int f10;
    int f12;
    char p14[0x20 - 0x14];
    int f20;
    int f22;
    int f24;
    char p26[0x28 - 0x26];
    int f28;
} REC_1E34;
extern REC_1E34 far *g_1e34;
extern int g_88c0;
extern int g_88c2;
extern long g_88cc;

extern REC_6DA4 far *g_6da4;
extern REC_15A g_70ae[];
extern int g_9646;
extern unsigned char g_a172[4];
extern unsigned char g_a176;
extern unsigned char g_a177;
extern char g_a178;
extern char g_a179;
extern char g_a17a;
extern HGLOBAL g_9100[];
typedef struct {                /* 0x70-byte records */
    int f00;
    int f02;
    int f04;
    int f06;
    char p08[0x0c - 0x08];
    int f0c;
    int f0e;
    char p10[0x20 - 0x10];
    int f20;
    int f22;
    char p24[0x70 - 0x24];
} REC_70;
extern REC_70 far *g_1df8[21];      /* 0-14: 0x460-byte blocks, 15-20: 0x70 */
extern int g_9324;
extern int g_1318;
extern int g_0010;
extern int g_8d14;
extern int g_8d16;
extern int g_8d18;
extern int g_8d1a;
extern int g_88ec;                  /* window origin, negated [inferred] */
extern int g_88ee;

typedef struct { int f00; char p02[0x12]; } REC_14;     /* 0x14 bytes */
typedef struct { int f00; char p02[0x92]; } REC_94;     /* 0x94 bytes */

extern REC_14 g_1e90[45];
extern REC_94 g_610e[9];
extern REC_14 g_58cc[20];
extern int g_9510;
extern long g_88d0;
extern int g_a1d3;
extern int g_a1d1;
extern int g_942a;
typedef struct {                /* far pointer at DS:1e40 */
    POINT f00;
    POINT f04;
    char p08[0x0c - 0x08];
    int f0c;
    int f0e;
    char p10[0x18 - 0x10];
    int f18;
    int f1a;
    char p1c[0x24 - 0x1c];
    int f24;
    char p26[0x28 - 0x26];
    int f28;
} REC_1E40;
typedef struct { RECT rc; char p08[0x18 - 0x08]; } REC_18;   /* DS:8870 */
extern REC_18 g_8870[];
extern POINT g_1050[];
POINT far pascal fn_08_2bbe(POINT p);
void far fn_06_84fc(int a, int x, int y, int dx, int dy, int w, int h,
                    int c, int d, int e);
extern REC_1E40 far *g_1e40;

extern int g_238c;
extern int g_238e;
extern int g_2390;
extern int g_2392;
extern int g_90ea;
extern int g_90ec;
extern DWORD g_1e50;
extern DWORD g_2408;

void far sprite_dc_release(void);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_10_7480(int a, int b);
void far fn_10_744c(int a);
void far fn_12_6d64(int a, int b);
int far fn_06_7c14(void);
POINT far pascal fn_08_29ea(POINT pt);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
void far fn_18_17f6(void);
void far fn_18_1cbe(int a);
void far fn_18_52a0(void);
void far fn_13_65f2(int);
void far fn_11_02f0(void);
int far pascal fn_08_19b0(int dx, int dy);
int far fn_09_88ba(int x);
extern signed char g_a198;
extern int g_9676;
extern HDC g_966a;
extern int g_9678;
extern POINT g_88f4[];
extern POINT g_8904[];
extern POINT g_8914[];
extern int g_a16a[];
extern HDC g_9656;
extern int g_3a36;
extern int g_a187[];
extern int g_a17f[];
extern POINT g_a199[];
extern POINT g_a1a9[];
extern POINT g_a1b9[];
extern HGDIOBJ g_3b44[3];
extern int g_a1c9;
extern int g_a1cb;
typedef struct {                /* 0x94 bytes at DS:6098 (seen as DS:610e) */
    int x[2][6];
    int y[2][6];
    char p30[0x74 - 0x30];
    int f74;
    int f76;
    int f78;
    char p7a[0x94 - 0x7a];
} REC_6098;
extern REC_6098 g_6098[];
int far fn_09_955c(UINT id, LPSTR buf);
void far fn_09_9580(UINT id, LPSTR dst);

/* @addr 18:034c */
void far fn_18_034c(void)
{
    if (g_9668) {
        SelectClipRgn(g_13dc, g_9668);
        g_9672 = 1;
    }
}

/* @addr 18:0378 */
void far fn_18_0378(int demon)
{
    long unused;

    g_8d34 = 0;
    g_965e = g_9660 = 0;
    if (demon) {
        g_9130 = 1;
        sprite_dc_release();
    }
    fn_13_65f2(3);
    fn_11_02f0();
    lstrcpy(g_6da4->f08, "Inner Demon");
    if (g_90f4 != 6)
        g_9530 = 1;
}

/* Creates the eight solid brushes [inferred]. */
/* @addr 18:0b1e */
void far fn_18_0b1e(void)
{
    if (!g_88d8[0]) {
        g_88d8[0] = CreateSolidBrush(RGB(255, 0, 0));
        g_88d8[1] = CreateSolidBrush(RGB(128, 0, 0));
        g_88d8[2] = CreateSolidBrush(RGB(255, 255, 0));
        g_88d8[3] = CreateSolidBrush(RGB(128, 128, 0));
        g_88d8[4] = CreateSolidBrush(RGB(0, 255, 255));
        g_88d8[5] = CreateSolidBrush(RGB(0, 128, 128));
        g_88d8[6] = CreateSolidBrush(RGB(255, 255, 255));
        g_88d8[7] = CreateSolidBrush(RGB(192, 192, 192));
    }
}

/* @addr 18:0ba0 */
void far fn_18_0ba0(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (g_88d8[i]) {
            DeleteObject(g_88d8[i]);
            g_88d8[i] = 0;
        }
    }
}

/* @addr 18:0d4e */
void far fn_18_0d4e(int msg, int key)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 == 1 && g_1318 <= 1)
                    g_9530 = 2;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 18:633c */
void far fn_18_633c(void)
{
    int i;

    g_a1cf = g_a1cd = 0;
    for (i = 0; i < 4; i++)
        g_a18f[i] = g_a193[i] = 1;
}

/* @addr 18:1784 */
void far fn_18_1784(int left, int top, int right, int bottom)
{
    DWORD org;

    if (g_90f4 != 1) {
        if (g_9668) {
            DeleteObject(g_9668);
            g_9668 = 0;
        }
        org = GetWindowOrg(g_13dc);
        g_88ec = LOWORD(org);
        g_88ee = HIWORD(org);
        g_88ec = -g_88ec;
        g_88ee = -g_88ee;
        g_9668 = CreateRectRgn(left + g_88ec, top + g_88ee,
                               right + g_88ec, bottom + g_88ee);
    }
}

/* @addr 18:1e46 */
void far fn_18_1e46(void)
{
    int i;

    for (i = 15; i <= 20; i++) {
        if (g_9100[i]) {
            if (g_1df8[i]) {
                GlobalUnlock(g_9100[i]);
                g_1df8[i] = 0;
            }
            GlobalFree(g_9100[i]);
            g_9100[i] = 0;
        }
    }
}

/* @addr 18:0be2 */
void far fn_18_0be2(void)
{
    int i;

    if (g_6da4)
        g_6da4->f1c = 1;
    for (i = 0; i < 4; i++)
        g_70ae[g_9646].f08[i] = g_a172[i];
    g_70ae[g_9646].f00 = g_a176 * 10;
    g_70ae[g_9646].f06 = g_a177;
    g_70ae[g_9646].f8e = g_a178;
    g_70ae[g_9646].f8f = g_a179;
    g_70ae[g_9646].fce = g_a17a;
}

/* @addr 18:1dd0 */
int far fn_18_1dd0(void)
{
    int i;

    for (i = 15; i <= 20; i++) {
        if ((g_9100[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x70L)) == 0)
            return 0;
        if ((g_1df8[i] = (REC_70 far *)GlobalLock(g_9100[i])) == 0) {
            GlobalFree(g_9100[i]);
            return 0;
        }
    }
    return 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far pascal fn_18_1934(int a, int b, int c)
{
}

/* @addr 18:17f6 */
void far fn_18_17f6(void)
{
    int unused1;
    int unused2;

    g_9672 = 0;
    PatBlt(g_13dc, 0, 0, g_88c0, g_88c2 + g_88ea, BLACKNESS);
    fn_18_1cbe(1);
    fn_18_034c();
    PatBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
           7 << g_9156 * 2, 7 << g_9156 * 2, BLACKNESS);
    if (g_1318 <= 1) {
        BitBlt(g_13dc, g_88f4[0].x, g_88f4[0].y, g_9678, g_9678,
               g_966a, 0, g_9678, SRCCOPY);
        BitBlt(g_13dc, g_88f4[1].x, g_88f4[1].y, g_9678, g_9678,
               g_966a, g_9678, g_9678, SRCCOPY);
        BitBlt(g_13dc, g_88f4[2].x, g_88f4[2].y, g_9678, g_9678,
               g_966a, g_9678, 0, SRCCOPY);
        BitBlt(g_13dc, g_88f4[3].x, g_88f4[3].y, g_9678, g_9678,
               g_966a, 0, 0, SRCCOPY);
    }
    g_1e34->f10 = (g_1e34->f22 + g_1e34->f24) * g_1e34->f28 + g_1e34->f24;
    g_1e34->f12 = g_1e34->f24;
    fn_18_1934(0xf00, 1, g_3a36);
}

/* Draws the two score lines when they changed [inferred]. */
/* @addr 18:1cbe */
void far fn_18_1cbe(int force)
{
    char buf[80];

    if ((g_1ca2 != g_a1cd || force) && !g_9672) {
        g_1ca2 = g_a1cd;
        g_1ca4 = g_a1cf;
        if (force)
            PatBlt(g_13dc, 0, g_88c2, g_88e8, g_88ea, BLACKNESS);
        if (!g_9156) {
            LoadString(g_9212, 0x7f0, buf, 80);
            if (g_a1cd) {
                fn_06_0f1a(g_a1cd, g_a1d5);
                lstrcat(buf, g_a1d5);
            } else
                lstrcat(buf, "0");
            fn_10_94c4(2, 0, PALETTERGB(255, 128, 0), 0, g_88c2, buf);
            LoadString(g_9212, 0x7f1, buf, 80);
            fn_06_0f1a(g_a1cf, g_a1d5);
            lstrcat(buf, g_a1d5);
            fn_10_94c4(2, 2, PALETTERGB(0, 255, 0), g_88c0 - 6, g_88c2, buf);
        }
    }
}

/* @addr 18:5220 */
void far fn_18_5220(int a)
{
    int i;

    if (g_90f4 == 1) {
        g_8d34 = GetCurrentTime() + 4000;
        fn_12_6d64(g_9646, a + 0x16);
        fn_10_744c(0x66);
    } else {
        g_a1cd += 10;
        g_a1d3++;
        fn_10_744c(0x25);
    }
    g_1e40->f1a = 0;
    g_942a = 0;
    for (i = 0; i < 12; i++)
        fn_06_7c14();
    if (g_90f4 == 6)
        fn_18_52a0();
}

/* @addr 18:52a0 */
void far fn_18_52a0(void)
{
    int ok;
    int i;

    ok = 1;
    for (i = 0; i < 4; i++)
        if (g_a18f[i])
            ok = 0;
    if (ok) {
        for (i = 0; i < 45; i++)
            g_1e90[i].f00 = -1;
        for (i = 0; i < 9; i++)
            g_610e[i].f00 = -1;
        for (i = 0; i < 20; i++)
            g_58cc[i].f00 = -1;
        g_9510 = 100;
        g_a1cf++;
        fn_10_7480(-2, 1);
        fn_18_17f6();
        fn_18_1cbe(1);
        g_88d0 = 2;
    }
}

/* @addr 18:591c */
void far fn_18_591c(void)
{
    if (g_238c) {
        fn_10_754a(8, rand() % g_90ea, rand() % g_90ec, 4);
        g_2390 += g_238c;
        g_2392 += g_238e;
        g_2390 += rand() % 3 - 2;
        g_2392 += rand() % 3 - 2;
        if (g_2390 > 5)
            g_238c = -9;
        else if (g_2390 < -5)
            g_238c = 9;
        if (g_2392 > 5)
            g_238e = -6;
        else if (g_2392 < -5)
            g_238e = 6;
        if (g_2408 < g_1e50)
            g_238c = 0;
        if (g_90f4 == 6) {
            g_2390 >>= 1;
            g_2392 >>= 1;
        }
    } else {
        *(long *)&g_2390 = 0;   /* clears g_2390 and g_2392 in one dword store */
    }
}

/* @addr 18:5f74 */
void far fn_18_5f74(void)
{
    int x;
    int t;

    fn_10_744c(0x48);
    g_1df8[g_9324][g_9646].f0e = 0;
    g_1df8[g_9324][g_9646].f0c = g_1df8[g_9324][g_9646].f0e;
    g_1318 = 2;
    t = (g_90ec * 4 / 3 - 1100) / 36 + 164;
    x = min((g_90ea - t) / 2 - 20, 260);
    g_8d14 = x - 18;
    g_8d16 = 164;
    g_8d1a = min(g_0010 * 2 / 5, g_0010 - 370);
    g_8d18 = max(g_90ea / -13 - x + g_90ea / 2 - 90, 0);
}

/* @addr 18:0c5c */
void far fn_18_0c5c(void)
{
    int i;

    for (i = 0; i < 4; i++)
        g_a172[i] = (unsigned char)g_70ae[g_9646].f08[i];
    g_a176 = g_70ae[g_9646].f00 / 10;
    g_a177 = (unsigned char)g_70ae[g_9646].f06;
    g_a178 = g_70ae[g_9646].f8e;
    g_a179 = g_70ae[g_9646].f8f;
    g_a17a = g_70ae[g_9646].fce;
    for (i = 0; i < 4; i++)
        g_70ae[g_9646].f08[i] = g_6e24[g_70ae[g_9646].fb8].f38[i];
    g_70ae[g_9646].f00 = 40 * g_6e24[g_70ae[g_9646].fb8].f1c;
    g_70ae[g_9646].f06 = g_6e24[g_70ae[g_9646].fb8].f74;
    g_70ae[g_9646].f8e = g_6e24[g_70ae[g_9646].fb8].f72;
    g_70ae[g_9646].f8f = g_6e24[g_70ae[g_9646].fb8].f73;
    g_70ae[g_9646].fce = 1;
}

/* @addr 18:337c */
void far fn_18_337c(void)
{
    g_1e34->f20 = (int)(g_1e34->f22 * g_88cc / g_88c0);
    g_1e34->f04 = (int)g_88cc / 2 - g_1e34->f20 / 2;
    g_1e34->f06 = (int)(g_88c2 * g_88cc / g_88c0) / 2 - g_1e34->f20 / 2;
    g_1e34->f00 = g_88c0 / 2 - g_1e34->f22 / 2;
    g_1e34->f08 = g_1e34->f00;
    g_1e34->f02 = g_88c2 / 2 - g_1e34->f22 / 2;
    g_1e34->f0a = g_1e34->f02;
    g_1e34->f0c = 0;
    g_1e34->f0e = 0;
}

/* @addr 18:4faa */
void far fn_18_4faa(int k)
{
    POINT pt;
    int r;

    if (k == 0 || k == 3)
        pt.x = g_8870[k].rc.right + 2;
    else
        pt.x = g_8870[k].rc.left - 2;
    pt.y = (g_8870[k].rc.bottom - g_8870[k].rc.top) / 2 + g_8870[k].rc.top;
    r = (4 - k) * 4 % 16;
    g_1e40->f04 = fn_08_2bbe(pt);
    g_1e40->f0c = g_1050[r].x * 5;
    g_1e40->f0e = g_1050[r].y * 5;
    g_1e40->f28 = k;
    g_1e40->f1a = 1;
    g_1e40->f18 = 1;
    g_1e40->f24 = 0;
    g_942a = 1;
    fn_10_744c(0x6e);
    fn_06_84fc((rand() % 2 + 1) * 10, 0, 0, 0, 0, 0, 0, 0, 400, k);
}

/* @addr 18:07b2 */
void far fn_18_07b2(void)
{
    int b;
    int a;
    int i;

    g_70ae[g_9646].f8e = g_6e24[g_70ae[g_9646].fb8].f72;
    g_70ae[g_9646].f8f = g_6e24[g_70ae[g_9646].fb8].f73;
    a = g_70ae[g_9646].f8e;
    b = g_70ae[g_9646].f8f;
    g_9156 = g_959e;
    fn_10_1eb6(g_9646, g_70ae[g_9646].f30, 1);
    fn_10_0552(0x22, 1);
    fn_10_0552(0xc, 1);
    fn_10_0552(0xa, 1);
    fn_10_5102();
    fn_10_5202();
    fn_10_5c42();
    fn_16_3784(g_9646, 2);
    for (i = 0; i <= g_9316; i++)
        fn_10_5d3c(i);
    if (g_70ae[g_9646].fc6 && g_96f0[g_70ae[g_9646].f30].f0a == 3) {
        if (!a)
            fn_08_2cd8(g_9646, 0);
        if (!b)
            fn_08_2cd8(g_9646, 1);
    }
}

/* The same 0x15a-byte records seen from DS:7090 (seg 3/4 base). */
typedef struct {
    char p00[0x0a];
    int f0a;
    char p0c[0x15a - 0x0c];
} REC_7090;
extern REC_7090 g_7090[];

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_18_1eac(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_18_2fee(int n)
{
}

/* @addr 18:621e */
void far fn_18_621e(void)
{
    int i;

    g_a1d1 = g_a1cd;
    g_a1d3 = 0;
    g_6da4->f1c = 1;
    for (i = 0; i < 4; i++)
        g_a18f[i] = g_a193[i] = 1;
    fn_18_1eac();
    g_1df8[20][g_9646].f04 = (int)g_88cc / 2;
    g_1df8[20][g_9646].f06 = 150;
    g_1df8[20][g_9646].f00 = -1000;
    g_1df8[20][g_9646].f02 = -1000;
    g_1df8[20][g_9646].f0c = 50;
    g_1df8[20][g_9646].f0e = 0;
    for (i = 0; i < 4; i++)
        g_70ae[g_9646].f08[i] = 100;
    g_70ae[g_9646].f00 = g_96f0[g_70ae[g_9646].f30].f00;
    if (!g_70ae[g_9646].f8e || !g_70ae[g_9646].f8f)
        fn_18_2fee(g_9646);
    if ((g_70ae[g_9646].f06 = g_7090[g_9646].f0a) == 2)
        g_70ae[g_9646].fc2 = g_70ae[g_9646].fc3 = 1;
    fn_10_7480(-3, 1);
}

/* near-match 58%: 18:3f02 (branch 1 register allocation, 4 bytes more frame) */
void far fn_18_3f02(int x, int y, int k)
{
    int unused1;
    int a;
    int dir;
    int t;
    int t1;
    int t2;
    POINT d;

    fn_10_754a(0x10, x, y, 4);
    a = g_1e34->f28;
    d.x = x - g_1e34->f20 / 2 - g_1e34->f04;
    d.y = y - g_1e34->f20 / 2 - g_1e34->f06;
    dir = (fn_08_19b0(d.x, d.y) + 8) % 16;
    t1 = fn_09_88ba(dir - a);
    t2 = fn_09_88ba(dir > a ? dir - a - 16 : dir - a + 16);
    t = min(t2, t1);
    if (g_90f4 == 1)
        g_9676 = min(max((21 - g_a198 * 5) * t * k * 2 / 20, (6 - g_a198) * 4) + g_9676,
                     (10 - g_a198) * 12);
    else {
        g_9676 = min(max((8 - g_a198) * t * k * 6 / 20, (13 - g_a198) * 2) + g_9676,
                     (15 - g_a198) * 8);
        g_9676 = max(g_9676, 18);
    }
}

/* @addr 18:50ac */
void far fn_18_50ac(void)
{
    int unused1;
    int unused2;
    POINT pt;
    int d;
    int b;
    int a;

    if (g_1e40->f1a) {
        g_1e40->f00 = fn_08_29ea(g_1e40->f04);
        g_1e40->f24++;
        if (g_1e40->f24 % 5 == 1) {
            int m;

            m = max(10 - g_a198, 0);
            g_1e40->f0c = (m + 28) * g_1e40->f0c / (m + 29);
            g_1e40->f0e = g_1e40->f0e * (m + 28) / (m + 29);
        }
        g_1e40->f00 = fn_08_29ea(g_1e40->f04);
        g_1e40->f04.x += g_1e40->f0c;
        g_1e40->f04.y += g_1e40->f0e;
        if (fn_06_7c14()) {
            g_1e40->f1a = 0;
            g_942a = 0;
            if (g_90f4 == 6)
                fn_18_52a0();
        }
        pt.x = g_1df8[g_9324][g_9646].f20 / 2 + g_1df8[g_9324][g_9646].f04;
        pt.y = g_1df8[g_9324][g_9646].f20 / 2 + g_1df8[g_9324][g_9646].f06;
        d = fn_08_285a(&b, &a, g_1e40->f04, pt);
        if (g_1e40->f24 > 40 && g_1df8[g_9324][g_9646].f22 > d)
            fn_18_5220(g_1e40->f28);
    }
}

/* @addr 18:5350 */
void far fn_18_5350(int x, int y)
{
    int k;
    int sy;
    int sx;

    if (g_1318 <= 6) {
        k = 5;
        if (y == -1 && x < 0 && x > -5)
            k = -x;
        else if (x < g_88c0 / 3) {
            if (y < g_88c2 / 2) {
                k = 3;
                sy = sx = 0;
            } else {
                sx = k = 0;
                sy = g_9678;
            }
        } else if (x > g_88c0 * 2 / 3) {
            if (y < g_88c2 / 2) {
                k = 2;
                sx = g_9678;
                sy = 0;
            } else {
                k = 1;
                sy = sx = g_9678;
            }
        }
        if (k < 5) {
            PatBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                   7 << g_9156 * 2, 7 << g_9156 * 2, BLACKNESS);
            BitBlt(g_13dc, g_88f4[k].x, g_88f4[k].y, g_9678, g_9678,
                   g_966a, sx, sy, SRCCOPY);
            BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                   7 << g_9156 * 2, 7 << g_9156 * 2,
                   g_966a, g_8914[k].x, g_8914[k].y, SRCCOPY);
            if (g_a18f[k])
                BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                       7 << g_9156 * 2, 7 << g_9156 * 2,
                       g_9656, g_a16a[k] / 40 * 7 << g_9156 * 2, 0, SRCPAINT);
            BitBlt(g_13dc, g_8904[k].x, g_8904[k].y, 7 << g_9156 * 2, 7 << g_9156 * 2,
                   g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678, SRCCOPY);
        } else
            fn_18_1934(0xf00, 1, g_3a36);
    }
}

/* Draws the end-of-level score screen [inferred]. */
/* @addr 18:6046 */
void far fn_18_6046(void)
{
    char buf[100];

    PatBlt(g_13dc, 0, 0, g_6da4->f02, g_6da4->f04, BLACKNESS);
    fn_10_744c(0x6e);
    fn_10_744c(0x66);
    fn_09_955c(0x7f1, buf);
    fn_06_0f1a(g_a1cf, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_09_9580(0x7f3, buf);
    fn_10_94c4(2, 6, PALETTERGB(255, 255, 0), g_6da4->f02 / 2, g_6da4->f04 / 2 - 46, buf);
    LoadString(g_9212, 0x7f2, buf, 100);
    fn_06_0f1a(g_a1cd - g_a1d1, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_10_94c4(2, 6, PALETTERGB(245, 61, 0), g_6da4->f02 / 2, g_6da4->f04 / 2 - 18, buf);
    LoadString(g_9212, 0x7f4, buf, 100);
    fn_06_0f1a(g_a1d3, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_10_94c4(2, 6, PALETTERGB(245, 61, 0), g_6da4->f02 / 2, g_6da4->f04 / 2, buf);
    LoadString(g_9212, 0x7f5, buf, 100);
    fn_06_0f1a(g_a1cd, g_a1d5);
    lstrcat(buf, g_a1d5);
    fn_10_94c4(2, 6, PALETTERGB(245, 61, 0), g_6da4->f02 / 2, g_6da4->f04 / 2 + 18, buf);
}

/* @addr 18:4dc4 */
int far pascal fn_18_4dc4(int n)
{
    int unused1;
    int unused2;
    int unused3;
    int unused4;
    int w;
    int k;
    int j;
    int unused5;
    int unused6;
    HGDIOBJ old;

    w = 2 << g_9156;
    if (g_a17f[n] >= 0 && g_a17f[n] < g_a187[n]) {
        MoveTo(g_13dc, g_a1b9[n].x, g_a1b9[n].y);
        g_a1b9[n].x = (int)(g_a199[n].x * (long)g_88c0 / g_88cc);
        g_a1b9[n].y = (int)(g_a199[n].y * (long)g_88c0 / g_88cc);
        old = SelectObject(g_13dc, g_3b44[rand() % 3]);
        if (g_a17f[n] > 0)
            LineTo(g_13dc, g_a1b9[n].x, g_a1b9[n].y);
        SelectObject(g_13dc, old);
        g_a199[n].x += g_a1a9[n].x;
        g_a199[n].y += g_a1a9[n].y;
        g_a17f[n]++;
    }
    if (g_a17f[n] >= g_a187[n]) {
        g_6098[n].f76 = g_6098[n].f74;
        g_a17f[n] = -1;
        for (k = 5; k > -1; k--)
            for (j = 0; j < g_6098[n].f78; j++)
                PatBlt(g_13dc, g_6098[n].x[j][k], g_6098[n].y[j][k], w, w, BLACKNESS);
        old = SelectObject(g_13dc, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));
        MoveTo(g_13dc, g_a1c9, g_a1cb);
        LineTo(g_13dc, g_a1b9[n].x, g_a1b9[n].y);
        SelectObject(g_13dc, old);
        fn_10_744c(0x16);
        g_a17f[n] = -1;
    }
    return 0;
}
