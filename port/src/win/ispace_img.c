/* ISPACE.DLL image loader: ordinal 1 (5:0402) loads a 16-colour DIB,
 * fits its colours to the game palette and makes a bitmap of it;
 * ordinal 2 (6:0000) builds surfaces from such images.
 *
 * Ported so far: images from resources, the colour sets of the caller,
 * colours left as they are (mode 3), added to the palette (mode 2) or put
 * in the palette as ramps (mode 0), ordinal 2's calibration strip
 * (5:17c2) and its surfaces (6:011c, ispace_surface.c), and 5:0000, the
 * dialogs' ship pictures, and 5:075e, the softened pictures of INI
 * Enhance; ordinal 2's surfaces of 6:78ba are ispace_quick.c's, and
 * 6:7fc8, images with VGA colours.  Images from files (5:1d74) log
 * themselves once and give no bitmap. */
#include <stdlib.h>
#include <string.h>

#include "gdi.h"
#include "ispace.h"

#define TYPE_IMAGE 4000                 /* resource type of the images */
#define OWN_COLORS 12                   /* colour set "the image's own" */

typedef IspaceDib Dib;

/* DS:178, 17c, 180 for a palette made with mode 0's fourth word 0 and 1:
 * where the ramps of colours 0-9, 10-14 and the colours of sets 4 and -1
 * start, as byte offsets of the entries. */
const int16_t ispace_ramp_area[2][3] = {{0x2e4, 0x354, 0x398}, {0x28, 0x14c, 0x1c0}};

static struct {
    int16_t height;                     /* DS:1c72: height of the last image */
    int16_t ds_0024;                    /* ramp shift of a ship picture (5:0000) */
    int16_t ds_1ea6;                    /* red and blue swapped (ordinal 18) */
    uint8_t ds_1178[16][4];             /* the image's colours, modes 0 and 1 */
    IspaceImgFlags f;
    IspaceEntries e;
} st;

static void not_ported(const char *what)
{
    win_stub(what);
}

static uint32_t le32(const uint8_t *p)
{
    return p[0] | p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

/* 5:24e4: colours in the table (biClrUsed, else by bit count). */
static int dib_colors(const Dib *d)
{
    uint32_t used = le32(d->data + 32);

    if (used)
        return (int)(used & 0xffff);
    switch (d->data[14]) {
    case 1: return 2;
    case 4: return 16;
    case 8: return 256;
    default: return 0;
    }
}

/* The colour table entry k: blue, green, red, 0. */
static uint8_t *dib_color(const Dib *d, int k)
{
    return d->data + 40 + 4 * k;
}

/* 5:24be: the bits, after the header and the colour table. */
static const uint8_t *dib_bits(const Dib *d)
{
    return d->data + 40 + 4 * dib_colors(d);
}

/* Header, table and bits inside the block (not checked by the DLL). */
static int dib_valid(const Dib *d)
{
    int bpp, w, h, n;

    if (d->size < 40 || le32(d->data) != 40)
        return 0;
    bpp = d->data[14];
    w = (int)le32(d->data + 4);
    h = (int)le32(d->data + 8);
    n = dib_colors(d);
    if ((bpp != 1 && bpp != 4 && bpp != 8) || (bpp == 4 && n < 16) || n > 256 || w <= 0 || h <= 0)
        return 0;
    return 40 + 4 * (uint32_t)n + (uint32_t)((w * bpp + 31) / 32 * 4) * (uint32_t)h <= d->size;
}

/* 5:1c16: image id from the resources of ISPACE.DLL (ids 220, 221, 300)
 * or IGRAPHIC.DLL: a bitmap file whose 14-byte file header is dropped. */
static int resource_dib(int16_t id, Dib *d)
{
    HINSTANCE m = id == 220 || id == 221 || id == 300 ? ispace_module() : igraphic_module();
    uint32_t size;
    const uint8_t *r = module_resource(m, MAKEINTRESOURCE(TYPE_IMAGE), MAKEINTRESOURCE(id), &size);

    if (!r || size < 14 || r[0] != 'B' || r[1] != 'M')
        return 0;
    d->size = size - 14;
    d->data = malloc(d->size);
    if (!d->data)
        return 0;
    memcpy(d->data, r + 14, d->size);
    if (!dib_valid(d)) {
        free(d->data);
        return 0;
    }
    return 1;
}

static void put_le32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

static void set_color(uint8_t *c, const uint8_t rgb[3])
{
    c[2] = rgb[0];
    c[1] = rgb[1];
    c[0] = rgb[2];
}

/* Colour 15 not black: these 16 colours instead (5:26a2). */
static const uint8_t vga[16][3] = {
    {0, 255, 0}, {0, 128, 0}, {128, 128, 0}, {255, 255, 0}, {255, 0, 0}, {128, 0, 0},
    {128, 0, 128}, {255, 0, 255}, {0, 0, 255}, {0, 0, 128}, {0, 128, 128}, {0, 255, 255},
    {255, 255, 255}, {192, 192, 192}, {128, 128, 128}, {0, 0, 0}
};

/* One step away from the colour: red and green 4 (or 2) up, or down
 * near the top. */
static void nudge(uint8_t *c, int step)
{
    c[2] = (uint8_t)(c[2] >= 0xfb ? c[2] - step : c[2] + step);
    c[1] = (uint8_t)(c[1] >= 0xfb ? c[1] - step : c[1] + step);
}

/* Colour k of the image as red, green, blue (or blue, green, red). */
static void image_rgb(const Dib *d, int k, int swap, int rgb[3])
{
    const uint8_t *c = dib_color(d, k);

    rgb[0] = c[swap ? 0 : 2];
    rgb[1] = c[1];
    rgb[2] = c[swap ? 2 : 0];
}

/* Writes a colour at byte offset off of the palette entries (the DLL
 * keeps them as bytes; offsets need not be whole entries). */
static void put_rgb(PALETTEENTRY *e, int off, const int rgb[3])
{
    uint8_t *p = (uint8_t *)e + off;
    int i;

    for (i = 0; i < 3; i++)
        p[i] = (uint8_t)rgb[i];
}

/* Colours from..to-1 as a ramp at byte offset off: steps entries from
 * each colour towards the next, then the last colour. */
static void put_ramp(PALETTEENTRY *e, int off, const Dib *d, int from, int to, int16_t steps)
{
    int c[3], next[3], step[3], k, i, j;

    for (k = from; k < to - 1; k++) {
        image_rgb(d, k, 0, c);
        image_rgb(d, k + 1, 0, next);
        for (j = 0; j < 3; j++)
            step[j] = (next[j] - c[j]) / steps;
        for (i = 0; i < steps; i++, off += 4) {
            put_rgb(e, off, c);
            for (j = 0; j < 3; j++)
                c[j] += step[j];
        }
    }
    image_rgb(d, to - 1, 0, c);
    put_rgb(e, off, c);
}

/* Colours from..to-1 get darker (or stay) one after the other. */
static int descending(const Dib *d, int from, int to)
{
    int16_t prev = 1000, lum;
    int k;

    for (k = from; k < to; k++) {
        const uint8_t *c = dib_color(d, k);

        lum = ispace_lum_image(c[2], c[1], c[0]);
        if (lum > prev)
            return 0;
        prev = lum;
    }
    return 1;
}

/* 5:26a2 mode 0: the image's colours go into palette pal.  Sets 4 and
 * -1: colours 1-15 one after the other.  Otherwise colours 0-9 and 10-14
 * as ramps, each unless its colour set is the image's own and its colours
 * do not get darker in order (DS:1eaa, DS:1eac). */
static void put_ramps(int16_t pal, const Dib *d, signed char a, signed char b)
{
    int s = ispace_pal_slot(pal), fixed, k, rgb[3];
    int16_t steps_a, steps_b, off_a, off_b;
    PALETTEENTRY *e;

    if (s < 0)
        return;
    e = ispace_pal_entries(s);
    fixed = ispace_pal_fixed(s) == 1;
    if (a == 4 && b == -1) {
        for (k = 1; k < 16; k++) {
            image_rgb(d, k, st.ds_1ea6, rgb);
            put_rgb(e, ispace_ramp_area[fixed][2] + 4 * (k - 1), rgb);
        }
        return;
    }
    if (st.f.ds_1ea4) {
        steps_a = steps_b = 1;
        off_a = (int16_t)(0x2a8 + st.ds_0024);  /* DS:174 */
        off_b = (int16_t)(0x2d0 + st.ds_0024);  /* DS:176 */
    } else {
        steps_a = fixed ? 8 : 3;
        steps_b = fixed ? 7 : 4;
        off_a = ispace_ramp_area[fixed][0];
        off_b = ispace_ramp_area[fixed][1];
        st.f.ds_1eaa = a != OWN_COLORS || descending(d, 0, 10);
        st.f.ds_1eac = b != OWN_COLORS || descending(d, 10, 15);
    }
    if (st.f.ds_1ea4 || st.f.ds_1eaa)
        put_ramp(e, off_a, d, 0, 10, steps_a);
    if (st.f.ds_1ea4 || st.f.ds_1eac)
        put_ramp(e, off_b, d, 10, 15, steps_b);
}

/* 5:39f6 and 5:26a2: the image's colours as a 16-entry palette (DS:1178;
 * the DLL also makes a palette of them, DS:1eae, which nothing reads). */
static void keep_colors(const Dib *d)
{
    int n = dib_colors(d), k;

    memset(st.ds_1178, 0, sizeof st.ds_1178);
    for (k = 0; k < 16 && k < n; k++) {
        const uint8_t *c = dib_color(d, k);

        st.ds_1178[k][0] = c[2];
        st.ds_1178[k][1] = c[1];
        st.ds_1178[k][2] = c[0];
        st.ds_1178[k][3] = PC_RESERVED;
    }
}

const uint8_t *ispace_image_colors(void)
{
    return st.ds_1178[0];
}

void ispace_set_image_swap(int16_t on)
{
    st.ds_1ea6 = on;
}

IspaceEntries *ispace_image_entries(void)
{
    return &st.e;
}

/* 5:26a2 with DS:015c set (6:5538's pictures): each colour's entry
 * (DS:1484) in the slot's palette.  A colour of a set nearest in the
 * ranges of sets DS:147c and DS:1480; a colour of the image's own (set
 * 12) nearest in the set of its hue, which goes into the palette at the
 * first colour of that hue.  Only for 8-bit palettes that are not
 * fixed. */
static void image_entries(int s, const Dib *d, signed char a, signed char b)
{
    int16_t hue[15];
    int k, j, met;

    for (k = 0; k < 15; k++) {
        const uint8_t *c = dib_color(d, k);
        hue[k] = -1;            /* [fix: the DLL compares stale stack bytes for colours not of set 12] */
        if ((k < 10 ? a : b) != OWN_COLORS) {
            st.e.ds_1484[k] = ispace_nearest_set_entry(s, c[2], c[1], c[0], st.e.ds_147c, st.e.ds_1480);
            continue;
        }
        hue[k] = ispace_set_of_color(c[2], c[1], c[0]);
        for (met = 0, j = 0; j < k; j++)
            met |= hue[j] == hue[k];
        if (!met)
            ispace_pal_load_set(s, hue[k]);
        st.e.ds_1484[k] = ispace_nearest_set_entry(s, c[2], c[1], c[0], hue[k], -1);
    }
}

/* 5:26a2: fits the image's colours to palette pal.  Colours 0-9 come
 * from colour set a, 10-14 from set b (unless OWN_COLORS or -1); colours
 * 10-14 equal to one of 0-9 are nudged apart.  Mode 2 adds the colours
 * to the palette (mode 6); mode 3 leaves them to the bitmap's colour
 * matching. */
static int fit_colors(int16_t pal, int16_t id, Dib *d, int16_t mode, signed char a, signed char b,
                      int16_t own)
{
    int n = dib_colors(d), s = ispace_pal_slot(pal), k, j;
    uint8_t *c15 = dib_color(d, 15);

    st.f.ds_1ea8 = 0;
    if (!n)
        return 1;
    if ((st.f.ds_0188 && c15[2]) || c15[1] || c15[0]) {
        st.f.ds_1ea8 = 1;
        for (k = 0; k < 16; k++)
            set_color(dib_color(d, k), vga[k]);
    }
    st.f.ds_0188 = 0;
    if (own) {
        not_ported("ispace image: keep own colours (5:26a2)");
        return 0;
    }
    if (id != 0x118) {
        for (k = 0; k < 10; k++)
            if (a != OWN_COLORS && a != -1 && a >= 0 && a < ISPACE_SETS)
                set_color(dib_color(d, k), ispace_set10[(int)a][k]);
        for (k = 10; k < 15; k++)
            if (b != OWN_COLORS && b != -1 && b >= 0 && b < ISPACE_SETS)
                set_color(dib_color(d, k), ispace_set5[(int)b][k - 10]);
    }
    for (k = 10; k < 15; k++)
        for (j = 0; j < 10; j++)
            if (!memcmp(dib_color(d, j), dib_color(d, k), 3))
                nudge(dib_color(d, k), 4);
    if (st.ds_0024)
        for (k = 0; k < 15; k++)
            nudge(dib_color(d, k), 2);
    if (st.e.ds_015c && ispace_pal_bits() >= 8 && s >= 0 && !ispace_pal_fixed(s))
        image_entries(s, d, a, b);
    if ((mode == 0 || mode == 1 || st.e.ds_015c) && !st.f.ds_1ea4)
        keep_colors(d);
    if (mode == 0 && ispace_pal_bits() >= 8)
        put_ramps(pal, d, a, b);
    if (mode == 2)
        for (k = 0; k < n; k++) {
            uint8_t *c = dib_color(d, k);
            ispace_pal_add_color(pal, c[2], c[1], c[0]);
        }
    return 1;
}

/* 6:7fc8: the pixels of an image with VGA colours (fit_colors gave it
 * the vga table above) renumbered from the VGA's colour order to that
 * table's, under a new 4-bit header (5:22e6).  The DLL also counts the
 * pixels by hue into DS:1670/1672, which nothing reads. */
static int vga_order(Dib *d)
{
    static const uint8_t game_color[16] = {15, 5, 1, 2, 9, 6, 10, 13, 14, 4, 0, 3, 8, 7, 11, 12};
    int16_t w = (int16_t)(d->data[4] | d->data[5] << 8), h = (int16_t)(d->data[8] | d->data[9] << 8);
    int stride = ((w + 1) / 2 + 3) & ~3, x, y;
    uint8_t *row;

    memset(d->data, 0, 40);
    put_le32(d->data, 40);
    put_le32(d->data + 4, (uint32_t)w);
    put_le32(d->data + 8, (uint32_t)h);
    d->data[12] = 1;
    d->data[14] = 4;
    put_le32(d->data + 20, (uint32_t)(((4 * w + 31) >> 3 & ~3) * h));
    if (!dib_valid(d))                  /* [fix: the DLL trusts the new header] */
        return 0;
    for (y = 0, row = d->data + 40 + 4 * dib_colors(d); y < h; y++, row += stride)
        for (x = 0; x < w; x++) {
            uint8_t *p = &row[x / 2];
            int shift = x & 1 ? 0 : 4;

            *p = (uint8_t)((*p & ~(0xf << shift)) | game_color[*p >> shift & 0xf] << shift);
        }
    return 1;
}

/* 5:1b8e: image id (from a file when negative: name) with its colours
 * fitted; shows the palette in modes 0 and 2. */
int ispace_dib_load(int16_t pal, int16_t id, LPCSTR name, int16_t mode, signed char a,
                    signed char b, int16_t own, Dib *d)
{
    (void)name;
    if (id < 0) {
        not_ported("ispace image: from a file (5:1d74)");
        return 0;
    }
    if (id == 0 || !resource_dib(id, d))
        return 0;
    if (!fit_colors(pal, id, d, mode, a, b, own)) {
        free(d->data);
        return 0;
    }
    if (mode == 2 || mode == 0)
        ispace_pal_animate(pal, 0, ispace_dc());
    st.e.ds_015c = 0;
    return 1;
}

/* 5:2080: a bitmap of the DIB for the screen with pal realized: 8-bit
 * pixels are palette indices, other colours are matched to pal. */
HBITMAP ispace_dib_bitmap(Dib *d, int16_t pal)
{
    const uint8_t *bits = dib_bits(d);
    HPALETTE old = 0;
    HBITMAP bm;
    HDC dc = GetDC(0);
    int i;

    if (!dc)
        return 0;
    if (pal)
        old = SelectPalette(dc, pal, 0);
    RealizePalette(dc);
    if (d->data[14] == 8 && d->size >= 40 + 512) {
        for (i = 0; i < 256; i++) {
            d->data[40 + 2 * i] = (uint8_t)i;
            d->data[41 + 2 * i] = 0;
        }
        bm = CreateDIBitmap(dc, (const BITMAPINFOHEADER *)d->data, CBM_INIT, bits, d->data, DIB_PAL_COLORS);
    } else {
        bm = CreateDIBitmap(dc, (const BITMAPINFOHEADER *)d->data, CBM_INIT, bits, d->data, DIB_RGB_COLORS);
    }
    if (old)
        SelectPalette(dc, old, 0);
    ReleaseDC(0, dc);
    return bm;
}

static uint8_t channel(const PALETTEENTRY *e, int k)
{
    return k == 0 ? e->peRed : k == 1 ? e->peGreen : e->peBlue;
}

/* 5:075e (b 1 and 2; INI Enhance asks for it): the picture softened in
 * the colours of slot s's entries.  For each channel of a pixel that is
 * not black, a byte sums the pixel at 3/4 (b 1) or 1/2 (b 2) and eight
 * reads around it at 1/32 or 1/16 each: in the row before (DIB rows, the
 * picture's bottom up) x - 1 twice [sic: the second meant x + 1 of the
 * pixel's own row], x and x + 1, in its own row x - 1, in the row after
 * x - 1, x and x + 1.  Off the picture the pixel stands in: in the row
 * before for both reads of a side and for the whole row at twice and
 * once the weight, in the row after once a read and for the whole row
 * at twice and once.  The sums (wrapping as bytes) are matched to the
 * entries of colour set c, or of the image's colours for special
 * images; a pixel whose sums are all 0 keeps its entry. */
static void soften(int s, Bmp *bm, int16_t b, int special, int16_t c)
{
    static const uint8_t shifts[2][3] = {{2, 5, 4}, {1, 4, 3}};     /* the pixel's second, a read, a stand-in */
    const PALETTEENTRY *e = ispace_pal_entries(s);
    int16_t w = (int16_t)bm->w, h = (int16_t)bm->h, stride = (int16_t)((w + 3) & ~3), x, y, k;
    const uint8_t *sh = shifts[b - 1];
    uint8_t *buf, *bits, *sum;
    long i;

    buf = calloc((size_t)stride * (size_t)h + 1, 1);   /* bits[-1]: the colour table's last byte, 0 */
    sum = calloc((size_t)stride * (size_t)h, 3);
    if (!buf || !sum) {
        free(buf);
        free(sum);
        return;
    }
    bits = buf + 1;
    for (y = 0; y < h; y++)
        memcpy(bits + (long)y * stride, bm->px + (long)(h - 1 - y) * w, (size_t)w);
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            const PALETTEENTRY *p = &e[bits[i = (long)y * stride + x]];
            if (!p->peRed && !p->peGreen && !p->peBlue)
                continue;
            for (k = 0; k < 3; k++) {
                uint8_t v = channel(p, k), t = (uint8_t)((b == 1 ? v >> 1 : 0) + (v >> sh[0]));
#define READ(o) (uint8_t)(channel(&e[bits[i + (o)]], k) >> sh[1])
                if (y > 0) {
                    t = (uint8_t)(t + (x > 0 ? READ(-stride - 1) + READ(-1) : v >> sh[2]));
                    t = (uint8_t)(t + (x < w - 1 ? READ(-stride - 1) + READ(-stride + 1) : v >> sh[2]));
                    t = (uint8_t)(t + READ(-stride));
                } else {
                    t = (uint8_t)(t + (v >> sh[1]) + (v >> sh[2]));
                }
                if (y < h - 1) {
                    t = (uint8_t)(t + (x > 0 ? READ(stride - 1) : v >> sh[1]));
                    t = (uint8_t)(t + (x < w - 1 ? READ(stride + 1) : v >> sh[1]));
                    t = (uint8_t)(t + READ(stride));
                } else {
                    t = (uint8_t)(t + (v >> sh[1]) + (v >> sh[2]));
                }
#undef READ
                sum[3 * i + k] = t;
            }
        }
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++) {
            const uint8_t *t = &sum[3 * (i = (long)y * stride + x)];
            if (!t[0] && !t[1] && !t[2])
                continue;
            bm->px[(long)(h - 1 - y) * w + x] = special ? ispace_nearest_image_entry(s, t[0], t[1], t[2], st.ds_1ea6)
                                                        : ispace_nearest_set_entry(s, t[0], t[1], t[2], c, -1);
        }
    free(buf);
    free(sum);
}

int16_t ispace_load_image(int16_t pal, int16_t id, char *name, int16_t dc, int16_t b, int16_t c)
{
    int s = ispace_pal_slot(pal), fixed = s >= 0 && ispace_pal_fixed(s), special = 0, recolor = 0, soft;
    int16_t mode;
    Dib d;
    HBITMAP bm;
    BITMAP info;

    if (ispace_pal_bits() >= 8 && b == 3)
        b = 0;
    if (b < -100)
        b += 150;
    else
        st.ds_0024 = 0;
    ispace_set_dc(dc);
    mode = fixed ? 2 : 3;
    if (id == -2)
        st.f.ds_0188 = 1;
    if (id == -2 || c < -100) {
        if (c < -100) {
            c += 150;
            recolor = 1;
        }
        st.f.ds_1ea4 = 1;
        mode = 0;
    } else {
        st.f.ds_1ea4 = 0;
    }
    if ((fixed && id == 0x118) || id == 0x28a) {
        special = 1;
        if (!ispace_dib_load(pal, id, name, fixed && id == 0x118, 4, -1, 0, &d))
            return 0;
    } else if (recolor) {
        if (!ispace_dib_load(pal, id, name, mode, (signed char)b, (signed char)c, 0, &d))
            return 0;
        c = -1;
        b = 0;
    } else if (!ispace_dib_load(pal, id, name, mode, OWN_COLORS, OWN_COLORS, 0, &d)) {
        return 0;
    }
    soft = GetDeviceCaps(dc, SIZEPALETTE) >= 256 && b;
    if ((st.f.ds_1ea8 && !vga_order(&d)) || (soft && (s < 0 || !pal))) {
        free(d.data);
        return 0;
    }
    bm = ispace_dib_bitmap(&d, pal);
    if (soft && (b < 1 || b > 2 || (fixed && !special)))
        not_ported("ispace image: 5:075e with a fixed palette or b other than 1, 2");
    else if (soft)
        soften(s, handle_get(bm, H_BITMAP), b, special, c);
    if (GetObject(bm, sizeof info, &info))
        st.height = info.bmHeight;
    free(d.data);
    st.ds_0024 = 0;
    st.f.ds_1ea4 = 0;
    return (int16_t)bm;
}

/* 5:0000: mode 0-2 shifts the ramps by DS:0024 (as bytes); with a mode
 * a is less 150, which keeps the shift in ordinal 1. */
HBITMAP ispace_ship_image(int16_t pal, int16_t id, char *name, int16_t a, int16_t b, int16_t mode)
{
    static const int16_t shift[3] = {0, 60, -12};

    if (mode)
        a = (int16_t)(a - 150);
    if (mode >= 0 && mode < 3)
        st.ds_0024 = shift[mode];
    return (HBITMAP)ispace_load_image(pal, id, name, (int16_t)ispace_dc(), a, (int16_t)(b - 150));
}

int16_t ispace_image_height(void)
{
    return st.height;
}

void ispace_set_image_height(int16_t h)
{
    st.height = h;
}

IspaceImgFlags *ispace_img_flags(void)
{
    return &st.f;
}

const uint8_t *ispace_dib_color(const Dib *d, int k)
{
    return dib_color(d, k);
}

const uint8_t *ispace_dib_bits(const Dib *d)
{
    return dib_bits(d);
}

/* 5:17c2: the calibration strip: fourteen 40-pixel cells gap apart on
 * black, each the tile of image 220, cells 1-13 with a shape of image
 * 221 on it (shapes 0-4, 3-0 turned half round, 5-8). */
static HBITMAP build_strip(int16_t pal, HDC dc, int16_t gap)
{
    enum { CELL = 40 };
    int s = ispace_pal_slot(pal), i, w = CELL * 14 + gap * 15, h = CELL + 2 * gap;
    HDC src[2], dst;
    HBITMAP img[2], old[2], bm, old_dst;
    HPALETTE old_pal[2] = {0, 0}, old_pal_dst = 0;

    if (s < 0)
        pal = 0;
    ispace_set_dc(dc);
    img[0] = (HBITMAP)ispace_load_image(pal, 220, "", dc, 3, -1);
    src[0] = CreateCompatibleDC(ispace_dc());
    old[0] = SelectObject(src[0], img[0]);
    if (pal)
        old_pal[0] = SelectPalette(src[0], pal, 0);
    dst = CreateCompatibleDC(ispace_dc());
    bm = CreateCompatibleBitmap(ispace_dc(), (int16_t)w, (int16_t)h);
    if (pal)
        old_pal_dst = SelectPalette(dst, pal, 0);
    old_dst = SelectObject(dst, bm);
    PatBlt(dst, 0, 0, (int16_t)w, (int16_t)h, BLACKNESS);
    for (i = 0; i < 14; i++)
        BitBlt(dst, (int16_t)((CELL + gap) * i + gap), gap, CELL, CELL, src[0], 0, 0, SRCCOPY);
    SelectObject(src[0], old[0]);
    if (old_pal[0])
        SelectPalette(src[0], old_pal[0], 0);
    DeleteDC(src[0]);
    if (img[0])
        DeleteObject(img[0]);

    /* shapes and their mask (1 where black): src[0] shapes, src[1] mask */
    img[0] = (HBITMAP)ispace_load_image(pal, 221, "", dc, 3, -1);
    img[1] = ispace_make_mask(pal, (int16_t)img[0], dc);
    for (i = 0; i < 2; i++) {
        src[i] = CreateCompatibleDC(ispace_dc());
        old[i] = SelectObject(src[i], img[i]);
        if (pal)
            old_pal[i] = SelectPalette(src[i], pal, 0);
    }
    for (i = 0; i < 4; i++) {
        int x = (CELL + gap) * (i + 1) + gap, xr = (CELL + gap) * (9 - i) + CELL + gap - 1;
        BitBlt(dst, (int16_t)x, gap, CELL, CELL, src[1], (int16_t)(CELL * i), 0, SRCAND);
        BitBlt(dst, (int16_t)x, gap, CELL, CELL, src[0], (int16_t)(CELL * i), 0, SRCPAINT);
        StretchBlt(dst, (int16_t)xr, (int16_t)(CELL + gap - 1), -CELL, -CELL, src[1], (int16_t)(CELL * i), 0,
                   CELL, CELL, SRCAND);
        StretchBlt(dst, (int16_t)xr, (int16_t)(CELL + gap - 1), -CELL, -CELL, src[0], (int16_t)(CELL * i), 0,
                   CELL, CELL, SRCPAINT);
    }
    BitBlt(dst, (int16_t)(CELL * 5 + gap * 6), gap, CELL, CELL, src[1], CELL * 4, 0, SRCAND);
    BitBlt(dst, (int16_t)(CELL * 5 + gap * 6), gap, CELL, CELL, src[0], CELL * 4, 0, SRCPAINT);
    for (i = 0; i < 4; i++) {
        int x = (CELL + gap) * (i + 10) + gap;
        BitBlt(dst, (int16_t)x, gap, CELL, CELL, src[1], (int16_t)(CELL * (i + 5)), 0, SRCAND);
        BitBlt(dst, (int16_t)x, gap, CELL, CELL, src[0], (int16_t)(CELL * (i + 5)), 0, SRCPAINT);
    }
    for (i = 0; i < 2; i++) {
        SelectObject(src[i], old[i]);
        if (old_pal[i])
            SelectPalette(src[i], old_pal[i], 0);
        DeleteDC(src[i]);
        if (img[i])
            DeleteObject(img[i]);
    }
    SelectObject(dst, old_dst);
    if (old_pal_dst)
        SelectPalette(dst, old_pal_dst, 0);
    DeleteDC(dst);
    return bm;
}

int16_t ispace_build_surface(int16_t pal, int16_t a, int32_t name, int16_t dc, int16_t e, int16_t f,
                             int16_t g, int16_t h, int16_t i, int16_t j, char k, char l, char m,
                             int16_t n)
{
    (void)name;
    (void)e;
    if (a == -1000)
        return (int16_t)build_strip(pal, dc, f);
    if (n)
        return ispace_quick_surface(pal, a, dc, f, g, h, j, k, l, m);
    return ispace_surface(pal, a, "", dc, f, i, j, (signed char)k, (signed char)l, (signed char)m);
}
