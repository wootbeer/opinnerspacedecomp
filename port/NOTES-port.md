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

## Current state

- 32 files are translated, with 842 functions and one definition each.
- These files compile without errors: seg02b, seg06, seg06b, seg09a, seg11b, seg13b.
- The other 26 files have 157 errors in total (gcc 13, `-std=c99 -Wall -Wextra -pedantic -fsigned-char`).

## Needs human judgement

1. **Function signatures that differ between files (about 135 errors).** Each decomp file had its own prototypes. game.h uses the definition's signature, so callers that disagree now fail to compile. The main cases, with the number of errors:

   | Function | Errors |
   |---|---|
   | `fn_07_2080` | 30 |
   | `fn_10_6e76` | 14 |
   | `fn_08_1d54` | 12 |
   | `fn_10_9526` | 6 |
   | `fn_10_7dd4` | 5 |
   | `fn_10_1eb6` | 5 |
   | `fn_07_5d6a` | 4 |
   | `fn_10_6ee6` | 3 |
   | `fn_08_99ce` | 3 |

   The rest have 1 or 2 each: `fn_18_5350`, `fn_16_7210`, `fn_11_a4a6`, `fn_11_3cc2`, `fn_10_7480`, `fn_08_9028`, `fn_07_119c`, `fn_06_1c0c`, `fn_17_30b0`, `fn_16_638a`, `fn_13_9a18`, `fn_10_7328`, `fn_08_285a`, `fn_06_12b6`, and the far pointers `g_1d4c`/`g_1d50`/`g_1d54`, `REC_70.f_5e`/`f_62`.

   The errors come in four forms:
   - **Extra arguments:** the original cdecl caller passed arguments the callee ignores.
   - **Struct versus two ints:** a POINT passed by value at some call sites and two ints at others (DECOMP: 8:9028, 8:1d54, 18:5350).
   - **void versus int returns:** a `void` definition whose result is used, e.g. `fn_02_1a5a` (DECOMP: "returns whatever g_fp_1d5c leaves").
   - **Function-pointer signatures that differ by caller:** `REC_70.f_5e` is seen with 0, 2 and 3 arguments.

   Each one needs a decision on the real signature.
2. **Table extents.** Lengths not declared anywhere are guessed as "up to the next declared global"; see `== table length` in translate-notes.
   - `g_6670` is joined with `g_66e0` as one 0x1c table of 14 records. That is a guess.
   - `g_57a8` (0x23) and `g_8870` (0x18) do not end on a record boundary.
3. **Object table base.** It is DS:7090, the lowest address any view uses (a view at 7090 has a field at +0). DECOMP.md calls 7092 the real record start. If 7092 is chosen, every object field name shifts by 2.
4. **Type conflicts the merge settled by rank** (`== field types`, `== global types`):
   - `REC_70 +6a` is DWORD in most files and `void far *` in one. DWORD was chosen.
   - `REC_70 +5e/+62/+66` are function pointers with several signatures.
   - `g_05a0` is `long` in inspace.h, but the code reads it as width + height ints. It stays `int32_t`, and the int views become `LO16`/`HI16`. A POINT-like pair may be the better final type.
5. **Signedness of views.** A file that declared a global `int` while the merged type is `uint16_t` (or the reverse) still compiles. No casts are inserted yet, so compares and divisions through such a view can change meaning. The list is in `== global types` / `== field types`.
6. **16-bit arithmetic.** `int` is 32 bits natively, so intermediate results no longer wrap at 16 bits, and `uint16_t` promotes to signed `int`. Compares, divisions, shifts and widening to 32 bits of such expressions need `(int16_t)`/`(uint16_t)` casts where overflow is possible. This is not done yet. A typed pass can find these places; the translator already infers 16-bit types. The 50 "left shift of negative value" warnings belong here too.
7. **Struct views over plain globals** (`RACEV` at DS:9ea2) are resolved to the individual globals. 8 aliasing casts could not be resolved and are left as they were (`alias kept`).
8. **Layout-only constructs are not removed yet.** They still show as warnings:
   - 558 unused locals (mostly frame fillers)
   - 80 variables set but never used
   - 8 unused labels
   - `if (0)` blocks, `(f(), 0) ||` chains and volatile dead loads are still in the code

   Removing unused locals is safe and mechanical. The rest needs a per-case look.
9. **Other warnings:**
   - 197 `char` array subscripts. The original indexed with a signed char, so the fix is an explicit `(int)` cast, not unsigned.
   - 94 precedence warnings.
   - 45 unused parameters.
   - About 150 pointer/integer conversions. Most are string or near-pointer arguments passed where the prototype says int, and `(long)` casts of far pointers; see "Far pointers" below.

## Far pointers and save files

- **Function pointers in `REC_70`.** The far function pointers at +5e/+62/+66 make `REC_70` 124 bytes natively instead of 0x70. Any code that sizes these blocks as 0x70, copies them as raw bytes, or reads them from a file must be checked. Every other record type is pointer-free, so its native layout equals the original.
- **Save files.** fn_06_9e66 and fn_14_4006 write and read whole GlobalAlloc blocks with `_lwrite`/`_lread`. These are the REC_SAVE block, `g_6e24` (REC_7C), `g_69f4` (REC_297), `g_6e1c`, `g_6e20`, `g_6afc` and REC_1A9 records. All are pointer-free, but they still need explicit serialisation of the original byte format, because their sizes come from `GlobalSize`.
- **Far-pointer arithmetic.** About 93 casts turn a far pointer into an integer, and 17 go the other way. These are segment:offset arithmetic and `(long)ptr` comparisons. Each must become plain pointer arithmetic.
- **`huge` and `_lread`/`_lwrite` sizes.** `huge` is dropped. The 0x7fff-byte chunking in fn_06_9e66 is harmless natively.
- **Runtime types that differ natively.** `time()`, `stat()` and `utime()` use the host's runtime types. The original's `time_t` was 32 bits; check any place that stores these values in 32-bit globals.
