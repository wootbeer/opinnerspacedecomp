/* platform_music_*: a .MID file played by TinySoundFont when the user
 * has named a SoundFont, else by the system's own MIDI synthesizer
 * (Windows' MIDI output, Android's MediaPlayer), else not at all. */
#include <SDL3/SDL_log.h>

#include "platform/music.h"

#if defined(_WIN32)
static const MusicBackend *const system_music = &music_win;
#elif defined(SDL_PLATFORM_ANDROID)
static const MusicBackend *const system_music = &music_android;
#else
static const MusicBackend *const system_music = NULL;
#endif

static const MusicBackend *backend;     /* the one with a file open */
static uint16_t volume_left = 0xffff, volume_right = 0xffff;

static int open_with(const MusicBackend *b, const char *path, const char *soundfont)
{
    if (!b || !b->open(path, soundfont))
        return 0;
    backend = b;
    backend->volume(volume_left, volume_right);
    return 1;
}

int platform_music_open(const char *path, const char *soundfont)
{
    static int told;

    platform_music_close();
    if (soundfont && open_with(&music_tsf, path, soundfont))
        return 1;
    if (open_with(system_music, path, NULL))
        return 1;
    if (!system_music && !soundfont && !told) {
        SDL_Log("no music: no SoundFont set (INSPACE.INI [Port] SoundFont=)");
        told = 1;
    }
    return 0;
}

void platform_music_play(uint32_t from, uint32_t to)
{
    if (backend)
        backend->play(from, to);
}

void platform_music_pause(void)
{
    if (backend)
        backend->pause();
}

int platform_music_ended(void)
{
    return backend && backend->ended();
}

void platform_music_close(void)
{
    if (backend)
        backend->close();
    backend = NULL;
}

void platform_music_volume(uint16_t left, uint16_t right)
{
    volume_left = left;
    volume_right = right;
    if (backend)
        backend->volume(left, right);
}
