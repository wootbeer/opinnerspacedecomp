/* INSPACE.EXE segment 13 (selector 1060), second source file (13:6900-end).
 * Calls into the first file (seg13.c: 2688, 2714, 4eec) are far. */
#include "inspace.h"

/* BEGIN STRUCTS */
#pragma pack(1)
/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record. Generated layout; keep in sync between seg13.c/seg14.c. */
typedef struct {
    char pad_000[0xe];
    int f_00e;    /* DS:70a0 */
    char pad_010[0x20];
    int f_030;    /* DS:70c2 */
    int f_032;    /* DS:70c4 */
    char pad_034[0x2];
    int f_036;    /* DS:70c8 */
    char pad_038[0x14];
    int f_04c;    /* DS:70de */
    char pad_04e[0x2];
    int f_050;    /* DS:70e2 */
    int f_052;    /* DS:70e4 */
    int f_054;    /* DS:70e6 */
    int f_056;    /* DS:70e8 */
    char pad_058[0x3];
    char f_05b;    /* DS:70ed */
    char f_05c;    /* DS:70ee */
    char pad_05d[0x3];
    int f_060[16];    /* DS:70f2 */
    int f_080;    /* DS:7112 */
    char pad_082[0x10];
    long f_092;    /* DS:7124 */
    long f_096;    /* DS:7128 */
    unsigned long f_09a;    /* DS:712c */
    char pad_09e[0x36];
    int f_0d4;    /* DS:7166 */
    char pad_0d6[0x13];
    char f_0e9;    /* DS:717b */
    char f_0ea;    /* DS:717c */
    char f_0eb;    /* DS:717d */
    char pad_0ec[0x68];
    long f_154;    /* DS:71e6 */
    char pad_158[0x2];
} OBJ15A;

/* 0x70-byte records reached through far pointers (DS:1e30, DS:1df8[]). */
typedef struct {
    char pad_000[0x4];
    POINT f_004;
    char pad_008[0x4];
    int f_00c;
    int f_00e;
    char pad_010[0x8];
    int f_018;
    char pad_01a[0xc];
    int f_026;
    char pad_028[0x1e];
    int f_046;
    char pad_048[0x28];
} REC70;

/* 0x41-byte records through the far pointer at DS:6e20 [inferred]. */
typedef struct {
    char pad_000[0x3];
    char f_003;
    char pad_004[0x6];
    char f_00a[23];
    int f_021;
    char pad_023[0x1e];
} REC41;

/* 0x2c-byte records through the far pointer at DS:6e1c [inferred]. */
typedef struct {
    char pad_000[0x21];
    int f_021;
    char pad_023[0x9];
} REC2C;

/* 0xad-byte records at DS:970a [inferred base]. */
typedef struct {
    int f_000;
    char pad_002[0xab];
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
extern int g_9646;
extern int g_964e;
extern int g_9650;
extern int g_9652;
extern int g_9654;

void far fn_03_06ec(int, int, int, int);
int far fn_04_8346(int n, int x, int y, int v);
void far fn_10_7480(int a, int b);
int far pascal fn_08_285a(int far *py, int far *px, POINT a, POINT b);
void far fn_13_2714(int, int, int, int, int, int);

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

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_13_8570(int i)
{
    return i;
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

/* near-match 92%: 13:a4f4 (the game copies the pair with two word moves,
 * CL /G3 uses one dword move here) */
void far fn_13_a4f4(void)
{
    PAIR p;

    if (g_9134) {
        p = g_6e52;
        if (p.b == 14) {
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
/* @addr 13:adbe */
void far fn_13_adbe(int a, int b, int c)
{
    int u, r;

    if (!fn_13_ae68(a, b, c))
        return;
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
