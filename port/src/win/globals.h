/* The DGROUP image and the globals that hold native pointers (generated
 * in game/globals.c). */
#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

typedef struct {
    uint16_t off;           /* DS offset of the pointer */
    void **addr;
} NearPtrInit;

extern const NearPtrInit game_near_ptrs[];
extern const int game_near_ptr_count;

/* Loads the data segment of INSPACE.EXE (segment 19) into the DGROUP image
 * and points the near-pointer globals into it.  Returns 0 when the file
 * cannot be read. */
int dgroup_init(const char *exe_path);

#endif
