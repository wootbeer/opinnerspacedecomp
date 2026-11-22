# Operation Inner Space – handoff for the restart

The first C rewrite was lost on 2026-11-22: the project folder was deleted, and the recovered copies are zero-filled. This file keeps what we learned, so the restart doesn't have to rediscover it.

## Goal (Matt)
- **Rewrite:** rewrite Operation: Inner Space (SDi, 16-bit Win3.x) as clean, readable C that runs natively on Windows. The Windows build comes first, and Android is later.
- **Faithful to the original:** behaviour stays 1:1 with the original, with the same rules, data, text and visuals. Save files must match byte for byte.
- **Options:** no new features by default. Options such as the extended view, higher resolutions and mods are off by default. With them off, every frame must stay identical to the original.
- **Naming:** name things only when 100% sure, and otherwise tag the name `[inferred]`.
- **Planned change:** try a byte-matching decomp first. The matching source would build two ways: with the old 16-bit compiler, to check the match, and with a modern compiler plus a thin Win16 shim, to make the real Windows build.

## Rules for working (from what went wrong)
- **Backups:** the GitHub repo `wootbeer/opinnerspacedecomp` is the working copy. Commit after every step, and push.
- **No deletes:** never `rm -rf` anything outside a scratch folder. Never delete the VM home folder, because connected folders are mounted inside it.
- **Game data:** keep it out of git with `.gitignore`. That covers INSPACE.EXE, the DLLs, WAV/DIB/MID files, DOSBox and Theworks. It's copyrighted.
- **Build hygiene:** plain C99, no globals, and zero warnings with `-Wall -Wextra -pedantic`. No pragmas that hide warnings.
- **Verification:** verify every function against the original. Count harness bugs separately from port bugs, because many divergences we chased turned out to be harness bugs.

## Binary facts
- **Files:**
  - `INSPACE.EXE`: the game.
  - `ISPACE.DLL`: graphics and support helpers, called by ordinal.
  - `IGRAPHIC.DLL`
  - `ENG_LANG.DLL`: strings.
  - The sound DLLs.
  - `FACTORY.EXE`, `BACKUP.EXE`.
- **Format:** Win16 NE. The selector for segment n is `0x1000 + 8*(n-1)`, and DS = `0x1090`.
- **Packing:** `INSPACE.EXE`, `ISPACE.DLL`, `FACTORY.EXE` and `BACKUP.EXE` are OPTLOADER-packed (LZ). In `ISPACE.DLL`, segment 1 has 0x1e7 plain bytes before its LZ stream. Unpack before any analysis or matching.
- **Disassembly pitfalls:** port from the disassembly, not from Ghidra's C. Ghidra gets these wrong:
  - `cwde` should be CBW.
  - `cdq` should be CWD.
  - Pascal argument order.
- **32-bit helpers:** the compiler calls helpers for 32-bit math (abs, ldiv, lmul), for example `1040:88dc` abs32. A test harness must implement them, not stub them to 0.
- **Text:** text goes through GDI TextOut with Arial via CreateFont at many heights; no system font is used. The port mapped it to Liberation Sans/Serif bitmap fonts (SIL OFL).
- **Sound:** sound is `sndPlaySound` (one channel) plus MCI. Music is 4 MIDI files in 12 sections.
- **Registered game:** `INSPACE.INI` `Full=1` was our stand-in switch, not an original key.

## Game flow (verified behaviour)
- **Sequence:** intro logos, title, credits, desk scene (a 3D room drawn by ISPACE ord 32), navigation window, briefing, wave, debrief, then back to the desk.
- **Demon:** the real Inner Demon appears at random. Demon's Gate is greyed out when the game is unregistered.
- **States:** state 4 is the GAME OVER screen. State 5 is the champions/fireworks screen. The Demon ending goes state 6, then 9, then 5.

## Known quirks of the original a faithful port must keep
- **16-bit wraps:**
  - The object index wraps (index 8195 becomes 3).
  - The class lookup wraps at `class & 0x3fff`.
- **Uninitialised reads:**
  - `1060:0d6c` steer_toward_direction: unused steer modes are never reached by missiles. Launch code stores modes 2, 3 and 4.
  - `shot_hit_object` reads the low word of the Demon map width.
  - `1010:1d0a` text buffer.
  - `hud.message_title`: there is leftover data behind the NUL.
- **Ambulance line:** the buffer at DS:6db8 is 90 bytes, followed by demon.host_rect at DS:6e08. The longest real line is 67 characters.
- **Summons:** report_crime, the enforcer order and escalation call `adbe` (summon with music), not `ae68`.
- **Shot damage:** shots damage rocks. Damage callback 5090 reads DS:9442 for class 0x1e.

## Selected names (confirmed)
- **DS words:**
  - DS:6b00 fireworks_end_ms
  - DS:1c38 fireworks_next_launch_ms
  - DS:95bc flow.interactive (1 while a person plays)
  - DS:9222 music_pause_state
  - DS:9148 dissolve_active_count
  - DS:058a hazards.ship_redraw_pending
  - DS:9336 session.helper_groups
  - DS:9130 subgame_active (the Demon sub-game)
  - DS:9442/9444 object sizes, DS:9446/9448 masses
- **Functions:**
  - 1040:8934 draw_briefing_panel_with_esc_prompt
  - 1060:1fc2 spawn_gun_shot
  - 1078:08e4 self_destruct_ship
  - 1060:3008 ship collected aftermath
  - 1048:49d4 race marker strip
  - 1050:4108 lap timer
  - 1018:8b82 race position
  - 1050:488c race radar background
  - 1048:8b1c world map
  - 1088:551a / 59ec repulsive / attractive force weapons
  - 1048:a856 / a90c sprite DC release / restore
  - 1060:3d40 draw_scaled_object
  - 1010:304c describe_defender_order_message
  - 1010:563c command_watch_ship
  - 1080:4354 pilot panel header
  - 1080:3ba6 ship status lines
- **Cheats:** cheat '3' summons the Knight and '4' the Pirate.

## Bugs found last time (traps to avoid)
- **Radar clip:** the radar blit was clipped by a stale play-view clip. The original uses a fresh DC with no clip.
- **Monochrome bitmaps:** they must map to 0/255, not to the palette's white.
- **Stale copies:** stale struct copies were written back over live state. This was the most common bug class, and a matching decomp avoids it entirely.

## Next steps
1. Clone the repo, add `.gitignore`, and put the game files in an ignored `data/` folder.
2. Unpack the NE segments (OPTLOADER) and set up the disassembly.
3. Identify the compiler and its flags from runtime signatures and prologues. Get the toolchain running in DOSBox or old Windows. Pilot-match 2–3 small functions.
4. If matching works, go function by function with a percent-matched score. If it doesn't, fall back to a verified port with the Unicorn harness.
