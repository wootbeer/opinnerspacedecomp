/* Scroll bar controls (class ScrollBar), vertical (SBS_VERT) or
 * horizontal: arrows at the ends, the thumb, and a page area on each side
 * of it, drawn in Windows 3.1's look.  A click is tracked in a loop of
 * its own until the button is released, as Windows 3.1 did: arrows and
 * page areas repeat while held, the thumb follows the mouse; the parent
 * gets WM_VSCROLL or WM_HSCROLL with the SB_ codes, then SB_ENDSCROLL.
 * A bar with the focus (WS_TABSTOP ones in dialogs) blinks its thumb and
 * takes the arrow keys, Page Up/Down, Home and End. */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>

#include "user.h"

#define SB_LINEUP 0
#define SB_LINEDOWN 1
#define SB_PAGEUP 2
#define SB_PAGEDOWN 3
#define SB_THUMBPOSITION 4
#define SB_THUMBTRACK 5
#define SB_TOP 6
#define SB_BOTTOM 7
#define SB_ENDSCROLL 8
#define THUMB 9                 /* the part: the thumb */
#define NONE (-1)
#define CTLCOLOR_SCROLLBAR 5
#define ARROW 17                /* SM_CYVSCROLL, SM_CXHSCROLL; the thumb as long [uncertain] */
#define FIRST_DELAY 200         /* ms before a held arrow repeats, then every REPEAT ms [uncertain] */
#define REPEAT 50
#define BLINK_MS 530            /* the focused thumb's blink: GetCaretBlinkTime's default [uncertain] */
#define TIMER_ID 0x7fff
#define BLINK_TIMER 0x7ffe

typedef struct {
    int16_t min, max, pos;
    int pressed;                /* the part held and under the mouse, or NONE */
    int tracking;               /* the thumb is dragged ... */
    int16_t track_pos;          /* ... to this position */
    int blink;                  /* the focused thumb is shown inverted */
} Bar;

typedef struct {
    int vert;
    int len, thick;             /* along the bar and across it */
    int arrow, travel;          /* travel < 0: no room for the thumb */
    int top;                    /* the thumb's start along the bar */
} Geo;

static Bar *bar_of(HWND h)
{
    Wnd *w = wnd_get(h);

    if (!w || w->proc != scrollbar_proc)
        return NULL;
    if (!w->data)
        w->data = calloc(1, sizeof(Bar));
    return w->data;
}

static int is_vert(HWND h)
{
    return (wnd_get(h)->style & SBS_VERT) != 0;
}

static int muldiv(int a, int b, int c)
{
    return c ? (a * b + c / 2) / c : 0;
}

static void geometry(HWND h, const Bar *b, Geo *g)
{
    RECT r;
    int range = b->max - b->min, pos = b->tracking ? b->track_pos : b->pos;

    GetClientRect(h, &r);
    g->vert = is_vert(h);
    g->len = g->vert ? r.bottom : r.right;
    g->thick = g->vert ? r.right : r.bottom;
    g->arrow = SDL_min(g->len / 2, ARROW);
    g->travel = range > 0 ? g->len - 2 * g->arrow - ARROW : -1;
    g->top = g->arrow + muldiv(pos - b->min, SDL_max(g->travel, 0), range);
}

/* The rectangle from a to b along the bar, inset by in across it. */
static void span(const Geo *g, int a, int b, int in, RECT *r)
{
    if (g->vert)
        SetRect(r, (int16_t)in, (int16_t)a, (int16_t)(g->thick - in), (int16_t)b);
    else
        SetRect(r, (int16_t)a, (int16_t)in, (int16_t)b, (int16_t)(g->thick - in));
}

static int part_at(HWND h, const Bar *b, int x, int y)
{
    Geo g;
    int along, across;

    geometry(h, b, &g);
    along = g.vert ? y : x;
    across = g.vert ? x : y;
    if (across < 0 || across >= g.thick || along < 0 || along >= g.len)
        return NONE;
    if (along < g.arrow)
        return SB_LINEUP;
    if (along >= g.len - g.arrow)
        return SB_LINEDOWN;
    if (g.travel < 0)
        return NONE;
    if (along < g.top)
        return SB_PAGEUP;
    if (along >= g.top + ARROW)
        return SB_PAGEDOWN;
    return THUMB;
}

static void shrink(RECT *r)
{
    SetRect(r, (int16_t)(r->left + 1), (int16_t)(r->top + 1), (int16_t)(r->right - 1), (int16_t)(r->bottom - 1));
}

static void fill(HDC dc, const RECT *r, COLORREF c)
{
    ctl_fill(dc, r->left, r->top, r->right, r->bottom, c);
}

/* An arrow button from a to b along the bar, pointing to its end of the
 * bar (first: up or left): black outline, raised face (pressed: flat,
 * shadow on the top and left, the arrow a pixel down and right). */
static void draw_arrow(HDC dc, const Geo *g, int a, int b, int first, int pressed)
{
    RECT r;
    int cx, cy, i;

    span(g, a, b, 0, &r);
    fill(dc, &r, GetSysColor(COLOR_WINDOWFRAME));
    cx = (r.left + r.right) / 2 + pressed;
    cy = (r.top + r.bottom) / 2 + pressed;
    shrink(&r);
    if (pressed) {
        fill(dc, &r, GetSysColor(COLOR_BTNFACE));
        ctl_fill(dc, r.left, r.top, r.right, r.top + 1, GetSysColor(COLOR_BTNSHADOW));
        ctl_fill(dc, r.left, r.top, r.left + 1, r.bottom, GetSysColor(COLOR_BTNSHADOW));
    } else {
        ctl_bevel(dc, r.left, r.top, r.right, r.bottom, 1);
    }
    for (i = 0; i < 4; i++) {
        int k = first ? -2 + i : 1 - i;         /* rows (columns) from the tip */
        if (g->vert)
            ctl_fill(dc, cx - i, cy + k, cx + i + 1, cy + k + 1, GetSysColor(COLOR_BTNTEXT));
        else
            ctl_fill(dc, cx + k, cy - i, cx + k + 1, cy + i + 1, GetSysColor(COLOR_BTNTEXT));
    }
}

/* The shaft in the parent's WM_CTLCOLOR brush between black sides, the
 * arrows, the thumb (a raised face between black lines); a page area
 * held is inverted [uncertain], as is the focused thumb when it blinks. */
static void paint(HWND h)
{
    Bar *b = bar_of(h);
    HDC dc;
    RECT r;
    Geo g;
    int below;

    if (!b || !wnd_visible(wnd_get(h)))
        return;
    dc = GetDC(h);
    geometry(h, b, &g);
    below = g.top + ARROW;
    span(&g, 0, g.len, 0, &r);
    fill(dc, &r, GetSysColor(COLOR_WINDOWFRAME));
    span(&g, g.arrow, g.len - g.arrow, 1, &r);
    FillRect(dc, &r, (HBRUSH)SendMessage(GetParent(h), WM_CTLCOLOR, dc, MAKELONG(h, CTLCOLOR_SCROLLBAR)));
    draw_arrow(dc, &g, 0, g.arrow, 1, b->pressed == SB_LINEUP);
    draw_arrow(dc, &g, g.len - g.arrow, g.len, 0, b->pressed == SB_LINEDOWN);
    if (g.travel >= 0) {
        span(&g, g.top, below, 0, &r);
        fill(dc, &r, GetSysColor(COLOR_WINDOWFRAME));
        shrink(&r);
        ctl_bevel(dc, r.left, r.top, r.right, r.bottom, 1);
        if (b->blink && GetFocus() == h)
            PatBlt(dc, r.left, r.top, (int16_t)(r.right - r.left), (int16_t)(r.bottom - r.top), DSTINVERT);
    }
    if (b->pressed == SB_PAGEUP || b->pressed == SB_PAGEDOWN) {
        span(&g, b->pressed == SB_PAGEUP ? g.arrow : below, b->pressed == SB_PAGEUP ? g.top : g.len - g.arrow, 1, &r);
        PatBlt(dc, r.left, r.top, (int16_t)(r.right - r.left), (int16_t)(r.bottom - r.top), DSTINVERT);
    }
    ReleaseDC(h, dc);
}

static void notify(HWND h, int code, int pos)
{
    SendMessage(GetParent(h), is_vert(h) ? WM_VSCROLL : WM_HSCROLL, (WPARAM)code, MAKELONG(pos, h));
}

static void set_pressed(HWND h, int part)
{
    Bar *b = bar_of(h);

    if (b && b->pressed != part) {
        b->pressed = part;
        paint(h);
    }
}

/* The thumb dragged with the mouse at (x, y), grabbed grab pixels past
 * its start: the position there. */
static int16_t drag_pos(HWND h, const Bar *b, int x, int y, int grab)
{
    Geo g;

    geometry(h, b, &g);
    if (g.travel <= 0)
        return b->pos;
    return (int16_t)(b->min + muldiv(SDL_clamp((g.vert ? y : x) - grab - g.arrow, 0, g.travel), b->max - b->min,
                                     g.travel));
}

/* A message of the tracking loop for the scroll bar: its mouse input
 * and timer are the loop's, its keys are dropped; 0 for the others. */
static int track_msg(HWND h, int part, int grab, const MSG *m)
{
    Bar *b = bar_of(h);
    int x = (int16_t)LOWORD(m->lParam), y = (int16_t)HIWORD(m->lParam);
    int16_t pos;

    if (m->hwnd != h)
        return 0;
    switch (m->message) {
    case WM_MOUSEMOVE:
        if (part != THUMB) {
            set_pressed(h, part_at(h, b, x, y) == part ? part : NONE);
        } else if ((pos = drag_pos(h, b, x, y, grab)) != b->track_pos) {
            b->track_pos = pos;
            paint(h);
            notify(h, SB_THUMBTRACK, pos);
        }
        return 1;
    case WM_LBUTTONUP:
        ReleaseCapture();
        return 1;
    case WM_TIMER:
        if (m->wParam != TIMER_ID)
            return 0;
        if (b->pressed == part)
            notify(h, part, 0);
        SetTimer(h, TIMER_ID, REPEAT, NULL);
        return 1;
    }
    return (m->message >= WM_KEYDOWN && m->message <= WM_SYSCHAR) || (m->message >= WM_MOUSEMOVE && m->message <= WM_RBUTTONDBLCLK);
}

/* A click at (x, y), tracked until the button is released. */
static void track(HWND h, int x, int y)
{
    Bar *b = bar_of(h);
    int part = part_at(h, b, x, y), grab = 0;
    Geo g;
    MSG m;

    if (part == NONE)
        return;
    SetCapture(h);
    if (part == THUMB) {
        geometry(h, b, &g);
        grab = (g.vert ? y : x) - g.top;
        b->tracking = 1;
        b->track_pos = b->pos;
    } else {
        set_pressed(h, part);
        notify(h, part, 0);
        SetTimer(h, TIMER_ID, FIRST_DELAY, NULL);
    }
    while (bar_of(h) && wnd_capture() == h) {
        if (!GetMessage(&m, 0, 0, 0)) {
            PostQuitMessage((int16_t)m.wParam);
            break;
        }
        if (!track_msg(h, part, grab, &m)) {
            TranslateMessage(&m);
            DispatchMessage(&m);
        }
    }
    if ((b = bar_of(h)) == NULL)
        return;
    ReleaseCapture();
    KillTimer(h, TIMER_ID);
    set_pressed(h, NONE);
    if (part == THUMB) {
        b->tracking = 0;
        paint(h);
        notify(h, SB_THUMBPOSITION, b->track_pos);
    }
    if (bar_of(h))
        notify(h, SB_ENDSCROLL, 0);
}

/* The keys a focused bar takes: their SB_ code, or NONE. */
static int key_code(WPARAM vk)
{
    switch (vk) {
    case VK_LEFT:
    case VK_UP: return SB_LINEUP;
    case VK_RIGHT:
    case VK_DOWN: return SB_LINEDOWN;
    case VK_PRIOR: return SB_PAGEUP;
    case VK_NEXT: return SB_PAGEDOWN;
    case VK_HOME: return SB_TOP;
    case VK_END: return SB_BOTTOM;
    }
    return NONE;
}

LRESULT scrollbar_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Bar *b = bar_of(h);
    PAINTSTRUCT ps;

    switch (msg) {
    case WM_CREATE:
        b->pressed = NONE;
        return 0;
    case WM_PAINT:
        BeginPaint(h, &ps);
        EndPaint(h, &ps);
        paint(h);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        if (wnd_get(h)->style & WS_TABSTOP)
            SetFocus(h);
        track(h, (int16_t)LOWORD(lp), (int16_t)HIWORD(lp));
        return 0;
    case WM_GETDLGCODE:
        return DLGC_WANTARROWS;
    case WM_SETFOCUS:
        b->blink = 1;
        SetTimer(h, BLINK_TIMER, BLINK_MS, NULL);
        paint(h);
        return 0;
    case WM_KILLFOCUS:
        KillTimer(h, BLINK_TIMER);
        b->blink = 0;
        paint(h);
        return 0;
    case WM_TIMER:
        if (wp == BLINK_TIMER) {
            b->blink = !b->blink;
            paint(h);
        }
        return 0;
    case WM_KEYDOWN:
        if (key_code(wp) != NONE)
            notify(h, key_code(wp), 0);
        return 0;
    case WM_KEYUP:
        if (key_code(wp) != NONE)
            notify(h, SB_ENDSCROLL, 0);
        return 0;
    }
    return DefWindowProc(h, msg, wp, lp);
}

/* SB_CTL only: the game has no window scroll bars. */
static Bar *ctl_bar(HWND h, int16_t which)
{
    if (which != SB_CTL) {
        win_stub("SetScrollPos/SetScrollRange: window scroll bars");
        return NULL;
    }
    return bar_of(h);
}

int16_t SetScrollPos(HWND h, int16_t which, int16_t pos, BOOL redraw)
{
    Bar *b = ctl_bar(h, which);
    int16_t old;

    if (!b)
        return 0;
    old = b->pos;
    b->pos = (int16_t)SDL_clamp(pos, SDL_min(b->min, b->max), SDL_max(b->min, b->max));
    if (redraw)
        paint(h);
    return old;
}

void SetScrollRange(HWND h, int16_t which, int16_t lo, int16_t hi, BOOL redraw)
{
    Bar *b = ctl_bar(h, which);

    if (!b)
        return;
    b->min = lo;
    b->max = hi;
    b->pos = (int16_t)SDL_clamp(b->pos, SDL_min(lo, hi), SDL_max(lo, hi));
    if (redraw)
        paint(h);
}

int16_t GetScrollPos(HWND h, int16_t which)
{
    Bar *b = ctl_bar(h, which);

    return b ? b->pos : 0;
}

void GetScrollRange(HWND h, int16_t which, int16_t *lo, int16_t *hi)
{
    Bar *b = ctl_bar(h, which);

    *lo = b ? b->min : 0;
    *hi = b ? b->max : 0;
}
