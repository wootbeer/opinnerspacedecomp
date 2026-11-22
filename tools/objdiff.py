#!/usr/bin/env python3
"""Show a compiled function next to the original, instruction by instruction.
usage: objdiff.py SRC.c FUNCNAME   (FUNCNAME as tagged with @addr)"""
import sys, os, shutil, tempfile
sys.path.insert(0, '/home/user/opinnerspacedecomp/tools')
import match
from ne_info import read_ne
from capstone import Cs, CS_ARCH_X86, CS_MODE_16
src, name = sys.argv[1], sys.argv[2]
os.chdir('/home/user/opinnerspacedecomp')
data = open('unpacked/INSPACE.EXE', 'rb').read()
h, segs = read_ne(data)
work = tempfile.mkdtemp()
objs = match.compile_all([src], work)
have = {n.lstrip('_').upper(): f for n, f in match.functions(objs[src]).items()}
sn, off = match.tags(src)[name]
code, mask = have[name.upper()]
s = segs[sn - 1]
game = data[s['file_off'] + off:s['file_off'] + off + len(code)]
md = Cs(CS_ARCH_X86, CS_MODE_16)
def dis(b):
    return [f"{i.address:04x} {i.bytes.hex():14} {i.mnemonic} {i.op_str}" for i in md.disasm(bytes(b), 0)]
a, g = dis(code), dis(game)
for k in range(max(len(a), len(g))):
    x = a[k] if k < len(a) else ''
    y = g[k] if k < len(g) else ''
    mark = ' ' if x[5:] == y[5:] else '*'
    print(f"{mark} {x:50} | {y}")
shutil.rmtree(work)
