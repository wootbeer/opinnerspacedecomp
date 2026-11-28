/* ISPACE.DLL's quick drawing (6:5538): a ship or object turned pixel by
 * pixel, without shading.  Ordinal 17 draws one angle of it into the
 * caller's sprite sheet (the cloak's frames, 11:4b00); ordinal 2 with
 * its n word set (INSPACE.INI Quick) makes the 16 angles of a surface
 * this way instead of 6:011c's (6:78ba).
 *
 * The image (a strip of square frames of 16 colours, 15 the background)
 * is loaded in mode 3 with each colour's palette entry worked out
 * (ispace_image_entries).  Each frame is turned to the angle by 22.5
 * degree steps (DS:011a sine, DS:013a minus cosine, x 512) into a cell
 * of h + border pixels; at angles 2, 6, 10 and 14 single gaps in a row
 * take the colour on their left.  Buffers are DIBs laid out as the
 * DLL's (rows bottom up, padded to 4 bytes).  Only the 8-bit display
 * path is ported: fixed palettes and images with VGA colours (6:7fc8)
 * log themselves and give no bitmap. */
#include <stdlib.h>
#include <string.h>

#include "ispace.h"

#define ANGLES 16
#define BG 15                           /* background colour of the images */
#define OWN_COLORS 12                   /* colour set "the image's own" */

static const int16_t sin512[ANGLES] = {0, 196, 362, 473, 512, 473, 362, 196,
                                       0, -196, -362, -473, -512, -473, -362, -196};
static const int16_t mcos512[ANGLES] = {-512, -473, -362, -196, 0, 196, 362, 473,
                                        512, 473, 362, 196, 0, -196, -362, -473};

static void not_ported(const char *what)
{
    win_stub(what);
}

static int16_t stride_of(int16_t n)
{
    return (int16_t)(n + (n % 4 ? 4 - n % 4 : 0));
}

/* (v + 256) >> 9 on a 16-bit value: the turn rounded. */
static int16_t round512(int16_t v)
{
    int16_t t = (int16_t)(v + 0x100);

    return (int16_t)(t >= 0 ? t / 512 : -((511 - t) / 512));
}

typedef struct {
    const uint8_t *bits;                /* the image, 4 bits a pixel */
    long size;
    int16_t stride, h;
} Image;

typedef struct {
    uint8_t *bits;                      /* the picture, 8 bits a pixel */
    long size, stride;
    int16_t border;
} Sheet;

/* Frame src (start: its first byte of each row, odd: it starts on a
 * pixel's low half) turned to angle into the cell at offset base. */
static void turn(const Image *im, long start, int odd, int16_t angle, Sheet *sh, long base)
{
    const uint8_t *entry = ispace_image_entries()->ds_1484;
    int16_t h = im->h, c = (int16_t)(h / 2), m = sh->border, x, y, tx, ty;
    long row = start, src, dst;
    uint8_t v;

    for (y = 0; y < h; y++, row += im->stride)
        for (x = odd; x < h; x++) {
            src = row + x / 2;
            if (src < 0 || src >= im->size)
                continue;
            v = (uint8_t)(x & 1 ? im->bits[src] & 15 : im->bits[src] >> 4);
            if (v == BG)
                continue;
            tx = (int16_t)(round512((int16_t)((y - c) * sin512[angle] + (c - x) * mcos512[angle])) + c + m);
            ty = (int16_t)(round512((int16_t)((c - y) * mcos512[angle] + (c - x) * sin512[angle])) + c + m);
            dst = (long)ty * sh->stride + tx + base;
            if (tx >= m && tx < h + m && ty >= m && ty < h + m && dst >= 0 && dst < sh->size)
                sh->bits[dst] = entry[v];
        }
}

/* Single gaps in the cell's rows take the colour on their left: rows
 * from the cell's first, not its border's [sic], columns past the
 * border. */
static void close_gaps(Sheet *sh, int16_t h, long base)
{
    int16_t m = sh->border, r, col;
    long i;

    for (r = m; r < h + m; r++, base += sh->stride)
        for (col = m; col < h + m; col++) {
            i = base + col;
            if (i < 1 || i + 1 >= sh->size)
                continue;
            if (!sh->bits[i] && sh->bits[i - 1] && sh->bits[i + 1])
                sh->bits[i] = sh->bits[i - 1];
        }
}

/* 6:5538: image id with colour sets cs1 (colours 0-9) and cs2 (10-14).
 * angle -1 makes 16 angles side by side, each frame a row (two frames
 * with two 1: the last and the first, a cell wider), and returns that
 * bitmap; another angle one cell.  With hdc that cell is drawn twice,
 * from the image's frames 1 and 2 [inferred: the cloak's], at
 * (16 h + 17 border, (h + border) * k + border) in hdc, scale/2 times
 * its size, and the bitmap is deleted. */
static int16_t quick_draw(int16_t pal, int16_t id, LPCSTR name, int16_t dc, int16_t border, signed char cs1,
                          signed char cs2, int16_t angle, int16_t hdc, signed char two, signed char scale)
{
    int s = ispace_pal_slot(pal);
    int16_t passes = angle == -1 ? ANGLES : hdc ? 2 : 1, cells = passes == ANGLES ? ANGLES : 1;
    int16_t w = 0, h = 0, frames = 0, rows = 1, pass, fr, src_fr;
    IspaceEntries *e = ispace_image_entries();
    IspaceImgFlags *flags = ispace_img_flags();
    IspaceDib img, out = {NULL, 0};
    Image im = {0};
    Sheet sh = {0};
    HBITMAP bm = 0;

    if (s < 0)
        return 0;
    if (ispace_pal_fixed(s) || ispace_pal_bits() < 8) {
        not_ported("ispace quick drawing: fixed palette or fewer colours (6:5538)");
        return 0;
    }
    if (cs1 != OWN_COLORS)
        ispace_pal_load_set(s, e->ds_147c = ispace_set_id(cs1));
    if (cs2 != OWN_COLORS)
        ispace_pal_load_set(s, e->ds_1480 = ispace_set_id(cs2));
    e->ds_015c = 1;
    flags->ds_0188 = 1;
    if (!ispace_dib_load(pal, id, name, 3, cs1, cs2, 0, &img))
        return 0;
    if (flags->ds_1ea8 || img.data[14] != 4) {
        not_ported(flags->ds_1ea8 ? "ispace quick drawing: VGA colours (6:7fc8)" : "ispace quick drawing: not 4-bit");
        free(img.data);
        return 0;
    }
    im.bits = ispace_dib_bits(&img);
    im.size = (long)(img.data + img.size - im.bits);
    sh.bits = NULL;
    for (pass = 0; pass < passes; pass++) {
        if (cells >= ANGLES)
            angle = pass;
        if (cells == 1 || pass == 0) {
            w = (int16_t)(img.data[4] | img.data[5] << 8);
            h = im.h = (int16_t)(img.data[8] | img.data[9] << 8);
            frames = rows = (int16_t)(w / h);
            ispace_set_image_height(h);
            if (border == 0x63)
                border = h & 1 ? 5 : 6;
            if (two == 1 && frames > 1 && cells == ANGLES) {
                rows = 2;
                cells = ANGLES + 1;
            }
            if (cells < ANGLES)
                frames = rows = 1;
            if (!ispace_dib8_new((int16_t)((h + border) * cells + border), (int16_t)((h + border) * rows + border),
                                 &out))
                break;
            sh.bits = out.data + 40 + 1024;
            sh.size = (long)(out.size - 40 - 1024);
            sh.stride = stride_of((int16_t)((h + border) * cells + border));
            sh.border = border;
            im.stride = stride_of((int16_t)((w + 1) / 2));
        }
        if (angle < 0 || angle >= ANGLES)
            angle = 0;      /* [fix: the DLL reads past its tables] */
        for (fr = 0; fr < rows; fr++) {
            long base = cells >= ANGLES ? (long)(h + border) * pass + (long)fr * sh.stride * (h + border) : 0;
            long start = hdc ? (long)(h / 2) * (pass + 1) : 0;
            int odd = hdc ? ((pass + 1) * h) & 1 : 0;
            src_fr = cells < ANGLES ? 0 : rows == frames ? frames - 1 - fr : fr == 0 ? frames - 1 : 0;
            if (!hdc)
                odd = (src_fr * h) & 1;
            turn(&im, start + (long)(src_fr * h) / 2, odd, angle, &sh, base);
            if ((angle & 3) == 2)
                close_gaps(&sh, h, base);
        }
        if (pass != ANGLES - 1 && cells != 1)
            continue;
        bm = ispace_dib_bitmap(&out, pal);
        free(out.data);
        out.data = NULL;
        if (hdc) {
            HDC mdc = CreateCompatibleDC((HDC)dc);
            HPALETTE old_pal = pal ? SelectPalette(mdc, (HPALETTE)pal, 0) : 0;
            HBITMAP old = SelectObject(mdc, bm);
            int16_t x = (int16_t)(h * 16 + border * 17), y = (int16_t)((h + border) * pass + border);
            if (scale == 1)
                BitBlt((HDC)hdc, x, y, h, h, mdc, border, border, SRCCOPY);
            else
                StretchBlt((HDC)hdc, (int16_t)((int16_t)(x << scale) >> 1), (int16_t)((int16_t)(y << scale) >> 1),
                           (int16_t)((int16_t)(h << scale) >> 1), (int16_t)((int16_t)(h << scale) >> 1), mdc,
                           border, border, h, h, SRCCOPY);
            if (pal)
                SelectPalette(mdc, old_pal, 0);
            SelectObject(mdc, old);
            DeleteDC(mdc);
            DeleteObject(bm);
        }
    }
    free(out.data);
    free(img.data);
    return (int16_t)bm;
}

/* Ordinal 17 (6:5538). */
int16_t ispace_quick_draw(int16_t pal, int16_t id, char *name, int16_t dc, int16_t border, int16_t c,
                          int16_t d, char cs1, char cs2, int16_t angle, int16_t hdc, char two, char scale)
{
    (void)name;
    (void)c;
    (void)d;
    return quick_draw(pal, id, "", dc, border, (signed char)cs1, (signed char)cs2, angle, hdc, (signed char)two,
                      (signed char)scale);
}

/* 6:78ba (ordinal 2 with n set): the colour sets of k and l into the
 * palette (for the image's own colours, set 12, the two set ids g and h
 * keep in their bytes, plus one), then the 16 angles of 6:5538. */
int16_t ispace_quick_surface(int16_t pal, int16_t id, int16_t dc, int16_t f, int16_t g, int16_t h, int16_t j,
                             signed char k, signed char l, signed char m)
{
    int s = ispace_pal_slot(pal), i;
    int16_t a[2], b[2];

    if (s >= 0 && !ispace_pal_fixed(s)) {
        a[0] = (int16_t)(k == OWN_COLORS ? (uint8_t)g - 1 : ispace_set_id(k));
        a[1] = (int16_t)(k == OWN_COLORS ? (uint8_t)(g >> 8) - 1 : -1);
        b[0] = (int16_t)(l == OWN_COLORS ? (uint8_t)h - 1 : ispace_set_id(l));
        b[1] = (int16_t)(l == OWN_COLORS ? (uint8_t)(h >> 8) - 1 : -1);
        for (i = 0; i < 2; i++) {
            ispace_pal_load_set(s, a[i]);
            ispace_pal_load_set(s, b[i]);
        }
    }
    return quick_draw(pal, id, "", dc, f, k, l, -1, 0, m, (signed char)(j ? 2 : 1));
}
