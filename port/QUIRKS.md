# Where the port differs from 1994, and where it does not

One list of the port's behaviour against the 1994 game. Details are in
NOTES-port.md (section names in quotes); addresses are SEG:OFF of
INSPACE.EXE or ISPACE.DLL as there.

## Settings that change behaviour

INSPACE.INI in the game folder, section `[Port]`. Off unless set to 1.

| Key | Off (the port's default) | On: as in 1994 |
|---|---|---|
| `CopyCheck` | The copy counts as registered: the full title, all ships in New Game. | The copy check (ISPACE.DLL ordinal 24, mode 2) compares the key in INSPACE.EXE with the disk serial number or WIN.INI `PDev`. Copies made from the disks fail it: the title shows "limited inner space" and New Game offers only TRANSFORMER and fewer ships. ("ISPACE.DLL dialogs", Registration) |
| `HelpMissing` | Help in Game Settings, Display Options and Joystick opens its topic in the game's help file, C:\SPACE\ENG_HELP.HLP. | Those buttons look for INSPACE.HLP in the sounds folder, where no help file is, and show "Cannot find the file". ("Help") |

The other `[Port]` keys only connect the game to the machine and change
nothing in play: `Drive<letter>` (a host folder as a DOS drive),
`Pad<button>` (keys a gamepad button sends) and `SoundFont` (music on a
SoundFont instead of the system's MIDI synthesizer); see README.md
"Settings".

## 1994 quirks the port keeps

| Where | What happens (as in 1994) | NOTES-port.md |
|---|---|---|
| 10:0dc0 Save Game | Esc does nothing (Cancel is id 333); "lastgame" in lower case is accepted and saves over LASTGAME.SAV. | "ISPACE.DLL dialogs" |
| 10:0ec2, 10:0f26 Restore, New Game | Esc does nothing; Alt+C cancels. | "ISPACE.DLL dialogs" |
| Ship files (MASTER.SHP), New Game | A ship file's length is taken as its low word, sign-extended: files of 32 KB or more give no ships. | "ISPACE.DLL dialogs" |
| 9:2f30 Audio Options | Any scroll bar moves the effects/music bar; a bar moved back to the last position it showed is not redrawn; a new sound system opens the mixer only at the next wave; Display and Audio Options start without focus. | "Game Settings" |
| 9:40da Joystick | Corners and "4 Buttons" survive Cancel until the next wave; an uncalibrated joystick is saved on OK; Esc does nothing; Help asks for a file the game lacks (see `HelpMissing`); only JMinX and JRangeX decide "calibrated". | "Joystick" |
| 5:34c8 palette manager (ord 4) | Mode 6 answers -1 both when no entry is free and when a near colour exists; entries 10 and 245 are never given out; mode 1 with -1000 reaches the screen only at the next mode 3. | "ISPACE.DLL" |
| 10:2e1a, 5:0062 (ord 36) | A copy both doubled and mirrored is one column off. | "ISPACE.DLL" |
| 6:7fc8 VGA-colour images | The colour search compares counts with the index found so far [sic]. | "ISPACE.DLL" |
| 6:00c4, 7:12d8 smoothing (ord 12) | Columns run to the image's height; mode only lightens with 1; corner cut looks at the opposite diagonal; codes wrap as bytes; colour set 0xff returns 0. | "ISPACE.DLL" |
| 8:0000 rooms (ord 32) | Mode 4 reads the parent's first position mode [sic]; a mode 0 box is the parent's width on all axes; object 2 is lifted only for rectangle byte -20; words 12/13 are the vanishing point's y/x; unknown textures use an empty bitmap. | "ISPACE.DLL rooms" |
| 6:5e76 sprite sheets (ord 18) | Rows run to the image's width, columns to its height. | "ISPACE.DLL in the launch scene and the wave" |
| 6:011c surfaces (ord 2) | A frame on an odd column is drawn one block right and loses its last column; the corner cut uses the planes of index f; m 1 makes the bitmap a cell wider. | "ISPACE.DLL surfaces" |
| 6:5538, 6:78ba quick drawing | Rows counted from the top edge, not the border's [sic]; a frame on an odd pixel is read from its second pixel. | "Quick drawing" |
| 2:0d78 | Case 0x60 (Main Menus) returns no value [sic]; nothing more happens. | "Menus and scroll bars" |
| 2:0000 | F1 does nothing in the Navigation window (MainAccel only for the main window) [inferred]. | "Help" |
| 8:1e32, seg11, 4:2da2 | Long products that overflow (distances above 181, the `* 500` score terms) wrap as in 1994. | "Needs human judgement" 9 |
| seg02 calls of 10:7480 | Called with one argument; the music's wait flag is 0 (1994 read a stale stack word). | "Needs human judgement" 3 |

## Crashes and memory errors fixed silently

These changed nothing a player could rely on: 1994 faulted, read garbage,
or the fault only exists in the native layout (marked *native*). Game
code: `fix` entries in overrides/signatures.txt, "Silent fixes in the
game code"; ISPACE.DLL: the "Fixed silently" notes of each section.

| Where | Fix |
|---|---|
| 7:13b2, 7:158e | Dissolve maps overflowed into the next records at zoom 1x: each dissolve has its own map. |
| 7:5e04 | A sparkle's last frame read one past its table: the 1994 stack word, 0 where it was garbage. |
| 8:1e32 | Breaking a released tether wrote through `g_1df8[-1]` (a GP fault): skipped. A zero mass divided by zero: no force. |
| 6:4368, 6:420a, 6:4190, 6:4748 | An empty path read the byte before its buffer: a `\` is appended. |
| 10:a96c | The Command Mode question overflowed its 200-byte buffer: 400 bytes. |
| REC_70 blocks (6:1b62, 18:1dd0, 11 GlobalReAllocs) | *native*: sized in native 124-byte records, so the zeroed part is the 1994 one. |
| DS:1e4c, DS:6078, DS:1d38, DOS structs | *native*: pointers and runtime structs that were wider than their 1994 slots. |
| 17:3ba6, 17:4354, 17:4068-17:76e4 | *native*: string ids the decomp wrote as literals are the 1994 numbers. |
| 10:2d3c, 10:250c | Width 0 and fixed message buffers bounded; an empty drive list writes no Drive. |
| 9:1fae, 9:1f38, 9:03d8 | Uninitialised previous sound system and version buffers; sounds left pointing into a freed DLL. |
| ord 7-9 sound | MixChannels above 8, ids out of range, an empty SndPath, long voice paths, unfreed voice waves. |
| 9:3e8a joystick | A range of 0 (never calibrated) divided by zero: the axis reads as the middle. |
| ord 1, 5:075e | Pictures of 32768 pixels or more had no buffer (GP fault): softened. |
| ord 2, 12, 15, 17, 18, 29, 32, 36 | Divisions by zero give 0; reads and writes outside images, sheets, tables and rooms are dropped or read as background. |
