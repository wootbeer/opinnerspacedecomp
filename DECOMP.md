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
- In loops the arm the game puts at the loop top must be the `else`:
  `if (A && B) {X} else {Y}` vs `if (!A || !B) {Y} else {X}` lay out
  differently.
- A separate `if (...) return 0;` puts the return block right after the test;
  folding it into a longer `||` chain moves it.
- `__aFulmul` comes from plain long multiplies; 32-bit `idiv ecx` from plain
  long division.
- fn_11_b09c is pascal (n, a); fn_10_754a likely (int, POINT, int); g_4fcc is
  `char far *` (briefing text).
- Zoom arithmetic: `#define SC(n) ((n) << g_9156 >> 1)`; `SC(v)*2` gives
  `shl; and al,0xfe`.
- Dead code the game keeps (address only, dead cwd pairs): reproduce with an
  unused local assignment (`dead = o.x + o.f22;`, `l = (long)a + (long)b;`).
- An unused block-scope `int pad[2];` can move later compiler temps (12:2b20).
- `1 > f() ? 1 : f()` keeps the arm order; `f() < 1 ? 1 : f()` swaps it.
- `old = m = 0;` merges into one xor only if both have the same type.
- fn_13_2f30 is pascal. 0x34-byte records start at or below DS:3d50.
- `x /= 2;` compiles to `mov cx,2; idiv cx`; `x / 2` gives cwd/sub/sar.
- A loop body that falls straight into the function exit had a `break` or
  `return` after the work.
- `u = load; r = u + other;` forces a load order (temp keeps its slot).
- Block-scoped locals in sibling blocks share a slot.
- If a near call to a defined function comes out far, check the callee's
  definition was not deleted by accident.
- 0x34-byte records start at DS:8560. fn_13_2206 returns int
  ((type << 8) | index). fn_08_0b76 is pascal.
- Every declared local takes a frame slot even when kept in si/di; frame
  gaps can be register locals.
- Locals inside a struct (`struct { int px, py, size; } r;`) stay out of
  registers.
- A value in si with no slot can be a CSE of `n + 1`: write the expression
  twice instead of adding a variable.
- Both words loaded before either store = a 4-byte struct copy.
- A switch testing a case value explicitly though it shares default's body
  needs a separate identical `case N: ...; break;`.
- Quick test of one function: copy the file's header and inspace.h into a
  scratch folder with the function.
- `mov cx,1000; imul cx` is only CL's form for a multiplier above imm8.
- 17:33ee passes a near pointer where fn_11_3fd4 expects far (bug in the
  original): call through a cast, keep it.
- Pushed constants that sit inside a dword table are ints, not strings;
  strings defined in other files: declare as `g_XXXX[]`.
- One `volatile` access changes code generation for the whole function
  (constants pushed as immediates everywhere); use `*(int *)&g` for a single
  plain access instead.
- A dead `les bx,[g]` comes from a dead store to an existing unused local
  (`j = g_1e1c->f00;`).
- A final switch whose cases return puts its test chain at the top of the
  function.
- CL merges adjacent word arguments into one `push dword`.
- Block-scope locals in sibling switch cases share slots; declaration order
  decides which gets which.
- More types: g_13dc is an HDC (unsigned); g_fp_3c54 returns int; g_9210 is
  an HINSTANCE.
- A bare label (no goto) resets CL's register tracking: constants pushed as
  immediates after it (6:190c).
- `p.x = p.y = 0` on a POINT gives one dword `xor eax` store; also works
  inside an argument chain.
- HIBYTE/LOBYTE of LOWORD/HIWORD reproduce byte stores of a long result.
- g_1df8 index = (DS offset - 0x1df8) / 4. Sprite DC arrays: g_39e8 (HDC),
  g_3974 (old bitmap), g_3ad0 (bitmap), g_3a5c (palette).
- More types: g_88c4 is a POINT; fn_18_1934 is int far pascal (key, unused,
  HDC); fn_08_3aec and fn_08_3fbe are pascal; fn_10_804c returns long.
- An 8-byte copy done as two dwords, high half first, comes from two POINT
  assignments (+4 first, then +0), not one struct copy.
- `if (a) s /= 3; else if (b) s /= 3;` reproduces a shared block another
  test jumps back into.
- A retf size that differs at the very end: the function is pascal; reverse
  the parameter order.
- More types: g_5224 is POINT[]; g_9e60/9e70/9e80/9e90, g_1c3e, g_05c0 are
  DWORD; abs32 is long abs32(long); fn_11_63b4 is pascal (n, a).
- Assigning into a never-read local inside an expression
  (`if ((u = expr) > k)`, `b.x - (w = W*8)`) changes evaluation order or
  folding without emitting a store.
- Object refs `(type << 8) | index` passed to pascal functions: WORD params
  read with HIBYTE/LOBYTE (a 2-byte struct reorders the loads).
- A void call inside an `||` chain: `(f(...), 0) || ...`.
- A `return 0` in a loop compiled as a jump to the final `return 0` was a
  `break`.
- A bare label just before a load stops an unwanted CSE of a record address.
- CL moves stores of the same constant forward to merge them; writing the
  globals as elements of one array (`(&g_9406)[k]`) stops it.
- An extern declared before `#include "inspace.h"` changes register choice
  against globals declared in the header.
- `if (...) continue;` loses cross-block CSE (`row + i`); `if (...) {body}`
  keeps it.
- `if (!(v & 1)) A; else B;` lets CL cross-jump B with an identical later
  block.
- `CFLAGS='... /Fc'` with match.py --keep gives listings with symbol names.
- fn_13_1076 is int far pascal (int type, int n). DS:9406 and DS:92ec are
  int[15] per-type tables.
- A bare label right after a call stops CL keeping a record index in si
  across it, and stops it sinking an earlier constant store into a push.
- Two adjacent globals stored as one dword (`mov dword [x], imm`) must be
  one object: `extern struct { int a, b; } g_x;`.
- Fields below a record base: declare a second view of the array at the
  lower base (the reference check works on the 16-bit sum).
- A frame one slot too big: a block-scoped local shares its slot with a
  compiler temp.
- Extern declaration order also decides how CL reassociates sums (and so
  what it CSEs).
- A global declared only at block scope counts as later than the locals:
  loaded first in commutative ops.
- The `je L; ...; L: jmp end` trampoline comes from a plain `if (a && b)
  {...}` as the last statement of a case or branch.
- More types: g_6e14/g_6e18 (demon host window size, position) are POINTs;
  g_190a/g_190e, g_1c54/g_1c58 POINT cursors; g_1876, g_05ac, g_1916,
  g_191a, g_1c60, g_187a, g_18b6 DWORD timers; g_94c8 compared signed.
- `*(POINT far *)&rec.f04 = p = fn(p);` gives the dword store to the local
  then word stores into the record.
- Wrapping the body in `if (...) { ... }` instead of an early return keeps a
  record pointer in bx across the next branch.
- Assignments inside call arguments (`f(d.x = ..., d.y = ...)`) give the
  "y computed first" order.
- Locals placed after the hidden POINT-return temporary are block-scope
  locals.
- object_sizes[2] / object_masses[2] cover DS:9442-9448.
- A global added to a local is loaded after it; an extern declared inside
  the function loads it first.
- Clamp without an intermediate store: the whole clamp in each branch
  (`if (c) g = g-3 < 50 ? 50 : g-3; else g = g-5 < 50 ? 50 : g-5;`).
- `if (c) x += A; else x += B;` gives a shared `add [mem],ax`.
- Early `if (x > y) return; if (g) return;` lets the first test jump to the
  second's `jmp exit`.
- Frame slots below the declared locals are often compiler CSE temps
  spilled across calls, not locals.
- fn_10_73a6's last two parameters are char; fn_18_5350 takes (x, y) pushed
  as one POINT; fn_08_124a is pascal.
- Taking a variable's address (`*(BYTE *)&v`, a union view) makes it
  addressable and loses CL's register tracking of it for the whole function.
- Scratch diff scripts that mask immediates hide `sub sp` frame-size
  differences: always confirm with match.py.
- fn_11_5ab6 is pascal (n, k); fn_04_0078 is pascal (n).
- A long constant passed through a stack slot (`mov ax,imm; mov dx,imm`,
  store, `push dx; push ax`): a DWORD local (`rop = SRCCOPY;`); `long` gives
  immediate pushes.
- `mov al,byte; and ax,0xf; cmp ax,0xf` comes from a local holding the masked
  value; `(x & 0xf) == 0xf` gives `and al`/`cmp al`.
- A char-array index `[bx+si+0x34]` needs an array starting lower read with
  an offset (`f30[k + 4]`); `f34[k]` emits `add bx,0x34`.
- CL pulls every store of the same constant in a basic block down to its last
  occurrence (one register load). If the game repeats a constant in separate
  groups, there were block boundaries in between. In 10:1fb2 they are
  reproduced with degenerate `if (c) X; else X;` tests [inferred: the
  original's real boundaries are unknown].
- Long table initialisers can be generated from the disassembly in binary
  store order (scripts in scratchpad/s10r5/).
- In `SelectObject(dc, x = fn(...))` CL pushes dc before the inner call.
- Race tracks (10:320a): LAZYLOOP, SDISPEED, GRANDPRI; layout in seg10b.c.
- More types: g_fp_3c40 returns a bitmap handle; fn_10_6ec6 returns HBITMAP;
  g_2408 is DWORD.
- To pick which copy of a cross-jumped tail CL keeps, turn one early
  `return` into `goto out;` with `out:;` at the end.
- Dword merging of adjacent constant stores has no single order rule: try
  high field first and low field first.
- `if ((c = f(k)) != 3 && c != 6 && c != 1)` gives a cmp/cmp/dec chain that
  looks like a switch.
- fn_13_a6bc is pascal (int); g_4eec is int[][3]; g_8e08 is long[].
- A dead `imul bx, n, size` before an assignment: `if (rec[n].f) x = 1;
  else x = 1;` (CL drops the test, keeps the address) [inferred: the field
  tested is arbitrary].
- `switch (st) { default: break; case 0: ... }` (default first) gives
  `mov ax,st; or ax,ax; jne` and out-of-line placement.
- A value in di used twice can be an expression written twice, not a local.
- CL keeps dead stores to locals inside loops (and in functions with
  loops); outside loops it drops them.
- An if/else-if chain on a local gives "store result, dec ax, compare slot";
  a switch keeps the value in ax.
- fn_02_1a5a's result is used (returns int, whatever g_fp_1d5c leaves).
- In functions where every path ends in `return 0`, fall through to one final
  `return 0` (shared `xor ax,ax`).
- Two int locals assigned constants can stay in memory (one dword store,
  not constant-propagated); stack position decides load order in `a + b`.
- `(long)x * 22 / 100` with x an int global gives `mov ax,22; imul word [x]`
  then __aFldiv.
- fn_07_5090 is int far (int type, int idx, int amount); REC_70.f5e
  declarations elsewhere have 2 arguments. g_95f4 is a bitmap handle.
- Read every incoming jump before blaming the compiler: an odd `je L; jmp`
  is often the false exit of an outer `if (a && b)` around a nested if.
- Char arrays sit at bp-2-size; CL dword-aligns `long` locals (a long at a
  non-multiple of 4 is a struct wrapper or a temp).
- A value compared with `cmp ax,0xffff` then pushed from ax is WORD.
- More types: g_9e41 is int[] (9e41..9e53); g_88c0 is copied as a POINT;
  g_a157 is char[10]; g_1050 POINT[]; g_116a int[]; g_6e10 DWORD.
- A ternary inside an array index that adds a frame temp: write the whole
  assignment in both arms of an if/else (cross-jumped tail, no temp).
- Two adjacent zero stores to separate int globals as `mov dword [x],0`:
  `*(long *)&g_x = 0;`.
- Early `return 1`/`return 0` compiled as jumps to shared return blocks at
  the end: `goto done;` with labels on the final returns.
- How a variable is used later can change an earlier load (4:4fc8: a later
  `LOBYTE(v) & 1` made an earlier compare load a byte).
- The /Fc listing (`CFLAGS='/AM /G3 /Gw /Gs /Os /Fc' match.py FILE --keep`)
  shows every local's bp offset: fastest way to size frame fillers.
- Two block-scope ints sharing a 4-byte compiler temp: one block-scope POINT.
- `if (c) { if (!d) goto skip; ... } x = 0; skip:` gives one store reached by
  fall-through and by jump.
- fn_11_39d8 is pascal (type, n, HDC).
- Chained assignment stores right to left: `a = b = x` stores b first;
  `f_03a = f_038 = f_036 = f_034 = 2` stores f_034 first. Swapped chains give
  identical bytes and are only caught by the reference check.
- Several `if (x == K) return 0;` in a row each redo the address imul; one
  `if (x == 3 || x == 13 || ...) return 0;` gives the trampoline layout.
- fn_08_7d70 is pascal (8 far int pointers, 2 ints); fn_02_170e(void).
- Immediate dword zero store to two int-sized words:
  `((int *)&g)[0] = ((int *)&g)[1] = 0;` (`*(long *)&g = 0` shares a zeroed
  eax with neighbouring stores).
- An else-arm ending in `if (A || B) return 0;` makes CL put the join after
  the then-arm; two separate `if (...) return 0;` fix it.
- `if (!a && !b) X; else {Y}` puts Y out of line; `if (a || b) {Y} else X`
  does not.
- 6:12b6 (init) takes a WNDCLASS by value, used as its local; WinMain
  passes it uninitialised. fn_05_0364/0352 are _dos_findfirst/_dos_findnext.
- Which copy of a merged tail CL keeps depends on surrounding control flow
  (`if (c) switch` vs `if (!c) break; switch`, `if (a && b) f();` vs nested
  ifs, if/else-if of identical calls vs `{ call; break; }` arms). Deleting a
  candidate block temporarily shows which one forces the merge.
- WPARAM (unsigned) parameters give jb/jbe/ja in switch range tests; int
  gives jl/jg.
- fn_03_00f4's second parameter is char at the call sites (no sub ah,ah).
