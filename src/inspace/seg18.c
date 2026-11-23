/* INSPACE.EXE segment 18 (selector 1088). */
#include "inspace.h"
#include <stdlib.h>
extern DWORD g_1e50;

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
    char p32[0x3d - 0x32];
    char f3d;
    char p3e[0x42 - 0x3e];
    char f42;
    char p43[0x66 - 0x43];
    DWORD f66;
    char p6a[0x8e - 0x6a];
    char f8e;
    char f8f;
    char p90[0x9a - 0x90];
    signed char f9a[0xad - 0x9a];
    signed char fad;
    char pae[0xb8 - 0xae];
    int fb8;
    char pba[0xc2 - 0xba];
    char fc2;
    char fc3;
    char pc4[0xc6 - 0xc4];
    char fc6;
    char pc7[0xcb - 0xc7];
    char fcb;
    char pcc[0xce - 0xcc];
    char fce;
    char pcf[0x15a - 0xcf];
} REC_15A;

typedef struct {                /* 0x7c-byte records at far DS:6e24 */
    int f00;
    char p02[0x1c - 0x02];
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
    char p2a[0x44 - 0x2a];
    int f44;
} REC_1E34;
extern REC_1E34 far *g_1e34;
extern int g_88c0;
extern int g_92e4;
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
    int f08;
    int f0a;
    int f0c;
    int f0e;
    int f10;
    int f12;
    char p14[0x18 - 0x14];
    int f18;
    int f1a;
    char p1c[0x1e - 0x1c];
    int f1e;
    int f20;
    int f22;
    int f24;
    char p26[0x28 - 0x26];
    int f28;
    char p2a[0x2c - 0x2a];
    int f2c;
    char f2e;
    signed char f2f;
    char p30[0x32 - 0x30];
    int f32;
    char p34[0x36 - 0x34];
    int f36;
    char p38[0x3c - 0x38];
    int f3c;
    char p3e[0x42 - 0x3e];
    int f42;
    int f44;
    int f46;
    int f48;
    char p4a[0x4c - 0x4a];
    DWORD f4c;
    char p50[0x53 - 0x50];
    char f53;
    char f54;
    char p55[0x5e - 0x55];
    int (far *f5e)(int type, int idx);
    void (far *f62)(void);
    void (far *f66)(int type, int idx);
    char p6a[0x70 - 0x6a];
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
    int x1[2][6];
    int y1[2][6];
    char p60[0x70 - 0x60];
    int f70;
    int f72;
    int f74;
    int f76;
    int f78;
    int f7a;
    int f7c;
    char p7e[0x82 - 0x7e];
    int f82;
    char p84[0x94 - 0x84];
} REC_6098;
extern REC_6098 g_6098[];
extern int g_073e;
extern int g_9664;
extern int g_9674;
extern char g_a197;
extern long g_88d4;
extern int g_9326;
extern int g_9328;
extern int g_934a;
extern int g_94c4;
extern int g_9330;
extern POINT g_88c4;
extern int g_88f0;
extern int g_88f2;
extern int g_13a0;
void far fn_06_7266(void);
void far fn_06_72d8(int n, int m);
void far fn_10_58ce(int a);
extern int g_9320;
extern DWORD g_1e68;
extern DWORD g_8e2c;
extern int g_9318;
extern int g_0992;
extern int g_932a;
extern int g_91f8;
extern int g_93ac;
extern int g_92e8;
extern int g_913e;
extern int g_9406[];
extern POINT g_88c8;
extern unsigned g_9666;
extern int g_913a;
extern DWORD g_2384;
extern int flow_interactive;        /* DS:95bc */
int far fn_09_955c(UINT id, LPSTR buf);
void far fn_09_9580(UINT id, LPSTR dst);

extern HPALETTE g_9670;
extern HBITMAP g_966e;
extern HBITMAP g_966c;
extern HPALETTE g_965c;
extern HBITMAP g_965a;
extern HBITMAP g_9658;
extern int g_952e;
extern int g_9e5b;
extern int g_93a6;
extern int g_0928;
extern int g_914a;
extern int music_pause_state;       /* DS:9222 */
extern int g_8e64;
extern LPARAM g_1d38;
extern DWORD g_05a4;
extern DWORD g_05b8;
extern int g_9136;
extern int g_0594;
extern int g_0598;
extern int g_9430;
extern int g_9434;
extern int g_1c9e;
extern int g_9146;
extern int g_1016;
extern int g_9456;
void far sprite_dc_restore(void);
void far fn_11_1d7c(void);
void far fn_11_592a(void);
void far fn_07_2128(void);
void far fn_11_4db0(void);
int far pascal fn_08_3aec(int j, int i);
void far pascal fn_08_3fbe(int i);
void far fn_07_375a(void);
void far fn_08_4e14(void);
void far fn_11_a9ea(int a);
void far fn_07_40c4(void);
void far fn_07_3bae(void);
void far fn_07_5e04(void);
void far fn_13_447a(void);
void far fn_18_03d6(void);
void far fn_18_0d94(void);
void far fn_18_37d8(void);
void far fn_18_403e(void);
void far fn_18_08bc(int big);
void far fn_18_6046(void);
void far fn_18_621e(void);
void far fn_18_034c(void);
void far fn_18_0d4e(int msg, int key, LPARAM lp);
void far fn_18_50ac(void);

#pragma pack(1)
typedef struct {                /* 0xad-byte class records, lowest field DS:96d6 */
    int f00;
    char p02[0x14 - 0x02];
    char f14;
    char p15;
    char f16;
    char p17[0x26 - 0x17];
    int f26;                    /* sprite cell size */
    char p28[0x2e - 0x28];
    int f2e;
    char p30[0x32 - 0x30];
    int f32;
    char p34[0x38 - 0x34];
    int f38;
    char p3a[0x64 - 0x3a];
    int f64;
    int f66;
    int f68;
    int f6a;
    char p6c[0x80 - 0x6c];
    char f80[0xa5 - 0x80];      /* name [inferred] */
    long fa5;
    char pa9[0xad - 0xa9];
} REC_AD6;
typedef struct {                /* 0x41-byte records at far DS:6e20 */
    char p00[0x21];
    int f21;
    char p23[0x41 - 0x23];
} REC_41;
typedef struct {                /* 0x2c-byte records at far DS:6e1c */
    char p00[0x1a];
    signed char f1a;
    char p1b[0x1e - 0x1b];
    signed char f1e;
    signed char f1f;
    char p20[0x2c - 0x20];
} REC_2C;
#pragma pack()
extern REC_AD6 g_96d6[];
extern REC_41 far *g_6e20;
extern REC_2C far *g_6e1c;
extern int g_931c;
extern HDC g_39e8[];
extern HBITMAP g_3974[];
extern HBITMAP g_3ad0[];
extern HPALETTE g_3a5c[];
void far fn_10_6ee6(int idx, int a, LPSTR name, int b, int c, long d, int e,
                    int f, char g, char h, char mode, int i);
int far fn_10_86ca(void);
void far fn_10_9962(int a, HDC dst, int x, int y, int w, int h, HDC src,
                    int sx, int sy, int sw, int sh, DWORD rop);
int far fn_14_3eda(void);
void far fn_14_4074(void);

extern int g_930a;
extern int g_9424;
extern int g_9428;
extern int g_942c;
extern int g_9312;
extern int g_930e;
extern int g_9314;
extern int g_942e;
extern int g_92ec[];
extern char g_a191;
extern char g_a192;
extern char g_a17b[];
void far fn_11_3914(void);
int far fn_07_570a(int type, int idx);
int far fn_07_2652(int type, int idx);
void far fn_12_274a(int type, int idx);
void far fn_11_39d8(void);
int far fn_07_5090(int type, int idx);
void far fn_18_633c(void);
HBITMAP far fn_10_6fec(int a, LPSTR s, int b, int c, int d, int e, int f,
                       int g, int h, int i, int j, int k);
void far fn_18_270e(int w, int h);

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
void far fn_18_0d4e(int msg, int key, LPARAM lp)
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

/* Moves object (type << 8 | idx) to its scaled map position and redraws
 * it from src: erases the uncovered part of the old square, then blits
 * the new one [inferred]. */
/* @addr 18:1934 */
int far pascal fn_18_1934(int key, int unused, HDC src)
{
    int type;
    int idx;
    int u0;
    int u5;
    int u1;
    POINT d;
    int u2;
    int u3;
    int u4;

    type = (unsigned char)(key >> 8);
    idx = (unsigned char)key;
    g_1df8[type][idx].f08 = g_1df8[type][idx].f00;
    g_1df8[type][idx].f0a = g_1df8[type][idx].f02;
    g_1df8[type][idx].f00 =
        (int)((long)g_1df8[type][idx].f04 * g_88c0 / g_88cc) + g_88c4.x;
    g_1df8[type][idx].f02 =
        (int)((long)g_1df8[type][idx].f06 * g_88c0 / g_88cc) + g_88c4.y;
    if (type != 15) {
        g_1df8[type][idx].f00 += g_2390;
        g_1df8[type][idx].f02 += g_2392;
    }
    d.x = g_1df8[type][idx].f00 - g_1df8[type][idx].f08;
    d.y = g_1df8[type][idx].f02 - g_1df8[type][idx].f0a;
    if (g_1df8[type][idx].f24 < fn_09_88ba(d.x)
        || g_1df8[type][idx].f24 < fn_09_88ba(d.y)) {
        if (fn_09_88ba(d.x) < g_1df8[type][idx].f22
            && fn_09_88ba(d.y) < g_1df8[type][idx].f22) {
            if (d.x < 0) {
                if (d.y < 0) {
                    PatBlt(g_13dc, g_1df8[type][idx].f22 + g_1df8[type][idx].f00,
                           g_1df8[type][idx].f02, -d.x,
                           g_1df8[type][idx].f22 - d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f00,
                           g_1df8[type][idx].f02 + g_1df8[type][idx].f22,
                           g_1df8[type][idx].f22, -d.y, BLACKNESS);
                } else {
                    PatBlt(g_13dc, g_1df8[type][idx].f22 + g_1df8[type][idx].f00,
                           g_1df8[type][idx].f02 - d.y, -d.x,
                           g_1df8[type][idx].f22 + d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f00,
                           g_1df8[type][idx].f02 - d.y,
                           g_1df8[type][idx].f22, d.y, BLACKNESS);
                }
            } else {
                if (d.y < 0) {
                    PatBlt(g_13dc, g_1df8[type][idx].f00 - d.x,
                           g_1df8[type][idx].f02, d.x,
                           g_1df8[type][idx].f22 - d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f00,
                           g_1df8[type][idx].f02 + g_1df8[type][idx].f22,
                           g_1df8[type][idx].f22, -d.y, BLACKNESS);
                } else {
                    PatBlt(g_13dc, g_1df8[type][idx].f00 - d.x,
                           g_1df8[type][idx].f02 - d.y, d.x,
                           g_1df8[type][idx].f22 + d.y, BLACKNESS);
                    PatBlt(g_13dc, g_1df8[type][idx].f00,
                           g_1df8[type][idx].f02 - d.y,
                           g_1df8[type][idx].f22, d.y, BLACKNESS);
                }
            }
        } else
            PatBlt(g_13dc, g_1df8[type][idx].f08, g_1df8[type][idx].f0a,
                   g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
        BitBlt(g_13dc, g_1df8[type][idx].f00, g_1df8[type][idx].f02,
               g_1df8[type][idx].f22, g_1df8[type][idx].f22, src,
               g_1df8[type][idx].f10, g_1df8[type][idx].f12, SRCCOPY);
    } else {
        BitBlt(g_13dc, g_1df8[type][idx].f00 - (d.x < 0 ? 0 : d.x), g_1df8[type][idx].f02 - (d.y < 0 ? 0 : d.y),
               fn_09_88ba(d.x) + g_1df8[type][idx].f22,
               fn_09_88ba(d.y) + g_1df8[type][idx].f22, src,
               g_1df8[type][idx].f10 - (d.x < 0 ? 0 : d.x), g_1df8[type][idx].f12 - (d.y < 0 ? 0 : d.y),
               SRCCOPY);
    }
    return 1;
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

/* Resets the Demon sub-game objects and their arrays [inferred]. */
/* @addr 18:1eac */
void far fn_18_1eac(void)
{
    int i;
    int j;
    int k;

    g_9424 = g_930a = 1;
    g_930e = g_942c = g_9312 = g_942a = g_9428 = 0;
    g_942e = g_9314 = g_9316 + 1;
    for (i = 15; i <= 20; i++) {
        GlobalUnlock(g_9100[i]);
        g_9100[i] = GlobalReAlloc(g_9100[i], (long)max(g_92ec[i], 1) * 0x70, GHND);
        g_1df8[i] = (REC_70 far *)GlobalLock(g_9100[i]);
    }
    g_1df8[17]->f44 = 120;
    g_1df8[17]->f42 = 100;
    g_1df8[17]->f4c = 0xff;
    g_1df8[17]->f62 = fn_11_3914;
    g_1df8[17]->f5e = fn_07_570a;
    g_1df8[17]->f53 = 0;
    g_1df8[17]->f54 = 0;
    g_1df8[18]->f44 = 100;
    g_1df8[18]->f42 = 100;
    g_1df8[18]->f4c = 0xff;
    g_1df8[18]->f62 = fn_11_3914;
    g_1df8[18]->f5e = fn_07_570a;
    g_1df8[18]->f53 = 0;
    g_1df8[18]->f54 = 0;
    g_1df8[18]->f18 = 1;
    g_1df8[18]->f1a = 0;
    g_1df8[15]->f44 = 1000;
    g_1df8[15]->f18 = 0;
    g_1df8[15]->f42 = 18;
    g_1df8[15]->f46 = 6;
    g_1df8[15]->f2c = 500;
    g_1df8[15]->f48 = 10;
    g_1df8[15]->f5e = fn_07_2652;
    g_1df8[15]->f66 = fn_12_274a;
    g_1df8[15]->f53 = 0;
    g_1df8[15]->f54 = 1;
    g_1df8[15]->f2f = 7;
    g_1df8[16]->f44 = 20000;
    g_1df8[16]->f18 = 1;
    g_1df8[16]->f1a = 0;
    g_1df8[16]->f42 = 6;
    g_1df8[16]->f54 = 1;
    g_1df8[16]->f22 = 2;
    g_1df8[16]->f0e = 0;
    g_1df8[16]->f0c = g_1df8[16]->f0e;
    g_1df8[16]->f46 = 1;
    g_1df8[16]->f62 = fn_11_39d8;
    g_1df8[16]->f5e = fn_07_5090;
    for (i = g_9326; i <= g_9324; i++)
        for (j = 0; j < g_92ec[i]; j++) {
            g_1df8[i][j].f12 = g_1df8[i][j].f24;
            g_1df8[i][j].f2e = 0;
            g_1df8[i][j].f32 = -1;
            g_1df8[i][j].f36 = -1;
        }
    for (i = k = 0; i < 4; i++)
        g_a18f[i] = 1;
    for (i = 0; i < 4; i++) {
        for (j = 0; j <= g_70ae[g_9646].fad; j++) {
            if (g_90f4 == 1) {
                if (g_70ae[g_9646].f9a[j] == 0x1a)
                    g_a191 = g_a192 = 0;
                else if (g_70ae[g_9646].f9a[j] - i == 0x16)
                    g_a18f[i] = 0;
            }
        }
        if (g_90f4 == 6 && !g_a193[i]) {
            g_a18f[i] = 0;
            k++;
        }
    }
    if (k > 3)
        fn_18_633c();
    g_a198 = 0;
    if (g_90f4 == 1) {
        for (i = 0; i < 4; i++)
            if (!g_a18f[i])
                g_a198++;
    } else
        g_a198 = min(g_a1cf, 3);
    for (i = 0; i < 4; i++)
        if (g_a18f[i]) {
            g_a16a[i] = 0;
            g_a17b[i] = 5;
        }
    for (i = 0; i < 4; i++)
        g_a17f[i] = -1;
}

/* Rebuilds the sprite sheet of object n at the current zoom [inferred]. */
/* @addr 18:2fee */
void far fn_18_2fee(int n)
{
    int idx;
    int cls;
    int r;
    int c;
    int size;
    int gap;
    int t;
    int unused;
    int rows;
    int cell;
    HBITMAP hbm;
    HBITMAP oldbm;
    HDC hdc;
    HPALETTE oldpal;
    char mode;
    char pad[32];
    BITMAP bm;

    cls = g_70ae[n].f30;
    idx = n + 40;
    if (!g_39e8[idx] || !g_70ae[n].f8e || !g_70ae[n].f8f) {
        if (g_70ae[n].fc6)
            mode = 0;
        else
            mode = 2;
        if (g_70ae[n].fcb)
            mode = 1;
        fn_10_6ee6(idx, g_96d6[cls].f32, g_96d6[cls].f80, 1, 0,
                   g_96d6[cls].fa5, 1, -1, g_96d6[cls].f14,
                   g_96d6[cls].f16, mode, 0);
        g_96d6[cls].f26 = size = fn_10_86ca();
        gap = 4;
        SelectObject(g_39e8[idx], g_3974[idx]);
        GetObject(g_3ad0[idx], sizeof(BITMAP), &bm);
        SelectObject(g_39e8[idx], g_3ad0[idx]);
        rows = bm.bmHeight / size;
        hdc = CreateCompatibleDC(g_13dc);
        cell = size * (g_9156 * 2 + 1) / 3;
        hbm = CreateCompatibleBitmap(g_13dc, cell * 16 + 68,
                                     (cell + 4) * rows + 4);
        if (g_920e)
            oldpal = SelectPalette(hdc, g_920e, 0);
        oldbm = SelectObject(hdc, hbm);
        PatBlt(hdc, 0, 0, cell * 16 + gap * 17,
               cell * rows + (rows + 1) * gap, BLACKNESS);
        SetStretchBltMode(hdc, 3);
        for (r = 0; r < rows; r++)
            for (c = 0; c < 16; c++)
                fn_10_9962(0, hdc, cell * c + (c + 1) * gap,
                           cell * r + (r + 1) * gap, cell, cell,
                           g_39e8[idx], size * c, size * r, size, size,
                           SRCCOPY);
        SelectObject(g_39e8[idx], g_3974[idx]);
        if (g_920e)
            SelectPalette(g_39e8[idx], g_3a5c[idx], 0);
        DeleteDC(g_39e8[idx]);
        DeleteObject(g_3ad0[idx]);
        g_39e8[idx] = hdc;
        g_3ad0[idx] = hbm;
        g_3974[idx] = oldbm;
        g_3a5c[idx] = oldpal;
        g_1df8[20][n].f22 = cell;
        g_1df8[20][n].f24 = gap;
        g_1df8[20][n].f20 = (int)(g_1df8[20][n].f22 * g_88cc / g_88c0);
        g_70ae[n].f3d = rows - 1;
        if (g_96d6[cls].f00 < 0)
            g_96d6[cls].f00 = 4 - g_96d6[cls].f00 - size / 2;
        t = g_6e24[g_931c].f00;
        fn_14_3eda();
        g_96d6[cls].f38 = g_6e1c[g_6e20[t].f21].f1a * (g_9156 * 2 + 1) / 6;
        g_96d6[cls].f64 = g_6e1c[g_6e20[t].f21].f1e - size / 2;
        g_96d6[cls].f66 = g_6e1c[g_6e20[t].f21].f1f - size / 2;
        g_96d6[cls].f68 = -g_96d6[cls].f64;
        g_96d6[cls].f6a = g_96d6[cls].f66;
        fn_14_4074();
    }
    g_70ae[n].f8e = g_70ae[n].f8f = 1;
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

/* @addr 18:3f02 */
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
    if (dir > a)
        t2 = fn_09_88ba(dir - a - 16);
    else
        t2 = fn_09_88ba(dir - a + 16);
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

/* Builds the Demon's sprite sheet (DC 39) and the 2x2 corner bitmap at
 * DS:966a [inferred]. */
/* @addr 18:2272 */
void far fn_18_2272(void)
{
    int size;
    int cell;
    int sz2;
    int w35;
    int rows;
    int r;
    int c;
    int gap;
    HBITMAP hbm;
    HBITMAP oldbm;
    HDC hdc;
    HPALETTE oldpal;
    BITMAP bm;

    fn_10_6ee6(0x27, 0x42, "", 1, 0, 0x10001L, 1, g_9156 + 1, 12, 12, 2, 0);
    size = fn_10_86ca();
    cell = g_9156 > 0 ? size * 2 : size;
    gap = 4;
    SelectObject(g_39e8[39], g_3974[39]);
    GetObject(g_3ad0[39], sizeof(BITMAP), &bm);
    SelectObject(g_39e8[39], g_3ad0[39]);
    rows = bm.bmHeight / cell;
    sz2 = (g_9156 + 1) * size;
    hdc = CreateCompatibleDC(g_13dc);
    hbm = CreateCompatibleBitmap(g_13dc, sz2 * 16 + 68, (sz2 + 4) * rows + 4);
    if (g_920e)
        oldpal = SelectPalette(hdc, g_920e, 0);
    oldbm = SelectObject(hdc, hbm);
    PatBlt(hdc, 0, 0, sz2 * 16 + gap * 17, rows * sz2 + (rows + 1) * gap,
           BLACKNESS);
    SetStretchBltMode(hdc, 3);
    for (r = 0; r < rows; r++)
        for (c = 0; c < 16; c++)
            fn_10_9962(0, hdc, c * sz2 + (c + 1) * gap,
                       r * sz2 + (r + 1) * gap, sz2, sz2, g_39e8[39],
                       c * cell, r * cell, cell, cell, SRCCOPY);
    SelectObject(g_39e8[39], g_3974[39]);
    if (g_920e)
        SelectPalette(g_39e8[39], g_3a5c[39], 0);
    DeleteDC(g_39e8[39]);
    DeleteObject(g_3ad0[39]);
    g_39e8[39] = hdc;
    g_3ad0[39] = hbm;
    g_3974[39] = oldbm;
    g_3a5c[39] = oldpal;
    g_1df8[15]->f22 = sz2;
    g_1df8[15]->f24 = gap;
    w35 = 0x35 << g_9156;
    g_9678 = 0x35 << g_9156 * 2 >> 1;
    g_966a = CreateCompatibleDC(g_13dc);
    g_966c = CreateCompatibleBitmap(g_13dc, g_9678 * 2, g_9678 * 2);
    hdc = CreateCompatibleDC(g_13dc);
    if (g_920e) {
        g_9670 = SelectPalette(g_966a, g_920e, 0);
        oldpal = SelectPalette(hdc, g_920e, 0);
    }
    g_966e = SelectObject(g_966a, g_966c);
    PatBlt(g_966a, 0, 0, g_9678 * 2, g_9678 * 2, BLACKNESS);
    SetStretchBltMode(g_966a, 3);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 4, 12, 2, 0));
    fn_10_9962(0, g_966a, 0, g_9678, g_9678, g_9678, hdc, 0, 0, w35, w35,
               SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 16, 12, 2, 0));
    fn_10_9962(0, g_966a, g_9678 * 2 - 1, g_9678, -g_9678, g_9678, hdc, 0, 0,
               w35, w35, SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 9, 12, 2, 0));
    fn_10_9962(0, g_966a, g_9678 * 2 - 1, g_9678 - 1, -g_9678, -g_9678, hdc,
               0, 0, w35, w35, SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    oldbm = SelectObject(hdc, hbm = fn_10_6fec(0x3c0, "", 1, -100, 1, 1, 1,
                                               g_9156, 2, 12, 2, 0));
    fn_10_9962(0, g_966a, 0, g_9678 - 1, g_9678, -g_9678, hdc, 0, 0, w35, w35,
               SRCCOPY);
    SelectObject(hdc, oldbm);
    DeleteObject(hbm);
    if (g_920e)
        SelectPalette(hdc, oldpal, 0);
    DeleteDC(hdc);
    fn_18_270e(g_6da4->f02, g_6da4->f04);
}

extern RECT g_8860[];
extern POINT g_8ce4[];
extern int g_8d1c[];
#define SC(n) ((n) << g_9156)

/* Sets the Demon arena size and lays out its wall rectangles, bounce
 * points and corner pieces [inferred]. */
/* @addr 18:270e */
void far fn_18_270e(int w, int h)
{
    g_6da4->f02 = w;
    g_6da4->f04 = h;
    g_88c0 = w;
    g_88c2 = h - g_88ea;
    g_88f4[0].x = 0;
    g_88f4[0].y = g_88c2 - g_9678;
    g_88f4[1].x = g_88c0 - g_9678;
    g_88f4[1].y = g_88c2 - g_9678;
    g_88f4[2].x = g_88c0 - g_9678;
    g_88f4[2].y = 0;
    g_88f4[3].x = 0;
    g_88f4[3].y = 0;
    g_9156 <<= 1;
    SetRect(&g_8860[0], 0, g_88c2 - g_9678, SC(5), g_88c2 + SC(9) - g_9678);
    SetRect(&g_8860[1], 0, SC(9) - g_9678 + g_88c2, SC(14), g_88c2);
    SetRect(&g_8860[2], SC(14), SC(-12) + g_88c2, g_9678, SC(-2) + g_88c2);
    g_8ce4[0].x = SC(-15);
    g_8ce4[0].y = SC(-2) - g_9678 + g_88c2;
    g_8d1c[0] = SC(20);
    g_8ce4[1].x = SC(-3);
    g_8ce4[1].y = SC(9) - g_9678 + g_88c2;
    g_8d1c[1] = SC(18);
    g_8ce4[2].x = SC(14);
    g_8ce4[2].y = SC(14) - g_9678 + g_88c2;
    g_8d1c[2] = SC(13);
    SetRect(&g_8860[3], SC(-5) + g_88c0, g_88c2 - g_9678, g_88c0, SC(9) - g_9678 + g_88c2);
    SetRect(&g_8860[4], SC(-14) + g_88c0, SC(9) - g_9678 + g_88c2, g_88c0, g_88c2);
    SetRect(&g_8860[5], g_88c0 - g_9678, SC(-12) + g_88c2, SC(-14) + g_88c0, SC(-2) + g_88c2);
    g_8ce4[3].x = SC(-5) + g_88c0;
    g_8ce4[3].y = SC(-2) - g_9678 + g_88c2;
    g_8d1c[3] = SC(20);
    g_8ce4[4].x = SC(-16) + g_88c0;
    g_8ce4[4].y = SC(9) - g_9678 + g_88c2;
    g_8d1c[4] = SC(19);
    g_8ce4[5].x = SC(-27) + g_88c0;
    g_8ce4[5].y = SC(15) - g_9678 + g_88c2;
    g_8d1c[5] = SC(13);
    SetRect(&g_8860[6], SC(-5) + g_88c0, SC(-9) + g_9678, g_88c0, g_9678);
    SetRect(&g_8860[7], SC(-14) + g_88c0, 0, g_88c0, SC(-9) + g_9678);
    SetRect(&g_8860[8], g_88c0 - g_9678, SC(2), SC(-14) + g_88c0, SC(12));
    g_8ce4[6].x = SC(-5) + g_88c0;
    g_8ce4[6].y = SC(-18) + g_9678;
    g_8d1c[6] = SC(20);
    g_8ce4[7].x = SC(-16) + g_88c0;
    g_8ce4[7].y = SC(-28) + g_9678;
    g_8d1c[7] = SC(19);
    g_8ce4[8].x = SC(-27) + g_88c0;
    g_8ce4[8].y = SC(-29) + g_9678;
    g_8d1c[8] = SC(15);
    SetRect(&g_8860[9], 0, SC(-9) + g_9678, SC(5), g_9678);
    SetRect(&g_8860[10], 0, 0, SC(14), SC(-9) + g_9678);
    SetRect(&g_8860[11], SC(14), SC(2), g_9678, SC(12));
    g_8ce4[9].x = SC(-15);
    g_8ce4[9].y = SC(-18) + g_9678;
    g_8d1c[9] = SC(20);
    g_8ce4[10].x = SC(-3);
    g_8ce4[10].y = SC(-28) + g_9678;
    g_8d1c[10] = SC(19);
    g_8ce4[11].x = SC(13);
    g_8ce4[11].y = SC(-28) + g_9678;
    g_8d1c[11] = SC(14);
    g_9156 /= 2;
    g_8904[0].x = 18 / (4 - g_9156 * 3);
    g_8904[0].y = 52 / (4 - g_9156 * 3) - g_9678 + g_88c2;
    g_8904[1].x = -46 / (4 - g_9156 * 3) + g_88c0;
    g_8904[1].y = 52 / (4 - g_9156 * 3) - g_9678 + g_88c2;
    g_8904[2].x = -46 / (4 - g_9156 * 3) + g_88c0;
    g_8904[2].y = 26 / (4 - g_9156 * 3);
    g_8904[3].x = 18 / (4 - g_9156 * 3);
    g_8904[3].y = 26 / (4 - g_9156 * 3);
    g_8914[0].x = 18 / (4 - g_9156 * 3);
    g_8914[0].y = 52 / (4 - g_9156 * 3) + g_9678;
    g_8914[1].x = -46 / (4 - g_9156 * 3) + g_9678 * 2;
    g_8914[1].y = 52 / (4 - g_9156 * 3) + g_9678;
    g_8914[2].x = -46 / (4 - g_9156 * 3) + g_9678 * 2;
    g_8914[2].y = 26 / (4 - g_9156 * 3);
    g_8914[3].x = 18 / (4 - g_9156 * 3);
    g_8914[3].y = 26 / (4 - g_9156 * 3);
    g_1e34->f20 = (int)(g_1e34->f22 * g_88cc / g_88c0);
    g_1e34->f04 = (int)g_88cc / 2 - g_1e34->f20 / 2;
    g_1e34->f06 = (int)(g_88c2 * g_88cc / g_88c0) / 2 - g_1e34->f20 / 2;
    g_1e34->f00 = g_88c0 / 2 - g_1e34->f22 / 2;
    g_1e34->f02 = g_88c2 / 2 - g_1e34->f22 / 2;
    g_1e34->f0c = 0;
    g_1e34->f0e = 0;
}

/* Builds the scaled copies (DCs 35-38) of the sprite sheets 6-8 for the
 * Demon view [inferred]. */
/* @addr 18:6374 */
void far fn_18_6374(void)
{
    int sw;
    int sg;
    int dg;
    int dw;
    int i;

    sw = 0x2c << g_959e >> 1;
    sg = 4 << g_959e >> 1;
    dw = 0x2c << g_9156 >> 1;
    dg = 4 << g_9156 >> 1;
    if (!g_9156)
        dw = dw * 2 / 3;
    g_39e8[35] = CreateCompatibleDC(g_13dc);
    g_3ad0[35] = CreateCompatibleBitmap(g_13dc, dw * 18 + dg * 19, dg * 2 + dw);
    if (g_920e)
        g_3a5c[35] = SelectPalette(g_39e8[35], g_920e, 0);
    g_3974[35] = SelectObject(g_39e8[35], g_3ad0[35]);
    PatBlt(g_39e8[35], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[35], 3);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[35], (dw + dg) * i + dg, dg, dw, dw, g_39e8[7],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
    g_39e8[36] = CreateCompatibleDC(g_39e8[6]);
    g_3ad0[36] = CreateCompatibleBitmap(g_39e8[6], dw * 18 + dg * 19, dg * 2 + dw);
    g_3974[36] = SelectObject(g_39e8[36], g_3ad0[36]);
    PatBlt(g_39e8[36], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[36], 2);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[36], (dw + dg) * i + dg, dg, dw, dw, g_39e8[6],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
    dw /= 2;
    dg /= 2;
    g_39e8[37] = CreateCompatibleDC(g_13dc);
    g_3ad0[37] = CreateCompatibleBitmap(g_13dc, dw * 18 + dg * 19, dg * 2 + dw);
    if (g_920e)
        g_3a5c[37] = SelectPalette(g_13dc, g_920e, 0);
    g_3974[37] = SelectObject(g_39e8[37], g_3ad0[37]);
    PatBlt(g_39e8[37], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[37], 3);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[37], (dw + dg) * i + dg, dg, dw, dw, g_39e8[7],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
    g_39e8[38] = CreateCompatibleDC(g_39e8[8]);
    g_3ad0[38] = CreateCompatibleBitmap(g_39e8[8], dw * 18 + dg * 19, dg * 2 + dw);
    g_3974[38] = SelectObject(g_39e8[38], g_3ad0[38]);
    PatBlt(g_39e8[38], 0, 0, dw * 18 + dg * 19, dg * 2 + dw, BLACKNESS);
    SetStretchBltMode(g_39e8[38], 2);
    for (i = 0; i < 18; i++)
        fn_10_9962(1, g_39e8[38], (dw + dg) * i + dg, dg, dw, dw, g_39e8[6],
                   (sg + sw) * i + sg, sg, sw, sw, SRCCOPY);
}

/* @addr 18:3474 */
void far fn_18_3474(void)
{
    int i;
    int a;
    int b;

    g_6e24[g_70ae[g_9646].fb8].f74 = g_70ae[g_9646].f06;
    g_6e24[g_70ae[g_9646].fb8].f72 = g_70ae[g_9646].f8e;
    g_6e24[g_70ae[g_9646].fb8].f73 = g_70ae[g_9646].f8f;
    if (g_959e != 1 || !g_9156) {
        a = g_70ae[g_9646].f8e;
        b = g_70ae[g_9646].f8f;
        fn_18_2fee(g_9646);
        fn_10_5d3c(g_9646);
        if (g_70ae[g_9646].fc6 && g_96f0[g_70ae[g_9646].f30].f0a == 3) {
            g_92e4 = 1;
            if (!a)
                fn_08_2cd8(g_9646, 0);
            if (!b)
                fn_08_2cd8(g_9646, 1);
            g_92e4 = 0;
        }
    } else {
        g_1df8[20][g_9646].f22 = g_1df8[14][g_9646].f22;
        g_1df8[20][g_9646].f24 = g_1df8[14][g_9646].f24;
        g_1df8[20][g_9646].f20 =
            (int)(g_1df8[20][g_9646].f22 * g_88cc / g_88c0);
    }
    for (i = 0; i < 4; i++)
        g_6e24[g_70ae[g_9646].fb8].f38[i] = g_70ae[g_9646].f08[i];
    g_6e24[g_70ae[g_9646].fb8].f1c = g_70ae[g_9646].f00 / 40;
    g_6e24[g_70ae[g_9646].fb8].f74 = g_70ae[g_9646].f06;
    g_6e24[g_70ae[g_9646].fb8].f72 = g_70ae[g_9646].f8e;
    g_6e24[g_70ae[g_9646].fb8].f73 = g_70ae[g_9646].f8f;
    g_1df8[20][g_9646].f04 = (int)g_88cc / 2;
    g_1df8[20][g_9646].f06 = 150;
    g_1df8[20][g_9646].f00 = -1000;
    g_1df8[20][g_9646].f02 = -1000;
    g_1df8[20][g_9646].f0c = 50;
    g_1df8[20][g_9646].f0e = 0;
    g_1df8[20][g_9646].f12 = g_1df8[20][g_9646].f24;
    g_1df8[20][g_9646].f44 = g_1df8[14][g_9646].f44;
    g_1df8[20][g_9646].f42 = g_1df8[14][g_9646].f42;
    g_1df8[20][g_9646].f46 = g_1df8[14][g_9646].f46;
    g_1df8[20][g_9646].f2c = g_1df8[14][g_9646].f2c;
    g_1df8[20][g_9646].f48 = g_1df8[14][g_9646].f48;
    g_1df8[20][g_9646].f66 = g_1df8[14][g_9646].f66;
    g_1df8[20][g_9646].f62 = g_1df8[14][g_9646].f62;
    g_1df8[20][g_9646].f5e = g_1df8[14][g_9646].f5e;
    g_1df8[20][g_9646].f3c = g_1df8[14][g_9646].f3c;
    g_1df8[20][g_9646].f54 = 0;
    g_1df8[20][g_9646].f48 = g_1df8[14][g_9646].f48;
    g_1df8[20][g_9646].f28 = 8;
    for (i = 0; i < 4; i++)
        g_a187[i] = 0;
}

/* Starts the Demon sub-game [inferred]. */
/* @addr 18:08bc */
void far fn_18_08bc(int big)
{
    int i;

    if (!g_9660) {
        g_073e = 1;
        fn_10_7480(10, 1);
    }
    g_9130 = 1;
    g_959e = g_9156;
    g_9664 = g_9674 = 0;
    g_88d0 = 0;
    if (big) {
        g_9156 = 1;
        g_a197 = 1;
    } else
        g_9156 = 0;
    fn_18_0b1e();
    if (g_959e != 1 || !g_9156) {
        fn_10_1eb6(g_9646, g_70ae[g_9646].f30, 1);
        fn_10_0552(0x22, 1);
        fn_10_0552(0xc, 1);
        fn_10_0552(0xa, 1);
    }
    /* two int stores through one view: CL merges them into one immediate
     * dword store instead of sharing a zeroed eax with g_88d4 */
    ((int *)&g_a1d1)[0] = ((int *)&g_a1d1)[1] = 0;
    g_88d4 = 0;
    g_9324 = 0x14;
    g_9326 = 0xf;
    g_9328 = 0x11;
    g_934a = 0x13;
    fn_06_7266();
    g_94c4 = 1;
    fn_06_72d8(2, 2);
    g_9330 = 1;
    for (i = g_94c4 = 0; i < 45; i++)
        g_1e90[i].f00 = -1;
    for (i = 0; i < 9; i++)
        g_610e[i].f00 = -1;
    for (i = 0; i < 20; i++)
        g_58cc[i].f00 = -1;
    g_88c0 = g_6da4->f02;
    g_88c2 = g_6da4->f04;
    g_88c4.x = g_88c4.y = 0;
    g_88f0 = g_88c0 * 10 / 255;
    g_88f2 = g_88c2 * 10 / 164;
    g_88f0 = max(g_88f0 / 3 * 3, 6);
    g_88f2 = max(g_88f2 / 4 * 4, 8);
    g_88e8 = g_88c0;
    g_88ea = g_88f2 + 2;
    if (g_90f4 == 1)
        g_88ea = 0;
    g_88c2 -= g_88ea;
    g_88cc = 8000;
    fn_18_1dd0();
    fn_18_1eac();
    if (g_959e != 1 || !g_9156) {
        fn_10_5c42();
        fn_10_5202();
        fn_10_5102();
    }
    fn_18_2272();
    fn_10_58ce(0);
    fn_18_6374();
    if (!g_9660) {
        fn_10_7480(-1, 1);
        g_13a0 = 0x10;
    }
    fn_18_337c();
    fn_18_3474();
    fn_18_1784(0, 0, g_6da4->f02, g_6da4->f04 - g_88ea);
    fn_18_17f6();
    if (g_90f4 == 1)
        fn_10_744c(0x30);
    g_9660 = 1;
}

/* Decides whether the Demon appears now and picks its position
 * [inferred]. */
/* @addr 18:5cec */
int far fn_18_5cec(void)
{
    int i;
    int j;
    int tries;
    int unused;
    int b;
    int a;
    int ok;
    POINT pt;
    POINT unused2;
    POINT unused3;

    ok = 1;
    if (!flow_interactive)
        return 0;
    if (g_9320 == 6)
        return 0;
    if (g_1e68 - g_8e2c < 400)
        return 0;
    for (i = 0; i < g_9318; i++)
        if (g_1df8[8][i].f1a || g_1df8[8][i + 1].f1a)
            ok = 0;
    if (g_70ae[g_9646].fad > 9)
        ok = 0;
    if (!g_1df8[7]->f18)
        ok = 0;
    if (g_0992 + 60 > g_932a && g_91f8 - g_93ac < 15)
        ok = 0;
    if (g_92e8 || g_913e > 1)
        ok = 1;
    if (ok) {
        if (rand() % 200 < ((int)g_1e68 - 300) / 8 || g_92e8) {
            tries = 0;
            do {
                tries++;
                ok = 1;
                pt.x = rand() % (g_90ea * 2) - g_90ea / 2;
                pt.y = rand() % (g_90ec * 2) - g_90ec / 2;
                for (i = 8; i <= 14; i++) {
                    if (i == 8 || i == 14)
                    for (j = 0; j < g_9406[i]; j++) {
                        if (!g_1df8[i][j].f18
                            && (g_1df8[i][j].f54 || i == 14 && j == g_9646)
                            && (g_90ea * 4 / 5 >> g_9156)
                               > fn_08_285a(&b, &a, *(POINT far *)&g_1df8[i][j].f04,
                                            fn_08_2bbe(pt)))
                            ok = 0;
                    }
                }
                if (tries > 10)
                    ok = 2;
            } while (!ok);
            if (ok == 2)
                return 0;
            g_88c8 = fn_08_2bbe(pt);
            fn_18_0b1e();
            g_9666 = 0;
            g_9664 = 0;
            g_913a = 1;
            fn_10_754a(0x27, g_88c8.x, g_88c8.y, 4);
            g_913e = 0;
            g_93ac = g_91f8;
            g_965e = 1;
            fn_10_7480(-2, 1);
            fn_10_7480(10, 1);
            g_2384 = g_1e50 + 70000;
            g_0992 += 50;
            return 1;
        }
    }
}

/* Per-tick update of the Demon sub-game [inferred]. */
/* @addr 18:0000 */
void far fn_18_0000(void)
{
    int j;
    int i;

    g_9672 = 0;
    if (g_8d34 && g_8d34 < g_1e50) {
        g_8d34 = 0;
        g_9530 = 2;
        fn_10_744c(0x22);
    }
    if (g_13a0 != -1)
        g_13a0--;
    if (g_13a0 == 1)
        fn_10_7480(6, 1);
    if (g_9530 == 2) {
        if (g_1318 > 1 && g_90f4 == 1) {
            if (g_966a) {
                if (g_920e)
                    SelectPalette(g_966a, g_9670, 0);
                SelectObject(g_966a, g_966e);
                DeleteObject(g_966c);
                DeleteDC(g_966a);
                g_966a = 0;
            }
            if (g_9656) {
                if (g_920e)
                    SelectPalette(g_9656, g_965c, 0);
                SelectObject(g_9656, g_965a);
                DeleteObject(g_9658);
                DeleteDC(g_9656);
                g_9656 = 0;
            }
            sprite_dc_restore();
            g_90f4 = 6;
            g_952e = g_9646;
            fn_10_7480(g_913e = g_88c4.x = g_88c4.y = g_914a = 0,
                       g_9530 = g_0928 = g_93a6 = g_9e5b = 1);
            g_9156 = 0;
        } else if (g_9660)
            fn_18_03d6();
    } else if (g_88d0) {
        if (g_88d0 == 2) {
            g_88d0 = g_1e50 + 12000;
            fn_18_6046();
        } else if (g_88d0 < g_1e50) {
            g_88d0 = 0;
            fn_18_621e();
        }
    } else {
        if (!g_9660) {
            if (g_90f4 == 1)
                fn_18_08bc(1);
            else
                fn_18_08bc(0);
        }
        if (g_6da4->f1c) {
            fn_18_17f6();
            g_6da4->f1c = 0;
        }
        fn_18_1cbe(0);
        fn_11_1d7c();
        fn_18_034c();
        if (g_9530 == 1 && music_pause_state == -2)
            fn_10_7480(-3, 1);
        if (g_8e62)
            fn_18_0d4e(g_8e62, g_8e64, g_1d38);
        if (!g_1df8[g_9324][g_9646].f18) {
            if (g_05a4 <= g_1e50) {
                g_05a4 = g_1e50 + 50;
                fn_11_592a();
            }
            if (g_05b8 < g_1e50) {
                g_05b8 = g_1e50 + 10000;
                fn_07_2128();
            }
        }
        if (!g_1df8[g_9324][g_9646].f18)
            fn_11_4db0();
        for (i = g_9136 = 0; i < 5; i++)
            for (j = 0; j < g_0598 + g_0594; j++)
                g_9136 = fn_08_3aec(j, i);
        if (g_9430 > 0)
            for (j = 0; j <= g_9434; j++)
                fn_08_3fbe(j);
        fn_07_375a();
        g_1c9e++;
        if (g_1c9e >= 8 && g_90f4 == 6) {
            g_1c9e = 0;
            if (g_70ae[g_9646].f42)
                g_70ae[g_9646].f42--;
        }
        g_9146 = 0;
        fn_08_4e14();
        if (g_1016)
            fn_11_a9ea(1);
        fn_18_0d94();
        fn_18_37d8();
        fn_18_403e();
        fn_07_40c4();
        fn_07_3bae();
        fn_18_50ac();
        if (g_9456 > 0)
            fn_07_5e04();
        fn_13_447a();
    }
}

extern int g_913c;
extern DWORD g_1e84;
extern int g_9662;
void far fn_16_631c(void);
void far fn_11_1bcc(void);
void far fn_11_0894(void);
void far fn_11_3396(void);
void far fn_11_0afe(void);

/* Ends the Demon sub-game and restores the normal view [inferred]. */
/* @addr 18:03d6 */
void far fn_18_03d6(void)
{
    int i;
    int j;
    int changed;
    int scaled;
    int b0;
    int b1;

    scaled = changed = 0;
    if (g_9130) {
        if (g_9156 == 1)
            scaled = 1;
        g_9130 = 0;
        if (g_9156 == 1)
            fn_16_631c();
        PatBlt(g_13dc, 0, 0, g_88c0, g_88c2, BLACKNESS);
        g_9326 = 0;
        if (g_92e8)
            g_9326 = 1;
        g_9324 = 14;
        g_9328 = 5;
        g_934a = 3;
        if (g_9156 == 1) {
            g_913c = 1;
            g_9666 = 0;
            g_9664 = 0;
            fn_10_754a(0x27, g_88c8.x, g_88c8.y, 4);
            g_1df8[14][g_9646].f18 = 1;
            g_073e = 0;
            fn_10_7480(-3, 1);
        } else
            fn_18_0ba0();
        for (j = 0; j < 4; j++)
            g_70ae[g_9646].f08[j] = g_6e24[g_70ae[g_9646].fb8].f38[j];
        g_70ae[g_9646].f00 = 40 * g_6e24[g_70ae[g_9646].fb8].f1c;
        g_70ae[g_9646].f06 = g_6e24[g_70ae[g_9646].fb8].f74;
        if (g_6e24[g_70ae[g_9646].fb8].f72 != g_70ae[g_9646].f8e ||
            g_6e24[g_70ae[g_9646].fb8].f73 != g_70ae[g_9646].f8f)
            changed = 1;
        if (!g_70ae[g_9646].fce)
            changed = 1;
        g_70ae[g_9646].f8e = g_6e24[g_70ae[g_9646].fb8].f72;
        g_70ae[g_9646].f8f = g_6e24[g_70ae[g_9646].fb8].f73;
        b0 = g_70ae[g_9646].f8e;
        b1 = g_70ae[g_9646].f8f;
        g_70ae[g_9646].fce = 1;
        g_1e84 = 0;
        g_2408 = 0;
        g_238c = 0;
        fn_06_7266();
        g_94c4 = 1;
        fn_06_72d8(5, 5);
        g_94c4 = 0;
        g_92e4 = g_9330 = 1;
        if (g_966a) {
            if (g_920e)
                SelectPalette(g_966a, g_9670, 0);
            SelectObject(g_966a, g_966e);
            DeleteObject(g_966c);
            DeleteDC(g_966a);
            g_966a = 0;
        }
        if (g_9656) {
            if (g_920e)
                SelectPalette(g_9656, g_965c, 0);
            SelectObject(g_9656, g_965a);
            DeleteObject(g_9658);
            DeleteDC(g_9656);
            g_9656 = 0;
        }
        if (g_9156 == 1)
            sprite_dc_restore();
        if (g_959e != 1 || !g_9156) {
            if (g_90f4 == 1)
                fn_18_07b2();
            else
                g_9662 = 1;
        } else if (changed) {
            fn_10_1eb6(g_9646, g_70ae[g_9646].f30, 1);
            fn_16_3784(g_9646, 2);
            if (g_70ae[g_9646].fc6 && g_96f0[g_70ae[g_9646].f30].f0a == 3) {
                if (!b0)
                    fn_08_2cd8(g_9646, 0);
                if (!b1)
                    fn_08_2cd8(g_9646, 1);
            }
        }
        fn_10_0552(0x27, 1);
        fn_10_0552(0x23, 1);
        fn_10_0552(0x24, 1);
        fn_10_0552(0x25, 1);
        fn_10_0552(0x26, 1);
        if (g_9668) {
            DeleteObject(g_9668);
            g_9668 = 0;
        }
        fn_18_1e46();
        g_92e4 = 0;
        g_9156 = g_959e;
        if (scaled) {
            fn_13_65f2(2);
            fn_11_1bcc();
            fn_11_0894();
            fn_11_3396();
            fn_11_0afe();
        }
        for (i = 0; i < 45; i++)
            g_1e90[i].f00 = -1;
        for (i = 0; i < 9; i++)
            g_610e[i].f00 = -1;
        for (i = 0; i < 20; i++)
            g_58cc[i].f00 = -1;
        g_9510 = 100;
        g_9660 = 0;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_18_0d94(void)
{
}

extern int g_1ca6;
extern int g_1ca8;
extern POINT g_1caa;               /* g_1caa, g_1cac */
extern int g_9334;
extern int g_943a;
extern int g_943c;
int far pascal steer_toward_direction(int y2, int x2, int y1, int x1, int cur,
                                      int mode, int obj, int a, int b, int c);
void far pascal fn_08_1b54(WORD r, int n);
void far pascal fn_12_2db6(int type, int idx, int c, int d, int kind);
int far pascal fn_08_50aa(WORD r);
int far pascal fn_08_546c(WORD ref, int far *pvx, int far *pvy, int m1, int m0);
void far fn_08_5df2(int a, int b, int c, int d, int e);
void far fn_18_66e0(void);
void far fn_18_591c(void);
void far repulsive_force_weapon(int type, int idx);
void far attractive_force_weapon(int type, int idx);
void far fn_11_9daa(int a, int b);

/* Per-frame update of the Demon (object 15:0): turns toward the player and
 * shoots, grows into view while g_1318 counts down, collides, and spins
 * the four gate gauges [inferred]. */
/* @addr 18:37d8 */
void far fn_18_37d8(void)
{
    int obj;                    /* assigned, never read */
    int i;
    int old;
    WORD r;
    int mode;
    int dir;
    int target;
    int ty;
    POINT s;                    /* s, t, rc as structs: CL then recomputes */
    POINT t;                    /* f22 / 2 like the game; t.y unused */
    RECT rc;                    /* the Demon's previous screen rect */

    if (g_90f4 == 6 && g_1318 > 1)
        return;
    g_1ca6++;
    g_9676 = g_9676 - 1 < 0 ? 0 : g_9676 - 1;
    if (g_90f4 == 1) {
        if (g_1ca6 % (12 - g_a198) == 0)
            mode = 1;
        else
            mode = 0;
        if (g_1318 >= 30)
            mode = 2;
    } else {
        if (g_1ca6 % max(18 - g_a198, 5) == 0)
            mode = 1;
        else
            mode = 0;
    }
    g_1e34->f0e = 0;
    g_1e34->f0c = g_1e34->f0e;
    fn_08_1b54(0xf00, 1);
    if (mode && g_70ae[g_9646].fce && !g_9676) {
        target = g_9324;
        obj = g_9646;
        if (mode == 1) {
            dir = g_1e34->f28;
            s.x = g_1e34->f22 / 2 + g_1e34->f04;
            s.y = g_1e34->f22 / 2 + g_1e34->f06;
            t.x = g_1df8[g_9324][g_9646].f22 / 2 + g_1df8[g_9324][g_9646].f04;
            g_1e34->f28 = steer_toward_direction(s.y, s.x,
                    ty = g_1df8[g_9324][g_9646].f06 + g_1df8[g_9324][g_9646].f22 / 2, t.x,
                    g_1e34->f28, 5, -1, g_9324, g_9646, 0);
            if (g_70ae[g_9646].f66 < g_1e50 && g_1318 < 2 && g_1e34->f28 == dir &&
                target == g_9324) {
                if ((g_90f4 == 1 && rand() % 9 < g_a198 + 3) ||
                    (g_90f4 == 6 && rand() % 27 < g_a198 + 7))
                    fn_12_2db6(15, 0, (g_1e34->f28 + 8) % 16, (g_a198 + 9) * 2, 5);
                else if (g_90f4 == 1) {
                    if (g_70ae[g_9646].f08[0] < 50) {
                        if (rand() % 6 < g_a198)
                            fn_18_66e0();
                    } else if (rand() % 13 < g_a198)
                        fn_18_66e0();
                } else {
                    if (g_70ae[g_9646].f08[0] < 50) {
                        if (rand() % 10 < g_a198 - 1)
                            fn_18_66e0();
                    } else if (rand() % 18 < g_a198 - 1)
                        fn_18_66e0();
                }
            }
        } else
            g_1e34->f28 = (g_1e34->f28 + 1) % 16;
        g_1e34->f10 = (g_1e34->f22 + g_1e34->f24) * g_1e34->f28 + g_1e34->f24;
        g_1e34->f12 = g_1e34->f24;
        if (mode == 1)
            fn_18_1934(0xf00, 1, g_3a36);
        else {
            if (g_1318 == 30)
                g_1ca8 = 0;
            rc.right = g_1e34->f22 - g_1e34->f22 / 2 + g_1ca8 / 2 + g_88c0 / 2 - g_1ca8 + g_88c4.x;
            rc.top = g_1ca8 / 2 - g_1e34->f22 / 2 + g_88c2 / 2 + g_88c4.y;
            rc.bottom = g_1e34->f22 - g_1ca8 + rc.top;
            g_88c0 = g_6da4->f02 + (g_8d14 - (long)g_6da4->f02) * ((long)g_1318 - 30) / 59;
            g_88c2 = g_6da4->f04 + (g_8d16 - (long)g_6da4->f04) * ((long)g_1318 - 30) / 59;
            g_88c4.x = (int)(g_8d18 * ((long)g_1318 - 30) / 59);
            g_88c4.y = (int)(g_8d1a * ((long)g_1318 - 30) / 59);
            SetStretchBltMode(g_13dc, 3);
            g_1ca8 = g_1e34->f22 * (g_1318 - 30) / 59;
            g_1caa.x = g_1ca8 / 2 - g_1e34->f22 / 2 + g_88c0 / 2 + g_88c4.x;
            g_1caa.y = g_1ca8 / 2 - g_1e34->f22 / 2 + g_88c2 / 2 + g_88c4.y;
            *(POINT far *)&g_1e34->f00 = g_1caa;
            StretchBlt(g_13dc, g_1caa.x, g_1caa.y, g_1e34->f22 - g_1ca8, g_1e34->f22 - g_1ca8,
                       g_3a36, g_1e34->f10, g_1e34->f12, g_1e34->f22, g_1e34->f22, SRCCOPY);
            rc.left = g_1e34->f22 - g_1ca8 + g_1caa.x;
            PatBlt(g_13dc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, BLACKNESS);
            PatBlt(g_13dc, g_1caa.x, rc.top, g_1e34->f22 - g_1ca8, g_1caa.y - rc.top, BLACKNESS);
            PatBlt(g_13dc, g_1caa.x, g_1e34->f22 - g_1ca8 + g_1caa.y, g_1e34->f22 - g_1ca8,
                   rc.bottom - (g_1e34->f22 - g_1ca8 + g_1caa.y), BLACKNESS);
        }
    }
    if (g_1318 > 5)
        return;
    g_943a = 15;
    g_943c = 0;
    r = fn_08_50aa(0xf00);
    if (HIBYTE(r) == g_9324 && g_1318 == 1 && g_90f4 != 6)
        fn_18_5f74();
    if (r != 0xffff)
        fn_08_5df2(15, 0, HIBYTE(r), LOBYTE(r),
                   fn_08_546c(r, &g_1e34->f0c, &g_1e34->f0e, g_1e34->f22 + 1, g_1e34->f44));
    if (g_1318 > 1)
        return;
    for (i = 0; i < 4; i++) {
        old = g_a16a[i] / 40;
        g_a16a[i] = (((unsigned char)g_a17b[i] >> 1) + g_a16a[i]) % 360;
        if (g_a16a[i] / 40 == old || mode) {
            BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                   7 << g_9156 * 2, 7 << g_9156 * 2, g_966a, g_8914[i].x, g_8914[i].y, SRCCOPY);
            if (g_a18f[i])
                BitBlt(g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678,
                       7 << g_9156 * 2, 7 << g_9156 * 2, g_9656,
                       g_a16a[i] / 40 * 7 << g_9156 * 2, 0, SRCPAINT);
            BitBlt(g_13dc, g_8904[i].x, g_8904[i].y, 7 << g_9156 * 2, 7 << g_9156 * 2,
                   g_966a, (-7 << g_9156 * 2) + g_9678, (-7 << g_9156 * 2) + g_9678, SRCCOPY);
        }
    }
    if (g_90f4 == 1)
        repulsive_force_weapon(15, 0);
    fn_18_591c();
    if (g_90f4 == 1) {
        if (!g_9676 && rand() % 26000 < (g_a198 + 2) * 2 + g_9334 / 2)
            fn_11_9daa(15, 0);
    } else {
        if (!g_9676 && rand() % 4000 < g_a198 - 2)
            fn_11_9daa(15, 0);
    }
    if (g_1ca6 % 7 == 0)
        attractive_force_weapon(15, 0);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_18_403e(void)
{
}

extern int g_9436;
extern int g_9438;
extern int g_943a;
extern int g_943c;
extern int g_944a;
extern int g_944c;
extern int g_944e;
extern int g_9450;
extern int object_sizes[2];         /* DS:9442 */
extern int object_masses[2];        /* DS:9446 */
extern int g_9448;                  /* object_masses[1] */
extern POINT g_52dc;
extern POINT g_52e0;
extern POINT g_52e4;
extern POINT g_52e8;
extern RECT g_8860[];
extern POINT g_8ce4[];
extern int g_8d1c[];
int far pascal fn_10_7dd4(int far *a, int far *b, int far *c, int far *d,
                          int far *e, int far *f, int far *g, int far *h,
                          int i, int j, int k, int l, int far *m, int far *n);
void far pascal fn_08_6a44(int a);

/* Checks an object against the Demon arena's wall rectangles and bounces
 * it [inferred]. unused8 stands for a temporary the original drops. */
/* near-match 71%: 18:2c1e (CL stores the unused8 temporary; the game keeps
 * g_88c0 - g_9678 in ax only, and its frame is 2 bytes larger, the extra
 * slot below the POINT return temporary; block-scope temps, casts and
 * extern order tried) */
int far fn_18_2c1e(int type, int idx)
{
    int i;
    int j;
    int unused8;
    int n;
    int k;
    POINT pos;
    POINT unused14;
    RECT rc1;
    RECT rc;
    int hit;

    if (type == 30 && g_70ae[g_9646].f06 == 2)
        n = 2;
    else
        n = 1;
    for (k = 0; k < n; k++) {
        if (type == 30) {
            pos.x = g_6098[idx].x[k][0];
            pos.y = g_6098[idx].y[k][0];
            object_sizes[1] = 4;
        } else {
            pos = *(POINT far *)&g_1df8[type][idx].f00;
            object_sizes[1] = g_1df8[type][idx].f22 + 2;
        }
        if ((pos.x <= g_9678 || pos.x >= (unused8 = g_88c0 - g_9678) - object_sizes[1]) &&
            (pos.y >= g_88c2 - g_9678 - object_sizes[1] || pos.y <= g_9678)) {
        SetRect(&rc, pos.x, pos.y, pos.x + object_sizes[1], pos.y + object_sizes[1]);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 3; j++) {
                if (!IntersectRect(&rc1, &g_8860[i * 3 + j], &rc))
                    continue;
                if (type == 30) {
                    object_masses[1] = 14 - g_6098[idx].f76 * 14 / g_6098[idx].f74;
                    if (g_6098[idx].f76 < 20)
                        object_masses[1] = 18;
                    object_masses[1] *= 2;
                    object_masses[1] = g_96d6[g_70ae[g_6098[idx].f7c].f30].f2e * object_masses[1] / 250;
                    if (g_90f4 == 1)
                        /* g_9448 = object_masses[1]: a second name stops CL
                         * merging this product with the else arm's [layout] */
                        object_masses[1] = (24 - 5 * g_a198) * g_9448 * 3 / 20;
                    else
                        object_masses[1] = (9 - g_a198) * object_masses[1] * 3 / 20;
                    k = n;
                } else
                    object_masses[1] = g_1df8[type][idx].f44;
                g_944a = 0x1f;
                g_944e = i;
                g_943a = g_944c = type;
                g_943c = g_9450 = idx;
                if (type == 30) {
                    g_52dc.x = g_6098[idx].f70 * 5;
                    g_52dc.y = g_6098[idx].f72 * 5;
                } else
                    g_52dc = *(POINT far *)&g_1df8[type][idx].f0c;
                *(long *)&g_52e0 = 0;
                g_52e8 = pos;
                g_52e4 = g_8ce4[i * 3 + j];
                object_sizes[0] = g_8d1c[i * 3 + j] + 2;
                if (type == 30)
                    object_masses[0] = 800;
                else
                    object_masses[0] = 20000;
                hit = fn_10_7dd4(&g_52dc.x, &g_52dc.y, &g_52e0.x, &g_52e0.y,
                                 &g_52e8.x, &g_52e8.y, &g_52e4.x, &g_52e4.y,
                                 object_sizes[1] + 1, object_sizes[0],
                                 object_masses[1], object_masses[0],
                                 &g_9436, &g_9438);
                g_9438 = g_9438 < 3 ? 3 : g_9438;
                if (hit) {
                    if (type == 30) {
                        pos = fn_08_2bbe(g_52e8);
                        g_6098[idx].x1[0][0] = pos.x;
                        g_6098[idx].y1[0][0] = pos.y;
                        g_6098[idx].f70 = g_52dc.x / 5;
                        g_6098[idx].f72 = g_52dc.y / 5;
                        if (j == 2 && g_a18f[i] && !g_1e40->f1a) {
                            fn_10_754a(0x24, 0x1e, idx, 2);
                            if (g_90f4 == 6)
                                g_a1cd++;
                            ((unsigned char *)g_a17b)[i] += (char)g_9438;
                            if (((unsigned char *)g_a17b)[i] < 200 &&
                                ((unsigned char *)g_a17b)[i] > 70) {
                                g_a18f[i] = 0;
                                if (g_90f4 == 6)
                                    g_a193[i] = 0;
                                fn_18_4faa(i);
                                ((unsigned char *)g_a17b)[i] = 0xdc;
                            }
                            return 2;
                        }
                        fn_10_754a(0x11, 0x1e, idx, 2);
                    } else {
                        *(POINT far *)&g_1df8[g_944c][g_9450].f04 = fn_08_2bbe(g_52e8);
                        fn_08_6a44(1);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

extern signed char g_9150;
int far fn_08_35d0(long a, long b);

/* Pulls every other object toward object (type, idx) [inferred]. */
/* @addr 18:59ec */
void far attractive_force_weapon(int type, int idx)
{
    POINT c;
    POINT d;
    POINT p;
    int dist;
    int t;
    int i;
    int force;

    if (g_1318 <= 1 && g_1df8[type][idx].f1a) {
    if (g_9130) {
        c.x = g_1df8[type][idx].f20 / 2 + g_1df8[type][idx].f04;
        c.y = g_1df8[type][idx].f20 / 2 + g_1df8[type][idx].f06;
    } else {
        if (!g_70ae[idx].f00)
            return;
        if (type == 14 && !g_1df8[14][idx].f54)
            g_70ae[idx].f00--;
        c.x = g_1df8[type][idx].f22 / 2 + g_1df8[type][idx].f00;
        c.y = g_1df8[type][idx].f22 / 2 + g_1df8[type][idx].f02;
    }
    for (t = g_9326; t <= g_9324; t++) {
        if (t == 5)
            continue;
        for (i = 0; i < g_9406[t]; i++) {
            if ((!g_1df8[t][i].f18 && (g_92e8 || g_1df8[t][i].f1a) &&
                 !g_1df8[t][i].f54 && (t != type || i != idx)) || t == 18) {
                if (g_9130) {
                    d.x = g_1df8[t][i].f20 / 2 + g_1df8[t][i].f04 - c.x;
                    d.y = g_1df8[t][i].f20 / 2 + g_1df8[t][i].f06 - c.y;
                } else {
                    p.x = g_1df8[t][i].f20 / 2 + g_1df8[t][i].f04;
                    p.y = g_1df8[t][i].f20 / 2 + g_1df8[t][i].f06;
                    p = fn_08_29ea(p);
                    d.x = p.x - c.x << g_9150;
                    d.y = p.y - c.y << g_9150;
                }
                dist = fn_08_35d0(d.x, d.y);
                if (g_9130) {
                    force = 13;
                    if (t == 19)
                        force = 7;
                } else {
                    force = 11L * g_1df8[type][idx].f44 / max(g_1df8[t][i].f44, 50);
                    force = force > 14 ? 14 : force;
                }
                if (g_92e8 && !g_1df8[t][i].f1a)
                    force *= 2;
                if (g_9130 || dist < 7000 || g_92e8) {
                    g_1df8[t][i].f0c -= (long)d.x * force / dist;
                    g_1df8[t][i].f0e -= (long)d.y * force / dist;
                }
            }
        }
    }
    }
}

typedef struct {                /* 0x1c-byte records at DS:66e4 */
    int f00;
    char p02[0x04 - 0x02];
    int f04;
    int f06;
    int f08;
    char p0a[0x1c - 0x0a];
} REC_1C;
typedef struct {                /* 0x50-byte records at DS:2f4c */
    char p00[0x26];
    int f26;
    char p28[0x2c - 0x28];
    int f2c;
    char p2e[0x50 - 0x2e];
} REC_50;
typedef struct {                /* 0x14-byte records at DS:5a50 */
    int f00;
    int f02;
    char p04[0x14 - 0x04];
} REC_14B;
extern REC_1C g_66e4[];
extern REC_50 g_2f4c[];
extern REC_14B g_5a50[];
extern int g_9410;
extern int g_9412;

/* Pushes every nearby object away from a point ahead of object
 * (type, idx) [inferred]. */
/* @addr 18:551a */
void far repulsive_force_weapon(int type, int idx)
{
    int dir;
    int dist;
    int force;
    int a;
    int b;
    int i;
    int r;
    int k;
    POINT tp;
    POINT src;
    POINT pp;

    if (type == 14 && !g_1df8[14][idx].f54) {
        if (!g_70ae[idx].f00)
            return;
        if (g_1e68 % 14 == 0)
            g_70ae[idx].f00--;
    }
    dir = g_1df8[type][idx].f28;
    if (type == 15)
        dir = (dir + 8) & 0xf;
    if (g_9130)
        r = g_88cc * (15 * g_a198 + 85) / g_88c0;
    else
        r = 800;
    src.x = (g_1050[dir].x * r >> 4) + (g_1df8[type][idx].f20 >> 1) + g_1df8[type][idx].f04;
    src.y = (g_1050[dir].y * r >> 4) + (g_1df8[type][idx].f20 >> 1) + g_1df8[type][idx].f06;
    pp = fn_08_29ea(src);
    for (i = 0; i < 5; i++) {
        if (g_6098[i].f76 >= 0 && g_6098[i].f74 >= g_6098[i].f76 &&
            (g_6098[i].f7a != type || g_6098[i].f7c != idx)) {
            tp.x = g_6098[i].x1[0][0];
            tp.y = g_6098[i].y1[0][0];
            dist = fn_08_285a(&a, &b, src, tp);
            if (!dist)
                dist = 1;
            if (dist < 90) {
                force = dist * 15 / -90 + 20;
                g_6098[i].f70 += (long)a * force / dist;
                g_6098[i].f72 += (long)b * force / dist;
                g_6098[i].f82 = 1;
            }
        }
    }
    if (!g_9130)
        for (i = 0; i < g_9412; i++) {
            k = g_66e4[i].f00;
            if ((g_2f4c[k].f26 > g_66e4[i].f08 || g_2f4c[k].f2c == 6) && k != -1 &&
                !g_1df8[6][i].f18 &&
                (g_66e4[i].f04 != type || g_66e4[i].f06 != idx)) {
                tp.x = g_1df8[6][i].f04;
                tp.y = g_1df8[6][i].f06;
                dist = fn_08_285a(&a, &b, src, tp);
                if (!dist)
                    dist = 1;
                if (dist < 90) {
                    force = dist * 15 / -90 + 20;
                    g_1df8[6][i].f0c += (long)a * force / dist;
                    g_1df8[6][i].f0e += (long)b * force / dist;
                }
            }
        }
    if (!g_9130)
        for (i = 0; i < g_9410; i++) {
            if (!g_1df8[5][i].f18 &&
                (g_5a50[i].f00 != type || g_5a50[i].f02 != idx)) {
                tp.x = g_1df8[5][i].f04;
                tp.y = g_1df8[5][i].f06;
                dist = fn_08_285a(&a, &b, src, tp);
                if (!dist)
                    dist = 1;
                if (dist < 90) {
                    force = dist * 15 / -90 + 20;
                    g_1df8[5][i].f0c += (long)a * force / dist;
                    g_1df8[5][i].f0e += (long)b * force / dist;
                }
            }
        }
}

void far fn_11_9daa(int a, int b);

/* A wall gun n aims at the player ship and fires when lined up
 * [inferred]. */
/* near-match 26%: 18:49d8 (the game keeps the second q.x/q.y in si/cx and
 * reuses them for d; here they are reloaded from q; layout otherwise the
 * same) */
void far fn_18_49d8(int n, int m)
{
    int i;
    int dist;
    int speed;
    int unused_a;
    POINT pos;
    POINT d;
    POINT v;
    POINT c;
    POINT q;
    RECT rc;

    if (g_90f4 == 6 && g_a198 < 6)
        return;
    if (g_a17f[n] < 0) {
        pos.x = g_6098[n].x1[0][0];
        pos.y = g_6098[n].y1[0][0];
        v.x = g_6098[n].f70;
        v.y = g_6098[n].f72;
        for (i = 0; i < 4; i++) {
            c.x = (g_8870[i].rc.right - g_8870[i].rc.left) / 2 + g_8870[i].rc.left;
            c.y = (g_8870[i].rc.bottom - g_8870[i].rc.top) / 2 + g_8870[i].rc.top;
            c = fn_08_2bbe(c);
            dist = fn_08_35d0(d.x = c.x - pos.x, d.y = c.y - pos.y);
            speed = fn_08_35d0(v.x, v.y);
            if (!speed)
                speed = 1;
            q.x = (long)dist * v.x / speed + pos.x;
            q.y = (long)dist * v.y / speed + pos.y;
            q = fn_08_29ea(q);
            SetRect(&rc, g_8870[i].rc.left - 7, g_8870[i].rc.top - 7,
                    g_8870[i].rc.right + 7, g_8870[i].rc.bottom + 7);
            if (PtInRect(&rc, q)) {
            POINT s;
            int steps;
            int dir1;
            int dir2;

            dir1 = (g_1e34->f28 + 8) % 16;
            s.x = g_1e34->f22 / 2 + g_1e34->f04;
            s.y = g_1e34->f22 / 2 + g_1e34->f06;
            dir2 = fn_08_19b0(c.x - s.x, c.y - s.y);
            if (g_9676)
                return;
            if (fn_09_88ba(dir1 - dir2) < 3) {
                if (g_90f4 == 1)
                    dist = (8 - g_a198) * dist / 10;
                else
                    dist = (14 - g_a198) * dist / 10;
                q.x = (long)dist * v.x / speed + pos.x;
                q.y = (long)dist * v.y / speed + pos.y;
                s.x = g_1e34->f20 / 2 + g_1e34->f04;
                s.y = g_1e34->f20 / 2 + g_1e34->f06;
                steps = dist / speed;
                if (steps >= m - 1)
                    return;
                dist = fn_08_35d0(d.x = q.x - s.x, d.y = q.y - s.y);
                if (!dist)
                    dist = 1;
                speed = dist / steps;
                g_a17f[n] = 0;
                g_a199[n].x = s.x;
                g_a199[n].y = s.y;
                *(POINT *)&g_a1c9 = fn_08_29ea(s);
                MoveTo(g_13dc, g_a1c9, g_a1cb);
                g_a1a9[n].x = (long)d.x * speed / dist;
                g_a1a9[n].y = (long)d.y * speed / dist;
                g_a187[n] = steps;
                return;
            }
            if ((g_90f4 == 1 && (g_a198 + 1) * 2 > rand() % 27) ||
                (g_90f4 == 6 && g_a198 - 1 > rand() % 12))
                fn_11_9daa(15, 0);
            return;
            }
        }
        g_a187[n] = 0;
    }
}

void far fn_07_2080(int t, int unused);

/* Spawns one Demon-arena missile of type g_934a aimed at the player ship
 * [inferred]. Its size f20 is scaled from record 0, not the new one (as in
 * the original). */
/* @addr 18:66e0 */
void far fn_18_66e0(void)
{
    POINT p;
    POINT d;
    int i;
    int found;
    POINT unused;
    int speed;
    int dist;

    if (g_9406[g_934a] < 1) {
        for (i = 0; i < g_92ec[g_934a]; i++)
            g_1df8[g_934a][i].f18 = 1;
        i = -1;
        found = 0;
        do {
            i++;
            if (i < 4) {
                if (g_92ec[g_934a] <= i) {
                    g_92ec[g_934a] = i + 1;
                    GlobalUnlock(g_9100[g_934a]);
                    g_9100[g_934a] = GlobalReAlloc(g_9100[g_934a],
                        (long)(g_92ec[g_934a] < 1 ? 1 : g_92ec[g_934a]) * 0x70,
                        GMEM_MOVEABLE | GMEM_ZEROINIT);
                    g_1df8[g_934a] = (REC_70 far *)GlobalLock(g_9100[g_934a]);
                    g_1df8[g_934a][i].f48 = 9;
                    g_1df8[g_934a][i].f42 = 8;
                    g_1df8[g_934a][i].f46 = 4;
                    g_1df8[g_934a][i].f4c = 0xc0c0c0;
                    g_1df8[g_934a][i].f5e = fn_07_5090;
                    g_1df8[g_934a][i].f53 = 0;
                    g_1df8[g_934a][i].f54 = 0;
                    g_1df8[g_934a][i].f32 = -1;
                    g_1df8[g_934a][i].f2e = 0;
                    g_1df8[g_934a][i].f18 = 1;
                    g_9406[g_934a] = i + 1;
                }
                if (g_1df8[g_934a][i].f18) {
                    if (g_70ae[g_9646].f08[0] < 50)
                        g_1df8[g_934a][i].f44 = 1400;
                    else
                        g_1df8[g_934a][i].f44 = 466;
                    g_1df8[g_934a][i].f22 = (44 << g_9156) >> 1;
                    if (!g_9156)
                        g_1df8[g_934a][i].f22 = g_1df8[g_934a][i].f22 * 2 / 3;
                    g_1df8[g_934a][i].f20 = (int)(g_1df8[g_934a]->f22 * g_88cc / g_88c0);
                    g_1df8[g_934a][i].f24 = (4 << g_9156) >> 1;
                    g_1df8[g_934a][i].f12 = g_1df8[g_934a][i].f24;
                    g_1df8[g_934a][i].f62 = fn_11_3914;
                    g_1df8[g_934a][i].f2c = 40;
                    g_1df8[g_934a][i].f1e = 0;
                    g_1df8[g_934a][i].f2f = 0;
                    g_1df8[g_934a][i].f18 = 0;
                    p.x = g_1050[(g_1e34->f28 + 8) % 16].x * (g_1e34->f22 / 2 + ((44 << g_9156) >> 2)) / 16
                        + g_1e34->f22 / 2 - ((44 << g_9156) >> 2) + g_1e34->f00;
                    p.y = g_1050[(g_1e34->f28 + 8) % 16].y * (g_1e34->f22 / 2 + ((44 << g_9156) >> 2)) / 16
                        + g_1e34->f22 / 2 - ((44 << g_9156) >> 2) + g_1e34->f02;
                    *(POINT far *)&g_1df8[g_934a][i].f04 = p = fn_08_2bbe(p);
                    g_1df8[g_934a][i].f00 = -1000;
                    g_1df8[g_934a][i].f08 = g_1df8[g_934a][i].f00;
                    g_1df8[g_934a][i].f02 = -1000;
                    g_1df8[g_934a][i].f0a = g_1df8[g_934a][i].f02;
                    d.x = (rand() % (50 - g_a198 * 4) + g_a198 * 3) * g_1df8[g_9324][g_9646].f0c
                        + g_1df8[g_9324][g_9646].f22 / 2 + g_1df8[g_9324][g_9646].f04
                        - g_1e34->f22 / 2 - p.x;
                    d.y = (rand() % (50 - g_a198 * 4) + g_a198 * 3) * g_1df8[g_9324][g_9646].f0e
                        + g_1df8[g_9324][g_9646].f22 / 2 + g_1df8[g_9324][g_9646].f06
                        - g_1e34->f22 / 2 - p.y;
                    dist = fn_08_35d0(d.x, d.y);
                    if (g_90f4 == 1)
                        speed = (g_a198 + 10) * 7;
                    else
                        speed = (g_a198 + 15) * 4;
                    g_1df8[g_934a][i].f0c = (long)d.x * speed / dist;
                    g_1df8[g_934a][i].f0e = (long)d.y * speed / dist;
                    g_9406[g_934a] = i + 1;
                    fn_10_754a(0x1c, g_934a, i, found = 1);
                }
            }
        } while (!found && i < 126);
    } else
        fn_07_2080(g_934a, 0);
}
