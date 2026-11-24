#!/usr/bin/env python3
"""Merge the decomp's per-file declarations into one header for the port.

Reads src/inspace/*.c (never writes there), parses every file with
pycparser, collects each file's view of the shared globals and record
types, normalises every table to one base and one struct type, and writes
port/src/game/game.h.  port_translate.py imports this module for the
parsed model.

Run from the repository root:  python3 -I tools/port_merge.py [--report]
"""
import os
import re
import sys
import json
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from pycparser import c_parser, c_ast  # noqa: E402
from port_overrides import overrides  # noqa: E402

OV = overrides()

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, 'src', 'inspace')
OUT = os.path.join(ROOT, 'port', 'src', 'game')
NAMES = os.path.join(ROOT, 'names', 'INSPACE.EXE.txt')

# ---------------------------------------------------------------------------
# Lexing and source cleaning
# ---------------------------------------------------------------------------

TOKEN_RE = re.compile(r'''
    (?P<comment>/\*.*?\*/|//[^\n]*)
  | (?P<string>"(?:\\.|[^"\\\n])*")
  | (?P<char>'(?:\\.|[^'\\\n])*')
  | (?P<ident>[A-Za-z_][A-Za-z_0-9]*)
  | (?P<number>(?:0[xX][0-9a-fA-F]+|\d+\.?\d*(?:[eE][-+]?\d+)?)[uUlL]*)
  | (?P<ws>[ \t\r\f\v]+)
  | (?P<nl>\n)
  | (?P<punct>->|\+\+|--|<<=|>>=|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^!=<>]=|\.\.\.|[^\s])
''', re.S | re.X)


class Tok:
    __slots__ = ('kind', 'text', 'pos')

    def __init__(self, kind, text, pos):
        self.kind, self.text, self.pos = kind, text, pos

    def __repr__(self):
        return 'Tok(%s,%r,%d)' % (self.kind, self.text, self.pos)


def lex(text):
    toks = []
    for m in TOKEN_RE.finditer(text):
        toks.append(Tok(m.lastgroup, m.group(), m.start()))
    return toks


def preproc_lines(text):
    """Yield (start, end) spans of preprocessor directives (with continuations)."""
    spans = []
    pos = 0
    n = len(text)
    while pos < n:
        eol = text.find('\n', pos)
        if eol < 0:
            eol = n
        line = text[pos:eol]
        if line.lstrip().startswith('#'):
            start = pos
            while text[pos:eol].rstrip().endswith('\\') and eol < n:
                pos = eol + 1
                eol = text.find('\n', pos)
                if eol < 0:
                    eol = n
            spans.append((start, eol))
        pos = eol + 1
    return spans


MACRO_KEEP = {'SC', 'GETPROC'}


def parse_defines(text):
    """Return list of (span, name, params or None, body) for #define lines."""
    out = []
    for s, e in preproc_lines(text):
        d = text[s:e]
        m = re.match(r'\s*#\s*define\s+([A-Za-z_]\w*)(\(([^)]*)\))?', d)
        if not m:
            continue
        body = d[m.end():]
        body = re.sub(r'\\\n', ' ', body)
        body = re.sub(r'/\*.*?\*/', ' ', body, flags=re.S).strip()
        params = None
        if m.group(2) is not None:
            params = [p.strip() for p in m.group(3).split(',') if p.strip()]
        out.append(((s, e), m.group(1), params, body))
    return out


def expand_macros(text):
    """Expand the file's own macros (except MACRO_KEEP) at their use sites.

    The decomp uses macros mostly as views of memory through casts; the
    translator needs to see those expressions.  The #define lines of
    expanded macros are blanked (comments in them dropped)."""
    defs = parse_defines(text)
    exp = [d for d in defs if d[1] not in MACRO_KEEP]
    if not exp:
        return text
    # blank the definitions
    chars = list(text)
    for (s, e), name, params, body in exp:
        for i in range(s, e):
            if chars[i] != '\n':
                chars[i] = ' '
    text = ''.join(chars)
    table = {d[1]: d for d in exp}
    for _ in range(5):
        toks = lex(text)
        out = []
        changed = False
        i = 0
        last = 0
        while i < len(toks):
            t = toks[i]
            if t.kind == 'ident' and t.text in table:
                (s, e), name, params, body = table[t.text]
                if t.pos < s:          # used before definition: not ours
                    i += 1
                    continue
                if params is None:
                    out.append(text[last:t.pos])
                    out.append(body)
                    last = t.pos + len(t.text)
                    changed = True
                    i += 1
                    continue
                # function-like: find argument list
                j = i + 1
                while j < len(toks) and toks[j].kind in ('ws', 'nl', 'comment'):
                    j += 1
                if j >= len(toks) or toks[j].text != '(':
                    i += 1
                    continue
                depth = 0
                args = []
                cur = []
                k = j
                while k < len(toks):
                    tt = toks[k]
                    if tt.text in '([{' and tt.kind == 'punct':
                        depth += 1
                        if depth == 1:
                            k += 1
                            continue
                    elif tt.text in ')]}' and tt.kind == 'punct':
                        depth -= 1
                        if depth == 0:
                            args.append(''.join(x.text for x in cur).strip())
                            break
                    elif tt.text == ',' and depth == 1:
                        args.append(''.join(x.text for x in cur).strip())
                        cur = []
                        k += 1
                        continue
                    cur.append(tt)
                    k += 1
                end = toks[k].pos + 1
                sub = {p: a for p, a in zip(params, args)}
                btoks = lex(body)
                rep = ''.join(('(' + sub[b.text] + ')' if (b.kind == 'ident' and b.text in sub
                               and not re.match(r'^[A-Za-z_]\w*$', sub[b.text])) else
                               sub[b.text] if (b.kind == 'ident' and b.text in sub) else b.text)
                              for b in btoks)
                out.append(text[last:t.pos])
                out.append(rep)
                last = end
                changed = True
                i = k + 1
                continue
            i += 1
        out.append(text[last:])
        text = ''.join(out)
        if not changed:
            break
    return text


FAR_WORDS = {'far', 'huge', '_far', '__far', '_huge', '__huge'}
DROP_WORDS = {'near', '_near', '__near', 'pascal', '_pascal', '__pascal',
              '_export', '__export', 'cdecl', '_cdecl', '__cdecl',
              '_loadds', '__loadds', 'register'}


class ParseText:
    """Parse text derived from source text, with a position map back."""

    def __init__(self, src):
        self.src = src
        pieces = []
        # parse-text line -> list of (pcol, scol) anchors
        toks = lex(src)
        pp = preproc_lines(src)
        pp_set = []
        for s, e in pp:
            d = src[s:e]
            pp_set.append((s, e, bool(re.match(r'\s*#\s*pragma', d))))
        ppi = 0
        out = []
        self.maps = defaultdict(list)    # pline -> [(pcol, spos)]
        pline, pcol = 1, 0
        idx = 0
        # va_arg(ap, T): the parser needs an expression; parse T as a cast.
        va_open, va_close = set(), set()
        sig = [i for i, t in enumerate(toks) if t.kind not in ('ws', 'nl', 'comment')]
        for n, i in enumerate(sig):
            if toks[i].text == 'va_arg':
                depth = 0
                for m in range(n + 1, len(sig)):
                    tx = toks[sig[m]].text
                    if tx == '(':
                        depth += 1
                    elif tx == ')':
                        depth -= 1
                        if depth == 0:
                            va_close.add(sig[m])
                            break
                    elif tx == ',' and depth == 1:
                        va_open.add(sig[m])
        while idx < len(toks):
            t = toks[idx]
            # preprocessor region?
            while ppi < len(pp_set) and pp_set[ppi][1] < t.pos:
                ppi += 1
            in_pp = ppi < len(pp_set) and pp_set[ppi][0] <= t.pos < pp_set[ppi][1]
            if t.kind == 'nl':
                out.append('\n')
                pline += 1
                pcol = 0
                idx += 1
                continue
            if in_pp and not pp_set[ppi][2]:
                idx += 1
                continue
            if t.kind == 'comment':
                nl = t.text.count('\n')
                if nl:
                    out.append('\n' * nl)
                    pline += nl
                    pcol = 0
                else:
                    out.append(' ')
                    pcol += 1
                idx += 1
                continue
            text = t.text
            if t.kind == 'ident' and text in DROP_WORDS:
                text = ' '
            elif t.kind == 'ident' and text in FAR_WORDS:
                # 'far' before '*' -> qualify pointee with restrict (marker);
                # inside "( far * name )" function-pointer declarators drop it.
                prev = [x for x in toks[max(0, idx - 4):idx] if x.kind not in ('ws', 'nl', 'comment')]
                if prev and prev[-1].text in ('(', 'far', 'pascal', 'huge') and prev[-1].kind != 'string':
                    # inside declarator parentheses or a cast?  A cast "(T far *)"
                    # has a type before far; "( far *" is a function pointer.
                    if prev[-1].text == '(' or prev[-1].text in ('pascal',):
                        text = ' '
                    else:
                        text = ' '
                else:
                    text = 'restrict'
            if idx in va_close:
                out.append(')0')
                pcol += 2
            self.maps[pline].append((pcol, t.pos))
            out.append(text)
            pcol += len(text)
            if idx in va_open:
                out.append('(')
                pcol += 1
            idx += 1
        self.text = ''.join(out)

    def src_pos(self, line, col):
        """Map a pycparser coord (1-based line, 1-based column) to src offset."""
        col0 = col - 1
        anchors = self.maps.get(line)
        if not anchors:
            raise KeyError((line, col))
        best = None
        for pc, sp in anchors:
            if pc <= col0:
                best = (pc, sp)
            else:
                break
        if best is None:
            raise KeyError((line, col))
        return best[1] + (col0 - best[0])


# ---------------------------------------------------------------------------
# Prelude for parsing: Win16 types (names only matter for the parser)
# ---------------------------------------------------------------------------

WIN_TYPES = {
    # name: (size16, port type)
    'BOOL': (2, 'int16_t'), 'BYTE': (1, 'uint8_t'), 'WORD': (2, 'uint16_t'),
    'DWORD': (4, 'uint32_t'), 'UINT': (2, 'uint16_t'), 'LONG': (4, 'int32_t'),
    'WPARAM': (2, 'uint16_t'), 'LPARAM': (4, 'int32_t'), 'LRESULT': (4, 'int32_t'),
    'COLORREF': (4, 'uint32_t'), 'HFILE': (2, 'int16_t'),
    'HANDLE': (2, 'uint16_t'), 'HWND': (2, 'uint16_t'), 'HDC': (2, 'uint16_t'),
    'HBITMAP': (2, 'uint16_t'), 'HBRUSH': (2, 'uint16_t'), 'HFONT': (2, 'uint16_t'),
    'HGDIOBJ': (2, 'uint16_t'), 'HGLOBAL': (2, 'uint16_t'), 'HICON': (2, 'uint16_t'),
    'HINSTANCE': (2, 'uint16_t'), 'HMENU': (2, 'uint16_t'), 'HPALETTE': (2, 'uint16_t'),
    'HPEN': (2, 'uint16_t'), 'HRGN': (2, 'uint16_t'), 'HRSRC': (2, 'uint16_t'),
    'HTASK': (2, 'uint16_t'), 'HACCEL': (2, 'uint16_t'), 'HMODULE': (2, 'uint16_t'),
    'HCURSOR': (2, 'uint16_t'), 'ATOM': (2, 'uint16_t'),
    'LPSTR': (4, 'char *'), 'LPCSTR': (4, 'const char *'), 'LPRECT': (4, 'RECT *'),
    'LPPOINT': (4, 'POINT *'), 'LPVOID': (4, 'void *'), 'PSTR': (2, 'char *'),
    'FARPROC': (4, 'FARPROC'), 'DLGPROC': (4, 'DLGPROC'), 'WNDPROC': (4, 'WNDPROC'),
    'POINT': (4, 'POINT'), 'RECT': (8, 'RECT'), 'SIZE': (4, 'SIZE'),
    'MSG': (18, 'MSG'), 'PAINTSTRUCT': (32, 'PAINTSTRUCT'), 'TEXTMETRIC': (31, 'TEXTMETRIC'),
    'WNDCLASS': (26, 'WNDCLASS'), 'OFSTRUCT': (136, 'OFSTRUCT'),
    'DRAWITEMSTRUCT': (26, 'DRAWITEMSTRUCT'), 'MEASUREITEMSTRUCT': (12, 'MEASUREITEMSTRUCT'),
    'MINMAXINFO': (20, 'MINMAXINFO'), 'TIMECAPS': (4, 'TIMECAPS'), 'BITMAP': (14, 'BITMAP'),
    'LOGPALETTE': (8, 'LOGPALETTE'), 'PALETTEENTRY': (4, 'PALETTEENTRY'),
    'BITMAPINFOHEADER': (40, 'BITMAPINFOHEADER'), 'RGBQUAD': (4, 'RGBQUAD'),
    'MCI_OPEN_PARMS': (18, 'MCI_OPEN_PARMS'),
    'va_list': (2, 'va_list'), 'size_t': (2, 'uint16_t'), 'time_t': (4, 'int32_t'),
    'FILE': (0, 'FILE'), 'off_t': (4, 'int32_t'),
    'BOOL_': (2, 'int16_t'),
}

PRELUDE = ''.join('typedef int %s;\n' % n for n in WIN_TYPES) + \
    'struct find_t { char x[43]; }; struct _find_t { char x[43]; }; struct stat { char x[30]; };\n' \
    'struct tm { char x[18]; }; struct utimbuf { char x[8]; };\n'
CRT_STRUCTS = {'find_t', '_find_t', 'stat', 'tm', 'utimbuf'}
PRELUDE_LINES = PRELUDE.count('\n')


_HDR = None


def header_parse_text():
    global _HDR
    if _HDR is None:
        with open(os.path.join(SRC, 'inspace.h'), encoding='latin-1') as f:
            _HDR = '# 1 "inspace.h"\n' + ParseText(OV.apply('inspace.h', f.read())).text + '\n'
    return _HDR


def prepare(path):
    """Return (src_text_after_macro_expansion, ParseText, ast)."""
    with open(path, encoding='latin-1') as f:
        raw = f.read()
    raw = OV.apply(os.path.basename(path), raw)
    src = expand_macros(raw)
    pt = ParseText(src)
    text = PRELUDE + header_parse_text() + '# 1 "%s"\n' % os.path.basename(path) + pt.text
    parser = c_parser.CParser()
    ast = parser.parse(text, filename=os.path.basename(path))
    return src, pt, ast


def src_files():
    return sorted(f for f in os.listdir(SRC) if f.endswith('.c'))


if __name__ == '__main__' and len(sys.argv) > 1 and sys.argv[1] == '--parse-test':
    for fn in src_files():
        try:
            prepare(os.path.join(SRC, fn))
            print('ok', fn)
        except Exception as e:  # noqa
            print('FAIL', fn, e)
    sys.exit(0)


# ---------------------------------------------------------------------------
# Type model (sizes as in the 16-bit medium-model original)
# ---------------------------------------------------------------------------

class Type:
    def size(self):
        raise NotImplementedError

    def align(self):
        return min(2, max(1, self.size()))


class Prim(Type):
    SIZES = {'void': 0, 'char': 1, 'schar': 1, 'uchar': 1, 'short': 2, 'ushort': 2,
             'int': 2, 'uint': 2, 'long': 4, 'ulong': 4, 'float': 4, 'double': 8}

    def __init__(self, name):
        self.name = name

    def size(self):
        return self.SIZES[self.name]

    def __repr__(self):
        return self.name

    def key(self):
        return self.name


class Win(Type):
    """A Windows type from windows.h, by name."""
    FIELDS = {'POINT': [('x', 0, 'int'), ('y', 2, 'int')],
              'RECT': [('left', 0, 'int'), ('top', 2, 'int'), ('right', 4, 'int'),
                       ('bottom', 6, 'int')],
              'SIZE': [('cx', 0, 'int'), ('cy', 2, 'int')]}

    def __init__(self, name):
        self.name = name

    def size(self):
        return WIN_TYPES[self.name][0]

    def __repr__(self):
        return self.name

    def key(self):
        return self.name


class Ptr(Type):
    def __init__(self, to, far):
        self.to, self.far = to, far

    def size(self):
        if isinstance(self.to, Func):
            return 4
        return 4 if self.far else 2

    def __repr__(self):
        return '%s%s*' % (self.to, ' far ' if self.far else ' ')

    def key(self):
        return ('ptr', tkey(self.to))


class Arr(Type):
    def __init__(self, of, n):
        self.of, self.n = of, n

    def size(self):
        es = self.of.size if isinstance(self.of.size, int) else self.of.size()
        return es * (self.n or 0)

    def align(self):
        return self.of.align()

    def __repr__(self):
        return '%s[%s]' % (self.of, '' if self.n is None else hex(self.n))

    def key(self):
        return ('arr', tkey(self.of), self.n)


class Func(Type):
    def __init__(self, ret, params, var):
        self.ret, self.params, self.var = ret, params, var

    def size(self):
        return 0

    def __repr__(self):
        return 'fn(%s)->%s' % (', '.join(repr(t) for _, t in self.params), self.ret)

    def key(self):
        return ('fn', tkey(self.ret), tuple(tkey(t) for _, t in self.params), self.var)


class Struct(Type):
    def __init__(self, name, file):
        self.name, self.file = name, file
        self.fields = []          # (name, type, offset)
        self._size = 0
        self._align = 1
        self.packed = False
        self.is_union = False

    def layout(self, members, pack):
        self.packed = pack == 1
        off = 0
        al = 1
        for name, t in members:
            a = 1 if pack == 1 else t.align()
            al = max(al, a)
            if self.is_union:
                self.fields.append((name, t, 0))
                off = max(off, t.size())
                continue
            off = (off + a - 1) // a * a
            self.fields.append((name, t, off))
            off += t.size()
        off = (off + al - 1) // al * al
        self._size = off
        self._align = al

    def size(self):
        return self._size

    def align(self):
        return self._align

    def field(self, name):
        for f in self.fields:
            if f[0] == name:
                return f
        return None

    def __repr__(self):
        return 'struct %s' % self.name

    def key(self):
        return ('struct', self.name, self.file)


def tkey(t):
    return t.key() if t is not None else None


INT = Prim('int')
UINT = Prim('uint')
LONG = Prim('long')
CHAR = Prim('char')


def prim_from_names(names):
    n = [x for x in names if x not in ('signed', 'const', 'volatile', 'restrict')]
    uns = 'unsigned' in n
    sig = 'signed' in names
    n = [x for x in n if x != 'unsigned']
    if 'char' in n:
        return Prim('uchar' if uns else ('schar' if sig else 'char'))
    if 'short' in n:
        return Prim('ushort' if uns else 'short')
    if 'long' in n:
        if 'double' in n:
            return Prim('double')
        return Prim('ulong' if uns else 'long')
    if 'float' in n:
        return Prim('float')
    if 'double' in n:
        return Prim('double')
    if 'void' in n:
        return Prim('void')
    return Prim('uint' if uns else 'int')


class Scope:
    def __init__(self, parent=None):
        self.parent = parent
        self.vars = {}
        self.types = {}
        self.tags = {}

    def lookup(self, name):
        s = self
        while s:
            if name in s.vars:
                return s.vars[name]
            s = s.parent
        return None

    def lookup_type(self, name):
        s = self
        while s:
            if name in s.types:
                return s.types[name]
            s = s.parent
        return None

    def lookup_tag(self, name):
        s = self
        while s:
            if name in s.tags:
                return s.tags[name]
            s = s.parent
        return None


class TypeBuilder:
    """Converts pycparser type nodes to Type, given a scope and pack state."""

    def __init__(self, file):
        self.file = file
        self.pack = 2
        self.anon = 0
        self.consts = {}

    def const_eval(self, node, scope=None):
        if node is None:
            return None
        if isinstance(node, c_ast.Constant):
            v = node.value.rstrip('uUlL')
            if node.type == 'char':
                return ord(eval(v))
            try:
                return int(v, 0) if not v.startswith('0') or v.startswith('0x') or v == '0' \
                    else int(v, 8)
            except ValueError:
                return None
        if isinstance(node, c_ast.BinaryOp):
            a = self.const_eval(node.left, scope)
            b = self.const_eval(node.right, scope)
            if a is None or b is None:
                return None
            op = node.op
            if op == '+':
                return a + b
            if op == '-':
                return a - b
            if op == '*':
                return a * b
            if op == '/':
                return int(a / b)
            if op == '<<':
                return a << b
            if op == '>>':
                return a >> b
            if op == '|':
                return a | b
            if op == '&':
                return a & b
            return None
        if isinstance(node, c_ast.UnaryOp):
            if node.op == 'sizeof':
                t = self.build(node.expr.type, scope) if isinstance(node.expr, c_ast.Typename) else None
                return t.size() if t else None
            a = self.const_eval(node.expr, scope)
            if a is None:
                return None
            return -a if node.op == '-' else a if node.op == '+' else None
        if isinstance(node, c_ast.ID):
            return self.consts.get(node.name)
        return None

    def build(self, node, scope, quals_far=False):
        """node: a pycparser type node (TypeDecl, PtrDecl, ArrayDecl, FuncDecl, Typename)."""
        if isinstance(node, c_ast.Typename):
            return self.build(node.type, scope)
        if isinstance(node, c_ast.Decl):
            return self.build(node.type, scope)
        if isinstance(node, c_ast.TypeDecl):
            return self.build_base(node.type, scope)
        if isinstance(node, c_ast.PtrDecl):
            inner = node.type
            far = False
            if isinstance(inner, c_ast.TypeDecl) and 'restrict' in inner.quals:
                far = True
            if isinstance(inner, c_ast.PtrDecl) and 'restrict' in inner.quals:
                far = True
            return Ptr(self.build(inner, scope), far)
        if isinstance(node, c_ast.ArrayDecl):
            n = self.const_eval(node.dim, scope)
            return Arr(self.build(node.type, scope), n)
        if isinstance(node, c_ast.FuncDecl):
            ret = self.build(node.type, scope)
            params = []
            var = False
            if node.args:
                for p in node.args.params:
                    if isinstance(p, c_ast.EllipsisParam):
                        var = True
                        continue
                    if isinstance(p, c_ast.ID):        # K&R
                        params.append((p.name, INT))
                        continue
                    t = self.build(p.type, scope)
                    if isinstance(t, Prim) and t.name == 'void' and not p.name:
                        continue
                    if isinstance(t, Arr):
                        t = Ptr(t.of, False)
                    params.append((p.name, t))
            return Func(ret, params, var)
        raise TypeError(node)

    def build_base(self, t, scope):
        if isinstance(t, c_ast.IdentifierType):
            names = t.names
            if len(names) == 1 and names[0] in WIN_TYPES:
                lt = scope.lookup_type(names[0]) if scope else None
                if lt is not None:
                    return lt
                return Win(names[0])
            if len(names) == 1 and scope is not None:
                lt = scope.lookup_type(names[0])
                if lt is not None:
                    return lt
            return prim_from_names(names)
        if isinstance(t, (c_ast.Struct, c_ast.Union)):
            if t.decls is None:
                if t.name and scope is not None:
                    st = scope.lookup_tag(t.name)
                    if st is not None:
                        return st
                s = Struct(t.name or '?', self.file)
                s.opaque = True
                return s
            self.anon += 1
            s = Struct(t.name or ('anon%d' % self.anon), self.file)
            s.is_union = isinstance(t, c_ast.Union)
            s.anon = t.name is None
            members = []
            for d in t.decls:
                if d.bitsize is not None:
                    raise TypeError('bitfield')
                members.append((d.name, self.build(d.type, scope)))
            s.layout(members, self.pack)
            if t.name and scope is not None:
                scope.tags[t.name] = s
            return s
        if isinstance(t, c_ast.Enum):
            return INT
        raise TypeError(t)


# ---------------------------------------------------------------------------
# Collecting each file's declarations
# ---------------------------------------------------------------------------

def load_names():
    """Confirmed names: {name: (sel, off)}; inferred names: {(sel,off): name}."""
    confirmed, inferred = {}, {}
    with open(NAMES) as f:
        for line in f:
            line = line.split('#', 1)
            text = line[0].strip()
            comment = line[1] if len(line) > 1 else ''
            m = re.match(r'([0-9a-f]{4}):([0-9a-f]{4})\s+(\S+)(\s+\[inferred\])?', text)
            if not m:
                continue
            sel, off, name = int(m.group(1), 16), int(m.group(2), 16), m.group(3)
            if m.group(4) or '[inferred]' in text:
                inferred[(sel, off)] = name
            else:
                confirmed[name] = (sel, off)
    return confirmed, inferred


CONFIRMED, INFERRED = load_names()
NAME_ADDR = {n: o for n, (s, o) in CONFIRMED.items() if s == 0x1090}
ADDR_NAME = {o: n for n, o in NAME_ADDR.items()}
FUNC_NAME = {((s - 0x1000) // 8 + 1, o): n for n, (s, o) in CONFIRMED.items() if s != 0x1090}


def confirmed_name(ident):
    """Confirmed name for a g_XXXX / g_fp_XXXX / fn_SS_OOOO identifier, or None."""
    m = re.match(r'^g_(?:fp_)?([0-9a-f]{4})$', ident)
    if m:
        return ADDR_NAME.get(int(m.group(1), 16))
    m = re.match(r'^fn_(\d\d)_([0-9a-f]{4})$', ident)
    if m:
        return FUNC_NAME.get((int(m.group(1)), int(m.group(2), 16)))
    return None


INFERRED_IDENT = {n: ('g_%04x' % o if s == 0x1090 else 'fn_%02d_%04x' % ((s - 0x1000) // 8 + 1, o))
                  for (s, o), n in INFERRED.items()}


def apply_names(text):
    """Replace address names by confirmed names in code (not comments or strings)."""
    out = []
    pos = 0
    for t in lex(text):
        if t.kind == 'ident':
            # inferred names stay comments: the code keeps the address name
            n = confirmed_name(t.text) or INFERRED_IDENT.get(t.text)
            if n:
                out.append(text[pos:t.pos])
                out.append(n)
                pos = t.pos + len(t.text)
    out.append(text[pos:])
    return ''.join(out)


def global_addr(name):
    m = re.match(r'^g_(?:fp_)?([0-9a-f]{4})$', name)
    if m:
        return int(m.group(1), 16)
    return NAME_ADDR.get(name)


class GDecl:
    def __init__(self, file, name, type, node, is_def, block):
        self.file, self.name, self.type, self.node = file, name, type, node
        self.is_def, self.block = is_def, block
        self.addr = global_addr(name)

    def __repr__(self):
        return '%s:%s %r' % (self.file, self.name, self.type)


class FileModel:
    def __init__(self, fn):
        self.fn = fn
        self.path = os.path.join(SRC, fn)
        self.src, self.pt, self.ast = prepare(self.path)
        self.tb = TypeBuilder(fn)
        self.scope = Scope()
        self.typedefs = {}            # name -> (Type, node)
        self.globals = {}             # name -> GDecl (file scope or block extern)
        self.block_externs = []       # GDecl
        self.funcs = {}               # name -> (Func type, FuncDef node or None)
        self.protos = {}              # name -> Func
        self.funcdefs = []            # FuncDef nodes (in this file)
        self.collect()

    def in_this_file(self, node):
        return node.coord is not None and node.coord.file == self.fn

    def collect(self):
        tb, scope = self.tb, self.scope
        for ext in self.ast.ext:
            if isinstance(ext, c_ast.Pragma):
                m = re.match(r'pack\s*\(\s*(\d*)\s*\)', ext.string)
                if m:
                    tb.pack = int(m.group(1)) if m.group(1) else 2
                continue
            if isinstance(ext, c_ast.Typedef):
                if ext.name in WIN_TYPES:
                    continue
                t = tb.build(ext.type, scope)
                if isinstance(t, Struct) and getattr(t, 'anon', False):
                    t.name = ext.name
                    t.anon = False
                scope.types[ext.name] = t
                self.typedefs[ext.name] = (t, ext)
                continue
            if isinstance(ext, c_ast.Decl):
                if ext.coord is None or ext.coord.file not in (self.fn, 'inspace.h'):
                    continue
                if ext.name is None:
                    # struct tag declaration
                    tb.build_base(ext.type, scope) if not isinstance(ext.type, c_ast.TypeDecl) \
                        else tb.build(ext.type, scope)
                    continue
                t = tb.build(ext.type, scope)
                if isinstance(t, Func):
                    self.protos[ext.name] = t
                    scope.vars[ext.name] = t
                    continue
                g = GDecl(self.fn if self.in_this_file(ext) else 'inspace.h', ext.name, t, ext,
                          'extern' not in ext.storage, False)
                scope.vars[ext.name] = t
                self.globals[ext.name] = g
                continue
            if isinstance(ext, c_ast.FuncDef):
                t = tb.build(ext.decl.type, scope)
                scope.vars[ext.decl.name] = t
                self.funcs[ext.decl.name] = (t, ext)
                self.funcdefs.append(ext)
                # block-scope externs and statics
                for node in walk(ext.body):
                    if isinstance(node, c_ast.Decl) and node.name and \
                            ('extern' in node.storage or 'static' in node.storage):
                        bt = tb.build(node.type, scope)
                        if isinstance(bt, Func):
                            self.protos.setdefault(node.name, bt)
                            continue
                        g = GDecl(self.fn, node.name, bt, node, 'static' in node.storage, True)
                        self.block_externs.append(g)
                continue


def walk(node):
    if node is None:
        return
    yield node
    for _, c in node.children():
        yield from walk(c)


_MODELS = None


def load_models():
    global _MODELS
    if _MODELS is None:
        _MODELS = [FileModel(fn) for fn in src_files()]
    return _MODELS


def survey():
    models = load_models()
    by = defaultdict(list)
    for m in models:
        for g in list(m.globals.values()) + m.block_externs:
            by[g.name].append((m.fn, g))
    nconf = 0
    for name in sorted(by, key=lambda n: (global_addr(n) or 0x10000, n)):
        reprs = defaultdict(list)
        for fn, g in by[name]:
            reprs[repr(g.type)].append(fn)
        if len(reprs) > 1:
            nconf += 1
            print(name, hex(global_addr(name) or 0))
            for r, fs in reprs.items():
                print('    %-40s %s' % (r, ' '.join(sorted(set(fs)))))
    print(len(by), 'globals,', nconf, 'with conflicts')


if __name__ == '__main__' and len(sys.argv) > 1 and sys.argv[1] == '--survey':
    survey()
    sys.exit(0)


def survey_tables():
    models = load_models()
    rows = defaultdict(set)
    for m in models:
        for g in list(m.globals.values()) + m.block_externs:
            t = g.type
            arr = None
            while isinstance(t, Arr):
                arr = t
                t = t.of
            if isinstance(t, Struct) and arr is not None:
                rows[(t.size(), g.addr)].add('%s:%s%s' % (m.fn, t.name, '' if arr.n is None else '[%x]' % arr.n))
            elif isinstance(t, Ptr) and isinstance(t.to, Struct):
                rows[(-t.to.size(), g.addr)].add('%s:*%s' % (m.fn, t.to.name))
    for (s, a) in sorted(rows):
        print('%5x %04x %s %s' % (abs(s), a or 0, 'PTR' if s < 0 else '   ', ' '.join(sorted(rows[(s, a)]))[:150]))


if __name__ == '__main__' and len(sys.argv) > 1 and sys.argv[1] == '--tables':
    survey_tables()
    sys.exit(0)


# ---------------------------------------------------------------------------
# Merging
# ---------------------------------------------------------------------------

# Tables whose views are too far apart for the automatic clustering
# (views closer than one record are joined automatically).  base: size, count
MANUAL_TABLES = {
    0x6e38: (0x1e, 12),     # DECOMP.md: 0x1e-byte records at DS:6e38
    0x6670: (0x1c, 14),     # views at 6670..6682 sit just below the 0x1c table at 66e0
}

# Arrays declared without a length whose length is known (DECOMP.md).
MANUAL_ARRAYS = {
    0x9406: 15,             # int[15] per-type table
    0x92ec: 15,             # int[15] per-type table
}

PAD_RE = re.compile(r'^(p[0-9a-f_]+|pad\\w*|_pad\\w*|rest\\w*|gap\\w*|filler\\w*)$')
OFFNAME_RE = re.compile(r'^[a-z]{1,2}_?m?[0-9a-f]+$')

HANDLE_NAMES = {n for n, (s, t) in WIN_TYPES.items() if n.startswith('H') or n in ('ATOM',)}


def is_pad(name, t):
    if name is None:
        return True
    if not PAD_RE.match(name):
        return False
    return isinstance(t, Arr) or isinstance(t, Prim)


def strip_arr(t):
    while isinstance(t, Arr):
        t = t.of
    return t


def type_rank(t):
    """Higher = more specific (preferred as the merged type)."""
    if isinstance(t, Struct):
        return 80 if getattr(t, 'anon', False) or t.name.startswith('anon') else 90
    if isinstance(t, Win):
        if t.name in ('POINT', 'RECT', 'SIZE'):
            return 85
        if t.name in HANDLE_NAMES:
            return 70
        if t.name in ('DWORD', 'COLORREF', 'LONG', 'LPARAM'):
            return 60
        return 50
    if isinstance(t, Ptr):
        if isinstance(t.to, Struct):
            return 80
        if isinstance(t.to, Func):
            return 78
        if isinstance(t.to, Prim) and t.to.name == 'void':
            return 55
        return 75
    if isinstance(t, Arr):
        return 40 + type_rank(t.of) // 10
    if isinstance(t, Prim):
        return {'ulong': 35, 'long': 34, 'uint': 21, 'int': 20, 'ushort': 19, 'short': 19,
                'uchar': 11, 'schar': 10, 'char': 10}.get(t.name, 5)
    return 0


def fn_params(t):
    """Parameter count of a function pointer: a slot called with several
    shapes takes the longest (the shorter callers' callees ignore the rest)."""
    if isinstance(t, Ptr) and isinstance(t.to, Func):
        return len(t.to.params)
    return 0


class Item:
    """One declared view of memory: offset, type, name, file."""
    __slots__ = ('off', 'type', 'name', 'file')

    def __init__(self, off, type, name, file):
        self.off, self.type, self.name, self.file = off, type, name, file

    @property
    def size(self):
        return self.type.size()

    def __repr__(self):
        return '%x:%s %r (%s)' % (self.off, self.name, self.type, self.file)


class MField:
    """One field of a merged layout."""

    def __init__(self, off, type, name, items):
        self.off, self.type, self.name, self.items = off, type, name, items

    @property
    def size(self):
        return self.type.size()


def same_class(a, b):
    if a.size() != b.size():
        return False
    if isinstance(a, Ptr) and isinstance(b, Ptr):
        return True
    return repr(a) == repr(b) or (not isinstance(a, (Ptr, Struct)) and not isinstance(b, (Ptr, Struct)))


def merge_items(items, total=None, fmt=None, report=None, what=''):
    """Merge overlapping views into one list of fields (sorted by offset).

    Arrays win over the scalars they contain when those line up with their
    elements; otherwise the most specific non-array view wins and arrays
    are cut short at the next chosen field.  fmt(off) names offset fields."""
    def end(it):
        return it.off + max(it.size, 1)

    def inside(a, b):           # a within b
        return b.off <= a.off and end(a) <= end(b)

    def overlap(a, b):
        return a.off < end(b) and b.off < end(a)

    arrays = [it for it in items if isinstance(it.type, Arr) and it.size > 0]
    scal = [it for it in items if not (isinstance(it.type, Arr) and it.size > 0)]
    compat, incompat = [], []
    for a in arrays:
        es = strip_arr(a.type).size() or 1
        ok = True
        for o in items:
            if o is a or not overlap(o, a):
                continue
            if isinstance(o.type, Arr) and same_class(strip_arr(o.type), strip_arr(a.type)) and \
                    (inside(o, a) or inside(a, o)):
                continue
            if not inside(o, a):
                ok = False
                break
            if isinstance(o.type, Arr) and repr(strip_arr(o.type)) == repr(strip_arr(a.type)):
                continue
            if (o.off - a.off) % es or o.size != es or \
                    (isinstance(strip_arr(o.type), Prim) and isinstance(strip_arr(a.type), Prim) and
                     strip_arr(o.type).name.lstrip('us').replace('h', '') !=
                     strip_arr(a.type).name.lstrip('us').replace('h', '')):
                ok = False
                break
        (compat if ok else incompat).append(a)
    cnt = defaultdict(int)
    for it in items:
        cnt[(it.off, repr(it.type))] += 1
    order = sorted(compat, key=lambda it: (-it.size, -type_rank(it.type), -cnt[(it.off, repr(it.type))], it.off)) + \
        sorted(scal, key=lambda it: (-type_rank(it.type), -it.size, -fn_params(it.type),
                                     -cnt[(it.off, repr(it.type))], it.off))
    chosen = []
    for it in order:
        if any(overlap(it, c) for c in chosen):
            continue
        chosen.append(it)
    for a in sorted(incompat, key=lambda it: (it.off, -it.size)):
        if any(inside(a, c) or (overlap(a, c) and c.off <= a.off) for c in chosen):
            continue
        nxt = min([c.off for c in chosen if c.off > a.off] + [end(a)])
        es = strip_arr(a.type).size() or 1
        n = (nxt - a.off) // es
        if n <= 0:
            continue
        t = a.type
        if (nxt - a.off) < a.size:
            inner = t.of if isinstance(t, Arr) else t
            if isinstance(inner, Arr):
                n = (nxt - a.off) // inner.size()
                t = Arr(inner, n)
            else:
                t = Arr(inner, n)
            if report is not None:
                report.append('%s+%x: %s %r cut to %r' % (what, a.off, a.name, a.type, t))
        chosen.append(Item(a.off, t, a.name, a.file))
    chosen.sort(key=lambda it: it.off)
    fields = []
    for c in chosen:
        sub = [it for it in items if overlap(it, c)]
        if report is not None:
            kinds = set(repr(it.type) for it in sub if it.off == c.off and it.size == c.size)
            if len(kinds) > 1:
                report.append('%s+%x: %s -> %r' % (what, c.off, ', '.join(sorted(kinds)), c.type))
            part = [it for it in sub if not inside(it, c)]
            if part:
                report.append('%s+%x: %r overlaps %s' % (what, c.off, c.type, '; '.join(
                    '%x:%s %r' % (it.off, it.name, it.type) for it in part)))
        names = defaultdict(int)
        for it in sub:
            if it.off == c.off and it.size == c.size and it.name and not OFFNAME_RE.match(it.name):
                names[it.name] += 1
        if names:
            name = max(names, key=lambda n: (names[n], n))
        else:
            name = fmt(c.off) if fmt else c.name
        fields.append(MField(c.off, c.type, name, sub))
    return fields


class Kind:
    """A merged record type."""

    def __init__(self, key, size):
        self.key = key
        self.size = size
        self.views = []          # (Struct, delta, file)
        self.fields = []
        self.name = None
        self.base = None         # DS address for DGROUP tables
        self.count = None
        self.packed = False
        self.has_ptr = False

    def fmt(self, off):
        return 'f_%03x' % off if self.size > 0x100 else 'f_%02x' % off


class Global:
    """A merged DGROUP object."""

    def __init__(self, addr, name, type):
        self.addr, self.name, self.type = addr, name, type
        self.items = []
        self.files = set()


class View:
    """A struct type seen at some place: (kind, delta) for one declaration."""

    def __init__(self, t, kind, delta, file, src):
        self.t, self.kind, self.delta, self.file, self.src = t, kind, delta, file, src


class Merge:
    def __init__(self, models):
        self.models = models
        self.report = defaultdict(list)
        self.kinds = []
        self.type_views = defaultdict(list)    # id(Struct) -> [View]
        self.decl_view = {}                    # (file, global name) -> View
        self.tables = []
        self.globals = {}
        self.overlays = {}                     # id(Struct) -> DS address
        self.run()

    def all_decls(self):
        first = self.models[0].fn
        for m in self.models:
            for g in list(m.globals.values()) + m.block_externs:
                if g.file == 'inspace.h' and m.fn != first:
                    continue
                yield m, g

    def run(self):
        self.find_tables()
        self.table_counts()
        self.find_pointer_kinds()
        self.find_casts()
        self.find_other_kinds()
        self.merge_kinds()
        self.merge_globals()
        self.name_kinds()

    def add_view(self, k, t, delta, fn, src=None):
        for v in self.type_views[id(t)]:
            if v.kind is k and v.delta == delta:
                return v
        v = View(t, k, delta, fn, src)
        self.type_views[id(t)].append(v)
        k.views.append(v)
        return v

    def is_pascal(self, name):
        """True if name's definition is declared pascal (arguments pushed left to right)."""
        if not hasattr(self, '_pascal'):
            self._pascal = {}
        if name not in self._pascal:
            r = None
            f = getattr(self, 'functions', {}).get(name)
            if f is not None:
                m = [x for x in self.models if x.fn == f[1]][0]
                d = OV.find_def(m.src, name)
                if d is not None:
                    r = re.search(r'\bpascal\b', m.src[d[0]:d[1]]) is not None
            self._pascal[name] = bool(r)
        return self._pascal[name]

    def is_pascal_ptr(self, name):
        """True if a declaration of the function pointer name says pascal."""
        if not hasattr(self, '_pascal_ptr'):
            self._pascal_ptr = {}
        if name not in self._pascal_ptr:
            pat = re.compile(r'\bpascal\s*\*\s*%s\s*\)' % re.escape(name))
            with open(os.path.join(SRC, 'inspace.h'), encoding='latin-1') as f:
                hdr = OV.apply('inspace.h', f.read())
            self._pascal_ptr[name] = any(pat.search(s) for s in [hdr] + [m.src for m in self.models])
        return self._pascal_ptr[name]

    def view_of_type(self, t):
        vs = self.type_views.get(id(t))
        return vs[0] if vs else None

    # -- DGROUP tables -----------------------------------------------------
    def find_tables(self):
        views = defaultdict(list)
        rows = []
        for m, g in self.all_decls():
            if g.addr is None:
                continue
            t = g.type
            dims = []
            while isinstance(t, Arr):
                dims.append(t.n)
                t = t.of
            if isinstance(t, Struct) and dims and t.name not in CRT_STRUCTS:
                views[t.size()].append((g.addr, t, m.fn, dims, g))
            elif len(dims) >= 2 and isinstance(t, Prim):
                rows.append((g.addr, g.type.of, m.fn, g))
        # char rows (char g[][35]) inside a table of 35-byte records
        for addr, rt, fn, g in rows:
            for size, vs in views.items():
                if size == rt.size() and any(abs(addr - v[0]) < 4 * size for v in vs):
                    st = Struct('row_%04x' % addr, fn)
                    st.layout([('row', rt)], 1)
                    st.row = True
                    views[size].append((addr, st, fn, [None], g))
                    break
        plain = set()
        for m, g in self.all_decls():
            t = strip_arr(g.type)
            if g.addr is not None and isinstance(g.type, Arr) and isinstance(t, Win) and t.name in Win.FIELDS:
                plain.add((g.addr, t.size()))
        for size in list(views):
            views[size] = [v for v in views[size] if (v[0], size) not in plain]
        for size, vs in views.items():
            vs.sort(key=lambda v: v[0])
            clusters = []
            for v in vs:
                man = [b for b, (sz, n) in MANUAL_TABLES.items()
                       if sz == size and b <= v[0] < b + sz * n]
                if man:
                    key = ('man', man[0])
                    for c in clusters:
                        if c[0] == key:
                            c[1].append(v)
                            break
                    else:
                        clusters.append([key, [v]])
                    continue
                if clusters and clusters[-1][0] == 'auto' and v[0] - clusters[-1][1][-1][0] < size:
                    clusters[-1][1].append(v)
                else:
                    clusters.append(['auto', [v]])
            for key, c in clusters:
                base = min(v[0] for v in c)
                if key != 'auto':
                    base = min(base, key[1])
                k = Kind(('table', base), size)
                k.base = base
                counts = []
                for addr, t, fn, dims, g in c:
                    if dims[0] is not None:
                        counts.append((addr - base) // size + dims[0])
                if key != 'auto':
                    counts.append(MANUAL_TABLES[key[1]][1])
                k.count = max(counts) if counts else None
                k.inner = None
                for addr, t, fn, dims, g in c:
                    if len(dims) > 1:
                        k.inner = dims[1:]
                for addr, t, fn, dims, g in c:
                    v = self.add_view(k, t, addr - base, fn, g)
                    self.decl_view[(fn, g.name)] = v
                self.kinds.append(k)
                self.tables.append(k)

    def table_counts(self):
        """Tables without a declared length extend to the next other global."""
        view_addrs = {}
        for k in self.tables:
            for v in k.views:
                view_addrs[k.base + v.delta] = k
        others = sorted({g.addr for m, g in self.all_decls()
                         if g.addr is not None and g.addr not in view_addrs})
        for k in self.tables:
            if k.inner:
                continue
            top = max(k.base + v.delta for v in k.views)
            if k.count is None:
                nxt = sorted([a for a in others if a > top] + [t.base for t in self.tables if t.base > top])
                end = nxt[0] if nxt else top + k.size
                # scalars right after the views may be fields: prefer an end
                # that is a whole number of records
                for a in nxt[:6]:
                    if (a - k.base) % k.size == 0:
                        end = a
                        break
                k.count = max(1, (end - k.base) // k.size)
                k.count_guessed = True
                if (end - k.base) % k.size:
                    self.report['table length'].append(
                        'g_%04x: %d records of 0x%x up to next global %04x (+%d bytes)' % (
                            k.base, k.count, k.size, end, (end - k.base) % k.size))
                else:
                    self.report['table length'].append(
                        'g_%04x: %d records of 0x%x up to next global %04x' % (k.base, k.count, k.size, end))

    def table_at(self, addr):
        for k in self.tables:
            n = k.count or 1
            if k.inner:
                for d in k.inner:
                    n *= d or 1
            if k.base <= addr < k.base + k.size * n:
                return k
        return None

    # -- pointer kinds -------------------------------------------------------
    def find_pointer_kinds(self):
        ptrs = []
        for m, g in self.all_decls():
            if g.addr is None:
                continue
            t = g.type
            n = 1
            while isinstance(t, Arr):
                n *= (t.n or 1)
                t = t.of
            if isinstance(t, Ptr) and isinstance(strip_arr(t.to), Struct):
                ptrs.append((g.addr, n, t.to, m.fn, isinstance(g.type, Arr), g))
        arrays = sorted({(a, n) for a, n, s, fn, isarr, g in ptrs if isarr}, key=lambda x: x[0])
        groups = {}
        for a, n, s, fn, isarr, g in ptrs:
            key = a
            for b, cnt in arrays:
                if b <= a < b + 4 * max(cnt, 21 if b == 0x1df8 else cnt):
                    key = b
                    break
            groups.setdefault(key, []).append((a, s, fn, g))
        self.ptr_kinds = {}
        for key, vs in sorted(groups.items()):
            sizes = defaultdict(int)
            for a, s, fn, g in vs:
                sizes[strip_arr(s).size()] += 1
            k = Kind(('ptr', key), max(sizes, key=lambda z: (sizes[z], z)))
            for a, s, fn, g in vs:
                v = self.add_view(k, strip_arr(s), 0, fn, g)
                self.decl_view[(fn, g.name)] = v
            self.kinds.append(k)
            self.ptr_kinds[key] = k

    # -- casts: (T *)ptr_global and (T *)&global -----------------------------
    def find_casts(self):
        for m in self.models:
            for fd in m.funcdefs:
                for node in walk(fd.body):
                    if not isinstance(node, c_ast.Cast):
                        continue
                    try:
                        ct = m.tb.build(node.to_type, m.scope)
                    except Exception:
                        continue
                    if not (isinstance(ct, Ptr) and isinstance(ct.to, Struct)):
                        continue
                    st = ct.to
                    e = node.expr
                    if isinstance(e, c_ast.ID) and e.name in m.globals:
                        v = self.decl_view.get((m.fn, e.name)) or self.decl_view.get(('inspace.h', e.name))
                        if v is not None and v.kind.key[0] == 'ptr' and not self.type_views.get(id(st)):
                            self.add_view(v.kind, st, 0, m.fn)
                            self.report['views from casts'].append('%s (%s *)%s' % (m.fn, st.name, e.name))
                    elif isinstance(e, c_ast.UnaryOp) and e.op == '&' and isinstance(e.expr, c_ast.ID):
                        a = global_addr(e.expr.name)
                        if a is not None and self.table_at(a) is None and not self.type_views.get(id(st)):
                            self.overlays[id(st)] = (a, st, m.fn)
                            self.report['struct overlays on globals'].append(
                                '%s (%s *)&%s' % (m.fn, st.name, e.expr.name))

    # -- remaining struct types: match by typedef name and size -------------
    def find_other_kinds(self):
        byname = defaultdict(set)
        for k in self.kinds:
            for v in k.views:
                byname[(v.t.name, v.t.size())].add((k, v.delta))
        loose = defaultdict(list)
        first = self.models[0].fn
        for m in self.models:
            for name, (t, node) in m.typedefs.items():
                if not isinstance(t, Struct) or self.type_views.get(id(t)) or id(t) in self.overlays:
                    continue
                if node.coord.file != m.fn and m.fn != first:
                    continue
                cands = byname.get((t.name, t.size()))
                if cands and len(cands) == 1:
                    k, d = next(iter(cands))
                    self.add_view(k, t, d, m.fn)
                    self.report['matched by name'].append('%s %s -> %s' % (m.fn, t.name, k.key))
                else:
                    loose[(t.name, t.size())].append((t, m.fn))
        for (name, size), ts in sorted(loose.items()):
            layouts = {}
            for t, fn in ts:
                sig = tuple((f[0], repr(f[1]), f[2]) for f in t.fields)
                layouts.setdefault(sig, []).append((t, fn))
            for i, (sig, tl) in enumerate(sorted(layouts.items())):
                k = Kind(('local', name, i), size)
                for t, fn in tl:
                    self.add_view(k, t, 0, fn)
                self.kinds.append(k)

    # -- field merge ----------------------------------------------------------
    def merge_kinds(self):
        for k in self.kinds:
            items = []
            S = k.size
            for v in k.views:
                t = v.t
                r = v.delta % S if S else v.delta
                k.packed |= t.packed
                for name, ft, off in t.fields:
                    if is_pad(name, ft):
                        continue
                    a = off + r
                    if S and a >= S:
                        a -= S
                    if getattr(t, 'row', False):
                        name = None
                    if S and a + ft.size() > S and isinstance(ft, Arr):
                        es = ft.of.size() or 1
                        ft = Arr(ft.of, (S - a) // es)
                    items.append(Item(a, ft, name, v.file))
                    if isinstance(strip_arr(ft), Ptr):
                        k.has_ptr = True
            k.fields = merge_items(items, S, k.fmt, self.report['field types'], str(k.key))
            for a, b in zip(k.fields, k.fields[1:] + [None]):
                if isinstance(a.type, Arr) and a.type.n is None:
                    end = b.off if b is not None else S
                    es = a.type.of.size() or 1
                    a.type = Arr(a.type.of, max(1, (end - a.off) // es))
            seen = defaultdict(int)
            for f in k.fields:
                seen[f.name] += 1
            for f in k.fields:
                if seen[f.name] > 1 or f.name is None:
                    f.name = k.fmt(f.off)

    def name_kinds(self):
        used = defaultdict(list)
        for k in self.kinds:
            cnt = defaultdict(int)
            for v in k.views:
                if not v.t.name.startswith('anon'):
                    cnt[v.t.name] += 1
            k.name = max(cnt, key=lambda n: (cnt[n], -len(n), n)) if cnt else 'REC_%X' % k.size
            used[k.name].append(k)
        for name, ks in used.items():
            if len(ks) > 1:
                stem = re.sub(r'(?<=[0-9A-F])[A-Z]$', '', name) if re.match(r'^REC_?[0-9A-F]+[A-Z]$', name) \
                    else name
                for k in ks:
                    if k.key[0] == 'table':
                        k.name = '%s_%04X' % (stem, k.base)
                    elif k.key[0] == 'ptr':
                        k.name = '%s_P%04X' % (stem, k.key[1])
                    else:
                        k.name = '%s_%s' % (name, k.views[0].file.replace('.c', ''))

    # -- DGROUP globals -----------------------------------------------------
    def merge_globals(self):
        items = []
        self.folded = {}          # global name -> (table Kind, absolute addr)
        for m, g in self.all_decls():
            if g.addr is None:
                if not (g.block and 'static' in g.node.storage):
                    self.report['globals without address'].append('%s %s' % (m.fn, g.name))
                continue
            k = self.table_at(g.addr)
            if k is not None:
                if (m.fn, g.name) not in self.decl_view and not (
                        g.file == 'inspace.h' and ('inspace.h', g.name) in self.decl_view):
                    self.folded[g.name] = (k, g.addr)
                    # scalar inside a table: becomes a field of the record
                    off = (g.addr - k.base) % k.size
                    k.extra = getattr(k, 'extra', [])
                    k.extra.append(Item(off, g.type, None, m.fn))
                continue
            items.append(Item(g.addr, g.type, g.name, m.fn))
        for sid, (a, st, fn) in self.overlays.items():
            for name, ft, off in st.fields:
                if not is_pad(name, ft):
                    items.append(Item(a + off, ft, None, fn))
        known = defaultdict(int)
        for it in items:
            if isinstance(it.type, Arr) and it.type.n:
                known[it.off] = max(known[it.off], it.type.size())
        for a, n in MANUAL_ARRAYS.items():
            for it in items:
                if it.off == a and isinstance(it.type, Prim):
                    it.type = Arr(it.type, n)
                    break
            known[a] = max(known[a], 2 * n)
        for it in items:
            if isinstance(it.type, Arr) and it.type.n is None and known[it.off]:
                it.type = Arr(it.type.of, known[it.off] // max(1, it.type.of.size()))
        fields = merge_items(items, None, lambda a: 'g_%04x' % a, self.report['global types'], 'DS')
        for f in fields:
            g = Global(f.off, None, f.type)
            g.items = f.items
            names = {it.name for it in f.items if it.off == f.off and it.name}
            nm = [n for n in names if n in NAME_ADDR]
            g.name = nm[0] if nm else 'g_%04x' % f.off
            if any(n.startswith('g_fp_') for n in names) and not nm:
                g.name = 'g_fp_%04x' % f.off
            g.files = {it.file for it in f.items}
            self.globals[f.off] = g
        for t in self.tables:
            et = t
            for d in reversed(t.inner or []):
                et = Arr(et, d)
            g = Global(t.base, ADDR_NAME.get(t.base, 'g_%04x' % t.base), Arr(et, t.count))
            g.table = t
            g.items = []
            self.globals[t.base] = g
        # merge the fields that folded scalars add to table records
        for k in self.tables:
            if getattr(k, 'extra', None):
                items = [Item(f.off, f.type, f.name, 'merged') for f in k.fields] + k.extra
                k.fields = merge_items(items, k.size, k.fmt, self.report['field types'], str(k.key))

    def global_at(self, addr):
        """(Global, offset inside it) for a DS address, or (None, None)."""
        best = None
        for a, g in self.globals.items():
            if a <= addr:
                size = g.type.size() if not isinstance(g.type, Arr) or g.type.n else 0
                if hasattr(g, 'table'):
                    size = g.table.size * (g.table.count or 0)
                if addr < a + max(size, 1) and (best is None or a > best.addr):
                    best = g
        if best is None:
            return None, None
        return best, addr - best.addr


def run_report():
    mg = Merge(load_models())
    for k in mg.kinds:
        print('KIND', k.key, k.name, hex(k.size), 'views', len(k.views), 'count', k.count)
        for f in k.fields:
            print('   +%03x %-12s %r' % (f.off, f.name, f.type))
    for sec, lines in mg.report.items():
        print('==', sec, len(lines))
        for ln in lines:
            print('  ', ln)


if __name__ == '__main__' and len(sys.argv) > 1 and sys.argv[1] == '--merge-report':
    run_report()
    sys.exit(0)


# ---------------------------------------------------------------------------
# Port spelling of types
# ---------------------------------------------------------------------------

PRIM_PORT = {'char': 'char', 'schar': 'signed char', 'uchar': 'uint8_t', 'short': 'int16_t',
             'ushort': 'uint16_t', 'int': 'int16_t', 'uint': 'uint16_t', 'long': 'int32_t',
             'ulong': 'uint32_t', 'void': 'void', 'float': 'float', 'double': 'double'}


class Speller:
    """Writes Types as port C declarations."""

    def __init__(self, merge):
        self.mg = merge

    def kind_of(self, st):
        v = self.mg.view_of_type(st)
        return v.kind if v else None

    def base(self, t):
        if isinstance(t, Prim):
            return PRIM_PORT[t.name]
        if isinstance(t, Win):
            return t.name
        if isinstance(t, Struct) and t.name in CRT_STRUCTS:
            return 'struct %s' % t.name
        if isinstance(t, Struct):
            k = self.kind_of(t)
            if k is not None:
                return k.name
            if getattr(t, 'opaque', False) or t.file in ('',):
                return 'struct %s' % t.name
            # nested anonymous struct: spell inline
            return self.inline_struct(t)
        raise TypeError(t)

    def inline_struct(self, t, indent='    '):
        out = ['union {' if t.is_union else 'struct {']
        for name, ft, off in t.fields:
            out.append(indent + '    ' + self.decl(ft, name) + ';')
        out.append(indent + '}')
        return '\n'.join(out)

    def decl(self, t, inner):
        if isinstance(t, Kind):
            return (t.name + ' ' + inner).rstrip()
        if isinstance(t, (Prim, Win, Struct)):
            b = self.base(t)
            return (b + ' ' + inner).rstrip() if inner else b
        if isinstance(t, Ptr):
            if isinstance(t.to, (Arr, Func)):
                return self.decl(t.to, '(*' + inner + ')')
            return self.decl(t.to, '*' + inner)
        if isinstance(t, Arr):
            return self.decl(t.of, '%s[%s]' % (inner, '' if t.n is None else
                                               ('%d' % t.n if t.n < 16 else '0x%x' % t.n)))
        if isinstance(t, Func):
            ps = ', '.join(self.decl(pt, pn or '') for pn, pt in t.params) or 'void'
            if t.var:
                ps += ', ...'
            return self.decl(t.ret, '%s(%s)' % (inner, ps))
        raise TypeError(t)

    def typename(self, t):
        return self.decl(t, '')


# ---------------------------------------------------------------------------
# game.h
# ---------------------------------------------------------------------------

def kind_deps(k, mg):
    deps = []
    for f in k.fields:
        t = strip_arr(f.type)
        if isinstance(t, Struct):
            v = mg.view_of_type(t)
            if v is not None and v.kind is not k:
                deps.append(v.kind)
    return deps


def emit_game_h(mg, path):
    sp = Speller(mg)
    out = []
    w = out.append
    w('/* Game declarations for the native port, generated by tools/port_merge.py')
    w(' * from the decomp in src/inspace/.  Do not edit by hand; rerun the script.')
    w(' * Records keep the original byte layout (16-bit ints, pack as in the')
    w(' * original); globals are named by their DS offset until understood. */')
    w('#ifndef GAME_H')
    w('#define GAME_H')
    w('')
    w('#include <stdint.h>')
    w('#include "win16api.h"')
    w('')
    w('/* Low and high halves of a 32-bit variable seen as 16-bit words, and a')
    w(' * typed view of a record at a byte offset from a field (little endian,')
    w(' * as the original). */')
    w('#define LO16(v) (((int16_t *)&(v))[0])')
    w('#define HI16(v) (((int16_t *)&(v))[1])')
    w('#define LO8(v) (((char *)&(v))[0])')
    w('#define HI8(v) (((char *)&(v))[1])')
    w('#define VIEW(T, field, off) (*(T *)((uint8_t *)&(field) + (off)))')
    w('#define VIEWP(PT, field, off) ((PT)((uint8_t *)&(field) + (off)))')
    w('')
    # kinds in dependency order
    used = [k for k in mg.kinds if k.fields or k.views]
    done = set()
    order = []

    def visit(k, stack=()):
        if id(k) in done or k in stack:
            return
        for d in kind_deps(k, mg):
            visit(d, stack + (k,))
        done.add(id(k))
        order.append(k)
    for k in used:
        visit(k)
    for k in order:
        if all(getattr(v.t, 'row', False) for v in k.views) and k.key[0] != 'table':
            continue
        where = ''
        if k.key[0] == 'table':
            where = 'records at DS:%04x' % k.base
        elif k.key[0] == 'ptr':
            where = 'reached through the far pointer(s) at DS:%04x' % k.key[1]
        else:
            where = 'used in %s' % ', '.join(sorted({v.file for v in k.views}))
        w('/* 0x%x bytes; %s. */' % (k.size, where))
        pack = 1 if k.packed else 2
        w('#pragma pack(push, %d)' % pack)
        w('typedef struct {')
        off = 0
        for f in k.fields:
            if f.off > off:
                w('    uint8_t pad_%02x[0x%x];' % (off, f.off - off))
            elif f.off < off:
                w('    /* TODO: field at +%x overlaps the previous one */' % f.off)
            d = sp.decl(f.type, f.name)
            w('    %s;' % d)
            off = max(off, f.off + max(f.size, 0))
        if k.size and off < k.size:
            w('    uint8_t pad_%02x[0x%x];' % (off, k.size - off))
        w('} %s;' % k.name)
        w('#pragma pack(pop)')
        w('')
    if any(k.name == 'OBJREF' for k in order):
        w('/* An OBJREF packed in a word as (type << 8) | idx, as some functions')
        w(' * return it. */')
        w('static inline OBJREF objref_of(int16_t w)')
        w('{')
        w('    OBJREF r;')
        w('    r.idx = (uint8_t)w;')
        w('    r.type = (uint8_t)((uint16_t)w >> 8);')
        w('    return r;')
        w('}')
        w('')
    # other typedefs (function pointer types and the like)
    seen = {}
    for m in mg.models:
        for name, (t, node) in m.typedefs.items():
            if isinstance(t, Struct) or name in seen:
                continue
            d = sp.decl(t, name)
            seen[name] = d
            w('typedef %s;' % d)
    w('')
    # globals
    w('/* DGROUP globals, by DS offset.  Plain data lives in the DGROUP image')
    w(' * at its 1994 offset, so neighbours, overlapping views and overruns')
    w(' * behave as they did; globals holding native pointers are variables')
    w(' * (globals.c).  The image starts as the data segment of INSPACE.EXE. */')
    w('extern uint8_t dgroup[0x10000];')
    w('#define DGROUP_AT(T, off) (*(T)(dgroup + (off)))')
    for a, g, t, kind in global_layout(mg):
        cm = ' /* DS:%04x */' % a
        if a in INFERRED_DS:
            cm = ' /* DS:%04x %s [inferred] */' % (a, INFERRED_DS[a])
        d = sp.decl(g.type if kind == 'image' else t, '(*)')
        if '{' in d:
            # an anonymous struct type gets a name
            w('typedef %s;' % sp.decl(t, anon_type_name(a)))
            d = '%s (*)' % anon_type_name(a)
        if kind == 'image':
            w('#define %s DGROUP_AT(%s, 0x%04x)%s' % (g.name, d, a, cm))
        else:
            w('extern %s;%s' % (sp.decl(t, g.name), cm))
    w('')
    w('/* Game functions. */')
    for name, (t, file, addr) in sorted(mg.functions.items(), key=lambda x: x[1][2] or (99, 0)):
        mm = re.match(r'^fn_(\d\d)_([0-9a-f]{4})$', name)
        inf = INFERRED_FN.get((int(mm.group(1)), int(mm.group(2), 16))) if mm else \
            (name if name in INFERRED_IDENT else None)
        w('%s;%s' % (sp.decl(t, name), ' /* %s [inferred] */' % inf if inf else ''))
    w('')
    w('#endif')
    with open(path, 'w') as f:
        f.write(apply_names('\n'.join(out) + '\n'))


def anon_type_name(addr):
    return 'ANON_%04X' % addr


def type_has_ptr(t, mg, seen=()):
    if isinstance(t, Ptr):
        return True
    if isinstance(t, Arr):
        return type_has_ptr(t.of, mg, seen)
    if isinstance(t, Struct):
        v = mg.view_of_type(t)
        if v is not None:
            t = v.kind
        else:
            return any(type_has_ptr(ft, mg, seen) for _, ft, _ in t.fields)
    if isinstance(t, Kind):
        if id(t) in seen:
            return False
        return t.has_ptr or any(type_has_ptr(f.type, mg, seen + (id(t),)) for f in t.fields)
    return False


def global_layout(mg):
    """(addr, Global, sized type, kind) for every DGROUP global.  kind is
    'image' for pointer-free data, which lives in the DGROUP image at its
    1994 offset; 'near' for a near pointer into DGROUP; 'native' for far
    pointers, which are native variables set at run time."""
    addrs = sorted(mg.globals)
    out = []
    for i, a in enumerate(addrs):
        g = mg.globals[a]
        t = g.type
        end = addrs[i + 1] if i + 1 < len(addrs) else 0x10000
        if isinstance(t, Arr) and t.n is None:
            es = t.of.size() if not isinstance(t.of, Kind) else t.of.size
            t = Arr(t.of, max(1, (end - a) // max(1, es)))
        if isinstance(t, Ptr) and not t.far and not isinstance(t.to, Func):
            kind = 'near'
        elif type_has_ptr(t, mg):
            kind = 'native'
        else:
            kind = 'image'
        out.append((a, g, t, kind))
    return out


def emit_globals_c(mg, path):
    """Definitions of the globals that hold native pointers, and the near
    pointers dgroup.c points into the DGROUP image at start-up."""
    sp = Speller(mg)
    defs, rows = [], []
    for a, g, t, kind in global_layout(mg):
        if kind == 'image':
            continue
        defs.append('%s;' % sp.decl(t, g.name))
        if kind == 'near':
            rows.append('    {0x%04x, (void **)&%s},' % (a, g.name))
    out = ['/* DGROUP globals holding native pointers (the others live in the',
           ' * DGROUP image, see game.h).  Generated by tools/port_merge.py; do',
           ' * not edit by hand. */',
           '#include "game.h"',
           '#include "globals.h"',
           '']
    out += defs
    out += ['', '/* Near pointers into DGROUP, by DS offset of the pointer. */',
            'const NearPtrInit game_near_ptrs[] = {'] + rows + ['};',
            'const int game_near_ptr_count = %d;' % len(rows), '']
    with open(path, 'w') as f:
        f.write(apply_names('\n'.join(out)))


INFERRED_DS = {o: n for (s, o), n in INFERRED.items() if s == 0x1090}
INFERRED_FN = {((s - 0x1000) // 8 + 1, o): n for (s, o), n in INFERRED.items() if s != 0x1090}


def collect_functions(mg):
    """name -> (Func type, file, (seg, off)) for every defined function."""
    funcs = {}
    for m in mg.models:
        tags = addr_tags(m.src)
        for fd in m.funcdefs:
            name = fd.decl.name
            t, _ = m.funcs[name]
            line = fd.decl.coord.line
            addr = tags.get(line)
            stub = is_stub(m, fd)
            if name in funcs and (stub or not funcs[name][3]):
                continue
            funcs[name] = (t, m.fn, addr, stub)
    mg.functions = {n: (t, f, a) for n, (t, f, a, s) in funcs.items()}
    return mg.functions


def addr_tags(src):
    """{line of definition: (seg, off)} from '/* @addr SEG:OFF */' tags."""
    tags = {}
    lines = src.split('\n')
    for i, l in enumerate(lines):
        m = re.search(r'@addr\s+([0-9a-fA-F]+):([0-9a-fA-F]+)', l)
        if m:
            tags[i + 2] = (int(m.group(1), 16), int(m.group(2), 16))
    return tags


def is_stub(m, fd):
    """Stub definitions that only exist to force near calls in the 1994 build."""
    line = fd.decl.coord.line
    tags = addr_tags(m.src)
    if line in tags:
        return False
    return True


if __name__ == '__main__' and (len(sys.argv) == 1 or sys.argv[1] == '--emit'):
    mg = Merge(load_models())
    collect_functions(mg)
    os.makedirs(OUT, exist_ok=True)
    emit_game_h(mg, os.path.join(OUT, 'game.h'))
    print('wrote', os.path.join(OUT, 'game.h'))


# ---------------------------------------------------------------------------
# win16api.h: the Windows and runtime calls the game makes, declared with
# fixed-width types (implementations come later)
# ---------------------------------------------------------------------------

MSVC_INC = os.path.join(os.environ.get('MSVC_DIR', '/home/user/toolchain/msvc'), 'INCLUDE')
API_HEADERS = ['WINDOWS.H', 'MMSYSTEM.H', 'SHELLAPI.H', 'DOS.H', 'IO.H', 'DIRECT.H',
               'SYS/STAT.H', 'SYS/UTIME.H', 'SYS/TYPES.H', 'STDLIB.H', 'STRING.H', 'TIME.H',
               'MALLOC.H', 'MEMORY.H', 'STDIO.H', 'CTYPE.H', 'MATH.H']

# Standard C functions: taken from the host's libc headers.
STD_FUNCS = {
    'string.h': 'strlen strcpy strcat strcmp strncpy strncmp strchr strrchr strstr memcpy memset '
                'memcmp memmove strncat',
    'stdlib.h': 'rand srand atoi atol abs labs malloc free calloc realloc qsort exit',
    'stdio.h': 'sprintf printf fopen fclose fread fwrite fprintf sscanf',
    'time.h': 'time localtime mktime',
    'ctype.h': 'toupper tolower isdigit isalpha isspace isupper islower',
    'stdarg.h': '',
}
STD_OF = {f: h for h, fs in STD_FUNCS.items() for f in fs.split()}

# 1994 runtime functions whose behaviour or types differ from the host's
# libc: the port supplies its own under another name.
RUNTIME_RENAMES = '''
/* The 1994 runtime's versions, not the host's (port/src/win/crt.c). */
#define rand msc_rand
#define srand msc_srand
#define stat dos_stat
#define utime dos_utime
#define _dev_t dos_dev_t
#define _ino_t dos_ino_t
#define _off_t dos_off_t
/* The game's entry point (2:0000); WinMain is the platform's own. */
#define WinMain inspace_WinMain
int16_t msc_rand(void);
void msc_srand(uint16_t seed);'''

HAND_MACROS = r'''
#define LOBYTE(w) ((BYTE)((WORD)(w) & 0xff))
#define HIBYTE(w) ((BYTE)((WORD)(w) >> 8))
#define LOWORD(l) ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l) ((WORD)((DWORD)(l) >> 16))
#define MAKELONG(lo, hi) ((LONG)(((WORD)(lo)) | (((DWORD)(WORD)(hi)) << 16)))
#define MAKELPARAM(lo, hi) ((LPARAM)MAKELONG(lo, hi))
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(b)) << 16)))
#define PALETTERGB(r, g, b) (0x02000000UL | RGB(r, g, b))
#define PALETTEINDEX(i) ((COLORREF)(0x01000000UL | (DWORD)(WORD)(i)))
#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb) >> 16))
#define MAKEINTRESOURCE(i) ((LPCSTR)(uintptr_t)(WORD)(i))
#define MAKEPOINT(l) (*(POINT *)&(l))
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
'''

BASIC_TYPES = r'''
typedef int16_t BOOL;
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint16_t UINT;
typedef int32_t LONG;
typedef uint16_t WPARAM;
typedef int32_t LPARAM;
typedef int32_t LRESULT;
typedef uint32_t COLORREF;
typedef int16_t HFILE;
typedef uint16_t ATOM;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef char *PSTR;
typedef void *LPVOID;
typedef uint8_t *LPBYTE;
typedef WORD *LPWORD;
typedef DWORD *LPDWORD;
typedef int16_t *LPINT;
#define TRUE 1
#define FALSE 0
typedef int16_t _dev_t;
typedef uint16_t _ino_t;
typedef int32_t _off_t;
'''


def _clean_header(text):
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    text = re.sub(r'//[^\n]*', ' ', text)
    return text


HDR_DROP = {'FAR', 'NEAR', '_far', '__far', '_near', '__near', 'far', 'near', 'WINAPI', 'CALLBACK',
            'PASCAL', '_pascal', '__pascal', '__cdecl', '_cdecl', 'cdecl', '_export', '__export',
            '_loadds', '__loadds', 'huge', '_huge', '__huge', '_FAR_', '_CRTAPI1', '_CRTAPI2',
            '__interrupt', '_interrupt', 'pascal', 'VFWAPI', 'STDAPI', '_based', 'APIENTRY',
            'CDECL', '_CDECL', '__CDECL'}


def port_c_types(text):
    """Map 16-bit C type words in a declaration fragment to fixed width."""
    toks = re.findall(r'[A-Za-z_]\w*|\d\w*|\S', text)
    out = []
    i = 0
    while i < len(toks):
        t = toks[i]
        if t in HDR_DROP:
            i += 1
            continue
        if t in ('unsigned', 'signed', 'int', 'long', 'short', 'char'):
            words = []
            while i < len(toks) and toks[i] in ('unsigned', 'signed', 'int', 'long', 'short', 'char'):
                words.append(toks[i])
                i += 1
            if 'char' in words:
                out.append('uint8_t' if 'unsigned' in words else 'char')
            elif 'long' in words:
                out.append('uint32_t' if 'unsigned' in words else 'int32_t')
            else:
                out.append('uint16_t' if 'unsigned' in words else 'int16_t')
            continue
        out.append(t)
        i += 1
    s = ''
    for t in out:
        if s and (re.match(r'\w', t) and re.match(r'(?s).*\w$', s)):
            s += ' '
        elif t == '*' and s and s[-1] not in '(*':
            s += ' '
        elif s and s[-1] == ',':
            s += ' '
        s += t
    return s


def read_headers():
    protos, defines, structs, typedefs = {}, {}, {}, {}
    for h in API_HEADERS:
        p = os.path.join(MSVC_INC, h)
        if not os.path.exists(p):
            continue
        with open(p, encoding='latin-1') as f:
            text = _clean_header(f.read())
        text = re.sub(r'\\\n', ' ', text)
        for m in re.finditer(r'^[ \t]*#[ \t]*define[ \t]+(\w+)[ \t]+([^\n]+)$', text, re.M):
            defines.setdefault(m.group(1), (m.group(2).strip(), h))
        body = re.sub(r'^[ \t]*#[^\n]*$', ' ', text, flags=re.M)
        for m in re.finditer(r'typedef\s+struct\s+(\w+)?\s*\{([^{}]*)\}\s*([^;]*);', body):
            names = [n.strip() for n in m.group(3).split(',')]
            for n in names:
                n2 = n.replace('FAR', '').replace('NEAR', '').replace('*', '').strip()
                if '*' in n:
                    typedefs.setdefault(n2, ('ptr', names[0].strip()))
                elif n2:
                    structs.setdefault(n2, (m.group(1), m.group(2), h))
        for m in re.finditer(r'struct\s+(\w+)\s*\{([^{}]*)\}\s*;', body):
            structs.setdefault('struct ' + m.group(1), (m.group(1), m.group(2), h))
        for m in re.finditer(r'typedef\s+([\w\s]+?)\s*(?:FAR|NEAR)?\s*\*\s*(\w+)\s*;', body):
            typedefs.setdefault(m.group(2), ('ptr', m.group(1).replace('FAR', '').strip()))
        for chunk in re.split(r'[;{}]', body):
            m = re.fullmatch(r'\s*([A-Za-z_][\w\s\*]*?)\b(\w+)\s*\(([^()]*)\)\s*', chunk)
            if not m:
                continue
            name = m.group(2)
            ret = m.group(1)
            if 'typedef' in ret or name in ('if', 'while', 'return', 'sizeof'):
                continue
            protos.setdefault(name, (ret.strip(), m.group(3).strip(), h))
    return protos, defines, structs, typedefs


def used_externals(models, mg):
    declared = set(mg.functions)
    calls, ids = set(), set()
    local_names = set()
    for m in models:
        declared |= set(m.globals) | {g.name for g in m.block_externs} | set(m.funcs)
        for fd in m.funcdefs:
            for n in walk(fd):
                if isinstance(n, c_ast.Decl) and n.name:
                    local_names.add(n.name)
                if isinstance(n, c_ast.FuncCall) and isinstance(n.name, c_ast.ID):
                    calls.add(n.name.name)
                elif isinstance(n, c_ast.ID):
                    ids.add(n.name)
        for name in m.protos:
            if name not in m.funcs and name not in mg.functions:
                calls.add(name) if False else None
    calls -= declared
    ids -= declared | local_names | calls
    return calls, ids


def emit_win16api_h(mg, path):
    protos, defines, structs, typedefs = read_headers()
    calls, ids = used_externals(mg.models, mg)
    calls -= {'va_start', 'va_end', 'va_arg', 'SC', 'GETPROC'}
    out = []
    w = out.append
    w('/* Windows 3.1 and C runtime calls made by the game, with fixed-width')
    w(' * types (int is 16 bits, long 32 bits in the original).  Generated by')
    w(' * tools/port_merge.py from the MSVC 1.5x headers; the implementations are')
    w(' * native and come later. */')
    w('#ifndef WIN16API_H')
    w('#define WIN16API_H')
    w('')
    w('#include <stdint.h>')
    w('#include <stddef.h>')
    w('#include <stdarg.h>')
    std_h = sorted({STD_OF[c] for c in calls if c in STD_OF})
    for h in std_h:
        w('#include <%s>' % h)
    w(RUNTIME_RENAMES)
    w(BASIC_TYPES)
    handles = sorted(n for n in WIN_TYPES if n.startswith('H') and n not in ('HFILE',))
    for h in handles:
        w('typedef uint16_t %s;' % h)
    w('typedef HANDLE HGLOBAL_;')
    w('typedef int16_t (*FARPROC)(void);')
    w('typedef LRESULT (*WNDPROC)(HWND, UINT, WPARAM, LPARAM);')
    w('typedef BOOL (*DLGPROC)(HWND, UINT, WPARAM, LPARAM);')
    w('typedef void (*TIMERPROC)(HWND, UINT, UINT, DWORD);')
    w('')
    # structs used by name
    want = [n for n in WIN_TYPES if WIN_TYPES[n][1] == n and n in structs]
    for alias, real in (('struct stat', 'struct _stat'), ('struct utimbuf', 'struct _utimbuf')):
        if real in structs:
            structs[alias] = (alias.split()[1],) + structs[real][1:]
    want += ['struct _find_t', 'struct stat', 'struct utimbuf']
    if 'time.h' not in std_h:
        want.append('struct tm')
    emitted = set()
    lines = []

    def emit_struct(n):
        if n in emitted or n not in structs:
            return
        emitted.add(n)
        tag, body, h = structs[n]
        # dependencies
        for dep in re.findall(r'\b([A-Z][A-Z0-9_]+)\b', body):
            if dep in structs and dep != n:
                emit_struct(dep)
        fields = [port_c_types(x.strip()) + ';' for x in body.split(';') if x.strip()]
        if n.startswith('struct '):
            lines.append('%s {' % n)
            lines.extend('    ' + f for f in fields)
            lines.append('};')
        else:
            lines.append('typedef struct {')
            lines.extend('    ' + f for f in fields)
            lines.append('} %s;' % n)
        lines.append('')
    for n in want:
        emit_struct(n)
    out.extend(lines)
    w('#define find_t _find_t')
    for n in sorted(emitted):
        if not n.startswith('struct ') and ('LP' + n) in typedefs:
            w('typedef %s *LP%s;' % (n, n))
    w('typedef POINT *LPPOINT;') if 'LPPOINT' not in ['LP' + n for n in emitted] else None
    w('')
    w(HAND_MACROS)
    # constants
    consts = []
    seen = set()

    def add_const(n, depth=0):
        if n in seen or n not in defines or depth > 4 or n in ('NULL', 'TRUE', 'FALSE'):
            return
        seen.add(n)
        val, h = defines[n]
        for dep in re.findall(r'\b([A-Z_][A-Z0-9_]+)\b', val):
            if dep in defines and dep not in BASIC_TYPES and dep not in WIN_TYPES:
                add_const(dep, depth + 1)
        val = port_c_types(val) if re.search(r'\b(int|long|unsigned)\b', val) else val
        consts.append('#define %s %s' % (n, val))
    missing = []
    for n in sorted(ids):
        if n in defines:
            add_const(n)
        elif re.match(r'^[A-Z][A-Z0-9_]+$', n):
            missing.append(n)
    w('/* Constants. */')
    out.extend(c for c in consts if not re.search(r'\b(min|max|RGB|LOWORD|HIWORD|MAKELONG|LOBYTE|HIBYTE|'
                                                    r'MAKEINTRESOURCE|MAKEPOINT|PALETTERGB|PALETTEINDEX|'
                                                    r'MAKELPARAM)\b', c.split()[1]))
    w('')
    w('/* Functions. */')
    unknown = []
    for c in sorted(calls):
        if c in STD_OF or c in ('min', 'max') or c in HAND_MACROS:
            continue
        if c in protos:
            ret, params, h = protos[c]
            ret = port_c_types(ret)
            params = port_c_types(params) if params else 'void'
            w('%s %s(%s);' % (ret, c, params))
        else:
            unknown.append(c)
    w('')
    w('#endif')
    with open(path, 'w') as f:
        f.write(apply_names('\n'.join(out) + '\n'))
    mg.report['api calls not found in the headers'] = unknown
    mg.report['identifiers not found in the headers'] = missing
