/* MessageBox: a modal dialog with the type's icon, the text word-wrapped
 * in the System font and a row of push buttons, as Windows 3.1 drew it.
 * The layout's sizes are approximations and the icons are the port's own
 * stand-ins for USER.EXE's (port/NOTES-port.md "Message boxes"). */
#include <SDL3/SDL_log.h>

#include "user.h"

#define MB_TYPEMASK 0x000f
#define MB_ICONMASK 0x00f0
#define MB_DEFMASK 0x0f00
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
#define BS_DEFPUSHBUTTON 1
#define SS_NOPREFIX 0x80
#define TEXT_ID 0xffff
#define TEXT_MAX_WIDTH 400      /* 5/8 of the screen [inferred] */
#define ICON_SIZE 32
#define DWL_USER 8              /* the box's icon (MB_ICONHAND >> 4 to MB_ICONASTERISK >> 4) */
#define DWL_ICON_AT 12          /* where it is drawn */

/* The buttons of each MB_ type, left to right. */
static const int buttons[][4] = {
    {IDOK},
    {IDOK, IDCANCEL},
    {IDABORT, IDRETRY, IDIGNORE},
    {IDYES, IDNO, IDCANCEL},
    {IDYES, IDNO},
    {IDRETRY, IDCANCEL},
};

static const char *label(int id)
{
    static const char *const labels[] = {"", "OK", "Cancel", "&Abort", "&Retry", "&Ignore", "&Yes", "&No"};

    return labels[id];
}

static int button_count(const int *ids)
{
    int n = 0;

    while (n < 4 && ids[n])
        n++;
    return n;
}

/* The template: a captioned popup without controls; WM_INITDIALOG adds
 * them.  Returns the size. */
static uint32_t make_template(uint8_t *t, uint32_t room, const char *title)
{
    static const DWORD style = WS_POPUP | WS_CAPTION | WS_SYSMENU | DS_MODALFRAME;
    uint32_t n = 0, k;

    for (k = 0; k < 4; k++)
        t[n++] = (uint8_t)(style >> 8 * k);
    for (k = 0; k < 11; k++)        /* no controls, position, size, menu, class */
        t[n++] = 0;
    for (k = 0; title[k] && n < room - 1; k++)
        t[n++] = (uint8_t)title[k];
    t[n++] = 0;
    return n;
}

typedef struct {
    const char *text;
    UINT type;
} Box;

/* A control of the box, in the System font the text was measured in. */
static void add(HWND control)
{
    SendMessage(control, WM_SETFONT, wnd_system_font(), 0);
}

/* The icons, drawn: a red stop disc with a white X, and a white disc with
 * a black "?" or "!" or a blue "i". */
static const struct {
    COLORREF disc, glyph;
    char text[2];
} icons[] = {{0}, {RGB(255, 0, 0), RGB(255, 255, 255), "X"}, {RGB(255, 255, 255), RGB(0, 0, 0), "?"},
             {RGB(255, 255, 255), RGB(0, 0, 0), "!"}, {RGB(255, 255, 255), RGB(0, 0, 255), "i"}};

static int icon_of(UINT type)
{
    unsigned i = (type & MB_ICONMASK) >> 4;

    return i < SDL_arraysize(icons) ? (int)i : 0;
}

static void paint_icon(HDC dc, int kind, int x, int y)
{
    HBRUSH disc = CreateSolidBrush(icons[kind].disc);
    HGDIOBJ old_brush = SelectObject(dc, disc), old_pen = SelectObject(dc, GetStockObject(BLACK_PEN));
    HFONT old_font = SelectObject(dc, wnd_system_font());
    DWORD ext = GetTextExtent(dc, icons[kind].text, 1);

    Ellipse(dc, (int16_t)x, (int16_t)y, (int16_t)(x + ICON_SIZE), (int16_t)(y + ICON_SIZE));
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, icons[kind].glyph);
    TextOut(dc, (int16_t)(x + (ICON_SIZE - LOWORD(ext)) / 2), (int16_t)(y + (ICON_SIZE - HIWORD(ext)) / 2),
            icons[kind].text, 1);
    SelectObject(dc, old_font);
    SelectObject(dc, old_pen);
    SelectObject(dc, old_brush);
    DeleteObject(disc);
}

static void lay_out(HWND h, const Box *box)
{
    const int *ids = buttons[box->type & MB_TYPEMASK];
    int n = button_count(ids), def = (int)(box->type & MB_DEFMASK) >> 8, tw, th, tx, ty, bw, bh, gap, cw, ch, w, ht, x, i;
    HDC dc = GetDC(h);
    HFONT old = SelectObject(dc, wnd_system_font());
    TEXTMETRIC tm;
    RECT win, client;

    GetTextMetrics(dc, &tm);
    cw = tm.tmAveCharWidth;
    ch = tm.tmHeight;
    ctl_wrapped_size(dc, box->text, TEXT_MAX_WIDTH, 1, &tw, &th);
    SelectObject(dc, old);
    ReleaseDC(h, dc);
    bw = 10 * cw;
    bh = ch * 3 / 2;
    gap = 2 * cw;
    tx = icon_of(box->type) ? gap + ICON_SIZE + gap : gap;
    ty = ch + SDL_max(0, (ICON_SIZE - th) / 2);
    th = SDL_max(th, icon_of(box->type) ? ICON_SIZE : 0);
    w = SDL_max(tx - gap + tw, n * bw + (n - 1) * gap) + 2 * gap;
    ht = ch + th + ch + bh + ch;
    SetWindowLong(h, DWL_USER, icon_of(box->type));
    SetWindowLong(h, DWL_ICON_AT, MAKELONG(gap, ch));
    add(CreateWindow("Static", box->text, WS_CHILD | WS_VISIBLE | SS_NOPREFIX, (int16_t)tx, (int16_t)ty,
                        (int16_t)tw, (int16_t)(th - (ty - ch)), h, (HMENU)TEXT_ID, 0, NULL));
    for (i = 0, x = (w - n * bw - (n - 1) * gap) / 2; i < n; i++, x += bw + gap)
        add(CreateWindow("Button", label(ids[i]),
                            WS_CHILD | WS_VISIBLE | WS_TABSTOP | (i ? 0 : WS_GROUP) | (i == def ? BS_DEFPUSHBUTTON : 0),
                            (int16_t)x, (int16_t)(ch + th + ch), (int16_t)bw, (int16_t)bh, h,
                            (HMENU)(uintptr_t)ids[i], 0, NULL));
    SetFocus(GetDlgItem(h, (int16_t)ids[SDL_min(def, n - 1)]));
    GetWindowRect(h, &win);
    GetClientRect(h, &client);
    w += win.right - win.left - client.right;
    ht += win.bottom - win.top - client.bottom;
    MoveWindow(h, (int16_t)((GetSystemMetrics(SM_CXSCREEN) - w) / 2), (int16_t)((GetSystemMetrics(SM_CYSCREEN) - ht) / 2),
               (int16_t)w, (int16_t)ht, 0);
}

/* Escape (and Close) answer Cancel when there is a Cancel button, OK
 * when OK is the only one, and nothing otherwise. */
static BOOL box_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    PAINTSTRUCT ps;
    DWORD at;
    int kind;

    switch (msg) {
    case WM_PAINT:
        if (!(kind = (int)GetWindowLong(h, DWL_USER)))
            return 0;
        BeginPaint(h, &ps);
        at = (DWORD)GetWindowLong(h, DWL_ICON_AT);
        paint_icon(ps.hdc, kind, LOWORD(at), HIWORD(at));
        EndPaint(h, &ps);
        return 1;
    case WM_INITDIALOG:
        lay_out(h, (const Box *)lp);
        return 0;
    case WM_COMMAND:
        if (wp == IDCANCEL && !GetDlgItem(h, IDCANCEL)) {
            if (GetDlgItem(h, IDOK))
                EndDialog(h, IDOK);
            return 1;
        }
        if (wp != TEXT_ID)
            EndDialog(h, (int16_t)wp);
        return 1;
    }
    return 0;
}

int16_t MessageBox(HWND h, LPCSTR text, LPCSTR title, UINT type)
{
    uint8_t tpl[256];
    Box box = {text ? text : "", type};

    SDL_Log("MessageBox [%s] %s", title ? title : "", box.text);
    if ((type & MB_TYPEMASK) >= SDL_arraysize(buttons))
        box.type = type & ~MB_TYPEMASK;
    MessageBeep(type & MB_ICONMASK);
    return dialog_box_indirect(tpl, make_template(tpl, sizeof tpl, title ? title : "Error"), h, box_proc,
                               (LPARAM)&box);
}
