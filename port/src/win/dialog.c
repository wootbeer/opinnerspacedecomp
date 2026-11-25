/* Dialog boxes from DIALOG resources (Windows 3.1 template format): the
 * dialog window and its controls, the modal loop of DialogBox and the
 * dialog keyboard interface (IsDialogMessage). */
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

#define RT_DIALOG_ 5
#define DC_HASDEFID 0x534b
#define CTLCOLOR_DLG 4

typedef struct {
    DLGPROC proc;
    int ended;
    int16_t result;
    HFONT font;
} Dlg;

/* A reader over a template. */
typedef struct {
    const uint8_t *p, *end;
} Tpl;

static unsigned tpl_byte(Tpl *t)
{
    return t->p < t->end ? *t->p++ : 0;
}

static unsigned tpl_word(Tpl *t)
{
    unsigned lo = tpl_byte(t);

    return lo | tpl_byte(t) << 8;
}

static DWORD tpl_dword(Tpl *t)
{
    DWORD lo = tpl_word(t);

    return lo | (DWORD)tpl_word(t) << 16;
}

static const char *tpl_string(Tpl *t)
{
    const char *s = (const char *)t->p;

    while (t->p < t->end && *t->p)
        t->p++;
    if (t->p < t->end)
        t->p++;
    return s;
}

static Dlg *dlg_of(HWND h)
{
    Wnd *w = wnd_get(h);

    return w && dialog_is(h) ? w->data : NULL;
}

int dialog_is(HWND h)
{
    Wnd *w = wnd_get(h);

    return w && !SDL_strcasecmp(w->cls, DIALOG_CLASS);
}

/* The dialog procedure first; what it leaves is DefDlgProc's. */
static LRESULT dlg_wndproc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Dlg *d = dlg_of(h);
    LRESULT r = d && d->proc ? d->proc(h, msg, wp, lp) : 0;
    HWND c;
    RECT rc;

    if (r)
        return r;
    switch (msg) {
    case WM_CLOSE:
        PostMessage(h, WM_COMMAND, IDCANCEL, MAKELONG(GetDlgItem(h, IDCANCEL), 0));
        return 0;
    case DM_GETDEFID:
        for (c = GetWindow(h, GW_CHILD); c; c = GetWindow(c, GW_HWNDNEXT))
            if (SendMessage(c, WM_GETDLGCODE, 0, 0) & DLGC_DEFPUSHBUTTON)
                return MAKELONG(GetDlgCtrlID(c), DC_HASDEFID);
        return 0;
    case WM_ERASEBKGND:
        GetClientRect(h, &rc);
        FillRect(wp, &rc, (HBRUSH)SendMessage(h, WM_CTLCOLOR, wp, MAKELONG(h, CTLCOLOR_DLG)));
        return 1;
    }
    return DefWindowProc(h, msg, wp, lp);
}

/* Dialog base units of a font: the average width of the 52 letters,
 * rounded, and the height (Helv 8 bold: 7 and 13). */
static void base_units(HFONT font, int *bx, int *by)
{
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    HDC dc = GetDC(0);
    HFONT old = font ? SelectObject(dc, font) : 0;
    TEXTMETRIC tm;

    GetTextMetrics(dc, &tm);
    *bx = (LOWORD(GetTextExtent(dc, letters, 52)) / 26 + 1) / 2;
    *by = tm.tmHeight;
    if (old)
        SelectObject(dc, old);
    ReleaseDC(0, dc);
}

static int16_t units(int v, int base, int div)
{
    return (int16_t)((v * base + div / 2) / div);
}

/* The focus moved by the dialog: an edit control gets all its text
 * selected. */
static void move_focus(HWND c)
{
    SetFocus(c);
    if (SendMessage(c, WM_GETDLGCODE, 0, 0) & DLGC_HASSETSEL)
        SendMessage(c, EM_SETSEL, 0, MAKELONG(0, -1));
}

static const char *const predefined[] = {"Button", "Edit", "Static", "ListBox", "ScrollBar", "ComboBox"};

static HWND create_from(const uint8_t *res, uint32_t size, HWND owner, DLGPROC proc)
{
    Tpl t = {res, res + size};
    DWORD style = tpl_dword(&t);
    int n = (int)tpl_byte(&t), x = (int16_t)tpl_word(&t), y = (int16_t)tpl_word(&t);
    int cx = (int16_t)tpl_word(&t), cy = (int16_t)tpl_word(&t), bx, by, i;
    const char *caption;
    HFONT font = 0;
    RECT r, client;
    HWND h, first = 0;
    POINT org = {0, 0};
    Dlg *d;

    if (tpl_byte(&t) == 0xff)               /* menu: none, ordinal or name */
        tpl_word(&t);
    else if (t.p[-1])
        tpl_string(&t);
    if (tpl_byte(&t))                       /* class */
        tpl_string(&t);
    caption = tpl_string(&t);
    if (style & DS_SETFONT) {               /* Windows 3.1 made it bold */
        int pt = (int)tpl_word(&t);
        font = CreateFont((int16_t)-((pt * 96 + 36) / 72), 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, tpl_string(&t));
    }
    base_units(font, &bx, &by);
    if (owner)
        ClientToScreen(owner, &org);
    SetRect(&r, 0, 0, 100, 100);
    wnd_frame(style, 1, &client, &r);
    SetRect(&r, (int16_t)(org.x + units(x, bx, 4)), (int16_t)(org.y + units(y, by, 8)), 0, 0);
    r.right = (int16_t)(r.left + units(cx, bx, 4) + 100 - (client.right - client.left));
    r.bottom = (int16_t)(r.top + units(cy, by, 8) + 100 - (client.bottom - client.top));
    h = CreateWindow(DIALOG_CLASS, caption, style & ~WS_VISIBLE, r.left, r.top, (int16_t)(r.right - r.left),
                     (int16_t)(r.bottom - r.top), owner, 0, 0, NULL);
    if (!h)
        return 0;
    d = calloc(1, sizeof *d);
    wnd_get(h)->data = d;
    d->proc = proc;
    d->font = font;
    for (i = 0; i < n; i++) {
        int ix = (int16_t)tpl_word(&t), iy = (int16_t)tpl_word(&t);
        int icx = (int16_t)tpl_word(&t), icy = (int16_t)tpl_word(&t);
        unsigned id = tpl_word(&t);
        DWORD cs = tpl_dword(&t);
        const char *cls, *text;
        unsigned k = tpl_byte(&t);
        HWND c;

        cls = k & 0x80 ? (k - 0x80 < 6 ? predefined[k - 0x80] : "Static") : (t.p--, tpl_string(&t));
        if (t.p < t.end && *t.p == 0xff) {      /* a resource id (icons): no text */
            t.p += 3;
            text = "";
        } else {
            text = tpl_string(&t);
        }
        t.p += tpl_byte(&t);
        c = CreateWindow(cls, text, cs | WS_CHILD, units(ix, bx, 4), units(iy, by, 8), units(icx, bx, 4),
                         units(icy, by, 8), h, (HMENU)id, 0, NULL);
        if (!c) {
            SDL_Log("dialog: no class %s", cls);
            continue;
        }
        if (font)
            SendMessage(c, WM_SETFONT, font, 0);
        if (!first && cs & WS_TABSTOP)
            first = c;
    }
    if (proc(h, WM_INITDIALOG, first, 0) && first)
        move_focus(first);
    if (style & WS_VISIBLE)
        ShowWindow(h, SW_SHOW);
    return h;
}

static const uint8_t *template_of(HINSTANCE inst, LPCSTR name, uint32_t *size)
{
    const uint8_t *res = module_resource(inst, MAKEINTRESOURCE(RT_DIALOG_), name, size);

    if (!res)
        SDL_Log("dialog %u not found", IS_INTRESOURCE(name) ? (unsigned)(uintptr_t)name : 0);
    return res;
}

HWND CreateDialog(HINSTANCE inst, LPCSTR name, HWND owner, DLGPROC proc)
{
    uint32_t size;
    const uint8_t *res = template_of(inst, name, &size);

    return res ? create_from(res, size, owner, proc) : 0;
}

int16_t DialogBox(HINSTANCE inst, LPCSTR name, HWND owner, DLGPROC proc)
{
    uint32_t size;
    const uint8_t *res = template_of(inst, name, &size);
    HWND h;
    Dlg *d;
    MSG m;
    int16_t result;

    if (!res)
        return -1;
    if (owner)
        EnableWindow(owner, 0);
    h = create_from(res, size, owner, proc);
    d = dlg_of(h);
    if (d && !d->ended)
        ShowWindow(h, SW_SHOW);
    while (d && !d->ended && GetMessage(&m, 0, 0, 0)) {
        if (!IsDialogMessage(h, &m)) {
            TranslateMessage(&m);
            DispatchMessage(&m);
        }
    }
    result = d ? d->result : -1;
    if (owner) {
        EnableWindow(owner, 1);
        SetActiveWindow(owner);
    }
    if (h) {
        if (d->font)
            DeleteObject(d->font);
        DestroyWindow(h);
    }
    return result;
}

void EndDialog(HWND h, int16_t r)
{
    Dlg *d = dlg_of(h);

    if (d) {
        d->ended = 1;
        d->result = r;
    }
}

int dialog_ended(HWND h, int16_t *result)
{
    Dlg *d = dlg_of(h);

    if (d && d->ended)
        *result = d->result;
    return d && d->ended;
}

LRESULT SendDlgItemMessage(HWND dlg, int16_t id, UINT msg, WPARAM wp, LPARAM lp)
{
    return SendMessage(GetDlgItem(dlg, id), msg, wp, lp);
}

HWND GetDlgItem(HWND h, int16_t id)
{
    HWND c;

    for (c = GetWindow(h, GW_CHILD); c; c = GetWindow(c, GW_HWNDNEXT))
        if (GetDlgCtrlID(c) == id)
            return c;
    return 0;
}

/* The dialog's control that h is or is inside (a combo box's edit
 * field), or 0. */
static HWND control_of(HWND dlg, HWND h)
{
    Wnd *w = wnd_get(h);

    while (w && wnd_is_child(w) && w->parent != dlg)
        w = wnd_get(w->parent);
    return w && wnd_is_child(w) ? w->hwnd : 0;
}

/* The next (dir 1) or previous (-1) control that takes the focus: with
 * WS_TABSTOP (tab), or in from's group (arrows). */
static HWND next_control(HWND dlg, HWND from, int dir, int group)
{
    HWND list[64], c;
    int n = 0, i, k, at = 0;

    for (c = GetWindow(dlg, GW_CHILD); c && n < 64; c = GetWindow(c, GW_HWNDNEXT)) {
        if (c == from)
            at = n;
        list[n++] = c;
    }
    for (k = 1; k <= n; k++) {
        Wnd *w;
        i = ((at + dir * k) % n + n) % n;
        w = wnd_get(list[i]);
        if (group && (dir > 0 ? w->style & WS_GROUP : wnd_get(list[(i + 1) % n])->style & WS_GROUP))
            return from;
        if (w->visible && !(w->style & WS_DISABLED) && (group || w->style & WS_TABSTOP) &&
            !(SendMessage(list[i], WM_GETDLGCODE, 0, 0) & DLGC_STATIC))
            return list[i];
    }
    return from;
}

/* The control whose text has '&' before ch, and the control to act on:
 * a button itself, else the next one that takes the focus. */
static HWND mnemonic(HWND dlg, int ch)
{
    HWND c;

    for (c = GetWindow(dlg, GW_CHILD); c; c = GetWindow(c, GW_HWNDNEXT)) {
        const char *s = wnd_get(c)->text, *a = SDL_strchr(s, '&');
        if (!a || SDL_toupper((unsigned char)a[1]) != SDL_toupper(ch) || !IsWindowEnabled(c))
            continue;
        if (SendMessage(c, WM_GETDLGCODE, 0, 0) & DLGC_STATIC)
            return next_control(dlg, c, 1, 1);
        return c;
    }
    return 0;
}

static void command(HWND dlg, int id)
{
    HWND c = GetDlgItem(dlg, (int16_t)id);

    SendMessage(dlg, WM_COMMAND, (WPARAM)id, MAKELONG(c, 0));
}

static int dialog_key(HWND dlg, const MSG *m, LRESULT code)
{
    int vk = (int)m->wParam;
    LRESULT def;

    switch (vk) {
    case VK_TAB:
        move_focus(next_control(dlg, control_of(dlg, GetFocus()), GetKeyState(VK_SHIFT) < 0 ? -1 : 1, 0));
        return 1;
    case VK_LEFT:
    case VK_UP:
    case VK_RIGHT:
    case VK_DOWN:
        if (code & DLGC_WANTARROWS)
            return 0;
        move_focus(next_control(dlg, control_of(dlg, GetFocus()), vk == VK_LEFT || vk == VK_UP ? -1 : 1, 1));
        return 1;
    case VK_RETURN:
        if (code & (DLGC_DEFPUSHBUTTON | DLGC_UNDEFPUSHBUTTON)) {
            command(dlg, GetDlgCtrlID(m->hwnd));
            return 1;
        }
        def = SendMessage(dlg, DM_GETDEFID, 0, 0);
        command(dlg, HIWORD(def) == DC_HASDEFID ? LOWORD(def) : IDOK);
        return 1;
    case VK_ESCAPE:
        command(dlg, IDCANCEL);
        return 1;
    }
    return 0;
}

static int dialog_char(HWND dlg, const MSG *m, LRESULT code)
{
    HWND c;

    if (m->message == WM_CHAR && code & DLGC_WANTCHARS)
        return 0;
    c = mnemonic(dlg, (int)m->wParam);
    if (!c)
        return m->message == WM_SYSCHAR;
    code = SendMessage(c, WM_GETDLGCODE, 0, 0);
    if (code & (DLGC_DEFPUSHBUTTON | DLGC_UNDEFPUSHBUTTON))
        command(dlg, GetDlgCtrlID(c));
    else if (code & DLGC_BUTTON)
        button_click(c);
    else
        move_focus(c);
    return 1;
}

/* Keyboard navigation for messages to the dialog or its controls; every
 * such message is handled here (translated and dispatched when the
 * keys are not the dialog's). */
BOOL IsDialogMessage(HWND dlg, MSG *m)
{
    Wnd *w = wnd_get(m->hwnd);
    LRESULT code;
    int done = 0;

    if (!w || (m->hwnd != dlg && !control_of(dlg, m->hwnd)))
        return 0;
    code = SendMessage(m->hwnd, WM_GETDLGCODE, 0, 0);
    if (m->message == WM_KEYDOWN && !(code & DLGC_WANTMESSAGE))
        done = dialog_key(dlg, m, code);
    else if ((m->message == WM_CHAR || m->message == WM_SYSCHAR) && !(code & DLGC_WANTMESSAGE))
        done = dialog_char(dlg, m, code);
    if (!done) {
        TranslateMessage(m);
        DispatchMessage(m);
    }
    return 1;
}

void dialog_register(void)
{
    WNDCLASS wc;

    memset(&wc, 0, sizeof wc);
    wc.style = CS_SAVEBITS;
    wc.lpfnWndProc = dlg_wndproc;
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = DIALOG_CLASS;
    RegisterClass(&wc);
}
