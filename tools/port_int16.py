#!/usr/bin/env python3
"""16-bit integer semantics for the generated port code.

The 1994 build (Microsoft C 8, medium model) had 16-bit int and unsigned
and 32-bit long; natively int is 32 bits.  This pass parses a generated
port/src/game/segNN.c (with game.h and win16api.h), computes for every
integer expression

  * its type under the 1994 rules (int16 / uint16 / int32 / uint32), and
  * an interval that contains its native value,

and inserts a cast where the native value can differ from the 1994 value
at a point where that difference matters.  Natively a 16-bit expression's
value is always congruent to the 1994 value modulo 2^16 (+ - * << & | ^ ~
and negation keep that), so it only matters where the whole value is used:

  compare, / % >>, condition, switch, widening to 32 bits (long operand,
  long variable or parameter, return from a long function, (long) cast),
  variadic argument, int parameter of the C library.

There the operand must lie in the range of the 1994 operation type;
otherwise it is cast to that type: `(int16_t)(a * b) < c` (the expression
overflowed 16 bits) or `(uint16_t)i < u` (the 1994 operation was
unsigned).  Constants are rewritten instead of cast (`u == -1` becomes
`u == 0xffff`).  Stores into 16-bit lvalues and 16-bit parameters truncate
natively as well and need nothing; neither do array indexes and pointer
offsets (the 1994 offset wrapped modulo 2^16 too, so an in-bounds native
index reaches the same element).

Accesses the translator marks `__view_T(...)` read a global or field
through a view whose signedness differs from the merged port type (an int
view of a HWND, a long view of a DWORD); the marker is removed and the
cast to T inserted where the 1994 signedness changes the result.

Used by tools/port_translate.py; checked by tools/port_int16_check.py.
Run alone on the generated files it must find nothing left to do:
    python3 -I tools/port_int16.py [segNN.c ...]
"""
import os
import re
import sys
from collections import Counter

from pycparser import c_ast, c_parser

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GAME = os.path.join(ROOT, 'port', 'src', 'game')

# ---------------------------------------------------------------------------
# Integer types: (bits, signed)
# ---------------------------------------------------------------------------

S8, U8, S16, U16, S32, U32 = (8, True), (8, False), (16, True), (16, False), (32, True), (32, False)
CNAME = {S8: 'char', U8: 'uint8_t', S16: 'int16_t', U16: 'uint16_t', S32: 'int32_t', U32: 'uint32_t'}


def rng(t):
    b, s = t
    return (-(1 << (b - 1)), (1 << (b - 1)) - 1) if s else (0, (1 << b) - 1)


def within(lo, hi, t):
    a, b = rng(t)
    return a <= lo and hi <= b


def promote(t):
    """1994 integer promotion: char/uchar -> int."""
    return S16 if t[0] < 16 else t


def usual(a, b):
    """1994 usual arithmetic conversions on promoted types."""
    a, b = promote(a), promote(b)
    if U32 in (a, b):
        return U32
    if S32 in (a, b):
        return S32
    if U16 in (a, b):
        return U16
    return S16


def native_wrap(lo, hi, t, ns=None):
    """Native value interval of a result whose 1994 type is t: the native
    operation is done in int (32-bit) unless unsigned long is involved
    (ns: native signedness)."""
    if ns is None:
        ns = t != U32
    nt = S32 if ns else U32
    if within(lo, hi, nt):
        return lo, hi
    return rng(nt)


PRIM_INT = {'char': S8, 'schar': S8, 'uchar': U8, 'short': S16, 'ushort': U16,
            'int': S16, 'uint': U16, 'long': S32, 'ulong': U32}
PORT_INT = {'int8_t': S8, 'uint8_t': U8, 'int16_t': S16, 'uint16_t': U16,
            'int32_t': S32, 'uint32_t': U32}
TYPE_NAME = {v: k for k, v in PORT_INT.items()}
MARK = re.compile(r'__view_(u?int\d+_t)(_arr)?$')


def marker(t, arr):
    """Marker the translator wraps around an access whose 1994 view type
    t differs in signedness from the port type; removed by this pass."""
    return '__view_%s%s' % (TYPE_NAME[t], '_arr' if arr else '')


# C types: ('i', (bits, signed)[, 1994 view type]), ('p', target), ('a', elem), ('s', fields),
# ('f', ret, params or None, variadic), ('v',), ('d',), ('?',)
UNKNOWN = ('?',)
BASE = {
    'char': S8, 'signed char': S8, 'unsigned char': U8,
    'short': S16, 'short int': S16, 'unsigned short': U16, 'int': S16,
    'unsigned': U16, 'unsigned int': U16, 'signed': S16,
    'long': S32, 'long int': S32, 'unsigned long': U32,
}

PRELUDE = '''typedef signed char int8_t; typedef unsigned char uint8_t;
typedef short int16_t; typedef unsigned short uint16_t;
typedef long int32_t; typedef unsigned long uint32_t;
typedef unsigned long uintptr_t; typedef unsigned short size_t;
typedef long ptrdiff_t; typedef long time_t; typedef long clock_t;
typedef char *va_list;
struct tm { short tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year,
            tm_wday, tm_yday, tm_isdst; };
short rand(void); void srand(unsigned short); short abs(short);
time_t time(time_t *); struct tm *localtime(const time_t *); clock_t clock(void);
'''
# libc functions whose native parameter is int (32 bits): the argument is
# not truncated natively, so it must already hold the 1994 value.
NATIVE_INT_PARAMS = {'abs', 'srand'}
# rand() is assumed to be the 1994 runtime's (0..0x7fff); abs() of -32768
# is treated as in range.
RESULT_RANGE = {'rand': (0, 0x7fff), 'abs': (0, 0x7fff)}

# Function-like macros of game.h / win16api.h, seen as calls.
MACRO_RESULT = {
    'LO16': S16, 'HI16': S16, 'LO8': S8, 'HI8': S8,
    'LOWORD': U16, 'HIWORD': U16, 'LOBYTE': U8, 'HIBYTE': U8,
    'MAKELONG': S32, 'MAKELPARAM': S32, 'RGB': U32, 'PALETTERGB': U32,
    'PALETTEINDEX': U32, 'GetRValue': U8, 'GetGValue': U8, 'GetBValue': U8,
    'va_arg': None, 'SC': S16,
}

# ---------------------------------------------------------------------------
# Source text helpers
# ---------------------------------------------------------------------------

TOK = re.compile(r'''
    (?P<ws>\s+) | (?P<com>/\*.*?\*/|//[^\n]*) |
    (?P<str>"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*') |
    (?P<num>\.?\d[\w.]*) | (?P<id>[A-Za-z_]\w*) |
    (?P<op>->|\+\+|--|<<=|>>=|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^]=|\.\.\.|.)
''', re.S | re.X)


def lex(text):
    toks = []
    for m in TOK.finditer(text):
        k = m.lastgroup
        if k in ('ws', 'com'):
            continue
        if k == 'op' and m.group() == '#':
            continue
        toks.append((k, m.group(), m.start(), m.end()))
    return toks


def strip_pp(text):
    """Blank preprocessor lines (and their continuations), keeping offsets."""
    out = []
    cont = False
    for ln in text.split('\n'):
        if cont or ln.lstrip().startswith('#'):
            cont = ln.endswith('\\')
            out.append(' ' * len(ln))
        else:
            out.append(ln)
    text = '\n'.join(out)
    return COMMENT.sub(lambda m: m.group() if m.group(1) is None else re.sub(r'[^\n]', ' ', m.group()), text)


COMMENT = re.compile(r'''"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*'|(/\*.*?\*/|//[^\n]*)''', re.S)

def mangle(text, mangled):
    """Replace the type arguments of VIEW/VIEWP (first) and va_arg (second)
    by identifiers of no greater length, padded with blanks and keeping
    newlines, so the text parses as C; mangled maps them to the type."""
    names = {}
    out = list(text)
    for m in re.finditer(r'\b(VIEWP?|va_arg)\(', text):
        i = m.end()
        if m.group(1) == 'va_arg':
            while text[i] != ',':
                i += 1
            i += 1
        depth = 0
        j = i
        while depth or text[j] not in ',)':
            depth += text[j] in '({'
            depth -= text[j] in ')}'
            j += 1
        t = text[i:j].strip()
        a = i + len(text[i:j]) - len(text[i:j].lstrip())
        if t not in names:
            names[t] = 'QV%d' % len(names)
            mangled[names[t]] = ' '.join(t.split())
        ident = names[t]
        first = text[a:j].split('\n')[0]
        assert len(first) >= len(ident), t
        for k in range(a, j):
            out[k] = '\n' if text[k] == '\n' else ' '
        out[a:a + len(ident)] = ident
    return ''.join(out)


def int_const(s):
    """(value, 1994 type) of an integer literal: decimal ones above 0x7fff
    are long, hex/octal ones up to 0xffff unsigned int."""
    t = s.lower()
    suf = re.search(r'[ul]*$', t).group()
    body = t[:len(t) - len(suf)]
    if body.startswith('0x'):
        v = int(body, 16)
        hexo = True
    elif len(body) > 1 and body.startswith('0'):
        v = int(body, 8)
        hexo = True
    else:
        v = int(body)
        hexo = False
    if 'l' in suf:
        ty = U32 if ('u' in suf or v > 0x7fffffff) else S32
    elif 'u' in suf:
        ty = U16 if v <= 0xffff else U32
    elif v <= 0x7fff:
        ty = S16
    elif hexo and v <= 0xffff:
        ty = U16
    elif v <= 0x7fffffff:
        ty = S32
    else:
        ty = U32
    return v, ty


ESC = {'n': 10, 't': 9, 'r': 13, '0': 0, '\\': 92, "'": 39, '"': 34, 'a': 7, 'b': 8, 'f': 12, 'v': 11}


def char_const(s):
    b = s[1:-1]
    if b.startswith('\\'):
        if b[1] == 'x':
            v = int(b[2:], 16)
        elif b[1].isdigit():
            v = int(b[1:], 8)
        else:
            v = ESC[b[1]]
    else:
        v = ord(b)
    if v > 127:
        v -= 256          # char is signed
    return v


# ---------------------------------------------------------------------------
# Expression info
# ---------------------------------------------------------------------------


class X:
    """Type and native value interval of an expression."""
    __slots__ = ('ct', 't', 'lo', 'hi', 'const', 'ns')

    def __init__(self, ct, t=None, lo=None, hi=None, const=False, ns=None):
        self.ct, self.t, self.lo, self.hi, self.const = ct, t, lo, hi, const
        # native signedness of a 32-bit value (16-bit ones promote to int)
        self.ns = (t != U32) if ns is None else ns


def xint(t, ct=None):
    """A value of integer type t (any value of the type)."""
    lo, hi = rng(t)
    return X(ct or ('i', t), promote(t), lo, hi)


NONINT = X(UNKNOWN)


class Pass:
    def __init__(self, headers):
        self.parser = c_parser.CParser()
        self.headers = headers
        self.typedefs = {}
        self.structs = {}
        self.globals = {}
        self.macros = {}
        self.macro_cache = {}

    # --- declarations ---------------------------------------------------

    def ctype(self, node):
        if isinstance(node, c_ast.TypeDecl):
            return self.ctype(node.type)
        if isinstance(node, c_ast.Typename):
            return self.ctype(node.type)
        if isinstance(node, c_ast.IdentifierType):
            names = [n for n in node.names if n not in ('const', 'volatile')]
            key = ' '.join(names)
            if key in self.typedefs:
                return self.typedefs[key]
            if key in BASE:
                return ('i', BASE[key])
            if key == 'void':
                return ('v',)
            if key in ('float', 'double'):
                return ('d',)
            return UNKNOWN
        if isinstance(node, c_ast.PtrDecl):
            return ('p', self.ctype(node.type))
        if isinstance(node, c_ast.ArrayDecl):
            return ('a', self.ctype(node.type))
        if isinstance(node, c_ast.FuncDecl):
            params, var = [], False
            if node.args:
                for p in node.args.params:
                    if isinstance(p, c_ast.EllipsisParam):
                        var = True
                        continue
                    params.append(self.ctype(p.type))
                if params == [('v',)]:
                    params = []
            return ('f', self.ctype(node.type), params, var)
        if isinstance(node, (c_ast.Struct, c_ast.Union)):
            if node.decls is None:
                return self.structs.get(node.name, ('s', {}))
            fields = {}
            st = ('s', fields)
            if node.name:
                if node.name in self.structs:
                    st = self.structs[node.name]
                    fields = st[1]
                else:
                    self.structs[node.name] = st
            for d in node.decls:
                if d.name:
                    fields[d.name] = self.ctype(d.type)
            return st
        if isinstance(node, c_ast.Enum):
            return ('i', S16)
        return UNKNOWN

    def declare_file(self, ext):
        for d in ext:
            if isinstance(d, c_ast.Typedef):
                self.typedefs[d.name] = self.ctype(d.type)
            elif isinstance(d, c_ast.Decl):
                t = self.ctype(d.type)
                if d.name:
                    self.globals[d.name] = t
            elif isinstance(d, c_ast.FuncDef):
                self.globals[d.decl.name] = self.ctype(d.decl.type)

    def load_headers(self):
        ast = self.parser.parse(self.headers, 'headers')
        self.declare_file(ast.ext)
        # typedef names only: enough to parse the files and macros
        self.short = ''.join('typedef int %s;\n' % k for k in self.typedefs)

    # --- per file ---------------------------------------------------------

    def run(self, fn, text):
        self.fn = fn
        self.text = text
        self.edits = []          # (pos, order, -length replaced, text)
        self.counts = Counter()
        self.notes = []
        self.mangled = {}
        self.depth = {}
        self.info = {}       # id(node) -> X, for tools/port_int16_check.py
        self.lvalues = set()     # nodes whose value is not used as a number
        self.file_macros = {}
        for m in re.finditer(r'^#define\s+(\w+)\s+(.*)$', text, re.M):
            self.file_macros[m.group(1)] = m.group(2).strip()
        src = mangle(strip_pp(text), self.mangled)
        assert len(src) == len(text) and src.count('\n') == text.count('\n')
        self.toks = lex(text)
        self.tok_at = {t[2]: i for i, t in enumerate(self.toks)}
        self.match = {}
        stack = []
        for i, t in enumerate(self.toks):
            if t[1] in '([{' and t[0] == 'op':
                stack.append(i)
            elif t[1] in ')]}' and t[0] == 'op':
                j = stack.pop()
                self.match[i], self.match[j] = j, i
        self.line_start = [0]
        for m in re.finditer('\n', text):
            self.line_start.append(m.end())
        full = self.short + '\n# 1 "%s"\n' % fn + src
        ast = self.parser.parse(full, "<typedefs>")
        mine = [d for d in ast.ext if d.coord and d.coord.file == fn]
        self.declare_file([d for d in mine if not isinstance(d, c_ast.FuncDef)])
        self.declare_file([d for d in mine if isinstance(d, c_ast.FuncDef)])
        self.fix_sc_macro()
        for i, t in enumerate(self.toks):
            if t[0] == 'id' and MARK.match(t[1]):
                j = self.match[i + 1]
                self.edits.append((t[2], 10 ** 6, -(self.toks[i + 1][3] - t[2]), ''))
                self.edits.append((self.toks[j][2], 10 ** 6, -1, ''))
        self.funcdefs = [d for d in mine if isinstance(d, c_ast.FuncDef)]
        for d in self.funcdefs:
            self.func(d)
        return self.render()

    def fix_sc_macro(self):
        # SC(n): (n) << g_9156 >> 1 shifted left in 16 bits before the
        # right shift in 1994.
        old = '#define SC(n) ((n) << g_9156 >> 1)'
        new = '#define SC(n) ((int16_t)((n) << g_9156) >> 1)'
        for m in re.finditer(re.escape(old), self.text):
            self.edits.append((m.start(), 0, -len(old), new))
            self.counts['shift right: SC() macro, 16-bit left shift first'] += 1

    def render(self):
        out = []
        pos = 0
        # replacements: (pos, order, -len, text); insertions have len 0
        for p, order, neg, txt in sorted(self.edits, key=lambda e: (e[0], e[1])):
            if p < pos:
                raise ValueError('%s: overlapping int16 edits at %d' % (self.fn, p))
            out.append(self.text[pos:p])
            out.append(txt)
            pos = p - neg
        out.append(self.text[pos:])
        return ''.join(out)

    # --- spans -------------------------------------------------------------

    def tok_index(self, coord):
        off = self.line_start[coord.line - 1] + coord.column - 1
        if off not in self.tok_at:
            raise ValueError('%s: no token at %s' % (self.fn, coord))
        return self.tok_at[off]

    def span(self, n):
        """(first, last) token index of an expression, with grouping
        parentheses around it."""
        s, e = self._span(n)
        while s > 0 and e + 1 < len(self.toks) and self.toks[s - 1][1] == '(' \
                and self.match.get(s - 1) == e + 1:
            p = self.toks[s - 2] if s >= 2 else None
            if p and (p[0] == 'id' or p[1] == ']'):
                break
            s, e = s - 1, e + 1
        return s, e

    def _span(self, n):
        if isinstance(n, (c_ast.ID, c_ast.Constant)):
            i = self.tok_index(n.coord)
            j = i
            if isinstance(n, c_ast.Constant) and n.type == 'string':
                while j + 1 < len(self.toks) and self.toks[j + 1][0] == 'str':
                    j += 1
            return i, j
        if isinstance(n, c_ast.BinaryOp):
            return self.span(n.left)[0], self.span(n.right)[1]
        if isinstance(n, c_ast.Assignment):
            return self.span(n.lvalue)[0], self.span(n.rvalue)[1]
        if isinstance(n, c_ast.TernaryOp):
            return self.span(n.cond)[0], self.span(n.iffalse)[1]
        if isinstance(n, c_ast.Cast):
            s, e = self.span(n.expr)
            return self.match[s - 1], e
        if isinstance(n, c_ast.UnaryOp):
            if n.op in ('p++', 'p--'):
                s, e = self.span(n.expr)
                return s, e + 1
            if n.op == 'sizeof':
                i = self.tok_index(n.coord)
                while self.toks[i][1] != 'sizeof':
                    i -= 1
                j = i + 1
                if self.toks[j][1] == '(' and isinstance(n.expr, c_ast.Typename):
                    return i, self.match[j]
                return i, self.span(n.expr)[1]
            s, e = self.span(n.expr)
            op = {'p++': '++', 'p--': '--'}.get(n.op, n.op)
            if self.toks[s - 1][1] != op:
                raise ValueError('%s: no operator %s before %s' % (self.fn, op, n.coord))
            return s - 1, e
        if isinstance(n, c_ast.FuncCall):
            s, e = self.span(n.name)
            return s, self.match[e + 1]
        if isinstance(n, c_ast.ArrayRef):
            s, e = self.span(n.name)
            return s, self.match[e + 1]
        if isinstance(n, c_ast.StructRef):
            s, _ = self.span(n.name)
            return s, self.tok_index(n.field.coord)
        if isinstance(n, c_ast.ExprList):
            return self.span(n.exprs[0])[0], self.span(n.exprs[-1])[1]
        if isinstance(n, c_ast.CompoundLiteral):
            i = self.tok_index(n.coord)
            return i, self.match[self.span(n.init.exprs[0])[0] - 1] if n.init.exprs else i
        raise ValueError('no span for %s' % type(n).__name__)

    # --- cast insertion ---------------------------------------------------

    def is_const(self, n):
        if isinstance(n, c_ast.Constant) and n.type in ('int', 'char'):
            return True
        return isinstance(n, c_ast.UnaryOp) and n.op in ('-', '+') and self.is_const(n.expr)

    def const_val(self, n):
        if isinstance(n, c_ast.Constant):
            if n.type == 'char':
                return char_const(n.value)
            return int_const(n.value)[0]
        v = self.const_val(n.expr)
        return -v if n.op == '-' else v

    def need(self, n, x, t, rule):
        """Make the native value of n (info x) equal its value in the 1994
        type t, by a cast to t when it can differ.  Returns the new info."""
        if x.t is None:
            return x
        if x.t[0] == 32 or t[0] == 32:
            # 32-bit: only the signedness can differ (a view of a DWORD as
            # long, or the reverse); 16-bit operands are widened elsewhere
            if x.t[0] < 32 or t[0] < 32 or x.ns == t[1]:
                return x
        elif within(x.lo, x.hi, t):
            return x
        s, e = self.span(n)
        lo, hi = rng(t)
        line = self.text.count('\n', 0, self.toks[s][2]) + 1
        if self.is_const(n) and t[0] == 16:
            v = self.const_val(n) & 0xffff
            if t[1] and v > 0x7fff:
                v -= 0x10000
            txt = ('0x%x' % v) if not t[1] else str(v)
            self.edits.append((self.toks[s][2], 0, -(self.toks[e][3] - self.toks[s][2]), txt))
            self.counts['%s: constant rewritten for %s' % (rule, CNAME[t])] += 1
            self.notes.append('%s:%d: %s: constant -> %s' % (self.fn, line, rule, txt))
            return X(x.ct, t, v, v)
        while isinstance(n, c_ast.FuncCall) and isinstance(n.name, c_ast.ID) and MARK.match(n.name.name):
            n = n.args.exprs[0]
        simple = isinstance(n, (c_ast.ID, c_ast.Constant, c_ast.FuncCall, c_ast.ArrayRef, c_ast.StructRef)) \
            or (isinstance(n, c_ast.UnaryOp) and n.op in ('p++', 'p--')) \
            or (self.toks[s][1] == '(' and self.match.get(s) == e)
        pre = '(%s)' % CNAME[t] if simple else '(%s)(' % CNAME[t]
        depth = self.depth.get(id(n), 0)
        self.edits.append((self.toks[s][2], depth, 0, pre))
        if not simple:
            self.edits.append((self.toks[e][3], 1000 - depth, 0, ')'))
        if t[0] == 32 or len(x.ct) == 3 and x.ct[0] == 'i':
            kind = 'view signedness'
        else:
            kind = 'overflow' if x.t == t else ('unsigned' if not t[1] else 'signed')
        if kind == 'overflow' and max(lo - x.lo, x.hi - hi) <= EDGE:
            self.counts['(of the overflow casts: only within 0x%x of the range ends)' % EDGE] += 1
        key = '%s: (%s), %s' % (rule, CNAME[t], kind)
        self.counts[key] += 1
        self.notes.append('%s:%d: %s: %s' % (self.fn, line, key,
                                             self.text[self.toks[s][2]:self.toks[e][3]].replace('\n', ' ')))
        if t[0] == 32:
            return X(x.ct, t, x.lo, x.hi, ns=t[1])
        return X(x.ct, promote(t), lo, hi)

    def need_own(self, n, x, rule):
        if x.t is None or x.t[0] == 32:
            return x
        return self.need(n, x, x.t, rule)

    # --- functions -------------------------------------------------------

    def func(self, fd):
        self.ret = self.ctype(fd.decl.type)[1]
        scope = [{}]
        ft = fd.decl.type
        if ft.args:
            for p in ft.args.params:
                if isinstance(p, c_ast.Decl) and p.name:
                    scope[0][p.name] = self.ctype(p.type)
        self.stmt(fd.body, scope)

    def lookup(self, name, scope):
        for s in reversed(scope):
            if name in s:
                return s[name]
        if name in self.globals:
            return self.globals[name]
        return None

    def stmt(self, n, scope):
        if n is None:
            return
        if isinstance(n, c_ast.Compound):
            scope.append({})
            for s in n.block_items or []:
                self.stmt(s, scope)
            scope.pop()
        elif isinstance(n, c_ast.Decl):
            t = self.ctype(n.type)
            scope[-1][n.name] = t
            if n.init is not None:
                self.init(n.init, t, scope)
        elif isinstance(n, c_ast.DeclList):
            for d in n.decls:
                self.stmt(d, scope)
        elif isinstance(n, c_ast.If):
            self.cond(n.cond, scope)
            self.stmt(n.iftrue, scope)
            self.stmt(n.iffalse, scope)
        elif isinstance(n, (c_ast.While, c_ast.DoWhile)):
            self.cond(n.cond, scope)
            self.stmt(n.stmt, scope)
        elif isinstance(n, c_ast.For):
            scope.append({})
            if isinstance(n.init, c_ast.DeclList):
                self.stmt(n.init, scope)
            elif n.init is not None:
                self.expr(n.init, scope)
            if n.cond is not None:
                self.cond(n.cond, scope)
            if n.next is not None:
                self.expr(n.next, scope)
            self.stmt(n.stmt, scope)
            scope.pop()
        elif isinstance(n, c_ast.Switch):
            x = self.expr(n.cond, scope)
            x = self.need_own(n.cond, x, 'switch value')
            self.cases(n.stmt, x.t)
            self.stmt(n.stmt, scope)
        elif isinstance(n, (c_ast.Case,)):
            for s in n.stmts or []:
                self.stmt(s, scope)
        elif isinstance(n, c_ast.Default):
            for s in n.stmts or []:
                self.stmt(s, scope)
        elif isinstance(n, c_ast.Label):
            self.stmt(n.stmt, scope)
        elif isinstance(n, c_ast.Return):
            if n.expr is not None:
                x = self.expr(n.expr, scope)
                if self.ret[0] == 'i':
                    self.store(n.expr, x, self.ret[1], 'return long')
        elif isinstance(n, (c_ast.Goto, c_ast.Break, c_ast.Continue, c_ast.EmptyStatement)):
            pass
        elif isinstance(n, c_ast.Node):
            self.expr(n, scope)

    def cases(self, n, t):
        """case labels are converted to the promoted switch type."""
        if n is None or t is None:
            return
        if isinstance(n, c_ast.Case):
            if self.is_const(n.expr):
                v = self.const_val(n.expr)
                if not within(v, v, t):
                    self.need(n.expr, X(('i', t), t, v, v), t, 'case label')
            for s in n.stmts or []:
                self.cases(s, t)
            return
        if isinstance(n, c_ast.Switch):
            return
        for _, c in n.children():
            self.cases(c, t)

    def init(self, n, t, scope):
        if isinstance(n, c_ast.InitList):
            for e in n.exprs:
                et = t[1] if t[0] == 'a' else UNKNOWN
                self.init(e, et, scope)
            return
        x = self.expr(n, scope)
        if t[0] == 'i':
            self.store(n, x, t[1], 'store to long')

    def store(self, n, x, t, rule):
        """Conversion as by assignment to integer type t."""
        if t[0] == 32 and x.t is not None and x.t[0] < 32:
            self.need_own(n, x, rule)

    def cond(self, n, scope):
        x = self.expr(n, scope)
        return self.truth(n, x)

    def truth(self, n, x):
        # only zero or not matters: a native value congruent modulo 2^16
        # with the 1994 value and within +-0xffff is zero when it is
        if x.t is None or x.t[0] == 32 or -0xffff <= x.lo and x.hi <= 0xffff:
            return x
        return self.need_own(n, x, 'condition')

    # --- expressions --------------------------------------------------------

    def ident(self, n, scope):
        t = self.lookup(n.name, scope)
        if t is None:
            mac = self.file_macros.get(n.name) or self.macros.get(n.name)
            if mac is not None:
                return self.macro_value(n.name, mac)
            UNRESOLVED[n.name] += 1
            return NONINT
        return self.of_type(t)

    def of_type(self, t):
        if t[0] == 'i':
            if len(t) == 3:      # 1994 view type differs from the port type
                lo, hi = rng(t[1])
                return X(t, promote(t[2]), lo, hi, ns=t[1] != U32)
            return xint(t[1], ct=t)
        return X(t)

    def macro_value(self, name, text):
        if name in self.macro_cache:
            return self.macro_cache[name]
        x = NONINT
        try:
            ast = self.parser.parse(self.short + '\nvoid __m(void) { (%s); }\n' % text, 'macro')
            e = ast.ext[-1].body.block_items[0]
            x = self.eval_const(e)
        except Exception:
            pass
        self.macro_cache[name] = x
        return x

    def eval_const(self, n):
        """Info of a constant expression in a macro (no edits)."""
        if isinstance(n, c_ast.Constant):
            return self.constant(n)
        if isinstance(n, c_ast.ID):
            mac = self.file_macros.get(n.name) or self.macros.get(n.name)
            return self.macro_value(n.name, mac) if mac else NONINT
        if isinstance(n, c_ast.UnaryOp) and n.op == '-':
            x = self.eval_const(n.expr)
            if x.t is None:
                return x
            return X(x.ct, x.t, -x.hi, -x.lo, True)
        if isinstance(n, c_ast.Cast):
            x = self.eval_const(n.expr)
            t = self.ctype(n.to_type)
            if t[0] == 'i' and x.t is not None:
                v = x.lo & ((1 << t[1][0]) - 1)
                if t[1][1] and v >= 1 << (t[1][0] - 1):
                    v -= 1 << t[1][0]
                return X(t, promote(t[1]), v, v, True)
            return X(t)
        if isinstance(n, c_ast.BinaryOp) and n.op in ('+', '|', '-'):
            a, b = self.eval_const(n.left), self.eval_const(n.right)
            if a.t is None or b.t is None:
                return NONINT
            v = {'+': a.lo + b.lo, '|': a.lo | b.lo, '-': a.lo - b.lo}[n.op]
            return X(('i', usual(a.t, b.t)), usual(a.t, b.t), v, v, True)
        return NONINT

    def constant(self, n):
        if n.type == 'char':
            v = char_const(n.value)
            return X(('i', S16), S16, v, v, True)
        if n.type == 'string':
            return X(('p', ('i', S8)))
        if n.type in ('float', 'double'):
            return X(('d',))
        v, t = int_const(n.value)
        return X(('i', t), t, v, v, True)

    def deref(self, ct):
        if ct[0] in ('p', 'a'):
            return ct[1]
        return UNKNOWN

    def field_type(self, st, name):
        if st[0] == 's':
            return st[1].get(name, UNKNOWN)
        return UNKNOWN

    def expr(self, n, scope, depth=0):
        self.depth[id(n)] = depth
        x = self._expr(n, scope, depth + 1)
        self.info[id(n)] = x
        return x

    def _expr(self, n, scope, d):
        if isinstance(n, c_ast.Constant):
            return self.constant(n)
        if isinstance(n, c_ast.ID):
            return self.ident(n, scope)
        if isinstance(n, c_ast.ArrayRef):
            a = self.expr(n.name, scope, d)
            i = self.expr(n.subscript, scope, d)
            if a.t is not None and i.t is None:      # 2[a]
                a, i = i, a
            # no cast: the 1994 index wraps modulo 2^16 together with the
            # near/far offset, so an in-bounds native index reaches the
            # same element
            return self.of_type(self.deref(a.ct))
        if isinstance(n, c_ast.StructRef):
            s = self.expr(n.name, scope, d)
            st = self.deref(s.ct) if n.type == '->' else s.ct
            return self.of_type(self.field_type(st, n.field.name))
        if isinstance(n, c_ast.Cast):
            t = self.ctype(n.to_type)
            if t[0] == 'i' and t[1][0] == 8:
                self.lvalues.add(id(n.expr))     # only the low byte is used
            x = self.expr(n.expr, scope, d)
            if t[0] == 'i':
                if t[1][0] == 32:
                    self.need_own(n.expr, x, '(long) cast')
                    if x.t is not None and within(x.lo, x.hi, t[1]):
                        return X(t, t[1], x.lo, x.hi)
                    return xint(t[1], ct=t)
                if x.t is not None and within(x.lo, x.hi, t[1]):
                    return X(t, promote(t[1]), x.lo, x.hi)
                return xint(t[1], ct=t)
            return X(t)
        if isinstance(n, c_ast.UnaryOp):
            return self.unary(n, scope, d)
        if isinstance(n, c_ast.BinaryOp):
            return self.binary(n, scope, d)
        if isinstance(n, c_ast.Assignment):
            return self.assign(n, scope, d)
        if isinstance(n, c_ast.TernaryOp):
            self.cond(n.cond, scope)
            a = self.expr(n.iftrue, scope, d)
            b = self.expr(n.iffalse, scope, d)
            if a.t is None or b.t is None:
                return a if a.t is None else b
            t = usual(a.t, b.t)
            if t[0] == 32:
                a = self.need_own(n.iftrue, a, 'widen to long')
                b = self.need_own(n.iffalse, b, 'widen to long')
            return X(('i', t), t, min(a.lo, b.lo), max(a.hi, b.hi), ns=a.ns and b.ns)
        if isinstance(n, c_ast.FuncCall):
            return self.call(n, scope, d)
        if isinstance(n, c_ast.ExprList):
            x = NONINT
            for e in n.exprs:
                x = self.expr(e, scope, d)
            return x
        if isinstance(n, c_ast.CompoundLiteral):
            t = self.ctype(n.type)
            self.init(n.init, t, scope)
            return X(t)
        if isinstance(n, c_ast.InitList):
            for e in n.exprs:
                self.expr(e, scope, d)
            return NONINT
        if isinstance(n, c_ast.Typename):
            return NONINT
        return NONINT

    def unary(self, n, scope, d):
        op = n.op
        if op == 'sizeof':
            if not isinstance(n.expr, c_ast.Typename):
                pass   # not evaluated
            return X(('i', U16), U16, 0, 0xffff)
        if op in ('&', '++', '--', 'p++', 'p--'):
            self.lvalues.add(id(n.expr))
        x = self.expr(n.expr, scope, d)
        if op == '&':
            return X(('p', x.ct))
        if op == '*':
            return self.of_type(self.deref(x.ct))
        if op in ('++', '--', 'p++', 'p--'):
            if x.ct[0] == 'i':
                return self.of_type(x.ct)
            return X(x.ct)
        if x.t is None:
            if op == '!':
                return X(('i', S16), S16, 0, 1)
            return x
        if op == '!':
            self.truth(n.expr, x)
            return X(('i', S16), S16, 0, 1)
        if op == '-':
            lo, hi = native_wrap(-x.hi, -x.lo, x.t, x.ns)
            return X(('i', x.t), x.t, lo, hi, x.const, x.ns)
        if op == '~':
            lo, hi = native_wrap(-x.hi - 1, -x.lo - 1, x.t, x.ns)
            return X(('i', x.t), x.t, lo, hi, x.const, x.ns)
        if op == '+':
            return x
        return NONINT

    def binary(self, n, scope, d):
        op = n.op
        if op in ('&&', '||'):
            self.cond(n.left, scope)
            self.cond(n.right, scope)
            return X(('i', S16), S16, 0, 1)
        a = self.expr(n.left, scope, d)
        b = self.expr(n.right, scope, d)
        if a.t is None or b.t is None:
            # pointer arithmetic / comparison
            if op in ('+', '-') and a.t is None and b.t is not None:
                return X(a.ct)
            if op == '+' and b.t is None and a.t is not None:
                return X(b.ct)
            if op == '-' and a.ct[0] in ('p', 'a') and b.ct[0] in ('p', 'a'):
                return X(('i', S16), S16, -0x8000, 0x7fff)
            if op in ('<', '>', '<=', '>=', '==', '!='):
                return X(('i', S16), S16, 0, 1)
            return NONINT
        if op in ('<<', '>>'):
            # shift counts are small; one that overflowed would be
            # meaningless either way
            t = a.t
            if op == '>>':
                a = self.need(n.left, a, t, 'shift right')
                c0, c1 = max(b.lo, 0), min(b.hi, 31)
                if c0 > c1:
                    c0 = c1 = 0
                vals = [a.lo >> c0, a.lo >> c1, a.hi >> c0, a.hi >> c1]
                return X(('i', t), t, min(vals), max(vals), ns=a.ns)
            c0, c1 = max(b.lo, 0), min(b.hi, 31)
            if c0 > c1:
                c0 = c1 = 0
            vals = [a.lo << c0, a.lo << c1, a.hi << c0, a.hi << c1]
            lo, hi = native_wrap(min(vals), max(vals), t, a.ns)
            return X(('i', t), t, lo, hi, ns=a.ns)
        t = usual(a.t, b.t)
        if t[0] == 32:
            a = self.need_own(n.left, a, 'widen to long')
            b = self.need_own(n.right, b, 'widen to long')
        if op in ('<', '>', '<=', '>=', '==', '!='):
            if op in ('==', '!=') and t[0] == 16 and max(a.hi, b.hi) - min(a.lo, b.lo) <= 0xffff:
                pass     # congruent values within one 2^16 window: same equality
            elif t[0] == 16:
                a = self.need(n.left, a, t, 'compare')
                b = self.need(n.right, b, t, 'compare')
            elif op not in ('==', '!='):
                a, b = self.sign32(n, a, b, t, 'compare')
            return X(('i', S16), S16, 0, 1)
        if op in ('/', '%'):
            rule = 'divide' if op == '/' else 'modulo'
            if t[0] == 16:
                a = self.need(n.left, a, t, rule)
                b = self.need(n.right, b, t, rule)
            else:
                a, b = self.sign32(n, a, b, t, rule)
            lo, hi = self.divmod_range(op, a, b, t)
            if t[0] == 16:
                # -32768 / -1 trapped (divide overflow) in 1994
                lo, hi = max(lo, rng(t)[0]), min(hi, rng(t)[1])
            return X(('i', t), t, lo, hi, ns=a.ns and b.ns)
        ns = a.ns and b.ns
        lo, hi = self.arith(op, a, b, t)
        lo, hi = native_wrap(lo, hi, t, ns)
        return X(('i', t), t, lo, hi, ns=ns)

    def sign32(self, n, a, b, t, rule):
        """A sign-sensitive operation in 32 bits: natively it is unsigned
        when an operand is a native uint32_t, in 1994 when the 1994 type
        t is unsigned long.  Cast the operand that makes them differ."""
        if (a.ns and b.ns) == t[1]:
            return a, b
        if t[1]:     # 1994 signed, native unsigned
            if not a.ns:
                a = self.need(n.left, a, t, rule)
            if not b.ns:
                b = self.need(n.right, b, t, rule)
            return a, b
        # 1994 unsigned, native signed: one 32-bit operand to uint32_t
        if a.t[0] == 32 and not a.const:
            a = self.need(n.left, a, t, rule)
        elif b.t[0] == 32:
            b = self.need(n.right, b, t, rule)
        return a, b

    def divmod_range(self, op, a, b, t):
        parts = []
        if b.lo <= -1:
            parts.append((b.lo, min(b.hi, -1)))
        if b.hi >= 1:
            parts.append((max(b.lo, 1), b.hi))
        if not parts:
            return rng(t)
        if op == '/':
            vals = []
            for c0, c1 in parts:
                for x in (a.lo, a.hi):
                    for y in (c0, c1):
                        q = abs(x) // abs(y)
                        vals.append(q if (x >= 0) == (y > 0) else -q)
            return native_wrap(min(vals), max(vals), t)
        m = max(abs(b.lo), abs(b.hi))
        lo = max(a.lo, -(m - 1)) if a.lo < 0 else 0
        hi = min(a.hi, m - 1) if a.hi > 0 else 0
        return lo, hi

    def arith(self, op, a, b, t):
        if op == '+':
            return a.lo + b.lo, a.hi + b.hi
        if op == '-':
            return a.lo - b.hi, a.hi - b.lo
        if op == '*':
            v = [a.lo * b.lo, a.lo * b.hi, a.hi * b.lo, a.hi * b.hi]
            return min(v), max(v)
        if op in ('&', '|', '^'):
            if op == '&' and (a.lo >= 0 or b.lo >= 0):
                if a.lo >= 0 and b.lo >= 0:
                    return 0, min(a.hi, b.hi)
                return 0, a.hi if a.lo >= 0 else b.hi
            if a.lo >= 0 and b.lo >= 0:
                k = max(a.hi.bit_length(), b.hi.bit_length())
                return 0, (1 << k) - 1
            k = max(max(abs(a.lo), abs(a.hi)).bit_length(), max(abs(b.lo), abs(b.hi)).bit_length()) + 1
            return -(1 << (k - 1)), (1 << (k - 1)) - 1
        return rng(t)

    def assign(self, n, scope, d):
        self.lvalues.add(id(n.lvalue))
        lv = self.expr(n.lvalue, scope, d)
        r = self.expr(n.rvalue, scope, d)
        if lv.ct[0] != 'i':
            return X(lv.ct)
        lt = lv.ct[1]
        res = self.of_type(lv.ct)
        if n.op == '=':
            self.store(n.rvalue, r, lt, 'store to long')
            return res
        if r.t is None:
            return res
        op = n.op[:-1]
        if op in ('<<', '>>'):
            if op == '>>' and lv.t != promote(lt):
                self.unfixed(n, 'compound >>= through a view of other signedness')
            return res
        t = usual(lv.t, r.t)
        if t[0] == 32:
            self.need_own(n.rvalue, r, 'widen to long')
        elif op in ('/', '%'):
            self.need(n.rvalue, r, t, 'divide' if op == '/' else 'modulo')
            if not within(lv.lo, lv.hi, t):
                self.unfixed(n, 'compound %s: the 1994 operation type is %s' % (n.op, CNAME[t]))
        return res

    def unfixed(self, n, msg):
        line = self.text.count('\n', 0, self.toks[self.span(n)[0]][2]) + 1
        self.notes.append('%s:%d: UNFIXED %s' % (self.fn, line, msg))
        self.counts['UNFIXED ' + msg.split(':')[0]] += 1

    def call(self, n, scope, d):
        name = n.name.name if isinstance(n.name, c_ast.ID) else None
        args = n.args.exprs if n.args else []
        m = MARK.match(name or '')
        if m and len(args) == 1:
            vt = PORT_INT[m.group(1)]
            x = self.expr(args[0], scope, d)
            ct = x.ct
            if m.group(2):
                if ct[0] in ('a', 'p') and ct[1][0] == 'i':
                    return X((ct[0], ('i', ct[1][1], vt)))
                return x
            if ct[0] == 'i' and vt[0] == 8:
                # char seen as unsigned char or the reverse: every value
                # use differs, so cast at the access
                if id(n) in self.lvalues:
                    return X(('i', ct[1]), promote(ct[1]), x.lo, x.hi)
                return self.need(n, X(('i', ct[1], vt), S16, x.lo, x.hi), vt, 'char view')
            if ct[0] == 'i':
                return X(('i', ct[1], vt), promote(vt), x.lo, x.hi, ns=x.ns)
            return x
        if name in ('VIEW', 'VIEWP') and args and isinstance(args[0], c_ast.ID) and args[0].name in self.mangled:
            for a in args[1:]:
                self.expr(a, scope, d)
            ty = self.parse_type(self.mangled[args[0].name])
            if name == 'VIEWP':
                return X(ty)
            return self.of_type(ty)
        if name == 'va_arg' and len(args) == 2 and isinstance(args[1], c_ast.ID) and args[1].name in self.mangled:
            ty = self.parse_type(self.mangled[args[1].name])
            if ty[0] == 'i' and ty[1][0] < 32 and self.mangled[args[1].name] != 'int':
                # va_arg of a type narrower than int is undefined (gcc makes
                # it abort): read the promoted int and truncate it
                s, e = self.span(n)
                a = self.toks[s][2]
                text = '(%s)va_arg(%s, int)' % (self.mangled[args[1].name],
                                                self.text[self.toks[s + 2][2]:self.toks[s + 2][3]])
                self.edits.append((a, 0, -(self.toks[e][3] - a), text))
                self.counts['va_arg of a 16-bit type: (T)va_arg(ap, int)'] += 1
            return self.of_type(ty)
        if name in ('min', 'max') and self.lookup(name, scope) is None:
            a = self.expr(args[0], scope, d)
            b = self.expr(args[1], scope, d)
            if a.t is None or b.t is None:
                return a
            t = usual(a.t, b.t)
            if t[0] == 32:
                a = self.need_own(args[0], a, 'widen to long')
                b = self.need_own(args[1], b, 'widen to long')
            else:
                a = self.need(args[0], a, t, 'compare')
                b = self.need(args[1], b, t, 'compare')
            return X(('i', t), t, min(a.lo, b.lo), max(a.hi, b.hi))
        if name in MACRO_RESULT and self.lookup(name, scope) is None:
            xs = [self.expr(a, scope, d) for a in args]
            if name == 'HIWORD' and xs:
                self.need_own(args[0], xs[0], 'widen to long')
            t = MACRO_RESULT[name]
            if t is None:
                return NONINT
            if name == 'SC':
                if xs and xs[0].t and xs[0].t[0] == 32:
                    self.unfixed(n, 'SC() of a long value (the macro casts to int16_t)')
                return X(('i', S16), S16, -0x4000, 0x3fff)
            return xint(t)
        if name == 'MAKEPOINT':
            for a in args:
                self.expr(a, scope, d)
            return X(self.typedefs.get('POINT', UNKNOWN))
        f = self.expr(n.name, scope, d)
        ft = f.ct
        if ft[0] == 'p':
            ft = ft[1]
        params, var, ret = None, False, UNKNOWN
        if ft[0] == 'f':
            ret, params, var = ft[1], ft[2], ft[3]
        for i, a in enumerate(args):
            x = self.expr(a, scope, d)
            if x.t is None:
                continue
            if params is not None and i < len(params):
                p = params[i]
                if p[0] == 'i':
                    if name in NATIVE_INT_PARAMS:
                        self.need(a, x, promote(p[1]), 'libc int argument')
                    else:
                        self.store(a, x, p[1], 'long argument')
            elif not var:
                self.need_own(a, x, 'unprototyped argument')
            # variadic: the 1994 callee read 16 bits of an int argument; the
            # native callee must read an int and truncate (va_arg below)
        if ret[0] == 'i':
            if name in RESULT_RANGE:
                lo, hi = RESULT_RANGE[name]
                return X(ret, promote(ret[1]), lo, hi)
            return xint(ret[1], ct=ret)
        return X(ret)

    def parse_type(self, text):
        key = ('type', text)
        if key not in self.macro_cache:
            decl = text.replace('(*)', '(*__t)', 1) if '(*)' in text else text + ' __t'
            ast = self.parser.parse(self.short + '\n%s;\n' % decl, 'type')
            self.macro_cache[key] = self.ctype(ast.ext[-1].type)
        return self.macro_cache[key]


def header_text():
    parts = [PRELUDE]
    macros = {}
    for h in ('win16api.h', 'game.h'):
        with open(os.path.join(GAME, h)) as f:
            t = f.read()
        for m in re.finditer(r'^#define\s+(\w+)\s+(.*)$', t, re.M):
            macros[m.group(1)] = m.group(2).strip()
        parts.append(strip_pp(t))
    text = '\n'.join(parts)
    return text, macros


_PASS = None
EDGE = 0x100        # for the count of casts needed only near the range ends
UNRESOLVED = Counter()


def process(fn, text):
    """Returns (new text, Counter of casts by kind, notes)."""
    global _PASS
    if _PASS is None:
        h, macros = header_text()
        _PASS = Pass(h)
        _PASS.macros = macros
        _PASS.load_headers()
    p = _PASS
    saved = dict(p.globals)
    try:
        new = p.run(fn, text)
    finally:
        p.globals = saved
    return new, p.counts, p.notes


def main(argv):
    files = argv or sorted(f for f in os.listdir(GAME) if f.startswith('seg') and f.endswith('.c'))
    total = Counter()
    for fn in files:
        with open(os.path.join(GAME, fn)) as f:
            text = f.read()
        new, counts, notes = process(fn, text)
        total.update(counts)
        for n in notes:
            print(n)
    for k, v in sorted(total.items()):
        print('%6d  %s' % (v, k))
    print('%6d  total' % sum(total.values()))
    print('unresolved:', UNRESOLVED.most_common(40))


if __name__ == '__main__':
    main(sys.argv[1:])
