/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMDictionary.h"
#include "vtkDICOMVR.h"
#include "vtkDICOMVM.h"
#include "vtkDICOMTag.h"
#include "vtkDICOMDictEntry.h"
#include "vtkDICOMDictPrivate.h"

#include <string.h>

//----------------------------------------------------------------------------
#define DICT_PRIVATE_HASH_SIZE 16

struct vtkDICOMDictionary::PrivateDict
{
  const char *Name;
  unsigned int Hash;
  vtkDICOMDictEntry::Entry **DictHashTable;
};

vtkDICOMDictionary::PrivateDict *
  vtkDICOMDictionary::PrivateDictTable[DICT_PRIVATE_TABLE_SIZE];

//----------------------------------------------------------------------------
// A helper class to delete static variables when program exits.
class vtkDICOMDictionaryCleanup
{
public:
  vtkDICOMDictionaryCleanup();
  ~vtkDICOMDictionaryCleanup();
};

vtkDICOMDictionaryCleanup::vtkDICOMDictionaryCleanup()
{
}

vtkDICOMDictionaryCleanup::~vtkDICOMDictionaryCleanup()
{
  typedef vtkDICOMDictionary::PrivateDict PrivateDict;

  if (vtkDICOMDictionary::InitializeOnce())
    {
    for (int i = 0; i < DICT_PRIVATE_TABLE_SIZE; i++)
      {
      PrivateDict *row = vtkDICOMDictionary::PrivateDictTable[i];
      if (row)
        {
        for (PrivateDict *dict = row; dict->Name != 0; dict++)
          {
          delete [] dict->Name;
          }
        delete [] row;
        }
      }
    }
}

// Destruction of this object when the program exits will cause
// the private dictionary list of vtkDICOMDictionary to be deleted.
static vtkDICOMDictionaryCleanup DictionaryCleanupInstance;

//----------------------------------------------------------------------------
bool vtkDICOMDictionary::InitializeOnce()
{
  // In C++ the order of initialization of static members is undefined,
  // whereas static variables in functions are always initialized the
  // first time the function they are defined in is run.  So we use this
  // predictability to make the initialization of our static members
  // similarly predictable.

  static bool initialized = false;

  if (!initialized)
    {
    for (int i = 0; i < DICT_PRIVATE_TABLE_SIZE; i++)
      {
      vtkDICOMDictionary::PrivateDictTable[i] = 0;
      }
    initialized = true;
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
unsigned int vtkDICOMDictionary::HashLongString(
  const char *input, char output[64])
{
  // Compute a string hash based on the function "djb2".
  // Because DICOM strings are padded with spaces to make their
  // length even, the pad space is ignored.
  unsigned int h = 5381;
  for (int k = 0; k < 64; k += 2)
    {
    unsigned char c = input[k];
    output[k] = c;
    if (c == '\0') { break; }
    h = (h << 5) + h + c;
    c = input[k+1];
    // trim pad space before terminating null
    if (c == ' ' && input[k+2] == '\0')
      {
      c = '\0';
      }
    output[k+1] = c;
    if (c == '\0') { break; }
    h = (h << 5) + h + c;
    }

  return h;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry::Entry **vtkDICOMDictionary::FindPrivateDict(
  const char *name)
{
  vtkDICOMDictionary::InitializeOnce();

  unsigned int m = DICT_PRIVATE_TABLE_SIZE - 1;
  PrivateDict **htable = vtkDICOMDictionary::PrivateDictTable;
  PrivateDict *hptr;

  // strip trailing spaces and compute the hash
  char stripname[64];
  unsigned int h = vtkDICOMDictionary::HashLongString(name, stripname);
  unsigned int i = (h & m);

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (hptr->Name != 0)
      {
      if (hptr->Hash == h && strncmp(hptr->Name, stripname, 64) == 0)
        {
        return hptr->DictHashTable;
        }
      hptr++;
      }
    }

  return 0;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMDictionary::FindDictEntry(
  const vtkDICOMTag tag, const char *dict)
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // default to the standard dictionary
  unsigned int m = DICT_HASH_TABLE_SIZE - 1;
  vtkDICOMDictEntry::Entry **htable = vtkDICOMDictionary::DictHashTable;
  vtkDICOMDictEntry::Entry *hptr;

  // for odd group number, only search the private dictionary
  if ((group & 1) != 0 && dict != 0)
    {
    m = DICT_PRIVATE_HASH_SIZE - 1;
    htable = vtkDICOMDictionary::FindPrivateDict(dict);
    }

  // compute the hash table index
  unsigned int i = (tag.ComputeHash() & m);

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (hptr->Group || hptr->Element || hptr->VR)
      {
      if (hptr->Group == group && hptr->Element == element)
        {
        return vtkDICOMDictEntry(hptr);
        }
      hptr++;
      }
    }

  // not found in dictionary
  return vtkDICOMDictEntry();
}

//----------------------------------------------------------------------------
void vtkDICOMDictionary::AddPrivateDictionary(
  const char *name, vtkDICOMDictEntry::Entry **hashTable)
{
  vtkDICOMDictionary::InitializeOnce();

  unsigned int m = DICT_PRIVATE_TABLE_SIZE - 1;
  PrivateDict **htable = vtkDICOMDictionary::PrivateDictTable;

  // strip trailing spaces and compute the hash
  char *stripname = new char[64];
  unsigned int h = vtkDICOMDictionary::HashLongString(name, stripname);
  unsigned int i = (h & m);
  PrivateDict *hptr = htable[i];

  // create hash table row if it is empty
  if (hptr == 0)
    {
    htable[i] = new PrivateDict[2];
    hptr = htable[i];
    hptr->Name = 0;
    hptr->Hash = 0;
    hptr->DictHashTable = 0;
    } 

  // go to the end of the row in the hash table
  int n = 0;
  while (hptr->Name != 0)
    {
    n++;
    hptr++;
    }

  // if n+1 is a power of two, double allocated space
  if (n > 0 && (n & (n+1)) == 0)
    {
    PrivateDict *oldptr = htable[i];
    hptr = new PrivateDict[2*(n+1)];
    htable[i] = hptr;
    // copy the old list
    for (int j = 0; j < n; j++)
      {
      *hptr++ = oldptr[j];
      }
    delete [] oldptr;
    }

  hptr->Name = stripname;
  hptr->Hash = h;
  hptr->DictHashTable = hashTable;

  hptr++;
  hptr->Name = 0;
  hptr->Hash = 0;
  hptr->DictHashTable = 0;
}
