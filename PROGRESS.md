# INSPACE.EXE decomp progress

- Functions matched byte for byte: **842 / 858** (98.14%)
- Code bytes in matched functions: **499327 / 520258** (95.98%)
- C runtime functions (from MLIBCEW/MLIBCAW.LIB, not counted): 80
- Functions in source, not yet matching: 0

Compiler: MSVC 1.5x CL 8.00c, `/AM /G3 /Gw /Gs /Os`. Regenerate with `python3 tools/progress.py --write PROGRESS.md`.

## Near-matches (written in C, logic complete; not byte-exact)

Each differs from the game only in a compiler register, stack-slot or
block-placement choice. Kept as-is for the readable/portable source.

| Function | Size | Match | File |
|---|---|---|---|
| 11:1b44 | 136 | 99.3% | seg11b.c |
| 8:1e32 | 2086 | 99% | seg08.c |
| 10:0736 | 302 | 99% | seg10b.c |
| 10:0a26 | 366 | 99% | seg10b.c |
| 10:0864 | 450 | 99% | seg10b.c |
| 12:3e98 | 3829 | 87% | seg12.c |
| 6:301a | 1966 | 84% | seg06d.c |
| 16:0000 | 162 | 82% | seg16.c |
| 8:3688 | 1124 | 74% | seg08b.c |
| 18:2c1e | 975 | 71% | seg18.c |
| 7:40c4 | 1721 | 58% | seg07.c |
| 7:0000 | 4507 | 48% | seg07b.c |
| 15:454c | 737 | 41% | seg15b.c |
| 17:3746 | 1119 | 29% | seg17.c |
| 12:4d8e | 447 | 26% | seg12.c |
| 18:49d8 | 1004 | 26% | seg18.c |
