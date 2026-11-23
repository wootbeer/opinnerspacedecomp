#!/usr/bin/env python3
"""Decomp progress for INSPACE.EXE: compiles every source in src/inspace,
checks each tagged function against the game, and scores against the
function inventory.

usage: progress.py [--write PROGRESS.md]

A function counts as matched only when every byte matches. A function
whose compiled size differs from the inventory size is reported, since that
usually means the inventory boundary or the source is wrong. Library
functions (C runtime, found in MLIBCEW.LIB) are counted apart: they come
from the original library, not from our source.
"""
import glob
import re
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import run          # noqa: E402

INV = 'inventory/INSPACE.EXE.tsv'


def main():
    rows = [l.rstrip('\n').split('\t') for l in open(INV) if not l.startswith('#')]
    inv = {r[0]: r for r in rows}
    lib = [r for r in rows if r[3] == 'lib']
    own = [r for r in rows if r[3] != 'lib']
    own_bytes = sum(int(r[2]) for r in own)
    srcs = sorted(f for f in glob.glob('src/inspace/*.c')
                  if re.fullmatch(r'seg\d\d[a-z]?\.c', os.path.basename(f)))
    results = run(srcs)
    seen = {}
    for r in results:                      # one result per address
        key = (r['seg'], r['off'])
        if key not in seen or r['bad'] == 0:
            seen[key] = r
    results = list(seen.values())
    matched = [r for r in results if r['bad'] == 0]
    mbytes = 0
    notes = []
    for r in results:
        key = f"{r['seg']}:{r['off']:04x}"
        row = inv.get(key)
        if row is None:
            notes.append(f"{key} {r['name']}: not a function start in the inventory")
            continue
        if r['bad'] == 0:
            mbytes += int(row[2])
            if r['size'] != int(row[2]):
                notes.append(f"{key} {r['name']}: matched {r['size']} bytes, inventory says {row[2]}")
    lines = [
        '# INSPACE.EXE decomp progress',
        '',
        f'- Functions matched byte for byte: **{len(matched)} / {len(own)}** '
        f'({100 * len(matched) / len(own):.2f}%)',
        f'- Code bytes in matched functions: **{mbytes} / {own_bytes}** '
        f'({100 * mbytes / own_bytes:.2f}%)',
        f'- C runtime functions (from MLIBCEW.LIB, not counted): {len(lib)}',
        f'- Functions in source, not yet matching: {len(results) - len(matched)}',
        '',
        'Compiler: MSVC 1.5x CL 8.00c, `/AM /G3 /Gw /Gs /Os`. '
        'Regenerate with `python3 tools/progress.py --write PROGRESS.md`.',
    ]
    if notes:
        lines += ['', '## Notes', ''] + [f'- {n}' for n in notes]
    text = '\n'.join(lines) + '\n'
    print(text)
    if '--write' in sys.argv:
        open(sys.argv[sys.argv.index('--write') + 1], 'w').write(text)


if __name__ == '__main__':
    main()
