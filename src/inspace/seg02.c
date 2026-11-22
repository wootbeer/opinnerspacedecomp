/* INSPACE.EXE segment 2 (selector 1008). */
#include "inspace.h"

/* @addr 2:094c */
int far fn_02_094c(UINT id)
{
    return LoadString(g_9212, id, g_8e68, 249);
}

/* @addr 2:1a5a */
void far fn_02_1a5a(int a, int b, long c)
{
    g_fp_1d5c(a, b, c);
}

/* @addr 2:1a7a */
int far fn_02_1a7a(int a)
{
    if (g_0024)
        return g_fp_1d58(a);
    return 0;
}
