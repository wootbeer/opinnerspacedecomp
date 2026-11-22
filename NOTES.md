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

- **Linker: SLR OPTLINK** (OPTLOADER is its packer/self-loader). Confirmed.
- **Compiler: Microsoft C.** Confirmed: `<<NMSG>>` message table and
  `_C_FILE_INFO=` are MS C runtime; the startup is MS C's Windows crt0
  (INITTASK, GetVersion, `mov ah,30h` through DOS3CALL).
- **Version: MS C/C++ 7.0 or Visual C++ 1.x (C8)** `[inferred]`: the runtime
  messages include R6020 "unexpected QuickWin error" and R6021 "no main
  procedure"; QuickWin arrived in C7. Telling C7 / VC 1.0 / VC 1.5 apart needs
  the real CRT objects to compare against.
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
