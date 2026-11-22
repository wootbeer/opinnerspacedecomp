/* INSPACE.EXE segment 6 (selector 1028). */
#include "inspace.h"

void far fn_06_10ce(unsigned long v, char far *buf);

/* @addr 6:0ef8 */
void far fn_06_0ef8(unsigned long v, char far *buf)
{
    buf[0] = 0;
    fn_06_10ce(v, buf);
}

/* @addr 6:10aa */
void far fn_06_10aa(unsigned v, char far *buf)
{
    buf[0] = 0;
    fn_06_10ce(v, buf);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_10ce(unsigned long v, char far *buf)
{
    buf[1] = (char)v;
}

/* @addr 6:73d6 */
void far fn_06_73d6(int i)
{
    g_6b0c[i].b[0] = 0;
}

/* @addr 6:1290 */
int far fn_06_1290(LPCSTR key, int def)
{
    return GetPrivateProfileInt(g_9690, key, def, g_96a9);
}

int far fn_02_1ac8(void);
void far fn_02_1b96(void);

/* @addr 6:1b3c */
void far fn_06_1b3c(void)
{
    if (g_8f66 && fn_02_1ac8())
        fn_02_1b96();
}
