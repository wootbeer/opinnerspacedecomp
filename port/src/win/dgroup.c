/* The game's data segment: plain globals live here at their 1994 offsets
 * and start with the bytes of INSPACE.EXE's data segment. */
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "globals.h"
#include "ne.h"

#define DGROUP_SEG 19

uint8_t dgroup[0x10000];

int dgroup_init(const char *exe_path)
{
    NeFile f;
    uint8_t *seg;
    uint32_t size;
    int i;

    if (!ne_open(&f, exe_path))
        return 0;
    seg = ne_segment(&f, DGROUP_SEG, &size);
    ne_close(&f);
    if (!seg)
        return 0;
    memcpy(dgroup, seg, size < sizeof dgroup ? size : sizeof dgroup);
    free(seg);
    for (i = 0; i < game_near_ptr_count; i++) {
        uint16_t off = game_near_ptrs[i].off;
        uint16_t w = (uint16_t)(dgroup[off] | dgroup[off + 1] << 8);
        *game_near_ptrs[i].addr = w ? dgroup + w : NULL;
    }
    return 1;
}
