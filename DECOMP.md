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
