/* ISPACE.DLL internals shared by its native modules: ispace.c (ordinal
 * table, bitmaps), ispace_pal.c (palette manager), ispace_img.c (image
 * loader), ispace_dlg.c (dialogs) and ispace_reg.c (copy checks). */
#ifndef ISPACE_H
#define ISPACE_H

#include "winrt.h"

HINSTANCE ispace_module(void);
HINSTANCE igraphic_module(void);
HINSTANCE ispace_lang_module(void);      /* DS:0690: <Language>_LANG.DLL (ispace_dlg.c) */

/* Ordinal 3 (5:0612) and ordinal 6 (5:0650). */
int16_t ispace_load_bitmap(LPCSTR name);
HBITMAP ispace_make_mask(int16_t pal, int16_t bm, int16_t dc);

/* Palette manager, ordinal 4 (5:34c8): seven words, the mode last. */
int16_t ispace_palette(int16_t pal, int16_t w2, int16_t w3, int16_t w4, int16_t w5, int16_t w6,
                       int16_t mode);

/* Ordinal 14 (5:50cc): a group of game colours scaled to percent. */
void ispace_pal_scale(int16_t pal, int16_t kind, int16_t percent, HWND hwnd, HDC dc);

/* The slot (0-2) of one of the manager's palettes, or -1. */
int ispace_pal_slot(HPALETTE pal);
HPALETTE ispace_pal_handle(int slot);    /* DS:1cd6 */
int ispace_pal_fixed(int slot);           /* DS:1e92 of the slot */
int ispace_pal_kind(int slot);            /* DS:1e9c: mode 1's kind (0-2) */
/* DS:1dea: the range colour set `set` occupies in the slot's kind (-1:
 * none); DS:1398: a range's first and last entry as byte offsets (NULL
 * outside the tables). */
int16_t ispace_pal_set_range(int slot, int set);
const int16_t *ispace_pal_range(int slot, int16_t r);
int ispace_pal_bits(void);                /* DS:1e9a: bits per pixel of the display */
/* The DC the DLL's routines last worked on (DS:1a32). */
void ispace_set_dc(HDC dc);
HDC ispace_dc(void);
/* 5:61b2: colour set id (3-13) into the slot's palette, or one more user
 * of the range it already has. */
void ispace_pal_load_set(int slot, int16_t id);
/* 5:4378: sends the slot's game entries (10-245) to the screen. */
void ispace_pal_animate(HPALETTE pal, HWND hwnd, HDC dc);
/* 5:3dee (mode 6): an entry for colour (r, g, b); -1 when a near colour
 * is already there or no entry is free. */
int16_t ispace_pal_add_color(HPALETTE pal, int16_t r, int16_t g, int16_t b);
/* 5:4292: the first black entry from 11 to 244, or -1. */
int16_t ispace_pal_first_black(HPALETTE pal);
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
/* DS:1178: the last image's 16 colours (red, green, blue, flags: 4 bytes
 * each) as loaded in modes 0 and 1 (5:26a2, 5:39f6). */
const uint8_t *ispace_image_colors(void);
/* DS:1ea6: red and blue of the image's colours swapped when they go into
 * the palette (set by ordinal 18). */
void ispace_set_image_swap(int16_t on);
extern const int16_t ispace_ramp_area[2][3];
/* 5:1b8e: image id with its colours fitted to palette pal (colour sets a
 * and b, mode as 5:26a2 takes it). */
int ispace_dib_load(int16_t pal, int16_t id, LPCSTR name, int16_t mode, signed char a,
                    signed char b, int16_t own, IspaceDib *d);
HBITMAP ispace_dib_bitmap(IspaceDib *d, int16_t pal);          /* 5:2080 */
/* 5:23a4: a zeroed 8-bit DIB of w x h, rows padded to 4 bytes. */
int ispace_dib8_new(int16_t w, int16_t h, IspaceDib *d);
const uint8_t *ispace_dib_color(const IspaceDib *d, int k);   /* blue, green, red */
const uint8_t *ispace_dib_bits(const IspaceDib *d);
void ispace_set_image_height(int16_t h);                       /* DS:1c72 */

/* 6:7f52 as its callers use it: the root mean square of three weighted
 * channels, three Newton steps from their mean.  Red counts 3/4, blue
 * 5/8 for image colours (ispace_lum_image), 1/2 for palette entries
 * (ispace_lum). */
int16_t ispace_lum(int r, int g, int b);
int16_t ispace_lum_image(int r, int g, int b);

/* Image loader, ordinal 1 (5:0402), and ordinal 2 (6:0000; the
 * calibration strip in ispace_img.c, the surfaces in ispace_surface.c). */
int16_t ispace_load_image(int16_t pal, int16_t id, char *name, int16_t dc, int16_t b, int16_t c);
int16_t ispace_build_surface(int16_t pal, int16_t a, int32_t name, int16_t dc, int16_t e, int16_t f,
                             int16_t g, int16_t h, int16_t i, int16_t j, char k, char l, char m,
                             int16_t n);
int16_t ispace_image_height(void);        /* ordinal 5 (6:00b0) */
/* 6:011c: image id turned to 4 or 16 angles, shaded (ispace_surface.c). */
int16_t ispace_surface(int16_t pal, int16_t id, LPCSTR name, int16_t dc, int16_t f, int16_t i,
                       int16_t j, signed char k, signed char l, signed char m);
/* Ordinal 12 (6:00c4): the image smoothed at twice its size. */
int16_t ispace_smooth_image(int16_t pal, int16_t id, int32_t name, int16_t dc, int16_t w,
                            int16_t h, int16_t g, int16_t c, int16_t i, char a, char b);

/* DS:1108-1144 and DS:1ca4-1cc2: the ramps image colours 0-9 (group 0,
 * ten ramps) and 10-14 (group 1, five) are shaded with: first (lightest)
 * and last palette entry and their lightness (ordinals 2 and 12). */
typedef struct {
    int16_t first, last, lum_first, lum_last;
} IspaceRamp;

IspaceRamp *ispace_ramps(int group);
/* The entry for lightness v on ramp rp: its place on the ramp, then the
 * nearest shade around it (5:6b72); entry 245 when darker than the ramp. */
uint8_t ispace_ramp_shade(const PALETTEENTRY *e, const IspaceRamp *rp, uint8_t v);
/* 5:66ea: the colour set id (0-13) whose hue colour r, g, b has. */
int16_t ispace_set_of_color(int r, int g, int b);
/* DS:1ccc: the angles of ordinal 2's last surface; ordinal 12 makes its
 * bitmap that many times wider again (ispace_surface.c). */
int16_t *ispace_ds_1ccc(void);

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

/* Ordinal 32 (8:0000): a room of IGRAPHIC.DLL drawn into a new bitmap
 * (ispace_room.c); ordinals 33-35 (8:037a, 8:05ac, 8:0768): text in the
 * ALPHABET font, a raised or sunken box, a gauge (ispace_panel.c). */
HBITMAP ispace_room(int16_t dc, int16_t pal, RECT *rects, HGLOBAL hrects, int16_t id, int32_t d,
                    int16_t e, int32_t f, int16_t g, int16_t w, int16_t h, int16_t y, int16_t x,
                    int16_t lift);
void ispace_letters(int16_t dc, int16_t pal, int32_t size, int16_t align, int32_t color, int16_t x,
                    int16_t y, char *text);
void ispace_bevel(int16_t dc, int16_t x, int16_t y, int16_t w, int16_t h, int16_t kind);
void ispace_gauge(int16_t dc, int16_t x, int16_t y, int16_t w, int16_t h, int16_t percent);
HBITMAP ispace_alphabet(void);           /* DS:1ea2 */
HDC ispace_shape_dc(void);               /* DS:0184: the masks of ordinal 15 (ispace_pal.c) */
/* 6:7f52: three Newton steps towards the square root of sq from m. */
int16_t ispace_newton_root(int32_t sq, int32_t m);

/* Ordinal 18 (6:5e76): image 280 turned to n angles, as a sprite sheet
 * (ispace_sprite.c). */
int16_t ispace_sprite_sheet(int16_t pal, int16_t unused1, int16_t unused2, int16_t kind, int16_t n,
                            int16_t swap);

/* Ordinal 15 (5:11a4): a side cut off a sprite sheet, mode 1 also the
 * part cut from direction dir as a bitmap (ispace_cut.c). */
int16_t ispace_cut(int16_t screen, int16_t sheet, int16_t side, int16_t size, int16_t offset,
                   int16_t border, int16_t pal, int16_t dir, int16_t mode);

/* Ordinal 29 (2:003c): two objects meeting (ispace_collide.c). */
int16_t ispace_collide(int16_t *vx1, int16_t *vy1, int16_t *vx2, int16_t *vy2, int16_t *x1,
                       int16_t *y1, int16_t *x2, int16_t *y2, int16_t s1, int16_t s2, int16_t m1,
                       int16_t m2, int16_t *hit1, int16_t *hit2);

/* Ordinal 10 (9:145e): the game's dialogs (ispace_dlg.c). */
int16_t ispace_dialog(int16_t hwnd, int16_t dc, int16_t pal, int16_t v1, int16_t v0, int16_t w6,
                      int16_t mode);
int ispace_dialog_slot(void);    /* DS:1f92, slot 0 before any dialog */
int16_t ispace_dialog_word6(void);  /* DS:2136: the sixth word of the last call (1: Game Settings grays its detail options) */
/* The dialogs' fonts (9:29c0, 9:2a1e) and 10:602a, which gives them to a
 * dialog's controls. */
void ispace_dialog_fonts(int make);
void ispace_dialog_set_fonts(HWND dlg);
/* 9:328e: the help file's topic (WinHelp). */
void ispace_help(int32_t topic);

/* Ordinal 10 mode 0 (9:1546): the Game Settings dialog with its dialog
 * procedures, ordinals 11 (9:15cc), 37 (9:2bf8, Display Options) and 38
 * (9:2f30, Audio Options) (ispace_options.c). */
int16_t ispace_options(HWND owner);
BOOL ispace_options_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp);
BOOL ispace_display_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp);
BOOL ispace_audio_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp);

/* The settings 9:22ca reads from the INI (ispace_sound.c), which the
 * Game Settings dialogs (ispace_options.c) show and change. */
typedef struct {
    int16_t system;             /* DS:2280 SoundSystem: 0 none, 1 standard, 2 dynamic, 3 3-D */
    int16_t device_best;        /* DS:227e: the most the wave device allows */
    int16_t fx_on, voice_on;    /* DS:0694 SoundFX, DS:0696 VoiceFX */
    int16_t volume;             /* DS:069e SoundVolume (SaverVolume in mode 10) */
    int16_t balance;            /* DS:06a2 FXMusic: 0 effects only ... 100 music only */
    int16_t stereo;             /* DS:228c StereoEffect */
    int16_t purge;              /* DS:0698 PurgeSound */
    int16_t swap;               /* DS:069a StereoSwap */
    int16_t enhance;            /* DS:2132 Enhance */
    int16_t detail;             /* DS:228a Detail */
    int16_t quick;              /* DS:2286 Quick */
} IspaceSettings;

IspaceSettings *ispace_settings(void);

/* Ordinals 7, 8, 9 (9:0000, 9:076c, 9:0c42): sound (ispace_sound.c). */
int16_t ispace_sound_control(int32_t a, int16_t mode);
int16_t ispace_sound_follow(POINT p, int16_t x, int16_t y, int32_t view);
int16_t ispace_sound_play(int16_t a, POINT p, int16_t r, int32_t q, int32_t view, DWORD now,
                          LPCSTR name);
void ispace_sound_effect(int16_t n);         /* 9:298c */
HWND ispace_sound_window(void);              /* DS:21ae: the NotifyClass window */
int16_t ispace_sound_system(void);           /* DS:2280 SoundSystem */
int16_t ispace_sound_music_volume(void);     /* DS:2288 */
void ispace_sound_path(char *path, size_t size);    /* INI SndPath with its '\' */
void ispace_sound_read_settings(void);       /* 9:22ca */
void ispace_sound_mix_volumes(void);         /* 9:0a9e */
int16_t ispace_sound_channels(void);         /* DS:219e MixChannels */
HINSTANCE ispace_sound_library(int n);       /* DS:068c: SND_FX.DLL (0), <Language>_FX.DLL (1) */
/* 9:331a after the Audio Options dialog's INI writes: the sound DLLs and
 * the mixer as the new settings and channel count say. */
void ispace_sound_apply(int16_t channels);

/* The music (ordinal 7 mode 11, 9:3906; ispace_music.c). */
void ispace_music(int16_t n, int16_t wait);
void ispace_music_set_on(int16_t on);        /* INI Music */
int16_t ispace_music_on(void);               /* DS:221e */
int16_t ispace_music_piece(void);            /* DS:0aa4: the piece asked for last */
void ispace_music_center(void);
LRESULT ispace_music_message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
void ispace_music_save_volume(void);
void ispace_music_restore_volume(void);
void ispace_music_deactivate(void);
void ispace_music_activate(int force_volume);
void ispace_music_resume(void);

#endif
