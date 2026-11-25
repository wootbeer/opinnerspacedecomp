/* Scroll bar controls (class ScrollBar; vertical, the game's only kind):
 * arrows at the ends, the thumb, and a page area on each side of it,
 * drawn in Windows 3.1's look.  A click is tracked in a loop of its own
 * until the button is released, as Windows 3.1 did: arrows and page
 * areas repeat while held, the thumb follows the mouse; the parent gets
 * WM_VSCROLL with the SB_ codes, then SB_ENDSCROLL. */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>

#include "user.h"

#define SB_LINEUP 0
#define SB_LINEDOWN 1
#define SB_PAGEUP 2
#define SB_PAGEDOWN 3
#define SB_THUMBPOSITION 4
#define SB_THUMBTRACK 5
#define SB_ENDSCROLL 8
#define THUMB 9                 /* the part: the thumb */
#define NONE (-1)
#define CTLCOLOR_SCROLLBAR 5
#define ARROW 17                /* SM_CYVSCROLL; the thumb as long (SM_CYVTHUMB) [uncertain] */
#define FIRST_DELAY 200         /* ms before a held arrow repeats, then every REPEAT ms [uncertain] */
#define REPEAT 50
#define TIMER_ID 0x7fff

typedef struct {
    int16_t min, max, pos;
    int pressed;                /* the part held and under the mouse, or NONE */
    int tracking;               /* the thumb is dragged ... */
    int16_t track_pos;          /* ... to this position */
} Bar;

typedef struct {
    int len, arrow, travel;     /* travel < 0: no room for the thumb */
    int top;                    /* the thumb's top */
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

static int muldiv(int a, int b, int c)
{
    return c ? (a * b + c / 2) / c : 0;
}

static void geometry(HWND h, const Bar *b, Geo *g)
{
    RECT r;
    int range = b->max - b->min, pos = b->tracking ? b->track_pos : b->pos;

    GetClientRect(h, &r);
    g->len = r.bottom;
    g->arrow = SDL_min(g->len / 2, ARROW);
    g->travel = range > 0 ? g->len - 2 * g->arrow - ARROW : -1;
    g->top = g->arrow + muldiv(pos - b->min, SDL_max(g->travel, 0), range);
}

static int part_at(HWND h, const Bar *b, int x, int y)
{
    RECT r;
    Geo g;

    GetClientRect(h, &r);
    geometry(h, b, &g);
    if (x < 0 || x >= r.right || y < 0 || y >= g.len)
        return NONE;
    if (y < g.arrow)
        return SB_LINEUP;
    if (y >= g.len - g.arrow)
        return SB_LINEDOWN;
    if (g.travel < 0)
        return NONE;
    if (y < g.top)
        return SB_PAGEUP;
    if (y >= g.top + ARROW)
        return SB_PAGEDOWN;
    return THUMB;
}

/* An arrow button: black outline, raised face (pressed: flat, shadow
 * on the top and left, the arrow a pixel down and right). */
static void draw_arrow(HDC dc, int wd, int t, int b, int up, int pressed)
{
    int cx = wd / 2 + pressed, cy = (t + b) / 2 + pressed, i;

    ctl_fill(dc, 0, t, wd, b, GetSysColor(COLOR_WINDOWFRAME));
    if (pressed) {
        ctl_fill(dc, 1, t + 1, wd - 1, b - 1, GetSysColor(COLOR_BTNFACE));
        ctl_fill(dc, 1, t + 1, wd - 1, t + 2, GetSysColor(COLOR_BTNSHADOW));
        ctl_fill(dc, 1, t + 1, 2, b - 1, GetSysColor(COLOR_BTNSHADOW));
    } else {
        ctl_bevel(dc, 1, t + 1, wd - 1, b - 1, 1);
    }
    for (i = 0; i < 4; i++) {
        int y = up ? cy - 2 + i : cy + 1 - i;
        ctl_fill(dc, cx - i, y, cx + i + 1, y + 1, GetSysColor(COLOR_BTNTEXT));
    }
}

/* The shaft in the parent's WM_CTLCOLOR brush between black sides, the
 * arrows, the thumb (a raised face between black lines); a page area
 * held is inverted [uncertain]. */
static void paint(HWND h)
{
    Bar *b = bar_of(h);
    HDC dc;
    RECT r;
    Geo g;
    int wd, below;

    if (!b || !wnd_visible(wnd_get(h)))
        return;
    dc = GetDC(h);
    GetClientRect(h, &r);
    wd = r.right;
    geometry(h, b, &g);
    below = g.top + ARROW;
    ctl_fill(dc, 0, 0, wd, g.len, GetSysColor(COLOR_WINDOWFRAME));
    SetRect(&r, 1, (int16_t)g.arrow, (int16_t)(wd - 1), (int16_t)(g.len - g.arrow));
    FillRect(dc, &r, (HBRUSH)SendMessage(GetParent(h), WM_CTLCOLOR, dc, MAKELONG(h, CTLCOLOR_SCROLLBAR)));
    draw_arrow(dc, wd, 0, g.arrow, 1, b->pressed == SB_LINEUP);
    draw_arrow(dc, wd, g.len - g.arrow, g.len, 0, b->pressed == SB_LINEDOWN);
    if (g.travel >= 0) {
        ctl_fill(dc, 0, g.top, wd, below, GetSysColor(COLOR_WINDOWFRAME));
        ctl_bevel(dc, 1, g.top + 1, wd - 1, below - 1, 1);
    }
    if (b->pressed == SB_PAGEUP)
        PatBlt(dc, 1, (int16_t)g.arrow, (int16_t)(wd - 2), (int16_t)(g.top - g.arrow), DSTINVERT);
    if (b->pressed == SB_PAGEDOWN)
        PatBlt(dc, 1, (int16_t)below, (int16_t)(wd - 2), (int16_t)(g.len - g.arrow - below), DSTINVERT);
    ReleaseDC(h, dc);
}

static void notify(HWND h, int code, int pos)
{
    SendMessage(GetParent(h), WM_VSCROLL, (WPARAM)code, MAKELONG(pos, h));
}

static void set_pressed(HWND h, int part)
{
    Bar *b = bar_of(h);

    if (b && b->pressed != part) {
        b->pressed = part;
        paint(h);
    }
}

/* The thumb dragged with the mouse at y, grabbed grab pixels below its
 * top: the position there. */
static int16_t drag_pos(HWND h, const Bar *b, int y, int grab)
{
    Geo g;

    geometry(h, b, &g);
    if (g.travel <= 0)
        return b->pos;
    return (int16_t)(b->min + muldiv(SDL_clamp(y - grab - g.arrow, 0, g.travel), b->max - b->min, g.travel));
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
        } else if ((pos = drag_pos(h, b, y, grab)) != b->track_pos) {
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
        grab = y - g.top;
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

LRESULT scrollbar_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Bar *b = bar_of(h);
    PAINTSTRUCT ps;

    switch (msg) {
    case WM_CREATE:
        b->pressed = NONE;
        if (!(wnd_get(h)->style & SBS_VERT))
            win_stub("ScrollBar: horizontal");
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
