"""
Generate tables for converting GB18030 multi-byte to Unicode

The input arguments should be the gb-18030-2005.ucm file from here:
http://source.icu-project.org/repos/icu/data/trunk/charset/data/ucm/

Two tables must be generated.  One for the 24066 two-byte codes, and
another for the four-byte codes.

"""

import sys
import os.path

fname = sys.argv[1]

f = open(fname,'r')
lines = f.readlines();
f.close()

m2 = {}
m4 = {}
for l in lines:
    l = l.strip()
    if l[0:2] == "<U" and l[6] == ">":
        u = int(l[2:6],16)
    elif l[0:2] == "<U" and l[7] == ">":
        u = int(l[2:7],16)
        l = l[1:]
    else:
        continue

    if l[12:14] != "\\x":
        # one-byte code is identical to ASCII
        continue
    elif l[16:18] != "\\x":
        # two-byte code
        a = int(l[10:12],16)
        b = int(l[14:16],16)
        if b > 0x7f:
            b -= 1
        g = (a - 0x81)*190 + (b - 0x40)
        m = m2
    else:
        # four-byte code
        a = int(l[10:12],16)
        b = int(l[14:16],16)
        c = int(l[18:20],16)
        d = int(l[22:24],16)
        aa = (a - 0x81)*10 + (b - 0x30)
        bb = (c - 0x81)*10 + (d - 0x30)
        g = aa*1260 + bb
        m = m4
    if m.has_key(g):
        if m[g] > 0xFFFF and u <= 0xFFFF:
            # attempt to stay on BMP
            m[g] = u
        elif l[-1] == '0' and u <= 0xFFFF:
            # prefer the primary over the fallback
            m[g] = u
        #sys.stderr.write("duplicate: %d 0x%04X 0x%04X\n" % (g,u,m[g]))
    else:
        m[g] = u

for k in range(0,23940):
    u = 0xFFFD
    try:
        u = m2[k]
    except KeyError:
        pass
    if u > 0xFFFF:
        sys.stderr.write("too large! 0x%04X\n" % (u,))
        u = 0xFFFD
    elif u >= 0xE000 and u <= 0xF8FF:
        # these are for character not yet in the unicode standard
        #sys.stderr.write("private! 0x%04X\n" % (u,))
        pass
    s = ' '
    if ((k+1) % 9 == 0):
        s = '\n'
    sys.stdout.write("0x%04X,%s" % (u,s))

sys.stdout.write("=======================================\n")
lastu = -10
i = 0
n = max(m4.keys())+1
for k in range(n):
    u = 0xFFFD
    try:
        u = m4[k]
    except KeyError:
        pass
    run = False
    if u == lastu+1 or (u == 0xFFFD and lastu == 0xFFFD):
        run = True
    if k == n-1:
        run = False
    lastu = u
    if not run:
        i = i + 1
        s = ' '
        if (i % 8 == 0):
            s = '\n'
        sys.stdout.write("0x%04X,%s" % (k,s))
        i = i + 1
        s = '  '
        if (i % 8 == 0):
            s = '\n'
        sys.stdout.write("0x%04X,%s" % (u,s))
