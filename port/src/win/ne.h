/* Reading the original NE files (INSPACE.EXE and the DLLs) at run time:
 * segments, OPTLOADER-packed segments and resources. */
#ifndef NE_H
#define NE_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *data;
    size_t size;
    size_t ne;              /* offset of the NE header */
} NeFile;

/* Resource types by number. */
enum {
    RT_CURSOR_ = 1, RT_BITMAP_ = 2, RT_ICON_ = 3, RT_MENU_ = 4, RT_DIALOG_ = 5,
    RT_STRING_ = 6, RT_ACCELERATOR_ = 9, RT_RCDATA_ = 10, RT_GROUP_ICON_ = 14
};

int  ne_open(NeFile *f, const char *path);
void ne_close(NeFile *f);

/* Segment n (1-based) as loaded: unpacked when the file is OPTLOADER-packed,
 * zero-filled up to its allocation size.  Returns a malloc'd block. */
uint8_t *ne_segment(const NeFile *f, int n, uint32_t *size);

/* Finds a resource.  type and name are either a number (name == NULL) or a
 * string compared case-insensitively. */
const uint8_t *ne_resource(const NeFile *f, uint16_t type, const char *type_name,
                           uint16_t id, const char *name, uint32_t *size);

#endif
