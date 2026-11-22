/* INSPACE.EXE segment 9 (selector 1040), 9:0b2a-5be0: one source file
 * (functions near-call each other) [inferred]. */
#include <stdlib.h>
#include "inspace.h"

/* Records reached through far pointers or DGROUP arrays; only the fields
 * this file uses are named (offset in the name). */
typedef struct {                /* 0x70 bytes, far array at DS:1df8 / 1e18 */
    char p00[0x18];
    int f18;
    char p1a[0x1e - 0x1a];
    int f1e;
    char p20[0x2f - 0x20];
    char f2f;
    char p30[0x51 - 0x30];
    char f51;
    char p52[0x70 - 0x52];
} REC_70;

#pragma pack(1)
typedef struct {                /* 0x297 bytes, far array at DS:69f4 */
    char p000[0x14e];
    int f14e;                   /* +14e */
    int f150;                   /* +150 */
    char p152[0x1c8 - 0x152];
    char f1c8[8];               /* +1c8 */
    char f1d0;                  /* +1d0 */
    char f1d1;                  /* +1d1 */
    int f1d2[8];                /* +1d2 */
    unsigned char f1e2[0x297 - 0x1e2];
} REC_297;

typedef struct {                /* 0x7c bytes, far array at DS:6e24 */
    char p00[0x64];
    char f64;                   /* +64 */
    char f65[0x7c - 0x65];      /* +65: name [inferred] */
} REC_7C;
#pragma pack()

typedef struct {                /* 0x15a bytes, DGROUP array at DS:7090 */
    char p000[0x1e];
    int f1e;                    /* +1e */
    char p020[0x4e - 0x20];
    int f4e;                    /* +4e */
    char p050[0xec - 0x50];
    char fec;                   /* +ec */
    char p0ed;
    char fee[0x146 - 0xee];     /* +ee, indexed by object [inferred] */
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
extern int g_13de;
extern long g_1e50;
extern long g_1e78;
extern long g_1e88;
extern REC_70 far *g_1df8[16];
extern int g_3a02;
extern char g_3966[];
extern HGDIOBJ g_4e94[32];
extern REC_23 g_57a8[];
extern void far *g_4fcc;
extern long g_5078;
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

void far fn_10_6d52(int a, int b, int c, int d, int e, int f);
void far fn_17_306e(void);
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
