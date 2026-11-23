/* INSPACE.EXE segment 9 (selector 1040), 9:0b2a-5be0: one source file
 * (functions near-call each other) [inferred]. */
/* Declared before inspace.h: CL's register choice in 9:0df6 depends on
 * declaration order (g_90ea/g_90ec before g_05a0). */
extern int g_90ea;
extern int g_90ec;
#include <stdlib.h>

#include "inspace.h"
/* Declared before g_933e: CL adds g_933e first in 9:10d4. */
extern int g_4ee0;

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
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    int f26;                    /* +26 */
    char p28[0x2c - 0x28];
    int f2c;                    /* +2c */
    char p2e;
    char f2f;
    char p30[0x42 - 0x30];
    int f42;                    /* +42 */
    int f44;                    /* +44 */
    int f46;                    /* +46 */
    int f48;                    /* +48 */
    char p4a[0x50 - 0x4a];
    char f50;                   /* +50 */
    char f51;
    char f52;                   /* +52 */
    char f53;                   /* +53 */
    char f54;                   /* +54 */
    char p55[0x5e - 0x55];
    int (far *f5e)(int type, int idx, int amount);  /* +5e [inferred] */
    void (far pascal *f62)(int type, int n, HDC dc);  /* +62 [inferred] */
    void (far *f66)(int type, int idx);  /* +66 */
    char p6a[0x70 - 0x6a];
} REC_70;

#pragma pack(1)
typedef struct {                /* 0x297 bytes, far array at DS:69f4 */
    POINT f000[40];             /* +000 */
    char fa0[5];                /* +a0: per-type counts [inferred] */
    char fa5[2];                /* +a5 */
    char fa7[2];                /* +a7 */
    char fa9[2];                /* +a9 */
    char fab[2];                /* +ab */
    char fad;                   /* +ad */
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
    unsigned char f1e2[0x232 - 0x1e2];
    char f232[10];              /* +232: group first index */
    char f23c[10];              /* +23c: group end index */
    char f246[10];              /* +246 */
    char f250[10];              /* +250 */
    char f25a[10];              /* +25a */
    char f264;                  /* +264: group count */
    char f265[10];              /* +265 */
    POINT f26f[10];             /* +26f */
} REC_297;

typedef struct {                /* 0x7c bytes, far array at DS:6e24 */
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08[5];                 /* +08 */
    char f12[5];                /* +12 */
    char f17[5];                /* +17 */
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
extern int g_9338;
extern int g_0994;
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
extern int g_9ea4;
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
extern int g_940c;
extern int g_92f2;
extern int g_9342;
extern int g_933e;
extern int g_933c;
extern int g_9416;
extern int g_92fc;
extern int g_9340;
extern int g_9418;
extern int g_92fe;
extern int g_941e;
extern int g_9304;
extern int session_helper_groups;   /* DS:9336 */
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
/* 0x34-byte records seen from DS:3d50 (below g_3d5a's base) [inferred]. */
typedef struct {
    long f00;                   /* +00 */
    char p04[0x08 - 0x04];
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    char p12[0x18 - 0x12];
    int f18;                    /* +18 */
    char p1a[0x1c - 0x1a];
    int f1c;                    /* +1c */
    int f1e;                    /* +1e */
    int f20;                    /* +20 */
    int f22;                    /* +22 */
    char p24[0x2a - 0x24];
    int f2a;                    /* +2a */
    char p2c[0x2e - 0x2c];
    int f2e;                    /* +2e */
    int f30;                    /* +30 */
    int f32;                    /* +32 */
} REC_34B;
extern REC_34B g_3d50[];
typedef struct {                /* 0x1c bytes at DS:6678 [inferred] */
    RECT r;                     /* +00 */
    char p08[0x0a - 0x08];
    int f0a;                    /* +0a */
    char p0c[0x0e - 0x0c];
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    char p14[0x1c - 0x14];
} REC_1CB;
extern REC_1CB g_6678[];
typedef struct {                /* 0x10 bytes at DS:4f2c [inferred] */
    int f00;                    /* +00: first index */
    int f02;                    /* +02: end index */
    int f04;                    /* +04 */
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    POINT f0a;                  /* +0a */
    int f0e;                    /* +0e */
} REC_10;
extern REC_10 g_4f2c[];
#pragma pack(1)
typedef struct {                /* 0x14 bytes at DS:4d90 [inferred] */
    char f00;
    char f01;                   /* +01 */
    char f02;                   /* +02 */
    char f03;                   /* +03 */
    char f04;                   /* +04 */
    char f05;                   /* +05 */
    char f06;
    char f07;                   /* +07 */
    char f08;                   /* +08 */
    char f09;                   /* +09 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    int f10;                    /* +10 */
    char p12[0x14 - 0x12];
} REC_14;
#pragma pack()
extern REC_14 g_4d90[];
typedef struct { char p00[0x12]; int f12; char p14[0x50 - 0x14]; } REC_50B;
extern REC_50B g_2f4c[];        /* 0x50-byte records [inferred] */
extern POINT g_a120[];
extern POINT g_9ea8[];
extern int g_9344;
extern int g_4ed4[2];
extern int g_4ee4;
extern int g_4ee8[2];
#define SC(n) ((n) << g_9156 >> 1)
void far pascal fn_11_39d8(int type, int n, HDC dc);
int far fn_07_5090(int type, int idx, int amount);
int far fn_07_2652(int type, int idx, int amount);
int far fn_10_18b0(int a, int b, int c, int d, int e);
void far fn_10_533a(int a);
void far fn_10_1dd8(void);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
void far fn_09_4896(void);
extern int g_4ee2;
extern int g_8ff8;
extern int g_9208;
extern HGLOBAL g_9110;
typedef struct { char p00[0x74]; POINT f74; char p78[0xe0 - 0x78]; } REC_E0;
extern REC_E0 far *g_1e28;
int far fn_06_71b2(int deg);
int far fn_06_720c(int deg);
extern int g_4f1c[];
extern int g_4fd0[][3];
extern int g_932a;
extern int g_967e;
extern int g_94a6;
extern int g_94a8;
extern int g_94aa;
extern char g_9eb4;
extern char g_9eb5;
extern int g_094e;
extern int g_0950;
extern int g_92f4;
extern int g_9ea6;
extern char g_9ebf[];
extern char g_9f39[][2];
extern HGLOBAL g_92e0;
extern DWORD far *g_3d4c;
extern char g_1822[];
extern char g_38c9;
extern char g_6990[];
extern char g_8f7a[];
extern int g_94c4;
extern int g_9330;
void far fn_06_11ec(void);
int far fn_16_5f0e(LPSTR a, LPSTR b);
void far fn_10_320a(void);
void far fn_06_72d8(int a, int b);

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

/* Places object n of type 4 at a random spot outside the centre rect [inferred]. */
/* @addr 9:0df6 */
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

/* End-of-wave bookkeeping: music cues, racer records (DS:6e24), ratings
 * and the wave summary in DS:69f4 [inferred]. */
/* @addr 9:2828 */
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
        lbl:    /* bare label: resets register tracking (recompute g_7090[n]) */
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
        g_69f4[g_94a2].fa0[3] = 0;
        g_69f4[g_94a2].fa0[0] = 0;
        g_69f4[g_94a2].fa0[1] = 0;
        for (n = 0; n < g_9418; n++)
            if (g_1df8[9][n].f18 == 0)
                g_69f4[g_94a2].fa0[3]++;
        for (n = 0; n < g_940c; n++) {
            if (g_1df8[3][n].f44 == 350 && g_1df8[3][n].f18 == 0)
                g_69f4[g_94a2].fa0[0]++;
            if (g_1df8[3][n].f44 == 1400 && g_1df8[3][n].f18 == 0)
                g_69f4[g_94a2].fa0[1]++;
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

/* Places the race track pieces (type 8 and 12 objects), their gates and
 * the checkpoints at the start of a race [inferred]. */
/* @addr 9:10d4 */
void far fn_09_10d4(void)
{
    int i;
    int j;
    int k;
    int t;
    int u0c;
    int res;
    int sel;
    int u12;
    int a;
    int b;
    int d;
    int cnt;
    int u1c;
    RECT rcw;
    RECT rc1;
    RECT rc2;
    RECT rc3;
    POINT pos;
    int ok;
    int flag;
    char pad46[14];             /* frame filler [inferred] */

    SetRect(&rcw, G_05A0_LO / 2 - 150, G_05A0_HI / 2 - 100,
            G_05A0_LO / 2 + 150, G_05A0_HI / 2 + 80);
    for (i = 0; i < g_9318 * 2; i++) {
        g_1df8[8][i].f08 = -1000;
        g_1df8[8][i].f00.x = g_1df8[8][i].f08;
        g_1df8[8][i].f0a = -1000;
        g_1df8[8][i].f00.y = g_1df8[8][i].f0a;
        if (!g_94b0)
            g_1df8[8][i].f1e = g_69f4[g_94a2].fae[i];
        else
            g_1df8[8][i].f1e = 0;
        if (g_94b0) {
            pos.x = (rand() % (G_05A0_LO - 60) + 30) * 8;
            pos.y = (rand() % (G_05A0_HI - 60) + 30) * 8;
        } else
            pos = g_69f4[g_94a2].f000[i];
        if (i >= g_9318 * 2)
            g_1df8[8][i].f04 = pos;
        g_1df8[8][i].f18 = 0;
        g_1df8[8][i].f24 = SC(6);
        g_1df8[8][i].f2f = 2;
        g_1df8[8][i].f54 = 1;
        if (i < g_9318 * 2) {
            g_3d50[i].f30 = -1;
            g_1df8[8][i].f44 = 3500;
            g_1df8[8][i].f22 = SC(0x22);
            g_1df8[8][i].f20 = 0x110;
            g_1df8[8][i].f42 = 8;
            g_1df8[8][i].f46 = 1;
            g_1df8[8][i].f62 = fn_11_39d8;
            g_1df8[8][i].f5e = fn_07_5090;
            g_3d50[i].f1c = 3;
            if (!(i & 1)) {
                g_6678[i / 2].f0a = 1200;
                g_6678[i / 2].f0e = 0x50;
                if (g_9320 == 6) {
                    pos.x = g_a120[g_9322].x - g_6678[i / 2].f0a / 2 - 160;
                    pos.y = g_a120[g_9322].y;
                } else if (g_94b0) {
                    pos.x = rand() % (G_05A0_LO - 300) * 8;
                    pos.y = (rand() % (G_05A0_HI - 200) + 200) * 8;
                }
                if (g_94b0 && g_9320 != 6) {
                    do {
                        SetRect(&rc1, pos.x - 720, pos.y - 720, pos.x + 2400, pos.y + 1200);
                        ok = 1;
                        for (j = 0; j < g_9324; j++)
                            for (k = 0; k < (&g_9406)[j]; k++) {
                                SetRect(&rc2, g_1df8[j][k].f04.x - 160, g_1df8[j][k].f04.y - 160,
                                        g_1df8[j][k].f04.x + 320, g_1df8[j][k].f04.y + 320);
                                if (IntersectRect(&rc3, &rc1, &rc2)) {
                                    ok = 0;
                                    pos.x = rand() % (G_05A0_LO - 300) * 8;
                                    pos.y = (rand() % (G_05A0_HI - 200) + 200) * 8;
                                    break;
                                }
                            }
                    } while (!ok);
                } else {
                    SetRect(&rc1, pos.x - 720, pos.y - 720, pos.x + 2400, pos.y + 1200);
                    for (t = 0; t <= 9; t++)
                        if (t == 0 || t == 4 || t == 3 || t == 9)
                            for (k = 0; k < (&g_9406)[t]; k++) {
                                SetRect(&rc2, g_1df8[t][k].f04.x - 160, g_1df8[t][k].f04.y - 160,
                                        g_1df8[t][k].f04.x + 320, g_1df8[t][k].f04.y + 320);
                                if (IntersectRect(&rc3, &rc1, &rc2))
                                    g_1df8[t][k].f04.y = (g_1df8[t][k].f04.y + 1600)
                                                         % (G_05A0_HI * 8);
                            }
                }
                g_1df8[8][i].f04 = pos;
                g_1df8[8][i + 1].f04 = pos;
                g_1df8[8][i + 1].f04.x += g_1df8[8][i].f20 + g_6678[i / 2].f0a;
                g_6678[i / 2].f10 = i;
                g_1df8[12][i].f04 = pos;
                g_1df8[12][i + 1].f04 = pos;
                g_1df8[12][i].f04.x += g_6678[i / 2].f0a / 2 + 160;
                g_1df8[12][i].f04.y -= 150;
                g_1df8[12][i + 1].f04.x += g_6678[i / 2].f0a / 2 + 160;
                SetRect(&g_6678[i / 2].r, g_1df8[8][i].f04.x + g_1df8[8][i].f20,
                        g_1df8[8][i].f04.y + g_1df8[8][i].f20 / 2 - 24,
                        g_1df8[8][i].f04.x + g_1df8[8][i].f20 + g_6678[i / 2].f0a,
                        g_1df8[8][i].f04.y + g_1df8[8][i].f20 / 2 + 24);
                g_1df8[12][i].f44 = 0;
                g_1df8[12][i].f22 = 0;
                g_1df8[12][i].f20 = 0;
                g_1df8[12][i + 1].f44 = 0;
                g_1df8[12][i + 1].f22 = 0;
                if (i == 2)
                    g_6678[i / 2].f12 = 1;
                if (i == 4)
                    g_6678[i / 2].f12 = 2;
            }
        }
    }
    if (g_94b0 && g_9320 != 6)
        fn_09_4896();
    for (i = g_9318 * 2; i < g_9416; i++) {
        g_1df8[8][i].f08 = -1000;
        g_1df8[8][i].f00.x = g_1df8[8][i].f08;
        g_1df8[8][i].f0a = -1000;
        g_1df8[8][i].f00.y = g_1df8[8][i].f0a;
        if (!g_94b0) {
            g_1df8[8][i].f1e = g_69f4[g_94a2].fae[i];
            g_3d50[i].f2e = g_69f4[g_94a2].ffe[i];
        } else
            g_1df8[8][i].f1e = 0;
        if (g_94b0 || g_9320 == 6) {
            ok = 0;
            for (j = 0; j < g_9344; j++)
                if (g_4f2c[j].f00 <= i && g_4f2c[j].f02 > i) {
                    ok = 1;
                    g_3d50[i].f32 = j;
                    g_1df8[8][i].f54 = 1;
                    break;
                }
            if (!ok) {
                g_3d50[i].f32 = -1;
                ok = 0;
                if (g_9320 != 6)
                    do {
                        ok = 1;
                        pos.x = rand() % G_05A0_LO * 8;
                        pos.y = rand() % G_05A0_HI * 8;
                        for (j = 0; j < g_9318; j++)
                            if (fn_08_285a(&a, &b, pos, g_1df8[12][j * 2].f04) < 150)
                                ok = 0;
                        for (j = 0; j < g_9344; j++) {
                            d = fn_08_285a(&a, &b, pos, g_4f2c[j].f0a);
                            if ((g_4f2c[j].f04 >> 3) + 200 > d)
                                ok = 0;
                        }
                        for (j = 0; j < i; j++) {
                            d = fn_08_285a(&a, &b, pos, g_1df8[8][j].f04);
                            if (d < 80)
                                ok = 0;
                        }
                    } while (!ok);
                else
                    *(PAIR *)&pos = fn_09_225a(i - g_9318 * 2);   /* PAIR result into a POINT */
            } else
                pos = g_1df8[8][i].f04;
        } else {
            pos = g_69f4[g_94a2].f000[i];
            g_3d50[i].f32 = -1;
            for (j = 0; j < g_9344; j++)
                if (g_4f2c[j].f00 <= i && g_4f2c[j].f02 > i)
                    g_3d50[i].f32 = j;
        }
        g_1df8[8][i].f04 = pos;
        g_1df8[8][i].f18 = 0;
        g_1df8[8][i].f24 = SC(5);
        g_1df8[8][i].f54 = 1;
        if (i < g_9318 * 2 + g_933e) {
            g_1df8[8][i].f44 = 3500;
            g_1df8[8][i].f42 = 8;
            g_1df8[8][i].f46 = 4;
            g_1df8[8][i].f62 = fn_11_39d8;
            g_1df8[8][i].f5e = fn_07_2652;
            g_1df8[8][i].f66 = fn_12_274a;
            if (i < g_9318 * 2 + g_4ee4) {
                g_3d50[i].f0a = g_4d90[g_4ee8[0]].f03;
                g_3d50[i].f30 = g_4ee8[0];
            } else {
                g_3d50[i].f0a = g_4d90[g_4ee8[1]].f03;
                g_3d50[i].f30 = g_4ee8[1];
            }
            if (g_3d50[i].f30 == 3) {
                g_1df8[8][i].f24 = SC(4);
                g_1df8[8][i].f22 = SC(14);
                g_1df8[8][i].f20 = 0x70;
                g_1df8[8][i].f2c = 12000;
                g_1df8[8][i].f48 = 0;
            } else if (g_3d50[i].f30 == 4) {
                g_1df8[8][i].f24 = SC(4);
                g_1df8[8][i].f22 = SC(20);
                g_1df8[8][i].f20 = 0x98;
                g_1df8[8][i].f2c = 0x78;
                g_1df8[8][i].f48 = 8;
            } else {
                g_1df8[8][i].f24 = SC(6);
                g_1df8[8][i].f22 = SC(0x22);
                g_1df8[8][i].f20 = 0x110;
                g_1df8[8][i].f2c = 0x78;
                g_1df8[8][i].f48 = 8;
            }
            g_3d50[i].f1c = 1;
            if (g_3d50[i].f0a != 4)
                g_1df8[8][i].f2f = 2;
        } else {
            g_3d50[i].f1c = 2;
            if (i < g_9318 * 2 + g_933e + g_4ee0)
                sel = 0;
            else
                sel = 1;
            g_3d50[i].f20 = g_4d90[g_4ed4[sel]].f0e;
            g_3d50[i].f22 = g_4d90[g_4ed4[sel]].f10;
            g_3d50[i].f2a = g_4d90[g_4ed4[sel]].f01;
            g_3d50[i].f0a = g_4d90[g_4ed4[sel]].f03;
            g_3d50[i].f18 = g_4d90[g_4ed4[sel]].f04;
            g_1df8[8][i].f44 = g_4d90[g_4ed4[sel]].f0a;
            if (g_9320 == 6)
                g_1df8[8][i].f54 = 1;
            else
                g_1df8[8][i].f54 = g_4d90[g_4ed4[sel]].f02;
            g_1df8[8][i].f48 = 9;
            g_1df8[8][i].f2c = g_4d90[g_4ed4[sel]].f0c;
            if (g_1df8[8][i].f2c < fn_09_88ba(g_1df8[8][i].f1e))
                g_1df8[8][i].f18 = 1;
            if (g_3d50[i].f0a != 4)
                g_1df8[8][i].f2f = 5;
            if (g_4d90[g_4ed4[sel]].f03 == -1)
                flag = 1;
            else
                flag = 0;
            if (g_94b0 && g_3d50[i].f0a == -1 && !(rand() & 1))
                g_3d50[i].f0a = -3;
            else if (!g_94b0 && g_3d50[i].f0a == -1 && g_1df8[8][i].f1e < 0) {
                g_1df8[8][i].f1e = -g_1df8[8][i].f1e;
                g_3d50[i].f0a = -3;
            }
            g_3d50[i].f30 = g_4ed4[sel];
            g_1df8[8][i].f42 = 6;
            g_1df8[8][i].f46 = 4;
            g_1df8[8][i].f62 = fn_11_39d8;
            g_1df8[8][i].f5e = fn_07_2652;
            g_1df8[8][i].f66 = fn_07_2e02;
            res = fn_10_18b0(g_3d50[i].f22, g_3d50[i].f20, g_3d50[i].f2a, flag, g_3d50[i].f30);
            if (g_3d50[i].f0a > 0 && g_2f4c[g_3d50[i].f0a].f12)
                fn_10_533a(g_3d50[i].f0a);
            g_1df8[8][i].f24 = SC(g_4d90[g_3d50[i].f30].f09);
            g_1df8[8][i].f22 = SC(g_4d90[g_3d50[i].f30].f08);
            g_1df8[8][i].f20 = g_4d90[g_3d50[i].f30].f08 * 8;
            g_3d50[i].f1e = res;
        }
        if (g_3d50[i].f0a == 1)
            g_3d50[i].f10 = rand() % 7 * 500 + 600;
        else
            g_3d50[i].f10 = rand() % 7 * 500 + 1200;
        g_3d50[i].f00 = 0;
        g_3d50[i].f0e = rand() % ((g_91f8 + 1) * 200) + 20;
        g_3d50[i].f0c = (g_91f8 + 5) * 3;
        if (g_3d50[i].f0c > 22)
            g_3d50[i].f0c = 22;
        g_3d50[i].f08 = rand() % 2;
        if (g_3d50[i].f30 != 4 && g_3d50[i].f30 != 3) {
            g_1df8[8][i].f04.x -= g_1df8[8][i].f20 / 2;
            g_1df8[8][i].f04.y -= g_1df8[8][i].f20 / 2;
        }
        for (j = 0; j < g_9344; j++)
            if (g_4f2c[j].f00 <= i && g_4f2c[j].f02 > i) {
                g_1df8[8][i].f54 = 1;
                break;
            }
    }
    fn_10_1dd8();
    cnt = i = 0;
    for (i = 0; i < g_9344; i++)
        if (i == 0 || (g_4f2c[i - 1].f0a.x != g_4f2c[i].f0a.x
                       && g_4f2c[i - 1].f0a.y != g_4f2c[i].f0a.y)) {
            g_1df8[0][cnt].f54 = 1;
            g_1df8[0][cnt].f0e = 0;
            g_1df8[0][cnt].f0c = g_1df8[0][cnt].f0e;
            g_1df8[0][cnt].f04.x = g_4f2c[i].f0a.x - 128;
            g_1df8[0][cnt].f04.y = g_4f2c[i].f0a.y - 128;
            cnt++;
            g_0992 += (g_4f2c[i].f02 - g_4f2c[i].f00 + 5) * 2;
        }
    if (g_9320 == 6 && g_9406 != 0) {
        POINT p0;               /* shares the frame with CL's temporaries */

        p0.y = g_9ea8[g_9322].x - 360;
        p0.x = g_1df8[12][0].f04.x;
        for (i = 0; i < g_9406; i++) {
            g_1df8[0][i].f54 = 1;
            g_1df8[0][i].f0e = 0;
            g_1df8[0][i].f0c = g_1df8[0][i].f0e;
            g_1df8[0][i].f04.x = ((g_9406 - 1) * 64 / 2 - i * 64 - 16) * 8 + p0.x;
            g_1df8[0][i].f04.y = p0.y;
        }
    }
    g_69f4[g_94a2].fad = g_9318;
    if (g_9320 == 6)
        g_69f4[g_94a2].fad = 0xff - g_9322;
    for (i = 0; i < g_9416; i++)
        g_69f4[g_94a2].f000[i] = g_1df8[8][i].f04;
    if (g_9320 == 6)
        fn_09_2012();
}

#define R297 g_69f4[g_94a2]
/* Builds the wave's enemy groups: up to five rings of objects around random
 * centres, plus escort rings, and stores the group table [inferred]. */
/* @addr 9:4896 */
void far fn_09_4896(void)
{
    int u4;
    int u6;
    int c;
    int s;
    int total;
    int dir[40];
    POINT ctr[5];
    POINT pos[40];
    int t112;
    int t114;
    int t116;
    int t118;
    int ang;
    int d1;
    int d2;
    long rad[5];
    long r136;
    long r13a;
    int cnt1[5];
    int cnt2[5];
    int remain;
    int m;
    int sum;
    int cnt;
    int sub[2];
    int j;
    int state;
    int kind1[5];
    int kind2[5];
    int c174;
    int c176;
    int i;
    int n;
    int l;
    int k;
    int total2;
    int ok;

    n = g_933e;
    if (g_4ee0 && (g_4d90[g_4ed4[0]].f02 || rand() % 3 < 2))
        n += g_4ee0;
    if (g_4ee2 && g_4d90[g_4ed4[1]].f02)
        n += g_4ee2;
    for (i = 0; i < 10; i++)
        g_4f2c[i].f00 = g_4f2c[i].f02 = 0;
    k = 0;
    n = min(g_9334 / 2 + 5, 9) * n / 9;
    if (n != 0) {
        remain = n;
        for (i = 0; i < 5; i++)
            cnt1[i] = cnt2[i] = 0;
        m = g_9344 = 0;
        do {
            t112 = rand() % 6 + 3;
            t114 = 0;
            if (remain > 15 && rand() % 20 == 0)
                t112 = 16;
            if (t112 == 7)
                t112 = 4;
            t116 = rand() % 16;
            r136 = (rand() % 75 + t112 * 18 + 120) << 3;
            r13a = 0;
            rad[g_9344] = r136;
            g_4f2c[k].f04 = (int)r136;
            g_4f2c[k].f0e = rand() % ((g_9334 + 7) * 2) - g_9334 - 7;
            if (g_9334 > 2 && rand() % 3 < 2 && remain - t112 > 2 && g_9208 > 0) {
                if ((g_9208 >= 2 || t112 < 3) && g_8ff8 > 1) {
                    if (t112 == 4) {
                        if (rand() % 3 < 2) {
                            t114 = 4;
                            t118 = rand() % 2 * 2 + t116;
                            r13a = r136 * 14 / 10;
                        } else {
                            t114 = 8;
                            r13a = r136 * 185 / 100;
                            t118 = t116 + 1;
                        }
                    }
                    if (t112 == 3) {
                        r136 = r136 * 3 / 4;
                        t114 = 3;
                        t118 = (rand() & 1) == 0 ? t116 + 8 : t116;
                        r13a = r136 * 2;
                    }
                    if (t112 == 5) {
                        t114 = 5;
                        t118 = t116 + 8;
                        r13a = (r136 = max(r136 * 3 / 5, 1200)) * 223 / 100;
                    }
                    if (t114 > 0) {
                        if (rand() % 4 == 1)
                            g_4f2c[k + 1].f0e = -g_4f2c[k].f0e;
                        else
                            g_4f2c[k + 1].f0e = g_4f2c[k].f0e;
                        g_4f2c[k + 1].f04 = (int)r13a;
                        rad[g_9344] = r13a;
                    }
                }
            }
            cnt1[g_9344] = t112;
            cnt2[g_9344] = t114;
            rad[g_9344] = r13a < r136 ? r136 : r13a;
            ok = 0;
            do {
                ctr[g_9344].x = rand() % ((long)(G_05A0_LO << 3) - rad[g_9344] * 2) + rad[g_9344];
                g_240c = ctr[g_9344].x;
                ctr[g_9344].y = rand() % ((long)(G_05A0_HI << 3) - rad[g_9344] * 2) + rad[g_9344];
                g_2410 = ctr[g_9344].y;
                ok = 1;
                for (i = 0; i < g_9318; i++)
                    if (fn_08_285a(&d1, &d2, ctr[g_9344], g_1e28[i].f74) < (rad[g_9344] >> 3) + 200)
                        ok = 0;
                for (i = 0; i < g_9344; i++)
                    if (fn_08_285a(&d1, &d2, ctr[g_9344], ctr[i]) < (rad[i] + rad[g_9344] >> 3) + 200)
                        ok = 0;
            } while (!ok);
            for (i = 0; i < t112; i++) {
                ang = (int)(360L * i / t112) + t116 * 22;
                c = fn_06_71b2(ang);
                s = fn_06_720c(ang);
                pos[m].y = c * r136 / 128 + ctr[g_9344].y;
                pos[m].x = s * r136 / 128 + ctr[g_9344].x;
                dir[m] = ang % 360;
                if (pos[m].y > G_05A0_HI << 3)
                    pos[m].y -= G_05A0_HI << 3;
                else if (pos[m].y < 0)
                    pos[m].y += G_05A0_HI << 3;
                if (pos[m].x > G_05A0_LO << 3)
                    pos[m].x -= G_05A0_LO << 3;
                else if (pos[m].x < 0)
                    pos[m].x += G_05A0_LO << 3;
                m++;
            }
            g_4f2c[k].f0a = ctr[g_9344];
            k++;
            if (t114 > 0) {
                g_4f2c[k].f0a = ctr[g_9344];
                k++;
            }
            for (i = 0; i < t114; i++) {
                ang = (int)(360L * i / t114) + t118 * 22;
                c = fn_06_71b2(ang);
                s = fn_06_720c(ang);
                pos[m].y = c * r13a / 128 + ctr[g_9344].y;
                pos[m].x = s * r13a / 128 + ctr[g_9344].x;
                dir[m] = ang % 360;
                if (pos[m].y > G_05A0_HI << 3)
                    pos[m].y -= G_05A0_HI << 3;
                else if (pos[m].y < 0)
                    pos[m].y += G_05A0_HI << 3;
                if (pos[m].x > G_05A0_LO << 3)
                    pos[m].x -= G_05A0_LO << 3;
                else if (pos[m].x < 0)
                    pos[m].x += G_05A0_LO << 3;
                m++;
            }
            remain -= t114 + t112;
            g_9344++;
        } while (g_9344 < 5 && remain > 2);

        state = 1;
        sum = sub[0] = sub[1] = j = 0;
        for (i = 0; i < 5; i++)
            kind1[i] = kind2[i] = 10;
        if (g_933e != 0) {
            sum = 0;
            do {
                kind1[j] = 0;
                state = 2;
                sum += cnt1[j];
                if (sum < g_933e) {
                    if (cnt2[j] > 0) {
                        sum = sum + cnt2[j];
                        kind2[j] = 0;
                    }
                    j++;
                    state = 1;
                }
            } while (sum < g_933e && j < g_9344);
        }
        sum = sum < g_933e ? g_933e : sum;
        for (i = 0; i < 2; i++) {
            if ((&g_4ee0)[i] != 0) {
                sub[i] = 0;
                if (state == 2) {
                    if (cnt2[j] > 0) {
                        sub[i] = cnt2[j];
                        kind2[j] = i + 1;
                    }
                    j++;
                    state = 1;
                }
                if (sub[i] < (&g_4ee0)[i]) {
                    while (sub[i] < (&g_4ee0)[i] && j < g_9344) {
                        state = 2;
                        kind1[j] = i + 1;
                        sub[i] += cnt1[j];
                        if (sub[i] < (&g_4ee0)[i]) {
                            if (cnt2[j] > 0) {
                                sub[i] = sub[i] + cnt2[j];
                                kind2[j] = i + 1;
                            }
                            state = 1;
                            j++;
                        }
                    }
                    sub[i] = sub[i] < (&g_4ee0)[i] ? (&g_4ee0)[i] : sub[i];
                }
            }
        }
        for (i = 0; i < 2; i++)
            sub[i] = sub[i] < (&g_4ee0)[i] ? (&g_4ee0)[i] : sub[i];
        total = g_9318 * 2 + sub[1] + sub[0] + sum;
        if (sum > g_933e) {
            R297.fa0[2] = sum;
            g_933e = sum;
            R297.fa5[0] = sum;
        }
        for (i = 0; i < 2; i++) {
            if (sub[i] > (&g_4ee0)[i]) {
                (&g_4ee0)[i] = sub[i];
                R297.fa7[i] = sub[i];
                R297.fa0[4] = sub[1] + sub[0];
                g_9342 = R297.fa0[4];
            }
        }
        if (total > g_92fc) {
            g_92fc = g_9416 = total;
            GlobalUnlock(g_9110);
            g_9110 = GlobalReAlloc(g_9110, (long)(g_92fc < 1 ? 1 : g_92fc) * 0x70, 0x42);
            g_1df8[8] = (REC_70 far *)GlobalLock(g_9110);
        }
        k = c176 = c174 = m = cnt = 0;
        for (i = 0; i < g_9344; i++) {
            if (kind1[i] == 0) {
                g_4f2c[k].f00 = g_9318 * 2 + cnt;
                for (l = 0; l < cnt1[i]; l++) {
                    g_1df8[8][g_9318 * 2 + cnt].f04 = pos[m];
                    g_3d5a[g_9318 * 2 + cnt].f24 = dir[m] << 3;
                    m++;
                    cnt++;
                }
                g_4f2c[k].f02 = g_9318 * 2 + cnt;
                g_4f2c[k].f08 = 0;
                g_4f2c[k].f06 = i;
                k++;
            }
            if (kind2[i] == 0) {
                g_4f2c[k].f00 = g_9318 * 2 + cnt;
                for (l = 0; l < cnt2[i]; l++) {
                    g_1df8[8][g_9318 * 2 + cnt].f04 = pos[m];
                    g_3d5a[g_9318 * 2 + cnt].f24 = dir[m] << 3;
                    m++;
                    cnt++;
                }
                g_4f2c[k].f02 = g_9318 * 2 + cnt;
                g_4f2c[k].f08 = 2;
                g_4f2c[k].f06 = i;
                k++;
            }
            if (kind1[i] == 1) {
                g_4f2c[k].f00 = g_9318 * 2 + c176 + g_933e;
                for (l = 0; l < cnt1[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c176 + g_933e].f04 = pos[m];
                    g_3d5a[g_9318 * 2 + c176 + g_933e].f24 = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f02 = g_9318 * 2 + c176 + g_933e;
                if (cnt2[i] != 0 && g_9334 < 7)
                    g_4f2c[k].f08 = 1;
                else if (g_9334 < 2)
                    g_4f2c[k].f08 = 2;
                else
                    g_4f2c[k].f08 = 0;
                g_4f2c[k].f06 = i;
                k++;
            }
            if (kind2[i] == 1) {
                g_4f2c[k].f00 = g_9318 * 2 + c176 + g_933e;
                for (l = 0; l < cnt2[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c176 + g_933e].f04 = pos[m];
                    g_3d5a[g_9318 * 2 + c176 + g_933e].f24 = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f02 = g_9318 * 2 + c176 + g_933e;
                if (g_9334 < 8 || rand() % g_9334 < 4)
                    g_4f2c[k].f08 = 2;
                else
                    g_4f2c[k].f08 = 0;
                g_4f2c[k].f06 = i;
                k++;
            }
            /* sic: counts with c176 but indexes with c174 */
            if (kind1[i] == 2) {
                g_4f2c[k].f00 = g_9318 * 2 + c174 + g_933e + g_4ee0;
                for (l = 0; l < cnt1[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c174 + g_933e + g_4ee0].f04 = pos[m];
                    g_3d5a[g_9318 * 2 + c174 + g_933e + g_4ee0].f24 = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f02 = g_9318 * 2 + c174 + g_933e + g_4ee0;
                if (cnt2[i] != 0 && g_9334 < 7)
                    g_4f2c[k].f08 = 1;
                else if (g_9334 < 2)
                    g_4f2c[k].f08 = 2;
                else
                    g_4f2c[k].f08 = 0;
                g_4f2c[k].f06 = i;
                k++;
            }
            if (kind2[i] == 2) {
                g_4f2c[k].f00 = g_9318 * 2 + c174 + g_933e + g_4ee0;
                for (l = 0; l < cnt2[i]; l++) {
                    g_1df8[8][g_9318 * 2 + c174 + g_933e + g_4ee0].f04 = pos[m];
                    g_3d5a[g_9318 * 2 + c174 + g_933e + g_4ee0].f24 = dir[m] << 3;
                    m++;
                    c176++;
                }
                g_4f2c[k].f02 = g_9318 * 2 + c174 + g_933e + g_4ee0;
                if (g_9334 < 8 || rand() % g_9334 < 4)
                    g_4f2c[k].f08 = 2;
                else
                    g_4f2c[k].f08 = 0;
                g_4f2c[k].f06 = i;
                k++;
            }
        }
    }
    do {
        total2 = g_9318 * 2;
        for (i = 0; i < g_9344; i++)
            total2 += cnt2[i] + cnt1[i];
        if (total2 > 40) {
            k--;
            if (kind1[g_9344 - 1] == 0) {
                R297.fa0[2] -= cnt1[g_9344 - 1];
                R297.fa5[0] -= cnt1[g_9344 - 1];
            } else if (kind1[g_9344 - 1] == 1 || kind1[g_9344 - 1] == 2) {
                R297.fa0[4] -= cnt1[g_9344 - 1];
                if (kind1[g_9344 - 1] == 1)
                    R297.fa7[0] -= cnt1[g_9344 - 1];
                else
                    R297.fa7[1] -= cnt1[g_9344 - 1];
            }
            if (cnt2[g_9344 - 1] != 0) {
                k--;
                if (kind2[g_9344 - 1] == 0) {
                    R297.fa0[2] -= cnt2[g_9344 - 1];
                    R297.fa5[0] -= cnt2[g_9344 - 1];
                } else if (kind2[g_9344 - 1] == 1 || kind2[g_9344 - 1] == 2) {
                    R297.fa0[4] -= cnt2[g_9344 - 1];
                    if (kind2[g_9344 - 1] == 1)
                        R297.fa7[0] -= cnt2[g_9344 - 1];
                    else
                        R297.fa7[1] -= cnt2[g_9344 - 1];
                }
            }
            g_9344--;
        }
    } while (total2 > 40);
    if (g_92fc > 40) {
        int ex;

        ex = g_92fc - 40;
        if (ex < g_9342) {
            g_9342 -= ex;
            R297.fa0[4] = g_9342;
            if (ex < g_4ee2) {
                g_4ee2 -= ex;
                R297.fa7[1] = g_4ee2;
            } else {
                g_4ee0 -= ex;
                R297.fa7[0] = g_4ee0;
            }
        } else {
            g_4ee4 -= ex;
            R297.fa5[0] = g_4ee4;
            g_933e -= ex;
            R297.fa0[2] = g_933e;
        }
        g_92fc = g_9416 = 40;
    }
    for (i = 0; i < 10; i++) {
        R297.f232[i] = g_4f2c[i].f00;
        R297.f23c[i] = g_4f2c[i].f02;
        R297.f246[i] = g_4f2c[i].f04 / 80;
        R297.f250[i] = g_4f2c[i].f06;
        R297.f25a[i] = g_4f2c[i].f08;
        R297.f26f[i] = g_4f2c[i].f0a;
        R297.f265[i] = g_4f2c[i].f0e;
    }
    R297.f264 = k;
    g_9344 = k;
}

/* Race set-up block at DS:9ea2 [inferred]; a struct view, so CL reloads
 * the fields as the game does. */
typedef struct {
    int n2;                     /* 9ea2 */
    int n4;                     /* 9ea4 */
    int n6;                     /* 9ea6 */
    char p8[0x9eb4 - 0x9ea8];
    char b4;                    /* 9eb4 */
    char b5;                    /* 9eb5 */
    char t6[3];                 /* 9eb6 */
    char t9[3];                 /* 9eb9 */
    char tc[3];                 /* 9ebc */
} RACEV;
#define RACE (*(RACEV *)&g_9ea2)

/* Plans the next wave: budget, helper groups, wave type (g_9320), the
 * demon gate and race set-up, enemy mix per type (g_933a[5]) and escort
 * classes; or reloads them from the saved record [inferred]. */
/* @addr 9:3202 */
void far fn_09_3202(void)
{
    int sumcost;
    int budget;
    int r;
    int score;
    int best;
    int bestidx;
    int i;
    int j;
    int sw;
    int nfree;
    int ok;
    int ok2;
    int flag;
    int z;
    int cost[5];
    int cnt;
    int best2;
    int bestidx2;
    int k;
    int l;
    char unused[50];            /* never used; sizes the frame */

    cost[0] = 1;
    cost[1] = 1;
    cost[2] = 3;
    cost[3] = 5;
    cost[4] = 5;
    fn_09_484c();
    g_9344 = z = 0;
    g_967e = 100;
    fn_06_11ec();
    if (g_932a < g_0992)
        g_0992 = min((g_0992 - g_932a) / 2, g_932a / 4);
    else
        g_0992 = 0;
    if (g_7090[g_9646].f26[0] != 0)
        g_0992 += 50 - g_7090[g_9646].f26[0] / 2;
    if (g_9346 != -1)
        g_0992 += 100;
    g_0994 = 0;
    if (g_94b0 == 0) {
        for (i = 0; i < 4; i++)
            g_0992 += R297.fa0[i] * cost[i];
        for (i = 0; i < 2; i++)
            g_0992 += R297.fa7[i] * (g_4d90[R297.fab[i]].f05 + 3);
    }
    if (g_932a * 2 / 3 > g_0992) {
        for (k = 0; k < 2; k++) {
            best2 = 0;
            bestidx2 = -1;
            if (g_6e24 == 0)
                continue;
            if (g_0994 * 100 + g_0992 >= g_932a * 2 / 3)
                continue;
            for (i = 0; i < 8; i++) {
                j = cnt = 0;
                for (; j < 3; j++)
                    if (g_6e24[g_931c].f64 != i && g_4eec[i][j] == g_931c)
                        cnt++;
                for (l = 0; l < g_0994; l++)
                    if (g_4f1c[l] + i == 0)
                        cnt = 0;
                if (best2 <= cnt && cnt != 0 && (best2 < cnt || rand() & 1)) {
                    best2 = cnt;
                    bestidx2 = i;
                }
            }
            if (best2 > 0 && rand() % 100 < (g_91f8 - g_4fd0[bestidx2][0] - g_0994 * 3) * 10 + best2 * 35 + 25) {
                g_4f1c[g_0994] = -bestidx2;
                g_0994++;
                g_0992 += 30;
            }
        }
        best2 = 0;
        bestidx2 = -1;
        if (g_6e24 && g_0994 * 75 + g_0992 < g_932a * 2 / 3) {
            for (i = 1; i < g_931a; i++) {
                for (j = 0; j < 5; j++) {
                    if (g_6e24[i].f17[j] == g_931c && g_6e24[i].f12[j] <= 5 && g_6e24[i].f08[j] > 4
                        && g_6e24[i].f64 != g_6e24[g_9646].f64) {
                        if (g_6e24[i].f38[0] <= 0)
                            g_6e24[i].f08[j] = g_6e24[i].f17[j] = -1;
                        else if (g_6e24[i].f08[j] > best2) {
                            bestidx2 = i;
                            best2 = g_6e24[i].f08[j];
                        }
                    }
                }
            }
            if (best2 != 0 && rand() % 100 < best2 + 40) {
                g_4f1c[g_0994] = bestidx2;
                g_0994++;
                g_0992 += 30;
            }
        }
        if (g_7090[g_9646].fce > 400 && g_932a * 3 / 5 - g_0994 * 50 > g_0992) {
            int chance;

            chance = min(g_7090[g_9646].fce / 25 - g_7090[g_9646].f26[0] / 5 + (g_9334 + 10) * 2
                         - g_0992 / 5 - g_0994 * 35 + g_9000 * 3, 75);
            if (rand() % 100 < chance) {
                g_0992 += 25;
                g_4f1c[g_0994] = -100;
                g_0994++;
            }
            if (rand() % 250 < chance && g_932a * 3 / 5 - g_0994 * 45 > g_0992) {
                g_0992 += 30;
                g_4f1c[g_0994] = -100;
                g_0994++;
            }
        }
    }
    g_9320 = -1;
    if (g_9334 == 0 && g_94b0 != 0) {
        if (g_91f8 == 0) {
            g_0986[0] = g_9320 = 0;
            budget = rand() % 20 + 30;
            g_9338 = session_helper_groups = 0;
        } else if (g_0986[2] && rand() % 2 == 1) {
            g_9320 = 2;
            g_0986[2] = 0;
            budget = rand() % 20 + 20;
            g_9338 = 1;
        } else if (g_0986[4] && rand() % 2 == 1) {
            g_9320 = 4;
            g_0986[4] = 0;
            budget = rand() % 20 + 50;
            g_9338 = 0;
        } else if (g_0986[3] && rand() % 2 == 1) {
            g_9320 = 3;
            g_0986[3] = 0;
            g_9338 = rand() % 2 + 1;
            budget = rand() % ((3 - g_9338) * 10) + 20;
        } else if (g_0990 != 0) {
            g_9320 = 5;
            g_0990--;
            g_9338 = rand() % 2 + 1;
            budget = rand() % ((3 - g_9338) * 10) + 20;
        } else if (g_0986[2]) {
            g_9320 = 2;
            g_0986[2] = 0;
            budget = rand() % 15 + 25;
            g_9338 = rand() % 2 + 1;
        } else if (g_0986[4]) {
            g_9320 = 4;
            g_0986[4] = 0;
            budget = rand() % 40 + 40;
            g_9338 = 1;
        } else
            g_9334 = 1;
    }
    if (g_91f8 < 5 && g_9320 == -1) {
        g_9320 = 5;
        g_0990--;
        budget = rand() % 15 + 30;
        g_9338 = rand() % 2 + 1;
    }
    if (g_94b0 == 0 && g_9320 != 6)
        g_9320 = -1;
    if (g_9334 != 0 && g_94b0 != 0) {
        session_helper_groups = 1;
        switch (sw = rand() % 5) {
        case 1:
            g_9338 = rand() % 3;
            budget = rand() % ((6 - g_9338) * 5) + g_9334 * 4 + 9;
            if (budget > 35)
                g_9334 = g_9334 - 2 < 1 ? 1 : g_9334 - 2;
            else
                g_9334--;
            break;
        case 0:
            g_9338 = rand() % 1 + 2;
            budget = rand() % ((8 - g_9338) * 5) + g_9334 * 2 + 5;
            break;
        case 2:
            g_9338 = rand() % 2 + 2;
            budget = rand() % ((7 - g_9338) * 5) + 5;
            if (rand() & 1)
                session_helper_groups = 2;
            else
                g_9334--;
            break;
        case 3:
            budget = rand() % 25 + 10;
            g_9338 = 2;
            g_9334 += 6;
            break;
        case 4:
            g_9338 = rand() % 2 + 2;
            budget = rand() % (18 - g_9338 * 4) + (g_9334 + 4) * 3;
            g_9334++;
            break;
        }
        if (g_9332 < 2 && rand() % 6 < 4)
            session_helper_groups--;
        g_9320 = rand() % 8 - 2;
        if (g_9320 == 4) {
            budget += budget / 2;
            if (g_9338 > 2)
                g_9338--;
        }
    }
    if (g_8ff8 >= 3)
        budget = budget * g_8ff8 / 2;
    if (g_932a * 4 / 5 - 20 < g_0992)
        g_9320 = 0;
    if (g_94b0 == 0 && g_69f4[g_94a2].fad < 0 && g_38c9 == ':')
        flag = 1;
    else
        flag = 0;
    if (g_94b0 != 0 && (fn_16_5f0e(g_6990, g_8f7a) != 0 || g_91f8 - g_94ca > 4 && g_38c9 == ':')
        && g_94a6 < 25 || flag) {
        if (fn_16_5f0e(g_6990, g_8f7a) != 0
            || rand() % 100 < (g_91f8 - g_94ca - 3) * 2 + g_9334 / 2
               && g_7090[g_9646].f26[0] > 50 && g_7090[g_9646].f26[2] > 50
            || flag) {
            int kind;
            int sub;

            if (flag) {
                kind = -(R297.fad + 1);
                R297.fad = 1;
            } else
                kind = rand() % 3;
            g_9320 = 6;
            sub = rand() % 3 + 1;
            g_9ea0 = ((rand() & 1) + 1) * 5;
            if (g_9ea0 == 10 && rand() % 5 == 3)
                g_9ea0 = 1;
            g_9eb4 = 0;
            g_094e = kind * 4 + sub + 1;
            if (g_967c == 0) {
                if (g_9334 < 5 && g_9000 < 2)
                    g_94aa = 5;
                else
                    g_94aa = 4;
                goto mix;   /* gotos: layout only; the game keeps the shared
                             * escort tail inside the second branch */
            } else if (g_967c < 3) {
                if (g_9000 < 2 && g_967c == 1 && rand() % 6 < 2 && g_9334 < 5)
                    g_94aa = 5;
                if (g_9334 < 9 && g_9000 == 0)
                    g_94aa = 4;
                else if (g_9334 < 7 && g_9000 == 1 || rand() % 5 == 1)
                    g_94aa = 4;
                else if (g_9334 > 7 && g_9000 == 2 && rand() % 6 < 2) {
                    g_94aa = 1;
                mix:
                    g_94a8 = 0;
                    if (g_967c > 1 && rand() % 6 < 3 && g_94aa != 0) {
                        if (sub < 3 && g_9334 > 6 && g_967c > 3 && rand() % 6 < 4) {
                            g_94a8 = 2;
                            goto out;
                        }
                        goto one;
                    }
                    goto out;
                } else if (rand() % 6 < 3)
                    g_94aa = 2;
                else
                    g_94aa = 3;
                goto mix;
            } else if (g_967c < 4) {
                if (g_9000 == 2 && g_9334 > 7 && (rand() & 1) == 0)
                    g_94aa = 1;
                else if (g_9000 < 2 && rand() % 6 < 2 && g_9334 < 5)
                    g_94aa = 4;
                else if (rand() % 6 < 3)
                    g_94aa = 3;
                else
                    g_94aa = 2;
                goto mix;
            } else {
                if (g_967c <= 6 && g_9000 != 2 || rand() % 6 >= 3)
                    g_94aa = 1;
                else
                    g_94aa = 0;
                goto mix;
            }
        one:
            g_94a8 = 1;
        }
    }
out:
    nfree = 0;
    for (i = 0; i < 8; i++)
        if (g_1df8[0][i].f18 == 0)
            nfree++;
    if (g_9432 > 600 && g_9334 != 0 && g_9338 < 3) {
        g_9338++;
        g_9334++;
    }
    if (g_9432 > 850 && g_9334 != 0 && g_9338 < 4) {
        g_9338++;
        g_9334++;
    }
    if (nfree < 5 && g_9338 > 2) {
        g_9338--;
        if (nfree < 3 && g_9338 > 4)
            g_9338--;
    }
    budget = (g_9208 + 3) * budget * 20 / 100;
    if (g_92e8 != 0 || g_9320 == 7) {
        budget = 0;
        if (g_92e8 != 0)
            g_9320 = 0;
        g_932c = 0;
    }
    if (g_932c && g_91f8 && g_9338 < 5)
        g_9338++;
    if (g_91f8 == 1)
        session_helper_groups = g_9338 = 1;
    if (g_0994 > g_9338)
        g_9338 = g_0994;
    if (g_094e != 0) {
        g_9320 = 6;
        budget = g_932c = 0;
        g_9338 = (g_094e - 1) % 4;
        g_9322 = (g_094e - 1) / 4;
        fn_10_320a();
        g_9eb4 = 0;
        session_helper_groups = 0;
    }
    if (g_0950 != 0) {
        g_9320 = 7;
        g_9338 = (g_0950 - 1) % 4;
        session_helper_groups = 0;
        g_6678[0].f0a = 1200;
        g_6678[0].f0e = 80;
    }
    g_940e = rand() % ((g_9338 + 1) * 4);
    if (g_940e < 3)
        g_940e = 3;
    if (g_9320 == 4)
        g_940e += rand() % 15 + 9;
    if (rand() % 25 == 4 && g_9208 > 1)
        g_92f4 = g_940e = 17;
    else
        g_92f4 = g_940e;
    if (g_92e8 != 0)
        g_92f4 = g_940e = 1;
    else if (g_9320 == 6)
        g_92f4 = g_940e = g_9ebf[g_9322];
    ok = 0;
    for (i = 0; i < 5; i++)
        (&g_933a)[i] = 0;
    if (g_9320 == 3)
        g_933e = 5;
    if (g_9320 == 2)
        g_9340 = 5;
    if (g_9320 == 5)
        g_9342 = 5;
    if (g_94b0 != 0 || g_094e != 0) {
        do {
            do {
                do {
                    ok = 1;
                    r = rand() % 5;
                    if (cost[r] > g_9334 + 2)
                        ok = 0;
                    if (cost[r] > g_9334 && rand() % 5 < 3)
                        ok = 0;
                    if (g_9334 == 0)
                        ok = 1;
                    if ((r == 1 || r == 0) && g_933c + g_933a > 120) {
                        ok = 0;
                        sumcost = budget;
                    }
                } while (!ok);
                (&g_933a)[r]++;
                if ((g_9320 == 1 || g_9320 == 4) && (r == 0 || r == 1))
                    (&g_933a)[r] += 2;
                else if (g_9320 == 2 && r == 3)
                    (&g_933a)[r] += 3;
                else if (g_9320 == 3 && r == 2)
                    (&g_933a)[r] += 3;
                else if (g_9320 == 5 && r == 4)
                    (&g_933a)[r] += 3;
                else if (g_9320 == 4)
                    (&g_933a)[r]++;
                if (g_9320 == 0 && (r == 2 || r == 3 || r == 4)
                    || g_9320 != 2 && g_9320 != -1 && r == 3 && g_9334 < 3)
                    (&g_933a)[r]--;
                sumcost = 0;
                for (i = 0; i < 5; i++)
                    sumcost += cost[i] * (&g_933a)[i];
                if ((g_9338 * 2 + g_0994) * 15 + sumcost + g_0992 > g_932a * 3 / 4)
                    sumcost = budget + 1;
            } while (budget > sumcost);
            ok2 = 1;
            for (i = 0; i < 5; i++) {
                if ((&g_933a)[i] > 0 && (&g_933a)[i] < min(budget / 12, 5) && i != 1) {
                    cost[i] = 100;
                    ok2 = (&g_933a)[i] = 0;
                }
            }
        } while (!ok2);
        /* POINT views: CL zeroes each pair with one dword store [layout] */
        ((POINT *)&g_4ee0)[0].x = ((POINT *)&g_4ee0)[0].y = 0;
        ((POINT *)&g_4ee0)[1].x = ((POINT *)&g_4ee0)[1].y = 0;
        if (g_9320 == 6) {
            for (i = 0; i <= 4; i++)
                (&g_933a)[i] = 0;
            RACE.n2 = RACE.t6[g_9322];
            RACE.n4 = RACE.t9[g_9322] - RACE.t6[g_9322];
            if (g_9000 > 1 && g_94a8 > 0)
                RACE.n6 = RACE.tc[g_9322];
            else
                RACE.n6 = 0;
            RACE.b5 = -1;
            g_933e = g_9ea2 + g_9ea4;
            g_9342 = RACE.n6;
            if (g_92e0) {
                GlobalUnlock(g_92e0);
                g_3d4c = 0;
                GlobalFree(g_92e0);
                g_92e0 = 0;
            }
            g_92e0 = GlobalAlloc(0x42, ((long)g_9ea0 * g_9ea2 + 1) * (g_9338 + 1) * 4);
            g_3d4c = (DWORD far *)GlobalLock(g_92e0);
        }
        if (g_9342 != 0) {
            if (g_9342 > 5) {
                g_4ee0 = rand() % g_9342 + 1;
                g_4ee2 = g_9342 - g_4ee0;
            } else {
                g_4ee0 = g_9342;
                g_4ee2 = 0;
            }
            for (i = 0; i < 2; i++) {
                best = -1000;
                bestidx = -1;
                for (j = 1; j < 13; j++) {
                    if (g_4d90[j].f00 == 2) {
                        score = rand() % 90 + 50;
                        if (g_9334 == 0) {
                            if (g_1822[j] == 0)
                                score += 50;
                            if (g_4d90[j].f05 > 5)
                                score += -20 * g_4d90[j].f05;
                        } else if (g_4d90[j].f05 > g_9334)
                            score += (g_9334 - g_4d90[j].f05) * 35;
                        if (g_9320 == 6 && g_9f39[g_9322][g_94a8] == j)
                            score += 1000;
                        score += g_4d90[j].f07 * 5;
                        if (g_4d90[j].f03 == 5 && g_9320 == 4)
                            score += 35;
                        if (score > best) {
                            best = score;
                            bestidx = j;
                        }
                    }
                }
                g_4ed4[i] = bestidx;
                g_1822[bestidx] = 1;
            }
            if (g_4ed4[1] == g_4ed4[0]) {
                g_4ee0 += g_4ee2;
                g_4ee2 = g_4ed4[1] = 0;
            }
        }
        g_9342 = g_4ee2 + g_4ee0;
        if (g_933e != 0) {
            if (g_9320 == 6) {
                g_4ee4 = g_9ea2;
                *(&g_4ee4 + 1) = g_9ea4;
            } else if (g_933e > 5) {
                g_4ee4 = rand() % g_933e + 1;
                *(&g_4ee4 + 1) = g_933e - g_4ee4;
            } else {
                g_4ee4 = g_933e;
                *(&g_4ee4 + 1) = 0;
            }
            for (i = 0; i < 2; i++) {
                if (g_9320 == 6) {
                    g_4ee8[0] = 3;
                    g_4ee8[1] = 4;
                } else {
                    best = -1000;
                    bestidx = -1;
                    for (j = 1; j < 13; j++) {
                        if (g_4d90[j].f00 == 1) {
                            score = rand() % 50 + 40;
                            if (g_4d90[j].f05 > g_9334)
                                score += (g_9334 - g_4d90[j].f05) * 20;
                            if (g_9320 == 4 && g_4d90[j].f03 == 5)
                                score += 50;
                            if (j == 3 || j == 4)
                                score = -1500;
                            if (score > best) {
                                best = score;
                                bestidx = j;
                            }
                        }
                    }
                    g_4ee8[i] = bestidx;
                }
            }
        }
        for (i = 0; i < 5; i++)
            R297.fa0[i] = (&g_933a)[i];
        for (i = 0; i < 2; i++) {
            R297.fa7[i] = (&g_4ee0)[i];
            R297.fa9[i] = g_4ee8[i];
            R297.fa5[i] = (&g_4ee4)[i];
            R297.fab[i] = g_4ed4[i];
        }
        g_9318 = 1;
        if (g_91f8 > 1 && rand() & 1 && g_92e8 == 0 && g_9320 != 6 && g_9320 != 7) {
            g_9318++;
            if (g_91f8 > 3 && rand() % 10 == 1) {
                g_9318++;
                if (g_91f8 > 7 && rand() % 5 == 1)
                    g_9318++;
            }
        }
    } else {
        for (i = 0; i < 5; i++)
            (&g_933a)[i] = R297.fa0[i];
        for (i = 0; i < 2; i++) {
            (&g_4ee0)[i] = R297.fa7[i];
            g_4ee8[i] = R297.fa9[i];
            (&g_4ee4)[i] = R297.fa5[i];
            g_4ed4[i] = R297.fab[i];
        }
        for (i = 0; i < 10; i++) {
            if ((BYTE)R297.f232[i] > g_92fc)
                R297.f232[i] = R297.f23c[i] = 0;
            g_4f2c[i].f00 = R297.f232[i];
            g_4f2c[i].f02 = R297.f23c[i];
            g_4f2c[i].f04 = R297.f246[i] * 80;
            g_4f2c[i].f06 = R297.f250[i];
            g_4f2c[i].f08 = R297.f25a[i];
            g_4f2c[i].f0a = R297.f26f[i];
            g_4f2c[i].f0e = R297.f265[i];
        }
        g_9344 = R297.f264;
        g_9318 = R297.fad;
    }
    fn_06_72d8(5, 5);
    g_94c4 = 0;
    g_9330 = 1;
    if (g_94b0 != 0) {
        for (i = 0; i < 4; i++)
            g_0992 += cost[i] * (&g_933a)[i];
        for (i = 0; i < 2; i++)
            if ((&g_4ee0)[i])
                g_0992 += (g_4d90[g_4ed4[i]].f05 + 3) * (&g_4ee0)[i];
    }
    if (g_91f8 < 1)
        g_932e = 0;
    else
        g_932e = rand() % 3 + g_9334 / 2 - 1;
    if (g_932e < 0)
        g_932e = 0;
    if (g_9208 > 2 && g_932e > 4)
        g_932e = 4;
    else if (g_9208 == 2 && g_932e > 3)
        g_932e = 3;
    else if (g_9208 <= 1 && g_932e > 2)
        g_932e = 2;
    if (g_92e8 != 0 || g_9320 == 6)
        g_932e = 0;
    if (g_9320 != 6 && g_9320 != 7 && g_92e8 == 0) {
        if (g_9338 * -40 - g_0992 + g_932a > 50)
            g_9338 += 2 >= rand() % ((g_9338 * -40 - g_0992 + g_932a + 60) / 50)
                ? rand() % ((g_9338 * -40 - g_0992 + g_932a + 60) / 50) : 2;
        if (g_9338 > 5)
            g_9338 = 5;
        if (g_9338 * 45 + g_0992 > g_932a)
            g_9338 += (g_0992 - g_932a) / 45;
        if (g_0994 > g_9338)
            g_9338 = g_0994;
    }
}

/* Sets up a level: display scale from the INI file, object tables and the
 * per-type builders, with progress steps (fn_09_27da) [inferred]. */
/* DS:9406 and DS:92ec are int[15] per-type tables [inferred]; written as
 * arrays so CL does not sink the zero stores past them. */
#define CNT(k) ((&g_9406)[k])   /* DS:9406: int[15], per-type counts [inferred] */
/* @addr 9:22b4 */
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
            v = GetPrivateProfileInt(g_9690, "DScale", 0, g_96a9);
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
                WritePrivateProfileString(g_9690, "Size", buf2, g_96a9);
            }
        }
        if (g_92e2) {
            g_9156 = GetPrivateProfileInt(g_9690, "Size", 1, g_96a9);
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
    CNT(0) = 8;
    CNT(g_9328) = CNT(2) = CNT(1) = 0;
    g_92ea = 14;
    g_92ec[0] = 8;
    g_92ec[1] = 2;
    g_92ec[2] = g_932e * 8;
    g_92ec[g_9328] = CNT(13) = CNT(11) = CNT(10) = CNT(7) = CNT(6) = 0;
    g_92ec[7] = g_92ec[6] = 1;
    g_92ec[11] = g_92ec[10] = 3;
    g_92ec[13] = 0;
    g_92ec[3] = CNT(3) = g_933c + g_933a;
    g_92ec[8] = CNT(8) = g_933e + g_9342;
    g_92ec[9] = CNT(9) = g_9340;
    g_92ea = g_933a;
    if (CNT(3) > 127) {
        CNT(3) = 120;
        g_92ec[3] = 920;
        g_933c = g_933a = 60;
    }
    CNT(8) += g_9318 * 2;
    g_92ec[12] = CNT(12) = g_9318 * 2;
    g_92ec[8] += g_9318 * 2;
    if (g_92ec[8] > 80)
        g_92ec[8] = CNT(8) = 80;
    if (g_92e8) {
        g_9326 = 1;
        g_9338 = session_helper_groups = CNT(3) = 0;
    }
    if (g_9320 == 6) {
        CNT(3) = 0;
        CNT(2) = 0;
        g_92ec[2] = 0;
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
