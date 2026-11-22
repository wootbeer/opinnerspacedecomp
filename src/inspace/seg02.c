/* INSPACE.EXE segment 2 (selector 1008). */
#include "inspace.h"

extern int g_0020;
extern RECT g_1d20;
extern int g_8f6a;
extern int g_8e5e;
extern int g_8f70;
extern int g_90f8;
extern DWORD g_1d40;
extern int g_0592;
extern int g_8f68;

/* @addr 2:094c */
int far fn_02_094c(UINT id)
{
    return LoadString(g_9212, id, g_8e68, 249);
}

/* @addr 2:1a5a */
void far fn_02_1a5a(int a, int b, long c)
{
    g_fp_1d5c(a, b, c);
}

/* @addr 2:1a7a */
int far fn_02_1a7a(int a)
{
    if (g_0024)
        return g_fp_1d58(a);
    return 0;
}

/* @addr 2:1a9e */
void far fn_02_1a9e(void)
{
    int r;

    if (g_0024) {
        FreeLibrary(g_0024);
        g_0024 = 0;
    }
}

/* @addr 2:11c0 */
void far fn_02_11c0(void)
{
    if (!IsIconic(g_0016)) {
        if (!g_0020)
            GetWindowRect(g_0016, &g_1d20);
        g_8f6a = 1;
    }
}

/* @addr 2:084c */
void far fn_02_084c(int id)
{
    switch (id) {
    case 0x9fa:
        g_8e5e = g_8f70 = 0;
        break;
    case 0x9f0:
        g_8e5e = g_8f70 = 1;
        break;
    }
    g_90f8 = 1;
    g_1d40 = GetCurrentTime();
}

/* @addr 2:09c4 */
void far fn_02_09c4(void)
{
    char buf[80];

    g_0592 = 2;
    g_8f68 = 0;
    LoadString(g_9212, 0x7fc, buf, 80);
    SetWindowText(g_0016, buf);
}
