/* INSPACE.EXE segment 3 (selector 1010). */
#include "inspace.h"

/* 0x34-byte records; base taken as DS:3d5a [inferred]. */
typedef struct {
    int  w00;                   /* +0x00 */
    char pad02[0x10];
    int  w12;                   /* +0x12 */
    char pad14[0x12];
    int  w26;                   /* +0x26 */
    char pad28[0x0c];
} REC34;
extern REC34 g_3d5a[];

/* 0x15a-byte records at DS:7090 [inferred]. */
typedef struct {
    char p000[6];
    int f06;                    /* +06 */
    int f08;                    /* +08 */
    char p00a[0x32 - 0x0a];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    char p03a[0x3e - 0x3a];
    int f3e;                    /* +3e */
    int f40;                    /* +40 */
    char p042[0x4e - 0x42];
    int f4e;                    /* +4e */
    char p050[0x52 - 0x50];
    int f52;                    /* +52 */
    int f54;                    /* +54 */
    int f56;                    /* +56 */
    char p058[0x5d - 0x58];
    char f5d;                   /* +5d */
    char p05e[0x98 - 0x5e];
    DWORD f98;                  /* +98 */
    char p09c[0x147 - 0x9c];
    char f147;                  /* +147 */
    char f148;                  /* +148 */
    char f149;                  /* +149 */
    char p14a[0x15a - 0x14a];
} REC_15A;
extern REC_15A g_7090[];

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. */
typedef struct {
    char p00[4];
    POINT f04;                  /* +04: position [inferred] */
    char p08[0x18 - 8];
    int f18;                    /* +18 */
    char p1a[0x26 - 0x1a];
    int f26;                    /* +26 */
    char p28[0x44 - 0x28];
    int f44;                    /* +44 */
    char p46[0x53 - 0x46];
    char f53;                   /* +53 */
    char p54[0x70 - 0x54];
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
    char p22[0x2c - 0x22];
    char f2c;                   /* +2c: flags [inferred] */
    char p2d[0x58 - 0x2d];
    char f58[0xad - 0x58];      /* +58: name [inferred] */
} REC_AD;
#pragma pack()
extern REC_AD g_96ea[];
extern int g_940a;
extern int g_9316;
extern int g_6e70;
extern int g_6e72;
int far fn_13_2688(int a, int b);
extern int g_6e52;
extern int g_6e54;
extern int g_9406[];
extern int g_9422;
int far pascal fn_08_285a(int far *p, int far *q, POINT a, POINT b);
extern char g_8d38[];               /* run-time buffer (BSS) */
extern int g_9498;
void far describe_defender_order_message(int n, int k, int mode);

extern char g_8694[];               /* run-time buffer (BSS) */
extern char g_86d0[];               /* run-time buffer (BSS) */
extern char g_8768[];               /* run-time buffer (BSS) */
extern char g_87b8[];               /* run-time buffer (BSS) */
extern char g_8db0[];               /* run-time buffer (BSS) */

extern char g_960a[];               /* run-time buffer (BSS) */
extern char g_9628[];               /* run-time buffer (BSS) */
extern char g_8718[];               /* run-time buffer (BSS) */
extern char g_57b4[][35];
extern int g_6038[];
extern int g_92e8;
extern HWND g_0a7c;
void far fn_13_218a(int i, LPSTR buf);
void far fn_17_8e60(int i, LPSTR buf);
void far fn_06_0f1a(int v, LPSTR buf);
void far fn_07_65aa(int type, int n);
int far fn_03_0000(int type, int n);
void far fn_03_00f4(int n, int type, int k);
void far fn_03_1542(int a, int type, int n, LPSTR buf, int mode);
int far fn_03_1ae6(LPSTR s);
extern int g_967a;
extern int g_9214;
typedef struct {                /* 0x1c-byte records at DS:66e4 */
    int f00;
    char p02[0x1c - 2];
} REC_1C;
extern REC_1C g_66e4[];
typedef struct {                /* 0x14-byte records at DS:4da2 */
    int f00;
    char p02[0x14 - 2];
} REC_14;
extern REC_14 g_4da2[];
typedef struct {                /* 0x50-byte records at DS:2f4c */
    char p00[8];
    int f08;                    /* +08 */
    char p0a[0x50 - 0x0a];
} REC_50;
extern REC_50 g_2f4c[];

/* Not yet decompiled: stubs so calls to them compile as near calls. */
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

/* Sets the target (type, k) of object n; for the player's object also
 * builds the target description lines [inferred]. */
/* @addr 3:00f4 */
void far fn_03_00f4(int n, int type, int k)
{
    char tmp[30];
    char buf[40];
    char unused[18];

    g_7090[n].f3e = type;
    g_7090[n].f40 = k;
    if (n != g_9646)
        return;
    g_6e54 = type;
    g_6e52 = k;
    if (!fn_03_0000(type, k) && !fn_13_371c(type, k)) {
        g_9498++;
        return;
    }
    lstrcpy(g_960a, "");
    lstrcpy(g_9628, "");
    if (type == -1) {
        LoadString(g_9212, 0x89d, g_9628, 40);
        LoadString(g_9212, 0x89e, g_8718, 40);
        if (g_0a7c)
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        return;
    }
    lstrcpy(g_960a, "");
    lstrcpy(g_9628, "");
    if (type == 14) {
        fn_03_1542(0, type, k, buf, 0);
        if (g_92e8)
            LoadString(g_9212, 0x89f, g_960a, 40);
        else if (g_96ea[g_7090[g_9646].f4e].f20
                 == g_96ea[g_7090[k].f4e].f20)
            LoadString(g_9212, 0x142, g_960a, 40);
        else
            fn_13_218a(g_96ea[g_7090[k].f4e].f20, g_960a);
        fn_17_8e60(k, g_9628);
    } else if (type == 0) {
        lstrcpy(g_9628, g_57b4[k]);
        fn_03_1542(0, type, k, buf, 0);
        if (g_1df8[0][k].f53 == 2) {
            LoadString(g_9212, 0x8a0, tmp, 40);
            lstrcat(buf, tmp);
        } else if (g_1df8[0][k].f53 == 0) {
            LoadString(g_9212, 0x8a1, tmp, 40);
            lstrcat(buf, tmp);
        }
    } else if (type == 1) {
        lstrcpy(g_9628, g_57b4[g_6038[k]]);
        fn_03_1542(0, type, k, buf, 0);
    } else if (type == 2) {
        fn_03_1542(0, type, k, buf, 0);
        LoadString(g_9212, 0x8a2, tmp, 40);
        lstrcat(buf, tmp);
        if (g_52fe[k].f06 == 0) {
            LoadString(g_9212, 0x98, g_960a, 40);
            g_960a[lstrlen(g_960a) - 2] = 0;
            fn_06_0f1a(g_52fe[k].f08, tmp);
            lstrcat(g_960a, tmp);
        } else
            lstrcpy(g_960a, g_96ea[g_7090[g_52fe[k].f08].f4e].f58);
    } else if (type == 7) {
        fn_03_1542(0, type, k, buf, 0);
        LoadString(g_9212, 0x8a3, buf, 40);
        LoadString(g_9212, 0x8a4, g_960a, 40);
    } else if (type == 9 || type == 11
               || type == 8 && g_3d5a[k].w12 == 2 && g_3d5a[k].w00 > 0
               || fn_13_371c(type, k))
        fn_03_1542(0, type, k, buf, 0);
    lstrcpy(g_8718, buf);
    if (g_0a7c)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    fn_07_65aa(type, k);
}

/* @addr 3:062e */
void far fn_03_062e(int a, int b, int c, int d)
{
    if (a) {
        g_6e90 = c;
        g_6e8e = d;
    } else
        fn_03_00f4(b, c, d);
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

/* Writes the name of object (type, n) into buf, with an article chosen
 * by mode; a != 0 adds the pilot name and upper-cases it [inferred]. */
/* @addr 3:1542 */
void far fn_03_1542(int a, int type, int n, LPSTR buf, int mode)
{
    char num[40];
    char art[10];
    int i;
    int g;
    int an;
    int off;

    g = -1;
    off = an = 0;
    if (mode == 7) {
        off = 10000;
        mode = 5;
        g = 4;
    }
    if (mode == 5 && g_967a != 0)
        mode = 1;
    if (type == 14) {
        lstrcpy(buf, g_96ea[g_7090[n].f4e].f58);
        if (mode == 5)
            mode = 1;
        if (g_96ea[g_7090[n].f4e].f2c & 0x20)
            g = 0;
        else
            g = 2;
    } else if (type == 0) {
        if (mode == 2)
            mode = 5;
        LoadString(g_9212, 0x98, buf, 40);
        if (buf[lstrlen(buf) - 1] == 'M')
            g = 0;
        else if (buf[lstrlen(buf) - 1] == 'F')
            g = 2;
        else if (buf[lstrlen(buf) - 1] == 'N')
            g = 6;
        buf[lstrlen(buf) - 2] = 0;
        fn_06_0f1a(n, num);
        lstrcat(buf, num);
        if (a) {
            lstrcat(buf, " (");
            lstrcat(buf, g_57b4[n]);
            lstrcat(buf, ")");
        }
    } else if (type == 1)
        LoadString(g_9212, 0x37c, buf, 40);
    else if (type == 7)
        LoadString(g_9212, 0x15b, buf, 40);
    else if (type == 2) {
        if (mode == 1 || mode == 5)
            mode = 2;
        LoadString(g_9212, 0x9a, buf, 40);
    } else if (type == 9) {
        LoadString(g_9212, off + 0xaa, buf, 40);
        if (off == 0) {
            g = fn_03_1ae6(buf);
            if (mode == 1 || mode == 5)
                mode = 2;
        }
    } else if (fn_13_371c(type, n)) {
        LoadString(g_9212, 0x249, buf, 40);
        if (mode == 5)
            mode = 1;
    } else if (type == 3) {
        LoadString(g_9212, off + 0x99, buf, 40);
        if (off == 0) {
            g = fn_03_1ae6(buf);
            if (mode == 1 || mode == 5)
                mode = 2;
        }
    } else if (type == 4) {
        switch (g_9214) {
        case 0:
            LoadString(g_9212, 0x9b, buf, 40);
            break;
        case 1:
            LoadString(g_9212, 0xeb, buf, 40);
            break;
        case 2:
            LoadString(g_9212, 0xec, buf, 40);
            break;
        case 3:
            if (g_1df8[type][n].f26 == 0)
                LoadString(g_9212, 0xed, buf, 40);
            else
                LoadString(g_9212, 0xee, buf, 40);
            break;
        case 4:
            if (g_1df8[type][n].f26 == 0)
                LoadString(g_9212, 0xf1, buf, 40);
            else
                LoadString(g_9212, 0xf2, buf, 40);
            break;
        }
        g = fn_03_1ae6(buf);
    } else if (type == 8 && g_3d5a[n].w12 == 2) {
        LoadString(g_9212, g_4da2[g_3d5a[n].w26].f00 + off, buf, 40);
        if (off == 0) {
            if (mode == 1 || mode == 5)
                mode = 2;
        }
    } else if (type == 8) {
        if (off == 0) {
            if (mode == 1 || mode == 5)
                mode = 2;
        }
        if (g_3d5a[n].w12 == 3)
            LoadString(g_9212, off + 0x16a, buf, 40);
        else if (g_3d5a[n].w12 == 1)
            LoadString(g_9212, off + 0x16b, buf, 40);
    } else if (type == 5) {
        if (mode == 1 || mode == 5)
            mode = 2;
        if (g_1df8[type][n].f44 == 0x78)
            LoadString(g_9212, 0x1ec, buf, 40);
        else if (g_1df8[type][n].f44 == 0xc8)
            LoadString(g_9212, 0x1ed, buf, 40);
    } else if (type == 6 && g_66e4[n].f00 > 0
               && g_2f4c[g_66e4[n].f00].f08 != -1) {
        LoadString(g_9212, g_2f4c[g_66e4[n].f00].f08 + 10000, buf, 40);
        if (mode == 1 || mode == 5)
            mode = 2;
    } else if (type == 11)
        LoadString(g_9212, 0x39e, buf, 40);
    else {
        LoadString(g_9212, 0xa9, buf, 40);
        fn_06_0f1a(type, num);
        lstrcat(buf, num);
    }
    switch (buf[0]) {
    case 'A': case 'E': case 'I': case 'O': case 'U':
    case 'a': case 'e': case 'i': case 'o': case 'u':
        an = 1;
    }
    if (g == -1)
        g = fn_03_1ae6(buf);
    if (mode == 1)
        LoadString(g_9212, an + g + 0xa8c, art, 40);
    else if (mode == 2)
        LoadString(g_9212, an + g + 0xaa0, art, 40);
    else if (mode == 6)
        LoadString(g_9212, an + g + 0xac8, art, 40);
    else if (mode == 3)
        LoadString(g_9212, an + g + 0xab4, art, 40);
    else
        art[0] = 0;
    if (a) {
        if (buf[lstrlen(buf) - 1] == ' ')
            buf[lstrlen(buf) - 1] = 0;
        for (i = 0; i < lstrlen(buf); i++)
            if (buf[i] < 0x7b && buf[i] > 0x60)
                buf[i] -= 0x20;
    }
    if (mode && art[0]) {
        for (i = lstrlen(buf); i >= 0; i--)
            buf[i + lstrlen(art)] = buf[i];
        for (i = 0; i < lstrlen(art); i++)
            buf[i] = art[i];
    }
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

/* Select the next target for the player [inferred]: the nearest one after
 * the current, else the next one in list order, else the first. */
/* @addr 3:045a */
void far fn_03_045a(int mode)
{
    int type;
    int n;
    int start;
    int oa;
    int ob;
    int d;
    int best;
    int btype;
    int bn;
    int ctype;
    int cn;
    int flag;

    flag = 0;
    if (mode == 6) {
        cn = g_6e8e;
        ctype = g_6e90;
        if (ctype == 0xe)
            mode = 1;
        else
            mode = 5;
        flag = 1;
    } else {
        ctype = g_6e54;
        cn = g_6e52;
    }
    if (!fn_03_065e(ctype, cn, mode)) {
        best = 20000;
        for (type = 0; type <= 0xe; type++) {
            for (n = 0; n < g_9406[type]; n++) {
                if (ctype == type && cn >= n)
                    continue;
                if (!fn_03_065e(type, n, mode))
                    continue;
                d = fn_08_285a(&oa, &ob, g_1df8[0xe][g_9646].f04,
                               g_1df8[type][n].f04);
                if (d < best) {
                    best = d;
                    btype = type;
                    bn = n;
                }
            }
        }
        if (best < 20000) {
            fn_03_062e(flag, g_9646, btype, bn);
            return;
        }
    }
    if (mode == 1)
        start = 0xe;
    else
        start = ctype;
    if (ctype <= 0xe || cn < g_9422) {
        for (type = start; type <= 0xe; type++) {
            for (n = 0; n < g_9406[type]; n++) {
                if (ctype == type && cn >= n)
                    continue;
                if (fn_03_065e(type, n, mode))
                    goto found;
            }
        }
    }
    if (mode != 1)
        start = 0;
    for (type = start; type <= 0xe; type++) {
        for (n = 0; n < g_9406[type]; n++) {
            if (fn_03_065e(type, n, mode)) {
            found:
                fn_03_062e(flag, g_9646, type, n);
                return;
            }
        }
    }
    fn_03_062e(flag, g_9646, 0xc, 1);
}
