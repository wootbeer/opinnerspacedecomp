# Coverage: what still does not run as in 1994

A survey of the port's remaining gaps (native Windows layer, native
ISPACE.DLL, the game code's calls into them) and of what scripted runs
reach. "Reachable" means in normal registered play with the user's data
(INSPACE.INI `[Port] CopyCheck` off); evidence is the calling code or a
run. Sizes are rough estimates of new code.

## Remaining gaps, in the order a player meets them

| Item | Reachable? | What the player sees | Status | Size |
|---|---|---|---|---|
| First start without INSPACE.INI (6:06d8, "Some game settings are missing") | yes, first launch | a message box, then the game writes its settings | as 1994 (its installer wrote the INI, so players rarely saw it) | decision: a port-side default INI, ~40 lines |
| Help: WinHelp viewer (Help menu, F1/F2, Navigation's Help, Game Settings' and Display Options' Help; 2:190a, 9:328e) | yes | nothing (logged) | not ported | medium-large: ~700 lines (HLP B+ tree, \|SYSTEM, \|CTXOMAP, \|TOPIC text, a window with links and Back) |
| Resizing windows (sizing border, system menu Size) | yes, windowed | the frame keeps its size | stub (logged) | small: the move loop (user.c) with an edge per hit-test code |
| Message box icon (MB_ICONEXCLAMATION and the others) | yes | the port's own 32x32 stand-in, not USER.EXE's picture (the user's data has none) | approximation | none: needs Windows 3.1's USER.EXE |
| Restore of saves written in the early port layout (t17's GAMES\*.SAV, 1212 bytes) | only with such files | Restore re-opens with the same game selected | as 1994 for a short file (6:930a fails quietly) | none |
| Ordinal 10 modes 8, 11 and 10:02f4 (ordering dialogs 10:0664, 10:124a: 'R' at the title, Benefits' Order.., Escape at an expired trial) | no: unregistered only (`CopyCheck=1`) | nothing (logged "not ported") | not ported | medium: ~400 lines with the oracle |
| Ordinal 10 mode 2 (10:3346), mode 9 (10:5b24, only from mode 10) | no: no caller | - | not ported | medium |
| `utime` (10:81b6, file times of the copy check) | no: unregistered only | - | stub, returns 0 | small |
| Ordinal 1 images from files (5:1d74) | no: only Ship Factory bodies with an image file; MASTER.BOD's one (IDRAGON) has no ship and no file | an invisible ship | not ported | medium: ~200 lines |
| Ordinal 1 "own colours" (colour set 12 kept, 5:26a2) | not seen in any run | - | not ported (logs) | small-medium |
| Ordinals 2, 12, 17 for images with VGA colours (6:0200, 7:13b8, 6:563b) | no: none of their images has VGA colours | - | not ported (logs) | small: the ordinal 1 path exists |
| Fixed-palette paths (ordinals 2, 14, 17, 18, 5:075e) | no: mode 0's fixed word is never set | - | not ported (logs) | medium |
| 4-bit and 1-bit display paths | no: the port is 256 colours | - | not ported | - |
| Ordinal 4 mode 8, ordinal 24's other modes, ordinal 32 room -1, ordinal 7 modes 5-8 | no: no caller (7: modules load on use) | - | stubs | - |
| Window scroll bars (WS_VSCROLL, SB_VERT), radio buttons, edit undo/clipboard, multi-line editing | no caller in the game | - | not ported | - |
| Music on Linux without `[Port] SoundFont=` | yes | silence | documented | - |

## Fixed in this pass

| Item | Was | Now |
|---|---|---|
| MessageBox (user.c) | logged; yes/no boxes answered No | msgbox.c: a modal Windows 3.1 box. F12's Command Mode question can be answered Yes; shop, save and copy-limit notes, resource alerts and the first-start note are shown |
| Command Mode question text (10:a96c) | 260 characters joined in a 200-byte buffer: garbled natively | buffer 400 bytes (`fix`), as the 1994 frame had room |
| Multiple-selection list boxes (listbox.c) | LB_GETSELCOUNT/LB_GETSELITEMS unanswered | LBS_EXTENDEDSEL and LBS_MULTIPLESEL: the Ambulance Options and Ship Options dialogs can buy and sell (Add >>, Remove were always grey), which also opens the way to New Ship Body |
| g_6078 (debriefing text pointer) | 8-byte view over g_607c: after a wave left through the gate the debriefing never drew (black screen) | native variable (`extern`) |
| g_1d38 (last key's lParam) | 8-byte view over g_1d3c (screen saver and demo timers) | 32-bit view (`extern`) |
| `struct _find_t`, `stat`, `utimbuf` in DGROUP | native sizes overran g_3974[0] (12-character file names) and g_9288-9299 | 1994 layout (pack 2, 32-bit times) |

## Runtime coverage

Scripted headless runs (AddressSanitizer build with
`-finstrument-functions`, each on a copy of the data) reached: the
intro and credits, the title, Restore Game (a port save restored), New
Game, the desk (room 100), Inner Space Navigation, the mission
briefing, a normal wave (C:\TOOLS), a race (Lazy Loop, laps finished
with secret code 1), the duel arena (Dodge City), the Demon's Gate wave
and its debriefing, the court (room 110, secret codes Delete, F6), the
ambulance and room 105 with Ambulance Options (buying) and Ship Options
(selling), the mission debriefing and the next wave, self-destruct
(Ctrl+Alt+X) to Game Over and Champions of Inner Space, the exit
question, Save Game, Game Settings (Alt+G), pause, the right-button
menu, Command Mode (F12), frame-rate keys, a gamepad as the joystick,
INI Quick/Enhance/BadVideo variants, the limited (unregistered)
version, the demo, and the Inner Demon sub-game on the ambulance
room's monitor (seg18). Functions entered over all runs: 661 of 859 in
the game code, 877 of 1003 in port/src/win. Not reached by script: the
end of the game (16:7210 and 16:7396, after the Inner Demon is beaten:
"AFTER EXPLORING ... AND DEFEATING YOUR INNER DEMON"), New Ship Body
through the game (a BODY item at the ambulance; the dialog itself is
checked with the oracle, newbody.txt), the Plus Pack dialog on exit
(benefits.txt). By reading, these call only ported routines.
No AddressSanitizer findings in any run.

The pass was stopped before its own final checks; the coordinating
session rebuilt, ran every oracle script and a scripted wave, and gave
the oracle's port side its own MessageBox (answers at once, as emu.py
does) so modal boxes don't wait for a click.
