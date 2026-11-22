/* INSPACE.EXE segment 6 (selector 1028), the part compiled with /G2
 * (6:5d58 onwards has no 32-bit instructions). */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include "inspace.h"

void far fn_06_7266(void);
void far fn_06_717a(void);
DWORD far pascal fn_06_9e66(HFILE f, char huge *buf, DWORD n);

extern HGLOBAL g_94e0;
extern void far *g_6afc;
extern HGLOBAL g_94de;
extern void far *g_6af8;
extern HGLOBAL g_94d8;
extern void far *g_6b04;
extern char g_9078[];
extern char g_96b8[];
extern HGLOBAL g_94da;
extern void far *g_6b08;
extern HGLOBAL g_94dc;
extern HGLOBAL g_94ae;
extern void far *g_69f4;
extern HGLOBAL g_95a4;
extern void far *g_6e24;
extern char g_900a[];
extern char g_a12c[][9];
extern unsigned g_94c8;
extern unsigned char g_0f00[];      /* quarter-wave sine table, 0..90 degrees [inferred] */

/* @addr 6:626c */
void far fn_06_626c(void)
{
    fn_06_7266();
    fn_06_717a();
    if (g_94d8) {
        if (g_6b04) {
            GlobalUnlock(g_94d8);
            g_6b04 = 0;
        }
        GlobalFree(g_94d8);
        g_94d8 = 0;
    }
}

/* @addr 6:717a */
void far fn_06_717a(void)
{
    if (g_94de) {
        GlobalUnlock(g_94de);
        GlobalFree(g_94de);
        g_94de = 0;
        g_6af8 = 0;
    }
}

/* Sine of an angle in degrees, from the quarter-wave table [inferred]. */
/* @addr 6:71b2 */
int far fn_06_71b2(int deg)
{
    int d;

    d = (deg + 360) % 360;
    if (d < 90)
        return g_0f00[d];
    if (d < 180)
        return g_0f00[180 - d];
    if (d < 270)
        return -g_0f00[d - 180];
    return -g_0f00[360 - d];
}

/* Cosine of an angle in degrees [inferred]. */
/* @addr 6:720c */
int far fn_06_720c(int deg)
{
    int d;

    d = (deg + 360) % 360;
    if (d < 90)
        return g_0f00[90 - d];
    if (d < 180)
        return -g_0f00[d - 90];
    if (d < 270)
        return -g_0f00[270 - d];
    return g_0f00[d - 270];
}

/* @addr 6:7266 */
void far fn_06_7266(void)
{
    if (g_94da) {
        if (g_6b08) {
            GlobalUnlock(g_94da);
            g_6b08 = 0;
        }
        GlobalFree(g_94da);
        g_94da = 0;
    }
    if (g_94dc) {
        if (g_6b0c) {
            GlobalUnlock(g_94dc);
            g_6b0c = 0;
        }
        GlobalFree(g_94dc);
        g_94dc = 0;
    }
}

/* @addr 6:8eb4 */
void far fn_06_8eb4(void)
{
    if (g_94e0) {
        GlobalUnlock(g_94e0);
        GlobalFree(g_94e0);
        g_6afc = 0;
        g_94e0 = 0;
    }
}

/* @addr 6:92b8 */
int far fn_06_92b8(void)
{
    char path[110];
    OFSTRUCT of;

    lstrcpy(path, g_9078);
    lstrcat(path, g_96b8);
    lstrcat(path, "demogame.sav");
    return OpenFile(path, &of, 0x200);
}

/* @addr 6:9932 */
void far fn_06_9932(HGLOBAL h, HFILE f, int keep)
{
    _lclose(f);
    if (h) {
        GlobalUnlock(h);
        GlobalFree(h);
    }
    if (!keep) {
        if (g_94ae) {
            GlobalUnlock(g_94ae);
            GlobalFree(g_94ae);
            g_94ae = 0;
            g_69f4 = 0;
        }
        if (g_95a4) {
            GlobalUnlock(g_95a4);
            GlobalFree(g_95a4);
            g_95a4 = 0;
            g_6e24 = 0;
        }
    }
}

/* Writes n bytes in chunks of 0x7fff; returns n, or 0 on error [inferred]. */
/* @addr 6:9e66 */
DWORD far pascal fn_06_9e66(HFILE f, char huge *buf, DWORD n)
{
    DWORD total;
    char huge *p;

    total = n;
    p = buf;
    while (n > 0x7fff) {
        if (_lwrite(f, (LPCSTR)p, 0x7fff) != 0x7fff)
            return 0;
        n -= 0x7fff;
        p += 0x7fff;
    }
    if (_lwrite(f, (LPCSTR)p, (UINT)n) != (UINT)n)
        return 0;
    return total;
}

/* @addr 6:73d6 */
void far fn_06_73d6(int i)
{
    g_6b0c[i].b[0] = 0;
}

/* Reads the "Complex" setting and sets the difficulty values [inferred]. */

/* Saves the race data to <dir><name>.rac [inferred]. */
/* @addr 6:8dfe */
int far fn_06_8dfe(int i)
{
    int unused1;
    int unused2;
    HFILE hf;
    DWORD size;
    char path[114];
    OFSTRUCT of;
    char unused3[10];

    lstrcpy(path, g_900a);
    lstrcat(path, g_a12c[i]);
    lstrcat(path, ".rac");
    hf = OpenFile(path, &of, OF_CREATE | OF_READWRITE);
    if (hf == -1)
        return 0;
    size = g_94c8 * 0x42;
    if (fn_06_9e66(hf, (char huge *)g_6afc, size) == 0) {
        GlobalUnlock(g_94e0);
        GlobalFree(g_94e0);
        g_94e0 = 0;
        _lclose(hf);
        return 0;
    }
    _lclose(hf);
    hf = 0;
    return 1;
}
