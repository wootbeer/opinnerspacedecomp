/* Menus: menu bars, system menus and popup menus (MENU resources of the
 * game's language DLL), drawn in Windows 3.1's look, and the menu loop
 * that runs while one is open.  The loop is modal, as in Windows: it
 * takes the mouse and the keyboard and dispatches everything else, so
 * the game's own idle loop waits.  It sends WM_INITMENU, WM_INITMENUPOPUP
 * and WM_MENUSELECT, and posts WM_COMMAND (WM_SYSCOMMAND for the system
 * menu) for the item chosen.  One level of popups: the game's menus have
 * no cascades.  Sizes are approximations (port/NOTES-port.md). */
#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

#define RT_MENU_ 4
#define MF_GRAYED 0x0001
#define MF_DISABLED 0x0002
#define MF_POPUP 0x0010
#define MF_END 0x0080           /* resource: last item of a level */
#define MF_HILITE 0x0080        /* WM_MENUSELECT */
#define MF_BYPOSITION 0x0400
#define MF_SYSMENU 0x2000
#define MF_MOUSESELECT 0x8000
#define MF_STATE (MF_GRAYED | MF_DISABLED | MF_CHECKED | MF_POPUP | MF_SEPARATOR)

#define MAX_ITEMS 32
#define BAR_PAD 6               /* each side of a menu bar title [uncertain] */
#define CHECK_W 14              /* the check mark column, and as much on the right [uncertain] */
#define ITEM_H 18               /* a popup item (SM_CYMENU) [uncertain] */
#define SEP_H 8                 /* a separator [uncertain] */
#define TAB_GAP 14              /* before the accelerator column [uncertain] */
#define SYSBOX 18               /* SM_CXSIZE */
#define POPUP_CLASS "#32768"
#define NO_SEL (-2)
#define SYS_SEL (-1)            /* the system menu box, left of the bar */

typedef struct {
    UINT flags;                 /* MF_GRAYED, MF_DISABLED, MF_CHECKED, MF_POPUP, MF_SEPARATOR */
    UINT id;                    /* the command, or the popup's menu */
    char text[64];
    RECT r;                     /* laid out: window coordinates (bar), client (popup) */
} Item;

typedef struct {
    int n;
    Item item[MAX_ITEMS];
    int width, height, tab_x;   /* a popup, laid out */
} Menu;

/* The open menu.  The bar row is the system menu box (SYS_SEL) and the
 * menu bar's titles; one popup is open at most. */
static struct {
    int running;
    HWND owner, old_capture;
    HMENU bar, sys;
    int bar_sel;
    HMENU popup;
    HWND popup_wnd;
    int sel;
    int button;                 /* the left button is held */
    int menu_key;               /* Alt or F10 went down in the loop: its release ends it */
    int key;                    /* the last key that went down in the loop */
    int key_ended;              /* that key ended the loop (Esc, Enter, a mnemonic) */
    int chosen;
    UINT cmd;
    int cmd_sys;
    LPARAM cmd_lp;
} t;

static Menu *menu_get(HMENU m)
{
    return handle_get(m, H_MENU);
}

int menu_is(HMENU m)
{
    return menu_get(m) != NULL;
}

static HMENU new_menu(void)
{
    Menu *mn = calloc(1, sizeof *mn);
    HMENU m = mn ? handle_new(H_MENU, mn) : 0;

    if (!m)
        free(mn);
    return m;
}

static int insert(Menu *mn, int at, UINT flags, UINT id, const char *text)
{
    Item *it;

    if (mn->n == MAX_ITEMS)
        return 0;
    memmove(&mn->item[at + 1], &mn->item[at], (size_t)(mn->n - at) * sizeof mn->item[0]);
    mn->n++;
    it = &mn->item[at];
    memset(it, 0, sizeof *it);
    it->flags = flags;
    it->id = id;
    if (text && !(flags & MF_SEPARATOR))
        SDL_strlcpy(it->text, text, sizeof it->text);
    return 1;
}

/* The item at position pos (MF_BYPOSITION) or with command pos, in mn or
 * its popups. */
static Item *find(Menu *mn, UINT pos, UINT flags)
{
    int i;

    if (!mn)
        return NULL;
    if (flags & MF_BYPOSITION)
        return pos < (UINT)mn->n ? &mn->item[pos] : NULL;
    for (i = 0; i < mn->n; i++) {
        Item *it = &mn->item[i], *sub;
        if (it->flags & MF_POPUP) {
            if ((sub = find(menu_get((HMENU)it->id), pos, flags)) != NULL)
                return sub;
        } else if (it->id == pos && !(it->flags & MF_SEPARATOR)) {
            return it;
        }
    }
    return NULL;
}

/* Resources: one level of items, each a flags word, then the id (not
 * for popups) and the text; a popup's items follow it.  An empty item
 * with id 0 is a separator. */
static const uint8_t *parse(HMENU m, const uint8_t *p, const uint8_t *end)
{
    UINT flags;

    do {
        const uint8_t *nul;
        UINT id = 0;
        HMENU sub = 0;
        if (end - p < 2)
            return end;
        flags = p[0] | (UINT)p[1] << 8;
        p += 2;
        if (!(flags & MF_POPUP)) {
            if (end - p < 2)
                return end;
            id = p[0] | (UINT)p[1] << 8;
            p += 2;
        }
        if ((nul = memchr(p, 0, (size_t)(end - p))) == NULL)
            return end;
        if (flags & MF_POPUP) {
            sub = new_menu();
            id = sub;
        } else if (!id && nul == p) {
            flags |= MF_SEPARATOR;
        }
        insert(menu_get(m), menu_get(m)->n, flags & ~MF_END, id, (const char *)p);
        p = nul + 1;
        if (sub)
            p = parse(sub, p, end);
    } while (!(flags & MF_END) && p < end);
    return p;
}

HMENU LoadMenu(HINSTANCE h, LPCSTR name)
{
    uint32_t size;
    const uint8_t *res = module_resource(h, MAKEINTRESOURCE(RT_MENU_), name, &size);
    HMENU m;

    if (!res || size < 4 || !(m = new_menu()))
        return 0;
    parse(m, res + 4 + (res[2] | res[3] << 8), res + size);
    return m;
}

BOOL DestroyMenu(HMENU m)
{
    Menu *mn = menu_get(m);
    int i;

    if (!mn)
        return 0;
    for (i = 0; i < mn->n; i++)
        if (mn->item[i].flags & MF_POPUP)
            DestroyMenu((HMENU)mn->item[i].id);
    handle_free(m);
    free(mn);
    return 1;
}

HMENU GetSubMenu(HMENU m, int16_t pos)
{
    Item *it = find(menu_get(m), (UINT)pos, MF_BYPOSITION);

    return it && it->flags & MF_POPUP ? (HMENU)it->id : 0;
}

int16_t GetMenuItemCount(HMENU m)
{
    Menu *mn = menu_get(m);

    return mn ? (int16_t)mn->n : -1;
}

BOOL AppendMenu(HMENU m, UINT flags, UINT id, LPCSTR text)
{
    Menu *mn = menu_get(m);

    return mn && insert(mn, mn->n, flags & MF_STATE, id, text);
}

BOOL ModifyMenu(HMENU m, UINT pos, UINT flags, UINT id, LPCSTR text)
{
    Item *it = find(menu_get(m), pos, flags);

    if (!it)
        return 0;
    it->flags = flags & MF_STATE;
    it->id = id;
    it->text[0] = 0;
    if (text && !(flags & MF_SEPARATOR))
        SDL_strlcpy(it->text, text, sizeof it->text);
    return 1;
}

/* Both return the item's previous state, -1 when there is no such item. */
BOOL EnableMenuItem(HMENU m, UINT pos, UINT flags)
{
    Item *it = find(menu_get(m), pos, flags);
    UINT old;

    if (!it)
        return -1;
    old = it->flags & (MF_GRAYED | MF_DISABLED);
    it->flags = (it->flags & ~(MF_GRAYED | MF_DISABLED)) | (flags & (MF_GRAYED | MF_DISABLED));
    return (BOOL)old;
}

BOOL CheckMenuItem(HMENU m, UINT pos, UINT flags)
{
    Item *it = find(menu_get(m), pos, flags);
    UINT old;

    if (!it)
        return -1;
    old = it->flags & MF_CHECKED;
    it->flags = (it->flags & ~MF_CHECKED) | (flags & MF_CHECKED);
    return (BOOL)old;
}

BOOL SetMenu(HWND h, HMENU m)
{
    Wnd *w = wnd_get(h);

    if (!w || wnd_is_child(w))
        return 0;
    w->id = m;
    wnd_reframe(h);
    return 1;
}

void DrawMenuBar(HWND h)
{
    Wnd *w = wnd_get(h);

    if (w && !wnd_is_child(w))
        wnd_reframe(h);
}

/* The system menu: Windows 3.1's, each window its own copy once asked
 * for (windows with WS_SYSMENU only). */
static HMENU new_sysmenu(void)
{
    static const struct {
        UINT id;
        const char *text;
    } items[] = {
        {SC_RESTORE, "&Restore"}, {SC_MOVE, "&Move"}, {SC_SIZE, "&Size"}, {SC_MINIMIZE, "Mi&nimize"},
        {SC_MAXIMIZE, "Ma&ximize"}, {0, NULL}, {SC_CLOSE, "&Close\tAlt+F4"}, {0, NULL},
        {SC_TASKLIST, "S&witch To...\tCtrl+Esc"},
    };
    HMENU m = new_menu();
    size_t i;

    for (i = 0; m && i < sizeof items / sizeof items[0]; i++)
        AppendMenu(m, items[i].text ? 0 : MF_SEPARATOR, items[i].id, items[i].text);
    return m;
}

HMENU GetSystemMenu(HWND h, BOOL revert)
{
    Wnd *w = wnd_get(h);

    if (!w)
        return 0;
    if (revert) {
        DestroyMenu(w->sysmenu);
        w->sysmenu = 0;
        return 0;
    }
    if (!w->sysmenu && w->style & WS_SYSMENU)
        w->sysmenu = new_sysmenu();
    return w->sysmenu;
}

/* What the window's style and state allow. */
static void sysmenu_state(HWND h, HMENU m)
{
    DWORD style = wnd_get(h)->style;
    int resized = (style & (WS_MINIMIZE | WS_MAXIMIZE)) != 0;

    EnableMenuItem(m, SC_RESTORE, resized ? 0 : MF_GRAYED);
    EnableMenuItem(m, SC_MOVE, style & WS_MAXIMIZE ? MF_GRAYED : 0);
    EnableMenuItem(m, SC_SIZE, style & WS_THICKFRAME && !resized ? 0 : MF_GRAYED);
    EnableMenuItem(m, SC_MINIMIZE, style & WS_MINIMIZEBOX && !(style & WS_MINIMIZE) ? 0 : MF_GRAYED);
    EnableMenuItem(m, SC_MAXIMIZE, style & WS_MAXIMIZEBOX && !(style & WS_MAXIMIZE) ? 0 : MF_GRAYED);
}

void menu_window_gone(Wnd *w)
{
    DestroyMenu(w->sysmenu);
    w->sysmenu = 0;
    if (!wnd_is_child(w))
        DestroyMenu(w->id);
}

/* Drawing.  Text is in the System font; selected items in the highlight
 * colours, grayed ones in gray. */
static int text_w(HDC dc, const char *s, int n)
{
    return ctl_label(dc, 0, 0, s, n, 0, 0);
}

static int tab_at(const char *s)
{
    const char *tab = SDL_strchr(s, '\t');

    return tab ? (int)(tab - s) : (int)SDL_strlen(s);
}

static void item_colours(HDC dc, const Item *it, int hot)
{
    SetTextColor(dc, GetSysColor(it->flags & MF_GRAYED ? COLOR_GRAYTEXT : hot ? COLOR_HIGHLIGHTTEXT : COLOR_MENUTEXT));
}

static int font_h(HDC dc)
{
    TEXTMETRIC tm;

    GetTextMetrics(dc, &tm);
    return tm.tmHeight;
}

static void layout_bar(Menu *mn, HDC dc, const RECT *bar)
{
    int x = bar->left, i;

    for (i = 0; i < mn->n; i++) {
        Item *it = &mn->item[i];
        int w = text_w(dc, it->text, (int)SDL_strlen(it->text)) + 2 * BAR_PAD;
        SetRect(&it->r, (int16_t)x, bar->top, (int16_t)(x + w), (int16_t)(bar->bottom - 1));
        x += w;
    }
}

static void draw_bar_item(HDC dc, const Item *it, int hot)
{
    const RECT *r = &it->r;

    ctl_fill(dc, r->left, r->top, r->right, r->bottom, GetSysColor(hot ? COLOR_HIGHLIGHT : COLOR_MENU));
    item_colours(dc, it, hot);
    ctl_label(dc, r->left + BAR_PAD, r->top + (r->bottom - r->top - font_h(dc)) / 2, it->text,
              (int)SDL_strlen(it->text), 0, 1);
}

/* A window DC with the System font, transparent text. */
static HDC menu_dc(HWND h, int window, HFONT *old)
{
    HDC dc = window ? GetWindowDC(h) : GetDC(h);

    *old = SelectObject(dc, wnd_system_font());
    SetBkMode(dc, TRANSPARENT);
    return dc;
}

static void release_dc(HWND h, HDC dc, HFONT old)
{
    SelectObject(dc, old);
    ReleaseDC(h, dc);
}

void menu_paint_bar(Wnd *w, HDC dc)
{
    Menu *mn = wnd_is_child(w) ? NULL : menu_get(w->id);
    HFONT old;
    RECT bar;
    int i;

    if (!mn)
        return;
    wnd_menu_rect(w, &bar);
    old = SelectObject(dc, wnd_system_font());
    SetBkMode(dc, TRANSPARENT);
    layout_bar(mn, dc, &bar);
    ctl_fill(dc, bar.left, bar.top, bar.right, bar.bottom - 1, GetSysColor(COLOR_MENU));
    ctl_fill(dc, bar.left, bar.bottom - 1, bar.right, bar.bottom, GetSysColor(COLOR_WINDOWFRAME));
    for (i = 0; i < mn->n; i++)
        draw_bar_item(dc, &mn->item[i], t.running && t.owner == w->hwnd && t.bar_sel == i);
    SelectObject(dc, old);
}

/* The system menu box: a gray square with a bar like a space bar, a
 * black line on its right; inverted while its menu is selected
 * [uncertain: the bar's pixels]. */
void menu_paint_sysbox(Wnd *w, HDC dc, int pressed)
{
    RECT r;
    int l, top;

    wnd_caption_rect(w, &r);
    l = r.left;
    top = r.top;
    ctl_fill(dc, l, top, l + SYSBOX, r.bottom, GetSysColor(COLOR_BTNFACE));
    ctl_fill(dc, l + SYSBOX, top, l + SYSBOX + 1, r.bottom, GetSysColor(COLOR_WINDOWFRAME));
    ctl_fill(dc, l + 3, top + 7, l + 15, top + 11, GetSysColor(COLOR_WINDOWFRAME));
    ctl_fill(dc, l + 4, top + 8, l + 14, top + 10, GetSysColor(COLOR_BTNHIGHLIGHT));
    ctl_fill(dc, l + 4, top + 11, l + 16, top + 12, GetSysColor(COLOR_BTNSHADOW));
    ctl_fill(dc, l + 15, top + 8, l + 16, top + 11, GetSysColor(COLOR_BTNSHADOW));
    if (pressed)
        PatBlt(dc, (int16_t)l, (int16_t)top, SYSBOX, (int16_t)(r.bottom - top), DSTINVERT);
}

/* A popup: a black border, items ITEM_H high with a check mark column on
 * the left, accelerator texts (after a tab) in a column of their own. */
static void layout_popup(Menu *mn, HDC dc)
{
    int y = 1, text = 0, acc = 0, i;

    for (i = 0; i < mn->n; i++) {
        const char *s = mn->item[i].text;
        int k = tab_at(s), h = mn->item[i].flags & MF_SEPARATOR ? SEP_H : ITEM_H;
        text = SDL_max(text, text_w(dc, s, k));
        if (s[k])
            acc = SDL_max(acc, text_w(dc, s + k + 1, (int)SDL_strlen(s + k + 1)));
        SetRect(&mn->item[i].r, 1, (int16_t)y, 0, (int16_t)(y + h));
        y += h;
    }
    mn->tab_x = 1 + CHECK_W + text + TAB_GAP;
    mn->width = 1 + CHECK_W + text + (acc ? TAB_GAP + acc : 0) + CHECK_W + 1;
    mn->height = y + 1;
    for (i = 0; i < mn->n; i++)
        mn->item[i].r.right = (int16_t)(mn->width - 1);
}

static void draw_check(HDC dc, int x, int y)
{
    static const int8_t rows[7][2] = {{6, 7}, {5, 7}, {0, 1}, {0, 2}, {1, 5}, {2, 4}, {3, 3}};
    int i;

    for (i = 0; i < 7; i++)
        ctl_fill(dc, x + rows[i][0], y + i, x + rows[i][1] + 1, y + i + 1, GetTextColor(dc));
    ctl_fill(dc, x + 4, y + 2, x + 6, y + 3, GetTextColor(dc));
}

static void draw_popup_item(HDC dc, const Menu *mn, int i, int hot)
{
    const Item *it = &mn->item[i];
    const RECT *r = &it->r;
    int k = tab_at(it->text), y = r->top + (ITEM_H - font_h(dc)) / 2;

    ctl_fill(dc, r->left, r->top, r->right, r->bottom, GetSysColor(hot ? COLOR_HIGHLIGHT : COLOR_MENU));
    if (it->flags & MF_SEPARATOR) {
        ctl_fill(dc, r->left, r->top + SEP_H / 2, r->right, r->top + SEP_H / 2 + 1, GetSysColor(COLOR_MENUTEXT));
        return;
    }
    item_colours(dc, it, hot);
    if (it->flags & MF_CHECKED)
        draw_check(dc, r->left + 3, r->top + (ITEM_H - 7) / 2);
    ctl_label(dc, r->left + CHECK_W, y, it->text, k, 0, 1);
    if (it->text[k])
        ctl_label(dc, mn->tab_x, y, it->text + k + 1, (int)SDL_strlen(it->text + k + 1), 0, 1);
}

static LRESULT popup_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    Menu *mn = menu_get(t.popup);
    PAINTSTRUCT ps;
    HFONT old;
    HDC dc;
    RECT r;
    int i;

    switch (msg) {
    case WM_PAINT:
        BeginPaint(h, &ps);
        EndPaint(h, &ps);
        if (h != t.popup_wnd || !mn)
            return 0;
        dc = menu_dc(h, 0, &old);
        GetClientRect(h, &r);
        FrameRect(dc, &r, GetStockObject(BLACK_BRUSH));
        for (i = 0; i < mn->n; i++)
            draw_popup_item(dc, mn, i, i == t.sel);
        release_dc(h, dc, old);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    }
    return DefWindowProc(h, msg, wp, lp);
}

void menu_register(void)
{
    WNDCLASS wc;

    memset(&wc, 0, sizeof wc);
    wc.style = CS_SAVEBITS;
    wc.lpfnWndProc = popup_proc;
    wc.lpszClassName = POPUP_CLASS;
    RegisterClass(&wc);
}

/* The menu loop. */
static int bar_count(void)
{
    Menu *mn = menu_get(t.bar);

    return mn ? mn->n : 0;
}

static HMENU bar_menu(int i)
{
    return i == SYS_SEL ? t.sys : GetSubMenu(t.bar, (int16_t)i);
}

/* The next title of the bar row in direction dir, round. */
static int bar_next(int i, int dir)
{
    int first = t.sys ? SYS_SEL : 0, n = bar_count() - first;

    if (n <= 0)
        return NO_SEL;
    return first + ((i - first + dir) % n + n) % n;
}

static void draw_bar_sel(int i, int hot)
{
    Wnd *w = wnd_get(t.owner);
    Menu *mn = menu_get(t.bar);
    HFONT old;
    HDC dc;
    RECT bar;

    if (!w || i == NO_SEL || (i >= 0 && (!mn || i >= mn->n)))
        return;
    dc = menu_dc(t.owner, 1, &old);
    if (i == SYS_SEL) {
        menu_paint_sysbox(w, dc, hot);
    } else {
        wnd_menu_rect(w, &bar);
        layout_bar(mn, dc, &bar);
        draw_bar_item(dc, &mn->item[i], hot);
    }
    release_dc(t.owner, dc, old);
}

static void menu_select(WPARAM wp, UINT flags, HMENU in, int mouse)
{
    flags = (flags & MF_STATE) | MF_HILITE | (in == t.sys && t.sys ? MF_SYSMENU : 0) | (mouse ? MF_MOUSESELECT : 0);
    SendMessage(t.owner, WM_MENUSELECT, wp, MAKELONG(flags, in));
}

static void select_bar(int i, int mouse)
{
    Item *it;

    if (i == t.bar_sel)
        return;
    draw_bar_sel(t.bar_sel, 0);
    t.bar_sel = i;
    draw_bar_sel(i, 1);
    if (i == SYS_SEL)
        menu_select(t.sys, MF_POPUP, t.sys, mouse);
    else if ((it = find(menu_get(t.bar), (UINT)i, MF_BYPOSITION)) != NULL)
        menu_select(it->id, it->flags, t.bar, mouse);
}

static void select_item(int i, int mouse)
{
    Menu *mn = menu_get(t.popup);
    HFONT old;
    HDC dc;

    if (!mn || i == t.sel)
        return;
    dc = menu_dc(t.popup_wnd, 0, &old);
    if (t.sel >= 0)
        draw_popup_item(dc, mn, t.sel, 0);
    t.sel = i;
    if (i >= 0)
        draw_popup_item(dc, mn, i, 1);
    release_dc(t.popup_wnd, dc, old);
    if (i >= 0)
        menu_select(mn->item[i].id, mn->item[i].flags, t.popup, mouse);
}

/* The next item that is not a separator, round; -1 when none. */
static int next_item(int i, int dir)
{
    Menu *mn = menu_get(t.popup);
    int k;

    if (i < 0)
        i = dir > 0 ? -1 : mn->n;
    for (k = 1; k <= mn->n; k++) {
        int j = ((i + dir * k) % mn->n + mn->n) % mn->n;
        if (!(mn->item[j].flags & MF_SEPARATOR))
            return j;
    }
    return -1;
}

static void close_popup(void)
{
    if (t.popup_wnd)
        DestroyWindow(t.popup_wnd);
    t.popup_wnd = 0;
    t.popup = 0;
    t.sel = NO_SEL;
}

/* Opens popup m at screen (x, y), kept on the screen; index is its place
 * in the bar, for WM_INITMENUPOPUP. */
static void open_popup(HMENU m, int index, int x, int y)
{
    Menu *mn = menu_get(m);
    HFONT old;
    HDC dc;

    if (!mn)
        return;
    if (m == t.sys)
        sysmenu_state(t.owner, m);
    SendMessage(t.owner, WM_INITMENUPOPUP, m, MAKELONG(index, m == t.sys && t.sys));
    if (!menu_get(m) || !t.running)
        return;
    dc = menu_dc(0, 0, &old);
    layout_popup(mn, dc);
    release_dc(0, dc, old);
    x = SDL_max(0, SDL_min(x, GetSystemMetrics(SM_CXSCREEN) - mn->width));
    y = SDL_max(0, SDL_min(y, GetSystemMetrics(SM_CYSCREEN) - mn->height));
    t.popup = m;
    t.sel = NO_SEL;
    t.popup_wnd = CreateWindow(POPUP_CLASS, "", WS_POPUP, (int16_t)x, (int16_t)y, (int16_t)mn->width,
                               (int16_t)mn->height, t.owner, 0, 0, NULL);
    ShowWindow(t.popup_wnd, SW_SHOWNA);
    UpdateWindow(t.popup_wnd);
}

/* Selects title i of the bar row and opens its popup under it, with the
 * first item selected when the keyboard asked. */
static void open_bar(int i, int first, int mouse)
{
    Wnd *w = wnd_get(t.owner);
    HMENU m = bar_menu(i);
    RECT r;
    Item *it;

    close_popup();
    select_bar(i, mouse);
    if (!m || !w)
        return;
    if (i == SYS_SEL) {
        wnd_caption_rect(w, &r);
        open_popup(m, 0, w->rect.left + r.left, w->rect.top + r.bottom);
    } else {
        wnd_menu_rect(w, &r);
        it = &menu_get(t.bar)->item[i];
        open_popup(m, i, w->rect.left + it->r.left, w->rect.top + r.bottom - 1);
    }
    if (first)
        select_item(next_item(-1, 1), mouse);
}

static void end_loop(void)
{
    t.running = 0;
}

static void choose(int i)
{
    Menu *mn = menu_get(t.popup);
    Item *it = mn && i >= 0 && i < mn->n ? &mn->item[i] : NULL;

    if (!it || it->flags & (MF_GRAYED | MF_DISABLED | MF_SEPARATOR | MF_POPUP))
        return;
    t.chosen = 1;
    t.cmd = it->id;
    t.cmd_sys = t.popup == t.sys && t.sys;
    end_loop();
}

/* The item of the open popup under screen point p (NO_SEL on a
 * separator or outside). */
static int popup_item_at(POINT p)
{
    Wnd *w = wnd_get(t.popup_wnd);
    Menu *mn = menu_get(t.popup);
    int i;

    if (!w || !mn || !PtInRect(&w->rect, p))
        return NO_SEL;
    p.x = (int16_t)(p.x - w->client.left);
    p.y = (int16_t)(p.y - w->client.top);
    for (i = 0; i < mn->n; i++)
        if (PtInRect(&mn->item[i].r, p))
            return mn->item[i].flags & MF_SEPARATOR ? NO_SEL : i;
    return NO_SEL;
}

static int in_popup(POINT p)
{
    Wnd *w = wnd_get(t.popup_wnd);

    return w && PtInRect(&w->rect, p);
}

/* The title of owner's bar row (menu bar, system menu) under screen
 * point p. */
static int bar_at(HWND owner, HMENU bar, HMENU sys, POINT p)
{
    Wnd *w = wnd_get(owner);
    Menu *mn = menu_get(bar);
    int i;

    if (!w)
        return NO_SEL;
    switch (wnd_hit(w, p.x, p.y)) {
    case HTSYSMENU:
        return sys ? SYS_SEL : NO_SEL;
    case HTMENU:
        p.x = (int16_t)(p.x - w->rect.left);
        p.y = (int16_t)(p.y - w->rect.top);
        for (i = 0; mn && i < mn->n; i++)
            if (PtInRect(&mn->item[i].r, p))
                return i;
        return NO_SEL;
    }
    return NO_SEL;
}

static int is_mouse(UINT msg)
{
    return (msg >= WM_MOUSEMOVE && msg <= WM_RBUTTONDBLCLK) || (msg >= WM_NCMOUSEMOVE && msg <= WM_NCMOUSEMOVE + 6);
}

/* Mouse input, by kind (0 move, 1 left down, 2 left up, 3 left double
 * click, 4 right down, 5 right up, 6 right double click). */
static void track_mouse(UINT msg, POINT p)
{
    int kind = (int)(msg >= WM_MOUSEMOVE ? msg - WM_MOUSEMOVE : msg - WM_NCMOUSEMOVE);
    int bar = bar_at(t.owner, t.bar, t.sys, p);

    switch (kind) {
    case 1:
    case 3:
        t.button = 1;
        if (in_popup(p))
            select_item(popup_item_at(p), 1);
        else if (bar == NO_SEL || (bar == t.bar_sel && t.popup))
            end_loop();
        else
            open_bar(bar, 0, 1);
        break;
    case 4:
    case 6:
        if (!in_popup(p) && bar == NO_SEL)
            end_loop();
        break;
    case 2:
        if (!t.button)
            break;
        t.button = 0;
        t.cmd_lp = MAKELONG(p.x, p.y);
        if (in_popup(p))
            choose(popup_item_at(p));
        else if (bar == NO_SEL)
            end_loop();
        break;
    case 0:
        if (in_popup(p))
            select_item(popup_item_at(p), 1);
        else if (bar != NO_SEL && bar != t.bar_sel && (t.popup || t.button))
            open_bar(bar, 0, 1);
        else if (t.popup)
            select_item(NO_SEL, 1);
        break;
    }
}

static int mnemonic(HMENU m, int ch)
{
    Menu *mn = menu_get(m);
    int i;

    for (i = 0; mn && i < mn->n; i++) {
        const char *a = SDL_strchr(mn->item[i].text, '&');
        if (a && SDL_toupper((unsigned char)a[1]) == SDL_toupper(ch) && !(mn->item[i].flags & MF_SEPARATOR))
            return i;
    }
    return -1;
}

static void track_key(int vk)
{
    int bar_row = t.bar_sel != NO_SEL;

    switch (vk) {
    case VK_MENU:
    case VK_F10:
        t.menu_key = 1;
        break;
    case VK_ESCAPE:
        if (t.popup && bar_row)
            close_popup();
        else
            end_loop();
        break;
    case VK_LEFT:
    case VK_RIGHT:
        if (!bar_row)
            break;
        if (t.popup)
            open_bar(bar_next(t.bar_sel, vk == VK_LEFT ? -1 : 1), 1, 0);
        else
            select_bar(bar_next(t.bar_sel, vk == VK_LEFT ? -1 : 1), 0);
        break;
    case VK_UP:
    case VK_DOWN:
        if (t.popup)
            select_item(next_item(t.sel, vk == VK_UP ? -1 : 1), 0);
        else if (bar_row)
            open_bar(t.bar_sel, 1, 0);
        break;
    case VK_RETURN:
        if (t.popup)
            choose(t.sel);
        else if (bar_row)
            open_bar(t.bar_sel, 1, 0);
        break;
    }
}

static void track_char(int ch)
{
    int i;

    if (ch <= ' ')
        return;
    if (t.popup) {
        if ((i = mnemonic(t.popup, ch)) < 0) {
            MessageBeep(0);
            return;
        }
        select_item(i, 0);
        choose(i);
    } else if ((i = mnemonic(t.bar, ch)) >= 0) {
        open_bar(i, 1, 0);
    } else {
        MessageBeep(0);
    }
}

/* Starts the loop on owner: the mouse is the menu's, WM_INITMENU. */
static void begin(HWND owner, HMENU bar, HMENU sys, HMENU init)
{
    memset(&t, 0, sizeof t);
    t.running = 1;
    t.owner = owner;
    t.bar = bar;
    t.sys = sys;
    t.bar_sel = t.sel = NO_SEL;
    t.old_capture = SetCapture(owner);
    SendMessage(owner, WM_INITMENU, init, 0);
}

static void run_loop(void)
{
    MSG m;

    while (t.running) {
        if (!GetMessage(&m, 0, 0, 0)) {
            PostQuitMessage((int16_t)m.wParam);
            break;
        }
        if (!IsWindow(t.owner))
            break;
        if (is_mouse(m.message)) {
            track_mouse(m.message, m.pt);
        } else if (m.message == WM_KEYDOWN || m.message == WM_SYSKEYDOWN) {
            TranslateMessage(&m);
            t.key = (int)m.wParam;
            track_key(t.key);
            t.key_ended = !t.running;
        } else if (m.message == WM_CHAR || m.message == WM_SYSCHAR) {
            track_char((int)m.wParam);
            t.key_ended = !t.running;
        } else if (m.message == WM_KEYUP || m.message == WM_SYSKEYUP) {
            if ((m.wParam == VK_MENU || m.wParam == VK_F10) && t.menu_key)
                end_loop();
        } else {
            DispatchMessage(&m);
        }
    }
    close_popup();
    draw_bar_sel(t.bar_sel, 0);
    t.bar_sel = NO_SEL;
    t.running = 0;
    if (t.key_ended)
        input_eat_key_up(t.key);
    if (IsWindow(t.owner)) {
        ReleaseCapture();
        if (t.old_capture)
            SetCapture(t.old_capture);
        SendMessage(t.owner, WM_MENUSELECT, 0, MAKELONG(0xffff, 0));
        if (t.chosen)
            PostMessage(t.owner, t.cmd_sys ? WM_SYSCOMMAND : WM_COMMAND, (WPARAM)t.cmd, t.cmd_lp);
    }
}

void menu_syscommand(HWND h, WPARAM cmd, LPARAM lp)
{
    Wnd *w = wnd_get(h);
    HMENU bar, sys;
    POINT p;
    int i;

    if (!w || t.running)
        return;
    bar = menu_is(w->id) ? w->id : 0;
    sys = GetSystemMenu(h, 0);
    if ((cmd & 0xfff0) == SC_MOUSEMENU) {
        p.x = (int16_t)LOWORD(lp);
        p.y = (int16_t)HIWORD(lp);
        i = (cmd & 0x0f) == HTSYSMENU ? (sys ? SYS_SEL : NO_SEL) : bar_at(h, bar, sys, p);
        if (i == NO_SEL)
            return;
        begin(h, bar, sys, i == SYS_SEL ? sys : bar);
        t.button = 1;
        open_bar(i, 0, 1);
    } else if (lp == 0 && (bar || sys)) {
        begin(h, bar, sys, bar ? bar : sys);
        select_bar(bar ? 0 : SYS_SEL, 0);
    } else if (lp == ' ' && sys) {
        begin(h, bar, sys, sys);
        open_bar(SYS_SEL, 1, 0);
    } else if (lp != 0 && lp != ' ' && (i = mnemonic(bar, (int)lp)) >= 0) {
        begin(h, bar, sys, bar);
        open_bar(i, 1, 0);
    } else {
        if (lp)
            MessageBeep(0);
        return;
    }
    run_loop();
}

BOOL TrackPopupMenu(HMENU m, UINT flags, int16_t x, int16_t y, int16_t reserved, HWND h, const RECT *r)
{
    (void)flags;
    (void)reserved;
    (void)r;
    if (t.running || !menu_is(m) || !IsWindow(h))
        return 0;
    begin(h, 0, 0, m);
    t.button = GetKeyState(VK_LBUTTON) < 0;
    open_popup(m, 0, x, y);
    run_loop();
    return 1;
}
