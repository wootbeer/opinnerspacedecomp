/* The ListBox control in Windows 3.1's look: items with strings, sorted
 * (LBS_SORT) or not, drawn by the control or by the parent
 * (LBS_OWNERDRAWFIXED, WM_DRAWITEM), in one column or in columns
 * (LBS_MULTICOLUMN); scroll bars (WS_VSCROLL, WS_HSCROLL with
 * LB_SETHORIZONTALEXTENT) appear when the items do not fit.  One item
 * is selected at a time (multiple selection is not modelled).  Any
 * change repaints the whole control, each item drawn entire. */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

#define LBS_NOTIFY 0x0001
#define LBS_SORT 0x0002
#define LBS_OWNERDRAWFIXED 0x0010
#define LBS_HASSTRINGS 0x0040
#define LBS_MULTICOLUMN 0x0200
#define WS_HSCROLL 0x00100000L
#define LB_ERR (-1)
#define LB_SETSEL (WM_USER + 6)
#define LB_GETTEXTLEN (WM_USER + 11)
#define LB_GETTOPINDEX (WM_USER + 15)
#define LB_SETHORIZONTALEXTENT (WM_USER + 21)
#define LB_SETCOLUMNWIDTH (WM_USER + 22)
#define LB_SETTOPINDEX (WM_USER + 24)
#define LBN_SETFOCUS 4
#define LBN_KILLFOCUS 5
#define ODT_LISTBOX 2
#define CTLCOLOR_LISTBOX 2
#define BAR 17                  /* SM_CXVSCROLL, SM_CYHSCROLL */
#define HSTEP 8                 /* pixels per horizontal scroll arrow click [uncertain] */

typedef struct {
    char *s;
    DWORD data;
} Item;

typedef struct {
    Item *v;
    int count, cap;
    int sel, top, xoff;         /* top: first item shown; xoff: pixels scrolled sideways */
    int item_h, col_w, extent;
    int redraw, tracking, pressed_sel, dbl;
    HFONT font;
} Lb;

/* What is shown where, from the client size. */
typedef struct {
    int w, h;                   /* item area */
    int rows, vbar, hbar;
} Layout;

static Lb *lb(HWND h)
{
    return wnd_get(h)->data;
}

static DWORD style(HWND h)
{
    return wnd_get(h)->style;
}

static int owner_draw(HWND h)
{
    return (style(h) & LBS_OWNERDRAWFIXED) != 0;
}

static int has_strings(HWND h)
{
    return !owner_draw(h) || (style(h) & LBS_HASSTRINGS);
}

static int multi(HWND h)
{
    return (style(h) & LBS_MULTICOLUMN) != 0;
}

static Layout layout(HWND h)
{
    Lb *l = lb(h);
    Layout o;
    RECT r;
    int pass;

    GetClientRect(h, &r);
    o.vbar = o.hbar = 0;
    for (pass = 0; pass < 2; pass++) {
        o.w = r.right - (o.vbar ? BAR : 0);
        o.h = r.bottom - (o.hbar ? BAR : 0);
        o.rows = o.h / l->item_h > 0 ? o.h / l->item_h : 1;
        o.vbar = !multi(h) && (style(h) & WS_VSCROLL) && l->count > o.rows;
        o.hbar = !multi(h) && (style(h) & WS_HSCROLL) && l->extent > r.right - (o.vbar ? BAR : 0);
    }
    o.w = r.right - (o.vbar ? BAR : 0);
    o.h = r.bottom - (o.hbar ? BAR : 0);
    return o;
}

/* Items per page: rows, or rows times whole columns. */
static int page(HWND h, const Layout *o)
{
    int cols = o->w / lb(h)->col_w;

    return multi(h) ? o->rows * (cols > 0 ? cols : 1) : o->rows;
}

static void item_rect(HWND h, const Layout *o, int i, RECT *r)
{
    Lb *l = lb(h);
    int k = i - l->top;

    if (multi(h))
        SetRect(r, (int16_t)(k / o->rows * l->col_w), (int16_t)(k % o->rows * l->item_h),
                (int16_t)((k / o->rows + 1) * l->col_w), (int16_t)((k % o->rows + 1) * l->item_h));
    else
        SetRect(r, (int16_t)-l->xoff, (int16_t)(k * l->item_h),
                (int16_t)((o->w > l->extent ? o->w : l->extent) - l->xoff), (int16_t)((k + 1) * l->item_h));
}

static void changed(HWND h)
{
    if (lb(h)->redraw)
        InvalidateRect(h, NULL, 1);
}

static void notify(HWND h, int code)
{
    if (style(h) & LBS_NOTIFY)
        SendMessage(GetParent(h), WM_COMMAND, (WPARAM)GetDlgCtrlID(h), MAKELONG(h, code));
}

/* Scrolling. */
static void set_top(HWND h, int top)
{
    Lb *l = lb(h);
    Layout o = layout(h);
    int max = l->count - page(h, &o);

    if (multi(h) && top % o.rows)
        top -= top % o.rows;
    if (top > max)
        top = multi(h) ? (max + o.rows - 1) / o.rows * o.rows : max;
    if (top < 0)
        top = 0;
    if (top != l->top) {
        l->top = top;
        changed(h);
    }
}

static void set_xoff(HWND h, int x)
{
    Lb *l = lb(h);
    Layout o = layout(h);
    int max = l->extent - o.w;

    if (x > max)
        x = max;
    if (x < 0)
        x = 0;
    if (x != l->xoff) {
        l->xoff = x;
        changed(h);
    }
}

static void show_item(HWND h, int i)
{
    Lb *l = lb(h);
    Layout o = layout(h);
    int n = page(h, &o);

    if (i < 0)
        return;
    if (i < l->top)
        set_top(h, i);
    else if (i >= l->top + n)
        set_top(h, multi(h) ? (i / o.rows + 1) * o.rows - n : i - n + 1);
}

static void select_item(HWND h, int i)
{
    Lb *l = lb(h);

    if (i >= l->count)
        i = l->count - 1;
    if (i < 0)
        i = l->count ? 0 : -1;
    if (i != l->sel) {
        l->sel = i;
        changed(h);
    }
    show_item(h, i);
}

/* Painting. */
static void draw_item(HWND h, HDC dc, const RECT *r, int i, int focus)
{
    Lb *l = lb(h);
    DRAWITEMSTRUCT dis;
    UINT state = (i == l->sel ? ODS_SELECTED : 0) | (focus ? ODS_FOCUS : 0);

    if (owner_draw(h)) {
        dis.CtlType = ODT_LISTBOX;
        dis.CtlID = (UINT)GetDlgCtrlID(h);
        dis.itemID = (UINT)i;
        dis.itemAction = i < 0 ? ODA_FOCUS : ODA_DRAWENTIRE;
        dis.itemState = (UINT)state;
        dis.hwndItem = h;
        dis.hDC = dc;
        dis.rcItem = *r;
        dis.itemData = i < 0 ? 0 : l->v[i].data;
        SendMessage(GetParent(h), WM_DRAWITEM, dis.CtlID, (LPARAM)&dis);
        return;
    }
    if (i < 0) {
        DrawFocusRect(dc, r);
        return;
    }
    ctl_fill(dc, r->left, r->top, r->right, r->bottom, GetSysColor(state & ODS_SELECTED ? COLOR_HIGHLIGHT : COLOR_WINDOW));
    SetTextColor(dc, GetSysColor(state & ODS_SELECTED ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
    SetBkMode(dc, TRANSPARENT);
    TextOut(dc, (int16_t)(r->left + 2), r->top, l->v[i].s, lstrlen(l->v[i].s));
    if (focus)
        DrawFocusRect(dc, r);
}

static void arrow(HDC dc, int l, int t, int dir)
{
    int i;

    for (i = 0; i < 4; i++) {
        int k = dir == 0 || dir == 2 ? 6 + i : 9 - i;
        if (dir < 2)                                    /* 0 up, 1 down */
            ctl_fill(dc, l + 8 - i, t + k, l + 9 + i, t + k + 1, 0);
        else                                            /* 2 left, 3 right */
            ctl_fill(dc, l + k, t + 8 - i, l + k + 1, t + 9 + i, 0);
    }
}

/* A scroll bar along (x, y) of length len: arrows at the ends, the
 * thumb at pos of range. */
static void bar(HDC dc, int x, int y, int len, int vertical, int pos, int range)
{
    int t = BAR + (len - 3 * BAR) * pos / (range > 0 ? range : 1);

    if (vertical) {
        ctl_fill(dc, x, y, x + BAR, y + len, GetSysColor(COLOR_SCROLLBAR));
        ctl_bevel(dc, x, y, x + BAR, y + BAR, 1);
        arrow(dc, x - 1, y, 0);
        ctl_bevel(dc, x, y + len - BAR, x + BAR, y + len, 1);
        arrow(dc, x - 1, y + len - BAR, 1);
        ctl_bevel(dc, x, y + t, x + BAR, y + t + BAR, 1);
    } else {
        ctl_fill(dc, x, y, x + len, y + BAR, GetSysColor(COLOR_SCROLLBAR));
        ctl_bevel(dc, x, y, x + BAR, y + BAR, 1);
        arrow(dc, x, y - 1, 2);
        ctl_bevel(dc, x + len - BAR, y, x + len, y + BAR, 1);
        arrow(dc, x + len - BAR, y - 1, 3);
        ctl_bevel(dc, x + t, y, x + t + BAR, y + BAR, 1);
    }
}

static void paint(HWND h)
{
    Wnd *w = wnd_get(h);
    Lb *l = lb(h);
    Layout o = layout(h);
    HDC dc = GetDC(h);
    HFONT old = l->font ? SelectObject(dc, l->font) : 0;
    HBRUSH bg = (HBRUSH)SendMessage(GetParent(h), WM_CTLCOLOR, dc, MAKELONG(h, CTLCOLOR_LISTBOX));
    int focus = GetFocus() == h, i, n = page(h, &o);
    RECT r;

    w->dirty = w->erase = 0;
    SetRect(&r, 0, 0, (int16_t)o.w, (int16_t)o.h);
    if (bg)
        FillRect(dc, &r, bg);
    else
        ctl_fill(dc, 0, 0, o.w, o.h, GetSysColor(COLOR_WINDOW));
    for (i = l->top; i < l->count && i < l->top + n + (multi(h) ? o.rows : 1); i++) {
        item_rect(h, &o, i, &r);
        draw_item(h, dc, &r, i, focus && i == l->sel);
    }
    if (!l->count && focus) {
        SetRect(&r, 0, 0, (int16_t)o.w, (int16_t)l->item_h);
        draw_item(h, dc, &r, -1, 1);
    }
    if (o.vbar)
        bar(dc, o.w, 0, o.h, 1, l->top, l->count - o.rows);
    if (o.hbar)
        bar(dc, 0, o.h, o.w, 0, l->xoff, l->extent - o.w);
    if (o.vbar && o.hbar)
        ctl_fill(dc, o.w, o.h, o.w + BAR, o.h + BAR, GetSysColor(COLOR_BTNFACE));
    if (old)
        SelectObject(dc, old);
    ReleaseDC(h, dc);
}

/* Items. */
static int insert(HWND h, int at, LPARAM lp)
{
    Lb *l = lb(h);
    Item it;

    if (at < 0 || at > l->count)
        at = l->count;
    if (l->count == l->cap) {
        int cap = l->cap ? l->cap * 2 : 32;
        Item *v = realloc(l->v, (size_t)cap * sizeof *v);
        if (!v)
            return -2;                                  /* LB_ERRSPACE */
        l->v = v;
        l->cap = cap;
    }
    it.s = SDL_strdup(has_strings(h) ? (const char *)lp : "");
    it.data = has_strings(h) ? 0 : (DWORD)lp;
    memmove(&l->v[at + 1], &l->v[at], (size_t)(l->count - at) * sizeof *l->v);
    l->v[at] = it;
    l->count++;
    if (l->sel >= at)
        l->sel++;
    changed(h);
    return at;
}

static int sorted_place(HWND h, const char *s)
{
    Lb *l = lb(h);
    int i = l->count;

    while (i > 0 && SDL_strcasecmp(l->v[i - 1].s, s) > 0)
        i--;
    return i;
}

static int delete_item(HWND h, int i)
{
    Lb *l = lb(h);

    if (i < 0 || i >= l->count)
        return LB_ERR;
    SDL_free(l->v[i].s);
    memmove(&l->v[i], &l->v[i + 1], (size_t)(l->count - i - 1) * sizeof *l->v);
    l->count--;
    if (l->sel == i)
        l->sel = -1;
    else if (l->sel > i)
        l->sel--;
    set_top(h, l->top);
    changed(h);
    return l->count;
}

static void reset(HWND h)
{
    Lb *l = lb(h);

    while (l->count)
        SDL_free(l->v[--l->count].s);
    l->sel = -1;
    l->top = l->xoff = 0;
    changed(h);
}

/* The item after start (from the first when start is -1, wrapping)
 * whose string begins with s, or equals it. */
static int find(HWND h, int start, const char *s, int exact)
{
    Lb *l = lb(h);
    size_t n = SDL_strlen(s);
    int k;

    if (start < -1 || start >= l->count)
        start = -1;
    for (k = 1; k <= l->count; k++) {
        int i = (start + k) % l->count;
        if (exact ? !SDL_strcasecmp(l->v[i].s, s) : !SDL_strncasecmp(l->v[i].s, s, n))
            return i;
    }
    return LB_ERR;
}

/* Input. */
static int item_at(HWND h, int x, int y)
{
    Lb *l = lb(h);
    Layout o = layout(h);
    int i;

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (y >= o.rows * l->item_h)
        y = o.rows * l->item_h - 1;
    i = multi(h) ? l->top + x / l->col_w * o.rows + y / l->item_h : l->top + y / l->item_h;
    return i < l->count ? i : l->count - 1;
}

/* A click on a scroll bar: a line at the arrows, else a page. */
static int bar_click(HWND h, int x, int y)
{
    Lb *l = lb(h);
    Layout o = layout(h);

    if (o.vbar && x >= o.w && y < o.h) {
        int t = BAR + (o.h - 3 * BAR) * l->top / (l->count - o.rows > 0 ? l->count - o.rows : 1);
        set_top(h, y < BAR ? l->top - 1 : y >= o.h - BAR ? l->top + 1 : y < t ? l->top - o.rows : l->top + o.rows);
        return 1;
    }
    if (o.hbar && y >= o.h && x < o.w) {
        int range = l->extent - o.w, t = BAR + (o.w - 3 * BAR) * l->xoff / (range > 0 ? range : 1);
        set_xoff(h, x < BAR ? l->xoff - HSTEP : x >= o.w - BAR ? l->xoff + HSTEP
                    : x < t ? l->xoff - o.w : l->xoff + o.w);
        return 1;
    }
    return x >= o.w || y >= o.h;
}

static void key(HWND h, int vk)
{
    Lb *l = lb(h);
    Layout o = layout(h);
    int n = page(h, &o), i = l->sel, side = multi(h) ? o.rows : 1;

    switch (vk) {
    case VK_UP: i--; break;
    case VK_DOWN: i++; break;
    case VK_LEFT: i -= side; break;
    case VK_RIGHT: i += side; break;
    case VK_PRIOR: i -= n > 1 ? n - 1 : 1; break;
    case VK_NEXT: i += n > 1 ? n - 1 : 1; break;
    case VK_HOME: i = 0; break;
    case VK_END: i = l->count - 1; break;
    default: return;
    }
    if (l->sel < 0 && vk != VK_END)
        i = 0;
    i = i < 0 ? 0 : i;
    if (i < l->count && i != l->sel) {
        select_item(h, i);
        notify(h, LBN_SELCHANGE);
    }
}

static void measure(HWND h)
{
    Wnd *w = wnd_get(h);
    Lb *l = lb(h);
    MEASUREITEMSTRUCT mis;
    HDC dc = GetDC(h);
    TEXTMETRIC tm;

    if (l->font)
        SelectObject(dc, l->font);
    GetTextMetrics(dc, &tm);
    ReleaseDC(h, dc);
    l->item_h = tm.tmHeight;
    l->col_w = 16 * tm.tmAveCharWidth;   /* [uncertain] Windows' default column width */
    if (!owner_draw(h))
        return;
    mis.CtlType = ODT_LISTBOX;
    mis.CtlID = (UINT)GetDlgCtrlID(h);
    mis.itemID = 0;
    mis.itemWidth = (UINT)(w->client.right - w->client.left);
    mis.itemHeight = (UINT)l->item_h;
    mis.itemData = 0;
    SendMessage(GetParent(h), WM_MEASUREITEM, mis.CtlID, (LPARAM)&mis);
    l->item_h = mis.itemHeight > 0 ? mis.itemHeight : 1;
}

LRESULT listbox_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    Lb *l = w->data;
    int i;

    if (!l) {
        l = w->data = calloc(1, sizeof *l);
        if (!l)
            return DefWindowProc(h, msg, wp, lp);
        l->sel = -1;
        l->redraw = 1;
        l->item_h = 16;
        l->col_w = 64;
    }
    switch (msg) {
    case WM_CREATE:
        measure(h);
        return 0;
    case WM_DESTROY:
        reset(h);
        free(l->v);
        l->v = NULL;
        return 0;
    case WM_PAINT:
        paint(h);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_SETFONT:
        l->font = wp;
        if (!owner_draw(h))
            measure(h);
        if (lp)
            changed(h);
        return 0;
    case 0x0031:                                        /* WM_GETFONT */
        return l->font;
    case WM_SIZE:
        set_top(h, l->top);
        set_xoff(h, l->xoff);
        changed(h);
        return 0;
    case WM_SETREDRAW:
        l->redraw = wp != 0;
        changed(h);
        return 0;
    case WM_SETFOCUS:
    case WM_KILLFOCUS:
        changed(h);
        notify(h, msg == WM_SETFOCUS ? LBN_SETFOCUS : LBN_KILLFOCUS);
        return 0;
    case WM_ENABLE:
        changed(h);
        return 0;
    case WM_GETDLGCODE:
        return DLGC_WANTARROWS | DLGC_WANTCHARS;
    case WM_KEYDOWN:
        key(h, wp);
        return 0;
    case WM_CHAR:
        i = find(h, l->sel, (char[2]){(char)wp, 0}, 0);
        if (i >= 0 && i != l->sel) {
            select_item(h, i);
            notify(h, LBN_SELCHANGE);
        }
        return 0;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        SetFocus(h);
        if (bar_click(h, (int16_t)LOWORD(lp), (int16_t)HIWORD(lp)))
            return 0;
        l->tracking = 1;
        l->dbl = msg == WM_LBUTTONDBLCLK;
        l->pressed_sel = l->sel;
        SetCapture(h);
        select_item(h, item_at(h, (int16_t)LOWORD(lp), (int16_t)HIWORD(lp)));
        return 0;
    case WM_MOUSEMOVE:
        if (l->tracking)
            select_item(h, item_at(h, (int16_t)LOWORD(lp), (int16_t)HIWORD(lp)));
        return 0;
    case WM_LBUTTONUP:
        if (!l->tracking)
            return 0;
        l->tracking = 0;
        ReleaseCapture();
        if (l->sel != l->pressed_sel)
            notify(h, LBN_SELCHANGE);
        if (l->dbl && l->sel >= 0)
            notify(h, LBN_DBLCLK);
        return 0;
    case LB_ADDSTRING:
        return insert(h, style(h) & LBS_SORT && has_strings(h) ? sorted_place(h, (const char *)lp) : -1, lp);
    case LB_INSERTSTRING:
        return insert(h, (int16_t)wp, lp);
    case LB_DELETESTRING:
        return delete_item(h, (int16_t)wp);
    case LB_RESETCONTENT:
        reset(h);
        return 0;
    case LB_SETCURSEL:
        i = (int16_t)wp;
        if (i < 0 || i >= l->count) {
            l->sel = -1;
            changed(h);
            return LB_ERR;
        }
        select_item(h, i);
        return i;
    case LB_GETCURSEL:
        return l->sel;
    case LB_GETTEXT:
        i = (int16_t)wp;
        if (i < 0 || i >= l->count)
            return LB_ERR;
        if (!has_strings(h)) {
            memcpy((void *)lp, &l->v[i].data, sizeof l->v[i].data);
            return sizeof l->v[i].data;
        }
        strcpy((char *)lp, l->v[i].s);
        return lstrlen(l->v[i].s);
    case LB_GETTEXTLEN:
        i = (int16_t)wp;
        return i < 0 || i >= l->count ? LB_ERR : has_strings(h) ? lstrlen(l->v[i].s) : 4;
    case LB_GETCOUNT:
        return l->count;
    case LB_FINDSTRING:
    case LB_FINDSTRINGEXACT:
        return find(h, (int16_t)wp, (const char *)lp, msg == LB_FINDSTRINGEXACT);
    case LB_SELECTSTRING:
        i = find(h, (int16_t)wp, (const char *)lp, 0);
        if (i >= 0)
            select_item(h, i);
        return i;
    case LB_GETTOPINDEX:
        return l->top;
    case LB_SETTOPINDEX:
        set_top(h, (int16_t)wp);
        return 0;
    case LB_SETHORIZONTALEXTENT:
        l->extent = (int16_t)wp;
        set_xoff(h, l->xoff);
        changed(h);
        return 0;
    case LB_SETCOLUMNWIDTH:
        l->col_w = (int16_t)wp > 0 ? (int16_t)wp : 1;
        changed(h);
        return 0;
    case LB_SETSEL:
        return LB_ERR;
    }
    return DefWindowProc(h, msg, wp, lp);
}
