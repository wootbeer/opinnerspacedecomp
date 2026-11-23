/* INSPACE.EXE segment 3 (selector 1010). */
#include "game.h"

/* 0xad-byte records; lowest field seen at DS:96ea [inferred]. */

/* 3:0000 */
int16_t fn_03_0000(int16_t type, int16_t n)
{
    int16_t unused;

    if (type < 0 || n < 0 || type > g_9324)
        return 0;
    if (g_92ec[type] <= n)
        return 0;
    if (type == 0xe && n != main_ship
        && (g_1df8[type][n].f_18 == 0 || g_7090[n].f_147 != 0))
        return 1;
    if (g_1df8[type][n].f_18 != 0)
        return 0;
    if (type == 0 || type == 7 || type == 1)
        return 1;
    if (type == 2 && (g_52ec[n].f_12 == 0xf
                      || g_52ec[n].f_18.a == 0xe && g_52ec[n].f_18.b == main_ship))
        return 1;
    if (type == 9 || type == 0xb)
        return 1;
    if (type == 8 && g_3d50[n].f_1c == 2 && g_3d50[n].f_0a > 0)
        return 1;
    if (fn_13_371c(type, n) != 2)
        return 0;
    return 1;
}

/* Sets the target (type, k) of object n; for the player's object also
 * builds the target description lines [inferred]. */
/* 3:00f4 */
void fn_03_00f4(int16_t n, int16_t type, int16_t k)
{
    char tmp[30];
    char buf[40];
    char unused[18];

    LO16(g_7090[n].f_03e) = type;
    HI16(g_7090[n].f_03e) = k;
    if (n != main_ship)
        return;
    g_6e38[0].f_1a.b = type;
    g_6e38[0].f_1a.a = k;
    if (!fn_03_0000(type, k) && !fn_13_371c(type, k)) {
        g_9498++;
        return;
    }
    lstrcpy(g_960a, "");
    lstrcpy(g_9628, "");
    if (type == -1) {
        LoadString(g_9212, 0x89d, g_9628, 40);
        LoadString(g_9212, 0x89e, g_8718, 40);
        if (g_0a7c)
            PostMessage(g_0a7c, WM_PAINT, 0, 0L);
        return;
    }
    lstrcpy(g_960a, "");
    lstrcpy(g_9628, "");
    if (type == 14) {
        fn_03_1542(0, type, k, buf, 0);
        if (g_92e8)
            LoadString(g_9212, 0x89f, g_960a, 40);
        else if (g_96d2[g_7090[main_ship].f_04e].f_38
                 == g_96d2[g_7090[k].f_04e].f_38)
            LoadString(g_9212, 0x142, g_960a, 40);
        else
            fn_13_218a(g_96d2[g_7090[k].f_04e].f_38, g_960a);
        fn_17_8e60(k, g_9628);
    } else if (type == 0) {
        lstrcpy(g_9628, g_57a8[k].f_0c);
        fn_03_1542(0, type, k, buf, 0);
        if (g_1df8[0][k].f_53 == 2) {
            LoadString(g_9212, 0x8a0, tmp, 40);
            lstrcat(buf, tmp);
        } else if (g_1df8[0][k].f_53 == 0) {
            LoadString(g_9212, 0x8a1, tmp, 40);
            lstrcat(buf, tmp);
        }
    } else if (type == 1) {
        lstrcpy(g_9628, g_57a8[g_6038[k]].f_0c);
        fn_03_1542(0, type, k, buf, 0);
    } else if (type == 2) {
        fn_03_1542(0, type, k, buf, 0);
        LoadString(g_9212, 0x8a2, tmp, 40);
        lstrcat(buf, tmp);
        if (g_52ec[k].f_18.a == 0) {
            LoadString(g_9212, 0x98, g_960a, 40);
            g_960a[lstrlen(g_960a) - 2] = 0;
            fn_06_0f1a(g_52ec[k].f_18.b, tmp);
            lstrcat(g_960a, tmp);
        } else
            lstrcpy(g_960a, g_96d2[g_7090[g_52ec[k].f_18.b].f_04e].f_70);
    } else if (type == 7) {
        fn_03_1542(0, type, k, buf, 0);
        LoadString(g_9212, 0x8a3, buf, 40);
        LoadString(g_9212, 0x8a4, g_960a, 40);
    } else if (type == 9 || type == 11
               || type == 8 && g_3d50[k].f_1c == 2 && g_3d50[k].f_0a > 0
               || fn_13_371c(type, k))
        fn_03_1542(0, type, k, buf, 0);
    lstrcpy(g_8718, buf);
    if (g_0a7c)
        PostMessage(g_0a7c, WM_PAINT, 0, 0L);
    fn_07_65aa(type, k);
}

/* 3:062e */
void fn_03_062e(int16_t a, int16_t b, int16_t c, int16_t d)
{
    if (a) {
        g_6e38[2].f_1a.b = c;
        g_6e38[2].f_1a.a = d;
    } else
        fn_03_00f4(b, c, d);
}

/* 3:065e */
int16_t fn_03_065e(int16_t a, int16_t b, int16_t c)
{
    if (!fn_03_0000(a, b))
        return 0;
    if (a == 0xe && b == main_ship)
        return 0;
    switch (c) {
    case 1:
        if (a != 0xe)
            return 0;
        goto yes;
    case 4:
        if (a != 2)
            return 0;
        goto yes;
    case 5:
        if (a != 9)
            return 0;
        goto yes;
    case 3:
        if (a == 8 && g_3d50[b].f_1c == 2 && g_3d50[b].f_0a > 0)
            return 1;
        return 0;
    case 0:
    yes:
        return 1;
    case 2:
        if (a == 0)
            goto yes;
        if (a != 0xb)
            return 0;
        goto yes;
    default:
        goto yes;
    }
    return 0;
}

/* Builds the message lines for event kind about target (type, k) of the
 * player's object n [inferred]. */
/* 3:06ec */
void fn_03_06ec(int16_t n, int16_t type, int16_t k, int16_t kind)
{
    char buf[50];
    char pad[40];               /* unused locals: frame layout */
    int16_t i;
    int16_t u1, u2, u3;
    int16_t t;
    int16_t a;
    int16_t u4;
    int16_t b;
    int16_t c;
    int16_t tt;
    int16_t tn;
    int16_t s54;
    int16_t s52;
    int16_t u5, u6, u7, u8, u9;

    if (n != main_ship)
        return;
    if (type == 0xe && k == main_ship)
        return;
    if (kind == 0xb7 && (g_7090[k].f_032.a == 0xc || g_7090[k].f_006 == 0xc))
        return;
    g_6e38[1].f_1a.a = k;
    g_6e38[1].f_1a.b = type;
    if (type == 0xe) {
        tt = g_7090[k].f_054;
        tn = g_7090[k].f_056;
    }
    s54 = g_6e38[0].f_1a.b;
    s52 = g_6e38[0].f_1a.a;
    if (g_0a76 != 3)
        fn_07_119c(3);
    if (g_0a7c)
        fn_11_3e6e();
    if (type == -1) {
        LoadString(g_9212, 0x8a5, g_8740, 40);
        lstrcpy(g_8768, "");
        lstrcpy(g_87b8, "");
        g_870c = g_1e50 + 3000;
        g_9608 = 0;
        return;
    }
    if (type != 0xe && type != 7 && type != 2)
        return;
    fn_03_1542(0, type, k, g_8740, 0);
    t = k;
    if (g_094e) {
        if (type == 7)
            g_870c = g_1e50 + 2500;
        else
            g_870c = g_1e50 + 5000;
    } else
        g_870c = g_1e50 + 7000;
    g_9608 = 0;
    g_1cb2 = k;
    g_1cb0 = kind;
    switch (kind) {
    case 1:
        g_870c = g_1e50 + 9000;
        switch (g_7090[t].f_052) {
        case 1:
            fn_10_744c(0x37);
            fn_10_a332(g_8db0, 0x125, 2);
            break;
        case 5:
            fn_10_744c(0x6d);
            fn_10_a332(g_8db0, 0x127, 2, tt, tn, 5, tt == 0xe && tn == main_ship);
            break;
        case 2:
        case 3:
            fn_10_744c(0x6c);
            if (g_7090[t].f_054 == 9) {
                if (fn_13_2688(t, main_ship) > -50)
                    fn_10_a332(g_8db0, 0x57a, 2);
                else
                    fn_10_a332(g_8db0, 0x57b, 2);
            } else
                fn_10_a332(g_8db0, 0x128, 2, tt, tn, 5, tt == 0xe && tn == main_ship);
            break;
        case 4:
            fn_10_744c(0x6c);
            fn_10_a332(g_8db0, 0x129, 2, tt, tn, 5, tt == 0xe && tn == main_ship);
            break;
        case 7:
            fn_10_a332(g_8db0, 0x16f, 2);
            break;
        case 9:
            fn_10_a332(g_8db0, 0x185, 1, tt, tn, 5);
            break;
        case 12:
            fn_10_a332(g_8db0, 0x1bc, 2);
            break;
        case 13:
            if (g_7090[t].f_056 == t) {
                fn_10_744c(0x44);
                fn_10_a332(g_8db0, 0x1c2, 2);
            } else
                fn_10_a332(g_8db0, 0x2a9, 2);
            break;
        case 10:
            fn_10_744c(0x36);
            fn_10_a332(g_8db0, 0x1aa, 2);
            break;
        }
        break;
    case 2:
    case 52:
        g_870c = 0;
        g_9608 = 1;
        if (kind == 2) {
            a = g_7090[n].f_052;
            b = g_7090[n].f_054;
            c = g_7090[n].f_056;
        } else {
            a = g_964e;
            b = g_9650;
            c = g_9652;
        }
        switch (a) {
        case 2:
        case 3:
        case 4:
            if (b == 0xe && g_7090[c].f_032.a == 0xe && g_7090[c].f_032.b == t
                && g_7090[c].f_038 == 1)
                fn_10_744c(0x34);
            else
                fn_10_744c(0x40);
            if (g_7090[n].f_054 == 9)
                fn_10_a332(g_8db0, 0xbcb, 2);
            else
                fn_10_a332(g_8db0, 0x12e, 2, b, c, 5);
            break;
        case 5:
            fn_10_744c(0x34);
            fn_10_a332(g_8db0, 0x12f, 2, b, c, 5);
            break;
        case 1:
            fn_10_744c(0x34);
            fn_10_a332(g_8db0, 0xbcc, 2, (LPSTR)g_380c);
            break;
        case 9:
            fn_10_a332(g_8db0, 0x184, 2, b, c, 5);
            break;
        case 10:
            fn_10_a332(g_8db0, 0x1ac, 2);
            break;
        case 12:
            fn_10_a332(g_8db0, 0x1ba, 2);
            break;
        }
        break;
    case 19:
        switch (g_7090[t].f_052) {
        case 1:
            fn_10_744c(0x44);
            fn_10_a332(g_8db0, 0x156, 2);
            break;
        case 2:
        case 3:
        case 4:
            fn_10_744c(0x44);
            fn_10_a332(g_8db0, 0x158, 2, tt, tn, 5);
            break;
        case 5:
            fn_10_744c(0x44);
            fn_10_a332(g_8db0, 0x159, 2, tt, tn, 0);
            break;
        case 6:
            fn_10_744c(0x6b);
            fn_10_a332(g_8db0, 0x159, 2, tt, tn, 5);
            break;
        case 9:
            fn_10_a332(g_8db0, 0x183, 2, tt, tn, 5);
            break;
        case 10:
            fn_10_a332(g_8db0, 0x1a8, 2);
            break;
        case 12:
            fn_10_a332(g_8db0, 0x1be, 2);
            break;
        }
        break;
    case 3:
        switch (g_7090[n].f_052) {
        case 1:
            fn_10_744c(0x3b);
            fn_10_a332(g_8db0, 0x12c, 2, (LPSTR)g_380c);
            break;
        case 2:
        case 3:
        case 4:
            fn_10_744c(0x3b);
            fn_10_a332(g_8db0, 0x186, 2, (LPSTR)g_380c);
            break;
        case 9:
            fn_10_744c(0x66);
            fn_10_a332(g_8db0, 0x198, 2, tt, tn, 5);
            break;
        }
        break;
    case 4:
        fn_10_a332(g_8db0, 0x148, 2, s54, s52, 5);
        break;
    case 100:
        fn_10_a332(g_8db0, 0x148, 2, (LPSTR)g_380c);
        break;
    case 24:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x173, 2);
        break;
    case 5:
        fn_10_a332(g_8db0, 0x14b, 2, s54, s52, 5);
        break;
    case 6:
        fn_10_a332(g_8db0, 0x149, 2);
        break;
    case 14:
        fn_10_a332(g_8db0, 0x14c, 2, (LPSTR)g_380c);
        break;
    case 15:
        fn_10_a332(g_8db0, 0x14e, 2, 0x14e);
        break;
    case 20:
        fn_10_a332(g_8db0, 0x14e, 2, s54, s52, 2);
        break;
    case 16:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x154, 2);
        break;
    case 17:
        fn_10_a332(g_8db0, 0x150, 2, g_380c);   /* near pointer (sic) */
        break;
    case 18:
        fn_10_a332(g_8db0, 0x152, 2);
        break;
    case 22:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x164, 2);
        break;
    case 21:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x166, 2);
        break;
    case 23:
        fn_10_a332(g_8db0, 0x168, 2, g_7090[main_ship].f_006, g_7090[main_ship].f_008, 5);
        break;
    case 7:
        fn_10_744c(0x33);
        fn_10_a332(g_8db0, 0x6e, 2, (LPSTR)g_380c);
        break;
    case 132:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x470, 2);
        break;
    case 8:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x15c, 2);
        break;
    case 9:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x79, 2);
        break;
    case 13:
        if (g_1cb4 < g_1e50) {
            g_1cb4 = g_1e50 + 4000;
            fn_10_744c(0x67);
        }
        fn_10_a332(g_8db0, 0x15e, 2, (LPSTR)g_380c);
        break;
    case 10:
    case 11:
    case 12:
        fn_10_744c(0x6e);
        if (kind == 10)
            fn_10_744c(0x2d);
        else
            fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x86, 2, kind + 0x75, kind == 10, 0x207, 0x87,
                   LO16(g_90ea) > 700);
        break;
    case 82:
    case 83:
        fn_10_a332(g_8db0, 0x205, 2, kind + 0x2e);
        break;
    case 84:
        fn_10_a332(g_8db0, 0x8a, 2, (LPSTR)g_380c);
        break;
    case 31:
        fn_10_a332(g_8db0, 0x181, 2);
        break;
    case 25:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x175, 2);
        break;
    case 26:
        fn_10_a332(g_8db0, 0x177, 2);
        break;
    case 30:
        fn_10_a332(g_8db0, 0x17d, 2, 0xe, main_ship, 0);
        break;
    case 29:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x17b, 2);
        break;
    case 27:
        fn_10_a332(g_8db0, 0x17f, 2);
        break;
    case 28:
        fn_10_a332(g_8db0, 0x179, 2);
        break;
    case 32:
        fn_10_a332(g_8db0, 0x188, 2, tt, tn, 5);
        break;
    case 33:
        fn_10_a332(g_8db0, 0x18a, 2, tt, tn, 5);
        break;
    case 34:
        fn_10_a332(g_8db0, 0x18c, 2, tt, tn, 5);
        break;
    case 85:
        if (g_9602 == 0) {
            fn_06_1010(g_9604, 100, 2, buf);
            fn_10_a332(g_8db0, 0x23e, 2, (LPSTR)buf);
        } else
            fn_10_a332(g_8db0, 0x23f, 2, g_9602, 0x9e2);
        break;
    case 86:
        fn_06_1010(g_9604, 100, 2, buf);
        fn_10_a332(g_8db0, 0x2a8, 2, (LPSTR)buf);
        break;
    case 181:
        fn_10_a332(g_8db0, 0x798, 2);
        break;
    case 35:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x18e, 2, s54, s52, 5);
        break;
    case 36:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x190, 2, s54, s52, 2);
        break;
    case 37:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x191, 2, s54, s52, 2);
        break;
    case 113:
        fn_10_a332(g_8db0, 0x429, 2);
        break;
    case 38:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x194, 2);
        break;
    case 39:
        fn_10_a332(g_8db0, 0x196, 2);
        break;
    case 48:
        fn_10_a332(g_8db0, 0x199, 2);
        break;
    case 41:
    case 42:
    case 43:
        fn_10_a332(g_8db0, kind + 0x172, 2);
        break;
    case 45:
        fn_10_a332(g_8db0, kind + 0x171, 2);
        break;
    case 51:
        fn_10_a332(g_8db0, 0x1b2, 2, s54, s52, 5);
        break;
    case 50:
        fn_10_a332(g_8db0, 0x1ae, 2);
        break;
    case 49:
        fn_10_a332(g_8db0, 0x1b0, 2);
        break;
    case 71:
        fn_10_a332(g_8db0, 0x28a, 2);
        break;
    case 55:
        fn_10_a332(g_8db0, 0x1b8, 2);
        break;
    case 54:
        fn_10_a332(g_8db0, 0x1b4, 2);
        break;
    case 53:
        fn_10_a332(g_8db0, 0x1b6, 2);
        break;
    case 56:
        fn_10_a332(g_8db0, 0x1c0, 2);
        break;
    case 57:
        fn_10_a332(g_8db0, 0x1c4, 2);
        break;
    case 64:
        fn_10_a332(g_8db0, 0x22b, 2);
        break;
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 65:
    case 66:
    case 67:
    case 68:
    case 87:
    case 88:
        switch (rand() % 4) {
        case 0:
            fn_10_744c(0x3d);
            break;
        case 1:
            fn_10_744c(0x3e);
            break;
        case 2:
            fn_10_744c(0x3f);
            break;
        }
        fn_10_a332(g_8db0, kind + 0x1eb, 2);
        break;
    case 92:
        fn_10_a332(g_8db0, 0x3b6, 2);
        break;
    case 69:
        fn_10_a332(g_8db0, 0x23a, 2);
        break;
    case 192:
        fn_10_a332(g_8db0, 0x3c4, 2);
        break;
    case 70:
        fn_10_a332(g_8db0, 0x23c, 2);
        break;
    case 93:
        fn_10_a332(g_8db0, 0x3c0, 2);
        break;
    case 101:
        fn_10_a332(g_8db0, 0x3c1, 2);
        break;
    case 134:
        fn_10_a332(g_8db0, 0x3c2, 2);
        break;
    case 185:
        fn_10_a332(g_8db0, 0x3c3, 2);
        break;
    case 135:
        fn_10_a332(g_8db0, 0x58f, 2);
        break;
    case 72:
        fn_10_744c(0x67);
        fn_10_a332(g_8db0, 0x28c, 2);
        break;
    case 73:
        fn_10_a332(g_8db0, 0x28e, 2, g_7090[k].f_032.a, g_7090[k].f_032.b, 0);
        break;
    case 74:
        fn_10_a332(g_8db0, 0x28f, 2);
        break;
    case 75:
        fn_10_a332(g_8db0, 0x291, 2);
        break;
    case 76:
        fn_10_a332(g_8db0, 0x293, 2);
        break;
    case 77:
        fn_10_a332(g_8db0, 0x295, 2);
        break;
    case 78:
        fn_10_a332(g_8db0, 0x297, 2);
        break;
    case 81:
        fn_10_744c(0x3b);
        fn_10_a332(g_8db0, 0x299, 2);
        break;
    case 79:
        fn_10_744c(0x3b);
        fn_03_3498(g_8d38, g_8768, g_87b8);
        break;
    case 80:
        fn_10_744c(0x3f);
        fn_03_3498(g_8d38, g_8768, g_87b8);
        break;
    case 89:
        fn_10_744c(0x36);
        fn_10_a332(g_8db0, 0x2ab, 2);
        break;
    case 90:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x2ad, 2);
        break;
    case 91:
        fn_10_a332(g_8db0, 0x2af, 2, 4, 0x2b0, (LPSTR)g_380c);
        break;
    case 112:
        fn_10_a332(g_8db0, 0x428, 2, 4, 0x2b0, (LPSTR)g_380c);
        break;
    case 94:
        fn_10_a332(g_8db0, 0x2b4, 2, 4, 0x2b0, (LPSTR)g_380c);
        break;
    case 99:
        fn_10_a332(g_8db0, 0x422, 2);
        break;
    case 95:
        fn_10_a332(g_8db0, 0x41a, 2);
        break;
    case 137:
        fn_10_a332(g_8db0, 0x591, 2);
        break;
    case 96:
        fn_10_a332(g_8db0, 0x41c, 2, 0xe, g_7090[k].f_008, 5);
        break;
    case 97:
        fn_10_a332(g_8db0, 0x41e, 2, 0xe, g_7090[k].f_008, 5);
        break;
    case 98:
        fn_10_a332(g_8db0, 0x41e, 2, g_7090[k].f_006, g_7090[k].f_008, 2);
        break;
    case 102:
        fn_10_a332(g_8db0, 0x2b5, 2, g_7090[k].f_032.a, g_7090[k].f_032.b, 5);
        break;
    case 103:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x2b7, 2);
        break;
    case 182:
        fn_10_a332(g_8db0, 0x25b, 2);
        break;
    case 104:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x2b9, 2);
        break;
    case 106:
        fn_10_744c(0x37);
        fn_10_a332(g_8db0, 0x2bf, 2);
        break;
    case 105:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x2bb, 2);
        break;
    case 108:
        fn_10_a332(g_8db0, 0x2c1, 2);
        break;
    case 107:
        fn_10_744c(0x30);
        fn_10_a332(g_8db0, 0x2bd, 2);
        break;
    case 110:
        fn_10_744c(0x30);
        fn_10_a332(g_8db0, 0x2c3, 2);
        break;
    case 109:
        fn_10_744c(0x2c);
        fn_10_a332(g_8db0, 0x2da, 2);
        break;
    case 111:
        fn_13_218a(g_96d2[g_7090[k].f_04e].f_38, buf);
        fn_10_a332(g_8db0, 0x426, 2, (LPSTR)buf);
        break;
    case 115:
        fn_10_744c(0x34);
        fn_10_a332(g_8db0, 0x579, 2);
        break;
    case 116:
        fn_10_a332(g_8db0, 0x580, 2);
        break;
    case 117:
        fn_10_744c(0x3b);
        fn_10_a332(g_8db0, 0x581, 2);
        break;
    case 118:
        fn_10_744c(0x3b);
        fn_10_a332(g_8db0, 0x582, 2);
        break;
    case 119:
        fn_10_744c(0x3b);
        if (g_7090[main_ship].f_032.a == 0xe)
            fn_10_a332(g_8db0, 0x583, 2);
        else
            fn_10_a332(g_8db0, 0x584, 2);
        break;
    case 127:
        fn_10_744c(0x3f);
        fn_10_a332(g_8db0, 0x588, 2);
        break;
    case 128:
        fn_10_a332(g_8db0, 0x589, 2);
        break;
    case 129:
        fn_10_a332(g_8db0, 0x58a, 2);
        break;
    case 130:
        fn_10_a332(g_8db0, 0x58b, 2);
        break;
    case 136:
        fn_10_a332(g_8db0, 0x590, 2);
        break;
    case 138:
        fn_10_744c(0x44);
        fn_10_a332(g_8db0, 0x592, 2);
        break;
    case 141:
        fn_10_744c(0x3c);
        fn_10_a332(g_8db0, 0x73c, 2,
                   (int16_t)((g_7090[k].f_098 - g_1e50) / 1000));
        break;
    case 139:
        fn_10_a332(g_8db0, 0x73a, 2, 4, 0, 0);
        break;
    case 140: case 142: case 143: case 144: case 145: case 146: case 147:
    case 148: case 149: case 150: case 151: case 152: case 153: case 154:
    case 155: case 156: case 157: case 158: case 159: case 160: case 161:
    case 162: case 163:
        fn_10_a332(g_8db0, kind + 0x6af, 2);
        break;
    case 164:
        fn_10_744c(0x30);
        fn_10_a332(g_8db0, 0x593, 2);
        break;
    case 165: case 166: case 167: case 168: case 169: case 170: case 171:
    case 172: case 173:
        fn_10_a332(g_8db0, kind + 0x6c7, 2);
        break;
    case 175: case 176: case 177: case 178:
        fn_10_a332(g_8db0, kind + 0x6d1, 2);
        break;
    case 179:
        fn_10_a332(g_8db0, 0x784, 2, 4, 0, 0);
        break;
    case 174:
        fn_10_a332(g_8db0, 0x794, 2);
        break;
    case 180:
        fn_10_a332(g_8db0, 0x796, 2);
        break;
    case 186:
        fn_10_a332(g_8db0, 0x78a, 2);
        break;
    case 187:
        fn_10_a332(g_8db0, 0x78c, 2);
        break;
    case 188:
        fn_10_a332(g_8db0, 0x79c, 2, 4, 0, 2);
        break;
    case 189:
        fn_10_a332(g_8db0, 0x7d0, 2, tt, tn, 5);
        break;
    case 190:
        fn_10_a332(g_8db0, 0x7d5, 2);
        break;
    case 191:
        fn_10_a332(g_8db0, 0x7d2, 2);
        break;
    case 183:
        fn_10_744c(0x36);
        fn_10_a332(g_8db0, 0x1aa, 2);
        break;
    case 184:
        fn_10_a332(g_8db0, 0x1aa, 2, (int16_t)g_7090[k].f_148,
                   (int16_t)g_7090[k].f_149, 5);
        break;
    }
    if (LO16(g_90ea) > 0x27b) {
        for (i = 0; i < lstrlen(g_8768); i++)
            if (g_8768[i] < '{' && g_8768[i] > '`')
                g_8768[i] -= 0x20;
        for (i = 0; i < lstrlen(g_87b8); i++)
            if (g_87b8[i] < '{' && g_87b8[i] > '`')
                g_87b8[i] -= 0x20;
    }
}

/* Writes the name of object (type, n) into buf, with an article chosen
 * by mode; a != 0 adds the pilot name and upper-cases it [inferred]. */
/* 3:1542 */
void fn_03_1542(int16_t a, int16_t type, int16_t n, LPSTR buf, int16_t mode)
{
    char num[40];
    char art[10];
    int16_t i;
    int16_t g;
    int16_t an;
    int16_t off;

    g = -1;
    off = an = 0;
    if (mode == 7) {
        off = 10000;
        mode = 5;
        g = 4;
    }
    if (mode == 5 && g_967a != 0)
        mode = 1;
    if (type == 14) {
        lstrcpy(buf, g_96d2[g_7090[n].f_04e].f_70);
        if (mode == 5)
            mode = 1;
        if (LO8(g_96d2[g_7090[n].f_04e].f_44) & 0x20)
            g = 0;
        else
            g = 2;
    } else if (type == 0) {
        if (mode == 2)
            mode = 5;
        LoadString(g_9212, 0x98, buf, 40);
        if (buf[lstrlen(buf) - 1] == 'M')
            g = 0;
        else if (buf[lstrlen(buf) - 1] == 'F')
            g = 2;
        else if (buf[lstrlen(buf) - 1] == 'N')
            g = 6;
        buf[lstrlen(buf) - 2] = 0;
        fn_06_0f1a(n, num);
        lstrcat(buf, num);
        if (a) {
            lstrcat(buf, " (");
            lstrcat(buf, g_57a8[n].f_0c);
            lstrcat(buf, ")");
        }
    } else if (type == 1)
        LoadString(g_9212, 0x37c, buf, 40);
    else if (type == 7)
        LoadString(g_9212, 0x15b, buf, 40);
    else if (type == 2) {
        if (mode == 1 || mode == 5)
            mode = 2;
        LoadString(g_9212, 0x9a, buf, 40);
    } else if (type == 9) {
        LoadString(g_9212, off + 0xaa, buf, 40);
        if (off == 0) {
            g = fn_03_1ae6(buf);
            if (mode == 1 || mode == 5)
                mode = 2;
        }
    } else if (fn_13_371c(type, n)) {
        LoadString(g_9212, 0x249, buf, 40);
        if (mode == 5)
            mode = 1;
    } else if (type == 3) {
        LoadString(g_9212, off + 0x99, buf, 40);
        if (off == 0) {
            g = fn_03_1ae6(buf);
            if (mode == 1 || mode == 5)
                mode = 2;
        }
    } else if (type == 4) {
        switch (g_9214) {
        case 0:
            LoadString(g_9212, 0x9b, buf, 40);
            break;
        case 1:
            LoadString(g_9212, 0xeb, buf, 40);
            break;
        case 2:
            LoadString(g_9212, 0xec, buf, 40);
            break;
        case 3:
            if (g_1df8[type][n].f_26 == 0)
                LoadString(g_9212, 0xed, buf, 40);
            else
                LoadString(g_9212, 0xee, buf, 40);
            break;
        case 4:
            if (g_1df8[type][n].f_26 == 0)
                LoadString(g_9212, 0xf1, buf, 40);
            else
                LoadString(g_9212, 0xf2, buf, 40);
            break;
        }
        g = fn_03_1ae6(buf);
    } else if (type == 8 && g_3d50[n].f_1c == 2) {
        LoadString(g_9212, g_4d90[g_3d50[n].f_30].f_12 + off, buf, 40);
        if (off == 0) {
            if (mode == 1 || mode == 5)
                mode = 2;
        }
    } else if (type == 8) {
        if (off == 0) {
            if (mode == 1 || mode == 5)
                mode = 2;
        }
        if (g_3d50[n].f_1c == 3)
            LoadString(g_9212, off + 0x16a, buf, 40);
        else if (g_3d50[n].f_1c == 1)
            LoadString(g_9212, off + 0x16b, buf, 40);
    } else if (type == 5) {
        if (mode == 1 || mode == 5)
            mode = 2;
        if (g_1df8[type][n].f_44 == 0x78)
            LoadString(g_9212, 0x1ec, buf, 40);
        else if (g_1df8[type][n].f_44 == 0xc8)
            LoadString(g_9212, 0x1ed, buf, 40);
    } else if (type == 6 && g_6670[n + 4].f_04.x > 0
               && g_2f4c[g_6670[n + 4].f_04.x].f_08 != -1) {
        LoadString(g_9212, g_2f4c[g_6670[n + 4].f_04.x].f_08 + 10000, buf, 40);
        if (mode == 1 || mode == 5)
            mode = 2;
    } else if (type == 11)
        LoadString(g_9212, 0x39e, buf, 40);
    else {
        LoadString(g_9212, 0xa9, buf, 40);
        fn_06_0f1a(type, num);
        lstrcat(buf, num);
    }
    switch (buf[0]) {
    case 'A': case 'E': case 'I': case 'O': case 'U':
    case 'a': case 'e': case 'i': case 'o': case 'u':
        an = 1;
    }
    if (g == -1)
        g = fn_03_1ae6(buf);
    if (mode == 1)
        LoadString(g_9212, an + g + 0xa8c, art, 40);
    else if (mode == 2)
        LoadString(g_9212, an + g + 0xaa0, art, 40);
    else if (mode == 6)
        LoadString(g_9212, an + g + 0xac8, art, 40);
    else if (mode == 3)
        LoadString(g_9212, an + g + 0xab4, art, 40);
    else
        art[0] = 0;
    if (a) {
        if (buf[lstrlen(buf) - 1] == ' ')
            buf[lstrlen(buf) - 1] = 0;
        for (i = 0; i < lstrlen(buf); i++)
            if (buf[i] < 0x7b && buf[i] > 0x60)
                buf[i] -= 0x20;
    }
    if (mode && art[0]) {
        for (i = lstrlen(buf); i >= 0; i--)
            buf[i + lstrlen(art)] = buf[i];
        for (i = 0; i < lstrlen(art); i++)
            buf[i] = art[i];
    }
}

/* 3:1ae6 */
int16_t fn_03_1ae6(LPSTR s)
{
    int16_t r;

    r = -1;
    if (s[lstrlen(s) - 1] == 'M')
        r = 0;
    else if (s[lstrlen(s) - 1] == 'F')
        r = 2;
    else if (s[lstrlen(s) - 1] == 'N')
        r = 6;
    else if (s[lstrlen(s) - 1] == 'P')
        r = 4;
    if (r != -1)
        s[lstrlen(s) - 2] = 0;
    else
        r = 6;
    return r;
}

/* 3:31d0 */
void fn_03_31d0(int16_t mode, LPSTR a, LPSTR b)
{
    int16_t i;

    if (b[0] == '.') {
        lstrcat(a, ".");
        for (i = 1; i < lstrlen(b); i++)
            b[i - 1] = b[i];
        b[lstrlen(b) - 1] = 0;
    }
    if (b[0] == 0 && a[lstrlen(a) - 1] != '.' && a[lstrlen(a) - 1] != '!')
        lstrcat(a, ".");
    switch (mode) {
    case 2:
        lstrcpy(g_8db0, a);
        lstrcat(g_8db0, " ");
        lstrcat(g_8db0, b);
        fn_03_3498(g_8db0, g_8768, g_87b8);
        break;
    case 3:
        fn_11_3fd4(a, 1);
        fn_11_3fd4(b, 1);
        lstrcpy(g_8694, a);
        lstrcpy(g_86d0, b);
        break;
    case 0:
    case 1:
        lstrcpy(g_8630, a);
        if (mode == 1) {
            lstrcat(g_8630, " ");
            lstrcat(g_8630, b);
        }
        break;
    }
}

/* 3:332e */
void fn_03_332e(int16_t a, int16_t b)
{
    char buf[40];

    lstrcpy(g_8630, g_380c);
    lstrcat(g_8630, ": ");
    LoadString(g_9212, a, buf, 40);
    lstrcat(g_8630, buf);
    LoadString(g_9212, b, buf, 40);
    lstrcat(g_8630, buf);
    g_058c = 1;
    g_05c0 = g_1e50 + 1200;
}

/* 3:3498 */
void fn_03_3498(LPSTR s, LPSTR a, LPSTR b)
{
    int16_t half;
    int16_t i;

    s[0x4e] = 0;
    half = lstrlen(s) / 2;
    for (i = 0; i < half; i++) {
        if (s[half + i] == ' ') {
            half += i + 1;
            break;
        }
        if (s[half - i] == ' ') {
            half += 1 - i;
            break;
        }
    }
    lstrcpy(a, s);
    if (i < half) {
        a[half] = 0;
        lstrcpy(b, s + half);
    } else
        b[0] = 0;
}

/* 3:33b4 */
void fn_03_33b4(int16_t id)
{
    char buf[40];

    switch (id) {
    case 2:
        if (g_7090[main_ship].f_054 == 9)
            LoadString(g_9212, 0x578, buf, 40);
        else
            fn_03_1542(0, g_7090[main_ship].f_054, g_7090[main_ship].f_056, buf, 0);
        g_05c0 = g_1e50 + 1200;
        fn_10_a332(g_8630, 0x57c, g_058c = 1, (LPSTR)buf);
        break;
    case 1:
        fn_10_a332(g_8630, 0x57d, 1, (LPSTR)buf);
        g_058c = 1;
        g_05c0 = g_1e50 + 1200;
        break;
    case 3:
    case 9:
        fn_10_a332(g_8630, id, 1, g_7090[main_ship].f_054, g_7090[main_ship].f_056, 5);
        g_058c = 1;
        g_05c0 = g_1e50 + 1200;
        break;
    }
}

/* Pick a target for ship n's order [inferred]. */
/* 3:1b8a */
void fn_03_1b8a(int16_t a, int16_t n)
{
    int16_t target;
    int16_t t;
    int16_t kind;
    int16_t i;
    int16_t j;
    int16_t best;
    int16_t bestscore;
    int16_t score;

    target = t = -1;
    kind = LO16(g_7090[n].f_03e);
    if (a && kind != 2) {
        for (i = 0; i < g_9406[2]; i++) {
            if (g_52ec[i].f_18.a == 0xe && g_52ec[i].f_18.b == n
                && g_1df8[2][i].f_18 == 0) {
                kind = 2;
                t = i;
                break;
            }
        }
    }
    if (t == -1 && (kind == 0xe || kind == 2))
        t = HI16(g_7090[n].f_03e);
    if (t > -1)
        target = t;
    if (target == -1) {
        best = -1;
        j = bestscore = 0;
        for (; j <= g_9316; j++) {
            if (j == n)
                continue;
            score = fn_13_2688(j, n) + 0x3c;
            score += g_7090[j].f_05d * 0x32;
            if (g_96d2[g_7090[n].f_04e].f_38 == g_96d2[g_7090[j].f_04e].f_38)
                score += 300;
            if (g_6e38[1].f_1a.b == 0xe && j == g_6e38[1].f_1a.a)
                score += 100;
            if (score > bestscore) {
                best = j;
                bestscore = score;
            }
        }
        if (best >= 0)
            target = best;
    }
    if (target == -1)
        fn_03_06ec(n, 7, 0, 100);
    else {
        if (kind == 0xe)
            fn_03_1d0a(n, target, 2);
        else
            describe_defender_order_message(n, target, 2);
        fn_03_06ec(n, kind, target, 0x3a);
    }
}

/* Builds the two status lines about object o (its order and state) as seen
 * by object me and shows them with fn_03_31d0 [inferred]. */
/* 3:1d0a */
void fn_03_1d0a(int16_t me, int16_t o, int16_t mode)
{
    int16_t tt;
    int16_t tn;
    int16_t i;
    int16_t unused;
    int16_t id;
    char name[40];
    char pre[40];
    char s1[60];
    char line1[60];
    char line2[60];
    int16_t sz;
    int16_t mood;
    int16_t cnt;                    /* also a found index and a loop counter */
    char tmp[40];               /* its first word also serves as a flag */

    tt = g_7090[o].f_032.a;
    tn = g_7090[o].f_032.b;
    if (tt != 0xe || tn != me || o == main_ship && g_9134 && flow_interactive)
        fn_03_1542(1, tt, tn, name, 5);
    else
        LoadString(g_9212, 0x1c8, name, 40);
    if (o != main_ship || !flow_interactive || g_9460)
        LoadString(g_9212, 0x43b, pre, 40);
    else
        LoadString(g_9212, 0x43a, pre, 40);
    if (tt == 3)
        fn_03_1542(1, tt, tn, name, 0);
    lstrcpy(line1, pre);
    id = -1;
    if (o == g_952e && g_9e49 >= 0 && g_9e49 < 9) {
        if (g_9e49 >= 6 || g_1e88 == 0 && g_1df8[7]->f_18 != 0) {
            LoadString(g_9212, 0x46e, s1, 40);
            LoadString(g_9212, 0x46f, line2, 40);
        } else if (g_7090[o].f_147) {
            LoadString(g_9212, 0x442, s1, 40);
            LoadString(g_9212, 0x443, line2, 40);
        } else if (g_7090[o].f_026[0] + g_7090[o].f_026[1] + g_7090[o].f_026[2] < 100) {
            LoadString(g_9212, 0x1e8, s1, 40);
            if (me == 100)
                LoadString(g_9212, 0x460, line2, 40);
            else
                LoadString(g_9212, 0x1e9, line2, 40);
        } else {
            LoadString(g_9212, 0x46c, s1, 40);
            LoadString(g_9212, 0x46d, line2, 40);
        }
    } else if (g_9320 == 6 && g_96d2[g_7090[o].f_04e].f_38 != 7) {
        if (!g_9eb4)
            LoadString(g_9212, 0x43e, s1, 40);
        else if (g_9eb5)
            LoadString(g_9212, 0x440, s1, 40);
        else if (g_1df8[14][o].f_51)
            LoadString(g_9212, 0x43f, s1, 40);
        else if (o == main_ship) {
            LoadString(g_9212, 0x441, s1, 40);
            fn_06_0f1a(g_7090[o].f_148, line2);
            lstrcat(s1, line2);
        } else {
            LoadString(g_9212, 0x43b, s1, 40);
            if (g_8e08[o] == 1000000L)
                LoadString(g_9212, 0x437, s1, 40);
            else if (g_8e08[o] == -50000L)
                LoadString(g_9212, 0x438, s1, 40);
            else if (g_8e08[o] == 50000L)
                LoadString(g_9212, 0x439, s1, 40);
            else {
                if (g_8e08[o] < 0) {
                    fn_11_4928(1, abs32(g_8e08[o]), line1);
                    lstrcat(s1, line1);
                    LoadString(g_9212, 0x43c, line1, 40);
                } else {
                    LoadString(g_9212, 0x43d, line1, 40);
                    lstrcat(s1, line1);
                    fn_11_4928(1, abs32(g_8e08[o]), line1);
                }
                lstrcat(s1, line1);
            }
            lstrcpy(line1, "");
            lstrcpy(line2, "");
            pre[0] = 0;
        }
        if (pre[0])
            line2[0] = 0;
    } else {
        switch (g_7090[o].f_038) {
        case 1:
            fn_10_a332(s1, 0x1c9, 1, (LPSTR)name);
            if (!flow_interactive && g_7090[o].f_0a4 + 14000 < g_1e50
                && g_7090[o].f_0a4 + 19000 > g_1e50)
                id = 0x467;
            else if (!flow_interactive && g_7090[o].f_0a4 + 19000 < g_1e50
                     && (g_7090[o].f_052 == 0
                         || g_7090[o].f_098 < g_1e50 && g_7090[o].f_052 != 4
                            && g_7090[o].f_052 != 1)) {
                id = 0x468;
                if (g_9320 == 7) {
                    for (i = 0; i <= g_9316; i++)
                        if (i != o && g_7090[o].f_056 != i
                            && !g_1df8[14][i].f_18) {
                            g_7090[o].f_056 = i;
                            g_7090[o].f_0a4 = g_1e50;
                            break;
                        }
                    if (g_9316 - i + 1 == 0) {
                        g_7090[o].f_094 = 0;
                        g_7090[o].f_052 = -1;
                        if (o != main_ship || !flow_interactive)
                            fn_04_0078(o);
                    }
                } else {
                    if (g_7090[o].f_032.a == 0xe) {
                        g_7090[o].f_062[g_7090[o].f_032.b] /= 2;
                        g_7090[o].f_0c2[g_7090[o].f_032.b] = -1;
                    }
                    g_7090[o].f_094 = 0;
                    g_7090[o].f_052 = -1;
                    if (o != main_ship || !flow_interactive)
                        fn_04_0078(o);
                }
            } else if (g_7090[o].f_146 == 0xd) {
                if (tn == me)
                    id = 0x1f0;
                else
                    id = 0x1f1;
            } else if (g_7090[o].f_052 >= 2 && g_7090[o].f_052 <= 4
                       && (o != main_ship || !flow_interactive) || g_9320 == 7) {
                if (g_7090[o].f_058 == o) {
                    if (mode == 3 && g_7090[o].f_054 == 0xe
                        && g_7090[o].f_056 == main_ship) {
                        sz = mood = cnt = 0;
                        for (i = 0; i <= g_9316; i++)
                            if (i != me && !g_1df8[14][i].f_18
                                && g_7090[i].f_054 == 0xe
                                && g_7090[i].f_056 == me) {
                                sz += g_7090[i].f_026[0];
                                mood += g_7090[i].f_13e[me];
                                cnt++;
                                if (i == o) {
                                    sz += g_7090[i].f_026[0];
                                    mood += g_7090[i].f_13e[me];
                                    cnt++;
                                } else if (!g_7090[i].flag)
                                    sz = -100;
                            }
                        if (cnt == 0)
                            cnt = 1;
                        sz /= cnt;
                        mood /= cnt;
                        if (g_9682 < 3 && g_9680 < 3)
                            id = 0x6c7;
                        else if (sz < 0) {
                            if (g_7090[o].f_05d < 2)
                                id = 0x6c8;
                            else
                                id = 0x6ca;
                        } else if (!g_7090[o].flag)
                            id = 0x6c9;
                        else if (!g_7090[me].flag) {
                            if (me == g_8560[0].f_0a && g_8560[0].f_02 <= 0)
                                id = 0x6d1;
                            else if (g_7090[o].f_05e == 3)
                                id = 0x6d0;
                            else if (g_96d2[g_7090[o].f_04e].f_38 == 3)
                                id = 0x6cf;
                            else if (g_7090[o].f_026[0] > 0x41)
                                id = 0x6d2;
                            else if (!g_7090[o].f_05e)
                                id = 0x6d3;
                            else if (g_7090[o].f_05d < 2)
                                id = 0x6cc;
                            else if (LO8(g_93b6) != -1)
                                id = 0x6cd;
                            else if (g_91f8 & 1)
                                id = 0x6cb;
                            else
                                id = 0x6ce;
                        } else if (g_7090[me].f_026[0] * 3 / 4 < sz) {
                            if (LO16(g_8e04) > LO16(g_8e00)) {
                                if (mood > 2 && LO16(g_8e04) > 0x50) {
                                    if (g_7090[o].f_05e < 2)
                                        id = 0x6ae;
                                    else
                                        id = 0x6af;
                                } else if (LO16(g_8e00) > 0x78 && mood < -2
                                           && g_1e68 > 900) {
                                    id = 0x6b0;
                                } else if (g_7090[o].f_05e < 2)
                                    id = 0x6b1;
                                else
                                    id = 0x6b2;
                            } else if (LO16(g_8e00) * 3 / 5 < LO16(g_8e04)) {
                                if (mood > 1) {
                                    if (g_7090[o].f_05e < 2)
                                        id = 0x6b3;
                                    else
                                        id = 0x6b4;
                                } else if (mood < -2)
                                    id = 0x6b5;
                                else if (g_7090[o].f_05e < 2)
                                    id = 0x6b7;
                                else
                                    id = 0x6b6;
                            } else if (g_7090[me].f_026[0] < sz)
                                id = 0x6b8;
                            else if (mood > 2) {
                                if (g_7090[o].f_05e < 2)
                                    id = 0x6b3;
                                else
                                    id = 0x6b4;
                            } else
                                id = 0x6b9;
                        } else if (LO16(g_8e00) * 3 / 4 < LO16(g_8e04)
                                   && g_7090[me].f_026[0] / 2 < sz) {
                            if (mood > 1) {
                                if (g_7090[o].f_05e < 2)
                                    id = 0x6ba;
                                else
                                    id = 0x6b4;
                            } else if (mood < -2)
                                id = 0x6b5;
                            else if (g_7090[o].f_05e < 2)
                                id = 0x6bb;
                            else
                                id = 0x6bc;
                        } else if (LO16(g_8e00) / 3 > LO16(g_8e04)) {
                            if (g_7090[o].f_05e < 2)
                                id = 0x6bd;
                            else if (mood < -2 && sz < 0x23) {
                                if (g_7090[o].f_05e < 2)
                                    id = 0x6be;
                                else
                                    id = 0x6bf;
                            } else
                                id = 0x6c0;
                        } else if (mood > 1) {
                            if (g_7090[o].f_05e < 2)
                                id = 0x6c2;
                            else
                                id = 0x6c3;
                        } else if (mood < -2 && sz < 0x1e) {
                            if (g_7090[o].f_05e < 2)
                                id = 0x6c1;
                            else
                                id = 0x6bf;
                        } else
                            id = 0x6c4;
                    } else if (g_7090[o].f_146 == 0x14) {
                        if (g_7090[o].f_032.a == 0xe && g_7090[o].f_032.b == me)
                            id = 0x6c5;
                        else
                            id = 0x6ab;
                    } else if (g_7090[o].f_146 == 0x15) {
                        if (g_7090[o].f_032.a == 0xe && g_7090[o].f_032.b == me)
                            id = 0x6c6;
                        else
                            id = 0x6ac;
                    } else
                        id = 0x1ca;
                } else
                    fn_10_a332(line2, 0x1cb, 1, 0xe, g_7090[o].f_058, name, 5); /* near name (sic) */
            } else if (g_7090[o].f_052 == 1) {
                if (g_7090[o].f_056 != me)
                    fn_03_1542(0, 0xe, g_7090[o].f_056, name, 5);
                else
                    LoadString(g_9212, 0x1c8, name, 40);
                id = 0x28dc;
            } else if (g_7090[o].f_146 == 1)
                id = 0x6a6;
            else if (g_7090[o].f_146 == 2) {
                cnt = -1;
                for (i = 0; i <= g_9316; i++) {
                    if (g_1df8[14][i].f_18)
                        continue;
                    if (i == o)
                        continue;
                    if (g_7090[i].f_032.a == g_7090[o].f_032.a
                        && g_7090[i].f_032.b == g_7090[o].f_032.b
                        && g_7090[i].f_038 == 1) {
                        cnt = i;
                        break;
                    }
                }
                if (cnt == -1)
                    id = 0x6a7;
                else
                    fn_10_a332(line2, 0x435, 1, 0xe, i, 5, tt == 0xe,
                               tn == me, 0x1cf, 0x1c8, tt != 0xe);
            } else if (tt == 2)
                id = 0x1cd;
            else if (g_7090[o].f_052 == 0x17)
                id = 0x1ef;
            else if (g_7090[o].f_146 == 0xa)
                id = 0x6a8;
            else if (g_7090[o].f_146 == 0xf)
                id = 0x6a9;
            else if (g_7090[o].f_146 == 0x10)
                id = 0x6aa;
            else if (tt == 0xe) {
                if (g_7090[o].f_0ee[tn] != 0 && g_7090[o].f_0ee[tn] <= 5) {
                    switch (g_7090[o].f_0ee[tn]) {
                    case 1:
                        id = 0x462;
                        break;
                    case 2:
                        id = 0x463;
                        break;
                    case 3:
                        id = 0x464;
                        break;
                    case 4:
                        id = 0x465;
                        break;
                    case 5:
                        id = 0x466;
                        break;
                    }
                } else
                    fn_10_a332(line2, 0x1ce, 1, tn == me, 0x1cf, 0x1c8);
            } else if (tt == 0) {
                if (g_1df8[0][tn].f_53 == 2)
                    id = 0x456;
                else if (g_1df8[0][tn].f_2f < 0
                         && g_7090[o].f_0b8[g_7090[o].f_018] == 5)
                    id = 0x6ad;
                else {
                    LoadString(g_9212, 0x457, line2, 40);
                    lstrcpy(tmp, g_57a8[tn].f_0c);
                    for (cnt = 0; cnt < lstrlen(tmp); cnt++)
                        if (tmp[cnt] == '.') {
                            tmp[cnt] = 0;
                            break;
                        }
                    lstrcat(line2, tmp);
                    lstrcat(line2, "!");
                }
            } else if (tt == 8) {
                if (g_3d50[tn].f_1c == 2) {
                    if (g_3d50[tn].f_0a == -1)
                        id = 0x459;
                    if (g_3d50[tn].f_0a == -3)
                        id = 0x45a;
                    if (g_3d50[tn].f_0a == 0x10)
                        id = 0x45b;
                    else
                        id = 0x45d;
                } else if (g_96d2[g_7090[o].f_04e].f_38 == 6)
                    id = 0x1f6;
                else
                    id = 0x45c;
            } else if (tt == 9)
                id = 0x458;
            else if (g_96d2[g_7090[o].f_04e].f_38 == 6)
                id = 0x1f6;
            else
                id = 0x1f7;
            break;
        case 3:
            if (tt == 0xe && (g_9134 != 1 || !flow_interactive || o != main_ship
                              || g_7090[o].f_052 == 5)) {
                if (g_7090[o].f_052 != 7) {
                    fn_10_a332(s1, 0x1d0, 1, (LPSTR)name);
                    if (tn == me && (!g_9134 || o != main_ship || !flow_interactive))
                        LoadString(g_9212, 0x1c8, name, 40);
                    else if (!g_9134 || o != main_ship || !flow_interactive)
                        LoadString(g_9212, 0x1cf, name, 40);
                    if (g_7090[o].f_052 == 5) {
                        if (flow_interactive && o == main_ship) {
                            if (!g_9134)
                                LoadString(g_9212, 0x127, s1, 40);
                            else
                                fn_10_a332(s1, 0x594, 1, (LPSTR)name);
                        } else if (g_7090[o].f_058 == o)
                            id = 0x28e2;
                        else
                            id = 0x28e1;
                    } else if (g_7090[o].f_052 == 0x14)
                        id = 0x1f2;
                    else if (g_7090[o].f_052 == 0x16) {
                        if (g_7090[o].f_056 == me)
                            LoadString(g_9212, 0x1fb, s1, 40);
                        else
                            fn_10_a332(s1, 0x1fc, 1, 0xe, g_7090[o].f_056, 5);
                        id = g_a163 + 0x44a;
                    } else if (fn_13_2688(o, tn) > g_7090[o].f_05d * 40 + 50)
                        id = 0x1f3;
                    else if (g_7090[o].f_0c2[tn] > 0)
                        id = 0x28e3;
                    else
                        id = 0x2904;
                } else {
                    LoadString(g_9212, 0x1d4, s1, 40);
                    id = 0x1d5;
                }
            } else if (g_7090[o].f_052 == 7
                       || o == main_ship && g_7090[o].f_032.a == 8
                          && g_7090[o].f_032.b == 0) {
                LoadString(g_9212, 0x1d6, s1, 40);
                if (tt == 0)
                    id = 0x28e7;
                else if (g_7090[o].f_03c == 5)
                    id = 0x28e8;
                else if (g_7090[o].f_026[0] < 0x32)
                    id = LoadString(g_9212, 0x1f5, line2, 40);  /* sic: length as id */
                else
                    id = 0x28e9;
            } else {
                fn_10_a332(s1, 0x1da, 1, (LPSTR)name);
                id = 0x1db;
            }
            break;
        case 2:
            if (fn_13_371c(tt, tn)) {
                if (g_7090[o].f_052 == 0x16) {
                    if (g_7090[o].f_056 == me)
                        LoadString(g_9212, 0x1fb, s1, 40);
                    else
                        fn_10_a332(s1, 0x1fc, 1, 0xe, g_7090[o].f_056, 5);
                    id = g_a163 + 0x44a;
                } else {
                    LoadString(g_9212, 0x1dc, s1, 40);
                    *(int16_t *)tmp = 0;    /* flag kept in tmp's slot (frame layout) */
                    for (i = 0; i <= g_9316; i++)
                        if (g_96d2[g_7090[i].f_04e].f_38 == 7
                            && g_7090[i].f_05e == 1 && g_7090[i].f_056 == o) {
                            *(int16_t *)tmp = 1;
                            break;
                        }
                    if (*(int16_t *)tmp)
                        id = 0x45e;
                    else if (me == 100) {
                        if (!flow_interactive)
                            id = 0x45f;
                        else
                            id = 0x461;
                    } else
                        id = 0x1dd;
                }
            } else if (g_1df8[tt][tn].f_53 || o == main_ship && g_9134 < 2) {
                fn_03_1542(1, tt, tn, name, 2);
                fn_10_a332(s1, 0x1de, 1, (LPSTR)name);
                if (g_7090[o].f_052 == 9 || g_7090[o].f_052 == 0xc) {
                    if (g_7090[o].f_058 == me)
                        id = 0x1df;
                    else
                        id = 0x1e0;
                } else if (g_7090[o].f_052 == 0xe)
                    fn_10_a332(line2, 0x202, 1, 0xe, g_7090[o].f_056, 5);
                else if (tt == 0xb) {
                    if (g_96d2[g_7090[o].f_04e].f_38 == 3)
                        id = 0x1fe;
                    else if (g_96d2[g_7090[o].f_04e].f_38 == 7)
                        id = 0x444;
                    else
                        id = 0x1ff;
                } else if (tt == 6 && g_96d2[g_7090[o].f_04e].f_38 == 7)
                    id = 0x200;
                else if (tt == 4 && g_7090[o].f_01e < 300)
                    id = 0x46b;
                else if (tt == 0)
                    id = 0x1e1;
                else if (tt == 4
                         && g_96d2[g_7090[o].f_04e].f_1e - 15 > g_7090[o].f_01e)
                    id = 0x46a;
                else if (tt == 4)
                    id = 0x469;
            } else {
                LoadString(g_9212, 0x6a4, s1, 40);
                id = 0x6a5;
            }
            break;
        case 4:
            if (tt == 0xe && tn == me) {
                LoadString(g_9212, 0x1e2, s1, 40);
                id = 0x1e3;
            } else {
                fn_10_a332(s1, 0x1e4, 1, tt, tn, 5);
                id = 0x1e5;
            }
            break;
        case 5:
            LoadString(g_9212, 0x1ea, s1, 40);
            id = 0x1eb;
            break;
        default:
            LoadString(g_9212, 0x1e6, s1, 40);
            id = 0x1e7;
            break;
        }
    }
    if (o == main_ship && flow_interactive && !g_9460)
        lstrcpy(line2, "");
    else if (id > 10000)
        fn_10_a332(line2, id - 10000, 1, (LPSTR)name);
    else if (id != -1)
        LoadString(g_9212, id, line2, 40);
    lstrcat(line1, s1);
    if (lstrlen(line1) > 60 || lstrlen(line2) > 60)
        g_9498++;
    fn_03_31d0(mode, line1, line2);
}

/* 3:304c */
void describe_defender_order_message(int16_t n, int16_t k, int16_t mode)
{
    int16_t t1;
    int16_t n1;
    int16_t unused;
    int16_t n2;
    int16_t t2;
    char name1[40];
    char name2[40];
    char line1[60];
    char line2[60];

    t1 = g_52ec[k].f_1c.a;
    n1 = g_52ec[k].f_1c.b;
    t2 = g_52ec[k].f_18.a;
    n2 = g_52ec[k].f_18.b;
    if (t1 != 0xe || n1 != n)
        fn_03_1542(0, t1, n1, name1, 5);
    else
        LoadString(g_9212, 0x1c8, name1, 40);
    if (t2 != 0xe || n2 != n)
        fn_03_1542(0, t2, n2, name2, 5);
    else
        LoadString(g_9212, 0x1c8, name2, 40);
    switch (g_52ec[k].f_12) {
    case 0xf:
        if (fn_13_371c(t1, n1))
            fn_10_a332(g_8d38, 0xbdf, 1, (LPSTR)name2);
        else
            fn_10_a332(g_8d38, 0xbe0, 1, (LPSTR)name1, t1 == 2, 0x9eb, 0x8a9,
                       (LPSTR)name2);
        break;
    default:
        fn_10_a332(g_8d38, 0x8aa, 1, (LPSTR)name2);
        break;
    case 0xa:
        fn_10_a332(g_8d38, 0xbe1, 1, (LPSTR)name1, (LPSTR)name2);
        break;
    }
    fn_03_3498(g_8d38, line1, line2);
    if (lstrlen(line1) > 40 || lstrlen(line2) > 40)
        g_9498++;
    fn_03_31d0(mode, line1, line2);
}

/* Select the next target for the player [inferred]: the nearest one after
 * the current, else the next one in list order, else the first. */
/* 3:045a */
void fn_03_045a(int16_t mode)
{
    int16_t type;
    int16_t n;
    int16_t start;
    int16_t oa;
    int16_t ob;
    int16_t d;
    int16_t best;
    int16_t btype;
    int16_t bn;
    int16_t ctype;
    int16_t cn;
    int16_t flag;

    flag = 0;
    if (mode == 6) {
        cn = g_6e38[2].f_1a.a;
        ctype = g_6e38[2].f_1a.b;
        if (ctype == 0xe)
            mode = 1;
        else
            mode = 5;
        flag = 1;
    } else {
        ctype = g_6e38[0].f_1a.b;
        cn = g_6e38[0].f_1a.a;
    }
    if (!fn_03_065e(ctype, cn, mode)) {
        best = 20000;
        for (type = 0; type <= 0xe; type++) {
            for (n = 0; n < g_9406[type]; n++) {
                if (ctype == type && cn >= n)
                    continue;
                if (!fn_03_065e(type, n, mode))
                    continue;
                d = fn_08_285a(&oa, &ob, g_1df8[0xe][main_ship].f_04,
                               g_1df8[type][n].f_04);
                if (d < best) {
                    best = d;
                    btype = type;
                    bn = n;
                }
            }
        }
        if (best < 20000) {
            fn_03_062e(flag, main_ship, btype, bn);
            return;
        }
    }
    if (mode == 1)
        start = 0xe;
    else
        start = ctype;
    if (ctype <= 0xe || cn < g_9406[14]) {
        for (type = start; type <= 0xe; type++) {
            for (n = 0; n < g_9406[type]; n++) {
                if (ctype == type && cn >= n)
                    continue;
                if (fn_03_065e(type, n, mode))
                    goto found;
            }
        }
    }
    if (mode != 1)
        start = 0;
    for (type = start; type <= 0xe; type++) {
        for (n = 0; n < g_9406[type]; n++) {
            if (fn_03_065e(type, n, mode)) {
            found:
                fn_03_062e(flag, main_ship, type, n);
                return;
            }
        }
    }
    fn_03_062e(flag, main_ship, 0xc, 1);
}
