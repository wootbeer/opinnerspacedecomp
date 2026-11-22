# Tools

Python 3. Run from the repo root; game files live in `data/` (git-ignored).

| Tool | What it does |
|---|---|
| `ne_info.py FILE` | NE header and segment table. |
| `optl_lz.py` | OPTLOADER LZ decoder (library), translated from the loader's routine at segment 1:0x31. |
| `optl_emu.py` | Runs that original routine under Unicorn (`pip install unicorn`); the reference `optl_lz.py` is checked against. |
| `optl_unpack.py IN OUT` | Rebuilds a packed NE file as a plain NE: unpacked segments, OPTLOADER relocation tails turned into NE relocation records, self-loading flag cleared. Original bytes are kept; new segments are appended. |
| `ne_relocs.py FILE [--list]` | Lists NE relocations and checks every chain. |

Unpack everything into the git-ignored `unpacked/`:

```
mkdir -p unpacked
for f in INSPACE.EXE ISPACE.DLL FACTORY.EXE BACKUP.EXE; do python3 tools/optl_unpack.py data/$f unpacked/$f; done
```

## OPTLOADER format (SLR Systems, 1993)

Segment 1 is the self-loader. It is identical in every packed file: 0x1e7
plain bytes (self-loading header + LZ decoder), then its own body as an LZ
stream that decodes in place after those bytes (matches can reach back into
them). Every other segment's file data is

```
WORD  nrelocs        total relocation entries in the tail (0 = no tail)
...   LZ stream      decodes to the segment, up to its alloc size; the loader zero-fills the rest
...   reloc tail     groups: WORD (kind | count << 8), then entries
```

LZ stream: 16-bit LE words read MSB first, refilled right after the 16th bit
is used; raw bytes come from the same input pointer.

```
1                      literal byte
0 0x                   length 2|x, distance = byte + 1 (<= 256)
0 10x / 0 110x         length 4|x / 6|x
0 1110xx / 0 11110xxx  length 8+xx / 12+xxx
0 11111 + byte         byte < 0x81: length; 0x81: no-op; > 0x81: end
then (except length 2) distance high byte:
  00 -> 0, 010 -> 1, 011x -> 2+x, 100xx -> 4+xx, 101xxx -> 8+xxx,
  1100xxxx -> 0x10+, 11010xxxx -> 0x20+, 110110xxxx -> 0x30+, 110111xxxxxx -> 0x40+
then the distance low byte; distance = (high << 8 | low) + 1
```

Relocation kinds: `0xF0` = selector chains (BYTE seg, WORD head). Otherwise
bits 0-2 = patch (0 byte, 1 selector, 2 far pointer, 3 offset; +4 additive,
else chained as in NE), bits 3-4 = target (0 internal: BYTE seg, 0xFF =
movable entry ordinal; 1 import ordinal and 2 import name: WORD module;
3 OS fixup: WORD type), then entries (WORD offset, WORD value; OS fixups
WORD offset only).

Verified: `optl_lz.py` matches the original routine byte for byte on all 21
streams of FACTORY.EXE, BACKUP.EXE and ISPACE.DLL; every tail parses
exactly; every chain ends in 0xFFFF inside its segment; all but one far
pointer fixup per file sit right after a `call far` (9A) opcode.
