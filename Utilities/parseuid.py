"""
Generate a C++ table for use as a UID dictionary.
"""

import sys

if len(sys.argv) != 2:
    sys.stderr.write(
        """usage: python parsuid.py nemauids.txt > vtkDICOMUtilitiesUIDTable.cxx""")
    sys.exit(1)

f = open(sys.argv[1], 'r')
lines = f.readlines()
f.close()

root = [0, 0, 0, 0, "", ""]

part = ""
l = 0
maxlevel = 0
while l < len(lines):
    text = lines[l]
    if text[0] == '#':
        l += 1
        continue
    uid = lines[l].strip()
    name = lines[l+1].strip()
    utype = lines[l+2].strip()
    if l+3 < len(lines):
        cite = lines[l+3].strip()
    else:
        cite = "1.2.840.10008."
    if uid[0:14] != "1.2.840.10008.":
        print "oops at line", l
        l += 1
        continue
    if cite[0:14] != "1.2.840.10008." and cite[0] != '#':
        l += 4
    elif uid[0:18] == "1.2.840.10008.6.1.":
        cite = name
        name = utype
        utype = "Context Group"
        l += 3
    else:
        cite = utype
        utype = "Frame of Reference"
        l += 3
    uid = uid[14:]
    ret = " (Retired)"
    if len(name) > 10 and name[-10:] == ret:
        name = name[0:-10]
    else:
        ret = ""
    k = name.find(": Default")
    if k > 0:
        name = name[0:k]
    parts = map(int, uid.split('.'))
    node = root
    for level in range(len(parts)):
        idx = parts[level]
        if node[0] == 0:
            node[1] = 1
            node[2] = idx
            node[0] = [ [0, 0, 0, 0, "", ""] ]
        if node[2] > idx:
            for i in range(idx, node[2]):
                node[0].insert(0, [0, 0, 0, 0, "", ""])
            node[1] += node[2] - idx
            node[2] = idx
        if node[2] + node[1] - 1 < idx:
            for i in range(node[2] + node[1] - 1, idx):
                node[0].append([0, 0, 0, 0, "", ""])
            node[1] += idx - (node[2] + node[1] - 1)
        node = node[0][idx - node[2]]
        if level == len(parts)-1:
            if cite[0:4] == "CID ":
                node[3] = int(cite[4:])
            else:
                node[3] = 0
            node[4] = " // 1.2.840.10008." + uid + ret
            node[5] = name
            if level > maxlevel:
                maxlevel = level

print "/*========================================================================="
print "This is an automatically generated file.  Include errata for any changes."
print "=========================================================================*/"

print "\n#include \"vtkDICOMUtilities.h\""

print "\nnamespace {\n"

print "struct UIDTableEntry"
print "{"
print "  unsigned short Next;"
print "  unsigned short Size;"
print "  unsigned short First;"
print "  unsigned short CID;"
print "  const char *Name;"
print "};"

def printnode(node):
    if node[0]:
        child = node[0][0][6]
        if node[3] or node[5]:
            print "{ %d, %d, %d, %d,%s\n  \"%s\" }," % tuple([child]+node[1:6])
        else:
            print "{ %d, %d, %d, 0, 0 }," % tuple([child]+node[1:3])
    else:
        if node[3] or node[5]:
            print "{ 0, %d, %d, %d,%s\n  \"%s\" }," % tuple(node[1:6])
        else:
            print "{ 0, %d, %d, 0, 0 }," % tuple(node[1:3])

def recursetrie(node, counter):
    if node[0]:
        for child in node[0]:
            if counter:
                counter[0] += 1
                child.append(counter[0])
            else:
                printnode(child)
        for child in node[0]:
            recursetrie(child, counter)

print "\nUIDTableEntry UIDTable[] = {"
recursetrie(root, [0])
printnode(root)
recursetrie(root, None)
print "};"

getterfunc = \
"""
UIDTableEntry *GetUIDTableEntry(const char *uid)
{
  if (uid == 0)
    {
    return 0;
    }

  const char *prefix = "1.2.840.10008.";
  while (*prefix != '\\0' && *uid != '\\0' && *prefix == *uid)
    {
    prefix++;
    uid++;
    }

  if (*prefix != '\\0')
    {
    return 0;
    }

  UIDTableEntry *table = UIDTable;
  while (*uid != '\\0')
    {
    int i = -1;
    if (*uid >= '0' && *uid <= '9')
      {
      if (uid[0] != '0' || uid[1] != '0')
        {
        i = 0;
        do
          {
          i *= 10;
          i += (*uid - '0');
          uid++;
          }
        while (*uid >= '0' && *uid <= '9' && i < 214748364);
        }
      }
    if (*uid == '.')
      {
      uid++;
      if (*uid == '\\0')
        {
        table = 0;
        break;
        }
      }
    else if (*uid != '\\0')
      {
      table = 0;
      break;
      }
    i -= table->First;
    if (i < 0 || i >= static_cast<int>(table->Size))
      {
      table = 0;
      break;
      }
    table = &UIDTable[table->Next + i];
    }

  return table;
}
"""
print getterfunc
print "} // anonymous namespace"

exportedcode = \
"""
const char *vtkDICOMUtilities::GetUIDName(const char *uid)
{
  const char *result = "";
  UIDTableEntry *table = GetUIDTableEntry(uid);
  if (table)
    {
    if (table->Name)
      {
      result = table->Name;
      }
    }
  return result;
}

unsigned short vtkDICOMUtilities::GetContextID(const char *uid)
{
  unsigned short result = 0;
  UIDTableEntry *table = GetUIDTableEntry(uid);
  if (table)
    {
    result = table->CID;
    }
  return result;
}"""

print exportedcode
