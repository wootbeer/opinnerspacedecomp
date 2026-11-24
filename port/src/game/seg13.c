/* INSPACE.EXE segment 13 (selector 1060), first source file (13:0000-68ff).
 * Functions from 13:6900 on were a separate source file (they call
 * 2688/2714/4eec far, and are called far): see seg13b.c. */
#include "game.h"

                                                                             

/* 0x23-byte records at DS:57a8 (REC_23 in seg07.c). */

                                                      
                                                      

/* Per-object update loop [inferred]: runs every object of the current
 * type (g_9324) once per tick. u4/uc/u1e/u20/u24 are never used, v6 and
 * w8 are stored but never read: they only reproduce the frame. The two
 * blocks with the lead-target test declare their locals in different
 * orders to get the original's slots [layout-only]. */
/* 13:0000 */
void fn_13_0000(void)
{
    int16_t u4;
    int16_t v6;
    int16_t w8;
    int16_t d;
    int16_t uc;
    int16_t tick;
    int16_t i;
    int16_t r;
    int16_t k;
    int16_t s;
    int16_t j;
    int16_t a;
    int16_t b;
    int16_t u1e;
    int16_t u20;
    int16_t c;
    int16_t u24;
    int16_t w;

    v6 = 1;
    fn_13_675e();
    g_95f6++;
    if (g_95f6 > 8)
        g_95f6 = 0;
    g_134e++;
    if (g_134e > 100)
        g_134e = 0;
    g_92ec[g_9324] = g_9406[g_9324] = g_9316 + 1;
    if (g_1350 < g_1e50) {
        tick = 1;
        g_1350 = g_1e50 + 9000;
    } else
        tick = 0;
    for (i = 0; i <= g_9316; i++) {
        a = g_1df8[g_9324][i].f_22;
        b = g_1df8[g_9324][i].f_24;
        c = g_7090[i].f_010;
        d = g_7090[i].f_0ea;
        if (g_1df8[g_9324][i].f_18)
            continue;
        if (i == main_ship && (g_913a == 2 || g_913c == 2))
            fn_13_3b88();
        else if (i != g_952e || g_9e49 < 1 || g_9e49 > 6)
            fn_08_1b54((char)i | (g_9324 << 8), 1);
        else
            fn_13_3748(i);
        if (!g_7090[i].flag || (i == g_952e && !g_9e5b && g_9e49 == 2)) {
            if (!g_7090[i].f_0e2)
                return;
            g_1df8[g_9324][i].f_26 = 1;
            if (g_7090[i].f_016 < 1) {
                g_1df8[g_9324][i].f_28 = fn_13_100c(i, g_1df8[g_9324][i].f_28);
                fn_13_6716(i);
                g_7090[i].f_016 = 1;
            } else
                g_7090[i].f_016--;
            if (!g_7090[i].flag && g_7090[i].f_084 < g_1e50) {
                g_7090[i].f_0e2 = 0;
                g_1df8[g_9324][i].f_26 = 0;
                fn_12_274a(g_9324, i);
            }
        } else if (g_7090[i].f_0e2) {
            g_1df8[g_9324][i].f_28 = fn_13_100c(i, g_1df8[g_9324][i].f_28);
            fn_13_6716(i);
            if (g_7090[i].f_084 < g_1e50) {
                g_7090[i].f_0e2 = 0;
                g_1df8[g_9324][i].f_26 = 0;
            } else if (g_9320 == 6) {
                if (!g_9134 && i == main_ship)
                    fn_04_277a();
                else
                    fn_04_144c(i, 0);
            }
        } else {
            if (!g_9134 && i == main_ship) {
                fn_04_0000(i);
                if (!(g_95f6 & 1))
                    fn_11_5ab6(i, 4);
            } else if (!(g_95f6 & 1))
                fn_11_5ab6(i, 3);
            if (!g_7090[i].f_0e4 && g_7090[i].f_002 && !g_1df8[g_9324][i].f_2e
                && (g_1df8[g_9324][i].f_1a || fn_13_59e8(14, i))) {
                g_1c72[i]++;
                if (g_1c72[i] > 1) {
                    g_1c72[i] = 0;
                    g_7090[i].f_05c += g_7090[i].f_05a;
                    if (g_7090[i].f_0e6) {
                        if (g_7090[i].f_05b < g_7090[i].f_05c)
                            g_7090[i].f_05c = 0;
                    } else if (g_7090[i].f_05a == 1 && g_7090[i].f_05b < g_7090[i].f_05c) {
                        g_7090[i].f_05c--;
                        g_7090[i].f_05a = -1;
                    } else if (g_7090[i].f_05c < 0) {
                        g_7090[i].f_05c++;
                        g_7090[i].f_05a = 1;
                    }
                    g_1df8[g_9324][i].f_12 = g_7090[i].f_05c * (b + a) + b;
                    fn_13_6716(i);
                }
            } else if (!g_7090[i].f_0e4 && g_7090[i].f_05c && g_1df8[g_9324][i].f_1a) {
                g_1df8[g_9324][i].f_12 = b;
                g_7090[i].f_05c = 0;
                g_7090[i].f_05a = 1;
                fn_13_6716(i);
            } else if (g_7090[i].f_0e9 && g_1df8[g_9324][i].f_1a && c > 0 && c < 7) {
                if (d)
                    g_7090[i].f_010++;
                else
                    g_7090[i].f_010--;
                fn_11_b09c(i, g_7090[i].f_002);
                fn_13_6716(i);
            }
            if ((g_134e % (10 - max(g_9208 * 2, 5)) == 0 && g_1df8[g_9324][i].f_1a)
                || g_134e % (18 - g_9208 * 4) == 0 || g_9320 == 6) {
                if (g_7090[i].f_0e8) {
                    if (((&g_7090[i].f_026[2])[1]) < 50 && rand() % (((&g_7090[i].f_026[2])[1]) * 2 + 1) == 0
                        && fn_11_4c72(i) && i == main_ship)
                        fn_03_332e(0x409, 0x417);
                } else if (g_7090[i].f_0ea && ((&g_7090[i].f_026[2])[1]) < 50
                    && rand() % (((&g_7090[i].f_026[2])[1]) * 2 + 1) == 0 && fn_11_4b00(i) && i == main_ship)
                    fn_03_332e(0x409, 0x417);
                if (!g_9134 && i == main_ship) {
                    w8 = 1;
                    if (g_9320 == 6)
                        fn_04_277a();
                } else {
                    fn_04_0078(i);
                    w8 = 0;
                }
            }
            if (tick && g_7090[i].f_038 == 1 && (g_9134 || i != main_ship))
                fn_04_6e70(i);
            if (g_9320 == 6 && g_1e68 % 9 == 0 && i == main_ship)
                lap_timer();
            if (g_9320 == 6 && g_9eb4 != 1) {
                POINT p;

                p = fn_08_29ea(g_1df8[12][1].f_04);
                if (g_1df8[14][i].f_00.y > 0
                    && ((i - g_9316) * 40 - 90 << g_9156) + p.y > g_1df8[14][i].f_00.y) {
                    g_1df8[14][i].f_0e = 0;
                    g_1df8[14][i].f_0c = g_1df8[14][i].f_0e;
                    if (!g_1df8[14][i].f_2e && g_1e68 % 5 == 0) {
                        g_1df8[14][i].f_28 = min((int16_t)(g_1df8[14][i].f_28 + 1), 4);
                        if (i == main_ship)
                            fn_07_1208();
                        fn_13_6716(i);
                    }
                } else if (g_1df8[14][i].f_0e > -20)
                    g_1df8[14][i].f_0e = -20;
            } else if (g_7090[i].f_016 < 10) {
                if (g_1df8[g_9324][i].f_1a || g_9320 == 6)
                    g_7090[i].f_016 += g_7090[i].f_014;
                else
                    g_7090[i].f_016 += g_7090[i].f_014 * 3;
                if (!g_9134 && i == main_ship) {
                    fn_11_592a();
                    w8 = 1;
                } else {
                    fn_04_0bde(i);
                    w8 = 0;
                }
            } else
                g_7090[i].f_016 -= 10;
        }
        if (g_1df8[g_9324][i].f_1a && g_7090[i].f_026[0] < 50
            && rand() % (g_7090[i].f_026[0] + 30) < 2 && (i != g_952e || g_9e49 != 4))
            fn_07_5b68(g_9324, i, 1);
        if (g_9208 > 1 && g_1df8[g_9324][i].f_1a && g_7090[i].f_038 == 1
            && g_1df8[g_9324][i].f_36 > -1
            && (i != main_ship || g_9134)
            && g_1df8[g_9324][i].f_36 != 10
            && g_65cc[VIEWP(char *, g_1df8[g_9324][i].f_30, 0)[1]].f_0a == 2) {
            if (g_1df8[g_9324][i].f_36 == g_7090[i].f_032.a
                && g_1df8[g_9324][i].f_38 == g_7090[i].f_032.b) {
                for (j = 0; j < g_9146; j++) {
                    int32_t vx, vy, f, e, sp, dist;
                    int16_t py;
                    int16_t px;

                    if (g_1df8[g_507c[j]][g_50e0[j]].f_44 > 500
                        && (g_1df8[g_9324][i].f_36 != g_507c[j]
                            || g_1df8[g_9324][i].f_38 != g_50e0[j])) {
                        dist = fn_08_285a(&py, &px, g_1df8[g_507c[j]][g_50e0[j]].f_04,
                            g_1df8[g_1df8[g_9324][i].f_36][g_1df8[g_9324][i].f_38].f_04);
                        if (dist > 120 && dist < 500) {
                            vx = g_1df8[g_1df8[g_9324][i].f_36][g_1df8[g_9324][i].f_38].f_0c;
                            vy = g_1df8[g_1df8[g_9324][i].f_36][g_1df8[g_9324][i].f_38].f_0e;
                            sp = fn_08_35d0(vx, vy);
                            if (sp) {
                                e = -((vy * px + vx * py) / dist);
                                f = (e << 7) / sp;
                                if (f > 125) {
                                    fn_11_947a(g_9324, i, 2);
                                    break;
                                }
                            }
                        }
                    }
                }
            } else {
                int32_t dist, sp, e, f, vx, vy;
                int16_t px;
                int16_t py;

                dist = fn_08_285a(&py, &px, g_1df8[g_7090[i].f_032.a][g_7090[i].f_032.b].f_04,
                    g_1df8[g_1df8[g_9324][i].f_36][g_1df8[g_9324][i].f_38].f_04);
                if (dist > 120 && dist < 500) {
                    vx = g_1df8[g_1df8[g_9324][i].f_36][g_1df8[g_9324][i].f_38].f_0c;
                    vy = g_1df8[g_1df8[g_9324][i].f_36][g_1df8[g_9324][i].f_38].f_0e;
                    sp = fn_08_35d0(vx, vy);
                    if (sp) {
                        e = -((vy * px + vx * py) / dist);
                        f = (e << 7) / sp;
                        if (f > 125)
                            fn_11_947a(g_9324, i, 2);
                    }
                }
            }
        }
        if (g_1df8[g_9324][i].f_1a && (i != main_ship || g_951a)
            && (g_9e49 < 3 || g_9e49 > 6 || i != g_952e)) {
            k = i + 40;
            if (c == 0 || c == 7)
                g_1df8[g_9324][i].f_10 = (g_1df8[g_9324][i].f_22 + g_1df8[g_9324][i].f_24)
                    * g_1df8[g_9324][i].f_28 + g_1df8[g_9324][i].f_24;
            else
                g_1df8[g_9324][i].f_10 = g_1df8[g_9324][i].f_22 * 16 + g_1df8[g_9324][i].f_24 * 17;
            if (c > 3)
                g_1df8[g_9324][i].f_12 = g_1df8[g_9324][i].f_24 * 2 + g_1df8[g_9324][i].f_22;
            else if (g_7090[i].f_0e9)
                g_1df8[g_9324][i].f_12 = g_1df8[g_9324][i].f_24;
            fn_08_0b76((char)i | (g_9324 << 8), 1, g_39e8[k], 0);
        }
        if (g_1df8[g_9324][i].f_1a) {
            g_943c = i;
            g_943a = g_9324;
            r = fn_08_50aa((char)g_943c | (g_943a << 8));
            if (r != -1) {
                s = fn_08_546c(r, &g_1df8[g_9324][i].f_0c, &g_1df8[g_9324][i].f_0e,
                    g_1df8[g_9324][i].f_20 + 2, g_1df8[g_9324][i].f_44);
                if (g_1df8[HIBYTE(r)][LOBYTE(r)].f_53 && !g_7090[i].f_0ea)
                    fn_13_16ac(i, r);
                else if (HIBYTE(r) == 6 && g_2f4c[g_6670[LOBYTE(r) + 4].f_04.x].f_2c == 6
                    && g_2f4c[g_7090[i].f_0b8[((&g_7090[i].f_016)[1])]].f_2c == 6) {
                    g_1df8[HIBYTE(r)][LOBYTE(r)].f_53 = 1;
                    fn_13_16ac(i, r);
                    g_7090[i].f_0ae[((&g_7090[i].f_016)[1])]++;
                } else
                    fn_08_5df2(g_9324, i, HIBYTE(r), LOBYTE(r), s);
            }
            w = g_7090[i].f_0b8[((&g_7090[i].f_016)[1])];
            if (w == 24 || w == 26)
                repulsive_force_weapon(g_9324, i);
            if ((w == 26 || w == 25) && !(g_1e68 & 7)
                && ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState('Z') & 0x8000)))
                attractive_force_weapon(g_9324, i);
        }
    }
}

/* 13:4eca */
void fn_13_4eca(LPCSTR text)
{
    if (g_131a)
        OutputDebugString(text);
}

/* Debug trace of a class-table change (body compiled out) [inferred]. */
/* 13:2da4 */
void fn_13_2da4(int16_t a, int16_t b, int16_t v)
{
    char buf[110];
}

/* Debug trace of an object-table change (body compiled out) [inferred]. */
/* 13:2db8 */
void fn_13_2db8(int16_t a, int16_t b, int16_t v, int16_t t)
{
    char buf[110];
}

/* 13:5850 */
void fn_13_5850(void)
{
    if (g_95fc) {
        DestroyWindow(g_95fc);
        g_95fc = 0;
    }
}

/* 13:6362 */
void fn_13_6362(void)
{
    if (g_95fe) {
        DestroyWindow(g_95fe);
        g_95fe = 0;
    }
}

/* 13:371c */
int16_t fn_13_371c(int16_t a, int16_t b)
{
    int16_t unused;

    if (a != 12)
        return 0;
    if (!(b & 1))
        return 1;
    return 2;
}

/* 13:6716 */
void fn_13_6716(int16_t i)
{
    if (i == main_ship && !g_951a && !g_238c)
        fn_07_1208();
    else
        g_7090[i].f_156 = g_1e50 - 1;
}

/* 13:4eec */
void fn_13_4eec(int16_t i, int16_t d)
{
    if (d > 0)
        g_7090[i].f_082 += (int32_t)(1000 - g_7090[i].f_082) * d / 1000;
    else
        g_7090[i].f_082 = (int32_t)(g_7090[i].f_082 + d) * 1000 / (int16_t)(d + 1000);
}

/* 13:5878 */
void fn_13_5878(void)
{
    if (g_0a7c && !g_95fc)
        CreateWindow("IS_WATCH", "Ship - Pilot", 0x10cc0000L,
                     g_1ddc, g_1dde, g_1de0 - g_1ddc,
                     GetSystemMetrics(SM_CYCAPTION) + 0x36,
                     g_0016, 0, g_8e66, NULL);
    SetActiveWindow(g_0016);
}

/* Turn direction cur (0..15) one step toward the target [inferred].
 * Mode 2 with the Demon sub-game uses the homing table; modes 3/4 aim
 * off to the side, 5/0x1e straight away. d stays unset for other modes
 * (HANDOFF: never reached; launch code stores modes 2, 3 and 4). */
/* 13:0d6c */
int16_t steer_toward_direction(int16_t y2, int16_t x2, int16_t y1, int16_t x1, int16_t cur,
                                      int16_t mode, int16_t obj, int16_t a, int16_t b, int16_t c)
{
    struct { int16_t y, x; } v;
    int16_t d, u1, u2, u3, u4, u5, u6;

    if (obj > -1) {
        if (g_7090[obj].f_0eb != 0)
            return cur;
        if (g_7090[obj].f_010 > 0 && g_7090[obj].f_010 < 7)
            return cur;
    }
    y2 >>= 3;
    y1 >>= 3;
    x1 >>= 3;
    x2 >>= 3;
    v.x = x1 - x2;
    if (fn_09_88ba(v.x) > (LO16(g_05a0)) >> 1 && g_9320 != 6) {
        v.x = (0 > v.x ? x1 + (LO16(g_05a0)) : x1 - (LO16(g_05a0))) - x2;
    }
    v.y = y1 - y2;
    if (fn_09_88ba(v.y) > HI16(g_05a0) >> 1 && g_9320 != 6) {
        v.y = (0 > v.y ? y1 + HI16(g_05a0) : y1 - HI16(g_05a0)) - y2;
    }
    if (mode == 2) {
        if (g_9320 == 6 && a != 4) {
            d = fn_08_19b0(v.x, v.y);
            if (obj > -1 && g_7090[obj].f_149 && g_7090[obj].f_032.a == 8) {
                if (g_1df8[8][g_7090[obj].f_148 + g_9318 * 2].f_52)
                    d = (g_7090[obj].f_149 + d) & 15;
                else
                    d = (char)(d - g_7090[obj].f_149) & 15;
            }
            if (obj > -1) {
                if (fn_09_88ba(g_1df8[14][obj].f_28 - d) >= 6
                    && fn_09_88ba(g_1df8[14][obj].f_28 - d) <= 10)
                    g_7090[obj].f_061 = 0;
                else
                    g_7090[obj].f_061 = 1;
            }
        } else if (c != 0 || g_9320 == 6) {
            d = fn_08_2658(g_9324, obj, a, b);
            if (g_9320 == 6)
                g_7090[obj].f_061 = 1;
        } else
            d = fn_08_19b0(v.x, v.y);
    } else if (mode == 4)
        d = fn_08_19b0(v.y - (v.x >> 2), -(v.x + (v.y >> 2)));
    else if (mode == 3)
        d = fn_08_19b0(-((v.x >> 2) + v.y), v.x - (v.y >> 2));
    else if (mode == 5 || mode == 0x1e)
        d = fn_08_19b0(-v.x, -v.y);
    if (d < 0 || d > 15)
        return cur;
    if (mode == 0x1e || obj == -100)
        return d;
    if (d == cur)
        return d;
    fn_13_6716(obj);
    if (d < cur) {
        if ((int16_t)(cur - d) < 9)
            cur--;
        else if (++cur > 15)
            cur = 0;
    } else {
        if ((int16_t)(d - cur) < 9)
            cur++;
        else if (--cur < 0)
            cur = 15;
    }
    return cur;
}

/* 13:100c */
int16_t fn_13_100c(int16_t i, int16_t v)
{
    if (g_7090[i].f_0eb != 0)
        return v;
    if (g_7090[i].f_010 > 0 && g_7090[i].f_010 < 7)
        return v;
    v += g_1df8[g_9324][i].f_26;
    if (v >= 16)
        v = 0;
    else if (v <= 0)
        v = 15;
    return v;
}

/* 13:5460 */
void fn_13_5460(HDC hdc, int16_t a, int16_t k, int16_t j, int16_t i, int16_t shift)
{
    int16_t x, y;

    if (a == 0 && g_238c == 0 && g_1df8[j][i].f_0c == 0
        && g_1df8[j][i].f_0e == 0)
        return;
    if (g_6e38[k].f_06) {
        x = (g_6e38[k].f_10 + g_6e38[k].f_16.x) >> shift;
        y = (g_6e38[k].f_12 + g_6e38[k].f_16.y) >> shift;
        SetPixel(hdc, x, y, 0L);
        g_6e38[k].f_06 = 0;
    }
}

/* 13:218a */
void fn_13_218a(int16_t n, LPSTR out)
{
    char key[40];
    char buf[40];

    LoadString(g_9212, 0xaf, key, 40);
    key[4] = 0;
    fn_06_0f1a(n + 1, buf);
    lstrcat(key, buf);
    LoadString(g_9212, 0xaf, buf, 40);
    GetPrivateProfileString(buf, key, "", out, 20, g_96a9);
}

/* 13:59e8 */
int16_t fn_13_59e8(int16_t k, int16_t i)
{
    int16_t w;

    if (k == 0 && g_9458)
        return 1;
    if (k == g_9324 && g_95fe)
        return 1;
    for (w = 0; w < 3; w++) {
        if ((w == 0 && g_0a76 == 2) || (w == 1 && g_0a76 == 3)
            || (w == 2 && g_95fc)) {
            if (g_6e38[w].f_1a.b == k && g_6e38[w].f_1a.a == i)
                return 1;
        }
    }
    return 0;
}

/* Attitude of object i towards object j [inferred]: relation table plus
 * class-vs-class table, adjusted by i's temperament bytes. */
/* 13:2688 */
int16_t fn_13_2688(int16_t i, int16_t j)
{
    int16_t a, b;
    int16_t r;
    int16_t u;

    a = g_96d2[g_7090[i].f_04e].f_38;
    b = g_96d2[g_7090[j].f_04e].f_38;
    u = g_7090[i].f_062[j];
    r = u + g_3824[a][b];
    if (r > 0)
        r += (3 - g_7090[i].f_05d) * 20;
    else
        r += (g_7090[i].f_05e - 3) * 20;
    if (g_92e8)
        return -300;
    return r;
}

/* 13:2dcc */
void fn_13_2dcc(void)
{
    int16_t i;
    int16_t r;

    for (i = 0; i <= g_9316; i++) {
        if (i == main_ship)
            r = 500;
        else
            r = fn_13_2688(i, main_ship);
        if (r < -80)
            g_1df8[g_9324][i].f_46 = 5;
        else if (r < 80)
            g_1df8[g_9324][i].f_46 = 4;
        else
            g_1df8[g_9324][i].f_46 = 7;
    }
}

/* Refresh the smart window (one row per visible object) [inferred]. */
/* 13:6450 */
void fn_13_6450(HDC hdc, int16_t b, int16_t c)
{
    int16_t i, u1, u2, n, got;
    HPALETTE pal;
    RECT r;

    if (!g_95fe)
        return;
    got = 0;
    if (hdc == 0) {
        got = 1;
        hdc = GetDC(g_95fe);
    }
    if (g_920e)
        pal = SelectPalette(hdc, g_920e, 0);
    n = i = 0;
    for (; i <= g_9316; i++) {
        if (i != main_ship && fn_03_0000(g_9324, i)) {
            g_6e38[n + 11].f_1a.a = i;
            g_6e38[n + 11].f_16.x = 2;
            g_6e38[n + 11].f_16.y = n * 0x2e + 2;
            n++;
        }
    }
    if (n != g_95fa) {
        g_95fa = n;
        if (!g_95fa) {
            fn_13_6362();
        } else {
            GetWindowRect(g_95fe, &r);
            MoveWindow(g_95fe, r.left, r.top, r.right - r.left,
                       r.bottom - r.top, TRUE);
        }
    } else if (c == -1) {
        for (i = 0; i < g_95fa; i++)
            fn_13_5a6a(hdc, 0, i * 0x2e + 4, g_9324, g_6e38[i + 11].f_1a.a,
                       i + 11, b, g_95f8);
    } else {
        for (i = 0; i < g_95fa; i++)
            if (g_6e38[i + 11].f_1a.a == c)
                break;
        fn_13_5a6a(hdc, 0, i * 0x2e + 4, g_9324, c, i + 11, b, g_95f8);
    }
    if (pal)
        SelectPalette(hdc, pal, 0);
    if (got) {
        ReleaseDC(g_95fe, hdc);
        hdc = 0;
    }
}

/* 13:675e */
void fn_13_675e(void)
{
    int16_t i;

    for (i = 0; i <= g_9316; i++) {
        if (g_131c || g_7090[i].f_156 + 10000 < g_1e50) {
            if ((g_7090[i].f_156 < g_1e50 && i != main_ship)
                || g_1df8[g_9324][i].f_18 != 0) {
                g_7090[i].f_156 = g_1e50 + 5000;
                fn_13_6890(i);
            }
        }
    }
    fn_13_50b0(0, 0);
    if (g_6e38[g_0a76 - 2].f_1a.b != g_9324)
        fn_13_58dc(0, 0);
    fn_07_64ac(0, 0, -1);
    if (!g_95fe && g_9316 && g_8f74) {
        i = 0;
        g_95fa = 0;
        for (; i <= g_9316; i++)
            if (i != main_ship && fn_03_0000(g_9324, i))
                g_95fa++;
        if (g_95fa)
            PostMessage(g_0016, 0x9b4, 0, 0L);
    }
}

/* Window procedure of the pilot window, class "IS_WATCH" [inferred]. */
/* 13:4f4e */
LRESULT fn_13_4f4e(HWND hwnd, UINT msg, WPARAM wParam,
                              LPARAM lParam)
{
    RECT r;
    RECT rc;
    PAINTSTRUCT ps;
    HDC hdc;
    MINMAXINFO *mm;

    switch (msg) {
    case WM_CREATE:
        g_95fc = hwnd;
        fn_13_57ac();
        break;
    case WM_SETFOCUS:
        g_8f68 = 1;
        break;
    case WM_MOVE:
        GetWindowRect(g_95fc, &r);
        if (r.left != g_1ddc || r.top != g_1dde) {
            CopyRect((LPRECT)&g_1ddc, &r);
            g_8fea = 1;
        }
        SetActiveWindow(g_0016);
        break;
    case WM_GETMINMAXINFO:
        mm = (MINMAXINFO *)lParam;
        mm->ptMinTrackSize.x = 0x36;
        ((MINMAXINFO *)lParam)->ptMinTrackSize.y
            = GetSystemMetrics(SM_CYCAPTION) + 0x36;
        ((MINMAXINFO *)lParam)->ptMaxTrackSize.y
            = GetSystemMetrics(SM_CYCAPTION) + 0x36;
        break;
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        PatBlt(hdc, 0, 0, rc.right, rc.bottom, BLACKNESS);
        lstrcpy(g_8694, "");
        lstrcpy(g_86d0, "");
        fn_13_50b0(hdc, 1);
        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        if (g_95fc) {
            DestroyWindow(g_95fc);
            g_95fc = 0;
        }
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0L;
}

/* Open or refresh the pilot window on the player's target [inferred]. */
/* 13:563c */
int16_t fn_13_563c(int16_t a, int16_t b)
{
    char buf[80];
    char title[100];
    int16_t i, s, k;

    if (!g_95fc && !a && !b) {
        g_6e38[2].f_1a.b = g_9324;
        g_6e38[2].f_1a.a = 0;
        g_6e38[2].f_16.x = 2;
        g_6e38[2].f_16.y = 2;
    }
    if (a && !b && g_95fc) {
        fn_13_5850();
        return 0;
    }
    s = LO16(g_7090[main_ship].f_03e);
    k = HI16(g_7090[main_ship].f_03e);
    if (!b)
        goto skip;
    if (s != 2) {
        for (i = 0; i < g_9406[2]; i++) {
            if (g_52ec[i].f_18.a == g_9324 && g_52ec[i].f_18.b == main_ship
                && g_1df8[2][i].f_18 == 0) {
                s = 2;
                k = i;
                break;
            }
        }
    }
skip:
    if (a || b || !g_95fc) {
        if (a && b) {
            s = g_9324;
            k = main_ship;
        }
        a = 0;
        if (s == g_9324 || s == 2) {
            g_6e38[2].f_1a.b = s;
            g_6e38[2].f_1a.a = k;
            a = 1;
        }
    }
    if (!a) {
        fn_03_045a(6);
        if (g_6e38[2].f_1a.b != g_9324 && g_6e38[2].f_1a.b != 2)
            return 0;
    }
    if (!g_95fc) {
        PostMessage(g_0016, 0x9a0, 0, 0L);
    } else {
        PostMessage(g_95fc, WM_PAINT, 0, 0L);
        fn_13_57ac();
    }
    return 1;
}

/* Window procedure of the smart window, class "IS_SMART" [inferred]
 * (same shape as fn_07_6184). */
/* 13:613a */
LRESULT fn_13_613a(HWND hwnd, UINT msg, WPARAM wParam,
                              LPARAM lParam)
{
    RECT r;
    RECT rc;
    PAINTSTRUCT ps;
    HDC hdc;
    MINMAXINFO *mm;
    UINT cmd;

    switch (msg) {
    case WM_CREATE:
        g_95fe = hwnd;
        g_9606 = GetSystemMenu(hwnd, FALSE);
        AppendMenu(g_9606, MF_SEPARATOR, 0, NULL);
        AppendMenu(g_9606, 0, 0xf0, "1/2x Scale");
        fn_07_63b6(g_9606, "1/2x Scale", g_95f8, 0xf0);
        DrawMenuBar(g_95fe);
        break;
    case WM_SYSCOMMAND:
        switch (cmd = wParam & 0xfff0) {
        case 0xf0:
            fn_07_63b6(g_9606, "1/2x Scale", g_95f8 = !g_95f8, 0xf0);
            GetWindowRect(g_95fe, &r);
            MoveWindow(g_95fe, r.left, r.top, r.right - r.left,
                       r.bottom - r.top, TRUE);
            SetActiveWindow(g_0016);
            break;
        case SC_CLOSE:
            g_8f74 = 0;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    case WM_SETFOCUS:
        g_8f68 = 1;
        break;
    case WM_MOVE:
        GetWindowRect(g_95fe, &r);
        if (r.left != g_1dec || r.top != g_1dee) {
            CopyRect((LPRECT)&g_1dec, &r);
            g_8ff0 = 1;
        }
        SetActiveWindow(g_0016);
        break;
    case WM_GETMINMAXINFO:
        mm = (MINMAXINFO *)lParam;
        mm->ptMinTrackSize.x = mm->ptMaxTrackSize.x = 50 >> g_95f8;
        if (g_95f8)
            mm->ptMinTrackSize.y = mm->ptMaxTrackSize.y
                = GetSystemMetrics(SM_CYCAPTION) + g_95fa * 23 + 3;
        else
            mm->ptMinTrackSize.y = mm->ptMaxTrackSize.y
                = GetSystemMetrics(SM_CYCAPTION) + g_95fa * 46 + 6;
        break;
    case WM_PAINT:
        InvalidateRect(hwnd, NULL, TRUE);
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &ps);
        PatBlt(hdc, 0, 0, rc.right, rc.bottom, BLACKNESS);
        fn_13_6450(hdc, 1, -1);
        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        if (g_95fe) {
            DestroyWindow(g_95fe);
            g_95fe = 0;
        }
        break;
    }
    return 0L;
}

/* Redraw the pilot window (g_95fc): ship cell, name and order lines
 * [inferred]. */
/* 13:50b0 */
void fn_13_50b0(HDC hdc, int16_t b)
{
    int16_t u;
    int16_t k, s;
    int16_t got, ok, changed;
    HPALETTE pal;
    char buf[80];
    char old1[60];
    char old2[60];
    RECT rc;

    if (!g_95fc)
        return;
    k = g_6e38[2].f_1a.a;
    ok = 0;
    s = g_6e38[2].f_1a.b;
    if (s == g_9324 && main_ship == k)
        ok = 1;
    else
        ok = fn_03_0000(s, k);
    if (!ok && !fn_13_563c(0, 0)) {
        fn_13_5850();
        return;
    }
    got = 0;
    if (hdc == 0) {
        got = 1;
        hdc = GetDC(g_95fc);
    }
    if (g_920e)
        pal = SelectPalette(hdc, g_920e, 0);
    fn_13_5a6a(hdc, g_6e38[2].f_16.x, g_6e38[2].f_16.y, s, k, 2, b, 0);
    changed = 0;
    if (g_1c8a <= g_1e50 || g_8694[0] == 0) {
        lstrcpy(old1, g_8694);
        lstrcpy(old2, g_86d0);
        if (s == g_9324) {
            char c;
            if (k == main_ship)
                c = 100;
            else
                c = (char)main_ship;
            fn_03_1d0a(c, k, 3);
        } else
            describe_defender_order_message(main_ship, k, 3);
        if (lstrcmp(old1, g_8694) != 0 || lstrcmp(old2, g_86d0) != 0)
            changed = 1;
    }
    if (g_1c8a <= g_1e50)
        g_1c8a = g_1e50 + 500;
    if (changed) {
        HFONT font;
        DWORD oldtext, oldbk;
        int16_t v;

        GetClientRect(g_95fc, &rc);
        PatBlt(hdc, 0x30, 0, rc.right, 0x30, BLACKNESS);
        font = SelectObject(hdc, g_90fe);
        SetTextAlign(hdc, 0);
        oldbk = SetBkColor(hdc, 0L);
        if (s == g_9324) {
            v = fn_13_2688(k, main_ship);
            if (k == main_ship)
                LoadString(g_9212, 0x7f9, buf, 80);
            else {
                if (g_96d2[g_7090[k].f_04e].f_38
                    == g_96d2[g_7090[main_ship].f_04e].f_38)
                    LoadString(g_9212, 0x7fa, buf, 80);
                else
                    fn_13_218a(g_96d2[g_7090[k].f_04e].f_38, buf);
                fn_11_3f2e(v);
                lstrcat(buf, " - ");
                lstrcat(buf, g_93e0);
            }
            if (v > 80)
                oldtext = SetTextColor(hdc, PALETTERGB(0, 0xb9, 0xff));
            else if (v < -80)
                oldtext = SetTextColor(hdc, PALETTERGB(0xff, 0x6e, 0));
            else
                oldtext = SetTextColor(hdc, PALETTERGB(0xaa, 0xaa, 0xaa));
        } else {
            oldtext = SetTextColor(hdc, RGB(0, 0x80, 0));
            fn_10_a332(buf, 0x9e3, 1, s, k, 0, g_52ec[k].f_18.a,
                       g_52ec[k].f_18.b, 6);
        }
        TextOut(hdc, 0x30, 0, buf, lstrlen(buf));
        if (g_90ee == 1)
            SetTextColor(hdc, RGB(0xff, 0xff, 0xff));
        else
            SetTextColor(hdc, RGB(0xff, 0xff, 0));
        TextOut(hdc, 0x30, 0x10, g_8694, lstrlen(g_8694));
        TextOut(hdc, 0x30, 0x1e, g_86d0, lstrlen(g_86d0));
        SetBkColor(hdc, oldbk);
        SetTextColor(hdc, oldtext);
        SelectObject(hdc, font);
    }
    if (pal)
        SelectPalette(hdc, pal, 0);
    if (got) {
        ReleaseDC(g_95fc, hdc);
        hdc = 0;
    }
}

/* Draw one object cell of a child window [inferred]. */
/* 13:5a6a */
void fn_13_5a6a(HDC hdc, int16_t x, int16_t y, int16_t s, int16_t k, int16_t w, int16_t b, int16_t c)
{
    int16_t draw, stars;

    if (b)
        g_6e38[w].f_14 = 0;
    else {
        g_6e38[w].f_14++;
        if (g_6e38[w].f_14 > 2)
            g_6e38[w].f_14 = 0;
    }
    if (g_6e38[w].f_14 == 0)
        stars = 1;
    else
        stars = 0;
    if (b == 1)
        PatBlt(hdc, x >> c, y >> c, 45 >> c, 45 >> c, BLACKNESS);
    if (g_1df8[s][k].f_18 != 0 || s == 2 || b != 0 || g_9208 < 2)
        stars = 0;
    if (s == g_9324 && !g_131c)
        stars = 0;
    if (stars)
        fn_13_5460(hdc, 0, w, s, k, c);
    draw = 1;
    if (b == 0) {
        if (s == 7 && g_1df8[s][k].f_18 != 0)
            draw = 0;
        if (s == 1)
            draw = 0;
        if (fn_13_371c(s, k))
            draw = 0;
        if (s == 0 && g_57a8[k].f_00 == 0 && g_1df8[0][k].f_51 == 0)
            draw = 0;
        if ((s == 0 || s == 11) && g_1df8[s][k].f_18 != 0
            && g_1df8[s][k].f_51 == 0)
            draw = 0;
        if (s == g_9324)
            draw = 0;
    }
    if (draw)
        fn_13_5c22(hdc, x, y, s, k, w, c);
    if (stars)
        fn_13_54da(hdc, 0, w, s, k, c);
}

/* Redraw the map child window [inferred: g_0a7c, modes 2/3 in g_0a76]. */
/* 13:58dc */
void fn_13_58dc(HDC hdc, int16_t b)
{
    int16_t u1, k, s, w, got, u2;
    HPALETTE pal;

    if (!g_0a7c)
        return;
    if (g_0a76 != 2 && g_0a76 != 3)
        return;
    if (g_9320 == 6 && g_0a76 == 2)
        return;
    w = g_0a76 - 2;
    s = g_6e38[w].f_1a.b;
    k = g_6e38[w].f_1a.a;
    if (s != 7 && s != 12 && !fn_03_0000(s, k)) {
        if (g_0a76 == 3) {
            g_0a76 = 2;
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        }
        return;
    }
    got = 0;
    if (hdc == 0) {
        got = 1;
        hdc = GetDC(g_0a7c);
    }
    if (g_920e)
        pal = SelectPalette(hdc, g_920e, 0);
    fn_13_5a6a(hdc, g_6e38[w].f_16.x, g_6e38[w].f_16.y, s, k, w, b, 0);
    if (pal)
        SelectPalette(hdc, pal, 0);
    if (got) {
        ReleaseDC(g_0a7c, hdc);
        hdc = 0;
    }
}

/* 13:6890 */
void fn_13_6890(int16_t i)
{
    if (g_95fe && i != main_ship)
        fn_13_6450(0, 2, i);
    if (g_95fc && g_6e38[2].f_1a.b == g_9324 && g_6e38[2].f_1a.a == i)
        fn_13_50b0(0, 2);
    if (g_6e38[g_0a76 - 2].f_1a.b == g_9324 && g_6e38[g_0a76 - 2].f_1a.a == i)
        fn_13_58dc(0, 2);
}

/* 13:3678 */
void fn_13_3678(int16_t i)
{
    int16_t e;
    int16_t d;
    int16_t y;
    int16_t x;

    d = fn_08_285a(&y, &x, g_1df8[g_9324][i].f_04,
                   g_1df8[g_7090[i].f_032.a][g_7090[i].f_032.b].f_04);
    e = fn_08_19b0(y, x);
    if (d > 90) {
        if ((e > 10 && e < 14) || (e > 2 && e < 6)) {
            if (fn_13_371c(g_7090[i].f_032.a, g_7090[i].f_032.b) == 2)
                g_7090[i].f_032.b--;
        }
    }
}

/* Set the pilot window's title [inferred]. */
/* 13:57ac */
void fn_13_57ac(void)
{
    char buf[80];
    char title[100];

    fn_03_1542(0, g_6e38[2].f_1a.b, g_6e38[2].f_1a.a, buf, 0);
    fn_11_3fd4(buf, 2);
    lstrcpy(title, buf);
    if (g_9324 == g_6e38[2].f_1a.b) {
        lstrcat(title, " - ");
        fn_17_8e60(g_6e38[2].f_1a.a, buf);
        fn_11_3fd4(buf, 2);
        lstrcat(title, buf);
    }
    SetWindowText(g_95fc, title);
}

/* 13:638a */
void fn_13_638a(void)
{
    int16_t i;

    if (g_0a7c && !g_95fe) {
        i = 0;
        g_95fa = 0;
        for (; i <= g_9316; i++)
            if (i != main_ship && fn_03_0000(g_9324, i))
                g_95fa++;
        if (!g_95fa)
            return;
        for (i = 0; i < 8; i++) {
            g_6e38[i + 11].f_1a.b = g_9324;
            g_6e38[i + 11].f_1a.a = i;
            g_6e38[i + 11].f_16.x = 2;
            g_6e38[i + 11].f_16.y = i * 0x2e + 2;
        }
        CreateWindow("IS_SMART", "", 0x10cc0000L, g_1dec, g_1dee, 50, 150,
                     g_0016, 0, g_8e66, NULL);
    }
    SetActiveWindow(g_0016);
}

/* 13:2e60 */
void fn_13_2e60(int16_t p, int16_t q, int16_t t)
{
    int16_t u;

    if (t == -1)
        t = 9;
    if (q != main_ship) {
        fn_13_4eec(p, g_131e[t] * 5);
        fn_13_4eec(q, g_131e[t] * 5);
    } else {
        fn_13_4eec(p, g_131e[t] * 12);
        fn_13_4eec(q, g_131e[t] * 12);
    }
    if (t == 9)
        return;
    if (t == 2 || t == 3) {
        if (g_96d2[g_7090[q].f_04e].f_38 == g_96d2[g_7090[p].f_04e].f_38)
            return;
        if (fn_13_2688(p, q) > 70)
            return;
    }
    g_7090[p].f_0f6[q][t] += (char)g_131e[t];
}

/* 13:3302 */
void fn_13_3302(void)
{
    int16_t i, u;

    if (g_9320 == 6)
        return;
    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].f_038 == 2 && g_7090[i].f_148 == g_7090[i].f_032.a
            && g_7090[i].f_149 == g_7090[i].f_032.b)
            continue;
        if (g_7090[main_ship].f_038 != 1
            && g_7090[i].f_148 == g_7090[main_ship].f_032.a
            && g_7090[i].f_149 == g_7090[main_ship].f_032.b && i != main_ship
            && (fn_13_2688(i, main_ship) > 0
                || g_96d2[g_7090[i].f_04e].f_38
                   == g_96d2[g_7090[main_ship].f_04e].f_38))
            fn_03_06ec(main_ship, 14, i, 0xb8);
        g_7090[i].f_148 = g_7090[i].f_149 = -1;
    }
}

/* 13:2f30 */
void fn_13_2f30(int16_t i)
{
    int16_t u1, u2, flag;
    char buf[162];
    char buf2[218];

    flag = 1;
    if (i != main_ship)
        return;
    if (g_7090[i].f_006 < 0) {
        g_7090[i].f_006 = 0;
        return;
    }
    lstrcpy(buf, g_8630);
    if (g_1df8[g_9324][i].f_1a != 0 || i == main_ship)
        fn_03_1d0a(100, i, (i != main_ship || g_9134) ? 1 : 0);
    if (lstrcmp(buf, g_8630)) {
        g_058c = 1;
        fn_13_4eca(g_8630);
        lstrcpy(buf, "\n\r");
        fn_13_4eca(buf);
    }
}

/* Send the list-11 entry: reuse a free one or the fullest; with b, the
 * first suitable object follows it (only one) [inferred]. */
/* 13:498e */
void fn_13_498e(int16_t a, int16_t b)
{
    int16_t i, best, bi, sel, found;

    found = 0;
    for (i = 0; i < g_92ec[11]; i++) {
        if (g_1df8[11][i].f_18 != 0) {
            fn_13_4ba0(a, i, b);
            sel = i;
            found = 1;
            break;
        }
    }
    if (!found) {
        best = 0;
        for (i = 0; i < g_92ec[11]; i++) {
            if (g_8560[i].f_04 > best) {
                best = g_8560[i].f_04;
                bi = i;
            }
        }
        g_1df8[11][bi].f_66(11, bi);
        fn_13_4ba0(a, bi, b);
        sel = bi;
        fn_07_2080(11);
    }
    if (b) {
        for (i = 0; i <= g_9316; i++) {
            if (g_7090[i].flag
                && ((g_96d2[g_7090[i].f_04e].f_38 == 7 && g_7090[i].f_05e > 1)
                    || g_96d2[g_7090[i].f_04e].f_38 == 3)) {
                g_7090[i].f_052 = 0;
                g_7090[i].f_006 = g_7090[i].f_032.a = 11;
                g_7090[i].f_032.b = g_7090[i].f_008 = sel;
                g_7090[i].f_03c = g_7090[i].f_038 = 2;
                break;
            }
        }
    }
}

/* Launch REC70 entry i of list 11 for object a (b: full transfer)
 * [inferred]. */
/* 13:4ba0 */
void fn_13_4ba0(int16_t a, int16_t i, int16_t b)
{
    int16_t j, u1, u2, u3;

    g_8560[i].f_04 = 0;
    g_8560[i].f_06 = 500;
    if (!g_92e8 || a == main_ship) {
        if (b) {
            for (j = 1; j < 10; j++) {
                if (g_7090[a].cnt > j) {
                    g_8560[i].f_0c[j] = g_7090[a].f_0b8[j];
                    g_8560[i].f_20[j] = g_7090[a].f_0ae[j];
                } else
                    g_8560[i].f_20[j] = g_8560[i].f_0c[j] = -1;
                g_7090[a].f_0ae[j] = g_7090[a].f_0b8[j] = 0;
            }
            g_8560[i].f_00 = 1;
            g_8560[i].f_02 = g_7090[a].f_0ce;
            g_7090[a].cnt = 1;
        } else {
            g_8560[i].f_00 = 3;
            g_8560[i].f_02 = min(g_7090[a].f_0ce, 400);
        }
        g_7090[a].f_0ce -= g_8560[i].f_02;
        g_1df8[11][i].f_4a = 0x1d;
    } else {
        g_1df8[11][i].f_4a = 0x1d;
        g_8560[i].f_00 = 2;
    }
    g_8560[i].f_08 = g_9324;
    g_8560[i].f_0a = a;
    g_1df8[11][i].f_22 = (24 << g_9156) >> 1;
    g_1df8[11][i].f_24 = (4 << g_9156) >> 1;
    g_1df8[11][i].f_20 = 0xb8;
    g_1df8[11][i].f_18 = 0;
    g_1df8[11][i].f_04.x = g_1df8[g_9324][a].f_20 / 2
        + g_1df8[g_9324][a].f_04.x - g_1df8[11][i].f_20 / 2;
    g_1df8[11][i].f_04.x += g_1050[(g_1df8[g_9324][a].f_28 + 8) & 0xf].x
        * g_1df8[g_9324][a].f_20 / 16;
    g_1df8[11][i].f_04.x %= (int16_t)((LO16(g_05a0)) * 8);
    g_1df8[11][i].f_04.y = g_1df8[g_9324][a].f_20 / 2
        + g_1df8[g_9324][a].f_04.y - g_1df8[11][i].f_20 / 2;
    g_1df8[11][i].f_04.y += g_1050[(g_1df8[g_9324][a].f_28 + 8) & 0xf].y
        * g_1df8[g_9324][a].f_20 / 16 % (HI16(g_05a0) * 8);
    g_1df8[11][i].f_04.y %= (int16_t)(HI16(g_05a0) * 8);
    VIEW(int32_t, g_1df8[11][i].f_0c, 0) = VIEW(int32_t, g_1df8[g_9324][a].f_0c, 0);
    g_1df8[11][i].f_0c += g_1050[(g_1df8[14][a].f_28 + 8) & 0xf].x * 5;
    g_1df8[11][i].f_0e += g_1050[(g_1df8[14][a].f_28 + 8) & 0xf].y * 5;
    g_1df8[11][i].f_44 = 0x65;
    g_1df8[11][i].f_53 = 0;
    g_1df8[11][i].f_51 = 0;
    fn_07_2080(11);
}

/* 13:4ac4 */
void fn_13_4ac4(int16_t a)
{
    int16_t j;

    fn_13_498e(a, 0);
    for (j = 0; j <= g_9316; j++) {
        if (g_1df8[14][j].f_18 == 0 && j != a && g_7090[j].f_038 == 1
            && g_7090[j].f_032.a == 14 && g_7090[j].f_032.b == a) {
            if (g_7090[j].f_0d6 == -1) {
            g_8680[a] = j;
            g_7090[j].f_052 = 0x16;
            g_7090[j].f_054 = 14;
            g_7090[j].f_056 = a;
            g_7090[j].f_098 = g_1e50 + 50000;
            g_7090[j].f_0ed = 1;
            g_7090[j].f_094 = g_1e50 + 500;
            if (a == main_ship) {
                g_a163 = 5;
                g_a14d[5]++;
            }
            return;
            } else {
            g_8680[a] = j;
            g_7090[a].f_038 = 2;
            g_7090[a].f_032.a = 11;
            g_7090[a].f_032.b = 0;
            }
        }
    }
}

/* Show/hide the game's child windows [inferred]. */
/* 13:65f2 */
int16_t fn_13_65f2(int16_t cmd)
{
    int16_t r;

    r = 1;
    switch (cmd) {
    case 3:
        if (g_95fc)
            ShowWindow(g_95fc, SW_HIDE);
        if (g_9458)
            ShowWindow(g_9458, SW_HIDE);
        if (g_95fe)
            ShowWindow(g_95fe, SW_HIDE);
        break;
    case 2:
        if (g_95fc)
            ShowWindow(g_95fc, SW_SHOW);
        if (g_9458)
            ShowWindow(g_9458, SW_SHOW);
        if (g_95fe)
            ShowWindow(g_95fe, SW_SHOW);
        if (g_95fc || g_9458 || g_95fe)
            SetActiveWindow(g_0016);
        break;
    case 1:
        fn_13_5850();
        fn_07_63f2();
        fn_13_6362();
        break;
    case 0:
        r = 0;
        if (g_8f72 && !g_9458) {
            PostMessage(g_0016, 0x9aa, 0, 0L);
            r = 1;
        }
        if (g_8f74 && !g_95fe) {
            PostMessage(g_0016, 0x9b4, 0, 0L);
            r = 1;
        }
        break;
    }
    return r;
}

/* 13:54da */
void fn_13_54da(HDC hdc, int16_t a, int16_t k, int16_t j, int16_t i, int16_t shift)
{
    int16_t y, x;

    if (a == 0 && g_238c == 0 && g_1df8[j][i].f_0c == 0
        && g_1df8[j][i].f_0e == 0)
        return;
    if (a == 0) {
        g_6e38[k].f_10 -= g_1df8[j][i].f_0c >> 2;
        g_6e38[k].f_12 -= g_1df8[j][i].f_0e >> 2;
        if (g_238c) {
            g_6e38[k].f_10 += g_2390 >> 2;
            g_6e38[k].f_12 += g_2392 >> 2;
        }
        if (g_6e38[k].f_10 < 0) {
            g_6e38[k].f_10 = 43;
            g_6e38[k].f_12 = rand() % 43;
            g_6e38[k].f_08 = 0xffff00L;
        } else if (g_6e38[k].f_10 > 43) {
            g_6e38[k].f_10 = 0;
            g_6e38[k].f_12 = rand() % 43;
            g_6e38[k].f_08 = 0xffff00L;
        }
        if (g_6e38[k].f_12 < 0) {
            g_6e38[k].f_12 = 43;
            g_6e38[k].f_10 = rand() % 43;
            g_6e38[k].f_08 = 0xffff00L;
        } else if (g_6e38[k].f_12 > 43) {
            g_6e38[k].f_12 = 0;
            g_6e38[k].f_10 = rand() % 43;
            g_6e38[k].f_08 = 0xffff00L;
        }
    }
    x = (g_6e38[k].f_10 + g_6e38[k].f_16.x) >> shift;
    y = (g_6e38[k].f_12 + g_6e38[k].f_16.y) >> shift;
    if (GetPixel(hdc, x, y) == 0) {
        SetPixel(hdc, x, y, g_6e38[k].f_08);
        g_6e38[k].f_06 = 1;
    } else {
        g_6e38[k].f_06 = 0;
    }
}

/* Draw object (s, k) scaled by c/d into its sprite DC; when it overlaps
 * object (a, b) (a == 15: the point at DS:88c8) mask it into that one's
 * DC too, then mark both for redraw [inferred]. */
/* 13:3d40 */
void draw_scaled_object(int16_t s, int16_t k, int16_t a, int16_t b, int16_t c,
                                   int16_t d)
{
    POINT dd, p1, p2, q1, q2, q3, sz;
    int16_t h1, sc, h2, o1, o2, off;
    HBITMAP bmp, bmp2;
    HGDIOBJ old2, old1;
    HDC memdc, memdc2;
    HPALETTE oldpal;

    if (d == 0)
        d = 1;
    p1 = fn_08_29ea(g_1df8[s][k].f_04);
    if (a != 15)
        p2 = fn_08_29ea(g_1df8[a][b].f_04);
    else
        p2 = fn_08_29ea(g_88c8);
    dd.x = p2.x - p1.x;
    dd.y = p2.y - p1.y;
    h1 = g_1df8[s][k].f_22;
    o1 = g_1df8[s][k].f_24;
    sc = (int16_t)(h1 * c) / d;
    off = o1 + (int16_t)(h1 - sc) / 2;
    if (a != 15) {
        h2 = g_1df8[a][b].f_22;
        o2 = g_1df8[a][b].f_24;
    } else {
        h2 = -10;
        o2 = 0;
    }
    if (dd.x < (int16_t)(-2 - h2) || dd.y < (int16_t)(-2 - h2) || dd.x > (int16_t)(h1 + 2) || dd.y > (int16_t)(h1 + 2)
        || a == 15) {
        if (a != 15) {
            PatBlt(g_1df8[a][b].f_3c, 0, 0, o2 * 2 + h2, o2 * 2 + h2,
                   BLACKNESS);
            BitBlt(g_1df8[a][b].f_3c, o2, o2, h2, h2, g_1df8[a][b].f_3a,
                   g_1df8[a][b].f_28 * (o2 + h2) + o2, o2, SRCCOPY);
        }
        if (sc == h1) {
            BitBlt(g_1df8[s][k].f_3c, o1, o1, h1, h1, g_1df8[s][k].f_3a,
                   g_1df8[s][k].f_28 * (o1 + h1) + o1, o1, SRCCOPY);
        } else {
            SetStretchBltMode(g_1df8[s][k].f_3c, 3);
            PatBlt(g_1df8[s][k].f_3c, 0, 0, o1 * 2 + h1, o1 * 2 + h1,
                   BLACKNESS);
            StretchBlt(g_1df8[s][k].f_3c, off, off, sc, sc,
                       g_1df8[s][k].f_3a,
                       g_1df8[s][k].f_28 * (o1 + h1) + o1, o1, h1, h1,
                       SRCCOPY);
        }
    } else {
        if (dd.x < 0) {
            q2.x = -dd.x;
            q3.x = 0;
            sz.x = min((int16_t)(o2 * 2 + h2 + dd.x), h1);
        } else {
            q2.x = 0;
            q3.x = dd.x;
            sz.x = min((int16_t)(h1 - dd.x), (int16_t)(o2 * 2 + h2));
        }
        if (dd.y < 0) {
            q2.y = -dd.y;
            q3.y = 0;
            sz.y = min((int16_t)(o2 * 2 + h2 + dd.y), h1);
        } else {
            q2.y = 0;
            q3.y = dd.y;
            sz.y = min((int16_t)(h1 - dd.y), (int16_t)(o2 * 2 + h2));
        }
        PatBlt(g_1df8[s][k].f_3c, 0, 0, o1 * 2 + h1, o1 * 2 + h1,
               BLACKNESS);
        BitBlt(g_1df8[s][k].f_3c, o1 + q3.x, o1 + q3.y, sz.x, sz.y,
               g_1df8[a][b].f_3a,
               g_1df8[a][b].f_28 * (o2 + h2) + o2 + q2.x, o2 + q2.y,
               SRCCOPY);
        memdc = CreateCompatibleDC(g_13dc);
        bmp = CreateCompatibleBitmap(g_13dc, o1 * 2 + h1, o1 * 2 + h1);
        if (g_920e)
            oldpal = SelectPalette(memdc, g_920e, 0);
        old1 = SelectObject(memdc, bmp);
        PatBlt(memdc, 0, 0, o1 * 2 + h1, o1 * 2 + h1, BLACKNESS);
        if (sc != h1) {
            SetStretchBltMode(memdc, 3);
            StretchBlt(memdc, off, off, sc, sc, g_1df8[s][k].f_3a,
                       g_1df8[s][k].f_28 * (o1 + h1) + o1, o1, h1, h1,
                       SRCCOPY);
        } else
            BitBlt(memdc, o1, o1, h1, h1, g_1df8[s][k].f_3a,
                   g_1df8[s][k].f_28 * (o1 + h1) + o1, o1, SRCCOPY);
        SelectObject(memdc, old1);
        bmp2 = fn_10_6ec6(bmp);
        SelectObject(memdc, bmp);
        memdc2 = CreateCompatibleDC(g_13dc);
        old2 = SelectObject(memdc2, bmp2);
        BitBlt(g_1df8[s][k].f_3c, o1, o1, h1, h1, memdc2, o1, o1, SRCAND);
        BitBlt(g_1df8[s][k].f_3c, o1, o1, h1, h1, memdc, o1, o1, SRCPAINT);
        if (dd.x > 0) {
            q1.x = dd.x;
            q3.x = 0;
            sz.x = min((int16_t)(o2 * 2 + h2), (int16_t)(h1 - dd.x));
        } else {
            q1.x = 0;
            q3.x = -dd.x;
            sz.x = min((int16_t)(o2 * 2 + h2 + dd.x), h1);
        }
        if (dd.y > 0) {
            q1.y = dd.y;
            q3.y = 0;
            sz.y = min((int16_t)(o2 * 2 + h2), (int16_t)(h1 - dd.y));
        } else {
            q1.y = 0;
            q3.y = -dd.y;
            sz.y = min((int16_t)(o2 * 2 + h2 + dd.y), h1);
        }
        PatBlt(g_1df8[a][b].f_3c, 0, 0, o2 * 2 + h2, o2 * 2 + h2, BLACKNESS);
        BitBlt(g_1df8[a][b].f_3c, o2, o2, h2, h2, g_1df8[a][b].f_3a,
               g_1df8[a][b].f_28 * (o2 + h2) + o2, o2, SRCCOPY);
        BitBlt(g_1df8[a][b].f_3c, o2 + q3.x, o2 + q3.y, sz.x, sz.y, memdc2,
               o1 + q1.x, o1 + q1.y, SRCAND);
        BitBlt(g_1df8[a][b].f_3c, o2 + q3.x, o2 + q3.y, sz.x, sz.y, memdc,
               o1 + q1.x, o1 + q1.y, SRCPAINT);
        if (g_920e)
            SelectPalette(memdc, oldpal, -1);
        SelectObject(memdc, old1);
        DeleteDC(memdc);
        DeleteObject(bmp);
        SelectObject(memdc2, old2);
        DeleteDC(memdc2);
        DeleteObject(bmp2);
    }
    g_1df8[s][k].f_1a = 1;
    g_1df8[s][k].f_10 = g_1df8[s][k].f_28 * (o1 + h1) + o1;
    fn_08_0b76((char)k | (s << 8), 1, g_1df8[s][k].f_3a, 0);
    g_1df8[s][k].f_1a = 0;
    if (a != 15) {
        g_1df8[a][b].f_10 = g_1df8[a][b].f_28 * (o2 + h2) + o2;
        fn_08_0b76((char)b | (a << 8), 1, g_1df8[a][b].f_3a, 0);
    }
}

/* Steer the player's ship toward the point at DS:88c8 [inferred]. */
/* 13:3b88 */
void fn_13_3b88(void)
{
    int16_t d, a, b, u1, w, u2, u3, u4;
    POINT p;

    p = g_1df8[g_9324][main_ship].f_04;
    w = g_1df8[g_9324][main_ship].f_20;
    p.x += w >> 1;
    p.y += w >> 1;
    d = fn_08_285a(&a, &b, p, g_88c8);
    if (g_913a == 2) {
        g_1df8[g_9324][main_ship].f_28 = (g_1df8[g_9324][main_ship].f_28 + 1) & 15;
        if (d < 5) {
            g_1df8[g_9324][main_ship].f_0c = 0;
            g_1df8[g_9324][main_ship].f_0e = 0;
            fn_12_26a4(14, main_ship);
            g_913a = 0;
            return;
        }
        draw_scaled_object(g_9324, main_ship, 15, 0, d + 50, 200);
        g_1df8[g_9324][main_ship].f_0c = (int16_t)(a * 70) / d;
        g_1df8[g_9324][main_ship].f_0e = (int16_t)(b * 70) / d;
    } else {
        g_1df8[g_9324][main_ship].f_28 = (g_1df8[g_9324][main_ship].f_28 - 1) & 15;
        if (d > 150) {
            fn_12_26a4(14, main_ship);
            g_913c = 1;
            return;
        }
        draw_scaled_object(g_9324, main_ship, 15, 0, d + 50, 200);
        g_1df8[g_9324][main_ship].f_0c = 70;
        g_1df8[g_9324][main_ship].f_0e = 0;
    }
    fn_08_1b54((char)main_ship | (g_9324 << 8), 1);
}

/* Draw object k of type s into a 45x45 cell at (x, y) >> c [inferred]. */
/* 13:5c22 */
void fn_13_5c22(HDC hdc, int16_t x, int16_t y, int16_t s, int16_t k, int16_t w, int16_t c)
{
    int16_t bmi, h, w8, off, sw;
    HGDIOBJ oldbr;
    int32_t rop;
    int16_t flag;
    POINT src;
    POINT pt;
    int16_t e, i;
    HGDIOBJ oldbmp;
    HDC memdc;
    int16_t u, t;

    w8 = g_1df8[s][k].f_20 >> 3;
    h = g_1df8[s][k].f_22;
    sw = g_1df8[s][k].f_24;
    src.y = g_1df8[s][k].f_12;
    if (s == g_9324 && !g_131c)
        src.x = sw;
    else
        src.x = g_1df8[s][k].f_28 * (sw + h) + sw;
    SetStretchBltMode(hdc, 3);
    flag = 0;
    rop = 0xcc0020L;
    switch (s) {
    case 2:
        bmi = 0;
        oldbr = SelectObject(hdc, g_576c[g_52ec[k].f_12 + g_0b6a]);
        rop = 0xc000caL;
        break;
    case 14:
        bmi = g_7090[k].f_050 + 0x28;
        if (g_7090[k].f_0e8)
            flag = 1;
        break;
    case 9:
        bmi = 0x16;
        break;
    case 7:
        if (g_1df8[s][k].f_18) {
            src.x = sw * 6 + h * 5;
            src.y = sw;
        } else
            src.x = g_1df8[7]->f_10;
        bmi = 5;
        w8 /= 2;
        break;
    case 8:
        bmi = g_3d50[k].f_1e;
        break;
    case 0:
        if (g_57a8[k].f_02 == 0) {
            bmi = 13;
            src.x = (sw + h) * k + sw;
        } else {
            bmi = k + 14;
            src.x = (g_57a8[k].f_02 / 2 - 1) * (sw + h) + sw;
        }
        break;
    case 11:
        bmi = 0x1d;
        break;
    }
    if (fn_13_371c(s, k)) {
        off = 1;
        pt.x = (int16_t)(x + 1) >> c;
        pt.y = (int16_t)(y + 1) >> c;
        i = fn_10_6c02(500, sw = 0, -1);
        e = CreateCompatibleDC(hdc);
        oldbmp = SelectObject(e, i);
        memdc = SelectPalette(e, g_920e, 0);
        h = w8 = 0x29;
        StretchBlt(hdc, pt.x, pt.y, 0x29 >> c, 0x29 >> c, e, 0, 0, h, h, SRCCOPY);
        SelectPalette(e, memdc, 0);
        SelectObject(e, oldbmp);
        DeleteDC(e);
        DeleteObject(i);
        return;
    }
    if (s == 1) {
        off = (int16_t)(0x2b - w8) / 2;
        pt.x = (int16_t)(off + x) >> c;
        pt.y = (int16_t)(off + y) >> c;
        memdc = CreateCompatibleDC(hdc);
        oldbmp = SelectObject(memdc, g_4e94[k]);
        StretchBlt(hdc, pt.x, pt.y, w8 >> c, w8 >> c, memdc, sw, sw, h, h,
                   SRCCOPY);
        SelectObject(memdc, oldbmp);
        DeleteDC(memdc);
        return;
    }
    if (g_1df8[s][k].f_18) {
        if (s == 0 && g_57a8[k].f_19) {
            sw = g_1df8[1]->f_24;
            h = g_1df8[1]->f_22;
            for (i = off = 0; i < 4; i++) {
                switch (i) {
                case 0:
                    u = t = 0;
                    break;
                case 1:
                    t = 0x16;
                    u = 0;
                    break;
                case 2:
                    t = 0;
                    u = 0x16;
                    break;
                case 3:
                    u = t = 0x16;
                    break;
                }
                pt.x = (int16_t)(t + off + x) >> c;
                pt.y = (int16_t)(u + off + y) >> c;
                e = g_57a8[k].f_1b[i];
                if (g_1df8[1][e].f_18 == 0 && g_6038[e] == k) {
                    memdc = CreateCompatibleDC(g_13dc);
                    oldbmp = SelectObject(memdc, g_4e94[e]);
                    StretchBlt(hdc, pt.x, pt.y, 0x14 >> c, 0x14 >> c, memdc, sw, sw,
                               h, h, SRCCOPY);
                    SelectObject(memdc, oldbmp);
                    DeleteDC(memdc);
                } else
                    PatBlt(hdc, pt.x, pt.y, 0x14 >> c, 0x14 >> c, BLACKNESS);
            }
            return;
        }
    }
    if (s == 0 && g_1df8[s][k].f_18 && g_1df8[s][k].f_51 == 0)
        return;
    off = (int16_t)(0x2b - w8) / 2;
    w8 >>= c;
    pt.x = (int16_t)(off + x) >> c;
    pt.y = (int16_t)(off + y) >> c;
    StretchBlt(hdc, pt.x, pt.y, w8, w8, g_39e8[bmi], src.x, src.y, h, h, rop);
    if (s == 2)
        SelectObject(hdc, oldbr);
    if (flag) {
        t = SelectObject(hdc, g_5ea8[1]);
        PatBlt(hdc, pt.x, pt.y, w8, w8, 0xa000c9L);
        SelectObject(hdc, t);
    }
}

/* 13:1fc2 */
void spawn_gun_shot(int16_t s, int16_t k)
{
    int16_t i, j, u1, w, cnt;
    int16_t u[8];
    int16_t found;

    w = g_1df8[s][k].f_20;
    if (g_9208 > 0) {
        i = cnt = found = 0;
        for (; i < g_0594; i++) {
            if (g_6098[i].f_7a == g_9324 && g_6098[i].f_7c == main_ship)
                found = 1;
            if (g_6098[i].z[1][5] == -1)
                cnt++;
        }
        if (!found && cnt < 2)
            return;
    }
    for (i = 0; i < g_0594; i++) {
        if (g_6098[i].z[1][5] == -1) {
            j = g_6098[i].f_80 = g_6098[i].f_7e = g_6098[i].z[1][5] = 0;
            for (; j < 2; j++) {
                g_6098[i].f_48[j / 6][j % 6] = g_6098[i].f_30[j / 6][j % 6] = -100;
                fn_08_0764(i, j);
            }
            g_6098[i].f_30[0][0] = w / 2 + (g_1050[g_1df8[s][k].f_28].x * 8
                                       + g_1df8[s][k].f_04.x);
            g_6098[i].f_48[0][0] = w / 2 + (g_1050[g_1df8[s][k].f_28].y * 8
                                       + g_1df8[s][k].f_04.y);
            g_6098[i].f_7a = s;
            g_6098[i].f_7c = k;
            g_6098[i].f_84 = g_6098[i].count = 1;
            g_6098[i].f_82 = 0;
            g_6098[i].z[1][2] = g_1050[g_1df8[s][k].f_28].x * 3;
            g_6098[i].z[1][3] = g_1050[g_1df8[s][k].f_28].y * 3;
            g_6098[i].z[1][4] = 20;
            if (g_9320 == 6) {
                g_6098[i].z[1][4] = 0x24;
                fn_11_5626(i);
            }
            g_6098[i].z[1][4] = (int32_t)g_6098[i].z[1][4] * max(HI16(g_90ea), LO16(g_90ea))
                             / 1000;
            fn_10_754a(3, 0x1e, i, 2);
            return;
        }
    }
}

/* Returns (type << 8) | index of the nearest object [inferred]: first among
 * those ahead of the player's ship (within 3 directions), preferring the
 * one at DS:943e/9440 for 5 s after DS:52d8, else of all types up to
 * g_9324. */
/* Returns (type << 8) | index of the nearest object [inferred]: first among
 * those ahead of the player's ship (within 3 directions), preferring the
 * one at DS:943e/9440 for 5 s after DS:52d8, else of all types up to
 * g_9324. */
/* 13:2206 */
int16_t fn_13_2206(void)
{
    int16_t u1, i, j, bs, bk, bd, d, y, x;
    int16_t u2[9];
    int16_t dir2, dir, n;
    int16_t ss[20];
    int16_t kk[20];
    POINT p;
    POINT dp;
    DWORD dt;

    dt = g_1e50 - g_52d8;
    bs = -1;
    bd = 20000;
    dir = g_1df8[g_9324][main_ship].f_28;
    for (i = n = 0; i < g_9146; i++) {
        if (g_507c[i] == g_9324 && g_507c[i] == main_ship)
            continue;
        p = g_1df8[g_507c[i]][g_50e0[i]].f_00;
        dp.x = p.x - g_1df8[g_9324][main_ship].f_00.x;
        dp.y = p.y - g_1df8[g_9324][main_ship].f_00.y;
        dir2 = fn_08_19b0(dp.x, dp.y);
        if (dir < 14) {
            if (dir > 2) {
                if (fn_09_88ba(dir - dir2) < 3) {
                ss[n] = g_507c[i];
                kk[n] = g_50e0[i];
                n++;
            }
            } else if ((int16_t)(dir2 - dir) < 3 || dir2 == 15) {
                ss[n] = g_507c[i];
                kk[n] = g_50e0[i];
                n++;
            }
        } else if ((int16_t)(dir - dir2) < 3 || dir2 == 0) {
                ss[n] = g_507c[i];
                kk[n] = g_50e0[i];
                n++;
            }
    }
    if (n) {
        if (dt < 5000) {
            for (i = 0; i < n; i++)
                if (ss[i] == g_943e && kk[i] == g_9440
                    && fn_03_0000(g_943e, g_9440))
                    return (g_943e << 8) | (char)g_9440;
        }
        for (i = 0; i < n; i++) {
            if (fn_03_0000(ss[i], kk[i])) {
                d = fn_08_285a(&y, &x, g_1df8[g_9324][main_ship].f_04,
                               g_1df8[ss[i]][kk[i]].f_04);
                if (d < bd) {
                    bs = ss[i];
                    bk = kk[i];
                    bd = d;
                }
            }
        }
    }
    if (bs > -1)
        return (bs << 8) | (char)bk;
    for (i = 0; i <= g_9324; i++) {
        for (j = 0; j < g_9406[i]; j++) {
            if (i == g_9324 && j == main_ship)
                continue;
            if (fn_03_0000(i, j)) {
                d = fn_08_285a(&y, &x, g_1df8[g_9324][main_ship].f_04,
                               g_1df8[i][j].f_04);
                if (d < bd) {
                    bs = i;
                    bk = j;
                    bd = d;
                }
            }
        }
    }
    return (bs << 8) | (char)bk;
}

/* Aim child window w's compass at its target and colour it by distance
 * [inferred]. s and k stay unset for w > 2 (as in the game). */
/* 13:24aa */
void fn_13_24aa(int16_t w)
{
    int16_t u1, dx, dy, s, k, d, r, u2, u3;
    POINT pt;

    if (w == 0) {
        if (g_094e)
            return;
        if (LO16(g_7090[main_ship].f_03e) == -1)
            return;
        if (!fn_03_0000(LO16(g_7090[main_ship].f_03e), HI16(g_7090[main_ship].f_03e))
            && fn_13_371c(LO16(g_7090[main_ship].f_03e), HI16(g_7090[main_ship].f_03e)) != 1) {
            r = fn_13_2206();
            fn_03_00f4(main_ship, HIBYTE(r), LOBYTE(r));
        }
        s = LO16(g_7090[main_ship].f_03e);
        k = HI16(g_7090[main_ship].f_03e);
    } else if (w == 1) {
        if (g_6e38[1].f_1a.b == -1)
            return;
        s = g_6e38[1].f_1a.b;
        k = g_6e38[1].f_1a.a;
    } else if (w == 2) {
        s = g_6e38[2].f_1a.b;
        k = g_6e38[2].f_1a.a;
    }
    if (s < 0)
        return;
    if (g_1df8[s][k].f_1a)
        pt = g_1df8[s][k].f_00;
    else
        pt = fn_08_29ea(g_1df8[s][k].f_04);
    dx = pt.x - g_1df8[g_9324][main_ship].f_00.x;
    dy = pt.y - g_1df8[g_9324][main_ship].f_00.y;
    g_6e38[w].f_00 = fn_08_19b0(dx, dy) / 2;
    d = (int16_t)fn_08_1290((int32_t)dy * dy + (int32_t)dx * dx,
                        (int32_t)(int16_t)(fn_09_88ba(dy) + fn_09_88ba(dx)));
    if (d < 300)
        g_6e38[w].f_0c = PALETTERGB(255, 255, 255);
    else if (d < 480)
        g_6e38[w].f_0c = PALETTERGB(255, 255, 0);
    else if (d < 740)
        g_6e38[w].f_0c = PALETTERGB(0, 255, 0);
    else
        g_6e38[w].f_0c = PALETTERGB(0, 0x72, 0);
    fn_11_3ed8(w);
}

/* Build object k's 16 rotation frames into its sprite DC [inferred]. */
/* 13:4710 */
void fn_13_4710(int16_t k)
{
    HBITMAP bm2, old2, bm1, old1, bm3, old3;
    HDC dc2, dc1, dc3;
    HPALETTE pal;
    int16_t u1, u2, j, size, w, m, off, h;

    fn_10_754a(0x6a, g_9324, k, 1);
    size = (32 << g_9156) >> 1;
    bm1 = fn_10_6308(-1, -1, fn_10_6c02(0xe6, 0, -1), -1);
    bm2 = fn_10_6ec6(bm1);
    dc1 = CreateCompatibleDC(g_13dc);
    old1 = SelectObject(dc1, bm1);
    if (g_920e)
        pal = SelectPalette(dc1, g_920e, 0);
    dc2 = CreateCompatibleDC(g_13dc);
    old2 = SelectObject(dc2, bm2);
    SelectObject(g_3a38[k], g_39c4[k]);
    bm3 = fn_10_6ec6(g_3b20[k]);
    g_39c4[k] = SelectObject(g_3a38[k], g_3b20[k]);
    dc3 = CreateCompatibleDC(g_13dc);
    old3 = SelectObject(dc3, bm3);
    w = g_1df8[g_9324][k].f_22;
    h = g_1df8[g_9324][k].f_24;
    m = min(w, size);
    off = max((int16_t)(w - size) / 2, 0);
    BitBlt(dc3, 0, -((9 << g_9156) >> 1), w * 16 + h * 17, w + h * 2,
           dc3, 0, 0, SRCAND);
    for (j = 0; j < 16; j++) {
        BitBlt(g_3a38[k], (h + w) * j + h + off, h + off, m, m,
               dc2, (j % 5) * size, 0, SRCAND);
        BitBlt(g_3a38[k], (h + w) * j + h + off, h + off, m, m,
               dc1, (j % 5) * size, 0, SRCPAINT);
        BitBlt(g_3a38[k], (h + w) * j + h, h, w, w,
               dc3, (h + w) * j + h, h, 0x00220326L);
    }
    SelectObject(dc1, old1);
    SelectObject(dc2, old2);
    SelectObject(dc3, old3);
    if (pal)
        SelectPalette(dc1, pal, 0);
    DeleteDC(dc1);
    DeleteDC(dc3);
    DeleteDC(dc2);
    DeleteObject(bm2);
    DeleteObject(bm3);
    DeleteObject(bm1);
}

/* Animate the three explosion surfaces [inferred]. */
/* 13:447a */
void fn_13_447a(void)
{
    int16_t i, s;
    HBITMAP bm2, old2, bm1, old1;
    HDC dc2, dc1;
    HPALETTE pal;
    POINT p;
    int16_t s2;

    for (i = 0; i < 3; i++) {
        if (g_915c[i].f_1a > 0) {
            fn_08_08a6(i);
            g_915c[i].f_00.x += g_915c[i].f_08.x;
            g_915c[i].f_00.y += g_915c[i].f_08.y;
            g_915c[i].f_08.x -= g_915c[i].f_08.x >> 4;
            g_915c[i].f_08.y -= g_915c[i].f_08.y >> 4;
            if (g_915c[i].f_1a == 1) {
                bm1 = fn_10_6308(-1, -1, fn_10_6c02(0xe6, 0, -1), -1);
                bm2 = fn_10_6ec6(bm1);
                dc1 = CreateCompatibleDC(g_13dc);
                old1 = SelectObject(dc1, bm1);
                if (g_920e)
                    pal = SelectPalette(dc1, g_920e, 0);
                dc2 = CreateCompatibleDC(g_13dc);
                old2 = SelectObject(dc2, bm2);
                if (!subgame_active)
                    s = (32 << g_9156) >> 1;
                else
                    s = ((g_9156 << 6) + 32) / 3;
                BitBlt(g_915c[i].f_0c, 0, 0, s * 5, s, dc2, 0, 0, SRCAND);
                BitBlt(g_915c[i].f_0c, 0, 0, s * 5, s, dc1, 0, 0, SRCPAINT);
                BitBlt(g_915c[i].f_0c, 0, 0, s * 5, s, g_915c[i].f_0e, 0, 0,
                       0x00220326L);
                fn_07_1208();
                SelectObject(dc1, old1);
                SelectObject(dc2, old2);
                if (pal)
                    SelectPalette(dc1, pal, 0);
                DeleteDC(dc1);
                DeleteDC(dc2);
                DeleteObject(bm2);
                DeleteObject(bm1);
            } else if (g_915c[i].f_1a == 0x32 || g_915c[i].f_1a == 0x38
                       || g_915c[i].f_1a == 0x3d || g_915c[i].f_1a == 0x3f
                       || g_915c[i].f_1a == 0x41 || g_915c[i].f_1a == 0x42) {
                p.x = g_915c[i].f_00.x + 0x80;
                p.y = g_915c[i].f_00.y + 0x80;
                fn_07_5d6a(p.x, p.y, 1, rand() % 60 - 30, rand() % 60 - 30);
            }
            g_915c[i].f_1a++;
            if (g_915c[i].f_1a == g_915c[i].f_1c) {
                if (!subgame_active)
                    s2 = (32 << g_9156) >> 1;
                else
                    s2 = ((g_9156 << 6) + 32) / 3;
                g_915c[i].f_1a = 0;
                PatBlt(g_13dc, g_915c[i].f_04.x, g_915c[i].f_04.y, s2, s2,
                       BLACKNESS);
                fn_10_37d0(i);
            }
        }
    }
}

/* Aftermath of object r being collected by n [inferred]. Compares
 * f_004 with both type and index (as the game does). */
/* 13:3008 */
void ship_collected_aftermath(OBJREF r, int16_t n)
{
    int16_t i, t, k, chance, v;

    t = r.type;
    k = r.idx;
    if ((g_7090[n].f_052 == 9 || g_7090[n].f_052 == 12)
        && g_7090[n].f_054 == t && g_7090[n].f_056 == k) {
        fn_03_06ec(g_7090[n].f_058, g_9324, n, 0x20);
        g_7090[n].f_052 = 0;
        g_7090[n].f_094 = g_1e50;
        for (i = 0; i <= g_9316; i++) {
            if (i != n && g_7090[i].f_006 == t && g_7090[i].f_006 == k
                && g_7090[i].f_036 == 2 && g_1df8[g_9324][i].f_18 == 0
                && g_7090[i].flag) {
                fn_03_06ec(n, g_9324, i, 0x49);
                fn_13_2714(i, g_7090[n].f_058, -5, -20, 0, -1);
                fn_03_06ec(g_7090[n].f_058, g_9324, i, 0x4a);
                fn_04_5e8e(i, n, 0x5a, 2);
            }
        }
    } else {
        for (i = 0; i <= g_9316; i++) {
            if (i != n && g_7090[i].f_032.a == t && g_7090[i].f_038 == 2
                && g_7090[i].f_032.b == k && g_1df8[g_9324][i].f_18 == 0
                && g_7090[i].flag) {
                if (g_96d2[g_7090[i].f_04e].f_38 == 7 && t == 6
                    && i == main_ship)
                    report_crime(n, 4);
                else if (g_7090[i].f_148 == t && g_7090[i].f_149 == k
                         && (t == 0 || t == 11)) {
                    fn_03_06ec(n, g_9324, i, 0x49);
                    if (t == 4)
                        v = 0x32;
                    else
                        v = 0x5a;
                    fn_04_5e8e(i, n, v, 2);
                }
            }
        }
    }
    if (n != main_ship && g_7090[n].f_0ce > 350 && g_9208 + 3 > g_9316
        && g_96d2[g_7090[n].f_04e].f_38 != 3 && g_0992 + 20 < g_932a) {
        chance = (g_7090[n].f_0ce - 200) / 50
                 + g_3824[3][g_96d2[g_7090[n].f_04e].f_38] / -100
                 - g_9316 / 2 + g_9334 / 2 + 2;
        if (g_7090[n].f_026[0] < 40)
            chance++;
        if (rand() % 30 < chance && g_9334 > 0) {
            for (i = 0; i <= g_9316; i++)
                if (!g_7090[i].flag || g_96d2[g_7090[i].f_04e].f_38 == 0
                    || !g_7090[i].f_0cd)
                    fn_13_adbe(n, 3, 0x69);
        }
    }
}

/* Change the relations after object a did something (c to the class
 * table, d to the per-object table) to object b; e: let bystanders react
 * [inferred]. */
/* 13:2714 */
void fn_13_2714(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f)
{
    int16_t j, ca, cb, cj, i, div;

    if (g_9320 == 7)
        return;
    if (f == 2)
        e = 0;
    ca = g_96d2[g_7090[a].f_04e].f_38;
    cb = g_96d2[g_7090[b].f_04e].f_38;
    if (fn_09_88ba(c) > 1
        && (g_3824[ca][cb] < -300 || g_3824[ca][cb] > 300
            || g_3824[cb][ca] < -300 || g_3824[cb][ca] > 300))
        c /= 2;
    if (fn_09_88ba(c) > 1
        && (g_3824[ca][cb] < -450 || g_3824[ca][cb] > 450
            || g_3824[cb][ca] < -450 || g_3824[cb][ca] > 450))
        c /= 3;
    if (g_3824[ca][cb] < -800 || g_3824[ca][cb] > 800
        || g_3824[cb][ca] < -800 || g_3824[cb][ca] > 800)
        c = 0;
    if (a == main_ship || b == main_ship)
        i = 1;
    if (b == a)
        return;
    if (d < 0) {
        if (g_7090[a].f_038 == 4 && g_7090[a].f_032.b == b) {
            d <<= 1;
            c <<= 1;
        }
        d += (3 - g_7090[a].f_05e) * d * 10 / 100;
    } else
        d += (3 - g_7090[b].f_05d) * d * 10 / 100;
    if (cb != ca) {
        if (c < 0 && g_7090[b].f_054 == g_9324 && g_7090[b].f_056 == a
            && g_7090[b].f_052 >= 2 && g_7090[b].f_052 <= 4) {
            g_3824[ca][cb] += c / 2;
            g_3824[cb][ca] += c / 6;
            fn_13_2da4(ca, cb, c / 2);
            fn_13_2da4(cb, ca, c / 6);
        } else if (g_3824[ca][cb] * c > 0) {
            g_3824[ca][cb] += c / 2;
            g_3824[cb][ca] += c / 6;
            fn_13_2da4(ca, cb, c / 2);
            fn_13_2da4(cb, ca, c / 6);
        } else {
            g_3824[ca][cb] += c;
            g_3824[cb][ca] += c / 3;
            fn_13_2da4(ca, cb, c);
            fn_13_2da4(cb, ca, c / 3);
        }
    }
    if (d < 0 && g_7090[b].f_054 == g_9324 && g_7090[b].f_056 == a
        && g_7090[b].f_052 >= 2 && g_7090[b].f_052 <= 4) {
        g_7090[a].f_062[b] += d / 2;
        fn_13_2e60(a, b, f);
        g_7090[b].f_062[a] += d / 8;
        fn_13_2db8(a, b, d / 2, f);
        fn_13_2db8(b, a, d / 8, f);
    } else if ((int16_t)(fn_13_2688(a, b) * d) > 0) {
        g_7090[a].f_062[b] += (int16_t)(d * 2) / 3;
        fn_13_2e60(a, b, f);
        g_7090[b].f_062[a] += d / 4;
        fn_13_2db8(a, b, d / 3, f);
        fn_13_2db8(b, a, d / 12, f);
    } else {
        g_7090[a].f_062[b] += d;
        fn_13_2e60(a, b, f);
        g_7090[b].f_062[a] += d / 3;
        fn_13_2db8(a, b, d, f);
        fn_13_2db8(b, a, d / 4, f);
    }
    if (e) {
        for (i = 0; i <= g_9316; i++) {
            if (i != a && i != b && !g_1df8[g_9324][i].f_18
                && g_7090[i].flag) {
                j = i;
                cj = g_96d2[g_7090[i].f_04e].f_38;
                if (fn_09_88ba(g_3824[cj][cb]) < 350) {
                    if (fn_13_2688(i, a) < -100) {
                        if (g_7090[a].f_032.a == g_9324 && g_7090[a].f_032.b == i
                            && g_7090[a].f_038 == 1 && g_7090[b].f_038 == 1
                            && g_7090[b].f_032.a == g_9324
                            && g_7090[b].f_032.b == a) {
                            div = 3;
                            fn_03_06ec(b, g_9324, i, 0x51);
                        } else
                            div = 11;
                        if (cj != cb) {
                            g_3824[cj][cb] -= (int16_t)(c * 3) / div;
                            fn_13_2da4(ca, cb, -((int16_t)(c * 3) / div));
                        }
                        g_7090[j].f_062[b] -= (int16_t)(d * 3) / div;
                        fn_13_2db8(j, b, -((int16_t)(d * 3) / div), 20);
                        if (((g_7090[a].f_032.a == g_9324 && g_7090[a].f_032.b == j
                              && g_7090[a].f_038 == 1)
                             || (g_7090[j].f_032.a == g_9324
                                 && g_7090[j].f_032.b == a
                                 && g_7090[j].f_038 == 1))
                            && d < 0)
                            fn_13_2e60(j, b, 6);
                    } else if (fn_13_2688(j, a) > 100) {
                        if (cj != cb) {
                            g_3824[cj][cb] += c / 4;
                            fn_13_2da4(ca, cb, c / 4);
                        }
                        g_7090[j].f_062[b] += d / 4;
                        fn_13_2db8(j, b, d / 4, 20);
                        if ((cj == ca || fn_13_2688(j, a) > 180) && d < 0)
                            fn_13_2e60(j, b, 3);
                    }
                    if (g_7090[j].f_062[b] > 200)
                        g_7090[j].f_062[b] = 200;
                    if (g_7090[j].f_062[b] < -200)
                        g_7090[j].f_062[b] = -200;
                }
            }
        }
    }
    if (g_7090[a].f_062[b] > 200)
        g_7090[a].f_062[b] = 200;
    if (g_7090[a].f_062[b] < -200)
        g_7090[a].f_062[b] = -200;
    if (g_7090[b].f_062[a] > 200)
        g_7090[b].f_062[a] = 200;
    if (g_7090[b].f_062[a] < -200)
        g_7090[b].f_062[a] = -200;
    if (b == main_ship && HI16(g_7090[main_ship].f_03e) == a && g_0a76 == 2)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
}

/* Nearest target for object n of list type [inferred]: (type << 8) | index,
 * or -1. */
/* 13:1076 */
int16_t fn_13_1076(int16_t type, int16_t n)
{
    char pad[24];
    int16_t bt, bk, best, py, px, d, u28, ex, ey, ek, nn;
    int16_t u32, u34, u36, u38;
    int16_t i;
    int16_t u3c, u3e, u40;
    int16_t f20, t, k, u48, own, ok;
    int32_t dx, dy, ly, lx, r, len;

    nn = n;
    if (type == g_9324) {
        own = 1;
        ex = g_7090[n].f_032.a;
        ey = g_7090[n].f_032.b;
        ek = g_7090[n].f_038;
    } else if (type == 6) {
        own = 0;
        ex = g_6670[n + 4].f_00.x;
        ey = g_6670[n + 4].f_00.y;
        ek = 2;
    }
    f20 = g_1df8[type][n].f_20;
    bt = -1;
    best = 20000;
    for (i = 0; i < g_9318 + g_9146; i++) {
        if (i < g_9146) {
            t = g_507c[i];
            k = g_50e0[i];
        } else {
            t = 12;
            k = (i - g_9146) * 2 + 1;
        }
        ok = 1;
        if ((t == type && k == n) || t == 2 || t == 9 || t == 4
            || (ek == 2 && t == ex && k == ey) || (ek == 2 && t == 0))
            ok = 0;
        if (ok) {
            d = fn_08_285a(&py, &px, g_1df8[type][n].f_04, g_1df8[t][k].f_04);
            if (d < 300 && d > 0) {
                dx = (int16_t)(g_1df8[type][n].f_0c - g_1df8[t][k].f_0c);
                dy = (int16_t)(g_1df8[type][n].f_0e - g_1df8[t][k].f_0e);
                len = fn_08_35d0(dx, dy);
                ly = py;
                lx = px;
                r = (lx * dy + ly * dx) / d;
                if (r > 0) {
                    d -= r * 3 / 2;
                    if (d < best) {
                        if (d < 60 || (t == 8 && g_9318 * 2 > k && d < 120)) {
                            if (g_9320 != 6 || g_9eb5 || t != 8) {
                                best = d;
                                bt = t;
                                bk = k;
                            }
                        }
                    }
                }
            }
        }
    }
    if (bt != -1)
        return (bt << 8) | (char)bk;
    return -1;
}

/* Combat rating of object n into f_0d6 [inferred]. */
/* 13:33d6 */
void fn_13_33d6(int16_t n)
{
    int16_t i, v6, v8, va, u1, u2, v10, u3, v14;

    v10 = g_96d2[g_7090[n].f_04e].f_1e / 20;
    if (g_7090[n].f_0d6 != -1) {
        v6 = g_96d2[g_7090[n].f_04e].f_12 * 100 / (20 - 3 * g_6e24[g_7090[n].f_0d6].f_35)
           + g_96d2[g_7090[n].f_04e].f_14 * 80 / (20 - 3 * g_6e24[g_7090[n].f_0d6].f_36)
           + g_96d2[g_7090[n].f_04e].f_10 * 80 / (20 - 3 * g_6e24[g_7090[n].f_0d6].f_34);
        if (g_96d2[g_7090[n].f_04e].f_28 != -1) {
            v6 += g_96d2[g_7090[n].f_04e].f_16 * 100 / (20 - 3 * g_6e24[g_7090[n].f_0d6].f_37);
            v6 /= 16;
        } else
            v6 /= 12;
    } else
        v6 = g_96d2[g_7090[n].f_04e].f_10;
    v6 = max((int16_t)((int32_t)(int16_t)(g_1df8[g_9324][n].f_44 + v10) * v6 / 86), 1);
    v14 = g_7090[n].f_00c;
    if (g_7090[n].f_0d6 != -1)
        v14 = (int32_t)v14 * ((g_6e24[g_7090[n].f_0d6].f_33 + 10) * 10) / 100;
    va = ((v14 * 2 - g_7090[n].f_00e) * 10 / (g_1df8[g_9324][n].f_44 + v10)
          - g_7090[n].f_014 / 10) * 2;
    v8 = 0;
    for (i = 1; i < g_7090[n].cnt; i++)
        v8 += g_1332[g_7090[n].f_0b8[i]] / ((int16_t)(i + 1) / 2);
    if (!g_96d2[g_7090[n].f_04e].f_4c)
        v6 = (int16_t)(v6 * 3) / 4;
    if (g_96d2[g_7090[n].f_04e].f_4a)
        v6 = (int16_t)(v6 * 6) / 5;
    if (g_96d2[g_7090[n].f_04e].f_a7)
        v6 = (int16_t)(v6 * 6) / 5;
    if (!g_96d2[g_7090[n].f_04e].f_42)
        va = (int16_t)(va * 5) / 6;
    va = (int16_t)(va * 5) / 6;
    v6 = (int16_t)(v6 * 6) / 5;
    if ((int16_t)(v6 * 5) < va)
        va = v6 * 5;
    if ((int16_t)(va * 5) < v6)
        v6 = va * 5;
    g_7090[n].f_0d8 = min((int32_t)(g_7090[n].f_026[0] / 2 + 50) * (int16_t)(va + v8 + v6), 0x7fbcL);
}

/* Spawn a list-5 object next to object n of list type [inferred: k 4/5
 * picks its f_044; t > 24 picks event 0x1b over 0x19]. Note the g_5eac
 * loop stores the same two slots five times (sic). */
/* 13:1318 */
void fn_13_1318(int16_t type, int16_t n, int16_t t, int16_t k)
{
    int16_t i, j, u8, u0a, ok, done;

    ok = 0;
    if (type == g_9324) {
        for (j = 1; j < g_7090[n].cnt; j++)
            if (g_7090[n].f_0b8[j] == k) {
                if (g_7090[n].f_01e > 40) {
                    g_7090[n].f_01e = max(g_7090[n].f_01e - g_2f4c[g_7090[n].f_0b8[j]].f_36, 0);
                    ok = 1;
                }
                break;
            }
    } else
        ok = 1;
    if (!ok)
        return;
    if (g_1df8[type][n].f_1a == 0 || (g_9208 + 2) * 2 <= g_9406[5])
        return;
    i = -1;
    done = 0;
    do {
        i++;
        if (g_92ec[5] <= i) {
            g_92ec[5] = i + 1;
            GlobalUnlock(g_9100[5]);
            g_9100[5] = GlobalReAlloc(g_9100[5], (int32_t)max(g_92ec[5], 1) * (int32_t)sizeof *g_1df8[0], GHND);
            g_1df8[5] = (REC_70 *)GlobalLock(g_9100[5]);
            g_1df8[5][i].f_44 = 120;
            g_1df8[5][i].f_42 = 100;
            g_1df8[5][i].f_4c = 0xff;
            g_1df8[5][i].f_62 = fn_11_3914;
            g_1df8[5][i].f_5e = fn_07_570a;
            g_1df8[5][i].f_53 = 0;
            g_1df8[5][i].f_54 = 0;
            g_1df8[5][i].f_32 = -1;
            g_1df8[5][i].f_12 = g_1df8[5][i].f_24;
            g_1df8[5][i].f_2e = 0;
            g_5a4c[i].f_00 = -1;
            g_9406[5] = i + 1;
        }
        if (g_5a4c[i].f_00 == -1) {
            done = 1;
            g_5a4c[i].f_10 = g_5a4c[i].f_00 = 0;
            g_5a4c[i].f_08 = type;
            g_5a4c[i].f_0a = n;
            if (k == 4)
                g_1df8[5][i].f_44 = 200;
            else if (k == 5)
                g_1df8[5][i].f_44 = 120;
            g_1df8[5][i].f_18 = 0;
            g_5a4c[i].f_12 = 0;
            g_1df8[5][i].f_2e = 0;
            for (j = 0; j < 5; j++)
                g_5eac[i][6] = g_5eac[i][0] = -100;
            g_5a4c[i].f_04 = type;
            g_5a4c[i].f_06 = n;
            g_1df8[5][i].f_0c = g_1050[g_1df8[type][n].f_28].x * 6;
            g_1df8[5][i].f_0e = g_1050[g_1df8[type][n].f_28].y * 6;
            g_1df8[5][i].f_04.x = g_1050[g_1df8[type][n].f_28].x
                * (g_1df8[type][n].f_20 / 32 + 6) + g_1df8[type][n].f_20 / 2
                + g_1df8[type][n].f_04.x - 32;
            g_1df8[5][i].f_04.y = g_1050[g_1df8[type][n].f_28].y
                * (g_1df8[type][n].f_20 / 32 + 6) + g_1df8[type][n].f_20 / 2
                + g_1df8[type][n].f_04.y - 32;
            g_5a4c[i].f_02 = t;
            g_1df8[5][i].f_0c += g_1df8[type][n].f_0c;
            g_1df8[5][i].f_0e += g_1df8[type][n].f_0e;
            if (type == g_9324 && n == main_ship)
                fn_10_744c(0x69);
            if (t > 24)
                fn_10_754a(0x1b, 5, i, 1);
            else
                fn_10_754a(0x19, 5, i, 1);
            break;
        }
    } while (!done);
    fn_07_2080(5);
}

/* Steps of the g_9e49 docking sequence for object n against list 7
 * object 0 (g_1e14) [inferred]. The POINTs a, b are computed and unused
 * (sic). */
/* 13:3748 */
void fn_13_3748(int16_t n)
{
    int16_t d, dy, dx, h, w, u;
    POINT b, a;

    if (g_9e49 == 3) {
        if (!g_7090[g_952e].flag)
            g_9e5b = g_7090[g_952e].flag;
        g_7090[g_952e].flag = 1;
        a = g_1df8[g_9324][n].f_04;
        b = g_1df8[7]->f_04;
        h = g_1df8[7]->f_20;
        b.x += h >> 1;
        b.y += h >> 1;
        w = g_1df8[g_9324][n].f_20;
        a.x += w >> 1;
        a.y += w >> 1;
        d = fn_08_285a(&dy, &dx, g_1df8[g_9324][n].f_04, g_1df8[7]->f_04);
        if (g_9e5b == 0) {
            g_1df8[g_9324][n].f_26 = 1;
            if (g_7090[n].f_016 < 1) {
                g_1df8[g_9324][n].f_28 = fn_13_100c(n, g_1df8[g_9324][n].f_28);
                fn_13_6716(n);
                g_7090[n].f_016 = 1;
            } else
                g_7090[n].f_016--;
        }
        if (d < 5) {
            g_1df8[g_9324][n].f_0c = 0;
            g_1df8[g_9324][n].f_0e = 0;
            fn_12_26a4(g_9324, g_952e);
            fn_12_26a4(7, 0);
            VIEW(struct {
        int16_t f_00;
        int16_t f_02;
    }, g_9e41.f_00, 0).f_00 = -1;
            VIEW(struct {
        int16_t f_00;
        int16_t f_02;
    }, g_9e41.f_00, 0).f_02 = 50;
            g_9e45 = 5;
            fn_10_754a(0x23, 7, g_9e4f = 0, 1);
            g_9e49 = 4;
            g_6e10 = g_1e50 + 1100;
            g_1df8[g_9324][n].f_04.x = g_1df8[7]->f_04.x + 2;
        } else {
            g_1df8[7]->f_28 = g_9e45;
            draw_scaled_object(g_9324, n, 7, 0, d + 50, g_9e53 + 50);
            g_1df8[g_9324][n].f_0c = (int16_t)(dy * 70) / d;
            g_1df8[g_9324][n].f_0e = (int16_t)(dx * 70) / d;
            fn_08_1b54((char)n | (g_9324 << 8), 1);
        }
    }
    if (g_9e49 == 6 && g_1df8[7]->f_2e == 0) {
        if (g_9e47 == 15) {
            a = g_1df8[g_9324][n].f_04;
            b = g_1df8[7]->f_04;
            h = g_1df8[7]->f_20;
            b.x += h >> 1;
            b.y += h >> 1;
            w = g_1df8[g_9324][n].f_20;
            a.x += w >> 1;
            a.y += w >> 1;
            d = fn_08_285a(&dy, &dx, g_1df8[g_9324][n].f_04, g_1df8[7]->f_04);
            if (dy == 0 && dx == 0) {
                dy = -10;
                d = 10;
            }
            if (d > g_9e53 || !g_7090[g_952e].flag) {
                fn_10_754a(0x23, 7, 0, 1);
                fn_12_26a4(g_9324, g_952e);
                fn_12_26a4(7, 0);
                VIEW(struct {
        int16_t f_00;
        int16_t f_02;
    }, g_9e41.f_00, 0).f_02 = 50;
                g_9e4f = 0;
                VIEW(struct {
        int16_t f_00;
        int16_t f_02;
    }, g_9e41.f_00, 0).f_00 = -1;
                fn_07_2080(7);
                g_9e49 = 8;
                g_7090[g_952e].f_147 = 0;
            } else if (d) {
                g_1df8[7]->f_28 = g_9e45;
                draw_scaled_object(g_9324, n, 7, 0, min(d, g_9e53) + 50, g_9e53 + 50);
                g_1df8[g_9324][n].f_0c = (int16_t)(dy * -50) / d;
                g_1df8[g_9324][n].f_0e = (int16_t)(dx * -50) / d;
                g_1df8[g_9324][n].f_28 = fn_08_19b0(g_1df8[g_9324][n].f_0c,
                                                     g_1df8[g_9324][n].f_0e);
                fn_08_1b54((char)n | (g_9324 << 8), 1);
            }
        } else if (g_9e47 == 2)
            fn_10_754a(0x23, 7, 0, 1);
        else if (g_9e47 == 14) {
            if (g_952e == main_ship)
                fn_10_744c(0x6e);
            fn_10_754a(0x1c, 7, 0, 1);
        }
    }
}

/* Object n touches (collects) object r: pickups, rescued ships, cargo
 * [inferred]. r is read as a WORD (HIBYTE/LOBYTE load order) and passed
 * on as the OBJREF it is; the cast is only for the matching load order. */
/* 13:16ac */
void fn_13_16ac(int16_t n, WORD r)
{
    int16_t j, m, t, k, bt, bi, y, x, d, best, i, u1;
    char buf[40];

    t = HIBYTE(r);
    k = LOBYTE(r);
    if (!g_1df8[t][k].f_53)
        return;
    if (n == g_952e && g_9e49 >= 1 && g_9e49 <= 6)
        return;
    if (!g_7090[n].flag && (t != 11 || g_8560[k].f_0a != n)) {
        fn_08_45e0(g_9324, n, 1);
        return;
    }
    if (g_7090[n].f_0ea || g_7090[n].f_0e8)
        return;
    if (t == 0 && g_1df8[0][k].f_2f < 0)
        return;
    PatBlt(g_13dc, g_1df8[t][k].f_00.x, g_1df8[t][k].f_00.y,
           g_1df8[t][k].f_22, g_1df8[t][k].f_22, BLACKNESS);
    fn_13_6716(n);
    fn_08_7d70(&g_1df8[t][k].f_0c, &g_1df8[t][k].f_0e,
               &g_1df8[g_9324][n].f_0c, &g_1df8[g_9324][n].f_0e,
               &g_1df8[t][k].f_00.x, &g_1df8[t][k].f_00.y,
               &g_1df8[g_9324][n].f_00.x, &g_1df8[g_9324][n].f_00.y,
               g_1df8[t][k].f_22, g_1df8[g_9324][n].f_22);
    g_7090[main_ship].f_156 = g_1e50 - 1;
    if (t == 0) {
        if (!g_1df8[t][k].f_51 && g_96d2[g_7090[n].f_04e].f_42) {
            g_1df8[t][k].f_18 = 1;
            g_1df8[t][k].f_51 = 11;
            g_1df8[t][k].f_48 = n;
            ship_collected_aftermath(*(OBJREF *)&r, n);
            if (g_9320 == 6 && fn_04_8d3a() != n) {
                report_crime(n, 8);
                for (i = 0; i < 2; i++)
                    fn_13_2714(fn_04_8d3a(), n, -50, -80, 1, 2);
            }
            fn_07_5ae8(k, 1);
            fn_07_3a42(k);
            fn_13_4eec(n, 0x23);
            if (g_1df8[t][k].f_53 == 2) {
                g_7090[n].f_0ce = g_7090[n].f_0ce - 100 < 0
                                  ? 0 : g_7090[n].f_0ce - 100;
                fn_03_06ec(n, 7, 0, 0x48);
                if (n == main_ship && g_9134 < 2) {
                    if (flow_interactive && !g_9134) {
                        flow_interactive = 0;
                        g_9134 = 2;
                    } else if (flow_interactive && g_9134) {
                        flow_interactive = 0;
                        g_9134 = 3;
                    } else if (!flow_interactive && g_9134)
                        g_9134 = 4;
                    if (g_9134 > 2) {
                        LoadString(g_9212, 0x6a4, buf, 40);
                        lstrcpy(g_8630, buf);
                        LoadString(g_9212, 0x6a5, buf, 40);
                        lstrcat(g_8630, buf);
                        g_058c = 1;
                        g_05c0 = g_1e50 + 1200;
                    }
                }
                g_7090[n].f_094 = g_1e50 + 15000;
                g_8690 = g_1e50 + 7500;
                bt = -1;
                best = 20000;
                for (i = 0; i < g_9324; i++) {
                    if (i == 3 || i == 8 || i == 9) {
                        for (m = 0; m < g_9406[i]; m++) {
                            if ((i != 8 || g_3d50[m].f_1c == 2)
                                && g_1df8[i][m].f_18 == 0) {
                                d = fn_08_285a(&y, &x, g_1df8[g_9324][n].f_04,
                                               g_1df8[i][m].f_04);
                                if (d < best) {
                                    best = d;
                                    bt = i;
                                    bi = m;
                                }
                            }
                        }
                    }
                }
                if (bt != -1) {
                    g_7090[n].f_032.a = g_7090[n].f_006 = bt;
                    g_7090[n].f_032.b = g_7090[n].f_008 = bi;
                    g_7090[n].f_03c = g_7090[n].f_03a = g_7090[n].f_038
                        = g_7090[n].f_036 = 2;
                }
                return;
            }
            g_9604 = (int16_t)(g_1df8[t][k].f_1e * -90) / 210 + 100;
            if (g_9604 < 0) {
                g_9498++;
                g_9604 = 50;
            }
            g_7090[n].f_0ce += g_9604;
            g_7090[n].f_0d2++;
            if (n != main_ship && g_96d2[g_7090[n].f_04e].f_38 == g_96d2[g_7090[main_ship].f_04e].f_38) {
                fn_03_06ec(main_ship, g_9324, n, 0x6f);
                g_1e58 += 1000;
                g_5078 += 1000;
            }
            for (j = g_9602 = 0; j < g_9406[2]; j++) {
                if (g_1df8[2][j].f_18 == 0 && g_52ec[j].f_18.a == 0
                    && g_52ec[j].f_18.b == k) {
                    g_52ec[j].f_18.a = g_9324;
                    g_52ec[j].f_18.b = n;
                    g_9602++;
                }
            }
            if (g_9602) {
                fn_02_170e();
                fn_10_744c(0x69);
            }
            if ((!g_9602 && !g_1df8[t][k].f_54) || g_9320 == 6)
                fn_10_754a(0x23, t, k, 1);
            else if (g_9602 < 2)
                fn_10_754a(0x26, t, k, 1);
            else
                fn_10_754a(0x66, t, k, 1);
            fn_03_06ec(n, 7, 0, 0x55);
            if (n == main_ship) {
                g_1e58 += (g_9602 + 4) * 1000;
                g_5078 += (g_9602 + 4) * 1000;
            }
        }
    }
    if (t == 4 && !g_7090[n].f_0ea && !g_1df8[t][k].f_51) {
        g_1df8[t][k].f_18 = 1;
        g_1df8[t][k].f_48 = n;
        g_7090[n].f_01e = min(g_96d2[g_7090[n].f_04e].f_1e,
                              g_7090[n].f_01e + 250);
        fn_13_4eec(n, 0x1e);
        fn_10_754a(0x71, g_9324, n, 1);
        g_1df8[t][k].f_51 = 10;
        ship_collected_aftermath(*(OBJREF *)&r, n);
        fn_12_0e5c(k);
        g_698c = g_1e50 + 10000;
    }
    if ((t == 11 || t == 6) && !g_7090[n].f_0ea && !g_1df8[t][k].f_51
        && (t == 6 || g_8560[k].f_0a != n || g_7090[n].flag)) {
        g_1df8[t][k].f_51 = 10;
        g_1df8[t][k].f_18 = 1;
        g_1df8[t][k].f_48 = n;
        if (t == 11 && g_8560[k].f_00 == 2) {
            g_1318 = 1;
            g_1df8[14][main_ship].f_54 = 0;
            if (g_94b2)
                g_913e = 1;
            fn_03_06ec(main_ship, 7, 0, 0xb5);
        }
        if (t == 11 && g_8560[k].f_00 == 1) {
            g_9604 = g_8560[k].f_02;
            g_7090[n].f_0ce += g_9604;
            fn_03_06ec(n, 7, 0, 0x56);
            for (m = 1; m < 10; m++) {
                if (g_8560[k].f_0c[m] == -1)
                    continue;
                for (i = 1; i < g_7090[n].cnt; i++) {
                    if (g_8560[k].f_0c[m] == g_7090[n].f_0b8[i]) {
                        g_7090[n].f_0ae[i] = min(g_7090[n].f_0ae[i]
                                                 + g_8560[k].f_20[m], 100);
                        g_8560[k].f_0c[m] = -1;
                        break;
                    }
                }
                if (g_8560[k].f_0c[m] != -1) {
                    fn_12_6d64(n, g_8560[k].f_0c[m]);
                    g_7090[n].f_0ae[g_7090[n].cnt - 1] = g_8560[k].f_20[m];
                }
            }
        }
        if (t == 6 && g_2f4c[g_6670[k + 4].f_04.x].f_4a) {
            g_1df8[g_9324][n].f_26 = 1;
            g_7090[n].f_0e2 = 1;
            g_7090[n].f_084 = g_1e50 + 1200;
            g_7090[n].f_01e = min(g_96d2[g_7090[n].f_04e].f_1e,
                                  g_7090[n].f_01e + 20);
        }
        if (t == 11)
            fn_10_754a(0x26, t, k, 1);
        else if (t == 6 && g_2f4c[g_6670[k + 4].f_04.x].f_2c == 6)
            fn_10_754a(0x23, g_9324, n, 1);
        else if (t == 6)
            fn_10_754a(0x71, g_9324, n, 1);
        ship_collected_aftermath(*(OBJREF *)&r, n);
        fn_13_4eec(n, 0x32);
        fn_12_129e(t, k);
        if (g_96d2[g_7090[n].f_04e].f_38 != 7 && t == 11 && g_8560[k].f_00 == 1 && !g_92e8)
            report_crime(n, 2);
    }
    if (n == main_ship && flow_interactive && g_9134)
        g_7090[main_ship].f_052 = 7;
}
