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
- Also /G2: all of segment 12 (seg12.c has the @cflags line).
- A ternary on `x < 0` gets its arms swapped; `0 > x ? A : B` keeps the order.
- An early `return`/`continue` resets register tracking; a block
  (`if (x != -1) { ... } return 1;`) keeps registers live and merges returns.
- `if (c) return A; else return B;` lays out differently from the same
  without `else`.
- A ternary adds a 2-4 byte compiler temp to the frame.
- Same constant to several fields: separate statements reuse one register;
  a chained assignment does not.
- A callee called both with a struct and with two ints (8:9028) needs an
  old-style K&R definition.
- More type notes: g_05a0 is read as int (map width, with g_05a2); 8:1cbe's
  first parameter is a 2-byte struct {unsigned char idx, type}.
- Statement order, not chained assignment, decides which adjacent stores
  merge into one dword store.
- Variables used only through their address live on the stack.
- A `continue` moves the loop test.
- A shared tail reached from two conditions can come from a `goto` into
  the shared block.
- Object records (0x15a bytes) start at DS:7092 (the lowest offset ever
  indexed), not 70ae. Field-offset mistakes hide in masked bytes; the
  reference check catches them.
- g_1e50 (millisecond clock) should be DWORD: compares against it are
  unsigned.
- Switch with six or more cases including 0 gives a jump table; merging
  `case 0:` with `default:` gives a dec chain instead.
- A constant stored just before being passed is sunk into the push; if the
  game pushes the literal separately, the parameter is `char`.
- Loops with constant bounds are rotated (no initial jump to the test).
- To get one shared tail, write identical statements at the end of each
  branch (cross-jumping).
- More type notes: g_1e4c is used as a far pointer (les); g_0016 is an HWND.
- An unused temporary (`u = expr; x = k - u;`) is removed as a dead store but
  still stops CL folding a negation or division.
- To change layout, change the expression's form, not just operand order:
  CL normalises many equivalent forms.
- `a = b = c = 0` stores c first.
- `do ; while (GetCurrentTime() < t);` gives the busy-wait layout.
- A block that can never run, laid out out of line without an entry jump:
  `while (cond) { ...; break; }`.
- if/else-if chains and switches compile differently; keep whichever the
  game shows.
- `volatile` keeps two zero stores as immediates (2:1c08) [inferred].
- 0x50-byte records start at DS:2f4c (not 2f50). DS:9646 is traced as
  "iMainSmart" in a debug string.
- Struct fields are never constant-propagated, scalar locals are: a POINT
  field reproduces "store 0, reload later".
- Block-scope locals get slots after the compiler temporaries.
- Two adjacent zero stores merge (`xor ax` + stores) unless the globals
  differ in type (unsigned vs int keeps immediate stores).
- `if (c) x = f(A); else x = f(B);` gives the tail-merged push/jmp/call form;
  a `?:` argument gives `sbb` arithmetic.
- ExtractIcon needs <shellapi.h> (else it compiles as cdecl).
- 18:1934 is pascal (retf 6); fn_06_84fc and fn_06_7c14 return int.
- A global the compare always loads wrongly may be a static local inside the
  function (DS:17c0 in 10:565a). match.py cannot check static references.
- In global-vs-global compares the earlier-declared extern goes into ax.
- Block-scoped locals share stack slots.
- Two ints pushed as one dword argument: a union with a long; a struct is
  split into register pushes.
- A loop step at the end of the body may belong in the for-increment with
  the comma operator.
- A call that should be near but comes out far: the callee is in another
  source file (inventory/files.tsv).
- More type notes: g_1d48 is a POINT (GetCursorPos); fn_06_1c0c takes one
  argument; fn_06_12b6 is pascal with a 26-byte struct by value.
- `u1 = z = 0;` with u1 unused reproduces dead `xor reg,reg` zeroing.
- `if (p.b != 14) return;` (early return) keeps struct fields in memory.
- `u = rec.f; if (u != -1)` gives the `mov cx,ax; inc ax; je` pattern.
- Window procs: `UINT cmd; switch (cmd = wParam & 0xfff0)`.
- Record bases (lowest offset touched): 0x1e-byte records DS:6e38; class
  records (0xad) DS:96ea; 0x22-byte records DS:915c.
- Pascal callees: fn_08_08a6, fn_08_2658, draw_scaled_object (retf 0xc),
  fn_08_1b54. fn_10_86ca returns int.
- A local assigned once and used once can vanish (kept in AX); unused stack
  slots in the game are often such locals.
- `y += 18;` before a call is moved into the argument pushes; declaring the
  coordinates as a POINT prevents it.
- Loop with `if (...) { X; continue; }` chain gives "else at loop top".
- Repeated switch-case code is merged; which copy is kept depends on the
  source shape (`if (c) A; else B; break;`; case group before `default:`).
- `dy = 16; dx = 16;` in that order gives one dword constant store.
- g_920e is an HPALETTE; 17:30b0 takes (int id, long v); g_18ac is a POINT.
- To stop CSE of locals across calls, make them POINT/struct members.
- A dead local store is removed but its address computation stays.
- A doubled test in the game may be literally doubled in the source
  (`fac == 0 || fac == 0`, keep with /* sic */).
- DWORD (unsigned long) for timers: g_1e50, g_8e28, g_52d8, g_8e44.
  fn_08_35d0 returns int. The 0x1c-byte array likely starts at DS:66e4.
- For commutative ops and compares the later-declared global is loaded first;
  parameters count as declared after file-scope globals (an extern declared
  inside the function changes that).
- A local assigned but never read loses its store but keeps its load.
- A stack slot written between pushes can be a CSE temp, not a local.
- When the game indexes a global the source already knows equals a local,
  write the global (`g_1df8[g_9328][idx]`), as the game does.
- More types: fn_10_9526 returns HBITMAP; fn_08_083e is pascal (i, j);
  DS:3c8c is POINT[4]; g_3d08 POINT[16], g_3ce8 int[16].
- A load the game makes and ignores: `*(volatile int far *)&p->f;`.
- Chains of `continue` reset register tracking; one `&&` condition or nested
  ifs often match instead.
- A different symbol for the same address can stop an unwanted CSE load
  (12:07c0: g_2f5e[k].f02 vs g_2f5a[k].f06).
- fn_08_35d0 and fn_08_285a return int. Segment 8 from 8256 is its own
  source file (seg08c.c).
- Switch layout: default first, then the first case in source order, then
  the code after the switch, then the remaining cases.
- Clamp copied into each branch (`v = expr; f = v < 0 ? 0 : v;`) gives one
  shared store; a single ternary after the join does not.
- A ternary in a GDI colour argument folds to sbb/and; the game's form comes
  from `if (c) g = a; else g = b;` on a local.
- To make the second of two identical blocks jump into the first, write it as
  `else if (c) X;` without a break.
- 16-bit `imul word` into dx:ax: `(long)a * b` with int operands (e.g.
  `-70L * p->f / 250`). The 32-bit form appears when CL reuses the widened
  value across statements; storing results in POINT members stops that.
- seg11d.c stubs duplicate real seg11.c functions: fine for matching, a
  symbol clash for a full link.
- Search loops: `for (...) if (x) { ok = 1; break; } } else ok = 1;` gives a
  shared `ok = 1`.
- Odd push orders often come from assignments inside call arguments
  (`fn(type = g_6e54, n = g_6e52)`).
- String literals are not merged (DS:13be-13c1 are four empty strings).
