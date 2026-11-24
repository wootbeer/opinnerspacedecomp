/* ISPACE.DLL ordinal 24 (10:48d2): the copy checks the game (10:885e,
 * 10:946a) and the New Game dialog (10:611c) make: the CD named by WIN.INI
 * CDDrive, the key resource of INSPACE.EXE, and the registered name kept
 * in it.  Modes 2, 10 and 21 are ported; the DLL has 22. */
#include <SDL3/SDL_stdinc.h>
#include <string.h>

#include "ispace.h"
#include "ne.h"

#define INI "INSPACE.INI"
#define APP "Inner Space"
#define KEY_TYPE 5500           /* INSPACE.EXE resource 5500/110: the key */
#define KEY_ID 110
#define NAME_TYPE 5000          /* 5000/143: the registered name, coded */
#define NAME_ID 143
#define NAME_SIZE 50

/* <LocalPath>\INSPACE.EXE (DS:2056).  An empty LocalPath gives
 * \INSPACE.EXE. */
static void exe_path(char *path, size_t size)
{
    size_t n;

    GetPrivateProfileString(APP, "LocalPath", "", path, 0x6d, INI);
    n = SDL_strlen(path);
    if (!n || path[n - 1] != '\\')
        SDL_strlcat(path, "\\", size);
    SDL_strlcat(path, "INSPACE.EXE", size);
}

/* 10:4666 (10:4696 reading): up to n bytes of resource type/id of the
 * NE file at path; 1 when found. */
static int16_t read_resource(const char *path, uint16_t type, uint16_t id, uint8_t *out, uint32_t n)
{
    char host[1024];
    const uint8_t *r;
    uint32_t size;
    NeFile f;

    if (!dos_to_host(path, host, sizeof host) || !ne_open(&f, host))
        return 0;
    r = ne_resource(&f, type, NULL, id, NULL, &size);
    if (r)
        memcpy(out, r, size < n ? size : n);
    ne_close(&f);
    return r != NULL;
}

/* 10:4440: the serial number of the disk the key names (int 21h 440Dh
 * 0866h through DPMI, 10:4568).  The port's drive C is a folder with no
 * media ID: 0, as when the call fails. */
static uint32_t disk_serial(uint16_t drive)
{
    (void)drive;
    return 0;
}

/* WIN.INI [windows] PDev less SYSTEM.INI [386Enh] vidsp. */
static int16_t pdev_less_vidsp(void)
{
    char path[0x6e];
    size_t n;

    GetWindowsDirectory(path, sizeof path);
    n = SDL_strlen(path);
    if (!n || path[n - 1] != '\\')
        SDL_strlcat(path, "\\", sizeof path);
    SDL_strlcat(path, "SYSTEM.INI", sizeof path);
    return (int16_t)(GetProfileInt("windows", "PDev", 0) - GetPrivateProfileInt("386Enh", "vidsp", 0, path));
}

/* 10:4f9c (mode 0): 0 when the key matches the disk; 1, 2, 3 or 1000
 * otherwise. */
static int16_t check_key(void)
{
    uint8_t key[10] = {0};
    char path[0x80];
    uint32_t stored, serial;
    int16_t diff;

    exe_path(path, sizeof path);
    read_resource(path, KEY_TYPE, KEY_ID, key, sizeof key);
    diff = pdev_less_vidsp();
    if (diff < 0)
        return 2;
    stored = key[0] | key[1] << 8 | (uint32_t)key[2] << 16 | (uint32_t)key[3] << 24;
    if (!stored)
        return 3;
    serial = disk_serial((uint16_t)(key[4] | key[5] << 8));
    if (serial)
        return serial == stored ? 0 : 1000;
    if (!diff)
        return 1;
    return diff == (int16_t)((uint16_t)stored % 0x28d + 0x28e) ? 0 : 1000;  /* 10:51b6 */
}

/* 10:4c68 (reading): the registered name into name (50 bytes), decoded
 * as 10:4dba does: each byte xor "*2-" in turn, negative ones 0.  1 when
 * the resource is there and the first three characters are not 0 (then
 * the name moves three bytes down). */
static int16_t read_name(char *name)
{
    static const char key[3] = {'*', '2', '-'};
    char path[0x80];
    int16_t r;
    int i;

    exe_path(path, sizeof path);
    r = read_resource(path, NAME_TYPE, NAME_ID, (uint8_t *)name, NAME_SIZE);
    for (i = 0; i < NAME_SIZE; i++)
        name[i] = (char)(name[i] >= 0 ? name[i] ^ key[i % 3] : 0);
    if (!name[0] || !name[1] || !name[2]) {
        memmove(name, name + 3, NAME_SIZE - 3);
        r = 0;
    }
    return r;
}

static void upcase_first(char *s)
{
    if (s[0] > 0x60 && s[0] < 0x7b)
        s[0] -= 0x20;
}

int16_t ispace_check(char *a, char *b, int16_t mode)
{
    upcase_first(b);
    upcase_first(a);
    switch (mode) {
    case 2:
        return check_key();
    case 10:
        return read_name(a);
    case 21:
        return 1;   /* 10:49bf: a CD in drive a[0]; the port has none (10:62f0) */
    default:
        win_stub("ispace_24: other modes");
        return 0;
    }
}
