# Roadmap: modern additions

Planned after the whole game runs as in 1994. Everything here is an
addition with its own setting; the 1994 game stays the default unless a
point says otherwise.

## Files
- The port keeps everything in the game folder, as 1994 did: saves,
  settings, race times. Nothing goes to the Windows user folder or
  AppData. On Android the game folder is the app's own storage (done).
- Check the user's game files at start: recognise the release (Plus
  Edition v1.29 and others) and say clearly what is missing or wrong.

## Settings screen
- One screen in the game for all port options, styled like the game's own
  dialogs.
- Usable with keyboard, mouse, gamepad and touch. The rest of the port's
  interface follows the same rule.

## Controls
- Remapping for keyboard and gamepad, including each stick direction, in
  the settings screen.
- Touch controls (Android, touch screens).

## Display
- Fullscreen, integer scaling, smooth scaling, CRT and other filters,
  through SDL's GPU support so they work on Windows, Linux, Steam Deck
  and Android.
- Widescreen: remove the circuit-board frame around the play area, move
  panel elements to overlays, and use the freed space for a wider play
  area with little or no stretching.
- GPU effects such as bloom, lighting, particles and debris, each with its
  own switch, plus reduced-flash and reduced-motion options.

## Audio
- More channels than WaveMix's 8, optional stereo and reverb. The original
  mix stays available.

## Testing only
- Input recording and replay, for testing. Not a user feature; build it
  only if testing needs it.

## Not planned
- Right-stick aiming.
- Achievements (not for now).
- Online play, online leaderboards.
