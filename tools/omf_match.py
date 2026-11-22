#!/usr/bin/env python3
"""Find OMF library modules (e.g. C runtime) inside an NE file's code.

usage: omf_match.py NEFILE LIB [LIB...] [--min N] [--list]

Each module's code segments are rebuilt from LEDATA records with every
FIXUPP location masked out, then searched for, byte for byte, in the
NE file's code segments. Prints how many modules of each library match and
(with --list) where. Public names of a matched module give names for the
game's library functions."""
import re
import struct
import sys

from ne_info import read_ne

LOC_SIZE = {0: 1, 1: 2, 2: 2, 3: 4, 4: 1, 5: 2, 9: 4, 11: 6, 13: 4}


def _index(b, p):
    v = b[p]
    if v & 0x80:
        return ((v & 0x7f) << 8) | b[p + 1], p + 2
    return v, p + 1


def modules(lib):
    """Yield (module name, {segment name: (bytearray, mask)}, publics)."""
    p = 0
    page = 16
    if lib[0] == 0xf0:
        page = struct.unpack_from('<H', lib, 1)[0] + 3
        p = page
    while p < len(lib):
        rtype = lib[p]
        if rtype == 0xf1:
            return
        if rtype != 0x80:
            raise ValueError(f'expected THEADR at {p:#x}, got {rtype:#x}')
        name = ''
        lnames = ['']
        segs = []                 # [name, data, mask]
        publics = []
        last = None               # (seg index, offset) of last LEDATA
        while True:
            rtype = lib[p]
            rlen = struct.unpack_from('<H', lib, p + 1)[0]
            body = lib[p + 3:p + 3 + rlen - 1]
            p += 3 + rlen
            if rtype == 0x80:
                name = body[1:1 + body[0]].decode('latin-1')
            elif rtype == 0x96:
                q = 0
                while q < len(body):
                    lnames.append(body[q + 1:q + 1 + body[q]].decode('latin-1'))
                    q += 1 + body[q]
            elif rtype in (0x98, 0x99):
                big = rtype & 1
                q = 1
                if body[0] >> 5 == 0:
                    q += 3
                size = struct.unpack_from('<I' if big else '<H', body, q)[0]
                q += 4 if big else 2
                if not big and body[0] & 2:
                    size = 0x10000
                ni, q = _index(body, q)
                ci, q = _index(body, q)
                segs.append([lnames[ni], lnames[ci], bytearray(size), bytearray(size)])
            elif rtype in (0x90, 0x91, 0xb6, 0xb7):
                q = 0
                gi, q = _index(body, q)
                si, q = _index(body, q)
                if gi == 0 and si == 0:
                    q += 2
                while q < len(body):
                    n = body[q + 1:q + 1 + body[q]].decode('latin-1')
                    q += 1 + body[q]
                    off = struct.unpack_from('<I' if rtype & 1 else '<H', body, q)[0]
                    q += 4 if rtype & 1 else 2
                    _, q = _index(body, q)
                    publics.append((n, si, off))
            elif rtype in (0xa0, 0xa1):
                si, q = _index(body, 0)
                off = struct.unpack_from('<I' if rtype & 1 else '<H', body, q)[0]
                q += 4 if rtype & 1 else 2
                data = body[q:]
                s = segs[si - 1]
                s[2][off:off + len(data)] = data
                s[3][off:off + len(data)] = b'\x01' * len(data)
                last = (si, off, rtype & 1)
            elif rtype in (0xa2, 0xa3):
                last = None       # iterated data: leave unmasked/unknown
            elif rtype in (0x9c, 0x9d):
                q = 0
                big = rtype & 1
                while q < len(body):
                    b0 = body[q]
                    if not b0 & 0x80:               # THREAD
                        method = (b0 >> 2) & 7
                        q += 1
                        if method < 3:
                            _, q = _index(body, q)
                        continue
                    locat = (b0 << 8) | body[q + 1]
                    q += 2
                    loc = (locat >> 10) & 0xf
                    doff = locat & 0x3ff
                    fix = body[q]
                    q += 1
                    if not fix & 0x80:
                        fm = (fix >> 4) & 7
                        if fm < 3:
                            _, q = _index(body, q)
                        elif fm == 3:
                            q += 2
                    if not fix & 0x08:
                        tm = fix & 3
                        if tm < 3:
                            _, q = _index(body, q)
                        else:
                            q += 2
                    if not fix & 0x04:
                        q += 4 if big else 2
                    if last:
                        si, off, _ = last
                        s = segs[si - 1]
                        a = off + doff
                        for k in range(LOC_SIZE.get(loc, 2)):
                            if a + k < len(s[3]):
                                s[3][a + k] = 0
            elif rtype in (0x8a, 0x8b):
                break
        code = {}
        for sname, cname, data, mask in segs:
            if cname.upper().endswith('CODE') and len(data):
                code[sname] = (bytes(data), bytes(mask))
        pubs = [(n, segs[si - 1][0] if si else None, off) for n, si, off in publics]
        yield name, code, pubs
        p = (p + page - 1) // page * page


def pattern(data, mask):
    return re.compile(b''.join(re.escape(bytes([c])) if m else b'.'
                               for c, m in zip(data, mask)), re.S)


def main():
    args = sys.argv[1:]
    minlen = 16
    if '--min' in args:
        i = args.index('--min')
        minlen = int(args[i + 1])
        del args[i:i + 2]
    listing = '--list' in args
    args = [a for a in args if a != '--list']
    data = open(args[0], 'rb').read()
    _, segs = read_ne(data)
    code = [(s['n'], data[s['file_off']:s['file_off'] + s['len']])
            for s in segs if not s['flags'] & 1 and s['file_off']]
    for libname in args[1:]:
        lib = open(libname, 'rb').read()
        tried = found = 0
        for mname, mcode, pubs in modules(lib):
            for sname, (d, m) in mcode.items():
                if len(d) < minlen or sum(m) < minlen:
                    continue
                tried += 1
                rx = pattern(d, m)
                hits = [(n, mt.start()) for n, b in code for mt in rx.finditer(b)]
                if hits:
                    found += 1
                if listing and hits:
                    names = ', '.join(n for n, s, _ in pubs if s == sname)[:70]
                    where = ' '.join(f'{n}:{o:04x}' for n, o in hits[:3])
                    print(f'  {mname:12} {sname:10} {len(d):5}  {where}  {names}')
        print(f'{libname}: {found}/{tried} code modules found')


if __name__ == '__main__':
    main()
