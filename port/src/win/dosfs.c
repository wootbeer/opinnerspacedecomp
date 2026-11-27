/* DOS drives and file names over the host's folders (port/README.md,
 * "Drives and file names").
 *
 * Drives: each of C: to Z: may be a host folder: the platform's folder
 * roots (Windows: its drives, by letter; elsewhere the user's home as C:),
 * replaced by INSPACE.INI [Port] DriveC=<folder> (any letter).  C:\SPACE
 * and C:\WINDOWS (both the data folder: nothing goes to the user's
 * settings folders) are mounted on C: whatever C: is.
 *
 * Names: the game sees 8.3 names in upper case, as under DOS.  A host
 * name that is a valid 8.3 name when upper-cased is shown so; any other
 * gets an alias as Windows 95 gave 16-bit programs (PROGRA~1, NOTES~1.TXT),
 * numbered in the order of the host names. */
#include <SDL3/SDL_stdinc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "winrt.h"
#include "platform/platform.h"

#define PATH_MAX_ 1024

typedef struct {
    char host[256];
    DosEntry e;
} HostEntry;

typedef struct {
    HostEntry *v;
    int n, cap;
} HostDir;

static const struct {
    const char *name;
    const char *(*folder)(void);
} mounts[] = {
    {"SPACE", platform_data_dir},
    {"WINDOWS", platform_data_dir},
};
#define N_MOUNTS ((int)(sizeof mounts / sizeof mounts[0]))

/* Drives. */
static char roots[26][260];

static void load_roots(void)
{
    static int loaded;
    char found[24][260], key[8], buf[260];
    int n, i, next = 'C';

    if (loaded)
        return;
    loaded = 1;
    n = platform_folder_roots(found, 24);
    for (i = 0; i < n; i++) {
        int letter = found[i][1] == ':' ? toupper((unsigned char)found[i][0]) : 0;
        if (letter < 'C' || letter > 'Z') {
            while (next <= 'Z' && roots[next - 'A'][0])
                next++;
            letter = next;
        }
        if (letter <= 'Z')
            SDL_strlcpy(roots[letter - 'A'], found[i], sizeof roots[0]);
    }
    for (i = 'C'; i <= 'Z'; i++) {
        snprintf(key, sizeof key, "Drive%c", i);
        if (GetPrivateProfileString("Port", key, "", buf, sizeof buf, "INSPACE.INI") > 0)
            SDL_strlcpy(roots[i - 'A'], buf, sizeof roots[0]);
    }
}

int dos_drive_exists(int letter)
{
    letter = toupper(letter);
    if (letter == 'C')
        return 1;               /* the mounts are on C: */
    load_roots();
    return letter > 'C' && letter <= 'Z' && roots[letter - 'A'][0];
}

/* 8.3 names. */
static int char_83(unsigned char c)
{
    return c > ' ' && c < 0x7f && !strchr("\"*+,./:;<=>?[\\]|", c);
}

static int is_83(const char *s)
{
    const char *dot = strchr(s, '.');
    size_t base = dot ? (size_t)(dot - s) : strlen(s), i;

    if (base < 1 || base > 8 || (dot && (strlen(dot + 1) > 3 || strchr(dot + 1, '.'))))
        return 0;
    for (i = 0; s[i]; i++)
        if (s[i] != '.' && !char_83((unsigned char)s[i]))
            return 0;
    return !dot || dot[1];
}

/* Upper-cased 8.3 characters of s[0..n): spaces and dots left out,
 * others not allowed in 8.3 names as '_', at most max. */
static size_t squeeze(const char *s, size_t n, char *out, size_t max)
{
    size_t i, k = 0;

    for (i = 0; i < n && k < max; i++) {
        unsigned char c = (unsigned char)s[i];
        if (c == ' ' || c == '.')
            continue;
        out[k++] = char_83(c) ? (char)toupper(c) : '_';
    }
    out[k] = 0;
    return k;
}

static int name_taken(const HostDir *d, int upto, const char *name)
{
    int i;

    for (i = 0; i < upto; i++)
        if (d->v[i].e.name[0] && !SDL_strcasecmp(d->v[i].e.name, name))
            return 1;
    return 0;
}

static void make_alias(HostDir *d, int k)
{
    const char *s = d->v[k].host, *dot;
    char base[9], ext[4], tail[8], alias[13];
    size_t nb;
    int num;

    while (*s == '.')
        s++;
    dot = strrchr(s, '.');
    nb = squeeze(s, dot ? (size_t)(dot - s) : strlen(s), base, 8);
    squeeze(dot ? dot + 1 : "", dot ? strlen(dot + 1) : 0, ext, 3);
    for (num = 1; num < 1000000; num++) {
        size_t nt = (size_t)snprintf(tail, sizeof tail, "~%d", num);
        size_t keep = nb + nt > 8 ? 8 - nt : nb;
        snprintf(alias, sizeof alias, "%.*s%s%s%s", (int)keep, base, tail, ext[0] ? "." : "", ext);
        if (!name_taken(d, d->n, alias))
            break;
    }
    SDL_strlcpy(d->v[k].e.name, alias, sizeof d->v[k].e.name);
}

static int by_host_name(const void *a, const void *b)
{
    return strcmp(((const HostEntry *)a)->host, ((const HostEntry *)b)->host);
}

/* Host folder listing. */
static void add_host(const PlatformDirEntry *pe, void *user)
{
    HostDir *d = user;
    HostEntry *h;

    if (!strcmp(pe->name, ".") || !strcmp(pe->name, "..") || strlen(pe->name) >= sizeof h->host)
        return;
    if (d->n == d->cap) {
        int cap = d->cap ? d->cap * 2 : 64;
        HostEntry *v = realloc(d->v, (size_t)cap * sizeof *v);
        if (!v)
            return;
        d->v = v;
        d->cap = cap;
    }
    h = &d->v[d->n++];
    memset(h, 0, sizeof *h);
    SDL_strlcpy(h->host, pe->name, sizeof h->host);
    h->e.attrib = (uint8_t)((pe->is_dir ? _A_SUBDIR : 0) | (pe->hidden ? _A_HIDDEN : 0));
    h->e.size = pe->size;
}

/* The entries of host folder path with their 8.3 names; 0 if it cannot
 * be read. */
static int read_host_dir(const char *path, HostDir *d)
{
    int i;

    memset(d, 0, sizeof *d);
    if (!platform_list_dir(path, "*", add_host, d) && !d->n) {
        free(d->v);
        return 0;
    }
    qsort(d->v, (size_t)d->n, sizeof *d->v, by_host_name);
    for (i = 0; i < d->n; i++) {
        char up[13];
        size_t k;
        if (!is_83(d->v[i].host))
            continue;
        for (k = 0; d->v[i].host[k]; k++)
            up[k] = (char)toupper((unsigned char)d->v[i].host[k]);
        up[k] = 0;
        if (!name_taken(d, i, up))
            SDL_strlcpy(d->v[i].e.name, up, sizeof d->v[i].e.name);
    }
    for (i = 0; i < d->n; i++)
        if (!d->v[i].e.name[0])
            make_alias(d, i);
    return 1;
}

static const HostEntry *find_name(const HostDir *d, const char *name)
{
    int i;

    for (i = 0; i < d->n; i++)
        if (!SDL_strcasecmp(d->v[i].e.name, name))
            return &d->v[i];
    for (i = 0; i < d->n; i++)
        if (!SDL_strcasecmp(d->v[i].host, name))
            return &d->v[i];
    return NULL;
}

/* Paths. */
static void join(char *path, size_t size, const char *name)
{
    size_t n = strlen(path);

    if (n && path[n - 1] != '/' && path[n - 1] != '\\')
        SDL_strlcat(path, "/", size);
    SDL_strlcat(path, name, size);
}

/* Splits an absolute or relative DOS path into the drive letter and its
 * components from the root ("." and ".." applied).  Relative paths are
 * in the current directory, C:\SPACE. */
static int split(const char *dos, char comp[][256], int max, int *drive)
{
    char full[PATH_MAX_];
    int n = 0;
    char *p, *save = NULL;

    if (dos[0] && dos[1] == ':')
        snprintf(full, sizeof full, "%s", dos);
    else if (dos[0] == '\\')
        snprintf(full, sizeof full, "C:%s", dos);
    else
        snprintf(full, sizeof full, "%s%s", GAME_DIR, dos);
    *drive = toupper((unsigned char)full[0]);
    for (p = SDL_strtok_r(full + 2, "\\/", &save); p; p = SDL_strtok_r(NULL, "\\/", &save)) {
        if (!strcmp(p, "."))
            continue;
        if (!strcmp(p, "..")) {
            if (n)
                n--;
            continue;
        }
        if (n == max)
            return -1;
        SDL_strlcpy(comp[n++], p, 256);
    }
    return n;
}

/* The host folder a drive's root or mount starts at; *used is the number
 * of components the mount takes. */
static const char *base_of(int drive, char comp[][256], int n, int *used)
{
    int i;

    *used = 0;
    if (drive == 'C' && n > 0)
        for (i = 0; i < N_MOUNTS; i++)
            if (!SDL_strcasecmp(comp[0], mounts[i].name)) {
                *used = 1;
                return mounts[i].folder();
            }
    if (drive < 'C' || drive > 'Z')
        return NULL;
    load_roots();
    return roots[drive - 'A'][0] ? roots[drive - 'A'] : NULL;
}

int dos_to_host(const char *dos, char *out, size_t size)
{
    char comp[32][256];
    int n, used, i, exists = 1, drive;
    const char *base;

    n = split(dos, comp, 32, &drive);
    if (n < 0 || !(base = base_of(drive, comp, n, &used)))
        return 0;
    SDL_strlcpy(out, base, size);
    for (i = used; i < n; i++) {
        HostDir d;
        const HostEntry *h = NULL;
        if (exists && read_host_dir(out, &d)) {
            h = find_name(&d, comp[i]);
            join(out, size, h ? h->host : comp[i]);
            free(d.v);
        } else {
            join(out, size, comp[i]);
        }
        exists = h != NULL;
    }
    return 1;
}

int dos_list(const char *dos_dir, DosEntry **out)
{
    char host[PATH_MAX_], comp[32][256];
    HostDir d;
    int n, drive, used, i, k;
    DosEntry *v;

    *out = NULL;
    n = split(dos_dir, comp, 32, &drive);
    if (n < 0 || !base_of(drive, comp, n, &used) || !dos_to_host(dos_dir, host, sizeof host) ||
        !read_host_dir(host, &d))
        return -1;
    v = malloc((size_t)(d.n + N_MOUNTS + 1) * sizeof *v);
    if (!v) {
        free(d.v);
        return -1;
    }
    for (i = k = 0; i < d.n; i++)
        v[k++] = d.v[i].e;
    free(d.v);
    if (drive == 'C' && n == 0) {
        for (i = 0; i < N_MOUNTS; i++) {
            int j;
            for (j = 0; j < k && SDL_strcasecmp(v[j].name, mounts[i].name); j++)
                ;
            if (j == k)
                k++;
            memset(&v[j], 0, sizeof v[j]);
            SDL_strlcpy(v[j].name, mounts[i].name, sizeof v[j].name);
            v[j].attrib = _A_SUBDIR;
        }
    }
    *out = v;
    return k;
}

/* DOS wildcards: name and pattern are compared as the 11 characters of
 * their 8.3 fields; '*' fills the rest of its field with '?'. */
static void fields(const char *s, char out[11], int pattern)
{
    const char *dot = strchr(s, '.');
    int f, i;

    memset(out, ' ', 11);
    for (f = 0; f < 2; f++) {
        const char *p = f ? (dot ? dot + 1 : "") : s;
        int width = f ? 3 : 8;
        for (i = 0; i < width && *p && *p != '.'; p++) {
            if (pattern && *p == '*') {
                while (i < width)
                    out[f * 8 + i++] = '?';
                break;
            }
            out[f * 8 + i++] = (char)toupper((unsigned char)*p);
        }
    }
}

int dos_match(const char *name, const char *pattern)
{
    char a[11], b[11];
    int i;

    fields(name, a, 0);
    fields(pattern, b, 1);
    for (i = 0; i < 11; i++)
        if (b[i] != '?' && b[i] != a[i])
            return 0;
    return 1;
}
