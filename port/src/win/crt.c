/* The parts of the 1994 C runtime (Microsoft C 8) and of the KERNEL/USER
 * string calls whose behaviour the game depends on exactly. */
#include <SDL3/SDL_filesystem.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "winrt.h"
#include "platform/platform.h"

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

/* Directory search: _dos_findfirst / _dos_findnext.  The match list is
 * kept here; find_t.reserved holds its slot. */
#define MAX_FIND 4
#define MAX_FOUND 1024

typedef struct {
    int used, count, next;
    struct {
        char name[13];
        char attrib;
        int32_t size;
    } e[MAX_FOUND];
} Search;
static Search searches[MAX_FIND];

typedef struct {
    Search *s;
    unsigned attr;
} FindCtx;

static void add_found(const PlatformDirEntry *e, void *user)
{
    FindCtx *c = user;
    Search *s = c->s;
    int i;

    if (s->count >= MAX_FOUND || (e->is_dir && !(c->attr & _A_SUBDIR)))
        return;
    if (!strcmp(e->name, ".") || !strcmp(e->name, ".."))
        return;
    for (i = 0; i < 12 && e->name[i]; i++)
        s->e[s->count].name[i] = (char)toupper((unsigned char)e->name[i]);
    s->e[s->count].name[i] = 0;
    s->e[s->count].attrib = e->is_dir ? _A_SUBDIR : 0;
    s->e[s->count].size = (int32_t)e->size;
    s->count++;
}

static uint16_t find_step(struct _find_t *ft)
{
    int k = (unsigned char)ft->reserved[0];
    Search *s;

    if (k >= MAX_FIND)
        return 18;
    s = &searches[k];
    if (!s->used || s->next >= s->count) {
        s->used = 0;
        return 18;
    }
    strcpy(ft->name, s->e[s->next].name);
    ft->attrib = s->e[s->next].attrib;
    ft->size = s->e[s->next].size;
    ft->wr_time = ft->wr_date = 0;
    s->next++;
    return 0;
}

uint16_t _dos_findfirst(const char *path, uint16_t attr, struct _find_t *ft)
{
    char dir[260], host[1024];
    const char *slash = strrchr(path, '\\');
    FindCtx c;
    int k;

    if (attr & _A_VOLID || !slash)
        return 2;
    for (k = 0; k < MAX_FIND && searches[k].used; k++)
        ;
    if (k == MAX_FIND)
        k = 0;
    snprintf(dir, sizeof dir, "%.*s", (int)(slash - path + 1), path);
    if (!dos_to_host(dir, host, sizeof host))
        return 3;
    c.s = &searches[k];
    c.attr = attr;
    c.s->used = 1;
    c.s->count = c.s->next = 0;
    platform_list_dir(host, slash + 1, add_found, &c);
    ft->reserved[0] = (char)k;
    if (find_step(ft))
        return 2;
    return 0;
}

uint16_t _dos_findnext(struct _find_t *ft)
{
    return find_step(ft);
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
    st->st_mtime = (time_t)(info.modify_time / 1000000000);
    st->st_atime = (time_t)(info.access_time / 1000000000);
    st->st_ctime = (time_t)(info.create_time / 1000000000);
    return 0;
}

int16_t utime(const char *path, struct utimbuf *t)
{
    (void)path;
    (void)t;
    STUB();
    return 0;
}
