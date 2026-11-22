/* INSPACE.EXE segment 11 (selector 1050): functions that near-call some
 * of seg11.c's functions but far-call others (11:1bcc far-calls 11:4c72,
 * 11:aece far-calls 11:3cc2 and 11:2f8c), so they cannot share seg11.c. */
#include "inspace.h"

/* 0x15a-byte records at DS:7090 [inferred]. */
typedef struct {
    char p000[2];
    int f02;                    /* +02 */
    char p004[0x0c - 4];
    int f0c;                    /* +0c */
    char p00e[0x18 - 0xe];
    int f18;                    /* +18 */
    char p01a[0x1e - 0x1a];
    int f1e;                    /* +1e */
    char p020[0x4e - 0x20];
    int f4e;                    /* +4e */
    char p050[0xb8 - 0x50];
    char fb8[0x13];             /* +b8 */
    char p0cb[0xd0 - 0xcb];
    int fd0;                    /* +d0 */
    int fd2;                    /* +d2 */
    char p0d4[0xd6 - 0xd4];
    int fd6;                    /* +d6 */
    char p0d8[0xe8 - 0xd8];
    char fe8;                   /* +e8 */
    char p0e9[0xec - 0xe9];
    char fec;                   /* +ec */
    char p0ed[0x15a - 0xed];
} REC_15A;
extern REC_15A g_7090[];

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. */
typedef struct {
    char p00[4];
    long f04;                   /* +04: position [inferred] */
    char p08[0x18 - 8];
    int f18;                    /* +18 */
    char p1a[0x44 - 0x1a];
    int f44;                    /* +44 */
    char p46[0x50 - 0x46];
    char f50;                   /* +50 */
    char p51[0x70 - 0x51];
} REC_70;
extern REC_70 far *g_1df8[16];

/* 0xad-byte records; lowest field seen at DS:96ea [inferred]. */
#pragma pack(1)
typedef struct {
    char p00[0x1a];
    int f1a;                    /* +1a */
    char p1c[0x20 - 0x1c];
    int f20;                    /* +20 */
    char p22[0x2a - 0x22];
    int f2a;                    /* +2a */
    char p2c[0xad - 0x2c];
} REC_AD;
#pragma pack()
extern REC_AD g_96ea[];

extern long g_1e58;
extern long g_5018;
extern DWORD g_1e50;
extern DWORD g_1e68;
extern DWORD g_1854;
extern DWORD g_5074;
extern int g_93fe;
extern int g_934e;
extern int g_9646;
extern int g_9316;
extern int g_9324;

extern int g_9320;
extern int g_1032;
extern int g_92e8;
extern int g_931c;
extern long g_1e80;
extern long g_1e84;
extern int g_9134;
extern int g_951a;
extern long g_6b50;

typedef struct { unsigned char idx, type; } OBJREF;

int far fn_11_4c72(int n);
void far fn_11_3cc2(int n, int a);
void far fn_11_2f8c(void);
void far fn_03_06ec(int n, int kind, int target, int d);
void far fn_03_00f4(int n, char type, int idx);
OBJREF far fn_13_2206(void);
void far pascal fn_08_4d60(int far *a, int far *b);
void far pascal fn_03_332e(int a, int b);
void far fn_13_2dcc(void);

/* Not yet decompiled here (in seg11.c): stubs so calls compile near. */
void far fn_11_04a0(int a) { }
void far fn_11_1d7c(void) { }
void far fn_11_ae94(void) { }

/* Periodic update of the ships' energy [inferred]. */
/* @addr 11:1bcc */
void far fn_11_1bcc(void)
{
    int i;
    int v;
    int unused;

    if (g_5018 != g_1e58)
        fn_11_04a0(0);
    if (g_1854 < g_1e50) {
        g_1854 = g_1e50 + 300;
        g_93fe = g_93fe == 0;
        fn_11_04a0(1);
    }
    if ((int)(g_1e68 / 36) != g_934e)
        fn_11_04a0(7);
    if (g_5074 < g_1e50) {
        g_5074 = g_1e50 + 1000;
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].f02) {
                v = g_7090[i].f0c / -40 - g_7090[i].fe8 * 5 + g_7090[i].f1e;
                g_7090[i].f1e = v < 0 ? 0 : v;
            } else {
                v = g_7090[i].f1e - g_7090[i].fe8 * 5;
                g_7090[i].f1e = v < 0 ? 0 : v;
            }
            if (g_7090[i].fe8) {
                g_7090[i].f1e -= 3;
                if (g_7090[i].f1e < 0x78) {
                    fn_11_4c72(i);
                    fn_03_332e(0x409, 0x418);
                }
            }
            if (g_7090[i].fb8[g_7090[i].f18] == 3) {
                if (i == g_9646)
                    g_1df8[g_9324][i].f50 += (0x6d - g_1df8[g_9324][i].f50) / 2;
                else
                    g_1df8[g_9324][i].f50 += (0x6d - g_1df8[g_9324][i].f50) / 5;
            }
            g_1df8[g_9324][i].f44 = g_7090[i].f1e / 20 + g_96ea[g_7090[i].f4e].f1a;
        }
        fn_11_04a0(6);
        fn_13_2dcc();
    }
    fn_11_1d7c();
}

/* Switch control to the next ship of the same side [inferred]. */
/* @addr 11:aece */
int far fn_11_aece(void)
{
    int start;
    int cand;
    int tmp;
    int ok;
    OBJREF r;

    if (g_9320 == 6 || g_9320 == 7)
        return 0;
    ok = g_1032 = 0;
    start = g_9646;
    if (g_1df8[g_9324][start].f18 != 0)
        return 0;
    if (g_92e8 != 0)
        return 0;
    do {
        if (g_9646 < g_9316)
            g_9646++;
        else
            g_9646 = 0;
        ok = 1;
        if (g_1df8[g_9324][g_9646].f18 != 0 || g_7090[g_9646].fec == 0)
            ok = 0;
        if (start == g_9646)
            ok = 1;
        else if (g_96ea[g_7090[g_9646].f4e].f20 != g_96ea[g_7090[start].f4e].f20)
            ok = 0;
    } while (!ok);
    if (start == g_9646)
        return 0;
    cand = g_9646;
    g_9646 = start;
    tmp = g_7090[cand].fd0;
    g_7090[cand].fd0 = g_7090[g_9646].fd0;
    g_7090[g_9646].fd0 = tmp;
    tmp = g_7090[cand].fd2;
    g_7090[cand].fd2 = g_7090[g_9646].fd2;
    g_7090[g_9646].fd2 = tmp;
    fn_03_06ec(g_9646, g_9324, cand, 0x71);
    g_9646 = cand;
    g_96ea[g_7090[cand].f4e].f2a = 1;
    r = fn_13_2206();
    fn_03_00f4(g_9646, r.type, r.idx);
    fn_08_4d60(&g_7090[cand].fd6, &g_7090[g_9646].fd6);
    g_931c = g_7090[g_9646].fd6;
    g_1e80 = g_1e84 = 0;
    g_9134 = 1;
    if (g_951a == 0)
        g_6b50 = g_1df8[g_9324][start].f04;
    g_951a = 1;
    fn_11_3cc2(g_9646, 1);
    fn_11_ae94();
    fn_11_2f8c();
    return 1;
}
