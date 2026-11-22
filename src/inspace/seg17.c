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
    int f_024;    /* DS:70b6 */
    char pad_026[0x26];
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
extern long g_1890;
extern long g_1894;
extern long g_18a4;
extern long g_18a0;
extern int g_6088;
extern char g_57b4[][35];
extern int g_9464;
extern HINSTANCE g_8e66;
extern int g_946a;
extern HWND g_9482;
extern HWND g_9480;
extern int g_9470;
extern long g_1898;
extern LPSTR g_6078;
extern int g_9004;
extern int g_9144;
extern HGLOBAL g_948e;

void far fn_07_2206(void);
void far fn_17_0000(int a, int b);
void far fn_17_65da(void);
void far fn_17_30b0(int a, int b, int c);
int far fn_17_2c5a(int a, int b);
void far fn_17_458e(void);
void far fn_17_51b0(void);
void far fn_17_5008(void);
int far fn_17_8910(int a, HWND hwnd, int b);
void far fn_17_14fc(void);
void far fn_03_1542(int a, int b, int c, LPSTR buf, int d);
void far fn_13_33d6(int i);
void far fn_17_3746(void);
void far fn_17_33ee(void);
void far fn_17_42ea(int flag);
void far fn_17_8e60(int i, LPSTR buf);
void far fn_11_3fd4(LPSTR buf, int a);
void far fn_17_8572(HWND hDlg);
void far fn_17_8874(HWND hDlg, int ok);
void far fn_17_84ee(int id, LPARAM lParam);
HBITMAP far world_map(int w, int h, int a, int b, int c, int d, int e);
void far fn_10_a332(LPSTR text, char *cls, int a, ...);
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

/* @addr 17:108c */
int far fn_17_108c(int reset)
{
    int unused;

    if (reset)
        g_1890 = 0;
    if (g_1890) {
        if (g_1890 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        g_5000 = g_6084 + 20;
        g_5002 = g_608a - 40;
        fn_17_30b0(g_93aa, 4500, 0);
        fn_17_458e();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6084 + 20;
        g_5002 = g_608a - 40;
            fn_17_458e();
            fn_17_2c5a(1, 1);
        } else if (fn_17_2c5a(0, 0) == 2 && !g_9460)
            g_9462++;
        break;
    case 2:
        g_1890 = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* @addr 17:1174 */
int far fn_17_1174(int reset)
{
    int unused;

    if (reset)
        g_1894 = 0;
    if (g_1894) {
        if (g_1894 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        g_5000 = g_6088 - 280;
        g_5002 = g_6086 + 60;
        fn_17_30b0(g_9468 + 305, 4500, 0);
        fn_17_51b0();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6088 - 280;
        g_5002 = g_6086 + 60;
            fn_17_51b0();
            fn_17_2c5a(1, 1);
        } else if (fn_17_2c5a(0, 0) == 2 && !g_9460)
            g_9462++;
        break;
    case 2:
        g_1894 = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* @addr 17:4204 */
void far fn_17_4204(void)
{
    char name[60];
    int i;
    int cnt[3];
    int j;
    int k;
    int v;

    k = g_96f0[g_7092[g_9646].f_04c].f1a;
    for (i = 0; i < 3; i++)
        cnt[i] = 0;
    for (i = 0; i < 8; i++) {
        j = i;
        if (k == j)
            continue;
        v = g_3824[j][k];
        if (v < -80)
            cnt[0]++;
        else if (v < 80)
            cnt[1]++;
        else
            cnt[2]++;
    }
    fn_13_218a(g_96f0[g_7092[g_9646].f_04c].f1a, name);
    fn_10_a332(g_6078, "", 1, (LPSTR)name, !cnt[0], cnt[0], cnt[0], 0x9dd,
               !cnt[2], cnt[2], cnt[2], 0x9de, cnt[1], cnt[1], 0x9d8);
}

/* @addr 17:15c6 */
int far fn_17_15c6(int reset)
{
    int unused;

    if (reset)
        g_18a4 = 0;
    if (g_18a4) {
        if (g_18a4 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        g_5000 = g_9468 == 0 ? g_6084 + 30 : (g_6088 - g_6084) / 2 + g_6084;
        g_5002 = g_6086 + 55;
        fn_17_30b0(g_93aa, 3000, 0);
        fn_17_5008();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_9468 == 0 ? g_6084 + 30 : (g_6088 - g_6084) / 2 + g_6084;
            g_5002 = g_6086 + 55;
            fn_17_2c5a(1, 1);
            fn_17_5008();
        } else
            fn_17_2c5a(0, 0);
        break;
    case 2:
        g_18a4 = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* @addr 17:13ca */
int far fn_17_13ca(int reset)
{
    int unused;

    if (reset)
        g_18a0 = 0;
    if (g_18a0) {
        if (g_18a0 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        fn_17_5008();
        if (!g_9460 || !((g_9468 + 1) & 1)) {
            fn_17_14fc();
            g_5000 = g_6088 - 280;
            g_5002 = g_6086 + 54;
        } else {
            g_5000 = 20;
            g_5002 = g_6086 + 40;
        }
        fn_17_30b0(g_93aa + 400, 3000, 0);
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            fn_17_5008();
            if (!g_9460 || !((g_9468 + 1) & 1)) {
                fn_17_14fc();
                g_5000 = g_6088 - 280;
                g_5002 = g_6086 + 54;
            } else {
                g_5000 = 20;
                g_5002 = g_6086 + 40;
            }
            fn_17_2c5a(1, 1);
        } else if (fn_17_2c5a(0, 0) == 2 && !g_9460)
            g_9462++;
        break;
    case 2:
        g_18a0 = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* @addr 17:12f6 */
int far fn_17_12f6(int reset)
{
    int unused;

    if (reset)
        g_189c = 0;
    if (g_189c) {
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

/* @addr 17:0c2e */
void far fn_17_0c2e(int idx, int x, int y)
{
    char buf[50];
    HFONT oldfont;
    HFONT hfont;
    COLORREF oldtext;
    COLORREF oldbk;

    hfont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, TA_CENTER);
    oldtext = SetTextColor(g_13dc, 0x0200ff80L);
    lstrcpy(buf, g_57b4[idx]);
    TextOut(g_13dc, x + 0x20, y + 0x44, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
}

/* @addr 17:32de */
void far fn_17_32de(int flag)
{
    int unused1;
    int unused2;
    int unused3;
    int saved;
    char a[50];
    char b[50];

    lstrcpy(g_6078, "");
    if (flag) {
        fn_09_95ba(0x130);
        fn_09_95ba(0x221);
        fn_03_1542(0, 0xe, g_9464, a, 0);
        lstrcat(g_6078, a);
        fn_17_42ea(1);
        fn_09_95ba(0x131);
        fn_17_8e60(g_9464, b);
        lstrcat(g_6078, b);
        fn_17_42ea(1);
        fn_09_95ba(0x132);
        fn_13_218a(g_96f0[g_7092[g_9464].f_04c].f1a, a);
        lstrcat(g_6078, a);
        saved = g_7092[g_9464].f_024;
        g_7092[g_9464].f_024 = 100;
        fn_13_33d6(g_9464);
        g_7092[g_9464].f_024 = saved;
        fn_17_42ea(1);
        fn_17_42ea(1);
        fn_17_3746();
    } else
        fn_17_33ee();
}

/* @addr 17:55e2 */
void far fn_17_55e2(int n)
{
    HFONT hfont;
    HFONT oldfont;
    COLORREF oldbk;
    COLORREF oldtext;
    char buf[70];
    int unused1;
    int unused2;
    int unused3;

    hfont = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    if (n == -1) {
        fn_09_955c(0x30f2, buf);
        fn_11_3fd4(buf, 1);
    } else
        fn_09_955c(g_2f54[n].f00, buf);
    oldtext = SetTextColor(g_13dc, 0x020080ffL);
    TextOut(g_13dc, g_6084 + 40, g_6086 + 20, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
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
        if (g_1898 < g_1e50)
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

/* @addr 17:646e */
void far fn_17_646e(void)
{
    int i;
    int h;
    int x;
    char s[] = "Test";
    char buf[220];
    HFONT old;
    RECT rc;

    GetClientRect(g_9460, &rc);
    g_13dc = GetDC(g_9460);
    old = SelectObject(g_13dc, g_6094[0]);
    h = HIWORD(GetTextExtent(g_13dc, s, 4));
    SelectObject(g_13dc, old);
    ReleaseDC(g_9460, g_13dc);
    g_13dc = 0;
    g_9470 = 9;
    for (i = 1; i < 27; i++)
        if (fn_10_5586(i)) {
            g_9470++;
            break;
        }
    if (g_9480)
        DestroyWindow(g_9480);
    if (g_6088 > 670)
        x = rc.left + 256;
    else
        x = rc.left + 186;
    g_9480 = CreateWindow("combobox", "", 0x50210003L, x, rc.bottom - 0x1c,
                          0x8c, h * g_9470 + 0x1e, g_9460, (HMENU)0x67, g_8e66, NULL);
    SendMessage(g_9480, WM_SETFONT, g_6094[0], 1L);
    for (i = 0; i < g_9470; i++) {
        fn_09_955c(i + 800, buf);
        SendMessage(g_9480, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    }
    SendMessage(g_9480, CB_SETCURSEL, g_9466, 0L);
}

/* @addr 17:65da */
void far fn_17_65da(void)
{
    int unused1;
    int h;
    int n;
    int unused2;
    char s[] = "Test";
    char unused3[220];
    HFONT old;
    RECT rc;

    GetClientRect(g_9460, &rc);
    g_13dc = GetDC(g_9460);
    old = SelectObject(g_13dc, g_6094[0]);
    h = HIWORD(GetTextExtent(g_13dc, s, 4));
    SelectObject(g_13dc, old);
    ReleaseDC(g_9460, g_13dc);
    g_13dc = 0;
    if (g_9482)
        DestroyWindow(g_9482);
    g_946a = fn_17_8910(g_9466, 0, 0);
    n = g_9466 == 0 ? g_946a / 2 : g_946a;
    if (g_946a < 2)
        EnableWindow(g_947a[2], 0);
    else
        EnableWindow(g_947a[2], 1);
    EnableWindow(g_947a[0], 0);
    if (n > 15)
        n = 15;
    g_9482 = CreateWindow("combobox", "", 0x50210003L, rc.right - 0xe0, rc.bottom - 0x1c,
                          0xa0, n * h + 0x1e, g_9460, (HMENU)0x68, g_8e66, NULL);
    SendMessage(g_9482, WM_SETFONT, g_6094[0], 1L);
    fn_17_8910(g_9466, g_9482, 0);
    if (g_9466 == 0)
        g_9464 = g_9646;
    g_9468 = 0;
    SendMessage(g_9482, CB_SETCURSEL, 0, 0L);
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
int far fn_17_2c5a(int a, int b)
{
    return 0;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_458e(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_51b0(void)
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
void far fn_17_3746(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_33ee(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_17_8910(int a, HWND hwnd, int b)
{
    return 0;
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
