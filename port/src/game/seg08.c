/* INSPACE.EXE segment 8 (selector 1038), /G3 parts.
 * 8:3688..81f8 was compiled with /G2: see seg08b.c; 8:8256 to the end is
 * another source file: see seg08c.c. */
#include "game.h"

                                                                             

/* 8:0764 */
void fn_08_0764(int16_t a, int16_t b)
{
    int16_t i;
    POINT pt;

    for (i = 0; i < g_6098[a].count; i++) {
        pt.x = g_6098[a].f_30[i][b];
        pt.y = g_6098[a].f_48[i][b];
        pt = fn_08_29ea(pt);
        g_6098[a].x[i][b] = pt.x;
        g_6098[a].y[i][b] = pt.y;
    }
}

/* 8:07d2 */
void fn_08_07d2(int16_t a, int16_t b, int16_t c)
{
    POINT u;
    POINT t;

    t = fn_08_29ea(g_2414[a][b][c].s);
    g_2414[a][b][c].p.x = t.x;
    g_2414[a][b][c].p.y = t.y;
    g_2414[a][b][c].q.x = g_2414[a][b][c].r.x;
    g_2414[a][b][c].q.y = g_2414[a][b][c].r.y;
    g_2414[a][b][c].r.x = g_2414[a][b][c].p.x;
    g_2414[a][b][c].r.y = g_2414[a][b][c].p.y;
}

/* 8:083e */
void fn_08_083e(int16_t a, int16_t b)
{
    POINT u;
    POINT t;

    t = fn_08_29ea(g_5b28[a][b].s);
    g_5b28[a][b].p.x = t.x;
    g_5b28[a][b].p.y = t.y;
    g_5b28[a][b].q.x = g_5b28[a][b].r.x;
    g_5b28[a][b].q.y = g_5b28[a][b].r.y;
    g_5b28[a][b].r.x = g_5b28[a][b].p.x;
    g_5b28[a][b].r.y = g_5b28[a][b].p.y;
}

/* 8:124a */
void fn_08_124a(int16_t i)
{
    g_58bc[i].b.x = g_58bc[i].a.x;
    g_58bc[i].b.y = g_58bc[i].a.y;
    g_58bc[i].a = fn_08_29ea(g_58bc[i].c);
}

/* Draw object ref (type << 8 | idx) with sprite DC dc: erase the uncovered
 * part of the old position, then blit [inferred]. mode 4 only moves the
 * object; 6 inverts, 7 plots a dot. Returns 0 for hidden objects.
 * The gotos reproduce the shared return blocks at the end. */
/* 8:0b76 */
int16_t fn_08_0b76(WORD ref, int16_t mode, HDC dc, int16_t c)
{
    int16_t type;
    int16_t idx;
    int16_t u8;
    DWORD rop;
    POINT d;
    int16_t u12;
    int16_t u14;
    int16_t draw;

    draw = 1;
    type = HIBYTE(ref);
    idx = LOBYTE(ref);
    if (g_1df8[type][idx].f_1a == 0 && type != 7 && mode != 4 && mode != 5
        && g_1df8[type][idx].f_32 == -1)
        goto hidden;
    if (type != g_9324 || idx != main_ship || g_951a != 0 || g_238e != 0) {
        if (type != g_9324 || idx != main_ship || g_951a != 0) {
            g_1df8[type][idx].f_08.x = g_1df8[type][idx].f_00.x;
            g_1df8[type][idx].f_08.y = g_1df8[type][idx].f_00.y;
            g_1df8[type][idx].f_00 = fn_08_29ea(g_1df8[type][idx].f_04);
        } else if (g_238c == 0) {
            g_1df8[type][idx].f_00.x = LO16(g_90ea) / 2;
            g_1df8[type][idx].f_00.y = HI16(g_90ea) / 2;
            g_238e = 0;
        }
        if (mode == 4)
            goto done;
        if (mode == 5 && g_1df8[type][idx].f_1a == 0)
            goto done;
        g_1df8[type][idx].f_3a = dc;
        if (g_1df8[type][idx].f_2e != 0) {
            dc = g_1df8[type][idx].f_3c;
            g_1df8[type][idx].f_10 = g_1df8[type][idx].f_24;
            g_1df8[type][idx].f_12 = g_1df8[type][idx].f_24;
            if (g_1df8[type][idx].f_2e <= -1)
                draw = 0;
        }
        if (g_9e49 == 3 || g_9e49 == 6 && g_9e47 == 15) {
            if (type == g_9324 && idx == g_952e || type == 7) {
                dc = g_1df8[type][idx].f_3c;
                g_1df8[type][idx].f_10 = g_1df8[type][idx].f_24;
                g_1df8[type][idx].f_12 = g_1df8[type][idx].f_24;
            }
        }
        if (c != 0)
            rop = 0xc000ca;
        else
            rop = SRCCOPY;
        if (mode == 6 && draw) {
            BitBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
                   g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, dc,
                   g_1df8[type][idx].f_10, g_1df8[type][idx].f_12, 0xee0086);
        } else if (mode == 7) {
            PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
                   3, 3, WHITENESS);
        } else if (draw) {
            d.x = g_1df8[type][idx].f_00.x - g_1df8[type][idx].f_08.x;
            d.y = g_1df8[type][idx].f_00.y - g_1df8[type][idx].f_08.y;
            if (rop == 0xc000ca) {
                if (d.x < 0)
                    d.x -= 2;
                if (d.y < 0)
                    d.y -= 2;
            }
            if (g_1df8[type][idx].f_24 < fn_09_88ba(d.x)
                || g_1df8[type][idx].f_24 < fn_09_88ba(d.y)) {
                if (g_1df8[type][idx].f_22 > fn_09_88ba(d.x)
                    && g_1df8[type][idx].f_22 > fn_09_88ba(d.y)) {
                    if (d.x < 0) {
                        if (d.y < 0) {
                            PatBlt(g_13dc, g_1df8[type][idx].f_22 + g_1df8[type][idx].f_00.x,
                                   g_1df8[type][idx].f_00.y, -d.x,
                                   g_1df8[type][idx].f_22 - d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                                   g_1df8[type][idx].f_00.y + g_1df8[type][idx].f_22,
                                   g_1df8[type][idx].f_22, -d.y, BLACKNESS);
                        } else {
                            PatBlt(g_13dc, g_1df8[type][idx].f_22 + g_1df8[type][idx].f_00.x,
                                   g_1df8[type][idx].f_00.y - d.y, -d.x,
                                   g_1df8[type][idx].f_22 + d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                                   g_1df8[type][idx].f_00.y - d.y,
                                   g_1df8[type][idx].f_22, d.y, BLACKNESS);
                        }
                    } else {
                        if (d.y < 0) {
                            PatBlt(g_13dc, g_1df8[type][idx].f_00.x - d.x,
                                   g_1df8[type][idx].f_00.y, d.x,
                                   g_1df8[type][idx].f_22 - d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                                   g_1df8[type][idx].f_00.y + g_1df8[type][idx].f_22,
                                   g_1df8[type][idx].f_22, -d.y, BLACKNESS);
                        } else {
                            PatBlt(g_13dc, g_1df8[type][idx].f_00.x - d.x,
                                   g_1df8[type][idx].f_00.y - d.y, d.x,
                                   g_1df8[type][idx].f_22 + d.y, BLACKNESS);
                            PatBlt(g_13dc, g_1df8[type][idx].f_00.x,
                                   g_1df8[type][idx].f_00.y - d.y,
                                   g_1df8[type][idx].f_22, d.y, BLACKNESS);
                        }
                    }
                } else {
                    PatBlt(g_13dc, g_1df8[type][idx].f_08.x, g_1df8[type][idx].f_08.y,
                           g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, BLACKNESS);
                }
                BitBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
                       g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, dc,
                       g_1df8[type][idx].f_10, g_1df8[type][idx].f_12, rop);
            } else {
                BitBlt(g_13dc, g_1df8[type][idx].f_00.x - (d.x < 0 ? 0 : d.x),
                       g_1df8[type][idx].f_00.y - (d.y < 0 ? 0 : d.y),
                       fn_09_88ba(d.x) + g_1df8[type][idx].f_22,
                       fn_09_88ba(d.y) + g_1df8[type][idx].f_22, dc,
                       g_1df8[type][idx].f_10 - (d.x < 0 ? 0 : d.x),
                       g_1df8[type][idx].f_12 - (d.y < 0 ? 0 : d.y), rop);
            }
        }
    } else {
        g_1df8[type][idx].f_3a = dc;
        if (g_1df8[type][idx].f_2e != 0 && g_1df8[type][idx].f_2e != -2) {
            dc = g_1df8[type][idx].f_3c;
            g_1df8[type][idx].f_10 = g_1df8[type][idx].f_24;
            g_1df8[type][idx].f_12 = g_1df8[type][idx].f_24;
            if (g_1df8[type][idx].f_2e == -1)
                draw = 0;
        }
        if (g_952e == main_ship && (g_9e49 == 3 || g_9e49 == 6 && g_9e47 == 15)) {
            dc = g_1df8[type][idx].f_3c;
            g_1df8[type][idx].f_10 = g_1df8[type][idx].f_24;
            g_1df8[type][idx].f_12 = g_1df8[type][idx].f_24;
        }
        if (g_913a == 2 || g_913c == 2) {
            dc = g_1df8[type][idx].f_3c;
            g_1df8[type][idx].f_10 = g_1df8[type][idx].f_24;
            g_1df8[type][idx].f_12 = g_1df8[type][idx].f_24;
        }
        if (draw) {
            HBRUSH old;

            BitBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
                   g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, dc,
                   g_1df8[type][idx].f_10, g_1df8[type][idx].f_12, SRCCOPY);
            if (g_1df8[type][idx].f_2e == -2) {
                old = SelectObject(g_13dc, g_5ea8[0]);
                PatBlt(g_13dc, g_1df8[type][idx].f_00.x, g_1df8[type][idx].f_00.y,
                       g_1df8[type][idx].f_22, g_1df8[type][idx].f_22, 0xa000c9);
                SelectObject(g_13dc, old);
            }
        }
    }
done:
    return 1;
hidden:
    return 0;
}

/* Per-frame camera update: follow the player's object (or the free camera
 * at g_6b50 gliding toward it), apply the screen shake, then split the
 * view into 1, 2 or 4 rectangles where it crosses the map wrap
 * [inferred]. */
/* 8:0000 */
void fn_08_0000(void)
{
    int16_t dx;
    int16_t dy;
    int16_t dist;
    int16_t k;
    int16_t m;
    POINT pos;
    POINT c;
    POINT w;
    POINT s;

    k = 0;
    s.x = LO16(g_90ea) << g_9150;
    s.y = HI16(g_90ea) << g_9150;
    if (g_951a == 0) {
        g_2400 = g_1df8[g_9324][main_ship].f_04.x - s.x / 2;
        g_2402 = g_1df8[g_9324][main_ship].f_04.y - s.y / 2;
    } else {
        if (g_1df8[g_9324][main_ship].f_18 != 0 || g_7090[main_ship].flag == 0)
            fn_11_aece();
        pos.x = g_1df8[g_9324][main_ship].f_04.x;
        pos.y = g_1df8[g_9324][main_ship].f_04.y;
        dist = fn_08_285a(&dx, &dy, g_6b50, pos);
        if (dist < 16) {
            g_2400 = g_1df8[g_9324][main_ship].f_04.x - s.x / 2;
            g_2402 = g_1df8[g_9324][main_ship].f_04.y - ((k << g_9150) + s.y) / 2;
            PatBlt(g_13dc, g_1df8[g_9324][main_ship].f_00.x, g_1df8[g_9324][main_ship].f_00.y,
                   g_1df8[g_9324][main_ship].f_22, g_1df8[g_9324][main_ship].f_22, BLACKNESS);
            fn_07_11cc();
            switch (g_9134) {
            case 2:
                g_9134 = 0;
                flow_interactive = 1;
                break;
            case 3:
                g_9134 = 1;
                flow_interactive = 1;
                break;
            case 4:
                g_9134 = 1;
                break;
            }
            g_9134 = g_9378;
            g_951a = 0;
            fn_07_1208();
            g_0a76 = 2;
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        } else {
            g_2394 = dx * 12 / dist * 8;
            g_2396 = dy * 12 / dist * 8;
            g_6b50.y += g_2396;
            g_6b50.x += g_2394;
            if (g_6b50.x < 0)
                g_6b50.x = (LO16(g_05a0)) * 8 + g_6b50.x;
            if (g_6b50.x > (LO16(g_05a0)) * 8)
                g_6b50.x -= (LO16(g_05a0)) * 8;
            if (g_6b50.y < 0)
                g_6b50.y += HI16(g_05a0) * 8;
            if (g_6b50.y > HI16(g_05a0) * 8)
                g_6b50.y -= HI16(g_05a0) * 8;
            g_2400 = g_6b50.x - s.x / 2;
            g_2402 = g_6b50.y - s.y / 2;
            if (g_1df8[g_9324][main_ship].f_18 != 0) {
                g_1e80 = g_1e50 + 2000;
                if (g_1df8[g_9324][main_ship].f_18 == 1)
                    g_1e84 = g_1e50 + 1500;
            }
        }
    }
    if (g_238c != 0) {
        fn_10_744c(0x69);
        fn_10_754a(8, rand() % LO16(g_90ea), rand() % HI16(g_90ea), 4);
        g_2390 += g_238c;
        g_2392 += g_238e;
        g_2390 += rand() % 3 - 2;
        g_2392 += rand() % 3 - 2;
        if (g_2390 > 5)
            g_238c = -9;
        else if (g_2390 < -5)
            g_238c = 9;
        if (g_2392 > 5)
            g_238e = -6;
        else if (g_2392 < -5)
            g_238e = 6;
        g_2402 += g_2392 * 8;
        g_2400 += g_2390 * 8;
        g_1df8[g_9324][main_ship].f_08.x = g_1df8[g_9324][main_ship].f_00.x;
        g_1df8[g_9324][main_ship].f_08.y = g_1df8[g_9324][main_ship].f_00.y;
        g_1df8[g_9324][main_ship].f_00.y += g_2392;
        g_1df8[g_9324][main_ship].f_00.x += g_2390;
        fn_07_1208();
        if (g_2408 < g_1e50) {
            g_238c = 0;
            g_1df8[g_9324][main_ship].f_08.x = g_1df8[g_9324][main_ship].f_00.x;
            g_1df8[g_9324][main_ship].f_08.y = g_1df8[g_9324][main_ship].f_00.y;
            fn_07_1208();
        }
    } else {
        VIEW(int32_t, g_2390, 0) = 0;   /* g_2390 = g_2392 = 0 as one dword store */
    }
    g_2404 = s.x + g_2400;
    g_2406 = s.y + g_2402;
    if (g_951a == 0)
        c = g_1df8[g_9324][main_ship].f_04;
    else
        c = g_6b50;
    w.x = (LO16(g_05a0)) * 8;
    w.y = HI16(g_05a0) * 8;
    m = 600;
    if (g_9320 == 6 && g_9eb5 != 1) {
        g_23e0[0].left = g_2400 - 600;
        g_23e0[0].right = g_2404 + 600;
        g_23e0[0].top = g_2402 - 600;
        g_23e0[0].bottom = g_2406 + 600;
        g_9158 = 1;
    } else if (s.x / 2 + m > c.x) {
        g_23e0[0].left = -m;
        g_23e0[0].right = m + g_2404;
        g_23e0[1].left = w.x - s.x / 2 - m + c.x;
        g_23e0[1].right = w.x + m;
        if (s.y / 2 + m > c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[1].top = g_23e0[0].top = -m;
            g_23e0[3].top = g_23e0[2].top = w.y - s.y / 2 - m + c.y;
            g_23e0[0].bottom = g_23e0[1].bottom = m + g_2406;
            g_23e0[2].bottom = g_23e0[3].bottom = w.y + m;
            g_9158 = 4;
        } else if (w.y - s.y / 2 - m < c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[0].top = g_23e0[1].top = -m;
            g_23e0[2].top = g_23e0[3].top = g_2402 - m;
            g_23e0[0].bottom = g_23e0[1].bottom = s.y / 2 - w.y + c.y + m;
            g_23e0[2].bottom = g_23e0[3].bottom = w.y + m;
            g_9158 = 4;
        } else {
            g_23e0[0].top = g_23e0[1].top = c.y - s.y / 2 - m;
            g_23e0[0].bottom = g_23e0[1].bottom = s.y / 2 + c.y + m;
            g_9158 = 2;
        }
    } else if (w.x - s.x / 2 - m < c.x) {
        g_23e0[0].left = g_2400 - m;
        g_23e0[0].right = w.x + m;
        g_23e0[1].left = -m;
        g_23e0[1].right = s.x / 2 - w.x + c.x + m;
        if (s.y / 2 + m > c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[1].top = g_23e0[0].top = -m;
            g_23e0[3].top = g_23e0[2].top = w.y - s.y / 2 - m + c.y;
            g_23e0[0].bottom = g_23e0[1].bottom = m + g_2406;
            g_23e0[2].bottom = g_23e0[3].bottom = w.y + m;
            g_9158 = 4;
        } else if (w.y - s.y / 2 - m < c.y) {
            g_23e0[2].left = g_23e0[1].left;
            g_23e0[2].right = g_23e0[1].right;
            g_23e0[3].left = g_23e0[0].left;
            g_23e0[3].right = g_23e0[0].right;
            g_23e0[0].top = g_23e0[1].top = g_2402 - m;
            g_23e0[2].top = g_23e0[3].top = -m;
            g_23e0[0].bottom = g_23e0[1].bottom = w.y + m;
            g_23e0[2].bottom = g_23e0[3].bottom = s.y / 2 - w.y + c.y + m;
            g_9158 = 4;
        } else {
            g_23e0[0].top = g_23e0[1].top = g_2402 - m;
            g_23e0[0].bottom = g_23e0[1].bottom = m + g_2406;
            g_9158 = 2;
        }
    } else if (s.y / 2 + m > c.y) {
        g_23e0[0].left = g_23e0[1].left = c.x - s.x / 2 - m;
        g_23e0[0].right = g_23e0[1].right = g_23e0[0].left + m * 2 + s.x;
        g_23e0[0].top = -m;
        g_23e0[1].top = w.y - s.y / 2 - m + c.y;
        g_23e0[0].bottom = m + g_2406;
        g_23e0[1].bottom = w.y + m;
        g_9158 = 2;
    } else if (w.y - s.y / 2 - m < c.y) {
        g_23e0[0].left = g_23e0[1].left = c.x - s.x / 2 - m;
        g_23e0[0].right = g_23e0[1].right = g_23e0[0].left + m * 2 + s.x;
        g_23e0[0].top = g_2402 - m;
        g_23e0[1].top = -m;
        g_23e0[0].bottom = w.y + m;
        g_23e0[1].bottom = s.y / 2 - w.y + c.y + m;
        g_9158 = 2;
    } else {
        g_23e0[0].left = g_2400 - m;
        g_23e0[0].right = m + g_2404;
        g_23e0[0].top = g_2402 - m;
        g_23e0[0].bottom = m + g_2406;
        g_9158 = 1;
    }
    g_240c = g_2400;
    g_2410 = g_2402;
}

/* Build the animated map icon for unit a (pieces g_915c) from its sprite
 * (fn_10_7370) and notify related units; b == 0 [inferred: side] picks
 * the other icon frame. */
/* 8:2cd8 */
void fn_08_2cd8(int16_t a, int16_t b)
{
    int16_t flag;
    int16_t done;
    int16_t i;
    int16_t k;
    int16_t sz;
    int16_t r;
    int16_t dir;
    int16_t h;
    HBITMAP bmp;
    HBITMAP oldbmp;
    HDC dc;
    HPALETTE oldpal;
    POINT o;
    POINT p;
    POINT q;
    POINT z;

    done = flag = 0;
    g_7090[a].f_156 = g_1e50 - 10000;
    if (b == 0) {
        g_7090[a].f_0ac = 0;
        flag = 1;
    } else
        g_7090[a].f_0ad = 0;
    if (g_95a6 == 0) {
        fn_14_3eda();
        if (g_7090[a].f_0d6 >= 0)
            g_96d2[g_7090[a].f_04e].f_3c =
                (g_6e1c[g_6e20[g_6e24[g_7090[a].f_0d6].f_00].f_21].f_1a << g_9156 >> 1) / 2;
        else
            g_96d2[g_7090[a].f_04e].f_3c =
                (g_6e1c[g_6e20[g_4ed8[g_7090[a].f_05e]].f_21].f_1a << g_9156 >> 1) / 2;
        fn_14_4074();
    }
    if (g_92e4 == 0) {
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].f_032.a == g_9324 && g_7090[i].f_032.b == a && g_7090[i].f_038 == 1) {
                if (g_7090[i].f_0ac == g_7090[a].f_0ac && g_7090[i].f_0ad == g_7090[a].f_0ad)
                    fn_03_06ec(i, g_9324, a, 0x1b);
                else if (g_7090[a].f_0ac != 0 || g_7090[a].f_0ad != 0) {
                    if (g_7090[i].f_0ac == 0 && g_7090[i].f_0ad == 0)
                        fn_03_06ec(i, g_9324, a, 0x1e);
                    else if (fn_04_5d9c(a, i) > 95)
                        fn_03_06ec(i, g_9324, a, 0x1c);
                    else
                        fn_03_06ec(i, g_9324, a, 0x19);
                } else if (fn_04_5d9c(a, i) > 95)
                    fn_03_06ec(i, g_9324, a, 0x1d);
                else
                    fn_03_06ec(i, g_9324, a, 0x1a);
            }
        }
        for (i = done = 0; i < 3; i++) {
            if (g_915c[i].f_1a == 0) {
                if (subgame_active == 0) {
                    sz = 0x100;
                    h = 0x100 >> g_9150;
                    r = g_96d2[g_7090[a].f_04e].f_3c / 2 * 8
                        + (g_1df8[g_9324][a].f_20 - g_96d2[g_7090[a].f_04e].f_3c * 8) / 4;
                } else {
                    h = ((g_9156 << 6) + 32) / 3;
                    sz = (int16_t)(h * g_88cc / g_88c0.x);
                    r = (int16_t)(g_96d2[g_7090[a].f_04e].f_3c / 2 * g_88cc / g_88c0.x)
                        + (g_1df8[g_9324][a].f_20
                           - (int16_t)(g_96d2[g_7090[a].f_04e].f_3c * g_88cc / g_88c0.x)) / 4;
                }
                g_915c[i].f_1a = 1;
                g_915c[i].f_1c = 0x46;
                g_915c[i].f_1e = g_1df8[g_9324][a].f_20;
                g_915c[i].f_00 = g_1df8[g_9324][a].f_04;
                g_915c[i].f_04.x = -1000;
                g_915c[i].f_04.y = -1000;
                dir = g_1df8[g_9324][a].f_28;
                g_915c[i].f_08 = VIEW(POINT, g_1df8[g_9324][a].f_0c, 0);   /* velocity */
                g_915c[i].f_08.x += g_1050[(dir + 4) % 16].x / 2;
                g_915c[i].f_08.y += g_1050[(dir + 4) % 16].y / 2;
                if (flag) {
                    p.x = g_915c[i].f_1e / 2 + g_066e[(dir + 12) % 16].x * r / 128;
                    p.y = g_915c[i].f_1e / 2 + g_066e[(dir + 12) % 16].y * r / 128;
                } else {
                    p.x = g_915c[i].f_1e / 2 + g_066e[(dir + 4) % 16].x * r / 128;
                    p.y = g_915c[i].f_1e / 2 + g_066e[(dir + 4) % 16].y * r / 128;
                }
                q.x = min(sz / 2 + p.x, g_915c[i].f_1e);
                z.x = max(p.x - sz / 2, 0);
                q.y = min(sz / 2 + p.y, g_915c[i].f_1e);
                z.y = max(p.y - sz / 2, 0);
                o.x = max(sz / 2 - p.x, 0);
                o.y = max(sz / 2 - p.y, 0);
                g_915c[i].f_00.x += p.x - sz / 2;
                g_915c[i].f_00.y += p.y - sz / 2;
                bmp = fn_10_7370(g_3a38[a], flag, g_1df8[g_9324][a].f_22,
                                 g_96d2[g_7090[a].f_04e].f_3c, g_1df8[g_9324][a].f_24,
                                 g_1df8[g_9324][a].f_28, 1);
                dc = CreateCompatibleDC(g_13dc);
                oldbmp = SelectObject(dc, bmp);
                if (g_920e != 0)
                    oldpal = SelectPalette(dc, g_920e, 0);
                g_915c[i].f_0c = CreateCompatibleDC(g_13dc);
                g_915c[i].f_10 = CreateCompatibleBitmap(g_13dc, h * 5, h);
                g_915c[i].f_14 = SelectObject(g_915c[i].f_0c, g_915c[i].f_10);
                if (g_920e != 0)
                    g_915c[i].pal = SelectPalette(g_915c[i].f_0c, g_920e, 0);
                PatBlt(g_915c[i].f_0c, 0, 0, h * 5, h, BLACKNESS);
                if (subgame_active == 0) {
                    for (k = 0; k < 5; k++)
                        BitBlt(g_915c[i].f_0c, (sz * k + o.x) >> g_9150, o.y >> g_9150,
                               (q.x - z.x) >> g_9150, (q.y - z.y) >> g_9150, dc,
                               z.x >> g_9150, z.y >> g_9150, SRCCOPY);
                } else {
                    o.x = (int16_t)(o.x * (int32_t)g_88c0.x * (g_9156 * 2 + 1) / g_88cc) / 3;
                    o.y = (int16_t)(o.y * (int32_t)g_88c0.x * (g_9156 * 2 + 1) / g_88cc) / 3;
                    for (k = 0; k < 5; k++)
                        BitBlt(g_915c[i].f_0c, h * k + o.x, o.y,
                               (int16_t)((q.x - z.x) * (int32_t)g_88c0.x * (g_9156 * 2 + 1) / g_88cc) / 3,
                               (int16_t)((q.y - z.y) * (int32_t)g_88c0.x * (g_9156 * 2 + 1) / g_88cc) / 3,
                               dc,
                               (int16_t)(z.x * (int32_t)g_88c0.x * (g_9156 * 2 + 1) / g_88cc) / 3,
                               (int16_t)(z.y * (int32_t)g_88c0.x * (g_9156 * 2 + 1) / g_88cc) / 3,
                               SRCCOPY);
                }
                SelectObject(g_915c[i].f_0c, g_915c[i].f_14);
                g_915c[i].f_12 = fn_10_6ec6(g_915c[i].f_10);
                g_915c[i].f_14 = SelectObject(g_915c[i].f_0c, g_915c[i].f_10);
                g_915c[i].f_0e = CreateCompatibleDC(g_13dc);
                g_915c[i].f_16 = SelectObject(g_915c[i].f_0e, g_915c[i].f_12);
                done = 1;
                SelectObject(dc, oldbmp);
                if (oldpal != 0)
                    SelectPalette(dc, oldpal, 0);
                DeleteDC(dc);
                DeleteObject(bmp);
                fn_10_754a(0x6a, g_9324, a, 1);
                break;
            }
        }
    }
    if (done == 0)
        fn_10_7370(g_3a38[a], flag, g_1df8[g_9324][a].f_22,
                   g_96d2[g_7090[a].f_04e].f_3c, g_1df8[g_9324][a].f_24,
                   g_1df8[g_9324][a].f_28, 0);
}

/* Clamp an object's velocity to [-v, v] [inferred]. */
/* 8:1cbe */
void fn_08_1cbe(OBJREF r, int16_t v)
{
    int16_t type;
    int16_t idx;

    type = r.type;
    idx = r.idx;
    if (g_1df8[type][idx].f_0c > v)
        g_1df8[type][idx].f_0c = v;
    if (g_1df8[type][idx].f_0e > v)
        g_1df8[type][idx].f_0e = v;
    if (g_1df8[type][idx].f_0c < -v)
        g_1df8[type][idx].f_0c = -v;
    if (g_1df8[type][idx].f_0e < -v)
        g_1df8[type][idx].f_0e = -v;
}

/* Direction 0..15 of the vector (dx, dy) from the slope dy/dx
 * [inferred]. */
/* 8:19b0 */
int16_t fn_08_19b0(int16_t dx, int16_t dy)
{
    int32_t d;
    int32_t r;
    int32_t ldx;
    int32_t ldy;
    int16_t dir;

    ldy = dy;
    ldx = dx;
    if (abs32(ldx) > 0)
        d = ldx;
    else
        d = 1;
    r = ldy * 100 / d;
    if (r > 500 || r < -500) {
        if (ldy > 0)
            dir = 8;
        else
            dir = 0;
    }
    if (r < 501 && r > 154) {
        if (ldy > 0)
            dir = 7;
        else
            dir = 15;
    } else if (r < 155 && r > 65) {
        if (ldy > 0)
            dir = 6;
        else
            dir = 14;
    } else if (r < 66 && r > 19) {
        if (ldy > 0)
            dir = 5;
        else
            dir = 13;
    } else if (r < 20 && r > -20) {
        if (ldx > 0)
            dir = 4;
        else
            dir = 12;
    } else if (r < -19 && r > -65) {
        if (ldy > 0)
            dir = 11;
        else
            dir = 3;
    } else if (r < -64 && r > -154) {
        if (ldy > 0)
            dir = 10;
        else
            dir = 2;
    } else if (r < -153 && r > -501) {
        if (ldy > 0)
            dir = 9;
        else
            dir = 1;
    }
    return dir;
}

/* r packs (type << 8) | index. Move an object by n times its velocity,
 * wrapping round the map
 * [inferred]. */
/* 8:1b54 */
void fn_08_1b54(WORD r, int16_t n)
{
    int16_t saved;
    int16_t type;
    int16_t idx;

    type = HIBYTE(r);
    idx = LOBYTE(r);
    if (type == 14 && g_1df8[14][idx].f_54 != 0 && g_92e8 != 0 && g_9e49 == 10)
        return;
    if (g_1df8[type][idx].f_32 != -1 && type != 10)
        fn_08_1e32(type, idx);
    if (type == g_9328) {
        saved = g_9006;
        g_9006 = 10;
    }
    if (n == 1) {
        g_1df8[type][idx].f_04.x += g_1df8[type][idx].f_0c;
        g_1df8[type][idx].f_04.y += g_1df8[type][idx].f_0e;
    } else {
        g_1df8[type][idx].f_04.x += g_1df8[type][idx].f_0c * n;
        g_1df8[type][idx].f_04.y += g_1df8[type][idx].f_0e * n;
    }
    if (subgame_active)
        return;
    if (g_1df8[type][idx].f_04.x > (LO16(g_05a0)) * 8)
        g_1df8[type][idx].f_04.x = 0;
    if (g_1df8[type][idx].f_04.x < 0)
        g_1df8[type][idx].f_04.x = (LO16(g_05a0)) * 8;
    if (g_1df8[type][idx].f_04.y > HI16(g_05a0) * 8)
        g_1df8[type][idx].f_04.y = 0;
    if (g_1df8[type][idx].f_04.y < 0)
        g_1df8[type][idx].f_04.y = HI16(g_05a0) * 8;
    if (type == g_9328)
        g_9006 = saved;
}

/* Tether physics for object (type, idx) towing object f32/f34: spring
 * forces, break-off, and redraw of the tether line [inferred]. */
/* near-match 99%: 8:1e32 (only compiler temp slots differ: the original
 * puts the cx/bx spills at bp-44/-42 and the POINT return temps at bp-48
 * and bp-4c; here the return temps come first). pad keeps per at bp-48. */
void fn_08_1e32(int16_t type, int16_t idx)
{
    POINT c;
    POINT dv;
    POINT dp;
    HPEN old;
    int16_t dist;
    int16_t t2;
    int16_t i2;
    int16_t bi;
    int16_t len;
    int16_t u;
    int16_t w;
    int16_t m1;
    int16_t m2;
    int16_t f1;
    int16_t f2;
    int16_t px;
    int16_t py;
    int16_t rest;
    int16_t heavy;
    int16_t k;
    int32_t dot;
    int32_t a;
    int32_t b;
    int16_t force;
    int16_t j;

    g_915a++;
    if (g_915a > 3)
        g_915a = 0;
    bi = g_1df8[type][idx].f_30;
    if (g_65cc[bi].f_0a == 2)
        heavy = 1;
    else
        heavy = 0;
    g_1df8[type][idx].f_04.x -= g_1df8[type][idx].f_0c;
    g_1df8[type][idx].f_04.y -= g_1df8[type][idx].f_0e;
    t2 = g_1df8[type][idx].f_32;
    i2 = g_1df8[type][idx].f_34;
    /* bare label: resets CL's register tracking (layout only) */
lbl:
    k = 0;
    j = i2;
    rest = 300;
    c.x = g_1df8[t2][i2].f_20 / 2 + g_1df8[t2][i2].f_04.x;
    c.y = g_1df8[t2][i2].f_20 / 2 + g_1df8[t2][i2].f_04.y;
    g_65cc[bi].f_10 = fn_08_29ea(g_1df8[type][idx].f_04);
    g_65cc[bi].f_18 = fn_08_29ea(g_1df8[t2][i2].f_04);
    dist = fn_08_285a(&px, &py, g_1df8[type][idx].f_04, c);
    if (dist == 0)
        dist = 1;
    if (t2 == 14) {
        int16_t m;
        int16_t pad;
        int16_t per;

        m = g_1df8[type][idx].f_44;
        per = m / -200 + 8 < 3 ? 3 : m / -200 + 8;
        if (g_1e68 % per == 0) {
            g_7090[i2].f_01e -= 3;
            if (g_7090[i2].f_01e <= 0)
                dist = 1000;
        }
    }
    if (heavy * 100 + 350 < dist
        || g_1df8[g_1df8[type][idx].f_32][g_1df8[type][idx].f_34].f_18 != 0
        || type == 7) {
        g_1df8[type][idx].f_32 = -1;
        g_1df8[g_65cc[bi].f_04][g_65cc[bi].f_06].f_36 = -1;
        g_65cc[bi].f_00 = -1;
        g_65cc[bi].f_04 = -1;
        old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
        fn_12_7256(g_13dc, g_65cc[bi].f_1c, g_65cc[bi].f_14);
        fn_12_7256(g_13dc, g_65cc[bi].f_18, g_65cc[bi].f_10);
        SelectObject(g_13dc, old);
        fn_07_2080(10);
        fn_10_744c(0x69);
        fn_10_754a(0x14, type, idx, 1);
    }
    if (dist > 40) {
        if (heavy == 0) {
            if (rest < dist) {
                dv.x = g_1df8[type][idx].f_0c - g_1df8[t2][i2].f_0c;
                dv.y = g_1df8[type][idx].f_0e - g_1df8[t2][i2].f_0e;
                len = (int16_t)fn_08_1290((int32_t)(dv.x * dv.x + dv.y * dv.y),
                                      (int32_t)(fn_09_88ba(dv.x) + fn_09_88ba(dv.y)));
                dp.x = g_65cc[bi].f_18.x - g_65cc[bi].f_10.x;
                dp.y = g_65cc[bi].f_18.y - g_65cc[bi].f_10.y;
                a = (int32_t)dp.x * dv.x;
                b = (int32_t)dp.y * dv.y;
                dot = a + b;
                if (len == 0)
                    len = 1;
                u = (int16_t)((w = (int16_t)(dot * -100 / ((int32_t)dist * len))) * (int32_t)len / 100);
                force = min(dist - rest, 60) * 50;
                m1 = g_1df8[type][idx].f_44;
                m2 = g_1df8[t2][i2].f_44;
                if (k != 0)
                    m1 /= 3;
                if (rest < 300)
                    m1 /= 3;
                if (force > 3000 && rest >= 300)
                    u = -50;
                if (force > 1800 && rest < 300 && type == g_9324
                    && g_7090[idx].f_0e2 == 0 && g_7090[idx].f_002 != 0) {
                    g_1df8[g_9324][i2].f_50 = 60;
                    fn_11_a234(g_9324, i2, type, idx);
                }
                if (dot < 0) {
                    f1 = (int16_t)((int32_t)u * 100 / ((int32_t)m1 * 100 / m2 + 100));
                    f2 = u - f1;
                } else
                    f1 = f2 = 0;
                f1 += force / m1;
                g_1df8[type][idx].f_0c += (g_17bc / 3 + f1) * dp.x / dist;
                g_1df8[type][idx].f_0e += (g_17bc / 3 + f1) * dp.y / dist;
                f2 += force / m2;
                g_1df8[t2][i2].f_0c -= (g_17be / 3 + f2) * dp.x / dist;
                g_1df8[t2][i2].f_0e -= (g_17be / 3 + f2) * dp.y / dist;
                g_17bc = f1;
                g_17be = f2;
                if (rest < 300)
                    fn_08_1cbe((OBJREF){idx, type}, 80);
            }
        } else if (g_1df8[type][idx].f_53 == 1) {
            g_1df8[type][idx].f_0c += px >> 2;
            g_1df8[type][idx].f_0e += py >> 2;
        } else if (g_65cc[bi].f_0e != 0) {
            g_1df8[type][idx].f_0c = (int16_t)(180L * py / dist) + (px << 3) / dist;
            g_1df8[type][idx].f_0e = (int16_t)(-180L * px / dist) + (py << 3) / dist;
        } else {
            g_1df8[type][idx].f_0c = (int16_t)(-180L * py / dist) + (px << 3) / dist;
            g_1df8[type][idx].f_0e = (int16_t)(180L * px / dist) + (py << 3) / dist;
        }
    }
    g_1df8[type][idx].f_04.x += g_1df8[type][idx].f_0c;
    g_1df8[type][idx].f_04.y += g_1df8[type][idx].f_0e;
    fn_07_1208();
    old = SelectObject(g_13dc, GetStockObject(BLACK_PEN));
    fn_12_7256(g_13dc, g_65cc[bi].f_1c, g_65cc[bi].f_14);
    SelectObject(g_13dc, old);
    if (g_1df8[type][idx].f_32 != -1) {
        g_65cc[bi].f_10 = fn_08_29ea(g_1df8[type][idx].f_04);
        g_65cc[bi].f_10.x += (g_1df8[type][idx].f_0c >> g_9150) + g_1df8[type][idx].f_22 / 2;
        g_65cc[bi].f_10.y += (g_1df8[type][idx].f_0e >> g_9150) + g_1df8[type][idx].f_22 / 2;
        g_65cc[bi].f_18 = fn_08_29ea(g_1df8[t2][i2].f_04);
        g_65cc[bi].f_18.x += g_1df8[t2][i2].f_22 / 2;
        g_65cc[bi].f_18.y += g_1df8[t2][i2].f_22 / 2;
        if (g_8ff2 != 0)
            old = SelectObject(g_13dc, GetStockObject(WHITE_PEN));
        else
            old = SelectObject(g_13dc, g_3b44[g_915a]);
        fn_12_7256(g_13dc, g_65cc[bi].f_18, g_65cc[bi].f_10);
        SelectObject(g_13dc, old);
    }
    g_65cc[bi].f_14 = g_65cc[bi].f_10;
    g_65cc[bi].f_1c = g_65cc[bi].f_18;
}

/* Slow an object down by one unit per axis once |vx|+|vy| reaches v
 * [inferred: friction]. */
/* 8:1d54 */
void fn_08_1d54(OBJREF r, int16_t v)
{
    int16_t sum;
    int16_t sx;
    int16_t sy;
    int16_t type;
    int16_t idx;

    type = r.type;
    idx = r.idx;
    if (g_1df8[type][idx].f_0c > 0) {
        sum = g_1df8[type][idx].f_0c;
        sx = 1;
    } else {
        sum = -g_1df8[type][idx].f_0c;
        sx = -1;
    }
    if (g_1df8[type][idx].f_0e > 0) {
        sum += g_1df8[type][idx].f_0e;
        sy = 1;
    } else {
        sum -= g_1df8[type][idx].f_0e;
        sy = -1;
    }
    if (sum >= v) {
        if (g_1df8[type][idx].f_0c != 0)
            g_1df8[type][idx].f_0c -= sx;
        if (g_1df8[type][idx].f_0e != 0)
            g_1df8[type][idx].f_0e -= sy;
    }
}

/* Steer object (type, idx) toward the centre of object (type2, idx2)
 * [inferred]. */
/* 8:348e */
void fn_08_348e(int16_t type, int16_t idx, int16_t type2, int16_t idx2, int16_t speed)
{
    POINT p1;
    POINT p2;
    int16_t dx;
    int16_t dy;
    int16_t vx;
    int16_t vy;
    int16_t d;

    p1 = fn_08_29ea(g_1df8[type][idx].f_04);
    p2 = fn_08_29ea(g_1df8[type2][idx2].f_04);
    p1.x <<= g_9150;
    p1.y <<= g_9150;
    p2.x <<= g_9150;
    p2.y <<= g_9150;
    p2.x += g_1df8[type2][idx2].f_20 / 2;
    p2.y += g_1df8[type2][idx2].f_20 / 2;
    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    vx = g_1df8[type2][idx2].f_0c;
    vy = g_1df8[type2][idx2].f_0e;
    d = fn_08_35d0(dx, dy);
    vx += (int32_t)dx * speed / d;
    vy += (int32_t)dy * speed / d;
    g_1df8[type][idx].f_0c = vx;
    g_1df8[type][idx].f_0e = vy;
}

/* Redraw map object i, masked when something overlaps it [inferred]. */
/* 8:08a6 */
void fn_08_08a6(int16_t i)
{
    RECT r3;
    RECT r1;
    RECT r2;
    int16_t hit;
    int16_t mine;
    int16_t k;
    int16_t size;

    mine = hit = 0;
    if (g_915c[i].f_1a < 2) {
        g_915c[i].f_04 = fn_08_29ea(g_915c[i].f_00);
        return;
    }
    if (subgame_active == 0)
        size = (32 << g_9156) >> 1;
    else
        size = ((g_9156 << 6) + 32) / 3;
    SetRect(&r1, g_915c[i].f_04.x, g_915c[i].f_04.y,
            g_915c[i].f_04.x + size, g_915c[i].f_04.y + size);
    for (k = 0; k < g_9146; k++) {
        SetRect(&r2, g_1df8[g_507c[k]][g_50e0[k]].f_00.x, g_1df8[g_507c[k]][g_50e0[k]].f_00.y,
                g_1df8[g_507c[k]][g_50e0[k]].f_22 + g_1df8[g_507c[k]][g_50e0[k]].f_00.x,
                g_1df8[g_507c[k]][g_50e0[k]].f_22 + g_1df8[g_507c[k]][g_50e0[k]].f_00.y);
        if (IntersectRect(&r3, &r2, &r1)) {
            hit = 1;
            if (g_507c[k] == g_9324 && g_50e0[k] == main_ship)
                mine = 1;
        }
    }
    if (hit) {
        if (g_915c[i].f_04.x > -40 && g_915c[i].f_04.x < LO16(g_90ea) + 40
            && g_915c[i].f_04.y > -40 && g_915c[i].f_04.y < HI16(g_90ea) + 40)
            BitBlt(g_13dc, g_915c[i].f_04.x, g_915c[i].f_04.y, size, size,
                   g_915c[i].f_0e, 0, 0, SRCAND);
        g_915c[i].f_04 = fn_08_29ea(g_915c[i].f_00);
        if (g_915c[i].f_04.x > -40 && g_915c[i].f_04.x < LO16(g_90ea) + 40
            && g_915c[i].f_04.y > -40 && g_915c[i].f_04.y < HI16(g_90ea) + 40) {
            BitBlt(g_13dc, g_915c[i].f_04.x, g_915c[i].f_04.y, size, size,
                   g_915c[i].f_0e, 0, 0, SRCAND);
            BitBlt(g_13dc, g_915c[i].f_04.x, g_915c[i].f_04.y, size, size,
                   g_915c[i].f_0c, g_915c[i].f_1a / 2 % 5 * size, 0, SRCPAINT);
        }
    } else {
        if (g_915c[i].f_04.x > -40 && g_915c[i].f_04.x < LO16(g_90ea) + 40
            && g_915c[i].f_04.y > -40 && g_915c[i].f_04.y < HI16(g_90ea) + 40)
            PatBlt(g_13dc, g_915c[i].f_04.x, g_915c[i].f_04.y, size, size, BLACKNESS);
        g_915c[i].f_04 = fn_08_29ea(g_915c[i].f_00);
        if (g_915c[i].f_04.x > -40 && g_915c[i].f_04.x < LO16(g_90ea) + 40
            && g_915c[i].f_04.y > -40 && g_915c[i].f_04.y < HI16(g_90ea) + 40)
            BitBlt(g_13dc, g_915c[i].f_04.x, g_915c[i].f_04.y, size, size,
                   g_915c[i].f_0c, g_915c[i].f_1a / 2 % 5 * size, 0, SRCCOPY);
    }
}

/* Move the stars against the ship's motion, wrapping round the view
 * with a new random position and colour [inferred]. */
/* 8:1320 */
void fn_08_1320(int16_t still)
{
    int16_t i;

    if (g_1df8[g_9324][main_ship].f_18 == 1) {
        g_1df8[g_9324][main_ship].f_0c = 0;
        g_1df8[g_9324][main_ship].f_0e = 0;
    }
    if (still == 0 && g_238c == 0 && g_1df8[g_9324][main_ship].f_0c == 0
        && g_1df8[g_9324][main_ship].f_0e == 0)
        return;
    for (i = 0; i < g_9152; i++) {
        if (g_91c2[i])
            PatBlt(g_13dc, g_2398[i].x, g_2398[i].y, 3, 3, BLACKNESS);
        if (still == 0) {
            if (g_951a) {
                g_2398[i].x -= (g_2394 << g_9156) >> 2;
                g_2398[i].y -= (g_2396 << g_9156) >> 2;
            } else {
                g_2398[i].x -= (g_1df8[g_9324][main_ship].f_0c << g_9156) >> 2;
                g_2398[i].y -= (g_1df8[g_9324][main_ship].f_0e << g_9156) >> 2;
            }
            if (g_238c) {
                g_2398[i].x += (g_2390 << g_9156) >> 2;
                g_2398[i].y += (g_2392 << g_9156) >> 2;
            }
            if (g_2398[i].x < 0) {
                g_2398[i].x = LO16(g_90ea);
                g_2398[i].y = rand() % HI16(g_90ea);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            } else if (g_2398[i].x > LO16(g_90ea)) {
                g_2398[i].x = 0;
                g_2398[i].y = rand() % HI16(g_90ea);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            }
            if (g_2398[i].y < 0) {
                g_2398[i].y = HI16(g_90ea);
                g_2398[i].x = rand() % LO16(g_90ea);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            } else if (g_2398[i].y > HI16(g_90ea)) {
                g_2398[i].y = 0;
                g_2398[i].x = rand() % LO16(g_90ea);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
            }
        }
        if (g_9154 == g_9152) {
            if (!PtInRect(&g_1e5c, g_2398[i])) {
                PatBlt(g_13dc, g_2398[i].x, g_2398[i].y, 3, 3, WHITENESS);
                g_91c2[i] = 1;
            } else {
                g_91c2[i] = 0;
            }
        }
    }
    if (g_9154 != g_9152)
        g_9152 = g_9154;
}

/* Random positions and colours for g_9152 entries [inferred: stars]. */
/* 8:190e */
void fn_08_190e(void)
{
    int16_t i;

    for (i = 0; i < g_9152; i++) {
        g_2398[i].x = rand() % LO16(g_90ea);
        g_2398[i].y = rand() % HI16(g_90ea);
        g_2f04[i] = PALETTERGB(255, rand() % 255, rand() % 255);
        g_91d4[i] = rand() % 3 + 1;
        g_91e6[i] = rand() % 40;
        g_91c2[i] = 1;
    }
}

/* Stars: move them against the ship's motion (deeper stars slower),
 * wrap them round the play view and draw them twinkling; every second
 * call only [inferred]. */
/* 8:158a */
void fn_08_158a(int16_t still)
{
    int16_t i;
    int16_t maxsz;
    int16_t t1;
    int16_t t2;
    int16_t c;
    int16_t sz;

    g_06ae++;
    if (g_06ae > 1)
        g_06ae = 0;
    if (still)
        g_06ae = 0;
    if (g_06ae != 0)
        return;
    if (g_8ff2) {
        fn_08_1320(still);
        return;
    }
    if (g_9156 == 0)
        maxsz = 2;
    else
        maxsz = 3;
    if (g_1df8[g_9324][main_ship].f_18 == 1
        || (g_1df8[g_9324][main_ship].f_54 != 0 && g_92e8 != 0)) {
        g_1df8[g_9324][main_ship].f_0c = 0;
        g_1df8[g_9324][main_ship].f_0e = 0;
    }
    for (i = 0; i < g_9152; i++) {
        if (g_91c2[i])
            PatBlt(g_13dc, g_2398[i].x, g_2398[i].y,
                   t1 = g_91d4[i] > maxsz ? maxsz : g_91d4[i], t1, BLACKNESS);
        if (still == 0) {
            t1 = g_9156 + 1;
            t2 = 6 - g_91d4[i];
            if (g_951a) {
                g_2398[i].x -= g_2394 << t1 >> t2;
                g_2398[i].y -= g_2396 << t1 >> t2;
            } else {
                g_2398[i].x -= g_1df8[g_9324][main_ship].f_0c << t1 >> t2;
                g_2398[i].y -= g_1df8[g_9324][main_ship].f_0e << t1 >> t2;
            }
            if (g_238c) {
                g_2398[i].x += g_2390 << t1 >> t2;
                g_2398[i].y += g_2392 << t1 >> t2;
            }
            if (g_2398[i].x < g_1d30.left) {
                g_2398[i].x = g_1d30.right;
                g_2398[i].y = rand() % (g_1d30.bottom - g_1d30.top);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            } else if (g_2398[i].x > g_1d30.right) {
                g_2398[i].x = g_1d30.left;
                g_2398[i].y = rand() % (g_1d30.bottom - g_1d30.top);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            }
            if (g_2398[i].y < g_1d30.top) {
                g_2398[i].y = g_1d30.bottom;
                g_2398[i].x = rand() % (g_1d30.right - g_1d30.left);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            } else if (g_2398[i].y > g_1d30.bottom) {
                g_2398[i].y = g_1d30.top;
                g_2398[i].x = rand() % (g_1d30.right - g_1d30.left);
                g_2f04[i] = RGB(255, rand() % 255, rand() % 255);
                g_91d4[i] = rand() % 3 + 1;
            }
        }
        if (g_9154 == g_9152) {
            if (!PtInRect(&g_1e5c, g_2398[i])) {
                t1 = g_91e6[i] / 5;
                if (t1 < 4)
                    c = t1 + 10;
                else
                    c = 18 - t1;
                sz = g_91d4[i] > maxsz ? maxsz : g_91d4[i];
                t2 = SelectObject(g_13dc, g_3b4c[c]);
                PatBlt(g_13dc, g_2398[i].x, g_2398[i].y, sz, sz, PATCOPY);
                SelectObject(g_13dc, t2);
                if (g_91e6[i] < 40)
                    g_91e6[i]++;
                else
                    g_91e6[i] = 0;
                g_91c2[i] = 1;
            } else {
                g_91c2[i] = 0;
            }
        }
    }
    if (g_9154 != g_9152)
        g_9152 = g_9154;
}

/* Distance from a to b on the wrapping map (in 8-unit cells), with the
 * offsets stored to *p and *q [inferred]. */
/* 8:285a */
int16_t fn_08_285a(int16_t *p, int16_t *q, POINT a, POINT b)
{
    int16_t dy;
    int16_t dx;
    int16_t ty;
    int16_t tx;
    int32_t g;
    int32_t adx;
    int32_t ady;

    if (subgame_active == 0) {
        b.y >>= 3;
        a.y >>= 3;
        b.x >>= 3;
        a.x >>= 3;
        dx = b.x - a.x;
        if (fn_09_88ba(dx) > (LO16(g_05a0)) >> 1) {
            tx = 0 > dx ? b.x + (LO16(g_05a0)) : b.x - (LO16(g_05a0));
            dx = tx - a.x;
        }
        dy = b.y - a.y;
        if (fn_09_88ba(dy) > HI16(g_05a0) >> 1) {
            ty = 0 > dy ? b.y + HI16(g_05a0) : b.y - HI16(g_05a0);
            dy = ty - a.y;
        }
    } else {
        b = fn_08_29ea(b);
        a = fn_08_29ea(a);
        dx = b.x - a.x;
        dy = b.y - a.y;
    }
    ady = fn_09_88ba(dy);
    adx = fn_09_88ba(dx);
    if (adx < ady)
        g = (adx >> 1) + ady;
    else
        g = (ady >> 1) + adx;
    *p = dx;
    *q = dy;
    return g ? ((ady * ady + adx * adx) / g + g) >> 1 : 1;
}

/* World point to screen point [inferred]: relative to the view origin
 * DS:240c/2410, wrapped the short way round the map, scaled down by
 * g_9150; in the sub-game a linear map (inverse of 8:2bbe). */
/* 8:29ea */
POINT fn_08_29ea(POINT pt)
{
    POINT r;
    int32_t u1;
    int32_t lx;
    int32_t ly;
    int16_t u2[1];

    lx = pt.x;
    ly = pt.y;
    if (subgame_active == 0) {
        r.x = (int16_t)((lx - g_240c) >> g_9150);
        if (fn_09_88ba((int16_t)lx - (LO16(g_90ea) << (g_9150 - 1)) - (int16_t)g_240c) > (LO16(g_05a0)) * 4
            && (g_9320 != 6 || g_9eb5 == 1))
            r.x = (int16_t)(((0 > r.x ? (int32_t)pt.x + (LO16(g_05a0)) * 8 : (int32_t)pt.x - (LO16(g_05a0)) * 8)
                         - g_240c) >> g_9150);
        r.y = (int16_t)((ly - g_2410) >> g_9150);
        if (abs32(ly - (HI16(g_90ea) << (g_9150 - 1)) - g_2410) > HI16(g_05a0) * 4
            && (g_9320 != 6 || g_9eb5 == 1))
            r.y = (int16_t)(((0 > r.y ? (int32_t)pt.y + HI16(g_05a0) * 8 : (int32_t)pt.y - HI16(g_05a0) * 8)
                         - g_2410) >> g_9150);
    } else {
        r.x = (int16_t)(pt.x * (int32_t)g_88c0.x / g_88cc) + g_88c4.x;
        r.y = (int16_t)(pt.y * (int32_t)g_88c0.x / g_88cc) + g_88c4.y;
    }
    return r;
}

/* Integer square root, one Newton step from guess g [inferred]. The loop
 * after the return is dead code in the original. */
/* The dead store a = (unsigned)b is removed, but it makes CL forget that ax
 * holds g's low word, so the loop's g < 3 test reloads it (layout only). */
/* 8:1290 */
int32_t fn_08_1290(int32_t n, int32_t g)
{
    int16_t i;
    int32_t a;
    int32_t b;

    if (g < 3)
        g = 3;
    return (n / g + g) >> 1;
    do {
        if (g < 3)
            g = 3;
        b = (n - g * g) / (2 * g) + g;
        g = b;
        a = (uint16_t)b;
        i++;
    } while (i < 1);
}

/* Distance approximation: start from max + min/2, one Newton step of the
 * square root of a*a + b*b [inferred]. */
/* Returns int although the expression is long (the result is truncated). */
/* 8:35d0 */
int16_t fn_08_35d0(int32_t a, int32_t b)
{
    int32_t aa;
    int32_t ab;
    int32_t g;

    ab = abs32(b);
    aa = abs32(a);
    if (aa < ab)
        g = (aa >> 1) + ab;
    else
        g = (ab >> 1) + aa;
    return g ? ((b * b + a * a) / g + g) >> 1 : 1;
}

/* Screen point to world point [inferred]: scaled by g_9150 and offset by
 * the view origin, wrapped to the map; in the sub-game a linear map. */
/* 8:2bbe */
POINT fn_08_2bbe(POINT pt)
{
    POINT r;
    int16_t oy;
    int16_t ox;
    int32_t lx;
    int32_t ly;

    if (subgame_active == 0) {
        oy = g_2402;
        ox = g_2400;
        if (ox < 0)
            ox += (LO16(g_05a0)) * 8;
        if (oy < 0)
            oy += HI16(g_05a0) * 8;
        lx = (int32_t)ox + (pt.x << g_9150);
        ly = (int32_t)oy + (pt.y << g_9150);
        if (lx > (LO16(g_05a0)) * 8)
            lx -= (LO16(g_05a0)) * 8;
        if (ly > HI16(g_05a0) * 8)
            ly -= HI16(g_05a0) * 8;
        r.x = (int16_t)lx;
        r.y = (int16_t)ly;
        return r;
    }
    r.x = (int16_t)((pt.x - g_88c4.x) * g_88cc / g_88c0.x);
    r.y = (int16_t)((pt.y - g_88c4.y) * g_88cc / g_88c0.x);
    return r;
}

/* Direction to aim from object (t1, i1) at the moving object (t2, i2):
 * a lead from the target's velocity and the shooter's speed [inferred]. */
/* 8:2658 */
int16_t fn_08_2658(int16_t t1, int16_t i1, int16_t t2, int16_t i2)
{
    int32_t u4;
    int32_t u8;
    int32_t uc;
    int32_t side;
    int32_t speed;
    int32_t diff;
    int32_t e2;
    int32_t e1;
    int32_t f1;
    int32_t f2;
    int32_t sq;
    int16_t dist;
    int16_t dx;
    int16_t dy;
    int16_t r;

    dist = fn_08_285a(&dx, &dy, g_1df8[t1][i1].f_04, g_1df8[t2][i2].f_04);
    side = (int32_t)g_1df8[t2][i2].f_0c * dy / dist - (int32_t)g_1df8[t2][i2].f_0e * dx / dist;
    speed = fn_08_35d0(g_1df8[t1][i1].f_0c, g_1df8[t1][i1].f_0e);
    if (speed < 30)
        speed = 50;
    if (speed < side)
        return fn_08_19b0(dx, dy);
    sq = speed * speed - side * side;
    r = (int16_t)fn_08_1290(sq, diff = abs32(speed) - abs32(side));
    e1 = (int32_t)r * dx / dist;
    e2 = (int32_t)dy * side / dist;
    f1 = -((int32_t)dx * side / dist);
    f2 = (int32_t)r * dy / dist;
    return fn_08_19b0((int16_t)(e2 + e1), (int16_t)(f1 + f2));
}
