#!/usr/bin/env python3
"""Ordinal -> name maps for imported Windows modules, read from OMF import
libraries (IMPDEF comment records), e.g. LIBW.LIB, MMSYSTEM.LIB, SHELL.LIB.

usage: impnames.py LIB... > names/imports.txt     (lines: MODULE.ordinal name)
"""
import struct
import sys


def impdefs(lib):
    p = 0
    out = {}
    while p + 3 <= len(lib):
        t = lib[p]
        n = struct.unpack_from('<H', lib, p + 1)[0]
        body = lib[p + 3:p + 3 + n - 1]
        if t == 0x88 and len(body) > 3 and body[1] == 0xa0 and body[2] == 0x01:
            q = 3
            byord = body[q]
            q += 1
            name = body[q + 1:q + 1 + body[q]].decode('latin-1')
            q += 1 + body[q]
            mod = body[q + 1:q + 1 + body[q]].decode('latin-1')
            q += 1 + body[q]
            if byord:
                ordinal = struct.unpack_from('<H', body, q)[0]
                out[(mod.upper(), ordinal)] = name
        if t == 0xf1:
            break
        p += 3 + n
        if t == 0x8a:                      # MODEND: skip page padding
            if lib[0] == 0xf0:
                page = struct.unpack_from('<H', lib, 1)[0] + 3
                p = (p + page - 1) // page * page
    return out


def load(path):
    names = {}
    for line in open(path, encoding='latin-1'):
        if line.strip() and not line.startswith('#'):
            key, name = line.split()
            mod, ordinal = key.rsplit('.', 1)
            names[(mod, int(ordinal))] = name
    return names


def main():
    allnames = {}
    for lib in sys.argv[1:]:
        allnames.update(impdefs(open(lib, 'rb').read()))
    print('# Windows import names by ordinal, from the MSVC 1.5x import libraries')
    for (mod, ordinal), name in sorted(allnames.items()):
        print(f'{mod}.{ordinal} {name}')


if __name__ == '__main__':
    main()
