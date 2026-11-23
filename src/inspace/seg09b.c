/* INSPACE.EXE segment 9 (selector 1040), 9:0b2a-5be0: one source file
 * (functions near-call each other) [inferred]. */
#include <stdlib.h>
#include "inspace.h"

/* Records reached through far pointers or DGROUP arrays; only the fields
 * this file uses are named (offset in the name). */
typedef struct {                /* 0x70 bytes, far array at DS:1df8 / 1e18 */
    POINT f00;                  /* +00 */
    POINT f04;                  /* +04 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x18 - 0x10];
    int f18;
    char p1a[0x1e - 0x1a];
    int f1e;
    char p20[0x26 - 0x20];
    int f26;                    /* +26 */
    char p28[0x2f - 0x28];
    char f2f;
    char p30[0x44 - 0x30];
    int f44;                    /* +44 */
    char p46[0x50 - 0x46];
    char f50;                   /* +50 */
    char f51;
    char f52;                   /* +52 */
    char f53;                   /* +53 */
    char p54[0x66 - 0x54];
    void (far *f66)(int type, int idx);  /* +66 */
    char p6a[0x70 - 0x6a];
} REC_70;

#pragma pack(1)
typedef struct {                /* 0x297 bytes, far array at DS:69f4 */
    char p000[0xa0];
    char fa0;                   /* +a0 */
    char fa1;                   /* +a1 */
    char pa2;
    char fa3;                   /* +a3 */
    char pa4[0xae - 0xa4];
    int fae[40];                /* +ae */
    int ffe[40];                /* +fe */
    int f14e;                   /* +14e */
    int f150;                   /* +150 */
    char p152[0x1c0 - 0x152];
    char f1c0[8];               /* +1c0 */
    char f1c8[8];               /* +1c8 */
    char f1d0;                  /* +1d0 */
    char f1d1;                  /* +1d1 */
    int f1d2[8];                /* +1d2 */
    unsigned char f1e2[0x297 - 0x1e2];
} REC_297;

typedef struct {                /* 0x7c bytes, far array at DS:6e24 */
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    char p08[0x1c - 0x08];
    char f1c;                   /* +1c */
    char f1d;                   /* +1d */
    char f1e[10];               /* +1e */
    char f28[16];               /* +28 */
    char f38[4];                /* +38 */
    char f3c[0x28];             /* +3c, indexed by record [inferred] */
    char f64;                   /* +64 */
    char f65[13];               /* +65: name [inferred] */
    char f72;                   /* +72 */
    char f73;                   /* +73 */
    char f74;                   /* +74 */
    char f75;                   /* +75 */
    char f76;                   /* +76 */
    char p77[0x7c - 0x77];
} REC_7C;

typedef struct {                /* 0x41 bytes, far array at DS:6e20 */
    char p00[5];
    char f05;                   /* +05 */
    char p06[0x41 - 0x06];
} REC_41;
#pragma pack()

typedef struct {                /* 0x15a bytes, DGROUP array at DS:7090 */
    char p000[0x0a];
    char f0a;                   /* +0a */
    char p00b[0x1e - 0x0b];
    int f1e;                    /* +1e */
    char p020[0x24 - 0x20];
    char f24;                   /* +24 */
    char p025;
    int f26[4];                 /* +26 */
    char p02e[0x44 - 0x2e];
    int f44[5];                 /* +44 */
    int f4e;                    /* +4e */
    char p050[0x54 - 0x50];
    int f54;                    /* +54 */
    int f56;                    /* +56 */
    char p058[0x5e - 0x58];
    char f5e;                   /* +5e */
    char p05f[0x62 - 0x5f];
    int f62[8];                 /* +62, indexed by racer [inferred] */
    char p072[0x82 - 0x72];
    int f82;                    /* +82 */
    char p084[0xac - 0x84];
    char fac;                   /* +ac */
    char fad;                   /* +ad */
    char fae[10];               /* +ae, indexed by slot [inferred] */
    char fb8[10];               /* +b8, indexed by slot [inferred] */
    char fc2[8];                /* +c2, indexed by object [inferred] */
    char p0ca;
    char fcb;                   /* +cb: slot count [inferred] */
    char p0cc[0xce - 0xcc];
    int fce;                    /* +ce */
    char p0d0[0xd6 - 0xd0];
    int fd6;                    /* +d6 */
    int fd8;                    /* +d8 */
    char p0da[0xdc - 0xda];
    long fdc;                   /* +dc */
    char p0e0[0xec - 0xe0];
    char fec;                   /* +ec */
    char p0ed;
    char fee[0x13e - 0xee];     /* +ee, indexed by object [inferred] */
    char f13e[8];               /* +13e, indexed by object [inferred] */
    char p146[0x15a - 0x146];
} REC_15A;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    char p02[0x1a - 0x02];
    int f1a;                    /* +1a */
    char p1c[0x30 - 0x1c];
    int f30;                    /* +30 */
    char p32[0xad - 0x32];
} REC_AD;

typedef struct {                /* 0x23 bytes, DGROUP array at DS:57a8 */
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p04[2];
    int f06;                    /* +06 */
    char p08[2];
    char f0a;                   /* +0a */
    char f0b;                   /* +0b */
    char f0c[13];               /* +0c: name [inferred] */
    int f19;                    /* +19 */
    char p1b[0x23 - 0x1b];
} REC_23;
#pragma pack()

extern int g_0010;
extern int g_0986[6];
extern int g_0990;
extern int g_0992;
extern long g_1e80;
extern long g_1e84;
extern int g_4eec[8][3];
extern long g_5018;
extern int g_91f8;
extern int g_92e4;
extern int g_93ac;
extern int g_9432;
extern int g_94ca;
extern char g_953e;
extern char g_953f;
extern char g_9540;
extern char g_9541;
extern char g_9542[27];
extern char g_9563;
extern char g_9564[27];
extern int g_967c;
extern int g_9156;
extern char g_a161;
extern char g_a18f[4];
extern char g_a193[4];
extern int g_a1cd;
extern int g_a1cf;
extern int g_13de;
extern long g_1e50;
extern long g_1e58;
extern long g_1e78;
extern long g_1e88;
extern REC_70 far *g_1df8[16];
extern int g_3a02;
extern char g_3966[];
extern HGDIOBJ g_4e94[32];
extern REC_23 g_57a8[];
extern void far *g_4fcc;
extern LPSTR g_6078;
extern REC_297 far *g_69f4;
extern char g_380c[];
extern REC_7C far *g_6e24;
extern int g_92e8;
extern REC_15A g_7090[];
extern long g_09bc[12];
extern int g_90ea;
extern int g_9200;
extern int g_9206;
extern int g_92e6;
extern int g_9316;
extern int g_9318;
extern int g_9322;
extern int g_9320;
extern int g_9334;
extern int g_9346;
extern long g_5078;
extern int g_9406;
extern int g_9408;
extern int g_94b0;
extern int g_94a2;
extern int g_9518;
extern int g_9646;
extern int g_90f4;
extern HGLOBAL g_93a8;
extern HGDIOBJ g_93ae;
extern HGLOBAL g_93b4;
extern REC_AD g_96f0[];
extern char g_9ec2[][40];
typedef struct { int a, b; } PAIR;
extern PAIR g_9f40[][40];
/* g_05a0 is declared long in inspace.h; read here as two ints (world
 * width and height [inferred]). */
#define G_05A0_LO (((int *)&g_05a0)[0])
#define G_05A0_HI (((int *)&g_05a0)[1])
extern int g_9214;
extern int g_940e;
extern PAIR g_104c[];
void far fn_07_2e02(int type, int idx);
void far fn_12_274a(int type, int idx);
extern long g_240c;
extern long g_2410;
extern int g_9150;
extern int g_90ec;
extern int g_9ea2;
extern char g_9eb9[];
extern RECT g_67f8[];

extern int g_9324;
extern int g_0d24;
extern int g_9326;
extern int g_9328;
extern int g_934a;
extern int g_6e72;
extern int g_8e5e;
extern int g_90f8;
extern int g_92e2;
extern int g_937a[8];
extern int g_940a;
extern int g_92ea;
extern int g_92ec[15];
extern int g_92f0;
extern int g_932e;
extern int g_9412;
extern int g_9414;
extern int g_941a;
extern int g_941c;
extern int g_9420;
extern int g_92f8;
extern int g_92fa;
extern int g_9300;
extern int g_9302;
extern int g_9306;
extern int g_933a;
extern int g_933c;
extern int g_940c;
extern int g_92f2;
extern int g_933e;
extern int g_9342;
extern int g_9416;
extern int g_92fc;
extern int g_9340;
extern int g_9418;
extern int g_92fe;
extern int g_941e;
extern int g_9304;
extern int session_helper_groups;   /* DS:9336 */
extern int g_9338;
extern int g_9000;
extern int g_9348;
extern HGLOBAL g_9100[];
extern int g_3a00;
extern int g_90f0;
extern int g_39e8;
extern int g_103a;
extern int g_964a;
extern int g_94e2;
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
void far fn_10_0522(int a);
void far fn_10_5c42(void);
void far fn_10_740c(void);
void far fn_10_0b94(void);
void far fn_10_069a(void);
void far fn_10_5102(void);
void far fn_10_3a2e(void);
void far fn_10_5202(void);
void far fn_10_464a(void);
void far fn_10_3ea2(void);
void far fn_10_565a(void);
void far fn_10_58ce(int a);
void far fn_10_561a(void);
void far fn_10_42ee(void);
void far fn_10_744c(int a);
void far race_marker_strip(void);
void far fn_09_27da(int a);
void far fn_09_2828(void);
void far fn_09_3202(void);
POINT far pascal fn_08_29ea(POINT pt);
long far fn_08_35d0(long a, long b);

void far fn_10_6d52(int a, int b, int c, int d, int e, int f);
void far fn_17_306e(void);
void far fn_02_16a2(void);
void far fn_09_5cca(void);
void far fn_10_0552(int i, int a);
void far fn_10_39a8(int a);
void far fn_13_4eca(LPSTR s);
void far fn_13_218a(int a, LPSTR buf);
void far fn_06_0f1a(int k, LPSTR buf);
void far fn_03_1542(int a, int b, int n, LPSTR buf, int c);
void far fn_07_2512(int i, int v);
void far fn_09_6a12(void);
void far fn_09_0000(int a);
void far fn_10_022e(int a);
void far fn_11_02f0(void);
void far fn_13_65f2(int a);

int far fn_09_094c(void);
void far fn_09_0352(HDC hdc, int x, int flags, int w, int h, LPSTR name);
void far fn_09_09b0(int slot);
int far fn_09_955c(UINT id, LPSTR buf);
void far fn_09_95ba(UINT id);
extern int g_8f70;
extern int flow_interactive;        /* DS:95bc */
extern int g_9ea0;
extern unsigned long g_9e60[];
extern unsigned long g_9e90[];
extern REC_70 far *g_1e30;
extern int g_9332;
extern int g_932c;
extern int g_931a;
extern int g_931c;
extern int g_9334;
extern unsigned long g_1e68;
extern HGLOBAL g_95a6;
extern REC_41 far *g_6e20;
extern int g_9516;
extern int g_0952[];
extern int g_096c[];
typedef struct { int f00; char p02[0x24 - 0x02]; int f24; char p26[0x34 - 0x26]; } REC_34;
extern REC_34 g_3d5a[];
int far fn_13_2688(int n, int m);
int far fn_06_8b90(int i);
int far fn_06_8cb2(int unused, int n, unsigned v, int j, int k);
int far fn_06_8dfe(int i);
void far fn_06_8eb4(void);
void far fn_06_885c(int a, int b);
void far pascal fn_11_b09c(int n, int a);
void far fn_14_421c(int n);
int far fn_14_3eda(void);
void far fn_14_4074(void);
int far fn_10_9672(void);
int far fn_09_88ba(int v);

/* @addr 9:0b2a */
void far fn_09_0b2a(void)
{
    int i;
    int unused;

    for (i = 0; i < g_9406; i++) {
        g_57a8[i].f06 = -1;
        if (g_94b0) {
            g_1df8[0][i].f1e = -1;
            g_69f4[g_94a2].f1d2[i] = g_1df8[0][i].f1e;
        }
        g_1df8[0][i].f18 = 1;
    }
    for (i = 0; i < g_9408; i++)
        g_1df8[1][i].f18 = 1;
    if (g_94b0) {
        g_69f4[g_94a2].f1d1 = 0;
        g_69f4[g_94a2].f150 = 0;
        g_69f4[g_94a2].f14e = g_69f4[g_94a2].f150;
    }
    fn_09_0000(8);
}

/* @addr 9:0c06 */
void far fn_09_0c06(void)
{
    int i;
    int j;

    for (i = 0; i < 2; i++)
        fn_13_4eca("\n\r");
    fn_13_4eca("START OF GAME! \n\r");
    fn_02_16a2();
    g_0992 = 0;
    if (g_92e4 == 0) {
        g_1e58 = 0;
        g_5078 = 0;
        g_9346 = -1;
        g_91f8 = 0;
        g_967c = 0;
        g_94ca = 0;
        g_93ac = 0;
        for (i = 0; i < 8; i++)
            for (j = 0; j < 3; j++)
                g_4eec[i][j] = -1;
        g_9432 = 100;
        g_a1cf = 1;
        g_a1cd = 0;
        for (i = 0; i < 4; i++)
            g_a193[i] = 1;
    }
    for (i = 0; i < 6; i++)
        g_0986[i] = 1;
    g_0990 = 2;
    g_5018 = -1;
    for (i = 0; i < 4; i++)
        g_a18f[i] = 1;
    g_953e = g_9540 = g_953f = g_9541 = 0;
    for (j = 1; j < 27; j++)
        g_9564[j] = g_9542[j] = 0;
    g_9563 = 0;
    g_1e84 = 0;
    g_1e80 = 0;
    g_a161 = -1;
    if (g_9156 != 1) {
        fn_10_0552(5, 1);
        fn_10_39a8(1);
        fn_10_0552(0x16, 1);
    }
    fn_09_5cca();
}

/* @addr 9:0d6c */
void far fn_09_0d6c(void)
{
    int i;

    fn_13_65f2(1);
    fn_11_02f0();
    if (g_13de == 0) {
        g_1e78 = g_1e50 + 25000;
        g_90f4 = 4;
    }
    g_1e88 = 0;
    fn_10_022e(0);
    for (i = 0; i < 10; i++)
        g_96f0[i].f1a = g_96f0[i].f30 = 0;
    PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
    if (g_13de == 0)
        fn_09_6a12();
}

/* @addr 9:1092 */
void far fn_09_1092(void)
{
    int i;

    for (i = 0; i < 32; i++) {
        if (g_4e94[i]) {
            DeleteObject(g_4e94[i]);
            g_4e94[i] = 0;
        }
    }
}

/* @addr 9:225a */
PAIR far fn_09_225a(int a)
{
    PAIR v;
    int idx;
    int t;
    int unused;

    v.a = g_9f40[g_9322][a].a;
    v.b = g_9f40[g_9322][a].b;
    t = g_9ec2[g_9322][a];
    g_1df8[8][g_9318 * 2 + a].f51 = t + g_9318 * 2;
    return v;
}
/* @addr 9:27da */
void far fn_09_27da(int a)
{
    if (g_92e6 == 0)
        fn_10_6d52(g_13dc, g_90ea / 4, g_0010 * 3 / 4 - 10, g_90ea / 2, 20, a);
}

/* @addr 9:484c */
void far fn_09_484c(void)
{
    int i;

    g_9334 = 0;
    for (i = 0; i < 12; i++) {
        if (g_09bc[i] < g_5078)
            g_9334 = i + 1;
    }
}


/* @addr 9:5be0 */
void far fn_09_5be0(int n, int k)
{
    char buf[34];
    int i;

    if (n != g_9646 && g_92e8 == 0) {
        fn_13_218a(g_6e24[k].f64, buf);
        for (i = 0; i < 20; i++) {
            if (buf[i] == ' ') {
                buf[i] = 0;
                break;
            } else if (buf[i] == 'S' && buf[i + 1] == 0) {
                buf[i] = 0;
                break;
            }
        }
        lstrcpy(g_6e24[k].f65, buf);
        fn_06_0f1a(k, buf);
        lstrcat(g_6e24[k].f65, " ");
        lstrcat(g_6e24[k].f65, buf);
    } else
        lstrcpy(g_6e24[k].f65, g_380c);
}

/* Per-segment side flags (+52) of the track polygon at g_1df8[8] and the bounding rects g_67f8 [inferred]. */
/* @addr 9:2012 */
void far fn_09_2012(void)
{
    POINT pa;
    POINT pb;
    POINT pc;
    POINT d1;
    POINT d2;
    int i;
    long l1;
    long l2;
    long r;

    for (i = 0; i < g_9ea2; i++) {
        g_240c = g_1df8[8][g_9318 * 2 + i].f04.x - (g_90ea << (g_9150 - 1));
        g_2410 = g_1df8[8][g_9318 * 2 + i].f04.y - (g_90ec << (g_9150 - 1));
        pa = fn_08_29ea(g_1df8[8][g_9318 * 2 + i].f04);
        if (i < g_9ea2 - 1)
            pb = fn_08_29ea(g_1df8[8][g_9318 * 2 + i + 1].f04);
        else
            pb = fn_08_29ea(g_1df8[8][g_9318 * 2].f04);
        if (i > 0)
            pc = fn_08_29ea(g_1df8[8][g_9318 * 2 + i - 1].f04);
        else
            pc = fn_08_29ea(g_1df8[8][g_9318 * 2 + g_9ea2 - 1].f04);
        d1.x = pa.x - pc.x;
        d1.y = pa.y - pc.y;
        l2 = (int)fn_08_35d0(d2.x = pb.x - pa.x, d2.y = pb.y - pa.y);
        l1 = (int)fn_08_35d0(d1.x, d1.y);
        r = (((long)d2.y * d1.x - (long)d2.x * d1.y) << 7) / (l2 * l1);
        if (r > 0)
            g_1df8[8][g_9318 * 2 + i].f52 = 0;
        else
            g_1df8[8][g_9318 * 2 + i].f52 = 1;
    }
    for (i = 0; i < g_9eb9[g_9322]; i++) {
        g_67f8[i].left = min(g_9f40[g_9322][g_9ec2[g_9322][i]].a, g_9f40[g_9322][i].a);
        g_67f8[i].right = max(g_9f40[g_9322][g_9ec2[g_9322][i]].a, g_9f40[g_9322][i].a);
        g_67f8[i].top = min(g_9f40[g_9322][g_9ec2[g_9322][i]].b, g_9f40[g_9322][i].b);
        g_67f8[i].bottom = max(g_9f40[g_9322][g_9ec2[g_9322][i]].b, g_9f40[g_9322][i].b);
    }
}

/* near-match 99%: 9:0df6 (SetRect right/bottom: the original adds into the
 * world-half register (add si,bx), this adds into the other one) */
/* Places object n of type 4 at a random spot outside the centre rect [inferred]. */
void far fn_09_0df6(int n)
{
    int i;
    int unused;
    int again;
    RECT rc;

    again = 1;
    while (again) {
        g_1df8[4][n].f04.x = (rand() % (G_05A0_LO - 150) + 150) * 8;
        g_1df8[4][n].f04.y = (rand() % (G_05A0_HI - 150) + 150) * 8;
        g_1df8[4][n].f00.x = g_1df8[4][n].f08 = -1000;
        g_1df8[4][n].f00.y = g_1df8[4][n].f0a = -1000;
        g_1df8[4][n].f0c = -(rand() % 50 - 25);
        g_1df8[4][n].f0e = -(rand() % 50 - 25);
        g_1df8[4][n].f26 = 0;
        if ((g_9214 == 3 || g_9214 == 4) && n % 2 == 1)
            g_1df8[4][n].f26 = 5;
        if (g_9214 == 1 || g_9214 == 2)
            g_1df8[4][n].f66 = fn_07_2e02;
        else if (g_9214 == 4 && n % 2 == 0)
            g_1df8[4][n].f66 = fn_07_2e02;
        else
            g_1df8[4][n].f66 = fn_12_274a;
        g_1df8[4][n].f2f = 0;
        g_1df8[4][n].f1e = 0;
        g_1df8[4][n].f50 = 0;
        g_1df8[4][n].f51 = 0;
        g_1df8[4][n].f18 = 0;
        if (g_9320 == 6)
            g_1df8[4][n].f18 = 1;
        SetRect(&rc, (G_05A0_LO / 2 - g_90ea / 2) << g_9150, (G_05A0_HI / 2 - g_90ec / 2) << g_9150,
                (g_90ea / 2 + G_05A0_LO / 2) << g_9150, (g_90ec / 2 + G_05A0_HI / 2) << g_9150);
        again = 0;
        if (PtInRect(&rc, g_1df8[4][n].f04))
            again = 1;
        if (g_940e == 17 && n == g_940e - 1) {
            g_1df8[4][0].f0c = g_1df8[4][0].f0e = 0;
            for (i = 1; i < g_940e; i++) {
                g_1df8[4][i].f04.y = (g_104c[i].a * 208 + g_1df8[4][0].f04.y) % (G_05A0_HI * 8);
                g_1df8[4][i].f04.x = (g_104c[i].b * 208 + g_1df8[4][0].f04.x) % (G_05A0_LO * 8);
                g_1df8[4][i].f0c = g_1df8[4][i].f0e = 0;
            }
        }
    }
}

/* Not yet decompiled. */
/* End-of-wave bookkeeping: music cues, racer records (DS:6e24), ratings
 * and the wave summary in DS:69f4 [inferred].
 * near-match 58%: 9:2828 (one byte short: the game recomputes
 * g_7090[n] for the test after the f76 store; this keeps it in cx). */
void far fn_09_2828(void)
{
    int n;
    int u06;
    int mode;
    int u0a;
    int k;
    int u0e;
    int rank;
    int u12;
    int d;
    int any7;
    int u18;
    int found;
    int m;
    int a;
    int b;

    any7 = 0;
    for (n = 0; n <= g_9316; n++) {
        fn_13_2688(n, g_9646);
        if (g_96f0[g_7090[n].f4e].f1a == 7)
            any7 = 1;
    }
    if ((g_8f70 != 0 || flow_interactive == 0) && g_9320 == 6 && g_91f8 != 0) {
        fn_06_8b90(g_9322);
        switch (g_9ea0) {
        case 1:
            b = 0;
            break;
        case 5:
            b = 1;
            break;
        case 10:
            b = 2;
            break;
        }
        for (n = 0; n <= g_9316; n++) {
            if (n == g_9646 && flow_interactive)
                a = 0;
            else
                a = 1;
            if (g_1e30[n].f51 != 0) {
                if (b > 0) {
                    fn_06_8cb2(g_9322, n, (unsigned)(g_9e60[n] > 64000 ? 64000 : g_9e60[n]), b, 1);
                    if (a == 0)
                        fn_06_8cb2(g_9322, n, (unsigned)(g_9e60[n] > 64000 ? 64000 : g_9e60[n]), b, 0);
                }
                fn_06_8cb2(g_9322, n, (unsigned)(g_9e90[n] > 64000 ? 64000 : g_9e90[n]), 0, 1);
                if (a == 0)
                    fn_06_8cb2(g_9322, n, (unsigned)(g_9e90[n] > 64000 ? 64000 : g_9e90[n]), 0, 0);
            }
        }
        fn_06_8dfe(g_9322);
        fn_06_8eb4();
    }
    for (n = 0; n <= g_9316; n++)
        if (g_7090[n].fec && g_96f0[g_7090[n].f4e].f1a == 7 && g_7090[n].f5e == 0
            && g_7090[n].f54 == 14 && g_7090[n].f56 == g_9646)
            g_9346 = g_7090[g_9646].fd6;
    if (g_9432 < 50)
        g_9332 = 3;
    else if (g_9432 < 180)
        g_9332 = 2;
    else if (g_9432 < 400)
        g_9332 = 1;
    else
        g_9332 = 0;
    g_932c = 0;
    if (g_964a == 0)
        mode = 1;
    else if (g_964a == 0 && g_9332 < 2)
        mode = 2;
    else if (g_964a > 0 && g_964a < 5)
        mode = 2;
    else if (g_964a > 4 && g_964a < 9)
        mode = 3;
    else if (g_964a > 8 && g_964a < 16) {
        if (g_9332 < 2 || any7)
            mode = 4;
        else
            mode = 3;
    } else if (g_964a > 15)
        mode = 4;
    switch (mode) {
    case 0:
        g_932c = 0;
        break;
    case 1:
        if (rand() % 100 < 20)
            g_932c = 1;
        break;
    case 2:
        if (rand() % 100 < 50)
            g_932c = 1;
        break;
    case 3:
        if (rand() % 100 < 80)
            g_932c = 1;
        break;
    case 4:
        g_932c = 1;
        break;
    }
    if (g_91f8 == 0)
        g_932c = 0;
    if (g_91f8 > 0) {
        b = g_9214;
        fn_10_9672();
        if (b != g_9214)
            fn_10_0552(4, 1);
        fn_10_565a();
    }
    if (g_91f8 > 0) {
        for (n = 0; n <= g_9316; n++) {
            fn_11_b09c(n, 0);
            if (g_7090[n].fd6 == -1)
                continue;
            for (k = 0; k <= g_9316; k++)
                g_6e24[g_7090[n].fd6].f3c[g_7090[k].fd6] = g_7090[n].f62[k] / 10;
            for (k = 0; k < 4; k++)
                g_6e24[g_7090[n].fd6].f38[k] = g_7090[n].f26[k];
            if (g_7090[n].fec == 0)
                g_6e24[g_7090[n].fd6].f38[0] = 0;
            for (k = 0; k < g_7090[n].fcb; k++) {
                g_6e24[g_7090[n].fd6].f28[k] = g_7090[n].fb8[k];
                g_6e24[g_7090[n].fd6].f1e[k] = g_7090[n].fae[k];
            }
            g_6e24[g_7090[n].fd6].f1d = g_7090[n].fcb;
            fn_14_421c(n);
            g_6e24[g_7090[n].fd6].f06 = g_7090[n].f82;
            g_6e24[g_7090[n].fd6].f1c = g_7090[n].f1e / 40;
            g_6e24[g_7090[n].fd6].f74 = g_7090[n].f24;
            g_6e24[g_7090[n].fd6].f75 = g_7090[n].f0a;
            g_6e24[g_7090[n].fd6].f72 = g_7090[n].fac;
            g_6e24[g_7090[n].fd6].f73 = g_7090[n].fad;
            g_6e24[g_7090[n].fd6].f04 = g_7090[n].fce;
            g_7090[n].fdc = g_7090[n].fdc > 327670L ? 327670L : g_7090[n].fdc;
            g_6e24[g_7090[n].fd6].f02 = g_7090[n].fdc / 10;
            u12 = (g_7090[n].fdc * 3 + g_7090[n].fd8) / 100;
            for (k = 1; k < 11; k++)
                if (g_0952[k] <= u12 && g_096c[k] > u12) {
                    rank = k;
                    break;
                }
            g_6e24[g_7090[n].fd6].f76 = rank;
            u0e = g_9646;
            if (g_7090[n].fec == 0 || g_7090[n].f82 < 0 || n == u0e) {
                for (k = 0; k < 8; k++)
                    if (g_69f4[g_94a2].f1c0[k] == g_7090[n].fd6)
                        g_69f4[g_94a2].f1c0[k] = -1;
            } else {
                found = 0;
                for (k = 0; k < 8; k++)
                    if (g_69f4[g_94a2].f1c0[k] == g_7090[n].fd6)
                        found = 1;
                if (!found)
                    for (k = 0; k < 8; k++)
                        if (g_69f4[g_94a2].f1c0[k] == -1) {
                            g_69f4[g_94a2].f1c0[k] = g_7090[n].fd6;
                            break;
                        }
            }
        }
        g_931c = g_7090[g_9646].fd6;
        for (n = 0; n <= g_931a; n++) {
            if (g_1e68 > 500) {
                if (g_6e24[n].f76 + 3 < g_9334)
                    d = g_6e24[n].f06 / -3;
                else if (g_6e24[n].f76 + 1 < g_9334)
                    d = -(g_6e24[n].f06 / 8);
                else
                    d = g_6e24[n].f06 / -14;
                b = 0;
                if (g_95a6 == 0) {
                    fn_14_3eda();
                    b = 1;
                }
                a = fn_09_88ba(g_6e20[g_6e24[n].f00].f05 - g_9332);
                d += g_6e24[n].f06 * a / -20;
                if (b)
                    fn_14_4074();
                g_6e24[n].f06 = g_6e24[n].f06 + d < 0 ? 0 : g_6e24[n].f06 + d;
            }
        }
        for (n = m = 0; m < 8; m++, n++) {
            k = 0;
            if (g_1df8[0][m].f18 != 0)
                for (k = m + 1; k < 8; k++)
                    if (g_1df8[0][k].f18 == 0) {
                        m = k;
                        break;
                    }
            if (k >= 8)
                break;
            if (g_1df8[0][m].f2f < 0)
                g_69f4[g_94a2].f1c8[n] = 2;
            if (g_1df8[0][m].f53 == 2)
                g_69f4[g_94a2].f1c8[n] = 1;
            g_69f4[g_94a2].f1d2[n] = g_1df8[0][m].f1e;
        }
        for (; n < 8; n++) {
            g_69f4[g_94a2].f1d2[n] = 0;
            g_69f4[g_94a2].f1c8[n] = 0;
        }
        g_69f4[g_94a2].fa3 = 0;
        g_69f4[g_94a2].fa0 = 0;
        g_69f4[g_94a2].fa1 = 0;
        for (n = 0; n < g_9418; n++)
            if (g_1df8[9][n].f18 == 0)
                g_69f4[g_94a2].fa3++;
        for (n = 0; n < g_940c; n++) {
            if (g_1df8[3][n].f44 == 350 && g_1df8[3][n].f18 == 0)
                g_69f4[g_94a2].fa0++;
            if (g_1df8[3][n].f44 == 1400 && g_1df8[3][n].f18 == 0)
                g_69f4[g_94a2].fa1++;
        }
        for (n = 0; n < g_9416; n++) {
            g_69f4[g_94a2].fae[n] = g_1df8[8][n].f1e;
            if (g_3d5a[n].f00 == -3)
                g_69f4[g_94a2].fae[n] = -g_69f4[g_94a2].fae[n];
            g_69f4[g_94a2].ffe[n] = g_3d5a[n].f24;
        }
    }
    if (g_7090[g_9646].fec && g_91f8 > 0 && (flow_interactive || g_9516 == 0))
        fn_06_885c(0, 0);
}

/* Not yet decompiled. */
void far fn_09_3202(void)
{
}

/* Sets up a level: display scale from the INI file, object tables and the
 * per-type builders, with progress steps (fn_09_27da) [inferred]. */
/* near-match 56%: 9:22b4 (the zero stores after g_9406 = 8 come out grouped
 * after the constant stores, and g_940a/g_940c are not merged into one dword
 * store; rest of the body lines up) */
void far fn_09_22b4(int a)
{
    int i;
    int j;
    int unused;
    char buf[40];
    char buf2[40];
    int cur;
    int v;

    g_9324 = 14;
    g_9326 = g_0d24 = 0;
    g_9328 = 5;
    g_934a = 3;
    g_6e72 = -1;
    fn_09_27da(1);
    if (g_92e6 == 0) {
        LoadString(g_9212, 0x383, buf, 40);
        lstrcat(buf, "...");
        fn_10_94c4(2, 6, 0x200ff00L, g_90ea / 2, g_0010 * 3 / 4 + 20, buf);
        if (g_90f8 && g_8e5e) {
            cur = g_9156;
            v = GetPrivateProfileInt(g_96a9, "DScale", 0, g_9690);
            if (v == 0) {
                if ((rand() & 1) || g_9156 == 2) {
                    cur = rand() % 3;
                    if (cur == g_9156 && cur == 2)
                        cur = 1;
                }
            } else
                cur = v - 1;
            if (cur != g_9156) {
                g_92e2 = 1;
                g_9156 = cur;
                fn_06_0f1a(cur, buf2);
                WritePrivateProfileString(g_96a9, "Size", buf2, g_9690);
            }
        }
        if (g_92e2) {
            g_9156 = GetPrivateProfileInt(g_96a9, "Size", 1, g_9690);
            g_9150 = 4 - g_9156;
            fn_10_0522(1);
            fn_10_5c42();
        }
        g_92e2 = 0;
    }
    if (g_91f8 == 0)
        fn_09_2828();
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 5; j++)
            g_7090[i].f44[j] = 0;
        for (j = 0; j < 8; j++)
            g_7090[i].fc2[j] = g_7090[i].f13e[j] = 0;
    }
    for (i = 0; i < 8; i++)
        g_937a[i] = 0;
    fn_09_3202();
    if (g_9432 > 250)
        g_9432 = g_9432 * 7 / 10;
    else
        g_9432 = g_9432 * 9 / 10;
    g_9406 = 8;
    (&g_9406)[g_9328] = g_940a = g_9408 = 0;
    g_92ea = 14;
    g_92ec[0] = 8;
    g_92ec[1] = 2;
    g_92f0 = g_932e * 8;
    g_92ec[g_9328] = g_9420 = g_941c = g_941a = g_9414 = g_9412 = 0;
    g_92fa = g_92f8 = 1;
    g_9302 = g_9300 = 3;
    g_9306 = 0;
    g_92f2 = g_940c = g_933c + g_933a;
    g_92fc = g_9416 = g_933e + g_9342;
    g_92fe = g_9418 = g_9340;
    g_92ea = g_933a;
    if (g_940c > 127) {
        g_940c = 120;
        g_92f2 = 920;
        g_933c = g_933a = 60;
    }
    g_9416 += g_9318 * 2;
    g_9304 = g_941e = g_9318 * 2;
    g_92fc += g_9318 * 2;
    if (g_92fc > 80)
        g_92fc = g_9416 = 80;
    if (g_92e8) {
        g_9326 = 1;
        g_9338 = session_helper_groups = g_940c = 0;
    }
    if (g_9320 == 6) {
        g_92f0 = g_940c = g_940a = 0;
        if (g_9000 == 2 || (g_9000 == 1 && g_9334 > 8))
            g_9348 = 1;
        else if ((g_9000 == 0 && g_9334 > 3) || g_9334 < 4)
            g_9348 = 2;
        else
            g_9348 = 3;
    }
    for (i = 0; i <= g_9324; i++) {
        GlobalUnlock(g_9100[i]);
        g_9100[i] = GlobalReAlloc(g_9100[i], (long)(g_92ec[i] < 1 ? 1 : g_92ec[i]) * 0x70, 0x42);
        g_1df8[i] = (REC_70 far *)GlobalLock(g_9100[i]);
    }
    fn_10_740c();
    fn_10_0b94();
    fn_10_069a();
    fn_09_27da(4);
    fn_10_740c();
    if (g_3a00 == 0) {
        fn_10_39a8(1);
        fn_09_27da(9);
        fn_10_740c();
        if (g_90f0)
            fn_10_5102();
        else
            fn_10_3a2e();
        fn_09_27da(0x3c);
        fn_10_740c();
        fn_10_5202();
    }
    fn_10_740c();
    fn_09_27da(0x41);
    if (g_932e && g_39e8 == 0)
        fn_10_464a();
    fn_10_740c();
    fn_09_27da(0x46);
    if (g_90f0 == 0)
        fn_10_5102();
    else
        fn_10_3a2e();
    fn_09_27da(0x4e);
    fn_10_740c();
    fn_10_3ea2();
    fn_09_27da(0x51);
    fn_10_740c();
    fn_10_565a();
    fn_09_27da(0x53);
    fn_10_740c();
    if (g_9418) {
        fn_10_58ce(1);
        fn_10_740c();
    }
    fn_09_27da(0x58);
    fn_10_561a();
    fn_10_740c();
    fn_09_27da(0x61);
    fn_10_42ee();
    fn_10_740c();
    if (g_9320 == 6)
        race_marker_strip();
    fn_10_740c();
    if (g_103a)
        g_103a = 0;
    fn_09_27da(100);
    g_964a = 0;
    fn_10_744c(0x6e);
    if (g_92e6 == 0)
        PatBlt(g_13dc, g_90ea / 4 - 2, g_0010 * 3 / 4 - 12, g_90ea / 2 + 4, 0x46, BLACKNESS);
    g_92e6 = 1;
    g_94e2 = (g_9340 + g_9342) * 2 + g_933c + g_933e + g_933a;
}
