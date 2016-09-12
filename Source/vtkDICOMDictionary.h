/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMDictionary_h
#define vtkDICOMDictionary_h

#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMDictEntry.h"
#include "vtkDICOMDictHash.h"

//! The size of the hash table for the dicom dictionary.
#define DICT_HASH_TABLE_SIZE 4096
#define DICT_PRIVATE_TABLE_SIZE 512

//! Provide access to the DICOM tag dictionary.
class VTKDICOM_EXPORT vtkDICOMDictionary
{
public:
  //! A struct to store a DICOM dictionary hash table.
  struct Dict
  {
    const char *Name;
    unsigned short HashSize;
    unsigned short DataSize;
    const unsigned short *TagHashTable;
    const unsigned short *KeyHashTable;
    const vtkDICOMDictEntry::Entry *Contents;
  };

  struct DictHashEntry;

  //@{
  //! Find the dictionary entry for the given tag.
  static vtkDICOMDictEntry FindDictEntry(const vtkDICOMTag tag) {
    return vtkDICOMDictionary::FindDictEntry(tag, 0); }

  //! Find the dictionary for the given key.
  static vtkDICOMDictEntry FindDictEntry(const char *key) {
    return vtkDICOMDictionary::FindDictEntry(key, 0); }
  //@}

  //@{
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

  //! Search for a private dictionary entry by key.
  /*!
   *  Warning: not all private dictionaries have normatively defined keys
   *  associated with the tags they use.  Even for those that do, the keys
   *  used by this library might not be accurate because it relies on
   *  information collected from third parties.
   */
  static vtkDICOMDictEntry FindDictEntry(
    const char *key, const char *privateDict);
  //@}

  //@{
  //! Add the hash table for a private dictionary.
  /*!
   *  The name should be the text that appears in the PrivateCreator
   *  element of the data set when this dictionary is used.  The value
   *  of "n" is the size of the provided hash table.
   */
  static void AddPrivateDictionary(Dict *dict);

  //! Remove a private dictionary.
  static void RemovePrivateDictionary(const char *name);
  //@}

private:
  friend class vtkDICOMDictionaryInitializer;

  //! Compute a string hash for a DICOM text value.
  /*!
   *  The final trailing space will be stripped, if present.  The
   *  resulting string will not be terminated if it fills all 64 bytes.
   */
  static unsigned int HashLongString(const char *lo, char stripped[64]);

  //! Locate a private dictionary, given the name.
  /*!
   *  This returns the hash table, and also returns the size of the
   *  hash table in the second argument.
   */
  static Dict *FindPrivateDict(const char *name);

  //! The lookup table for the dictionary.
  static Dict DictData;

  //! The lookup table for private dictionaries.
  static DictHashEntry *PrivateDictTable[DICT_PRIVATE_TABLE_SIZE];
};

//! @cond
//! Initializer (Schwarz counter).
/*!
 *  This ensures that the vtkDICOMDictionary module is initialized before
 *  any other module that includes this header file.
 */
class VTKDICOM_EXPORT vtkDICOMDictionaryInitializer
{
public:
  vtkDICOMDictionaryInitializer();
  ~vtkDICOMDictionaryInitializer();
private:
  vtkDICOMDictionaryInitializer(const vtkDICOMDictionaryInitializer&);
  vtkDICOMDictionaryInitializer& operator=(
    const vtkDICOMDictionaryInitializer&);
};

static vtkDICOMDictionaryInitializer vtkDICOMDictionaryInitializerInstance;
//! @endcond

#endif /* vtkDICOMDictionary_h */
// VTK-HeaderTest-Exclude: vtkDICOMDictionary.h
