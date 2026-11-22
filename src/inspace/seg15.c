/* INSPACE.EXE segment 15 (selector 1070). */
#include "inspace.h"

int far fn_10_6d38(LPCSTR s);

/* @addr 15:5914 */
void far fn_15_5914(void)
{
    g_95f4 = fn_10_6d38("SD_LOGO");
}
