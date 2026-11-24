/* ISPACE.DLL segment 8: the 3D rooms of ordinal 32 (ispace_room.c) and
 * the shapes they are drawn with (ispace_shape.c).
 *
 * A room is a resource of type 6600 in IGRAPHIC.DLL: a 0x6c-byte header
 * (colour ramps, eye position) and 0x26-byte objects placed relative to
 * other objects.  World x runs across, y into the picture (depth), z up;
 * all lengths are in thousandths of what the object is placed in.  A
 * point at depth y is seen at the scale s = vw * dist / (y * vw / 1000 +
 * dist), so lengths shrink with depth, and points of the floor converge
 * on (eye_x, eye_y).  Names of the view values are [inferred]. */
#ifndef ISPACE_ROOM_H
#define ISPACE_ROOM_H

#include "ispace.h"

#define ROOM_RAMPS 10

typedef struct {
    HDC dc;                     /* DS:1c66: memory DC of the picture */
    HPALETTE pal;               /* the palette ordinal 32 was given */
    int16_t w, h;               /* DS:0d18, 0d1a: picture size */
    int16_t vw;                 /* DS:0d28, 0d3c: h * 4 / 3 */
    int16_t eye_x, eye_y;       /* DS:0d2c, 0d2e: vanishing point */
    int16_t floor_y;            /* DS:1c6c: the floor's y at depth 0 */
    int32_t dist;               /* DS:0d4c: eye distance */
    int32_t floor_k;            /* DS:0d48: (floor_y - eye_y) * 2000 / vw */
    int32_t shift_k;            /* DS:0d44: horizon distance per x shift */
    const uint8_t *hdr;         /* DS:0d10: the room's header */
    uint8_t ramp_channel[ROOM_RAMPS];   /* DS:1c42: brightest channel of each ramp */
    uint8_t ramp_first[ROOM_RAMPS];     /* DS:1c4c: palette entries of each ramp */
    uint8_t ramp_last[ROOM_RAMPS];      /* DS:1c56 */
    RECT face;                  /* DS:0d30: front face of the last box */
    POINT line_pt[2];           /* DS:0cde: the ends of the current line */
    int16_t line_floor;         /* DS:0ce6: floor y at the line's first end */
} Room;

extern Room room;

/* Header words and colours. */
int16_t room_hdr_word(int off);

/* Depth y to scale s; the floor's y and the screen x of world x at
 * scale s (for the floor's y fy). */
int32_t room_scale(int32_t y);
int16_t room_floor_y(int32_t s);
int16_t room_screen_x(int16_t fy, int16_t x);
/* hz = floor_y - eye_y, used by every shading rule. */
int16_t room_hz(void);
/* Brightness at floor y fy for brightness b: (fy - eye_y)^2 * 2b / hz^2,
 * halved as a 16-bit value. */
int16_t room_floor_light(int16_t fy, int32_t two_b);

/* 8:27f0: the palette entry of ramp r at brightness b (PALETTEINDEX). */
COLORREF room_color(int16_t ramp, int16_t channel, int16_t b);
/* A solid brush of colour c selected into the picture; room_unbrush
 * puts the old one back and deletes it. */
HBRUSH room_brush(COLORREF c);
void room_unbrush(HBRUSH old);

/* Shapes (ispace_shape.c). */
void room_face(const POINT q[4], int16_t ramp, int16_t channel, int16_t b, int16_t fy0,
               int16_t fy1, int16_t step, int16_t across);
void room_box(int32_t x, int32_t y, int32_t d, int32_t w, int32_t z, int32_t h, int16_t front,
              int16_t vents, int16_t step, int16_t ramp, int16_t channel, int16_t b,
              const char *text, int16_t text_face, int16_t text_kind, int16_t text_size);
void room_cylinder(int32_t x, int32_t y, int32_t z, int32_t w, int32_t d, int32_t h, int16_t ramp,
                   int16_t channel, int16_t b, int16_t mark, int16_t step);
void room_point(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t t,
                int16_t ramp, int16_t channel, int16_t b);
void room_line_point(int32_t x, int32_t y, int32_t z, int16_t ramp, int16_t channel, int16_t b,
                     int16_t width, int16_t draw);
void room_text(int16_t x, int16_t y, int16_t size, const char *s, int16_t kind, int16_t fy,
               int16_t r, int16_t g, int16_t b);

#endif
