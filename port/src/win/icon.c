/* Icons: ExtractIcon reads them from the resources of Windows programs
 * (NE, 16-bit; PE, 32- and 64-bit), LoadIcon from the game's modules,
 * DrawIcon puts them on a DC as Windows does: the screen ANDed with the
 * mask, then XORed with the colours.  An icon is made 32x32 (SM_CXICON)
 * from the group's image nearest that size; its colours are matched to
 * the 20 static colours, as Windows 3.1 made icons for a 256-colour
 * display (port/NOTES-port.md, "Icons"). */
#include <SDL3/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gdi.h"

#define ICON_W 32
#define RES_ICON 3
#define RES_GROUP_ICON 14
#define MAX_RES (64u << 20)     /* larger resources are not read */

typedef struct {
    uint8_t keep[ICON_W * ICON_W];      /* AND mask: 1 keeps the screen */
    COLORREF color[ICON_W * ICON_W];    /* XORed after */
} Icon;

static unsigned u16(const uint8_t *p)
{
    return p[0] | p[1] << 8;
}

static uint32_t u32(const uint8_t *p)
{
    return p[0] | p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

/* Decoding.  dib is an icon image: a BITMAPINFOHEADER, colour table,
 * colour rows and mask rows, bottom-up, the height counting both. */
static HICON decode(const uint8_t *dib, uint32_t len)
{
    Icon *ic;
    uint32_t hsize, ncol, cstride, mstride, coff, moff;
    int32_t w, h;
    unsigned bpp;
    int x, y, alpha = 0;

    if (len < 40 || (hsize = u32(dib)) < 40 || hsize > len)
        return 0;
    w = (int32_t)u32(dib + 4);
    h = (int32_t)u32(dib + 8) / 2;
    bpp = u16(dib + 14);
    if (w <= 0 || h <= 0 || w > 1024 || h > 1024 || u32(dib + 16) != 0 ||
        (bpp != 1 && bpp != 4 && bpp != 8 && bpp != 24 && bpp != 32))
        return 0;
    ncol = bpp <= 8 ? (u32(dib + 32) && u32(dib + 32) < (1u << bpp) ? u32(dib + 32) : 1u << bpp) : 0;
    cstride = ((uint32_t)w * bpp + 31) / 32 * 4;
    mstride = ((uint32_t)w + 31) / 32 * 4;
    coff = hsize + ncol * 4;
    moff = coff + cstride * (uint32_t)h;
    if (moff > len)
        return 0;
    if (moff + mstride * (uint32_t)h > len && bpp != 32)
        return 0;
    if (bpp == 32)
        for (y = 0; y < h && !alpha; y++)
            for (x = 0; x < w; x++)
                alpha |= dib[coff + (uint32_t)y * cstride + (uint32_t)x * 4 + 3];
    ic = calloc(1, sizeof *ic);
    if (!ic)
        return 0;
    for (y = 0; y < ICON_W; y++) {
        uint32_t sy = (uint32_t)(h - 1 - y * h / ICON_W);
        const uint8_t *row = dib + coff + sy * cstride;
        for (x = 0; x < ICON_W; x++) {
            uint32_t sx = (uint32_t)(x * w / ICON_W);
            const uint8_t *c;
            int keep;
            if (bpp <= 8) {
                unsigned shift = 8 - bpp - (sx * bpp) % 8;
                unsigned k = (row[sx * bpp / 8] >> shift) & ((1u << bpp) - 1);
                c = dib + hsize + (k < ncol ? k : 0) * 4;
            } else {
                c = row + sx * (bpp / 8);
            }
            if (bpp == 32 && alpha)
                keep = c[3] < 128;
            else if (moff + mstride * (uint32_t)h <= len)
                keep = dib[moff + sy * mstride + sx / 8] >> (7 - sx % 8) & 1;
            else
                keep = 0;
            ic->keep[y * ICON_W + x] = (uint8_t)keep;
            ic->color[y * ICON_W + x] = keep && bpp == 32 && alpha ? 0 : RGB(c[2], c[1], c[0]);
        }
    }
    return handle_new(H_ICON, ic);
}

/* The image of a group (GRPICONDIR) Windows 3.1 would take [inferred]:
 * 32x32 if there is one, else the nearest size, larger first; then the
 * most colours up to 256, else the fewest above.  Returns the entry. */
static int choose(const uint8_t *grp, uint32_t len)
{
    unsigned n = len >= 6 ? u16(grp + 4) : 0, i;
    int best = -1, bscore = 0;

    for (i = 0; i < n && 6 + 14 * (i + 1) <= len; i++) {
        const uint8_t *e = grp + 6 + 14 * i;
        int w = e[0] ? e[0] : 256, bits = u16(e + 6), size, depth, score;
        if (!bits)
            bits = e[2] == 2 ? 1 : e[2] == 16 ? 4 : 8;
        size = w == ICON_W ? 0 : w > ICON_W ? w - ICON_W : 2 * (ICON_W - w);
        depth = bits <= 8 ? 8 - bits : bits;
        score = size * 64 + depth;
        if (best < 0 || score < bscore) {
            best = (int)i;
            bscore = score;
        }
    }
    return best;
}

/* Resources of a file on disk. */
typedef struct {
    FILE *fp;
    uint32_t size;
    int pe;
    uint8_t *table;             /* NE resource table */
    uint32_t table_len;
    uint32_t rsrc;              /* PE: file offset of the resource section */
    uint32_t rsrc_rva, rsrc_len;
} ResFile;

static int rd(const ResFile *f, uint32_t off, void *buf, uint32_t n)
{
    return off <= f->size && n <= f->size - off && fseek(f->fp, (long)off, SEEK_SET) == 0 &&
           fread(buf, 1, n, f->fp) == n;
}

static uint8_t *rd_alloc(const ResFile *f, uint32_t off, uint32_t n)
{
    uint8_t *p = n && n <= MAX_RES ? malloc(n) : NULL;

    if (p && !rd(f, off, p, n)) {
        free(p);
        p = NULL;
    }
    return p;
}

static int open_ne(ResFile *f, uint32_t ne)
{
    uint8_t h[0x40];

    if (!rd(f, ne, h, sizeof h) || u16(h + 0x26) <= u16(h + 0x24))
        return 0;
    f->table_len = u16(h + 0x26) - u16(h + 0x24);
    f->table = rd_alloc(f, ne + u16(h + 0x24), f->table_len);
    return f->table != NULL && f->table_len >= 2;
}

static int open_pe(ResFile *f, uint32_t pe)
{
    uint8_t h[24], opt[240], sec[40];
    unsigned nsec, optlen, i;
    uint32_t dirs, ndirs;

    if (!rd(f, pe, h, sizeof h))
        return 0;
    nsec = u16(h + 6);
    optlen = u16(h + 20);
    if (optlen > sizeof opt || optlen < 96 || !rd(f, pe + 24, opt, optlen))
        return 0;
    dirs = u16(opt) == 0x20b ? 112 : 96;
    ndirs = u32(opt + dirs - 4);
    if (ndirs < 3 || dirs + 24 > optlen)
        return 0;
    f->rsrc_rva = u32(opt + dirs + 16);
    f->rsrc_len = u32(opt + dirs + 20);
    for (i = 0; i < nsec && i < 96; i++) {
        uint32_t va, raw;
        if (!rd(f, pe + 24 + optlen + 40 * i, sec, sizeof sec))
            return 0;
        va = u32(sec + 12);
        raw = u32(sec + 20);
        if (f->rsrc_rva >= va && f->rsrc_rva < va + u32(sec + 16)) {
            f->rsrc = raw + (f->rsrc_rva - va);
            f->pe = 1;
            return 1;
        }
    }
    return 0;
}

/* 1 for a Windows program (NE or PE), 0 otherwise. */
static int res_open(ResFile *f, const char *path)
{
    uint8_t mz[0x40], sig[4];
    uint32_t hdr;
    int ok = 0;

    memset(f, 0, sizeof *f);
    f->fp = fopen(path, "rb");
    if (!f->fp)
        return 0;
    if (fseek(f->fp, 0, SEEK_END) == 0) {
        long n = ftell(f->fp);
        f->size = n > 0 && n < 0x7fffffffL ? (uint32_t)n : 0;
    }
    if (rd(f, 0, mz, sizeof mz) && mz[0] == 'M' && mz[1] == 'Z' && rd(f, hdr = u32(mz + 0x3c), sig, 4)) {
        if (sig[0] == 'N' && sig[1] == 'E')
            ok = open_ne(f, hdr);
        else if (!memcmp(sig, "PE\0\0", 4))
            ok = open_pe(f, hdr);
    }
    if (!ok) {
        free(f->table);
        fclose(f->fp);
        f->fp = NULL;
    }
    return ok;
}

static void res_close(ResFile *f)
{
    free(f->table);
    if (f->fp)
        fclose(f->fp);
}

/* NE: the index-th resource of a type (index >= 0), or the one with
 * id.  Returns the number of resources of the type. */
static int ne_find(const ResFile *f, unsigned type, int index, unsigned id, uint32_t *off, uint32_t *len)
{
    const uint8_t *t = f->table, *end = t + f->table_len;
    const uint8_t *p = t + 2;
    unsigned shift = u16(t);
    int n = 0;

    if (shift > 16)
        return 0;
    while (p + 8 <= end && u16(p)) {
        unsigned count = u16(p + 2), i, match = u16(p) == (0x8000 | type);
        p += 8;
        for (i = 0; i < count && p + 12 <= end; i++, p += 12) {
            if (!match)
                continue;
            if (index >= 0 ? n == index : u16(p + 6) == (0x8000 | id)) {
                *off = (uint32_t)u16(p) << shift;
                *len = (uint32_t)u16(p + 2) << shift;
            }
            n++;
        }
    }
    return n;
}

/* PE: a resource directory's entries (8 bytes each, named first). */
static uint8_t *pe_dir(const ResFile *f, uint32_t at, unsigned *n)
{
    uint8_t h[16];

    if (at >= f->rsrc_len || !rd(f, f->rsrc + at, h, sizeof h))
        return NULL;
    *n = u16(h + 12) + u16(h + 14);
    return rd_alloc(f, f->rsrc + at + 16, *n * 8);
}

static int pe_find(const ResFile *f, unsigned type, int index, unsigned id, uint32_t *off, uint32_t *len)
{
    uint8_t *types, *names = NULL, *langs = NULL, data[8];
    unsigned nt, nn = 0, nl, i;
    int found = 0, count;

    if (!(types = pe_dir(f, 0, &nt)))
        return 0;
    for (i = 0; i < nt && !names; i++)
        if (u32(types + 8 * i) == type && u32(types + 8 * i + 4) >> 31)
            names = pe_dir(f, u32(types + 8 * i + 4) & 0x7fffffff, &nn);
    for (i = 0; names && i < nn && !found; i++) {
        uint32_t sub = u32(names + 8 * i + 4);
        if ((index >= 0 ? i != (unsigned)index : u32(names + 8 * i) != id) || !(sub >> 31))
            continue;
        langs = pe_dir(f, sub & 0x7fffffff, &nl);
        if (langs && nl && !(u32(langs + 4) >> 31) && rd(f, f->rsrc + u32(langs + 4), data, 8) &&
            u32(data) >= f->rsrc_rva) {
            *off = f->rsrc + (u32(data) - f->rsrc_rva);
            *len = u32(data + 4);
            found = 1;
        }
        free(langs);
    }
    count = names ? (int)nn : 0;
    free(types);
    free(names);
    return count;
}

static int res_find(const ResFile *f, unsigned type, int index, unsigned id, uint32_t *off, uint32_t *len)
{
    *off = *len = 0;
    return f->pe ? pe_find(f, type, index, id, off, len) : ne_find(f, type, index, id, off, len);
}

static HICON file_icon(const ResFile *f, int index)
{
    uint32_t off, len;
    uint8_t *grp, *img = NULL;
    HICON icon = 0;
    int e;

    res_find(f, RES_GROUP_ICON, index, 0, &off, &len);
    if (!(grp = rd_alloc(f, off, len)))
        return 0;
    e = choose(grp, len);
    if (e >= 0) {
        res_find(f, RES_ICON, -1, u16(grp + 6 + 14 * e + 12), &off, &len);
        img = rd_alloc(f, off, len);
    }
    if (img)
        icon = decode(img, len);
    free(img);
    free(grp);
    return icon;
}

/* -1: the number of icons in the file.  Else the icon of that index; 0
 * when the program has no such icon, 1 when the file is not a Windows
 * program. */
HICON ExtractIcon(HINSTANCE h, LPCSTR file, UINT index)
{
    char host[1024];
    ResFile f;
    uint32_t off, len;
    HICON icon;

    (void)h;
    if (!dos_to_host(file, host, sizeof host) || !res_open(&f, host))
        return (int16_t)index == -1 ? 0 : 1;
    if ((int16_t)index == -1)
        icon = (HICON)res_find(&f, RES_GROUP_ICON, -1, 0, &off, &len);
    else
        icon = file_icon(&f, (int16_t)index);
    res_close(&f);
    return icon;
}

HICON LoadIcon(HINSTANCE h, LPCSTR name)
{
    uint32_t len, ilen;
    const uint8_t *grp = h ? module_resource(h, MAKEINTRESOURCE(RES_GROUP_ICON), name, &len) : NULL;
    const uint8_t *img;
    int e = grp ? choose(grp, len) : -1;

    if (e < 0)
        return 0;
    img = module_resource(h, MAKEINTRESOURCE(RES_ICON), MAKEINTRESOURCE(u16(grp + 6 + 14 * e + 12)), &ilen);
    return img ? decode(img, ilen) : 0;
}

BOOL DestroyIcon(HICON h)
{
    Icon *ic = handle_get(h, H_ICON);

    if (!ic)
        return 0;
    free(ic);
    handle_free(h);
    return 1;
}

BOOL DrawIcon(HDC hd, int16_t x, int16_t y, HICON h)
{
    Dc *d = dc_get(hd);
    Bmp *b = d ? dc_bmp(d) : NULL;
    Icon *ic = handle_get(h, H_ICON);
    int i, j;

    if (!b || !ic)
        return 0;
    for (j = 0; j < ICON_W; j++)
        for (i = 0; i < ICON_W; i++) {
            int px = DX(d, x + i), py = DY(d, y + j);
            uint8_t *p;
            if (!gdi_drawable(d, px, py))
                continue;
            p = &b->px[(size_t)py * b->w + px];
            *p = (uint8_t)((ic->keep[j * ICON_W + i] ? *p : 0) ^ gdi_pixel_of(d, ic->color[j * ICON_W + i]));
        }
    return 1;
}
