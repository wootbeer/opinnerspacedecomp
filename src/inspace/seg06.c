/* INSPACE.EXE segment 6 (selector 1028): 6:0000-6:12b6, one source file
 * (6:12b6-6:1c72 is in seg06c.c, 6:1c72-6:5d58 in seg06d.c, the rest,
 * compiled with /G2, in seg06b.c). */
#include "inspace.h"

void far fn_06_10ce(unsigned long v, char far *buf);

extern HINSTANCE g_8e66;
extern int g_90f8;
extern int g_131a;
extern int g_8f70;
extern int g_8fec;
extern int g_8ff8;
extern int g_932a;
extern int g_9000;
extern int g_91f8;

int far fn_02_094c(UINT id);

/* @addr 6:02ca */
void far fn_06_02ca(void)
{
    SetClassWord(g_0016, GCW_HICON, LoadIcon(g_8e66, "GAME"));
    g_131a = GetPrivateProfileInt(g_9690, "Aux", 0, g_96a9);
    if (!g_90f8)
        g_8f70 = GetPrivateProfileInt(g_9690, "QuickIntro", 0, g_96a9);
    g_8fec = GetPrivateProfileInt(g_9690, "Rate", 0, g_96a9);
}

/* @addr 6:09f8 */
int far fn_06_09f8(void)
{
    if (!SetTimer(g_0016, 1, 1000, NULL)) {
        fn_02_094c(0x844);
        MessageBox(g_0016, g_8e68, g_9690, MB_ICONEXCLAMATION);
        PostMessage(g_0016, WM_DESTROY, 0, 0L);
        return 0;
    }
    SetClassWord(g_0016, GCW_HICON, LoadIcon(g_8e66, "GAME"));
    return 1;
}

/* @addr 6:0eb8 */
void far fn_06_0eb8(long v, char far *buf)
{
    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    fn_06_10ce(v, buf);
}

/* @addr 6:0ef8 */
void far fn_06_0ef8(unsigned long v, char far *buf)
{
    buf[0] = 0;
    fn_06_10ce(v, buf);
}

/* @addr 6:10aa */
void far fn_06_10aa(unsigned v, char far *buf)
{
    buf[0] = 0;
    fn_06_10ce(v, buf);
}

/* @addr 6:0f1a */
void far fn_06_0f1a(int v, char far *buf)
{
    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    fn_06_10ce(v, buf);
}

/* Formats v / div as "int.frac", the fraction cut to width digits [inferred]. */
/* @addr 6:1010 */
void far fn_06_1010(int v, int div, int width, char far *buf)
{
    char tmp[16];
    int r;

    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    tmp[0] = 0;
    fn_06_10ce(v / div, tmp);
    lstrcat(buf, tmp);
    lstrcat(buf, ".");
    tmp[0] = 0;
    r = v % div;
    fn_06_10ce(r, tmp);
    tmp[width] = 0;
    lstrcat(buf, tmp);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_10ce(unsigned long v, char far *buf)
{
    buf[1] = (char)v;
}

/* @addr 6:11ec */
void far fn_06_11ec(void)
{
    g_8ff8 = GetPrivateProfileInt(g_9690, "Complex", 0, g_96a9);
    switch (g_8ff8) {
    case 0:
        g_932a = 130;
        g_9000 = 0;
        break;
    case 1:
        g_932a = 220;
        g_9000 = 0;
        break;
    case 2:
        g_932a = 310;
        g_9000 = 1;
        break;
    case 3:
        g_932a = 420;
        g_9000 = 2;
        break;
    case 4:
        g_932a = 2000;
        g_9000 = 2;
        break;
    }
    if (g_91f8 < 10)
        g_932a = min(g_932a / 2 + g_91f8 * g_932a / 20, g_932a);
}

/* @addr 6:1290 */
int far fn_06_1290(LPCSTR key, int def)
{
    return GetPrivateProfileInt(g_9690, key, def, g_96a9);
}
