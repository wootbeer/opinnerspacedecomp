/* The wave output ISPACE.DLL uses: Microsoft's WaveMix library (the
 * calls ISPACE.DLL makes, WAVEMIX.DLL 2.x), MMSYSTEM's sndPlaySound and
 * the wave device's volume.  Waves are 8-bit mono at 11025 Hz, as
 * WaveMix kept them for a mono session (the game's are all so); every
 * sample frame the playing waves are added, clipped to 8 bits as WaveMix
 * did, and sent to both sides at the device's left and right volume
 * (waveOutSetVolume).  Mixing runs on the platform's audio thread; the
 * state it reads is changed only under platform_audio_lock. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "platform/platform.h"

#define RATE 11025
#define CHANNELS 8              /* WaveMix's most */
#define SESSION 1               /* the one session */

struct MixWave {
    uint8_t *pcm;               /* unsigned 8-bit mono at RATE */
    uint32_t len;
};

typedef struct {
    const MixWave *wave;
    uint32_t pos;
    uint16_t loops;             /* repeats left; 0xffff: until flushed */
    HWND notify;
    int done;                   /* finished: MM_WOM_DONE to post */
} Voice;

static struct {
    int device;                 /* -1 not tried, 0 none, 1 open */
    int open;                   /* channels opened in the session */
    int active;                 /* WaveMixActivate */
    Voice ch[CHANNELS];
    Voice snd;                  /* sndPlaySound's sound */
    MixWave snd_wave;
    uint16_t vol_left, vol_right;
} mix = {-1, 0, 0, {{0}}, {0}, {0}, 0xffff, 0xffff};

/* One sample of v (0 when silent); moves it on and ends it. */
static int voice_sample(Voice *v)
{
    int s;

    if (!v->wave)
        return 0;
    s = v->wave->pcm[v->pos] - 128;
    if (++v->pos >= v->wave->len) {
        v->pos = 0;
        if (v->loops == 0) {
            v->wave = NULL;
            v->done = 1;
        } else if (v->loops != 0xffff)
            v->loops--;
    }
    return s;
}

static void mix_frames(int16_t *out, int count, void *user)
{
    int i, c;

    (void)user;
    for (i = 0; i < count; i++) {
        int s = voice_sample(&mix.snd);
        for (c = 0; c < CHANNELS && mix.active; c++)
            s += voice_sample(&mix.ch[c]);
        s = s < -128 ? -128 : s > 127 ? 127 : s;
        out[2 * i] = (int16_t)(s * 256 * (long)mix.vol_left / 0xffff);
        out[2 * i + 1] = (int16_t)(s * 256 * (long)mix.vol_right / 0xffff);
    }
}

/* The output device, opened on first use; 0 when there is none. */
int wavemix_device(void)
{
    if (mix.device < 0)
        mix.device = platform_audio_open(RATE, mix_frames, NULL);
    return mix.device;
}

/* A RIFF WAVE image as 8-bit mono at RATE: PCM of 8 or 16 bits, mono or
 * stereo, any rate (the nearest sample) [uncertain: how WaveMix
 * converted other formats; the game's own need none]. */
static int wave_from_riff(const uint8_t *p, uint32_t size, MixWave *w)
{
    uint32_t off = 12, fmt_rate = 0, i, n, data_len = 0;
    uint16_t tag = 0, chans = 0, bits = 0;
    const uint8_t *data = NULL;
    unsigned frame;

    if (size < 12 || memcmp(p, "RIFF", 4) || memcmp(p + 8, "WAVE", 4))
        return 0;
    while (off + 8 <= size) {
        uint32_t len = p[off + 4] | p[off + 5] << 8 | p[off + 6] << 16 | (uint32_t)p[off + 7] << 24;
        const uint8_t *body = p + off + 8;
        if (len > size - off - 8)
            len = size - off - 8;
        if (!memcmp(p + off, "fmt ", 4) && len >= 16) {
            tag = (uint16_t)(body[0] | body[1] << 8);
            chans = (uint16_t)(body[2] | body[3] << 8);
            fmt_rate = body[4] | body[5] << 8 | body[6] << 16 | (uint32_t)body[7] << 24;
            bits = (uint16_t)(body[14] | body[15] << 8);
        } else if (!memcmp(p + off, "data", 4)) {
            data = body;
            data_len = len;
        }
        off += 8 + len + (len & 1);
    }
    if (tag != 1 || !data || !fmt_rate || (chans != 1 && chans != 2) || (bits != 8 && bits != 16))
        return 0;
    frame = chans * bits / 8u;
    n = (uint32_t)((uint64_t)(data_len / frame) * RATE / fmt_rate);
    if (!n || !(w->pcm = malloc(n)))
        return 0;
    for (i = 0; i < n; i++) {
        const uint8_t *f = data + (uint64_t)i * fmt_rate / RATE * frame;
        w->pcm[i] = bits == 8 ? f[0] : (uint8_t)((f[1] ^ 0x80));
    }
    w->len = n;
    return 1;
}

static MixWave *new_wave(const uint8_t *riff, uint32_t size)
{
    MixWave *w = calloc(1, sizeof *w);

    if (w && !wave_from_riff(riff, size, w)) {
        free(w);
        w = NULL;
    }
    return w;
}

static uint8_t *read_file(LPCSTR dos_path, uint32_t *size)
{
    char host[1024];
    FILE *f;
    long n;
    uint8_t *p = NULL;

    if (!dos_to_host(dos_path, host, sizeof host) || !(f = fopen(host, "rb")))
        return NULL;
    if (fseek(f, 0, SEEK_END) == 0 && (n = ftell(f)) > 0 && fseek(f, 0, SEEK_SET) == 0 &&
        (p = malloc((size_t)n)) != NULL && fread(p, 1, (size_t)n, f) != (size_t)n) {
        free(p);
        p = NULL;
    }
    fclose(f);
    *size = p ? (uint32_t)n : 0;
    return p;
}

/* The bytes of a RIFF image in memory (its header gives the size). */
static uint32_t riff_size(const uint8_t *p)
{
    return memcmp(p, "RIFF", 4) ? 0 : 8 + (p[4] | p[5] << 8 | p[6] << 16 | (uint32_t)p[7] << 24);
}

/* WaveMix. */
HANDLE WaveMixConfigureInit(void)
{
    return wavemix_device() ? SESSION : 0;
}

UINT WaveMixOpenChannel(HANDLE session, int16_t count, DWORD flags)
{
    (void)flags;
    if (session != SESSION || count < 1 || count > CHANNELS)
        return MMSYSERR_INVALPARAM;
    mix.open = count;
    return 0;
}

UINT WaveMixActivate(HANDLE session, BOOL on)
{
    if (session != SESSION)
        return MMSYSERR_INVALPARAM;
    platform_audio_lock();
    mix.active = on != 0;
    platform_audio_unlock();
    return 0;
}

MixWave *WaveMixOpenWave(HANDLE session, LPCSTR dos_path)
{
    uint32_t size;
    uint8_t *p;
    MixWave *w;

    if (session != SESSION || !(p = read_file(dos_path, &size)))
        return NULL;
    w = new_wave(p, size);
    free(p);
    return w;
}

MixWave *WaveMixOpenWaveData(HANDLE session, const void *riff, DWORD size)
{
    return session == SESSION ? new_wave(riff, size) : NULL;
}

/* Starts p->wave on its channel at once, in place of anything there
 * (WMIX_CLEARQUEUE | WMIX_HIPRIORITY, the only way ISPACE.DLL plays);
 * the wave plays 1 + p->loops times [uncertain: whether wLoops counted
 * the first play].  MM_WOM_DONE goes to p->notify when it ends. */
UINT WaveMixPlay(const MIXPLAYPARAMS *p)
{
    Voice *v;

    if (p->session != SESSION || p->channel < 0 || p->channel >= mix.open || !p->wave)
        return MMSYSERR_INVALPARAM;
    if (!mix.active)
        return MMSYSERR_ERROR;
    v = &mix.ch[p->channel];
    platform_audio_lock();
    v->wave = p->wave;
    v->pos = 0;
    v->loops = p->loops;
    v->notify = p->notify;
    v->done = 0;
    platform_audio_unlock();
    return 0;
}

/* Stops channel ch, or all with WMIX_ALL, without MM_WOM_DONE
 * [uncertain: whether WaveMix posted it for flushed waves]. */
UINT WaveMixFlushChannel(HANDLE session, int16_t ch, DWORD flags)
{
    int c;

    if (session != SESSION)
        return MMSYSERR_INVALPARAM;
    platform_audio_lock();
    for (c = 0; c < CHANNELS; c++)
        if (flags & WMIX_ALL || c == ch) {
            mix.ch[c].wave = NULL;
            mix.ch[c].done = 0;
        }
    platform_audio_unlock();
    return 0;
}

UINT WaveMixFreeWave(HANDLE session, MixWave *w)
{
    int c;

    if (session != SESSION || !w)
        return MMSYSERR_INVALPARAM;
    platform_audio_lock();
    for (c = 0; c < CHANNELS; c++)
        if (mix.ch[c].wave == w)
            mix.ch[c].wave = NULL;
    platform_audio_unlock();
    free(w->pcm);
    free(w);
    return 0;
}

UINT WaveMixCloseChannel(HANDLE session, int16_t ch, DWORD flags)
{
    UINT r = WaveMixFlushChannel(session, ch, flags);

    if (!r && flags & WMIX_ALL)
        mix.open = 0;
    return r;
}

UINT WaveMixCloseSession(HANDLE session)
{
    if (session != SESSION)
        return MMSYSERR_INVALPARAM;
    WaveMixCloseChannel(session, 0, WMIX_ALL);
    WaveMixActivate(session, 0);
    return 0;
}

/* WaveMix fed the device from WaveMixPump; the platform's audio thread
 * does it here. */
void WaveMixPump(void)
{
}

/* Posts MM_WOM_DONE (wParam the channel) for the waves that have ended,
 * as WaveMix did when the device gave their buffers back. */
void wavemix_notify(void)
{
    HWND to[CHANNELS];
    int c;

    platform_audio_lock();
    for (c = 0; c < CHANNELS; c++) {
        to[c] = mix.ch[c].done ? mix.ch[c].notify : 0;
        mix.ch[c].done = 0;
    }
    platform_audio_unlock();
    for (c = 0; c < CHANNELS; c++)
        if (to[c])
            PostMessage(to[c], MM_WOM_DONE, (WPARAM)c, 0);
}

/* MMSYSTEM.  sndPlaySound plays one sound at a time: a new one (or NULL)
 * stops the last.  Supported as ISPACE.DLL calls it: SND_ASYNC, with
 * SND_MEMORY (a RIFF image) or a file name, SND_LOOP until stopped. */
BOOL sndPlaySound(LPCSTR sound, UINT flags)
{
    uint32_t size = 0;
    uint8_t *file = NULL;
    const uint8_t *riff = (const uint8_t *)sound;
    MixWave w = {NULL, 0};
    uint8_t *old;
    int ok;

    if (sound && !(flags & SND_MEMORY))
        riff = file = read_file(sound, &size);
    else if (sound)
        size = riff_size(riff);
    ok = riff && wavemix_device() && wave_from_riff(riff, size, &w);
    free(file);
    platform_audio_lock();
    old = mix.snd_wave.pcm;
    mix.snd_wave = w;
    mix.snd.wave = ok ? &mix.snd_wave : NULL;
    mix.snd.pos = 0;
    mix.snd.loops = flags & SND_LOOP ? 0xffff : 0;
    platform_audio_unlock();
    free(old);
    return ok || !sound;
}

UINT waveOutGetVolume(UINT dev, DWORD *vol)
{
    (void)dev;
    *vol = MAKELONG(mix.vol_left, mix.vol_right);
    return 0;
}

UINT waveOutSetVolume(UINT dev, DWORD vol)
{
    (void)dev;
    platform_audio_lock();
    mix.vol_left = LOWORD(vol);
    mix.vol_right = HIWORD(vol);
    platform_audio_unlock();
    return 0;
}
