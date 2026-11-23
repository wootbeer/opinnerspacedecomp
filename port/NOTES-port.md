# Port notes: game code translated from the decomp

`port/src/game/` is generated. Do not edit it by hand. To regenerate it, run:

    python3 -I tools/port_translate.py      # writes game.h, win16api.h, segNN*.c
    python3 -I tools/port_merge.py --merge-report   # merge details only

`port/translate-notes.txt` is regenerated on each run. It lists every merge decision and conflict: table lengths, field type choices, arrays cut short, overlapping views and per-line notes.

## How it works

- **port_merge.py** parses each decomp file with pycparser. Before parsing, the file's own macros are expanded (except `SC` and `GETPROC`), `far`/`huge` become a parser marker, and `pascal`/`near` are dropped. The script then collects every view of DGROUP and of the records and merges them:
  - **Tables:** struct arrays with the same record size whose bases are less than one record apart form one table. Its base is the lowest view address and its type is one struct with all fields at their true offsets. Fields are named `f_XX` by true offset; a descriptive name is kept when the views agree on it.
  - **Records behind far pointers:** these are grouped by pointer slot. For example, `g_1e30` is `g_1df8[14]`.
  - **Other globals:** one declaration per DS address. The most specific type wins (struct, POINT/RECT, handle, DWORD, then int). Arrays win over the scalars inside them.
  - **Mismatched views:** an access through a narrower or differently typed view becomes `LO16`/`HI16`/`LO8`/`HI8`, `VIEW(T, field, off)` or `VIEWP(PT, field, off)`. These macros are in `game.h`. They are exact because records keep the original byte layout: fixed-width types with `#pragma pack` as in the original. They also assume a little-endian target.
- **port_translate.py** edits the decomp text, so comments and layout survive:
  - It drops the file-local typedefs, externs and prototypes, plus the stubs that only forced near calls in the 1994 build.
  - It maps the 16-bit types to `int16_t`/`int32_t`/... and replaces `@addr` tags with an address comment.
  - It rewrites accesses through other views onto the merged tables. Index shifts become `[i + q]`, fields are renamed by true offset, and `*(T *)&x` / `((T *)&x)[k]` aliases become the global or field they name.
- **win16api.h** is generated from the MSVC 1.5x headers. It holds the API prototypes and constants the game uses, with fixed-width types. Standard C functions come from the host libc.
- **16-bit arithmetic** (`tools/port_int16.py`, run on each generated file). It types every expression under the 1994 rules (16-bit int/unsigned, MSC conversions, literal types) and tracks the range of its native value. Natively an int16 expression equals the 1994 value modulo 2^16, so a cast is inserted only where the whole value is used and can differ: compare, `/ % >>`, condition, widening to long, a libc int parameter (`(int16_t)(a * b) < c`, `(uint16_t)i < u`, `u == 0xffff`). Stores to 16-bit variables, 16-bit parameters and array indexes need none. Reads through a view of the other signedness (`int` view of a HWND, `long` view of a DWORD) are marked by the translator and cast where it matters. Long arithmetic wraps with `-fwrapv`. Counts by kind and every site are in translate-notes; `python3 -I tools/port_int16_check.py` checks the result against a 1994 evaluator on random values.
- **Names.** Confirmed names from `names/INSPACE.EXE.txt` replace `g_XXXX` / `fn_SS_OOOO` everywhere in the generated code (declarations, definitions, calls, uses). Names tagged `[inferred]` are only comments in game.h; where the decomp already used one as an identifier (`command_watch_ship`), the code goes back to the address name.
- **Signatures** (`tools/port_overrides.py`, `port/overrides/signatures.txt`). The callee's definition is the real signature. The overrides file lists the exceptions (thunks whose callers use the result or pass other types, K&R definitions, a few single calls); they are applied to the decomp text in memory before parsing, so game.h, the definition and all callers follow. The translator then adapts every call to the callee's signature: extra arguments are dropped (side effects kept, as statements before the call), two values become a `(POINT){x, y}` or a long (`MAKELONG` or a literal), a long or a two-int record passed for two int parameters is split, `(char)idx | type << 8` becomes `(OBJREF){idx, type}`, and a function stored in a function pointer loses its cast when it has the pointer's type. Each adaptation is a note in translate-notes; dropped arguments are listed under `== dropped call arguments`.

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

## Far pointers and save files

- **Function pointers in `REC_70`.** The far function pointers at +5e/+62/+66 make `REC_70` 124 bytes natively instead of 0x70. Any code that sizes these blocks as 0x70, copies them as raw bytes, or reads them from a file must be checked. Every other record type is pointer-free, so its native layout equals the original.
- **Save files.** fn_06_9e66 and fn_14_4006 write and read whole GlobalAlloc blocks with `_lwrite`/`_lread`. These are the REC_SAVE block, `g_6e24` (REC_7C), `g_69f4` (REC_297), `g_6e1c`, `g_6e20`, `g_6afc` and REC_1A9 records. All are pointer-free, but they still need explicit serialisation of the original byte format, because their sizes come from `GlobalSize`.
- **Far-pointer arithmetic.** About 93 casts turn a far pointer into an integer, and 17 go the other way. These are segment:offset arithmetic and `(long)ptr` comparisons. Each must become plain pointer arithmetic.
- **`huge` and `_lread`/`_lwrite` sizes.** `huge` is dropped. The 0x7fff-byte chunking in fn_06_9e66 is harmless natively.
- **Runtime types that differ natively.** `time()`, `stat()` and `utime()` use the host's runtime types. The original's `time_t` was 32 bits; check any place that stores these values in 32-bit globals.
