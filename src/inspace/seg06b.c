/* INSPACE.EXE segment 6 (selector 1028), the part compiled with /G2
 * (6:5d58 onwards has no 32-bit instructions). */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include "inspace.h"
#include <stdlib.h>

#pragma pack(1)
typedef struct {                /* 0x229-byte records at far DS:6b08 */
    char p000[0x02];
    char f02;
    char p003[0x13 - 0x03];
    long f13;
    long f17;
    long f1b;
    long f1f;
    char p023[0x2b - 0x23];
    int f2b[15];
    long f49[15];
    long f85[15];
    long fc1[15];
    long ffd[15];
    char p139[0x229 - 0x139];
} REC_229;
#pragma pack()

void far fn_06_7266(void);
void far fn_06_717a(void);
DWORD far pascal fn_06_9e66(HFILE f, char huge *buf, DWORD n);
int far fn_14_4006(HFILE f, char huge *buf, unsigned long len);

extern HGLOBAL g_94e0;
extern void far *g_6afc;
extern HGLOBAL g_94de;
extern void far *g_6af8;
extern HGLOBAL g_94d8;
extern void far *g_6b04;
extern char g_9078[];
extern char g_96b8[];
extern HGLOBAL g_94da;
extern REC_229 far *g_6b08;
extern HGLOBAL g_94dc;
extern HGLOBAL g_94ae;
extern void far *g_69f4;
extern HGLOBAL g_95a4;
extern void far *g_6e24;
extern char g_900a[];
extern char g_a12c[][9];
extern unsigned g_94c8;
extern long g_939a;
extern int g_94ce;
extern int g_94d0;
extern int g_94d2;
extern int g_94d4;
extern int g_94d6;
extern int g_9208;
extern int g_9330;
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

/* @addr 6:72d8 */
void far fn_06_72d8(int n, int m)
{
    int i;

    fn_06_7266();
    g_94ce = n;
    g_94d0 = m;
    switch (g_9208) {
    case 0:
        g_94d2 = 7;
        g_94d4 = 7;
        g_94d6 = 5;
        break;
    case 1:
        g_94d2 = 7;
        g_94d4 = 10;
        g_94d6 = 5;
        break;
    case 2:
        g_94d2 = 8;
        g_94d4 = 13;
        g_94d6 = 6;
        break;
    case 3:
        g_94d2 = 10;
        g_94d4 = 15;
        g_94d6 = 6;
        break;
    }
    g_94da = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (long)g_94ce * 0x229);
    g_6b08 = (REC_229 far *)GlobalLock(g_94da);
    g_94dc = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (long)g_94d0 * 0x4b0);
    g_6b0c = (REC_4B0 far *)GlobalLock(g_94dc);
    for (i = 0; i < g_94d0; i++)
        g_6b0c[i].b[0] = 0;
    for (i = 0; i < g_94ce; i++)
        g_6b08[i].f02 = 0;
    g_9330 = 0;
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

/* Returns 1 when the file is missing or does not start with the
 * expected signature g_939a [inferred]. */
/* @addr 6:8776 */
int far fn_06_8776(LPSTR path)
{
    OFSTRUCT of;
    HGLOBAL h;
    long far *p;
    int r;
    DWORD size;
    HFILE hf;

    hf = OpenFile(path, &of, OF_READ);
    if (hf == -1)
        return 1;
    h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1a9L);
    GlobalLock(h);
    size = GlobalSize(h);
    GlobalUnlock(h);
    if (fn_14_4006(hf, (char huge *)(p = (long far *)GlobalLock(h = GlobalReAlloc(h, size, GMEM_MOVEABLE | GMEM_ZEROINIT))), size) == 0)
        r = 1;
    else {
        r = 0;
        if (*p == g_939a)
            r = 1;
    }
    GlobalUnlock(h);
    GlobalFree(h);
    _lclose(hf);
    return r;
}

/* @addr 6:8684 */
void far fn_06_8684(int i, int j)
{
    g_6b08[i].f49[j] = g_6b08[i].f13;
    g_6b08[i].f85[j] = g_6b08[i].f17;
    g_6b08[i].fc1[j] = rand() % 1024 - (g_6b08[i].f1b >> 2) - 512;
    g_6b08[i].ffd[j] = rand() % 1024 - (g_6b08[i].f1f >> 2) - 512;
    g_6b08[i].f2b[j] = 0;
}

/* Loads the race data from <dir><name>.rac [inferred]. */
/* @addr 6:8b90 */
int far fn_06_8b90(int i)
{
    int unused1;
    int unused2;
    HFILE hf;
    DWORD size;
    char path[114];
    OFSTRUCT of;
    char unused3[30];

    lstrcpy(path, g_900a);
    lstrcat(path, g_a12c[i]);
    lstrcat(path, ".rac");
    hf = OpenFile(path, &of, OF_READ);
    if (hf != -1) {
        size = _filelength(hf);
        g_94c8 = size / 0x42;
        size = g_94c8 * 0x42;
    } else {
        g_94c8 = 0;
        size = 0x42;
    }
    if (g_94e0) {
        GlobalUnlock(g_94e0);
        GlobalFree(g_94e0);
    }
    g_94e0 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size);
    g_6afc = GlobalLock(g_94e0);
    if (!g_94e0)
        return 0;
    if (hf != -1) {
        if (fn_14_4006(hf, (char huge *)g_6afc, size) == 0) {
            GlobalUnlock(g_94e0);
            GlobalFree(g_94e0);
            if (hf != -1)
                _lclose(hf);
            return 0;
        }
        _lclose(hf);
        hf = 0;
    }
    return 1;
}
