/* INSPACE.EXE segment 15 (selector 1070), first source file: 15:0000-15:52e4
 * (files.tsv group 29), compiled with /G2 (no 386 long jumps). */
#include "game.h"

/* px, py, size live in a struct: CL does not keep struct fields in
 * registers, which gives the game's [bp-8] pushes. */
/* 15:0760 */
void fn_15_0760(void)
{
    int16_t y;
    int16_t x;
    struct { int16_t px, py, size; } r;     /* icon position and size [inferred] */

    y = x = 0;
    if (g_929a) {
        if ((g_929c >= 2 || g_92a2 >= 1) && g_92d6 != -1) {
            BitBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, g_929a, 0, 0, SRCCOPY);
            if ((g_92a2 != 1 || g_92d8 == -1) && g_929c <= 6) {
                r.size = (g_6e24[g_7090[main_ship].f_0d6].f_7a
                        + (g_6e24[g_7090[main_ship].f_0d6].f_7b - 6) / 2) * 4;
                r.px = LO16(g_90ea) / 2 - r.size / 2;
                BitBlt(g_13dc, r.px, r.py = g_92d6 + 5, r.size, r.size, g_3cdc[1], 0, g_3ce8[1], SRCAND);
                BitBlt(g_13dc, r.px, r.py, r.size, r.size, g_3cdc[0], 0, g_3ce8[1], SRCPAINT);
            }
            return;
        }
        SelectObject(g_929a, g_9296);
        if (g_92a0)
            SelectPalette(g_929a, g_92a0, 0);
        DeleteDC(g_929a);
        DeleteObject(g_9294);
        g_929a = g_9294 = 0;
    } else if (g_929c >= 6)
        return;
    if (!g_92a6) {
        g_92a6 = GlobalAlloc(GHND, 8L);
        if (!g_92a6)
            return;
        g_3cc0 = (RECT *)GlobalLock(g_92a6);
        if (!g_3cc0) {
            GlobalFree(g_92a6);
            return;
        }
    }
    g_9294 = fn_10_9526(g_3cc0, g_92a6, 0x73, 0L, 0, 0L, 0, LO16(g_90ea), g_0010, x, y, 0);
    g_929a = CreateCompatibleDC(g_13dc);
    g_9296 = SelectObject(g_929a, g_9294);
    if (g_920e)
        g_92a0 = SelectPalette(g_929a, g_920e, 0);
    SetRect(&g_3ca8, g_3cc0[0].left, g_3cc0[0].top, g_3cc0[0].right, g_3cc0[0].bottom);
    g_3d48 = g_3ca4 = g_3cc0[0].left;
    g_3d4a = g_3ca6 = g_3cc0[0].top;
    g_92ba = g_3cc0[1].top;
    g_92de = g_0010;
    fn_15_8604();
    BitBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, g_929a, 0, 0, SRCCOPY);
    if (g_3cc0) {
        GlobalUnlock(g_92a6);
        g_3cc0 = 0;
        GlobalFree(g_92a6);
        g_92a6 = 0;
    }
}

/* Builds the 16-row perspective strip in g_3ccc[] from bitmap g_92b0[1]
 * [inferred]. */
/* 15:09e6 */
void fn_15_09e6(void)
{
    HGDIOBJ oldbmp;
    HDC dc;
    HPALETTE pal;
    int16_t i;
    int16_t size;
    int16_t dy;
    int16_t pct;
    int16_t scale;
    int16_t unit;
    int16_t y;
    int16_t unit2;
    int16_t u;
    int16_t j;
    BITMAP bm;

    if (g_90ee < 8)
        scale = 4;
    else
        scale = 2;
    if (g_90f4 == 0 || g_9563 == 0)
        unit = fn_15_2a08();
    else {
        GetObject(g_92b0[0], sizeof(BITMAP), &bm);
        unit = bm.bmHeight / scale;
    }
    g_92da = unit;
    size = unit * scale;
    unit2 = unit * 2;
    g_3d08[0].y = g_3d08[0].x = unit * 4;
    dy = (int16_t)((int16_t)(unit2 * -27) / 100 + unit * 4) / 15;
    y = unit * 4;
    g_3ce8[0] = 0;
    pct = 95;
    for (i = 1; i < 10; i++, pct -= 6) {
        g_3ce8[i] = y;
        g_3d08[i].x = g_3d08[i - 1].x - dy;
        g_3d08[i].y = g_3d08[i].x * pct / 100;
        y += g_3d08[i].y;
    }
    for (; i < 16; i++, pct += 13) {
        g_3ce8[i] = y;
        g_3d08[i].x = g_3d08[i - 1].x - dy;
        g_3d08[i].y = g_3d08[i].x * pct / 100;
        y += g_3d08[i].y;
    }
    dc = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(dc, g_92b0[1]);
    if (g_920e)
        pal = SelectPalette(dc, g_920e, 0);
    for (j = 0; j < 2; j++)
        if (g_3ccc[j]) {
            SelectObject(g_3cdc[j], g_3cd0[j]);
            if (j == 0)
                SelectPalette(g_3cdc[j], g_3ce0[j], 0);
            DeleteDC(g_3cdc[j]);
            g_3cdc[j] = 0;
            DeleteObject(g_3ccc[j]);
            g_3ccc[j] = 0;
        }
    g_3ccc[0] = CreateCompatibleBitmap(dc, g_3d08[0].x, y);
    g_3cdc[0] = CreateCompatibleDC(dc);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    if (g_920e)
        g_3ce0[0] = SelectPalette(g_3cdc[0], g_920e, 0);
    PatBlt(g_3cdc[0], 0, 0, g_3d08[0].x, y, BLACKNESS);
    SetStretchBltMode(g_3cdc[0], COLORONCOLOR);
    for (i = 0; i < 16; i++) {
        fn_10_740c();
        fn_10_9962(0, g_3cdc[0], 0, g_3ce8[i], g_3d08[i].x, g_3d08[i].y, dc, 0, 0,
                   size, size, SRCCOPY);
    }
    SelectObject(g_3cdc[0], g_3cd0[0]);
    g_3ccc[1] = fn_10_6ec6(g_3ccc[0]);
    g_3cdc[1] = CreateCompatibleDC(g_13dc);
    g_3cd0[1] = SelectObject(g_3cdc[1], g_3ccc[1]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    SelectObject(dc, oldbmp);
    if (pal)
        SelectPalette(dc, pal, 0);
    DeleteDC(dc);
}

/* 15:0cb0 */
void fn_15_0cb0(void)
{
    DWORD u;
    int16_t y;
    int16_t x;
    DWORD t;

    y = x = 0;
    fn_10_744c(0x6e);
    g_6e28 = g_1e50 + 90000L;
    if (g_90f4 == 0)
        PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
    if (g_90f4 == 0 && g_95b8 == 6) {
        if (!g_9298)
            g_92d4 = 9;
        else {
            fn_10_6da6(0, 1);
            fn_10_6e76(0x2006dL);
            if (!g_92a6) {
                g_92a6 = GlobalAlloc(GHND, 8L);
                if (!g_92a6)
                    return;
                g_3cc0 = (RECT *)GlobalLock(g_92a6);
                if (!g_3cc0) {
                    GlobalFree(g_92a6);
                    return;
                }
            }
            timeGetTime();
            g_9294 = fn_10_9526(g_3cc0, g_92a6, 100, 0L, 0, 0L, 0, LO16(g_90ea), g_0010, x, y, 0);
            g_929a = CreateCompatibleDC(g_13dc);
            g_9296 = SelectObject(g_929a, g_9294);
            if (g_920e)
                g_92a0 = SelectPalette(g_929a, g_920e, 0);
            timeGetTime();
            SetRect(&g_3ca8, g_3cc0[0].left, g_3cc0[0].top, g_3cc0[0].right, g_3cc0[0].bottom);
            SetRect(&g_3cb8, g_3cc0[1].left, g_3cc0[1].top, g_3cc0[1].right, g_3cc0[1].bottom);
            SetRect(&g_3cd4, g_3cc0[4].left, g_3cc0[4].top, g_3cc0[4].right, g_3cc0[4].bottom);
            g_3d48 = g_3ca4 = g_3cc0[0].left;
            g_3d4a = g_3ca6 = g_3cc0[0].top;
            g_92de = max(g_3cc0[2].bottom, g_3cc0[3].bottom);
            fn_15_8604();
            fn_15_8ae6();
            fn_15_0f2e();
            BitBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, g_929a, 0, 0, SRCCOPY);
            if (g_3cc0) {
                GlobalUnlock(g_92a6);
                g_3cc0 = 0;
                GlobalFree(g_92a6);
                g_92a6 = 0;
            }
            g_92d4 = 0;
            g_3cc4 = g_1e50 + 1100;
        }
    } else
        g_92d4 = 5;
    if (g_90f4) {
        fn_10_744c(0x4b);
        t = GetCurrentTime() + 1550;
        do
            fn_10_740c();
        while (GetCurrentTime() < t);
        g_92d8 = g_92d6;
        g_92d6 = 10;
    }
}

/* 15:0f2e */
void fn_15_0f2e(void)
{
    HBITMAP bmp;
    HGDIOBJ old1;
    HBITMAP bmp2;
    HGDIOBJ old2;
    HDC dc1;
    HDC dc2;
    HPALETTE oldpal;
    int16_t id;

    g_9214 = 0;
    fn_10_9672();
    if (!g_9214)
        return;
    if (g_9214 == 1)
        id = 0x110;
    if (g_9214 == 2)
        id = 0x112;
    if (g_9214 == 3)
        id = 0x116;
    if (g_9214 == 4)
        id = (rand() % 2 + 35) * 2;
    bmp = fn_10_6c02(id, 0, -1);
    bmp2 = fn_10_6ec6(bmp);
    dc1 = CreateCompatibleDC(g_13dc);
    dc2 = CreateCompatibleDC(g_13dc);
    old2 = SelectObject(dc2, bmp2);
    old1 = SelectObject(dc1, bmp);
    if (g_920e)
        oldpal = SelectPalette(dc1, g_920e, 0);
    fn_10_9962(0, g_929a, g_3cd4.left, g_3cd4.top, g_3cd4.right - g_3cd4.left,
               g_3cd4.bottom - g_3cd4.top, dc2, 0, 0, 29, 29, SRCAND);
    SetStretchBltMode(g_929a, COLORONCOLOR);
    fn_10_9962(0, g_929a, g_3cd4.left, g_3cd4.top, g_3cd4.right - g_3cd4.left,
               g_3cd4.bottom - g_3cd4.top, dc1, 0, 0, 29, 29, SRCPAINT);
    SelectObject(dc1, old1);
    SelectObject(dc2, old2);
    if (oldpal)
        SelectPalette(dc1, oldpal, 0);
    DeleteDC(dc1);
    DeleteObject(bmp);
    DeleteDC(dc2);
    DeleteObject(bmp2);
}

/* 15:1328 */
void fn_15_1328(int16_t full)
{
    int16_t i;
    int16_t j;
    DWORD t;

    fn_09_699e();
    if (g_92ac) {
        SelectObject(g_92b8, g_92ae);
        if (g_92c2)
            SelectPalette(g_92b8, g_92c2, 0);
        DeleteDC(g_92b8);
        DeleteObject(g_92ac);
        g_92ac = g_92b8 = 0;
        if (g_90f4 == 0 && g_3ccc[0] != 0) {
            t = GetCurrentTime();
            while (GetCurrentTime() - t < 1300)
                ;
        }
    }
    if (full) {
        for (i = 0; i < 3; i++)
            if (g_9534[i]) {
                DeleteObject(g_9534[i]);
                g_9534[i] = 0;
            }
        if (g_953a) {
            DeleteObject(g_953a);
            g_953a = 0;
        }
        if (g_953c) {
            DeleteObject(g_953c);
            g_953c = 0;
        }
    }
    for (j = 0; j < 2; j++)
        if (g_3ccc[j]) {
            SelectObject(g_3cdc[j], g_3cd0[j]);
            if (j == 0)
                SelectPalette(g_3cdc[j], g_3ce0[j], 0);
            DeleteDC(g_3cdc[j]);
            g_3cdc[j] = 0;
            DeleteObject(g_3ccc[j]);
            g_3ccc[j] = 0;
        }
    if (g_90f4 != 8 && g_929a) {
        SelectObject(g_929a, g_9296);
        if (g_92a0)
            SelectPalette(g_929a, g_92a0, 0);
        DeleteDC(g_929a);
        DeleteObject(g_9294);
        g_929a = g_9294 = 0;
    }
}

/* Step of a timed screen sequence, state g_92d4 [inferred]. */
/* 15:10be */
void fn_15_10be(void)
{
    DWORD u;
    DWORD t;
    DWORD t2;

    switch (g_92d4) {
    case 0:
        if (g_90f4 != 9)
            fn_10_7480(-1, 1);
        if (GetCurrentTime() > g_3cc4) {
            fn_15_52e4();
            g_92d4++;
        }
        break;
    case 2:
        fn_10_744c(0x4b);
        t = GetCurrentTime() + 1460;
        do
            fn_10_740c();
        while (GetCurrentTime() < t - 400);
        fn_15_482e();
        fn_10_740c();
        fn_15_09e6();
        do
            fn_10_740c();
        while (GetCurrentTime() < t);
        fn_15_4c76(1, 0);
        g_92d4++;
        break;
    case 3:
        fn_15_4c76(0, 0);
        break;
    case 4:
        if (g_90f4) {
            g_92d4++;
            break;
        }
    case 1:
        fn_15_1584(0);
        break;
    case 5:
        if (g_90f4 == 0) {
            BitBlt(g_929a, g_3ca4 + 29, g_3ca6 + 29, g_3ca8.right - g_3ca8.left - 58, g_92d2 - 58,
                   g_13dc, g_3d48 + 29, g_3d4a + 29, SRCCOPY);
            t = GetCurrentTime() + 800;
            do
                ;
            while (GetCurrentTime() < t);
        } else
            fn_15_09e6();
        fn_15_0000(2);
        g_3cc4 = GetCurrentTime() + 950;
        g_92d4++;
        break;
    case 6:
        if (GetCurrentTime() > g_3cc4) {
            g_92d4++;
            fn_15_0000(1);
        }
        break;
    case 7:
        if (!fn_15_0000(0))
            break;
    case 8:
        fn_10_740c();
        g_92d4++;
        break;
    case 9:
        fn_10_740c();
        fn_15_1328(1);
        fn_15_14be();
        if (g_90f4 == 0) {
            PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
            t2 = GetCurrentTime();
            do
                fn_10_740c();
            while (GetCurrentTime() - t2 < 450);
            fn_10_6e76(8L);
            fn_10_6dd4(0);
            g_95b8 = 7;
            if (!g_92e4)
                g_91f8 = 0;
            fn_06_1d9a();
            fn_06_1c72(1);
        } else if (g_90f4 == 6)
            g_914a++;
        else if (g_90f4 == 8)
            g_929c++;
        break;
    }
}

/* 15:14be */
void fn_15_14be(void)
{
    int16_t i;

    for (i = 0; i < 3; i++)
        if (g_92b0[i]) {
            DeleteObject(g_92b0[i]);
            g_92b0[i] = 0;
        }
    for (i = 0; i < 2; i++)
        if (g_3cc8[i]) {
            DeleteObject(g_3cc8[i]);
            g_3cc8[i] = 0;
        }
    fn_15_152e();
}

/* 15:152e */
void fn_15_152e(void)
{
    if (g_92b6) {
        SelectObject(g_92b6, g_92aa);
        if (g_92bc)
            SelectPalette(g_92b6, g_92bc, 0);
        DeleteDC(g_92b6);
        DeleteObject(g_92a8);
        g_92b6 = g_92a8 = 0;
    }
}

/* Scatters 250 random dots into two DCs [inferred]. POINT, not two ints:
 * CL does not CSE struct members across the calls. */
/* 15:28b2 */
void fn_15_28b2(HDC dc1, HDC dc2, int16_t a, int16_t b)
{
    int16_t i;
    HGDIOBJ old1;
    HGDIOBJ old2;
    int16_t h;
    int16_t w;
    int16_t sz;
    POINT pt;

    w = b * a - 3;
    h = (b - 8) * a;
    for (i = 0; i < 250; i++) {
        pt.x = rand() % w + 3;
        pt.y = rand() % h;
        if (rand() % 3) {
            sz = rand() % 4 + 2;
            old1 = SelectObject(dc1, GetStockObject(BLACK_BRUSH));
            old2 = SelectObject(dc2, GetStockObject(BLACK_BRUSH));
            Ellipse(dc1, pt.x, pt.y, pt.x + sz, pt.y + sz);
            Ellipse(dc2, pt.x, pt.y, pt.x + sz, pt.y + sz);
        } else {
            sz = rand() % 4 + 2;
            old1 = SelectObject(dc1, g_5ea8[0]);
            old2 = SelectObject(dc2, g_5ea8[0]);
            PatBlt(dc1, pt.x, pt.y, sz, sz, 0xa000c9L);
            PatBlt(dc2, pt.x, pt.y, sz, sz, 0xa000c9L);
        }
        SelectObject(dc1, old1);
        SelectObject(dc2, old2);
    }
}

/* 15:3bfa */
void fn_15_3bfa(int16_t w, int16_t h)
{
    if (g_92b8) {
        SelectObject(g_92b8, g_92ae);
        if (g_92c2)
            SelectPalette(g_92b8, g_92c2, 0);
        DeleteDC(g_92b8);
        DeleteObject(g_92ac);
        g_92ac = g_92b8 = 0;
    }
    g_92b8 = CreateCompatibleDC(g_13dc);
    g_92ac = CreateCompatibleBitmap(g_13dc, w, h);
    g_92ae = SelectObject(g_92b8, g_92ac);
    if (g_920e)
        g_92c2 = SelectPalette(g_92b8, g_920e, 0);
    PatBlt(g_92b8, 0, 0, w, h, BLACKNESS);
}

/* 15:3590 */
void fn_15_3590(void)
{
    int16_t i;

    switch (g_92a2) {
    case 0:
        if (!fn_15_3caa(0))
            break;
        if (g_90f4 == 9) {
            g_92a2 = 2;
            break;
        }
        g_17f2 = 0;
        g_92a2++;
        fn_15_1328(1);
        fn_15_1eac();
        if (!g_93a6)
            PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
        if (!g_0928) {
            fn_10_993a(3, 0xcc);
            fn_10_993a(2, 0x89);
        }
        if (g_90f4 == 6) {
            fn_10_6e76(MAKELONG(-1, 1));
            for (i = 40; i < 228; i += 4)
                fn_10_6d7a(i, i, i);
            fn_10_6e4c();
            fn_10_6da6(1, 0);
            fn_10_6e76(0x20000L);
            for (i = 40; i < 228; i += 4)
                fn_10_6d7a(i, i, i);
            fn_10_6e4c();
            fn_15_482e();
            fn_10_6e76(MAKELONG(-1, 1));
            fn_10_6dd4(1);
        } else
            fn_10_6e76(MAKELONG(-2, 2));
        fn_15_374c(1);
        break;
    case 1:
        if (g_17f2 == 0) {
            if (fn_15_374c(0)) {
                fn_10_744c(9);
                g_17f2 = g_1e50 + 1000;
            }
        } else if (g_1e50 > g_17f2)
            g_92a2++;
        break;
    case 2:
        if (g_90f4 == 6)
            g_914a++;
        else if (g_90f4 == 8)
            g_929c++;
        else if (g_90f4 == 9)
            g_92be++;
        break;
    }
}

/* Builds the two-frame bitmap pair g_3ccc[] from the bitmaps g_92b0[1..2]
 * [inferred]. */
/* 15:1eac */
void fn_15_1eac(void)
{
    int16_t u1[2];
    HGDIOBJ old[2];
    HDC dc[2];
    HPALETTE pal[2];
    int16_t i;
    int16_t u2[2];
    int16_t size;
    int16_t scale;
    int16_t h;

    if (g_90ee < 8)
        scale = 4;
    else
        scale = 2;
    size = (g_6e24[g_7090[main_ship].f_0d6].f_7a + (g_6e24[g_7090[main_ship].f_0d6].f_7b - 6) / 2) * scale;
    for (i = g_3ce8[0] = h = 0; i < 2; i++) {
        g_3d08[i].x = g_3d08[i].y = (g_6e24[g_7090[main_ship].f_0d6].f_7a
                                     + (g_6e24[g_7090[main_ship].f_0d6].f_7b - 6) / 2) * 4;
        g_3ce8[i] = h;
        h += g_3d08[i].y;
        dc[i] = CreateCompatibleDC(g_13dc);
        old[i] = SelectObject(dc[i], g_92b0[i + 1]);
        if (g_920e)
            pal[i] = SelectPalette(dc[i], g_920e, 0);
    }
    g_3ccc[0] = CreateCompatibleBitmap(dc[0], g_3d08[0].x, h);
    g_3cdc[0] = CreateCompatibleDC(dc[0]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    if (g_920e)
        g_3ce0[0] = SelectPalette(g_3cdc[0], g_920e, 0);
    PatBlt(g_3cdc[0], 0, 0, g_3d08[0].x, h, BLACKNESS);
    SetStretchBltMode(g_3cdc[0], COLORONCOLOR);
    for (i = 0; i < 2; i++)
        fn_10_9962(0, g_3cdc[0], 0, g_3ce8[i], g_3d08[i].x, g_3d08[i].y, dc[i], 0, 0,
                   size, size, SRCCOPY);
    SelectObject(g_3cdc[0], g_3cd0[0]);
    g_3ccc[1] = fn_10_6ec6(g_3ccc[0]);
    g_3cdc[1] = CreateCompatibleDC(g_13dc);
    g_3cd0[1] = SelectObject(g_3cdc[1], g_3ccc[1]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    for (i = 0; i < 2; i++) {
        SelectObject(dc[i], old[i]);
        if (pal[i])
            SelectPalette(dc[i], pal[i], 0);
        DeleteDC(dc[i]);
    }
}

/* Draws the grey-shaded backdrop into g_92b6 [inferred]. */
/* 15:4a2e */
void fn_15_4a2e(void)
{
    HGDIOBJ oldbr;
    HDC dc;
    HBITMAP bmp;
    HGDIOBJ oldbmp;
    int16_t i;
    int16_t step;
    int16_t c;
    int16_t u;

    dc = CreateCompatibleDC(g_92b6);
    oldbmp = SelectObject(dc, bmp = CreateCompatibleBitmap(dc, g_3ce6, g_3c8c[3].y));
    PatBlt(dc, 0, 0, g_3ce6, g_3c8c[3].y, BLACKNESS);
    oldbr = SelectObject(dc, GetStockObject(WHITE_BRUSH));
    Polygon(dc, g_3c8c, 4);
    SelectObject(dc, oldbr);
    step = 1700 / g_3c8c[3].y;
    c = 450;
    for (i = 0; i < g_3c8c[3].y - 2; i += 2) {
        oldbr = SelectObject(g_92b6, CreateSolidBrush(PALETTERGB(c / 10, c / 10, c / 10)));
        BitBlt(g_92b6, 0, i, g_3ce6, 2, dc, 0, i, MERGECOPY);
        DeleteObject(SelectObject(g_92b6, oldbr));
        c = min(2550, c += step);
    }
    SelectObject(dc, oldbmp);
    DeleteDC(dc);
    DeleteObject(bmp);
    oldbr = SelectObject(g_92b6, CreateSolidBrush(PALETTERGB(0x80, 0x80, 0x80)));
    PatBlt(g_92b6, g_3c8c[3].x + 1, g_3c8c[3].y, g_3ce6 - 2, 10, PATCOPY);
    DeleteObject(SelectObject(g_92b6, oldbr));
    step = 227;
    c = 450;
    for (i = 0; i < 18; i += 2) {
        oldbr = SelectObject(g_92b6, CreateSolidBrush(PALETTERGB(c / 10, c / 10, c / 10)));
        PatBlt(g_92b6, g_3ce6 / 2 + i + g_3c8c[3].x - 18, g_3c8c[3].y + 10, 2, 42, PATCOPY);
        PatBlt(g_92b6, g_3ce6 / 2 - i + g_3c8c[3].x + 16, g_3c8c[3].y + 10, 2, 42, PATCOPY);
        DeleteObject(SelectObject(g_92b6, oldbr));
        c = min((int16_t)(c + step), 2550);
    }
}

/* Builds the 16-row strip bitmaps g_3ccc[] at the sizes for g_9208 (or the
 * g_92be variants when g_90f4 == 9) [inferred]. */
/* 15:1a42 */
void fn_15_1a42(void)
{
    int16_t u;
    HGDIOBJ oldbmp;
    HPALETTE oldpal;
    int16_t i;
    int16_t a;
    int16_t b;
    int16_t size;
    int16_t mult;
    int16_t sum;
    int16_t div;
    int16_t step;
    int16_t k;

    if (g_90ee < 8)
        mult = 4;
    else
        mult = 2;
    g_92a4 = size = (g_6e24[g_7090[main_ship].f_0d6].f_7a
                     + (g_6e24[g_7090[main_ship].f_0d6].f_7b - 6) / 2) * mult;
    if (g_90f4 != 9 || !g_92be || g_92be == 2)
        fn_15_20ca();
    g_3d08[0].x = g_92c6;
    sum = g_3d08[0].y = g_92c8;
    g_3ce8[0] = 0;
    switch (g_9208) {
    case 0:
        a = 350;
        step = 16;
        div = 4;
        break;
    case 1:
        a = 450;
        step = 27;
        div = 5;
        break;
    case 2:
        a = 550;
        step = 39;
        div = 6;
        break;
    case 3:
        a = 650;
        step = 50;
        div = 7;
        break;
    }
    if (g_90f4 == 9) {
        k = g_3d08[0].x;
        i = sum = 0;
        for (; i < 16; i++) {
            if (!g_92be) {
                g_3d08[i].x = ((int16_t)(i * i) + 125L) * k * 12 / 7200;
                g_3d08[i].y = g_3d08[i].x * (i * 6 + 10) / 100;
            } else if (g_92be == 2) {
                g_3d08[i].x = ((int32_t)(int16_t)(i * i) * 14 + 1800) * k / 6000;
                g_3d08[i].y = g_3d08[i].x * 40 / 100;
            }
            g_3ce8[i] = sum;
            sum += g_3d08[i].y;
        }
        k = 15;
    } else {
        for (i = 1; i < 10; i++, a -= step) {
            g_3ce8[i] = sum;
            g_3d08[i].x = g_3d08[0].x / div * (a / 10) / 10;
            g_3d08[i].y = g_3d08[i].x * 40 / 100;
            sum += g_3d08[i].y;
        }
        b = 100;
        a = 10;
        for (i = 0; i < 6; i++, a += 2, b -= 12) {
            g_3ce8[15 - i] = sum;
            g_3d08[15 - i].x = g_3d08[0].x / div * a / 10;
            g_3d08[15 - i].y = g_3d08[15 - i].x * b / 100;
            sum += g_3d08[15 - i].y;
        }
        k = 0;
    }
    g_929e = CreateCompatibleDC(g_13dc);
    oldbmp = SelectObject(g_929e, g_92b0[1]);
    if (g_920e)
        oldpal = SelectPalette(g_929e, g_920e, 0);
    if (g_3ccc[0]) {
        SelectObject(g_3cdc[0], g_3cd0[0]);
        SelectPalette(g_3cdc[0], g_3ce0[0], 0);
        DeleteDC(g_3cdc[0]);
        g_3cdc[0] = 0;
        DeleteObject(g_3ccc[0]);
        g_3ccc[0] = 0;
    }
    g_3ccc[0] = CreateCompatibleBitmap(g_929e, g_3d08[k].x, sum);
    g_3cdc[0] = CreateCompatibleDC(g_929e);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    if (g_920e)
        g_3ce0[0] = SelectPalette(g_3cdc[0], g_920e, 0);
    PatBlt(g_3cdc[0], 0, 0, g_3d08[k].x, sum, BLACKNESS);
    SetStretchBltMode(g_3cdc[0], 3);
    if (g_90f4 == 9 && g_92be == 2)
        fn_07_13b2(1, 20, 0);
    if (!g_0928) {
        for (i = 0; i < 16; i++) {
            fn_10_9962(0, g_3cdc[0], 0, g_3ce8[i], g_3d08[i].x, g_3d08[i].y, g_929e, 0, 0,
                       size, size, SRCCOPY);
            if (g_90f4 == 9 && g_92be == 2 && i > 6)
                fn_07_158e();
        }
    }
    SelectObject(g_3cdc[0], g_3cd0[0]);
    g_3ccc[1] = fn_10_6ec6(g_3ccc[0]);
    g_3cdc[1] = CreateCompatibleDC(g_13dc);
    g_3cd0[1] = SelectObject(g_3cdc[1], g_3ccc[1]);
    g_3cd0[0] = SelectObject(g_3cdc[0], g_3ccc[0]);
    SelectObject(g_929e, oldbmp);
    if (oldpal)
        SelectPalette(g_929e, oldpal, 0);
    DeleteDC(g_929e);
    if (k == 15) {
        g_92d6 -= g_3d08[15].y + 10;
        fn_10_993a(3, 0x31);
        fn_10_993a(2, 0x49);
    }
}

/* Moves the ship sprite along the launch tube and draws it; returns 1
 * when it has left the tube [inferred]. */
/* 15:374c */
int16_t fn_15_374c(int16_t a)
{
    int16_t l4;
    int16_t sz;
    int16_t l8;
    int16_t da;
    int16_t db;
    RECT r;
    int16_t h;
    int16_t u;                      /* unused */
    HGDIOBJ old;

    sz = (g_6e24[g_7090[main_ship].f_0d6].f_7a + (g_6e24[g_7090[main_ship].f_0d6].f_7b - 6) / 2) * 4;
    if (a) {
        if (g_90f4 == 6) {
            g_9580 = CreateCompatibleDC(g_13dc);
            g_9584 = CreateCompatibleBitmap(g_13dc, LO16(g_90ea), g_0010);
            if (g_920e)
                g_9582 = SelectPalette(g_9580, g_920e, 0);
            g_9586 = SelectObject(g_9580, g_9584);
            PatBlt(g_9580, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
            g_3cb0.left = LO16(g_90ea) / 2 - g_3ce6 / 2;
            g_3cb0.right = g_3cb0.left + g_3ce6;
            g_3cb0.top = g_0010 - g_3c9a - 0x34;
            g_3cb0.bottom = g_3cb0.top + g_3c9a + 0x34;
            BitBlt(g_9580, g_3cb0.left, g_3cb0.top, g_3ce6, g_3c9a + 0x34, g_92b6, 0, 0, SRCCOPY);
            fn_16_1f78();
            g_92d6 = g_3cb0.top - sz + g_3c9a - 10;
            g_92d8 = g_92d6 - 300;
            if (g_0928)
                g_92d8 = g_92d6 + 1;
        } else {
            PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
            g_92d6 = -1;
            fn_15_0760();
            g_3cb0.right = LO16(g_90ea);
            g_3cb0.top = g_3cb0.left = 0;
            g_3cb0.bottom = g_0010;
            g_92d6 = g_92ba - sz;
            g_92d8 = g_3ca8.bottom - sz;
            if (g_0928)
                g_92d8 = g_92d6 + 1;
        }
        g_17fa = g_92d8 * 10;
        g_17f8 = g_17fc = 0;
        fn_15_3bfa(sz, sz + 40);
        g_17f6 = 150;
    } else if (g_0928) {
        g_92d8 = g_92d6 + 1;
        g_17fa = g_92d8 * 10;
    }
    if ((g_92d6 - 10) * 10 < g_17fa)
        g_17fc = 1;
    else if ((g_92d6 - 60) * 10 < g_17fa)
        g_17fc = 0;
    else if ((g_92d8 + 60) * 10 < g_17fa)
        g_17fc = 1;
    if (g_8ffc < 1300)
        g_17f6 = g_17f6 - 3 < 50 ? 50 : g_17f6 - 3;
    else
        g_17f6 = g_17f6 - 5 < 50 ? 50 : g_17f6 - 5;
    g_17f6 = g_17f6 > 120 ? 120 : g_17f6;
    if (g_0928)
        g_17f6 = 0;
    if (!g_17fc && g_17fc != g_17f8)
        fn_10_744c(0x20);
    g_17f8 = g_17fc;
    l4 = g_17fa / -10 + g_92d8;
    g_17fe.left = LO16(g_90ea) / 2 - sz / 2;
    g_17fe.top = g_17fa / 10;
    g_17fe.right = g_17fe.left + sz;
    g_17fe.bottom = g_17fe.top + sz + 40;
    PatBlt(g_92b8, 0, 0, g_17fe.right - g_17fe.left, g_17fe.bottom - g_17fe.top, BLACKNESS);
    if (IntersectRect(&r, &g_3cb0, &g_17fe)) {
        if (g_90f4 == 6)
            BitBlt(g_92b8, r.left - g_17fe.left, r.top - g_17fe.top, r.right - r.left,
                   r.bottom - r.top, g_92b6, r.left - g_3cb0.left, r.top - g_3cb0.top, SRCCOPY);
        else if (g_90f4 == 8)
            BitBlt(g_92b8, r.left - g_17fe.left, r.top - g_17fe.top, r.right - r.left,
                   r.bottom - r.top, g_929a, r.left - g_3cb0.left, r.top - g_3cb0.top, SRCCOPY);
    }
    l8 = g_17fa / -10 + g_92d6;
    if (l8 < 120 || g_90f4 == 8) {
        h = l8 / 2 + 4;
        if (g_90ee < 8)
            old = SelectObject(g_92b8, g_5ea8[0]);
        else
            old = SelectObject(g_92b8, g_5ea8[1]);
        if (g_90ee <= 8)
            BitBlt(g_92b8, 0, h + 5, sz, sz, g_3cdc[1], 0, g_3ce8[1], 0x00a803a9L);
        SelectObject(g_92b8, old);
    }
    BitBlt(g_92b8, 0, 5, sz, sz, g_3cdc[1], 0, g_3ce8[g_17fc], SRCAND);
    BitBlt(g_92b8, 0, 5, sz, sz, g_3cdc[0], 0, g_3ce8[g_17fc], SRCPAINT);
    BitBlt(g_13dc, g_17fe.left, g_17fe.top, g_17fe.right - g_17fe.left,
           g_17fe.bottom - g_17fe.top, g_92b8, 0, 0, SRCCOPY);
    if (g_8ffc < 1300) {
        da = 5;
        db = 3;
    } else {
        da = 6;
        db = 4;
    }
    if (g_17fc == 0)
        g_17fa += g_17f6 * 2 / da;
    else
        g_17fa += g_17f6 * 2 / db;
    if (g_92d6 * 10 < g_17fa) {
        if (g_90f4 == 8)
            g_92d8 = -1;
        return 1;
    }
    return 0;
}

/* Sets up the trapezoid view geometry (g_3c8c) and its memory DC [inferred]. */
/* 15:482e */
void fn_15_482e(void)
{
    int32_t l1, l2;
    g_3ce4 = ((int16_t)(HI16(g_90ea) * 4) / 3 - 1100) / 22 + 139;
    g_3ce6 = ((int16_t)(HI16(g_90ea) * 4) / 3 - 1100) / 36 + 164;
    g_92dc = 200;
    g_3c8c[0].x = g_3ce6 / 2 - g_3ce4 / 2;
    g_3c8c[0].y = 1;
    g_3c8c[1].x = g_3ce4 / 2 + g_3ce6 / 2;
    g_3c8c[1].y = 1;
    g_3c8c[2].x = g_3ce6;
    g_3c8c[2].y = ((int16_t)(HI16(g_90ea) * 4) / 3 - 1100) / 30 + 80;
    g_3c8c[3].x = 0;
    g_3c8c[3].y = g_3c8c[2].y;
    l1 = (g_3c8c[0].y - g_3c8c[3].y) * 100 / (g_3c8c[0].x - g_3c8c[3].x);
    l2 = (g_3c8c[1].y - g_3c8c[2].y) * 100 / (g_3c8c[1].x - g_3c8c[2].x);
    g_3c9c = (int16_t)(HI16(g_90ea) * 4) / 3 / 2 - g_3ce6 / 2;
    g_3c9e = 0;
    g_3ca0 = ((l1 - l2) * g_3c9c - l2 * g_3ce6) / (l1 - l2);
    g_3ca2 = l1 * (g_3ca0 - g_3c9c) / 100 + g_0010 - 0x34;
    if (g_92b6) {
        SelectObject(g_92b6, g_92aa);
        if (g_920e)
            SelectPalette(g_92b6, g_92bc, 0);
        DeleteObject(g_92a8);
        DeleteDC(g_92b6);
        g_92b6 = g_92a8 = 0;
    }
    g_92b6 = CreateCompatibleDC(g_13dc);
    g_92a8 = CreateCompatibleBitmap(g_13dc, g_3ce6, g_3c8c[3].y + 0x34);
    g_92aa = SelectObject(g_92b6, g_92a8);
    if (g_920e)
        g_92bc = SelectPalette(g_92b6, g_920e, 0);
    PatBlt(g_92b6, 0, 0, g_3ce6, g_3c8c[3].y + 0x34, BLACKNESS);
    fn_15_4a2e();
}

/* Loads the main ship's bitmap (g_92b0[0]) and its cockpit overlay and
 * returns its size [inferred]. */
/* 15:2a08 */
int16_t fn_15_2a08(void)
{
    int16_t i;
    int16_t sz;
    int16_t off;
    int16_t sc;
    int16_t id;
    int16_t c8;
    int16_t c7;
    int16_t v19;
    int16_t off14;
    int16_t v1a;
    int16_t save;
    HDC dcs2[2];
    HDC dcs1[2];
    HDC mdc;
    HGDIOBJ old2[2];
    HGDIOBJ old1[2];
    HBITMAP bmp;
    HGDIOBJ oldm;
    HPALETTE pal2[2];
    HPALETTE pal1[2];
    POINT pt;
    int16_t c4;
    int16_t c2;
    int16_t c0;
    int16_t be;
    char buf[20];
    char name[16];
    BITMAP bm;

    if (g_90ee < 8)
        sc = 4;
    else
        sc = 2;
    fn_14_3eda();
    if (g_92b0[0] == 0) {
        GetPrivateProfileString(g_9690, "MainShip", "EAGLE", buf, 20, g_96a9);
        for (i = 0; i < g_95aa; i++)
            if (lstrcmp(g_6e20[i].f_0a, buf) == 0)
                break;
        if (g_6e1c[g_6e20[i].f_21].f_20 & 4)
            be = 1;
        else
            be = 0;
        v19 = g_6e1c[g_6e20[i].f_21].f_19;
        if (g_6e1c[g_6e20[i].f_21].f_20 & 1)
            c2 = 0;
        else
            c2 = 1;
        if (g_6e20[i].f_09 & 1)
            c4 = 0;
        else
            c4 = 1;
        lstrcpy(name, g_6e1c[g_6e20[i].f_21].f_23);
        id = g_6e1c[g_6e20[i].f_21].f_21;
        c7 = g_6e20[i].f_07;
        c8 = g_6e20[i].f_08;
        if (g_6e1c[g_6e20[i].f_21].f_20 & 8)
            c0 = 1;
        else
            c0 = 0;
        v1a = g_6e1c[g_6e20[i].f_21].f_1a;
        g_92b0[0] = fn_10_73a6(id, name, -2, -2, 2, 0, 1, (char)c7, (char)c8);
        GetObject(g_92b0[0], sizeof(BITMAP), &bm);
        sz = bm.bmHeight / sc;
        off = (int16_t)(sz - v1a) / 2;
        g_92b0[1] = CreateCompatibleBitmap(g_13dc, sc * sz, sc * sz);
        save = g_9156;
        g_9156 = 1;
        g_3cc8[0] = fn_10_7032(1, 1, c4);
        g_3cc8[1] = fn_10_6ec6(g_3cc8[0]);
        g_9156 = save;
    } else {
        if (g_96d2[g_7090[main_ship].f_04e].f_28 == 3)
            be = 1;
        else
            be = 0;
        c4 = g_96d2[g_7090[main_ship].f_04e].f_44;
        GetObject(g_92b0[0], sizeof(BITMAP), &bm);
        sz = bm.bmHeight / sc;
        c0 = g_96d2[g_7090[main_ship].f_04e].f_48;
        c2 = g_7090[main_ship].f_0e4;
        v19 = g_6e1c[g_6e20[g_6e24[g_7090[main_ship].f_0d6].f_00].f_21].f_19;
    }
    fn_14_4074();
    if (g_92b0[2]) {
        DeleteObject(g_92b0[2]);
        g_92b0[2] = 0;
    }
    if (g_90f4 && !g_953f && !g_9563)
        return sz;
    bmp = fn_10_6ec6(g_92b0[0]);
    mdc = CreateCompatibleDC(g_13dc);
    oldm = SelectObject(mdc, bmp);
    for (i = 0; i < 2; i++)
        if (g_92b0[i]) {
            dcs1[i] = CreateCompatibleDC(g_13dc);
            old1[i] = SelectObject(dcs1[i], g_92b0[i]);
            pal1[i] = SelectPalette(dcs1[i], g_920e, 0);
        }
    for (i = 0; i < 2; i++) {
        dcs2[i] = CreateCompatibleDC(g_13dc);
        old2[i] = SelectObject(dcs2[i], g_3cc8[i]);
        pal2[i] = SelectPalette(dcs2[i], g_920e, 0);
    }
    BitBlt(dcs1[1], 0, 0, sc * sz, sc * sz, dcs1[0], 0, 0, SRCCOPY);
    if (c2) {
        pt.x = (int16_t)(sz - 9) / 2;
        pt.y = v19;
        if (sc == 4 && c4)
            off14 = 18;
        else
            off14 = 0;
        if (c0)
            PatBlt(dcs1[1], 0, 0, sc * sz, sc * sz, BLACKNESS);
        if (g_90f0 == 0) {
            BitBlt(dcs1[1], pt.x * sc, pt.y * sc, 36, 36, dcs2[1], 0, off14 * 2, SRCAND);
            BitBlt(dcs1[1], pt.x * sc, pt.y * sc, 36, 36, dcs2[0], 0, off14 * 2, SRCPAINT);
        } else {
            fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, sc * 9, sc * 9, dcs2[1], 0, off14,
                       18, 18, SRCAND);
            fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, sc * 9, sc * 9, dcs2[0], 0, off14,
                       18, 18, SRCPAINT);
        }
    }
    if (c0) {
        BitBlt(dcs1[1], 0, 0, sc * sz, sc * sz, mdc, 0, 0, SRCAND);
        BitBlt(dcs1[1], 0, 0, sc * sz, sc * sz, dcs1[0], 0, 0, SRCPAINT);
    }
    if (g_92e4) {
        if (!g_6e24[g_931c].f_72 && be) {
            PatBlt(dcs1[1], 0, 0, sc * off, sc * sz, BLACKNESS);
            PatBlt(dcs1[0], 0, 0, sc * off, sc * sz, BLACKNESS);
        }
        if (!g_6e24[g_931c].f_73 && be) {
            PatBlt(dcs1[1], (sz - off) * sc, 0, sc * off, sc * sz, BLACKNESS);
            PatBlt(dcs1[0], (sz - off) * sc, 0, sc * off, sc * sz, BLACKNESS);
        }
    }
    SelectObject(mdc, oldm);
    DeleteDC(mdc);
    DeleteObject(bmp);
    for (i = 0; i < 2; i++) {
        SelectObject(dcs2[i], old2[i]);
        SelectPalette(dcs2[i], pal2[i], 0);
        DeleteDC(dcs2[i]);
    }
    for (i = 0; i < 2; i++) {
        SelectObject(dcs1[i], old1[i]);
        if (pal1[i])
            SelectPalette(dcs1[i], pal1[i], 0);
        DeleteDC(dcs1[i]);
    }
    return sz;
}

/* Raises (a = 1) or lowers the ship panel below the view and draws the
 * ship in it [inferred]. */
/* 15:4c76 */
void fn_15_4c76(int16_t a, int16_t b)
{
    int16_t i;
    int16_t sz4;
    int16_t hgt;
    int16_t sc;
    HDC dc[3];
    HDC mdc2;
    HPALETTE pal[3];
    HPALETTE pal2;
    HGDIOBJ old[3];
    HBITMAP bmp;
    HGDIOBJ oldbrush;
    struct { int16_t x, y, w, h; } v;
    BITMAP bm;
    RECT ri;
    RECT ra;
    RECT rb;
    DWORD t0;

    if (g_90f4 && a && !b && g_9563) {
        t0 = GetCurrentTime();
        for (i = 0; i < 3; i++)
            if (g_92b0[i]) {
                DeleteObject(g_92b0[i]);
                g_92b0[i] = 0;
            }
        fn_15_2a08();
        do
            ;
        while (GetCurrentTime() - t0 < 2000);
    }
    GetObject(g_92b0[0], sizeof(BITMAP), &bm);
    if (g_90ee < 8)
        sc = 4;
    else
        sc = 2;
    hgt = bm.bmHeight;
    sz4 = hgt / sc * 4;
    if (a && !g_90f4 && !g_953c)
        g_953c = CreateCompatibleBitmap(g_13dc, g_3ce6, sz4 + 0x43);
    dc[0] = CreateCompatibleDC(g_13dc);
    old[0] = SelectObject(dc[0], g_953c);
    if (g_920e)
        pal[0] = SelectPalette(dc[0], g_920e, 0);
    SetStretchBltMode(dc[0], COLORONCOLOR);
    v.x = LO16(g_90ea) / 2 - g_3ce6 / 2;
    v.y = g_0010 - sz4 - 0x43;
    v.w = g_3ce6;
    v.h = sz4 + 0x3e;
    if (a) {
        fn_10_744c(5);
        if (b)
            g_181c = 0;
        else {
            if (!g_90f4)
                g_181c = v.h;
            PatBlt(dc[0], 0, 0, v.w, v.h, BLACKNESS);
            BitBlt(dc[0], 0, v.h - g_3c9a - 0x34, g_3ce6, g_3c9a + 0x34, g_92b6, 0, 0, SRCCOPY);
            bmp = fn_10_6ec6(g_92b0[0]);
            for (i = 1; i < 3; i++) {
                dc[i] = CreateCompatibleDC(g_13dc);
                if (g_920e)
                    pal[i] = SelectPalette(dc[i], g_920e, 0);
                if (i == 1)
                    old[i] = SelectObject(dc[i], g_92b0[0]);
                else
                    old[i] = SelectObject(dc[i], bmp);
            }
            if (g_90ee < 8)
                oldbrush = SelectObject(dc[0], g_5ea8[0]);
            else
                oldbrush = SelectObject(dc[0], g_5ea8[1]);
            if (g_90ee <= 8)
                fn_10_9962(0, dc[0], v.w / 2 - sz4 / 2, 9, sz4, sz4, dc[2], 0, 0, hgt, hgt,
                           0x00a803a9L);
            SelectObject(dc[0], oldbrush);
            fn_10_9962(0, dc[0], v.w / 2 - sz4 / 2, 5, sz4, sz4, dc[2], 0, 0, hgt, hgt, SRCAND);
            fn_10_9962(0, dc[0], v.w / 2 - sz4 / 2, 5, sz4, sz4, dc[1], 0, 0, hgt, hgt, SRCPAINT);
            for (i = 1; i < 3; i++) {
                SelectObject(dc[i], old[i]);
                if (pal[i])
                    SelectPalette(dc[i], pal[i], 0);
                DeleteDC(dc[i]);
            }
            DeleteObject(bmp);
        }
        if (g_95b8 == 6 && g_0010 - sz4 - 0x3e < g_92de && !g_92ac) {
            fn_15_3bfa(v.w, v.h);
            SelectObject(dc[0], old[0]);
            g_181e = fn_10_6ec6(g_953c);
            SelectObject(dc[0], g_953c);
        }
    }
    if (g_95b8 == 6 && g_92ac) {
        ra.left = g_3d48;
        ra.right = g_3d48 - g_3ca8.left + g_3ca8.right;
        ra.top = g_3d4a;
        ra.bottom = g_92de;
        rb.left = v.x;
        rb.right = rb.left + v.w;
        rb.top = g_181c + v.y;
        rb.bottom = rb.top + v.h;
        if (IntersectRect(&ri, &ra, &rb)) {
            mdc2 = CreateCompatibleDC(g_13dc);
            g_1820 = SelectObject(mdc2, g_181e);
            if (g_920e)
                pal2 = SelectPalette(mdc2, g_920e, 0);
            BitBlt(g_92b8, ri.left - rb.left, ri.bottom - rb.top, v.w, ri.top - ri.bottom + v.h,
                   dc[0], 0, ri.bottom - ri.top, SRCCOPY);
            BitBlt(g_92b8, ri.left - rb.left, ri.top - rb.top, v.w, v.h, dc[0], 0, 0, SRCCOPY);
            BitBlt(g_92b8, ri.left - rb.left, ri.top - rb.top, ri.right - ri.left,
                   ri.bottom - ri.top, g_929a, ri.left - ra.left + g_3ca4,
                   ri.top - ra.top + g_3ca6, SRCCOPY);
            BitBlt(g_92b8, ri.left - rb.left, ri.top - rb.top, ri.right - ri.left,
                   ri.bottom - ri.top, mdc2, 0, 0, SRCAND);
            BitBlt(g_92b8, ri.left - rb.left, ri.top - rb.top, ri.right - ri.left,
                   ri.bottom - ri.top, dc[0], 0, 0, SRCPAINT);
            BitBlt(g_13dc, v.x, g_181c + v.y, v.w, v.h, g_92b8, 0, 0, SRCCOPY);
            SelectObject(mdc2, g_1820);
            if (pal2)
                SelectPalette(mdc2, pal2, 0);
            DeleteDC(mdc2);
        } else
            BitBlt(g_13dc, v.x, g_181c + v.y, v.w, v.h, dc[0], 0, 0, SRCCOPY);
    } else
        BitBlt(g_13dc, v.x, g_181c + v.y, v.w, v.h, dc[0], 0, 0, SRCCOPY);
    SelectObject(dc[0], old[0]);
    if (pal[0])
        SelectPalette(dc[0], pal[0], 0);
    DeleteDC(dc[0]);
    if (b) {
        if (g_181c < v.h) {
            g_181c += 2;
            if (g_181c > v.h)
                g_181c = v.h;
            return;
        }
    } else if (g_181c > 5) {
        g_181c -= 2;
        if (g_181c < 5)
            g_181c = 5;
        return;
    } else if (!g_90f4) {
        g_92d4++;
        if (g_92ac) {
            SelectObject(g_92b8, g_92ae);
            if (g_92c2)
                SelectPalette(g_92b8, g_92c2, 0);
            DeleteDC(g_92b8);
            DeleteObject(g_92ac);
            g_92ac = g_92b8 = 0;
            if (g_181e)
                DeleteObject(g_181e);
        }
        return;
    }
    g_914a++;
}

/* Types the briefing text g_4fcc onto the screen a few characters per
 * call, with a cursor block and scrolling [inferred]. */
/* 15:1584 */
void fn_15_1584(int16_t a)
{
    HGDIOBJ oldfont;
    HFONT font;
    DWORD oldtc;
    DWORD oldbk;
    DWORD sz;
    int16_t k;
    int16_t cnt;
    int16_t h;
    int16_t w;
    RECT rc;
    RECT rc2;
    char word[50];
    int16_t wrap;
    int16_t m;
    int16_t j;
    int16_t n;

    h = (g_3ca8.right - g_3ca8.left - 63) / 15;
    w = (int16_t)(h * 8) / 21;
    if (a && g_92d4 == 0) {
        fn_15_84b0(LO16(g_90ea) / 2, g_92d2 / 2 + g_3ca6);
        g_17ec = g_17ea = g_092a = 0;
        cnt = 2;
        g_17e2.x = g_3d48 + 29;
        g_17e2.y = g_3d4a + 29;
        g_17ee = g_1e50 + 500;
        return;
    }
    if (a && g_92d4 < 2) {
        g_92d4 = 2;
        for (k = g_17ea; lstrlen(g_4fcc) > k; k++)
            if (g_4fcc[k] == 13 && g_4fcc[k + 2] == ' ') {
                g_17ea = k;
                return;
            }
        return;
    }
    if (g_17ee > g_1e50)
        return;
    g_17ee = g_1e50 + 40;
    cnt = 2;
    if (g_092a)
        return;
    font = CreateFont(h, w, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0x22, "Arial");
    oldfont = SelectObject(g_13dc, font);
    oldbk = SetBkColor(g_13dc, 0L);
    SetBkMode(g_13dc, OPAQUE);
    SetTextAlign(g_13dc, 0);
    oldtc = SetTextColor(g_13dc, RGB(0, 255, 0));
    for (k = 0; k < cnt; k++) {
        if (g_4fcc[g_17ea] < 13 && g_4fcc[g_17ea] != 0 && g_4fcc[g_17ea] != 10)
            g_4fcc[g_17ea] = 13;
        wrap = 0;
        if (g_4fcc[g_17ea] == ' ') {
            int16_t x;

            n = 0;
            j = g_17ea;
            do
                word[++n] = g_4fcc[++j];
            while (g_4fcc[j] != 0 && g_4fcc[j] != ' ' && g_4fcc[j] != 13);
            word[n + 1] = 0;
            x = GetTextExtent(g_13dc, word, n) + g_17e2.x;
            m = 9;
            if (g_6084.right - m < x)
                wrap = 1;
        }
        if (g_4fcc[g_17ea] == 13 || wrap) {
            g_17ec++;
            g_17e2.x = g_3d48 + 29;
            if (g_4fcc[g_17ea] == 13)
                g_17ea++;
            if ((g_92d2 - 58) / (h + 1) <= g_17ec) {
                int16_t s;

                SetRect(&rc, g_6084.left, g_6084.top, g_6084.right, g_6084.bottom);
                for (s = 0; s < (int16_t)(h + 1); s++)
                    ScrollDC(g_13dc, 0, -1, &rc, &rc, 0, &rc2);
                g_17e6.y -= h + 1;
            } else
                g_17e2.y += h + 1;
        } else {
            HGDIOBJ old;
            /* block-scope int views of g_17e6.y / g_17e2.y: only to get the
             * game's add order (global before h) */

            if (g_17ea)
                PatBlt(g_13dc, g_17e6.x + 2, (int16_t)(h * 10) / -13 + g_17e6.y + h, (int16_t)(h * 6) / 13, (int16_t)(h * 10) / 13,
                       BLACKNESS);
            TextOut(g_13dc, g_17e2.x, g_17e2.y, g_4fcc + g_17ea, 1);
            sz = GetTextExtent(g_13dc, g_4fcc + g_17ea, 1);
            g_17e2.x += LOWORD(sz);
            old = SelectObject(g_13dc, CreateSolidBrush(RGB(0x80, 0xff, 0)));
            PatBlt(g_13dc, g_17e2.x + 2, (int16_t)(h * 10) / -13 + g_17e2.y + h, (int16_t)(h * 6) / 13, (int16_t)(h * 10) / 13,
                   PATCOPY);
            DeleteObject(SelectObject(g_13dc, old));
            g_17e6 = g_17e2;
        }
        g_17ea++;
        fn_10_754a(0x2b, 0, 0, 0);
        if (!a && g_4fcc[g_17ea] == 13 && g_4fcc[g_17ea - 1] == 10) {
            g_17ee = g_1e50 + 1900;
            break;
        }
        if (g_4fcc[g_17ea] == 13 && g_4fcc[g_17ea + 2] == ' ') {
            if (g_90f4 == 8)
                g_929c++;
            else if (g_90f4 == 9)
                g_92be++;
            else
                g_92d4++;
            break;
        }
        if (g_4fcc[g_17ea] == 0) {
            if (g_90f4 == 8)
                g_929c++;
            else if (g_90f4 == 9)
                g_92be++;
            else
                g_92d4++;
            g_092a = 1;
            break;
        }
    }
    SetBkColor(g_13dc, oldbk);
    SetTextColor(g_13dc, oldtc);
    SelectObject(g_13dc, oldfont);
    if (font) {
        DeleteObject(font);
        font = 0;
    }
}

/* Builds the briefing text in g_4fcc: header, restored-game summary or
 * the default text resource, then the difficulty line [inferred]. */
/* 15:52e4 */
void fn_15_52e4(void)
{
    HGLOBAL hres;
    char *lp;
    int16_t v2;
    int16_t i;
    int16_t len2;
    int16_t len1;
    int16_t v1;
    int16_t id;
    char buf[200];
    char name[220];
    char str[40];
    int16_t space;
    HFILE hf;
    int16_t min;
    int16_t sec;
    int16_t pad[8];
    DWORD size;
    int32_t pad2;
    HGLOBAL hmem;
    REC_1A9_seg15b *rec;
    OFSTRUCT of;

    g_93a8 = GlobalAlloc(GHND, 2000L);
    g_4fcc = GlobalLock(g_93a8);
    LoadString(g_9212, 0x24e, buf, 30);
    lstrcpy(g_4fcc, buf);
    v1 = fn_10_9764(1);
    v2 = fn_10_9764(0);
    if (v2 == 2)
        v2 = -41;
    fn_10_a332(g_4fcc, 0xbd8, 1, v2 != 3, v1 + 0x24f, v2 + 0x27f, v2 == 3, 0x282,
               (LPSTR)g_380c);
    lstrcpy(buf, g_9078);
    lstrcat(buf, g_96b8);
    GetPrivateProfileString(g_9690, "Restore", "", name, 9, g_96a9);
    for (i = space = 0; i < lstrlen(name); i++)
        if (name[i] == ' ')
            space = 1;
    if (!space) {
        lstrcat(buf, name);
        lstrcat(buf, ".sav");
        hf = OpenFile(buf, &of, 0);
        if (hf == -1)
            return;
        hmem = GlobalAlloc(GHND, 0x1a9L);
        GlobalLock(hmem);
        size = GlobalSize(hmem);
        GlobalUnlock(hmem);
        fn_14_4006(hf, (char *)(rec = (REC_1A9_seg15b *)GlobalLock(
                                         hmem = GlobalReAlloc(hmem, size, GHND))), size);
        _lclose(hf);
        rec->f_18b = rec->f_18b / 36;
        min = (int16_t)rec->f_18b / 60;
        sec = (int16_t)rec->f_18b - min * 60;
        if (rec->f_15e >= 100)
            rec->f_15e -= 100;
        if (rec->f_032 == rec->f_160) {
            if (rec->f_160 == 1)
                LoadString(g_9212, 0x9c7, str, 40);
            else
                LoadString(g_9212, 0x9c5, str, 40);
        } else if (rec->f_160 == 0) {
            if (rec->f_032 > 1)
                LoadString(g_9212, 0x9c6, str, 40);
            else
                LoadString(g_9212, 0x9e1, str, 40);
        } else
            fn_10_a332(str, 0x9c4, 1, rec->f_160);
        fn_10_a332(g_4fcc, 0xbb8, 0, 0, rec->f_024, min, 0x9c9, sec, 0x9c8, rec->f_032, 0x13e,
                   (LPSTR)str);
        if (rec->f_15a || rec->f_15c)
            fn_10_a332(g_4fcc, 0xbb9, 0, rec->f_156 + rec->f_158, 0x9d3, rec->f_15a, rec->f_15a,
                       0x9d3, rec->f_15c, rec->f_15c, 0x9d3);
        fn_10_a332(g_4fcc, 0xbd7, 0, rec->f_164 > 400, rec->f_15e + 0x137);
        GlobalUnlock(hmem);
        GlobalFree(hmem);
    } else {
        lp = 0;
        hres = LoadResource(g_9212, FindResource(g_9212, MAKEINTRESOURCE(210),
                                                 MAKEINTRESOURCE(5000)));
        if (hres)
            lp = LockResource(hres);
        len1 = lstrlen(lp);
        len2 = lstrlen(g_4fcc);
        for (i = 0; i < len1; i++, len2++)
            g_4fcc[len2] = lp[i];
        if (lp) {
            GlobalUnlock(hres);
            lp = 0;
        }
        if (hres) {
            FreeResource(hres);
            hres = 0;
        }
    }
    switch (g_9214) {
    case 1:
        id = 0xeb;
        break;
    case 2:
        id = 0xec;
        break;
    case 4:
        id = 0xf0;
    case 3:
        id = 0x288;
        break;
    default:
        id = 0x288;
        break;
    }
    fn_10_a332(g_4fcc, 0xbd6, 0, g_9214 != 3, g_9214 == 3, !g_9214, g_9214 != 0, id,
               (LPSTR)g_380c);
    fn_11_3fd4(g_4fcc, 1);
    fn_15_1584(1);
}

/* near-match 41%: 15:454c (draws the shaded side walls and the four
 * perspective lines [inferred]). Frame and first 0xad bytes match; the game
 * subtracts the spilled x0 straight from memory (CL reloads it into dx),
 * loads ybot's g_6db6 into dx, and in the loop computes pt.x in cx keeping
 * x0/xa in ax (CL computes into ax). The never-read x0/xa assignments in
 * the loop give the game's (int)i CSE in si; 19 instructions differ. */
void fn_15_454c(void)
{
    HGDIOBJ oldbrush;
    int16_t c[3];
    int16_t k;
    int16_t x0;                     /* x0, xa, mid, xb, h, y1, y2: register locals */
    POINT pt;
    int16_t ytop;
    int16_t xa, mid, xb, h, y1;
    int16_t ybot;
    int16_t y2;
    int32_t i;
    int32_t dy1;
    int32_t dy2;
    int32_t w;
    int32_t dh;
    HGDIOBJ oldpen;
    HDC dc;

    dc = g_9580 ? g_9580 : g_13dc;
    x0 = g_6dac + g_6db4;
    xa = x0 + 2;
    ytop = g_6dae + g_6db6;
    mid = LO16(g_90ea) / 2;
    xb = mid - 90;
    y1 = (int32_t)(int16_t)(mid - xa - 90) * (g_3ca2 - g_6db6) / (mid - xa) + g_6db6;
    y2 = ytop + (int32_t)(int16_t)(mid - xa - 90) * (g_3ca2 - ytop) / (mid - xa);
    w = (int16_t)(xb - x0);
    dh = (int16_t)(ytop - (ybot = g_6db6));
    dy1 = y1 - g_6db6;
    dy2 = (int16_t)(y2 - ytop);
    for (i = 0; i < w; i += 2) {
        for (k = 0; k < 3; k++)
            c[k] = i * -150 / w + 170;
        pt.x = (x0 = g_6dac + g_6db4) + (int16_t)i;
        pt.y = dy1 * i / w + ybot;
        h = (dy2 - dy1) * i / w + dh;
        oldbrush = SelectObject(dc, CreateSolidBrush(PALETTERGB(c[0], c[1], c[2])));
        PatBlt(dc, pt.x, pt.y, 2, h, PATCOPY);
        pt.x = (xa = g_6db0 - 2) - (int16_t)i;
        PatBlt(dc, pt.x, pt.y, 2, h + 2, PATCOPY);
        DeleteObject(SelectObject(dc, oldbrush));
    }
    oldpen = SelectObject(dc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
    MoveTo(dc, g_6dac + g_6db4 + 2, ybot - 1);
    LineTo(dc, LO16(g_90ea) / 2, g_3ca2);
    MoveTo(dc, g_6dac + g_6db4 + 2, ytop);
    LineTo(dc, LO16(g_90ea) / 2, g_3ca2 + 2);
    MoveTo(dc, g_6db0 - 2, ybot);
    LineTo(dc, LO16(g_90ea) / 2, g_3ca2);
    MoveTo(dc, g_6db0 - 2, ytop);
    LineTo(dc, LO16(g_90ea) / 2, g_3ca2);
    DeleteObject(SelectObject(dc, oldpen));
}

/* Opens the briefing screen: background bitmap, layout rects and the
 * "loading" caption [inferred]. */
/* 15:302e */
void fn_15_302e(void)
{
    char s[80];
    char t[40];
    int16_t u1, u2;
    int16_t jy;
    int16_t jx;

    jy = jx = 0;
    fn_13_65f2(3);
    if (g_90f4 != 9)
        fn_10_7480(-2, 1);
    if (g_90f4 != 9 || !g_92be) {
        fn_10_744c(0x6e);
        if (!g_93a6)
            PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
        fn_10_6da6(0, 1);
        if (!g_93a6 && (g_8ffc < 850 || g_8ffc < 1600 && g_90ee < 8)) {
            lstrcpy(s, "");
            if (LO16(g_90ea) > 700) {
                LoadString(g_9212, 0x859, t, 40);
                lstrcat(s, t);
            }
            LoadString(g_9212, 0x85a, t, 40);
            lstrcat(s, t);
            fn_10_94c4(0, 6, RGB(0, 255, 0), LO16(g_90ea) / 2, HI16(g_90ea) / 2, s);
        }
    }
    g_92d6 = (int32_t)g_0010 * 22 / 100;
    g_92d8 = g_0010 - 10;
    if (g_90f4 == 9 && !g_92be) {
        g_92d8 = g_0010 / 30;
        g_92d6 = g_0010 * 4 / 10;
    }
    if (!g_0928) {
        if (!g_92a6) {
            if (!(g_92a6 = GlobalAlloc(GHND, 8L)))
                return;
            if (!(g_3cc0 = (RECT *)GlobalLock(g_92a6))) {
                GlobalFree(g_92a6);
                return;
            }
        }
        if (g_90f4 == 6) {
            g_9294 = fn_10_9526(g_3cc0, g_92a6, 0x69, 0L, 0, 0L, 0, LO16(g_90ea), g_0010, jx, jy, 0);
            g_929a = CreateCompatibleDC(g_13dc);
            g_9296 = SelectObject(g_929a, g_9294);
            if (g_920e)
                g_92a0 = SelectPalette(g_929a, (HPALETTE)g_920e, 0);
            g_92de = g_3cc0->bottom;
            g_92d6 = g_3cc0[1].top - 40;
        } else if (g_90f4 == 8) {
            g_9294 = fn_10_9526(g_3cc0, g_92a6, 0x6e, 0L, 0, 0L, 0, LO16(g_90ea), g_0010, jx, jy, 0);
            g_929a = CreateCompatibleDC(g_13dc);
            g_9296 = SelectObject(g_929a, g_9294);
            if (g_920e)
                g_92a0 = SelectPalette(g_929a, (HPALETTE)g_920e, 0);
            SetRect(&g_3ca8, g_3cc0->left, g_3cc0->top, g_3cc0->right, g_3cc0->bottom);
            g_92de = g_0010;
            g_92d6 = g_3ca8.top + 20;
        } else if (g_90f4 == 9) {
            if (!g_92be) {
                g_9294 = fn_10_9526(g_3cc0, g_92a6, 0x78, 0L, 0, 0L, 0, LO16(g_90ea), g_0010, jx, jy, 0);
                g_929a = CreateCompatibleDC(g_13dc);
                g_9296 = SelectObject(g_929a, g_9294);
                if (g_920e)
                    g_92a0 = SelectPalette(g_929a, (HPALETTE)g_920e, 0);
                SetRect(&g_3ca8, g_3cc0->left, g_3cc0->top, g_3cc0->right, g_3cc0->bottom);
                g_92c0 = g_3cc0[1].top;
                g_92de = g_0010;
            } else if (g_92be == 2) {
                PatBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, BLACKNESS);
                fn_10_6da6(1, 1);
                jy = -201;
                jx = 500;
                fn_10_744c(0x6e);
            reload:     /* bare label: keeps jx/jy in memory (layout only) */
                g_9294 = fn_10_9526(g_3cc0, g_92a6, 100, 0L, 0, 0L, 0, LO16(g_90ea), g_0010, jx, jy, 0x4b);
                g_929a = CreateCompatibleDC(g_13dc);
                g_9296 = SelectObject(g_929a, g_9294);
                if (g_920e)
                    g_92a0 = SelectPalette(g_929a, (HPALETTE)g_920e, 0);
                SetRect(&g_3ca8, g_3cc0->left, g_3cc0->top, g_3cc0->right, g_3cc0->bottom);
                SetRect(&g_3cb8, g_3cc0[1].left, g_3cc0[1].top, g_3cc0[1].right, g_3cc0[1].bottom);
                SetRect(&g_3cd4, g_3cc0[4].left, g_3cc0[4].top, g_3cc0[4].right, g_3cc0[4].bottom);
                g_3d48 = g_3ca4 = g_3cc0->left;
                g_3d4a = g_3ca6 = g_3cc0->top;
                g_92de = g_3cc0[2].bottom < g_3cc0[3].bottom ? g_3cc0[3].bottom : g_3cc0[2].bottom;
                fn_15_8604();
                fn_15_8ae6();
                g_92d8 = (g_3ca8.bottom - g_3ca8.top) * 2 / 5 + g_3ca8.top;
                g_92d6 = g_0010 * 7 / 10;
            }
        }
        BitBlt(g_13dc, 0, 0, LO16(g_90ea), g_0010, g_929a, 0, 0, SRCCOPY);
        if (g_3cc0) {
            GlobalUnlock(g_92a6);
            g_3cc0 = 0;
            GlobalFree(g_92a6);
            g_92a6 = 0;
        }
    }
    fn_15_1a42();
    g_92a2 = 0;
    fn_15_3caa(1);
    if (g_90ee >= 8 && g_093c) {
        if (g_8ffc > 2000)
            g_9004 <<= 2;
        else if (g_8ffc > 1500)
            g_9004 <<= 1;
    }
    g_093c = 0;
}

/* Moves the briefing ship sprite one step down the screen (scaled sprite
 * frames from g_3d08/g_3ce8, sound pitch via fn_10_993a); returns 0 once
 * it has arrived [inferred]. */
/* 15:0000 */
int16_t fn_15_0000(int16_t a)
{
    int16_t p;
    int16_t w4;
    int16_t y;
    int16_t ten;
    int16_t c;
    int16_t e;
    int16_t prev;
    int16_t old17d0;
    int16_t u14;
    int16_t v;
    RECT rc;
    int16_t a20;
    int16_t k;                      /* unused */
    BITMAP bm;
    HGDIOBJ old;
    DWORD t;

    if (g_90f4 == 0)
        w4 = g_92da * 4;
    else {
        GetObject((HGDIOBJ)g_92b0[0], sizeof bm, &bm);
        if (g_90ee < 8)
            g_17ce = 4;
        else
            g_17ce = 2;
        w4 = bm.bmHeight / g_17ce * 4;
    }
    if (a == 2) {
        fn_10_744c(0x20);
        g_3cb0.left = LO16(g_90ea) / 2 - g_3ce6 / 2;
        g_3cb0.right = g_3cb0.left + g_3ce6;
        g_3cb0.top = g_0010 - g_3c9a - 0x34;
        g_3cb0.bottom = g_3cb0.top + g_3c9a + 0x34;
        g_17d2.left = g_3d48;
        g_17d2.right = g_3d48 - g_3ca8.left + g_3ca8.right;
        g_17d2.top = g_3d4a;
        g_17d2.bottom = g_92de;
        if (g_92b6)
            g_92d8 = g_3cb0.top - w4 + g_3c9a - 10;
        if (g_90f4 == 0) {
            g_92d6 = 60;
            BitBlt(g_13dc, g_3cb0.left, g_3cb0.top, g_3ce6, g_3c9a + 0x34, (HDC)g_92b6, 0, 0,
                   SRCCOPY);
        } else if (g_90f4 == 6)
            g_92d6 = -10;
        else if (g_90f4 == 8) {
            g_92d6 = (g_3ca8.bottom - g_3ca8.top) / 4 + g_3ca6;
            BitBlt(g_929a, g_3ca8.left, g_3ca8.top, g_3ca8.right - g_3ca8.left,
                   g_3ca8.bottom - g_3ca8.top, g_13dc, g_3ca8.left, g_3ca8.top, SRCCOPY);
        }
        g_17c2 = g_92d8 * 10;
        fn_15_3bfa(g_3d08[0].x, g_3d08[0].y + 15);
        g_17c8 = 150;
        g_17ca = 0;
        g_17d0 = 100;
    } else if (a == 1)
        fn_10_744c(0x1c);
    prev = g_17ca;
    if (prev < 10) {
        p = g_17c2 / -10 + g_92d8;
        g_17c6 = (g_92d8 - g_92d6) / 2 / 10;
        if (!g_17c6)
            g_17c6 = 1;
        g_17ca = p / g_17c6 > 15 ? 15 : p / g_17c6;
    } else {
        p = (g_92d6 - g_92d8) / 2 - g_17c2 / 10 + g_92d8;
        g_17c6 = (g_92d8 - g_92d6) / 2 / 6;
        if (!g_17c6)
            g_17c6 = 1;
        g_17ca = p / g_17c6 + 10 > 15 ? 15 : p / g_17c6 + 10;
    }
    g_17da.left = LO16(g_90ea) / 2 - g_3d08[0].x / 2;
    g_17da.right = g_17da.left + g_3d08[0].x;
    g_17da.top = g_17c2 / 10;
    g_17da.bottom = g_17da.top + g_3d08[0].y + 15;
    if (prev < g_17ca) {
        u14 = g_17da.top + a20 + c;     /* sic: a20, c unset on first call */
        old17d0 = g_17d0;
        g_17d0 = g_17ca * -100 / 40 + 100;
        if (!old17d0)
            old17d0 = 1;
        v = g_17d0 * 100 / old17d0;
        fn_10_993a(3, v);
        fn_10_993a(2, (int16_t)(v + 200) / 3);
    }
    if (a == 2)
        g_17cc = g_17da.top;
    if (g_8ffc < 1400)
        g_17c8 = 150 - g_17ca / 2;
    else
        g_17c8 = 150 - g_17ca * 4;
    g_17c8 = g_17c8 < 9 ? 9 : g_17c8;
    PatBlt((HDC)g_92b8, 0, 0, g_17da.right - g_17da.left, g_17da.bottom - g_17da.top, BLACKNESS);
    if ((g_95b8 == 6 || g_90f4 == 8) && IntersectRect(&rc, &g_17d2, &g_17da))
        BitBlt((HDC)g_92b8, rc.left - g_17da.left, rc.top - g_17da.top, rc.right - rc.left,
               rc.bottom - rc.top, g_929a, rc.left - g_17d2.left + g_3ca4,
               rc.top - g_17d2.top + g_3ca6, SRCCOPY);
    if (g_92b6 && IntersectRect(&rc, &g_3cb0, &g_17da))
        BitBlt((HDC)g_92b8, rc.left - g_17da.left, rc.top - g_17da.top, rc.right - rc.left,
               rc.bottom - rc.top, (HDC)g_92b6, rc.left - g_3cb0.left, rc.top - g_3cb0.top,
               SRCCOPY);
    y = g_17c2 / -10 + g_92d8;
    if (y < 80 || g_90f4 == 0) {
        if (g_90f4 == 0) {
            if (g_17c2 / 10 - g_92d6 < 40)
                y = g_17c2 / 10 - g_92d6;
            y = y > 40 ? 40 : y;
        }
        a20 = y / 3 + 4;
        e = g_17cc - g_17da.top;
        ten = g_3d08[0].y - e - a20 + 14;
        c = ten > g_3d08[g_17ca].y ? g_3d08[g_17ca].y : ten;
        if (g_90ee < 8)
            old = SelectObject((HDC)g_92b8, g_5ea8[0]);
        else
            old = SelectObject((HDC)g_92b8, g_5ea8[1]);
        if (g_90ee <= 8)
            BitBlt((HDC)g_92b8, g_3d08[0].x / 2 - g_3d08[g_17ca].x / 2, a20, g_3d08[g_17ca].x, c,
                   g_3cdc[1], 0, g_3ce8[g_17ca], 0x00a803a9L);
        SelectObject((HDC)g_92b8, old);
    }
    BitBlt((HDC)g_92b8, g_3d08[0].x / 2 - g_3d08[g_17ca].x / 2, 0, g_3d08[g_17ca].x,
           g_3d08[g_17ca].y, g_3cdc[1], 0, g_3ce8[g_17ca], SRCAND);
    BitBlt((HDC)g_92b8, g_3d08[0].x / 2 - g_3d08[g_17ca].x / 2, 0, g_3d08[g_17ca].x,
           g_3d08[g_17ca].y, g_3cdc[0], 0, g_3ce8[g_17ca], SRCPAINT);
    BitBlt(g_13dc, g_17da.left, g_17da.top, g_17da.right - g_17da.left,
           g_17da.bottom - g_17da.top, (HDC)g_92b8, 0, 0, SRCCOPY);
    g_17cc = g_17da.top;
    if (g_8ffc < 1400)
        g_17c2 += g_17c8 * 5 / -7;
    else
        g_17c2 += g_17c8 * 3 / -7;
    if (g_92d6 * 10 > g_17c2) {
        if (g_90f4 == 0) {
            BitBlt(g_13dc, g_3ca4 + 29, g_3ca6 + 29, g_3ca8.right - g_3ca8.left - 58, g_92d2 - 58,
                   g_929a, g_3d48 + 29, g_3d4a + 29, SRCCOPY);
            fn_10_754a(0x4c, 0, 0, 0);
        } else {
            fn_10_744c(0x15);
            if (g_929a) {
                BitBlt(g_13dc, g_17da.left, g_17da.top, g_17da.right - g_17da.left,
                       g_17da.bottom - g_17da.top, g_929a, g_17da.left, g_17da.top, SRCCOPY);
                SelectObject(g_929a, g_9296);
                if (g_92a0)
                    SelectPalette(g_929a, g_92a0, 0);
                DeleteDC(g_929a);
                DeleteObject(g_9294);
                g_929a = g_9294 = 0;
            } else
                PatBlt(g_13dc, g_17da.left, g_17da.top, g_17da.right - g_17da.left,
                       g_17da.bottom - g_17da.top, BLACKNESS);
        }
        fn_15_84b0((g_17da.right - g_17da.left) / 2 + g_17da.left, g_17da.top + 12);
        if (g_90f4 == 0) {
            BitBlt(g_13dc, g_3ca4 + 29, g_3ca6 + 29, g_3ca8.right - g_3ca8.left - 58, g_92d2 - 58,
                   g_929a, g_3d48 + 29, g_3d4a + 29, SRCCOPY);
            t = GetCurrentTime() + 1460;
            do
                fn_10_740c();
            while (GetCurrentTime() < t);
        }
        return 1;
    }
    return 0;
}

/* Builds the bitmaps of the current object's ship (g_92b0[], g_3cc8[]) and
 * sets the panel sizes g_92c6/g_92c8 [inferred]. */
/* 15:20ca */
void fn_15_20ca(void)
{
    int16_t i;
    int16_t sz;
    int16_t off;
    int16_t sc;
    int16_t off14;
    int16_t save;
    HDC dcs2[2];
    HDC dcs1[3];
    HDC mdc;
    HGDIOBJ old2[2];
    HGDIOBJ old1[3];
    HBITMAP bmp;
    HGDIOBJ oldm;
    HPALETTE pal2[2];
    HPALETTE pal1[3];
    POINT pt;
    int16_t be;

    if (g_90ee < 8)
        sc = 4;
    else
        sc = 2;
    if (g_96d2[g_7090[main_ship].f_04e].f_44)
        be = 1;
    else
        be = 0;
    sz = g_6e24[g_7090[main_ship].f_0d6].f_7a + (g_6e24[g_7090[main_ship].f_0d6].f_7b - 6) / 2;
    g_92b0[0] = fn_10_73a6(g_96d2[g_7090[main_ship].f_04e].f_36, g_96d2[g_7090[main_ship].f_04e].f_84,
                           -2, -2, 2, 0, 1, LO8(g_96d2[g_7090[main_ship].f_04e].f_18),
                           LO8(g_96d2[g_7090[main_ship].f_04e].f_1a));
    g_92b0[1] = CreateCompatibleBitmap(g_13dc, sc * sz, sc * sz);
    g_92b0[2] = CreateCompatibleBitmap(g_13dc, sc * sz, sc * sz);
    bmp = fn_10_6ec6(g_92b0[0]);
    mdc = CreateCompatibleDC(g_13dc);
    oldm = SelectObject(mdc, bmp);
    save = g_9156;
    g_9156 = 1;
    g_3cc8[0] = fn_10_7032(1, 1, be);
    g_9156 = save;
    g_3cc8[1] = fn_10_6ec6(g_3cc8[0]);
    for (i = 0; i < 3; i++) {
        dcs1[i] = CreateCompatibleDC(g_13dc);
        old1[i] = SelectObject(dcs1[i], g_92b0[i]);
        pal1[i] = SelectPalette(dcs1[i], g_920e, 0);
    }
    for (i = 0; i < 2; i++) {
        dcs2[i] = CreateCompatibleDC(g_13dc);
        old2[i] = SelectObject(dcs2[i], g_3cc8[i]);
        pal2[i] = SelectPalette(dcs2[i], g_920e, 0);
    }
    fn_14_3eda();
    if (!g_96d2[g_7090[main_ship].f_04e].f_48) {
        if (g_90f4 == 9)
            fn_10_9962(0, dcs1[1], 0, sc * sz - 1, sc * sz, -(sc * sz), dcs1[0], 0, 0, sc * sz,
                       sc * sz, SRCCOPY);
        else
            BitBlt(dcs1[1], 0, 0, sc * sz, sc * sz, dcs1[0], 0, 0, SRCCOPY);
        off = sz / 2 - g_6e1c[g_6e20[g_6e24[g_7090[main_ship].f_0d6].f_00].f_21].f_1a / 2;
        if (!g_7090[main_ship].f_0ac && g_96d2[g_7090[main_ship].f_04e].f_28 == 3)
            PatBlt(dcs1[1], 0, 0, sc * off, sc * sz, BLACKNESS);
        if (!g_7090[main_ship].f_0ad && g_96d2[g_7090[main_ship].f_04e].f_28 == 3)
            PatBlt(dcs1[1], (sz - off) * sc, 0, sc * off, sc * sz, BLACKNESS);
        BitBlt(dcs1[2], 0, 0, sc * sz, sc * sz, dcs1[1], 0, 0, SRCCOPY);
        if (!g_9e5b)
            fn_15_28b2(dcs1[1], dcs1[2], sc, sz);
    }
    if (g_7090[main_ship].f_0e4) {
        pt.x = sz / 2 - 4;
        pt.y = g_6e1c[g_6e20[g_6e24[g_7090[main_ship].f_0d6].f_00].f_21].f_19;
        if (g_90f4 == 9)
            pt.y = sz - pt.y;
        if (sc == 4 && g_96d2[g_7090[main_ship].f_04e].f_44)
            off14 = 18;
        else
            off14 = 0;
        if (g_96d2[g_7090[main_ship].f_04e].f_48)
            PatBlt(dcs1[1], 0, 0, sc * sz, sc * sz, BLACKNESS);
        if (g_90f0 == 0) {
            if (g_90f4 == 9) {
                fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, 36, -36, dcs2[1], 0, off14 * 2,
                           36, 36, SRCAND);
                fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, 36, -36, dcs2[0], 0, off14 * 2,
                           36, 36, SRCPAINT);
            } else {
                BitBlt(dcs1[1], pt.x * sc, pt.y * sc, 36, 36, dcs2[1], 0, off14 * 2, SRCAND);
                BitBlt(dcs1[1], pt.x * sc, pt.y * sc, 36, 36, dcs2[0], 0, off14 * 2, SRCPAINT);
            }
        } else if (g_90f4 == 9) {
            fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, sc * 9, -(sc * 9), dcs2[1], 0, off14,
                       18, 18, SRCAND);
            fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, sc * 9, -(sc * 9), dcs2[0], 0, off14,
                       18, 18, SRCPAINT);
        } else {
            fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, sc * 9, sc * 9, dcs2[1], 0, off14,
                       18, 18, SRCAND);
            fn_10_9962(0, dcs1[1], pt.x * sc, pt.y * sc, sc * 9, sc * 9, dcs2[0], 0, off14,
                       18, 18, SRCPAINT);
        }
    }
    fn_14_4074();
    if (g_96d2[g_7090[main_ship].f_04e].f_48) {
        if (g_90f4 == 9) {
            fn_10_9962(0, dcs1[1], 0, sc * sz, sc * sz, -(sc * sz), mdc, 0, 0, sc * sz, sc * sz,
                       SRCAND);
            fn_10_9962(0, dcs1[1], 0, sc * sz, sc * sz, -(sc * sz), dcs1[0], 0, 0, sc * sz,
                       sc * sz, SRCPAINT);
            fn_10_9962(0, dcs1[2], 0, sc * sz, sc * sz, -(sc * sz), dcs1[0], 0, 0, sc * sz,
                       sc * sz, SRCCOPY);
        } else {
            BitBlt(dcs1[1], 0, 0, sc * sz, sc * sz, mdc, 0, 0, SRCAND);
            BitBlt(dcs1[1], 0, 0, sc * sz, sc * sz, dcs1[0], 0, 0, SRCPAINT);
            BitBlt(dcs1[2], 0, 0, sc * sz, sc * sz, dcs1[0], 0, 0, SRCCOPY);
        }
        fn_14_3eda();
        off = sz / 2 - g_6e1c[g_6e20[g_6e24[g_7090[main_ship].f_0d6].f_00].f_21].f_1a / 2;
        fn_14_4074();
        if (!g_7090[main_ship].f_0ac && g_96d2[g_7090[main_ship].f_04e].f_28 == 3) {
            PatBlt(dcs1[1], 0, 0, sc * off, sc * sz, BLACKNESS);
            PatBlt(dcs1[2], 0, 0, sc * off, sc * sz, BLACKNESS);
        }
        if (!g_7090[main_ship].f_0ad && g_96d2[g_7090[main_ship].f_04e].f_28 == 3) {
            PatBlt(dcs1[1], (sz - off) * sc, 0, sc * off, sc * sz, BLACKNESS);
            PatBlt(dcs1[2], (sz - off) * sc, 0, sc * off, sc * sz, BLACKNESS);
        }
        if (!g_9e5b)
            fn_15_28b2(dcs1[1], dcs1[2], sc, sz);
    }
    SelectObject(mdc, oldm);
    DeleteDC(mdc);
    DeleteObject(bmp);
    for (i = 0; i < 2; i++) {
        SelectObject(dcs2[i], old2[i]);
        SelectPalette(dcs2[i], pal2[i], 0);
        DeleteDC(dcs2[i]);
    }
    for (i = 0; i < 3; i++) {
        SelectObject(dcs1[i], old1[i]);
        if (pal1[i])
            SelectPalette(dcs1[i], pal1[i], 0);
        DeleteDC(dcs1[i]);
    }
    switch (g_9208) {
    case 0:
        g_92c6 = sz * 4;
        g_92c8 = (int16_t)(sz * 16) / 10;
        break;
    case 1:
        g_92c6 = sz * 5;
        g_92c8 = sz * 2;
        break;
    case 2:
        g_92c6 = sz * 6;
        g_92c8 = (int16_t)(sz * 24) / 10;
        break;
    case 3:
        g_92c6 = sz * 7;
        g_92c8 = (int16_t)(sz * 28) / 10;
        break;
    }
}

/* Animates the ship taking off from / landing in the briefing panel one
 * step per call; returns 1 while still moving [inferred]. */
/* 15:3caa */
int16_t fn_15_3caa(int16_t a)
{
    int16_t hh;
    int16_t dx6;
    int16_t d8;
    int16_t ten;
    int16_t c;
    int16_t prev;
    int16_t old1812;
    int16_t u12;                    /* unused */
    int16_t v;
    int16_t k0;
    int16_t k1;
    int16_t hgt;
    int16_t yoff;
    HGDIOBJ old;

    if (g_0928)
        return 1;
    if (g_90f4 == 9) {
        k0 = 15;
        k1 = 0;
    } else {
        k0 = 0;
        k1 = 15;
    }
    if (a) {
        g_180c = g_92d8 * 10;
        g_180e = 0;
        fn_10_744c(0x1c);
        g_3cb0.right = LO16(g_90ea);
        g_3cb0.top = g_3cb0.left = 0;
        g_3cb0.bottom = g_92de;
        fn_15_3bfa(g_3d08[k0].x, g_3d08[k0].y + 15);
        g_1806 = (g_92d8 - g_92d6) / 16;
        g_1808 = 150;
        g_180a = 0;
        g_1812 = 100;
        if (g_90f4 == 9)
            g_1812 = 50;
    }
    if (!g_1806)
        g_1806 = 1;
    if (g_180e == 0 || g_180e == 2) {
        int16_t y;
        RECT rc;

        y = g_180c / -10 + g_92d8 - 55;
        prev = g_180a;
        g_180a = y / g_1806;
        if (g_90f4 == 9 && g_92be >= 0)
            g_180a = (int32_t)(g_180c / 10 - g_92d8) * 15 / (g_92d6 - g_92d8);
        g_180a = g_180a > 15 ? 15 : g_180a;
        g_180a = g_180a < 0 ? 0 : g_180a;
        if (g_180e == 2)
            g_180a = 15;
        g_1814.left = LO16(g_90ea) / 2 - g_3d08[k0].x / 2;
        g_1814.top = g_180c / 10;
        if (a)
            g_1810 = g_1814.top;
        g_1814.right = g_3d08[k0].x + g_1814.left;
        g_1814.bottom = g_3d08[k0].y + g_1814.top + 15;
        if (prev < g_180a && g_180e == 0) {
            old1812 = g_1812;
            if (g_90f4 == 9)
                g_1812 = g_180a * 100 / 30 + 50;
            else
                g_1812 = g_180a * -100 / 30 + 100;
            if (!old1812)
                old1812 = 1;
            v = g_1812 * 100 / old1812;
            fn_10_993a(3, v);
            fn_10_993a(2, (int16_t)(v + 200) / 3);
        }
        if (g_90f4 == 9) {
            if (g_180e == 0) {
                if (g_92be == 1)
                    g_1808 = (int32_t)g_180a * g_180a * g_180a * 40 / 1000 + 15;
                else {
                    g_1808 = (int32_t)g_180a * g_180a * 44 / 100 + 50;
                    if (g_180a == 7 && prev == 6)
                        fn_10_744c(0x27);
                }
            } else
                g_1808 = 150;
            g_1814.top -= 15;
            g_1814.bottom -= 15;
        } else
            g_1808 = 150 - g_180a * 4 < 9 ? 9 : 150 - g_180a * 4;
        PatBlt((HDC)g_92b8, 0, 0, g_1814.right - g_1814.left, g_1814.bottom - g_1814.top,
               BLACKNESS);
        if (IntersectRect(&rc, &g_3cb0, &g_1814))
            BitBlt((HDC)g_92b8, rc.left - g_1814.left, rc.top - g_1814.top, rc.right - rc.left,
                   rc.bottom - rc.top, g_929a, rc.left, rc.top - g_3cb0.top, SRCCOPY);
        if (g_180a < 10) {
            dx6 = 25 - g_180a * 2;
            hh = (15 - g_180a) * 4;
        } else {
            dx6 = 15 - g_180a;
            hh = 30 - g_180a;
        }
        d8 = g_1810 - g_1814.top;
        ten = g_3d08[k0].y - d8 - hh + 14;
        c = ten > g_3d08[g_180a].y ? g_3d08[g_180a].y : ten;
        if (g_90f4 != 9) {
            if (g_90ee < 8)
                old = SelectObject((HDC)g_92b8, g_5ea8[0]);
            else
                old = SelectObject((HDC)g_92b8, g_5ea8[1]);
            if (g_90ee <= 8)
                BitBlt((HDC)g_92b8, g_3d08[k0].x / 2 - g_3d08[g_180a].x / 2 + dx6, hh,
                       g_3d08[g_180a].x, c, g_3cdc[1], 0, g_3ce8[g_180a], 0x00a803a9L);
            SelectObject((HDC)g_92b8, old);
        }
        yoff = 0;
        if (g_90f4 == 9 && g_180e == 2) {
            hgt = g_180c / -10 + g_3ca8.top;
            hgt = hgt < 0 ? 0 : hgt;
            if (g_180c / 10 + g_3d08[g_180a].y > g_92c0) {
                yoff = g_180c / -10 + g_92c0;
                yoff = yoff < 0 ? 0 : yoff;
                hgt = g_3d08[g_180a].y - yoff;
                hgt = hgt < 0 ? 0 : hgt;
            }
        } else
            hgt = g_3d08[g_180a].y;
        BitBlt((HDC)g_92b8, g_3d08[k0].x / 2 - g_3d08[g_180a].x / 2, yoff + k0, g_3d08[g_180a].x,
               hgt, g_3cdc[1], 0, g_3ce8[g_180a] + yoff, SRCAND);
        BitBlt((HDC)g_92b8, g_3d08[k0].x / 2 - g_3d08[g_180a].x / 2, yoff + k0, g_3d08[g_180a].x,
               hgt, g_3cdc[0], 0, g_3ce8[g_180a] + yoff, SRCPAINT);
        BitBlt(g_13dc, g_1814.left, g_1814.top, g_1814.right - g_1814.left,
               g_1814.bottom - g_1814.top, (HDC)g_92b8, 0, 0, SRCCOPY);
        g_1810 = g_1814.top;
        if (g_90f4 == 9) {
            g_180c += g_1808 * 2 / 3;
            if (g_180c > g_92d6 * 10) {
                if (g_180e == 0 && g_92be == 1) {
                    g_92d8 = g_92d6;
                    g_92d6 = g_0010 * 7 / 10;
                    g_180e = 2;
                } else {
                    if (g_92be != 3)
                        return 1;
                    BitBlt(g_13dc, g_1814.left, g_1814.top, g_1814.right - g_1814.left,
                           g_1814.bottom - g_1814.top, g_929a, g_1814.left, g_1814.top,
                           SRCCOPY);
                    return 1;
                }
            }
        } else {
            g_180c += g_1808 * 2 / -3;
            if (g_180c < g_92d6 * 10) {
                g_180c -= 20;
                g_1808 = 200;
                g_180e = 1;
            }
        }
    } else {
        int16_t y;
        RECT rc;

        g_1808 = g_1808 - 5 < 50 ? 50 : g_1808 - 5;
        y = g_180c / -10 + g_92d8 - 55;    /* never read */
        g_1814.left = LO16(g_90ea) / 2 - g_3d08[k0].x / 2;
        g_1814.top = g_180c / 10;
        g_1814.right = g_1814.left + g_3d08[k0].x;
        g_1814.bottom = g_1814.top + g_3d08[k0].y + 15;
        PatBlt((HDC)g_92b8, 0, 0, g_1814.right - g_1814.left, g_1814.bottom - g_1814.top,
               BLACKNESS);
        if (IntersectRect(&rc, &g_3cb0, &g_1814))
            BitBlt((HDC)g_92b8, rc.left - g_1814.left, rc.top - g_1814.top, rc.right - rc.left,
                   rc.bottom - rc.top, g_929a, rc.left, rc.top - g_3cb0.top, SRCCOPY);
        if (g_180a < 10) {
            dx6 = 25 - g_180a * 2;
            hh = (15 - g_180a) * 4;
        } else {
            dx6 = 15 - g_180a;
            hh = 30 - g_180a;
        }
        if (g_90ee < 8)
            old = SelectObject((HDC)g_92b8, g_5ea8[0]);
        else
            old = SelectObject((HDC)g_92b8, g_5ea8[1]);
        if (g_90ee <= 8)
            BitBlt((HDC)g_92b8, g_3d08[k0].x / 2 - g_3d08[g_180a].x / 2 + dx6, hh,
                   g_3d08[g_180a].x, g_3d08[g_180a].y, g_3cdc[1], 0, g_3ce8[g_180a],
                   0x00a803a9L);
        SelectObject((HDC)g_92b8, old);
        BitBlt((HDC)g_92b8, g_3d08[k0].x / 2 - g_3d08[k1].x / 2, 2, g_3d08[k1].x, g_3d08[k1].y,
               g_3cdc[1], 0, g_3ce8[15], SRCAND);
        BitBlt((HDC)g_92b8, g_3d08[k0].x / 2 - g_3d08[k1].x / 2, 2, g_3d08[k1].x, g_3d08[k1].y,
               g_3cdc[0], 0, g_3ce8[15], SRCPAINT);
        BitBlt(g_13dc, g_1814.left, g_1814.top, g_1814.right - g_1814.left,
               g_1814.bottom - g_1814.top, (HDC)g_92b8, 0, 0, SRCCOPY);
        g_180c += g_1808 * 2 / 20;
        if (g_180c > (g_92d6 + 44) * 10)
            return 1;
    }
    return 0;
}
