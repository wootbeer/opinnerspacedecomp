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
    int f23;
    int f25;
    int f27;
    int f29;
    int f2b[15];
    long f49[15];
    long f85[15];
    long fc1[15];
    long ffd[15];
    int f139[60];               /* trail x per spark [inferred] */
    int f1b1[60];               /* trail y */
} REC_229;
typedef struct {                /* 0x70-byte records at far DS:1e10, DS:1e40 */
    POINT f00;
    char p04[0x0c - 0x04];
    int f0c;
    int f0e;
    char p10[0x18 - 0x10];
    int f18;
    int f1a;
    char p1c[0x70 - 0x1c];
} REC_70S;
#pragma pack()
extern REC_70S far *g_1e10;
extern REC_70S far *g_1e40;
extern int g_9150;
extern HBRUSH g_3b38[];
void far fn_06_78ea(int kind, int x, int y, int vx, int vy, int size, int n,
                    int c);

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
    char p00[0x0a];
    int f0a;
    char p0c[0x52 - 0x0c];
    char f52[0xad - 0x52];
} REC_96F0;
#pragma pack()
extern REC_96F0 g_96f0[];      /* quarter-wave sine table, 0..90 degrees [inferred] */

#pragma pack(1)
typedef struct {                /* 0x4b0-byte effect records at far DS:6b0c */
    char f00;                   /* state, 0 = free */
    char f01;
    int f02;                    /* grid size n */
    char f04;
    char f05;
    int f06;
    int f08;
    int f0a;
    int f0c[144];               /* trail x */
    int f12c[144];              /* trail y */
    char f24c[36];
    long f270[36];
    long f300[36];
    long f390[36];
    long f420[36];
} REC_FX;
typedef struct {                /* 0x70-byte records at far DS:1e30 */
    char p00[0x54];
    char f54;
    char p55[0x70 - 0x55];
} REC_1E30;
#pragma pack()
#define FX ((REC_FX far *)g_6b0c)
extern REC_1E30 far *g_1e30;
extern int g_92e8;
extern int g_913a;
extern POINT g_88c8;
extern int g_9664;
extern int g_9666;
extern int g_965e;
POINT far pascal fn_08_2bbe(POINT p);
void far fn_18_0b1e(void);

#pragma pack(1)
typedef struct {                /* 0x1a9-byte save summary [inferred] */
    long f00;
    char f04[0x18 - 0x04];      /* name */
    char f18;
    char f19;
    char f1a;
    char f1b;
    char f1c;
    char f1d;
    long f1e;
    int f22;
    int f24;
    int f26;
    int f28;
    int f2a;
    int f2c;
    int f2e;
    int f30;
    int f32;
    int f34;
    int f36[8][8];
    int fb6[8][3];
    int fe6[8][3];
    int f116[8][3];
    int f146[8];
    int f156;
    int f158;
    int f15a;
    int f15c;
    int f15e;
    int f160;
    int f162;
    int f164;
    int f166;
    int f168;
    long f16a;
    char f16e;
    char f16f;
    char f170;
    char f171;
    char f172;
    char f173;
    char f174[10];
    char f17e[10];
    char f188;
    char f189;
    char f18a;
    long f18b;
    char f18f;
    char f190[7];
    char p197[0x1a9 - 0x197];
} REC_SAVE;
typedef struct {                /* 0x15a-byte object records from DS:7092 */
    char p00[0x08];
    char f08;
    char p09[0x16 - 0x09];
    int f16;
    char p18[0x1c - 0x18];
    int f1c;
    char p1e[0x22 - 0x1e];
    int f22;
    int f24[4];
    char p2c[0x4c - 0x2c];
    int f4c;                    /* class */
    char p4e[0x5b - 0x4e];
    signed char f5b;
    signed char f5c;
    char p5d[0x60 - 0x5d];
    int f60[16];
    int f80;
    char p82[0xaa - 0x82];
    char faa;
    char fab;
    char fac[10];
    char fb6[0xc9 - 0xb6];
    char fc9;
    char pca[0xcc - 0xca];
    int fcc;
    int fce;
    int fd0;
    char pd2[0xd4 - 0xd2];
    int fd4;
    int fd6;
    char pd8[0xda - 0xd8];
    long fda;
    char pde[0xe2 - 0xde];
    char fe2;
    char pe3[0xea - 0xe3];
    char fea;
    char peb[0x15a - 0xeb];
} REC_7092;
typedef struct { int f00; char p02[0x7c - 0x02]; } REC_7CB;
typedef struct {                /* 0x7c-byte records at far DS:6e24 */
    int f00;
    int f02;
    int f04;
    int f06;
    char p08[0x1c - 0x08];
    char f1c;
    char f1d;
    char f1e[10];
    char f28[0x38 - 0x28];
    char f38[4];
    char f3c[0x64 - 0x3c];
    char f64;
    char p65[0x72 - 0x65];
    char f72;
    char f73;
    char f74;
    char f75;
    char f76;
    char p77[0x7c - 0x77];
} REC_7C;
typedef struct {                /* 0x297-byte records at far DS:69f4 */
    char p000[0xa0];
    char fa0;
    char fa1;
    char p0a2;
    char fa3;
    char p0a4[0xad - 0xa4];
    char fad;
    int fae[40];
    int ffe[0x1c0 - 0xfe >> 1];
    signed char f1c0[8];
    char p1c8[0x297 - 0x1c8];
} REC_297C;
typedef struct { char p00[0x18]; int f18; char p1a[0x1e - 0x1a]; int f1e;
                 char p20[0x44 - 0x20]; int f44; char p46[0x70 - 0x46]; } REC_70;
typedef struct { int f00; char p02[0x24 - 0x02]; int f24; char p26[0x34 - 0x26]; } REC_34;
typedef struct { char p000[0x1d0]; char f1d0; char p1d1[0x297 - 0x1d1]; } REC_297B;
#pragma pack()
extern REC_7092 g_7092[];
extern int g_939e;
extern char g_93a0;
extern int g_94a4;
extern long g_5078;
extern long g_05a8;
extern int g_91f8;
extern int g_94a2;
extern int g_931c;
extern int g_9432;
extern int g_964a;
extern int g_931a;
extern int g_9134;
extern int g_94ac;
extern int g_93ac;
extern int g_94ca;
extern int g_9346;
extern int g_967c;
extern char g_a14d[10];
extern char g_a157[10];
extern int g_3824[8][8];
extern int g_4eec[8][3];
extern int g_4fd0[8][3];
extern int g_6b10[8][3];
extern int g_6b40[8];
extern int g_945c;
extern int g_945e;
extern int g_a1cd;
extern int g_a1cf;
extern char g_a191[];
extern int g_1318;
extern int g_9156;
long far fn_10_804c(int a);

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

#pragma pack(1)
typedef struct {                /* 0x31-byte champion candidates [inferred] */
    long f00;                   /* signature */
    char f04[0x18 - 0x04];      /* name */
    char f18;
    char f19;
    char f1a;
    char f1b;
    char f1c;
    char f1d;
    long f1e;                   /* score */
    int f22;
    int f24;
    char f26[10];               /* file name without extension */
    char f30;                   /* 0 = .sav, 1 = .ded, 2 = .don */
} REC_31;
#pragma pack()
#define CH ((REC_31 far *)g_6af8)
typedef struct { char p00[0x0a]; char name[0x41 - 0x0a]; } REC_41;
extern REC_41 far *g_6e20;
extern int g_94c6;
extern HWND g_9488;
extern int g_95aa;
extern HINSTANCE g_9212;
void far fn_14_3eda(void);
int far fn_14_455c(int n);
void far fn_14_4074(void);

/* Builds the champions list from the save files (*.sav, *.ded, *.don),
 * best score first, and fills the list box g_9488 or the table at
 * g_6b04 [inferred]. */
/* @addr 6:6576 */
void far fn_06_6576(void)
{
    int k;
    int i;
    HFILE hf;
    int r;
    int n;
    int m;
    int start;
    long t;
    DWORD size;
    int unused1;
    int unused2;
    int v;
    struct find_t ft;
    HGLOBAL h;
    REC_31 far *p;
    char path[110];
    char line[110];
    OFSTRUCT of;

    fn_14_3eda();
    if (!g_6af8) {
        g_94de = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x31L);
        g_6af8 = GlobalLock(g_94de);
        g_94c6 = 0;
        h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x31L);
        p = (REC_31 far *)GlobalLock(h);
        p->f1e = g_1e58;
        p->f00 = g_939a;
        p->f22 = ((REC_7CB far *)g_6e24)[g_931c].f00;
        p->f24 = g_91f8;
        v = g_939e;
        p->f18 = v >> 8;
        p->f19 = v;
        p->f1a = g_93a0;
        t = fn_10_804c(0);
        v = (int)t;
        p->f1b = v >> 8;
        p->f1c = v;
        p->f1d = LOBYTE(HIWORD(t));
        lstrcpy(p->f04, g_380c);
        lstrcpy(p->f26, "--");
        p->f30 = 0;
        n = 1;
        for (i = 0; i < 3; i++) {
            lstrcpy(path, g_9078);
            if (i == 0) {
                lstrcat(path, g_96b8);
                lstrcat(path, "*.sav");
            } else {
                lstrcat(path, g_96c5);
                if (i == 2)
                    lstrcat(path, "*.don");
                else
                    lstrcat(path, "*.ded");
            }
            r = _dos_findfirst(path, _A_RDONLY, &ft);
            while (r == 0) {
                n++;
                lstrcpy(path, g_9078);
                if (i == 0)
                    lstrcat(path, g_96b8);
                else
                    lstrcat(path, g_96c5);
                lstrcat(path, ft.name);
                GlobalUnlock(h);
                h = GlobalReAlloc(h, size = (unsigned)((n + 1) * 0x31), GMEM_MOVEABLE | GMEM_ZEROINIT);
                p = (REC_31 far *)GlobalLock(h);
                if ((hf = OpenFile(path, &of, OF_READ)) == -1)
                    return;
                if (fn_14_4006(hf, (char huge *)&p[n - 1], 0x26L) == 0)
                    return;
                if (p[n - 1].f00 == g_939a && p[n - 1].f1e <= g_1e58)
                    p[n - 1].f00 = 0;
                lstrcpy(path, ft.name);
                for (k = 0; k < 4; k++)
                    path[lstrlen(path) - 1] = 0;
                lstrcpy(p[n - 1].f26, path);
                p[n - 1].f30 = i;
                _lclose(hf);
                r = _dos_findnext(&ft);
            }
        }
        for (i = 0; i < n; i++) {
            int best;
            long bestval;
            long sig;

            best = -1;
            bestval = -1;
            for (k = 0; k < n; k++) {
                if (!p[k].f00 || p[k].f1e < 0)
                    continue;
                if (p[k].f1e <= bestval)
                    continue;
                bestval = p[k].f1e;
                best = k;
            }
            if (best == -1)
                break;
            if (best == 0)
                g_93a2 = i + 1;
            sig = p[best].f00;
            if (best == 0)
                start = 0;
            else
                start = 1;
            for (k = start; k < n; k++)
                if (p[k].f00 == sig && p[k].f1e >= 0)
                    p[k].f1e = -1 - p[k].f1e;
        }
        for (k = 0; k < n; k++)
            if (p[k].f1e < 0)
                p[k].f1e = -1 - p[k].f1e;
        for (i = m = 0; i < n; i++) {
            long bestval;
            int best;
            long sig;

            best = -1;
            bestval = -1;
            for (k = 0; k < n; k++) {
                if (!p[k].f00)
                    continue;
                if (p[k].f1e <= bestval)
                    continue;
                bestval = p[k].f1e;
                best = k;
            }
            if (best == -1)
                break;
            size = (unsigned)((g_94c6 + 1) * 0x31);
            GlobalUnlock(g_94de);
            g_94de = GlobalReAlloc(g_94de, size, GMEM_MOVEABLE | GMEM_ZEROINIT);
            g_6af8 = GlobalLock(g_94de);
            CH[g_94c6].f1e = p[best].f1e;
            CH[g_94c6].f00 = p[best].f00;
            CH[g_94c6].f22 = p[best].f22;
            if (p[best].f22 > g_95aa - 1 || !fn_14_455c(p[best].f22)) {
                p[best].f22 = 0;
                CH[g_94c6].f22 = 0;
            }
            CH[g_94c6].f24 = p[best].f24;
            CH[g_94c6].f18 = p[best].f18;
            CH[g_94c6].f19 = p[best].f19;
            CH[g_94c6].f1a = p[best].f1a;
            CH[g_94c6].f1b = p[best].f1b;
            CH[g_94c6].f1c = p[best].f1c;
            CH[g_94c6].f1d = p[best].f1d;
            lstrcpy(CH[g_94c6].f04, p[best].f04);
            lstrcpy(CH[g_94c6].f26, p[best].f26);
            CH[g_94c6].f30 = p[best].f30;
            g_94c6++;
            sig = p[best].f00;
            if (best == 0)
                start = 0;
            else
                start = 1;
            for (k = start; k < n; k++)
                if (p[k].f00 == sig)
                    p[k].f00 = 0;
        }
        GlobalUnlock(h);
        GlobalFree(h);
    }
    for (i = 0; i < g_94c6; i++) {
        if (g_9488) {
            lstrcpy(line, "");
            fn_06_0f1a(i + 1, path);
            lstrcat(line, path);
            lstrcat(line, " - ");
            lstrcat(line, CH[i].f04);
            lstrcat(line, " - ");
            lstrcat(line, g_6e20[CH[i].f22].name);
            lstrcat(line, "\t230");
            fn_06_0eb8(CH[i].f1e, path);
            lstrcat(line, path);
            lstrcat(line, "\t292");
            fn_06_0f1a(CH[i].f18 + 1, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(CH[i].f19, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(CH[i].f1a, path);
            lstrcat(line, path);
            lstrcat(line, " - ");
            fn_06_0f1a(CH[i].f1b + 1, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(CH[i].f1c, path);
            lstrcat(line, path);
            lstrcat(line, "/");
            fn_06_0f1a(CH[i].f1d, path);
            lstrcat(line, path);
            lstrcat(line, "\t415");
            switch (CH[i].f30) {
            case 0:
                LoadString(g_9212, 0x839, path, 40);
                break;
            case 1:
                LoadString(g_9212, 0x83a, path, 40);
                break;
            case 2:
                LoadString(g_9212, 0x83b, path, 40);
                break;
            }
            lstrcat(line, path);
            lstrcat(line, "\t475");
            lstrcat(line, "(");
            lstrcat(line, CH[i].f26);
            lstrcat(line, ")");
            SendMessage(g_9488, 0x401, 0, (LPARAM)(LPSTR)line);
        } else if (g_90f4 == 5) {
            if (g_93a2 < 8 && i < 10 || i < 3
                || i > g_93a2 - 5 && i < g_93a2 + 3) {
                g_6b04[m].f2c = i + 1;
                g_6b04[m].f28 = CH[i].f1e;
                lstrcpy(g_6b04[m].name, CH[i].f04);
                lstrcat(g_6b04[m].name, " - ");
                lstrcat(g_6b04[m].name, g_6e20[CH[i].f22].name);
                m++;
            }
        }
    }
    fn_14_4074();
}

/* Fills the save summary record [inferred]. */
/* @addr 6:8eea */
void far fn_06_8eea(REC_SAVE far *p)
{
    int i;
    int j;
    int n;
    int sum;
    long t;
    int v;

    p->f170 = 0;
    if (g_7092[g_9646].fe2) {
        p->f170 = !g_7092[g_9646].faa;
        p->f170 += !g_7092[g_9646].fab * 2;
    }
    p->f171 = g_9156;
    p->f26 = g_7092[g_9646].f5b;
    p->f28 = g_7092[g_9646].f5c;
    p->f24 = g_91f8;
    p->f2a = g_94a2;
    p->f2c = g_931c;
    p->f2e = g_9432;
    p->f30 = g_964a;
    p->f32 = g_94a4;
    p->f34 = g_931a;
    p->f1e = g_1e58;
    p->f16a = g_5078;
    p->f18b = g_05a8;
    p->f15c = g_7092[g_9646].fce;
    p->f15a = g_7092[g_9646].fd0;
    p->f162 = (int)((g_7092[g_9646].fda = min(g_7092[g_9646].fda, 327670L)) / 10);
    p->f164 = g_7092[g_9646].fcc;
    p->f172 = g_7092[g_9646].f16;
    p->f22 = ((REC_7CB far *)g_6e24)[g_931c].f00;
    p->f160 = 0;
    p->f16e = g_9134;
    p->f16f = g_94ac;
    p->f166 = g_93ac;
    p->f168 = g_94ca;
    p->f18f = g_9346;
    p->f18a = g_967c;
    for (i = 0; i < 10; i++) {
        p->f174[i] = g_a14d[i];
        p->f17e[i] = g_a157[i];
    }
    p->f00 = g_939a;
    v = g_939e;
    p->f18 = v >> 8;
    p->f19 = v;
    p->f1a = g_93a0;
    t = fn_10_804c(0);
    p->f1b = HIBYTE(LOWORD(t));
    p->f1c = LOBYTE(LOWORD(t));
    p->f1d = LOBYTE(HIWORD(t));
    for (i = 0; i < g_94a4; i++)
        if (((REC_297B far *)g_69f4)[i].f1d0 == 2)
            p->f160++;
    lstrcpy(p->f04, g_380c);
    if (g_96f0[g_7092[g_9646].f4c].f0a == -1)
        n = 3;
    else
        n = 4;
    for (i = sum = 0; i < n; i++)
        sum += g_7092[g_9646].f24[i];
    sum /= n;
    if (sum > 70)
        p->f15e = 100;
    else if (sum > 45)
        p->f15e = 101;
    else if (sum > 27)
        p->f15e = 102;
    else
        p->f15e = 103;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            p->f36[i][j] = g_3824[i][j];
        for (j = 0; j < 3; j++) {
            p->fb6[i][j] = g_4eec[i][j];
            p->fe6[i][j] = g_4fd0[i][j];
            p->f116[i][j] = g_6b10[i][j];
        }
        p->f146[i] = g_6b40[i];
    }
    p->f156 = g_945c;
    p->f158 = g_945e;
    p->f190[0] = g_a1cd / 128;
    p->f190[1] = g_a1cd % 128;
    p->f190[6] = g_a1cf;
    for (i = 2; i < 6; i++)
        p->f190[i] = g_a191[i];
    p->f173 = g_1318;
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

extern HGDIOBJ g_3b4c[];

/* Moves and draws every active effect; returns 1 when none is active
 * [inferred]. */
/* @addr 6:73f6 */
int far fn_06_73f6(void)
{
    int j;
    int cnt;
    int bi;                     /* brush index */
    int last;
    int row;
    int col;
    int base;
    int k;
    int x;
    int y;
    HGDIOBJ old;
    int done;
    int u1c;

    if (!g_94dc)
        return 1;
    done = 1;
    for (k = 0; k < g_94d0; k++) {
        if (FX[k].f04 - FX[k].f05 == -4)
            fn_06_73d6(k);
        else if (FX[k].f00) {
            done = 0;
            if (FX[k].f04 <= FX[k].f05 && FX[k].f04 + 4 > FX[k].f05) {
                cnt = FX[k].f02 * FX[k].f02;
                for (j = 0; j < cnt; j++)
                    PatBlt(g_13dc, FX[k].f0c[FX[k].f0a + j], FX[k].f12c[FX[k].f0a + j],
                           4, 4, BLACKNESS);
                FX[k].f05++;
                FX[k].f0a += g_94d6;
                if (FX[k].f0a > g_94d6 * 3)
                    FX[k].f0a = 0;
            }
            if (FX[k].f04 > FX[k].f05) {
                bi = FX[k].f01 + FX[k].f05 * 9 / FX[k].f04;
                old = SelectObject(g_13dc, g_3b4c[bi]);
                last = FX[k].f02 - 1;
                cnt = (last + 1) * (last + 1);
                for (base = row = 0; base < cnt; row++, base += FX[k].f02)
                    for (col = 0; col < FX[k].f02; col++) {
                        j = col + base;
                        PatBlt(g_13dc, FX[k].f0c[FX[k].f0a + j], FX[k].f12c[FX[k].f0a + j],
                               4, 4, BLACKNESS);
                        x = (int)(FX[k].f390[j] >> 8);
                        y = (int)(FX[k].f420[j] >> 8);
                        if (FX[k].f24c[j] > 0) {
                            if (FX[k].f24c[j] <= 4) {
                                switch (FX[k].f24c[j]) {
                                case 1:
                                    old = SelectObject(g_13dc, GetStockObject(GRAY_BRUSH));
                                    break;
                                case 2:
                                    old = SelectObject(g_13dc, GetStockObject(WHITE_BRUSH));
                                    break;
                                case 3:
                                    old = SelectObject(g_13dc, GetStockObject(LTGRAY_BRUSH));
                                    break;
                                case 4:
                                    old = SelectObject(g_13dc, GetStockObject(BLACK_BRUSH));
                                    break;
                                }
                                PatBlt(g_13dc, x, y, 4, 4, PATCOPY);
                                SelectObject(g_13dc, old);
                                FX[k].f24c[j]++;
                            }
                        } else {
                            if (col == 0 || col == last || row == 0 || row == last)
                                PatBlt(g_13dc, x, y, 2, 2, PATCOPY);
                            else if (col == 1 || last - col - 1 == 0 || row == 1 || last - row - 1 == 0)
                                PatBlt(g_13dc, x, y, 3, 3, PATCOPY);
                            else
                                PatBlt(g_13dc, x, y, 4, 4, PATCOPY);
                            if (FX[k].f04 - 8 <= FX[k].f05 && FX[k].f04 - 4 >= FX[k].f05
                                && FX[k].f05 - FX[k].f04 + rand() % 4 + 4 >= 0) {
                                if (FX[k].f06 > 1000)
                                    FX[k].f24c[j] = 1;
                                else
                                    FX[k].f05 = FX[k].f04 - 2;
                            }
                        }
                        FX[k].f0c[FX[k].f0a + j] = x;
                        FX[k].f12c[FX[k].f0a + j] = y;
                        FX[k].f390[j] += FX[k].f270[j];
                        FX[k].f420[j] += FX[k].f300[j];
                        FX[k].f270[j] -= FX[k].f270[j] >> FX[k].f08;
                        FX[k].f300[j] -= FX[k].f300[j] >> FX[k].f08;
                    }
                SelectObject(g_13dc, old);
                FX[k].f05++;
                FX[k].f0a += g_94d6;
                if (FX[k].f0a > g_94d6 * 3)
                    FX[k].f0a = 0;
            }
        }
    }
    return done;
}

/* Updates the fireworks rockets and their sparks; returns 1 when none
 * is active [inferred]. */
/* @addr 6:7c14 */
int far fn_06_7c14(void)
{
    int unused1;
    int i;
    int j;
    int x;
    int y;
    int px;
    int py;
    int unused2;
    int unused3;
    HBRUSH old;
    int done;

    if (!g_94da)
        return 1;
    done = 1;
    for (i = 0; i < g_94ce; i++) {
        if (g_6b08[i].f02) {
            done = 0;
            if (g_6b08[i].f07 >= 1)
                PatBlt(g_13dc, g_6b08[i].f23, g_6b08[i].f25, 4, 4, BLACKNESS);
            if (g_6b08[i].f05 > 0) {
                x = g_6b08[i].f13 >> 8;
                y = g_6b08[i].f17 >> 8;
                if (y)
                    PatBlt(g_13dc, x, y, 4, 4, WHITENESS);
                if (g_6b08[i].f01 >= 0 && !g_9330
                    && (y < g_90ec / 4 || x < 0 || x > g_90ea))
                    g_6b08[i].f05 = 0;
                if (y > g_90ec * 3 / 4 && g_6b08[i].f1f > 0)
                    g_6b08[i].f05 = 0;
                g_6b08[i].f23 = x;
                g_6b08[i].f25 = y;
                if (g_9330) {
                    if (g_9130) {
                        g_6b08[i].f13 = (long)g_1e40->f00.x << 8;
                        g_6b08[i].f17 = (long)g_1e40->f00.y << 8;
                        g_6b08[i].f1b = (long)(g_1e40->f0c >> g_9150) << 2;
                        g_6b08[i].f1b = (long)(g_1e40->f0e >> g_9150) << 2;  /* sic */
                        if (!g_1e40->f1a)
                            g_6b08[i].f05 = 0;
                    } else {
                        g_6b08[i].f13 = (long)g_1e10[g_6b08[i].f01].f00.x << 8;
                        g_6b08[i].f17 = (long)g_1e10[g_6b08[i].f01].f00.y << 8;
                        g_6b08[i].f1b = (long)(g_1e10[g_6b08[i].f01].f0c >> g_9150) << 2;
                        g_6b08[i].f1b = (long)(g_1e10[g_6b08[i].f01].f0e >> g_9150) << 2;  /* sic */
                        if (g_1e10[g_6b08[i].f01].f18)
                            g_6b08[i].f05 = 0;
                    }
                } else {
                    g_6b08[i].f13 += g_6b08[i].f1b;
                    g_6b08[i].f17 += g_6b08[i].f1f;
                    g_6b08[i].f1b += (g_6b08[i].f1b >> g_6b08[i].f0b)
                                   - (g_6b08[i].f1b >> g_6b08[i].f0d);
                    g_6b08[i].f1f += (g_6b08[i].f1f >> g_6b08[i].f0b)
                                   - (g_6b08[i].f1f >> g_6b08[i].f0d) + g_6b08[i].f0f;
                }
            }
            if (g_6b08[i].f05 <= 0) {
                if (!g_6b08[i].f00) {
                    g_6b08[i].f00 = 1;
                    if (g_6b08[i].f01 <= 0 || rand() % 100 > 90 || g_9330) {
                        if (!g_9130)
                            fn_06_78ea(rand() % 2 * 10, (int)(g_6b08[i].f13 >> 8), (int)(g_6b08[i].f17 >> 8),
                                       (int)(g_6b08[i].f1b >> 8), (int)(g_6b08[i].f1f >> 8),
                                       rand() % 1000 + 4000, 4, 50 - rand() % 10);
                    } else {
                        fn_06_84fc(g_6b08[i].f02, (int)(g_6b08[i].f13 >> 8), (int)(g_6b08[i].f17 >> 8),
                                   rand() % 1600 + (int)g_6b08[i].f1b - 800,
                                   rand() % 1600 + (int)g_6b08[i].f1f - 800,
                                   g_6b08[i].f0b, g_6b08[i].f0d, g_6b08[i].f0f,
                                   rand() % 10 + g_6b08[i].f07 / 2, g_6b08[i].f01 - 1);
                        if (rand() % 20 < 9)
                            fn_06_84fc(g_6b08[i].f02, (int)(g_6b08[i].f13 >> 8), (int)(g_6b08[i].f17 >> 8),
                                       rand() % 1600 + (int)g_6b08[i].f1b - 800,
                                       rand() % 1600 + (int)g_6b08[i].f1f - 800,
                                       g_6b08[i].f0b, g_6b08[i].f0d, g_6b08[i].f0f,
                                       rand() % 10 + g_6b08[i].f07 / 2, g_6b08[i].f01 - 1);
                        fn_06_78ea(rand() % 2 * 10, (int)(g_6b08[i].f13 >> 8), (int)(g_6b08[i].f17 >> 8),
                                   (int)(g_6b08[i].f1b >> 8), (int)(g_6b08[i].f1f >> 8), 800, 4,
                                   50 - rand() % 10);
                    }
                }
                if (g_6b08[i].f05 < -g_94d2) {
                    g_6b08[i].f02 = 0;
                    continue;
                }
            }
            for (j = 0; j < g_94d4; j++) {
                if (g_6b08[i].f07 < j)
                    continue;
                if (g_6b08[i].f2b[j] >= g_94d2) {
                    if (!g_6b08[i].f00)
                        fn_06_8684(i, j);
                } else {
                    if (g_6b08[i].f2b[j] >= 4)
                        PatBlt(g_13dc, g_6b08[i].f139[g_6b08[i].f29 + j],
                               g_6b08[i].f1b1[g_6b08[i].f29 + j], 2, 2, BLACKNESS);
                    if (g_6b08[i].f2b[j] < g_94d2 - 4) {
                        px = g_6b08[i].f49[j] >> 8;
                        py = g_6b08[i].f85[j] >> 8;
                        if (py) {
                            old = SelectObject(g_13dc,
                                               g_3b38[g_6b08[i].f02 + g_6b08[i].f2b[j]]);
                            PatBlt(g_13dc, px, py, 2, 2, PATCOPY);
                            SelectObject(g_13dc, old);
                        }
                        g_6b08[i].f139[g_6b08[i].f29 + j] = px;
                        g_6b08[i].f1b1[g_6b08[i].f29 + j] = py;
                        g_6b08[i].f49[j] += g_6b08[i].fc1[j];
                        g_6b08[i].f85[j] += g_6b08[i].ffd[j];
                    }
                    g_6b08[i].f2b[j]++;
                }
            }
            g_6b08[i].f29 += g_94d4;
            if (g_6b08[i].f29 > g_94d4 * 3)
                g_6b08[i].f29 = 0;
            g_6b08[i].f07++;
            g_6b08[i].f05--;
        }
    }
    return done;
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

/* Starts an effect record in the 1200-byte table at DS:6b0c: a grid of
 * n x n points around (x, y) [inferred: explosion/debris cloud]. */
/* @addr 6:78ea */
void far fn_06_78ea(int kind, int x, int y, int vx, int vy, int size, int n,
                    int c)
{
    int unused;
    int i;
    int j;
    int idx;
    int k;

    if (!g_94dc || g_94c4)
        return;
    fn_10_744c(0x69);
    if (size < 1000 && (rand() & 1))
        fn_10_754a(8, x, y, 4);
    else
        fn_10_754a(0x45, x, y, 4);
    if (g_9330 && !g_9130 && g_92e8 && !g_913a && !g_1e30[g_9646].f54) {
        g_88c8.x = x;
        g_88c8.y = y;
        g_88c8 = fn_08_2bbe(g_88c8);
        fn_18_0b1e();
        g_9664 = g_9666 = 0;
        g_913a = 1;
        fn_10_754a(0x27, g_88c8.x, g_88c8.y, 4);
        g_965e = 1;
    }
    for (k = 0; k < g_94d0; k++) {
        if (FX[k].f00)
            continue;
        FX[k].f0a = 0;
        FX[k].f08 = n;
        FX[k].f01 = kind;
        FX[k].f04 = c;
        FX[k].f00 = 4;
        FX[k].f05 = 0;
        FX[k].f06 = size;
        FX[k].f02 = (n + (size >> 9) - 2) & ~1;
        if (FX[k].f02 > g_94d6)
            FX[k].f02 = g_94d6;
        if (FX[k].f02 < 4)
            FX[k].f02 = 4;
        for (j = 0; j < FX[k].f02; j++)
            for (i = 0; i < FX[k].f02; i++) {
                idx = FX[k].f02 * j + i;
                FX[k].f24c[idx] = 0;
                FX[k].f390[idx] = (long)x << 8;
                FX[k].f420[idx] = (long)y << 8;
                FX[k].f270[idx] = ((long)FX[k].f06
                    * fn_06_71b2(i * 180 / (FX[k].f02 - 1) + 90) >> 8)
                    * fn_06_71b2(j * 90 / (FX[k].f02 - 1) + 45) >> 6;
                FX[k].f270[idx] += vx << 8;
                FX[k].f300[idx] = ((long)FX[k].f06
                    * fn_06_71b2(j * 180 / (FX[k].f02 - 1) + 90) >> 8)
                    * fn_06_71b2(i * 90 / (FX[k].f02 - 1) + 45) >> 6;
                FX[k].f300[idx] += vy << 8;
            }
        return;
    }
}

extern int g_9316;
extern int g_9418;
extern int g_940c;
extern int g_9416;
extern int g_0952[];
extern int g_096c[];
extern REC_70 far *g_1e04;
extern REC_70 far *g_1e18;
extern REC_70 far *g_1e1c;
extern REC_34 g_3d5a[];
void far fn_14_421c(int n);

#define R7C ((REC_7C far *)g_6e24)
#define R297 ((REC_297C far *)g_69f4)

/* Copies the object records into the far ship table (DS:6e24) and the
 * current mission record (DS:69f4), then saves [inferred]. rank stays
 * uninitialised when no band matches (as in the original). */
/* @addr 6:99b6 */
void far fn_06_99b6(void)
{
    int i;
    int me;                     /* copy of g_9646 */
    int u8;
    int ua;
    int j;
    int v;
    int rank;
    int u12;
    int u14;
    int u16;
    int u18;
    int found;

    if (g_91f8 > 0) {
        for (i = 0; i <= g_9316; i++) {
            if (g_7092[i].fd4 == -1)
                continue;
            for (j = 0; j <= g_9316; j++)
                R7C[g_7092[i].fd4].f3c[g_7092[j].fd4] = g_7092[i].f60[j] / 10;
            for (j = 0; j < 4; j++)
                R7C[g_7092[i].fd4].f38[j] = g_7092[i].f24[j];
            if (!g_7092[i].fea)
                R7C[g_7092[i].fd4].f38[0] = 0;
            for (j = 0; j < g_7092[i].fc9; j++) {
                R7C[g_7092[i].fd4].f28[j] = g_7092[i].fb6[j];
                R7C[g_7092[i].fd4].f1e[j] = g_7092[i].fac[j];
            }
            R7C[g_7092[i].fd4].f1d = g_7092[i].fc9;
            fn_14_421c(i);
            R7C[g_7092[i].fd4].f06 = g_7092[i].f80;
            R7C[g_7092[i].fd4].f1c = g_7092[i].f1c / 40;
            R7C[g_7092[i].fd4].f74 = g_7092[i].f22;
            R7C[g_7092[i].fd4].f75 = g_7092[i].f08;
            R7C[g_7092[i].fd4].f72 = g_7092[i].faa;
            R7C[g_7092[i].fd4].f73 = g_7092[i].fab;
            R7C[g_7092[i].fd4].f04 = g_7092[i].fcc;
            R7C[g_7092[i].fd4].f02 = (int)((g_7092[i].fda = min(g_7092[i].fda, 327670L)) / 10);
            v = (int)((g_7092[i].fda * 3 + g_7092[i].fd6) / 100);
            for (j = 1; j < 11; j++)
                if (g_0952[j] <= v && g_096c[j] > v) {
                    rank = j;
                    break;
                }
            R7C[g_7092[i].fd4].f76 = rank;
            /* bare label: resets CL's register tracking (layout only) */
        reset:
            me = g_9646;
            if (!g_7092[i].fea || g_7092[i].f80 < 0 || i == me) {
                for (j = 0; j < 8; j++)
                    if (R297[g_94a2].f1c0[j] == g_7092[i].fd4)
                        R297[g_94a2].f1c0[j] = -1;
            } else {
                for (j = found = 0; j < 8; j++)
                    if (R297[g_94a2].f1c0[j] == g_7092[i].fd4)
                        found = 1;
                if (!found)
                    for (j = 0; j < 8; j++)
                        if (R297[g_94a2].f1c0[j] == -1) {
                            R297[g_94a2].f1c0[j] = g_7092[i].fd4;
                            break;
                        }
            }
        }
        g_931c = g_7092[g_9646].fd4;
        R297[g_94a2].fa3 = 0;
        R297[g_94a2].fa0 = 0;
        R297[g_94a2].fa1 = 0;
        for (i = 0; i < g_9418; i++)
            if (!g_1e1c[i].f18)
                R297[g_94a2].fa3++;
        for (i = 0; i < g_940c; i++) {
            if (g_1e04[i].f44 == 350 && !g_1e04[i].f18)
                R297[g_94a2].fa0++;
            if (g_1e04[i].f44 == 1400 && !g_1e04[i].f18)
                R297[g_94a2].fa1++;
        }
        for (i = 0; i < g_9416; i++) {
            R297[g_94a2].fae[i] = g_1e18[i].f1e;
            if (g_3d5a[i].f00 == -3)
                R297[g_94a2].fae[i] = -R297[g_94a2].fae[i];
            R297[g_94a2].ffe[i] = g_3d5a[i].f24;
        }
    }
    fn_06_885c(1, 0);
}

extern int g_92e2;
extern char g_a161;
extern char g_a162;
extern int g_95aa;
extern int g_951c;
extern int g_104c;
extern int g_104e;
extern int g_92e4;
void far fn_14_3eda(void);
int far fn_14_455c(int n);
void far fn_14_4074(void);

/* Loads the saved game [inferred]. */
/* @addr 6:930a */
int far fn_06_930a(void)
{
    int i;
    int j;
    HFILE hf;
    DWORD size;
    DWORD size2;
    char path[110];
    char name[20];
    char tmp[20];
    OFSTRUCT of;
    HGLOBAL h;
    REC_SAVE far *p;
    int hi;
    int lo;

    if (!g_920c && flow_interactive) {
        fn_16_68d6(g_0016, 0x915, -1);
        return 0;
    }
    g_939a = fn_10_804c(1);
    *(long *)&g_939e = fn_10_804c(0);
    lstrcpy(path, g_9078);
    lstrcat(path, g_96b8);
    if (flow_interactive) {
        GetPrivateProfileString(g_9690, "Restore", "", name, 9, g_96a9);
        lstrcat(path, name);
    } else
        lstrcat(path, "demogame");
    lstrcat(path, ".sav");
    hf = OpenFile(path, &of, OF_READ);
    if (hf == -1 || !(h = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 0x1a9L)))
        return 0;
    if (!(p = (REC_SAVE far *)GlobalLock(h))) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    size = GlobalSize(h);
    GlobalUnlock(h);
    if (!fn_14_4006(hf, (char huge *)(p = (REC_SAVE far *)GlobalLock(h = GlobalReAlloc(h, size, GMEM_MOVEABLE | GMEM_ZEROINIT))), size)) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    if (g_95a4) {
        GlobalUnlock(g_95a4);
        GlobalFree(g_95a4);
    }
    if (g_94ae) {
        GlobalUnlock(g_94ae);
        GlobalFree(g_94ae);
    }
    if (!(g_95a4 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size = (long)(p->f34 + 1) * 0x7c)))
        return 0;
    if (!(g_6e24 = GlobalLock(g_95a4))) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    size2 = GlobalSize(g_95a4);
    GlobalUnlock(g_95a4);
    if (!fn_14_4006(hf, (char huge *)(g_6e24 = GlobalLock(g_95a4 = GlobalReAlloc(g_95a4, size2, GMEM_MOVEABLE | GMEM_ZEROINIT))), size2)) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    if (!(g_94ae = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size = 0x297L * p->f32)))
        return 0;
    if (!(g_69f4 = GlobalLock(g_94ae))) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    size2 = GlobalSize(g_94ae);
    GlobalUnlock(g_94ae);
    if (!fn_14_4006(hf, (char huge *)(g_69f4 = GlobalLock(g_94ae = GlobalReAlloc(g_94ae, size2, GMEM_MOVEABLE | GMEM_ZEROINIT))), size2)) {
        fn_06_9932(h, hf, 0);
        return 0;
    }
    if (p->f171 != g_9156) {
        fn_06_0f1a(g_9156 = p->f171, tmp);
        WritePrivateProfileString(g_9690, "Size", tmp, g_96a9);
        g_92e2 = 1;
    }
    g_939a = p->f00;
    hi = p->f1a;
    lo = (p->f18 << 8) | p->f19;
    *(long *)&g_939e = ((long)hi << 16) | (unsigned)lo;
    g_7092[0].f5b = p->f26;
    g_7092[0].f5c = p->f28;
    g_91f8 = p->f24;
    g_94a2 = p->f2a;
    if (!R297[g_94a2].fad)
        R297[g_94a2].fad = 1;
    g_931c = p->f2c;
    g_9432 = p->f2e;
    g_964a = p->f30;
    g_94a4 = p->f32;
    g_931a = p->f34;
    g_1e58 = p->f1e;
    g_5078 = p->f16a;
    g_93ac = p->f166;
    g_94ca = p->f168;
    g_9346 = p->f18f;
    g_967c = p->f18a;
    for (i = 0; i < 10; i++) {
        g_a14d[i] = p->f174[i];
        g_a157[i] = p->f17e[i];
    }
    g_a161 = p->f188;
    g_a162 = p->f189;
    g_7092[g_9646].f16 = p->f172;
    g_7092[0].fd0 = p->f15a;
    g_7092[0].fce = p->f15c;
    g_9134 = p->f16e;
    if (!flow_interactive)
        g_9134 = 1;
    g_94ac = p->f16f;
    g_05a8 = p->f18b;
    lstrcpy(g_380c, p->f04);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            g_3824[i][j] = p->f36[i][j];
        for (j = 0; j < 3; j++) {
            g_4eec[i][j] = p->fb6[i][j];
            g_4fd0[i][j] = p->fe6[i][j];
            g_6b10[i][j] = p->f116[i][j];
        }
        g_6b40[i] = p->f146[i];
    }
    g_945c = p->f156;
    g_945e = p->f158;
    g_a1cd = p->f190[0] << 7;
    g_a1cd += p->f190[1];
    g_a1cf = p->f190[6];
    for (i = 2; i < 6; i++)
        g_a191[i] = p->f190[i];
    g_1318 = p->f173;
    fn_14_3eda();
    for (i = 0; i < g_931a; i++) {
        if (R7C[i].f64 == 7)
            R7C[i].f64 = 0;
        if (R7C[i].f00 >= g_95aa || !i && !fn_14_455c(R7C[i].f00))
            R7C[i].f00 = 1;
    }
    fn_14_4074();
    g_104e = g_104c = g_951c = 0;
    g_92e4 = 1;
    if (p->f15e < 100)
        for (i = 0; i < g_931a; i++)
            if (R7C[i].f02 < -15000)
                R7C[i].f02 = (unsigned)R7C[i].f02 / 10;
            else
                R7C[i].f02 /= 10;
    fn_06_9932(h, hf, 1);
    return 1;
}
