/* INSPACE.EXE segment 14 (selector 1068). */
#include "inspace.h"
#include <stdlib.h>
#include <io.h>

/* BEGIN STRUCTS */
typedef void (far *FNPTR)(int, int);  /* REC70 handler [inferred] */
typedef int (far *FNSPLIT)(int, int); /* REC70 +5e, e.g. fn_07_570a */
typedef void (far *FNVOID)(void);     /* REC70 +62, e.g. fn_11_3914 */
#pragma pack(1)
/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record. Generated layout; keep in sync between seg13.c/seg14.c. */
typedef struct {
    int f_000;    /* DS:7092 */
    int f_002;    /* DS:7094 */
    int f_004;    /* DS:7096 */
    int f_006;    /* DS:7098 */
    int f_008;    /* DS:709a */
    int f_00a;    /* DS:709c */
    int f_00c;    /* DS:709e */
    int f_00e;    /* DS:70a0 */
    char pad_010[0x2];
    int f_012;    /* DS:70a4 */
    int f_014;    /* DS:70a6 */
    char pad_016[0x4];
    int f_01a;    /* DS:70ac */
    int f_01c;    /* DS:70ae */
    char pad_01e[0x4];
    int f_022;    /* DS:70b4 */
    int f_024;    /* DS:70b6 */
    int f_026;    /* DS:70b8 */
    int f_028;    /* DS:70ba */
    char pad_02a[0x6];
    int f_030;    /* DS:70c2 */
    int f_032;    /* DS:70c4 */
    int f_034;    /* DS:70c6 */
    int f_036;    /* DS:70c8 */
    int f_038;    /* DS:70ca */
    int f_03a;    /* DS:70cc */
    int f_03c;    /* DS:70ce */
    int f_03e;    /* DS:70d0 */
    char pad_040[0x2];
    int f_042;    /* DS:70d4 */
    char pad_044[0x8];
    int f_04c;    /* DS:70de */
    int f_04e;    /* DS:70e0 */
    int f_050;    /* DS:70e2 */
    int f_052;    /* DS:70e4 */
    int f_054;    /* DS:70e6 */
    int f_056;    /* DS:70e8 */
    char f_058;    /* DS:70ea */
    char pad_059[0x1];
    char f_05a;    /* DS:70ec */
    char f_05b;    /* DS:70ed */
    char f_05c;    /* DS:70ee */
    char f_05d;    /* DS:70ef */
    char pad_05e[0x1];
    char f_05f;    /* DS:70f1 */
    int f_060[16];    /* DS:70f2 */
    int f_080;    /* DS:7112 */
    unsigned long f_082;    /* DS:7114 */
    char pad_086[0xc];
    long f_092;    /* DS:7124 */
    unsigned long f_096;    /* DS:7128 */
    unsigned long f_09a;    /* DS:712c */
    int f_09e;    /* DS:7130 */
    int f_0a0;    /* DS:7132 */
    long f_0a2;    /* DS:7134 */
    char pad_0a6[0x4];
    char f_0aa;    /* DS:713c */
    char f_0ab;    /* DS:713d */
    char f_0ac[10];    /* DS:713e */
    char f_0b6[16];    /* DS:7148 */
    char pad_0c6[0x3];
    char f_0c9;    /* DS:715b */
    char pad_0ca[0x1];
    char f_0cb;    /* DS:715d */
    int f_0cc;    /* DS:715e */
    char pad_0ce[0x2];
    int f_0d0;    /* DS:7162 */
    char pad_0d2[0x2];
    int f_0d4;    /* DS:7166 */
    int f_0d6;    /* DS:7168 */
    char pad_0d8[0x2];
    long f_0da;    /* DS:716c */
    char pad_0de[0x2];
    char f_0e0;    /* DS:7172 */
    char f_0e1;    /* DS:7173 */
    char f_0e2;    /* DS:7174 */
    char f_0e3;    /* DS:7175 */
    char f_0e4;    /* DS:7176 */
    char f_0e5;    /* DS:7177 */
    char f_0e6;    /* DS:7178 */
    char f_0e7;    /* DS:7179 */
    char f_0e8;    /* DS:717a */
    char f_0e9;    /* DS:717b */
    char f_0ea;    /* DS:717c */
    char f_0eb;    /* DS:717d */
    char f_0ec[8];    /* DS:717e */
    char f_0f4[9][9];    /* DS:7186 */
    char f_145;    /* DS:71d7 */
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
    int f_010;
    int f_012;
    char pad_014[0x4];
    int f_018;
    int f_01a;
    char pad_01c[0x2];
    int f_01e;
    int f_020;
    int f_022;
    int f_024;
    int f_026;
    int f_028;
    char pad_02a[0x2];
    int f_02c;
    char f_02e;
    char f_02f;
    char pad_030[0x2];
    int f_032;
    int f_034;
    int f_036;
    int f_038;
    int f_03a;
    int f_03c;
    char pad_03e[0x4];
    int f_042;
    int f_044;
    int f_046;
    int f_048;
    int f_04a;
    unsigned long f_04c;
    char pad_050[0x1];
    char f_051;
    char f_052;
    char f_053;
    char f_054;
    char pad_055[0x9];
    FNSPLIT f_05e;
    FNVOID f_062;
    FNPTR f_066;
    char pad_06a[0x6];
} REC70;

/* 0x41-byte records through the far pointer at DS:6e20 [inferred]. */
typedef struct {
    char f_000;
    char f_001;
    char f_002;
    char f_003;
    char f_004[2];
    char f_006;
    char f_007;
    char f_008;
    char f_009;
    char f_00a[21];
    int f_01f;
    int f_021;
    char pad_023[0x15];
    char f_038[9];
} REC41;

/* 0x2c-byte records through the far pointer at DS:6e1c [inferred]. */
typedef struct {
    char pad_000[0x15];
    int f_015;
    int f_017;
    char f_019;
    char f_01a;
    char f_01b;
    char f_01c;
    char f_01d;
    char f_01e;
    char f_01f;
    char f_020;
    int f_021;
    char f_023[9];
} REC2C;

/* 0xad-byte records at DS:96ea (base as in seg03.c/seg11.c) [inferred]. */
typedef struct {
    char f_000;
    char pad_001[0x1];
    char f_002;
    char pad_003[0x3];
    int f_006;
    char pad_008[0x16];
    int f_01e;
    int f_020;
    char pad_022[0x8];
    int f_02a;
    char pad_02c[0x2];
    int f_02e;
    char pad_030[0x20];
    int f_050;
    int f_052;
    int f_054;
    int f_056;
    char pad_058[0x14];
    char f_06c[37];
    long f_091;
    char pad_095[0x18];
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
extern RECAD g_96ea[];
extern REC70 far *g_1df8[];
extern int g_9324;
extern int g_9646;
extern int g_9156;
extern int g_90f4;
extern int g_931e;
extern unsigned long g_1e68;
extern int g_39e8[];
extern int g_4ed8[];

/* 0x7c-byte records through the far pointer at DS:6e24 (REC_7C in
 * seg04.c). */
typedef struct {
    int f_00;
    int f_02;
    int f_04;
    int f_06;
    int f_08[5];
    char f_12[5];
    char f_17[5];
    char f_1c;
    char f_1d;
    char f_1e[10];
    char f_28[10];
    char pad_32[0x1];
    char f_33;
    char pad_34[0x38 - 0x34];
    char f_38[4];
    char f_3c[40];
    char f_64;
    char pad_65[0x72 - 0x65];
    char f_72;
    char f_73;
    char f_74;
    char f_75;
    char pad_76[0x77 - 0x76];
    char f_77;
    char f_78;
    char f_79;
    char f_7a;
    char f_7b;
} REC7C;
extern REC7C far *g_6e24;

/* 0x50-byte records at DS:2f5e [inferred]. */
typedef struct {
    int f_00;
    char pad_02[0x50 - 0x02];
} REC50;
extern REC50 g_2f5e[];

void far fn_10_86e2(int i);
void far fn_10_5d3c(int i);
void far fn_10_533a(int a);
int far fn_10_86ca(void);                  /* seg10.c declares void */
void far fn_10_6ee6(int a, int b, char far *s, int c, int d, long e,
                    int g, int h, char i, char j, char k, int l);

extern int g_9316;
int far fn_09_88ba(int x);

#pragma pack(1)
/* 0x297-byte records through the far pointer at DS:69f4 (REC_297 in
 * seg07.c). */
typedef struct {
    char pad_000[0x1c0];
    char f_1c0[16];
    char pad_1d0[0x297 - 0x1d0];
} REC297;
#pragma pack()
extern REC297 far *g_69f4;
/* 0x50-byte records at DS:2f4c [inferred]. */
typedef struct {
    char pad_00[0x3e];
    int f_3e;                       /* DS:2f8a */
    char pad_40[0x50 - 0x40];
} REC50B;
extern REC50B g_2f4c[];
extern int g_95b2;
extern int g_95b4;
extern int g_931a;
extern HGLOBAL g_95a4;
extern int g_94a4;
extern int g_94a2;
extern int g_9334;
extern int g_91f8;
extern int g_0992;
void far fn_09_5be0(int n, int k);
/* Record n's view at DS:7090: the 2-byte field just below each OBJ15A. */
typedef struct {
    int f_m2;
    char pad[0x158];
} OBJ15A_M2;
extern OBJ15A_M2 g_7090[];
extern int g_4eec[][3];
extern long g_8e08[];
extern int g_9134;
extern int g_9320;
extern int flow_interactive;       /* DS:95bc */

extern int g_104e;
extern int g_9346;
void far fn_03_00f4(int a, int s, int k);
void far fn_12_6d64(int n, int k);
void far fn_14_1b84(int n, int c, int t, int g);
#pragma pack(1)
/* View of the class records (RECAD) at DS:96d6, 0x14 bytes below the
 * usual base DS:96ea; fields a_XXX are at RECAD offset XXX (mXX below). */
typedef struct {
    int a_m14;
    char pad_m12[0x2];
    int a_m10;
    int a_m0e;
    int a_m0c;
    int a_m0a;
    int a_m08;
    int a_m06;
    int a_m04;
    int a_m02;
    int a_000;
    int a_002;
    char pad_004[0x2];
    int a_006;
    int a_008;
    int a_00a;
    int a_00c;
    int a_00e;
    int a_010;
    char pad_012[0x2];
    int a_014;
    int a_016;
    int a_018;
    int a_01a;
    char pad_01c[0x2];
    int a_01e;
    char pad_020[0x4];
    int a_024;
    int a_026;
    int a_028;
    int a_02a;
    int a_02c;
    int a_02e;
    int a_030;
    int a_032;
    int a_034;
    int a_036;
    char pad_038[0x14];
    int a_04c;
    int a_04e;
    char pad_050[0x8];
    char a_058[20];
    char a_06c[15];
    char a_07b[15];
    char a_08a;
    char a_08b;
    char a_08c[2];
    char a_08e;
    int a_08f;
    int a_091;
    int a_093;
    char pad_095[0x4];
} RECADV;
#pragma pack()
extern RECADV g_96d6[];
void far fn_10_754a(int a, int b, int c, int d);
void far fn_16_08e4();
void far fn_11_37a0();
int far fn_08_45e0();

#define SC(n) ((n) << g_9156 >> 1)

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
/* @addr 14:40d8 */
int far fn_14_40d8(int n)
{
    int k, a, b, u1, c, u2;

    a = g_6e20[n].f_002 * g_6e1c[g_6e20[n].f_021].f_01b / 36;
    u1 = 22 * g_6e1c[g_6e20[n].f_021].f_01d / max(g_6e20[n].f_001, 22);
    b = ((10 * g_6e20[n].f_001 - g_6e1c[g_6e20[n].f_021].f_01c)
         / g_6e1c[g_6e20[n].f_021].f_01b - u1) * 2;
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

/* (Re)load the sprite of object n [inferred]. */
/* @addr 14:11a8 */
void far fn_14_11a8(int n)
{
    int slot, c, j, r, v, rec, u;
    char sel;
    char buf[30];
    int f2, f1;

    c = g_7092[n].f_04c;
    slot = n + 40;
    if (g_7092[n].f_04e != n && g_7092[g_7092[n].f_04e].f_0ab
        && g_7092[g_7092[n].f_04e].f_0aa) {
        if (g_96ea[c].f_02e) {
            fn_10_86e2(n);
            fn_10_5d3c(n);
        }
        goto done;
    }
    if (g_39e8[slot] && g_7092[n].f_0aa && g_7092[n].f_0ab)
        goto done;
    if (g_39e8[slot])
        f1 = 1;
    else
        f1 = 0;
    if (g_7092[n].f_0e2)
        sel = 0;
    else
        sel = 2;
    if (g_7092[n].f_0e7)
        sel = 1;
    if (g_90f4 == 1 && g_1e68 > 0) {
        if ((g_931e == 1 && n != g_9646) || g_931e == 2)
            f2 = 1;
        else
            f2 = 0;
    } else if (g_931e == 2)
        f2 = 1;
    else
        f2 = 0;
    fn_10_6ee6(slot, g_96ea[c].f_01e, g_96ea[c].f_06c, 1, 0x63,
               g_96ea[c].f_091, 1, 0, g_96ea[c].f_000, g_96ea[c].f_002,
               sel, f2);
    r = fn_10_86ca();
    if (r & 1)
        v = 5;
    else
        v = 6;
    if (g_7092[n].f_0d4 != -1) {
        g_6e24[g_7092[n].f_0d4].f_7a = (char)r;
        g_6e24[g_7092[n].f_0d4].f_7b = (char)v;
    } else if (!f1) {
        g_1df8[g_9324][n].f_022 = r;
        g_1df8[g_9324][n].f_024 = v;
    }
    u = g_7092[n].f_0d4;
    if (u != -1)
        rec = g_6e24[u].f_00;
    else
        rec = g_4ed8[g_7092[n].f_05c];
    if (g_95a6) {
        g_96ea[c].f_050 = g_6e1c[g_6e20[rec].f_021].f_01e - r / 2 - g_9156;
        g_96ea[c].f_052 = g_6e1c[g_6e20[rec].f_021].f_01f - r / 2;
        g_96ea[c].f_054 = -(g_96ea[c].f_050 + g_9156);
        g_96ea[c].f_056 = g_96ea[c].f_052;
    }
done:
    g_7092[n].f_0aa = g_7092[n].f_0ab = 1;
    for (j = 0; j < g_7092[n].f_0c9; j++)
        if (g_2f5e[g_7092[n].f_0b6[j]].f_00)
            fn_10_533a(g_7092[n].f_0b6[j]);
}

/* Update object n's per-object scores and its top-5 list in g_6e24
 * [inferred]. */
/* @addr 14:421c */
void far fn_14_421c(int n)
{
    int s2, s1, j, i, m, u, flag, mx2, mx;
    char b1, b2, k;

    k = g_7092[n].f_0d4;
    if (k != -1) {
        for (i = 0; i <= g_9316; i++)
            g_7092[n].f_060[i + 8] = fn_09_88ba(g_7092[n].f_060[i + 8]);
        for (j = 0; j < 5; j++)
            for (i = 0; i <= g_9316; i++)
                if (g_6e24[k].f_17[j] == g_7092[i].f_0d4)
                    g_6e24[k].f_08[j] = g_7092[n].f_060[i + 8];
        for (j = 0; j <= g_9316; j++) {
            b2 = b1 = 0;
            mx = mx2 = 0;
            s1 = 0;
            s2 = 0;
            if (j != n && g_7092[j].f_0ea) {
                for (i = 1; i <= 5; i++) {
                    s2 += g_7092[n].f_0f4[j][i];
                    if (g_7092[n].f_0f4[j][i] > mx && i != 2) {
                        mx = g_7092[n].f_0f4[j][i];
                        b2 = i;
                    }
                }
                for (i = 6; i <= 8; i++) {
                    s1 += g_7092[n].f_0f4[j][i];
                    if (g_7092[n].f_0f4[j][i] > mx2) {
                        mx2 = g_7092[n].f_0f4[j][i];
                        b1 = i;
                    }
                }
                if ((8 - g_7092[n].f_05b) * s1 < (8 - g_7092[n].f_05c) * s2) {
                    if (g_7092[n].f_060[j + 8] <= s2) {
                        g_7092[n].f_0ec[j] = b2;
                        g_7092[n].f_060[j + 8] = s2;
                        flag = 1;
                    } else
                        flag = 0;
                } else {
                    if (g_7092[n].f_060[j + 8] <= s1) {
                        g_7092[n].f_0ec[j] = b1;
                        g_7092[n].f_060[j + 8] = s1;
                        flag = 1;
                    } else
                        flag = 0;
                }
            } else {
                g_7092[n].f_0ec[j] = 0;
                g_7092[n].f_060[j + 8] = 0;
            }
        }
        if (flag) {
            for (i = 0; i <= g_9316; i++)
                for (j = 0; j < 5; j++)
                    if (g_6e24[k].f_08[j] < g_7092[n].f_060[i + 8]) {
                        for (m = 4; m > j; m--) {
                            g_6e24[k].f_12[m] = g_6e24[k].f_12[m - 1];
                            g_6e24[k].f_08[m] = g_6e24[k].f_08[m - 1];
                            g_6e24[k].f_17[m] = g_6e24[k].f_17[m - 1];
                        }
                        g_6e24[k].f_12[j] = g_7092[n].f_0ec[i];
                        g_6e24[k].f_08[j] = g_7092[n].f_060[i + 8];
                        g_6e24[k].f_17[j] = g_7092[i].f_0d4;
                        j = 5;
                    }
        }
    }
}

/* Give object n a g_6e24 record (new, or the weakest unused one when
 * full) built from ship type s, or reuse k0 [inferred]. */
/* @addr 14:0dd6 */
void far fn_14_0dd6(int n, int s, int k0)
{
    int i, j, m, best, bi, k;

    if (g_95b4 > g_95b2) {
        if (g_931a > 0x26) {
            int flag;

            best = 1000;
            bi = -1;
            for (j = 1; j < 40; j++)
                if (g_6e24[j].f_06 < best) {
                    flag = 1;
                    for (m = 0; m < n; m++)
                        if (g_7092[m].f_0d4 == j)
                            flag = 0;
                    if (flag) {
                        best = g_6e24[j].f_06;
                        bi = j;
                    }
                }
            if (bi == -1) {
                MessageBeep(0);
                bi = 10;
            }
            for (i = 0; i < g_94a4; i++)
                for (m = 0; m < 8; m++)
                    if (g_69f4[i].f_1c0[m] == bi)
                        g_69f4[i].f_1c0[m] = -1;
            k = bi;
        } else {
            g_931a++;
            GlobalUnlock(g_95a4);
            g_95a4 = GlobalReAlloc(g_95a4, (long)(g_931a + 1) * 0x7c, GHND);
            g_6e24 = (REC7C far *)GlobalLock(g_95a4);
            k = g_931a;
        }
        g_6e24[k].f_00 = s;
        for (j = 0; j < 40; j++)
            g_6e24[k].f_3c[j] = 0;
        for (j = 0; j < 4; j++)
            g_6e24[k].f_38[j] = 100;
        for (j = 0; j < 5; j++) {
            g_6e24[k].f_12[j] = 0;
            g_6e24[k].f_08[j] = 0;
            g_6e24[k].f_17[j] = -1;
        }
        if (g_6e20[s].f_006) {
            g_6e24[k].f_1d = 2;
            if (g_11aa == 0 && g_2f4c[g_6e20[s].f_006].f_3e != -1)
                g_6e24[k].f_28[1] = g_2f4c[g_6e20[s].f_006].f_3e;
            else
                g_6e24[k].f_28[1] = g_6e20[s].f_006;
            g_6e24[k].f_1e[1] = 20;
        } else
            g_6e24[k].f_1d = 1;
        g_6e24[k].f_06 = 15;
        g_6e24[k].f_73 = 1;
        g_6e24[k].f_72 = g_6e24[k].f_73;
        g_6e24[k].f_74 = 1;
        g_6e24[k].f_75 = 1;
        g_6e24[k].f_1c = g_6e20[s].f_000;
        g_6e24[k].f_02 = rand() % ((g_9334 + 1) * 10) + 10;
        g_6e24[k].f_04 = rand() % ((g_9334 + 1) * 50) + 150;
        g_6e24[k].f_77 = 0;
        g_6e24[k].f_64 = g_6e20[s].f_003;
        fn_09_5be0(n, k);
    } else {
        k = k0;
        for (i = 0; i < g_94a4; i++)
            for (j = 0; j < 10; j++)
                if (g_69f4[i].f_1c0[j] == k) {
                    g_69f4[i].f_1c0[j] = -1;
                    break;
                }
        for (j = 0; j < 8; j++)
            if (g_69f4[g_94a2].f_1c0[j] == -1) {
                g_69f4[g_94a2].f_1c0[j] = k;
                break;
            }
        if (g_6e24[k].f_79 < g_91f8 - 1)
            g_6e24[k].f_02 += min((g_91f8 - g_6e24[k].f_79) * (g_9334 + 15), 200);
    }
    g_7092[n].f_0d4 = k;
    g_0992 += 40;
}

/* Set up object n for a new mission from its pilot record [inferred]. */
/* @addr 14:1430 */
void far fn_14_1430(int n)
{
    int i, u1, t, j, c, g;

    t = g_7092[n].f_0d4;
    if (t != -1)
        g = g_6e24[t].f_00;
    else
        g = g_4ed8[g_7092[n].f_05c];
    if (g_95aa - 1 < g) {
        g_6e24[t].f_00 = 0;
        g = g_6e24[t].f_00;
    }
    c = g_7092[n].f_04c;
    if (t != -1)
        g_96ea[c].f_020 = g_6e24[t].f_64;
    else
        g_96ea[c].f_020 = g_6e20[g].f_003;
    g_7092[n].f_145 = 0;
    fn_14_1b84(n, c, t, g);
    for (j = 0; j <= 8; j++)
        for (i = 0; i <= g_9316; i++)
            g_7092[n].f_0f4[i][j] = 0;
    g_7092[n].f_002 = n + 40;
    g_7092[n].f_0b6[0] = 0;
    g_7092[n].f_0ac[0] = 1;
    if (t != -1)
        g_7092[n].f_0c9 = g_6e24[t].f_1d;
    g_8e08[n] = 1000000L;
    for (i = g_7092[n].f_0c9; i < 10; i++)
        g_7092[n].f_0b6[i] = 0;
    for (i = 0; i < 2; i++)
        (&g_7092[n].f_05b)[i] = g_96ea[c].f_06c[0x20 + i];
    g_7092[n].f_030 = g_7092[n].f_004 = 8;
    g_7092[n].f_032 = g_7092[n].f_006 = 0;
    g_7092[n].f_036 = 3;
    g_7092[n].f_03a = 2;
    g_7092[n].f_146 = g_7092[n].f_147 = -1;
    g_7092[n].f_092 = 0;
    g_7092[n].f_0e8 = 0;
    g_1df8[g_9324][n].f_028 = 0;
    g_1df8[g_9324][n].f_051 = 0;
    g_7092[n].f_00e = 0;
    g_7092[n].f_000 = 0;
    g_7092[n].f_0e6 = 0;
    if (n == g_9646 && g_9134 != 0)
        g_7092[n].f_050 = 7;
    else
        g_7092[n].f_050 = 0;
    if (g_96ea[c].f_020 == 7 && g_7092[n].f_05c > 1) {
        g_7092[n].f_050 = 0x14;
        g_7092[n].f_052 = g_9324;
        g_7092[n].f_054 = g_9646;
    }
    if (g_9320 == 7 && (n != g_9646 || !flow_interactive)) {
        g_7092[n].f_050 = 4;
        g_7092[n].f_052 = 14;
        g_7092[n].f_054 = g_9646;
        if (n == g_9646)
            fn_03_00f4(n, 14, g_7092[n].f_054 = 1);
        else
            fn_03_00f4(n, 14, g_9646);
        g_7092[n].f_056 = n;
    }
    if (t != -1) {
        g_7092[n].f_0c9 = g_6e24[t].f_1d;
        for (j = 1; j < g_6e24[t].f_1d; j++) {
            if (g_11aa == 0 && g_2f4c[g_6e24[t].f_28[j]].f_3e != -1)
                g_6e24[t].f_28[j] = g_2f4c[g_6e24[t].f_28[j]].f_3e;
            g_7092[n].f_0b6[j] = g_6e24[t].f_28[j];
            g_7092[n].f_0ac[j] = g_6e24[t].f_1e[j];
        }
        if (g_104e)
            fn_12_6d64(n, 13);
        for (j = 0; j < 4; j++)
            (&g_7092[n].f_024)[j] = g_6e24[t].f_38[j];
        for (i = 0; i <= g_9316; i++) {
            g_7092[n].f_060[i + 8] = 0;
            g_7092[n].f_0ec[i] = 0;
        }
        for (j = 0; j < 5; j++)
            for (i = 0; i <= g_9316; i++)
                if (g_6e24[t].f_17[j] == g_7092[i].f_0d4
                    && g_6e24[t].f_08[j] > 1 && i != n) {
                    g_7092[n].f_0ec[i] = g_6e24[t].f_12[j];
                    g_7092[n].f_060[i + 8] = g_6e24[t].f_08[j];
                }
        for (j = 0; j <= g_9316; j++)
            for (i = 0; i < 3; i++)
                if (g_4eec[g_96ea[c].f_020][i] == g_7092[j].f_0d4
                    && g_7092[j].f_0d4 >= 0
                    && g_7092[n].f_060[j + 8] < 15) {
                    g_7092[n].f_0ec[j] = 4;
                    g_7092[n].f_060[j + 8] += 15;
                }
        g_7092[n].f_01c = 40 * (unsigned char)g_6e24[t].f_1c;
        if (n != g_9646)
            g_7092[n].f_01c = max(g_7092[n].f_01c, g_96ea[c].f_006 * 2 / 3);
        if (g_96ea[c].f_006 < g_7092[n].f_01c) {
            g_7092[n].f_01c = g_96ea[c].f_006;
            g_6e24[t].f_1c = g_96ea[c].f_006 / 40;
        }
        if (g_7092[g_9646].f_0e2 == 0)
            g_7092[n].f_0aa = g_7092[n].f_0ab = 1;
        else {
            g_7092[n].f_0aa = g_6e24[t].f_72;
            g_7092[n].f_0ab = g_6e24[t].f_73;
        }
        g_7092[n].f_022 = g_6e24[t].f_74;
        g_7092[n].f_008 = g_6e24[t].f_75;
        g_7092[n].f_0da = 10L * g_6e24[t].f_02;
        g_7092[n].f_0cc = g_6e24[t].f_04;
        g_7092[n].f_080 = g_6e24[t].f_06;
        g_7090[n].f_m2 = 0;
        if (g_6e24[t].f_79 - g_91f8 == -1)
            g_6e24[t].f_78++;
        else if (g_6e24[t].f_78 > 1) {
            g_7090[n].f_m2 = 4;
            g_6e24[t].f_78 = 1;
        } else
            g_6e24[t].f_78 = 0;
        if (g_6e24[t].f_79 != g_91f8)
            g_6e24[t].f_77++;
        g_6e24[t].f_79 = (char)g_91f8;
        for (j = 0; j < g_9316; j++)
            g_7092[n].f_060[j] = 10 * g_6e24[t].f_3c[g_7092[j].f_0d4];
    } else {
        g_7092[n].f_0c9 = 3;
        g_7092[n].f_0b6[1] = 15;
        g_7092[n].f_0ac[1] = 1;
        g_7092[n].f_0b6[2] = g_6e20[g].f_006;
        g_7092[n].f_0ac[2] = 20;
        if (g_7092[n].f_05c == 0) {
            g_7092[n].f_050 = 0x17;
            g_7092[n].f_052 = g_9324;
            g_7092[n].f_054 = fn_14_4520(g_9346, g_9316);
            g_7092[n].f_0cb = (char)g_7092[n].f_054;
            if (g_7092[n].f_0cb < 0)
                g_7092[n].f_0cb = (char)(g_7092[n].f_054 = g_9646);
            g_7092[n].f_0eb = 1;
        }
        for (j = 0; j < 4; j++)
            (&g_7092[n].f_024)[j] = 100;
        for (j = 0; j < 5; j++) {
            g_7092[n].f_0ec[j] = 0;
            g_7092[n].f_060[j + 8] = 0;
        }
        g_7092[n].f_01c = 40 * g_6e20[g].f_000;
        g_7092[n].f_0ab = g_7092[n].f_0aa = 1;
        g_7092[n].f_008 = g_7092[n].f_022 = 2;
        g_7092[n].f_0cc = 100;
        g_7092[n].f_0da = 0;
        g_7092[n].f_080 = 0;
        for (j = 0; j < g_9316; j++)
            g_7092[n].f_060[j] = 0;
    }
}


/* Fill class record c (and object n) from body g and pilot t [inferred]. */
/* @addr 14:1b84 */
void far fn_14_1b84(int n, int c, int t, int g)
{
    int i;

    g_96d6[c].a_036 = 1;
    g_96d6[c].a_000 = g_6e20[g].f_007;
    g_96d6[c].a_002 = g_6e20[g].f_008;
    if (g_96d6[c].a_000 == 12)
        g_96d6[c].a_091 = g_6e1c[g_6e20[g].f_021].f_015;
    else
        g_96d6[c].a_091 = 0;
    if (g_96d6[c].a_002 == 12)
        g_96d6[c].a_093 = g_6e1c[g_6e20[g].f_021].f_017;
    else
        g_96d6[c].a_093 = 0;
    lstrcpy(g_96d6[c].a_06c, g_6e1c[g_6e20[g].f_021].f_023);
    lstrcpy(g_96d6[c].a_07b, g_6e20[g].f_038);
    g_96d6[c].a_m14 = -g_6e1c[g_6e20[g].f_021].f_019;
    g_96d6[c].a_026 = 5 * g_6e20[g].f_001;
    g_96d6[c].a_028 = g_6e1c[g_6e20[g].f_021].f_01c;
    g_96d6[c].a_m0e = g_6e20[g].f_002 / 4;
    g_96d6[c].a_m0c = g_6e20[g].f_002 / 5;
    g_96d6[c].a_m0a = g_6e20[g].f_002 / 5;
    g_96d6[c].a_m10 = g_6e20[g].f_002 / 4;
    g_96d6[c].a_m06 = g_6e20[g].f_002 / 5;
    g_96d6[c].a_m04 = g_6e20[g].f_002 / 4;
    g_96d6[c].a_m02 = g_6e20[g].f_002 / 5;
    g_96d6[c].a_m08 = g_6e20[g].f_002 / 4;
    g_96d6[c].a_08e = g_6e20[g].f_002;
    g_96d6[c].a_006 = 40 * g_6e20[g].f_000;
    g_96d6[c].a_008 = g_6e1c[g_6e20[g].f_021].f_01d;
    g_96d6[c].a_00a = 0;
    g_96d6[c].a_00c = 1;
    g_96d6[c].a_00e = 2;
    if (g_6e1c[g_6e20[g].f_021].f_020 & 8)
        g_96d6[c].a_030 = 1;
    else
        g_96d6[c].a_030 = 0;
    if (g_6e1c[g_6e20[g].f_021].f_020 & 4)
        g_96d6[c].a_010 = 3;
    else if (g_6e20[g].f_009 & 8)
        g_96d6[c].a_010 = 4;
    else if (g_6e1c[g_6e20[g].f_021].f_020 & 2)
        g_96d6[c].a_010 = 5;
    else
        g_96d6[c].a_010 = -1;
    if (!(g_6e1c[g_6e20[g].f_021].f_020 & 4))
        g_7092[n].f_0aa = g_7092[n].f_0ab = 0;
    g_96d6[c].a_014 = 7;
    if ((g_96d6[c].a_016 = g_6e20[g].f_01f) > 0)
        fn_10_754a(g_96d6[c].a_016, 0, 0, 5);
    g_96d6[c].a_01a = 10 * g_6e1c[g_6e20[g].f_021].f_01b;
    g_96d6[c].a_01a = g_96d6[c].a_01a * (g_6e20[g].f_002 / 4 + 100L) / 100;
    g_96d6[c].a_018 = g_96d6[c].a_01a / 22;
    g_96d6[c].a_01e = g_6e1c[g_6e20[g].f_021].f_021;
    if (g_6e20[g].f_009 & 0x10)
        g_96d6[c].a_02a = 1;
    else
        g_96d6[c].a_02a = 0;
    if (g_6e20[g].f_009 & 1)
        g_96d6[c].a_02c = 0;
    else
        g_96d6[c].a_02c = 1;
    if (g_6e20[g].f_009 & 0x20)
        g_96d6[c].a_02c |= 0x20;
    if (g_6e1c[g_6e20[g].f_021].f_020 & 4)
        g_96d6[c].a_08b = 6;
    if (g_6e1c[g_6e20[g].f_021].f_020 & 1)
        g_96d6[c].a_02e = 0;
    else
        g_96d6[c].a_02e = 1;
    if (g_6e1c[g_6e20[g].f_021].f_020 & 0x40)
        g_96d6[c].a_08a = 1;
    else
        g_96d6[c].a_08a = 0;
    if (g_6e1c[g_6e20[g].f_021].f_020 & 2) {
        g_96d6[c].a_08f = 1;
        fn_10_754a(5, 0, 0, 5);
    } else
        g_96d6[c].a_08f = 0;
    if (g_6e20[g].f_009 & 8)
        g_96d6[c].a_032 = 1;
    else
        g_96d6[c].a_032 = 0;
    if (g_6e20[g].f_009 & 4)
        g_96d6[c].a_034 = 1;
    else
        g_96d6[c].a_034 = 0;
    g_96d6[c].a_04e = g_96d6[c].a_04c = 0;
    for (i = 0; i < 2; i++)
        g_96d6[c].a_08c[i] = g_6e20[g].f_004[i];
    g_96d6[c].a_024 = SC(g_6e1c[g_6e20[g].f_021].f_01a) / 2;
    lstrcpy(g_96d6[c].a_058, g_6e20[g].f_00a);
    g_96d6[c].a_036 = 1;
    g_1df8[g_9324][n].f_044 = g_96d6[c].a_01a;
    g_1df8[g_9324][n].f_042 = g_96d6[c].a_016;
    g_1df8[g_9324][n].f_046 = g_96d6[c].a_014;
    g_1df8[g_9324][n].f_02c = 200;
    g_1df8[g_9324][n].f_048 = g_96d6[c].a_018;
    g_1df8[g_9324][n].f_01e = 0;
    g_1df8[g_9324][n].f_066 = (FNPTR)fn_16_08e4;
    g_1df8[g_9324][n].f_062 = (FNVOID)fn_11_37a0;
    g_1df8[g_9324][n].f_05e = (FNSPLIT)fn_08_45e0;
    g_1df8[g_9324][n].f_02e = 0;
    g_1df8[g_9324][n].f_03c = 0;
    g_1df8[g_9324][n].f_054 = 0;
    g_7092[n].f_0ea = 1;
    g_7092[n].f_00a = g_96d6[c].a_026;
    g_7092[n].f_00c = g_96d6[c].a_028;
    g_7092[n].f_034 = 0;
    g_7092[n].f_01a = 1;
    g_7092[n].f_082 = GetCurrentTime();
    g_7092[n].f_0e1 = g_96d6[c].a_02c & 1;
    g_7092[n].f_0e2 = g_96d6[c].a_02e;
    g_7092[n].f_0e4 = g_96d6[c].a_08a;
    g_7092[n].f_0e5 = g_96d6[c].a_032;
    g_7092[n].f_0e7 = g_96d6[c].a_08f;
    if (g_91f8 == 1 || n != g_9646)
        g_7092[n].f_008 = 1;
    g_7092[n].f_058 = 1;
    g_7092[n].f_05a = 0;
    g_7092[n].f_050 = g_7092[n].f_052 = 0;
    g_7092[n].f_0eb = 0;
    g_7092[n].f_09e = g_7092[n].f_0a0 = 0;
    g_7092[n].f_05d = 0;
    if (g_96d6[c].a_08b != 0)
        g_7092[n].f_0e3 = 1;
    else
        g_7092[n].f_0e3 = 0;
    if (g_7092[n].f_0d4 != -1)
        g_7092[n].f_012 = 1200L * g_96d6[c].a_008
            / ((long)g_96d6[c].a_026 * ((g_6e24[g_7092[n].f_0d4].f_33 + 10) * 10) / 100);
    else
        g_7092[n].f_012 = 1200L * g_96d6[c].a_008 / g_96d6[c].a_026;
    if (n == g_9646 && flow_interactive)
        g_7092[n].f_012 = g_7092[n].f_012 * 3 / 4;
}
