/* INSPACE.EXE segment 16 (selector 1078). */
#include "inspace.h"

typedef struct {                /* 0x15a bytes, DGROUP array at DS:70ae */
    int f00;
    char p02[0x30 - 0x02];
    int f30;
    char p32[0x15a - 0x32];
} REC_15A;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    char p02[0xad - 0x02];
} REC_AD;
#pragma pack()

extern REC_15A g_70ae[];
extern REC_AD g_96f0[];
extern int g_92e4;
extern int g_111e;
extern long g_6da8;
extern int g_90f4;
extern int g_952e;
extern int g_9530;
extern int g_9e49;

void far fn_03_06ec(int a, int b, int c, int d);
void far fn_07_13b2(int a, int b, int c);
void far fn_12_2556(int a, int b);
void far fn_18_0378(int a);
void far fn_16_3784(int a, int b);
void far pascal fn_16_590c(DRAWITEMSTRUCT far *dis);
void far pascal fn_16_5ada(DRAWITEMSTRUCT far *dis);

/* @addr 16:085e */
int far fn_16_085e(void)
{
    return 0;
}

/* @addr 16:0872 */
void far fn_16_0872(void)
{
    fn_16_3784(g_952e, 0);
    fn_03_06ec(g_952e, 7, 0, 0x54);
}

/* @addr 16:08a0 */
void far fn_16_08a0(void)
{
    fn_12_2556(7, 0);
    fn_07_13b2(1, 7, 0);
    g_9e49 = 10;
    g_952e = -1;
    g_111e = 0;
    g_6da8 = 0;
}

/* @addr 16:64c8 */
int far fn_16_64c8(void)
{
    char buf[398];

    g_9530 = 3;
    if (g_90f4 == 1)
        fn_18_0378(1);
    else
        fn_18_0378(0);
    return 1;
}

/* @addr 16:3e80 */
int far fn_16_3e80(int i)
{
    int d;

    d = (g_96f0[g_70ae[i].f30].f00 - g_70ae[i].f00) / 7;
    if (g_92e4 == 0)
        g_70ae[i].f00 = g_96f0[g_70ae[i].f30].f00;
    return d / 10 * 10;
}

/* Owner-draw item handler [inferred]. */
/* @addr 16:5a8a */
void far pascal fn_16_5a8a(DRAWITEMSTRUCT far *dis)
{
    RECT rc;

    CopyRect(&rc, &dis->rcItem);
    if (dis->itemID == -1 || (dis->itemState & ODS_FOCUS))
        DrawFocusRect(dis->hDC, &rc);
    else
        fn_16_5ada(dis);
}

/* @addr 16:5ada */
void far pascal fn_16_5ada(DRAWITEMSTRUCT far *dis)
{
    RECT rc;

    fn_16_590c(dis);
    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_FOCUS)
        DrawFocusRect(dis->hDC, &rc);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far pascal fn_16_590c(DRAWITEMSTRUCT far *dis)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_16_3784(int a, int b)
{
}
