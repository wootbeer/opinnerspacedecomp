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
import port_int16  # noqa: E402
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
        self.active = set()

    def add(self, s, e, pieces, prio=0):
        if isinstance(pieces, str):
            pieces = [pieces]
        self.edits.append((s, e, pieces, prio))

    def render(self, s=0, e=None):
        if e is None:
            e = len(self.text)
        inner = [x for x in self.edits if s <= x[0] and x[1] <= e and (x[0], x[1]) != (s, e)]
        # keep outermost edits only
        inner.sort(key=lambda x: (x[0], x[1] != x[0], -(x[1] - x[0]), -x[3]))
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
        for x in top:
            a, b, pieces, prio = x
            out.append(self.text[pos:a])
            self.active.add(id(x))
            for p in pieces:
                if isinstance(p, tuple):
                    out.append(self.render_span(p[0], p[1]))
                else:
                    out.append(p)
            self.active.discard(id(x))
            pos = max(pos, b)
        out.append(self.text[pos:e])
        return ''.join(out)

    def render_span(self, s, e):
        # an edit covering exactly this span applies to it too
        exact = [x for x in self.edits if (x[0], x[1]) == (s, e) and s != e and
                 id(x) not in self.active]
        if exact:
            x = max(exact, key=lambda x: x[3])
            self.active.add(id(x))
            out = []
            for p in x[2]:
                out.append(self.render_span(p[0], p[1]) if isinstance(p, tuple) else p)
            self.active.discard(id(x))
            return ''.join(out)
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
        self.dropped = []
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
            return self.sign_view(t, vt, ('', path, ''))
        if isinstance(t, Kind):
            for f in t.fields:
                if f.off <= off and off + size <= f.off + max(f.size, 0):
                    return self.sub_path(f.type, off - f.off, size, vt, path + '.' + f.name)
                if f.off <= off < f.off + max(f.size, 1) and isinstance(f.type, Arr) and \
                        isinstance(vt, Arr):
                    # array view longer than the merged field: same start
                    return self.sub_path(f.type, off - f.off, f.size, vt, path + '.' + f.name)
            for f in t.fields:
                if f.off <= off < f.off + max(f.size, 1):
                    return self.view_cast(f.type, off - f.off, size, vt, path + '.' + f.name)
            return self.view_cast(t, off, size, vt, path)
        if isinstance(t, Struct):
            for name, ft, fo in t.fields:
                if fo <= off and off + size <= fo + ft.size():
                    return self.sub_path(ft, off - fo, size, vt, path + '.' + name)
            for name, ft, fo in t.fields:
                if fo <= off < fo + max(ft.size(), 1):
                    return self.view_cast(ft, off - fo, size, vt, path + '.' + name)
            return self.view_cast(t, off, size, vt, path)
        if isinstance(t, Win) and t.name in Win.FIELDS:
            for n, o, _ in Win.FIELDS[t.name]:
                if o == off and size == 2 and not isinstance(vt, (Ptr, Arr)):
                    return ('', path + '.' + n, '')
            return self.view_cast(t, off, size, vt, path)
        if isinstance(t, Arr):
            es = t.of.size() if not isinstance(t.of, Kind) else t.of.size
            if es and isinstance(vt, Arr) and isinstance(t.of, Arr) and not isinstance(vt.of, Arr) \
                    and off // es < (t.n or 1 << 30):
                # 1-D view of a 2-D array: index into the row it starts in
                return self.sub_path(t.of, off % es, min(size, es), vt, path + '[%d]' % (off // es))
            if es and isinstance(vt, Arr) and off % es == 0 and \
                    self.compatible(strip_arr(t), strip_arr(vt)):
                if off == 0:
                    return self.sign_view(t, vt, ('', path, ''))
                return self.sign_view(t, vt, ('(', path, ' + %d)' % (off // es)))
            if es and off // es < (t.n or 1 << 30) and off % es + size <= es:
                return self.sub_path(t.of, off % es, size, vt, path + '[%d]' % (off // es))
            return self.view_cast(t, off, size, vt, path)
        if tsz == 4 and size == 2 and off in (0, 2) and not isinstance(vt, (Ptr, Arr, Struct, Win)) \
                or (isinstance(vt, Win) and vt.name in pm.HANDLE_NAMES and tsz == 4 and size == 2):
            return ('LO16(' if off == 0 else 'HI16(', path, ')')
        if tsz == 2 and size == 1 and off in (0, 1) and isinstance(vt, Prim):
            return ('LO8(' if off == 0 else 'HI8(', path, ')')
        return self.view_cast(t, off, size, vt, path)

    @staticmethod
    def int_sign(t):
        """(bits, signed) of a 1994 integer type, else None."""
        if isinstance(t, Prim):
            return port_int16.PRIM_INT.get(t.name)
        if isinstance(t, Win) and t.name in pm.WIN_TYPES:
            return port_int16.PORT_INT.get(pm.WIN_TYPES[t.name][1])
        return None

    def sign_view(self, t, vt, res):
        """An integer view whose signedness differs from the merged type
        is marked for port_int16, which casts where the 1994 view type
        changes the result (and drops the marker elsewhere)."""
        a, b = self.int_sign(strip_arr(t)), self.int_sign(strip_arr(vt))
        if a is None or b is None or a == b or a[0] != b[0]:
            return res
        self.counts['signedness view'] += 1
        mark = port_int16.marker(b, isinstance(vt, Arr))
        return (mark + '(' + res[0], res[1], res[2] + ')')

    def view_cast(self, t, off, size, vt, path):
        self.counts['VIEW'] += 1
        if isinstance(vt, Arr):
            return ('VIEWP(%s, ' % self.sp.typename(Ptr(vt.of, True)), path, ', %d)' % off)
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
            if isinstance(mt, Struct) and isinstance(vt, Struct) and mt.name == vt.name and \
                    mt.name in pm.CRT_STRUCTS:
                return True
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
        if isinstance(node, c_ast.ArrayRef) and self.rewrite_shifted_view(node, scope, parent):
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
        if isinstance(node, (c_ast.UnaryOp, c_ast.StructRef)) and self.rewrite_win_ptr_deref(node, scope):
            return 'skip'
        if isinstance(node, c_ast.ArrayRef) and isinstance(node.name, c_ast.StructRef):
            self.rewrite_flat_index(node, scope)
        if isinstance(node, c_ast.StructRef):
            self.rewrite_field(node, scope)
        if isinstance(node, c_ast.FuncCall):
            self.rewrite_call(node, scope, parent)
        if isinstance(node, c_ast.Assignment) and node.op == '=':
            self.rewrite_getproc(node, scope)
            self.rewrite_fnptr_store(node, scope)
            self.rewrite_objref_word(node, scope)
        if isinstance(node, c_ast.ID) and self.is_global(node.name, scope):
            if not (isinstance(parent, c_ast.ArrayRef) and parent.name is node) and \
                    not (isinstance(parent, c_ast.StructRef) and parent.field is node) and \
                    not (isinstance(parent, c_ast.FuncCall) and parent.name is node and
                         isinstance(scope.lookup(node.name), Func)):
                self.rewrite_global_id(node, scope, parent)
        return None

    # -- calls: adapt the arguments to the callee's real signature -----------
    def callee_type(self, node, scope):
        """(name, Func, pascal) of a call's callee, from its definition."""
        n = node.name
        if isinstance(n, c_ast.ID) and n.name in self.mg.functions and \
                not self.shadowed(n.name, scope):
            return n.name, self.mg.functions[n.name][0], self.mg.is_pascal(n.name)
        vt = self.typeof(n, scope)
        if vt is None:
            return None
        t = vt.t
        name = None
        if isinstance(n, c_ast.ID) and self.is_global(n.name, scope):
            name = n.name
            addr = pm.global_addr(n.name)
            g, off = self.mg.global_at(addr) if addr is not None else (None, None)
            if g is not None and off == 0:
                t = g.type
        elif isinstance(n, c_ast.StructRef):
            mt = self.merged_field_type(n, scope)
            if mt is not None:
                t = mt
        if isinstance(t, Ptr) and isinstance(t.to, Func):
            pascal = getattr(t, 'pascal', False) or (name is not None and self.mg.is_pascal_ptr(name))
            return name, t.to, pascal
        return None

    def merged_field_type(self, X, scope):
        try:
            loc = self.location(X, scope, False)
        except ValueError:
            return None
        if loc is None or not isinstance(loc[1], Kind):
            return None
        for f in loc[1].fields:
            if f.off == loc[2]:
                return f.type
        return None

    def shadowed(self, name, scope):
        s = scope
        while s is not None and s.parent is not None:
            if name in s.vars and name not in getattr(s, 'externs', ()):
                return True
            s = s.parent
        return False

    @staticmethod
    def words(t):
        if t is None:
            return None
        sz = t.size if isinstance(t, Kind) else t.size()
        return max(1, (sz + 1) // 2)

    def two_fields(self, t):
        """Field names of a 4-byte record of two 16-bit fields, or None."""
        if isinstance(t, Win) and t.name in ('POINT', 'SIZE'):
            return [n for n, o, _ in Win.FIELDS[t.name]]
        k = t if isinstance(t, Kind) else (self.mg.view_of_type(t).kind
                                           if isinstance(t, Struct) and self.mg.view_of_type(t) else None)
        if k is None or k.size != 4:
            return None
        fs = [f for f in k.fields if f.size == 2]
        if len(fs) == 2 and fs[0].off == 0 and fs[1].off == 2:
            return [fs[0].name, fs[1].name]
        return None

    @staticmethod
    def signed16(v):
        return v - 0x10000 if v >= 0x8000 else v

    def arg_spans(self, node):
        """(open paren index, close paren index, [(start, end)] per argument)."""
        e = self.node_end(node.name)
        if e is None:
            return None
        i = self.tok_at(self.find_tok(e, '('))
        j = self.match_close(i)
        spans = []
        d = 0
        start = None
        for k in range(i + 1, j):
            t = self.toks[k]
            if t.kind in ('ws', 'nl', 'comment'):
                continue
            if t.kind == 'punct' and t.text in '([{':
                d += 1
            elif t.kind == 'punct' and t.text in ')]}':
                d -= 1
            elif d == 0 and t.text == ',':
                spans.append((start, last))
                start = None
                continue
            if start is None:
                start = t.pos
            last = t.pos + len(t.text)
        if start is not None:
            spans.append((start, last))
        return i, j, spans

    def is_plain(self, node):
        """No side effects: safe to name twice."""
        for n in walk(node):
            if isinstance(n, (c_ast.FuncCall, c_ast.Assignment)) or \
                    isinstance(n, c_ast.UnaryOp) and n.op in ('++', '--', 'p++', 'p--'):
                return False
        return True

    def objref_parts(self, a):
        """(idx node, type node or constant) of '(char)i | t << 8' style packing."""
        k = self.m.tb.const_eval(a)
        if k is not None:
            return None
        if isinstance(a, c_ast.Cast):
            return a.expr, 0
        if isinstance(a, c_ast.BinaryOp) and a.op == '|' and isinstance(a.left, c_ast.Cast):
            r = a.right
            k = self.m.tb.const_eval(r)
            if k is not None and k & 0xff == 0:
                return a.left.expr, k >> 8
            if isinstance(r, c_ast.BinaryOp) and r.op == '<<' and self.m.tb.const_eval(r.right) == 8:
                return a.left.expr, r.left
        return None

    def rewrite_call(self, node, scope, parent=None):
        ct = self.callee_type(node, scope)
        if ct is None:
            return
        name, ft, pascal = ct
        args = node.args.exprs if node.args else []
        sp = self.arg_spans(node)
        if sp is None:
            return
        oi, ci, spans = sp
        if len(spans) != len(args):
            return
        line = node.coord.line if node.coord else 0
        ov = pm.OV.calls.get((self.m.fn, line, name))
        if ov is not None:
            self.ed.add(self.toks[oi].pos, self.toks[ci].pos + 1, '(' + ov + ')')
            self.counts['call override'] += 1
            return
        if ft.var:
            return
        params = [t for _, t in ft.params]
        ats = [self.typeof(a, scope) for a in args]
        out = []
        changed = []
        i = j = 0
        while i < len(params) and j < len(args):
            p = params[i]
            pw = self.words(p)
            at = ats[j].t if ats[j] is not None else None
            aw = self.words(at) if at is not None else pw
            pf = self.two_fields(p)
            af = self.two_fields(at) if at is not None else None
            nxt = j + 1 < len(args) and (ats[j + 1] is None or self.words(ats[j + 1].t) == 1)
            if pf and not af and pw == aw == 2:
                a = args[j]
                if isinstance(a, c_ast.UnaryOp) and a.op == '*' and isinstance(a.expr, c_ast.Cast) \
                        and isinstance(a.expr.expr, c_ast.UnaryOp) and a.expr.expr.op == '&':
                    xt = self.typeof(a.expr.expr.expr, scope)
                    if xt is not None and self.two_fields(xt.t) == pf:
                        out.append([self.span(a.expr.expr.expr)])
                        changed.append('aliased record passed as itself')
                        i += 1
                        j += 1
                        continue
                if isinstance(a, c_ast.FuncCall) and isinstance(a.name, c_ast.ID) and \
                        a.name.name == 'MAKELONG' and len(a.args.exprs) == 2:
                    sub = self.arg_spans(a)[2]
                    out.append(['(%s){' % self.sp.typename(p), sub[0], ', ', sub[1], '}'])
                    changed.append('MAKELONG -> %s' % self.sp.typename(p))
                    i += 1
                    j += 1
                    continue
            if pw == aw and not (pf and at is not None and not af and isinstance(at, Prim)) and \
                    not (pw == 1 and isinstance(p, Struct) and isinstance(at, Prim)):
                out.append([spans[j]])
                i += 1
                j += 1
                continue
            more_args = len(args) - j > len(params) - i
            fewer_args = len(args) - j < len(params) - i
            if pw == 2 and aw == 1 and nxt and more_args:
                lo, hi = (spans[j + 1], spans[j]) if pascal else (spans[j], spans[j + 1])
                if pf:
                    out.append(['(%s){' % self.sp.typename(p), lo, ', ', hi, '}'])
                    changed.append('two values -> %s' % self.sp.typename(p))
                else:
                    kl = self.m.tb.const_eval(args[j + 1] if pascal else args[j])
                    kh = self.m.tb.const_eval(args[j] if pascal else args[j + 1])
                    if kl is not None and kh is not None and 0 <= kl < 0x10000 and 0 <= kh < 0x8000:
                        out.append(['%dL' % kl if kh == 0 else
                                    '0x%xL' % (((kh & 0xffff) << 16) | (kl & 0xffff))])
                    else:
                        out.append(['MAKELONG(', lo, ', ', hi, ')'])
                    changed.append('two words -> long')
                i += 1
                j += 2
                continue
            if pw == 1 and aw == 2 and af and i + 1 < len(params) and fewer_args and \
                    self.words(params[i + 1]) == 1 and self.is_plain(args[j]):
                f0, f1 = (af[1], af[0]) if pascal else (af[0], af[1])
                out.append([spans[j], '.' + f0, ', ', spans[j], '.' + f1])
                changed.append('record -> two values')
                i += 2
                j += 1
                continue
            if pw == 1 and aw == 2 and not af and fewer_args and i + 1 < len(params) and \
                    self.words(params[i + 1]) == 1 and isinstance(at, (Prim, Win)) and \
                    not isinstance(at, Ptr):
                k = self.m.tb.const_eval(args[j])
                if k is not None:
                    lo, hi = str(self.signed16(k & 0xffff)), str(self.signed16((k >> 16) & 0xffff))
                    parts = [lo, ', ', hi]
                elif self.is_plain(args[j]) and isinstance(args[j], (c_ast.ID, c_ast.StructRef,
                                                                       c_ast.ArrayRef)):
                    parts = ['LO16(', spans[j], '), HI16(', spans[j], ')']
                else:
                    parts = None
                if parts is not None:
                    if pascal:
                        parts = [hi, ', ', lo] if k is not None else \
                            ['HI16(', spans[j], '), LO16(', spans[j], ')']
                    out.append(parts)
                    changed.append('long -> two words')
                    i += 2
                    j += 1
                    continue
            if pw == 1 and isinstance(p, Struct) and isinstance(at, Prim):
                parts = self.objref_parts(args[j])
                k = self.mg.view_of_type(p)
                if parts is not None and k is not None:
                    idx, typ = parts
                    ti = typ if isinstance(typ, int) else None
                    out.append(['(%s){' % k.kind.name, self.span(idx), ', ',
                                str(ti) if ti is not None else self.span(typ), '}'])
                    changed.append('packed word -> %s' % k.kind.name)
                    i += 1
                    j += 1
                    continue
            # leave as is
            out.append([spans[j]])
            i += 1
            j += 1
        effects = []
        if j < len(args):
            changed.append('dropped %d extra argument(s): %s' % (
                len(args) - j, ', '.join(self.src[a:b] for a, b in spans[j:])))
            # keep side effects of dropped arguments (evaluated first: right to left)
            effects = [spans[k] for k in range(len(args) - 1, j - 1, -1) if not self.is_plain(args[k])]
        if i < len(params):
            self.note(node, 'call to %s passes %d argument(s) for %d parameters' % (
                name or 'pointer', len(args), len(params)))
            self.counts['call too few'] += 1
            return
        if not changed:
            return
        pieces = ['(']
        for k, a in enumerate(out):
            if k:
                pieces.append(', ')
            pieces.extend(a)
        pieces.append(')')
        self.ed.add(self.toks[oi].pos, self.toks[ci].pos + 1, pieces)
        if effects:
            cs = self.node_start(node)
            if isinstance(parent, c_ast.Compound):
                ls = self.src.rfind('\n', 0, cs) + 1
                indent = self.src[ls:cs] if not self.src[ls:cs].strip() else ''
                pre = []
                for sp_ in effects:
                    pre += [sp_, ';\n' + indent]
                self.ed.add(cs, cs, pre)
            else:
                pre = ['(']
                for sp_ in effects:
                    pre += [sp_, ', ']
                self.ed.add(cs, cs, pre)
                self.ed.add(self.toks[ci].pos + 1, self.toks[ci].pos + 1, ')')
        for c in changed:
            self.note(node, 'call to %s: %s' % (name or 'pointer', c))
            self.counts['call adapted'] += 1
            if c.startswith('dropped'):
                self.dropped.append('%s:%d %s: %s' % (self.m.fn, line, name or self.src[
                    self.pos(node) or 0:self.toks[oi].pos].strip(), c))

    def rewrite_flat_index(self, node, scope):
        """f[j] through a 1-D view of a field merged as a 2-D array."""
        vt = self.typeof(node.name, scope)
        if vt is None or not isinstance(vt.t, Arr) or isinstance(vt.t.of, Arr):
            return
        mt = self.merged_field_type(node.name, scope)
        if not isinstance(mt, Arr) or not isinstance(mt.of, Arr) or isinstance(mt.of.of, Arr):
            return
        m = mt.of.n
        if not m or mt.of.of.size() != vt.t.of.size():
            return
        if not self.is_plain(node.subscript):
            return
        e = self.node_end(node.name)
        bi = self.tok_at(self.find_tok(e, '['))
        be = self.match_close(bi)
        k = self.m.tb.const_eval(node.subscript)
        if k is not None:
            self.ed.add(self.toks[bi].pos, self.toks[be].pos + 1, '[%d][%d]' % (k // m, k % m))
        else:
            sp = self.span(node.subscript)
            self.ed.add(self.toks[bi].pos, self.toks[be].pos + 1,
                        ['[', sp, ' / %d][' % m, sp, ' %% %d]' % m])
        self.counts['flat index'] += 1

    def rewrite_shifted_view(self, node, scope, parent):
        """v[a][b] where v is an array view a few elements below a global of the
        same shape (the 1994 compiler folded a constant index into the base)."""
        if isinstance(parent, c_ast.ArrayRef) and parent.name is node:
            return False
        subs = []
        base = node
        while isinstance(base, c_ast.ArrayRef):
            subs.insert(0, base.subscript)
            base = base.name
        if not isinstance(base, c_ast.ID) or not self.is_global(base.name, scope):
            return False
        addr = pm.global_addr(base.name)
        vt = scope.lookup(base.name)
        if addr is None or addr in self.mg.globals or not isinstance(vt, Arr):
            return False
        dims = []
        t = vt
        while isinstance(t, Arr):
            dims.append(t.n)
            t = t.of
        if len(subs) != len(dims) or not isinstance(t, Prim):
            return False
        es = t.size()
        nxt = [a for a in self.mg.globals if addr < a <= addr + 8]
        if not nxt:
            return False
        g = self.mg.globals[min(nxt)]
        gd, gt = [], g.type
        while isinstance(gt, Arr):
            gd.append(gt.n)
            gt = gt.of
        if gd[1:] != dims[1:] or not isinstance(gt, Prim) or gt.size() != es:
            return False
        k = (g.addr - addr) // es
        if (g.addr - addr) % es or k >= (dims[-1] or 1 << 30):
            return False
        pieces = [g.name]
        for i, sub in enumerate(subs):
            pieces += ['[', self.span(sub), ' - %d]' % k if i == len(subs) - 1 else ']']
            self.visit(sub, scope, node)
        s = self.pos(base)
        e = self.node_end(node)
        self.ed.add(s, e, pieces, prio=1)
        self.note(node, 'view %s read as %s with the last index shifted by %d' % (base.name, g.name, -k))
        return True

    def rewrite_objref_word(self, node, scope):
        """ref = f() where f returns the OBJREF packed in a word."""
        r = node.rvalue
        if not isinstance(r, c_ast.FuncCall):
            return
        lt = self.typeof(node.lvalue, scope)
        rt = self.typeof(r, scope)
        ct = self.callee_type(r, scope)
        if lt is None or ct is None or not isinstance(lt.t, Struct):
            return
        v = self.mg.view_of_type(lt.t)
        if v is None or v.kind.name != 'OBJREF' or not isinstance(ct[1].ret, Prim):
            return
        s = self.node_start(r)
        e = self.node_end(r)
        if s is None or e is None:
            return
        self.ed.add(s, e, ['objref_of(', (s, e), ')'], prio=1)
        self.counts['objref from word'] += 1

    def fn_sig(self, f):
        """Spelling of a function type without parameter names."""
        return self.sp.typename(Ptr(Func(f.ret, [(None, t) for _, t in f.params], f.var), True))

    def rewrite_fnptr_store(self, node, scope):
        """p = (cast)fn: drop the cast when fn has the pointer's real type."""
        r = node.rvalue
        cast = None
        if isinstance(r, c_ast.Cast):
            cast, r = r, r.expr
        if cast is None or not isinstance(r, c_ast.ID) or r.name not in self.mg.functions:
            return
        lt = None
        if isinstance(node.lvalue, c_ast.StructRef):
            lt = self.merged_field_type(node.lvalue, scope)
        elif isinstance(node.lvalue, c_ast.ID) and self.is_global(node.lvalue.name, scope):
            addr = pm.global_addr(node.lvalue.name)
            g, off = self.mg.global_at(addr) if addr is not None else (None, None)
            lt = g.type if g is not None and off == 0 else None
        if not (isinstance(lt, Ptr) and isinstance(lt.to, Func)):
            return
        ft = self.mg.functions[r.name][0]
        if self.fn_sig(ft) != self.fn_sig(lt.to):
            return
        ci = self.tok_at(self.pos(cast))
        if self.toks[ci].text != '(':
            ci = self.prev_sig(ci)
        ce = self.match_close(ci)
        if ce is None:
            return
        self.ed.add(self.toks[ci].pos, self.pos(r), '')
        self.counts['function cast dropped'] += 1

    def rewrite_getproc(self, node, scope):
        """g = GetProcAddress(...): cast to the global's function pointer type."""
        r = node.rvalue
        cast = None
        if isinstance(r, c_ast.Cast):
            cast, r = r, r.expr
        if not (isinstance(r, c_ast.FuncCall) and isinstance(r.name, c_ast.ID) and
                r.name.name == 'GetProcAddress'):
            return
        lv = node.lvalue
        if not (isinstance(lv, c_ast.ID) and self.is_global(lv.name, scope)):
            return
        addr = pm.global_addr(lv.name)
        g, off = self.mg.global_at(addr) if addr is not None else (None, None)
        if g is None or off or not isinstance(g.type, Ptr) or not isinstance(g.type.to, Func):
            return
        tn = '(%s)' % self.sp.typename(g.type)
        s = self.pos(r.name)
        if cast is not None:
            ci = self.tok_at(self.pos(cast))
            if self.toks[ci].text != '(':
                ci = self.prev_sig(ci)
            ce = self.match_close(ci) if self.toks[ci].text == '(' else None
            if ce is None:
                return
            self.ed.add(self.toks[ci].pos, self.toks[ce].pos + 1, tn)
        else:
            self.ed.add(s, s, tn)

    # -- rewrites -------------------------------------------------------------
    def view_for_decl(self, name):
        return self.mg.decl_view.get((self.m.fn, name)) or self.mg.decl_view.get(('inspace.h', name))

    def table_name(self, kind):
        return self.mg.globals[kind.base].name

    def note(self, node, msg):
        line = node.coord.line if node is not None and node.coord else 0
        self.notes.append('%s:%d: %s' % (self.m.fn, line, msg))

    def rewrite_global_id(self, node, scope, parent):
        name = node.name
        addr = pm.global_addr(name)
        if addr is None:
            return
        p = self.pos(node)
        if p is None:
            return
        v = self.view_for_decl(name)
        if v is not None and v.kind.key[0] == 'table':
            S = v.kind.size
            q, r = divmod(v.delta, S)
            tn = self.table_name(v.kind)
            if r:
                self.note(node, '%s used as a pointer into the middle of %s records' % (name, tn))
                self.ed.add(p, p + len(name), '/* TODO: %s+%d */ (&%s[%d])' % (name, r, tn, q))
            elif q:
                self.ed.add(p, p + len(name), '(&%s[%d])' % (tn, q))
            elif tn != name:
                self.ed.add(p, p + len(name), tn)
            return
        vt = scope.lookup(name)
        if vt is None or isinstance(vt, Func):
            return
        if isinstance(parent, c_ast.Assignment) and parent.lvalue is node:
            # whole-object store of a value of the merged type: no view needed
            g, off = self.mg.global_at(addr)
            rt = self.typeof(parent.rvalue, scope)
            if g is not None and off == 0 and rt is not None and \
                    g.type.size() == vt.size() and self.compatible(g.type, rt.t) and \
                    not self.compatible(g.type, vt):
                if g.name != name:
                    self.ed.add(p, p + len(name), g.name)
                return
        res = self.ds_path(addr, vt.size(), vt)
        if res is None:
            self.note(node, 'no merged global for %s' % name)
            return
        pre, path, post = res
        if (pre, path, post) == ('', name, ''):
            return
        self.ed.add(p, p + len(name), pre + path + post)

    def rewrite_table_index(self, node, inner, scope, parent):
        v = self.view_for_decl(inner.name)
        if v is None or v.kind.key[0] != 'table':
            self.rewrite_global_id(inner, scope, None)
            return
        p = self.pos(inner)
        if p is None:
            return
        k = v.kind
        S = k.size
        tn = self.table_name(k)
        q, r = divmod(v.delta, S)
        q += self.extra_q.get(id(node), 0)
        if k.inner and v.delta:
            if len(k.inner) != 1 or isinstance(parent, c_ast.ArrayRef) and parent.name is node:
                self.note(node, 'view %s of a 2-D table at +%x' % (inner.name, v.delta))
                return
            self.rewrite_flat_table_index(node, inner, tn, k.inner[0], q, p)
            return
        if tn != inner.name:
            self.ed.add(p, p + len(inner.name), tn)
        i = self.tok_at(self.find_tok(p + len(inner.name), '['))
        j = self.match_close(i)
        close = self.toks[j].pos
        if q:
            self.ed.add(close, close, ' + %d' % q if q > 0 else ' - %d' % -q)
        if getattr(v.t, 'row', False):
            res = self.sub_path(k, r, v.t.size(), v.t.fields[0][1], '')
            if res:
                pre, path, post = res
                if pre:
                    self.ed.add(p, p, pre)
                self.ed.add(close + 1, close + 1, path + post)

    def rewrite_flat_table_index(self, node, inner, tn, n, q, p):
        """v[k] where v is a 1-D view into a table of rows of n records."""
        i = self.tok_at(self.find_tok(p + len(inner.name), '['))
        j = self.match_close(i)
        sub = node.subscript
        a = b = None
        if q == 0 and isinstance(sub, c_ast.BinaryOp) and sub.op == '+' and \
                isinstance(sub.left, c_ast.BinaryOp) and sub.left.op == '*' and \
                self.m.tb.const_eval(sub.left.right) == n:
            a, b = self.span(sub.left.left), self.span(sub.right)
            pieces = [tn, '[', a, '][', b, ']']
        elif self.is_plain(sub):
            sp = self.span(sub)
            k = self.m.tb.const_eval(sub)
            if k is not None:
                pieces = [tn, '[%d][%d]' % ((k + q) // n, (k + q) % n)]
            else:
                qs = ' + %d' % q if q else ''
                pieces = [tn, '[(', sp, qs + ') / %d][(' % n, sp, qs + ') %% %d]' % n]
        else:
            self.note(node, 'view %s of a 2-D table: index has side effects' % inner.name)
            return
        self.ed.add(p, self.toks[j].pos + 1, pieces)

    def rewrite_field(self, node, scope):
        bt = self.typeof(node.name, scope)
        if bt is None:
            return
        st = bt.t
        if node.type == '->':
            st = st.to if isinstance(st, Ptr) else (st.of if isinstance(st, Arr) else None)
        if isinstance(st, Win) and st.name in Win.FIELDS and node.type == '->' and \
                isinstance(node.name, c_ast.ID) and self.is_global(node.name.name, scope):
            self.rewrite_win_ptr_field(node, st)
            return
        if not isinstance(st, Struct) or st.name in pm.CRT_STRUCTS:
            return
        v = bt.view if (bt.view is not None and bt.view.t is st) else self.mg.view_of_type(st)
        if v is None:
            return
        f = st.field(node.field.name)
        if f is None:
            self.note(node, 'unknown field %s' % node.field.name)
            return
        if node.type == '.' and self.rewrite_field_on_global(node, f, scope):
            return
        fname, ft, off = f
        K = v.kind
        S = K.size or 1
        a = off + v.delta % S
        extra, a = divmod(a, S)
        if extra:
            if isinstance(node.name, c_ast.ArrayRef) and node.type == '.':
                self.extra_q[id(node.name)] = self.extra_q.get(id(node.name), 0) + extra
            else:
                self.note(node, 'field %s lies in the next record' % fname)
        res = self.sub_path(K, a, ft.size(), ft, '')
        if res is None:
            return
        pre, path, post = res
        fp = self.pos(node.field)
        if fp is None:
            return
        if path[1:] != fname:
            self.ed.add(fp, fp + len(fname), path[1:])
        if pre or post:
            s = self.node_start(node)
            if s is None:
                return
            # include opening parens of a cast or grouping inside the access
            i = self.tok_at(s)
            while i is not None:
                j = self.prev_sig(i)
                if j is None or j < 0 or self.toks[j].text != '(' or \
                        self.toks[self.match_close(j)].pos > fp:
                    break
                i = j
            if i is not None:
                s = self.toks[i].pos
            self.ed.add(s, s, pre)
            self.ed.add(fp + len(fname), fp + len(fname), post)

    def rewrite_win_ptr_field(self, node, st):
        """p->x where p is a global POINT/RECT pointer whose merged type
        points to a record (e.g. a POINT view of a REC_70 slot)."""
        addr = pm.global_addr(node.name.name)
        if addr is None:
            return
        g, off = self.mg.global_at(addr)
        if g is None:
            return
        mt = g.type
        while isinstance(mt, Arr):
            es = mt.of.size if isinstance(mt.of, Kind) else mt.of.size()
            off %= es
            mt = mt.of
        if off or not isinstance(mt, Ptr) or not isinstance(mt.to, Struct):
            return
        v = self.mg.view_of_type(mt.to)
        if v is None:
            return
        fo = [o for n, o, _ in Win.FIELDS[st.name] if n == node.field.name]
        if not fo:
            return
        res = self.sub_path(v.kind, fo[0], 2, Prim('int'), '')
        if res is None or res[0]:
            return
        fp = self.pos(node.field)
        self.ed.add(fp, fp + len(node.field.name), res[1][1:])

    def win_ptr_kind(self, name):
        """Merged record kind behind a global POINT/RECT pointer, or None."""
        addr = pm.global_addr(name)
        if addr is None:
            return None
        g, off = self.mg.global_at(addr)
        if g is None:
            return None
        mt = g.type
        while isinstance(mt, Arr):
            es = mt.of.size if isinstance(mt.of, Kind) else mt.of.size()
            off %= es
            mt = mt.of
        if off or not isinstance(mt, Ptr) or not isinstance(mt.to, Struct):
            return None
        v = self.mg.view_of_type(mt.to)
        return v.kind if v is not None else None

    def rewrite_win_ptr_deref(self, node, scope):
        """*p and p[k].x where p is a global POINT pointer onto a record."""
        if isinstance(node, c_ast.UnaryOp) and node.op == '*':
            ident, k, field = node.expr, 0, None
        elif isinstance(node, c_ast.StructRef) and node.type == '.' and \
                isinstance(node.name, c_ast.ArrayRef):
            ident, k, field = node.name.name, self.m.tb.const_eval(node.name.subscript), node.field.name
        else:
            return False
        if not isinstance(ident, c_ast.ID) or k is None or not self.is_global(ident.name, scope):
            return False
        vt = scope.lookup(ident.name)
        if not (isinstance(vt, Ptr) and isinstance(vt.to, Win) and vt.to.name in Win.FIELDS):
            return False
        kind = self.win_ptr_kind(ident.name)
        if kind is None:
            return False
        w = vt.to
        off = k * w.size()
        size, at = w.size(), w
        if field is not None:
            fo = [o for n, o, _ in Win.FIELDS[w.name] if n == field]
            if not fo:
                return False
            off += fo[0]
            size, at = 2, Prim('int')
        res = self.sub_path(kind, off, size, at, '')
        base = self.ds_path(pm.global_addr(ident.name), vt.size(), vt)
        if res is None or base is None or res[0] or base[0]:
            return False
        s = self.node_start(node)
        e = self.node_end(node)
        if s is None or e is None:
            return False
        if field is None:
            si = self.prev_sig(self.tok_at(s))
            if self.toks[si].text != '*':
                return False
            s = self.toks[si].pos
        self.ed.add(s, e, base[1] + '->' + res[1][1:], prio=1)
        return True

    def rewrite_field_on_global(self, node, f, scope):
        """g[i][j].f where g is a plain global array whose merged element type
        is not this struct (e.g. a PAIR view of a POINT array)."""
        base = node.name
        depth = 0
        while isinstance(base, c_ast.ArrayRef):
            base = base.name
            depth += 1
        if not isinstance(base, c_ast.ID) or not self.is_global(base.name, scope):
            return False
        if self.view_for_decl(base.name) is not None:
            return False
        addr = pm.global_addr(base.name)
        if addr is None:
            return False
        g, off = self.mg.global_at(addr)
        if g is None or off:
            return False
        mt = g.type
        for _ in range(depth):
            if not isinstance(mt, Arr):
                return False
            mt = mt.of
        if isinstance(mt, Kind):
            return False
        fname, ft, foff = f
        res = self.sub_path(mt, foff, ft.size(), ft, '')
        if res is None:
            return True
        pre, path, post = res
        fp = self.pos(node.field)
        if fp is None:
            return True
        if path[1:] != fname:
            self.ed.add(fp, fp + len(fname), path[1:])
        if pre or post:
            st = self.node_start(node)
            self.ed.add(st, st, pre)
            self.ed.add(fp + len(fname), fp + len(fname), post)
        return True

    def location(self, X, scope, visit=True):
        """(container pieces, merged type, byte offset) of an lvalue, or None."""
        if isinstance(X, c_ast.ID) and self.is_global(X.name, scope):
            addr = pm.global_addr(X.name)
            if addr is None:
                return None
            v = self.view_for_decl(X.name)
            g, off = self.mg.global_at(addr)
            if g is None:
                return None
            return ([g.name], g.type, off)
        if isinstance(X, c_ast.ArrayRef) and isinstance(X.name, c_ast.ID) and \
                self.is_global(X.name.name, scope):
            v = self.view_for_decl(X.name.name)
            if v is not None and v.kind.key[0] == 'table' and not v.kind.inner:
                S = v.kind.size
                q, r = divmod(v.delta, S)
                if visit:
                    self.visit(X.subscript, scope, X)
                return ([self.table_name(v.kind) + '[', self.span(X.subscript),
                         (' + %d]' % q) if q else ']'], v.kind, r)
            addr = pm.global_addr(X.name.name)
            k = self.m.tb.const_eval(X.subscript)
            vt = scope.lookup(X.name.name)
            if addr is not None and k is not None and isinstance(vt, Arr):
                g, off = self.mg.global_at(addr + k * vt.of.size())
                if g is not None:
                    return ([g.name], g.type, off)
            return None
        if isinstance(X, c_ast.StructRef):
            bt = self.typeof(X.name, scope)
            if bt is None:
                return None
            st = bt.t
            if X.type == '->':
                st = st.to if isinstance(st, Ptr) else None
            if not isinstance(st, Struct):
                if isinstance(st, Win) and st.name in Win.FIELDS:
                    inner = self.location(X.name, scope, visit) if X.type == '.' else None
                    if inner is None:
                        return None
                    for n, o, _ in Win.FIELDS[st.name]:
                        if n == X.field.name:
                            return (inner[0], inner[1], inner[2] + o)
                return None
            v = bt.view if (bt.view is not None and bt.view.t is st) else self.mg.view_of_type(st)
            f = st.field(X.field.name)
            if v is None or f is None:
                return None
            S = v.kind.size or 1
            if X.type == '.':
                inner = self.location(X.name, scope, visit)
                if inner is not None and inner[1] is v.kind:
                    return (inner[0], v.kind, inner[2] + f[2])
                if inner is None:
                    if visit:
                        self.visit(X.name, scope, X)
                    return ([self.span(X.name)], v.kind, f[2] + v.delta % S)
                return None
            if visit:
                self.visit(X.name, scope, X)
            return (['(*', self.span(X.name), ')'], v.kind, f[2] + v.delta % S)
        return None

    def span(self, node):
        s = self.node_start(node)
        e = self.node_end(node)
        if s is None or e is None:
            raise ValueError('no span')
        # include parentheses that open before s and close at e
        return (s, e)

    def rewrite_alias(self, node, cast, k, scope):
        try:
            tt = self.m.tb.build(cast.to_type, scope)
        except Exception:
            return False
        if not isinstance(tt, Ptr) or not isinstance(cast.expr, c_ast.UnaryOp) or cast.expr.op != '&':
            return False
        T = tt.to
        X = cast.expr.expr
        try:
            loc = self.location(X, scope)
        except ValueError:
            loc = None
        if loc is None:
            self.counts['alias kept'] += 1
            return False
        pieces, mt, off = loc
        off += k * T.size()
        res = self.sub_path(mt, off, T.size(), T, '')
        if res is None:
            return False
        pre, path, post = res
        cp = self.pos(cast)
        if cp is None:
            return False
        ci = self.tok_at(cp)
        if isinstance(node, c_ast.UnaryOp):
            si = self.prev_sig(ci)
            s = self.toks[si].pos
            e = self.node_end(X)
        else:
            si = self.prev_sig(ci)
            if self.toks[si].text != '(':
                return False
            close = self.match_close(si)
            bi = self.next_sig(close)
            if self.toks[bi].text != '[':
                return False
            s = self.toks[si].pos
            e = self.toks[self.match_close(bi)].pos + 1
        if e is None:
            return False
        self.ed.add(s, e, [pre] + pieces + [path, post], prio=1)
        self.counts['alias resolved'] += 1
        return True

    def rewrite_addr_index(self, node, ident, k, scope):
        addr = pm.global_addr(ident.name)
        vt = scope.lookup(ident.name)
        if addr is None or vt is None or not self.is_global(ident.name, scope):
            return False
        res = self.ds_path(addr + k * vt.size(), vt.size(), vt)
        if res is None:
            return False
        p = self.pos(ident)
        ai = self.prev_sig(self.tok_at(p))          # '&'
        oi = self.prev_sig(ai)                        # '('
        if self.toks[oi].text != '(':
            return False
        bi = self.next_sig(self.match_close(oi))
        e = self.toks[self.match_close(bi)].pos + 1
        self.ed.add(self.toks[oi].pos, e, ''.join(res), prio=1)
        return True

    # -- statements and file scope -------------------------------------------
    def stmt_bounds(self, i):
        """Token range [a, b] of the declaration statement around token i."""
        a = i
        depth = 0
        while a > 0:
            t = self.toks[a - 1]
            if t.kind == 'punct' and t.text in ')]':
                depth += 1
            elif t.kind == 'punct' and t.text in '([':
                if depth == 0:
                    break
                depth -= 1
            elif depth == 0 and t.kind == 'punct' and t.text in ';{}':
                break
            a -= 1
        while self.toks[a].kind in ('ws', 'nl', 'comment'):
            a += 1
        b = i
        depth = 0
        while b < len(self.toks):
            t = self.toks[b]
            if t.kind == 'punct' and t.text in '([{':
                depth += 1
            elif t.kind == 'punct' and t.text in ')]}':
                depth -= 1
            elif depth == 0 and t.text == ';':
                break
            b += 1
        return a, b

    def delete_lines(self, a, b, with_comments=True):
        """Delete tokens a..b plus their line (if nothing else is on it)."""
        s = self.toks[a].pos
        e = self.toks[b].pos + len(self.toks[b].text)
        ls = self.src.rfind('\n', 0, s) + 1
        if self.src[ls:s].strip() == '':
            s = ls
        le = self.src.find('\n', e)
        le = len(self.src) if le < 0 else le
        rest = self.src[e:le]
        if re.match(r'^\s*(/\*.*\*/)?\s*$', rest):
            e = le + 1
        if with_comments and s == ls:
            # comment lines directly above
            while True:
                pe = s - 1
                if pe <= 0:
                    break
                ps = self.src.rfind('\n', 0, pe) + 1
                line = self.src[ps:pe]
                if re.match(r'^\s*(/\*.*\*/|//.*)\s*$', line) and '@addr' not in line:
                    s = ps
                    continue
                if line.strip().endswith('*/') and '/*' not in line:
                    st = self.src.rfind('/*', 0, pe)
                    sl = self.src.rfind('\n', 0, st) + 1
                    if self.src[sl:st].strip() == '':
                        s = sl
                        continue
                break
        self.ed.add(s, e, '', prio=2)

    def remove_stmt(self, node):
        p = self.pos(node)
        if p is None:
            return
        i = self.tok_at(p)
        if i is None:
            return
        a, b = self.stmt_bounds(i)
        self.delete_lines(a, b, with_comments=False)

    def file_scope(self):
        toks = self.toks
        pp = pm.preproc_lines(self.src)
        in_pp = set()
        for s, e in pp:
            line = self.src[s:e]
            if re.match(r'\s*#\s*include\s*"inspace.h"', line):
                self.ed.add(s, e, '#include "game.h"')
            elif re.match(r'\s*#\s*(include|pragma)', line):
                le = e + 1 if e < len(self.src) else e
                self.ed.add(s, le, '', prio=2)
        for i, t in enumerate(toks):
            if t.kind == 'comment' and '@cflags' in t.text:
                ls = self.src.rfind('\n', 0, t.pos) + 1
                le = self.src.find('\n', t.pos)
                self.ed.add(ls, le + 1, '', prio=2)
            elif t.kind == 'comment' and '@addr' in t.text:
                m = re.search(r'@addr\s+(\S+)', t.text)
                self.ed.add(t.pos, t.pos + len(t.text), '/* %s */' % m.group(1))
        # top-level statements
        depth = 0
        start = None
        stmts = []
        pp_spans = [(s, e) for s, e in pp]
        ppi = 0
        for i, t in enumerate(toks):
            while ppi < len(pp_spans) and pp_spans[ppi][1] < t.pos:
                ppi += 1
            if ppi < len(pp_spans) and pp_spans[ppi][0] <= t.pos < pp_spans[ppi][1]:
                continue
            if t.kind in ('ws', 'nl', 'comment'):
                continue
            if start is None:
                start = i
            if t.kind == 'punct' and t.text in '([{':
                depth += 1
            elif t.kind == 'punct' and t.text in ')]}':
                depth -= 1
                if depth == 0 and t.text == '}':
                    # function body ends here unless a declaration continues
                    j = self.next_sig(i)
                    if j < len(toks) and toks[j].text in (';',) or self.is_typedef_or_decl(start, i):
                        continue
                    stmts.append((start, i, 'func'))
                    start = None
            elif depth == 0 and t.text == ';':
                stmts.append((start, i, 'decl'))
                start = None
        funcs = {fd.decl.coord.line: fd for fd in self.m.funcdefs if fd.coord.file == self.m.fn}
        for a, b, kind in stmts:
            words = [toks[k].text for k in range(a, b + 1) if toks[k].kind not in ('ws', 'nl', 'comment')]
            if kind == 'func':
                line = self.src.count('\n', 0, toks[a].pos) + 1
                fd = None
                for k in range(a, b):
                    if toks[k].kind == 'punct' and toks[k].text == '{':
                        break
                    ln = self.src.count('\n', 0, toks[k].pos) + 1
                    if ln in funcs:
                        fd = funcs[ln]
                if fd is not None and self.is_dropped_stub(fd):
                    self.delete_lines(a, b)
                continue
            if words and words[0] in ('typedef', 'extern'):
                self.delete_lines(a, b)
                continue
            if '=' not in words:
                # prototype or plain declaration
                self.delete_lines(a, b)
                continue
            self.notes.append('%s: kept definition with initialiser: %s' % (
                self.m.fn, ' '.join(words)[:80]))

    def is_typedef_or_decl(self, a, i):
        w = self.toks[a].text
        return w in ('typedef', 'extern', 'struct', 'union')

    def tokens_pass(self):
        kinds = {}
        for name, (t, node) in self.m.typedefs.items():
            if isinstance(t, Struct):
                v = self.mg.view_of_type(t)
                if v is not None and v.kind.name != name:
                    kinds[name] = v.kind.name
        pp = pm.preproc_lines(self.src)
        keep_pp = [(s, e) for s, e in pp if re.match(r'\s*#\s*define', self.src[s:e])]
        skip = [(s, e) for s, e in pp if (s, e) not in keep_pp]
        toks = self.toks
        i = 0
        si = 0
        while i < len(toks):
            t = toks[i]
            while si < len(skip) and skip[si][1] < t.pos:
                si += 1
            if si < len(skip) and skip[si][0] <= t.pos < skip[si][1]:
                i += 1
                continue
            if t.kind != 'ident':
                i += 1
                continue
            if t.text in pm.FAR_WORDS or t.text in pm.DROP_WORDS:
                e = t.pos + len(t.text)
                if e < len(self.src) and self.src[e] == ' ':
                    e += 1
                elif t.pos > 0 and self.src[t.pos - 1] == ' ':
                    self.ed.add(t.pos - 1, e, '')
                    i += 1
                    continue
                self.ed.add(t.pos, e, '')
                i += 1
                continue
            if t.text in BASE_WORDS:
                j = i
                words = []
                last = i
                while j < len(toks):
                    if toks[j].kind == 'ident' and toks[j].text in BASE_WORDS:
                        words.append(toks[j].text)
                        last = j
                        j += 1
                    elif toks[j].kind == 'ws':
                        j += 1
                    else:
                        break
                self.ed.add(t.pos, toks[last].pos + len(toks[last].text), spell_base(words))
                i = last + 1
                continue
            if t.text in kinds:
                self.ed.add(t.pos, t.pos + len(t.text), kinds[t.text])
            i += 1


DROPPED = []
INT16_COUNTS = port_int16.Counter()
INT16_SITES = []


def translate(fn, mg, sp, notes, counts):
    m = [x for x in mg.models if x.fn == fn][0]
    tr = FileTranslator(m, mg, sp)
    tr.extra_q = {}
    text = tr.run()
    text = re.sub(r'\n{3,}', '\n\n', text)
    text = re.sub(r'\)\n\n+\{\n', ')\n{\n', text)     # padding left by header overrides
    text = pm.apply_names(text)
    text, casts, sites = port_int16.process(fn, text)
    INT16_COUNTS.update(casts)
    INT16_SITES.extend(sites)
    with open(os.path.join(OUT, fn), 'w') as f:
        f.write(text)
    notes.extend(tr.notes)
    DROPPED.extend(tr.dropped)
    for k, v in tr.counts.items():
        counts[k] += v


def main(argv):
    mg = pm.Merge(pm.load_models())
    pm.collect_functions(mg)
    os.makedirs(OUT, exist_ok=True)
    pm.emit_game_h(mg, os.path.join(OUT, 'game.h'))
    pm.emit_win16api_h(mg, os.path.join(OUT, 'win16api.h'))
    pm.emit_globals_c(mg, os.path.join(OUT, 'globals.c'))
    sp = pm.Speller(mg)
    files = argv or pm.src_files()
    notes = []
    counts = defaultdict(int)
    for fn in files:
        translate(fn, mg, sp, notes, counts)
    with open(os.path.join(pm.ROOT, 'port', 'translate-notes.txt'), 'w') as f:
        f.write('\n'.join(notes) + '\n')
        for k, v in sorted(counts.items()):
            f.write('%s: %d\n' % (k, v))
        mg.report['dropped call arguments'] = [pm.apply_names(d) for d in DROPPED]
        mg.report['16-bit arithmetic casts by kind'] = [
            '%5d  %s' % (v, k) for k, v in sorted(INT16_COUNTS.items())] + [
            '%5d  total' % sum(v for k, v in INT16_COUNTS.items() if not k.startswith('('))]
        mg.report['16-bit arithmetic casts'] = INT16_SITES
        for sec, lines in mg.report.items():
            f.write('== %s (%d)\n' % (sec, len(lines)))
            for ln in lines:
                f.write('  %s\n' % ln)
    print('%d files, %d notes, %s' % (len(files), len(notes), dict(counts)))


if __name__ == '__main__':
    main(sys.argv[1:])
