/* Private profile (INI) files.  A bare file name (INSPACE.INI) lives in
 * the Windows folder, which is the platform's writable settings folder. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "winrt.h"
#include "platform/platform.h"

#define MAX_LINES 1024
#define LINE_LEN 256

typedef struct {
    int n;
    char line[MAX_LINES][LINE_LEN];
} Ini;

static void ini_path(LPCSTR file, char *out, size_t size)
{
    char dos[300];

    if (strchr(file, '\\'))
        snprintf(dos, sizeof dos, "%s", file);
    else
        snprintf(dos, sizeof dos, "%s\\%s", WIN_DIR, file);
    if (!dos_to_host(dos, out, size))
        snprintf(out, size, "%s%s", platform_pref_dir(), file);
}

static Ini *ini_load(LPCSTR file)
{
    char path[1024];
    Ini *ini = calloc(1, sizeof *ini);
    FILE *fp;

    if (!ini)
        return NULL;
    ini_path(file, path, sizeof path);
    fp = fopen(path, "r");
    if (!fp)
        return ini;
    while (ini->n < MAX_LINES && fgets(ini->line[ini->n], LINE_LEN, fp)) {
        char *s = ini->line[ini->n];
        size_t len = strlen(s);
        while (len && (s[len - 1] == '\n' || s[len - 1] == '\r'))
            s[--len] = 0;
        ini->n++;
    }
    fclose(fp);
    return ini;
}

static void ini_save(const Ini *ini, LPCSTR file)
{
    char path[1024];
    FILE *fp;
    int i;

    ini_path(file, path, sizeof path);
    fp = fopen(path, "w");
    if (!fp)
        return;
    for (i = 0; i < ini->n; i++)
        fprintf(fp, "%s\r\n", ini->line[i]);
    fclose(fp);
}

static int same(const char *a, size_t n, const char *b)
{
    size_t i;

    for (i = 0; i < n; i++)
        if (!b[i] || toupper((unsigned char)a[i]) != toupper((unsigned char)b[i]))
            return 0;
    return b[n] == 0;
}

static const char *skip_space(const char *s)
{
    while (*s == ' ' || *s == '\t')
        s++;
    return s;
}

/* Line of [section], or -1. */
static int find_section(const Ini *ini, LPCSTR section)
{
    int i;

    for (i = 0; i < ini->n; i++) {
        const char *s = skip_space(ini->line[i]);
        const char *e = strchr(s, ']');
        if (*s == '[' && e && same(s + 1, (size_t)(e - s - 1), section))
            return i;
    }
    return -1;
}

/* Length of the key name on a line, or 0 when it is not a key line. */
static size_t key_len(const char *s)
{
    const char *eq = strchr(s, '=');
    size_t n;

    if (!eq || *s == ';' || *s == '[')
        return 0;
    n = (size_t)(eq - s);
    while (n && (s[n - 1] == ' ' || s[n - 1] == '\t'))
        n--;
    return n;
}

/* Line of key inside the section starting at sec, or -1. */
static int find_key(const Ini *ini, int sec, LPCSTR key, int *end)
{
    int i;

    for (i = sec + 1; i < ini->n; i++) {
        const char *s = skip_space(ini->line[i]);
        size_t n;
        if (*s == '[')
            break;
        n = key_len(s);
        if (n && same(s, n, key)) {
            *end = i;
            return i;
        }
    }
    *end = i;
    return -1;
}

int16_t GetPrivateProfileString(LPCSTR section, LPCSTR key, LPCSTR def, LPSTR buf, int16_t size,
                                LPCSTR file)
{
    Ini *ini = ini_load(file);
    const char *value = def ? def : "";
    int sec, k, end;
    size_t n;

    if (size <= 0) {
        free(ini);
        return 0;
    }
    sec = ini ? find_section(ini, section) : -1;
    if (sec >= 0 && !key) {
        int pos = 0;
        for (k = sec + 1; k < ini->n && *skip_space(ini->line[k]) != '['; k++) {
            const char *s = skip_space(ini->line[k]);
            size_t len = key_len(s);
            if (len && pos + (int)len + 2 < size) {
                memcpy(buf + pos, s, len);
                pos += (int)len;
                buf[pos++] = 0;
            }
        }
        buf[pos] = 0;
        free(ini);
        return (int16_t)pos;
    }
    if (sec >= 0 && (k = find_key(ini, sec, key, &end)) >= 0)
        value = skip_space(strchr(ini->line[k], '=') + 1);
    n = strlen(value);
    while (n && (value[n - 1] == ' ' || value[n - 1] == '\t'))
        n--;
    if (n > (size_t)size - 1)
        n = (size_t)size - 1;
    memmove(buf, value, n);
    buf[n] = 0;
    free(ini);
    return (int16_t)n;
}

UINT GetPrivateProfileInt(LPCSTR section, LPCSTR key, int16_t def, LPCSTR file)
{
    char buf[32];

    if (!GetPrivateProfileString(section, key, "", buf, sizeof buf, file))
        return (UINT)def;
    return (UINT)atoi(buf);
}

BOOL WritePrivateProfileString(LPCSTR section, LPCSTR key, LPCSTR value, LPCSTR file)
{
    Ini *ini = ini_load(file);
    int sec, k, end;

    if (!ini)
        return 0;
    sec = find_section(ini, section);
    if (sec < 0) {
        if (!key || !value || ini->n + 2 >= MAX_LINES) {
            free(ini);
            return 1;
        }
        sec = ini->n;
        snprintf(ini->line[ini->n++], LINE_LEN, "[%s]", section);
    }
    if (!key) {
        for (end = sec + 1; end < ini->n && *skip_space(ini->line[end]) != '['; end++)
            ;
        memmove(ini->line[sec], ini->line[end], (size_t)(ini->n - end) * LINE_LEN);
        ini->n -= end - sec;
    } else if ((k = find_key(ini, sec, key, &end)) >= 0) {
        if (value) {
            snprintf(ini->line[k], LINE_LEN, "%s=%s", key, value);
        } else {
            memmove(ini->line[k], ini->line[k + 1], (size_t)(ini->n - k - 1) * LINE_LEN);
            ini->n--;
        }
    } else if (value && ini->n < MAX_LINES) {
        while (end > sec + 1 && !*skip_space(ini->line[end - 1]))
            end--;
        memmove(ini->line[end + 1], ini->line[end], (size_t)(ini->n - end) * LINE_LEN);
        snprintf(ini->line[end], LINE_LEN, "%s=%s", key, value);
        ini->n++;
    }
    ini_save(ini, file);
    free(ini);
    return 1;
}

UINT GetProfileInt(LPCSTR section, LPCSTR key, int16_t def)
{
    return GetPrivateProfileInt(section, key, def, "WIN.INI");
}

int16_t GetProfileString(LPCSTR section, LPCSTR key, LPCSTR def, LPSTR buf, int16_t size)
{
    return GetPrivateProfileString(section, key, def, buf, size, "WIN.INI");
}
