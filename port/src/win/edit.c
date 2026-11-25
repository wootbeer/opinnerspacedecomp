/* The Edit control class: multi-line ones show their text word-wrapped
 * (the game only displays text in them); single-line ones are edited as
 * in Windows 3.1: a blinking caret, a selection (Shift with the arrow
 * keys or the mouse, all of it when the dialog moves the focus there),
 * a length limit (EM_LIMITTEXT) and scrolling sideways (ES_AUTOHSCROLL)
 * to keep the caret in view.  No clipboard and no undo.  A combo box's
 * field (id 1001) leaves the keys of the combo box's list to it. */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

#define ES_MULTILINE 0x0004
#define ES_READONLY 0x0800
#define EM_GETSEL (WM_USER + 0)
#define EM_LIMITTEXT (WM_USER + 21)
#define EN_SETFOCUS 0x0100
#define EN_KILLFOCUS 0x0200
#define EN_CHANGE 0x0300
#define EN_UPDATE 0x0400
#define EN_MAXTEXT 0x0501
#define CB_GETDROPPEDSTATE (WM_USER + 23)
#define COMBO_EDIT 1001
#define CTLCOLOR_EDIT 1
#define CARET_TIMER 1
#define BLINK_MS 530            /* GetCaretBlinkTime's default */
#define MAX_TEXT 255            /* the window text's room (user.h) */

typedef struct {
    HFONT font;
    int anchor, caret;          /* the selection runs from anchor to caret */
    int first;                  /* first character shown */
    int limit;
    int caret_on;               /* the caret is inverted on the screen */
    int dragging;
} Edit;

static Edit *edit_of(HWND h)
{
    Wnd *w = wnd_get(h);

    if (w && !w->data && (w->data = calloc(1, sizeof(Edit))) != NULL)
        ((Edit *)w->data)->limit = 30000;
    return w ? w->data : NULL;
}

static int sel_min(const Edit *e)
{
    return e->anchor < e->caret ? e->anchor : e->caret;
}

static int sel_max(const Edit *e)
{
    return e->anchor > e->caret ? e->anchor : e->caret;
}

static HDC edit_dc(HWND h, HFONT *old)
{
    HDC dc = GetDC(h);
    Edit *e = edit_of(h);

    *old = e->font ? SelectObject(dc, e->font) : 0;
    return dc;
}

static void edit_release(HWND h, HDC dc, HFONT old)
{
    if (old)
        SelectObject(dc, old);
    ReleaseDC(h, dc);
}

/* Width of n characters of s. */
static int extent(HDC dc, const char *s, int n)
{
    return n > 0 ? LOWORD(GetTextExtent(dc, s, (int16_t)n)) : 0;
}

static int line_height(HDC dc)
{
    TEXTMETRIC tm;

    GetTextMetrics(dc, &tm);
    return tm.tmHeight;
}

/* The caret: one pixel wide, a line high, inverted [uncertain width]. */
static void invert_caret(HWND h)
{
    Wnd *w = wnd_get(h);
    Edit *e = edit_of(h);
    HFONT old;
    HDC dc = edit_dc(h, &old);

    PatBlt(dc, (int16_t)(1 + extent(dc, w->text + e->first, e->caret - e->first)), 1, 1,
           (int16_t)line_height(dc), DSTINVERT);
    edit_release(h, dc, old);
    e->caret_on = !e->caret_on;
}

static void hide_caret(HWND h)
{
    if (edit_of(h)->caret_on)
        invert_caret(h);
}

/* The caret shown again (once the window is) and its blinking
 * restarted. */
static void show_caret(HWND h)
{
    if (GetFocus() != h || (wnd_get(h)->style & ES_READONLY))
        return;
    if (!edit_of(h)->caret_on && wnd_visible(wnd_get(h)))
        invert_caret(h);
    SetTimer(h, CARET_TIMER, BLINK_MS, NULL);
}

/* Scrolls so that the caret is inside the control. */
static void keep_caret_visible(HWND h)
{
    Wnd *w = wnd_get(h);
    Edit *e = edit_of(h);
    HFONT old;
    HDC dc;
    RECT r;

    if (e->caret < e->first)
        e->first = e->caret;
    GetClientRect(h, &r);
    dc = edit_dc(h, &old);
    while (e->first < e->caret && extent(dc, w->text + e->first, e->caret - e->first) > r.right - 2)
        e->first++;
    edit_release(h, dc, old);
}

static void paint_single(HWND h, HDC dc, const RECT *r)
{
    Wnd *w = wnd_get(h);
    Edit *e = edit_of(h);
    const char *s = w->text + e->first;
    int n = (int)SDL_strlen(s), lo = sel_min(e) - e->first, hi = sel_max(e) - e->first, x = 1;
    int lh = line_height(dc);
    HBRUSH br;
    RECT sel;

    if (lo < 0)
        lo = 0;
    if (hi < 0)
        hi = 0;
    SetBkMode(dc, TRANSPARENT);
    TextOut(dc, 1, 1, s, (int16_t)n);
    if (GetFocus() != h || lo >= hi)
        return;
    x += extent(dc, s, lo);
    SetRect(&sel, (int16_t)x, 1, (int16_t)(x + extent(dc, s + lo, hi - lo)), (int16_t)(1 + lh));
    IntersectRect(&sel, &sel, r);
    br = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
    FillRect(dc, &sel, br);
    DeleteObject(br);
    SetTextColor(dc, GetSysColor(COLOR_HIGHLIGHTTEXT));
    TextOut(dc, (int16_t)x, 1, s + lo, (int16_t)(hi - lo));
}

/* Multi-line: the text word-wrapped, left-aligned. */
static void paint_multi(HWND h, HDC dc, const RECT *r)
{
    const char *s = wnd_get(h)->text;
    int y = r->top, width = r->right - r->left - 1, lh = line_height(dc);

    SetBkMode(dc, TRANSPARENT);
    while (*s && y < r->bottom) {
        int n = 0, fit = 0;
        while (s[n] && s[n] != '\n') {
            n++;
            if ((s[n] == ' ' || !s[n] || s[n] == '\n') && extent(dc, s, n) <= width)
                fit = n;
            else if (extent(dc, s, n) > width)
                break;
        }
        if (!fit)
            fit = n > 0 ? n : 1;
        TextOut(dc, (int16_t)(r->left + 1), (int16_t)y, s, (int16_t)fit);
        s += fit;
        while (*s == ' ')
            s++;
        if (*s == '\n')
            s++;
        y += lh;
    }
}

static void paint(HWND h)
{
    Wnd *w = wnd_get(h);
    Edit *e = edit_of(h);
    HFONT old;
    HDC dc;
    HBRUSH bg;
    RECT r;

    w->dirty = w->erase = 0;
    dc = edit_dc(h, &old);
    bg = (HBRUSH)SendMessage(GetParent(h), WM_CTLCOLOR, dc, MAKELONG(h, CTLCOLOR_EDIT));
    GetClientRect(h, &r);
    if (bg)
        FillRect(dc, &r, bg);
    if (w->style & ES_MULTILINE)
        paint_multi(h, dc, &r);
    else
        paint_single(h, dc, &r);
    edit_release(h, dc, old);
    if (e->caret_on) {
        e->caret_on = 0;
        invert_caret(h);
    }
}

static void notify(HWND h, int code)
{
    SendMessage(GetParent(h), WM_COMMAND, (WPARAM)GetDlgCtrlID(h), MAKELONG(h, code));
}

/* The selection set (caret at end), scrolled into view and shown. */
static void set_sel(HWND h, int anchor, int caret)
{
    Edit *e = edit_of(h);
    int n = (int)SDL_strlen(wnd_get(h)->text);

    hide_caret(h);
    e->anchor = anchor < 0 || anchor > n ? n : anchor;
    e->caret = caret < 0 || caret > n ? n : caret;
    keep_caret_visible(h);
    InvalidateRect(h, NULL, 0);
    UpdateWindow(h);
    show_caret(h);
}

/* Replaces the selection by n characters of s, within the limit. */
static void replace_sel(HWND h, const char *s, int n)
{
    Wnd *w = wnd_get(h);
    Edit *e = edit_of(h);
    int lo = sel_min(e), hi = sel_max(e), len = (int)SDL_strlen(w->text);
    int room = (e->limit < MAX_TEXT ? e->limit : MAX_TEXT) - (len - (hi - lo));

    if (n > room) {
        n = room > 0 ? room : 0;
        MessageBeep(0);
        notify(h, EN_MAXTEXT);
    }
    if (!n && lo == hi)
        return;
    memmove(w->text + lo + n, w->text + hi, (size_t)(len - hi + 1));
    memcpy(w->text + lo, s, (size_t)n);
    notify(h, EN_UPDATE);
    set_sel(h, lo + n, lo + n);
    notify(h, EN_CHANGE);
}

static void key(HWND h, int vk)
{
    Edit *e = edit_of(h);
    int n = (int)SDL_strlen(wnd_get(h)->text), shift = GetKeyState(VK_SHIFT) < 0, to;

    switch (vk) {
    case VK_LEFT:
        to = !shift && e->anchor != e->caret ? sel_min(e) : e->caret - (e->caret > 0);
        break;
    case VK_RIGHT:
        to = !shift && e->anchor != e->caret ? sel_max(e) : e->caret + (e->caret < n);
        break;
    case VK_HOME:
        to = 0;
        break;
    case VK_END:
        to = n;
        break;
    case VK_DELETE:
        if (wnd_get(h)->style & ES_READONLY)
            return;
        if (e->anchor == e->caret) {
            if (e->caret == n)
                return;
            e->anchor = e->caret + 1;
        }
        replace_sel(h, "", 0);
        return;
    default:
        return;
    }
    set_sel(h, shift ? e->anchor : to, to);
}

static void character(HWND h, int ch)
{
    Edit *e = edit_of(h);
    char c = (char)ch;

    if (wnd_get(h)->style & ES_READONLY)
        return;
    if (ch == VK_BACK) {
        if (e->anchor == e->caret) {
            if (!e->caret)
                return;
            e->anchor = e->caret - 1;
        }
        replace_sel(h, "", 0);
    } else if ((unsigned char)c >= ' ') {
        replace_sel(h, &c, 1);
    }
}

/* The combo box whose field h is, or 0. */
static HWND combo_of(HWND h)
{
    char cls[16];
    HWND p = GetParent(h);

    if (!p || GetDlgCtrlID(h) != COMBO_EDIT)
        return 0;
    GetClassName(p, cls, sizeof cls);
    return SDL_strcasecmp(cls, "ComboBox") ? 0 : p;
}

/* Keys for a combo box's list: up and down, F4, and all while it is
 * open. */
static int combo_key(HWND combo, int vk)
{
    return combo && (vk == VK_UP || vk == VK_DOWN || vk == VK_F4 || SendMessage(combo, CB_GETDROPPEDSTATE, 0, 0));
}

/* The character boundary nearest to x. */
static int index_at(HWND h, int x)
{
    Wnd *w = wnd_get(h);
    Edit *e = edit_of(h);
    int n = (int)SDL_strlen(w->text), i;
    HFONT old;
    HDC dc = edit_dc(h, &old);

    for (i = e->first; i < n; i++) {
        int mid = 1 + extent(dc, w->text + e->first, i - e->first) + extent(dc, w->text + i, 1) / 2;
        if (x < mid)
            break;
    }
    edit_release(h, dc, old);
    return i;
}

LRESULT edit_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    Edit *e = edit_of(h);
    int i;

    if (!e)
        return DefWindowProc(h, msg, wp, lp);
    switch (msg) {
    case WM_PAINT:
        paint(h);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_SETFONT:
        e->font = wp;
        if (lp)
            InvalidateRect(h, NULL, 1);
        return 0;
    case 0x0031:                /* WM_GETFONT */
        return e->font;
    case WM_SETTEXT:
        hide_caret(h);
        e->anchor = e->caret = e->first = 0;
        InvalidateRect(h, NULL, 1);
        show_caret(h);
        return 0;
    case WM_ENABLE:
        InvalidateRect(h, NULL, 1);
        return 0;
    case WM_GETDLGCODE:
        return DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTARROWS |
               (combo_of(h) ? SendMessage(combo_of(h), msg, wp, lp) & DLGC_WANTMESSAGE : 0);
    case WM_SETFOCUS:
        InvalidateRect(h, NULL, 0);
        show_caret(h);
        notify(h, EN_SETFOCUS);
        return 0;
    case WM_KILLFOCUS:
        KillTimer(h, CARET_TIMER);
        hide_caret(h);
        InvalidateRect(h, NULL, 0);
        notify(h, EN_KILLFOCUS);
        return 0;
    case WM_TIMER:
        if (wp == CARET_TIMER && GetFocus() == h && (e->caret_on || wnd_visible(w)))
            invert_caret(h);
        return 0;
    case WM_LBUTTONDOWN:
        SetFocus(h);
        i = index_at(h, (int16_t)LOWORD(lp));
        set_sel(h, GetKeyState(VK_SHIFT) < 0 ? e->anchor : i, i);
        e->dragging = 1;
        SetCapture(h);
        return 0;
    case WM_MOUSEMOVE:
        if (e->dragging)
            set_sel(h, e->anchor, index_at(h, (int16_t)LOWORD(lp)));
        return 0;
    case WM_LBUTTONUP:
        if (e->dragging) {
            e->dragging = 0;
            ReleaseCapture();
        }
        return 0;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        if (combo_key(combo_of(h), (int)wp))
            return SendMessage(combo_of(h), msg, wp, lp);
        if (msg == WM_SYSKEYDOWN)
            break;
        if (!(w->style & ES_MULTILINE))
            key(h, (int)wp);
        return 0;
    case WM_CHAR:
        if (!(w->style & ES_MULTILINE))
            character(h, (int)wp);
        return 0;
    case EM_GETSEL:
        return MAKELONG(sel_min(e), sel_max(e));
    case EM_SETSEL:             /* start -1: no selection */
        i = (int16_t)LOWORD(lp);
        set_sel(h, i == -1 ? e->caret : i, i == -1 ? e->caret : (int16_t)HIWORD(lp));
        return 1;
    case EM_LIMITTEXT:
        e->limit = wp ? (int)wp : 30000;
        return 0;
    case WM_DESTROY:
        KillTimer(h, CARET_TIMER);
        return 0;
    }
    return DefWindowProc(h, msg, wp, lp);
}
