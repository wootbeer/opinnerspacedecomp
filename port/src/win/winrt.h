/* Shared declarations of the native Windows 3.1 calls the game makes
 * (port/src/win/).  Each module implements one area, only as far as this
 * game uses it.  Include it after the system headers: the game's headers
 * rename a few runtime names (stat, rand, ...). */
#ifndef WINRT_H
#define WINRT_H

#include "game.h"

/* Constants the game itself does not name. */
#define WM_CHAR 0x0102
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_LBUTTONUP 0x0202
#define WM_RBUTTONUP 0x0205
#define MK_LBUTTON 0x0001
#define MK_RBUTTON 0x0002
#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define IDNO 7
#define DSTINVERT 0x00550009L

/* Calls not implemented yet log their name once. */
void win_stub(const char *name);
#define STUB() win_stub(__func__)

/* Handles: one table for every kind of object, 16-bit values. */
enum {
    H_FREE, H_MEM, H_MODULE, H_RSRC, H_WND, H_DC, H_BITMAP, H_PALETTE,
    H_BRUSH, H_PEN, H_FONT, H_RGN, H_MENU, H_ACCEL, H_ICON, H_CURSOR
};
uint16_t handle_new(int type, void *obj);
void *handle_get(uint16_t h, int type);
int handle_type(uint16_t h);
void handle_free(uint16_t h);

/* DOS drives and 8.3 names over host folders (dosfs.c).  C:\SPACE is the
 * data folder, C:\WINDOWS the writable settings folder; other paths are
 * in the drives' folders.  dos_to_host gives 0 for a drive without one. */
#define GAME_DIR "C:\\SPACE\\"
#define WIN_DIR "C:\\WINDOWS"
#define _A_HIDDEN 0x02
typedef struct {
    char name[13];          /* 8.3, upper case */
    uint8_t attrib;         /* _A_SUBDIR, _A_HIDDEN */
    uint32_t size;
} DosEntry;
int dos_to_host(const char *dos, char *out, size_t size);
int dos_drive_exists(int letter);
/* The entries of a directory (malloc'd, to free), or -1. */
int dos_list(const char *dos_dir, DosEntry **out);
/* DOS wildcard match of an 8.3 name ("*.EXE", "*.*"). */
int dos_match(const char *name, const char *pattern);

/* Port settings (INSPACE.INI [Port]; profile.c): 1 when name=1; a
 * value and its length (0: not set). */
int port_option(const char *name);
int port_setting(const char *name, char *buf, int size);

/* Modules and resources (module.c).  A resource name or type is a
 * string or MAKEINTRESOURCE(n). */
#define IS_INTRESOURCE(s) ((uintptr_t)(s) <= 0xffff)
HINSTANCE module_exe(void);
int module_init(void);
const uint8_t *module_resource(HINSTANCE h, LPCSTR type, LPCSTR name, uint32_t *size);
int module_is(HINSTANCE h, const char *name);

/* ISPACE.DLL entry points by ordinal (ispace.c). */
FARPROC ispace_proc(int ordinal);

/* GDI (gdi.c): the screen is an 8-bit bitmap over the framebuffer. */
void gdi_init(void);
uint8_t gdi_color_index(HDC dc, COLORREF c);

/* GDI calls only ISPACE.DLL makes (the game's headers do not declare
 * them). */
#define PC_RESERVED 0x01
#define SIZEPALETTE 104
#define NUMRESERVED 106
#define DIB_RGB_COLORS 0
#define DIB_PAL_COLORS 1
#define CBM_INIT 0x04L
HPALETTE CreatePalette(const LOGPALETTE *lp);
void AnimatePalette(HPALETTE pal, UINT start, UINT n, const PALETTEENTRY *e);
UINT GetSystemPaletteEntries(HDC dc, UINT start, UINT n, PALETTEENTRY *e);
HBITMAP CreateDIBitmap(HDC dc, const BITMAPINFOHEADER *bih, DWORD init, const void *bits,
                       const void *bmi, UINT usage);

/* Runtime and KERNEL calls only ISPACE.DLL makes. */
int16_t _getdrive(void);            /* 1 = A: */
int16_t _chdrive(int16_t drive);    /* 0, or -1 when there is no such drive */
UINT SetErrorMode(UINT mode);
#define WF_CPU286 0x0002
#define WF_CPU386 0x0004
#define WF_CPU486 0x0008
#define WF_80x87 0x0400
DWORD GetWinFlags(void);
UINT GetSystemDirectory(LPSTR buf, UINT size);

/* MMSYSTEM: the wave device as ISPACE.DLL asks about it. */
#define WAVECAPS_SYNC 0x0010
typedef struct {
    WORD wMid, wPid;
    WORD vDriverVersion;
    char szPname[32];
    DWORD dwFormats;
    WORD wChannels;
    DWORD dwSupport;
} WAVEOUTCAPS;
#define WAVECAPS_VOLUME 0x0004
#define WAVECAPS_LRVOLUME 0x0008
UINT waveOutGetNumDevs(void);
UINT waveOutGetDevCaps(UINT dev, WAVEOUTCAPS *caps, UINT size);

/* The wave output (wavemix.c): WaveMix as ISPACE.DLL uses it,
 * sndPlaySound and the device volume.  wavemix_device opens the output
 * (0: no sound device); wavemix_notify posts the MM_WOM_DONE of waves
 * that have ended (called with the input events). */
#define MMSYSERR_ERROR 1
#define MMSYSERR_INVALPARAM 11
#define MM_WOM_DONE 0x3bd
#define SND_ASYNC 0x0001
#define SND_NODEFAULT 0x0002
#define SND_MEMORY 0x0004
#define SND_LOOP 0x0008
#define WMIX_ALL 0x0001
#define WMIX_OPENCOUNT 0x0002
typedef struct MixWave MixWave;
typedef struct {
    HANDLE session;
    int16_t channel;
    MixWave *wave;
    HWND notify;
    uint16_t loops;
} MIXPLAYPARAMS;
int wavemix_device(void);
void wavemix_notify(void);
HANDLE WaveMixConfigureInit(void);          /* a mono session */
UINT WaveMixOpenChannel(HANDLE session, int16_t count, DWORD flags);
UINT WaveMixActivate(HANDLE session, BOOL on);
MixWave *WaveMixOpenWave(HANDLE session, LPCSTR dos_path);
MixWave *WaveMixOpenWaveData(HANDLE session, const void *riff, DWORD size);
UINT WaveMixPlay(const MIXPLAYPARAMS *p);
UINT WaveMixFlushChannel(HANDLE session, int16_t ch, DWORD flags);
UINT WaveMixFreeWave(HANDLE session, MixWave *w);
UINT WaveMixCloseChannel(HANDLE session, int16_t ch, DWORD flags);
UINT WaveMixCloseSession(HANDLE session);
void WaveMixPump(void);
BOOL sndPlaySound(LPCSTR sound, UINT flags);
UINT waveOutGetVolume(UINT dev, DWORD *vol);
UINT waveOutSetVolume(UINT dev, DWORD vol);

/* MCI's MIDI sequencer, as ISPACE.DLL drives it, and the MIDI output's
 * volume (mci.c).  mci_notify posts MM_MCINOTIFY when play has reached
 * its end (called with the input events). */
#define MM_MCINOTIFY 0x3b9
#define MCI_NOTIFY_SUCCESSFUL 1
UINT mci_open_sequencer(LPCSTR dos_path);
void mci_close(UINT dev);
void mci_seek(UINT dev, DWORD to, HWND notify);
UINT mci_play(UINT dev, DWORD to, HWND notify);
void mci_pause(UINT dev);
void mci_notify(void);
UINT midiOutGetVolume(UINT dev, DWORD *vol);
UINT midiOutSetVolume(UINT dev, DWORD vol);

#include "win.h"

#endif
