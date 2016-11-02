"""
Generate tables for converting CP949 (Korean) to Unicode

The input arguments should be CP949.TXT
http://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/

"""

import sys
import os.path

fname = sys.argv[1]

f = open(fname,'r')
lines = f.readlines();
f.close()

m = {}
for l in lines:
    if l and l[0] != '\n' and l[0] != '#':
        columns = l.strip().split()
        if len(columns) > 1 and columns[1][0:2] in ('0x','0X'):
            c1 = int(columns[0], 16)
            c2 = int(columns[1], 16)
            a = (c1 >> 8) & 0xff
            b = c1 & 0xff
            c = 0
            if a == 0:
                continue
            if a >= 0x81 and a <= 0xa0:
                a -= 0x81
                if b >= 0x41 and b <= 0x5a:
                    b -= 0x41
                elif b >= 0x61 and b <= 0x7a:
                    b -= (0x61 - 26)
                elif b >= 0x81 and b <= 0xfe:
                    b -= (0x81 - 52)
                else:
                    sys.stderr.write("bad: 0x%4.4X\n" % (c1,))
                    continue
                c = a*178 + b
            elif a >= 0xa1 and a <= 0xc6:
                a -= 0xa1
                if b >= 0x41 and b <= 0x5a:
                    b -= 0x41
                elif b >= 0x61 and b <= 0x7a:
                    b -= (0x61 - 26)
                elif b >= 0x81 and b <= 0xa0:
                    b -= (0x81 - 52)
                elif b >= 0xa1 and b <= 0xfe:
                    continue
                else:
                    sys.stderr.write("bad: 0x%4.4X\n" % (c1,))
                    continue
                c = a*84 + b + 5696
            else:
               continue

            if m.has_key(c):
                sys.stderr.write("duplicate: %d 0x%4.4X 0x%4.4X\n" % (c1,c2,m[c1]))
            else:
                m[c] = c2

for k in range(8822):
    u = m[k]
    s = ' '
    if ((k+1) % 9 == 0):
        s = '\n'
    sys.stdout.write("0x%4.4X,%s" % (u,s))
sys.stdout.write("\n")
