#!/usr/bin/env python3
"""Build the function inventory of an unpacked NE file.

usage: inventory.py NEFILE OUT.tsv [--names names/X.txt] [--lib LIB...]

Function starts come from: far prologues (`mov ax,ds|ss; nop; inc bp;
push bp; mov bp,sp`), internal relocation targets in code segments, the
entry table, near-call targets found while disassembling, and C runtime
modules matched in LIBs (tools/omf_match.py). Each function is then
disassembled by recursive descent (following jumps, near calls and MSC
switch tables, `jmp cs:[bx+table]`) to find its extent.

Output columns: seg:off, selector:off, size, kind (far / near / lib),
name, name source, flags (data = jump tables inside; gap = unreached bytes
before the next function).
"""
import re
import struct
import sys

import capstone

from ne_info import read_ne
from ne_relocs import relocs
from omf_match import modules, pattern

PROLOGUES = [bytes.fromhex('8cd0904555 8bec'.replace(' ', '')),
             bytes.fromhex('8cd8904555 8bec'.replace(' ', ''))]
JMP_TABLE = re.compile(r'^word ptr cs:\[bx \+ (0x[0-9a-f]+)\]$')


def entries(data, h):
    p = h['ne'] + h['entry_off']
    end = p + h['entry_len']
    out = []
    ordinal = 1
    while p < end:
        n, t = data[p], data[p + 1]
        p += 2
        if n == 0:
            break
        for _ in range(n):
            if t == 0xff:
                _, _, sg, off = struct.unpack_from('<BHBH', data, p)
                p += 6
                out.append((ordinal, sg, off))
            elif t:
                _, off = struct.unpack_from('<BH', data, p)
                p += 3
                out.append((ordinal, t, off))
            ordinal += 1
    return out


def load_names(path):
    names = {}
    for line in open(path, encoding='utf-8'):
        line = line.split('#')[0].strip()
        if not line:
            continue
        addr, name = line.split(None, 1)
        name = name.split()[0]                 # drop tags such as [inferred]
        sel, off = addr.split(':')
        seg = (int(sel, 16) - 0x1000) // 8 + 1
        names[(seg, int(off, 16))] = name
    return names


class Seg:
    def __init__(self, n, body):
        self.n = n
        self.body = body
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_16)
        self.cache = {}

    def insn(self, a):
        if a not in self.cache:
            it = next(self.md.disasm(self.body[a:a + 16], a), None)
            self.cache[a] = it
        return self.cache[a]


def walk(seg, start, limit, near_calls):
    """Recursive descent from start. Returns (covered byte set, has_data)."""
    covered = set()
    work = [start]
    seen = set()
    has_data = False
    while work:
        a = work.pop()
        while a not in seen and 0 <= a < limit:
            seen.add(a)
            it = seg.insn(a)
            if it is None:
                break
            covered.update(range(a, a + it.size))
            m, op = it.mnemonic, it.op_str
            nxt = a + it.size
            if m in ('ret', 'retf', 'iret', 'hlt'):
                break
            if m == 'jmp':
                if op.startswith('0x'):
                    work.append(int(op, 16))
                    break
                t = JMP_TABLE.match(op)
                if t:
                    tab = int(t.group(1), 16)
                    targets = []
                    q = tab
                    lowest = None
                    while q + 2 <= limit and q not in covered:
                        v = struct.unpack_from('<H', seg.body, q)[0]
                        if not start <= v < limit:
                            break
                        if lowest is not None and q >= lowest:
                            break
                        targets.append(v)
                        covered.update((q, q + 1))
                        lowest = v if lowest is None else min(lowest, v)
                        if tab < a and q + 2 >= a:
                            break
                        q += 2
                    has_data = True
                    work.extend(targets)
                break
            if m.startswith('j') or m.startswith('loop') or m == 'jcxz':
                if op.startswith('0x'):
                    work.append(int(op, 16))
            elif m == 'call' and op.startswith('0x'):
                near_calls.add(int(op, 16))
            a = nxt
    return covered, has_data


def lib_starts(data, segs, libs):
    """{(seg, off): name} for C runtime publics found in code."""
    found = {}
    code = [(s['n'], data[s['file_off']:s['file_off'] + s['len']])
            for s in segs if not s['flags'] & 1 and s['n'] > 1]
    for lib in libs:
        for _, mcode, pubs in modules(open(lib, 'rb').read()):
            for sname, (d, m) in mcode.items():
                if len(d) < 16 or sum(m) < 12:
                    continue
                rx = pattern(d, m)
                hits = [(n, mt.start()) for n, b in code for mt in rx.finditer(b)]
                if len(hits) != 1:
                    continue
                n, base = hits[0]
                for pname, ps, off in pubs:
                    if ps == sname:
                        found.setdefault((n, base + off), pname)
    return found


def main():
    args = sys.argv[1:]
    names, libs = {}, []
    if '--names' in args:
        i = args.index('--names')
        names = load_names(args[i + 1])
        del args[i:i + 2]
    if '--lib' in args:
        i = args.index('--lib')
        libs = args[i + 1:]
        del args[i:]
    src, out = args
    data = open(src, 'rb').read()
    h, segs = read_ne(data)
    code = {s['n']: s for s in segs if not s['flags'] & 1 and s['n'] > 1 and s['file_off']}
    starts = {}                                  # (seg, off) -> kind

    def add(seg, off, kind):
        if seg in code and 0 <= off < code[seg]['len']:
            starts.setdefault((seg, off), kind)

    for sn, s in code.items():
        body = data[s['file_off']:s['file_off'] + s['len']]
        for p in PROLOGUES:
            i = body.find(p)
            while i >= 0:
                add(sn, i, 'far')
                i = body.find(p, i + 1)
    for s, src_t, fl, sites, tgt in relocs(data):
        m = re.fullmatch(r'(\d+):([0-9a-f]{4})', tgt)
        if m and fl & 3 == 0 and src_t in (3, 5):
            add(int(m.group(1)), int(m.group(2), 16), 'far')
    for _, sg, off in entries(data, h):
        add(sg, off, 'far')
    libnames = lib_starts(data, segs, libs) if libs else {}
    for (sn, off) in libnames:
        starts[(sn, off)] = 'lib'
    for key in names:
        add(key[0], key[1], 'far')

    segobj = {sn: Seg(sn, data[s['file_off']:s['file_off'] + s['len']]) for sn, s in code.items()}
    # iterate: near-call targets become new starts
    done = {}
    pending = set(starts)
    while pending:
        sn, off = pending.pop()
        if (sn, off) in done:
            continue
        near = set()
        cov, has_data = walk(segobj[sn], off, code[sn]['len'], near)
        done[(sn, off)] = (cov, has_data)
        for t in near:
            if (sn, t) not in starts:
                starts[(sn, t)] = 'near'
                pending.add((sn, t))

    rows = []
    total = covered_all = 0
    for sn in sorted(code):
        ss = sorted(off for (s, off) in starts if s == sn)
        seglen = code[sn]['len']
        total += seglen
        for i, off in enumerate(ss):
            nxt = ss[i + 1] if i + 1 < len(ss) else seglen
            cov, has_data = done[(sn, off)]
            mine = [a for a in cov if off <= a < nxt]
            end = max(mine) + 1 if mine else off
            # trailing alignment byte
            pad = nxt - end
            gap = pad > 1 or (pad == 1 and segobj[sn].body[end] != 0x90)
            size = end - off
            covered_all += len(mine)
            sel = 0x1000 + 8 * (sn - 1)
            name = names.get((sn, off)) or libnames.get((sn, off)) or ''
            source = 'names' if (sn, off) in names else ('lib' if (sn, off) in libnames else '')
            flags = ','.join(f for f, on in (('data', has_data), (f'gap{pad}', gap)) if on)
            rows.append(f'{sn}:{off:04x}\t{sel:04x}:{off:04x}\t{size}\t{starts[(sn, off)]}\t{name}\t{source}\t{flags}')
    with open(out, 'w') as f:
        f.write('# addr\tselector\tsize\tkind\tname\tname_source\tflags\n')
        f.write('\n'.join(rows) + '\n')
    nf = len(rows)
    print(f'{nf} functions; {covered_all}/{total} code bytes reached ({100 * covered_all / total:.1f}%)')
    kinds = {}
    for r in rows:
        k = r.split('\t')[3]
        kinds[k] = kinds.get(k, 0) + 1
    print(kinds, f"{sum(1 for r in rows if r.split(chr(9))[4])} named")


if __name__ == '__main__':
    main()
