#!/usr/bin/env python3
"""OPTLOADER (SLR Systems, 1993) LZ decoder, translated from the loader's
own decode routine (segment 1, offset 0x31). Verified byte-for-byte against
that routine run under Unicorn (tools/optl_emu.py).

Bit stream: 16-bit little-endian words, consumed MSB first. A new word is
fetched as soon as the previous one's 16th bit is taken, so it comes before
any raw byte read that follows. Raw bytes (literals, distance low bytes,
long lengths) are read from the same input pointer, between words.
"""


class _Bits:
    def __init__(self, src, pos):
        self.src = src
        self.pos = pos
        self.buf = self._word()
        self.left = 16

    def _word(self):
        w = self.src[self.pos] | (self.src[self.pos + 1] << 8)
        self.pos += 2
        return w

    def bit(self):
        b = (self.buf >> 15) & 1
        self.buf = (self.buf << 1) & 0xffff
        self.left -= 1
        if self.left == 0:
            self.buf = self._word()
            self.left = 16
        return b

    def bits(self, n):
        v = 0
        for _ in range(n):
            v = (v << 1) | self.bit()
        return v

    def byte(self):
        b = self.src[self.pos]
        self.pos += 1
        return b


END = object()


def _length(r):
    """Match length after the '0' (not literal) bit. Returns an int, None
    for the 0x81 no-op marker, or END."""
    if not r.bit():                       # 0x69: '0x'
        n = 2 | r.bit()                   # 0x70..0x78
        return n                          # 2 = short form, see decode()
    if not r.bit():                       # 0xcb: '10x'
        return 4 | r.bit()
    if not r.bit():                       # 0xd3: '110x'
        return 6 | r.bit()
    if not r.bit():                       # 0xdb: '1110xx'
        return 8 + r.bits(2)
    if not r.bit():                       # 0xe3: '11110xxx'
        return 12 + r.bits(3)
    n = r.byte()                          # 0xeb: '11111' + byte
    if n < 0x81:
        return n
    if n == 0x81:
        return None
    return END


def _dist_high(r):
    """High byte of (distance - 1), at 0x7f."""
    if not r.bit():
        if not r.bit():
            return 0                      # '00'
        if not r.bit():
            return 1                      # '010'
        return 2 + r.bits(1)              # '011x'
    if not r.bit():
        if not r.bit():
            return 4 + r.bits(2)          # '100xx'
        return 8 + r.bits(3)              # '101xxx'
    if not r.bit():
        return 0x10 + r.bits(4)           # '1100xxxx'
    if not r.bit():
        return 0x20 + r.bits(4)           # '11010xxxx'
    if not r.bit():
        return 0x30 + r.bits(4)           # '110110xxxx'
    return 0x40 + r.bits(6)               # '11111xxxxxx'


def decode(src, pos=0, prefix=b''):
    """Decode an LZ stream starting at src[pos]. `prefix` is output already
    in place that matches may refer back into. Returns (output after the
    prefix, end_pos)."""
    r = _Bits(src, pos)
    out = bytearray(prefix)
    while True:
        if r.bit():                       # 0x62: '1' = literal
            out.append(r.byte())
            continue
        n = _length(r)
        if n is END:
            return bytes(out[len(prefix):]), r.pos
        if n is None:
            continue
        hi = 0 if n == 2 else _dist_high(r)
        lo = r.byte()                     # 0x91
        dist = ((hi << 8) | lo) + 1
        start = len(out) - dist
        if start < 0:
            raise ValueError(f'match before start of output at {len(out):#x}')
        for i in range(n):                # byte by byte: overlap repeats
            out.append(out[start + i])
