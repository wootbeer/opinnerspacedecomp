/* INSPACE.EXE segment 11 (selector 1050). */
#include "inspace.h"

/* 0x15a-byte records indexed by g_9646; base taken as DS:70a8 [inferred]. */
typedef struct {
    int  w00;                   /* +0x00 */
    char pad02[0xb1];
    char b_b3;                  /* +0xb3 */
    char pad_b4[0x16];
    char b_ca;                  /* +0xca */
    char pad_cb[0x15a - 0xcb];
} REC15A;
extern REC15A g_70a8[];

/* 0x1e-byte records at DS:6e3c [inferred]. */
typedef struct {
    int  w00;                   /* +0x00 */
    char pad02[0x1c];
} REC1E;
extern REC1E g_6e3c[];

extern int g_001a;
extern HWND g_0a7a;
extern HWND g_0a7c;
extern HWND g_0a7e;
extern int g_13de;
extern int g_500a;
extern int g_8e62;
extern int g_8ff4;
extern int g_90f4;
extern int g_9130;                  /* subgame_active */
extern int g_9208;
extern int g_92e4;
extern int g_93aa;
extern int g_93d6;
extern int g_93de;
extern int g_9462;
extern char g_94e4[22];
extern char g_94fa[22];
extern int g_9646;
extern int g_968e;

int far fn_10_6b54(void);
void far fn_06_1c72(int a);
void far fn_09_0d6c(void);
void far fn_06_626c(void);

/* Not yet decompiled: stubs so calls to them compile as near calls. */
void far fn_11_04ea(void) { }
void far fn_11_05fe(int a) { }
void far fn_11_0978(void) { }
void far fn_11_1ef6(int a) { }
void far fn_11_2ce6(HDC dc, int a) { }
void far fn_11_33cc(void) { }

/* @addr 11:2120 */
int far fn_11_2120(void)
{
    if (g_500a == 0 || g_9130 != 0 || g_90f4 != 1 && g_90f4 != 7)
        return 0;
    return 1;
}

/* @addr 11:72b2 */
void far fn_11_72b2(void)
{
    if (g_70a8[g_9646].b_ca == 0 && fn_10_6b54() == 0xa7)
        g_8ff4 = 0;
}

/* @addr 11:3396 */
void far fn_11_3396(void)
{
    if (++g_93de >= ((8 - g_9208) * 16 >> 6) * g_93d6) {
        g_93de = 0;
        fn_11_33cc();
    }
}

/* @addr 11:ae94 */
void far fn_11_ae94(void)
{
    if (g_92e4 == 0) {
        if (g_70a8[g_9646].b_b3 > 1)
            g_70a8[g_9646].w00 = 1;
        else
            g_70a8[g_9646].w00 = 0;
    }
}

/* @addr 11:7b7a */
void far fn_11_7b7a(int msg, int key)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1)
                    fn_06_1c72(1);
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:78bc */
void far fn_11_78bc(int msg, int key)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 0) {
                    g_13de = 1;
                    g_968e = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:7b30 */
void far fn_11_7b30(int msg, int key)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 4) {
                    fn_09_0d6c();
                    fn_06_626c();
                    g_001a = 0;
                }
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:7bbc */
void far fn_11_7bbc(int msg, int key)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 != 1 && g_90f4 != 7)
                    g_93aa = 0x12;
                break;
            case 0x20:
                g_9462 = -1;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 11:b306 */
int far fn_11_b306(int c)
{
    int i;

    if (g_94fa[0] != 'Y') {
        for (i = 1; i < 0x16; i++)
            if (g_94fa[i] == c)
                return g_94e4[i];
    }
    return c;
}

/* @addr 11:04a0 */
void far fn_11_04a0(int a)
{
    if (fn_11_2120()) {
        switch (a) {
        case 0:
            fn_11_04ea();
            break;
        case 1:
            fn_11_05fe(0);
            break;
        case 6:
            fn_11_0978();
            break;
        case 7:
            fn_11_1ef6(0);
            break;
        }
    }
}

/* @addr 11:02f0 */
void far fn_11_02f0(void)
{
    if (g_0a7a) {
        DestroyWindow(g_0a7a);
        g_0a7a = 0;
    }
    if (g_0a7c) {
        DestroyWindow(g_0a7c);
        g_0a7c = 0;
    }
    if (g_0a7e) {
        DestroyWindow(g_0a7e);
        g_0a7e = 0;
    }
}

/* @addr 11:3ed8 */
void far fn_11_3ed8(int i)
{
    HDC dc;
    HWND hwnd;

    g_6e3c[i].w00 = g_6e3c[i].w00 == 0;
    if (i == 2)
        hwnd = g_95fc;
    else
        hwnd = g_0a7c;
    fn_11_2ce6(dc = GetDC(hwnd), i);
    ReleaseDC(hwnd, dc);
}
