/* USER and GDI calls not implemented yet: menus, scroll bars,
 * help.  Each logs its name once and returns a neutral value. */
#include <string.h>

#include "winrt.h"

HMENU LoadMenu(HINSTANCE h, LPCSTR name) { (void)h; (void)name; STUB(); return handle_new(H_MENU, NULL); }
BOOL DestroyMenu(HMENU m) { if (handle_type(m) == H_MENU) handle_free(m); return 1; }
BOOL SetMenu(HWND w, HMENU m) { (void)w; (void)m; STUB(); return 1; }
void DrawMenuBar(HWND w) { (void)w; STUB(); }
HMENU GetSubMenu(HMENU m, int16_t i) { (void)m; (void)i; STUB(); return 0; }
HMENU GetSystemMenu(HWND w, BOOL revert) { (void)w; (void)revert; STUB(); return 0; }
int16_t GetMenuItemCount(HMENU m) { (void)m; STUB(); return 0; }
BOOL AppendMenu(HMENU m, UINT f, UINT id, LPCSTR s) { (void)m; (void)f; (void)id; (void)s; STUB(); return 1; }
BOOL ModifyMenu(HMENU m, UINT pos, UINT f, UINT id, LPCSTR s) { (void)m; (void)pos; (void)f; (void)id; (void)s; STUB(); return 1; }
BOOL CheckMenuItem(HMENU m, UINT id, UINT f) { (void)m; (void)id; (void)f; STUB(); return 0; }
BOOL EnableMenuItem(HMENU m, UINT id, UINT f) { (void)m; (void)id; (void)f; STUB(); return 0; }
BOOL TrackPopupMenu(HMENU m, UINT f, int16_t x, int16_t y, int16_t r, HWND w, const RECT *rc) { (void)m; (void)f; (void)x; (void)y; (void)r; (void)w; (void)rc; STUB(); return 0; }


int16_t SetScrollPos(HWND w, int16_t bar, int16_t pos, BOOL redraw) { (void)w; (void)bar; (void)pos; (void)redraw; STUB(); return 0; }
void SetScrollRange(HWND w, int16_t bar, int16_t lo, int16_t hi, BOOL redraw) { (void)w; (void)bar; (void)lo; (void)hi; (void)redraw; STUB(); }
BOOL WinHelp(HWND w, LPCSTR file, UINT cmd, DWORD data) { (void)w; (void)file; (void)cmd; (void)data; STUB(); return 0; }
