/* Platform implementation on SDL3, shared by Windows, Linux and Android.
 * Folder roots are filled in when the game code needs them. */
#include "platform/platform.h"

#include <SDL3/SDL.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

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

/* Windows: its drives from C: on, as "C:/"; elsewhere the user's home
 * folder (it becomes drive C:, see port/README.md). */
int platform_folder_roots(char roots[][260], int max)
{
#ifdef _WIN32
    DWORD drives = GetLogicalDrives();
    int n = 0, i;

    for (i = 2; i < 26 && n < max; i++)
        if (drives & (1u << i))
            SDL_snprintf(roots[n++], 260, "%c:/", 'A' + i);
    return n;
#else
    const char *home = SDL_GetUserFolder(SDL_FOLDER_HOME);

    if (!home || max < 1)
        return 0;
    SDL_strlcpy(roots[0], home, 260);
    return 1;
#endif
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

static int is_hidden(const char *path, const char *name)
{
#ifdef _WIN32
    wchar_t w[1024];
    DWORD a;

    (void)name;
    if (!MultiByteToWideChar(CP_UTF8, 0, path, -1, w, 1024))
        return 0;
    a = GetFileAttributesW(w);
    return a != INVALID_FILE_ATTRIBUTES && (a & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM));
#else
    (void)path;
    return name[0] == '.';
#endif
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
    e.hidden = is_hidden(full, fname);
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

const void *platform_asset(const char *name, size_t *size)
{
    const char *base = SDL_GetBasePath();
    char path[512];

    SDL_snprintf(path, sizeof path, "%s%s", base ? base : "", name);
    return SDL_LoadFile(path, size);
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

static struct {
    SDL_AudioStream *stream;
    PlatformAudioFn fn;
    void *user;
    SDL_IOStream *dump;
    Uint32 dumped;          /* bytes of samples written to dump */
    int rate;
} audio;

static void write_wav_header(SDL_IOStream *io, int rate, Uint32 bytes)
{
    SDL_SeekIO(io, 0, SDL_IO_SEEK_SET);
    SDL_WriteIO(io, "RIFF", 4);
    SDL_WriteU32LE(io, 36 + bytes);
    SDL_WriteIO(io, "WAVEfmt ", 8);
    SDL_WriteU32LE(io, 16);
    SDL_WriteU16LE(io, 1);                      /* PCM */
    SDL_WriteU16LE(io, 2);
    SDL_WriteU32LE(io, (Uint32)rate);
    SDL_WriteU32LE(io, (Uint32)rate * 4);
    SDL_WriteU16LE(io, 4);
    SDL_WriteU16LE(io, 16);
    SDL_WriteIO(io, "data", 4);
    SDL_WriteU32LE(io, bytes);
}

static void SDLCALL audio_more(void *userdata, SDL_AudioStream *stream, int additional, int total)
{
    int16_t buf[1024];

    (void)userdata;
    (void)total;
    while (additional > 0) {
        int frames = SDL_min(additional / 4 + (additional % 4 != 0), (int)(sizeof buf / 4));
        audio.fn(buf, frames, audio.user);
        SDL_PutAudioStreamData(stream, buf, frames * 4);
        if (audio.dump && SDL_WriteIO(audio.dump, buf, (size_t)frames * 4) == (size_t)frames * 4)
            audio.dumped += (Uint32)frames * 4;
        additional -= frames * 4;
    }
}

int platform_audio_open(int rate, PlatformAudioFn fn, void *user)
{
    SDL_AudioSpec spec;

    if (audio.stream)
        return 1;
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        SDL_Log("no sound: %s", SDL_GetError());
        return 0;
    }
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq = rate;
    audio.fn = fn;
    audio.user = user;
    audio.rate = rate;
    audio.stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, audio_more, NULL);
    if (!audio.stream) {
        SDL_Log("no sound: %s", SDL_GetError());
        return 0;
    }
    if (audio.dump)
        write_wav_header(audio.dump, rate, 0);
    SDL_ResumeAudioStreamDevice(audio.stream);
    return 1;
}

void platform_audio_lock(void)
{
    if (audio.stream)
        SDL_LockAudioStream(audio.stream);
}

void platform_audio_unlock(void)
{
    if (audio.stream)
        SDL_UnlockAudioStream(audio.stream);
}

void platform_audio_dump(const char *path)
{
    audio.dump = SDL_IOFromFile(path, "wb");
    if (!audio.dump)
        SDL_Log("audio dump: %s", SDL_GetError());
}

void platform_audio_close(void)
{
    if (audio.stream) {
        SDL_DestroyAudioStream(audio.stream);
        audio.stream = NULL;
    }
    if (audio.dump) {
        write_wav_header(audio.dump, audio.rate, audio.dumped);
        SDL_CloseIO(audio.dump);
        audio.dump = NULL;
    }
}

/* Windows' MessageBeep, fetched by name: the port's own MessageBeep and
 * GetProcAddress (the game's Windows 3.1 calls) have the same link
 * names. */
void platform_beep(void)
{
#ifdef _WIN32
    typedef BOOL (WINAPI *BeepFn)(UINT);
    static SDL_SharedObject *user32;
    BeepFn beep;

    if (!user32)
        user32 = SDL_LoadObject("user32.dll");
    beep = user32 ? (BeepFn)SDL_LoadFunction(user32, "MessageBeep") : NULL;
    if (beep)
        beep(MB_OK);
#endif
}

/* No MIDI playback yet on any platform. */
int platform_music_open(const char *path)
{
    (void)path;
    return 0;
}

void platform_music_play(uint32_t from, uint32_t to)
{
    (void)from;
    (void)to;
}

void platform_music_pause(void)
{
}

int platform_music_ended(void)
{
    return 0;
}

void platform_music_close(void)
{
}

void platform_music_volume(uint16_t left, uint16_t right)
{
    (void)left;
    (void)right;
}
