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

Environment: MSVC_DIR (default /home/user/toolchain/msvc, holding BIN, LIB,
INCLUDE), CFLAGS (default the flags confirmed for INSPACE.EXE).
"""
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from ne_info import read_ne          # noqa: E402
from omf_match import modules        # noqa: E402

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
        lines.append(f'cl /c /nologo {CFLAGS} /Fo{name}.OBJ {name}.C >> D:\\CL.TXT')
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


def run(srcs, exe='unpacked/INSPACE.EXE', keep=False):
    """Compile and compare. Returns a list of dicts: src, name, seg, off,
    size (bytes compared, 0 if missing), bad (differing byte count, None
    if the function was not produced)."""
    data = open(exe, 'rb').read()
    h, segs = read_ne(data)
    is_exe = not h['flags'] & 0x8000              # NE flag: library (DLL)
    work = tempfile.mkdtemp(prefix='match-')
    results = []
    try:
        objs = compile_all(srcs, work)
        for src in srcs:
            have = {}
            if os.path.exists(objs[src]):
                have = {n.lstrip('_').upper(): f for n, f in functions(objs[src]).items()}
            for name, (sn, off) in tags(src).items():
                r = {'src': src, 'name': name, 'seg': sn, 'off': off, 'size': 0, 'bad': None}
                fn = have.get(name.upper())
                if fn is not None:
                    s = segs[sn - 1]
                    game = data[s['file_off'] + off:s['file_off'] + s['len']]
                    n, bad = compare(fn, game, is_exe)
                    r.update(size=n, bad=len(bad), first=bad[0] if bad else None)
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
        else:
            pct = 100 * (r['size'] - r['bad']) / r['size']
            print(f"  {r['name']:32} {where:8} {pct:5.1f}%  first diff at +{r['first']:#x} "
                  f"({r['bad']} bytes differ)")
    matched = sum(1 for r in results if r['bad'] == 0)
    print(f'{matched}/{len(results)} functions match')
    return 0 if matched == len(results) else 1


if __name__ == '__main__':
    sys.exit(main())
