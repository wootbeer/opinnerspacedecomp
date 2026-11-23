#!/usr/bin/env python3
"""Translate the decomp's src/inspace/segNN*.c into port/src/game/segNN*.c.

Uses the merged model of tools/port_merge.py: file-local typedefs and
externs are dropped in favour of game.h, accesses through other views of
a table are rewritten onto the merged table, 16-bit types become fixed
width types, and the 1994 compiler's keywords and tags are removed.

Run from the repository root:  python3 -I tools/port_translate.py [FILE.c ...]
"""
import os
import re
import sys
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import port_merge as pm  # noqa: E402
from port_merge import (Prim, Win, Ptr, Arr, Func, Struct, Kind, c_ast,  # noqa: E402
                        strip_arr, lex, walk)

OUT = pm.OUT

# ---------------------------------------------------------------------------
# Edits on the source text
# ---------------------------------------------------------------------------


class Edits:
    """Non-overlapping (or properly nested) replacements on a text.

    A replacement is a list of pieces: strings, or (start, end) spans of
    the original text rendered with the edits inside them."""

    def __init__(self, text):
        self.text = text
        self.edits = []          # (start, end, pieces, prio)

    def add(self, s, e, pieces, prio=0):
        if isinstance(pieces, str):
            pieces = [pieces]
        self.edits.append((s, e, pieces, prio))

    def render(self, s=0, e=None):
        if e is None:
            e = len(self.text)
        inner = [x for x in self.edits if s <= x[0] and x[1] <= e and (x[0], x[1]) != (s, e)]
        # keep outermost edits only
        inner.sort(key=lambda x: (x[0], -(x[1] - x[0]), -x[3]))
        top = []
        for x in inner:
            if top and x[0] < top[-1][1] and not (x[0] == x[1] == top[-1][0] == top[-1][1]):
                # nested or overlapping: inner insertions at the same point are kept
                if x[0] >= top[-1][0] and x[1] <= top[-1][1] and top[-1][0] != top[-1][1]:
                    continue
                if x[0] == x[1] and top[-1][0] < x[0] < top[-1][1]:
                    continue
                if x[0] < top[-1][1] and x[1] > top[-1][1]:
                    raise ValueError('overlapping edits %r %r' % (top[-1][:2], x[:2]))
            top.append(x)
        out = []
        pos = s
        for (a, b, pieces, prio) in top:
            out.append(self.text[pos:a])
            for p in pieces:
                if isinstance(p, tuple):
                    out.append(self.render_span(p[0], p[1]))
                else:
                    out.append(p)
            pos = max(pos, b)
        out.append(self.text[pos:e])
        return ''.join(out)

    def render_span(self, s, e):
        return self.render(s, e)


# ---------------------------------------------------------------------------
# Type spelling inside function bodies (token level)
# ---------------------------------------------------------------------------

BASE_WORDS = {'unsigned', 'signed', 'int', 'long', 'short', 'char'}


def spell_base(words):
    w = [x for x in words]
    uns = 'unsigned' in w
    sig = 'signed' in w
    if 'char' in w:
        return 'uint8_t' if uns else ('signed char' if sig else 'char')
    if 'long' in w:
        return 'uint32_t' if uns else 'int32_t'
    return 'uint16_t' if uns else 'int16_t'


# ---------------------------------------------------------------------------
# Expression typing
# ---------------------------------------------------------------------------

class VT:
    """Type of an expression plus the view it carries (for structs)."""
    __slots__ = ('t', 'view')

    def __init__(self, t, view=None):
        self.t, self.view = t, view


class FileTranslator:
    def __init__(self, m, mg, sp):
        self.m, self.mg, self.sp = m, mg, sp
        self.src = m.src
        self.ed = Edits(m.src)
        self.toks = [t for t in lex(m.src)]
        self.tokpos = {t.pos: i for i, t in enumerate(self.toks)}
        self.notes = []
        self.counts = defaultdict(int)

    # -- positions ------------------------------------------------------------
    def pos(self, node):
        c = node.coord
        if c is None or c.file != self.m.fn:
            return None
        try:
            return self.m.pt.src_pos(c.line, c.column)
        except KeyError:
            return None

    def tok_at(self, pos):
        return self.tokpos.get(pos)

    def next_sig(self, i):
        i += 1
        while i < len(self.toks) and self.toks[i].kind in ('ws', 'nl', 'comment'):
            i += 1
        return i

    def prev_sig(self, i):
        i -= 1
        while i >= 0 and self.toks[i].kind in ('ws', 'nl', 'comment'):
            i -= 1
        return i

    def match_close(self, i):
        """Index of the bracket closing the one at token i."""
        op = self.toks[i].text
        cl = {'(': ')', '[': ']', '{': '}'}[op]
        d = 0
        for j in range(i, len(self.toks)):
            t = self.toks[j]
            if t.kind != 'punct':
                continue
            if t.text == op:
                d += 1
            elif t.text == cl:
                d -= 1
                if d == 0:
                    return j
        return None

    def node_start(self, node):
        best = None
        for n in walk(node):
            p = self.pos(n)
            if p is not None and (best is None or p < best):
                best = p
        if best is None:
            return None
        # a cast or parenthesised start: include an opening paren we are inside
        return best

    def node_end(self, node):
        """End offset of an expression node (exclusive)."""
        if isinstance(node, c_ast.ID):
            p = self.pos(node)
            return p + len(node.name)
        if isinstance(node, c_ast.Constant):
            p = self.pos(node)
            i = self.tok_at(p)
            return p + len(self.toks[i].text) if i is not None else None
        if isinstance(node, c_ast.StructRef):
            return self.node_end(node.field)
        if isinstance(node, c_ast.ArrayRef):
            e = self.node_end(node.name)
            if e is None:
                return None
            i = self.tok_at(self.find_tok(e, '['))
            j = self.match_close(i)
            return self.toks[j].pos + 1
        if isinstance(node, c_ast.FuncCall):
            e = self.node_end(node.name)
            i = self.tok_at(self.find_tok(e, '('))
            j = self.match_close(i)
            return self.toks[j].pos + 1
        if isinstance(node, c_ast.UnaryOp) and node.op in ('p++', 'p--'):
            e = self.node_end(node.expr)
            return self.find_tok(e, node.op[1:]) + 2
        if isinstance(node, c_ast.UnaryOp) or isinstance(node, c_ast.Cast):
            e = self.node_end(node.expr)
            return self.close_parens(e, node)
        return None

    def close_parens(self, e, node):
        return e

    def find_tok(self, pos, text):
        """Position of the first token with this text at or after pos."""
        i = self.tok_at(pos)
        if i is None:
            # pos is just after a token
            for j, t in enumerate(self.toks):
                if t.pos >= pos:
                    i = j
                    break
        while i < len(self.toks) and self.toks[i].text != text:
            i += 1
        return self.toks[i].pos

    # -- type resolution ----------------------------------------------------
    def view_of(self, t, gname=None):
        if gname is not None:
            v = self.mg.decl_view.get((self.m.fn, gname)) or self.mg.decl_view.get(('inspace.h', gname))
            if v is not None:
                return v
        st = strip_arr(t)
        while isinstance(st, Ptr):
            st = strip_arr(st.to)
        if isinstance(st, Struct):
            return self.mg.view_of_type(st)
        return None

    def typeof(self, node, scope):
        try:
            return self._typeof(node, scope)
        except Exception:
            return None

    def _typeof(self, node, scope):
        if isinstance(node, c_ast.ID):
            t = scope.lookup(node.name)
            if t is None:
                return None
            g = self.global_decl(node.name, scope)
            return VT(t, self.view_of(t, node.name if g else None))
        if isinstance(node, c_ast.Constant):
            if node.type == 'string':
                return VT(Ptr(Prim('char'), True))
            return VT(Prim('long' if node.value.lower().endswith('l') else 'int'))
        if isinstance(node, c_ast.ArrayRef):
            b = self.typeof(node.name, scope)
            if b is None:
                return None
            t = b.t
            if isinstance(t, (Arr, Ptr)):
                inner = t.of if isinstance(t, Arr) else t.to
                return VT(inner, b.view)
            return None
        if isinstance(node, c_ast.StructRef):
            b = self.typeof(node.name, scope)
            if b is None:
                return None
            st = b.t
            if node.type == '->':
                st = st.to if isinstance(st, Ptr) else (st.of if isinstance(st, Arr) else None)
            if isinstance(st, Win) and st.name in Win.FIELDS:
                return VT(Prim('int'))
            if not isinstance(st, Struct):
                return None
            f = st.field(node.field.name)
            if f is None:
                return None
            return VT(f[1], self.view_of(f[1]))
        if isinstance(node, c_ast.UnaryOp):
            if node.op == '&':
                b = self.typeof(node.expr, scope)
                return VT(Ptr(b.t, True), b.view) if b else None
            if node.op == '*':
                b = self.typeof(node.expr, scope)
                if b is None:
                    return None
                t = b.t
                if isinstance(t, Ptr):
                    return VT(t.to, b.view)
                if isinstance(t, Arr):
                    return VT(t.of, b.view)
                return None
            if node.op == 'sizeof':
                return VT(Prim('uint'))
            return self.typeof(node.expr, scope)
        if isinstance(node, c_ast.Cast):
            t = self.m.tb.build(node.to_type, scope)
            return VT(t, self.view_of(t))
        if isinstance(node, c_ast.FuncCall):
            ft = self.typeof(node.name, scope)
            if ft is None:
                return None
            t = ft.t
            if isinstance(t, Ptr):
                t = t.to
            if isinstance(t, Func):
                return VT(t.ret, self.view_of(t.ret))
            return None
        if isinstance(node, c_ast.BinaryOp):
            a = self.typeof(node.left, scope)
            if a is not None and isinstance(a.t, (Ptr, Arr)) and node.op in ('+', '-'):
                b = self.typeof(node.right, scope)
                if b is not None and isinstance(b.t, (Ptr, Arr)):
                    return VT(Prim('int'))
                return VT(a.t if isinstance(a.t, Ptr) else Ptr(a.t.of, True), a.view)
            b = self.typeof(node.right, scope)
            if b is not None and isinstance(b.t, (Ptr, Arr)) and node.op == '+':
                return VT(b.t if isinstance(b.t, Ptr) else Ptr(b.t.of, True), b.view)
            if node.op in ('<', '>', '<=', '>=', '==', '!=', '&&', '||'):
                return VT(Prim('int'))
            return a or b
        if isinstance(node, c_ast.Assignment):
            return self.typeof(node.lvalue, scope)
        if isinstance(node, c_ast.TernaryOp):
            return self.typeof(node.iftrue, scope) or self.typeof(node.iffalse, scope)
        if isinstance(node, c_ast.ExprList):
            return self.typeof(node.exprs[-1], scope)
        return None

    def global_decl(self, name, scope):
        """True if name resolves to a global (not shadowed by a local)."""
        s = scope
        while s is not None:
            if name in s.vars:
                return s.parent is None or getattr(s, 'is_global', False)
            s = s.parent
        return False

    # -- merged-layout paths --------------------------------------------------
    def sub_path(self, t, off, size, vt, path):
        """Access of type vt (size bytes) at byte off inside merged type t.

        Returns (pre, path, post): the access is pre + <expr><path> + post,
        or None if it cannot be expressed."""
        tsz = t.size if isinstance(t, Kind) else t.size()
        if off == 0 and tsz == size and self.compatible(t, vt):
            return ('', path, '')
        if isinstance(t, Kind):
            for f in t.fields:
                if f.off <= off and off + size <= f.off + max(f.size, 0):
                    return self.sub_path(f.type, off - f.off, size, vt, path + '.' + f.name)
                if f.off <= off < f.off + max(f.size, 1) and isinstance(f.type, Arr) and \
                        isinstance(vt, Arr):
                    # array view longer than the merged field: same start
                    return self.sub_path(f.type, off - f.off, f.size, vt, path + '.' + f.name)
            return self.view_cast(t, off, size, vt, path)
        if isinstance(t, Win) and t.name in Win.FIELDS:
            for n, o, _ in Win.FIELDS[t.name]:
                if o == off and size == 2 and not isinstance(vt, (Ptr, Arr)):
                    return ('', path + '.' + n, '')
            return self.view_cast(t, off, size, vt, path)
        if isinstance(t, Arr):
            es = t.of.size() if not isinstance(t.of, Kind) else t.of.size
            if es and isinstance(vt, Arr) and off % es == 0 and \
                    self.compatible(strip_arr(t), strip_arr(vt)):
                if off == 0:
                    return ('', path, '')
                return ('(', path, ' + %d)' % (off // es))
            if es and off // es < (t.n or 1 << 30) and off % es + size <= es:
                return self.sub_path(t.of, off % es, size, vt, path + '[%d]' % (off // es))
            return self.view_cast(t, off, size, vt, path)
        if tsz == 4 and size == 2 and off in (0, 2) and not isinstance(vt, (Ptr, Arr, Struct, Win)) \
                or (isinstance(vt, Win) and vt.name in pm.HANDLE_NAMES and tsz == 4 and size == 2):
            return ('LO16(' if off == 0 else 'HI16(', path, ')')
        if tsz == 2 and size == 1 and off in (0, 1) and isinstance(vt, Prim):
            return ('LO8(' if off == 0 else 'HI8(', path, ')')
        return self.view_cast(t, off, size, vt, path)

    def view_cast(self, t, off, size, vt, path):
        self.counts['VIEW'] += 1
        return ('VIEW(%s, ' % self.sp.typename(self.port_vt(vt)), path, ', %d)' % off)

    def port_vt(self, vt):
        return vt

    def compatible(self, mt, vt):
        if isinstance(mt, Kind):
            v = self.mg.view_of_type(strip_arr(vt)) if isinstance(strip_arr(vt), Struct) else None
            return v is not None and v.kind is mt
        msz = mt.size()
        if msz != vt.size():
            return False
        if isinstance(mt, Ptr) or isinstance(vt, Ptr):
            return isinstance(mt, Ptr) and isinstance(vt, Ptr) or \
                (isinstance(mt, Win) and mt.name in ('LPSTR', 'LPCSTR', 'FARPROC', 'DLGPROC')) or \
                (isinstance(vt, Win) and vt.name in ('LPSTR', 'LPCSTR', 'FARPROC', 'DLGPROC'))
        if isinstance(mt, Struct) or isinstance(vt, Struct):
            if isinstance(mt, Struct) and isinstance(vt, Struct):
                a = self.mg.view_of_type(mt)
                b = self.mg.view_of_type(vt)
                return a is not None and b is not None and a.kind is b.kind
            return False
        if isinstance(mt, Win) and mt.name in Win.FIELDS or isinstance(vt, Win) and vt.name in Win.FIELDS:
            return isinstance(mt, Win) and isinstance(vt, Win) and mt.name == vt.name
        if isinstance(mt, Arr) or isinstance(vt, Arr):
            return isinstance(mt, Arr) and isinstance(vt, Arr) and \
                self.compatible(strip_arr(mt), strip_arr(vt)) if strip_arr(mt).size() == strip_arr(vt).size() \
                else False
        return True

    def ds_path(self, addr, size, vt):
        g, off = self.mg.global_at(addr)
        if g is None:
            return None
        r = self.sub_path(g.type, off, size, vt, '')
        if r is None:
            return None
        return (r[0], g.name + r[1], r[2])

    # -- the walk ---------------------------------------------------------------
    def run(self):
        self.file_scope()
        for fd in self.m.funcdefs:
            if fd.coord.file != self.m.fn:
                continue
            if self.is_dropped_stub(fd):
                continue
            scope = pm.Scope(self.m.scope)
            scope.externs = set()
            ft = self.m.funcs[fd.decl.name][0]
            for pn, pt in ft.params:
                if pn:
                    scope.vars[pn] = pt
            self.visit(fd.body, scope, None)
        self.tokens_pass()
        return self.ed.render()

    def is_dropped_stub(self, fd):
        name = fd.decl.name
        f = self.mg.functions.get(name)
        tags = pm.addr_tags(self.src)
        return fd.decl.coord.line not in tags and f is not None and \
            (f[1] != self.m.fn or f[2] is not None)

    def visit(self, node, scope, parent):
        if node is None:
            return
        if isinstance(node, c_ast.Compound):
            inner = pm.Scope(scope)
            inner.externs = set()
            for item in node.block_items or []:
                self.visit(item, inner, node)
            return
        if isinstance(node, c_ast.Decl):
            if node.name:
                t = self.m.tb.build(node.type, scope)
                scope.vars[node.name] = t
                if 'extern' in node.storage:
                    scope.externs.add(node.name)
                    self.remove_stmt(node)
                    return
            if node.init is not None:
                self.visit(node.init, scope, node)
            return
        if isinstance(node, (c_ast.Typedef,)):
            return
        handled = self.rewrite(node, scope, parent)
        if handled == 'skip':
            return
        for _, c in node.children():
            self.visit(c, scope, node)

    def is_global(self, name, scope):
        s = scope
        while s is not None:
            if name in s.vars:
                return s.parent is None or name in getattr(s, 'externs', ())
            s = s.parent
        return False

    def lvalue_ctx(self, node, parent):
        if isinstance(parent, c_ast.Assignment) and parent.lvalue is node:
            return True
        if isinstance(parent, c_ast.UnaryOp) and parent.op in ('&', '++', '--', 'p++', 'p--'):
            return True
        return False

    def rewrite(self, node, scope, parent):
        if isinstance(node, c_ast.UnaryOp) and node.op == '*' and isinstance(node.expr, c_ast.Cast):
            r = self.rewrite_alias(node, node.expr, 0, scope)
            if r:
                return 'skip'
        if isinstance(node, c_ast.ArrayRef):
            inner = node.name
            if isinstance(inner, c_ast.Cast):
                k = self.m.tb.const_eval(node.subscript)
                if k is not None and self.rewrite_alias(node, inner, k, scope):
                    return 'skip'
            if isinstance(inner, c_ast.UnaryOp) and inner.op == '&' and isinstance(inner.expr, c_ast.ID):
                k = self.m.tb.const_eval(node.subscript)
                if k is not None and self.rewrite_addr_index(node, inner.expr, k, scope):
                    return 'skip'
            if isinstance(inner, c_ast.ID) and self.is_global(inner.name, scope):
                self.rewrite_table_index(node, inner, scope, parent)
        if isinstance(node, c_ast.StructRef):
            self.rewrite_field(node, scope)
        if isinstance(node, c_ast.ID) and self.is_global(node.name, scope):
            if not (isinstance(parent, c_ast.ArrayRef) and parent.name is node) and \
                    not (isinstance(parent, c_ast.StructRef) and parent.field is node) and \
                    not (isinstance(parent, c_ast.FuncCall) and parent.name is node and
                         isinstance(scope.lookup(node.name), Func)):
                self.rewrite_global_id(node, scope, parent)
        return None
