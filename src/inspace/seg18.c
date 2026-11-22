/* INSPACE.EXE segment 18 (selector 1088). */
#include "inspace.h"
#include <stdlib.h>

extern int g_9668;
extern int g_9672;
extern int g_a1cd;
extern int g_a1cf;
extern char g_a18f[4];
extern char g_a193[4];
extern HANDLE g_88d8[8];
extern int g_8e62;
extern int g_90f4;
extern int g_9530;
extern long g_8d34;
extern int g_965e;
extern int g_9660;
extern int g_9130;                  /* subgame_active */
#pragma pack(1)
typedef struct {                /* far pointer at DS:6da4 */
    char p00[0x08];
    char f08[0x1c - 0x08];      /* name, "Inner Demon" [inferred] */
    int f1c;
} REC_6DA4;

typedef struct {                /* 0x15a bytes, DGROUP array at DS:70ae */
    int f00;
    char p02[0x06 - 0x02];
    int f06;
    int f08[4];
    char p10[0x8e - 0x10];
    char f8e;
    char f8f;
    char p90[0xce - 0x90];
    char fce;
    char pcf[0x15a - 0xcf];
} REC_15A;
#pragma pack()

extern REC_6DA4 far *g_6da4;
extern REC_15A g_70ae[];
extern int g_9646;
extern unsigned char g_a172[4];
extern unsigned char g_a176;
extern unsigned char g_a177;
extern char g_a178;
extern char g_a179;
extern char g_a17a;
extern HGLOBAL g_9100[];
typedef struct {                /* 0x70-byte records */
    char p00[0x0c];
    int f0c;
    int f0e;
    char p10[0x70 - 0x10];
} REC_70;
extern REC_70 far *g_1df8[21];      /* 0-14: 0x460-byte blocks, 15-20: 0x70 */
extern int g_9324;
extern int g_1318;
extern int g_0010;
extern int g_8d14;
extern int g_8d16;
extern int g_8d18;
extern int g_8d1a;
extern int g_88ec;                  /* window origin, negated [inferred] */
extern int g_88ee;

typedef struct { int f00; char p02[0x12]; } REC_14;     /* 0x14 bytes */
typedef struct { int f00; char p02[0x92]; } REC_94;     /* 0x94 bytes */

extern REC_14 g_1e90[45];
extern REC_94 g_610e[9];
extern REC_14 g_58cc[20];
extern int g_9510;
extern long g_88d0;
extern int g_a1d3;
extern int g_942a;
typedef struct { char p00[0x1a]; int f1a; } REC_1E40;
extern REC_1E40 far *g_1e40;

extern int g_238c;
extern int g_238e;
extern int g_2390;
extern int g_2392;
extern int g_90ea;
extern int g_90ec;
extern DWORD g_1e50;
extern DWORD g_2408;

void far sprite_dc_release(void);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_10_7480(int a, int b);
void far fn_10_744c(int a);
void far fn_12_6d64(int a, int b);
void far fn_06_7c14(void);
void far fn_18_17f6(void);
void far fn_18_1cbe(int a);
void far fn_18_52a0(void);
void far fn_13_65f2(int);
void far fn_11_02f0(void);

/* @addr 18:034c */
void far fn_18_034c(void)
{
    if (g_9668) {
        SelectClipRgn(g_13dc, g_9668);
        g_9672 = 1;
    }
}

/* @addr 18:0378 */
void far fn_18_0378(int demon)
{
    long unused;

    g_8d34 = 0;
    g_965e = g_9660 = 0;
    if (demon) {
        g_9130 = 1;
        sprite_dc_release();
    }
    fn_13_65f2(3);
    fn_11_02f0();
    lstrcpy(g_6da4->f08, "Inner Demon");
    if (g_90f4 != 6)
        g_9530 = 1;
}

/* Creates the eight solid brushes [inferred]. */
/* @addr 18:0b1e */
void far fn_18_0b1e(void)
{
    if (!g_88d8[0]) {
        g_88d8[0] = CreateSolidBrush(RGB(255, 0, 0));
        g_88d8[1] = CreateSolidBrush(RGB(128, 0, 0));
        g_88d8[2] = CreateSolidBrush(RGB(255, 255, 0));
        g_88d8[3] = CreateSolidBrush(RGB(128, 128, 0));
        g_88d8[4] = CreateSolidBrush(RGB(0, 255, 255));
        g_88d8[5] = CreateSolidBrush(RGB(0, 128, 128));
        g_88d8[6] = CreateSolidBrush(RGB(255, 255, 255));
        g_88d8[7] = CreateSolidBrush(RGB(192, 192, 192));
    }
}

/* @addr 18:0ba0 */
void far fn_18_0ba0(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (g_88d8[i]) {
            DeleteObject(g_88d8[i]);
            g_88d8[i] = 0;
        }
    }
}

/* @addr 18:0d4e */
void far fn_18_0d4e(int msg, int key)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 == 1 && g_1318 <= 1)
                    g_9530 = 2;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 18:633c */
void far fn_18_633c(void)
{
    int i;

    g_a1cf = g_a1cd = 0;
    for (i = 0; i < 4; i++)
        g_a18f[i] = g_a193[i] = 1;
}

/* @addr 18:1784 */
void far fn_18_1784(int left, int top, int right, int bottom)
{
    DWORD org;

    if (g_90f4 != 1) {
        if (g_9668) {
            DeleteObject(g_9668);
            g_9668 = 0;
        }
        org = GetWindowOrg(g_13dc);
        g_88ec = LOWORD(org);
        g_88ee = HIWORD(org);
        g_88ec = -g_88ec;
        g_88ee = -g_88ee;
        g_9668 = CreateRectRgn(left + g_88ec, top + g_88ee,
                               right + g_88ec, bottom + g_88ee);
    }
}

/* @addr 18:1e46 */
void far fn_18_1e46(void)
{
    int i;

    for (i = 15; i <= 20; i++) {
        if (g_9100[i]) {
            if (g_1df8[i]) {
                GlobalUnlock(g_9100[i]);
                g_1df8[i] = 0;
            }
            GlobalFree(g_9100[i]);
            g_9100[i] = 0;
        }
    }
}

/* @addr 18:0be2 */
void far fn_18_0be2(void)
{
    int i;

    if (g_6da4)
        g_6da4->f1c = 1;
    for (i = 0; i < 4; i++)
        g_70ae[g_9646].f08[i] = g_a172[i];
    g_70ae[g_9646].f00 = g_a176 * 10;
    g_70ae[g_9646].f06 = g_a177;
    g_70ae[g_9646].f8e = g_a178;
    g_70ae[g_9646].f8f = g_a179;
    g_70ae[g_9646].fce = g_a17a;
}

/* @addr 18:1dd0 */
int far fn_18_1dd0(void)
{
    int i;

    for (i = 15; i <= 20; i++) {
        if ((g_9100[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x70L)) == 0)
            return 0;
        if ((g_1df8[i] = (REC_70 far *)GlobalLock(g_9100[i])) == 0) {
            GlobalFree(g_9100[i]);
            return 0;
        }
    }
    return 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_18_17f6(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_18_1cbe(int a)
{
    g_9510 = a;
}

/* @addr 18:5220 */
void far fn_18_5220(int a)
{
    int i;

    if (g_90f4 == 1) {
        g_8d34 = GetCurrentTime() + 4000;
        fn_12_6d64(g_9646, a + 0x16);
        fn_10_744c(0x66);
    } else {
        g_a1cd += 10;
        g_a1d3++;
        fn_10_744c(0x25);
    }
    g_1e40->f1a = 0;
    g_942a = 0;
    for (i = 0; i < 12; i++)
        fn_06_7c14();
    if (g_90f4 == 6)
        fn_18_52a0();
}

/* @addr 18:52a0 */
void far fn_18_52a0(void)
{
    int ok;
    int i;

    ok = 1;
    for (i = 0; i < 4; i++)
        if (g_a18f[i])
            ok = 0;
    if (ok) {
        for (i = 0; i < 45; i++)
            g_1e90[i].f00 = -1;
        for (i = 0; i < 9; i++)
            g_610e[i].f00 = -1;
        for (i = 0; i < 20; i++)
            g_58cc[i].f00 = -1;
        g_9510 = 100;
        g_a1cf++;
        fn_10_7480(-2, 1);
        fn_18_17f6();
        fn_18_1cbe(1);
        g_88d0 = 2;
    }
}

/* @addr 18:591c */
void far fn_18_591c(void)
{
    if (g_238c) {
        fn_10_754a(8, rand() % g_90ea, rand() % g_90ec, 4);
        g_2390 += g_238c;
        g_2392 += g_238e;
        g_2390 += rand() % 3 - 2;
        g_2392 += rand() % 3 - 2;
        if (g_2390 > 5)
            g_238c = -9;
        else if (g_2390 < -5)
            g_238c = 9;
        if (g_2392 > 5)
            g_238e = -6;
        else if (g_2392 < -5)
            g_238e = 6;
        if (g_2408 < g_1e50)
            g_238c = 0;
        if (g_90f4 == 6) {
            g_2390 >>= 1;
            g_2392 >>= 1;
        }
    } else {
        *(long *)&g_2390 = 0;   /* clears g_2390 and g_2392 in one dword store */
    }
}

/* @addr 18:5f74 */
void far fn_18_5f74(void)
{
    int x;
    int t;

    fn_10_744c(0x48);
    g_1df8[g_9324][g_9646].f0e = 0;
    g_1df8[g_9324][g_9646].f0c = g_1df8[g_9324][g_9646].f0e;
    g_1318 = 2;
    t = (g_90ec * 4 / 3 - 1100) / 36 + 164;
    x = min((g_90ea - t) / 2 - 20, 260);
    g_8d14 = x - 18;
    g_8d16 = 164;
    g_8d1a = min(g_0010 * 2 / 5, g_0010 - 370);
    g_8d18 = max(g_90ea / -13 - x + g_90ea / 2 - 90, 0);
}
