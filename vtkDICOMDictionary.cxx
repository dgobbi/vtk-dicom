/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMDictionary.h"
#include "vtkDICOMVR.h"
#include "vtkDICOMVM.h"
#include "vtkDICOMTag.h"
#include "vtkDICOMDictEntry.h"

// Including this forces the loading of the private dictionaries.
#include "vtkDICOMDictPrivate.h"

#include <string.h>

//----------------------------------------------------------------------------
struct vtkDICOMDictionary::PrivateDict
{
  const char *Name;
  unsigned int Hash;
  unsigned int DictHashTableSize;
  vtkDICOMDictEntry::Entry **DictHashTable;
};

vtkDICOMDictionary::PrivateDict *
  vtkDICOMDictionary::PrivateDictTable[DICT_PRIVATE_TABLE_SIZE];

//----------------------------------------------------------------------------
// A helper class to delete static variables when program exits.
static int vtkDICOMDictionaryInitializerCounter;

// Perform initialization of static variables.
vtkDICOMDictionaryInitializer::vtkDICOMDictionaryInitializer()
{
  if (vtkDICOMDictionaryInitializerCounter++ == 0)
    {
    for (int i = 0; i < DICT_PRIVATE_TABLE_SIZE; i++)
      {
      vtkDICOMDictionary::PrivateDictTable[i] = 0;
      }
    }
}

// Perform cleanup of static variables.
vtkDICOMDictionaryInitializer::~vtkDICOMDictionaryInitializer()
{
  typedef vtkDICOMDictionary::PrivateDict PrivateDict;

  if (--vtkDICOMDictionaryInitializerCounter == 0)
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
  const char *name, unsigned int *tableSizePtr)
{
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
        *tableSizePtr = hptr->DictHashTableSize;
        return hptr->DictHashTable;
        }
      hptr++;
      }
    }

  *tableSizePtr = 1;
  return 0;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMDictionary::FindDictEntry(
  const vtkDICOMTag tag, const char *dict)
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // compute the hash table index
  unsigned int h = tag.ComputeHash();
  unsigned int i = (h & (DICT_HASH_TABLE_SIZE - 1));

  // default to the standard dictionary
  vtkDICOMDictEntry::Entry **htable = vtkDICOMDictionary::DictHashTable;
  vtkDICOMDictEntry::Entry *hptr;

  // for odd group number, only search the private dictionary
  if ((group & 1) != 0 && dict != 0)
    {
    unsigned int m;
    htable = vtkDICOMDictionary::FindPrivateDict(dict, &m);
    i = (h % m);
    }

  // search the hash table
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
  const char *name, vtkDICOMDictEntry::Entry **hashTable, unsigned int size)
{
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
    hptr->DictHashTableSize = 0;
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
  hptr->DictHashTableSize = size;
  hptr->DictHashTable = hashTable;

  hptr++;
  hptr->Name = 0;
  hptr->Hash = 0;
  hptr->DictHashTableSize = 0;
  hptr->DictHashTable = 0;
}

//----------------------------------------------------------------------------
void vtkDICOMDictionary::RemovePrivateDictionary(const char *name)
{
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
        break;
        }
      hptr++;
      }

    if (hptr->Name)
      {
      delete [] hptr->Name;
      }

    // erase
    while (hptr->Name != 0)
      {
      *hptr = *(hptr + 1);
      hptr++;
      }
    }
}

