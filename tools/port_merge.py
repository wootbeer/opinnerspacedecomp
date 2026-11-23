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
    'struct find_t { int x; }; struct _find_t { int x; }; struct stat { int x; };\n' \
    'struct tm { int x; }; struct utimbuf { int x; };\n'
PRELUDE_LINES = PRELUDE.count('\n')


_HDR = None


def header_parse_text():
    global _HDR
    if _HDR is None:
        with open(os.path.join(SRC, 'inspace.h'), encoding='latin-1') as f:
            _HDR = '# 1 "inspace.h"\n' + ParseText(f.read()).text + '\n'
    return _HDR


def prepare(path):
    """Return (src_text_after_macro_expansion, ParseText, ast)."""
    with open(path, encoding='latin-1') as f:
        raw = f.read()
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
