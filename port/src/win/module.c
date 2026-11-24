/* Modules (INSPACE.EXE and the DLLs it loads) and their resources, read
 * from the original files. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "ne.h"

typedef struct {
    char name[16];          /* file name, upper case: ISPACE.DLL */
    char path[128];         /* DOS path */
    NeFile ne;
    int refs;
} Module;

typedef struct {
    const uint8_t *data;
    uint32_t size;
} Rsrc;

#define MAX_MODULES 8
static HINSTANCE exe;
static HINSTANCE loaded[MAX_MODULES];

static void base_name(const char *path, char *out, size_t size)
{
    const char *b = strrchr(path, '\\');
    size_t i;

    b = b ? b + 1 : path;
    for (i = 0; i + 1 < size && b[i]; i++)
        out[i] = (char)toupper((unsigned char)b[i]);
    out[i] = 0;
}

static HINSTANCE load(const char *dos_path)
{
    char host[1024];
    Module *m;
    HINSTANCE h;
    int i;

    if (!dos_to_host(dos_path, host, sizeof host))
        return 2;
    m = calloc(1, sizeof *m);
    if (!m)
        return 8;
    if (!ne_open(&m->ne, host)) {
        free(m);
        return 2;
    }
    base_name(dos_path, m->name, sizeof m->name);
    snprintf(m->path, sizeof m->path, "%s", dos_path);
    m->refs = 1;
    h = handle_new(H_MODULE, m);
    for (i = 0; h && i < MAX_MODULES; i++)
        if (!handle_get(loaded[i], H_MODULE)) {
            loaded[i] = h;
            break;
        }
    return h ? h : 8;
}

int module_init(void)
{
    exe = load(GAME_DIR "INSPACE.EXE");
    return exe >= 32;
}

HINSTANCE module_exe(void)
{
    return exe;
}

int module_is(HINSTANCE h, const char *name)
{
    Module *m = handle_get(h, H_MODULE);

    return m && !strcmp(m->name, name);
}

HINSTANCE LoadLibrary(LPCSTR path)
{
    char name[16];
    int i;

    base_name(path, name, sizeof name);
    for (i = 0; i < MAX_MODULES; i++) {
        Module *m = handle_get(loaded[i], H_MODULE);
        if (m && !strcmp(m->name, name)) {
            m->refs++;
            return loaded[i];
        }
    }
    return load(path);
}

void FreeLibrary(HINSTANCE h)
{
    Module *m = handle_get(h, H_MODULE);

    if (m && h != exe && --m->refs == 0) {
        ne_close(&m->ne);
        free(m);
        handle_free(h);
    }
}

FARPROC GetProcAddress(HINSTANCE h, LPCSTR name)
{
    if (module_is(h, "ISPACE.DLL") && IS_INTRESOURCE(name))
        return ispace_proc((int)(uintptr_t)name);
    return NULL;
}

int16_t GetModuleFileName(HINSTANCE h, LPSTR buf, int16_t size)
{
    Module *m = handle_get(h, H_MODULE);

    if (!m || size <= 0)
        return 0;
    snprintf(buf, (size_t)size, "%s", m->path);
    return (int16_t)strlen(buf);
}

/* Resources. */
const uint8_t *module_resource(HINSTANCE h, LPCSTR type, LPCSTR name, uint32_t *size)
{
    Module *m = handle_get(h, H_MODULE);

    if (!m)
        return NULL;
    return ne_resource(&m->ne,
                       IS_INTRESOURCE(type) ? (uint16_t)(uintptr_t)type : 0,
                       IS_INTRESOURCE(type) ? NULL : type,
                       IS_INTRESOURCE(name) ? (uint16_t)(uintptr_t)name : 0,
                       IS_INTRESOURCE(name) ? NULL : name, size);
}

HRSRC FindResource(HINSTANCE h, LPCSTR name, LPCSTR type)
{
    Rsrc *r = malloc(sizeof *r);
    HRSRC hr;

    if (!r)
        return 0;
    r->data = module_resource(h, type, name, &r->size);
    if (!r->data || !(hr = handle_new(H_RSRC, r))) {
        free(r);
        return 0;
    }
    return hr;
}

DWORD SizeofResource(HINSTANCE h, HRSRC hr)
{
    Rsrc *r = handle_get(hr, H_RSRC);

    (void)h;
    return r ? r->size : 0;
}

HGLOBAL LoadResource(HINSTANCE h, HRSRC hr)
{
    Rsrc *r = handle_get(hr, H_RSRC);
    HGLOBAL g;

    (void)h;
    if (!r || !(g = GlobalAlloc(GMEM_MOVEABLE, r->size)))
        return 0;
    memcpy(GlobalLock(g), r->data, r->size);
    return g;
}

void *LockResource(HGLOBAL g)
{
    return GlobalLock(g);
}

BOOL FreeResource(HGLOBAL g)
{
    return GlobalFree(g) != 0;
}

int16_t LoadString(HINSTANCE h, UINT id, LPSTR buf, int16_t size)
{
    uint32_t len;
    const uint8_t *p = module_resource(h, MAKEINTRESOURCE(RT_STRING_), MAKEINTRESOURCE(id / 16 + 1), &len);
    const uint8_t *end = p + len;
    unsigned i, n;

    if (size <= 0)
        return 0;
    buf[0] = 0;
    if (!p)
        return 0;
    for (i = 0; i < id % 16 && p < end; i++)
        p += 1 + *p;
    if (p >= end)
        return 0;
    n = *p;
    if (n > (unsigned)size - 1)
        n = (unsigned)size - 1;
    memcpy(buf, p + 1, n);
    buf[n] = 0;
    return (int16_t)n;
}

HICON LoadIcon(HINSTANCE h, LPCSTR name)
{
    (void)h;
    (void)name;
    return handle_new(H_ICON, NULL);
}

HCURSOR LoadCursor(HINSTANCE h, LPCSTR name)
{
    static HCURSOR arrow;

    (void)h;
    (void)name;
    if (!arrow)
        arrow = handle_new(H_CURSOR, NULL);
    return arrow;
}

BOOL DestroyIcon(HICON h)
{
    if (handle_type(h) == H_ICON)
        handle_free(h);
    return 1;
}

HICON ExtractIcon(HINSTANCE h, LPCSTR file, UINT index)
{
    (void)h;
    (void)file;
    (void)index;
    STUB();
    return 0;
}

/* Accelerators: the table as stored (BYTE flags, WORD key, WORD command;
 * flag 0x80 ends it). */
HACCEL LoadAccelerators(HINSTANCE h, LPCSTR name)
{
    uint32_t len;
    const uint8_t *p = module_resource(h, MAKEINTRESOURCE(RT_ACCELERATOR_), name, &len);

    return p ? handle_new(H_ACCEL, (void *)p) : 0;
}

/* A virtual-key entry matches WM_KEYDOWN/WM_SYSKEYDOWN with the same
 * Shift, Ctrl and Alt state; a character entry matches WM_CHAR, or
 * WM_SYSCHAR when it asks for Alt. */
int16_t TranslateAccelerator(HWND hwnd, HACCEL acc, MSG *msg)
{
    const uint8_t *p = handle_get(acc, H_ACCEL);
    int virt, shift, ctrl, alt;

    if (!p)
        return 0;
    switch (msg->message) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        virt = 1;
        break;
    case WM_CHAR:
    case WM_SYSCHAR:
        virt = 0;
        break;
    default:
        return 0;
    }
    shift = GetKeyState(VK_SHIFT) < 0;
    ctrl = GetKeyState(VK_CONTROL) < 0;
    alt = GetKeyState(VK_MENU) < 0;
    for (;; p += 5) {
        unsigned fl = p[0], key = p[1] | p[2] << 8, cmd = p[3] | p[4] << 8;
        if (!!(fl & 1) == virt && key == msg->wParam && !!(fl & 0x10) == alt &&
            (!virt || (!!(fl & 4) == shift && !!(fl & 8) == ctrl))) {
            SendMessage(hwnd, WM_COMMAND, (WPARAM)cmd, MAKELONG(0, 1));
            return 1;
        }
        if (fl & 0x80)
            return 0;
    }
}
