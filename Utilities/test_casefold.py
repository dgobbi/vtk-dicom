# =====
# This script takes the unicode CaseFolding.txt file as input,
# reports an error wherever vtkDICOMCharacterSet fails to match.
# =====

import sys

f = open(sys.argv[1], 'r')
from vtkDICOMPython import *
fold = vtkDICOMCharacterSet(13)

lasta = 0

for l in f.readlines():
    l = l.strip()
    if l == "" or l[0] == '#':
        continue
    a, t, b, c = l.split('; ')
    if t not in ('C', 'F'):
        continue
    a = int(a, 16)
    if a > 0xFFFF:
        break

    lasta = lasta + 1
    while lasta < a:
        s = unichr(lasta).encode('utf-8')
        if s:
            d = fold.CaseFoldedUTF8(s, len(s))
            if s != d:
                d = ord(d[0])
                sys.stdout.write("mismatch! 0x%04X 0x%04X\n" % (lasta,d));
        lasta = lasta + 1

    b = b.split(' ')
    r = None
    offset = 0
    mismatch = False
    s = unichr(a).encode('utf-8')
    if not s:
        sys.stderr.write("endoding error 0x%04X\n" % (a,))
    s = fold.CaseFoldedUTF8(s, len(s))
    if not s:
        sys.stderr.write("folding error 0x%04X\n" % (a,))
    s = s.decode('utf-8')
    if not s:
        sys.stderr.write("decoding error 0x%04X\n" % (a,))
    if len(b) == 1:
        b = int(b[0], 16)
        mismatch = (s != unichr(b))
        offset = b - a
    elif len(b) == 2:
        r = (int(b[0], 16), int(b[1], 16), 0)
        mismatch = (s != unichr(r[0]) + unichr(r[1]))
        b = 0
    elif len(b) == 3:
        r = (int(b[0], 16), int(b[1], 16), int(b[2], 16))
        mismatch = (s != unichr(r[0]) + unichr(r[1]) + unichr(r[2]))
        b = 0
    else:
        raise ValueError

    if mismatch:
        sys.stderr.write("mismatch! 0x%04X 0x%04X\n" % (a,b));
