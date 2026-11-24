/* Runs a script of ISPACE.DLL calls on the port's native versions and
 * prints what they leave: each call's result, the pixels of a bitmap it
 * returns and the entries of every palette a call has returned.  The
 * other half of oracle.py (tools/README.md); not part of the game.
 *
 * Script lines: ORDINAL ARG...; an ARG is a number, "text", @K (the
 * result of call K, from 0) or DC (a screen DC).  Ordinal 29's words
 * are passed by pointer and printed after the call ("outs"). */
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "video.h"
#include "gdi.h"
#include "ispace.h"

#define MAX_CALLS 4096
#define MAX_ARGS 16

static int16_t results[MAX_CALLS];
static int ncalls;
static HBITMAP mdc_bitmap;      /* the bitmap of the last MDC argument */
static RECT *rects;             /* ordinal 32's rectangles */
static HGLOBAL rect_block;

void app_frame(void)
{
}

typedef struct {
    int16_t w[MAX_ARGS];
    int32_t l[MAX_ARGS];
    char s[MAX_ARGS][64];
    int n;
} Args;

static int parse(char *line, int *ordinal, Args *a)
{
    char *p = line, *end;

    *ordinal = (int)strtol(p, &end, 10);
    if (end == p)
        return 0;
    p = end;
    for (a->n = 0; a->n < MAX_ARGS; a->n++) {
        int k = a->n;
        while (*p == ' ' || *p == '\t')
            p++;
        if (!*p || *p == '\n')
            break;
        a->s[k][0] = 0;
        a->w[k] = 0;
        a->l[k] = 0;
        if (*p == '"') {
            size_t len = strcspn(++p, "\"");
            snprintf(a->s[k], sizeof a->s[k], "%.*s", (int)len, p);
            p += len + (p[len] == '"');
        } else if (*p == '@') {
            long i = strtol(p + 1, &p, 10);
            a->w[k] = i >= 0 && i < ncalls ? results[i] : 0;
        } else if (!strncmp(p, "MDC", 3)) {
            HDC dc = CreateCompatibleDC(0);
            mdc_bitmap = CreateCompatibleBitmap(GetDC(0), 640, 480);
            SelectObject(dc, mdc_bitmap);
            a->w[k] = (int16_t)dc;
            p += 3;
        } else if (!strncmp(p, "DC", 2)) {
            a->w[k] = (int16_t)GetDC(0);
            p += 2;
        } else {
            a->l[k] = (int32_t)strtoll(p, &p, 0);
            a->w[k] = (int16_t)a->l[k];
        }
    }
    return 1;
}

static int16_t run(int ordinal, Args *a)
{
    int16_t *w = a->w;

    switch (ordinal) {
    case 1: return ispace_load_image(w[0], w[1], a->s[2], w[3], w[4], w[5]);
    case 2: return ispace_build_surface(w[0], w[1], 0, w[3], w[4], w[5], w[6], w[7], w[8], w[9],
                                        (char)w[10], (char)w[11], (char)w[12], w[13]);
    case 3: return ispace_load_bitmap(a->s[0]);
    case 4: return ispace_palette(w[0], w[1], w[2], w[3], w[4], w[5], w[6]);
    case 5: return ispace_image_height();
    case 6: return (int16_t)ispace_make_mask(w[0], w[1], w[2]);
    case 12: return ispace_smooth_image(w[0], w[1], 0, w[3], w[4], w[5], w[6], w[7], w[8],
                                        (char)w[9], (char)w[10]);
    case 14:
        ispace_pal_scale(w[0], w[1], w[2], w[3], w[4]);
        return 0;
    case 18: return ispace_sprite_sheet(w[0], w[1], w[2], w[3], w[4], w[5]);
    case 29:
        return ispace_collide(&w[0], &w[1], &w[2], &w[3], &w[4], &w[5], &w[6], &w[7], w[8], w[9],
                              w[10], w[11], &w[12], &w[13]);
    case 32:
        rect_block = GlobalAlloc(GHND, 8);
        rects = GlobalLock(rect_block);
        return (int16_t)ispace_room(w[0], w[1], rects, rect_block, w[2], a->l[3], w[4], a->l[5], w[6], w[7], w[8],
                                    w[9], w[10], w[11]);
    case 33:
        ispace_letters(w[0], w[1], a->l[2], w[3], a->l[4], w[5], w[6], a->s[7]);
        return 0;
    case 34:
        ispace_bevel(w[0], w[1], w[2], w[3], w[4], w[5]);
        return 0;
    case 35:
        ispace_gauge(w[0], w[1], w[2], w[3], w[4], w[5]);
        return 0;
    case 1000: return (int16_t)ispace_ship_image(w[0], w[1], a->s[2], w[3], w[4], w[5]);
    default:
        fprintf(stderr, "port_calls: ordinal %d not supported\n", ordinal);
        exit(2);
    }
}

static void hex(const uint8_t *p, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++)
        printf("%02x", p[i]);
    printf("\n");
}

static void report(int k, int ordinal, const Args *a)
{
    Bmp *b = handle_get((uint16_t)results[k], H_BITMAP);
    int i;

    if (!b && ordinal >= 33 && ordinal <= 35)
        b = handle_get(mdc_bitmap, H_BITMAP);
    printf("call %d ord %d ret %d\n", k, ordinal, results[k]);
    if (ordinal == 29) {
        printf("outs");
        for (i = 0; i < 14; i++)
            if (i < 8 || i > 11)
                printf(" %d", a->w[i]);
        printf("\n");
    }
    if (ordinal == 32) {
        int n = (int)(GlobalSize(rect_block) / 8);
        rects = GlobalLock(rect_block);
        printf("rects");
        for (i = 0; i < n; i++)
            printf(" %d %d %d %d", rects[i].left, rects[i].top, rects[i].right, rects[i].bottom);
        printf("\n");
    }
    if (b) {
        printf("bmp %d %d %d ", b->w, b->h, b->mono);
        hex(b->px, (size_t)b->w * (size_t)b->h);
    }
    for (i = 0; i <= k; i++) {
        Pal *p = handle_get((uint16_t)results[i], H_PALETTE);
        uint8_t rgb[256 * 3];
        int j;
        if (!p)
            continue;
        for (j = 0; j < 256; j++) {
            rgb[3 * j] = j < p->n ? p->e[j].peRed : 0;
            rgb[3 * j + 1] = j < p->n ? p->e[j].peGreen : 0;
            rgb[3 * j + 2] = j < p->n ? p->e[j].peBlue : 0;
        }
        printf("pal @%d ", i);
        hex(rgb, sizeof rgb);
    }
}

int main(int argc, char **argv)
{
    char line[512];
    FILE *f;
    Args a;
    int ordinal;

    if (argc != 2 || !(f = fopen(argv[1], "r"))) {
        fprintf(stderr, "usage: port_calls SCRIPT\n");
        return 2;
    }
    if (!SDL_Init(SDL_INIT_VIDEO) || !video_open("port_calls", 640, 480) || !win_init())
        return 1;
    while (ncalls < MAX_CALLS && fgets(line, sizeof line, f)) {
        if (line[0] == '#' || !parse(line, &ordinal, &a))
            continue;
        results[ncalls] = run(ordinal, &a);
        report(ncalls++, ordinal, &a);
    }
    fclose(f);
    return 0;
}
