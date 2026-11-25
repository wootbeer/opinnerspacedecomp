/* The game controller (platform_pad_read) as the game knew one: the
 * 1994 joystick on the game port, which ISPACE.DLL reads (ispace_joy.c),
 * and keys for its buttons.  The left stick is joystick A's stick, the
 * face buttons A and B its buttons 1 and 2, X and Y buttons 3 and 4 of
 * a four-button stick (on a two-button one they were joystick B's, not
 * there).  Every button also sends the keys of a table (INSPACE.INI
 * [Port] Pad<name>= overrides them), except the joystick's buttons while
 * the game reads the joystick: then they are only the joystick's. */
#include <SDL3/SDL_stdinc.h>

#include "user.h"
#include "platform/platform.h"

#define COUNT_SHIFT 6           /* a stick's travel as loop counts 0-1023 [port's choice] */
#define JOYSTICK_MS 500         /* after a read the game counts as reading the joystick */

static const int port_buttons[4] = {PAD_A, PAD_B, PAD_X, PAD_Y};

/* Each button's INI name (Pad<name>) and its keys by default: what the
 * game uses them for in a wave, in dialogs and lists. */
static const struct {
    const char *name;
    const char *keys;
} button_keys[PAD_BUTTONS] = {
    [PAD_A] = {"A", "Return"},                  /* OK, choose; fire weapon */
    [PAD_B] = {"B", "Escape"},                  /* cancel; leave the wave */
    [PAD_X] = {"X", "Space"},                   /* press a button, tick a box; fire gun */
    [PAD_Y] = {"Y", "Tab"},                     /* next control; change weapon */
    [PAD_BACK] = {"Back", "Escape"},
    [PAD_START] = {"Start", "P"},               /* pause */
    [PAD_LEFT_STICK] = {"LeftStick", "Return"}, /* also while A is the joystick's */
    [PAD_RIGHT_STICK] = {"RightStick", "Alt+G"},        /* Game Settings */
    [PAD_LEFT_SHOULDER] = {"LeftShoulder", "H"},        /* call the ambulance */
    [PAD_RIGHT_SHOULDER] = {"RightShoulder", "R"},      /* new ship target */
    [PAD_UP] = {"Up", "Up"},                    /* thrust */
    [PAD_DOWN] = {"Down", "Down"},              /* brake */
    [PAD_LEFT] = {"Left", "Left"},              /* turn */
    [PAD_RIGHT] = {"Right", "Right"},
    [PAD_LEFT_TRIGGER] = {"LeftTrigger", "Ctrl"},       /* turbo thrust */
    [PAD_RIGHT_TRIGGER] = {"RightTrigger", "CapsLock"}, /* cloak or shield */
};

static struct {
    int loaded;
    uint32_t keys[PAD_BUTTONS][WIN_KEYS];
    int count[PAD_BUTTONS];
    uint32_t sent;              /* buttons whose keys are down */
    uint32_t port_read;         /* when the game port was read last */
    int port_count;             /* how many buttons it was read with */
} pad;

/* The table with the INI's overrides ("None": no keys). */
static void load_keys(void)
{
    char key[32], spec[64];
    int i;

    pad.loaded = 1;
    for (i = 0; i < PAD_BUTTONS; i++) {
        SDL_snprintf(key, sizeof key, "Pad%s", button_keys[i].name);
        if (!port_setting(key, spec, sizeof spec))
            SDL_strlcpy(spec, button_keys[i].keys, sizeof spec);
        pad.count[i] = SDL_strcasecmp(spec, "None") ? win_key_names(spec, pad.keys[i]) : 0;
    }
}

static void send_keys(int button, int down)
{
    int k, n = pad.count[button];

    for (k = 0; k < n; k++)
        input_key(pad.keys[button][down ? k : n - 1 - k], down);
}

int pad_game_port(uint16_t count[2], uint16_t *buttons, int n)
{
    PlatformPad p;
    int i;

    pad.port_read = platform_time_ms();
    pad.port_count = n;
    if (!platform_pad_read(&p))
        return 0;
    count[0] = (uint16_t)(p.x >> COUNT_SHIFT);
    count[1] = (uint16_t)(p.y >> COUNT_SHIFT);
    *buttons = 0;
    for (i = 0; i < n; i++)
        if (p.buttons & 1u << port_buttons[i])
            *buttons |= (uint16_t)(1 << i);
    return 1;
}

void pad_poll(void)
{
    PlatformPad p;
    uint32_t held, changed;
    int i;

    platform_pad_read(&p);
    held = p.buttons;
    if (platform_time_ms() - pad.port_read < JOYSTICK_MS)
        for (i = 0; i < pad.port_count; i++)
            held &= ~(1u << port_buttons[i]);
    if (!(changed = held ^ pad.sent))
        return;
    if (!pad.loaded)
        load_keys();
    for (i = 0; i < PAD_BUTTONS; i++)
        if (changed & 1u << i)
            send_keys(i, (held >> i) & 1);
    pad.sent = held;
}
