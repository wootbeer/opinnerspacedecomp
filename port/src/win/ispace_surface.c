/* ISPACE.DLL ordinal 2's surfaces (6:011c): a 16-colour image, a strip
 * of frames each as wide as the image is high, drawn as ordinal 12 draws
 * an image (each pixel a 2x2 block of its lightness, colours 0-9 and
 * 10-14 as two groups shaded on palette ramps, corners cut), turned to
 * 4 or 16 angles in 22.5-degree steps and shaded at the image's size (or
 * 2 or 4 times it).  Each angle goes into a sheet of 16 cells with its
 * three quarter turns 4, 8 and 12 cells on; the frames are stacked.  The
 * game's ships and other objects in waves are cut from these sheets.
 *
 * Only the DLL's 8-bit display path is ported; fixed palettes and images
 * with VGA colours (6:7fc8) log themselves and give no bitmap. */
#include <stdlib.h>
#include <string.h>

#include "ispace.h"

#define BG 15                           /* background colour of the images */
#define BG_CODE 100                     /* block code of the background */
#define TAKEN 0x65                      /* added to the code of a corner taken from a neighbour */
#define OWN_COLORS 12                   /* colour set "the image's own" */
#define ANGLES 16
#define MAX_PLANES 48                   /* the DLL's tables of code planes (DS:1048) */
#define LIT 0x1e                        /* cells above this are turned */
#define DIM 0x1c                        /* cells below this may be gaps */

/* DS:011a, DS:013a: sine and minus cosine of 22.5-degree steps, x 512. */
static const int16_t sin512[ANGLES] = {0, 196, 362, 473, 512, 473, 362, 196,
                                       0, -196, -362, -473, -512, -473, -362, -196};
static const int16_t mcos512[ANGLES] = {-512, -473, -362, -196, 0, 196, 362, 473,
                                        512, 473, 362, 196, 0, -196, -362, -473};

static int16_t ds_1ccc;

int16_t *ispace_ds_1ccc(void)
{
    return &ds_1ccc;
}

static void not_ported(const char *what)
{
    win_stub(what);
}

/* 5:6f58: the set id of colour set k; -1 for set 12 and others (the DLL
 * returns an uninitialised word). */
static int16_t id_of_set(int k)
{
    static const int8_t id[18] = {2, 5, 13, 6, 1, 7, 12, 8, 0, 0, 4, 4, -1, 10, 11, 3, 2, 9};

    return k >= 0 && k < 18 ? id[k] : -1;
}

static int16_t shl16(int x, int j)
{
    return (int16_t)(j < 16 ? (uint16_t)((uint16_t)x << j) : 0);
}

/* A 16-bit value shifted right 9 places, rounding down (sar). */
static int16_t asr9(int16_t v)
{
    return (int16_t)(v >= 0 ? v / 512 : -((511 - v) / 512));
}

/* The lightness of a palette entry as 6:011c works it out for the ends
 * of a ramp: group 1's root starts from half the mean and takes six
 * Newton steps (two calls of 6:7f52). */
static int16_t entry_lum(const PALETTEENTRY *e, int group)
{
    int32_t r = e->peRed - (e->peRed >> 2), g = e->peGreen, b = e->peBlue >> 1;
    int32_t sq = (r * r + g * g + b * b) / 3;

    if (!group)
        return ispace_lum(e->peRed, e->peGreen, e->peBlue);
    return ispace_newton_root(sq, ispace_newton_root(sq, (int16_t)((r + g + b) / 6)));
}

/* A ramp for set id: the set into the palette (5:61b2), then the range
 * it has; no range gives entry 0 (the DLL reads before the table). */
static void new_ramp(int s, int group, IspaceRamp *rp, int16_t id)
{
    const PALETTEENTRY *e = ispace_pal_entries(s);
    const int16_t *range;

    ispace_pal_load_set(s, id);
    range = ispace_pal_range(s, ispace_pal_set_range(s, id));
    rp->first = range ? (int16_t)(range[0] / 4) : 0;
    rp->last = range ? (int16_t)(range[1] / 4) : 0;
    rp->lum_first = entry_lum(&e[rp->first & 0xff], group);
    rp->lum_last = entry_lum(&e[rp->last & 0xff], group);
}

/* Lightness and ramp of the colours of a group (0: colours 0-9, which
 * count 5 lighter; 1: colours 10-14).  The image's own colours (set 12)
 * get a ramp per hue met (5:66ea), any other set one ramp (set_id). */
static void group_ramps(int s, int group, signed char set, int16_t set_id, int16_t lum[16],
                        int16_t ramp[16])
{
    const uint8_t *t = ispace_image_colors();
    IspaceRamp *rp = ispace_ramps(group);
    int16_t ids[10], count = 0, id, r, k;
    int c, from = group ? 10 : 0, to = group ? 15 : 10;

    for (c = from; c < to; c++) {
        const uint8_t *rgb = t + 4 * c;

        r = -1;
        if (set == OWN_COLORS) {
            id = ispace_set_of_color(rgb[0], rgb[1], rgb[2]);
            for (k = 0; k < count && r < 0; k++)
                if (ids[k] == id)
                    r = k;
        } else {
            id = set_id;
            if (c > from)
                r = 0;
        }
        if (r < 0) {
            ids[count] = id;
            new_ramp(s, group, &rp[count], id);
            r = count++;
        }
        lum[c] = (int16_t)(ispace_lum_image(rgb[0], rgb[1], rgb[2]) + (group ? 0 : 5));
        ramp[c] = r;
    }
}

/* The source image: 4-bit pixels, rows bottom-up as stored. */
typedef struct {
    const uint8_t *bits;
    long size, stride;
} Image;

static int pixel(const Image *im, int x, int y)
{
    long o = y * im->stride + x / 2;
    int byte = o >= 0 && o < im->size ? im->bits[o] : 0xff;

    return x & 1 ? byte & 15 : byte >> 4;
}

/* The working planes, (2n)^2 bytes each: per frame and angle a shade
 * plane per group (DS:0ec8) and a code plane (DS:1048: the block's ramp
 * * 2 + group, BG_CODE for the background).  Angle 0 is drawn, the others
 * are turned from it. */
typedef struct {
    int n, angles;
    long w, size;
    uint8_t **shade, **code;
    int nshade, ncode;
} Planes;

static uint8_t *shade_plane(const Planes *pl, int f, int a, int group)
{
    return pl->shade[(f * pl->angles + a) * 2 + group];
}

static uint8_t *code_plane(const Planes *pl, int f, int a)
{
    return pl->code[f * pl->angles + a];
}

static int alloc_planes(Planes *pl, int n, int frames, int angles)
{
    int k, ok = 1;

    pl->n = n;
    pl->angles = angles;
    pl->w = 2L * n;
    pl->size = pl->w * pl->w;
    pl->nshade = 2 * frames * angles;
    pl->ncode = frames * angles;
    pl->shade = calloc((size_t)pl->nshade + 1, sizeof *pl->shade);
    pl->code = calloc((size_t)pl->ncode + 1, sizeof *pl->code);
    if (!pl->shade || !pl->code)
        return 0;
    for (k = 0; k < pl->nshade; k++)
        ok &= (pl->shade[k] = calloc((size_t)pl->size, 1)) != NULL;
    for (k = 0; k < pl->ncode; k++)
        ok &= (pl->code[k] = calloc((size_t)pl->size, 1)) != NULL;
    return ok;
}

static void free_planes(Planes *pl)
{
    int k;

    for (k = 0; pl->shade && k < pl->nshade; k++)
        free(pl->shade[k]);
    for (k = 0; pl->code && k < pl->ncode; k++)
        free(pl->code[k]);
    free(pl->shade);
    free(pl->code);
}

static void fill_block(uint8_t *p, long o, long w, uint8_t v)
{
    p[o] = p[o + 1] = p[o + w] = p[o + w + 1] = v;
}

static void add(uint8_t *p, long o, uint8_t v)
{
    p[o] = (uint8_t)(p[o] + v);
}

/* One group of a frame (as ordinal 12's passes 2 and 3): each pixel of
 * the group becomes a block of half its lightness with the block's code;
 * corners next to the other group gain, the facing cells of neighbouring
 * blocks of the group gain a quarter.  Background pixels mark their
 * blocks.  The frame starts at column x0 + skip; with skip 1 (a frame
 * starting on an odd column) block x shows pixel x0 + x [sic: one block
 * right, the frame's last column left out]. */
static void draw_group(const Planes *pl, int f, int group, const Image *im, int x0, int skip,
                       const int16_t lum[16], const int16_t ramp[16])
{
    /* neighbours up, down, left, right */
    static const int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
    uint8_t *e = shade_plane(pl, f, 0, group), *code = code_plane(pl, f, 0);
    long w = pl->w, near[4][2] = {{-w, -w + 1}, {2 * w, 2 * w + 1}, {-1, w - 1}, {2, w + 2}};
    int n = pl->n, x, y, k;

    for (y = 0; y < n; y++)
        for (x = skip; x < n; x++) {
            long o = 2 * y * w + 2 * x;
            int c = pixel(im, x0 + x, y), stop[4], other[4];
            uint8_t full, part;

            if (c == BG) {
                fill_block(code, o, w, BG_CODE);
                continue;
            }
            full = (uint8_t)(lum[c] >> 1);
            part = (uint8_t)(lum[c] >> 2);
            if ((c >= 10) != group || full == 0)
                continue;
            for (k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k], nc;

                stop[k] = 1;
                other[k] = 0;
                if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                    continue;
                nc = pixel(im, x0 + nx, ny);
                stop[k] = nc == BG || (nc >= 10) != (c >= 10);
                other[k] = stop[k] && nc != BG;
            }
            fill_block(code, o, w, (uint8_t)(ramp[c] * 2 + group));
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

/* A block's group for the corner pass: 0, 1 or 2 (background). */
static int block_group(const uint8_t *code, long o)
{
    return code[o] == BG_CODE ? 2 : code[o] & 1;
}

/* Cell t takes group side's shade and code from cell from. */
static void take(uint8_t *shade[2], uint8_t *code, long t, int side, long from)
{
    shade[1][t] = 0;
    shade[0][t] = 0;
    if (side == 2)
        return;
    shade[side][t] = shade[side][from];
    code[t] = (uint8_t)(code[from] + TAKEN);
}

/* Corners where a block meets two blocks of another group (and, for a
 * group-0 block, a third such block diagonally) take that group's
 * neighbouring cell.  Frame f's corners are cut on the planes of index
 * f, not the frame's [sic: with several angles, for f > 0 planes still
 * empty unless f is a multiple of the angles]. */
static void cut_corners(const Planes *pl, int f)
{
    uint8_t *shade[2] = {pl->shade[2 * f], pl->shade[2 * f + 1]}, *code = pl->code[f];
    long w = pl->w;
    int n = pl->n, r, x;

    for (r = 2; r < n - 2; r++)
        for (x = 2; x < n - 2; x++) {
            long o = 2 * r * w + 2 * x;
            int cur = block_group(code, o), left = block_group(code, o - 2), up = block_group(code, o - 2 * w);
            int right = block_group(code, o + 2), down = block_group(code, o + 2 * w);

            if (left != cur) {
                if (up == left && (cur || (code[o + 2 * w - 2] & 1) == left))
                    take(shade, code, o, left, o - w);
                if (down == left && (cur || (code[o - 2 * w - 2] & 1) == left))
                    take(shade, code, o + w, left, o + 2 * w);
            }
            if (right != cur) {
                if (up == right && (cur || (code[o + 2 * w + 2] & 1) == right))
                    take(shade, code, o + 1, right, o - w + 1);
                if (down == right && (cur || (code[o - 2 * w + 2] & 1) == right))
                    take(shade, code, o + w + 1, right, o + 2 * w + 1);
            }
        }
}

/* Angle a of frame f: each cell of angle 0 lit above LIT goes to its
 * place turned about the centre (rounded down: the DLL's rounding terms
 * are cleared before use), with its code. */
static void turn(const Planes *pl, int f, int a)
{
    const uint8_t *code = code_plane(pl, f, 0);
    uint8_t *to_code = code_plane(pl, f, a);
    int16_t n = (int16_t)pl->n, w = (int16_t)pl->w, x, y, tx, ty, dx, dy;
    int group;

    for (group = 0; group < 2; group++) {
        const uint8_t *s = shade_plane(pl, f, 0, group);
        uint8_t *d = shade_plane(pl, f, a, group);

        for (y = 0; y < w; y++)
            for (x = 0; x < w; x++) {
                long o = (long)y * w + x, t;

                if (s[o] <= LIT)
                    continue;
                dx = (int16_t)(n - x);
                dy = (int16_t)(n - y);
                tx = (int16_t)(asr9((int16_t)(mcos512[a] * dx - sin512[a] * dy)) + n);
                ty = (int16_t)(asr9((int16_t)(mcos512[a] * dy + sin512[a] * dx)) + n);
                if (tx < 0 || tx >= w || ty < 0 || ty >= w)
                    continue;
                t = (long)ty * w + tx;
                d[t] = s[o];
                to_code[t] = code[o];
            }
    }
}

/* A dim cell of a turned angle between two lit cells in its row takes
 * the shade and code of the one on its left (the group lit there first). */
static void close_gaps(const Planes *pl, int f, int a)
{
    uint8_t *s[2] = {shade_plane(pl, f, a, 0), shade_plane(pl, f, a, 1)}, *code = code_plane(pl, f, a);
    long w = pl->w, x, y;

    for (y = 1; y < w - 1; y++)
        for (x = 1; x < w - 1; x++) {
            long o = y * w + x;
            int left, right;

            if (s[0][o] >= DIM || s[1][o] >= DIM)
                continue;
            left = s[0][o - 1] ? 1 : s[1][o - 1] ? 2 : 0;
            right = s[0][o + 1] ? 1 : s[1][o + 1] ? 2 : 0;
            if (!left || !right)
                continue;
            s[left - 1][o] = s[left - 1][o - 1];
            code[o] = code[o - 1];
        }
}

/* A frame's sheet: an 8-bit DIB (rows bottom-up), cells of size cell
 * (the image height << j) pitch apart from base. */
typedef struct {
    IspaceDib dib;
    uint8_t *bits;
    long size, stride, base, pitch, cell;
} Sheet;

static void put(Sheet *sh, long o, uint8_t v)
{
    if (o >= 0 && o < sh->size)
        sh->bits[o] = v;
}

static uint8_t at(const Planes *pl, const uint8_t *p, long o)
{
    return o >= 0 && o < pl->size ? p[o] : 0;
}

/* One group of angle a of frame f into the sheet: at j 0 each pixel is
 * the mean of the lit cells of a 2x2 block (two at least; the code of
 * the last), at j 1 or 2 one cell, shaded on the block's ramp; with
 * several angles also turned a quarter, half and three quarters round
 * into cells a + 4, a + 8, a + 12.  At j 2 a row's cells step half a
 * plane row [sic]. */
static void shade_group(const Planes *pl, int f, int a, int group, int j, Sheet *sh, const PALETTEENTRY *e)
{
    const uint8_t *s = shade_plane(pl, f, a, group), *code = code_plane(pl, f, a);
    const long w = pl->w, cs = sh->cell, d[4] = {0, 1, w, w + 1};
    int16_t step = (int16_t)((int16_t)(2 * w) >> j);
    long row = 0, x, y;

    for (y = 0; y < cs; y++, row += step)
        for (x = 0; x < cs; x++) {
            long o = row + ((int16_t)(2 * x) >> j);
            int k = 0, count = 4, sum = 0, i;
            uint8_t v, out;

            if (j) {
                v = at(pl, s, o);
                k = at(pl, code, o);
            } else {
                for (count = 0, i = 0; i < 4; i++)
                    if (at(pl, s, o + d[i])) {
                        sum += at(pl, s, o + d[i]);
                        k = at(pl, code, o + d[i]);
                        count++;
                    }
                v = (uint8_t)(count ? sum / count : 0);
            }
            if (!v || count <= 1 || k == BG_CODE)
                continue;
            if (k > BG_CODE)
                k -= TAKEN;
            if ((k & 1) != group)
                k = group;
            out = k >> 1 < (group ? 5 : 10) ? ispace_ramp_shade(e, &ispace_ramps(group)[k >> 1], v) : 0;
            put(sh, a * sh->pitch + y * sh->stride + x + sh->base, out);
            if (pl->angles == 1)
                continue;
            put(sh, (cs - y - 1) * sh->stride + (a + 8) * sh->pitch - x + cs + sh->base - 1, out);
            put(sh, (cs - x - 1) * sh->stride + (a + 4) * sh->pitch + y + sh->base, out);
            put(sh, (a + 12) * sh->pitch + x * sh->stride - y + cs + sh->base - 1, out);
        }
}

/* Frame f's sheet (16 cells of angles, F apart; one cell for one angle)
 * as a bitmap. */
static HBITMAP frame_bitmap(const Planes *pl, int f, int16_t pal, int16_t sf, int j)
{
    int16_t n = (int16_t)pl->n, w, h;
    Sheet sh;
    HBITMAP bm;
    int a, group;

    if (pl->angles == 1)
        w = h = shl16(n, j);
    else {
        w = shl16(n * 16 + sf * 17, j);
        h = shl16(sf * 2 + n, j);
    }
    if (!ispace_dib8_new(w, h, &sh.dib))
        return 0;
    sh.bits = sh.dib.data + 40 + 1024;
    sh.size = (long)sh.dib.size - 40 - 1024;
    sh.stride = (w + 3) & ~3;
    sh.base = (long)((unsigned long)((long)sf * sh.stride) << j) + shl16(sf, j);
    sh.pitch = shl16(n + sf, j);
    sh.cell = shl16(n, j);
    for (a = 0; a < pl->angles; a++)
        for (group = 0; group < 2; group++)
            shade_group(pl, f, a, group, j, &sh, ispace_pal_entries(ispace_pal_slot(pal)));
    bm = ispace_dib_bitmap(&sh.dib, pal);
    free(sh.dib.data);
    return bm;
}

/* The sheets of all frames stacked (n + F apart) into one bitmap, F
 * black around the cells, m == 1 one cell wider. */
static HBITMAP stack(const Planes *pl, int frames, int used, int16_t pal, int16_t dc, int16_t sf, int j,
                     signed char m)
{
    int16_t n = (int16_t)pl->n, bw, bh, fw, fh;
    HDC dst = CreateCompatibleDC(dc), src;
    HPALETTE old_pal[2] = {0, 0};
    HBITMAP bm, old, fbm, fold;
    int f;

    if (pl->angles == 1)
        bw = bh = fw = fh = shl16(n, j);
    else {
        bw = (int16_t)(shl16(n * 16 + sf * 17, j) + (m == 1 ? shl16(n + sf, j) : 0));
        bh = shl16((n + sf) * frames + sf, j);
        fw = shl16(n * 16 + sf * 17, j);
        fh = shl16(sf * 2 + n, j);
    }
    bm = CreateCompatibleBitmap(dc, bw, bh);
    old = SelectObject(dst, bm);
    if (pal)
        old_pal[0] = SelectPalette(dst, pal, 0);
    PatBlt(dst, 0, 0, bw, bh, BLACKNESS);
    src = CreateCompatibleDC(dc);
    if (pal)
        old_pal[1] = SelectPalette(src, pal, 0);
    for (f = 0; f < used; f++) {
        if (!(fbm = frame_bitmap(pl, f, pal, sf, j)))
            continue;
        fold = SelectObject(src, fbm);
        BitBlt(dst, 0, pl->angles == 1 ? 0 : shl16((n + sf) * f, j), fw, fh, src, 0, 0, SRCCOPY);
        SelectObject(src, fold);
        DeleteObject(fbm);
    }
    if (pal) {
        SelectPalette(src, old_pal[1], 0);
        SelectPalette(dst, old_pal[0], 0);
    }
    SelectObject(dst, old);
    DeleteDC(dst);
    DeleteDC(src);
    return bm;
}

/* 6:011c.  f: black around the cells (99: 5 for an odd image height, 6
 * for an even one; -100: one angle, nothing around); i: 4 angles (16
 * when 0); j: the sheet 2^j times the image's size; k, l: colour sets of
 * colours 0-9 and 10-14; m == 1: only the first two frames, the sheet a
 * cell wider. */
int16_t ispace_surface(int16_t pal, int16_t id, LPCSTR name, int16_t dc, int16_t f, int16_t i,
                       int16_t j, signed char k, signed char l, signed char m)
{
    int s = ispace_pal_slot(pal), frames, used, angles, x0, fr, a;
    IspaceImgFlags *flags = ispace_img_flags();
    int16_t n, set_a = 0, set_b = 0, lum[16], ramp[16], start;
    IspaceDib src;
    Planes pl;
    Image im;
    HBITMAP bm = 0;

    if (s < 0)
        return 0;
    ispace_set_dc(dc);
    if (ispace_pal_fixed(s)) {
        not_ported("ispace surface: fixed palette (6:011c)");
        return 0;
    }
    if (k != OWN_COLORS)
        ispace_pal_load_set(s, set_a = id_of_set(k));
    if (l != OWN_COLORS)
        ispace_pal_load_set(s, set_b = id_of_set(l));
    flags->ds_0188 = 1;
    if (!ispace_dib_load(pal, id, name, 1, k, l, 0, &src))
        return 0;
    if (flags->ds_1ea8 || ispace_pal_bits() < 8 || src.data[14] != 4) {
        not_ported(flags->ds_1ea8 ? "ispace surface: VGA colours (6:7fc8)" : "ispace surface: not 4-bit, 8-bit");
        free(src.data);
        return 0;
    }
    n = (int16_t)(src.data[8] | src.data[9] << 8);
    frames = (int16_t)(src.data[4] | src.data[5] << 8) / n;
    ispace_set_image_height(n);
    if (f == 99)
        f = n & 1 ? 5 : 6;
    used = m == 1 && frames > 1 ? 2 : frames;
    if (f == -100) {
        angles = 1;
        f = 0;
    } else {
        angles = i ? 4 : ANGLES;
    }
    ds_1ccc = (int16_t)angles;
    if (used * angles > MAX_PLANES) {
        free(src.data);
        return 0;   /* the DLL writes past its tables of planes */
    }
    group_ramps(s, 0, k, set_a, lum, ramp);
    group_ramps(s, 1, l, set_b, lum, ramp);
    im.bits = ispace_dib_bits(&src);
    im.size = (long)(src.data + src.size - im.bits);
    im.stride = ((int16_t)(src.data[4] | src.data[5] << 8) + 1) / 2;
    im.stride += im.stride % 4 ? 4 - im.stride % 4 : 0;
    if (alloc_planes(&pl, n, used, angles)) {
        for (fr = 0; fr < used; fr++) {
            /* with m == 1 the second frame is the image's last */
            start = (int16_t)((fr == 0 || used == frames ? fr : frames - 1) * n);
            x0 = start / 2 * 2;
            draw_group(&pl, fr, 0, &im, x0, start & 1, lum, ramp);
            draw_group(&pl, fr, 1, &im, x0, start & 1, lum, ramp);
            cut_corners(&pl, fr);
        }
        for (fr = 0; fr < used; fr++)
            for (a = 1; a < angles; a++)
                turn(&pl, fr, a);
        for (fr = 0; fr < used; fr++)
            for (a = 1; a < angles; a++)
                close_gaps(&pl, fr, a);
        bm = stack(&pl, frames, used, pal, dc, f, j & 31, m);
    }
    free_planes(&pl);
    free(src.data);
    ispace_pal_animate(pal, 0, ispace_dc());
    return (int16_t)bm;
}
