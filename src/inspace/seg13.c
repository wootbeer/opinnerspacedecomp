/* INSPACE.EXE segment 13 (selector 1060), first source file (13:0000-68ff).
 * Functions from 13:6900 on were a separate source file (they call
 * 2688/2714/4eec far, and are called far): see seg13b.c. */
#include "inspace.h"

extern int g_131a;                 /* debug output on when nonzero */

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

/* 0x1e-byte records at DS:6e3e [inferred base], three of them (one per
 * child window [inferred], see fn_13_59e8). */
typedef struct {
    int f_00;                       /* DS:6e3e */
    char pad_02[0x0a - 0x02];
    int f_0a;                       /* DS:6e48 */
    int f_0c;                       /* DS:6e4a */
    char pad_0e[0x10 - 0x0e];
    int f_10;                       /* DS:6e4e */
    int f_12;                       /* DS:6e50 */
    int f_14;                       /* DS:6e52 */
    int f_16;                       /* DS:6e54 */
    char pad_18[0x1e - 0x18];
} REC1E;
extern REC1E g_6e3e[];

extern RECAD g_970a[];

extern int g_3824[][8];
extern REC70 far *g_1e30;
extern REC70 far *g_1df8[];

extern long g_1e50;
extern int g_0a7c;
extern int g_1ddc;
extern int g_1dde;
extern int g_1de0;
extern int g_9134;
extern int g_6e8e;
extern int g_6e90;
extern int g_0a76;
extern int g_9316;
extern int g_92e8;
extern int g_9324;
extern HINSTANCE g_8e66;
extern int g_238c;
extern int g_951a;
extern int g_9646;

void far fn_07_1208(void);
void far fn_06_0f1a(int v, char far *buf);
int far pascal fn_08_285a(int far *py, int far *px, POINT a, POINT b);
int far pascal fn_08_19b0(int dy, int dx);
void far fn_03_1542(int a, int b, int c, char far *buf, int d);
void far fn_11_3fd4(char far *s, int n);
void far fn_17_8e60(int a, char far *buf);

/* @addr 13:4eca */
void far fn_13_4eca(LPCSTR text)
{
    if (g_131a)
        OutputDebugString(text);
}

/* @addr 13:2da4 */
void far fn_13_2da4(void)
{
    char buf[110];
}

/* @addr 13:2db8 */
void far fn_13_2db8(void)
{
    char buf[110];
}

/* @addr 13:5850 */
void far fn_13_5850(void)
{
    if (g_95fc) {
        DestroyWindow(g_95fc);
        g_95fc = 0;
    }
}

/* @addr 13:6362 */
void far fn_13_6362(void)
{
    if (g_95fe) {
        DestroyWindow(g_95fe);
        g_95fe = 0;
    }
}

/* @addr 13:371c */
int far fn_13_371c(int a, int b)
{
    int unused;

    if (a != 12)
        return 0;
    if (!(b & 1))
        return 1;
    return 2;
}

/* @addr 13:6716 */
void far fn_13_6716(int i)
{
    if (i == g_9646 && !g_951a && !g_238c)
        fn_07_1208();
    else
        g_7092[i].f_154 = g_1e50 - 1;
}

/* @addr 13:4eec */
void far fn_13_4eec(int i, int d)
{
    if (d > 0)
        g_7092[i].f_080 += (long)(1000 - g_7092[i].f_080) * d / 1000;
    else
        g_7092[i].f_080 = (long)(g_7092[i].f_080 + d) * 1000 / (d + 1000);
}

/* @addr 13:5878 */
void far fn_13_5878(void)
{
    if (g_0a7c && !g_95fc)
        CreateWindow("IS_WATCH", "Ship - Pilot", 0x10cc0000L,
                     g_1ddc, g_1dde, g_1de0 - g_1ddc,
                     GetSystemMetrics(SM_CYCAPTION) + 0x36,
                     g_0016, 0, g_8e66, NULL);
    SetActiveWindow(g_0016);
}

/* @addr 13:100c */
int far pascal fn_13_100c(int i, int v)
{
    if (g_7092[i].f_0e9 != 0)
        return v;
    if (g_7092[i].f_00e > 0 && g_7092[i].f_00e < 7)
        return v;
    v += g_1df8[g_9324][i].f_026;
    if (v >= 16)
        v = 0;
    else if (v <= 0)
        v = 15;
    return v;
}

/* @addr 13:5460 */
void far fn_13_5460(HDC hdc, int a, int k, int j, int i, int shift)
{
    int x, y;

    if (a == 0 && g_238c == 0 && g_1df8[j][i].f_00c == 0
        && g_1df8[j][i].f_00e == 0)
        return;
    if (g_6e3e[k].f_00) {
        x = (g_6e3e[k].f_0a + g_6e3e[k].f_10) >> shift;
        y = (g_6e3e[k].f_0c + g_6e3e[k].f_12) >> shift;
        SetPixel(hdc, x, y, 0L);
        g_6e3e[k].f_00 = 0;
    }
}

/* @addr 13:218a */
void far fn_13_218a(int n, LPSTR out)
{
    char key[40];
    char buf[40];

    LoadString(g_9212, 0xaf, key, 40);
    key[4] = 0;
    fn_06_0f1a(n + 1, buf);
    lstrcat(key, buf);
    LoadString(g_9212, 0xaf, buf, 40);
    GetPrivateProfileString(buf, key, "", out, 20, g_96a9);
}

/* @addr 13:59e8 */
int far fn_13_59e8(int k, int i)
{
    int w;

    if (k == 0 && g_9458)
        return 1;
    if (k == g_9324 && g_95fe)
        return 1;
    for (w = 0; w < 3; w++) {
        if ((w == 0 && g_0a76 == 2) || (w == 1 && g_0a76 == 3)
            || (w == 2 && g_95fc)) {
            if (g_6e3e[w].f_16 == k && g_6e3e[w].f_14 == i)
                return 1;
        }
    }
    return 0;
}

/* Attitude of object i towards object j [inferred]: relation table plus
 * class-vs-class table, adjusted by i's temperament bytes.
 * near-match 44%: 13:2688 (the game loads f_060[j] before indexing
 * g_3824; CL keeps evaluating g_3824 first) */
int far fn_13_2688(int i, int j)
{
    int a, b, u;
    int r;

    a = g_970a[g_7092[i].f_04c].f_000;
    b = g_970a[g_7092[j].f_04c].f_000;
    r = g_7092[i].f_060[j] + g_3824[a][b];
    if (r > 0)
        r += (3 - g_7092[i].f_05b) * 20;
    else
        r += (g_7092[i].f_05c - 3) * 20;
    if (g_92e8)
        return -300;
    return r;
}

/* @addr 13:2dcc */
void far fn_13_2dcc(void)
{
    int i;
    int r;

    for (i = 0; i <= g_9316; i++) {
        if (i == g_9646)
            r = 500;
        else
            r = fn_13_2688(i, g_9646);
        if (r < -80)
            g_1df8[g_9324][i].f_046 = 5;
        else if (r < 80)
            g_1df8[g_9324][i].f_046 = 4;
        else
            g_1df8[g_9324][i].f_046 = 7;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_13_6450(int a, int b, int c)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_13_50b0(int a, int b)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_13_58dc(int a, int b)
{
}

/* @addr 13:6890 */
void far fn_13_6890(int i)
{
    if (g_95fe && i != g_9646)
        fn_13_6450(0, 2, i);
    if (g_95fc && g_6e3e[0].f_16 == g_9324 && g_6e3e[0].f_14 == i)
        fn_13_50b0(0, 2);
    if (g_6e3e[g_0a76 - 2].f_16 == g_9324 && g_6e3e[g_0a76 - 2].f_14 == i)
        fn_13_58dc(0, 2);
}

/* @addr 13:3678 */
void far fn_13_3678(int i)
{
    int e;
    int d;
    int y;
    int x;

    d = fn_08_285a(&y, &x, g_1df8[g_9324][i].f_004,
                   g_1df8[g_7092[i].f_030][g_7092[i].f_032].f_004);
    e = fn_08_19b0(y, x);
    if (d > 90) {
        if ((e > 10 && e < 14) || (e > 2 && e < 6)) {
            if (fn_13_371c(g_7092[i].f_030, g_7092[i].f_032) == 2)
                g_7092[i].f_032--;
        }
    }
}

/* Set the pilot window's title [inferred]. */
/* @addr 13:57ac */
void far fn_13_57ac(void)
{
    char buf[80];
    char title[100];

    fn_03_1542(0, g_6e90, g_6e8e, buf, 0);
    fn_11_3fd4(buf, 2);
    lstrcpy(title, buf);
    if (g_6e90 == g_9324) {
        lstrcat(title, " - ");
        fn_17_8e60(g_6e8e, buf);
        fn_11_3fd4(buf, 2);
        lstrcat(title, buf);
    }
    SetWindowText(g_95fc, title);
}
