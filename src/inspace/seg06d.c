/* INSPACE.EXE segment 6 (selector 1028): 6:1c72-6:5d58, one source file. */
#include "inspace.h"
#include <dos.h>
#include <shellapi.h>

int far fn_06_4190(char far *dir);
int far fn_06_4650(char far *dir);
int far fn_06_4748(char far *dir);
void far pascal fn_06_47e8(DRAWITEMSTRUCT far *dis);
void far pascal fn_06_4ea8(DRAWITEMSTRUCT far *dis);

int far fn_06_301a(void);
void far fn_06_1e68(int start);
int far fn_06_4f46(void);
int far fn_06_5260(char far *s);
void far fn_06_5318(void);
void far fn_06_5524(void);

extern HWND g_0d1e;
extern int g_0010;
extern int g_90ea;
extern int g_94ac;
extern int flow_interactive;        /* DS:95bc */

void far fn_10_7480(int a, int b);
void far fn_15_6558(int n, char far *buf);
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
extern DWORD g_1e50;
extern long g_1c34;
extern int g_0d26;
extern int g_94b4;
extern int g_94b6;
extern int g_0d24;
extern int g_0d20;
extern int g_0d1c;
extern char g_0d18[];
extern RECT g_6af0;
extern HINSTANCE g_8e66;
extern int g_90f4;
extern int g_9134;
extern long g_1d40;
extern HGDIOBJ g_6aec[2];
extern HGDIOBJ g_94ba;
extern int g_049e;
void far fn_10_7db8(void);
void far fn_11_1774(int c, int l, int t, int r, int b);
void far fn_11_3fd4(LPSTR s, int mode);
void far fn_09_8bec(HDC hdc, int x, int y, int size, int width, UINT align, LPSTR s);
extern char g_6a24[];
extern int g_920c;
extern int g_94a4;
int far fn_16_5f0e(char far *a, char far *b);
#pragma pack(1)
typedef struct {                /* 0x297 bytes, far array at DS:69f4 */
    char p000[0x152];
    char f152[0x1d0 - 0x152];
    char f1d0;
    char p1d1[0x297 - 0x1d1];
} REC_297;
#pragma pack()
extern REC_297 far *g_69f4;
extern char g_6990[];
extern HGDIOBJ g_6aee;
extern int g_94a6;
extern int g_94c0;
extern int g_94c2;
extern HINSTANCE g_9210;
void far fn_09_0352(HDC hdc, int x, int flags, int w, int h, LPSTR name);
extern HGDIOBJ g_90fe;
int far fn_06_5cbc(int i, char far *s);
extern struct find_t g_69f8;
void far fn_06_0f1a(int v, char far *buf);

/* @addr 6:2dba */
void far fn_06_2dba(int mode)
{
    int a;
    int b;

    switch (mode) {
    case 0:
        a = b = 0;
        break;
    case 1:
        a = SW_SHOW;
        b = SW_HIDE;
        break;
    case 2:
        a = SW_HIDE;
        b = SW_SHOW;
        break;
    }
    ShowWindow(GetDlgItem(g_0d1e, 0x8c), a);
    ShowWindow(GetDlgItem(g_0d1e, 0x8d), a);
    ShowWindow(GetDlgItem(g_0d1e, 0x8e), a);
    ShowWindow(GetDlgItem(g_0d1e, 0x8f), a);
    ShowWindow(GetDlgItem(g_0d1e, 0x90), a);
    ShowWindow(GetDlgItem(g_0d1e, 0x93), b);
    ShowWindow(GetDlgItem(g_0d1e, 0x91), b);
    ShowWindow(GetDlgItem(g_0d1e, 0x92), b);
    ShowWindow(GetDlgItem(g_0d1e, 0x94), b);
}

/* Opens the navigation window, or shows it if it already exists [inferred]. */
/* @addr 6:1c72 */
void far fn_06_1c72(int a)
{
    DWORD style;
    char title[80];

    g_0d24 = 1;
    if (!IsWindow(g_0d1e)) {
        g_0d20 = a;
        g_94b4 = g_0d1c;
        g_0d18[0] = g_94ac + 'C';
        g_6af0.left = GetPrivateProfileInt(g_9690, "NavLeft", 30, g_96a9);
        g_6af0.top = GetPrivateProfileInt(g_9690, "NavTop", 30, g_96a9);
        g_6af0.right = GetPrivateProfileInt(g_9690, "NavRight", 560, g_96a9);
        g_6af0.bottom = GetPrivateProfileInt(g_9690, "NavBottom", 350, g_96a9);
        LoadString(g_9212, 0x85c, title, 70);
        CreateWindow("IS_NAV", title, style = 0x10cc0000L,
                     g_6af0.left, g_6af0.top, g_6af0.right, g_6af0.bottom,
                     g_0016, 0, g_8e66, NULL);
        if (g_13dc && g_90f4 != 2)
            PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
        if (g_9134 && !flow_interactive)
            fn_06_1e68(1);
    } else
        ShowWindow(g_0d1e, SW_SHOW);
}

/* @addr 6:1d9a */
void far fn_06_1d9a(void)
{
    char str[100];
    char buf[80];
    char unused[46];

    fn_10_7480(-1, 1);
    LoadString(g_9212, 0x85d, str, 100);
    fn_15_6558(g_94ac, buf);
    lstrcat(str, buf);
    lstrcat(str, "...");
    fn_10_94c4(0, 6, RGB(0, 255, 0), g_90ea / 2, g_0010 / 2 - 40, str);
    if (!flow_interactive) {
        LoadString(g_9212, 0x85e, str, 100);
        fn_10_94c4(0, 6, RGB(0, 255, 0), g_90ea / 2, g_0010 / 2, str);
    }
}

/* @addr 6:1e68 */
void far fn_06_1e68(int start)
{
    int x;
    char buf[100];
    int r;

    if (start)
        g_1c34 = GetCurrentTime() + 1200;
    g_0d26 = 0;
    if ((DWORD)g_1c34 < g_1e50) {
        g_1c34 = g_1e50 + 600;
        if (!fn_06_301a()) {
            if (g_94b6 > g_94b4) {
                x = 0;
                if ((r = fn_06_5260(buf)) == 1)
                    x = fn_06_4f46();
                g_94b4++;
                SendMessage(GetDlgItem(g_0d1e, 0x65), 0x407, g_94b4, 0L);
                fn_06_5318();
            } else
                g_0d26 = 1;
        }
        if (g_94b6 - 1 <= g_94b4)
            g_0d26 = 1;
    }
}

/* Saves the navigation window position and closes it [inferred]. */
/* @addr 6:2ebc */
void far fn_06_2ebc(void)
{
    char buf[10];
    int i;

    if (g_0d1e) {
        g_1d40 = GetCurrentTime() + 1000;
        fn_06_0f1a(g_6af0.left, buf);
        WritePrivateProfileString(g_9690, "NavLeft", buf, g_96a9);
        fn_06_0f1a(g_6af0.right - g_6af0.left, buf);
        WritePrivateProfileString(g_9690, "NavRight", buf, g_96a9);
        fn_06_0f1a(g_6af0.top, buf);
        WritePrivateProfileString(g_9690, "NavTop", buf, g_96a9);
        fn_06_0f1a(g_6af0.bottom - g_6af0.top, buf);
        WritePrivateProfileString(g_9690, "NavBottom", buf, g_96a9);
        for (i = 0; i < 2; i++) {
            if (g_6aec[i]) {
                DeleteObject(g_6aec[i]);
                g_6aec[i] = 0;
            }
        }
        if (g_94ba) {
            DeleteObject(g_94ba);
            g_94ba = 0;
        }
        if (!g_049e) {
            fn_10_7db8();
            EnableWindow(g_0016, TRUE);
        }
        if (g_0d1e) {
            DestroyWindow(g_0d1e);
            g_0d1e = 0;
        }
        if (!g_049e) {
            ShowWindow(g_0016, SW_SHOW);
            SetActiveWindow(g_0016);
        }
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_06_301a(void)
{
    return g_0d26;
}

/* @addr 6:4118 */
void far fn_06_4118(char far *s, int a, int b, int c)
{
    int unused1;
    int unused2;
    int n;

    lstrcat(s, "0");
    n = lstrlen(s);
    s[n - 1] += a;
    lstrcat(s, "0");
    n = lstrlen(s);
    s[n - 1] += b;
    lstrcat(s, "0");
    n = lstrlen(s);
    s[n - 1] += c;
}

/* Nonzero when the directory holds no .exe file [inferred]. */
/* Draws the icon of program dir\\name into the 32x32 bitmap g_94ba
 * [inferred]. */
/* @addr 6:4368 */
void far fn_06_4368(char far *dir, char far *name)
{
    HICON icon;
    HDC saved;
    HDC memdc;
    HGDIOBJ old;
    HPALETTE pal;
    int rel;
    char path[130];
    int n;
    int res;

    rel = 0;
    saved = g_13dc;
    if (!saved) {
        rel = 1;
        g_13dc = GetDC(g_0d1e);
    }
    if (g_920e)
        pal = SelectPalette(g_13dc, g_920e, 0);
    lstrcpy(path, dir);
    res = 0;
    if (lstrlen(path) == 1) {
        switch (path[0]) {
        case 'R':
            res = 0x6a;
            break;
        case 'S':
            res = 0x69;
            break;
        case 'D':
            res = 0x6b;
            break;
        }
    }
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, name);
    n = (int)ExtractIcon(g_8e66, path, -1);
    if (*name)
        n = n < 1 ? 1 : n;
    g_94a6 += n;
    if (!g_94c0) {
        if (*name)
            icon = ExtractIcon(g_8e66, path, 0);
        else if (res)
            icon = LoadIcon(g_9210, MAKEINTRESOURCE(res));
        else
            icon = 0;
        if (icon > 1 || !*name || !g_94c2) {
            if (icon > 1 || !*name)
                g_94c0 = 1;
            memdc = CreateCompatibleDC(g_13dc);
            if (!g_94ba)
                g_94ba = CreateCompatibleBitmap(g_13dc, 32, 32);
            old = SelectObject(memdc, g_94ba);
            if (!g_94c2 || icon > 1)
                PatBlt(memdc, 0, 0, 32, 32, BLACKNESS);
            if (icon > 1)
                DrawIcon(memdc, 0, 0, icon);
            if (icon < 2 && g_94a6 && !g_94c2)
                fn_09_0352(memdc, 0, 0, 32, 0, name);
            g_94c2 = 1;
            SelectObject(memdc, old);
            DeleteDC(memdc);
            if (icon > 1)
                DestroyIcon(icon);
        }
    }
    if (pal)
        SelectPalette(g_13dc, pal, 0);
    if (rel)
        ReleaseDC(g_0d1e, g_13dc);
    g_13dc = saved;
}

/* Lists the files matching mask in dir into list box 0x6b; returns their
 * count [inferred]. */
/* @addr 6:420a */
int far fn_06_420a(char far *dir, char far *mask)
{
    struct find_t ft;
    int r;
    int n;
    int flag;
    char path[120];
    char line[100];
    char unused[130];

    flag = 0;
    lstrcpy(path, dir);
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, mask);
    r = _dos_findfirst(path, 0, &ft);
    if (r)
        return 0;
    n = 1;
    fn_06_4368(dir, ft.name);
    lstrcpy(line, "");
    lstrcat(line, ft.name);
    lstrcat(line, " ");
    lstrcat(line, "0");
    line[lstrlen(line) - 1] += flag;
    SendMessage(GetDlgItem(g_0d1e, 0x6b), LB_ADDSTRING, 0, (LONG)(LPSTR)line);
    while (_dos_findnext(&ft) == 0) {
        n++;
        fn_06_4368(dir, ft.name);
        lstrcpy(line, "");
        lstrcat(line, ft.name);
        lstrcat(line, " ");
        lstrcat(line, "0");
        line[lstrlen(line) - 1] += flag;
        SendMessage(GetDlgItem(g_0d1e, 0x6b), LB_ADDSTRING, 0, (LONG)(LPSTR)line);
    }
    return n;
}

/* Classifies the directory dir: 3 = a game directory, 2/1 = in the list
 * of known directories, 0 = other [inferred]. */
/* @addr 6:3f4c */
int far fn_06_3f4c(char far *path)
{
    int i;
    int r;
    char dir[110];
    char s1[60];
    char s2[40];

    lstrcpy(dir, path);
    if (dir[lstrlen(dir) - 1] != '\\')
        lstrcat(dir, "\\");
    r = 0;
    if (!g_920c && flow_interactive) {
        LoadString(g_9212, 0x2e4, s1, 40);
        LoadString(g_9212, 0x2e3, s2, 40);
        lstrcat(s2, "\\");
        lstrcat(s1, s2);
        if (fn_16_5f0e(dir, s2)) {
            r = 3;
            if (fn_16_5f0e(dir, s1))
                r = 0;
        }
        LoadString(g_9212, 0x2e0, s2, 40);
        lstrcat(s2, "\\");
        if (fn_16_5f0e(dir, s2))
            r = 3;
        if (r == 3)
            return 3;
    }
    if (g_920c != -1 && g_920c != 2) {
        LoadString(g_9212, 0x2f8, s2, 40);
        lstrcat(s2, "\\");
        if (fn_16_5f0e(dir, s2))
            r = 3;
        if (r == 3)
            return 3;
    }
    for (i = 0; i < g_94a4; i++) {
        if (!lstrcmp(g_69f4[i].f152, dir)) {
            if (g_69f4[i].f1d0 == 2)
                r = 2;
            else
                r = 1;
            break;
        }
    }
    return r;
}

/* @addr 6:4190 */
int far fn_06_4190(char far *dir)
{
    struct find_t ft;
    int r;
    char path[120];

    lstrcpy(path, dir);
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, "*.exe");
    r = _dos_findfirst(path, 0, &ft);
    if (r)
        return 0;
    return 1;
}

/* @addr 6:45be */
int far fn_06_45be(char far *dir)
{
    int root;

    if (lstrcmp("C:\\", dir) == 0)
        root = 1;
    else
        root = 0;
    if (dir[lstrlen(dir) - 1] != '\\')
        lstrcat(dir, "\\");
    if (fn_06_4190(dir))
        return 1;
    if (root)
        return 0;
    if (!fn_06_4748(dir))
        return 0;
    if (fn_06_4650(dir))
        return 1;
    return 0;
}

/* Nonzero when some subdirectory of dir holds an .exe file [inferred]. */
/* @addr 6:4650 */
int far fn_06_4650(char far *dir)
{
    struct find_t ft;
    int r;
    char path[120];

    if (dir[lstrlen(dir) - 1] != '\\')
        lstrcat(dir, "\\");
    lstrcpy(path, dir);
    lstrcat(path, "*.*");
    r = _dos_findfirst(path, _A_RDONLY | _A_SYSTEM | _A_SUBDIR, &ft);
    if ((ft.attrib & _A_SUBDIR) && ft.name[0] != '.') {
        lstrcpy(path, dir);
        lstrcat(path, ft.name);
        if (fn_06_4190(path))
            return 1;
    }
    while (_dos_findnext(&ft) == 0) {
        if ((ft.attrib & _A_SUBDIR) && ft.name[0] != '.') {
            lstrcpy(path, dir);
            lstrcat(path, ft.name);
            if (fn_06_4190(path))
                return 1;
        }
    }
    return 0;
}

/* Nonzero when dir has a subdirectory [inferred]. */
/* @addr 6:4748 */
int far fn_06_4748(char far *dir)
{
    struct find_t ft;
    int unused;
    int r;
    char path[120];

    lstrcpy(path, dir);
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, "*.*");
    r = _dos_findfirst(path, _A_RDONLY | _A_SYSTEM | _A_SUBDIR, &ft);
    if (r == 0 && (ft.attrib & _A_SUBDIR) && ft.name[0] != '.')
        return 1;
    while (_dos_findnext(&ft) == 0) {
        if ((ft.attrib & _A_SUBDIR) && ft.name[0] != '.')
            return 1;
    }
    return 0;
}

/* Draws the bottom panel of the navigation window [inferred]. */
/* @addr 6:5b4c */
void far fn_06_5b4c(HDC hdc, int frame)
{
    int rel;
    HPALETTE pal;
    RECT rc;
    HDC saved;
    HDC memdc;
    HGDIOBJ old;
    POINT pt;

    GetClientRect(g_0d1e, &rc);
    rel = 0;
    if (!hdc) {
        rel = 1;
        hdc = GetDC(g_0d1e);
    }
    saved = g_13dc;
    g_13dc = hdc;
    if (g_920e)
        pal = SelectPalette(g_13dc, g_920e, 0);
    fn_11_1774(-1, rc.left, rc.bottom - 25, rc.right, rc.bottom);
    fn_11_3fd4(g_6a24, 3);
    fn_09_8bec(g_13dc, 5, rc.bottom - 20, 14, 0, 0, g_6a24);
    pt.y = 0x55;
    pt.x = rc.right - 0x60;
    if (frame) {
        fn_11_1774(4, pt.x, 0x55, pt.x + 0x48, 0x9d);
        PatBlt(g_13dc, pt.x + 4, pt.y + 4, 64, 64, BLACKNESS);
    }
    memdc = CreateCompatibleDC(g_13dc);
    old = SelectObject(memdc, g_94ba);
    StretchBlt(g_13dc, pt.x + 4, pt.y + 4, 64, 64, memdc, 0, 0, 32, 32, SRCCOPY);
    SelectObject(memdc, old);
    DeleteDC(memdc);
    if (pal)
        SelectPalette(g_13dc, pal, 0);
    if (rel)
        ReleaseDC(g_0d1e, g_13dc);
    g_13dc = saved;
}

/* @addr 6:5cbc */
int far fn_06_5cbc(int i, char far *s)
{
    int k;
    int d;

    SendMessage(GetDlgItem(g_0d1e, 0x6b), 0x40a, i, (LONG)s);
    d = s[lstrlen(s) - 1] - '0';
    for (k = 0; k < 2; k++)
        s[lstrlen(s) - 1] = 0;
    if (s[0] == ' ')
        for (k = 0; k < lstrlen(s); k++)
            s[k] = s[k + 1];
    return d;
}

/* Owner-draw paint of a directory tree item (list box 0x65): indent by
 * depth, tree lines, folder icon, name [inferred]. */
/* count and buf2 are block-scoped: their slots go after CL's temporary for
 * the `buf[lstrlen(buf) - 1] = 0` store, which then shares a slot. */
/* @addr 6:49c0 */
void far pascal fn_06_49c0(DRAWITEMSTRUCT far *dis)
{
    RECT rc;
    RECT rc2;
    HBRUSH brush;
    HGDIOBJ oldfont;
    int unused1;
    HDC memdc;
    int unused2;
    HGDIOBJ oldbmp;
    char buf[80];
    COLORREF oldcolor;
    int k;
    int c2;
    int c1;
    int x;
    int sx;
    int sx0;
    int depth;
    int flag2;
    int flag1;
    int d2;

    oldcolor = GetTextColor(dis->hDC);
    memdc = CreateCompatibleDC(dis->hDC);
    oldbmp = SelectObject(memdc, g_6aec[0]);
    CopyRect(&rc, &dis->rcItem);
    CopyRect(&rc2, &dis->rcItem);
    SendMessage(dis->hwndItem, 0x40a, dis->itemID, (LONG)(LPSTR)buf);
    sx0 = 90;
    depth = buf[lstrlen(buf) - 3] - '0';
    x = depth * 16 - 6;
    if (dis->itemID == 0)
        for (k = x = sx = 0; k < lstrlen(buf); k++)
            buf[k] = buf[k + 1];
    c1 = buf[lstrlen(buf) - 2] - '0';
    c2 = buf[lstrlen(buf) - 1] - '0';
    for (k = 0; k < 3; k++)
        buf[lstrlen(buf) - 1] = 0;
    switch (c1) {
    case 0:
    case 2:
        sx = 0;
        break;
    case 1:
        sx = 15;
        break;
    }
    switch (c2) {
    case 0:
        break;
    case 1:
        sx += 30;
        break;
    case 2:
        sx += 60;
        break;
    case 3:
        sx += 105;
        break;
    }
    rc2.left += x;
    brush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    FillRect(dis->hDC, &rc, brush);
    DeleteObject(brush);
    if (dis->itemState & ODS_SELECTED) {
        brush = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
        FillRect(dis->hDC, &rc2, brush);
        DeleteObject(brush);
    }
    oldfont = SelectObject(dis->hDC, g_90fe);
    if (dis->itemID) {
        int count;

        flag2 = flag1 = 0;
        count = (int)SendMessage(dis->hwndItem, 0x40c, 0, 0L);
        if (dis->itemID >= count - 1) {
            flag2 = 1;
            flag1 = 1;
        } else if (depth > 1) {
            char buf2[80];

            SendMessage(dis->hwndItem, 0x40a, dis->itemID + 1, (LONG)(LPSTR)buf2);
            d2 = buf2[lstrlen(buf2) - 3] - '0';
            if (d2 != depth)
                flag1 = 1;
        }
        MoveTo(dis->hDC, rc.left + 4, rc.top);
        if (flag2)
            LineTo(dis->hDC, rc.left + 4, rc.top + 6);
        else
            LineTo(dis->hDC, rc.left + 4, rc.bottom);
        if (depth) {
            MoveTo(dis->hDC, depth * 14 + rc.left - 10, rc.top);
            if (flag1)
                LineTo(dis->hDC, depth * 14 + rc.left - 10, rc.top + 6);
            else
                LineTo(dis->hDC, depth * 14 + rc.left - 10, rc.bottom);
            MoveTo(dis->hDC, depth * 14 + rc.left - 10, rc.top + 6);
            LineTo(dis->hDC, depth * 14 + rc.left - 5, rc.top + 6);
        }
    }
    BitBlt(dis->hDC, x + rc.left + 1, rc.top + 1, 15, 11, memdc, sx0, 0, SRCAND);
    BitBlt(dis->hDC, x + rc.left + 1, rc.top + 1, 15, 11, memdc, sx, 0, SRCPAINT);
    if (dis->itemState & ODS_SELECTED)
        SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
    else
        SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
    SetBkMode(dis->hDC, TRANSPARENT);
    fn_11_3fd4(buf, 0);
    k = lstrlen(buf);
    TextOut(dis->hDC, x + rc.left + 18, rc.top, buf, lstrlen(buf));
    SelectObject(dis->hDC, oldfont);
    SelectObject(memdc, oldbmp);
    DeleteDC(memdc);
    SetTextColor(dis->hDC, oldcolor);
}

/* Owner-draw list item paint [inferred]. */
/* @addr 6:47e8 */
void far pascal fn_06_47e8(DRAWITEMSTRUCT far *dis)
{
    RECT rc;
    HBRUSH brush;
    HGDIOBJ oldfont;
    HDC memdc;
    HGDIOBJ oldbmp;
    char buf[80];
    int unused;
    int kind;
    COLORREF oldcolor;

    if (dis->CtlID == 0x65) {
        fn_06_49c0(dis);
        return;
    }
    oldcolor = GetTextColor(dis->hDC);
    memdc = CreateCompatibleDC(dis->hDC);
    oldbmp = SelectObject(memdc, g_6aee);
    CopyRect(&rc, &dis->rcItem);
    if (dis->itemState & ODS_SELECTED)
        brush = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
    else
        brush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    kind = fn_06_5cbc(dis->itemID, buf);
    FillRect(dis->hDC, &rc, brush);
    oldfont = SelectObject(dis->hDC, g_90fe);
    BitBlt(dis->hDC, rc.left + 1, rc.top + 1, 11, 12, memdc, 22, 0, SRCAND);
    switch (kind) {
    case 1:
        SetTextColor(dis->hDC, RGB(0, 0, 255));
        break;
    case 2:
        SetTextColor(dis->hDC, RGB(255, 0, 0));
        break;
    }
    BitBlt(dis->hDC, rc.left + 1, rc.top + 1, 11, 12, memdc, 0, 0, SRCPAINT);
    if (dis->itemState & ODS_SELECTED)
        SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
    else
        SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
    SetBkMode(dis->hDC, TRANSPARENT);
    fn_11_3fd4(buf, 0);
    TextOut(dis->hDC, rc.left + 15, rc.top, buf, lstrlen(buf));
    SelectObject(dis->hDC, oldfont);
    DeleteObject(brush);
    SelectObject(memdc, oldbmp);
    DeleteDC(memdc);
    SetTextColor(dis->hDC, oldcolor);
}

/* Owner-draw list item focus [inferred]. */
/* @addr 6:4e04 */
void far pascal fn_06_4e04(DRAWITEMSTRUCT far *dis)
{
    RECT rc;
    char buf[100];
    int d;
    int x;

    CopyRect(&rc, &dis->rcItem);
    if (dis->CtlID == 0x65) {
        if (dis->itemID == 0)
            x = 0;
        else {
            SendMessage(dis->hwndItem, 0x40a, dis->itemID, (LONG)(LPSTR)buf);
            d = buf[lstrlen(buf) - 3] - '0';
            x = d * 16 - 6;
        }
        rc.left += x;
    }
    if (dis->itemID == -1 || (dis->itemState & ODS_FOCUS))
        DrawFocusRect(dis->hDC, &rc);
    else
        fn_06_4ea8(dis);
}

/* @addr 6:4ea8 */
void far pascal fn_06_4ea8(DRAWITEMSTRUCT far *dis)
{
    RECT rc;
    char buf[100];
    int d;
    int x;

    fn_06_47e8(dis);
    CopyRect(&rc, &dis->rcItem);
    if (dis->CtlID == 0x65) {
        if (dis->itemID == 0)
            x = 0;
        else {
            SendMessage(dis->hwndItem, 0x40a, dis->itemID, (LONG)(LPSTR)buf);
            d = buf[lstrlen(buf) - 3] - '0';
            x = d * 16 - 6;
        }
        rc.left += x;
    }
    if (dis->itemState & ODS_FOCUS)
        DrawFocusRect(dis->hDC, &rc);
}

/* Marks the selected tree entry with '1' and removes its deeper
 * children [inferred: collapses a directory]. */
/* @addr 6:511c */
void far fn_06_511c(void)
{
    int i;
    int sel;
    int depth;
    int d;
    int unused1;
    int count;
    char buf[114];
    HWND hwnd;

    hwnd = GetDlgItem(g_0d1e, 0x65);
    SendMessage(hwnd, WM_SETREDRAW, 0, 0L);
    sel = (int)SendMessage(hwnd, LB_GETCURSEL, 0, 0L);
    SendMessage(hwnd, LB_GETTEXT, sel, (LONG)(LPSTR)buf);
    buf[lstrlen(buf) - 2] = '1';
    SendMessage(hwnd, LB_DELETESTRING, sel, 0L);
    SendMessage(hwnd, LB_INSERTSTRING, sel, (LONG)(LPSTR)buf);
    SendMessage(hwnd, LB_SETCURSEL, sel, 0L);
    depth = buf[lstrlen(buf) - 3] - '0';
    count = (int)SendMessage(hwnd, LB_GETCOUNT, 0, 0L);
    sel++;
    for (i = sel; i < count; i++) {
        SendMessage(hwnd, LB_GETTEXT, sel, (LONG)(LPSTR)buf);
        d = buf[lstrlen(buf) - 3] - '0';
        if (d <= depth)
            break;
        SendMessage(hwnd, LB_DELETESTRING, sel, 0L);
    }
    SendMessage(hwnd, WM_SETREDRAW, 1, 0L);
}

/* Expands the selected tree entry: marks it with '2' and inserts its
 * subdirectories below it; returns 1 if any were added [inferred]. */
/* @addr 6:4f46 */
int far fn_06_4f46(void)
{
    int sel;
    int depth;
    int r;
    int a;
    int b;
    int old;
    char buf[110];
    HWND hwnd;

    old = g_94b6;
    hwnd = GetDlgItem(g_0d1e, 0x65);
    SendMessage(hwnd, WM_SETREDRAW, 0, 0L);
    sel = (int)SendMessage(hwnd, LB_GETCURSEL, 0, 0L);
    SendMessage(hwnd, LB_GETTEXT, sel, (LONG)(LPSTR)buf);
    buf[lstrlen(buf) - 2] = '2';
    SendMessage(hwnd, LB_DELETESTRING, sel, 0L);
    SendMessage(hwnd, LB_INSERTSTRING, sel, (LONG)(LPSTR)buf);
    SendMessage(hwnd, LB_SETCURSEL, sel, 0L);
    depth = buf[lstrlen(buf) - 3] - '0';
    sel++;
    lstrcpy(buf, g_6990);
    lstrcat(buf, "*.*");
    r = _dos_findfirst(buf, _A_RDONLY | _A_SYSTEM | _A_SUBDIR, &g_69f8);
    do {
        if ((g_69f8.attrib & _A_SUBDIR) && g_69f8.name[0] != '.') {
            lstrcpy(buf, g_6990);
            lstrcat(buf, g_69f8.name);
            if (fn_06_45be(buf)) {
                a = 0;
                if (fn_06_4748(buf) && fn_06_4650(buf))
                    a = 1;
                b = fn_06_3f4c(buf);
                lstrcpy(buf, g_69f8.name);
                fn_06_4118(buf, depth + 1, a, b);
                SendMessage(hwnd, LB_INSERTSTRING, sel, (LONG)(LPSTR)buf);
                g_94b6++;
            }
        }
    } while (_dos_findnext(&g_69f8) == 0);
    SendMessage(hwnd, WM_SETREDRAW, 1, 0L);
    if (old < g_94b6)
        return 1;
    return 0;
}

/* @addr 6:5260 */
int far fn_06_5260(char far *s)
{
    int k;
    int sel;
    int d;

    sel = (int)SendMessage(GetDlgItem(g_0d1e, 0x65), 0x409, 0, 0L);
    if (sel == 0) {
        lstrcpy(s, "C:\\");
        d = s[lstrlen(s) - 2] - '0';
    } else {
        SendMessage(GetDlgItem(g_0d1e, 0x65), 0x40a, sel, (LONG)s);
        d = s[lstrlen(s) - 2] - '0';
        for (k = 0; k < 3; k++)
            s[lstrlen(s) - 1] = 0;
    }
    return d;
}

/* Builds the path of the selected tree entry into g_6990 and refills
 * the file list [inferred]. */
/* @addr 6:5318 */
void far fn_06_5318(void)
{
    char buf[100];
    char tmp[100];
    char path[100];
    int lvl;
    int d;
    int i;
    int k;
    int sel;
    int depth;
    int dd;
    int r;
    int found;

    SendMessage(GetDlgItem(g_0d1e, 0x6b), WM_SETREDRAW, 0, 0L);
    SendMessage(GetDlgItem(g_0d1e, 0x6b), LB_RESETCONTENT, 0, (LONG)(LPSTR)"");
    r = fn_06_5260(path);
    sel = (int)SendMessage(GetDlgItem(g_0d1e, 0x65), LB_GETCURSEL, 0, 0L);
    SendMessage(GetDlgItem(g_0d1e, 0x65), LB_GETTEXT, sel, (LONG)(LPSTR)buf);
    depth = buf[lstrlen(buf) - 3] - '0';
    if (depth > 1 && sel != 0) {
        d = depth;
        i = sel - 1;
        for (lvl = 1; lvl < d; lvl++) {
            found = 0;
            do {
                SendMessage(GetDlgItem(g_0d1e, 0x65), LB_GETTEXT, i, (LONG)(LPSTR)buf);
                dd = buf[lstrlen(buf) - 3] - '0';
                if (depth - dd == lvl) {
                    for (k = 0; k < 3; k++)
                        buf[lstrlen(buf) - 1] = 0;
                    lstrcat(buf, "\\");
                    lstrcpy(tmp, buf);
                    lstrcat(tmp, path);
                    lstrcpy(path, tmp);
                    found = 1;
                }
                i--;
            } while (!found);
        }
    }
    if (!sel)
        lstrcpy(g_6990, path);
    else {
        lstrcpy(g_6990, g_0d18);
        lstrcat(g_6990, path);
        lstrcat(g_6990, "\\");
    }
    fn_06_5524();
    SendMessage(GetDlgItem(g_0d1e, 0x6b), WM_SETREDRAW, 1, 0L);
    SetFocus(GetDlgItem(g_0d1e, 0x65));
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_5524(void)
{
}

extern int g_94b8;
int far fn_02_1a5a(int a, int b, long c);
void far fn_02_190a(DWORD ctx);
void far fn_06_23d4(void);

/* Window procedure of the load/save dialog window [inferred]. */
/* @addr 6:1f22 */
LRESULT far pascal fn_06_1f22(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    int u26;
    int y;
    RECT u2a;
    RECT rc;
    DRAWITEMSTRUCT far *dis;
    UINT cmd;
    int r;
    MINMAXINFO far *mm;
    char u46[120];
    TEXTMETRIC tm;
    HDC dc;
    HGDIOBJ oldfont;

    switch (msg) {
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case WM_CREATE:
        g_0d1e = hwnd;
        fn_06_23d4();
        break;
    case WM_DRAWITEM:
        dis = (DRAWITEMSTRUCT far *)lParam;
        if (dis->itemID == -1)
            fn_06_4e04(dis);
        else
            switch (dis->itemAction) {
            case ODA_DRAWENTIRE:
                fn_06_4ea8(dis);
                break;
            case ODA_SELECT:
                fn_06_47e8(dis);
                break;
            case ODA_FOCUS:
                fn_06_4e04(dis);
                break;
            }
        return 1;
    case WM_MEASUREITEM: {
        MEASUREITEMSTRUCT far *mis;

        dc = GetDC(g_0016);
        oldfont = SelectObject(dc, g_90fe);
        GetTextMetrics(dc, &tm);
        SelectObject(dc, oldfont);
        ReleaseDC(g_0016, dc);
        (mis = (MEASUREITEMSTRUCT far *)lParam)->itemHeight =
            max(tm.tmHeight + tm.tmExternalLeading + 3, 14);
        break;
    }
    case WM_CTLCOLOR:
        if (g_0024 && (r = fn_02_1a5a(msg, wParam, lParam)) != 0)
            return (UINT)r;
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case WM_GETMINMAXINFO:
        mm = (MINMAXINFO far *)lParam;
        mm->ptMinTrackSize.x = 560;
        mm->ptMinTrackSize.y = 350;
        break;
    case WM_SIZE:
        GetWindowRect(g_0d1e, &g_6af0);
        GetClientRect(g_0d1e, &rc);
        MoveWindow(GetDlgItem(g_0d1e, 1), rc.right - 105, 5, 90, 26, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x70), rc.right - 105, 40, 90, 26, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x65), 0, 0, 160, rc.bottom - 26, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x6b), 164, 0, rc.right - 284, rc.bottom - 26, TRUE);
        y = rc.bottom - 155;
        MoveWindow(GetDlgItem(g_0d1e, 0x8c), rc.right - 110, y, 102, 122, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x93), rc.right - 110, y, 102, 122, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x8d), rc.right - 97, y + 18, 80, g_94b8 * 4 + 30, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x91), rc.right - 99, y + 18, 83, (g_94b8 + 10) * 3, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x8e), rc.right - 97, y + 43, 80, (g_94b8 + 10) * 3, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x92), rc.right - 99, y + 43, 83, (g_94b8 + 10) * 3, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x8f), rc.right - 97, y + 68, 80, (g_94b8 + 10) * 3, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x90), rc.right - 97, y + 93, 80, (g_94b8 + 5) * 6, TRUE);
        MoveWindow(GetDlgItem(g_0d1e, 0x94), rc.right - 99, y + 68, 83, (g_94b8 + 5) * 6, TRUE);
        break;
    case WM_MOVE:
        GetWindowRect(g_0d1e, &g_6af0);
        break;
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        GetClientRect(hwnd, &rc);
        fn_06_5b4c(hdc = BeginPaint(hwnd, &ps), 1);
        EndPaint(hwnd, &ps);
        break;
    case WM_COMMAND: {
        int res;

        switch (wParam) {
        case 0x65:
            if (HIWORD(lParam) == 2) {
                char buf[100];

                res = fn_06_5260(buf);
                if (res == 1)
                    fn_06_4f46();
                else if (res == 2)
                    fn_06_511c();
            } else if (HIWORD(lParam) == 1) {
                int v;

                v = (int)SendMessage(GetDlgItem(g_0d1e, 0x65), 0x409, 0, 0L);
                if (v != g_94b4) {
                    g_94b4 = v;
                    fn_06_5318();
                }
            }
            break;
        case 0x70:
            fn_02_190a(5L);
            break;
        case IDOK:
            if (!fn_06_301a()) {
                char buf[100];

                res = fn_06_5260(buf);
                if (res == 1)
                    fn_06_4f46();
                else if (res == 2)
                    fn_06_511c();
            }
            break;
        }
        break;
    }
    case WM_SYSCOMMAND:
        switch (cmd = wParam & 0xfff0) {
        case SC_CLOSE:
            PostMessage(g_0016, WM_SYSCOMMAND, SC_CLOSE, 0L);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        break;
    }
    return 0;
}

int far fn_10_6d38(LPCSTR s);
int far fn_02_1a7a(int a);
void far fn_10_744c(int a);
void far fn_06_37ca(void);

/* Creates the child controls of the load/save dialog window [inferred]. */
/* @addr 6:23d4 */
void far fn_06_23d4(void)
{
    int u4;
    int h;
    int sel;
    int ua;
    RECT rc;
    HWND hwnd;
    HDC hdc;
    char test[] = "Test";
    char buf[40];
    HGDIOBJ oldfont;

    EnableWindow(g_0016, FALSE);
    if (!g_6aec[0])
        g_6aec[0] = fn_10_6d38("FLDR");
    if (!g_6aee)
        g_6aee = fn_10_6d38("FILES");
    GetClientRect(g_0d1e, &rc);

    LoadString(g_9212, 0x85f, buf, 40);
    hwnd = CreateWindow("button", buf, 0x50030000L, rc.right - 90, 15, 90, 26,
                        g_0d1e, (HMENU)1, g_8e66, NULL);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x860, buf, 40);
    hwnd = CreateWindow("button", buf, 0x50010000L, rc.right - 90, 51, 90, 26,
                        g_0d1e, (HMENU)0x70, g_8e66, NULL);
    fn_02_1a7a(hwnd);
    hwnd = CreateWindow("listbox", "", 0x50b30153L, 0, 0, 160, rc.bottom - 26,
                        g_0d1e, (HMENU)0x65, g_8e66, NULL);
    SendMessage(GetDlgItem(g_0d1e, 0x65), 0x415, 200, 0L);
    fn_02_1a7a(hwnd);
    hwnd = CreateWindow("listbox", "", 0x50a30b53L, 164, 0, rc.right - 264, rc.bottom - 26,
                        g_0d1e, (HMENU)0x6b, g_8e66, NULL);
    SendMessage(GetDlgItem(g_0d1e, 0x6b), 0x416, 95, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x861, buf, 40);
    hwnd = CreateWindow("button", buf, 0x50000007L, rc.right - 90, 120, 90, 40,
                        g_0d1e, (HMENU)0x8c, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 1L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x862, buf, 40);
    hwnd = CreateWindow("button", buf, 0x50000007L, rc.right - 90, 120, 90, 40,
                        g_0d1e, (HMENU)0x93, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 1L);
    fn_02_1a7a(hwnd);

    hdc = GetDC(g_0d1e);
    oldfont = SelectObject(hdc, g_90fe);
    h = HIWORD(GetTextExtent(hdc, test, 4));
    SelectObject(hdc, oldfont);
    ReleaseDC(g_0016, hdc);

    hwnd = CreateWindow("combobox", "", 0x50210003L, rc.right - 60, 120, 60,
                        ((g_94b8 = h) + 10) * 3, g_0d1e, (HMENU)0x8d, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x863, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, hdc = 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x864, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x865, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x866, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    SendMessage(hwnd, CB_SETCURSEL, sel = GetPrivateProfileInt(g_9690, "Racers", 1, g_96a9), 0L);

    hwnd = CreateWindow("combobox", "", 0x50210003L, rc.right - 60, 120, 60,
                        (g_94b8 + 10) * 3, g_0d1e, (HMENU)0x91, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x867, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x868, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x869, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    SendMessage(hwnd, CB_SETCURSEL, sel = GetPrivateProfileInt(g_9690, "Duelers", 0, g_96a9), 0L);

    hwnd = CreateWindow("combobox", "", 0x50210003L, rc.right - 60, 150, 60,
                        (g_94b8 + 10) * 3, g_0d1e, (HMENU)0x8e, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x86a, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x86b, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x86c, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    SendMessage(hwnd, CB_SETCURSEL, sel = GetPrivateProfileInt(g_9690, "RaceDiff", 0, g_96a9), 0L);

    hwnd = CreateWindow("combobox", "", 0x50210003L, rc.right - 60, 150, 60,
                        (g_94b8 + 10) * 3, g_0d1e, (HMENU)0x92, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x86a, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x86b, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x86c, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    SendMessage(hwnd, CB_SETCURSEL, sel = GetPrivateProfileInt(g_9690, "DuelDiff", 0, g_96a9), 0L);

    hwnd = CreateWindow("combobox", "", 0x50210003L, rc.right - 60, 180, 60,
                        (g_94b8 + 10) * 3, g_0d1e, (HMENU)0x8f, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x86d, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x86e, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x86f, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    SendMessage(hwnd, CB_SETCURSEL, sel = GetPrivateProfileInt(g_9690, "RaceLaps", 1, g_96a9), 0L);

    hwnd = CreateWindow("combobox", "", 0x50210003L, rc.right - 60, 180, 60,
                        (g_94b8 + 5) * 6, g_0d1e, (HMENU)0x90, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x870, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x871, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x872, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x873, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x874, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x875, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    SendMessage(hwnd, CB_SETCURSEL, sel = GetPrivateProfileInt(g_9690, "RaceOpp", 2, g_96a9), 0L);

    hwnd = CreateWindow("combobox", "", 0x50210003L, rc.right - 60, 180, 60,
                        (g_94b8 + 5) * 6, g_0d1e, (HMENU)0x94, g_8e66, NULL);
    SendMessage(hwnd, WM_SETFONT, g_90fe, 0L);
    fn_02_1a7a(hwnd);
    LoadString(g_9212, 0x876, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x877, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x872, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x873, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x878, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    LoadString(g_9212, 0x879, buf, 40);
    SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPSTR)buf);
    SendMessage(hwnd, CB_SETCURSEL, sel = GetPrivateProfileInt(g_9690, "DuelOpp", 2, g_96a9), 0L);

    fn_06_37ca();
    fn_06_5318();
    if (g_0d20) {
        fn_10_744c(0x6e);
        fn_10_744c(0x4d);
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_37ca(void)
{
}
