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
#define WM_NCHITTEST 0x0084    /* asked of children only; DefWindowProc answers HTCLIENT */
#define WM_NCPAINT 0x0085
#define WM_GETDLGCODE 0x0087
#define WM_SYSCHAR 0x0106
#define WM_NCACTIVATE 0x0086
#define WM_NCMOUSEMOVE 0x00A0  /* WM_MOUSEMOVE .. WM_RBUTTONDBLCLK less 0x160 */
#define WM_NCLBUTTONDOWN 0x00A1
#define WM_INITMENU 0x0116
#define WM_INITMENUPOPUP 0x0117
#define WM_MENUSELECT 0x011F
#define WM_RBUTTONDBLCLK 0x0206
#define WM_HSCROLL 0x0114
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
#define CS_SAVEBITS 0x0800
#define SW_SHOWNA 8            /* shown, not activated */
#define GW_HWNDNEXT 2
#define GW_CHILD 5
#define VK_BACK 0x08
#define VK_F10 0x79
#define VK_HOME 0x24
#define VK_END 0x23
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define COLOR_SCROLLBAR 0
#define COLOR_ACTIVECAPTION 2
#define COLOR_INACTIVECAPTION 3
#define COLOR_MENU 4
#define COLOR_WINDOWFRAME 6
#define COLOR_MENUTEXT 7
#define COLOR_CAPTIONTEXT 9
#define COLOR_ACTIVEBORDER 10
#define COLOR_INACTIVEBORDER 11
#define COLOR_BTNFACE 15
#define COLOR_BTNSHADOW 16
#define COLOR_BTNTEXT 18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT 20

#define DLGC_WANTARROWS 0x0001
#define DLGC_WANTMESSAGE 0x0004     /* every key: a dropped-down combo box */
#define DLGC_WANTCHARS 0x0080
#define DLGC_DEFPUSHBUTTON 0x0010
#define DLGC_UNDEFPUSHBUTTON 0x0020
#define DLGC_STATIC 0x0100
#define DLGC_BUTTON 0x2000

#define GWW_HINSTANCE (-6)

/* Buttons and statics: check boxes and icons. */
#define BS_CHECKBOX 2
#define BS_AUTOCHECKBOX 3
#define BM_GETCHECK (WM_USER + 0)
#define BM_SETCHECK (WM_USER + 1)
#define BM_GETSTATE (WM_USER + 2)
#define BM_SETSTATE (WM_USER + 3)       /* shown pressed (wParam 1) or not */
#define BST_PUSHED 0x0004
#define SS_ICON 3
#define STM_SETICON (WM_USER + 0)
void CheckDlgButton(HWND dlg, int16_t id, UINT check);
UINT IsDlgButtonChecked(HWND dlg, int16_t id);
/* A check box chosen by its mnemonic: focus, then as clicked. */
void button_click(HWND h);

/* Hit-test codes: where a point lies in a window. */
#define HTTRANSPARENT (-1)     /* the window under it gets the mouse */
#define HTNOWHERE 0
#define HTCLIENT 1
#define HTCAPTION 2
#define HTSYSMENU 3
#define HTMENU 5
#define HTBORDER 18

#define SC_SIZE 0xF000
#define SC_MOVE 0xF010
#define SC_MOUSEMENU 0xF090
#define SC_KEYMENU 0xF100
#define SC_TASKLIST 0xF130

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
    uint8_t *saved;         /* the screen under a CS_SAVEBITS window while it is shown */
    HMENU sysmenu;          /* the window's own copy of the system menu (menu.c) */
    WORD words[8];
    LONG longs[4];
} Wnd;

Wnd *wnd_get(HWND h);
void win_pump(void);        /* SDL events, ended sounds and frame presentation */
int wnd_is_child(const Wnd *w);
int wnd_visible(const Wnd *w);   /* shown, and its parents too */
/* The windows above w's top-level window (popups made later), up to
 * max of their rectangles; window DCs do not draw there. */
int wnd_occluders(const Wnd *w, RECT *out, int max);
uint32_t wnd_zgen(void);    /* changes whenever the stacking or a rectangle does */
/* The deepest visible, enabled window under screen point (x, y). */
HWND wnd_at(int x, int y);
/* The client area of a window at rect: inside its border and caption
 * (DS_MODALFRAME counts for dialogs only); a menu bar is not counted. */
void wnd_frame(DWORD style, int dialog, RECT *client, const RECT *rect);
/* Mouse input at screen (x, y) for window h: client messages, or the
 * non-client ones (WM_NCMOUSEMOVE ...) outside its client area. */
void wnd_send_click(HWND h, UINT msg, int x, int y, WPARAM keys);
/* What part of w screen point (x, y) is on (HT...). */
int wnd_hit(const Wnd *w, int x, int y);
/* The window's frame changed (a menu bar came or went): the client area
 * is worked out again, WM_SIZE and WM_MOVE are sent when it changed, and
 * the frame is repainted. */
void wnd_reframe(HWND h);
/* Where w's caption and menu bar are, in window coordinates; empty when
 * it has none. */
void wnd_caption_rect(const Wnd *w, RECT *r);
void wnd_menu_rect(const Wnd *w, RECT *r);
/* The System font (Liberation Sans Bold standing in), made once. */
HFONT wnd_system_font(void);
HWND wnd_capture(void);

/* Built-in window classes (controls.c, edit.c, listbox.c), registered
 * at start-up, and the 3-D drawing they share (controls.c). */
void controls_register(void);
LRESULT edit_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp);
LRESULT listbox_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp);
void ctl_fill(HDC dc, int l, int t, int r, int b, COLORREF c);
void ctl_bevel(HDC dc, int l, int t, int r, int b, int thin);   /* raised face */
/* Text with '&' prefixes (unless noprefix): the next character is
 * underlined.  Returns the width; draws only when draw is set. */
int ctl_label(HDC dc, int x, int y, const char *s, int n, int noprefix, int draw);
#define EM_SETSEL (WM_USER + 1)
#define CB_LIMITTEXT (WM_USER + 1)
#define DLGC_HASSETSEL 0x0008
/* Combo box and edit contents for native callers (the message forms
 * take far pointers in lParam). */
int16_t combo_add_string(HWND combo, LPCSTR s);
int16_t combo_find_string(HWND combo, int16_t start, LPCSTR s);
int16_t combo_get_text(HWND combo, int16_t i, LPSTR out, int16_t n);

/* Where keyboard messages go: the focus window, else the active one. */
HWND user_key_target(void);

/* Key message lParam bits (input.c). */
#define KF_ALT 0x20000000L      /* the context code: Alt held */
#define KF_REPEAT 0x40000000L   /* the key was already down */
#define KF_UP 0x80000000L       /* transition: the key was released */
/* Alt or F10 was pressed and released with no other key between (the
 * menu key); asking clears it. */
int input_menu_key_tapped(void);
/* A key (an SDL key code) pressed or released as on the keyboard. */
void input_key(uint32_t key, int down);

/* The game controller (pad.c).  pad_game_port: what the 1994 game port
 * loop (ISPACE.DLL 9:3ffe) reads, the loop counts of joystick A's x and
 * y and n (2 or 4) buttons (bit k: button k + 1 held); 0 when no
 * joystick answers.  pad_poll: the keys of the buttons (win_pump). */
int pad_game_port(uint16_t count[2], uint16_t *buttons, int n);
void pad_poll(void);

/* Menus (menu.c).  A top-level window's menu bar is its id (GWW_ID), as
 * in Windows. */
#define MENU_BAR_H 18       /* SM_CYMENU */
int menu_is(HMENU m);
void menu_paint_bar(Wnd *w, HDC dc);
void menu_paint_sysbox(Wnd *w, HDC dc, int pressed);
/* WM_SYSCOMMAND SC_KEYMENU and SC_MOUSEMENU: the menu loop. */
void menu_syscommand(HWND h, WPARAM cmd, LPARAM lp);
/* A window goes: its menu bar and system menu go with it. */
void menu_window_gone(Wnd *w);
void menu_register(void);

/* Scroll bar controls (scrollbar.c); the Get calls are for the oracle (tools/dll_oracle). */
LRESULT scrollbar_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp);
int16_t GetScrollPos(HWND h, int16_t which);
void GetScrollRange(HWND h, int16_t which, int16_t *lo, int16_t *hi);

/* Dialogs (dialog.c). */
#define DIALOG_CLASS "#32770"
int dialog_is(HWND h);
int dialog_ended(HWND h, int16_t *result);   /* EndDialog was called, with *result */
void dialog_register(void);

#endif
