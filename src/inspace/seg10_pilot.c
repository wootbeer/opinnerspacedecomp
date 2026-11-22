/* Pilot match for the toolchain: INSPACE.EXE segment 10 (selector 1048).
 * Build: cl /c /AM /G3 /Gw /Gs /Os (MSVC 1.5x, CL 8.00c).
 * Names are placeholders by address until the function is understood.
 */

extern int g_90f4;                 /* DS:90f4 */
void far fn_15_5932(void);         /* 15:5932 (selector 1070) */
void far fn_10_022e(int a);        /* 10:022e, same segment */

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

/* Stub so the compiler places the callee in this segment (near call via
 * push cs). Not yet decompiled; not checked. */
void far fn_10_022e(int a)
{
    g_90f4 = a;
}
