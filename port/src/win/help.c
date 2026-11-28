/* WinHelp: the game's help file, <Language>_HELP.HLP (the Help menu, the
 * Navigation window's Help button; ISPACE.DLL's Game Settings and
 * Joystick dialogs ask for files under SndPath, which are not there).
 * The file is shown by the port's viewer (winhelp.c).  As in Windows 3.1
 * the call succeeds whether the file is there or not: WINHELP.EXE, not
 * the caller, told the user about a missing file.  A missing file is
 * looked for as the game's own help file in the game folder, unless
 * [Port] HelpMissing=1 keeps 1994's box (port/NOTES-port.md "Help"). */
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include "winhelp.h"

static int exists(const char *dos_path)
{
    OFSTRUCT of;

    return OpenFile(dos_path, &of, OF_EXIST) != HFILE_ERROR;
}

/* The file to show: the one asked for, or the game's
 * C:\SPACE\<Language>_HELP.HLP in its place when it is missing. */
static void resolve(const char *file, char *path, size_t size)
{
    char language[5];

    SDL_strlcpy(path, file, size);
    if (exists(path) || port_option("HelpMissing"))
        return;
    GetPrivateProfileString("Inner Space", "Language", "", language, sizeof language, "INSPACE.INI");
    SDL_snprintf(path, size, "%s%s_HELP.HLP", GAME_DIR, language);
    SDL_Log("help: %s is missing; %s instead", file, path);
}

BOOL WinHelp(HWND w, LPCSTR file, UINT cmd, DWORD data)
{
    static const char *const problems[] = {NULL, "Cannot find the file %s.",
                                           "%s is not a Windows 3.1 help file the port can show."};
    char path[260], text[320];
    int status;

    (void)w;
    if (cmd == HELP_QUIT) {
        winhelp_quit();
        return 1;
    }
    resolve(file ? file : "", path, sizeof path);
    SDL_Log("help: %s, %s %lu", path, cmd == HELP_CONTEXT ? "context" : "command",
            (unsigned long)(cmd == HELP_CONTEXT ? data : cmd));
    status = winhelp_open(path, cmd, data);
    if (status != HLP_OK) {
        SDL_snprintf(text, sizeof text, problems[status], path);
        MessageBox(0, text, "Help", MB_ICONEXCLAMATION);
    }
    return 1;
}
