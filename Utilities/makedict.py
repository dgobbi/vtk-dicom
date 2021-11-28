"""
Generate a C++ DICOM dictionary from a text file.

This program will read a text file generated from the DICOM data
element regsistry table (DICOM Chapter 6 part 6) and will generate
a hash table that can be used for dictionary lookups.

Usage: python makedict.py nemadict.txt > vtkDICOMDictHash.cxx
Usage: python makedict.py --header nemadict.txt > vtkDICOMDictHash.h

The option "--private=name" can be added to create a private dictionary,
or "--private=vtkDICOMDictPrivate" for all default dictionaries.
"""

import sys
import math

header = \
"""/*=========================================================================
This is an automatically generated file.  Include errata for any changes.
=========================================================================*/
"""

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
DICT_HASH_TABLE_SIZE = 4096

# whether to show individual hash rows in output
VISUALIZE_HASH_ROWS = False

# collect private dictionaries
privatelines = {}

# read the file in one go
f = open(filename, 'r')
lines = f.readlines()
f.close()

# look for repeating groups and repeat them
i = 0
rg = []
while i < len(lines):
  tag = lines[i].strip()
  try:
    g, e = tag[1:10].split(',')
  except ValueError:
    sys.stderr.write("exception: %s\n" % (tag))
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
    i += len(nb)
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

def hashtag(g, e):
  """Compute a hash from (group, element).
  This was found by trial-and-error.
  """
  k = (g << 16) + e
  h = (k >> 15) + k
  h = h + (h >> 6) + (h >> 12)
  return (h & 0xffffffff)

def hashstring(s):
  """Compute a string hash based on the function "djb2".
  Use at most 64 characters.
  """
  h = 5381
  s = s[0:64]
  for c in s:
    h = ((h << 5) + h + ord(c)) & 0xffffffff
  return h

def hashstats(ht):
  """Return statistics for hash table, as a tuple:
  (used bucket fraction, average linear search, total bytes used)
  """
  m = len(ht)
  f = m
  d = m
  c = 0
  for l in ht:
    if l == None:
      f = f - 1
    else:
      d = d + len(l) + 1
      c = c + len(l)//2
  return (f/m, c/f, 2*(d + 1))

def makedict(lines, creator="DICOM"):
  # the tables that will be created
  enum_list = []
  element_list = []
  entry_list = []

  # a set to keep track of all VM strings encountered
  vms = {}

  htsize = DICT_HASH_TABLE_SIZE
  if privatedict:
    htsize = int(len(lines)//6)
    if htsize == 0:
      htsize = 1

  ht = [None]*htsize
  ht2 = [None]*htsize

  # iterate through all elements in the table
  j = 0
  i = 0
  n = len(lines)
  while i < n:
    try:
      tag = lines[i].encode('ascii').strip().decode('ascii')
      i = i + 1
      name = lines[i].encode('ascii').strip().decode('ascii')
      i = i + 1
      key = lines[i].encode('ascii').strip().decode('ascii')
      i = i + 1
      vr = lines[i].encode('ascii').strip().decode('ascii')
      i = i + 1
      vm = lines[i].encode('ascii').strip().decode('ascii')
      i = i + 1
      ret = lines[i].encode('ascii').strip().decode('ascii')
      i = i + 1
    except:
      sys.stderr.write("non-ascii character encountered on line %d\n" % (i,))
      raise TypeError

    # replace "Unknown" and "?" with ""
    if name in ("Unknown", "Internal", "?"):
      name = ""
    if key in ("Unknown", "Internal", "?"):
      key = ""

    # replace "US or SS" with "XS"
    if vr in ("US or SS", "SS or US", "xs"):
      vr = "XS"

    # replace "OB or OW" with "OX"
    if vr in ("OB or OW", "OW or OB", "ox"):
      vr = "OX"

    # replace "see note" with "XX"
    if vr in ("", "see note", "See Note"):
      vr = "XX"

    # replace mixed short with "OW"
    if len(vr) > 2:
      if vr.find("OW") >= 0:
        vr = "OW"
        vm = "1"
      if vr.find("OB") >= 0:
        vr = "OB"
        vm = "1"

    # replace 'RET' with 1 or 0
    if ret and not privatedict:
      if not printheader:
        ret = {"RET":"1","DICONDE":"2","DICOS":"3"}[ret]
      elif ret == "RET":
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
      print("XXXXXX %s" % (key,))
      sys.exit(1)

    # get the group, element
    g, e = tag[1:10].split(',')

    # make sure g, e are hexadecimal integers
    try:
      gi = int(g, 16)
      ei = int(e, 16)
    except:
      # replace 'x' (which means any digit) with zero
      #print("XXXXXX %s %s" % (tag, key))
      g = g.replace('xx','00')
      e = e.replace('xxxx','0000')
      e = e.replace('xxx','000')
      e = e.replace('xx','00')
      e = e.replace('x','1')
      gi = int(g, 16)
      ei = int(e, 16)

    if key or privatedict:
      enum_list.append(
        ("%-39s = 0x%s%s, // %s %-5s %s" % (key, g, e, vr, vm, ret)).strip())

      element_list.append(
        "{ 0x%s, 0x%s, %s, VR::%s, VM::%s, \"%s\" }," % (g, e, ret, vr, vm, key))

      # create a hash from group, element
      h = hashtag(gi, ei)

      # create a string hash
      hkey = hashstring(key)

      # build the hash tables
      h = (h % htsize)
      if ht[h] == None:
        ht[h] = []
      h2 = (hkey % htsize)
      if ht2[h2] == None:
        ht2[h2] = []

      # build the index table
      ht[h].append(j)
      ht[h].append(ei)

      ht2[h2].append(j)
      ht2[h2].append((hkey//htsize) & 0xffff)
      j = j + 1

  # debug: print all VM's that were found
  #print(vms.keys())

  # debug: print statistics about the hash table
  if not privatedict:
    sys.stderr.write("Hash Stat: buckets used, items per bucket, total bytes\n")
    sys.stderr.write("Tag Table: %f, %f, %d\n" % hashstats(ht))
    sys.stderr.write("Key Table: %f, %f, %d\n" % hashstats(ht2))

  return enum_list, element_list, ht, ht2

# write the output file
def printhead(enum_dict, classname):
  f = sys.stdout
  f.write(header)
  f.write("\n")
  f.write("#ifndef %s_h\n" % (classname,))
  f.write("#define %s_h\n" % (classname,))
  f.write("\n")
  if not privatedict:
    f.write("//! Tag values defined in the DICOM standard\n")
    f.write("namespace DC\n")
    f.write("{\n")
    f.write("enum EnumType {\n")
    for enum_list in enum_dict.values():
      # eliminate the "," for the last enum item
      m = len(enum_list)
      if m:
        enum_list[m-1] = enum_list[m-1].replace(", //", "  //")
      for l in enum_list:
        f.write(l + "\n")
    f.write("};\n")
    f.write("} // end namespace DC\n")
  else:
    f.write("// This must be included before the initializer is declared.\n")
    f.write("#include \"vtkDICOMDictionary.h\"\n")
    f.write("\n")
    f.write("// Initializer to add dict when header included.\n")
    f.write("struct VTK_DICOM_EXPORT %sInitializer\n" % (classname,))
    f.write("{\n")
    f.write("  %sInitializer();\n" % (classname,))
    f.write("  ~%sInitializer();\n" % (classname,))
    f.write("};\n")
    f.write("\n")
    f.write("static %sInitializer %sInitializerInstance;\n" % (classname,classname))
  f.write("\n")
  f.write("#endif /* %s_h */\n" % (classname,))

def printbody(entry_dict, classname):
  f = sys.stdout
  f.write(header)
  f.write("\n")
  f.write("#include \"vtkDICOMDictionary.h\"\n")
  f.write("#include \"%s.h\"\n" % (classname,))
  f.write("\n")

  f.write("namespace {\n")
  f.write("\n")
  f.write("typedef vtkDICOMVR VR;\n")
  f.write("typedef vtkDICOMVM VM;\n")
  f.write("typedef vtkDICOMDictEntry::Entry DictEntry;\n")

  ns = ""
  if not privatedict:
    ns = "vtkDICOMDictionary::"

  dn = 0
  for name, (entry_list, tag_table, key_table) in entry_dict.items():
    dn = dn + 1
    ds = ""
    f.write("\n")
    if len(entry_dict) > 1:
      ds = "%03d" % (dn,)
      f.write("// ----- %s -----\n" % (name,))
      f.write("\n")
    f.write("const DictEntry Dict%sContents[] = {\n" % (ds,))
    for l in entry_list:
      f.write(l + "\n")
    f.write("};\n")
    for table,tagorkey in [(tag_table,"Tag"),(key_table,"Key")]:
      f.write("\n")
      f.write("const unsigned short Dict%s%sHashTable[] = {\n" % (ds,tagorkey))
      i = 0
      j = len(table) + 1
      row = []
      for l in table:
        if l is None:
          row.append("%5d," % (len(table),))
          i = i + 1
          if i % 10 == 0:
            f.write(" ".join(row) + "\n")
            row = []
        else:
          row.append("%5d," % (j,))
          i = i + 1
          if i % 10 == 0:
            f.write(" ".join(row) + "\n")
            row = []
          j = j + len(l) + 1
      row.append("%5d," % (0,))
      i = i + 1
      if VISUALIZE_HASH_ROWS:
        i = 0
      if i % 10 == 0:
        f.write(" ".join(row) + "\n")
        row = []
      for l in table:
        if not (l is None):
          row.append("%5d," % (len(l)//2,))
          i = i + 1
          if i % 10 == 0:
            f.write(" ".join(row) + "\n")
            row = []
          for j, e in enumerate(l):
            row.append("%5d," % (e,))
            i = i + 1
            if VISUALIZE_HASH_ROWS and j == len(l) - 1:
              i = 0
            if i % 10 == 0:
              f.write(" ".join(row) + "\n")
              row = []
      if i % 10 != 0:
        f.write(" ".join(row) + "\n")
      f.write("};\n")

    if not privatedict:
      f.write("\n")
      f.write("} // end anonymous namespace\n")

    f.write("\n")
    if len(entry_dict) > 1:
      ds = "%03d" % (dn,)
    f.write("vtkDICOMDictionary::Dict %sDict%sData = {\n" % (ns,ds))
    f.write("\"%s\",\n" % (name,))
    f.write("%d,\n" % (len(tag_table),))
    f.write("%d,\n" % (len(entry_list),))
    f.write("Dict%sTagHashTable,\n" % (ds,))
    f.write("Dict%sKeyHashTable,\n" % (ds,))
    f.write("Dict%sContents\n" % (ds,))
    f.write("};\n")

  if privatedict:
    f.write("\n")
    f.write("vtkDICOMDictionary::Dict *PrivateDictData[] = {\n")
    dn = 0
    for item in entry_dict.items():
      dn = dn + 1
      f.write("&Dict%03dData," % (dn,))
      if dn % 5 == 0:
        f.write("\n")
    f.write("NULL\n")
    f.write("};\n")
    f.write("\n")
    f.write("} // end anonymous namespace\n")
    f.write("\n")
    f.write("static unsigned int %sInitializerCounter;\n" % (classname,))
    f.write("\n")
    f.write("%sInitializer::%sInitializer()\n" % (classname,classname))
    f.write("{\n")
    f.write("  if (%sInitializerCounter++ == 0)\n" % (classname,))
    f.write("  {\n")
    f.write("    for (vtkDICOMDictionary::Dict **dp = PrivateDictData; *dp != NULL; dp++)\n")
    f.write("    {\n")
    f.write("      vtkDICOMDictionary::AddPrivateDictionary(*dp);\n")
    f.write("    }\n")
    f.write("  }\n")
    f.write("}\n")
    f.write("\n")
    f.write("%sInitializer::~%sInitializer()\n" % (classname,classname))
    f.write("{\n")
    f.write("  if (--%sInitializerCounter == 0)\n" % (classname,))
    f.write("  {\n")
    f.write("    for (vtkDICOMDictionary::Dict **dp = PrivateDictData; *dp != NULL; dp++)\n")
    f.write("    {\n")
    f.write("      vtkDICOMDictionary::RemovePrivateDictionary((*dp)->Name);\n")
    f.write("    }\n")
    f.write("  }\n")
    f.write("}\n")

if privatedict:
  enum_dict = {}
  entry_dict = {}

  for name, lines in privatelines.items():
    enum_list, entry_list, tag_table, key_table = makedict(lines, name)
    enum_dict[name] = enum_list
    entry_dict[name] = (entry_list, tag_table, key_table)

  if printheader:
    printhead(enum_dict, privatedict)
  else:
    printbody(entry_dict, privatedict)

else:
  enum_list, entry_list, tag_table, key_table = makedict(lines)

  classname = "vtkDICOMDictHash"

  if printheader:
    printhead({"DICOM" : enum_list}, classname)
    sys.stdout.write("// VTK-HeaderTest-Exclude: %s.h\n" % (classname,))
  else:
    printbody({"DICOM" : (entry_list, tag_table, key_table)}, classname)

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
