/* INSPACE.EXE segment 15 (selector 1070). */
#include "inspace.h"

extern int g_1016;
extern int g_8ffc;
extern long g_3b98;
extern int g_95d8;
extern int g_95dc;
extern char g_87e0[];               /* run-time buffer (BSS) */
extern char g_881c[];               /* run-time buffer (BSS) */
extern long g_6e28;
extern long g_6e2c;
extern long g_1e50;

extern int g_92a8;
extern int g_92aa;
extern int g_92b6;
extern int g_92bc;
extern int g_92b0[3];
extern int g_3cc8[2];
extern int g_95d0;

void far fn_10_6e4c(void);
void far fn_10_6e76(long a);
void far fn_10_0552(int i, int a);
void far fn_10_58ce(int a);
void far fn_10_754a(int a, int b, int c, int d);
int far fn_10_6d38(LPCSTR s);
void far fn_10_0136(void);
void far fn_11_a4a6(long a, long b, int c);
void far fn_11_a9ea(int a);

void far fn_15_152e(void);

/* @addr 15:14be */
void far fn_15_14be(void)
{
    int i;

    for (i = 0; i < 3; i++)
        if (g_92b0[i]) {
            DeleteObject(g_92b0[i]);
            g_92b0[i] = 0;
        }
    for (i = 0; i < 2; i++)
        if (g_3cc8[i]) {
            DeleteObject(g_3cc8[i]);
            g_3cc8[i] = 0;
        }
    fn_15_152e();
}

/* @addr 15:152e */
void far fn_15_152e(void)
{
    if (g_92b6) {
        SelectObject(g_92b6, g_92aa);
        if (g_92bc)
            SelectPalette(g_92b6, g_92bc, 0);
        DeleteDC(g_92b6);
        DeleteObject(g_92a8);
        g_92b6 = g_92a8 = 0;
    }
}

/* @addr 15:5914 */
void far fn_15_5914(void)
{
    g_95f4 = fn_10_6d38("SD_LOGO");
}

/* @addr 15:5932 */
void far fn_15_5932(void)
{
    int unused;

    fn_10_0136();
    if (g_95f4) {
        DeleteObject(g_95f4);
        g_95f4 = 0;
    }
}

void far fn_15_80da(void);

/* @addr 15:80b0 */
void far fn_15_80b0(long a, long b)
{
    fn_15_80da();
    fn_11_a4a6(a, g_3b98 = b, 14);
}

/* @addr 15:80da */
void far fn_15_80da(void)
{
    if (g_1016) {
        if (g_8ffc < 0x578) {
            fn_11_a9ea(0);
            g_1016 = 0;
        } else {
            do
                fn_11_a9ea(0);
            while (g_1016);
        }
    }
}

void far fn_15_811a(void);

/* @addr 15:7b34 */
void far fn_15_7b34(void)
{
    g_6e28 = g_1e50 + 90000L;
    fn_10_6e76(MAKELONG(8, g_95dc = 0));
    fn_10_6e4c();
    fn_10_0552(0x16, 1);
    fn_10_58ce(0);
    fn_10_754a(0x13, 0, 0, 0);
    g_95d0 = 50;
    g_95d8 = 0;
    g_6e2c = 0;
    fn_15_811a();
}

/* @addr 15:811a */
void far fn_15_811a(void)
{
    LoadString(g_9212, g_95d8 + 1000, g_87e0, 60);
    LoadString(g_9212, g_95d8 + 980, g_881c, 60);
    g_95dc = 0;
    g_6e2c = 0;
    g_6e28 = g_1e50 + 90000L;
}
