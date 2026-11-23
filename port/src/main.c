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
    if (frame_limit >= 0 && ++frame_count >= frame_limit)
        finish(0);
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
