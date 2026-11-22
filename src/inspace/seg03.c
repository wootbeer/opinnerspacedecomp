/* INSPACE.EXE segment 3 (selector 1010). */
#include "inspace.h"

/* 0x34-byte records; base taken as DS:3d5a [inferred]. */
typedef struct {
    int  w00;                   /* +0x00 */
    char pad02[0x10];
    int  w12;                   /* +0x12 */
    char pad14[0x20];
} REC34;
extern REC34 g_3d5a[];

/* 0x15a-byte records at DS:7090 [inferred]. */
typedef struct {
    char p000[0x3e];
    int f3e;                    /* +3e */
    int f40;                    /* +40 */
    char p042[0x4e - 0x42];
    int f4e;                    /* +4e */
    char p050[0x54 - 0x50];
    int f54;                    /* +54 */
    int f56;                    /* +56 */
    char p058[0x5d - 0x58];
    char f5d;                   /* +5d */
    char p05e[0x147 - 0x5e];
    char f147;                  /* +147 */
    char p148[0x15a - 0x148];
} REC_15A;
extern REC_15A g_7090[];

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. */
typedef struct {
    char p00[0x18];
    int f18;                    /* +18 */
    char p1a[0x70 - 0x1a];
} REC_70;
extern REC_70 far *g_1df8[16];

/* 0x24-byte records at DS:52fe [inferred]. */
typedef struct {
    int f00;                    /* +00 */
    char p02[4];
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    int f0a;                    /* +0a */
    int f0c;                    /* +0c */
    char p0e[0x24 - 0xe];
} REC_24;
extern REC_24 g_52fe[];

extern int g_058c;
extern int g_92ec[];
extern int g_9324;
extern long g_05c0;
extern unsigned long g_1e50;
extern char g_380c[];               /* run-time buffer (BSS) */
extern int g_6e8e;
extern int g_6e90;
extern char g_8630[];               /* run-time buffer (BSS) */
extern int g_9646;

void far fn_10_a332(LPSTR buf, int id, int n, ...);
int far fn_13_371c(int type, int n);
void far fn_11_3fd4(LPSTR s, int mode);
void far fn_03_3498(LPSTR s, LPSTR a, LPSTR b);

/* 0xad-byte records; lowest field seen at DS:96ea [inferred]. */
#pragma pack(1)
typedef struct {
    char p00[0x20];
    int f20;                    /* +20 */
    char p22[0xad - 0x22];
} REC_AD;
#pragma pack()
extern REC_AD g_96ea[];
extern int g_940a;
extern int g_9316;
extern int g_6e70;
extern int g_6e72;
int far fn_13_2688(int a, int b);
extern char g_8d38[];               /* run-time buffer (BSS) */
extern int g_9498;
void far describe_defender_order_message(int n, int k, int mode);

extern char g_8694[];               /* run-time buffer (BSS) */
extern char g_86d0[];               /* run-time buffer (BSS) */
extern char g_8768[];               /* run-time buffer (BSS) */
extern char g_87b8[];               /* run-time buffer (BSS) */
extern char g_8db0[];               /* run-time buffer (BSS) */

/* Not yet decompiled: stubs so calls to them compile as near calls. */
void far fn_03_00f4(int a, long b) { }
void far fn_03_1542(int a, int b, int n, LPSTR buf, int c) { }
void far fn_03_06ec(int n, int kind, int target, int d) { }
void far fn_03_1d0a(int n, int target, int c) { }

/* @addr 3:0000 */
int far fn_03_0000(int type, int n)
{
    int unused;

    if (type < 0 || n < 0 || type > g_9324)
        return 0;
    if (g_92ec[type] <= n)
        return 0;
    if (type == 0xe && n != g_9646
        && (g_1df8[type][n].f18 == 0 || g_7090[n].f147 != 0))
        return 1;
    if (g_1df8[type][n].f18 != 0)
        return 0;
    if (type == 0 || type == 7 || type == 1)
        return 1;
    if (type == 2 && (g_52fe[n].f00 == 0xf
                      || g_52fe[n].f06 == 0xe && g_52fe[n].f08 == g_9646))
        return 1;
    if (type == 9 || type == 0xb)
        return 1;
    if (type == 8 && g_3d5a[n].w12 == 2 && g_3d5a[n].w00 > 0)
        return 1;
    if (fn_13_371c(type, n) != 2)
        return 0;
    return 1;
}

/* @addr 3:062e */
void far fn_03_062e(int a, int b, int c, int d)
{
    if (a) {
        g_6e90 = c;
        g_6e8e = d;
    } else
        fn_03_00f4(b, MAKELONG(c, d));
}

/* @addr 3:065e */
int far fn_03_065e(int a, int b, int c)
{
    if (!fn_03_0000(a, b))
        return 0;
    if (a == 0xe && b == g_9646)
        return 0;
    switch (c) {
    case 1:
        if (a != 0xe)
            return 0;
        goto yes;
    case 4:
        if (a != 2)
            return 0;
        goto yes;
    case 5:
        if (a != 9)
            return 0;
        goto yes;
    case 3:
        if (a == 8 && g_3d5a[b].w12 == 2 && g_3d5a[b].w00 > 0)
            return 1;
        return 0;
    case 0:
    yes:
        return 1;
    case 2:
        if (a == 0)
            goto yes;
        if (a != 0xb)
            return 0;
        goto yes;
    default:
        goto yes;
    }
    return 0;
}

/* @addr 3:1ae6 */
int far fn_03_1ae6(LPSTR s)
{
    int r;

    r = -1;
    if (s[lstrlen(s) - 1] == 'M')
        r = 0;
    else if (s[lstrlen(s) - 1] == 'F')
        r = 2;
    else if (s[lstrlen(s) - 1] == 'N')
        r = 6;
    else if (s[lstrlen(s) - 1] == 'P')
        r = 4;
    if (r != -1)
        s[lstrlen(s) - 2] = 0;
    else
        r = 6;
    return r;
}

/* @addr 3:31d0 */
void far fn_03_31d0(int mode, LPSTR a, LPSTR b)
{
    int i;

    if (b[0] == '.') {
        lstrcat(a, ".");
        for (i = 1; i < lstrlen(b); i++)
            b[i - 1] = b[i];
        b[lstrlen(b) - 1] = 0;
    }
    if (b[0] == 0 && a[lstrlen(a) - 1] != '.' && a[lstrlen(a) - 1] != '!')
        lstrcat(a, ".");
    switch (mode) {
    case 2:
        lstrcpy(g_8db0, a);
        lstrcat(g_8db0, " ");
        lstrcat(g_8db0, b);
        fn_03_3498(g_8db0, g_8768, g_87b8);
        break;
    case 3:
        fn_11_3fd4(a, 1);
        fn_11_3fd4(b, 1);
        lstrcpy(g_8694, a);
        lstrcpy(g_86d0, b);
        break;
    case 0:
    case 1:
        lstrcpy(g_8630, a);
        if (mode == 1) {
            lstrcat(g_8630, " ");
            lstrcat(g_8630, b);
        }
        break;
    }
}

/* @addr 3:332e */
void far pascal fn_03_332e(int a, int b)
{
    char buf[40];

    lstrcpy(g_8630, g_380c);
    lstrcat(g_8630, ": ");
    LoadString(g_9212, a, buf, 40);
    lstrcat(g_8630, buf);
    LoadString(g_9212, b, buf, 40);
    lstrcat(g_8630, buf);
    g_058c = 1;
    g_05c0 = g_1e50 + 1200;
}

/* @addr 3:3498 */
void far fn_03_3498(LPSTR s, LPSTR a, LPSTR b)
{
    int half;
    int i;

    s[0x4e] = 0;
    half = lstrlen(s) / 2;
    for (i = 0; i < half; i++) {
        if (s[half + i] == ' ') {
            half += i + 1;
            break;
        }
        if (s[half - i] == ' ') {
            half += 1 - i;
            break;
        }
    }
    lstrcpy(a, s);
    if (i < half) {
        a[half] = 0;
        lstrcpy(b, s + half);
    } else
        b[0] = 0;
}

/* @addr 3:33b4 */
void far fn_03_33b4(int id)
{
    char buf[40];

    switch (id) {
    case 2:
        if (g_7090[g_9646].f54 == 9)
            LoadString(g_9212, 0x578, buf, 40);
        else
            fn_03_1542(0, g_7090[g_9646].f54, g_7090[g_9646].f56, buf, 0);
        g_05c0 = g_1e50 + 1200;
        fn_10_a332(g_8630, 0x57c, g_058c = 1, (LPSTR)buf);
        break;
    case 1:
        fn_10_a332(g_8630, 0x57d, 1, (LPSTR)buf);
        g_058c = 1;
        g_05c0 = g_1e50 + 1200;
        break;
    case 3:
    case 9:
        fn_10_a332(g_8630, id, 1, g_7090[g_9646].f54, g_7090[g_9646].f56, 5);
        g_058c = 1;
        g_05c0 = g_1e50 + 1200;
        break;
    }
}

/* Pick a target for ship n's order [inferred]. */
/* @addr 3:1b8a */
void far fn_03_1b8a(int a, int n)
{
    int target;
    int t;
    int kind;
    int i;
    int j;
    int best;
    int bestscore;
    int score;

    target = t = -1;
    kind = g_7090[n].f3e;
    if (a && kind != 2) {
        for (i = 0; i < g_940a; i++) {
            if (g_52fe[i].f06 == 0xe && g_52fe[i].f08 == n
                && g_1df8[2][i].f18 == 0) {
                kind = 2;
                t = i;
                break;
            }
        }
    }
    if (t == -1 && (kind == 0xe || kind == 2))
        t = g_7090[n].f40;
    if (t > -1)
        target = t;
    if (target == -1) {
        best = -1;
        j = bestscore = 0;
        for (; j <= g_9316; j++) {
            if (j == n)
                continue;
            score = fn_13_2688(j, n) + 0x3c;
            score += g_7090[j].f5d * 0x32;
            if (g_96ea[g_7090[n].f4e].f20 == g_96ea[g_7090[j].f4e].f20)
                score += 300;
            if (g_6e72 == 0xe && j == g_6e70)
                score += 100;
            if (score > bestscore) {
                best = j;
                bestscore = score;
            }
        }
        if (best >= 0)
            target = best;
    }
    if (target == -1)
        fn_03_06ec(n, 7, 0, 100);
    else {
        if (kind == 0xe)
            fn_03_1d0a(n, target, 2);
        else
            describe_defender_order_message(n, target, 2);
        fn_03_06ec(n, kind, target, 0x3a);
    }
}

/* @addr 3:304c */
void far describe_defender_order_message(int n, int k, int mode)
{
    int t1;
    int n1;
    int unused;
    int n2;
    int t2;
    char name1[40];
    char name2[40];
    char line1[60];
    char line2[60];

    t1 = g_52fe[k].f0a;
    n1 = g_52fe[k].f0c;
    t2 = g_52fe[k].f06;
    n2 = g_52fe[k].f08;
    if (t1 != 0xe || n1 != n)
        fn_03_1542(0, t1, n1, name1, 5);
    else
        LoadString(g_9212, 0x1c8, name1, 40);
    if (t2 != 0xe || n2 != n)
        fn_03_1542(0, t2, n2, name2, 5);
    else
        LoadString(g_9212, 0x1c8, name2, 40);
    switch (g_52fe[k].f00) {
    case 0xf:
        if (fn_13_371c(t1, n1))
            fn_10_a332(g_8d38, 0xbdf, 1, (LPSTR)name2);
        else
            fn_10_a332(g_8d38, 0xbe0, 1, (LPSTR)name1, t1 == 2, 0x9eb, 0x8a9,
                       (LPSTR)name2);
        break;
    default:
        fn_10_a332(g_8d38, 0x8aa, 1, (LPSTR)name2);
        break;
    case 0xa:
        fn_10_a332(g_8d38, 0xbe1, 1, (LPSTR)name1, (LPSTR)name2);
        break;
    }
    fn_03_3498(g_8d38, line1, line2);
    if (lstrlen(line1) > 40 || lstrlen(line2) > 40)
        g_9498++;
    fn_03_31d0(mode, line1, line2);
}
