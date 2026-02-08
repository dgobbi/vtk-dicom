"""
Generate a C++ table for use as a UID dictionary.
"""

import sys

if len(sys.argv) != 2:
    sys.stderr.write(
        """usage: python parseuid.py nemauids.txt > vtkDICOMUtilitiesUIDTable.cxx""")
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
        sys.stderr.write("oops at line %d\n" % (l,))
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
    parts = [int(x) for x in uid.split('.')]
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

f = sys.stdout
f.write("/*=========================================================================\n")
f.write("This is an automatically generated file.  Include errata for any changes.\n")
f.write("=========================================================================*/\n")

f.write("\n#include \"vtkDICOMUtilitiesUIDTable.h\"\n")

f.write("\n// clang-format off\n")

f.write("\nnamespace {\n\n")

f.write("struct UIDTableEntry\n")
f.write("{\n")
f.write("  unsigned short Next;\n")
f.write("  unsigned short Size;\n")
f.write("  unsigned short First;\n")
f.write("  unsigned short CID;\n")
f.write("  const char *Name;\n")
f.write("};\n")

def printnode(node):
    if node[0]:
        child = node[0][0][6]
        if node[3] or node[5]:
            f.write("{ %d, %d, %d, %d,%s\n  \"%s\" },\n" % tuple([child]+node[1:6]))
        else:
            f.write("{ %d, %d, %d, 0, nullptr },\n" % tuple([child]+node[1:3]))
    else:
        if node[3] or node[5]:
            f.write("{ 0, %d, %d, %d,%s\n  \"%s\" },\n" % tuple(node[1:6]))
        else:
            f.write("{ 0, %d, %d, 0, nullptr },\n" % tuple(node[1:3]))

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

f.write("\nconst UIDTableEntry UIDTable[] = {\n")
recursetrie(root, [0])
printnode(root)
recursetrie(root, None)
f.write("};\n")

getterfunc = \
"""
const UIDTableEntry *GetUIDTableEntry(const char *uid)
{
  if (uid == nullptr)
  {
    return nullptr;
  }

  const char *prefix = "1.2.840.10008.";
  while (*prefix != '\\0' && *uid != '\\0' && *prefix == *uid)
  {
    prefix++;
    uid++;
  }

  if (*prefix != '\\0')
  {
    return nullptr;
  }

  const UIDTableEntry *table = UIDTable;
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
        table = nullptr;
        break;
      }
    }
    else if (*uid != '\\0')
    {
      table = nullptr;
      break;
    }
    i -= table->First;
    if (i < 0 || i >= static_cast<int>(table->Size))
    {
      table = nullptr;
      break;
    }
    table = &UIDTable[table->Next + i];
  }

  return table;
}

"""
f.write(getterfunc)
f.write("} // anonymous namespace\n")

exportedcode = \
"""
const char *vtkDICOMUtilities::GetUIDName(const char *uid)
{
  const char *result = "";
  const UIDTableEntry *table = GetUIDTableEntry(uid);
  if (table)
  {
    if (table->Name)
    {
      result = table->Name;
    }
  }
  return result;
}

unsigned short vtkDICOMUtilities::GetCIDFromUID(const char *uid)
{
  unsigned short result = 0;
  const UIDTableEntry *table = GetUIDTableEntry(uid);
  if (table)
  {
    result = table->CID;
  }
  return result;
}
"""

f.write(exportedcode)

f.write("\n// clang-format on\n")
