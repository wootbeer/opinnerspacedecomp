/* The game draws into a 256-colour framebuffer, as it did on a 1994
 * palette display. video_present() converts it through the palette and
 * shows it in the SDL window. */
#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

typedef struct {
    uint8_t r, g, b;
} Rgb;

typedef struct {
    int width;
    int height;
    uint8_t *pixels;          /* width * height palette indices */
    Rgb palette[256];
} Framebuffer;

int  video_open(const char *title, int width, int height);
void video_close(void);
Framebuffer *video_framebuffer(void);
void video_present(void);
int  video_save_ppm(const char *path);

/* Window pixel position to framebuffer position. */
void video_map_point(float wx, float wy, int *x, int *y);
/* Framebuffer position to window pixel position (test input). */
void video_window_point(int x, int y, float *wx, float *wy);

#endif
