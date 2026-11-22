#!/usr/bin/env python3
"""Print the NE header and segment table of a Win16 executable."""
import struct
import sys


def read_ne(data):
    ne = struct.unpack_from('<H', data, 0x3c)[0]
    if data[ne:ne + 2] != b'NE':
        raise ValueError('not an NE file')
    h = {}
    (h['entry_off'], h['entry_len'], h['flags'], h['autodata'], h['heap'], h['stack'],
     h['ip'], h['cs'], h['sp'], h['ss'], h['nseg'], h['nmod'], h['nonres_len'],
     h['seg_off'], h['res_off'], h['resname_off'], h['modref_off'], h['imp_off'],
     h['nonres_off'], h['nmovable'], h['align'], h['nres']) = struct.unpack_from(
        '<HH4xHHHHHHHHHHHHHHHHIHHH', data, ne + 4)
    h['ne'] = ne
    segs = []
    for i in range(h['nseg']):
        off, ln, fl, alloc = struct.unpack_from('<HHHH', data, ne + h['seg_off'] + 8 * i)
        segs.append({'n': i + 1, 'file_off': off << h['align'],
                     'len': ln or (0x10000 if off else 0), 'flags': fl,
                     'alloc': alloc or 0x10000})
    return h, segs


def main():
    data = open(sys.argv[1], 'rb').read()
    h, segs = read_ne(data)
    print(f"NE at {h['ne']:#x} flags={h['flags']:#06x} autodata={h['autodata']} "
          f"entry={h['cs']}:{h['ip']:#06x} nseg={h['nseg']} align={h['align']}")
    for s in segs:
        kind = 'DATA' if s['flags'] & 1 else 'CODE'
        print(f"  seg {s['n']:2} {kind} file={s['file_off']:#08x} len={s['len']:#06x} "
              f"alloc={s['alloc']:#06x} flags={s['flags']:#06x}"
              f"{' RELOC' if s['flags'] & 0x100 else ''}")


if __name__ == '__main__':
    main()
