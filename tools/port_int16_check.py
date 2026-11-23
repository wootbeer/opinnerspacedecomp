#!/usr/bin/env python3
"""Check of tools/port_int16.py on the generated game code.

Takes every pure integer expression of the game code that is an if/while/
for condition or the right side of an assignment (no calls with side
effects inside, no nested assignments), replaces its operands (variables,
fields, array elements, calls) by parameters, and evaluates it

  * in Python under the 1994 rules (16-bit int, MSC conversions), on the
    text before the int16 pass, and
  * natively, compiled by the host C compiler (-fwrapv), both before and
    after the pass,

on random operand values (small numbers, range ends and uniform values).
Prints, per expression kind, how many expressions differ from the 1994
result before and after the pass.  After the pass none may differ.

    python3 -I tools/port_int16_check.py [--keep DIR] [segNN.c ...]
"""
import os
import random
import re
import subprocess
import sys
import tempfile
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from pycparser import c_ast  # noqa: E402

import port_int16 as pi  # noqa: E402
from port_int16 import S16, promote, usual, int_const, char_const  # noqa: E402

SAMPLES = 64
OPS = {'+', '-', '*', '/', '%', '<<', '>>', '&', '|', '^', '<', '>', '<=', '>=', '==', '!=', '&&', '||'}


class Invalid(Exception):
    pass


def wrap(v, t):
    b, s = t
    v &= (1 << b) - 1
    if s and v >= 1 << (b - 1):
        v -= 1 << b
    return v


def ref_eval(n, leaves, vals):
    """Value and 1994 type of expression n (MSC 16-bit rules)."""
    if id(n) in leaves:
        k, t = leaves[id(n)]
        return wrap(vals[k], t), promote(t)
    if isinstance(n, c_ast.Constant):
        if n.type == 'char':
            return char_const(n.value), S16
        v, t = int_const(n.value)
        return v, t
    if isinstance(n, c_ast.Cast):
        v, _ = ref_eval(n.expr, leaves, vals)
        t = CHK.ctype(n.to_type)[1]
        return wrap(v, t), promote(t)
    if isinstance(n, c_ast.UnaryOp):
        v, t = ref_eval(n.expr, leaves, vals)
        if n.op == '-':
            return wrap(-v, t), t
        if n.op == '~':
            return wrap(~v, t), t
        if n.op == '!':
            return int(v == 0), S16
        return v, t
    if isinstance(n, c_ast.TernaryOp):
        c, _ = ref_eval(n.cond, leaves, vals)
        a, ta = ref_eval(n.iftrue, leaves, vals)
        b, tb = ref_eval(n.iffalse, leaves, vals)
        t = usual(ta, tb)
        return wrap(a if c else b, t), t
    if isinstance(n, c_ast.BinaryOp):
        a, ta = ref_eval(n.left, leaves, vals)
        b, tb = ref_eval(n.right, leaves, vals)
        op = n.op
        if op == '&&':
            return int(bool(a) and bool(b)), S16
        if op == '||':
            return int(bool(a) or bool(b)), S16
        if op in ('<<', '>>'):
            t = promote(ta)
            if not 0 <= b < t[0]:
                raise Invalid
            a = wrap(a, t)
            return wrap(a << b if op == '<<' else a >> b, t), t
        t = usual(ta, tb)
        a, b = wrap(a, t), wrap(b, t)
        if op in ('<', '>', '<=', '>=', '==', '!='):
            return int({'<': a < b, '>': a > b, '<=': a <= b, '>=': a >= b,
                        '==': a == b, '!=': a != b}[op]), S16
        if op in ('/', '%'):
            if b == 0:
                raise Invalid
            q = abs(a) // abs(b)
            if (a < 0) != (b < 0):
                q = -q
            if q != wrap(q, t):
                raise Invalid       # divide overflow trapped in 1994
            return wrap(q if op == '/' else a - q * b, t), t
        v = {'+': a + b, '-': a - b, '*': a * b, '&': a & b, '|': a | b, '^': a ^ b}[op]
        return wrap(v, t), t
    raise Invalid


CHK = None


def collect(p):
    """(kind, root node, lvalue node or None, op) of candidate expressions."""
    out = []

    def visit(n):
        if isinstance(n, (c_ast.If, c_ast.While, c_ast.DoWhile)) and n.cond is not None:
            out.append(('condition', n.cond, None, None))
        elif isinstance(n, c_ast.For) and n.cond is not None:
            out.append(('condition', n.cond, None, None))
        elif isinstance(n, c_ast.Assignment):
            out.append(('assign', n.rvalue, n.lvalue, n.op))
        for _, c in n.children():
            visit(c)
    for fd in p.funcdefs:
        visit(fd.body)
    return out


def leaves_of(p, n, acc):
    """Fill acc with operand nodes; False if n is not a pure expression."""
    if isinstance(n, c_ast.Constant):
        return n.type in ('int', 'char')
    if isinstance(n, c_ast.BinaryOp) and n.op in OPS or \
            isinstance(n, c_ast.UnaryOp) and n.op in ('-', '~', '!', '+') or \
            isinstance(n, c_ast.TernaryOp):
        return all(leaves_of(p, c, acc) for _, c in n.children())
    if isinstance(n, c_ast.Cast):
        t = p.ctype(n.to_type)
        return t[0] == 'i' and leaves_of(p, n.expr, acc)
    x = p.info.get(id(n))
    if x is None or x.t is None or x.const or x.ct[0] != 'i':
        return False
    if has_side_effect(n):
        return False
    acc.append(n)
    return True


def has_side_effect(n):
    if isinstance(n, c_ast.Assignment) or isinstance(n, c_ast.UnaryOp) and n.op in ('++', '--', 'p++', 'p--'):
        return True
    if isinstance(n, c_ast.FuncCall):
        name = n.name.name if isinstance(n.name, c_ast.ID) else ''
        if not (pi.MARK.match(name) or name in ('LO16', 'HI16', 'LO8', 'HI8', 'LOWORD', 'HIWORD',
                                                'LOBYTE', 'HIBYTE', 'VIEW', 'rand', 'abs')):
            return True
    return any(has_side_effect(c) for _, c in n.children())


def render_span(p, a, b, repl):
    """Text [a, b) of the file with the pass's edits inside it, and the
    spans in repl (start -> (end, text)) replaced."""
    out = []
    pos = a
    edits = [e for e in p.edits if a <= e[0] and e[0] - e[2] <= b]
    for s, (e, txt) in repl.items():
        edits = [x for x in edits if not (s < x[0] < e or x[0] == s and x[2] < 0 or
                                          x[0] == e and x[2] < 0 and x[0] - x[2] <= e)]
        edits.append((s, 10 ** 7, -(e - s), txt))
    for q, order, neg, txt in sorted(edits, key=lambda x: (x[0], x[1])):
        if q < pos:
            raise ValueError('overlap')
        out.append(p.text[pos:q])
        out.append(txt)
        pos = q - neg
    out.append(p.text[pos:b])
    return ''.join(out)


def strip_edits(p):
    class P:
        pass
    q = P()
    q.text = p.text
    q.edits = [e for e in p.edits if e[1] == 10 ** 6]      # view markers only
    return q


def rand_val(rng, bits):
    r = rng.random()
    if r < 0.35:
        v = rng.randint(-20, 20)
    elif r < 0.55:
        v = rng.choice([0x7fff, 0x8000, 0xffff, 0x7ffe, 0x8001, 0x4000, 0x3fff, 0x100, 0xff, 0x80, 0x7f])
        v += rng.choice([0, 0, -1, 1])
    elif r < 0.7:
        v = rng.randint(-2000, 2000)
    else:
        v = rng.getrandbits(bits)
    return v & ((1 << bits) - 1)


def main(argv):
    global CHK
    keep = None
    if argv[:1] == ['--keep']:
        keep, argv = argv[1], argv[2:]
    files = argv or sorted(f for f in os.listdir(pi.GAME) if f.startswith('seg') and f.endswith('.c'))
    # the text the translator hands to the pass (with view markers)
    import port_translate as pt
    pre = {}
    real = pi.process

    def capture(fn, text):
        pre[fn] = text
        return text, Counter(), []
    pi.process = capture
    pt_out = pt.OUT
    tmp = tempfile.mkdtemp(prefix='int16check')
    pt.OUT = tmp
    import io
    import contextlib
    with contextlib.redirect_stdout(io.StringIO()):
        pt.main(files)
    pt.OUT = pt_out
    pi.process = real
    rng = random.Random(1994)
    cases = []
    for fn in files:
        real(fn, pre[fn])
        p = pi._PASS
        CHK = p
        for kind, root, lv, op in collect(p):
            acc = []
            if not leaves_of(p, root, acc):
                continue
            if lv is not None:
                lx = p.info.get(id(lv))
                if lx is None or lx.ct[0] != 'i' or has_side_effect(lv):
                    continue
            # the operand types: 1994 (view) and native (storage)
            leaves = {}
            params = []
            repl = {}
            ok = True
            for k, n in enumerate(acc):
                ct = p.info[id(n)].ct
                t1994 = ct[2] if len(ct) == 3 else ct[1]
                leaves[id(n)] = (k, t1994)
                s, e = p.span(n)
                repl[p.toks[s][2]] = (p.toks[e][3], 'p%d' % k)
                params.append(pi.TYPE_NAME[ct[1]] if ct[1] in pi.TYPE_NAME else None)
                ok = ok and params[-1] is not None
            if lv is not None:
                lct = p.info[id(lv)].ct
                lt1994 = lct[2] if len(lct) == 3 else lct[1]
                lnat = pi.TYPE_NAME.get(lct[1])
                ok = ok and lnat is not None
            if not ok:
                continue
            s, e = p.span(root)
            a, b = p.toks[s][2], p.toks[e][3]
            try:
                new = render_span(p, a, b, dict(repl))
                old = render_span(strip_edits(p), a, b, dict(repl))
            except ValueError:
                continue
            samples = []
            for _ in range(SAMPLES):
                vals = [rand_val(rng, leaves[id(n)][1][0]) for n in acc]
                lval = rand_val(rng, lt1994[0]) if lv is not None else 0
                try:
                    v, t = ref_eval(root, leaves, vals)
                    if lv is None:
                        res = int(v != 0)
                    elif op == '=':
                        res = wrap(v, lt1994)
                    else:
                        bop = op[:-1]
                        fake = c_ast.BinaryOp(bop, c_ast.ID('__lv'), c_ast.ID('__rv'))
                        lvs = {id(fake.left): (0, lt1994)}
                        tt = (t[0], t[1])
                        rl = {id(fake.left): (0, lt1994), id(fake.right): (1, tt)}
                        del lvs
                        r, _ = ref_eval(fake, rl, [lval, v & ((1 << t[0]) - 1)])
                        res = wrap(r, lt1994)
                except Invalid:
                    continue
                samples.append((vals, lval, res & ((1 << (lt1994[0] if lv is not None else 16)) - 1)))
            if not samples:
                continue
            line = p.text.count('\n', 0, a) + 1
            cases.append(dict(fn=fn, line=line, kind=kind if lv is None else 'assign' + op,
                              params=params, lnat=lnat if lv is not None else None, op=op,
                              lbits=lt1994[0] if lv is not None else 16,
                              new=new, old=old, samples=samples, changed=new != old))
    # C harness: one function per expression and version, reading its
    # operands from an array; the samples and 1994 results in tables
    src = ['#include <stdio.h>', '#include "game.h"', '']
    for i, c in enumerate(cases):
        decl = ''.join(' %s p%d = (%s)a[%d];' % (t, k, t, k) for k, t in enumerate(c['params']))
        if c['lnat']:
            decl += ' %s lv = (%s)a[%d];' % (c['lnat'], c['lnat'], len(c['params']))
        for tag, text in (('n', c['new']), ('o', c['old'])):
            if c['lnat']:
                body = 'lv %s (%s); return (long long)lv;' % (c['op'], text)
            else:
                body = 'return (%s) ? 1 : 0;' % text
            src.append('static long long %s%d(const long long *a) {%s %s }' % (tag, i, decl, body))
        rows = []
        for vals, lval, res in c['samples']:
            rows.append('{%s}' % ', '.join('%dLL' % v for v in vals + [lval, res]))
        src.append('static const long long s%d[][%d] = {%s};' % (i, len(c['params']) + 2, ', '.join(rows)))
    src.append('typedef long long (*F)(const long long *);')
    src.append('static const struct { F n, o; const long long *s; int rows, cols; unsigned long long mask; } T[] = {')
    for i, c in enumerate(cases):
        src.append('    {n%d, o%d, &s%d[0][0], %d, %d, %dULL},' % (i, i, i, len(c['samples']),
                                                              len(c['params']) + 2, (1 << c['lbits']) - 1))
    src.append('};')
    src.append('''int main(void) {
    for (unsigned i = 0; i < sizeof T / sizeof T[0]; i++) {
        int bn = 0, bo = 0;
        for (int r = 0; r < T[i].rows; r++) {
            const long long *a = T[i].s + r * T[i].cols;
            unsigned long long want = (unsigned long long)a[T[i].cols - 1] & T[i].mask;
            bn |= ((unsigned long long)T[i].n(a) & T[i].mask) != want;
            bo |= ((unsigned long long)T[i].o(a) & T[i].mask) != want;
        }
        if (bn) printf("n %u\\n", i);
        if (bo) printf("o %u\\n", i);
    }
    return 0;
}''')
    d = keep or tmp
    os.makedirs(d, exist_ok=True)
    cfile = os.path.join(d, 'int16check.c')
    with open(cfile, 'w') as f:
        f.write('\n'.join(src) + '\n')
    exe = os.path.join(d, 'int16check')
    subprocess.check_call(['cc', '-std=c99', '-O0', '-fwrapv', '-fsigned-char', '-w', '-I', pi.GAME, '-o', exe, cfile])
    out = subprocess.run([exe], capture_output=True, text=True).stdout.split()
    bad = {'n': set(), 'o': set()}
    for tag, i in zip(out[::2], out[1::2]):
        bad[tag].add(int(i))
    total = Counter()
    diff_old = Counter()
    diff_new = Counter()
    for i, c in enumerate(cases):
        total[c['kind']] += 1
        if i in bad['o']:
            diff_old[c['kind']] += 1
        if i in bad['n']:
            diff_new[c['kind']] += 1
            print('DIFFERS after the pass: %s:%d: %s' % (c['fn'], c['line'], c['new']))
    print('%-12s %7s %16s %15s' % ('kind', 'checked', 'differ before', 'differ after'))
    for k in sorted(total):
        print('%-12s %7d %16d %15d' % (k, total[k], diff_old[k], diff_new[k]))
    print('%-12s %7d %16d %15d' % ('total', sum(total.values()), sum(diff_old.values()),
                                   sum(diff_new.values())))
    print('expressions changed by the pass: %d; samples per expression: up to %d'
          % (sum(c['changed'] for c in cases), SAMPLES))
    return 1 if bad['n'] else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
