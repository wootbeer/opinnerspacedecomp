/* INSPACE.EXE segment 17 (selector 1080). */
#include "game.h"

#define SC(n) ((n) << g_9156 >> 1)     /* zoom scaling */

/* 17:306e */
void fn_17_306e(void)
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

/* 17:6036 */
void fn_17_6036(void)
{
    int16_t i;

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

/* 17:8e60 */
void fn_17_8e60(int16_t i, LPSTR buf)
{
    char tmp[20];
    int16_t a;
    int16_t b;
    int16_t c;

    if (g_7090[i].f_0d6 >= 0) {
        lstrcpy(buf, g_6e24[g_7090[i].f_0d6].f_65);
    } else {
        a = g_7090[i].f_05e;
        b = i;
        LoadString(g_9212, 0x314, buf, 40);
        c = (i * 2 + 3) * (a + 2) * (i + 6) * (i + 7) * 2 / (a + 3) + 956;
        fn_06_0f1a(c, tmp);
        lstrcat(buf, " ");
        lstrcat(buf, tmp);
    }
}

/* 17:14fc */
void fn_17_14fc(void)
{
    HDC hdc;
    HBITMAP hbm;
    HBITMAP old;
    HPALETTE oldpal;
    int16_t n;

    if (g_9460)
        n = (g_9468 - 1) / 2;
    else
        n = g_9322;
    hbm = world_map(g_6084.bottom - g_6084.top, g_6084.bottom - g_6084.top, 1, n, -1, -1, 0);
    hdc = CreateCompatibleDC(g_13dc);
    if (g_920e)
        oldpal = SelectPalette(hdc, g_920e, 0);
    old = SelectObject(hdc, hbm);
    BitBlt(g_13dc, g_6084.left, g_6084.top, g_6084.bottom - g_6084.top, g_6084.bottom - g_6084.top, hdc, 0, 0, SRCCOPY);
    SelectObject(hdc, old);
    if (g_920e)
        SelectPalette(hdc, oldpal, 0);
    DeleteDC(hdc);
    DeleteObject(hbm);
}

/* 17:7614 */
void fn_17_7614(int16_t i)
{
    int16_t unused;
    int16_t id;

    if (g_4ed4[i] == 11)
        id = 0x829;
    if (g_4d90[g_4ed4[i]].f_0a > 1200)
        id = 0x81f;
    else if (g_4d90[g_4ed4[i]].f_0a > 700)
        id = 0x820;
    else
        id = 0x821;
    fn_10_a332(g_6078, "button", 1, g_4d90[g_4ed4[i]].f_12 + 10000, g_4d90[g_4ed4[i]].f_02,
               0x819, 0x818, g_4d90[g_4ed4[i]].f_03 <= 0, g_4d90[g_4ed4[i]].f_03 > 0,
               g_4d90[g_4ed4[i]].f_03 == 1, g_2f4c[g_4d90[g_4ed4[i]].f_03].f_08, 0x81d,
               g_4d90[g_4ed4[i]].f_12 + 10000, id);
}

/* 17:108c */
int16_t fn_17_108c(int16_t reset)
{
    int16_t unused;

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
        g_5000 = g_6084.left + 20;
        g_5002 = g_6084.bottom - 40;
        fn_17_30b0(g_93aa, 4500L);
        fn_17_458e();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6084.left + 20;
        g_5002 = g_6084.bottom - 40;
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

/* 17:1174 */
int16_t fn_17_1174(int16_t reset)
{
    int16_t unused;

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
        g_5000 = g_6084.right - 280;
        g_5002 = g_6084.top + 60;
        fn_17_30b0(g_9468 + 305, 4500L);
        fn_17_51b0();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6084.right - 280;
        g_5002 = g_6084.top + 60;
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

/* 17:4204 */
void fn_17_4204(void)
{
    char name[60];
    int16_t i;
    int16_t cnt[3];
    int16_t j;
    int16_t k;
    int16_t v;

    k = g_96d2[g_7090[g_9646].f_04e].f_38;
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
    fn_13_218a(g_96d2[g_7090[g_9646].f_04e].f_38, name);
    fn_10_a332(g_6078, "", 1, (LPSTR)name, !cnt[0], cnt[0], cnt[0], 0x9dd,
               !cnt[2], cnt[2], cnt[2], 0x9de, cnt[1], cnt[1], 0x9d8);
}

/* 17:15c6 */
int16_t fn_17_15c6(int16_t reset)
{
    int16_t unused;

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
        g_5000 = g_9468 == 0 ? g_6084.left + 30 : (g_6084.right - g_6084.left) / 2 + g_6084.left;
        g_5002 = g_6084.top + 55;
        fn_17_30b0(g_93aa, 3000L);
        fn_17_5008();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_9468 == 0 ? g_6084.left + 30 : (g_6084.right - g_6084.left) / 2 + g_6084.left;
            g_5002 = g_6084.top + 55;
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

/* 17:13ca */
int16_t fn_17_13ca(int16_t reset)
{
    int16_t unused;

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
            g_5000 = g_6084.right - 280;
            g_5002 = g_6084.top + 54;
        } else {
            g_5000 = 20;
            g_5002 = g_6084.top + 40;
        }
        fn_17_30b0(g_93aa + 400, 3000L);
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            fn_17_5008();
            if (!g_9460 || !((g_9468 + 1) & 1)) {
                fn_17_14fc();
                g_5000 = g_6084.right - 280;
                g_5002 = g_6084.top + 54;
            } else {
                g_5000 = 20;
                g_5002 = g_6084.top + 40;
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

/* 17:12f6 */
int16_t fn_17_12f6(int16_t reset)
{
    int16_t unused;

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
        g_5000 = g_6084.left + 30;
        g_5002 = g_6084.top + 40;
        fn_17_30b0(g_93aa, 3000L);
        fn_17_5008();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6084.left + 30;
            g_5002 = g_6084.top + 40;
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
/* 17:8418 */
BOOL fn_17_8418(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int16_t v;
    char buf[110];
    int16_t idx;

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

/* 17:0c2e */
void fn_17_0c2e(int16_t idx, int16_t x, int16_t y)
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
    lstrcpy(buf, g_57a8[idx].f_0c);
    TextOut(g_13dc, x + 0x20, y + 0x44, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
}

/* 17:32de */
void fn_17_32de(int16_t flag)
{
    int16_t unused1;
    int16_t unused2;
    int16_t unused3;
    int16_t saved;
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
        fn_13_218a(g_96d2[g_7090[g_9464].f_04e].f_38, a);
        lstrcat(g_6078, a);
        saved = g_7090[g_9464].f_026[0];
        g_7090[g_9464].f_026[0] = 100;
        fn_13_33d6(g_9464);
        g_7090[g_9464].f_026[0] = saved;
        fn_17_42ea(1);
        fn_17_42ea(1);
        fn_17_3746();
    } else
        fn_17_33ee();
}

/* 17:55e2 */
void fn_17_55e2(int16_t n)
{
    HFONT hfont;
    HFONT oldfont;
    COLORREF oldbk;
    COLORREF oldtext;
    char buf[70];
    int16_t unused1;
    int16_t unused2;
    int16_t unused3;

    hfont = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    if (n == -1) {
        fn_09_955c(0x30f2, buf);
        fn_11_3fd4(buf, 1);
    } else
        fn_09_955c(g_2f4c[n].f_08, buf);
    oldtext = SetTextColor(g_13dc, 0x020080ffL);
    TextOut(g_13dc, g_6084.left + 40, g_6084.top + 20, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
}

/* 17:60d8 */
void fn_17_60d8(void)
{
    if (++g_9144 >= g_9004) {
        fn_07_2206();
        g_9144 = 0;
        g_1e50 = GetCurrentTime();
        fn_17_0000(0, 0);
    }
}

/* 17:6742 */
void fn_17_6742(int16_t a, int16_t b, HWND hwnd, int16_t code)
{
    int16_t unused;
    int16_t sel;
    char buf[30];

    switch (code) {
    case CBN_SELCHANGE:
        sel = (int16_t)SendMessage(hwnd, CB_GETCURSEL, 0, 0L);
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

/* 17:6792 */
void fn_17_6792(int16_t a, int16_t b, HWND hwnd, int16_t code)
{
    int16_t sel;

    switch (code) {
    case CBN_SELCHANGE:
        sel = (int16_t)SendMessage(hwnd, CB_GETCURSEL, 0, 0L);
        if (sel == -1)
            break;
        g_9468 = g_9466 == 0 ? sel * 2 : sel;
        fn_17_67e6();
        g_1926 = sel;
        break;
    }
}

/* 17:7b44 */
void fn_17_7b44(void)
{
    char buf[84];

    lstrcpy(g_6078, "");
    fn_09_95ba(0x82d);
    fn_17_7ba6(g_93a2, buf);
    lstrcat(g_6078, buf);
    fn_09_95ba(0x82e);
    lstrcat(g_6078, ". ");
}

/* 17:42ea */
void fn_17_42ea(int16_t flag)
{
    lstrcat(g_6078, " ");
    if (g_93aa != 11 || flag) {
        lstrcat(g_6078, "  ");
        g_6078[lstrlen(g_6078) - 2] = '\r';
        g_6078[lstrlen(g_6078) - 1] = '\n';
    }
}

/* 17:72aa */
void fn_17_72aa(int16_t a, int16_t b, int16_t c)
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
        fn_17_8f1e(b, c, 0, g_947a[5], buf2);
    }
}

/* Appends the ordinal suffix of n to buf [inferred]. */
/* 17:7ba6 */
void fn_17_7ba6(int16_t n, LPSTR buf)
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

/* 17:84ee */
void fn_17_84ee(int16_t id, LPARAM lParam)
{
    char buf[120];
    int16_t sel;

    switch (HIWORD(lParam)) {
    case LBN_SELCHANGE:
        SendMessage((HWND)LOWORD(lParam), LB_GETTEXT,
                    sel = (int16_t)SendMessage((HWND)LOWORD(lParam), LB_GETCURSEL, 0, 0L),
                    (LPARAM)(LPSTR)buf);
        buf[lstrlen(buf) - 9] = 0;
        SetWindowText(GetDlgItem(g_948c, 0x195), buf);
        break;
    case LBN_DBLCLK:
        PostMessage(g_948c, WM_COMMAND, 1, 0L);
        break;
    }
}

/* 17:56fe */
void fn_17_56fe(int16_t i, LPSTR buf)
{
    int16_t k;
    int16_t v;
    char tmp[50];

    k = g_96d2[g_7090[g_9646].f_04e].f_38;
    fn_13_218a(i, buf);
    lstrcat(buf, "...(");
    v = g_3824[i][k];
    fn_06_0f1a(v / 10, tmp);
    lstrcat(buf, tmp);
    lstrcat(buf, ")");
}

/* 17:1260 */
int16_t fn_17_1260(int16_t reset)
{
    int16_t unused;

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
        g_5000 = g_6084.left + 20;
        g_5002 = g_6084.bottom - 40;
        fn_17_4988();
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            g_5000 = g_6084.left + 20;
            g_5002 = g_6084.bottom - 40;
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

/* 17:8874 */
void fn_17_8874(HWND hDlg, int16_t ok)
{
    char buf[110];
    int16_t sel;
    int16_t v;
    int16_t unused;

    g_948c = 0;
    if (ok) {
        sel = (int16_t)SendMessage(GetDlgItem(hDlg, 0x199), LB_GETCURSEL, 0, 0L);
        SendMessage(GetDlgItem(hDlg, 0x199), LB_GETTEXT, sel, (LPARAM)(LPSTR)buf);
        v = (buf[lstrlen(buf) - 2] - '0') * 100;
        v += buf[lstrlen(buf) - 1] - '0';
    } else
        v = 0;
    EndDialog(hDlg, v);
}

/* 17:7526 */
int16_t fn_17_7526(int16_t n)
{
    char name1[80];
    char name2[80];
    int16_t i;
    int16_t k;
    int16_t unused;

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

/* 17:75c6 */
int16_t fn_17_75c6(int16_t n)
{
    int16_t i;
    int16_t cnt;

    cnt = 0;
    for (i = 0; i < n; i++)
        if (g_1df8[14][i].f_18 == 0 && g_7090[i].flag != 0)
            cnt += 2;
    return cnt;
}

/* 17:92b8 */
void fn_17_92b8(DRAWITEMSTRUCT *dis)
{
    RECT rc;

    CopyRect(&rc, &dis->rcItem);
    if (dis->itemID == -1 || (dis->itemState & ODS_FOCUS))
        DrawFocusRect(dis->hDC, &rc);
    else
        fn_17_9308(dis);
}

/* 17:9308 */
void fn_17_9308(DRAWITEMSTRUCT *dis)
{
    RECT rc;

    fn_17_90d2(dis);
    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_FOCUS)
        DrawFocusRect(dis->hDC, &rc);
}

/* 17:646e */
void fn_17_646e(void)
{
    int16_t i;
    int16_t h;
    int16_t x;
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
    if (g_947a[3])
        DestroyWindow(g_947a[3]);
    if (g_6084.right > 670)
        x = rc.left + 256;
    else
        x = rc.left + 186;
    g_947a[3] = CreateWindow("combobox", "", 0x50210003L, x, rc.bottom - 0x1c,
                          0x8c, h * g_9470 + 0x1e, g_9460, (HMENU)0x67, g_8e66, NULL);
    SendMessage(g_947a[3], WM_SETFONT, g_6094[0], 1L);
    for (i = 0; i < g_9470; i++) {
        fn_09_955c(i + 800, buf);
        SendMessage(g_947a[3], CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    }
    SendMessage(g_947a[3], CB_SETCURSEL, g_9466, 0L);
}

/* 17:65da */
void fn_17_65da(void)
{
    int16_t unused1;
    int16_t h;
    int16_t n;
    int16_t unused2;
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
    if (g_947a[4])
        DestroyWindow(g_947a[4]);
    g_946a = fn_17_8910(g_9466, 0, 0);
    n = g_9466 == 0 ? g_946a / 2 : g_946a;
    if (g_946a < 2)
        EnableWindow(g_947a[2], 0);
    else
        EnableWindow(g_947a[2], 1);
    EnableWindow(g_947a[0], 0);
    if (n > 15)
        n = 15;
    g_947a[4] = CreateWindow("combobox", "", 0x50210003L, rc.right - 0xe0, rc.bottom - 0x1c,
                          0xa0, n * h + 0x1e, g_9460, (HMENU)0x68, g_8e66, NULL);
    SendMessage(g_947a[4], WM_SETFONT, g_6094[0], 1L);
    fn_17_8910(g_9466, g_947a[4], 0);
    if (g_9466 == 0)
        g_9464 = g_9646;
    g_9468 = 0;
    SendMessage(g_947a[4], CB_SETCURSEL, 0, 0L);
}

/* Handles a selection change in the list combo box [inferred]. */
/* 17:67e6 */
void fn_17_67e6(void)
{
    int16_t i;
    int16_t j;
    int16_t r;
    int16_t unused;
    int16_t sel;
    int16_t unused2;
    char buf[258];
    char text[110];

    if (g_9468 == 0) {
        if (IsWindowEnabled(g_947a[0])) {
            if (GetFocus() == g_947a[0])
                SetFocus(g_947a[4]);
            EnableWindow(g_947a[0], 0);
        }
    } else if (!IsWindowEnabled(g_947a[0]))
        EnableWindow(g_947a[0], 1);
    if (g_946a - g_9468 == 1) {
        if (IsWindowEnabled(g_947a[2])) {
            if (GetFocus() == g_947a[2])
                SetFocus(g_947a[4]);
            EnableWindow(g_947a[2], 0);
        }
    } else if (!IsWindowEnabled(g_947a[2]))
        EnableWindow(g_947a[2], 1);
    g_9462 = -2;
    SendMessage(g_947a[4], CB_GETLBTEXT, g_9468, (LPARAM)(LPSTR)text);
    fn_11_3fd4(text, 1);
    switch (g_9466) {
    case 0:
        for (i = j = 0; i <= g_9316; i++) {
            if (g_1df8[14][i].f_18 == 0 && g_7090[i].flag != 0) {
                if (g_9468 / 2 == j) {
                    g_9464 = i;
                    break;
                }
                j++;
            }
        }
        g_93aa = 11;
        g_9462 = -3;
        break;
    case 1:
        switch (g_9468) {
        case 0:
            g_93aa = 1;
            break;
        case 1:
            g_93aa = 3;
            break;
        }
        break;
    case 2:
        fn_09_955c(0x27a9, buf);
        fn_11_3fd4(buf, 1);
        if (lstrcmp(buf, text) == 0) {
            g_93aa = 4;
            break;
        }
        fn_09_955c(0x27ba, buf);
        fn_11_3fd4(buf, 1);
        if (lstrcmp(buf, text) == 0) {
            g_93aa = 6;
            break;
        }
        if (g_4ee0[0]) {
            fn_10_a332(buf, (char *)g_4d90[g_4ed4[0]].f_12, 1);
            if (lstrcmp(buf, text) == 0)
                g_93aa = 8;
            else
                g_93aa = 9;
        }
        break;
    case 3:
        switch (g_9468) {
        case 0:
            g_93aa = 5;
            break;
        case 1:
            g_93aa = 7;
            break;
        }
        break;
    case 4:
        switch (g_9468) {
        case 0:
            g_93aa = 12;
            break;
        default:
            g_93aa = 13;
            break;
        }
        break;
    case 5:
        g_93aa = 14;
        break;
    case 6:
        g_93aa = 15;
        break;
    case 7:
        switch (g_9468) {
        case 0:
            g_93aa = 17;
            break;
        default:
            g_93aa = 2;
            break;
        }
        break;
    case 8:
        g_93aa = 16;
        break;
    case 9:
        for (i = 1; i < 27; i++) {
            fn_09_955c(i + 0xba, buf);
            if (lstrcmp(buf, text) == 0) {
                g_93aa = 10;
                g_9472 = i;
                break;
            }
        }
        break;
    }
    if ((r = fn_17_7088(g_9476 = 0)) != 0)
        g_9476 = 1;
    if (g_947a[5]) {
        DestroyWindow(g_947a[5]);
        g_947a[5] = 0;
    }
    if (g_947a[6]) {
        DestroyWindow(g_947a[6]);
        g_947a[6] = 0;
    }
    if (g_947a[7]) {
        DestroyWindow(g_947a[7]);
        g_947a[7] = 0;
    }
    if (g_9466 == 8) {
        if (g_9468 == 0) {
            g_947a[7] = CreateWindow("listbox", "", 0x40a30151L, 0x2e, 0x5c, 0x23a, 0xc0,
                                  g_9460, (HMENU)0x6c, g_8e66, NULL);
            fn_02_1a7a(g_947a[7]);
        }
        fn_06_6576();
        if (g_9468 == 0)
            SendMessage(g_947a[7], 0x407, g_93a2 - 1, 0L);
    } else if (g_9466 == 7) {
        fn_10_320a();
        if ((g_9468 + 1) & 1) {
            uint16_t best;
            int16_t bi;

            g_947a[7] = CreateWindow("listbox", "", 0x40a30151L, 0x1b, 0x5c, 0x241, 0xc0,
                                  g_9460, (HMENU)0x6c, g_8e66, NULL);
            fn_02_1a7a(g_947a[7]);
            fn_06_8b90((g_9468 - 1) / 2);
            fn_06_8cb2((g_9468 - 1) / 2, g_9646, 0, 0, 1);
            sel = -1;
            for (j = 0; j < g_94c8; j++) {
                best = 60000;
                bi = -1;
                for (i = 0; i < g_94c8; i++) {
                    if (g_6afc[i].f_32[0][1] > 1 && g_6afc[i].f_32[0][1] < best) {
                        bi = i;
                        best = g_6afc[i].f_32[0][1];
                    } else if (g_6afc[i].f_32[0][1] == 0 && best == 60000) {
                        best = 59999;
                        bi = i;
                    }
                }
                if (bi >= 0) {
                    if (lstrcmp(g_96d2[g_7090[g_9646].f_04e].f_70, g_6afc[bi].f_00) == 0)
                        sel = j;
                    fn_17_7ba6(j + 1, buf);
                    lstrcat(buf, "\t050");
                    lstrcat(buf, g_6afc[bi].f_00);
                    lstrcat(buf, "\t185");
                    fn_11_4928(2, g_6afc[bi].f_32[0][1], text);
                    lstrcat(buf, text);
                    lstrcat(buf, "\t250");
                    fn_11_4928(2, g_6afc[bi].f_32[0][0], text);
                    lstrcat(buf, text);
                    lstrcat(buf, "\t310");
                    fn_11_4928(0, g_6afc[bi].f_32[1][1], text);
                    lstrcat(buf, text);
                    lstrcat(buf, "\t370");
                    fn_11_4928(0, g_6afc[bi].f_32[1][0], text);
                    lstrcat(buf, text);
                    lstrcat(buf, "\t450");
                    fn_11_4928(0, g_6afc[bi].f_32[2][1], text);
                    lstrcat(buf, text);
                    lstrcat(buf, "\t510");
                    fn_11_4928(0, g_6afc[bi].f_32[2][0], text);
                    lstrcat(buf, text);
                    lstrcat(buf, "\t250");
                    lstrcat(buf, g_6afc[bi].f_14[0]);
                    lstrcat(buf, "\t370");
                    lstrcat(buf, g_6afc[bi].f_14[1]);
                    lstrcat(buf, "\t510");
                    lstrcat(buf, g_6afc[bi].f_14[2]);
                    SendMessage(g_947a[7], 0x401, 0, (LPARAM)(LPSTR)buf);
                    g_6afc[bi].f_32[0][1] = 1;
                }
            }
            if (sel < 0)
                sel = 0;
            SendMessage(g_947a[7], 0x407, sel, 0L);
            fn_06_8eb4();
        }
    }
    if (g_9476) {
        int16_t h;
        HFONT old;
        char s[] = "Test";
        RECT rc;

        GetClientRect(g_9460, &rc);
        g_13dc = GetDC(g_9460);
        old = SelectObject(g_13dc, g_6094[0]);
        h = HIWORD(GetTextExtent(g_13dc, s, 4));
        SelectObject(g_13dc, old);
        ReleaseDC(g_9460, g_13dc);
        g_13dc = 0;
        g_947a[5] = CreateWindow("combobox", "", 0x50210003L, rc.right - 0xb4, rc.bottom - 0x3c,
                              0xaa, h * r + 0x1e, g_9460, (HMENU)0x6a, g_8e66, NULL);
        SendMessage(g_947a[5], WM_SETFONT, g_6094[0], 1L);
        fn_09_955c(0x88e, buf);
        g_947a[6] = CreateWindow("button", buf, 0x50010000L, rc.right - 0x104, rc.bottom - 0x3f,
                              0x4b, 0x17, g_9460, (HMENU)0x6b, g_8e66, NULL);
        SendMessage(g_947a[6], WM_SETFONT, g_6094[1], 1L);
        fn_17_7088(r);
        SendMessage(g_947a[5], 0x40e, 0, 0L);
    }
    if (g_9466 == 0)
        SendMessage(g_947a[4], 0x40e, g_9468 / 2, 0L);
    else
        SendMessage(g_947a[4], 0x40e, g_9468, 0L);
}

/* Types the briefing text g_6078 a few characters per call [inferred]. */
/* 17:2c5a */
int16_t fn_17_2c5a(int16_t a, int16_t b)
{
    HFONT oldfont;
    HFONT hfont;
    DWORD oldtext;
    DWORD oldbk;
    char word[54];
    int16_t i;
    int16_t n;
    int16_t pad[8];
    int16_t hasctl;
    int16_t wrap;
    int16_t margin;
    int16_t j;
    int16_t len;

    n = 10;
    if (a) {
        if (!b)
            fn_15_84b0(g_5000 + 15, g_5002 + 10);
        g_0ba2 = 0;
        g_1912 = 0;
        g_1914 = 0;
        g_190a = VIEW(POINT, g_5000, 0);
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
                    int16_t w;

                    word[len + 1] = 0;
                    w = LOWORD(GetTextExtent(g_13dc, word, len)) + g_190a.x;
                    if (len > 5)
                        margin = 9;
                    else
                        margin = 22;
                    if (g_6084.right - margin < w)
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
/* 17:458e */
void fn_17_458e(void)
{
    HFONT font;
    HGDIOBJ oldfont;
    COLORREF oldbk;
    COLORREF oldtxt;
    char buf1[80];
    char buf2[70];
    int16_t i;
    int16_t j;
    int16_t me;
    int16_t rel;
    POINT pt;

    font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    fn_09_955c(0x382, buf2);
    oldtxt = SetTextColor(g_13dc, PALETTERGB(0, 214, 255));
    TextOut(g_13dc, g_5000, g_6084.top + 20, buf2, lstrlen(buf2));
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
    me = g_96d2[g_7090[g_9646].f_04e].f_38;
    oldtxt = SetTextColor(g_13dc, RGB(0, 255, 255));
    pt.y = g_6084.top + 60;
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
    pt.y = g_6084.top + 60;
    pt.x = g_6084.left + 210;
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
    pt.y = g_6084.top + 60;
    pt.x = g_6084.left + 410;
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

/* 17:51b0 */
void fn_17_51b0(void)
{
    HFONT hfont;
    HFONT oldfont;
    DWORD oldbk;
    DWORD oldtext;
    char buf[80];
    char name[70];
    int16_t i;
    int16_t count;
    int16_t unused;
    int16_t side;
    int16_t rel;
    POINT pt;
    int16_t rel2;

    hfont = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    side = g_96d2[g_7090[g_9646].f_04e].f_38;
    fn_13_218a(g_9468 - 1, name);
    if ((rel = g_3824[g_9468 - 1][side]) > 80 || g_9468 - side - 1 == 0)
        oldtext = SetTextColor(g_13dc, PALETTERGB(0, 0xd6, 0xff));
    else if (rel < -80)
        oldtext = SetTextColor(g_13dc, PALETTERGB(0xff, 0x80, 0));
    else
        oldtext = SetTextColor(g_13dc, PALETTERGB(0xc0, 0xc0, 0xc0));
    TextOut(g_13dc, g_6084.left + 40, g_6084.top + 20, name, lstrlen(name));
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
    pt.y = g_6084.top + 60;
    pt.x = g_6084.left + 40;
    if (g_9468 - side - 1 == 0) {
        fn_09_955c(0x806, buf);
    } else {
        i = count = 0;
        for (; i <= g_9316; i++)
            if (g_7090[i].flag && g_96d2[g_7090[i].f_04e].f_38 - g_9468 + 1 == 0)
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

/* Ship statistics lines of the info panel [inferred]. */
/* near-match 29%: 17:3746 (code shape and order match; CL's choice of CSE temps
 * differs: the game keeps g_1e30[idx].f44 * 3 in a temp and has no extra copy of
 * ia4, which shifts the frame and every temp slot). la2 is a struct so that it is
 * not dword-aligned (the game has it at bp-0xa2). */
void fn_17_3746(void)
{
    int16_t i;
    int16_t u1;
    int16_t u2;
    int16_t u3;
    int16_t idx;
    char buf1[50];
    char buf2[50];
    int32_t l74;
    int32_t l78;
    int32_t l7c;
    int32_t l80;
    int32_t l84;
    int32_t l88;
    int32_t l8c;
    int32_t l90;
    int32_t l94;
    int16_t i96;
    int16_t i98;
    int16_t i9a;
    int16_t i9c;
    int16_t i9e;
    struct { int32_t v; } la2;
    int16_t ia4;

    idx = g_9464;
    l7c = 10L * g_1df8[14][idx].f_44;
    i96 = 1350 / g_7090[idx].f_014;
    l90 = g_7090[idx].f_00c;
    if (g_7090[idx].f_0d6 != -1)
        l90 = l90 * ((g_6e24[g_7090[idx].f_0d6].f_33 + 10) * 10) / 100;
    l78 = l90 * 3456;
    l80 = g_96d2[g_7090[idx].f_04e].f_1e / 2;
    i98 = g_7090[idx].f_00c * 3 / 4;
    ia4 = g_7090[idx].f_00e;
    i9a = (int16_t)(l90 * 69 / ia4);
    l74 = l78 / (i9a * 10 / 36);
    l88 = ia4 * -3600L / (g_1df8[14][idx].f_44 * 3) + 100;
    la2.v = l88 * l88 * l88 / -60000 - l88 * l88 / 200;
    l8c = (la2.v - l88 - 100) * 37 / 100 + 100;
    i9c = (int16_t)(l90 * l8c * 69 / (ia4 * 100L));
    i9e = g_1df8[14][idx].f_44 * 3 / (ia4 * 12);
    if (g_7090[idx].f_0d6 != -1) {
        l94 = g_96d2[g_7090[idx].f_04e].f_12 * 100 / (20 - 3 * g_6e24[g_7090[idx].f_0d6].f_35)
            + g_96d2[g_7090[idx].f_04e].f_14 * 80 / (20 - 3 * g_6e24[g_7090[idx].f_0d6].f_36)
            + g_96d2[g_7090[idx].f_04e].f_10 * 80 / (20 - 3 * g_6e24[g_7090[idx].f_0d6].f_34);
        if (g_96d2[g_7090[idx].f_04e].f_28 != -1) {
            l94 += g_96d2[g_7090[idx].f_04e].f_16 * 100 / (20 - 3 * g_6e24[g_7090[idx].f_0d6].f_37);
            l94 /= 4;
        } else
            l94 /= 3;
    } else
        l94 = g_96d2[g_7090[idx].f_04e].f_a6;
    l84 = l94 * (g_1df8[14][idx].f_44 + 350) * 2 / 350 * 12600 / 3000;
    for (i = 0; i < 7; i++) {
        fn_09_95ba(i + 0xfe);
        fn_09_95ba(0x221);
        switch (i) {
        case 0:
            fn_06_0eb8(l7c, buf1);
            break;
        case 1:
            fn_06_0f1a(i96, buf1);
            break;
        case 2:
            fn_06_0f1a(i9a, buf1);
            lstrcpy(buf2, buf1);
            fn_09_9580(0x105, buf2);
            fn_06_0f1a(i9e, buf1);
            lstrcat(buf2, buf1);
            break;
        case 3:
            fn_06_0f1a(i9c, buf1);
            break;
        case 4:
            fn_06_0f1a(i98, buf1);
            break;
        case 5:
            fn_06_0eb8(l80, buf1);
            break;
        case 6:
            fn_06_0eb8(l84, buf1);
            break;
        }
        if (i == 2)
            lstrcat(g_6078, buf2);
        else
            lstrcat(g_6078, buf1);
        fn_09_95ba(i + 0x107);
        if (i < 6)
            fn_17_42ea(1);
    }
}

/* Writes the relations/finance lines of the contact report [inferred]. */
/* 17:33ee */
void fn_17_33ee(void)
{
    int16_t rel;
    int16_t rel2;
    int16_t c1;
    int16_t c2;
    char buf3e[52];
    char buf66[40];
    char buff2[140];
    int16_t id1;
    int16_t id2;

    if (g_9464 == g_9646) {
        fn_06_0f54(g_7090[g_9464].f_0dc, 100, 2, buf3e);
        fn_06_1010(g_7090[g_9464].f_0ce, 100, 2, buf66);
        fn_10_a332(g_6078, (char *)0xbdb, 0, g_91f8 < 1 ? 1 : g_91f8, (LPSTR)g_38c8, g_1e58,
                   g_7090[g_9646].f_0d2, 0x9d3, g_7090[g_9646].f_0d0, 0x9d3,
                   (LPSTR)buf3e, (LPSTR)buf66);
        if (g_9460)
            return;
        fn_17_42ea(1);
        fn_17_42ea(1);
    } else {
        if (g_96d2[g_7090[g_9464].f_04e].f_38 != 7 && g_7090[g_9464].f_0d6 >= 0
            && g_6e24[g_7090[g_9464].f_0d6].f_77 > 1)
            fn_10_a332(g_6078, (char *)0xbda, 0, 0xe, g_9464, 3,
                       g_6e24[g_7090[g_9464].f_0d6].f_77 < 4,
                       g_6e24[g_7090[g_9464].f_0d6].f_77 == 2, 0x39a, 0x39b,
                       g_6e24[g_7090[g_9464].f_0d6].f_77 >= 4,
                       g_6e24[g_7090[g_9464].f_0d6].f_77 - 1);
        else
            fn_10_a332(g_6078, (char *)0x399, 0, 0xe, g_9464, 3);
        if (g_96d2[g_7090[g_9464].f_04e].f_38 != 7 && g_7090[g_9464].f_0d6 >= 0
            && g_6e24[g_7090[g_9464].f_0d6].f_77 > 1) {
            fn_09_95ba(0x7fe);
            lstrcat(g_6078, g_09ee);
        }
        c1 = g_96d2[g_7090[g_9464].f_04e].f_38;
        c2 = g_96d2[g_7090[g_9646].f_04e].f_38;
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
            ((void (*)(char *))fn_11_3fd4)(g_8db0);
            fn_03_3498(g_8db0, g_8768, g_87b8);
            fn_06_0f54(g_7090[g_9464].f_0dc, 100, 2, buf3e);
            fn_06_1010(g_7090[g_9464].f_0ce, 100, 2, buf66);
            fn_10_a332(g_6078, (char *)0xbde, 0, (LPSTR)g_8768, (LPSTR)g_87b8,
                       (LPSTR)buf3e, (LPSTR)buf66);
            lstrcpy(g_8d38, buff2);
            return;
        }
    }
    fn_17_4068(g_9464, buff2);
    lstrcat(g_6078, buff2);
}

/* 17:4988 */
void fn_17_4988(void)
{
    HFONT hfont;
    HFONT oldfont;
    DWORD oldbk;
    DWORD oldtext;
    char line[80];
    char buf[70];
    int16_t i;
    POINT pt;

    hfont = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    fn_15_84b0(30, g_6084.top + 20);
    fn_09_955c(g_9468 + 0x492, buf);
    oldtext = SetTextColor(g_13dc, PALETTERGB(0, 0xd6, 0xff));
    TextOut(g_13dc, 30, g_6084.top + 20, buf, lstrlen(buf));
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
    oldtext = SetTextColor(g_13dc, RGB(0, 255, 255));
    pt.y = g_6084.top + 60;
    pt.x = 30;
    switch (g_9468) {
    case 0:
        fn_09_955c(0x310, line);
        TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
        fn_09_955c(0x311, line);
        TextOut(g_13dc, pt.x + 195, pt.y, line, lstrlen(line));
        pt.y += 28;
        for (i = 0; i < 9; i++) {
            fn_09_955c(i + 0x4c7, buf);
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            fn_09_955c(i + 0x52b, buf);
            TextOut(g_13dc, pt.x + 195, pt.y, buf, lstrlen(buf));
            pt.y += 18;
        }
        break;
    case 1:
        fn_09_955c(0x493, line);
        TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
        fn_09_955c(0x312, line);
        TextOut(g_13dc, pt.x + 110, pt.y, line, lstrlen(line));
        fn_09_955c(0x313, line);
        TextOut(g_13dc, pt.x + 220, pt.y, line, lstrlen(line));
        fn_09_955c(0x311, line);
        TextOut(g_13dc, pt.x + 380, pt.y, line, lstrlen(line));
        pt.y += 28;
        for (i = 0; i < 9; i++) {
            fn_09_955c(i + 0x4d0, line);
            TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
            fn_09_955c(i + 0x4d9, line);
            TextOut(g_13dc, pt.x + 110, pt.y, line, lstrlen(line));
            fn_09_955c(i + 0x4e2, line);
            TextOut(g_13dc, pt.x + 220, pt.y, line, lstrlen(line));
            fn_09_955c(i + 0x534, line);
            TextOut(g_13dc, pt.x + 380, pt.y, line, lstrlen(line));
            pt.y += 18;
        }
        break;
    case 2:
        pt.y -= 10;
        fn_09_955c(0x310, line);
        TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
        fn_09_955c(0x311, line);
        TextOut(g_13dc, pt.x + 80, pt.y, line, lstrlen(line));
        pt.y += 28;
        for (i = 0; i < 11; i++) {
            fn_09_955c(i + 0x4b0, buf);
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            fn_09_955c(i + 0x514, buf);
            TextOut(g_13dc, pt.x + 80, pt.y, buf, lstrlen(buf));
            pt.y += 18;
        }
        pt.y = g_6084.top + 60;
        pt.x = (g_6084.right - g_6084.left) / 2 + g_6084.left;
        fn_09_955c(0x310, line);
        TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
        fn_09_955c(0x311, line);
        TextOut(g_13dc, pt.x + 100, pt.y, line, lstrlen(line));
        pt.y += 28;
        for (i = 0; i < 11; i++) {
            fn_09_955c(i + 0x4bc, buf);
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            fn_09_955c(i + 0x520, buf);
            TextOut(g_13dc, pt.x + 100, pt.y, buf, lstrlen(buf));
            pt.y += 18;
        }
        break;
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
}

/* 17:0000 */
void fn_17_0000(int16_t a, int16_t b)
{
    int16_t done;
    int16_t v;
    int16_t f;
    int16_t pad;

    if (!g_9460 && (g_8f70 || g_90f8) && g_93aa != 18) {
        g_93aa = 18;
        return;
    }
    f = 0;
    if (g_93aa != 11)
        g_946c = -1;
    if (g_9462 == -3) {
        PatBlt(g_13dc, g_6084.left, g_6084.top, g_6084.right - g_6084.left, g_6084.bottom - g_6084.top, BLACKNESS);
        fn_10_744c(0x6e);
        done = fn_17_20fa(1, 0, 1);
    }
    if (g_9462 == -2)
        fn_17_03b2();
    if (g_9462 == -1) {
        if (g_93aa == 11) {
            PatBlt(g_13dc, g_6084.left, g_6084.top, g_6084.right - g_6084.left, g_6084.bottom - g_6084.top, BLACKNESS);
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
        VIEW(int32_t, g_608c, 0) = g_90ea;
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
        if (!g_91f8 && g_92ec[3] || g_9460)
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
        if ((g_91f8 == 1 || g_9460) && g_92ec[2])
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
        if (g_92ec[9])
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

/* 17:8910 */
int16_t fn_17_8910(int16_t a, HWND hwnd, int16_t b)
{
    char buf[120];
    int16_t i;
    int16_t k;
    int16_t unused;
    int16_t count;
    int16_t j;

    switch (a) {
    case 0:
        count = 0;
        for (i = 0; i <= g_9316; i++) {
            if (g_1df8[14][i].f_18 == 0 && g_7090[i].flag != 0)
                count += 2;
        }
        break;
    case 2:
        count = 1;
        if (g_92ec[9] != 0)
            count = 2;
        for (k = 0; k < 2; k++) {
            if (g_4ee0[k] != 0)
                count++;
        }
        break;
    case 3:
        count = 1;
        if (g_92ec[2] == 0)
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

/* 17:8f1e */
void fn_17_8f1e(int16_t a, int16_t b, int16_t c, HWND hwnd, LPSTR buf)
{
    char s1[120];
    char s2[110];
    int16_t i;

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
        if (hwnd == g_947a[5]) {
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

/* 17:8a92 */
void fn_17_8a92(int16_t idx, int16_t kind, LPSTR out)
{
    char s1[110];
    char s2[110];
    int16_t i;
    int16_t t;
    int16_t n;
    int16_t unused;

    n = 0;
    switch (kind) {
    case 0:
        for (i = 0; i <= g_9316; i++) {
            if (g_1df8[14][i].f_18 == 0 && g_7090[i].flag != 0) {
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
        } else if (g_92ec[9] != 0 && idx == 1) {
            LoadString(g_9212, 0x27ba, s1, 110);
        } else {
            t = idx - 1;
            if (g_92ec[9] != 0)
                t--;
            if (g_4ee0[t] != 0)
                fn_10_a332(s1, (char *)(g_4d90[g_4ed4[t]].f_12 + 10000), 1);
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
            lstrcat(s1, g_6af8[idx - 1].f_04);
            lstrcat(s1, " - ");
            lstrcat(s1, g_6e20[g_6af8[idx - 1].f_22].f_0a);
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

/* 17:4068 */
void fn_17_4068(int16_t i, LPSTR buf)
{
    char unused[60];
    int16_t saved;
    int16_t id;

    saved = g_7090[i].f_026[0];
    g_7090[i].f_026[0] = 100;
    fn_13_33d6(i);
    g_7090[i].f_026[0] = saved;
    if (g_7090[i].f_0d8 > 32600)
        id = 0x2c5;
    else if (g_7090[i].f_0d8 > 25000)
        id = 0x2c6;
    else if (g_7090[i].f_0d8 > g_0956[10] * 100)
        id = 0x2c7;
    else if (g_7090[i].f_0d8 > g_0956[9] * 100)
        id = 0x2c8;
    else if (g_7090[i].f_0d8 > g_0956[8] * 100)
        id = 0x2c9;
    else if (g_7090[i].f_0d8 > g_0956[7] * 100)
        id = 0x2ca;
    else if (g_7090[i].f_0d8 > g_0956[6] * 100)
        id = 0x2cb;
    else if (g_7090[i].f_0d8 > g_0956[5] * 100)
        id = 0x2cc;
    else if (g_7090[i].f_0d8 > g_0956[4] * 100)
        id = 0x2cd;
    else if (g_7090[i].f_0d8 > g_0956[3] * 100)
        id = 0x2ce;
    else if (g_7090[i].f_0d8 > g_0956[2] * 100)
        id = 0x2cf;
    else if (g_7090[i].f_0d8 > g_0956[1] * 100)
        id = 0x2d0;
    else if (g_7090[i].f_0d8 > g_0956[0] * 100)
        id = 0x2d1;
    else
        id = 0x2d2;
    fn_10_a332(buf, "n", 1, i == g_9646, i != g_9646, id);
}

/* 17:5008 */
void fn_17_5008(void)
{
    HFONT font;
    HFONT old;
    COLORREF oldbk;
    COLORREF oldtc;
    char buf[150];
    int16_t unused;
    int16_t x;
    int16_t unused2;
    int16_t unused3;
    int16_t t;

    font = CreateFont(15, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    old = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    if (g_93aa == 2) {
        if (g_9460 != 0 && (g_9468 + 1) % 2 != 0)
            SendMessage(g_947a[4], CB_GETLBTEXT, g_9468, (LPARAM)(LPSTR)buf);
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
        SendMessage(g_947a[4], CB_GETLBTEXT, g_9468, (LPARAM)(LPSTR)buf);
    }
    if (g_93aa == 0x10 && g_9468 != 0)
        fn_17_7c2a();
    oldtc = SetTextColor(g_13dc, PALETTERGB(0, 0xd6, 0xff));
    if (g_93aa == 2 && (g_9460 == 0 || (g_9468 + 1) % 2 == 0))
        x = g_6084.right - 280;
    else if (g_93aa == 2)
        x = 20;
    else
        x = 35;
    TextOut(g_13dc, x, g_6084.top + 20, buf, lstrlen(buf));
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtc);
    SelectObject(g_13dc, old);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
}

/* Shows the details of the selected saved game [inferred]. */
/* 17:7c2a */
void fn_17_7c2a(void)
{
    HFONT hfont;
    HFONT oldfont;
    DWORD oldbk;
    DWORD oldtext;
    char line[80];
    char buf[110];
    char unused[10];
    HFILE fh;
    POINT pt;
    DWORD size;
    int32_t unused4;
    HGLOBAL h;
    REC_SAVE_seg17 *p;
    OFSTRUCT of;
    int16_t r;

    hfont = CreateFont(13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    oldfont = SelectObject(g_13dc, hfont);
    oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
    SetBkMode(g_13dc, TRANSPARENT);
    SetTextAlign(g_13dc, 0);
    SetTextColor(g_13dc, RGB(0, 255, 255));
    pt.y = g_6084.top + 60;
    pt.x = g_6084.left + 30;
    fn_14_3eda();
    if (g_9468 != g_93a2) {
        lstrcpy(buf, g_9078);
        if (g_6af8[g_9468 - 1].f_30 == 0)
            lstrcat(buf, g_96b8);
        else
            lstrcat(buf, g_96c5);
        lstrcat(buf, g_6af8[g_9468 - 1].f_26);
        switch (g_6af8[g_9468 - 1].f_30) {
        case 0:
            lstrcat(buf, ".sav");
            break;
        case 1:
            lstrcat(buf, ".ded");
            break;
        case 2:
            lstrcat(buf, ".don");
            break;
        }
        if ((fh = OpenFile(buf, &of, 0)) == -1)
            return;
    }
    h = GlobalAlloc(GHND, 0x1a9L);
    GlobalLock(h);
    size = GlobalSize(h);
    GlobalUnlock(h);
    h = GlobalReAlloc(h, size, GHND);
    p = (REC_SAVE_seg17 *)GlobalLock(h);
    if (g_9468 != g_93a2) {
        r = fn_14_4006(fh, (char *)p, size);
        _lclose(fh);
    } else {
        fn_06_8eea((LPSTR)p);
    }
    LoadString(g_9212, 0x833, line, 40);
    lstrcat(line, p->f_004);
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 18;
    LoadString(g_9212, 0x834, line, 40);
    lstrcat(line, g_6e20[p->f_022].f_0a);
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 18;
    LoadString(g_9212, 0x835, line, 40);
    fn_13_218a(g_96d2[g_7090[g_9464].f_04e].f_38, buf);
    lstrcat(line, buf);
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 36;
    LoadString(g_9212, 0x836, line, 40);
    fn_06_0eb8(p->f_01e, buf);
    lstrcat(line, buf);
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 18;
    LoadString(g_9212, 0x837, line, 40);
    fn_06_0f1a(g_9468, buf);
    lstrcat(line, buf);
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 18;
    LoadString(g_9212, 0x838, line, 40);
    switch (g_6af8[g_9468 - 1].f_30) {
    case 0:
        LoadString(g_9212, 0x839, buf, 40);
        lstrcat(line, buf);
        break;
    case 1:
        LoadString(g_9212, 0x83a, buf, 40);
        lstrcat(line, buf);
        break;
    case 2:
        LoadString(g_9212, 0x83b, buf, 40);
        lstrcat(line, buf);
        break;
    }
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 18;
    LoadString(g_9212, 0x83c, line, 40);
    fn_06_0f1a(p->f_018 + 1, buf);
    lstrcat(line, buf);
    lstrcat(line, "/");
    fn_06_0f1a(p->f_019, buf);
    lstrcat(line, buf);
    lstrcat(line, "/");
    fn_06_0f1a(p->f_01a, buf);
    lstrcat(line, buf);
    lstrcat(line, " - ");
    fn_06_0f1a(p->f_01b + 1, buf);
    lstrcat(line, buf);
    lstrcat(line, "/");
    fn_06_0f1a(p->f_01c, buf);
    lstrcat(line, buf);
    lstrcat(line, "/");
    fn_06_0f1a(p->f_01d, buf);
    lstrcat(line, buf);
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 18;
    LoadString(g_9212, 0x83d, line, 40);
    fn_15_6558(p->f_16f, buf);
    lstrcat(line, buf);
    TextOut(g_13dc, pt.x, pt.y, line, lstrlen(line));
    pt.y += 18;
    GlobalUnlock(h);
    GlobalFree(h);
    fn_14_4074();
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtext);
    SelectObject(g_13dc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
}

/* 17:8270 */
void fn_17_8270(void)
{
    int16_t unused1;
    int16_t unused2;
    HFILE fh;
    char path[110];
    char unused3[30];
    DWORD size;
    int32_t unused4;
    HGLOBAL h;
    LPSTR p;
    OFSTRUCT of;
    int16_t r;

    lstrcpy(g_6078, "");
    if (g_9468 != g_93a2) {
        lstrcpy(path, g_9078);
        if (g_6af8[g_9468 - 1].f_30 == 0)
            lstrcat(path, g_96b8);
        else
            lstrcat(path, g_96c5);
        lstrcat(path, g_6af8[g_9468 - 1].f_26);
        switch (g_6af8[g_9468 - 1].f_30) {
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
/* 17:90d2 */
void fn_17_90d2(DRAWITEMSTRUCT *dis)
{
    RECT rc;
    HBRUSH br;
    HFONT oldf;
    char text[240];
    char buf[140];
    int16_t i;
    int16_t n;
    int16_t x;
    int16_t y;
    int16_t prev;
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

/* 17:7324 */
void fn_17_7324(void)
{
    int16_t save;
    int16_t kind;
    int16_t idx;
    int16_t t;
    int16_t k;
    char unused[82];
    int16_t r;

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
        t = g_7090[g_9646].f_0b8[g_7090[g_9646].f_018];
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
            kind = g_6e38[1].f_1a.b;
            idx = g_6e38[1].f_1a.a;
        } else if (g_0a76 == 2) {
            kind = g_6e38[0].f_1a.b;
            idx = g_6e38[0].f_1a.a;
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
            if (g_3d50[idx].f_1c == 2) {
                g_9466 = 2;
                g_9468 = 1;
                if (g_92ec[9] != 0)
                    g_9468 = 2;
                for (k = 0; k < 2; k++) {
                    if (g_4d90[g_4ed4[k]].f_12 == g_4d90[idx].f_12)
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

/* 17:193c */
int16_t fn_17_193c(int16_t reset)
{
    int16_t unused;
    int16_t k;
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
        g_5000 = g_6084.right - 320;
        g_5002 = g_6084.top + 30;
        fn_17_30b0(g_93aa, 0x1194L);
        fn_17_55e2(-1);
        g_18b4 = k = 0;
        old = SelectObject(g_13dc, (g_576c + 10)[0]);
        SetStretchBltMode(g_13dc, 2);
        fn_10_9962(0, g_13dc, g_6084.right / 2 - 200, g_5002 + 50, 13, 13, g_39e8[0],
                   g_1df8[2]->f_24, g_1df8[2]->f_24, g_1df8[2]->f_22, g_1df8[2]->f_22, 0xc000caL);
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
        old = SelectObject(g_13dc, (g_576c + 10)[k / 5]);
        SetStretchBltMode(g_13dc, 2);
        fn_10_9962(0, g_13dc, g_6084.right / 2 - 200, g_5002 + 50, 13, 13, g_39e8[0],
                   g_1df8[2]->f_24, g_1df8[2]->f_24, g_1df8[2]->f_22, g_1df8[2]->f_22, 0xc000caL);
        SelectObject(g_13dc, old);
        if (g_9460 != 0 && g_9474 != 0) {
            g_9474 = 0;
            g_5000 = g_6084.right - 320;
            g_5002 = g_6084.top + 30;
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
/* 17:30b0 */
void fn_17_30b0(int16_t id, int32_t v)
{
    int16_t flag;
    int16_t i;
    int16_t size;
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

/* Builds the race / track description text in g_6078 [inferred]. */
/* 17:76e4 */
void fn_17_76e4(void)
{
    int16_t i;
    int16_t j;
    int16_t k;
    int16_t n;
    char buf[200];
    char names[3][10];
    uint16_t best[3][2];

    n = g_9460 ? (g_9468 - 1) / 2 : g_9322;
    lstrcpy(g_6078, "");
    if (g_9460 && ((g_9468 + 1) & 1)) {
        fn_06_8b90((g_9468 - 1) / 2);
        fn_06_8cb2((g_9468 - 1) / 2, g_9646, 0, 0, 1);
        for (i = 0; i < 3; i++)
            for (j = 0; j < 2; j++)
                best[i][j] = 0;
        for (i = 0; i < g_94c8; i++)
            for (j = 0; j < 3; j++)
                for (k = 0; k < 2; k++)
                    if (g_6afc[i].f_32[j][k]
                        && (g_6afc[i].f_32[j][k] < best[j][k] || best[j][k] == 0)) {
                        best[j][k] = g_6afc[i].f_32[j][k];
                        if (k == 0)
                            lstrcpy(names[j], g_6afc[i].f_14[j]);
                    }
        fn_09_95ba(0x823);
        lstrcat(g_6078, "\t185");
        fn_11_4928(2, best[0][1], buf);
        lstrcat(g_6078, buf);
        lstrcat(g_6078, "\t250");
        fn_11_4928(2, best[0][0], buf);
        lstrcat(g_6078, buf);
        lstrcat(g_6078, "\t310");
        fn_11_4928(0, best[1][1], buf);
        lstrcat(g_6078, buf);
        lstrcat(g_6078, "\t370");
        fn_11_4928(0, best[1][0], buf);
        lstrcat(g_6078, buf);
        lstrcat(g_6078, "\t450");
        fn_11_4928(0, best[2][1], buf);
        lstrcat(g_6078, buf);
        lstrcat(g_6078, "\t510");
        fn_11_4928(0, best[2][0], buf);
        lstrcat(g_6078, buf);
        fn_17_42ea(1);
        lstrcat(g_6078, "\t250");
        if (best[0][0])
            lstrcat(g_6078, names[0]);
        lstrcat(g_6078, "\t370");
        if (best[1][0])
            lstrcat(g_6078, names[1]);
        lstrcat(g_6078, "\t510");
        if (best[2][0])
            lstrcat(g_6078, names[2]);
        fn_06_8dfe((g_9468 - 1) / 2);
        fn_06_8eb4();
    } else {
        fn_09_95ba((n + 800) * 2);
        lstrcat(g_6078, g_09ee);
        fn_09_95ba(n * 2 + 0x641);
        lstrcat(g_6078, g_09ee);
        if (g_094e && (g_094e - 1) / 4 == n) {
            fn_17_42ea(1);
            fn_17_42ea(1);
            fn_09_95ba(0x824);
            fn_06_0f1a(g_9ea0, buf);
            lstrcat(g_6078, buf);
            fn_09_95ba(0x825);
            lstrcat(g_6078, g_09ee);
            switch (g_9ea0) {
            case 1:
                fn_09_95ba(0x826);
                break;
            case 5:
                fn_09_95ba(0x827);
                break;
            case 10:
                fn_09_95ba(0x828);
                break;
            }
            lstrcat(g_6078, g_09ee);
            if (g_4ee0[0]) {
                if (!g_4ee0[1])
                    g_4ed4[1] = 0;
                fn_10_a332(g_6078, "button", 0, g_9ebc[n], 0x9db,
                           g_4d90[g_4ed4[j]].f_12 + 10000, g_4ee0[1],
                           g_4d90[g_4ed4[1]].f_12 + 10000);
            }
        }
    }
}

/* 17:7088 */
int16_t fn_17_7088(int16_t a)
{
    int16_t k;
    int16_t i;
    int16_t count;
    int16_t n;
    int16_t t;

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
        count = g_7090[g_9464].cnt + 1;
        n = g_96d2[g_7090[g_9464].f_04e].f_38;
        fn_17_72aa(a, n + 1, 4);
        fn_17_72aa(a, 0, 8);
        for (i = 1; i < g_7090[g_9464].cnt; i++) {
            k = g_7090[g_9464].f_0b8[i];
            fn_17_72aa(a, fn_17_7526(k), 9);
        }
        break;
    case 4:
        if (g_93aa == 13) {
            for (k = 0; k <= g_9316; k++) {
                if (g_1df8[14][k].f_18 == 0 && g_7090[k].flag != 0 &&
                    g_96d2[g_7090[k].f_04e].f_38 == g_9468 - 1) {
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
            if (g_92ec[2] != 0) {
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
            if (g_1df8[14][k].f_18 == 0 && g_7090[k].flag != 0) {
                for (i = 0; i < g_7090[k].cnt; i++) {
                    if (g_7090[k].f_0b8[i] == t) {
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
/* 17:4354 */
void pilot_panel_header(int16_t i)
{
    HFONT font;
    HFONT old;
    COLORREF oldbk;
    COLORREF oldtc;
    char buf[80];
    char unused[60];
    int16_t mood;
    int16_t rel;
    int16_t flag;

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
               g_96d2[g_7090[g_9464].f_04e].f_38 == g_96d2[g_7090[g_9646].f_04e].f_38,
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
/* 17:3ba6 */
void ship_status_lines(int16_t flag)
{
    HFONT font;
    HFONT old;
    COLORREF oldbk;
    COLORREF oldtc;
    char tmp[50];
    char buf[90];
    POINT pt;
    int16_t i;

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
            fn_06_0f1a((&g_7090[g_9464].f_026[0])[i], tmp);
            lstrcat(buf, tmp);
            lstrcat(buf, "%");
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            pt.y += 18;
        }
        if (g_96d2[g_7090[g_9464].f_04e].f_28 != -1) {
            fn_09_955c(0x34b, buf);
            lstrcat(buf, ": ");
            fn_06_0f1a(g_7090[g_9464].f_026[3], tmp);
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
            if (g_96d2[g_7090[g_9464].f_04e].f_38 == g_96d2[g_7090[g_9646].f_04e].f_38) {
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
            if (flow_interactive != 0 && (g_91f8 == 0 || (g_91f8 < 2 && g_9460 != 0))) {
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
        if (flow_interactive == 0 || g_9464 != g_9646 || g_91f8 > 1 || (g_91f8 != 0 && g_9460 == 0)) {
            fn_10_a332(buf, "\x80\x1a\x06", 1, g_7090[g_9464].f_05d + 0xf6,
                       g_7090[g_9464].f_05d > 2, 0x21e021dL);
            TextOut(g_13dc, pt.x, pt.y, buf, lstrlen(buf));
            pt.y += 18;
            fn_10_a332(buf, "\xc0" "E\x04", 1, g_7090[g_9464].f_05e + 0xfa,
                       g_7090[g_9464].f_05e > 2, 0x21e021dL);
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

/* 17:03b2 */
void fn_17_03b2(void)
{
    int16_t k;

    fn_10_744c(0x6e);
    g_9462 = 0;
    if (g_93aa >= 18 && g_9134 == 0)
        g_93aa = 1;
    PatBlt(g_13dc, g_6084.left, g_6084.top, g_6084.right - g_6084.left, g_6084.bottom - g_6084.top, BLACKNESS);
    switch (g_93aa) {
    case 1:
        fn_17_0600(1);
        break;
    case 3:
        if (g_91f8 == 0 || g_9460 != 0)
            fn_17_0d22(1);
        break;
    case 4:
        if ((g_91f8 == 0 && g_92ec[3] != 0) || g_9460 != 0)
            fn_17_1b3e(1, 3);
        break;
    case 5:
        if ((g_094e == 0 && g_91f8 == 1) || g_9460 != 0)
            fn_17_1b3e(1, 7);
        break;
    case 6:
        if (g_92ec[9] != 0)
            fn_17_1b3e(1, 9);
        break;
    case 7:
        if ((g_91f8 == 1 || g_9460 != 0) && g_92ec[2] != 0)
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
            for (k = 0; k < g_9406[8]; k++)
                if (g_3d50[k].f_30 == g_4ed4[0])
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
            for (k = 0; k < g_9406[8]; k++)
                if (g_3d50[k].f_30 == g_4ed4[1])
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
        if (g_947a[7]) {
            ShowWindow(g_947a[7], SW_HIDE);
            ShowWindow(g_947a[7], SW_SHOW);
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
        if (g_947a[7]) {
            ShowWindow(g_947a[7], SW_HIDE);
            ShowWindow(g_947a[7], SW_SHOW);
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

/* Shows the crew portraits one by one, growing in and then shrinking
 * away (briefing step 1) [inferred]. */
/* 17:0600 */
int16_t fn_17_0600(int16_t reset)
{
    HFONT oldfont;
    HFONT hfont;
    char buf[80];
    DWORD oldtext;
    DWORD oldbk;
    int16_t unused;
    int16_t total;
    int16_t left;
    int16_t r;
    int16_t org;
    int16_t sz;
    int16_t step;
    int16_t y;
    int16_t x;

    org = SC(6);
    sz = SC(32);
    if (g_91fc < 7)
        step = 80;
    else
        step = 70;
    if (reset) {
        if (!g_91fc && !g_9460) {
            g_91f8++;
            fn_09_6624();
            g_91f8--;
            g_187a = g_1e50 - 1;
            return 1;
        }
        g_187a = 0;
        g_187e = g_1880 = g_1882 = 0;
        if (g_91fc && g_1df8[0][0].f_18)
            do
                g_1880++;
            while (g_1df8[0][g_1880].f_18 && g_1880 < g_91fe);
    }
    if (g_187a) {
        if (g_187a < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        if (!g_91fc) {
            g_1882 += 3;
            y = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom + 20;
            hfont = CreateFont(0x26, 0x16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
            oldfont = SelectObject(g_13dc, hfont);
            oldbk = SetBkColor(g_13dc, RGB(0, 0, 0));
            SetBkMode(g_13dc, TRANSPARENT);
            SetTextAlign(g_13dc, TA_CENTER);
            oldtext = SetTextColor(g_13dc, RGB(0, 255, 255));
            fn_09_955c(0x143, buf);
            TextOut(g_13dc, (g_6084.right - g_6084.left) / 2 + g_6084.left, (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom + 52,
                    buf, lstrlen(buf));
            SetBkColor(g_13dc, oldbk);
            SetTextColor(g_13dc, oldtext);
            SelectObject(g_13dc, oldfont);
            if (hfont) {
                DeleteObject(hfont);
                hfont = 0;
            }
        } else {
            total = step * g_91fc;
            left = (g_6084.right - total - g_6084.left) / 2;
            x = left - (g_1882 + 4) / 2 + g_187e * step + g_6084.left + 32;
            y = (g_6084.top - g_6084.bottom) / 2 - (g_1882 + 4) / 2 + g_6084.bottom + 52;
            fn_10_9962(0, g_13dc, x, y, g_1882 + 4, g_1882 + 4, g_39e8[13],
                       (sz + org) * g_1880 + org, org, sz, sz, SRCCOPY);
            g_1882 += 3;
            if (g_1882 == 12)
                fn_10_754a(0x13, x, y, 4);
            if (g_1882 > 60) {
                fn_17_0c2e(g_1880, x, y);
                do
                    g_1880++;
                while (g_1880 < g_91fe && g_1df8[0][g_1880].f_18);
                g_187e++;
                g_1882 = 0;
            }
        }
        if (!g_91fc && g_1882 > 10 || g_1880 >= g_91fe) {
            g_1882 = 0;
            g_9462++;
            g_5000 = (g_6084.right - g_6084.left) / 2 + g_6084.left - 265;
            g_5002 = y - 106;
            if (!g_91f8)
                fn_17_30b0(g_93aa, 5000L);
            else
                fn_17_30b0(g_93aa, 3000L);
        }
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            y = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom + 20;
            g_5000 = (g_6084.right - g_6084.left) / 2 + g_6084.left - 265;
            g_5002 = y - 106;
            fn_17_2c5a(1, 1);
            SetStretchBltMode(g_13dc, 3);
            g_1880 = g_187e = 0;
            if (g_91fc && g_1df8[0][0].f_18)
                do
                    g_1880++;
                while (g_1880 < g_91fe && g_1df8[0][g_1880].f_18);
            while (g_1880 < g_91fe) {
                total = step * g_91fc;
                left = (g_6084.right - total - g_6084.left) / 2;
                x = left + g_187e * step + g_6084.left;
                fn_10_9962(0, g_13dc, x, y, 64, 64, g_39e8[13],
                           (sz + org) * g_1880 + org, org, sz, sz, SRCCOPY);
                fn_17_0c2e(g_1880, x, y);
                do
                    g_1880++;
                while (g_1df8[0][g_1880].f_18 && g_1880 < g_91fe);
                g_187e++;
            }
            break;
        }
        if ((r = fn_17_2c5a(0, 0)) == 1) {
            g_91f8++;
            fn_09_6624();
            g_91f8--;
        } else if (r == 2 && !g_9460) {
            g_1880 = 0;
            g_9462++;
            g_1882 = g_1884 = 60;
            fn_10_754a(0x15, x, y, 4);
        }
        break;
    case 2:
        total = step * g_91fe;
        left = (g_6084.right - total - g_6084.left) / 2;
        x = left - (g_1884 + 4) / 2 + g_1880 * step + g_6084.left + 32;
        y = (g_6084.top - g_6084.bottom) / 2 - (g_1882 + 4) / 2 + g_6084.bottom + 52;
        fn_10_9962(0, g_13dc, x, y, g_1884 + 4, g_1884 + 4, g_39e8[13],
                   (sz + org) * g_1880 + org - 2, org - 2, sz + 4, sz + 4, SRCCOPY);
        g_1884 = g_1882;
        g_1882 -= 4;
        if (g_1882 == 48) {
            fn_10_744c(0x6e);
            if (!g_1880)
                fn_10_744c(0x15);
            else
                fn_10_754a(0x15, x, y, 4);
        }
        if (g_1882 <= 0) {
            x = g_1880 * step + left + g_6084.left;
            y = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom + 20;
            PatBlt(g_13dc, x - 6, y, 76, step, BLACKNESS);
            g_1884 = g_1882 = 60;
            if (++g_1880 >= g_91fe)
                g_187a = g_1e50 + 1000;
        }
        break;
    }
    g_9474 = 0;
    return 0;
}

/* Contact animation step (portrait zoom in/out) [inferred]. */
/* 17:0d22 */
int16_t fn_17_0d22(int16_t reset)
{
    POINT pt;
    int16_t sz;
    int16_t b;
    int16_t a;
    int16_t r;
    int16_t unused[2];

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
        b = g_1df8[4]->f_22;
        sz = min(g_188a * 36 / 20, 72);
        if (sz < 72)
            g_188e = g_188a * 2;
        pt.x = g_608c / 2 - sz / 2 - g_188e - 30;
        pt.y = (g_6084.top - g_6084.bottom) / 2 - sz / 2 + g_6084.bottom;
        a = g_1df8[4]->f_24;
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
            a = g_1df8[4]->f_24;
            b = g_1df8[4]->f_22;
            pt.y = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom - 36;
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
        b = g_1df8[4]->f_22;
        sz = min(g_188c * 36 / 20, 72);
        a = g_1df8[4]->f_24;
        if (sz < 72)
            g_188e = g_188a * 2;
        pt.x = g_608c / 2 - sz / 2 - g_188e - 30;
        pt.y = (g_6084.top - g_6084.bottom) / 2 - sz / 2 + g_6084.bottom;
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

/* Grows a sprite on screen while its text types out, then shrinks it
 * again (kind 3, 7, 8 or 9) [inferred]. */
/* 17:1b3e */
int16_t fn_17_1b3e(int16_t reset, int16_t kind)
{
    int16_t y;
    int16_t x;
    int16_t size;
    int16_t sz;
    int16_t org;
    int16_t r;
    int16_t limit;
    int16_t frames;
    int16_t spr;
    int16_t idx;
    int16_t base;

    idx = 0;
    switch (kind) {
    case 3:
        spr = 7;
        limit = 150;
        frames = 18;
        base = 44;
        break;
    case 7:
        spr = 5;
        limit = 190;
        frames = 10;
        base = 40;
        break;
    case 9:
        spr = 22;
        limit = 102;
        frames = 9;
        base = 38;
        break;
    case 8:
        idx = g_946e;
        spr = g_3d50[idx].f_1e;
        limit = 112;
        frames = 16;
        base = g_4d90[g_3d50[idx].f_30].f_08;
        break;
    }
    if (reset) {
        fn_10_744c(0x6e);
        fn_10_744c(0x13);
        g_18b6 = 0;
        g_18c0 = g_18ba = 1;
    }
    if (g_18b6) {
        if (g_18b6 < g_1e50)
            return 1;
        return 0;
    }
    switch (g_9462) {
    case 0:
        sz = g_1df8[kind][idx].f_22;
        size = min(base * g_18ba / 55, base * 2);
        org = g_1df8[kind][idx].f_24;
        if (size < base * 2)
            g_18be = g_18ba;
        x = g_608c / 2 - size / 2 - g_18be - 30;
        y = (g_6084.top - g_6084.bottom) / 2 - size / 2 + g_6084.bottom;
        SetStretchBltMode(g_13dc, 3);
        fn_10_9962(0, g_13dc, x, y, size, size, g_39e8[spr], (org + sz) * (g_18c0 / 2) + org,
                   org, sz, sz, SRCCOPY);
        PatBlt(g_13dc, size + x, y, 2, size, BLACKNESS);
        g_18ba++;
        if (++g_18c0 >= frames * 2)
            g_18c0 = 0;
        if (g_18ba > limit) {
            g_9462++;
            g_5000 = size + x + 90;
            g_5002 = y - 10;
            fn_17_30b0(g_93aa, 5000L);
        }
        break;
    case 1:
        if (g_9460 && g_9474) {
            g_9474 = 0;
            sz = g_1df8[kind][idx].f_22;
            org = g_1df8[kind][idx].f_24;
            size = base * 2;
            x = g_608c / 2 - size / 2 - 140;
            y = (g_6084.top - g_6084.bottom) / 2 - size / 2 + g_6084.bottom;
            g_5000 = x + size + 90;
            g_5002 = y - 10;
            fn_17_2c5a(1, 1);
            SetStretchBltMode(g_13dc, 3);
            fn_10_9962(0, g_13dc, x, y, size, size, g_39e8[spr], (org + sz) * (frames / 2) + org,
                       org, sz, sz, SRCCOPY);
            break;
        }
        if (kind != 3 && kind != 7) {
            sz = g_1df8[kind][idx].f_22;
            size = min(base * g_18ba / 55, base * 2);
            org = g_1df8[kind][idx].f_24;
            if (size < base * 2)
                g_18be = g_18ba;
            x = g_608c / 2 - size / 2 - g_18be - 30;
            y = (g_6084.top - g_6084.bottom) / 2 - size / 2 + g_6084.bottom;
            SetStretchBltMode(g_13dc, 3);
            fn_10_9962(0, g_13dc, x, y, size, size, g_39e8[spr], (org + sz) * (g_18c0 / 2) + org,
                       org, sz, sz, SRCCOPY);
            PatBlt(g_13dc, size + x, y, 2, size, BLACKNESS);
            if (++g_18c0 >= frames * 2)
                g_18c0 = 0;
        }
        if ((r = fn_17_2c5a(0, 0)) == 1)
            fn_10_565a();
        else if (r == 2 && !g_9460) {
            fn_10_744c(0x15);
            g_18bc = g_18ba = 110;
            g_9462++;
        }
        break;
    case 2:
        sz = g_1df8[kind][idx].f_22;
        size = min(base * g_18bc / 55, base * 2);
        org = g_1df8[kind][idx].f_24;
        if (size < base * 2)
            g_18be = g_18ba;
        x = g_608c / 2 - size / 2 - g_18be - 30;
        y = (g_6084.top - g_6084.bottom) / 2 - size / 2 + g_6084.bottom;
        SetStretchBltMode(g_13dc, 3);
        fn_10_9962(0, g_13dc, x, y, size, size, g_39e8[spr], (org + sz) * (g_18c0 / 2) + org - 2,
                   org - 2, sz + 4, sz + 4, SRCCOPY);
        PatBlt(g_13dc, x - 4, y, 4, size, BLACKNESS);
        PatBlt(g_13dc, x - 10, y - 10, size + 10, 10, BLACKNESS);
        g_18bc = g_18ba;
        g_18ba -= 2;
        if (--g_18c0 < 0)
            g_18c0 = frames * 2 - 1;
        if (g_18ba <= 8) {
            PatBlt(g_13dc, x - 4, y - 4, size + 8, size + 8, BLACKNESS);
            g_18b6 = g_1e50 + 1000;
        }
        break;
    }
    g_9474 = 0;
    return 0;
}

/* Animates the pilot portraits flying in and out of the pilot panel [inferred].
 * Returns 1 when the animation is finished or waiting. */
/* 17:20fa */
int16_t fn_17_20fa(int16_t reset, int16_t a, int16_t b)
{
    int16_t h4;
    int16_t h6;
    int16_t size;
    int16_t ha;
    int16_t pc;
    int16_t pe;
    int16_t r;
    int16_t bmp;
    int16_t obj;
    int16_t u16;
    int16_t u18;
    int16_t u1a;
    int16_t h1c;
    int16_t h1e;
    int16_t mult;

    obj = g_9464;
    bmp = g_7090[obj].f_050 + 0x28;
    if (g_90ee < 8)
        mult = 2;
    else
        mult = 3;
    if (reset && g_946c == g_9464 && g_9460) {
        if (g_7090[g_9464].f_0d6 >= 0)
            size = g_6e24[g_7090[g_9464].f_0d6].f_7a;
        else
            size = g_1df8[14][g_9464].f_22;
        g_9462 = 1;
        pc = g_1df8[14][g_9464].f_22;
        pe = g_1df8[14][g_9464].f_24;
        g_5000 = (size + 13) * 3 + g_1906.x;
        g_5002 = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom - 0x56;
        SetStretchBltMode(g_13dc, 3);
        PatBlt(g_13dc, g_5000, g_5002, g_6084.right - g_5000, g_6084.bottom - g_5002, BLACKNESS);
        PatBlt(g_13dc, g_6084.left, g_5002, g_5000 - 100, g_6084.bottom - g_5002, BLACKNESS);
        fn_10_9962(0, g_13dc, g_1906.x, g_1906.y, mult * size, mult * size, g_39e8[bmp],
                   pe, pe, pc, pc, SRCCOPY);
        pilot_panel_header(g_9464);
        fn_17_30b0(g_93aa, 3000L);
        return 0;
    }
    if (reset) {
        g_91f8++;
        fn_09_6624();
        g_91f8--;
        if (b)
            g_9462 = 0;
        else if (a) {
            if (++g_9464 > g_9316) {
                g_18c2 = g_1e50 + 100;
                return 1;
            }
            g_9462 = 0;
        } else
            g_9464 = 0;
        if (g_9464 > g_9316) {
            g_18c2 = g_1e50 + 100;
            return 1;
        }
        if (g_7090[g_9464].f_0d6 != -1)
            size = g_6e24[g_7090[g_9464].f_0d6].f_7a;
        else
            size = g_1df8[14][g_9464].f_22;
        g_1df8[14][g_9464].f_1a = 1;
        fn_11_b09c(g_9464, 1);
        g_1df8[14][g_9464].f_1a = 0;
        g_18c6 = 0;
        g_18fa = 1;
        g_18ca = 20;
        g_18ce = 80;
        g_18e2 = 25;
        g_18e6 = mult * 100 - 25L;
        g_18ea = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom;
        g_18ee = 0;
        g_18f2 = 400;
        g_18f6 = 0;
        g_18de = 0;
        g_18da = 0;
        g_18d2 = (g_6084.left + 40) * 10;
        g_18d6 = g_18d2 + (g_6084.right - g_6084.left) * 11 / 3;
        g_1902 = g_18d2 / 10;
        g_1904 = g_18ea;
        fn_10_754a(0x13, 100, HI16(g_90ea) / 2, 4);
        g_18c2 = 0;
    }
    if (g_39e8[bmp] == 0)
        return 1;
    if (g_18c2 != 0) {
        if (g_18c2 < g_1e50)
            return 1;
        return 0;
    }
    if (g_7090[g_9464].f_0d6 != -1)
        size = g_6e24[g_7090[g_9464].f_0d6].f_7a;
    else
        size = g_1df8[14][g_9464].f_22;
    switch (g_9462) {
    case 0:
        h4 = g_18e6 * g_18d2 / g_18d6 + g_18e2;
        h1e = h4 / 2 * g_18fa;
        h1c = g_18d2 * g_18ce / g_18d6 + g_18ca;
        if (g_18de == 0)
            h6 = g_18f2 / 100;
        else
            h6 = (g_18f6 * g_18da / g_18de + g_18f2) / 100;
        pc = g_1df8[14][g_9464].f_22;
        pe = g_1df8[14][g_9464].f_24;
        g_1904 = g_18ee * g_18d2 / g_18d6 + g_18ea;
        ha = size * h4 / 100;
        g_1906.y = g_1904 - ha / 2;
        g_1906.x = ha * h1c / -100 / 2 + g_1902;
        SetStretchBltMode(g_13dc, 3);
        fn_10_9962(0, g_13dc, g_1906.x, g_1906.y, ha * h1c / 100, ha, g_39e8[bmp],
                   (pe + pc) * h6 + pe, pe, pc, pc, SRCCOPY);
        PatBlt(g_13dc, g_1906.x - 20, g_1906.y - 20, 20, ha + 20, BLACKNESS);
        g_1902 = (g_18d2 += h1e) / 10;
        g_18da++;
        if (g_18d2 >= g_18d6 && g_18de <= g_18da) {
            g_1df8[14][obj].f_1a = 1;
            fn_11_b09c(obj, 0);
            g_1df8[14][obj].f_1a = 0;
            g_18c6++;
            g_18ca = 100;
            g_18ce = 0;
            g_18e2 = mult * 100;
            g_18e6 = 0;
            g_18ea = g_1904;
            g_18ee = 0;
            g_18f2 = 400;
            g_18f6 = -400;
            g_18da = 0;
            g_18de = 10;
            g_18fa = 0;
        }
        if (g_18c6 > 1) {
            g_18fe = g_18d6;
            g_18c6 = 0;
            g_18ca = 100;
            g_18ce = 0;
            g_18e2 = 0;
            g_18e6 = 0;
            g_18ea = g_1904;
            g_18ee = 0;
            g_18f2 = 0;
            g_18f6 = 400;
            g_18da = 0;
            g_18de = 10;
            g_9462++;
            g_5000 = ha + g_1906.x + 39;
            g_5002 = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom - 0x56;
            if (g_91f8 && g_9464 == g_9646)
                fn_17_30b0(g_93aa, 3500L);
            else
                fn_17_30b0(g_93aa, 5000L);
            pilot_panel_header(g_9464);
        }
        break;
    case 1:
        g_946c = g_9464;
        if (g_9460 && g_9474) {
            g_9474 = 0;
            pc = g_1df8[14][g_946c].f_22;
            pe = g_1df8[14][g_946c].f_24;
            g_5000 = (size + 13) * 3 + g_1906.x;
            g_5002 = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom - 0x56;
            pilot_panel_header(g_9464);
            fn_17_2c5a(1, 1);
            SetStretchBltMode(g_13dc, 3);
            fn_10_9962(0, g_13dc, g_1906.x, g_1906.y, mult * size, mult * size, g_39e8[bmp],
                       pe, pe, pc, pc, SRCCOPY);
            break;
        }
        if ((r = fn_17_2c5a(0, 0)) == 1)
            fn_10_565a();
        else if (r == 2 && !g_9460) {
            g_9462++;
            PatBlt(g_13dc, g_5000, g_5002, g_6084.right - g_5000, g_6084.bottom - g_5002, BLACKNESS);
            PatBlt(g_13dc, g_6084.left, g_5002, g_5000 - 100, g_6084.bottom - g_5002, BLACKNESS);
        }
        break;
    case 2:
        h4 = g_18fe * g_18e6 / g_18d6 + g_18e2;
        h1e = h4 / 2 * g_18fa;
        h1c = g_18fe * g_18ce / g_18d6 + g_18ca;
        if (g_18de == 0)
            h6 = g_18f2 / 100;
        else
            h6 = (g_18f6 * g_18da / g_18de + g_18f2) / 100;
        pc = g_1df8[14][g_9464].f_22;
        pe = g_1df8[14][g_9464].f_24;
        g_1904 = g_18fe * g_18ee / g_18d6 + g_18ea;
        ha = size * h4 / 100;
        g_1906.y = g_1904 - ha / 2;
        g_1906.x = ha * h1c / -100 / 2 + g_1902;
        SetStretchBltMode(g_13dc, 3);
        fn_10_9962(0, g_13dc, g_1906.x, g_1906.y, ha * h1c / 100, ha, g_39e8[bmp],
                   (pe + pc) * h6 + pe, pe, pc, pc, SRCCOPY);
        PatBlt(g_13dc, g_1906.x - 20, g_1906.y - 20, ha * h1c / 100 + 20, 20, BLACKNESS);
        PatBlt(g_13dc, g_1906.x - 20, ha + g_1906.y, ha * h1c / 100 + 20, 20, BLACKNESS);
        PatBlt(g_13dc, g_1906.x - 20, g_1906.y - 20, 20, ha + 20, BLACKNESS);
        g_1902 = (g_18d2 += h1e) / 10;
        g_18da++;
        g_18fe += h1e;
        if (g_18fe >= g_18d6 && g_18de <= g_18da) {
            g_1df8[14][obj].f_1a = 1;
            fn_11_b09c(obj, 1);
            g_1df8[14][obj].f_1a = 0;
            g_18fa = 1;
            g_18ca = 100;
            g_18ce = -80;
            g_18e2 = mult * 100;
            g_18e6 = 50 - g_18e2;
            g_18ea = g_1904;
            g_18ee = 0;
            g_18f2 = 400;
            g_18f6 = 0;
            g_18fe = 0;
            g_18d6 = g_6084.right * 10 - g_18d2 - 200;
            g_18de = 0;
            g_18da = 0;
            g_18c6++;
            if (g_18c6 <= 1)
                fn_10_754a(0x15, g_6084.right / 2 + 250, HI16(g_90ea) / 2, 4);
            else {
                g_9464++;
                PatBlt(g_13dc, g_6084.left, g_6084.top, g_6084.right - g_6084.left, g_6084.bottom - g_6084.top, BLACKNESS);
                if (g_9464 <= g_9316) {
                    g_1df8[14][g_9464].f_1a = 1;
                    fn_11_b09c(g_9464, 1);
                    g_1df8[14][g_9464].f_1a = 0;
                    g_9462 = 0;
                    g_18c6 = 0;
                    g_18fa = 1;
                    g_18ca = 20;
                    g_18ce = 80;
                    g_18e2 = 25;
                    g_18e6 = mult * 100 - 25L;
                    g_18ea = (g_6084.top - g_6084.bottom) / 2 + g_6084.bottom;
                    g_18ee = 0;
                    g_18f2 = 400;
                    g_18f6 = 0;
                    g_18de = 0;
                    g_18da = 0;
                    g_18d2 = (g_6084.left + 40) * 10;
                    g_18d6 = g_18d2 + (g_6084.right - g_6084.left) * 11 / 3;
                    g_1902 = g_6084.left + 40;
                    g_1904 = g_18ea;
                    fn_10_754a(0x13, 100, HI16(g_90ea) / 2, 4);
                } else
                    g_18c2 = g_1e50 + 1000;
            }
        }
        break;
    }
    g_9474 = 0;
    return 0;
}

/* 17:16cc */
int16_t fn_17_16cc(int16_t reset, int16_t n)
{
    int16_t r;
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
        g_5000 = g_6084.right - 280;
        g_5002 = g_6084.top + 60;
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
        fn_10_9962(0, g_13dc, g_6084.right / 2 - g_18ac.x - 200, g_5002 + 50, g_18ac.x * 2, g_18ac.y * 2,
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
            fn_10_9962(0, g_13dc, g_6084.right / 2 - g_18ac.x - 200, g_5002 + 50, g_18ac.x * 2, g_18ac.y * 2,
                       hdc, 0, 0, g_18ac.x, g_18ac.y, SRCCOPY);
            SelectPalette(hdc, oldpal, 0);
            SelectObject(hdc, old);
            DeleteDC(hdc);
            g_9474 = 0;
            g_5000 = g_6084.right - 280;
            g_5002 = g_6084.top + 60;
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
/* 17:8572 */
void fn_17_8572(HWND hDlg)
{
    int16_t unused0;
    char s1[110];
    char s2[110];
    int16_t i;
    int16_t w;
    int16_t h;
    int16_t unused1;
    int16_t unused2;
    int16_t y;
    RECT rc;
    int16_t unused3;
    int16_t unused4;
    int16_t unused5;
    int16_t unused6;

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
    SendMessage(g_947a[4], CB_GETLBTEXT, g_9468, (LPARAM)(LPSTR)s2);
    lstrcpy(s1, s2);
    lstrcat(s1, " - ");
    SendMessage(g_947a[3], CB_GETLBTEXT, g_9466, (LPARAM)(LPSTR)s2);
    lstrcat(s1, s2);
    SendMessage(GetDlgItem(hDlg, 0x199), 0x40d, -1, (LPARAM)(LPSTR)s1);
    SetFocus(GetDlgItem(hDlg, 0x195));
}

/* WM_CREATE handler of the contact window: layout and buttons [inferred]. */
/* 17:6116 */
void fn_17_6116(void)
{
    RECT rc;
    char buf[80];
    int16_t i;
    HPALETTE old;

    GetClientRect(g_9460, &rc);
    g_6084.top = 0;
    g_607c.left = g_6084.left = 6;
    g_607c.right = g_6084.right = rc.right - g_6084.left;
    g_607c.top = g_6084.bottom = rc.bottom - 67;
    g_607c.bottom = g_607c.top + 180;
    if (g_93ae) {
        DeleteObject(g_93ae);
        g_93ae = 0;
    }
    g_93ae = CreateRectRgn(g_6084.left, g_6084.top, g_6084.right, g_6084.bottom);
    for (i = 0; i < 9; i++) {
        if (g_947a[i]) {
            DestroyWindow(g_947a[i]);
            g_947a[i] = 0;
        }
    }
    g_6094[0] = CreateFont(12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    g_6094[1] = CreateFont(14, 7, 0, 0, 730, 0, 0, 0, 0, 0, 0, 2, 0x22, g_06b0);
    if (g_6084.right > 670) {
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
    if (g_947a[7])
        SetFocus(g_947a[7]);
    else
        SetFocus(g_947a[4]);
    g_608c = g_6084.right;
    g_608e = g_6084.bottom;
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

/* Window procedure of the race/records window [inferred]. */
/* 17:5782 */
LRESULT fn_17_5782(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT wr;
    RECT rc;
    HGDIOBJ oldbrush;
    int16_t r;
    HGDIOBJ oldpen;
    char text[80];
    char buf[120];
    DWORD oldtc;
    DWORD oldbk;
    HGDIOBJ oldfont;
    int16_t u10e;
    int16_t u110;
    DRAWITEMSTRUCT *dis;
    int16_t u116;
    int16_t res;
    int16_t xt;
    int16_t idx;

    switch (msg) {
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case WM_CREATE:
        g_1920 = GetCurrentTime();
        g_191e = GetStockObject(2);
        EnableWindow(g_0016, 0);
        g_90f4 = 7;
        g_9460 = hwnd;
        fn_17_6116();
        break;
    case WM_MOVE:
        GetWindowRect(g_9460, &wr);
        if (wr.left != g_1dc4 || wr.top != g_1dc6) {
            CopyRect((LPRECT)&g_1dc4, &wr);
            g_0128 = 1;
        }
        break;
    case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT *)lParam;
        if (dis->itemID == -1)
            fn_17_92b8(dis);
        else
            switch (dis->itemAction) {
            case ODA_DRAWENTIRE:
                fn_17_9308(dis);
                break;
            case ODA_SELECT:
                fn_17_90d2(dis);
                break;
            case ODA_FOCUS:
                fn_17_92b8(dis);
                break;
            }
        return 1;
    case WM_MEASUREITEM: {
        TEXTMETRIC tm;
        HDC dc;
        HGDIOBJ old;
        MEASUREITEMSTRUCT *mis;

        mis = (MEASUREITEMSTRUCT *)lParam;
        dc = GetDC(g_0016);
        old = SelectObject(dc, g_6094[0]);
        GetTextMetrics(dc, &tm);
        SelectObject(dc, old);
        ReleaseDC(g_0016, dc);
        mis->itemHeight = max(tm.tmExternalLeading + tm.tmHeight + 3, 14);
        if (g_9466 == 7)
            mis->itemHeight *= 2;
        break;
    }
    case WM_CTLCOLOR:
        if (g_0024 && (r = fn_02_1a5a(msg, wParam, lParam)) != 0)
            return (UINT)r;
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case WM_COMMAND:
        switch (wParam) {
        case 100:
            g_9468--;
            fn_17_67e6();
            break;
        case 101:
            res = DialogBox(g_9212, MAKEINTRESOURCE(0x194), g_9460, (DLGPROC)fn_17_8418);
            if (res) {
                SendMessage(g_947a[3], 0x40e, g_9466 = res / 100 - 1, 0L);
                fn_17_65da();
                g_9468 = res % 100;
                fn_17_67e6();
                SetFocus(g_947a[4]);
            }
            break;
        case 102:
            g_9468++;
            fn_17_67e6();
            break;
        case 105:
            PostMessage(g_9460, WM_CLOSE, 0, 0L);
            break;
        case 107:
            idx = (int16_t)SendMessage(g_947a[5], 0x407, 0, 0L);
            SendMessage(g_947a[5], 0x408, idx, (LPARAM)(LPSTR)buf);
            g_9466 = buf[lstrlen(buf) - 2] - '1';
            SendMessage(g_947a[3], 0x40e, g_9466, 0L);
            fn_17_65da();
            g_9468 = buf[lstrlen(buf) - 1] - '0';
            fn_17_67e6();
            break;
        case 103:
            fn_17_6742(g_9460, wParam, (HWND)LOWORD(lParam), HIWORD(lParam));
            break;
        case 104:
            fn_17_6792(g_9460, wParam, (HWND)LOWORD(lParam), HIWORD(lParam));
            break;
        case 108:
            if (g_9466 == 8)
                switch (HIWORD(lParam)) {
                case 2:
                    g_9468 = (int16_t)SendMessage((HWND)LOWORD(lParam), 0x409, 0, 0L);
                    g_9468++;
                    fn_17_67e6();
                    break;
                }
            break;
        }
        break;
    case WM_PAINT: {
        int16_t x;

        if (GetCurrentTime() > g_1920 + 500 || g_93aa == 16 || g_93aa == 2) {
            fn_10_744c(20);
            g_9474 = 1;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        GetClientRect(hwnd, &rc);
        g_13dc = hdc = BeginPaint(hwnd, &ps);
        fn_11_1774(2, 0, -5, g_1dc8 - g_1dc4 - 2, g_1dca - GetSystemMetrics(SM_CYCAPTION) - g_1dc6 - 2);
        if (g_93aa == 16 && g_9468 == 0) {
            fn_11_1774(4, x = 0x27, 0x4c, 0x26f, 0x124);
            fn_11_1774(-1, x, 0x4c, 0x26f, 0x5a);
            fn_09_955c(0x80e, buf);
            fn_09_8bec(g_13dc, 0x3b, 0x4d, 0xd, 0, 0, buf);
            fn_09_955c(0x80f, buf);
            fn_09_8bec(g_13dc, 0x10d, 0x4d, 0xd, 0, 0, buf);
            fn_09_955c(0x810, buf);
            fn_09_8bec(g_13dc, 0x14b, 0x4d, 0xd, 0, 0, buf);
            fn_09_955c(0x811, buf);
            fn_09_8bec(g_13dc, 0x1c6, 0x4d, 0xd, 0, 0, buf);
            fn_09_955c(0x812, buf);
            fn_09_8bec(g_13dc, 0x202, 0x4d, 0xd, 0, 0, buf);
        }
        if (g_9460) {
            if (g_93aa == 2 && ((g_9468 + 1) & 1)) {
                fn_11_1774(4, x = 0x14, 0x4c, 0x264, 0x124);
                fn_11_1774(-1, x, 0x4c, 0x264, 0x5a);
                fn_09_955c(0x80e, buf);
                fn_09_8bec(g_13dc, 0x28, 0x4d, 0xd, 0, 0, buf);
                fn_09_955c(0x813, buf);
                fn_09_8bec(g_13dc, 0xcd, 0x4d, 0xd, 0, 0, buf);
                fn_09_955c(0x816, buf);
                fn_09_8bec(g_13dc, 0x10e, 0x4d, 0xd, 0, 0, buf);
                fn_09_955c(0x814, buf);
                fn_09_8bec(g_13dc, 0x14a, 0x4d, 0xd, 0, 0, buf);
                fn_09_955c(0x816, buf);
                fn_09_8bec(g_13dc, 0x186, 0x4d, 0xd, 0, 0, buf);
                fn_09_955c(0x815, buf);
                fn_09_8bec(g_13dc, 0x1d6, 0x4d, 0xd, 0, 0, buf);
                fn_09_955c(0x816, buf);
                fn_09_8bec(g_13dc, 0x212, 0x4d, 0xd, 0, 0, buf);
            }
        }
        oldpen = SelectObject(g_13dc, CreatePen(PS_SOLID, 1, RGB(192, 192, 192)));
        MoveTo(g_13dc, 6, rc.bottom - 0x20);
        LineTo(g_13dc, rc.right - 6, rc.bottom - 0x20);
        DeleteObject(SelectObject(g_13dc, oldpen));
        oldbrush = SelectObject(g_13dc, GetStockObject(2));
        PatBlt(g_13dc, 6, rc.bottom - 0x1f, rc.right - 0xc, 0x19, PATCOPY);
        SelectObject(g_13dc, oldbrush);
        oldfont = SelectObject(g_13dc, g_6094[1]);
        oldbk = SetBkColor(g_13dc, RGB(128, 128, 128));
        SetBkMode(g_13dc, TRANSPARENT);
        SetTextAlign(g_13dc, 0);
        oldtc = SetTextColor(g_13dc, PALETTERGB(0, 0, 0));
        fn_09_955c(0x211, text);
        TextOut(g_13dc, xt = g_6084.right > 0x29e ? rc.left + 0xca : rc.left + 0x84,
                rc.bottom - 0x1a, text, lstrlen(text));
        SetTextAlign(g_13dc, 2);
        fn_09_955c(0x212, text);
        if (g_6084.right <= 0x29e) {
            text[3] = ':';
            text[4] = 0;
        }
        TextOut(g_13dc, rc.right - 0xe4, rc.bottom - 0x1a, text, lstrlen(text));
        SetBkColor(g_13dc, oldbk);
        SetTextColor(g_13dc, oldtc);
        SelectObject(g_13dc, oldfont);
        if (g_948c) {
            if (g_920e)
                x = SelectPalette(g_13dc, (HPALETTE)g_920e, 0);
            fn_17_0000(1, 0);
            if (x)
                SelectPalette(g_13dc, (HPALETTE)x, 0);
        }
        g_13dc = 0;
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_CLOSE:
        if (g_9460) {
            fn_06_717a();
            fn_17_6036();
            SetActiveWindow(g_0016);
            EnableWindow(g_0016, 1);
            g_90f4 = 1;
            DestroyWindow(g_9460);
            g_9460 = 0;
            fn_10_7480(-3, 1);
            SetActiveWindow(g_0016);
        }
        break;
    }
    return 0;
}
