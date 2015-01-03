# =====
# This script takes GB18030-BMP.TXT as an input and uses it to validate
# the decoding of the GB18030 by vtkDICOMCharacterSet. GB18030-BMP.TXT
# can be found in libiconv.
# ====

import sys
from vtkDICOMPython import *

fname = sys.argv[1]

gb = vtkDICOMCharacterSet("GB18030")
def g(x):
    return gb.ConvertToUTF8(x,len(x))

f = open(fname, "r")
l = f.readlines()

def u(x):
    if len(x) == 1:
        return ord(x)
    if len(x) == 2:
        return ((ord(x[0]) & 0x3F) << 6) | (ord(x[1]) & 0x7F)
    if len(x) == 3:
        return ((ord(x[0]) & 0x1F) << 12) | ((ord(x[1]) & 0x7F) << 6) | (ord(x[2]) & 0x7F)
    if len(x) == 4:
        return ((ord(x[0]) & 0x0F) << 18) | ((ord(x[1]) & 0x7F) << 12) | ((ord(x[2]) & 0x7F) << 6) | (ord(x[3]) & 0x7F)

def s(x):
    if x <= 0xFF:
        return chr(x)
    if x <= 0xFFFF:
        return chr((x >> 8) & 0xFF) + chr(x & 0xFF)
    return chr(x >> 24) + chr((x >> 16) & 0xFF) + chr((x >> 8) & 0xFF) + chr(x & 0xFF)

for i in l:
    x = i.split()
    a = int(x[0],16)
    b = int(x[1],16)
    c = u(g(s(a)))
    if c is None:
        c = (u(g(s(a))[0:3]) << 16) + u(g(s(a))[3:6])
    if b != c:
        print "mismatch", hex(a), hex(c), hex(b)
