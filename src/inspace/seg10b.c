/* @cflags /AM /G2 /Gw /Gs /Os */
/* INSPACE.EXE segment 10 (selector 1048): source file 21 of
 * inventory/files.tsv (10:0000..10:39a8), compiled with /G2: the long
 * conditional jumps are jcc+jmp pairs (no 386 jcc rel16) [inferred]. */
#include "inspace.h"

extern HGLOBAL g_94ae;
extern HGLOBAL g_95a4;
extern void far *g_69f4;
extern void far *g_6e24;
extern int g_94a2;
extern int g_94a4;
extern int g_931a;
extern int g_90f4;
extern HDC g_39e8[];
extern HPALETTE g_3a5c[];
extern HBITMAP g_3974[];
extern HBITMAP g_3ad0[];
typedef struct {
    HDC dc1;            /* +0x00 */
    HDC dc2;            /* +0x02 */
    HBITMAP bm1;        /* +0x04 */
    HBITMAP bm2;        /* +0x06 */
    HBITMAP old1;       /* +0x08 */
    HBITMAP old2;       /* +0x0a */
    HPALETTE pal;       /* +0x0c */
    char rest[0x14];
} SURF_22;              /* 34-byte records at DS:9168 [inferred: off-screen surfaces] */
extern SURF_22 g_9168[];
#pragma pack(1)
typedef struct {
    int f00;            /* +0x00 */
    int f02;            /* +0x02 */
    char p04[0x26];
    int f2a;            /* +0x2a */
    char rest[0xad - 0x2c];
} REC_AD;               /* 173-byte records at DS:96d2 */
#pragma pack()
extern REC_AD g_96d2[];
extern POINT g_7b60[][64];
extern POINT g_7ba0[][64];
int far fn_06_720c(int a);
int far fn_06_71b2(int a);
typedef struct {
    int f00;
    int f02;
    int f04;
    int f06;
    int f08;
    int f0a;
    int f0c;
    int f0e;
    char rest[0x24 - 0x10];
} REC_24;
extern REC_24 g_52f4[];
typedef struct {
    char p00[4];
    long f04;
    char p08[0x10];
    int f18;
    char rest[0x70 - 0x1a];
} REC_70;
extern REC_70 far *g_1e00;
extern int g_92f0;
void far fn_15_5932(void);
void far fn_10_022e(int a);
void far fn_10_0552(int i, int a);

/* @addr 10:3864 */
void far fn_10_3864(void)
{
    if (g_94ae) {
        if (g_69f4) {
            GlobalUnlock(g_94ae);
            g_69f4 = 0;
        }
        GlobalFree(g_94ae);
        g_94ae = 0;
    }
    if (g_95a4) {
        if (g_6e24) {
            GlobalUnlock(g_95a4);
            g_6e24 = 0;
        }
        GlobalFree(g_95a4);
        g_95a4 = 0;
    }
    g_931a = g_94a2 = g_94a4 = 0;
}

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

/* @addr 10:0522 */
void far fn_10_0522(int a)
{
    int i;

    for (i = 0; i < 58; i++)
        fn_10_0552(i, a);
}

/* @addr 10:0552 */
void far fn_10_0552(int i, int force)
{
    if (g_39e8[i]) {
        if (!force) {
            if (i == 4 || i == 5 || i == 6 || i == 7)
                return;
            if (i >= 10 && i < 13)
                return;
            if (i == 1 || i == 2 || i == 22 || i == 8 || i == 9 || i == 34)
                return;
        }
        if (g_3a5c[i])
            SelectPalette(g_39e8[i], g_3a5c[i], 0);
        SelectObject(g_39e8[i], g_3974[i]);
        DeleteDC(g_39e8[i]);
        g_39e8[i] = 0;
        if (g_3ad0[i]) {
            DeleteObject(g_3ad0[i]);
            g_3ad0[i] = 0;
        }
    }
}

/* @addr 10:1eb6 */
void far fn_10_1eb6(int a)
{
    int i;
    int u;

    i = a + 40;
    if (g_39e8[i]) {
        if (g_3a5c[i])
            SelectPalette(g_39e8[i], g_3a5c[i], 0);
        SelectObject(g_39e8[i], g_3974[i]);
        DeleteDC(g_39e8[i]);
        g_39e8[i] = 0;
        if (g_3ad0[i]) {
            DeleteObject(g_3ad0[i]);
            g_3ad0[i] = 0;
        }
    }
}

/* @addr 10:061a */
void far fn_10_061a(void)
{
    int i;

    for (i = 0; i < 58; i++) {
        if (g_39e8[i]) {
            if (g_3a5c[i])
                SelectPalette(g_39e8[i], g_3a5c[i], 0);
            SelectObject(g_39e8[i], g_3974[i]);
            DeleteDC(g_39e8[i]);
            g_39e8[i] = 0;
            if (g_3ad0[i]) {
                DeleteObject(g_3ad0[i]);
                g_3ad0[i] = 0;
            }
        }
    }
}

/* @addr 10:1f30 */
void far fn_10_1f30(int a, int b)
{
    int i;
    int j;
    HDC dc;
    HBITMAP bm;
    HBITMAP old;
    HPALETTE pal;

    j = b + 40;
    i = a + 40;
    dc = g_39e8[i];
    bm = g_3ad0[i];
    old = g_3974[i];
    pal = g_3a5c[i];
    g_39e8[i] = g_39e8[j];
    g_3ad0[i] = g_3ad0[j];
    g_3974[i] = g_3974[j];
    g_3a5c[i] = g_3a5c[j];
    g_39e8[j] = dc;
    g_3ad0[j] = bm;
    g_3974[j] = old;
    g_3a5c[j] = pal;
}

/* @addr 10:37d0 */
void far fn_10_37d0(int i)
{
    if (g_9168[i].dc1) {
        SelectObject(g_9168[i].dc1, g_9168[i].old1);
        if (g_920e)
            SelectPalette(g_9168[i].dc1, g_9168[i].pal, 0);
        DeleteDC(g_9168[i].dc1);
        DeleteObject(g_9168[i].bm1);
        g_9168[i].dc1 = 0;
    }
    if (g_9168[i].dc2) {
        SelectObject(g_9168[i].dc2, g_9168[i].old2);
        DeleteDC(g_9168[i].dc2);
        DeleteObject(g_9168[i].bm2);
        g_9168[i].dc2 = 0;
    }
}

/* @addr 10:1620 */
void far fn_10_1620(int i)
{
    int w;
    int j;
    int r;
    int ang;

    w = g_96d2[i].f2a;
    r = g_96d2[i].f02;
    for (j = 0, ang = 270; j < 16; j++, ang -= j % 2 + 22) {
        g_7ba0[i][j].x = fn_06_720c(ang) * r / 127 + w / 2;
        g_7ba0[i][j].y = w / 2 + fn_06_71b2(ang) * r / -127;
    }
}

/* @addr 10:1460 */
void far fn_10_1460(int i)
{
    int w;
    int j;
    int r;
    int ang;

    w = g_96d2[i].f2a;
    r = g_96d2[i].f00 + 3;
    for (j = 0, ang = 450; j < 16; j++, ang -= j % 2 + 22) {
        g_7b60[i][j].x = fn_06_720c(ang) * r / 128 + w / 2;
        g_7b60[i][j].y = w / 2 - fn_06_71b2(ang) * r / 128;
    }
}

/* @addr 10:069a */
void far fn_10_069a(void)
{
    int i;

    for (i = 0; i < g_92f0; i++) {
        g_1e00[i].f18 = 1;
        g_52f4[i].f08 = -1;
        g_52f4[i].f0a = 0;
        g_52f4[i].f0c = 0;
        g_52f4[i].f00 = 0;
        g_52f4[i].f02 = 0;
        switch (i / 8) {
        case 0:
            g_52f4[i].f0e = 0x11;
            break;
        case 1:
            g_52f4[i].f0e = 0xd;
            break;
        case 2:
            g_52f4[i].f0e = 0xb;
            break;
        case 3:
            g_52f4[i].f0e = 9;
            break;
        }
    }
}
