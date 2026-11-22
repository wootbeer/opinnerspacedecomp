/* INSPACE.EXE segment 9 (selector 1040). */
#include "inspace.h"

/* Records reached through far pointers or DGROUP arrays; only the fields
 * this file uses are named (offset in the name). */
typedef struct {                /* 0x70 bytes, far array at DS:1df8 / 1e18 */
    char p00[0x18];
    int f18;
    char p1a[0x51 - 0x1a];
    char f51;
    char p52[0x70 - 0x52];
} REC_70;

typedef struct {                /* 0x297 bytes, far array at DS:69f4 */
    char p000[0x1d0];
    char f1d0;
    char p1d1[0x1e2 - 0x1d1];
    unsigned char f1e2[0x297 - 0x1e2];
} REC_297;

typedef struct {                /* 0x15a bytes, DGROUP array at DS:70ae */
    int f00;
    char p02[0x30 - 0x02];
    int f30;
    char p32[0x15a - 0x32];
} REC_15A;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    char p02[0xad - 0x02];
} REC_AD;
#pragma pack()

typedef struct { int a, b; } PAIR;

extern int g_0010;
extern REC_70 far *g_1df8;
extern REC_70 far *g_1e18;
extern HGDIOBJ g_4e94[32];
extern long g_5078;
extern LPSTR g_6078;
extern REC_297 far *g_69f4;
extern REC_15A g_70ae[];
extern long g_09bc[12];
extern int g_90ea;
extern int g_9200;
extern int g_9206;
extern int g_92e6;
extern int g_9316;
extern int g_9318;
extern int g_9322;
extern int g_9334;
extern int g_9406;
extern int g_94a2;
extern HGDIOBJ g_93ae;
extern REC_AD g_96f0[];
extern char g_9ec2[][40];
extern PAIR g_9f40[][40];

void far fn_10_6d52(int a, int b, int c, int d, int e, int f);
void far fn_17_306e(void);

/* @addr 9:094c */
int far fn_09_094c(void)
{
    int i;
    int unused;
    int found;

    for (i = 0; i < g_9406; i++) {
        found = 1;
        if (g_1df8[i].f18 == 0)
            found = 0;
        if (found)
            return i;
    }
    g_69f4[g_94a2].f1d0 = 1;
    g_9206++;
    return -1;
}

/* @addr 9:0ac4 */
int far fn_09_0ac4(int n, int count)
{
    unsigned char mask;
    int unused;
    int idx;

    idx = n / 8;
    mask = 1 << (n % 8);
    if (count)
        g_9200++;
    if (g_69f4[g_94a2].f1e2[idx] & mask)
        return 1;
    return 0;
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

/* near-match 53%: 9:225a */
PAIR far fn_09_225a(int a)
{
    PAIR v;
    int unused[3];

    v.a = g_9f40[g_9322][a].a;
    v.b = g_9f40[g_9322][a].b;
    g_1e18[g_9318 * 2 + a].f51 = (int)g_9ec2[g_9322][a] + g_9318 * 2;
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

/* @addr 9:6db0 */
void far fn_09_6db0(void)
{
    int i;

    for (i = 0; i <= g_9316; i++)
        g_70ae[i].f00 = g_96f0[g_70ae[i].f30].f00;
}

/* @addr 9:88ba */
int far fn_09_88ba(int x)
{
    if (x >= 0)
        return x;
    return -x;
}

/* @addr 9:88dc */
long far abs32(long x)
{
    if (x >= 0)
        return x;
    return -x;
}

/* @addr 9:8908 */
void far fn_09_8908(void)
{
    fn_17_306e();
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
}

/* @addr 9:955c */
int far fn_09_955c(UINT id, LPSTR buf)
{
    return LoadString(g_9212, id, buf, 160);
}

/* @addr 9:9580 */
void far fn_09_9580(UINT id, LPSTR dst)
{
    char buf[200];

    LoadString(g_9212, id, buf, 199);
    lstrcat(dst, buf);
}

/* @addr 9:95ba */
void far fn_09_95ba(UINT id)
{
    char buf[200];

    LoadString(g_9212, id, buf, 199);
    lstrcat(g_6078, buf);
}

/* @addr 9:95f4 */
void far fn_09_95f4(UINT id)
{
    char buf[100];

    LoadString(g_9212, id, ambulance_line, 90);
}

/* @addr 9:961a */
void far fn_09_961a(UINT id)
{
    char buf[100];

    LoadString(g_9212, id, buf, 90);
    lstrcat(ambulance_line, buf);
}
