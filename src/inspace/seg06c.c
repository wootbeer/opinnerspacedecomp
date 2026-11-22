/* INSPACE.EXE segment 6 (selector 1028): 6:12b6-6:1c72, one source file. */
#include "inspace.h"

void far fn_06_190c(void);
int far fn_02_1ac8(void);
void far fn_02_1b96(void);

extern int g_90f4;
extern int g_049e;
extern int g_90f8;
extern char g_1d60[];
extern HFONT g_90fe;
extern int g_912c;
extern HMENU g_90fa;
extern HRGN g_0012;
extern HGLOBAL g_9100[];
extern void far *g_1df8[];
extern int g_94a4;
extern HGLOBAL g_912a;

void far fn_10_6e00(void);
void far fn_10_6e76(int a, int b);
int far fn_10_6d38(LPCSTR s);
void far fn_06_02ca(void);
int far fn_06_09f8(void);
void far fn_06_2ebc(void);
void far fn_02_1d58(void);
void far fn_10_022e(int a);
void far fn_10_0330(void);
void far fn_06_033e(void);
void far fn_10_6e26(void);
void far fn_10_6b70(int a);

/* @addr 6:1b3c */
void far fn_06_1b3c(void)
{
    if (g_8f66 && fn_02_1ac8())
        fn_02_1b96();
}

/* @addr 6:18e0 */
void far fn_06_18e0(void)
{
    fn_06_190c();
    g_049e = g_90f4 = 0;
    PostMessage(g_0016, 0x9cf, 0, 0L);
}

/* near-match 73%: 6:190c (the original loads the font height with
 * `mov ax,14; push ax` and pushes the zeros as immediates; plain C gives
 * `push 14` and reuses a zeroed ax) */
void far fn_06_190c(void)
{
    int unused1;
    int unused2;
    HPALETTE old;

    g_13dc = GetDC(g_0016);
    fn_10_6e00();
    old = SelectPalette(g_13dc, g_920e, 0);
    fn_10_6e76(-1000, 2);
    SelectPalette(g_13dc, old, 0);
    ReleaseDC(g_0016, g_13dc);
    g_13dc = 0;
    g_90fe = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PROOF_QUALITY,
                        VARIABLE_PITCH | FF_SWISS, "Arial");
    g_912c = fn_10_6d38("ALPHABET");
    fn_06_02ca();
    if (!fn_06_09f8())
        PostQuitMessage(0);
}

/* @addr 6:19bc */
void far fn_06_19bc(void)
{
    int unused;

    if (!g_049e) {
        g_049e = 1;
        fn_06_2ebc();
        fn_02_1d58();
        fn_10_022e(1);
        if (g_0012) {
            DeleteObject(g_0012);
            g_0012 = 0;
        }
        if (g_0016)
            SetMenu(g_0016, 0);
        if (g_90fa) {
            DestroyMenu(g_90fa);
            g_90fa = 0;
        }
        fn_10_0330();
        fn_06_033e();
        KillTimer(g_0016, 1);
        if (g_90fe) {
            DeleteObject(g_90fe);
            g_90fe = 0;
        }
        fn_10_6e26();
        fn_10_6b70(0);
    }
}

/* @addr 6:1b62 */
int far fn_06_1b62(void)
{
    int i;

    for (i = 0; i <= 14; i++) {
        if ((g_9100[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x460L)) == 0)
            return 0;
        if ((g_1df8[i] = GlobalLock(g_9100[i])) == 0) {
            GlobalFree(g_9100[i]);
            return 0;
        }
    }
    g_94a4 = 0;
    if ((g_912a = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 8L)) == 0)
        return 0;
    if ((g_1e4c = (long)GlobalLock(g_912a)) == 0) {
        GlobalFree(g_912a);
        return 0;
    }
    return 1;
}

/* @addr 6:1c0c */
int far fn_06_1c0c(void)
{
    g_90f8 = 0;
    if (lstrcmp(g_1d60, "DEMO") == 0) {
        g_90f8 = 1;
        PostMessage(g_0016, 0x9f0, 0, 0L);
    }
    if (lstrcmp(g_1d60, "PLAY") == 0) {
        g_90f8 = 1;
        PostMessage(g_0016, 0x9fa, 0, 0L);
    }
    return g_90f8;
}

/* Appends three digits to s, as '0' plus each value [inferred]. */
