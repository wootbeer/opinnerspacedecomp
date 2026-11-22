/* INSPACE.EXE segment 14 (selector 1068). */
#include "inspace.h"
#include <stdlib.h>

/* BEGIN STRUCTS */
#pragma pack(1)
/* Object records: array of 0x15a-byte records at DS:7092 [inferred base:
 * lowest offset accessed with an index * 0x15a]. Fields named by offset
 * in the record. Generated layout; keep in sync between seg13.c/seg14.c. */
typedef struct {
    char pad_000[0xe];
    int f_00e;    /* DS:70a0 */
    char pad_010[0x20];
    int f_030;    /* DS:70c2 */
    int f_032;    /* DS:70c4 */
    char pad_034[0x2];
    int f_036;    /* DS:70c8 */
    char pad_038[0x14];
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
    long f_096;    /* DS:7128 */
    unsigned long f_09a;    /* DS:712c */
    char pad_09e[0x36];
    int f_0d4;    /* DS:7166 */
    char pad_0d6[0x13];
    char f_0e9;    /* DS:717b */
    char f_0ea;    /* DS:717c */
    char f_0eb;    /* DS:717d */
    char pad_0ec[0x68];
    long f_154;    /* DS:71e6 */
    char pad_158[0x2];
} OBJ15A;

/* 0x70-byte records reached through far pointers (DS:1e30, DS:1df8[]). */
typedef struct {
    char pad_000[0x4];
    POINT f_004;
    char pad_008[0x4];
    int f_00c;
    int f_00e;
    char pad_010[0x8];
    int f_018;
    char pad_01a[0xc];
    int f_026;
    char pad_028[0x1e];
    int f_046;
    char pad_048[0x28];
} REC70;

/* 0x41-byte records through the far pointer at DS:6e20 [inferred]. */
typedef struct {
    char pad_000[0x3];
    char f_003;
    char pad_004[0x6];
    char f_00a[23];
    int f_021;
    char pad_023[0x1e];
} REC41;

/* 0x2c-byte records through the far pointer at DS:6e1c [inferred]. */
typedef struct {
    char pad_000[0x21];
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
extern int g_95aa;
extern HGLOBAL g_95a6;
extern HGLOBAL g_95ac;

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
