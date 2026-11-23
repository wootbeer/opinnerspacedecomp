# Native port

Playable, native version of Operation: Inner Space, built from the decomp in
`../src/inspace` (which stays the byte-exact archival source and is not
changed for the port).

Goals: the same gameplay as the original; native code (no emulator, no
general Windows layer); Windows first, Android later; plain C that a person
can work on.

## Layout

- `src/main.c` – entry point and main loop.
- `src/video.c` – 256-colour framebuffer shown through SDL3; frames can be
  saved (`--dump`) to compare with the original.
- `src/platform/` – everything machine-specific the game needs (time, date,
  folders and files to explore, data location). One implementation per
  platform; game code never calls the OS directly.

- `src/game/` – the game logic, generated from the decomp (see
  `NOTES-port.md`).
- `src/win/` – native versions of the Windows calls the game makes, one
  module per area, each doing only what this game needs; status in
  `RUNTIME.md`.

## Building

Needs CMake and SDL3.

    cmake -S port -B build -DCMAKE_PREFIX_PATH=<SDL3 install>
    cmake --build build

Run headless (tests): `SDL_VIDEO_DRIVER=offscreen build/inspace --frames 3 --dump out.ppm`.

Game data (INSPACE.EXE and the other original files) is read from `data/`
or the folder in `INSPACE_DATA`; it is not part of the repository. The game
sees it as `C:\SPACE\`; `C:\WINDOWS\` (INSPACE.INI) is the platform's
settings folder (SDL pref path).

Windows: `cmake -S port -B build-win -DCMAKE_TOOLCHAIN_FILE=<mingw.cmake>
-DCMAKE_PREFIX_PATH=<SDL3 Windows install>`.

## Quirks

Original behaviour is the default. Crashes and memory-safety bugs are fixed;
bugs whose fix would change gameplay noticeably stay as in the original,
with the fix available as a setting. Each is listed in `QUIRKS.md` (to come).

## File-name case

C identifiers are case-sensitive everywhere, so names in code are not an
issue. File names are: Windows ignores case, Linux and Android do not.
- Source and include file names in `port/` are lowercase, and `#include`s
  match them exactly.
- The platform module opens data files case-insensitively (the original
  files are uppercase; a user's copy may not be).
- Folder scanning matches DOS-style patterns (`*.EXE`) case-insensitively;
  name comparisons the game makes (it ran on uppercase DOS names) are
  case-insensitive too. Names are shown upper-case where the original did.
