/* Pilot match: INSPACE.EXE segment 9 (selector 1040). */

/* @addr 9:88ba */
int far fn_09_88ba(int x)
{
    if (x >= 0)
        return x;
    return -x;
}
