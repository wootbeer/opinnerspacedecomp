/* INSPACE.EXE segment 11 (selector 1050): functions that call 11:33cc far,
 * so they cannot share seg11.c (where 11:3396 calls it near). */
#include "inspace.h"

extern HWND g_0a7a;
extern long g_0a6c;

void far fn_11_33cc(void);

/* 0x15a-byte records at DS:7090 [inferred]. */
typedef struct {
    char p000[0x18];
    int f18;                    /* +18 */
    char p01a[0x32 - 0x1a];
    long f32;                   /* +32 */
    int f36;                    /* +36 */
    char p038[0x3a - 0x38];
    int f3a;                    /* +3a */
    char p03c[0x3e - 0x3c];
    long f3e;                   /* +3e */
    char p042[0x84 - 0x42];
    DWORD f84;                  /* +84 */
    char p088[0xb8 - 0x88];
    char fb8[0x13];             /* +b8 */
    char p0cb[0xce - 0xcb];
    int fce;                    /* +ce */
    char p0d0[0xdc - 0xd0];
    int fdc;                    /* +dc */
    char p0de[0xe7 - 0xde];
    char fe7;                   /* +e7 */
    char p0e8;
    char fe9;                   /* +e9 */
    char p0ea[0x148 - 0xea];
    char f148;                  /* +148 */
    char p149[0x15a - 0x149];
} REC_15A;
extern REC_15A g_7090[];

/* 0x70-byte records; DS:1df8 holds one far array of them per object
 * type [inferred]. */
typedef struct {
    char p00[0x18];
    int f18;                    /* +18 */
    char p1a[0x51 - 0x1a];
    char f51;                   /* +51 */
    char p52[0x70 - 0x52];
} REC_70;
extern REC_70 far *g_1df8[16];

/* 0x24-byte records at DS:5304 [inferred]. */
typedef struct {
    int f00;                    /* +00: type */
    int f02;                    /* +02: index */
    char p04[0x24 - 4];
} REC_24;
extern REC_24 g_5304[];

typedef struct { unsigned char idx, type; } OBJREF;

extern int g_0a62;
extern int g_0a76;
extern HWND g_0a7c;
extern int g_1032;
extern int g_1038;
extern int g_104c;
extern int g_13de;
extern DWORD g_1e50;
extern long g_5018;
extern char g_38c8[];
extern char g_8630[];
extern int g_8e62;
extern int g_920c;
extern int g_92e8;
extern int g_9134;
extern int g_9316;
extern int g_9318;
extern int g_9320;
extern int g_9324;
extern int g_934e;
extern int g_9378;
extern int g_940a;
extern int g_951c;
extern int g_95bc;                  /* flow_interactive */
extern int g_9646;
extern int g_968e;
extern char g_9eb4;
extern char g_9eb5;
extern int g_9ea2;
extern int g_9ea4;

void far fn_10_744c(int a);
void far race_radar_background(int a);
void far fn_12_3e98(int i);
void far fn_09_0d6c(void);
int far fn_10_a96c(void);
void far pascal fn_13_2f30(int n);
void far fn_13_8e98(int n);
void far fn_13_a4f4(void);
void far self_destruct_ship(int type, int n);
void far fn_13_81c2(int n);
void far fn_13_9ae8(int n);
int far fn_16_0b4e(int n);
void far fn_03_06ec(int n, int kind, int target, int d);
void far fn_13_915c(int n);
void far fn_13_a01c(int n);
void far fn_13_a47c(void);
void far fn_13_9ce0(int n);
void far fn_13_a234(void);
void far fn_13_4ac4(int n);
void far fn_13_9810(int n);
void far fn_13_a568(void);
void far fn_13_8570(int n);
void far fn_13_9a18(int n, long v);
void far fn_13_a186(void);
void far fn_13_9f3e(int n);
void far fn_08_9028(int i, int a, int b, int c);
void far fn_10_754a(int a, int b, int c, int d);
void far fn_13_a3c8(void);
void far command_watch_ship(int ctrl, int alt);
OBJREF far fn_13_2206(void);
void far fn_03_00f4(int n, char type, int idx);
void far fn_11_2f8c(void);
void far fn_10_7e1c(int d);
void far fn_10_9a2a(int d);

/* Not yet decompiled here (in seg11.c): stubs so calls compile near. */
int far fn_11_72e0(int key) { return 0; }
int far fn_11_4b00(int n) { return 0; }
int far fn_11_4c72(int n) { return 0; }
void far fn_11_ac86(void) { }
void far fn_11_adf0(void) { }
void far fn_11_772e(int a, int b) { }

/* Scroll bar handler: zoom between 100 and 500 [inferred]. */
/* @addr 11:7798 */
void far fn_11_7798(int code, unsigned pos)
{
    long old;

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
        SetScrollPos(g_0a7a, SB_CTL, 600 - (int)g_0a6c, TRUE);
    }
}

/* Key handler for game mode 1 (g_90f4 == 1) [inferred]. */
/* @addr 11:6b64 */
void far pascal fn_11_6b64(int msg, WPARAM wparam, long lparam)
{
    int u4, u6;
    OBJREF ref;
    int ua, uc, ue, i, u12, u14, found, pause, alt, ctrl, u1e;

    if (msg == WM_KEYUP && (wparam == VK_ESCAPE || (wparam == 'R' && !g_95bc))) {
        if (g_9320 == 6 && !g_9eb5 && g_9eb4 && g_38c8[1] != ':'
            && wparam == VK_ESCAPE) {
            fn_10_744c(0x14);
            g_9eb5 = 1;
            race_radar_background(0);
            for (i = g_9318 * 2; i < g_9318 * 2 + g_9ea2 + g_9ea4; i++)
                fn_12_3e98(i);
            for (i = 0; i <= g_9316; i++) {
                g_7090[i].f148 = 0xfe;
                g_7090[i].f32 = 12;
                g_7090[i].f3a = g_7090[i].f36 = 2;
                g_1df8[14][i].f51 = 1;
            }
        } else if (g_95bc && wparam == VK_ESCAPE) {
            if (g_934e > 2)
                PostMessage(g_0016, 0x991, 0, 0L);
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
    if ((g_7090[g_9646].f84 > g_1e50 || g_1df8[g_9324][g_9646].f18) && !pause)
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
        if (!g_95bc)
            break;
        switch (wparam) {
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
        case VK_F3: case VK_F4: case VK_F5: case VK_F6: case VK_F7:
        case VK_F8: case VK_F9:
            if (g_951c)
                fn_11_72e0(wparam);
            break;
        case VK_F12:
            if (g_9134)
                g_9134 = 0;
            else if (g_9320 != 6 && !g_92e8 && fn_10_a96c()) {
                g_9134 = 1;
                lstrcpy(g_8630, "");
                fn_13_2f30(g_9646);
            }
            g_1038 = 1;
            g_9378 = g_9134;
            PostMessage(g_0016, 0x9a5, 0, 0L);
            break;
        case 'P':
            if (g_920c != 3)
                g_1032 = 1;
            break;
        case VK_CAPITAL:
            if (!g_9134) {
                if (g_7090[g_9646].fe9)
                    fn_11_4b00(g_9646);
                else if (g_7090[g_9646].fe7)
                    fn_11_4c72(g_9646);
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
        if (!g_95bc && wparam != VK_ADD && wparam != VK_SUBTRACT
            && wparam != 'W' && wparam != 0xbd && wparam != 0xbb)
            break;
        switch (wparam) {
        case VK_DELETE:
            if (g_920c == 2 || g_920c == -1) {
                g_951c = !g_951c;
                if (!g_951c)
                    g_104c = 0;
                else
                    fn_10_744c(0x49);
                g_5018 = -1;
            }
            break;
        case 'D':
            if (ctrl)
                fn_13_8e98(g_9646);
            else
                fn_13_a4f4();
            break;
        case 'X':
            if (ctrl)
                if (alt)
                    self_destruct_ship(g_9324, g_9646);
            break;
        case VK_RETURN:
        case 'Z':
            if (!g_9134 && g_7090[g_9646].fb8[g_7090[g_9646].f18] == 0xd)
                fn_11_ac86();
            break;
        case 'H':
            if (ctrl)
                fn_13_81c2(g_9646);
            if (alt)
                fn_13_9ae8(g_9646);
            else if (!ctrl && g_95bc) {
                if (fn_16_0b4e(g_9646))
                    fn_03_06ec(g_9646, 7, 0, 7);
                else if (g_7090[g_9646].fdc + g_7090[g_9646].fce < -300)
                    fn_03_06ec(g_9646, 7, 0, 0x84);
                else
                    fn_03_06ec(g_9646, 7, 0, 8);
            }
            break;
        case 'F':
            if (ctrl)
                fn_13_915c(g_9646);
            break;
        case 'G':
            if (ctrl)
                fn_13_a01c(g_9646);
            else
                fn_13_a47c();
            break;
        case 'C':
            if (ctrl)
                fn_13_9ce0(g_9646);
            else
                fn_13_a234();
            break;
        case 'S':
            if (ctrl && alt)
                fn_13_4ac4(g_9646);
            else if (ctrl)
                fn_13_9810(g_9646);
            else
                fn_13_a568();
            break;
        case 'A':
            if (ctrl)
                fn_13_8570(g_9646);
            if (alt)
                fn_13_9a18(g_9646, g_7090[g_9646].f3e);
            else if (!ctrl)
                fn_13_a186();
            break;
        case 'E':
            if (ctrl)
                fn_13_9f3e(g_9646);
            if (alt) {
                found = -1;
                for (i = 0; i < g_940a; i++)
                    if (g_5304[i].f00 == g_9324 && g_5304[i].f02 == g_9646) {
                        fn_08_9028(i, 0xf, 0xc, 1);
                        found = i;
                    }
                if (found >= 0)
                    fn_10_754a(0x15, 2, found, 1);
            } else if (!ctrl)
                fn_13_a3c8();
            break;
        case 'W':
            command_watch_ship(ctrl, alt);
            break;
        case 'T':
            if (ctrl) {
                g_0a62 = !g_0a62;
                if (g_0a62) {
                    ref = fn_13_2206();
                    fn_03_00f4(g_9646, ref.type, ref.idx);
                }
                if (g_0a7c)
                    PostMessage(g_0a7c, WM_PAINT, 0, 0L);
            } else
                fn_11_772e(ctrl, 0);
            break;
        case 'I':
            if (alt)
                PostMessage(g_0016, 0x9aa, 0, 0L);
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
                PostMessage(g_0016, 0x9b4, 0, 0L);
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
                    600 - (int)(g_0a6c = g_0a6c + 8 > 500 ? 500 : g_0a6c + 8), TRUE);
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
                    600 - (int)(g_0a6c = g_0a6c - 8 < 100 ? 100 : g_0a6c - 8), TRUE);
                fn_11_33cc();
            }
            break;
        }
        break;
    }
    g_8e62 = 0;
}
