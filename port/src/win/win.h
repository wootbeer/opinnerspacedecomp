/* The native Windows layer as main.c sees it. */
#ifndef WIN_H
#define WIN_H

/* Screen objects, the DGROUP image and INSPACE.EXE; 0 when the game's
 * files cannot be read. */
int win_init(void);

/* Runs the game (its WinMain) with the given command line. */
int win_run(const char *cmdline);

/* Called about 60 times a second while the game runs (main.c). */
void app_frame(void);

#endif
