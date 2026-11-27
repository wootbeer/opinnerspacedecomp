/* The help viewer, as WINHELP.EXE 3.1 showed a help file kept simple: a
 * top-level window of its own (class MS_WINHELP, another task to the
 * game) with the file's title as caption, a button bar (Contents, Back,
 * << and >>), the topic word-wrapped in a scrolled area and its jumps
 * green and underlined.  Keys: Tab / Shift+Tab pick a jump, Return
 * follows it, arrows / Page Up / Page Down / Home / End scroll, C, B, <
 * and > (Alt too) press the buttons, Backspace or Left goes back, Escape
 * or Alt+F4 closes (port/NOTES-port.md "Help"). */
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "winhelp.h"

#define CLASS "MS_WINHELP"
#define VIEW_X 136
#define VIEW_Y 12
#define VIEW_W 496
#define VIEW_H 456
#define BAR_H 28
#define BUTTON_W 70
#define BUTTON_H 22
#define SCROLL_W 17
#define MARGIN 8
#define LINE_STEP 16
#define TAB_STEP 48
#define HISTORY 40
#define MAX_FACES 64
#define WEIGHT_NORMAL 400
#define WEIGHT_BOLD 700
#define JUMP_COLOR RGB(0, 128, 0)
#define TEXT_BACK RGB(255, 255, 255)
#define SB_LINEUP 0
#define SB_LINEDOWN 1
#define SB_PAGEUP 2
#define SB_PAGEDOWN 3
#define SB_THUMBTRACK 5
#define SB_TOP 6
#define SB_BOTTOM 7
#define SB_ENDSCROLL 8

enum { ID_CONTENTS = 1, ID_BACK, ID_PREV, ID_NEXT, ID_SCROLL = 100 };

static const struct {
    const char *label;
    char key;
} buttons[] = {{"&Contents", 'c'}, {"&Back", 'b'}, {"<<", '<'}, {">>", '>'}};

/* Windows 3.1's [FontSubstitutes] for the old raster names. */
static const struct {
    const char *old, *now;
} substitutes[] = {{"Helv", "MS Sans Serif"}, {"Tms Rmn", "Times New Roman"}};

typedef struct {
    HFONT font;
    int ascent, descent, underline;
    COLORREF color;
} Face;

/* A word or part of one, placed: y is its top, w its ink and adv its
 * width with the spaces after it. */
typedef struct {
    int x, y, w, adv, h;
    int face, hot;
    const char *s;
    int n;
} Run;

typedef struct {
    int topic;                  /* -1: a hotspot the viewer cannot follow */
    int first, end;             /* its runs */
} Hot;

typedef struct {
    Run *runs;
    Hot *hots;
    int nruns, nhots, cap_runs, cap_hots, height;
    /* while laying out */
    HDC dc;
    int width, face, x, y, line, new_para, in_hot;
    HlpPara para;
} Layout;

static struct {
    HWND hwnd, scroll;
    char path[260];
    Hlp *hlp;
    Face faces[MAX_FACES];
    int nfaces;
    int topic, top, sel;
    Layout lay;
    struct {
        int topic, top;
    } history[HISTORY];
    int nhistory;
} view;

static const char *substitute(const char *face)
{
    size_t i;

    for (i = 0; i < SDL_arraysize(substitutes); i++)
        if (SDL_strcasecmp(face, substitutes[i].old) == 0)
            return substitutes[i].now;
    return face;
}

static void make_faces(HDC dc)
{
    const HlpFont *f;
    TEXTMETRIC tm;
    Face *face;
    int i;

    view.nfaces = SDL_min(hlp_font_count(view.hlp), MAX_FACES);
    for (i = 0; i < view.nfaces; i++) {
        f = hlp_font(view.hlp, i);
        face = &view.faces[i];
        face->font = CreateFont((int16_t)-SDL_max(f->height, 6), 0, 0, 0, f->bold ? WEIGHT_BOLD : WEIGHT_NORMAL,
                                (BYTE)f->italic, 0, 0, 0, 0, 0, 0, 0, substitute(f->face));
        SelectObject(dc, face->font);
        GetTextMetrics(dc, &tm);
        face->ascent = tm.tmAscent;
        face->descent = tm.tmHeight - tm.tmAscent;
        face->underline = f->underline;
        face->color = f->color;
    }
    if (view.nfaces)
        return;
    view.faces[0].font = wnd_system_font();     /* a file without |FONT */
    SelectObject(dc, view.faces[0].font);
    GetTextMetrics(dc, &tm);
    view.faces[0].ascent = tm.tmAscent;
    view.faces[0].descent = tm.tmHeight - tm.tmAscent;
    view.nfaces = 1;
}

static void free_faces(void)
{
    int i;

    for (i = 0; i < view.nfaces; i++)
        if (view.faces[i].font != wnd_system_font())
            DeleteObject(view.faces[i].font);
    view.nfaces = 0;
}

/* Layout: the topic's items placed in lines of the area's width. */
static const Face *lay_face(const Layout *L)
{
    return &view.faces[L->face];
}

static void flush_line(Layout *L)
{
    const Face *cur = lay_face(L);
    int ascent = 0, descent = 0, end = 0, shift, i;

    if (L->new_para)
        L->y += L->para.above;
    L->new_para = 0;
    for (i = L->line; i < L->nruns; i++) {
        ascent = SDL_max(ascent, view.faces[L->runs[i].face].ascent);
        descent = SDL_max(descent, view.faces[L->runs[i].face].descent);
        end = L->runs[i].x + L->runs[i].w;
    }
    if (L->line == L->nruns) {
        ascent = cur->ascent;
        descent = cur->descent;
    }
    shift = L->width - L->para.right - end;
    shift = L->para.align == HLP_RIGHT ? shift : L->para.align == HLP_CENTER ? shift / 2 : 0;
    for (i = L->line; i < L->nruns; i++) {
        L->runs[i].x += SDL_max(shift, 0);
        L->runs[i].y = L->y + ascent - view.faces[L->runs[i].face].ascent;
    }
    L->y += ascent + descent;
    L->line = L->nruns;
    L->x = L->para.left;
}

/* Room in *array (of *cap items) for item n. */
static int grow(void *array, int *cap, int n, size_t size)
{
    void **at = array, *grown;
    int want = SDL_max(*cap * 2, 64);

    if (n < *cap)
        return 1;
    if (!(grown = realloc(*at, (size_t)want * size)))
        return 0;
    *at = grown;
    *cap = want;
    return 1;
}

static int text_width(HDC dc, const char *s, int n)
{
    return n ? LOWORD(GetTextExtent(dc, s, (int16_t)n)) : 0;
}

static void place_text(Layout *L, const char *s, int n)
{
    int k, ink, w, adv;
    Run *r;

    while (n > 0) {
        for (ink = 0; ink < n && (s[ink] != ' ' || ink == 0); ink++)
            ;
        for (k = ink; k < n && s[k] == ' '; k++)
            ;
        w = text_width(L->dc, s, ink);
        adv = text_width(L->dc, s, k);
        if (L->x + w > L->width - L->para.right && L->nruns > L->line)
            flush_line(L);
        if (!grow(&L->runs, &L->cap_runs, L->nruns, sizeof *L->runs))
            return;
        r = &L->runs[L->nruns++];
        *r = (Run){L->x, L->y, w, adv, lay_face(L)->ascent + lay_face(L)->descent, L->face,
                   L->in_hot ? L->nhots - 1 : -1, s, ink};
        L->x += adv;
        s += k;
        n -= k;
    }
}

static void tab(Layout *L)
{
    int i;

    for (i = 0; i < L->para.ntabs; i++)
        if (L->para.tabs[i] > L->x) {
            L->x = L->para.tabs[i];
            return;
        }
    L->x = (L->x / TAB_STEP + 1) * TAB_STEP;
}

static void begin_hot(Layout *L, int topic)
{
    if (L->in_hot || !grow(&L->hots, &L->cap_hots, L->nhots, sizeof *L->hots))
        return;
    L->hots[L->nhots++] = (Hot){topic, L->nruns, L->nruns};
    L->in_hot = 1;
}

static void lay_item(void *ctx, const HlpItem *it)
{
    Layout *L = ctx;

    switch (it->kind) {
    case HLP_PARA:
        L->para = *it->para;
        if (L->line == L->nruns)
            L->x = L->para.left + L->para.first;
        break;
    case HLP_TEXT:
        place_text(L, it->s, it->n);
        break;
    case HLP_FONT:
        L->face = it->value >= 0 && it->value < view.nfaces ? it->value : 0;
        SelectObject(L->dc, view.faces[L->face].font);
        break;
    case HLP_LINE:
        flush_line(L);
        break;
    case HLP_END_PARA:
        flush_line(L);
        L->y += L->para.below;
        L->new_para = 1;
        L->x = L->para.left + L->para.first;
        break;
    case HLP_TAB:
        tab(L);
        break;
    case HLP_LINK:
        begin_hot(L, it->value);
        break;
    case HLP_LINK_END:
        if (L->in_hot)
            L->hots[L->nhots - 1].end = L->nruns;
        L->in_hot = 0;
        break;
    }
}

static void text_area(RECT *r)
{
    GetClientRect(view.hwnd, r);
    r->top = BAR_H;
    r->right = (int16_t)(r->right - SCROLL_W);
}

static int page(void)
{
    RECT r;

    text_area(&r);
    return r.bottom - r.top;
}

static int max_top(void)
{
    return SDL_max(0, view.lay.height - page());
}

static void lay_out(void)
{
    Layout *L = &view.lay;
    RECT r;
    HDC dc = GetDC(view.hwnd);

    free(L->runs);
    free(L->hots);
    memset(L, 0, sizeof *L);
    text_area(&r);
    L->dc = dc;
    L->width = r.right - r.left - 2 * MARGIN;
    L->new_para = 1;
    SelectObject(dc, view.faces[0].font);
    hlp_topic_walk(view.hlp, view.topic, lay_item, L);
    if (L->line < L->nruns)
        flush_line(L);
    if (L->in_hot)
        L->hots[L->nhots - 1].end = L->nruns;
    L->height = L->y + 2 * MARGIN;
    L->dc = 0;
    ReleaseDC(view.hwnd, dc);
}

/* Scrolling, the scroll bar and the buttons kept in step. */
static void scroll_to(int top)
{
    RECT r;

    view.top = SDL_clamp(top, 0, max_top());
    SetScrollRange(view.scroll, SB_CTL, 0, (int16_t)SDL_min(max_top(), 0x7fff), 0);
    SetScrollPos(view.scroll, SB_CTL, (int16_t)SDL_min(view.top, 0x7fff), 1);
    text_area(&r);
    InvalidateRect(view.hwnd, &r, 0);
}

static void update_buttons(void)
{
    EnableWindow(GetDlgItem(view.hwnd, ID_BACK), view.nhistory > 0);
    EnableWindow(GetDlgItem(view.hwnd, ID_PREV), hlp_browse(view.hlp, view.topic, 0) >= 0);
    EnableWindow(GetDlgItem(view.hwnd, ID_NEXT), hlp_browse(view.hlp, view.topic, 1) >= 0);
}

static void show_topic(int topic, int top)
{
    view.topic = SDL_clamp(topic, 0, hlp_topic_count(view.hlp) - 1);
    view.sel = -1;
    SDL_Log("help: topic %d \"%s\"", view.topic, hlp_topic_title(view.hlp, view.topic));
    lay_out();
    update_buttons();
    scroll_to(top);
}

static void go(int topic)
{
    if (topic < 0) {
        MessageBeep(0);
        return;
    }
    if (view.nhistory == HISTORY)
        memmove(view.history, view.history + 1, sizeof view.history - sizeof view.history[0]);
    view.history[SDL_min(view.nhistory, HISTORY - 1)].topic = view.topic;
    view.history[SDL_min(view.nhistory, HISTORY - 1)].top = view.top;
    view.nhistory = SDL_min(view.nhistory + 1, HISTORY);
    show_topic(topic, 0);
}

static void back(void)
{
    if (!view.nhistory) {
        MessageBeep(0);
        return;
    }
    view.nhistory--;
    show_topic(view.history[view.nhistory].topic, view.history[view.nhistory].top);
}

static void press(int id)
{
    switch (id) {
    case ID_CONTENTS:
        go(0);
        break;
    case ID_BACK:
        back();
        break;
    case ID_PREV:
    case ID_NEXT:
        go(hlp_browse(view.hlp, view.topic, id == ID_NEXT));
        break;
    }
}

static int hot_empty(int i)
{
    return view.lay.hots[i].first == view.lay.hots[i].end;
}

/* Tab's choice: the next jump (previous with Shift), at first the first
 * one in view, brought into view. */
static void select_hot(int step)
{
    const Layout *L = &view.lay;
    const Run *r;
    int n = L->nhots, start, i, k;

    for (i = 0; i < n && (hot_empty(i) || L->runs[L->hots[i].first].y < view.top); i++)
        ;
    start = view.sel >= 0 ? view.sel + step : step > 0 ? i : i - 1;
    for (k = 0; k < n; k++) {
        i = ((start + k * step) % n + n) % n;
        if (!hot_empty(i))
            break;
    }
    if (k == n)
        return;
    view.sel = i;
    r = &L->runs[L->hots[i].first];
    if (r->y < view.top || r->y + r->h > view.top + page() - 2 * MARGIN)
        scroll_to(r->y - page() / 3);
    else
        scroll_to(view.top);
}

static void follow(int hot)
{
    if (hot >= 0 && hot < view.lay.nhots)
        go(view.lay.hots[hot].topic);
}

static int hot_at(int x, int y)
{
    const Layout *L = &view.lay;
    RECT r;
    int i;

    text_area(&r);
    if (y < r.top)
        return -1;
    x -= r.left + MARGIN;
    y -= r.top + MARGIN - view.top;
    for (i = 0; i < L->nruns; i++)
        if (x >= L->runs[i].x && x < L->runs[i].x + L->runs[i].adv && y >= L->runs[i].y &&
            y < L->runs[i].y + L->runs[i].h)
            return L->runs[i].hot;
    return -1;
}

static void key(WPARAM vk)
{
    int shift = GetKeyState(VK_SHIFT) < 0;

    switch (vk) {
    case VK_UP:
    case VK_DOWN:
        scroll_to(view.top + (vk == VK_UP ? -LINE_STEP : LINE_STEP));
        break;
    case VK_PRIOR:
    case VK_NEXT:
        scroll_to(view.top + (vk == VK_PRIOR ? -1 : 1) * (page() - LINE_STEP));
        break;
    case VK_HOME:
    case VK_END:
        scroll_to(vk == VK_HOME ? 0 : max_top());
        break;
    case VK_TAB:
        select_hot(shift ? -1 : 1);
        break;
    case VK_RETURN:
        follow(view.sel);
        break;
    case VK_BACK:
    case VK_LEFT:
        back();
        break;
    case VK_ESCAPE:
        DestroyWindow(view.hwnd);
        break;
    }
}

/* C, B, < and >: 1 when the character was a button's. */
static int mnemonic(WPARAM c)
{
    size_t i;

    for (i = 0; i < SDL_arraysize(buttons); i++)
        if (SDL_tolower((int)c) == buttons[i].key && IsWindowEnabled(GetDlgItem(view.hwnd, (int16_t)(ID_CONTENTS + i)))) {
            press(ID_CONTENTS + (int)i);
            return 1;
        }
    return 0;
}

static void on_scroll(WPARAM code, LPARAM lp)
{
    static const int steps[] = {-LINE_STEP, LINE_STEP, -1, 1};

    switch (code) {
    case SB_LINEUP:
    case SB_LINEDOWN:
        scroll_to(view.top + steps[code]);
        break;
    case SB_PAGEUP:
    case SB_PAGEDOWN:
        scroll_to(view.top + steps[code] * (page() - LINE_STEP));
        break;
    case SB_THUMBTRACK:
        scroll_to(LOWORD(lp));
        break;
    case SB_TOP:
    case SB_BOTTOM:
        scroll_to(code == SB_TOP ? 0 : max_top());
        break;
    case SB_ENDSCROLL:
        SetFocus(view.hwnd);
        break;
    }
}

static void paint_run(HDC dc, const Run *r, int x0, int y0)
{
    const Face *f = &view.faces[r->face];
    const Hot *hot = r->hot >= 0 ? &view.lay.hots[r->hot] : NULL;
    int x = x0 + r->x, y = y0 + r->y, last = hot && hot->end - 1 == (int)(r - view.lay.runs);
    int w = hot && !last ? r->adv : r->w, base = y + f->ascent + 1;

    if (r->hot >= 0 && r->hot == view.sel)
        ctl_fill(dc, x, y, x + w, y + r->h, JUMP_COLOR);
    SelectObject(dc, f->font);
    SetTextColor(dc, r->hot < 0 ? f->color : r->hot == view.sel ? TEXT_BACK : JUMP_COLOR);
    TextOut(dc, (int16_t)x, (int16_t)y, r->s, (int16_t)r->n);
    if (hot || f->underline)
        ctl_fill(dc, x, base, x + w, base + 1, hot ? JUMP_COLOR : f->color);
}

static void paint(HDC dc)
{
    RECT client, area;
    HRGN clip;
    int i, x0, y0;

    GetClientRect(view.hwnd, &client);
    text_area(&area);
    ctl_fill(dc, 0, 0, client.right, BAR_H - 1, GetSysColor(COLOR_BTNFACE));
    ctl_fill(dc, 0, BAR_H - 1, client.right, BAR_H, RGB(0, 0, 0));
    clip = CreateRectRgn(area.left, area.top, area.right, area.bottom);
    SelectClipRgn(dc, clip);
    ctl_fill(dc, area.left, area.top, area.right, area.bottom, TEXT_BACK);
    SetBkMode(dc, TRANSPARENT);
    x0 = area.left + MARGIN;
    y0 = area.top + MARGIN - view.top;
    for (i = 0; i < view.lay.nruns; i++)
        if (y0 + view.lay.runs[i].y < area.bottom && y0 + view.lay.runs[i].y + view.lay.runs[i].h > area.top)
            paint_run(dc, &view.lay.runs[i], x0, y0);
    SelectClipRgn(dc, 0);
    DeleteObject(clip);
}

static void create_children(HWND h)
{
    RECT r;
    size_t i;
    HDC dc = GetDC(h);

    make_faces(dc);
    ReleaseDC(h, dc);
    for (i = 0; i < SDL_arraysize(buttons); i++)
        SendMessage(CreateWindow("Button", buttons[i].label, WS_CHILD | WS_VISIBLE, (int16_t)(4 + i * (BUTTON_W + 4)),
                                 (BAR_H - 1 - BUTTON_H) / 2, BUTTON_W, BUTTON_H, h,
                                 (HMENU)(uintptr_t)(ID_CONTENTS + i), WINHELP_INSTANCE, NULL),
                    WM_SETFONT, wnd_system_font(), 0);
    GetClientRect(h, &r);
    view.scroll = CreateWindow("ScrollBar", "", WS_CHILD | WS_VISIBLE | SBS_VERT, (int16_t)(r.right - SCROLL_W), BAR_H,
                               SCROLL_W, (int16_t)(r.bottom - BAR_H), h, (HMENU)ID_SCROLL, WINHELP_INSTANCE, NULL);
}

/* WINHELP.EXE was a task of its own that painted whatever the game's
 * message loop was doing; in the port's one loop the game's windows can
 * keep taking WM_PAINT first, so the viewer paints at once. */
static void paint_now(void)
{
    HWND c;

    UpdateWindow(view.hwnd);
    for (c = view.hwnd ? GetWindow(view.hwnd, GW_CHILD) : 0; c; c = GetWindow(c, GW_HWNDNEXT))
        UpdateWindow(c);
}

static LRESULT help_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    PAINTSTRUCT ps;

    switch (msg) {
    case WM_CREATE:
        view.hwnd = h;
        create_children(h);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT:
        BeginPaint(h, &ps);
        paint(ps.hdc);
        EndPaint(h, &ps);
        return 0;
    case WM_COMMAND:
        if (wp != ID_SCROLL)
            press((int)wp);
        SetFocus(h);
        paint_now();
        return 0;
    case WM_VSCROLL:
        on_scroll(wp, lp);
        paint_now();
        return 0;
    case WM_KEYDOWN:
        key(wp);
        paint_now();
        return 0;
    case WM_CHAR:
        mnemonic(wp);
        paint_now();
        return 0;
    case WM_SYSCHAR:
        if (!(lp & KF_ALT && mnemonic(wp)))
            return DefWindowProc(h, msg, wp, lp);
        paint_now();
        return 0;
    case WM_LBUTTONDOWN:
        SetFocus(h);
        follow(hot_at((int16_t)LOWORD(lp), (int16_t)HIWORD(lp)));
        paint_now();
        return 0;
    case WM_DESTROY:
        free(view.lay.runs);
        free(view.lay.hots);
        free_faces();
        hlp_close(view.hlp);
        memset(&view, 0, sizeof view);
        return 0;
    }
    return DefWindowProc(h, msg, wp, lp);
}

static int register_class(void)
{
    static int done;
    WNDCLASS wc;

    if (done)
        return 1;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = help_proc;
    wc.hInstance = WINHELP_INSTANCE;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.lpszClassName = CLASS;
    done = RegisterClass(&wc) != 0;
    return done;
}

static int open_file(const char *dos_path)
{
    char host[512];
    Hlp *h;
    int status;

    if (view.hwnd && SDL_strcasecmp(view.path, dos_path) == 0)
        return HLP_OK;
    if (!dos_to_host(dos_path, host, sizeof host))
        return HLP_MISSING;
    if ((status = hlp_open(host, &h)) != HLP_OK)
        return status;
    winhelp_quit();
    if (!register_class()) {
        hlp_close(h);
        return HLP_UNSUPPORTED;
    }
    view.hlp = h;
    SDL_strlcpy(view.path, dos_path, sizeof view.path);
    if (!CreateWindow(CLASS, hlp_title(h), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, VIEW_X, VIEW_Y, VIEW_W, VIEW_H, 0, 0,
                      WINHELP_INSTANCE, NULL)) {
        hlp_close(view.hlp);
        memset(&view, 0, sizeof view);
        return HLP_UNSUPPORTED;
    }
    return HLP_OK;
}

int winhelp_open(const char *dos_path, UINT cmd, DWORD data)
{
    int fresh = !view.hwnd || SDL_strcasecmp(view.path, dos_path) != 0, status = open_file(dos_path), topic;

    if (status != HLP_OK)
        return status;
    topic = cmd == HELP_CONTEXT ? hlp_topic_of_context(view.hlp, data) : 0;
    if (topic < 0)
        SDL_Log("help: no topic for context %lu", (unsigned long)data);
    if (fresh)
        show_topic(SDL_max(topic, 0), 0);
    else
        go(SDL_max(topic, 0));
    ShowWindow(view.hwnd, SW_SHOWNORMAL);
    SetWindowPos(view.hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetActiveWindow(view.hwnd);
    SetFocus(view.hwnd);
    paint_now();
    return HLP_OK;
}

void winhelp_quit(void)
{
    if (view.hwnd)
        DestroyWindow(view.hwnd);
}
