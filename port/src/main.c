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
    SDL_Keycode key[4];
} keys[MAX_KEYS];
static int key_count;

static SDL_Keycode key_named(const char *name)
{
    if (!SDL_strcasecmp(name, "Alt"))
        return SDLK_LALT;
    if (!SDL_strcasecmp(name, "Ctrl"))
        return SDLK_LCTRL;
    if (!SDL_strcasecmp(name, "Shift"))
        return SDLK_LSHIFT;
    return SDL_GetKeyFromName(name);
}

static int parse_keys(const char *spec)
{
    char buf[4096], *item, *save, *part, *save2, *slash;

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
        for (part = SDL_strtok_r(colon + 1, "+", &save2); part && keys[key_count].n < 4;
             part = SDL_strtok_r(NULL, "+", &save2))
            if ((keys[key_count].key[keys[key_count].n++] = key_named(part)) == SDLK_UNKNOWN)
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

void app_frame(void)
{
    video_present();
    if (dump_path && shot_every > 0 && frame_count % shot_every == 0)
        save_shot();
    if (++frame_count >= frame_limit && frame_limit >= 0)
        finish(0);
    inject_keys();
    inject_mouse();
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
        else if (!strcmp(argv[i], "--shots") && i + 1 < argc)
            shot_every = SDL_atoi(argv[++i]);
        else if (!strcmp(argv[i], "--keys") && i + 1 < argc) {
            if (!parse_keys(argv[++i])) {
                fprintf(stderr, "--keys: FRAME:KEY[+KEY][/HOLD],... with SDL key names\n");
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
