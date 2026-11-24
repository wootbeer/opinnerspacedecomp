/* ISPACE.DLL ordinals 33-35 (8:037a, 8:05ac, 8:0768): text in the
 * ALPHABET bitmap font, a raised or sunken box and a gauge, used by the
 * game's panels and screens and by the rooms (ispace_shape.c). */
#include <string.h>

#include "ispace.h"

#define GLYPH_W 0x12            /* a letter in the ALPHABET bitmap */
#define GLYPH_H 0x14
#define BLANK -2
#define NONE -1

/* The ALPHABET bitmap's column of character c: letters (either case),
 * digits from 35, a few signs; BLANK for space and '_', NONE for
 * characters it does not have. */
static int16_t glyph(int c)
{
    static const char signs[] = "/():!?,.-";
    static const int16_t sign_glyph[] = {0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22};
    const char *p;

    if (c >= '0' && c <= '9')
        return (int16_t)(c - 13);
    if (c >= 'a' && c <= 'z')
        return (int16_t)(c - 'a');
    if (c >= 'A' && c <= 'Z')
        return (int16_t)(c - 'A');
    if (c == ' ' || c == '_')
        return BLANK;
    if (c == '%')
        return 0x2d;
    if (c == '\\')
        return 0x1a;
    p = c > 0 ? strchr(signs, c) : NULL;
    return p ? sign_glyph[p - signs] : NONE;
}

/* Ordinal 33: text at (x, y) in letters size wide (low word) and high
 * (high word), left (align 0), right (2) or centred (6) on x, each
 * letter the ALPHABET glyph ANDed with colour.  Spaces are black. */
void ispace_letters(int16_t dc, int16_t pal, int32_t size, int16_t align, int32_t color, int16_t x,
                    int16_t y, char *text)
{
    int16_t w = (int16_t)size, h = (int16_t)(size >> 16), n = (int16_t)strlen(text), i, g;
    HBRUSH old_brush = SelectObject(dc, CreateSolidBrush((COLORREF)color));
    HDC mdc = CreateCompatibleDC(dc);
    HBITMAP old_bm = SelectObject(mdc, ispace_alphabet());
    HPALETTE old_pal = pal ? SelectPalette(mdc, pal, 0) : 0;

    if (align == 6)
        x = (int16_t)(x - (int16_t)(n * w) / 2);
    else if (align == 2)
        x = (int16_t)(x - (int16_t)(n * w));
    SetStretchBltMode(dc, COLORONCOLOR);
    for (i = 0; i < n; i++) {
        g = glyph((signed char)text[i]);
        if (g == NONE)
            continue;
        if (g == BLANK)
            PatBlt(dc, x, y, w, h, BLACKNESS);
        else
            StretchBlt(dc, x, y, w, h, mdc, (int16_t)(g * GLYPH_W), 0, GLYPH_W, GLYPH_H, MERGECOPY);
        x = (int16_t)(x + w);
    }
    DeleteObject(SelectObject(dc, old_brush));
    SelectObject(mdc, old_bm);
    if (old_pal)
        SelectPalette(mdc, old_pal, 0);
    DeleteDC(mdc);
}

static void pen_lines(HDC dc, uint8_t grey, const POINT *p, int n)
{
    HPEN old = SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(grey, grey, grey)));
    int i;

    MoveTo(dc, (int16_t)p[0].x, (int16_t)p[0].y);
    for (i = 1; i < n; i++)
        LineTo(dc, (int16_t)p[i].x, (int16_t)p[i].y);
    DeleteObject(SelectObject(dc, old));
}

/* Ordinal 34: a box filled black (kind 0) or light grey (1-3) with a
 * shadow on its right and bottom edges and a light on its left and top
 * ones: kind 0 a grey shadow, 1 and 2 raised (white light, black
 * shadow; 2 with a grey bottom edge), 3 sunken.  The DLL leaves other
 * kinds' brush and colours unset; they draw nothing here. */
void ispace_bevel(int16_t dc, int16_t x, int16_t y, int16_t w, int16_t h, int16_t kind)
{
    static const struct {
        int brush;
        int light;              /* -1: none */
        uint8_t shadow;
    } look[4] = {{BLACK_BRUSH, -1, 0xc0}, {LTGRAY_BRUSH, 0xff, 0}, {LTGRAY_BRUSH, 0xff, 0}, {LTGRAY_BRUSH, 0x80, 0xff}};
    int16_t r = (int16_t)(x + w), b = (int16_t)(y + h);
    POINT shadow[3] = {{r, y}, {r, b}, {x, b}}, light[3] = {{r, y}, {x, y}, {x, b}}, bottom[2] = {{x, b}, {r, b}};
    HGDIOBJ old;

    if (kind < 0 || kind > 3)
        return;
    old = SelectObject(dc, GetStockObject(look[kind].brush));
    PatBlt(dc, x, y, w, h, PATCOPY);
    SelectObject(dc, old);
    pen_lines(dc, look[kind].shadow, shadow, 3);
    if (look[kind].light >= 0)
        pen_lines(dc, (uint8_t)look[kind].light, light, 3);
    if (kind == 2)
        pen_lines(dc, 0x80, bottom, 2);
}

static void fill(HDC dc, COLORREF c, const RECT *r, int n)
{
    HBRUSH old = SelectObject(dc, CreateSolidBrush(c));
    int i;

    for (i = 0; i < n; i++)
        PatBlt(dc, (int16_t)r[i].left, (int16_t)r[i].top, (int16_t)r[i].right, (int16_t)r[i].bottom, PATCOPY);
    DeleteObject(SelectObject(dc, old));
}

/* Ordinal 35: a gauge percent full: a sunken frame (white below and
 * right, dark grey above and left), black for the empty part, and the
 * full part green with yellow top and left edges and dark green bottom
 * and right ones.  The rectangles below are x, y, width, height. */
void ispace_gauge(int16_t dc, int16_t x, int16_t y, int16_t w, int16_t h, int16_t percent)
{
    int16_t f = (int16_t)(((int32_t)percent * w) / 100);
    const COLORREF yellow = RGB(255, 255, 0);
    RECT frame;
    HGDIOBJ old;

    SetRect(&frame, (int16_t)(x - 1), (int16_t)(y - 1), (int16_t)(x + w + 1), (int16_t)(y + h + 1));
    PatBlt(dc, (int16_t)(frame.left - 1), (int16_t)frame.bottom, (int16_t)(frame.right - frame.left + 2), 1, WHITENESS);
    PatBlt(dc, (int16_t)frame.right, (int16_t)(frame.top - 1), 1, (int16_t)(frame.bottom - frame.top + 1), WHITENESS);
    old = SelectObject(dc, GetStockObject(DKGRAY_BRUSH));
    PatBlt(dc, (int16_t)(frame.left - 1), (int16_t)(frame.top - 1), 1, (int16_t)(frame.bottom - frame.top + 1), PATCOPY);
    PatBlt(dc, (int16_t)frame.left, (int16_t)(frame.top - 1), (int16_t)(frame.right - frame.left), 1, PATCOPY);
    SelectObject(dc, old);
    PatBlt(dc, (int16_t)(x + f), y, (int16_t)(w - f), h, BLACKNESS);
    if (!f)
        return;
    {
        const RECT inner[1] = {{x + 3, y + 3, f - 6, h - 6}};
        const RECT lit[2] = {{x, y, f, 3}, {x, y, 3, h}};
        const RECT dark[2] = {{x, y + h - 3, f, 3}, {x + f - 3, y, 3, h}};
        fill(dc, RGB(0, 255, 0), inner, 1);
        fill(dc, yellow, lit, 2);
        fill(dc, RGB(0, 128, 0), dark, 2);
    }
    SetPixel(dc, x, (int16_t)(y + h - 3), yellow);
    SetPixel(dc, x, (int16_t)(y + h - 2), yellow);
    SetPixel(dc, (int16_t)(x + 1), (int16_t)(y + h - 3), yellow);
    SetPixel(dc, (int16_t)(x + f - 3), y, yellow);
    SetPixel(dc, (int16_t)(x + f - 2), y, yellow);
    SetPixel(dc, (int16_t)(x + f - 3), (int16_t)(y + 1), yellow);
}
