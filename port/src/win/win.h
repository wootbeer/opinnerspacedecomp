/* The native Windows layer as main.c sees it. */
#ifndef WIN_H
#define WIN_H

#include <stdint.h>

/* Screen objects, the DGROUP image and INSPACE.EXE; 0 when the game's
 * files cannot be read. */
int win_init(void);

/* Runs the game (its WinMain) with the given command line. */
int win_run(const char *cmdline);

/* The keys of an SDL key name with modifiers before it ("Escape",
 * "Alt+X"; "Alt", "Ctrl" and "Shift" are the left ones), in the order
 * they are pressed; their count, 0 when a name is not known. */
#define WIN_KEYS 4
int win_key_names(const char *spec, uint32_t keys[WIN_KEYS]);

/* Called about 60 times a second while the game runs (main.c). */
void app_frame(void);

#endif
