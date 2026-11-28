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

- [ ] Frame pacing: run with `--frame-stats` in a wave on Windows and the
      Deck. Expect frame time p50 29.00 ms (28.00 after about 45 s), p99
      within about 1 ms, and note the CPU %.
- [ ] High rates (Alt+ up to 104) on the Deck under gamescope: if
      `--frame-stats` shows the rate capped at the display refresh, the
      present is blocking.
- [ ] Windowed, maximised and fullscreen: no tearing; the window repaints
      after resizing or uncovering it while a dialog or pause is up.
- [ ] No audio gaps over long waves.

- [ ] First start with no INSPACE.INI on Windows and Linux: no "settings
      missing" box, and INSPACE.INI appears in the game folder (nothing in
      AppData or ~/.local/share). An INSPACE.INI from an earlier port run
      sits in the old settings folder; move it into the game folder to keep
      it.
- [ ] Difficulty: a fresh start uses the installer's Normal (Complex=2);
      an INI the game wrote itself has no Complex key and plays Gentle.

- [ ] Android (debug APK built, never run): the first-start screen names
      the game folder and "Import game folder..." copies a chosen folder in
      (try an SD card or USB stick; on Android 11+ check that folder is
      reachable over USB/adb). Taps land on the right buttons with black
      bars; Back acts as Esc in dialogs; music plays, loops, pauses in the
      background and resumes; fonts load; startup time; a gamepad.

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
- [ ] Every wave now shows image 170 softened (Enhance=1, the default).
- [ ] Plus Pack text: a tab after "Death Heads" shows as a small box (edit
      fields don't expand tabs yet).
- [ ] Letters may differ by a pixel from real Windows Arial.

## Behaviour
- [ ] Message boxes are now real Windows 3.1-style boxes (before, they were
      only logged and yes/no answered No). They have no icon yet. Check the
      shop, save and first-start notes and F12's Command Mode question.
- [ ] Ambulance Options and Ship Options: buying and selling work now (Add
      and Remove were always grey).
- [ ] After leaving a wave through the gate, the debriefing draws (it was a
      black screen).
- [ ] Windowed mode (`Full=0`): drag a window by its title bar (an outline
      follows, as in Win3.1); Alt+Space then M and the arrow keys; Minimize
      from the system menu and restore from the taskbar (the game pauses and
      resumes); minimise with the desktop's own title-bar button; Maximize
      then Restore. Resizing a window is not done yet.
- [ ] Message box icons are the port's own simple drawings (Windows' own
      icons aren't in the game files).
- [ ] Put an ORDER.TXT in the data folder and press Order in the Plus Pack
      dialog: it should open in your text viewer (Linux and Windows).
- [ ] Waves look smoother. At 36 a wave starts at 34.5 fps and settles at
      35.7 after about 45 s; that is the 1994 game's own timing.
- [ ] Title logo, briefing, landing and the exit-question delay now draw as
      they happen instead of all at once afterwards.
- [ ] One wave ended without explanation in windowed mode (not reproduced
      in a 20,000-frame run). If it happens again, note what was clicked
      just before: a right-click opens the game's menu at the pointer, and
      the next left click can land on "Exit Game".
- [ ] Rocks shot apart: the three pieces should move normally (the mass-0
      pieces came from the record-size bug, now fixed; not re-observed).
- [ ] After pressing OK in Game Settings once (it writes `Quick=1`), ships
      and objects that appear mid-wave are drawn by the quick ship drawing;
      before, they were invisible. Check over a long wave.
- [ ] Cloak/shield (Caps Lock) shows the ship's cloak frames.
- [ ] New Ship Body dialog after the ambulance picks you up (never reached
      in a real test run).
- [ ] Help: the Help menu and Navigation's Help button open ENG_HELP.HLP
      in the port's viewer. F1 does nothing while the Navigation window is
      active: the game only checks its keyboard shortcuts when its main
      window is active (as in 1994, inferred). Small fonts readable?
      Clicking the game while help is open doesn't bring the game forward
      (Esc closes help).
- [ ] Game Settings / Display Options / Joystick Help open their topics in
      ENG_HELP.HLP (1994 looked under SOUNDS\ and showed "Cannot find the
      file"; `[Port] HelpMissing=1` brings that back).
- [ ] Room 105 shows the textured tower fronts and 2 px circuit lines;
      rooms 110 and 115 show the discs (pentagram platform, pedestal).
- [ ] Lines the game draws with wide pens elsewhere are now 2-3 px thick
      (they were all 1 px); check they look right.

## Decisions
- [ ] Optional: turn on and calibrate the joystick automatically when a
      modern pad is found (off by default).
- [ ] Scope the ideas from smashport (per-user save folder, file check at
      setup, settings menu, remapping, display filters, replays).

## Done
- Esc on the right-button menu in a wave no longer asks to leave the wave
  (the menu takes the key-up).
