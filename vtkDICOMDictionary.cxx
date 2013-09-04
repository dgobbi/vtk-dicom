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

#include <string.h>

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
  if (vtkDICOMDictionary::InitializeOnce())
    {
    char **cpp = vtkDICOMDictionary::PrivateDictionaryNames;
    if (cpp)
      {
      while (*cpp)
        {
        delete [] *cpp;
        cpp++;
        }
      }

    delete [] vtkDICOMDictionary::PrivateDictionaryNames;
    delete [] vtkDICOMDictionary::PrivateDictionaries;
    vtkDICOMDictionary::PrivateDictionaries = 0;
    }
}

// Destruction of this object when the program exits will cause
// the private dictionary list of vtkDICOMDictionary to be deleted.
static vtkDICOMDictionaryCleanup DictionaryCleanupInstance;

//----------------------------------------------------------------------------
vtkDICOMDictEntry::Entry ***vtkDICOMDictionary::PrivateDictionaries;
char **vtkDICOMDictionary::PrivateDictionaryNames;

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
    vtkDICOMDictionary::PrivateDictionaries = 0;
    vtkDICOMDictionary::PrivateDictionaryNames = 0;
    initialized = true;
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMDictionary::FindDictEntry(
  const vtkDICOMTag tag, const char *dict)
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // default to the standard dictionary
  vtkDICOMDictEntry::Entry **htable = vtkDICOMDictionary::DictHashTable;
  vtkDICOMDictEntry::Entry *hptr;

  // for odd group number, only search the private dictionary
  if (group & 1)
    {
    vtkDICOMDictionary::InitializeOnce();
    char **names = vtkDICOMDictionary::PrivateDictionaryNames;
    htable = 0;
    if (names && dict)
      {
      for (int i = 0; names[i] != 0; i++)
        {
        size_t n = strlen(names[i]);
        if (strncmp(names[i], dict, n) == 0)
          {
          htable = vtkDICOMDictionary::PrivateDictionaries[i];
          break;
          }
        }
      }
    }

  // compute the hash table index
  unsigned int m = DICT_HASH_TABLE_SIZE - 1;
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
  vtkDICOMDictEntry::Entry ***tlist = vtkDICOMDictionary::PrivateDictionaries;
  char **nlist = vtkDICOMDictionary::PrivateDictionaryNames;

  int n = 0;
  if (tlist)
    {
    while (tlist[n]) { n++; }
    }

  vtkDICOMDictEntry::Entry ***newlist = new vtkDICOMDictEntry::Entry**[n+2];
  char **newnames = new char *[n+2];
  char *newname = new char[strlen(name)+1];
  strcpy(newname, name);

  for (int i = 0; i < n; i++)
    {
    newlist[i] = tlist[i];
    newnames[i] = nlist[i];
    }

  newlist[n] = hashTable;
  newlist[n+1] = 0;
  newnames[n] = newname;
  newnames[n+1] = 0;
  vtkDICOMDictionary::PrivateDictionaries = newlist;
  vtkDICOMDictionary::PrivateDictionaryNames = newnames;

  delete [] tlist;
  delete [] nlist;
}
