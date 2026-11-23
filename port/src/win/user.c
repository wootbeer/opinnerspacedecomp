/* USER: window classes, windows, the message queue, timers and input.
 * Every window draws straight into the screen; its client area is the
 * whole window rectangle. */
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <string.h>

#include "winrt.h"
#include "platform/platform.h"
#include "video.h"

#define MAX_CLASSES 16
#define MAX_WINDOWS 64
#define MAX_TIMERS 16
#define QUEUE_LEN 256
#define SCREEN_W 640
#define SCREEN_H 480
#define FRAME_MS 16

static struct {
    char name[32];
    WNDCLASS wc;
} classes[MAX_CLASSES];
static int class_count;

static HWND windows[MAX_WINDOWS];
static HWND active, focus;

static struct {
    HWND hwnd;
    UINT id, ms;
    uint32_t due;
    TIMERPROC proc;
    int pending;
} timers[MAX_TIMERS];

static MSG queue[QUEUE_LEN];
static int q_head, q_count;
static int quit_posted, quit_code;

static BYTE keys[256];
static POINT cursor;
static uint32_t last_frame;

Wnd *wnd_get(HWND h)
{
    return handle_get(h, H_WND);
}

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

HWND CreateWindow(LPCSTR cls, LPCSTR title, DWORD style, int16_t x, int16_t y, int16_t w, int16_t h,
                  HWND parent, HMENU menu, HINSTANCE inst, void *param)
{
    const WNDCLASS *wc = find_class(cls);
    Wnd *wnd;
    int i;

    (void)inst;
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
    SetRect(&wnd->rect, x, y, x + w, y + h);
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
    if (wnd->proc(wnd->hwnd, WM_CREATE, 0, 0) == -1) {
        DestroyWindow(wnd->hwnd);
        return 0;
    }
    if (wnd_get(wnd->hwnd)) {
        wnd->proc(wnd->hwnd, WM_SIZE, 0, MAKELONG(w, h));
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
    handle_free(h);
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
    if (w->visible) {
        w->dirty = 1;
        if (!active)
            active = focus = h;
    }
    return (BOOL)was;
}

void UpdateWindow(HWND h)
{
    Wnd *w = wnd_get(h);

    if (w && w->visible && w->dirty)
        SendMessage(h, WM_PAINT, 0, 0);
}

void InvalidateRect(HWND h, const RECT *r, BOOL erase)
{
    Wnd *w = wnd_get(h);

    (void)r;
    (void)erase;
    if (w)
        w->dirty = 1;
}

BOOL IsIconic(HWND h)
{
    (void)h;
    return 0;
}

BOOL IsWindowEnabled(HWND h)
{
    return wnd_get(h) != NULL;
}

BOOL EnableWindow(HWND h, BOOL on)
{
    (void)h;
    (void)on;
    return 0;
}

HWND GetActiveWindow(void)
{
    return active;
}

HWND SetActiveWindow(HWND h)
{
    HWND old = active;

    if (wnd_get(h))
        active = h;
    return old;
}

HWND GetFocus(void)
{
    return focus;
}

HWND SetFocus(HWND h)
{
    HWND old = focus;

    focus = h;
    return old;
}

void GetClientRect(HWND h, RECT *r)
{
    Wnd *w = wnd_get(h);

    if (w)
        SetRect(r, 0, 0, w->rect.right - w->rect.left, w->rect.bottom - w->rect.top);
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
        p->x += w->rect.left;
        p->y += w->rect.top;
    }
}

BOOL MoveWindow(HWND h, int16_t x, int16_t y, int16_t cx, int16_t cy, BOOL repaint)
{
    Wnd *w = wnd_get(h);

    if (!w)
        return 0;
    SetRect(&w->rect, x, y, x + cx, y + cy);
    w->proc(h, WM_SIZE, 0, MAKELONG(cx, cy));
    w->proc(h, WM_MOVE, 0, MAKELONG(x, y));
    if (repaint)
        w->dirty = 1;
    return 1;
}

BOOL SetWindowPos(HWND h, HWND after, int16_t x, int16_t y, int16_t cx, int16_t cy, UINT flags)
{
    Wnd *w = wnd_get(h);

    (void)after;
    if (!w)
        return 0;
    if (!(flags & SWP_NOMOVE))
        SetRect(&w->rect, x, y, x + w->rect.right - w->rect.left, y + w->rect.bottom - w->rect.top);
    if (!(flags & SWP_NOSIZE)) {
        w->rect.right = w->rect.left + cx;
        w->rect.bottom = w->rect.top + cy;
    }
    return 1;
}

void SetWindowText(HWND h, LPCSTR s)
{
    Wnd *w = wnd_get(h);

    if (w)
        SDL_strlcpy(w->text, s, sizeof w->text);
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
HDC BeginPaint(HWND h, PAINTSTRUCT *ps)
{
    Wnd *w = wnd_get(h);

    memset(ps, 0, sizeof *ps);
    if (!w)
        return 0;
    w->dirty = 0;
    ps->hdc = GetDC(h);
    GetClientRect(h, &ps->rcPaint);
    return ps->hdc;
}

void EndPaint(HWND h, const PAINTSTRUCT *ps)
{
    ReleaseDC(h, ps->hdc);
}

LRESULT DefWindowProc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    PAINTSTRUCT ps;

    (void)lp;
    switch (msg) {
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

    if (q_count == QUEUE_LEN)
        return 0;
    m = &queue[(q_head + q_count++) % QUEUE_LEN];
    m->hwnd = h;
    m->message = msg;
    m->wParam = wp;
    m->lParam = lp;
    m->time = platform_time_ms();
    m->pt = cursor;
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
    m->pt = cursor;
}

/* The next message in Windows' order: posted (and input), quit, paint,
 * timer. */
static int next_message(MSG *m, int remove)
{
    uint32_t now = platform_time_ms();
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
    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *w = wnd_get(windows[i]);
        if (w && w->visible && w->dirty) {
            make_msg(m, w->hwnd, WM_PAINT, 0, 0);
            return 1;
        }
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

BOOL TranslateMessage(const MSG *m)
{
    int c = (int)m->wParam;

    if (m->message != WM_KEYDOWN)
        return 0;
    if (c >= 'A' && c <= 'Z' && !(keys[VK_SHIFT] & 0x80))
        c += 'a' - 'A';
    else if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || c == ' ' || c == 13 || c == 27 || c == 8))
        return 0;
    return PostMessage(m->hwnd, WM_CHAR, (WPARAM)c, m->lParam);
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

/* Input. */
static int vk_of(SDL_Keycode k)
{
    if (k >= 'a' && k <= 'z')
        return (int)(k - 'a' + 'A');
    if ((k >= '0' && k <= '9') || k == ' ')
        return (int)k;
    if (k >= SDLK_F1 && k <= SDLK_F12)
        return 0x70 + (int)(k - SDLK_F1);
    switch (k) {
    case SDLK_ESCAPE: return 0x1b;
    case SDLK_RETURN: return 0x0d;
    case SDLK_BACKSPACE: return 0x08;
    case SDLK_TAB: return 0x09;
    case SDLK_LEFT: return 0x25;
    case SDLK_UP: return 0x26;
    case SDLK_RIGHT: return 0x27;
    case SDLK_DOWN: return 0x28;
    case SDLK_INSERT: return 0x2d;
    case SDLK_DELETE: return 0x2e;
    case SDLK_HOME: return 0x24;
    case SDLK_END: return 0x23;
    case SDLK_PAGEUP: return 0x21;
    case SDLK_PAGEDOWN: return 0x22;
    case SDLK_LSHIFT: case SDLK_RSHIFT: return VK_SHIFT;
    case SDLK_LCTRL: case SDLK_RCTRL: return VK_CONTROL;
    case SDLK_LALT: case SDLK_RALT: return VK_MENU;
    default: return 0;
    }
}

static HWND window_at(int x, int y)
{
    HWND found = 0;
    int i;

    for (i = 0; i < MAX_WINDOWS; i++) {
        Wnd *w = wnd_get(windows[i]);
        if (w && w->visible && x >= w->rect.left && x < w->rect.right &&
            y >= w->rect.top && y < w->rect.bottom)
            found = w->hwnd;
    }
    return found ? found : active;
}

static void post_mouse(UINT msg, int x, int y)
{
    HWND h = window_at(x, y);
    Wnd *w = wnd_get(h);
    WPARAM wp = 0;

    if (!w)
        return;
    if (keys[VK_LBUTTON] & 0x80)
        wp |= MK_LBUTTON;
    if (keys[VK_RBUTTON] & 0x80)
        wp |= MK_RBUTTON;
    PostMessage(h, msg, wp, MAKELONG(x - w->rect.left, y - w->rect.top));
}

void win_pump(void)
{
    SDL_Event ev;
    uint32_t now;
    int vk, x, y;

    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
        case SDL_EVENT_QUIT:
            if (active)
                PostMessage(active, WM_CLOSE, 0, 0);
            else
                PostQuitMessage(0);
            break;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            vk = vk_of(ev.key.key);
            if (!vk)
                break;
            if (ev.type == SDL_EVENT_KEY_DOWN) {
                if (!(keys[vk] & 0x80))
                    keys[vk] ^= 1;
                keys[vk] |= 0x80;
            } else {
                keys[vk] &= 0x7f;
            }
            if (focus || active)
                PostMessage(focus ? focus : active, ev.type == SDL_EVENT_KEY_DOWN ? WM_KEYDOWN : WM_KEYUP,
                            (WPARAM)vk, ev.key.repeat ? 0x40000001L : 1);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            video_map_point(ev.motion.x, ev.motion.y, &x, &y);
            cursor.x = (int16_t)x;
            cursor.y = (int16_t)y;
            post_mouse(WM_MOUSEMOVE, x, y);
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            vk = ev.button.button == SDL_BUTTON_RIGHT ? VK_RBUTTON : VK_LBUTTON;
            video_map_point(ev.button.x, ev.button.y, &x, &y);
            if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
                keys[vk] |= 0x80;
            else
                keys[vk] &= 0x7f;
            if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
                post_mouse(vk == VK_LBUTTON ? (ev.button.clicks == 2 ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN)
                                            : WM_RBUTTONDOWN, x, y);
            else
                post_mouse(vk == VK_LBUTTON ? WM_LBUTTONUP : WM_RBUTTONUP, x, y);
            break;
        default:
            break;
        }
    }
    now = platform_time_ms();
    if (now - last_frame >= FRAME_MS) {
        last_frame = now;
        app_frame();
    }
}

int16_t GetKeyState(int16_t vk)
{
    return (int16_t)((keys[vk & 0xff] & 0x80 ? 0xff80 : 0) | (keys[vk & 0xff] & 1));
}

int16_t GetAsyncKeyState(int16_t vk)
{
    win_pump();
    return (int16_t)(keys[vk & 0xff] & 0x80 ? 0x8000 : 0);
}

void GetKeyboardState(BYTE *k)
{
    memcpy(k, keys, sizeof keys);
}

void SetKeyboardState(BYTE *k)
{
    memcpy(keys, k, sizeof keys);
}

void GetCursorPos(POINT *p)
{
    *p = cursor;
}

void SetCursorPos(int16_t x, int16_t y)
{
    cursor.x = x;
    cursor.y = y;
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
