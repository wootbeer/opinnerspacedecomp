/* ISPACE.DLL segment 8: the shapes of the rooms (ispace_room.h) drawn
 * into room.dc: faces filled in bands with their edges smoothed
 * (8:1fe6), boxes (8:28de), upright cylinders (8:3874), discs
 * (8:4206), lines (8:5470, 8:5632) and text (8:5978).  Every band is shaded by its
 * distance from the horizon on the floor below it. */

#include <stdlib.h>
#include <string.h>

#include "ispace_room.h"

static int32_t div32(int32_t a, int32_t b)
{
    return b ? a / b : 0;      /* the DLL faults on 0 */
}

static int16_t abs16(int16_t v)
{
    return (int16_t)(v < 0 ? -v : v);
}

/* d * k / step with the DLL's 16-bit product. */
static int16_t part(int16_t d, int16_t k, int16_t step)
{
    return (int16_t)((int16_t)(d * k) / step);
}

static void band(int16_t x, int16_t y, int16_t w, int16_t h)
{
    PatBlt(room.dc, x, y, w, h, PATCOPY);
}

/* The step of a band for an extent e. */
static int16_t band_step(int16_t e)
{
    return e < 20 ? 2 : e < 35 ? 3 : e < 45 ? 4 : 5;
}

/* 8:1fe6 for faces with level top and bottom edges: rows of step
 * pixels from the bottom edge (q[3]-q[2]) to the top one (q[0]-q[1]),
 * and between two rows wedges that follow the slanted side edges.  fy0
 * and fy1 are the floor's y below the bottom and top edges. */
static void face_rows(const POINT q[4], int16_t ramp, int16_t channel, int32_t two_b, int16_t fy0,
                      int16_t fy1)
{
    int16_t ex = (int16_t)(q[2].x - q[3].x), ey = (int16_t)(q[3].y - q[0].y), a, step, sgn;
    int16_t l, r, y, pl = 0, pr = 0, py = 0, k;
    int32_t dl = (int16_t)(q[0].x - q[3].x), dr = (int16_t)(q[1].x - q[2].x), t, u;

    if (!ey)
        ey = -1;
    sgn = ey < 0 ? -1 : 1;
    a = abs16(ey);
    step = band_step(a);
    for (t = 0; (int16_t)(a + step) >= t; t += step) {
        int32_t qy = 0;
        HBRUSH old;
        u = a > t ? t : a;
        qy = div32((int16_t)(fy0 - fy1) * u, ey);
        old = room_brush(room_color(ramp, channel, room_floor_light((int16_t)(sgn == 1 ? fy0 - qy : qy + fy0), two_b)));
        if (sgn == 1) {
            l = (int16_t)(div32(u * dl, ey) + q[3].x);
            r = (int16_t)(div32(u * (dr - dl), ey) + l + ex + 1);
            y = (int16_t)(q[0].y - u + ey);
        } else {
            l = (int16_t)(q[3].x - div32(u * dl, ey));
            r = (int16_t)(div32(u * (dl - dr), ey) + l + ex + 1);
            y = (int16_t)(q[0].y + u + ey);
        }
        band(l, y, (int16_t)(r - l), step);
        for (k = 1; u > 0 && k < step; k++) {
            if (sgn == 1) {
                if (pl > l)
                    band(pl, (int16_t)(py - k + step - 1), part((int16_t)(l - pl), k, step), 1);
                else if (pl < l)
                    band(l, (int16_t)(y + k), part((int16_t)(pl - l), k, step), 1);
                if (pr > r)
                    band(r, (int16_t)(y + k), part((int16_t)(pr - r), k, step), 1);
                else if (pr < r)
                    band(pr, (int16_t)(py - k + step - 1), part((int16_t)(r - pr), k, step), 1);
            } else {
                if (pl > l)
                    band(pl, (int16_t)(y - step + k), part((int16_t)(l - pl), k, step), 1);
                else if (pl < l)
                    band(l, (int16_t)(y + k - 1), part((int16_t)(pl - l), (int16_t)(step - k), step), 1);
                if (pr > r)
                    band(r, (int16_t)(y + k - 1), part((int16_t)(pr - r), (int16_t)(step - k), step), 1);
                else if (pr < r)
                    band(pr, (int16_t)(y - step + k), part((int16_t)(r - pr), k, step), 1);
            }
        }
        pl = l;
        pr = r;
        py = y;
        room_unbrush(old);
    }
}

/* 8:1fe6 for faces with upright left and right edges: columns from the
 * left edge (q[0]-q[3]) to the right one (q[1]-q[2]); fy0 and fy1 are
 * the floor's y below them. */
static void face_columns(const POINT q[4], int16_t ramp, int16_t channel, int32_t two_b, int16_t fy0,
                         int16_t fy1)
{
    int16_t ex = (int16_t)(q[2].x - q[3].x), ey = (int16_t)(q[3].y - q[0].y), step = band_step(ex);
    int16_t x, top, bottom, ptop = 0, pbottom = 0, k;
    int32_t du = (int16_t)(q[1].y - q[0].y), dd = (int16_t)(q[2].y - q[3].y), t, u;

    if (!ey)
        ey = -1;
    for (t = 0; (int16_t)(ex + step) >= t; t += step) {
        HBRUSH old;
        u = ex > t ? t : ex;
        old = room_brush(room_color(ramp, channel,
                                    room_floor_light((int16_t)(fy0 - div32((int16_t)(fy0 - fy1) * u, ex)), two_b)));
        x = (int16_t)(q[3].x + u);
        top = (int16_t)(div32(u * du, ex) + q[0].y);
        bottom = (int16_t)(div32(u * (dd - du), ex) + top + ey + 1);
        band(x, top, step, (int16_t)(bottom - top));
        for (k = 1; t > 0 && k < step; k++) {
            if (ptop > top)
                band((int16_t)(x - step + k), ptop, 1, part((int16_t)(top - ptop), k, step));
            else if (ptop < top)
                band((int16_t)(x + k - 1), top, 1, part((int16_t)(ptop - top), (int16_t)(step - k), step));
            if (pbottom > bottom)
                band((int16_t)(x + k - 1), bottom, 1, part((int16_t)(pbottom - bottom), (int16_t)(step - k), step));
            else if (pbottom < bottom)
                band((int16_t)(x - step + k), pbottom, 1, part((int16_t)(bottom - pbottom), k, step));
        }
        ptop = top;
        pbottom = bottom;
        room_unbrush(old);
    }
}

/* 8:1fe6: face q (top-left, top-right, bottom-right, bottom-left) in
 * colour ramp at brightness b; rows when across is set, else columns.
 * The DLL's step argument is overwritten (5, less for small faces). */
void room_face(const POINT q[4], int16_t ramp, int16_t channel, int16_t b, int16_t fy0,
               int16_t fy1, int16_t step, int16_t across)
{
    int32_t two_b = (int16_t)(b * 2);

    (void)step;
    if (across)
        face_rows(q, ramp, channel, two_b, fy0, fy1);
    else
        face_columns(q, ramp, channel, two_b, fy0, fy1);
}

/* What a box looks like at depth y: the floor's y below it, its top
 * edge, left and right ends and its scaled sizes. */
typedef struct {
    int32_t s, w, h, z;
    int16_t fy, top, left, right;
} BoxView;

static BoxView box_view(int32_t x, int32_t y, int32_t w, int32_t z, int32_t h, int16_t vents_div)
{
    BoxView v;
    int16_t cx;
    int32_t half;

    v.s = room_scale(y);
    v.fy = room_floor_y(v.s);
    v.z = div32(z * v.s, 1000);
    v.h = div32(h * v.s, vents_div);
    v.w = div32(w * v.s, 1000);
    v.top = (int16_t)(v.fy - (int16_t)v.h - (int16_t)v.z);
    cx = room_screen_x(v.fy, (int16_t)div32(x * v.s, 1000));
    half = div32(v.w, 2);
    v.left = (int16_t)(cx - (int16_t)half);
    v.right = (int16_t)((int16_t)half + cx);
    return v;
}

/* 8:28de: the slots (vents) on a box's right or left side, at n depths
 * from its front. */
static void box_vents(int32_t x, int32_t y, int32_t d, int32_t w, int32_t z, int32_t h, int16_t n,
                      int right)
{
    int16_t j;

    for (j = 0; j < n; j++) {
        BoxView v = box_view(x, div32((int32_t)j * d, n) + y, w, z, h, 2000);
        int32_t sw = div32(v.s * (int16_t)div32(div32(d, n), 6), 1500);
        int16_t q = (int16_t)(v.h >> 1), mid = v.top, dy = (int16_t)(v.fy - room.eye_y);
        int16_t sw16 = (int16_t)(sw < 1 ? 1 : sw), light, x0, x1;
        HBRUSH old;
        if (right) {
            light = (int16_t)((int16_t)(div32((int32_t)dy * 1800, room_hz()) + 0x280) >> 4);
            x0 = v.right;
            x1 = (int16_t)(v.right + (sw16 >> 2));
        } else {
            light = (int16_t)((int16_t)(div32((int32_t)dy * 2048, room_hz()) + 0x300) >> 4);
            x0 = (int16_t)(v.left - sw16);
            x1 = (int16_t)(v.left - (sw16 >> 2) - sw16);
        }
        old = room_brush(room_color(0, 0, (int16_t)((int16_t)(light << 2) / 5)));
        band(x0, mid, sw16, q);
        room_unbrush(old);
        old = room_brush(room_color(0, 0, light));
        band(x1, (int16_t)(mid + q), sw16, q);
        room_unbrush(old);
    }
}

/* 8:28de: the "HIGH VOLTAGE" sign on a front face. */
static void danger_sign(int16_t left, int16_t top, int32_t wd, int32_t hd, int16_t size, int16_t fy)
{
    int16_t cx = (int16_t)((int16_t)wd / 2 + left), sz = (int16_t)((int16_t)((int16_t)wd * size) / 100);
    int16_t ty = (int16_t)((int16_t)hd / 3 + top), up = (int16_t)((int16_t)(sz + sz) / -3);
    int16_t bw = (int16_t)((int16_t)(sz * 13) / 3), bh = (int16_t)((int16_t)(sz * 5) / 2);

    ispace_bevel(room.dc, (int16_t)(cx - 2 * sz), (int16_t)(ty + up), bw, (int16_t)(bh + 5), 2);
    ispace_bevel(room.dc, (int16_t)((3 - sz) * 2 + cx), (int16_t)(up + ty + 6), (int16_t)(bw - 12), (int16_t)(bh - 7), 3);
    room_text(cx, ty, sz, "HIGH", 3, fy, 192, 0, 0);
    room_text(cx, (int16_t)(ty + sz), sz, "VOLTAGE", 3, fy, 192, 0, 0);
}

/* 8:28de: the front face, a texture (100 METAL, 120 image 76) or the
 * ramp's colour; a black screen inset; slots across it (2-99). */
static void box_front(int32_t y, int32_t w, int16_t front, int16_t inset, int16_t ramp, int16_t channel,
                      int32_t two_b, int16_t fy, int16_t left, int16_t left2, int16_t top, int32_t hd,
                      const char *text, int16_t text_face, int16_t text_kind, int16_t text_size)
{
    int32_t s = room_scale(y), wd = div32(w * s, 1000);
    int16_t light = (int16_t)((int16_t)div32(div32(two_b * 12, 13) * (int16_t)(fy - room.eye_y), room_hz()) >> 1);
    HBRUSH old;

    if (left > left2) {
        left += 2;
        wd -= 2;
    }
    if (front >= 100) {
        char none[1] = "";
        HBITMAP bm = front == 100 ? (HBITMAP)ispace_load_bitmap("METAL")
                   : front == 120 ? (HBITMAP)ispace_load_image(room.pal, 0x4c, none, room.dc, 0, -1) : 0;
        front = 0;
        old = SelectObject(room.dc, CreatePatternBrush(bm));
        band(left, top, (int16_t)wd, (int16_t)((int16_t)hd + 1));
        room_unbrush(old);
        DeleteObject(bm);
    } else {
        old = room_brush(room_color(ramp, channel, light));
        band(left, top, (int16_t)wd, (int16_t)((int16_t)hd + 1));
        room_unbrush(old);
    }
    SetRect(&room.face, left, top, (int16_t)(wd + left), (int16_t)((int16_t)hd + top));
    if (inset) {
        int16_t m = (int16_t)(wd >> 3), e = (int16_t)((int16_t)wd - (int16_t)(wd >> 2));
        PatBlt(room.dc, (int16_t)(m + left), (int16_t)(m + top), e, e, BLACKNESS);
    }
    if (text_size && text_face) {
        if (!text_kind) {
            int16_t sz = (int16_t)((int16_t)((int16_t)wd * text_size) / 100);
            room_text((int16_t)((int16_t)wd / 20 + left), (int16_t)((int16_t)hd / 17 + top), sz, text, 2, fy, 300, 260,
                      100);
        } else if (text[0] == 'H') {
            danger_sign(left, top, wd, hd, text_size, fy);
        }
    }
    if (front) {
        int16_t mid = (int16_t)((int16_t)(hd >> 1) + top), q = (int16_t)(hd >> 2), j;
        int16_t sw = (int16_t)div32(wd, (int16_t)(front * 5)), sx = (int16_t)(sw + left);
        for (j = 0; j < front; j++) {
            old = room_brush(room_color(0, 0, (int16_t)((int16_t)(light * 7) / 4)));
            band((int16_t)(sx - sw), mid, sw, (int16_t)(q + 1));
            room_unbrush(old);
            old = room_brush(room_color(ramp, channel, (int16_t)(light * 2)));
            band((int16_t)(sx - sw), (int16_t)(q + mid + 1), sw, (int16_t)(q + 1));
            room_unbrush(old);
            sx = (int16_t)(sx + div32(wd - sw, (int16_t)(front - 1)));
        }
    }
}

/* 8:28de: a box with its front at depth y, d deep, centred on x, from
 * z up h high.  Its lid or bottom, the side facing the middle and its
 * front are drawn (in that order); room.face gets the front's
 * rectangle.  With ramp -1 only that rectangle is worked out. */
void room_box(int32_t x, int32_t y, int32_t d, int32_t w, int32_t z, int32_t h, int16_t front,
              int16_t vents, int16_t step, int16_t ramp, int16_t channel, int16_t b, const char *text,
              int16_t text_face, int16_t text_kind, int16_t text_size)
{
    BoxView f, k;
    POINT q[4], s[4];
    int16_t inset = front == 1;

    if (b < 0)
        b = (int16_t)-(b * 10);
    if (inset)
        front = 0;
    f = box_view(x, y, w, z, h, 1000);
    SetRect(&room.face, f.left, f.top, (int16_t)(f.left + (int16_t)f.w), (int16_t)(f.top + (int16_t)f.h));
    if (ramp == -1)
        return;
    k = box_view(x, y + d, w, z, h, 1000);
    q[0].x = k.left;
    q[1].x = k.right;
    q[0].y = q[1].y = k.top;
    q[2].x = f.right;
    q[3].x = f.left;
    q[2].y = q[3].y = f.top;
    if (f.top > room.eye_y) {
        room_face(q, ramp, channel, b, f.fy, k.fy, step, 1);
        if (text_size && !text_face && text_size != 1000) {
            int16_t sz = (int16_t)((int16_t)((k.right - f.left - k.left + f.right) * text_size) / 200);
            room_text((int16_t)((int16_t)(f.right + f.left) / 2), (int16_t)((int16_t)(k.top + f.top) / 2), sz, text, 1,
                      (int16_t)((int16_t)(k.fy + f.fy) / 2), 300, 300, 300);
        }
    } else if ((int16_t)((int16_t)f.h + f.top) < room.eye_y) {
        q[0].y = q[1].y = (int16_t)(k.top + (int16_t)k.h);
        q[2].y = q[3].y = (int16_t)(f.top + (int16_t)f.h);
        room_face(q, ramp, channel, b, f.fy, k.fy, step, 1);
    }
    if (k.right > f.right) {
        s[0].x = s[3].x = f.right;
        s[1].x = s[2].x = k.right;
        s[0].y = f.top;
        s[3].y = (int16_t)(f.top + (int16_t)f.h);
        s[1].y = k.top;
        s[2].y = (int16_t)(k.top + (int16_t)k.h);
        room_face(s, ramp, channel, (int16_t)((int16_t)(b * 3) / 4), f.fy, k.fy, step, 0);
        box_vents(x, y, d, w, z, h, vents, 1);
    } else if (f.left > k.left) {
        s[0].x = s[3].x = k.left;
        s[1].x = s[2].x = f.left;
        s[0].y = k.top;
        s[3].y = (int16_t)(k.top + (int16_t)k.h);
        s[1].y = f.top;
        s[2].y = (int16_t)(f.top + (int16_t)f.h);
        room_face(s, ramp, channel, (int16_t)((int16_t)(b * 5) / 4), k.fy, f.fy, step, 0);
        box_vents(x, y, d, w, z, h, vents, 0);
    }
    box_front(y, w, front, inset, ramp, channel, (int16_t)(b * 2), f.fy, f.left, k.left, f.top, f.h, text,
              text_face, text_kind, text_size);
}

/* The floor light before the DLL halves it (8:3874 shades its side
 * with it). */
static int16_t floor_light2(int16_t fy, int32_t two_b)
{
    int32_t hz = room_hz(), d = (int16_t)(fy - room.eye_y);

    return (int16_t)div32(d * d * two_b, hz * hz);
}

/* 8:3874: the half-height of a cylinder's ellipse (radii rx, ry) at
 * column i of its width wc. */
static int16_t ellipse_at(int32_t i, int32_t wc, int32_t rx, int32_t ry)
{
    int32_t half = div32(wc, 2), p = i - half;
    int32_t sq = ry * ry + div32((half - i) * ry, rx) * div32(p * ry, rx);

    return ispace_newton_root(sq, labs(ry) - labs(div32(p * ry, rx + rx)));
}

/* 8:3874: an upright cylinder with its front at depth y, d deep, w
 * wide, from z up h high: its side in columns lit from the front, a
 * "+" (mark 1, the batteries), and its lid when seen from above. */
void room_cylinder(int32_t x, int32_t y, int32_t z, int32_t w, int32_t d, int32_t h, int16_t ramp,
                   int16_t channel, int16_t b, int16_t mark, int16_t step)
{
    int32_t two_b = (int16_t)(b * 2), s1 = room_scale(y), sc = room_scale(div32(d, 2) + y), wc, rx, ry0, ry1, i;
    int16_t fy1 = room_floor_y(s1), fyc = room_floor_y(sc), h1 = (int16_t)div32(h * s1, 1000);
    int16_t cx = room_screen_x(fyc, (int16_t)div32(x * sc, 1000)), left, right, half16;
    int16_t base_f = (int16_t)(fy1 - (int16_t)div32(z * s1, 1000));
    int16_t base_c = (int16_t)(fyc - (int16_t)div32(z * sc, 1000));
    int16_t top_c = (int16_t)(base_c - (int16_t)div32(h * sc, 1000)), top_f = (int16_t)(base_f - h1);
    int16_t e[2], j, pl = 0, pr = 0;
    HBRUSH old;

    wc = div32(w * sc, 1000);
    left = (int16_t)(cx - (int16_t)div32(wc, 2));
    right = (int16_t)((int16_t)div32(wc, 2) + cx);
    rx = (int16_t)((int16_t)(right - left) / 2);
    ry0 = (int16_t)(base_f - base_c);
    ry1 = (int16_t)(top_f - top_c);
    if (!ry1)
        ry1 = 1;
    if (!ry0)
        ry0 = 1;
    for (i = 0; i < wc; i += step) {
        int32_t lit, shade;
        int16_t v;
        e[0] = ellipse_at(i, wc, rx, ry0);
        e[1] = ellipse_at(i, wc, rx, ry1);
        if (base_c > base_f)
            e[0] = (int16_t)-e[0];
        if (top_c > top_f)
            e[1] = (int16_t)-e[1];
        v = (int16_t)(div32((int16_t)((int16_t)(fy1 - fyc) * e[0]), ry0) + fyc);
        lit = div32((rx - i) * (i - rx) * 128, rx * rx) + 0xc0;
        shade = div32((int32_t)floor_light2(v, two_b) * lit, 128);
        if (shade > 0xfff)
            shade = 0xfff;
        old = room_brush(room_color(ramp, channel, (int16_t)(shade >> 1)));
        band((int16_t)(left + i), (int16_t)(top_c + e[1]), step, (int16_t)(base_c - top_c - e[1] + e[0]));
        room_unbrush(old);
    }
    if (mark == 1) {
        int16_t lw = (int16_t)wc / 3, lh = (int16_t)wc / 10, y6 = (int16_t)(h1 / 6);
        if (!(lw & 1))
            lw++;
        if (!(lh & 1))
            lh++;
        old = room_brush(room_color(0, 0, (int16_t)((int16_t)div32((int32_t)(int16_t)(fy1 - room.eye_y) * 4096,
                                                                     room_hz()) >> 4)));
        half16 = (int16_t)((int16_t)wc / 2);
        band((int16_t)(half16 - lh / 2 + left), (int16_t)(y6 + top_f), lh, lw);
        band((int16_t)(half16 - lw / 2 + left), (int16_t)(lw / 2 + (y6 - lh / 2) + top_f), lw, lh);
        room_unbrush(old);
    }
    step = ry1 < 12 ? 2 : ry1 < 25 ? 3 : 4;
    if (top_c <= room.eye_y)
        return;
    for (j = (int16_t)-ry1; j <= ry1; j += step) {
        int32_t g = div32((int32_t)j * rx, ry1), sq = rx * rx - g * g, m;
        int16_t hw, l, r, y0, k, v;
        g = div32((int32_t)j * rx, ry1 + ry1);
        m = labs(rx) - labs(g);
        if (div32(rx * 9, 10) < labs(g))
            m = 0;
        hw = ispace_newton_root(sq, m);
        v = (int16_t)(fyc - div32((int16_t)((int16_t)(fy1 - fyc) * j), ry0));
        old = room_brush(room_color(ramp, channel, room_floor_light(v, two_b)));
        l = (int16_t)((int16_t)(left + right) / 2 - hw);
        y0 = (int16_t)(top_c - j);
        band(l, y0, (int16_t)(hw * 2), step);
        r = (int16_t)(hw * 2 + l);
        for (k = 1; -ry1 < j && k < step; k++) {
            if (pl > l)
                band(pl, (int16_t)(y0 + k + step - 1), part((int16_t)(l - pl), (int16_t)(step - k), step), 1);
            else if (pl < l)
                band(l, (int16_t)(y0 + k), part((int16_t)(pl - l), k, step), 1);
            if (pr > r)
                band(r, (int16_t)(y0 + k), part((int16_t)(pr - r), k, step), 1);
            else if (pr < r)
                band(pr, (int16_t)(y0 + k + step - 1), part((int16_t)(r - pr), (int16_t)(step - k), step), 1);
        }
        pl = l;
        pr = r;
        room_unbrush(old);
    }
}

/* 8:4206: where the rim of a disc meets column xi at depth y: the
 * screen x, the floor's y, and the screen y of its bottom (z) and top
 * (z + h). */
typedef struct {
    int16_t x, fy, base, top;
} RimPoint;

static RimPoint rim_point(int32_t xi, int32_t y, int32_t z, int32_t h)
{
    int32_t s = room_scale(y);
    RimPoint p;

    p.fy = room_floor_y(s);
    p.x = room_screen_x(p.fy, (int16_t)div32(xi * s, 1000));
    p.base = (int16_t)(p.fy - (int16_t)div32(z * s, 1000));
    p.top = (int16_t)(p.base - (int16_t)div32((int16_t)s * h, 1000));
    return p;
}

/* 8:4206: half the chord of a circle of radius rw at p from its
 * centre. */
static int16_t disc_root(int32_t rw, int32_t p)
{
    return ispace_newton_root(rw * rw - p * p, labs(rw) - div32(labs(p) * 3, 4));
}

/* 8:4206: the disc's side along its far or near half, in columns step
 * apart lit from the front; a column is drawn where the rim runs right
 * to left (far half) or left to right (near half). */
static void disc_side(int32_t x, int32_t y, int32_t z, int32_t w, int32_t h, int32_t step, int back,
                      int16_t ramp, int16_t channel, int32_t two_b)
{
    int32_t rw = div32(w, 2), x0 = x - rw, xi;
    RimPoint prev, cur = {0, 0, 0, 0};

    for (xi = x0; xi < x + rw; xi += step) {
        int32_t p = xi - x, lit, shade;
        int16_t r = disc_root(rw, p);
        HBRUSH old;

        prev = cur;
        cur = rim_point(xi, (back ? r : -r) + rw + y, z, h);
        if (xi <= x0 || (back ? prev.x <= cur.x : prev.x >= cur.x))
            continue;
        lit = div32(-(p * p) * 128, rw * rw) + 0xc0;
        shade = div32((int32_t)floor_light2(cur.fy, two_b) * lit, 128);
        if (shade > 0xfff)
            shade = 0xfff;
        old = room_brush(room_color(ramp, channel, (int16_t)(shade >> 1)));
        band(prev.x, prev.top, (int16_t)(cur.x - prev.x), (int16_t)(prev.base - prev.top));
        room_unbrush(old);
    }
}

/* 8:4206: the lid of the disc in rows from the back, with wedges along
 * its rim between rows (one row's left, right and top: l, r, t; the row
 * before's left and right: pl, pr; the row's height n). */
static void disc_wedges(int16_t l, int16_t r, int16_t t, int16_t pl, int16_t pr, int16_t n)
{
    int16_t k;

    for (k = 1; k < n; k++) {
        if (pl > l)
            band(pl, (int16_t)(t - n + k), part((int16_t)(l - pl), k, n), 1);
        else if (pl < l)
            band(l, (int16_t)(t - k + n - 1), part((int16_t)(pl - l), k, n), 1);
        if (pr > r)
            band(r, (int16_t)(t - k + n - 1), part((int16_t)(pr - r), k, n), 1);
        else if (pr < r)
            band(pr, (int16_t)(t - n + k), part((int16_t)(r - pr), k, n), 1);
    }
}

static void disc_lid(int32_t x, int32_t y, int32_t z, int32_t w, int32_t h, int32_t step, int16_t ramp,
                     int16_t channel, int32_t two_b)
{
    int32_t rw = div32(w, 2), yi;
    int16_t l = 0, r = 0, t = 0, pl = 0, pr = 0;

    for (yi = w + y; y - step < yi; yi -= step) {
        int32_t s = room_scale(yi);
        int16_t root = disc_root(rw, yi - (rw + y)), fy = room_floor_y(s), pl2 = l, pr2 = r, pt = t, n;
        HBRUSH old;

        l = room_screen_x(fy, (int16_t)div32((x - root) * s, 1000));
        r = room_screen_x(fy, (int16_t)div32((x + root) * s, 1000));
        t = (int16_t)(fy + (int16_t)div32((int16_t)s * h, -1000) - (int16_t)div32((int16_t)s * z, 1000));
        if (yi >= w + y)
            continue;
        n = (int16_t)(t - pt);
        old = room_brush(room_color(ramp, channel, room_floor_light(fy, two_b)));
        band(pl2, pt, (int16_t)(pr2 - pl2), n);
        if (w + y - step > yi)
            disc_wedges(pl2, pr2, pt, pl, pr, n);
        pl = pl2;
        pr = pr2;
        room_unbrush(old);
    }
}

/* 8:4206: a disc lying on the floor (rooms 110 and 115): w across and w
 * deep from depth y, centred on x, from z up h high; its size on the
 * screen is taken at depth y + d / 2.  Its side, then its lid when seen
 * from above. */
void room_disc(int32_t x, int32_t y, int32_t z, int32_t w, int32_t d, int32_t h, int16_t ramp,
               int16_t channel, int16_t b)
{
    int32_t two_b = (int16_t)(b * 2), s1 = room_scale(y), sc = room_scale(div32(d, 2) + y), wc, rx, ry, step;
    int16_t fy1 = room_floor_y(s1), fyc = room_floor_y(sc);
    int16_t cx = room_screen_x(fyc, (int16_t)div32(x * sc, 1000)), left, right;
    int16_t base_c = (int16_t)(fyc - (int16_t)div32(z * sc, 1000));
    int16_t top_c = (int16_t)(base_c - (int16_t)div32(h * sc, 1000));
    int16_t top_f = (int16_t)(fy1 - (int16_t)div32(z * s1, 1000) - (int16_t)div32(h * s1, 1000));

    wc = div32(w * sc, 1000);
    left = (int16_t)(cx - (int16_t)div32(wc, 2));
    right = (int16_t)((int16_t)div32(wc, 2) + cx);
    rx = (int16_t)((int16_t)(right - left) / 2);
    ry = (int16_t)(top_f - top_c);
    if (!ry)
        ry = 1;
    step = div32(w, rx);
    if (step) {                         /* [fix: 0 loops for ever in the DLL] */
        disc_side(x, y, z, w, h, step, 1, ramp, channel, two_b);
        disc_side(x, y, z, w, h, step, 0, ramp, channel, two_b);
    }
    step = div32(w, ry < 2 ? 2 : ry);
    if (top_c > room.eye_y && step)
        disc_lid(x, y, z, w, h, step, ramp, channel, two_b);
}

/* 8:50ec: a flat point (the star of a pentagram) at height t from
 * three floor points (x, y): its base edge across (x1, y1), its middle
 * at (x2, y2) and its tip at (x3, y3); two faces, base to middle and
 * middle to tip. */
void room_point(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t t,
                int16_t ramp, int16_t channel, int16_t b)
{
    int32_t s1 = room_scale(y1), s2 = room_scale(y2), s3 = room_scale(y3);
    int16_t fy1 = room_floor_y(s1), fy2 = room_floor_y(s2), fy3 = room_floor_y(s3);
    int16_t sx1 = room_screen_x(fy1, (int16_t)div32(x1 * s1, 1000));
    int16_t sx2 = room_screen_x(fy2, (int16_t)div32(x2 * s2, 1000));
    int16_t sx3 = room_screen_x(fy3, (int16_t)div32(x3 * s3, 1000));
    int16_t mx = (int16_t)(sx1 - div32((int32_t)(int16_t)(sx1 - sx3) * (int16_t)(fy1 - fy2), (int16_t)(fy1 - fy3)));
    POINT q[4];

    q[0].x = mx;
    q[1].x = sx2;
    if (mx > sx2) {
        q[0].x = sx2;
        q[1].x = mx;
    }
    q[0].y = q[1].y = (int16_t)(fy2 - (int16_t)div32(t * s2, 1000));
    q[2].x = q[3].x = sx1;
    q[2].y = q[3].y = (int16_t)(fy1 - (int16_t)div32(t * s1, 1000));
    room_face(q, ramp, channel, b, fy1, fy2, 2, 1);
    q[3].x = q[0].x;
    q[2].x = q[1].x;
    q[2].y = q[3].y = q[0].y;
    q[0].x = q[1].x = sx3;
    q[0].y = q[1].y = (int16_t)(fy3 - (int16_t)div32(t * s3, 1000));
    room_face(q, ramp, channel, b, fy2, fy3, 2, 1);
}

/* 8:5632: a line from a down to b (or, level, from left to right), in
 * pieces of 5 rows shaded by the floor's y (fy_a at a, fy_b at b). */
static void line_part(POINT a, POINT b, int16_t ramp, int16_t channel, int16_t bright, int16_t fy_b,
                      int16_t fy_a, int16_t width)
{
    int16_t dy = (int16_t)(b.y - a.y), sgn = dy < 0 ? -1 : 1;
    int32_t two_b = (int16_t)(bright * 2), dx = (int16_t)(b.x - a.x), t;


    if (width == 200)
        return;
    if (!dy) {
        HBRUSH old = room_brush(room_color(ramp, channel, room_floor_light(fy_a, two_b)));
        band((int16_t)a.x, (int16_t)a.y, (int16_t)(b.x - a.x), width);
        room_unbrush(old);
    }
    if (width == 100) {
        HPEN old = SelectObject(room.dc, CreatePen(PS_SOLID, 2, RGB(0, 0, 0)));
        MoveTo(room.dc, (int16_t)a.x, (int16_t)a.y);
        LineTo(room.dc, (int16_t)(dx + a.x), (int16_t)(dy + a.y));
        DeleteObject(SelectObject(room.dc, old));
        return;
    }
    for (t = 0; abs16(dy) > t; t += 5) {
        int32_t q = div32((int16_t)(fy_a - fy_b) * t, dy), n;
        int16_t v = (int16_t)(sgn == 1 ? fy_a - q : q + fy_a);
        HPEN old = SelectObject(room.dc, CreatePen(PS_SOLID, width,
                                                   room_color(ramp, channel, room_floor_light(v, two_b))));
        if (!t)
            MoveTo(room.dc, (int16_t)a.x, (int16_t)a.y);
        if (sgn == 1)
            n = t + 5 <= dy ? t + 5 : dy;
        else
            n = -5 - t >= dy ? -5 - t : dy;
        LineTo(room.dc, (int16_t)(div32(n * dx, dy) + a.x), (int16_t)(n + a.y));
        DeleteObject(SelectObject(room.dc, old));
    }
}

/* 8:5470: the point (x, y, z) on the screen as a line's first (draw 0)
 * or second end; the second draws the line from the first, which it
 * then becomes. */
void room_line_point(int32_t x, int32_t y, int32_t z, int16_t ramp, int16_t channel, int16_t b,
                     int16_t width, int16_t draw)
{
    int32_t s = room_scale(y);
    int16_t fy = room_floor_y(s);
    POINT *p = room.line_pt;

    p[draw].y = (int16_t)(fy - (int16_t)div32(z * s, 1000));
    p[draw].x = room_screen_x(fy, (int16_t)div32(x * s, 1000));
    if (draw) {
        if (p[0].y < p[1].y)
            line_part(p[0], p[1], ramp, channel, b, fy, room.line_floor, width);
        else if (p[0].y > p[1].y)
            line_part(p[1], p[0], ramp, channel, b, room.line_floor, fy, width);
        else if (p[1].x < p[0].x)
            line_part(p[1], p[0], ramp, channel, b, room.line_floor, fy, width);
        else if (p[1].x > p[0].x)
            line_part(p[0], p[1], ramp, channel, b, fy, room.line_floor, width);
        p[0] = p[1];
    }
    room.line_floor = fy;
}

/* 8:5978: text in Arial, shaded like the floor at fy from colour (r,
 * g, b) in sixteenths: kind 1 centred (a lid), 2 from the left (a
 * front), 3 bold and centred (the danger sign). */
void room_text(int16_t x, int16_t y, int16_t size, const char *s, int16_t kind, int16_t fy, int16_t r,
               int16_t g, int16_t b)
{
    int16_t rgb[3] = {(int16_t)(r * 16), (int16_t)(g * 16), (int16_t)(b * 16)}, c[3], k;
    int16_t height = kind == 1 ? size / 6 : kind == 2 || kind == 3 ? size / 2 : 0;
    HFONT font = CreateFont(height, (int16_t)(kind >= 1 && kind <= 3 ? size / 3 : 0), 0, 0, kind == 3 ? 700 : 0, 0, 0,
                            0, 0, 0, 0, 2, 0x22, "Arial");
    HGDIOBJ old_font = SelectObject(room.dc, font);
    COLORREF old_bk = SetBkColor(room.dc, 0), old_text;

    SetBkMode(room.dc, TRANSPARENT);
    if (kind == 1 || kind == 3) {
        SetTextAlign(room.dc, TA_CENTER);
        y = (int16_t)(y + size / -12);
    } else if (kind == 2) {
        SetTextAlign(room.dc, TA_LEFT);
    }
    for (k = 0; k < 3; k++) {
        c[k] = (int16_t)div32((int32_t)rgb[k] * (int16_t)(fy - room.eye_y), room_hz());
        if (c[k]) {
            c[k] = (int16_t)(c[k] + 400);
            if (c[k] > 0xff0)
                c[k] = 0xff0;
        }
    }
    old_text = SetTextColor(room.dc, PALETTERGB((uint8_t)(c[0] >> 4), (uint8_t)(c[1] >> 4), (uint8_t)(c[2] >> 4)));
    TextOut(room.dc, x, y, s, (int16_t)strlen(s));
    SetBkColor(room.dc, old_bk);
    SetTextColor(room.dc, old_text);
    SelectObject(room.dc, old_font);
    DeleteObject(font);
}
