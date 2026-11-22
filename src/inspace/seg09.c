/* INSPACE.EXE segment 9 (selector 1040). */
#include "inspace.h"

/* @addr 9:88ba */
int far fn_09_88ba(int x)
{
    if (x >= 0)
        return x;
    return -x;
}

/* @addr 9:955c */
int far fn_09_955c(UINT id, LPSTR buf)
{
    return LoadString(g_9212, id, buf, 160);
}
