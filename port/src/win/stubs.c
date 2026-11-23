/* USER and GDI calls not implemented yet: text, menus, dialogs, scroll
 * bars, help.  Each logs its name once and returns a neutral value. */
#include <string.h>

#include "winrt.h"

BOOL TextOut(HDC dc, int16_t x, int16_t y, LPCSTR s, int16_t n) { (void)dc; (void)x; (void)y; (void)s; (void)n; STUB(); return 1; }
BOOL ExtTextOut(HDC dc, int16_t x, int16_t y, UINT f, const RECT *r, LPCSTR s, UINT n, int16_t *dx) { (void)dc; (void)x; (void)y; (void)f; (void)r; (void)s; (void)n; (void)dx; STUB(); return 1; }
DWORD GetTextExtent(HDC dc, LPCSTR s, int16_t n) { (void)dc; (void)s; STUB(); return MAKELONG(n * 7, 14); }
BOOL GetTextMetrics(HDC dc, TEXTMETRIC *tm) { (void)dc; STUB(); memset(tm, 0, sizeof *tm); tm->tmHeight = 14; tm->tmAscent = 11; tm->tmDescent = 3; tm->tmAveCharWidth = 6; tm->tmMaxCharWidth = 13; return 1; }
BOOL DrawIcon(HDC dc, int16_t x, int16_t y, HICON i) { (void)dc; (void)x; (void)y; (void)i; STUB(); return 1; }

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

HWND CreateDialog(HINSTANCE h, LPCSTR name, HWND parent, DLGPROC proc) { (void)h; (void)name; (void)parent; (void)proc; STUB(); return 0; }
int16_t DialogBox(HINSTANCE h, LPCSTR name, HWND parent, DLGPROC proc) { (void)h; (void)name; (void)parent; (void)proc; STUB(); return -1; }
void EndDialog(HWND w, int16_t r) { (void)w; (void)r; STUB(); }
HWND GetDlgItem(HWND w, int16_t id) { (void)w; (void)id; STUB(); return 0; }
BOOL IsDialogMessage(HWND w, MSG *m) { (void)w; (void)m; return 0; }

int16_t SetScrollPos(HWND w, int16_t bar, int16_t pos, BOOL redraw) { (void)w; (void)bar; (void)pos; (void)redraw; STUB(); return 0; }
void SetScrollRange(HWND w, int16_t bar, int16_t lo, int16_t hi, BOOL redraw) { (void)w; (void)bar; (void)lo; (void)hi; (void)redraw; STUB(); }
BOOL WinHelp(HWND w, LPCSTR file, UINT cmd, DWORD data) { (void)w; (void)file; (void)cmd; (void)data; STUB(); return 0; }
