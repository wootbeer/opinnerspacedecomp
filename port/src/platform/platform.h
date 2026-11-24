/* What the game needs from the machine it runs on. One implementation per
 * platform; the game never calls the OS directly. */
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stddef.h>
#include <stdint.h>

/* Milliseconds since an arbitrary start; wraps like timeGetTime(). */
uint32_t platform_time_ms(void);

/* Local date and time. */
typedef struct {
    int year, month, day, hour, minute, second;
} PlatformDate;
void platform_date(PlatformDate *out);

/* Folder roots the game may explore (drives on Windows, granted folders on
 * Android). Returns the number written to roots, at most max. */
int platform_folder_roots(char roots[][260], int max);

/* Directory listing: calls fn for every entry of path matching pattern
 * (DOS-style wildcard, e.g. "*.EXE"). */
typedef struct {
    const char *name;
    uint32_t size;
    int is_dir;
} PlatformDirEntry;
typedef void (*PlatformDirFn)(const PlatformDirEntry *entry, void *user);
int platform_list_dir(const char *path, const char *pattern,
                      PlatformDirFn fn, void *user);

/* Path of the folder holding the game's data files (INSPACE.EXE etc.). */
const char *platform_data_dir(void);

/* A file shipped with the port (the fonts), from the folder of the
 * executable; NULL if missing.  The data stays loaded. */
const void *platform_asset(const char *name, size_t *size);

/* Writable folder for settings (INSPACE.INI), ending in a separator. */
const char *platform_pref_dir(void);

/* Finds path on disk ignoring the case of each name in it ('/' separated).
 * Names that do not exist are kept as given (for new files).  Returns 1
 * when the whole path exists. */
int platform_find_path(const char *path, char *out, int size);

#endif
