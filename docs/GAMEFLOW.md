# How the game flows

From Matt's notes (player's point of view). The order of the final Inner
Demon fight and the evil-twin fight may be reversed.

1. Intro: company logo(s).
2. Title / splash screen.
3. Menu: new game or load a saved one.
4. Desk scene: a computer on a desk; tells you about the current time etc.
5. Your ship flies "into" the computer.
6. Directory picker: you choose a directory.
7. Briefing screen: tells you about the wave.
8. The wave. During it you can enter the ambulance; inside the ambulance
   you can play a test round against the Inner Demon.
9. Debriefing after the wave, then back to the directory picker (6).
10. The real Inner Demon appears at random in waves. Beating it earns a
    Noble Weapon.
11. With all four Noble Weapons you can enter the Demon's Gate wave and
    fight the Inner Demon a final time.
12. Then you fight a copy of yourself to beat the game. Credits.

## Links to the code (confirmed so far)

- Intro logo: 15:5914 loads the "SD_LOGO" bitmap.
- Title screen: 15:6cdc, state machine on DS:95cc (text, version and
  CD/demo lines, logo dissolve, scrolling title, fireworks).
- Desk scene: drawn by ISPACE.DLL ordinal 32 (HANDOFF).
- Briefing: draw_briefing_panel_with_esc_prompt (9:8934), briefing
  typewriter text 9:8d18, briefing text builder 15:52e4.
- Ambulance: the line buffer at DS:6db8 (90 bytes, HANDOFF), filled by
  9:95f4; ambulance-line typewriter 16:2e3c.
- Inner Demon sub-game: segment 18 (18:0378 copies "Inner Demon" and sets
  subgame_active; 18:403e is the player ship's per-frame update in it).
- Game states (HANDOFF): 4 = GAME OVER, 5 = champions/fireworks; the Demon
  ending goes 6 -> 9 -> 5. Demon's Gate is greyed out when unregistered.
- Fireworks: 6:7c14 (rockets and sparks); champions list 6:6576.

## From the game's own help file (ENG_HELP.HLP)

- The Inner Demon is "a dark reflection of you" in a black hole; it pulls
  you in from time to time. Inside: dragons curled around energy balls you
  feed; ESC returns; you come back as you were when you entered. A smaller
  version can be played in the ambulance (practice).
- Noble Weapons (4): Enlightenment, Uncertainty, the Attractive Force, the
  Repulsive Force. Only won from the Demon; not sold in the ambulance.
  With both Forces, the ambulance offers "Unify Forces" (the Inner Force).
- Two ways to finish: capture or destroy every icon on the drive, or hold
  all 4 Noble Weapons; then enter the "Demon's Gate" directory.
- Icon Watch window (Alt-I) = window class IS_WATCH.
- Status panel: score, target display (messages from ships and the
  ambulance; 'T' target, 'M' last message), radar (zoomable), damage display
  (Engine, Guns, Thruster, Wings/Cloak), weapon display ('TAB' to switch).

Tools: `tools/ne_resources.py FILE --strings` dumps string tables;
`tools/string_refs.py data/strings/ENG_LANG.txt` lists which strings each
decomp function loads. Their output is game text: keep it in `data/`.
