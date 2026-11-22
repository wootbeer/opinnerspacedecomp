/* INSPACE.EXE segment 14 (selector 1068). */
#include "inspace.h"

/* Object records: array of 0x15a-byte records at DS:7092 [inferred base].
 * Fields named by offset in the record (DS address = 0x7092 + offset). */
typedef struct {
    char pad_000[0xd4];
    int f_0d4;                      /* DS:7166 */
    char pad_0d6[0x15a - 0xd6];
} OBJ15A;
extern OBJ15A g_7092[];

/* @addr 14:4520 */
int far fn_14_4520(int key, int last)
{
    int i;

    for (i = 0; i <= last; i++)
        if (g_7092[i].f_0d4 == key)
            return i;
    return -1;
}
