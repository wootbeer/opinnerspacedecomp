/* INSPACE.EXE segment 17 (selector 1080). */
#include "inspace.h"

/* 0x15a-byte object records, DGROUP array at DS:7092 (base = lowest
 * offset accessed with an index * 0x15a; same layout as seg13.c). */
typedef struct {
    char pad_000[0x8];
    int f_008;    /* DS:709a */
    int f_00a;    /* DS:709c */
    char pad_00c[0x6];
    int f_012;    /* DS:70a4 */
    char pad_014[0x8];
    int f_01c;    /* DS:70ae */
    char pad_01e[0x4];
    int f_022;    /* DS:70b4 */
    char pad_024[0x28];
    int f_04c;    /* DS:70de */
    char pad_04e[0xe];
    char f_05c;    /* DS:70ee */
    char pad_05d[0x4d];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    signed char f_0ac[10];    /* DS:713e */
    signed char f_0b6[10];    /* DS:7148 */
    char pad_0c0[0x9];
    signed char f_0c9;    /* DS:715b */
    char pad_0ca[0xa];
    int f_0d4;    /* DS:7166 */
    char pad_0d6[0x8];
    char f_0de;    /* DS:7170 */
    char f_0df;    /* DS:7171 */
    char pad_0e0[0xa];
    char f_0ea;    /* DS:717c */
    char pad_0eb[0x6f];
} OBJ15A;

typedef struct {                /* 0x70-byte records, far pointer at DS:1e30 */
    char p00[0x18];
    int f18;
    char p1a[0x70 - 0x1a];
} REC_70;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    char p02[0x1a - 0x02];
    int f1a;
    char p1c[0xad - 0x1c];
} REC_AD;
#pragma pack()

extern OBJ15A g_7092[];
extern REC_AD g_96f0[];
extern int g_3824[][8];
extern int g_9646;
extern HWND g_948c;
extern long g_1898;
extern int g_5000;
extern int g_5002;
extern int g_6084;
extern int g_608a;
extern int g_9460;
extern int g_9462;
extern int g_9474;
typedef struct {                /* 0x7c-byte records, far pointer at DS:6e24 */
    char p00[0x65];
    char name[0x7c - 0x65];
} REC_7C;
extern REC_7C far *g_6e24;
typedef struct {                /* 0x14-byte records, DGROUP array at DS:4d92 */
    char f00;
    char f01;
    char p02[0x08 - 0x02];
    int f08;
    char p0a[0x10 - 0x0a];
    int f10;
    char p12[0x14 - 0x12];
} REC_14;
extern REC_14 g_4d92[];
extern int g_4ed4[];
typedef struct { int f00; char p02[0x50 - 0x02]; } REC_50;
extern REC_50 g_2f54[];
extern int g_6086;
extern int g_9322;
extern HGDIOBJ g_9490;
extern HGDIOBJ g_93ae;
extern int g_946c;
extern HWND g_947a[9];
extern HGDIOBJ g_6094[2];
extern REC_70 far *g_1e30;
extern int g_1924;
extern int g_1926;
extern int g_93a2;
extern int g_93aa;
extern int g_9484;
extern int g_9466;
extern int g_9468;
extern DWORD g_1e50;
extern long g_189c;
extern LPSTR g_6078;
extern int g_9004;
extern int g_9144;
extern HGLOBAL g_948e;

void far fn_07_2206(void);
void far fn_17_0000(int a, int b);
void far fn_17_65da(void);
void far fn_17_30b0(int a, int b, int c);
void far fn_17_2c5a(int a, int b);
void far fn_17_5008(void);
void far fn_17_8572(HWND hDlg);
void far fn_17_8874(HWND hDlg, int ok);
void far fn_17_84ee(int id, LPARAM lParam);
HBITMAP far world_map(int w, int h, int a, int b, int c, int d, int e);
void far fn_10_a332(LPSTR text, char *cls, int a, int b, int c, int d, int e,
                    int f, int g, int h, int i, int j, int k, int l);
void far fn_09_955c(int id, LPSTR buf);
int far fn_10_5586(int i);
void far fn_06_0f1a(int v, LPSTR buf);
void far fn_13_218a(int i, LPSTR buf);
void far fn_17_4988(void);
void far fn_09_9580(int id, LPSTR buf);
void far fn_17_8a92(int a, int b, LPSTR buf);
void far fn_17_8f1e(int a, int b, int c, int d, LPSTR buf);
void far fn_09_95ba(int id);
void far fn_17_7ba6(int a, LPSTR buf);
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

/* @addr 17:6036 */
void far fn_17_6036(void)
{
    int i;

    if (g_9490) {
        DeleteObject(g_9490);
        g_9490 = 0;
    }
    g_946c = -1;
    fn_17_306e();
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
    for (i = 0; i < 9; i++)
        if (g_947a[i]) {
            DestroyWindow(g_947a[i]);
            g_947a[i] = 0;
        }
    for (i = 0; i < 2; i++)
        if (g_6094[i]) {
            DeleteObject(g_6094[i]);
            g_6094[i] = 0;
        }
}

/* @addr 17:8e60 */
void far fn_17_8e60(int i, LPSTR buf)
{
    char tmp[20];
    int a;
    int b;
    int c;

    if (g_7092[i].f_0d4 >= 0) {
        lstrcpy(buf, g_6e24[g_7092[i].f_0d4].name);
    } else {
        a = g_7092[i].f_05c;
        b = i;
        LoadString(g_9212, 0x314, buf, 40);
        c = (i * 2 + 3) * (a + 2) * (i + 6) * (i + 7) * 2 / (a + 3) + 956;
        fn_06_0f1a(c, tmp);
        lstrcat(buf, " ");
        lstrcat(buf, tmp);
    }
}

/* @addr 17:14fc */
void far fn_17_14fc(void)
{
    HDC hdc;
    HBITMAP hbm;
    HBITMAP old;
    HPALETTE oldpal;
    int n;

    if (g_9460)
        n = (g_9468 - 1) / 2;
    else
        n = g_9322;
    hbm = world_map(g_608a - g_6086, g_608a - g_6086, 1, n, -1, -1, 0);
    hdc = CreateCompatibleDC(g_13dc);
    if (g_920e)
        oldpal = SelectPalette(hdc, g_920e, 0);
    old = SelectObject(hdc, hbm);
    BitBlt(g_13dc, g_6084, g_6086, g_608a - g_6086, g_608a - g_6086, hdc, 0, 0, SRCCOPY);
    SelectObject(hdc, old);
    if (g_920e)
        SelectPalette(hdc, oldpal, 0);
    DeleteDC(hdc);
    DeleteObject(hbm);
}

/* @addr 17:7614 */
void far fn_17_7614(int i)
{
    int unused;
    int id;

    if (g_4ed4[i] == 11)
        id = 0x829;
    if (g_4d92[g_4ed4[i]].f08 > 1200)
        id = 0x81f;
    else if (g_4d92[g_4ed4[i]].f08 > 700)
        id = 0x820;
    else
        id = 0x821;
    fn_10_a332(g_6078, "button", 1, g_4d92[g_4ed4[i]].f10 + 10000, g_4d92[g_4ed4[i]].f00,
               0x819, 0x818, g_4d92[g_4ed4[i]].f01 <= 0, g_4d92[g_4ed4[i]].f01 > 0,
               g_4d92[g_4ed4[i]].f01 == 1, g_2f54[g_4d92[g_4ed4[i]].f01].f00, 0x81d,
               g_4d92[g_4ed4[i]].f10 + 10000, id);
}

/* @addr 17:12f6 */
int far fn_17_12f6(int reset)
{
    int unused;

    if (reset)
        g_189c = 0;
    if (g_189c) {
        /* Same CL 8.00c /G3 32-bit compare as in fn_17_1260. */
        if (g_189c < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        g_5000 = g_6084 + 30;
        g_5002 = g_6086 + 40;
        fn_17_30b0(g_93aa, 3000, 0);
        fn_17_5008();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6084 + 30;
            g_5002 = g_6086 + 40;
            fn_17_2c5a(1, 1);
            fn_17_5008();
        } else
            fn_17_2c5a(0, 0);
        break;
    case 2:
        g_189c = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* Dialog procedure [inferred]. */
/* @addr 17:8418 */
BOOL far pascal fn_17_8418(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int v;
    char buf[110];
    int idx;

    switch (msg) {
    case WM_INITDIALOG:
        fn_17_8572(hDlg);
        break;
    case WM_COMMAND:
        switch (wParam) {
        case 0x195:
            v = HIWORD(lParam);
            if (v == EN_CHANGE) {
                GetWindowText(GetDlgItem(hDlg, 0x195), buf, 100);
                SendMessage(GetDlgItem(hDlg, 0x199), LB_SELECTSTRING, -1, (LPARAM)(LPSTR)buf);
                /* idx is never assigned: the original reads it uninitialised. */
                if (idx == -1)
                    SendMessage(GetDlgItem(hDlg, 0x199), LB_SETCURSEL, 0, 0L);
            }
            break;
        case 0x199:
            fn_17_84ee(wParam, lParam);
            break;
        case IDOK:
            fn_17_8874(hDlg, 1);
            return TRUE;
        case IDCANCEL:
            fn_17_8874(hDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
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

/* @addr 17:6792 */
void far fn_17_6792(int a, int b, HWND hwnd, int code)
{
    int sel;

    switch (code) {
    case CBN_SELCHANGE:
        sel = (int)SendMessage(hwnd, CB_GETCURSEL, 0, 0L);
        if (sel == -1)
            break;
        g_9468 = g_9466 == 0 ? sel * 2 : sel;
        fn_17_67e6();
        g_1926 = sel;
        break;
    }
}

/* @addr 17:7b44 */
void far fn_17_7b44(void)
{
    char buf[84];

    lstrcpy(g_6078, "");
    fn_09_95ba(0x82d);
    fn_17_7ba6(g_93a2, buf);
    lstrcat(g_6078, buf);
    fn_09_95ba(0x82e);
    lstrcat(g_6078, ". ");
}

/* @addr 17:42ea */
void far fn_17_42ea(int flag)
{
    lstrcat(g_6078, " ");
    if (g_93aa != 11 || flag) {
        lstrcat(g_6078, "  ");
        g_6078[lstrlen(g_6078) - 2] = '\r';
        g_6078[lstrlen(g_6078) - 1] = '\n';
    }
}

/* @addr 17:72aa */
void far fn_17_72aa(int a, int b, int c)
{
    char buf1[110];
    char buf2[110];

    if (a) {
        fn_17_8a92(b, c, buf1);
        lstrcpy(buf2, buf1);
        if (c) {
            lstrcat(buf2, " - ");
            fn_09_9580(c + 800, buf2);
        }
        fn_17_8f1e(b, c, 0, g_9484, buf2);
    }
}

/* Appends the ordinal suffix of n to buf [inferred]. */
/* @addr 17:7ba6 */
void far fn_17_7ba6(int n, LPSTR buf)
{
    fn_06_0f1a(n, buf);
    if (n % 10 == 1 && n != 11)
        fn_09_9580(0x82f, buf);
    else if (n % 10 == 2 && n != 12)
        fn_09_9580(0x830, buf);
    else if (n % 10 == 3 && n != 13)
        fn_09_9580(0x831, buf);
    else
        fn_09_9580(0x832, buf);
}

/* @addr 17:84ee */
void far fn_17_84ee(int id, LPARAM lParam)
{
    char buf[120];
    int sel;

    switch (HIWORD(lParam)) {
    case LBN_SELCHANGE:
        SendMessage((HWND)LOWORD(lParam), LB_GETTEXT,
                    sel = (int)SendMessage((HWND)LOWORD(lParam), LB_GETCURSEL, 0, 0L),
                    (LPARAM)(LPSTR)buf);
        buf[lstrlen(buf) - 9] = 0;
        SetWindowText(GetDlgItem(g_948c, 0x195), buf);
        break;
    case LBN_DBLCLK:
        PostMessage(g_948c, WM_COMMAND, 1, 0L);
        break;
    }
}

/* @addr 17:56fe */
void far fn_17_56fe(int i, LPSTR buf)
{
    int k;
    int v;
    char tmp[50];

    k = g_96f0[g_7092[g_9646].f_04c].f1a;
    fn_13_218a(i, buf);
    lstrcat(buf, "...(");
    v = g_3824[i][k];
    fn_06_0f1a(v / 10, tmp);
    lstrcat(buf, tmp);
    lstrcat(buf, ")");
}

/* @addr 17:1260 */
int far fn_17_1260(int reset)
{
    int unused;

    if (reset)
        g_1898 = 0;
    if (g_1898) {
        /* CL 8.00c /G3 emits this 32-bit compare as cmp g_1898,g_1e50;
         * jae (taken when g_1898 >= g_1e50): the game's behaviour is
         * "return 1 while g_1898 < g_1e50". */
        if (g_1898 > g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        g_5000 = g_6084 + 20;
        g_5002 = g_608a - 40;
        fn_17_4988();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6084 + 20;
            g_5002 = g_608a - 40;
            fn_17_4988();
        }
        break;
    case 2:
        g_1898 = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* @addr 17:8874 */
void far fn_17_8874(HWND hDlg, int ok)
{
    char buf[110];
    int sel;
    int v;
    int unused;

    g_948c = 0;
    if (ok) {
        sel = (int)SendMessage(GetDlgItem(hDlg, 0x199), LB_GETCURSEL, 0, 0L);
        SendMessage(GetDlgItem(hDlg, 0x199), LB_GETTEXT, sel, (LPARAM)(LPSTR)buf);
        v = (buf[lstrlen(buf) - 2] - '0') * 100;
        v += buf[lstrlen(buf) - 1] - '0';
    } else
        v = 0;
    EndDialog(hDlg, v);
}

/* @addr 17:7526 */
int far fn_17_7526(int n)
{
    char name1[80];
    char name2[80];
    int i;
    int k;
    int unused;

    if (n >= 0)
        fn_09_955c(n + 0xba, name1);
    k = 0;
    for (i = 1; i < 27; i++) {
        if (fn_10_5586(i)) {
            if (n == -1)
                return 1;
            fn_09_955c(i + 0xba, name2);
            if (lstrcmp(name1, name2) == 0)
                return k;
            k++;
        }
    }
    if (n == -1)
        return 0;
    return -1;
}

/* @addr 17:75c6 */
int far fn_17_75c6(int n)
{
    int i;
    int cnt;

    cnt = 0;
    for (i = 0; i < n; i++)
        if (g_1e30[i].f18 == 0 && g_7092[i].f_0ea != 0)
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
void far fn_17_8a92(int a, int b, LPSTR buf)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_30b0(int a, int b, int c)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_2c5a(int a, int b)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_5008(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_8572(HWND hDlg)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_8f1e(int a, int b, int c, int d, LPSTR buf)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_4988(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_0000(int a, int b)
{
}
