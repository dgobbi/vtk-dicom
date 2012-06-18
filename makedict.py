"""
Generate a C++ DICOM dictionary from a text file.

This program will read a text file generated from the DICOM data
element regsistry table (DICOM Chapter 6 part 6) and will generate
a hash table that can be used for dictionary lookups.

Usage: python makedict.py nemadict.txt > vtkDICOMMetaDataDict.cxx"

"""

import sys

if len(sys.argv) != 2:
  print "usage: python makedict.py nemadict.txt > vtkDICOMMetaDataDict.cxx"
  sys.exit(1)

# read the file in one go
f = open(sys.argv[1], 'r')
lines = f.readlines()
f.close()

# the tables that will be created
enum_list = []
element_list = []
entry_list = []

# a set to keep track of all VM strings encountered
vms = {}

# the hash table, in PYTHON
htsize = 1024
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
    raise TypeError

  # replace "US or SS" with "XS"
  if vr == "US or SS":
    vr = "XS"

  # replace "OB or OW" with "OX"
  if vr == "OB or OW":
    vr = "OX"

  # replace mixed short with "OW"
  if len(vr) > 2:
    if vr.find("OW"):
      vr = "OW"
    if vr.find("OB"):
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
      "{ 0x%s, 0x%s, VR::%s, VM::%s, \"%s\" }," % (g, e, vr, vm, name))

    # create a hash from group, element
    h = ((gi ^ (gi >> 6)) ^ (ei ^ (ei >> 6)))

    # build the hash table
    h = (h & 0x3ff)
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
  s = s + "{ 0, 0, 0, 0, 0 }"
  entry_list.append(s)
  k = k + len(te) + 1

# debug: print statistics about the hash table
#print maxl, minl, k0, k4

# write the output file
print "#include \"vtkDICOMMetaData.h\""
print

print "namespace {"
print

ct = 0
for l in entry_list:
  print "vtkDICOMMetaData::DictElement DictRow%04d[] = {" % (ct,)
  print l
  print "};"
  ct = ct + 1
print
print "}"
print

ct = 0
print "vtkDICOMMetaData::DictElement *vtkDICOMMetaData::DictHashTable[1024] = {"
for l in entry_list:
  print "DictRow%04d," % (ct,)
  ct = ct + 1
print "};"
print

"""
for l in enum_list:
  print l
"""

# informative: these names represent a range of tag values
""" keys with ranges
(0020,3100 to 31FF) SourceImageIDs
(0028,04x0) RowsForNthOrderCoefficients
(0028,04x1) ColumnsForNthOrderCoefficients
(0028,04x2) CoefficientCoding
(0028,04x3) CoefficientCodingPointers
(0028,08x0) CodeLabel
(0028,08x2) NumberOfTables
(0028,08x3) CodeTableLocation
(0028,08x4) BitsForCodeWord
(0028,08x8) ImageDataLocation
(1000,xxx0) EscapeTriplet
(1000,xxx1) RunLengthTriplet
(1000,xxx2) HuffmanTableSize
(1000,xxx3) HuffmanTableTriplet
(1000,xxx4) ShiftTableSize
(1000,xxx5) ShiftTableTriplet
(1010,xxxx) ZonalMap
"""
