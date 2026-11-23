/* Pixel operations: raster-op blits, fills, lines and shapes, on bitmaps
 * of palette indices (as on a 256-colour display) or monochrome 0/1. */
#include <math.h>
#include <stdlib.h>

#include "gdi.h"

/* The ternary raster operation (the high word's low byte of a ROP code)
 * applied bit by bit to pattern, source and destination pixel values. */
static uint8_t rop3(unsigned code, uint8_t p, uint8_t s, uint8_t d)
{
    uint8_t r = 0;
    int i;

    switch (code) {
    case 0x00: return 0;
    case 0xcc: return s;
    case 0xf0: return p;
    case 0x88: return s & d;
    case 0xee: return s | d;
    case 0x66: return s ^ d;
    case 0xff: return 0xff;
    default: break;
    }
    for (i = 0; i < 8; i++)
        if (code >> i & 1)
            r |= (uint8_t)((i & 4 ? p : ~p) & (i & 2 ? s : ~s) & (i & 1 ? d : ~d));
    return r;
}

static uint8_t brush_pixel(const Dc *d, const Brush *b, int x, int y)
{
    uint8_t v;

    if (!b || b->null)
        return 0;
    if (!b->has_pattern)
        return gdi_pixel_of(d, b->color);
    v = b->pattern[(y & 7) * 8 + (x & 7)];
    if (b->pattern_mono)
        return gdi_pixel_of(d, v ? d->bk : d->text);
    return v;
}

/* A source pixel converted to the destination's format. */
static uint8_t convert(const Dc *d, const Bmp *db, const Dc *s, const Bmp *sb, uint8_t v)
{
    if (sb->mono == db->mono)
        return v;
    if (sb->mono)
        return gdi_pixel_of(d, v ? d->bk : d->text);
    return v == gdi_pixel_of(s, s->bk);
}

void draw_blit(Dc *d, int x, int y, int w, int h, Dc *s, int sx, int sy, int sw, int sh, DWORD rop)
{
    Bmp *db = dc_bmp(d), *sb = s ? dc_bmp(s) : NULL;
    const Brush *br = handle_get(d->brush, H_BRUSH);
    unsigned code = rop >> 16 & 0xff;
    int aw = abs(w), ah = abs(h), asw = abs(sw), ash = abs(sh);
    int x0 = w < 0 ? x + w + 1 : x, y0 = h < 0 ? y + h + 1 : y;
    int sx0 = sw < 0 ? sx + sw + 1 : sx, sy0 = sh < 0 ? sy + sh + 1 : sy;
    int mx = (w < 0) != (sw < 0), my = (h < 0) != (sh < 0);
    int i, j;
    uint8_t mask;

    if (!db || !aw || !ah || (s && (!sb || !asw || !ash)))
        return;
    mask = db->mono ? 1 : 0xff;
    for (j = 0; j < ah; j++) {
        int ty = y0 + j, syy = 0;
        uint8_t *row;
        if (ty < d->clip.top || ty >= d->clip.bottom)
            continue;
        if (sb) {
            int k = (int)((long)j * ash / ah);
            syy = sy0 + (my ? ash - 1 - k : k);
        }
        row = db->px + (size_t)ty * db->w;
        for (i = 0; i < aw; i++) {
            int tx = x0 + i;
            uint8_t sv = 0, pv;
            if (tx < d->clip.left || tx >= d->clip.right)
                continue;
            if (sb) {
                int k = (int)((long)i * asw / aw);
                int sxx = sx0 + (mx ? asw - 1 - k : k);
                if (sxx >= 0 && sxx < sb->w && syy >= 0 && syy < sb->h)
                    sv = convert(d, db, s, sb, sb->px[(size_t)syy * sb->w + sxx]);
            }
            pv = brush_pixel(d, br, tx - d->ox, ty - d->oy);
            row[tx] = rop3(code, pv, sv, row[tx]) & mask;
        }
    }
}

void draw_fill(Dc *d, const RECT *r, HBRUSH brush, DWORD rop)
{
    HBRUSH old = d->brush;

    d->brush = brush;
    draw_blit(d, r->left - d->org.x + d->ox, r->top - d->org.y + d->oy,
              r->right - r->left, r->bottom - r->top, NULL, 0, 0, 0, 0, rop);
    d->brush = old;
}

#define DX(dc, px) ((px) - (dc)->org.x + (dc)->ox)
#define DY(dc, py) ((py) - (dc)->org.y + (dc)->oy)

BOOL BitBlt(HDC hd, int16_t x, int16_t y, int16_t w, int16_t h, HDC hs, int16_t sx, int16_t sy, DWORD rop)
{
    Dc *d = dc_get(hd), *s = dc_get(hs);
    unsigned code = rop >> 16 & 0xff;
    int uses_src = (code >> 2 & 0x33) != (code & 0x33);

    if (!d || (uses_src && !s))
        return 0;
    draw_blit(d, DX(d, x), DY(d, y), w, h, uses_src ? s : NULL,
              s ? DX(s, sx) : 0, s ? DY(s, sy) : 0, w, h, rop);
    return 1;
}

BOOL StretchBlt(HDC hd, int16_t x, int16_t y, int16_t w, int16_t h, HDC hs, int16_t sx, int16_t sy,
                int16_t sw, int16_t sh, DWORD rop)
{
    Dc *d = dc_get(hd), *s = dc_get(hs);

    if (!d || !s)
        return 0;
    draw_blit(d, DX(d, x), DY(d, y), w, h, s, DX(s, sx), DY(s, sy), sw, sh, rop);
    return 1;
}

BOOL PatBlt(HDC hd, int16_t x, int16_t y, int16_t w, int16_t h, DWORD rop)
{
    Dc *d = dc_get(hd);

    if (!d)
        return 0;
    draw_blit(d, DX(d, x), DY(d, y), w, h, NULL, 0, 0, 0, 0, rop);
    return 1;
}

int16_t FillRect(HDC hd, const RECT *r, HBRUSH brush)
{
    Dc *d = dc_get(hd);

    if (!d)
        return 0;
    draw_fill(d, r, brush, PATCOPY);
    return 1;
}

int16_t FrameRect(HDC hd, const RECT *r, HBRUSH brush)
{
    Dc *d = dc_get(hd);
    RECT e;

    if (!d)
        return 0;
    SetRect(&e, r->left, r->top, r->right, r->top + 1);
    draw_fill(d, &e, brush, PATCOPY);
    SetRect(&e, r->left, r->bottom - 1, r->right, r->bottom);
    draw_fill(d, &e, brush, PATCOPY);
    SetRect(&e, r->left, r->top, r->left + 1, r->bottom);
    draw_fill(d, &e, brush, PATCOPY);
    SetRect(&e, r->right - 1, r->top, r->right, r->bottom);
    draw_fill(d, &e, brush, PATCOPY);
    return 1;
}

void DrawFocusRect(HDC hd, const RECT *r)
{
    Dc *d = dc_get(hd);
    RECT e;

    if (!d)
        return;
    SetRect(&e, r->left, r->top, r->right, r->top + 1);
    draw_fill(d, &e, GetStockObject(BLACK_BRUSH), DSTINVERT);
    SetRect(&e, r->left, r->bottom - 1, r->right, r->bottom);
    draw_fill(d, &e, GetStockObject(BLACK_BRUSH), DSTINVERT);
    SetRect(&e, r->left, r->top + 1, r->left + 1, r->bottom - 1);
    draw_fill(d, &e, GetStockObject(BLACK_BRUSH), DSTINVERT);
    SetRect(&e, r->right - 1, r->top + 1, r->right, r->bottom - 1);
    draw_fill(d, &e, GetStockObject(BLACK_BRUSH), DSTINVERT);
}

static void put(Dc *d, int x, int y, uint8_t v)
{
    Bmp *b = dc_bmp(d);

    x = DX(d, x);
    y = DY(d, y);
    if (b && x >= d->clip.left && x < d->clip.right && y >= d->clip.top && y < d->clip.bottom)
        b->px[(size_t)y * b->w + x] = v;
}

COLORREF SetPixel(HDC hd, int16_t x, int16_t y, COLORREF c)
{
    Dc *d = dc_get(hd);

    if (d)
        put(d, x, y, gdi_pixel_of(d, c));
    return c;
}

COLORREF GetPixel(HDC hd, int16_t x, int16_t y)
{
    Dc *d = dc_get(hd);
    Bmp *b = d ? dc_bmp(d) : NULL;
    int px, py;

    if (!b)
        return (COLORREF)-1;
    px = DX(d, x);
    py = DY(d, y);
    if (px < 0 || py < 0 || px >= b->w || py >= b->h)
        return (COLORREF)-1;
    if (b->mono)
        return b->px[(size_t)py * b->w + px] ? RGB(255, 255, 255) : 0;
    return PALETTEINDEX(b->px[(size_t)py * b->w + px]);
}

/* Lines exclude their end point, as in GDI. */
static void line(Dc *d, int x0, int y0, int x1, int y1)
{
    const Pen *p = handle_get(d->pen, H_PEN);
    int dx = abs(x1 - x0), dy = -abs(y1 - y0);
    int stx = x0 < x1 ? 1 : -1, sty = y0 < y1 ? 1 : -1, err = dx + dy;
    uint8_t v;

    if (!p || p->null)
        return;
    v = gdi_pixel_of(d, p->color);
    while (x0 != x1 || y0 != y1) {
        int e2 = 2 * err;
        put(d, x0, y0, v);
        if (e2 >= dy) {
            err += dy;
            x0 += stx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sty;
        }
    }
}

DWORD MoveTo(HDC hd, int16_t x, int16_t y)
{
    Dc *d = dc_get(hd);
    DWORD old;

    if (!d)
        return 0;
    old = MAKELONG(d->pos.x, d->pos.y);
    d->pos.x = x;
    d->pos.y = y;
    return old;
}

DWORD GetCurrentPosition(HDC hd)
{
    Dc *d = dc_get(hd);

    return d ? MAKELONG(d->pos.x, d->pos.y) : 0;
}

BOOL LineTo(HDC hd, int16_t x, int16_t y)
{
    Dc *d = dc_get(hd);

    if (!d)
        return 0;
    line(d, d->pos.x, d->pos.y, x, y);
    d->pos.x = x;
    d->pos.y = y;
    return 1;
}

BOOL Rectangle(HDC hd, int16_t l, int16_t t, int16_t r, int16_t b)
{
    Dc *d = dc_get(hd);
    RECT in;

    if (!d)
        return 0;
    SetRect(&in, l + 1, t + 1, r - 1, b - 1);
    if (in.right > in.left && in.bottom > in.top)
        draw_fill(d, &in, d->brush, PATCOPY);
    line(d, l, t, r - 1, t);
    line(d, r - 1, t, r - 1, b - 1);
    line(d, r - 1, b - 1, l, b - 1);
    line(d, l, b - 1, l, t);
    return 1;
}

/* Fills the polygon (alternate rule) with the brush, then outlines it. */
BOOL Polygon(HDC hd, const POINT *pts, int16_t n)
{
    Dc *d = dc_get(hd);
    int i, j, y, ymin, ymax;

    if (!d || n < 2)
        return 0;
    ymin = ymax = pts[0].y;
    for (i = 1; i < n; i++) {
        if (pts[i].y < ymin)
            ymin = pts[i].y;
        if (pts[i].y > ymax)
            ymax = pts[i].y;
    }
    for (y = ymin; y < ymax; y++) {
        int xs[64], k = 0;
        for (i = 0, j = n - 1; i < n; j = i++) {
            int ya = pts[j].y, yb = pts[i].y;
            if ((ya <= y && yb > y) || (yb <= y && ya > y)) {
                if (k < 64)
                    xs[k++] = pts[j].x + (int)((long)(y - ya) * (pts[i].x - pts[j].x) / (yb - ya));
            }
        }
        for (i = 1; i < k; i++)
            for (j = i; j > 0 && xs[j - 1] > xs[j]; j--) {
                int t = xs[j];
                xs[j] = xs[j - 1];
                xs[j - 1] = t;
            }
        for (i = 0; i + 1 < k; i += 2) {
            RECT r;
            SetRect(&r, (int16_t)xs[i], (int16_t)y, (int16_t)xs[i + 1], (int16_t)(y + 1));
            draw_fill(d, &r, d->brush, PATCOPY);
        }
    }
    for (i = 0, j = n - 1; i < n; j = i++)
        line(d, pts[j].x, pts[j].y, pts[i].x, pts[i].y);
    return 1;
}

BOOL Ellipse(HDC hd, int16_t l, int16_t t, int16_t r, int16_t b)
{
    Dc *d = dc_get(hd);
    const Pen *p;
    long b2;
    int y, cx2 = l + r - 1, cy2 = t + b - 1;

    if (!d || r - l < 1 || b - t < 1)
        return 0;
    p = handle_get(d->pen, H_PEN);
    b2 = (long)(b - t) * (b - t);
    for (y = t; y < b; y++) {
        long dy = 2 * y - cy2;
        double half = (r - l) / 2.0 * sqrt(1.0 - (double)dy * dy / (double)b2);
        int x0 = (int)(cx2 / 2.0 - half + 0.5), x1 = (int)(cx2 / 2.0 + half + 0.5);
        RECT row;
        SetRect(&row, (int16_t)x0, (int16_t)y, (int16_t)(x1 + 1), (int16_t)(y + 1));
        draw_fill(d, &row, d->brush, PATCOPY);
        if (p && !p->null) {
            put(d, x0, y, gdi_pixel_of(d, p->color));
            put(d, x1, y, gdi_pixel_of(d, p->color));
        }
    }
    return 1;
}

BOOL ScrollDC(HDC hd, int16_t dx, int16_t dy, const RECT *scroll, const RECT *clip, HRGN upd, RECT *out)
{
    Dc *d = dc_get(hd);
    HDC tmp;
    Dc *t;
    HBITMAP bm, old;
    int w, h;

    (void)clip;
    (void)upd;
    if (!d || !scroll)
        return 0;
    w = scroll->right - scroll->left;
    h = scroll->bottom - scroll->top;
    tmp = CreateCompatibleDC(hd);
    bm = gdi_new_bitmap(w, h, dc_bmp(d)->mono);
    old = SelectObject(tmp, bm);
    t = dc_get(tmp);
    draw_blit(t, 0, 0, w, h, d, DX(d, scroll->left), DY(d, scroll->top), w, h, SRCCOPY);
    draw_blit(d, DX(d, scroll->left + dx), DY(d, scroll->top + dy), w, h, t, 0, 0, w, h, SRCCOPY);
    SelectObject(tmp, old);
    DeleteObject(bm);
    DeleteDC(tmp);
    if (out)
        SetRect(out, 0, 0, 0, 0);
    return 1;
}
