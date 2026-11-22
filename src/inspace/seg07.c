/* INSPACE.EXE segment 7 (selector 1030). */
#include "inspace.h"

/* @addr 7:63f2 */
void far fn_07_63f2(void)
{
    if (g_9458) {
        DestroyWindow(g_9458);
        g_9458 = 0;
    }
}
