"""
Generate a C++ DICOM dictionary from a text file.

This program will read a text file generated from the DICOM data
element regsistry table (DICOM Chapter 6 part 6) and will generate
a hash table that can be used for dictionary lookups.

Usage: python makedict.py nemadict.txt > vtkDICOMDictHash.cxx
Usage: python makedict.py --header nemadict.txt > vtkDICOMDictHash.h

The option "--private" can be added to create a private dictionary.
"""

import sys
import math

header = \
"""/*=========================================================================
This is an automatically generated file.  Include errata for any changes.
=========================================================================*/"""

printheader = False
privatedict = False
filename = None
for arg in sys.argv[1:]:
  if arg == "--header":
    printheader = True
  elif arg[0:10] == "--private=":
    privatedict = arg[10:]
  elif arg[0] != '-' and filename == None:
    filename = arg
  else:
    sys.stderr.write(
      """usage: python makedict.py nemadict.txt > vtkDICOMDictHash.cxx
      python makedict.py --header nemadict.txt > vtkDICOMDictHash.h\n""")
    sys.exit(1)

# the hash table, in PYTHON
if privatedict:
  htsize = 16
else:
  htsize = 1024

# read the file in one go
f = open(filename, 'r')
lines = f.readlines()
f.close()

# collect private dictionaries
privatelines = {}

# look for repeating groups and repeat them
i = 0
rg = []
while i < len(lines):
  tag = lines[i].strip()
  g, e = tag[1:10].split(',')
  if g == "60xx" or g == "50xx":
    rg.extend(lines[i:i+6])
    i = i + 6
  elif rg:
    nb = []
    for j in range(1,16):
      k = 0
      m = len(rg)
      while k < m:
        g, e = rg[k][1:10].split(',')
        nb.append("(%s%02X,%s)\n" % (g[0:2], 2*j, e))
        nb.append("%s %d\n" % (rg[k+1].strip(), j+1))
        nb.append("%s%d\n" % (rg[k+2].strip(), j+1))
        nb.append(rg[k+3])
        nb.append(rg[k+4])
        nb.append(rg[k+5])
        k = k + 6
    lines = lines[0:i] + nb + lines[i:]
    i += 16*len(rg)
    rg = []
  else:
    # check for and filter out the private tags
    private = False
    try:
      private = ((int(g[3]) & 0x1) != 0)
    except:
      pass
    if private:
      creator = lines[i + 5].strip()
      try:
        privatelines[creator] += lines[i:i+6]
      except KeyError:
        privatelines[creator] = lines[i:i+6]
    i = i + 6

def makedict(lines):
  # the tables that will be created
  enum_list = []
  element_list = []
  entry_list = []

  # a set to keep track of all VM strings encountered
  vms = {}

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
      print "non-ascii character encountered on line %d" % (i,)
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
    if ret and not privatedict:
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
      h = (h & (htsize-1))
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
  return enum_list, entry_list

# write the output file
def printhead(enum_dict, classname):
  print header
  print
  print "#ifndef __%s_h" % (classname,)
  print "#define __%s_h" % (classname,)
  print
  if not privatedict:
    print "//! Tag values defined in the DICOM standard"
    print "namespace DC"
    print "{"
    print "enum EnumType {"
    for enum_list in enum_dict.values():
      for l in enum_list:
        print l
    print "};"
    print "} // end namespace DC"
  else:
    print "// Initializer to add dict when header included."
    print "struct %sInitializer" % (classname,)
    print "{"
    print "  %sInitializer();" % (classname,)
    print "  ~%sInitializer();" % (classname,)
    print "};"
    print
    print "static %sInitializer %sInitializerInstance;" % (classname,classname);
  print
  print "#endif /* __%s_h */" % (classname,)

def printbody(entry_dict, classname):
  print header
  print
  print "#include \"vtkDICOMDictionary.h\""
  print "#include \"%s.h\"" % (classname,)
  print

  print "namespace {"
  print
  print "typedef vtkDICOMVR VR;"
  print "typedef vtkDICOMVM VM;"
  print "typedef vtkDICOMDictEntry::Entry DictEntry;"
  print

  ct = 0
  dn = 0
  for name, entry_list in entry_dict.items():
    dn = dn + 1
    ds = ""
    if len(entry_dict) > 1:
      ds = "%02d" % (dn,)
    for l in entry_list:
      print "DictEntry Dict%sRow%0*d[] = {" % (ds,int(math.log10(htsize)+1),ct)
      print l
      print "};"
      ct = ct + 1
  print
  ns = ""
  if not privatedict:
    print "}"
    ns = "vtkDICOMDictionary::"

  ct = 0
  dn = 0
  for name, entry_list in entry_dict.items():
    dn = dn + 1
    ds = ""
    if len(entry_dict) > 1:
      ds = "%02d" % (dn,)
    print
    print "DictEntry *%sDict%sHashTable[%d] = {" % (ns,ds,htsize)
    for l in entry_list:
      print "Dict%sRow%0*d," % (ds,int(math.log10(htsize)+1),ct)
      ct = ct + 1
    print "};"

  if privatedict:
    print
    print "} // end anonymous namespace"
    print
    print "static int %sInitializerCounter;" % (classname,)
    print
    print "%sInitializer::%sInitializer()" % (classname,classname)
    print "{"
    print "  if (%sInitializerCounter++ == 0)" % (classname,)
    print "    {"
    dn = 0
    for name, entry_list in entry_dict.items():
      dn = dn + 1
      ds = ""
      if len(entry_dict) > 1:
        ds = "%02d" % (dn,)
      print "    vtkDICOMDictionary::AddPrivateDictionary("
      print "       \"%s\", Dict%sHashTable);" % (name,ds)
    print "    }"
    print "}"
    print
    print "%sInitializer::~%sInitializer()" % (classname,classname)
    print "{"
    print "  --%sInitializerCounter;" % (classname,)
    print "}"

if privatedict:
  enum_dict = {}
  entry_dict = {}

  for name, lines in privatelines.items():
    enum_list, entry_list = makedict(lines)
    enum_dict[name] = enum_list
    entry_dict[name] = entry_list

  if printheader:
    printhead(enum_dict, privatedict)
  else:
    printbody(entry_dict, privatedict)

else:
  enum_list, entry_list = makedict(lines)

  classname = "vtkDICOMDictHash"

  if printheader:
    printhead({"DICOM" : enum_list}, classname)
  else:
    printbody({"DICOM" : entry_list}, classname)

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
