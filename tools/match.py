#!/usr/bin/env python3
"""Compile C sources with the original compiler (MSVC 1.5x CL 8.00c under
DOSBox) and compare each function with the game, byte for byte.

usage: match.py SRC.C [SRC.C...] [--exe unpacked/INSPACE.EXE] [--keep]

Each function to check is tagged in its source with a comment on the line
before it:
    /* @addr 10:01fe */
The function's bytes run from its public symbol to the next public in the
object (or the segment end, without trailing alignment padding). Fixup
bytes in the object are masked. The linker (OPTLINK) rewrote EXE prologues
`mov ax,ds` (8C D8) to `mov ax,ss` (8C D0); that byte is accepted.

A source may set its own compile flags with a comment anywhere in it:
    /* @cflags /AM /G2 /Gw /Gs /Os */
(some original files were built with other flags, e.g. part of segment 8
with /G2).

Environment: MSVC_DIR (default /home/user/toolchain/msvc, holding BIN, LIB,
INCLUDE), CFLAGS (default the flags confirmed for INSPACE.EXE).
"""
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from ne_info import read_ne          # noqa: E402
from omf_match import modules        # noqa: E402
from omf_fixups import parse as parse_fixups   # noqa: E402
from ne_relocs import relocs         # noqa: E402
from impnames import load as load_imports      # noqa: E402

ROOT = os.path.dirname(HERE)

MSVC_DIR = os.environ.get('MSVC_DIR', '/home/user/toolchain/msvc')
CFLAGS = os.environ.get('CFLAGS', '/AM /G3 /Gw /Gs /Os')

DOSBOX_CONF = """[sdl]
output=surface
[dosbox]
memsize=32
[cpu]
core=auto
cycles=max
[mixer]
nosound=true
[autoexec]
mount c {msvc}
mount d {work}
d:
set PATH=C:\\BIN
set INCLUDE=C:\\INCLUDE;D:\\
set LIB=C:\\LIB
set TMP=D:\\
call D:\\RUN.BAT > D:\\OUT.TXT
exit
"""


def compile_all(srcs, work):
    """Compile every source in one DOSBox run. Returns {src: obj path}."""
    objs = {}
    lines = []
    for d in {os.path.dirname(os.path.abspath(x)) for x in srcs}:
        for h in os.listdir(d):
            if h.lower().endswith('.h'):
                shutil.copyfile(os.path.join(d, h), os.path.join(work, h.upper()))
    for i, src in enumerate(srcs):
        name = f'S{i}'
        shutil.copyfile(src, os.path.join(work, name + '.C'))
        m = re.search(r'/\*\s*@cflags\s+(.*?)\s*\*/', open(src, encoding='latin-1').read())
        flags = m.group(1) if m else CFLAGS
        lines.append(f'cl /c /nologo {flags} /Fo{name}.OBJ {name}.C >> D:\\CL.TXT')
        objs[src] = os.path.join(work, name + '.OBJ')
    with open(os.path.join(work, 'RUN.BAT'), 'w', newline='\r\n') as f:
        f.write('\n'.join(lines) + '\n')
    with open(os.path.join(work, 'dosbox.conf'), 'w') as f:
        f.write(DOSBOX_CONF.format(msvc=MSVC_DIR, work=work))
    env = dict(os.environ, SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy')
    subprocess.run(['dosbox', '-conf', os.path.join(work, 'dosbox.conf'), '-exit'],
                   env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                   timeout=600, check=False)
    log = os.path.join(work, 'CL.TXT')
    if os.path.exists(log):
        text = open(log, 'rb').read().decode('latin-1').replace('\r', '')
        text = '\n'.join(l for l in text.split('\n')
                         if l.strip() and not re.fullmatch(r's\d+\.c', l.strip()))
        if text:
            print(text)
    return objs


def tags(src):
    """{function name: (seg, off)} from /* @addr S:OOOO */ comments."""
    out = {}
    text = open(src, encoding='latin-1').read()
    for m in re.finditer(r'/\*\s*@addr\s+([0-9a-fA-F]+):([0-9a-fA-F]+)\s*\*/\s*\n'
                         r'[^\n(]*?\b(\w+)\s*\(', text):
        out[m.group(3)] = (int(m.group(1)), int(m.group(2), 16))
    return out


def functions(obj):
    """{public name: (code bytes, mask)} for the code publics of an object."""
    out = {}
    for _, code, pubs in modules(open(obj, 'rb').read()):
        for sname, (data, mask) in code.items():
            offs = sorted((off, n) for n, s, off in pubs if s == sname)
            for i, (off, n) in enumerate(offs):
                end = offs[i + 1][0] if i + 1 < len(offs) else len(data)
                out[n] = (data[off:end], mask[off:end])
    return out


def compare(fn, game, exe_prologue):
    data, mask = fn
    n = len(data)
    while n and data[n - 1] == 0x90 and mask[n - 1]:
        n -= 1                                   # alignment padding
    bad = []
    for k in range(n):
        if not mask[k]:
            continue
        g = game[k] if k < len(game) else None
        if g == data[k]:
            continue
        if exe_prologue and k == 1 and data[0] == 0x8c and data[k] == 0xd8 and g == 0xd0:
            continue
        bad.append(k)
    return n, bad


class Refs:
    """What the game's code refers to, to check object fixups against."""

    def __init__(self, data, exe):
        self.data = data
        self.h, self.segs = read_ne(data)
        base = os.path.basename(exe)
        self.addr = {}                       # symbol name (upper) -> (seg, off)
        inv = os.path.join(ROOT, 'inventory', base + '.tsv')
        if os.path.exists(inv):
            for line in open(inv):
                if line.startswith('#'):
                    continue
                r = line.rstrip('\n').split('\t')
                if r[4]:
                    sn, off = r[0].split(':')
                    self.addr[r[4].lstrip('_').upper()] = (int(sn), int(off, 16))
        names = os.path.join(ROOT, 'names', base + '.txt')
        if os.path.exists(names):
            for line in open(names, encoding='utf-8'):
                line = line.split('#')[0].strip()
                if line:
                    a, n = line.split(None, 1)
                    sel, off = a.split(':')
                    self.addr[n.split()[0].upper()] = ((int(sel, 16) - 0x1000) // 8 + 1, int(off, 16))
        imps = load_imports(os.path.join(ROOT, 'names', 'imports.txt'))
        self.site = {}                       # (seg, off) -> ('imp', NAME) | ('sel', seg)
        for sg, src, fl, sites, tgt in relocs(data):
            m = re.fullmatch(r'(\w+)\.(\d+)', tgt)
            if m and (m.group(1), int(m.group(2))) in imps:
                info = ('imp', imps[(m.group(1), int(m.group(2)))].upper())
            else:
                m = re.fullmatch(r'(\d+):([0-9a-f]{4})', tgt)
                info = ('sel', int(m.group(1))) if m and src == 2 else ('int', tgt)
            for a in sites:
                self.site[(sg['n'], a)] = info

    def target(self, name):
        n = name.lstrip('_').upper()
        m = re.fullmatch(r'G_(?:FP_)?([0-9A-F]{4})', n)
        if m:
            return (19, int(m.group(1), 16))
        m = re.fullmatch(r'FN_(\d+)_([0-9A-F]{4})', n)
        if m:
            return (int(m.group(1)), int(m.group(2), 16))
        return self.addr.get(n)

    def word(self, sn, off):
        s = self.segs[sn - 1]
        return struct.unpack_from('<H', self.data, s['file_off'] + off)[0]

    def check(self, objinfo, si, start, end, sn, goff):
        """Problems with the fixups of one function: list of strings."""
        segs, exts, _, fixes = objinfo
        body = segs[si - 1][1]
        bad = []
        for fsi, a, loc, tm, tidx, disp, segrel in fixes:
            if fsi != si or not start <= a < end or tm != 2:
                continue
            name = exts[tidx]
            g = goff + (a - start)                     # game offset of the site
            inplace = struct.unpack_from('<H', body, a)[0] if a + 2 <= len(body) else 0
            t = self.target(name)
            site = self.site.get((sn, g)) or self.site.get((sn, g + 2))
            if site and site[0] == 'imp':
                if site[1].lstrip('_') != name.lstrip('_').upper():
                    bad.append(f'+{a - start:#x} calls {name}, game calls {site[1]}')
                continue
            if t is None:
                continue                               # unknown symbol: not checked
            tsn, toff = t
            if not segrel:                             # near call: rel16
                if tsn != sn:
                    bad.append(f'+{a - start:#x} near call to {name} in another segment')
                    continue
                want = (toff - (g + 2)) & 0xffff
                got = self.word(sn, g)
                if want != got:
                    bad.append(f'+{a - start:#x} near call {name} -> {toff:04x}, '
                               f'game -> {(got + g + 2) & 0xffff:04x}')
                continue
            if loc in (1, 5, 3):                       # offset or far pointer
                want = (toff + inplace + disp) & 0xffff
                got = self.word(sn, g)
                if loc == 3 and tsn != 19:
                    want = (toff + disp) & 0xffff
                if want != got:
                    bad.append(f'+{a - start:#x} {name} -> {want:04x}, game {got:04x}')
                    continue
            if loc in (2, 3) and tsn != 19:            # selector part
                sel = self.site.get((sn, g + (2 if loc == 3 else 0)))
                if sel and sel[0] == 'sel' and sel[1] != tsn:
                    bad.append(f'+{a - start:#x} {name} in segment {tsn}, game segment {sel[1]}')
        return bad


def run(srcs, exe='unpacked/INSPACE.EXE', keep=False):
    """Compile and compare. Returns a list of dicts: src, name, seg, off,
    size (bytes compared, 0 if missing), bad (differing byte count, None
    if the function was not produced)."""
    data = open(exe, 'rb').read()
    h, segs = read_ne(data)
    is_exe = not h['flags'] & 0x8000              # NE flag: library (DLL)
    refs = Refs(data, exe)
    work = tempfile.mkdtemp(prefix='match-')
    results = []
    try:
        objs = compile_all(srcs, work)
        for src in srcs:
            have = {}
            pubs = {}
            if os.path.exists(objs[src]):
                have = {n.lstrip('_').upper(): f for n, f in functions(objs[src]).items()}
                objinfo = parse_fixups(objs[src])
                for n, si, off in objinfo[2]:
                    pubs[n.lstrip('_').upper()] = (si, off)
            for name, (sn, off) in tags(src).items():
                r = {'src': src, 'name': name, 'seg': sn, 'off': off, 'size': 0, 'bad': None}
                fn = have.get(name.upper())
                if fn is not None:
                    s = segs[sn - 1]
                    game = data[s['file_off'] + off:s['file_off'] + s['len']]
                    n, bad = compare(fn, game, is_exe)
                    refbad = []
                    if name.upper() in pubs:
                        si, start = pubs[name.upper()]
                        refbad = refs.check(objinfo, si, start, start + n, sn, off)
                    r.update(size=n, bad=len(bad) + len(refbad),
                             first=bad[0] if bad else None, refs=refbad)
                results.append(r)
    finally:
        if keep:
            print('work dir:', work)
        else:
            shutil.rmtree(work)
    return results


def main():
    args = sys.argv[1:]
    exe = 'unpacked/INSPACE.EXE'
    if '--exe' in args:
        i = args.index('--exe')
        exe = args[i + 1]
        del args[i:i + 2]
    srcs = [a for a in args if not a.startswith('--')]
    results = run(srcs, exe, '--keep' in args)
    for r in results:
        where = f"{r['seg']}:{r['off']:04x}"
        if r['bad'] is None:
            print(f"  {r['name']:32} {where:8} not in object")
        elif r['bad'] == 0:
            print(f"  {r['name']:32} {where:8} MATCH  ({r['size']} bytes)")
        elif r['first'] is None:
            print(f"  {r['name']:32} {where:8} WRONG REFERENCE: {r['refs'][0]}"
                  + (f" (+{len(r['refs']) - 1} more)" if len(r['refs']) > 1 else ''))
        else:
            pct = 100 * (r['size'] - r['bad']) / r['size']
            print(f"  {r['name']:32} {where:8} {pct:5.1f}%  first diff at +{r['first']:#x} "
                  f"({r['bad']} bytes differ)")
    matched = sum(1 for r in results if r['bad'] == 0)
    print(f'{matched}/{len(results)} functions match')
    return 0 if matched == len(results) else 1


if __name__ == '__main__':
    sys.exit(main())
