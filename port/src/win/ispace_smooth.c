/* ISPACE.DLL ordinal 12 (6:00c4, 7:12d8): a 16-colour image drawn at
 * twice its size with smoothed edges and shading.  Each pixel becomes a
 * 2x2 block; colours 0-9 and 10-14 are two groups, each shaded along a
 * ramp of palette entries (7:4ee8) by a lightness worked out per block,
 * spread to the neighbouring blocks of its group and blurred.  Colour 15
 * is the background.
 *
 * Only the DLL's 8-bit display path is ported (the display here is
 * 8-bit); images with VGA colours (6:7fc8) log themselves and give no
 * bitmap. */
#include <stdlib.h>
#include <string.h>

#include "ispace.h"

#define BG 15                           /* background colour of the images */
#define BG_CODE 100                     /* block code of the background */
#define TAKEN 0x65                      /* added to the code of a corner taken from a neighbour */
#define DARK 245                        /* entry for shades below a ramp */
#define FAINT 2                         /* shades up to this stay background */

typedef IspaceRamp Ramp;

static struct {
    Ramp a[10];                         /* colours 0-9: DS:1108, 111c, 1130, 1144 */
    Ramp b[5];                          /* colours 10-14: DS:1ca4, 1cae, 1cb8, 1cc2 */
} st;

IspaceRamp *ispace_ramps(int group)
{
    return group ? st.b : st.a;
}

static void not_ported(const char *what)
{
    win_stub(what);
}

int16_t ispace_newton_root(int32_t sq, int32_t m)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (m < 2)
            m = 2;
        m += (sq - m * m) / (2 * m);
    }
    return (int16_t)m;
}

static int16_t rms3(int32_t r, int32_t g, int32_t b)
{
    return ispace_newton_root((r * r + g * g + b * b) / 3, (int16_t)((r + g + b) / 3));
}

int16_t ispace_lum(int r, int g, int b)
{
    return rms3(r - (r >> 2), g, b >> 1);
}

int16_t ispace_lum_image(int r, int g, int b)
{
    return rms3(r - (r >> 2), g, (b >> 1) + (b >> 3));
}

static int16_t entry_lum(const PALETTEENTRY *e)
{
    return ispace_lum(e->peRed, e->peGreen, e->peBlue);
}

/* 5:66ea from 6a4e on. */
static int16_t set_of_color_6a4e(int r, int g, int b, int m)
{
    if (94 * r / g > 100 * r / b && r - g > 20) {
        if (r < 180 && b < 200 && g < 150)
            return 100 * r / b < 85 ? 8 : 7;
        if (100 * r / b < 85)
            return 8;
        if (100 * r / b >= 110 || 100 * g / b <= 50)
            return 7;
        return 8;
    }
    if (m * 100 / r < 35 && b < g && b < r)
        return 3;
    if (b > g)
        return 0;
    if (100 * b / g >= 30)
        return 10;
    return 100 * r / g > 80 ? 5 : 4;
}

int16_t ispace_set_of_color(int r, int g, int b)
{
    int m;

    r = r < 1 ? 1 : r;
    g = g < 1 ? 1 : g;
    b = b < 1 ? 1 : b;
    m = abs(r - b) >= abs(r - g) ? abs(r - b) : abs(r - g);
    if (m * 100 / r < 10)
        return g > r && 100 * b / g < 93 ? 3 : 2;
    if (abs(r - g) * 100 / r < 8 && abs(r - b) * 100 / r < 30 && (b > r || b > g))
        return g > r && 100 * b / g < 93 ? 3 : 2;
    if (abs(g - b) * 100 / g < 6 && abs(r - g) * 100 / r < 21)
        return 2;
    if ((!(r - g > 10 && r - b > 50) && !(r > 210 && g <= r && r - b > 30))
        || (b - g >= 70 && r / b <= 150))
        return set_of_color_6a4e(r, g, b, m);
    if (r / g > 10 && r / b > 10)
        return 1;
    if (100 * r / b > 650 || r - b > 180) {
        if (100 * g / b > 88 && 100 * g / b < 111 && (r / g < 4 || (r < 150 && r / g < 8)))
            return 11;
        if (100 * g / r > 85)
            return r > 210 ? 1 : 5;
        if (100 * g / r > 74 || (100 * g / r > 65 && r < 170))
            return 5;
        if (100 * g / r > 60 || 100 * g / r <= 35 || 100 * b / g <= 12 || r - g >= 110)
            return 1;
        return 9;
    }
    if (100 * g / b > 85 && 100 * g / b < 115 && (r / g < 4 || (r < 150 && r / g < 10)))
        return 11;
    if (r - g > 30 && r - g < 80 && 100 * b / g < 85 && 100 * g / r > 45 && 100 * g / r < 85)
        return 9;
    if (100 * b / g > 55 && 100 * b / g < 100)
        return 13;
    if (100 * b / g > 25 && 100 * b / g < 100 && 100 * g / r > 60)
        return 1;
    return 100 * r / (b > g ? b : g) > 200 ? 1 : 9;
}

/* The colour set of set id 0-13 (the jump table of 7:4ee8); -1 for the
 * others (the DLL reads an uninitialised word). */
static int set_of_id(int16_t id)
{
    static const int8_t set[14] = {8, 4, 0, 15, 10, 1, 3, 5, 7, 17, 13, 14, 6, 2};

    return id >= 0 && id < 14 ? set[id] : -1;
}

/* A group's numbers in 7:4ee8: divisors placing a ramp in the group's
 * area (for its colours, for its first and last entry), and the scale
 * and end of the position in the colour set (ten colours per 100). */
typedef struct {
    int16_t pos_div, first_div, scale, top;
} Group;

static const Group groups[2] = {
    {40, 10, 3600, 90},
    {20, 5, 800, 40},
};

static uint8_t set_channel(int group, int set, int q, int ch)
{
    return group ? ispace_set5[set][q][ch] : ispace_set10[set][q][ch];
}

/* Fills the entries from byte offset pos up to end with colour set set
 * stretched over them. */
static void put_set(PALETTEENTRY *e, int group, int set, int16_t pos, int16_t end,
                    int16_t span_count)
{
    const Group *gr = &groups[group];
    uint8_t *p = (uint8_t *)e;
    int16_t i, t, ch;

    for (i = 0; pos < end; i++, pos += 4)
        for (ch = 0; ch < 3; ch++) {
            uint8_t c0, c1;

            if (group == 0)
                t = (int16_t)((int32_t)gr->scale * i / span_count);
            else
                t = (int16_t)(gr->scale * i) / span_count;
            if (t >= gr->top)
                t = (int16_t)(gr->top - 1);
            c0 = set_channel(group, set, t / 10, ch);
            c1 = set_channel(group, set, t / 10 + 1, ch);
            p[pos + ch] = (uint8_t)(c0 + (int16_t)((c1 - c0) * (t % 10)) / 10);
        }
}

/* 7:4ee8: ramp r of a group: count image colours from colour start (10
 * and up: the second group).  Set ids 100 and up use the group's whole
 * area as the image loader filled it; others fill their share of it with
 * their colour set and show the palette. */
static void ramp_setup(int s, int16_t id, int16_t r, int16_t count, int16_t start)
{
    int group = start >= 10, own = id >= 100, set = set_of_id(id);
    const int16_t *area = ispace_ramp_area[ispace_pal_fixed(s) == 1];
    PALETTEENTRY *e = ispace_pal_entries(s);
    const Group *gr = &groups[group];
    int16_t from = area[group], span = (int16_t)(area[group + 1] - from);
    Ramp *rp;

    if (group)
        start = (int16_t)(start - 10);
    if (id == -1 || r < 0 || r >= (group ? 5 : 10) || (!own && set < 0))
        return;
    rp = group ? &st.b[r] : &st.a[r];
    if (own) {
        rp->first = (int16_t)(from / 4);
        rp->last = (int16_t)(area[group + 1] / 4 - 1);
    } else {
        int16_t pos = (int16_t)((int16_t)(span * start) / gr->pos_div * 4 + from);
        int16_t end = (int16_t)((int16_t)(span * (start + count)) / gr->pos_div * 4 + from);

        put_set(e, group, set, pos, end, (int16_t)(span * count));
        rp->first = (int16_t)(((int16_t)(span * start) / gr->first_div + from) / 4);
        rp->last = (int16_t)(((int16_t)(span * (start + count)) / gr->first_div + from) / 4 - 1);
    }
    rp->lum_first = entry_lum(&e[rp->first & 0xff]);
    rp->lum_last = entry_lum(&e[rp->last & 0xff]);
    if (!own)
        ispace_pal_animate(ispace_pal_handle(s), 0, ispace_dc());
}

/* 5:6b72: from entry idx, the entry between first and last whose
 * lightness comes nearest v, walking darker or lighter while it gets
 * nearer (within 3 is near enough). */
static int16_t nearest_shade(const PALETTEENTRY *e, int16_t v, int16_t first, int16_t last,
                             int16_t idx)
{
    int16_t lum = entry_lum(&e[idx]), d = (int16_t)abs(lum - v), dp, step = lum > v ? 1 : -1, p;

    if (d < 3)
        return idx;
    for (p = (int16_t)(idx + step); step > 0 ? p <= last : p >= first; p = (int16_t)(p + step)) {
        dp = (int16_t)abs(entry_lum(&e[p]) - v);
        if (dp > d)
            return (int16_t)(p - step);
        if (dp < 3)
            return p;
        d = dp;
    }
    return step > 0 ? last : first;
}

uint8_t ispace_ramp_shade(const PALETTEENTRY *e, const IspaceRamp *rp, uint8_t v)
{
    int16_t idx, den = (int16_t)(rp->lum_first - rp->lum_last);
    int32_t q;

    if (2 * v <= rp->lum_last)
        return DARK;
    q = den ? (int32_t)(int16_t)(v - rp->lum_last) * (int16_t)(rp->last - rp->first) / den : 0;
    idx = (int16_t)(rp->last - (int16_t)q);
    if (idx < rp->first)
        idx = rp->first;
    else if (idx > rp->last)
        idx = rp->last;
    return (uint8_t)nearest_shade(e, v, rp->first, rp->last, idx);
}

/* The source image: 4-bit pixels, rows bottom-up as stored. */
typedef struct {
    const uint8_t *bits;
    long size, stride;
} Image;

static int pixel(const Image *im, int x, int y)
{
    long o = y * im->stride + x / 2;
    int byte = o < im->size ? im->bits[o] : 0xff;

    return x & 1 ? byte & 15 : byte >> 4;
}

/* The working planes, all (2n)^2 bytes, n the image height: shade
 * planes 0-1 (blurred, final) and 2-3 (drawn by group: plane 2 colours
 * 0-9, plane 3 colours 10-14), and the code plane: the block's ramp and
 * group ((ramp - 1) * 2 + plane), BG_CODE for the background. */
typedef struct {
    uint8_t *shade[4], *code;
    long w;
} Planes;

static void fill_block(uint8_t *p, long o, long w, uint8_t v)
{
    p[o] = p[o + 1] = p[o + w] = p[o + w + 1] = v;
}

static void add(uint8_t *p, long o, uint8_t v)
{
    p[o] = (uint8_t)(p[o] + v);
}

/* Pass 2 or 3 of 7:12d8: each pixel of the pass's group becomes a block
 * of its lightness on the pass's plane; corners next to the other group
 * gain, and the lightness spreads into the facing cells of neighbouring
 * blocks of the same group.  Background pixels mark their blocks. */
static void draw_group(Planes *pl, const Image *im, int n, int pass, const int16_t lum[15],
                       const int16_t ramp[15], int16_t g)
{
    /* neighbours up, down, left, right */
    static const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
    uint8_t *e = pl->shade[pass];
    long w = pl->w, near[4][2] = {{-w, -w + 1}, {2 * w, 2 * w + 1}, {-1, w - 1}, {2, w + 2}};
    int x, y, k;

    for (y = 0; y < n; y++)
        for (x = 0; x < n; x++) {
            long o = 2 * y * w + 2 * x;
            int c = pixel(im, x, y), stop[4], other[4];
            uint8_t full, part;

            if (c == BG) {
                fill_block(pl->code, o, w, BG_CODE);
                continue;
            }
            full = (uint8_t)(lum[c] >> 1);
            part = (uint8_t)(lum[c] >> 2);
            if (g == 1)
                full = (uint8_t)(full + part);
            if ((c >= 10) != (pass == 3) || full == 0)
                continue;
            for (k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k], nc;

                stop[k] = 1;
                other[k] = 0;
                if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                    continue;
                nc = pixel(im, nx, ny);
                stop[k] = nc == BG || (nc >= 10) != (c >= 10);
                other[k] = stop[k] && nc != BG;
            }
            fill_block(pl->code, o, w, (uint8_t)((ramp[c] - 1) * 2 + pass));
            for (k = 0; k < 4; k++) {
                int corner = other[k >> 1] + other[2 + (k & 1)];
                long at = o + (k >> 1) * w + (k & 1);

                add(e, at, full);
                if (corner)
                    add(e, at, (uint8_t)(part << (corner - 1)));
            }
            for (k = 0; k < 4; k++)
                if (!stop[k]) {
                    add(e, o + near[k][0], part);
                    add(e, o + near[k][1], part);
                }
        }
}

/* Plane q (0, 1) gets plane q + 2 blurred: each lit cell keeps 3/4 of
 * itself and gains 1/16 of each diagonal neighbour (of itself where the
 * neighbour is 20 or less). */
static void blur(Planes *pl, int q)
{
    const uint8_t *s = pl->shade[q + 2];
    uint8_t *d = pl->shade[q];
    long w = pl->w, diag[4] = {-w - 1, -w + 1, w - 1, w + 1}, o;
    int x, y, k;

    for (y = 1; y < w - 1; y++)
        for (x = 1; x < w - 1; x++) {
            uint8_t v = s[o = y * w + x];

            if (!v)
                continue;
            add(d, o, v >> 1);
            add(d, o, v >> 2);
            for (k = 0; k < 4; k++)
                add(d, o, (s[o + diag[k]] > 20 ? s[o + diag[k]] : v) >> 4);
        }
}

/* A block's group for the corner pass: 0, 1 or 2 (background). */
static int block_group(const Planes *pl, long o)
{
    return pl->code[o] == BG_CODE ? 2 : pl->code[o] & 1;
}

/* Cell t takes group side's shade and code from cell from. */
static void take(Planes *pl, long t, int side, long from)
{
    pl->shade[1][t] = 0;
    pl->shade[0][t] = 0;
    if (side == 2)
        return;
    pl->shade[side][t] = pl->shade[side][from];
    pl->code[t] = (uint8_t)(pl->code[from] + TAKEN);
}

/* Corners where a block meets two blocks of another group (and, for a
 * group-0 block, a third such block diagonally) take that group's
 * neighbouring cell, cutting the corner. */
static void cut_corners(Planes *pl, int n)
{
    long w = pl->w;
    int r, x;

    for (r = 2; r < n - 2; r++)
        for (x = 2; x < n - 2; x++) {
            long o = 2 * r * w + 2 * x;
            int cur = block_group(pl, o), left = block_group(pl, o - 2), up = block_group(pl, o - 2 * w);
            int right = block_group(pl, o + 2), down = block_group(pl, o + 2 * w);

            if (left != cur) {
                if (up == left && (cur || (pl->code[o + 2 * w - 2] & 1) == left))
                    take(pl, o, left, o - w);
                if (down == left && (cur || (pl->code[o - 2 * w - 2] & 1) == left))
                    take(pl, o + w, left, o + 2 * w);
            }
            if (right != cur) {
                if (up == right && (cur || (pl->code[o + 2 * w + 2] & 1) == right))
                    take(pl, o + 1, right, o - w + 1);
                if (down == right && (cur || (pl->code[o - 2 * w + 2] & 1) == right))
                    take(pl, o + w + 1, right, o + 2 * w + 1);
            }
        }
}

/* The final pixel of cell i: the shade of the plane that is lit more on
 * its block's ramp; cells lit 2 or less stay 0. */
static uint8_t final_pixel(const Planes *pl, long i, const PALETTEENTRY *e)
{
    int m = pl->code[i], e0 = pl->shade[0][i], e1 = pl->shade[1][i], k;

    if (m > BG_CODE)
        m -= TAKEN;
    if (e0 > FAINT && e1 < e0) {
        k = m % 2 == 1 ? 0 : m >> 1;
        return k < 10 ? ispace_ramp_shade(e, &st.a[k], (uint8_t)e0) : 0;
    }
    if (e1 > FAINT) {
        k = m & 1 ? m >> 1 : 0;
        return k < 5 ? ispace_ramp_shade(e, &st.b[k], (uint8_t)e1) : 0;
    }
    return 0;
}

/* The lightness and ramp of each colour of a group, the group's ramps
 * set up: one ramp of set id + 100 (the image loader's ramp), or with
 * the image's own colours (set 12) one per run of colours of the same
 * hue. */
static void group_ramps(int s, const IspaceDib *d, int from, int to, signed char set,
                        int16_t lum[15], int16_t ramp[15])
{
    int16_t id[16], count = 0, r = 0;
    int i;

    for (i = 0; i < 16; i++)
        id[i] = 100;
    for (i = from; i < to; i++) {
        const uint8_t *c = ispace_dib_color(d, i);

        if (set == 12)
            id[i] = ispace_set_of_color(c[2], c[1], c[0]);
        lum[i] = ispace_lum_image(c[2], c[1], c[0]);
    }
    if (set != 12) {
        ramp_setup(s, (int16_t)(100 + set), 0, (int16_t)(to - from), (int16_t)from);
        for (i = from; i < to; i++)
            ramp[i] = 0;
        return;
    }
    for (i = from + 1; i <= to; i++) {
        count++;
        ramp[i - 1] = r;
        if (id[i] == id[i - 1])
            continue;
        ramp_setup(s, id[i - 1], r, count, (int16_t)(i - count));
        r++;
        count = 0;
    }
}

/* The output DIB: 8-bit, n x n, its colour table left to 5:2080. */
static int new_dib(IspaceDib *d, int n, long *stride)
{
    uint8_t *h;
    long bytes;

    *stride = (n + 3) & ~3;
    bytes = *stride * n;
    d->size = 40 + 4 * 256 + (uint32_t)bytes;
    d->data = calloc(d->size, 1);
    if (!d->data)
        return 0;
    h = d->data;
    h[0] = 40;
    h[4] = h[8] = (uint8_t)n;
    h[5] = h[9] = (uint8_t)(n >> 8);
    h[12] = 1;
    h[14] = 8;
    h[20] = (uint8_t)bytes;
    h[21] = (uint8_t)(bytes >> 8);
    h[22] = (uint8_t)(bytes >> 16);
    return 1;
}

static int alloc_planes(Planes *pl, int n)
{
    size_t size = (size_t)4 * n * n;
    int k, ok = 1;

    pl->w = 2L * n;
    for (k = 0; k < 4; k++)
        ok &= (pl->shade[k] = calloc(size, 1)) != NULL;
    ok &= (pl->code = calloc(size, 1)) != NULL;
    return ok;
}

static void free_planes(Planes *pl)
{
    int k;

    for (k = 0; k < 4; k++)
        free(pl->shade[k]);
    free(pl->code);
}

/* The smoothed image as a bitmap: drawn by group, blurred, corners cut,
 * then shaded from the palette. */
static HBITMAP render(int s, int16_t pal, const Image *im, int n, const int16_t lum[15],
                      const int16_t ramp[15], int16_t g)
{
    const PALETTEENTRY *e = ispace_pal_entries(s);
    HBITMAP bm = 0;
    IspaceDib out;
    Planes pl;
    long stride, x, y;

    if (alloc_planes(&pl, n) && new_dib(&out, 2 * n, &stride)) {
        uint8_t *bits = out.data + 40 + 4 * 256;

        draw_group(&pl, im, n, 2, lum, ramp, g);
        draw_group(&pl, im, n, 3, lum, ramp, g);
        blur(&pl, 0);
        blur(&pl, 1);
        cut_corners(&pl, n);
        for (y = 0; y < pl.w; y++)
            for (x = 0; x < pl.w; x++)
                bits[y * stride + x] = final_pixel(&pl, y * pl.w + x, e);
        bm = ispace_dib_bitmap(&out, pal);
        free(out.data);
    }
    free_planes(&pl);
    return bm;
}

/* The bitmap of size w x h (w times DS:1ccc + 1 wide) with the image
 * stretched over w x h. */
static HBITMAP stretch(HBITMAP img, int16_t pal, int16_t size, int16_t w, int16_t h)
{
    HBITMAP bm = CreateCompatibleBitmap(ispace_dc(), (int16_t)(w * (*ispace_ds_1ccc() + 1)), h);
    HDC dc[2];
    HPALETTE old_pal[2];
    HGDIOBJ old[2];
    int i;

    for (i = 0; i < 2; i++) {
        dc[i] = CreateCompatibleDC(ispace_dc());
        old_pal[i] = SelectPalette(dc[i], pal, 0);
        old[i] = SelectObject(dc[i], i ? img : bm);
    }
    SetStretchBltMode(dc[0], COLORONCOLOR);
    StretchBlt(dc[0], 0, 0, w, h, dc[1], 0, 0, size, size, SRCCOPY);
    for (i = 1; i >= 0; i--) {
        if (old_pal[i])
            SelectPalette(dc[i], old_pal[i], 0);
        SelectObject(dc[i], old[i]);
        DeleteDC(dc[i]);
    }
    DeleteObject(img);
    return bm;
}

/* 7:12d8.  w, h: the bitmap's size (negative: in image heights); g == 1
 * shades lighter; c == 0 clears DS:1ccc; a, b: colour sets of colours
 * 0-9 and 10-14. */
static int16_t smooth(int16_t pal, int16_t id, int16_t w, int16_t h, int16_t g, int16_t c,
                      signed char a, signed char b)
{
    int s = ispace_pal_slot(pal), n;
    IspaceImgFlags *f = ispace_img_flags();
    IspaceDib src;
    Image im;
    int16_t lum[15], ramp[15];
    HBITMAP bm = 0, img;

    if (s < 0 || !pal)
        return 0;
    if (c == 0)
        *ispace_ds_1ccc() = 0;
    f->ds_0188 = 1;
    if (!ispace_dib_load(pal, id, "", 0, a, b, ispace_pal_fixed(s) != 0, &src))
        return 0;
    if (f->ds_1ea8 || ispace_pal_bits() < 8 || src.data[14] != 4) {
        not_ported(f->ds_1ea8 ? "ispace smooth: VGA colours (6:7fc8)" : "ispace smooth: not 4-bit, 8-bit");
        free(src.data);
        return 0;
    }
    n = (int16_t)(src.data[8] | src.data[9] << 8);
    im.bits = ispace_dib_bits(&src);
    im.size = (long)(src.data + src.size - im.bits);
    im.stride = ((int16_t)(src.data[4] | src.data[5] << 8) + 1) / 2;
    im.stride += im.stride % 4 ? 4 - im.stride % 4 : 0;
    ispace_set_image_height((int16_t)n);
    if (w < 0) {
        w = (int16_t)-(n * w);
        h = (int16_t)-(n * h);
    }
    if (f->ds_1eaa)
        a = 100;
    if (f->ds_1eac)
        b = 100;
    group_ramps(s, &src, 0, 10, a, lum, ramp);
    group_ramps(s, &src, 10, 15, b, lum, ramp);
    if (n > 0 && (img = render(s, pal, &im, n, lum, ramp, g)) != 0)
        bm = stretch(img, pal, (int16_t)(2 * n), w, h);
    free(src.data);
    ispace_pal_animate(pal, 0, ispace_dc());
    return (int16_t)bm;
}

int16_t ispace_smooth_image(int16_t pal, int16_t id, int32_t name, int16_t dc, int16_t w,
                            int16_t h, int16_t g, int16_t c, int16_t i, char a, char b)
{
    (void)name;
    (void)i;
    ispace_set_dc(dc);
    ispace_img_flags()->ds_1ea4 = 0;
    if ((uint8_t)a == 0xff || (uint8_t)b == 0xff)
        return 0;
    return smooth(pal, id, w, h, g, c, (signed char)a, (signed char)b);
}
