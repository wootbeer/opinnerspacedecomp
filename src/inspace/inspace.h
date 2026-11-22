/* Shared declarations for INSPACE.EXE.
 * Globals are named by their DGROUP (DS = selector 1090) offset until
 * understood; names from names/INSPACE.EXE.txt are used where confirmed.
 * Types follow how the game's code accesses them.
 */
#ifndef INSPACE_H
#define INSPACE_H

#include <windows.h>

/* Far function pointers in DGROUP, called indirectly (lcall [DS:x]);
 * set at run time [inferred: entry points fetched with GetProcAddress]. */
extern int  (far pascal *g_fp_1d58)(int);
extern void (far pascal *g_fp_1d5c)(int, int, long);
extern int  (far pascal *g_fp_3c2c)(LPCSTR);
extern void (far pascal *g_fp_3c40)(int, int, int);
extern void (far pascal *g_fp_3c4c)(void);
extern void (far pascal *g_fp_3c50)(int, int, int, int, int, int, int);
extern void (far pascal *g_fp_3c54)(long, int);
extern void (far pascal *g_fp_3c84)(int, long);

extern int g_0024;
extern long g_05a0;
extern int g_13dc;
extern long g_1e4c;
extern int g_8e5c;
extern char g_8e68[];
extern int g_920e;
extern HINSTANCE g_9212;              /* passed to LoadString: the instance */
extern int g_95f4;

typedef struct { char b[0x4b0]; } REC_4B0;    /* 1200-byte records */
extern REC_4B0 far *g_6b0c;

#endif
