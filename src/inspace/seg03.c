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
    char p00a[0x18 - 0x0a];
    int f18;                    /* +18 */
    char p01a[0x1e - 0x1a];
    int f1e;                    /* +1e */
    char p020[0x26 - 0x20];
    int f26;                    /* +26 */
    int f28;                    /* +28 */
    int f2a;                    /* +2a */
    char p02c[0x32 - 0x2c];
    int f32;                    /* +32 */
    int f34;                    /* +34 */
    int f36;                    /* +36 */
    int f38;                    /* +38 */
    char p03a[0x3c - 0x3a];
    int f3c;                    /* +3c */
    int f3e;                    /* +3e */
    int f40;                    /* +40 */
    char p042[0x4e - 0x42];
    int f4e;                    /* +4e */
    char p050[0x52 - 0x50];
    int f52;                    /* +52 */
    int f54;                    /* +54 */
    int f56;                    /* +56 */
    int f58;                    /* +58 */
    char p05a[0x5d - 0x5a];
    char f5d;                   /* +5d */
    char f5e;                   /* +5e */
    char p05f[0x62 - 0x5f];
    int f62[(0x94 - 0x62) / 2]; /* +62: per object index [inferred] */
    DWORD f94;                  /* +94 */
    DWORD f98;                  /* +98 */
    char p09c[0xa4 - 0x9c];
    DWORD fa4;                  /* +a4 */
    char p0a8[0xb8 - 0xa8];
    char fb8[0xc2 - 0xb8];      /* +b8 */
    char fc2[0xec - 0xc2];      /* +c2 */
    char fec;                   /* +ec */
    char p0ed;
    char fee[0x13e - 0xee];     /* +ee */
    char f13e[0x146 - 0x13e];   /* +13e */
    char f146;                  /* +146 */
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
    char p28[0x2f - 0x28];
    char f2f;                   /* +2f */
    char p30[0x44 - 0x30];
    int f44;                    /* +44 */
    char p46[0x51 - 0x46];
    char f51;                   /* +51 */
    char p52;
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
    char p00[6];
    int f06;                    /* +06 */
    char p08[0x20 - 8];
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

extern DWORD g_870c;
extern int g_9608;
extern int g_1cb0;
extern int g_1cb2;
extern DWORD g_1cb4;
extern int g_094e;
extern int g_0a76;
extern int g_90ea;
extern int g_9602;
extern int g_9604;
extern int g_964e;
extern int g_9650;
extern int g_9652;
extern char g_8740[];               /* run-time buffer (BSS) */
void far fn_10_744c(int a);
void far fn_06_1010(int v, int div, int width, char far *buf);
void far fn_07_119c(int a, int b);  /* defined with one parameter */
void far fn_11_3e6e(void);
extern int g_952e;
extern int g_9e49;
extern long g_1e88;
extern char g_9eb4;
extern char g_9eb5;
extern int g_9320;
extern int g_9134;
extern int g_9460;
extern int g_95bc;                  /* flow_interactive */
extern long g_8e08[];
extern int g_9682;
extern int g_9680;
extern int g_856a;
extern int g_8562;
extern char g_93b6;
extern int g_91f8;
extern int g_8e00;
extern int g_8e04;
extern DWORD g_1e68;
extern char g_a163;
long far abs32(long x);
void far fn_11_4928(int mode, DWORD t, LPSTR out);
void far pascal fn_04_0078(int n);

/* Defined below; called near from fn_03_1b8a. */
void far fn_03_1d0a(int me, int o, int mode);

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

/* Builds the message lines for event kind about target (type, k) of the
 * player's object n [inferred]. */
/* @addr 3:06ec */
void far fn_03_06ec(int n, int type, int k, int kind)
{
    char buf[50];
    char pad[40];               /* unused locals: frame layout */
    int i;
    int u1, u2, u3;
    int t;
    int a;
    int u4;
    int b;
    int c;
    int tt;
    int tn;
    int s54;
    int s52;
    int u5, u6, u7, u8, u9;

    if (n != g_9646)
        return;
    if (type == 0xe && k == g_9646)
        return;
    if (kind == 0xb7 && (g_7090[k].f32 == 0xc || g_7090[k].f06 == 0xc))
        return;
    g_6e70 = k;
    g_6e72 = type;
    if (type == 0xe) {
        tt = g_7090[k].f54;
        tn = g_7090[k].f56;
    }
    s54 = g_6e54;
    s52 = g_6e52;
    if (g_0a76 != 3)
        fn_07_119c(3, 0);
    if (g_0a7c)
        fn_11_3e6e();
    if (type == -1) {
        LoadString(g_9212, 0x8a5, g_8740, 40);
        lstrcpy(g_8768, "");
        lstrcpy(g_87b8, "");
        g_870c = g_1e50 + 3000;
        g_9608 = 0;
        return;
    }
    if (type != 0xe && type != 7 && type != 2)
        return;
    fn_03_1542(0, type, k, g_8740, 0);
    t = k;
    if (g_094e) {
        if (type == 7)
            g_870c = g_1e50 + 2500;
        else
            g_870c = g_1e50 + 5000;
    } else
        g_870c = g_1e50 + 7000;
    g_9608 = 0;
    g_1cb2 = k;
    g_1cb0 = kind;
    switch (kind) {
    case 1:
        g_870c = g_1e50 + 9000;
        switch (g_7090[t].f52) {
        case 1:
            fn_10_744c(0x37);
            fn_10_a332(g_8db0, 0x125, 2);
            break;
        case 5:
            fn_10_744c(0x6d);
            fn_10_a332(g_8db0, 0x127, 2, tt, tn, 5, tt == 0xe && tn == g_9646);
            break;
        case 2:
        case 3:
            fn_10_744c(0x6c);
            if (g_7090[t].f54 == 9) {
                if (fn_13_2688(t, g_9646) > -50)
                    fn_10_a332(g_8db0, 0x57a, 2);
                else
                    fn_10_a332(g_8db0, 0x57b, 2);
            } else
                fn_10_a332(g_8db0, 0x128, 2, tt, tn, 5, tt == 0xe && tn == g_9646);
            break;
        case 4:
            fn_10_744c(0x6c);
            fn_10_a332(g_8db0, 0x129, 2, tt, tn, 5, tt == 0xe && tn == g_9646);
            break;
        case 7:
            fn_10_a332(g_8db0, 0x16f, 2);
            break;
        case 9:
            fn_10_a332(g_8db0, 0x185, 1, tt, tn, 5);
            break;
        case 12:
            fn_10_a332(g_8db0, 0x1bc, 2);
            break;
        case 13:
            if (g_7090[t].f56 == t) {
                fn_10_744c(0x44);
                fn_10_a332(g_8db0, 0x1c2, 2);
            } else
                fn_10_a332(g_8db0, 0x2a9, 2);
            break;
        case 10:
            fn_10_744c(0x36);
            fn_10_a332(g_8db0, 0x1aa, 2);
            break;
        }
        break;
    case 2:
    case 52:
        g_870c = 0;
        g_9608 = 1;
        if (kind == 2) {
            a = g_7090[n].f52;
            b = g_7090[n].f54;
            c = g_7090[n].f56;
        } else {
            a = g_964e;
            b = g_9650;
            c = g_9652;
        }
        switch (a) {
        case 2:
        case 3:
        case 4:
            if (b == 0xe && g_7090[c].f32 == 0xe && g_7090[c].f34 == t
                && g_7090[c].f38 == 1)
                fn_10_744c(0x34);
            else
                fn_10_744c(0x40);
            if (g_7090[n].f54 == 9)
                fn_10_a332(g_8db0, 0xbcb, 2);
            else
                fn_10_a332(g_8db0, 0x12e, 2, b, c, 5);
            break;
        case 5:
            fn_10_744c(0x34);
            fn_10_a332(g_8db0, 0x12f, 2, b, c, 5);
            break;
        case 1:
            fn_10_744c(0x34);
            fn_10_a332(g_8db0, 0xbcc, 2, (LPSTR)g_380c);
            break;
        case 9:
            fn_10_a332(g_8db0, 0x184, 2, b, c, 5);
            break;
        case 10:
            fn_10_a332(g_8db0, 0x1ac, 2);
            break;
        case 12:
            fn_10_a332(g_8db0, 0x1ba, 2);
            break;
        }
        break;
    case 19:
        switch (g_7090[t].f52) {
        case 1:
            fn_10_744c(0x44);
            fn_10_a332(g_8db0, 0x156, 2);
            break;
        case 2:
        case 3:
        case 4:
            fn_10_744c(0x44);
            fn_10_a332(g_8db0, 0x158, 2, tt, tn, 5);
            break;
        case 5:
            fn_10_744c(0x44);
            fn_10_a332(g_8db0, 0x159, 2, tt, tn, 0);
            break;
        case 6:
            fn_10_744c(0x6b);
            fn_10_a332(g_8db0, 0x159, 2, tt, tn, 5);
            break;
        case 9:
            fn_10_a332(g_8db0, 0x183, 2, tt, tn, 5);
            break;
        case 10:
            fn_10_a332(g_8db0, 0x1a8, 2);
            break;
        case 12:
            fn_10_a332(g_8db0, 0x1be, 2);
            break;
        }
        break;
    case 3:
        switch (g_7090[n].f52) {
        case 1:
            fn_10_744c(0x3b);
            fn_10_a332(g_8db0, 0x12c, 2, (LPSTR)g_380c);
            break;
        case 2:
        case 3:
        case 4:
            fn_10_744c(0x3b);
            fn_10_a332(g_8db0, 0x186, 2, (LPSTR)g_380c);
            break;
        case 9:
            fn_10_744c(0x66);
            fn_10_a332(g_8db0, 0x198, 2, tt, tn, 5);
            break;
        }
        break;
    case 4:
        fn_10_a332(g_8db0, 0x148, 2, s54, s52, 5);
        break;
    case 100:
        fn_10_a332(g_8db0, 0x148, 2, (LPSTR)g_380c);
        break;
    case 24:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x173, 2);
        break;
    case 5:
        fn_10_a332(g_8db0, 0x14b, 2, s54, s52, 5);
        break;
    case 6:
        fn_10_a332(g_8db0, 0x149, 2);
        break;
    case 14:
        fn_10_a332(g_8db0, 0x14c, 2, (LPSTR)g_380c);
        break;
    case 15:
        fn_10_a332(g_8db0, 0x14e, 2, 0x14e);
        break;
    case 20:
        fn_10_a332(g_8db0, 0x14e, 2, s54, s52, 2);
        break;
    case 16:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x154, 2);
        break;
    case 17:
        fn_10_a332(g_8db0, 0x150, 2, g_380c);   /* near pointer (sic) */
        break;
    case 18:
        fn_10_a332(g_8db0, 0x152, 2);
        break;
    case 22:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x164, 2);
        break;
    case 21:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x166, 2);
        break;
    case 23:
        fn_10_a332(g_8db0, 0x168, 2, g_7090[g_9646].f06, g_7090[g_9646].f08, 5);
        break;
    case 7:
        fn_10_744c(0x33);
        fn_10_a332(g_8db0, 0x6e, 2, (LPSTR)g_380c);
        break;
    case 132:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x470, 2);
        break;
    case 8:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x15c, 2);
        break;
    case 9:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x79, 2);
        break;
    case 13:
        if (g_1cb4 < g_1e50) {
            g_1cb4 = g_1e50 + 4000;
            fn_10_744c(0x67);
        }
        fn_10_a332(g_8db0, 0x15e, 2, (LPSTR)g_380c);
        break;
    case 10:
    case 11:
    case 12:
        fn_10_744c(0x6e);
        if (kind == 10)
            fn_10_744c(0x2d);
        else
            fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x86, 2, kind + 0x75, kind == 10, 0x207, 0x87,
                   g_90ea > 700);
        break;
    case 82:
    case 83:
        fn_10_a332(g_8db0, 0x205, 2, kind + 0x2e);
        break;
    case 84:
        fn_10_a332(g_8db0, 0x8a, 2, (LPSTR)g_380c);
        break;
    case 31:
        fn_10_a332(g_8db0, 0x181, 2);
        break;
    case 25:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x175, 2);
        break;
    case 26:
        fn_10_a332(g_8db0, 0x177, 2);
        break;
    case 30:
        fn_10_a332(g_8db0, 0x17d, 2, 0xe, g_9646, 0);
        break;
    case 29:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x17b, 2);
        break;
    case 27:
        fn_10_a332(g_8db0, 0x17f, 2);
        break;
    case 28:
        fn_10_a332(g_8db0, 0x179, 2);
        break;
    case 32:
        fn_10_a332(g_8db0, 0x188, 2, tt, tn, 5);
        break;
    case 33:
        fn_10_a332(g_8db0, 0x18a, 2, tt, tn, 5);
        break;
    case 34:
        fn_10_a332(g_8db0, 0x18c, 2, tt, tn, 5);
        break;
    case 85:
        if (g_9602 == 0) {
            fn_06_1010(g_9604, 100, 2, buf);
            fn_10_a332(g_8db0, 0x23e, 2, (LPSTR)buf);
        } else
            fn_10_a332(g_8db0, 0x23f, 2, g_9602, 0x9e2);
        break;
    case 86:
        fn_06_1010(g_9604, 100, 2, buf);
        fn_10_a332(g_8db0, 0x2a8, 2, (LPSTR)buf);
        break;
    case 181:
        fn_10_a332(g_8db0, 0x798, 2);
        break;
    case 35:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x18e, 2, s54, s52, 5);
        break;
    case 36:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x190, 2, s54, s52, 2);
        break;
    case 37:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x191, 2, s54, s52, 2);
        break;
    case 113:
        fn_10_a332(g_8db0, 0x429, 2);
        break;
    case 38:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x194, 2);
        break;
    case 39:
        fn_10_a332(g_8db0, 0x196, 2);
        break;
    case 48:
        fn_10_a332(g_8db0, 0x199, 2);
        break;
    case 41:
    case 42:
    case 43:
        fn_10_a332(g_8db0, kind + 0x172, 2);
        break;
    case 45:
        fn_10_a332(g_8db0, kind + 0x171, 2);
        break;
    case 51:
        fn_10_a332(g_8db0, 0x1b2, 2, s54, s52, 5);
        break;
    case 50:
        fn_10_a332(g_8db0, 0x1ae, 2);
        break;
    case 49:
        fn_10_a332(g_8db0, 0x1b0, 2);
        break;
    case 71:
        fn_10_a332(g_8db0, 0x28a, 2);
        break;
    case 55:
        fn_10_a332(g_8db0, 0x1b8, 2);
        break;
    case 54:
        fn_10_a332(g_8db0, 0x1b4, 2);
        break;
    case 53:
        fn_10_a332(g_8db0, 0x1b6, 2);
        break;
    case 56:
        fn_10_a332(g_8db0, 0x1c0, 2);
        break;
    case 57:
        fn_10_a332(g_8db0, 0x1c4, 2);
        break;
    case 64:
        fn_10_a332(g_8db0, 0x22b, 2);
        break;
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 65:
    case 66:
    case 67:
    case 68:
    case 87:
    case 88:
        switch (rand() % 4) {
        case 0:
            fn_10_744c(0x3d);
            break;
        case 1:
            fn_10_744c(0x3e);
            break;
        case 2:
            fn_10_744c(0x3f);
            break;
        }
        fn_10_a332(g_8db0, kind + 0x1eb, 2);
        break;
    case 92:
        fn_10_a332(g_8db0, 0x3b6, 2);
        break;
    case 69:
        fn_10_a332(g_8db0, 0x23a, 2);
        break;
    case 192:
        fn_10_a332(g_8db0, 0x3c4, 2);
        break;
    case 70:
        fn_10_a332(g_8db0, 0x23c, 2);
        break;
    case 93:
        fn_10_a332(g_8db0, 0x3c0, 2);
        break;
    case 101:
        fn_10_a332(g_8db0, 0x3c1, 2);
        break;
    case 134:
        fn_10_a332(g_8db0, 0x3c2, 2);
        break;
    case 185:
        fn_10_a332(g_8db0, 0x3c3, 2);
        break;
    case 135:
        fn_10_a332(g_8db0, 0x58f, 2);
        break;
    case 72:
        fn_10_744c(0x67);
        fn_10_a332(g_8db0, 0x28c, 2);
        break;
    case 73:
        fn_10_a332(g_8db0, 0x28e, 2, g_7090[k].f32, g_7090[k].f34, 0);
        break;
    case 74:
        fn_10_a332(g_8db0, 0x28f, 2);
        break;
    case 75:
        fn_10_a332(g_8db0, 0x291, 2);
        break;
    case 76:
        fn_10_a332(g_8db0, 0x293, 2);
        break;
    case 77:
        fn_10_a332(g_8db0, 0x295, 2);
        break;
    case 78:
        fn_10_a332(g_8db0, 0x297, 2);
        break;
    case 81:
        fn_10_744c(0x3b);
        fn_10_a332(g_8db0, 0x299, 2);
        break;
    case 79:
        fn_10_744c(0x3b);
        fn_03_3498(g_8d38, g_8768, g_87b8);
        break;
    case 80:
        fn_10_744c(0x3f);
        fn_03_3498(g_8d38, g_8768, g_87b8);
        break;
    case 89:
        fn_10_744c(0x36);
        fn_10_a332(g_8db0, 0x2ab, 2);
        break;
    case 90:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x2ad, 2);
        break;
    case 91:
        fn_10_a332(g_8db0, 0x2af, 2, 4, 0x2b0, (LPSTR)g_380c);
        break;
    case 112:
        fn_10_a332(g_8db0, 0x428, 2, 4, 0x2b0, (LPSTR)g_380c);
        break;
    case 94:
        fn_10_a332(g_8db0, 0x2b4, 2, 4, 0x2b0, (LPSTR)g_380c);
        break;
    case 99:
        fn_10_a332(g_8db0, 0x422, 2);
        break;
    case 95:
        fn_10_a332(g_8db0, 0x41a, 2);
        break;
    case 137:
        fn_10_a332(g_8db0, 0x591, 2);
        break;
    case 96:
        fn_10_a332(g_8db0, 0x41c, 2, 0xe, g_7090[k].f08, 5);
        break;
    case 97:
        fn_10_a332(g_8db0, 0x41e, 2, 0xe, g_7090[k].f08, 5);
        break;
    case 98:
        fn_10_a332(g_8db0, 0x41e, 2, g_7090[k].f06, g_7090[k].f08, 2);
        break;
    case 102:
        fn_10_a332(g_8db0, 0x2b5, 2, g_7090[k].f32, g_7090[k].f34, 5);
        break;
    case 103:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x2b7, 2);
        break;
    case 182:
        fn_10_a332(g_8db0, 0x25b, 2);
        break;
    case 104:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x2b9, 2);
        break;
    case 106:
        fn_10_744c(0x37);
        fn_10_a332(g_8db0, 0x2bf, 2);
        break;
    case 105:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x2bb, 2);
        break;
    case 108:
        fn_10_a332(g_8db0, 0x2c1, 2);
        break;
    case 107:
        fn_10_744c(0x30);
        fn_10_a332(g_8db0, 0x2bd, 2);
        break;
    case 110:
        fn_10_744c(0x30);
        fn_10_a332(g_8db0, 0x2c3, 2);
        break;
    case 109:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x2da, 2);
        break;
    case 111:
        fn_13_218a(g_96ea[g_7090[k].f4e].f20, buf);
        fn_10_a332(g_8db0, 0x426, 2, (LPSTR)buf);
        break;
    case 115:
        fn_10_744c(0x34);
        fn_10_a332(g_8db0, 0x579, 2);
        break;
    case 116:
        fn_10_a332(g_8db0, 0x580, 2);
        break;
    case 117:
        fn_10_744c(0x3b);
        fn_10_a332(g_8db0, 0x581, 2);
        break;
    case 118:
        fn_10_744c(0x3b);
        fn_10_a332(g_8db0, 0x582, 2);
        break;
    case 119:
        fn_10_744c(0x3b);
        if (g_7090[g_9646].f32 == 0xe)
            fn_10_a332(g_8db0, 0x583, 2);
        else
            fn_10_a332(g_8db0, 0x584, 2);
        break;
    case 127:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x588, 2);
        break;
    case 128:
        fn_10_a332(g_8db0, 0x589, 2);
        break;
    case 129:
        fn_10_a332(g_8db0, 0x58a, 2);
        break;
    case 130:
        fn_10_a332(g_8db0, 0x58b, 2);
        break;
    case 136:
        fn_10_a332(g_8db0, 0x590, 2);
        break;
    case 138:
        fn_10_744c(0x44);
        fn_10_a332(g_8db0, 0x592, 2);
        break;
    case 141:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x73c, 2,
                   (int)((g_7090[k].f98 - g_1e50) / 1000));
        break;
    case 139:
        fn_10_a332(g_8db0, 0x73a, 2, 4, 0, 0);
        break;
    case 140: case 142: case 143: case 144: case 145: case 146: case 147:
    case 148: case 149: case 150: case 151: case 152: case 153: case 154:
    case 155: case 156: case 157: case 158: case 159: case 160: case 161:
    case 162: case 163:
        fn_10_a332(g_8db0, kind + 0x6af, 2);
        break;
    case 164:
        fn_10_744c(0x30);
        fn_10_a332(g_8db0, 0x593, 2);
        break;
    case 165: case 166: case 167: case 168: case 169: case 170: case 171:
    case 172: case 173:
        fn_10_a332(g_8db0, kind + 0x6c7, 2);
        break;
    case 175: case 176: case 177: case 178:
        fn_10_a332(g_8db0, kind + 0x6d1, 2);
        break;
    case 179:
        fn_10_a332(g_8db0, 0x784, 2, 4, 0, 0);
        break;
    case 174:
        fn_10_a332(g_8db0, 0x794, 2);
        break;
    case 180:
        fn_10_a332(g_8db0, 0x796, 2);
        break;
    case 186:
        fn_10_a332(g_8db0, 0x78a, 2);
        break;
    case 187:
        fn_10_a332(g_8db0, 0x78c, 2);
        break;
    case 188:
        fn_10_a332(g_8db0, 0x79c, 2, 4, 0, 2);
        break;
    case 189:
        fn_10_a332(g_8db0, 0x7d0, 2, tt, tn, 5);
        break;
    case 190:
        fn_10_a332(g_8db0, 0x7d5, 2);
        break;
    case 191:
        fn_10_a332(g_8db0, 0x7d2, 2);
        break;
    case 183:
        fn_10_744c(0x36);
        fn_10_a332(g_8db0, 0x1aa, 2);
        break;
    case 184:
        fn_10_a332(g_8db0, 0x1aa, 2, (int)g_7090[k].f148,
                   (int)g_7090[k].f149, 5);
        break;
    }
    if (g_90ea > 0x27b) {
        for (i = 0; i < lstrlen(g_8768); i++)
            if (g_8768[i] < '{' && g_8768[i] > '`')
                g_8768[i] -= 0x20;
        for (i = 0; i < lstrlen(g_87b8); i++)
            if (g_87b8[i] < '{' && g_87b8[i] > '`')
                g_87b8[i] -= 0x20;
    }
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

/* Builds the two status lines about object o (its order and state) as seen
 * by object me and shows them with fn_03_31d0 [inferred]. */
/* @addr 3:1d0a */
void far fn_03_1d0a(int me, int o, int mode)
{
    int tt;
    int tn;
    int i;
    int unused;
    int id;
    char name[40];
    char pre[40];
    char s1[60];
    char line1[60];
    char line2[60];
    int sz;
    int mood;
    int cnt;                    /* also a found index and a loop counter */
    char tmp[40];               /* its first word also serves as a flag */

    tt = g_7090[o].f32;
    tn = g_7090[o].f34;
    if (tt != 0xe || tn != me || o == g_9646 && g_9134 && g_95bc)
        fn_03_1542(1, tt, tn, name, 5);
    else
        LoadString(g_9212, 0x1c8, name, 40);
    if (o != g_9646 || !g_95bc || g_9460)
        LoadString(g_9212, 0x43b, pre, 40);
    else
        LoadString(g_9212, 0x43a, pre, 40);
    if (tt == 3)
        fn_03_1542(1, tt, tn, name, 0);
    lstrcpy(line1, pre);
    id = -1;
    if (o == g_952e && g_9e49 >= 0 && g_9e49 < 9) {
        if (g_9e49 >= 6 || g_1e88 == 0 && g_1df8[7]->f18 != 0) {
            LoadString(g_9212, 0x46e, s1, 40);
            LoadString(g_9212, 0x46f, line2, 40);
        } else if (g_7090[o].f147) {
            LoadString(g_9212, 0x442, s1, 40);
            LoadString(g_9212, 0x443, line2, 40);
        } else if (g_7090[o].f26 + g_7090[o].f28 + g_7090[o].f2a < 100) {
            LoadString(g_9212, 0x1e8, s1, 40);
            if (me == 100)
                LoadString(g_9212, 0x460, line2, 40);
            else
                LoadString(g_9212, 0x1e9, line2, 40);
        } else {
            LoadString(g_9212, 0x46c, s1, 40);
            LoadString(g_9212, 0x46d, line2, 40);
        }
    } else if (g_9320 == 6 && g_96ea[g_7090[o].f4e].f20 != 7) {
        if (!g_9eb4)
            LoadString(g_9212, 0x43e, s1, 40);
        else if (g_9eb5)
            LoadString(g_9212, 0x440, s1, 40);
        else if (g_1df8[14][o].f51)
            LoadString(g_9212, 0x43f, s1, 40);
        else if (o == g_9646) {
            LoadString(g_9212, 0x441, s1, 40);
            fn_06_0f1a(g_7090[o].f148, line2);
            lstrcat(s1, line2);
        } else {
            LoadString(g_9212, 0x43b, s1, 40);
            if (g_8e08[o] == 1000000L)
                LoadString(g_9212, 0x437, s1, 40);
            else if (g_8e08[o] == -50000L)
                LoadString(g_9212, 0x438, s1, 40);
            else if (g_8e08[o] == 50000L)
                LoadString(g_9212, 0x439, s1, 40);
            else {
                if (g_8e08[o] < 0) {
                    fn_11_4928(1, abs32(g_8e08[o]), line1);
                    lstrcat(s1, line1);
                    LoadString(g_9212, 0x43c, line1, 40);
                } else {
                    LoadString(g_9212, 0x43d, line1, 40);
                    lstrcat(s1, line1);
                    fn_11_4928(1, abs32(g_8e08[o]), line1);
                }
                lstrcat(s1, line1);
            }
            lstrcpy(line1, "");
            lstrcpy(line2, "");
            pre[0] = 0;
        }
        if (pre[0])
            line2[0] = 0;
    } else {
        switch (g_7090[o].f38) {
        case 1:
            fn_10_a332(s1, 0x1c9, 1, (LPSTR)name);
            if (!g_95bc && g_7090[o].fa4 + 14000 < g_1e50
                && g_7090[o].fa4 + 19000 > g_1e50)
                id = 0x467;
            else if (!g_95bc && g_7090[o].fa4 + 19000 < g_1e50
                     && (g_7090[o].f52 == 0
                         || g_7090[o].f98 < g_1e50 && g_7090[o].f52 != 4
                            && g_7090[o].f52 != 1)) {
                id = 0x468;
                if (g_9320 == 7) {
                    for (i = 0; i <= g_9316; i++)
                        if (i != o && g_7090[o].f56 != i
                            && !g_1df8[14][i].f18) {
                            g_7090[o].f56 = i;
                            g_7090[o].fa4 = g_1e50;
                            break;
                        }
                    if (g_9316 - i + 1 == 0) {
                        g_7090[o].f94 = 0;
                        g_7090[o].f52 = -1;
                        if (o != g_9646 || !g_95bc)
                            fn_04_0078(o);
                    }
                } else {
                    if (g_7090[o].f32 == 0xe) {
                        g_7090[o].f62[g_7090[o].f34] /= 2;
                        g_7090[o].fc2[g_7090[o].f34] = -1;
                    }
                    g_7090[o].f94 = 0;
                    g_7090[o].f52 = -1;
                    if (o != g_9646 || !g_95bc)
                        fn_04_0078(o);
                }
            } else if (g_7090[o].f146 == 0xd) {
                if (tn == me)
                    id = 0x1f0;
                else
                    id = 0x1f1;
            } else if (g_7090[o].f52 >= 2 && g_7090[o].f52 <= 4
                       && (o != g_9646 || !g_95bc) || g_9320 == 7) {
                if (g_7090[o].f58 == o) {
                    if (mode == 3 && g_7090[o].f54 == 0xe
                        && g_7090[o].f56 == g_9646) {
                        sz = mood = cnt = 0;
                        for (i = 0; i <= g_9316; i++)
                            if (i != me && !g_1df8[14][i].f18
                                && g_7090[i].f54 == 0xe
                                && g_7090[i].f56 == me) {
                                sz += g_7090[i].f26;
                                mood += g_7090[i].f13e[me];
                                cnt++;
                                if (i == o) {
                                    sz += g_7090[i].f26;
                                    mood += g_7090[i].f13e[me];
                                    cnt++;
                                } else if (!g_7090[i].fec)
                                    sz = -100;
                            }
                        if (cnt == 0)
                            cnt = 1;
                        sz /= cnt;
                        mood /= cnt;
                        if (g_9682 < 3 && g_9680 < 3)
                            id = 0x6c7;
                        else if (sz < 0) {
                            if (g_7090[o].f5d < 2)
                                id = 0x6c8;
                            else
                                id = 0x6ca;
                        } else if (!g_7090[o].fec)
                            id = 0x6c9;
                        else if (!g_7090[me].fec) {
                            if (me == g_856a && g_8562 <= 0)
                                id = 0x6d1;
                            else if (g_7090[o].f5e == 3)
                                id = 0x6d0;
                            else if (g_96ea[g_7090[o].f4e].f20 == 3)
                                id = 0x6cf;
                            else if (g_7090[o].f26 > 0x41)
                                id = 0x6d2;
                            else if (!g_7090[o].f5e)
                                id = 0x6d3;
                            else if (g_7090[o].f5d < 2)
                                id = 0x6cc;
                            else if (g_93b6 != -1)
                                id = 0x6cd;
                            else if (g_91f8 & 1)
                                id = 0x6cb;
                            else
                                id = 0x6ce;
                        } else if (g_7090[me].f26 * 3 / 4 < sz) {
                            if (g_8e04 > g_8e00) {
                                if (mood > 2 && g_8e04 > 0x50) {
                                    if (g_7090[o].f5e < 2)
                                        id = 0x6ae;
                                    else
                                        id = 0x6af;
                                } else if (g_8e00 > 0x78 && mood < -2
                                           && g_1e68 > 900) {
                                    id = 0x6b0;
                                } else if (g_7090[o].f5e < 2)
                                    id = 0x6b1;
                                else
                                    id = 0x6b2;
                            } else if (g_8e00 * 3 / 5 < g_8e04) {
                                if (mood > 1) {
                                    if (g_7090[o].f5e < 2)
                                        id = 0x6b3;
                                    else
                                        id = 0x6b4;
                                } else if (mood < -2)
                                    id = 0x6b5;
                                else if (g_7090[o].f5e < 2)
                                    id = 0x6b7;
                                else
                                    id = 0x6b6;
                            } else if (g_7090[me].f26 < sz)
                                id = 0x6b8;
                            else if (mood > 2) {
                                if (g_7090[o].f5e < 2)
                                    id = 0x6b3;
                                else
                                    id = 0x6b4;
                            } else
                                id = 0x6b9;
                        } else if (g_8e00 * 3 / 4 < g_8e04
                                   && g_7090[me].f26 / 2 < sz) {
                            if (mood > 1) {
                                if (g_7090[o].f5e < 2)
                                    id = 0x6ba;
                                else
                                    id = 0x6b4;
                            } else if (mood < -2)
                                id = 0x6b5;
                            else if (g_7090[o].f5e < 2)
                                id = 0x6bb;
                            else
                                id = 0x6bc;
                        } else if (g_8e00 / 3 > g_8e04) {
                            if (g_7090[o].f5e < 2)
                                id = 0x6bd;
                            else if (mood < -2 && sz < 0x23) {
                                if (g_7090[o].f5e < 2)
                                    id = 0x6be;
                                else
                                    id = 0x6bf;
                            } else
                                id = 0x6c0;
                        } else if (mood > 1) {
                            if (g_7090[o].f5e < 2)
                                id = 0x6c2;
                            else
                                id = 0x6c3;
                        } else if (mood < -2 && sz < 0x1e) {
                            if (g_7090[o].f5e < 2)
                                id = 0x6c1;
                            else
                                id = 0x6bf;
                        } else
                            id = 0x6c4;
                    } else if (g_7090[o].f146 == 0x14) {
                        if (g_7090[o].f32 == 0xe && g_7090[o].f34 == me)
                            id = 0x6c5;
                        else
                            id = 0x6ab;
                    } else if (g_7090[o].f146 == 0x15) {
                        if (g_7090[o].f32 == 0xe && g_7090[o].f34 == me)
                            id = 0x6c6;
                        else
                            id = 0x6ac;
                    } else
                        id = 0x1ca;
                } else
                    fn_10_a332(line2, 0x1cb, 1, 0xe, g_7090[o].f58, name, 5); /* near name (sic) */
            } else if (g_7090[o].f52 == 1) {
                if (g_7090[o].f56 != me)
                    fn_03_1542(0, 0xe, g_7090[o].f56, name, 5);
                else
                    LoadString(g_9212, 0x1c8, name, 40);
                id = 0x28dc;
            } else if (g_7090[o].f146 == 1)
                id = 0x6a6;
            else if (g_7090[o].f146 == 2) {
                cnt = -1;
                for (i = 0; i <= g_9316; i++) {
                    if (g_1df8[14][i].f18)
                        continue;
                    if (i == o)
                        continue;
                    if (g_7090[i].f32 == g_7090[o].f32
                        && g_7090[i].f34 == g_7090[o].f34
                        && g_7090[i].f38 == 1) {
                        cnt = i;
                        break;
                    }
                }
                if (cnt == -1)
                    id = 0x6a7;
                else
                    fn_10_a332(line2, 0x435, 1, 0xe, i, 5, tt == 0xe,
                               tn == me, 0x1cf, 0x1c8, tt != 0xe);
            } else if (tt == 2)
                id = 0x1cd;
            else if (g_7090[o].f52 == 0x17)
                id = 0x1ef;
            else if (g_7090[o].f146 == 0xa)
                id = 0x6a8;
            else if (g_7090[o].f146 == 0xf)
                id = 0x6a9;
            else if (g_7090[o].f146 == 0x10)
                id = 0x6aa;
            else if (tt == 0xe) {
                if (g_7090[o].fee[tn] != 0 && g_7090[o].fee[tn] <= 5) {
                    switch (g_7090[o].fee[tn]) {
                    case 1:
                        id = 0x462;
                        break;
                    case 2:
                        id = 0x463;
                        break;
                    case 3:
                        id = 0x464;
                        break;
                    case 4:
                        id = 0x465;
                        break;
                    case 5:
                        id = 0x466;
                        break;
                    }
                } else
                    fn_10_a332(line2, 0x1ce, 1, tn == me, 0x1cf, 0x1c8);
            } else if (tt == 0) {
                if (g_1df8[0][tn].f53 == 2)
                    id = 0x456;
                else if (g_1df8[0][tn].f2f < 0
                         && g_7090[o].fb8[g_7090[o].f18] == 5)
                    id = 0x6ad;
                else {
                    LoadString(g_9212, 0x457, line2, 40);
                    lstrcpy(tmp, g_57b4[tn]);
                    for (cnt = 0; cnt < lstrlen(tmp); cnt++)
                        if (tmp[cnt] == '.') {
                            tmp[cnt] = 0;
                            break;
                        }
                    lstrcat(line2, tmp);
                    lstrcat(line2, "!");
                }
            } else if (tt == 8) {
                if (g_3d5a[tn].w12 == 2) {
                    if (g_3d5a[tn].w00 == -1)
                        id = 0x459;
                    if (g_3d5a[tn].w00 == -3)
                        id = 0x45a;
                    if (g_3d5a[tn].w00 == 0x10)
                        id = 0x45b;
                    else
                        id = 0x45d;
                } else if (g_96ea[g_7090[o].f4e].f20 == 6)
                    id = 0x1f6;
                else
                    id = 0x45c;
            } else if (tt == 9)
                id = 0x458;
            else if (g_96ea[g_7090[o].f4e].f20 == 6)
                id = 0x1f6;
            else
                id = 0x1f7;
            break;
        case 3:
            if (tt == 0xe && (g_9134 != 1 || !g_95bc || o != g_9646
                              || g_7090[o].f52 == 5)) {
                if (g_7090[o].f52 != 7) {
                    fn_10_a332(s1, 0x1d0, 1, (LPSTR)name);
                    if (tn == me && (!g_9134 || o != g_9646 || !g_95bc))
                        LoadString(g_9212, 0x1c8, name, 40);
                    else if (!g_9134 || o != g_9646 || !g_95bc)
                        LoadString(g_9212, 0x1cf, name, 40);
                    if (g_7090[o].f52 == 5) {
                        if (g_95bc && o == g_9646) {
                            if (!g_9134)
                                LoadString(g_9212, 0x127, s1, 40);
                            else
                                fn_10_a332(s1, 0x594, 1, (LPSTR)name);
                        } else if (g_7090[o].f58 == o)
                            id = 0x28e2;
                        else
                            id = 0x28e1;
                    } else if (g_7090[o].f52 == 0x14)
                        id = 0x1f2;
                    else if (g_7090[o].f52 == 0x16) {
                        if (g_7090[o].f56 == me)
                            LoadString(g_9212, 0x1fb, s1, 40);
                        else
                            fn_10_a332(s1, 0x1fc, 1, 0xe, g_7090[o].f56, 5);
                        id = g_a163 + 0x44a;
                    } else if (fn_13_2688(o, tn) > g_7090[o].f5d * 40 + 50)
                        id = 0x1f3;
                    else if (g_7090[o].fc2[tn] > 0)
                        id = 0x28e3;
                    else
                        id = 0x2904;
                } else {
                    LoadString(g_9212, 0x1d4, s1, 40);
                    id = 0x1d5;
                }
            } else if (g_7090[o].f52 == 7
                       || o == g_9646 && g_7090[o].f32 == 8
                          && g_7090[o].f34 == 0) {
                LoadString(g_9212, 0x1d6, s1, 40);
                if (tt == 0)
                    id = 0x28e7;
                else if (g_7090[o].f3c == 5)
                    id = 0x28e8;
                else if (g_7090[o].f26 < 0x32)
                    id = LoadString(g_9212, 0x1f5, line2, 40);  /* sic: length as id */
                else
                    id = 0x28e9;
            } else {
                fn_10_a332(s1, 0x1da, 1, (LPSTR)name);
                id = 0x1db;
            }
            break;
        case 2:
            if (fn_13_371c(tt, tn)) {
                if (g_7090[o].f52 == 0x16) {
                    if (g_7090[o].f56 == me)
                        LoadString(g_9212, 0x1fb, s1, 40);
                    else
                        fn_10_a332(s1, 0x1fc, 1, 0xe, g_7090[o].f56, 5);
                    id = g_a163 + 0x44a;
                } else {
                    LoadString(g_9212, 0x1dc, s1, 40);
                    *(int *)tmp = 0;    /* flag kept in tmp's slot (frame layout) */
                    for (i = 0; i <= g_9316; i++)
                        if (g_96ea[g_7090[i].f4e].f20 == 7
                            && g_7090[i].f5e == 1 && g_7090[i].f56 == o) {
                            *(int *)tmp = 1;
                            break;
                        }
                    if (*(int *)tmp)
                        id = 0x45e;
                    else if (me == 100) {
                        if (!g_95bc)
                            id = 0x45f;
                        else
                            id = 0x461;
                    } else
                        id = 0x1dd;
                }
            } else if (g_1df8[tt][tn].f53 || o == g_9646 && g_9134 < 2) {
                fn_03_1542(1, tt, tn, name, 2);
                fn_10_a332(s1, 0x1de, 1, (LPSTR)name);
                if (g_7090[o].f52 == 9 || g_7090[o].f52 == 0xc) {
                    if (g_7090[o].f58 == me)
                        id = 0x1df;
                    else
                        id = 0x1e0;
                } else if (g_7090[o].f52 == 0xe)
                    fn_10_a332(line2, 0x202, 1, 0xe, g_7090[o].f56, 5);
                else if (tt == 0xb) {
                    if (g_96ea[g_7090[o].f4e].f20 == 3)
                        id = 0x1fe;
                    else if (g_96ea[g_7090[o].f4e].f20 == 7)
                        id = 0x444;
                    else
                        id = 0x1ff;
                } else if (tt == 6 && g_96ea[g_7090[o].f4e].f20 == 7)
                    id = 0x200;
                else if (tt == 4 && g_7090[o].f1e < 300)
                    id = 0x46b;
                else if (tt == 0)
                    id = 0x1e1;
                else if (tt == 4
                         && g_96ea[g_7090[o].f4e].f06 - 15 > g_7090[o].f1e)
                    id = 0x46a;
                else if (tt == 4)
                    id = 0x469;
            } else {
                LoadString(g_9212, 0x6a4, s1, 40);
                id = 0x6a5;
            }
            break;
        case 4:
            if (tt == 0xe && tn == me) {
                LoadString(g_9212, 0x1e2, s1, 40);
                id = 0x1e3;
            } else {
                fn_10_a332(s1, 0x1e4, 1, tt, tn, 5);
                id = 0x1e5;
            }
            break;
        case 5:
            LoadString(g_9212, 0x1ea, s1, 40);
            id = 0x1eb;
            break;
        default:
            LoadString(g_9212, 0x1e6, s1, 40);
            id = 0x1e7;
            break;
        }
    }
    if (o == g_9646 && g_95bc && !g_9460)
        lstrcpy(line2, "");
    else if (id > 10000)
        fn_10_a332(line2, id - 10000, 1, (LPSTR)name);
    else if (id != -1)
        LoadString(g_9212, id, line2, 40);
    lstrcat(line1, s1);
    if (lstrlen(line1) > 60 || lstrlen(line2) > 60)
        g_9498++;
    fn_03_31d0(mode, line1, line2);
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
