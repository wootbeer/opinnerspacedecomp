/* A MIDI file played from a time to a time, as MCI's sequencer played it
 * for ISPACE.DLL: play starts with the channels as the file has set them
 * by then (programs, controllers, pitch bends; notes are not chased) and
 * stops when it gets to its end time, or to the file's end. */
#include <SDL3/SDL.h>

#include "platform/music.h"

#define CHANNELS 16

int music_seq_load(MusicSeq *q, const char *path)
{
    size_t size;
    void *data = SDL_LoadFile(path, &size);
    unsigned int length = 0;

    SDL_zerop(q);
    if (!data)
        return 0;
    q->song = size <= SDL_MAX_SINT32 ? tml_load_memory(data, (int)size) : NULL;
    SDL_free(data);
    if (!q->song)
        return 0;
    tml_get_info(q->song, NULL, NULL, NULL, NULL, &length);
    q->length = length;
    q->next = q->song;
    return 1;
}

void music_seq_free(MusicSeq *q)
{
    tml_free(q->song);
    SDL_zerop(q);
}

static void send_reset(MusicSendFn send, void *user)
{
    static const struct {
        unsigned char type, a, b;
    } reset[] = {
        {TML_CONTROL_CHANGE, TML_ALL_CTRL_OFF, 0},
        {TML_CONTROL_CHANGE, TML_SUSTAIN_SWITCH, 0},
        {TML_CONTROL_CHANGE, TML_BANK_SELECT_MSB, 0},
        {TML_CONTROL_CHANGE, TML_VOLUME_MSB, 100},
        {TML_CONTROL_CHANGE, TML_PAN_MSB, 64},
        {TML_PROGRAM_CHANGE, 0, 0},
        {TML_PITCH_BEND, 0, 0},     /* the centre, set below */
    };
    tml_message m;
    unsigned c, i;

    SDL_zero(m);
    for (c = 0; c < CHANNELS; c++)
        for (i = 0; i < SDL_arraysize(reset); i++) {
            m.type = reset[i].type;
            m.channel = (unsigned char)c;
            m.key = (char)reset[i].a;
            m.velocity = (char)reset[i].b;
            if (m.type == TML_PITCH_BEND)
                m.pitch_bend = 0x2000;
            send(&m, user);
        }
}

static int is_note(const tml_message *m)
{
    return m->type == TML_NOTE_ON || m->type == TML_NOTE_OFF || m->type == TML_KEY_PRESSURE;
}

/* Plays from `from` (PLATFORM_MUSIC_HERE: where it is) to `to` (0, or
 * past the file's end: its end), the channels first set as the file has
 * them at that time.  The messages at `from` itself go at once. */
void music_seq_play(MusicSeq *q, uint32_t from, uint32_t to, MusicSendFn send, void *user)
{
    if (from != PLATFORM_MUSIC_HERE)
        q->pos = from;
    q->to = to && to < q->length ? to : q->length;
    send_reset(send, user);
    for (q->next = q->song; q->next && q->next->time < q->pos; q->next = q->next->next)
        if (!is_note(q->next))
            send(q->next, user);
    q->playing = 1;
    q->ended = 0;
    music_seq_advance(q, 0, send, user);
}

/* Moves play on by ms and sends what has fallen due; 1 when that got it
 * to its end (the backend then stops the notes). */
int music_seq_advance(MusicSeq *q, double ms, MusicSendFn send, void *user)
{
    if (!q->playing)
        return 0;
    q->pos = SDL_min(q->pos + ms, (double)q->to);
    for (; q->next && q->next->time <= q->pos && q->next->time < q->to; q->next = q->next->next)
        send(q->next, user);
    if (q->pos < q->to)
        return 0;
    q->playing = 0;
    q->ended = 1;
    return 1;
}

/* Milliseconds until the next message or the end (-1: not playing). */
double music_seq_wait(const MusicSeq *q)
{
    uint32_t t = q->to;

    if (!q->playing)
        return -1;
    if (q->next && q->next->time < t)
        t = q->next->time;
    return t > q->pos ? t - q->pos : 0;
}
