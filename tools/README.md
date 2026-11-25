# Tools

Python 3. Run from the repo root; game files live in `data/` (git-ignored).

| Tool | What it does |
|---|---|
| `ne_info.py FILE` | NE header and segment table. |
| `optl_lz.py` | OPTLOADER LZ decoder (library), translated from the loader's routine at segment 1:0x31. |
| `optl_emu.py` | Runs that original routine under Unicorn (`pip install unicorn`); the reference `optl_lz.py` is checked against. |
| `optl_unpack.py IN OUT` | Rebuilds a packed NE file as a plain NE: unpacked segments, OPTLOADER relocation tails turned into NE relocation records, self-loading flag cleared. Original bytes are kept; new segments are appended. |
| `ne_relocs.py FILE [--list]` | Lists NE relocations and checks every chain. |
| `omf_match.py NE LIB... [--list]` | Finds OMF library modules (C runtime) in an NE file's code, fixup bytes masked. |
| `fat12_extract.py IMG DIR` | Extracts a FAT12 floppy image (install disks). |
| `msexpand.c` | Expands Microsoft COMPRESS files (KWAJ or SZDD) with libmspack: `cc -std=c99 -Wall -Wextra -pedantic -O2 -o msexpand tools/msexpand.c -lmspack` (`apt-get install libmspack-dev`). |
| `dll_oracle/` | Test oracle: ISPACE.DLL ordinals run on the original DLL (Unicorn) and on the port, compared; see below. |
| `szdd_expand.py SRC DST` | Pure-Python SZDD expander (SZDD only; the C7 disks are KWAJ, use `msexpand`). |

Unpack everything into the git-ignored `unpacked/`:

```
mkdir -p unpacked
for f in INSPACE.EXE ISPACE.DLL FACTORY.EXE BACKUP.EXE; do python3 tools/optl_unpack.py data/$f unpacked/$f; done
```

## OPTLOADER format (SLR Systems, 1993)

Segment 1 is the self-loader. It is identical in every packed file: 0x1e7
plain bytes (self-loading header + LZ decoder), then its own body as an LZ
stream that decodes in place after those bytes (matches can reach back into
them). Every other segment's file data is

```
WORD  nrelocs        total relocation entries in the tail (0 = no tail)
...   LZ stream      decodes to the segment, up to its alloc size; the loader zero-fills the rest
...   reloc tail     groups: WORD (kind | count << 8), then entries
```

LZ stream: 16-bit LE words read MSB first, refilled right after the 16th bit
is used; raw bytes come from the same input pointer.

```
1                      literal byte
0 0x                   length 2|x, distance = byte + 1 (<= 256)
0 10x / 0 110x         length 4|x / 6|x
0 1110xx / 0 11110xxx  length 8+xx / 12+xxx
0 11111 + byte         byte < 0x81: length; 0x81: no-op; > 0x81: end
then (except length 2) distance high byte:
  00 -> 0, 010 -> 1, 011x -> 2+x, 100xx -> 4+xx, 101xxx -> 8+xxx,
  1100xxxx -> 0x10+, 11010xxxx -> 0x20+, 110110xxxx -> 0x30+, 110111xxxxxx -> 0x40+
then the distance low byte; distance = (high << 8 | low) + 1
```

Relocation kinds: `0xF0` = selector chains (BYTE seg, WORD head). Otherwise
bits 0-2 = patch (0 byte, 1 selector, 2 far pointer, 3 offset; +4 additive,
else chained as in NE), bits 3-4 = target (0 internal: BYTE seg, 0xFF =
movable entry ordinal; 1 import ordinal and 2 import name: WORD module;
3 OS fixup: WORD type), then entries (WORD offset, WORD value; OS fixups
WORD offset only).

Verified: `optl_lz.py` matches the original routine byte for byte on all 21
streams of FACTORY.EXE, BACKUP.EXE and ISPACE.DLL; every tail parses
exactly; every chain ends in 0xFFFF inside its segment; all but one far
pointer fixup per file sit right after a `call far` (9A) opcode.

## Matching

`tools/match.py SRC.C...` compiles with CL 8.00c in DOSBox (`MSVC_DIR`, default
`/home/user/toolchain/msvc`; flags `CFLAGS`, default `/AM /G3 /Gw /Gs /Os`) and
compares every function tagged `/* @addr SEG:OFF */` with the game. Needs
`dosbox` and the MSVC 1.5x `BIN`, `LIB`, `INCLUDE` (not in git).

## DLL oracle (`dll_oracle/`)

A test tool, never part of the port: runs ISPACE.DLL's own code (unpacked
in memory from the user's `data/ISPACE.DLL`) under Unicorn with Python
stand-ins for the Windows calls it makes, runs the same calls on the
port's native versions, and compares the results, returned bitmaps pixel
for pixel and palettes entry for entry. Needs `pip install unicorn` (2.1)
and SDL3 for the port side.

```
cmake -S tools/dll_oracle -B build/dll_oracle -DCMAKE_PREFIX_PATH=<SDL3 install>
cmake --build build/dll_oracle
python3 -I tools/dll_oracle/oracle.py tools/dll_oracle/smooth.txt
```

The build takes every file of `port/src/win/` and `port/src/game/`: run
the first command again after files are added there.

- `emu.py`: the emulated DLL (`IspaceEmu`: loading, relocations, import
  stand-ins, `call_ordinal`). The stand-ins model memory (GlobalSize in
  Windows' 32-byte units), resources of ISPACE.DLL, IGRAPHIC.DLL and
  ENG_LANG.DLL, palettes and 8-bit bitmaps with their pixels, and GDI
  drawing as the port does it (port/src/win/draw.c: any ROP3, brushes
  and stock objects, pattern brushes, lines, polygons, pixels); a call
  without one stops the run with its name. Colour matching (`CreateDIBitmap` with RGB
  colours, `LoadBitmap`, RGB brushes and pens) follows the port's rule,
  so it is not checked. `TextOut` is recorded, not drawn. The machine
  (`GetWinFlags`, the wave device, INI files) answers as the port's;
  INSPACE.INI is `INI` (emu.py), the sound DLLs are the user's
  `SOUNDS\SND_FX.DLL` and `ENG_FX.DLL`, and sounds are not played (the
  wave and MIDI volumes are kept; MCI commands are recorded).
  `C:\WINDOWS\WAVEMIX.DLL` exists, as the port's WaveMix always does:
  GetProcAddress gives stand-ins that succeed and play nothing. Files of
  the data folder can be read (OpenFile, `_lread`, `_llseek`,
  `_lclose`, DOS3Call's seek and read); there is no WIN.INI (the
  defaults) and no DOS memory (GlobalDosAlloc fails: the disk serial
  number reads 0, as the port's). RegisterClass fails for a class
  registered already, as in Windows. GetDIBits gives an 8-bit bitmap's
  palette indices. The
  game port (`in`/`out` on 0x201) holds the joystick pseudo-ordinal 1004
  sets, as the port's pad.c gives it: each axis bit stays set for its
  count + 1 reads after an `out` (count = the stick's -32768..32767
  plus 32768, shifted right by 6), held buttons read 0, buttons 3 and 4
  only with the DLL's 4Btns; nothing plugged in reads 0xff (the DLL's
  loop times out). Dialogs
  are modelled from the language DLL's templates (controls with their
  text, enabled state, check, combo items and selection, scroll range
  and position; `_wsprintf` of `%d %u %x %s`); DialogBox and WinHelp are
  recorded, not run, as is PostMessage.
- `port_calls.c`: runs a script on the port's `ispace_*` routines and
  prints the results (built from the port's sources without `main.c`).
- `oracle.py SCRIPT`: runs both and lists each call as same or differs.
  A script line is `ORDINAL ARG...`; an argument is a number, `"text"`,
  `@K` (the result of call K, from 0), `DC` (a screen DC), `MDC` (a
  memory DC with a 640x480 bitmap, which is compared after the call) or
  `DC@K` (a memory DC with call K's bitmap selected, which is compared
  after the call as well: a sprite sheet a call changes), or `X,Y` (a
  point, ordinals 8 and 9). Ordinal 29's word pointers are given as their values; the words are
  compared after the call. Results of routines that return nothing
  (`VOID`, ordinal 14) are not compared. A call that stops the emulation
  (a Windows call without a stand-in) is reported with its number.
  Ordinals 1-12, 14, 15, 17, 18, 26, 28, 29, 32-35, 37, 38, 40 and 41 are supported, and pseudo-ordinal
  1000 for 5:0000 (the dialogs' ship picture, a C-convention routine the
  DLL does not export: `INTERNAL` in oracle.py). The dialog procedures
  (11, 26, 28, 37, 38, 40: hwnd, msg, wParam, lParam) take `DLGn` (a
  dialog of the language DLL's template n; `DLG` the last one),
  `N<id>:<code>` (MAKELONG(control id's handle, code): a control's
  WM_COMMAND notification) and `C<id>:<pos>`
  (MAKELONG(pos, control id's handle), for WM_HSCROLL); pseudo-ordinals
  1001 (id, 0/1), 1002 (id, item) and 1003 (id, "text") are the user
  checking a box, picking an item and typing a control's text; after
  these the controls (with a push button's pressed state), the focus,
  the dialog's end (EndDialog's value) and INSPACE.INI are compared.
  Ordinal 41 reads into an 8-byte block (x, y, four button bytes)
  compared after the call; pseudo-ordinal 1004 (x, y, buttons, present)
  is the joystick: the emulator's game port, the port's a virtual SDL
  gamepad (left stick; buttons A, B, X, Y as bits 0-3); 1005 and 1006
  are the Joystick dialog's procedure (9:40da, `DLG975`) and its timer
  (9:4d02), Pascal routines the DLL does not export (`PASCAL`). Add others to
  `ORDINALS` (oracle.py) and `run` (port_calls.c). Ordinal 32's script
  arguments leave out the rectangles block (both sides make an 8-byte
  one); its rectangles are compared too.
- `ships.py OUT`: writes a script from the user's `SHIPS/MASTER.SHP` and
  `MASTER.BOD` (so it is not kept in git): smooth.txt's palette set-up,
  then 5:0000 for every ship as the New Game dialog shows it, every tenth
  also in modes 1 and 2. All 142 calls agree.
- `smooth.txt`: the palette set-up up to the title and ordinal 12 on 21
  images of IGRAPHIC.DLL. All agree.
- `rooms.txt`: the palette set-up up to the desk (captured from a run)
  and ordinal 32: the desk as the game draws it, room 120, and room 100
  with other sizes and vanishing points. All agree. Rooms 105 (image 76
  not loaded by ordinal 1), 110 and 115 (object type 5 not ported) still
  differ.
- `wave.txt`: the palette set-up of a run up to a wave (captured), the
  launch scene's ordinal 14 calls and more percentages, ordinal 18 as the
  game calls it (kinds 1 and 0) and six variations, and ordinal 29: the
  16 calls of a flight in a wave and 400 random ones. All agree.
- `surfaces.txt`: wave.txt's set-up with ordinal 2's surfaces where the
  game makes them in a wave (images 180, 60, 370), 21 variations (one
  and 16 angles, j 0 and 1, frames, colour sets, borders, 18:08bc's
  calls) and ordinal 12 after them. All agree. j 2 is left out: the DLL
  reads past its planes there (port/NOTES-port.md).
- `damage.txt`: surfaces.txt's set-up up to the wave's surfaces, then
  ordinal 15 on fresh surfaces (`DC@K`): both sides, modes 1 and 0,
  every direction, three sizes, odd offsets, no palette, and the two
  calls of waves (captured) one after the other on one sheet. All 194
  calls agree. The
  stand-in for `Polygon` fills as the port's draw.c does (the masks of
  DS:0184 are polygons).
- `sound.txt`: ordinal 7's set-up (mode 0) and modes 2, 3, 4, 10,
  ordinal 8 at points in and beyond the view and ordinal 9 with sounds
  and commands, on and off screen, at times inside and after the quiet
  times; the wave device's volume is compared after each call. Both
  sides read the emulator's INSPACE.INI (`INI` in emu.py: MixChannels 1,
  sounds through sndPlaySound; the port side gets a settings
  folder of its own and SDL's dummy sound device). All 200 agree.
- `options.txt`: the sound set-up, then the Game Settings dialogs
  (ordinal 10 mode 0): ordinals 11 (template 100), 37 (Display Options)
  and 38 (Audio Options) opened, every scroll code on each bar, boxes
  checked and items picked, OK and Cancel, the detail options grayed
  (ordinal 10's sixth word), channel counts changed, a negative width in
  sound mode 0. All 132 calls agree.
- `savegame.txt`: the Save Game dialog (ordinal 10 mode 3, template
  167, ordinal 26 = 10:0dc0): opened (the combo box it adds, the saved
  games of GAMES\*.SAV but LASTGAME, the one INI Restore begins picked),
  Save with no name, LASTGAME, "my game" and a listed game, Cancel. Run
  it with `--data` on a copy of the game's files whose GAMES folder holds
  saved games (the emulator lists them through DOS3Call's find
  functions; LocalPath is C:\SPACE\ on both sides). All 14 calls agree.
- `joystick.txt`: the sound set-up (9:22ca reads the joystick's INI
  settings), ordinal 41 with a bad n and with nothing plugged in, the
  Joystick dialog (template 975) opened without and with a joystick,
  turned on, 4 Buttons, Calibrate: the corners taken by a button (the
  lower right one refused while short of where the stick went first),
  buttons shown pressed, actions picked, OK; then ordinal 41 calibrated
  across the stick's range with buttons, and the dialog again: 4
  Buttons off and Cancel (buttons 3 and 4 gone), unplugged while it
  runs, turned on again without calibrating. All 69 calls agree. (A
  range of 0 is left out: the DLL divides by it.)
- `panel.txt`: the same set-up, then ordinals 33-35 on a memory DC. All
  agree. (Image 200, taller than wide, differs
  in 37 pixels of its top rows: the DLL reads past its pixels there, see
  port/NOTES-port.md.)
- `soften.txt`: ordinal 1's 5:075e (b 1 and 2: INI Enhance's softened
  pictures): wave.txt's set-up, then image 170 as the wave loads it,
  other colour sets and images, image 0x28a. All 51 calls agree.
- `quick.txt`: the quick drawing 6:5538: surfaces.txt's set-up, ordinal
  2 with n set (6:78ba, INI Quick) on the wave's images and variations,
  then ordinal 17 into ships' sheets (`DC@K`) as the cloak draws it.
  Ordinal 17's result (a handle it may have deleted) is not compared.
  All 94 calls agree.
- `newbody.txt`: the New Ship Body dialog (ordinal 10 mode 6, template
  286, ordinal 28) with the DLL's starting words (not played by a person,
  the limited version); the port side runs with `[Port] CopyCheck=1`
  (oracle.py writes it for every script) so both check the copy the same
  way. All 16 calls agree.
- `benefits.txt`: the Registration Benefits / Plus Pack dialog (modes 12
  and 14, templates 799 and 1872, ordinal 40). All 5 calls agree (only
  the text of mode 0: the mode is set by 10:42c6, which runs DialogBox).
