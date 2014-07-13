/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMCharacterSet_h
#define __vtkDICOMCharacterSet_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"

#include <string>

//! Character sets.
/*!
 *  DICOM supports a fairly small number of single-byte and multi-byte
 *  character sets.  The only VRs that support these character sets are
 *  PN, LO, SH, ST, LT, and ST (all other text VRs must be ASCII). In
 *  total, there is one 7-bit encoding (ASCII), eleven 8-bit single-byte
 *  encodings, two unicode multi-byte ecodings (UTF-8 and GB18030), and
 *  three iso-2022 multi-byte encodings.  It is possible to use iso-2022
 *  escape codes to switch between any encodings except for UTF-8 and
 *  GB18030, although only a subset of the iso-2022 escape codes are
 *  supported by DICOM.
 */
class VTK_DICOM_EXPORT vtkDICOMCharacterSet
{
public:
  enum EnumType
  {
    ISO_IR_6   = 0,  // US_ASCII
    ISO_IR_100 = 1,  // ISO-8859-1,  latin1, western europe
    ISO_IR_101 = 2,  // ISO-8859-2,  latin2, central europe
    ISO_IR_109 = 3,  // ISO-8859-3,  latin3, maltese
    ISO_IR_110 = 4,  // ISO-8859-4,  latin4, baltic
    ISO_IR_144 = 5,  // ISO-8859-5,  cyrillic
    ISO_IR_127 = 6,  // ISO-8859-6,  arabic
    ISO_IR_126 = 7,  // ISO-8859-7,  greek
    ISO_IR_138 = 8,  // ISO-8859-8,  hebrew
    ISO_IR_148 = 9,  // ISO-8859-9,  latin5, turkish
    ISO_IR_166 = 10, // ISO-8859-11, thai
    ISO_IR_13  = 11, // JIS-X-0201,  katakana, japanese
    ISO_IR_14  = 12, // JIS-X-0201,  romaji, japanese
    ISO_IR_192 = 13, // UTF-8,       unicode
    GB18030    = 14, // gb18030,     chinese
    ISO_2022_OTHER  = 16, // any non-multibyte ISO-2022 character set
    ISO_2022_IR_87  = 32, // part of ISO-2022-JP and ISO-2022-JP-2
    ISO_2022_IR_159 = 64, // part of ISO-2022-JP-2
    ISO_2022_IR_149 = 128, // part of ISO-2022-KR and ISO-2022-JP-2
    ISO_2022   = 240, // mask for the bitfield that indicates ISO-2022
    Unknown    = 255  // signifies unknown character set
  };

  //! Construct an object that describes the default (ASCII) character set.
  vtkDICOMCharacterSet() : Key(0) {}

  //! Construct a character set object from a given code.
  /*!
   *  The code can be any of the enumerated code values.  The ISO_2022 codes
   *  are a bitfield and they can be combined with most other codes, but they
   *  cannot be combined with ISO_IR_192 or GB18030.
   */
  vtkDICOMCharacterSet(int k) : Key(static_cast<unsigned char>(k)) {}

  //! Construct a character set object from a SpecificCharacterSet value.
  /*!
   *  This generates an 8-bit code that uniquely identifies a DICOM
   *  character set plus its code extensions.
   */
  explicit vtkDICOMCharacterSet(const std::string& name);

  //! Generate a SpecificCharacterSet value.
  /*!
   *  The result is given as a set of backslash-separated values if more
   *  than one encoding is present.  The first value may be empty to indicate
   *  that it is ASCII.  Since this class uses an unsigned char for storage,
   *  the only secondary and tertiary values that can be represented are the
   *  three multi-byte ISO 2022 character sets.  Therefore, if the condition
   *  "if ((GetKey() & ISO_2022_OTHER) != 0)" is true, then the string
   *  returned by this method will be incomplete and only the first character
   *  set will be listed.
   */
  std::string GetCharacterSetString() const;

  //! Get the numerical code for this character set object.
  unsigned char GetKey() const { return this->Key; }

  //! Convert text from this encoding to UTF-8.
  /*!
   *  This will convert text to UTF-8, which is generally a lossless
   *  process for western languages but not for the CJK languages.
   *  Characters that cannot be mapped to unicode, or whose place in
   *  unicode is not known, will be printed as unicode missing-character
   *  marks.
   */
  std::string ConvertToUTF8(const char *text, size_t l) const;

  //! Convert text from this encoding to lowercase UTF-8.
  /*!
   *  This function is currently limited to the latin alphabet, so it works
   *  with latin1, latin2, latin3, latin4, and the corresponding parts of
   *  unicode.  It does not do greek or cyrillic.
   */
  std::string ConvertToLowerCaseUTF8(const char *text, size_t l) const;

  //! Check for bidirectional character sets.
  /*!
   *  This is used to check for character sets that are likely to
   *  contain characters that print right-to-left, specifically Hebrew
   *  and Arabic.  Note that even though some parts of unaicode fall
   *  into this category, this flag is off for unicode and GB18030.
   */
  bool IsBiDirectional() const {
    return (this->Key == ISO_IR_127 || this->Key == ISO_IR_138); }

  //! Count the number of backslashes in an encoded string.
  /*!
   *  The backslash byte is sometimes present as half of a multibyte
   *  character in the Japanese and Chinese encodings.  This method
   *  skips these false backslashes and counts only real backslashes.
   */
  unsigned int CountBackslashes(const char *text, size_t l) const;

  //! Get the offset to the next backslash, or to the end of the string.
  /*!
   *  In order to work properly, this method requires that its input is
   *  either at the beginning of the string or just after a backslash.
   */
  size_t NextBackslash(const char *text, const char *end) const;

  bool operator==(vtkDICOMCharacterSet b) const { return (this->Key == b.Key); }
  bool operator!=(vtkDICOMCharacterSet b) const { return (this->Key != b.Key); }
  bool operator<=(vtkDICOMCharacterSet a) const { return (this->Key <= a.Key); }
  bool operator>=(vtkDICOMCharacterSet a) const { return (this->Key >= a.Key); }
  bool operator<(vtkDICOMCharacterSet a) const { return (this->Key < a.Key); }
  bool operator>(vtkDICOMCharacterSet a) const { return (this->Key > a.Key); }

private:
  unsigned char Key;
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMCharacterSet& a);

#endif /* __vtkDICOMCharacterSet_h */
