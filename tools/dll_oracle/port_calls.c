/* Runs a script of ISPACE.DLL calls on the port's native versions and
 * prints what they leave: each call's result, the pixels of a bitmap it
 * returns and the entries of every palette a call has returned.  The
 * other half of oracle.py (tools/README.md); not part of the game.
 *
 * Script lines: ORDINAL ARG...; an ARG is a number, "text", @K (the
 * result of call K, from 0), DC (a screen DC), MDC (a memory DC with a
 * 640x480 bitmap), DC@K (a memory DC with call K's bitmap, printed
 * after the call: "dcbmp") or X,Y (a point).  Ordinal 29's words are
 * passed by pointer and printed after the call ("outs"), as is the wave
 * device's volume after ordinals 7-9.  The dialog procedures (ordinals
 * 11, 26, 28, 37, 38, 40) take DLGn (a dialog from the language DLL's template n,
 * owned by a window of INSPACE.EXE; DLG: the last one), C<id>:<pos>
 * (MAKELONG(pos, the control)) and N<id>:<code> (MAKELONG(the control,
 * code)); after them and pseudo-ordinals 1001
 * (check a box), 1002 (pick a combo item) and 1003 (type a control's
 * text) the dialog's controls, its end and INSPACE.INI are printed
 * ("state").  Ordinal 41 reads into a block printed after the call
 * ("outs"); pseudo-ordinal 1004 (x, y, buttons, present) is a virtual
 * gamepad: the left stick, the face buttons A, B, X, Y as bits 0-3,
 * attached or not; 1005 and 1006 are the Joystick dialog's procedure
 * and timer. */
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "video.h"
#include "gdi.h"
#include "user.h"
#include "ispace.h"

#define MAX_CALLS 4096
#define MAX_ARGS 16

static int16_t results[MAX_CALLS];
static int ncalls;
static HBITMAP mdc_bitmap;      /* the bitmap of the last MDC argument */
static HBITMAP dc_bitmap;       /* the bitmap of a DC@K argument of this call */
static RECT *rects;             /* ordinal 32's rectangles */
static HGLOBAL rect_block;
static HWND dlg;                /* the last DLGn */
static char joystick[8];        /* ordinal 41's reading */
static struct {
    SDL_JoystickID id;
    SDL_Joystick *j;
} vpad;

void app_tick(void)
{
}

static BOOL no_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    (void)h;
    (void)msg;
    (void)wp;
    (void)lp;
    return 0;
}

/* A dialog of template n owned by a window of INSPACE.EXE, in place of
 * the last one; the script calls its procedure. */
static HWND new_dialog(int n)
{
    static HWND owner;
    WNDCLASS wc;

    if (!owner) {
        memset(&wc, 0, sizeof wc);
        wc.lpfnWndProc = DefWindowProc;
        wc.lpszClassName = "PortCalls";
        RegisterClass(&wc);
        owner = CreateWindow("PortCalls", "", WS_POPUP, 0, 0, 640, 480, 0, 0, module_exe(), NULL);
    }
    if (dlg)
        DestroyWindow(dlg);
    return CreateDialog(ispace_lang_module(), MAKEINTRESOURCE(n), owner, no_proc);
}

typedef struct {
    int16_t w[MAX_ARGS];
    int16_t y[MAX_ARGS];        /* a point's y (X,Y) */
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
        } else if (!strncmp(p, "DLG", 3)) {
            p += 3;
            if (*p >= '0' && *p <= '9')
                dlg = new_dialog((int)strtol(p, &p, 10));
            a->w[k] = (int16_t)dlg;
        } else if (*p == 'C' && p[1] >= '0' && p[1] <= '9') {
            HWND c = GetDlgItem(dlg, (int16_t)strtol(p + 1, &p, 0));
            a->l[k] = (int32_t)MAKELONG(strtol(p + 1, &p, 0), c);
            a->w[k] = (int16_t)a->l[k];
        } else if (*p == 'N' && p[1] >= '0' && p[1] <= '9') {
            HWND c = GetDlgItem(dlg, (int16_t)strtol(p + 1, &p, 0));
            a->l[k] = (int32_t)MAKELONG(c, strtol(p + 1, &p, 0));
            a->w[k] = (int16_t)a->l[k];
        } else if (!strncmp(p, "DC@", 3)) {
            HDC dc = CreateCompatibleDC(0);
            long i = strtol(p + 3, &p, 10);
            dc_bitmap = (HBITMAP)(i >= 0 && i < ncalls ? results[i] : 0);
            SelectObject(dc, dc_bitmap);
            a->w[k] = (int16_t)dc;
        } else if (!strncmp(p, "DC", 2)) {
            a->w[k] = (int16_t)GetDC(0);
            p += 2;
        } else {
            a->l[k] = (int32_t)strtoll(p, &p, 0);
            a->w[k] = (int16_t)a->l[k];
            if (*p == ',')
                a->y[k] = (int16_t)strtol(p + 1, &p, 0);
        }
    }
    return 1;
}

/* The virtual gamepad of pseudo-ordinal 1004. */
static void set_pad(int16_t x, int16_t y, int buttons, int present)
{
    static const SDL_GamepadButton face[4] = {SDL_GAMEPAD_BUTTON_SOUTH, SDL_GAMEPAD_BUTTON_EAST,
                                              SDL_GAMEPAD_BUTTON_WEST, SDL_GAMEPAD_BUTTON_NORTH};
    SDL_VirtualJoystickDesc desc;
    int i;

    if (!present && vpad.j) {
        SDL_CloseJoystick(vpad.j);
        SDL_DetachVirtualJoystick(vpad.id);
        vpad.j = NULL;
    }
    if (!present)
        return;
    if (!vpad.j) {
        SDL_InitSubSystem(SDL_INIT_GAMEPAD);
        SDL_INIT_INTERFACE(&desc);
        desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
        desc.naxes = SDL_GAMEPAD_AXIS_COUNT;
        desc.nbuttons = SDL_GAMEPAD_BUTTON_COUNT;
        vpad.id = SDL_AttachVirtualJoystick(&desc);
        vpad.j = SDL_OpenJoystick(vpad.id);
    }
    SDL_SetJoystickVirtualAxis(vpad.j, SDL_GAMEPAD_AXIS_LEFTX, x);
    SDL_SetJoystickVirtualAxis(vpad.j, SDL_GAMEPAD_AXIS_LEFTY, y);
    for (i = 0; i < 4; i++)
        SDL_SetJoystickVirtualButton(vpad.j, face[i], (buttons >> i) & 1);
    SDL_UpdateJoysticks();
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
    case 7: return ispace_sound_control(a->l[0], w[1]);
    case 8: return ispace_sound_follow((POINT){w[0], a->y[0]}, w[1], w[2], a->l[3]);
    case 9:
        return ispace_sound_play(w[0], (POINT){w[1], a->y[1]}, w[2], a->l[3], a->l[4], (DWORD)a->l[5],
                                 a->s[6]);
    case 12: return ispace_smooth_image(w[0], w[1], 0, w[3], w[4], w[5], w[6], w[7], w[8],
                                        (char)w[9], (char)w[10]);
    case 14:
        ispace_pal_scale(w[0], w[1], w[2], w[3], w[4]);
        return 0;
    case 15: return ispace_cut(w[0], w[1], w[2], w[3], w[4], w[5], w[6], w[7], w[8]);
    case 17: return ispace_quick_draw(w[0], w[1], 0, w[3], w[4], w[5], w[6], (char)w[7], (char)w[8], w[9], w[10],
                                      (char)w[11], (char)w[12]);
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
    case 10: return ispace_dialog(w[0], w[1], w[2], w[3], w[4], w[5], w[6]);
    case 11: return ispace_options_proc((HWND)w[0], (UINT)w[1], (WPARAM)(uint16_t)w[2], (LPARAM)a->l[3]);
    case 37: return ispace_display_proc((HWND)w[0], (UINT)w[1], (WPARAM)(uint16_t)w[2], (LPARAM)a->l[3]);
    case 38: return ispace_audio_proc((HWND)w[0], (UINT)w[1], (WPARAM)(uint16_t)w[2], (LPARAM)a->l[3]);
    case 26: return ispace_save_proc((HWND)w[0], (UINT)w[1], (WPARAM)(uint16_t)w[2], (LPARAM)a->l[3]);
    case 28: return ispace_newbody_proc((HWND)w[0], (UINT)w[1], (WPARAM)(uint16_t)w[2], (LPARAM)a->l[3]);
    case 40: return ispace_benefits_proc((HWND)w[0], (UINT)w[1], (WPARAM)(uint16_t)w[2], (LPARAM)a->l[3]);
    case 41: return ispace_joystick(w[0], joystick);
    case 1004:
        set_pad(w[0], w[1], w[2], w[3]);
        return 0;
    case 1005: return ispace_joy_proc((HWND)w[0], (UINT)w[1], (WPARAM)(uint16_t)w[2], (LPARAM)a->l[3]);
    case 1006:
        ispace_joy_timer();
        return 0;
    case 1001:
        CheckDlgButton(dlg, w[0], (UINT)w[1]);
        return 0;
    case 1002:
        SendDlgItemMessage(dlg, w[0], CB_SETCURSEL, (WPARAM)w[1], 0);
        return 0;
    case 1003:
        SetWindowText(GetDlgItem(dlg, w[0]), a->s[1]);
        return 0;
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

static int key_cmp(const void *a, const void *b)
{
    const char *x = *(const char *const *)a, *y = *(const char *const *)b;

    for (; *x && *y && *x != '=' && *y != '='; x++, y++)
        if (SDL_toupper((unsigned char)*x) != SDL_toupper((unsigned char)*y))
            return SDL_toupper((unsigned char)*x) - SDL_toupper((unsigned char)*y);
    return (*x != '=' && *x) - (*y != '=' && *y);
}

/* INSPACE.INI's [Inner Space] keys, sorted. */
static void print_ini(void)
{
    static char lines[512][256];
    char *sorted[512], path[1024];
    int n = 0, in = 0, i;
    FILE *f;

    if (!dos_to_host("C:\\WINDOWS\\INSPACE.INI", path, sizeof path) || !(f = fopen(path, "r")))
        return;
    while (n < 512 && fgets(lines[n], sizeof lines[n], f)) {
        lines[n][strcspn(lines[n], "\r\n")] = 0;
        if (lines[n][0] == '[')
            in = !SDL_strcasecmp(lines[n], "[Inner Space]");
        else if (in && strchr(lines[n], '='))
            sorted[n] = lines[n], n++;
    }
    fclose(f);
    qsort(sorted, (size_t)n, sizeof sorted[0], key_cmp);
    for (i = 0; i < n; i++)
        printf("state ini %s\n", sorted[i]);
}

/* The dialog's controls as oracle.py's emulator prints them. */
static void print_dialog(void)
{
    HWND c, focus = GetFocus();
    char cls[20], text[4096], item[256], items[1024];
    int16_t lo = 0, hi = 0, pos = 0, sel, i, n, result;
    int checked, pressed;
    char *p;

    for (c = GetWindow(dlg, GW_CHILD); c; c = GetWindow(c, GW_HWNDNEXT)) {
        GetClassName(c, cls, sizeof cls);
        checked = !strcmp(cls, "Button") ? (int)SendMessage(c, BM_GETCHECK, 0, 0) : 0;
        pressed = !strcmp(cls, "Button") && SendMessage(c, BM_GETSTATE, 0, 0) & BST_PUSHED;
        sel = -1;
        items[0] = 0;
        if (!strcmp(cls, "ComboBox")) {
            sel = (int16_t)SendMessage(c, CB_GETCURSEL, 0, 0);
            n = (int16_t)SendMessage(c, WM_USER + 6, 0, 0);     /* CB_GETCOUNT */
            for (i = 0; i < n; i++) {
                combo_get_text(c, i, item, sizeof item);
                SDL_strlcat(items, i ? "|" : "", sizeof items);
                SDL_strlcat(items, item, sizeof items);
            }
        }
        if (!strcmp(cls, "ScrollBar")) {
            GetScrollRange(c, SB_CTL, &lo, &hi);
            pos = GetScrollPos(c, SB_CTL);
        } else {
            lo = hi = pos = 0;
        }
        GetWindowText(c, text, sizeof text);
        while ((p = strchr(text, '&')) != NULL)
            memmove(p, p + 1, strlen(p));
        printf("state %d %s en %d chk %d hi %d sel %d [%s] sb %d %d %d \"", GetDlgCtrlID(c), cls,
               IsWindowEnabled(c) != 0, checked, pressed, sel, items, lo, hi, pos);
        for (p = text; *p; p++)
            printf(*p == '\r' ? "\\r" : *p == '\n' ? "\\n" : "%c", *p);
        printf("\"\n");
    }
    while (focus && GetParent(focus) && GetParent(focus) != dlg)
        focus = GetParent(focus);           /* a combo box's edit field: the combo box */
    printf("state focus %d\n", focus && GetParent(focus) == dlg ? GetDlgCtrlID(focus) : 0);
    if (dialog_ended(dlg, &result))
        printf("state ended %d\n", result);
    print_ini();
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
    if (ordinal == 11 || ordinal == 26 || ordinal == 28 || ordinal == 40 || ordinal == 37 || ordinal == 38 || (ordinal >= 1001 && ordinal <= 1003) ||
        ordinal == 1005 || ordinal == 1006)
        print_dialog();
    if (ordinal == 41)
        printf("outs %u %u %d %d %d %d\n", (uint8_t)joystick[0] | (uint8_t)joystick[1] << 8,
               (uint8_t)joystick[2] | (uint8_t)joystick[3] << 8, joystick[4], joystick[5], joystick[6], joystick[7]);
    if (ordinal >= 7 && ordinal <= 9) {
        DWORD v;
        waveOutGetVolume(0, &v);
        printf("outs %u %u\n", (unsigned)LOWORD(v), (unsigned)HIWORD(v));
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
    if (dc_bitmap && (b = handle_get(dc_bitmap, H_BITMAP)) != NULL) {
        printf("dcbmp %d %d %d ", b->w, b->h, b->mono);
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
        dc_bitmap = 0;
        if (line[0] == '#' || !parse(line, &ordinal, &a))
            continue;
        results[ncalls] = run(ordinal, &a);
        report(ncalls++, ordinal, &a);
    }
    fclose(f);
    return 0;
}
