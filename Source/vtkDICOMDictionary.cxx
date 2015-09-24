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
struct vtkDICOMDictionary::DictHashEntry
{
  unsigned int Hash;
  vtkDICOMDictionary::Dict *Dict;
};

vtkDICOMDictionary::DictHashEntry *
  vtkDICOMDictionary::PrivateDictTable[DICT_PRIVATE_TABLE_SIZE];

//----------------------------------------------------------------------------
// A helper class to delete static variables when program exits.
static unsigned int vtkDICOMDictionaryInitializerCounter;

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
  if (--vtkDICOMDictionaryInitializerCounter == 0)
    {
    for (int i = 0; i < DICT_PRIVATE_TABLE_SIZE; i++)
      {
      delete [] vtkDICOMDictionary::PrivateDictTable[i];
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
vtkDICOMDictionary::Dict *vtkDICOMDictionary::FindPrivateDict(
  const char *name)
{
  unsigned int m = DICT_PRIVATE_TABLE_SIZE - 1;
  DictHashEntry **htable = vtkDICOMDictionary::PrivateDictTable;
  DictHashEntry *hptr;

  // strip trailing spaces and compute the hash
  char stripname[64];
  unsigned int h = vtkDICOMDictionary::HashLongString(name, stripname);
  unsigned int i = (h & m);

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (hptr->Dict != 0)
      {
      if (hptr->Hash == h && strncmp(hptr->Dict->Name, stripname, 64) == 0)
        {
        return hptr->Dict;
        }
      hptr++;
      }
    }

  return 0;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMDictionary::FindDictEntry(
  const vtkDICOMTag tag, const char *dictname)
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // compute the hash table index
  unsigned int h = tag.ComputeHash();
  unsigned int i = (h & (DICT_HASH_TABLE_SIZE - 1));

  // default to the standard dictionary
  vtkDICOMDictionary::Dict *dict = &vtkDICOMDictionary::DictData;

  // for odd group number, only search the private dictionary
  if ((group & 1) != 0 && dictname != 0)
    {
    dict = vtkDICOMDictionary::FindPrivateDict(dictname);
    if (dict == 0)
      {
      // private dictionary not found
      return vtkDICOMDictEntry();
      }
    i = (h % dict->HashSize);
    }

  // search the hash table
  unsigned short *hptr = &dict->TagHashTable[dict->TagHashTable[i]];
  vtkDICOMDictEntry::Entry *dptr = dict->Contents;
  for (unsigned short n = *hptr; n != 0; --n)
    {
    ++hptr;
    vtkDICOMDictEntry::Entry *entry = &dptr[*hptr];
    ++hptr;
    if (*hptr == element && entry->Group == group)
      {
      return vtkDICOMDictEntry(entry);
      }
    }

  // not found in dictionary
  return vtkDICOMDictEntry();
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMDictionary::FindDictEntry(
  const char *key, const char *dictname)
{
  if (key == 0 || key[0] == '\0')
    {
    return vtkDICOMDictEntry();
    }

  char stripkey[64];
  unsigned int h = vtkDICOMDictionary::HashLongString(key, stripkey);

  // default to the standard dictionary
  vtkDICOMDictionary::Dict *dict = &vtkDICOMDictionary::DictData;

  // for odd group number, only search the private dictionary
  if (dictname != 0 && dictname[0] != '\0')
    {
    dict = vtkDICOMDictionary::FindPrivateDict(dictname);
    if (dict == 0)
      {
      // private dictionary not found
      return vtkDICOMDictEntry();
      }
    }

  unsigned short i = static_cast<unsigned short>(h % dict->HashSize);
  unsigned short j = static_cast<unsigned short>(h / dict->HashSize);

  // search the hash table
  unsigned short *hptr = &dict->KeyHashTable[dict->KeyHashTable[i]];
  vtkDICOMDictEntry::Entry *dptr = dict->Contents;
  for (unsigned short n = *hptr; n != 0; --n)
    {
    ++hptr;
    vtkDICOMDictEntry::Entry *entry = &dptr[*hptr];
    ++hptr;
    if (*hptr == j && strncmp(stripkey, entry->Name, 64) == 0)
      {
      return vtkDICOMDictEntry(entry);
      }
    }

  if (dictname != 0 && dictname[0] != '\0')
    {
    // brute force search the entire dictionary, if hash lookup failed
    // (in case people manually changed the key strings in the code,
    // without re-running makedict.py to re-generate the hash table)
    for (unsigned short k = 0; k < dict->DataSize; k++)
      {
      vtkDICOMDictEntry::Entry *entry = &dptr[k];
      if (strncmp(stripkey, entry->Name, 64) == 0)
        {
        return vtkDICOMDictEntry(entry);
        }
      }
    }

  // not found in dictionary
  return vtkDICOMDictEntry();
}

//----------------------------------------------------------------------------
void vtkDICOMDictionary::AddPrivateDictionary(Dict *dict)
{
  unsigned int m = DICT_PRIVATE_TABLE_SIZE - 1;
  DictHashEntry **htable = vtkDICOMDictionary::PrivateDictTable;

  // strip trailing spaces and compute the hash
  char stripname[64];
  unsigned int h = vtkDICOMDictionary::HashLongString(dict->Name, stripname);
  unsigned int i = (h & m);
  DictHashEntry *hptr = htable[i];

  // create hash table row if it is empty
  if (hptr == 0)
    {
    htable[i] = new DictHashEntry[2];
    hptr = htable[i];
    hptr->Hash = 0;
    hptr->Dict = 0;
    }

  // go to the end of the row in the hash table
  int n = 0;
  while (hptr->Dict != 0)
    {
    n++;
    hptr++;
    }

  // if n+1 is a power of two, double allocated space
  if (n > 0 && (n & (n+1)) == 0)
    {
    DictHashEntry *oldptr = htable[i];
    hptr = new DictHashEntry[2*(n+1)];
    htable[i] = hptr;
    // copy the old list
    for (int j = 0; j < n; j++)
      {
      *hptr++ = oldptr[j];
      }
    delete [] oldptr;
    }

  hptr->Hash = h;
  hptr->Dict = dict;

  hptr++;
  hptr->Hash = 0;
  hptr->Dict = 0;
}

//----------------------------------------------------------------------------
void vtkDICOMDictionary::RemovePrivateDictionary(const char *name)
{
  unsigned int m = DICT_PRIVATE_TABLE_SIZE - 1;
  DictHashEntry **htable = vtkDICOMDictionary::PrivateDictTable;
  DictHashEntry *hptr;

  // strip trailing spaces and compute the hash
  char stripname[64];
  unsigned int h = vtkDICOMDictionary::HashLongString(name, stripname);
  unsigned int i = (h & m);

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (hptr->Dict != 0)
      {
      if (hptr->Hash == h && strncmp(hptr->Dict->Name, stripname, 64) == 0)
        {
        break;
        }
      hptr++;
      }

    // erase
    while (hptr->Dict != 0)
      {
      *hptr = *(hptr + 1);
      hptr++;
      }
    }
}
