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

/* DOS paths (C:\SPACE\...) to host paths: the game folder is the data
 * folder, the Windows folder is the writable settings folder. */
#define GAME_DIR "C:\\SPACE\\"
#define WIN_DIR "C:\\WINDOWS"
int dos_to_host(const char *dos, char *out, size_t size);

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

#include "win.h"

#endif
