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
  folders and files to explore, data location, sound output, MIDI music). One implementation per
  platform; game code never calls the OS directly.

- `src/game/` – the game logic, generated from the decomp (see
  `NOTES-port.md`).
- `src/win/` – native versions of the Windows calls the game makes, one
  module per area, each doing only what this game needs; status in
  `RUNTIME.md`.
- `third_party/` – code and data from elsewhere, each with its licence:
  - `stb/stb_truetype.h` (v1.28, public domain or MIT, licence at its end):
    the TrueType rasteriser for text.
  - `liberation/` (Liberation Fonts 2.1.5, SIL Open Font License 1.1,
    `LICENSE`): Sans Regular, Bold, Bold Italic and Serif Italic. The game
    asks for Windows' Arial and Times New Roman; Liberation Sans and Serif
    have the same metrics.

## Fonts

The game draws all its text with TrueType fonts made by `CreateFont` at
many heights and widths. `src/win/text.c` maps Arial (and any other face)
to Liberation Sans and Times New Roman to Liberation Serif, picks bold for
weights above 550, and rasterises each size on first use, one bit per pixel
as Windows 3.1 drew it. The build copies the font files to `fonts/` next
to the executable, where the game loads them at start (a missing style
falls back to the family's regular one).

## Building

Needs CMake and SDL3.

    cmake -S port -B build -DCMAKE_PREFIX_PATH=<SDL3 install>
    cmake --build build

Run headless (tests): `SDL_VIDEO_DRIVER=offscreen build/inspace --frames 3 --dump out.ppm`.

Command line:

- `--frames N`: run N frames (about 60 a second), then exit.
- `--dump FILE`: save the last frame as a PPM picture.
- `--keys "FRAME:KEY,..."`: press KEY at frame FRAME and release it two
  frames later. KEY is an SDL key name (`Escape`, `Return`, `Down`, `F4`,
  `X`, ...), modifiers before it with `+` (`Alt+X`, `Shift+Tab`). Example:
  `--frames 1700 --keys "1600:Escape" --dump out.ppm` shows the Restore
  Game dialog. `FRAME:KEY/HOLD` holds the key HOLD frames
  (`4100:Up/200` thrusts for about three seconds). Frames follow real
  time, so the frame a screen appears at varies a little between runs.
- `--shots N` (with `--dump FILE`): also save every Nth frame as
  `FILE-NNNNN.ppm`.
- `--audio-dump FILE.wav`: also write everything played (16-bit
  stereo, 11025 Hz) to FILE.wav. Without a sound device run with
  `SDL_AUDIO_DRIVER=dummy`, which plays in real time into nothing.
- `--mouse "FRAME:X,Y[,ACTION];..."`: move the mouse to framebuffer point
  (X, Y) at frame FRAME, then ACTION: `move` (the default), `down`, `up`,
  `click` (down, up two frames later), `dclick` (a double click's second
  press, then up), `rdown`, `rup`, `rclick`. Example:
  `--mouse "4000:300,200,rclick;4100:320,255,click"` opens the game's
  right-button menu in a wave and chooses Exit Game.

Game data (INSPACE.EXE and the other original files) is read from `data/`
or the folder in `INSPACE_DATA`; it is not part of the repository. The game
sees it as `C:\SPACE\`; `C:\WINDOWS\` (INSPACE.INI) is the platform's
settings folder (SDL pref path). The rest of the game's drives are the
user's folders: see "Drives and file names".

Windows: `cmake -S port -B build-win -DCMAKE_TOOLCHAIN_FILE=<mingw.cmake>
-DCMAKE_PREFIX_PATH=<SDL3 Windows install>`.

## Settings

Port options live in INSPACE.INI (the settings folder) under `[Port]`;
the switches are off unless set to 1.

- `CopyCheck=1`: the original copy check (ISPACE.DLL ordinal 24, mode 2).
  Off, the port reports a registered copy. On, it checks the key in
  INSPACE.EXE against the disk serial number or WIN.INI `PDev` as the
  original did, which the user's files normally fail: the title shows
  "limited inner space" and the New Game dialog offers only TRANSFORMER
  and fewer ships. Off by default so that no files in the Windows folder
  are needed (Android has none).
- `DriveC=<folder>` (any letter C-Z): the host folder the game sees as
  that drive, an absolute path in the host's form. It replaces the
  platform's choice for that letter ("Drives and file names").

## Game speed

The game paces itself by real time (36 frames a second in waves) but
measures the machine at start-up (INSPACE.INI `Calibrate`) and picks some
animation steps from it. The port shows it one fixed fast machine
(Calibrate about 2300) whatever the computer: see NOTES-port.md "Game
speed".

## Quirks

Original behaviour is the default. Crashes and memory-safety bugs are fixed;
bugs whose fix would change gameplay noticeably stay as in the original,
with the fix available as a setting. Each is listed in `QUIRKS.md` (to come).

## Drives and file names

The Navigation window and the waves are made from the user's own folders
and programs: every directory of the game's drive is a place to fly to,
and every program in it an icon to capture. `src/win/dosfs.c` maps the
game's DOS paths onto host folders:

- **Drives.** On Windows the drives are the real ones (C: is C:\, D: is
  D:\ ...). On Linux C: is the user's home folder and there are no
  other drives. Android will use the folders the user grants (not done
  yet; `platform_folder_roots`). INSPACE.INI `[Port] DriveC=` (any
  letter) points a drive at any folder. The game asks for the drive in
  its New Game dialog, which lists the drives that exist.
- **Mounts.** `C:\SPACE` (the game's own folder, a race track in the
  game) is always the data folder and `C:\WINDOWS` the settings folder,
  whatever C: is. They are listed in C:\ and hide a host folder of the
  same name.
- **8.3 names.** The game was written for DOS names (8 characters, a
  dot, 3 characters, upper case); its paths, buffers and saved games
  assume them. It sees each host name as Windows 95 showed it to 16-bit
  programs: a valid 8.3 name is upper-cased (`readme.txt` is
  `README.TXT`); any other gets an alias of its first six allowed
  characters (spaces and extra dots dropped; `+,;=[]` and non-ASCII
  characters as `_`), `~1`, `~2`, ..., and the first three characters of
  its last extension (`Program Files` is `PROGRA~1`, `notes.backup.html`
  is `NOTESB~1.HTM`). Windows numbers aliases in the order the files were
  made; the port numbers them in the order of the host names (byte
  order), so they stay the same between runs. The game shows names in
  lower case (its own choice, as File Manager did).
- **Case.** Names are matched ignoring case, by alias or by host name;
  names that do not exist yet (new files) are kept as given.
- **Hidden files** (Windows: hidden or system attribute; elsewhere names
  starting with a dot) are left out, as DOS left them out unless asked.
- **Programs.** As in the original, the programs of a directory are its
  `*.EXE` files (and `*.DLL` files count as icons too); the extension
  decides, so Linux programs (ELF, no extension) are not icons. Icons
  are read from Windows programs (16-bit NE and 32/64-bit PE,
  `src/win/icon.c`); for a program without one the game draws its own
  default.

Source and include file names in `port/` are lowercase, and `#include`s
match them exactly.
