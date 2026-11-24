#!/usr/bin/env python3
"""Runs a script of ISPACE.DLL calls on the original DLL (emulated, emu.py)
and on the port (port_calls) and compares what they leave: results,
returned bitmaps pixel for pixel, palettes entry for entry.

usage: oracle.py SCRIPT [--port PATH] [--data DIR] [--show N]
  SCRIPT  one call per line: ORDINAL ARG...; ARG is a number, "text",
          @K (the result of call K, counted from 0) or DC (a screen DC);
          '#' starts a comment line.  Pseudo-ordinals name routines the
          DLL does not export (INTERNAL).
  --port  the port_calls executable (default build/dll_oracle/port_calls)
  --data  the game's files (default data/)
  --show  differences listed per call (default 5)
Exit status 1 when anything differs."""
import argparse
import os
import shlex
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from emu import IspaceEmu, ROOT  # noqa: E402

# Argument kinds per ordinal, in the DLL's (Pascal) order: w word,
# s far string, b byte (passed as a word).
ORDINALS = {1: 'wwswww', 3: 's', 4: 'wwwwwww', 5: '', 6: 'www', 12: 'wwswwwwwwbb', 1000: 'wwswww'}
# Pseudo-ordinal -> (segment, offset) of a C-convention routine: 1000 is
# 5:0000, the ship picture of the dialogs (pal, id, name, a, b, mode).
INTERNAL = {1000: (5, 0x0000)}


def parse_script(path):
    calls = []
    for line in open(path):
        if line.strip() and not line.lstrip().startswith('#'):
            p = shlex.split(line)
            calls.append((int(p[0]), p[1:]))
    return calls


def run_emu(calls, data_dir):
    e = IspaceEmu(data_dir)
    results, out = [], []
    for k, (ordinal, args) in enumerate(calls):
        words = []
        for kind, a in zip(ORDINALS[ordinal], args):
            if kind == 's':
                fp = e.far_string(a)
                words += [fp >> 16, fp & 0xffff] if ordinal not in INTERNAL else [fp & 0xffff, fp >> 16]
            elif a == 'DC':
                words.append(e.new_gdi('dc', bmp=None, pal=None, bk=0xffffff))
            elif a.startswith('@'):
                words.append(results[int(a[1:])])
            else:
                words.append(int(a, 0) & (0xff if kind == 'b' else 0xffff))
        if ordinal in INTERNAL:
            r = e.call(*INTERNAL[ordinal], words[::-1]) & 0xffff
        else:
            r = e.call_ordinal(ordinal, words) & 0xffff
        results.append(r)
        b = e.bitmap(r)
        pals = {i: e.palette(h) for i, h in enumerate(results) if e.palette(h)}
        out.append(dict(ret=r, bmp=(b['w'], b['h'], int(b['mono']), bytes(b['px'])) if b else None,
                        pals=pals))
    return out


def run_port(script, exe):
    env = dict(os.environ, SDL_VIDEODRIVER='dummy')
    text = subprocess.run([exe, script], env=env, capture_output=True, text=True, check=True).stdout
    out = []
    for line in text.splitlines():
        p = line.split()
        if p[0] == 'call':
            out.append(dict(ret=int(p[5]) & 0xffff, bmp=None, pals={}))
        elif p[0] == 'bmp':
            out[-1]['bmp'] = (int(p[1]), int(p[2]), int(p[3]), bytes.fromhex(p[4]))
        elif p[0] == 'pal':
            rgb = bytes.fromhex(p[2])
            out[-1]['pals'][int(p[1][1:])] = [tuple(rgb[3 * i:3 * i + 3]) for i in range(256)]
    return out


def compare(k, o, p, show):
    """Differences of call k as lines (none when they agree)."""
    diffs = []
    is_handle = o['bmp'] or p['bmp'] or k in o['pals'] or k in p['pals']
    if not is_handle and o['ret'] != p['ret']:
        diffs.append('result: DLL %d, port %d' % (o['ret'], p['ret']))
    if bool(o['bmp']) != bool(p['bmp']):
        diffs.append('bitmap returned: DLL %s, port %s' % (bool(o['bmp']), bool(p['bmp'])))
    elif o['bmp']:
        (w, h, m, opx), (pw, ph, pm, ppx) = o['bmp'], p['bmp']
        if (w, h, m) != (pw, ph, pm):
            diffs.append('bitmap: DLL %dx%d mono %d, port %dx%d mono %d' % (w, h, m, pw, ph, pm))
        else:
            bad = [i for i in range(len(opx)) if opx[i] != ppx[i]]
            if bad:
                diffs.append('bitmap: %d of %d pixels differ' % (len(bad), len(opx)))
                diffs += ['  (%d,%d) DLL %d port %d' % (i % w, i // w, opx[i], ppx[i]) for i in bad[:show]]
    for i in sorted(set(o['pals']) | set(p['pals'])):
        op, pp = o['pals'].get(i), p['pals'].get(i)
        if not op or not pp:
            diffs.append('palette @%d only in the %s' % (i, 'DLL' if op else 'port'))
            continue
        bad = [j for j in range(256) if op[j] != pp[j]]
        if bad:
            diffs.append('palette @%d: %d entries differ' % (i, len(bad)))
            diffs += ['  %d DLL %s port %s' % (j, op[j], pp[j]) for j in bad[:show]]
    return diffs


def main():
    ap = argparse.ArgumentParser(usage=__doc__)
    ap.add_argument('script')
    ap.add_argument('--port', default=os.path.join(ROOT, 'build', 'dll_oracle', 'port_calls'))
    ap.add_argument('--data', default=os.path.join(ROOT, 'data'))
    ap.add_argument('--show', type=int, default=5)
    a = ap.parse_args()
    calls = parse_script(a.script)
    unknown = sorted({o for o, _ in calls} - set(ORDINALS))
    if unknown:
        sys.exit('ordinals not supported: %s' % unknown)
    dll, port = run_emu(calls, a.data), run_port(a.script, a.port)
    failed = 0
    for k, (ordinal, args) in enumerate(calls):
        diffs = compare(k, dll[k], port[k], a.show)
        failed += bool(diffs)
        print('%3d ord %-2d %-40s %s' % (k, ordinal, ' '.join(args)[:40], 'differs' if diffs else 'same'))
        for d in diffs:
            print('      ' + d)
    print('%d of %d calls differ' % (failed, len(calls)))
    sys.exit(1 if failed else 0)


if __name__ == '__main__':
    main()
