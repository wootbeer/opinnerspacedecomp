/* INSPACE.EXE segment 13 (selector 1060), second source file (13:6900-end).
 * Calls into the first file (seg13.c: 2688, 2714, 4eec) are far. */
#include "inspace.h"
#include <stdlib.h>

/* BEGIN STRUCTS */
typedef void (far *FNPTR)(int, int);  /* REC70 handler [inferred] */
#pragma pack(1)
/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record. Generated layout; keep in sync between seg13.c/seg14.c. */
typedef struct {
    char pad_000[0x4];
    int f_004;    /* DS:7096 */
    int f_006;    /* DS:7098 */
    char pad_008[0x6];
    int f_00e;    /* DS:70a0 */
    char pad_010[0xc];
    int f_01c;    /* DS:70ae */
    char pad_01e[0x6];
    int f_024;    /* DS:70b6 */
    int f_026;    /* DS:70b8 */
    int f_028;    /* DS:70ba */
    char pad_02a[0x6];
    int f_030;    /* DS:70c2 */
    int f_032;    /* DS:70c4 */
    int f_034;    /* DS:70c6 */
    int f_036;    /* DS:70c8 */
    char pad_038[0x2];
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
    char pad_058[0x3];
    char f_05b;    /* DS:70ed */
    char f_05c;    /* DS:70ee */
    char pad_05d[0x2];
    char f_05f;    /* DS:70f1 */
    int f_060[16];    /* DS:70f2 */
    int f_080;    /* DS:7112 */
    char pad_082[0x10];
    long f_092;    /* DS:7124 */
    unsigned long f_096;    /* DS:7128 */
    unsigned long f_09a;    /* DS:712c */
    char pad_09e[0x4];
    long f_0a2;    /* DS:7134 */
    char pad_0a6[0x4];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    char pad_0ac[0xa];
    char f_0b6[16];    /* DS:7148 */
    char pad_0c6[0x3];
    char f_0c9;    /* DS:715b */
    char pad_0ca[0x1];
    char f_0cb;    /* DS:715d */
    int f_0cc;    /* DS:715e */
    char pad_0ce[0x6];
    int f_0d4;    /* DS:7166 */
    char pad_0d6[0x4];
    int f_0da;    /* DS:716c */
    char pad_0dc[0x6];
    char f_0e2;    /* DS:7174 */
    char pad_0e3[0x4];
    char f_0e7;    /* DS:7179 */
    char pad_0e8[0x1];
    char f_0e9;    /* DS:717b */
    char f_0ea;    /* DS:717c */
    char f_0eb;    /* DS:717d */
    char pad_0ec[0x8];
    char f_0f4[9][9];    /* DS:7186 */
    char pad_145[0x1];
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
    char pad_010[0x8];
    int f_018;
    int f_01a;
    char pad_01c[0x2];
    int f_01e;
    int f_020;
    int f_022;
    int f_024;
    int f_026;
    int f_028;
    char pad_02a[0x1c];
    int f_046;
    char pad_048[0x9];
    char f_051;
    char f_052;
    char f_053;
    char pad_054[0x12];
    FNPTR f_066;
    char pad_06a[0x6];
} REC70;

/* 0x41-byte records through the far pointer at DS:6e20 [inferred]. */
typedef struct {
    char pad_000[0x1];
    char f_001;
    char f_002;
    char f_003;
    char pad_004[0x2];
    char f_006;
    char pad_007[0x2];
    char f_009;
    char f_00a[23];
    int f_021;
    char pad_023[0x1e];
} REC41;

/* 0x2c-byte records through the far pointer at DS:6e1c [inferred]. */
typedef struct {
    char pad_000[0x1b];
    char f_01b;
    char f_01c;
    char f_01d;
    char f_01e;
    char f_01f;
    char f_020;
    int f_021;
    char pad_023[0x9];
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

/* near-match 88%: 13:a01c (only the tail merge differs: the game keeps the
 * shared `push i; jmp call` in the 0x35 branch, CL in the 0x36 one) */
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

/* near-match 38%: 13:8e98 (the game stores done = 1 right after f_050 = 5
 * and reloads the record index after each call; CL sinks the store and
 * keeps the index in si) */
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
                g_7092[i].f_092 = g_1e50 + 200;
                g_7092[i].f_096 = g_1e50 + 20000;
                g_7092[a].f_09a = g_1e50 + 15000;
                g_7092[i].f_052 = g_7092[a].f_03c;
                g_7092[i].f_054 = g_7092[a].f_03e;
                g_7092[i].f_0eb = 1;
                fn_03_06ec(i, 14, a, 2);
                g_7092[i].f_056 = a;
                fn_13_2714(g_7092[a].f_03e, a, 15, 0x32, 1, -1);
                break;
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
