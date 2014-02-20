"""
Parse a DCMTK dict file and produce a flat file.
"""

import sys
import string
import re

r = re.compile(r'\(([^,]*),"([^"]*)",([^,]*)\)[ \t]*(..)[ \t]*([^ \t]*)[ \t]*(.*)')
s = r'(\1,00\3)\n\5\n\5\n\4\n\6\n\2\n'

for filename in sys.argv[1:]:
  f = open(filename)
  for line in f.readlines():
    l = line.strip()
    if line[0] == '(':
      g = re.sub(r,r'\1',l)
      if len(g) > 4:
        g0 = int(g[0:4],16)
        g1 = int(g[7:11],16)
        tail = re.sub(r,s[3:],l)
        for g in range(g0,g1+1,2):
          sys.stdout.write("(%04.4x" % (g,) + tail)
      else:
        sys.stdout.write(re.sub(r,s,l))
