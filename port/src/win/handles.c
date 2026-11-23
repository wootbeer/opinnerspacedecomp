/* One handle table for all object kinds.  Handles start above 0x100 so
 * that they never look like the small error values Windows used. */

#include "winrt.h"

#define MAX_HANDLES 8192
#define HANDLE_BASE 0x100

static struct {
    int type;
    void *obj;
} table[MAX_HANDLES];
static int next_free;

uint16_t handle_new(int type, void *obj)
{
    int i;

    for (i = 0; i < MAX_HANDLES; i++) {
        int k = (next_free + i) % MAX_HANDLES;
        if (table[k].type == H_FREE) {
            table[k].type = type;
            table[k].obj = obj;
            next_free = k + 1;
            return (uint16_t)(HANDLE_BASE + k);
        }
    }
    return 0;
}

static int slot(uint16_t h)
{
    int k = h - HANDLE_BASE;

    return k >= 0 && k < MAX_HANDLES ? k : -1;
}

void *handle_get(uint16_t h, int type)
{
    int k = slot(h);

    return k >= 0 && table[k].type == type ? table[k].obj : NULL;
}

int handle_type(uint16_t h)
{
    int k = slot(h);

    return k >= 0 ? table[k].type : H_FREE;
}

void handle_free(uint16_t h)
{
    int k = slot(h);

    if (k >= 0) {
        table[k].type = H_FREE;
        table[k].obj = NULL;
    }
}
