"""
Generate tables for converting ISO-2022 multi-byte CJK to Unicode

The input arguments should be one of the text files from here:
http://source.icu-project.org/repos/icu/data/trunk/charset/data/ucm/
Alternatively, the original (and obsolete) unicode files for cjk:
http://www.unicode.org/Public/MAPPINGS/OBSOLETE/EASTASIA/

iso-2022-ir-87  java-ISO2022JP-1.3_P.ucm (old: JIS0208.TXT)
iso-2022-ir-159 JIS0212.TXT
iso-2022-ir-149 java-ISO2022KR-1.3_P.ucm (old: KSX1001.TXT)

"""

import sys
import os.path

fname = sys.argv[1]

f = open(fname,'r')
lines = f.readlines();
f.close()

ext = os.path.splitext(fname)[1]

m = {}
if ext == ".ucm":
    for l in lines:
        if l[0:2] == "<U" and l[12:14] == "\\x":
            i = int(l[2:6],16)
            s = 0x21 ^ (int(l[10:12],16) & 0x80)
            j = (int(l[10:12],16)-s)*94+(int(l[14:16],16)-s)
            if m.has_key(j):
                sys.stderr.write("duplicate: %d 0x%4.4X 0x%4.4X\n" % (j,i,m[j]))
            else:
                m[j] = i
else:
    for l in lines:
        if l and l[0] != '\n' and l[0] != '#':
            columns = l.strip().split()
            if len(columns) > 1 and columns[1][0:2] in ('0x','0X'):
                c1 = int(columns[0], 16)
                c2 = int(columns[1], 16)
                if len(columns) > 2 and columns[2][0:2] in ('0x','0X'):
                    c1 = c2
                    c2 = int(columns[2], 16)
                s = 0x21 ^ (c1 & 0x80)
                c1 = ((c1 >> 8) - s)*94 + ((c1 & 0xff) - s)
                if m.has_key(c1):
                    sys.stderr.write("duplicate: %d 0x%4.4X 0x%4.4X\n" % (c1,c2,m[c1]))
                else:
                    m[c1] = c2

for k in range(94*94):
    u = 0xFFFD
    try:
        u = m[k]
    except KeyError:
        pass
    s = ' '
    if ((k+1) % 9 == 0):
        s = '\n'
    sys.stdout.write("0x%4.4X,%s" % (u,s))
