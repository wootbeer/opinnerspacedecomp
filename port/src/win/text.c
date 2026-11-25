/* Fonts and text output.  The game asks for Windows' TrueType fonts
 * (Arial, Times New Roman); the metric-compatible Liberation fonts stand
 * in for them (port/third_party/liberation, loaded from fonts/ next to
 * the executable).  stb_truetype rasterises each font at the size asked
 * for, one bit per pixel as Windows 3.1 drew TrueType text. */
#include <SDL3/SDL_stdinc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gdi.h"
#include "platform/platform.h"
#include "stb/stb_truetype.h"

#define TA_RIGHT_CENTER 0x0006
#define TA_BOTTOM 0x0008
#define TA_BASELINE 0x0018
#define ETO_OPAQUE 0x0002

/* Coverage (0-255) from which a pixel is drawn. */
#define INK 128

/* Font files by family (0 sans, 1 serif) * 4 + bold * 2 + italic.  Only
 * the styles the game uses are shipped; the others fall back to the
 * family's regular style. */
static const char *const file_names[8] = {
    "LiberationSans-Regular.ttf", "LiberationSans-Italic.ttf",
    "LiberationSans-Bold.ttf", "LiberationSans-BoldItalic.ttf",
    "LiberationSerif-Regular.ttf", "LiberationSerif-Italic.ttf",
    "LiberationSerif-Bold.ttf", "LiberationSerif-BoldItalic.ttf",
};

typedef struct {
    int tried, ok;
    stbtt_fontinfo info;
    int avg_width;          /* in font units */
} Ttf;

typedef struct {
    uint8_t *bits;          /* w * h, 1 where the glyph has ink */
    int x, y, w, h;         /* box from the pen position at the cell's top */
    int advance;
    int ready;
} Glyph;

/* Windows 3.1's raster faces on a VGA display: each size's cell height,
 * ascent, internal leading and average width (MS Sans Serif, which Helv
 * stands for: as Wine's metric-compatible font has them; System:
 * VGASYS.FNT), by size.  Their glyphs
 * are drawn from the Liberation outlines.  A regular size asked for bold
 * is emboldened as GDI did it: each character one pixel wider, drawn
 * twice a pixel apart. */
typedef struct {
    const char *face;
    int16_t height, ascent, leading, ave;
    int bold;
} Raster;

static const Raster rasters[] = {
    {"MS Sans Serif", 13, 11, 2, 5, 0},
    {"MS Sans Serif", 16, 13, 3, 7, 0},
    {"MS Sans Serif", 20, 16, 4, 8, 0},
    {"System", 16, 13, 3, 7, 1},
};

typedef struct {
    int used, file;         /* file: index in ttfs, -1 for none */
    const Raster *raster;   /* NULL for a TrueType face */
    int embolden;           /* a raster size made bold by GDI */
    int16_t height, width;  /* as asked for */
    float sx, sy;
    TEXTMETRIC tm;
    Glyph glyph[256];
} Face;

#define FACES 16
static Ttf ttfs[8];
static Face faces[FACES];
static int next_face;

/* Windows-1252 characters 0x80-0x9f as Unicode (0: undefined). */
static const uint16_t cp1252[32] = {
    0x20ac, 0, 0x201a, 0x0192, 0x201e, 0x2026, 0x2020, 0x2021,
    0x02c6, 0x2030, 0x0160, 0x2039, 0x0152, 0, 0x017d, 0,
    0, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014,
    0x02dc, 0x2122, 0x0161, 0x203a, 0x0153, 0, 0x017e, 0x0178,
};

static int unicode_of(uint8_t c)
{
    return c >= 0x80 && c < 0xa0 && cp1252[c - 0x80] ? cp1252[c - 0x80] : c;
}

/* The average character width as Arial's OS/2 table gives it (the
 * weighted average of a-z and space); Liberation's own field is computed
 * over all glyphs and is wider. */
static int average_width(const stbtt_fontinfo *f)
{
    static const char letters[] = "abcdefghijklmnopqrstuvwxyz ";
    static const uint8_t weight[] = {
        64, 14, 27, 35, 100, 20, 14, 42, 63, 3, 6, 35, 20,
        56, 56, 17, 4, 49, 56, 71, 31, 10, 18, 3, 18, 2, 166,
    };
    long sum = 0;
    int i, adv, lsb;

    for (i = 0; letters[i]; i++) {
        stbtt_GetCodepointHMetrics(f, letters[i], &adv, &lsb);
        sum += (long)adv * weight[i];
    }
    return (int)(sum / 1000);
}

static int load_ttf(int i)
{
    Ttf *t = &ttfs[i];
    char name[64];
    const void *data;
    size_t size;

    if (t->tried)
        return t->ok;
    t->tried = 1;
    snprintf(name, sizeof name, "fonts/%s", file_names[i]);
    data = platform_asset(name, &size);
    t->ok = data && stbtt_InitFont(&t->info, data, 0);
    if (t->ok)
        t->avg_width = average_width(&t->info);
    return t->ok;
}

/* The shipped file for a family and style, -1 if none loads. */
static int font_file(int family, int bold, int italic)
{
    int i = family * 4 + bold * 2 + italic;

    if (load_ttf(i))
        return i;
    if (load_ttf(family * 4))
        return family * 4;
    return load_ttf(0) ? 0 : -1;
}

static int iround(float v)
{
    return (int)floorf(v + 0.5f);
}

/* Windows' TrueType metrics: a positive height is the cell (ascent +
 * descent), a negative one the em; a width scales the font from its own
 * average character width at that height (rounded, as GDI reports it) to
 * the one asked for.  A raster face has its size's metrics, the outlines
 * scaled to its em with their baseline at its ascent. */
static void set_metrics(Face *f, int bold, int italic, int family)
{
    const Raster *r = f->raster;
    TEXTMETRIC *tm = &f->tm;
    int asc = 1854, desc = -434, gap = 67, upm = 2048, avg = 904;
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;

    if (f->file >= 0) {
        const stbtt_fontinfo *info = &ttfs[f->file].info;
        stbtt_GetFontVMetrics(info, &asc, &desc, &gap);
        stbtt_GetFontBoundingBox(info, &x0, &y0, &x1, &y1);
        upm = iround(1 / stbtt_ScaleForMappingEmToPixels(info, 1));
        avg = ttfs[f->file].avg_width;
    }
    if (r)
        f->sy = (float)(r->height - r->leading) / upm;
    else
        f->sy = f->height > 0 ? (float)f->height / (asc - desc) : (float)-f->height / upm;
    f->sx = f->width && !r ? f->sy * f->width / SDL_max(1, iround(avg * f->sy)) : f->sy;
    memset(tm, 0, sizeof *tm);
    tm->tmAscent = (int16_t)(r ? r->ascent : iround(asc * f->sy));
    tm->tmHeight = (int16_t)(r ? r->height : tm->tmAscent + iround(-desc * f->sy));
    tm->tmDescent = (int16_t)(tm->tmHeight - tm->tmAscent);
    tm->tmInternalLeading = (int16_t)(r ? r->leading : tm->tmHeight - iround(upm * f->sy));
    tm->tmExternalLeading = (int16_t)(r ? 0 : iround(gap * f->sy));
    tm->tmAveCharWidth = (int16_t)(r ? r->ave + f->embolden : f->width ? f->width : iround(avg * f->sx));
    tm->tmMaxCharWidth = (int16_t)(iround((x1 - x0) * f->sx) + f->embolden);
    tm->tmOverhang = (int16_t)f->embolden;
    tm->tmWeight = (int16_t)(bold ? 700 : 400);
    tm->tmItalic = (BYTE)italic;
    tm->tmFirstChar = 0x20;
    tm->tmLastChar = 0xff;
    tm->tmDefaultChar = 0x1f;
    tm->tmBreakChar = 0x20;
    /* variable pitch, swiss or roman; TrueType ones vector and TrueType */
    tm->tmPitchAndFamily = (BYTE)(r ? 0x21 : family ? 0x17 : 0x27);
    tm->tmDigitizedAspectX = 96;
    tm->tmDigitizedAspectY = 96;
}

/* The size of a raster face Windows picks for a height (positive: the
 * cell, negative: the em, 0: the smallest): the largest not above it,
 * else the smallest.  NULL for faces that are not raster ones (Helv is
 * MS Sans Serif, as WIN.INI's FontSubstitutes had it). */
static const Raster *raster_of(const char *face, int16_t height)
{
    const Raster *pick = NULL;
    size_t i;

    if (!SDL_strcasecmp(face, "Helv"))
        face = "MS Sans Serif";
    for (i = 0; i < SDL_arraysize(rasters); i++) {
        const Raster *r = &rasters[i];
        int size = height > 0 ? r->height : r->height - r->leading;
        if (SDL_strcasecmp(face, r->face))
            continue;
        if (!pick || size <= SDL_abs(height))
            pick = r;
    }
    return pick;
}

static void free_face(Face *f)
{
    int i;

    for (i = 0; i < 256; i++)
        free(f->glyph[i].bits);
    memset(f, 0, sizeof *f);
}

/* The realised face of a font; the game creates its fonts for each
 * drawing, so faces are kept by file and size. */
static Face *face_of(const Font *font)
{
    const Raster *raster = raster_of(font->face, font->height);
    int family = strcmp(font->face, "Times New Roman") == 0;
    int bold = font->weight > 550 || (raster && raster->bold);
    int embolden = bold && raster && !raster->bold;
    int italic = font->italic;
    int file = font_file(family, bold && !embolden, italic);
    int16_t height = font->height ? font->height : 16;
    Face *f;
    int i;

    for (i = 0; i < FACES; i++) {
        f = &faces[i];
        if (f->used && f->raster == raster && f->embolden == embolden && f->file == file && f->height == height
            && f->width == font->width && f->tm.tmWeight == (bold ? 700 : 400) && f->tm.tmItalic == italic)
            return f;
    }
    f = &faces[next_face];
    next_face = (next_face + 1) % FACES;
    free_face(f);
    f->used = 1;
    f->file = file;
    f->height = height;
    f->width = font->width;
    f->raster = raster;
    f->embolden = embolden;
    set_metrics(f, bold, italic, family);
    return f;
}

static Face *dc_face(const Dc *d)
{
    Font *font = handle_get(d->font, H_FONT);

    return font ? face_of(font) : NULL;
}

static const Glyph *glyph(Face *f, uint8_t c)
{
    Glyph *g = &f->glyph[c];
    const stbtt_fontinfo *info;
    int cp = unicode_of(c), adv, lsb, x0, y0, x1, y1, i;

    if (g->ready)
        return g;
    g->ready = 1;
    if (f->file < 0) {
        g->advance = f->tm.tmAveCharWidth;
        return g;
    }
    info = &ttfs[f->file].info;
    stbtt_GetCodepointHMetrics(info, cp, &adv, &lsb);
    g->advance = iround(adv * f->sx) + f->embolden;
    stbtt_GetCodepointBitmapBox(info, cp, f->sx, f->sy, &x0, &y0, &x1, &y1);
    if (x1 <= x0 || y1 <= y0)
        return g;
    g->bits = calloc((size_t)(x1 - x0 + f->embolden) * (y1 - y0), 1);
    if (!g->bits)
        return g;
    g->x = x0;
    g->y = f->tm.tmAscent + y0;
    g->w = x1 - x0 + f->embolden;
    g->h = y1 - y0;
    stbtt_MakeCodepointBitmap(info, g->bits, x1 - x0, g->h, g->w, f->sx, f->sy, cp);
    for (i = 0; i < g->w * g->h; i++)
        g->bits[i] = g->bits[i] >= INK;
    for (i = g->w * g->h - 1; f->embolden && i > 0; i--)
        g->bits[i] |= i % g->w ? g->bits[i - 1] : 0;
    return g;
}

static int text_width(Face *f, LPCSTR s, int n, const int16_t *dx)
{
    int i, w = 0;

    for (i = 0; i < n; i++)
        w += dx ? dx[i] : glyph(f, (uint8_t)s[i])->advance;
    return w;
}

/* The cell's top-left for text of width w at (x, y) by the DC's
 * alignment, in logical units; with TA_UPDATECP the text starts at the
 * current position, which moves past it. */
static POINT text_origin(Dc *d, const Face *f, int x, int y, int w)
{
    POINT p;
    int h = d->align & TA_RIGHT_CENTER;

    if (d->align & TA_UPDATECP) {
        x = d->pos.x;
        y = d->pos.y;
        if (h == TA_LEFT)
            d->pos.x = (int16_t)(x + w);
        else if (h == TA_RIGHT)
            d->pos.x = (int16_t)(x - w);
    }
    if (h == TA_CENTER)
        x -= w / 2;
    else if (h == TA_RIGHT)
        x -= w;
    if ((d->align & TA_BASELINE) == TA_BASELINE)
        y -= f->tm.tmAscent;
    else if (d->align & TA_BOTTOM)
        y -= f->tm.tmHeight;
    p.x = (int16_t)x;
    p.y = (int16_t)y;
    return p;
}

/* r (device pixels) filled with v, inside clip. */
static void fill_box(Dc *d, RECT r, const RECT *clip, uint8_t v)
{
    Bmp *b = dc_bmp(d);
    int x, y;

    IntersectRect(&r, &r, clip);
    for (y = r.top; y < r.bottom; y++)
        for (x = r.left; x < r.right; x++)
            if (gdi_drawable(d, x, y))
                b->px[(size_t)y * b->w + x] = v;
}

/* Draws the glyphs of s with the cell's top-left at device (x, y). */
static void draw_glyphs(Dc *d, Face *f, int x, int y, LPCSTR s, int n, const int16_t *dx,
                        const RECT *clip)
{
    Bmp *b = dc_bmp(d);
    uint8_t v = gdi_pixel_of(d, d->text);
    int k, i, j;

    for (k = 0; k < n; k++) {
        const Glyph *g = glyph(f, (uint8_t)s[k]);
        for (j = 0; j < g->h; j++) {
            int py = y + g->y + j;
            if (py < clip->top || py >= clip->bottom)
                continue;
            for (i = 0; i < g->w; i++) {
                int px = x + g->x + i;
                if (g->bits[j * g->w + i] && px >= clip->left && px < clip->right && gdi_drawable(d, px, py))
                    b->px[(size_t)py * b->w + px] = v;
            }
        }
        x += dx ? dx[k] : g->advance;
    }
}

/* TextOut and ExtTextOut: rect (logical) is filled with ETO_OPAQUE and
 * clips with ETO_CLIPPED. */
static BOOL text_out(HDC h, int x, int y, UINT flags, const RECT *rect, LPCSTR s, int n,
                     const int16_t *dx)
{
    Dc *d = dc_get(h);
    Face *f;
    RECT clip, box, r;
    POINT o;
    int w;

    if (!d || !dc_bmp(d) || !(f = dc_face(d)))
        return 0;
    clip = d->clip;
    if (rect)
        SetRect(&r, (int16_t)DX(d, rect->left), (int16_t)DY(d, rect->top),
                (int16_t)DX(d, rect->right), (int16_t)DY(d, rect->bottom));
    if (rect && flags & ETO_OPAQUE)
        fill_box(d, r, &clip, gdi_pixel_of(d, d->bk));
    if (rect && flags & ETO_CLIPPED)
        IntersectRect(&clip, &clip, &r);
    w = text_width(f, s, n, dx);
    o = text_origin(d, f, x, y, w);
    x = DX(d, o.x);
    y = DY(d, o.y);
    if (d->bkmode == OPAQUE) {
        SetRect(&box, (int16_t)x, (int16_t)y, (int16_t)(x + w), (int16_t)(y + f->tm.tmHeight));
        fill_box(d, box, &clip, gdi_pixel_of(d, d->bk));
    }
    draw_glyphs(d, f, x, y, s, n, dx, &clip);
    return 1;
}

BOOL TextOut(HDC dc, int16_t x, int16_t y, LPCSTR s, int16_t n)
{
    return text_out(dc, x, y, 0, NULL, s, n, NULL);
}

BOOL ExtTextOut(HDC dc, int16_t x, int16_t y, UINT flags, const RECT *r, LPCSTR s, UINT n,
                int16_t *dx)
{
    return text_out(dc, x, y, flags, r, s, (int)n, dx);
}

DWORD GetTextExtent(HDC h, LPCSTR s, int16_t n)
{
    Dc *d = dc_get(h);
    Face *f = d ? dc_face(d) : NULL;

    return f ? MAKELONG(text_width(f, s, n, NULL), f->tm.tmHeight) : 0;
}

BOOL GetTextMetrics(HDC h, TEXTMETRIC *tm)
{
    Dc *d = dc_get(h);
    Face *f = d ? dc_face(d) : NULL;

    if (!f)
        return 0;
    *tm = f->tm;
    return 1;
}
