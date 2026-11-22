#!/usr/bin/env python3
"""Rebuild an OPTLOADER-packed Win16 NE file as a plain NE file.

usage: optl_unpack.py IN OUT [--verbose]

Packed segments (every segment after the loader, segment 1) are stored as
  WORD  nrelocs                total relocation entries in the tail
  ...   LZ stream              see optl_lz.py
  ...   relocation tail        OPTLOADER's own format (loader 0x770)
The tail holds groups, each starting with a word: low byte = kind,
high byte = entry count.
  kind 0xF0      entries of BYTE seg, WORD chain head: selector chains
  other kinds    bits 0-2: patch (0 byte, 1 selector, 2 far ptr, 3 offset;
                 +4 = additive, otherwise a chain as in NE),
                 bits 3-4: target (0 internal, 1 import by ordinal,
                 2 import by name, 3 OS fixup)
    internal     BYTE seg (0xFF = movable, via entry ordinal), then
                 entries of WORD offset, WORD target offset/ordinal
    import       WORD module index, then entries of WORD offset,
                 WORD ordinal / imported-names offset
    OS fixup     WORD fixup type, then entries of WORD offset
These map one to one onto NE relocation records, which is what this tool
writes. The original file is kept byte for byte; the unpacked segments are
appended at the end and the segment table and NE flags are pointed at them.
The self-loading flag is cleared, so the result loads like any NE file.
"""
import struct
import sys

from ne_info import read_ne
from optl_lz import decode

NE_SRC = {0: 0, 1: 2, 2: 3, 3: 5}   # patch & 3 -> NE source type
NE_ADDITIVE = 4


def parse_tail(tail, count):
    """Return NE relocation records (bytes, 8 each) from a packed tail."""
    recs = []
    pos = 0
    left = count
    while left:
        kind, n = tail[pos], tail[pos + 1]
        pos += 2
        left -= n
        if left < 0:
            raise ValueError('relocation count overrun')
        if kind == 0xf0:
            for _ in range(n):
                seg, off = struct.unpack_from('<BH', tail, pos)
                pos += 3
                recs.append(struct.pack('<BBHBBH', 2, 0, off, seg, 0, 0))
            continue
        patch, target = kind & 7, (kind >> 3) & 3
        if kind & ~0x1f:
            raise ValueError(f'unknown relocation kind {kind:#x}')
        src = NE_SRC[patch & 3]
        flags = target | (NE_ADDITIVE if patch & 4 else 0)
        if target == 0:
            seg = tail[pos]
            pos += 1
            for _ in range(n):
                off, val = struct.unpack_from('<HH', tail, pos)
                pos += 4
                recs.append(struct.pack('<BBHBBH', src, flags, off, seg, 0, val))
        elif target in (1, 2):
            mod = struct.unpack_from('<H', tail, pos)[0]
            pos += 2
            for _ in range(n):
                off, val = struct.unpack_from('<HH', tail, pos)
                pos += 4
                recs.append(struct.pack('<BBHHH', src, flags, off, mod, val))
        else:
            fix = struct.unpack_from('<H', tail, pos)[0]
            pos += 2
            for _ in range(n):
                off = struct.unpack_from('<H', tail, pos)[0]
                pos += 2
                recs.append(struct.pack('<BBHHH', src, flags, off, fix, 0))
    return recs, pos


def unpack(data, verbose=False):
    h, segs = read_ne(data)
    ne = h['ne']
    if not h['flags'] & 0x0800:
        raise ValueError('not a self-loading NE file')
    loader = data[segs[0]['file_off']:segs[0]['file_off'] + segs[0]['len']]
    if b'OPTLOADER' not in loader:
        raise ValueError('segment 1 is not OPTLOADER')
    out = bytearray(data)
    unit = 1 << h['align']
    for s in segs[1:]:
        if not s['file_off']:
            continue                      # no file data (BSS-only segment)
        if s['flags'] & 0x0100:
            raise ValueError(f"segment {s['n']} has NE relocations")
        raw = data[s['file_off']:s['file_off'] + s['len']]
        nrel = struct.unpack_from('<H', raw, 0)[0]
        body, end = decode(raw, 2)
        if len(body) > s['alloc']:
            raise ValueError(f"segment {s['n']} unpacks past its alloc size")
        recs, used = parse_tail(raw[end:], nrel)
        if end + used != len(raw):
            raise ValueError(f"segment {s['n']}: {len(raw) - end - used} bytes left over")
        out += bytes(-len(out) % unit)
        pos = len(out)
        out += body
        flags = s['flags']
        if recs:
            out += struct.pack('<H', len(recs)) + b''.join(recs)
            flags |= 0x0100
        if pos // unit > 0xffff or len(body) > 0x10000:
            raise ValueError('output too large for the NE segment table')
        struct.pack_into('<HHHH', out, ne + h['seg_off'] + 8 * (s['n'] - 1),
                         pos // unit, len(body) & 0xffff, flags,
                         s['alloc'] & 0xffff)
        if verbose:
            print(f"seg {s['n']:2}: {s['len']:#06x} -> {len(body):#06x} bytes, "
                  f"{len(recs)} relocations")
    struct.pack_into('<H', out, ne + 0x0c, h['flags'] & ~0x0800)
    return bytes(out)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('-')]
    if len(args) != 2:
        sys.exit(__doc__)
    data = open(args[0], 'rb').read()
    res = unpack(data, '--verbose' in sys.argv)
    open(args[1], 'wb').write(res)


if __name__ == '__main__':
    main()
