/* The window manager shared by user.c (windows, messages), input.c
 * (keyboard and mouse), dialog.c, controls.c and gdi.c (window DCs). */
#ifndef USER_H
#define USER_H

#include "winrt.h"

/* Windows 3.1 constants and calls the game itself does not use. */
#define WM_ENABLE 0x000A
#define WM_SETTEXT 0x000C      /* sent after the text is stored; lParam unused */
#define WM_ERASEBKGND 0x0014
#define WM_KILLFOCUS 0x0008
#define WM_NCPAINT 0x0085
#define WM_GETDLGCODE 0x0087
#define WM_SYSCHAR 0x0106
#define DM_GETDEFID (WM_USER + 0)

#define WS_DISABLED 0x08000000L
#define WS_BORDER 0x00800000L
#define WS_DLGFRAME 0x00400000L
#define WS_VSCROLL 0x00200000L
#define WS_GROUP 0x00020000L
#define DS_MODALFRAME 0x80L
#define DS_SETFONT 0x40L

#define CS_VREDRAW 0x0001
#define CS_HREDRAW 0x0002
#define GW_HWNDNEXT 2
#define GW_CHILD 5
#define VK_BACK 0x08
#define VK_F10 0x79
#define VK_HOME 0x24
#define VK_END 0x23
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define COLOR_ACTIVECAPTION 2
#define COLOR_WINDOWFRAME 6
#define COLOR_CAPTIONTEXT 9
#define COLOR_BTNFACE 15
#define COLOR_BTNSHADOW 16
#define COLOR_BTNTEXT 18
#define COLOR_BTNHIGHLIGHT 20

#define DLGC_WANTARROWS 0x0001
#define DLGC_WANTCHARS 0x0080
#define DLGC_DEFPUSHBUTTON 0x0010
#define DLGC_UNDEFPUSHBUTTON 0x0020
#define DLGC_STATIC 0x0100
#define DLGC_BUTTON 0x2000

#define GWW_HINSTANCE (-6)

HWND GetWindow(HWND h, UINT cmd);
WORD GetWindowWord(HWND h, int16_t index);
LRESULT SendDlgItemMessage(HWND dlg, int16_t id, UINT msg, WPARAM wp, LPARAM lp);
HWND GetParent(HWND h);
int16_t GetClassName(HWND h, LPSTR name, int16_t n);
HWND SetCapture(HWND h);
void ReleaseCapture(void);
BOOL UnregisterClass(LPCSTR name, HINSTANCE inst);
void ScreenToClient(HWND h, POINT *p);
void OffsetRect(RECT *r, int16_t dx, int16_t dy);
void UnionRect(RECT *d, const RECT *a, const RECT *b);
HDC GetWindowDC(HWND h);

/* A window.  rect and client are screen coordinates; a child's are
 * kept in step with its parent's. */
typedef struct {
    uint16_t hwnd;
    WNDPROC proc;
    RECT rect;
    RECT client;
    DWORD style;
    uint16_t parent;        /* parent of a child window, owner of a popup */
    HMENU id;
    HINSTANCE inst;
    int visible;
    int dirty;              /* needs WM_PAINT */
    int erase;              /* WM_PAINT's BeginPaint erases first */
    RECT update;            /* what needs painting, screen coordinates */
    HBRUSH background;      /* the class's */
    char cls[32];
    char text[256];
    void *data;             /* state of a built-in control (controls.c) */
    WORD words[8];
    LONG longs[4];
} Wnd;

Wnd *wnd_get(HWND h);
void win_pump(void);        /* SDL events and frame presentation */
int wnd_is_child(const Wnd *w);
/* The windows above w's top-level window (popups made later), up to
 * max of their rectangles; window DCs do not draw there. */
int wnd_occluders(const Wnd *w, RECT *out, int max);
uint32_t wnd_zgen(void);    /* changes whenever the stacking or a rectangle does */
/* The deepest visible, enabled window under screen point (x, y). */
HWND wnd_at(int x, int y);
/* The client area of a window at rect: inside its border and caption
 * (DS_MODALFRAME counts for dialogs only). */
void wnd_frame(DWORD style, int dialog, RECT *client, const RECT *rect);
void wnd_send_click(HWND h, UINT msg, int x, int y, WPARAM keys);

/* Built-in window classes (controls.c), registered at start-up. */
void controls_register(void);
/* Combo box and edit contents for native callers (the message forms
 * take far pointers in lParam). */
int16_t combo_add_string(HWND combo, LPCSTR s);
int16_t combo_find_string(HWND combo, int16_t start, LPCSTR s);
int16_t combo_get_text(HWND combo, int16_t i, LPSTR out, int16_t n);

/* Where keyboard messages go: the focus window, else the active one. */
HWND user_key_target(void);

/* Dialogs (dialog.c). */
#define DIALOG_CLASS "#32770"
int dialog_is(HWND h);
void dialog_register(void);

#endif
