/* ISPACE.DLL internals shared by its native modules: ispace.c (ordinal
 * table, bitmaps), ispace_pal.c (palette manager), ispace_img.c (image
 * loader), ispace_dlg.c (dialogs) and ispace_reg.c (copy checks). */
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
HPALETTE ispace_pal_handle(int slot);    /* DS:1cd6 */
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
/* The slot's 256 entries as the DLL keeps them (DS:116c). */
PALETTEENTRY *ispace_pal_entries(int slot);
/* The colour sets of 5:5846: ten colours for DIB colours 0-9 and five
 * for colours 10-14, as red, green, blue. */
#define ISPACE_SETS 18
extern const uint8_t ispace_set10[ISPACE_SETS][10][3];
extern const uint8_t ispace_set5[ISPACE_SETS][5][3];

/* A packed DIB (BITMAPINFOHEADER, colour table, bits) in the DLL's
 * memory. */
typedef struct {
    uint8_t *data;
    uint32_t size;
} IspaceDib;

/* Flags the image loader leaves in the DLL's data for what follows. */
typedef struct {
    int16_t ds_0188;                    /* id -2 asked for: colour 15's red counts */
    int16_t ds_1ea4;                    /* the image is being recoloured */
    int16_t ds_1ea8;                    /* colour 15 was not black: VGA colours put in */
    int16_t ds_1eaa;                    /* colours 0-9 went into the palette as a ramp */
    int16_t ds_1eac;                    /* colours 10-14 likewise */
} IspaceImgFlags;

IspaceImgFlags *ispace_img_flags(void);
extern const int16_t ispace_ramp_area[2][3];
/* 5:1b8e: image id with its colours fitted to palette pal (colour sets a
 * and b, mode as 5:26a2 takes it). */
int ispace_dib_load(int16_t pal, int16_t id, LPCSTR name, int16_t mode, signed char a,
                    signed char b, int16_t own, IspaceDib *d);
HBITMAP ispace_dib_bitmap(IspaceDib *d, int16_t pal);          /* 5:2080 */
const uint8_t *ispace_dib_color(const IspaceDib *d, int k);   /* blue, green, red */
const uint8_t *ispace_dib_bits(const IspaceDib *d);
void ispace_set_image_height(int16_t h);                       /* DS:1c72 */

/* 6:7f52 as its callers use it: the root mean square of three weighted
 * channels, three Newton steps from their mean.  Red counts 3/4, blue
 * 5/8 for image colours (ispace_lum_image), 1/2 for palette entries
 * (ispace_lum). */
int16_t ispace_lum(int r, int g, int b);
int16_t ispace_lum_image(int r, int g, int b);

/* Image loader, ordinal 1 (5:0402), and ordinal 2 (6:0000). */
int16_t ispace_load_image(int16_t pal, int16_t id, char *name, int16_t dc, int16_t b, int16_t c);
int16_t ispace_build_surface(int16_t pal, int16_t a, int32_t name, int16_t dc, int16_t e, int16_t f,
                             int16_t g, int16_t h, int16_t i, int16_t j, char k, char l, char m,
                             int16_t n);
int16_t ispace_image_height(void);        /* ordinal 5 (6:00b0) */
/* Ordinal 12 (6:00c4): the image smoothed at twice its size. */
int16_t ispace_smooth_image(int16_t pal, int16_t id, int32_t name, int16_t dc, int16_t w,
                            int16_t h, int16_t g, int16_t c, int16_t i, char a, char b);

/* DS:01ac: set by palette mode 0, read by the New Game dialog as its
 * registered flag (-1: not known yet). */
int16_t *ispace_ds_01ac(void);

/* Ordinal 24 (10:48d2): copy checks (ispace_reg.c). */
int16_t ispace_check(char *a, char *b, int16_t mode);

/* 5:0000: a ship's picture, image id (or the file name) with colour sets
 * a and b put in the palette at the slot's ramp (mode 0-2). */
HBITMAP ispace_ship_image(int16_t pal, int16_t id, char *name, int16_t a, int16_t b, int16_t mode);

/* Ordinal 36 (10:2e1a): StretchBlt doubling or mirroring (ispace.c). */
int16_t ispace_blit_double(HDC dst, int16_t x, int16_t y, int16_t w, int16_t h, HDC src, int16_t xs,
                           int16_t ys, int16_t ws, int16_t hs, int32_t rop);

/* Ordinal 10 (9:145e): the game's dialogs (ispace_dlg.c). */
int16_t ispace_dialog(int16_t hwnd, int16_t dc, int16_t pal, int16_t v1, int16_t v0, int16_t w6,
                      int16_t mode);
int ispace_dialog_slot(void);    /* DS:1f92, slot 0 before any dialog */

#endif
