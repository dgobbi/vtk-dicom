"""
Parse one of Dave Clunie's tpl files and generate a flat file.
"""

import sys
import string

blocks = {}

def parseline(line):
  if line[0] != '(':
    return
  entries = {}
  tag = line[0:11]
  i = 12
  while 1:
    try:
      while line[i] in string.whitespace:
        i = i + 1
    except IndexError:
      break
    j = i
    try:
      while line[j] != '=':
        j = j + 1
    except IndexError:
      break
    key = line[i:j]
    if line[j+1] != '\"':
      break
    i = j + 2
    j = i
    while line[j] != '\"':
      j = j + 1
    val = line[i:j]
    i = j + 1
    entries[key] = val.strip()

  try:
    entries['Name']
    entries['Keyword']
    entries['VR']
    entries['VM']
    entries['Owner']
  except KeyError:
    sys.stderr.write("Missing key: %s\n" % (line,))
    return

  try:
    block = blocks[entries['Owner']]
  except KeyError:
    block = {}
    blocks[entries['Owner']] = block

  block[tag] = entries

  #g = int(tag[1:5], 16)
  #e = int(tag[6:10], 16)

  #tag = "(%04x,%04x)" % (g,e)

for filename in sys.argv[1:]:
  f = open(filename)
  for line in f.readlines():
    parseline(line)

#print(len(blocks))

for owner, block in blocks.items():
  lines = []
  tags = block.keys()

  tags.sort()
  for tag in tags:
    entries = block[tag]
    lines.append(tag)
    lines.append(entries['Name'])
    lines.append(entries['Keyword'])
    lines.append(entries['VR'])
    lines.append(entries['VM'])
    lines.append(owner)

  for line in lines:
    print(line)
