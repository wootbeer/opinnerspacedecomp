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

extern int g_8ffa;
extern int g_8ffc;
extern int g_9002;
extern int g_9004;
extern int g_9006;
extern int g_9150;
extern int g_9152;
extern int g_9154;
extern int g_9156;

extern long g_1df4;
extern int g_8f76;
extern int g_8f78;
extern int g_9008;
extern int g_9208;
extern int g_8ffe;
extern int g_8ff2;

int far fn_02_094c(UINT id);
void far fn_10_4dfe(void);
void far fn_06_0b3e(void);
void far fn_06_0f1a(int v, char far *buf);

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

/* @addr 6:0a6c */
void far fn_06_0a6c(void)
{
    char buf[10];

    g_8ffc = g_8ffa;
    if (g_8ffc > 1200)
        g_9004 = g_8ffc / 50;
    else if (g_8ffc > 850)
        g_9004 = g_8ffc / 150;
    else
        g_9004 = 0;
    g_9002 = g_9004;
    g_9006 = 10;
    if (g_8ffc > 360)
        g_9006 = g_8ffc / 38;
    else
        g_9006 = 7;
    g_9006 = min(g_9006, 10);
    g_9006 = max(g_9006, 7);
    fn_06_0b3e();
    g_9156 = GetPrivateProfileInt(g_9690, "Size", 1, g_96a9);
    g_9150 = 4 - g_9156;
    g_9152 = g_9154;
    fn_06_0f1a(g_8ffc, buf);
    WritePrivateProfileString(g_9690, "Calibrate", buf, g_96a9);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_0b3e(void)
{
    g_9006 = 0;
}

/* @addr 6:0daa */
void far fn_06_0daa(void)
{
    int v;

    if (g_8ffc > 600) {
        g_1df4 = 120;
        g_8f76 = g_8ffa / 28;
    } else if (g_8ffc > 500) {
        g_1df4 = 130;
        g_8f76 = g_8ffa / 80;
    } else if (g_8ffc > 250) {
        g_1df4 = 140;
        g_8f76 = g_8ffa / 80;
    } else {
        g_1df4 = 150;
        g_8f76 = 0;
    }
    g_9008 = min(g_8ffa / 65, 26);
    g_9008 = max(g_9008, 11);
    g_9008 = 4;
    switch (g_9208) {
    case 0:
        g_9154 = 4;
        g_8ffe = 3;
        break;
    case 1:
        g_9154 = 7;
        g_8ffe = 2;
        break;
    case 2:
        g_9154 = 13;
        g_8ffe = 1;
        break;
    case 3:
        g_9154 = 18;
        g_8ffe = 1;
        break;
    }
    v = GetPrivateProfileInt(g_9690, "Bright", 0, g_96a9);
    if (v)
        g_9154--;
    if (v != g_8ff2) {
        g_8ff2 = v;
        fn_10_4dfe();
    }
    g_8f78 = g_8f76;
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
/* Long version of fn_06_1010 [inferred]. */
/* @addr 6:0f54 */
void far fn_06_0f54(long v, int div, int width, char far *buf)
{
    char tmp[16];
    long r;

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

/* Appends the decimal digits of v to buf (after a "-" already there).
 * Quirk: exactly 1000000000 counts as 9 digits. [inferred] */
/* @addr 6:10ce */
void far fn_06_10ce(unsigned long v, char far *buf)
{
    int unused1;
    int unused2;
    int i;
    int pos;
    int n;
    int off;

    if (buf[0])
        off = 1;
    else
        off = 0;
    if (v > 1000000000)
        n = 10;
    else if (v >= 100000000)
        n = 9;
    else if (v >= 10000000)
        n = 8;
    else if (v >= 1000000)
        n = 7;
    else if (v >= 100000)
        n = 6;
    else if (v >= 10000)
        n = 5;
    else if (v >= 1000)
        n = 4;
    else if (v >= 100)
        n = 3;
    else if (v >= 10)
        n = 2;
    else
        n = 1;
    buf[off + n] = 0;
    pos = n + off - 1;
    for (i = 0; i < n; i++, pos--) {
        buf[pos] = (char)(v % 10) + '0';
        v /= 10;
    }
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
