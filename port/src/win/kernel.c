/* KERNEL: global memory, files, DOS paths, time and system queries. */
#include <SDL3/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "winrt.h"
#include "platform/platform.h"

/* Some records are larger natively than in 1994 (REC_70 holds far
 * function pointers, see NOTES-port.md), so every block gets slack.  A
 * block keeps its address when it is reallocated within its slack, as a
 * Win16 block keeps its selector: the game holds pointers to locked
 * blocks that ISPACE.DLL grows (ordinal 32's rectangles). */
#define MEM_SLACK(n) ((n) / 4 + 64)

typedef struct {
    void *p;
    DWORD size;
    DWORD cap;                  /* bytes allocated */
} Mem;

HGLOBAL GlobalAlloc(UINT flags, DWORD size)
{
    Mem *m = calloc(1, sizeof *m);
    HGLOBAL h;

    (void)flags;
    if (!m || !(m->p = calloc(1, size + MEM_SLACK(size)))) {
        free(m);
        return 0;
    }
    m->size = size;
    m->cap = size + MEM_SLACK(size);
    h = handle_new(H_MEM, m);
    if (!h) {
        free(m->p);
        free(m);
    }
    return h;
}

void *GlobalLock(HGLOBAL h)
{
    Mem *m = handle_get(h, H_MEM);

    return m ? m->p : NULL;
}

BOOL GlobalUnlock(HGLOBAL h)
{
    (void)h;
    return 0;
}

DWORD GlobalSize(HGLOBAL h)
{
    Mem *m = handle_get(h, H_MEM);

    return m ? m->size : 0;
}

HGLOBAL GlobalReAlloc(HGLOBAL h, DWORD size, UINT flags)
{
    Mem *m = handle_get(h, H_MEM);
    void *p;

    if (!m)
        return 0;
    if (size > m->cap) {
        p = realloc(m->p, size + MEM_SLACK(size));
        if (!p)
            return 0;
        m->p = p;
        m->cap = size + MEM_SLACK(size);
    }
    if (size > m->size && (flags & GMEM_ZEROINIT))
        memset((char *)m->p + m->size, 0, size - m->size);
    m->size = size;
    return h;
}

HGLOBAL GlobalFree(HGLOBAL h)
{
    Mem *m = handle_get(h, H_MEM);

    if (!m)
        return h;
    free(m->p);
    free(m);
    handle_free(h);
    return 0;
}

DWORD GlobalCompact(DWORD n)
{
    (void)n;
    return 0x7fffffff;
}

/* Files: DOS handles 5 and up. */
#define MAX_FILES 32
#define FILE_BASE 5
static FILE *files[MAX_FILES];

static FILE *file_of(HFILE h)
{
    int k = h - FILE_BASE;

    return k >= 0 && k < MAX_FILES ? files[k] : NULL;
}

HFILE OpenFile(LPCSTR path, OFSTRUCT *of, UINT mode)
{
    char host[1024];
    const char *how;
    FILE *fp;
    int k;

    memset(of, 0, sizeof *of);
    of->cBytes = sizeof *of;
    of->fFixedDisk = 1;
    snprintf(of->szPathName, sizeof of->szPathName, "%s", path);
    if (!dos_to_host(path, host, sizeof host)) {
        of->nErrCode = 3;
        return HFILE_ERROR;
    }
    if (mode & OF_DELETE)
        return remove(host) == 0 ? 1 : HFILE_ERROR;
    if (mode & OF_CREATE)
        how = "w+b";
    else if (mode & 3)        /* OF_WRITE or OF_READWRITE */
        how = "r+b";
    else
        how = "rb";
    fp = fopen(host, how);
    if (!fp) {
        of->nErrCode = 2;
        return HFILE_ERROR;
    }
    if (mode & OF_EXIST) {
        fclose(fp);
        return 1;
    }
    for (k = 0; k < MAX_FILES && files[k]; k++)
        ;
    if (k == MAX_FILES) {
        fclose(fp);
        of->nErrCode = 4;
        return HFILE_ERROR;
    }
    files[k] = fp;
    return (HFILE)(FILE_BASE + k);
}

UINT _lread(HFILE h, void *buf, UINT n)
{
    FILE *fp = file_of(h);

    return fp ? (UINT)fread(buf, 1, n, fp) : (UINT)-1;
}

UINT _lwrite(HFILE h, const void *buf, UINT n)
{
    FILE *fp = file_of(h);

    return fp ? (UINT)fwrite(buf, 1, n, fp) : (UINT)-1;
}

HFILE _lclose(HFILE h)
{
    FILE *fp = file_of(h);

    if (!fp)
        return HFILE_ERROR;
    fclose(fp);
    files[h - FILE_BASE] = NULL;
    return 0;
}

int32_t _filelength(int16_t h)
{
    FILE *fp = file_of(h);
    long pos, len;

    if (!fp)
        return -1;
    pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fseek(fp, pos, SEEK_SET);
    return (int32_t)len;
}

/* Time. */
DWORD GetCurrentTime(void)
{
    return platform_time_ms();
}

DWORD timeGetTime(void)
{
    return platform_time_ms();
}

UINT timeGetDevCaps(TIMECAPS *tc, UINT size)
{
    (void)size;
    tc->wPeriodMin = 1;
    tc->wPeriodMax = 0xffff;
    return 0;
}

/* System. */
UINT GetWindowsDirectory(LPSTR buf, UINT size)
{
    snprintf(buf, size, "%s", WIN_DIR);
    return (UINT)strlen(buf);
}

/* A 486 with a coprocessor in enhanced mode [inferred: the machines the
 * game was made for; the desk scene shows it]. */
DWORD GetWinFlags(void)
{
    return 0x0001 | WF_CPU486 | 0x0020 | WF_80x87;
}

UINT GetSystemDirectory(LPSTR buf, UINT size)
{
    snprintf(buf, size, "%s\\SYSTEM", WIN_DIR);
    return (UINT)strlen(buf);
}

/* One stereo wave device with left and right volume (wavemix.c), when
 * the platform has sound. */
UINT waveOutGetNumDevs(void)
{
    return wavemix_device() ? 1 : 0;
}

UINT waveOutGetDevCaps(UINT dev, WAVEOUTCAPS *caps, UINT size)
{
    (void)dev;
    (void)size;
    memset(caps, 0, sizeof *caps);
    caps->wChannels = 2;
    caps->dwSupport = WAVECAPS_VOLUME | WAVECAPS_LRVOLUME;
    return 0;
}

UINT SetErrorMode(UINT mode)
{
    static UINT current;
    UINT old = current;

    current = mode;
    return old;
}

DWORD GetVersion(void)
{
    return 0x05000a03;      /* Windows 3.10 on DOS 5.0 */
}

UINT GetFreeSystemResources(UINT what)
{
    (void)what;
    return 80;
}

int16_t GetInstanceData(HINSTANCE h, BYTE *buf, int16_t n)
{
    (void)h;
    (void)buf;
    (void)n;
    return 0;
}

BOOL SetMessageQueue(int16_t n)
{
    (void)n;
    return 1;
}

void OutputDebugString(LPCSTR s)
{
    if (SDL_getenv("INSPACE_DEBUG"))
        fputs(s, stderr);
}

UINT WinExec(LPCSTR cmd, UINT show)
{
    (void)cmd;
    (void)show;
    STUB();
    return 2;
}

void win_stub(const char *name)
{
    static const char *seen[512];
    static int n;
    int i;

    for (i = 0; i < n; i++)
        if (seen[i] == name)
            return;
    if (n < 512)
        seen[n++] = name;
    fprintf(stderr, "stub: %s\n", name);
}
