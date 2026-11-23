#!/usr/bin/env python3
"""Which game strings each decomp function loads by constant ID.

usage: string_refs.py STRINGS.txt [SRC.c ...] > data/strings/refs.txt
STRINGS.txt is the output of ne_resources.py --strings (ENG_LANG.DLL).
Output (game text, keep it under data/): per function, its address and the
strings it loads. Used as evidence for naming functions.
"""
import glob
import re
import sys

# loader -> index of the string-ID argument
LOADERS = {'LoadString': 1, 'fn_10_a332': 1, 'fn_09_955c': 0,
           'fn_02_094c': 0, 'fn_09_95f4': 0}

DEF = re.compile(r'^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\(([^;{]*)\)?\s*$')
ADDR = re.compile(r'(?:@addr|near-match [0-9.]+%:)\s*([0-9]+:[0-9a-f]{4})')


def args_of(text, start):
    """Split the argument list starting after '(' at text[start]."""
    depth, cur, out = 0, '', []
    for ch in text[start:]:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            if depth == 0:
                out.append(cur.strip())
                return out
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    return out


def main():
    strings = {}
    for line in open(sys.argv[1], encoding='latin-1'):
        sid, _, text = line.rstrip('\n').partition('\t')
        strings[int(sid)] = text
    srcs = sys.argv[2:] or sorted(glob.glob('src/inspace/seg*.c'))
    for src in srcs:
        lines = open(src, encoding='latin-1').read().split('\n')
        func, addr, pending, refs = None, None, None, []

        def flush():
            if func and refs:
                print(f'{addr or "?"}\t{func}')
                for sid in refs:
                    print(f'\t{sid}\t{strings.get(sid, "?")}')
        for i, line in enumerate(lines):
            m = ADDR.search(line)
            if m:
                pending = m.group(1)
            if line and not line[0].isspace() and '(' in line and not line.rstrip().endswith(';') \
                    and i + 1 < len(lines) and lines[i + 1].startswith('{'):
                d = DEF.match(line)
                if d and d.group(1) not in ('if', 'while', 'for', 'switch'):
                    flush()
                    func, addr, refs, pending = d.group(1), pending, [], None
                    continue
            for name, idx in LOADERS.items():
                for m2 in re.finditer(r'\b' + name + r'\s*\(', line):
                    a = args_of(line, m2.end())
                    if len(a) > idx:
                        v = a[idx].replace('(UINT)', '').strip()
                        if re.fullmatch(r'0x[0-9a-fA-F]+|[0-9]+', v):
                            refs.append(int(v, 0))
        flush()


if __name__ == '__main__':
    main()
