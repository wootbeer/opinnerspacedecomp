/* INSPACE.EXE segment 11 (selector 1050): functions that call 11:33cc far,
 * so they cannot share seg11.c (where 11:3396 calls it near). */
#include "inspace.h"

extern HWND g_0a7a;
extern long g_0a6c;

void far fn_11_33cc(void);

/* Scroll bar handler: zoom between 100 and 500 [inferred]. */
/* @addr 11:7798 */
void far fn_11_7798(int code, unsigned pos)
{
    long old;

    old = g_0a6c;
    switch (code) {
    case 1:
        g_0a6c -= 20;
        break;
    case 0:
        g_0a6c += 20;
        break;
    case 6:
        g_0a6c = 500;
        break;
    case 7:
        g_0a6c = 100;
        break;
    case 4:
    case 5:
        g_0a6c = 600L - pos;
        break;
    case 2:
    case 3:
        break;
    }
    if (g_0a6c > 500)
        g_0a6c = 500;
    else if (g_0a6c < 100)
        g_0a6c = 100;
    if (old != g_0a6c) {
        fn_11_33cc();
        SetScrollPos(g_0a7a, SB_CTL, 600 - (int)g_0a6c, TRUE);
    }
}
