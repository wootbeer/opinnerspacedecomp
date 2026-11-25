/* ISPACE.DLL's music (9:3906 and the routines after it): SOUNDS\MAIN.MID,
 * RACE.MID, ANTHEM.MID and DEMON.MID through MCI's sequencer (mci.c).
 * The game asks for one of 12 pieces (ordinal 7 mode 11); each is a
 * section of one file, played from its start to its end and then again
 * (7 and 8 go on with piece 2; 5 and 11 play once).  Commands below 0
 * pause or go on.  The MIDI output's volume is the music's share of
 * SoundVolume, set as ordinal 8 sets the waves' for a sound in the
 * middle. */
#include <SDL3/SDL_stdinc.h>

#include "user.h"
#include "ispace.h"

#define INI "INSPACE.INI"
#define APP "Inner Space"
#define PIECES 12

/* DS:0ad8: the file of each piece; DS:0aa8, DS:0ac0: its start and
 * length in tenths of a second. */
static const char *const file_names[4] = {"main", "race", "anthem", "demon"};
static const int8_t piece_file[PIECES] = {2, 0, 0, 1, 1, 2, 3, 0, 0, 3, 3, 2};
static const int16_t piece_start[PIECES] = {0, 45, 1700, 0, 340, 2000, 190, 2870, 2920, 0, 89, 1810};
static const int16_t piece_length[PIECES] = {1810, 1495, 1170, 290, 2550, 166, 2030, 50, 90, 89, 101, 190};

enum {                          /* DS:2292 */
    CLOSED, PLAYING, PAUSED_FOR_FOCUS, SEEKING, STOPPED
};

static struct {
    int16_t on;                 /* DS:221e INI Music */
    int16_t file;               /* DS:0aa2: the file open (-1 none) */
    int16_t piece;              /* DS:0aa4 */
    int16_t last;               /* DS:0aa6: the piece played before */
    int16_t state;              /* DS:2292 */
    int16_t resume;             /* DS:229a: paused by the focus while playing */
    UINT device;                /* DS:22a6 (0: none) */
    DWORD volume;               /* DS:06a8: the game's MIDI volume */
    DWORD saved_volume;         /* DS:06b0: the MIDI volume before the game's */
    DWORD set_volume;           /* DS:0d06: the last one set */
} mus = {1, -1, -1, -1, CLOSED, 0, 0, 0xffffffff, 0xffffffff, 0};

void ispace_music_set_on(int16_t on)
{
    mus.on = on;
}

/* 9:3e46: the MIDI volume, when it changes. */
static void set_volume(DWORD v)
{
    if (v != mus.set_volume) {
        mus.set_volume = v;
        midiOutSetVolume(0, v);
    }
}

/* 9:38e2 (9:3bf4 for a sound in the view's middle): 95% of the music
 * volume on both sides, with dynamic sound. */
void ispace_music_center(void)
{
    uint32_t level;

    if (ispace_sound_system() <= 1)
        return;
    level = 95u * (uint16_t)ispace_sound_music_volume() / 100;
    if (level > 100)
        level = 100;
    level = level * 0xffff / 100;
    mus.volume = MAKELONG(level, level);
    set_volume(mus.volume);
}

/* 9:3a16. */
static void music_close(void)
{
    mci_close(mus.device);
    mus.device = 0;
    mus.state = CLOSED;
}

/* 9:3b5c: the piece from where it is to its end. */
static void play_piece(void)
{
    if (mus.state != PAUSED_FOR_FOCUS && mus.state != SEEKING)
        return;
    if (!mus.on || !ispace_sound_system() || mus.piece < 0) {
        music_close();
        return;
    }
    mus.last = mus.piece;
    if (mci_play(mus.device, 100 * ((DWORD)piece_start[mus.piece] + (DWORD)piece_length[mus.piece]),
                 ispace_sound_window()))
        music_close();
    else
        mus.state = PLAYING;
}

/* 9:3a94: to the piece's start, then play it (at once when wait, else
 * when the seek's MM_MCINOTIFY comes).  Coming from piece 2 to 1 starts
 * 4.5 s early, from 1 to 2 15 s early. */
static void seek_piece(int16_t wait)
{
    DWORD to = 100 * (DWORD)piece_start[mus.piece];

    mus.state = SEEKING;
    if (mus.piece == 1 && mus.last == 2)
        to -= 4500;
    else if (mus.piece == 2 && mus.last == 1)
        to -= 15000;
    mci_seek(mus.device, to, wait ? 0 : ispace_sound_window());
    if (wait)
        play_piece();
}

/* 9:3a48: pauses; STOPPED always, PAUSED_FOR_FOCUS only while playing
 * (and then the focus brings it back). */
static void music_pause(int16_t state)
{
    mus.resume = 0;
    if (state != STOPPED) {
        if (mus.state != PLAYING)
            return;
        mus.resume = state == PAUSED_FOR_FOCUS;
    }
    mci_pause(mus.device);
    mus.state = state;
}

/* 9:37ea: opens the file and starts the piece.  (The DLL asked whether
 * to go on when the sequencer did not play through the MIDI Mapper; the
 * platform's always does.) */
static void music_open(const char *path)
{
    mus.device = mci_open_sequencer(path);
    if (mus.device)
        seek_piece(1);
}

/* 9:3906: piece n (0-11), wait as in seek_piece; -1 stop, -2 pause for
 * a while, -3 go on, -5 nothing. */
void ispace_music(int16_t n, int16_t wait)
{
    char path[0x80];

    if (n <= -1 && mus.state == STOPPED)
        return;
    switch (n) {
    case -5:
        return;
    case -3:
        play_piece();
        return;
    case -2:
        mus.last = n;
        music_pause(PAUSED_FOR_FOCUS);
        return;
    case -1:
        mus.last = n;
        music_pause(STOPPED);
        return;
    default:
        break;
    }
    if (n < 0 || n >= PIECES)   /* the DLL read past its tables */
        return;
    mus.piece = n;
    if (!ispace_sound_system() || !mus.on)
        return;
    ispace_music_center();
    if (piece_file[n] == mus.file && mus.state != CLOSED) {
        seek_piece(wait);
        return;
    }
    music_close();
    mus.file = piece_file[n];
    ispace_sound_path(path, sizeof path);
    SDL_strlcat(path, file_names[mus.file], sizeof path);
    SDL_strlcat(path, ".mid", sizeof path);
    music_open(path);
}

/* The NotifyClass window's music messages (9:2ac4): a play or seek has
 * finished, or the game's command 0x84c (a piece to play). */
LRESULT ispace_music_message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_USER + 0x44c) {
        ispace_music((int16_t)wp, 1);
        return 0;
    }
    if (msg != MM_MCINOTIFY)
        return DefWindowProc(hwnd, msg, wp, lp);
    if (wp != MCI_NOTIFY_SUCCESSFUL)
        return 0;
    if (mus.state == SEEKING) {
        play_piece();
        return 0;
    }
    if (mus.state != PLAYING)
        return 0;
    if (mus.piece == 7 || mus.piece == 8)
        mus.piece = 2;
    if (mus.piece != 5 && mus.piece != 11)
        seek_piece(0);
    return 0;
}

/* 9:00ba: the MIDI volume before the game's, put back by
 * ispace_music_restore_volume (9:06a0). */
void ispace_music_save_volume(void)
{
    midiOutGetVolume(0, &mus.saved_volume);
}

void ispace_music_restore_volume(void)
{
    set_volume(mus.saved_volume);
}

/* 9:0af2 and 9:0ba6: the game loses and gets back the focus. */
void ispace_music_deactivate(void)
{
    midiOutGetVolume(0, &mus.volume);
    music_pause(PAUSED_FOR_FOCUS);
    set_volume(mus.saved_volume);
}

void ispace_music_activate(int force_volume)
{
    midiOutGetVolume(0, &mus.saved_volume);
    if (force_volume)
        mus.saved_volume = 0xffffffff;
    set_volume(mus.volume);
}

void ispace_music_resume(void)
{
    if (mus.resume)
        play_piece();
}
