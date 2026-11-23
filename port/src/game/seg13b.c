/* INSPACE.EXE segment 13 (selector 1060), second source file (13:6900-end).
 * Calls into the first file (seg13.c: 2688, 2714, 4eec) are far. */
#include "game.h"

                                                                      

/* 13:910a */
int16_t fn_13_910a(int16_t n)
{
    int16_t i;

    for (i = 0; i <= g_9316; i++) {
        if (i == n)
            continue;
        if (g_1df8[14][i].f_18 == 0 && g_7090[i].flag != 0)
            return 0;
    }
    return 1;
}

/* Object n asks the others for help against its target (f_03c, f_03e):
 * picks the first object that agrees, else reports the best refusal
 * message [inferred]. Returns 1 if someone agreed, 0 if not, -1 when n
 * asked too recently. */
/* 13:8570 */
int16_t fn_13_8570(int16_t n)
{
    int16_t j, u1, s, k, pw, rel, u2, msg, best, bestj, rel2;

    u1 = u2 = 0;
    if ((n != g_9646 || g_9134 != 0) && g_7090[n].f_09c > g_1e50)
        return -1;
    g_7090[n].f_09c = g_1e50 + 10000;
    if (g_934e < 5 && (n != g_9646 || !flow_interactive))
        return 0;
    s = LO16(g_7090[n].f_03e);
    k = HI16(g_7090[n].f_03e);
    if ((n != g_9646 || !flow_interactive)
        && g_7090[g_9646].f_032.a == s
        && (s == 0x16 || g_7090[g_9646].f_032.b == k))
        return 0;
    if (n != g_9646 && s == 9) {
        if (g_8710 && g_8710 + 1500 > g_1e68)
            return 0;
        if (g_8714 && g_8714 + 600 > g_1e68)
            return 0;
        for (j = 0; j < g_9316; j++) {
            if (j == g_9646)
                continue;
            if (g_7090[j].flag && g_7090[j].f_032.a == 14
                && g_7090[j].f_032.b == g_9646 && g_7090[j].f_038 == 1)
                return 0;
        }
        if (g_7090[g_9646].f_026[0] < 40)
            return 0;
    }
    fn_13_4eec(n, 4);
    best = 1000;
    for (j = 0; j <= g_9316; j++) {
        msg = 1000;
        pw = fn_04_5d9c(j, k) + 20;
        rel = fn_13_2688(j, n);
        if (s == 14)
            rel2 = fn_13_2688(j, k);
        else
            rel2 = -400;
        if (j == n || g_1df8[14][j].f_18)
            msg = 0xa3;
        else if (s == 14 && k == j)
            msg = 0x9e;
        else if (g_96d2[g_7090[j].f_04e].f_38 == 2 && s == 14)
            msg = 0x93;
        else if (g_96d2[g_7090[j].f_04e].f_38 == 7)
            msg = 0x96;
        else if (g_96d2[g_7090[j].f_04e].f_38 == 6)
            msg = 0x95;
        else if (g_96d2[g_7090[j].f_04e].f_38 == 4 && g_96d2[g_7090[n].f_04e].f_38 != 4 && s == 14)
            msg = 0x94;
        else if (rel < -100 && g_96d2[g_7090[j].f_04e].f_38 != g_96d2[g_7090[n].f_04e].f_38) {
            if (s == 14)
                msg = 0x9d;
            else
                msg = 0xa2;
        } else if (rel2 + 70 > rel || rel2 > 150)
            msg = 0x91;
        else if (g_96d2[g_7090[k].f_04e].f_38 != g_96d2[g_7090[j].f_04e].f_38
                 && (g_7090[j].f_05d >= 3
                     || (rel < 100 && g_7090[j].f_05e >= 3)))
            msg = 0x9a;
        else if (k == 14 && g_96d2[g_7090[k].f_04e].f_38 == g_96d2[g_7090[j].f_04e].f_38)
            msg = 0x98;
        else if (k == 14 && g_96d2[g_7090[k].f_04e].f_38 == g_96d2[g_7090[n].f_04e].f_38
                 && !(g_7090[k].f_038 == 1 && g_7090[k].f_032.a == 14
                      && g_7090[k].f_032.b == n)
                 && g_96d2[g_7090[j].f_04e].f_38 != 3) {
            if (g_96d2[g_7090[j].f_04e].f_38 == g_96d2[g_7090[n].f_04e].f_38)
                msg = 0x9b;
            else
                msg = 0x92;
        } else if (s == 0 && g_1df8[0][k].f_53 == 1
                   && g_1df8[0][k].f_1e == 0 && g_96d2[g_7090[j].f_04e].f_38 != 3)
            msg = 0x97;
        else if (g_7090[j].f_0ee[k] == 8)
            msg = 0x99;
        else if (k == 14 && g_7090[j].f_0b8[k + 10] == -1)
            msg = 0x90;
        else if (g_7090[j].f_05d * 62 - rel * 3 / 4 + 60 > pw)
            msg = 0x8f;
        else if (g_96d2[g_7090[j].f_04e].f_1e / 10 > g_7090[j].f_01e)
            msg = 0x8b;
        else if (g_7090[j].f_0ce + g_7090[j].f_0dc
                     < (g_7090[j].f_05e - 2) * 50
                 && rel < 200 && g_7090[j].f_026[0] < 50 && pw < 80)
            msg = 0x9c;
        else if (g_7090[j].f_038 == 1 && g_7090[j].f_032.a == 14
                 && g_7090[j].f_0f6[8][g_7090[j].f_032.b] > 0
                 && (g_7090[j].f_032.a != n || g_7090[j].f_052 < 2
                     || g_7090[j].f_052 > 4)
                 && (s != 14 || g_7090[j].f_032.b != k))
            msg = 0x8e;
        else if (g_7090[j].f_052 != 0 && g_7090[j].f_052 != 7
                 && g_7090[j].f_052 != 13 && g_7090[j].f_098 > g_1e50
                 && g_7090[j].f_058 != n) {
            if (g_7090[j].f_054 != 14 || g_7090[j].f_056 != n)
                msg = 0x8d;
            else if (g_7090[j].f_052 == 1 || g_7090[j].f_052 == 5)
                msg = 0x9f;
            else if (g_7090[j].f_052 >= 2 || g_7090[j].f_052 <= 4) {
                if (g_7090[j].f_058 == j)
                    msg = 0xa1;
                else
                    msg = 0xa0;
            }
        } else if (msg != 1000 && s == 14 && g_7090[k].f_0e8)
            msg = 0x8c;
        if (msg < best || (best > 0x90 && msg < 0x9e && (rand() & 1))) {
            best = msg;
            bestj = j;
            continue;
        }
        if (msg != 1000)
            continue;
        fn_13_4eec(j, 15);
        if (n == g_9646)
            fn_13_4eec(j, 25);
        fn_13_4eec(n, 20);
        if (s == 9) {
            fn_13_4eec(j, -10);
            fn_13_4eec(n, -13);
            if (n != g_9646)
                g_8710 = g_1e68;
        }
        if (j == g_9646 && g_9134 && flow_interactive) {
            if (g_1e50 - 15000 > g_8858) {
                g_964e = 4;
                g_9650 = s;
                g_9652 = k;
                g_8858 = g_1e50;
                g_9654 = n;
                fn_03_06ec(g_9646, 14, n, 0x34);
            }
            continue;
        }
        if (g_7090[j].f_052)
            fn_03_06ec(g_7090[j].f_058, 14, n, 0x13);
        if (n == g_9646) {
            if (s == 14)
                g_9432 += 120;
            else
                g_9432 += 30;
        }
        if (g_7090[j].f_05d >= 2)
            g_7090[j].f_052 = 2;
        else if (g_7090[j].f_05d <= 1)
            g_7090[j].f_052 = 3;
        else if (g_7090[j].f_05d == 0)
            g_7090[j].f_052 = 4;
        fn_04_8346(j, s, k, 9);
        if (j == g_9646)
            g_7090[j].f_052 = 2;
        if (n == g_9646 && g_9134 == 1)
            fn_03_33b4(2);
        g_7090[j].f_094 = g_1e50 + 400;
        g_7090[j].f_054 = s;
        g_7090[j].f_056 = k;
        g_7090[j].f_058 = n;
        g_7090[j].f_098 = g_1e50 + 10000;
        g_7090[n].f_09c = g_1e50 + 15000;
        g_7090[j].f_0ed = 1;
        g_7090[j].f_0a4 = g_1e50 - g_7090[j].f_05e * 2000 + 8000;
        fn_03_06ec(j, 14, n, 2);
        if (j != g_9646)
            fn_03_00f4(j, g_7090[j].f_054, g_7090[j].f_056);
        if (s == 14)
            fn_13_2714(HI16(g_7090[n].f_03e), n, -(g_7090[j].f_052 * 10),
                       g_7090[j].f_052 * -40, 0, 5);
        return 1;
    }
    if (n != g_9646
        && (g_7090[g_9646].f_052 == 0 || g_7090[g_9646].f_052 == 7)
        && !g_9134 && !(s == 14 && k == g_9646) && n != g_9646
        && fn_13_2688(n, g_9646) > -100
        && !(g_7090[g_9646].f_032.a == 14 && g_7090[g_9646].f_032.b == n)) {
        g_7090[g_9646].f_052 = 2;
        g_7090[g_9646].f_058 = n;
        g_7090[n].f_09c = g_7090[g_9646].f_098 = g_1e50 + 15000;
        g_7090[g_9646].f_054 = s;
        g_7090[g_9646].f_056 = k;
        fn_04_8346(g_9646, s, k, 9);
        fn_03_06ec(g_9646, 14, n, 2);
        if (s == 9)
            g_8710 = g_1e68;
        return 1;
    }
    if (best == 0xa3)
        fn_03_06ec(n, 7, 0, best);
    else
        fn_03_06ec(n, 14, bestj, best);
    return 0;
}

/* 13:9970 */
int16_t fn_13_9970(int16_t i)
{
    int16_t j;

    if (g_7090[i].f_09c > g_1e50)
        return -1;
    for (j = 0; j <= g_9316; j++) {
        if (g_1df8[14][j].f_18 == 0 && g_7090[j].flag && g_7090[j].f_052 >= 2
            && g_7090[j].f_052 <= 4 && g_7090[j].f_058 == i
            && j != g_9646 && j != i) {
            g_7090[i].f_09c = g_1e50 + 5000;
            return 0;
        }
    }
    return fn_13_8570(i);
}

/* 13:a5c2 */
void fn_13_a5c2(void)
{
    if (g_7090[g_9646].f_052 == g_964e && g_7090[g_9646].f_054 == g_9650
        && g_8858 + 20000 > g_1e50) {
        if (g_7090[g_9646].f_056 == g_9652 || g_9650 == 9)
            goto hit;
    } else if (g_7090[g_9646].f_052 == 4 && g_964e == 11
               && g_8858 + 20000 > g_1e50
               && g_7090[g_9646].f_054 == g_9650
               && g_7090[g_9646].f_056 == g_9652) {
hit:
        g_885c = g_1e50 + 700;
        g_8858 = g_1e50;
    }
}

/* 13:a186 */
void fn_13_a186(void)
{
    if (g_9134) {
        g_7090[g_9646].f_052 = 4;
        g_7090[g_9646].f_054 = g_6e38[0].f_1a.b;
        g_7090[g_9646].f_056 = g_6e38[0].f_1a.a;
        if (g_7090[g_9646].f_054 == 12)
            g_7090[g_9646].f_054 = 8;
        g_7090[g_9646].f_098 = g_1e50 + 30000;
        g_7090[g_9646].f_094 = g_1e50 + 200;
        g_7090[g_9646].f_0ed = 1;
        g_7090[g_9646].f_058 = g_9646;
        fn_04_8346(g_9646, g_6e38[0].f_1a.b, g_6e38[0].f_1a.a, 12);
        if (g_6e38[0].f_1a.b == 14)
            fn_13_2714(g_6e38[0].f_1a.a, g_9646, -15, -60, 1, 1);
        fn_13_a5c2();
    }
}

/* 13:a3c8 */
void fn_13_a3c8(void)
{
    int16_t i, y, x, d, best;

    if (g_9134) {
        best = 20000;
        for (i = 0; i < g_9318 * 2; i += 2) {
            d = fn_08_285a(&y, &x, g_1df8[14][g_9646].f_04, g_1df8[12][i].f_04);
            if (d < best) {
                best = d;
                g_7090[g_9646].f_052 = 10;
                g_7090[g_9646].f_054 = 12;
                g_7090[g_9646].f_056 = i;
                g_7090[g_9646].f_098 = g_1e50 + 30000;
                g_7090[g_9646].f_094 = g_1e50 + 200;
                g_7090[g_9646].f_0ed = 1;
                g_7090[g_9646].f_058 = g_9646;
            }
        }
        fn_13_a5c2();
    }
}

/* 13:a47c */
void fn_13_a47c(void)
{
    if (g_9134) {
        if (g_9406[4] < 1) {
            fn_03_06ec(g_9646, 7, 0, 0x38);
        } else {
            g_7090[g_9646].f_052 = 12;
            g_7090[g_9646].f_054 = 14;
            g_7090[g_9646].f_056 = g_9646;
            g_7090[g_9646].f_098 = g_1e50 + 30000;
            g_7090[g_9646].f_094 = g_1e50 + 200;
            g_7090[g_9646].f_0ed = 1;
            g_7090[g_9646].f_058 = g_9646;
            fn_13_a5c2();
        }
    }
}

/* 13:a4f4 */
void fn_13_a4f4(void)
{
    PAIR p;

    if (g_9134) {
        p.a = g_6e38[0].f_1a.a;
        p.b = g_6e38[0].f_1a.b;
        if (p.b != 14)
            return;
            g_7090[g_9646].f_052 = 1;
            g_7090[g_9646].f_054 = p.b;
            g_7090[g_9646].f_056 = p.a;
            g_7090[g_9646].f_098 = g_1e50 + 30000;
            g_7090[g_9646].f_094 = g_1e50 + 200;
            g_7090[g_9646].f_0ed = 1;
            g_7090[g_9646].f_058 = g_9646;
            fn_13_a5c2();
    }
}

/* 13:a568 */
void fn_13_a568(void)
{
    if (g_9134) {
        g_7090[g_9646].f_052 = 13;
        g_7090[g_9646].f_054 = 14;
        g_7090[g_9646].f_056 = g_9646;
        g_7090[g_9646].f_098 = g_1e50 + 30000;
        g_7090[g_9646].f_094 = g_1e50 + 200;
        g_7090[g_9646].f_0ed = 1;
        g_7090[g_9646].f_058 = g_9646;
    }
}

/* 13:7b40 */
void fn_13_7b40(int16_t a)
{
    fn_03_06ec(g_9646, 14, a, 3);
    if (!g_9134)
        g_7090[g_9646].f_052 = 0;
    if (g_7090[g_9646].f_054 == 9)
        fn_13_2714(a, g_9646, 10, 0x16, 0, 6);
    else
        fn_13_2714(a, g_9646, 15, 0x41, 1, 8);
}

/* 13:a65a */
void fn_13_a65a(void)
{
    if (g_885c != 0 && g_885c < g_1e50) {
        if (g_8858 != 11)
            fn_13_7b40(g_9654);
        else
            fn_03_06ec(g_9646, g_9650, g_9652, 0x1f);
        g_964e = 0;
        g_9650 = 0;
        g_9652 = 0;
        g_9654 = 0;
        g_885c = 0;
        g_8858 = 0;
    }
}

/* Summon with music [inferred, HANDOFF: report_crime, the enforcer order
 * and escalation call this rather than ae68]. */
/* Falls off the end without a return value after the music part (the
 * game's callers test the result anyway: fn_13_b93a). */
/* 13:adbe */
int16_t fn_13_adbe(int16_t a, int16_t b, int16_t c)
{
    int16_t u, r;

    if (!fn_13_ae68(a, b, c))
        return 0;
    r = 2;
    switch (b) {
    case 3:
        r = 7;
        break;
    case 4:
        if (a == g_9646)
            r = 8;
        else if (g_7090[g_9646].f_032.a == 14 && g_7090[g_9646].f_032.b == a
                 && g_7090[g_9646].f_038 == 1)
            r = 7;
        else
            r = -1;
        break;
    case 0x13:
        r = 7;
        break;
    case 0x14:
        r = 7;
        break;
    case 0x15:
        r = 2;
        break;
    case 0x16:
        r = 2;
        break;
    }
    if (r != -1) {
        fn_10_7480(r, 0);
        g_2384 = g_1e50 + 12000;
    }
}

/* 13:b93a */
void fn_13_b93a(void)
{
    int16_t i, k, s1, s2;

    for (i = 0; i <= g_9316; i++) {
        if (g_7090[i].flag && g_1df8[14][i].f_18 == 0
            && g_96d2[g_7090[i].f_04e].f_38 == 7 && g_7090[i].f_05e > 1
            && g_1df8[14][i].f_1a != 0) {
            s1 = 0;
            s2 = 0;
            for (k = 0; k < 10; k++) {
                if (k != 9) {
                    s1 += g_a14d[k];
                    s2 += g_a157[k];
                }
            }
            if (s2 < s1) {
                if (fn_13_adbe(g_9646, 0x15, -1)) {
                    fn_03_06ec(g_9646, 14, i, 0xae);
                    g_a163 = g_a161;
                }
                return;
            }
        }
    }
}

/* 13:9a18 */
void fn_13_9a18(int16_t a, int16_t s, int16_t k)
{
    int16_t i, u, best;

    if (k < 0 || k >= g_9406[s] || g_1df8[s][k].f_18 != 0)
        return;
    best = -1;
    for (i = 0; i < g_9406[2]; i++) {
        if (g_52ec[i].f_18.a == 14 && g_52ec[i].f_18.b == a
            && (g_52ec[i].f_1c.a != s || g_52ec[i].f_1c.b != k
                || g_52ec[i].f_12 != 15)
            && g_1df8[2][i].f_18 == 0) {
            g_52ec[i].f_12 = 15;
            g_52ec[i].f_1c.a = s;
            g_52ec[i].f_1c.b = k;
            g_52ec[i].f_0a = 0;
            best = i;
        }
    }
    if (best >= 0)
        fn_10_754a(0x15, 2, best, 1);
}

/* 13:9ae8 */
void fn_13_9ae8(int16_t a)
{
    int16_t i, best;

    best = -1;
    for (i = 0; i < g_9406[2]; i++) {
        if (g_52ec[i].f_18.a == 14 && g_52ec[i].f_18.b == a
            && g_52ec[i].f_12 == 15) {
            g_52ec[i].f_12 = 0;
            LO16(g_52ec[i].f_00.l) = g_1df8[2][i].f_04.x
                - g_1df8[g_52ec[i].f_18.a][g_52ec[i].f_18.b].f_04.x;
            HI16(g_52ec[i].f_00.l) = g_1df8[2][i].f_04.y
                - g_1df8[g_52ec[i].f_18.a][g_52ec[i].f_18.b].f_04.y;
            g_1df8[2][i].f_1e = 0;
            best = i;
        }
    }
    if (best >= 0)
        fn_10_754a(0x15, 2, best, 1);
}

/* 13:9f3e */
void fn_13_9f3e(int16_t i)
{
    int16_t u1, u2, u3, t, cls, m, z;

    cls = g_96d2[g_7090[i].f_04e].f_38;
    m = LO16(g_7090[i].f_03e);
    t = HI16(g_7090[i].f_03e);
    u1 = z = 0;
    if (m != 14 || g_96d2[g_7090[t].f_04e].f_38 != cls) {
        t = -1;
        fn_03_06ec(i, 7, 0, 0x32);
    } else if (g_7090[t].f_052 != 0 && g_7090[t].f_052 != 7
               && g_7090[t].f_098 > g_1e50 && g_7090[t].f_05d > 1) {
        fn_03_06ec(i, 14, t, 0x31);
    } else if (g_96d2[g_7090[t].f_04e].f_38 == 7) {
        fn_03_06ec(i, 14, t, 0x40);
    } else {
        if (g_7090[t].f_052 != 0)
            fn_03_06ec(g_7090[t].f_058, m, t, 0x13);
        g_7090[t].f_052 = 10;
        g_7090[t].f_094 = g_1e50;
        fn_03_06ec(t, 14, i, 2);
    }
}

/* 13:9bb8 */
int16_t fn_13_9bb8(int16_t i, int16_t b)
{
    int16_t u1, u2, s;

    if (g_1df8[7]->f_18 == 0)
        return 0;
    s = g_7090[i].f_0ce;
    s += g_7090[i].f_0dc;
    if (s < 250 && i != g_9646)
        return 0;
    if ((g_7090[g_9646].f_032.a == 14 && g_7090[g_9646].f_032.b == i)
        || (g_7090[i].f_032.a == 14 && g_7090[i].f_032.b == g_9646)) {
        if (g_7090[i].f_082 < 1700)
            return 0;
        if (g_7090[i].f_026[0] > 1)
            return 0;
    }
    if (g_1c8e[i] == g_91f8)
        return 0;
    if (g_7090[i].f_026[1] <= 0 || g_7090[i].f_026[2] <= 0) {
        g_1c8e[i] = g_91f8;
        return 1;
    }
    if (g_7090[i].f_026[0] + g_7090[i].f_026[1] + g_7090[i].f_026[2]
        < max(min((b + 2) * 20 + s / 10, 180), 70)
        || (g_7090[i].f_0ce > 200 && (g_9334 + 20) * 35 < s)) {
        g_1c8e[i] = g_91f8;
        return 1;
    }
    if (g_7090[i].f_0ac && g_7090[i].f_0ad)
        return 0;
    if (s > 500) {
        g_1c8e[i] = g_91f8;
        return 1;
    }
    return 0;
}

/* Object i asks its target t to escort it [inferred]. */
/* 13:a01c */
void fn_13_a01c(int16_t i)
{
    int16_t u1, u2, u3, t, cls, m, z;

    cls = g_96d2[g_7090[i].f_04e].f_38;
    m = LO16(g_7090[i].f_03e);
    t = HI16(g_7090[i].f_03e);
    u1 = z = 0;
    if (m == 14 && g_96d2[g_7090[t].f_04e].f_38 == 7) {
        fn_03_06ec(i, m, t, 0x40);
    } else if (m != 14 || g_96d2[g_7090[i].f_04e].f_38
                          != g_96d2[g_7090[t].f_04e].f_38) {
        fn_03_06ec(i, 7, 0, 0x36);
    } else if (g_7090[t].f_052 != 0 && g_7090[t].f_052 != 7
               && g_7090[t].f_09c > g_1e50 && g_7090[t].f_05d > 0) {
        fn_03_06ec(i, 14, t, 0x35);
        return;
    } else {
        if (g_7090[t].f_052 != 0)
            fn_03_06ec(g_7090[t].f_058, 14, t, 0x13);
        g_7090[t].f_052 = 12;
        g_7090[t].f_032.a = 14;
        g_7090[t].f_032.b = i;
        g_7090[t].f_03c = g_7090[t].f_038 = 2;
        g_7090[t].f_054 = 14;
        g_7090[t].f_056 = i;
        g_7090[t].f_058 = i;
        g_7090[t].f_098 = g_1e50 + 25000;
        g_7090[t].f_094 = g_1e50 + 500;
        g_7090[i].f_09c = g_1e50 + 15000;
        g_7090[t].f_0ed = 1;
        g_7090[t].f_0a4 = g_1e50 - g_7090[t].f_05e * 2000 + 8000;
        fn_03_06ec(t, 14, i, 2);
    }
}

/* 13:9810 */
void fn_13_9810(int16_t i)
{
    int16_t u1, u2, m, t, done;

    u1 = done = 0;
    if (i != g_9646 && g_7090[i].f_09c > g_1e50)
        return;
    m = LO16(g_7090[i].f_03e);
    t = HI16(g_7090[i].f_03e);
    if (fn_13_910a(i)) {
        fn_03_06ec(i, 7, 0, 100);
        return;
    }
    if (m != 14)
        return;
    if (g_96d2[g_7090[t].f_04e].f_38 == 7) {
        fn_03_06ec(i, 14, t, 0x40);
        return;
    }
    if (g_1df8[14][t].f_18 == 0 && g_7090[t].flag
        && (g_7090[t].f_052 == 0 || g_7090[t].f_052 == 7
            || g_7090[t].f_098 < g_1e50)
        && t != i && fn_13_2688(t, i) > 0) {
        if (g_7090[t].f_052 != 0)
            fn_03_06ec(g_7090[t].f_058, 14, t, 0x13);
        g_7090[t].f_052 = 13;
        g_7090[t].f_094 = g_1e50 + 200;
        g_7090[t].f_058 = i;
        g_7090[t].f_098 = g_1e50 + 15000;
        g_7090[t].f_0ed = 0;
        fn_03_06ec(t, 14, i, 2);
        done = 1;
    } else if (!done)
        fn_03_06ec(i, 14, t, 0x5a);
}

/* Send the player to the selected object, or to the nearest free one of
 * kinds 0 and 11 [inferred]. */
/* 13:a234 */
void fn_13_a234(void)
{
    int16_t i;
    PAIR p;
    int16_t d, best, bs, bk, y, x;

    if (g_9134) {
        p.a = g_6e38[0].f_1a.a;
        p.b = g_6e38[0].f_1a.b;
        if ((p.b == 0 || p.b == 11) && g_1df8[p.b][p.a].f_18 == 0)
            goto set;
        best = 20000;
        bs = -1;
        for (i = 0; i < g_91fa; i++) {
            if (g_1df8[0][i].f_18 == 0) {
                d = fn_08_285a(&y, &x, g_1df8[14][g_9646].f_04,
                               g_1df8[0][i].f_04);
                if (d < best) {
                    best = d;
                    bs = 0;
                    bk = i;
                }
            }
        }
        for (i = 0; i < g_9406[11]; i++) {
            if (g_1df8[11][i].f_18 == 0) {
                d = fn_08_285a(&y, &x, g_1df8[14][g_9646].f_04,
                               g_1df8[11][i].f_04);
                if (d < best) {
                    best = d;
                    bs = 11;
                    bk = i;
                }
            }
        }
        if (bs != -1) {
            fn_03_00f4(g_9646, bs, bk);
            p.b = bs;
            p.a = bk;
        } else {
            fn_03_06ec(g_9646, 7, 0, 0x25);
            return;
        }
set:
        g_7090[g_9646].f_052 = 9;
        g_7090[g_9646].f_094 = g_1e50 + 200;
        g_7090[g_9646].f_054 = p.b;
        g_7090[g_9646].f_056 = p.a;
        g_7090[g_9646].f_058 = g_9646;
        g_7090[g_9646].f_098 = g_1e50 + 25000;
        g_7090[g_9646].f_0ed = 1;
        fn_13_a5c2();
    }
}

/* Pick the music section for the danger level [inferred]. */
/* 13:ba04 */
void fn_13_ba04(void)
{
    int16_t i, m;
    int32_t t;
    int16_t found;

    m = 1;
    t = 5000;
    if (g_9220 == 9 || g_9220 == 10)
        return;
    for (i = 0; i <= g_9316; i++) {
        found = 0;
        t = 3000;
        if (g_7090[i].flag && g_1df8[14][i].f_18 == 0) {
            if (g_7090[i].f_038 == 1 && g_7090[i].f_032.a == 14
                && g_7090[i].f_032.b == g_9646)
                found = 1;
            if ((g_7090[i].f_052 == 0x16 || g_7090[i].f_052 == 0x17)
                && g_7090[i].f_054 == 14 && g_7090[i].f_056 == g_9646)
                found = 1;
        }
        if (found) {
            m = 2;
            t = 6000;
            break;
        }
    }
    if (g_7090[g_9646].f_038 == 1 && g_9220 == 2
        && g_7090[g_9646].f_032.a == 14) {
        t = 6000;
        m = 2;
    } else if (g_9220 == 2) {
        for (i = 0; i <= g_9316; i++) {
            if (i != g_9646 && g_1e68 / 10 - g_7090[i].f_044[0] < 20
                && g_7090[i].f_044[0] != 0 && g_1df8[14][i].f_18 == 0) {
                m = 2;
                t = 6000;
            }
        }
    }
    if (m != g_9220) {
        fn_10_7480(m, 0);
    } else {
        if (g_9220 == 2)
            t = 6000;
        else
            t = 3000;
    }
    g_2384 = g_1e50 + t;
}

/* Report a crime of kind t by object a to a nearby police ship
 * [inferred: HANDOFF report_crime; calls adbe]. flag is never read. */
/* 13:b6f2 */
void fn_13_b6f2(int16_t a, int16_t t)
{
    int16_t i, y, x, d, msg, flag;

    flag = 1;
    if (g_9320 == 7)
        return;
    switch (t) {
    case 1:
        msg = 0x45;
        break;
    case 2:
        msg = 0x46;
        break;
    case 3:
        msg = 0x5d;
        break;
    case 4:
        msg = 0x65;
        break;
    case 5:
        if (g_a163 == 5)
            return;
        msg = 0x72;
        break;
    case 6:
        msg = 0x86;
        break;
    case 8:
        msg = 0xb9;
        break;
    case 9:
        msg = 0xc0;
        break;
    }
    if (a == g_9646 && t != 9) {
        g_964a++;
        g_9648++;
    }
    if (t != 6) {
        g_964a += 3;
        g_9648 += 3;
    } else {
        g_964a++;
        g_9648++;
    }
    if (t == 2) {
        g_964a += 4;
        g_9648 += 4;
    }
    if (t == 8 || g_104a) {
        g_964a += 2;
        g_9648 += 2;
        g_a163 = (char)t;
        fn_13_adbe(a, 0x15, -1);
        fn_03_06ec(a, 14, g_9316, msg);
        if (a == g_9646)
            g_a14d[t]++;
        g_104a = 0;
        return;
    }
    for (i = 0; i <= g_9316; i++) {
        if (g_96d2[g_7090[i].f_04e].f_38 == 7 && g_1df8[14][i].f_18 == 0
            && g_7090[i].f_052 != 0x16 && g_7090[i].f_052 != 0x17
            && (d = fn_08_285a(&y, &x, g_1df8[14][i].f_04, g_1df8[14][a].f_04))
               < 2400
            && (t != 6 || g_a157[t] >= g_a14d[t])) {
            if (fn_13_adbe(a, 0x15, -1)) {
                fn_03_06ec(a, 14, i, msg);
                g_a163 = (char)t;
                if (a == g_9646)
                    g_a14d[t]++;
                return;
            } else {
                fn_03_06ec(a, 14, i, 0x44);
                return;
            }
        } else if (g_96d2[g_7090[i].f_04e].f_38 == 7
                   && g_1df8[14][i].f_18 == 0)
            flag = 0;
    }
    if (g_9648 > 4 && g_9648 < 1000) {
        fn_03_06ec(g_9646, 7, 0, 0x6e);
        g_9648 = 1001;
    }
}

/* 13:9ce0 */
int16_t fn_13_9ce0(int16_t a)
{
    int16_t i, u, s, k, done;

    u = done = 0;
    if ((a != g_9646 || g_9134 != 0) && g_7090[a].f_09c > g_1e50)
        return 0;
    s = LO16(g_7090[a].f_03e);
    k = HI16(g_7090[a].f_03e);
    if (!g_1df8[s][k].f_53) {
        for (i = 0; i <= g_9316; i++)
            if (g_96d2[g_7090[i].f_04e].f_38
                    == g_96d2[g_7090[a].f_04e].f_38 && i != a)
                break;
        if (i <= g_9316) {
            if (s == 14)
                fn_03_06ec(a, 14, i, 0x23);
            else
                fn_03_06ec(a, 14, i, 0x24);
        } else
            fn_03_06ec(a, 7, 0, 0x25);
        return 0;
    }
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f_18 == 0 && g_7090[i].flag
            && (g_7090[i].f_052 == 0 || g_7090[i].f_052 == 7
                || g_7090[i].f_098 < g_1e50)
            && i != a
            && g_96d2[g_7090[i].f_04e].f_38
               == g_96d2[g_7090[a].f_04e].f_38) {
            if (g_7090[i].f_052 != 0)
                fn_03_06ec(g_7090[i].f_058, 14, i, 0x13);
            g_7090[i].f_052 = 9;
            g_7090[i].f_094 = g_1e50 + 200;
            g_7090[i].f_054 = s;
            g_7090[i].f_056 = k;
            g_7090[i].f_058 = a;
            g_7090[i].f_098 = g_1e50 + 25000;
            g_7090[a].f_09c = g_1e50 + 15000;
            g_7090[i].f_0ed = 1;
            fn_03_06ec(i, 14, a, 2);
            if (a == g_9646 && g_9134 == 1)
                fn_03_33b4(9);
            done = 1;
            if (i != g_9646)
                fn_03_00f4(i, g_7090[i].f_054, g_7090[i].f_056);
            return 1;
        }
    }
    if (done)
        return 0;
    for (i = 0; i <= g_9316; i++)
        if (g_96d2[g_7090[i].f_04e].f_38 == g_96d2[g_7090[a].f_04e].f_38
            && i != a)
            break;
    if (i <= g_9316)
        fn_03_06ec(a, 14, i, 0x26);
    else
        fn_03_06ec(a, 7, 0, 0x27);
    return 0;
}

/* Object a asks the others to join its attack on k [inferred]. The bare
 * label l1 (no goto) is needed to match: it resets CL's register
 * tracking after the first call. */
/* 13:8e98 */
void fn_13_8e98(int16_t a)
{
    int16_t i, u, s, k, done;

    u = done = 0;
    s = LO16(g_7090[a].f_03e);
    k = HI16(g_7090[a].f_03e);
    if (s != 14)
        return;
    if ((a != g_9646 || g_9134 != 0) && g_7090[a].f_09c > g_1e50)
        return;
    g_7090[a].f_09c = g_1e50 + 5000;
    if (fn_13_910a(a)) {
        fn_03_06ec(a, 7, 0, 100);
        return;
    }
    for (i = 0; i <= g_9316; i++) {
        if (g_96d2[g_7090[i].f_04e].f_38 != 6 && g_1df8[14][i].f_18 == 0
            && g_7090[i].flag
            && (g_7090[i].f_052 == 0 || g_7090[i].f_052 == 7
                || g_7090[i].f_098 < g_1e50 || a == g_9646)
            && (u = fn_13_2688(i, k) + -50 * g_7090[i].f_05d
                    + fn_13_2688(i, a)) > 0
            && i != a && k != i) {
            if (i == g_9646 && g_9134 && flow_interactive) {
                if (g_1e50 - 15000 > g_8858) {
                    g_964e = 5;
                    g_9654 = a;
                    g_9650 = s;
                    g_9652 = k;
                    g_8858 = g_1e50;
                    fn_03_06ec(g_9646, 14, a, 0x34);
                }
                return;
            }
            if (g_96d2[g_7090[i].f_04e].f_38 != 7) {
                g_7090[i].f_052 = 5;
                done = 1;
                fn_03_06ec(g_7090[i].f_058, 14, a, 0x13);
            l1:
                g_7090[i].f_094 = g_1e50 + 200;
                g_7090[i].f_098 = g_1e50 + 20000;
                g_7090[a].f_09c = g_1e50 + 15000;
                g_7090[i].f_054 = LO16(g_7090[a].f_03e);
                g_7090[i].f_056 = HI16(g_7090[a].f_03e);
                g_7090[i].f_0ed = 1;
                fn_03_06ec(i, 14, a, 2);
                g_7090[i].f_058 = a;
                fn_13_2714(HI16(g_7090[a].f_03e), a, 15, 0x32, 1, -1);
                return;
            }
        }
    }
    if (done)
        return;
    if (a != g_9646 || flow_interactive)
        fn_03_06ec(a, 7, 0, 5);
}

/* Pick an ally of a against b, or a negative reason code [inferred]. */
/* 13:78b8 */
int16_t fn_13_78b8(int16_t a, int16_t b)
{
    int16_t i, r, m, d;

    if (g_96d2[g_7090[a].f_04e].f_1e / 10 > g_7090[a].f_01e)
        return -6;
    m = fn_13_2688(a, b);
    if (g_96d2[g_7090[b].f_04e].f_38 == g_96d2[g_7090[a].f_04e].f_38)
        m += 200;
    if (g_7090[b].f_05d < 3)
        m += (3 - g_7090[b].f_05d) * 4;
    m += 20 * g_7090[a].f_0f6[b][6];
    m += 40 * g_7090[a].f_0f6[b][8];
    if (g_7090[a].f_0cd == b)
        m += 600;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f_18 == 0 && i != a && i != b && g_7090[i].flag
            && g_7090[i].f_032.a == g_7090[a].f_054
            && g_7090[i].f_032.b == g_7090[a].f_056
            && (g_7090[i].f_038 == 1 || fn_13_2688(i, b) < 0)) {
            r = fn_13_2688(a, i);
            if (g_96d2[g_7090[i].f_04e].f_38 == g_96d2[g_7090[a].f_04e].f_38)
                r += 200;
            if (g_96d2[g_7090[i].f_04e].f_38 == 7) {
                if (g_96d2[g_7090[a].f_04e].f_38 == 3
                    || g_96d2[g_7090[a].f_04e].f_38 == 6)
                    r -= 150;
                else if (g_96d2[g_7090[a].f_04e].f_38 == 1
                         || g_96d2[g_7090[a].f_04e].f_38 == 5)
                    r += 20;
                else
                    r += 100;
            }
            r += 25 * g_7090[i].f_0f6[b][1];
            d = fn_04_5d9c(a, i);
            d += g_7090[a].f_05d * d / -5;
            if (g_96d2[g_7090[b].f_04e].f_38 == g_96d2[g_7090[a].f_04e].f_38
                || g_96d2[g_7090[a].f_04e].f_38 == 4)
                d <<= 1;
            if (g_7090[a].f_0cd == b)
                d += 50;
            if (d < 50)
                return -2;
            if (m < r) {
                if (g_96d2[g_7090[i].f_04e].f_38 == 7)
                    return -3;
                if (g_7090[b].f_0f6[i][1] + 2 < g_7090[i].f_0f6[b][1])
                    return -4;
                return -5;
            }
            return i;
        }
    }
    return -1;
}

/* Object n reacts to the ones attacking it: counts them, then flees,
 * fights back or asks for help [inferred]. */
/* 13:7ba2 */
void fn_13_7ba2(int16_t n)
{
    int16_t i, cnt, j, best, bestj, u1, t, u2, flag;

    cnt = 0;
    if (n == g_9646 && flow_interactive)
        return;
    if (g_92e8 || g_9320 == 7 || g_96d2[g_7090[n].f_04e].f_38 == 7)
        return;
    t = -1;
    if (g_1df8[14][n].f_32 == 14)
        t = g_1df8[14][n].f_34;
    flag = 0;
    if ((g_7090[n].f_052 == 1 || g_7090[n].f_052 == 5)
        && g_7090[n].f_0b8[g_7090[n].f_056 + 10] == 0)
        flag = 1;
    best = 20000;
    bestj = -1;
    if (g_7090[n].f_052 != 0 && g_7090[n].f_052 != 7
        && g_7090[n].f_098 > g_1e50)
        return;
    for (i = 0; i <= g_9316; i++) {
        if (g_1df8[14][i].f_18 == 0 && g_7090[i].f_032.a == 14
            && g_7090[i].f_032.b == n && g_7090[i].f_038 == 1
            && g_7090[i].flag) {
            u1 = fn_04_5d9c(n, i);
            if (u1 < best) {
                best = u1;
                bestj = i;
            }
            cnt++;
        }
    }
    for (i = 0; i < g_9406[2]; i++) {
        if (g_1df8[2][i].f_18 == 0 && g_52ec[i].f_1c.a == 14
            && g_52ec[i].f_1c.b == n && g_52ec[i].f_12 == 10)
            cnt++;
    }
    if (t != -1) {
        bestj = t;
        cnt++;
    }
    if (cnt) {
        if (bestj != -1 && g_7090[n].f_0f6[8][bestj] < -1)
            cnt++;
        if (flag && g_7090[n].f_026[0] > 320 && t == -1)
            return;
        if (g_7090[n].f_038 != 4
            && (g_7090[n].f_052 != 3 || g_7090[n].f_026[0] < 20)
            && (g_7090[n].f_05e * cnt * 6 + 15 > g_7090[n].f_026[0]
                || g_7090[n].f_05e * cnt * 6 + 17 > g_7090[n].f_026[1])
            && (g_7090[n].f_052 == 0
                || g_7090[n].f_098 - 7000 < g_1e50)) {
            if ((cnt * 20 + 35 > best
                 || 15 * g_7090[n].f_05e + 20 > g_7090[n].f_026[0])
                && bestj != -1 && g_7090[n].f_0f6[8][bestj] < -1) {
                g_7090[n].f_006 = g_7090[n].f_032.a = 14;
                g_7090[n].f_008 = g_7090[n].f_032.b = bestj;
                g_7090[n].f_03c = 5;
                g_7090[n].f_03a = 5;
                g_7090[n].f_038 = 4;
                g_7090[n].f_036 = 4;
                g_7090[n].f_052 = 7;
                g_7090[n].f_094 = g_1e50 + 4000;
                fn_03_06ec(bestj, 14, n, 0x47);
            } else if (g_7090[n].f_026[2] < 50
                       && g_7090[n].f_05e * 8 + 35 > g_7090[n].f_026[0]) {
                g_7090[n].f_052 = 13;
                g_7090[n].f_058 = n;
                g_7090[n].f_094 = g_7090[n].f_098 = g_1e50 + 1000;
                g_7090[n].f_0ed = 0;
                if (g_7090[n].f_052 >= 2 && g_7090[n].f_052 <= 4) {
                    if (g_7090[n].f_054 == 14 && g_7090[n].f_058 == n)
                        fn_03_06ec(g_7090[n].f_056, 14, n, 0x8a);
                    else
                        fn_03_06ec(g_7090[n].f_058, 14, n, 0x73);
                    g_7090[n].f_0f6[8][g_7090[n].f_056] = 0;
                    g_7090[n].f_0b8[g_7090[n].f_056 + 10] = -1;
                }
                if (g_7090[n].f_052 == 1 || g_7090[n].f_052 == 2) {
                    fn_03_06ec(g_7090[n].f_056, 14, n, 0x13);
                    fn_03_06ec(g_7090[n].f_058, 14, n, 0x13);
                }
            }
        } else if (g_7090[n].f_038 == 4 && cnt * 20 + 35 < best) {
            g_7090[n].f_038 = 1;
            g_7090[n].f_036 = 1;
            fn_04_8346(n, g_7090[n].f_032.a, g_7090[n].f_032.b, 0x10);
        }
        if (fn_13_9bb8(n, cnt))
            fn_16_0b4e(n);
        if (g_7090[n].f_026[0] < cnt * 20 + 25 && bestj != -1) {
            for (j = 0; j <= g_9316; j++) {
                if (g_1df8[14][j].f_18 == 0 && g_7090[j].flag && j != n
                    && g_7090[j].f_052 == 1 && g_7090[j].f_056 == n
                    && j != g_9646)
                    return;
            }
            if (!fn_13_81c2(n))
                g_7090[n].f_09c = 1;
        } else if (cnt && bestj != -1
                   && (cnt > 1 || best < 78
                       || (g_7090[n].f_032.b == g_952e
                           && g_7090[n].f_032.a == 14 && g_9e49 != 10))) {
            fn_03_00f4(n, 14, bestj);
            if (!fn_13_9970(n))
                g_7090[n].f_09c = 1;
        }
        if (g_96d2[g_7090[n].f_04e].f_38 == 2 && cnt && bestj != -1) {
            for (j = 0; j <= g_9316; j++) {
                if (g_1df8[14][j].f_18 == 0 && g_7090[j].flag && j != n
                    && g_7090[j].f_052 == 1 && g_7090[j].f_056 == n
                    && j != g_9646)
                    return;
            }
            if (!fn_13_81c2(n))
                g_7090[n].f_09c = 1;
        }
    }
    if ((cnt == 0 || best > 60) && g_7090[n].f_038 == 4) {
        g_7090[n].f_036 = 3;
        g_7090[n].f_038 = 3;
        g_7090[n].f_052 = 0;
        g_7090[n].f_094 = g_1e50;
    }
    if (fn_13_9bb8(n, cnt))
        fn_16_0b4e(n);
    if (g_7090[n].f_038 == 1 && g_7090[n].f_032.a == 14
        && g_7090[n].f_0f6[8][g_7090[n].f_032.b] < -2
        && fn_13_2688(n, g_7090[n].f_032.b) < -150 && g_7090[n].flag) {
        fn_03_00f4(n, 14, g_7090[n].f_032.b);
        if (!fn_13_9970(n))
            g_7090[n].f_09c = 1;
    }
    if (g_9406[9] > 1 && g_7090[n].f_032.a != 14 && rand() % 3 == 0
        && g_7090[n].f_09c < g_1e50) {
        for (j = 0; j < g_9406[9]; j++) {
            if (g_1df8[9][j].f_18 == 0) {
                fn_03_00f4(n, 9, j);
                fn_13_9970(n);
                break;
            }
        }
    }
}

/* Object n looks for a helper among the others (like fn_13_8570) [inferred].
 * Returns 1 if one joined, 0 if none, -1 when n asked too recently. */
/* 13:81c2 */
int16_t fn_13_81c2(int16_t n)
{
    int16_t j, u, sc, found;

    u = found = 0;
    if ((n != g_9646 || g_9134 != 0) && g_7090[n].f_09c > g_1e50)
        return -1;
    g_7090[n].f_09c = g_1e50 + 5000;
    fn_13_4eec(n, 15);
    for (j = 0; j <= g_9316; j++) {
        if (g_1df8[14][j].f_18 == 0 && g_7090[j].flag && j != n
            && (g_7090[j].f_052 == 0 || g_7090[j].f_052 == 7
                || g_7090[j].f_098 < g_1e50 || g_7090[j].f_058 == n
                || (flow_interactive && n == g_9646))) {
            sc = fn_13_2688(n, j) + g_7090[j].f_05d * -100;
            if (g_7090[j].f_026[0] < 40)
                sc -= 100;
            if (g_96d2[g_7090[j].f_04e].f_38 == g_96d2[g_7090[n].f_04e].f_38)
                sc += 100;
            if ((g_7090[j].f_032.a == 14 && g_7090[j].f_032.b == n && g_7090[j].f_038 == 1)
                || (g_7090[n].f_032.a == 14 && g_7090[n].f_032.b == j && g_7090[n].f_038 == 1))
                sc -= 800;
            if (g_96d2[g_7090[j].f_04e].f_38 == 0 && g_96d2[g_7090[n].f_04e].f_38 == 2)
                sc += 350;
            if (g_96d2[g_7090[n].f_04e].f_1e / 10 > g_7090[n].f_01e)
                sc -= 1000;
            if (sc > -150) {
                fn_13_4eec(n, 20);
                if (n == g_9646)
                    fn_13_4eec(j, 40);
                if (j == g_9646 && g_9134 && flow_interactive) {
                    if (g_1e50 - 15000 > g_8858) {
                        g_964e = 1;
                        g_9652 = g_9654 = n;
                        g_8858 = g_1e50;
                        fn_03_06ec(g_9646, g_9650 = 14, n, 0x34);
                    }
                } else if (g_96d2[g_7090[j].f_04e].f_38 != 7) {
                    if (g_7090[j].f_052)
                        fn_03_06ec(g_7090[j].f_058, 14, n, 0x13);
                    if (n == g_9646 && g_9134 == 1)
                        fn_03_33b4(1);
                    g_7090[j].f_094 = g_1e50 + 200;
                    found = g_7090[j].f_052 = 1;
                    g_7090[j].f_054 = 14;
                    g_7090[j].f_056 = n;
                    g_7090[n].f_09c = g_7090[j].f_098 = g_1e50 + 15000;
                    g_7090[j].f_058 = n;
                    fn_03_00f4(j, 14, n);
                    g_7090[j].f_0ed = 1;
                    g_7090[j].f_0a4 = g_1e50 - g_7090[j].f_05d * 2000 + 8000;
                    fn_03_06ec(j, 14, n, 2);
                    if (n != g_9646)
                        fn_13_2714(n, j, 15, 0x23, 0, -1);
                    else
                        fn_13_2714(n, j, 15, 15, 0, -1);
                    return 1;
                }
            }
        }
    }
    if (!found) {
        if (n == g_9646 || rand() % 14 < 12 - g_9208
            || (g_0992 + 20 < g_932a && !fn_13_adbe(n, 4, 0x68)))
            if (n != g_9646 || flow_interactive)
                fn_03_06ec(n, 7, 0, 6);
    }
    return 0;
}

/* Object n is asked to fight k: decides whether to accept the duel and
 * sets both up for it [inferred]. */
/* 13:915c */
void fn_13_915c(int16_t n)
{
    int16_t u1, s, k, rel, dist, sc, t, u2, d, res, range;

    u1 = res = 0;
    s = LO16(g_7090[n].f_03e);
    k = HI16(g_7090[n].f_03e);
    g_7090[n].f_09c = g_1e50 + 5000;
    if (s != 14)
        fn_03_06ec(n, 7, 0, 0x14);
    else if (g_96d2[g_7090[k].f_04e].f_38 == 7)
        fn_03_06ec(n, 14, k, 0x40);
    else if (g_96d2[g_7090[k].f_04e].f_1e / 10 > g_7090[k].f_01e)
        fn_03_06ec(n, 14, k, 0xbc);
    else if (g_7090[k].f_052 == 1)
        fn_03_06ec(n, 14, k, 0xbd);
    else if ((n == g_9646 && (!g_9134 || flow_interactive))
             || g_7090[n].f_09c <= g_1e50 || g_7090[n].f_0b8[k + 10] >= 4) {
        range = 0;
        d = fn_04_5d9c(n, k);
        if (d > 500 || d < 20) {
            if (g_7090[k].f_05e > 0 && k != g_9646) {
                if (d > 500) {
                    fn_03_06ec(n, 14, k, 0x4c);
                    fn_13_81c2(k);
                    return;
                }
                fn_03_06ec(n, 14, k, 0x4e);
                goto out;
            }
            if (d < 20)
                range = 1;
            if (d > 500)
                range = 2;
        }
        if (g_7090[k].f_054 == 14 && g_7090[k].f_056 == n
            && g_7090[k].f_052 >= 2 && g_7090[k].f_052 <= 4
            && g_7090[k].f_058 == k
            && g_7090[n].f_054 == 14 && g_7090[n].f_056 == k
            && g_7090[n].f_052 >= 2 && g_7090[n].f_052 <= 4
            && g_7090[n].f_058 == n) {
            fn_03_06ec(n, 14, k, 0x74);
            return;
        }
        if (!g_1df8[14][k].f_18 && g_7090[k].flag) {
            dist = fn_04_5d9c(n, k);
            t = 30 * g_7090[k].f_05e;
            rel = fn_13_2688(k, n);
            sc = 0;
            if (g_7090[n].f_0b8[k + 10] > 2)
                sc = 30 * g_7090[n].f_0b8[k + 10];
            if (rel > 50) {
                sc += 20 * g_7090[k].f_05d;
                sc += rel / -5 - abs(100 - dist) * 2;
                sc += 15 * g_7090[n].f_0b8[k + 10];
                if (g_7090[n].f_0b8[k + 10] == -1)
                    sc -= 100;
                if (range
                    || (sc > -70
                        && (g_7090[k].f_052 == 0 || g_7090[k].f_052 == 7
                            || g_7090[k].f_098 < g_1e50 || k == g_9646)))
                    res = 2;
                else if (n != g_9646 || flow_interactive) {
                    if (g_7090[k].f_052 != 0 && g_7090[k].f_098 > g_1e50)
                        fn_03_06ec(n, 14, k, 0x10);
                    else
                        fn_03_06ec(n, 14, k, 0xe);
                }
            } else {
                if (g_7090[k].f_052 != 0 && g_7090[k].f_052 != 7
                    && g_7090[k].f_098 > g_1e50)
                    sc = -110;
                else
                    sc = -30;
                sc += 25 * g_7090[n].f_0b8[k + 10] - rel / 5 - t + dist;
                if (g_7090[n].f_0b8[k + 10] == -1)
                    sc -= 140;
                if (range)
                    res = 1;
                else if (sc > -90)
                    res = 1;
                else if (n != g_9646 || flow_interactive) {
                    if (g_7090[k].f_052 != 0 && g_7090[k].f_052 != 7
                        && g_7090[k].f_098 > g_1e50)
                        fn_03_06ec(n, 14, k, 0x10);
                    else
                        fn_03_06ec(n, 14, k, 0xf);
                }
            }
            if (res == 0) {
                g_7090[n].f_0b8[k + 10] = -1;
                return;
            }
            g_7090[n].f_0b8[k + 10] = 21;
            g_7090[k].f_0b8[n + 10] = 20;
            if (g_7090[k].f_052)
                fn_03_06ec(g_7090[k].f_058, 14, n, 0x13);
            if (g_7090[n].f_052)
                fn_03_06ec(g_7090[n].f_058, 14, n, 0x13);
            if (k == g_9646 && g_9134 && flow_interactive) {
                if (g_1e50 - 15000 > g_8858) {
                    g_964e = 11;
                    g_9650 = 14;
                    g_9652 = g_9654 = n;
                    g_8858 = g_1e50;
                }
            } else {
                g_7090[k].f_052 = 2;
                g_7090[k].f_094 = g_1e50 + 200;
                g_7090[k].f_098 = g_1e50 + 40000;
                g_7090[k].f_09c = g_1e50 + 8000;
                g_7090[k].f_054 = 14;
                g_7090[k].f_056 = n;
                g_7090[k].f_058 = k;
                g_7090[k].f_0ed = 1;
                g_7090[k].f_032.a = 14;
                g_7090[k].f_032.b = n;
                g_7090[k].f_038 = 1;
                g_7090[k].f_0a4 = g_1e50 - g_7090[k].f_05e * 2000 + 8000;
                fn_04_8346(k, 14, n, 0x15);
                if (k == g_9646)
                    g_0a62 = 1;
                g_7090[n].f_052 = 2;
                g_7090[n].f_094 = g_1e50 + 200;
                g_7090[n].f_098 = g_1e50 + 40000;
                g_7090[n].f_09c = g_1e50 + 8000;
                g_7090[n].f_054 = 14;
                g_7090[n].f_056 = k;
                g_7090[n].f_058 = n;
                g_7090[n].f_0ed = 0;
                g_7090[n].f_038 = 1;
                if (n != g_9646)
                    fn_03_00f4(n, 14, k);
                g_7090[n].f_032.a = 14;
                g_7090[n].f_032.b = k;
                g_7090[n].f_0a4 = g_1e50 - g_7090[n].f_05e * 2000 + 8000;
                if (res == 1 && (g_96d2[g_7090[n].f_04e].f_38 == 4 || g_96d2[g_7090[n].f_04e].f_38 == 0))
                    g_7090[n].f_052 = 3;
                fn_04_8346(n, 14, k, 0x14);
                if (g_9320 != 7)
                    LO16(g_8e00) = LO16(g_8e04) = g_9680 = g_9682 = 0;
                if (res) {
                    g_7090[n].f_0f6[8][k] = 0;
                    g_7090[k].f_0f6[8][n] = 0;
                    if (n == g_9646 && g_9134 == 1)
                        fn_03_33b4(3);
                }
                fn_13_2714(HI16(g_7090[n].f_03e), n, -12, -55, 1, -1);
            }
            if (range == 1) {
                fn_03_06ec(k, 14, n, 0x4b);
                fn_03_06ec(n, 14, k, 0x4d);
            } else if (range == 2) {
                fn_03_06ec(k, 14, n, 0x4d);
                fn_03_06ec(n, 14, k, 0x4b);
            } else if (g_7090[n].f_052 == 3) {
                fn_03_06ec(k, 14, n, 0x82);
                fn_03_06ec(n, 14, k, 0x12);
            } else if (res == 1) {
                fn_03_06ec(n, 14, k, 0x12);
                fn_03_06ec(k, 14, n, 0x16);
            } else if (res == 2) {
                fn_03_06ec(n, 14, k, 0x11);
                fn_03_06ec(k, 14, n, 0x15);
            }
        }
    }
out:;
}

/* Object n in duel states 0x14-0x17 (approach, challenge, fight) [inferred]. */
/* 13:a6bc */
void fn_13_a6bc(int16_t n)
{
    int16_t i, j, k, d, y, x, c, u2, flag, cnt;

    g_7090[n].f_094 = g_1e50 + 750;
    if (g_9406[6] && g_1df8[14][n].f_36 == -1) {
        for (i = 0; i < g_9406[6]; i++) {
            if (g_6670[i + 4].f_04.x == 0x10 && g_1df8[6][i].f_18 == 0) {
                g_7090[n].f_006 = 6;
                g_7090[n].f_008 = i;
                g_7090[n].f_03a = 2;
                g_7090[n].f_036 = 2;
                if (g_1df8[14][n].f_36 != 14)
                    return;
                for (j = 0; j <= g_7090[n].cnt; j++) {
                    if (g_7090[n].f_0b8[j] == 15) {
                        fn_04_584c(j, n, 0);
                        break;
                    }
                }
                return;
            }
        }
    }
    if (g_7090[n].f_052 == 0x14) {
        flag = 0;
        if (g_1df8[g_7090[n].f_054][g_7090[n].f_056].f_18)
            flag = 1;
        if (!g_7090[g_7090[n].f_056].flag)
            flag = 1;
        if ((g_7090[g_7090[n].f_056].f_038 != 1 && g_7090[n].f_098 < g_1e50)
            || g_7090[n].f_098 < g_1e50 + 5000)
            flag = 1;
        if (flag) {
            k = g_7090[n].f_056;
            for (i = 0; i <= g_9316; i++) {
                if (++k > g_9316)
                    k = 0;
                if (g_1df8[14][k].f_18 == 0 && g_7090[k].flag && g_96d2[g_7090[k].f_04e].f_38 != 7)
                    break;
            }
            g_7090[n].f_054 = 14;
            g_7090[n].f_056 = k;
            g_7090[n].f_098 = g_1e50 + 13000;
            if (g_1df8[14][k].f_18 || !g_7090[k].flag || g_96d2[g_7090[k].f_04e].f_38 == 7) {
                fn_03_06ec(g_9646, 14, n, 0xb7);
                g_7090[n].f_006 = 12;
                g_7090[n].f_008 = 0;
                g_7090[n].f_03a = 2;
                g_7090[n].f_036 = 2;
                return;
            }
        }
        g_7090[n].f_006 = g_7090[n].f_054;
        g_7090[n].f_008 = g_7090[n].f_056;
        g_7090[n].f_03a = 2;
        g_7090[n].f_036 = 3;
        if (g_7090[g_7090[n].f_056].f_032.a == 14
            && g_7090[g_7090[n].f_056].f_032.b == n
            && g_7090[g_7090[n].f_056].f_038 == 1) {
            g_7090[n].f_036 = 1;
            fn_04_8346(n, 14, g_7090[n].f_056, 0x12);
        }
    } else if (g_7090[n].f_052 == 0x15) {
        if (g_7090[n].f_0ed == 1) {
            fn_03_06ec(g_7090[n].f_056, 14, n, 0x3b);
            g_7090[n].f_0ed = 0;
        } else {
            g_7090[n].f_052 = 0x14;
            g_7090[n].f_098 = g_1e50 + 5000;
        }
        g_7090[n].f_094 = g_1e50 + 2000;
    } else if (g_7090[n].f_052 == 0x16) {
        if (g_1df8[g_7090[n].f_054][g_7090[n].f_056].f_18 == 0
            && g_7090[g_7090[n].f_056].flag) {
            k = g_7090[n].f_056;
            if (g_7090[k].f_038 == 1 && g_7090[k].f_032.a == 14
                && g_7090[k].f_032.b == n && g_7090[n].f_098 < g_1e50) {
                cnt = 0;
                for (i = 0; i < 5; i++)
                    if ((&g_7090[n].f_044[0])[i])
                        cnt++;
                if (cnt > 1) {
                    if (k == g_9646)
                        g_a14d[7]++;
                    g_7090[n].f_052 = 0x17;
                    if (g_7090[n].f_0ed == 2 || g_7090[n].f_0ed == -1)
                        g_7090[n].f_0ed = 2;
                    else
                        g_7090[n].f_0ed = 1;
                    g_7090[n].f_098 = g_1e50 + 20000;
                    g_7090[n].f_094 = g_1e50;
                    return;
                }
            }
            if (g_7090[n].f_0ed > 0) {
                g_7090[n].f_006 = 14;
                g_7090[n].f_008 = k;
                g_7090[n].f_03a = 2;
                g_7090[n].f_036 = 3;
                d = fn_08_285a(&y, &x, g_1df8[14][n].f_04, g_1df8[14][k].f_04);
                if (d < 250) {
                    if (g_7090[n].f_0ed == 1) {
                        fn_03_06ec(k, 14, n, 0x3d);
                        g_7090[n].f_0ed = 0;
                        g_a147 = g_1e68;
                        g_a14b = g_91f8;
                        g_a161 = g_a163;
                        g_a162 = (char)n;
                    } else {
                        fn_03_06ec(k, 14, n, 0x57);
                        g_7090[n].f_0ed = -1;
                    }
                    if (g_7090[k].f_05e > 0 && (k != g_9646 || !flow_interactive)) {
                        if ((c = g_96d2[g_7090[k].f_04e].f_38) != 3 && c != 6 && c != 1) {
                            g_7090[k].f_052 = 10;
                            g_7090[k].f_098 = g_1e50 + 500;
                            g_7090[k].f_058 = n;
                        } else {
                            g_7090[k].f_052 = 2;
                            g_7090[k].f_054 = 14;
                            g_7090[k].f_056 = n;
                            g_7090[k].f_058 = k;
                            fn_04_8346(k, 14, n, 10);
                        }
                    }
                    for (i = 0; i <= g_7090[n].cnt; i++) {
                        if (g_7090[n].f_0b8[i] == 15) {
                            fn_04_584c(i, n, 0);
                            break;
                        }
                    }
                }
            } else {
                g_7090[n].f_006 = 12;
                g_7090[n].f_008 = 0;
                g_7090[n].f_03a = 2;
                g_7090[n].f_036 = 2;
            }
        } else {
            g_7090[n].f_006 = 12;
            g_7090[n].f_008 = 0;
            g_7090[n].f_03a = 2;
            g_7090[n].f_036 = 2;
        }
        if (g_7090[n].f_0ed < 1 && g_1df8[14][n].f_36 != 10
            && (g_1df8[14][n].f_36 != 14 || g_1df8[14][n].f_38 != k))
            g_7090[n].f_0ed = 1;
    } else {
        g_7090[n].f_052 = 0x17;
        k = g_7090[n].f_056;
        if (g_7090[n].f_0ed != 0) {
            if (g_7090[n].f_0ed == 2
                || (g_7090[n].f_0f6[k][1] > 2 && g_7090[n].f_0f6[8][k] < -2
                    && g_7090[n].f_026[0] < 55)) {
                fn_03_06ec(g_9646, 14, n, 0xb7);
                g_7090[n].f_006 = 12;
                g_7090[n].f_008 = 0;
                g_7090[n].f_03a = 2;
                g_7090[n].f_036 = 2;
                g_7090[n].f_0ed = 0;
                fn_13_adbe(k, 20, 0x58);
                return;
            }
            fn_03_06ec(k, 14, n, 0x3e);
            g_7090[n].f_0ed = 0;
            fn_03_00f4(n, g_7090[n].f_054, g_7090[n].f_056);
            fn_04_8346(n, 14, g_7090[n].f_056, 0x13);
        }
        if (g_7090[n].f_098 < g_1e50 && g_7090[n].f_05e == 1) {
            g_7090[n].f_052 = 0x16;
            g_7090[n].f_0ed = 2;
            g_7090[n].f_094 = g_1e50;
            g_7090[n].f_098 = g_1e50 + 5000;
            return;
        }
        if (g_1df8[14][k].f_18 || !g_7090[k].flag) {
            fn_03_06ec(g_9646, 14, n, 0xb7);
            g_7090[n].f_006 = 12;
            g_7090[n].f_008 = 0;
            g_7090[n].f_03a = 2;
            g_7090[n].f_036 = 2;
            return;
        }
        fn_03_00f4(n, g_7090[n].f_054, g_7090[n].f_056);
        g_7090[n].f_006 = 14;
        g_7090[n].f_008 = k;
        g_7090[n].f_03a = 2;
        g_7090[n].f_036 = 1;
    }
}

/* Object n's per-tick behaviour by state f_050 (follow, escort, flee,
 * seek help, ...); class 7 goes to fn_13_a6bc [inferred]. */
/* 13:6900 */
void fn_13_6900(int16_t n)
{
    int16_t d, t, i, y, x, best, bt, bi, u1, best2, bk, dist, cnt, r;
    char buf[40];

    g_7090[n].f_094 = g_1e50 + 4000;
    if (g_96d2[g_7090[n].f_04e].f_38 == 7) {
        fn_13_a6bc(n);
    } else if (g_96d2[g_7090[n].f_04e].f_38 == 6 && g_7090[n].f_058 != n
               && (n != g_9646 || !flow_interactive)) {
        g_7090[n].f_052 = 0;
        fn_03_06ec(g_7090[n].f_058, 14, n, 0x83);
        g_7090[n].f_094 = g_1e50;
        g_7090[n].f_0ed = 0;
        if (!flow_interactive && n == g_9646) {
            fn_10_a332(g_8630, 0x58d, 1, g_7090[g_9646].f_058, buf, 5);
            g_058c = 1;
            g_05c0 = g_1e50 + 700;
        }
    } else if (g_7090[n].f_052 == 1) {
        best = 20000;
        r = fn_13_78b8(n, g_7090[n].f_056);
        if (r >= 0) {
            g_7090[n].f_006 = 14;
            g_7090[n].f_008 = r;
            g_7090[n].f_036 = 1;
            g_7090[n].f_03a = 2;
            if (g_7090[n].f_0ed == 1) {
                g_7090[n].f_0ed = 0;
                fn_13_2714(g_7090[n].f_056, n, 20, 60, 1, 8);
                fn_03_06ec(g_7090[n].f_056, 14, n, 1);
                if (g_96d2[g_7090[n].f_04e].f_38 == 4) {
                    if (g_7090[n].f_0ee[r] != 0 && g_7090[n].f_0ee[r] <= 5
                        && g_7090[n].f_062[r + 8] > 3 && g_96d2[g_7090[n].f_04e].f_38 != 4) {
                        fn_03_06ec(r, 14, n, 0x7f);
                        g_7090[n].f_052 = 4;
                        fn_04_8346(n, 14, r, 11);
                        g_7090[n].f_094 = g_1e50 + 500;
                        g_7090[n].f_054 = 14;
                        g_7090[n].f_056 = r;
                        g_7090[n].f_0ed = 1;
                        g_7090[n].f_062[r + 8] = 0;
                    } else
                        fn_03_06ec(r, 14, n, 0x80);
                    fn_13_2714(n, r, 0, -140, 0, 3);
                } else
                    fn_03_06ec(r, 14, n, 0x81);
                if (g_7090[n].f_052 != 4)
                    fn_04_8346(n, 14, r, 14);
            }
        } else if (r < -1) {
            fn_03_06ec(g_7090[n].f_056, 14, n, 0xad - r);
            g_7090[n].f_052 = 0;
        } else {
            g_7090[n].f_052 = 5;
            g_7090[n].f_094 = g_1e50 + 200;
            fn_03_06ec(g_7090[n].f_058, 14, n, 1);
            fn_03_06ec(g_7090[n].f_056, 14, n, 1);
            g_7090[n].f_0ed = 0;
        }
    } else if (g_7090[n].f_052 >= 2 && g_7090[n].f_052 <= 4) {
        if (g_7090[n].f_054 == 14)
            dist = fn_04_5d9c(n, g_7090[n].f_056);
        if (!((g_7090[n].f_054 == 14 && (dist <= 15 || dist >= 600)
             && g_7090[n].f_052 != 4 && (n != g_9646 || !flow_interactive)
             && g_7090[n].f_05e >= 2)
            || g_1df8[g_7090[n].f_054][g_7090[n].f_056].f_18 == 1
            || (g_7090[n].f_054 == 14 && !g_7090[g_7090[n].f_056].flag)
            || (dist <= 75 && g_7090[n].f_0f6[8][g_7090[n].f_056] <= -6
                && g_7090[n].f_052 < 3 && g_7090[n].f_054 == 14))) {
            g_7090[n].f_006 = g_7090[n].f_054;
            g_7090[n].f_008 = g_7090[n].f_056;
            g_7090[n].f_036 = 1;
            g_7090[n].f_03a = 2;
            if (g_7090[n].f_0ed == 1) {
                g_7090[n].f_0ed = 0;
                if (g_7090[n].f_058 == n && g_7090[n].f_054 == 14
                    && g_7090[n].f_056 == g_9646)
                    fn_10_754a(0x3f, 0, 0, 0);
                else
                    fn_03_06ec(g_7090[n].f_058, 14, n, 1);
            }
        } else {
            if (g_7090[n].f_054 == 14
                && g_7090[n].f_0f6[8][g_7090[n].f_056] < g_7090[n].f_05e - 7
                && 20 * g_7090[n].f_05d + 15 > fn_04_5d9c(n, g_7090[n].f_056)) {
                if (g_7090[n].f_058 == n)
                    fn_03_06ec(g_7090[n].f_056, 14, n, 0x8a);
                else
                    fn_03_06ec(g_7090[n].f_058, 14, n, 0x73);
                g_7090[n].f_0f6[8][g_7090[n].f_056] = 0;
                g_7090[n].f_0b8[g_7090[n].f_056 + 10] = -1;
            } else {
                g_7090[n].f_052 = 6;
                fn_03_06ec(g_7090[n].f_058, 14, n, 0x13);
            }
            g_7090[n].f_052 = 0;
        }
    } else if (g_7090[n].f_052 == 5) {
        d = fn_08_285a(&y, &x, g_1df8[14][n].f_04,
                       g_1df8[g_7090[n].f_054][g_7090[n].f_056].f_04);
        if (d < 350)
            g_7090[n].f_03a = 3;
        else
            g_7090[n].f_03a = 2;
        g_7090[n].f_006 = g_7090[n].f_054;
        g_7090[n].f_008 = g_7090[n].f_056;
        g_7090[n].f_036 = 3;
        g_7090[n].f_094 = g_1e50 + 700;
        if (g_7090[g_7090[n].f_056].f_026[0] > 40 && g_7090[n].f_098 < g_1e50
            && (n != g_9646 || !g_9134 || !flow_interactive)) {
            fn_03_06ec(g_7090[n].f_058, 14, n, 0x13);
            g_7090[n].f_052 = 0;
            if (g_7090[n].f_0cd == g_7090[n].f_056 && n != g_9646) {
                g_7090[n].f_052 = 10;
                g_7090[n].f_094 = g_1e50 + 500;
                return;
            }
        }
        if (!g_7090[g_7090[n].f_056].flag) {
            g_7090[n].f_052 = 0;
            g_7090[n].f_094 = g_1e50 + 500;
            return;
        }
        r = fn_13_78b8(n, g_7090[n].f_056);
        if (r > -1) {
            g_7090[n].f_008 = r;
            g_7090[n].f_036 = 1;
            g_7090[n].f_03a = 2;
            g_7090[n].f_052 = 1;
            g_7090[n].f_0ed = 1;
            g_7090[n].f_094 = g_1e50 + 700;
            return;
        }
        if (r < -1) {
            fn_03_06ec(g_7090[n].f_056, 14, n, 0xad - r);
            g_7090[n].f_052 = 0;
            if (g_7090[n].f_0cd == g_7090[n].f_056 && n != g_9646)
                g_7090[n].f_052 = 10;
            g_7090[n].f_094 = g_1e50 + 500;
        }
    } else if (g_7090[n].f_052 == 7) {
        if (g_7090[n].f_0ed == 1 && g_7090[n].f_058 != n) {
            g_7090[n].f_0ed = 0;
            fn_03_06ec(g_7090[n].f_058, 14, n, 1);
        }
        g_7090[n].f_094 = g_1e50 + 2000;
        best = 20000;
        bt = -1;
        t = 14;
        for (i = 0; i < g_9406[t]; i++) {
            if (t == 14 && i == n)
                continue;
            if (g_1df8[t][i].f_18 == 0 && g_1df8[t][i].f_44 != 0) {
                d = fn_08_285a(&y, &x, g_1df8[14][n].f_04, g_1df8[t][i].f_04);
                if (t == 14 && fn_13_2688(i, n) < 100)
                    d -= 150;
                if (d < best) {
                    best = d;
                    bt = t;
                    bi = i;
                }
            }
        }
        if (bt != -1) {
            g_7090[n].f_006 = bt;
            g_7090[n].f_008 = bi;
            g_7090[n].f_03a = 5;
            if (best < 300)
                g_7090[n].f_036 = 3;
            else if (fn_09_88ba(g_1df8[14][bi].f_0c) > 30
                     || fn_09_88ba(g_1df8[14][bi].f_0e) > 30) {
                fn_11_5ab6(n, 5);
                g_7090[n].f_036 = 5;
            }
        } else
            g_7090[n].f_036 = 5;
        if (g_7090[n].f_098 < g_1e50 && (n != g_9646 || !flow_interactive))
            g_7090[n].f_052 = 0;
    } else if (g_7090[n].f_052 == 9) {
        if (g_7090[n].f_0ed == 1) {
            g_7090[n].f_0ed = 0;
            fn_03_06ec(g_7090[n].f_058, 14, n, 1);
        }
        best2 = 20000;
        bk = -1;
        for (t = cnt = 0; t <= g_9316; t++) {
            if (g_1df8[14][t].f_18 == 0 && g_7090[t].f_032.a == 14
                && g_7090[t].f_032.b == n && g_7090[t].f_038 == 1) {
                dist = fn_04_5d9c(n, t);
                if (dist < best2) {
                    best2 = dist;
                    bk = t;
                }
                cnt++;
            }
        }
        if ((cnt != 0 && best2 < 70) || cnt > 1) {
            if (!g_9134 || !flow_interactive || n != g_9646) {
                g_7090[n].f_052 = g_7090[n].f_054 = 0;
                g_7090[n].f_094 = g_1e50;
                fn_03_06ec(g_7090[n].f_058, 14, n, 0x21);
            }
        }
        if (g_1df8[g_7090[n].f_054][g_7090[n].f_056].f_18) {
            fn_03_06ec(g_7090[n].f_058, 14, n, 0x22);
            g_7090[n].f_052 = 0;
            g_7090[n].f_094 = g_1e50;
        }
        g_7090[n].f_03a = g_7090[n].f_036 = 2;
        g_7090[n].f_006 = g_7090[n].f_054;
        g_7090[n].f_008 = g_7090[n].f_056;
    } else if (g_7090[n].f_052 == 10) {
        if (g_7090[n].f_0ed == 1) {
            g_7090[n].f_0ed = 0;
            fn_03_06ec(g_7090[n].f_058, 14, n, 1);
        }
        best = 20000;
        for (t = 0; t < g_9318 * 2; t += 2) {
            d = fn_08_285a(&y, &x, g_1df8[14][n].f_04, g_1df8[12][t].f_04);
            if (d < best) {
                best = d;
                fn_03_06ec(g_9646, 14, n, 0xb7);
                g_7090[n].f_006 = 12;
                g_7090[n].f_008 = t;
                g_7090[n].f_03a = g_7090[n].f_036 = 2;
            }
        }
    } else if (g_7090[n].f_052 == 12) {
        if (g_7090[n].f_0ed == 1) {
            g_7090[n].f_0ed = 0;
            fn_03_06ec(g_7090[n].f_058, 14, n, 1);
        }
        best = 20000;
        r = -1;
        for (i = 0; i < g_9406[4]; i++) {
            if (g_1df8[4][i].f_18 == 0) {
                d = fn_08_285a(&y, &x, g_1df8[14][n].f_04, g_1df8[4][i].f_04);
                if (d < best) {
                    best = d;
                    r = i;
                }
            }
        }
        if (r >= 0) {
            g_7090[n].f_006 = g_7090[n].f_054 = 4;
            g_7090[n].f_056 = r;
            g_7090[n].f_008 = r;
            g_7090[n].f_03a = g_7090[n].f_036 = 2;
        } else {
            fn_03_06ec(g_7090[n].f_058, 14, n, 0x38);
            g_7090[n].f_052 = 0;
        }
    } else if (g_7090[n].f_052 == 13) {
        if (g_7090[n].f_0ed == 1) {
            g_7090[n].f_0ed = 0;
            fn_03_06ec(g_7090[n].f_058, 14, n, 1);
            if ((g_7090[n].f_026[0] < 25 || g_7090[n].f_026[2] < 25)
                && g_7090[n].f_0ce + g_7090[n].f_0dc > 300)
                fn_16_0b4e(n);
            else if ((g_7090[n].f_05e * 4 + 30 > g_7090[n].f_026[0]
                      || g_7090[n].f_026[2] < 29)
                     && g_7090[n].f_0ce < 200) {
                bk = -1;
                if (g_7090[n].f_038 != 4 && g_932c) {
                    best2 = 20000;
                    for (t = 0; t <= g_9316; t++) {
                        if (g_1df8[14][t].f_18 == 0 && g_7090[t].f_032.a == 14
                            && g_7090[t].f_032.b == n && g_7090[t].f_038 == 1) {
                            bk = t;
                            break;
                        }
                    }
                    if (bk != -1) {
                        g_7090[n].f_006 = g_7090[n].f_032.a = 14;
                        g_7090[n].f_008 = g_7090[n].f_032.b = bk;
                        g_7090[n].f_03c = 5;
                        g_7090[n].f_03a = 5;
                        g_7090[n].f_038 = 4;
                        g_7090[n].f_036 = 4;
                        g_7090[n].f_052 = 7;
                        g_7090[n].f_094 = g_1e50 + 4000;
                        fn_03_06ec(bk, 14, n, 0x47);
                        return;
                    }
                }
                if (bk == -1) {
                    best = 20000;
                    for (t = 0; t < g_9318 * 2; t += 2) {
                        d = fn_08_285a(&y, &x, g_1df8[14][n].f_04, g_1df8[12][t].f_04);
                        if (d < best) {
                            best = d;
                            g_7090[n].f_006 = 12;
                            g_7090[n].f_008 = t;
                            g_7090[n].f_03a = g_7090[n].f_036 = 2;
                        }
                    }
                    g_7090[n].f_094 = g_1e50 + 500;
                    if (g_96d2[g_7090[g_9646].f_04e].f_38 == g_96d2[g_7090[n].f_04e].f_38)
                        fn_03_06ec(g_9646, 14, n, 0x59);
                    return;
                }
            }
        }
        best = 20000;
        bt = -1;
        for (t = 0; t <= g_9316; t++) {
            if (g_1df8[14][t].f_18 == 0 && g_7090[t].f_038 == 1
                && g_7090[t].f_032.a == 14 && g_7090[t].f_032.b == n) {
                d = fn_08_285a(&y, &x, g_1df8[14][n].f_04, g_1df8[14][t].f_04);
                if (d < best) {
                    bt = 14;
                    bi = t;
                    best = d;
                }
            }
        }
        for (t = 0; t < g_9406[2]; t++) {
            if (g_1df8[2][t].f_18 == 0 && g_52ec[t].f_12 == 15
                && g_52ec[t].f_1c.a == 14 && g_52ec[t].f_1c.b == n) {
                d = fn_08_285a(&y, &x, g_1df8[14][n].f_04, g_1df8[2][t].f_04);
                if (d < best) {
                    bt = 2;
                    bi = t;
                    best = d;
                }
            }
        }
        if (bt != -1) {
            g_7090[n].f_006 = bt;
            g_7090[n].f_008 = bi;
            g_7090[n].f_036 = 1;
            g_7090[n].f_03a = 2;
            g_7090[n].f_094 = g_1e50 + 5000;
            fn_04_8346(n, bt, bi, 15);
            return;
        }
        if (g_7090[n].f_058 != n)
            fn_03_06ec(g_7090[n].f_058, 14, n, 0x39);
        g_7090[n].f_052 = 7;
        g_7090[n].f_094 = g_1e50 + 1500;
        g_7090[n].f_0ed = 1;
        g_7090[n].f_098 = g_1e50 + 20000;
    } else if (g_7090[n].f_052 == 14) {
        if (g_7090[g_7090[n].f_056].flag && !g_1df8[14][g_7090[n].f_056].f_18
            && g_7090[g_7090[n].f_056].f_038 != 1
            && (g_7090[g_7090[n].f_056].f_038 == 2
                || (g_7090[n].f_056 == g_9646 && !g_9134))) {
            if (g_7090[g_7090[n].f_056].f_038 == 2
                || g_1df8[g_7090[g_7090[n].f_056].f_032.a][g_7090[g_7090[n].f_056].f_032.b].f_53) {
                g_7090[n].f_006 = g_7090[g_7090[n].f_056].f_032.a;
                g_7090[n].f_008 = g_7090[g_7090[n].f_056].f_032.b;
                g_7090[n].f_03a = g_7090[n].f_036 = 2;
            } else {
                g_7090[n].f_006 = 14;
                g_7090[n].f_008 = g_7090[n].f_056;
                g_7090[n].f_036 = 3;
                g_7090[n].f_03a = 2;
            }
        } else {
            g_7090[n].f_052 = 0;
            g_7090[n].f_094 = g_7090[n].f_098 = g_1e50;
        }
    } else {
        if (n == g_9646 && flow_interactive) {
            if (fn_03_0000(LO16(g_7090[n].f_03e), HI16(g_7090[n].f_03e))) {
                g_7090[n].f_006 = LO16(g_7090[n].f_03e);
                g_7090[n].f_008 = HI16(g_7090[n].f_03e);
            }
            g_7090[n].f_052 = 7;
            g_7090[n].f_094 = g_1e50;
            g_7090[n].f_036 = 5;
        } else
            g_7090[n].f_052 = 0;
    }
}

/* Summon a helper of kind b for object a (respawn a parked ship or
 * create a new one); c: message for a, or -1. Returns 0, 1 (reused) or 2
 * (new) [inferred]. */
/* 13:ae68 */
int16_t fn_13_ae68(int16_t a, int16_t b, int16_t c)
{
    int16_t i, j, s, lvl, st, cls, found, flag;

    found = 0;
    if ((g_9320 == 6 || g_9320 == 7) && (b != 0x15 || g_a163 != 8))
        return 0;
    if (g_9208 * 2 + 1 < g_964c && b != 0x15)
        return 0;
    if (g_9208 + 3 < g_9316)
        return 0;
    if (g_92e8 && b != 0x13)
        return 0;
    if (b == 0x15) {
        lvl = 1;
        cls = 7;
        st = 0x16;
    } else if (b == 0x14) {
        lvl = 0;
        cls = 7;
        st = 0x17;
    } else if (b == 4) {
        if (g_7090[a].f_0cd >= 0)
            return 0;
        lvl = -1;
        cls = 4;
        st = 1;
        if (g_96d2[g_7090[a].f_04e].f_38 == 2 && g_3824[0][2] > 50)
            cls = 0;
        if (g_96d2[g_7090[a].f_04e].f_38 == 3)
            cls = 3;
        if (g_96d2[g_7090[a].f_04e].f_38 == 6 || g_3824[cls][g_96d2[g_7090[a].f_04e].f_38] < 0)
            return 0;
        for (i = 0; i < g_9316; i++)
            if (g_7090[i].flag && g_96d2[g_7090[i].f_04e].f_38 == cls && g_7090[i].f_0cd == a)
                return 0;
        if (g_7090[a].f_038 == 1 && cls == 4) {
            if (g_7090[a].f_0f6[8][8] == 3 || g_7090[a].f_0f6[8][8] == 13
                || g_7090[a].f_0f6[8][8] == 8 || g_7090[a].f_0f6[8][8] == 10)
                return 0;
        }
    } else if (b == 3) {
        if (g_7090[a].f_0cd >= 0)
            return 0;
        lvl = -1;
        cls = 3;
        st = 4;
        for (i = 0; i < g_9316; i++)
            if (g_7090[i].flag && g_96d2[g_7090[i].f_04e].f_38 == cls && g_7090[i].f_0cd == a)
                return 0;
    } else if (b == 0x16) {
        lvl = 2;
        cls = 7;
        st = 0x14;
    } else if (b == 0x13) {
        cls = g_96d2[g_7090[g_9646].f_04e].f_38;
        st = 4;
    }
    if (cls == 7) {
        for (j = 0; j <= g_9316; j++) {
            if (g_1df8[14][j].f_18 && g_96d2[g_7090[j].f_04e].f_38 == cls
                && (g_7090[j].f_05e == lvl || lvl == -1)) {
                if (g_7090[j].f_05e < 2)
                    fn_10_744c(0x70);
                fn_16_3784(j, 1);
                s = rand() % g_9318;
                g_1df8[14][j].f_04 = g_1df8[8][s * 2].f_04;
                g_1df8[14][j].f_04.x += g_1df8[8][s * 2].f_22 - g_1df8[14][j].f_22 / 2
                                     + g_6670[s].f_12 / 2;
                g_1df8[14][j].f_18 = 0;
                fn_10_754a(0x27, 14, j, found = 1);
                fn_12_2556(14, j);
                fn_07_13b2(2, 14, j);
                g_7090[j].f_052 = st;
                g_7090[j].f_054 = 14;
                g_7090[j].f_056 = a;
                g_7090[j].f_032.a = 14;
                g_7090[j].f_032.b = a;
                g_7090[j].f_094 = g_1e50;
                g_7090[j].f_0ed = 1;
                g_7090[j].f_058 = j;
                g_7090[j].f_098 = g_1e50 + 5000;
                g_7090[j].f_038 = 3;
                g_7090[j].f_0cd = a;
                return 1;
            }
        }
    }
    for (j = flag = 0; j <= g_9316; j++) {
        if (b != 4 && b != 0x13) {
            if (!g_1df8[14][j].f_18 && g_96d2[g_7090[j].f_04e].f_38 == cls
                && (g_7090[j].f_05e == lvl || lvl == -1)) {
                if (g_7090[j].flag
                    && (g_7090[j].f_0cd == -1 || g_7090[j].f_0cd == a)) {
            if (b == 0x15 || b == 0x14) {
                if (g_7090[j].f_0cd == a && g_7090[j].f_052 > 0x14)
                    return 0;
                fn_03_06ec(g_7090[j].f_056, 14, j, 0x3f);
            }
            g_7090[j].f_052 = st;
            g_7090[j].f_054 = 14;
            g_7090[j].f_056 = a;
            g_7090[j].f_0ed = 1;
            g_7090[j].f_058 = j;
            g_7090[j].f_094 = g_1e50;
            g_7090[j].f_038 = 3;
            g_7090[j].f_0cd = a;
            if (b == 3)
                fn_04_8346(j, 14, a, 0xd);
            return 1;
                } else
                    flag = 1;
            }
        } else if (b == 4 && g_7090[j].flag && g_1df8[14][j].f_18
                   && g_96d2[g_7090[j].f_04e].f_38 == g_96d2[g_7090[a].f_04e].f_38) {
            s = rand() % g_9318;
            g_1df8[14][j].f_04 = g_1df8[8][s * 2].f_04;
            g_1df8[14][j].f_04.x += g_1df8[8][s * 2].f_22 - g_1df8[14][j].f_22 / 2
                                 + g_6670[s].f_12 / 2;
            g_1df8[14][j].f_18 = 0;
            fn_10_754a(0x27, 14, j, 1);
            fn_12_2556(14, j);
            fn_07_13b2(2, 14, j);
            g_7090[j].f_052 = st;
            g_7090[j].f_054 = 14;
            g_7090[j].f_056 = a;
            g_7090[j].f_032.a = 14;
            g_7090[j].f_032.b = a;
            g_7090[j].f_094 = g_1e50;
            g_7090[j].f_0ed = 1;
            g_7090[j].f_058 = j;
            g_7090[j].f_098 = g_1e50 + 5000;
            g_7090[j].f_038 = 3;
            g_7090[j].f_0cd = a;
            return 1;
        }
    }
    if (flag)
        return 0;
    fn_14_3eda();
    if (b == 0x15) {
        if (a == g_9646)
            fn_10_744c(0x70);
        else
            fn_10_754a(0x70, 14, a, 1);
    }
    if (c != -1)
        fn_03_06ec(a, 7, 0, c);
    fn_11_238e(g_0a7c, 0);
    if (b == 4)
        fn_14_0000(cls);
    else
        fn_14_0000(b);
    g_0992 += 10;
    fn_14_4074();
    g_1df8[14][g_9316].f_12 = g_1df8[14][g_9316].f_24;
    g_1df8[14][g_9316].f_2e = 0;
    g_1df8[14][g_9316].f_32 = -1;
    g_1df8[14][g_9316].f_36 = -1;
    found = 1;
    s = rand() % g_9318;
    if (g_92e8) {
        int16_t r, dir;
        POINT p;

        r = rand() % (LO16(g_90ea) / 5) + LO16(g_90ea) / 5;
        dir = rand() % 16;
        p.x = g_1050[dir].x * r / 16 + g_1df8[14][g_9646].f_00.x;
        p.y = g_1050[dir].y * r / 16 + g_1df8[14][g_9646].f_00.y;
        g_1df8[14][j].f_04 = fn_08_2bbe(p);
    } else {
        g_1df8[14][g_9316].f_04 = g_1df8[8][s * 2].f_04;
        g_1df8[14][g_9316].f_04.x += g_1df8[8][s * 2].f_22
                                  - g_1df8[14][g_9316].f_22 / 2
                                  + g_6670[s].f_12 / 2;
    }
    g_1df8[14][g_9316].f_18 = 0;
    fn_10_754a(0x27, 14, g_9316, 1);
    fn_12_2556(14, g_9316);
    fn_07_13b2(2, 14, g_9316);
    g_7090[g_9316].f_052 = st;
    g_7090[g_9316].f_054 = 14;
    g_7090[g_9316].f_056 = a;
    g_7090[g_9316].f_032.a = 14;
    g_7090[g_9316].f_032.b = a;
    g_7090[g_9316].f_094 = g_1e50;
    g_7090[g_9316].f_058 = j;
    g_7090[g_9316].f_0ed = 1;
    g_7090[g_9316].f_038 = 3;
    g_96d2[g_7090[g_9316].f_04e].f_42 = 0;
    g_7090[g_9316].f_0cd = a;
    g_964c++;
    if (b == 3) {
        g_7090[g_9316].f_0ed = 0;
        fn_03_06ec(a, 14, g_9316, 0x67);
        g_7090[g_9316].f_062[a] = -300;
        fn_04_8346(g_9316, 14, a, 0xd);
    } else if (b == 4) {
        g_7090[g_9316].f_0ed = 0;
        fn_03_06ec(a, 14, g_9316, 0x68);
        g_7090[g_9316].f_062[a] = 300;
    }
    g_7090[g_9316].f_098 = g_1e50 + 5000;
    g_8e2c = g_1e68;
    return 2;
}
