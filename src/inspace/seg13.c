/* INSPACE.EXE segment 13 (selector 1060). */
#include "inspace.h"

extern int g_131a;                 /* debug output on when nonzero */

/* @addr 13:4eca */
void far fn_13_4eca(LPCSTR text)
{
    if (g_131a)
        OutputDebugString(text);
}

/* @addr 13:2da4 */
void far fn_13_2da4(void)
{
    char buf[110];
}

/* @addr 13:2db8 */
void far fn_13_2db8(void)
{
    char buf[110];
}
