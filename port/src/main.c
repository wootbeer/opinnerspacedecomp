/* Operation: Inner Space, native port.
 * For now: opens the window and shows a palette test pattern. The game's
 * start-up (WinMain at 2:0000 in the original) is translated next. */
#include "video.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    Framebuffer *fb;
    int frames = -1;            /* --frames N: run N frames, then exit */
    const char *dump = NULL;    /* --dump FILE: save the last frame */
    int i, x, y;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--frames") && i + 1 < argc)
            frames = SDL_atoi(argv[++i]);
        else if (!strcmp(argv[i], "--dump") && i + 1 < argc)
            dump = argv[++i];
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (!video_open("Inner Space", 640, 480)) {
        fprintf(stderr, "video: %s\n", SDL_GetError());
        return 1;
    }

    fb = video_framebuffer();
    for (i = 0; i < 256; i++) {
        fb->palette[i].r = (uint8_t)i;
        fb->palette[i].g = (uint8_t)(255 - i);
        fb->palette[i].b = (uint8_t)(i * 3);
    }
    for (y = 0; y < fb->height; y++)
        for (x = 0; x < fb->width; x++)
            fb->pixels[y * fb->width + x] = (uint8_t)(x / 2 + y / 2);

    for (i = 0; frames < 0 || i < frames; i++) {
        SDL_Event ev;
        int quit = 0;

        while (SDL_PollEvent(&ev))
            if (ev.type == SDL_EVENT_QUIT)
                quit = 1;
        if (quit)
            break;
        video_present();
        SDL_Delay(16);
    }

    if (dump)
        video_save_ppm(dump);
    video_close();
    SDL_Quit();
    return 0;
}
