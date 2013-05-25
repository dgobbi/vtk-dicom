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
    delete [] vtkDICOMDictionary::PrivateDictionaries;
    vtkDICOMDictionary::PrivateDictionaries = 0;
    }
}

// Destruction of this object when the program exits will cause
// the private dictionary list of vtkDICOMDictionary to be deleted.
static vtkDICOMDictionaryCleanup DictionaryCleanupInstance;

//----------------------------------------------------------------------------
vtkDICOMDictEntry::Entry ***vtkDICOMDictionary::PrivateDictionaries;

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
    initialized = true;
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMDictionary::FindDictEntry(const vtkDICOMTag tag)
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // default to the standard dictionary
  vtkDICOMDictEntry::Entry **htable = vtkDICOMDictionary::DictHashTable;
  vtkDICOMDictEntry::Entry *hptr;

  // for even group number, only search standard dictionary
  vtkDICOMDictEntry::Entry **empty = 0;
  vtkDICOMDictEntry::Entry ***tlist = &empty;

  // for odd group number, only search the private dictionaries
  if (group & 1)
    {
    vtkDICOMDictionary::InitializeOnce();
    tlist = vtkDICOMDictionary::PrivateDictionaries;
    htable = 0;
    if (tlist)
      {
      htable = *tlist++;
      }
    }

  // compute the hash table index
  unsigned int m = DICT_HASH_TABLE_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);

  // search the dictionary (or dictionaries)
  while (htable)
    {
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

    htable = *tlist++;
    }

  // not found in dictionary
  return vtkDICOMDictEntry();
}

//----------------------------------------------------------------------------
void vtkDICOMDictionary::AddPrivateDictionary(
  vtkDICOMDictEntry::Entry **hashTable)
{
  vtkDICOMDictionary::InitializeOnce();
  vtkDICOMDictEntry::Entry ***tlist = vtkDICOMDictionary::PrivateDictionaries;
  int n = 0;
  if (tlist)
    {
    while (tlist[n]) { n++; }
    }

  vtkDICOMDictEntry::Entry ***newlist = new vtkDICOMDictEntry::Entry**[n+2];

  for (int i = 0; i < n; i++)
    {
    newlist[i] = tlist[i];
    }

  newlist[n] = hashTable;
  newlist[n+1] = 0;
  vtkDICOMDictionary::PrivateDictionaries = newlist;

  delete [] tlist;
}
