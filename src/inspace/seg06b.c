/* INSPACE.EXE segment 6 (selector 1028), the part compiled with /G2
 * (6:5d58 onwards has no 32-bit instructions). */
/* @cflags /AM /G2 /Gw /Gs /Os */
#include "inspace.h"
#include <stdlib.h>
#include <dos.h>

#pragma pack(1)
typedef struct {                /* 0x229-byte records at far DS:6b08 */
    char f00;
    char f01;
    char f02;
    char p003[0x05 - 0x03];
    int f05;
    int f07;
    char p009[0x0b - 0x09];
    int f0b;
    int f0d;
    int f0f;
    int f11;
    long f13;
    long f17;
    long f1b;
    long f1f;
    char p023[0x27 - 0x23];
    int f27;
    int f29;
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
typedef struct {                /* 0x42-byte race record [inferred] */
    char name[0x14];
    char f14[3][10];
    unsigned f32[4][2];
} REC_42;
extern REC_42 far *g_6afc;
extern HGLOBAL g_94de;
extern void far *g_6af8;
extern HGLOBAL g_94d8;
typedef struct {                /* 0x2e-byte champion entries [inferred] */
    char name[0x28];
    long f28;                   /* score [inferred] */
    int f2c;
} REC_2E;
extern REC_2E far *g_6b04;
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
extern char g_8f7a[];
extern char g_96c5[];
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
extern int g_94c4;
extern int g_0010;
extern int g_9130;                  /* subgame_active */
void far fn_10_754a(int a, int b, int c, int d);
void far fn_06_72d8(int n, int m);
int far fn_06_84fc(int a, int x, int y, int dx, int dy, int w, int h,
                   int c, int d, int e);
void far fn_10_744c(int a);
void far fn_10_7d58(int x, int y);
void far fn_13_65f2(int a);
void far fn_11_02f0(void);
void far fn_10_7480(int a, int b);
extern int g_90f4;
extern int g_94cc;
extern int g_90ea;
extern int g_90ec;
extern DWORD g_1e50;
extern DWORD g_1e7c;
extern long g_1e58;
extern int g_93a2;
extern DWORD fireworks_end_ms;      /* DS:6b00 */
extern DWORD fireworks_next_launch_ms;  /* DS:1c38 */
extern int g_1c3c;
extern int g_920c;
extern char g_380c[];
void far fn_16_68d6(HWND hwnd, int id, int id2);
int far fn_06_8776(LPSTR path);
void far fn_06_7042(void);
void far fn_10_94c4(int a, int b, long color, int x, int y, LPSTR s);
void far fn_06_0f1a(int v, char far *buf);
void far fn_06_0eb8(long v, char far *buf);
extern unsigned char g_0f00[];
extern int g_9646;
extern int flow_interactive;        /* DS:95bc */
void far fn_17_8e60(int i, LPSTR buf);
typedef struct {                /* 0x15a bytes at DS:70ae */
    char p00[0x30];
    int f30;
    char p32[0x15a - 0x32];
} REC_70AE;
extern REC_70AE g_70ae[];
#pragma pack(1)
typedef struct {                /* 0xad bytes at DS:96f0 */
    char p00[0x52];
    char f52[0xad - 0x52];
} REC_96F0;
#pragma pack()
extern REC_96F0 g_96f0[];      /* quarter-wave sine table, 0..90 degrees [inferred] */

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
    char unused4[20];
    OFSTRUCT of;
    char unused3[10];

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
    g_6afc = (REC_42 far *)GlobalLock(g_94e0);
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

/* Deletes the *.ded files that carry the signature g_939a [inferred]. */
/* @addr 6:7042 */
void far fn_06_7042(void)
{
    int unused1;
    int unused2;
    HFILE hf;
    int r;
    char unused3[20];
    struct find_t ft;
    HGLOBAL h;
    long far *p;
    char path[110];
    char unused4[110];
    OFSTRUCT of;
    long sig;

    lstrcpy(path, g_8f7a);
    lstrcat(path, g_96c5);
    lstrcat(path, "*.ded");
    h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x62L);
    p = (long far *)GlobalLock(h);
    for (r = _dos_findfirst(path, _A_RDONLY, &ft); r == 0; r = _dos_findnext(&ft)) {
        lstrcpy(path, g_8f7a);
        lstrcat(path, g_96c5);
        lstrcat(path, ft.name);
        hf = OpenFile(path, &of, OF_READ);
        if (hf != -1 && fn_14_4006(hf, (char huge *)p, 0x26L) != 0) {
            sig = *p;
            _lclose(hf);
            if (sig == g_939a)
                OpenFile(path, &of, OF_DELETE);
        }
    }
    GlobalUnlock(h);
    GlobalFree(h);
}

/* Finds or adds the race record for player n's name and stores a new
 * best value v in slot [j][k] [inferred]. */
/* @addr 6:8cb2 */
int far fn_06_8cb2(int unused, int n, unsigned v, int j, int k)
{
    char name[30];
    int i;

    lstrcpy(name, g_96f0[g_70ae[n].f30].f52);
    for (i = 0; i < (int)g_94c8 && lstrcmp(g_6afc[i].name, name); i++)
        ;
    if (i == g_94c8) {
        g_94c8++;
        GlobalUnlock(g_94e0);
        g_94e0 = GlobalReAlloc(g_94e0, g_94c8 * 0x42, GMEM_MOVEABLE | GMEM_ZEROINIT);
        g_6afc = (REC_42 far *)GlobalLock(g_94e0);
        lstrcpy(g_6afc[i].name, g_96f0[g_70ae[n].f30].f52);
    }
    if (v && (g_6afc[i].f32[j][k] > v || g_6afc[i].f32[j][k] == 0)) {
        g_6afc[i].f32[j][k] = v;
        if (n == g_9646 && flow_interactive)
            fn_17_8e60(n, g_6afc[i].f14[j]);
        else
            lstrcpy(g_6afc[i].f14[j], "----");
    }
    return i;
}

/* Starts a new particle/explosion in a free slot [inferred]. */
/* @addr 6:84fc */
int far fn_06_84fc(int a, int x, int y, int dx, int dy, int w, int h,
                   int c, int d, int e)
{
    int unused1;
    int i;
    int unused2;
    int snd;

    if (!g_94da)
        return 1;
    if (g_94c4)
        return 0;
    c = c * 600 / g_0010;
    c = c < 28 ? 28 : c;
    c = c > 29 ? 29 : c;
    for (i = 0; i < g_94ce; i++) {
        if (g_6b08[i].f02)
            continue;
        if (rand() % 3)
            snd = 0x4e;
        else
            snd = 0x1b;
        if (g_9330 && !g_9130)
            fn_10_754a(snd, 6, e, 1);
        else
            fn_10_754a(snd, 0, 0, 0);
        g_6b08[i].f00 = 0;
        g_6b08[i].f27 = 0;
        g_6b08[i].f29 = 0;
        g_6b08[i].f02 = a;
        g_6b08[i].f05 = d;
        g_6b08[i].f07 = 0;
        g_6b08[i].f13 = (long)x << 8;
        g_6b08[i].f17 = (long)y << 8;
        g_6b08[i].f1b = dx;
        g_6b08[i].f1f = dy;
        g_6b08[i].f0b = w;
        g_6b08[i].f0d = h;
        g_6b08[i].f11 = 0;
        g_6b08[i].f0f = c;
        g_6b08[i].f01 = e;
        return 1;
    }
    return 0;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_6576(void)
{
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_8eea(void far *p)
{
}

/* Saves the game (mode 0: .sav, 1: .ded, 2: .don) [inferred]. */
/* @addr 6:885c */
int far fn_06_885c(int ask, int mode)
{
    int i;
    int unused1;
    HFILE hf;
    int unused2;
    int unused3;
    DWORD size;
    char path[110];
    char name[20];
    char tmp[100];
    OFSTRUCT of;
    HGLOBAL h;
    void far *p;
    int done;
    int n;

    if (mode && g_1e58 < 1000)
        return 0;
    if (!g_920c && flow_interactive) {
        if (ask && !mode)
            fn_16_68d6(g_0016, 0x914, -1);
        return 0;
    }
    fn_06_7042();
    lstrcpy(path, g_9078);
    if (mode)
        lstrcat(path, g_96c5);
    else
        lstrcat(path, g_96b8);
    if (ask) {
        GetPrivateProfileString(g_9690, "Restore", "", name, 9, g_96a9);
        if (mode && name[3] == ' ') {
            lstrcpy(tmp, g_380c);
            tmp[7] = 0;
            lstrcpy(name, tmp);
            for (i = 0; i < lstrlen(name); i++)
                if (name[i] == ' ')
                    name[i] = 0;
        }
        lstrcat(path, name);
    } else if (flow_interactive)
        lstrcat(path, "lastgame");
    else
        lstrcat(path, "demogame");
    if (mode == 2)
        lstrcat(path, ".don");
    else if (mode)
        lstrcat(path, ".ded");
    else
        lstrcat(path, ".sav");
    if (mode) {
        n = done = 0;
        do {
            done = fn_06_8776(path);
            if (!done) {
                lstrcpy(path, g_8f7a);
                lstrcat(path, g_96c5);
                name[5] = 0;
                lstrcat(path, name);
                fn_06_0f1a(++n, tmp);
                lstrcat(path, tmp);
                if (mode == 2)
                    lstrcat(path, ".don");
                else
                    lstrcat(path, ".ded");
            }
        } while (!done);
    }
    hf = OpenFile(path, &of, OF_CREATE | OF_READWRITE);
    if (hf == -1)
        return 0;
    h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1a9L);
    p = GlobalLock(h);
    if (!p) {
        GlobalFree(h);
        _lclose(hf);
        return 0;
    }
    fn_06_8eea(p);
    if (!h || !g_94ae || !g_95a4) {
        _lclose(hf);
        return 0;
    }
    if (!fn_06_9e66(hf, (char huge *)p, size = GlobalSize(h))
        || !fn_06_9e66(hf, (char huge *)g_6e24, size = GlobalSize(g_95a4))
        || !mode && !fn_06_9e66(hf, (char huge *)g_69f4, size = GlobalSize(g_94ae))) {
        GlobalUnlock(h);
        GlobalFree(h);
        _lclose(hf);
        return 0;
    }
    _lclose(hf);
    GlobalUnlock(h);
    GlobalFree(h);
    h = 0;
    p = 0;
    return 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_06_73f6(void)
{
    return 0;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
int far fn_06_7c14(void)
{
    return 0;
}

/* Draws the champions table [inferred]. */
/* @addr 6:62b6 */
void far fn_06_62b6(void)
{
    int i;
    int unused;
    int y;
    int w;
    int maxlen;
    int off;
    int n;
    char buf[40];
    char line[60];
    int g;
    int b;

    w = min(g_90ea / 2 - 20, 360);
    maxlen = min((w - 33) * 2 / 18, 39);
    n = 10;
    off = 0;
    if (g_0010 < 480) {
        off = 15;
        n = g_0010 / 47;
    }
    LoadString(g_9212, 0x39d, buf, 40);
    fn_10_94c4(0, 6, RGB(255, 0, 0), g_90ea / 2, g_90ec / 2 + off - 175, buf);
    for (i = 0; i < n; i++) {
        y = i * 30 + g_90ec / 2 + off - 130;
        fn_06_0f1a(g_6b04[i].f2c, buf);
        if (!g_6b04[i].name[0])
            break;
        if (g_6b04[i].f28 == g_1e58)
            g = b = 255;
        else {
            if (i < 3 && g_93a2 > 7)
                g = 255;
            else
                g = i * -255 / 10 + 230;
            b = 0;
        }
        fn_10_94c4(0, 2, PALETTERGB(255, g, b), g_90ea / 2 - w + 7, y, buf);
        lstrcpy(buf, g_6b04[i].name);
        buf[maxlen] = 0;
        fn_10_94c4(0, 0, PALETTERGB(255, g, b), g_90ea / 2 - w + 0x2e, y, g_6b04[i].name);
        fn_06_0eb8(g_6b04[i].f28, buf);
        fn_10_94c4(0, 2, PALETTERGB(255, g, b), g_90ea / 2 + w - 0x1e, y, buf);
    }
    LoadString(g_9212, 0x134, buf, 40);
    lstrcpy(line, buf);
    LoadString(g_9212, 0x80f, buf, 40);
    lstrcat(line, buf);
    lstrcat(line, ": ");
    fn_06_0eb8(g_1e58, buf);
    lstrcat(line, buf);
    fn_10_94c4(0, 6, PALETTERGB(255, 255, 255), g_90ea / 2, y - off / 2 + 50, line);
}

/* Fireworks: launches new rockets until fireworks_end_ms, then shows the
 * champions table [inferred]. */
/* @addr 6:5f7a */
void far fn_06_5f7a(int first)
{
    int a;
    int v;
    int sw;
    int ok;
    int r1;
    int r2;

    if (first)
        g_1c3c = 0;
    if (g_1e50 < fireworks_end_ms) {
        if (first) {
            v = rand() % 200 + 100;
            fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2 - 200, g_90ec, v, -2500,
                       32, 32, 25, 0x8c, -1);
            fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2 + 200, g_90ec, v = -v, -2500,
                       32, 32, 25, 0xc3, -1);
            fireworks_next_launch_ms = g_1e50 + 1700;
        }
        if (fireworks_next_launch_ms < g_1e50) {
            ok = 0;
            switch (sw = rand() % 3) {
            case 0:
                ok = fn_06_84fc((rand() % 2 + 1) * 10, rand() % 400 + g_90ea / 2 - 200,
                                g_90ec, 0, -2500, 32, 32, 25, rand() % 30 + 80, -1);
                break;
            case 1:
                ok = fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2, g_90ec, 300, -2500,
                                32, 32, 25, rand() % 25 + 40, rand() % 3);
                if (ok)
                    ok = fn_06_84fc((rand() % 2 + 1) * 10, g_90ea / 2, g_90ec, 300, -2500,
                                    32, 32, 25, rand() % 25 + 40, rand() % 3);
                break;
            case 2:
                a = rand() % 2;
                v = rand() % g_90ea + g_90ea;
                if (a)
                    v = -v;
                ok = fn_06_84fc((rand() % 2 + 1) * 10, a * g_90ea, g_90ec, v, -2500,
                                32, 32, 25, rand() % 58 + 30, 2);
                break;
            }
            if (ok) {
                if (rand() % 6 < 2 && sw != 1)
                    fireworks_next_launch_ms = g_1e50 + rand() % 700;
                else
                    fireworks_next_launch_ms = g_1e50 + rand() % 600 + 600;
            }
        }
    }
    r1 = fn_06_73f6();
    r2 = fn_06_7c14();
    if (fireworks_end_ms < g_1e50 && r2 && r1 && !g_1c3c) {
        g_1c3c = g_94c4 = 1;
        fn_06_62b6();
    }
}

/* Starts the champions/fireworks screen (state 5) [inferred]. */
/* @addr 6:5d58 */
void far fn_06_5d58(void)
{
    DWORD t;
    POINT p;

    if (g_90f4 == 9)
        g_94cc = 1;
    else {
        g_94cc = 0;
        fn_10_744c(0x6e);
    }
    fn_10_7d58(g_90ea / 2, g_90ec / 2);
    fn_13_65f2(1);
    fn_11_02f0();
    g_1e7c = g_1e50 + 30000;
    g_90f4 = 5;
    PatBlt(g_13dc, 0, 0, g_90ea, g_0010, BLACKNESS);
    g_94d8 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1ccL);
    g_6b04 = (REC_2E far *)GlobalLock(g_94d8);
    fn_06_6576();
    if (!g_94cc && (g_1e58 < 200000L || g_93a2 > 3))
        fn_10_7480(5, 1);
    else
        fn_10_7480(0xb, 1);
    if (!g_94cc)
        fn_06_885c(1, 1);
    if (g_94cc) {
        fireworks_end_ms = g_1e50 + 11000;
        fn_06_72d8(5, 5);
        p.y = 0;
        p.x = rand() % g_90ea + g_90ea;
        fn_06_84fc((rand() % 2 + 1) * 10, p.y * g_90ea, g_90ec + 100, p.x, -2500,
                   32, 32, 25, 0x26, 0);
        fn_06_84fc((rand() % 2 + 1) * 10, g_90ea, g_90ec + 100, -p.x, -2500,
                   32, 32, 25, 0x15, 0);
    } else {
        if (g_93a2 > 10)
            fireworks_end_ms = g_1e50;
        else {
            if (g_93a2 == 1)
                t = 8800;
            else
                t = (12 - (long)g_93a2) * 600UL;
            fireworks_end_ms = g_1e50 + t + 1000;
        }
        fn_06_72d8(3, 5);
    }
    g_94c4 = 0;
    fn_06_5f7a(1);
    g_1e7c = g_1e50 + 34000;
}
