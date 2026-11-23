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
    char pad_014[0x2];
    int f_016;    /* DS:70a8 */
    char pad_018[0x4];
    int f_01c;    /* DS:70ae */
    char pad_01e[0x4];
    int f_022;    /* DS:70b4 */
    int f_024;    /* DS:70b6 */
    int f_026;
    int f_028;
    int f_02a;    /* DS:70bc */
    char pad_02c[0x20];
    int f_04c;    /* DS:70de */
    char pad_04e[0xd];
    char f_05b;    /* DS:70ed */
    char f_05c;    /* DS:70ee */
    char pad_05d[0x4d];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    signed char f_0ac[10];    /* DS:713e */
    signed char f_0b6[10];    /* DS:7148 */
    char pad_0c0[0x9];
    signed char f_0c9;    /* DS:715b */
    char pad_0ca[0x2];
    int f_0cc;    /* DS:715e */
    int f_0ce;    /* DS:7160 */
    int f_0d0;    /* DS:7162 */
    char pad_0d2[0x2];
    int f_0d4;    /* DS:7166 */
    int f_0d6;    /* DS:7168 */
    char pad_0d8[0x2];
    long f_0da;    /* DS:716c */
    char f_0de;    /* DS:7170 */
    char f_0df;    /* DS:7171 */
    char pad_0e0[0xa];
    char f_0ea;    /* DS:717c */
    char pad_0eb[0x6f];
} OBJ15A;

typedef struct {                /* 0x70-byte records, far pointer at DS:1e30 */
    char p00[0x18];
    int f18;
    char p1a[0x22 - 0x1a];
    int f22;
    int f24;
    char p26[0x70 - 0x26];
} REC_70;

#pragma pack(1)
typedef struct {                /* 0xad bytes, DGROUP array at DS:96f0 */
    int f00;
    char p02[0x0a - 0x02];
    int f0a;
    char p0c[0x1a - 0x0c];
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
    char name[0x77 - 0x65];
    signed char f77;
    char p78[0x7c - 0x78];
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
extern int g_9468;
extern int g_93a2;
extern int g_93aa;
extern int g_9484;
extern int g_9466;
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
void far fn_17_30b0(int id, long v);
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
void far fn_17_8f1e(int a, int b, int c, HWND hwnd, LPSTR buf);
void far fn_09_95ba(int id);
void far fn_17_7ba6(int a, LPSTR buf);
void far fn_17_67e6(void);
void far pascal fn_17_90d2(DRAWITEMSTRUCT far *dis);
void far pascal fn_17_9308(DRAWITEMSTRUCT far *dis);
extern int g_9316;
extern int g_92fe;
extern int g_92f0;
extern int g_4ee0[2];
extern int g_94c6;
void far fn_06_6576(void);
#pragma pack(1)
typedef struct {                /* 0x31-byte records, far pointer at DS:6af8 */
    char p00[0x04];
    char name[0x22 - 0x04];
    int f22;
    char p24[0x26 - 0x24];
    char f26[0x30 - 0x26];
    signed char f30;
} REC_31;
typedef struct {                /* 0x41-byte records, far pointer at DS:6e20 */
    char p00[0x0a];
    char name[0x41 - 0x0a];
} REC_41;
#pragma pack()
extern REC_31 far *g_6af8;
extern REC_41 far *g_6e20;
extern int g_9214;
int far fn_14_3eda(void);
void far fn_14_4074(void);
extern int g_0956[11];
void far fn_17_7c2a(void);
extern char g_9078[];
extern char g_96b8[];
extern char g_96c5[];
int far fn_14_4006(HFILE f, char huge *buf, unsigned long len);
void far fn_06_8eea(LPSTR p);
void far pascal fn_10_a118(LPSTR src, LPSTR dst);
int far fn_17_75c6(int n);
int far fn_17_7526(int n);
void far fn_17_646e(void);
extern int g_93c6;
extern int g_0a76;
extern int g_6e70;
extern int g_6e72;
extern int g_6e52;
extern int g_6e54;
extern int g_094e;
typedef struct {                /* 0x34-byte records, DGROUP array at DS:3d6c */
    int f00;
    char p02[0x14 - 0x02];
    int f14;
    char p16[0x34 - 0x16];
} REC_34;
extern REC_34 g_3d6c[];
extern DWORD g_18b0;
extern int g_18b4;
extern HBITMAP g_5780[];
extern HDC g_39e8[];
extern REC_70 far *g_1e00;
void far fn_10_9962(int unused, HDC dst, int x, int y, int w, int h, HDC src,
                    int xs, int ys, int ws, int hs, DWORD rop);
void far fn_17_55e2(int n);
extern int g_90f4;
void far fn_17_8270(void);
extern int g_9478;
extern long g_6090;
void far fn_09_6fee(void);
void far fn_17_306e(void);
void far fn_17_7614(int i);
void far fn_17_76e4(void);
void far fn_17_4204(void);
void far fn_17_7b44(void);
void far fn_17_32de(int flag);
extern int g_9472;
void far fn_17_72aa(int a, int b, int c);
int far fn_13_2688(int i, int j);
void far ship_status_lines(int flag);
extern int g_95bc;              /* flow.interactive */
extern int g_91f8;
void far fn_17_4068(int i, LPSTR buf);
extern int g_9134;
extern int g_92f2;
extern int g_9416;
extern int g_946e;
extern HWND g_9488;
void far fn_09_6624(void);
void far fn_10_744c(int a);
int far fn_17_0600(int reset);
int far fn_17_0d22(int reset);
int far fn_17_1b3e(int reset, int kind);
int far fn_17_16cc(int reset, int n);
int far fn_17_20fa(int reset, int a, int b);
int far fn_17_108c(int reset);
int far fn_17_1174(int reset);
int far fn_17_1260(int reset);
int far fn_17_12f6(int reset);
int far fn_17_13ca(int reset);
int far fn_17_15c6(int reset);
int far fn_17_193c(int reset);
extern DWORD g_18a8;
extern POINT g_18ac;           /* bitmap size */
HBITMAP far fn_11_2ff6(int n);
extern long g_1e58;
extern char g_38c8[];
extern char g_09ee[];
extern char g_8d38[];
extern char g_8db0[];
extern char g_8768[];
extern char g_87b8[];
void far fn_06_0f54(long v, int div, int width, LPSTR buf);
void far fn_06_1010(int v, int div, int width, LPSTR buf);
void far fn_03_1d0a(int i, int j, int k);
void far fn_03_3498(LPSTR a, LPSTR b, LPSTR c);
extern int g_607c;
extern int g_607e;
extern int g_6080;
extern int g_6082;
extern int g_608c;
extern int g_608e;
extern char g_06b0[];
extern DWORD g_1886;
extern int g_188a;
extern int g_188c;
extern int g_188e;
extern REC_70 far *g_1e08;
extern HDC g_39f0;
void far fn_10_3a2e(void);
void far fn_10_3ea2(void);
extern int g_8f70;
extern int g_90f8;
extern int g_90ea;
extern DWORD g_1876;
extern DWORD g_05ac;
int far fn_09_8d18(int init, int quiet);
void far fn_17_03b2(void);
void far fn_17_6036(void);
extern POINT g_190a;            /* typewriter cursor [inferred] */
extern POINT g_190e;            /* previous cursor [inferred] */
extern int g_1912;              /* index into g_6078 */
extern int g_1914;
extern DWORD g_1916;            /* next character time */
extern DWORD g_191a;
extern int g_0ba2;              /* text finished */
void far fn_15_84b0(int x, int y);

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
        fn_17_30b0(g_93aa, 4500L);
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
        fn_17_30b0(g_9468 + 305, 4500L);
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
        fn_17_30b0(g_93aa, 3000L);
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
        fn_17_30b0(g_93aa + 400, 3000L);
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
        fn_17_30b0(g_93aa, 3000L);
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

/* Types the briefing text g_6078 a few characters per call [inferred]. */
/* @addr 17:2c5a */
int far fn_17_2c5a(int a, int b)
{
    HFONT oldfont;
    HFONT hfont;
    DWORD oldtext;
    DWORD oldbk;
    char word[54];
    int i;
    int n;
    int pad[8];
    int hasctl;
    int wrap;
    int margin;
    int j;
    int len;

    n = 10;
    if (a) {
        if (!b)
            fn_15_84b0(g_5000 + 15, g_5002 + 10);
        g_0ba2 = 0;
        g_1912 = 0;
        g_1914 = 0;
        g_190a = *(POINT *)&g_5000;
        g_1916 = g_1e50 + 500;
        g_191a = 0;
        if (!b)
            return 0;
        n = 1000;
    } else {
        if (a && g_1912 < 250)
            g_1912 = 250;
        if (g_1916 > g_1e50)
            return 0;
        g_1916 = g_1e50 + 50;
    }
    if (g_0ba2) {
        g_1916 = g_1e50 + 400;
        if (!g_191a) {
            g_191a = g_6090 + g_1e50;
            if (!b)
                PatBlt(g_13dc, g_190a.x + 4, g_190a.y + 2, 12, 12, BLACKNESS);
        }
    } else {
        hfont = CreateFont(13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
        oldfont = SelectObject(g_13dc, hfont);
        oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
        SetBkMode(g_13dc, TRANSPARENT);
        SetTextAlign(g_13dc, 0);
        oldtext = SetTextColor(g_13dc, RGB(0, 255, 255));
        for (i = 0; i < n; i++) {
            wrap = 0;
            if (g_9478 && g_6078[g_1912] == ' ') {
                len = hasctl = 0;
                j = g_1912;
                do {
                    j++;
                    if ((word[++len] = g_6078[j]) == 9 || word[len] == 13)
                        hasctl = 1;
                } while (g_6078[j] != 0 && g_6078[j] != ' ' && g_6078[j] != 13);
                if (!hasctl) {
                    int w;

                    word[len + 1] = 0;
                    w = LOWORD(GetTextExtent(g_13dc, word, len)) + g_190a.x;
                    if (len > 5)
                        margin = 9;
                    else
                        margin = 22;
                    if (g_6088 - margin < w)
                        wrap = 1;
                }
            }
            if (g_6078[g_1912] == 13 || wrap) {
                g_190a.x = g_5000;
                g_190a.y += 18;
                if (g_6078[g_1912] == 13)
                    g_1912++;
            } else if (g_6078[g_1912] == 9) {
                g_190a.x = (g_6078[g_1912 + 1] - '0') * 100 + (g_6078[g_1912 + 2] - '0') * 10
                           + (g_6078[g_1912 + 3] - '0') + g_5000;
                g_1912 += 3;
            } else {
                HBRUSH oldbr;

                if (g_1912 && !b)
                    PatBlt(g_13dc, g_190e.x + 4, g_190e.y + 2, 12, 18, BLACKNESS);
                TextOut(g_13dc, g_190a.x, g_190a.y, g_6078 + g_1912, 1);
                g_190a.x += LOWORD(GetTextExtent(g_13dc, g_6078 + g_1912, 1));
                if (!b) {
                    oldbr = SelectObject(g_13dc, CreateSolidBrush(RGB(0, 255, 255)));
                    PatBlt(g_13dc, g_190a.x + 4, g_190a.y + 2, 12, 12, PATCOPY);
                    DeleteObject(SelectObject(g_13dc, oldbr));
                    g_190e = g_190a;
                }
            }
            g_1912++;
            if (!b)
                fn_10_744c(0x2b);
            if (!b && g_6078[g_1912] == 13 && g_6078[g_1912 - 1] == 10
                && g_93aa != 15 && g_93aa != 17) {
                g_1916 = g_1e50 + 900;
                break;
            }
            if (g_6078[g_1912] == 0) {
                g_0ba2 = 1;
                break;
            }
        }
        SetBkColor(g_13dc, oldbk);
        SetTextColor(g_13dc, oldtext);
        SelectObject(g_13dc, oldfont);
        if (hfont) {
            DeleteObject(hfont);
            hfont = 0;
        }
        if (g_0ba2) {
            if (g_191a && g_191a < g_1e50)
                return 2;
            return 1;
        }
        return 0;
    }
    if (g_191a && g_191a < g_1e50)
        return 2;
    return 1;
}

/* Draws the friends / neutral / enemies lists of the relations page [inferred]. */
/* @addr 17:458e */
void far fn_17_458e(void)
{
    HFONT font;
    HGDIOBJ oldfont;
    COLORREF oldbk;
    COLORREF oldtxt;
    char buf1[80];
    char buf2[70];
    int i;
    int j;
    int me;
    int rel;
    POINT pt;

    font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    fn_09_955c(0x382, buf2);
    oldtxt = SetTextColor(g_13dc, PALETTERGB(0, 214, 255));
    TextOut(g_13dc, g_5000, g_6086 + 20, buf2, lstrlen(buf2));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtxt);
    SelectObject(g_13dc, oldfont);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
    font = CreateFont(13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    me = g_96f0[g_7092[g_9646].f_04c].f1a;
    oldtxt = SetTextColor(g_13dc, RGB(0, 255, 255));
    pt.y = g_6086 + 60;
    pt.x = g_5000;
    fn_09_955c(0x380, buf1);
    lstrcat(buf1, "S");
    TextOut(g_13dc, pt.x, pt.y, buf1, lstrlen(buf1));
    pt.y += 28;
    for (i = 0; i < 8; i++) {
        j = i;
        if (j != me && (rel = g_3824[j][me]) > 80) {
            fn_17_56fe(j, buf2);
            TextOut(g_13dc, pt.x, pt.y, buf2, lstrlen(buf2));
            pt.y += 18;
        }
    }
    oldtxt = SetTextColor(g_13dc, PALETTERGB(192, 192, 192));
    pt.y = g_6086 + 60;
    pt.x = g_6084 + 210;
    fn_09_955c(0x246, buf1);
    TextOut(g_13dc, pt.x, pt.y, buf1, lstrlen(buf1));
    pt.y += 28;
    for (i = 0; i < 8; i++) {
        j = i;
        if (j != me && (rel = g_3824[j][me]) < 80 && rel > -80) {
            fn_17_56fe(j, buf2);
            TextOut(g_13dc, pt.x, pt.y, buf2, lstrlen(buf2));
            pt.y += 18;
        }
    }
    oldtxt = SetTextColor(g_13dc, PALETTERGB(255, 128, 60));
    pt.y = g_6086 + 60;
    pt.x = g_6084 + 410;
    fn_09_955c(0x30ed, buf1);
    TextOut(g_13dc, pt.x, pt.y, buf1, lstrlen(buf1));
    pt.y += 36;
    for (i = 0; i < 8; i++) {
        j = i;
        if (j != me && (rel = g_3824[j][me]) < -80) {
            fn_17_56fe(j, buf2);
            TextOut(g_13dc, pt.x, pt.y, buf2, lstrlen(buf2));
            pt.y += 18;
        }
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtxt);
    SelectObject(g_13dc, oldfont);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
}

/* @addr 17:51b0 */
void far fn_17_51b0(void)
{
    HFONT hfont;
    HFONT oldfont;
    DWORD oldbk;
    DWORD oldtext;
    char buf[80];
    char name[70];
    int i;
    int count;
    int unused;
    int side;
    int rel;
    POINT pt;
    int rel2;

    hfont = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    side = g_96f0[g_7092[g_9646].f_04c].f1a;
    fn_13_218a(g_9468 - 1, name);
    if ((rel = g_3824[g_9468 - 1][side]) > 80 || g_9468 - side - 1 == 0)
        oldtext = SetTextColor(g_13dc, PALETTERGB(0, 0xd6, 0xff));
    else if (rel < -80)
        oldtext = SetTextColor(g_13dc, PALETTERGB(0xff, 0x80, 0));
    else
        oldtext = SetTextColor(g_13dc, PALETTERGB(0xc0, 0xc0, 0xc0));
    TextOut(g_13dc, g_6084 + 40, g_6086 + 20, name, lstrlen(name));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
    hfont = CreateFont(13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    SetTextColor(g_13dc, RGB(0, 255, 255));
    pt.y = g_6086 + 60;
    pt.x = g_6084 + 40;
    if (g_9468 - side - 1 == 0) {
        fn_09_955c(0x806, buf);
    } else {
        i = count = 0;
        for (; i <= g_9316; i++)
            if (g_7092[i].f_0ea && g_96f0[g_7092[i].f_04c].f1a - g_9468 + 1 == 0)
                count++;
        if (count == 1)
            fn_09_955c(0x807, buf);
        else
            fn_09_955c(0x808, buf);
        fn_06_0f1a(count, name);
        lstrcat(buf, " ");
        lstrcat(buf, name);
        lstrcat(buf, " ");
        fn_13_218a(g_9468 - 1, name);
        lstrcat(buf, name);
        if (count == 1)
            buf[lstrlen(buf) - 1] = 0;
        TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
        pt.y += 18;
        fn_09_955c(0x80a, buf);
        lstrcat(buf, g_09ee);
        TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
        pt.y += 36;
        fn_13_218a(g_9468 - 1, buf);
        lstrcat(buf, " ");
        rel2 = g_3824[g_9468 - 1][side];
        if (rel2 < -80)
            fn_09_9580(0x80b, buf);
        else if (rel2 < 80)
            fn_09_9580(0x80c, buf);
        else
            fn_09_9580(0x80d, buf);
        if (rel2 < 80) {
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            pt.y += 18;
            lstrcpy(buf, "");
        }
        fn_09_9580(0x33e, buf);
    }
    lstrcat(buf, g_09ee);
    TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_3746(void)
{
}

/* Writes the relations/finance lines of the contact report [inferred]. */
/* @addr 17:33ee */
void far fn_17_33ee(void)
{
    int rel;
    int rel2;
    int c1;
    int c2;
    char buf3e[52];
    char buf66[40];
    char buff2[140];
    int id1;
    int id2;

    if (g_9464 == g_9646) {
        fn_06_0f54(g_7092[g_9464].f_0da, 100, 2, buf3e);
        fn_06_1010(g_7092[g_9464].f_0cc, 100, 2, buf66);
        fn_10_a332(g_6078, (char *)0xbdb, 0, g_91f8 < 1 ? 1 : g_91f8, (LPSTR)g_38c8, g_1e58,
                   g_7092[g_9646].f_0d0, 0x9d3, g_7092[g_9646].f_0ce, 0x9d3,
                   (LPSTR)buf3e, (LPSTR)buf66);
        if (g_9460)
            return;
        fn_17_42ea(1);
        fn_17_42ea(1);
    } else {
        if (g_96f0[g_7092[g_9464].f_04c].f1a != 7 && g_7092[g_9464].f_0d4 >= 0
            && g_6e24[g_7092[g_9464].f_0d4].f77 > 1)
            fn_10_a332(g_6078, (char *)0xbda, 0, 0xe, g_9464, 3,
                       g_6e24[g_7092[g_9464].f_0d4].f77 < 4,
                       g_6e24[g_7092[g_9464].f_0d4].f77 == 2, 0x39a, 0x39b,
                       g_6e24[g_7092[g_9464].f_0d4].f77 >= 4,
                       g_6e24[g_7092[g_9464].f_0d4].f77 - 1);
        else
            fn_10_a332(g_6078, (char *)0x399, 0, 0xe, g_9464, 3);
        if (g_96f0[g_7092[g_9464].f_04c].f1a != 7 && g_7092[g_9464].f_0d4 >= 0
            && g_6e24[g_7092[g_9464].f_0d4].f77 > 1) {
            fn_09_95ba(0x7fe);
            lstrcat(g_6078, g_09ee);
        }
        c1 = g_96f0[g_7092[g_9464].f_04c].f1a;
        c2 = g_96f0[g_7092[g_9646].f_04c].f1a;
        if (c1 == c2) {
            rel = 90;
            id1 = 0x319;
        } else {
            rel = g_3824[c1][c2];
            if (rel < -80)
                id1 = 0x316;
            else if (rel < 80)
                id1 = 0x317;
            else
                id1 = 0x318;
        }
        rel2 = fn_13_2688(g_9646, g_9464);
        if (rel2 < -80)
            id2 = 0x316;
        else if (rel2 < 80)
            id2 = 0x317;
        else
            id2 = 0x318;
        fn_10_a332(g_6078, (char *)0x31a, 0, id1,
                   id2 == id1 || (id2 == 0x318 && id1 == 0x319) ? 1 : 0,
                   0x800, 0x31b, id2);
        if (g_9460) {
            lstrcpy(buff2, g_8d38);
            fn_03_1d0a(g_9646, g_9464, 2);
            lstrcpy(g_8db0, g_8d38);
            ((void (far *)(char *))fn_11_3fd4)(g_8db0);
            fn_03_3498(g_8db0, g_8768, g_87b8);
            fn_06_0f54(g_7092[g_9464].f_0da, 100, 2, buf3e);
            fn_06_1010(g_7092[g_9464].f_0cc, 100, 2, buf66);
            fn_10_a332(g_6078, (char *)0xbde, 0, (LPSTR)g_8768, (LPSTR)g_87b8,
                       (LPSTR)buf3e, (LPSTR)buf66);
            lstrcpy(g_8d38, buff2);
            return;
        }
    }
    fn_17_4068(g_9464, buff2);
    lstrcat(g_6078, buff2);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_4988(void)
{
}

/* @addr 17:0000 */
void far fn_17_0000(int a, int b)
{
    int done;
    int v;
    int f;
    int pad;

    if (!g_9460 && (g_8f70 || g_90f8) && g_93aa != 18) {
        g_93aa = 18;
        return;
    }
    f = 0;
    if (g_93aa != 11)
        g_946c = -1;
    if (g_9462 == -3) {
        PatBlt(g_13dc, g_6084, g_6086, g_6088 - g_6084, g_608a - g_6086, BLACKNESS);
        fn_10_744c(0x6e);
        done = fn_17_20fa(1, 0, 1);
    }
    if (g_9462 == -2)
        fn_17_03b2();
    if (g_9462 == -1) {
        if (g_93aa == 11) {
            PatBlt(g_13dc, g_6084, g_6086, g_6088 - g_6084, g_608a - g_6086, BLACKNESS);
            fn_10_744c(0x6e);
            done = fn_17_20fa(1, 1, 0);
            if (g_9462 == -1)
                g_9462 = 0;
            if (done && !g_9460) {
                g_93aa = 18;
                fn_17_03b2();
            }
        } else {
            b = f = 1;
            g_1876 = g_1e50 - 10;
        }
    }
    if (b) {
        if (g_9460)
            return;
        *(long *)&g_608c = *(long *)&g_90ea;
        if (!f) {
            fn_09_8d18(1, a);
            if (g_93aa)
                g_1876 = g_1e50 - 10;
            v = a;
        } else
            v = fn_09_8d18(0, 0);
        if (!v) {
            if (!a && !f)
                g_93aa = 0;
            else {
                fn_09_8d18(1, 1);
                fn_09_8d18(0, 1);
                g_1876 = g_1e50 - 10;
            }
        }
    }
    v = fn_09_8d18(0, 0);
    if (g_93aa)
        SelectClipRgn(g_13dc, g_93ae);
    done = 0;
    switch (g_93aa) {
    case 0:
        if (v && !g_1876)
            g_1876 = g_1e50 + 500;
        break;
    case 1:
        done = fn_17_0600(0);
        break;
    case 3:
        if (!g_91f8 || g_9460)
            done = fn_17_0d22(0);
        else
            done = 1;
        break;
    case 4:
        if (!g_91f8 && g_92f2 || g_9460)
            done = fn_17_1b3e(0, 3);
        else
            done = 1;
        break;
    case 5:
        if (!g_094e && g_91f8 == 1 || g_9460)
            done = fn_17_1b3e(0, 7);
        else
            done = 1;
        break;
    case 7:
        if ((g_91f8 == 1 || g_9460) && g_92f0)
            done = fn_17_193c(0);
        else
            done = 1;
        break;
    case 8:
        if (g_4ee0[0])
            done = fn_17_1b3e(0, 8);
        else
            done = 1;
        break;
    case 9:
        if (g_4ee0[1])
            done = fn_17_1b3e(0, 8);
        else
            done = 1;
        break;
    case 10:
        if (g_9460 && fn_10_5586(g_9472))
            done = fn_17_16cc(0, g_9472);
        else
            done = 1;
        break;
    case 6:
        if (g_92fe)
            done = fn_17_1b3e(0, 9);
        else
            done = 1;
        break;
    case 14:
        if (g_9460)
            done = fn_17_1260(0);
        else
            done = 1;
        break;
    case 2:
        if (g_9460 || g_094e)
            done = fn_17_13ca(0);
        else
            done = 1;
        break;
    case 15:
    case 17:
        if (g_9460)
            done = fn_17_12f6(0);
        else
            done = 1;
        break;
    case 16:
        if (g_9460)
            done = fn_17_15c6(0);
        else
            done = 1;
        break;
    case 12:
        if (g_9460)
            done = fn_17_108c(0);
        else
            done = 1;
        break;
    case 13:
        if (g_9460)
            done = fn_17_1174(0);
        else
            done = 1;
        break;
    case 11:
        done = fn_17_20fa(0, 0, 0);
        break;
    case 18:
        if (!g_05ac) {
            g_05ac = g_1e50;
            fn_17_6036();
        }
        return;
    }
    if (g_1876 && g_1876 < g_1e50) {
        g_1876 = 0;
        done = 1;
    }
    if (done) {
        g_93aa++;
        fn_17_03b2();
    }
}

/* @addr 17:8910 */
int far fn_17_8910(int a, HWND hwnd, int b)
{
    char buf[120];
    int i;
    int k;
    int unused;
    int count;
    int j;

    switch (a) {
    case 0:
        count = 0;
        for (i = 0; i <= g_9316; i++) {
            if (g_1e30[i].f18 == 0 && g_7092[i].f_0ea != 0)
                count += 2;
        }
        break;
    case 2:
        count = 1;
        if (g_92fe != 0)
            count = 2;
        for (k = 0; k < 2; k++) {
            if (g_4ee0[k] != 0)
                count++;
        }
        break;
    case 3:
        count = 1;
        if (g_92f0 == 0)
            break;
    case 1:
    case 6:
        count = 2;
        break;
    case 4:
        count = 9;
        break;
    case 5:
        count = 3;
        break;
    case 7:
        count = 7;
        break;
    case 8:
        if (g_948c != 0) {
            count = 1;
            break;
        }
        fn_06_6576();
        count = g_94c6 + 1;
        break;
    case 9:
        count = 0;
        for (i = 1; i < 27; i++) {
            if (fn_10_5586(i))
                count++;
        }
        break;
    }
    if (hwnd == 0)
        return count;
    for (i = 0; i < count; i++) {
        j = i;
        if (a == 0)
            i++;
        fn_17_8a92(j, a, buf);
        fn_17_8f1e(j, a, b, hwnd, buf);
    }
    return count;
}

/* @addr 17:8f1e */
void far fn_17_8f1e(int a, int b, int c, HWND hwnd, LPSTR buf)
{
    char s1[120];
    char s2[110];
    int i;

    if (hwnd == 0)
        return;
    if (g_948c != 0 && b == 8 && a != 0)
        return;
    if (c != 0) {
        if (a == -1) {
            a = 0;
            LoadString(g_9212, b + 800, s2, 110);
            lstrcpy(s1, s2);
            lstrcat(s1, " ");
            lstrcat(s1, buf);
        } else {
            lstrcpy(s1, buf);
            lstrcat(s1, " - ");
            LoadString(g_9212, b + 800, s2, 110);
            lstrcat(s1, s2);
        }
        lstrcat(s1, "\t\t\t\t\t\t\t");
        lstrcat(s1, " ");
        s1[lstrlen(s1) - 1] = b + '1';
        lstrcat(s1, " ");
        s1[lstrlen(s1) - 1] = a + '0';
        SendMessage(hwnd, 0x401, 0, (LPARAM)(LPSTR)s1);
    } else {
        if (hwnd == g_9484) {
            lstrcpy(s1, buf);
            for (i = 0; i < 28; i++)
                lstrcat(s1, " ");
            s1[lstrlen(s1) - 1] = b + '1';
            lstrcat(s1, " ");
            s1[lstrlen(s1) - 1] = a + '0';
        } else {
            lstrcpy(s1, buf);
        }
        SendMessage(hwnd, 0x403, 0, (LPARAM)(LPSTR)s1);
    }
}

/* @addr 17:8a92 */
void far fn_17_8a92(int idx, int kind, LPSTR out)
{
    char s1[110];
    char s2[110];
    int i;
    int t;
    int n;
    int unused;

    n = 0;
    switch (kind) {
    case 0:
        for (i = 0; i <= g_9316; i++) {
            if (g_1e30[i].f18 == 0 && g_7092[i].f_0ea != 0) {
                if (n == idx) {
                    fn_03_1542(0, 14, i, s1, 0);
                    lstrcpy(s2, s1);
                    lstrcat(s2, " - ");
                    fn_17_8e60(i, s1);
                    lstrcat(s2, s1);
                    lstrcpy(s1, s2);
                }
                n += 2;
            }
        }
        break;
    case 1:
        if (idx == 0) {
            LoadString(g_9212, 0x30e3, s1, 110);
        } else {
            switch (g_9214) {
            case 0:
                LoadString(g_9212, 0x335, s1, 110);
                break;
            case 1:
                LoadString(g_9212, 0xeb, s1, 110);
                break;
            case 3:
                LoadString(g_9212, 0xef, s1, 110);
                break;
            case 2:
                LoadString(g_9212, 0xec, s1, 110);
                break;
            case 4:
                LoadString(g_9212, 0xf0, s1, 110);
                break;
            }
            fn_11_3fd4(s1, 1);
        }
        break;
    case 2:
        if (idx == 0) {
            LoadString(g_9212, 0x27a9, s1, 110);
        } else if (g_92fe != 0 && idx == 1) {
            LoadString(g_9212, 0x27ba, s1, 110);
        } else {
            t = idx - 1;
            if (g_92fe != 0)
                t--;
            if (g_4ee0[t] != 0)
                fn_10_a332(s1, (char *)(g_4d92[g_4ed4[t]].f10 + 10000), 1);
        }
        break;
    case 3:
        if (idx == 0) {
            LoadString(g_9212, 0x338, s1, 110);
        } else {
            LoadString(g_9212, 0x9e2, s1, 110);
            fn_11_3fd4(s1, 1);
        }
        break;
    case 4:
        if (idx == 0)
            LoadString(g_9212, 0x140, s1, 110);
        else
            fn_13_218a(idx - 1, s1);
        break;
    case 5:
        LoadString(g_9212, idx + 0x492, s1, 110);
        break;
    case 6:
        if (idx == 0)
            LoadString(g_9212, 0x4ae, s1, 110);
        else
            LoadString(g_9212, 0x30e3, s1, 110);
        break;
    case 7:
        switch (idx) {
        case 0:
            LoadString(g_9212, 0x2e1, s1, 110);
            break;
        case 1:
            LoadString(g_9212, 0x2e4, s1, 110);
            break;
        case 2:
            LoadString(g_9212, 0x2e4, s1, 110);
            LoadString(g_9212, 0x841, s2, 110);
            lstrcat(s1, s2);
            break;
        case 3:
            LoadString(g_9212, 0x2e5, s1, 110);
            break;
        case 4:
            LoadString(g_9212, 0x2e5, s1, 110);
            LoadString(g_9212, 0x841, s2, 110);
            lstrcat(s1, s2);
            break;
        case 5:
            LoadString(g_9212, 0x2e6, s1, 110);
            break;
        case 6:
            LoadString(g_9212, 0x2e6, s1, 110);
            LoadString(g_9212, 0x841, s2, 110);
            lstrcat(s1, s2);
            break;
        }
        break;
    case 8:
        if (idx == 0) {
            LoadString(g_9212, 0x80f, s1, 110);
            lstrcat(s1, "S");
        } else {
            fn_14_3eda();
            lstrcpy(s1, "");
            fn_17_7ba6(idx, s2);
            lstrcat(s1, s2);
            lstrcat(s1, " - ");
            lstrcat(s1, g_6af8[idx - 1].name);
            lstrcat(s1, " - ");
            lstrcat(s1, g_6e20[g_6af8[idx - 1].f22].name);
            fn_14_4074();
        }
        break;
    case 9:
        for (i = 1; i < 27; i++) {
            if (fn_10_5586(i)) {
                if (n == idx)
                    LoadString(g_9212, i + 0xba, s1, 110);
                n++;
            }
        }
        break;
    }
    lstrcpy(out, s1);
}

/* @addr 17:4068 */
void far fn_17_4068(int i, LPSTR buf)
{
    char unused[60];
    int saved;
    int id;

    saved = g_7092[i].f_024;
    g_7092[i].f_024 = 100;
    fn_13_33d6(i);
    g_7092[i].f_024 = saved;
    if (g_7092[i].f_0d6 > 32600)
        id = 0x2c5;
    else if (g_7092[i].f_0d6 > 25000)
        id = 0x2c6;
    else if (g_7092[i].f_0d6 > g_0956[10] * 100)
        id = 0x2c7;
    else if (g_7092[i].f_0d6 > g_0956[9] * 100)
        id = 0x2c8;
    else if (g_7092[i].f_0d6 > g_0956[8] * 100)
        id = 0x2c9;
    else if (g_7092[i].f_0d6 > g_0956[7] * 100)
        id = 0x2ca;
    else if (g_7092[i].f_0d6 > g_0956[6] * 100)
        id = 0x2cb;
    else if (g_7092[i].f_0d6 > g_0956[5] * 100)
        id = 0x2cc;
    else if (g_7092[i].f_0d6 > g_0956[4] * 100)
        id = 0x2cd;
    else if (g_7092[i].f_0d6 > g_0956[3] * 100)
        id = 0x2ce;
    else if (g_7092[i].f_0d6 > g_0956[2] * 100)
        id = 0x2cf;
    else if (g_7092[i].f_0d6 > g_0956[1] * 100)
        id = 0x2d0;
    else if (g_7092[i].f_0d6 > g_0956[0] * 100)
        id = 0x2d1;
    else
        id = 0x2d2;
    fn_10_a332(buf, "n", 1, i == g_9646, i != g_9646, id);
}

/* @addr 17:5008 */
void far fn_17_5008(void)
{
    HFONT font;
    HFONT old;
    COLORREF oldbk;
    COLORREF oldtc;
    char buf[150];
    int unused;
    int x;
    int unused2;
    int unused3;
    int t;

    font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    old = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    if (g_93aa == 2) {
        if (g_9460 != 0 && (g_9468 + 1) % 2 != 0)
            SendMessage(g_9482, CB_GETLBTEXT, g_9468, (LPARAM)(LPSTR)buf);
        else
        {
            if (g_9460)
                t = (g_9468 - 1) / 2;
            else
                t = g_9322;
            fn_09_955c(t + 0x2e4, buf);
        }
    } else if (g_93aa == 0x10 && g_9468 == 0) {
        fn_09_955c(0x39d, buf);
    } else {
        SendMessage(g_9482, CB_GETLBTEXT, g_9468, (LPARAM)(LPSTR)buf);
    }
    if (g_93aa == 0x10 && g_9468 != 0)
        fn_17_7c2a();
    oldtc = SetTextColor(g_13dc, PALETTERGB(0, 0xd6, 0xff));
    if (g_93aa == 2 && (g_9460 == 0 || (g_9468 + 1) % 2 == 0))
        x = g_6088 - 280;
    else if (g_93aa == 2)
        x = 20;
    else
        x = 35;
    TextOut(g_13dc, x, g_6086 + 20, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtc);
    SelectObject(g_13dc, old);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_7c2a(void)
{
}

/* @addr 17:8270 */
void far fn_17_8270(void)
{
    int unused1;
    int unused2;
    HFILE fh;
    char path[110];
    char unused3[30];
    DWORD size;
    long unused4;
    HGLOBAL h;
    LPSTR p;
    OFSTRUCT of;
    int r;

    lstrcpy(g_6078, "");
    if (g_9468 != g_93a2) {
        lstrcpy(path, g_9078);
        if (g_6af8[g_9468 - 1].f30 == 0)
            lstrcat(path, g_96b8);
        else
            lstrcat(path, g_96c5);
        lstrcat(path, g_6af8[g_9468 - 1].f26);
        switch (g_6af8[g_9468 - 1].f30) {
        case 0:
            lstrcat(path, ".sav");
            break;
        case 1:
            lstrcat(path, ".ded");
            break;
        case 2:
            lstrcat(path, ".don");
            break;
        }
        if ((fh = OpenFile(path, &of, 0)) == -1)
            return;
    }
    h = GlobalAlloc(GHND, 0x1a9L);
    GlobalLock(h);
    size = GlobalSize(h);
    GlobalUnlock(h);
    h = GlobalReAlloc(h, size, GHND);
    p = GlobalLock(h);
    if (g_9468 != g_93a2) {
        r = fn_14_4006(fh, p, size);
        _lclose(fh);
    } else {
        fn_06_8eea(p);
    }
    fn_10_a118(p, g_6078);
    if (g_9468 != g_93a2)
        _lclose(fh);
    GlobalUnlock(h);
    GlobalFree(h);
    fn_11_3fd4(g_6078, 1);
}

/* Owner-drawn list item with tab-positioned columns [inferred]. */
/* @addr 17:90d2 */
void far pascal fn_17_90d2(DRAWITEMSTRUCT far *dis)
{
    RECT rc;
    HBRUSH br;
    HFONT oldf;
    char text[240];
    char buf[140];
    int i;
    int n;
    int x;
    int y;
    int prev;
    COLORREF oldtc;

    oldtc = GetTextColor(dis->hDC);
    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_SELECTED)
        br = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
    else
        br = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    SendMessage(dis->hwndItem, LB_GETTEXT, dis->itemID, (LPARAM)(LPSTR)text);
    FillRect(dis->hDC, &rc, br);
    oldf = SelectObject(dis->hDC, g_6094[0]);
    if (dis->itemState & ODS_SELECTED)
        SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
    else
        SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
    SetBkMode(dis->hDC, TRANSPARENT);
    prev = x = 2;
    n = i = y = 0;
    while (lstrlen(text) > i) {
        if (text[i] == '\t') {
            buf[n] = 0;
            TextOut(dis->hDC, x + rc.left, y + rc.top, buf, n);
            x = (text[i + 1] - '0') * 100 + (text[i + 2] - '0') * 10 + (text[i + 3] - '0') - 6;
            if (x < prev)
                y = 14;
            prev = x;
            i += 4;
            n = 0;
        } else {
            buf[n] = text[i];
            i++;
            n++;
        }
    }
    if (n != 0) {
        buf[n] = 0;
        TextOut(dis->hDC, x + rc.left, y + rc.top, buf, n);
    }
    SelectObject(dis->hDC, oldf);
    DeleteObject(br);
    SetTextColor(dis->hDC, oldtc);
}

/* @addr 17:7324 */
void far fn_17_7324(void)
{
    int save;
    int kind;
    int idx;
    int t;
    int k;
    char unused[82];
    int r;

    g_93aa = 11;
    g_9462 = -2;
    g_9464 = g_9646;
    if (g_93c6 == 6) {
        g_9466 = 8;
        fn_06_6576();
        g_9468 = g_93a2;
    } else if (g_93c6 == 5) {
        g_9466 = 8;
        g_9468 = 0;
    } else if (g_93c6 == 2) {
        g_9466 = 0;
        g_9468 = fn_17_75c6(g_9646);
    } else if (g_93c6 == 3) {
        g_9466 = 0;
        g_9468 = fn_17_75c6(g_9646) + 1;
    } else if (g_93c6 == 0) {
        g_9466 = 9;
        t = g_7092[g_9646].f_0b6[g_7092[g_9646].f_016];
        g_9468 = fn_17_7526(t);
        r = fn_17_7526(-1);
        if (t == 0) {
            if (r != 0) {
                g_9468 = 0;
            } else {
                g_9466 = 0;
                g_9468 = fn_17_75c6(g_9646);
            }
        }
    } else {
        if (g_0a76 == 3) {
            kind = g_6e72;
            idx = g_6e70;
        } else if (g_0a76 == 2) {
            kind = g_6e54;
            idx = g_6e52;
        } else {
            kind = 14;
            idx = g_9646;
        }
        if (g_93c6 == 4 && (kind == 0 || kind == 7)) {
            kind = 14;
            idx = g_9646;
        }
        if (g_094e != 0 && g_93c6 == 4) {
            g_9466 = 7;
            g_9468 = (g_094e - 1) / 4 * 2 + 1;
        } else if (kind == 14) {
            g_9466 = 0;
            g_9468 = fn_17_75c6(idx);
        } else if (kind == 0) {
            g_9466 = 1;
            g_9468 = 0;
        } else if (kind == 9) {
            g_9466 = 2;
            g_9468 = 1;
        } else if (kind == 2) {
            g_9466 = 3;
            g_9468 = 1;
        } else if (kind == 7) {
            if (g_0a76 == 2) {
                g_9466 = 3;
                g_9468 = 0;
            }
        } else if (kind == 8) {
            if (g_3d6c[idx].f00 == 2) {
                g_9466 = 2;
                g_9468 = 1;
                if (g_92fe != 0)
                    g_9468 = 2;
                for (k = 0; k < 2; k++) {
                    if (g_4d92[g_4ed4[k]].f10 == g_4d92[idx].f10)
                        break;
                    g_9468++;
                }
            }
        }
    }
    save = g_9468;
    fn_17_646e();
    fn_17_65da();
    g_9468 = save;
    fn_17_67e6();
}

/* @addr 17:193c */
int far fn_17_193c(int reset)
{
    int unused;
    int k;
    HGDIOBJ old;

    if (reset) {
        g_18b0 = 0;
        g_9474 = 0;
        return 0;
    }
    if (g_18b0 != 0) {
        if (g_18b0 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        g_5000 = g_6088 - 320;
        g_5002 = g_6086 + 30;
        fn_17_30b0(g_93aa, 0x1194L);
        fn_17_55e2(-1);
        g_18b4 = k = 0;
        old = SelectObject(g_13dc, g_5780[0]);
        SetStretchBltMode(g_13dc, 2);
        fn_10_9962(0, g_13dc, g_6088 / 2 - 200, g_5002 + 50, 13, 13, g_39e8[0],
                   g_1e00->f24, g_1e00->f24, g_1e00->f22, g_1e00->f22, 0xc000caL);
        SelectObject(g_13dc, old);
        break;
    case 1:
        fn_17_55e2(-1);
        g_18b4++;
        if (g_18b4 > 49)
            g_18b4 = 0;
        if (g_18b4 < 25)
            k = g_18b4;
        else
            k = 49 - g_18b4;
        old = SelectObject(g_13dc, g_5780[k / 5]);
        SetStretchBltMode(g_13dc, 2);
        fn_10_9962(0, g_13dc, g_6088 / 2 - 200, g_5002 + 50, 13, 13, g_39e8[0],
                   g_1e00->f24, g_1e00->f24, g_1e00->f22, g_1e00->f22, 0xc000caL);
        SelectObject(g_13dc, old);
        if (g_9460 != 0 && g_9474 != 0) {
            g_9474 = 0;
            g_5000 = g_6088 - 320;
            g_5002 = g_6086 + 30;
            fn_17_2c5a(1, 1);
        } else if (fn_17_2c5a(0, 0) == 2 && g_9460 == 0) {
            g_9462++;
        }
        break;
    case 2:
        g_18b0 = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* Loads a text resource (type 5000) into the g_6078 buffer [inferred]. */
/* @addr 17:30b0 */
void far fn_17_30b0(int id, long v)
{
    int flag;
    int i;
    int size;
    HRSRC hres;
    HGLOBAL hmem;
    LPSTR p;

    fn_17_306e();
    if (g_90f4 == 2) {
        g_9478 = 1;
        id = 2;
    } else {
        switch (g_93aa) {
        case 2: case 3:
        case 8: case 9: case 10: case 11: case 12: case 13:
        case 15: case 16: case 17:
            g_9478 = 1;
            break;
        default:
            g_9478 = 0;
            break;
        }
    }
    g_948e = GlobalAlloc(GHND, 2000L);
    g_6078 = GlobalLock(g_948e);
    switch (id) {
    case 8:
        fn_17_7614(0);
        break;
    case 9:
        fn_17_7614(1);
        break;
    case 402:
        fn_17_76e4();
        break;
    case 12:
        fn_17_4204();
        break;
    case 16:
        if (g_9468 == 0)
            fn_17_7b44();
        else
            fn_17_8270();
        break;
    case 2:
        fn_09_6fee();
        break;
    case 11:
        if (g_9460 != 0 && !(g_9468 & 1))
            flag = 1;
        else
            flag = 0;
        fn_17_32de(flag);
        break;
    default:
        if (id == 3) {
            switch (g_9214) {
            case 0:
                id = 0x12d;
                break;
            case 1:
                id = 0xb5;
                break;
            case 2:
                id = 0xb6;
                break;
            case 3:
                id = 0xb4;
                break;
            case 4:
                id = 0xb7;
                break;
            }
        } else if (id < 0x6e) {
            if (id == 0xf)
                id = g_9468 + 0x140;
            else if (id == 0x11)
                id = 0x89;
            else if (id == 4)
                id = 0x12e;
            else if (id == 5)
                id = 0x12f;
            else if (id == 7)
                id = 0x131;
            else if (id == 6)
                id = 0x130;
            else
                id += 0x12b;
        }
        hres = FindResource(g_9212, MAKEINTRESOURCE(id), MAKEINTRESOURCE(5000));
        size = SizeofResource(g_9212, hres);
        hmem = LoadResource(g_9212, hres);
        p = LockResource(hmem);
        for (i = 0; i < size; i++)
            g_6078[i] = p[i];
        if (hmem) {
            if (p) {
                GlobalUnlock(hmem);
                p = 0;
            }
            FreeResource(hmem);
        }
        break;
    }
    g_6090 = v;
    fn_17_2c5a(1, 0);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_17_76e4(void)
{
}

/* @addr 17:7088 */
int far fn_17_7088(int a)
{
    int k;
    int i;
    int count;
    int n;
    int t;

    count = 0;
    switch (g_9466) {
    case 1:
        if (g_9468 == 0) {
            count = 1;
            fn_17_72aa(a, 1, 6);
        }
        break;
    case 3:
        if (g_9468 == 1) {
            count = 1;
            fn_17_72aa(a, 1, 6);
        }
        break;
    case 0:
        count = g_7092[g_9464].f_0c9 + 1;
        n = g_96f0[g_7092[g_9464].f_04c].f1a;
        fn_17_72aa(a, n + 1, 4);
        fn_17_72aa(a, 0, 8);
        for (i = 1; i < g_7092[g_9464].f_0c9; i++) {
            k = g_7092[g_9464].f_0b6[i];
            fn_17_72aa(a, fn_17_7526(k), 9);
        }
        break;
    case 4:
        if (g_93aa == 13) {
            for (k = 0; k <= g_9316; k++) {
                if (g_1e30[k].f18 == 0 && g_7092[k].f_0ea != 0 &&
                    g_96f0[g_7092[k].f_04c].f1a == g_9468 - 1) {
                    count++;
                    fn_17_72aa(a, fn_17_75c6(k), 0);
                }
            }
            if (g_9468 == 8) {
                count++;
                fn_17_72aa(a, 0, 6);
            }
        }
        break;
    case 6:
        switch (g_9468) {
        case 0:
            count = 1;
            fn_17_72aa(a, 8, 4);
            break;
        case 1:
            count = 1;
            fn_17_72aa(a, 0, 1);
            if (g_92f0 != 0) {
                count = 2;
                fn_17_72aa(a, 1, 3);
            }
            break;
        }
        break;
    case 8:
        if (g_93a2 == g_9468) {
            count = 1;
            fn_17_72aa(a, fn_17_75c6(g_9646), 0);
        }
        break;
    case 9:
        t = g_9472;
        for (k = 0; k <= g_9316; k++) {
            if (g_1e30[k].f18 == 0 && g_7092[k].f_0ea != 0) {
                for (i = 0; i < g_7092[k].f_0c9; i++) {
                    if (g_7092[k].f_0b6[i] == t) {
                        count++;
                        fn_17_72aa(a, fn_17_75c6(k), 0);
                        break;
                    }
                }
            }
        }
        break;
    }
    return count;
}

/* Draws the header of the pilot panel for object i [names]. */
/* @addr 17:4354 */
void far pilot_panel_header(int i)
{
    HFONT font;
    HFONT old;
    COLORREF oldbk;
    COLORREF oldtc;
    char buf[80];
    char unused[60];
    int mood;
    int rel;
    int flag;

    if (i != g_9646) {
        rel = fn_13_2688(g_9646, g_9464);
        if (rel < -80)
            mood = 0;
        else if (rel < 80)
            mood = 1;
        else
            mood = 2;
    }
    font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    old = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    if (i == g_9646) {
        fn_09_955c(0x20b, buf);
        oldtc = SetTextColor(g_13dc, PALETTERGB(0, 0xd6, 0xff));
    } else {
        switch (mood) {
        case 0:
            oldtc = SetTextColor(g_13dc, PALETTERGB(0xff, 0x80, 0));
            break;
        case 1:
            oldtc = SetTextColor(g_13dc, PALETTERGB(0xd2, 0xd2, 0xd2));
            break;
        case 2:
            oldtc = SetTextColor(g_13dc, PALETTERGB(0, 0xaa, 0xff));
            break;
        }
        fn_10_a332(buf, "\r\x03", 1, mood + 0x245);
    }
    TextOut(g_13dc, g_5000 - 330, g_5002, buf, lstrlen(buf));
    fn_10_a332(buf, "\x03", 1, i == g_9646, i != g_9646,
               g_96f0[g_7092[g_9464].f_04c].f1a == g_96f0[g_7092[g_9646].f_04c].f1a,
               0x210020fL);
    TextOut(g_13dc, g_5000 - 330, g_5002 + 20, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtc);
    SelectObject(g_13dc, old);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
    if (g_9460 != 0 && !(g_9468 & 1))
        flag = 1;
    else
        flag = 0;
    ship_status_lines(flag);
}

/* Draws the ship status lines of the pilot panel [names]. */
/* @addr 17:3ba6 */
void far ship_status_lines(int flag)
{
    HFONT font;
    HFONT old;
    COLORREF oldbk;
    COLORREF oldtc;
    char tmp[50];
    char buf[90];
    POINT pt;
    int i;

    font = CreateFont(13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    old = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    oldtc = SetTextColor(g_13dc, RGB(0, 0xff, 0xff));
    pt.x = g_5000 - 330;
    pt.y = g_5002 + 90;
    if (flag) {
        for (i = 0; i < 3; i++) {
            fn_09_955c(i + 0x348, buf);
            lstrcat(buf, ": ");
            fn_06_0f1a((&g_7092[g_9464].f_024)[i], tmp);
            lstrcat(buf, tmp);
            lstrcat(buf, "%");
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            pt.y += 18;
        }
        if (g_96f0[g_7092[g_9464].f_04c].f0a != -1) {
            fn_09_955c(0x34b, buf);
            lstrcat(buf, ": ");
            fn_06_0f1a(g_7092[g_9464].f_02a, tmp);
            lstrcat(buf, tmp);
            lstrcat(buf, "%");
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
        }
        fn_17_4068(g_9464, buf);
        pt.y += 36;
        TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
    } else {
        pt.y += 54;
        lstrcpy(buf, "");
        if (g_9464 != g_9646) {
            if (g_96f0[g_7092[g_9464].f_04c].f1a == g_96f0[g_7092[g_9646].f_04c].f1a) {
                fn_09_9580(0x147, buf);
            } else {
                fn_03_1542(0, 14, g_9464, tmp, 3);
                lstrcat(buf, tmp);
            }
            fn_09_9580(0x136, buf);
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            lstrcpy(buf, "");
        } else {
            pt.y += 18;
            if (g_95bc != 0 && (g_91f8 == 0 || (g_91f8 < 2 && g_9460 != 0))) {
                fn_09_955c(0x803, buf);
                TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
                lstrcpy(buf, "");
                pt.y += 18;
                fn_09_955c(0x804, buf);
                lstrcat(buf, ". ");
                TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
                lstrcpy(buf, "");
            } else {
                fn_09_955c(0x805, buf);
                TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            }
        }
        pt.y += 18;
        if (g_95bc == 0 || g_9464 != g_9646 || g_91f8 > 1 || (g_91f8 != 0 && g_9460 == 0)) {
            fn_10_a332(buf, "\x80\x1a\x06", 1, g_7092[g_9464].f_05b + 0xf6,
                       g_7092[g_9464].f_05b > 2, 0x21e021dL);
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            pt.y += 18;
            fn_10_a332(buf, "\xc0" "E\x04", 1, g_7092[g_9464].f_05c + 0xfa,
                       g_7092[g_9464].f_05c > 2, 0x21e021dL);
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            pt.y += 18;
        }
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtc);
    SelectObject(g_13dc, old);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
}

/* @addr 17:03b2 */
void far fn_17_03b2(void)
{
    int k;

    fn_10_744c(0x6e);
    g_9462 = 0;
    if (g_93aa >= 18 && g_9134 == 0)
        g_93aa = 1;
    PatBlt(g_13dc, g_6084, g_6086, g_6088 - g_6084, g_608a - g_6086, BLACKNESS);
    switch (g_93aa) {
    case 1:
        fn_17_0600(1);
        break;
    case 3:
        if (g_91f8 == 0 || g_9460 != 0)
            fn_17_0d22(1);
        break;
    case 4:
        if ((g_91f8 == 0 && g_92f2 != 0) || g_9460 != 0)
            fn_17_1b3e(1, 3);
        break;
    case 5:
        if ((g_094e == 0 && g_91f8 == 1) || g_9460 != 0)
            fn_17_1b3e(1, 7);
        break;
    case 6:
        if (g_92fe != 0)
            fn_17_1b3e(1, 9);
        break;
    case 7:
        if ((g_91f8 == 1 || g_9460 != 0) && g_92f0 != 0)
            fn_17_193c(1);
        break;
    case 10:
        if (g_9460 != 0 && fn_10_5586(g_9472))
            fn_17_16cc(1, g_9472);
        break;
    case 8:
        if (g_4ee0[0] != 0) {
            g_91f8++;
            fn_09_6624();
            g_91f8--;
            for (k = 0; k < g_9416; k++)
                if (g_3d6c[k].f14 == g_4ed4[0])
                    break;
            g_946e = k;
            fn_17_1b3e(1, 8);
        }
        break;
    case 9:
        if (g_4ee0[1] != 0) {
            g_91f8++;
            fn_09_6624();
            g_91f8--;
            for (k = 0; k < g_9416; k++)
                if (g_3d6c[k].f14 == g_4ed4[1])
                    break;
            g_946e = k;
            fn_17_1b3e(1, 8);
        }
        break;
    case 12:
        if (g_9460 != 0)
            fn_17_108c(1);
        break;
    case 14:
        if (g_9460 != 0)
            fn_17_1260(1);
        break;
    case 2:
        if (g_9460 != 0 || g_094e != 0)
            fn_17_13ca(1);
        if (g_9488) {
            ShowWindow(g_9488, SW_HIDE);
            ShowWindow(g_9488, SW_SHOW);
        }
        break;
    case 15:
    case 17:
        if (g_9460 != 0)
            fn_17_12f6(1);
        break;
    case 16:
        if (g_9460 != 0)
            fn_17_15c6(1);
        if (g_9488) {
            ShowWindow(g_9488, SW_HIDE);
            ShowWindow(g_9488, SW_SHOW);
        }
        break;
    case 13:
        if (g_9460 != 0)
            fn_17_1174(1);
        break;
    case 11:
        fn_17_20fa(1, 0, 0);
        break;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_17_0600(int reset)
{
    return 0;
}

/* Contact animation step (portrait zoom in/out) [inferred]. */
/* @addr 17:0d22 */
int far fn_17_0d22(int reset)
{
    POINT pt;
    int sz;
    int b;
    int a;
    int r;
    int unused[2];

    if (reset) {
        fn_10_744c(0x13);
        g_1886 = 0;
        g_188a = 1;
    }
    if (g_1886) {
        if (g_1886 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        b = g_1e08->f22;
        sz = min(g_188a * 36 / 20, 72);
        if (sz < 72)
            g_188e = g_188a * 2;
        pt.x = g_608c / 2 - sz / 2 - g_188e - 30;
        pt.y = (g_6086 - g_608a) / 2 - sz / 2 + g_608a;
        a = g_1e08->f24;
        SetStretchBltMode(g_13dc, 3);
        fn_10_9962(0, g_13dc, pt.x, pt.y, sz, sz, g_39f0, a, a, b, b, SRCCOPY);
        PatBlt(g_13dc, sz + pt.x, pt.y, 2, sz, BLACKNESS);
        g_188a++;
        if (g_188a > 40) {
            g_9462++;
            g_5000 = sz + pt.x + 60;
            g_5002 = pt.y - 17;
            fn_17_30b0(g_93aa, 0x1194L);
        }
        break;
    case 1:
        if (g_9460 != 0 && g_9474 != 0) {
            g_9474 = 0;
            a = g_1e08->f24;
            b = g_1e08->f22;
            pt.y = (g_6086 - g_608a) / 2 + g_608a - 36;
            pt.x = g_608c / 2 - 146;
            g_5000 = pt.x + 132;
            g_5002 = pt.y - 17;
            fn_17_2c5a(1, 1);
            SetStretchBltMode(g_13dc, 3);
            fn_10_9962(0, g_13dc, pt.x, pt.y, 72, 72, g_39f0, a, a, b, b, SRCCOPY);
        } else {
            r = fn_17_2c5a(0, 0);
            if (r == 1) {
                fn_10_3a2e();
                fn_10_3ea2();
            } else if (r == 2 && g_9460 == 0) {
                g_188c = g_188a = 40;
                fn_10_744c(0x15);
                g_9462++;
            }
        }
        break;
    case 2:
        b = g_1e08->f22;
        sz = min(g_188c * 36 / 20, 72);
        a = g_1e08->f24;
        if (sz < 72)
            g_188e = g_188a * 2;
        pt.x = g_608c / 2 - sz / 2 - g_188e - 30;
        pt.y = (g_6086 - g_608a) / 2 - sz / 2 + g_608a;
        SetStretchBltMode(g_13dc, 3);
        fn_10_9962(0, g_13dc, pt.x, pt.y, sz, sz, g_39f0, a - 3, a - 3, b + 6, b + 6, SRCCOPY);
        PatBlt(g_13dc, pt.x - 10, pt.y, 10, sz, BLACKNESS);
        PatBlt(g_13dc, pt.x - 20, pt.y - 20, sz + 20, 20, BLACKNESS);
        g_188c = g_188a;
        g_188a -= 2;
        if (g_188a <= 7) {
            PatBlt(g_13dc, pt.x - 4, pt.y - 4, sz + 8, sz + 8, BLACKNESS);
            g_1886 = g_1e50 + 1000;
        }
        break;
    }
    g_9474 = 0;
    return 0;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_17_1b3e(int reset, int kind)
{
    return 0;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_17_20fa(int reset, int a, int b)
{
    return 0;
}

/* @addr 17:16cc */
int far fn_17_16cc(int reset, int n)
{
    int r;
    HGDIOBJ old;
    HDC hdc;
    BITMAP bm;
    HPALETTE oldpal;

    if (reset) {
        g_18a8 = 0;
        g_9474 = 0;
        return 0;
    }
    if (g_18a8 != 0) {
        if (g_18a8 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        g_9462++;
        g_5000 = g_6088 - 280;
        g_5002 = g_6086 + 60;
        fn_17_30b0(n + 0x6d, 0x1194L);
        fn_17_55e2(n);
        if (g_9490) {
            DeleteObject(g_9490);
            g_9490 = 0;
        }
        g_9490 = fn_11_2ff6(n);
        GetObject(g_9490, sizeof(BITMAP), &bm);
        g_18ac.x = bm.bmWidth;
        g_18ac.y = bm.bmHeight;
        hdc = CreateCompatibleDC(g_13dc);
        old = SelectObject(hdc, g_9490);
        oldpal = SelectPalette(hdc, g_920e, 0);
        SetStretchBltMode(g_13dc, 3);
        fn_10_9962(0, g_13dc, g_6088 / 2 - g_18ac.x - 200, g_5002 + 50, g_18ac.x * 2, g_18ac.y * 2,
                   hdc, 0, 0, g_18ac.x, g_18ac.y, SRCCOPY);
        SelectPalette(hdc, oldpal, 0);
        SelectObject(hdc, old);
        DeleteDC(hdc);
        break;
    case 1:
        if (g_9460 != 0 && g_9474 != 0) {
            fn_17_55e2(n);
            hdc = CreateCompatibleDC(g_13dc);
            old = SelectObject(hdc, g_9490);
            oldpal = SelectPalette(hdc, g_920e, 0);
            SetStretchBltMode(g_13dc, 3);
            fn_10_9962(0, g_13dc, g_6088 / 2 - g_18ac.x - 200, g_5002 + 50, g_18ac.x * 2, g_18ac.y * 2,
                       hdc, 0, 0, g_18ac.x, g_18ac.y, SRCCOPY);
            SelectPalette(hdc, oldpal, 0);
            SelectObject(hdc, old);
            DeleteDC(hdc);
            g_9474 = 0;
            g_5000 = g_6088 - 280;
            g_5002 = g_6086 + 60;
            fn_17_2c5a(1, 1);
        } else {
            r = fn_17_2c5a(0, 0);
            if (r == 2 && g_9460 == 0)
                g_9462++;
        }
        break;
    case 2:
        g_18a8 = g_1e50 + 1000;
        break;
    }
    g_9474 = 0;
    return 0;
}

/* WM_INITDIALOG handler of a dialog with list 0x199 [inferred]. */
/* @addr 17:8572 */
void far fn_17_8572(HWND hDlg)
{
    int unused0;
    char s1[110];
    char s2[110];
    int i;
    int w;
    int h;
    int unused1;
    int unused2;
    int y;
    RECT rc;
    int unused3;
    int unused4;
    int unused5;
    int unused6;

    g_948c = hDlg;
    fn_10_744c(0x13);
    GetWindowRect(hDlg, &rc);
    w = rc.right - rc.left;
    h = rc.bottom - rc.top;
    y = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2 - 150;
    if (y < 50)
        y = 50;
    MoveWindow(hDlg, GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2 - 200, y, w, h, TRUE);
    SendMessage(GetDlgItem(hDlg, 0x199), WM_SETFONT, g_6094[0], 1L);
    SendMessage(GetDlgItem(hDlg, 0x198), WM_SETFONT, g_6094[0], 1L);
    SendMessage(GetDlgItem(hDlg, 0x195), WM_SETFONT, g_6094[0], 1L);
    SendMessage(GetDlgItem(hDlg, 1), WM_SETFONT, g_6094[1], 1L);
    SendMessage(GetDlgItem(hDlg, 2), WM_SETFONT, g_6094[1], 1L);
    for (i = 0; i < g_9470; i++) {
        LoadString(g_9212, 0x840, s1, 110);
        fn_17_8f1e(-1, i, 1, GetDlgItem(hDlg, 0x199), s1);
        fn_17_8910(i, GetDlgItem(hDlg, 0x199), 1);
    }
    for (i = 0; i < 9; i++) {
        LoadString(g_9212, i + 0x52b, s1, 110);
        fn_17_8f1e(0, 5, 1, GetDlgItem(hDlg, 0x199), s1);
        LoadString(g_9212, i + 0x514, s1, 110);
        fn_17_8f1e(2, 5, 1, GetDlgItem(hDlg, 0x199), s1);
        LoadString(g_9212, i + 0x51d, s1, 110);
        fn_17_8f1e(2, 5, 1, GetDlgItem(hDlg, 0x199), s1);
        LoadString(g_9212, i + 0x534, s1, 110);
        fn_17_8f1e(1, 5, 1, GetDlgItem(hDlg, 0x199), s1);
    }
    SendMessage(g_9482, CB_GETLBTEXT, g_9468, (LPARAM)(LPSTR)s2);
    lstrcpy(s1, s2);
    lstrcat(s1, " - ");
    SendMessage(g_9480, CB_GETLBTEXT, g_9466, (LPARAM)(LPSTR)s2);
    lstrcat(s1, s2);
    SendMessage(GetDlgItem(hDlg, 0x199), 0x40d, -1, (LPARAM)(LPSTR)s1);
    SetFocus(GetDlgItem(hDlg, 0x195));
}

/* WM_CREATE handler of the contact window: layout and buttons [inferred]. */
/* @addr 17:6116 */
void far fn_17_6116(void)
{
    RECT rc;
    char buf[80];
    int i;
    HPALETTE old;

    GetClientRect(g_9460, &rc);
    g_6086 = 0;
    g_607c = g_6084 = 6;
    g_6080 = g_6088 = rc.right - g_6084;
    g_607e = g_608a = rc.bottom - 67;
    g_6082 = g_607e + 180;
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
    g_93ae = CreateRectRgn(g_6084, g_6086, g_6088, g_608a);
    for (i = 0; i < 9; i++) {
        if (g_947a[i]) {
            DestroyWindow(g_947a[i]);
            g_947a[i] = 0;
        }
    }
    g_6094[0] = CreateFont(12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    g_6094[1] = CreateFont(14, 7, 0, 0, 730, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    if (g_6088 > 670) {
        fn_09_955c(0x88a, buf);
        g_947a[1] = CreateWindow("button", buf, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                 9, rc.bottom - 30, 60, 23, g_9460, 0x65, g_8e66, NULL);
        fn_09_955c(0x88b, buf);
        g_947a[0] = CreateWindow("button", buf, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                 0x49, rc.bottom - 30, 60, 23, g_9460, 0x64, g_8e66, NULL);
        fn_09_955c(0x88c, buf);
        g_947a[2] = CreateWindow("button", buf, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                 0x89, rc.bottom - 30, 60, 23, g_9460, 0x66, g_8e66, NULL);
    } else {
        g_947a[1] = CreateWindow("button", "&?", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                 9, rc.bottom - 30, 30, 23, g_9460, 0x65, g_8e66, NULL);
        g_947a[0] = CreateWindow("button", "<<", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                 0x2b, rc.bottom - 30, 40, 23, g_9460, 0x64, g_8e66, NULL);
        g_947a[2] = CreateWindow("button", ">>", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                 0x57, rc.bottom - 30, 40, 23, g_9460, 0x66, g_8e66, NULL);
    }
    SendMessage(g_947a[0], WM_SETFONT, g_6094[1], 1L);
    SendMessage(g_947a[2], WM_SETFONT, g_6094[1], 1L);
    SendMessage(g_947a[1], WM_SETFONT, g_6094[1], 1L);
    fn_17_7324();
    fn_09_955c(0x88d, buf);
    g_947a[8] = CreateWindow("button", buf, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                             rc.right - 55, rc.bottom - 30, 45, 23, g_9460, 0x69, g_8e66, NULL);
    SendMessage(g_947a[8], WM_SETFONT, g_6094[1], 1L);
    if (g_9488)
        SetFocus(g_9488);
    else
        SetFocus(g_9482);
    g_608c = g_6088;
    g_608e = g_608a;
    g_1e50 = GetCurrentTime();
    g_13dc = GetDC(g_9460);
    if (g_920e)
        old = SelectPalette(g_13dc, g_920e, 0);
    fn_17_0000(0, 1);
    if (old)
        SelectPalette(g_13dc, old, 0);
    ReleaseDC(g_0016, g_13dc);
    g_13dc = 0;
}
