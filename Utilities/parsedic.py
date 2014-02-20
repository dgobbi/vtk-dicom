"""
Parse a DCMTK dict file and produce a flat file.
"""

import sys
import string
import re

r = re.compile(r'\(([^,]*),"([^"]*)",([^,]*)\)[ \t]*(..)[ \t]*([^ \t]*)[ \t]*([^ \t\r\n]*)')
s = r'(\1,00\3)\n\5\n\5\n\4\n\6\n\2'

for filename in sys.argv[1:]:
  f = open(filename)
  for line in f.readlines():
    if line[0] == '(':
      sys.stdout.write(re.sub(r,s,line))
