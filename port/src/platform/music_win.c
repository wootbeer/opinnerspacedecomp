/* Music on Windows' own MIDI synthesizer: the file's messages sent to
 * the MIDI Mapper (midiOut) at their times by a thread of ours, timed by
 * SDL's clock.  (MCI's sequencer would time them itself, but its only
 * volume, midiOutSetVolume, is the whole program's on the Microsoft GS
 * Wavetable Synth, the effects' too; here the music volume scales each
 * channel's volume controller.)  All state is changed under lock. */
#include <SDL3/SDL.h>
#include <windows.h>
#include <mmsystem.h>

#include "platform/music.h"

#define CHANNELS 16

static struct {
    HMIDIOUT out;
    SDL_Thread *thread;
    SDL_Mutex *lock;
    SDL_Condition *wake;
    int quit;
    MusicSeq seq;
    Uint64 clock;               /* SDL_GetTicksNS() when seq.pos was moved */
    uint8_t channel_volume[CHANNELS];   /* controller 7 as the file sets it */
    float scale;                /* the music volume, as a factor of controller 7 */
} win;

static void out(int status, int data1, int data2)
{
    midiOutShortMsg(win.out, (DWORD)status | (DWORD)(data1 & 0x7f) << 8 | (DWORD)(data2 & 0x7f) << 16);
}

/* Controller 7 as sent: the synthesizer's level goes with its square
 * (General MIDI's curve), so the music volume v scales it by sqrt(v). */
static void out_channel_volume(int ch)
{
    out(0xb0 | ch, TML_VOLUME_MSB, (int)(win.channel_volume[ch] * win.scale + 0.5f));
}

static void send_message(const tml_message *m, void *user)
{
    int status = m->type | m->channel;

    (void)user;
    switch (m->type) {
    case TML_NOTE_OFF:
    case TML_NOTE_ON:
    case TML_KEY_PRESSURE:
        out(status, m->key, m->velocity);
        break;
    case TML_CONTROL_CHANGE:
        if (m->control != TML_VOLUME_MSB) {
            out(status, m->control, m->control_value);
            break;
        }
        win.channel_volume[m->channel] = (uint8_t)m->control_value;
        out_channel_volume(m->channel);
        break;
    case TML_PROGRAM_CHANGE:
    case TML_CHANNEL_PRESSURE:
        out(status, m->program, 0);
        break;
    case TML_PITCH_BEND:
        out(status, m->pitch_bend, m->pitch_bend >> 7);
        break;
    default:
        break;
    }
}

/* Every note ends (sustained ones too), with its release. */
static void notes_off(void)
{
    int ch;

    for (ch = 0; ch < CHANNELS; ch++) {
        out(0xb0 | ch, TML_SUSTAIN_SWITCH, 0);
        out(0xb0 | ch, TML_ALL_NOTES_OFF, 0);
    }
}

/* Moves play on to now. */
static void catch_up(void)
{
    Uint64 now = SDL_GetTicksNS();

    if (music_seq_advance(&win.seq, (double)(now - win.clock) / SDL_NS_PER_MS, send_message, NULL))
        notes_off();
    win.clock = now;
}

static int SDLCALL run(void *unused)
{
    (void)unused;
    SDL_LockMutex(win.lock);
    while (!win.quit) {
        catch_up();
        SDL_WaitConditionTimeout(win.wake, win.lock,
                                 win.seq.playing ? (Sint32)music_seq_wait(&win.seq) + 1 : -1);
    }
    SDL_UnlockMutex(win.lock);
    return 0;
}

static void win_close(void)
{
    if (win.thread) {
        SDL_LockMutex(win.lock);
        win.quit = 1;
        SDL_SignalCondition(win.wake);
        SDL_UnlockMutex(win.lock);
        SDL_WaitThread(win.thread, NULL);
    }
    if (win.out) {
        notes_off();
        midiOutClose(win.out);
    }
    SDL_DestroyCondition(win.wake);
    SDL_DestroyMutex(win.lock);
    music_seq_free(&win.seq);
    SDL_zero(win);
}

static int win_open(const char *path, const char *soundfont)
{
    (void)soundfont;
    SDL_zero(win);
    win.scale = 1.0f;
    SDL_memset(win.channel_volume, 100, sizeof win.channel_volume);
    if (!music_seq_load(&win.seq, path))
        return 0;
    if (midiOutOpen(&win.out, MIDI_MAPPER, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        SDL_Log("music: no MIDI output");
        win.out = NULL;
        win_close();
        return 0;
    }
    win.lock = SDL_CreateMutex();
    win.wake = SDL_CreateCondition();
    win.thread = win.lock && win.wake ? SDL_CreateThread(run, "music", NULL) : NULL;
    if (!win.thread) {
        win_close();
        return 0;
    }
    return 1;
}

static void win_play(uint32_t from, uint32_t to)
{
    SDL_LockMutex(win.lock);
    music_seq_play(&win.seq, from, to, send_message, NULL);
    win.clock = SDL_GetTicksNS();
    SDL_SignalCondition(win.wake);
    SDL_UnlockMutex(win.lock);
}

static void win_pause(void)
{
    SDL_LockMutex(win.lock);
    if (win.seq.playing) {
        catch_up();
        win.seq.playing = 0;
        notes_off();
    }
    SDL_UnlockMutex(win.lock);
}

static int win_ended(void)
{
    int ended;

    SDL_LockMutex(win.lock);
    ended = win.seq.ended;
    win.seq.ended = 0;
    SDL_UnlockMutex(win.lock);
    return ended;
}

static void win_volume(uint16_t left, uint16_t right)
{
    int ch;

    SDL_LockMutex(win.lock);
    win.scale = SDL_sqrtf(SDL_max(left, right) / 65535.0f);
    for (ch = 0; ch < CHANNELS; ch++)
        out_channel_volume(ch);
    SDL_UnlockMutex(win.lock);
}

const MusicBackend music_win = {
    win_open, win_play, win_pause, win_ended, win_close, win_volume,
};
