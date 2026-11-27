/* USER: window classes, windows, focus, painting, the message queue and
 * timers.  Every window draws straight into the screen; top-level windows
 * are stacked in the order they were made, and window DCs do not draw
 * where a later popup lies (wnd_occluders). */
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "video.h"
#include "platform/platform.h"

#define MAX_CLASSES 24
#define MAX_WINDOWS 128
#define MAX_TIMERS 16
#define QUEUE_LEN 256
#define SCREEN_W 640
#define SCREEN_H 480
#define CAPTION_H 19        /* SM_CYCAPTION less the line it shares with the frame */
#define FRAME 4             /* SM_CXDLGFRAME, SM_CXFRAME [inferred: border width 3, plus 1] */
#define SYSBOX 18           /* SM_CXSIZE: the system menu box */
#define NOTCH (FRAME + SYSBOX - 1)  /* the sizing border's marks, from each corner [uncertain] */
#define MINTRACK_X 100      /* SM_CXMINTRACK, SM_CYMINTRACK [uncertain] */
#define MINTRACK_Y 28
#define CTLCOLOR_SCROLLBAR 5

static struct {
    char name[32];
    WNDCLASS wc;
} classes[MAX_CLASSES];
static int class_count;

static HWND windows[MAX_WINDOWS];   /* in creation order: parents before children */
static HWND active, focus, capture;

static struct {
    HWND hwnd;
    UINT id, ms;
    uint32_t due;
    TIMERPROC proc;
} timers[MAX_TIMERS];

static uint32_t zgen;
static MSG queue[QUEUE_LEN];
static int q_head, q_count;
static int quit_posted, quit_code;

Wnd *wnd_get(HWND h)
{
    return handle_get(h, H_WND);
}

int wnd_is_child(const Wnd *w)
{
    return (w->style & WS_CHILD) != 0;
}

static const WNDCLASS *find_class(LPCSTR name);

int wnd_visible(const Wnd *w)
{
    while (w && w->visible) {
        if (!wnd_is_child(w))
            return 1;
        w = wnd_get(w->parent);
    }
    return 0;
}

static const Wnd *top_level(const Wnd *w)
{
    const Wnd *p;

    while (w && wnd_is_child(w) && (p = wnd_get(w->parent)) != NULL)
        w = p;
    return w;
}

static int z_index(HWND h)
{
    int i;

    for (i = 0; i < MAX_WINDOWS; i++)
        if (windows[i] == h)
            return i;
    return -1;
}

int wnd_occluders(const Wnd *w, RECT *out, int max)
{
    int i, n = 0;

    w = top_level(w);
    if (!w)
        return 0;
    for (i = z_index(w->hwnd) + 1; i < MAX_WINDOWS && n < max; i++) {
        Wnd *o = wnd_get(windows[i]);
        if (o && !wnd_is_child(o) && o->visible)
            out[n++] = o->rect;
    }
    return n;
}

uint32_t wnd_zgen(void)
{
    return zgen;
}

/* Classes. */
static const WNDCLASS *find_class(LPCSTR name)
{
    int i;

    for (i = 0; i < class_count; i++)
        if (!SDL_strcasecmp(classes[i].name, name))
            return &classes[i].wc;
    return NULL;
}

ATOM RegisterClass(const WNDCLASS *wc)
{
    if (class_count == MAX_CLASSES || find_class(wc->lpszClassName))
        return 0;
    SDL_strlcpy(classes[class_count].name, wc->lpszClassName, sizeof classes[0].name);
    classes[class_count].wc = *wc;
    classes[class_count].wc.lpszClassName = classes[class_count].name;
    return (ATOM)(0xc000 + class_count++);
}

BOOL UnregisterClass(LPCSTR name, HINSTANCE inst)
{
    int i;

    (void)inst;
    for (i = 0; i < class_count; i++)
        if (!SDL_strcasecmp(classes[i].name, name)) {
            classes[i] = classes[--class_count];
            classes[i].wc.lpszClassName = classes[i].name;
            return 1;
        }
    return 0;
}

int16_t GetClassName(HWND h, LPSTR name, int16_t n)
{
    Wnd *w = wnd_get(h);

    if (!w || n <= 0)
        return 0;
    SDL_strlcpy(name, w->cls, (size_t)n);
    return (int16_t)SDL_strlen(name);
}

/* Window geometry. */
void wnd_frame(DWORD style, int dialog, RECT *client, const RECT *rect)
{
    int b = 0, top = 0;

    if ((dialog && style & DS_MODALFRAME) || (style & WS_CAPTION) == WS_DLGFRAME || style & WS_THICKFRAME)
        b = FRAME;
    else if (style & WS_BORDER)
        b = 1;
    if ((style & WS_CAPTION) == WS_CAPTION)
        top = CAPTION_H;
    SetRect(client, (int16_t)(rect->left + b), (int16_t)(rect->top + b + top),
            (int16_t)(rect->right - b), (int16_t)(rect->bottom - b));
}

/* The client area of w, inside its frame and menu bar. */
static void frame_of(Wnd *w)
{
    wnd_frame(w->style, dialog_is(w->hwnd), &w->client, &w->rect);
    if (!wnd_is_child(w) && menu_is(w->id))
        w->client.top = (int16_t)(w->client.top + MENU_BAR_H);
}

static int has_caption(const Wnd *w)
{
    return (w->style & WS_CAPTION) == WS_CAPTION;
}

void wnd_caption_rect(const Wnd *w, RECT *r)
{
    int b = w->client.left - w->rect.left;

    SetRect(r, 0, 0, 0, 0);
    if (has_caption(w))
        SetRect(r, (int16_t)b, (int16_t)b, (int16_t)(w->rect.right - w->rect.left - b), (int16_t)(b + CAPTION_H - 1));
}

void wnd_menu_rect(const Wnd *w, RECT *r)
{
    int b = w->client.left - w->rect.left, top = w->client.top - w->rect.top;

    SetRect(r, 0, 0, 0, 0);
    if (!wnd_is_child(w) && menu_is(w->id))
        SetRect(r, (int16_t)b, (int16_t)(top - MENU_BAR_H), (int16_t)(w->rect.right - w->rect.left - b), (int16_t)top);
}

int wnd_hit(const Wnd *w, int x, int y)
{
    RECT r;
    POINT p;

    p.x = (int16_t)x;
    p.y = (int16_t)y;
    if (PtInRect(&w->client, p))
        return HTCLIENT;
    if (!PtInRect(&w->rect, p))
        return HTNOWHERE;
    p.x = (int16_t)(p.x - w->rect.left);
    p.y = (int16_t)(p.y - w->rect.top);
    wnd_menu_rect(w, &r);
    if (PtInRect(&r, p))
        return HTMENU;
    wnd_caption_rect(w, &r);
    if (PtInRect(&r, p))
        return w->style & WS_SYSMENU && p.x < r.left + SYSBOX ? HTSYSMENU : HTCAPTION;
    return HTBORDER;
}

static void offset_tree(HWND h, int dx, int dy)
{
    Wnd *w = wnd_get(h);
    int i;

    OffsetRect(&w->rect, (int16_t)dx, (int16_t)dy);
    OffsetRect(&w->client, (int16_t)dx, (int16_t)dy);
    OffsetRect(&w->update, (int16_t)dx, (int16_t)dy);
    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *c = wnd_get(windows[i]);
        if (c && wnd_is_child(c) && c->parent == h)
            offset_tree(c->hwnd, dx, dy);
    }
}

/* Adds r (screen) to what w must repaint. */
static void invalidate(Wnd *w, const RECT *r, int erase)
{
    RECT x;

    if (!IntersectRect(&x, r, &w->rect))
        return;
    if (w->dirty) {
        UnionRect(&w->update, &w->update, &x);
    } else {
        w->update = x;
        w->dirty = 1;
    }
    w->erase |= erase;
}

/* Windows of a CS_SAVEBITS class (dialogs, menus) keep the screen under
 * them while shown and put it back when they go, so what lies under is
 * not repainted.  Drawing under a shown dialog is clipped, so what was saved
 * stays right unless the dialog moves. */
static void save_under(Wnd *w)
{
    Framebuffer *fb = video_framebuffer();
    const WNDCLASS *wc = find_class(w->cls);
    int y, cw = w->rect.right - w->rect.left;

    if (w->saved || wnd_is_child(w) || !wc || !(wc->style & CS_SAVEBITS) || w->rect.left < 0 || w->rect.top < 0
        || w->rect.right > fb->width || w->rect.bottom > fb->height || cw <= 0)
        return;
    w->saved = malloc((size_t)cw * (size_t)(w->rect.bottom - w->rect.top));
    for (y = w->rect.top; w->saved && y < w->rect.bottom; y++)
        memcpy(w->saved + (size_t)(y - w->rect.top) * (size_t)cw, fb->pixels + (size_t)y * (size_t)fb->width + w->rect.left,
               (size_t)cw);
}

static int restore_under(Wnd *w)
{
    Framebuffer *fb = video_framebuffer();
    int y, cw = w->rect.right - w->rect.left;

    if (!w->saved)
        return 0;
    for (y = w->rect.top; y < w->rect.bottom; y++)
        memcpy(fb->pixels + (size_t)y * (size_t)fb->width + w->rect.left, w->saved + (size_t)(y - w->rect.top) * (size_t)cw,
               (size_t)cw);
    fb->drawn = 1;
    free(w->saved);
    w->saved = NULL;
    return 1;
}

/* Marks what lies under r (screen) for repainting, as Windows does when
 * a window above goes away or moves.  The desktop is black, as the
 * screen is before the first window. */
static void uncover(const RECT *r)
{
    HDC dc = GetDC(0);
    int i;

    FillRect(dc, r, GetStockObject(BLACK_BRUSH));
    ReleaseDC(0, dc);

    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *w = wnd_get(windows[i]);
        if (w && wnd_visible(w))
            invalidate(w, r, 1);
    }
}

/* A sizable or overlapped window's size is kept within the tracking
 * sizes its WM_GETMINMAXINFO gives (DefWindowProc's WM_WINDOWPOSCHANGING,
 * and CreateWindow). */
static void minmax_info(Wnd *w, MINMAXINFO *mm)
{
    memset(mm, 0, sizeof *mm);
    mm->ptMaxSize.x = mm->ptMaxTrackSize.x = SCREEN_W + 2 * FRAME;
    mm->ptMaxSize.y = mm->ptMaxTrackSize.y = SCREEN_H + 2 * FRAME;
    mm->ptMaxPosition.x = mm->ptMaxPosition.y = -FRAME;
    mm->ptMinTrackSize.x = MINTRACK_X;
    mm->ptMinTrackSize.y = MINTRACK_Y;
    w->proc(w->hwnd, WM_GETMINMAXINFO, 0, (LPARAM)mm);
}

static void track_limits(Wnd *w, int *cx, int *cy)
{
    MINMAXINFO mm;

    if (wnd_is_child(w) || !(w->style & WS_THICKFRAME || !(w->style & WS_POPUP)))
        return;
    minmax_info(w, &mm);
    *cx = SDL_clamp(*cx, mm.ptMinTrackSize.x, mm.ptMaxTrackSize.x);
    *cy = SDL_clamp(*cy, mm.ptMinTrackSize.y, mm.ptMaxTrackSize.y);
}

/* Places w at (x, y) (relative to its parent's client area for a child)
 * with size cx x cy, moving its children along.  Returns 0 when nothing
 * changed. */
static int place(Wnd *w, int x, int y, int cx, int cy)
{
    Wnd *p = wnd_is_child(w) ? wnd_get(w->parent) : NULL;
    RECT old = w->rect;
    int dx, dy;

    track_limits(w, &cx, &cy);
    if (p) {
        x += p->client.left;
        y += p->client.top;
    }
    dx = x - w->rect.left;
    dy = y - w->rect.top;
    if (!dx && !dy && cx == w->rect.right - w->rect.left && cy == w->rect.bottom - w->rect.top)
        return 0;
    if (dx || dy)
        offset_tree(w->hwnd, dx, dy);
    w->rect.right = (int16_t)(w->rect.left + cx);
    w->rect.bottom = (int16_t)(w->rect.top + cy);
    frame_of(w);
    zgen++;
    free(w->saved);
    w->saved = NULL;
    if (wnd_visible(w))
        uncover(&old);
    return 1;
}

/* The active window goes (destroyed or hidden): its owner becomes
 * active, else the topmost other visible top-level window, as in
 * Windows. */
static void activate_other(Wnd *gone)
{
    Wnd *o = wnd_get(gone->parent);
    int i;

    active = 0;
    if (!o || !o->visible || o->style & WS_DISABLED)
        for (o = NULL, i = MAX_WINDOWS - 1; i >= 0 && !o; i--) {
            Wnd *c = wnd_get(windows[i]);
            if (c && c != gone && !wnd_is_child(c) && c->visible && !(c->style & WS_DISABLED))
                o = c;
        }
    if (o)
        SetActiveWindow(o->hwnd);
}

/* Windows. */
HWND CreateWindow(LPCSTR cls, LPCSTR title, DWORD style, int16_t x, int16_t y, int16_t w, int16_t h,
                  HWND parent, HMENU menu, HINSTANCE inst, void *param)
{
    const WNDCLASS *wc = find_class(cls);
    Wnd *wnd;
    int i;

    (void)param;
    if (!wc || !(wnd = calloc(1, sizeof *wnd)))
        return 0;
    if ((uint16_t)x == 0x8000) {
        x = y = 0;
        w = SCREEN_W;
        h = SCREEN_H;
    }
    wnd->proc = wc->lpfnWndProc;
    wnd->style = style;
    wnd->parent = parent;
    wnd->id = menu;
    wnd->inst = inst;
    wnd->background = wc->hbrBackground;
    SDL_strlcpy(wnd->cls, wc->lpszClassName, sizeof wnd->cls);
    SDL_strlcpy(wnd->text, title ? title : "", sizeof wnd->text);
    wnd->hwnd = handle_new(H_WND, wnd);
    if (!wnd->hwnd) {
        free(wnd);
        return 0;
    }
    for (i = 0; i < MAX_WINDOWS && windows[i]; i++)
        ;
    if (i < MAX_WINDOWS)
        windows[i] = wnd->hwnd;
    place(wnd, x, y, w, h);
    if (wnd->proc(wnd->hwnd, WM_CREATE, 0, 0) == -1) {
        DestroyWindow(wnd->hwnd);
        return 0;
    }
    if (wnd_get(wnd->hwnd)) {
        wnd->proc(wnd->hwnd, WM_SIZE, 0, MAKELONG(wnd->client.right - wnd->client.left,
                                                  wnd->client.bottom - wnd->client.top));
        wnd->proc(wnd->hwnd, WM_MOVE, 0, MAKELONG(x, y));
    }
    if (style & WS_VISIBLE)
        ShowWindow(wnd->hwnd, SW_SHOWNORMAL);
    return wnd->hwnd;
}

BOOL DestroyWindow(HWND h)
{
    Wnd *w = wnd_get(h);
    int i;

    if (!w)
        return 0;
    if (w->visible && !wnd_is_child(w)) {
        w->visible = 0;
        if (!restore_under(w))
            uncover(&w->rect);
    }
    free(w->saved);
    w->saved = NULL;
    zgen++;
    if (active == h)
        activate_other(w);
    for (i = 0; i < MAX_WINDOWS; i++)
        if (windows[i] && wnd_get(windows[i]) && wnd_get(windows[i])->parent == h)
            DestroyWindow(windows[i]);
    w->proc(h, WM_DESTROY, 0, 0);
    menu_window_gone(w);
    for (i = 0; i < MAX_TIMERS; i++)
        if (timers[i].hwnd == h)
            timers[i].ms = 0;
    for (i = 0; i < MAX_WINDOWS; i++)
        if (windows[i] == h)
            windows[i] = 0;
    if (active == h)
        active = 0;
    if (focus == h)
        focus = 0;
    if (capture == h)
        capture = 0;
    handle_free(h);
    free(w->data);
    free(w);
    return 1;
}

BOOL IsWindow(HWND h)
{
    return wnd_get(h) != NULL;
}

BOOL ShowWindow(HWND h, int16_t cmd)
{
    Wnd *w = wnd_get(h);
    int was;

    if (!w)
        return 0;
    was = w->visible;
    w->visible = cmd != SW_HIDE;
    zgen++;
    if (w->visible) {
        if (!was)
            save_under(w);
        invalidate(w, &w->rect, 1);
        if (!wnd_is_child(w) && (cmd == SW_SHOW || cmd == SW_SHOWNORMAL || !active))
            SetActiveWindow(h);
    } else if (was) {
        if (!restore_under(w))
            uncover(&w->rect);
        if (active == h)
            activate_other(w);
    }
    return (BOOL)was;
}

void UpdateWindow(HWND h)
{
    Wnd *w = wnd_get(h);

    if (w && wnd_visible(w) && w->dirty)
        SendMessage(h, WM_PAINT, 0, 0);
}

/* Children are repainted where their parent is (no WS_CLIPCHILDREN). */
static void invalidate_tree(Wnd *w, const RECT *r, int erase)
{
    int i;

    invalidate(w, r, erase);
    for (i = z_index(w->hwnd) + 1; i > 0 && i < MAX_WINDOWS; i++) {
        Wnd *c = wnd_get(windows[i]);
        if (c && wnd_is_child(c) && c->parent == w->hwnd)
            invalidate_tree(c, r, erase);
    }
}

void InvalidateRect(HWND h, const RECT *r, BOOL erase)
{
    Wnd *w = wnd_get(h);
    RECT s;

    if (!w)
        return;
    s = r ? *r : w->rect;
    if (r)
        OffsetRect(&s, w->client.left, w->client.top);
    invalidate_tree(w, &s, erase != 0);
}

BOOL IsIconic(HWND h)
{
    Wnd *w = wnd_get(h);

    return w && w->style & WS_MINIMIZE;
}

BOOL IsZoomed(HWND h)
{
    Wnd *w = wnd_get(h);

    return w && w->style & WS_MAXIMIZE;
}

BOOL IsWindowEnabled(HWND h)
{
    Wnd *w = wnd_get(h);

    return w && !(w->style & WS_DISABLED);
}

BOOL EnableWindow(HWND h, BOOL on)
{
    Wnd *w = wnd_get(h);
    int was_disabled;

    if (!w)
        return 0;
    was_disabled = (w->style & WS_DISABLED) != 0;
    if (on)
        w->style &= ~WS_DISABLED;
    else
        w->style |= WS_DISABLED;
    if (was_disabled == !on)
        return (BOOL)was_disabled;
    if (!on && focus == h)
        SetFocus(0);
    SendMessage(h, WM_ENABLE, (WPARAM)(on != 0), 0);
    return (BOOL)was_disabled;
}

HWND GetActiveWindow(void)
{
    return active;
}

HWND SetActiveWindow(HWND h)
{
    HWND old = active;
    Wnd *f = wnd_get(focus);

    if (!wnd_get(h))
        return old;
    active = h;
    if (old != h) {
        SendMessage(old, WM_NCACTIVATE, 0, 0);
        SendMessage(h, WM_NCACTIVATE, 1, 0);
    }
    if (!f || top_level(f)->hwnd != h)
        SetFocus(h);
    return old;
}

HWND GetFocus(void)
{
    return focus;
}

HWND SetFocus(HWND h)
{
    HWND old = focus;

    if (h == old || (h && !wnd_get(h)))
        return old;
    if (old)
        SendMessage(old, WM_KILLFOCUS, h, 0);
    focus = h;
    if (h)
        SendMessage(h, WM_SETFOCUS, old, 0);
    return old;
}

HWND SetCapture(HWND h)
{
    HWND old = capture;

    capture = h;
    return old;
}

void ReleaseCapture(void)
{
    capture = 0;
}

HWND wnd_capture(void)
{
    return capture;
}

HWND GetParent(HWND h)
{
    Wnd *w = wnd_get(h);

    return w ? w->parent : 0;
}

/* GW_CHILD: the first child; GW_HWNDNEXT: the next child of the same
 * parent, in creation order. */
HWND GetWindow(HWND h, UINT cmd)
{
    Wnd *w = wnd_get(h);
    HWND parent;
    int i;

    if (!w || (cmd != GW_CHILD && cmd != GW_HWNDNEXT))
        return 0;
    parent = cmd == GW_CHILD ? h : w->parent;
    for (i = cmd == GW_CHILD ? 0 : z_index(h) + 1; i < MAX_WINDOWS; i++) {
        Wnd *c = wnd_get(windows[i]);
        if (c && wnd_is_child(c) && c->parent == parent)
            return c->hwnd;
    }
    return 0;
}

/* The last visible window containing p among the top-level windows
 * (parent 0) or the children of parent; children that answer
 * WM_NCHITTEST with HTTRANSPARENT (group boxes) are passed over. */
static HWND topmost_at(HWND parent, POINT p)
{
    HWND found = 0;
    int i;

    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *w = wnd_get(windows[i]);
        if (w && w->visible && PtInRect(&w->rect, p) &&
            (parent ? wnd_is_child(w) && w->parent == parent : !wnd_is_child(w)) &&
            (!parent || (int16_t)SendMessage(w->hwnd, WM_NCHITTEST, 0, MAKELONG(p.x, p.y)) != HTTRANSPARENT))
            found = w->hwnd;
    }
    return found;
}

HWND wnd_at(int x, int y)
{
    POINT p;
    HWND h, c;

    p.x = (int16_t)x;
    p.y = (int16_t)y;
    h = topmost_at(0, p);
    if (!IsWindowEnabled(h))
        return 0;
    while ((c = topmost_at(h, p)) != 0 && IsWindowEnabled(c))
        h = c;
    return h;
}

void wnd_send_click(HWND h, UINT msg, int x, int y, WPARAM keys)
{
    Wnd *w = wnd_get(capture ? capture : h);
    int hit;

    if (!w)
        return;
    hit = capture ? HTCLIENT : wnd_hit(w, x, y);
    if (hit == HTCLIENT)
        PostMessage(w->hwnd, msg, keys, MAKELONG(x - w->client.left, y - w->client.top));
    else
        PostMessage(w->hwnd, msg - (WM_MOUSEMOVE - WM_NCMOUSEMOVE), (WPARAM)hit, MAKELONG(x, y));
}

void GetClientRect(HWND h, RECT *r)
{
    Wnd *w = wnd_get(h);

    if (w)
        SetRect(r, 0, 0, w->client.right - w->client.left, w->client.bottom - w->client.top);
    else
        SetRect(r, 0, 0, SCREEN_W, SCREEN_H);
}

void GetWindowRect(HWND h, RECT *r)
{
    Wnd *w = wnd_get(h);

    if (w)
        *r = w->rect;
    else
        SetRect(r, 0, 0, SCREEN_W, SCREEN_H);
}

void ClientToScreen(HWND h, POINT *p)
{
    Wnd *w = wnd_get(h);

    if (w) {
        p->x += w->client.left;
        p->y += w->client.top;
    }
}

void ScreenToClient(HWND h, POINT *p)
{
    Wnd *w = wnd_get(h);

    if (w) {
        p->x -= w->client.left;
        p->y -= w->client.top;
    }
}

BOOL MoveWindow(HWND h, int16_t x, int16_t y, int16_t cx, int16_t cy, BOOL repaint)
{
    Wnd *w = wnd_get(h);
    int moved;

    if (!w)
        return 0;
    moved = place(w, x, y, cx, cy);
    w->proc(h, WM_SIZE, 0, MAKELONG(w->client.right - w->client.left, w->client.bottom - w->client.top));
    w->proc(h, WM_MOVE, 0, MAKELONG(x, y));
    if (repaint && moved)
        invalidate(w, &w->rect, 1);
    return 1;
}

BOOL SetWindowPos(HWND h, HWND after, int16_t x, int16_t y, int16_t cx, int16_t cy, UINT flags)
{
    Wnd *w = wnd_get(h);
    Wnd *p;

    (void)after;
    if (!w)
        return 0;
    p = wnd_is_child(w) ? wnd_get(w->parent) : NULL;
    if (flags & SWP_NOMOVE) {
        x = (int16_t)(w->rect.left - (p ? p->client.left : 0));
        y = (int16_t)(w->rect.top - (p ? p->client.top : 0));
    }
    if (flags & SWP_NOSIZE) {
        cx = (int16_t)(w->rect.right - w->rect.left);
        cy = (int16_t)(w->rect.bottom - w->rect.top);
    }
    place(w, x, y, cx, cy);
    return 1;
}

void SetWindowText(HWND h, LPCSTR s)
{
    Wnd *w = wnd_get(h);

    if (!w)
        return;
    SDL_strlcpy(w->text, s, sizeof w->text);
    SendMessage(h, WM_SETTEXT, 0, 0);
}

int16_t GetWindowText(HWND h, LPSTR s, int16_t n)
{
    Wnd *w = wnd_get(h);

    if (!w || n <= 0)
        return 0;
    SDL_strlcpy(s, w->text, (size_t)n);
    return (int16_t)SDL_strlen(s);
}

WORD SetWindowWord(HWND h, int16_t index, WORD v)
{
    Wnd *w = wnd_get(h);
    WORD old;

    if (!w)
        return 0;
    if (index == GWW_ID) {
        old = w->id;
        w->id = v;
        return old;
    }
    if (index < 0 || index / 2 >= 8)
        return 0;
    old = w->words[index / 2];
    w->words[index / 2] = v;
    return old;
}

WORD GetWindowWord(HWND h, int16_t index)
{
    Wnd *w = wnd_get(h);

    if (!w)
        return 0;
    if (index == GWW_ID)
        return w->id;
    if (index == GWW_HINSTANCE)
        return w->inst;
    return index >= 0 && index / 2 < 8 ? w->words[index / 2] : 0;
}

LONG GetWindowLong(HWND h, int16_t index)
{
    Wnd *w = wnd_get(h);

    if (!w)
        return 0;
    if (index == GWL_STYLE)
        return (LONG)w->style;
    return index >= 0 && index / 4 < 4 ? w->longs[index / 4] : 0;
}

LONG SetWindowLong(HWND h, int16_t index, LONG v)
{
    Wnd *w = wnd_get(h);
    LONG old;

    if (!w)
        return 0;
    if (index == GWL_STYLE) {
        old = (LONG)w->style;
        w->style = (DWORD)v;
        return old;
    }
    if (index < 0 || index / 4 >= 4)
        return 0;
    old = w->longs[index / 4];
    w->longs[index / 4] = v;
    return old;
}

WORD SetClassWord(HWND h, int16_t index, WORD v)
{
    (void)h;
    (void)index;
    (void)v;
    return 0;
}

HTASK GetWindowTask(HWND h)
{
    const Wnd *w = wnd_get(h);

    return w && top_level(w)->inst == WINHELP_INSTANCE ? WINHELP_TASK : 1;
}

int16_t GetDlgCtrlID(HWND h)
{
    Wnd *w = wnd_get(h);

    return w ? (int16_t)w->id : 0;
}

int16_t GetSystemMetrics(int16_t i)
{
    switch (i) {
    case SM_CXSCREEN:
        return SCREEN_W;
    case SM_CYSCREEN:
        return SCREEN_H;
    case SM_CYCAPTION:
        return 20;
    default:
        return 0;
    }
}

/* Painting. */
/* The DC is clipped to what needs painting. */
HDC BeginPaint(HWND h, PAINTSTRUCT *ps)
{
    Wnd *w = wnd_get(h);
    HRGN rgn;

    memset(ps, 0, sizeof *ps);
    if (!w)
        return 0;
    if (!w->dirty)
        SetRect(&w->update, 0, 0, 0, 0);
    w->dirty = 0;
    ps->hdc = GetDC(h);
    ps->rcPaint = w->update;
    OffsetRect(&ps->rcPaint, (int16_t)-w->client.left, (int16_t)-w->client.top);
    rgn = CreateRectRgn(ps->rcPaint.left, ps->rcPaint.top, ps->rcPaint.right, ps->rcPaint.bottom);
    SelectClipRgn(ps->hdc, rgn);
    DeleteObject(rgn);
    if (w->erase) {
        w->erase = 0;
        ps->fErase = !SendMessage(h, WM_ERASEBKGND, ps->hdc, 0);
    }
    return ps->hdc;
}

void EndPaint(HWND h, const PAINTSTRUCT *ps)
{
    ReleaseDC(h, ps->hdc);
}

HFONT wnd_system_font(void)
{
    static HFONT font;

    if (!font)
        font = CreateFont(0, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, "System");
    return font;
}

/* The band of a sizing border (border colour, a mark across it SYSBOX
 * pixels in from each corner) or of a dialog frame (caption colour). */
static void paint_band(Wnd *w, HDC dc, int wd, int ht, int b, int on)
{
    int sizing = w->style & WS_THICKFRAME && !(dialog_is(w->hwnd) && w->style & DS_MODALFRAME);
    COLORREF c = GetSysColor(sizing ? (on ? COLOR_ACTIVEBORDER : COLOR_INACTIVEBORDER)
                                    : (on ? COLOR_ACTIVECAPTION : COLOR_INACTIVECAPTION));
    COLORREF black = GetSysColor(COLOR_WINDOWFRAME);

    ctl_fill(dc, 0, 0, wd, b, c);
    ctl_fill(dc, 0, ht - b, wd, ht, c);
    ctl_fill(dc, 0, b, b, ht - b, c);
    ctl_fill(dc, wd - b, b, wd, ht - b, c);
    if (!sizing)
        return;
    ctl_fill(dc, NOTCH, 0, NOTCH + 1, b, black);
    ctl_fill(dc, wd - 1 - NOTCH, 0, wd - NOTCH, b, black);
    ctl_fill(dc, NOTCH, ht - b, NOTCH + 1, ht, black);
    ctl_fill(dc, wd - 1 - NOTCH, ht - b, wd - NOTCH, ht, black);
    ctl_fill(dc, 0, NOTCH, b, NOTCH + 1, black);
    ctl_fill(dc, 0, ht - 1 - NOTCH, b, ht - NOTCH, black);
    ctl_fill(dc, wd - b, NOTCH, wd, NOTCH + 1, black);
    ctl_fill(dc, wd - b, ht - 1 - NOTCH, wd, ht - NOTCH, black);
}

/* The caption: active or inactive colour, a black line under it, the
 * system menu box on the left, the title centred in the rest. */
static void paint_caption(Wnd *w, HDC dc, int on)
{
    HFONT old;
    RECT r;
    int left;

    wnd_caption_rect(w, &r);
    ctl_fill(dc, r.left, r.top, r.right, r.bottom, GetSysColor(on ? COLOR_ACTIVECAPTION : COLOR_INACTIVECAPTION));
    ctl_fill(dc, r.left - 1, r.bottom, r.right + 1, r.bottom + 1, GetSysColor(COLOR_WINDOWFRAME));
    left = r.left;
    if (w->style & WS_SYSMENU) {
        menu_paint_sysbox(w, dc, 0);
        left += SYSBOX + 1;
    }
    old = SelectObject(dc, wnd_system_font());
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, GetSysColor(on ? COLOR_CAPTIONTEXT : COLOR_INACTIVECAPTIONTEXT));
    SetTextAlign(dc, TA_CENTER);
    TextOut(dc, (int16_t)((left + r.right) / 2), (int16_t)(r.top + 2), w->text, (int16_t)SDL_strlen(w->text));
    SetTextAlign(dc, TA_LEFT);
    SelectObject(dc, old);
}

/* The frame of a window: Windows 3.1's look (black outline, sizing
 * border or dialog frame, caption, menu bar). */
static void paint_frame(Wnd *w)
{
    HDC dc = GetWindowDC(w->hwnd);
    int wd = w->rect.right - w->rect.left, ht = w->rect.bottom - w->rect.top;
    int b = w->client.left - w->rect.left, on = w->hwnd == active;
    HBRUSH frame = CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME));
    RECT r;

    if (b > 1) {
        paint_band(w, dc, wd, ht, b, on);
        SetRect(&r, (int16_t)(b - 1), (int16_t)(b - 1), (int16_t)(wd - b + 1), (int16_t)(ht - b + 1));
        FrameRect(dc, &r, frame);
    }
    if (b > 0) {
        SetRect(&r, 0, 0, (int16_t)wd, (int16_t)ht);
        FrameRect(dc, &r, frame);
    }
    if (has_caption(w))
        paint_caption(w, dc, on);
    menu_paint_bar(w, dc);
    DeleteObject(frame);
    ReleaseDC(w->hwnd, dc);
}

static int has_frame(const Wnd *w)
{
    return w->client.left != w->rect.left || w->client.top != w->rect.top;
}

void wnd_reframe(HWND h)
{
    Wnd *w = wnd_get(h);
    RECT old;

    if (!w)
        return;
    old = w->client;
    frame_of(w);
    if (old.left != w->client.left || old.top != w->client.top || old.right != w->client.right ||
        old.bottom != w->client.bottom) {
        zgen++;
        if (wnd_visible(w))
            invalidate_tree(w, &w->rect, 1);
        if (old.right - old.left != w->client.right - w->client.left ||
            old.bottom - old.top != w->client.bottom - w->client.top)
            w->proc(h, WM_SIZE, 0, MAKELONG(w->client.right - w->client.left, w->client.bottom - w->client.top));
        if (wnd_get(h) && (old.left != w->client.left || old.top != w->client.top))
            w->proc(h, WM_MOVE, 0, MAKELONG(w->client.left, w->client.top));
    }
    if (wnd_get(h) && wnd_visible(w) && has_frame(w))
        SendMessage(h, WM_NCPAINT, 0, 0);
}

/* The brush of a system colour, made once. */
static HBRUSH sys_brush(int i)
{
    static HBRUSH made[32];

    if (!made[i & 31])
        made[i & 31] = CreateSolidBrush(GetSysColor((int16_t)i));
    return made[i & 31];
}

/* System commands: Move, Minimize, Maximize, Restore. */
static void send_size(Wnd *w, WPARAM type)
{
    w->proc(w->hwnd, WM_SIZE, type, MAKELONG(w->client.right - w->client.left, w->client.bottom - w->client.top));
}

static void send_move(Wnd *w)
{
    Wnd *p = wnd_is_child(w) ? wnd_get(w->parent) : NULL;

    w->proc(w->hwnd, WM_MOVE, 0, MAKELONG(w->client.left - (p ? p->client.left : 0),
                                          w->client.top - (p ? p->client.top : 0)));
}

/* Moves w's frame to screen position (x, y) and repaints it there. */
static void move_to(Wnd *w, int x, int y, int cx, int cy)
{
    Wnd *p = wnd_is_child(w) ? wnd_get(w->parent) : NULL;

    if (p) {
        x -= p->client.left;
        y -= p->client.top;
    }
    if (place(w, x, y, cx, cy))
        invalidate_tree(w, &w->rect, 1);
}

/* The 640x480 screen is all the port shows, so a minimized window is the
 * host window minimized; the icon Windows drew is not drawn. */
static void minimize(Wnd *w)
{
    if (w->style & WS_MINIMIZE)
        return;
    w->style |= WS_MINIMIZE;
    video_minimize();
    w->proc(w->hwnd, WM_SIZE, SIZE_MINIMIZED, MAKELONG(32, 32));
}

static void maximize(Wnd *w)
{
    MINMAXINFO mm;

    if (w->style & WS_MINIMIZE) {
        w->style &= ~WS_MINIMIZE;
        video_restore();
    }
    if (!(w->style & WS_MAXIMIZE)) {
        w->normal = w->rect;
        w->style |= WS_MAXIMIZE;
        minmax_info(w, &mm);
        move_to(w, mm.ptMaxPosition.x, mm.ptMaxPosition.y, mm.ptMaxSize.x, mm.ptMaxSize.y);
    }
    invalidate_tree(w, &w->rect, 1);
    send_size(w, SIZE_MAXIMIZED);
    send_move(w);
}

static void restore(Wnd *w)
{
    RECT r = w->normal;

    if (w->style & WS_MINIMIZE) {
        w->style &= ~WS_MINIMIZE;
        video_restore();
        invalidate_tree(w, &w->rect, 1);
        send_size(w, w->style & WS_MAXIMIZE ? SIZE_MAXIMIZED : SIZE_RESTORED);
    } else if (w->style & WS_MAXIMIZE) {
        w->style &= ~WS_MAXIMIZE;
        move_to(w, r.left, r.top, r.right - r.left, r.bottom - r.top);
        send_size(w, SIZE_RESTORED);
        send_move(w);
    }
}

/* The host window was minimized or shown again: the application's main
 * window (the owner of the active window) is told, as Windows 3.1 told
 * it when its icon was made or opened. */
void win_host_minimized(int on)
{
    Wnd *w = wnd_get(active);

    while (w && wnd_get(w->parent))
        w = wnd_get(w->parent);
    if (w && on != !!(w->style & WS_MINIMIZE))
        PostMessage(w->hwnd, WM_SYSCOMMAND, on ? SC_MINIMIZE : SC_RESTORE, 0);
}

/* Windows 3.1's drag frame: a halftone FRAME pixels wide, inverted. */
static void drag_frame(HDC dc, const RECT *r)
{
    int16_t cx = (int16_t)(r->right - r->left), cy = (int16_t)(r->bottom - r->top);

    PatBlt(dc, r->left, r->top, cx, FRAME, PATINVERT);
    PatBlt(dc, r->left, (int16_t)(r->bottom - FRAME), cx, FRAME, PATINVERT);
    PatBlt(dc, r->left, (int16_t)(r->top + FRAME), FRAME, (int16_t)(cy - 2 * FRAME), PATINVERT);
    PatBlt(dc, (int16_t)(r->right - FRAME), (int16_t)(r->top + FRAME), FRAME, (int16_t)(cy - 2 * FRAME), PATINVERT);
}

/* SC_MOVE: Windows 3.1 moves an outline (full drag came with Windows 95)
 * until the button is released, Enter or a click (from the keyboard), or
 * Esc puts it back.  From the keyboard the cursor starts on the caption's
 * middle and the arrow keys move it 8 pixels. */
static void move_loop(Wnd *w, WPARAM cmd, LPARAM lp)
{
    static const uint8_t halftone[16] = {0xaa, 0, 0x55, 0, 0xaa, 0, 0x55, 0, 0xaa, 0, 0x55, 0, 0xaa, 0, 0x55, 0};
    HWND h = w->hwnd, old_capture;
    int by_mouse = (cmd & 0x0f) == HTCAPTION, done = 0, cancel = 0;
    RECT start = w->rect, r = start;
    POINT anchor, at;
    HBITMAP bm;
    HBRUSH brush;
    HGDIOBJ old_brush;
    HDC dc;
    MSG m;

    if (w->style & WS_MAXIMIZE)
        return;
    if (by_mouse) {
        anchor.x = (int16_t)LOWORD(lp);
        anchor.y = (int16_t)HIWORD(lp);
    } else {
        anchor.x = (int16_t)((start.left + start.right) / 2);
        anchor.y = (int16_t)(start.top + FRAME + CAPTION_H / 2);
        SetCursorPos(anchor.x, anchor.y);
    }
    bm = CreateBitmap(8, 8, 1, 1, halftone);
    brush = CreatePatternBrush(bm);
    dc = GetDC(0);
    old_brush = SelectObject(dc, brush);
    old_capture = SetCapture(h);
    drag_frame(dc, &r);
    while (!done && !cancel) {
        if (!GetMessage(&m, 0, 0, 0)) {
            PostQuitMessage((int16_t)m.wParam);
            cancel = 1;
            break;
        }
        switch (m.message) {
        case WM_KEYDOWN:
            done = m.wParam == VK_RETURN;
            cancel = m.wParam == VK_ESCAPE;
            if (done || cancel)
                input_eat_key_up((int)m.wParam);
            GetCursorPos(&at);
            at.x = (int16_t)(at.x + 8 * ((m.wParam == VK_RIGHT) - (m.wParam == VK_LEFT)));
            at.y = (int16_t)(at.y + 8 * ((m.wParam == VK_DOWN) - (m.wParam == VK_UP)));
            SetCursorPos(at.x, at.y);
            break;
        case WM_MOUSEMOVE:
            at = m.pt;
            break;
        case WM_LBUTTONUP:
            done = by_mouse;
            continue;
        case WM_LBUTTONDOWN:
            done = !by_mouse;
            continue;
        case WM_CHAR:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_SYSCHAR:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            continue;
        default:
            DispatchMessage(&m);
            continue;
        }
        drag_frame(dc, &r);
        r = start;
        OffsetRect(&r, (int16_t)(at.x - anchor.x), (int16_t)(at.y - anchor.y));
        drag_frame(dc, &r);
    }
    drag_frame(dc, &r);
    ReleaseCapture();
    if (old_capture)
        SetCapture(old_capture);
    SelectObject(dc, old_brush);
    ReleaseDC(0, dc);
    DeleteObject(brush);
    DeleteObject(bm);
    if (!cancel && IsWindow(h) && (r.left != start.left || r.top != start.top)) {
        move_to(w, r.left, r.top, r.right - r.left, r.bottom - r.top);
        send_move(w);
    }
}

LRESULT DefWindowProc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    PAINTSTRUCT ps;
    RECT r;

    if (!w)
        return 0;
    switch (msg) {
    case WM_NCHITTEST:
        return HTCLIENT;
    case WM_NCPAINT:
        if (has_frame(w))
            paint_frame(w);
        return 0;
    case WM_NCACTIVATE:
        if (wnd_visible(w) && has_frame(w))
            paint_frame(w);
        return 1;
    case WM_NCLBUTTONDOWN:
        if (wp == HTMENU || wp == HTSYSMENU)
            SendMessage(h, WM_SYSCOMMAND, SC_MOUSEMENU + (wp == HTSYSMENU ? HTSYSMENU : 0), lp);
        else if (wp == HTCAPTION)
            SendMessage(h, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, lp);
        return 0;
    case WM_SYSKEYDOWN:
        if (wp == VK_F4 && lp & KF_ALT)
            PostMessage(top_level(w)->hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
        return 0;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        if ((wp == VK_MENU || wp == VK_F10) && input_menu_key_tapped())
            SendMessage(top_level(w)->hwnd, WM_SYSCOMMAND, SC_KEYMENU, 0);
        return 0;
    case WM_SYSCHAR:
        if (!(lp & KF_ALT))
            MessageBeep(0);
        else if (wp == ' ' && wnd_is_child(w))
            SendMessage(w->parent, msg, wp, lp);
        else if (wp != '\t' && wp != 27)
            SendMessage(h, WM_SYSCOMMAND, SC_KEYMENU, (LPARAM)wp);
        return 0;
    case WM_CTLCOLOR:
        if (HIWORD(lp) == CTLCOLOR_SCROLLBAR)
            return sys_brush(COLOR_SCROLLBAR);
        SetTextColor(wp, GetSysColor(COLOR_WINDOWTEXT));
        SetBkColor(wp, GetSysColor(COLOR_WINDOW));
        return sys_brush(COLOR_WINDOW);
    case WM_ERASEBKGND:
        if (!w || !w->background)
            return 0;
        GetClientRect(h, &r);
        FillRect(wp, &r, w->background);
        return 1;
    case WM_PAINT:
        BeginPaint(h, &ps);
        EndPaint(h, &ps);
        return 0;
    case WM_CLOSE:
        DestroyWindow(h);
        return 0;
    case WM_SYSCOMMAND:
        switch (wp & 0xfff0) {
        case SC_CLOSE:
            PostMessage(h, WM_CLOSE, 0, 0);
            break;
        case SC_KEYMENU:
        case SC_MOUSEMENU:
            menu_syscommand(top_level(w)->hwnd, wp, lp);
            break;
        case SC_MOVE:
            move_loop(w, wp, lp);
            break;
        case SC_MINIMIZE:
            minimize(w);
            break;
        case SC_MAXIMIZE:
            maximize(w);
            break;
        case SC_RESTORE:
            restore(w);
            break;
        default:
            win_stub("DefWindowProc: WM_SYSCOMMAND size, task list");
            break;
        }
        return 0;
    }
    return 0;
}

/* Messages. */
BOOL PostMessage(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    MSG *m;
    POINT pt;

    if (q_count == QUEUE_LEN)
        return 0;
    GetCursorPos(&pt);
    m = &queue[(q_head + q_count++) % QUEUE_LEN];
    m->hwnd = h;
    m->message = msg;
    m->wParam = wp;
    m->lParam = lp;
    m->time = platform_time_ms();
    m->pt = pt;
    return 1;
}

/* Takes the first posted msg with wParam wp out of the queue; 1 when
 * there was one. */
int user_unpost(UINT msg, WPARAM wp)
{
    int i, k;

    for (i = 0; i < q_count; i++) {
        MSG *m = &queue[(q_head + i) % QUEUE_LEN];
        if (m->message != msg || m->wParam != wp)
            continue;
        for (k = i; k < q_count - 1; k++)
            queue[(q_head + k) % QUEUE_LEN] = queue[(q_head + k + 1) % QUEUE_LEN];
        q_count--;
        return 1;
    }
    return 0;
}

LRESULT SendMessage(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);

    return w && w->proc ? w->proc(h, msg, wp, lp) : 0;
}

void PostQuitMessage(int16_t code)
{
    quit_posted = 1;
    quit_code = code;
}

static void make_msg(MSG *m, HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    m->hwnd = h;
    m->message = msg;
    m->wParam = wp;
    m->lParam = lp;
    m->time = platform_time_ms();
    GetCursorPos(&m->pt);
}

/* The next window to paint, parents before children; its frame is
 * painted first. */
static HWND next_paint(void)
{
    int i;

    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *w = wnd_get(windows[i]);
        if (w && w->dirty && wnd_visible(w)) {
            if (w->erase)
                SendMessage(w->hwnd, WM_NCPAINT, 0, 0);
            return w->hwnd;
        }
    }
    return 0;
}

/* The next message in Windows' order: posted (and input), quit, paint,
 * timer. */
static int next_message(MSG *m, int remove)
{
    uint32_t now = platform_time_ms();
    HWND paint;
    int i;

    if (q_count) {
        *m = queue[q_head];
        if (remove) {
            q_head = (q_head + 1) % QUEUE_LEN;
            q_count--;
        }
        return 1;
    }
    if (quit_posted) {
        make_msg(m, 0, WM_QUIT, (WPARAM)quit_code, 0);
        if (remove)
            quit_posted = 0;
        return 1;
    }
    if ((paint = next_paint()) != 0) {
        make_msg(m, paint, WM_PAINT, 0, 0);
        return 1;
    }
    for (i = 0; i < MAX_TIMERS; i++) {
        if (timers[i].ms && (int32_t)(now - timers[i].due) >= 0) {
            make_msg(m, timers[i].hwnd, WM_TIMER, (WPARAM)timers[i].id, 0);
            if (remove)
                timers[i].due = now + timers[i].ms;
            return 1;
        }
    }
    return 0;
}

/* Time and waiting.  The game polls with PeekMessage and does a step of
 * its frame whenever no message is waiting (2:0000).  On a 1994 machine
 * that idle loop ran as fast as the processor allowed; the game measures
 * its rate (Calibrate, 15:5e22), counts frame steps in idle calls and
 * times its frames with timeGetTime (NOTES-port.md "Game speed").  The
 * port answers "no message" once a millisecond, as one fixed machine
 * (Calibrate about 2300, the help file's "very fast" class) whatever the
 * host's speed: at the start of each millisecond of the clock the game
 * reads, sleeping in between, so a frame's time read is the millisecond
 * it is due.  Calls owed after a long step are made at once, at most
 * IDLE_BURST of them.  Whenever the game waits, what it drew is shown. */
#define MS 1000000u                 /* platform_time_ns() per millisecond */
#define IDLE_BURST 50

static int clock_reads;             /* since the last message call */

static void wait_next_ms(void)
{
    platform_sleep_until((platform_time_ns() / MS + 1) * MS);
}

static void pace_idle(void)
{
    static uint64_t next;           /* when the next idle call is due */
    uint64_t now = platform_time_ns();

    video_show();
    if (now > next + IDLE_BURST * MS)
        next = (now / MS - IDLE_BURST) * MS;
    platform_sleep_until(next);
    next += MS;
}

/* The game also waits by reading the clock in a loop (2:0d78's 450 ms
 * before the exit question, the title logo's 40 ms steps in 15:7cda,
 * ...), drawing in between.  A step of the game reads it a few times,
 * such a loop millions of times a second: after CLOCK_POLLS reads
 * without a message call, a read that finds the same millisecond as the
 * one before shows what was drawn and sleeps until the next. */
#define CLOCK_POLLS 1000

static uint32_t clock_read(void)
{
    static uint32_t last;
    uint32_t now = platform_time_ms();

    if (clock_reads < CLOCK_POLLS)
        clock_reads++;
    else if (now == last) {
        video_show();
        wait_next_ms();
        now = platform_time_ms();
    }
    return last = now;
}

DWORD GetCurrentTime(void)
{
    return clock_read();
}

DWORD timeGetTime(void)
{
    return clock_read();
}

BOOL PeekMessage(MSG *m, HWND h, UINT lo, UINT hi, UINT flags)
{
    (void)h;
    (void)lo;
    (void)hi;
    clock_reads = 0;
    win_pump();
    if (next_message(m, flags & PM_REMOVE))
        return 1;
    pace_idle();
    return 0;
}

BOOL GetMessage(MSG *m, HWND h, UINT lo, UINT hi)
{
    (void)h;
    (void)lo;
    (void)hi;
    clock_reads = 0;
    for (;;) {
        win_pump();
        if (next_message(m, 1))
            return m->message != WM_QUIT;
        video_show();
        wait_next_ms();
    }
}

LONG DispatchMessage(const MSG *m)
{
    if (m->message == WM_TIMER && m->lParam) {
        int i;
        for (i = 0; i < MAX_TIMERS; i++)
            if (timers[i].ms && timers[i].hwnd == m->hwnd && timers[i].id == m->wParam && timers[i].proc)
                timers[i].proc(m->hwnd, WM_TIMER, m->wParam, m->time);
        return 0;
    }
    return SendMessage(m->hwnd, m->message, m->wParam, m->lParam);
}

UINT SetTimer(HWND h, UINT id, UINT ms, TIMERPROC proc)
{
    static UINT next_id = 100;
    int i, free_slot = -1;

    for (i = 0; i < MAX_TIMERS; i++) {
        if (timers[i].ms && h && timers[i].hwnd == h && timers[i].id == id)
            free_slot = i;
        else if (!timers[i].ms && free_slot < 0)
            free_slot = i;
    }
    if (free_slot < 0)
        return 0;
    timers[free_slot].hwnd = h;
    timers[free_slot].id = h ? id : next_id++;
    timers[free_slot].ms = ms ? ms : 1;
    timers[free_slot].due = platform_time_ms() + timers[free_slot].ms;
    timers[free_slot].proc = proc;
    return timers[free_slot].id;
}

BOOL KillTimer(HWND h, UINT id)
{
    int i;

    for (i = 0; i < MAX_TIMERS; i++)
        if (timers[i].ms && timers[i].hwnd == h && timers[i].id == id) {
            timers[i].ms = 0;
            return 1;
        }
    return 0;
}

/* Keyboard and mouse messages go to the focus window (else the active
 * one) and to the window under the cursor (or the capture). */
HWND user_key_target(void)
{
    return focus ? focus : active;
}

HCURSOR SetCursor(HCURSOR c)
{
    static HCURSOR current;
    HCURSOR old = current;

    current = c;
    return old;
}

void MessageBeep(UINT type)
{
    (void)type;
    platform_beep();
}

/* Rectangles. */
void SetRect(RECT *r, int16_t l, int16_t t, int16_t rt, int16_t b)
{
    r->left = l;
    r->top = t;
    r->right = rt;
    r->bottom = b;
}

void CopyRect(RECT *d, const RECT *s)
{
    *d = *s;
}

void OffsetRect(RECT *r, int16_t dx, int16_t dy)
{
    r->left += dx;
    r->right += dx;
    r->top += dy;
    r->bottom += dy;
}

void UnionRect(RECT *d, const RECT *a, const RECT *b)
{
    RECT r;

    r.left = a->left < b->left ? a->left : b->left;
    r.top = a->top < b->top ? a->top : b->top;
    r.right = a->right > b->right ? a->right : b->right;
    r.bottom = a->bottom > b->bottom ? a->bottom : b->bottom;
    *d = r;
}

BOOL PtInRect(const RECT *r, POINT p)
{
    return p.x >= r->left && p.x < r->right && p.y >= r->top && p.y < r->bottom;
}

BOOL IntersectRect(RECT *d, const RECT *a, const RECT *b)
{
    d->left = a->left > b->left ? a->left : b->left;
    d->top = a->top > b->top ? a->top : b->top;
    d->right = a->right < b->right ? a->right : b->right;
    d->bottom = a->bottom < b->bottom ? a->bottom : b->bottom;
    if (d->left >= d->right || d->top >= d->bottom) {
        SetRect(d, 0, 0, 0, 0);
        return 0;
    }
    return 1;
}
