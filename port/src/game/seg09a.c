/* INSPACE.EXE segment 9 (selector 1040), 9:0000-0ac4: one source file
 * (functions near-call each other) [inferred]. */
#include "game.h"

/* 9:0000 */
void fn_09_0000(int16_t max)
{
    char path[128];
    int16_t r;

    g_9204 = max;
    g_9206 = g_9200 = g_9202 = 0;
    g_69f4[g_94a2].f_1d0 = 2;
    lstrcpy(path, g_38c8);
    lstrcat(path, "*.exe");
    for (r = _dos_findfirst(path, _A_RDONLY, &g_3948); r == 0; r = _dos_findnext(&g_3948)) {
        if (g_9206 > 9)
            goto doneexe;
        lstrcpy(path, g_38c8);
        lstrcat(path, g_3948.name);
        fn_09_0156(path);
    }
doneexe:
    lstrcpy(path, g_38c8);
    lstrcat(path, "*.dll");
    for (r = _dos_findfirst(path, _A_RDONLY, &g_3948); r == 0; r = _dos_findnext(&g_3948)) {
        if (g_9206 > 9)
            goto donedll;
        lstrcpy(path, g_38c8);
        lstrcat(path, g_3948.name);
        fn_09_0156(path);
    }
donedll:
    if (g_9202 && g_69f4[g_94a2].f_1d0 != 1)
        g_69f4[g_94a2].f_1d0 = 0;
    g_91fe = g_91fc = g_91fa = min(g_9206, g_9204);
    g_9204 = 8;
}

/* 9:0156 */
void fn_09_0156(LPSTR file)
{
    int16_t i;
    int16_t n;
    int16_t slot;
    int16_t w;
    int16_t h;
    HICON icon;

    w = 32;
    h = 6;
    n = (int16_t)ExtractIcon(g_8e66, file, -1);
    if (n) {
        for (i = 0; g_9206 <= 9 && i < n; i++) {
            if (fn_09_0ac4(g_9200, 0))
                g_9200++;
            else {
                slot = fn_09_094c();
                if (slot == -1)
                    return;
                icon = ExtractIcon(g_8e66, file, i);
                if ((UINT)icon > 1) {
                    PatBlt((HDC)g_3a02, (h + w) * slot + h, h, w, w, BLACKNESS);
                    DrawIcon((HDC)g_3a02, (h + w) * slot + h, h, icon);
                    DestroyIcon(icon);
                }
                if (fn_09_08da((h + w) * slot + h, h))
                    fn_09_0278(0, slot);
                else
                    fn_09_09b0(slot);
            }
        }
    } else {
        n = (int16_t)ExtractIcon(g_8e66, file, 0);
        if (n == 0)
            fn_09_0278(0, -1);
        else
            fn_09_0278(0x107, -1);
    }
}

/* 9:0278 */
void fn_09_0278(UINT kind, int16_t slot)
{
    int16_t i;
    int16_t j;
    int16_t flags;
    int16_t w;
    int16_t h;
    int16_t ok;
    int16_t unused;
    char name[12];
    char ext[6];

    w = 32;
    h = 6;
    lstrcpy(name, g_3948.name);
    lstrcpy(ext, ".DLL");
    ok = 1;
    for (i = 0; i < 4; i++) {
        j = lstrlen(name) + i - 4;
        if (name[j] != ext[i])
            ok = 0;
    }
    name[lstrlen(name) - 4] = 0;
    flags = 32;
    switch (kind) {
    case 0x106:
    case 0x107:
        flags = 0;
    }
    if (slot == -1) {
        slot = fn_09_094c();
        if (slot == -1)
            return;
    }
    fn_09_0352((HDC)g_3a02, (h + w) * slot + h, flags, w, h, name);
    fn_09_09b0(slot);
}

/* Draws a drive/file icon at (x, y) with its caption: name without a
 * 4-character extension [inferred]. */
/* 9:0352 */
void fn_09_0352(HDC hdc, int16_t x, int16_t flags, int16_t w, int16_t y, LPSTR name)
{
    HGDIOBJ oldfont;
    HFONT hfont;
    DWORD tc;
    DWORD bk;
    int16_t unused;
    HGDIOBJ oldbrush;
    HGDIOBJ oldpen;
    char drv[10];
    char buf[110];

    lstrcpy(buf, name);
    if (lstrlen(buf) > 4 && buf[lstrlen(buf) - 4] == '.')
        buf[lstrlen(buf) - 4] = 0;
    if (hdc == 0)
        drv[1] = 0;
    PatBlt(hdc, x, y, w, w, BLACKNESS);
    if (flags) {
        oldbrush = SelectObject(hdc, GetStockObject(GRAY_BRUSH));
        PatBlt(hdc, x, y, 32, 21, PATCOPY);
        SelectObject(hdc, CreateSolidBrush(0x800000L));
        PatBlt(hdc, x, y, 32, 9, PATCOPY);
        DeleteObject(SelectObject(hdc, GetStockObject(LTGRAY_BRUSH)));
        PatBlt(hdc, x, y, 8, 8, PATCOPY);
        SelectObject(hdc, oldbrush);
        oldpen = SelectObject(hdc, GetStockObject(WHITE_PEN));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, x, y);
        LineTo(hdc, x + 32, y);
        SelectObject(hdc, CreatePen(PS_SOLID, 1, 0xc0c0c0L));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, w + x - 1, y + 20);
        LineTo(hdc, w + x - 1, y);
        DeleteObject(SelectObject(hdc, GetStockObject(BLACK_PEN)));
        MoveTo(hdc, x + 1, y + 8);
        LineTo(hdc, x + 8, y + 8);
        LineTo(hdc, x + 8, y + 1);
        MoveTo(hdc, x + 1, y + 5);
        LineTo(hdc, x + 7, y + 5);
        SelectObject(hdc, CreatePen(PS_SOLID, 1, 0x808080L));
        MoveTo(hdc, x + 1, y + 3);
        LineTo(hdc, x + 7, y + 3);
        DeleteObject(SelectObject(hdc, oldpen));
        SetPixel(hdc, x + 1, y + 4, 0);
        SetPixel(hdc, x + 6, y + 4, 0);
    } else {
        oldpen = SelectObject(hdc, GetStockObject(WHITE_PEN));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, x, y);
        LineTo(hdc, x + 32, y);
        SelectObject(hdc, CreatePen(PS_SOLID, 1, 0x808080L));
        MoveTo(hdc, x, y + 20);
        LineTo(hdc, w + x - 1, y + 20);
        LineTo(hdc, w + x - 1, y);
        DeleteObject(SelectObject(hdc, oldpen));
        SetPixel(hdc, x, y, 0);
        SetPixel(hdc, x, y + 20, 0);
        SetPixel(hdc, w + x - 1, y, 0);
        SetPixel(hdc, w + x - 1, y + 20, 0);
        SetPixel(hdc, x + 1, y + 1, 0xc0c0c0L);
        SetPixel(hdc, x + 1, y + 19, 0xc0c0c0L);
        SetPixel(hdc, w + x - 2, y + 1, 0xc0c0c0L);
        SetPixel(hdc, w + x - 2, y + 19, 0xc0c0c0L);
        hfont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
        oldfont = SelectObject(hdc, hfont);
        SetBkMode(hdc, OPAQUE);
        bk = SetBkColor(hdc, 0);
        SetTextAlign(hdc, 0);
        tc = SetTextColor(hdc, 0xff00L);
        lstrcpy(drv, "C:>");
        drv[0] += LO8(g_94ac);
        TextOut(hdc, x + 2, y + 2, drv, lstrlen(drv));
        SetTextColor(hdc, tc);
        SetBkColor(hdc, bk);
        SelectObject(hdc, oldfont);
        if (hfont) {
            DeleteObject(hfont);
            hfont = 0;
        }
    }
    hfont = CreateFont(7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Small Fonts");
    oldfont = SelectObject(hdc, hfont);
    bk = SetBkColor(hdc, 0);
    SetTextAlign(hdc, TA_CENTER);
    tc = SetTextColor(hdc, 0xffffffL);
    TextOut(hdc, x + 16, y + 26, buf, lstrlen(buf));
    SetTextColor(hdc, tc);
    SetBkColor(hdc, bk);
    SelectObject(hdc, oldfont);
    if (hfont) {
        DeleteObject(hfont);
        hfont = 0;
    }
    PatBlt(hdc, x - y, y, y, w, BLACKNESS);
    PatBlt(hdc, w + x, y, y, w, BLACKNESS);
}

/* 9:08da */
int16_t fn_09_08da(int16_t x, int16_t y)
{
    int16_t i;
    int16_t j;
    COLORREF c;

    c = GetPixel((HDC)g_3a02, 0, 0);
    for (i = x; i < (int16_t)(x + 32); i++)
        for (j = y; j < (int16_t)(y + 32); j++)
            if (GetPixel((HDC)g_3a02, i, j) != c)
                return 0;
    return 1;
}

/* 9:094c */
int16_t fn_09_094c(void)
{
    int16_t i;
    int16_t unused;
    int16_t found;

    for (i = 0; i < g_9406[0]; i++) {
        found = 1;
        if (object_records[0][i].f_18 == 0)
            found = 0;
        if (found)
            return i;
    }
    g_69f4[g_94a2].f_1d0 = 1;
    g_9206++;
    return -1;
}

/* 9:09b0 */
void fn_09_09b0(int16_t slot)
{
    int16_t unused;

    if (fn_09_0ac4(g_9200, 1))
        return;
    if (g_9206 < g_9204) {
        g_57a8[slot].f_02 = g_57a8[slot].f_00 = 0;
        g_57a8[slot].f_0a = g_57a8[slot].f_0b = -1;
        g_57a8[slot].f_19 = 0;
        if (g_69f4[g_94a2].f_1d2[slot] < 0)
            g_69f4[g_94a2].f_1d2[slot] = 0;
        object_records[0][slot].f_1e = g_69f4[g_94a2].f_1d2[slot];
        g_57a8[slot].f_06 = g_9200 - 1;
        lstrcpy(g_57a8[slot].f_0c, g_3948.name);
        object_records[0][slot].f_18 = 0;
        fn_10_0736(slot);
        object_records[0][slot].f_0c = rand() % 60 - 30;
        object_records[0][slot].f_0e = rand() % 60 - 30;
        g_9202++;
    } else
        g_69f4[g_94a2].f_1d0 = 1;
    g_9206++;
}

/* 9:0ac4 */
int16_t fn_09_0ac4(int16_t n, int16_t count)
{
    uint8_t mask;
    int16_t unused;
    int16_t idx;

    idx = n / 8;
    mask = 1 << (n % 8);
    if (count)
        g_9200++;
    if (g_69f4[g_94a2].f_1e2[idx] & mask)
        return 1;
    return 0;
}

