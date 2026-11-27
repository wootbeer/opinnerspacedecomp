/* Start-up of the native layer and the call of the game's WinMain. */
#include <stdio.h>

#include "user.h"
#include "win.h"
#include "globals.h"

int win_init(void)
{
    char exe[1024];

    profile_first_start();
    gdi_init();
    controls_register();
    dialog_register();
    menu_register();
    if (!dos_to_host(GAME_DIR "INSPACE.EXE", exe, sizeof exe) || !dgroup_init(exe) || !module_init()) {
        fprintf(stderr, "cannot read INSPACE.EXE (%s)\n", exe);
        return 0;
    }
    return 1;
}

int win_run(const char *cmdline)
{
    char cmd[128];

    snprintf(cmd, sizeof cmd, "%s", cmdline);
    return WinMain(module_exe(), 0, cmd, SW_SHOWNORMAL);
}
