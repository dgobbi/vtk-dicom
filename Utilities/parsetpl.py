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
  entries['Tag'] = tag
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
    try:
      while line[j] != '\"':
        j = j + 1
    except:
      sys.stderr.write(line)
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

  try:
    # check whether the tag is already defined
    oldentries = block[tag.lower()]
    # overwrite unless new definition has no keyword
    if entries['Keyword'] and entries['Keyword'] != "?":
      block[tag.lower()] = entries
    # print any duplicate private tags to stderr
    sys.stderr.write("Dup \"" + entries['Owner'] + "\" " +
      tag.lower() + " " +
      oldentries['VR'] + "/" + entries['VR'] + " " +
      oldentries['VM'] + "/" + entries['VM'] + " " +
      "\"" + oldentries['Keyword'] + "\"/\"" + entries['Keyword'] + "\"\n")
  except KeyError:
    block[tag.lower()] = entries

for filename in sys.argv[1:]:
  f = open(filename)
  for line in f.readlines():
    parseline(line)

#print(len(blocks))

for owner in sorted(blocks.keys()):
  block = blocks[owner]
  lines = []

  for tag in sorted(block.keys()):
    entries = block[tag]
    lines.append(entries['Tag'])
    lines.append(entries['Name'])
    lines.append(entries['Keyword'])
    lines.append(entries['VR'])
    lines.append(entries['VM'])
    lines.append(owner)

  for line in lines:
    print(line)
