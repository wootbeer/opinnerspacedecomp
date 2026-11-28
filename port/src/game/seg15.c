/* INSPACE.EXE segment 15 (selector 1070). */
#include "game.h"

/* Reads demogame.sav and returns its word at +0x22 [inferred]; the result
 * is uninitialised when the read fails (as in the original). */
/* 15:5d14 */
int16_t fn_15_5d14(void)
{
    HFILE hf;
    int16_t result;
    DWORD size;
    int32_t unused;
    HGLOBAL h;
    int16_t *lp;
    char path[140];
    OFSTRUCT of;

    lstrcpy(path, g_9078);
    lstrcat(path, g_96b8);
    lstrcat(path, "demogame.sav");
    h = GlobalAlloc(GHND, 425L);
    if (!h)
        return -1;
    lp = (int16_t *)GlobalLock(h);
    if (!lp) {
        GlobalFree(h);
        return -1;
    }
    hf = OpenFile(path, &of, 0);
    if (hf == -1) {
        GlobalUnlock(h);
        GlobalFree(h);
        return -1;
    }
    size = GlobalSize(h);
    GlobalUnlock(h);
    if (!fn_14_4006(hf, (char *)(lp = (int16_t *)GlobalLock(h = GlobalReAlloc(h, size, GHND))), size))
        MessageBeep(0);
    else
        result = lp[0x11];
    _lclose(hf);
    GlobalUnlock(h);
    GlobalFree(h);
    return result;
}

/* 15:5786 */
void fn_15_5786(void)
{
    HPALETTE oldpal;

    PatBlt(main_dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    fn_10_4b2e();
    fn_10_7480(-1, 1);
    if (g_90f8 && g_8e5e) {
        if (!g_95f2)
            g_95f2 = g_8f70 = 1;
        else if (rand() % 6)
            g_8f70 = 1;
        else
            g_8f70 = 0;
    }
    g_9516 = g_001a = 0;
    fn_10_885e(0);
    g_95b8 = 0;
    now_ms = GetCurrentTime();
    g_6e28 = now_ms + 65000L;
    g_95cc = 0;
    g_95d0 = 0x122;
    g_95d2 = 5000;
    ShowWindow(main_window, SW_SHOW);
    fn_15_5914();
    g_5ea8[0] = CreatePatternBrush(g_3820[0] = CreateBitmap(8, 8, 1, 1, g_06c6));
    g_5ea8[1] = CreatePatternBrush(g_3820[1] = CreateBitmap(8, 8, 1, 1, g_06b6));
    if (game_palette) {
        oldpal = SelectPalette(main_dc, game_palette, 0);
        RealizePalette(main_dc);
    }
    if (g_9156 != 1) {
        fn_10_0552(5, 1);
        fn_10_39a8(0);
    }
    fn_15_5962(1);
    if (oldpal)
        SelectPalette(main_dc, oldpal, 0);
    fn_10_73e2();
    fn_10_744c(0x6e);
    fn_10_7480(-5, 1);
    if (!g_1212) {
        g_120e = GetCurrentTime();
        g_8ffa = 0;
    }
}

/* 15:5914 */
void fn_15_5914(void)
{
    g_95f4 = fn_10_6d38("SD_LOGO");
}

/* 15:5932 */
void fn_15_5932(void)
{
    int16_t unused;

    fn_10_0136();
    if (g_95f4) {
        DeleteObject(g_95f4);
        g_95f4 = 0;
    }
}

/* 15:80b0 */
void fn_15_80b0(POINT a, POINT b)
{
    fn_15_80da();
    fn_11_a4a6(a, g_3b98 = b, 14);
}

/* 15:80da */
void fn_15_80da(void)
{
    if (g_1016) {
        if (g_8ffc < 0x578) {
            fn_11_a9ea(0);
            g_1016 = 0;
        } else {
            do
                fn_11_a9ea(0);
            while (g_1016);
        }
    }
}

/* Builds a drive description: letter, a loaded string and the volume
 * label of the drive [inferred]. */
/* 15:6558 */
void fn_15_6558(int16_t drive, LPSTR out)
{
    struct find_t ft;
    int16_t j;
    uint16_t rc;
    char buf[50];

    lstrcpy(out, "C");
    out[0] += g_94ac;
    LoadString(lang_module, 0x3a9, buf, 30);
    lstrcat(out, buf);
    lstrcpy(buf, "C:\\*.*");
    buf[0] += drive;
    ft.name[0] = 0;
    rc = _dos_findfirst(buf, _A_VOLID, &ft);
    if (rc != 0 || ft.name[0] == 0) {
        lstrcpy(buf, "Unknown_HD");
    } else {
        lstrcpy(buf, ft.name);
        if (lstrlen(buf) > 7 && buf[8] == '.')
            for (j = 8; lstrlen(buf) > j; j++)
                buf[j] = buf[j + 1];
    }
    lstrcat(out, buf);
}

/* 15:6640 */
void fn_15_6640(void)
{
    char buf1[100];
    char buf2[40];
    int16_t k;

    fn_10_744c(0x6e);
    fn_10_754a(0x6f, LO16(g_90ea) / 2, HI16(g_90ea) / 2 - 240, 4);
    k = fn_10_9764(0);
    lstrcpy(buf1, "");
    if (k == 3) {
        LoadString(lang_module, 0x24e, buf2, 30);
        lstrcpy(buf1, buf2);
    } else {
        LoadString(lang_module, 0x137, buf2, 30);
        lstrcat(buf2, " ");
        lstrcat(buf1, buf2);
    }
    LoadString(lang_module, k + 0x27f, buf2, 30);
    lstrcat(buf1, buf2);
    lstrcat(buf1, ", ");
    lstrcat(buf1, g_380c);
    lstrcat(buf1, "!");
    fn_10_94c4(0, 6, RGB(0x80, 0xff, 0), LO16(g_90ea) / 2, g_0010 / 2 - 90, buf1);
    LoadString(lang_module, 0x285, buf1, 30);
    fn_10_94c4(0, 6, RGB(0x80, 0xff, 0), LO16(g_90ea) / 2, g_0010 / 2 - 55, buf1);
    LoadString(lang_module, 0x3a8, buf2, 30);
    lstrcpy(buf1, buf2);
    fn_15_6558(g_94ac, buf2);
    lstrcat(buf1, buf2);
    fn_10_94c4(0, 6, RGB(0, 0xff, 0), LO16(g_90ea) / 2, g_0010 / 2, buf1);
}

/* 15:681c */
void fn_15_681c(HINSTANCE inst, LPSTR buf)
{
    char tmp[20];

    LoadString(inst, 0xa7, tmp, 10);
    lstrcpy(buf, "V0.00.00");
    buf[1] = tmp[0];
    buf[3] = tmp[1];
    buf[4] = tmp[2];
    LoadString(inst, 0xe9, tmp, 10);
    buf[6] = tmp[0];
    buf[7] = tmp[1];
    buf[8] = 0;
}

/* Shows the version line and an 11-line text page from resource 5000
 * [inferred]. */
/* 15:6890 */
void fn_15_6890(void)
{
    HGDIOBJ oldfont;
    HFONT font;
    char buf[60];
    char ver[10];
    int16_t i;
    int16_t off;
    int16_t k;
    int16_t id;
    COLORREF oldtext;
    COLORREF oldbk;
    HGLOBAL hres;
    DWORD u;
    LPSTR ptr;

    fn_15_681c(g_8e66, ver);
    if (!g_920c)
        LoadString(lang_module, 0x922, buf, 45);
    else
        LoadString(lang_module, 0x921, buf, 45);
    lstrcat(buf, " ");
    lstrcat(buf, ver);
    fn_10_94c4(0, 6, RGB(0x8c, 0, 0xff), LO16(g_90ea) / 2, g_0010 / 2 - 175, buf);
    font = CreateFont(18, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    oldfont = SelectObject(main_dc, font);
    oldbk = SetBkColor(main_dc, 0L);
    SetBkMode(main_dc, TRANSPARENT);
    SetTextAlign(main_dc, TA_CENTER);
    if (g_90ee < 8)
        oldtext = SetTextColor(main_dc, RGB(0, 0xff, 0xc8));
    else
        oldtext = SetTextColor(main_dc, PALETTERGB(0x80, 0x80, 0xff));
    if (g_920c == 0 || g_920c == 1)
        id = 0x88;
    else
        id = 0xc8;
    hres = LoadResource(lang_module, FindResource(lang_module, MAKEINTRESOURCE(id),
                                             MAKEINTRESOURCE(5000)));
    ptr = LockResource(hres);
    for (k = 0; ptr[k]; k++)
        if (ptr[k] == '\r')
            ptr[k] = 0;
    PatBlt(main_dc, 0, g_0010 / 2 - 115, LO16(g_90ea), g_0010 / 2 + 149, BLACKNESS);
    for (i = off = 0; i < g_95d6 * 11; i++)
        off += lstrlen(ptr + off) + 2;
    for (i = 0; i < 11; i++) {
        TextOut(main_dc, LO16(g_90ea) / 2, g_0010 / 2 + i * 24 - 115, ptr + off, lstrlen(ptr + off));
        off += lstrlen(ptr + off) + 2;
    }
    SetBkColor(main_dc, oldbk);
    SetTextColor(main_dc, oldtext);
    SelectObject(main_dc, oldfont);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
    if (ptr)
        GlobalUnlock(hres);
    if (hres)
        FreeResource(hres);
    LoadString(lang_module, 0x847, buf, 60);
    fn_10_94c4(0, 6, RGB(255, 255, 255), LO16(g_90ea) / 2, g_0010 / 2 + ++i * 24 - 115, buf);
}

/* 15:6b52 */
void fn_15_6b52(void)
{
    char buf1[80];
    char buf2[60];
    int16_t i;
    int16_t id1;
    int16_t id2;

    LoadString(lang_module, 0x848, buf1, 80);
    fn_10_94c4(0, 6, RGB(255, 0, 0), LO16(g_90ea) / 2, g_0010 / 2 - 200, buf1);
    for (i = 0; i < 11; i++) {
        switch (i) {
        case 8:
            id1 = 0x4b9;
            id2 = 0x51d;
            break;
        case 9:
            id1 = 0x4bd;
            id2 = 0x521;
            break;
        case 10:
            id1 = 0x4b7;
            id2 = 0x51b;
            break;
        default:
            id1 = i + 0x4c7;
            id2 = i + 0x52b;
            break;
        }
        LoadString(lang_module, id1, buf1, 60);
        fn_10_94c4(0, 0, RGB(255 - i * 13, 0, i * 12 + 11), LO16(g_90ea) / 2 - 295,
                   g_0010 / 2 + (i - 5) * 30, buf1);
        lstrcpy(buf1, "- ");
        LoadString(lang_module, id2, buf2, 60);
        lstrcat(buf1, buf2);
        fn_10_94c4(0, 0, RGB(255 - i * 13, 0, i * 12 + 11), LO16(g_90ea) / 2 - 5,
                   g_0010 / 2 + (i - 5) * 30, buf1);
    }
}

/* 15:7970 */
void fn_15_7970(int16_t x, int16_t y, LPCSTR s)
{
    int16_t i;
    int16_t off;
    int16_t len;

    len = lstrlen(s);
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            off = -1;
            SetTextColor(main_dc, RGB(255, 255, 255));
            break;
        case 1:
            off = 1;
            if (!g_11aa)
                SetTextColor(main_dc, PALETTERGB(0x60, 0x00, 0xc0));
            else if (g_90ee < 8)
                SetTextColor(main_dc, RGB(0x80, 0, 0));
            else
                SetTextColor(main_dc, PALETTERGB(0x74, 0x53, 0x19));
            break;
        case 2:
            off = 0;
            if (!g_11aa) {
                if (g_90ee < 8)
                    SetTextColor(main_dc, RGB(255, 0, 255));
                else
                    SetTextColor(main_dc, PALETTERGB(0xa0, 0x60, 0xff));
            } else {
                if (g_90ee < 8)
                    SetTextColor(main_dc, RGB(255, 255, 0));
                else
                    SetTextColor(main_dc, PALETTERGB(0xd8, 0xbc, 0x56));
            }
            break;
        }
        TextOut(main_dc, off + x, off + y, s, len);
    }
}

/* Draws one character with a light/dark/colour emboss at the current
 * position and advances it [inferred]. */
/* 15:7a62 */
void fn_15_7a62(LPCSTR s)
{
    int16_t i;
    int16_t off;
    int16_t u1;
    int16_t ext;
    int16_t x;
    int16_t y;
    DWORD pos;
    int16_t u2;
    int16_t u3;

    pos = GetCurrentPosition(main_dc);
    x = LOWORD(pos);
    y = HIWORD(pos);
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            off = -1;
            SetTextColor(main_dc, RGB(255, 255, 255));
            break;
        case 1:
            off = 1;
            SetTextColor(main_dc, PALETTERGB(0x60, 0x00, 0xc0));
            break;
        case 2:
            off = 0;
            if (g_90ee < 8)
                SetTextColor(main_dc, RGB(255, 0, 255));
            else
                SetTextColor(main_dc, PALETTERGB(0xa0, 0x60, 0xff));
            break;
        }
        TextOut(main_dc, x + off, y + off, s, 1);
    }
    ext = LOWORD(GetTextExtent(main_dc, s, 1));
    MoveTo(main_dc, LOWORD(pos) + ext, HIWORD(pos));
}

/* 15:7b34 */
void fn_15_7b34(void)
{
    g_6e28 = now_ms + 90000L;
    fn_10_6e76(MAKELONG(8, g_95dc = 0));
    fn_10_6e4c();
    fn_10_0552(0x16, 1);
    fn_10_58ce(0);
    fn_10_754a(0x13, 0, 0, 0);
    g_95d0 = 50;
    g_95d8 = 0;
    g_6e2c = 0;
    fn_15_811a();
}

/* 15:7ba6 */
void fn_15_7ba6(void)
{
    int16_t a;
    int16_t b;

    if (g_94c4)
        return;
    if (!g_95dc && g_6e28 - 19300 < now_ms) {
        g_95dc = 1;
        fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2, HI16(g_90ea), 0, -2500,
                   32, 32, 25, 150, -1);
        fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2 - 30, HI16(g_90ea), 950, -2500,
                   32, 32, 25, 47, 3);
        fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2 + 30, HI16(g_90ea), -950, -2500,
                   32, 32, 25, 19, 0);
        g_6e28 = now_ms + 7400;
    }
    a = fn_06_73f6();
    b = fn_06_7c14();
    if (now_ms - g_6e28 != -500 && a && b) {
        g_6e28 = now_ms + 500;
        g_94c4 = 1;
    }
}

/* Demo screen: spinning logo, then the two name lines with sparks
 * [inferred]. */
/* 15:7cda */
void fn_15_7cda(void)
{
    int16_t i;
    int16_t size;
    int16_t gap;
    int16_t sz;
    POINT p1;
    int16_t y2;
    int16_t u;
    DWORD t;
    int16_t n;

    gap = 4;
    size = 38;
    if (g_8ffc < 800)
        g_95d2 += 6;
    else
        g_95d2 += 3;
    if (g_95d2 >= 89)
        g_95d2 = 0;
    if (g_8ffc < 800)
        g_95d0 += 6;
    else
        g_95d0 += 3;
    if (g_95d0 > 300)
        g_95d0 = 300;
    sz = size * g_95d0 / 200;
    SetStretchBltMode(main_dc, COLORONCOLOR);
    StretchBlt(main_dc, LO16(g_90ea) / 2 - sz / 2, g_0010 / 2 - sz / 2 - 20, sz, sz, g_3a14,
               (gap + size) * (g_95d2 / 10) + gap, gap, size, size, SRCCOPY);
    if (g_95d0 != 300)
        return;
    if (g_130c) {
        if (g_130c < now_ms) {
            fn_15_811a();
            g_130c = 0;
        }
        return;
    }
    if (!g_6e2c) {
        if (fn_15_8174(g_95dc, g_95da)) {
            if (!g_95dc) {
                fn_15_80da();
                fn_15_8174(g_95dc, -1);
                g_95dc++;
            } else {
                g_6e2c = now_ms + 3000;
                fn_15_80da();
                fn_15_8174(g_95dc, -1);
            }
            g_95da = 0;
            return;
        }
        if (g_8ffc > 900 && g_920a > 1)
            g_95da += 2;
        else
            g_95da += 4;
        if (!(g_95da & 1))
            fn_10_754a(0x14, LOWORD(VIEW(int32_t, g_3b98, 0)), HIWORD(VIEW(int32_t, g_3b98, 0)), 4);
        return;
    }
    if (g_6e2c >= now_ms)
        return;
    p1.x = LO16(g_90ea) / 2;
    p1.y = g_0010 / 2 - 20;
    y2 = g_0010 / 2 - 150;
    if (g_920a == 1)
        n = 1;
    else
        n = 4;
    for (i = 0; i < n; i++) {
        fn_15_80b0(p1, (POINT){rand() % 300 + LO16(g_90ea) / 2 - 150, y2});
        fn_10_754a(0x22, LOWORD(VIEW(int32_t, g_3b98, 0)), HIWORD(VIEW(int32_t, g_3b98, 0)), 4);
        t = GetCurrentTime() + 40;
        do
            ;
        while (GetCurrentTime() < t);
    }
    fn_15_80da();
    PatBlt(main_dc, 0, g_0010 / 2 - 150, LO16(g_90ea), 40, BLACKNESS);
    StretchBlt(main_dc, LO16(g_90ea) / 2 - sz / 2, g_0010 / 2 - sz / 2 - 20, sz, sz, g_3a14,
               (gap + size) * (g_95d2 / 10) + gap, gap, size, size, SRCCOPY);
    t = GetCurrentTime() + 270;
    do
        ;
    while (GetCurrentTime() < t);
    y2 = g_0010 / 2 + 100;
    for (i = 0; i < n; i++) {
        fn_15_80b0(p1, (POINT){rand() % 300 + LO16(g_90ea) / 2 - 150, y2});
        fn_10_754a(0x22, LOWORD(VIEW(int32_t, g_3b98, 0)), HIWORD(VIEW(int32_t, g_3b98, 0)), 4);
        t = GetCurrentTime() + 40;
        do
            ;
        while (GetCurrentTime() < t);
    }
    fn_15_80da();
    PatBlt(main_dc, 0, g_0010 / 2 + 100, LO16(g_90ea), 40, BLACKNESS);
    now_ms = GetCurrentTime();
    if (++g_95d8 > 5) {
        g_6e28 = now_ms + 4000;
        g_6e2c = now_ms + 9000;
    } else
        g_130c = now_ms + 1000;
}

/* 15:811a */
void fn_15_811a(void)
{
    LoadString(lang_module, g_95d8 + 1000, g_87e0, 60);
    LoadString(lang_module, g_95d8 + 980, g_881c, 60);
    g_95dc = 0;
    g_6e2c = 0;
    g_6e28 = now_ms + 90000L;
}

/* Draws the first n letters of a name centred on screen, small letters
 * as smaller capitals [inferred]. */
/* 15:8174 */
int16_t fn_15_8174(int16_t which, int16_t n)
{
    char buf[80];
    char buf2[80];
    int16_t i;
    int16_t dy;
    int16_t w;
    int16_t orig;
    HGDIOBJ old;
    HFONT font1;
    HFONT font2;
    COLORREF oldtext;
    COLORREF oldbk;
    POINT p1;
    POINT p2;
    char ch[2];

    if (g_95d8 > 5)
        return 1;
    orig = n;
    n /= 2;
    if (!which) {
        lstrcpy(buf, g_87e0);
        dy = -150;
    } else {
        lstrcpy(buf, g_881c);
        dy = 100;
    }
    if (orig == -1)
        n = lstrlen(buf);
    else if (lstrlen(buf) < n)
        return 1;
    font1 = CreateFont(28, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    font2 = CreateFont(22, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    if (!n) {
        lstrcpy(buf2, buf);
        MoveTo(main_dc, -2000, 0);
        SetTextAlign(main_dc, TA_UPDATECP);
        for (i = g_1c70 = 0; i < lstrlen(buf2); i++) {
            ch[0] = buf2[i];
            ch[1] = 0;
            if (ch[0] < '{' && ch[0] > '`') {
                ch[0] -= 0x20;
                old = SelectObject(main_dc, font2);
            } else
                old = SelectObject(main_dc, font1);
            TextOut(main_dc, 0, 0, ch, 1);
            SelectObject(main_dc, old);
        }
        g_1c70 = LOWORD(GetCurrentPosition(main_dc)) + 2000;
    }
    w = g_1c70 * n / lstrlen(buf);
    if (orig != -1) {
        p1.x = LO16(g_90ea) / 2;
        p1.y = g_0010 / 2 - 20;
        p2.x = LO16(g_90ea) / 2 - g_1c70 / 2 + w;
        if (orig / 2 != n)
            p2.x += 10;
        p2.y = g_0010 / 2 + dy;
        fn_15_80b0(p1, p2);
    }
    oldbk = SetBkColor(main_dc, 0L);
    SetBkMode(main_dc, TRANSPARENT);
    MoveTo(main_dc, LO16(g_90ea) / 2 - g_1c70 / 2, g_0010 / 2 + dy);
    if (g_90ee < 8)
        oldtext = SetTextColor(main_dc, RGB(0, 0xff, 0xff));
    else
        oldtext = SetTextColor(main_dc, PALETTERGB(0, 0xa5, 0xff));
    for (i = 0; i < n; i++) {
        ch[0] = buf[i];
        ch[1] = 0;
        if (ch[0] < '{' && ch[0] > '`') {
            ch[0] -= 0x20;
            old = SelectObject(main_dc, font2);
        } else
            old = SelectObject(main_dc, font1);
        fn_15_7a62(ch);
        SelectObject(main_dc, old);
    }
    SetBkColor(main_dc, oldbk);
    SetTextColor(main_dc, oldtext);
    if (font1) {
        DeleteObject(font1);
        font1 = 0;
    }
    if (font2) {
        DeleteObject(font2);
        font2 = 0;
    }
    return 0;
}

/* 15:84b0 */
void fn_15_84b0(int16_t x, int16_t y)
{
    int16_t i;
    HGDIOBJ old;

    if (g_90f4 != 0 || g_92d4 != 7)
        fn_10_754a(0x14, x, y, 4);
    old = SelectObject(main_dc, GetStockObject(WHITE_PEN));
    for (i = 2; i < 200; i++) {
        MoveTo(main_dc, x, i / -10 + y);
        LineTo(main_dc, x, i / 10 + y);
        MoveTo(main_dc, i / -10 + x, y);
        LineTo(main_dc, i / 10 + x, y);
    }
    SelectObject(main_dc, old);
    for (i = 200; i > 0; i--) {
        SetPixel(main_dc, x, i / -10 + y, 0L);
        SetPixel(main_dc, x, i / 10 + y, 0L);
        SetPixel(main_dc, i / -10 + x, y, 0L);
        SetPixel(main_dc, i / 10 + x, y, 0L);
        PatBlt(main_dc, x - 1, y - 1, 2, 2, BLACKNESS);
    }
}

/* Step of the demo/attract sequence, state g_95b8 [inferred]. */
/* 15:5962 */
void fn_15_5962(int16_t a)
{
    int16_t i;
    int16_t k;
    char buf[30];
    char buf2[30];

    switch (g_95b8) {
    case 0:
        flow_interactive = 1;
        fn_15_5e22(a);
        break;
    case 2:
        fn_15_6cdc();
        break;
    case 3:
        fn_15_7cda();
        break;
    case 4:
        if (a)
            fn_15_6890();
        break;
    case 5:
        if (a && g_6e28 != now_ms)
            fn_15_6b52();
        break;
    case 6:
        fn_15_10be();
        break;
    case 7:
        return;
    }
    if (g_6e28 >= now_ms)
        return;
    if (g_95b8 == 4 && g_95d6 < 1) {
        g_95d6++;
        if (g_920c == 1 || g_920c == 0)
            g_6e28 = now_ms + 27000;
        else
            g_6e28 = now_ms + 17000;
        fn_15_6890();
        return;
    }
    fn_10_744c(0x6e);
    PatBlt(main_dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    g_95b8++;
    if ((g_95b8 == 2 && g_90f8 && g_8f70) || g_95b8 > 5) {
        flow_interactive = 0;
        g_9134 = 1;
        g_95b8 = 7;
        g_05b4 = GetCurrentTime() + 120000L;
        g_91f8 = 0;
        if (g_90f8) {
            g_95ba = GetPrivateProfileInt(app_name, "DemoType", 0x207, ini_name);
            if (g_95ba == 0x207)
                g_95ba = rand() % 4 + 0x208;
            if (g_90f8 && g_95ba == 0x208) {
                GetPrivateProfileString(app_name, "Ship1", "", buf, 20, ini_name);
                if (!buf[0]) {
                    fn_14_3eda();
                    fn_14_31d0(0, buf);
                    fn_14_4074();
                    fn_06_92b8();
                }
                if ((k = fn_15_5d14()) != -1) {
                    fn_14_3eda();
                    lstrcpy(buf2, g_6e20[k].f_0a);
                    fn_14_4074();
                }
                if (lstrcmp(buf, buf2) || k == -1) {
                    fn_06_92b8();
                    WritePrivateProfileString(app_name, "MainShip", buf, ini_name);
                }
                g_9516 = 0;
            } else
                g_9516 = 1;
        }
        if (!g_9516)
            fn_06_930a();
        fn_06_1d9a();
        fn_06_1c72(1);
        return;
    }
    switch (g_95b8) {
    case 0:
        fn_10_7d58(LO16(g_90ea) / 2, HI16(g_90ea) / 2);
        g_6e28 = now_ms + 65000;
        g_95cc = 0;
        g_95d0 = 400;
        break;
    case 1:
        if (!g_8f70 || !g_90f8)
            fn_10_7480(0, 1);
        g_6e28 = now_ms + 1000;
        break;
    case 2:
        fn_10_4b2e();
        fn_06_7266();
        g_6e28 = now_ms + 65000;
        g_95cc = 0;
        fn_10_6e76(MAKELONG(8, g_94c4 = 1));
        if (g_0010 < 440)
            g_95de = 40;
        else if (g_0010 < 500)
            g_95de = 30;
        else
            g_95de = 0;
        for (i = g_95d4 = g_95ca = g_95c8 = 0; i < 18; i++)
            g_95e0[i] = 0;
        break;
    case 3:
        fn_15_7b34();
        break;
    case 4:
        fn_10_7d58(LO16(g_90ea) / 2, HI16(g_90ea) / 2);
        if (g_920c == 0 || g_920c == 1)
            g_6e28 = now_ms + 25000;
        else
            g_6e28 = now_ms + 18000;
        g_95d6 = 0;
        fn_15_6890();
        break;
    case 5:
        g_6e28 = now_ms + 11000;
        fn_15_6b52();
        break;
    }
}

/* Calibration screen (state machine on g_95cc): counter gauge, the
 * spark/laser animation and the final caption [inferred]. */
/* 15:5e22 */
void fn_15_5e22(int16_t a)
{
    HDC mdc;
    HGDIOBJ oldm;
    HGDIOBJ oldbr;
    HGDIOBJ oldpen;
    int16_t i;
    int16_t r;
    int16_t n;
    int16_t sz;                     /* digit size */
    int16_t m;                      /* digit margin */
    COLORREF color;

    m = 6;
    sz = 40;
    mdc = CreateCompatibleDC(main_dc);
    oldm = SelectObject(mdc, (HGDIOBJ)g_95f4);
    if (a && g_95cc)
        BitBlt(main_dc, LO16(g_90ea) / 2 - 88, g_0010 / 2 - 60, 40, 40, g_39f2, n * 46 + 6, 6, SRCCOPY);  /* sic: n unset */
    switch (g_95cc) {
    case 0: {
        int16_t v;

        if (g_95d2 < 9999)
            n = g_95d2 / 1000;
        else
            n = 0;
        if (g_1212 && g_120e == 0 && g_95d0 && g_95d0 < 160 && n == 5) {
            g_95d0 = g_95d2 = 0;
            fn_10_754a(0x23, 0, 0, 0);
            g_95cc++;
        }
        BitBlt(main_dc, LO16(g_90ea) / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2, (sz + m) * n + m,
               m, SRCCOPY);
        g_95d2 += g_95d0;
        if (g_95d2 > 13999) {
            g_95d2 = 0;
            if (g_120e == 0)
                g_95d0 = g_95d0 - 18 < 1 ? 1 : g_95d0 - 18;
        }
        if (g_120e) {
            if (GetCurrentTime() > g_120e + 1000) {
                v = GetPrivateProfileInt(app_name, "Calibrate", 0, ini_name);
                if (g_8ffa && v / 2 > g_8ffa && g_1214)
                    g_1214 = g_8ffa = 0;
                if ((g_90f8 || g_90ee < 8) && GetCurrentTime() < g_1d3c + 2000 || !g_8ffa) {
                    g_120e = GetCurrentTime();
                    g_8ffa = 0;
                } else {
                    g_1212 = 1;
                    g_95d0 = 240;
                    g_120e = 0;
                    g_8ffa = (int32_t)g_8ffa * 23 / 10;
                    fn_06_0a6c();
                }
            } else
                g_8ffa++;
        }
        break;
    }
    case 1:
        BitBlt(main_dc, LO16(g_90ea) / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2,
               (n = g_95d2 / 1000 + 10) * (m + sz) + m, m, SRCCOPY);
        g_95d2 += 45;
        if (g_95d2 >= 3940) {
            fn_10_754a(0x68, 0, 0, 0);
            g_95d2 = 620;
            g_95cc++;
        }
        break;
    case 2:
        switch (r = rand() % 4) {
        case 0:
            color = RGB(0, 0, 255);
            break;
        case 1:
            color = RGB(0, 255, 255);
            break;
        case 2:
            color = RGB(255, 255, 255);
            break;
        case 3:
            color = RGB(0, 128, 128);
            break;
        }
        oldpen = SelectObject(main_dc, CreatePen(PS_SOLID, 2, color));
        MoveTo(main_dc, LO16(g_90ea) / 2 - 48, g_0010 / 2 - 40);
        LineTo(main_dc, LO16(g_90ea) / 2 + g_95d2 / 5 - 38, rand() % 30 + g_0010 / 2 - 55);
        DeleteObject(SelectObject(main_dc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0))));
        MoveTo(main_dc, LO16(g_90ea) / 2 - 48, g_0010 / 2 - 40);
        LineTo(main_dc, LO16(g_90ea) / 2 + g_95d2 / 5 - 38, rand() % 30 + g_0010 / 2 - 55);
        DeleteObject(SelectObject(main_dc, oldpen));
        fn_10_7d58(LO16(g_90ea) / 2 + g_95d2 / 2 - 38, HI16(g_90ea) / 2);
        oldbr = SelectObject(main_dc, GetStockObject(DKGRAY_BRUSH));
        BitBlt(main_dc, g_95d2 / 5 + LO16(g_90ea) / 2 - 38, g_0010 / 2 - 56, 2, 32, mdc, g_95d2 / 5, 0,
               MERGECOPY);
        SelectObject(main_dc, oldbr);
        if ((g_95d2 -= 4) < 0) {
            PatBlt(main_dc, LO16(g_90ea) / 2 - 48, g_0010 / 2 - 56, 10, 32, BLACKNESS);
            for (i = 0; i < 630; i += 2) {
                if (i == 100)
                    fn_10_744c(0x6e);
                oldbr = SelectObject(main_dc, CreateSolidBrush(RGB(i / 5 + 128, i / 5 - 128,
                                                                  i / -5 + 127)));
                BitBlt(main_dc, LO16(g_90ea) / 2 - 38, g_0010 / 2 - 56, 130, 32, mdc, 0, 0, MERGECOPY);
                DeleteObject(SelectObject(main_dc, oldbr));
            }
            g_95cc++;
            g_95d2 = 3940;
            fn_10_744c(0x23);
        }
        break;
    case 3:
        BitBlt(main_dc, LO16(g_90ea) / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2,
               (n = g_95d2 / 1000 + 10) * (m + sz) + m, m, SRCCOPY);
        g_95d2 -= 45;
        if (g_95d2 <= 60) {
            BitBlt(main_dc, LO16(g_90ea) / 2 - 88, g_0010 / 2 - 60, sz, sz, g_39f2, m * 6 + sz * 5,
                   m, SRCCOPY);
            g_95cc++;
            g_6e28 = now_ms + 3000;
        }
        break;
    case 4: {
        HGDIOBJ oldfont;
        HFONT font;
        char buf[40];
        DWORD oldtc;
        DWORD oldbk;

        fn_10_744c(0x6e);
        font = CreateFont(38, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0x22, "Times New Roman");
        oldfont = SelectObject(main_dc, font);
        oldbk = SetBkColor(main_dc, RGB(0, 0, 0));
        SetBkMode(main_dc, TRANSPARENT);
        SetTextAlign(main_dc, TA_CENTER);
        oldtc = SetTextColor(main_dc, RGB(255, 255, 0));
        LoadString(lang_module, 0x846, buf, 40);
        TextOut(main_dc, LO16(g_90ea) / 2, g_0010 / 2 + 17, buf, lstrlen(buf));
        SetBkColor(main_dc, oldbk);
        SetTextColor(main_dc, oldtc);
        SelectObject(main_dc, oldfont);
        if (font) {
            DeleteObject(font);
            font = 0;
        }
        break;
    }
    }
    SelectObject(mdc, oldm);
    DeleteDC(mdc);
}

/* Title screen: logo lines, version and CD/demo status, the logo bitmap
 * dissolving in, then the title scrolling and the end fireworks [inferred]. */
/* 15:6cdc */
void fn_15_6cdc(void)
{
    int16_t u1;                     /* u1-u6 never used: frame layout */
    int16_t u2;
    int16_t u3;
    int16_t u4;
    int16_t u5;
    int16_t v;                      /* fade level, stored but never read */
    int16_t flag;
    int16_t u6;
    int16_t k;
    int16_t pix;
    int16_t ok;
    char mask;
    int16_t bit;
    int16_t idx;
    HGDIOBJ oldfont;
    HFONT font;
    char buf[90];
    char buf2[140];
    COLORREF textcol;
    COLORREF bkcol;

    switch (g_95cc) {
    case 0:
        if (g_95d4 == 0) {
            fn_10_6ea0(5);
            font = CreateFont(24, 11, 0, 0, 600, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(main_dc, font);
            bkcol = SetBkColor(main_dc, 0L);
            SetBkMode(main_dc, TRANSPARENT);
            SetTextAlign(main_dc, TA_CENTER);
            if (g_90ee < 8)
                textcol = SetTextColor(main_dc, RGB(0, 0xff, 0xff));
            else
                textcol = SetTextColor(main_dc, PALETTERGB(0, 0xa5, 0xff));
            LoadString(lang_module, 0x849, buf, 90);
            fn_15_7970(LO16(g_90ea) / 2 - 90, g_0010 / 2 + g_95de - 245, buf);
            SelectObject(main_dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(35, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(main_dc, font);
            if (g_920c == 0)
                LoadString(lang_module, 0x922, buf, 45);
            else
                LoadString(lang_module, 0x921, buf, 45);
            fn_11_3fd4(buf, 0);
            lstrcat(buf, "\x99");
            fn_15_7970(LO16(g_90ea) / 2, g_0010 / 2 + g_95de - 220, buf);
            SelectObject(main_dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(main_dc, font);
            if (g_11aa == 0) {
                if (g_920c == 3)
                    lstrcpy(buf, "");
                else
                    fn_09_955c(0x923, buf);
            } else
                fn_09_955c(0x924, buf);
            lstrcat(buf, " - ");
            fn_15_681c(g_8e66, buf2);
            lstrcat(buf, buf2);
            lstrcat(buf, " ");
            LoadString(g_8e66, 0x25f, buf2, 20);
            lstrcat(buf, buf2);
            SetTextColor(main_dc, PALETTERGB(0xc0, 0xc0, 0xc0));
            fn_15_7970(LO16(g_90ea) / 2, g_0010 / 2 + g_95de - 186, buf);
            fn_10_885e(0);
            flag = 0;
            SetTextColor(main_dc, PALETTERGB(0xc0, 0xc0, 0xc0));
            if (g_920c != 3) {
                if (g_920c == -1) {
                    GetProfileString(app_name, "CDDrive", "", buf, 40);
                    if (buf[0] == 0) {
                        fn_09_955c(0x84c, buf2);
                        fn_10_946a(buf);
                        lstrcat(buf2, buf);
                    } else {
                        lstrcpy(buf2, "CD: ");
                        lstrcat(buf2, buf);
                    }
                } else if (g_920c == 2) {
                    int16_t n;

                    n = -g_9224;
                    fn_09_955c(0x926, buf);
                    wsprintf(buf2, buf, n);
                } else {
                    int16_t n;

                    if (g_922a)
                        fn_09_955c(0x927, buf2);
                    else {
                        if (g_9224 < 0) {
                            n = -g_9224;
                            fn_09_955c(0x926, buf);
                        } else {
                            lstrcpy(buf, "");
                            n = g_9224;
                            fn_09_955c(0x925, buf);
                        }
                        wsprintf(buf2, buf, n);
                    }
                    flag = 1;
                }
                fn_15_7970(LO16(g_90ea) / 2, g_0010 / 2 + g_95ce + 125, buf2);
            }
            if (flag) {
                SetTextColor(main_dc, 0L);
                SetBkColor(main_dc, PALETTERGB(0xb4, 0x80, 0xe0));
                SetBkMode(main_dc, OPAQUE);
                if (g_922a)
                    fn_09_955c(0x928, buf2);
                else
                    fn_09_955c(0x906, buf2);
                TextOut(main_dc, LO16(g_90ea) / 2, g_0010 / 2 + g_95ce + 150, buf2, lstrlen(buf2));
                SetBkColor(main_dc, 0L);
                SetBkMode(main_dc, TRANSPARENT);
            }
            SelectObject(main_dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(16, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(main_dc, font);
            if (g_90ee != 8) {
                SetTextColor(main_dc, 0L);
                SetBkColor(main_dc, PALETTERGB(0xc0, 0xc0, 0xc0));
                SetBkMode(main_dc, OPAQUE);
                lstrcpy(buf2, " For best results, change Windows to 256 color mode ");
                TextOut(main_dc, LO16(g_90ea) / 2, g_0010 / 2 + g_95ce + 86, buf2, lstrlen(buf2));
                SetBkColor(main_dc, 0L);
                SetBkMode(main_dc, TRANSPARENT);
            }
            SetTextColor(main_dc, PALETTERGB(0xb4, 0x80, 0xe0));
            lstrcpy(buf, "\xa9 1994-2000 Software Dynamics, inc. All rights reserved.");
            TextOut(main_dc, LO16(g_90ea) / 2, g_0010 / 2 + g_95ce + 103, buf, lstrlen(buf));
            SelectObject(main_dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            font = CreateFont(30, 0, 0, 0, 800, 1, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
            oldfont = SelectObject(main_dc, font);
            SetTextColor(main_dc, PALETTERGB(0xb4, 0x80, 0xe0));
            fn_09_955c(0x9ee, buf2);
            fn_15_7970(LO16(g_90ea) / 2, g_0010 / 2 + g_95ce + 185, buf2);
            SetBkColor(main_dc, bkcol);
            SetTextColor(main_dc, textcol);
            SelectObject(main_dc, oldfont);
            if (font) {
                DeleteObject(font);
                font = 0;
            }
            g_95be = fn_10_6c02(300, 0, -1);
            g_95c2 = CreateCompatibleDC(main_dc);
            g_95c0 = SelectObject(g_95c2, g_95be);
            if (game_palette)
                g_95c4 = SelectPalette(g_95c2, game_palette, 0);
            SetStretchBltMode(main_dc, 3);
            fn_10_9962(1, main_dc, LO16(g_90ea) / 2 - 138, g_0010 / 2 + g_95de - 155, 276, 210,
                       g_95c2, 0, 0, 138, 105, SRCCOPY);
            if (game_palette)
                SelectPalette(g_95c2, g_95c4, 0);
            SelectObject(g_95c2, g_95c0);
            DeleteObject(g_95be);
            for (k = 0; k < 18; k++)
                g_95e0[k] = 0;
            if (g_90f0 == 0 && (g_8fe8 == 0 || g_8ffa < 800)) {
                HDC mdc;
                HBITMAP bmp;
                HGDIOBJ oldbmp;
                HPALETTE oldpal;

                bmp = fn_10_6c02(300, 3, -1);
                mdc = CreateCompatibleDC(main_dc);
                oldbmp = SelectObject(mdc, bmp);
                if (game_palette)
                    oldpal = SelectPalette(mdc, game_palette, 0);
                g_95be = CreateCompatibleBitmap(main_dc, 276, 276);
                g_95c0 = SelectObject(g_95c2, g_95be);
                if (game_palette)
                    g_95c4 = SelectPalette(g_95c2, game_palette, 0);
                SetStretchBltMode(g_95c2, 3);
                fn_10_9962(1, g_95c2, 0, 0, 276, 276, mdc, 0, 0, 138, 138, SRCCOPY);
                if (game_palette)
                    SelectPalette(mdc, oldpal, 0);
                SelectObject(mdc, oldbmp);
                DeleteObject(bmp);
                DeleteDC(mdc);
            } else {
                g_95be = fn_10_73a6(300, "", -2, -2, 2, 0, 1, 1, 12);
                g_95c0 = SelectObject(g_95c2, g_95be);
                if (game_palette)
                    g_95c4 = SelectPalette(g_95c2, game_palette, 0);
            }
        }
        g_6e2c = 0;
        g_95c6 = LO16(g_90ea) / 2 - 400;
        ok = g_95dc = 0;
        while (!ok) {
            pix = rand() % 105;
            idx = pix >> 3;
            bit = pix & 7;
            mask = 1 << bit;
            ok = !(g_95e0[idx] & mask);
        }
        g_95e0[idx] |= mask;
        g_95d4++;
        BitBlt(main_dc, LO16(g_90ea) / 2 - 138, g_0010 / 2 + pix * 2 + g_95de - 155, 276, 2,
               g_95c2, 0, pix * 2, SRCCOPY);
        if (g_95d4 >= 105) {
            if (g_95c4)
                SelectPalette(g_95c2, g_95c4, 0);
            SelectObject(g_95c2, g_95c0);
            DeleteObject(g_95be);
            DeleteDC(g_95c2);
            g_95c2 = 0;
            for (k = 0; k < 18; k++)
                g_95e0[k] = 0;
            g_95cc++;
            g_95d4 = 0;
            g_95ca = g_95c8 = 0;
        }
        break;
    case 1:
        g_95cc++;
        g_95ce = g_95c8 = 0;
        break;
    case 2:
        g_95cc++;
        g_95ca = g_95c8 = 0;
        break;
    case 3:
        fn_10_7d58(g_95c6 += 5, HI16(g_90ea) / 2);
        if (g_95ca > 190)
            v = min(g_95c8 - 190, 255);
        else
            v = max((24 - g_95c8) * 10, 0);
        g_95c8 += 2;
        g_95ca += 2;
        if (g_95ca >= 230) {
            g_95cc++;
            g_95ca = g_95c8 = 0;
        }
        break;
    case 4:
        fn_10_7d58(g_95c6 += 5, HI16(g_90ea) / 2);
        g_95c8 += 4;
        g_95ce += 2;
        if (g_95ce >= 40) {
            g_6e2c = now_ms + 45000;
            g_6e28 = g_6e2c + 6500;
            g_95cc = 5;
            g_95ca = g_95c8 = 0;
        }
        break;
    }
    if (g_6e2c && g_6e2c < now_ms) {
        g_94c4 = 0;
        fn_06_7266();
        fn_06_72d8(2, 3);
        fn_10_744c(0x6e);
        fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2 - 210, HI16(g_90ea), 0, -2500,
                   32, 32, 25, 178, -1);
        fn_06_84fc((rand() % 2 + 1) * 10, LO16(g_90ea) / 2 + 210, HI16(g_90ea), 0, -2500,
                   32, 32, 25, 165, -1);
        g_6e2c = 0;
    }
    if (g_94c4 == 0) {
        int16_t a;
        int16_t b;

        a = fn_06_73f6();
        b = fn_06_7c14();
        if (b && !g_95dc) {
            g_95dc = 1;
            PatBlt(main_dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
            g_1c6c = now_ms + 100;
            g_6e28 = now_ms + 2500;
        }
        if (g_6e28 - 800 > now_ms && g_1c6c + 100 < now_ms && g_95dc && rand() % 10 < 3) {
            fn_06_78ea(rand() % 2 * 10, rand() % 300 + LO16(g_90ea) / 2 - 150,
                       rand() % 440 + HI16(g_90ea) / 2 - 220, 0, 0, 800, 4, 50 - rand() % 10);
            g_1c6c = now_ms;
        }
        if (g_6e28 - 200 < now_ms)
            g_94c4 = 1;
    }
}

/* Draws the bevelled frame of the picture panel g_3ca8 [inferred]. */
/* 15:8604 */
void fn_15_8604(void)
{
    HBITMAP bmp;
    HGDIOBJ oldbmp;
    HDC dc;
    HGDIOBJ old;
    HPALETTE pal;

    g_92d2 = g_3ca8.bottom - g_3ca8.top - 15;
    FillRect(g_929a, &g_3ca8, GetStockObject(LTGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 25, g_3ca8.top + 25, g_3ca8.right - 25,
            g_3ca8.top + g_92d2 - 25);
    SetRect(&g_6084, g_3ca8.left + 25, g_3ca8.top + 25, g_3ca8.right - 25,
            g_3ca8.top + g_92d2 - 25);
    FillRect(g_929a, &g_6e30, GetStockObject(BLACK_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 20, g_3ca8.top + 20, g_3ca8.right - 20, g_3ca8.top + 25);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 20, g_3ca8.top + g_92d2 - 25, g_3ca8.right - 20,
            g_3ca8.top + g_92d2 - 20);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.right - 25, g_3ca8.top + 20, g_3ca8.right - 20,
            g_3ca8.top + g_92d2 - 20);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.left + 20, g_3ca8.top + 20, g_3ca8.left + 25,
            g_3ca8.top + g_92d2 - 20);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left, g_3ca8.top, g_3ca8.right, g_3ca8.top + 2);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.left, g_3ca8.top, g_3ca8.left + 2, g_3ca8.bottom);
    FillRect(g_929a, &g_6e30, GetStockObject(WHITE_BRUSH));
    SetRect(&g_6e30, g_3ca8.right - 2, g_3ca8.top, g_3ca8.right, g_3ca8.bottom);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    SetRect(&g_6e30, g_3ca8.left, g_3ca8.bottom - 2, g_3ca8.right, g_3ca8.bottom);
    FillRect(g_929a, &g_6e30, GetStockObject(DKGRAY_BRUSH));
    old = SelectObject(g_929a, GetStockObject(WHITE_PEN));
    MoveTo(g_929a, g_3ca8.left, g_3ca8.top + g_92d2 - 5);
    LineTo(g_929a, g_3ca8.right - 1, g_3ca8.top + g_92d2 - 5);
    SelectObject(g_929a, old);
    bmp = fn_10_6c02(0x122, 0, -1);
    dc = CreateCompatibleDC(main_dc);
    if (game_palette)
        pal = SelectPalette(dc, game_palette, 0);
    oldbmp = SelectObject(dc, bmp);
    BitBlt(g_929a, g_3ca8.left + 20, g_3ca8.top + g_92d2 - 17, 44, 10, dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldbmp);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(bmp);
    SelectObject(g_929a, CreatePen(PS_SOLID, 1, RGB(0, 0xff, 0)));
    MoveTo(g_929a, g_3ca8.right - 19, g_3ca8.top + g_92d2 - 5);
    LineTo(g_929a, g_3ca8.right - 38, g_3ca8.top + g_92d2 - 5);
    DeleteObject(SelectObject(g_929a, old));
    old = SelectObject(g_929a, GetStockObject(WHITE_PEN));
    MoveTo(g_929a, g_3ca8.right - 20, g_3ca8.bottom - 16);
    LineTo(g_929a, g_3ca8.right - 20, g_3ca8.bottom - 6);
    LineTo(g_929a, g_3ca8.right - 35, g_3ca8.bottom - 6);
    SelectObject(g_929a, CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80)));   /* leaked */
    LineTo(g_929a, g_3ca8.right - 35, g_3ca8.bottom - 16);
    LineTo(g_929a, g_3ca8.right - 20, g_3ca8.bottom - 16);
    DeleteObject(SelectObject(g_929a, old));
    bmp = fn_10_6d38("CORNER");
    dc = CreateCompatibleDC(main_dc);
    oldbmp = SelectObject(dc, bmp);
    BitBlt(g_929a, g_3ca8.left + 20, g_3ca8.top + g_92d2 - 25, 5, 5, dc, 0, 0, SRCCOPY);
    BitBlt(g_929a, g_3ca8.right - 26, g_3ca8.top + 20, 5, 5, dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
    DeleteObject(bmp);
}

/* Draws a panel with frames, a label bitmap and three lamps in g_3cb8
 * [inferred]. */
/* 15:8ae6 */
void fn_15_8ae6(void)
{
    HBITMAP bmp;
    HGDIOBJ oldbmp;
    HDC dc;
    int16_t u;
    HGDIOBJ oldbr;
    HPALETTE pal;
    int16_t w;
    int16_t h;

    w = g_3cb8.right - g_3cb8.left;
    h = g_3cb8.bottom - g_3cb8.top;
    fn_10_949c(g_929a, g_3cb8.left, g_3cb8.top, w, h, 2);
    fn_10_949c(g_929a, w / 16 + g_3cb8.left, w / 16 + g_3cb8.top, (int16_t)(w * 7) / 8, h - w / 8, 3);
    fn_10_949c(g_929a, w / 8 + g_3cb8.left, (int16_t)(h * 5) / 8 + g_3cb8.top + 1, (int16_t)(w * 3) / 4,
               (int16_t)(h * 3) / 8 - w / 8, 1);
    fn_10_949c(g_929a, w / 8 + g_3cb8.left, h / 2 + g_3cb8.top, (int16_t)(w * 3) / 4, h / 8, 1);
    bmp = fn_10_6c02(0x122, 0, -1);
    dc = CreateCompatibleDC(main_dc);
    if (game_palette)
        pal = SelectPalette(dc, game_palette, 0);
    oldbmp = SelectObject(dc, bmp);
    BitBlt(g_929a, w / 8 + g_3cb8.left + 2, (int16_t)(h * 5) / 8 + g_3cb8.top + 3, min((int16_t)(w * 3) / 4, 44), 10,
           dc, 0, 0, SRCCOPY);
    SelectObject(dc, oldbmp);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
    DeleteObject(bmp);
    oldbr = SelectObject(g_929a, CreateSolidBrush(PALETTERGB(0, 0xff, 0)));
    PatBlt(g_929a, (int16_t)(w * 3) / 8 + g_3cb8.left - 2, (int16_t)(h * 17) / 32 + g_3cb8.top, 5, 3, PATCOPY);
    DeleteObject(SelectObject(g_929a, oldbr));
    oldbr = SelectObject(g_929a, CreateSolidBrush(PALETTERGB(0x7f, 0xff, 0)));
    PatBlt(g_929a, (int16_t)(w * 4) / 8 + g_3cb8.left - 2, (int16_t)(h * 17) / 32 + g_3cb8.top, 5, 3, PATCOPY);
    DeleteObject(SelectObject(g_929a, oldbr));
    oldbr = SelectObject(g_929a, CreateSolidBrush(PALETTERGB(0x7f, 0, 0)));
    PatBlt(g_929a, (int16_t)(w * 5) / 8 + g_3cb8.left - 2, (int16_t)(h * 17) / 32 + g_3cb8.top, 5, 3, PATCOPY);
    DeleteObject(SelectObject(g_929a, oldbr));
}
