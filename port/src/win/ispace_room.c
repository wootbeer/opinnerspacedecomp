/* ISPACE.DLL ordinal 32 (8:0000): draws one of the rooms of IGRAPHIC.DLL
 * (the desk, the inside of the computer, ...) into a new bitmap and
 * returns the screen rectangles of the objects the game needs (the
 * monitor's screen, ...).  See ispace_room.h for the room format; the
 * shapes are in ispace_shape.c.  The display is always 8-bit here, so
 * the DLL's paths for fewer colours are not ported. */
#include <SDL3/SDL_stdinc.h>
#include <string.h>

#include "ispace_room.h"

#define ROOM_TYPE 6600
#define HDR_SIZE 0x6c
#define OBJ_START 0x80          /* GlobalSize of the 0x6c-byte header block */
#define OBJ_SIZE 0x26
#define MAX_OBJS 128

/* One object (0x26 bytes).  v[] are the words at +1: position (x is the
 * centre), size, their modes, and at +0x19 the text. */
typedef struct {
    uint8_t done;               /* +00: placed */
    int16_t v[13];
    int8_t parent;              /* +1b: placed relative to */
    int8_t parent2;             /* +1c: the second end of a line is relative to */
    int8_t ramp;                /* +1d: colour ramp, -1 none */
    uint8_t type;               /* +1e: 1 box, 2 line, 3 cylinder, 4 and 5 not ported */
    int8_t rect;                /* +1f: >= 0 the game's rectangle, < -1 a condition */
    int8_t shade;               /* +20: brightness in fiftieths */
    int8_t f21, f22, f23, f24, f25;
} RoomObj;

#define POS(o, k) ((o)->v[k])
#define SIZE(o, k) ((o)->v[3 + (k)])
#define POS_MODE(o, k) ((o)->v[6 + (k)])
#define SIZE_MODE(o, k) ((o)->v[9 + (k)])
#define TEXT(o) ((o)->v[12])

Room room;

static struct {
    uint8_t hdr[0x100];         /* DS:0d10 block, zero past the header */
    RoomObj obj[MAX_OBJS];      /* DS:0d50 block */
    int count;                  /* DS:1c6e */
    int max_rect;               /* DS:1c68 */
    int16_t eye_x, eye_y;       /* DS:0d2c, 0d2e: kept between calls */
    /* 8:5c86: what the computer on the desk knows about the machine. */
    char video[0x5a];           /* DS:1b34 */
    char sound[0x5a];           /* DS:1b8e */
    char network[0x5a];         /* DS:1be8 */
    char cpu[10];               /* DS:0d1c */
    int16_t cpu_class;          /* DS:1c70: 2, 3, 4 (286-486) or 0 */
    int8_t fpu;                 /* DS:22a8: 1 for a 386 with a coprocessor */
    int8_t wave, stereo;        /* DS:22aa, 22ab */
} rs;

/* MSC's ldiv truncates like C99; a zero divisor (a divide fault in the
 * DLL) gives 0. */
static int32_t div32(int32_t a, int32_t b)
{
    return b ? a / b : 0;
}

int16_t room_hdr_word(int off)
{
    return (int16_t)(rs.hdr[off] | rs.hdr[off + 1] << 8);
}

static int32_t hdr_long(int off)
{
    return (int32_t)((uint32_t)(uint16_t)room_hdr_word(off) | (uint32_t)(uint16_t)room_hdr_word(off + 2) << 16);
}

int32_t room_scale(int32_t y)
{
    return div32((int32_t)room.vw * room.dist, div32(y * room.vw, 1000) + room.dist);
}

int16_t room_floor_y(int32_t s)
{
    return (int16_t)(div32(s * room.floor_k, 2000) + room.eye_y);
}

int16_t room_screen_x(int16_t fy, int16_t x)
{
    return (int16_t)(div32((int32_t)(int16_t)(room.floor_y - fy) * 1000, room.shift_k) + x
                     + (int16_t)(room.w - room.vw) / 2);
}

int16_t room_hz(void)
{
    return (int16_t)(room.floor_y - room.eye_y);
}

int16_t room_floor_light(int16_t fy, int32_t two_b)
{
    int32_t hz = room_hz(), d = (int16_t)(fy - room.eye_y);

    return (int16_t)((int16_t)div32(d * d * two_b, hz * hz) >> 1);
}

COLORREF room_color(int16_t ramp, int16_t channel, int16_t b)
{
    int16_t top, low, first, last, idx;

    if (ramp < 0 || ramp >= ROOM_RAMPS || channel < 0 || channel > 2)
        return PALETTEINDEX(0);     /* the DLL reads outside its tables */
    if (b > 255)
        b = 255;
    top = room_hdr_word(2 * (3 * ramp + channel));
    low = room_hdr_word(0x2c + 2 * (3 * ramp + channel));
    first = room.ramp_first[ramp];
    last = room.ramp_last[ramp];
    idx = (int16_t)(last - div32((int32_t)(int16_t)(top - b) * (int16_t)(last - first), (int16_t)(top - low)));
    if (idx < first)
        idx = first;
    if (idx > last)
        idx = last;
    return PALETTEINDEX((uint16_t)idx);
}

HBRUSH room_brush(COLORREF c)
{
    return SelectObject(room.dc, CreateSolidBrush(c));
}

void room_unbrush(HBRUSH old)
{
    DeleteObject(SelectObject(room.dc, old));
}

/* 8:5b76: room id from IGRAPHIC.DLL: the header, then the objects from
 * 0x80 on.  The DLL copies them into blocks whose sizes Windows rounds
 * up to 32 bytes; the count is taken from the rounded size (the slack
 * is zero). */
static int load_room(int16_t id)
{
    uint32_t size;
    const uint8_t *r = module_resource(igraphic_module(), MAKEINTRESOURCE(ROOM_TYPE), MAKEINTRESOURCE(id),
                                       &size);
    int i, k;

    memset(rs.hdr, 0, sizeof rs.hdr);
    memset(rs.obj, 0, sizeof rs.obj);
    rs.count = 0;
    if (!r || size < OBJ_START)
        return 0;
    memcpy(rs.hdr, r, HDR_SIZE);
    rs.count = (int)(((size - OBJ_START + 31) & ~31u) / OBJ_SIZE);
    if (rs.count > MAX_OBJS)
        rs.count = MAX_OBJS;
    for (i = 0; i < rs.count; i++) {
        uint8_t b[OBJ_SIZE] = {0};
        RoomObj *o = &rs.obj[i];
        uint32_t at = OBJ_START + (uint32_t)i * OBJ_SIZE;
        memcpy(b, r + at, at + OBJ_SIZE <= size ? OBJ_SIZE : at < size ? size - at : 0);
        o->done = b[0];
        for (k = 0; k < 13; k++)
            o->v[k] = (int16_t)(b[1 + 2 * k] | b[2 + 2 * k] << 8);
        o->parent = (int8_t)b[0x1b];
        o->parent2 = (int8_t)b[0x1c];
        o->ramp = (int8_t)b[0x1d];
        o->type = b[0x1e];
        o->rect = (int8_t)b[0x1f];
        o->shade = (int8_t)b[0x20];
        o->f21 = (int8_t)b[0x21];
        o->f22 = (int8_t)b[0x22];
        o->f23 = (int8_t)b[0x23];
        o->f24 = (int8_t)b[0x24];
        o->f25 = (int8_t)b[0x25];
    }
    return 1;
}

static RoomObj *obj_at(int i)
{
    return i >= 0 && i < rs.count ? &rs.obj[i] : NULL;
}

/* The length mode m of object p refers to (for m 1-4 the words from its
 * size on: 4 is its first position mode [sic]); -1 for none. */
static int16_t ref_len(const RoomObj *p, int16_t m)
{
    if (m == 5)
        return SIZE(&rs.obj[0], 0);
    return m >= 1 && m <= 10 ? p->v[2 + m] : -1;
}

/* A position or size in screen units (modes 6 and up) as pixels: of the
 * picture's width (6) or height (7), pixels (8), of the screen's width
 * (9) or height (10); larger modes are a minimum in pixels for a share
 * of the height. */
static int32_t screen_len(int16_t m, int16_t v)
{
    switch (m) {
    case 6: return (int32_t)v * room.w;
    case 7: return (int32_t)v * room.h;
    case 8: return (int32_t)v * 1000;
    case 9: return (int32_t)v * GetSystemMetrics(SM_CXSCREEN);
    case 10: return (int32_t)v * GetSystemMetrics(SM_CYSCREEN);
    default: {
        int32_t a = (int32_t)v * room.h, b = (int32_t)m * 1000;
        return a > b ? a : b;
    }
    }
}

/* 8:0a36, positions and sizes relative to the parent for coordinate k. */
static void place_axis(RoomObj *o, int k)
{
    RoomObj *p = &rs.obj[o->parent], *q;
    int16_t m = POS_MODE(o, k);
    int32_t len;

    if (m < 6) {
        len = m == 0 ? SIZE(p, k) : ref_len(p, m);
        if (len != -1) {
            POS(o, k) = (int16_t)(div32((int32_t)POS(o, k) * len, 1000) + POS(p, k));
            if (k == 0)
                POS(o, k) -= SIZE(p, 0) / 2;
            else if (k == 2)
                POS(o, k) += SIZE(p, 2);
        }
    }
    m = SIZE_MODE(o, k);
    if (o->type == 1 || o->type == 3 || o->type == 4 || o->type == 5) {
        if (m == 0)
            len = SIZE(p, 0);
        else if (k != 0 && m == 4)
            len = SIZE(o, 0);
        else
            len = m < 6 ? ref_len(p, m) : -1;
        if (len != -1)
            SIZE(o, k) = (int16_t)div32((int32_t)SIZE(o, k) * len, 1000);
    } else if (o->type == 2 && (q = obj_at(o->parent2)) != NULL) {
        len = m == 0 ? SIZE(q, k) : m == 5 ? SIZE(&rs.obj[0], 0) : (m >= 1 && m <= 10 ? q->v[2 + m] : 0);
        SIZE(o, k) = (int16_t)(div32((int32_t)SIZE(o, k) * len, 1000) + POS(q, k));
        if (k == 0)
            SIZE(o, k) -= SIZE(q, 0) / 2;
        else if (k == 2)
            SIZE(o, k) += SIZE(q, 2);
    }
}

/* Positions and sizes given in screen units become world units at the
 * object's depth. */
static void place_on_screen(RoomObj *o)
{
    int32_t s = room_scale(POS(o, 1)), lift = div32(s * room.floor_k, 2000);
    int16_t fy = (int16_t)(lift + room.eye_y), m;
    int32_t shift = div32((int32_t)(int16_t)(room.floor_y - fy) * 1000, room.shift_k);

    if ((m = POS_MODE(o, 0)) >= 6) {
        int32_t v = m == 8 ? POS(o, 0) : div32(screen_len(m, POS(o, 0)), 1000);
        POS(o, 0) = (int16_t)div32((v - shift - (int16_t)(room.w - room.vw) / 2) * 1000, s);
    }
    if ((m = POS_MODE(o, 2)) >= 6) {
        int32_t v = m == 8 ? POS(o, 2) : div32(screen_len(m, POS(o, 2)), 1000);
        POS(o, 2) = (int16_t)div32((lift - v + room.eye_y) * 1000, s);
    }
    if ((m = SIZE_MODE(o, 0)) >= 6)
        SIZE(o, 0) = (int16_t)div32(screen_len(m, SIZE(o, 0)), s);
    if ((m = SIZE_MODE(o, 2)) >= 6)
        SIZE(o, 2) = (int16_t)div32(screen_len(m, SIZE(o, 2)), s);
}

/* An object can be placed once its parent is (and, for a line, the
 * object its second end refers to). */
static int ready(const RoomObj *o)
{
    const RoomObj *p = obj_at(o->parent), *q = obj_at(o->parent2);

    if (o->done || !p || !p->done)
        return 0;
    if (o->type == 1 || o->type == 3 || o->type == 4 || o->type == 5)
        return 1;
    return o->type == 2 && q && q->done;
}

/* 8:0a36: places every object, pass after pass until a pass places
 * none, then makes the colour ramps and sends the palette to the screen
 * (5:4378).  Object 0 (the room) is placed from the start. */
static void place_all(HPALETTE pal, HDC dc)
{
    int i, k, j, placed;

    rs.max_rect = -1;
    do {
        placed = 0;
        for (i = 1; i < rs.count; i++) {
            RoomObj *o = &rs.obj[i];
            if (!ready(o))
                continue;
            for (k = 0; k < 3; k++)
                place_axis(o, k);
            place_on_screen(o);
            o->done = 1;
            if (o->rect > rs.max_rect)
                rs.max_rect = o->rect;
            placed = 1;
        }
    } while (placed);
    for (j = 0; j < room_hdr_word(0x24) && j < ROOM_RAMPS; j++) {
        int16_t top = -1, n, c, step;
        room.ramp_channel[j] = 0;
        for (c = 0; c < 3; c++)
            if (room_hdr_word(6 * j + 2 * c) > top) {
                top = room_hdr_word(6 * j + 2 * c);
                room.ramp_channel[j] = (uint8_t)c;
            }
        c = room.ramp_channel[j];
        step = room_hdr_word(0x26 + 2 * j);
        n = step ? (int16_t)((int16_t)(room_hdr_word(6 * j + 2 * c) - room_hdr_word(0x2c + 6 * j + 2 * c)) / step) : 0;
        room.ramp_first[j] = (uint8_t)ispace_pal_first_black(pal);
        for (k = 0; k < n; k++) {
            int16_t rgb[3];
            for (c = 0; c < 3; c++) {
                int16_t lo = room_hdr_word(0x2c + 6 * j + 2 * c);
                rgb[c] = (int16_t)((int16_t)((room_hdr_word(6 * j + 2 * c) - lo) * k) / n + lo);
            }
            ispace_pal_add_color(pal, rgb[0], rgb[1], rgb[2]);
        }
        room.ramp_last[j] = (uint8_t)(ispace_pal_first_black(pal) - 1);
    }
    ispace_pal_animate(pal, 0, dc);
}

/* 8:5c86: the machine as Windows describes it: the display and sound
 * drivers' names from SYSTEM.INI and CONTROL.INI, the network card from
 * PROTOCOL.INI and NETWORK.INF, the wave device, the processor. */
static void cut_name(char *s, const char *stops)
{
    int i;

    for (i = 0; i < (int)strlen(s); i++)
        if ((i > 16 && s[i] == ' ') || strchr(stops, s[i]))
            s[i] = 0;
}

static void ini_path(char *path, size_t size, int system, const char *file)
{
    if (system)
        GetSystemDirectory(path, (UINT)size);
    else
        GetWindowsDirectory(path, (UINT)size);
    SDL_strlcat(path, file, size);
}

static void read_machine(void)
{
    char path[0x6e], key[0x28];
    WAVEOUTCAPS caps;
    DWORD flags;
    int i;

    ini_path(path, sizeof path, 0, "\\system.ini");
    GetPrivateProfileString("Boot.description", "display.drv", "Video Card", rs.video, sizeof rs.video, path);
    cut_name(rs.video, "(");
    GetPrivateProfileString("drivers", "Wave", "", key, sizeof key, path);
    ini_path(path, sizeof path, 0, "\\control.ini");
    GetPrivateProfileString("drivers.desc", key, "Sound Card", rs.sound, sizeof rs.sound, path);
    if (!strncmp(rs.sound, "Crea", 4))
        strcpy(rs.sound, "Sound Blaster");
    cut_name(rs.sound, "(");
    rs.wave = 1;
    rs.stereo = 0;
    if (!waveOutGetNumDevs()) {
        rs.wave = 0;
    } else {
        waveOutGetDevCaps(0, &caps, sizeof caps);
        if (caps.dwSupport & WAVECAPS_SYNC)
            rs.wave = 0;
        if (caps.wChannels > 1)
            rs.stereo = 1;
    }
    ini_path(path, sizeof path, 0, "\\protocol.ini");
    GetPrivateProfileString("network.setup", "netcard", "", key, sizeof key, path);
    for (i = 0; i < (int)strlen(key); i++)
        if (key[i] == ',')
            key[i] = 0;
    ini_path(path, sizeof path, 1, "\\network.inf");
    GetPrivateProfileString("netcard", key, "", rs.network, sizeof rs.network, path);
    if (rs.network[0] == '"')
        memmove(rs.network, rs.network + 1, strlen(rs.network));
    cut_name(rs.network, "(,\"");
    rs.fpu = -1;
    flags = GetWinFlags();
    if (flags & WF_CPU286) {
        rs.cpu_class = 2;
    } else if (flags & WF_CPU386) {
        rs.cpu_class = 3;
        if (flags & WF_80x87)
            rs.fpu = 1;
    } else if (flags & WF_CPU486) {
        rs.cpu_class = 4;
        rs.fpu = 0;
    } else {
        rs.cpu_class = 0;
    }
    SDL_snprintf(rs.cpu, sizeof rs.cpu, "%d", rs.cpu_class * 100 + 86);
}

/* Objects with a rectangle below -1 are drawn only when the machine has
 * what header byte 0x48 - rect asks for: 1 a 386 coprocessor, 2 a 486,
 * 3 a wave device, 4 no 486, 5 stereo. */
static int shown(const RoomObj *o)
{
    if (o->rect >= -1)
        return 1;
    switch ((int8_t)rs.hdr[0x48 - o->rect]) {
    case 1: return rs.fpu == 1;
    case 2: return rs.cpu_class > 3;
    case 3: return rs.wave != 0;
    case 4: return rs.cpu_class <= 3;
    case 5: return rs.stereo != 0;
    default: return 0;
    }
}

/* The text of a box: a string of the language DLL, or (-13 to -10) what
 * the machine is.  Other values leave it empty (the DLL draws whatever
 * its buffer held). */
static void box_text(const RoomObj *o, char *buf, int size)
{
    static const char *const machine[] = {rs.cpu, rs.video, rs.sound, rs.network};

    buf[0] = 0;
    if (TEXT(o) > 1)
        LoadString(ispace_lang_module(), (UINT)TEXT(o), buf, (int16_t)size);
    else if (TEXT(o) >= -13 && TEXT(o) <= -10)
        SDL_strlcpy(buf, machine[TEXT(o) + 13], (size_t)size);
}

static int16_t brightness(const RoomObj *o)
{
    int c = room.ramp_channel[o->ramp];

    return (int16_t)((int16_t)(room_hdr_word(2 * (3 * o->ramp + c)) * o->shade) / 50);
}

/* 8:15ec: the objects in their order in the room (8:1b66's sort is
 * never reached), each by its type; boxes with a rectangle report their
 * front face. */
static void draw_all(RECT *rects)
{
    int i;
    char buf[40];

    for (i = 1; i < rs.count; i++) {
        RoomObj *o = &rs.obj[i];
        int16_t ramp = o->ramp < ROOM_RAMPS ? o->ramp : -1, c = ramp >= 0 ? room.ramp_channel[ramp] : -1;
        int16_t b = ramp >= 0 ? brightness(o) : -1;
        if (ramp < 0 && o->rect < 0)
            continue;
        switch (o->type) {
        case 1:
            box_text(o, buf, sizeof buf);
            if (!shown(o))
                break;
            room_box(POS(o, 0), POS(o, 1), SIZE(o, 1), SIZE(o, 0), POS(o, 2), SIZE(o, 2),
                     ramp >= 0 ? o->f21 : 0, ramp >= 0 ? o->f22 : 0, 2, ramp, c, b, buf, o->f24,
                     o->f25, o->f23);
            break;
        case 2:
            room_line_point(POS(o, 0), POS(o, 1), POS(o, 2), 0, 0, 0xff, 2, 0);
            room_line_point(SIZE(o, 0), SIZE(o, 1), SIZE(o, 2), ramp, c, b, 2, 1);
            break;
        case 3:
            if (ramp >= 0)
                room_cylinder(POS(o, 0), POS(o, 1), POS(o, 2), SIZE(o, 0), SIZE(o, 1), SIZE(o, 2), ramp, c, b,
                              o->f21, 2);
            break;
        case 4:
            if (ramp >= 0)
                room_point(POS(o, 0), SIZE(o, 0), POS(o, 1), SIZE(o, 1), POS(o, 2), SIZE(o, 2),
                           (int16_t)(o->f21 * 10), ramp, c, b);
            break;
        case 5:
            win_stub("ispace_32: object type 5 (8:4206)");
            break;
        default:
            break;
        }
        if (o->type == 1 && o->rect >= 0 && rects && o->rect <= rs.max_rect)
            SetRect(&rects[o->rect], room.face.left, room.face.top, room.face.right, room.face.bottom + 1);
    }
}

/* The view: picture size, vanishing point and floor from the header
 * (longs at 0x5c-0x68, in thousandths of the width or height as bytes
 * 0x50 and 0x51 say; 8 pixels), x and y (when not both 0) replacing
 * the vanishing point's; lift raises object 2 (the ship [inferred]). */
static void set_view(int16_t w, int16_t h, int16_t x, int16_t y, int16_t lift)
{
    RoomObj *ship = obj_at(2);
    int32_t t;
    int a;

    room.w = w;
    room.h = h;
    room.vw = (int16_t)((int16_t)(h << 2) / 3);
    if (x || y) {
        for (a = 0; a < 4; a++) {
            rs.hdr[0x5c + a] = (uint8_t)((int32_t)x >> 8 * a);
            rs.hdr[0x60 + a] = (uint8_t)((int32_t)y >> 8 * a);
        }
    }
    if (rs.count > 2 && ship->rect == -20)
        POS(ship, 2) += lift;
    for (a = 0; a < 2; a++) {
        int16_t *v = a ? &rs.eye_y : &rs.eye_x;
        int32_t l = hdr_long(0x5c + 4 * a);
        switch (rs.hdr[0x50 + a]) {
        case 6: *v = (int16_t)div32(l * w, 1000); break;
        case 7: *v = (int16_t)div32(l * h, 1000); break;
        case 8: *v = (int16_t)l; break;
        default: break;
        }
    }
    room.eye_x = rs.eye_x;
    room.eye_y = rs.eye_y;
    room.dist = div32(hdr_long(0x64) * room.vw, 1000);
    room.floor_y = (int16_t)div32(hdr_long(0x68) * h, 1000);
    room.floor_k = div32((int32_t)room_hz() * 2000, room.vw);
    t = (int16_t)((int16_t)(room.vw - w) / 2 + room.eye_x);
    if (!t)
        t = 1;
    room.shift_k = div32((int32_t)room_hz() * 1000, t);
    if (!room.shift_k)
        room.shift_k = 1;
}

/* Ordinal 32 (8:0000).  The game passes room ids (100 the desk); the
 * DLL's own path for a room in the caller's memory (id -1, d and f) is
 * not used by the game and not ported.  rects (block hrects, locked)
 * gets the rectangles; it is grown as the DLL grows it. */
HBITMAP ispace_room(int16_t dc, int16_t pal, RECT *rects, HGLOBAL hrects, int16_t id, int32_t d,
                    int16_t e, int32_t f, int16_t g, int16_t w, int16_t h, int16_t y, int16_t x,
                    int16_t lift)
{
    HBITMAP bmp, old_bmp;
    HPALETTE old_pal = 0;

    (void)d;
    (void)e;
    (void)f;
    (void)g;
    if (id == -1 || !load_room(id)) {
        win_stub("ispace_32: room not loaded");
        return 0;
    }
    room.hdr = rs.hdr;
    room.pal = pal;
    set_view(w, h, x, y, lift);
    read_machine();
    place_all(pal, dc);
    if (rs.max_rect >= 0 && hrects) {
        if (GlobalReAlloc(hrects, (DWORD)(rs.max_rect + 1) << 3, GHND))
            rects = GlobalLock(hrects);
        else
            rects = NULL;
    } else {
        rects = NULL;
    }
    room.dc = CreateCompatibleDC(dc);
    bmp = CreateCompatibleBitmap(dc, w, h);
    old_bmp = SelectObject(room.dc, bmp);
    if (pal)
        old_pal = SelectPalette(room.dc, pal, 0);
    SetStretchBltMode(room.dc, COLORONCOLOR);
    PatBlt(room.dc, 0, 0, w, h, BLACKNESS);
    draw_all(rects);
    SelectObject(room.dc, old_bmp);
    if (old_pal)
        SelectPalette(room.dc, old_pal, 0);
    DeleteDC(room.dc);
    room.dc = 0;
    return bmp;
}
