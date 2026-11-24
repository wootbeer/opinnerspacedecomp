/* ISPACE.DLL, the game's graphics and support library, called by ordinal
 * through the pointers fetched in fn_10_6656.  Native versions of its
 * routines, written from the DLL's code; those not done yet are stubs.
 * The palette manager is in ispace_pal.c, the image loader in
 * ispace_img.c, the dialogs in ispace_dlg.c, the copy checks in
 * ispace_reg.c, the rooms in ispace_room.c and ispace_shape.c, the
 * panel helpers in ispace_panel.c, ordinal 2's surfaces in
 * ispace_surface.c. */

#include <stdlib.h>
#include <string.h>

#include "gdi.h"
#include "ispace.h"
#include "ne.h"

/* GCC allows function pointer casts through void (*)(void). */
#define PROC(f) ((FARPROC)(void (*)(void))(f))

HINSTANCE ispace_module(void)
{
    static HINSTANCE h;

    if (!h)
        h = LoadLibrary(GAME_DIR "ISPACE.DLL");
    return h;
}

HINSTANCE igraphic_module(void)
{
    static HINSTANCE h;

    if (!h)
        h = LoadLibrary(GAME_DIR "IGRAPHIC.DLL");
    return h;
}

/* Ordinal 3 (5:0612): LoadBitmap of name from IGRAPHIC.DLL; SD_LOGO comes
 * from ISPACE.DLL itself. */
int16_t ispace_load_bitmap(LPCSTR name)
{
    HINSTANCE m = lstrcmp(name, "SD_LOGO") == 0 ? ispace_module() : igraphic_module();
    uint32_t size;
    const uint8_t *dib = module_resource(m, MAKEINTRESOURCE(RT_BITMAP_), name, &size);

    return dib ? (int16_t)gdi_bitmap_from_dib(dib, size) : 0;
}

/* Ordinal 6 (5:0650): a monochrome mask of bitmap bm, 1 where it is black. */
HBITMAP ispace_make_mask(int16_t pal, int16_t bm, int16_t dc)
{
    BITMAP info;
    HBITMAP mask, old[2];
    HDC dcs[2];
    HPALETTE old_pal = 0;
    COLORREF bk;
    int i;

    if (!GetObject(bm, sizeof info, &info))
        return 0;
    mask = CreateBitmap(info.bmWidth, info.bmHeight, 1, 1, NULL);
    for (i = 0; i < 2; i++)
        dcs[i] = CreateCompatibleDC(dc);
    old[0] = SelectObject(dcs[0], bm);
    old[1] = SelectObject(dcs[1], mask);
    if (pal)
        old_pal = SelectPalette(dcs[0], pal, 0);
    bk = SetBkColor(dcs[0], RGB(0, 0, 0));
    BitBlt(dcs[1], 0, 0, info.bmWidth, info.bmHeight, dcs[0], 0, 0, SRCCOPY);
    SetBkColor(dcs[0], bk);
    if (old_pal)
        SelectPalette(dcs[0], old_pal, 0);
    for (i = 0; i < 2; i++) {
        SelectObject(dcs[i], old[i]);
        DeleteDC(dcs[i]);
    }
    return mask;
}

/* 5:0062 (with 5:0106): a copy of bitmap bm, doubled in both directions
 * when doubled is set and mirrored where xdir or ydir is -1, made as the
 * DLL makes it in an 8-bit DIB (rows bottom-up, padded to 4 bytes).  A
 * doubled and mirrored copy is one column off: each pixel's right half
 * goes one column right of its place, the first column stays 0 and the
 * last spills into the row padding or the next row (the DLL's
 * allocation had room for it; here the buffer has a spare row). */
static HBITMAP double_mirror(HPALETTE pal, HBITMAP bm, int doubled, int xdir, int ydir)
{
    Bmp *b = handle_get(bm, H_BITMAP), *ob;
    int f = doubled ? 2 : 1, w, h, dw, dh, i, j;
    long stride, base;
    uint8_t *buf;
    HBITMAP out;

    if (!pal || ispace_pal_slot(pal) < 0 || !b)
        return 0;
    w = b->w;
    h = b->h;
    dw = w * f;
    dh = h * f;
    stride = (dw + 3) & ~3;
    buf = calloc((size_t)stride * (dh + 1), 1);
    if (!buf)
        return 0;
    base = ydir == -1 ? (h - 1) * stride * f : 0;
    if (xdir == -1)
        base += dw - 1;
    for (j = 0; j < h; j++) {
        const uint8_t *row = b->px + (size_t)(h - 1 - j) * w;
        for (i = 0; i < w; i++) {
            long o = base + (long)i * xdir * f;
            buf[o] = row[i];
            if (doubled) {
                buf[o + stride + 1] = row[i];
                buf[o + stride] = row[i];
                buf[o + 1] = row[i];
            }
        }
        base += stride * ydir * f;
    }
    out = gdi_new_bitmap(dw, dh, 0);
    ob = handle_get(out, H_BITMAP);
    for (j = 0; ob && j < dh; j++)
        memcpy(ob->px + (size_t)j * dw, buf + (dh - 1 - j) * stride, (size_t)dw);
    free(buf);
    return out;
}

/* Ordinal 36 (10:2e1a): StretchBlt for a destination twice the source,
 * or mirrored (negative width or height).  The source rectangle is
 * copied, doubled when either side is twice the source's, mirrored, and
 * blitted; a mirrored width that is not a multiple of the source's is
 * stretched from the mirrored copy at the source's size.  Returns what
 * the DLL leaves in AX: the last DeleteObject's result. */
int16_t ispace_blit_double(HDC dst, int16_t x, int16_t y, int16_t w, int16_t h, HDC src,
                                  int16_t xs, int16_t ys, int16_t ws, int16_t hs, int32_t rop)
{
    int16_t out_w = w, out_h = h;
    HPALETTE pal = ispace_pal_handle(ispace_dialog_slot()), old_pal = 0;
    HBITMAP bm, copy, old;
    HDC mdc;
    int doubled;

    if (ws == 0)
        return 0;   /* the DLL divides by ws */
    if ((w < 0 || h < 0) && w % ws != 0) {
        w = w < 0 ? -ws : ws;
        h = h < 0 ? -hs : hs;
    }
    mdc = CreateCompatibleDC(src);
    bm = CreateCompatibleBitmap(src, ws, hs);
    if (pal)
        old_pal = SelectPalette(mdc, pal, 0);
    old = SelectObject(mdc, bm);
    BitBlt(mdc, 0, 0, ws, hs, src, xs, ys, SRCCOPY);
    SelectObject(mdc, old);
    if (pal)
        SelectPalette(mdc, old_pal, 0);
    DeleteDC(mdc);
    doubled = 2 * abs(ws) == abs(w) || 2 * abs(hs) == abs(h);
    if (h < 0)
        y = (int16_t)(y + out_h + 1);
    if (w < 0)
        x = (int16_t)(x + out_w + 1);
    copy = double_mirror(pal, bm, doubled, w < 0 ? -1 : 1, h < 0 ? -1 : 1);
    mdc = CreateCompatibleDC(dst);
    if (pal)
        old_pal = SelectPalette(mdc, pal, 0);
    old = SelectObject(mdc, copy);
    if (out_w != w)
        StretchBlt(dst, x, y, (int16_t)abs(out_w), (int16_t)abs(out_h), mdc, 0, 0, (int16_t)abs(w),
                   (int16_t)abs(h), rop);
    else
        BitBlt(dst, x, y, (int16_t)abs(w), (int16_t)abs(h), mdc, 0, 0, rop);
    SelectObject(mdc, old);
    if (pal)
        SelectPalette(mdc, old_pal, 0);
    DeleteDC(mdc);
    DeleteObject(copy);
    return (int16_t)DeleteObject(bm);
}

static int16_t ispace_7(int32_t a, int16_t b) { (void)a; (void)b; STUB(); return 1; }
static int16_t ispace_8(POINT a, int16_t b, int16_t c, int32_t d) { (void)a; (void)b; (void)c; (void)d; STUB(); return 0; }
static int16_t ispace_9(int16_t a, POINT b, int16_t c, int32_t d, int32_t e, DWORD f, LPCSTR g) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; STUB(); return 0; }
static int16_t ispace_15(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h, int16_t i) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; STUB(); return 0; }
static void ispace_17(int16_t a, int16_t b, int32_t c, int16_t d, int16_t e, int16_t f, int16_t g, char h, char i, int16_t j, int16_t k, char l, char m) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; (void)l; (void)m; STUB(); }
static int16_t ispace_41(int16_t a, int32_t b) { (void)a; (void)b; STUB(); return 0; }

FARPROC ispace_proc(int ordinal)
{
    switch (ordinal) {
    case 1: return PROC(ispace_load_image);
    case 2: return PROC(ispace_build_surface);
    case 3: return PROC(ispace_load_bitmap);
    case 4: return PROC(ispace_palette);
    case 5: return PROC(ispace_image_height);
    case 6: return PROC(ispace_make_mask);
    case 7: return PROC(ispace_7);
    case 8: return PROC(ispace_8);
    case 9: return PROC(ispace_9);
    case 10: return PROC(ispace_dialog);
    case 12: return PROC(ispace_smooth_image);
    case 14: return PROC(ispace_pal_scale);
    case 15: return PROC(ispace_15);
    case 17: return PROC(ispace_17);
    case 18: return PROC(ispace_sprite_sheet);
    case 24: return PROC(ispace_check);
    case 29: return PROC(ispace_collide);
    case 32: return PROC(ispace_room);
    case 33: return PROC(ispace_letters);
    case 34: return PROC(ispace_bevel);
    case 35: return PROC(ispace_gauge);
    case 36: return PROC(ispace_blit_double);
    case 41: return PROC(ispace_41);
    default: return NULL;
    }
}
