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

extern int g_058c;
extern long g_05c0;
extern unsigned long g_1e50;
extern char g_380c[];               /* run-time buffer (BSS) */
extern int g_6e8e;
extern int g_6e90;
extern char g_8630[];               /* run-time buffer (BSS) */
extern int g_9646;

/* Not yet decompiled: stubs so calls to them compile as near calls. */
int far fn_03_0000(int a, int b) { return 0; }
void far fn_03_00f4(int a, long b) { }

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
