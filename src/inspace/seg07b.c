/* INSPACE.EXE segment 7 (selector 1030), first source file: 7:0000-7:2206
 * (files.tsv group 13). */
#include "inspace.h"
#include <stdlib.h>
#include <mmsystem.h>

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    int f00;
    int f02;
    POINT f04;                  /* +4 */
    char p08[0x0c - 0x08];
    int f0c;                    /* +c */
    int f0e;                    /* +e */
    int f10;                    /* +10 */
    int f12;                    /* +12 */
    char p14[0x18 - 0x14];
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
    char p2f[0x3a - 0x2f];
    HDC f3a;                    /* +3a */
    HDC f3c;                    /* +3c */
    char p3e[0x44 - 0x3e];
    int f44;                    /* +44 */
    char p46[0x51 - 0x46];
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
    char p02[0x06 - 0x02];
    int f06;
    char p08[0x0a - 0x08];
    char f0a;
    char f0b;
    char p0c[0x23 - 0x0c];
} REC_23;
#pragma pack()

typedef struct {                /* 0x15a bytes, DGROUP array at DS:7090 */
    char p00[0x06];
    int f06;                    /* +6 */
    int f08;                    /* +8 */
    int f0a;                    /* +a */
    char p0c[0x10 - 0x0c];
    int f10;                    /* +10 */
    char p12[0x24 - 0x12];
    int f24;                    /* +24 */
    char p26[0x2e - 0x26];
    int f2e;                    /* +2e */
    char p30[0x32 - 0x30];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    int f3a;                    /* +3a */
    int f3c;                    /* +3c */
    char p3e[0x44 - 0x3e];
    int f44;                    /* +44 */
    char p46[0x4e - 0x46];
    int f4e;                    /* +4e */
    int f50;                    /* +50 */
    int f52;                    /* +52 */
    char p54[0x56 - 0x54];
    int f56;                    /* +56 */
    int f58;                    /* +58 */
    char p5a[0x5e - 0x5a];
    char f5e;                   /* +5e */
    char p5f;
    char f60;                   /* +60 */
    char p61[0x88 - 0x61];
    DWORD f88;                  /* +88 */
    char p8c[0xb8 - 0x8c];
    char fb8[0xc2 - 0xb8];      /* +b8 */
    char fc2[0xcb - 0xc2];      /* +c2, per object */
    char fcb;                   /* +cb */
    char pcc[0xd0 - 0xcc];
    int fd0;                    /* +d0 */
    char pd2[0xe4 - 0xd2];
    char fe4;                   /* +e4 */
    char pe5[0xe9 - 0xe5];
    char fe9;                   /* +e9 */
    char fea;                   /* +ea */
    char feb;                   /* +eb */
    char fec;                   /* +ec */
    char fed;                   /* +ed */
    char pee[0xfd - 0xee];
    char ffd[0x13e - 0xfd];     /* +fd, [object * 9] */
    char f13e[0x156 - 0x13e];   /* +13e, per object */
    DWORD f156;                 /* +156 */
} REC_15A;

typedef struct { int f0, f2, f4, f6; char rest[0x1e - 8]; } REC_1E;


extern REC_70 far *g_1df8[16];
extern REC_70 far *g_1e30;     /* = g_1df8[14] */
extern int g_3a02;
extern int g_3a28;
extern int g_952e;
extern int g_9646;
extern int g_90ea;
extern int g_90ec;
extern int g_0a76;
extern int g_9208;
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
extern DWORD g_1e64;
extern DWORD g_1e50;
extern DWORD g_1e8c;
/* order g_0586, g_9004, g_914c and g_1e50 before g_1e8c: operand choice in 7:2206 */
extern int g_0586;
extern int g_9004;
extern int g_914c;
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

/* 0x5a-byte records at DS:221c, 4 of them [inferred: active dissolves]. */
typedef struct {
    char b[80];
    int type;                   /* +50, -1 = free */
    int idx;                    /* +52 */
    int r;                      /* +54 */
    int sq;                     /* +56 */
    int f58;                    /* +58 */
} REC_5A;
extern REC_5A g_221c[4];
extern int dissolve_active_count;   /* DS:9148 */
extern int g_92a4;
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
extern int g_1de4;
extern int g_1de6;
extern HINSTANCE g_8e66;
extern HWND g_0a7c;

/* 20-byte records at DS:1e90 [inferred]. */
typedef struct {
    int f0;
    char p2[4];
    int f6;
    int f8;
    char pa[0x14 - 0x0a];
} REC_14B;
extern REC_14B g_1e90[];
extern int g_9434;
extern int g_951a;
extern int g_9e49;
extern int g_3a38;
extern RECT g_1e5c;
extern HDC g_39e8[];
extern int subgame_active;              /* DS:9130 */
extern int hazards_ship_redraw_pending; /* DS:058a */

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    char p00[0x1a];
    int f1a;                    /* +1a */
    char p1c[0x24 - 0x1c];
    int f24;                    /* +24 */
    char p26[0xad - 0x26];
} REC_AD;
#pragma pack()
extern REC_AD g_96f0[];
extern int g_9318;
extern int g_9140;
extern int g_9320;
extern int g_668a;
extern int g_094e;
extern int g_0950;
void far fn_08_0000(void);
void far fn_12_2556(int type, int idx);
void far command_watch_ship(int a, int b);   /* 13:563c */

void far pascal fn_08_1d54(int a, int b);
void far pascal fn_08_1b54(int a, int b);
void far fn_07_233c(int a, int b, int c);
void far fn_07_5a46(void);
void far fn_07_63f2(void);
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
void far fn_08_99ce(int a, int b, int c, int d, int e);
void far fn_13_6450(int a, int b, int c);
void far fn_13_58dc(int a, int b);
void far fn_13_5a6a(HDC dc, int a, int b, int c, int d, int e, int f, int g);
void far fn_02_170e(void);
void far fn_07_2080();          /* old-style: 7:158e passes (type, idx) */
void far fn_12_3778(void);
void far fn_12_26a4(int type, int idx);
void far fn_03_06ec(int n, int kind, int target, int d);
void far fn_10_a332(LPSTR out, int id, int n, ...);
extern long g_05c0;
extern long g_1e58;
extern DWORD g_1e68;
extern int g_937a[8];
extern char g_938a[8];
extern char g_9392[8];
extern HDC g_929e;
extern HDC g_9580;
typedef struct { int f00; char p02[0x08 - 0x02]; int f08; char p0a[0x1c - 0x0a]; } REC_1C;
extern REC_1C g_66e4[];
typedef struct { char p00[0x26]; int f26; char p28[0x50 - 0x28]; } REC_50;
extern REC_50 g_2f4c[];


/* Used by 7:0000 (main per-tick dispatcher [inferred]). */
extern int g_001a;
extern int g_0022;
extern DWORD g_1e54;
extern int g_9132;
extern int g_058e;
extern int g_912e;
extern DWORD g_2214;
extern DWORD g_2218;
extern DWORD g_05c4;
extern DWORD g_05c8;
extern int g_965e;
extern int g_913a;
extern int g_8f6c;
extern int g_13de;
extern int g_968e;
extern DWORD g_1e84;
extern DWORD g_1e80;
extern int g_8e62;
extern int g_8e64;
extern LPARAM g_1d38;
extern int g_9144;
extern int g_9294;
extern int g_0d1e;
extern int g_1212;
extern int flow_interactive;            /* DS:95bc */
extern DWORD g_05ac;
extern DWORD g_1e70;
extern DWORD g_1e74;
extern DWORD g_1e78;
extern DWORD g_1e7c;
extern int g_9002;
extern int g_8e60;
extern HRGN g_0012;
extern int g_8f76;
extern DWORD g_1e88;
extern int g_93a4;
extern int g_929c;
extern int g_0d26;
extern int g_9516;
extern int g_920c;
extern DWORD g_05b4;
extern DWORD g_05b0;
extern int g_1038;
extern int g_1032;
extern DWORD g_05bc;
extern int g_9138;
extern DWORD g_05a8;
extern int g_1048;
extern DWORD g_1e6c;
extern int g_92f0;
extern int g_914e;
extern DWORD g_05a4;
extern DWORD g_05b8;
extern int g_9136;
extern int g_0598;
extern int g_0594;
extern DWORD g_05cc;
extern int g_9430;
extern int g_059c;
extern int g_059e;
extern int g_17b6;
extern int g_8ff4;
extern DWORD g_2388;
extern int g_103c;
extern int g_9146;
extern DWORD g_870c;
extern int g_9608;
extern DWORD g_17b8;
extern REC_70 far *g_1e14;     /* = g_1df8[7] */
extern DWORD g_6da8;
extern int g_05d2;
extern int g_1016;
extern int g_913c;
extern int g_9600;
extern DWORD g_2384;
extern int g_92e8;
extern int g_0588;
extern int g_238c;
extern int g_913e;
extern int g_94b2;
extern DWORD g_8714;
extern int g_0596;

int far fn_16_619e(void);
void far fn_09_0d6c(void);
void far fn_11_785e(int msg, int key, long lparam);
void far fn_16_0cfe(int a);
void far fn_16_6928(int a);
void far fn_06_5d58(void);
void far fn_16_7210(int a);
void far fn_11_7902(int msg, int key, long lparam);
void far fn_06_1e68(int start);
void far fn_15_5962(int a);
void far fn_09_60bc(void);
void far fn_13_4eca(LPSTR s);
void far fn_06_0f1a(int n, char far *buf);
void far fn_11_7bbc(int msg, int key, long lparam);
void far fn_17_0000(int a, int b);
void far fn_09_5cca(void);
void far fn_06_1c72(int a);
void far fn_11_7b7a(int msg, int key, long lparam);
void far fn_09_6dec(int a);
void far fn_11_78bc(int msg, int key, long lparam);
void far fn_06_626c(void);
void far fn_11_7b30(int msg, int key, long lparam);
void far fn_06_5f7a(int a);
void far pascal fn_11_6aa8(int msg, int wparam, long lparam);
void far fn_16_32a0(void);
int far fn_06_92b8(void);
void far fn_09_2828(void);
int far fn_06_885c(int ask, int mode);
void far fn_16_68d6(HWND hwnd, int id, int id2);
void far fn_09_6bc2(void);
void far fn_02_0ba4(void);
void far fn_11_aece(void);
void far fn_11_1bcc(void);
void far fn_11_0894(void);
void far fn_11_3396(void);
void far fn_11_4db0(void);
void far fn_08_9464(void);
void far fn_08_9564(void);
int far pascal fn_08_3aec(int n, int s);
void far pascal fn_08_3fbe(int i);
void far fn_07_375a(void);
void far fn_11_72b2(void);
void far fn_11_7504(void);
void far fn_16_64fa(void);
void far fn_10_7f88(void);
void far pascal fn_08_158a(int still);
void far fn_08_4e14(void);
void far fn_07_3a42(int n);
void far fn_13_24aa(int w);
void far fn_16_00a2(void);
int far fn_16_33a2(void);
void far fn_16_3306(void);
void far fn_11_a9ea(int a);
void far fn_10_7b48(void);
void far fn_12_4d8e(void);
void far fn_18_0d94(void);
void far fn_13_0000(void);
void far fn_07_3bae(void);
void far fn_12_532c(void);
void far fn_12_633e(void);
void far fn_08_8256(void);
void far fn_07_309c(void);
void far fn_07_32d0(void);
void far fn_07_40c4(void);
void far fn_12_0000(void);
int far fn_06_73f6(void);
int far fn_06_7c14(void);
void far fn_07_5e04(void);
void far fn_12_3148(void);
void far fn_12_6b1e(void);
void far fn_12_0ae4(void);
void far fn_12_3e98(int i);
void far fn_13_ba04(void);
void far fn_13_b93a(void);
void far fn_13_6716(int n);
int far fn_18_5cec(void);
int far fn_13_adbe(int a, int b, int c);   /* summon_with_music [inferred] */
void far fn_12_6d64(int n, int k);
int far fn_04_59bc(void);
void far fn_13_7b40(int n);
void far fn_13_2714(int a, int b, int c, int d, int e, int f);
void far fn_04_6700(int n);
void far fn_08_9ab8(void);
void far fn_13_3302(void);
void far fn_04_7e2a(void);
void far fn_04_83ae(void);
void far fn_08_9b4e(void);
void far pascal fn_13_2f30(int n);
void far fn_13_447a(void);
void far fn_12_515e(void);
void far fn_07_119c();          /* old-style: 7:0000 passes two arguments */
void far fn_07_1208(void);
void far fn_07_158e(void);
void far fn_07_1d0c(void);
void far fn_07_1f38(void);
void far fn_07_2128(void);
void far fn_07_2206(void);

/* Main per-tick dispatcher on the game state g_90f4 [inferred]. */
/* @addr 7:0000 */
void far fn_07_0000(void)
{
    int i;
    int j;
    int r;
    int skip;
    char buf[34];
    int res;
    char text[144];
    char title[30];

    if (g_001a)
        return;
    g_0022 = 1;
    g_1e50 = GetCurrentTime();
    if (g_1e50 > g_1e54 && !g_9132) {
        res = GetFreeSystemResources(GFSR_GDIRESOURCES);
        if (res <= 10 && g_058e) {
            fn_10_a332(text, 0xbe3, 1, res);
            fn_10_a332(title, 0x9ed, 1);
            MessageBox(g_0016, text, title, MB_ICONEXCLAMATION);
            g_058e = 0;
        } else if (res > 40)
            g_058e = 1;
        g_1e54 += 5000;
    }
    if (g_912e)
        g_2214 = timeGetTime();
    if (g_965e && !g_913a)
        fn_16_619e();
    if (g_8f6c) {
        g_13de = 1;
        g_8f6c = 0;
        g_968e = 0;
        g_1e84 = 0;
        g_1e80 = 0;
        fn_09_0d6c();
    }
    switch (g_90f4) {
    case 6:
        g_0022 = 0;
        if (g_8e62)
            fn_11_785e(g_8e62, g_8e64, g_1d38);
        skip = 0;
        if (g_952c && g_9530 == 1 && g_912e) {
            if (g_2218 + g_05c4 < g_2214)
                g_9144 = g_9004;
            else if (g_2218 + g_05c8 > g_2214)
                skip = 1;
        }
        g_9144++;
        if (skip)
            break;
        if (g_9144 < g_9004)
            break;
        fn_07_2206();
        g_2218 = g_2214;
        g_9144 = 0;
        fn_16_0cfe(0);
        break;
    case 8:
        g_0022 = 0;
        g_9144++;
        if (g_9144 < g_9004)
            break;
        fn_07_2206();
        g_9144 = 0;
        fn_16_6928(0);
        break;
    case 9:
        g_0022 = 0;
        if (g_1e84 && g_1e84 <= g_1e50) {
            g_1e84 = 0;
            fn_06_5d58();
            break;
        }
        g_9144++;
        if (g_9144 < g_9004)
            break;
        fn_07_2206();
        g_9144 = 0;
        fn_16_7210(0);
        break;
    case 0:
        if (g_9294)
            g_0022 = 0;
        if (g_8e62)
            fn_11_7902(g_8e62, g_8e64, g_1d38);
        if (g_0d1e && g_9134 && !flow_interactive) {
            fn_06_1e68(0);
            break;
        }
        skip = 0;
        if (g_912e && g_1212) {
            if (g_2218 + 14 < g_2214)
                g_9144 = g_9004;
            else if (g_2218 + 13 > g_2214)
                skip = 1;
        }
        g_9144++;
        if (skip)
            break;
        if (g_9144 < g_9004)
            break;
        if (g_1212)
            fn_07_2206();
        g_2218 = g_2214;
        g_9144 = 0;
        fn_15_5962(0);
        break;
    case 3:
        if (g_05ac && g_05ac <= g_1e50) {
            g_05ac = 0;
            fn_09_60bc();
            fn_13_4eca("iMainSmart = ");
            fn_06_0f1a(g_9646, buf);
            fn_13_4eca(buf);
            fn_13_4eca("\n\r");
            break;
        }
        if (g_8e62)
            fn_11_7bbc(g_8e62, g_8e64, g_1d38);
        g_9144++;
        if (g_9144 < g_9004)
            break;
        fn_07_2206();
        g_9144 = 0;
        fn_17_0000(0, 0);
        break;
    case 2:
        if (g_0d1e && !flow_interactive) {
            fn_06_1e68(0);
            break;
        }
        if (g_1e70 && g_1e70 <= g_1e50) {
            g_1e70 = 0;
            fn_09_5cca();
            break;
        }
        if (g_1e74 && g_1e74 <= g_1e50) {
            fn_06_1c72(1);
            break;
        }
        if (g_8e62)
            fn_11_7b7a(g_8e62, g_8e64, g_1d38);
        g_9144++;
        if (g_9144 < g_9004)
            break;
        fn_07_2206();
        g_9144 = 0;
        fn_09_6dec(0);
        break;
    case 4:
        if (g_1e78 <= g_1e50) {
            g_13de = 1;
            g_968e = 0;
            break;
        }
        if (g_8e62)
            fn_11_78bc(g_8e62, g_8e64, g_1d38);
        break;
    case 5:
        if (g_1e7c <= g_1e50) {
            fn_09_0d6c();
            fn_06_626c();
            g_001a = 0;
            g_13de = 1;
            g_968e = 4;
            break;
        }
        if (g_8e62)
            fn_11_7b30(g_8e62, g_8e64, g_1d38);
        g_9144++;
        if (g_9144 < g_9002)
            break;
        g_9144 = 0;
        fn_06_5f7a(0);
        break;
    default:
        fn_13_4eca("Frame iMainSmart = ");
        fn_06_0f1a(g_9646, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
        if (g_8e60) {
            SelectClipRgn(g_13dc, g_0012);
            if (g_8e62)
                fn_11_6aa8(g_8e62, g_8e64, g_1d38);
            g_8e60 = 0;
            break;
        }
        fn_13_4eca("Before Timer iMainSmart = ");
        fn_06_0f1a(g_9646, buf);
        fn_13_4eca(buf);
        fn_13_4eca("\n\r");
        skip = 0;
        if (g_912e) {
            if (g_2218 + g_05c4 < g_2214)
                g_9144 = g_8f76;
            else if (g_2218 + g_05c8 > g_2214)
                skip = 1;
        }
        g_9144++;
        if (!subgame_active) {
            fn_13_4eca("AMB? iMainSmart = ");
            fn_06_0f1a(g_9646, buf);
            fn_13_4eca(buf);
            fn_13_4eca("\n\r");
            if (g_1e88 && g_1e88 <= g_1e50) {
                g_1e88 = 0;
                if (g_9646 == g_952e && !g_951a) {
                    g_90f4 = 6;
                    g_914a = 0;
                    fn_16_0cfe(1);
                    break;
                }
                fn_16_32a0();
            }
            if (g_1e80 && g_1e80 <= g_1e50) {
                if (!flow_interactive) {
                    if (g_69f4[g_94a2].f1d0 == 2 && g_0d26)
                        fn_06_92b8();
                    if (g_93a4) {
                        g_90f4 = 8;
                        g_929c = 0;
                        fn_16_6928(1);
                        break;
                    }
                    fn_09_2828();
                    if (g_7090[g_9646].fec && !g_9516)
                        fn_06_885c(0, 0);
                    fn_09_0d6c();
                    g_13de = 1;
                    g_968e = 0;
                } else {
                    if (g_9134 > 1)
                        g_9134 = 1;
                    if (!g_7090[g_9646].fec)
                        g_1e84 = g_1e50;
                    else
                        fn_09_6bc2();
                }
                g_1e80 = 0;
                break;
            }
            if (g_1e84 && g_1e84 <= g_1e50) {
                if (!g_920c)
                    fn_16_68d6(g_0016, 0x918, 0x919);
                g_1e84 = 0;
                fn_06_5d58();
                break;
            }
            if (g_05b4 && !flow_interactive && g_05b4 <= g_1e50 && g_9320 != 7) {
                g_7090[g_9646].f52 = 10;
                g_7090[g_9646].fed = 1;
            }
            if (g_05b0 && g_05b0 <= g_1e50) {
                g_05b0 = 0;
                fn_09_0d6c();
                break;
            }
            fn_13_4eca("Change Clip? iMainSmart = ");
            fn_06_0f1a(g_9646, buf);
            fn_13_4eca(buf);
            fn_13_4eca("\n\r");
            if (g_1038)
                fn_02_0ba4();
            fn_13_4eca("Change Persp? iMainSmart = ");
            fn_06_0f1a(g_9646, buf);
            fn_13_4eca(buf);
            fn_13_4eca("\n\r");
            if (g_1032)
                fn_11_aece();
            if (g_058c && !g_951a && g_05bc < g_1e50)
                fn_07_1f38();
            if (g_9138 || (g_9144 >= g_8f76 && g_8f76) || (!g_8f76 && g_05a8 % 3 == 0)) {
                g_9138 = 0;
                fn_11_1bcc();
                fn_11_0894();
                fn_11_3396();
            }
            SelectClipRgn(g_13dc, g_0012);
            if (g_8e62)
                fn_11_6aa8(g_8e62, g_8e64, g_1d38);
            if (g_001a)
                break;
            if (!g_1e30[g_9646].f18)
                fn_11_4db0();
            if (g_1048) {
                if (g_1e50 >= g_1e6c && g_92f0) {
                    g_1e6c = g_1e50 + 10000;
                    fn_08_9464();
                    g_914e = 0;
                }
                if (g_1e6c - 500 <= g_1e50 && !g_914e)
                    fn_08_9564();
            }
            if (!g_1df8[g_9324][g_9646].f18) {
                if (g_1e50 >= g_05a4)
                    g_05a4 = g_1e50 + 50;
                if (g_05b8 < g_1e50) {
                    g_05b8 = g_1e50 + 10000;
                    fn_07_2128();
                }
            }
            if (skip)
                break;
            if (g_9144 >= g_8f76) {
                for (j = g_9136 = 0; j < 5; j++) {
                    for (i = 0; i < g_0598 + g_0594; i++)
                        g_9136 = fn_08_3aec(i, j);
                    g_05cc++;
                }
                if (g_9430 > 0)
                    for (i = 0; i <= g_9434; i++)
                        fn_08_3fbe(i);
                fn_07_375a();
            }
        } else {
            if (g_8e62)
                fn_11_6aa8(g_8e62, g_8e64, g_1d38);
            if (g_001a)
                break;
            if (skip)
                break;
        }
        if (g_9144 < g_8f76)
            break;
        g_2218 = g_2214;
        g_9144 = 0;
        g_9142++;
        if (g_9142 > 54)
            g_9142 = 0;
        if (g_059c > 1000)
            g_8f76 = 0;
        else {
            g_914c++;
            if (g_1e50 > g_1e64) {
                if (!g_0592 && (g_059e + 1 < g_914c || g_059e - 1 > g_914c)) {
                    if (g_914c > g_059e && !g_8f76)
                        g_8f76 = 1;
                    g_8f76 = g_914c * g_8f76 / g_059e;
                }
                g_1e64 = g_1e50 + 250;
                g_914c = 0;
            }
        }
        g_0586++;
        if (g_1e50 > g_1e8c) {
            g_1e8c = g_1e50 + 1000;
            if (!g_0592 && g_059c < 1000 && g_059c + 9 > g_0586 && g_059c - 9 < g_0586) {
                if (g_059c < g_0586 && !g_8f76)
                    g_8f76 = 1;
                g_8f76 = g_8f76 * g_0586 / g_059c;
            }
            if (g_0592)
                g_0592--;
            g_059a = g_0586;
            if (g_0a76 == 4)
                PostMessage(g_0a7c, WM_PAINT, 0, 0L);
            g_0586 = 0;
        }
        g_17b6++;
        if (g_17b6 >= 8)
            for (i = g_17b6 = 0; i <= g_9316; i++)
                if (g_7090[i].f60)
                    g_7090[i].f60--;
        g_05a8++;
        g_1e68++;
        if (g_8ff4) {
            if (g_2388 < g_1e50) {
                g_2388 = g_1e50 + 50;
                fn_11_72b2();
            }
            fn_11_7504();
        }
        if (subgame_active) {
            fn_16_64fa();
            break;
        }
        if (g_103c) {
            fn_10_7f88();
            g_103c = 0;
        }
        fn_08_158a(0);
        fn_08_0000();
        if (g_9140)
            fn_07_1d0c();
        g_9146 = 0;
        fn_08_4e14();
        if (g_870c && g_1e50 > g_870c) {
            g_870c = 0;
            if (g_9608)
                fn_03_06ec(g_9646, 14, g_7090[g_9646].f58, 2);
            else
                fn_07_119c(2, 0);
        }
        fn_12_3778();
        for (i = 0; i < g_9406[0]; i++)
            if (g_1df8[0][i].f51)
                fn_07_3a42(i);
        if (g_17b8 < g_1e50) {
            g_17b8 = g_1e50 + 280;
            if (g_0a76 == 2)
                fn_13_24aa(0);
            else if (g_0a76 == 3)
                fn_13_24aa(1);
            if (g_95fc)
                fn_13_24aa(2);
        }
        if (!g_1e14->f18)
            fn_16_00a2();
        else if (g_1e50 > g_6da8 && g_6da8 && fn_16_33a2())
            fn_16_3306();
        g_05d2 = !g_05d2;
        if (g_1016)
            fn_11_a9ea(1);
        fn_10_7b48();
        if (g_9320 == 6)
            fn_12_4d8e();
        if (g_913a || g_913c)
            fn_18_0d94();
        fn_13_0000();
        fn_07_3bae();
        fn_12_532c();
        fn_12_633e();
        fn_08_8256();
        fn_07_309c();
        fn_07_32d0();
        fn_07_40c4();
        fn_12_0000();
        fn_06_73f6();
        fn_06_7c14();
        if (g_9456 > 0)
            fn_07_5e04();
        fn_12_3148();
        fn_12_6b1e();
        if (g_9600)
            fn_12_0ae4();
        fn_12_3e98(0);
        if (g_2384 < g_1e50 && !g_0950 && !g_094e && !g_92e8 && !subgame_active)
            fn_13_ba04();
        if (g_1e68 % 300 == 0)
            fn_13_b93a();
        if ((hazards_ship_redraw_pending || g_0588 || g_7090[g_9646].feb) && !g_951a) {
            if (!g_238c)
                fn_07_1208();
        } else if (g_7090[g_9646].f156 <= g_1e50) {
            if (!g_951a) {
                g_7090[g_9646].f156 = g_1e50 + 1500;
                fn_13_6716(g_9646);
                if (g_913e)
                    fn_18_5cec();
                if (!g_6da8 && g_952e >= 0 && g_9e49 >= 0 && g_9e49 < 9
                    && (g_9e49 >= 6 || (!g_1e88 && g_1e14->f18)))
                    g_6da8 = 1;
                for (i = 0; i <= g_9316; i++)
                    if (g_7090[i].feb && !g_1e30[i].f2e)
                        g_7090[i].feb = 0;
                if (g_9320 == 7)
                    fn_12_515e();
                if (g_92e8 && flow_interactive) {
                    g_9134 = 0;
                    if (g_94b2 && !g_9316 && g_1e68 > 100) {
                        fn_13_adbe(g_9646, 0x13, 0xb4);
                        for (i = 1; i < g_7090[g_9646].fcb; i++)
                            if (g_7090[g_9646].fb8[i] < 0x16)
                                fn_12_6d64(1, g_7090[g_9646].fb8[i]);
                        g_7090[1].f0a = g_7090[1].f24 = g_7090[g_9646].f0a;
                    }
                }
                if (!g_9134) {
                    r = fn_04_59bc();
                    g_7090[g_9646].f32 = g_7090[g_9646].f06;
                    g_7090[g_9646].f34 = g_7090[g_9646].f08;
                    g_7090[g_9646].f38 = g_7090[g_9646].f36;
                    g_7090[g_9646].f3c = g_7090[g_9646].f3a;
                    if (g_7090[g_9646].f32 == 9 && g_7090[g_9646].f38 == 1)
                        g_8714 = g_1e68;
                    if (g_7090[g_9646].f38 == 1
                        && (g_7090[g_9646].f52 == 1 || g_7090[g_9646].f52 == 5)
                        && !g_1e30[g_7090[g_9646].f56].f18) {
                        if (g_7090[g_9646].f32 == 14) {
                            if (g_7090[g_7090[g_9646].f34].f38 == 1
                                && g_7090[g_7090[g_9646].f34].f32 == 14
                                && g_7090[g_7090[g_9646].f34].f34 == g_7090[g_9646].f56)
                                fn_13_7b40(g_7090[g_9646].f56);
                        }
                    } else if (g_7090[g_9646].f32 == 14 && g_7090[g_9646].f38 == 1
                        && g_7090[g_7090[g_9646].f34].f38 == 1
                        && g_7090[g_7090[g_9646].f34].f32 == 14
                        && g_7090[g_7090[g_9646].f34].f34 != g_9646) {
                        g_0596++;
                        if (g_0596 > 1) {
                            fn_13_2714(g_7090[g_7090[g_9646].f34].f34, g_9646,
                                (10 - min(g_7090[g_7090[g_9646].f34].ffd[g_9646 * 9], 10)) * 2,
                                (10 - min(g_7090[g_7090[g_9646].f34].ffd[g_9646 * 9], 10)) * 5,
                                0, 7);
                            g_0596 = -4;
                        }
                    } else if (g_7090[g_9646].f32 != 14 || g_7090[g_9646].f38 == 1)
                        g_0596 = 0;
                    if ((g_7090[g_9646].f32 == 0 || g_7090[g_9646].f32 == 4 || g_7090[g_9646].f32 == 11)
                        && g_7090[g_9646].f38 == 2)
                        fn_04_6700(g_9646);
                }
                fn_08_9ab8();
                fn_13_3302();
                for (i = 0; i <= g_9324; i++)
                    if (g_9406[i] < 0 || g_92ec[i] < g_9406[i])
                        g_9406[i] = g_92ec[i];
                for (i = 0; i <= g_9316; i++) {
                    if (i != g_9646 && g_7090[i].fc2[g_9646] > 0 && g_7090[i].fc2[g_9646] < 20
                        && g_1e68 / 10 - g_7090[i].f44 > 60) {
                        g_7090[i].fc2[g_9646]--;
                        g_7090[i].f13e[g_9646] = g_7090[g_9646].f13e[i] = 0;
                    }
                    if (g_1df8[g_9324][i].f18 == 1 && g_96f0[g_7090[i].f4e].f1a == 7
                        && g_7090[i].f5e == 1) {
                        g_1df8[g_9324][i].f18 = 100;
                        g_7090[i].fec = 1;
                    }
                }
                fn_04_7e2a();
                fn_04_83ae();
                fn_08_9b4e();
            }
            fn_13_2f30(g_9646);
        }
        if (dissolve_active_count > 0)
            fn_07_158e();
        fn_13_447a();
        break;
    }
}

/* @addr 7:119c */
void far fn_07_119c(int a)
{
    g_0a76 = a;
    if (g_0a7c)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
}

/* @addr 7:11cc */
void far fn_07_11cc(void)
{
    g_1e30[g_9646].f00 = g_90ea / 2;
    g_1e30[g_9646].f02 = g_90ec / 2;
}

/* Updates the player ship sprite frame [inferred]. */
/* @addr 7:1208 */
void far fn_07_1208(void)
{
    int u1;
    int u2;
    int v;
    int idx;
    int i;
    int w;
    int h;
    int mode;
    int u3;

    if (g_90f4 != 1 || g_1e30[g_9646].f18 != 0 || g_951a || subgame_active)
        return;
    if (g_9e49 >= 3 && g_9e49 <= 6 && g_9646 == g_952e)
        return;
    if (!g_3a38)
        return;
    if (!g_7090[g_9646].fec)
        for (i = 0; i <= g_9434; i++)
            if (g_1e90[i].f6 == 14 && g_1e90[i].f8 == g_9646 && g_1e90[i].f0 > 0
                && g_1e90[i].f0 < 9)
                return;
    idx = g_9646;
    w = g_1e30[idx].f22;
    h = g_1e30[idx].f24;
    SetRect(&g_1e5c, g_1e30[idx].f00 + 2, g_1e30[idx].f02 + 2,
            g_1e30[idx].f00 + w - 2, g_1e30[idx].f02 + w - 2);
    mode = g_7090[idx].f10;
    u1 = g_7090[idx].fea;      /* never read: CL drops the store, keeps the load */
    v = (g_7090[idx].fe4 ? idx : g_7090[idx].f50) + 40;
    if (mode == 0 || mode == 7)
        g_1e30[g_9646].f10 = g_1e30[g_9646].f28 * (h + w) + h;
    else
        g_1e30[g_9646].f10 = w * 16 + h * 17;
    if (mode > 3)
        g_1e30[g_9646].f12 = h * 2 + w;
    else if (g_7090[idx].fe9)
        g_1e30[g_9646].f12 = h;
    fn_08_0b76((char)g_9646 | 0xe00, 1, g_39e8[v], 0);
    hazards_ship_redraw_pending = 0;
}

/* Starts a dissolve effect on an object [inferred]. */
/* @addr 7:13b2 */
void far fn_07_13b2(char kind, int type, int idx)
{
    int i;
    int j;
    int u;
    int sq;
    int r;
    int found;

    if (type < 0)
        MessageBeep(0);
    if (type <= 14) {
        if (g_1df8[type][idx].f2e > 0)
            return;
        fn_10_754a(0x27, type, idx, 1);
    }
    found = 0;
    if (type <= 14) {
        if (g_1df8[type][idx].f22 % ((2 << g_9156) >> 1) == 0)
            r = 0;
        else
            r = 1;
        r += g_1df8[type][idx].f22 >> g_9156;
    } else if (type == 20)
        r = g_92a4 / 8;
    else if (type >= 21)
        r = 24;
    sq = r * r;
    for (i = 0; i < 4; i++) {
        if (g_221c[i].type != -1)
            continue;
        if (type <= 14)
            g_1df8[type][idx].f2e = kind;
        g_221c[i].type = type;
        g_221c[i].idx = idx;
        g_221c[i].sq = sq;
        g_221c[i].f58 = 0;
        g_221c[i].r = r;
        if (type == 14)
            g_7090[idx].feb = 1;
        for (j = 0; j < 80; j++)
            g_221c[i].b[j] = 0;
        found = 1;
        dissolve_active_count++;
        if (kind == 2 && g_221c[i].type <= 14)
            PatBlt(g_1df8[g_221c[i].type][g_221c[i].idx].f3c, 0, 0,
                   g_1df8[g_221c[i].type][g_221c[i].idx].f24 * 2
                       + g_1df8[g_221c[i].type][g_221c[i].idx].f22,
                   g_1df8[g_221c[i].type][g_221c[i].idx].f24 * 2
                       + g_1df8[g_221c[i].type][g_221c[i].idx].f22,
                   BLACKNESS);
        break;
    }
    if (!found && type <= 14)
        PatBlt(g_13dc, g_1df8[type][idx].f00, g_1df8[type][idx].f02,
               g_1df8[type][idx].f22, g_1df8[type][idx].f22, BLACKNESS);
}

/* Advances the active dissolves by a few pixels each [inferred]. */
#define DOBJ(i) g_1df8[g_221c[i].type][g_221c[i].idx]
/* @addr 7:158e */
void far fn_07_158e(void)
{
    int i;
    int j;
    int pix;
    int y;
    int x;
    int k;
    int bit;
    int ok;
    char mask;
    char unused[44];            /* never used: frame size */
    int n;

    for (i = 0; i < 4; i++) {
        if (g_221c[i].type != -1) {
            if (g_221c[i].type <= 14)
                n = 10;
            else if (g_221c[i].type == 20)
                n = g_221c[i].sq / 9;
            else if (g_221c[i].type >= 21)
                n = 5;
            for (j = 0; j < n; j++) {
                do {
                    pix = rand() % g_221c[i].sq;
                    k = pix >> 3;
                    bit = pix & 7;
                    mask = 1 << bit;
                    ok = !(mask & g_221c[i].b[k]);
                } while (!ok);
                g_221c[i].b[k] |= mask;
                g_221c[i].f58++;
                if (g_221c[i].type <= 14) {
                    x = pix % g_221c[i].r << g_9156;
                    y = pix / g_221c[i].r << g_9156;
                } else if (g_221c[i].type == 20) {
                    x = pix % g_221c[i].r << 3;
                    y = pix / g_221c[i].r << 3;
                } else if (g_221c[i].type == 21) {
                    x = (long)(pix % g_221c[i].r) * g_90ea / g_221c[i].r;
                    y = (long)(pix / g_221c[i].r) * g_90ec / g_221c[i].r;
                } else if (g_221c[i].type == 22) {
                    x = (long)(pix % g_221c[i].r) * g_90ea / g_221c[i].r / 2;
                    y = (long)(pix / g_221c[i].r) * g_90ec / g_221c[i].r / 2;
                } else if (g_221c[i].type == 23) {
                    x = (long)(pix % g_221c[i].r) * g_90ea / g_221c[i].r / 2 + g_90ea / 2;
                    y = (long)(pix / g_221c[i].r) * g_90ec / g_221c[i].r / 2;
                } else if (g_221c[i].type == 24) {
                    x = (long)(pix % g_221c[i].r) * g_90ea / g_221c[i].r / 2 + g_90ea / 2;
                    y = (long)(pix / g_221c[i].r) * g_90ec / g_221c[i].r / 2 + g_90ec / 2;
                } else if (g_221c[i].type == 25) {
                    x = (long)(pix % g_221c[i].r) * g_90ea / g_221c[i].r / 2;
                    y = (long)(pix / g_221c[i].r) * g_90ec / g_221c[i].r / 2 + g_90ec / 2;
                }
                if (g_221c[i].f58 >= g_221c[i].sq) {
                    if (g_221c[i].type <= 14) {
                        if (DOBJ(i).f2e == 1) {
                            PatBlt(g_13dc, DOBJ(i).f00, DOBJ(i).f02, DOBJ(i).f22, DOBJ(i).f22,
                                   BLACKNESS);
                            if (g_221c[i].type == 14 && g_7090[g_221c[i].idx].f2e == 2) {
                                DOBJ(i).f2e = -2;
                                if (g_9134 && g_7090[g_9646].f32 == g_221c[i].type
                                    && g_7090[g_9646].f34 == g_221c[i].idx
                                    && g_7090[g_9646].f38 == 1) {
                                    g_05c0 = g_1e50 + 1200;
                                    fn_10_a332(g_8630, 0x58e, g_058c = 1);
                                }
                            } else {
                                DOBJ(i).f18 = 1;
                                fn_07_65aa(g_221c[i].type, g_221c[i].idx);
                                if (g_221c[i].type != 14 && g_221c[i].type != 6
                                    && g_221c[i].type != 7 && g_221c[i].type != 2)
                                    for (j = 0; j < 8 && g_1e68 / 10 - g_937a[j] < 20; j++) {
                                        if (g_938a[j] == g_221c[i].type && g_9392[j] == g_221c[i].idx) {
                                            fn_10_754a(0x73, g_221c[i].type, g_221c[i].idx, 1);
                                            fn_03_06ec(g_9646, 7, 0, 0x70);
                                            g_1e58 += 800;
                                            break;
                                        }
                                    }
                                if (g_221c[i].type == 6) {
                                    g_66e4[g_221c[i].idx].f08 = g_2f4c[g_66e4[g_221c[i].idx].f00].f26;
                                    g_66e4[g_221c[i].idx].f00 = -1;
                                    DOBJ(i).f2e = 0;
                                } else {
                                    DOBJ(i).f2e = -1;
                                    fn_12_3778();
                                }
                                fn_12_26a4(g_221c[i].type, g_221c[i].idx);
                                fn_07_2080(g_221c[i].type, g_221c[i].idx);  /* sic: 2 args */
                                fn_02_170e();
                            }
                        } else {
                            if (DOBJ(i).f1a)
                                BitBlt(g_13dc, DOBJ(i).f00, DOBJ(i).f02, DOBJ(i).f22, DOBJ(i).f22,
                                       DOBJ(i).f3c,
                                       (DOBJ(i).f22 + DOBJ(i).f24) * DOBJ(i).f28 + DOBJ(i).f24,
                                       DOBJ(i).f24, SRCCOPY);
                            DOBJ(i).f2e = 0;
                            if (g_221c[i].type == 14 && g_221c[i].idx == g_9646
                                && g_7090[g_9646].f2e != 2)
                                fn_10_754a(0x65, 0, 0, 0);
                            fn_12_26a4(g_221c[i].type, g_221c[i].idx);
                        }
                        if (g_221c[i].type == 14) {
                            g_7090[g_221c[i].idx].feb = 0;
                            fn_02_170e();
                        }
                        g_221c[i].type = -1;
                        dissolve_active_count--;
                        return;
                    } else if (g_221c[i].type == 20) {
                        PatBlt(g_929e, 0, 0, g_92a4, g_92a4, BLACKNESS);
                        g_221c[i].type = -1;
                        dissolve_active_count--;
                        return;
                    } else if (g_221c[i].type >= 21) {
                        g_221c[i].type = -1;
                        dissolve_active_count--;
                        return;
                    }
                } else if (g_221c[i].type <= 14) {
                    if (DOBJ(i).f2e == 1)
                        PatBlt(DOBJ(i).f3c, x + DOBJ(i).f24, y + DOBJ(i).f24,
                               (2 << g_9156) >> 1, (2 << g_9156) >> 1, BLACKNESS);
                    else
                        BitBlt(DOBJ(i).f3c, x + DOBJ(i).f24, y + DOBJ(i).f24,
                               (2 << g_9156) >> 1, (2 << g_9156) >> 1, DOBJ(i).f3a,
                               (DOBJ(i).f22 + DOBJ(i).f24) * DOBJ(i).f28 + DOBJ(i).f24 + x,
                               y + DOBJ(i).f24, SRCCOPY);
                } else if (g_221c[i].type == 20)
                    PatBlt(g_929e, x, y, 8, 8, BLACKNESS);
                else if (g_221c[i].type == 21)
                    BitBlt(g_13dc, x, y, g_90ea / g_221c[i].r + 1, g_90ec / g_221c[i].r + 1,
                           g_9580, x, y, SRCCOPY);
                else if (g_221c[i].type > 21)
                    BitBlt(g_13dc, x, y, g_90ea / g_221c[i].r / 2 + 1,
                           g_90ec / g_221c[i].r / 2 + 1, g_9580, x, y, SRCCOPY);
            }
        }
    }
}

/* Respawns ships waiting in state 100 after their timer runs out [inferred].
 * The redundant `j <= g_9316` test reproduces the extra jg. */
/* @addr 7:1d0c */
void far fn_07_1d0c(void)
{
    int i;
    int t;
    int j;
    int r;

    if (g_1e30[g_9646].f18 == 100)
        fn_07_1208();
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].f88 < g_1e50) {
            t = g_96f0[g_7090[i].f4e].f1a;
            for (j = i + 1; j <= g_9316; j++)
                if (j <= g_9316 && g_1e30[i].f18 == 100 && g_1e30[j].f18 == 100) {
                    g_7090[j].f88 = g_1e50 + 5000;
                    break;
                }
            if (g_1e30[i].f18 == 100 && (t != 7 || g_7090[i].f5e != 1)) {
                r = rand() % g_9318;
                if (i == g_9646)
                    r = 0;
                g_1e30[i].f04 = g_1df8[8][r * 2].f04;
                g_1e30[i].f04.x += (g_1df8[8][r * 2 + 1].f04.x - g_1df8[8][r * 2].f04.x) / 2
                                   - g_1e30[i].f20 / 2 + g_1df8[8]->f20 / 2;
                g_1e30[i].f18 = 0;
                if (i == g_9646)
                    g_96f0[g_7090[i].f4e].f24 = 1;
                fn_08_0000();
                fn_10_754a(0x27, 14, i, 1);
                fn_12_2556(14, i);
                fn_07_13b2(2, 14, i);
                for (j = g_9140 = 0; j <= g_9316; j++)
                    if (g_1e30[j].f18 == 100 && g_7090[j].fec)
                        g_9140 = 1;
                if (!g_9140 && g_9320 == 7)
                    g_668a = 1;
                if ((g_094e || g_0950) && i != g_9646)
                    command_watch_ship(0, 0);
                return;
            }
        }
    }
}

/* @addr 7:1f38 */
void far fn_07_1f38(void)
{
    HFONT oldfont;
    HFONT font;
    COLORREF textcol;
    COLORREF bkcol;

    if (g_9134 == 1 && g_058c) {
        font = CreateFont(14, 9, g_058c = 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
        oldfont = SelectObject(g_13dc, font);
        bkcol = SetBkColor(g_13dc, 0L);
        SetBkMode(g_13dc, OPAQUE);
        SetTextAlign(g_13dc, 0);
        textcol = SetTextColor(g_13dc, PALETTERGB(0, 0xff, 0xff));
        PatBlt(g_13dc, g_1d28.left + 10, g_1d28.top, g_1d28.right - 10, g_1d28.bottom,
               BLACKNESS);
        g_1d28.bottom += g_1d28.top;
        g_1d28.right += g_1d28.left;
        fn_02_094c(0x929);
        lstrcat(g_8e68, g_8630);
        ExtTextOut(g_13dc, g_1d28.left + 10, g_1d28.top, ETO_CLIPPED, &g_1d28,
                   g_8e68, lstrlen(g_8e68), NULL);
        g_1d28.bottom -= g_1d28.top;
        g_1d28.right -= g_1d28.left;
        SetBkColor(g_13dc, bkcol);
        SetTextColor(g_13dc, textcol);
        SelectObject(g_13dc, oldfont);
        if (font)
            DeleteObject(font);
    }
}

/* @addr 7:2080 */
void far fn_07_2080(int t)
{
    int i;

    if (t == 1 || t == 2 || t == 7 || t == 5 || t == 11 || t == 9
        || t == 10 || t == 4 || t == 6 || t == 8 || t == 19) {
        for (i = g_92ec[t]; i > 0; i--)
            if (g_1df8[t][i - 1].f18 == 0 || g_1df8[t][i - 1].f51 != 0) {
                g_9406[t] = i;
                break;
            }
        if (i == 0)
            g_9406[t] = 0;
    }
}

/* @addr 7:2128 */
void far fn_07_2128(void)
{
    int i;
    char unused[72];

    if (g_9316 == 0) {
        g_9432 -= max(g_9432 / 50, 2);
        if (g_9432 < 0)
            g_9432 = 0;
        return;
    }
    for (i = 0; i < g_9316; i++)
        if (g_7090[i].f32 == 14 && g_7090[i].f34 == g_9646 && g_7090[i].f38 == 1) {
            g_9432 -= max(g_9432 / 18, 4);
            if (g_9432 < 0)
                g_9432 = 0;
            if (g_8e28 + 15000 < g_1e50) {
                g_9432 -= max(g_9432 / 14, 4);
                if (g_9432 < 0)
                    g_9432 = 0;
            }
            return;
        }
    g_9432 -= max(g_9432 / 40, 3);
    if (g_9432 < 0)
        g_9432 = 0;
    if (g_8e28 + 15000 < g_1e50) {
        g_9432 -= max(g_9432 / 36, 2);
        if (g_9432 < 0)
            g_9432 = 0;
    }
}

/* Frame-rate bookkeeping [inferred]: counts frames per 250 ms and per
 * second and rescales g_9004 when off target. */
/* @addr 7:2206 */
void far fn_07_2206(void)
{
    int a;
    int b;

    if (g_90f4 == 6 && g_952c && g_9530 == 1) {
        b = g_6da4->f2a;
        a = b / 4;
    } else if (g_90f4 == 6 && g_914a == 1 && g_92a2 == 0) {
        a = 8;
        b = 32;
    } else {
        a = 18;
        b = 72;
    }
    g_914c++;
    if (g_1e50 > g_1e64) {
        if (a + 1 < g_914c || a - 1 > g_914c) {
            if (g_914c > a && g_9004 == 0)
                g_9004 = 1;
            g_9004 = g_914c * g_9004 / a;
        }
        g_1e64 = g_1e50 + 250;
        g_914c = 0;
    }
    g_0586++;
    if (g_1e50 > g_1e8c) {
        g_1e8c = g_1e50 + 1000;
        if (b + 9 > g_0586 && b - 9 < g_0586) {
            if (b < g_0586 && g_9004 == 0)
                g_9004 = 1;
            g_9004 = g_9004 * g_0586 / b;
        }
        if (g_0592)
            g_0592--;
        g_059a = g_0586;
        g_0586 = 0;
    }
}
