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
  folders and files to explore, data location, sound output, MIDI music,
  game controllers): `platform_sdl.c` on SDL3 for every platform,
  `platform_pad.c` (gamepads and joysticks, SDL3), and the music backends
  behind `platform_music.c` (`music_tsf.c` on a SoundFont, `music_win.c`
  on Windows' MIDI output). Game code never calls the OS directly.

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
  - `tsf/` (TinySoundFont v0.9 `tsf.h`, MIT, and TinyMidiLoader v0.7
    `tml.h`, zlib; licences in `LICENSE` and at the top of each header;
    github.com/schellingb/TinySoundFont at commit a3621a1, 2026-11-17):
    the MIDI music on a SoundFont (`[Port] SoundFont=`).

## Fonts

The game draws all its text with TrueType fonts made by `CreateFont` at
many heights and widths. `src/win/text.c` maps Arial (and any other face)
to Liberation Sans and Times New Roman to Liberation Serif, picks bold for
weights above 550, and rasterises each size on first use, one bit per pixel
as Windows 3.1 drew it. The build copies the font files to `fonts/` next
to the executable, where the game loads them at start (a missing style
falls back to the family's regular one). Windows 3.1's bitmap faces that
the dialogs and captions name (Helv / MS Sans Serif, System) are drawn
from Liberation Sans too, with those fonts' VGA metrics (NOTES-port.md
"Text").

## Building

Needs CMake and SDL3.

    cmake -S port -B build -DCMAKE_PREFIX_PATH=<SDL3 install>
    cmake --build build

Run headless (tests): `SDL_VIDEO_DRIVER=offscreen build/inspace --frames 3 --dump out.ppm`.

Command line:

- `--frames N`: run N frames, then exit. These frames are the test
  clock of `--frames`, `--keys`, `--mouse`, `--pad` and `--shots`, about
  60 a second of real time while the game polls for messages; they are
  not the game's frames.
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
- `--frame-stats`: every 5 seconds, a log line on the pictures the game
  finished and showed: frames a second, the time between them (median,
  95th and 99th percentile, longest) and the processor time used, e.g.
  `frame-stats: 34.5 fps over 5.0 s (173 frames, 173 shown), frame time
  p50 29.00 p95 29.70 p99 29.95 max 30.02 ms, cpu 7%`. "shown" is less
  than "frames" when the game draws faster than the display refreshes.
- `--audio-dump FILE.wav`: also write everything played (the sound
  device's mix of effects and SoundFont music, 16-bit, at the device's
  rate) to FILE.wav. Without a sound device run with
  `SDL_AUDIO_DRIVER=dummy`, which plays in real time into nothing.
- `--mouse "FRAME:X,Y[,ACTION];..."`: move the mouse to framebuffer point
  (X, Y) at frame FRAME, then ACTION: `move` (the default), `down`, `up`,
  `click` (down, up two frames later), `dclick` (a double click's second
  press, then up), `rdown`, `rup`, `rclick`. Example:
  `--mouse "4000:300,200,rclick;4100:320,255,click"` opens the game's
  right-button menu in a wave and chooses Exit Game.
- `--pad "FRAME:WHAT[/HOLD],..."`: a virtual game controller (SDL's
  virtual joystick). WHAT is `attach` (a gamepad), `attachraw` (a
  joystick SDL has no gamepad mapping for), `detach`, a button held HOLD
  frames (2 by default: `A`, `B`, `X`, `Y`, `Back`, `Start`, `LeftStick`,
  `RightStick`, `LeftShoulder`, `RightShoulder`, `Up`, `Down`, `Left`,
  `Right`, `LeftTrigger`, `RightTrigger`), or `LX=V` / `LY=V`, the left
  stick (-32768 to 32767; with `/HOLD` back to the middle after HOLD
  frames). Example: `--pad "10:attach,1600:B,3600:LX=32767/100"`.

Game data (INSPACE.EXE and the other original files) is read from `data/`
or the folder in `INSPACE_DATA`; it is not part of the repository. The game
sees it as `C:\SPACE\`; `C:\WINDOWS\` (INSPACE.INI, WIN.INI) is the
same folder, so the port writes nothing to the user's settings folders
(AppData, ~/.local/share). The rest of the game's drives are the
user's folders: see "Drives and file names".

Windows: `cmake -S port -B build-win -DCMAKE_TOOLCHAIN_FILE=<mingw.cmake>
-DCMAKE_PREFIX_PATH=<SDL3 Windows install>`.

## Settings

On the first start, with no INSPACE.INI in the game folder, the port
writes the one the 1994 installer left (all parts in `C:\SPACE\`, Normal
difficulty and speed, full screen, the player "your name") with commented
`[Port]` examples, so the game starts as an installed copy without its
"Some game settings are missing" box. An existing INSPACE.INI is never
rewritten; delete it to start afresh.

Port options live in INSPACE.INI (the game folder) under `[Port]`;
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
- `Pad<button>=<keys>`: the keys a gamepad button sends (see "Gamepad").
- `SoundFont=<file>`: a SoundFont (.sf2, General MIDI, e.g. FluidR3_GM or
  GeneralUser GS; none comes with the port), an absolute path in the
  host's form. The music (the game's MAIN.MID, RACE.MID, ANTHEM.MID and
  DEMON.MID) is then played on it, on every platform. Without it Windows
  plays the music on its own MIDI synthesizer and Linux plays none
  (NOTES-port.md "Music").

## Help

The game's help (the Help menu, the Navigation window's Help button,
Game Settings' and Joystick's Help) is a Windows 3.1 help file,
ENG_HELP.HLP in the data folder. The port has no help viewer yet: each
request is logged with its topic and the game goes on, as it did when
WinHelp could not find the file (NOTES-port.md "Help").

## Gamepad

A gamepad (Xbox, PlayStation, Switch, the Steam Deck's controls, anything
SDL3 knows the layout of) or any other joystick can be plugged in and out
while the game runs; the whole game can be played with it, no keyboard
needed. It does two things:

- **The 1994 joystick.** The left stick and the face buttons are the
  joystick the game read on the PC's game port: buttons A and B are its
  buttons 1 and 2, X and Y buttons 3 and 4 when "4 Buttons" is ticked.
  As in 1994 it is turned on and calibrated in Game Settings, Joystick..
  (tick Joystick Enabled, Calibrate, push the stick up and left and press
  A, down and right and press A; then OK). In a wave the ship turns
  towards where the stick points and thrusts once it faces that way;
  each button does what the dialog sets (Fire Gun, Fire Weapon, Change
  Weapon, Turbo Thrust, Call Ambulance, New Ship Target, Cloak/Shield).
  Unplugged during a wave the joystick is off until the settings are read
  again, as a pulled cable was in 1994.
- **Keys.** Every button sends keys the game already uses, so menus,
  lists, dialogs and the intro work too. While the game reads the
  joystick, the buttons that are the joystick's (A, B; X, Y with four
  buttons) send no keys.

| Button | Keys | In a wave | Elsewhere |
|---|---|---|---|
| D-pad | arrows | thrust, brake, turn | move in lists, menus, dialogs |
| A (bottom) | Return | fire weapon | OK, choose |
| B (right) | Escape | leave the wave | cancel, intro: the New/Restore dialog |
| X (left) | Space | fire gun | press the button that has the focus, tick a box |
| Y (top) | Tab | change weapon | next control |
| Start | P | pause | |
| Back / View | Escape | leave the wave | cancel |
| Left stick button | Return | fire weapon | OK (also while A is the joystick's) |
| Right stick button | Alt+G | Game Settings | Game Settings |
| Left shoulder | H | call the ambulance | |
| Right shoulder | R | new ship target | |
| Left trigger | Ctrl | turbo thrust | |
| Right trigger | Caps Lock | cloak or shield | |

A, B, X and Y are named by place (on a Switch controller A is the right
button, on a PlayStation one Cross is A). Any button's keys can be set in
INSPACE.INI `[Port]`: `PadA=`, `PadB=`, `PadX=`, `PadY=`, `PadBack=`,
`PadStart=`, `PadLeftStick=`, `PadRightStick=`, `PadLeftShoulder=`,
`PadRightShoulder=`, `PadUp=`, `PadDown=`, `PadLeft=`, `PadRight=`,
`PadLeftTrigger=`, `PadRightTrigger=`, each an SDL key name with
modifiers before it as in `--keys` (`PadStart=Alt+G`), or `None`. The game
has a large dead zone of its own (the stick's middle three fifths do
nothing), so the port adds none.

## Game speed

The game paces itself by real time (FrameRateSet, 36 frames a second by
default, changed with Alt + and Alt - in a wave) but measures the
machine at start-up (INSPACE.INI `Calibrate`) and picks some animation
steps from it. The port shows it one fixed fast machine (Calibrate about
2300) whatever the computer, keeps its clock to the millisecond, sleeps
between frames and shows each frame as soon as the game has drawn it, no
vsync. The game's own arithmetic makes 36 into 34.5 frames a second at
the start of a wave and 35.7 after about 45 seconds, as on a fast 1994
machine. See NOTES-port.md "Game speed" (and `--frame-stats`).

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
  game) and `C:\WINDOWS` are always the data folder,
  whatever C: is. They are listed in C:\ and hide a host folder of the
  same name. As the original did in its folder, the game writes into
  the data folder: saved games (`GAMES\*.SAV`, `LASTGAME.SAV` after each
  wave), retired pilots (`RETIRED\*.DED`, `*.DON`) and race times
  (`GAMES\*.RAC`). Saved games are in the 1994 format: the original's files
  load in the port and the port's in the original.
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
