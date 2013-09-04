/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMDictionary_h
#define __vtkDICOMDictionary_h

#include "vtkDICOMModule.h"
#include "vtkDICOMDictEntry.h"
#include "vtkDICOMDictHash.h"

//! The size of the hash table for the dicom dictionary.
#define DICT_HASH_TABLE_SIZE 1024

//! Provide access to the DICOM tag dictionary.
class VTK_DICOM_EXPORT vtkDICOMDictionary
{
public:
  //! Find the dictionary entry for the given tag.
  static vtkDICOMDictEntry FindDictEntry(const vtkDICOMTag tag) {
    return vtkDICOMDictionary::FindDictEntry(tag, 0); }

  //! Include a private dictionary when searching for the tag.
  /*!
   *  This method requires that the creator of the private dictionary
   *  be given as it appears in the creator tag.  This method is usually
   *  not called directly, it is best to call vtkDICOMMetaData's
   *  FindDictEntry method because it can automatically identify the
   *  creator of any private tags that are present in the metadata.
   */
  static vtkDICOMDictEntry FindDictEntry(
    const vtkDICOMTag tag, const char *privateDict);

protected:
  //! Called by subclasses to add private dictionaries.
  static void AddPrivateDictionary(
    const char *name, vtkDICOMDictEntry::Entry **hashTable);

private:
  friend class vtkDICOMDictionaryCleanup;

  //! A method to handle static initialization of PrivateDictionaries
  static bool InitializeOnce();

  //! The lookup table for the dictionary.
  static vtkDICOMDictEntry::Entry *DictHashTable[DICT_HASH_TABLE_SIZE];

  //! A null-terminated list of private dictionaries.
  static vtkDICOMDictEntry::Entry ***PrivateDictionaries;
  static char **PrivateDictionaryNames;
};

#endif /* __vtkDICOMDictionary_h */
