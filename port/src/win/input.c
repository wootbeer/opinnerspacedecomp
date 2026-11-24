/* Keyboard and mouse: SDL events become Windows 3.1 input messages
 * (US keyboard layout), the key state table and the cursor position. */
#include <SDL3/SDL_events.h>
#include <string.h>

#include "user.h"
#include "platform/platform.h"
#include "video.h"

#define FRAME_MS 16
#define KF_ALT 0x20000000L      /* lParam: the context code (Alt held) */
#define KF_REPEAT 0x40000000L   /* lParam: the key was already down */
#define KF_UP 0x80000000L       /* lParam: transition (key released) */

static BYTE keys[256];
static POINT cursor;
static uint32_t last_frame;
static int alt_alone;           /* Alt pressed with no other key since */

/* SDL key to virtual-key code. */
static const struct {
    SDL_Keycode key;
    uint8_t vk;
} vk_table[] = {
    {SDLK_ESCAPE, VK_ESCAPE}, {SDLK_RETURN, VK_RETURN}, {SDLK_BACKSPACE, VK_BACK},
    {SDLK_TAB, VK_TAB}, {SDLK_SPACE, VK_SPACE}, {SDLK_LEFT, VK_LEFT}, {SDLK_UP, VK_UP},
    {SDLK_RIGHT, VK_RIGHT}, {SDLK_DOWN, VK_DOWN}, {SDLK_INSERT, 0x2d}, {SDLK_DELETE, VK_DELETE},
    {SDLK_HOME, VK_HOME}, {SDLK_END, VK_END}, {SDLK_PAGEUP, VK_PRIOR}, {SDLK_PAGEDOWN, VK_NEXT},
    {SDLK_LSHIFT, VK_SHIFT}, {SDLK_RSHIFT, VK_SHIFT}, {SDLK_LCTRL, VK_CONTROL},
    {SDLK_RCTRL, VK_CONTROL}, {SDLK_LALT, VK_MENU}, {SDLK_RALT, VK_MENU},
    {SDLK_CAPSLOCK, VK_CAPITAL}, {SDLK_PAUSE, 0x13}, {SDLK_KP_MULTIPLY, 0x6a},
    {SDLK_KP_PLUS, VK_ADD}, {SDLK_KP_MINUS, VK_SUBTRACT}, {SDLK_KP_PERIOD, 0x6e},
    {SDLK_KP_DIVIDE, 0x6f}, {SDLK_KP_ENTER, VK_RETURN}, {SDLK_SEMICOLON, 0xba},
    {SDLK_EQUALS, 0xbb}, {SDLK_COMMA, 0xbc}, {SDLK_MINUS, 0xbd}, {SDLK_PERIOD, 0xbe},
    {SDLK_SLASH, 0xbf}, {SDLK_GRAVE, 0xc0}, {SDLK_LEFTBRACKET, 0xdb}, {SDLK_BACKSLASH, 0xdc},
    {SDLK_RIGHTBRACKET, 0xdd}, {SDLK_APOSTROPHE, 0xde},
};

/* Characters of the keys that type one that is not their own code:
 * plain and with Shift. */
static const struct {
    uint8_t vk;
    char plain, shifted;
} char_table[] = {
    {'0', '0', ')'}, {'1', '1', '!'}, {'2', '2', '@'}, {'3', '3', '#'}, {'4', '4', '$'},
    {'5', '5', '%'}, {'6', '6', '^'}, {'7', '7', '&'}, {'8', '8', '*'}, {'9', '9', '('},
    {0xba, ';', ':'}, {0xbb, '=', '+'}, {0xbc, ',', '<'}, {0xbd, '-', '_'}, {0xbe, '.', '>'},
    {0xbf, '/', '?'}, {0xc0, '`', '~'}, {0xdb, '[', '{'}, {0xdc, '\\', '|'}, {0xdd, ']', '}'},
    {0xde, '\'', '"'}, {VK_SPACE, ' ', ' '}, {VK_RETURN, 13, 13}, {VK_ESCAPE, 27, 27},
    {VK_BACK, 8, 8}, {VK_TAB, 9, 9}, {0x6a, '*', '*'}, {VK_ADD, '+', '+'},
    {VK_SUBTRACT, '-', '-'}, {0x6e, '.', '.'}, {0x6f, '/', '/'},
};

static int vk_of(SDL_Keycode k)
{
    size_t i;

    if (k >= 'a' && k <= 'z')
        return (int)(k - 'a' + 'A');
    if (k >= '0' && k <= '9')
        return (int)k;
    if (k >= SDLK_F1 && k <= SDLK_F12)
        return 0x70 + (int)(k - SDLK_F1);
    if (k >= SDLK_KP_1 && k <= SDLK_KP_9)
        return 0x61 + (int)(k - SDLK_KP_1);
    if (k == SDLK_KP_0)
        return 0x60;
    for (i = 0; i < sizeof vk_table / sizeof vk_table[0]; i++)
        if (vk_table[i].key == k)
            return vk_table[i].vk;
    return 0;
}

/* The character a key types with the current shift state, or 0. */
static int char_of(int vk)
{
    int shift = (keys[VK_SHIFT] & 0x80) != 0;
    size_t i;

    if (vk >= 'A' && vk <= 'Z')
        return shift != (keys[VK_CAPITAL] & 1) ? vk : vk + 'a' - 'A';
    if (vk >= 0x60 && vk <= 0x69)
        return '0' + vk - 0x60;
    for (i = 0; i < sizeof char_table / sizeof char_table[0]; i++)
        if (char_table[i].vk == vk)
            return (uint8_t)(shift ? char_table[i].shifted : char_table[i].plain);
    return 0;
}

/* WM_KEYDOWN/UP, or WM_SYSKEYDOWN/UP while Alt is held (and for F10,
 * and for releasing Alt when no other key came between). */
static void post_key(int vk, int down, int repeat)
{
    int alt = (keys[VK_MENU] & 0x80) != 0;
    int sys = (alt && !(keys[VK_CONTROL] & 0x80)) || vk == VK_F10 || (vk == VK_MENU && alt_alone);
    UINT msg = sys ? (down ? WM_SYSKEYDOWN : WM_SYSKEYUP) : (down ? WM_KEYDOWN : WM_KEYUP);
    LPARAM lp = 1 | (alt ? KF_ALT : 0) | (repeat || !down ? KF_REPEAT : 0) | (down ? 0 : KF_UP);
    HWND target = user_key_target();

    if (target)
        PostMessage(target, msg, (WPARAM)vk, lp);
}

static void on_key(const SDL_KeyboardEvent *e)
{
    int vk = vk_of(e->key);

    if (!vk)
        return;
    if (e->down) {
        if (!(keys[vk] & 0x80))
            keys[vk] ^= 1;
        keys[vk] |= 0x80;
        alt_alone = vk == VK_MENU ? !e->repeat || alt_alone : 0;
        post_key(vk, 1, e->repeat);
    } else {
        post_key(vk, 0, 0);
        keys[vk] &= 0x7f;
        if (vk == VK_MENU)
            alt_alone = 0;
    }
}

static void on_mouse(UINT msg, float wx, float wy)
{
    WPARAM wp = 0;
    int x, y;
    HWND h;

    video_map_point(wx, wy, &x, &y);
    cursor.x = (int16_t)x;
    cursor.y = (int16_t)y;
    if (keys[VK_LBUTTON] & 0x80)
        wp |= MK_LBUTTON;
    if (keys[VK_RBUTTON] & 0x80)
        wp |= MK_RBUTTON;
    if ((h = wnd_at(x, y)) != 0 || msg != WM_MOUSEMOVE)
        wnd_send_click(h, msg, x, y, wp);
}

static void on_button(const SDL_MouseButtonEvent *e)
{
    int right = e->button == SDL_BUTTON_RIGHT;
    int vk = right ? VK_RBUTTON : VK_LBUTTON;
    UINT msg;

    if (e->down) {
        keys[vk] |= 0x80;
        msg = right ? WM_RBUTTONDOWN : e->clicks == 2 ? WM_LBUTTONDBLCLK : WM_LBUTTONDOWN;
    } else {
        keys[vk] &= 0x7f;
        msg = right ? WM_RBUTTONUP : WM_LBUTTONUP;
    }
    on_mouse(msg, e->x, e->y);
}

void win_pump(void)
{
    SDL_Event ev;
    uint32_t now;
    HWND target;

    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
        case SDL_EVENT_QUIT:
            if ((target = GetActiveWindow()) != 0)
                PostMessage(target, WM_CLOSE, 0, 0);
            else
                PostQuitMessage(0);
            break;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            on_key(&ev.key);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            on_mouse(WM_MOUSEMOVE, ev.motion.x, ev.motion.y);
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            on_button(&ev.button);
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

/* WM_CHAR for WM_KEYDOWN, WM_SYSCHAR for WM_SYSKEYDOWN, when the key
 * types a character (Ctrl+letter gives the control code). */
BOOL TranslateMessage(const MSG *m)
{
    int c;

    if (m->message != WM_KEYDOWN && m->message != WM_SYSKEYDOWN)
        return 0;
    c = char_of((int)m->wParam);
    if (keys[VK_CONTROL] & 0x80 && m->wParam >= 'A' && m->wParam <= 'Z')
        c = (int)m->wParam - 'A' + 1;
    if (!c)
        return 0;
    return PostMessage(m->hwnd, m->message == WM_KEYDOWN ? WM_CHAR : WM_SYSCHAR, (WPARAM)c, m->lParam);
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
