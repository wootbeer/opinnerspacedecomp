/* GDI objects (gdi.c) and their pixel operations (draw.c).  Bitmaps hold
 * one byte per pixel: a palette index, or 0/1 for monochrome. */
#ifndef GDI_H
#define GDI_H

#include "winrt.h"

typedef struct {
    int w, h, mono;
    uint8_t *px;
    int owned;
} Bmp;

typedef struct {
    int n;
    PALETTEENTRY e[256];
} Pal;

typedef struct {
    int null;
    COLORREF color;
    int has_pattern, pattern_mono;
    uint8_t pattern[64];
} Brush;

typedef struct {
    int null;
    COLORREF color;
} Pen;

typedef struct {
    int16_t height, width, weight;
    char face[32];
} Font;

typedef struct {
    RECT r;
} Rgn;

typedef struct {
    HWND hwnd;              /* window DC (0 for memory DCs) */
    HBITMAP bmp;
    HPALETTE pal;
    HBRUSH brush;
    HPEN pen;
    HFONT font;
    COLORREF text, bk;
    int bkmode, stretch_mode;
    UINT align;
    int ox, oy;             /* device origin in the bitmap */
    POINT org;              /* window origin (SetWindowOrg) */
    RECT clip;              /* in bitmap pixels */
    POINT pos;              /* current position */
} Dc;

Dc *dc_get(HDC h);
Bmp *dc_bmp(const Dc *d);
HBITMAP gdi_new_bitmap(int w, int h, int mono);
HBITMAP gdi_bitmap_from_dib(const uint8_t *dib, uint32_t size);
HPALETTE gdi_new_palette(const PALETTEENTRY *e, int n);

/* A COLORREF as a pixel value in d's bitmap. */
uint8_t gdi_pixel_of(const Dc *d, COLORREF c);

/* Raster operations on device pixels (draw.c). */
void draw_blit(Dc *d, int x, int y, int w, int h, Dc *s, int sx, int sy, int sw, int sh, DWORD rop);
void draw_fill(Dc *d, const RECT *r, HBRUSH brush, DWORD rop);

#endif
