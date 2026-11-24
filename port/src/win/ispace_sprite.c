/* ISPACE.DLL ordinal 18 (6:5e76): image 280 (a small shaded ball, 18 x 18)
 * turned to n angles a quarter of a turn apart, side by side, as a
 * bitmap.  The game makes the sheet its sprites are cut from with it
 * (10:7032): kind 0 is antialiased at half size in two colourings (the
 * colour set 1 range and the same entries moved into the set 0 range),
 * kind 1 is the full-size picture in the image's own colours.
 *
 * Every step works on the DLL's 16-bit values; buffers are DIBs laid out
 * as the DLL's (rows bottom-up, padded to 4 bytes). */
#include <stdlib.h>
#include <string.h>

#include "ispace.h"

#define IMAGE 0x118
#define MAX_ANGLES 5
#define DARK 0x32                       /* a channel at most this is unlit */

/* DS:00f6, DS:0108: sine and minus cosine of 22.5 degree steps, x 512. */
static const int16_t sin512[MAX_ANGLES] = {0, 196, 362, 473, 512};
static const int16_t mcos512[MAX_ANGLES] = {-512, -473, -362, -196, 0};
/* Per angle a shift of the turned picture (the DLL's locals at bp-15a). */
static const int16_t shift[MAX_ANGLES][2] = {{0, 0}, {-1, 2}, {1, 1}, {1, -1}, {0, -1}};

static int16_t ds_01a6 = 40;            /* 5:64f8's last match, a byte offset */

static int16_t stride_of(int16_t width_bytes)
{
    int16_t r = (int16_t)(width_bytes % 4);

    return (int16_t)(width_bytes + (r ? 4 - r : 0));
}

static int16_t sum_diff(const PALETTEENTRY *e, int r, int g, int b)
{
    return (int16_t)(abs(e->peRed - r) + abs(e->peGreen - g) + abs(e->peBlue - b));
}

/* 5:4e96: the entry of group 2 (DS:0180, 16 entries) nearest to the
 * colour (sum of the channel differences); the first closer than 14
 * wins.  Red and blue swap while DS:1ea6 is set. */
static uint8_t nearest_image_entry(int s, uint8_t r, uint8_t g, uint8_t b, int swap)
{
    const PALETTEENTRY *e = ispace_pal_entries(s);
    int16_t first = (int16_t)(ispace_ramp_area[ispace_pal_fixed(s) == 1][2] / 4), best = 1000, d, i,
            found = 0;

    if (swap) {
        uint8_t t = r;
        r = b;
        b = t;
    }
    for (i = first; i < first + 16; i++) {
        d = sum_diff(&e[i], r, g, b);
        if (d < best) {
            best = d;
            found = i;
        }
        if (d < 14)
            break;
    }
    return (uint8_t)found;
}

/* 5:64f8: the entry nearest to the colour in the ranges of colour sets
 * set1 and set2 (-1: none); the first closer than 14 wins, and without
 * any entry to look at the last call's answer stands.  Kind 2 gives 0. */
static uint8_t nearest_set_entry(int s, uint8_t r, uint8_t g, uint8_t b, int set1, int set2)
{
    const PALETTEENTRY *e = ispace_pal_entries(s);
    int sets[2] = {set1, set2}, k;
    int16_t best = 1000, d, off;
    const int16_t *range;

    if (ispace_pal_kind(s) == 2)
        return 0;
    for (k = 0; k < 2; k++) {
        if (sets[k] == -1 || !(range = ispace_pal_range(s, ispace_pal_set_range(s, sets[k]))))
            continue;
        for (off = range[0]; off <= range[1] && off / 4 < 256; off += 4) {
            d = sum_diff(&e[off / 4], r, g, b);
            if (d < best) {
                best = d;
                ds_01a6 = off;
            }
            if (d < 14)
                return (uint8_t)(ds_01a6 >> 2);
        }
    }
    return (uint8_t)(ds_01a6 >> 2);
}

/* A zeroed 8-bit DIB of w x h (5:23a4). */
static int new_dib(int16_t w, int16_t h, IspaceDib *d)
{
    uint32_t bits = (uint32_t)stride_of(w) * (uint32_t)h;

    d->size = 40 + 1024 + bits;
    d->data = calloc(1, d->size);
    if (!d->data)
        return 0;
    d->data[0] = 40;
    d->data[4] = (uint8_t)w;
    d->data[5] = (uint8_t)(w >> 8);
    d->data[8] = (uint8_t)h;
    d->data[9] = (uint8_t)(h >> 8);
    d->data[12] = 1;
    d->data[14] = 8;
    return 1;
}

static int16_t round512(int16_t v)
{
    return (int16_t)((int16_t)(v + (v >= 0 ? 0x100 : -0x100)) / 512);
}

/* The source's 4-bit colours turned to each angle (5 frames of h columns
 * in a sheet of w * n), then single gaps in a row closed with the colour
 * on their left.  The rows run up to the width, the columns up to the
 * height [sic: the image is square]. */
static void turn(const IspaceDib *src, int16_t w, int16_t h, int16_t n, uint8_t *sheet, int16_t stride)
{
    const uint8_t *bits = ispace_dib_bits(src);
    int16_t sstride = stride_of((int16_t)((w + 1) / 2)), hh = (int16_t)(h / 2), f, x, y, tx, ty, idx;
    uint32_t size = (uint32_t)stride * (uint32_t)h;
    uint8_t v, c;

    for (f = 0; f < n; f++)
        for (y = 0; y < w; y++)
            for (x = 0; x < h; x++) {
                v = bits[y * sstride + x / 2];
                c = (uint8_t)(x & 1 ? v & 15 : v >> 4);
                if (!c)
                    continue;
                tx = (int16_t)(round512((int16_t)((y - hh) * sin512[f] + (hh - x) * mcos512[f]))
                               + shift[f][0] + hh);
                ty = (int16_t)(round512((int16_t)((hh - y) * mcos512[f] + (hh - x) * sin512[f]))
                               + shift[f][1] + hh);
                idx = (int16_t)(ty * stride + tx + h * f);
                if (tx >= 0 && tx < w && ty >= 0 && ty < h && idx >= 0 && (uint32_t)idx < size)
                    sheet[idx] = c;
            }
    for (y = 1; y < h - 1; y++)
        for (x = 1; x < h * n - 1; x++) {
            uint8_t *p = &sheet[y * stride + x];
            if (!p[0] && p[-1] && p[1])
                p[0] = p[-1];
        }
}

/* Kind 1: the sheet's colours through the image's colours' nearest
 * entries of group 2. */
static int image_colors(int s, const uint8_t *sheet, int16_t h, int16_t n, int16_t stride, int swap,
                        IspaceDib *out)
{
    const uint8_t *t = ispace_image_colors();
    uint8_t map[16] = {0};
    uint8_t *bits;
    int16_t k, x, y;
    uint32_t size;

    for (k = 1; k < 16; k++)
        map[k] = nearest_image_entry(s, t[4 * k], t[4 * k + 1], t[4 * k + 2], swap);
    if (!new_dib((int16_t)(h * n), h, out))
        return 0;
    bits = out->data + 40 + 1024;
    size = out->size - 40 - 1024;
    for (y = 0; y < h; y++)
        for (x = 0; x < h * n; x++)
            if ((uint32_t)(y * stride + x) < size)
                bits[y * stride + x] = map[sheet[y * stride + x] & 15];
    return 1;
}

/* Kind 0: each 2 x 2 block of the sheet averaged in the image's colours,
 * matched to the colour set 1 range (unlit blocks black), into the top
 * half; the bottom half has the same entries moved into the set 0
 * range. */
static int half_size(int s, const uint8_t *sheet, int16_t h, int16_t n, int16_t stride, IspaceDib *out)
{
    const uint8_t *t = ispace_image_colors();
    int16_t ow = (int16_t)(h * n / 2), ostride = stride_of(ow), rgb_stride = (int16_t)(h * n * 3 / 2);
    int16_t x, y, c, start0, start1, count0, count1;
    const int16_t *r0 = ispace_pal_range(s, ispace_pal_set_range(s, 0));
    const int16_t *r1 = ispace_pal_range(s, ispace_pal_set_range(s, 1));
    uint8_t *rgb, *bits, c1, c2;
    int ch;

    rgb = calloc(1, (size_t)rgb_stride * (size_t)(h / 2) + 3);
    if (!rgb || !new_dib(ow, h, out)) {
        free(rgb);
        return 0;
    }
    for (y = 0; y + 1 < h; y += 2)
        for (x = 0; x + 1 < h * n; x += 2) {
            const uint8_t *p = &sheet[y * stride + x];
            for (ch = 0; ch < 3; ch++)
                rgb[y / 2 * rgb_stride + x * 3 / 2 + ch] = (uint8_t)(
                    (t[4 * (p[0] & 15) + ch] + t[4 * (p[1] & 15) + ch] + t[4 * (p[stride] & 15) + ch]
                     + t[4 * (p[stride + 1] & 15) + ch]) >> 2);
        }
    start0 = r0 ? (int16_t)(r0[0] / 4) : 0;
    start1 = r1 ? (int16_t)(r1[0] / 4) : 0;
    count0 = r0 ? (int16_t)((r0[1] - r0[0]) / 4) : 0;
    count1 = r1 ? (int16_t)((r1[1] - r1[0]) / 4) : 0;
    bits = out->data + 40 + 1024;
    for (y = 0; y < h / 2; y++)
        for (x = 0; x < ow; x++) {
            const uint8_t *p = &rgb[y * rgb_stride + x * 3];
            c1 = p[0] > DARK || p[1] > DARK || p[2] > DARK ? nearest_set_entry(s, p[0], p[1], p[2], 1, -1) : 0;
            c = (int16_t)(c1 && count1 && r0 && r1 ? (int16_t)((c1 - start1) * count0) / count1 + start0 : 0);
            c2 = (uint8_t)c;
            bits[(int16_t)(ostride * h) / 2 + y * ostride + x] = c1;
            bits[y * ostride + x] = c2;
        }
    free(rgb);
    return 1;
}

/* Ordinal 18: pal, then two words the game passes as 1 (not read), kind
 * (0 or 1), n angles (5) and swap (red and blue of the colours swapped
 * as they go into the palette). */
int16_t ispace_sprite_sheet(int16_t pal, int16_t unused1, int16_t unused2, int16_t kind, int16_t n,
                            int16_t swap)
{
    int s = ispace_pal_slot(pal), ok;
    IspaceDib src, out;
    int16_t w, h, stride;
    uint8_t *sheet;
    HBITMAP bm;

    (void)unused1;
    (void)unused2;
    if (s < 0 || n < 1 || n > MAX_ANGLES)
        return 0;
    if (kind == 0 && ispace_pal_fixed(s)) {
        win_stub("ispace_18: fixed palette (6:773c)");
        return 0;
    }
    ispace_set_image_swap((int16_t)(swap != 0));
    ispace_img_flags()->ds_1ea4 = 0;
    ok = kind == 0 ? ispace_dib_load(pal, IMAGE, "", 1, 12, 12, 0, &src)
                   : ispace_dib_load(pal, IMAGE, "", 0, 4, -1, 0, &src);
    if (!ok || src.data[14] != 4) {
        if (ok)
            free(src.data);
        ispace_set_image_swap(0);
        return 0;
    }
    w = (int16_t)(src.data[4] | src.data[5] << 8);
    h = (int16_t)(src.data[8] | src.data[9] << 8);
    stride = stride_of((int16_t)(w * n));
    sheet = calloc((size_t)stride * (size_t)h + (size_t)stride + 2, 1);
    if (!sheet) {
        free(src.data);
        ispace_set_image_swap(0);
        return 0;
    }
    turn(&src, w, h, n, sheet, stride);
    free(src.data);
    ok = kind ? image_colors(s, sheet, h, n, stride, swap != 0, &out) : half_size(s, sheet, h, n, stride, &out);
    ispace_set_image_swap(0);
    free(sheet);
    if (!ok)
        return 0;
    bm = ispace_dib_bitmap(&out, pal);
    free(out.data);
    return (int16_t)bm;
}
