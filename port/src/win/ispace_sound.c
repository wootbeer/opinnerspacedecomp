/* ISPACE.DLL's sound: ordinals 7 (9:0000, set-up and control), 8 (9:076c,
 * volume and balance from where the followed sound is) and 9 (9:0c42,
 * play a sound), the NotifyClass window (ordinal 31, 9:2ac4) and the
 * dialogs' sound effect (9:298c).
 *
 * A sound is WAVE resource 100 + id (type 100) of SND_FX.DLL or, for
 * voices, <Language>_FX.DLL, both in INI SndPath.  With MixChannels above
 * 1 they play through WaveMix (wavemix.c) on that many channels, else
 * through sndPlaySound, one at a time.  The DLL keeps a table of what
 * each channel plays and follows one sound: ordinal 8 sets the wave
 * device's left and right volume, for everything playing, from where
 * that sound is.  The DLL looked for WAVEMIX.DLL in the Windows folder;
 * the port's is always there. */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "ispace.h"

#define INI "INSPACE.INI"
#define APP "Inner Space"
#define SOUNDS 0x52             /* ids 0-0x51 */
#define MAX_CHANNELS 8
#define NO_CHANNEL MAX_CHANNELS /* DS:21a2 following nothing: a ninth slot */
#define RES_TYPE 100            /* the sounds' resource type; id 100 + sound */
#define FAR_X -6000             /* a position for sounds from nowhere: full volume */
#define PRELOAD_X -11111        /* load the sound, do not play it */
#define NOTIFY_CLASS "NotifyClass"
#define CS_GLOBALCLASS 0x4000

/* DS:2224, set by 9:25c6. */
#define F_VOICE 1               /* in the voice DLL */
#define F_ON_DEMAND 2           /* loaded when first played; freed by mode 2 */
#define F_PURGE 4               /* freed by mode 2 even without PurgeSound */

static const uint8_t sound_flags[SOUNDS] = {
    0, 2, 2, 0, 2, 6, 0, 2, 0, 6, 6, 6, 6, 6, 6, 6,
    6, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 0, 0, 0, 1, 0, 4, 2, 3, 2, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 2, 6, 7, 3, 0, 2, 3, 3, 3, 6, 7, 7, 7, 6, 7,
    7, 7,
};

/* 9:0c42: milliseconds after sound 0x26 + i (played on screen) during
 * which sounds that do not loop are not started. */
static const int16_t quiet_ms[0x24] = {
    900, 0, 0, 0, 0, 0, 730, 900, 1000, 900, 600, 1300, 1100, 1250, 510, 300,
    700, 540, 300, 0, 0, 0, 0, 350, 640, 750, 520, 0, 0, 0, 0, 0,
    0, 660, 960, 700,
};

typedef struct {                /* DS:1760, 12 bytes each */
    int16_t id;                 /* 0: free */
    DWORD start;
    int16_t on_screen;          /* the source was in view (9:0c42's r) */
    int16_t voice;
} Channel;

typedef struct {                /* DS:187c, DS:17d8 */
    const char *riff;           /* for sndPlaySound */
    MixWave *wave;              /* for WaveMix */
} Sound;

static IspaceSettings cfg = {.volume = 100, .balance = 50};

static struct {
    int16_t fx_volume;          /* DS:06a0 */
    int16_t music_volume;       /* DS:2288 */
    HINSTANCE lib[2];           /* DS:068c: SND_FX.DLL, <Language>_FX.DLL */
    int16_t lib_refs[2];        /* DS:19d8 */
    int16_t channels;           /* DS:219e MixChannels */
    int16_t opened;             /* DS:219c */
    HANDLE session;             /* DS:21aa */
    int16_t active;             /* DS:2222 */
    HWND notify;                /* DS:21ae */
    Channel ch[MAX_CHANNELS + 1];
    MixWave *file_wave[MAX_CHANNELS];   /* DS:173c: named sounds playing */
    Sound sound[SOUNDS];
    int16_t followed;           /* DS:21a0: the sound followed (0: none) */
    int16_t followed_ch;        /* DS:21a2 */
    int16_t on_screen_count;    /* DS:21a4 */
    int16_t busy;               /* DS:21a8: channels in use */
    DWORD quiet_until;          /* DS:0cf2 */
    int16_t last_cheer;         /* DS:0cfc: sound 0x66's last pick */
    int16_t last_alt;           /* DS:0cfa: sound 0x67's last pick */
    POINT world;                /* DS:19c8: the wave's size (mode 0) */
    POINT view;                 /* DS:19c4: the view's size (ordinal 8) */
    POINT offset;               /* DS:2282 */
    DWORD wave_volume;          /* DS:06a4: the game's device volume */
    DWORD saved_volume;         /* DS:06ac: the device volume before the game's */
    DWORD set_volume;           /* DS:0cee: the last one set */
    uint32_t seed;              /* DS:0b8c: the DLL's own rand */
} snd = {
    .fx_volume = 100, .wave_volume = 0xffffffff, .saved_volume = 0xffffffff,
    .followed_ch = NO_CHANNEL, .seed = 1,
};

/* The DLL's C runtime rand (3:0668), separate from the game's.  The DLL
 * seeds it from the time in dialogs the port does not have yet. */
static int16_t dll_rand(void)
{
    snd.seed = snd.seed * 214013u + 2531011u;
    return (int16_t)(snd.seed >> 16 & 0x7fff);
}

IspaceSettings *ispace_settings(void)
{
    return &cfg;
}

/* 9:0a9e: effects and music volume from SoundVolume and FXMusic. */
void ispace_sound_mix_volumes(void)
{
    snd.fx_volume = cfg.balance <= 50 ? cfg.volume
                                      : (int16_t)((100 - cfg.balance) * 2 * cfg.volume / 100);
    snd.music_volume = cfg.balance >= 50 ? cfg.volume : (int16_t)(cfg.balance * 2 * cfg.volume / 100);
}

/* 9:0b62: the device volume, when it changes; 0 when setting it fails. */
static int set_wave_volume(DWORD v)
{
    if (v == snd.set_volume)
        return 1;
    snd.set_volume = v;
    return waveOutSetVolume(0, v) == 0;
}

static void profile_put_int(const char *key, int16_t v)
{
    char buf[8];

    SDL_snprintf(buf, sizeof buf, "%d", v);
    WritePrivateProfileString(APP, key, buf, INI);
}

/* 9:22ca: the INI's sound settings, Enhance, Detail and Quick, the
 * joystick's (ispace_joy.c) and what the
 * wave device can do.  A synchronous device (a PC speaker driver) turns
 * all sound off, in the INI too, unless AllowSound is set. */
void ispace_sound_read_settings(void)
{
    WAVEOUTCAPS caps;

    cfg.fx_on = GetPrivateProfileInt(APP, "SoundFX", 1, INI);
    cfg.voice_on = GetPrivateProfileInt(APP, "VoiceFX", 1, INI);
    ispace_music_set_on(GetPrivateProfileInt(APP, "Music", 1, INI));
    cfg.volume = GetPrivateProfileInt(APP, "SoundVolume", 100, INI);
    cfg.balance = GetPrivateProfileInt(APP, "FXMusic", 50, INI);
    cfg.stereo = GetPrivateProfileInt(APP, "StereoEffect", 2, INI);
    cfg.purge = GetPrivateProfileInt(APP, "PurgeSound", 1, INI);
    cfg.swap = GetPrivateProfileInt(APP, "StereoSwap", 0, INI);
    ispace_joy_read_settings();
    ispace_sound_mix_volumes();
    if (!waveOutGetNumDevs()) {
        cfg.device_best = 0;
    } else {
        waveOutGetDevCaps(0, &caps, sizeof caps);
        if (caps.dwSupport & WAVECAPS_SYNC && !GetPrivateProfileInt(APP, "AllowSound", 0, INI)) {
            cfg.device_best = cfg.voice_on = cfg.fx_on = 0;
            ispace_music_set_on(0);
            profile_put_int("Music", 0);
            profile_put_int("SoundFX", 0);
            profile_put_int("VoiceFX", 0);
        } else if (caps.dwSupport & WAVECAPS_VOLUME)
            cfg.device_best = caps.dwSupport & WAVECAPS_LRVOLUME ? 3 : 2;
        else
            cfg.device_best = 1;
    }
    cfg.system = GetPrivateProfileInt(APP, "SoundSystem", -1, INI);
    if (cfg.system == -1) {
        cfg.system = cfg.device_best;
        profile_put_int("SoundSystem", cfg.system);
    }
    cfg.enhance = GetPrivateProfileInt(APP, "Enhance", 1, INI);
    cfg.detail = GetPrivateProfileInt(APP, "Detail", 3, INI);
    cfg.quick = GetPrivateProfileInt(APP, "Quick", 1, INI);
    if (cfg.system > cfg.device_best)
        cfg.system = cfg.device_best;
}

/* INI SndPath, ending in '\' (an empty one gives "\"). */
void ispace_sound_path(char *path, size_t size)
{
    size_t n;

    GetPrivateProfileString(APP, "SndPath", "", path, 0x6d, INI);
    n = SDL_strlen(path);
    if (!n || path[n - 1] != '\\')
        SDL_strlcat(path, "\\", size);
}

/* 9:00ba for n 0 and 1: SND_FX.DLL or <Language>_FX.DLL, counting its
 * users.  A missing one turns its sounds off, in the INI too. */
static void load_library(int n)
{
    static const char *const off_key[2] = {"SoundFX", "VoiceFX"};
    char path[0x80], lang[5], text[0x100], msg[0x50];
    OFSTRUCT of;
    HINSTANCE h;

    ispace_sound_path(path, sizeof path);
    snd.lib_refs[n]++;
    if (snd.lib[n])
        return;
    if (n == 0) {
        ispace_music_save_volume();
        waveOutGetVolume(0, &snd.saved_volume);
        SDL_strlcat(path, "SND_FX.DLL", sizeof path);
    } else {
        GetPrivateProfileString(APP, "Language", "", lang, sizeof lang, INI);
        SDL_strlcat(path, lang, sizeof path);
        SDL_strlcat(path, "_FX.DLL", sizeof path);
    }
    if (OpenFile(path, &of, OF_EXIST) == HFILE_ERROR) {
        *(n == 0 ? &cfg.fx_on : &cfg.voice_on) = 0;
        profile_put_int(off_key[n], 0);
        return;
    }
    h = LoadLibrary(path);
    if (h < 32) {
        LoadString(ispace_lang_module(), 0x7ea, msg, sizeof msg);
        SDL_snprintf(text, sizeof text, "%s%s", path, msg);
        MessageBox(0, text, APP, MB_ICONEXCLAMATION);
        return;
    }
    snd.lib[n] = h;
}

/* 9:0390. */
static void free_library(int n)
{
    if (snd.lib_refs[n] > 0)
        snd.lib_refs[n]--;
    if (!snd.lib_refs[n] && snd.lib[n]) {
        FreeLibrary(snd.lib[n]);
        snd.lib[n] = 0;
    }
}

static int loaded(int16_t a)
{
    return snd.sound[a].riff || snd.sound[a].wave;
}

/* 9:25c6: sound a from its DLL, in the form the player needs.  Without
 * force, on-demand sounds are left; sounds turned off never load. */
static void load_wave(int16_t a, int force)
{
    int voice = sound_flags[a] & F_VOICE;
    HINSTANCE lib = snd.lib[voice];
    const uint8_t *riff;
    uint32_t size;

    if (!cfg.system || loaded(a) || !lib)
        return;
    if ((!force && sound_flags[a] & F_ON_DEMAND) || (voice ? !cfg.voice_on : !cfg.fx_on))
        return;
    riff = module_resource(lib, MAKEINTRESOURCE(RES_TYPE), MAKEINTRESOURCE(100 + a), &size);
    if (!riff)
        return;
    if (snd.channels == 1)
        snd.sound[a].riff = (const char *)riff;
    else if (snd.session && snd.active)
        snd.sound[a].wave = WaveMixOpenWaveData(snd.session, riff, size);
}

/* 9:28d2: sound a let go; without force only on-demand sounds, and of
 * those only F_PURGE ones unless PurgeSound is set.  (The DLL freed by
 * the current channel count, not by how the sound was loaded.) */
static void free_wave(int16_t a, int force)
{
    if (!force && (!(sound_flags[a] & F_ON_DEMAND) || (!cfg.purge && !(sound_flags[a] & F_PURGE))))
        return;
    if (snd.sound[a].wave)
        WaveMixFreeWave(snd.session, snd.sound[a].wave);
    snd.sound[a].riff = NULL;
    snd.sound[a].wave = NULL;
}

/* 9:1174: everything stopped, no sound followed. */
static void stop_all(void)
{
    int16_t i;

    snd.followed = 0;
    snd.followed_ch = NO_CHANNEL;
    if (snd.session && snd.active)
        WaveMixFlushChannel(snd.session, 0, WMIX_ALL);
    snd.busy = snd.on_screen_count = 0;
    for (i = 0; i < snd.channels; i++)
        memset(&snd.ch[i], 0, sizeof snd.ch[i]);
    if (snd.channels == 1)
        sndPlaySound(NULL, 0);
}

/* Ordinal 31 (9:2ac4): NotifyClass, told when a channel's sound has
 * ended; it also gets the Joystick dialog's timer and the music's MCI
 * notifications. */
static LRESULT notify_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int16_t c = (int16_t)wp, i;

    if (msg == WM_TIMER) {
        ispace_joy_timer();
        return 0;
    }
    if (msg != MM_WOM_DONE)
        return ispace_music_message(hwnd, msg, wp, lp);
    if (c < 0 || c >= MAX_CHANNELS)
        return 0;
    if (c == snd.followed_ch) {
        snd.followed_ch = NO_CHANNEL;
        snd.followed = 0;
    }
    if (snd.file_wave[c]) {
        WaveMixFreeWave(snd.session, snd.file_wave[c]);
        snd.file_wave[c] = NULL;
    }
    memset(&snd.ch[c], 0, sizeof snd.ch[c]);
    snd.on_screen_count = 0;
    for (i = 0; i < snd.channels; i++)
        if (snd.ch[i].on_screen)
            snd.on_screen_count++;
    snd.busy--;
    return 0;
}

HWND ispace_sound_window(void)
{
    return snd.notify;
}

/* 9:2a60. */
static int register_notify(void)
{
    WNDCLASS wc;

    memset(&wc, 0, sizeof wc);
    wc.style = CS_GLOBALCLASS;          /* the window is hidden: no brush */
    wc.lpfnWndProc = notify_proc;
    wc.hInstance = ispace_module();
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.lpszClassName = NOTIFY_CLASS;
    return RegisterClass(&wc) != 0;
}

/* 9:0624: stops everything; the last user (or force) closes the mixer. */
static void close_mixer(int force)
{
    stop_all();
    if (!force && --snd.opened)
        return;
    if (snd.notify) {
        DestroyWindow(snd.notify);
        snd.notify = 0;
        UnregisterClass(NOTIFY_CLASS, ispace_module());
    }
    if (!snd.session)
        return;
    WaveMixCloseChannel(snd.session, 0, WMIX_ALL);
    WaveMixCloseSession(snd.session);
    snd.session = 0;
    snd.active = 0;
}

/* 9:04e0: MixChannels channels of WaveMix, or sndPlaySound for one.
 * restart closes it first (the Audio Options dialog's new channel
 * count); one_channel forces sndPlaySound (mode 0's negative width).
 * More than 8 channels (only by editing the INI) overran the DLL's
 * table: 8. */
static void open_mixer(int restart, int one_channel)
{
    snd.channels = GetPrivateProfileInt(APP, "MixChannels", 4, INI);
    if (snd.channels > MAX_CHANNELS)
        snd.channels = MAX_CHANNELS;
    if (one_channel)
        snd.channels = 1;
    if (restart) {
        close_mixer(1);
        if (!snd.opened)
            snd.opened = 1;
    } else if (++snd.opened > 1)
        return;
    snd.active = 0;
    if (!snd.notify && register_notify())
        snd.notify = CreateWindow(NOTIFY_CLASS, NULL, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0,
                                  ispace_module(), NULL);
    stop_all();
    if (snd.channels == 1) {
        snd.session = 0;
        return;
    }
    snd.session = WaveMixConfigureInit();
    if (!snd.session || WaveMixOpenChannel(snd.session, snd.channels, WMIX_OPENCOUNT))
        return;
    WaveMixActivate(snd.session, 1);
    snd.active = 1;
}

/* 9:0448 (mode 0): the wave's size, the settings, the sound DLLs, the
 * mixer and the sounds that are not loaded on demand; a negative w asks
 * for one channel (sndPlaySound) and only sound 0x23 [uncertain: what
 * for; the game passes none]. */
static void sound_init(int16_t w, int16_t h)
{
    int only_one = w < 0;
    int16_t i;

    if (only_one)
        w = (int16_t)-w;
    if (w) {
        snd.world.x = w;
        snd.world.y = h;
    }
    ispace_sound_read_settings();
    load_library(0);
    load_library(1);
    if (cfg.system)
        open_mixer(0, only_one);
    if (only_one)
        load_wave(0x23, 0);
    else
        for (i = 0; i < SOUNDS; i++)
            load_wave(i, 0);
}

/* 9:03d8: library n let go whatever its users: everything stopped, the
 * sounds freed (all of them while SND_FX.DLL has at most one user, else
 * the on-demand ones).  A sound left in the DLL's memory would have
 * pointed into the freed library; those of library n go too. */
static void drop_library(int n)
{
    int16_t i;

    stop_all();
    for (i = 0; i < SOUNDS; i++)
        free_wave(i, snd.lib_refs[0] <= 1 || (snd.sound[i].riff && (sound_flags[i] & F_VOICE) == n));
    snd.lib_refs[n] = 0;
    if (snd.lib[n]) {
        FreeLibrary(snd.lib[n]);
        snd.lib[n] = 0;
    }
}

void ispace_sound_apply(int16_t channels)
{
    int reload = 0, n;
    int16_t i;

    for (n = 0; n < 2; n++)
        if (!(n ? cfg.voice_on : cfg.fx_on) && snd.lib[n])
            drop_library(n);
    for (n = 0; n < 2; n++)
        if ((n ? cfg.voice_on : cfg.fx_on) && !snd.lib[n]) {
            load_library(n);
            reload = 1;
        }
    if (channels != snd.channels && cfg.system) {
        drop_library(0);
        drop_library(1);
        snd.channels = channels;
        load_library(0);
        load_library(1);
        reload = 1;
        open_mixer(1, 0);
    }
    if (reload)
        for (i = 0; i < SOUNDS; i++)
            load_wave(i, 0);
}

int16_t ispace_sound_channels(void)
{
    return snd.channels;
}

HINSTANCE ispace_sound_library(int n)
{
    return snd.lib[n];
}

/* 9:06a0 (mode 1). */
static void sound_end(void)
{
    int16_t i;

    for (i = 0; i < SOUNDS; i++)
        free_wave(i, snd.lib_refs[0] <= 1);
    if (cfg.system)
        close_mixer(0);
    free_library(0);
    free_library(1);
    ispace_music_restore_volume();
    set_wave_volume(snd.saved_volume);
}

/* 9:0af2 (mode 3): the game loses the focus: its sound stops and the
 * device gets its volume from before back. */
static void sound_deactivate(void)
{
    if (!cfg.system)
        return;
    stop_all();
    waveOutGetVolume(0, &snd.wave_volume);
    ispace_music_deactivate();
    set_wave_volume(snd.saved_volume);
    if (snd.session) {
        WaveMixActivate(snd.session, 0);
        snd.active = 0;
    }
}

/* 9:0ba6 (mode 4): it has the focus again; ForceVol makes the volume put
 * back later full. */
static void sound_activate(void)
{
    int force = GetPrivateProfileInt(APP, "ForceVol", 0, INI) != 0;

    if (!cfg.system)
        return;
    waveOutGetVolume(0, &snd.saved_volume);
    if (force)
        snd.saved_volume = 0xffffffff;
    ispace_music_activate(force);
    set_wave_volume(snd.wave_volume);
    if (snd.session) {
        WaveMixActivate(snd.session, 1);
        snd.active = 1;
    }
    ispace_music_resume();
}

/* Ordinal 7 (9:0000): sound control by mode; a is the long the game
 * passes (the wave's size, or for mode 11 the music command and its
 * wait flag).  Modes 5-8 load and free the language DLL and IGRAPHIC.DLL,
 * which the port's modules load when first used. */
int16_t ispace_sound_control(int32_t a, int16_t mode)
{
    int16_t i;

    switch (mode) {
    case 0:
        sound_init(LO16(a), HI16(a));
        break;
    case 1:
        sound_end();
        break;
    case 2:                     /* 9:073a: between waves */
        stop_all();
        for (i = 0; i < SOUNDS; i++)
            free_wave(i, 0);
        break;
    case 3:
        sound_deactivate();
        break;
    case 4:
        sound_activate();
        break;
    case 9:                     /* 9:360a */
        if (snd.session && snd.active)
            WaveMixPump();
        break;
    case 10:                    /* the screen saver's volume */
        cfg.volume = GetPrivateProfileInt(APP, "SaverVolume", 0, INI);
        ispace_sound_mix_volumes();
        break;
    case 11:                    /* 9:3906 */
        ispace_music((int16_t)LO16(a), (int16_t)HI16(a));
        break;
    default:
        break;
    }
    return 1;
}

/* The level (0-100) of a sound at distance d along an axis, scaled by
 * StereoEffect: for x the near and far ear, for y both. */
static int16_t scaled(int16_t d)
{
    switch (cfg.stereo) {
    case 0: return (int16_t)(d / 4);
    case 1: return (int16_t)(d / 2);
    case 3: return (int16_t)(d + d / 2);
    default: return d;
    }
}

static void x_levels(int16_t d, int16_t *near_ear, int16_t *far_ear)
{
    if (d < 300) {
        *near_ear = (int16_t)(d / 60 + 95);
        *far_ear = (int16_t)((int16_t)(d * 10) / -35 + 95);
    } else if (d < 600) {
        d = (int16_t)(d - 300);
        *near_ear = (int16_t)(d / -6 + 100);
        *far_ear = (int16_t)(d / -30 + 10);
    } else if (d < 900) {
        d = (int16_t)(d - 600);
        *near_ear = (int16_t)((int16_t)(d * 10) / -85 + 50);
        *far_ear = 0;
    } else {
        *near_ear = 15;
        *far_ear = 0;
    }
}

static int16_t y_level(int16_t d)
{
    if (d < 300)
        return (int16_t)(d / -12 + 100);
    if (d < 600)
        return (int16_t)((int16_t)((d - 300) * 10) / -55 + 75);
    if (d < 900)
        return (int16_t)((d - 600) / -60 + 20);
    return 15;
}

/* The distance from the view's middle along one axis, the shorter way
 * round the wave (which wraps). */
static int16_t axis_distance(int16_t p, int16_t view, int16_t offset, int16_t world)
{
    int16_t d = (int16_t)(p - view / 2 - offset);

    if (abs(d) > world / 2)
        d = (int16_t)((d < 0 ? p + world : p - world) - view / 2 - offset);
    return d;
}

/* 2:0850: about the length of (a, b): one Newton step from the larger
 * plus half the smaller. */
static int32_t length(int32_t a, int32_t b)
{
    int32_t aa = a < 0 ? -a : a, bb = b < 0 ? -b : b;
    int32_t m = aa < bb ? aa / 2 + bb : bb / 2 + aa;

    return m ? ((b * b + a * a) / m + m) / 2 : 1;
}

/* An ear's level (0-100) at the effects volume, as a device volume. */
static uint16_t device_level(uint16_t level)
{
    level = (uint16_t)((uint32_t)level * (uint16_t)snd.fx_volume / 100);
    if (level > 100)
        level = 100;
    return (uint16_t)((uint32_t)level * 0xffff / 100);
}

/* Ordinal 8 (9:076c): the device volume for the followed sound at p (in
 * the view; FAR_X: full) in a view of size view (offset by x, y when x is
 * not 0).  A quiet sound no longer counts as on screen.  Returns 1 when
 * the volume is set or unchanged (as the DLL leaves it: 0 then). */
int16_t ispace_sound_follow(POINT p, int16_t x, int16_t y, int32_t view)
{
    int16_t dx, dy, near_ear, far_ear, both, left, right, t;
    int set;

    if (cfg.system <= 1)
        return 0;
    if (x) {
        snd.offset.x = x;
        snd.offset.y = y;
        snd.view.x = LO16(view);
        snd.view.y = HI16(view);
    }
    ispace_music_center();
    if (p.x == FAR_X) {
        left = right = 80;
        both = 100;
    } else {
        dx = axis_distance(p.x, snd.view.x, snd.offset.x, snd.world.x);
        dy = axis_distance(p.y, snd.view.y, snd.offset.y, snd.world.y);
        x_levels(scaled((int16_t)abs(dx)), &near_ear, &far_ear);
        both = y_level(scaled((int16_t)abs(dy)));
        left = dx < 0 ? near_ear : far_ear;
        right = dx < 0 ? far_ear : near_ear;
    }
    right = (int16_t)((uint32_t)(uint16_t)both * (uint16_t)right / 100);
    left = (int16_t)((uint32_t)(uint16_t)both * (uint16_t)left / 100);
    if ((int16_t)length(left, right) < 65)
        snd.ch[snd.followed_ch].on_screen = 0;
    left = (int16_t)device_level((uint16_t)left);
    right = (int16_t)device_level((uint16_t)right);
    if (cfg.swap) {
        t = left;
        left = right;
        right = t;
    }
    snd.wave_volume = MAKELONG(left, right);
    set = set_wave_volume(snd.wave_volume);
    return set ? 0 : 1;
}

/* 9:10ae: whether sound a (on screen: r) may play and becomes the
 * followed one: -1 not played, 1 followed, 0 played unfollowed. */
static int16_t take_over(int16_t a, int16_t r, int16_t loops)
{
    if (!r && snd.ch[snd.followed_ch].on_screen)
        return -1;
    if (r && !snd.ch[snd.followed_ch].on_screen && !snd.on_screen_count) {
        if (a == 1 && snd.busy)
            return -1;
        stop_all();
        return 1;
    }
    if (snd.followed == 1) {
        stop_all();
        return 1;
    }
    if (a == 1)
        return 0;
    if (sound_flags[a] & F_VOICE || (loops && snd.channels == 1) || a >= snd.followed)
        return 1;
    if (sound_flags[snd.followed] & F_VOICE)
        return 0;
    if (a == 0x1a)
        return snd.followed < 0x20;
    return a == 0x1c;
}

/* 9:11f4: the channel for sound a: the one that started it under 80 ms
 * ago (not for 8, 0x14, 0x27, 0x2b), a free one, or the one playing
 * longest that is not followed nor a voice on screen. */
static int16_t pick_channel(int16_t a)
{
    DWORD oldest;
    int16_t i, pick = 0;

    if (a != 0x2b && a != 0x27 && a != 8 && a != 0x14)
        for (i = 0; i < snd.channels; i++)
            if (snd.ch[i].id == a && snd.ch[i].start + 80 > GetCurrentTime())
                return i;
    for (i = 0; i < snd.channels; i++)
        if (!snd.ch[i].id)
            return i;
    oldest = GetCurrentTime() + 500;
    for (i = 0; i < snd.channels; i++)
        if (snd.ch[i].start < oldest && i != snd.followed_ch && (!snd.ch[i].voice || !snd.ch[i].on_screen)) {
            pick = i;
            oldest = snd.ch[i].start;
        }
    return pick;
}

/* 9:11f4: plays sound a (file path when named) looping loops more times
 * and records it; 1 when it started. */
static int start_sound(int16_t a, const char *path, int16_t loops, int16_t take, int16_t r)
{
    int16_t c = pick_channel(a);
    MIXPLAYPARAMS mp;
    Channel *ch = &snd.ch[c];
    int ok;

    if (snd.channels == 1) {
        ok = path ? sndPlaySound(path, SND_ASYNC | SND_NODEFAULT)
                  : sndPlaySound(snd.sound[a].riff,
                                 SND_ASYNC | SND_NODEFAULT | SND_MEMORY | (loops ? SND_LOOP : 0));
    } else {
        if (!snd.session || !snd.active)
            return 0;
        mp.wave = snd.sound[a].wave;
        if (path) {
            if (snd.file_wave[c])       /* the DLL lost it: the wave it replaces */
                WaveMixFreeWave(snd.session, snd.file_wave[c]);
            mp.wave = snd.file_wave[c] = WaveMixOpenWave(snd.session, path);
        }
        mp.session = snd.session;
        mp.channel = c;
        mp.notify = snd.notify;
        mp.loops = (uint16_t)loops;
        ok = WaveMixPlay(&mp) == 0;
    }
    if (!ok)
        return 0;
    if (!ch->id)
        snd.busy++;
    if (r && !ch->on_screen)
        snd.on_screen_count++;
    ch->id = a;
    ch->start = GetCurrentTime();
    ch->on_screen = r;
    ch->voice = sound_flags[a] & F_VOICE;
    if (take) {
        snd.followed = a;
        snd.followed_ch = c;
    }
    return 1;
}

/* Ordinal 9 (9:0c42): plays sound a coming from p (screen position;
 * FAR_X: everywhere; PRELOAD_X: load only), on screen when r, at game
 * time now; q's high word and low word and view as ordinal 8 takes them.
 * a = -1 plays the voice file <SndPath><name>.WAV; ids from 0x64 on are
 * commands or stand for others.  Unless the sound loops, nothing starts
 * before the quiet time of the last one.  Returns 1 when the sound is
 * followed (and for the stop commands 0x69, 0x6e). */
int16_t ispace_sound_play(int16_t a, POINT p, int16_t r, int32_t q, int32_t view, DWORD now,
                          LPCSTR name)
{
    int16_t asked = a, loops = 0, k = 0, take;
    char path[0x80];
    const char *file = NULL;

    if (!cfg.system || (!cfg.voice_on && a == -1))
        return 0;
    switch (a) {
    case -1:
        a = 0x11;
        ispace_sound_path(path, sizeof path);
        SDL_strlcat(path, name, sizeof path);
        SDL_strlcat(path, ".WAV", sizeof path);
        file = path;
        break;
    case 0x0c: a = 0x0b; break;
    case 0x26:
        if (!cfg.voice_on)
            a = 0x23;
        break;
    case 0x64: return 0;
    case 0x65: a = (int16_t)(dll_rand() % 3 + 0x30); break;
    case 0x66:                  /* one of three cheers, not the last one */
        k = (int16_t)(dll_rand() % 3);
        if (k == snd.last_cheer && ++k > 2)
            k = 0;
        a = (int16_t)(0x47 + k);
        break;
    case 0x67:                  /* two sounds in turn */
        k = !snd.last_alt;
        a = k ? 0x49 : 0x2e;
        break;
    case 0x68: loops = 0x14; a = 0x14; break;
    case 0x69:                  /* follow nothing (one channel: stop) */
        if (snd.channels > 1) {
            snd.followed = 0;
            snd.followed_ch = NO_CHANNEL;
        } else
            stop_all();
        snd.quiet_until = 0;
        return 1;
    case 0x6e:                  /* stop everything */
        stop_all();
        snd.quiet_until = 0;
        return 1;
    case 0x6f: loops = 0x14; a = 0x17; break;
    case 0x70: loops = 8; a = 0x4a; break;
    case 0x75: loops = 7; a = 0x46; break;
    default: break;
    }
    if (a < 0 || a >= SOUNDS)   /* the DLL read past its tables */
        return 0;
    if (!loops && (!snd.fx_volume || now < snd.quiet_until))
        return 0;
    if (!file) {
        if (!loaded(a))
            load_wave(a, 1);
        if (!loaded(a) || p.x == PRELOAD_X)
            return 0;
    }
    take = take_over(a, r, loops);
    if (take == -1)
        return 0;
    if (take)
        ispace_sound_follow(p, HI16(q), LO16(q), view);
    snd.quiet_until = now;
    if (r && a >= 0x26 && a < 0x26 + (int16_t)SDL_arraysize(quiet_ms))
        snd.quiet_until += (DWORD)quiet_ms[a - 0x26];
    if (!start_sound(a, file, loops, take, r))
        return 0;
    if (asked == 0x66)
        snd.last_cheer = k;
    else if (asked == 0x67)
        snd.last_alt = k;
    if (take)
        ispace_sound_follow(p, HI16(q), LO16(q), view);
    if (!r)
        snd.quiet_until = now;
    return take ? 1 : 0;
}

/* 9:298c: the dialogs' sound n, from everywhere. */
void ispace_sound_effect(int16_t n)
{
    POINT far_away = {FAR_X, FAR_X};

    ispace_sound_play(n, far_away, 1, 0, MAKELONG(FAR_X, FAR_X), GetCurrentTime(), "");
}

/* The DLL's music settings the music module reads. */
int16_t ispace_sound_system(void)
{
    return cfg.system;
}

int16_t ispace_sound_music_volume(void)
{
    return snd.music_volume;
}
