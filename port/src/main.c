/* Operation: Inner Space, native port: sets up the screen and the native
 * Windows calls, gives the globals their initial values from INSPACE.EXE
 * and runs the game's WinMain (2:0000). */
#include "platform/platform.h"
#include "video.h"
#include "win/win.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int frame_limit = -1;        /* --frames N: run N frames, then exit */
static const char *dump_path;       /* --dump FILE: save the last frame */
static int shot_every;              /* --shots N: also save every Nth frame */
static int frame_count;

/* --keys "FRAME:KEY,...": keys pressed at a frame and released two
 * frames later (or HOLD frames later: FRAME:KEY/HOLD), for headless
 * runs.  KEY is an SDL key name, with modifiers before it:
 * "1600:Escape,1700:Alt+X,1800:Up/120". */
#define MAX_KEYS 256
static struct {
    int frame, hold, n;
    uint32_t key[WIN_KEYS];
} keys[MAX_KEYS];
static int key_count;

static int parse_keys(const char *spec)
{
    char buf[4096], *item, *save, *slash;

    SDL_strlcpy(buf, spec, sizeof buf);
    for (item = SDL_strtok_r(buf, ",", &save); item && key_count < MAX_KEYS;
         item = SDL_strtok_r(NULL, ",", &save)) {
        char *colon = SDL_strchr(item, ':');
        if (!colon)
            return 0;
        *colon = 0;
        keys[key_count].frame = SDL_atoi(item);
        slash = SDL_strchr(colon + 1, '/');
        keys[key_count].hold = slash ? SDL_atoi(slash + 1) : 2;
        if (slash)
            *slash = 0;
        if (!(keys[key_count].n = win_key_names(colon + 1, keys[key_count].key)))
            return 0;
        key_count++;
    }
    return 1;
}

static void push_key(SDL_Keycode k, int down)
{
    SDL_Event e;

    SDL_zero(e);
    e.type = down ? SDL_EVENT_KEY_DOWN : SDL_EVENT_KEY_UP;
    e.key.key = k;
    e.key.down = down != 0;
    SDL_PushEvent(&e);
}

static void inject_keys(void)
{
    int i, j;

    for (i = 0; i < key_count; i++) {
        if (keys[i].frame == frame_count)
            for (j = 0; j < keys[i].n; j++)
                push_key(keys[i].key[j], 1);
        if (keys[i].frame + keys[i].hold == frame_count)
            for (j = keys[i].n - 1; j >= 0; j--)
                push_key(keys[i].key[j], 0);
    }
}

/* --mouse "FRAME:X,Y[,ACTION];...": the mouse moved to framebuffer
 * point (X, Y) at frame FRAME, then ACTION: move (the default), down, up,
 * click (down, up two frames later), dclick (a double click's second
 * press, then up), rdown, rup, rclick. */
#define MAX_MOUSE 256
static struct {
    int frame, x, y;
    int button, down;           /* button 0: move only */
    int clicks;
} mouse[MAX_MOUSE];
static int mouse_count;

static int add_mouse(int frame, int x, int y, int button, int down, int clicks)
{
    if (mouse_count == MAX_MOUSE)
        return 0;
    mouse[mouse_count].frame = frame;
    mouse[mouse_count].x = x;
    mouse[mouse_count].y = y;
    mouse[mouse_count].button = button;
    mouse[mouse_count].down = down;
    mouse[mouse_count].clicks = clicks;
    mouse_count++;
    return 1;
}

static int parse_mouse(const char *spec)
{
    static const struct {
        const char *name;
        int button, down, up, clicks;   /* up: also released two frames later */
    } actions[] = {
        {"move", 0, 0, 0, 1}, {"down", SDL_BUTTON_LEFT, 1, 0, 1}, {"up", SDL_BUTTON_LEFT, 0, 0, 1},
        {"click", SDL_BUTTON_LEFT, 1, 1, 1}, {"dclick", SDL_BUTTON_LEFT, 1, 1, 2},
        {"rdown", SDL_BUTTON_RIGHT, 1, 0, 1}, {"rup", SDL_BUTTON_RIGHT, 0, 0, 1},
        {"rclick", SDL_BUTTON_RIGHT, 1, 1, 1},
    };
    char buf[4096], *item, *save;

    SDL_strlcpy(buf, spec, sizeof buf);
    for (item = SDL_strtok_r(buf, ";", &save); item; item = SDL_strtok_r(NULL, ";", &save)) {
        char action[16] = "move";
        int frame, x, y, n = SDL_sscanf(item, "%d:%d,%d,%15s", &frame, &x, &y, action);
        size_t i;
        if (n < 3)
            return 0;
        for (i = 0; i < sizeof actions / sizeof actions[0] && SDL_strcmp(actions[i].name, action); i++)
            ;
        if (i == sizeof actions / sizeof actions[0] ||
            !add_mouse(frame, x, y, actions[i].button, actions[i].down, actions[i].clicks) ||
            (actions[i].up && !add_mouse(frame + 2, x, y, actions[i].button, 0, actions[i].clicks)))
            return 0;
    }
    return 1;
}

static void inject_mouse(void)
{
    SDL_Event e;
    float wx, wy;
    int i;

    for (i = 0; i < mouse_count; i++) {
        if (mouse[i].frame != frame_count)
            continue;
        video_window_point(mouse[i].x, mouse[i].y, &wx, &wy);
        SDL_zero(e);
        e.type = SDL_EVENT_MOUSE_MOTION;
        e.motion.x = wx;
        e.motion.y = wy;
        SDL_PushEvent(&e);
        if (!mouse[i].button)
            continue;
        SDL_zero(e);
        e.type = mouse[i].down ? SDL_EVENT_MOUSE_BUTTON_DOWN : SDL_EVENT_MOUSE_BUTTON_UP;
        e.button.button = (Uint8)mouse[i].button;
        e.button.down = mouse[i].down != 0;
        e.button.clicks = (Uint8)mouse[i].clicks;
        e.button.x = wx;
        e.button.y = wy;
        SDL_PushEvent(&e);
    }
}

/* --pad "FRAME:WHAT[/HOLD],...": a virtual game controller for headless
 * runs.  WHAT is attach (a gamepad), attachraw (a joystick SDL has no
 * mapping for), detach, a button held HOLD frames (2 by default: A, B,
 * X, Y, Back, Start, LeftStick, RightStick, LeftShoulder, RightShoulder,
 * Up, Down, Left, Right, LeftTrigger, RightTrigger), or LX=V or LY=V,
 * the left stick's position (-32768 to 32767; with /HOLD back to 0
 * after HOLD frames).  "100:attach,4100:LX=32767/200,4200:A". */
#define MAX_PAD 256
enum { PAD_ATTACH, PAD_ATTACH_RAW, PAD_DETACH, PAD_BUTTON, PAD_AXIS };
static struct {
    int frame, hold, what, index, value;
} pad_items[MAX_PAD];
static int pad_count;
static struct {
    SDL_JoystickID id;
    SDL_Joystick *joystick;
    int raw;
} vpad;

/* A gamepad's buttons by name; a raw joystick's are the first four,
 * the shoulders, Back and Start, the sticks' and its hat for the
 * d-pad (platform_pad.c's order). */
static const struct {
    const char *name;
    int button, raw, trigger;   /* trigger: an axis held at its top */
    Uint8 hat;
} pad_names[] = {
    {"A", SDL_GAMEPAD_BUTTON_SOUTH, 0, -1, 0}, {"B", SDL_GAMEPAD_BUTTON_EAST, 1, -1, 0},
    {"X", SDL_GAMEPAD_BUTTON_WEST, 2, -1, 0}, {"Y", SDL_GAMEPAD_BUTTON_NORTH, 3, -1, 0},
    {"LeftShoulder", SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, 4, -1, 0},
    {"RightShoulder", SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, 5, -1, 0},
    {"Back", SDL_GAMEPAD_BUTTON_BACK, 6, -1, 0}, {"Start", SDL_GAMEPAD_BUTTON_START, 7, -1, 0},
    {"LeftStick", SDL_GAMEPAD_BUTTON_LEFT_STICK, 8, -1, 0},
    {"RightStick", SDL_GAMEPAD_BUTTON_RIGHT_STICK, 9, -1, 0},
    {"Up", SDL_GAMEPAD_BUTTON_DPAD_UP, -1, -1, SDL_HAT_UP},
    {"Down", SDL_GAMEPAD_BUTTON_DPAD_DOWN, -1, -1, SDL_HAT_DOWN},
    {"Left", SDL_GAMEPAD_BUTTON_DPAD_LEFT, -1, -1, SDL_HAT_LEFT},
    {"Right", SDL_GAMEPAD_BUTTON_DPAD_RIGHT, -1, -1, SDL_HAT_RIGHT},
    {"LeftTrigger", -1, -1, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, 0},
    {"RightTrigger", -1, -1, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, 0},
};

static int parse_pad(const char *spec)
{
    static const char *const words[] = {"attach", "attachraw", "detach"};
    char buf[4096], *item, *save, *slash, *what;
    size_t i;

    SDL_strlcpy(buf, spec, sizeof buf);
    for (item = SDL_strtok_r(buf, ",", &save); item && pad_count < MAX_PAD;
         item = SDL_strtok_r(NULL, ",", &save)) {
        char *colon = SDL_strchr(item, ':');
        if (!colon)
            return 0;
        *colon = 0;
        what = colon + 1;
        pad_items[pad_count].frame = SDL_atoi(item);
        slash = SDL_strchr(what, '/');
        pad_items[pad_count].hold = slash ? SDL_atoi(slash + 1) : -1;
        if (slash)
            *slash = 0;
        pad_items[pad_count].what = -1;
        for (i = 0; i < SDL_arraysize(words); i++)
            if (!SDL_strcmp(what, words[i]))
                pad_items[pad_count].what = (int)i;
        for (i = 0; i < SDL_arraysize(pad_names); i++)
            if (!SDL_strcmp(what, pad_names[i].name)) {
                pad_items[pad_count].what = PAD_BUTTON;
                pad_items[pad_count].index = (int)i;
                if (pad_items[pad_count].hold < 0)
                    pad_items[pad_count].hold = 2;
            }
        if ((what[0] == 'L' && (what[1] == 'X' || what[1] == 'Y') && what[2] == '=')) {
            pad_items[pad_count].what = PAD_AXIS;
            pad_items[pad_count].index = what[1] == 'X' ? SDL_GAMEPAD_AXIS_LEFTX : SDL_GAMEPAD_AXIS_LEFTY;
            pad_items[pad_count].value = SDL_atoi(what + 3);
        }
        if (pad_items[pad_count].what < 0)
            return 0;
        pad_count++;
    }
    return 1;
}

static void pad_attach(int raw)
{
    SDL_VirtualJoystickDesc desc;

    if (vpad.joystick || !SDL_InitSubSystem(SDL_INIT_GAMEPAD))
        return;
    SDL_INIT_INTERFACE(&desc);
    desc.type = raw ? SDL_JOYSTICK_TYPE_UNKNOWN : SDL_JOYSTICK_TYPE_GAMEPAD;
    desc.naxes = raw ? 2 : SDL_GAMEPAD_AXIS_COUNT;
    desc.nbuttons = raw ? 10 : SDL_GAMEPAD_BUTTON_COUNT;
    desc.nhats = raw ? 1 : 0;
    desc.name = raw ? "--pad joystick" : "--pad gamepad";
    vpad.raw = raw;
    if ((vpad.id = SDL_AttachVirtualJoystick(&desc)) != 0)
        vpad.joystick = SDL_OpenJoystick(vpad.id);
}

static void pad_detach(void)
{
    if (!vpad.joystick)
        return;
    SDL_CloseJoystick(vpad.joystick);
    SDL_DetachVirtualJoystick(vpad.id);
    vpad.joystick = NULL;
}

static void pad_button(int i, int down)
{
    static Uint8 hat;

    if (!vpad.joystick)
        return;
    if (pad_names[i].trigger >= 0 && !vpad.raw)
        SDL_SetJoystickVirtualAxis(vpad.joystick, pad_names[i].trigger,
                                   down ? SDL_JOYSTICK_AXIS_MAX : SDL_JOYSTICK_AXIS_MIN);
    else if (pad_names[i].hat && vpad.raw) {
        hat = down ? hat | pad_names[i].hat : hat & ~pad_names[i].hat;
        SDL_SetJoystickVirtualHat(vpad.joystick, 0, hat);
    } else if ((vpad.raw ? pad_names[i].raw : pad_names[i].button) >= 0)
        SDL_SetJoystickVirtualButton(vpad.joystick, vpad.raw ? pad_names[i].raw : pad_names[i].button, down);
}

static void inject_pad(void)
{
    int i;

    for (i = 0; i < pad_count; i++) {
        int start = pad_items[i].frame == frame_count;
        int end = pad_items[i].hold >= 0 && pad_items[i].frame + pad_items[i].hold == frame_count;
        switch (pad_items[i].what) {
        case PAD_ATTACH:
        case PAD_ATTACH_RAW:
            if (start)
                pad_attach(pad_items[i].what == PAD_ATTACH_RAW);
            break;
        case PAD_DETACH:
            if (start)
                pad_detach();
            break;
        case PAD_BUTTON:
            if (start || end)
                pad_button(pad_items[i].index, start);
            break;
        case PAD_AXIS:
            if ((start || end) && vpad.joystick)
                SDL_SetJoystickVirtualAxis(vpad.joystick, pad_items[i].index,
                                           (Sint16)(start ? pad_items[i].value : 0));
            break;
        }
    }
}

static void finish(int code)
{
    if (dump_path)
        video_save_ppm(dump_path);
    video_close();
    platform_audio_close();
    SDL_Quit();
    exit(code);
}

static void save_shot(void)
{
    char path[512];

    SDL_snprintf(path, sizeof path, "%s-%05d.ppm", dump_path, frame_count);
    video_save_ppm(path);
}

void app_tick(void)
{
    if (dump_path && shot_every > 0 && frame_count % shot_every == 0)
        save_shot();
    if (++frame_count >= frame_limit && frame_limit >= 0)
        finish(0);
    inject_keys();
    inject_mouse();
    inject_pad();
}

int main(int argc, char **argv)
{
    char cmd[128] = "";
    int i, r;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--frames") && i + 1 < argc)
            frame_limit = SDL_atoi(argv[++i]);
        else if (!strcmp(argv[i], "--dump") && i + 1 < argc)
            dump_path = argv[++i];
        else if (!strcmp(argv[i], "--audio-dump") && i + 1 < argc)
            platform_audio_dump(argv[++i]);
        else if (!strcmp(argv[i], "--frame-stats"))
            video_frame_stats();
        else if (!strcmp(argv[i], "--shots") && i + 1 < argc)
            shot_every = SDL_atoi(argv[++i]);
        else if (!strcmp(argv[i], "--keys") && i + 1 < argc) {
            if (!parse_keys(argv[++i])) {
                fprintf(stderr, "--keys: FRAME:KEY[+KEY][/HOLD],... with SDL key names\n");
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--pad") && i + 1 < argc) {
            if (!parse_pad(argv[++i])) {
                fprintf(stderr, "--pad: FRAME:attach|attachraw|detach|BUTTON|LX=V|LY=V[/HOLD],...\n");
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--mouse") && i + 1 < argc) {
            if (!parse_mouse(argv[++i])) {
                fprintf(stderr, "--mouse: FRAME:X,Y[,move|down|up|click|dclick|rdown|rup|rclick];...\n");
                return 1;
            }
        }
        else
            SDL_strlcpy(cmd, argv[i], sizeof cmd);
    }
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (!video_open("Inner Space", 640, 480)) {
        fprintf(stderr, "video: %s\n", SDL_GetError());
        return 1;
    }
    if (!win_init())
        return 1;
    r = win_run(cmd);
    finish(r);
    return r;
}
