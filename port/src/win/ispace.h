/* ISPACE.DLL internals shared by its native modules: ispace.c (ordinal
 * table, bitmaps), ispace_pal.c (palette manager) and ispace_img.c
 * (image loader). */
#ifndef ISPACE_H
#define ISPACE_H

#include "winrt.h"

HINSTANCE ispace_module(void);
HINSTANCE igraphic_module(void);

/* Ordinal 3 (5:0612) and ordinal 6 (5:0650). */
int16_t ispace_load_bitmap(LPCSTR name);
HBITMAP ispace_make_mask(int16_t pal, int16_t bm, int16_t dc);

/* Palette manager, ordinal 4 (5:34c8): seven words, the mode last. */
int16_t ispace_palette(int16_t pal, int16_t w2, int16_t w3, int16_t w4, int16_t w5, int16_t w6,
                       int16_t mode);

/* The slot (0-2) of one of the manager's palettes, or -1. */
int ispace_pal_slot(HPALETTE pal);
int ispace_pal_fixed(int slot);           /* DS:1e92 of the slot */
int ispace_pal_bits(void);                /* DS:1e9a: bits per pixel of the display */
/* The DC the DLL's routines last worked on (DS:1a32). */
void ispace_set_dc(HDC dc);
HDC ispace_dc(void);
/* 5:4378: sends the slot's game entries (10-245) to the screen. */
void ispace_pal_animate(HPALETTE pal, HWND hwnd, HDC dc);
/* 5:3dee (mode 6): an entry for colour (r, g, b); -1 when a near colour
 * is already there or no entry is free. */
int16_t ispace_pal_add_color(HPALETTE pal, int16_t r, int16_t g, int16_t b);
/* The colour sets of 5:5846: ten colours for DIB colours 0-9 and five
 * for colours 10-14, as red, green, blue. */
#define ISPACE_SETS 18
extern const uint8_t ispace_set10[ISPACE_SETS][10][3];
extern const uint8_t ispace_set5[ISPACE_SETS][5][3];

/* Image loader, ordinal 1 (5:0402), and ordinal 2 (6:0000). */
int16_t ispace_load_image(int16_t pal, int16_t id, char *name, int16_t dc, int16_t b, int16_t c);
int16_t ispace_build_surface(int16_t pal, int16_t a, int32_t name, int16_t dc, int16_t e, int16_t f,
                             int16_t g, int16_t h, int16_t i, int16_t j, char k, char l, char m,
                             int16_t n);
int16_t ispace_image_height(void);        /* ordinal 5 (6:00b0) */

#endif
