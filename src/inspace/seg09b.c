/* @cflags /AM /G2 /Gw /Gs /Os */
/* INSPACE.EXE segment 9 (selector 1040): code compiled with /G2. */
#include "inspace.h"

typedef struct {                /* 0x70 bytes, far array at DS:1e18 */
    char p00[0x51];
    char f51;
    char p52[0x70 - 0x52];
} REC_70;

extern REC_70 far *g_1e18;
extern int g_9318;
extern int g_9322;
extern char g_9ec2[][40];
extern long g_9f40[][40];

/* @addr 9:225a */
long far fn_09_225a(int a)
{
    long v;
    int unused[3];

    v = g_9f40[g_9322][a];
    g_1e18[g_9318 * 2 + a].f51 = g_9ec2[g_9322][a] + g_9318 * 2;
    return v;
}
