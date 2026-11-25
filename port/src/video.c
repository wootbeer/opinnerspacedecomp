#include "video.h"
#include "platform/platform.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static Framebuffer fb;
static int pending;             /* finished, not shown yet */
static uint64_t shown;          /* when the last picture went out */
static uint64_t refresh;        /* the display's refresh period (ns) */

/* --frame-stats: the pictures of the current 5 seconds. */
#define STATS_NS (5 * (uint64_t)SDL_NS_PER_SECOND)
#define STATS_MAX 8192
static struct {
    int on;
    uint64_t start, cpu, last;  /* the period's start, processor time then; the last picture */
    int frames, shown;
    float ms[STATS_MAX];        /* time from the picture before, of up to STATS_MAX */
} stats;

int video_open(const char *title, int width, int height)
{
    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!window)
        return 0;
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
        return 0;
    /* A present waiting for the display's refresh would hold up the
     * game, whose pace is its own (NOTES-port.md "Game speed"). */
    SDL_SetRenderVSync(renderer, 0);
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

static int by_value(const void *a, const void *b)
{
    float x = *(const float *)a, y = *(const float *)b;

    return (x > y) - (x < y);
}

static void stats_report(uint64_t now)
{
    int n = stats.frames < STATS_MAX ? stats.frames : STATS_MAX;
    double s = (double)(now - stats.start) / SDL_NS_PER_SECOND;
    double cpu = (double)(platform_cpu_ns() - stats.cpu) / SDL_NS_PER_SECOND;

    if (n) {
        qsort(stats.ms, (size_t)n, sizeof stats.ms[0], by_value);
        SDL_Log("frame-stats: %.1f fps over %.1f s (%d frames, %d shown), frame time p50 %.2f "
                "p95 %.2f p99 %.2f max %.2f ms, cpu %.0f%%",
                stats.frames / s, s, stats.frames, stats.shown, stats.ms[n / 2],
                stats.ms[n * 95 / 100], stats.ms[n * 99 / 100], stats.ms[n - 1], 100 * cpu / s);
    }
    stats.start = now;
    stats.cpu = platform_cpu_ns();
    stats.frames = stats.shown = 0;
}

static void stats_frame(uint64_t now)
{
    if (!stats.on)
        return;
    if (stats.last) {
        if (stats.frames < STATS_MAX)
            stats.ms[stats.frames] = (float)(now - stats.last) / SDL_NS_PER_MS;
        stats.frames++;
    } else
        stats_report(now);
    stats.last = now;
    if (now - stats.start >= STATS_NS)
        stats_report(now);
}

void video_frame_stats(void)
{
    stats.on = 1;
}

void video_close(void)
{
    if (stats.on)
        stats_report(platform_time_ns());
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

static void present(void)
{
    const SDL_DisplayMode *mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(window));
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
    refresh = (uint64_t)(SDL_NS_PER_SECOND / (mode && mode->refresh_rate > 0 ? mode->refresh_rate : 60.0f));
}

/* A picture is shown at once unless the last went out less than half a
 * refresh ago (the game draws faster than the display shows: the title,
 * high rates, no limit); every refresh still gets the newest. */
void video_show(void)
{
    uint64_t now;

    if (!fb.drawn && !pending)
        return;
    now = platform_time_ns();
    if (fb.drawn) {
        fb.drawn = 0;
        pending = 1;
        stats_frame(now);
    }
    if (now - shown < refresh / 2)
        return;
    present();
    shown = now;
    pending = 0;
    stats.shown++;
}

void video_expose(void)
{
    pending = 1;
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

void video_window_point(int x, int y, float *wx, float *wy)
{
    *wx = (float)x;
    *wy = (float)y;
    SDL_RenderCoordinatesToWindow(renderer, (float)x + 0.5f, (float)y + 0.5f, wx, wy);
}

void video_map_point(float wx, float wy, int *x, int *y)
{
    float fx = wx, fy = wy;

    SDL_RenderCoordinatesFromWindow(renderer, wx, wy, &fx, &fy);
    *x = (int)fx;
    *y = (int)fy;
}
