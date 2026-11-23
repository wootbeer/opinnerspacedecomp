/* Platform implementation on SDL3, shared by Windows, Linux and Android.
 * Folder roots and listing are filled in when the game code needs them. */
#include "platform/platform.h"

#include <SDL3/SDL.h>
#include <string.h>
#include <time.h>

uint32_t platform_time_ms(void)
{
    return (uint32_t)SDL_GetTicks();
}

void platform_date(PlatformDate *out)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    out->year = t->tm_year + 1900;
    out->month = t->tm_mon + 1;
    out->day = t->tm_mday;
    out->hour = t->tm_hour;
    out->minute = t->tm_min;
    out->second = t->tm_sec;
}

int platform_folder_roots(char roots[][260], int max)
{
    (void)roots;
    (void)max;
    return 0;
}

int platform_list_dir(const char *path, const char *pattern,
                      PlatformDirFn fn, void *user)
{
    (void)path;
    (void)pattern;
    (void)fn;
    (void)user;
    return 0;
}

const char *platform_data_dir(void)
{
    const char *env = SDL_getenv("INSPACE_DATA");

    return env ? env : "data";
}
