#!/usr/bin/env python3
"""Expand Microsoft COMPRESS (SZDD) files, as on old Microsoft install disks.

usage: szdd_expand.py SRCDIR DSTDIR
Expands every file in SRCDIR (recursively) into DSTDIR, restoring the last
character of the name ("CL.EX$" -> "CL.EXE") from the SZDD header. Files
that are not SZDD are copied as they are."""
import os
import shutil
import struct
import sys

MAGIC = b'SZDD\x88\xf0\x27\x33'


def expand(data):
    if data[:8] != MAGIC or data[8:9] != b'A':
        raise ValueError('not SZDD mode A')
    size = struct.unpack_from('<I', data, 10)[0]
    win = bytearray(b' ' * 4096)
    pos = 4096 - 16
    out = bytearray()
    i = 14
    while i < len(data) and len(out) < size:
        flags = data[i]
        i += 1
        for bit in range(8):
            if i >= len(data) or len(out) >= size:
                break
            if flags & (1 << bit):
                c = data[i]
                i += 1
                out.append(c)
                win[pos] = c
                pos = (pos + 1) & 0xfff
            else:
                if i + 1 >= len(data):
                    break
                lo, hi = data[i], data[i + 1]
                i += 2
                mpos = lo | ((hi & 0xf0) << 4)
                mlen = (hi & 0x0f) + 3
                for k in range(mlen):
                    c = win[(mpos + k) & 0xfff]
                    out.append(c)
                    win[pos] = c
                    pos = (pos + 1) & 0xfff
    if len(out) != size:
        raise ValueError(f'size mismatch {len(out)} != {size}')
    return bytes(out), chr(data[9]) if data[9] else ''


def main():
    src, dst = sys.argv[1], sys.argv[2]
    for root, _, files in os.walk(src):
        for name in files:
            p = os.path.join(root, name)
            rel = os.path.relpath(root, src)
            os.makedirs(os.path.join(dst, rel), exist_ok=True)
            data = open(p, 'rb').read()
            if data[:8] == MAGIC and name.endswith('$'):
                body, last = expand(data)
                out = name[:-1] + (last.upper() if last else '')
                if not out or '/' in out or '\\' in out or out in ('.', '..'):
                    raise ValueError(f'bad name {out!r}')
                open(os.path.join(dst, rel, out), 'wb').write(body)
            else:
                shutil.copyfile(p, os.path.join(dst, rel, name))


if __name__ == '__main__':
    main()
