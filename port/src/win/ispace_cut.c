/* ISPACE.DLL ordinal 15 (5:11a4): a side of an object cut off its sprite
 * sheet.  The sheet (ordinal 2's layout: 16 cells of size x size, border
 * pixels around and between them, one per direction) is ANDed in every
 * cell with a mask of DS:0184 (ispace_pal.c): one of five half planes,
 * turned to the cell's direction and moved `offset` across, so the side
 * beyond the line goes black.  Mode 1 also returns the part cut away
 * from the cell of direction dir as a new size x size bitmap.  The game
 * calls it when a ship of two halves loses one (8:2cd8; side picks
 * which). */
#include "ispace.h"

#define SHAPE 90                        /* side of a mask in DS:0184 */
#define PHASES 5
#define FLIP_X 1
#define FLIP_Y 2

/* DS:001a, DS:0010: minus cosine and sine of the masks' angles, x 128. */
static const int16_t mcos128[PHASES] = {-128, -118, -91, -50, 0};
static const int16_t sin128[PHASES] = {0, 50, 91, 118, 128};
/* The jump table at 5:12b0: the mask of each direction. */
static const uint8_t phase_of[16] = {0, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 3, 2, 1};
/* Per mask the cells it is cut into, in the DLL's order (-1: none). */
static const int8_t cells_of[PHASES][4] = {
    {0, 8, -1, -1}, {1, 7, 9, 15}, {2, 6, 10, 14}, {3, 5, 11, 13}, {4, 12, -1, -1}};

/* The part of a mask laid over a cell. */
typedef struct {
    int16_t x, y, w, h;
} Part;

static Part part_of(int k, int16_t size, int16_t offset)
{
    int16_t a = (int16_t)((int16_t)(mcos128[k] * offset) >> 7);
    int16_t b = (int16_t)((int16_t)(sin128[k] * offset) >> 7);
    int16_t left = (int16_t)(SHAPE / 2 - size / 2);
    Part p;

    p.x = (int16_t)(SHAPE * k - a + left);
    p.y = (int16_t)(b + left);
    p.w = (int16_t)(a - left + SHAPE - 1);
    p.h = (int16_t)(SHAPE - 1 - p.y);
    if (p.w > size)
        p.w = size;
    if (p.h > size)
        p.h = size;
    return p;
}

/* How the mask is mirrored for the cell of direction c: for side 1 as
 * the angles go round; side 0 has it turned half round, except
 * directions 8 and 12, which take the mask as it is. */
static int flip_of(int16_t c, int16_t side)
{
    int f = c <= 4 ? 0 : c <= 8 ? FLIP_X : c < 12 ? FLIP_X | FLIP_Y : FLIP_Y;

    if (side)
        return f;
    return c == 8 || c == 12 ? 0 : f ^ (FLIP_X | FLIP_Y);
}

/* The mask part into the size x size cell at (x, y) of dc. */
static void cut(HDC dc, int16_t x, int16_t y, int16_t size, const Part *p, int flip, DWORD rop)
{
    StretchBlt(dc, (int16_t)(flip & FLIP_X ? x + size - 1 : x), (int16_t)(flip & FLIP_Y ? y + size - 1 : y),
               (int16_t)(flip & FLIP_X ? -p->w : p->w), (int16_t)(flip & FLIP_Y ? -p->h : p->h),
               ispace_shape_dc(), p->x, p->y, p->w, p->h, rop);
}

int16_t ispace_cut(int16_t screen, int16_t sheet, int16_t side, int16_t size, int16_t offset,
                   int16_t border, int16_t pal, int16_t dir, int16_t mode)
{
    int16_t stride = (int16_t)(border + size);
    HBITMAP part = 0, old = 0;
    HPALETTE old_pal = 0;
    HDC dc = 0;
    int k, i;

    (void)screen;
    /* A direction outside 0-15 makes the DLL read its other locals as
     * the mask's place: no part then. */
    if (mode && dir >= 0 && dir < 16) {
        Part p = part_of(phase_of[dir], size, offset);
        dc = CreateCompatibleDC(sheet);
        part = CreateCompatibleBitmap(sheet, size, size);
        old = SelectObject(dc, part);
        if (pal)
            old_pal = SelectPalette(dc, pal, 0);
        PatBlt(dc, 0, 0, size, size, BLACKNESS);
        BitBlt(dc, 0, 0, size, size, sheet, (int16_t)(stride * dir + border), border, SRCCOPY);
        cut(dc, 0, 0, size, &p, flip_of(dir, side), 0x220326);     /* DSna */
    }
    for (k = 0; k < PHASES; k++) {
        Part p = part_of(k, size, offset);
        for (i = 0; i < 4 && cells_of[k][i] >= 0; i++) {
            int16_t c = cells_of[k][i];
            cut(sheet, (int16_t)(stride * c + border), border, size, &p, flip_of(c, side), SRCAND);
        }
    }
    if (!mode)
        return -1;
    if (dc) {
        SelectObject(dc, old);
        if (pal)
            SelectPalette(dc, old_pal, 0);
        DeleteDC(dc);
    }
    return (int16_t)part;
}
