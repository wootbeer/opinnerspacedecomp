"""ISPACE.DLL run under Unicorn: the DLL's own code (unpacked in memory from
the user's data/ISPACE.DLL) in 16-bit real mode, with Python stand-ins for
the Windows calls it makes.  A test oracle only; never part of the port.

Selectors are paragraphs: segment n of the DLL is loaded at its own
paragraph and far pointers are paragraph:offset.  Each import is a
`retf n` thunk; a code hook on it runs the stand-in, which reads the
Pascal arguments from the stack and returns DX:AX.

The stand-ins model what the DLL's results depend on: global memory,
resources of ISPACE.DLL and IGRAPHIC.DLL, palettes (CreatePalette,
AnimatePalette on PC_RESERVED entries), 8-bit bitmaps with their pixels
(CreateDIBitmap, CreateCompatibleBitmap, SRCCOPY BitBlt/StretchBlt,
colour-to-monochrome BitBlt).  Calls without a stand-in stop the run."""
import os
import struct
import sys

from unicorn import Uc, UC_ARCH_X86, UC_MODE_16, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_AX, UC_X86_REG_BP, UC_X86_REG_CS, UC_X86_REG_DS,
                               UC_X86_REG_DX, UC_X86_REG_ES, UC_X86_REG_SP, UC_X86_REG_SS)

TOOLS = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, TOOLS)
from ne_info import read_ne          # noqa: E402
from ne_relocs import relocs         # noqa: E402
from ne_resources import resources   # noqa: E402
from optl_unpack import unpack       # noqa: E402

ROOT = os.path.dirname(TOOLS)
DATA_SEG = 11                        # ISPACE.DLL's DGROUP
HINST = {0x0b00: 'ISPACE', 0x0c00: 'IGRAPHIC', 0x0d00: 'ENG_LANG', 0x0e00: 'SND_FX', 0x0f00: 'ENG_FX'}
ISPACE_HINST_SLOT = 0x1a30           # DS words LibMain / ordinal 3 would fill
IGRAPHIC_HINST_SLOT = 0x0692
LANG_HINST_SLOT = 0x0690            # the language DLL (ordinal 7, 9:0174)
SRCCOPY = 0x00cc0020

# The 20 static colours of the Windows 3.1 system palette.
STATICS = {0: (0, 0, 0), 1: (128, 0, 0), 2: (0, 128, 0), 3: (128, 128, 0), 4: (0, 0, 128),
           5: (128, 0, 128), 6: (0, 128, 128), 7: (192, 192, 192), 8: (192, 220, 192),
           9: (166, 202, 240), 246: (255, 251, 240), 247: (160, 160, 164), 248: (128, 128, 128),
           249: (255, 0, 0), 250: (0, 255, 0), 251: (255, 255, 0), 252: (0, 0, 255),
           253: (255, 0, 255), 254: (0, 255, 255), 255: (255, 255, 255)}
TYPENAMES = {2: 'BITMAP', 6: 'STRING', 10: 'RCDATA'}
# INSPACE.INI for the sound ordinals (tools/README.md, sound.txt): one
# channel, as the DLL has with no WAVEMIX.DLL in the Windows folder.
INI = {'SndPath': 'C:\\SPACE\\SOUNDS\\', 'Language': 'ENG', 'MixChannels': '1'}
CAPS = {8: 640, 10: 480, 12: 8, 14: 1, 24: 20, 38: 0x799, 104: 256, 106: 20}


def import_names():
    names = {}
    for line in open(os.path.join(ROOT, 'names', 'imports.txt')):
        p = line.split()
        if len(p) >= 2 and '.' in p[0]:
            names[p[0]] = p[1]
    return names


def entry_points(data):
    """Ordinal -> (segment, offset) from the NE entry table."""
    h, _ = read_ne(data)
    p = h['ne'] + h['entry_off']
    out, ordinal = {}, 1
    while data[p]:
        count, kind = data[p], data[p + 1]
        p += 2
        for _ in range(count):
            if kind == 0xff:
                out[ordinal] = (data[p + 3], struct.unpack_from('<H', data, p + 4)[0])
                p += 6
            elif kind:
                out[ordinal] = (kind, struct.unpack_from('<H', data, p + 1)[0])
                p += 3
            ordinal += 1
    return out


def load_resources(data):
    return {(str(t), str(n)): blob for t, n, blob in resources(data)}


class IspaceEmu:
    def __init__(self, data_dir):
        packed = open(os.path.join(data_dir, 'ISPACE.DLL'), 'rb').read()
        data = unpack(packed)
        self.entries = entry_points(data)
        self.res = {'ISPACE': load_resources(packed),
                    'IGRAPHIC': load_resources(open(os.path.join(data_dir, 'IGRAPHIC.DLL'), 'rb').read()),
                    'ENG_LANG': load_resources(open(os.path.join(data_dir, 'ENG_LANG.DLL'), 'rb').read()),
                    'SND_FX': load_resources(open(os.path.join(data_dir, 'SOUNDS', 'SND_FX.DLL'), 'rb').read()),
                    'ENG_FX': load_resources(open(os.path.join(data_dir, 'SOUNDS', 'ENG_FX.DLL'), 'rb').read())}
        self.data_dir = data_dir
        self.ini = dict(INI)
        self.wave_volume = self.midi_volume = 0xffffffff
        self.uc = Uc(UC_ARCH_X86, UC_MODE_16)
        self.uc.mem_map(0, 0x111000)
        self._load(data)
        self.blocks = {}                     # global handle -> [paragraph, size]
        self.free = [(self.heap_lo, 0x10ff0 - self.heap_lo)]
        self.next_mem = 0x2000
        self.gdi = {}                        # GDI handle -> dict(kind=...)
        self.next_gdi = 0x400
        self.res_handles = {}
        self.time = 100000
        self.failed = None
        self.texts = []
        self.wds(ISPACE_HINST_SLOT, 0x0b00)
        self.wds(IGRAPHIC_HINST_SLOT, 0x0c00)
        self.wds(LANG_HINST_SLOT, 0x0d00)
        self.stock = {}
        for i, kw in STOCK.items():
            self.stock[i] = self.new_gdi(kw[0], **kw[1])

    # loading
    def _load(self, data):
        _, segs = read_ne(data)
        para, self.para = 0x100, {}
        for s in segs:
            self.para[s['n']] = para
            self.uc.mem_write(para * 16, data[s['file_off']:s['file_off'] + s['len']])
            size = 0x10000 if s['n'] == DATA_SEG else max(s['alloc'], s['len'])
            para = (para + (size + 15) // 16 + 0xff) & ~0xff
        self.ds = self.para[DATA_SEG]
        self.thunk = para
        self.ss = para + 0x100
        self.heap_lo = self.ss + 0x1000
        names, self.imports, index = import_names(), [], {}
        consts = {'__AHSHIFT': 12, '__AHINCR': 0x1000, '__WINFLAGS': 0x0413}
        for s, src, _, sites, tgt in relocs(data):
            base = self.para[s['n']] * 16
            for site in sites:
                if tgt.startswith('osfixup'):
                    continue
                if ':' in tgt:
                    seg, off = tgt.split(':')
                    seg, off = int(seg), int(off, 16)
                    val = {3: struct.pack('<HH', off, self.para[seg]),
                           2: struct.pack('<H', self.para[seg]), 5: struct.pack('<H', off)}[src]
                    self.uc.mem_write(base + site, val)
                    continue
                name = names.get(tgt.upper(), tgt)
                if src == 3:
                    if name not in index:
                        index[name] = len(self.imports)
                        self.imports.append(name)
                    self.uc.mem_write(base + site, struct.pack('<HH', index[name] * 4, self.thunk))
                else:
                    v = consts[name]
                    self.uc.mem_write(base + site, bytes([v & 0xff]) if src == 0 else struct.pack('<H', v))
        for i, name in enumerate(self.imports):
            nbytes = API[name][0] if name in API else 0
            self.uc.mem_write(self.thunk * 16 + i * 4, b'\xca' + struct.pack('<H', nbytes) + b'\x90')
        self.uc.mem_write(self.thunk * 16 + 0xff0, b'\xf4')     # return address of call()
        self.uc.hook_add(UC_HOOK_CODE, self._on_import, begin=self.thunk * 16,
                         end=self.thunk * 16 + 0xfef)

    # memory
    def rd(self, lin, n):
        return bytes(self.uc.mem_read(lin, n))

    def word(self, lin):
        return struct.unpack('<H', self.rd(lin, 2))[0]

    def wds(self, off, v):
        self.uc.mem_write(self.ds * 16 + off, struct.pack('<H', v & 0xffff))

    @staticmethod
    def lin(fp):
        return (fp >> 16 & 0xffff) * 16 + (fp & 0xffff)

    def cstr(self, lin):
        out = bytearray()
        while True:
            c = self.rd(lin + len(out), 1)[0]
            if not c:
                return out.decode('latin-1')
            out.append(c)

    def galloc(self, size):
        size = (size + 31) & ~31
        n = (size + 15) // 16 + 1
        for i, (p, avail) in enumerate(self.free):
            if avail >= n:
                self.free[i] = (p + n, avail - n)
                h, self.next_mem = self.next_mem, self.next_mem + 2
                self.blocks[h] = [p, size]
                self.uc.mem_write(p * 16, bytes(size))
                return h
        raise MemoryError(size)

    def gfree(self, h):
        if h not in self.blocks:
            return
        p, size = self.blocks.pop(h)
        merged = []
        for q, n in sorted(self.free + [(p, (size + 15) // 16 + 1)]):
            if merged and merged[-1][0] + merged[-1][1] == q:
                merged[-1] = (merged[-1][0], merged[-1][1] + n)
            else:
                merged.append((q, n))
        self.free = merged

    def far_string(self, s):
        """A string in a new global block; its far pointer."""
        h = self.galloc(len(s) + 1)
        self.uc.mem_write(self.blocks[h][0] * 16, s.encode('latin-1') + b'\0')
        return self.blocks[h][0] << 16

    def new_gdi(self, kind, **kw):
        h, self.next_gdi = self.next_gdi, self.next_gdi + 2
        kw['kind'] = kind
        self.gdi[h] = kw
        return h

    def obj(self, h, kind):
        o = self.gdi.get(h)
        return o if o and o['kind'] == kind else None

    # calls
    def _on_import(self, uc, addr, size, ud):
        off = addr - self.thunk * 16
        if off % 4:
            return
        name = self.imports[off // 4]
        if name not in API:
            self.failed = name
            uc.emu_stop()
            return
        nbytes, spec, fn = API[name]
        p = self.ss * 16 + uc.reg_read(UC_X86_REG_SP) + 4 + nbytes
        args = []
        for t in spec:
            p -= 2 if t == 'w' else 4
            args.append(self.word(p) if t == 'w' else struct.unpack('<I', self.rd(p, 4))[0])
        r = fn(self, *args) or 0
        uc.reg_write(UC_X86_REG_AX, r & 0xffff)
        uc.reg_write(UC_X86_REG_DX, r >> 16 & 0xffff)

    def call(self, seg, off, words):
        """Far call of seg:off with words pushed in order (Pascal: the
        first parameter first).  Returns DX:AX."""
        uc, sp = self.uc, 0xfff0
        for w in words:
            sp -= 2
            uc.mem_write(self.ss * 16 + sp, struct.pack('<H', w & 0xffff))
        sp -= 4
        uc.mem_write(self.ss * 16 + sp, struct.pack('<HH', 0xff0, self.thunk))
        for reg, v in ((UC_X86_REG_SS, self.ss), (UC_X86_REG_SP, sp), (UC_X86_REG_DS, self.ds),
                       (UC_X86_REG_ES, self.ds), (UC_X86_REG_BP, 0), (UC_X86_REG_AX, self.ds),
                       (UC_X86_REG_CS, self.para[seg])):
            uc.reg_write(reg, v)
        uc.emu_start(self.para[seg] * 16 + off, self.thunk * 16 + 0xff0, count=500_000_000)
        if self.failed:
            raise RuntimeError('no stand-in for ' + self.failed)
        return uc.reg_read(UC_X86_REG_AX) | uc.reg_read(UC_X86_REG_DX) << 16

    def call_ordinal(self, ordinal, words):
        return self.call(*self.entries[ordinal], words)

    # GDI state the comparisons read
    def dc_palette(self, dc):
        """The selected palette's colours by index, or None (the default
        palette: the static colours)."""
        return self.dc_palette_of(self.obj(dc, 'dc'))

    def dc_palette_of(self, d):
        p = self.obj(d['pal'], 'pal') if d else None
        return [tuple(e[:3]) for e in p['e']] if p else None

    def bitmap(self, h):
        return self.obj(h, 'bmp')

    def palette(self, h):
        p = self.obj(h, 'pal')
        return [tuple(e[:3]) for e in p['e']] if p else None


API = {}


def api(nbytes, spec):
    def deco(f):
        API[f.__name__.upper()] = (nbytes, spec, f)
        return f
    return deco


# KERNEL
@api(6, 'wl')
def GlobalAlloc(e, flags, size):
    return e.galloc(size)


@api(8, 'wlw')
def GlobalReAlloc(e, h, size, flags):
    p, old = e.blocks[h]
    data = e.rd(p * 16, min(old, size))
    e.gfree(h)
    nh = e.galloc(size)
    e.uc.mem_write(e.blocks[nh][0] * 16, data)
    return nh


@api(2, 'w')
def GlobalLock(e, h):
    return e.blocks[h][0] << 16 if h in e.blocks else 0


@api(2, 'w')
def GlobalUnlock(e, h):
    return 0


@api(2, 'w')
def GlobalFree(e, h):
    e.gfree(h)


@api(2, 'w')
def GlobalSize(e, h):
    """Windows 3.1 gives blocks in 32-byte units; the scene data of
    IGRAPHIC.DLL (type 6600) is laid out for that."""
    return (e.blocks[h][1] + 31) & ~31 if h in e.blocks else 0


@api(6, 'www')
def LocalInit(e, seg, start, end):
    return 1


@api(0, '')
def GetCurrentTime(e):
    e.time += 55
    return e.time


@api(0, '')
def timeGetTime(e):
    e.time += 55
    return e.time


@api(0, '')
def GetVersion(e):
    return 0x0a03


@api(0, '')
def GetWinFlags(e):
    """As the port's: a 486 with a coprocessor in enhanced mode."""
    return 0x0429


def put_string(e, fp, text, size):
    data = text.encode('latin-1')[:max(size - 1, 0)]
    e.uc.mem_write(e.lin(fp), data + b'\0')
    return len(data)


@api(6, 'lw')
def GetWindowsDirectory(e, fp, size):
    return put_string(e, fp, 'C:\\WINDOWS', size)


@api(6, 'lw')
def GetSystemDirectory(e, fp, size):
    return put_string(e, fp, 'C:\\WINDOWS\\SYSTEM', size)


@api(22, 'llllwl')
def GetPrivateProfileString(e, app, key, default, ret, size, file):
    """INSPACE.INI as INI below; no other INI files (the port's settings
    folder has none of SYSTEM.INI, CONTROL.INI, PROTOCOL.INI or
    NETWORK.INF): the default."""
    v = e.ini.get(e.cstr(e.lin(key))) if e.cstr(e.lin(file)).upper() == 'INSPACE.INI' else None
    return put_string(e, ret, v if v is not None else e.cstr(e.lin(default)), size)


@api(14, 'llwl')
def GetPrivateProfileInt(e, app, key, default, file):
    v = e.ini.get(e.cstr(e.lin(key))) if e.cstr(e.lin(file)).upper() == 'INSPACE.INI' else None
    return int(v) & 0xffff if v is not None else default


@api(16, 'llll')
def WritePrivateProfileString(e, app, key, value, file):
    if e.cstr(e.lin(file)).upper() == 'INSPACE.INI':
        e.ini[e.cstr(e.lin(key))] = e.cstr(e.lin(value))
    return 1


def host_path(e, dos):
    """C:\\SPACE\\... in the data folder; nothing else exists."""
    dos = dos.upper()
    if not dos.startswith('C:\\SPACE\\'):
        return None
    return os.path.join(e.data_dir, *dos[len('C:\\SPACE\\'):].split('\\'))


@api(10, 'llw')
def OpenFile(e, name, of, mode):
    """Existence checks (OF_EXIST) only."""
    p = host_path(e, e.cstr(e.lin(name)))
    return 1 if p and os.path.exists(p) else 0xffff


@api(8, 'll')
def lstrcat(e, a, b):
    e.uc.mem_write(e.lin(a), (e.cstr(e.lin(a)) + e.cstr(e.lin(b))).encode('latin-1') + b'\0')
    return a


@api(0, '')
def waveOutGetNumDevs(e):
    return 1


@api(8, 'wlw')
def waveOutGetDevCaps(e, dev, fp, size):
    """As the port's: one stereo device with left and right volume
    (WAVECAPS_VOLUME | WAVECAPS_LRVOLUME), no WAVECAPS_SYNC."""
    caps = struct.pack('<HHH32sIHI', 0, 0, 0, b'', 0, 2, 0x0c)
    e.uc.mem_write(e.lin(fp), caps[:size])
    return 0


@api(2, 'w')
def GetSystemMetrics(e, i):
    return {0: 640, 1: 480}.get(i, 0)


@api(10, 'wwlw')
def LoadString(e, inst, sid, fp, size):
    blob = e.res[HINST[inst]].get(('STRING', str((sid >> 4) + 1)))
    text, q = '', 0
    for i in range(16 if blob else 0):
        n = blob[q]
        if i == sid & 15:
            text = blob[q + 1:q + 1 + n].decode('latin-1')
        q += 1 + n
    return put_string(e, fp, text, size)


def res_name(e, fp):
    if fp >> 16 == 0:
        return str(fp & 0xffff)
    s = e.cstr(e.lin(fp))
    return s[1:] if s.startswith('#') else s.upper()


@api(10, 'wll')
def FindResource(e, inst, name, typ):
    t = res_name(e, typ)
    if t.isdigit():
        t = TYPENAMES.get(int(t), t)
    key = (t, res_name(e, name))
    mod = HINST.get(inst)
    if mod is None or key not in e.res[mod]:
        return 0
    h = 0x100 + 2 * len(e.res_handles)
    e.res_handles[h] = (mod, key)
    return h


@api(4, 'ww')
def LoadResource(e, inst, hres):
    mod, key = e.res_handles[hres]
    blob = e.res[mod][key]
    h = e.galloc(len(blob))
    e.uc.mem_write(e.blocks[h][0] * 16, blob)
    return h


@api(2, 'w')
def LockResource(e, h):
    return GlobalLock(e, h)


@api(2, 'w')
def FreeResource(e, h):
    e.gfree(h)


@api(4, 'ww')
def SizeofResource(e, inst, hres):
    mod, key = e.res_handles[hres]
    return len(e.res[mod][key])


@api(4, 'l')
def LoadLibrary(e, name):
    n = e.cstr(e.lin(name)).upper()
    for h, mod in HINST.items():
        if mod + '.DLL' in n:
            return h
    return 0x0b00


@api(2, 'w')
def FreeLibrary(e, h):
    return 0


@api(8, 'll')
def lstrcmp(e, a, b):
    x, y = e.cstr(e.lin(a)), e.cstr(e.lin(b))
    return 0 if x == y else (1 if x > y else 0xffff)


@api(8, 'll')
def lstrcpy(e, a, b):
    e.uc.mem_write(e.lin(a), e.cstr(e.lin(b)).encode('latin-1') + b'\0')
    return a


@api(4, 'l')
def lstrlen(e, a):
    return len(e.cstr(e.lin(a)))


# GDI: device contexts
def new_dc(e):
    return e.new_gdi('dc', bmp=None, pal=None, bk=0xffffff, text=0, brush=e.stock[0],
                     pen=e.stock[7], pos=(0, 0))


@api(16, 'llll')
def CreateDC(e, a, b, c, d):
    return new_dc(e)


@api(2, 'w')
def CreateCompatibleDC(e, dc):
    return new_dc(e)


@api(2, 'w')
def GetDC(e, hwnd):
    return new_dc(e)


@api(2, 'w')
def DeleteDC(e, dc):
    e.gdi.pop(dc, None)
    return 1


@api(4, 'ww')
def ReleaseDC(e, hwnd, dc):
    return DeleteDC(e, dc)


@api(4, 'ww')
def GetDeviceCaps(e, dc, i):
    return CAPS.get(i, 0)


SLOT = {'bmp': 'bmp', 'brush': 'brush', 'pen': 'pen', 'font': 'font'}


@api(4, 'ww')
def SelectObject(e, dc, h):
    d = e.obj(dc, 'dc')
    o = e.gdi.get(h)
    if not d or not o or o['kind'] not in SLOT:
        return 0x3f2
    slot = SLOT[o['kind']]
    old, d[slot] = d.get(slot), h
    return old or 0x3f2


@api(2, 'w')
def DeleteObject(e, h):
    e.gdi.pop(h, None)
    return 1


@api(2, 'w')
def GetStockObject(e, i):
    return e.stock.get(i, 0x380 + 2 * i)


@api(6, 'wl')
def SetBkColor(e, dc, c):
    d = e.obj(dc, 'dc')
    old = d['bk'] if d else 0
    if d:
        d['bk'] = c
    return old


@api(4, 'ww')
def SetStretchBltMode(e, dc, m):
    return 1


# GDI: palettes
@api(10, 'wwwl')
def GetSystemPaletteEntries(e, dc, start, n, fp):
    for i in range(n):
        r, g, b = STATICS.get((start + i) & 0xff, (0, 0, 0))
        e.uc.mem_write(e.lin(fp) + 4 * i, bytes([r, g, b, 0]))
    return n


@api(4, 'l')
def CreatePalette(e, fp):
    n = e.word(e.lin(fp) + 2)
    return e.new_gdi('pal', e=[list(e.rd(e.lin(fp) + 4 + 4 * i, 4)) for i in range(n)])


@api(10, 'wwwl')
def AnimatePalette(e, pal, start, n, fp):
    p = e.obj(pal, 'pal')
    ent = e.rd(e.lin(fp), 4 * n)
    for i in range(n if p else 0):
        if start + i < len(p['e']) and p['e'][start + i][3] & 1:
            p['e'][start + i][:3] = list(ent[4 * i:4 * i + 3])


@api(6, 'www')
def SelectPalette(e, dc, pal, force):
    d = e.obj(dc, 'dc')
    if not d:
        return 0x3f0
    old, d['pal'] = d['pal'], pal
    return old or 0x3f0


@api(2, 'w')
def RealizePalette(e, dc):
    return 0


# GDI: bitmaps.  Pixels are top-down, one byte each (0/1 when monochrome).
def new_bitmap(e, w, h, mono=False, px=None):
    return e.new_gdi('bmp', w=w, h=h, mono=mono, px=px if px is not None else bytearray(w * h))


@api(6, 'www')
def CreateCompatibleBitmap(e, dc, w, h):
    return new_bitmap(e, w, h)


@api(12, 'wwwwl')
def CreateBitmap(e, w, h, planes, bpp, bits):
    return new_bitmap(e, w, h, mono=planes * bpp == 1)


def nearest(pal, rgb):
    """Index of the colour nearest rgb (squared distance, the first on a
    tie) in pal, or among the static colours when pal is None.  The port's
    rule; Windows 3.1's own is not verified."""
    cands = list(enumerate(pal)) if pal else sorted(STATICS.items())
    return min(cands, key=lambda c: sum((a - b) ** 2 for a, b in zip(c[1], rgb)))[0]


def dib_bitmap(e, w, h, bpp, bits, table, mono=False):
    """A bottom-up DIB's pixels (1, 4 or 8 bits) mapped through table."""
    stride = (w * bpp + 31) // 32 * 4
    px = bytearray(w * h)
    for y in range(h):
        row = bits[(h - 1 - y) * stride:(h - y) * stride]
        for x in range(w):
            v = row[x] if bpp == 8 else row[x * bpp // 8] >> (8 - bpp - x * bpp % 8) & ((1 << bpp) - 1)
            px[y * w + x] = table[v] if v < len(table) else table[0]
    return new_bitmap(e, w, h, mono, px)


@api(20, 'wllllw')
def CreateDIBitmap(e, dc, hdr, init, bits, bmi, usage):
    size, w, h, _, bpp, _, _, _, _, used = struct.unpack('<IiiHHIIiiI', e.rd(e.lin(hdr), 36))
    n = min(used or 1 << bpp, 1 << bpp)
    table = e.rd(e.lin(bmi) + size, 4 * n)
    if usage == 1:
        table = [table[2 * i] for i in range(n)]
    else:
        pal = e.dc_palette(dc)
        table = [nearest(pal, tuple(table[4 * i:4 * i + 3][::-1])) for i in range(n)]
    stride = (w * bpp + 31) // 32 * 4
    return dib_bitmap(e, w, h, bpp, e.rd(e.lin(bits), stride * h), table)


@api(6, 'wl')
def LoadBitmap(e, inst, name):
    """As the port's LoadBitmap model: monochrome stays monochrome,
    colours become their nearest static colour."""
    key = ('BITMAP', res_name(e, name))
    dib = e.res[HINST[inst]].get(key)
    if not dib:
        return 0
    size = struct.unpack_from('<I', dib)[0]
    if size == 12:
        w, h, _, bpp = struct.unpack_from('<HHHH', dib, 4)
        n, q = 1 << bpp, 3
    else:
        w, h, _, bpp = struct.unpack_from('<iiHH', dib, 4)
        n, q = min(struct.unpack_from('<I', dib, 32)[0] or 1 << bpp, 1 << bpp), 4
    cols = [tuple(dib[size + q * i:size + q * i + 3][::-1]) for i in range(n)]
    table = [int(sum(c) >= 384) for c in cols] if bpp == 1 else [nearest(None, c) for c in cols]
    return dib_bitmap(e, w, h, bpp, dib[size + q * n:], table, mono=bpp == 1)


@api(8, 'wwl')
def GetObject(e, h, n, fp):
    b = e.bitmap(h)
    if not b:
        return 0
    bpp = 1 if b['mono'] else 8
    wb = (b['w'] * bpp + 15) // 16 * 2
    e.uc.mem_write(e.lin(fp), struct.pack('<HHHHBBI', 0, b['w'], b['h'], wb, 1, bpp, 0)[:n])
    return n


def s16(v):
    return v - 0x10000 if v & 0x8000 else v


def rop3(code, p, s, d):
    """The ternary raster operation, bit by bit (as port/src/win/draw.c)."""
    r = 0
    for i in range(8):
        if code >> i & 1:
            r |= (p if i & 4 else ~p) & (s if i & 2 else ~s) & (d if i & 1 else ~d)
    return r & 0xff


def color_index(e, d, c):
    """The port's rule (gdi.c color_index): PALETTEINDEX as is,
    PALETTERGB the nearest entry of the DC's palette, anything else the
    nearest static colour."""
    rgb = (c & 0xff, c >> 8 & 0xff, c >> 16 & 0xff)
    if c >> 24 == 1:
        return c & 0xff
    pal = e.dc_palette_of(d)
    if c >> 24 == 2 and pal:
        return nearest(pal, rgb)
    return nearest(None, rgb)


def pixel_of(e, d, c):
    b = e.bitmap(d['bmp']) if d else None
    if not b or not b['mono']:
        return color_index(e, d, c)
    if c >> 24 == 1:
        pal = e.dc_palette_of(d) or [STATICS.get(i, (0, 0, 0)) for i in range(256)]
        return int(sum(pal[c & 0xff]) >= 384)
    return int((c & 0xff) + (c >> 8 & 0xff) + (c >> 16 & 0xff) >= 384)


def brush_pixel(e, d, x, y):
    b = e.gdi.get(d.get('brush'))
    if not b or b['kind'] != 'brush' or b.get('null'):
        return 0
    if b.get('pattern') is None:
        return pixel_of(e, d, b['color'])
    v = b['pattern'][(y & 7) * 8 + (x & 7)]
    if b.get('mono'):
        return pixel_of(e, d, d['bk'] if v else d['text'])
    return v


def blit(e, dst, x, y, w, h, src, sx, sy, sw, sh, rop):
    """port/src/win/draw.c draw_blit: any ROP3 on palette indices,
    stretching by nearest pixel, negative extents mirror; within one
    bitmap the source is read as it was before the blit."""
    x, y, w, h, sx, sy, sw, sh = map(s16, (x, y, w, h, sx, sy, sw, sh))
    d, s = e.obj(dst, 'dc'), e.obj(src, 'dc') if src is not None else None
    db = e.bitmap(d['bmp']) if d else None
    sb = e.bitmap(s['bmp']) if s else None
    code = rop >> 16 & 0xff
    aw, ah, asw, ash = abs(w), abs(h), abs(sw), abs(sh)
    if not db or not aw or not ah or (s and (not sb or not asw or not ash)):
        return 1
    x0, y0 = (x + w + 1 if w < 0 else x), (y + h + 1 if h < 0 else y)
    sx0, sy0 = (sx + sw + 1 if sw < 0 else sx), (sy + sh + 1 if sh < 0 else sy)
    mx, my = (w < 0) != (sw < 0), (h < 0) != (sh < 0)
    mask = 1 if db['mono'] else 0xff
    sbk = pixel_of(e, s, s['bk']) if sb and not sb['mono'] and db['mono'] else None
    W, H, px = db['w'], db['h'], db['px']
    spx = sb and (bytes(sb['px']) if sb is db else sb['px'])
    for j in range(ah):
        ty = y0 + j
        if not 0 <= ty < H:
            continue
        syy = 0
        if sb:
            k = j * ash // ah
            syy = sy0 + (ash - 1 - k if my else k)
        for i in range(aw):
            tx = x0 + i
            if not 0 <= tx < W:
                continue
            sv = 0
            if sb:
                k = i * asw // aw
                sxx = sx0 + (asw - 1 - k if mx else k)
                if 0 <= sxx < sb['w'] and 0 <= syy < sb['h']:
                    sv = spx[syy * sb['w'] + sxx]
                    if sb['mono'] != db['mono']:
                        sv = pixel_of(e, d, d['bk'] if sv else d['text']) if sb['mono'] else int(sv == sbk)
            pv = brush_pixel(e, d, tx, ty)
            px[ty * W + tx] = rop3(code, pv, sv, px[ty * W + tx]) & mask
    return 1


def cdiv(a, b):
    """C division (truncating towards zero)."""
    q = abs(a) // abs(b)
    return q if (a < 0) == (b < 0) else -q


@api(8, 'wlw')
def Polygon(e, dc, points, n):
    """port/src/win/draw.c Polygon: rows filled between pairs of edge
    crossings (alternate rule) with the brush, then the outline."""
    d = e.obj(dc, 'dc')
    pts = [tuple(map(s16, struct.unpack_from('<2H', e.rd(e.lin(points) + 4 * i, 4)))) for i in range(n)]
    if not d or n < 2:
        return 0
    ys = [p[1] for p in pts]
    for y in range(min(ys), max(ys)):
        xs = []
        for i in range(n):
            (xa, ya), (xb, yb) = pts[i - 1], pts[i]
            if (ya <= y < yb) or (yb <= y < ya):
                xs.append(xa + cdiv((y - ya) * (xb - xa), yb - ya))
        xs.sort()
        for i in range(0, len(xs) - 1, 2):
            blit(e, dc, xs[i], y, xs[i + 1] - xs[i], 1, None, 0, 0, 0, 0, 0xf00021)
    for i in range(n):
        line(e, d, *pts[i - 1], *pts[i])
    return 1


@api(14, 'wwwwwl')
def PatBlt(e, dc, x, y, w, h, rop):
    return blit(e, dc, x, y, w, h, None, 0, 0, 0, 0, rop)


# GDI: brushes, pens, lines, pixels, text state
STOCK = {0: ('brush', dict(color=0xffffff)), 1: ('brush', dict(color=0xc0c0c0)),
         2: ('brush', dict(color=0x808080)),
         3: ('brush', dict(color=0x404040, pattern=[0 if (i // 8 + i % 8) & 1 else 248 for i in range(64)])),
         4: ('brush', dict(color=0)), 5: ('brush', dict(color=0, null=True)),
         6: ('pen', dict(color=0xffffff)), 7: ('pen', dict(color=0)), 8: ('pen', dict(color=0, null=True))}


@api(4, 'l')
def CreateSolidBrush(e, c):
    return e.new_gdi('brush', color=c)


@api(2, 'w')
def CreatePatternBrush(e, h):
    b = e.bitmap(h)
    pat = [b['px'][(y % b['h']) * b['w'] + x % b['w']] for y in range(8) for x in range(8)] if b else None
    return e.new_gdi('brush', color=0, pattern=pat, mono=bool(b and b['mono']))


@api(8, 'wwl')
def CreatePen(e, style, width, c):
    return e.new_gdi('pen', color=c, null=style == 5)


@api(6, 'www')
def MoveTo(e, dc, x, y):
    d = e.obj(dc, 'dc')
    old = d['pos']
    d['pos'] = (s16(x), s16(y))
    return (old[0] & 0xffff) | (old[1] & 0xffff) << 16


def put(e, d, x, y, v):
    b = e.bitmap(d['bmp'])
    if b and 0 <= x < b['w'] and 0 <= y < b['h']:
        b['px'][y * b['w'] + x] = v


@api(6, 'www')
def LineTo(e, dc, x, y):
    d = e.obj(dc, 'dc')
    x1, y1 = s16(x), s16(y)
    x0, y0 = d['pos']
    d['pos'] = (x1, y1)
    return line(e, d, x0, y0, x1, y1)


def line(e, d, x0, y0, x1, y1):
    """port/src/win/draw.c line(): Bresenham, end point left out."""
    p = e.gdi.get(d['pen'])
    if not p or p.get('null'):
        return 1
    v = pixel_of(e, d, p['color'])
    dx, dy = abs(x1 - x0), -abs(y1 - y0)
    stx, sty = (1 if x0 < x1 else -1), (1 if y0 < y1 else -1)
    err = dx + dy
    while x0 != x1 or y0 != y1:
        e2 = 2 * err
        put(e, d, x0, y0, v)
        if e2 >= dy:
            err += dy
            x0 += stx
        if e2 <= dx:
            err += dx
            y0 += sty
    return 1


@api(10, 'wwwl')
def SetPixel(e, dc, x, y, c):
    d = e.obj(dc, 'dc')
    put(e, d, s16(x), s16(y), pixel_of(e, d, c))
    return c


@api(6, 'wl')
def SetTextColor(e, dc, c):
    d = e.obj(dc, 'dc')
    old, d['text'] = d['text'], c
    return old


@api(4, 'ww')
def SetBkMode(e, dc, m):
    d = e.obj(dc, 'dc')
    old, d['bkmode'] = d.get('bkmode', 2), m
    return old


@api(4, 'ww')
def SetTextAlign(e, dc, a):
    d = e.obj(dc, 'dc')
    old, d['align'] = d.get('align', 0), a
    return old


@api(20, 'wwwwwwwwl')
def BitBlt(e, dst, x, y, w, h, src, sx, sy, rop):
    return blit(e, dst, x, y, w, h, src, sx, sy, w, h, rop)


@api(24, 'wwwwwwwwwwl')
def StretchBlt(e, dst, x, y, w, h, src, sx, sy, sw, sh, rop):
    return blit(e, dst, x, y, w, h, src, sx, sy, sw, sh, rop)


@api(12, 'lwwww')
def SetRect(e, fp, l, t, r, b):
    e.uc.mem_write(e.lin(fp), struct.pack('<4H', l, t, r, b))


@api(30, 'wwwwwbbbbbbbbl'.replace('b', 'w'))
def CreateFont(e, h, w, esc, orient, weight, italic, underline, strike, charset, out, clip, quality,
               pitch, face):
    return e.new_gdi('font', height=s16(h), width=s16(w), weight=weight, italic=italic & 0xff,
                     face=e.cstr(e.lin(face)))


@api(12, 'wwwlw')
def TextOut(e, dc, x, y, fp, n):
    """Recorded, not drawn (text is rasterised by the port's text.c)."""
    d = e.obj(dc, 'dc')
    e.texts.append(dict(x=s16(x), y=s16(y), text=e.rd(e.lin(fp), n).decode('latin-1'),
                        font=dict(e.gdi.get(d.get('font'), {})), color=d['text'], bk=d['bk'],
                        bkmode=d.get('bkmode', 2), align=d.get('align', 0)))
    return 1


# MMSYSTEM sound: the volumes are kept (the oracle compares the wave
# device's), sounds are not played.
@api(6, 'wl')
def waveOutGetVolume(e, dev, fp):
    e.uc.mem_write(e.lin(fp), struct.pack('<I', e.wave_volume))
    return 0


@api(6, 'wl')
def waveOutSetVolume(e, dev, v):
    e.wave_volume = v
    return 0


@api(6, 'wl')
def midiOutGetVolume(e, dev, fp):
    e.uc.mem_write(e.lin(fp), struct.pack('<I', e.midi_volume))
    return 0


@api(6, 'wl')
def midiOutSetVolume(e, dev, v):
    e.midi_volume = v
    return 0


@api(8, 'wlw')
def midiOutGetDevCaps(e, dev, fp, size):
    e.uc.mem_write(e.lin(fp), bytes(size))
    return 0


@api(6, 'lw')
def sndPlaySound(e, fp, flags):
    return 1


# USER: the sound's hidden window
@api(4, 'l')
def RegisterClass(e, fp):
    return 1


@api(6, 'wl')
def LoadCursor(e, inst, name):
    return 1


@api(30, 'lllwwwwwwwl')
def CreateWindow(e, cls, title, style, x, y, w, h, parent, menu, inst, param):
    return 0x500


@api(2, 'w')
def DestroyWindow(e, h):
    return 1


@api(6, 'lw')
def UnregisterClass(e, name, inst):
    return 1


@api(12, 'wllw')
def MessageBox(e, h, text, title, style):
    return 1
