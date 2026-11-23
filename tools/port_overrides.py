"""Signature decisions for the port, read from port/overrides/signatures.txt.

The decomp keeps each 1994 file's own prototypes; where they disagree
with the callee's definition, port/overrides/signatures.txt says which
signature is the real one.  The decisions are applied to the decomp text
in memory, before parsing, so game.h, the definitions and every caller
follow them.  src/inspace/ itself is never changed.

Entry forms (a line starting with whitespace continues the entry):

  fn NAME: PROTOTYPE [| return] [| forward]
      Replace the header of NAME's definition by PROTOTYPE (decomp
      syntax).  "return": the body's last statement is an expression whose
      value becomes the return value.  "forward": the run of the old
      parameter names in the body's call is replaced by the new names
      (for thunks whose parameters changed).
  extern NAME: DECLARATION
      Replace every file-scope declaration of the global NAME.
  call FILE:LINE NAME: ARGS
      Replace the argument list of the call to NAME on that decomp line.
  local FILE FUNC: OLD => NEW
      In FUNC's body, replace the declaration text OLD by NEW (a local
      declared as a byte block but used as a real type).
"""
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PATH = os.path.join(ROOT, 'port', 'overrides', 'signatures.txt')


class Overrides:
    def __init__(self, path=PATH):
        self.funcs = {}      # name -> (proto, set(opts))
        self.externs = {}    # name -> decl
        self.calls = {}      # (file, line, name) -> args text
        self.locals = []     # (file, func, old, new)
        if os.path.exists(path):
            self.load(path)

    def load(self, path):
        entries = []
        with open(path) as f:
            for line in f:
                line = line.rstrip('\n')
                if not line.strip() or line.lstrip().startswith('#'):
                    continue
                if line[0] in ' \t' and entries:
                    entries[-1] += '\n    ' + line.strip()
                else:
                    entries.append(line.strip())
        for e in entries:
            m = re.match(r'fn\s+(\w+)\s*:\s*(.*)$', e, re.S)
            if m:
                parts = [p.strip() for p in m.group(2).split('|')]
                self.funcs[m.group(1)] = (parts[0], set(parts[1:]))
                continue
            m = re.match(r'extern\s+(\w+)\s*:\s*(.*)$', e, re.S)
            if m:
                self.externs[m.group(1)] = m.group(2).strip()
                continue
            m = re.match(r'call\s+(\S+?):(\d+)\s+(\w+)\s*:\s*(.*)$', e, re.S)
            if m:
                self.calls[(m.group(1), int(m.group(2)), m.group(3))] = ' '.join(m.group(4).split())
                continue
            m = re.match(r'local\s+(\S+)\s+(\w+)\s*:\s*(.*?)\s*=>\s*(.*)$', e, re.S)
            if m:
                self.locals.append((m.group(1), m.group(2), m.group(3).strip(), m.group(4).strip()))
                continue
            raise ValueError('bad override entry: %s' % e)

    # -- application to the decomp text ---------------------------------------
    def apply(self, fn, text):
        for name, (proto, opts) in self.funcs.items():
            text = self.apply_fn(text, name, proto, opts)
        for name, decl in self.externs.items():
            text = self.apply_extern(text, name, decl)
        for f, func, old, new in self.locals:
            if f != fn:
                continue
            r = self.find_def(text, func)
            if r is None:
                raise ValueError('local override: no %s in %s' % (func, fn))
            e = self.body_end(text, r[1])
            body = text[r[1]:e]
            if old not in body:
                raise ValueError('local override: %r not in %s' % (old, func))
            text = text[:r[1]] + body.replace(old, new, 1) + text[e:]
        return text

    @staticmethod
    def match_paren(text, i):
        d = 0
        for j in range(i, len(text)):
            if text[j] == '(':
                d += 1
            elif text[j] == ')':
                d -= 1
                if d == 0:
                    return j
        return None

    def find_def(self, text, name):
        """(header start, body '{' index, params text) of name's definition."""
        for m in re.finditer(r'\b%s\s*\(' % re.escape(name), text):
            ls = text.rfind('\n', 0, m.start()) + 1
            head = text[ls:m.start()]
            if ';' in head or '=' in head or head.strip() == '' or head.startswith((' ', '\t')):
                continue
            close = self.match_paren(text, m.end() - 1)
            rest = text[close + 1:]
            k = len(rest) - len(rest.lstrip())
            if rest[k:k + 1] == ';' or rest[k:k + 1] == ',':
                continue
            brace = text.find('{', close)
            return ls, brace, text[m.end():close]
        return None

    @staticmethod
    def param_names(params):
        names = []
        for p in params.split(','):
            m = re.search(r'(\w+)\s*(\[[^\]]*\])?\s*$', p.strip())
            if m and m.group(1) not in ('void',):
                names.append(m.group(1))
        return names

    def apply_fn(self, text, name, proto, opts):
        r = self.find_def(text, name)
        if r is None:
            return text
        ls, brace, old_params = r
        old = text[ls:brace]
        new = proto.rstrip() + '\n'
        if new.count('\n') > old.count('\n'):
            new = ' '.join(proto.split()) + '\n'
        pad = old.count('\n') - new.count('\n')
        if pad > 0:
            new += '\n' * pad
        body_end = self.body_end(text, brace)
        body = text[brace:body_end]
        if 'forward' in opts:
            onames = self.param_names(old_params)
            pm = re.search(r'\(([^()]*)\)\s*$', proto)
            nnames = self.param_names(pm.group(1)) if pm else []
            pat = r'\b' + r'\s*,\s*'.join(re.escape(n) + r'\b' for n in onames)
            body = re.sub(pat, ', '.join(nnames), body, count=1)
        if 'return' in opts:
            # last statement of the body
            k = body.rstrip().rfind('}')
            semi = body.rfind(';', 0, k)
            prev = max(body.rfind(';', 0, semi), body.rfind('{', 0, semi), body.rfind('}', 0, semi))
            s = prev + 1
            while body[s] in ' \t\n':
                s += 1
            body = body[:s] + 'return ' + body[s:]
        return text[:ls] + new + body + text[body_end:]

    @staticmethod
    def body_end(text, brace):
        d = 0
        for j in range(brace, len(text)):
            if text[j] == '{':
                d += 1
            elif text[j] == '}':
                d -= 1
                if d == 0:
                    return j + 1
        return len(text)

    def apply_extern(self, text, name, decl):
        pat = re.compile(r'(?m)^[ \t]*extern\b[^;]*?\b%s\b[^;]*;' % re.escape(name))

        def rep(m):
            old = m.group(0)
            new = decl
            if new.count('\n') > old.count('\n'):
                new = ' '.join(decl.split())
            pad = old.count('\n') - new.count('\n')
            return new + '\n' * max(pad, 0)
        return pat.sub(rep, text)


_OV = None


def overrides():
    global _OV
    if _OV is None:
        _OV = Overrides()
    return _OV
