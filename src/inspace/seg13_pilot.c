/* Pilot match: INSPACE.EXE segment 13 (selector 1060). */
#include <windows.h>

extern int g_131a;                 /* DS:131a, debug output on when nonzero */

/* @addr 13:4eca */
void far fn_13_4eca(LPCSTR text)
{
    if (g_131a)
        OutputDebugString(text);
}
