#!/usr/bin/env python3
"""Reference OPTLOADER LZ decoder: runs the loader's own decode routine
(segment 1, offset 0x31) under Unicorn. Used to verify optl_unpack.py."""
from unicorn import Uc, UC_ARCH_X86, UC_MODE_16
from unicorn.x86_const import (UC_X86_REG_CS, UC_X86_REG_DS, UC_X86_REG_ES,
                               UC_X86_REG_SS, UC_X86_REG_SI, UC_X86_REG_DI,
                               UC_X86_REG_SP, UC_X86_REG_IP)

SEG = 0x1000      # code/data segment for the decoder and buffers
STK = 0x3000
DECODE = 0x31     # decoder entry in the loader segment
RET = 0xfff0      # address of a HLT stub the decoder returns to


def decode(loader, src, out_size, prefix=b''):
    """Decode `src` with the loader code `loader` (bytes of segment 1).
    `prefix` is output already present before the stream (the loader decodes
    itself after its own 0x1e7 plain bytes). Returns (output bytes after the
    prefix, number of source bytes consumed)."""
    uc = Uc(UC_ARCH_X86, UC_MODE_16)
    uc.mem_map(0, 0x100000)
    base = SEG * 16
    uc.mem_write(base, bytes(loader[:0x1e7]))
    # Output goes in its own segment, input in another, so they can't overlap.
    obase, ibase = 0x40000, 0x50000
    uc.mem_write(ibase, bytes(src))
    uc.mem_write(obase, bytes(prefix))
    uc.mem_write(base + RET, b'\xf4')
    # The decoder copies matches from ES:[DI-dist] with an ES override and
    # reads input through DS:SI; literals are movsb DS:SI -> ES:DI. Matches
    # use `lea si,[bx+di]` then `es rep movsb`, so input and output must be
    # addressed with the same SI/DI scheme: DS=input seg, ES=output seg.
    uc.reg_write(UC_X86_REG_DS, ibase >> 4)
    uc.reg_write(UC_X86_REG_ES, obase >> 4)
    uc.reg_write(UC_X86_REG_SS, STK)
    uc.reg_write(UC_X86_REG_SP, 0xfffe)
    uc.reg_write(UC_X86_REG_SI, 0)
    uc.reg_write(UC_X86_REG_DI, len(prefix))
    # push near return address
    uc.mem_write(STK * 16 + 0xfffc, RET.to_bytes(2, 'little'))
    uc.reg_write(UC_X86_REG_SP, 0xfffc)
    uc.reg_write(UC_X86_REG_CS, SEG)
    uc.emu_start(base + DECODE, base + RET, count=50_000_000)
    di = uc.reg_read(UC_X86_REG_DI)
    si = uc.reg_read(UC_X86_REG_SI)
    out = bytes(uc.mem_read(obase + len(prefix), max(di - len(prefix), 1)))[:di - len(prefix)]
    return out, si
