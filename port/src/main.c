/* Operation: Inner Space, native port: sets up the screen and the native
 * Windows calls, gives the globals their initial values from INSPACE.EXE
 * and runs the game's WinMain (2:0000). */
#include "video.h"
#include "win/win.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int frame_limit = -1;        /* --frames N: run N frames, then exit */
static const char *dump_path;       /* --dump FILE: save the last frame */
static int frame_count;

/* --keys "FRAME:KEY,...": keys pressed at a frame and released two
 * frames later, for headless runs.  KEY is an SDL key name, with
 * modifiers before it: "1600:Escape,1700:Alt+X". */
#define MAX_KEYS 64
static struct {
    int frame, n;
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
    char buf[512], *item, *save, *part, *save2;

    SDL_strlcpy(buf, spec, sizeof buf);
    for (item = SDL_strtok_r(buf, ",", &save); item && key_count < MAX_KEYS;
         item = SDL_strtok_r(NULL, ",", &save)) {
        char *colon = SDL_strchr(item, ':');
        if (!colon)
            return 0;
        *colon = 0;
        keys[key_count].frame = SDL_atoi(item);
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
        if (keys[i].frame + 2 == frame_count)
            for (j = keys[i].n - 1; j >= 0; j--)
                push_key(keys[i].key[j], 0);
    }
}

static void finish(int code)
{
    if (dump_path)
        video_save_ppm(dump_path);
    video_close();
    SDL_Quit();
    exit(code);
}

void app_frame(void)
{
    video_present();
    if (++frame_count >= frame_limit && frame_limit >= 0)
        finish(0);
    inject_keys();
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
        else if (!strcmp(argv[i], "--keys") && i + 1 < argc) {
            if (!parse_keys(argv[++i])) {
                fprintf(stderr, "--keys: FRAME:KEY[+KEY],... with SDL key names\n");
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
