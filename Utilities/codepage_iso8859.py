"""
Generate tables for converting ISO-8859 to Unicode.

The input arguments should be one or more text files from here:
http://www.unicode.org/Public/MAPPINGS/ISO8859/

The output (on stdout) will be a C-formatted table that gives the 96
special characters for each of the input tables, e.g. if the inputs are
  8859-2.TXT -3.TXT -4.TXT -5.TXT -6.TXT -7.TXT -8.TXT -9.TXT -11.TXT
then the output will be:

  { 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0 },
  { 0x0104, 0x0126, 0x0104, 0x0401, 0xFFFD, 0x2018, 0xFFFD, 0x00A1, 0x0E01 },
  { 0x02D8, 0x02D8, 0x0138, 0x0402, 0xFFFD, 0x2019, 0x00A2, 0x00A2, 0x0E02 },
  ... 96 rows in total

"""

import sys

encodings = sys.argv[1:]
n = len(encodings)

table = []
for i in range(256):
    row = [0xFFFD]*n
    table.append(row)

for i in range(n):
    e = encodings[i]
    f = open(e, "r")
    lines = f.readlines()
    f.close()
    for l in lines:
        if l and l[0] != '\n' and l[0] != '#':
            columns = l.strip().split()
            table[int(columns[0], 16)][i] = int(columns[1], 16)

for i in range(0xA0, 0x100):
    sys.stdout.write("  ")
    c = '{'
    for e in table[i]:
        sys.stdout.write("%s 0x%4.4X" % (c, e))
        c = ','
    sys.stdout.write(" },\n")
