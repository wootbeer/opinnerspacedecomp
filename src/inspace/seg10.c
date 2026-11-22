/* INSPACE.EXE segment 10 (selector 1048). */
#include "inspace.h"

extern int g_90f4;
extern int g_9228;
extern int g_9210;
extern int g_921e;
extern long g_90ea;

typedef int (far pascal *FP7I)(int, int, int, int, int, int, int);
extern int  (far pascal *g_fp_3c34)(int, int, long, int, int, int, int, int, int, char, char);
extern int  (far pascal *g_fp_3c44)(int, int, int, int, int, int, int, int, int);
extern int  (far pascal *g_fp_3c48)(int, int, int, int, int, int, int, int, int, int, long);
extern int  (far pascal *g_fp_3c58)(POINT, int, int, long);
extern int  (far pascal *g_fp_3c68)(char far *, char far *, int);

void far fn_10_0552(int i, int a);
void far fn_10_6ee6(int a, int b, char far *s, int c, int d, int e, int f,
                    int g, int h, int i, int j, int k, int l);
extern int g_9300;
extern int g_39ee;
extern HGDIOBJ g_3c60[2];
extern char g_9156;
extern void (far pascal *g_fp_3c78)(int, int, long, int, int, long, int, long,
                                    int, int, int, long, int);
extern void (far pascal *g_fp_3c30)(int, int, long, int, int, int, int, int,
                                    int, int, char, char, char, int);
extern void (far pascal *g_fp_3c6c)(long, long, long, long, long, long, long,
                                    long, long, long, long, long);
extern void (far pascal *g_fp_3c38)(int, int, long, int, int, int, int, char,
                                    char, int, int, char, char);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_10_80dc(void);
int far fn_10_82a2(int a);
void far fn_10_81b6(void);
void far fn_15_5932(void);
void far fn_10_022e(int a);

/* @addr 10:01fe */
int far fn_10_01fe(void)
{
    switch (g_90f4) {
    case 0:
        fn_15_5932();
        break;
    case 1:
        fn_10_022e(1);
        break;
    }
    return 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_022e(int a)
{
    g_90f4 = a;
}

/* @addr 10:6d38 */
int far fn_10_6d38(LPCSTR s)
{
    return g_fp_3c2c(s);
}

/* @addr 10:6e26 */
void far fn_10_6e26(void)
{
    g_fp_3c50(g_920e, 0, 0, 0, 0L, 2);
}

/* @addr 10:6ec6 */
void far fn_10_6ec6(int a)
{
    g_fp_3c40(g_920e, a, g_13dc);
}

/* @addr 10:6b54 */
void far fn_10_6b54(void)
{
    g_fp_3c84(0, g_1e4c);
}

/* @addr 10:7db8 */
void far fn_10_7db8(void)
{
    g_fp_3c54(g_05a0, 2);
}

/* @addr 10:8686 */
void far fn_10_8686(void)
{
    g_8e5c = 0;
    g_fp_3c54(g_05a0, 3);
}

/* @addr 10:86ca */
void far fn_10_86ca(void)
{
    int r;

    r = 0;
    g_fp_3c4c();
}

/* @addr 10:86a8 */
void far fn_10_86a8(void)
{
    g_8e5c = 1;
    g_fp_3c54(g_05a0, 4);
}

/* @addr 10:6e00 */
void far fn_10_6e00(void)
{
    g_920e = g_fp_3c50(0, 0, 0, 0, 0L, 0);
}

/* @addr 10:6ea0 */
void far fn_10_6ea0(unsigned a)
{
    g_fp_3c50(g_920e, 0, 0, 0, a, 7);
}

/* @addr 10:6e4c */
void far fn_10_6e4c(void)
{
    g_fp_3c50(g_920e, g_0016, g_13dc, 0, 0L, 3);
}

/* @addr 10:6e76 */
void far fn_10_6e76(long a)
{
    g_fp_3c50(g_920e, 0, 0, 0, a, 1);
    fn_10_6e4c();
}

void far fn_10_4672(int a, int b);

/* @addr 10:464a */
void far fn_10_464a(void)
{
    g_928a = fn_10_6d38("DEF");
    fn_10_4672(0, 3);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_4672(int a, int b)
{
    g_928a = a + b;
}

/* @addr 10:5c1a */
void far fn_10_5c1a(void)
{
    if (g_9288) {
        DeleteDC(g_9288);
        g_9288 = 0;
    }
}

/* @addr 10:6d52 */
void far fn_10_6d52(int a, int b, int c, int d, int e, int f)
{
    g_fp_3c80(a, b, c, d, e, f);
}

/* @addr 10:949c */
void far fn_10_949c(int a, int b, int c, int d, int e, int f)
{
    g_fp_3c70(a, b, c, d, e, f);
}

/* @addr 10:993a */
void far fn_10_993a(int a, int b)
{
    g_fp_3c7c(g_920e, a, b, g_0016, g_13dc);
}

/* @addr 10:73e2 */
void far fn_10_73e2(void)
{
    if (!g_9228) {
        g_9228 = 1;
        g_fp_3c54(g_05a0, 0);
    }
}

/* @addr 10:7d8e */
void far fn_10_7d8e(void)
{
    if (g_9228) {
        g_9228 = 0;
        g_fp_3c54(g_05a0, 1);
    }
}

/* @addr 10:6d7a */
void far fn_10_6d7a(int a, int b, int c)
{
    int r;

    ((FP7I)g_fp_3c50)(g_920e, 0, 0, a, b, c, 6);
}

/* @addr 10:6da6 */
void far fn_10_6da6(int a, int b)
{
    ((FP7I)g_fp_3c50)(g_920e, 0, g_13dc, 0, a, b, 4);
    fn_10_6e4c();
}

/* @addr 10:6dd4 */
void far fn_10_6dd4(int a)
{
    ((FP7I)g_fp_3c50)(g_920e, 0, g_13dc, 0, a, 0, 5);
    fn_10_6e4c();
}

/* @addr 10:0522 */
void far fn_10_0522(int a)
{
    int i;

    for (i = 0; i < 58; i++)
        fn_10_0552(i, a);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_0552(int i, int a)
{
    g_90f4 = i + a;
}

/* @addr 10:946a */
int far fn_10_946a(char far *p)
{
    char buf[20];
    int r;

    r = g_fp_3c68(p, buf, 10);
    p[0x30] = 0;
    return r;
}

/* @addr 10:744c */
void far fn_10_744c(int a)
{
    fn_10_754a(0x69, 0, 0, 0);
    if (a != 0x69)
        fn_10_754a(a, 0, 0, 0);
}

/* @addr 10:80a8 */
int far fn_10_80a8(void)
{
    int r;

    if (g_921e < 20) {
        g_921e++;
        fn_10_80dc();
        r = fn_10_82a2(8);
        fn_10_81b6();
    }
    return r;
}

/* @addr 10:7370 */
void far fn_10_7370(int a, int b, int c, int d, int e, int f, int g)
{
    int r;

    g_fp_3c44(g_13dc, a, b, c, d, e, g_920e, f, g);
}

/* @addr 10:7d58 */
void far fn_10_7d58(int x, int y)
{
    POINT p;

    if (g_9210) {
        p.x = x;
        p.y = y;
        g_fp_3c58(p, -10, -10, g_90ea);
    }
}

/* @addr 10:6bca */
void far fn_10_6bca(int a, int b, int c, int d, int e, int f, int g, int h,
                    int i, int j, long k)
{
    g_fp_3c48(a, b, c, d, e, f, g, h, i, j, k);
}

/* @addr 10:73a6 */
void far fn_10_73a6(int a, long b, int c, int d, int e, int f, int g,
                    char h, char i)
{
    g_fp_3c34(g_920e, a, b, g_13dc, c, d, e, f, g, h, i);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_754a(int a, int b, int c, int d)
{
    g_90f4 = a + b + c + d;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_80dc(void)
{
    g_90f4 = 0;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_81b6(void)
{
    g_90f4 = 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_10_82a2(int a)
{
    return a;
}

/* @addr 10:561a */
void far fn_10_561a(void)
{
    if (g_9300 && !g_39ee)
        fn_10_6ee6(3, 0xb4, "", 0, 0x63, 3, 0, 1, 0, 12, 12, 0, 0);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_6ee6(int a, int b, char far *s, int c, int d, int e, int f,
                    int g, int h, int i, int j, int k, int l)
{
    g_90f4 = a;
}

/* @addr 10:740c */
void far fn_10_740c(void)
{
    HWND h;
    HTASK t;
    int u;

    h = GetActiveWindow();
    t = GetWindowTask(g_0016);
    if (GetWindowTask(h) == t)
        g_fp_3c54(g_05a0, 9);
}

/* @addr 10:5cfa */
void far fn_10_5cfa(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        if (g_3c60[i]) {
            DeleteObject(g_3c60[i]);
            g_3c60[i] = 0;
        }
    }
}

/* @addr 10:9526 */
void far fn_10_9526(long a, int b, int c, long d, int e, long f, int g,
                    int h, int i, long j, int k)
{
    g_fp_3c78(g_13dc, g_920e, a, b, c, d, e, f, g, h, i, j, k);
}

/* @addr 10:6fec */
void far fn_10_6fec(int a, long b, int c, int d, int e, int f, int g, int h,
                    char i, char j, char k, int l)
{
    g_fp_3c30(g_920e, a, b, g_13dc, c, d, e, f, g, h, i, j, k, l);
}

/* @addr 10:7dd4 */
void far pascal fn_10_7dd4(long a, long b, long c, long d, long e, long f,
                           long g, long h, long i, long j, long k, long l)
{
    g_fp_3c6c(a, b, c, d, e, f, g, h, i, j, k, l);
}

/* @addr 10:7328 */
void far fn_10_7328(int a, long b, int c, int d, char e, char f, int g, int h,
                    char i, char m)
{
    int r;

    g_fp_3c38(g_920e, a, b, g_13dc, m, c, d, e, f, g, h, i, g_9156);
}
