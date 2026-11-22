# How to decompile a function (INSPACE.EXE)

Setup (once per container): the game files in `data/`, unpacked with
`tools/optl_unpack.py` into `unpacked/`; MSVC 1.5x (`BIN`, `LIB`, `INCLUDE`)
in `/home/user/toolchain/msvc` (or `MSVC_DIR`); `apt-get install dosbox`;
`pip install capstone unicorn`.

1. Pick a function from `inventory/INSPACE.EXE.tsv` (seg:off, size). Skip
   kind `lib` (C runtime) and segment 5 (runtime segment).
2. Read it: `python3 tools/disfn.py SEG:OFF`. Calls show import names,
   internal targets and DS names. `inventory/files.tsv` shows which functions
   likely shared a source file.
3. Write C in `src/inspace/segNN.c`, tagged `/* @addr SEG:OFF */` on the
   line before the definition. Follow the code's shape closely: CL 8.00c
   `/Os` output tracks the source structure (`if (x >= 0) return x;
   return -x;` and `return x >= 0 ? x : -x;` compile differently).
4. Check: `python3 tools/match.py src/inspace/segNN.c`. A function counts
   only when it says MATCH (every non-fixup byte equal).
5. `python3 tools/progress.py --write PROGRESS.md`, commit, push.

Conventions
- Placeholder names: functions `fn_SS_OOOO`, globals `g_XXXX` (DS offset),
  far function pointers `g_fp_XXXX`. Real names only when certain (else tag
  `[inferred]` in a comment); confirmed names live in `names/INSPACE.EXE.txt`.
- Shared declarations: `src/inspace/inspace.h`. One global, one type.
- Near call (`push cs; call near`) in the game = the callee must be defined
  in the same C file. Use a stub (marked "Not yet decompiled") until the
  callee is done. Far call to a function = it must not be defined in that
  file.
- Strings: if a pushed `ds:offset` holds a string in DGROUP's file data,
  write the literal; if the offset is past the data (BSS), it is a buffer
  global.
- Calling convention: `retf N` = pascal (callee pops), `retf` = cdecl.
  Missing `add sp` after the last call of a function is the `/Os`
  `lea sp,[bp-2]` epilogue, not proof of pascal.
- `push 0; push x` for a long argument = a 16-bit unsigned value widened;
  `cwd` before = signed.
- Plain C99-compatible code where the 1993 compiler allows; keep
  `far`/`pascal` as the game needs them for matching.

## Compiler patterns found while matching (CL 8.00c /Os)

- Some original files were built with `/G2`: no 66-prefixed instructions,
  long conditional jumps as `jcc short` over `jmp near` (not `0f 8x`),
  far-pointer zeroing as `sub ax,ax` + two word stores. Put such a file's
  functions in `src/inspace/segNNb.c` with `/* @cflags /AM /G2 /Gw /Gs /Os */`.
  Known: 10:0000-39a8 (file 21), part of segment 8 (about 3688-81f8).
- switch: case bodies are laid out in source order; the tests follow numeric
  order.
- `x = x < 640 ? 640 : x;` keeps x in AX; the `if` form stores to memory.
- `v &= ~MASK;` as its own statement gives the in-memory `and`.
- `if (c) n = a; else n = b;` and `n = c ? a : b;` load operands in different
  orders.
- Long from two words: `((long)hi << 16) | (unsigned)lo`; MAKELONG adds a temp.
- Locals: the first declared gets bp-4; unused locals must still be declared
  to reproduce `sub sp,N`.
- Under /G3 two adjacent int stores of 0 merge into one dword store.
- A struct passed by value to a pascal function is pushed as one block;
  field assignment order before the call matters.
- Loops whose body is an if/else or `&&` chain: CL puts the *else* arm at the
  loop top; write the if/else the way round that gives the game's layout.
- `goto` sometimes reproduces a loop layout that `break`/`while` cannot.
- Adjacent constant stores merge into one dword store only in the right
  statement order.
- Odd-sized records need `#pragma pack(1)` (seen: 0x297, 0xad, 0x23).
- A segment can hold several original files that far-call each other: split
  into segNN.c / segNNa.c / segNNb.c following inventory/files.tsv.
- `tools/objdiff.py SRC.c NAME` shows the compiled code next to the game's.

## Type questions to settle when consolidating inspace.h
- g_05a0: declared long, but 4:83ae reads it as two ints (world width/height
  [inferred]).
- g_6084 / g_607c: RECTs (seg 4) vs int g_6084 (seg 17).
- fn_10_94c4 last argument: LPSTR, not long.
- g_fp_3c50: called with (int, int, int, int, long, int) and with 7 ints.
- g_0024: a module handle (LoadLibrary/FreeLibrary).
- Order of extern declarations can change register choice in compares
  (6:1e68 needed `g_1e50` declared before `g_1c34`).
- `x = y = 0;` on two adjacent locals becomes one dword store (lower address
  first); for globals use `*(long *)&g = 0`.
- `x = mem - expr` compiled as `sub ax,[mem]; neg ax` needs a temporary for
  expr.
- windows.h `min`/`max` reproduce the `cmp; jle; mov` clamps.
- Two near-identical calls in if/else are tail-merged by the compiler; write
  both calls, not a `?:` argument.
- Use your own scratchpad subfolder; the scratchpad is shared.
- More type notes: g_1e4c holds a GlobalLock pointer; g_13dc is an HDC;
  g_1df8 needs at least 21 far pointers; fn_10_1eb6 is called with 3 args
  from 18:07b2; fn_08_2bbe returns a POINT (pascal, hidden pointer, retf 6).
- `if (A) {X} else {Y}` inside loops puts Y before the loop test; if blocks
  come out mirrored, invert the condition and swap them.
- `RGB()` / `PALETTERGB()` reproduce the game's byte arithmetic.
- Put comments above the `@addr` tag: match.py needs the tag directly
  before the function definition line.
- Also /G2: 15:0000-52e4 (seg15b.c), 6:5d58-end (seg06b.c).
- More type notes: fn_10_6e76 is (int lo, int hi) as called at 15:7b34;
  fn_10_6308 and fn_10_6ec6 return int (bitmap handle); REC_297 needs pack(1);
  g_94ac is int; g_1e50 is DWORD.
- match.py also checks every fixup's target (globals by g_XXXX / names
  file, functions by fn_SS_OOOO / names, near calls, Windows imports): a
  function that reads the wrong global, or swaps two, is reported as
  WRONG REFERENCE, not MATCH. Unknown symbols (string literals, other names)
  are not checked.
- `a = b = 0;` stores b first.
