/* MCI's MIDI sequencer and the MIDI output's volume, as ISPACE.DLL plays
 * its music: one file open at a time, times in milliseconds, played up
 * to a time with MM_MCINOTIFY when it gets there.  The playing itself is
 * the platform's (platform_music_*). */
#include "user.h"
#include "platform/platform.h"

#define DEVICE 1                /* the one sequencer's device id */

static struct {
    int open;
    DWORD pos;                  /* where play starts (PLATFORM_MUSIC_HERE: where it is) */
    HWND notify;                /* told when play reaches its end */
    DWORD volume;
} seq = {0, 0, 0, 0xffffffff};

/* MCI_OPEN of a sequencer with the file at dos_path: its device id, or
 * 0 (an MCI error).  It plays on the SoundFont INSPACE.INI [Port]
 * SoundFont= names (a host path), if any. */
UINT mci_open_sequencer(LPCSTR dos_path)
{
    char host[1024], soundfont[1024];
    int has_soundfont = port_setting("SoundFont", soundfont, sizeof soundfont) > 0;

    if (seq.open || !dos_to_host(dos_path, host, sizeof host) ||
        !platform_music_open(host, has_soundfont ? soundfont : NULL))
        return 0;
    seq.open = 1;
    seq.pos = 0;
    seq.notify = 0;
    return DEVICE;
}

void mci_close(UINT dev)
{
    if (dev != DEVICE || !seq.open)
        return;
    platform_music_close();
    seq.open = 0;
}

/* MCI_SEEK (MCI_TO); with notify, MM_MCINOTIFY follows. */
void mci_seek(UINT dev, DWORD to, HWND notify)
{
    if (dev != DEVICE || !seq.open)
        return;
    platform_music_pause();
    seq.pos = to;
    seq.notify = 0;
    if (notify)
        PostMessage(notify, MM_MCINOTIFY, MCI_NOTIFY_SUCCESSFUL, (LPARAM)dev);
}

/* MCI_PLAY (MCI_NOTIFY | MCI_TO): from where it is to `to`; 0 when it
 * plays. */
UINT mci_play(UINT dev, DWORD to, HWND notify)
{
    if (dev != DEVICE || !seq.open)
        return MMSYSERR_ERROR;
    platform_music_play(seq.pos, to);
    seq.pos = PLATFORM_MUSIC_HERE;
    seq.notify = notify;
    return 0;
}

/* MCI_PAUSE: play stops where it is, and goes on from there. */
void mci_pause(UINT dev)
{
    if (dev != DEVICE || !seq.open)
        return;
    platform_music_pause();
    seq.notify = 0;
}

/* Posts MM_MCINOTIFY when play has reached its end (with the input
 * events). */
void mci_notify(void)
{
    if (seq.open && seq.notify && platform_music_ended()) {
        PostMessage(seq.notify, MM_MCINOTIFY, MCI_NOTIFY_SUCCESSFUL, (LPARAM)DEVICE);
        seq.notify = 0;
    }
}

UINT midiOutGetVolume(UINT dev, DWORD *vol)
{
    (void)dev;
    *vol = seq.volume;
    return 0;
}

UINT midiOutSetVolume(UINT dev, DWORD vol)
{
    (void)dev;
    seq.volume = vol;
    platform_music_volume(LOWORD(vol), HIWORD(vol));
    return 0;
}
