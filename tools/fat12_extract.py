#!/usr/bin/env python3
"""Extract all files from a FAT12 floppy image.

usage: fat12_extract.py IMAGE OUTDIR
Names are taken from 8.3 entries only, upper case, and checked so nothing
can be written outside OUTDIR."""
import os
import re
import struct
import sys


def extract(img, outdir):
    bps, spc, rsv, nfat, nroot, _, _, spf = struct.unpack_from('<HBHBHHBH', img, 11)
    fat = img[rsv * bps:(rsv + spf) * bps]
    root = (rsv + nfat * spf) * bps
    data = root + nroot * 32
    csize = bps * spc

    def nxt(c):
        v = struct.unpack_from('<H', fat, c * 3 // 2)[0]
        return v >> 4 if c & 1 else v & 0xfff

    def chain(c, size=None):
        out = bytearray()
        seen = set()
        while 2 <= c < 0xff0 and c not in seen:
            seen.add(c)
            off = data + (c - 2) * csize
            out += img[off:off + csize]
            c = nxt(c)
        return bytes(out if size is None else out[:size])

    def walk(raw, path):
        for i in range(0, len(raw), 32):
            e = raw[i:i + 32]
            if len(e) < 32 or e[0] == 0:
                break
            if e[0] == 0xe5 or e[11] == 0x0f or e[11] & 8:
                continue
            name = e[0:8].decode('latin-1').rstrip()
            ext = e[8:11].decode('latin-1').rstrip()
            full = name + ('.' + ext if ext else '')
            if full in ('.', '..'):
                continue
            if not re.fullmatch(r"[A-Z0-9_$~!#%&'()@^`{}\-]+(\.[A-Z0-9_$~!#%&'()@^`{}\-]+)?", full):
                raise ValueError(f'unexpected name {full!r}')
            clus, size = struct.unpack_from('<HI', e, 26)
            dest = os.path.join(path, full)
            if e[11] & 0x10:
                os.makedirs(dest, exist_ok=True)
                walk(chain(clus), dest)
            else:
                with open(dest, 'wb') as f:
                    f.write(chain(clus, size))
                print(os.path.relpath(dest, outdir), size)

    os.makedirs(outdir, exist_ok=True)
    walk(img[root:data], outdir)


if __name__ == '__main__':
    extract(open(sys.argv[1], 'rb').read(), sys.argv[2])
