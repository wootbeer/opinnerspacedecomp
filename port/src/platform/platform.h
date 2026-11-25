/* What the game needs from the machine it runs on. One implementation per
 * platform; the game never calls the OS directly. */
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stddef.h>
#include <stdint.h>

/* Nanoseconds since an arbitrary start. */
uint64_t platform_time_ns(void);
/* The same clock in milliseconds (platform_time_ns() / 1000000); wraps
 * like timeGetTime(). */
uint32_t platform_time_ms(void);
/* Sleeps until platform_time_ns() reaches t (not at all if it has), as
 * closely as the system's timers allow, without spinning. */
void platform_sleep_until(uint64_t t);
/* Processor time the program has used, in nanoseconds. */
uint64_t platform_cpu_ns(void);

/* Local date and time. */
typedef struct {
    int year, month, day, hour, minute, second;
} PlatformDate;
void platform_date(PlatformDate *out);

/* Folder roots the game may explore: on Windows its drives ("C:/"), on
 * Linux the user's home, on Android (later) the folders the user granted.
 * Returns the number written to roots, at most max. */
int platform_folder_roots(char roots[][260], int max);

/* Directory listing: calls fn for every entry of path matching pattern
 * (DOS-style wildcard, e.g. "*.EXE"). */
typedef struct {
    const char *name;
    uint32_t size;
    int is_dir;
    int hidden;             /* Windows: hidden or system; elsewhere: a dot name */
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

/* Sound output: 16-bit stereo frames at rate, asked of fn on the
 * platform's audio thread and mixed with the music.  platform_audio_lock
 * keeps fn from running (for data fn reads).  Returns 0 when there is no
 * sound device. */
typedef void (*PlatformAudioFn)(int16_t *frames, int count, void *user);
int platform_audio_open(int rate, PlatformAudioFn fn, void *user);
void platform_audio_lock(void);
void platform_audio_unlock(void);
/* Test option: everything played (the device's mix, 16-bit at its rate)
 * is also written to a WAV file at path (call before platform_audio_open);
 * platform_audio_close finishes it. */
void platform_audio_dump(const char *path);
void platform_audio_close(void);

/* Music: a standard MIDI file (.MID) at a host path, times in
 * milliseconds.  It plays on the SoundFont at the host path soundfont
 * (TinySoundFont; NULL: none) or else on the system's own synthesizer;
 * platform_music_open gives 0 when neither can (port/NOTES-port.md,
 * "Music").  platform_music_play plays from `from` (PLATFORM_MUSIC_HERE:
 * where it stopped) to `to` (0: the end); platform_music_ended tells,
 * once, that it got there.  Volumes are 0-0xffff per side, kept across
 * files.  platform_audio_close closes the music too. */
#define PLATFORM_MUSIC_HERE 0xffffffffu
int platform_music_open(const char *path, const char *soundfont);
void platform_music_play(uint32_t from, uint32_t to);
void platform_music_pause(void);
int platform_music_ended(void);
void platform_music_close(void);
void platform_music_volume(uint16_t left, uint16_t right);

/* The system's default beep (Windows' MessageBeep); nothing elsewhere. */
void platform_beep(void);

/* Game controller (platform_pad.c): a gamepad (Xbox, PlayStation,
 * Switch, Steam Deck ...), else any joystick; plugged in or out at any
 * time.  Buttons are named by place: A is the bottom face button, B the
 * right, X the left, Y the top one; the triggers count as held from half
 * way.  platform_pad_read gives 0 when no controller is connected. */
enum {
    PAD_A, PAD_B, PAD_X, PAD_Y, PAD_BACK, PAD_START, PAD_LEFT_STICK, PAD_RIGHT_STICK,
    PAD_LEFT_SHOULDER, PAD_RIGHT_SHOULDER, PAD_UP, PAD_DOWN, PAD_LEFT, PAD_RIGHT,
    PAD_LEFT_TRIGGER, PAD_RIGHT_TRIGGER, PAD_BUTTONS
};
typedef struct {
    uint16_t x, y;              /* left stick: 0 (left, up) to 65535, 32768 centred */
    uint32_t buttons;           /* 1 << PAD_x: held */
} PlatformPad;
int platform_pad_read(PlatformPad *out);

#endif
