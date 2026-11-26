/* The built-in control classes dialogs use: Button (push buttons, check
 * boxes, group boxes), Static (text, icons) and ComboBox (drop-down list,
 * and drop-down with an edit field; Edit is in edit.c), drawn in Windows
 * 3.1's look into the screen.  Colours come from the parent's
 * WM_CTLCOLOR as in Windows; sizes Windows 3.1 derived from its own
 * fonts and bitmaps are approximations (port/NOTES-port.md). */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

#define BS_TYPE 0x0f
#define BS_DEFPUSHBUTTON 1
#define BS_GROUPBOX 7
#define SS_TYPE 0x0f
#define SS_CENTER 1
#define SS_RIGHT 2
#define SS_NOPREFIX 0x80
#define CBS_TYPE 0x0003
#define CBS_DROPDOWN 0x0002
#define CBS_SORT 0x0100
#define ES_AUTOHSCROLL 0x0080
#define CB_GETCOUNT (WM_USER + 6)
#define CB_RESETCONTENT (WM_USER + 11)
#define CB_FINDSTRING (WM_USER + 12)
#define CB_SHOWDROPDOWN (WM_USER + 15)
#define CB_GETDROPPEDSTATE (WM_USER + 23)
#define CBN_EDITCHANGE 5
#define CBN_DROPDOWN 7
#define EN_KILLFOCUS 0x0200
#define EN_CHANGE 0x0300
#define EM_LIMITTEXT (WM_USER + 21)
#define COMBO_EDIT 1001         /* the id of a combo box's edit field, as in Windows */
#define BN_CLICKED 0
#define CTLCOLOR_EDIT 1
#define CTLCOLOR_LISTBOX 2
#define CTLCOLOR_BTN 3
#define CTLCOLOR_STATIC 6
#define ARROW_W 17              /* SM_CXVSCROLL */
#define MAX_ITEMS 256
#define LIST_CLASS "ComboLBox"

#define CHECK_BOX 13            /* a check box's square [uncertain: Windows 3.1's bitmap] */
#define CHECK_GAP 4             /* from the square to the text [uncertain] */

typedef struct {
    HFONT font;
    int pressed, tracking;      /* buttons */
    int checked;                /* check boxes */
    HICON icon;                 /* icon statics */
    /* combo box */
    char items[MAX_ITEMS][64];
    int count, sel, hot, top;
    int drop_h;                 /* height asked for, field and list */
    HWND list;
    HWND edit;                  /* CBS_DROPDOWN: the field, which keeps the text */
} Ctl;

static Ctl *ctl(HWND h)
{
    Wnd *w = wnd_get(h);

    if (!w)
        return NULL;
    if (!w->data)
        w->data = calloc(1, sizeof(Ctl));
    return w->data;
}

/* Common parts. */
static void validate(HWND h)
{
    Wnd *w = wnd_get(h);

    w->dirty = w->erase = 0;
}

static HDC ctl_dc(HWND h, HFONT *old)
{
    HDC dc = GetDC(h);
    Ctl *c = ctl(h);

    *old = c && c->font ? SelectObject(dc, c->font) : 0;
    return dc;
}

static void ctl_release(HWND h, HDC dc, HFONT old)
{
    if (old)
        SelectObject(dc, old);
    ReleaseDC(h, dc);
}

static HBRUSH ctl_color(HWND h, HDC dc, int type)
{
    return (HBRUSH)SendMessage(GetParent(h), WM_CTLCOLOR, dc, MAKELONG(h, type));
}

static void notify(HWND h, int code)
{
    SendMessage(GetParent(h), WM_COMMAND, (WPARAM)GetDlgCtrlID(h), MAKELONG(h, code));
}

void ctl_fill(HDC dc, int l, int t, int r, int b, COLORREF c)
{
    HBRUSH br = CreateSolidBrush(c);
    RECT rc;

    SetRect(&rc, (int16_t)l, (int16_t)t, (int16_t)r, (int16_t)b);
    FillRect(dc, &rc, br);
    DeleteObject(br);
}

/* A raised 3-D face: highlight on the top and left, two lines of
 * shadow on the bottom and right (one when thin). */
void ctl_bevel(HDC dc, int l, int t, int r, int b, int thin)
{
    ctl_fill(dc, l, t, r, b, GetSysColor(COLOR_BTNFACE));
    ctl_fill(dc, l, t, r - 1, t + 1, GetSysColor(COLOR_BTNHIGHLIGHT));
    ctl_fill(dc, l, t, l + 1, b - 1, GetSysColor(COLOR_BTNHIGHLIGHT));
    ctl_fill(dc, l, b - 1, r, b, GetSysColor(COLOR_BTNSHADOW));
    ctl_fill(dc, r - 1, t, r, b, GetSysColor(COLOR_BTNSHADOW));
    if (!thin) {
        ctl_fill(dc, l + 1, b - 2, r - 1, b - 1, GetSysColor(COLOR_BTNSHADOW));
        ctl_fill(dc, r - 2, t + 1, r - 1, b - 1, GetSysColor(COLOR_BTNSHADOW));
    }
}

int ctl_label(HDC dc, int x, int y, const char *s, int n, int noprefix, int draw)
{
    TEXTMETRIC tm;
    int w = 0, i;

    GetTextMetrics(dc, &tm);
    for (i = 0; i < n; i++) {
        int cw;
        if (s[i] == '&' && !noprefix && i + 1 < n) {
            i++;
            if (s[i] != '&') {
                cw = LOWORD(GetTextExtent(dc, s + i, 1));
                if (draw)
                    ctl_fill(dc, x + w, y + tm.tmAscent + 1, x + w + cw, y + tm.tmAscent + 2, GetTextColor(dc));
            }
        }
        cw = LOWORD(GetTextExtent(dc, s + i, 1));
        if (draw)
            TextOut(dc, (int16_t)(x + w), (int16_t)y, s + i, 1);
        w += cw;
    }
    return w;
}

/* The length of s's next line in width: the words that fit, at least
 * one (DrawText's DT_WORDBREAK leaves a word wider than the line whole,
 * to be clipped). */
static int line_length(HDC dc, const char *s, int width, int noprefix)
{
    int n = 0, fit = 0;

    while (s[n] && s[n] != '\n') {
        n++;
        if (s[n] != ' ' && s[n] && s[n] != '\n')
            continue;
        if (fit && ctl_label(dc, 0, 0, s, n, noprefix, 0) > width)
            break;
        fit = n;
    }
    return fit;
}

/* Text word-wrapped into r: left, centred or right aligned lines, drawn
 * when draw is set.  Returns the height used; *widest gets the widest
 * line. */
static int wrap(HDC dc, const RECT *r, const char *s, int align, int noprefix, int draw, int *widest)
{
    TEXTMETRIC tm;
    int y = r->top, width = r->right - r->left;

    GetTextMetrics(dc, &tm);
    *widest = 0;
    while (*s && y < r->bottom) {
        int n = line_length(dc, s, width, noprefix);
        int w = ctl_label(dc, 0, 0, s, n, noprefix, 0);
        if (draw)
            ctl_label(dc, align == SS_RIGHT ? r->right - w : align == SS_CENTER ? r->left + (width - w) / 2 : r->left,
                      y, s, n, noprefix, 1);
        if (w > *widest)
            *widest = w;
        s += n;
        while (*s == ' ')
            s++;
        if (*s == '\n')
            s++;
        y += tm.tmHeight;
    }
    return y - r->top;
}

void ctl_wrapped_size(HDC dc, const char *s, int width, int noprefix, int *w, int *h)
{
    RECT r;

    SetRect(&r, 0, 0, (int16_t)width, 0x7fff);
    *h = wrap(dc, &r, s, 0, noprefix, 0, w);
}

static LRESULT common(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Ctl *c = ctl(h);

    switch (msg) {
    case WM_SETFONT:
        c->font = wp;
        if (lp)
            InvalidateRect(h, NULL, 1);
        return 0;
    case 0x0031:                /* WM_GETFONT */
        return c->font;
    case WM_SETTEXT:
    case WM_ENABLE:
    case WM_SETFOCUS:
    case WM_KILLFOCUS:
        InvalidateRect(h, NULL, 1);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    }
    return DefWindowProc(h, msg, wp, lp);
}

/* Push buttons. */
static void button_paint(HWND h)
{
    Wnd *w = wnd_get(h);
    Ctl *c = ctl(h);
    HFONT old;
    HDC dc = ctl_dc(h, &old);
    RECT r;
    int def = (w->style & BS_TYPE) == BS_DEFPUSHBUTTON, wd, ht, tw, tx, ty;
    TEXTMETRIC tm;
    HBRUSH bg = ctl_color(h, dc, CTLCOLOR_BTN);

    GetClientRect(h, &r);
    wd = r.right;
    ht = r.bottom;
    if (bg)
        FillRect(dc, &r, bg);
    ctl_fill(dc, 1, 0, wd - 1, 1, 0);
    ctl_fill(dc, 1, ht - 1, wd - 1, ht, 0);
    ctl_fill(dc, 0, 1, 1, ht - 1, 0);
    ctl_fill(dc, wd - 1, 1, wd, ht - 1, 0);
    if (def) {
        ctl_fill(dc, 1, 1, wd - 1, 2, 0);
        ctl_fill(dc, 1, ht - 2, wd - 1, ht - 1, 0);
        ctl_fill(dc, 1, 1, 2, ht - 1, 0);
        ctl_fill(dc, wd - 2, 1, wd - 1, ht - 1, 0);
    }
    if (c->pressed) {
        ctl_fill(dc, 1 + def, 1 + def, wd - 1 - def, ht - 1 - def, GetSysColor(COLOR_BTNFACE));
        ctl_fill(dc, 1 + def, 1 + def, wd - 1 - def, 2 + def, GetSysColor(COLOR_BTNSHADOW));
        ctl_fill(dc, 1 + def, 1 + def, 2 + def, ht - 1 - def, GetSysColor(COLOR_BTNSHADOW));
    } else {
        ctl_bevel(dc, 1 + def, 1 + def, wd - 1 - def, ht - 1 - def, 0);
    }
    GetTextMetrics(dc, &tm);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, IsWindowEnabled(h) ? GetSysColor(COLOR_BTNTEXT) : GetSysColor(17));
    tw = ctl_label(dc, 0, 0, w->text, (int)SDL_strlen(w->text), 0, 0);
    tx = (wd - tw) / 2 + c->pressed;
    ty = (ht - tm.tmHeight) / 2 + c->pressed;
    ctl_label(dc, tx, ty, w->text, (int)SDL_strlen(w->text), 0, 1);
    if (GetFocus() == h) {
        SetRect(&r, (int16_t)(tx - 2), (int16_t)ty, (int16_t)(tx + tw + 2), (int16_t)(ty + tm.tmHeight));
        DrawFocusRect(dc, &r);
    }
    ctl_release(h, dc, old);
}

/* Group boxes: a frame from half the text's height down, the text
 * on the control's background at its top left. */
static void group_paint(HWND h)
{
    Wnd *w = wnd_get(h);
    HFONT old;
    HDC dc = ctl_dc(h, &old);
    HBRUSH bg = ctl_color(h, dc, CTLCOLOR_BTN);
    COLORREF frame = GetSysColor(COLOR_WINDOWFRAME);
    TEXTMETRIC tm;
    RECT r;
    int y, tw;

    GetClientRect(h, &r);
    GetTextMetrics(dc, &tm);
    y = tm.tmHeight / 2;
    ctl_fill(dc, 0, y, r.right, y + 1, frame);
    ctl_fill(dc, 0, r.bottom - 1, r.right, r.bottom, frame);
    ctl_fill(dc, 0, y, 1, r.bottom, frame);
    ctl_fill(dc, r.right - 1, y, r.right, r.bottom, frame);
    tw = ctl_label(dc, 0, 0, w->text, (int)SDL_strlen(w->text), 0, 0);
    SetRect(&r, 8, 0, (int16_t)(10 + tw), (int16_t)tm.tmHeight);
    if (bg)
        FillRect(dc, &r, bg);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, GetSysColor(COLOR_WINDOWTEXT));
    ctl_label(dc, 9, 0, w->text, (int)SDL_strlen(w->text), 0, 1);
    ctl_release(h, dc, old);
}

static int is_check_box(const Wnd *w)
{
    return (w->style & BS_TYPE) == BS_CHECKBOX || (w->style & BS_TYPE) == BS_AUTOCHECKBOX;
}

/* Check boxes: a square (black frame, two while pressed, a cross when
 * checked) in the middle of the left side, the text after it, the
 * focus rectangle around the text. */
static void check_paint(HWND h)
{
    Wnd *w = wnd_get(h);
    Ctl *c = ctl(h);
    HFONT old;
    HDC dc = ctl_dc(h, &old);
    HBRUSH bg = ctl_color(h, dc, CTLCOLOR_BTN);
    COLORREF frame = GetSysColor(COLOR_WINDOWFRAME);
    TEXTMETRIC tm;
    RECT r;
    int y, k, tw, tx, ty;

    GetClientRect(h, &r);
    if (bg)
        FillRect(dc, &r, bg);
    y = (r.bottom - CHECK_BOX) / 2;
    ctl_fill(dc, 0, y, CHECK_BOX, y + CHECK_BOX, frame);
    k = c->pressed ? 2 : 1;
    ctl_fill(dc, k, y + k, CHECK_BOX - k, y + CHECK_BOX - k, GetSysColor(COLOR_WINDOW));
    if (c->checked)
        for (k = 2; k < CHECK_BOX - 2; k++) {
            ctl_fill(dc, k, y + k, k + 1, y + k + 1, frame);
            ctl_fill(dc, CHECK_BOX - 1 - k, y + k, CHECK_BOX - k, y + k + 1, frame);
        }
    GetTextMetrics(dc, &tm);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, GetSysColor(IsWindowEnabled(h) ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT));
    tw = ctl_label(dc, 0, 0, w->text, (int)SDL_strlen(w->text), 0, 0);
    tx = CHECK_BOX + CHECK_GAP;
    ty = (r.bottom - tm.tmHeight) / 2;
    ctl_label(dc, tx, ty, w->text, (int)SDL_strlen(w->text), 0, 1);
    if (GetFocus() == h) {
        SetRect(&r, (int16_t)(tx - 1), (int16_t)ty, (int16_t)(tx + tw + 1), (int16_t)(ty + tm.tmHeight));
        DrawFocusRect(dc, &r);
    }
    ctl_release(h, dc, old);
}

/* A button released over itself: an automatic check box changes, the
 * parent hears of it. */
static void button_done(HWND h)
{
    Ctl *c = ctl(h);

    if ((wnd_get(h)->style & BS_TYPE) == BS_AUTOCHECKBOX) {
        c->checked = !c->checked;
        InvalidateRect(h, NULL, 0);
    }
    notify(h, BN_CLICKED);
}

void button_click(HWND h)
{
    SetFocus(h);
    button_done(h);
}

static void button_set_pressed(HWND h, int on)
{
    Ctl *c = ctl(h);

    if (c->pressed != on) {
        c->pressed = on;
        InvalidateRect(h, NULL, 0);
    }
}

static LRESULT button_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    Ctl *c = ctl(h);
    POINT p;
    RECT r;

    if ((w->style & BS_TYPE) == BS_GROUPBOX) {
        if (msg == WM_PAINT) {
            validate(h);
            group_paint(h);
            return 0;
        }
        if (msg == WM_GETDLGCODE)
            return DLGC_STATIC;
        if (msg == WM_NCHITTEST)
            return HTTRANSPARENT;
        return common(h, msg, wp, lp);
    }
    switch (msg) {
    case WM_PAINT:
        validate(h);
        if (is_check_box(w))
            check_paint(h);
        else
            button_paint(h);
        return 0;
    case WM_GETDLGCODE:
        if (is_check_box(w))
            return DLGC_BUTTON;
        return DLGC_BUTTON | ((w->style & BS_TYPE) == BS_DEFPUSHBUTTON ? DLGC_DEFPUSHBUTTON : DLGC_UNDEFPUSHBUTTON);
    case BM_GETCHECK:
        return c->checked;
    case BM_GETSTATE:
        return c->checked | (c->pressed ? BST_PUSHED : 0);
    case BM_SETSTATE:
        button_set_pressed(h, wp != 0);
        return 0;
    case BM_SETCHECK:
        if (is_check_box(w) && c->checked != (int)wp) {
            c->checked = (int)wp;
            InvalidateRect(h, NULL, 0);
        }
        return 0;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        SetCapture(h);
        SetFocus(h);
        c->tracking = 1;
        button_set_pressed(h, 1);
        return 0;
    case WM_MOUSEMOVE:
        if (c->tracking) {
            GetClientRect(h, &r);
            p.x = LOWORD(lp);
            p.y = HIWORD(lp);
            button_set_pressed(h, PtInRect(&r, p));
        }
        return 0;
    case WM_LBUTTONUP:
        if (!c->tracking)
            return 0;
        c->tracking = 0;
        ReleaseCapture();
        if (c->pressed) {
            button_set_pressed(h, 0);
            button_done(h);
        }
        return 0;
    case WM_KEYDOWN:
        if (wp == VK_SPACE)
            button_set_pressed(h, 1);
        return 0;
    case WM_KEYUP:
        if (wp == VK_SPACE && c->pressed) {
            button_set_pressed(h, 0);
            button_done(h);
        }
        return 0;
    case WM_KILLFOCUS:
        c->pressed = c->tracking = 0;
        break;
    }
    return common(h, msg, wp, lp);
}

/* Static text, or an icon (SS_ICON: STM_SETICON's, at the top left; the
 * template's icon resource is not loaded [uncertain: the game's names
 * none that exists]). */
static LRESULT static_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    Ctl *c = ctl(h);
    HFONT old;
    HDC dc;
    HBRUSH bg;
    RECT r;
    HICON prev;
    int widest;

    switch (msg) {
    case WM_PAINT:
        validate(h);
        dc = ctl_dc(h, &old);
        bg = ctl_color(h, dc, CTLCOLOR_STATIC);
        GetClientRect(h, &r);
        if (bg)
            FillRect(dc, &r, bg);
        SetBkMode(dc, TRANSPARENT);
        if ((w->style & SS_TYPE) == SS_ICON) {
            if (c->icon)
                DrawIcon(dc, 0, 0, c->icon);
        } else {
            wrap(dc, &r, w->text, (int)(w->style & SS_TYPE), (w->style & SS_NOPREFIX) != 0, 1, &widest);
        }
        ctl_release(h, dc, old);
        return 0;
    case STM_SETICON:
        prev = c->icon;
        c->icon = wp;
        InvalidateRect(h, NULL, 1);
        return prev;
    case WM_GETDLGCODE:
        return DLGC_STATIC;
    case WM_SETFOCUS:
        return 0;
    }
    return common(h, msg, wp, lp);
}

/* Combo boxes (drop-down lists, and CBS_DROPDOWN ones whose field is an
 * edit control).  The window is as high as the field; the height it was
 * made or moved with is the field and the list together, as in
 * Windows. */
static int combo_item_h(HWND h)
{
    HFONT old;
    HDC dc = ctl_dc(h, &old);
    TEXTMETRIC tm;

    GetTextMetrics(dc, &tm);
    ctl_release(h, dc, old);
    return tm.tmHeight;
}

static int combo_field_h(HWND h)
{
    return combo_item_h(h) + 6;
}

static void combo_paint(HWND h)
{
    Ctl *c = ctl(h);
    HFONT old;
    HDC dc = ctl_dc(h, &old);
    RECT r;
    int wd, ht, ax, i;

    GetClientRect(h, &r);
    wd = r.right;
    ht = r.bottom;
    ax = wd - ARROW_W;
    ctl_color(h, dc, CTLCOLOR_EDIT);
    ctl_fill(dc, 0, 0, wd, ht, 0);
    ctl_fill(dc, 1, 1, ax, ht - 1, GetSysColor(COLOR_WINDOW));
    SetBkMode(dc, TRANSPARENT);
    if (GetFocus() == h && !c->list) {
        ctl_fill(dc, 3, 3, ax - 2, ht - 3, GetSysColor(COLOR_HIGHLIGHT));
        SetTextColor(dc, GetSysColor(COLOR_HIGHLIGHTTEXT));
    }
    if (!c->edit && c->sel >= 0 && c->sel < c->count)
        ctl_label(dc, 4, (ht - combo_item_h(h)) / 2, c->items[c->sel], (int)SDL_strlen(c->items[c->sel]), 1, 1);
    if (GetFocus() == h && !c->list) {
        SetRect(&r, 3, 3, (int16_t)(ax - 2), (int16_t)(ht - 3));
        DrawFocusRect(dc, &r);
    }
    ctl_bevel(dc, ax + 1, 1, wd - 1, ht - 1, 1);
    for (i = 0; i < 4; i++)
        ctl_fill(dc, ax + 5 + i, ht / 2 - 3 + i, wd - 5 - i, ht / 2 - 2 + i, IsWindowEnabled(h) ? 0 : GetSysColor(COLOR_BTNSHADOW));
    ctl_fill(dc, ax + 5, ht / 2 + 2, wd - 5, ht / 2 + 3, 0);
    ctl_release(h, dc, old);
    if (c->edit)
        InvalidateRect(c->edit, NULL, 0);       /* painted over: the field again */
}

/* The edit field inside the frame, left of the arrow [uncertain: Windows
 * 3.1 drew the field and the arrow button apart]. */
static void combo_place_edit(HWND h)
{
    Ctl *c = ctl(h);
    RECT r;

    GetClientRect(h, &r);
    MoveWindow(c->edit, 3, 2, (int16_t)(r.right - ARROW_W - 4), (int16_t)(r.bottom - 4), 1);
}

/* The edit field's text (and so the combo box's), all selected. */
static void combo_set_edit(HWND h, const char *s)
{
    Ctl *c = ctl(h);

    SDL_strlcpy(wnd_get(h)->text, s, sizeof wnd_get(h)->text);
    SetWindowText(c->edit, s);
    SendMessage(c->edit, EM_SETSEL, 0, MAKELONG(0, -1));
}

static void combo_select(HWND h, int i, int tell)
{
    Ctl *c = ctl(h);

    if (i < 0 || i >= c->count || i == c->sel)
        return;
    c->sel = i;
    if (c->edit)
        combo_set_edit(h, c->items[i]);
    InvalidateRect(h, NULL, 0);
    if (tell)
        notify(h, CBN_SELCHANGE);
}

static void combo_close(HWND h, int take)
{
    Ctl *c = ctl(h);
    HWND list = c->list;

    if (!list)
        return;
    c->list = 0;
    ReleaseCapture();
    DestroyWindow(list);
    if (take)
        combo_select(h, c->hot, 1);
    InvalidateRect(h, NULL, 0);
}

static void list_set_hot(HWND combo, int i);

static void combo_open(HWND h)
{
    Wnd *w = wnd_get(h);
    Ctl *c = ctl(h);
    int ih = combo_item_h(h), lh = c->drop_h - (w->rect.bottom - w->rect.top);

    if (c->list || c->count == 0)
        return;
    notify(h, CBN_DROPDOWN);
    if (lh < ih + 2)
        lh = ih + 2;
    lh = (lh - 2) / ih * ih + 2;
    if (lh > c->count * ih + 2)
        lh = c->count * ih + 2;
    c->hot = c->sel;
    c->top = 0;
    c->list = CreateWindow(LIST_CLASS, "", WS_POPUP | WS_BORDER, w->rect.left, w->rect.bottom,
                           (int16_t)(w->rect.right - w->rect.left), (int16_t)lh, h, 0, 0, NULL);
    if (c->hot >= 0)
        list_set_hot(h, c->hot);
    ShowWindow(c->list, SW_SHOWNA);
    SetCapture(c->list);
    InvalidateRect(h, NULL, 0);
}

static int combo_search(HWND h, int start, const char *s, int exact)
{
    Ctl *c = ctl(h);
    size_t n = SDL_strlen(s);
    int k;

    for (k = 1; k <= c->count; k++) {
        int i = (start + k) % c->count;
        if (exact ? !SDL_strcasecmp(c->items[i], s) : !SDL_strncasecmp(c->items[i], s, n))
            return i;
    }
    return -1;
}

/* The open list: rows that fit, and a scroll bar on the right when the
 * items do not (arrow buttons and a square thumb, Windows 3.1's look
 * approximated). */
static int list_rows(HWND combo)
{
    RECT r;

    GetClientRect(ctl(combo)->list, &r);
    return r.bottom / combo_item_h(combo);
}

static int list_has_bar(HWND combo)
{
    return ctl(combo)->count > list_rows(combo);
}

static void list_scroll(HWND combo, int top)
{
    Ctl *c = ctl(combo);
    int rows = list_rows(combo);

    if (top > c->count - rows)
        top = c->count - rows;
    c->top = top < 0 ? 0 : top;
    InvalidateRect(c->list, NULL, 0);
}

static void list_set_hot(HWND combo, int i)
{
    Ctl *c = ctl(combo);
    int rows = list_rows(combo);

    c->hot = i < 0 ? 0 : i >= c->count ? c->count - 1 : i;
    if (c->hot < c->top)
        list_scroll(combo, c->hot);
    else if (c->hot >= c->top + rows)
        list_scroll(combo, c->hot - rows + 1);
    InvalidateRect(c->list, NULL, 0);
}

static void list_key(HWND combo, int vk)
{
    Ctl *c = ctl(combo);
    int rows = list_rows(combo);

    switch (vk) {
    case VK_DOWN: list_set_hot(combo, c->hot + 1); break;
    case VK_UP: list_set_hot(combo, c->hot - 1); break;
    case VK_NEXT: list_set_hot(combo, c->hot + rows - 1); break;
    case VK_PRIOR: list_set_hot(combo, c->hot - rows + 1); break;
    case VK_HOME: list_set_hot(combo, 0); break;
    case VK_END: list_set_hot(combo, c->count - 1); break;
    }
}

static void arrow(HDC dc, int l, int t, int up)
{
    int i;

    for (i = 0; i < 4; i++) {
        int y = up ? t + 6 + i : t + 9 - i;
        ctl_fill(dc, l + 8 - i, y, l + 9 + i, y + 1, 0);
    }
}

static int thumb_top(HWND combo, int height)
{
    Ctl *c = ctl(combo);
    int range = c->count - list_rows(combo);

    return ARROW_W + (height - 3 * ARROW_W) * c->top / (range > 0 ? range : 1);
}

static void list_bar(HWND combo, HDC dc, const RECT *r)
{
    int x = r->right - ARROW_W, t = thumb_top(combo, r->bottom);

    ctl_fill(dc, x, 0, r->right, r->bottom, GetSysColor(COLOR_SCROLLBAR));
    ctl_fill(dc, x, 0, x + 1, r->bottom, 0);
    ctl_bevel(dc, x + 1, 0, r->right, ARROW_W, 1);
    arrow(dc, x, 0, 1);
    ctl_bevel(dc, x + 1, r->bottom - ARROW_W, r->right, r->bottom, 1);
    arrow(dc, x, r->bottom - ARROW_W, 0);
    ctl_bevel(dc, x + 1, t, r->right, t + ARROW_W, 1);
}

/* A click on the scroll bar at y: a line or a page up or down. */
static void list_bar_click(HWND combo, int y, int height)
{
    Ctl *c = ctl(combo);
    int rows = list_rows(combo), t = thumb_top(combo, height);

    if (y < ARROW_W)
        list_scroll(combo, c->top - 1);
    else if (y >= height - ARROW_W)
        list_scroll(combo, c->top + 1);
    else if (y < t)
        list_scroll(combo, c->top - rows);
    else if (y >= t + ARROW_W)
        list_scroll(combo, c->top + rows);
}

static void combo_key(HWND h, int vk)
{
    Ctl *c = ctl(h);
    int alt = GetKeyState(VK_MENU) < 0;

    if (vk == VK_F4 || ((vk == VK_DOWN || vk == VK_UP) && alt)) {
        if (c->list)
            combo_close(h, 1);
        else
            combo_open(h);
        return;
    }
    if (c->list) {
        if (vk == VK_RETURN || vk == VK_ESCAPE)
            combo_close(h, vk == VK_RETURN);
        else
            list_key(h, vk);
        return;
    }
    switch (vk) {
    case VK_DOWN:
    case VK_RIGHT:
        combo_select(h, c->sel + 1, 1);
        break;
    case VK_UP:
    case VK_LEFT:
        combo_select(h, c->sel - 1, 1);
        break;
    case VK_HOME:
        combo_select(h, 0, 1);
        break;
    case VK_END:
        combo_select(h, c->count - 1, 1);
        break;
    }
}

static LRESULT combo_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    Ctl *c = ctl(h);
    char s[2];
    int i;

    switch (msg) {
    case WM_CREATE:
        c->sel = -1;
        if ((w->style & CBS_TYPE) == CBS_DROPDOWN)
            c->edit = CreateWindow("Edit", w->text, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 0, 0, 0, 0, h,
                                   (HMENU)COMBO_EDIT, w->inst, NULL);
        return 0;
    case WM_SIZE:
        if (HIWORD(lp) != combo_field_h(h)) {
            c->drop_h = HIWORD(lp);
            SetWindowPos(h, 0, 0, 0, LOWORD(lp), (int16_t)combo_field_h(h), SWP_NOMOVE);
        }
        if (c->edit)
            combo_place_edit(h);
        return 0;
    case WM_SETFONT:
        if (c->edit)
            SendMessage(c->edit, WM_SETFONT, wp, lp);
        common(h, msg, wp, lp);
        SetWindowPos(h, 0, 0, 0, (int16_t)(w->rect.right - w->rect.left), (int16_t)combo_field_h(h), SWP_NOMOVE);
        if (c->edit)
            combo_place_edit(h);
        return 0;
    case WM_PAINT:
        validate(h);
        combo_paint(h);
        return 0;
    case WM_GETDLGCODE:
        return DLGC_WANTARROWS | DLGC_WANTCHARS | (c->list ? DLGC_WANTMESSAGE : 0);
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        SetFocus(h);
        combo_open(h);
        return 0;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        combo_key(h, wp);
        return 0;
    case WM_CHAR:
        s[0] = (char)wp;
        s[1] = 0;
        i = combo_search(h, c->list ? c->hot : c->sel, s, 0);
        if (c->list && i >= 0) {
            list_set_hot(h, i);
        } else {
            combo_select(h, i, 1);
        }
        return 0;
    case WM_KILLFOCUS:
        combo_close(h, 0);
        break;
    case WM_SETFOCUS:
        if (!c->edit)
            break;
        SetFocus(c->edit);
        SendMessage(c->edit, EM_SETSEL, 0, MAKELONG(0, -1));
        return 0;
    case WM_SETTEXT:
        if (c->edit)
            SetWindowText(c->edit, w->text);
        break;
    case WM_ENABLE:
        if (c->edit)
            EnableWindow(c->edit, (BOOL)wp);
        break;
    case WM_CTLCOLOR:           /* from the edit field */
        return SendMessage(GetParent(h), msg, wp, lp);
    case WM_COMMAND:            /* from the edit field */
        if (HIWORD(lp) == EN_CHANGE) {
            GetWindowText(c->edit, w->text, sizeof w->text);
            notify(h, CBN_EDITCHANGE);
        } else if (HIWORD(lp) == EN_KILLFOCUS) {
            combo_close(h, 0);
        }
        return 0;
    case CB_LIMITTEXT:
        if (!c->edit)
            return -1;          /* CB_ERR */
        SendMessage(c->edit, EM_LIMITTEXT, wp, 0);
        return 1;
    case CB_GETCURSEL:
        return c->sel;
    case CB_SETCURSEL:
        c->sel = (int16_t)wp < c->count ? (int16_t)wp : -1;
        if (c->edit)
            combo_set_edit(h, c->sel >= 0 ? c->items[c->sel] : "");
        InvalidateRect(h, NULL, 0);
        return c->sel;
    case CB_GETCOUNT:
        return c->count;
    case CB_ADDSTRING:
        return combo_add_string(h, (LPCSTR)lp);
    case CB_GETLBTEXT:
        return combo_get_text(h, (int16_t)wp, (LPSTR)lp, 256);
    case CB_FINDSTRING:
        return combo_find_string(h, (int16_t)wp, (LPCSTR)lp);
    case CB_RESETCONTENT:
        c->count = 0;
        c->sel = -1;
        InvalidateRect(h, NULL, 0);
        return 0;
    case CB_SHOWDROPDOWN:
        if (wp)
            combo_open(h);
        else
            combo_close(h, 0);
        return 1;
    case CB_GETDROPPEDSTATE:
        return c->list != 0;
    case WM_DESTROY:
        combo_close(h, 0);
        return 0;
    }
    return common(h, msg, wp, lp);
}

int16_t combo_add_string(HWND combo, LPCSTR s)
{
    Wnd *w = wnd_get(combo);
    Ctl *c = ctl(combo);
    int i;

    if (!c || c->count == MAX_ITEMS)
        return -2;              /* CB_ERRSPACE */
    i = c->count;
    if (w->style & CBS_SORT)
        while (i > 0 && SDL_strcasecmp(c->items[i - 1], s) > 0)
            i--;
    memmove(c->items[i + 1], c->items[i], (size_t)(c->count - i) * sizeof c->items[0]);
    SDL_strlcpy(c->items[i], s, sizeof c->items[0]);
    c->count++;
    if (c->sel >= i)
        c->sel++;
    return (int16_t)i;
}

int16_t combo_find_string(HWND combo, int16_t start, LPCSTR s)
{
    Ctl *c = ctl(combo);

    if (!c || !c->count)
        return -1;
    return (int16_t)combo_search(combo, start < 0 || start >= c->count ? c->count - 1 : start, s, 0);
}

int16_t combo_get_text(HWND combo, int16_t i, LPSTR out, int16_t n)
{
    Ctl *c = ctl(combo);

    if (!c || i < 0 || i >= c->count)
        return -1;
    SDL_strlcpy(out, c->items[i], (size_t)n);
    return (int16_t)SDL_strlen(out);
}

/* The open list of a combo box: a popup owned by the combo box, with the
 * mouse captured while open. */
static LRESULT list_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    HWND combo = GetParent(h);
    Ctl *c = ctl(combo);
    HFONT old;
    HDC dc;
    RECT r;
    int i, ih, y, w;

    switch (msg) {
    case WM_PAINT:
        validate(h);
        ih = combo_item_h(combo);
        dc = GetDC(h);
        old = c->font ? SelectObject(dc, c->font) : 0;
        GetClientRect(h, &r);
        ctl_color(combo, dc, CTLCOLOR_LISTBOX);
        ctl_fill(dc, 0, 0, r.right, r.bottom, GetSysColor(COLOR_WINDOW));
        SetBkMode(dc, TRANSPARENT);
        if (list_has_bar(combo))
            list_bar(combo, dc, &r);
        w = list_has_bar(combo) ? r.right - ARROW_W : r.right;
        for (i = c->top, y = 0; i < c->count && y + ih <= r.bottom; i++, y += ih) {
            if (i == c->hot)
                ctl_fill(dc, 0, y, w, y + ih, GetSysColor(COLOR_HIGHLIGHT));
            SetTextColor(dc, GetSysColor(i == c->hot ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
            ctl_label(dc, 2, y, c->items[i], (int)SDL_strlen(c->items[i]), 1, 1);
        }
        if (old)
            SelectObject(dc, old);
        ReleaseDC(h, dc);
        return 0;
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        GetClientRect(h, &r);
        y = (int16_t)HIWORD(lp);
        w = list_has_bar(combo) ? r.right - ARROW_W : r.right;
        if (list_has_bar(combo) && (int16_t)LOWORD(lp) >= w && (int16_t)LOWORD(lp) < r.right && y >= 0 &&
            y < r.bottom) {
            if (msg == WM_LBUTTONDOWN)
                list_bar_click(combo, y, r.bottom);
            return 0;
        }
        i = (int16_t)LOWORD(lp) >= 0 && (int16_t)LOWORD(lp) < w && y >= 0 && y < r.bottom
                ? c->top + y / combo_item_h(combo) : -1;
        if (i >= 0 && i < c->count && i != c->hot && (msg != WM_MOUSEMOVE || wp & MK_LBUTTON)) {
            c->hot = i;
            InvalidateRect(h, NULL, 0);
        }
        if (msg == WM_LBUTTONUP && i >= 0)
            combo_close(combo, 1);
        else if (msg == WM_LBUTTONDOWN && i < 0)
            combo_close(combo, 0);
        return 0;
    }
    return DefWindowProc(h, msg, wp, lp);
}

void CheckDlgButton(HWND dlg, int16_t id, UINT check)
{
    SendDlgItemMessage(dlg, id, BM_SETCHECK, check, 0);
}

UINT IsDlgButtonChecked(HWND dlg, int16_t id)
{
    return (UINT)SendDlgItemMessage(dlg, id, BM_GETCHECK, 0, 0);
}

void controls_register(void)
{
    static const struct {
        const char *name;
        WNDPROC proc;
    } cls[] = {
        {"Button", button_proc}, {"Static", static_proc}, {"Edit", edit_proc},
        {"ComboBox", combo_proc}, {LIST_CLASS, list_proc}, {"ListBox", listbox_proc},
        {"ScrollBar", scrollbar_proc},
    };
    WNDCLASS wc;
    size_t i;

    memset(&wc, 0, sizeof wc);
    for (i = 0; i < sizeof cls / sizeof cls[0]; i++) {
        wc.lpfnWndProc = cls[i].proc;
        wc.lpszClassName = cls[i].name;
        RegisterClass(&wc);
    }
}
