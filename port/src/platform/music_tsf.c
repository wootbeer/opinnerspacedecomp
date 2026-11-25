/* Music played by TinySoundFont on the user's SoundFont (INSPACE.INI
 * [Port] SoundFont=), rendered into the SDL audio device beside the
 * effects through a stream of its own.  The MIDI messages go to the
 * synthesizer between blocks of BLOCK frames (1.5 ms at 44.1 kHz); all
 * state is changed under the stream's lock, which SDL holds while it
 * asks for more. */
#include <SDL3/SDL.h>

#include "platform/music.h"
#include "platform/sdl_audio.h"
#include "tsf.h"

#define BLOCK 64
#define GAIN_DB (-14.0f)        /* the synthesizer's level: see NOTES-port.md "Music" */

static struct {
    tsf *synth;                 /* the SoundFont, kept loaded once read */
    char soundfont[1024];       /* the file it came from (or failed to) */
    int rate;
    SDL_AudioStream *stream;
    MusicSeq seq;
    float left, right;
} mus = {NULL, "", 0, NULL, {0}, 1.0f, 1.0f};

static void send_message(const tml_message *msg, void *user)
{
    tsf *f = user;

    switch (msg->type) {
    case TML_NOTE_ON:
        tsf_channel_note_on(f, msg->channel, msg->key, msg->velocity / 127.0f);
        break;
    case TML_NOTE_OFF:
        tsf_channel_note_off(f, msg->channel, msg->key);
        break;
    case TML_PROGRAM_CHANGE:
        tsf_channel_set_presetnumber(f, msg->channel, msg->program, msg->channel == 9);
        break;
    case TML_PITCH_BEND:
        tsf_channel_set_pitchwheel(f, msg->channel, msg->pitch_bend);
        break;
    case TML_CONTROL_CHANGE:
        tsf_channel_midi_control(f, msg->channel, msg->control, msg->control_value);
        break;
    default:
        break;
    }
}

static void SDLCALL render(void *userdata, SDL_AudioStream *stream, int additional, int total)
{
    float buf[2 * BLOCK];
    int i;

    (void)userdata;
    (void)total;
    for (; additional > 0; additional -= (int)sizeof buf) {
        tsf_render_float(mus.synth, buf, BLOCK, 0);
        for (i = 0; i < BLOCK; i++) {
            buf[2 * i] *= mus.left;
            buf[2 * i + 1] *= mus.right;
        }
        SDL_PutAudioStreamData(stream, buf, sizeof buf);
        if (music_seq_advance(&mus.seq, BLOCK * 1000.0 / mus.rate, send_message, mus.synth))
            tsf_note_off_all(mus.synth);
    }
}

/* The SoundFont at path, read once (a file that fails is not read
 * again); the synthesizer set to the device's rate. */
static int load_soundfont(const char *path, int rate)
{
    void *data;
    size_t size;

    if (SDL_strcmp(path, mus.soundfont) != 0) {
        tsf_close(mus.synth);
        SDL_strlcpy(mus.soundfont, path, sizeof mus.soundfont);
        data = SDL_LoadFile(path, &size);
        mus.synth = data && size <= SDL_MAX_SINT32 ? tsf_load_memory(data, (int)size) : NULL;
        SDL_free(data);
        mus.rate = 0;
        if (!mus.synth)
            SDL_Log("music: cannot read the SoundFont %s", path);
    }
    if (mus.synth && mus.rate != rate) {
        tsf_set_output(mus.synth, TSF_STEREO_INTERLEAVED, rate, GAIN_DB);
        mus.rate = rate;
    }
    return mus.synth != NULL;
}

static int tsf_open(const char *path, const char *soundfont)
{
    SDL_AudioDeviceID device = platform_sdl_audio_device();
    SDL_AudioSpec spec;

    if (!device || !SDL_GetAudioDeviceFormat(device, &spec, NULL))
        return 0;
    spec.format = SDL_AUDIO_F32;
    spec.channels = 2;
    if (!load_soundfont(soundfont, spec.freq) || !music_seq_load(&mus.seq, path))
        return 0;
    mus.stream = SDL_CreateAudioStream(&spec, NULL);
    if (!mus.stream || !SDL_SetAudioStreamGetCallback(mus.stream, render, NULL) ||
        !SDL_BindAudioStream(device, mus.stream)) {
        SDL_Log("music: %s", SDL_GetError());
        SDL_DestroyAudioStream(mus.stream);
        mus.stream = NULL;
        music_seq_free(&mus.seq);
        return 0;
    }
    return 1;
}

static void tsf_play(uint32_t from, uint32_t to)
{
    SDL_LockAudioStream(mus.stream);
    music_seq_play(&mus.seq, from, to, send_message, mus.synth);
    SDL_UnlockAudioStream(mus.stream);
}

static void tsf_pause(void)
{
    SDL_LockAudioStream(mus.stream);
    mus.seq.playing = 0;
    tsf_note_off_all(mus.synth);
    SDL_UnlockAudioStream(mus.stream);
}

static int tsf_ended(void)
{
    int ended;

    SDL_LockAudioStream(mus.stream);
    ended = mus.seq.ended;
    mus.seq.ended = 0;
    SDL_UnlockAudioStream(mus.stream);
    return ended;
}

/* The sound stops at once; the SoundFont stays loaded for the next
 * file. */
static void tsf_close_music(void)
{
    SDL_DestroyAudioStream(mus.stream);
    mus.stream = NULL;
    music_seq_free(&mus.seq);
    tsf_reset(mus.synth);
}

static void tsf_volume(uint16_t left, uint16_t right)
{
    SDL_LockAudioStream(mus.stream);
    mus.left = left / 65535.0f;
    mus.right = right / 65535.0f;
    SDL_UnlockAudioStream(mus.stream);
}

const MusicBackend music_tsf = {
    tsf_open, tsf_play, tsf_pause, tsf_ended, tsf_close_music, tsf_volume,
};
