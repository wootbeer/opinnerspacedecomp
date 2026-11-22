/* INSPACE.EXE segment 17 (selector 1080). */
#include "inspace.h"

typedef struct {                /* 0x15a bytes, DGROUP array at DS:70ae */
    int f00;
    char p02[0x30 - 0x02];
    int f30;
    char p32[0xce - 0x32];
    char fce;
    char pcf[0x15a - 0xcf];
} REC_15A;

typedef struct {                /* 0x70-byte records, far pointer at DS:1e30 */
    char p00[0x18];
    int f18;
    char p1a[0x70 - 0x1a];
} REC_70;

extern REC_15A g_70ae[];
extern REC_70 far *g_1e30;
extern int g_1924;
extern int g_9466;
extern int g_9468;
extern long g_1e50;
extern void far *g_6078;
extern int g_9004;
extern int g_9144;
extern HGLOBAL g_948e;

void far fn_07_2206(void);
void far fn_17_0000(int a, int b);
void far fn_17_65da(void);
void far fn_17_67e6(void);
void far pascal fn_17_90d2(DRAWITEMSTRUCT far *dis);
void far pascal fn_17_9308(DRAWITEMSTRUCT far *dis);

/* @addr 17:306e */
void far fn_17_306e(void)
{
    if (g_948e) {
        if (g_6078) {
            GlobalUnlock(g_948e);
            g_6078 = 0;
        }
        GlobalFree(g_948e);
        g_948e = 0;
    }
}

/* @addr 17:60d8 */
void far fn_17_60d8(void)
{
    if (++g_9144 >= g_9004) {
        fn_07_2206();
        g_9144 = 0;
        g_1e50 = GetCurrentTime();
        fn_17_0000(0, 0);
    }
}

/* @addr 17:6742 */
void far fn_17_6742(int a, int b, HWND hwnd, int code)
{
    int unused;
    int sel;
    char buf[30];

    switch (code) {
    case CBN_SELCHANGE:
        sel = (int)SendMessage(hwnd, CB_GETCURSEL, 0, 0L);
        if (sel == -1)
            break;
        g_9466 = sel;
        fn_17_65da();
        g_9468 = 0;
        fn_17_67e6();
        g_1924 = sel;
        break;
    }
}

/* @addr 17:75c6 */
int far fn_17_75c6(int n)
{
    int i;
    int cnt;

    cnt = 0;
    for (i = 0; i < n; i++)
        if (g_1e30[i].f18 == 0 && g_70ae[i].fce != 0)
            cnt += 2;
    return cnt;
}

/* @addr 17:92b8 */
void far pascal fn_17_92b8(DRAWITEMSTRUCT far *dis)
{
    RECT rc;

    CopyRect(&rc, &dis->rcItem);
    if (dis->itemID == -1 || (dis->itemState & ODS_FOCUS))
        DrawFocusRect(dis->hDC, &rc);
    else
        fn_17_9308(dis);
}

/* @addr 17:9308 */
void far pascal fn_17_9308(DRAWITEMSTRUCT far *dis)
{
    RECT rc;

    fn_17_90d2(dis);
    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_FOCUS)
        DrawFocusRect(dis->hDC, &rc);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far pascal fn_17_90d2(DRAWITEMSTRUCT far *dis)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_65da(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_67e6(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_0000(int a, int b)
{
}
