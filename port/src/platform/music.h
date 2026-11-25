/* Inside the platform layer: the music backends behind platform_music_*
 * (platform_music.c picks one) and the MIDI file sequencing that the
 * backends which send the notes themselves share (music_seq.c). */
#ifndef MUSIC_H
#define MUSIC_H

#include "platform/platform.h"
#include "tml.h"

/* One way of playing a .MID file, with platform_music_*'s meanings. */
typedef struct {
    int (*open)(const char *path, const char *soundfont);
    void (*play)(uint32_t from, uint32_t to);
    void (*pause)(void);
    int (*ended)(void);
    void (*close)(void);
    void (*volume)(uint16_t left, uint16_t right);
} MusicBackend;

extern const MusicBackend music_tsf;    /* music_tsf.c: TinySoundFont */
#ifdef _WIN32
extern const MusicBackend music_win;    /* music_win.c: Windows' MIDI output */
#endif

/* A MIDI file's messages played from a time to a time (milliseconds).
 * The backend moves it on as its clock runs; the messages that fall due
 * go to its send function. */
typedef void (*MusicSendFn)(const tml_message *m, void *user);

typedef struct {
    tml_message *song;          /* all messages, in time order */
    tml_message *next;          /* the next one to send */
    uint32_t length;            /* the time of the last message */
    double pos;                 /* where play is */
    uint32_t to;                /* where it ends */
    int playing;
    int ended;                  /* got to `to` (cleared when read) */
} MusicSeq;

int music_seq_load(MusicSeq *q, const char *path);
void music_seq_free(MusicSeq *q);
void music_seq_play(MusicSeq *q, uint32_t from, uint32_t to, MusicSendFn send, void *user);
int music_seq_advance(MusicSeq *q, double ms, MusicSendFn send, void *user);
double music_seq_wait(const MusicSeq *q);

#endif
