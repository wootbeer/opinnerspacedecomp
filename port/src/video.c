#include "video.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static Framebuffer fb;

int video_open(const char *title, int width, int height)
{
    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!window)
        return 0;
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
        return 0;
    SDL_SetRenderLogicalPresentation(renderer, width, height,
                                     SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_XRGB8888,
                                SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture)
        return 0;
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    fb.width = width;
    fb.height = height;
    fb.pixels = calloc((size_t)width * height, 1);
    return fb.pixels != NULL;
}

void video_close(void)
{
    free(fb.pixels);
    fb.pixels = NULL;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

Framebuffer *video_framebuffer(void)
{
    return &fb;
}

void video_present(void)
{
    void *dst;
    int pitch, x, y;

    if (!SDL_LockTexture(texture, NULL, &dst, &pitch))
        return;
    for (y = 0; y < fb.height; y++) {
        Uint32 *row = (Uint32 *)((Uint8 *)dst + (size_t)y * pitch);
        const uint8_t *src = fb.pixels + (size_t)y * fb.width;
        for (x = 0; x < fb.width; x++) {
            Rgb c = fb.palette[src[x]];
            row[x] = (Uint32)c.r << 16 | (Uint32)c.g << 8 | c.b;
        }
    }
    SDL_UnlockTexture(texture);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/* Writes the framebuffer as an RGB PPM image: used by tests to compare
 * frames with the original game's. */
int video_save_ppm(const char *path)
{
    FILE *f = fopen(path, "wb");
    int i, n = fb.width * fb.height;

    if (!f)
        return 0;
    fprintf(f, "P6\n%d %d\n255\n", fb.width, fb.height);
    for (i = 0; i < n; i++) {
        Rgb c = fb.palette[fb.pixels[i]];
        fputc(c.r, f);
        fputc(c.g, f);
        fputc(c.b, f);
    }
    return fclose(f) == 0;
}

void video_map_point(float wx, float wy, int *x, int *y)
{
    float fx = wx, fy = wy;

    SDL_RenderCoordinatesFromWindow(renderer, wx, wy, &fx, &fy);
    *x = (int)fx;
    *y = (int)fy;
}
