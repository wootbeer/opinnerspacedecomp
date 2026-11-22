# Findings

Findings from this restart. `HANDOFF.md` holds what came before.

## Files (SHA-1)

| File | SHA-1 | Notes |
|---|---|---|
| INSPACE.EXE | 7fe3dfe164b19152793f1dd6ca0c77f8fc2b49dc | 19 segments, seg 19 = DGROUP (DS 0x1090), entry 5:001a |
| ISPACE.DLL | fa73f48cbde188737329c5ddf08a0f2451bd3abd | 11 segments, seg 11 = data |
| FACTORY.EXE | 07cd9b911480c0f51e4c6429650a8e5a95f77800 | 6 segments |
| IGRAPHIC.DLL, ENG_LANG.DLL | | resources only, no segments |

## Unpacking (step 2): done

All four packed files unpack with `tools/optl_unpack.py` (format in
`tools/README.md`). INSPACE.EXE: 18 packed segments, decoder output checked
byte for byte against the original loader routine, 10005 fixup sites, all
chains valid; 5900 of 5901 far-pointer fixups sit on `call far` operands.

Correction to HANDOFF: segment 1's LZ body decodes *in place after* its 0x1e7
plain bytes and its matches reach back into them. Decoding it into an empty
buffer gives plausible but wrong bytes.

## Toolchain (step 3): what the binaries say

C runtime matches use the medium-model Windows libraries (`MLIBCW`, `MDLLCW`):
more modules match than with large model. Memory model: `/AM` `[inferred]`.

- **Linker: SLR OPTLINK** (OPTLOADER is its packer/self-loader). Confirmed.
- **Compiler: Microsoft C.** Confirmed: `<<NMSG>>` message table and
  `_C_FILE_INFO=` are MS C runtime; the startup is MS C's Windows crt0
  (INITTASK, GetVersion, `mov ah,30h` through DOS3CALL).
- **Version: Visual C++ 1.0 or 1.5x (C8), not C7.** Evidence:
  - MS C/C++ 7.0 (all 9 disks checked, `/home/user/toolchain/c700`) has only
    `/G0`-`/G2`; INSPACE.EXE has ~1400 instructions with 32-bit registers.
  - The startup module (`windows\crt0.asm`) of every file (INSPACE, ISPACE,
    FACTORY, BACKUP) differs from C7's: the game's has extra code, e.g.
    `xchg al,ah; mov [..],ax` after the GetVersion and DOS version calls.
  - 15 smaller C7 runtime modules (strcpy, strlen, getenv.c, rand.c, growseg,
    ...) match INSPACE.EXE segment 5 byte for byte, so those did not change
    between C7 and the version used; C7 `crt0dat.asm` matches except for
    prologues (next point).
  - Still to settle: VC++ 1.0 vs 1.5x, by the same library comparison
    (`tools/omf_match.py`) once their libraries are available.
- **Prologue rewrite at link time** `[inferred]`: C7 library code has
  `mov ax,ds; nop` (8C D8 90), the same code in the EXEs has `mov ax,ss; nop`
  (8C D0 90). All EXE far prologues read `mov ax,ss`, the DLL's `mov ax,ds`.
  Most likely an OPTLINK option rewriting prologues for EXEs (SS == DS);
  option name not confirmed.
- **Flags** `[inferred]`, from code patterns, to confirm by compiling:
  - INSPACE.EXE, FACTORY.EXE, BACKUP.EXE: far functions start
    `mov ax,ss; nop; inc bp; push bp; mov bp,sp; push ds; mov ds,ax` = `/GA`
    (protected-mode application, SS == DS).
  - ISPACE.DLL: `mov ax,ds; nop; inc bp; ...` = `/GD`-style DLL prologue.
  - Frames are `sub sp,N` with almost no `__chkstk` calls: `/Gs` (no stack
    checks), or most functions are small.
  - INSPACE.EXE: ~1400 32-bit-operand instructions (e.g. `xor eax,eax;
    mov [bp-12h],eax` for a long = 0) and ~2200 `C1` immediate shifts:
    `/G3`. ISPACE.DLL has 5 such instructions and 387 `C1` shifts: `/G2`
    likely. FACTORY/BACKUP have some 32-bit code too.
  - `push imm8` (6A) everywhere: at least `/G1`.
  - Memory model: far calls between segments, near data: medium or large.
