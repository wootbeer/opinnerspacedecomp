/* ISPACE.DLL palette manager (ordinal 4, 5:34c8).  Up to three 256-entry
 * palettes: entries 0-9 and 246-255 are the display's static colours,
 * 10-245 belong to the game (PC_RESERVED, changed with AnimatePalette).
 * The DLL keeps each palette's entries in its own memory, changes them
 * there and sends them to the screen with mode 3 (5:4378).
 *
 * The display here is always 8-bit, so the DLL's 4-bit and 1-bit paths
 * are not ported. */
#include <stdlib.h>
#include <string.h>

#include "ispace.h"

#define SLOTS 3
#define FIRST 10                /* first game entry */
#define COUNT 236               /* game entries */
#define KINDS 3                 /* values of a slot's kind (mode 1) */
#define RANGES 19
#define SET_IDS 25

typedef struct {
    HPALETTE pal;                       /* DS:1cd6 */
    PALETTEENTRY e[256];                /* DS:116c: the entries as the DLL keeps them */
    PALETTEENTRY saved[2][256];         /* DS:14a4: copies for modes 4 and 5 */
    int16_t fixed;                      /* DS:1e92: mode 0's fourth word (0 in this game) */
    int16_t kind;                       /* DS:1e9c: mode 1's high word */
} Slot;

static struct {
    Slot slot[SLOTS];
    int16_t size;                       /* DS:1e98: SIZEPALETTE */
    int16_t bits;                       /* DS:1e9a: bits per pixel (or planes) */
    int16_t ds_01ac;                    /* first palette passed to mode 0 with w2 set */
    int16_t users;                      /* DS:1f3c: palettes sharing the two bitmaps below */
    HDC shape_dc;                       /* DS:0184 */
    HBITMAP shape_bm, shape_old;        /* DS:0186, DS:1f3e */
    HBITMAP alphabet;                   /* DS:1ea2: "ALPHABET" from IGRAPHIC.DLL */
    HDC dc;                             /* DS:1a32 */
    /* Per kind: which of the 19 ranges a colour set occupies (-1: none),
     * how often each range is in use, and each range's first and last
     * entry as byte offsets (mode 1 counts them from the palette header,
     * 5:61b2 from the first entry [sic]). */
    int16_t set_range[KINDS][SET_IDS];  /* DS:1dea */
    int16_t range_used[KINDS][RANGES];  /* DS:1eb8 */
    int16_t range[KINDS][RANGES][2];    /* DS:1398 */
} st = {.ds_01ac = -1};

/* 5:5846 sets these up at every mode 0: ramps between given end colours,
 * then a few colours set one by one. */
const uint8_t ispace_set10[ISPACE_SETS][10][3] = {
    {{255, 255, 255}, {230, 230, 232}, {205, 205, 208}, {180, 180, 184}, {155, 155, 160},
     {130, 130, 136}, {105, 105, 112}, {80, 80, 88}, {55, 55, 64}, {30, 30, 40}}, /* 0 */
    {{255, 230, 110}, {236, 209, 98}, {216, 188, 86}, {196, 167, 74}, {176, 146, 62},
     {156, 125, 49}, {136, 104, 37}, {116, 83, 25}, {96, 62, 13}, {76, 40, 0}}, /* 1 */
    {{240, 210, 100}, {220, 190, 90}, {210, 170, 80}, {200, 155, 70}, {180, 140, 60},
     {160, 125, 50}, {140, 105, 40}, {115, 80, 30}, {90, 60, 20}, {70, 40, 10}}, /* 2 */
    {{255, 235, 0}, {235, 215, 0}, {215, 195, 0}, {195, 175, 0}, {175, 155, 0},
     {155, 135, 0}, {135, 115, 0}, {115, 95, 0}, {95, 75, 0}, {75, 55, 0}}, /* 3 */
    {{255, 250, 60}, {255, 192, 0}, {255, 160, 0}, {255, 110, 0}, {245, 40, 0},
     {224, 0, 0}, {192, 0, 0}, {160, 0, 0}, {108, 0, 0}, {75, 0, 0}}, /* 4 */
    {{245, 85, 245}, {220, 55, 220}, {207, 45, 214}, {190, 0, 205}, {170, 0, 180},
     {140, 0, 145}, {130, 0, 145}, {108, 0, 115}, {75, 0, 80}, {45, 0, 55}}, /* 5 */
    {{150, 110, 195}, {137, 98, 182}, {124, 86, 168}, {110, 74, 154}, {97, 62, 140},
     {84, 49, 126}, {70, 37, 112}, {57, 25, 98}, {44, 13, 84}, {30, 0, 70}}, /* 6 */
    {{200, 176, 192}, {190, 150, 200}, {180, 128, 224}, {160, 96, 255}, {144, 80, 255},
     {128, 64, 255}, {112, 32, 224}, {96, 0, 192}, {0, 0, 160}, {0, 0, 90}}, /* 7 */
    {{0, 170, 255}, {0, 150, 240}, {0, 130, 225}, {0, 110, 205}, {0, 85, 190},
     {0, 60, 170}, {0, 30, 150}, {0, 10, 135}, {0, 0, 110}, {0, 0, 75}}, /* 8 */
    {{150, 245, 255}, {95, 195, 240}, {75, 180, 230}, {40, 145, 224}, {20, 105, 214},
     {0, 85, 208}, {0, 60, 190}, {0, 35, 162}, {0, 15, 126}, {0, 0, 75}}, /* 9 */
    {{170, 255, 0}, {152, 233, 0}, {133, 210, 0}, {114, 187, 0}, {95, 164, 0},
     {76, 142, 0}, {57, 119, 0}, {38, 96, 0}, {19, 73, 0}, {0, 50, 0}}, /* 10 */
    {{192, 255, 0}, {128, 240, 0}, {64, 220, 0}, {58, 179, 0}, {0, 160, 0},
     {0, 145, 0}, {0, 135, 0}, {0, 102, 0}, {0, 96, 0}, {0, 75, 0}}, /* 11 */
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
     {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, /* 12 */
    {{0, 255, 235}, {0, 240, 220}, {0, 220, 200}, {0, 210, 190}, {0, 190, 170},
     {0, 165, 145}, {0, 140, 120}, {0, 120, 100}, {0, 100, 80}, {0, 75, 60}}, /* 13 */
    {{255, 220, 220}, {235, 190, 190}, {225, 165, 165}, {215, 140, 140}, {195, 120, 120},
     {180, 100, 100}, {160, 80, 80}, {140, 60, 60}, {100, 40, 40}, {75, 0, 0}}, /* 14 */
    {{164, 156, 125}, {144, 142, 116}, {131, 135, 115}, {116, 125, 112}, {110, 115, 101},
     {103, 104, 87}, {97, 92, 73}, {90, 83, 65}, {80, 75, 57}, {54, 51, 39}}, /* 15 */
    {{255, 255, 255}, {248, 248, 248}, {238, 238, 238}, {223, 223, 223}, {210, 210, 210},
     {185, 185, 185}, {165, 165, 165}, {125, 125, 125}, {95, 95, 95}, {60, 60, 60}}, /* 16 */
    {{255, 210, 160}, {235, 185, 135}, {215, 165, 115}, {205, 145, 95}, {190, 130, 80},
     {180, 120, 70}, {160, 100, 50}, {140, 80, 30}, {130, 70, 20}, {120, 60, 10}}, /* 17 */
};

const uint8_t ispace_set5[ISPACE_SETS][5][3] = {
    {{255, 255, 255}, {199, 199, 202}, {143, 143, 148}, {87, 87, 94}, {30, 30, 40}}, /* 0 */
    {{255, 210, 30}, {210, 168, 23}, {165, 125, 15}, {120, 83, 8}, {75, 40, 0}}, /* 1 */
    {{240, 210, 100}, {208, 160, 70}, {170, 125, 45}, {120, 80, 25}, {70, 40, 10}}, /* 2 */
    {{255, 230, 0}, {210, 184, 0}, {165, 138, 0}, {120, 92, 0}, {75, 45, 0}}, /* 3 */
    {{255, 250, 60}, {255, 150, 0}, {250, 60, 0}, {192, 0, 0}, {75, 0, 0}}, /* 4 */
    {{255, 0, 255}, {208, 0, 210}, {160, 0, 165}, {112, 0, 120}, {64, 0, 75}}, /* 5 */
    {{180, 110, 180}, {135, 83, 143}, {90, 55, 106}, {45, 28, 69}, {0, 0, 32}}, /* 6 */
    {{200, 176, 192}, {180, 128, 224}, {144, 80, 255}, {96, 0, 192}, {0, 0, 75}}, /* 7 */
    {{0, 220, 220}, {0, 165, 184}, {0, 110, 148}, {0, 55, 112}, {0, 0, 75}}, /* 8 */
    {{110, 230, 255}, {80, 165, 185}, {50, 100, 150}, {25, 60, 130}, {0, 20, 75}}, /* 9 */
    {{200, 255, 0}, {150, 210, 0}, {100, 165, 0}, {50, 120, 0}, {0, 75, 0}}, /* 10 */
    {{170, 255, 0}, {114, 198, 0}, {0, 160, 0}, {0, 128, 0}, {0, 75, 0}}, /* 11 */
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, /* 12 */
    {{0, 255, 235}, {0, 210, 193}, {0, 165, 150}, {0, 120, 108}, {0, 75, 65}}, /* 13 */
    {{255, 220, 220}, {210, 170, 170}, {170, 135, 135}, {130, 50, 50}, {80, 0, 0}}, /* 14 */
    {{164, 156, 125}, {142, 137, 110}, {115, 109, 85}, {85, 78, 63}, {54, 51, 39}}, /* 15 */
    {{255, 255, 255}, {190, 190, 190}, {140, 140, 140}, {100, 100, 100}, {60, 60, 60}}, /* 16 */
    {{255, 210, 160}, {215, 165, 115}, {190, 130, 80}, {160, 100, 50}, {120, 60, 10}}, /* 17 */
};

/* 5:61b2: the colour set loaded for each set id (3-13); -1: none (the
 * DLL reads an uninitialised local, see NOTES-port.md). */
static const int8_t set_source[14] = {-1, -1, -1, 15, -1, 1, 3, 5, 7, 17, 13, 14, 6, 2};

/* Ranges of a kind after mode 1: five fixed ones, then fourteen of ten
 * entries from entry 102 on. */
static const int16_t fixed_ranges[5][2] = {
    {0x2c, 0x6c}, {0x70, 0xf8}, {0x124, 0x164}, {0xfc, 0x120}, {0x168, 0x198}
};

int ispace_pal_slot(HPALETTE pal)
{
    int s;

    for (s = 0; s < SLOTS; s++)
        if (st.slot[s].pal == pal)
            return s;
    return -1;
}

HPALETTE ispace_pal_handle(int slot)
{
    return st.slot[slot].pal;
}

PALETTEENTRY *ispace_pal_entries(int slot)
{
    return st.slot[slot].e;
}

int ispace_pal_fixed(int slot)
{
    return st.slot[slot].fixed;
}

int ispace_pal_bits(void)
{
    return st.bits;
}

void ispace_set_dc(HDC dc)
{
    st.dc = dc;
}

HDC ispace_dc(void)
{
    return st.dc;
}

static void set_rgb(PALETTEENTRY *e, uint8_t r, uint8_t g, uint8_t b)
{
    e->peRed = r;
    e->peGreen = g;
    e->peBlue = b;
}

static int is_black(const PALETTEENTRY *e)
{
    return !e->peRed && !e->peGreen && !e->peBlue;
}

/* The 450x90 monochrome bitmap of three white bars and three white
 * shapes made with the first palette [inferred: its use is in parts of
 * the DLL not ported yet]. */
static void make_shapes(HDC screen)
{
    static const POINT p1[3] = {{180, 89}, {269, 89}, {269, 0}};
    static const POINT p2[4] = {{112, 89}, {179, 89}, {179, 0}, {157, 0}};
    static const POINT p3[4] = {{270, 68}, {270, 89}, {359, 89}, {359, 21}};
    HPEN pen;
    HBRUSH brush;

    st.shape_bm = CreateBitmap(450, 90, 1, 1, NULL);
    st.shape_dc = CreateCompatibleDC(screen);
    st.shape_old = SelectObject(st.shape_dc, st.shape_bm);
    PatBlt(st.shape_dc, 0, 0, 450, 90, BLACKNESS);
    PatBlt(st.shape_dc, 45, 0, 46, 90, WHITENESS);
    PatBlt(st.shape_dc, 360, 45, 90, 46, WHITENESS);
    pen = SelectObject(st.shape_dc, GetStockObject(WHITE_PEN));
    brush = SelectObject(st.shape_dc, GetStockObject(WHITE_BRUSH));
    Polygon(st.shape_dc, p1, 3);
    Polygon(st.shape_dc, p2, 4);
    Polygon(st.shape_dc, p3, 4);
    SelectObject(st.shape_dc, brush);
    SelectObject(st.shape_dc, pen);
    st.users = 0;
}

/* Mode 0 (5:3596): a new palette: the static colours, the game entries
 * black. */
static HPALETTE create(int16_t fixed)
{
    int s = ispace_pal_slot(0), reserved, half, i;
    Slot *p;
    HDC dc;
    struct {
        WORD version, count;
        PALETTEENTRY e[256];
    } lp;

    if (s < 0)
        return 0;
    p = &st.slot[s];
    p->fixed = fixed;
    memset(p->e, 0, sizeof p->e);
    dc = CreateDC("DISPLAY", NULL, NULL, NULL);
    st.size = GetDeviceCaps(dc, SIZEPALETTE);
    reserved = GetDeviceCaps(dc, NUMRESERVED);
    st.bits = max(GetDeviceCaps(dc, BITSPIXEL), GetDeviceCaps(dc, PLANES));
    if (!st.size)
        st.size = 16;
    if (!reserved)
        reserved = 16;
    half = reserved / 2;
    GetSystemPaletteEntries(dc, 0, half, p->e);
    GetSystemPaletteEntries(dc, st.size - half, half, &p->e[256 - half]);
    if (!st.alphabet)
        st.alphabet = ispace_load_bitmap("ALPHABET");
    if (!st.shape_bm)
        make_shapes(dc);
    st.users++;
    DeleteDC(dc);
    for (i = FIRST; i < 256 - FIRST; i++)
        p->e[i].peFlags = PC_RESERVED;
    lp.version = 0x300;
    lp.count = 256;
    memcpy(lp.e, p->e, sizeof lp.e);
    p->pal = CreatePalette((const LOGPALETTE *)&lp);
    memcpy(p->saved[0], p->e, sizeof p->e);
    memcpy(p->saved[1], p->e, sizeof p->e);
    return p->pal;
}

/* Mode 2 (5:3aae). */
static void destroy(HPALETTE pal)
{
    int s = ispace_pal_slot(pal);

    if (s < 0)
        return;
    if (st.slot[s].pal)
        DeleteObject(st.slot[s].pal);
    st.slot[s].pal = 0;
    if (--st.users == 0 && st.shape_dc) {
        SelectObject(st.shape_dc, st.shape_old);
        DeleteDC(st.shape_dc);
        DeleteObject(st.shape_bm);
        st.shape_bm = 0;
        DeleteObject(st.alphabet);
        st.alphabet = 0;
    }
}

void ispace_pal_animate(HPALETTE pal, HWND hwnd, HDC dc)
{
    int s, got = 0;
    HPALETTE old = 0;

    st.dc = dc;
    s = ispace_pal_slot(pal);
    if (s < 0 || !pal)
        return;
    if (!st.dc) {
        got = 1;
        st.dc = GetDC(hwnd);
    }
    old = SelectPalette(st.dc, pal, 0);
    AnimatePalette(pal, FIRST, COUNT, &st.slot[s].e[FIRST]);
    if (old)
        SelectPalette(st.dc, old, 0);
    if (got) {
        ReleaseDC(hwnd, st.dc);
        st.dc = 0;
    }
}

/* 5:61b2: puts colour set id (3-13; 103-113 the same) into the first
 * two black entries in a row and shows the palette; a set the kind has
 * already loaded only gains a user. */
static void load_set(int s, int16_t id)
{
    Slot *p = &st.slot[s];
    int r = 5, pos, j, src;

    if (id == -1 || p->fixed == 1)
        return;
    if (id >= 100)
        id -= 100;
    if (id < 0 || id >= SET_IDS || p->kind < 0 || p->kind > 2)
        return;
    if (p->kind != 2 && st.set_range[p->kind][id] != -1) {
        st.range_used[p->kind][st.set_range[p->kind][id]]++;
        return;
    }
    if (p->kind != 2)
        while (r < RANGES && st.range_used[p->kind][r])
            r++;
    if (r >= RANGES)
        return;
    if (p->kind != 2) {
        st.set_range[p->kind][id] = (int16_t)r;
        st.range_used[p->kind][r] = 1;
    }
    src = id < (int)sizeof set_source ? set_source[id] : -1;
    if (src < 0)
        return;
    for (pos = FIRST; pos < COUNT; pos++)
        if (is_black(&p->e[pos]) && is_black(&p->e[pos + 1]))
            break;
    if (pos < COUNT) {
        st.range[p->kind][r][0] = (int16_t)(pos * 4);
        st.range[p->kind][r][1] = (int16_t)((pos + 9) * 4);
        for (j = 0; j < 10; j++)
            set_rgb(&p->e[pos + j], ispace_set10[src][j][0], ispace_set10[src][j][1],
                    ispace_set10[src][j][2]);
    }
    ispace_pal_animate(p->pal, 0, st.dc);
}

/* 5:254c, 5:2626: entries 11-102 from ISPACE.DLL's resource 100 of type
 * 5500 (92 colours, red, green, blue). */
static void load_base_colors(Slot *p)
{
    uint32_t size;
    const uint8_t *c = module_resource(ispace_module(), MAKEINTRESOURCE(5500), MAKEINTRESOURCE(100), &size);
    int i;

    if (!c || size < 92 * 3)
        return;
    for (i = 0; i < 92; i++)
        set_rgb(&p->e[11 + i], c[3 * i], c[3 * i + 1], c[3 * i + 2]);
}

/* Mode 1 (5:44ac): sets the slot's kind (0-2) and refills its entries:
 * n == -1000 makes them white; otherwise black (n < 0: only 10-182), then
 * the base colours, and colour set n (with n >= 100 or n == -2 entries
 * 73-182 black first; kind 0 also loads sets 5-13). */
static void select_sets(HPALETTE pal, int16_t n, int16_t kind)
{
    int s = ispace_pal_slot(pal), all = n > -1, i;
    Slot *p;

    if (s < 0)
        return;
    p = &st.slot[s];
    p->kind = kind;
    if (kind >= 0 && kind < 2) {
        for (i = 0; i < SET_IDS; i++)
            st.set_range[kind][i] = -1;
        for (i = 0; i < RANGES - 5; i++) {
            st.range_used[kind][5 + i] = 0;
            st.range[kind][5 + i][0] = (int16_t)(0x19c + 40 * i);
            st.range[kind][5 + i][1] = (int16_t)(0x19c + 40 * i + 0x24);
        }
        for (i = 0; i < 5; i++) {
            st.set_range[kind][i] = (int16_t)i;
            st.range_used[kind][i] = 1;
            st.range[kind][i][0] = fixed_ranges[i][0];
            st.range[kind][i][1] = fixed_ranges[i][1];
        }
    }
    if (st.bits < 8)
        return;
    if (n == -1000)
        for (i = 0; i < COUNT; i++)
            set_rgb(&p->e[FIRST + i], 0xff, 0xff, 0xff);
    else
        for (i = 0; i < (all ? COUNT : 173); i++)
            set_rgb(&p->e[FIRST + i], 0, 0, 0);
    if (!p->fixed && n != -1000)
        load_base_colors(p);
    if (n >= 100 || n == -2) {
        for (i = 63; i < 173; i++)
            set_rgb(&p->e[FIRST + i], 0, 0, 0);
        n -= 100;
    }
    if (p->fixed || n <= 4)
        return;
    load_set(s, n + 100);
    if (kind == 0)
        for (i = 5; i <= 13; i++)
            if (i != n)
                load_set(s, (int16_t)(i + 100));
}

/* Modes 4 and 5 (5:484a, 5:474c): copy the game entries to copy which
 * (blacking them when clear), or back from it, and show them. */
static void save_entries(HPALETTE pal, HDC dc, int16_t clear, int16_t which)
{
    int s, i;

    if (st.bits < 8)
        return;
    st.dc = dc;
    s = ispace_pal_slot(pal);
    if (s < 0 || which < 0 || which > 1)
        return;
    for (i = FIRST; i < FIRST + COUNT; i++) {
        PALETTEENTRY *e = &st.slot[s].e[i], *c = &st.slot[s].saved[which][i];
        set_rgb(c, e->peRed, e->peGreen, e->peBlue);
        if (clear)
            set_rgb(e, 0, 0, 0);
    }
    ispace_pal_animate(pal, 0, st.dc);
}

static void restore_entries(HPALETTE pal, HDC dc, int16_t which)
{
    int s, i;

    if (st.bits < 8)
        return;
    st.dc = dc;
    s = ispace_pal_slot(pal);
    if (s < 0 || which < 0 || which > 1)
        return;
    for (i = FIRST; i < FIRST + COUNT; i++) {
        PALETTEENTRY *c = &st.slot[s].saved[which][i];
        set_rgb(&st.slot[s].e[i], c->peRed, c->peGreen, c->peBlue);
    }
    ispace_pal_animate(pal, 0, st.dc);
}

static int near_color(const PALETTEENTRY *e, int r, int g, int b)
{
    return abs(e->peRed - r) < 4 && abs(e->peGreen - g) < 4 && abs(e->peBlue - b) < 4;
}

/* Black, or the colour 1, 11, 111 [inferred: a marker for a free entry]. */
static int is_free(const PALETTEENTRY *e)
{
    return is_black(e) || (e->peRed == 1 && e->peGreen == 11 && e->peBlue == 111);
}

/* Mode 6 (5:3dee): the first free entry from 11 up to 244 (a fixed
 * palette: from 244 down to 11) takes the colour, unless a near colour
 * comes first (entries 10 and 245 count only as near colours).  Only the
 * DLL's copy changes. */
int16_t ispace_pal_add_color(HPALETTE pal, int16_t r, int16_t g, int16_t b)
{
    int s = ispace_pal_slot(pal), fixed, step, end, i;
    PALETTEENTRY *e;

    if (s < 0)
        return -1;
    fixed = st.slot[s].fixed != 0;
    step = fixed ? -1 : 1;
    end = fixed ? FIRST : FIRST + COUNT - 1;
    for (i = fixed ? FIRST + COUNT - 1 : FIRST; i != end; i += step) {
        e = &st.slot[s].e[i];
        if (near_color(e, r, g, b))
            return -1;
        if (is_free(e) && i != FIRST && i != FIRST + COUNT - 1) {
            set_rgb(e, (uint8_t)r, (uint8_t)g, (uint8_t)b);
            return (int16_t)i;
        }
    }
    return -1;
}

/* Mode 7 (5:446e). */
static void load_set_of(HPALETTE pal, int16_t id)
{
    int s = ispace_pal_slot(pal);

    if (s >= 0 && st.slot[s].pal)
        load_set(s, id);
}

int16_t ispace_palette(int16_t pal, int16_t w2, int16_t w3, int16_t w4, int16_t w5, int16_t w6,
                       int16_t mode)
{
    switch (mode) {
    case 0:
        if (w2 && st.ds_01ac == -1)
            st.ds_01ac = pal;
        return (int16_t)create(w4);
    case 1:
        select_sets(pal, w6, w5);
        break;
    case 2:
        destroy(pal);
        break;
    case 3:
        ispace_pal_animate(pal, w2, w3);
        break;
    case 4:
        save_entries(pal, w3, w6, w5);
        break;
    case 5:
        restore_entries(pal, w3, w5);
        break;
    case 6:
        return ispace_pal_add_color(pal, w4, w5, w6);
    case 7:
        load_set_of(pal, w6);
        break;
    default:            /* mode 8 (5:3bae) is not used by the game */
        break;
    }
    return 0;
}
