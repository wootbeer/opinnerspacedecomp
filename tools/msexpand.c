/* msexpand: expand one Microsoft COMPRESS file (KWAJ or SZDD) with libmspack.
 * usage: msexpand IN OUT
 * Prints the original file name stored in the header (KWAJ), if any.
 * Build: cc -std=c99 -Wall -Wextra -pedantic -O2 -o msexpand msexpand.c -lmspack
 */
#include <mspack.h>
#include <stdio.h>
#include <string.h>

static int expand_kwaj(const char *in, const char *out)
{
    struct mskwaj_decompressor *d = mspack_create_kwaj_decompressor(NULL);
    struct mskwajd_header *h;
    int err;

    if (!d)
        return -1;
    h = d->open(d, in);
    if (!h) {
        mspack_destroy_kwaj_decompressor(d);
        return 1;                       /* not KWAJ */
    }
    if (h->filename)
        printf("%s\n", h->filename);
    err = d->extract(d, h, out);
    d->close(d, h);
    mspack_destroy_kwaj_decompressor(d);
    return err == MSPACK_ERR_OK ? 0 : -1;
}

static int expand_szdd(const char *in, const char *out)
{
    struct msszdd_decompressor *d = mspack_create_szdd_decompressor(NULL);
    struct msszddd_header *h;
    int err;

    if (!d)
        return -1;
    h = d->open(d, in);
    if (!h) {
        mspack_destroy_szdd_decompressor(d);
        return 1;
    }
    if (h->missing_char)
        printf("%c\n", h->missing_char);
    err = d->extract(d, h, out);
    d->close(d, h);
    mspack_destroy_szdd_decompressor(d);
    return err == MSPACK_ERR_OK ? 0 : -1;
}

int main(int argc, char **argv)
{
    int r;

    if (argc != 3) {
        fprintf(stderr, "usage: msexpand IN OUT\n");
        return 2;
    }
    r = expand_kwaj(argv[1], argv[2]);
    if (r == 1)
        r = expand_szdd(argv[1], argv[2]);
    if (r != 0) {
        fprintf(stderr, "msexpand: cannot expand %s\n", argv[1]);
        return 1;
    }
    return 0;
}
