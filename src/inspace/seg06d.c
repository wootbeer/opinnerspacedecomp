/* INSPACE.EXE segment 6 (selector 1028): 6:1c72-6:5d58, one source file. */
#include "inspace.h"
#include <dos.h>

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
void far fn_06_4118(char far *s, char a, char b, char c)
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
/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_4368(char far *dir, char far *name)
{
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

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far pascal fn_06_47e8(DRAWITEMSTRUCT far *dis)
{
    dis->CtlID = 0;
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

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_06_4f46(void)
{
    return g_0d26;
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

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_5318(void)
{
    g_0d26 = 0;
}
