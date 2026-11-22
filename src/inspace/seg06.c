/* INSPACE.EXE segment 6 (selector 1028). */
#include "inspace.h"

void far fn_06_10ce(unsigned long v, char far *buf);
void far fn_06_190c(void);
void far fn_06_7266(void);
void far fn_06_717a(void);

extern int g_90f4;
extern int g_049e;
extern HGLOBAL g_94e0;
extern void far *g_6afc;
extern HGLOBAL g_94de;
extern void far *g_6af8;
extern HGLOBAL g_94d8;
extern void far *g_6b04;
extern char g_9078[];
extern char g_96b8[];

/* @addr 6:0eb8 */
void far fn_06_0eb8(long v, char far *buf)
{
    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
    fn_06_10ce(v, buf);
}

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

/* @addr 6:0f1a */
void far fn_06_0f1a(int v, char far *buf)
{
    buf[0] = 0;
    if (v < 0) {
        lstrcpy(buf, "-");
        v = -v;
    }
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

/* @addr 6:18e0 */
void far fn_06_18e0(void)
{
    fn_06_190c();
    g_049e = g_90f4 = 0;
    PostMessage(g_0016, 0x9cf, 0, 0L);
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_190c(void)
{
    g_90f4 = 1;
}

/* @addr 6:626c */
void far fn_06_626c(void)
{
    fn_06_7266();
    fn_06_717a();
    if (g_94d8) {
        if (g_6b04) {
            GlobalUnlock(g_94d8);
            g_6b04 = 0;
        }
        GlobalFree(g_94d8);
        g_94d8 = 0;
    }
}

/* @addr 6:717a */
void far fn_06_717a(void)
{
    if (g_94de) {
        GlobalUnlock(g_94de);
        GlobalFree(g_94de);
        g_94de = 0;
        g_6af8 = 0;
    }
}

/* Not yet decompiled: stub so calls to it compile as near calls. */
void far fn_06_7266(void)
{
    g_94de = 1;
}

/* @addr 6:8eb4 */
void far fn_06_8eb4(void)
{
    if (g_94e0) {
        GlobalUnlock(g_94e0);
        GlobalFree(g_94e0);
        g_6afc = 0;
        g_94e0 = 0;
    }
}

/* @addr 6:92b8 */
int far fn_06_92b8(void)
{
    OFSTRUCT of;
    char path[110];

    lstrcpy(path, g_9078);
    lstrcat(path, g_96b8);
    lstrcat(path, "demogame.sav");
    return OpenFile(path, &of, 0x200);
}
