/* USER: window classes, windows, focus, painting, the message queue and
 * timers.  Every window draws straight into the screen; top-level windows
 * are stacked in the order they were made, and window DCs do not draw
 * where a later popup lies (wnd_occluders). */
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <string.h>

#include "user.h"
#include "platform/platform.h"

#define MAX_CLASSES 24
#define MAX_WINDOWS 128
#define MAX_TIMERS 16
#define QUEUE_LEN 256
#define SCREEN_W 640
#define SCREEN_H 480
#define CAPTION_H 19        /* SM_CYCAPTION less the line it shares with the frame */
#define DLGFRAME 4

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

static int wnd_visible(const Wnd *w)
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

    if ((dialog && style & DS_MODALFRAME) || (style & WS_CAPTION) == WS_DLGFRAME)
        b = DLGFRAME;
    else if (style & WS_BORDER)
        b = 1;
    if ((style & WS_CAPTION) == WS_CAPTION)
        top = CAPTION_H;
    SetRect(client, (int16_t)(rect->left + b), (int16_t)(rect->top + b + top),
            (int16_t)(rect->right - b), (int16_t)(rect->bottom - b));
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

/* Marks what lies under r (screen) for repainting, as Windows does when
 * a window above goes away or moves. */
static void uncover(const RECT *r)
{
    int i;

    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *w = wnd_get(windows[i]);
        if (w && wnd_visible(w))
            invalidate(w, r, 1);
    }
}

/* Places w at (x, y) (relative to its parent's client area for a child)
 * with size cx x cy, moving its children along.  Returns 0 when nothing
 * changed. */
static int place(Wnd *w, int x, int y, int cx, int cy)
{
    Wnd *p = wnd_is_child(w) ? wnd_get(w->parent) : NULL;
    RECT old = w->rect;
    int dx, dy;

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
    wnd_frame(w->style, dialog_is(w->hwnd), &w->client, &w->rect);
    zgen++;
    if (wnd_visible(w))
        uncover(&old);
    return 1;
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
    if (w->visible && !wnd_is_child(w))
        uncover(&w->rect);
    zgen++;
    for (i = 0; i < MAX_WINDOWS; i++)
        if (windows[i] && wnd_get(windows[i]) && wnd_get(windows[i])->parent == h)
            DestroyWindow(windows[i]);
    w->proc(h, WM_DESTROY, 0, 0);
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
        invalidate(w, &w->rect, 1);
        if (!active && !wnd_is_child(w))
            SetActiveWindow(h);
    } else if (was) {
        uncover(&w->rect);
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
    (void)h;
    return 0;
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
 * (parent 0) or the children of parent. */
static HWND topmost_at(HWND parent, POINT p)
{
    HWND found = 0;
    int i;

    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *w = wnd_get(windows[i]);
        if (w && w->visible && PtInRect(&w->rect, p) &&
            (parent ? wnd_is_child(w) && w->parent == parent : !wnd_is_child(w)))
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

    if (w)
        PostMessage(w->hwnd, msg, keys, MAKELONG(x - w->client.left, y - w->client.top));
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
    (void)h;
    return 1;
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

/* The frame of a window with a border or caption: Windows 3.1's look
 * (black outline, caption in the active caption colour, centred title). */
static void paint_frame(Wnd *w)
{
    HDC dc = GetWindowDC(w->hwnd);
    int wd = w->rect.right - w->rect.left, ht = w->rect.bottom - w->rect.top;
    int b = w->client.left - w->rect.left, top = w->client.top - w->rect.top;
    HBRUSH frame = CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME));
    HBRUSH caption = CreateSolidBrush(GetSysColor(COLOR_ACTIVECAPTION));
    RECT r;

    SetRect(&r, 0, 0, (int16_t)wd, (int16_t)ht);
    FillRect(dc, &r, caption);
    FrameRect(dc, &r, frame);
    if (b > 1) {
        SetRect(&r, (int16_t)(b - 1), (int16_t)(b - 1), (int16_t)(wd - b + 1), (int16_t)(ht - b + 1));
        FrameRect(dc, &r, frame);
    }
    if (top > b) {
        HFONT font = CreateFont(-12, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, "System");
        HFONT old = SelectObject(dc, font);
        SetRect(&r, (int16_t)(b - 1), (int16_t)(top - 1), (int16_t)(wd - b + 1), (int16_t)top);
        FillRect(dc, &r, frame);
        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, GetSysColor(COLOR_CAPTIONTEXT));
        SetTextAlign(dc, TA_CENTER);
        TextOut(dc, (int16_t)(wd / 2), (int16_t)(b + 2), w->text, (int16_t)SDL_strlen(w->text));
        SelectObject(dc, old);
        DeleteObject(font);
    }
    DeleteObject(frame);
    DeleteObject(caption);
    ReleaseDC(w->hwnd, dc);
}

/* The brush of a system colour, made once. */
static HBRUSH sys_brush(int i)
{
    static HBRUSH made[32];

    if (!made[i & 31])
        made[i & 31] = CreateSolidBrush(GetSysColor((int16_t)i));
    return made[i & 31];
}

LRESULT DefWindowProc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    PAINTSTRUCT ps;
    RECT r;

    (void)lp;
    switch (msg) {
    case WM_NCPAINT:
        if (w && (w->client.left != w->rect.left || w->client.top != w->rect.top))
            paint_frame(w);
        return 0;
    case WM_CTLCOLOR:
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
        if ((wp & 0xfff0) == SC_CLOSE)
            PostMessage(h, WM_CLOSE, 0, 0);
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

BOOL PeekMessage(MSG *m, HWND h, UINT lo, UINT hi, UINT flags)
{
    (void)h;
    (void)lo;
    (void)hi;
    win_pump();
    return (BOOL)next_message(m, flags & PM_REMOVE);
}

BOOL GetMessage(MSG *m, HWND h, UINT lo, UINT hi)
{
    (void)h;
    (void)lo;
    (void)hi;
    for (;;) {
        win_pump();
        if (next_message(m, 1))
            return m->message != WM_QUIT;
        SDL_Delay(1);
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
}

int16_t MessageBox(HWND h, LPCSTR text, LPCSTR title, UINT type)
{
    (void)h;
    SDL_Log("MessageBox [%s] %s", title ? title : "", text ? text : "");
    return (type & 0xf) == MB_YESNO ? IDNO : IDOK;
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
