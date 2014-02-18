"""
Parse one of Dave Clunie's tpl files and generate a flat file.
"""

import sys
import string

header = \
"""/*=========================================================================
This is an automatically generated file.  Do not edit.
=========================================================================*/"""
printheader = False
htsize = 16

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
    entries[key] = val

  try:
    block = blocks[entries['Owner']]
  except KeyError:
    block = {}
    blocks[entries['Owner']] = block

  block[tag] = entries

  #g = int(tag[1:5], 16)
  #e = int(tag[6:10], 16)

  #tag = "(%04x,%04x)" % (g,e)

def printhash(lines):
  # the tables that will be created
  enum_list = []
  element_list = []
  entry_list = []

  # a set to keep track of all VM strings encountered
  vms = {}

  # the hash table, in PYTHON
  ht = [None]*htsize

  # iterate through all elements in the table
  j = 0
  i = 0
  n = len(lines)
  while i < n:
    try:
      tag = lines[i].encode('ascii').strip()
      i = i + 1
      name = lines[i].encode('ascii').strip()
      i = i + 1
      key = lines[i].encode('ascii').strip()
      i = i + 1
      vr = lines[i].encode('ascii').strip()
      i = i + 1
      vm = lines[i].encode('ascii').strip()
      i = i + 1
      ret = lines[i].encode('ascii').strip()
      i = i + 1
    except:
      print "non-ascii character encounterd on line %d" % (i,)
      print lines[i]
      raise TypeError

    # replace "US or SS" with "XS"
    if vr == "US or SS" or vr == "SS or US":
      vr = "XS"

    # replace "OB or OW" with "OX"
    if vr == "OB or OW" or vr == "OW or OB":
      vr = "OX"

    # replace "see note" with "XX"
    if vr == "" or vr == "see note":
      vr = "XX"

    # replace mixed short with "OW"
    if len(vr) > 2:
      if vr.find("OW") >= 0:
        vr = "OW"
      if vr.find("OB") >= 0:
        vr = "OB"

    # replace 'RET' with 1 or 0
    if ret:
      ret = "1"
    else:
      ret = "0"

    # prefix vm with 'M', change '-' to 'T', change 'n' to 'N'
    vm = 'M' + vm.split(' ')[0].replace('-', 'T').replace('n', 'N')
    # add to the set of VMs
    vms[vm] = True

    # this is debug info: make sure no keys are over 63 chars,
    # which is the maximum id length in the C++ standard
    if len(key) > 63:
      print "XXXXXX", key
      sys.exit(1)

    # get the group, element
    g, e = tag[1:10].split(',')

    # make sure g, e are hexidecimal integers
    try:
      gi = int(g, 16)
      ei = int(e, 16)
    except:
      # replace 'x' (which means any digit) with zero
      #print "XXXXXX %s %s" % (tag, key)
      g = g.replace('x','0')
      e = e.replace('x','0')
      gi = int(g, 16)
      ei = int(e, 16)

    if key:
      enum_list.append(
        ("%-39s = 0x%s%s, // %s %-5s %s" % (key, g, e, vr, vm, ret)).strip())

      element_list.append(
        "{ 0x%s, 0x%s, %s, VR::%s, VM::%s, \"%s\" }," % (g, e, ret, vr, vm, name))

      # create a hash from group, element
      h = ((gi ^ (gi >> 6)) ^ (ei ^ (ei >> 6)))

      # build the hash table
      h = (h & (htsize - 1))
      if ht[h] == None:
        ht[h] = []

      # build the index table
      ht[h].append(j)
      j = j + 1

  # debug: print all VM's that were found
  #print vms.keys()

  # create the C++ text for the hash table
  maxl = 0
  minl = j
  k0 = 0
  k4 = 0
  k = 0
  for te in ht:
    if te == None:
      te = []
    l = len(te)
    if l == 0:
      k0 = k0 + 1
    if l > 3:
      k4 = k4 + 1
    maxl = max(maxl, l)
    minl = min(minl, l)
    s = ""
    for idx in te:
      s = s + element_list[idx] + "\n"
    s = s + "{ 0, 0, 0, 0, 0, NULL }"
    entry_list.append(s)
    k = k + len(te) + 1

  # debug: print statistics about the hash table
  #print maxl, minl, k0, k4

  # write the output file
  if printheader:
    print header
    print
    print "#ifndef __vtkDICOMDictHash_h"
    print "#define __vtkDICOMDictHash_h"
    print
    print "//! Tag values defined in the DICOM standard"
    print "namespace DC"
    print "{"
    print "enum EnumType {"
    for l in enum_list:
      print l
    print "};"
    print "} // end namespace DC"
    print
    print "#endif /* __vtkDICOMDictHash_h */"

  else:
    print header
    print
    print "#include \"vtkDICOMDictionary.h\""
    print

    print "namespace {"
    print
    print "typedef vtkDICOMVR VR;"
    print "typedef vtkDICOMVM VM;"
    print "typedef vtkDICOMDictEntry::Entry DictEntry;"
    print

    ct = 0
    for l in entry_list:
      print "DictEntry DictRow%04d[] = {" % (ct,)
      print l
      print "};"
      ct = ct + 1
    print
    print "}"
    print

    ct = 0
    print "DictEntry *vtkDICOMDictionary::DictHashTable[%d] = {" % (htsize,)
    for l in entry_list:
      print "DictRow%04d," % (ct,)
      ct = ct + 1
    print "};"


f = open(sys.argv[1])

for line in f.readlines():
  parseline(line)

#print len(blocks)

for owner, block in blocks.items():
  lines = []
  tags = block.keys()

  name = "SIEMENS"
  nlen = len(name)
  if owner[0:nlen] != name:
    continue
  #if len(tags) < 5:
  #  continue

  tags.sort()
  for tag in tags:
    entries = block[tag]
    lines.append(tag)
    lines.append(entries['Name'])
    lines.append(entries['Keyword'])
    lines.append(entries['VR'])
    lines.append(entries['VM'])
    lines.append("") # retired

  print "// =================", owner, "================="
  printhash(lines)
