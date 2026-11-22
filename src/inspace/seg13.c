/* INSPACE.EXE segment 13 (selector 1060). */
#include "inspace.h"

extern int g_131a;                 /* debug output on when nonzero */

/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record (DS address = 0x7092 + offset). */
typedef struct {
    char pad_000[0xd4];
    int f_0d4;                      /* DS:7166 */
    char pad_0d6[0xea - 0xd6];
    char f_0ea;                     /* DS:717c */
    char pad_0eb[0x154 - 0xeb];
    long f_154;                     /* DS:71e6 */
    char pad_158[0x15a - 0x158];
} OBJ15A;
extern OBJ15A g_7092[];

/* 0x70-byte records reached through a far pointer at DS:1e30. */
typedef struct {
    char pad_00[0x18];
    int f_18;
    char pad_1a[0x70 - 0x1a];
} REC70;
extern REC70 far *g_1e30;

extern long g_1e50;
extern int g_238c;
extern int g_9316;
extern int g_951a;
extern int g_9646;

void far fn_07_1208(void);

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

/* @addr 13:910a */
int far fn_13_910a(int n)
{
    int i;

    for (i = 0; i <= g_9316; i++) {
        if (i == n)
            continue;
        if (g_1e30[i].f_18 == 0 && g_7092[i].f_0ea != 0)
            return 0;
    }
    return 1;
}
