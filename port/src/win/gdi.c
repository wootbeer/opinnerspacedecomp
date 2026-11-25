/* GDI objects: device contexts, bitmaps, palettes, brushes, pens, fonts
 * and regions, on a 256-colour screen (the framebuffer). */
#include <stdlib.h>
#include <string.h>

#include "gdi.h"
#include "user.h"
#include "video.h"

/* The 20 static colours of the Windows 3.1 system palette. */
static const struct {
    uint8_t index, r, g, b;
} statics[20] = {
    {0, 0, 0, 0}, {1, 128, 0, 0}, {2, 0, 128, 0}, {3, 128, 128, 0}, {4, 0, 0, 128},
    {5, 128, 0, 128}, {6, 0, 128, 128}, {7, 192, 192, 192}, {8, 192, 220, 192},
    {9, 166, 202, 240}, {246, 255, 251, 240}, {247, 160, 160, 164}, {248, 128, 128, 128},
    {249, 255, 0, 0}, {250, 0, 255, 0}, {251, 255, 255, 0}, {252, 0, 0, 255},
    {253, 255, 0, 255}, {254, 0, 255, 255}, {255, 255, 255, 255}
};

static HBITMAP screen_bmp, default_bmp;
static HPALETTE default_pal;
static HPALETTE realized_pal;       /* the palette the screen shows */
static HGDIOBJ stock[18];

Dc *dc_get(HDC h)
{
    return handle_get(h, H_DC);
}

Bmp *dc_bmp(const Dc *d)
{
    return handle_get(d->bmp, H_BITMAP);
}

Bmp *dc_target(const Dc *d)
{
    if (d->bmp == screen_bmp)
        video_framebuffer()->drawn = 1;
    return dc_bmp(d);
}

HBITMAP gdi_new_bitmap(int w, int h, int mono)
{
    Bmp *b = calloc(1, sizeof *b);
    HBITMAP hb;

    if (w < 1)
        w = 1;
    if (h < 1)
        h = 1;
    if (!b || !(b->px = calloc((size_t)w * h, 1))) {
        free(b);
        return 0;
    }
    b->w = w;
    b->h = h;
    b->mono = mono;
    b->owned = 1;
    hb = handle_new(H_BITMAP, b);
    if (!hb) {
        free(b->px);
        free(b);
    }
    return hb;
}

HPALETTE gdi_new_palette(const PALETTEENTRY *e, int n)
{
    Pal *p = calloc(1, sizeof *p);

    if (!p)
        return 0;
    p->n = n > 256 ? 256 : n;
    memcpy(p->e, e, (size_t)p->n * sizeof *e);
    return handle_new(H_PALETTE, p);
}

static HGDIOBJ new_brush(COLORREF c, int null)
{
    Brush *b = calloc(1, sizeof *b);

    if (!b)
        return 0;
    b->color = c;
    b->null = null;
    return handle_new(H_BRUSH, b);
}

/* DKGRAY_BRUSH: RGB(64, 64, 64) is not a static colour, so the 8-bit
 * display dithers it from black and dark gray (entry 248), half each, in
 * a checkerboard [uncertain: which of the two is at the origin]. */
static HGDIOBJ new_dark_gray(void)
{
    HGDIOBJ h = new_brush(RGB(64, 64, 64), 0);
    Brush *b = handle_get(h, H_BRUSH);
    int i;

    if (!b)
        return h;
    b->has_pattern = 1;
    for (i = 0; i < 64; i++)
        b->pattern[i] = (uint8_t)((i / 8 + i % 8) & 1 ? 0 : 248);
    return h;
}

static HGDIOBJ new_pen(COLORREF c, int width, int null)
{
    Pen *p = calloc(1, sizeof *p);

    if (!p)
        return 0;
    p->color = c;
    p->width = width;
    p->null = null;
    return handle_new(H_PEN, p);
}

void gdi_init(void)
{
    Framebuffer *fb = video_framebuffer();
    PALETTEENTRY e[20];
    Bmp *s;
    int i;

    for (i = 0; i < 20; i++) {
        Rgb *c = &fb->palette[statics[i].index];
        c->r = statics[i].r;
        c->g = statics[i].g;
        c->b = statics[i].b;
        e[i].peRed = statics[i].r;
        e[i].peGreen = statics[i].g;
        e[i].peBlue = statics[i].b;
        e[i].peFlags = 0;
    }
    s = calloc(1, sizeof *s);
    s->w = fb->width;
    s->h = fb->height;
    s->px = fb->pixels;
    screen_bmp = handle_new(H_BITMAP, s);
    default_bmp = gdi_new_bitmap(1, 1, 1);
    default_pal = gdi_new_palette(e, 20);
    stock[WHITE_BRUSH] = new_brush(RGB(255, 255, 255), 0);
    stock[LTGRAY_BRUSH] = new_brush(RGB(192, 192, 192), 0);
    stock[GRAY_BRUSH] = new_brush(RGB(128, 128, 128), 0);
    stock[DKGRAY_BRUSH] = new_dark_gray();
    stock[BLACK_BRUSH] = new_brush(RGB(0, 0, 0), 0);
    stock[NULL_BRUSH] = new_brush(0, 1);
    stock[WHITE_PEN] = new_pen(RGB(255, 255, 255), 1, 0);
    stock[BLACK_PEN] = new_pen(RGB(0, 0, 0), 1, 0);
    stock[8] = new_pen(0, 1, 1);
    stock[13] = handle_new(H_FONT, calloc(1, sizeof(Font)));
    stock[15] = default_pal;
}

static int is_stock(HGDIOBJ h)
{
    int i;

    for (i = 0; i < 18; i++)
        if (stock[i] == h)
            return 1;
    return h == screen_bmp || h == default_bmp;
}

HGDIOBJ GetStockObject(int16_t i)
{
    return i >= 0 && i < 18 ? stock[i] : 0;
}

/* Colours. */
static int nearest(const PALETTEENTRY *e, int n, COLORREF c)
{
    int i, best = 0;
    long dmin = 0x7fffffff;

    for (i = 0; i < n; i++) {
        long dr = e[i].peRed - (long)GetRValue(c);
        long dg = e[i].peGreen - (long)GetGValue(c);
        long db = e[i].peBlue - (long)GetBValue(c);
        long d = dr * dr + dg * dg + db * db;
        if (d < dmin) {
            dmin = d;
            best = i;
        }
    }
    return best;
}

static uint8_t color_index(const Dc *d, COLORREF c)
{
    Pal *p = d ? handle_get(d->pal, H_PALETTE) : NULL;
    PALETTEENTRY e[20];
    int i;

    if (c >> 24 == 1)
        return (uint8_t)c;
    if (c >> 24 == 2 && p && d->pal != default_pal)
        return (uint8_t)nearest(p->e, p->n, c);
    for (i = 0; i < 20; i++) {
        e[i].peRed = statics[i].r;
        e[i].peGreen = statics[i].g;
        e[i].peBlue = statics[i].b;
    }
    return statics[nearest(e, 20, c)].index;
}

uint8_t gdi_color_index(HDC h, COLORREF c)
{
    return color_index(dc_get(h), c);
}

/* Monochrome pixels are 1 for colours nearer white. */
uint8_t gdi_pixel_of(const Dc *d, COLORREF c)
{
    Bmp *b = dc_bmp(d);
    Framebuffer *fb = video_framebuffer();

    if (!b || !b->mono)
        return color_index(d, c);
    if (c >> 24 == 1) {
        Rgb *e = &fb->palette[c & 0xff];
        return e->r + e->g + e->b >= 384;
    }
    return GetRValue(c) + GetGValue(c) + GetBValue(c) >= 384;
}

/* Device contexts. */
static HDC new_dc(HWND hwnd, HBITMAP bmp)
{
    Dc *d = calloc(1, sizeof *d);
    Bmp *b = handle_get(bmp, H_BITMAP);
    HDC h;

    if (!d)
        return 0;
    d->hwnd = hwnd;
    d->bmp = bmp;
    d->pal = default_pal;
    d->brush = stock[WHITE_BRUSH];
    d->pen = stock[BLACK_PEN];
    d->font = stock[13];
    d->text = RGB(0, 0, 0);
    d->bk = RGB(255, 255, 255);
    d->bkmode = OPAQUE;
    d->stretch_mode = 1;
    SetRect(&d->clip, 0, 0, (int16_t)b->w, (int16_t)b->h);
    h = handle_new(H_DC, d);
    if (!h)
        free(d);
    return h;
}

/* The clip a window DC starts with: its client area (whole window for
 * GetWindowDC) inside its parents' client areas and the screen. */
static void window_clip(Dc *d)
{
    Bmp *s = handle_get(screen_bmp, H_BITMAP);
    Wnd *w = wnd_get(d->hwnd);
    RECT all;

    SetRect(&all, 0, 0, (int16_t)s->w, (int16_t)s->h);
    d->ox = d->oy = 0;
    d->clip = all;
    if (!w)
        return;
    d->ox = d->nonclient ? w->rect.left : w->client.left;
    d->oy = d->nonclient ? w->rect.top : w->client.top;
    IntersectRect(&d->clip, &all, d->nonclient ? &w->rect : &w->client);
    while (wnd_is_child(w) && (w = wnd_get(w->parent)) != NULL)
        IntersectRect(&d->clip, &d->clip, &w->client);
}

int gdi_drawable(Dc *d, int x, int y)
{
    POINT p;
    int i;

    if (x < d->clip.left || x >= d->clip.right || y < d->clip.top || y >= d->clip.bottom)
        return 0;
    if (!d->hwnd)
        return 1;
    if (d->zgen != wnd_zgen()) {
        d->zgen = wnd_zgen();
        d->nexcl = wnd_occluders(wnd_get(d->hwnd), d->excl, (int)(sizeof d->excl / sizeof d->excl[0]));
    }
    p.x = (int16_t)x;
    p.y = (int16_t)y;
    for (i = 0; i < d->nexcl; i++)
        if (PtInRect(&d->excl[i], p))
            return 0;
    return 1;
}

static HDC window_dc(HWND hwnd, int nonclient)
{
    HDC h = new_dc(hwnd, screen_bmp);

    if (h) {
        dc_get(h)->nonclient = nonclient;
        dc_get(h)->zgen = wnd_zgen() - 1;
        window_clip(dc_get(h));
    }
    return h;
}

HDC GetDC(HWND hwnd)
{
    return window_dc(hwnd, 0);
}

HDC GetWindowDC(HWND hwnd)
{
    return window_dc(hwnd, 1);
}

int16_t ReleaseDC(HWND hwnd, HDC h)
{
    (void)hwnd;
    return DeleteDC(h);
}

HDC CreateDC(LPCSTR driver, LPCSTR device, LPCSTR port, const void *init)
{
    (void)driver;
    (void)device;
    (void)port;
    (void)init;
    return GetDC(0);
}

HDC CreateCompatibleDC(HDC h)
{
    (void)h;
    return new_dc(0, default_bmp);
}

BOOL DeleteDC(HDC h)
{
    Dc *d = dc_get(h);

    if (!d)
        return 0;
    free(d);
    handle_free(h);
    return 1;
}

int16_t GetDeviceCaps(HDC h, int16_t i)
{
    (void)h;
    switch (i) {
    case HORZRES:
        return 640;
    case VERTRES:
        return 480;
    case BITSPIXEL:
        return 8;
    case PLANES:
        return 1;
    case 24:                /* NUMCOLORS */
        return 20;
    case 38:                /* RASTERCAPS: RC_PALETTE | RC_BITBLT | RC_STRETCHBLT ... */
        return 0x0799;
    case SIZEPALETTE:
        return 256;
    case NUMRESERVED:
        return 20;
    default:
        return 0;
    }
}

HGDIOBJ SelectObject(HDC h, HGDIOBJ obj)
{
    Dc *d = dc_get(h);
    HGDIOBJ old = 0;
    Bmp *b;

    if (!d)
        return 0;
    switch (handle_type(obj)) {
    case H_BITMAP:
        if (d->hwnd || obj == screen_bmp)
            return 0;
        old = d->bmp;
        d->bmp = obj;
        b = dc_bmp(d);
        SetRect(&d->clip, 0, 0, (int16_t)b->w, (int16_t)b->h);
        break;
    case H_BRUSH:
        old = d->brush;
        d->brush = obj;
        break;
    case H_PEN:
        old = d->pen;
        d->pen = obj;
        break;
    case H_FONT:
        old = d->font;
        d->font = obj;
        break;
    case H_RGN:
        SelectClipRgn(h, obj);
        return 2;           /* SIMPLEREGION */
    default:
        break;
    }
    return old;
}

BOOL DeleteObject(HGDIOBJ obj)
{
    int type = handle_type(obj);
    void *p;

    if (is_stock(obj) || type == H_FREE || type == H_DC || type == H_WND)
        return 0;
    p = handle_get(obj, type);
    if (type == H_BITMAP && ((Bmp *)p)->owned)
        free(((Bmp *)p)->px);
    if (obj == realized_pal)
        realized_pal = 0;
    free(p);
    handle_free(obj);
    return 1;
}

int16_t GetObject(HGDIOBJ obj, int16_t size, void *out)
{
    Bmp *b = handle_get(obj, H_BITMAP);
    Pal *p = handle_get(obj, H_PALETTE);

    if (b && size >= (int16_t)sizeof(BITMAP)) {
        BITMAP *bm = out;
        memset(bm, 0, sizeof *bm);
        bm->bmWidth = (int16_t)b->w;
        bm->bmHeight = (int16_t)b->h;
        bm->bmWidthBytes = (int16_t)(b->mono ? (b->w + 15) / 16 * 2 : (b->w + 1) / 2 * 2);
        bm->bmPlanes = 1;
        bm->bmBitsPixel = b->mono ? 1 : 8;
        return (int16_t)sizeof(BITMAP);
    }
    if (p && size >= 2) {
        *(WORD *)out = (WORD)p->n;
        return 2;
    }
    return 0;
}

/* Bitmaps. */
HBITMAP CreateBitmap(int16_t w, int16_t h, UINT planes, UINT bpp, const void *bits)
{
    int mono = planes * bpp == 1;
    HBITMAP hb = gdi_new_bitmap(w, h, mono);
    Bmp *b = handle_get(hb, H_BITMAP);
    const uint8_t *src = bits;
    int x, y, stride;

    if (!b || !src)
        return hb;
    stride = mono ? (b->w + 15) / 16 * 2 : (b->w + 1) / 2 * 2;
    for (y = 0; y < b->h; y++)
        for (x = 0; x < b->w; x++)
            b->px[y * b->w + x] = mono ? src[y * stride + x / 8] >> (7 - x % 8) & 1
                                       : src[y * stride + x];
    return hb;
}

HBITMAP CreateCompatibleBitmap(HDC h, int16_t w, int16_t hgt)
{
    Dc *d = dc_get(h);
    Bmp *b = d ? dc_bmp(d) : NULL;

    if (w <= 0 || hgt <= 0)
        return gdi_new_bitmap(1, 1, 1);
    return gdi_new_bitmap(w, hgt, b ? b->mono : 0);
}

/* Pixels of a DIB (bpp 1, 4 or 8, rows bottom-up, stride bytes apart)
 * as a device bitmap, each value mapped through map. */
static HBITMAP dib_pixels(int w, int h, int bpp, int mono, const uint8_t *bits, const uint8_t map[256])
{
    int x, y, stride = (w * bpp + 31) / 32 * 4;
    HBITMAP hb = gdi_new_bitmap(w, h, mono);
    Bmp *b = handle_get(hb, H_BITMAP);

    if (!b)
        return 0;
    for (y = 0; y < h; y++) {
        const uint8_t *row = bits + (size_t)(h - 1 - y) * stride;
        for (x = 0; x < w; x++)
            b->px[y * w + x] = map[bpp == 8 ? row[x] : row[x * bpp / 8] >> (8 - bpp - x * bpp % 8) & ((1 << bpp) - 1)];
    }
    return hb;
}

/* A packed DIB (BITMAPINFOHEADER or BITMAPCOREHEADER, colours, bits) as a
 * device bitmap, the way LoadBitmap makes one: monochrome stays
 * monochrome, colours map to the static system colours. */
HBITMAP gdi_bitmap_from_dib(const uint8_t *dib, uint32_t size)
{
    uint32_t hsize = dib[0] | dib[1] << 8 | (uint32_t)dib[2] << 16;
    int core = hsize == 12;
    int w = core ? dib[4] | dib[5] << 8 : (int)(dib[4] | dib[5] << 8 | dib[6] << 16);
    int h = core ? dib[6] | dib[7] << 8 : (int)(dib[8] | dib[9] << 8 | dib[10] << 16);
    int bpp = core ? dib[10] : dib[14];
    int ncol = core ? 0 : dib[32] | dib[33] << 8;
    int qsize = core ? 3 : 4;
    int x;
    const uint8_t *pal = dib + hsize, *bits;
    uint8_t map[256] = {0};

    if (bpp != 1 && bpp != 4 && bpp != 8)
        return 0;
    if (!ncol || ncol > 1 << bpp)
        ncol = 1 << bpp;
    bits = pal + ncol * qsize;
    if ((uint32_t)(bits - dib) + (uint32_t)((w * bpp + 31) / 32 * 4) * h > size)
        return 0;
    for (x = 0; x < ncol; x++) {
        COLORREF c = RGB(pal[x * qsize + 2], pal[x * qsize + 1], pal[x * qsize]);
        map[x] = bpp == 1 ? (uint8_t)(GetRValue(c) + GetGValue(c) + GetBValue(c) >= 384)
                          : gdi_color_index(0, c);
    }
    for (; x < 256; x++)
        map[x] = map[0];
    return dib_pixels(w, h, bpp, bpp == 1, bits, map);
}

/* CreateDIBitmap for a BITMAPINFOHEADER DIB of 1, 4 or 8 bits per pixel,
 * always initialised (CBM_INIT): a colour bitmap whose pixels are the
 * colour table's palette indices (DIB_PAL_COLORS) or the colours'
 * nearest entries in dc's palette (DIB_RGB_COLORS). */
HBITMAP CreateDIBitmap(HDC dc, const BITMAPINFOHEADER *bih, DWORD init, const void *bits,
                       const void *bmi, UINT usage)
{
    const uint8_t *table = (const uint8_t *)bmi + bih->biSize;
    int bpp = bih->biBitCount, ncol = bih->biClrUsed ? (int)bih->biClrUsed : 1 << bpp;
    uint8_t map[256] = {0};
    int i;

    (void)init;
    if (bpp != 1 && bpp != 4 && bpp != 8)
        return 0;
    if (ncol > 1 << bpp)
        ncol = 1 << bpp;
    for (i = 0; i < ncol; i++)
        map[i] = usage == DIB_PAL_COLORS ? table[2 * i]
                                         : gdi_color_index(dc, PALETTERGB(table[4 * i + 2], table[4 * i + 1], table[4 * i]));
    return dib_pixels((int)bih->biWidth, (int)bih->biHeight, bpp, 0, bits, map);
}

/* Palettes. */
HPALETTE SelectPalette(HDC h, HPALETTE pal, BOOL bg)
{
    Dc *d = dc_get(h);
    HPALETTE old;

    (void)bg;
    if (!d || !handle_get(pal, H_PALETTE))
        return 0;
    old = d->pal;
    d->pal = pal;
    return old;
}

UINT RealizePalette(HDC h)
{
    Dc *d = dc_get(h);
    Pal *p = d ? handle_get(d->pal, H_PALETTE) : NULL;
    Framebuffer *fb = video_framebuffer();
    int i;

    if (!p || d->pal == default_pal)
        return 0;
    realized_pal = d->pal;
    for (i = 0; i < p->n; i++) {
        fb->palette[i].r = p->e[i].peRed;
        fb->palette[i].g = p->e[i].peGreen;
        fb->palette[i].b = p->e[i].peBlue;
    }
    fb->drawn = 1;
    return (UINT)p->n;
}

HPALETTE CreatePalette(const LOGPALETTE *lp)
{
    return gdi_new_palette(lp->palPalEntry, lp->palNumEntries);
}

/* Entries of pal from start on take the new colours where pal has them
 * PC_RESERVED; on the screen at once when pal is the realized palette
 * (identity mapping: logical index = screen index). */
void AnimatePalette(HPALETTE pal, UINT start, UINT n, const PALETTEENTRY *e)
{
    Pal *p = handle_get(pal, H_PALETTE);
    Framebuffer *fb = video_framebuffer();
    UINT i;

    if (!p)
        return;
    for (i = 0; i < n && start + i < (UINT)p->n; i++) {
        PALETTEENTRY *d = &p->e[start + i];
        if (!(d->peFlags & PC_RESERVED))
            continue;
        d->peRed = e[i].peRed;
        d->peGreen = e[i].peGreen;
        d->peBlue = e[i].peBlue;
        if (pal == realized_pal) {
            fb->palette[start + i].r = d->peRed;
            fb->palette[start + i].g = d->peGreen;
            fb->palette[start + i].b = d->peBlue;
            fb->drawn = 1;
        }
    }
}

UINT GetSystemPaletteEntries(HDC h, UINT start, UINT n, PALETTEENTRY *e)
{
    Framebuffer *fb = video_framebuffer();
    UINT i;

    (void)h;
    for (i = 0; i < n && start + i < 256; i++) {
        e[i].peRed = fb->palette[start + i].r;
        e[i].peGreen = fb->palette[start + i].g;
        e[i].peBlue = fb->palette[start + i].b;
        e[i].peFlags = 0;
    }
    return i;
}

int16_t UpdateColors(HDC h)
{
    (void)h;
    return 1;
}

/* Brushes, pens, fonts, regions. */
HBRUSH CreateSolidBrush(COLORREF c)
{
    return new_brush(c, 0);
}

HBRUSH CreatePatternBrush(HBITMAP hb)
{
    Bmp *b = handle_get(hb, H_BITMAP);
    HBRUSH h = new_brush(0, 0);
    Brush *br = handle_get(h, H_BRUSH);
    int x, y;

    if (!br || !b)
        return h;
    br->has_pattern = 1;
    br->pattern_mono = b->mono;
    for (y = 0; y < 8; y++)
        for (x = 0; x < 8; x++)
            br->pattern[y * 8 + x] = b->px[(y % b->h) * b->w + x % b->w];
    return h;
}

HPEN CreatePen(int16_t style, int16_t width, COLORREF c)
{
    return new_pen(c, width, style == 5);
}

HFONT CreateFont(int16_t height, int16_t width, int16_t esc, int16_t orient, int16_t weight,
                 BYTE italic, BYTE underline, BYTE strike, BYTE charset, BYTE out_prec,
                 BYTE clip_prec, BYTE quality, BYTE pitch, LPCSTR face)
{
    Font *f = calloc(1, sizeof *f);

    (void)esc;
    (void)orient;
    (void)underline;
    (void)strike;
    (void)charset;
    (void)out_prec;
    (void)clip_prec;
    (void)quality;
    (void)pitch;
    if (!f)
        return 0;
    f->height = height;
    f->width = width;
    f->weight = weight;
    f->italic = italic != 0;
    strncpy(f->face, face ? face : "", sizeof f->face - 1);
    return handle_new(H_FONT, f);
}

HRGN CreateRectRgn(int16_t l, int16_t t, int16_t r, int16_t b)
{
    Rgn *g = calloc(1, sizeof *g);

    if (!g)
        return 0;
    SetRect(&g->r, l, t, r, b);
    return handle_new(H_RGN, g);
}

int16_t SelectClipRgn(HDC h, HRGN rgn)
{
    Dc *d = dc_get(h);
    Rgn *g = handle_get(rgn, H_RGN);
    Bmp *b;
    RECT r, all;

    if (!d)
        return 0;
    b = dc_bmp(d);
    SetRect(&all, 0, 0, (int16_t)b->w, (int16_t)b->h);
    if (d->hwnd || d->bmp == screen_bmp)
        window_clip(d);
    else
        d->clip = all;
    if (g) {
        r = g->r;
        r.left = (int16_t)(r.left + d->ox);
        r.right = (int16_t)(r.right + d->ox);
        r.top = (int16_t)(r.top + d->oy);
        r.bottom = (int16_t)(r.bottom + d->oy);
        IntersectRect(&d->clip, &d->clip, &r);
    }
    return 2;
}

/* DC attributes. */
COLORREF SetBkColor(HDC h, COLORREF c)
{
    Dc *d = dc_get(h);
    COLORREF old = d ? d->bk : 0;

    if (d)
        d->bk = c;
    return old;
}

COLORREF SetTextColor(HDC h, COLORREF c)
{
    Dc *d = dc_get(h);
    COLORREF old = d ? d->text : 0;

    if (d)
        d->text = c;
    return old;
}

COLORREF GetTextColor(HDC h)
{
    Dc *d = dc_get(h);

    return d ? d->text : 0;
}

int16_t SetBkMode(HDC h, int16_t mode)
{
    Dc *d = dc_get(h);
    int16_t old = d ? (int16_t)d->bkmode : 0;

    if (d)
        d->bkmode = mode;
    return old;
}

UINT SetTextAlign(HDC h, UINT align)
{
    Dc *d = dc_get(h);
    UINT old = d ? d->align : 0;

    if (d)
        d->align = align;
    return old;
}

int16_t SetStretchBltMode(HDC h, int16_t mode)
{
    Dc *d = dc_get(h);
    int16_t old = d ? (int16_t)d->stretch_mode : 0;

    if (d)
        d->stretch_mode = mode;
    return old;
}

DWORD SetWindowOrg(HDC h, int16_t x, int16_t y)
{
    Dc *d = dc_get(h);
    DWORD old;

    if (!d)
        return 0;
    old = MAKELONG(d->org.x, d->org.y);
    d->org.x = x;
    d->org.y = y;
    return old;
}

DWORD GetWindowOrg(HDC h)
{
    Dc *d = dc_get(h);

    return d ? MAKELONG(d->org.x, d->org.y) : 0;
}

/* Windows 3.1's default colour scheme. */
COLORREF GetSysColor(int16_t i)
{
    static const COLORREF colors[21] = {
        RGB(192, 192, 192), RGB(0, 128, 128), RGB(0, 0, 128), RGB(255, 255, 255),
        RGB(255, 255, 255), RGB(255, 255, 255), RGB(0, 0, 0), RGB(0, 0, 0),
        RGB(0, 0, 0), RGB(255, 255, 255), RGB(192, 192, 192), RGB(192, 192, 192),
        RGB(255, 255, 255), RGB(0, 0, 128), RGB(255, 255, 255), RGB(192, 192, 192),
        RGB(128, 128, 128), RGB(128, 128, 128), RGB(0, 0, 0), RGB(0, 0, 0),
        RGB(255, 255, 255),
    };

    return i >= 0 && i < 21 ? colors[i] : RGB(0, 0, 0);
}
