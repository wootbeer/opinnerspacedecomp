# Port notes: game code translated from the decomp

`port/src/game/` is generated. Do not edit it by hand. To regenerate it, run:

    python3 -I tools/port_translate.py      # writes game.h, win16api.h, segNN*.c
    python3 -I tools/port_merge.py --merge-report   # merge details only

`port/translate-notes.txt` is regenerated on each run. It lists every merge decision and conflict: table lengths, field type choices, arrays cut short, overlapping views and per-line notes.

## How it works

- **DGROUP image.** Plain globals are not separate variables: game.h
  defines each as a typed view of `dgroup[]` at its DS offset
  (`#define g_39f2 DGROUP_AT(HDC (*), 0x39f2)`), and `dgroup[]` starts as the
  data segment of the user's INSPACE.EXE (src/win/dgroup.c). Neighbouring
  globals, arrays the decomp declared without a length (`g_39e8[5]` is
  `g_39f2`), overlapping views and overruns therefore behave as in 1994.
  Globals that hold native pointers (far pointers, the near string
  pointers at DS:0078-0080) are real variables in globals.c; near pointers
  are pointed into the image at start-up. Needs `-fno-strict-aliasing`.
- **Runtime renames** (win16api.h): `rand/srand` are MSC's (`msc_rand`),
  `stat/utime` and `_dev_t/_ino_t/_off_t` the 16-bit DOS ones, and
  `WinMain` is `inspace_WinMain` (the platform's WinMain is SDL's).

- **port_merge.py** parses each decomp file with pycparser. Before parsing, the file's own macros are expanded (except `SC` and `GETPROC`), `far`/`huge` become a parser marker, and `pascal`/`near` are dropped. The script then collects every view of DGROUP and of the records and merges them:
  - **Tables:** struct arrays with the same record size whose bases are less than one record apart form one table. Its base is the lowest view address and its type is one struct with all fields at their true offsets. Fields are named `f_XX` by true offset; a descriptive name is kept when the views agree on it.
  - **Records behind far pointers:** these are grouped by pointer slot. For example, `g_1e30` is `g_1df8[14]`.
  - **Other globals:** one declaration per DS address. The most specific type wins (struct, POINT/RECT, handle, DWORD, then int). Arrays win over the scalars inside them.
  - **Mismatched views:** an access through a narrower or differently typed view becomes `LO16`/`HI16`/`LO8`/`HI8`, `VIEW(T, field, off)` or `VIEWP(PT, field, off)`. These macros are in `game.h`. They are exact because records keep the original byte layout: fixed-width types with `#pragma pack` as in the original. They also assume a little-endian target.
- **port_translate.py** edits the decomp text, so comments and layout survive:
  - It drops the file-local typedefs, externs and prototypes, plus the stubs that only forced near calls in the 1994 build.
  - It maps the 16-bit types to `int16_t`/`int32_t`/... and replaces `@addr` tags with an address comment.
  - It rewrites accesses through other views onto the merged tables. Index shifts become `[i + q]`, fields are renamed by true offset, and `*(T *)&x` / `((T *)&x)[k]` aliases become the global or field they name.
- **Message lParam.** `LPARAM` is pointer-sized (`intptr_t`), as in
  Win32, so messages carry native pointers (LB_ADDSTRING, LB_GETTEXT,
  CB_ADDSTRING, WM_DRAWITEM, ...). The translator turns a `(LONG)` cast of
  a pointer passed as the lParam of SendMessage, PostMessage,
  SendDlgItemMessage or DefWindowProc into `(LPARAM)` (17 sites, all in
  seg06d; `lparam pointer` in translate-notes); the 16-bit pass still
  types LPARAM as the 32-bit long it was.
- **win16api.h** is generated from the MSVC 1.5x headers. It holds the API prototypes and constants the game uses, with fixed-width types. Standard C functions come from the host libc.
- **16-bit arithmetic** (`tools/port_int16.py`, run on each generated file). It types every expression under the 1994 rules (16-bit int/unsigned, MSC conversions, literal types) and tracks the range of its native value. Natively an int16 expression equals the 1994 value modulo 2^16, so a cast is inserted only where the whole value is used and can differ: compare, `/ % >>`, condition, widening to long, a libc int parameter (`(int16_t)(a * b) < c`, `(uint16_t)i < u`, `u == 0xffff`). Stores to 16-bit variables, 16-bit parameters and array indexes need none. Reads through a view of the other signedness (`int` view of a HWND, `long` view of a DWORD) are marked by the translator and cast where it matters. Long arithmetic wraps with `-fwrapv`. Counts by kind and every site are in translate-notes; `python3 -I tools/port_int16_check.py` checks the result against a 1994 evaluator on random values.
- **Names.** Confirmed names from `names/INSPACE.EXE.txt` replace `g_XXXX` / `fn_SS_OOOO` everywhere in the generated code (declarations, definitions, calls, uses). Names tagged `[inferred]` are only comments in game.h; where the decomp already used one as an identifier (`command_watch_ship`), the code goes back to the address name.
- **Signatures** (`tools/port_overrides.py`, `port/overrides/signatures.txt`). The callee's definition is the real signature. The overrides file lists the exceptions (thunks whose callers use the result or pass other types, K&R definitions, a few single calls); they are applied to the decomp text in memory before parsing, so game.h, the definition and all callers follow. The translator then adapts every call to the callee's signature: extra arguments are dropped (side effects kept, as statements before the call), two values become a `(POINT){x, y}` or a long (`MAKELONG` or a literal), a long or a two-int record passed for two int parameters is split, `(char)idx | type << 8` becomes `(OBJREF){idx, type}`, and a function stored in a function pointer loses its cast when it has the pointer's type. Each adaptation is a note in translate-notes; dropped arguments are listed under `== dropped call arguments`.
- **Assignments read by another argument.** C leaves the order of a
  call's arguments open, MSC did not: `PatBlt(dc, x, y, t1 = n, t1, ...)`
  (8:158a, the stars' erase) passed the new t1 twice in 1994 (pascal
  callees take their arguments left to right; for the C callee of
  10:4412 the compiler pushed the one value twice), while gcc read the
  old t1 first, so the stars were erased one pixel short and left
  trails. The translator makes such an assignment a statement before the
  call (or a comma expression) and passes the variable (4 sites,
  `assignment argument hoisted` in translate-notes).

## Current state

- 32 files are translated, with 842 functions and one definition each.
- All 32 files compile without errors (gcc 13, `-std=c99 -Wall -Wextra -pedantic -fsigned-char -fwrapv -fsyntax-only`); 1313 warnings, see 11 and 12 below.
- 1484 casts for 16-bit arithmetic (see `== 16-bit arithmetic casts by kind`). The check evaluates 21885 conditions and assignments: 817 differed from 1994 natively before the pass, none after.

## Needs human judgement

1. **Signature decisions.** See the comments in `port/overrides/signatures.txt`. Ones to check:
   - **seg10 thunks into the graphics DLL** (`fn_10_86ca`, `6b54`, `7370`, `73a6`, `6fec`, `7dd4`, `9526`) and the hook thunk `fn_02_1a5a` were defined `void` but their callers use the DLL routine's result, so they return it. `fn_10_7dd4` (collision test) takes 8 int pointers, 4 ints and 2 int pointers (the definition passed them on as 12 longs); `fn_10_9526` takes a `RECT *` first and two ints x, y where the definition had one long. The DLL pointers `g_fp_3c4c/3c6c/3c78/3c84` and `g_fp_1d5c` were changed to match. Other thunks keep `long` parameters that callers fill with string pointers (`fn_10_73a6`, `6fec`, `7328`): far-pointer step.
   - **K&R definitions** `fn_08_1cbe` (OBJREF, int), `fn_08_9028` (four ints), `fn_11_2154` (int align) are written as prototypes.
   - **`REC_70` function pointers:** a slot called with several shapes takes the longest signature: `f_5e` is `int16_t (*)(type, idx, amount)`, `f_62` is `void (*)(type, n, HDC)`, `f_66` is `void (*)(type, idx)`. Earlier, `f_5e(type, idx)` and `f_62()` would have dropped the amount and the HDC. `fn_07_570a` and `fn_16_085e`, stored in `f_5e`, got the unused parameters (they ignored them in 1994 too).
   - `g_1d4c/1d50/1d54` (hook DLL procedures) are `void (*)(HINSTANCE)`; the GetProcAddress results are cast to the pointer's type.
   - `fn_10_94c4` (ordinal 33's thunk) and `g_fp_3c74` take the string as `char *` (the definition passed it on as a long).
   - `fn_15_80b0` takes two POINTs (callers passed POINTs seen as longs, or MAKELONG(x, y)).
   - `fn_13_2206` returns the OBJREF packed in a word, as defined; the two callers that store it into an OBJREF use `objref_of()` (game.h).
   - WinMain passes an uninitialised 26-byte block as the WNDCLASS of `fn_06_12b6`; the local is now a WNDCLASS (still uninitialised).
2. **Dropped arguments** (the callee ignores them; they may show a bug or a changed signature in 1994):
   - `fn_07_2080(t)`: 30 callers pass a second value, -1 or the object index (`idx`, `i`, `n`, `g_221c[i].idx`). The function only uses the type.
   - `fn_10_1eb6(a)`: 5 callers (seg14, seg18) pass `(a, x, 1)`, e.g. `g_70ae[main_ship].f30` as the second value.
   - `fn_08_99ce(a, b, kind, idx)`: 3 callers pass a fifth value (`1`, `ret`, `ret + 2`).
   - `fn_06_1c0c(void)` is called with 1 and 0; `fn_16_7210(void)` with 0 and 1; `fn_07_119c(a)` and `fn_11_3cc2(n)` with an extra 0 or 1.
3. **Too few arguments in the original:** `fn_10_7480(a, b)` is called with one argument at seg02.c:433 and :1008; the callee then reads an uninitialised word of the caller's frame as `b` (only forwarded to the music DLL as `pt.y`). The port passes 0.
4. **Possible original bug:** seg09b.c:2187 reads `g_9f39[g_9322][g_94a8]`, which is `g_9f3a[g_9322][g_94a8 - 1]` (the compiler folded the -1 into the base). For `g_94a8 == 0` (a difficulty value the same function sets) it reads the byte before the row: `g_9f3a[map - 1][1]`, or for map 0 the last byte of `g_9ec2`. The port reads `g_9f3a[g_9322][g_94a8 - 1]`, which is out of bounds in that case.
5. **Table extents.** Lengths not declared anywhere are guessed as "up to the next declared global"; see `== table length` in translate-notes.
   - `g_6670` is joined with `g_66e0` as one 0x1c table of 14 records. That is a guess.
   - `g_57a8` (0x23) and `g_8870` (0x18) do not end on a record boundary.
6. **Object table base.** It is DS:7090, the lowest address any view uses (a view at 7090 has a field at +0). DECOMP.md calls 7092 the real record start. If 7092 is chosen, every object field name shifts by 2.
7. **Type conflicts the merge settled by rank** (`== field types`, `== global types`):
   - `REC_70 +6a` is DWORD in most files and `void far *` in one. DWORD was chosen.
   - `g_05a0` is `long` in inspace.h, but the code reads it as width + height ints. It stays `int32_t`, and the int views become `LO16`/`HI16`. A POINT-like pair may be the better final type.
8. **Signedness of views** is handled by the 16-bit pass (6 casts). Not covered: a 1994 compound assignment `x /= y` through a view of the other signedness (the pass reports it as `UNFIXED`; there are none now).
9. **16-bit arithmetic.** Done, see "How it works". To check:
   - The casts are exact under the type ranges, so some only matter at the ends of the range (`(int16_t)(n - 1) < 0` for n = -32768): 246 casts, listed with the rest. A value-range analysis of globals could drop them.
   - `rand()` is assumed to be the 1994 runtime's (0..0x7fff, 408 calls); the host's is not. The port needs MSC's `rand`/`srand` (also for identical sequences).
   - Variadic arguments are passed as native ints; the callee truncates: `va_arg(ap, int16_t)` became `(int16_t)va_arg(ap, int)` (gcc aborts on the former). A native `wsprintf` must likewise print `%d/%u/%x` as 16-bit values unless `l` is given.
   - `abs(-32768)` and `-32768 / -1` (a divide-overflow trap in 1994) are not reproduced.
   - The `SC(n)` zoom macro now shifts in 16 bits before `>> 1`.
   - Likely overflows in the original (kept, as 1994): `(long)(dv.x * dv.x + dv.y * dv.y)` in fn_08_1e32 (and `w * w - k * k` in seg11.c) wraps for distances above 181; in fn_04_2da2 `(...) * 500` added to the longs `g_5078`/`g_1e58` wraps when the factor exceeds 65; in fn_08_5df2 `dmg * 200 + g_1e50` (a time) wraps for dmg above 163.
10. **Struct views over plain globals** (`RACEV` at DS:9ea2) are resolved to the individual globals. 8 aliasing casts could not be resolved and are left as they were (`alias kept`).
11. **Layout-only constructs are not removed yet.** They still show as warnings:
   - 559 unused locals (mostly frame fillers)
   - 80 variables set but never used
   - 8 unused labels
   - `if (0)` blocks, `(f(), 0) ||` chains and volatile dead loads are still in the code

   Removing unused locals is safe and mechanical. The rest needs a per-case look.
12. **Other warnings:**
   - 197 `char` array subscripts. The original indexed with a signed char, so the fix is an explicit `(int)` cast, not unsigned.
   - 95 `&&` within `||` and 31 other precedence warnings.
   - 49 unused parameters.
   - About 220 pointer/integer conversions. Most are string or near-pointer arguments passed where the prototype says int, and `(long)` casts of far pointers; see "Far pointers" below.

13. **Layout tricks added or resolved to make the code compile** (to revisit with the later steps):
   - A long passed for two int parameters is split with `LO16(x), HI16(x)`: `fn_10_6ee6` (3 callers), `fn_10_7328`, `fn_13_9a18`; the long fields (`g_96d2[].f_a9`, `g_7090[].f_03e`) are probably two ints.
   - 1-D views of 2-D arrays are indexed in the 2-D array: `g_6098[].f_30/f_48[j]` becomes `[j / 6][j % 6]` (seg13), `g_5b2c[i * 4 + j]` becomes `g_5b28[i][j]` (seg09), `g_3854[x]` becomes `g_3824[3][x]` (seg13).
   - `POINT *` views of `g_1df8` slots (`*g_1e38`, `g_1e38[3].x`) become fields of the record (`g_1df8[16]->f_00`, `->f_0c`).
   - Views a few bytes below a global of the same shape are rewritten onto it with a shifted index (`g_a191[i]` = `g_a193[i - 2]`, `g_9f39` above).
   - seg10.c:1668 passes the record's position, read through a long/POINT union in the decomp, as the POINT (`call` override, written in port terms).

## Game speed (Calibrate)

The game is paced by real time, not by the processor (help file, "Play
Speed": "calibrated for 36 frames/second"). Its main loop (2:0000) polls
with PeekMessage and, whenever no message waits, runs one idle step
(2:1c08, 7:0000); the step counts idle calls and does a frame only
every g_9004-th (outside waves) or g_8f76-th (in waves) call, and 7:2206
and 7:0000 rescale those counts every 250 ms and every second towards 72
frames a second outside waves and FrameRateSet (INI, default 36) in
waves, with timeGetTime forcing or skipping wave frames 27-28 ms apart.

Calibrate (15:5e22, the counting digits at start-up) is the number of
idle calls in one second times 2.3, written to the INI by 6:0a6c. It
sets the starting frame divisors (g_9004 = Calibrate / 50 above 1200,
/ 150 above 850, else 0; g_8f76 from INI GameSpeed, which defaults to
Calibrate, / 28 above 600), the thrust divisor g_9006 (Calibrate / 38,
kept within 7-10: 10 for any value from 380), and per-frame steps of some
animations, chosen for slow (below 800 or 1300) or fast machines; the
title's enhanced logo needs 800. The help file's table: above 1300 "very
fast", 800-1300, 520-800, below 520 "use LOW or MEDIUM Detail".

On a modern host the idle loop ran 10 000-25 000 times a second
(Calibrate 22717 was seen), the value is stored in a 16-bit word (it
wraps negative above 32767, about 14 000 calls a second, which would
select every slow-machine branch), the frame-divisor arithmetic
(`g_914c * g_9004` in 16 bits) overflows on still faster hosts, and the
busy loop takes a whole processor core.

**Port's choice:** PeekMessage (user.c) answers "no message" once a
millisecond (calls owed after a long sleep are caught up, at most 50),
sleeping in between: the game sees one fixed machine whatever the host,
Calibrate is 2300 (+-20), the "very fast" class, so every speed-dependent
choice is the fast machine's: thrust divisor 10, the fast animation
steps, the enhanced title. Frames per second are what the original
gives on a fast machine (36 in waves, shown with B: "36 SET, 35
ACTUAL"). [uncertain: which machine the designers had in mind; the
help file's top class]

Every use of the calibrated value (g_8ffc) outside start-up, all at
2300 in the port:

- 6:0a6c (start-up): frame divisor g_9004, thrust divisor g_9006 (10
  from 380 up), in-wave divisor g_8f76 via GameSpeed. The divisors are
  rescaled by time within a second, so only g_9006 lasts. g_9008 is
  derived from GameSpeed and then overwritten with 4.
- 15:80da: title logo pieces all at once (from 1400) or one per frame.
- 15:7cda (title logo zoom): steps 3, or 6 below 800.
- 15:7cda: logo reveal step 2 (above 900 with Detail > 1) or 4.
- 15:374c (launch, ship rise) and 15:0000 (landing):
  steps per frame for the fast class (from 1300 / 1400) or larger
  steps for slower machines.
- 15:302e: a warning text shown before the wave below 850, or below
  1600 on a display of fewer than 256 colours.
- 15:302e: after a wave, the outside-wave frame divisor is doubled
  (above 1500) or quadrupled (above 2000); it is rescaled by time
  within a second.
- 16:2144: dissolve uses one pattern below 300, four otherwise.

The slower-machine branches take bigger steps per frame because those
machines could not reach the target frame rate; at the full rate the
fast-class steps are the ones that keep the animations' speed in real
time. None of the branches touches flight physics, damage or scoring.

In-game speed controls (all kept): Alt + and Alt - change FrameRateSet
by 2 (4-104 frames a second; above 104 it becomes 1200, which turns
off the frame limit), saved to the INI and shown with B. Physics
advance a fixed amount per frame, so FrameRateSet is the game's speed:
a higher rate is a faster game, not a smoother one. Detail (INI, 1-3)
and GameSpeed (INI, overrides Calibrate for the in-wave divisor) are
the other two.

**Alternative for the user to decide:** a slower model machine (for
example 500 idle calls a second, Calibrate about 1150: the 800-1300
class) would take the medium branches (animation steps of 3 rather than 5
in the launch scene's ship rise, 15:374c; the title's logo pieces drawn
one per frame, 15:80da). Frames per second and the gameplay constants
would not change (all are above 380 and paced by time). The rate is
one constant (`pace_idle`, user.c).

## Silent fixes in the game code (`fix` entries in overrides/signatures.txt)

Memory-safety bugs of the 1994 code, fixed where the translator applies
the overrides; `src/inspace/` is unchanged.

- **Dissolve pixel maps (7:13b2, 7:158e).** Each of the 4 dissolves at
  DS:221c marks the pixels it has drawn in an 80-byte map (640 pixels),
  but a 30x30 icon at zoom 1x has 900. The extra bits overwrote the
  record's type, idx, r, sq and count and the next record; a corrupted
  type then indexed the per-type record table out of range, which
  crashed the port when the first icon dissolved in a wave. Each
  dissolve now has its own 2 KB map. At zoom 2x the maps never
  overflowed, so play there is unchanged; at 1x a dissolve now ends after
  exactly its pixels instead of with whatever the corrupted fields said.
- **Sparkle bursts (7:5e04).** A burst's last frame (its counter 54,
  q = 6) takes its source column from `tbl[6]`, one past the six-entry
  table. In the 1994 stack frame that word is the local k (bp-10), set
  only by the sub-game's loop (4 after it), stack garbage otherwise; the
  frame drawn from the sparkle bitmap was then arbitrary. The port reads
  k as the original did, 0 where the original had garbage (found by
  AddressSanitizer in a wave).
- **Tethers (8:1e32).** Breaking a tether clears the far end's link
  through the tether record's type and index; when another routine
  (11:947a, 12:3778, 12:3498) had already released the record (type -1),
  1994 wrote through `g_1df8[-1]`, the far pointer 0000:0078 made of
  DS:1df4-1df6 (the calibration word g_1df4 and a zero): a null selector,
  a general protection fault. The port skips that write (found by
  AddressSanitizer while flying in a wave, through the rock records of
  the next item, whose link 0 pointed at tether record 0).
- **Tether forces (8:1e32)** divide by both objects' masses. In a wave
  (flying and shooting rocks) records 44-46 of the rocks (type 3) had
  mass 0 and a tether link of 0 rather than -1, so they were treated as
  tethered to object 0 of type 0, and the division faulted (found by
  AddressSanitizer). A zero mass now gives no force. [uncertain: whether
  1994 could reach this state (a divide fault there) or the port missed
  setting the records up: the wave's set-up (9:6624) sets the links to
  -1 for the records counted then (g_92ec, from 9:22b4); which routine
  made these three is not found yet.]
- **Object record blocks (REC_70).** Not a 1994 bug but the native
  layout: the records hold far function pointers and are 124 bytes here,
  0x70 in 1994, yet their blocks were allocated and grown as counts of
  0x70 (6:1b62, 18:1dd0, and the GlobalReAlloc calls of 7:2768, 7:570a,
  7:5090, 9:4896, 9:22b4, 11:7c12, 12:2db6, 13:1318, 14:0000, 18:1eac,
  18:66e0). Growing with GMEM_ZEROINIT cleared from the 1994 end of the
  last record, inside the native records: summoning a ship (13:ae68 ->
  14:0000) after the ship count had shrunk cleared the function pointers
  of ship 1, and the radar (11:33cc) called a null pointer (found with
  the secret codes in a wave, AddressSanitizer and a watchpoint). The
  blocks are now sized in native records (`sizeof *g_1df8[0]`), so the
  zeroed part is exactly the 1994 one. [uncertain: the rocks of mass 0
  and link 0 of the tether fix above may have been this as well.]
- **Empty directory paths (6:4368, 6:420a, 6:4190, 6:4748).**
  `path[lstrlen(path) - 1]` read the byte before the buffer when the path
  was empty; that byte was almost never `\`, so a `\` was appended. The
  port appends it for an empty path.

## Far pointers and save files

- **Function pointers in `REC_70`.** The far function pointers at +5e/+62/+66 make `REC_70` 124 bytes natively instead of 0x70. Any code that sizes these blocks as 0x70, copies them as raw bytes, or reads them from a file must be checked. Every other record type is pointer-free, so its native layout equals the original.
- **Save files.** fn_06_9e66 and fn_14_4006 write and read whole GlobalAlloc blocks with `_lwrite`/`_lread`. These are the REC_SAVE block, `g_6e24` (REC_7C), `g_69f4` (REC_297), `g_6e1c`, `g_6e20`, `g_6afc` and REC_1A9 records. All are pointer-free, but they still need explicit serialisation of the original byte format, because their sizes come from `GlobalSize`.
- **Far-pointer arithmetic.** About 93 casts turn a far pointer into an integer, and 17 go the other way. These are segment:offset arithmetic and `(long)ptr` comparisons. Each must become plain pointer arithmetic.
- **`huge` and `_lread`/`_lwrite` sizes.** `huge` is dropped. The 0x7fff-byte chunking in fn_06_9e66 is harmless natively.
- **Runtime types that differ natively.** `time()`, `stat()` and `utime()` use the host's runtime types. The original's `time_t` was 32 bits; check any place that stores these values in 32-bit globals.

## ISPACE.DLL (port/src/win/ispace*.c)

Native versions of the DLL's routines, written from its disassembly
(ISPACE.DLL unpacked with tools/optl_unpack.py).

- **Palette manager signature.** Ordinal 4 takes seven words, the mode
  last. Most callers pass words 5-6 as one long, seg10's `FP7I` casts pass
  seven ints, so `g_fp_3c50` is declared with seven ints
  (`port/overrides/signatures.txt`) and the translator splits the longs
  (high word first: the pointer is pascal). 10:6ea0 passes an unsigned,
  zero-extended to a long in 1994: a `call` override passes `0, a`.
  Translator fixes for this: `call` overrides can name a function-pointer
  global, pascal is read from a pointer's declaration, and a constant long
  split for a pascal callee gives `hi, lo` (it gave a broken argument list).
- **Colour sets.** 5:5846 fills two tables of colour ramps (18 sets of ten
  and of five colours) at every mode 0; the port has the result as
  constant tables. Set 12 ("the image's own colours") is written only by
  an image-loader branch not ported yet; it will then need to be state.
- **DLL bugs, fixed silently (memory safety):**
  - A palette handle that is not one of the manager's (or 0, which finds a
    free slot) indexes the slot tables at slot 3 (DS:1cd6 + 6 is the colour
    table at DS:1cdc; mode 1 writes the kind over the ALPHABET handle) or
    works on an unallocated slot. The port ignores the call.
  - 5:61b2 (colour set into the palette) reads an uninitialised local as
    the colour set for set ids other than 3 and 5-13 (the game passes only
    those). The port loads no colours for them.
  - 5:4378 restores an uninitialised palette handle when the slot has no
    palette; ordinal 1 returns an uninitialised handle for image id 0;
    ordinal 6 sizes the mask from an uninitialised BITMAP when GetObject
    fails. The port uses 0 / gives no bitmap.
  - Image data is checked against the resource size (the DLL trusts it).
- **Quirks kept:**
  - Mode 6 returns -1 both when no entry is free and when a near colour
    (all channels within 3) is already there; it does not return that
    entry. Entries 10 and 245 are never given out.
  - Mode 1 with n = -1000 (white) and the black fills change only the DLL's
    copy; the screen palette changes at the next mode 3 (or mode 4, 5, 7).
  - 5:61b2 and mode 1 store a colour set's range as byte offsets, mode 1
    counted from the palette header, 5:61b2 from the first entry (one entry
    apart).
- **Uncertain:** `CreateDIBitmap` with DIB_RGB_COLORS takes the nearest
  entry of the DC's logical palette (squared RGB distance, first one on a
  tie). Windows 3.1's exact metric and tie rule are not verified; images
  loaded in mode 3 (all 16-colour game images so far) depend on it.
- **Ordinal 36 (10:2e1a, 2x / mirrored blit).** Used by fn_10_9962 when
  BadVideo is set (the default) for exact 2x stretches and negative sizes.
  It copies the source rectangle, makes a doubled and/or mirrored copy
  through an 8-bit DIB (5:0062, 5:0106; GetDIBits and back is the identity
  on palette indices, so the port works on the indices) and blits it. The
  palette it selects is slot DS:1f92's, which ordinal 10's dialogs
  (10:42c6) set; slot 0 before any.
  - **Quirk kept:** a copy both doubled and mirrored horizontally is one
    column off (each pixel's right half lands one column right, column 0
    stays black, the last column spills into the row padding or the next
    row). Nothing seen so far draws one.
  - **Fixed silently:** a source width of 0 (divide by zero in the DLL)
    draws nothing; the spill past the last row goes into a spare row.
- **Image loader mode 0 (5:26a2).** Mode 0 puts the image's colours in
  the palette: colours 0-9 as a ramp of 28 entries from 185 (three steps
  from each colour to the next), 10-14 as 17 entries from 213 (four
  steps); a fixed palette (mode 0's fourth word 1) would use entries
  10/83 and 8/7 steps, recolouring (DS:1ea4) one step each from entries
  170/180, both groups always. A group whose colour set is the image's own (12)
  gets its ramp only when its colours get darker one after the other
  (DS:1eaa, DS:1eac, read by ordinal 12). Sets 4 and -1 put colours 1-15
  in one after the other from entry 230. Mode 1 and the 16-colour palette
  of the image (DS:1178, DS:1eae, 5:39f6, 5:3a68) are not modelled; no
  ported routine reads them. Ordinal 1 reaches mode 0 for
  recolouring (c < -100: the dialogs' ship pictures, 5:0000, checked
  against the DLL with the oracle), id -2 and id 0x28a (not used so
  far, not checked).
- **Ordinal 12 (6:00c4, 7:12d8; ispace_smooth.c).** The title's logo and
  the "Enhance" ship pictures (seg15b). The image (16 colours, colour 15
  the background) is loaded with mode 0 and drawn at twice its size,
  each pixel a 2x2 block, colours 0-9 and 10-14 as two groups:
  - Each group has ramps of palette entries (7:4ee8, ranges at DS:1108
    and DS:1ca4). A colour set other than 12, or a ramp the loader made
    (DS:1eaa/1eac), gives one ramp over the group's area; set 12 gives one
    ramp per run of colours of the same hue (5:66ea), filled from that
    hue's colour set (ids 3-13 map to sets as in 5:61b2).
  - Per colour a lightness: 6:7f52, three Newton steps of the square
    root of the mean square of red x 3/4, green, blue x 5/8 (palette
    entries: blue x 1/2), started from the mean. ispace_lum and
    ispace_lum_image.
  - Pass 2 (colours 0-9) and 3 (10-14) draw each block at half its
    colour's lightness (3/4 with the mode word 1) into their own plane,
    add a quarter (or half) at corners touching the other group and a
    quarter into the facing cells of neighbouring blocks of the same
    group; a code plane keeps the block's ramp and group. Each plane is
    blurred into a final plane (3/4 of the cell plus 1/16 of each
    diagonal neighbour, or of the cell itself where that is 20 or
    less), corners where two blocks of the other group meet are cut
    (taking that group's neighbouring cell), and each cell gets the
    entry of its ramp nearest its lightness (5:6b72), entry 245 when
    darker than the ramp, 0 when unlit.
  - The result (2n x 2n for an n x n image) is stretched to the asked
    size with COLORONCOLOR; negative sizes are multiples of the image
    height.
  - **Verified** against the DLL's own code run under Unicorn
    (`tools/dll_oracle`, a test tool, not part of the port; its
    `smooth.txt` keeps 21 of these calls): the game's ISPACE calls up to
    the title replayed on the emulated DLL, then ordinal 12 compared
    pixel for pixel and palette entry for entry: the title call, and 107
    more (every 16-colour image of IGRAPHIC.DLL and ISPACE.DLL with random
    colour sets and both shading modes) in one sequence. All identical
    except the two noted below. 5:66ea was compared for all 2^24
    colours.
  - **Quirks kept:** columns run up to the image's height, not its width
    (the images used are square); the mode word only lightens with 1
    (its switch sets the corner shift 3 for mode 1, then falls through to
    2); the corner cut looks at the diagonal block on the other side
    (below-left for the top-left corner); codes of taken cells wrap as
    bytes; colour set 0xff in either word returns 0 (6:00c4).
  - **Fixed silently (memory safety):** an image taller than wide is
    read past its pixels by the DLL (the port reads that as background;
    images 200 and 260 differ from the DLL in their top rows); a ramp
    index outside the tables (possible only after wrapped codes, never
    seen) gives entry 0; a ramp whose ends are equally light (the DLL
    divides by zero) starts its search at its last entry; set ids 14-99
    (an uninitialised word in 7:4ee8) give no ramp; palettes that are
    not the manager's and images that are not 4-bit give no bitmap.
  - DS:1ccc, the angles of ordinal 2's last surface, makes the bitmap
    that many times wider again unless c is 0 (checked with the oracle,
    surfaces.txt). The ramp tables (DS:1108, DS:1ca4) are shared with
    ordinal 2.
  - **Not modelled:** DS:1e80-1e84 (per-palette colour sets, written
    only), the per-row callback 9:360a (DS:21aa/2222/1738, set by the sound
    ordinals, which are stubs); 5:6f58 (colour set to id), whose results
    7:12d8 stores but never reads.

## ISPACE.DLL rooms (ordinal 32; port/src/win/ispace_room.c, ispace_shape.c)

Ordinal 32 (8:0000) draws a room of IGRAPHIC.DLL (resource type 6600:
100 the desk, 105 inside the computer, 110 and 115 pentagram halls, 120)
into a new bitmap and returns the rectangles the game draws into (the
monitor's screen, the tower, ...). The format and the view are described
in ispace_room.h.

- **Loading (8:5b76).** The DLL copies the header (0x6c bytes) into a
  block and the rest of the resource from GlobalSize of that block on:
  Windows gives 0x80, and the rooms are laid out for it (objects start at
  0x80). The object count comes from the rounded size of the second
  block (the slack is zero; it reads as an empty object of type 0).
- **Layout (8:0a36).** Passes over the objects until one places none: an
  object is placed once its parent (and a line's second reference) is.
  Positions and sizes are thousandths of what their mode names (the
  parent's extent, the room's width, or the parent's words from its size
  on: mode 4 reads the parent's first position mode [sic]); modes 6 and
  up are screen units turned into world units at the object's depth. Then
  each colour ramp of the header becomes palette entries (5:3dee, from
  the first black entry found by 5:4292) and the palette goes to the
  screen (5:4378).
- **Drawing (8:15ec).** In the room's order (8:1b66 sets the identity
  order; its sort, 8:1c14, is never reached): boxes (8:28de: lid or
  bottom, the side facing the middle, then the front; vents (8:28de
  side loops), slots, a black screen inset, textures METAL and image 76,
  text and the "HIGH VOLTAGE" sign, the monitor and tower fronts as the
  game's rectangles), lines (8:5470, 8:5632), upright cylinders (8:3874,
  with the batteries' "+"), flat points (type 4, 8:50ec). Faces are
  filled in bands with wedges along slanted edges (8:1fe6); every band is
  shaded by the floor's distance below the horizon (8:27f0 picks the
  ramp's entry).
- **System information (8:5c86).** The desk's computer can show the
  display and sound drivers (SYSTEM.INI, CONTROL.INI), the network card
  (PROTOCOL.INI, NETWORK.INF), the processor; objects can depend on a
  386 coprocessor, a 486, a wave device or stereo. The port's answers:
  no INI files (defaults "Video Card", "Sound Card", no network), a 486
  with a coprocessor (GetWinFlags), one stereo wave device. Room 100
  shows none of it.
- **Verified** against the DLL with the oracle (tools/dll_oracle,
  rooms.txt): the one ordinal 32 call the game makes up to the
  navigation window (room 100 at 640x480, captured from a run), room 120,
  and room 100 with other vanishing points, lifts and sizes: bitmaps,
  palettes and rectangles identical.
- **Not ported:** object type 5 (8:4206, a ring or disc; rooms 110 and
  115 draw it and are not identical yet; they are not reached before the
  navigation window); rooms in the caller's memory (id -1, unused by the
  game); the paths for displays of fewer than 256 colours. Room 105's
  two fronts with texture 120 stay black: ordinal 1 does not load image
  76 (its VGA colours, 6:7fc8, are not ported).
- **Quirks kept:** a box size of mode 0 is the parent's width on all
  three axes; object 2 is lifted (word 14) only when its rectangle byte
  is -20; the 12th and 13th words set the vanishing point's y and x (the
  game's thunk calls them x and y); textures other than 100 and 120 use
  an uninitialised bitmap (none here: 0).
- **Fixed silently (memory safety, divide faults):** a zero divisor (a
  divide fault in the DLL) gives 0; parent indexes outside the room and
  modes outside 0-10 are not followed (the DLL reads outside the object
  table); a box's text with an id of 0 or 1 is empty (the DLL draws an
  uninitialised buffer); cylinders and points without a colour ramp
  (the DLL reads before its ramp tables) and kinds of text not 1-3 (an
  uninitialised font size) are not drawn; header bytes past 0x6c read 0.
- **Uncertain (GDI, not checked by the oracle, which draws as the port
  does):** lines are drawn with pens 2 pixels wide, which the port draws
  1 pixel wide (wide pens are not modelled); the wedges along slanted
  edges are PatBlts of negative width, which the port fills from x + w +
  1 to x; the text of room 105 goes through text.c.
- **Rectangles block.** The DLL grows the game's locked block
  (GlobalReAlloc) and writes the rectangles through the new pointer; the
  game keeps its old pointer (in Win16 the selector stays). kernel.c
  keeps a block's address when it grows within its slack, which covers
  the five rectangles of room 100.

## ISPACE.DLL panel helpers (ordinals 33-35; port/src/win/ispace_panel.c)

- **Ordinal 33 (8:037a):** text in the ALPHABET bitmap (18x20 glyphs:
  letters, digits from glyph 35, `/ ( ) : ! ? , . - % \`), each glyph
  stretched to the asked size and ANDed with a solid brush of the colour
  (MERGECOPY); space and `_` are black, other characters are skipped.
  The game's thunk passed the string as a long; `fn_10_94c4` and
  `g_fp_3c74` now take a `char *` (port/overrides/signatures.txt).
- **Ordinal 34 (8:05ac):** a box: kind 0 black with a grey shadow, 1 and
  2 light grey raised (2 with a grey bottom edge), 3 sunken. Other kinds
  leave the DLL's brush unset: the port draws nothing.
- **Ordinal 35 (8:0768):** a gauge: sunken frame, black empty part,
  green full part with yellow and dark green edges.
- **Verified** with the oracle (panel.txt): all identical.

## GDI (port/src/win/draw.c)

- **Blits within one bitmap** read the source as it was before the blit,
  however source and destination overlap, as Windows' BitBlt does. A
  burning icon in a wave (7:477e, then 7:4d86 each frame) melts by
  copying narrow columns of its pane a row or two down onto themselves,
  in the icon sheet and in its five burning frames. Drawn row by row
  from the top, each copied row was copied again, so every column
  touched became the black border above the pane, and within a second
  the icon (and the panel's target picture of it) was a few red stripes.
  The oracle's stand-in (tools/dll_oracle/emu.py) reads the same way.
  [uncertain: whether Windows 3.1's StretchBlt did so too for an
  overlapping stretch, as 7:3a42's shrinking icon has.]

## Text (port/src/win/text.c)

- **Fonts.** Liberation Sans for Arial (and every other face, including
  "Small Fonts" and the stock font), Liberation Serif for Times New Roman;
  bold for weights above 550 (the game asks for 0, 500, 520, 600, 730 and
  800; Windows picks the nearer of the regular and bold faces), italic from
  the italic file. The stock font (height 0) is drawn 16 pixels high
  [uncertain].
- **Metrics** follow Windows' TrueType rules: a positive height is the cell
  (win ascent + descent scaled to it), a negative one the em; a width sets
  the average character width. The average width is the old OS/2
  definition (weighted a-z and space): Liberation's own xAvgCharWidth is
  computed over all glyphs (1187 units against Arial's 904); the weighted
  one gives 904 for Sans, 980 for Sans Bold (Arial Bold: 983). Advances are
  the unhinted widths rounded; `GetTextExtent` and drawing use the same
  ones. No kerning (Windows 3.1 had none).
- **Uncertain, not pixel-exact:** Windows 3.1 hinted Arial and used its
  hdmx widths; the port rasterises unhinted outlines and inks a pixel at
  50% coverage, so glyph shapes and some advances differ by a pixel from
  the original. tmFirstChar/LastChar/DefaultChar are guesses (the game
  reads only tmHeight and tmExternalLeading).

## Windows, input and dialogs (port/src/win/user.c, input.c, dialog.c, controls.c)

- **Dialogs keep what they cover.** The dialog class has CS_SAVEBITS:
  while a dialog is shown the screen under it is kept, and when it goes
  it is put back instead of being repainted (drawing under a shown
  dialog is clipped, so the copy stays right; a dialog that moves loses
  it). Without this, the area of the New Game dialog was erased black by
  the next WM_PAINT after the desk was drawn (the game does not repaint
  the desk) [uncertain: when Windows 3.1 discards saved bits].
- **Windows.** Top-level windows stack in the order they are made (a
  dialog above the game window); a window DC does not draw where a
  visible popup above its window lies, so the game drawing on timers
  while a dialog is up does not cover it. Children are clipped to their
  parents and repainted where their parent is (no WS_CLIPCHILDREN). What
  a window uncovers when it goes away or moves is repainted (erased with
  the class brush first), as in Windows. Showing the game window
  activates it and gives it the focus (WM_SETFOCUS), as in Windows.
- **Keyboard.** US layout. Alt makes WM_SYSKEYDOWN/WM_SYSCHAR, so the
  game's Alt accelerators (MainAccel: Alt-X exit, Alt-G, ...) arrive as in
  Windows; Alt-X opens the exit question (ordinal 10 mode 5).
- **Dialog look** (Windows 3.1 default colours; sizes partly
  [uncertain]): dialog units from the dialog font (DS_SETFONT "Helv" 8,
  mapped to Liberation Sans at 11 pixels) as the letters' average width,
  rounded, and the font height [uncertain: Windows 3.1's own rule;
  tmAveCharWidth would give 5 instead of 6, and the Restore Game labels
  would not fit]. Frame 4 pixels, caption 19 (title in Liberation Sans
  Bold standing in for the System font), push buttons with a 1-pixel
  highlight and 2-pixel shadow, combo box field the font height + 6 with
  a 17-pixel arrow button, drop-down list of whole items with a scroll
  bar when they do not fit (arrow buttons, a square thumb; clicks on it
  scroll a line or a page, the thumb is not dragged). The focus rectangle
  inverts every other pixel (those whose coordinates add up to an even
  number [uncertain: the phase of Windows' gray pattern]). Stock
  DKGRAY_BRUSH is a checkerboard of black and dark gray (entry 248), as
  an 8-bit display dithers RGB(64, 64, 64) [uncertain: which colour is at
  the origin]; other RGB brushes are not dithered. Not modelled: list
  scroll bars elsewhere, icons in statics. At 14 pixels some glyphs lose
  detail (the colon's upper dot), see "Text".
- **Edit controls** (edit.c): single-line ones are edited as in Windows
  3.1: caret one pixel wide [uncertain] and a line high, inverted,
  blinking every 530 ms; selection with Shift and the arrows, Home, End,
  or the mouse, shown only while focused; typing replaces it; Delete,
  Backspace; EM_GETSEL/EM_SETSEL/EM_LIMITTEXT (default 30000, and the
  window text's 255); EN_UPDATE, EN_CHANGE, EN_MAXTEXT (with a beep),
  EN_SETFOCUS, EN_KILLFOCUS; scrolled sideways one character at a time
  to keep the caret in view [uncertain: Windows scrolls further], also
  without ES_AUTOHSCROLL. The dialog selects all of an edit's text when
  it gives it the focus (Tab, mnemonic, first control). Text starts at
  (1, 1) inside the border. No clipboard, undo, double-click word
  selection or multi-line editing (multi-line ones only show their
  text).
- **Uncertain:** CB_FINDSTRING with an empty string finds item 0 (the
  Restore Game dialog relies on it while INI Restore is unset).
- **Messages with pointers** (CB_ADDSTRING, LB_GETTEXT, WM_DRAWITEM, ...)
  carry native pointers in the pointer-sized lParam ("How it works").
  The native DLL code calls `combo_*` (user.h) directly; WM_SETTEXT is
  sent after SetWindowText has stored the text.

## Menus and scroll bars (port/src/win/menu.c, scrollbar.c)

- **What the game has.** MENU resources of ENG_LANG.DLL (read at run
  time): 101 (the menu bar: Game, Ship Cmds, Defenders, Watch, Help), 102
  (the same with Strategy, when DS:9134 is set), 110 (Ship Factory's,
  unused by INSPACE.EXE) and POPUPMENU (Options Menu, Game Options.., Exit
  Game), the right-button menu in a wave (2:134c, TrackPopupMenu).
  System menus: IS_ICON (7:6184) and IS_SMART (13:613a) append "1/2x
  Scale" (0xf0, ModifyMenu checks it); the main window appends "&Main
  Menus" (0x60, the menu bar on/off) when it is restored to a window
  (2:0d78 SC_RESTORE, after a double click toggles full screen, 2:1046).
  2:170e grays menu items by position after game-state changes. The game
  handles none of WM_INITMENU, WM_INITMENUPOPUP, WM_MENUSELECT; menu and
  accelerator commands arrive as WM_COMMAND (2:13b2) and WM_SYSCOMMAND
  (2:0d78). One scroll bar: the radar zoom (11:3790, `scrollbar` child
  200, range 100-500, position 600 - DS:0a6c), whose WM_VSCROLL 11:7798
  handles: SB_LINEUP/DOWN 20 steps, SB_TOP/BOTTOM, SB_THUMBTRACK and
  SB_THUMBPOSITION; page clicks do nothing. Created only when DS:094e is
  0.
- **INI `Menu`.** Both reads (6:0000, 6:0a6c) default to 0 and 6:033e
  writes the current state back at exit, so a first run has no menu bar,
  as the port's default is. The help file: "Turn on Game Menu ... Press
  the 'Display..' button on the Game Settings dialog" (ordinal 10 mode 0,
  not ported) or, windowed, the system menu's Main Menus.
- **The menu bar** is the main window's id (GWW_ID), as in Windows: the
  game turns it on and off with SetWindowWord + DrawMenuBar, which works
  out the client area again (18 pixels less, WM_SIZE; the game lays out
  again). A full-screen (WS_POPUP) window shows a bar too.
- **Menu loop** (modal, as Windows 3.1's): the game's idle loop stops
  while a menu is open (timers and painting go on). Mouse: a title opens
  its popup (clicking it again closes the menu), moving over titles with
  a popup open switches popups, release on an enabled item chooses it,
  a click outside ends the menu. Keyboard: Alt or F10 tapped alone (no
  other key between press and release; tracked in input.c as Windows
  tracks it at its input queue) selects the first title, Alt+letter opens
  the title with that mnemonic, Alt+Space the system menu; arrows, Enter,
  Esc (first closes the popup, then the menu), letters, Alt/F10 released
  end it. Grayed items can be selected, not chosen. Commands are posted
  after the loop: WM_COMMAND (id, 0), WM_SYSCOMMAND (id, mouse position
  or 0). Esc ends the menu on its key-down; its WM_KEYUP then reaches
  the game window, and the game acts on key-ups (Esc there asks to leave
  the wave), as it would under Windows [uncertain: not checked against
  Windows 3.1].
- **System menu**: Windows 3.1's (Restore, Move, Size, Minimize,
  Maximize, Close Alt+F4, Switch To... Ctrl+Esc), a copy per window with
  WS_SYSMENU made by GetSystemMenu; Restore always gray (no window is
  minimized or maximized in the port), Size/Minimize/Maximize gray
  without WS_THICKFRAME/MINIMIZEBOX/MAXIMIZEBOX. DefWindowProc's Move,
  Size, Minimize, Maximize, Restore and Switch To log and do nothing.
- **Look** [uncertain: sizes from Windows 3.1's metrics as far as known,
  the rest approximated]: System font (Liberation Sans Bold, as in
  captions); bar 18 pixels (SM_CYMENU) with a black line under it, titles
  6 pixels each side; popups with a black border, items 18 high, a 14
  pixel check mark column and right margin, separators 8 high with a
  line in the middle, accelerator texts in a column 14 pixels after the
  widest text; no drop shadow; selection in the highlight colours, gray
  text for grayed items. System menu box 18 pixels (SM_CXSIZE), a bar
  like a space bar, inverted while its menu is selected. Popups drop from
  the bar's bottom line (the caption's for the system menu) and are kept
  on the screen; they keep what they cover (CS_SAVEBITS) and are not
  activated.
- **Scroll bar** (vertical controls only; the game has no others):
  arrows as long as SM_CYVSCROLL (17, at most half the bar) and the
  thumb as long [uncertain: Windows 3.1 may scale both for a 14-pixel
  wide bar], thumb top = arrow + (pos - min) * (length - 2 arrows -
  thumb) / (max - min), rounded. A click is tracked in a loop of its own
  until release (the game waits, as under Windows 3.1): arrows and page
  areas send their code at once, again after 200 ms and every 50 ms
  while held and under the mouse [uncertain: Windows 3.1's delays];
  the thumb follows the mouse (SB_THUMBTRACK when the position changes,
  SB_THUMBPOSITION at release); SB_ENDSCROLL last. A held page area is
  inverted [uncertain]. The shaft is the parent's WM_CTLCOLOR
  (CTLCOLOR_SCROLLBAR) brush, COLOR_SCROLLBAR by default. Not modelled:
  the thumb snapping back when the mouse goes far from the bar, keyboard
  (the game's bar has no WS_TABSTOP, so it never has the focus).
- **Frames and activation** (user.c). Sizing borders (WS_THICKFRAME:
  IS_NAV, IS_ICON, IS_SMART, IS_WATCH, the windowed main window) are 4
  pixels (SM_CXFRAME [inferred: border width 3 plus 1]) in the border
  colour, with black marks across them 21 pixels in from each corner
  [uncertain]; captions are drawn in the inactive colours (white, black
  text) when the window is not the active one, and repainted when
  activation changes (WM_NCACTIVATE). ShowWindow with SW_SHOW or
  SW_SHOWNORMAL activates a top-level window, and when the active window
  is destroyed or hidden its owner (else the topmost other window) is
  activated, as in Windows; dialogs are now the active window while
  shown, which the game expects (2:11f8 excludes them from its pause
  test). Sizable and overlapped windows are kept within the tracking
  sizes their WM_GETMINMAXINFO gives when made, moved or sized
  (DefWindowProc's WM_WINDOWPOSCHANGING in Windows): IS_ICON and
  IS_SMART size themselves this way (their height from the number of
  pilots, half size with 1/2x Scale); the Navigation window is at least
  560x350; the windowed main window at least 600x400 in a wave, and
  otherwise fixed at its current size [uncertain: at creation its
  handler reads GetWindowRect of a window not yet made, 640x480 in the
  port]. Defaults: minimum 100x28 (SM_CXMINTRACK, SM_CYMINTRACK
  [uncertain]), maximum the screen plus the borders.
- **The dark-blue patch** at the top right of waves (x 592-640) was the
  IS_ICON pilot-icon window (INI `IconWnd`, default 1; `IconLeft`
  defaults to the screen width - 48, so 2 pixels are off the screen as
  in the original) drawn with an active caption, no system menu box, a
  1-pixel border and 50x150 instead of its own size. It is now drawn as
  Windows drew it: inactive (white) caption with the system menu box,
  sizing border, sized for its pilots.
- **Non-client mouse input.** Clicks and moves outside a window's
  client area (no capture) are WM_NCxxx messages with the hit-test code
  and screen coordinates, as in Windows; DefWindowProc opens menus for
  HTMENU and HTSYSMENU (SC_MOUSEMENU). Before, such clicks reached the
  window procedures as client messages with negative coordinates.
- **Game code, noted, not changed:** 2:0d78's case 0x60 (Main Menus)
  returns no value [sic]; the caller passes WM_SYSCOMMAND 0x60 to
  DefWindowProc when the leftover value is nonzero, which ignores it, so
  either way nothing more happens.

## ISPACE.DLL dialogs (port/src/win/ispace_dlg.c)

- **Ordinal 10 (9:145e)** keeps some of its words for the dialogs by mode
  and runs 10:42c6, which picks the palette slot (DS:1f92), makes the
  dialog fonts (9:29c0: Arial 14x6, regular and weight 730) and runs the
  mode's dialog from ENG_LANG.DLL. Ported: mode 1's Restore Game dialog
  (template 267; 10:0ec2 with 10:1438, 10:1a38, 10:1a80 for " NEW GAME",
  10:1d36) and New Game dialog (template 321, or 589 "New Demo" for mode
  4; 10:0f26 with 10:1e7c, 10:250c, 10:2978), their LevClass preview
  window (10:4250, 10:309c, 10:2c68, 10:2aac, 10:2d3c), the ship tables
  (10:3f70, 10:406a, freed by 10:4168), 10:602a (fonts for the
  controls), and modes 5/7, the exit question (template 244; 10:103c,
  10:109a). The language DLL handle (DS:0690, which ordinal 7's 9:0174
  loads) is loaded on first use.
- **Flow:** ESC on the title runs mode 1. OK with " NEW GAME" writes INI
  `Restore= NEW GAME` and ends with 1; then the New Game dialog. Cancel
  ends with 0; a saved game ends with 2 (its details, 10:1b13, are not
  ported). Modes other than 1, 4, 5, 7 and 15 log "not ported" and
  answer 0.
- **New Game dialog** (10:1e7c): zoom levels (strings 2230-2232, INI
  SetSize, default 1, picks item 2 - SetSize); the ships of MASTER.SHP
  with a name, not of type 7 and allowed (10:611c, below), sorted; the
  drives C-Z that `_chdrive` accepts, as "C: LABEL" (volume label, or
  "Unknown_HD"; INI Drive, default C, picks one); play modes ACTION and
  COMMAND (strings 2275, 2276; INI PlayMode); the pilot (INI ThePlayer,
  default "AutoPilot"); the ship of INI MainShip (default EAGLE), which
  becomes TRANSFORMER, written back, when it is of type 7 or not
  allowed, and is always TRANSFORMER in the limited version (word v0 of
  ordinal 10, DS:01aa: the game passes 1 when unregistered, 3 for its
  other mode); the team of the ship's type (INI [Teams] Team<type + 1>,
  empty here). Picking a ship shows it and its team (10:2978).
  - OK (10:250c): in the limited version any ship but TRANSFORMER gets
    message 2326-2327 and the dialog stays. Otherwise INI MainShip,
    Drive (the item's first letter), Size and SetSize (2 - item),
    ThePlayer (the edit's first 19 characters), PlayMode; with COMMAND,
    sound effects 0x6e and 0x2c (9:298c; no sound yet) and, while INI
    StratAsk is 0 or 10, question 2850-2853: No keeps the dialog, Yes
    writes StratAsk + 1. Mode 4's dialog writes only MainShip and Drive.
    The dialog ends with 1 (OK) or 0 (Cancel).
  - The preview (10:2aac, 5:0000): the body's image (MASTER.BOD +0x21,
    or the file +0x23 when negative) with the ship's colour sets (+7,
    +8) put in the palette as one-step ramps from entry 170 (colours
    0-9) and 180 (10-14) (ordinal 1 recolouring, 5:26a2 mode 0; modes
    1 and 2 of 5:0000 shift them by 60 and -12 bytes), drawn at twice its
    height in the middle of the 96-pixel window (10:2d3c: ordinal 36 when
    BadVideo is set, as here, else StretchBlt). Verified against the DLL
    with the oracle (tools/dll_oracle/ships.py): every ship of MASTER.SHP
    in mode 0 and some in modes 1 and 2, bitmaps and palettes identical.
  - **Quirk kept:** Esc does nothing in the Restore and New Game
    dialogs: their Cancel buttons are id 333, not IDCANCEL, which Esc
    sends. Alt+C (the button's mnemonic) cancels.
  - **Quirk kept:** the TEAM text (a static 96 units wide) runs under
    the preview window; setting it repaints its rectangle in the dialog
    colour over the preview (Windows paints overlapping siblings that
    way too), leaving a white patch at the preview's left edge after a
    ship is picked [uncertain: depends on the dialog units, which are
    uncertain].
- **Registration (10:611c, ordinal 24 = 10:48d2, ispace_reg.c).** The
  dialog offers all ships only to a registered copy; the game asks
  ordinal 24 the same (10:885e, 10:946a). Ported modes: 21 (a CD in the
  drive of WIN.INI CDDrive: the port has no CD drive, so 1), 2 (10:4f9c:
  the key, resource 5500/110 of <LocalPath>\INSPACE.EXE, against the
  serial number of its disk (10:4440, int 21h 440Dh through DPMI: none
  in the port, 0, as when the call fails), else WIN.INI [windows] PDev
  less SYSTEM.INI [386Enh] vidsp against key % 653 + 654 (10:51b6)), 10
  (10:4c68: the registered name, resource 5000/143, xor "*2-"). With the
  user's files the key is 0x1234 and nothing sets PDev, so the copy is
  unregistered: the title says "limited inner space" and counts the
  demo days, the New Game dialog forces TRANSFORMER and leaves out the
  ships whose bodies are images 178, 310, 320, 400, 440, 450, 520, 550,
  560, 590, 600, 604, 605, 710, 720, 730, 750, 890, 900, 930 and 950.
  This is the original's behaviour with these files. The port runs it
  only with the setting `[Port] CopyCheck=1` (port/README.md); by default
  mode 2 answers 0, a registered copy, so nothing has to be put in the
  Windows folder (Android users have none). Mode 10 still reads the
  name (" - " in the user's INSPACE.EXE). With the check on, WIN.INI
  (settings folder) [windows] PDev=743 makes this copy registered, as the
  original on Windows NT [inferred: what the installer writes there]. The flag is cached in
  DS:01ac, which palette mode 0 also writes (a palette handle) when its
  second word is set; the game never sets it.
- **Not modelled:** the date of mode 15 is stored but not used yet;
  LocalPath and ShipPath are read from the INI when used (the DLL reads
  LocalPath once, in 10:4b1c).
- **DLL bugs, fixed silently (memory safety):**
  - 10:3f70/10:406a: when reading MASTER.BOD/SHP fails the DLL frees the
    block but keeps its pointer (10:4168 frees it again) and leaves the
    file open; the port drops the data and closes the file.
  - 10:1438 cuts ".SAV" by writing before the name if it is shorter than
    4 characters (impossible for *.SAV matches); the port stops there.
  - 10:42c6 uses slot 3 (DS:1cd6 + 6, inside the colour table) when the
    palette passed is not one of the manager's; the port uses no palette
    (ordinal 36: slot 0).
  - Ordinal 10 modes 10 and 13 return whatever AX holds; the port 0.
  - A ship whose body index is outside MASTER.BOD makes the DLL read
    past the table; the port shows no picture and lets it be played. A
    failed read leaves no ships (the DLL keeps the count).
  - 10:2d3c divides by the source width when the destination is
    mirrored; a width of 0 takes the StretchBlt path.
  - 10:250c builds its messages in fixed buffers (150 and 250 bytes)
    with lstrcat; the port bounds them (the shipped strings fit).
  - 10:250c writes the drive's first letter from an uninitialised buffer
    when the drive list is empty; the port writes an empty Drive (the
    port always lists C).
- **Quirk kept:** a ship file's length is divided as its low word,
  sign-extended (files of 32 KB or more give no records).

## Inner Space Navigation (seg06d; dosfs.c, listbox.c, icon.c)

The directory picker is the game's own code (6:1c72 opens the IS_NAV
window, 6:23d4 makes its controls, 6:37ca fills the directory tree,
6:5318 and 6:5524 the program list and the description, 6:4368 the icon
box, 6:301a enters the directory). It runs on the native list box,
group box, icons and the drive mapping of port/README.md ("Drives and
file names"). Enter (IDOK through IsDialogMessage) or a double click
on a directory with programs leads to the wave's briefing.

- **List boxes** (listbox.c):
  - **Uncertain:** sorted insertion compares ignoring ASCII case
    (Windows 3.1 used its language collation); LBN_SELCHANGE is sent when
    the mouse button is released; a horizontal arrow click scrolls 8
    pixels; the default column width of a multi-column list is 16
    average characters (the game sets its own); an owner-drawn item's
    rectangle is as wide as the horizontal extent when that is wider.
  - Every change repaints the whole control, each item with
    ODA_DRAWENTIRE, where Windows sends ODA_SELECT and ODA_FOCUS for the
    items that changed; the game's handlers (6:47e8, 6:4e04, 6:4ea8) draw
    the same pixels either way.
  - Not modelled: multiple selection (the program list is
    LBS_EXTENDEDSEL; it selects one item at a time), dragging the thumb.
- **Group boxes** (controls.c): frame from half the text height,
  text at 9 pixels on the control's background [uncertain: Windows 3.1's
  offsets]. The navigation window shows them only for race tracks and
  the duel arena.
- **Icons** (icon.c):
  - ExtractIcon returns the number of icon groups for index -1; for an
    index, the icon, 0 when the program has none of that index, and 1
    when the file is not a Windows program (NE or PE) or cannot be read,
    as Windows documents it. The game counts a program without icons as
    one icon and draws its own picture for it (9:0352).
  - **Inferred:** of a group's images the 32x32 one is taken, else the
    nearest size (larger first, scaled to 32x32); among those, the most
    colours up to 256, else the fewest above. Colours go to the nearest of
    the 20 static colours (plain RGB through the DC), as Windows 3.1 made
    icons with the default palette; 16-colour icons are exact. 32-bit
    images with alpha use it as the mask (Windows 3.1 had none); PNG
    images are not read.
  - Resource tables of the user's files are read with every offset
    checked (they are not the game's files).
- **Directory searches** (crt.c): DOS keeps a search in find_t's
  reserved bytes; the port keeps a snapshot of the matches per search
  (64, the oldest reused) and names it there. The game starts searches
  it never finishes (6:4190 only asks whether a `*.exe` exists); with
  the earlier 4 slots kept until a search ended, these could take the
  slot of the tree's own search (DS:69f8).
- **Not ported yet, met after Navigation:** ISPACE ordinal 1's branch
  5:075e (logs as a stub on the way to the briefing). Ordinal 2's
  surfaces (6:011c), met there too, and ordinals 14 and 18, met in the
  launch scene, are ported (below).

## ISPACE.DLL in the launch scene and the wave (ordinals 14, 18, 29)

- **Ordinal 14 (5:50cc; ispace_pal.c `ispace_pal_scale`).** Scales the
  colours of one group of game entries to a percentage of themselves
  (at most 255) in the DLL's copy of the palette and shows it: kind 3
  the ramps (entries 185-229, DS:0178-0180), any other kind the image
  colours (230-245). Called by the launch scene through 10:993a (the
  decomp's comment on 15:0000 calls it a sound pitch, which it is not),
  96-99 % per frame, so the ramps fade step by step. The fixed-palette
  path (5:5268, colour sets blended through DS:1e80/DS:1f2a) is not
  ported: this game never makes a fixed palette (it logs if met).
  Verified with the oracle on the calls of a run up to the wave
  (tools/dll_oracle/wave.txt) and percentages 0-400: palettes identical.
- **Ordinal 18 (6:5e76; ispace_sprite.c).** Image 280 (an 18 x 18 shaded
  ball) turned to n angles (5, a quarter turn in 22.5-degree steps:
  DS:00f6/0108, sine and minus cosine x 512, rounded half away from zero,
  each angle shifted by a pixel or two, bp-15a), side by side; single
  gaps in a row are closed with the colour on their left. Kind 1 (the
  launch scene, 10:7032 with b = 1): loaded in mode 0 with sets 4/-1 (the
  colours go to entries 230-245), each colour mapped to the nearest of
  those entries (5:4e96: sum of channel differences, the first below 14
  wins), full size. Kind 0 (the sheet the wave's sprites are cut from,
  10:5c42): loaded in mode 1 (the image's own colours, DS:1178, 5:39f6),
  each 2 x 2 block averaged in RGB to half size; blocks with a channel
  above 0x32 get the nearest entry of colour set 1's range (5:64f8, which
  keeps its last answer in DS:01a6 when it has nothing to search), the
  top half of the bitmap; the bottom half has the same entries moved
  into colour set 0's range (linear between the ranges' first entries).
  The fourth word swaps red and blue (DS:1ea6) as the colours go into
  the palette.
  - **Quirk kept:** rows run up to the image's width and columns up to
    its height (the image is square).
  - **Fixed silently (memory safety):** a palette not the manager's, n
    outside 1-5 (the DLL reads other locals as the shifts), an image not
    4-bit, writes outside the sheet, and colour sets without a range (the
    DLL reads before its range table) or an empty range (divide fault)
    give no bitmap, nothing, or entry 0.
  - **Not ported:** the 4-bit and 1-bit display paths (7:08e6, the
    dithered 16-colour path 6:71f6) and fixed palettes (6:773c; logs).
  - **Verified** with the oracle: the two calls of a run (kinds 1 and 0)
    and six variations (n 1-5, both swaps): bitmaps and palettes
    identical.
- **Ordinal 29 (2:003c; ispace_collide.c).** Two round objects meeting
  [inferred: the game's collision response; called by 8:546c, 8:6f3c,
  8:3688 and 18:403e for ships, shots and rocks]: velocities, positions, sizes and masses
  in; it works in tenths with the runtime's 32-bit helpers (3:00fe,
  3:0130) and keeps their truncation. When the objects move apart
  (positive closing speed along the line between them) every velocity
  word grows a step (x2 below 3, x4/3 below 7, x7/6 below 11, else
  x11/10) and it returns 0. Otherwise object 1 is moved back by the time
  the gap along the nearer axis needs to close, the velocities along the
  line between the centres are exchanged as an elastic collision of the
  masses, and half of each one's change of speed goes to the two result
  words (damage); it returns 1. Nearly still objects (both velocity
  differences 4 or less) first get object 2's velocity less half a unit
  along the line. Length (2:0850): one Newton step from the larger
  component plus half the smaller.
  - **Fixed silently:** divisions by zero (divide faults in the DLL) give
    0.
  - **Verified** with the oracle: 400 random calls in the game's ranges
    and the 16 calls of a flight in a wave: all identical (results and
    every word).

## ISPACE.DLL ordinal 15 (5:11a4; port/src/win/ispace_cut.c)

A side cut off a ship's sprite sheet. 8:2cd8 calls it (through 10:7370)
when a ship whose class has two halves (class word +28 = 3) loses one
(8:45e0, the ships' damage routine: component 3, the damage display's
Wings/Cloak [inferred], below 50 for one half, 0 for both), and again with mode 0
when a damaged ship's sheet is made anew (14:0000, 10:9a2a, 18:07b2
after the Demon sub-game; DS:92e4 set: no piece). Words: the screen DC
(not read), the DC holding the sheet (ordinal 2's layout: 16 cells of
size x size, border pixels around and between them, one per direction),
side (which half goes), size, an offset, border, palette, direction and
mode.

- **Masks.** DS:0184 (ispace_pal.c, made with the first palette) holds
  five 90x90 monochrome masks, white right of a line through the centre,
  the line upright and turned clockwise in four steps to level. Per mask
  k the part laid over a cell starts (45 - size/2) in, moved by the
  offset times -cos and sin of k x 22.5 degrees (DS:001a, DS:0010, x 128,
  16-bit product shifted right 7), and runs to the mask's last column
  but one and last row but one, at most size x size.
- **Cut.** Every cell of the sheet is ANDed (SRCAND, monochrome source:
  white keeps, black clears) with the part of its direction's mask
  (5:12b0: directions 0-4 masks 0-4, then back down and up again),
  mirrored as the direction goes round: side 1 as is for 0-4, left-right
  for 5-8, both for 9-11, upside down for 12-15; side 0 turned half round
  from that, except directions 8 and 12, which take the mask as it is
  (masks 0 and 4 are symmetric that way, so the halves still fit).
- **Mode 1** first copies the cell of direction dir into a new size x
  size bitmap and clears it with the same part (DSna: what the sheet
  loses), and returns it: the piece flying off. Mode 0 returns -1.
- **Fixed silently:** mode 1 with a direction outside 0-15 (the game
  passes 0-15) reads two other locals of the DLL as the mask's place; the
  port then makes no piece (returns 0) and still cuts the sheet.
- **Verified** with the oracle (tools/dll_oracle/damage.txt, 194 calls):
  both sides, both modes, every direction on fresh surfaces of three
  sizes (12, 23 and 145: the part then starts before the mask), large
  and negative offsets, no palette, and the calls of waves (the player's
  TRANSFORMER, size 33, border 5, losing a wing to the enemies of the
  secret codes 3, 4 and F5): the sheet and the piece identical. The
  masks' polygons are filled by the port's Polygon (the emulated DLL's
  stand-in draws them the same way), so Windows' own polygon edges are
  not checked [uncertain: GDI's fill rule for these edges may differ by
  a pixel].

## ISPACE.DLL surfaces (ordinal 2, 6:011c; port/src/win/ispace_surface.c)

The pictures of the wave's ships and objects: the game calls ordinal 2
through 10:6ee6 and 10:6fec (the shield picture of 18:08bc) and cuts
its sprites from the result. Words used: f (the black border around
each cell; 99: 5 for an odd image height, 6 for an even one; -100: one
angle and no border), i (4 angles, 16 when 0), j (the sheet 2^j times
the image's size), k and l (colour sets of colours 0-9 and 10-14), m
(1: only two frames) and n (non-zero: 6:78ba, below). e, g and h are
not read on the 8-bit path.

- **Image.** Loaded in mode 1 (5:1b8e) with colour sets k and l, which
  are first put in the palette (5:6f58 set to id, 5:61b2); it is a strip
  of frames as wide as it is high. With m == 1 only two frames are made,
  the second from the image's last frame.
- **Ramps.** Per group a ramp per hue met (5:66ea) for the image's own
  colours (set 12), else one ramp of the set; each ramp is the range its
  set has in the palette (DS:1dea, DS:1398), set into the palette once
  more (5:61b2 again: one more user of the range). The ends' lightness
  as ordinal 12's, except group 1's: the root from half the mean, six
  Newton steps. Colours 0-9 count 5 lighter than their lightness.
- **Drawing** (per frame): as ordinal 12's passes 2 and 3 into 2n x 2n
  planes per group and a code plane (ramp * 2 + group), then the corner
  cut; no blur. Angles 1-3 (or 1-15) are turned from angle 0 (DS:011a
  sine, DS:013a minus cosine, x 512): every cell lit above 0x1e goes to
  its turned place, rounded down; cells below 0x1c between two lit
  cells of a row take the left one.
- **Shading.** Each angle at the image's size (j 0: the mean of the lit
  cells of each 2x2 block, two at least, the code of the last; j 1, 2:
  one cell), group 0 then group 1 over it, on the block's ramp
  (ispace_ramp_shade, as ordinal 12). With 4 or 16 angles each cell is
  also written turned a quarter, half and three quarters round, 4, 8
  and 12 cells on: 16 directions from 4 angles. A frame's sheet (16
  cells n + f apart, f around) is an 8-bit DIB made a bitmap (5:2080)
  and blitted into the result, frames n + f apart; one angle gives one
  n x n cell.
- **Quirks kept:** a frame starting on an odd column (frames of odd
  height after the first) is drawn one block right and loses its last
  column (the DLL skips block 0); the corner cut of frame f works on
  the planes of index f, not the frame's own (with several angles, for
  f > 0 planes still empty unless f is a multiple of the angles), so
  later frames keep their corners; the turn's rounding terms are cleared before use;
  with m == 1 the bitmap is a cell wider (left black); with j 2 each row
  of a cell steps half a plane row, so odd rows read the plane h cells
  on; with 16 angles the turned copies of angles 4-15 land past the 16
  cells, in later rows of the sheet.
- **Fixed silently (memory safety, divide faults):** a ramp whose ends
  are equally light (the DLL divides by zero; seen in the emulated DLL)
  starts its search at its last entry; with j 2 the last row of a cell
  reads past its planes (0 here; the DLL reads the next block); writes
  past a sheet (16 angles) are dropped; more than 48 frames x angles
  (the DLL writes past its tables of planes) give no bitmap; 5:6f58 for
  set 12 and unknown sets (an uninitialised word) gives no set; a set
  without a range (the DLL reads before the range table) and a ramp
  index past the tables give entry 0; a palette not the manager's gives
  no bitmap.
- **Not ported:** fixed palettes, images with VGA colours (6:7fc8),
  displays of fewer than 8 bits (log, no bitmap); n != 0 (6:78ba, which
  sets colour sets up and calls 6:5538; logs, no bitmap). n is set from
  INSPACE.INI `Quick` (6:0b3e reads it, nothing writes it): with 2 the
  ships (14:11a8), the wave's other objects (10:533a) and 10:18b0's
  picture are made so; with 1 the objects and 10:18b0's picture, and the
  ships other than the player's, while DS:1e68 is set in a wave
  [uncertain: what DS:1e68 counts]. 6:5538 is a quick drawing: the image (mode 3,
  with DS:015c set so 5:26a2 fills DS:1484, each colour's palette entry)
  turned to 16 angles pixel by pixel (DS:011a, DS:013a), no shading,
  single gaps closed at angles 2, 6, 10, 14; that loader branch is not
  ported either;
  the per-row callback 9:360a (sound, stubs).
- **Verified** with the oracle (tools/dll_oracle/surfaces.txt): the
  three calls of a wave (images 180, 60 with m 1, 370) after the
  wave's set-up, and 21 variations (one angle, 16 angles, j 0 and 1,
  frames of odd and even height, m 0 and 1, other colour sets and
  borders, 18:08bc's calls), and ordinal 12 after them: bitmaps and
  palettes identical. **Not verified:** j 2 (Size=2; the emulated DLL
  reads past its planes there and faults or differs).
