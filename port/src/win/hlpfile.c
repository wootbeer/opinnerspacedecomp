/* Windows 3.1 help files (HC31, |SYSTEM 1.21), read from the user's data:
 * the internal file system's B+ tree directory, |SYSTEM (title), |FONT,
 * |CTXOMAP (context numbers), |CONTEXT (hotspot hashes), |TTLBTREE
 * (titles) and |TOPIC's uncompressed topic records.  LZ77 and phrase
 * compression, pictures and 3.0 files are not read.  Every read is
 * checked against the file's size (port/NOTES-port.md "Help"). */
#include <SDL3/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "winhelp.h"

#define MAX_FILE (16u << 20)
#define HFS_MAGIC 0x00035F3Fu
#define BTREE_MAGIC 0x293B
#define BTREE_HEADER 38
#define SYSTEM_MAGIC 0x036C
#define SYSTEM_TITLE 1
#define BLOCK 4096u                 /* |TOPIC blocks of an uncompressed 3.1 file */
#define BLOCK_HEADER 12u
#define LINK_HEADER 21u
#define TL_TOPICHDR 2
#define TL_DISPLAY 0x20
#define TL_TABLE 0x23
#define NONE 0xffffffffu

/* A bounded reader: reading past the end sets bad and gives zeros. */
typedef struct {
    const uint8_t *p;
    size_t n, at;
    int bad;
} Rd;

static int rd_has(Rd *r, size_t k)
{
    if (r->bad || r->n - r->at < k)
        r->bad = 1;
    return !r->bad;
}

static unsigned rd_u8(Rd *r)
{
    return rd_has(r, 1) ? r->p[r->at++] : 0;
}

static unsigned rd_u16(Rd *r)
{
    unsigned lo = rd_u8(r);

    return lo | rd_u8(r) << 8;
}

static uint32_t rd_u32(Rd *r)
{
    uint32_t lo = rd_u16(r);

    return lo | (uint32_t)rd_u16(r) << 16;
}

static void rd_skip(Rd *r, size_t k)
{
    if (rd_has(r, k))
        r->at += k;
}

static int rd_peek_odd(Rd *r)
{
    return rd_has(r, 1) && r->p[r->at] & 1;
}

/* HC31's compressed numbers: a byte or a word, a word or a dword. */
static unsigned rd_cword(Rd *r)
{
    return rd_peek_odd(r) ? rd_u16(r) >> 1 : rd_u8(r) >> 1;
}

static int rd_cshort(Rd *r)
{
    return rd_peek_odd(r) ? (int)(rd_u16(r) >> 1) - 0x4000 : (int)(rd_u8(r) >> 1) - 0x40;
}

static uint32_t rd_clong(Rd *r)
{
    return rd_peek_odd(r) ? rd_u32(r) >> 1 : rd_u16(r) >> 1;
}

/* A NUL-terminated string; its length in *n (to the end when unterminated). */
static const char *rd_str(Rd *r, int *n)
{
    const char *s = (const char *)r->p + r->at;
    const uint8_t *end;

    if (r->bad) {
        *n = 0;
        return "";
    }
    end = memchr(r->p + r->at, 0, r->n - r->at);
    *n = (int)((end ? (size_t)(end - r->p) : r->n) - r->at);
    r->at += (size_t)*n + (end != NULL);
    return s;
}

static Rd rd_range(const Rd *r, size_t at, size_t n)
{
    Rd s = {r->p, 0, 0, 1};

    if (!r->bad && at <= r->n && n <= r->n - at)
        s = (Rd){r->p + at, n, 0, 0};
    return s;
}

typedef struct {
    uint32_t offset;            /* TOPICOFFSET of the topic's start */
    size_t link;                /* its header record in text */
    uint32_t browse[2];
    char title[80];
} Topic;

typedef struct {
    uint32_t key, offset;
} Pair;

struct Hlp {
    uint8_t *file;
    size_t size;
    char title[128];
    uint8_t *text;              /* |TOPIC's blocks without their headers */
    size_t text_size;
    uint32_t first_link;
    Topic *topics;
    int ntopics;
    Pair *numbers, *hashes;     /* |CTXOMAP, |CONTEXT */
    int nnumbers, nhashes;
    HlpFont *fonts;
    int nfonts;
};

/* An internal file: its used space after the 9-byte header. */
static Rd hfs_file(const Hlp *h, uint32_t at)
{
    Rd all = {h->file, h->size, 0, 0}, hdr = rd_range(&all, at, 9);
    uint32_t used;

    rd_u32(&hdr);
    used = rd_u32(&hdr);
    return rd_range(&all, (size_t)at + 9, used);
}

/* Calls leaf for each entry of a B+ tree, in key order; leaf reads one
 * entry from the page.  0 when the tree is damaged. */
typedef void (*Leaf)(void *ctx, Rd *page);

static int btree_each(Rd tree, Leaf leaf, void *ctx)
{
    unsigned size, page, levels, pages, visited, n;
    Rd hdr = tree, pg;

    if (rd_u16(&hdr) != BTREE_MAGIC)
        return 0;
    rd_skip(&hdr, 2);
    size = rd_u16(&hdr);
    rd_skip(&hdr, 16 + 2 + 2);
    page = rd_u16(&hdr);
    rd_skip(&hdr, 2);
    pages = rd_u16(&hdr);
    levels = rd_u16(&hdr);
    if (hdr.bad || size < 8)
        return 0;
    for (; levels > 1; levels--) {
        pg = rd_range(&tree, BTREE_HEADER + (size_t)page * size, size);
        rd_skip(&pg, 4);
        page = rd_u16(&pg);
        if (pg.bad)
            return 0;
    }
    for (visited = 0; page != 0xffff && visited < pages; visited++) {
        pg = rd_range(&tree, BTREE_HEADER + (size_t)page * size, size);
        rd_skip(&pg, 2);
        n = rd_u16(&pg);
        rd_skip(&pg, 2);
        page = rd_u16(&pg);
        while (n-- && !pg.bad)
            leaf(ctx, &pg);
        if (pg.bad)
            return 0;
    }
    return 1;
}

/* The directory: the internal files this reader uses. */
static const char *const wanted[] = {"|SYSTEM", "|TOPIC", "|FONT", "|CTXOMAP", "|CONTEXT", "|TTLBTREE"};
enum { F_SYSTEM, F_TOPIC, F_FONT, F_CTXOMAP, F_CONTEXT, F_TTLBTREE, F_COUNT };

static void dir_entry(void *ctx, Rd *pg)
{
    uint32_t *at = ctx;
    int n, i;
    const char *name = rd_str(pg, &n);
    uint32_t offset = rd_u32(pg);

    for (i = 0; i < F_COUNT; i++)
        if ((int)strlen(wanted[i]) == n && memcmp(name, wanted[i], (size_t)n) == 0)
            at[i] = offset;
}

/* |SYSTEM: 3.1 without compression, and the title. */
static int read_system(Hlp *h, Rd r)
{
    unsigned minor, flags, type, size;
    Rd rec;
    int n;
    const char *s;

    if (rd_u16(&r) != SYSTEM_MAGIC)
        return 0;
    minor = rd_u16(&r);
    rd_skip(&r, 2 + 4);
    flags = rd_u16(&r);
    if (r.bad || minor <= 16 || flags != 0)
        return 0;
    while (r.at < r.n && !r.bad) {
        type = rd_u16(&r);
        size = rd_u16(&r);
        rec = rd_range(&r, r.at, size);
        rd_skip(&r, size);
        if (type != SYSTEM_TITLE)
            continue;
        s = rd_str(&rec, &n);
        SDL_strlcpy(h->title, s, (size_t)SDL_min(n + 1, (int)sizeof h->title));
    }
    return 1;
}

/* |FONT: face names, then 11-byte descriptors (attributes, half points,
 * family, face, colour). */
static void read_fonts(Hlp *h, Rd r)
{
    unsigned nfaces = rd_u16(&r), ndesc = rd_u16(&r), faces = rd_u16(&r), descs = rd_u16(&r), len, attr, face, i;
    uint8_t rgb[3];
    Rd d, f;
    HlpFont *font;
    int n;
    const char *s;

    if (r.bad || !nfaces || descs < faces || !(h->fonts = calloc(ndesc ? ndesc : 1, sizeof *h->fonts)))
        return;
    len = (descs - faces) / nfaces;
    d = rd_range(&r, descs, (size_t)ndesc * 11);
    for (i = 0; i < ndesc && !d.bad; i++) {
        font = &h->fonts[i];
        attr = rd_u8(&d);
        font->height = (int)rd_u8(&d) * 2 / 3;      /* half points at 96 dpi */
        rd_skip(&d, 1);
        face = rd_u16(&d);
        rgb[0] = (uint8_t)rd_u8(&d);
        rgb[1] = (uint8_t)rd_u8(&d);
        rgb[2] = (uint8_t)rd_u8(&d);
        font->color = RGB(rgb[0], rgb[1], rgb[2]);
        rd_skip(&d, 3);
        font->bold = attr & 1;
        font->italic = attr >> 1 & 1;
        font->underline = attr >> 2 & 1;
        f = rd_range(&r, faces + (size_t)face % nfaces * len, len);
        s = rd_str(&f, &n);
        SDL_strlcpy(font->face, s, (size_t)SDL_min(n + 1, (int)sizeof font->face));
        h->nfonts += !d.bad;
    }
}

static void read_numbers(Hlp *h, Rd r)
{
    unsigned n = rd_u16(&r), i;

    if (r.bad || !(h->numbers = calloc(n ? n : 1, sizeof *h->numbers)))
        return;
    for (i = 0; i < n && !r.bad; i++) {
        h->numbers[i].key = rd_u32(&r);
        h->numbers[i].offset = rd_u32(&r);
        h->nnumbers += !r.bad;
    }
}

static void hash_entry(void *ctx, Rd *pg)
{
    Hlp *h = ctx;
    Pair p;
    Pair *grown;

    p.key = rd_u32(pg);
    p.offset = rd_u32(pg);
    if (pg->bad || !(grown = realloc(h->hashes, (size_t)(h->nhashes + 1) * sizeof *grown)))
        return;
    h->hashes = grown;
    h->hashes[h->nhashes++] = p;
}

/* A TOPICOFFSET's topic: the last one starting at or before it. */
static int topic_at(const Hlp *h, uint32_t offset)
{
    int t = -1;

    if (offset == NONE)
        return -1;
    while (t + 1 < h->ntopics && h->topics[t + 1].offset <= offset)
        t++;
    return t;
}

static void title_entry(void *ctx, Rd *pg)
{
    Hlp *h = ctx;
    uint32_t offset = rd_u32(pg);
    int n, t;
    const char *s = rd_str(pg, &n);

    t = topic_at(h, offset);
    if (!pg->bad && t >= 0 && h->topics[t].offset == offset)
        SDL_strlcpy(h->topics[t].title, s, (size_t)SDL_min(n + 1, (int)sizeof h->topics[t].title));
}

/* A TOPICPOS (block << 14 | offset in the block) as an index in text;
 * NONE when it is not in it. */
static size_t text_pos(const Hlp *h, uint32_t pos)
{
    size_t off = pos & 0x3fff, at = (size_t)(pos >> 14) * (BLOCK - BLOCK_HEADER) + off - BLOCK_HEADER;

    return pos == NONE || off < BLOCK_HEADER || at >= h->text_size ? (size_t)NONE : at;
}

typedef struct {
    uint32_t size, len2, next, len1;
    unsigned type;
    Rd data1, data2;
} Link;

static int read_link(const Hlp *h, size_t at, Link *l)
{
    Rd text = {h->text, h->text_size, 0, 0}, r = rd_range(&text, at, LINK_HEADER);

    l->size = rd_u32(&r);
    l->len2 = rd_u32(&r);
    rd_skip(&r, 4);
    l->next = rd_u32(&r);
    l->len1 = rd_u32(&r);
    l->type = rd_u8(&r);
    if (r.bad || l->len1 < LINK_HEADER || l->size < l->len1)
        return 0;
    l->data1 = rd_range(&text, at + LINK_HEADER, l->len1 - LINK_HEADER);
    l->data2 = rd_range(&text, at + l->len1, SDL_min(l->size - l->len1, l->len2));
    return !l->data1.bad && !l->data2.bad;
}

/* The display records' text length: TopicLength after TopicSize. */
static unsigned display_length(Rd d)
{
    rd_clong(&d);
    return rd_cword(&d);
}

static int add_topic(Hlp *h, size_t at, uint32_t offset, Rd hdr)
{
    Topic *grown = realloc(h->topics, (size_t)(h->ntopics + 1) * sizeof *grown), *t;

    if (!grown)
        return 0;
    h->topics = grown;
    t = &h->topics[h->ntopics++];
    memset(t, 0, sizeof *t);
    t->offset = offset;
    t->link = at;
    rd_skip(&hdr, 4);
    t->browse[0] = rd_u32(&hdr);
    t->browse[1] = rd_u32(&hdr);
    return 1;
}

/* |TOPIC: the blocks joined, then the topic records walked in order.  A
 * TOPICOFFSET is the block << 15 plus the display text before it in that
 * block. */
static int read_topics(Hlp *h, Rd r)
{
    size_t blocks = (r.n + BLOCK - 1) / BLOCK, b, at, next;
    uint32_t pos, offset = 0, block = NONE;
    Rd first = rd_range(&r, 4, 4);
    Link l;

    if (!(h->text = malloc(blocks * BLOCK)))
        return 0;
    for (b = 0; b < blocks; b++) {
        size_t start = b * BLOCK + BLOCK_HEADER, end = SDL_min(r.n, (b + 1) * BLOCK);

        if (start < end) {
            memcpy(h->text + h->text_size, r.p + start, end - start);
            h->text_size += end - start;
        }
    }
    pos = rd_u32(&first);
    for (at = text_pos(h, pos); at != (size_t)NONE && read_link(h, at, &l); at = next, pos = l.next) {
        if (pos >> 14 != block) {
            block = pos >> 14;
            offset = block << 15;
        }
        if (l.type == TL_TOPICHDR && !add_topic(h, at, offset, l.data1))
            return 0;
        if (l.type == TL_DISPLAY || l.type == TL_TABLE)
            offset += display_length(l.data1);
        next = text_pos(h, l.next);
        if (next != (size_t)NONE && next <= at)
            break;
    }
    return h->ntopics > 0;
}

int hlp_open(const char *host_path, Hlp **out)
{
    FILE *f = fopen(host_path, "rb");
    Hlp *h;
    long size;
    Rd hdr;
    uint32_t at[F_COUNT];
    int ok;

    *out = NULL;
    if (!f)
        return HLP_MISSING;
    h = calloc(1, sizeof *h);
    ok = h && fseek(f, 0, SEEK_END) == 0 && (size = ftell(f)) > 0 && (unsigned long)size <= MAX_FILE &&
         fseek(f, 0, SEEK_SET) == 0 && (h->file = malloc((size_t)size)) &&
         fread(h->file, 1, (size_t)size, f) == (size_t)size;
    fclose(f);
    if (!ok) {
        hlp_close(h);
        return HLP_UNSUPPORTED;
    }
    h->size = (size_t)size;
    memset(at, 0, sizeof at);
    hdr = (Rd){h->file, h->size, 0, 0};
    ok = rd_u32(&hdr) == HFS_MAGIC && btree_each(hfs_file(h, rd_u32(&hdr)), dir_entry, at) && at[F_SYSTEM] &&
         at[F_TOPIC] && read_system(h, hfs_file(h, at[F_SYSTEM])) && read_topics(h, hfs_file(h, at[F_TOPIC]));
    if (!ok) {
        hlp_close(h);
        return HLP_UNSUPPORTED;
    }
    if (at[F_FONT])
        read_fonts(h, hfs_file(h, at[F_FONT]));
    if (at[F_CTXOMAP])
        read_numbers(h, hfs_file(h, at[F_CTXOMAP]));
    if (at[F_CONTEXT])
        btree_each(hfs_file(h, at[F_CONTEXT]), hash_entry, h);
    if (at[F_TTLBTREE])
        btree_each(hfs_file(h, at[F_TTLBTREE]), title_entry, h);
    *out = h;
    return HLP_OK;
}

void hlp_close(Hlp *h)
{
    if (!h)
        return;
    free(h->file);
    free(h->text);
    free(h->topics);
    free(h->numbers);
    free(h->hashes);
    free(h->fonts);
    free(h);
}

const char *hlp_title(const Hlp *h)
{
    return h->title[0] ? h->title : "Windows Help";
}

int hlp_topic_count(const Hlp *h)
{
    return h->ntopics;
}

const char *hlp_topic_title(const Hlp *h, int topic)
{
    return topic >= 0 && topic < h->ntopics ? h->topics[topic].title : "";
}

static int topic_of(const Hlp *h, const Pair *p, int n, uint32_t key)
{
    int i;

    for (i = 0; i < n; i++)
        if (p[i].key == key)
            return topic_at(h, p[i].offset);
    return -1;
}

int hlp_topic_of_context(const Hlp *h, uint32_t number)
{
    return topic_of(h, h->numbers, h->nnumbers, number);
}

int hlp_browse(const Hlp *h, int topic, int forward)
{
    return topic >= 0 && topic < h->ntopics ? topic_at(h, h->topics[topic].browse[forward != 0]) : -1;
}

int hlp_font_count(const Hlp *h)
{
    return h->nfonts;
}

const HlpFont *hlp_font(const Hlp *h, int i)
{
    return &h->fonts[i];
}

/* A display record's paragraph format: TopicSize, TopicLength, two
 * unknown bytes, a word, then the fields its bits name (10-twip units). */
static void read_para(Rd *d, HlpPara *p)
{
    unsigned bits, i, n, stop;

    memset(p, 0, sizeof *p);
    rd_clong(d);
    rd_cword(d);
    rd_skip(d, 4);
    bits = rd_u16(d);
    if (bits & 0x0001)
        rd_clong(d);
    p->above = bits & 0x0002 ? rd_cshort(d) * 2 / 3 : 0;
    p->below = bits & 0x0004 ? rd_cshort(d) * 2 / 3 : 0;
    if (bits & 0x0008)
        rd_cshort(d);
    p->left = bits & 0x0010 ? rd_cshort(d) * 2 / 3 : 0;
    p->right = bits & 0x0020 ? rd_cshort(d) * 2 / 3 : 0;
    p->first = bits & 0x0040 ? rd_cshort(d) * 2 / 3 : 0;
    if (bits & 0x0100)
        rd_skip(d, 3);
    n = bits & 0x0200 ? (unsigned)SDL_max(0, rd_cshort(d)) : 0;
    for (i = 0; i < n && !d->bad; i++) {
        stop = rd_cword(d);
        if (stop & 0x4000)
            rd_cword(d);
        if (p->ntabs < HLP_TABS)
            p->tabs[p->ntabs++] = (int)(stop & 0x3fff) * 2 / 3;
    }
    p->align = bits & 0x0400 ? HLP_RIGHT : bits & 0x0800 ? HLP_CENTER : HLP_LEFT;
}

static void emit_kind(HlpEmit emit, void *ctx, HlpKind kind, int value)
{
    HlpItem it = {kind, NULL, 0, value, NULL};

    emit(ctx, &it);
}

/* One formatting command of a display record (at a NUL of its text);
 * 0 at its end or at one this reader cannot step over. */
static int command(const Hlp *h, Rd *d, HlpEmit emit, void *ctx)
{
    static const char nbsp[] = " ", nbhyphen[] = "-";
    unsigned c = rd_u8(d);
    HlpItem text = {HLP_TEXT, NULL, 1, 0, NULL};

    switch (c) {
    case 0x20:
        rd_skip(d, 4);
        break;
    case 0x21:
        rd_skip(d, 2);
        break;
    case 0x80:
        emit_kind(emit, ctx, HLP_FONT, (int)rd_u16(d));
        break;
    case 0x81:
        emit_kind(emit, ctx, HLP_LINE, 0);
        break;
    case 0x82:
        emit_kind(emit, ctx, HLP_END_PARA, 0);
        break;
    case 0x83:
        emit_kind(emit, ctx, HLP_TAB, 0);
        break;
    case 0x89:
        emit_kind(emit, ctx, HLP_LINK_END, 0);
        break;
    case 0x8B:
    case 0x8C:
        text.s = c == 0x8B ? nbsp : nbhyphen;
        emit(ctx, &text);
        break;
    case 0xC8:
    case 0xCC:                  /* a macro hotspot */
        rd_skip(d, rd_u16(d));
        emit_kind(emit, ctx, HLP_LINK, -1);
        break;
    case 0xE0:
    case 0xE1:
        rd_skip(d, 4);
        emit_kind(emit, ctx, HLP_LINK, -1);
        break;
    case 0xE2:
    case 0xE3:
    case 0xE6:
    case 0xE7:                  /* popups and jumps by context hash */
        emit_kind(emit, ctx, HLP_LINK, topic_of(h, h->hashes, h->nhashes, rd_u32(d)));
        break;
    case 0xEA:
    case 0xEB:
    case 0xEE:
    case 0xEF:                  /* into another file or window */
        rd_skip(d, rd_u16(d));
        emit_kind(emit, ctx, HLP_LINK, -1);
        break;
    default:                    /* 0xFF, pictures, unknown */
        return 0;
    }
    return !d->bad;
}

static void walk_display(const Hlp *h, const Link *l, HlpEmit emit, void *ctx)
{
    Rd d = l->data1, t = l->data2;
    HlpPara para;
    HlpItem it = {HLP_PARA, NULL, 0, 0, &para};
    int more = 1;

    read_para(&d, &para);
    if (d.bad)
        return;
    emit(ctx, &it);
    while (more && t.at < t.n) {
        it.kind = HLP_TEXT;
        it.s = rd_str(&t, &it.n);
        if (it.n)
            emit(ctx, &it);
        more = command(h, &d, emit, ctx);
    }
}

void hlp_topic_walk(const Hlp *h, int topic, HlpEmit emit, void *ctx)
{
    size_t at, next;
    Link l;

    if (topic < 0 || topic >= h->ntopics || !read_link(h, h->topics[topic].link, &l))
        return;
    for (at = text_pos(h, l.next); at != (size_t)NONE && read_link(h, at, &l) && l.type != TL_TOPICHDR; at = next) {
        if (l.type == TL_DISPLAY)
            walk_display(h, &l, emit, ctx);
        next = text_pos(h, l.next);
        if (next != (size_t)NONE && next <= at)
            break;
    }
}
