/* INSPACE.EXE segment 13 (selector 1060), second source file (13:6900-end).
 * Calls into the first file (seg13.c: 2688, 2714, 4eec) are far. */
#include "inspace.h"
#include <stdlib.h>

/* BEGIN STRUCTS */
typedef void (far *FNPTR)(int, int);  /* REC70 handler [inferred] */
typedef int (far *FNSPLIT)(int, int); /* REC70 +5e, e.g. fn_07_570a */
typedef void (far *FNVOID)(void);     /* REC70 +62, e.g. fn_11_3914 */
#pragma pack(1)
/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record. Generated layout; keep in sync between seg13.c/seg14.c. */
typedef struct {
    int f_000;    /* DS:7092 */
    int f_002;    /* DS:7094 */
    int f_004;    /* DS:7096 */
    int f_006;    /* DS:7098 */
    int f_008;    /* DS:709a */
    int f_00a;    /* DS:709c */
    int f_00c;    /* DS:709e */
    int f_00e;    /* DS:70a0 */
    char pad_010[0x2];
    int f_012;    /* DS:70a4 */
    int f_014;    /* DS:70a6 */
    char pad_016[0x4];
    int f_01a;    /* DS:70ac */
    int f_01c;    /* DS:70ae */
    char pad_01e[0x4];
    int f_022;    /* DS:70b4 */
    int f_024;    /* DS:70b6 */
    int f_026;    /* DS:70b8 */
    int f_028;    /* DS:70ba */
    char pad_02a[0x6];
    int f_030;    /* DS:70c2 */
    int f_032;    /* DS:70c4 */
    int f_034;    /* DS:70c6 */
    int f_036;    /* DS:70c8 */
    int f_038;    /* DS:70ca */
    int f_03a;    /* DS:70cc */
    int f_03c;    /* DS:70ce */
    int f_03e;    /* DS:70d0 */
    char pad_040[0x2];
    int f_042;    /* DS:70d4 */
    char pad_044[0x8];
    int f_04c;    /* DS:70de */
    int f_04e;    /* DS:70e0 */
    int f_050;    /* DS:70e2 */
    int f_052;    /* DS:70e4 */
    int f_054;    /* DS:70e6 */
    int f_056;    /* DS:70e8 */
    char f_058;    /* DS:70ea */
    char pad_059[0x1];
    char f_05a;    /* DS:70ec */
    char f_05b;    /* DS:70ed */
    char f_05c;    /* DS:70ee */
    char f_05d;    /* DS:70ef */
    char pad_05e[0x1];
    char f_05f;    /* DS:70f1 */
    int f_060[16];    /* DS:70f2 */
    int f_080;    /* DS:7112 */
    unsigned long f_082;    /* DS:7114 */
    char pad_086[0xc];
    long f_092;    /* DS:7124 */
    unsigned long f_096;    /* DS:7128 */
    unsigned long f_09a;    /* DS:712c */
    int f_09e;    /* DS:7130 */
    int f_0a0;    /* DS:7132 */
    long f_0a2;    /* DS:7134 */
    char pad_0a6[0x4];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    char f_0ac[10];    /* DS:713e */
    char f_0b6[16];    /* DS:7148 */
    char pad_0c6[0x3];
    char f_0c9;    /* DS:715b */
    char pad_0ca[0x1];
    char f_0cb;    /* DS:715d */
    int f_0cc;    /* DS:715e */
    char pad_0ce[0x2];
    int f_0d0;    /* DS:7162 */
    char pad_0d2[0x2];
    int f_0d4;    /* DS:7166 */
    int f_0d6;    /* DS:7168 */
    char pad_0d8[0x2];
    long f_0da;    /* DS:716c */
    char pad_0de[0x2];
    char f_0e0;    /* DS:7172 */
    char f_0e1;    /* DS:7173 */
    char f_0e2;    /* DS:7174 */
    char f_0e3;    /* DS:7175 */
    char f_0e4;    /* DS:7176 */
    char f_0e5;    /* DS:7177 */
    char f_0e6;    /* DS:7178 */
    char f_0e7;    /* DS:7179 */
    char f_0e8;    /* DS:717a */
    char f_0e9;    /* DS:717b */
    char f_0ea;    /* DS:717c */
    char f_0eb;    /* DS:717d */
    char f_0ec[8];    /* DS:717e */
    char f_0f4[9][9];    /* DS:7186 */
    char f_145;    /* DS:71d7 */
    char f_146;    /* DS:71d8 */
    char f_147;    /* DS:71d9 */
    char pad_148[0xc];
    unsigned long f_154;    /* DS:71e6 */
    char pad_158[0x2];
} OBJ15A;

/* 0x70-byte records reached through far pointers (DS:1e30, DS:1df8[]). */
typedef struct {
    POINT f_000;
    POINT f_004;
    char pad_008[0x4];
    int f_00c;
    int f_00e;
    int f_010;
    int f_012;
    char pad_014[0x4];
    int f_018;
    int f_01a;
    char pad_01c[0x2];
    int f_01e;
    int f_020;
    int f_022;
    int f_024;
    int f_026;
    int f_028;
    char pad_02a[0x2];
    int f_02c;
    char f_02e;
    char f_02f;
    char pad_030[0x2];
    int f_032;
    int f_034;
    int f_036;
    int f_038;
    int f_03a;
    int f_03c;
    char pad_03e[0x4];
    int f_042;
    int f_044;
    int f_046;
    int f_048;
    int f_04a;
    unsigned long f_04c;
    char pad_050[0x1];
    char f_051;
    char f_052;
    char f_053;
    char f_054;
    char pad_055[0x9];
    FNSPLIT f_05e;
    FNVOID f_062;
    FNPTR f_066;
    char pad_06a[0x6];
} REC70;

/* 0x41-byte records through the far pointer at DS:6e20 [inferred]. */
typedef struct {
    char f_000;
    char f_001;
    char f_002;
    char f_003;
    char f_004[2];
    char f_006;
    char f_007;
    char f_008;
    char f_009;
    char f_00a[21];
    int f_01f;
    int f_021;
    char pad_023[0x15];
    char f_038[9];
} REC41;

/* 0x2c-byte records through the far pointer at DS:6e1c [inferred]. */
typedef struct {
    char pad_000[0x15];
    int f_015;
    int f_017;
    char f_019;
    char f_01a;
    char f_01b;
    char f_01c;
    char f_01d;
    char f_01e;
    char f_01f;
    char f_020;
    int f_021;
    char f_023[9];
} REC2C;

/* 0xad-byte records at DS:96ea (base as in seg03.c/seg11.c) [inferred]. */
typedef struct {
    char f_000;
    char pad_001[0x1];
    char f_002;
    char pad_003[0x3];
    int f_006;
    char pad_008[0x16];
    int f_01e;
    int f_020;
    char pad_022[0xc];
    int f_02e;
    char pad_030[0x20];
    int f_050;
    int f_052;
    int f_054;
    int f_056;
    char pad_058[0x14];
    char f_06c[37];
    long f_091;
    char pad_095[0x18];
} RECAD;
#pragma pack()
/* END STRUCTS */
extern OBJ15A g_7092[];
extern REC70 far *g_1e30;
extern REC70 far *g_1e28;

extern long g_1e50;
extern unsigned long g_8858;
extern unsigned long g_885c;
extern int g_9134;
extern int g_940e;
typedef struct { int a, b; } PAIR;
extern PAIR g_6e52;               /* = g_6e3e[0].f_14/f_16 in seg13.c */
extern int g_9316;
extern int g_9318;
extern long g_2384;
extern char g_a157[];
extern char g_a14d[];
extern char g_a161;
extern char g_a163;
extern RECAD g_96ea[];
extern REC70 far *g_1df8[];
extern REC70 far *g_1e00;
extern int g_9406[];
extern int g_940a;
extern REC70 far *g_1e14;
extern int g_1c8e[];
extern int g_91f8;
extern int g_9334;

/* 0x24-byte records at DS:52ec [inferred base]. */
typedef struct {
    int f_00;                       /* DS:52ec */
    int f_02;
    char pad_04[0x0a - 0x04];
    int f_0a;                       /* DS:52f6 */
    char pad_0c[0x12 - 0x0c];
    int f_12;                       /* DS:52fe */
    char pad_14[0x18 - 0x14];
    int f_18;                       /* DS:5304 */
    int f_1a;
    int f_1c;
    int f_1e;
    char pad_20[0x24 - 0x20];
} REC24;
extern REC24 g_52ec[];
extern int g_9646;
extern int g_964e;
extern int g_9650;
extern int g_9652;
extern int g_9654;

void far fn_03_06ec(int, int, int, int);
int far fn_04_8346(int n, int x, int y, int v);
void far fn_10_7480(int a, int b);
void far fn_10_754a(int a, int b, int c, int d);
int far pascal fn_08_285a(int far *py, int far *px, POINT a, POINT b);
void far fn_13_2714(int, int, int, int, int, int);
int far fn_13_2688(int i, int j);
void far fn_03_00f4(int a, int s, int k);  /* seg03.c: (int, long) */
extern int g_91fa;
int far fn_04_5d9c(int a, int i);
extern int flow_interactive;       /* DS:95bc */
void far fn_03_33b4(int n);
extern int g_9320;
extern int g_964a;
extern int g_9648;
extern int g_104a;
extern int g_9220;
extern unsigned long g_1e68;
extern int g_941c;
extern REC70 far *g_1e24;
extern unsigned long g_8710;
extern unsigned long g_8714;
extern int g_934e;
extern int g_9432;
void far fn_13_4eec(int i, int d);
#define CLS(i) g_96ea[g_7092[i].f_04c].f_020   /* class of object i */

extern int g_9208;
extern int g_0992;
extern int g_932a;
extern int g_92e8;
extern int g_9e49;
extern int g_952e;
extern int g_9418;
extern REC70 far *g_1e1c;
void far fn_16_0b4e(int n);
int far fn_13_9970(int i);
int far fn_13_9bb8(int i, int b);
int far fn_13_81c2(int n);
extern int g_0a62;
extern int g_8e00;
extern int g_8e04;
extern int g_9680;
extern int g_9682;
/* 0x1c-byte records at DS:66e4. */
typedef struct {
    int f_00;
    char pad_02[0x1a];
} REC1C;
extern REC1C g_66e4[];
extern int g_9412;
extern REC70 far *g_1e10;
extern char g_a154;
extern long g_a147;
extern int g_a14b;
extern char g_a162;
void far pascal fn_04_584c(int s, int n, int t);
int far fn_13_adbe(int a, int b, int c);

void far fn_10_a332(LPSTR buf, int id, int n, ...);
extern char g_8630[];
extern int g_058c;
extern DWORD g_05c0;
int far fn_03_0000(int a, int b);
void far pascal fn_11_5ab6(int n, int k);
int far fn_09_88ba(int x);
extern REC70 far *g_1e08;
extern int g_932c;
void far pascal fn_13_a6bc(int n);

/* @addr 13:910a */
int far fn_13_910a(int n)
{
    int i;

    for (i = 0; i <= g_9316; i++) {
        if (i == n)
            continue;
        if (g_1e30[i].f_018 == 0 && g_7092[i].f_0ea != 0)
            return 0;
    }
    return 1;
}

/* Object n asks the others for help against its target (f_03c, f_03e):
 * picks the first object that agrees, else reports the best refusal
 * message [inferred]. Returns 1 if someone agreed, 0 if not, -1 when n
 * asked too recently. */
/* @addr 13:8570 */
int far fn_13_8570(int n)
{
    int j, u1, s, k, pw, rel, u2, msg, best, bestj, rel2;

    u1 = u2 = 0;
    if ((n != g_9646 || g_9134 != 0) && g_7092[n].f_09a > g_1e50)
        return -1;
    g_7092[n].f_09a = g_1e50 + 10000;
    if (g_934e < 5 && (n != g_9646 || !flow_interactive))
        return 0;
    s = g_7092[n].f_03c;
    k = g_7092[n].f_03e;
    if ((n != g_9646 || !flow_interactive)
        && g_7092[g_9646].f_030 == s
        && (s == 0x16 || g_7092[g_9646].f_032 == k))
        return 0;
    if (n != g_9646 && s == 9) {
        if (g_8710 && g_8710 + 1500 > g_1e68)
            return 0;
        if (g_8714 && g_8714 + 600 > g_1e68)
            return 0;
        for (j = 0; j < g_9316; j++) {
            if (j == g_9646)
                continue;
            if (g_7092[j].f_0ea && g_7092[j].f_030 == 14
                && g_7092[j].f_032 == g_9646 && g_7092[j].f_036 == 1)
                return 0;
        }
        if (g_7092[g_9646].f_024 < 40)
            return 0;
    }
    fn_13_4eec(n, 4);
    best = 1000;
    for (j = 0; j <= g_9316; j++) {
        msg = 1000;
        pw = fn_04_5d9c(j, k) + 20;
        rel = fn_13_2688(j, n);
        if (s == 14)
            rel2 = fn_13_2688(j, k);
        else
            rel2 = -400;
        if (j == n || g_1e30[j].f_018)
            msg = 0xa3;
        else if (s == 14 && k == j)
            msg = 0x9e;
        else if (CLS(j) == 2 && s == 14)
            msg = 0x93;
        else if (CLS(j) == 7)
            msg = 0x96;
        else if (CLS(j) == 6)
            msg = 0x95;
        else if (CLS(j) == 4 && CLS(n) != 4 && s == 14)
            msg = 0x94;
        else if (rel < -100 && CLS(j) != CLS(n)) {
            if (s == 14)
                msg = 0x9d;
            else
                msg = 0xa2;
        } else if (rel2 + 70 > rel || rel2 > 150)
            msg = 0x91;
        else if (CLS(k) != CLS(j)
                 && (g_7092[j].f_05b >= 3
                     || (rel < 100 && g_7092[j].f_05c >= 3)))
            msg = 0x9a;
        else if (k == 14 && CLS(k) == CLS(j))
            msg = 0x98;
        else if (k == 14 && CLS(k) == CLS(n)
                 && !(g_7092[k].f_036 == 1 && g_7092[k].f_030 == 14
                      && g_7092[k].f_032 == n)
                 && CLS(j) != 3) {
            if (CLS(j) == CLS(n))
                msg = 0x9b;
            else
                msg = 0x92;
        } else if (s == 0 && g_1df8[0][k].f_053 == 1
                   && g_1df8[0][k].f_01e == 0 && CLS(j) != 3)
            msg = 0x97;
        else if (g_7092[j].f_0ec[k] == 8)
            msg = 0x99;
        else if (k == 14 && g_7092[j].f_0b6[k + 10] == -1)
            msg = 0x90;
        else if (g_7092[j].f_05b * 62 - rel * 3 / 4 + 60 > pw)
            msg = 0x8f;
        else if (g_96ea[g_7092[j].f_04c].f_006 / 10 > g_7092[j].f_01c)
            msg = 0x8b;
        else if (g_7092[j].f_0cc + g_7092[j].f_0da
                     < (g_7092[j].f_05c - 2) * 50
                 && rel < 200 && g_7092[j].f_024 < 50 && pw < 80)
            msg = 0x9c;
        else if (g_7092[j].f_036 == 1 && g_7092[j].f_030 == 14
                 && g_7092[j].f_0f4[8][g_7092[j].f_032] > 0
                 && (g_7092[j].f_030 != n || g_7092[j].f_050 < 2
                     || g_7092[j].f_050 > 4)
                 && (s != 14 || g_7092[j].f_032 != k))
            msg = 0x8e;
        else if (g_7092[j].f_050 != 0 && g_7092[j].f_050 != 7
                 && g_7092[j].f_050 != 13 && g_7092[j].f_096 > g_1e50
                 && g_7092[j].f_056 != n) {
            if (g_7092[j].f_052 != 14 || g_7092[j].f_054 != n)
                msg = 0x8d;
            else if (g_7092[j].f_050 == 1 || g_7092[j].f_050 == 5)
                msg = 0x9f;
            else if (g_7092[j].f_050 >= 2 || g_7092[j].f_050 <= 4) {
                if (g_7092[j].f_056 == j)
                    msg = 0xa1;
                else
                    msg = 0xa0;
            }
        } else if (msg != 1000 && s == 14 && g_7092[k].f_0e6)
            msg = 0x8c;
        if (msg < best || (best > 0x90 && msg < 0x9e && (rand() & 1))) {
            best = msg;
            bestj = j;
            continue;
        }
        if (msg != 1000)
            continue;
        fn_13_4eec(j, 15);
        if (n == g_9646)
            fn_13_4eec(j, 25);
        fn_13_4eec(n, 20);
        if (s == 9) {
            fn_13_4eec(j, -10);
            fn_13_4eec(n, -13);
            if (n != g_9646)
                g_8710 = g_1e68;
        }
        if (j == g_9646 && g_9134 && flow_interactive) {
            if (g_1e50 - 15000 > g_8858) {
                g_964e = 4;
                g_9650 = s;
                g_9652 = k;
                g_8858 = g_1e50;
                g_9654 = n;
                fn_03_06ec(g_9646, 14, n, 0x34);
            }
            continue;
        }
        if (g_7092[j].f_050)
            fn_03_06ec(g_7092[j].f_056, 14, n, 0x13);
        if (n == g_9646) {
            if (s == 14)
                g_9432 += 120;
            else
                g_9432 += 30;
        }
        if (g_7092[j].f_05b >= 2)
            g_7092[j].f_050 = 2;
        else if (g_7092[j].f_05b <= 1)
            g_7092[j].f_050 = 3;
        else if (g_7092[j].f_05b == 0)
            g_7092[j].f_050 = 4;
        fn_04_8346(j, s, k, 9);
        if (j == g_9646)
            g_7092[j].f_050 = 2;
        if (n == g_9646 && g_9134 == 1)
            fn_03_33b4(2);
        g_7092[j].f_092 = g_1e50 + 400;
        g_7092[j].f_052 = s;
        g_7092[j].f_054 = k;
        g_7092[j].f_056 = n;
        g_7092[j].f_096 = g_1e50 + 10000;
        g_7092[n].f_09a = g_1e50 + 15000;
        g_7092[j].f_0eb = 1;
        g_7092[j].f_0a2 = g_1e50 - g_7092[j].f_05c * 2000 + 8000;
        fn_03_06ec(j, 14, n, 2);
        if (j != g_9646)
            fn_03_00f4(j, g_7092[j].f_052, g_7092[j].f_054);
        if (s == 14)
            fn_13_2714(g_7092[n].f_03e, n, -(g_7092[j].f_050 * 10),
                       g_7092[j].f_050 * -40, 0, 5);
        return 1;
    }
    if (n != g_9646
        && (g_7092[g_9646].f_050 == 0 || g_7092[g_9646].f_050 == 7)
        && !g_9134 && !(s == 14 && k == g_9646) && n != g_9646
        && fn_13_2688(n, g_9646) > -100
        && !(g_7092[g_9646].f_030 == 14 && g_7092[g_9646].f_032 == n)) {
        g_7092[g_9646].f_050 = 2;
        g_7092[g_9646].f_056 = n;
        g_7092[n].f_09a = g_7092[g_9646].f_096 = g_1e50 + 15000;
        g_7092[g_9646].f_052 = s;
        g_7092[g_9646].f_054 = k;
        fn_04_8346(g_9646, s, k, 9);
        fn_03_06ec(g_9646, 14, n, 2);
        if (s == 9)
            g_8710 = g_1e68;
        return 1;
    }
    if (best == 0xa3)
        fn_03_06ec(n, 7, 0, best);
    else
        fn_03_06ec(n, 14, bestj, best);
    return 0;
}

/* @addr 13:9970 */
int far fn_13_9970(int i)
{
    int j;

    if (g_7092[i].f_09a > g_1e50)
        return -1;
    for (j = 0; j <= g_9316; j++) {
        if (g_1e30[j].f_018 == 0 && g_7092[j].f_0ea && g_7092[j].f_050 >= 2
            && g_7092[j].f_050 <= 4 && g_7092[j].f_056 == i
            && j != g_9646 && j != i) {
            g_7092[i].f_09a = g_1e50 + 5000;
            return 0;
        }
    }
    return fn_13_8570(i);
}

/* @addr 13:a5c2 */
void far fn_13_a5c2(void)
{
    if (g_7092[g_9646].f_050 == g_964e && g_7092[g_9646].f_052 == g_9650
        && g_8858 + 20000 > g_1e50) {
        if (g_7092[g_9646].f_054 == g_9652 || g_9650 == 9)
            goto hit;
    } else if (g_7092[g_9646].f_050 == 4 && g_964e == 11
               && g_8858 + 20000 > g_1e50
               && g_7092[g_9646].f_052 == g_9650
               && g_7092[g_9646].f_054 == g_9652) {
hit:
        g_885c = g_1e50 + 700;
        g_8858 = g_1e50;
    }
}

/* @addr 13:a186 */
void far fn_13_a186(void)
{
    if (g_9134) {
        g_7092[g_9646].f_050 = 4;
        g_7092[g_9646].f_052 = g_6e52.b;
        g_7092[g_9646].f_054 = g_6e52.a;
        if (g_7092[g_9646].f_052 == 12)
            g_7092[g_9646].f_052 = 8;
        g_7092[g_9646].f_096 = g_1e50 + 30000;
        g_7092[g_9646].f_092 = g_1e50 + 200;
        g_7092[g_9646].f_0eb = 1;
        g_7092[g_9646].f_056 = g_9646;
        fn_04_8346(g_9646, g_6e52.b, g_6e52.a, 12);
        if (g_6e52.b == 14)
            fn_13_2714(g_6e52.a, g_9646, -15, -60, 1, 1);
        fn_13_a5c2();
    }
}

/* @addr 13:a3c8 */
void far fn_13_a3c8(void)
{
    int i, y, x, d, best;

    if (g_9134) {
        best = 20000;
        for (i = 0; i < g_9318 * 2; i += 2) {
            d = fn_08_285a(&y, &x, g_1e30[g_9646].f_004, g_1e28[i].f_004);
            if (d < best) {
                best = d;
                g_7092[g_9646].f_050 = 10;
                g_7092[g_9646].f_052 = 12;
                g_7092[g_9646].f_054 = i;
                g_7092[g_9646].f_096 = g_1e50 + 30000;
                g_7092[g_9646].f_092 = g_1e50 + 200;
                g_7092[g_9646].f_0eb = 1;
                g_7092[g_9646].f_056 = g_9646;
            }
        }
        fn_13_a5c2();
    }
}

/* @addr 13:a47c */
void far fn_13_a47c(void)
{
    if (g_9134) {
        if (g_940e < 1) {
            fn_03_06ec(g_9646, 7, 0, 0x38);
        } else {
            g_7092[g_9646].f_050 = 12;
            g_7092[g_9646].f_052 = 14;
            g_7092[g_9646].f_054 = g_9646;
            g_7092[g_9646].f_096 = g_1e50 + 30000;
            g_7092[g_9646].f_092 = g_1e50 + 200;
            g_7092[g_9646].f_0eb = 1;
            g_7092[g_9646].f_056 = g_9646;
            fn_13_a5c2();
        }
    }
}

/* @addr 13:a4f4 */
void far fn_13_a4f4(void)
{
    PAIR p;

    if (g_9134) {
        p.a = g_6e52.a;
        p.b = g_6e52.b;
        if (p.b != 14)
            return;
            g_7092[g_9646].f_050 = 1;
            g_7092[g_9646].f_052 = p.b;
            g_7092[g_9646].f_054 = p.a;
            g_7092[g_9646].f_096 = g_1e50 + 30000;
            g_7092[g_9646].f_092 = g_1e50 + 200;
            g_7092[g_9646].f_0eb = 1;
            g_7092[g_9646].f_056 = g_9646;
            fn_13_a5c2();
    }
}

/* @addr 13:a568 */
void far fn_13_a568(void)
{
    if (g_9134) {
        g_7092[g_9646].f_050 = 13;
        g_7092[g_9646].f_052 = 14;
        g_7092[g_9646].f_054 = g_9646;
        g_7092[g_9646].f_096 = g_1e50 + 30000;
        g_7092[g_9646].f_092 = g_1e50 + 200;
        g_7092[g_9646].f_0eb = 1;
        g_7092[g_9646].f_056 = g_9646;
    }
}

/* @addr 13:7b40 */
void far fn_13_7b40(int a)
{
    fn_03_06ec(g_9646, 14, a, 3);
    if (!g_9134)
        g_7092[g_9646].f_050 = 0;
    if (g_7092[g_9646].f_052 == 9)
        fn_13_2714(a, g_9646, 10, 0x16, 0, 6);
    else
        fn_13_2714(a, g_9646, 15, 0x41, 1, 8);
}

/* @addr 13:a65a */
void far fn_13_a65a(void)
{
    if (g_885c != 0 && g_885c < g_1e50) {
        if (g_8858 != 11)
            fn_13_7b40(g_9654);
        else
            fn_03_06ec(g_9646, g_9650, g_9652, 0x1f);
        g_964e = 0;
        g_9650 = 0;
        g_9652 = 0;
        g_9654 = 0;
        g_885c = 0;
        g_8858 = 0;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_13_ae68(int a, int b, int c)
{
    return a;
}

/* Summon with music [inferred, HANDOFF: report_crime, the enforcer order
 * and escalation call this rather than ae68]. */
/* Falls off the end without a return value after the music part (the
 * game's callers test the result anyway: fn_13_b93a). */
/* @addr 13:adbe */
int far fn_13_adbe(int a, int b, int c)
{
    int u, r;

    if (!fn_13_ae68(a, b, c))
        return 0;
    r = 2;
    switch (b) {
    case 3:
        r = 7;
        break;
    case 4:
        if (a == g_9646)
            r = 8;
        else if (g_7092[g_9646].f_030 == 14 && g_7092[g_9646].f_032 == a
                 && g_7092[g_9646].f_036 == 1)
            r = 7;
        else
            r = -1;
        break;
    case 0x13:
        r = 7;
        break;
    case 0x14:
        r = 7;
        break;
    case 0x15:
        r = 2;
        break;
    case 0x16:
        r = 2;
        break;
    }
    if (r != -1) {
        fn_10_7480(r, 0);
        g_2384 = g_1e50 + 12000;
    }
}

/* @addr 13:b93a */
void far fn_13_b93a(void)
{
    int i, k, s1, s2;

    for (i = 0; i <= g_9316; i++) {
        if (g_7092[i].f_0ea && g_1e30[i].f_018 == 0
            && g_96ea[g_7092[i].f_04c].f_020 == 7 && g_7092[i].f_05c > 1
            && g_1e30[i].f_01a != 0) {
            s1 = 0;
            s2 = 0;
            for (k = 0; k < 10; k++) {
                if (k != 9) {
                    s1 += g_a14d[k];
                    s2 += g_a157[k];
                }
            }
            if (s2 < s1) {
                if (fn_13_adbe(g_9646, 0x15, -1)) {
                    fn_03_06ec(g_9646, 14, i, 0xae);
                    g_a163 = g_a161;
                }
                return;
            }
        }
    }
}

/* @addr 13:9a18 */
void far fn_13_9a18(int a, int s, int k)
{
    int i, u, best;

    if (k < 0 || k >= g_9406[s] || g_1df8[s][k].f_018 != 0)
        return;
    best = -1;
    for (i = 0; i < g_940a; i++) {
        if (g_52ec[i].f_18 == 14 && g_52ec[i].f_1a == a
            && (g_52ec[i].f_1c != s || g_52ec[i].f_1e != k
                || g_52ec[i].f_12 != 15)
            && g_1e00[i].f_018 == 0) {
            g_52ec[i].f_12 = 15;
            g_52ec[i].f_1c = s;
            g_52ec[i].f_1e = k;
            g_52ec[i].f_0a = 0;
            best = i;
        }
    }
    if (best >= 0)
        fn_10_754a(0x15, 2, best, 1);
}

/* @addr 13:9ae8 */
void far fn_13_9ae8(int a)
{
    int i, best;

    best = -1;
    for (i = 0; i < g_940a; i++) {
        if (g_52ec[i].f_18 == 14 && g_52ec[i].f_1a == a
            && g_52ec[i].f_12 == 15) {
            g_52ec[i].f_12 = 0;
            g_52ec[i].f_00 = g_1e00[i].f_004.x
                - g_1df8[g_52ec[i].f_18][g_52ec[i].f_1a].f_004.x;
            g_52ec[i].f_02 = g_1e00[i].f_004.y
                - g_1df8[g_52ec[i].f_18][g_52ec[i].f_1a].f_004.y;
            g_1e00[i].f_01e = 0;
            best = i;
        }
    }
    if (best >= 0)
        fn_10_754a(0x15, 2, best, 1);
}

/* @addr 13:9f3e */
void far fn_13_9f3e(int i)
{
    int u1, u2, u3, t, cls, m, z;

    cls = g_96ea[g_7092[i].f_04c].f_020;
    m = g_7092[i].f_03c;
    t = g_7092[i].f_03e;
    u1 = z = 0;
    if (m != 14 || g_96ea[g_7092[t].f_04c].f_020 != cls) {
        t = -1;
        fn_03_06ec(i, 7, 0, 0x32);
    } else if (g_7092[t].f_050 != 0 && g_7092[t].f_050 != 7
               && g_7092[t].f_096 > g_1e50 && g_7092[t].f_05b > 1) {
        fn_03_06ec(i, 14, t, 0x31);
    } else if (g_96ea[g_7092[t].f_04c].f_020 == 7) {
        fn_03_06ec(i, 14, t, 0x40);
    } else {
        if (g_7092[t].f_050 != 0)
            fn_03_06ec(g_7092[t].f_056, m, t, 0x13);
        g_7092[t].f_050 = 10;
        g_7092[t].f_092 = g_1e50;
        fn_03_06ec(t, 14, i, 2);
    }
}

/* @addr 13:9bb8 */
int far fn_13_9bb8(int i, int b)
{
    int u1, u2, s;

    if (g_1e14->f_018 == 0)
        return 0;
    s = g_7092[i].f_0cc;
    s += g_7092[i].f_0da;
    if (s < 250 && i != g_9646)
        return 0;
    if ((g_7092[g_9646].f_030 == 14 && g_7092[g_9646].f_032 == i)
        || (g_7092[i].f_030 == 14 && g_7092[i].f_032 == g_9646)) {
        if (g_7092[i].f_080 < 1700)
            return 0;
        if (g_7092[i].f_024 > 1)
            return 0;
    }
    if (g_1c8e[i] == g_91f8)
        return 0;
    if (g_7092[i].f_026 <= 0 || g_7092[i].f_028 <= 0) {
        g_1c8e[i] = g_91f8;
        return 1;
    }
    if (g_7092[i].f_024 + g_7092[i].f_026 + g_7092[i].f_028
        < max(min((b + 2) * 20 + s / 10, 180), 70)
        || (g_7092[i].f_0cc > 200 && (g_9334 + 20) * 35 < s)) {
        g_1c8e[i] = g_91f8;
        return 1;
    }
    if (g_7092[i].f_0aa && g_7092[i].f_0ab)
        return 0;
    if (s > 500) {
        g_1c8e[i] = g_91f8;
        return 1;
    }
    return 0;
}

/* Object i asks its target t to escort it [inferred]. */
/* @addr 13:a01c */
void far fn_13_a01c(int i)
{
    int u1, u2, u3, t, cls, m, z;

    cls = g_96ea[g_7092[i].f_04c].f_020;
    m = g_7092[i].f_03c;
    t = g_7092[i].f_03e;
    u1 = z = 0;
    if (m == 14 && g_96ea[g_7092[t].f_04c].f_020 == 7) {
        fn_03_06ec(i, m, t, 0x40);
    } else if (m != 14 || g_96ea[g_7092[i].f_04c].f_020
                          != g_96ea[g_7092[t].f_04c].f_020) {
        fn_03_06ec(i, 7, 0, 0x36);
    } else if (g_7092[t].f_050 != 0 && g_7092[t].f_050 != 7
               && g_7092[t].f_09a > g_1e50 && g_7092[t].f_05b > 0) {
        fn_03_06ec(i, 14, t, 0x35);
        return;
    } else {
        if (g_7092[t].f_050 != 0)
            fn_03_06ec(g_7092[t].f_056, 14, t, 0x13);
        g_7092[t].f_050 = 12;
        g_7092[t].f_030 = 14;
        g_7092[t].f_032 = i;
        g_7092[t].f_03a = g_7092[t].f_036 = 2;
        g_7092[t].f_052 = 14;
        g_7092[t].f_054 = i;
        g_7092[t].f_056 = i;
        g_7092[t].f_096 = g_1e50 + 25000;
        g_7092[t].f_092 = g_1e50 + 500;
        g_7092[i].f_09a = g_1e50 + 15000;
        g_7092[t].f_0eb = 1;
        g_7092[t].f_0a2 = g_1e50 - g_7092[t].f_05c * 2000 + 8000;
        fn_03_06ec(t, 14, i, 2);
    }
}

/* @addr 13:9810 */
void far fn_13_9810(int i)
{
    int u1, u2, m, t, done;

    u1 = done = 0;
    if (i != g_9646 && g_7092[i].f_09a > g_1e50)
        return;
    m = g_7092[i].f_03c;
    t = g_7092[i].f_03e;
    if (fn_13_910a(i)) {
        fn_03_06ec(i, 7, 0, 100);
        return;
    }
    if (m != 14)
        return;
    if (g_96ea[g_7092[t].f_04c].f_020 == 7) {
        fn_03_06ec(i, 14, t, 0x40);
        return;
    }
    if (g_1e30[t].f_018 == 0 && g_7092[t].f_0ea
        && (g_7092[t].f_050 == 0 || g_7092[t].f_050 == 7
            || g_7092[t].f_096 < g_1e50)
        && t != i && fn_13_2688(t, i) > 0) {
        if (g_7092[t].f_050 != 0)
            fn_03_06ec(g_7092[t].f_056, 14, t, 0x13);
        g_7092[t].f_050 = 13;
        g_7092[t].f_092 = g_1e50 + 200;
        g_7092[t].f_056 = i;
        g_7092[t].f_096 = g_1e50 + 15000;
        g_7092[t].f_0eb = 0;
        fn_03_06ec(t, 14, i, 2);
        done = 1;
    } else if (!done)
        fn_03_06ec(i, 14, t, 0x5a);
}

/* Send the player to the selected object, or to the nearest free one of
 * kinds 0 and 11 [inferred]. */
/* @addr 13:a234 */
void far fn_13_a234(void)
{
    int i;
    PAIR p;
    int d, best, bs, bk, y, x;

    if (g_9134) {
        p.a = g_6e52.a;
        p.b = g_6e52.b;
        if ((p.b == 0 || p.b == 11) && g_1df8[p.b][p.a].f_018 == 0)
            goto set;
        best = 20000;
        bs = -1;
        for (i = 0; i < g_91fa; i++) {
            if (g_1df8[0][i].f_018 == 0) {
                d = fn_08_285a(&y, &x, g_1e30[g_9646].f_004,
                               g_1df8[0][i].f_004);
                if (d < best) {
                    best = d;
                    bs = 0;
                    bk = i;
                }
            }
        }
        for (i = 0; i < g_941c; i++) {
            if (g_1e24[i].f_018 == 0) {
                d = fn_08_285a(&y, &x, g_1e30[g_9646].f_004,
                               g_1e24[i].f_004);
                if (d < best) {
                    best = d;
                    bs = 11;
                    bk = i;
                }
            }
        }
        if (bs != -1) {
            fn_03_00f4(g_9646, bs, bk);
            p.b = bs;
            p.a = bk;
        } else {
            fn_03_06ec(g_9646, 7, 0, 0x25);
            return;
        }
set:
        g_7092[g_9646].f_050 = 9;
        g_7092[g_9646].f_092 = g_1e50 + 200;
        g_7092[g_9646].f_052 = p.b;
        g_7092[g_9646].f_054 = p.a;
        g_7092[g_9646].f_056 = g_9646;
        g_7092[g_9646].f_096 = g_1e50 + 25000;
        g_7092[g_9646].f_0eb = 1;
        fn_13_a5c2();
    }
}

/* Pick the music section for the danger level [inferred]. */
/* @addr 13:ba04 */
void far fn_13_ba04(void)
{
    int i, m;
    long t;
    int found;

    m = 1;
    t = 5000;
    if (g_9220 == 9 || g_9220 == 10)
        return;
    for (i = 0; i <= g_9316; i++) {
        found = 0;
        t = 3000;
        if (g_7092[i].f_0ea && g_1e30[i].f_018 == 0) {
            if (g_7092[i].f_036 == 1 && g_7092[i].f_030 == 14
                && g_7092[i].f_032 == g_9646)
                found = 1;
            if ((g_7092[i].f_050 == 0x16 || g_7092[i].f_050 == 0x17)
                && g_7092[i].f_052 == 14 && g_7092[i].f_054 == g_9646)
                found = 1;
        }
        if (found) {
            m = 2;
            t = 6000;
            break;
        }
    }
    if (g_7092[g_9646].f_036 == 1 && g_9220 == 2
        && g_7092[g_9646].f_030 == 14) {
        t = 6000;
        m = 2;
    } else if (g_9220 == 2) {
        for (i = 0; i <= g_9316; i++) {
            if (i != g_9646 && g_1e68 / 10 - g_7092[i].f_042 < 20
                && g_7092[i].f_042 != 0 && g_1e30[i].f_018 == 0) {
                m = 2;
                t = 6000;
            }
        }
    }
    if (m != g_9220) {
        fn_10_7480(m, 0);
    } else {
        if (g_9220 == 2)
            t = 6000;
        else
            t = 3000;
    }
    g_2384 = g_1e50 + t;
}

/* Report a crime of kind t by object a to a nearby police ship
 * [inferred: HANDOFF report_crime; calls adbe]. flag is never read. */
/* @addr 13:b6f2 */
void far fn_13_b6f2(int a, int t)
{
    int i, y, x, d, msg, flag;

    flag = 1;
    if (g_9320 == 7)
        return;
    switch (t) {
    case 1:
        msg = 0x45;
        break;
    case 2:
        msg = 0x46;
        break;
    case 3:
        msg = 0x5d;
        break;
    case 4:
        msg = 0x65;
        break;
    case 5:
        if (g_a163 == 5)
            return;
        msg = 0x72;
        break;
    case 6:
        msg = 0x86;
        break;
    case 8:
        msg = 0xb9;
        break;
    case 9:
        msg = 0xc0;
        break;
    }
    if (a == g_9646 && t != 9) {
        g_964a++;
        g_9648++;
    }
    if (t != 6) {
        g_964a += 3;
        g_9648 += 3;
    } else {
        g_964a++;
        g_9648++;
    }
    if (t == 2) {
        g_964a += 4;
        g_9648 += 4;
    }
    if (t == 8 || g_104a) {
        g_964a += 2;
        g_9648 += 2;
        g_a163 = (char)t;
        fn_13_adbe(a, 0x15, -1);
        fn_03_06ec(a, 14, g_9316, msg);
        if (a == g_9646)
            g_a14d[t]++;
        g_104a = 0;
        return;
    }
    for (i = 0; i <= g_9316; i++) {
        if (g_96ea[g_7092[i].f_04c].f_020 == 7 && g_1e30[i].f_018 == 0
            && g_7092[i].f_050 != 0x16 && g_7092[i].f_050 != 0x17
            && (d = fn_08_285a(&y, &x, g_1e30[i].f_004, g_1e30[a].f_004))
               < 2400
            && (t != 6 || g_a157[t] >= g_a14d[t])) {
            if (fn_13_adbe(a, 0x15, -1)) {
                fn_03_06ec(a, 14, i, msg);
                g_a163 = (char)t;
                if (a == g_9646)
                    g_a14d[t]++;
                return;
            } else {
                fn_03_06ec(a, 14, i, 0x44);
                return;
            }
        } else if (g_96ea[g_7092[i].f_04c].f_020 == 7
                   && g_1e30[i].f_018 == 0)
            flag = 0;
    }
    if (g_9648 > 4 && g_9648 < 1000) {
        fn_03_06ec(g_9646, 7, 0, 0x6e);
        g_9648 = 1001;
    }
}

/* @addr 13:9ce0 */
int far fn_13_9ce0(int a)
{
    int i, u, s, k, done;

    u = done = 0;
    if ((a != g_9646 || g_9134 != 0) && g_7092[a].f_09a > g_1e50)
        return 0;
    s = g_7092[a].f_03c;
    k = g_7092[a].f_03e;
    if (!g_1df8[s][k].f_053) {
        for (i = 0; i <= g_9316; i++)
            if (g_96ea[g_7092[i].f_04c].f_020
                    == g_96ea[g_7092[a].f_04c].f_020 && i != a)
                break;
        if (i <= g_9316) {
            if (s == 14)
                fn_03_06ec(a, 14, i, 0x23);
            else
                fn_03_06ec(a, 14, i, 0x24);
        } else
            fn_03_06ec(a, 7, 0, 0x25);
        return 0;
    }
    for (i = 0; i <= g_9316; i++) {
        if (g_1e30[i].f_018 == 0 && g_7092[i].f_0ea
            && (g_7092[i].f_050 == 0 || g_7092[i].f_050 == 7
                || g_7092[i].f_096 < g_1e50)
            && i != a
            && g_96ea[g_7092[i].f_04c].f_020
               == g_96ea[g_7092[a].f_04c].f_020) {
            if (g_7092[i].f_050 != 0)
                fn_03_06ec(g_7092[i].f_056, 14, i, 0x13);
            g_7092[i].f_050 = 9;
            g_7092[i].f_092 = g_1e50 + 200;
            g_7092[i].f_052 = s;
            g_7092[i].f_054 = k;
            g_7092[i].f_056 = a;
            g_7092[i].f_096 = g_1e50 + 25000;
            g_7092[a].f_09a = g_1e50 + 15000;
            g_7092[i].f_0eb = 1;
            fn_03_06ec(i, 14, a, 2);
            if (a == g_9646 && g_9134 == 1)
                fn_03_33b4(9);
            done = 1;
            if (i != g_9646)
                fn_03_00f4(i, g_7092[i].f_052, g_7092[i].f_054);
            return 1;
        }
    }
    if (done)
        return 0;
    for (i = 0; i <= g_9316; i++)
        if (g_96ea[g_7092[i].f_04c].f_020 == g_96ea[g_7092[a].f_04c].f_020
            && i != a)
            break;
    if (i <= g_9316)
        fn_03_06ec(a, 14, i, 0x26);
    else
        fn_03_06ec(a, 7, 0, 0x27);
    return 0;
}

/* Object a asks the others to join its attack on k [inferred]. The bare
 * label l1 (no goto) is needed to match: it resets CL's register
 * tracking after the first call. */
/* @addr 13:8e98 */
void far fn_13_8e98(int a)
{
    int i, u, s, k, done;

    u = done = 0;
    s = g_7092[a].f_03c;
    k = g_7092[a].f_03e;
    if (s != 14)
        return;
    if ((a != g_9646 || g_9134 != 0) && g_7092[a].f_09a > g_1e50)
        return;
    g_7092[a].f_09a = g_1e50 + 5000;
    if (fn_13_910a(a)) {
        fn_03_06ec(a, 7, 0, 100);
        return;
    }
    for (i = 0; i <= g_9316; i++) {
        if (g_96ea[g_7092[i].f_04c].f_020 != 6 && g_1e30[i].f_018 == 0
            && g_7092[i].f_0ea
            && (g_7092[i].f_050 == 0 || g_7092[i].f_050 == 7
                || g_7092[i].f_096 < g_1e50 || a == g_9646)
            && (u = fn_13_2688(i, k) + -50 * g_7092[i].f_05b
                    + fn_13_2688(i, a)) > 0
            && i != a && k != i) {
            if (i == g_9646 && g_9134 && flow_interactive) {
                if (g_1e50 - 15000 > g_8858) {
                    g_964e = 5;
                    g_9654 = a;
                    g_9650 = s;
                    g_9652 = k;
                    g_8858 = g_1e50;
                    fn_03_06ec(g_9646, 14, a, 0x34);
                }
                return;
            }
            if (g_96ea[g_7092[i].f_04c].f_020 != 7) {
                g_7092[i].f_050 = 5;
                done = 1;
                fn_03_06ec(g_7092[i].f_056, 14, a, 0x13);
            l1:
                g_7092[i].f_092 = g_1e50 + 200;
                g_7092[i].f_096 = g_1e50 + 20000;
                g_7092[a].f_09a = g_1e50 + 15000;
                g_7092[i].f_052 = g_7092[a].f_03c;
                g_7092[i].f_054 = g_7092[a].f_03e;
                g_7092[i].f_0eb = 1;
                fn_03_06ec(i, 14, a, 2);
                g_7092[i].f_056 = a;
                fn_13_2714(g_7092[a].f_03e, a, 15, 0x32, 1, -1);
                return;
            }
        }
    }
    if (done)
        return;
    if (a != g_9646 || flow_interactive)
        fn_03_06ec(a, 7, 0, 5);
}

/* Pick an ally of a against b, or a negative reason code [inferred]. */
/* @addr 13:78b8 */
int far fn_13_78b8(int a, int b)
{
    int i, r, m, d;

    if (g_96ea[g_7092[a].f_04c].f_006 / 10 > g_7092[a].f_01c)
        return -6;
    m = fn_13_2688(a, b);
    if (g_96ea[g_7092[b].f_04c].f_020 == g_96ea[g_7092[a].f_04c].f_020)
        m += 200;
    if (g_7092[b].f_05b < 3)
        m += (3 - g_7092[b].f_05b) * 4;
    m += 20 * g_7092[a].f_0f4[b][6];
    m += 40 * g_7092[a].f_0f4[b][8];
    if (g_7092[a].f_0cb == b)
        m += 600;
    for (i = 0; i <= g_9316; i++) {
        if (g_1e30[i].f_018 == 0 && i != a && i != b && g_7092[i].f_0ea
            && g_7092[i].f_030 == g_7092[a].f_052
            && g_7092[i].f_032 == g_7092[a].f_054
            && (g_7092[i].f_036 == 1 || fn_13_2688(i, b) < 0)) {
            r = fn_13_2688(a, i);
            if (g_96ea[g_7092[i].f_04c].f_020 == g_96ea[g_7092[a].f_04c].f_020)
                r += 200;
            if (g_96ea[g_7092[i].f_04c].f_020 == 7) {
                if (g_96ea[g_7092[a].f_04c].f_020 == 3
                    || g_96ea[g_7092[a].f_04c].f_020 == 6)
                    r -= 150;
                else if (g_96ea[g_7092[a].f_04c].f_020 == 1
                         || g_96ea[g_7092[a].f_04c].f_020 == 5)
                    r += 20;
                else
                    r += 100;
            }
            r += 25 * g_7092[i].f_0f4[b][1];
            d = fn_04_5d9c(a, i);
            d += g_7092[a].f_05b * d / -5;
            if (g_96ea[g_7092[b].f_04c].f_020 == g_96ea[g_7092[a].f_04c].f_020
                || g_96ea[g_7092[a].f_04c].f_020 == 4)
                d <<= 1;
            if (g_7092[a].f_0cb == b)
                d += 50;
            if (d < 50)
                return -2;
            if (m < r) {
                if (g_96ea[g_7092[i].f_04c].f_020 == 7)
                    return -3;
                if (g_7092[b].f_0f4[i][1] + 2 < g_7092[i].f_0f4[b][1])
                    return -4;
                return -5;
            }
            return i;
        }
    }
    return -1;
}

/* Object n reacts to the ones attacking it: counts them, then flees,
 * fights back or asks for help [inferred]. */
/* @addr 13:7ba2 */
void far fn_13_7ba2(int n)
{
    int i, cnt, j, best, bestj, u1, t, u2, flag;

    cnt = 0;
    if (n == g_9646 && flow_interactive)
        return;
    if (g_92e8 || g_9320 == 7 || CLS(n) == 7)
        return;
    t = -1;
    if (g_1e30[n].f_032 == 14)
        t = g_1e30[n].f_034;
    flag = 0;
    if ((g_7092[n].f_050 == 1 || g_7092[n].f_050 == 5)
        && g_7092[n].f_0b6[g_7092[n].f_054 + 10] == 0)
        flag = 1;
    best = 20000;
    bestj = -1;
    if (g_7092[n].f_050 != 0 && g_7092[n].f_050 != 7
        && g_7092[n].f_096 > g_1e50)
        return;
    for (i = 0; i <= g_9316; i++) {
        if (g_1e30[i].f_018 == 0 && g_7092[i].f_030 == 14
            && g_7092[i].f_032 == n && g_7092[i].f_036 == 1
            && g_7092[i].f_0ea) {
            u1 = fn_04_5d9c(n, i);
            if (u1 < best) {
                best = u1;
                bestj = i;
            }
            cnt++;
        }
    }
    for (i = 0; i < g_940a; i++) {
        if (g_1e00[i].f_018 == 0 && g_52ec[i].f_1c == 14
            && g_52ec[i].f_1e == n && g_52ec[i].f_12 == 10)
            cnt++;
    }
    if (t != -1) {
        bestj = t;
        cnt++;
    }
    if (cnt) {
        if (bestj != -1 && g_7092[n].f_0f4[8][bestj] < -1)
            cnt++;
        if (flag && g_7092[n].f_024 > 320 && t == -1)
            return;
        if (g_7092[n].f_036 != 4
            && (g_7092[n].f_050 != 3 || g_7092[n].f_024 < 20)
            && (g_7092[n].f_05c * cnt * 6 + 15 > g_7092[n].f_024
                || g_7092[n].f_05c * cnt * 6 + 17 > g_7092[n].f_026)
            && (g_7092[n].f_050 == 0
                || g_7092[n].f_096 - 7000 < g_1e50)) {
            if ((cnt * 20 + 35 > best
                 || 15 * g_7092[n].f_05c + 20 > g_7092[n].f_024)
                && bestj != -1 && g_7092[n].f_0f4[8][bestj] < -1) {
                g_7092[n].f_004 = g_7092[n].f_030 = 14;
                g_7092[n].f_006 = g_7092[n].f_032 = bestj;
                g_7092[n].f_03a = 5;
                g_7092[n].f_038 = 5;
                g_7092[n].f_036 = 4;
                g_7092[n].f_034 = 4;
                g_7092[n].f_050 = 7;
                g_7092[n].f_092 = g_1e50 + 4000;
                fn_03_06ec(bestj, 14, n, 0x47);
            } else if (g_7092[n].f_028 < 50
                       && g_7092[n].f_05c * 8 + 35 > g_7092[n].f_024) {
                g_7092[n].f_050 = 13;
                g_7092[n].f_056 = n;
                g_7092[n].f_092 = g_7092[n].f_096 = g_1e50 + 1000;
                g_7092[n].f_0eb = 0;
                if (g_7092[n].f_050 >= 2 && g_7092[n].f_050 <= 4) {
                    if (g_7092[n].f_052 == 14 && g_7092[n].f_056 == n)
                        fn_03_06ec(g_7092[n].f_054, 14, n, 0x8a);
                    else
                        fn_03_06ec(g_7092[n].f_056, 14, n, 0x73);
                    g_7092[n].f_0f4[8][g_7092[n].f_054] = 0;
                    g_7092[n].f_0b6[g_7092[n].f_054 + 10] = -1;
                }
                if (g_7092[n].f_050 == 1 || g_7092[n].f_050 == 2) {
                    fn_03_06ec(g_7092[n].f_054, 14, n, 0x13);
                    fn_03_06ec(g_7092[n].f_056, 14, n, 0x13);
                }
            }
        } else if (g_7092[n].f_036 == 4 && cnt * 20 + 35 < best) {
            g_7092[n].f_036 = 1;
            g_7092[n].f_034 = 1;
            fn_04_8346(n, g_7092[n].f_030, g_7092[n].f_032, 0x10);
        }
        if (fn_13_9bb8(n, cnt))
            fn_16_0b4e(n);
        if (g_7092[n].f_024 < cnt * 20 + 25 && bestj != -1) {
            for (j = 0; j <= g_9316; j++) {
                if (g_1e30[j].f_018 == 0 && g_7092[j].f_0ea && j != n
                    && g_7092[j].f_050 == 1 && g_7092[j].f_054 == n
                    && j != g_9646)
                    return;
            }
            if (!fn_13_81c2(n))
                g_7092[n].f_09a = 1;
        } else if (cnt && bestj != -1
                   && (cnt > 1 || best < 78
                       || (g_7092[n].f_032 == g_952e
                           && g_7092[n].f_030 == 14 && g_9e49 != 10))) {
            fn_03_00f4(n, 14, bestj);
            if (!fn_13_9970(n))
                g_7092[n].f_09a = 1;
        }
        if (CLS(n) == 2 && cnt && bestj != -1) {
            for (j = 0; j <= g_9316; j++) {
                if (g_1e30[j].f_018 == 0 && g_7092[j].f_0ea && j != n
                    && g_7092[j].f_050 == 1 && g_7092[j].f_054 == n
                    && j != g_9646)
                    return;
            }
            if (!fn_13_81c2(n))
                g_7092[n].f_09a = 1;
        }
    }
    if ((cnt == 0 || best > 60) && g_7092[n].f_036 == 4) {
        g_7092[n].f_034 = 3;
        g_7092[n].f_036 = 3;
        g_7092[n].f_050 = 0;
        g_7092[n].f_092 = g_1e50;
    }
    if (fn_13_9bb8(n, cnt))
        fn_16_0b4e(n);
    if (g_7092[n].f_036 == 1 && g_7092[n].f_030 == 14
        && g_7092[n].f_0f4[8][g_7092[n].f_032] < -2
        && fn_13_2688(n, g_7092[n].f_032) < -150 && g_7092[n].f_0ea) {
        fn_03_00f4(n, 14, g_7092[n].f_032);
        if (!fn_13_9970(n))
            g_7092[n].f_09a = 1;
    }
    if (g_9418 > 1 && g_7092[n].f_030 != 14 && rand() % 3 == 0
        && g_7092[n].f_09a < g_1e50) {
        for (j = 0; j < g_9418; j++) {
            if (g_1e1c[j].f_018 == 0) {
                fn_03_00f4(n, 9, j);
                fn_13_9970(n);
                break;
            }
        }
    }
}

/* Object n looks for a helper among the others (like fn_13_8570) [inferred].
 * Returns 1 if one joined, 0 if none, -1 when n asked too recently. */
/* @addr 13:81c2 */
int far fn_13_81c2(int n)
{
    int j, u, sc, found;

    u = found = 0;
    if ((n != g_9646 || g_9134 != 0) && g_7092[n].f_09a > g_1e50)
        return -1;
    g_7092[n].f_09a = g_1e50 + 5000;
    fn_13_4eec(n, 15);
    for (j = 0; j <= g_9316; j++) {
        if (g_1e30[j].f_018 == 0 && g_7092[j].f_0ea && j != n
            && (g_7092[j].f_050 == 0 || g_7092[j].f_050 == 7
                || g_7092[j].f_096 < g_1e50 || g_7092[j].f_056 == n
                || (flow_interactive && n == g_9646))) {
            sc = fn_13_2688(n, j) + g_7092[j].f_05b * -100;
            if (g_7092[j].f_024 < 40)
                sc -= 100;
            if (CLS(j) == CLS(n))
                sc += 100;
            if ((g_7092[j].f_030 == 14 && g_7092[j].f_032 == n && g_7092[j].f_036 == 1)
                || (g_7092[n].f_030 == 14 && g_7092[n].f_032 == j && g_7092[n].f_036 == 1))
                sc -= 800;
            if (CLS(j) == 0 && CLS(n) == 2)
                sc += 350;
            if (g_96ea[g_7092[n].f_04c].f_006 / 10 > g_7092[n].f_01c)
                sc -= 1000;
            if (sc > -150) {
                fn_13_4eec(n, 20);
                if (n == g_9646)
                    fn_13_4eec(j, 40);
                if (j == g_9646 && g_9134 && flow_interactive) {
                    if (g_1e50 - 15000 > g_8858) {
                        g_964e = 1;
                        g_9652 = g_9654 = n;
                        g_8858 = g_1e50;
                        fn_03_06ec(g_9646, g_9650 = 14, n, 0x34);
                    }
                } else if (CLS(j) != 7) {
                    if (g_7092[j].f_050)
                        fn_03_06ec(g_7092[j].f_056, 14, n, 0x13);
                    if (n == g_9646 && g_9134 == 1)
                        fn_03_33b4(1);
                    g_7092[j].f_092 = g_1e50 + 200;
                    found = g_7092[j].f_050 = 1;
                    g_7092[j].f_052 = 14;
                    g_7092[j].f_054 = n;
                    g_7092[n].f_09a = g_7092[j].f_096 = g_1e50 + 15000;
                    g_7092[j].f_056 = n;
                    fn_03_00f4(j, 14, n);
                    g_7092[j].f_0eb = 1;
                    g_7092[j].f_0a2 = g_1e50 - g_7092[j].f_05b * 2000 + 8000;
                    fn_03_06ec(j, 14, n, 2);
                    if (n != g_9646)
                        fn_13_2714(n, j, 15, 0x23, 0, -1);
                    else
                        fn_13_2714(n, j, 15, 15, 0, -1);
                    return 1;
                }
            }
        }
    }
    if (!found) {
        if (n == g_9646 || rand() % 14 < 12 - g_9208
            || (g_0992 + 20 < g_932a && !fn_13_adbe(n, 4, 0x68)))
            if (n != g_9646 || flow_interactive)
                fn_03_06ec(n, 7, 0, 6);
    }
    return 0;
}

/* Object n is asked to fight k: decides whether to accept the duel and
 * sets both up for it [inferred]. */
/* @addr 13:915c */
void far fn_13_915c(int n)
{
    int u1, s, k, rel, dist, sc, t, u2, d, res, range;

    u1 = res = 0;
    s = g_7092[n].f_03c;
    k = g_7092[n].f_03e;
    g_7092[n].f_09a = g_1e50 + 5000;
    if (s != 14)
        fn_03_06ec(n, 7, 0, 0x14);
    else if (CLS(k) == 7)
        fn_03_06ec(n, 14, k, 0x40);
    else if (g_96ea[g_7092[k].f_04c].f_006 / 10 > g_7092[k].f_01c)
        fn_03_06ec(n, 14, k, 0xbc);
    else if (g_7092[k].f_050 == 1)
        fn_03_06ec(n, 14, k, 0xbd);
    else if ((n == g_9646 && (!g_9134 || flow_interactive))
             || g_7092[n].f_09a <= g_1e50 || g_7092[n].f_0b6[k + 10] >= 4) {
        range = 0;
        d = fn_04_5d9c(n, k);
        if (d > 500 || d < 20) {
            if (g_7092[k].f_05c > 0 && k != g_9646) {
                if (d > 500) {
                    fn_03_06ec(n, 14, k, 0x4c);
                    fn_13_81c2(k);
                    return;
                }
                fn_03_06ec(n, 14, k, 0x4e);
                goto out;
            }
            if (d < 20)
                range = 1;
            if (d > 500)
                range = 2;
        }
        if (g_7092[k].f_052 == 14 && g_7092[k].f_054 == n
            && g_7092[k].f_050 >= 2 && g_7092[k].f_050 <= 4
            && g_7092[k].f_056 == k
            && g_7092[n].f_052 == 14 && g_7092[n].f_054 == k
            && g_7092[n].f_050 >= 2 && g_7092[n].f_050 <= 4
            && g_7092[n].f_056 == n) {
            fn_03_06ec(n, 14, k, 0x74);
            return;
        }
        if (!g_1e30[k].f_018 && g_7092[k].f_0ea) {
            dist = fn_04_5d9c(n, k);
            t = 30 * g_7092[k].f_05c;
            rel = fn_13_2688(k, n);
            sc = 0;
            if (g_7092[n].f_0b6[k + 10] > 2)
                sc = 30 * g_7092[n].f_0b6[k + 10];
            if (rel > 50) {
                sc += 20 * g_7092[k].f_05b;
                sc += rel / -5 - abs(100 - dist) * 2;
                sc += 15 * g_7092[n].f_0b6[k + 10];
                if (g_7092[n].f_0b6[k + 10] == -1)
                    sc -= 100;
                if (range
                    || (sc > -70
                        && (g_7092[k].f_050 == 0 || g_7092[k].f_050 == 7
                            || g_7092[k].f_096 < g_1e50 || k == g_9646)))
                    res = 2;
                else if (n != g_9646 || flow_interactive) {
                    if (g_7092[k].f_050 != 0 && g_7092[k].f_096 > g_1e50)
                        fn_03_06ec(n, 14, k, 0x10);
                    else
                        fn_03_06ec(n, 14, k, 0xe);
                }
            } else {
                if (g_7092[k].f_050 != 0 && g_7092[k].f_050 != 7
                    && g_7092[k].f_096 > g_1e50)
                    sc = -110;
                else
                    sc = -30;
                sc += 25 * g_7092[n].f_0b6[k + 10] - rel / 5 - t + dist;
                if (g_7092[n].f_0b6[k + 10] == -1)
                    sc -= 140;
                if (range)
                    res = 1;
                else if (sc > -90)
                    res = 1;
                else if (n != g_9646 || flow_interactive) {
                    if (g_7092[k].f_050 != 0 && g_7092[k].f_050 != 7
                        && g_7092[k].f_096 > g_1e50)
                        fn_03_06ec(n, 14, k, 0x10);
                    else
                        fn_03_06ec(n, 14, k, 0xf);
                }
            }
            if (res == 0) {
                g_7092[n].f_0b6[k + 10] = -1;
                return;
            }
            g_7092[n].f_0b6[k + 10] = 21;
            g_7092[k].f_0b6[n + 10] = 20;
            if (g_7092[k].f_050)
                fn_03_06ec(g_7092[k].f_056, 14, n, 0x13);
            if (g_7092[n].f_050)
                fn_03_06ec(g_7092[n].f_056, 14, n, 0x13);
            if (k == g_9646 && g_9134 && flow_interactive) {
                if (g_1e50 - 15000 > g_8858) {
                    g_964e = 11;
                    g_9650 = 14;
                    g_9652 = g_9654 = n;
                    g_8858 = g_1e50;
                }
            } else {
                g_7092[k].f_050 = 2;
                g_7092[k].f_092 = g_1e50 + 200;
                g_7092[k].f_096 = g_1e50 + 40000;
                g_7092[k].f_09a = g_1e50 + 8000;
                g_7092[k].f_052 = 14;
                g_7092[k].f_054 = n;
                g_7092[k].f_056 = k;
                g_7092[k].f_0eb = 1;
                g_7092[k].f_030 = 14;
                g_7092[k].f_032 = n;
                g_7092[k].f_036 = 1;
                g_7092[k].f_0a2 = g_1e50 - g_7092[k].f_05c * 2000 + 8000;
                fn_04_8346(k, 14, n, 0x15);
                if (k == g_9646)
                    g_0a62 = 1;
                g_7092[n].f_050 = 2;
                g_7092[n].f_092 = g_1e50 + 200;
                g_7092[n].f_096 = g_1e50 + 40000;
                g_7092[n].f_09a = g_1e50 + 8000;
                g_7092[n].f_052 = 14;
                g_7092[n].f_054 = k;
                g_7092[n].f_056 = n;
                g_7092[n].f_0eb = 0;
                g_7092[n].f_036 = 1;
                if (n != g_9646)
                    fn_03_00f4(n, 14, k);
                g_7092[n].f_030 = 14;
                g_7092[n].f_032 = k;
                g_7092[n].f_0a2 = g_1e50 - g_7092[n].f_05c * 2000 + 8000;
                if (res == 1 && (CLS(n) == 4 || CLS(n) == 0))
                    g_7092[n].f_050 = 3;
                fn_04_8346(n, 14, k, 0x14);
                if (g_9320 != 7)
                    g_8e00 = g_8e04 = g_9680 = g_9682 = 0;
                if (res) {
                    g_7092[n].f_0f4[8][k] = 0;
                    g_7092[k].f_0f4[8][n] = 0;
                    if (n == g_9646 && g_9134 == 1)
                        fn_03_33b4(3);
                }
                fn_13_2714(g_7092[n].f_03e, n, -12, -55, 1, -1);
            }
            if (range == 1) {
                fn_03_06ec(k, 14, n, 0x4b);
                fn_03_06ec(n, 14, k, 0x4d);
            } else if (range == 2) {
                fn_03_06ec(k, 14, n, 0x4d);
                fn_03_06ec(n, 14, k, 0x4b);
            } else if (g_7092[n].f_050 == 3) {
                fn_03_06ec(k, 14, n, 0x82);
                fn_03_06ec(n, 14, k, 0x12);
            } else if (res == 1) {
                fn_03_06ec(n, 14, k, 0x12);
                fn_03_06ec(k, 14, n, 0x16);
            } else if (res == 2) {
                fn_03_06ec(n, 14, k, 0x11);
                fn_03_06ec(k, 14, n, 0x15);
            }
        }
    }
out:;
}

/* Object n in duel states 0x14-0x17 (approach, challenge, fight) [inferred]. */
/* @addr 13:a6bc */
void far pascal fn_13_a6bc(int n)
{
    int i, j, k, d, y, x, c, u2, flag, cnt;

    g_7092[n].f_092 = g_1e50 + 750;
    if (g_9412 && g_1e30[n].f_036 == -1) {
        for (i = 0; i < g_9412; i++) {
            if (g_66e4[i].f_00 == 0x10 && g_1e10[i].f_018 == 0) {
                g_7092[n].f_004 = 6;
                g_7092[n].f_006 = i;
                g_7092[n].f_038 = 2;
                g_7092[n].f_034 = 2;
                if (g_1e30[n].f_036 != 14)
                    return;
                for (j = 0; j <= g_7092[n].f_0c9; j++) {
                    if (g_7092[n].f_0b6[j] == 15) {
                        fn_04_584c(j, n, 0);
                        break;
                    }
                }
                return;
            }
        }
    }
    if (g_7092[n].f_050 == 0x14) {
        flag = 0;
        if (g_1df8[g_7092[n].f_052][g_7092[n].f_054].f_018)
            flag = 1;
        if (!g_7092[g_7092[n].f_054].f_0ea)
            flag = 1;
        if ((g_7092[g_7092[n].f_054].f_036 != 1 && g_7092[n].f_096 < g_1e50)
            || g_7092[n].f_096 < g_1e50 + 5000)
            flag = 1;
        if (flag) {
            k = g_7092[n].f_054;
            for (i = 0; i <= g_9316; i++) {
                if (++k > g_9316)
                    k = 0;
                if (g_1e30[k].f_018 == 0 && g_7092[k].f_0ea && CLS(k) != 7)
                    break;
            }
            g_7092[n].f_052 = 14;
            g_7092[n].f_054 = k;
            g_7092[n].f_096 = g_1e50 + 13000;
            if (g_1e30[k].f_018 || !g_7092[k].f_0ea || CLS(k) == 7) {
                fn_03_06ec(g_9646, 14, n, 0xb7);
                g_7092[n].f_004 = 12;
                g_7092[n].f_006 = 0;
                g_7092[n].f_038 = 2;
                g_7092[n].f_034 = 2;
                return;
            }
        }
        g_7092[n].f_004 = g_7092[n].f_052;
        g_7092[n].f_006 = g_7092[n].f_054;
        g_7092[n].f_038 = 2;
        g_7092[n].f_034 = 3;
        if (g_7092[g_7092[n].f_054].f_030 == 14
            && g_7092[g_7092[n].f_054].f_032 == n
            && g_7092[g_7092[n].f_054].f_036 == 1) {
            g_7092[n].f_034 = 1;
            fn_04_8346(n, 14, g_7092[n].f_054, 0x12);
        }
    } else if (g_7092[n].f_050 == 0x15) {
        if (g_7092[n].f_0eb == 1) {
            fn_03_06ec(g_7092[n].f_054, 14, n, 0x3b);
            g_7092[n].f_0eb = 0;
        } else {
            g_7092[n].f_050 = 0x14;
            g_7092[n].f_096 = g_1e50 + 5000;
        }
        g_7092[n].f_092 = g_1e50 + 2000;
    } else if (g_7092[n].f_050 == 0x16) {
        if (g_1df8[g_7092[n].f_052][g_7092[n].f_054].f_018 == 0
            && g_7092[g_7092[n].f_054].f_0ea) {
            k = g_7092[n].f_054;
            if (g_7092[k].f_036 == 1 && g_7092[k].f_030 == 14
                && g_7092[k].f_032 == n && g_7092[n].f_096 < g_1e50) {
                cnt = 0;
                for (i = 0; i < 5; i++)
                    if ((&g_7092[n].f_042)[i])
                        cnt++;
                if (cnt > 1) {
                    if (k == g_9646)
                        g_a154++;
                    g_7092[n].f_050 = 0x17;
                    if (g_7092[n].f_0eb == 2 || g_7092[n].f_0eb == -1)
                        g_7092[n].f_0eb = 2;
                    else
                        g_7092[n].f_0eb = 1;
                    g_7092[n].f_096 = g_1e50 + 20000;
                    g_7092[n].f_092 = g_1e50;
                    return;
                }
            }
            if (g_7092[n].f_0eb > 0) {
                g_7092[n].f_004 = 14;
                g_7092[n].f_006 = k;
                g_7092[n].f_038 = 2;
                g_7092[n].f_034 = 3;
                d = fn_08_285a(&y, &x, g_1e30[n].f_004, g_1e30[k].f_004);
                if (d < 250) {
                    if (g_7092[n].f_0eb == 1) {
                        fn_03_06ec(k, 14, n, 0x3d);
                        g_7092[n].f_0eb = 0;
                        g_a147 = g_1e68;
                        g_a14b = g_91f8;
                        g_a161 = g_a163;
                        g_a162 = (char)n;
                    } else {
                        fn_03_06ec(k, 14, n, 0x57);
                        g_7092[n].f_0eb = -1;
                    }
                    if (g_7092[k].f_05c > 0 && (k != g_9646 || !flow_interactive)) {
                        if ((c = CLS(k)) != 3 && c != 6 && c != 1) {
                            g_7092[k].f_050 = 10;
                            g_7092[k].f_096 = g_1e50 + 500;
                            g_7092[k].f_056 = n;
                        } else {
                            g_7092[k].f_050 = 2;
                            g_7092[k].f_052 = 14;
                            g_7092[k].f_054 = n;
                            g_7092[k].f_056 = k;
                            fn_04_8346(k, 14, n, 10);
                        }
                    }
                    for (i = 0; i <= g_7092[n].f_0c9; i++) {
                        if (g_7092[n].f_0b6[i] == 15) {
                            fn_04_584c(i, n, 0);
                            break;
                        }
                    }
                }
            } else {
                g_7092[n].f_004 = 12;
                g_7092[n].f_006 = 0;
                g_7092[n].f_038 = 2;
                g_7092[n].f_034 = 2;
            }
        } else {
            g_7092[n].f_004 = 12;
            g_7092[n].f_006 = 0;
            g_7092[n].f_038 = 2;
            g_7092[n].f_034 = 2;
        }
        if (g_7092[n].f_0eb < 1 && g_1e30[n].f_036 != 10
            && (g_1e30[n].f_036 != 14 || g_1e30[n].f_038 != k))
            g_7092[n].f_0eb = 1;
    } else {
        g_7092[n].f_050 = 0x17;
        k = g_7092[n].f_054;
        if (g_7092[n].f_0eb != 0) {
            if (g_7092[n].f_0eb == 2
                || (g_7092[n].f_0f4[k][1] > 2 && g_7092[n].f_0f4[8][k] < -2
                    && g_7092[n].f_024 < 55)) {
                fn_03_06ec(g_9646, 14, n, 0xb7);
                g_7092[n].f_004 = 12;
                g_7092[n].f_006 = 0;
                g_7092[n].f_038 = 2;
                g_7092[n].f_034 = 2;
                g_7092[n].f_0eb = 0;
                fn_13_adbe(k, 20, 0x58);
                return;
            }
            fn_03_06ec(k, 14, n, 0x3e);
            g_7092[n].f_0eb = 0;
            fn_03_00f4(n, g_7092[n].f_052, g_7092[n].f_054);
            fn_04_8346(n, 14, g_7092[n].f_054, 0x13);
        }
        if (g_7092[n].f_096 < g_1e50 && g_7092[n].f_05c == 1) {
            g_7092[n].f_050 = 0x16;
            g_7092[n].f_0eb = 2;
            g_7092[n].f_092 = g_1e50;
            g_7092[n].f_096 = g_1e50 + 5000;
            return;
        }
        if (g_1e30[k].f_018 || !g_7092[k].f_0ea) {
            fn_03_06ec(g_9646, 14, n, 0xb7);
            g_7092[n].f_004 = 12;
            g_7092[n].f_006 = 0;
            g_7092[n].f_038 = 2;
            g_7092[n].f_034 = 2;
            return;
        }
        fn_03_00f4(n, g_7092[n].f_052, g_7092[n].f_054);
        g_7092[n].f_004 = 14;
        g_7092[n].f_006 = k;
        g_7092[n].f_038 = 2;
        g_7092[n].f_034 = 1;
    }
}

/* Object n's per-tick behaviour by state f_050 (follow, escort, flee,
 * seek help, ...); class 7 goes to fn_13_a6bc [inferred]. */
/* @addr 13:6900 */
void far pascal fn_13_6900(int n)
{
    int d, t, i, y, x, best, bt, bi, u1, best2, bk, dist, cnt, r;
    char buf[40];

    g_7092[n].f_092 = g_1e50 + 4000;
    if (CLS(n) == 7) {
        fn_13_a6bc(n);
    } else if (CLS(n) == 6 && g_7092[n].f_056 != n
               && (n != g_9646 || !flow_interactive)) {
        g_7092[n].f_050 = 0;
        fn_03_06ec(g_7092[n].f_056, 14, n, 0x83);
        g_7092[n].f_092 = g_1e50;
        g_7092[n].f_0eb = 0;
        if (!flow_interactive && n == g_9646) {
            fn_10_a332(g_8630, 0x58d, 1, g_7092[g_9646].f_056, buf, 5);
            g_058c = 1;
            g_05c0 = g_1e50 + 700;
        }
    } else if (g_7092[n].f_050 == 1) {
        best = 20000;
        r = fn_13_78b8(n, g_7092[n].f_054);
        if (r >= 0) {
            g_7092[n].f_004 = 14;
            g_7092[n].f_006 = r;
            g_7092[n].f_034 = 1;
            g_7092[n].f_038 = 2;
            if (g_7092[n].f_0eb == 1) {
                g_7092[n].f_0eb = 0;
                fn_13_2714(g_7092[n].f_054, n, 20, 60, 1, 8);
                fn_03_06ec(g_7092[n].f_054, 14, n, 1);
                if (CLS(n) == 4) {
                    if (g_7092[n].f_0ec[r] != 0 && g_7092[n].f_0ec[r] <= 5
                        && g_7092[n].f_060[r + 8] > 3 && CLS(n) != 4) {
                        fn_03_06ec(r, 14, n, 0x7f);
                        g_7092[n].f_050 = 4;
                        fn_04_8346(n, 14, r, 11);
                        g_7092[n].f_092 = g_1e50 + 500;
                        g_7092[n].f_052 = 14;
                        g_7092[n].f_054 = r;
                        g_7092[n].f_0eb = 1;
                        g_7092[n].f_060[r + 8] = 0;
                    } else
                        fn_03_06ec(r, 14, n, 0x80);
                    fn_13_2714(n, r, 0, -140, 0, 3);
                } else
                    fn_03_06ec(r, 14, n, 0x81);
                if (g_7092[n].f_050 != 4)
                    fn_04_8346(n, 14, r, 14);
            }
        } else if (r < -1) {
            fn_03_06ec(g_7092[n].f_054, 14, n, 0xad - r);
            g_7092[n].f_050 = 0;
        } else {
            g_7092[n].f_050 = 5;
            g_7092[n].f_092 = g_1e50 + 200;
            fn_03_06ec(g_7092[n].f_056, 14, n, 1);
            fn_03_06ec(g_7092[n].f_054, 14, n, 1);
            g_7092[n].f_0eb = 0;
        }
    } else if (g_7092[n].f_050 >= 2 && g_7092[n].f_050 <= 4) {
        if (g_7092[n].f_052 == 14)
            dist = fn_04_5d9c(n, g_7092[n].f_054);
        if (!((g_7092[n].f_052 == 14 && (dist <= 15 || dist >= 600)
             && g_7092[n].f_050 != 4 && (n != g_9646 || !flow_interactive)
             && g_7092[n].f_05c >= 2)
            || g_1df8[g_7092[n].f_052][g_7092[n].f_054].f_018 == 1
            || (g_7092[n].f_052 == 14 && !g_7092[g_7092[n].f_054].f_0ea)
            || (dist <= 75 && g_7092[n].f_0f4[8][g_7092[n].f_054] <= -6
                && g_7092[n].f_050 < 3 && g_7092[n].f_052 == 14))) {
            g_7092[n].f_004 = g_7092[n].f_052;
            g_7092[n].f_006 = g_7092[n].f_054;
            g_7092[n].f_034 = 1;
            g_7092[n].f_038 = 2;
            if (g_7092[n].f_0eb == 1) {
                g_7092[n].f_0eb = 0;
                if (g_7092[n].f_056 == n && g_7092[n].f_052 == 14
                    && g_7092[n].f_054 == g_9646)
                    fn_10_754a(0x3f, 0, 0, 0);
                else
                    fn_03_06ec(g_7092[n].f_056, 14, n, 1);
            }
        } else {
            if (g_7092[n].f_052 == 14
                && g_7092[n].f_0f4[8][g_7092[n].f_054] < g_7092[n].f_05c - 7
                && 20 * g_7092[n].f_05b + 15 > fn_04_5d9c(n, g_7092[n].f_054)) {
                if (g_7092[n].f_056 == n)
                    fn_03_06ec(g_7092[n].f_054, 14, n, 0x8a);
                else
                    fn_03_06ec(g_7092[n].f_056, 14, n, 0x73);
                g_7092[n].f_0f4[8][g_7092[n].f_054] = 0;
                g_7092[n].f_0b6[g_7092[n].f_054 + 10] = -1;
            } else {
                g_7092[n].f_050 = 6;
                fn_03_06ec(g_7092[n].f_056, 14, n, 0x13);
            }
            g_7092[n].f_050 = 0;
        }
    } else if (g_7092[n].f_050 == 5) {
        d = fn_08_285a(&y, &x, g_1e30[n].f_004,
                       g_1df8[g_7092[n].f_052][g_7092[n].f_054].f_004);
        if (d < 350)
            g_7092[n].f_038 = 3;
        else
            g_7092[n].f_038 = 2;
        g_7092[n].f_004 = g_7092[n].f_052;
        g_7092[n].f_006 = g_7092[n].f_054;
        g_7092[n].f_034 = 3;
        g_7092[n].f_092 = g_1e50 + 700;
        if (g_7092[g_7092[n].f_054].f_024 > 40 && g_7092[n].f_096 < g_1e50
            && (n != g_9646 || !g_9134 || !flow_interactive)) {
            fn_03_06ec(g_7092[n].f_056, 14, n, 0x13);
            g_7092[n].f_050 = 0;
            if (g_7092[n].f_0cb == g_7092[n].f_054 && n != g_9646) {
                g_7092[n].f_050 = 10;
                g_7092[n].f_092 = g_1e50 + 500;
                return;
            }
        }
        if (!g_7092[g_7092[n].f_054].f_0ea) {
            g_7092[n].f_050 = 0;
            g_7092[n].f_092 = g_1e50 + 500;
            return;
        }
        r = fn_13_78b8(n, g_7092[n].f_054);
        if (r > -1) {
            g_7092[n].f_006 = r;
            g_7092[n].f_034 = 1;
            g_7092[n].f_038 = 2;
            g_7092[n].f_050 = 1;
            g_7092[n].f_0eb = 1;
            g_7092[n].f_092 = g_1e50 + 700;
            return;
        }
        if (r < -1) {
            fn_03_06ec(g_7092[n].f_054, 14, n, 0xad - r);
            g_7092[n].f_050 = 0;
            if (g_7092[n].f_0cb == g_7092[n].f_054 && n != g_9646)
                g_7092[n].f_050 = 10;
            g_7092[n].f_092 = g_1e50 + 500;
        }
    } else if (g_7092[n].f_050 == 7) {
        if (g_7092[n].f_0eb == 1 && g_7092[n].f_056 != n) {
            g_7092[n].f_0eb = 0;
            fn_03_06ec(g_7092[n].f_056, 14, n, 1);
        }
        g_7092[n].f_092 = g_1e50 + 2000;
        best = 20000;
        bt = -1;
        t = 14;
        for (i = 0; i < g_9406[t]; i++) {
            if (t == 14 && i == n)
                continue;
            if (g_1df8[t][i].f_018 == 0 && g_1df8[t][i].f_044 != 0) {
                d = fn_08_285a(&y, &x, g_1e30[n].f_004, g_1df8[t][i].f_004);
                if (t == 14 && fn_13_2688(i, n) < 100)
                    d -= 150;
                if (d < best) {
                    best = d;
                    bt = t;
                    bi = i;
                }
            }
        }
        if (bt != -1) {
            g_7092[n].f_004 = bt;
            g_7092[n].f_006 = bi;
            g_7092[n].f_038 = 5;
            if (best < 300)
                g_7092[n].f_034 = 3;
            else if (fn_09_88ba(g_1e30[bi].f_00c) > 30
                     || fn_09_88ba(g_1e30[bi].f_00e) > 30) {
                fn_11_5ab6(n, 5);
                g_7092[n].f_034 = 5;
            }
        } else
            g_7092[n].f_034 = 5;
        if (g_7092[n].f_096 < g_1e50 && (n != g_9646 || !flow_interactive))
            g_7092[n].f_050 = 0;
    } else if (g_7092[n].f_050 == 9) {
        if (g_7092[n].f_0eb == 1) {
            g_7092[n].f_0eb = 0;
            fn_03_06ec(g_7092[n].f_056, 14, n, 1);
        }
        best2 = 20000;
        bk = -1;
        for (t = cnt = 0; t <= g_9316; t++) {
            if (g_1e30[t].f_018 == 0 && g_7092[t].f_030 == 14
                && g_7092[t].f_032 == n && g_7092[t].f_036 == 1) {
                dist = fn_04_5d9c(n, t);
                if (dist < best2) {
                    best2 = dist;
                    bk = t;
                }
                cnt++;
            }
        }
        if ((cnt != 0 && best2 < 70) || cnt > 1) {
            if (!g_9134 || !flow_interactive || n != g_9646) {
                g_7092[n].f_050 = g_7092[n].f_052 = 0;
                g_7092[n].f_092 = g_1e50;
                fn_03_06ec(g_7092[n].f_056, 14, n, 0x21);
            }
        }
        if (g_1df8[g_7092[n].f_052][g_7092[n].f_054].f_018) {
            fn_03_06ec(g_7092[n].f_056, 14, n, 0x22);
            g_7092[n].f_050 = 0;
            g_7092[n].f_092 = g_1e50;
        }
        g_7092[n].f_038 = g_7092[n].f_034 = 2;
        g_7092[n].f_004 = g_7092[n].f_052;
        g_7092[n].f_006 = g_7092[n].f_054;
    } else if (g_7092[n].f_050 == 10) {
        if (g_7092[n].f_0eb == 1) {
            g_7092[n].f_0eb = 0;
            fn_03_06ec(g_7092[n].f_056, 14, n, 1);
        }
        best = 20000;
        for (t = 0; t < g_9318 * 2; t += 2) {
            d = fn_08_285a(&y, &x, g_1e30[n].f_004, g_1e28[t].f_004);
            if (d < best) {
                best = d;
                fn_03_06ec(g_9646, 14, n, 0xb7);
                g_7092[n].f_004 = 12;
                g_7092[n].f_006 = t;
                g_7092[n].f_038 = g_7092[n].f_034 = 2;
            }
        }
    } else if (g_7092[n].f_050 == 12) {
        if (g_7092[n].f_0eb == 1) {
            g_7092[n].f_0eb = 0;
            fn_03_06ec(g_7092[n].f_056, 14, n, 1);
        }
        best = 20000;
        r = -1;
        for (i = 0; i < g_940e; i++) {
            if (g_1e08[i].f_018 == 0) {
                d = fn_08_285a(&y, &x, g_1e30[n].f_004, g_1e08[i].f_004);
                if (d < best) {
                    best = d;
                    r = i;
                }
            }
        }
        if (r >= 0) {
            g_7092[n].f_004 = g_7092[n].f_052 = 4;
            g_7092[n].f_054 = r;
            g_7092[n].f_006 = r;
            g_7092[n].f_038 = g_7092[n].f_034 = 2;
        } else {
            fn_03_06ec(g_7092[n].f_056, 14, n, 0x38);
            g_7092[n].f_050 = 0;
        }
    } else if (g_7092[n].f_050 == 13) {
        if (g_7092[n].f_0eb == 1) {
            g_7092[n].f_0eb = 0;
            fn_03_06ec(g_7092[n].f_056, 14, n, 1);
            if ((g_7092[n].f_024 < 25 || g_7092[n].f_028 < 25)
                && g_7092[n].f_0cc + g_7092[n].f_0da > 300)
                fn_16_0b4e(n);
            else if ((g_7092[n].f_05c * 4 + 30 > g_7092[n].f_024
                      || g_7092[n].f_028 < 29)
                     && g_7092[n].f_0cc < 200) {
                bk = -1;
                if (g_7092[n].f_036 != 4 && g_932c) {
                    best2 = 20000;
                    for (t = 0; t <= g_9316; t++) {
                        if (g_1e30[t].f_018 == 0 && g_7092[t].f_030 == 14
                            && g_7092[t].f_032 == n && g_7092[t].f_036 == 1) {
                            bk = t;
                            break;
                        }
                    }
                    if (bk != -1) {
                        g_7092[n].f_004 = g_7092[n].f_030 = 14;
                        g_7092[n].f_006 = g_7092[n].f_032 = bk;
                        g_7092[n].f_03a = 5;
                        g_7092[n].f_038 = 5;
                        g_7092[n].f_036 = 4;
                        g_7092[n].f_034 = 4;
                        g_7092[n].f_050 = 7;
                        g_7092[n].f_092 = g_1e50 + 4000;
                        fn_03_06ec(bk, 14, n, 0x47);
                        return;
                    }
                }
                if (bk == -1) {
                    best = 20000;
                    for (t = 0; t < g_9318 * 2; t += 2) {
                        d = fn_08_285a(&y, &x, g_1e30[n].f_004, g_1e28[t].f_004);
                        if (d < best) {
                            best = d;
                            g_7092[n].f_004 = 12;
                            g_7092[n].f_006 = t;
                            g_7092[n].f_038 = g_7092[n].f_034 = 2;
                        }
                    }
                    g_7092[n].f_092 = g_1e50 + 500;
                    if (CLS(g_9646) == CLS(n))
                        fn_03_06ec(g_9646, 14, n, 0x59);
                    return;
                }
            }
        }
        best = 20000;
        bt = -1;
        for (t = 0; t <= g_9316; t++) {
            if (g_1e30[t].f_018 == 0 && g_7092[t].f_036 == 1
                && g_7092[t].f_030 == 14 && g_7092[t].f_032 == n) {
                d = fn_08_285a(&y, &x, g_1e30[n].f_004, g_1e30[t].f_004);
                if (d < best) {
                    bt = 14;
                    bi = t;
                    best = d;
                }
            }
        }
        for (t = 0; t < g_940a; t++) {
            if (g_1e00[t].f_018 == 0 && g_52ec[t].f_12 == 15
                && g_52ec[t].f_1c == 14 && g_52ec[t].f_1e == n) {
                d = fn_08_285a(&y, &x, g_1e30[n].f_004, g_1e00[t].f_004);
                if (d < best) {
                    bt = 2;
                    bi = t;
                    best = d;
                }
            }
        }
        if (bt != -1) {
            g_7092[n].f_004 = bt;
            g_7092[n].f_006 = bi;
            g_7092[n].f_034 = 1;
            g_7092[n].f_038 = 2;
            g_7092[n].f_092 = g_1e50 + 5000;
            fn_04_8346(n, bt, bi, 15);
            return;
        }
        if (g_7092[n].f_056 != n)
            fn_03_06ec(g_7092[n].f_056, 14, n, 0x39);
        g_7092[n].f_050 = 7;
        g_7092[n].f_092 = g_1e50 + 1500;
        g_7092[n].f_0eb = 1;
        g_7092[n].f_096 = g_1e50 + 20000;
    } else if (g_7092[n].f_050 == 14) {
        if (g_7092[g_7092[n].f_054].f_0ea && !g_1e30[g_7092[n].f_054].f_018
            && g_7092[g_7092[n].f_054].f_036 != 1
            && (g_7092[g_7092[n].f_054].f_036 == 2
                || (g_7092[n].f_054 == g_9646 && !g_9134))) {
            if (g_7092[g_7092[n].f_054].f_036 == 2
                || g_1df8[g_7092[g_7092[n].f_054].f_030][g_7092[g_7092[n].f_054].f_032].f_053) {
                g_7092[n].f_004 = g_7092[g_7092[n].f_054].f_030;
                g_7092[n].f_006 = g_7092[g_7092[n].f_054].f_032;
                g_7092[n].f_038 = g_7092[n].f_034 = 2;
            } else {
                g_7092[n].f_004 = 14;
                g_7092[n].f_006 = g_7092[n].f_054;
                g_7092[n].f_034 = 3;
                g_7092[n].f_038 = 2;
            }
        } else {
            g_7092[n].f_050 = 0;
            g_7092[n].f_092 = g_7092[n].f_096 = g_1e50;
        }
    } else {
        if (n == g_9646 && flow_interactive) {
            if (fn_03_0000(g_7092[n].f_03c, g_7092[n].f_03e)) {
                g_7092[n].f_004 = g_7092[n].f_03c;
                g_7092[n].f_006 = g_7092[n].f_03e;
            }
            g_7092[n].f_050 = 7;
            g_7092[n].f_092 = g_1e50;
            g_7092[n].f_034 = 5;
        } else
            g_7092[n].f_050 = 0;
    }
}
