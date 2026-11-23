/* ISPACE.DLL, the game's graphics and support library, called by ordinal
 * through the pointers fetched in fn_10_6656.  Native versions of its
 * routines, written from the DLL's code; those not done yet are stubs. */

#include "gdi.h"
#include "ne.h"

/* GCC allows function pointer casts through void (*)(void). */
#define PROC(f) ((FARPROC)(void (*)(void))(f))

static HINSTANCE ispace_module(void)
{
    static HINSTANCE h;

    if (!h)
        h = LoadLibrary(GAME_DIR "ISPACE.DLL");
    return h;
}

static HINSTANCE igraphic_module(void)
{
    static HINSTANCE h;

    if (!h)
        h = LoadLibrary(GAME_DIR "IGRAPHIC.DLL");
    return h;
}

/* Ordinal 3 (5:0612): LoadBitmap of name from IGRAPHIC.DLL; SD_LOGO comes
 * from ISPACE.DLL itself. */
static int16_t load_bitmap(LPCSTR name)
{
    HINSTANCE m = lstrcmp(name, "SD_LOGO") == 0 ? ispace_module() : igraphic_module();
    uint32_t size;
    const uint8_t *dib = module_resource(m, MAKEINTRESOURCE(RT_BITMAP_), name, &size);

    return dib ? (int16_t)gdi_bitmap_from_dib(dib, size) : 0;
}

/* Ordinal 6 (5:0650): a monochrome mask of bitmap bm, 1 where it is black. */
static HBITMAP make_mask(int16_t pal, int16_t bm, int16_t dc)
{
    BITMAP info;
    HBITMAP mask, old[2];
    HDC dcs[2];
    HPALETTE old_pal = 0;
    COLORREF bk;
    int i;

    GetObject(bm, sizeof info, &info);
    mask = CreateBitmap(info.bmWidth, info.bmHeight, 1, 1, NULL);
    for (i = 0; i < 2; i++)
        dcs[i] = CreateCompatibleDC(dc);
    old[0] = SelectObject(dcs[0], bm);
    old[1] = SelectObject(dcs[1], mask);
    if (pal)
        old_pal = SelectPalette(dcs[0], pal, 0);
    bk = SetBkColor(dcs[0], RGB(0, 0, 0));
    BitBlt(dcs[1], 0, 0, info.bmWidth, info.bmHeight, dcs[0], 0, 0, SRCCOPY);
    SetBkColor(dcs[0], bk);
    if (old_pal)
        SelectPalette(dcs[0], old_pal, 0);
    for (i = 0; i < 2; i++) {
        SelectObject(dcs[i], old[i]);
        DeleteDC(dcs[i]);
    }
    return mask;
}

static int16_t ispace_1(int16_t a, int16_t b, char *c, int16_t d, int16_t e, int16_t f) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; STUB(); return 0; }
static int16_t ispace_2(int16_t a, int16_t b, int32_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h, int16_t i, int16_t j, char k, char l, char m, int16_t n) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; (void)l; (void)m; (void)n; STUB(); return 0; }
static int16_t ispace_4(int16_t a, int16_t b, int16_t c, int16_t d, int32_t e, int16_t f) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; STUB(); return 0; }
static int16_t ispace_5(void) { STUB(); return 0; }
static int16_t ispace_7(int32_t a, int16_t b) { (void)a; (void)b; STUB(); return 1; }
static int16_t ispace_8(POINT a, int16_t b, int16_t c, int32_t d) { (void)a; (void)b; (void)c; (void)d; STUB(); return 0; }
static int16_t ispace_9(int16_t a, POINT b, int16_t c, int32_t d, int32_t e, DWORD f, LPCSTR g) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; STUB(); return 0; }
static int16_t ispace_10(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; STUB(); return 0; }
static int16_t ispace_12(int16_t a, int16_t b, int32_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h, int16_t i, char j, char k) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; STUB(); return 0; }
static void ispace_14(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e) { (void)a; (void)b; (void)c; (void)d; (void)e; STUB(); }
static int16_t ispace_15(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h, int16_t i) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; STUB(); return 0; }
static void ispace_17(int16_t a, int16_t b, int32_t c, int16_t d, int16_t e, int16_t f, int16_t g, char h, char i, int16_t j, int16_t k, char l, char m) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; (void)l; (void)m; STUB(); }
static int16_t ispace_18(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; STUB(); return 0; }
static int16_t ispace_24(char *a, char *b, int16_t c) { (void)a; (void)b; (void)c; STUB(); return 0; }
static int16_t ispace_29(int16_t *a, int16_t *b, int16_t *c, int16_t *d, int16_t *e, int16_t *f, int16_t *g, int16_t *h, int16_t i, int16_t j, int16_t k, int16_t l, int16_t *m, int16_t *n) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; (void)l; (void)m; (void)n; STUB(); return 0; }
static HBITMAP ispace_32(int16_t a, int16_t b, RECT *c, HGLOBAL d, int16_t e, int32_t f, int16_t g, int32_t h, int16_t i, int16_t j, int16_t k, int16_t l, int16_t m, int16_t n) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; (void)l; (void)m; (void)n; STUB(); return 0; }
static void ispace_33(int16_t a, int16_t b, int32_t c, int16_t d, int32_t e, int16_t f, int16_t g, int32_t h) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; STUB(); }
static void ispace_34(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; STUB(); }
static void ispace_35(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; STUB(); }
static int16_t ispace_36(int16_t a, int16_t b, int16_t c, int16_t d, int16_t e, int16_t f, int16_t g, int16_t h, int16_t i, int16_t j, int32_t k) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; STUB(); return 0; }
static int16_t ispace_41(int16_t a, int32_t b) { (void)a; (void)b; STUB(); return 0; }

FARPROC ispace_proc(int ordinal)
{
    switch (ordinal) {
    case 1: return PROC(ispace_1);
    case 2: return PROC(ispace_2);
    case 3: return PROC(load_bitmap);
    case 4: return PROC(ispace_4);
    case 5: return PROC(ispace_5);
    case 6: return PROC(make_mask);
    case 7: return PROC(ispace_7);
    case 8: return PROC(ispace_8);
    case 9: return PROC(ispace_9);
    case 10: return PROC(ispace_10);
    case 12: return PROC(ispace_12);
    case 14: return PROC(ispace_14);
    case 15: return PROC(ispace_15);
    case 17: return PROC(ispace_17);
    case 18: return PROC(ispace_18);
    case 24: return PROC(ispace_24);
    case 29: return PROC(ispace_29);
    case 32: return PROC(ispace_32);
    case 33: return PROC(ispace_33);
    case 34: return PROC(ispace_34);
    case 35: return PROC(ispace_35);
    case 36: return PROC(ispace_36);
    case 41: return PROC(ispace_41);
    default: return NULL;
    }
}
