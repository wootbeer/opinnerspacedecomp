/* Game controller on SDL3: the first gamepad SDL knows the layout of
 * (its standard mapping: Xbox, PlayStation, Switch, Steam Deck ...),
 * else the first other joystick, whose buttons and hat are taken in the
 * usual order.  Controllers may come and go at any time: whenever SDL
 * tells of one added or removed, the choice is made again. */
#include "platform/platform.h"

#include <SDL3/SDL.h>

#define TRIGGER_DOWN 16384      /* a trigger counts as held from half way */

static struct {
    int started;                /* 1: watching, -1: no controllers here */
    SDL_AtomicInt changed;      /* a controller was added or removed */
    SDL_Gamepad *gamepad;
    SDL_Joystick *joystick;     /* the gamepad's, or one without a mapping */
} pad;

static const struct {
    SDL_GamepadButton sdl;
    int button;
} gamepad_buttons[] = {
    {SDL_GAMEPAD_BUTTON_SOUTH, PAD_A}, {SDL_GAMEPAD_BUTTON_EAST, PAD_B},
    {SDL_GAMEPAD_BUTTON_WEST, PAD_X}, {SDL_GAMEPAD_BUTTON_NORTH, PAD_Y},
    {SDL_GAMEPAD_BUTTON_BACK, PAD_BACK}, {SDL_GAMEPAD_BUTTON_START, PAD_START},
    {SDL_GAMEPAD_BUTTON_LEFT_STICK, PAD_LEFT_STICK}, {SDL_GAMEPAD_BUTTON_RIGHT_STICK, PAD_RIGHT_STICK},
    {SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, PAD_LEFT_SHOULDER},
    {SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, PAD_RIGHT_SHOULDER},
    {SDL_GAMEPAD_BUTTON_DPAD_UP, PAD_UP}, {SDL_GAMEPAD_BUTTON_DPAD_DOWN, PAD_DOWN},
    {SDL_GAMEPAD_BUTTON_DPAD_LEFT, PAD_LEFT}, {SDL_GAMEPAD_BUTTON_DPAD_RIGHT, PAD_RIGHT},
};

static const struct {
    SDL_GamepadAxis sdl;
    int button;
} gamepad_triggers[] = {
    {SDL_GAMEPAD_AXIS_LEFT_TRIGGER, PAD_LEFT_TRIGGER}, {SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, PAD_RIGHT_TRIGGER},
};

/* A joystick's buttons by number [uncertain: the order most PC pads
 * without a mapping report], and its first hat as the d-pad. */
static const int joystick_buttons[] = {
    PAD_A, PAD_B, PAD_X, PAD_Y, PAD_LEFT_SHOULDER, PAD_RIGHT_SHOULDER, PAD_BACK, PAD_START,
    PAD_LEFT_STICK, PAD_RIGHT_STICK,
};

static const struct {
    Uint8 hat;
    int button;
} joystick_hat[] = {
    {SDL_HAT_UP, PAD_UP}, {SDL_HAT_DOWN, PAD_DOWN}, {SDL_HAT_LEFT, PAD_LEFT}, {SDL_HAT_RIGHT, PAD_RIGHT},
};

static void close_pad(void)
{
    if (pad.gamepad)
        SDL_CloseGamepad(pad.gamepad);
    else if (pad.joystick)
        SDL_CloseJoystick(pad.joystick);
    pad.gamepad = NULL;
    pad.joystick = NULL;
}

static void scan(void)
{
    SDL_JoystickID *ids;
    int n;

    if ((ids = SDL_GetGamepads(&n)) != NULL && n > 0) {
        SDL_Gamepad *g = SDL_OpenGamepad(ids[0]);
        if (g) {
            close_pad();
            pad.gamepad = g;
            pad.joystick = SDL_GetGamepadJoystick(g);
        }
    }
    SDL_free(ids);
    if (pad.joystick || (ids = SDL_GetJoysticks(&n)) == NULL)
        return;
    if (n > 0)
        pad.joystick = SDL_OpenJoystick(ids[0]);
    SDL_free(ids);
}

/* Called by SDL for every event as it is queued, on any thread. */
static bool SDLCALL watch(void *user, SDL_Event *e)
{
    (void)user;
    if (e->type == SDL_EVENT_JOYSTICK_ADDED || e->type == SDL_EVENT_JOYSTICK_REMOVED)
        SDL_SetAtomicInt(&pad.changed, 1);
    return true;
}

/* The controller in use, chosen again after a change. */
static int connected(void)
{
    if (!pad.started) {
        SDL_SetAtomicInt(&pad.changed, 1);
        pad.started = SDL_InitSubSystem(SDL_INIT_GAMEPAD) && SDL_AddEventWatch(watch, NULL) ? 1 : -1;
    }
    if (pad.started < 0)
        return 0;
    if (SDL_SetAtomicInt(&pad.changed, 0)) {
        if (pad.joystick && !SDL_JoystickConnected(pad.joystick))
            close_pad();
        if (!pad.gamepad)
            scan();
    }
    return pad.joystick != NULL;
}

static uint16_t axis(Sint16 v)
{
    return (uint16_t)(v + 32768);
}

static uint32_t gamepad_held(void)
{
    uint32_t held = 0;
    size_t i;

    for (i = 0; i < SDL_arraysize(gamepad_buttons); i++)
        if (SDL_GetGamepadButton(pad.gamepad, gamepad_buttons[i].sdl))
            held |= 1u << gamepad_buttons[i].button;
    for (i = 0; i < SDL_arraysize(gamepad_triggers); i++)
        if (SDL_GetGamepadAxis(pad.gamepad, gamepad_triggers[i].sdl) >= TRIGGER_DOWN)
            held |= 1u << gamepad_triggers[i].button;
    return held;
}

static uint32_t joystick_held(void)
{
    Uint8 hat = SDL_GetNumJoystickHats(pad.joystick) > 0 ? SDL_GetJoystickHat(pad.joystick, 0) : 0;
    uint32_t held = 0;
    size_t i;

    for (i = 0; i < SDL_arraysize(joystick_buttons); i++)
        if (SDL_GetJoystickButton(pad.joystick, (int)i))
            held |= 1u << joystick_buttons[i];
    for (i = 0; i < SDL_arraysize(joystick_hat); i++)
        if (hat & joystick_hat[i].hat)
            held |= 1u << joystick_hat[i].button;
    return held;
}

int platform_pad_read(PlatformPad *out)
{
    SDL_zerop(out);
    out->x = out->y = 32768;
    if (!connected())
        return 0;
    if (pad.gamepad) {
        out->x = axis(SDL_GetGamepadAxis(pad.gamepad, SDL_GAMEPAD_AXIS_LEFTX));
        out->y = axis(SDL_GetGamepadAxis(pad.gamepad, SDL_GAMEPAD_AXIS_LEFTY));
        out->buttons = gamepad_held();
    } else {
        if (SDL_GetNumJoystickAxes(pad.joystick) >= 2) {
            out->x = axis(SDL_GetJoystickAxis(pad.joystick, 0));
            out->y = axis(SDL_GetJoystickAxis(pad.joystick, 1));
        }
        out->buttons = joystick_held();
    }
    return 1;
}
