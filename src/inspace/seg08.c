/* INSPACE.EXE segment 8 (selector 1038), /G3 parts.
 * 8:3688..81f8 was compiled with /G2: see seg08b.c. */
#include "inspace.h"

/* 20-byte records at DS:58bc [inferred: tracked positions]. */
typedef struct {
    POINT a;        /* +0 */
    POINT b;        /* +4 */
    POINT c;        /* +8 */
    char rest[8];   /* +c */
} REC_14;
extern REC_14 g_58bc[];

POINT far pascal fn_08_29ea(POINT pt);

/* @addr 8:124a */
void far pascal fn_08_124a(int i)
{
    g_58bc[i].b.x = g_58bc[i].a.x;
    g_58bc[i].b.y = g_58bc[i].a.y;
    g_58bc[i].a = fn_08_29ea(g_58bc[i].c);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
POINT far pascal fn_08_29ea(POINT pt)
{
    return pt;
}
