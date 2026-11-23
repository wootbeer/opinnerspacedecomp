/* INSPACE.EXE segment 4 (selector 1018). */
#include <stdlib.h>
#include "inspace.h"

/* g_05a0 is declared long in inspace.h; this code reads its two words
 * separately (world width and height [inferred]). */
#define G_05A0_LO (((int *)&g_05a0)[0])
#define G_05A0_HI (((int *)&g_05a0)[1])

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    POINT f00;                  /* +00 */
    POINT f04;                  /* +04: position [inferred] */
    char p08[0x0c - 0x08];
    int f0c;                    /* +0c */
    int f0e;                    /* +0e */
    char p10[0x18 - 0x10];
    int f18;                    /* +18 */
    int f1a;                    /* +1a */
    char p1c[0x20 - 0x1c];
    int f20;                    /* +20 */
    int f22;                    /* +22: size [inferred] */
    char p24[0x26 - 0x24];
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    char p2a[0x2e - 0x2a];
    char f2e;                   /* +2e */
    char f2f;                   /* +2f */
    char p30[0x32 - 0x30];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    char p38[0x44 - 0x38];
    int f44;                    /* +44 */
    char p46[0x51 - 0x46];
    char f51;                   /* +51 */
    char f52;                   /* +52 */
    char f53;                   /* +53 */
    char f54;                   /* +54 */
    char p55[0x70 - 0x55];
} REC_70;

/* 0x15a-byte records at DS:7090, indexed like the object records
 * [inferred]. */
typedef struct {
    int f00;                    /* +00: countdown [inferred] */
    char p002[0x06 - 0x02];
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    char p00a[0x10 - 0x0a];
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    int f14;                    /* +14 */
    int f16;                    /* +16 */
    int f18;                    /* +18 */
    char p01a[0x1e - 0x1a];
    int f1e;                    /* +1e */
    char p020[0x26 - 0x20];
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    int f2a;                    /* +2a */
    char p02c[0x30 - 0x2c];
    int f30;                    /* +30 */
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    int f3a;                    /* +3a */
    int f3c;                    /* +3c */
    char p03e[0x44 - 0x3e];
    int f44[5];                 /* +44: history [inferred] */
    int f4e;                    /* +4e */
    char p050[0x52 - 0x50];
    int f52;                    /* +52 */
    int f54;                    /* +54 */
    int f56;                    /* +56 */
    int f58;                    /* +58 */
    char p05a[0x5d - 0x5a];
    char f5d;                   /* +5d */
    char f5e;                   /* +5e */
    char f5f;                   /* +5f */
    char p060;
    char f61;                   /* +61 */
    char p062[0x72 - 0x62];
    int f72[8];                 /* +72, indexed by object [inferred] */
    char p082[0x88 - 0x82];
    DWORD f88;                  /* +88: time stamp [inferred] */
    char p08c[0x94 - 0x8c];
    long f94;                   /* +94 */
    long f98;                   /* +98 */
    DWORD f9c;                  /* +9c: time stamp [inferred] */
    char p0a0[0xa4 - 0xa0];
    DWORD fa4;                  /* +a4 */
    DWORD fa8;                  /* +a8 */
    char fac;                   /* +ac */
    char p0ad;
    char fae[10];               /* +ae, indexed by slot [inferred] */
    char fb8[10];               /* +b8, indexed by slot [inferred] */
    char fc2[8];                /* +c2, indexed by object [inferred] */
    char fca;                   /* +ca */
    char fcb;                   /* +cb: slot count [inferred] */
    char fcc;                   /* +cc */
    char fcd;                   /* +cd */
    int fce;                    /* +ce */
    char p0d0[0xd4 - 0xd0];
    int fd4;                    /* +d4 */
    int fd6;                    /* +d6 */
    int fd8;                    /* +d8 */
    int fda;                    /* +da */
    long fdc;                   /* +dc */
    char p0e0[0xe2 - 0xe0];
    char fe2;                   /* +e2 */
    char p0e3[0xe7 - 0xe3];
    char fe7;                   /* +e7 */
    char fe8;                   /* +e8 */
    char fe9;                   /* +e9 */
    char p0ea[0xec - 0xea];
    char fec;                   /* +ec */
    char fed;                   /* +ed */
    char fee[8];                /* +ee, indexed by object [inferred] */
    char p0f6;
    char ff7[7][9];             /* +f7, indexed by object [inferred] */
    char p136[0x13e - 0x136];
    char f13e[8];               /* +13e, indexed by object [inferred] */
    char f146;                  /* +146 */
    char p147;
    char f148;                  /* +148 */
    char f149;                  /* +149 */
    POINT f14a;                 /* +14a */
    char p14e[0x15a - 0x14e];
} REC_15A;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;                    /* +00 */
    char p02[0x1a - 0x02];
    int f1a;                    /* +1a */
    char p1c[0xad - 0x1c];
} REC_AD;
#pragma pack()

typedef struct {                /* 0x1c bytes, DGROUP array at DS:66e8 */
    int f00;                    /* +00 */
    int f02;                    /* +02 */
    char p04[0x08 - 0x04];
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    char p0e[0x1c - 0x0e];
} REC_1C;

typedef struct {                /* 0x24 bytes, DGROUP array at DS:52fe */
    int f00;                    /* +00 */
    char p02[0x0a - 0x02];
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    char p0e[0x24 - 0x0e];
} REC_24;

typedef struct {                /* 0x50 bytes, DGROUP array at DS:2f58 */
    int f00;                    /* +00 */
    char p02[0x06 - 0x02];
    int f06;                    /* +06 */
    char p08[0x24 - 0x08];
    int f24;                    /* +24 */
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    int f2a;                    /* +2a */
    char p2c[0x3e - 0x2c];
    int f3e;                    /* +3e */
    char p40[0x42 - 0x40];
    int f42;                    /* +42 */
    char p44[0x50 - 0x44];
} REC_50;

extern REC_50 g_2f58[];
extern REC_1C g_66e8[];
extern REC_70 far *g_1df8[16];
extern DWORD g_1e50;
extern DWORD g_1d06;
extern DWORD g_1e68;
extern DWORD g_8e28;
extern int g_9000;
extern long g_1e58;
extern long g_5078;
extern int g_9318;
extern int g_91fc;
extern int g_94a8;
extern int g_94aa;
extern int g_967c;
extern int g_9684;
extern int g_9ea4;
extern char g_9eb5;
extern int g_9134;
extern int g_9334;
extern int g_9524;
extern int g_967e;
extern REC_AD g_96f0[];
extern int g_238c;
extern REC_15A g_7090[];
extern int g_9316;
extern int g_9646;
extern int g_9ea0;                  /* after g_9646: load order in 4:277a */
extern int g_8e48[];
extern int g_9ea2;
extern int flow_interactive;        /* DS:95bc */
extern unsigned long g_9e60[];
extern long g_8e00;
extern long g_8e04;
extern int g_9680;
extern int g_9682;

void far fn_03_06ec(int a, int b, int n, int id);
void far fn_07_1208(void);
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
void far fn_10_744c(int a);
void far race_radar_background(int a);
void far fn_12_3e98(int i);
int far fn_04_6a78(int n, int i);
int far fn_13_2688(int n, int m);
int far pascal fn_13_1076(int type, int n);   /* pascal (retf 4) */
void far pascal fn_11_7c12(int k, int type, int n);
void far fn_11_8a42(int type, int n);
void far fn_11_9078(int type, int n);
void far fn_11_947a(int type, int n, int k);
void far fn_11_9daa(int type, int n);
void far fn_11_9fdc(int type, int n);
void far fn_11_2f8c(void);
void far pascal fn_13_1318(int type, int n, int t, int k);
void far fn_13_4eec(int i, int d);
void far fn_13_9a18(int n, int x, int y);
POINT far pascal fn_08_29ea(POINT pt);
int far pascal fn_08_19b0(int dx, int dy);
void far pascal fn_03_332e(int a, int b);
int far fn_11_4c72(int n);
int far fn_11_4b00(int n);
void far pascal fn_04_584c(int s, int n, int t);
void far fn_04_6e70(int n);
extern REC_24 g_52fe[];
extern int g_92e8;
extern int g_940a;
extern int g_940e;
extern int g_9208;
extern int g_9320;
int far fn_16_0b4e(int n);
void far fn_03_1542(int a, int b, int n, LPSTR buf, int c);
extern char g_8630[];               /* run-time buffer (BSS) */
extern int g_058c;
extern long g_05c0;
typedef struct {                /* 0x7c bytes, far array at DS:6e24 */
    int f00;                    /* +00 */
    char p02[0x7c - 0x02];
} REC_7C;
extern REC_7C far *g_6e24;
extern long g_2384;
extern int g_6b40[];
extern int g_9346;
extern long g_a147;
extern int g_a14b;
extern char g_a14d[];
extern char g_a157[];
extern int g_91f8;
extern int g_4eec[][3];
extern int g_4fd0[][3];
extern int g_6b10[][3];
extern int g_4ed8[];
extern int g_940c;
extern int g_9416;
int far fn_09_88ba(int v);
extern DWORD g_52d8;
extern DWORD g_8e44;
extern char g_507c[];
extern char g_50e0[];
extern int g_9146;
extern int g_9686;
extern int g_9412;
extern int g_9418;
int far fn_13_371c(int type, int n);
void far fn_12_2288(int type, int n);
/* DS:66e4: a word 4 bytes before each g_66e8 record [inferred] */
#define G_66E4(i) (((int *)&g_66e8[i])[-2])
extern int g_9688;
extern int g_968a;
void far fn_13_7b40(int n);
int far fn_04_8626(int type, int idx, int flag);
int far fn_13_78b8(int n, int m);
int far fn_04_8346(int n, int x, int y, int v);
typedef struct { int f00; char p02[0x12 - 0x02]; int f12; char p14[0x34 - 0x14]; } REC_34;
extern REC_34 g_3d5a[];             /* base as in seg07.c */
extern REC_70 far *g_1e30;
extern int g_937a[8];
extern char g_938a[8];
extern char g_9392[8];
extern int g_6e52;
extern int g_6e54;
int far fn_06_720c(int deg);
int far fn_08_35d0(long a, long b);
extern int g_913a;
extern int g_913c;
extern DWORD g_8e2c;
extern DWORD g_1d0a;
extern DWORD g_1d0e;
extern DWORD g_1d12;
extern int g_0992;
extern int g_932a;
extern int g_964a;
extern int g_9648;
extern int g_3824[8][8];            /* per-class tables, row by kind [inferred] */
int far fn_13_adbe(int a, int b, int c);    /* summon_with_music [inferred] */
typedef struct { char p00[0x0a]; char name[0x41 - 0x0a]; } REC_41;
extern REC_41 far *g_6e20;
extern int g_934e;
extern char g_380c[];               /* run-time buffer (BSS) */
extern char g_8d38[];               /* run-time buffer (BSS) */
extern char g_09d6[];
int far fn_14_3eda(void);
void far fn_14_4074(void);
void far fn_03_00f4(int n, int type, int k);
void far fn_10_a332(LPSTR buf, int id, int n, ...);

extern long g_240c;
extern long g_2410;
extern int g_90ea;
extern int g_90ec;
extern int g_9150;
extern int g_9156;
extern POINT g_1cea;
extern POINT g_1cee;
extern POINT g_1cf2;
extern long g_1d02;
extern DWORD far *g_3d4c;
extern long g_8e08[];
extern DWORD g_9e70[];
extern DWORD g_9e80[];
extern DWORD g_9e90[];
extern POINT g_9ea8[];
extern int g_9322;


void far fn_13_2714(int a, int b, int c, int d, int e, int f);
void far fn_13_b6f2(int a, int t);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_13_915c(int n);
extern char g_a152;
extern char g_a15c;
extern char g_a163;
extern int g_9432;
/* word 0x0e bytes below each class record [inferred] */
#define AD_M0E(k) (((int *)&g_96f0[k])[-7])

extern int g_952e;
extern int g_9e49;
extern int g_1cb8[];
extern int g_8e3c[];
extern int g_932e;
int far pascal steer_toward_direction(int y2, int x2, int y1, int x1, int cur,
                                      int mode, int obj, int a, int b, int c);
void far pascal fn_11_5ab6(int n, int k);
void far fn_13_6716(int n);
void far fn_13_16ac(int n, int ref);
void far pascal fn_04_4fc8(int n);
extern DWORD g_8690;
extern DWORD g_8e30;
extern int g_8680[];
extern int g_0a62;
void far pascal fn_13_6900(int n);
void far fn_13_7ba2(int n);
int far fn_03_0000(int type, int n);
void far fn_13_a65a(void);
void far fn_13_3678(int n);
void far pascal fn_11_4e0a(int n);
void far pascal fn_04_2f98(int n, int k);
int far pascal fn_04_5654(int n);
void far pascal fn_04_4d00(int n);
void far fn_04_79ae(int n);
void far pascal fn_04_485c(int n, int unused);
extern int g_9406[];
extern int g_8e34[];
extern char g_9eb4;
extern long g_1cca[];
extern int g_9348;
extern char g_9ebc[];
extern char g_9eb9[];         /* after g_9ebc: load order in 4:144c */
extern char g_9ebf[];
extern char g_9ec2[][40];
extern POINT g_1050[];


/* @addr 4:0000 */
void far pascal fn_04_0000(int n)
{
    if (g_1df8[14][n].f26 && g_238c == 0)
        fn_07_1208();
    if (g_7090[n].f12) {
        g_1df8[14][n].f28 += g_7090[n].f12;
        if (g_1df8[14][n].f28 > 15)
            g_1df8[14][n].f28 = 0;
        if (g_1df8[14][n].f28 < 0)
            g_1df8[14][n].f28 = 15;
        fn_07_1208();
    }
}

/* @addr 4:2da2 */
void far fn_04_2da2(void)
{
    int v;
    int i;

    g_9eb5 = 1;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f18 != 0)
            continue;
        if (g_7090[i].fda < 0)
            v = -1 - g_7090[i].fda;
        else
            v = g_7090[i].fda;
        if (v < g_9ea0)
            g_9eb5 = 0;
    }
    if (g_7090[g_9646].fda - g_9ea0 == 1)
        g_9eb5 = 1;
    else {
        if (g_9684 == 1) {
            fn_10_744c(0x74);
            if (g_91fc) {
                fn_03_06ec(g_9646, 7, 0, 0xba);
                g_967c++;
            }
        } else {
            fn_10_744c(0x42);
            if (g_91fc)
                fn_03_06ec(g_9646, 7, 0, 0xbb);
        }
        g_9e60[g_9646] = g_1e68 - g_9e60[g_9646];
        if (g_91fc)
            g_9eb5 = 1;
        if (g_9684 == 1 && g_9316 != 0) {
            g_5078 += ((9 - g_94aa) * g_9316 + (g_94a8 + 5) * 4) * 500;
            g_1e58 += ((9 - g_94aa) * g_9316 + (g_94a8 + 5) * 4) * 500;
        } else if (g_9684 == 2 && g_9316 > 1) {
            g_5078 += (g_94a8 + 8) * 500 + (8 - g_94aa) * g_9316 * 200;
            g_1e58 += (g_94a8 + 8) * 500 + (8 - g_94aa) * g_9316 * 200;
        }
    }
    if (g_9eb5) {
        fn_10_744c(20);
        race_radar_background(0);
        for (i = g_9318 * 2; i < g_9318 * 2 + g_9ea2 + g_9ea4; i++)
            fn_12_3e98(i);
        for (i = 0; i <= g_9316; i++) {
            g_7090[i].f148 = -2;
            g_7090[i].f32 = 12;
            g_7090[i].f34 = 0;
            g_7090[i].f3c = g_7090[i].f38 = 2;
            if (g_1df8[14][i].f51 == 0)
                g_1df8[14][i].f51 = 1;
        }
    }
    g_1df8[14][g_9646].f51 = 2;
}

/* Per-frame order and target update for racer n [inferred]. */
/* @addr 4:0078 */
void far pascal fn_04_0078(int n)
{
    int u04;
    int r;
    int hd;
    int i;
    int u0c;
    int a;
    int b;
    int dist;
    char pad14[14];             /* frame filler [inferred] */
    POINT pos;
    char pad26[0x18];
    int type;
    int idx;
    char pad42[8];
    int flag;

    if (g_9320 == 6 && g_9eb5 == 0)
        return;
    g_7090[n].f61 = 0;
    if (g_96f0[g_7090[n].f4e].f1a == 7 && g_7090[n].f32 == 14
        && g_96f0[g_7090[g_7090[n].f34].f4e].f1a == 7) {
        g_7090[n].f34 = 0;
        g_7090[n].f32 = 0;
        g_7090[n].f94 = 0;
        g_7090[n].f52 = g_7090[n].f54 = g_7090[n].f56 = 0;
    }
    if (g_7090[n].f32 == 14 && g_7090[g_7090[n].f34].fec == 0)
        g_7090[n].f94 = 0;
    if (g_9134 >= 2 && n == g_9646 && g_8690 < g_1e50 && g_7090[g_9646].f26 < 40)
        g_7090[g_9646].f94 = 0;
    if (g_7090[n].f38 == 1 && g_7090[n].f32 == 14 && g_8680[g_7090[n].f34] == n
        && g_96f0[g_7090[n].f4e].f1a != 7) {
        g_7090[n].f52 = 0;
        g_7090[n].f94 = 0;
    }
    if (g_92e8 != 0) {
        if (g_1e30[g_9646].f54 == 0 && g_7090[n].f26 < 60) {
            fn_03_06ec(g_9646, 14, 1, 0xb7);
            g_7090[1].f32 = 12;
            g_7090[1].f38 = 2;
            g_7090[1].f34 = 0;
            g_7090[1].f52 = 0;
        } else if (g_1e30[g_9646].f54 != 0 && g_7090[1].f1e == 0) {
            if (g_8e30 < g_1e50) {
                g_1e30[g_9646].f54 = 0;
                g_7090[1].f1e = g_96f0[g_7090[1].f4e].f00;
                fn_03_06ec(g_9646, 14, 1, 0xb7);
                g_7090[1].f32 = 12;
                g_7090[1].f38 = 2;
                g_7090[1].f34 = 0;
                g_7090[1].f52 = 0;
            }
            if (g_8e30 - 13000 < g_1e50 && g_7090[1].f00 == 0) {
                fn_03_06ec(g_9646, 14, 1, 0xb6);
                g_7090[1].f00 = 1;
            }
        }
    }
    if (g_9320 == 7 && (!flow_interactive || n != g_9646)
        && (g_7090[n].f52 != 4 || g_7090[n].f32 != 14)
        && (g_7090[n].f32 != 4 || g_1df8[g_7090[n].f32][g_7090[n].f34].f18 != 0)) {
        g_7090[n].f52 = 4;
        if (g_1df8[g_7090[n].f54][g_7090[n].f56].f18 == 1 && n == g_9646) {
            for (i = 0; i <= g_9316; i++)
                if (i != n && g_1e30[i].f18 != 1 && g_7090[i].fec != 0) {
                    g_7090[n].f56 = i;
                    break;
                }
            if (i == g_9316 + 1 && g_7090[n].f32 != 12) {
                if (g_7090[n].f32 != 12)        /* sic: tested twice */
                    fn_03_06ec(g_9646, 14, n, 0xb7);
                g_7090[n].f32 = 12;
                g_7090[n].f34 = 0;
                g_7090[n].f38 = 2;
                g_7090[n].f52 = 0;
            }
        } else {
            g_7090[n].f32 = g_7090[n].f54;
            g_7090[n].f34 = g_7090[n].f56;
            g_7090[n].f38 = 1;
            g_7090[n].f3c = 2;
        }
    }
    if (g_9320 == 6 && g_7090[n].f32 != 12 && g_96f0[g_7090[n].f4e].f1a != 7)
        g_7090[n].f94 = g_1e50;
    if (g_7090[n].f94 < g_1e50 || g_1df8[g_7090[n].f32][g_7090[n].f34].f18 != 0) {
        if (g_1df8[g_7090[n].f32][g_7090[n].f34].f18 != 0 && g_7090[n].f52 != 0
            && g_7090[n].f52 != 7 && g_7090[n].f54 != -1
            && g_1df8[g_7090[n].f54][g_7090[n].f56].f18 != 0) {
            if (g_9320 == 7) {
                if (g_1df8[g_7090[n].f32][g_7090[n].f34].f18 != 1)
                    goto skip;
                for (i = 0; i <= g_9316; i++)
                    if (i != n && g_1e30[i].f18 != 1) {
                        g_7090[n].f56 = i;
                        break;
                    }
                if (i != g_9316 + 1)
                    goto skip;
            }
            g_7090[n].f52 = 0;
        }
    skip:
        if (n == g_9646 && g_9134 >= 2) {
            switch (g_9134) {
            case 2:
                g_9134 = 0;
                flow_interactive = 1;
                break;
            case 3:
                g_9134 = 1;
                flow_interactive = 1;
                break;
            case 4:
                g_9134 = 1;
                break;
            }
            g_8690 = 0;
            fn_03_06ec(g_9646, 7, 0, 0xa4);
        }
        if (fn_04_702e(n) == 0
            && (!fn_13_371c(g_7090[n].f32, g_7090[n].f34) || g_7090[n].f3c != 2
                || g_7090[n].f38 != 2 || (n == g_9646 && flow_interactive)
                || g_96f0[g_7090[n].f4e].f1a == 7)) {
            fn_13_7ba2(n);
            if (g_7090[n].f9c == 1)
                g_7090[n].f9c = g_1e50 + 5000;
            if (g_7090[n].f38 != 4 && (g_9320 != 6 || g_96f0[g_7090[n].f4e].f1a == 7)) {
                if (g_7090[n].f52 < 1 && (n != g_9646 || g_9134 == 0 || !flow_interactive)) {
                    g_7090[n].fed = 0;
                    if (g_7090[n].f36 != 4)
                        fn_04_2f98(n, 1);
                    fn_04_485c(n, -1);
                } else
                    fn_13_6900(n);
                if (g_7090[n].f06 < 0) {
                    g_7090[n].f08 = 0;
                    g_7090[n].f06 = 0;
                }
                if (n == g_9646 && !flow_interactive
                    && fn_03_0000(g_7090[n].f06, g_7090[n].f08)) {
                    g_0a62 = 1;
                    fn_03_00f4(n, g_7090[n].f06, g_7090[n].f08);
                }
                if (g_9320 != 6) {
                    if (((g_7090[n].f52 != 3 && g_7090[n].f52 != 4) || g_9320 == 7)
                        && (n != g_9646 || g_9134 == 0 || !flow_interactive))
                        fn_04_4d00(n);
                    else
                        fn_13_a65a();
                }
                if (g_7090[n].f06 != g_7090[n].f32 || g_7090[n].f08 != g_7090[n].f34
                    || g_7090[n].f36 != g_7090[n].f38 || g_7090[n].f3a != g_7090[n].f3c) {
                    g_7090[n].fa4 = g_7090[n].fa8 = g_1e50;
                    g_7090[n].f32 = g_7090[n].f06;
                    g_7090[n].f34 = g_7090[n].f08;
                    g_7090[n].f38 = g_7090[n].f36;
                    g_7090[n].f3c = g_7090[n].f3a;
                }
            }
            if (g_96f0[g_7090[n].f4e].f1a == 7 && g_7090[n].f52 < 20
                && g_7090[n].f32 != 11 && g_7090[n].f32 != 12 && g_7090[n].f32 != 4) {
                g_7090[n].f52 = 22;
                if (g_7090[n].fcd >= 0 && g_7090[n].f5e < 2) {
                    if (g_7090[g_7090[n].fcd].fec == 0) {
                        fn_03_06ec(g_9646, 14, n, 0xb7);
                        g_7090[n].f06 = 12;
                        g_7090[n].f08 = 0;
                        g_7090[n].f36 = 2;
                        g_7090[n].f3a = 2;
                    } else {
                        g_7090[n].f54 = 14;
                        g_7090[n].f56 = g_7090[n].fcd;
                    }
                } else if (g_7090[n].f32 == 14 || g_7090[n].f5e == 0) {
                    g_7090[n].f54 = 14;
                    g_7090[n].f56 = g_7090[n].f34;
                    if (g_7090[n].f5e == 0)
                        g_7090[n].f52 = 23;
                } else if (g_7090[n].f54 == 14) {
                    if (g_7090[n].f5e == 0)
                        g_7090[n].f52 = 23;
                    else if (g_7090[n].f5e == 1)
                        g_7090[n].f52 = 22;
                    else
                        g_7090[n].f52 = 20;
                } else
                    g_7090[n].f52 = 20;
                g_7090[n].fed = 2;
                g_7090[n].f58 = n;
                g_7090[n].f94 = g_1e50;
                g_7090[n].f38 = 3;
                fn_13_6900(n);
            }
        } else {
            if (fn_13_371c(g_7090[n].f32, g_7090[n].f34) == 2)
                fn_13_3678(n);
            fn_03_00f4(n, g_7090[n].f32, g_7090[n].f34);
            g_7090[n].f94 = g_1e50 + 3000;
        }
        fn_04_79ae(n);
    }
    g_7090[n].f30++;
    if (g_9134 != 2)
        fn_04_4fc8(n);
    type = g_7090[n].f06;
    idx = g_7090[n].f08;
    if (type == 14 && g_7090[idx].fe8 && g_92e8 == 0)
        pos = g_7090[idx].f14a;
    else
        pos = g_1df8[type][idx].f04;
    dist = fn_08_285a(&a, &b, g_1e30[n].f04, pos);
    if (g_7090[n].f38 == 4) {
        if (dist < 400 && type == 14 && g_7090[n].f32 == type && g_7090[n].f34 == idx
            && (n != g_952e || g_9e49 < 1 || g_9e49 > 6)) {
            if (g_7090[n].fca <= 0)
                fn_04_5654(n);
            g_7090[n].fca += 4 - g_9208;
            if (dist < 100)
                fn_11_5ab6(n, 2);
        }
        g_7090[n].f61 = 1;
        g_7090[n].f3a = 5;
    }
    hd = g_1e30[n].f28;
    if (n == g_952e && g_9e49 >= 1 && g_9e49 <= 6)
        return;
    if (g_7090[n].f5f == 2 && g_7090[n].f38 != 4) {
        if (g_7090[n].f38 == 1) {
            if (dist < 160) {
                flag = 1;
                for (i = 0; i < g_9412; i++)
                    if (g_1df8[6][i].f18 == 0 && g_66e8[i].f00 == 14 && g_66e8[i].f02 == n)
                        flag = 0;
                if (flag) {
                    g_7090[n].f3a = 5;
                    g_7090[n].f3c = 5;
                    g_7090[n].fca = 0;
                } else {
                    g_7090[n].f3a = 2;
                    g_7090[n].f3c = 2;
                }
            } else if (dist > 210) {
                g_7090[n].f3a = 2;
                g_7090[n].f3c = 2;
            } else if (g_7090[n].f3c == 5)
                g_7090[n].f3a = 5;
        } else
            g_7090[n].f5f = 0;
    }
    g_7090[n].fca = g_7090[n].fca - 1 < 0 ? 0 : g_7090[n].fca - 1;
    g_7090[n].fcc = g_7090[n].fcc - 1 < 0 ? 0 : g_7090[n].fcc - 1;
    g_7090[n].fd4 = g_7090[n].fd4 - 1 < 0 ? 0 : g_7090[n].fd4 - 1;
    if (g_7090[n].f36 == 1) {
        if (dist < 400 && (g_9208 > 1 || g_1e30[n].f1a != 0)) {
            if (n != g_9646 && g_7090[n].fa4 + 19000 < g_1e50
                && (g_7090[n].f52 == 0
                    || (g_7090[n].f98 < g_1e50 && g_7090[n].f52 != 4
                        && g_7090[n].f52 != 1 && g_7090[n].f52 != 23))) {
                if (g_7090[n].f32 == 14)
                    g_7090[n].fc2[g_7090[n].f34] = -1;
                g_7090[n].f94 = 0;
                g_7090[n].f52 = -1;
                fn_04_2f98(n, 1);
                g_7090[n].fa4 = g_7090[n].fa8 = g_1e50;
                g_7090[n].f32 = g_7090[n].f06;
                g_7090[n].f34 = g_7090[n].f08;
                g_7090[n].f38 = g_7090[n].f36;
                g_7090[n].f3c = g_7090[n].f3a;
            }
            r = 0;
            if (g_7090[n].fca <= 0 && g_1e30[n].f1a != 0)
                r = fn_04_5654(n);
            if (g_7090[n].f3a == 2 && r == 0 && g_7090[n].fcc <= 0
                && (type != 0 || g_7090[n].fb8[g_7090[n].f18] != 5))
                fn_11_4e0a(n);
        } else if (g_7090[n].f1e > 150 && dist > 700) {
            fn_11_5ab6(n, 2);
            g_7090[n].f61 = 1;
        }
    }
}

/* Current waypoint record of racer n [inferred]. */
#define RACE_WP(n) g_1df8[8][g_7090[n].f148 + g_9318 * 2]

/* Race AI: steer racer n along the track's waypoints [inferred]. */
/* @addr 4:144c */
void far fn_04_144c(int n, int flag)
{
    POINT pos;
    POINT d1;
    POINT wp;
    POINT vel;
    POINT next;
    POINT prev;
    POINT d2;
    long unused;                /* never used; keeps the frame size */
    long dist2;
    long spd;
    long dist;
    long r1;
    long r3;
    long r2;
    int i;
    int turn;

    if (g_7090[n].f148 < 0) {
        if (g_7090[n].f148 == -2) {
            if (g_7090[n].f32 == 0) {
                if (g_1df8[0][g_7090[n].f34].f18) {
                    for (i = 0; i < g_9406[0]; i++)
                        if (g_1df8[0][i].f18 == 0) {
                            g_7090[n].f34 = i;
                            break;
                        }
                    if (g_1df8[0][g_7090[n].f34].f18) {
                        g_7090[n].f32 = 12;
                        g_7090[n].f34 = 0;
                    }
                }
            } else {
                g_7090[n].f32 = 12;
                g_7090[n].f34 = 0;
            }
            g_7090[n].f38 = 2;
            g_7090[n].f3c = 2;
            return;
        }
        g_7090[n].f148 = 0;
        g_7090[n].fda = 0;
    }
    pos = fn_08_29ea(g_1df8[14][n].f04);
    pos.x += g_1df8[14][n].f22 / 2;
    pos.y += g_1df8[14][n].f22 / 2;
    if (g_8e34[n] != -1)
        wp = fn_08_29ea(g_1df8[4][g_8e34[n]].f04);
    else
        wp = fn_08_29ea(RACE_WP(n).f04);
    wp.x += 7 << g_9156;
    wp.y += 7 << g_9156;
    if (g_7090[n].f148 < g_9ea2 - 1)
        next = fn_08_29ea(g_1df8[8][g_7090[n].f148 + g_9318 * 2 + 1].f04);
    else
        next = fn_08_29ea(g_1df8[8][g_9318 * 2].f04);
    if (g_7090[n].f148 > 0)
        prev = fn_08_29ea(g_1df8[8][g_7090[n].f148 + g_9318 * 2 - 1].f04);
    else
        prev = fn_08_29ea(g_1df8[8][g_9318 * 2 + g_9ea2 - 1].f04);
    vel = *(POINT far *)&g_1df8[14][n].f0c;
    g_8e48[n] = dist = fn_08_35d0(d1.x = (pos.x - wp.x) * 2 >> g_9156,
                                  d1.y = (pos.y - wp.y) * 2 >> g_9156);
    spd = fn_08_35d0(vel.x, vel.y);
    r1 = -((((long)vel.x * d1.x + (long)vel.y * d1.y) << 7) / (dist * spd));
    r2 = (((long)vel.y * d1.x - (long)vel.x * d1.y) << 7) / (dist * spd);
    turn = 0;
    if (flag) {
        if (g_9eb4) {
            if (!RACE_WP(n).f52 && r2 < 0 || RACE_WP(n).f52 && r2 > 0) {
                /* both arms equal: CL drops the test but keeps the
                 * operand's (dead) computation, as the game does */
                if (dist < (spd + 250) * 2)
                    turn = 2;
                else
                    turn = 2;
                if (!RACE_WP(n).f52 && r2 < -35 || RACE_WP(n).f52 && r2 > 35)
                    turn = 3;
                if ((!RACE_WP(n).f52 && dist / -7 + 5 > r2 || RACE_WP(n).f52 && dist / 7 - 5 < r2)
                    && dist < 400) {
                    turn = 4;
                    g_1df8[14][n].f0c = g_1df8[14][n].f0c * 5 / 6;
                    g_1df8[14][n].f0e = g_1df8[14][n].f0e * 5 / 6;
                }
            } else {
                turn = 0;
                if ((!RACE_WP(n).f52 && 1000 / dist + g_8e3c[n] * 6 + 14 > r2
                     || RACE_WP(n).f52 && -1000 / dist - g_8e3c[n] * 6 - 14 < r2) && dist < 800)
                    turn = 2;
                else if ((!RACE_WP(n).f52 && g_8e3c[n] * 6 + 40 > r2
                          || RACE_WP(n).f52 && -40 - g_8e3c[n] * 6 < r2) && dist < 1000)
                    turn = 1;
                if ((!RACE_WP(n).f52 && g_8e3c[n] * 6 + 52 < r2
                     || RACE_WP(n).f52 && -52 - g_8e3c[n] * 6 > r2) && dist > 70)
                    turn = -1;
                if ((!RACE_WP(n).f52 && g_8e3c[n] * 6 + 65 < r2
                     || RACE_WP(n).f52 && -65 - g_8e3c[n] * 6 > r2) && dist > 70)
                    turn = -2;
            }
        }
        if (dist / 4 - g_8e3c[n] * 7 + 80 < r1 && 140 - spd / 2 > dist && g_8e34[n] == -1) {
            if (RACE_WP(n).f52)
                g_7090[n].f3c = 3;
            else
                g_7090[n].f3c = 4;
            g_7090[n].f149 = 0;
        } else {
            if (turn) {             /* f3c in both arms: shared tail */
                g_7090[n].f149 = turn;
                g_7090[n].f3c = 2;
            } else {
                g_7090[n].f149 = 0;
                g_7090[n].f3c = 2;
            }
        }
        if (g_8e34[n] != -1) {
            wp = fn_08_29ea(RACE_WP(n).f04);
            g_8e48[n] = dist = fn_08_35d0(d1.x = (pos.x - wp.x) * 2 >> g_9156,
                                          d1.y = (pos.y - wp.y) * 2 >> g_9156);
            if (g_1df8[4][g_8e34[n]].f18)
                g_8e34[n] = -1;
            if (r1 < 0 && (long)g_7090[n].f1e * 100 / g_96f0[g_7090[n].f4e].f00 > 20)
                g_8e34[n] = -1;
        }
        if (g_8e34[n] != -1) {
            g_7090[n].f32 = 4;
            g_7090[n].f34 = g_8e34[n];
        } else {
            g_7090[n].f32 = 8;
            g_7090[n].f34 = g_7090[n].f148 + g_9318 * 2;
        }
        g_7090[n].f38 = 2;
        if (spd / 3 - g_8e3c[n] * 5 + 37 < r1 && g_7090[n].f3c == 2
            && g_8e3c[n] * 15 + 130 > dist && g_8e34[n] == -1)
            g_7090[n].f38 = 5;
    }
    if ((dist < 350 || rand() % 5 == 0) && g_8e34[n] == -1) {
        dist2 = fn_08_35d0(d2.x = (prev.x - wp.x) * 2 >> g_9156,
                           d2.y = (prev.y - wp.y) * 2 >> g_9156);
        r1 = (((long)d2.x * d1.x + (long)d2.y * d1.y) << 7) / (dist * dist2);
        if (r1 < g_8e3c[n] - 2) {
            dist2 = fn_08_35d0(d2.x = (next.x - wp.x) * 2 >> g_9156,
                               d2.y = (next.y - wp.y) * 2 >> g_9156);
            r3 = (((long)d2.x * d1.x + (long)d2.y * d1.y) << 7) / (dist * dist2);
            r2 = (((long)d2.y * d1.x - (long)d2.x * d1.y) << 7) / (dist * dist2);
            if (r3 > spd / -24 + r1 - 2) {
                fn_10_754a(2, 8, g_7090[n].f148 + g_9318 * 2, 1);
                if (g_1df8[14][n].f51 == 0) {
                    int v;

                    if (g_7090[n].fda < 0)
                        v = -1 - g_7090[n].fda;
                    else
                        v = g_7090[n].fda;
                    g_3d4c[(n * g_9ea0 + v) * g_9ea2 + g_7090[n].f148 + 1] = g_1e68;
                    if (n == g_9646) {
                        for (i = 0; i <= g_9316; i++)
                            if (g_1df8[14][i].f18 == 0 && i != n
                                && g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[n].f148 + 1] != 0)
                                g_8e08[i] = g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[n].f148 + 1]
                                    - g_3d4c[(n * g_9ea0 + v) * g_9ea2 + g_7090[n].f148 + 1];
                            else if (g_8e08[i] < 0)
                                g_8e08[i] = 50000;
                    } else if (g_3d4c[(g_9646 * g_9ea0 + v) * g_9ea2 + g_7090[n].f148 + 1] != 0)
                        g_8e08[n] = g_3d4c[(n * g_9ea0 + v) * g_9ea2 + g_7090[n].f148 + 1]
                            - g_3d4c[(g_9646 * g_9ea0 + v) * g_9ea2 + g_7090[n].f148 + 1];
                    else if (g_8e08[n] > 0)
                        g_8e08[n] = -50000;
                    if (flow_interactive == 0)
                        g_8e3c[n] = 0;
                    else if (g_8e08[n] < -210)
                        g_8e3c[n] = g_9348 + 3;
                    else if (g_8e08[n] < -90)
                        g_8e3c[n] = g_9348 + 2;
                    else if (g_8e08[n] < -10)
                        g_8e3c[n] = g_9348 + 1;
                    else if (g_8e08[n] > 40)
                        g_8e3c[n] = g_9348 - 1;
                    else if (g_8e08[n] > 100)
                        g_8e3c[n] = g_9348 - 2 < 0 ? 0 : g_9348 - 2;
                    else
                        g_8e3c[n] = g_9348;
                }
                if (g_7090[n].f148 < g_9ea2 - 1) {
                    g_7090[n].f148++;
                    g_7090[n].f32 = 8;
                    g_7090[n].f34 = g_7090[n].f148 + g_9318 * 2;
                } else {
                    g_7090[n].f148 = 0;
                    g_7090[n].f32 = 8;
                    g_7090[n].f34 = g_9318 * 2;
                    g_7090[n].fda = -1 - g_7090[n].fda;
                }
                dist = fn_08_35d0(d1.x = (pos.x - next.x) * 2 >> g_9156,
                                  d1.y = (pos.y - next.y) * 2 >> g_9156);
                if (g_8e3c[n] * 40 + 700 < dist
                    && (int)((long)g_7090[n].f1e * 100 / g_96f0[g_7090[n].f4e].f00) > rand() % 110) {
                    dist = fn_08_35d0(d1.x = (wp.x - pos.x) * 2 >> g_9156,
                                      d1.y = (wp.y - pos.y) * 2 >> g_9156);
                    r1 = ((long)g_1050[g_1df8[14][n].f28].y * d1.y
                          + (long)g_1050[g_1df8[14][n].f28].x * d1.x) * 10 / (dist * 8 / 5);
                    r3 = ((long)g_1df8[14][n].f0e * d1.y + (long)g_1df8[14][n].f0c * d1.x) * 10
                         / (dist * spd / 10);
                    if (g_1df8[14][n].f51 == 0 && g_7090[n].f1e > 200
                        && r1 < (8 - g_8e3c[n]) * 7 && r3 < 38 - g_8e3c[n] * 5)
                        fn_11_5ab6(n, 2);
                }
                g_8e34[n] = -1;
                if ((long)g_7090[n].f1e * 100 / g_96f0[g_7090[n].f4e].f00 < rand() % 27 + 20)
                    for (i = 0; i < g_9ebf[g_9322]; i++)
                        if (g_1df8[4][i].f18 == 0
                            && g_9ec2[g_9322][g_9eb9[g_9322] + g_9ebc[g_9322] + i] == g_7090[n].f148)
                            g_8e34[n] = i;
            }
            g_1cca[n] = r2;
        }
    }
    if (n == g_9646 && g_1df8[14][n].f51 && g_1e68 - g_9e70[n] > 600)
        g_7090[n].fda = -1 - g_9ea0;
    if (g_7090[n].fda < 0) {
        if (g_1df8[14][n].f04.x + g_1df8[14][n].f20 > g_1df8[12][1].f04.x + 350
            && g_1df8[14][n].f04.x < g_1df8[12][1].f04.x + 2000
            && g_1df8[14][n].f04.y + g_1df8[14][n].f20 > g_9ea8[g_9322].x
            && g_1df8[14][n].f04.y < g_9ea8[g_9322].y
            && (g_1df8[14][n].f0c > 0 || g_7090[n].fda + g_9ea0 == -1)) {
            fn_10_754a(0x72, 14, n, 1);
            if (g_1df8[14][n].f51 == 0) {
                g_9e80[n] = g_9e70[n];
                g_9e70[n] = g_1e68;
                if (g_9e90[n] == 0 || g_1e68 - g_9e80[n] < g_9e90[n])
                    g_9e90[n] = g_9e70[n] - g_9e80[n];
            }
            g_7090[n].fda = -g_7090[n].fda;
            if (g_7090[n].fda >= g_9ea0 && g_9eb5 == 0) {
                g_9eb5 = 1;
                for (i = 0; i <= g_9316; i++)
                    if (g_1df8[14][i].f18 == 0) {
                        int v;

                        if (g_7090[i].fda < 0)
                            v = -1 - g_7090[i].fda;
                        else
                            v = g_7090[i].fda;
                        if (v < g_9ea0)
                            g_9eb5 = 0;
                    }
                if (n == g_9646) {
                    if (g_7090[n].fda - g_9ea0 == 1)
                        g_9eb5 = 1;
                    else {
                        if (g_9684 == 1)
                            fn_10_744c(0x74);
                        else
                            fn_10_744c(0x42);
                        g_9e60[n] = g_1e68 - g_9e60[n];
                    }
                } else if (g_7090[n].fda == g_9ea0) {
                    fn_10_744c(0x69);
                    fn_10_754a(0x42, 14, n, 1);
                    g_9e60[n] = g_1e68 - g_9e60[n];
                }
                if (g_91fc) {
                    g_7090[n].f148 = -2;
                    g_7090[n].f32 = 0;
                    g_7090[n].f34 = 0;
                    g_7090[n].f38 = 2;
                    g_7090[n].f3c = 2;
                    g_9eb5 = 1;
                }
                g_1df8[14][n].f51 = 2;
                if (g_9eb5) {
                    fn_10_744c(0x14);
                    race_radar_background(0);
                    for (i = g_9318 * 2; i < g_9318 * 2 + g_9ea2 + g_9ea4; i++)
                        fn_12_3e98(i);
                    for (i = 0; i <= g_9316; i++)
                        if (i != n || g_7090[i].f32 != 0) {
                            g_7090[i].f148 = -2;
                            g_7090[i].f32 = 12;
                            g_7090[i].f34 = 0;
                            g_7090[i].f38 = 2;
                            g_7090[i].f3c = 2;
                            if (g_1df8[14][i].f51 == 0)
                                g_1df8[14][i].f51 = 1;
                        }
                }
            }
        }
    }
    g_7090[n].f94 = g_1e50 + 60;
}

/* Not yet decompiled: 4:2f98 */
void far pascal fn_04_2f98(int n, int k)
{
}

/* Per-frame steering of racer n toward its current target [inferred]. */
/* @addr 4:0bde */
void far fn_04_0bde(int n)
{
    int d;
    int a;
    int b;
    int kind;
    int idx;
    int old;
    int i;
    int mode;
    int same;
    int ok;
    POINT tgt;
    POINT scr;
    RECT r1;
    RECT r2;
    RECT r3;

    if (n == g_952e && g_9e49 >= 1 && g_9e49 <= 6)
        return;
    g_1cb8[n]++;
    ok = 1;
    if (g_9320 == 6 && (g_9eb5 == 0 || g_7090[n].f32 == 0)) {
        fn_04_144c(n, g_9208 > 0 || g_1cb8[n] & 1);
        g_7090[n].f06 = g_7090[n].f32;
        g_7090[n].f08 = g_7090[n].f34;
        g_7090[n].f3a = g_7090[n].f3c;
        g_7090[n].f36 = g_7090[n].f38;
        if (g_9134 != 2)
            fn_04_4fc8(n);
    }
    if (g_7090[n].f36 == 1 || g_7090[n].f06 != g_7090[n].f32 || g_7090[n].f08 != g_7090[n].f34)
        same = 0;
    else
        same = 1;
    kind = g_7090[n].f06;
    idx = g_7090[n].f08;
    if (kind == -1)
        fn_04_0078(n);
    if (kind == 14 && g_7090[idx].fe8) {
        tgt.x = g_7090[idx].f14a.x;
        tgt.y = g_7090[idx].f14a.y;
    } else if (kind == 12 && !(idx & 1) && g_1df8[14][n].f1a && g_1df8[8][idx].f1a
               && g_1df8[8][idx].f00.y < g_1df8[14][n].f00.y) {
        tgt.y = g_1df8[kind][idx].f04.y - 400;
        scr = fn_08_29ea(g_1df8[12][idx].f04);
        if (g_1df8[14][n].f00.x > scr.x)
            tgt.x = g_1df8[kind][idx].f04.x + 1400;
        else
            tgt.x = g_1df8[kind][idx].f04.x - 1400;
        if (tgt.x < 0)
            tgt.x += G_05A0_LO * 8;
        else if (tgt.x > G_05A0_LO * 8)
            tgt.x -= G_05A0_LO * 8;
    } else
        tgt = g_1df8[kind][idx].f04;
    d = fn_08_285a(&a, &b, g_1df8[14][n].f04, tgt);
    if (g_7090[n].f36 != 2 && d < 220) {
        if (kind == 14 && g_7090[n].f52 == 5 || g_7090[n].f52 == 20)
            g_7090[n].f3a = 7;
        else if (kind == 9 && d < 180 && g_7090[n].f32 == 9 && g_7090[n].f36 == 1
                 || kind == 14 && g_7090[idx].f06 == 14 && g_7090[idx].f08 == n
                    && (fn_09_88ba(g_1df8[14][n].f0c) > 34 || fn_09_88ba(g_1df8[14][n].f0e) > 34)) {
            fn_11_5ab6(n, 5);
            ok = 0;
        }
    }
    if (g_7090[n].f36 == 1 && d > 100 && g_9208 > 1
        && ((long)g_1df8[14][n].f0e * b + (long)g_1df8[14][n].f0c * a) / d < -50) {
        fn_11_5ab6(n, 5);
        ok = 0;
    }
    mode = g_7090[n].f3a;
    if (mode == 7) {
        mode = 3;
        g_7090[n].f3a = 2;
    }
    if (g_9320 == 6 && (g_7090[n].f3a == 3 || g_7090[n].f3a == 4) && g_9eb5 == 0) {
        g_7090[n].f06 = kind = g_7090[n].f32;
        g_7090[n].f08 = idx = g_7090[n].f34;
        if (g_7090[n].f3a == 3) {
            if (g_1df8[8][g_7090[n].f148 + g_9318 * 2].f52)
                g_7090[n].f149 += 2;
            else
                g_7090[n].f149 -= 2;
        } else if (g_7090[n].f3a == 4) {
            if (g_1df8[8][g_7090[n].f148 + g_9318 * 2].f52)
                g_7090[n].f149 -= 2;
            else
                g_7090[n].f149 += 2;
        }
        g_7090[n].f36 = g_7090[n].f3a = mode = 2;
        g_7090[n].f61 = 1;
        tgt = g_1df8[kind][idx].f04;
    }
    old = g_1df8[14][n].f28;
    g_1df8[14][n].f28 = steer_toward_direction(g_1df8[14][n].f04.y, g_1df8[14][n].f04.x,
                                               tgt.y, tgt.x, g_1df8[14][n].f28, mode, n,
                                               kind, idx, same);
    if (g_1df8[14][n].f28 != old)
        fn_13_6716(n);
    if ((g_1df8[14][n].f28 == old || g_1df8[14][n].f28 - old == 1 || g_1df8[14][n].f28 - old == -1
         || g_9320 == 6 && g_7090[n].f3c == 2 && fn_09_88ba(g_7090[n].f149 < 5) && g_9eb5 == 0)
        && g_7090[n].f38 != 5 && ok) {
        if (g_9320 != 6 || g_7090[n].f61 || g_9eb5)
            fn_11_5ab6(n, 1);
        else
            fn_11_5ab6(n, 6);
    } else if (g_7090[n].f3a == 3 || g_7090[n].f3a == 4) {
        fn_11_5ab6(n, 1);
        g_7090[n].f61 = 1;
    } else {
        fn_11_5ab6(n, 6);
        if (g_9320 == 6) {
            if (g_8e3c[n] < 2)
                g_7090[n].f16 = g_7090[n].f14 / 3;
            else if (g_8e3c[n] < 4)
                g_7090[n].f16 = g_7090[n].f14 / 2;
        }
    }
    if (g_7090[n].f3a == 3 || g_7090[n].f3a == 4)
        g_7090[n].f16 = g_7090[n].f14 / 3;
    if (g_7090[n].f3a == 5 && d < 70 && ok)
        fn_11_5ab6(n, 2);
    if (g_7090[n].f3a == 2 && g_7090[n].f36 == 2) {
        if (!(g_7090[n].f30 & 1) && g_932e > 1 && d < 220 && g_7090[n].f1e > 200
            && g_1df8[14][n].f28 == old && kind == 0)
            fn_11_5ab6(n, 2);
        else if ((d > 800 && g_7090[n].f26 > 50 && g_7090[n].f1e > 200 && ok
                  || g_9320 == 6 && d > 500 && g_1df8[14][n].f51 == 0 && g_7090[n].f1e > 200)
                 && g_1df8[14][n].f28 == old) {
            if (rand() % 18 == 0 && g_9320 != 6
                || g_9320 == 6 && g_1df8[14][n].f51 == 0 && (!(rand() & 7) || g_7090[n].f149 > 2))
                fn_11_5ab6(n, 2);
            g_7090[n].f61 = 1;
        } else if (d < 400 && d > 80 && g_9208 > 1) {
            if (g_1df8[kind][idx].f53 && (g_1df8[kind][idx].f54 == 0 || kind == 4))
                for (i = 1; i < g_7090[n].fcb; i++)
                    if (g_7090[n].fb8[i] == 2) {
                        if (g_1df8[14][n].f36 != 10 && g_1df8[14][n].f36 != g_7090[n].f32
                            && (kind != 0 || (long)g_7090[n].fce + g_7090[n].fdc >= 400)
                            && (kind != 4 || g_96f0[g_7090[n].f4e].f00 - 50 >= g_7090[n].f1e))
                            fn_04_584c(i, n, 0);
                        break;
                    }
        } else if (g_9134 == 2 && d < 100)
            fn_11_5ab6(n, 2);
        if (g_1df8[14][n].f1a == 0) {
            SetRect(&r1, g_1df8[kind][idx].f04.x - 0x90, g_1df8[kind][idx].f04.y - 0x90,
                    g_1df8[kind][idx].f04.x + 0x180, g_1df8[kind][idx].f04.y + 0x180);
            SetRect(&r2, g_1df8[14][n].f04.x, g_1df8[14][n].f04.y,
                    g_1df8[14][n].f04.x + g_1df8[14][n].f20, g_1df8[14][n].f04.y + g_1df8[14][n].f20);
            if (IntersectRect(&r3, &r1, &r2))
                fn_13_16ac(n, kind << 8 | (char)idx);
        }
    }
}

/* Race checkpoint progress for the player's ship [inferred]. */
/* @addr 4:277a */
void far fn_04_277a(void)
{
    int u4;
    POINT pos;
    POINT d1;
    POINT vel;
    POINT d2;
    POINT save;
    long u1c;
    int i;
    long dist2;
    long u26;
    long dist;
    long r1;
    long r2;
    long r3;

    if (g_9eb5 == 1)
        return;
    if (g_7090[g_9646].f148 < 0) {
        g_7090[g_9646].f148 = 0;
        g_7090[g_9646].fda = 0;
    }
    save.x = g_240c;
    save.y = g_2410;
    g_240c = g_1df8[8][g_7090[g_9646].f148 + g_9318 * 2].f04.x - (g_90ea << (g_9150 - 1));
    g_2410 = g_1df8[8][g_7090[g_9646].f148 + g_9318 * 2].f04.y - (g_90ec << (g_9150 - 1));
    pos = fn_08_29ea(g_1df8[14][g_9646].f04);
    g_1cea = fn_08_29ea(g_1df8[8][g_7090[g_9646].f148 + g_9318 * 2].f04);
    if (g_7090[g_9646].f148 < g_9ea2 - 1)
        g_1cee = fn_08_29ea(g_1df8[8][g_7090[g_9646].f148 + g_9318 * 2 + 1].f04);
    else
        g_1cee = fn_08_29ea(g_1df8[8][g_9318 * 2].f04);
    if (g_7090[g_9646].f148 > 0)
        g_1cf2 = fn_08_29ea(g_1df8[8][g_7090[g_9646].f148 + g_9318 * 2 - 1].f04);
    else
        g_1cf2 = fn_08_29ea(g_1df8[8][g_9318 * 2 + g_9ea2 - 1].f04);
    vel = *(POINT far *)&g_1df8[14][g_9646].f0c;
    g_8e48[g_9646] = dist = fn_08_35d0(d1.x = (pos.x - g_1cea.x) * 2 >> g_9156,
                                       d1.y = (pos.y - g_1cea.y) * 2 >> g_9156);
    if (dist < 350 || rand() % 5 == 0) {
        dist2 = fn_08_35d0(d2.x = (g_1cf2.x - g_1cea.x) * 2 >> g_9156,
                           d2.y = (g_1cf2.y - g_1cea.y) * 2 >> g_9156);
        r1 = (((long)d2.x * d1.x + (long)d2.y * d1.y) << 7) / (dist * dist2);
        if (r1 < 0) {
            dist2 = fn_08_35d0(d2.x = (g_1cee.x - g_1cea.x) * 2 >> g_9156,
                               d2.y = (g_1cee.y - g_1cea.y) * 2 >> g_9156);
            r2 = (((long)d2.x * d1.x + (long)d2.y * d1.y) << 7) / (dist * dist2);
            r3 = (((long)d2.y * d1.x - (long)d2.x * d1.y) << 7) / (dist * dist2);
            if (r2 > r1) {
                fn_10_744c(2);
                if (g_1df8[14][g_9646].f51 == 0) {
                    int v;

                    if (g_7090[g_9646].fda < 0)
                        v = -1 - g_7090[g_9646].fda;
                    else
                        v = g_7090[g_9646].fda;
                    g_3d4c[(g_9646 * g_9ea0 + v) * g_9ea2 + g_7090[g_9646].f148 + 1] = g_1e68;
                    for (i = 0; i <= g_9316; i++)
                        if (g_1df8[14][i].f18 == 0 && i != g_9646
                            && g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[g_9646].f148 + 1] != 0)
                            g_8e08[i] = g_3d4c[(i * g_9ea0 + v) * g_9ea2 + g_7090[g_9646].f148 + 1]
                                - g_3d4c[(g_9646 * g_9ea0 + v) * g_9ea2 + g_7090[g_9646].f148 + 1];
                        else if (g_8e08[i] < 0)
                            g_8e08[i] = 50000;
                    if (g_7090[g_9646].f148 < g_9ea2 - 1)
                        g_7090[g_9646].f148++;
                    else {
                        g_7090[g_9646].f148 = 0;
                        g_7090[g_9646].fda = -1 - g_7090[g_9646].fda;
                    }
                }
            }
            g_1d02 = r3;
        }
    }
    if (g_1df8[14][g_9646].f51 && g_1e68 - g_9e70[g_9646] > 600 && g_9eb5 == 0)
        g_7090[g_9646].fda = -1 - g_9ea0;
    if (g_7090[g_9646].fda < 0) {
        if (g_1df8[14][g_9646].f04.x + g_1df8[14][g_9646].f20 > g_1df8[12][1].f04.x + 350
            && g_1df8[14][g_9646].f04.x < g_1df8[12][1].f04.x + 2000
            && g_1df8[14][g_9646].f04.y + g_1df8[14][g_9646].f20 > g_9ea8[g_9322].x
            && g_1df8[14][g_9646].f04.y < g_9ea8[g_9322].y
            && (g_1df8[14][g_9646].f0c > 0 || g_7090[g_9646].fda + g_9ea0 == -1)) {
            fn_10_744c(0x72);
            if (g_1df8[14][g_9646].f51 == 0) {
                g_9e80[g_9646] = g_9e70[g_9646];
                g_9e70[g_9646] = g_1e68;
                if (g_9e90[g_9646] == 0 || g_1e68 - g_9e80[g_9646] < g_9e90[g_9646])
                    g_9e90[g_9646] = g_9e70[g_9646] - g_9e80[g_9646];
            }
            g_7090[g_9646].fda = -g_7090[g_9646].fda;
            if (g_7090[g_9646].fda - g_9ea0 == -1)
                fn_10_744c(0x4f);
            if (g_7090[g_9646].fda >= g_9ea0 && g_9eb5 == 0)
                fn_04_2da2();
        }
    }
    g_240c = save.x;
    g_2410 = save.y;
}

/* Racer n reports what hit it (event ev, attacker kind/m) [inferred]. */
/* @addr 4:474c */
void far fn_04_474c(int n, int kind, int m, int ev)
{
    if (g_1d06 > g_1e50 || g_1df8[14][n].f1a == 0)
        return;
    g_1d06 = g_1e50 + 20000;
    if (ev == 5)
        fn_03_06ec(g_9646, 14, n, 0xa5);
    else if (ev == 2) {
        if (kind == 3 || kind == 8 || kind == 1)
            fn_03_06ec(g_9646, 14, n, 0xa6);
        else if (kind == 9)
            fn_03_06ec(g_9646, 14, n, 0xa7);
        else if (kind == 0 && g_1df8[0][m].f53 == 1)
            fn_03_06ec(g_9646, 14, n, 0xa8);
        else if (kind == 0)
            fn_03_06ec(g_9646, 14, n, 0xa9);
        else if (kind == 2)
            fn_03_06ec(g_9646, 14, n, 0xaa);
        else if (kind == 14 && fn_13_2688(n, m) < 0 && g_96f0[g_7090[m].f4e].f1a == 3)
            fn_03_06ec(g_9646, 14, n, 0xad);
        else if (kind == 14 && fn_13_2688(n, m) < 0)
            fn_03_06ec(g_9646, 14, n, 0xab);
        else if (kind == 14)
            fn_03_06ec(g_9646, 14, n, 0xac);
    }
}

/* Picks ship n's current target and its approach side [inferred]. */
/* @addr 4:4fc8 */
void far pascal fn_04_4fc8(int n)
{
    int size;
    int d;
    int a;
    int b;
    int best;
    int sel;
    int i;
    long dx;
    long dy;
    long ex;
    long ey;
    long c;
    long v;
    int changed;
    RECT rc2;
    RECT rc;

    size = g_1df8[14][n].f22;
    changed = 1;
    if (g_1df8[14][n].f1a == 0) {
        g_7090[n].f06 = g_7090[n].f32;
        g_7090[n].f08 = g_7090[n].f34;
        g_7090[n].f36 = g_7090[n].f38;
        g_7090[n].f3a = g_7090[n].f3c;
    } else {
        v = fn_13_1076(14, n);
        if (v != -1) {
            if (HIBYTE(v) == g_7090[n].f06 && LOBYTE(v) == g_7090[n].f08)
                changed = 0;
            g_7090[n].f06 = HIBYTE(v);
            g_7090[n].f08 = LOBYTE(v);
            g_7090[n].f36 = 3;
            if (HIBYTE(v) == 8 && g_3d5a[LOBYTE(v)].f00 == -3)
                g_7090[n].f3a = 5;
            else if (g_7090[n].f32 == 12 && g_7090[n].f38 == 2 && HIBYTE(v) == 8
                     && LOBYTE(v) < g_9318 * 2) {
                if (!(LOBYTE(v) & 1))
                    g_7090[n].f3a = 4;
                else
                    g_7090[n].f3a = 3;
            } else {
                dx = g_1df8[HIBYTE(v)][LOBYTE(v)].f04.x - g_1df8[14][n].f04.x;
                dy = g_1df8[HIBYTE(v)][LOBYTE(v)].f04.y - g_1df8[14][n].f04.y;
                ex = g_1df8[HIBYTE(v)][LOBYTE(v)].f0c - g_1df8[14][n].f0c;
                ey = g_1df8[HIBYTE(v)][LOBYTE(v)].f0e - g_1df8[14][n].f0e;
                if ((c = dx * ey - dy * ex) > 0)
                    g_7090[n].f3a = 4;
                else
                    g_7090[n].f3a = 3;
            }
        } else {
            best = 350;
            for (i = 0; i < g_9418; i++)
                if (g_1df8[9][i].f18 == 0 && g_1df8[9][i].f1a != 0
                    && (g_7090[n].f32 != 9 || g_7090[n].f34 != i)) {
                    d = fn_08_285a(&a, &b, g_1df8[14][n].f04, g_1df8[9][i].f04);
                    if (d < best) {
                        best = d;
                        sel = i;
                    }
                }
            if (best < 250) {
                g_7090[n].f06 = 9;
                g_7090[n].f08 = sel;
                g_7090[n].f36 = 3;
                dx = g_1df8[9][sel].f04.x - g_1df8[14][n].f04.x;
                dy = g_1df8[9][sel].f04.y - g_1df8[14][n].f04.y;
                ex = g_1df8[9][sel].f0c - g_1df8[14][n].f0c;
                ey = g_1df8[9][sel].f0e - g_1df8[14][n].f0e;
                if ((c = dx * ey - dy * ex) > 0)
                    g_7090[n].f3a = 4;
                else
                    g_7090[n].f3a = 3;
                best = 20000;
            } else
                best = 18888;
            for (i = 0; i < g_9412; i++)
                if (g_1df8[6][i].f18 == 0 && (g_66e8[i].f00 != 14 || g_66e8[i].f02 != n)
                    && G_66E4(i) != 0x1b) {
                    d = fn_08_285a(&a, &b, g_1df8[14][n].f04, g_1df8[6][i].f04);
                    if (d < best) {
                        best = d;
                        sel = i;
                    }
                }
            if (best < 160) {
                for (i = 1; i <= g_7090[n].fcb; i++)
                    if (g_2f58[g_7090[n].fb8[i]].f42) {
                        if (g_7090[n].fb8[i] != 2
                            || g_1df8[14][n].f36 == -1 && (g_2f58[G_66E4(i)].f06 == 1
                                                           || g_2f58[G_66E4(i)].f06 == 5))
                            fn_04_584c(i, n, 0);
                        break;
                    }
            }
            if (best < 400) {
                if (g_7090[n].f5e * 15 + 40 > g_7090[n].f26) {
                    g_7090[n].f06 = 6;
                    g_7090[n].f08 = sel;
                    g_7090[n].f36 = 3;
                    g_7090[n].f3a = 5;
                }
            } else if (best == 18888) {
                g_7090[n].f06 = g_7090[n].f32;
                g_7090[n].f08 = g_7090[n].f34;
                g_7090[n].f36 = g_7090[n].f38;
                g_7090[n].f3a = g_7090[n].f3c;
            }
        }
    }
    if (fn_13_371c(g_7090[n].f32, g_7090[n].f34) && g_1df8[14][n].f1a == 0) {
        SetRect(&rc, g_1df8[14][n].f04.x - 800, g_1df8[14][n].f04.y - 800,
                g_1df8[14][n].f04.x + g_1df8[14][n].f22 + 800,
                g_1df8[14][n].f04.y + g_1df8[14][n].f22 + 800);
        if (IntersectRect(&rc2, (RECT *)&g_66e8[g_7090[n].f34 / 2 - 4], &rc)
            && g_7090[n].f88 + 3000 < g_1e50)
            fn_12_2288(14, n);
    }
}

/* Sets g_66e8[n].f0c from the side of the targeted object [inferred]. */
/* @addr 4:5514 */
void far pascal fn_04_5514(int n)
{
    extern REC_1C g_66e4[];     /* same records seen from DS:66e4: makes CL
                                 * load f08 first in the compare [layout-only] */
    long dx;
    long dy;
    long ex;
    long ey;
    int size;                   /* never read: its load puts the record
                                 * address add before the es load */
    int unused3;                /* frame filler [inferred] */
    long l;
    char unused[10];           /* frame filler [inferred] */
    long v;
    char unused2[16];

    size = g_1df8[6][n].f22;
    if (g_1df8[6][n].f1a) {
        v = l = fn_13_1076(6, n);
        if (l != -1) {
            g_66e8[n].f08 = HIBYTE(l);
            g_66e8[n].f0a = LOBYTE(l);
            if (((int *)&g_66e4[n])[2] != g_66e8[n].f08 || g_66e8[n].f02 != g_66e8[n].f0a) {
                dx = g_1df8[HIBYTE(v)][LOBYTE(v)].f04.x - g_1df8[6][n].f04.x;
                dy = g_1df8[HIBYTE(v)][LOBYTE(v)].f04.y - g_1df8[6][n].f04.y;
                ex = g_1df8[HIBYTE(v)][LOBYTE(v)].f0c - g_1df8[6][n].f0c;
                ey = g_1df8[HIBYTE(v)][LOBYTE(v)].f0e - g_1df8[6][n].f0e;
                if (dx * ey - dy * ex > 0)
                    g_66e8[n].f0c = 4;
                else
                    g_66e8[n].f0c = 3;
                return;
            }
        }
    }
    g_66e8[n].f0c = 2;
}

/* @addr 4:584c */
void far pascal fn_04_584c(int s, int n, int t)
{
    int k;

    if (g_1df8[14][n].f2e)
        return;
    if (n == g_9646 && g_9134 == 0)
        g_8e28 = g_1e50;
    k = g_7090[n].fb8[s];
    if (g_2f58[k].f3e == 0)
        g_7090[n].fca = g_7090[n].f5e * 4 + g_2f58[k].f24;
    else {
        g_7090[n].fca = 2;
        g_7090[n].fd4 = g_2f58[k].f24 * 3;
    }
    fn_13_4eec(n, 5);
    if (g_2f58[k].f06)
        fn_11_7c12(k, 14, n);
    else if (k == 5)
        fn_13_1318(14, n, t, 5);
    else if (k == 4)
        fn_13_1318(14, n, t, 4);
    else if (k == 1)
        fn_11_8a42(14, n);
    else if (k == 2)
        fn_11_947a(14, n, 2);
    else if (k == 15)
        fn_11_947a(14, n, 15);
    else if (k == 3)
        fn_11_9fdc(14, n);
    else if (k == 23)
        fn_11_9daa(14, n);
    else if (k == 13)
        fn_11_9078(14, n);
    if (n == g_9646 && g_9134 && g_7090[n].f18 != s) {
        g_9524 = s;
        g_7090[n].f18 = s;
        fn_11_2f8c();
    }
    g_7090[n].f18 = s;
}

/* Scores how useful weapon slot s of racer n is against its current
 * target (-2000 / -100 / 0 = not usable) [inferred]. */
/* @addr 4:6a78 */
int far fn_04_6a78(int n, int s)
{
    int w;
    int type;
    int idx;
    int unused;
    int a;
    int b;
    int rel;
    int ratio;
    int v;
    int score;
    int i;
    int count;

    w = g_7090[n].fb8[s];
    type = g_7090[n].f32;
    idx = g_7090[n].f34;
    if (g_2f58[w].f26 == 0)
        return -2000;
    if (type != 14
        && ((g_7090[n].fae[s] < 14 && g_2f58[g_7090[n].fb8[s]].f06)
            || g_2f58[g_7090[n].fb8[s]].f28 > 3))
        return -2000;
    score = 0;
    if (type == 14) {
        rel = fn_13_2688(n, idx);
        ratio = fn_04_5d9c(n, idx);
    } else {
        rel = -100;
        ratio = 100;
    }
    v = 7;
    if (rel < 0)
        v = 8;
    else
        v--;
    if (rel < -60)
        v++;
    if (rel > 60)
        v--;
    if (rel < -270)
        v++;
    if (rel > 250)
        v--;
    v -= g_7090[n].f5e;
    if (ratio < 60)
        v++;
    if (ratio < 25)
        v++;
    if (g_96f0[g_7090[n].f4e].f1a == 3 || g_96f0[g_7090[n].f4e].f1a == 1
        || g_96f0[g_7090[n].f4e].f1a == 4)
        v += 2;
    v -= g_7090[n].f13e[g_7090[n].f34] / 2;
    if (g_7090[n].f52 == 3 || g_7090[n].f52 == 4)
        v += 2;
    if (g_2f58[w].f26 < v)
        v += -(v - g_2f58[w].f26) * 3 / 4;
    if (type == 14 && g_7090[idx].fe2 && g_2f58[w].f3e == 0)
        score += 7;
    if (g_2f58[w].f3e && type != 14)
        return 0;
    if (g_2f58[w].f26 < 3)
        return 0;
    if (g_2f58[w].f26 - 3 > v)
        return 0;
    score += rand() % 3 - fn_09_88ba(v - g_2f58[w].f26) + 12;
    if (w == 2) {
        count = 0;
        for (i = 0; i < g_940c; i++) {
            if (g_1df8[3][i].f18 == 0 && g_1df8[3][i].f44 > 500
                && fn_08_285a(&a, &b, g_1df8[3][i].f04, g_1df8[14][n].f04) < 320) {
                count++;
                if (count > 1)
                    break;
            }
        }
        for (i = 0; i < g_9416; i++) {
            if (g_1df8[8][i].f18 == 0 && g_1df8[8][i].f44 > 500
                && fn_08_285a(&a, &b, g_1df8[8][i].f04, g_1df8[14][n].f04) < 320) {
                count++;
                if (count > 1)
                    break;
            }
        }
        if (count == 0)
            return 0;
        if (count > 1)
            score += 2;
    }
    if (g_7090[n].f38 == 4) {
        if (g_2f58[w].f00 == 2)
            score += 12;
        if (g_2f58[w].f00 == 3)
            score += 7;
    }
    if (g_7090[n].f1e < 250 && g_2f58[w].f2a != 0) {
        score -= 2;
        if (g_7090[n].f1e < 75)
            score -= 2;
        if (g_2f58[w].f2a > 50)
            score -= 2;
        if (g_2f58[w].f2a * 2 > g_7090[n].f1e)
            return 0;
    }
    if (g_2f58[w].f28 != 0 && (g_2f58[w].f28 + 5) * 5 > g_7090[n].f26) {
        score -= g_2f58[w].f28;
        if (g_2f58[w].f28 * 3 + 13 > g_7090[n].f26 || g_7090[n].f32 != 14)
            return -100;
    }
    if (score > 0 && g_2f58[w].f3e && g_7090[n].f32 == 14) {
        if (g_7090[n].fd4 > 0)
            return 0;
        if (g_7090[n].f38 == 4)
            score += 3;
        if (ratio > 250)
            return 0;
        if (type != 14)
            return 0;
        if (g_7090[n].f13e[g_7090[n].f34] < 0)
            score += -(g_7090[n].f13e[g_7090[n].f34] * 2 - 3);
    }
    return score;
}

/* @addr 4:6e70 */
void far fn_04_6e70(int n)
{
    int i;
    int best;
    int sel;
    int v;
    int j;

    i = g_7090[n].f18;
    g_7090[n].f5f = 0;
    best = -1000;
    sel = -1;
    if (g_7090[n].fcb <= 1)
        return;
    for (i = 1; i < g_7090[n].fcb; i++) {
        if (g_7090[n].fae[i] > 0) {
            if (g_7090[n].f32 == 0 && g_1df8[0][g_7090[n].f34].f2f < 0 && g_7090[n].fb8[i] == 5)
                v = 10000;
            else
                v = fn_04_6a78(n, i);
            if (v > best) {
                sel = i;
                best = v;
            }
        }
    }

    if (best > 0) {
        if (g_2f58[g_7090[n].fb8[sel]].f00 == 2)
            g_7090[n].f5f = 2;
        else if (g_2f58[g_7090[n].fb8[sel]].f00 == 3)
            g_7090[n].f5f = 3;
        else
            g_7090[n].f5f = 1;
        g_7090[n].f18 = sel;
    } else if (best == -100) {
        best = 100;
        for (j = 1; j < g_7090[n].fcb; j++) {
            if (g_7090[n].fae[j] >= 0 && g_2f58[g_7090[n].fb8[j]].f2a < g_7090[n].f1e
                && g_2f58[g_7090[n].fb8[j]].f28 < best) {
                best = g_2f58[g_7090[n].fb8[j]].f28;
                sel = j;
            }
        }

        if (best < 100) {
            if (g_2f58[g_7090[n].fb8[sel]].f00 == 2)
                g_7090[n].f5f = 2;
            else if (g_2f58[g_7090[n].fb8[sel]].f00 == 3)
                g_7090[n].f5f = 3;
            else
                g_7090[n].f5f = 1;
            g_7090[n].f18 = sel;
        } else {
            g_7090[n].f18 = 0;
            g_7090[n].f5f = 1;
        }
    } else {
        g_7090[n].f18 = 0;
        g_7090[n].f5f = 1;
    }
    if (n == g_9646)
        fn_11_2f8c();
}

/* Decides whether the police or other enforcers are summoned against
 * the player (two warning stages via g_1d0a / g_1d0e) [inferred]. */
/* Racer n reacts to a grudge against racer j (f72 / fee): radio
 * message, then attack orders, ganging up for class 2 [inferred].
 * Returns 1 when it acted. */
/* @addr 4:702e */
int far fn_04_702e(int n)
{
    char buf[40];
    char name[20];
    int j;
    int k;
    int age;
    int mode;
    int found;
    int locked;
    int alt;

    locked = found = 0;
    if (g_7090[n].fee[g_9646] == 0)
        return 0;
    if (g_7090[n].f72[g_9646] == 0)
        return 0;
    if (g_92e8 || g_9320 == 7 || g_9320 == 6)
        return 0;
    if (g_7090[n].f00 != 0 && g_7090[n].f00 < 4)
        g_7090[n].f00--;
    if ((n == g_9646 && !flow_interactive) || g_1e30[n].f1a == 0)
        return 0;
    if (g_7090[n].f00 != 0) {
        if (g_7090[n].f00 == 4)
            fn_03_06ec(g_9646, 14, n, 0x88);
        g_7090[n].f00--;
        return 0;
    }
    if (g_7090[n].f26 < 45)
        return 0;
    if (g_96f0[g_7090[n].f4e].f1a == 4 || g_934e < 7)
        return 0;
    for (j = 0; j < g_9316; j++) {
        if (g_1e30[j].f1a != 0 && j != n && g_7090[n].f72[j] > 5
            && g_96f0[g_7090[n].f4e].f1a != 7) {
            if (g_96f0[g_7090[j].f4e].f1a == g_96f0[g_7090[n].f4e].f1a
                && g_7090[n].fee[j] <= 8 && g_7090[n].fee[j] != 4) {
                g_7090[n].fee[j] = 0;
                return g_7090[n].f72[j] = 0;
            } else {
                if (g_7090[n].fee[j] <= 5) {
                    mode = 1;
                    if (rand() % 3 == 0)
                        lstrcpy(buf, g_380c);
                    else if (g_7090[n].f5e == 0)
                        LoadString(g_9212, 0x29c, buf, 40);
                    else if (g_7090[n].f5e < 3)
                        LoadString(g_9212, 0x29d, buf, 40);
                    else if (g_7090[n].f5e == 3)
                        LoadString(g_9212, 0x29e, buf, 40);
                } else {
                    mode = 0;
                    if (rand() % 3 == 0)
                        lstrcpy(buf, g_380c);
                    else if (g_7090[n].f5d == 0)
                        LoadString(g_9212, 0x29f, buf, 40);
                    else if (g_7090[n].f5d < 2)
                        LoadString(g_9212, 0x2a0, buf, 40);
                    else if (g_7090[n].f5d == 3)
                        LoadString(g_9212, 0x2a1, buf, 40);
                }
                if (g_7090[n].fee[j] == 4) {
                    for (k = 0; k < 3; k++) {
                        if (g_4eec[g_96f0[g_7090[n].f4e].f1a][k] == g_7090[j].fd6) {
                            found = 1;
                            if (g_6e20 == 0) {
                                fn_14_3eda();
                                locked = 1;
                            }
                            lstrcpy(name, g_6e20[g_6b10[g_96f0[g_7090[n].f4e].f1a][k]].name);
                            age = g_91f8 - g_4fd0[g_96f0[g_7090[n].f4e].f1a][k];
                        }
                    }
                }
                if (!found && !(rand() & 1))
                    alt = 1;
                else
                    alt = 0;
                fn_10_a332(g_8d38, 0xbd9, 1, !(rand() & 1), (LPSTR)buf, alt, !found,
                           g_7090[n].fee[j] + 0x351, found, (LPSTR)name, age, g_09d6);
                if (locked && found)
                    fn_14_4074();
                fn_03_06ec(j, 14, n, mode + 0x4f);
                if (mode) {
                    if (g_7090[n].f72[j] < 9 || g_96f0[g_7090[n].f4e].f1a == 2) {
                        g_7090[n].f52 = 0;
                        g_7090[n].f06 = g_7090[n].f32 = 14;
                        g_7090[n].f08 = g_7090[n].f34 = j;
                        g_7090[n].f94 = g_1e50 + 8000;
                        g_7090[n].f38 = 1;
                        g_7090[n].f36 = 1;
                        g_7090[n].f3c = 2;
                        g_7090[n].f3a = 2;
                        if (g_96f0[g_7090[n].f4e].f1a == 2) {
                            for (k = 0; k <= g_9316; k++) {
                                if (g_96f0[g_7090[k].f4e].f1a == 2 && k != j) {
                                    g_7090[k].f38 = 3;
                                    g_7090[k].f36 = 3;
                                    g_7090[k].f3c = 2;
                                    g_7090[k].f3a = 2;
                                    g_7090[k].f52 = 0;
                                    g_7090[k].f06 = g_7090[k].f32 = 14;
                                    g_7090[k].f08 = g_7090[k].f34 = j;
                                    g_7090[k].f94 = g_1e50 + 15000;
                                }
                                if (g_96f0[g_7090[k].f4e].f1a == 0
                                    && (g_7090[n].fee[j] == 3 || g_7090[n].fee[j] == 1)) {
                                    g_7090[k].f52 = 2;
                                    g_7090[k].f98 = g_1e50 + 20000;
                                    g_7090[k].f54 = 14;
                                    g_7090[k].f56 = j;
                                    g_7090[k].f58 = n;
                                    g_7090[k].fed = 1;
                                    fn_03_00f4(n, g_7090[n].f54, g_7090[n].f56);
                                    fn_04_8346(k, 14, j, 8);
                                    g_7090[k].fee[j] = 3;
                                    g_7090[k].f72[j] = 0;
                                }
                            }
                        } else
                            fn_04_8346(n, 14, j, 8);
                    } else {
                        if (g_7090[n].f72[j] < 14)
                            g_7090[n].f52 = 2;
                        else if (g_7090[n].f72[j] < 18)
                            g_7090[n].f52 = 3;
                        else
                            g_7090[n].f52 = 4;
                        fn_04_8346(n, 14, j, 8);
                        g_7090[n].f98 = g_1e50 + 20000;
                        g_7090[n].f54 = 14;
                        g_7090[n].f56 = j;
                        g_7090[n].f58 = n;
                        g_7090[n].fed = 1;
                        fn_03_00f4(n, g_7090[n].f54, g_7090[n].f56);
                    }
                    if (g_7090[n].fee[j] == 4) {
                        for (k = 0; k < 3; k++)
                            if (g_4eec[g_96f0[g_7090[n].f4e].f1a][k] == g_7090[j].fd6)
                                g_4eec[g_96f0[g_7090[n].f4e].f1a][k] = -1;
                    }
                }
                g_7090[n].f72[j] = 0;
                return 1;
            }
        }
    }
    return 0;
}

/* @addr 4:7e2a */
void far fn_04_7e2a(void)
{
    int i;
    int c6;
    int c8;
    int v;
    int chance;
    int ce;
    int f;

    if (g_913a || g_913c || g_1e68 - g_8e2c < 400)
        return;
    if (g_1e68 < 500) {
        g_1d0e = g_1d12 = 0;
        g_1d0a = 0;
        return;
    }
    if (g_92e8 || g_9320 == 6 || g_9320 == 7 || g_0992 + 20 > g_932a)
        return;
    if (g_3824[3][g_96f0[g_7090[g_9646].f4e].f1a] < 150
        && (g_1d0a < g_1e50 || g_1d0a == 0)
        && g_9208 / 2 + 3 > g_9316 && g_7090[g_9646].fce > 398) {
        f = 2;
        for (i = ce = c8 = 0; i <= g_9316; i++) {
            if (g_96f0[g_7090[i].f4e].f1a == 3) {
                f--;
                if (g_7090[i].fcd == g_9646)
                    f = 0;
            }
            if (g_7090[i].f38 == 1 && g_7090[i].f32 == 14 && g_1e30[i].f1a != 0) {
                ce++;
                if (g_7090[i].f34 == g_9646)
                    ce++;
            }
        }
        if (f > 0) {
            v = (g_7090[g_9646].fce - 220) / 32 + g_3824[3][g_96f0[g_7090[g_9646].f4e].f1a] / -100
                + g_9334 / 3 - ce - g_9316;
            if (g_7090[g_9646].f26 < 40)
                v++;
            if ((v = f * v / 2) > rand() % 720 && g_9334 > 0) {
                if (g_1d0a != 0 && g_1d0a < g_1e50) {
                    fn_13_adbe(g_9646, 3, 0x69);
                    g_1d0a = 0;
                    return;
                }
                if (g_1d0a == 0) {
                    fn_03_06ec(g_9646, 7, 0, 0x6b);
                    g_1d0a = g_1e50 + 7000;
                    return;
                }
            }
        }
    }
    if (g_3824[4][g_96f0[g_7090[g_9646].f4e].f1a] > -50
        && (g_1d0e < g_1e50 || g_1d0e == 0)
        && g_9208 / 2 + 3 > g_9316 && g_7090[g_9646].f26 < 60) {
        f = 2;
        for (i = c6 = c8 = 0; i <= g_9316; i++) {
            if (i != g_9646 && g_7090[i].fec) {
                if (g_96f0[g_7090[g_9646].f4e].f1a == 2) {
                    if (g_96f0[g_7090[i].f4e].f1a == 0) {
                        f--;
                        if (g_7090[i].fcd == g_9646)
                            f = 0;
                    }
                } else if (g_96f0[g_7090[g_9646].f4e].f1a == 3) {
                    if (g_96f0[g_7090[i].f4e].f1a == 3) {
                        f--;
                        if (g_7090[i].fcd == g_9646)
                            f = 0;
                    }
                } else if (g_96f0[g_7090[i].f4e].f1a == 4) {
                    f--;
                    if (g_7090[i].fcd == g_9646)
                        f = 0;
                }
                if (g_96f0[g_7090[i].f4e].f1a == g_96f0[g_7090[g_9646].f4e].f1a)
                    c8++;
                if (g_7090[i].f38 == 1 && g_7090[i].f32 == 14 && g_7090[i].f34 == g_9646) {
                    c6++;
                    if (fn_04_5d9c(g_9646, i) < 40)
                        c6++;
                }
            }
        }
        for (i = 0; i < g_940a; i++)
            if (g_1df8[2][i].f18 == 0 && g_52fe[i].f0a == 14 && g_52fe[i].f0c == g_9646
                && g_52fe[i].f00 == 10)
                c6++;
        if (f > 0) {
            chance = (g_3824[4][g_96f0[g_7090[g_9646].f4e].f1a] / 120 + (c6 * 2 - c8) * 2
                      - g_7090[g_9646].f26 / 15 + g_9334 / 2 - g_9316 + 5) * f / 2;
            if (c6 != 0 && rand() % 300 < chance) {
                if (g_1d0e != 0 && g_1d0e < g_1e50) {
                    fn_13_adbe(g_9646, 4, 0x6a);
                    g_1d0e = 0;
                    return;
                }
                if (g_1d0e == 0) {
                    fn_03_06ec(g_9646, 7, 0, 0x6c);
                    g_1d0e = g_1e50 + 7000;
                    return;
                }
            }
        }
    }
    if (g_9208 / 2 + 4 > g_9316 && g_964a > 6 && g_9648 > 4 && g_9208 > 0) {
        f = 1;
        for (i = c8 = 0; i <= g_9316; i++)
            if (g_96f0[g_7090[i].f4e].f1a == 7)
                f = 0;
        chance = g_964a / 2 + g_3824[7][g_96f0[g_7090[g_9646].f4e].f1a] / -140 + g_9334 / 2;
        if (f && rand() % 300 < chance)
            fn_13_adbe(g_9646, 0x16, 0x6d);
    }
}

/* @addr 4:8346 */
int far fn_04_8346(int n, int x, int y, int v)
{
    if (v == 3 && g_7090[n].f38 == 1 && g_7090[n].f32 == x && g_7090[n].f34 == y)
        v = g_7090[n].f146;
    if (n != g_9646 || flow_interactive == 0)
        fn_13_9a18(n, x, y);
    g_7090[n].f146 = v;
    return 1;
}

/* @addr 4:83ae */
void far fn_04_83ae(void)
{
    int i;
    int j;
    int a;
    int b;
    int d;

    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].fec && g_7090[i].fe8) {
            for (j = 0; j <= g_9316; j++) {
                if (j != i && g_7090[j].fec && g_7090[j].f32 == 14 && g_7090[j].f34 == i) {
                    d = fn_08_285a(&a, &b, g_1df8[14][i].f04, g_7090[i].f14a);
                    if (d > 350) {
                        g_7090[i].f14a.x = rand() % 4000 + g_1df8[14][i].f04.x - 2000;
                        g_7090[i].f14a.y = rand() % 4000 + g_1df8[14][i].f04.y - 2000;
                        if (g_7090[i].f14a.x < 0)
                            g_7090[i].f14a.x += G_05A0_LO * 8;
                        else if (g_7090[i].f14a.x > G_05A0_LO * 8)
                            g_7090[i].f14a.x -= G_05A0_LO * 8;
                        if (g_7090[i].f14a.y < 0)
                            g_7090[i].f14a.y += G_05A0_HI * 8;
                        else if (g_7090[i].f14a.y > G_05A0_HI * 8)
                            g_7090[i].f14a.y -= G_05A0_HI * 8;
                    }
                }
            }
        }
    }
}

/* @addr 4:84de */
void far fn_04_84de(void)
{
    int i;
    int count;
    int r;

    g_967e = min(g_9334 * 7 + 45, 100);
    if (g_1e68 < 500)
        g_967e -= (700 - g_1e68) / 8;
    else
        g_967e = min(g_967e + g_1e68 / 100, 100);
    if (g_967e < 3)
        g_967e = 3;
    if (g_7090[g_9646].fce + g_7090[g_9646].fdc < 100)
        g_967e -= 20;
    if (g_7090[g_9646].fce + g_7090[g_9646].fdc > 250)
        g_967e += 20;
    if (g_7090[g_9646].fce + g_7090[g_9646].fdc > 1000)
        g_967e += 30;
    count = 0;
    for (i = 0; i < 8; i++)
        if (g_1df8[0][i].f18 == 0)
            count++;
    r = count * 10 / (g_9316 + 1);
    if (r < 15)
        g_967e -= 10;
    if (r < 10)
        g_967e -= 10;
    if (r < 5)
        g_967e -= 10;
    if (g_9000 == 0)
        g_967e = -10;
}

/* @addr 4:8c80 */
int far fn_04_8c80(void)
{
    int i;
    int best;
    int max;
    int a;
    int score;

    best = -1;
    max = -1;
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].fec && g_1df8[14][i].f18 == 0) {
            if (g_7090[i].fda < 0)
                a = -g_7090[i].fda;
            else
                a = g_7090[i].fda;
            score = a * g_9ea2 + g_7090[i].f148;
            if (score > max) {
                max = score;
                best = i;
            }
            if (score == max && g_8e48[best] > g_8e48[i]) {
                max = score;
                best = i;
            }
        }
    }
    return best;
}

/* @addr 4:8d3a */
int far fn_04_8d3a(void)
{
    unsigned long best;
    int i;
    int found;

    best = 1000000;
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].fec && g_1df8[14][i].f18 == 0 && g_1df8[14][i].f51 == 2
            && g_9e60[i] < best) {
            found = i;
            best = g_9e60[i];
        }
    }
    return found;
}
/* @addr 4:5d9c */
int far fn_04_5d9c(int a, int b)
{
    long a26;
    long ad8;
    long b26;
    long bd8;
    long x;
    long y;

    if (a >= 0 && a <= g_9316 && b >= 0 && b <= g_9316) {
        ad8 = g_7090[a].fd8;
        bd8 = g_7090[b].fd8;
        a26 = g_7090[a].f26;
        b26 = g_7090[b].f26;
        x = (long)g_7090[a].f26 * ad8 / (a26 / 2 + 50);
        y = (long)g_7090[b].f26 * bd8 / (b26 / 2 + 50);
        if (y == 0)
            y = 10;
        return x * 100 / y;
    }
    return 100;
}

/* Racer n reacts to being hit by m (damage dmg, kind) [inferred]. */
/* @addr 4:5e8e */
void far fn_04_5e8e(int n, int m, int dmg, int kind)
{
    int r;
    int i;
    int cn;
    int cm;
    int k;
    int d;
    int c;
    int u12;
    int ok;

    if (dmg == 90)
        dmg = 50;
    fn_13_2714(n, m, -(dmg / 4 + 4), -8 - dmg, 0, -1);
    if (kind == 1 && m == g_9646
        && !(g_7090[g_9646].f38 == 1 && g_7090[g_9646].f32 == 14 && g_7090[g_9646].f34 == n)
        && g_7090[n].fc2[m] == 0
        && (dmg < 33 || g_7090[n].f44[1] == 0 || g_1e68 / 10 - g_7090[n].f44[1] > 80))
        return;
    if (g_92e8 || g_9320 == 7)
        return;
    if (kind == 1 && g_7090[n].ff7[m][0] < 9)
        fn_13_2714(n, m, -8, -10 - dmg, 0, 1);
    if (g_7090[n].f38 == 4) {
        if (g_3824[7][g_96f0[g_7090[n].f4e].f1a] > -100
            && g_3824[7][g_96f0[g_7090[m].f4e].f1a] < 100) {
            if (dmg > 10 && rand() % 4 <= 1 && g_7090[n].f26 < 40)
                fn_13_b6f2(m, 3);
            else
                for (i = 0; i < g_9316; i++)
                    if (g_96f0[g_7090[i].f4e].f1a == 7) {
                        fn_03_06ec(m, 14, i, 0x5c);
                        break;
                    }
        }
        fn_13_2714(n, m, -13, -dmg, 0, kind);
        return;
    }
    c = 0;
    cn = g_96f0[g_7090[n].f4e].f1a;
    cm = g_96f0[g_7090[m].f4e].f1a;
    if (g_7090[n].f26 < 41 && kind != 1)
        return;
    if (kind == 2 && (cm == cn || g_7090[n].f52 == 9 || fn_13_2688(n, m) > 100))
        return;
    if (m == n)
        return;
    if (g_7090[n].f52 >= 2 && g_7090[n].f52 <= 4 && g_7090[n].f58 == n
        && g_7090[n].f54 == 14 && g_7090[n].f56 == m)
        return;
    if (kind == 2 && fn_13_2688(n, m) > 130)
        return;
    if (cn == 5 || cm == cn)
        c++;
    if (cn == 4)
        c++;
    if (g_7090[n].fc2[m] >= 20) {
        g_7090[n].fc2[m] = 0;
        return;
    }
    if (g_7090[n].f32 == 14 && g_7090[n].f34 == m && g_7090[n].f38 == 1 && cn != 7)
        return;
    if (g_96f0[g_7090[n].f4e].f00 / 10 > g_7090[n].f1e && m == g_9646) {
        fn_03_06ec(m, 14, n, 0xbe);
        if (g_7090[n].fc2[m] == 4) {
            dmg *= 2;
            if (g_3824[7][g_96f0[g_7090[n].f4e].f1a] > -100
                && g_3824[7][g_96f0[g_7090[m].f4e].f1a] < 100)
                fn_13_b6f2(m, 3);
        } else
            fn_10_744c(0x3d);
        g_7090[n].fc2[m] = 4;
        return;
    }
    if (kind != 1 || g_7090[n].ff7[m][0] > 8)
        fn_13_2714(n, m, -(dmg / 2 + 7), -10 - dmg, 1, kind);
    if (n == g_9646 && (g_9134 == 0 || flow_interactive))
        return;
    d = fn_04_5d9c(n, m);
    if (g_7090[n].f5e > 1 && (d < 15 || d > 700) && cn != 7)
        return;
    if (d < 30 || d > 300)
        c++;
    if (g_7090[n].fc2[m] == 0 && m == g_9646)
        fn_10_754a(0x3d, 0, 0, 0);
    g_7090[n].fc2[m]++;
    if (m == g_9646 && kind == 1)
        g_9432 += dmg / 2;
    r = fn_13_2688(n, m);
    k = 0;
    if (g_7090[n].f26 - dmg / AD_M0E(g_7090[n].f4e) < 65)
        k = 1;
    if (g_7090[n].f26 - dmg / AD_M0E(g_7090[n].f4e) < 45)
        k++;
    if (dmg > 24)
        k++;
    if (dmg > 36)
        k++;
    if (dmg == 90) {
        if (g_7090[n].f5e == 3)
            k += 3;
        else
            k++;
    }
    if (r < -100)
        k++;
    if (r < -210)
        k++;
    if (cn == 7 && g_96f0[g_7090[m].f4e].f1a != 7) {
        if (g_7090[n].f5e > 1) {
            if (g_7090[n].fc2[m] < 2) {
                ok = 1;
                for (i = 0; i <= g_9316; i++)
                    if (g_7090[i].f5e == 1 && g_96f0[g_7090[i].f4e].f1a == 7
                        && g_1df8[14][i].f18 == 0 && g_7090[i].fec != 0)
                        ok = 0;
                if (ok)
                    fn_03_06ec(m, 14, n, 0x3b);
                g_7090[n].f52 = 0x15;
                g_7090[n].f54 = 14;
                g_7090[n].f56 = m;
                g_7090[n].fed = 1;
                g_7090[n].f94 = g_1e50;
                g_964a++;
                g_9648 += 3;
            } else {
                if (fn_13_adbe(m, 0x15, 0x3c))
                    g_a163 = 5;
                else
                    fn_03_06ec(m, 14, n, 0x43);
                if (m == g_9646 && g_a152 - 1 < g_a15c)
                    g_a152++;
                g_964a += 3;
                g_9648 += 3;
                g_7090[n].f52 = 0x14;
                for (i = 0; i <= g_9316; i++)
                    g_7090[n].fc2[i] = 0;
            }
        } else if (g_7090[n].f54 != 14 || g_7090[n].f56 != m && g_7090[n].f5e == 1) {
            if (g_7090[n].fc2[m] > 2) {
                g_7090[n].f52 = 0x3e;
                g_7090[n].fed = 2;
                g_7090[n].f98 = g_1e50 + 20000;
                g_7090[n].f54 = 14;
                g_7090[n].f56 = m;
            } else
                fn_03_06ec(m, 14, n, 0x41);
        }
    } else if (r > 0) {
        if (c - g_7090[n].f5d + 4 >= g_7090[n].fc2[m]) {
            if (dmg != 90) {
                if (g_7090[n].fc2[m] > 1)
                    fn_03_06ec(m, 14, n, 0x2a);
                else
                    fn_03_06ec(m, 14, n, 0x29);
                if (c - g_7090[n].fc2[m] - g_7090[n].f5d == -5 && m == g_9646) {
                    fn_03_06ec(m, 14, n, 0x2b);
                    fn_10_754a(0x3e, 0, 0, 0);
                }
            }
        } else {
            if (g_96f0[g_7090[n].f4e].f1a == 2)
                for (i = 0; i <= g_9316; i++)
                    if (g_96f0[g_7090[i].f4e].f1a == 0 && i != g_9646 && g_7090[i].fec
                        && g_1df8[14][i].f18 == 0 && g_7090[i].f26 > 40 && i != m)
                        n = i;
            fn_03_00f4(n, 14, m);
            fn_13_915c(n);
        }
    } else {
        if (g_7090[n].f5e + c + 1 >= g_7090[n].fc2[m]) {
            if (dmg != 90) {
                if (g_7090[n].fc2[m] > 1)
                    fn_03_06ec(m, 14, n, 0x2e);
                else
                    fn_03_06ec(m, 14, n, 0x2d);
                if (g_7090[n].f5e - g_7090[n].fc2[m] + c == -2 && m == g_9646) {
                    fn_03_06ec(m, 14, n, 0x2f);
                    fn_10_754a(0x3e, 0, 0, 0);
                }
            }
        } else {
            if (g_96f0[g_7090[n].f4e].f1a == 2)
                for (i = 0; i <= g_9316; i++)
                    if (g_96f0[g_7090[i].f4e].f1a == 0 && i != g_9646 && g_7090[i].fec
                        && g_1df8[14][i].f18 == 0 && g_7090[i].f26 > 40 && i != m)
                        n = i;
            fn_03_00f4(n, 14, m);
            fn_13_915c(n);
        }
    }
    g_7090[n].fc2[m] += k;
}

/* @addr 4:7d36 */
void far fn_04_7d36(int a, int b, int c)
{
    int k;
    int i;

    if ((g_7090[a].f32 == 14 && g_7090[a].f34 == b)
        || (g_7090[b].f32 == 14 && g_7090[b].f34 == a)) {
        k = 1;
        if (c > 30)
            k = 2;
        g_7090[a].f13e[b] = g_7090[a].f13e[b] + k > 6 ? 6 : g_7090[a].f13e[b] + k;
        g_7090[b].f13e[a] = g_7090[b].f13e[a] - k < -6 ? -6 : g_7090[b].f13e[a] - k;
        if (a == g_9646) {
            g_9680++;
            g_8e00 += c;
        } else if (b == g_9646) {
            g_9682++;
            g_8e04 += c;
        }
    }
    if (c > 0 && a == g_9646) {
        for (i = 3; i >= 0; i--)
            g_7090[b].f44[i + 1] = g_7090[b].f44[i];
        g_7090[b].f44[0] = g_1e68 / 10;
    }
}

/* Updates g_9684 with the player's race standing [inferred]. */
/* @addr 4:8b82 */
void far race_position(void)
{
    int i;
    int score;
    int mine;
    int a;

    if (g_1df8[14][g_9646].f51 == 0) {
        if (g_7090[g_9646].fda < 0)
            a = -g_7090[g_9646].fda;
        else
            a = g_7090[g_9646].fda;
        mine = a * g_9ea2 + g_7090[g_9646].f148;
        g_9684 = 1;
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].fec && g_1df8[14][i].f18 == 0 && i != g_9646) {
                if (g_7090[i].fda < 0)
                    a = -g_7090[i].fda;
                else
                    a = g_7090[i].fda;
                score = a * g_9ea2 + g_7090[i].f148;
                if (score > mine)
                    g_9684++;
                if (mine == score && g_8e48[i] < g_8e48[g_9646])
                    g_9684++;
            }
        }
    }
}

/* Checks whether object n may act now (facing test, timers) and then calls fn_04_584c [inferred]. */
/* @addr 4:5654 */
int far pascal fn_04_5654(int n)
{
    int u1;
    int u2;
    int r;
    int dir;
    int c;
    int m;
    char pad[18];
    POINT p2;
    POINT p1;
    POINT p3;
    int u3;

    if (g_7090[n].f18 == 0)
        return 0;
    if (g_7090[n].f32 == 14 && g_2f58[g_7090[n].f18].f3e && g_7090[g_7090[n].f34].fe2)
        fn_04_6e70(n);
    if (g_7090[n].f5f != 3) {
        if (g_1df8[g_7090[n].f32][g_7090[n].f34].f1a)
            p1 = g_1df8[g_7090[n].f32][g_7090[n].f34].f00;
        else
            p1 = fn_08_29ea(g_1df8[g_7090[n].f32][g_7090[n].f34].f04);
        if (g_1df8[14][n].f1a)
            p2 = g_1df8[14][n].f00;
        else
            p2 = fn_08_29ea(g_1df8[14][n].f04);
        dir = fn_08_19b0(p1.x - p2.x, p1.y - p2.y);
        c = g_1df8[14][n].f28;
        m = (c + 8) % 16;
        if (c == dir)
            r = 1;
        else if (m == dir)
            r = 2;
        if (g_7090[n].f5f != r)
            return 0;
    }
    if (g_7090[n].fe8 || g_7090[n].f10 > 0) {
        if (g_8e28 + 3000 > g_1e50) {
            if (g_1df8[14][n].f2e == -2 && fn_11_4c72(n) && n == g_9646)
                fn_03_332e(0x409, 0x416);
            if (g_7090[n].f10 == 7 && fn_11_4b00(n) && n == g_9646)
                fn_03_332e(0x408, 0x416);
            return 0;
        }
    }
    fn_04_584c(g_7090[n].f18, n, 0x19);
    return 1;
}

/* Picks a new goal (f06/f08) for racer n [inferred]. */
/* @addr 4:4d00 */
void far pascal fn_04_4d00(int n)
{
    int d;
    int i;
    int j;
    int a;
    int b;
    int best;
    int sel;
    int count;

    if (g_7090[n].f06 == 12 && g_7090[n].f36 == 2)
        return;
    if (g_92e8)
        return;
    if (g_940a) {
        if (g_96f0[g_7090[n].f4e].f1a != 7 && g_9208 >= 2) {
            if (g_7090[n].f52 == 0 || g_7090[n].f52 == 7) {
                best = 20000;
                sel = -1;
                count = 0;
                for (i = 0; i < g_940a; i++) {
                    if (g_1df8[2][i].f18 == 0 && g_52fe[i].f0a == 14 && g_52fe[i].f0c == n
                        && g_52fe[i].f00 == 15) {
                        count++;
                        d = fn_08_285a(&a, &b, g_1df8[14][n].f04, g_1df8[2][i].f04);
                        if (d < best)
                            sel = i;
                    }
                }
                if (count > 1 || best < 180) {
                    g_7090[n].f06 = 2;
                    g_7090[n].f08 = sel;
                    g_7090[n].f36 = 1;
                    fn_04_8346(n, g_7090[n].f3a = 2, sel, 6);
                }
            }
        }
    }
    if (g_96f0[g_7090[n].f4e].f00 / 10 > g_7090[n].f1e) {
        if (g_7090[n].f1e != 0 && rand() % g_7090[n].f1e > 150)
            return;
        best = 20000;
        sel = -1;
        for (j = 0; j < g_940e; j++) {
            if (g_1df8[4][j].f18 == 0) {
                d = fn_08_285a(&a, &b, g_1df8[14][n].f04, g_1df8[4][j].f04);
                if (d < best) {
                    best = d;
                    sel = j;
                }
            }
        }
        if (sel >= 0) {
            g_7090[n].f06 = 4;
            g_7090[n].f08 = sel;
            g_7090[n].f36 = 2;
            g_7090[n].f94 = g_1e50 + 4000;
            g_7090[n].f3a = 2;
            g_7090[n].f52 = 0;
            return;
        }
        if (g_7090[n].fce + g_7090[n].fdc >= 200) {
            if (fn_16_0b4e(n)) {
                g_7090[n].f06 = 7;
                g_7090[n].f08 = 0;
                g_7090[n].f36 = 3;
                g_7090[n].f3a = 2;
            }
        } else if (g_9320 != 7) {
            fn_03_06ec(g_9646, 14, n, 0xb7);
            g_7090[n].f06 = 12;
            g_7090[n].f08 = 0;
            g_7090[n].f3a = g_7090[n].f36 = 2;
        }
    }
    if (g_1df8[14][n].f32 == 14 && g_7090[n].f36 != 4
        && !(g_7090[n].f06 == 14 && g_1df8[14][n].f34 == g_7090[n].f08)) {
        g_7090[n].f06 = 14;
        g_7090[n].f08 = g_1df8[14][n].f34;
        g_7090[n].f3a = 2;
        g_7090[n].f36 = 1;
        g_7090[n].f52 = 0;
    }
}

/* Racers that reach the goal object of n react: messages and new goals [inferred]. */
/* @addr 4:6700 */
void far fn_04_6700(int n)
{
    int i;
    int k;
    int a;
    int b;
    int type;
    int idx;
    int done;
    char buf[40];

    type = g_7090[n].f06;
    idx = g_7090[n].f08;
    if (g_1df8[type][idx].f18 != 0)
        return;
    done = 0;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f18 == 0 && g_7090[i].fec && g_7090[i].f52 != 14
            && g_7090[i].f32 == type && g_9320 != 6 && i != n && g_7090[i].f34 == idx
            && g_1df8[type][idx].f53 != 0
            && !(g_7090[i].f148 == type && g_7090[i].f149 == idx)) {
            if (g_96f0[g_7090[i].f4e].f1a == 7)
                fn_03_06ec(i, 14, n, 0xbf);
            else
                fn_03_06ec(i, 14, n, 0x66);
            g_7090[i].f148 = type;
            g_7090[i].f149 = idx;
        }
        k = g_96f0[g_7090[i].f4e].f1a;
        if (g_7090[i].f52 != 14 && !done
            && (k == 2 || k == 5) && g_1df8[14][i].f18 == 0 && g_7090[i].fec && i != n
            && !(i == g_9646 && flow_interactive)
            && !(g_7090[i].f52 == 2 && k != 2)
            && (fn_13_2688(i, n) < 160 || g_7090[i].fc2[n] > 0)) {
            if (g_96f0[g_7090[n].f4e].f1a != k
                && !(g_7090[i].f32 == type && g_7090[i].f34 == idx)
                && !(k == 2 && g_96f0[g_7090[n].f4e].f1a == 0)) {
                g_7090[i].f06 = g_7090[i].f32 = type;
                g_7090[i].f08 = g_7090[i].f34 = idx;
                if (fn_08_285a(&a, &b, g_1df8[14][n].f04, g_1df8[14][i].f04) < 1900) {
                    g_7090[i].f38 = 2;
                    g_7090[i].f36 = 2;
                    fn_03_06ec(n, 14, i, 0x17);
                } else
                    g_7090[i].f36 = g_7090[i].f38 = 3;
                g_7090[i].f3a = g_7090[i].f3c = 2;
                g_7090[i].f54 = g_7090[i].f52 = 14;
                g_7090[i].f56 = n;
                g_7090[i].f94 = g_1e50 + 500;
                if (i == g_9646) {
                    LoadString(g_9212, 0x585, buf, 40);
                    lstrcpy(g_8630, buf);
                    fn_03_1542(0, g_7090[i].f06, g_7090[i].f08, buf, 0);
                    lstrcat(g_8630, buf);
                    LoadString(g_9212, 0x586, buf, 40);
                    lstrcat(g_8630, buf);
                    fn_03_1542(0, 14, n, buf, 0);
                    lstrcat(g_8630, buf);
                    lstrcat(g_8630, ".");
                    g_058c = 1;
                    g_05c0 = g_1e50 + 1200;
                }
                done = 1;
            }
            if (g_7090[i].f32 == type && g_7090[i].f34 == idx)
                done = 1;
        }
    }
}

/* Racer n chooses whom to attack (f06/f08), with messages to the player [inferred]. */
/* @addr 4:7636 */
void far fn_04_7636(int n, int type, int idx, int quiet)
{
    int k;
    int i;
    int v;
    int sel;
    int best;
    int found;

    found = 0;
    g_2384 = g_1e50 + 5000;
    k = g_96f0[g_7090[n].f4e].f1a;
    if (type == 14 && g_96f0[g_7090[idx].f4e].f1a == 7) {
        g_7090[n].f06 = type;
        g_7090[n].f08 = idx;
        return;
    }
    if (g_7090[n].f32 == 14 && g_7090[n].ff7[g_7090[n].f34][0] > 3) {
        type = 14;
        idx = g_7090[n].f34;
    }
    best = 7;
    sel = -1;
    for (i = 0; i <= g_9316; i++) {
        if (i != n) {
            v = g_7090[n].ff7[i][0];
            if (type == 14 && i == idx) {
                v += 5;
                if (v > 12)
                    v += 100;
            }
            if (v > best) {
                best = v;
                sel = i;
            }
        }
    }
    if (sel != -1) {
        type = 14;
        idx = sel;
    }
    if (type == 14) {
        g_7090[n].f06 = type;
        g_7090[n].f08 = idx;
        if (idx == g_9646)
            g_6b40[g_96f0[g_7090[n].f4e].f1a]++;
        if (k == 7) {
            if (g_7090[n].f5e > 0) {
                g_9346 = g_7090[idx].fd6;
                if (idx == g_9646) {
                    g_a14d[0]++;
                    g_a147 = g_1e68;
                    g_a14b = g_91f8;
                }
            } else {
                for (i = 0; i <= 9; i++)
                    g_a157[i] = g_a14d[i];
            }
        }
        if (g_7090[n].fee[idx] <= 5 && g_7090[n].f38 != 4)
            type = 0;
        else if (g_96f0[g_7090[n].f4e].f1a == 3 && g_7090[n].fcd == idx)
            type = 0;
        else if (g_9320 == 7)
            type = 0;
        else {
            for (i = 0; i < 3; i++) {
                if (g_4eec[k][i] == -1) {
                    g_4eec[k][i] = g_7090[idx].fd6;
                    g_4fd0[k][i] = g_91f8;
                    if (g_7090[n].fd6 != -1)
                        g_6b10[k][i] = g_6e24[g_7090[n].fd6].f00;
                    else
                        g_6b10[k][i] = g_4ed8[g_7090[n].f5e];
                    found = 1;
                    break;
                }
            }
            if (!found) {
                g_4eec[k][0] = g_7090[idx].fd6;
                g_4fd0[k][i] = g_91f8;
                if (g_7090[n].fd6 != -1)
                    g_6b10[k][i] = g_6e24[g_7090[n].fd6].f00;
                else
                    g_6b10[k][i] = g_4ed8[g_7090[n].f5e];
            }
        }
        if (n == g_9646)
            return;
        if (idx == n)
            fn_03_06ec(g_9646, 14, n, 0x89);
        else if (idx == g_9646) {
            if (g_96f0[g_7090[n].f4e].f1a == g_96f0[g_7090[g_9646].f4e].f1a && !quiet)
                fn_03_06ec(g_9646, 14, n, 0x63);
            else if (!quiet)
                fn_03_06ec(g_9646, 14, n, 0x5f);
        } else if (g_96f0[g_7090[n].f4e].f1a == g_96f0[g_7090[g_9646].f4e].f1a) {
            g_7090[n].f06 = 14;
            g_7090[n].f08 = idx;
            if (!quiet)
                fn_03_06ec(g_9646, 14, n, 0x60);
        } else {
            g_7090[n].f06 = 14;
            g_7090[n].f08 = idx;
            if (!quiet)
                fn_03_06ec(g_9646, 14, n, 0x61);
        }
    } else {
        if (n == g_9646)
            return;
        g_7090[n].f06 = type;
        g_7090[n].f08 = idx;
        fn_03_06ec(g_9646, 14, n, 0x62);
    }
}

/* Racer n may shout a taunt/warning message (0x406-0x415) [inferred]. */
/* @addr 4:79ae */
void far fn_04_79ae(int n)
{
    int i;
    int sel;
    int a;
    int b;
    int msg;
    int msg2;
    int flag;

    if (g_7090[n].fe7 == 0 && g_7090[n].fe9 == 0)
        return;
    msg = 0;
    if (g_7090[n].fe9 && (g_7090[n].fac == 0 || g_7090[n].fac == 0))  /* sic: same test twice */
        return;
    if (g_7090[n].fe7 && g_7090[n].f1e < 100)
        return;
    if (g_7090[n].f10 != 0 || g_7090[n].fe8 != 0)
        flag = 0;
    else
        flag = 1;
    sel = -1;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f18 == 0 && i != n && g_7090[i].f32 == 14 && g_7090[i].f34 == n
            && g_7090[i].f38 == 1
            && fn_08_285a(&a, &b, g_1df8[14][i].f04, g_1df8[14][n].f04) < 500)
            sel = i;
    }
    if (!flag && g_7090[n].f38 == 2
        && fn_08_285a(&a, &b, g_1df8[14][n].f04,
                      g_1df8[g_7090[n].f32][g_7090[n].f34].f04) < 150) {
        if (g_7090[n].fe9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x410;
    }
    if (flag && sel == -1 && g_96f0[g_7090[n].f4e].f1a != 3)
        return;
    if (!flag && sel == -1 && rand() % 3 == 0 && g_96f0[g_7090[n].f4e].f1a != 3) {
        if (g_7090[n].fe9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x411;
    } else if (flag && sel != -1 && (rand() % 5 == 0 || g_7090[n].f13e[sel] < -1)
               && g_7090[n].f13e[sel] < 2) {
        if (g_7090[n].fe9) {
            if (fn_11_4b00(n))
                msg = 0x406;
        } else {
            if (fn_11_4c72(n))
                msg = 0x407;
        }
        msg2 = 0x412;
    } else if (flag && g_96f0[g_7090[n].f4e].f1a == 3 && sel == -1 && g_7090[n].f38 == 1
               && g_7090[n].f32 == 14 && rand() % 4 <= 2 && g_7090[n].f13e[sel] < 2) {
        if (g_7090[n].fe9) {
            if (fn_11_4b00(n))
                msg = 0x406;
        } else {
            if (fn_11_4c72(n))
                msg = 0x407;
        }
        msg2 = 0x413;
    } else if (!flag && sel == -1 && g_7090[n].f38 != 1) {
        if (g_7090[n].fe9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x414;
    } else if (!flag && g_7090[n].f13e[sel] > 2) {
        if (g_7090[n].fe9) {
            if (fn_11_4b00(n))
                msg = 0x408;
        } else {
            if (fn_11_4c72(n))
                msg = 0x409;
        }
        msg2 = 0x415;
    }
    if (n == g_9646 && msg)
        fn_03_332e(msg, msg2);
}

/* Scores object (type, idx) as a goal for the player's racer; sets
 * g_9686 / g_9688 / g_968a as hints for the chosen approach [inferred].
 * flag is unused. */
/* @addr 4:8626 */
int far fn_04_8626(int type, int idx, int flag)
{
    int unused;
    int v;
    int k;
    int dx;
    int dy;
    int dist;
    int heading;
    int ang;
    int rel;
    int c16;
    int c18;
    int c1a;
    int i;
    long speed;
    long cosv;
    long appr;
    long vx;
    long vy;
    long closing;
    int near_;

    k = 10;
    g_968a = v = 0;
    near_ = g_9686 = g_8e28 + 2000 > g_1e50;
    if (g_7090[g_9646].f38 == 1 && g_8e28 + 3000 > g_1e50
        && g_7090[g_9646].f32 == type && g_7090[g_9646].f34 == idx)
        near_ = g_9686 = 1;
    v = g_9688 = 0;
    if (type == 14 || g_1df8[type][idx].f53 != 0)
        v = 30;
    else if (type == 9 || (type == 8 && g_3d5a[idx].f12 == 2)
             || (type == 2 && g_52fe[idx].f00 == 15))
        v = 20;
    else if (type == 5)
        v = -200;
    if (v != 0 && near_ != 0)
        v += 25;
    dist = fn_08_285a(&dx, &dy, g_1df8[type][idx].f04, g_1e30[g_9646].f04);
    heading = g_1e30[g_9646].f28;
    ang = fn_08_19b0(-dx, -dy);
    rel = (heading - ang) * 360 / 16;
    cosv = fn_06_720c(rel);
    vx = g_1e30[g_9646].f0c;
    vy = g_1e30[g_9646].f0e;
    speed = fn_08_35d0(vx, vy);
    closing = -((dx * vx + dy * vy) / dist);
    appr = closing * 128 / speed;
    c16 = c18 = c1a = 0;
    if (type == 14) {
        for (i = 0; i < 5; i++) {
            if (g_7090[idx].f44[i] != 0) {
                c1a++;
                if (g_1e68 / 10 - g_7090[idx].f44[i] < 36)
                    c16++;
                if (g_1e68 / 10 - g_7090[idx].f44[i] < 300)
                    c18++;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            if (g_938a[i] == type && (g_9392[i] == idx || type == 3) && g_937a[i] != 0) {
                c1a++;
                if (g_1e68 / 10 - g_937a[i] < 36)
                    c16++;
                if (g_1e68 / 10 - g_937a[i] < 300)
                    c18++;
            }
        }
    }
    if (near_) {
        v += ((c18 - 3) * 2 + c1a) * 4 + cosv / 2 + appr / 8 + c16 * 11;
        if (c1a == 0)
            v -= 30;
        if (c1a == 1)
            v -= 15;
        if (c18 == 0)
            v -= 15;
    } else {
        v += (int)(appr / 3 + cosv / 5) + c18 * 2 + c16 * 3 + c1a;
        if (type == 12 && appr > 75 && cosv > 75)
            v += (int)(appr / 3 + cosv / 5) + 10;
        if (appr > 105 || cosv > 105 || (appr > 80 && cosv > 80)
            || (appr > 55 && cosv > 55 && g_1df8[type][idx].f53 == 1)) {
            if (dist < 360) {
                g_9688 = 1;
                if (g_1df8[type][idx].f53 == 1)
                    v += (int)(appr / 3 + cosv / 5);
            }
        }
    }
    if (appr < -60 && cosv < -70 && closing < -30 && type == 14
        && g_7090[idx].f32 == 14 && g_7090[idx].f34 == g_9646
        && (g_7090[idx].f38 == 1
            || (g_7090[idx].f52 >= 2 && g_7090[idx].f52 <= 4
                && g_7090[idx].f54 == 14 && g_7090[idx].f56 == g_9646))) {
        g_968a = 1;
        near_ = 0;
        v += 25 - closing;
    }
    v += type == 12 ? dist / -7 + 55 : dist / -10 + 40;
    if (g_7090[g_9646].f06 == type && g_7090[g_9646].f08 == idx && v > 0)
        k = 12;
    if (g_7090[g_9646].f52 >= 2 && g_7090[g_9646].f52 <= 4
        && g_7090[g_9646].f54 == type && g_7090[g_9646].f56 == idx)
        v += 15;
    if (type == g_6e54 && idx == g_6e52)
        v += 30;
    v = k * v / 10;
    return v;
}

/* Chooses the player's autopilot goal (f06/f08/f36) [inferred]; pt and j
 * are dead stores kept for the code shape. */
/* @addr 4:59bc */
int far fn_04_59bc(void)
{
    int v;
    int i;
    POINT pt;
    int j;
    char pad1[28];
    int best;
    int flag;
    int s9686;
    int s968a;
    int s9688;
    char pad2[166];
    int type;
    int idx;
    char pad3[88];
    long dt1;
    long dt2;
    long dt3;
    int btype;
    int bidx;


    dt1 = g_1e50 - g_52d8;
    dt2 = g_1e50 - g_8e44;
    dt3 = g_1e50 - g_8e28;
    flag = 1;
    if (g_7090[g_9646].f52 == 1) {
        for (i = 0; i <= g_9316; i++)
            if (g_7090[i].f32 == g_7090[g_9646].f54 && g_7090[i].f34 == g_7090[g_9646].f56)
                flag = 0;
    }
    fn_04_84de();
    if (g_7090[g_9646].f52 >= 2 && g_7090[g_9646].f52 <= 4) {
        flag = 0;
        if (g_7090[g_9646].f06 == g_7090[g_9646].f54
            && (g_7090[g_9646].f08 == g_7090[g_9646].f56
                || (g_7090[g_9646].f06 == 9 && rand() % 5 == 1))
            && g_7090[g_9646].f36 == 1) {
            g_7090[g_9646].f52++;
            if (g_7090[g_9646].f54 == 14
                && g_1e68 / 10 - g_7090[g_7090[g_9646].f56].f44[2] < 40)
                g_7090[g_9646].f52 = 4;
            if (g_7090[g_9646].f52 >= 4) {
                if (g_7090[g_9646].f58 != g_9646)
                    fn_13_7b40(g_7090[g_9646].f58);
                else {
                    type = g_7090[g_9646].f54;
                    idx = g_7090[g_9646].f56;
                    if (type == 14 && g_7090[idx].f52 == 2 && g_7090[idx].f56 == g_9646
                        && g_7090[idx].f58 == idx)
                        fn_03_06ec(g_9646, type, idx, 0x1f);
                }
                g_7090[g_9646].f52 = 0;
            }
        }
    }
    if (g_7090[g_9646].f52 != 0) {
        if ((g_7090[g_9646].f98 + 20000 < g_1e50
             && g_1e68 / 10 - g_7090[g_7090[g_9646].f56].f44[0] > 25) || flag)
            g_7090[g_9646].f52 = -1;
    }
    if (g_7090[g_9646].f52 == -1)
        g_7090[g_9646].f52 = 0;
    pt = g_1df8[14][g_9646].f04;
    best = -40;
    j = 0;
    for (i = 0; i < g_9146; i++) {
        if (g_507c[i] == 14 && g_50e0[i] == g_9646)
            continue;
        v = fn_04_8626(g_507c[i], g_50e0[i], 1);
        if (v > best) {
            best = v;
            btype = g_507c[i];
            bidx = g_50e0[i];
            s9686 = g_9686;
            s968a = g_968a;
            s9688 = g_9688;
        }
    }
    for (i = 0; i < g_9318; i++) {
        v = fn_04_8626(12, i * 2 + 1, 1);
        if (v > best) {
            best = v;
            btype = 12;
            bidx = i * 2 + 1;
            s9686 = g_9686;
            s968a = g_968a;
            s9688 = g_9688;
        }
    }
    g_9686 = s9686;
    if (best > 0 || (s9686 == 0 && best > -40)) {
        g_7090[g_9646].f06 = btype;
        g_7090[g_9646].f08 = bidx;
        g_7090[g_9646].f3a = 2;
        if (g_9686 == 0 && btype == 14
            && ((g_7090[bidx].f44[1] != 0 && g_1e68 / 36 - g_7090[bidx].f44[1] < 10)
                || g_7090[bidx].fc2[g_9646] > 2))
            g_9686 = 1;
        if (g_9686)
            g_7090[g_9646].f36 = 1;
        else if ((g_1df8[btype][bidx].f53 || btype == 12) && s9688)
            g_7090[g_9646].f36 = 2;
        else if (s968a) {
            g_7090[g_9646].f36 = 4;
            g_7090[g_9646].f3a = 5;
        } else
            g_7090[g_9646].f36 = 3;
        return best;
    }
    g_7090[g_9646].f3a = 0;
    g_7090[g_9646].f06 = 8;
    g_7090[g_9646].f08 = 0;
    g_7090[g_9646].f36 = 3;
    g_7090[g_9646].f3a = 2;
    return 0;
}

/* Racer n looks for a rival j to gang up on (f52 = 1, f54 = 14, f56 = j)
 * [inferred]. */
/* @addr 4:485c */
void far pascal fn_04_485c(int n, int unused)
{
    int j;
    int i;
    int thr;
    int d;
    int a;
    int b;
    int c1;
    int sel;
    int c2;
    int skip;
    int score;

    sel = -1;
    if (g_96f0[g_7090[n].f4e].f1a == 7)
        return;
    if (g_96f0[g_7090[n].f4e].f1a == 6)
        return;
    for (j = 0; j <= g_9316; j++) {
        if (g_1df8[14][j].f18 == 0 && j != n && g_7090[j].fec) {
        for (i = skip = 0; i <= g_9316; i++) {
            if ((g_7090[i].f52 == 5 || g_7090[i].f52 == 1) && g_7090[i].f56 == j) {
                skip = 1;
                break;
            }
        }
        if (g_96f0[g_7090[n].f4e].f1a == 3 && g_96f0[g_7090[j].f4e].f1a != 3)
            skip = 1;
        if (g_7090[n].fc2[j] > 0)
            skip = 1;
        if (g_7090[n].fee[j] > 0 && g_7090[n].fee[j] <= 5)
            skip = 1;
        if (g_7090[j].f32 == 14 && g_7090[j].f34 == n && g_7090[j].f38 == 1)
            skip = 1;
        for (i = 1; i <= 5; i++)
            if (g_7090[n].ff7[j][i - 1] > 5)
                skip = 1;
        if (!skip) {
            thr = 10;
            score = 0;
            if (g_7090[j].f26 < 50)
                score = 1;
            if (g_7090[j].f38 == 4)
                score++;
            for (i = c2 = c1 = 0; i <= g_9316; i++) {
                if (g_1df8[14][i].f18 == 0 && i != n && i != j && g_7090[i].fec
                    && g_7090[i].f32 == 14 && g_7090[i].f34 == j && g_7090[i].f38 == 1) {
                    thr += fn_13_2688(n, i) / 45;
                    if (fn_04_5d9c(j, i) < ++c1 * 40)
                        sel = j;
                }
                if (fn_13_2688(i, j) < -50 && i != j && g_7090[i].fec)
                    c2++;
            }
            if (sel != -1)
                score++;
            if (c1 > 1)
                score++;
            if (c1 != 0)
                score++;
            if (g_7090[n].f5e + g_7090[n].f5d < 3)
                score++;
            if (score > 1) {
                d = fn_08_285a(&a, &b, g_1df8[14][n].f04, g_1df8[14][j].f04);
                if (d < 1000)
                    thr -= 10;
                if (g_96f0[g_7090[j].f4e].f1a == g_96f0[g_7090[n].f4e].f1a
                    || g_96f0[g_7090[n].f4e].f1a == 4)
                    thr -= 15;
                thr += g_7090[n].f5d * 4;
                if (fn_13_2688(n, j) >= thr * 10) {
                    for (i = 0; i < g_940a; i++)
                        if (g_52fe[i].f00 == 15 && g_52fe[i].f0a == 14 && g_52fe[i].f0c == j)
                            c1++;
                    if (c2 + c1 > 0) {
                        if (c1 > 2)
                            sel = j;
                        if (g_7090[j].f28 < c1 * 9 + 14 || g_7090[j].f2a < c1 * 9 + 14)
                            sel = j;
                        if (c2 * 4 + c1 * 10 + 21 > g_7090[j].f26)
                            sel = j;
                        if (fn_13_2688(n, j) >= ((thr += 15) - c1 * 6) * 10 && c1) {
                            if (g_7090[j].f5e > 0 && g_7090[j].f5d < 3) {
                                if (c1 > 1)
                                    sel = j;
                                if (g_7090[j].f28 < 30 || g_7090[j].f2a < 30)
                                    sel = j;
                                if ((g_7090[j].f26 < 45 || fn_13_2688(n, j) > (thr + 12) * 10)
                                    && j == g_9646)
                                    sel = j;
                            }
                        } else if (c2 > 2 && g_7090[j].f26 < 35
                                   && fn_13_2688(n, j) > (thr + 10) * 10)
                            sel = j;
                    }
                }
                if (sel >= 0 && fn_13_78b8(n, j) >= -1) {
                    g_7090[n].fed = 1;
                    g_7090[n].f52 = 1;
                    g_7090[n].f54 = 14;
                    g_7090[n].f56 = j;
                    g_7090[n].f58 = n;
                    g_7090[n].f98 = g_1e50 + 18000;
                    g_7090[n].f94 = g_1e50 + 300;
                    return;
                }
            }
        }
        }
    }
}
