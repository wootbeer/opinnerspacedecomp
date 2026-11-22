#!/usr/bin/env python3
"""Read an OMF object's segments, externs, publics and fixups.
(Parser by the segment 16/17 helper, from its fixchk.py.)

parse(obj_path) -> (segs, exts, pubs, fixes)
  segs  [[name, bytearray]]          by SEGDEF index - 1
  exts  ['', name, ...]              EXTDEF/LEXTDEF names by index
  pubs  [(name, seg index, offset)]
  fixes [(seg index, offset, location type, target method, target index,
          displacement, segment-relative)]   target method 2 = extern,
          0 = segment, 1 = group; segment-relative False = self-relative
          (near call/jump)
"""
import struct

from omf_match import _index


def parse(obj):
    b = open(obj, 'rb').read()
    p = 0; lnames = ['']; segs = []; exts = ['']; pubs = []; last = None; fixes = []
    threads = {}
    while p < len(b):
        rt = b[p]; rl = struct.unpack_from('<H', b, p+1)[0]; body = b[p+3:p+3+rl-1]; p += 3+rl
        if rt == 0x96:
            q = 0
            while q < len(body):
                lnames.append(body[q+1:q+1+body[q]].decode('latin-1')); q += 1+body[q]
        elif rt in (0x98, 0x99):
            q = 1
            if body[0] >> 5 == 0: q += 3
            size = struct.unpack_from('<H', body, q)[0]; q += 2
            ni, q = _index(body, q)
            segs.append([lnames[ni], bytearray(size)])
        elif rt in (0x8c, 0xb4):
            q = 0
            while q < len(body):
                exts.append(body[q+1:q+1+body[q]].decode('latin-1')); q += 1+body[q]
                _, q = _index(body, q)
        elif rt in (0x90, 0x91):
            q = 0
            gi, q = _index(body, q); si, q = _index(body, q)
            if gi == 0 and si == 0: q += 2
            while q < len(body):
                n = body[q+1:q+1+body[q]].decode('latin-1'); q += 1+body[q]
                off = struct.unpack_from('<H', body, q)[0]; q += 2
                _, q = _index(body, q)
                pubs.append((n, si, off))
        elif rt in (0xa0, 0xa1):
            si, q = _index(body, 0)
            off = struct.unpack_from('<H', body, q)[0]; q += 2
            segs[si-1][1][off:off+len(body)-q] = body[q:]
            last = (si, off)
        elif rt in (0x9c, 0x9d):
            q = 0
            while q < len(body):
                b0 = body[q]
                if not b0 & 0x80:
                    method = (b0 >> 2) & 7; num = b0 & 3; isframe = b0 & 0x40
                    q += 1; idx = None
                    if isframe:
                        if method < 3: idx, q = _index(body, q)
                    else:
                        method &= 3
                        if method < 3: idx, q = _index(body, q)
                        elif method == 3: q += 2
                        threads[num] = (method, idx)
                    continue
                locat = (b0 << 8) | body[q+1]; q += 2
                loc = (locat >> 10) & 0xf; doff = locat & 0x3ff
                fix = body[q]; q += 1
                if not fix & 0x80:
                    fm = (fix >> 4) & 7
                    if fm < 3: _, q = _index(body, q)
                if fix & 0x08:
                    tm, tidx = threads[fix & 3]
                else:
                    tm = fix & 3; tidx = None
                    if tm < 3: tidx, q = _index(body, q)
                    else: q += 2
                disp = 0
                if not fix & 0x04:
                    disp = struct.unpack_from('<H', body, q)[0]; q += 2
                fixes.append((last[0], last[1] + doff, loc, tm, tidx, disp, bool(locat & 0x4000)))
    return segs, exts, pubs, fixes

