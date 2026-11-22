#!/usr/bin/env python3
"""Disassemble INSPACE.EXE functions with symbols, for decompiling.

usage: disfn.py SEG:OFF [SEG:OFF...] [--exe unpacked/INSPACE.EXE]

Uses the inventory for function extents, relocations for call/pointer
targets (imports by API name, internal targets by inventory name or
fn_SS_OOOO), and names/*.txt for data (DS) names. The `mov ax,ss` of EXE
prologues is shown as the compiler emitted it plus a note."""
import os
import re
import sys

import capstone

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from ne_info import read_ne            # noqa: E402
from ne_relocs import relocs           # noqa: E402
from impnames import load as load_imports   # noqa: E402

ROOT = os.path.dirname(HERE)


def api_case():
    """Upper-case API name -> spelling in the Windows headers."""
    out = {}
    inc = os.path.join(os.environ.get('MSVC_DIR', '/home/user/toolchain/msvc'), 'INCLUDE')
    for h in ('WINDOWS.H', 'MMSYSTEM.H', 'SHELLAPI.H', 'TOOLHELP.H', 'COMMDLG.H'):
        p = os.path.join(inc, h)
        if os.path.exists(p):
            for w in re.findall(r'\b([A-Za-z_]\w*)\s*\(', open(p, encoding='latin-1').read()):
                out.setdefault(w.upper(), w)
    return out


class Symbols:
    def __init__(self, exe):
        self.data = open(exe, 'rb').read()
        self.h, self.segs = read_ne(self.data)
        base = os.path.basename(exe)
        self.inv = {}
        inv = os.path.join(ROOT, 'inventory', base + '.tsv')
        for line in open(inv):
            if line.startswith('#'):
                continue
            r = line.rstrip('\n').split('\t')
            sn, off = r[0].split(':')
            self.inv[(int(sn), int(off, 16))] = (int(r[2]), r[4], r[3])
        self.dsnames = {}
        for line in open(os.path.join(ROOT, 'names', base + '.txt'), encoding='utf-8'):
            line = line.split('#')[0].strip()
            if line.startswith('1090:'):
                a, n = line.split(None, 1)
                self.dsnames[int(a[5:], 16)] = n.split()[0]
        imps = load_imports(os.path.join(ROOT, 'names', 'imports.txt'))
        case = api_case()
        self.sites = {}
        for s, src, fl, sites, tgt in relocs(self.data):
            m = re.fullmatch(r'(\w+)\.(\d+)', tgt)
            if m and (m.group(1), int(m.group(2))) in imps:
                n = imps[(m.group(1), int(m.group(2)))]
                tgt = case.get(n, n)
            else:
                m = re.fullmatch(r'(\d+):([0-9a-f]{4})', tgt)
                if m:
                    tgt = self.fname(int(m.group(1)), int(m.group(2), 16))
            selseg = None
            m = re.fullmatch(r'fn_(\d+)_0000|DGROUP', tgt)
            if src == 2 and m:
                selseg = int(m.group(1)) if m.group(1) else 19
            for a in sites:
                self.sites[(s['n'], a)] = (selseg, ('sel ' if src == 2 else '') + tgt)

    def fname(self, sn, off):
        e = self.inv.get((sn, off))
        if e and e[1]:
            return e[1]
        if sn == 19:
            return 'DGROUP' if off == 0 else f'DGROUP:{off:04x}'
        return f'fn_{sn:02d}_{off:04x}'

    def body(self, sn):
        s = self.segs[sn - 1]
        return self.data[s['file_off']:s['file_off'] + s['len']]


def disasm(sym, sn, off):
    size, name, kind = sym.inv.get((sn, off), (0x100, '', '?'))
    body = sym.body(sn)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_16)
    print(f'; {sym.fname(sn, off)}  {sn}:{off:04x}  (selector {0x1000 + 8 * (sn - 1):04x})  '
          f'{size} bytes, {kind}')
    end = off + size
    a = off
    while a < end:
        it = next(md.disasm(body[a:end], a), None)
        if it is None:
            print(f'  {a:04x}  db {body[a]:02x}')
            a += 1
            continue
        text = f'{it.mnemonic} {it.op_str}'.strip()
        # capstone names 98/99 by their 32-bit forms; in 16-bit code they are
        # cbw/cwd unless an operand-size prefix (66) is present
        if it.bytes in (b'\x98', b'\x99'):
            text = 'cbw' if it.bytes == b'\x98' else 'cwd'
        elif it.bytes in (b'\x66\x98', b'\x66\x99'):
            text = 'cwde' if it.bytes == b'\x66\x98' else 'cdq'
        notes = []
        for k in range(it.size):
            t = sym.sites.get((sn, a + k))
            if t:
                selseg, label = t
                if selseg and it.mnemonic in ('lcall', 'ljmp') and it.size == 5:
                    label = sym.fname(selseg, int.from_bytes(it.bytes[1:3], 'little'))
                elif selseg == 19:
                    label = 'seg DGROUP'
                elif selseg:
                    label = f'seg {selseg}'
                notes.append(label)
                break
        if it.mnemonic in ('call', 'jmp') and it.op_str.startswith('0x'):
            t = int(it.op_str, 16)
            if (sn, t) in sym.inv:
                notes.append(sym.fname(sn, t))
        if a == off and it.bytes[:2] == b'\x8c\xd0':
            notes.append('linker: was mov ax,ds')
        for m in re.finditer(r'(?<![\w+-])\[(0x[0-9a-f]+)\]|ptr \[(0x[0-9a-f]+)\]', it.op_str):
            v = int(m.group(1) or m.group(2), 16)
            if 'cs:' not in it.op_str and 'es:' not in it.op_str:
                notes.append(sym.dsnames.get(v, f'DS:{v:04x}'))
        line = f'  {a:04x}  {it.bytes.hex():<14} {text}'
        if notes:
            line = f'{line:<60} ; {", ".join(notes)}'
        print(line)
        a += it.size


def main():
    import signal
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)
    args = sys.argv[1:]
    exe = os.path.join(ROOT, 'unpacked', 'INSPACE.EXE')
    if '--exe' in args:
        i = args.index('--exe')
        exe = args[i + 1]
        del args[i:i + 2]
    sym = Symbols(exe)
    for a in args:
        sn, off = a.split(':')
        disasm(sym, int(sn), int(off, 16))
        print()


if __name__ == '__main__':
    main()
