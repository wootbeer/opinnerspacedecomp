#!/usr/bin/env python3
"""List and check the NE relocations of an (unpacked) NE file.

usage: ne_relocs.py FILE [--list]
Checks that every chain stays inside its segment and ends in 0xFFFF, and
counts imports per module. With --list, prints every relocation."""
import collections
import struct
import sys

from ne_info import read_ne

SRC = {0: 'byte', 2: 'sel', 3: 'far', 5: 'off'}


def pstr(data, off):
    return data[off + 1:off + 1 + data[off]].decode('latin-1')


def relocs(data):
    h, segs = read_ne(data)
    ne = h['ne']
    mods = []
    for i in range(h['nmod']):
        o = struct.unpack_from('<H', data, ne + h['modref_off'] + 2 * i)[0]
        mods.append(pstr(data, ne + h['imp_off'] + o))
    for s in segs:
        if not s['flags'] & 0x100:
            continue
        body = data[s['file_off']:s['file_off'] + s['len']]
        p = s['file_off'] + s['len']
        n = struct.unpack_from('<H', data, p)[0]
        for i in range(n):
            src, fl, off, a, b = struct.unpack_from('<BBHHH', data, p + 2 + 8 * i)
            kind = fl & 3
            if kind == 0:
                seg = a & 0xff
                tgt = f'entry #{b}' if seg == 0xff else f'{seg}:{b:04x}'
            elif kind == 1:
                tgt = f'{mods[a - 1]}.{b}'
            elif kind == 2:
                tgt = f'{mods[a - 1]}.{pstr(data, ne + h["imp_off"] + b)}'
            else:
                tgt = f'osfixup {a}'
            sites = [off]
            if not fl & 4 and src in (2, 3, 5) and kind != 3:
                sites = []
                cur, guard = off, 0
                while cur != 0xffff:
                    if cur + 2 > len(body) or guard > 0x10000:
                        raise ValueError(f"seg {s['n']}: chain from {off:#x} leaves segment")
                    sites.append(cur)
                    cur = struct.unpack_from('<H', body, cur)[0]
                    guard += 1
            yield s, src, fl, sites, tgt


def main():
    data = open(sys.argv[1], 'rb').read()
    per_mod = collections.Counter()
    nsites = callfar = far = 0
    for s, src, fl, sites, tgt in relocs(data):
        per_mod[tgt.split('.')[0] if fl & 3 in (1, 2) else ('internal' if fl & 3 == 0 else 'os')] += len(sites)
        nsites += len(sites)
        body = data[s['file_off']:s['file_off'] + s['len']]
        if src == 3:
            far += len(sites)
            callfar += sum(1 for x in sites if x and body[x - 1] == 0x9a)
        if '--list' in sys.argv:
            print(f"{s['n']:2}: {SRC.get(src, src):4} {'add ' if fl & 4 else ''}"
                  f"{' '.join(f'{x:04x}' for x in sites)} -> {tgt}")
    print(f'{nsites} fixup sites; far pointers {far}, of which after 9A (call far) {callfar}')
    for m, c in per_mod.most_common():
        print(f'  {m}: {c}')


if __name__ == '__main__':
    main()
