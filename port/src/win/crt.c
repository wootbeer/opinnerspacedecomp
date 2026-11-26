/* The parts of the 1994 C runtime (Microsoft C 8) and of the KERNEL/USER
 * string calls whose behaviour the game depends on exactly. */
#include <SDL3/SDL_filesystem.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "winrt.h"

static uint32_t rand_seed = 1;

void msc_srand(uint16_t seed)
{
    rand_seed = seed;
}

int16_t msc_rand(void)
{
    rand_seed = rand_seed * 214013u + 2531011u;
    return (int16_t)(rand_seed >> 16 & 0x7fff);
}

LPSTR lstrcpy(LPSTR d, LPCSTR s)
{
    memmove(d, s, strlen(s) + 1);
    return d;
}

LPSTR lstrcat(LPSTR d, LPCSTR s)
{
    memmove(d + strlen(d), s, strlen(s) + 1);
    return d;
}

int16_t lstrlen(LPCSTR s)
{
    return s ? (int16_t)strlen(s) : 0;
}

/* Windows compares by its language collation: case-insensitive first,
 * lower case before upper case when the words are otherwise equal. */
int16_t lstrcmp(LPCSTR a, LPCSTR b)
{
    const unsigned char *p = (const unsigned char *)a, *q = (const unsigned char *)b;
    int tie = 0;

    for (; *p || *q; p++, q++) {
        int x = tolower(*p), y = tolower(*q);
        if (x != y)
            return x < y ? -1 : 1;
        if (!tie && *p != *q)
            tie = islower(*p) ? -1 : 1;
    }
    return (int16_t)tie;
}

/* wsprintf: %c %d %i %u %x %X %s with flags, width, precision and the 'l'
 * size; without 'l' the value is a 16-bit int as in 1994. */
int16_t wsprintf(LPSTR out, LPCSTR fmt, ...)
{
    va_list ap;
    char *o = out;

    va_start(ap, fmt);
    while (*fmt) {
        char spec[16], buf[64];
        int n = 0, is_long = 0;

        if (*fmt != '%') {
            *o++ = *fmt++;
            continue;
        }
        spec[n++] = *fmt++;
        while (*fmt && strchr("-#0 +", *fmt) && n < 8)
            spec[n++] = *fmt++;
        while (isdigit((unsigned char)*fmt) && n < 11)
            spec[n++] = *fmt++;
        if (*fmt == '.') {
            spec[n++] = *fmt++;
            while (isdigit((unsigned char)*fmt) && n < 14)
                spec[n++] = *fmt++;
        }
        if (*fmt == 'l') {
            is_long = 1;
            fmt++;
        }
        if (!*fmt)
            break;
        spec[n++] = *fmt == 'i' ? 'd' : *fmt;
        spec[n] = 0;
        switch (*fmt++) {
        case 'd':
        case 'i':
            if (is_long)
                snprintf(buf, sizeof buf, spec, (int)(int32_t)va_arg(ap, int));
            else
                snprintf(buf, sizeof buf, spec, (int)(int16_t)va_arg(ap, int));
            break;
        case 'u':
        case 'x':
        case 'X':
            if (is_long)
                snprintf(buf, sizeof buf, spec, (unsigned)(uint32_t)va_arg(ap, int));
            else
                snprintf(buf, sizeof buf, spec, (unsigned)(uint16_t)va_arg(ap, int));
            break;
        case 'c':
            snprintf(buf, sizeof buf, spec, (int)(char)va_arg(ap, int));
            break;
        case 's': {
            const char *s = va_arg(ap, const char *);
            int len = snprintf(NULL, 0, spec, s ? s : "");
            sprintf(o, spec, s ? s : "");
            o += len;
            continue;
        }
        default:
            snprintf(buf, sizeof buf, "%s", spec + n - 1);
            break;
        }
        strcpy(o, buf);
        o += strlen(buf);
    }
    va_end(ap);
    *o = 0;
    return (int16_t)(o - out);
}

/* Directory search: _dos_findfirst / _dos_findnext.  DOS keeps a
 * search's state in find_t.reserved; here it names a snapshot of the
 * matches (slot, generation, next entry).  The oldest snapshot is reused
 * by a new search, and a search whose snapshot was reused ends. */
#define MAX_FIND 64

typedef struct {
    uint32_t gen;
    int count;
    DosEntry *e;
} Search;
static Search searches[MAX_FIND];
static uint32_t find_gen;

static void put32(char *p, uint32_t v)
{
    p[0] = (char)v;
    p[1] = (char)(v >> 8);
    p[2] = (char)(v >> 16);
    p[3] = (char)(v >> 24);
}

static uint32_t get32(const char *p)
{
    const unsigned char *u = (const unsigned char *)p;

    return u[0] | u[1] << 8 | (uint32_t)u[2] << 16 | (uint32_t)u[3] << 24;
}

static uint16_t find_step(struct _find_t *ft)
{
    unsigned k = (unsigned char)ft->reserved[0];
    uint16_t next = (uint16_t)((unsigned char)ft->reserved[5] | (unsigned char)ft->reserved[6] << 8);
    Search *s;

    if (k >= MAX_FIND || searches[k].gen != get32(ft->reserved + 1) || next >= searches[k].count)
        return 18;
    s = &searches[k];
    strcpy(ft->name, s->e[next].name);
    ft->attrib = (char)s->e[next].attrib;
    ft->size = (int32_t)s->e[next].size;
    ft->wr_time = ft->wr_date = 0;
    next++;
    ft->reserved[5] = (char)next;
    ft->reserved[6] = (char)(next >> 8);
    return 0;
}

/* Normal files always match; hidden, system files and directories only
 * when attr asks for them. */
uint16_t _dos_findfirst(const char *path, uint16_t attr, struct _find_t *ft)
{
    char dir[260];
    const char *slash = strrchr(path, '\\');
    DosEntry *e;
    Search *s;
    int n, i, k, oldest = 0;

    if (attr & _A_VOLID || !slash)
        return 2;
    snprintf(dir, sizeof dir, "%.*s", (int)(slash - path + 1), path);
    n = dos_list(dir, &e);
    if (n < 0)
        return 3;
    for (k = 1; k < MAX_FIND; k++)
        if (searches[k].gen < searches[oldest].gen)
            oldest = k;
    s = &searches[oldest];
    free(s->e);
    s->e = e;
    s->gen = ++find_gen;
    for (i = s->count = 0; i < n; i++)
        if (!(e[i].attrib & (_A_HIDDEN | _A_SYSTEM | _A_SUBDIR) & ~attr) && dos_match(e[i].name, slash + 1))
            e[s->count++] = e[i];
    ft->reserved[0] = (char)oldest;
    put32(ft->reserved + 1, s->gen);
    ft->reserved[5] = ft->reserved[6] = 0;
    return find_step(ft) ? 2 : 0;
}

uint16_t _dos_findnext(struct _find_t *ft)
{
    return find_step(ft);
}

/* Drives: C: and the others dosfs.c maps to host folders. */
static int16_t current_drive = 3;

int16_t _getdrive(void)
{
    return current_drive;
}

int16_t _chdrive(int16_t drive)
{
    if (drive < 1 || drive > 26 || !dos_drive_exists('A' + drive - 1))
        return -1;
    current_drive = drive;
    return 0;
}

int16_t stat(const char *path, struct stat *st)
{
    char host[1024];
    SDL_PathInfo info;

    if (!dos_to_host(path, host, sizeof host) || !SDL_GetPathInfo(host, &info))
        return -1;
    memset(st, 0, sizeof *st);
    st->st_mode = info.type == SDL_PATHTYPE_DIRECTORY ? 0x4000 : 0x8000;
    st->st_size = (_off_t)info.size;
    st->st_mtime = (dos_time_t)(info.modify_time / 1000000000);
    st->st_atime = (dos_time_t)(info.access_time / 1000000000);
    st->st_ctime = (dos_time_t)(info.create_time / 1000000000);
    return 0;
}

int16_t utime(const char *path, struct utimbuf *t)
{
    (void)path;
    (void)t;
    STUB();
    return 0;
}
