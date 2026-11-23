/* NE files and the OPTLOADER (SLR Systems, 1993) LZ format; see
 * tools/README.md and tools/optl_lz.py. */
#include "ne.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned rd16(const uint8_t *p)
{
    return p[0] | p[1] << 8;
}

int ne_open(NeFile *f, const char *path)
{
    FILE *fp = fopen(path, "rb");
    long n;

    memset(f, 0, sizeof *f);
    if (!fp)
        return 0;
    fseek(fp, 0, SEEK_END);
    n = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    f->data = malloc(n > 0 ? (size_t)n : 1);
    if (!f->data || n < 0x40 || fread(f->data, 1, (size_t)n, fp) != (size_t)n) {
        fclose(fp);
        ne_close(f);
        return 0;
    }
    fclose(fp);
    f->size = (size_t)n;
    f->ne = rd16(f->data + 0x3c) | (size_t)rd16(f->data + 0x3e) << 16;
    if (f->ne + 0x40 > f->size || f->data[f->ne] != 'N' || f->data[f->ne + 1] != 'E') {
        ne_close(f);
        return 0;
    }
    return 1;
}

void ne_close(NeFile *f)
{
    free(f->data);
    memset(f, 0, sizeof *f);
}

/* LZ bit reader: 16-bit words, most significant bit first; a new word is
 * fetched as soon as the last bit of the previous one is used. */
typedef struct {
    const uint8_t *src;
    size_t pos, end;
    unsigned buf, left;
} Bits;

static unsigned next_word(Bits *r)
{
    unsigned w = r->pos + 1 < r->end ? rd16(r->src + r->pos) : 0;

    r->pos += 2;
    return w;
}

static unsigned bit(Bits *r)
{
    unsigned b = r->buf >> 15 & 1;

    r->buf = r->buf << 1 & 0xffff;
    if (--r->left == 0) {
        r->buf = next_word(r);
        r->left = 16;
    }
    return b;
}

static unsigned bits(Bits *r, int n)
{
    unsigned v = 0;

    while (n--)
        v = v << 1 | bit(r);
    return v;
}

static unsigned byte(Bits *r)
{
    return r->pos < r->end ? r->src[r->pos++] : 0;
}

/* Match length: 0 for the no-op marker, -1 for the end. */
static int lz_length(Bits *r)
{
    unsigned n;

    if (!bit(r))
        return 2 | bit(r);
    if (!bit(r))
        return 4 | bit(r);
    if (!bit(r))
        return 6 | bit(r);
    if (!bit(r))
        return 8 + bits(r, 2);
    if (!bit(r))
        return 12 + bits(r, 3);
    n = byte(r);
    if (n < 0x81)
        return (int)n;
    return n == 0x81 ? 0 : -1;
}

static unsigned lz_dist_high(Bits *r)
{
    if (!bit(r)) {
        if (!bit(r))
            return 0;
        if (!bit(r))
            return 1;
        return 2 + bits(r, 1);
    }
    if (!bit(r)) {
        if (!bit(r))
            return 4 + bits(r, 2);
        return 8 + bits(r, 3);
    }
    if (!bit(r))
        return 0x10 + bits(r, 4);
    if (!bit(r))
        return 0x20 + bits(r, 4);
    if (!bit(r))
        return 0x30 + bits(r, 4);
    return 0x40 + bits(r, 6);
}

/* Decodes the stream at src into out (at most cap bytes); returns the
 * number of bytes written. */
static size_t lz_decode(const uint8_t *src, size_t len, uint8_t *out, size_t cap)
{
    Bits r;
    size_t n = 0;

    r.src = src;
    r.pos = 0;
    r.end = len;
    r.buf = next_word(&r);
    r.left = 16;
    for (;;) {
        int k, i;
        size_t dist;

        if (bit(&r)) {
            unsigned c = byte(&r);
            if (n < cap)
                out[n++] = (uint8_t)c;
            continue;
        }
        k = lz_length(&r);
        if (k < 0)
            return n;
        if (k == 0)
            continue;
        dist = (k == 2 ? 0 : lz_dist_high(&r)) << 8;
        dist = (dist | byte(&r)) + 1;
        if (dist > n)
            return n;
        for (i = 0; i < k && n < cap; i++, n++)
            out[n] = out[n - dist];
    }
}

uint8_t *ne_segment(const NeFile *f, int n, uint32_t *size)
{
    const uint8_t *h = f->data + f->ne;
    const uint8_t *s;
    unsigned shift = rd16(h + 0x32);
    size_t off, len, alloc;
    uint8_t *out;

    if (n < 1 || n > (int)rd16(h + 0x1c))
        return NULL;
    s = h + rd16(h + 0x22) + 8 * (n - 1);
    off = (size_t)rd16(s) << shift;
    len = rd16(s + 2) ? rd16(s + 2) : 0x10000;
    alloc = rd16(s + 6) ? rd16(s + 6) : 0x10000;
    if (!rd16(s))
        len = 0;
    if (off + len > f->size)
        return NULL;
    out = calloc(alloc < len ? len : alloc, 1);
    if (!out)
        return NULL;
    if (rd16(h + 0x0c) & 0x0800 && n > 1 && len > 2)
        lz_decode(f->data + off + 2, len - 2, out, alloc);
    else if (len)
        memcpy(out, f->data + off, len);
    if (size)
        *size = (uint32_t)(alloc < len ? len : alloc);
    return out;
}

/* Compares a resource-table name (Pascal string) with s, ignoring case. */
static int name_is(const uint8_t *p, const char *s)
{
    unsigned i, n = p[0];

    if (strlen(s) != n)
        return 0;
    for (i = 0; i < n; i++)
        if (toupper(p[1 + i]) != toupper((unsigned char)s[i]))
            return 0;
    return 1;
}

static int id_matches(const uint8_t *table, unsigned v, uint16_t id, const char *name)
{
    if (v & 0x8000)
        return !name && (v & 0x7fff) == id;
    return name && name_is(table + v, name);
}

const uint8_t *ne_resource(const NeFile *f, uint16_t type, const char *type_name,
                           uint16_t id, const char *name, uint32_t *size)
{
    const uint8_t *h = f->data + f->ne;
    const uint8_t *table, *p;
    unsigned shift;

    if (rd16(h + 0x24) == rd16(h + 0x26))
        return NULL;
    table = h + rd16(h + 0x24);
    shift = rd16(table);
    p = table + 2;
    while (rd16(p)) {
        unsigned count = rd16(p + 2), i;
        int match = id_matches(table, rd16(p), type, type_name);

        p += 8;
        for (i = 0; i < count; i++, p += 12) {
            size_t off = (size_t)rd16(p) << shift;
            size_t len = (size_t)rd16(p + 2) << shift;
            if (match && id_matches(table, rd16(p + 6), id, name) && off + len <= f->size) {
                if (size)
                    *size = (uint32_t)len;
                return f->data + off;
            }
        }
    }
    return NULL;
}
