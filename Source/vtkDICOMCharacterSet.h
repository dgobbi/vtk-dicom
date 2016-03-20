/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMCharacterSet_h
#define vtkDICOMCharacterSet_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h" // For export macro

#include <string>

//! Character sets.
/*!
 *  DICOM supports a fairly small number of single-byte and multi-byte
 *  character sets.  The only VRs that support these character sets are
 *  PN, LO, SH, ST, LT, and ST (all other text VRs must be ASCII). In
 *  total, there is one 7-bit encoding (ASCII), eleven 8-bit single-byte
 *  encodings, three variable-length encodings (UTF-8, GB18030, GBK), and
 *  three iso-2022 multi-byte encodings.  It is possible to use iso-2022
 *  escape codes to switch between any encodings except for UTF-8 and
 *  GB18030/GBK, although only a subset of the iso-2022 escape codes are
 *  supported by DICOM.
 */
class VTKDICOM_EXPORT vtkDICOMCharacterSet
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
    ISO_IR_13  = 11, // JIS X 0201,  katakana, japanese
    ISO_IR_14  = 12, // JIS X 0201,  romaji, japanese
    ISO_IR_192 = 13, // UTF-8,       unicode
    GB18030    = 14, // gb18030,     chinese with full unicode mapping
    GBK        = 15, // gbk,         chinese without full unicode mapping
    ISO_2022_IR_58  = 16, // the GB2312 subset of ISO-2022-CN
    ISO_2022_IR_87  = 32, // the JIS X 0208 subset of ISO-2022-JP
    ISO_2022_IR_159 = 64, // the JIS X 0212 subset of ISO-2022-JP-2
    ISO_2022_IR_149 = 128, // the KS X 1001 subset of ISO-2022-KR
    ISO_2022   = 240, // mask for the bitfield that indicates ISO-2022
    Unknown    = 255  // signifies unknown character set
  };

  //@{
  //! Construct an object that describes the default (ASCII) character set.
  vtkDICOMCharacterSet() : Key(0) {}

  //! Construct a character set object from a given code.
  /*!
   *  The code can be any of the enumerated code values.  The ISO 2022 codes
   *  are a bitfield and they can be combined with most other codes, but they
   *  cannot be combined with ISO_IR_192, GB18030, or GBK.
   */
  vtkDICOMCharacterSet(int k) : Key(static_cast<unsigned char>(k)) {}

  //! Construct a character set object from a SpecificCharacterSet value.
  /*!
   *  This generates an 8-bit code that uniquely identifies a DICOM
   *  character set plus its code extensions.
   */
  explicit vtkDICOMCharacterSet(const std::string& name) {
    this->Key = KeyFromString(name.data(), name.length()); }
  vtkDICOMCharacterSet(const char *name, size_t nl) {
    this->Key = KeyFromString(name, nl); }
  //@}

  //@{
  //! Generate SpecificCharacterSet code values (diagnostic only).
  /*!
   *  Attempt to generate SpecificCharacterSet code values.  If ISO 2022
   *  encoding is not used, then a single code value is returned.  If
   *  ISO 2022 encoding is used with the single-byte character sets, then
   *  only the code value for first character set will be returned (due to
   *  limitations in the way this class stores the information).  A simple
   *  way to check whether such incomplete information will be returned is
   *  to check if "((GetKey() & ISO_2022) == ISO_2022)" is true.  However,
   *  if ISO 2022 encoding is used with one or more multi-byte character
   *  sets, the result is a set of backslash-separated code values, where
   *  the first value will be empty if the initial coding is ASCII.
   */
  std::string GetCharacterSetString() const;

  //! Get the numerical code for this character set object.
  unsigned char GetKey() const { return this->Key; }
  //@}

  //@{
  //! Convert text from this encoding to UTF-8.
  /*!
   *  This will convert text to UTF-8, which is generally a lossless
   *  process for western languages but not for the CJK languages.
   *  Characters that cannot be mapped to unicode, or whose place in
   *  unicode is not known, will be printed as unicode missing-character
   *  marks.
   */
  std::string ConvertToUTF8(const char *text, size_t l) const;

  //! Convert text into a form suitable for case-insensitive matching.
  /*!
   *  This function will perform case normalization on a string by
   *  converting it to lowercase, and by normalizing the forms of
   *  lowercase characters that do not have an exact uppercase
   *  equivalent.  In some cases, it might increase the length of
   *  the string.  It covers modern European scripts (including Greek
   *  and Cyrillic) and latin characters used in East Asian languages.
   */
  std::string CaseFoldedUTF8(const char *text, size_t l) const;

  //! Check for bidirectional character sets.
  /*!
   *  This is used to check for character sets that are likely to
   *  contain characters that print right-to-left, specifically Hebrew
   *  and Arabic.  Note that even though some parts of unicode fall
   *  into this category, this flag is off for unicode and GB18030/GBK.
   */
  bool IsBiDirectional() const {
    return (this->Key == ISO_IR_127 || this->Key == ISO_IR_138); }
  //@}

  //@{
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
  //@}

  //@{
  bool operator==(vtkDICOMCharacterSet b) const { return (this->Key == b.Key); }
  bool operator!=(vtkDICOMCharacterSet b) const { return (this->Key != b.Key); }
  bool operator<=(vtkDICOMCharacterSet a) const { return (this->Key <= a.Key); }
  bool operator>=(vtkDICOMCharacterSet a) const { return (this->Key >= a.Key); }
  bool operator<(vtkDICOMCharacterSet a) const { return (this->Key < a.Key); }
  bool operator>(vtkDICOMCharacterSet a) const { return (this->Key > a.Key); }
  //@}

private:
  static unsigned char KeyFromString(const char *name, size_t nl);

  unsigned char Key;
};

VTKDICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMCharacterSet& a);

#endif /* vtkDICOMCharacterSet_h */
// VTK-HeaderTest-Exclude: vtkDICOMCharacterSet.h
