/* INSPACE.EXE segment 7 (selector 1030). */
#include "inspace.h"

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. Only the fields this file uses are named. */
typedef struct {
    int f00;
    char p02[0x1e - 0x02];
    int f1e;                    /* +1e */
    char p20[0x22 - 0x20];
    int f22;                    /* +22 */
    int f24;                    /* +24 */
    char p26[0x2c - 0x26];
    int f2c;                    /* +2c */
    char p2e[0x54 - 0x2e];
    char f54;                   /* +54 */
    char p55[0x66 - 0x55];
    void (far *f66)(int type, int idx);  /* +66 */
    char p6a[0x70 - 0x6a];
} REC_70;

typedef struct { int x, y; char rest[0x70 - 4]; } REC_70P;

extern REC_70 far *g_1df8[16];
extern REC_70P far *g_1e30;
extern int g_3a02;
extern int g_3a28;
extern int g_9646;
extern int g_90ea;
extern int g_90ec;
extern int g_0a76;
extern HWND g_0a7c;

void far pascal fn_08_1d54(int a, int b);
void far pascal fn_08_1b54(int a, int b);
void far fn_07_233c(int a, int b, int c);

/* @addr 7:11cc */
void far fn_07_11cc(void)
{
    g_1e30[g_9646].x = g_90ea / 2;
    g_1e30[g_9646].y = g_90ec / 2;
}

/* @addr 7:119c */
void far fn_07_119c(int a)
{
    g_0a76 = a;
    if (g_0a7c)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
}

/* @addr 7:2652 */
int far fn_07_2652(int type, int idx, int amount)
{
    if (type == 15)
        return 0;
    if (g_1df8[type][idx].f1e > g_1df8[type][idx].f2c && type != 9)
        return 0;
    g_1df8[type][idx].f1e += amount;
    if (g_1df8[type][idx].f1e > g_1df8[type][idx].f2c) {
        g_1df8[type][idx].f66(type, idx);
        return 1;
    }
    return 0;
}

/* @addr 7:3294 */
void far pascal fn_07_3294(int n)
{
    fn_08_1d54((char)n, 0x1e);
    if (!g_1df8[0][n].f54)
        fn_08_1b54((char)n, 3);
}

/* @addr 7:3400 */
void far pascal fn_07_3400(char c)
{
    fn_08_1d54(c | 0x100, 0x28);
    fn_08_1b54(c | 0x100, 3);
}

/* @addr 7:5660 */
void far fn_07_5660(int n)
{
    int size, gap;

    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    StretchBlt(g_3a02, (size + gap) * n + gap, gap, size, size,
               g_3a28, n * 32, 0, 32, 32, SRCCOPY);
    fn_07_233c(0, n, 0);
}

/* @addr 7:56ba */
void far fn_07_56ba(int n)
{
    int size, gap;

    size = g_1df8[0]->f22;
    gap = g_1df8[0]->f24;
    StretchBlt(g_3a28, n * 32, 0, 32, 32,
               g_3a02, (size + gap) * n + gap, gap, size, size, SRCCOPY);
}

/* @addr 7:63b6 */
void far fn_07_63b6(HMENU menu, LPCSTR text, int checked, UINT id)
{
    UINT flags;

    if (checked)
        flags = MF_CHECKED;
    else
        flags = 0;
    ModifyMenu(menu, id, flags, id, text);
}

/* @addr 7:63f2 */
void far fn_07_63f2(void)
{
    if (g_9458) {
        DestroyWindow(g_9458);
        g_9458 = 0;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_07_233c(int a, int b, int c)
{
    g_0a76 = a + b + c;
}
