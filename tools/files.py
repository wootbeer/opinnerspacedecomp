#!/usr/bin/env python3
"""Work out original source-file boundaries in INSPACE.EXE.

usage: files.py [--exe unpacked/INSPACE.EXE] [--out inventory/files.tsv]

CL 8.00c calls a far function defined in the same source file with
`push cs; call near`; a far call (9A + selector fixup) to a function in the
same segment means the callee came from a different file. Near functions
(plain `call near`) are static to their file. A file's code is contiguous,
so:
  same-file pair i..j  -> no file boundary between them
  other-file pair i, j -> at least one boundary between them
Boundaries are placed by greedy interval stabbing (fewest files), each at
the latest allowed point. Output: one line per function with its file
number; `certain` marks boundaries with only one possible position."""
import os
import re
import sys

import capstone

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from disfn import Symbols        # noqa: E402


def main():
    args = sys.argv[1:]
    exe = 'unpacked/INSPACE.EXE'
    out = 'inventory/files.tsv'
    if '--exe' in args:
        exe = args[args.index('--exe') + 1]
    if '--out' in args:
        out = args[args.index('--out') + 1]
    sym = Symbols(exe)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_16)
    lines = ['# seg:off\tfile\tboundary_before\tname']
    nfiles = 0
    for sn in sorted({k[0] for k in sym.inv}):
        funcs = sorted(off for (s, off) in sym.inv if s == sn)
        idx = {off: i for i, off in enumerate(funcs)}
        body = sym.body(sn)
        same, other = [], []
        for i, off in enumerate(funcs):
            size = sym.inv[(sn, off)][0]
            a = off
            while a < off + size:
                it = next(md.disasm(body[a:off + size], a), None)
                if it is None:
                    a += 1
                    continue
                if it.mnemonic == 'call' and it.op_str.startswith('0x'):
                    t = int(it.op_str, 16)
                    if t in idx:
                        same.append((min(i, idx[t]), max(i, idx[t])))
                elif it.mnemonic == 'lcall' and it.size == 5:
                    sel = None
                    for k in range(3, 5):
                        v = sym.sites.get((sn, a + k))
                        if v:
                            sel = v[0]
                    t = int.from_bytes(it.bytes[1:3], 'little')
                    if sel == sn and t in idx and idx[t] != i:
                        other.append((min(i, idx[t]), max(i, idx[t])))
                a += it.size
        # boundary positions: b means "between funcs[b-1] and funcs[b]", 1..n-1
        n = len(funcs)
        blocked = set()
        for i, j in same:
            blocked.update(range(i + 1, j + 1))
        conflicts = [(i, j) for i, j in other if all(b in blocked for b in range(i + 1, j + 1))]
        cuts = set()
        for i, j in sorted(other, key=lambda p: p[1]):
            if any(i < c <= j for c in cuts):
                continue
            allowed = [b for b in range(i + 1, j + 1) if b not in blocked]
            if allowed:
                cuts.add(allowed[-1])
        # a cut is certain when the pair forcing it allows only one position
        certain = set()
        for i, j in other:
            allowed = [b for b in range(i + 1, j + 1) if b not in blocked]
            if len(allowed) == 1:
                certain.add(allowed[0])
        nfiles += 1
        for k, off in enumerate(funcs):
            if k in cuts:
                nfiles += 1
            mark = 'segment' if k == 0 else ('certain' if k in certain else ('placed' if k in cuts else ''))
            lines.append(f'{sn}:{off:04x}\t{nfiles}\t{mark}\t{sym.fname(sn, off)}')
        if conflicts:
            print(f'segment {sn}: {len(conflicts)} conflicting constraints, e.g. {conflicts[:3]}')
    open(out, 'w').write('\n'.join(lines) + '\n')
    print(f'{nfiles} source files (minimum consistent with the calls)')


if __name__ == '__main__':
    main()
