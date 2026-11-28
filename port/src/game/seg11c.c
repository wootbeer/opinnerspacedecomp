/* INSPACE.EXE segment 11 (selector 1050): functions that call 11:33cc far,
 * so they cannot share seg11.c (where 11:3396 calls it near). */
#include "game.h"

/* Scroll bar handler: zoom between 100 and 500 [inferred]. */
/* 11:7798 */
void fn_11_7798(int16_t code, uint16_t pos)
{
    int32_t old;

    old = g_0a6c;
    switch (code) {
    case 1:
        g_0a6c -= 20;
        break;
    case 0:
        g_0a6c += 20;
        break;
    case 6:
        g_0a6c = 500;
        break;
    case 7:
        g_0a6c = 100;
        break;
    case 4:
    case 5:
        g_0a6c = 600L - pos;
        break;
    case 2:
    case 3:
        break;
    }
    if (g_0a6c > 500)
        g_0a6c = 500;
    else if (g_0a6c < 100)
        g_0a6c = 100;
    if (old != g_0a6c) {
        fn_11_33cc();
        SetScrollPos(g_0a7a, SB_CTL, 600 - (int16_t)g_0a6c, TRUE);
    }
}

/* Key handler for game mode 1 (g_90f4 == 1) [inferred]. */
/* Unused locals keep the frame size; u4 is never read (it only fixes the
 * load order of fdc + fce). */
/* 11:6b64 */
void fn_11_6b64(int16_t msg, WPARAM wparam, int32_t lparam)
{
    int16_t u4, u6;
    OBJREF ref;
    int16_t ua, uc, ue, i, u12, u14, found, pause, alt, ctrl, u1e;

    if (msg == WM_KEYUP && (wparam == VK_ESCAPE || (wparam == 'R' && !flow_interactive))) {
        if (g_9320 == 6 && !g_9eb5 && g_9eb4 && g_38c8[1] != ':'
            && wparam == VK_ESCAPE) {
            fn_10_744c(0x14);
            g_9eb5 = 1;
            race_radar_background(0);
            for (i = g_9318 * 2; i < g_9318 * 2 + g_9ea2 + g_9ea4; i++)
                fn_12_3e98(i);
            for (i = 0; i <= g_9316; i++) {
                g_7090[i].f_148 = 0xfe;
                VIEW(int32_t, g_7090[i].f_032.a, 0) = 12;
                g_7090[i].f_03a = g_7090[i].f_036 = 2;
                object_records[14][i].f_51 = 1;
            }
        } else if (flow_interactive && wparam == VK_ESCAPE) {
            if (g_934e > 2)
                PostMessage(main_window, 0x991, 0, 0L);
        } else {
            g_13de = 1;
            g_968e = 0;
            fn_09_0d6c();
        }
    }
    if (!g_8e62)
        return;
    if ((msg == WM_KEYUP && wparam == 'P') || (msg == WM_KEYDOWN && wparam == 'H'))
        pause = 1;
    else
        pause = 0;
    if ((g_7090[main_ship].f_084 > now_ms || object_records[g_9324][main_ship].f_18) && !pause)
        return;
    if (msg == 0x99e || GetKeyState(VK_CONTROL) & 0x8000)
        ctrl = 1;
    else
        ctrl = 0;
    if (msg == 0x99b || GetKeyState(VK_MENU) & 0x8000)
        alt = 1;
    else
        alt = 0;
    switch (msg) {
    case WM_KEYUP:
        if (!flow_interactive)
            break;
        switch (wparam) {
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
        case VK_F3: case VK_F4: case VK_F5: case VK_F6: case VK_F7:
        case VK_F8: case VK_F9:
            if (g_951c)
                handle_cheat_key(wparam);
            break;
        case VK_F12:
            if (g_9134)
                g_9134 = 0;
            else if (g_9320 != 6 && !g_92e8 && fn_10_a96c()) {
                g_9134 = 1;
                lstrcpy(g_8630, "");
                fn_13_2f30(main_ship);
            }
            g_1038 = 1;
            g_9378 = g_9134;
            PostMessage(main_window, 0x9a5, 0, 0L);
            break;
        case 'P':
            if (g_920c != 3)
                g_1032 = 1;
            break;
        case VK_CAPITAL:
            if (!g_9134) {
                if (g_7090[main_ship].f_0e9)
                    fn_11_4b00(main_ship);
                else if (g_7090[main_ship].f_0e7)
                    fn_11_4c72(main_ship);
            }
            break;
        case VK_RETURN:
        case 'Z':
            if (!g_9134)
                fn_11_ac86();
            break;
        }
        break;
    case WM_KEYDOWN:
    case 0x99b:
    case 0x99e:
        if (flow_interactive || wparam == VK_ADD || wparam == VK_SUBTRACT
            || wparam == 'W' || wparam == 0xbd || wparam == 0xbb)
        switch (wparam) {
        case VK_DELETE:
            if (g_920c == 2 || g_920c == -1) {
                g_951c = !g_951c;
                if (!g_951c)
                    g_104c[0].a = 0;
                else
                    fn_10_744c(0x49);
                g_5018 = -1;
            }
            break;
        case 'D':
            if (ctrl)
                fn_13_8e98(main_ship);
            else
                fn_13_a4f4();
            break;
        case 'X':
            if (ctrl && alt)
                self_destruct_ship(g_9324, main_ship);
            break;
        case VK_RETURN:
        case 'Z':
            if (!g_9134 && g_7090[main_ship].f_0b8[g_7090[main_ship].f_018] == 0xd)
                fn_11_ac86();
            break;
        case 'H':
            if (ctrl)
                fn_13_81c2(main_ship);
            if (alt)
                fn_13_9ae8(main_ship);
            else if (!ctrl && flow_interactive) {
                if (fn_16_0b4e(main_ship))
                    fn_03_06ec(main_ship, 7, 0, 7);
                else if ((u4 = LO16(g_7090[main_ship].f_0dc)) + g_7090[main_ship].f_0ce < -300)
                    fn_03_06ec(main_ship, 7, 0, 0x84);
                else
                    fn_03_06ec(main_ship, 7, 0, 8);
            }
            break;
        case 'F':
            if (ctrl)
                fn_13_915c(main_ship);
            break;
        case 'G':
            if (ctrl)
                fn_13_a01c(main_ship);
            else
                fn_13_a47c();
            break;
        case 'C':
            if (ctrl)
                fn_13_9ce0(main_ship);
            else
                fn_13_a234();
            break;
        case 'S':
            if (ctrl && alt)
                fn_13_4ac4(main_ship);
            else if (ctrl)
                fn_13_9810(main_ship);
            else
                fn_13_a568();
            break;
        case 'A':
            if (ctrl)
                fn_13_8570(main_ship);
            if (alt)
                fn_13_9a18(main_ship, LO16(g_7090[main_ship].f_03e), HI16(g_7090[main_ship].f_03e));
            else if (!ctrl)
                fn_13_a186();
            break;
        case 'E':
            if (ctrl)
                fn_13_9f3e(main_ship);
            if (alt) {
                found = -1;
                for (i = 0; i < g_9406[2]; i++)
                    if (g_52ec[i].f_18.a == g_9324 && g_52ec[i].f_18.b == main_ship) {
                        fn_08_9028(i, 0xf, 0xc, 1);
                        found = i;
                    }
                if (found >= 0)
                    fn_10_754a(0x15, 2, found, 1);
            } else if (!ctrl)
                fn_13_a3c8();
            break;
        case 'W':
            fn_13_563c(ctrl, alt);
            break;
        case 'T':
            if (ctrl) {
                g_0a62 = !g_0a62;
                if (g_0a62) {
                    ref = objref_of(fn_13_2206());
                    fn_03_00f4(main_ship, ref.type, ref.idx);
                }
                if (g_0a7c)
                    PostMessage(g_0a7c, WM_PAINT, 0, 0L);
            } else
                fn_11_772e(ctrl, 0);
            break;
        case 'I':
            if (alt)
                PostMessage(main_window, 0x9aa, 0, 0L);
            else
                fn_11_772e(ctrl, 2);
            break;
        case 'Y':
            fn_11_772e(ctrl, 3);
            break;
        case 'U':
            fn_11_772e(ctrl, 5);
            break;
        case 'V':
            fn_11_772e(ctrl, 4);
            break;
        case 'R':
            if (alt)
                PostMessage(main_window, 0x9b4, 0, 0L);
            else
                fn_11_772e(ctrl, 1);
            break;
        case 'M':
            if (g_0a76 != 3) {
                g_0a76 = 3;
                if (g_0a7c)
                    PostMessage(g_0a7c, WM_PAINT, 0, 0L);
            }
            break;
        case 'B':
            if (g_0a76 != 4)
                g_0a76 = 4;
            if (g_0a7c)
                PostMessage(g_0a7c, WM_PAINT, 0, 0L);
            break;
        case VK_TAB:
            fn_11_adf0();
            fn_11_2f8c();
            break;
        case VK_ADD:
        case 0xbb:
            if (alt)
                fn_10_7e1c(1);
            else if (ctrl)
                fn_10_9a2a(1);
            else {
                SetScrollPos(g_0a7a, SB_CTL,
                    600 - (int16_t)(g_0a6c = g_0a6c + 8 > 500 ? 500 : g_0a6c + 8), TRUE);
                fn_11_33cc();
            }
            break;
        case VK_SUBTRACT:
        case 0xbd:
            if (alt)
                fn_10_7e1c(-1);
            else if (ctrl)
                fn_10_9a2a(-1);
            else {
                SetScrollPos(g_0a7a, SB_CTL,
                    600 - (int16_t)(g_0a6c = g_0a6c - 8 < 100 ? 100 : g_0a6c - 8), TRUE);
                fn_11_33cc();
            }
            break;
        }
        break;
    }
    g_8e62 = 0;
}
