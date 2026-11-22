/* INSPACE.EXE segment 18 (selector 1088). */
#include "inspace.h"

extern int g_9668;
extern int g_9672;
extern int g_a1cd;
extern int g_a1cf;
extern char g_a18f[4];
extern char g_a193[4];
extern HANDLE g_88d8[8];
extern int g_8e62;
extern int g_90f4;
extern int g_1318;
extern int g_9530;

/* @addr 18:034c */
void far fn_18_034c(void)
{
    if (g_9668) {
        SelectClipRgn(g_13dc, g_9668);
        g_9672 = 1;
    }
}

/* @addr 18:0ba0 */
void far fn_18_0ba0(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (g_88d8[i]) {
            DeleteObject(g_88d8[i]);
            g_88d8[i] = 0;
        }
    }
}

/* @addr 18:0d4e */
void far fn_18_0d4e(int msg, int key)
{
    if (g_8e62) {
        switch (msg) {
        case 0x101:
            switch (key) {
            case 0x1b:
                if (g_90f4 == 1 && g_1318 <= 1)
                    g_9530 = 2;
                break;
            }
            break;
        }
        g_8e62 = 0;
    }
}

/* @addr 18:633c */
void far fn_18_633c(void)
{
    int i;

    g_a1cf = g_a1cd = 0;
    for (i = 0; i < 4; i++)
        g_a18f[i] = g_a193[i] = 1;
}
