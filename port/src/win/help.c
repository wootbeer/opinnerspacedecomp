/* WinHelp: the game's help file, <Language>_HELP.HLP (the Help menu, the
 * Navigation window's Help button; ISPACE.DLL's Game Settings and
 * Joystick dialogs ask for files under SndPath).  The port has no help
 * viewer yet: the request is logged.  As in Windows 3.1 the call succeeds
 * whether the file is there or not: WINHELP.EXE, not the caller, told
 * the user about a missing file. */
#include <stdio.h>

#include "winrt.h"

#define HELP_QUIT 0x0002

BOOL WinHelp(HWND w, LPCSTR file, UINT cmd, DWORD data)
{
    OFSTRUCT of;

    (void)w;
    if (cmd == HELP_QUIT)
        return 1;
    fprintf(stderr, "help: %s, %s %lu: %s\n", file ? file : "", cmd == HELP_CONTEXT ? "topic" : "command",
            (unsigned long)(cmd == HELP_CONTEXT ? data : cmd),
            file && OpenFile(file, &of, OF_EXIST) != HFILE_ERROR ? "no help viewer in the port" : "no such file");
    return 1;
}
