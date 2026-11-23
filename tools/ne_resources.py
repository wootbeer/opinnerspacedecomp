#!/usr/bin/env python3
"""List the resources of an NE file and dump its string tables.

usage: ne_resources.py FILE [--strings] [--list]
  --list     one line per resource: type, name/id, size
  --strings  every string-table entry as "id<TAB>text" (game text: write the
             output under data/, which git ignores)
"""
import struct
import sys

from ne_info import read_ne

TYPES = {1: 'CURSOR', 2: 'BITMAP', 3: 'ICON', 4: 'MENU', 5: 'DIALOG',
         6: 'STRING', 7: 'FONTDIR', 8: 'FONT', 9: 'ACCELERATOR', 10: 'RCDATA',
         12: 'GROUP_CURSOR', 14: 'GROUP_ICON', 16: 'VERSION'}


def resources(data):
    h, _ = read_ne(data)
    base = h['ne'] + h['res_off']
    shift = struct.unpack_from('<H', data, base)[0]
    p = base + 2

    def rname(v):
        if v & 0x8000:
            return v & 0x7fff
        o = base + v
        return data[o + 1:o + 1 + data[o]].decode('latin-1')

    while True:
        tid = struct.unpack_from('<H', data, p)[0]
        if tid == 0:
            break
        count = struct.unpack_from('<H', data, p + 2)[0]
        p += 8
        tname = TYPES.get(tid & 0x7fff, tid & 0x7fff) if tid & 0x8000 else rname(tid)
        for _ in range(count):
            off, ln, _, rid = struct.unpack_from('<HHHH', data, p)
            p += 12
            yield tname, rname(rid), data[off << shift:(off << shift) + (ln << shift)]


def main():
    data = open(sys.argv[1], 'rb').read()
    for tname, rid, blob in resources(data):
        if '--list' in sys.argv:
            print(f'{tname}\t{rid}\t{len(blob)}')
        if '--strings' in sys.argv and tname == 'STRING':
            q = 0
            for i in range(16):
                if q >= len(blob):
                    break
                n = blob[q]
                s = blob[q + 1:q + 1 + n].decode('latin-1')
                q += 1 + n
                if s:
                    sid = (rid - 1) * 16 + i
                    print(f'{sid}\t{s!r}'[0:] if False else f'{sid}\t' + s.replace('\n', '\\n').replace('\r', ''))


if __name__ == '__main__':
    main()
