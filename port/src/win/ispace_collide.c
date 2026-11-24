/* ISPACE.DLL ordinal 29 (2:003c): two round objects meeting [inferred:
 * the game's collision response].  Velocities, positions and the results
 * are the game's words; the DLL works in tenths and thousandths with the
 * runtime's 32-bit helpers (3:00fe multiply, 3:0130 divide), whose
 * truncation the port keeps. */
#include "ispace.h"

static int32_t lmul(int32_t a, int32_t b)
{
    return (int32_t)((uint32_t)a * (uint32_t)b);
}

static int32_t ladd(int32_t a, int32_t b)
{
    return (int32_t)((uint32_t)a + (uint32_t)b);
}

/* 3:0130; a zero divisor (a divide fault in the DLL) gives 0. */
static int32_t ldiv32(int32_t a, int32_t b)
{
    if (b == 0 || (b == -1 && a == INT32_MIN))
        return b == 0 ? 0 : a;
    return a / b;
}

static int16_t abs16(int16_t v)    /* 2:0802 */
{
    return (int16_t)(v < 0 ? -v : v);
}

static int32_t labs32(int32_t v)   /* 2:0824 */
{
    return v < 0 ? (int32_t)(0u - (uint32_t)v) : v;
}

/* 2:0850: the length of (x, y), one Newton step from |x| + |y| / 2 or
 * |y| + |x| / 2 (the larger in full); 1 for (0, 0). */
static int16_t length(int32_t x, int32_t y)
{
    int32_t ax = labs32(x), ay = labs32(y), m;

    m = ax < ay ? (ax >> 1) + ay : (ay >> 1) + ax;
    if (m == 0)
        return 1;
    return (int16_t)(ladd(ldiv32(ladd(lmul(y, y), lmul(x, x)), m), m) >> 1);
}

/* 16-bit word division (idiv); a fault in the DLL gives 0. */
static int16_t div16(int16_t a, int16_t b)
{
    return (int16_t)(b == 0 ? 0 : (int32_t)a / b);
}

/* Moving apart: each velocity word grows by a step that shrinks with it. */
static void speed_up(int16_t *v)
{
    int16_t m = abs16(*v);

    if (m < 3)
        *v = (int16_t)(*v << 1);
    else if (m < 7)
        *v = div16((int16_t)(*v << 2), 3);
    else if (m < 11)
        *v = div16((int16_t)(*v * 7), 6);
    else
        *v = div16((int16_t)(*v * 11), 10);
}

/* The time (thousandths) until the gap along one axis closes. */
static int32_t time_to(int16_t d, int16_t reach, int16_t dv, int32_t u)
{
    int32_t t = labs32(u) >= 1 ? labs32(u) : 1;

    return ldiv32((int32_t)(int16_t)(dv > 0 ? d + reach : reach - d) * 1000, t);
}

/* Object 1 at (*x1, *y1), size s1, mass m1, moving (*vx1, *vy1); object 2
 * likewise.  Returns 0 when they are moving apart (both sped up), else 1:
 * object 1 is moved back out of object 2, the velocities along the line
 * between them are exchanged as an elastic collision of the masses, and
 * *hit1, *hit2 are half of each one's change of speed. */
int16_t ispace_collide(int16_t *vx1, int16_t *vy1, int16_t *vx2, int16_t *vy2, int16_t *x1,
                       int16_t *y1, int16_t *x2, int16_t *y2, int16_t s1, int16_t s2, int16_t m1,
                       int16_t m2, int16_t *hit1, int16_t *hit2)
{
    int16_t off = (int16_t)(s1 / 2 - s2 / 2);
    int16_t dx = (int16_t)((off - *x2 + *x1) * 10), dy = (int16_t)((off - *y2 + *y1) * 10);
    int16_t reach = (int16_t)((s1 + s2) * 5 + 0x12);
    int16_t dvx = (int16_t)((*vx1 - *vx2) * 10), dvy = (int16_t)((*vy1 - *vy2) * 10);
    int16_t dist = length(dx, dy), speed, p1, p2, q1, q2;
    int32_t ux, uy, ty, tx, t, nx, ny;

    if (abs16(dvx) <= 40 && abs16(dvy) <= 40) {
        *vx1 = (int16_t)(*vx2 - div16((int16_t)(dx * 5), dist));
        *vy1 = (int16_t)(*vy2 - div16((int16_t)(dy * 5), dist));
        dvx = (int16_t)((*vx1 - *vx2) * 10);
        dvy = (int16_t)((*vy1 - *vy2) * 10);
    }
    speed = length(dvx, dvy);
    if ((int16_t)ldiv32(lmul(ladd(lmul(dx, dvx), lmul(dy, dvy)), 100), (int32_t)speed * dist) > 0) {
        speed_up(vx1);
        speed_up(vy1);
        speed_up(vx2);
        speed_up(vy2);
        return 0;
    }

    ux = ldiv32((int32_t)dvx * 1000, speed);
    uy = ldiv32((int32_t)dvy * 1000, speed);
    ty = time_to(dy, reach, dvy, uy);
    tx = time_to(dx, reach, dvx, ux);
    t = labs32(ty) > labs32(tx) ? tx : ty;
    *x1 = (int16_t)(*x1 + ldiv32(lmul(ux, t), -10000));
    *y1 = (int16_t)(*y1 + ldiv32(lmul(uy, t), -10000));

    dx = (int16_t)((off - *x2 + *x1) * 10);
    dy = (int16_t)((off - *y2 + *y1) * 10);
    dist = length(dx, dy);
    nx = ldiv32((int32_t)(int16_t)-dx * 1000, dist);
    ny = ldiv32((int32_t)(int16_t)-dy * 1000, dist);
    p1 = (int16_t)((int16_t)ldiv32(lmul(nx, *vx1), 1000) + (int16_t)ldiv32(lmul(ny, *vy1), 1000));
    p2 = (int16_t)((int16_t)ldiv32(lmul(nx, *vx2), 1000) + (int16_t)ldiv32(lmul(ny, *vy2), 1000));
    *vx1 = (int16_t)(*vx1 + ldiv32(lmul(p1, nx), -1000));
    *vy1 = (int16_t)(*vy1 + ldiv32(lmul(p1, ny), -1000));
    *vx2 = (int16_t)(*vx2 + ldiv32(lmul(p2, nx), -1000));
    *vy2 = (int16_t)(*vy2 + ldiv32(lmul(p2, ny), -1000));

    q2 = (int16_t)ldiv32(ladd(lmul((int32_t)m2 - m1, p2), lmul(lmul(p1, m1), 2)), (int32_t)m1 + m2);
    q1 = (int16_t)(q2 - p1 + p2);
    *vx1 = (int16_t)(*vx1 + ldiv32(lmul(q1, nx), 1000));
    *vy1 = (int16_t)(*vy1 + ldiv32(lmul(q1, ny), 1000));
    *vx2 = (int16_t)(*vx2 + ldiv32(lmul(q2, nx), 1000));
    *vy2 = (int16_t)(*vy2 + ldiv32(lmul(q2, ny), 1000));
    *hit1 = (int16_t)(abs16((int16_t)(q1 - p1)) / 2);
    *hit2 = (int16_t)(abs16((int16_t)(q2 - p2)) / 2);
    return 1;
}
