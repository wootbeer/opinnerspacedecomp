#!/usr/bin/env python3
"""Writes an oracle script for 5:0000, the dialogs' ship picture
(pseudo-ordinal 1000): the palette set-up of smooth.txt, then every ship
of the user's SHIPS/MASTER.SHP as the New Game dialog shows it (mode 0),
every tenth also in modes 1 and 2.  The ships' numbers come from the
game's files, so the script is made, not kept.

usage: ships.py OUT [--data DIR]"""
import argparse
import os
import struct

HERE = os.path.dirname(os.path.abspath(__file__))
SHIP, BODY = 0x41, 0x2c


def signed(b):
    return b - 256 if b > 127 else b


def main():
    ap = argparse.ArgumentParser(usage=__doc__)
    ap.add_argument('out')
    ap.add_argument('--data', default=os.path.join(HERE, '..', '..', 'data'))
    a = ap.parse_args()
    ships = open(os.path.join(a.data, 'SHIPS', 'MASTER.SHP'), 'rb').read()
    bodies = open(os.path.join(a.data, 'SHIPS', 'MASTER.BOD'), 'rb').read()
    setup = [line for line in open(os.path.join(HERE, 'smooth.txt')).read().splitlines()
             if line and not line.startswith(('#', '12 '))]
    out = ['# made by ships.py'] + setup
    for i in range(len(ships) // SHIP):
        r = ships[i * SHIP:(i + 1) * SHIP]
        if not r[0xa]:
            continue
        body = struct.unpack_from('<h', r, 0x21)[0]
        image = struct.unpack_from('<h', bodies, body * BODY + 0x21)[0]
        for mode in [0] + ([1, 2] if i % 10 == 0 else []):
            out.append('1000 @4 %d "" %d %d %d' % (image, signed(r[7]), signed(r[8]), mode))
    open(a.out, 'w').write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
