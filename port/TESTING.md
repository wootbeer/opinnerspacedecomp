# Things to test

Checks that need a person, real hardware or the original game. Items move to
"Done" once confirmed.

## Platforms and hardware
- [ ] Windows build: starts, plays a wave, saves and restores.
- [ ] Windows music: plays through the MIDI Mapper (midiOut).
- [ ] Linux music: plays with `[Port] SoundFont=` set to a .sf2 file.
- [ ] Real gamepad: steering feel after calibrating in the Joystick dialog
      (the stick-to-joystick scale is a guess), fire buttons, plugging in
      and out while playing.
- [ ] Gamepad button mapping: the defaults make sense in waves, menus and
      dialogs (table in README.md).
- [ ] Steam Deck: built-in controls work as a gamepad.

## Saves
- [ ] A save made by the port loads in the original 1994 game (same layout,
      untested because the original can't run here).
- [ ] Your own 1994 saves, if you have any, load in the port.
- [ ] Saving from the menu between waves (never reached in a test run).
- [ ] `data/GAMES/LASTGAME.SAV` was written by an early port run in a wrong
      layout; delete or replace it.
- [ ] The game writes saves and race times into its data folder, as in 1994;
      play from a copy if the originals matter.

## Look
- [ ] White patch at the edge of the ship preview (earlier fix).
- [ ] Save Game: a stray caret (short white line) near the top left.
- [ ] Combo boxes with a typing field (Save Game) look only roughly like
      Win3.1.
- [ ] Window titles and menus use the 16 px System font, slightly larger
      than before.
- [ ] Display Options reaches the right edge of the screen (placed from its
      template, believed to match 1994).
- [ ] Letters may differ by a pixel from real Windows Arial.

## Behaviour
- [ ] Esc on a popup menu during a wave: should it ever leave the wave?
- [ ] One wave ended without explanation in windowed mode.
- [ ] Rocks with mass 0 (possibly fixed with the record-size fix).
- [ ] Rooms: object type 5 not drawn; room lines drawn 1 px wide instead
      of 2.

## Decisions
- [ ] Optional: turn on and calibrate the joystick automatically when a
      modern pad is found (off by default).
- [ ] Scope the ideas from smashport (per-user save folder, file check at
      setup, settings menu, remapping, display filters, replays).

## Done
