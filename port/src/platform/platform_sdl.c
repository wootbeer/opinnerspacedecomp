/* Platform implementation on SDL3, shared by Windows, Linux and Android.
 * Folder roots are filled in when the game code needs them. */
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

/* DOS-style wildcard match ('*' and '?'), ignoring case. */
static int wild_match(const char *pat, const char *s)
{
    for (; *pat; pat++, s++) {
        if (*pat == '*') {
            for (;; s++) {
                if (wild_match(pat + 1, s))
                    return 1;
                if (!*s)
                    return 0;
            }
        }
        if (!*s || (*pat != '?' && SDL_toupper((unsigned char)*pat) != SDL_toupper((unsigned char)*s)))
            return 0;
    }
    return *s == 0;
}

typedef struct {
    const char *dir, *pattern;
    PlatformDirFn fn;
    void *user;
    int count;
} ListCtx;

static SDL_EnumerationResult SDLCALL list_one(void *userdata, const char *dirname, const char *fname)
{
    ListCtx *c = userdata;
    char full[1024];
    SDL_PathInfo info;
    PlatformDirEntry e;

    (void)dirname;
    if (!wild_match(c->pattern, fname))
        return SDL_ENUM_CONTINUE;
    SDL_snprintf(full, sizeof full, "%s/%s", c->dir, fname);
    if (!SDL_GetPathInfo(full, &info))
        return SDL_ENUM_CONTINUE;
    e.name = fname;
    e.size = (uint32_t)info.size;
    e.is_dir = info.type == SDL_PATHTYPE_DIRECTORY;
    c->fn(&e, c->user);
    c->count++;
    return SDL_ENUM_CONTINUE;
}

int platform_list_dir(const char *path, const char *pattern,
                      PlatformDirFn fn, void *user)
{
    ListCtx c;

    c.dir = path;
    c.pattern = pattern;
    c.fn = fn;
    c.user = user;
    c.count = 0;
    SDL_EnumerateDirectory(path, list_one, &c);
    return c.count;
}

const char *platform_data_dir(void)
{
    const char *env = SDL_getenv("INSPACE_DATA");

    return env ? env : "data";
}

const char *platform_pref_dir(void)
{
    static char *dir;

    if (!dir)
        dir = SDL_GetPrefPath("SDi", "Inner Space");
    return dir ? dir : "./";
}

typedef struct {
    const char *want;
    char found[256];
} FindCtx;

static SDL_EnumerationResult SDLCALL find_one(void *userdata, const char *dirname, const char *fname)
{
    FindCtx *c = userdata;

    (void)dirname;
    if (SDL_strcasecmp(c->want, fname) == 0) {
        SDL_strlcpy(c->found, fname, sizeof c->found);
        return SDL_ENUM_SUCCESS;
    }
    return SDL_ENUM_CONTINUE;
}

int platform_find_path(const char *path, char *out, int size)
{
    char name[256];
    int n = 0, exists = 1;

    out[0] = 0;
    if (*path == '/') {
        SDL_strlcpy(out, "/", size);
        path++;
    }
    while (*path) {
        const char *end = strchr(path, '/');
        size_t len = end ? (size_t)(end - path) : strlen(path);
        FindCtx c;

        if (len >= sizeof name)
            len = sizeof name - 1;
        memcpy(name, path, len);
        name[len] = 0;
        c.want = name;
        c.found[0] = 0;
        if (exists && len && strcmp(name, ".") && strcmp(name, "..")) {
            SDL_EnumerateDirectory(out[0] ? out : ".", find_one, &c);
            if (c.found[0])
                SDL_strlcpy(name, c.found, sizeof name);
            else
                exists = 0;
        }
        n = (int)strlen(out);
        if (n && out[n - 1] != '/')
            SDL_strlcat(out, "/", size);
        SDL_strlcat(out, name, size);
        path += len;
        while (*path == '/')
            path++;
    }
    return exists;
}
