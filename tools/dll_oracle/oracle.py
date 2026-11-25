#!/usr/bin/env python3
"""Runs a script of ISPACE.DLL calls on the original DLL (emulated, emu.py)
and on the port (port_calls) and compares what they leave: results,
returned bitmaps pixel for pixel, palettes entry for entry.

usage: oracle.py SCRIPT [--port PATH] [--data DIR] [--show N]
  SCRIPT  one call per line: ORDINAL ARG...; ARG is a number, "text",
          @K (the result of call K, counted from 0), DC (a screen DC),
          MDC (a memory DC with a 640x480 bitmap) or DC@K (a memory DC
          with call K's bitmap selected; the bitmap is compared after
          the call); '#' starts a comment line.  Pseudo-ordinals name routines the
          DLL does not export (INTERNAL).
  --port  the port_calls executable (default build/dll_oracle/port_calls)
  --data  the game's files (default data/)
  --show  differences listed per call (default 5)
Exit status 1 when anything differs."""
import argparse
import os
import struct
import shlex
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from emu import INI, IspaceEmu, ROOT, GetDlgItem, dialog_state, dialog_window, new_bitmap, new_dc  # noqa: E402

# Argument kinds per ordinal, in the DLL's (Pascal) order: w word,
# s far string, b byte (passed as a word), l long, P a POINT (the script
# gives X,Y), R the rectangle block
# of ordinal 32 (no script argument: a far pointer and a handle), p a
# far pointer to a word (the script gives its value; the words are
# compared after the call).
ORDINALS = {10: 'wwwwwww', 11: 'wwwl', 37: 'wwwl', 38: 'wwwl', 1001: 'ww', 1002: 'ww', 1: 'wwswww', 2: 'wwswwwwwwwbbbw', 3: 's', 4: 'wwwwwww', 5: '', 6: 'www', 12: 'wwswwwwwwbb', 1000: 'wwswww',
            7: 'lw', 8: 'Pwwl', 9: 'wPwllls', 14: 'wwwww', 15: 'wwwwwwwww', 18: 'wwwwww', 29: 'ppppppppwwwwpp', 32: 'wwRwlwlwwwwww', 33: 'wwlwlwws', 34: 'wwwwww', 35: 'wwwwww'}
# Ordinals after which the wave device's volume is compared (as outs).
SOUND = {7, 8, 9}
# Ordinals that return nothing (AX is left over).
VOID = {14}
# Pseudo-ordinal -> (segment, offset) of a C-convention routine: 1000 is
# 5:0000, the ship picture of the dialogs (pal, id, name, a, b, mode).
INTERNAL = {1000: (5, 0x0000)}
# Dialog procedures (hwnd, msg, wParam, lParam): the first argument DLGn
# makes a dialog from the language DLL's template n (the script sends its
# WM_INITDIALOG), DLG is the last one made; C<id>:<pos> is the long
# MAKELONG(pos, the control's handle) of a scroll message.  After each
# call the dialog's state is compared.  Pseudo-ordinals 1001 (id, 0/1)
# and 1002 (id, item) are the user checking a box and picking an item.
DIALOGS = {11, 37, 38, 1001, 1002}
USER = {1001: 'checked', 1002: 'sel'}


def parse_script(path):
    calls = []
    for line in open(path):
        if line.strip() and not line.lstrip().startswith('#'):
            p = shlex.split(line)
            calls.append((int(p[0]), p[1:]))
    return calls


def script_args(ordinal, args):
    """The kinds paired with the script's arguments (R takes none)."""
    out, it = [], iter(args)
    for kind in ORDINALS[ordinal]:
        out.append((kind, None if kind == 'R' else next(it, '0')))
    return out


def run_emu(calls, data_dir):
    e = IspaceEmu(data_dir)
    results, out, dlg = [], [], 0
    for k, (ordinal, args) in enumerate(calls):
        words, rect_block, mdc, ptrs, sdc = [], None, None, [], None
        if ordinal in USER:
            w = e.windows[GetDlgItem(e, dlg, int(args[0], 0))]
            w[USER[ordinal]] = int(args[1], 0)
            results.append(0)
            out.append(dict(ret=0, bmp=None, dcbmp=None, pals={}, rects=None, outs=[], texts=[],
                            state=dialog_state(e, dlg) + ini_state(e.ini)))
            continue
        for kind, a in script_args(ordinal, args):
            if kind == 'p':
                h = e.galloc(2)
                e.uc.mem_write(e.blocks[h][0] * 16, struct.pack('<h', int(a, 0)))
                ptrs.append(e.blocks[h][0] * 16)
                words += [e.blocks[h][0], 0]
            elif kind == 'P':
                x, y = (int(v, 0) for v in a.split(','))
                words += [y & 0xffff, x & 0xffff]
            elif kind == 'R':
                rect_block = e.galloc(8)
                words += [e.blocks[rect_block][0], 0, rect_block]
            elif kind == 's':
                fp = e.far_string(a)
                words += [fp >> 16, fp & 0xffff] if ordinal not in INTERNAL else [fp & 0xffff, fp >> 16]
            elif a.startswith('DLG'):
                dlg = dialog_window(e, int(a[3:])) if a[3:] else dlg
                words.append(dlg)
            elif a.startswith('C') and ':' in a:
                cid, pos = a[1:].split(':')
                words += [GetDlgItem(e, dlg, int(cid, 0)), int(pos, 0) & 0xffff]
            elif a == 'DC':
                words.append(new_dc(e))
            elif a.startswith('DC@'):
                sdc = new_dc(e)
                e.obj(sdc, 'dc')['bmp'] = results[int(a[3:])]
                words.append(sdc)
            elif a == 'MDC':
                mdc = new_dc(e)
                e.obj(mdc, 'dc')['bmp'] = new_bitmap(e, 640, 480)
                words.append(mdc)
            elif kind == 'l':
                v = int(a, 0) & 0xffffffff
                words += [v >> 16, v & 0xffff]
            elif a.startswith('@'):
                words.append(results[int(a[1:])])
            else:
                words.append(int(a, 0) & (0xff if kind == 'b' else 0xffff))
        try:
            if ordinal in INTERNAL:
                r = e.call(*INTERNAL[ordinal], words[::-1]) & 0xffff
            else:
                r = e.call_ordinal(ordinal, words) & 0xffff
        except RuntimeError as x:
            sys.exit('call %d (ordinal %d): %s' % (k, ordinal, x))
        results.append(r)
        b = e.bitmap(r) or (e.bitmap(e.obj(mdc, 'dc')['bmp']) if mdc else None)
        pals = {i: e.palette(h) for i, h in enumerate(results) if e.palette(h)}
        rects = None
        if rect_block is not None:
            lin = e.word(e.ds * 16 + 0xd16) * 16 + e.word(e.ds * 16 + 0xd14)
            n = e.blocks.get(e.word(e.ds * 16 + 0x1a36), [0, 0])[1] // 8
            rects = [struct.unpack('<4h', e.rd(lin + 8 * i, 8)) for i in range(n)]
        outs = [struct.unpack('<h', e.rd(q, 2))[0] for q in ptrs]
        if ordinal in SOUND:
            outs = [e.wave_volume & 0xffff, e.wave_volume >> 16]
        db = e.bitmap(e.obj(sdc, 'dc')['bmp']) if sdc else None
        out.append(dict(ret=r, bmp=(b['w'], b['h'], int(b['mono']), bytes(b['px'])) if b else None,
                        dcbmp=(db['w'], db['h'], int(db['mono']), bytes(db['px'])) if db else None,
                        pals=pals, rects=rects, texts=e.texts, outs=outs,
                        state=dialog_state(e, dlg) + ini_state(e.ini) if ordinal in DIALOGS else None))
        e.texts = []
    return out


def ini_state(ini):
    return ['ini %s=%s' % kv for kv in sorted(ini.items(), key=lambda kv: kv[0].upper())]


def run_port(script, exe, data_dir):
    """port_calls with a settings folder of its own holding the emulator's
    INSPACE.INI, and a sound device (SDL's dummy one)."""
    with tempfile.TemporaryDirectory() as home:
        os.makedirs(os.path.join(home, 'SDi', 'Inner Space'))
        with open(os.path.join(home, 'SDi', 'Inner Space', 'INSPACE.INI'), 'w') as f:
            f.write('[Inner Space]\n' + ''.join('%s=%s\n' % kv for kv in INI.items()))
        env = dict(os.environ, SDL_VIDEODRIVER='dummy', SDL_AUDIO_DRIVER='dummy', XDG_DATA_HOME=home,
                   INSPACE_DATA=data_dir)
        text = subprocess.run([exe, script], env=env, capture_output=True, text=True, check=True).stdout
    out = []
    for line in text.splitlines():
        p = line.split()
        if p[0] == 'call':
            out.append(dict(ret=int(p[5]) & 0xffff, bmp=None, dcbmp=None, pals={}, rects=None, outs=[], state=None))
        elif p[0] == 'state':
            out[-1]['state'] = (out[-1]['state'] or []) + [line[6:]]
        elif p[0] == 'outs':
            out[-1]['outs'] = [int(x) for x in p[1:]]
        elif p[0] == 'rects':
            v = [int(x) for x in p[1:]]
            out[-1]['rects'] = [tuple(v[i:i + 4]) for i in range(0, len(v), 4)]
        elif p[0] in ('bmp', 'dcbmp'):
            out[-1][p[0]] = (int(p[1]), int(p[2]), int(p[3]), bytes.fromhex(p[4]))
        elif p[0] == 'pal':
            rgb = bytes.fromhex(p[2])
            out[-1]['pals'][int(p[1][1:])] = [tuple(rgb[3 * i:3 * i + 3]) for i in range(256)]
    return out


def compare_bitmaps(what, ob, pb, show):
    if bool(ob) != bool(pb):
        return ['%s returned: DLL %s, port %s' % (what, bool(ob), bool(pb))]
    if not ob:
        return []
    (w, h, m, opx), (pw, ph, pm, ppx) = ob, pb
    if (w, h, m) != (pw, ph, pm):
        return ['%s: DLL %dx%d mono %d, port %dx%d mono %d' % (what, w, h, m, pw, ph, pm)]
    bad = [i for i in range(len(opx)) if opx[i] != ppx[i]]
    if not bad:
        return []
    return (['%s: %d of %d pixels differ' % (what, len(bad), len(opx))]
            + ['  (%d,%d) DLL %d port %d' % (i % w, i // w, opx[i], ppx[i]) for i in bad[:show]])


def compare(k, ordinal, o, p, show):
    """Differences of call k as lines (none when they agree)."""
    diffs = []
    is_handle = o['bmp'] or p['bmp'] or k in o['pals'] or k in p['pals'] or ordinal in VOID
    if not is_handle and o['ret'] != p['ret']:
        diffs.append('result: DLL %d, port %d' % (o['ret'], p['ret']))
    if o['outs'] != p['outs']:
        diffs.append('words: DLL %s, port %s' % (o['outs'], p['outs']))
    if o.get('state') != p.get('state'):
        os_, ps = o.get('state') or [], p.get('state') or []
        diffs += ['state: DLL %s | port %s' % (a, b) for a, b in zip(os_ + [''] * len(ps), ps + [''] * len(os_))
                  if a != b][:show]
    diffs += compare_bitmaps('bitmap', o['bmp'], p['bmp'], show)
    diffs += compare_bitmaps('DC bitmap', o['dcbmp'], p['dcbmp'], show)
    if o.get('rects') is not None or p.get('rects') is not None:
        orr, prr = o.get('rects') or [], p.get('rects') or []
        n = min(len(orr), len(prr))
        if orr[:n] != prr[:n]:
            diffs.append('rectangles: DLL %s, port %s' % (orr, prr))
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
    dll, port = run_emu(calls, a.data), run_port(a.script, a.port, a.data)
    failed = 0
    for k, (ordinal, args) in enumerate(calls):
        diffs = compare(k, ordinal, dll[k], port[k], a.show)
        failed += bool(diffs)
        print('%3d ord %-2d %-40s %s' % (k, ordinal, ' '.join(args)[:40], 'differs' if diffs else 'same'))
        for d in diffs:
            print('      ' + d)
    print('%d of %d calls differ' % (failed, len(calls)))
    sys.exit(1 if failed else 0)


if __name__ == '__main__':
    main()
