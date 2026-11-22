/* INSPACE.EXE segment 10 (selector 1048). */
#include "inspace.h"

extern int g_90f4;
void far fn_15_5932(void);
void far fn_10_022e(int a);

/* @addr 10:01fe */
int far fn_10_01fe(void)
{
    switch (g_90f4) {
    case 0:
        fn_15_5932();
        break;
    case 1:
        fn_10_022e(1);
        break;
    }
    return 1;
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_10_022e(int a)
{
    g_90f4 = a;
}

/* @addr 10:6d38 */
int far fn_10_6d38(LPCSTR s)
{
    return g_fp_3c2c(s);
}

/* @addr 10:6e26 */
void far fn_10_6e26(void)
{
    g_fp_3c50(g_920e, 0, 0, 0, 0, 0, 2);
}

/* @addr 10:6ec6 */
void far fn_10_6ec6(int a)
{
    g_fp_3c40(g_920e, a, g_13dc);
}

/* @addr 10:6b54 */
void far fn_10_6b54(void)
{
    g_fp_3c84(0, g_1e4c);
}

/* @addr 10:7db8 */
void far fn_10_7db8(void)
{
    g_fp_3c54(g_05a0, 2);
}

/* @addr 10:8686 */
void far fn_10_8686(void)
{
    g_8e5c = 0;
    g_fp_3c54(g_05a0, 3);
}

/* @addr 10:86ca */
void far fn_10_86ca(void)
{
    int r;

    r = 0;
    g_fp_3c4c();
}
