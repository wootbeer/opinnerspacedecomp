/* INSPACE.EXE segment 14 (selector 1068). */
#include "inspace.h"
#include <stdlib.h>
#include <io.h>

/* BEGIN STRUCTS */
typedef void (far *FNPTR)(int, int);  /* REC70 handler [inferred] */
#pragma pack(1)
/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record. Generated layout; keep in sync between seg13.c/seg14.c. */
typedef struct {
    char pad_000[0x4];
    int f_004;    /* DS:7096 */
    int f_006;    /* DS:7098 */
    char pad_008[0x6];
    int f_00e;    /* DS:70a0 */
    char pad_010[0x14];
    int f_024;    /* DS:70b6 */
    int f_026;    /* DS:70b8 */
    int f_028;    /* DS:70ba */
    char pad_02a[0x6];
    int f_030;    /* DS:70c2 */
    int f_032;    /* DS:70c4 */
    char pad_034[0x2];
    int f_036;    /* DS:70c8 */
    char pad_038[0x2];
    int f_03a;    /* DS:70cc */
    int f_03c;    /* DS:70ce */
    int f_03e;    /* DS:70d0 */
    char pad_040[0x2];
    int f_042;    /* DS:70d4 */
    char pad_044[0x8];
    int f_04c;    /* DS:70de */
    char pad_04e[0x2];
    int f_050;    /* DS:70e2 */
    int f_052;    /* DS:70e4 */
    int f_054;    /* DS:70e6 */
    int f_056;    /* DS:70e8 */
    char pad_058[0x3];
    char f_05b;    /* DS:70ed */
    char f_05c;    /* DS:70ee */
    char pad_05d[0x3];
    int f_060[16];    /* DS:70f2 */
    int f_080;    /* DS:7112 */
    char pad_082[0x10];
    long f_092;    /* DS:7124 */
    unsigned long f_096;    /* DS:7128 */
    unsigned long f_09a;    /* DS:712c */
    char pad_09e[0x4];
    long f_0a2;    /* DS:7134 */
    char pad_0a6[0x4];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    char pad_0ac[0x20];
    int f_0cc;    /* DS:715e */
    char pad_0ce[0x6];
    int f_0d4;    /* DS:7166 */
    char pad_0d6[0x4];
    int f_0da;    /* DS:716c */
    char pad_0dc[0xd];
    char f_0e9;    /* DS:717b */
    char f_0ea;    /* DS:717c */
    char f_0eb;    /* DS:717d */
    char pad_0ec[0x8];
    char f_0f4[9][9];    /* DS:7186 */
    char pad_145[0x1];
    char f_146;    /* DS:71d8 */
    char f_147;    /* DS:71d9 */
    char pad_148[0xc];
    unsigned long f_154;    /* DS:71e6 */
    char pad_158[0x2];
} OBJ15A;

/* 0x70-byte records reached through far pointers (DS:1e30, DS:1df8[]). */
typedef struct {
    POINT f_000;
    POINT f_004;
    char pad_008[0x4];
    int f_00c;
    int f_00e;
    char pad_010[0x8];
    int f_018;
    int f_01a;
    char pad_01c[0x2];
    int f_01e;
    int f_020;
    char pad_022[0x4];
    int f_026;
    int f_028;
    char pad_02a[0x1c];
    int f_046;
    char pad_048[0x9];
    char f_051;
    char pad_052[0x14];
    FNPTR f_066;
    char pad_06a[0x6];
} REC70;

/* 0x41-byte records through the far pointer at DS:6e20 [inferred]. */
typedef struct {
    char pad_000[0x1];
    char f_001;
    char f_002;
    char f_003;
    char pad_004[0x2];
    char f_006;
    char pad_007[0x2];
    char f_009;
    char f_00a[23];
    int f_021;
    char pad_023[0x1e];
} REC41;

/* 0x2c-byte records through the far pointer at DS:6e1c [inferred]. */
typedef struct {
    char pad_000[0x1b];
    char f_01b;
    char f_01c;
    char f_01d;
    char pad_01e[0x2];
    char f_020;
    int f_021;
    char pad_023[0x9];
} REC2C;

/* 0xad-byte records at DS:970a [inferred base]. */
typedef struct {
    int f_000;
    char pad_002[0xab];
} RECAD;
#pragma pack()
/* END STRUCTS */
extern OBJ15A g_7092[];
extern REC2C far *g_6e1c;
extern REC41 far *g_6e20;
extern int g_11aa;
extern int g_95aa;                 /* number of REC41 records */
extern int g_95ae;                 /* number of REC2C records */
extern int g_9498;
extern HGLOBAL g_95a6;
extern HGLOBAL g_95ac;
extern char g_1332[];
extern int g_0952[];
extern int g_096c[];

/* @addr 14:455c */
int far fn_14_455c(int k)
{
    if (g_11aa)
        return 1;
    switch (g_6e1c[g_6e20[k].f_021].f_021) {
    case 178: case 310: case 320: case 400: case 440: case 450: case 520:
    case 550: case 560: case 590: case 600: case 604: case 605: case 710:
    case 720: case 730: case 750: case 890: case 900: case 930: case 950:
        return 0;
    }
    return 1;
}

/* Pick a random entry of the DS:6e20 table and copy its name [inferred]. */
/* @addr 14:31d0 */
int far fn_14_31d0(int a, LPSTR out)
{
    int k, n, ok;

    ok = 0;
    n = rand() % 20 + 10;
    do {
        k = rand() % g_95aa;
        ok = 1;
        if (g_6e20[k].f_00a[0] == 0)
            ok = 0;
        if (!fn_14_455c(k))
            ok = 0;
        if (g_6e20[k].f_003 == 7 && a == 0)
            ok = 0;
        if (n > 0)
            n--;
    } while (n != 0 || !ok);
    lstrcpy(out, g_6e20[k].f_00a);
    return k;
}

/* @addr 14:4520 */
int far fn_14_4520(int key, int last)
{
    int i;

    for (i = 0; i <= last; i++)
        if (g_7092[i].f_0d4 == key)
            return i;
    return -1;
}

/* Read len bytes from file f into a huge buffer, 0x7fff bytes at a time.
 * Returns 1 on success, 0 on a short read [inferred]. */
/* Not yet decompiled: forward declaration (defined below). */
int far fn_14_4006(HFILE f, char huge *buf, unsigned long len);

/* Load MASTER.BOD (ShipPath in the ini) into the REC2C table [inferred].
 * Returns 0 ok, 1 already loaded, 2 open failed, 3 no memory, 4 read failed. */
/* @addr 14:3db6 */
int far fn_14_3db6(void)
{
    int u;
    HFILE fh;
    OFSTRUCT of;
    unsigned long len;
    char path[128];

    if (g_95ac)
        return 1;
    GetPrivateProfileString(g_9690, "ShipPath", "", path, 0x6d, g_96a9);
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, "MASTER.BOD");
    fh = OpenFile(path, &of, OF_READ);
    if (fh == HFILE_ERROR)
        return 2;
    g_95ae = (len = _filelength(fh)) / sizeof(REC2C);
    g_95ac = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
                         len = g_95ae * sizeof(REC2C));
    g_6e1c = (REC2C far *)GlobalLock(g_95ac);
    if (!g_95ac)
        return 3;
    if (!fn_14_4006(fh, (char huge *)g_6e1c, len)) {
        GlobalUnlock(g_95ac);
        GlobalFree(g_95ac);
        _lclose(fh);
        return 4;
    }
    _lclose(fh);
    fh = 0;
    return 0;
}

/* Load MASTER.SHP into the REC41 table [inferred]; same results. */
/* @addr 14:3eda */
int far fn_14_3eda(void)
{
    int u;
    HFILE fh;
    OFSTRUCT of;
    unsigned long len;
    char path[128];

    if (g_95a6)
        return 1;
    fn_14_3db6();
    GetPrivateProfileString(g_9690, "ShipPath", "", path, 0x6d, g_96a9);
    if (path[lstrlen(path) - 1] != '\\')
        lstrcat(path, "\\");
    lstrcat(path, "MASTER.SHP");
    fh = OpenFile(path, &of, OF_READ);
    if (fh == HFILE_ERROR) {
        g_9498++;
        return 2;
    }
    g_95aa = (len = _filelength(fh)) / sizeof(REC41);
    g_95a6 = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
                         len = g_95aa * sizeof(REC41));
    g_6e20 = (REC41 far *)GlobalLock(g_95a6);
    if (!g_95a6)
        return 3;
    if (!fn_14_4006(fh, (char huge *)g_6e20, len)) {
        GlobalUnlock(g_95a6);
        GlobalFree(g_95a6);
        _lclose(fh);
        return 4;
    }
    _lclose(fh);
    fh = 0;
    return 0;
}

/* @addr 14:4006 */
int far fn_14_4006(HFILE f, char huge *buf, unsigned long len)
{
    char huge *p;
    int n;

    p = buf;
    while (len != 0) {
        n = len > 0x7fff ? 0x7fff : (int)len;
        if (_lread(f, p, n) != n)
            return 0;
        len -= n;
        p += n;
    }
    return 1;
}

/* @addr 14:4074 */
void far fn_14_4074(void)
{
    if (g_6e20) {
        GlobalUnlock(g_95a6);
        g_6e20 = 0;
        GlobalFree(g_95a6);
        g_95a6 = 0;
    }
    if (g_6e1c) {
        GlobalUnlock(g_95ac);
        g_6e1c = 0;
        GlobalFree(g_95ac);
        g_95ac = 0;
    }
}

/* Rating of record n [inferred]: class index 1..10 whose [lo, hi) range
 * holds the score; falls off the end (returns the score in ax) when none. */
/* near-match 99%: 14:40d8 (CL adds a dead `mov ax,es` before spilling the
 * g_6e20[n] pointer and loads the 22 after it; operand orders, max forms,
 * an explicit pointer variable tried) */
int far fn_14_40d8(int n)
{
    int k, a, b, u1, c, u2;

    a = g_6e20[n].f_002 * g_6e1c[g_6e20[n].f_021].f_01b / 36;
    b = ((10 * g_6e20[n].f_001 - g_6e1c[g_6e20[n].f_021].f_01c)
         / g_6e1c[g_6e20[n].f_021].f_01b
         - 22 * g_6e1c[g_6e20[n].f_021].f_01d / max(g_6e20[n].f_001, 22)) * 2;
    c = g_1332[g_6e20[n].f_006];
    if (!(g_6e20[n].f_009 & 4))
        a = a * 3 / 4;
    if (g_6e20[n].f_009 & 8)
        a = a * 6 / 5;
    if (g_6e1c[g_6e20[n].f_021].f_020 & 2)
        a = a * 6 / 5;
    if (!(g_6e20[n].f_009 & 0x10))
        b = b * 5 / 6;
    u2 = c + b + a;
    for (k = 1; k < 11; k++)
        if (g_0952[k] <= u2 && g_096c[k] > u2)
            return k;
}
