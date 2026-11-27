/* The help viewer: a Windows 3.1 help file read from the user's data
 * (hlpfile.c) and shown in a window of its own (winhelp.c). */
#ifndef WINHELP_H
#define WINHELP_H

#include "winrt.h"

/* The parsed file.  Topics are numbered 0.. in file order. */
typedef struct Hlp Hlp;
enum { HLP_OK, HLP_MISSING, HLP_UNSUPPORTED };
int hlp_open(const char *host_path, Hlp **out);
void hlp_close(Hlp *h);
const char *hlp_title(const Hlp *h);
int hlp_topic_count(const Hlp *h);
const char *hlp_topic_title(const Hlp *h, int topic);
int hlp_topic_of_context(const Hlp *h, uint32_t number);   /* |CTXOMAP; -1: none */
int hlp_browse(const Hlp *h, int topic, int forward);       /* the << and >> sequence; -1: none */

typedef struct {
    char face[32];
    int height;                 /* pixels */
    int bold, italic, underline;
    COLORREF color;
} HlpFont;
int hlp_font_count(const Hlp *h);
const HlpFont *hlp_font(const Hlp *h, int i);

/* A topic's contents in order: paragraph formats, text in the current
 * font, breaks and hotspots.  Distances are pixels. */
#define HLP_TABS 16
enum { HLP_LEFT, HLP_RIGHT, HLP_CENTER };
typedef struct {
    int left, right, first, above, below, align;
    int ntabs, tabs[HLP_TABS];
} HlpPara;
typedef enum { HLP_PARA, HLP_TEXT, HLP_FONT, HLP_LINE, HLP_END_PARA, HLP_TAB, HLP_LINK, HLP_LINK_END } HlpKind;
typedef struct {
    HlpKind kind;
    const char *s;              /* HLP_TEXT, n bytes */
    int n;
    int value;                  /* HLP_FONT: the font; HLP_LINK: the topic, -1 when not in this file */
    const HlpPara *para;        /* HLP_PARA */
} HlpItem;
typedef void (*HlpEmit)(void *ctx, const HlpItem *item);
void hlp_topic_walk(const Hlp *h, int topic, HlpEmit emit, void *ctx);

/* WinHelp's commands for the viewer (winhelp.c). */
#define HELP_QUIT 0x0002
#define HELP_HELPONHELP 0x0004
/* Opens the viewer on dos_path (loaded again when it is another file)
 * at cmd's topic, or raises it; HLP_OK, or why the file cannot be shown. */
int winhelp_open(const char *dos_path, UINT cmd, DWORD data);
void winhelp_quit(void);

#endif
