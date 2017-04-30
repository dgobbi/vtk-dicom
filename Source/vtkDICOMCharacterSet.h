/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
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
 *  This class provides the means to convert the various international
 *  text encodings used by DICOM to the popular UTF-8 encoding.  It does
 *  not at this time provide the means to convert to any encoding other
 *  than UTF-8.
 *
 *  During conversion to UTF-8, any codes in the original encoding that
 *  cannot be converted to Unicode are replaced by "REPLACEMENT CHARACTER",
 *  which is a question mark in a black diamond.  For instance, if the
 *  original encoding is ISO_IR_6, any octets with the 8th bit set will
 *  be replaced.
 *
 *  DICOM supports a fairly small number of single-byte and multi-byte
 *  character sets.  The only VRs that support these character sets are
 *  PN, LO, SH, ST, LT, and ST (all other text VRs must be ASCII). In
 *  total, there is one 7-bit encoding (ASCII), eleven 8-bit single-byte
 *  encodings, three variable-length encodings (UTF-8, GB18030, GBK), and
 *  three iso-2022 multi-byte encodings.  It is possible to use iso-2022
 *  escape codes to switch between most of the encodings, with UTF-8 and
 *  GB18030/GBK as the most noteworthy exceptions.
 *
 *  In some DICOM data sets, especially old ones, the SpecificCharacterSet
 *  attribute will be missing and it might be necessary to manually specify
 *  a character set for the application to use.  Use SetGlobalDefault() to
 *  do so.  The vtkDICOMCharacterSet constructor can take the desired
 *  character encoding as a string, where the following encodings are
 *  allowed: 'ascii', 'latin1' (cp1252), 'latin2', 'latin3', 'latin4',
 *  'cyrillic' (iso-8859-5), 'arabic' (iso-8859-6), 'greek' (iso-8859-7),
 *  'hebrew' (iso-8859-8), 'latin5' (cp1254), 'tis-620', 'shift-jis', 'euc-jp',
 *  'iso-2022-jp', 'korean' (euc-kr), 'chinese' (gbk), 'gb18030', 'big5',
 *  'cp1250', 'cp1251', 'cp1253', 'cp1255', 'cp1256', 'latin9', and 'utf-8'.
 *  Common aliases of these character sets can also be used.
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
    ISO_IR_13  = 11, // JIS X 0201,  japanese romaji + katakana
    X_LATIN9   = 12, // ISO-8859-15, latin9, western europe
    ISO_IR_192 = 13, // UTF-8,       unicode
    GB18030    = 14, // gb18030,     chinese with full unicode mapping
    GBK        = 15, // gbk,         chinese
    X_CP1250   = 16, // cp1250,      central europe
    X_CP1251   = 17, // cp1251,      cyrillic
    X_CP1253   = 18, // cp1253,      greek
    X_CP1255   = 19, // cp1255,      hebrew
    X_GB2312   = 20, // reserved     ISO_IR_58 without escape codes
    X_EUCKR    = 21, // reserved     ISO_IR_149 without escape codes
    X_BIG5     = 22, // big5 + ETEN, traditional chinese
    X_SJIS     = 23, // windows-31j, aka shift-jis, code page 932
    X_EUCJP    = 24, // euc-jp,      unix encoding for japanese
    X_CP1256   = 25, // cp1256,      arabic
    // ISO_IR_87  = 32, // reserved, use ISO_2022_IR_87
    // ISO_IR_159 = 64, // reserved, use ISO_2022_IR_159
    ISO_2022        = 128, // bit that indicates use of ISO-2022
    ISO_2022_IR_6   = 128, // US_ASCII
    ISO_2022_IR_100 = 129, // ISO-8859-1,  latin1, western europe
    ISO_2022_IR_101 = 130, // ISO-8859-2,  latin2, central europe
    ISO_2022_IR_109 = 131, // ISO-8859-3,  latin3, maltese
    ISO_2022_IR_110 = 132, // ISO-8859-4,  latin4, baltic
    ISO_2022_IR_144 = 133, // ISO-8859-5,  cyrillic
    ISO_2022_IR_127 = 134, // ISO-8859-6,  arabic
    ISO_2022_IR_126 = 135, // ISO-8859-7,  greek
    ISO_2022_IR_138 = 136, // ISO-8859-8,  hebrew
    ISO_2022_IR_148 = 137, // ISO-8859-9,  latin5, turkish
    ISO_2022_IR_166 = 138, // ISO-8859-11, thai
    ISO_2022_IR_13  = 139, // JIS X 0201,  japanese katakana
    ISO_2022_IR_58  = 148, // the GB2312 part of ISO-2022-CN
    ISO_2022_IR_149 = 149, // the KS X 1001 part of ISO-2022-KR
    ISO_2022_IR_87  = 160, // the JIS X 0208 part of ISO-2022-JP
    ISO_2022_IR_159 = 192, // the JIS X 0212 part of ISO-2022-JP2
    Unknown    = 255  // signifies unknown character set
  };

  //@{
  //! Construct an object that describes the default (ASCII) character set.
  vtkDICOMCharacterSet() : Key(0) {}

  //! Construct a character set object from a given code.
  /*!
   *  The code can be any of the enumerated code values.  The ISO_2022 flag
   *  can be added to any of the ISO-8859 codes to indicate that the character
   *  set allows the use of escape codes.  Also note that ISO_2022_IR_87 and
   *  ISO_2022_IR_159 are combining codes that can be added to each other and
   *  to ISO_IR_13.  Specifying any other codes in combination can lead to
   *  undefined results, for example "ISO_2022_IR_100 | ISO_2022_IR_101" is
   *  not permitted and "ISO_2022_IR_100" must be used instead.
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
  //! Set the character set to use if SpecificCharacterSet is missing.
  /*!
   *  Some DICOM files do not list a SpecificCharacterSet attribute, but
   *  neverthless use a non-ASCII character encoding.  This method can be
   *  used to specify the character set in absence of SpecificCharacterSet.
   *  If SpecificCharacterSet is present, the default will not override it
   *  unless OverrideCharacterSet is true.
   */
  static void SetGlobalDefault(vtkDICOMCharacterSet cs) {
    GlobalDefault = cs.GetKey(); }
  static vtkDICOMCharacterSet GetGlobalDefault() {
    return GlobalDefault; }

  //! Override the value stored in SpecificCharacterSet with the default.
  /*!
   *  This method can be used if the SpecificCharacterSet attribute of a
   *  file is incorrect.  It forces the use of the character set that
   *  was set with SetGlobalDefault.
   */
  static void SetGlobalOverride(bool b) {
    GlobalOverride = b; }
  static void GlobalOverrideOn() { GlobalOverride = true; }
  static void GlobalOverrideOff() { GlobalOverride = false; }
  static bool GetGlobalOverride() { return GlobalOverride; }
  //@}

  //@{
  //! Generate SpecificCharacterSet code values (diagnostic only).
  /*!
   *  Attempt to generate SpecificCharacterSet code values.  If ISO 2022
   *  encoding is not used, then a single code value is returned.  If
   *  ISO 2022 encoding is used with the single-byte character sets, then
   *  only the code value for first character set will be returned (due to
   *  limitations in the way this class stores the information).  However,
   *  if ISO 2022 encoding is used with the multi-byte character sets,
   *  the result is a set of backslash-separated code values, where
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
   *  unicode is not known, will be printed as unicode U+FFFD which
   *  appears as a question mark in a diamond.
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
    return (this->Key == ISO_IR_127 ||
            this->Key == ISO_IR_138 ||
            this->Key == X_CP1255 ||
            this->Key == X_CP1256); }
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
  void ISO2022ToUTF8(const char *text, size_t l, std::string *s) const;
  static unsigned char KeyFromString(const char *name, size_t nl);

  unsigned char Key;

  enum {
    //! Mask to get the initial charset.
    ISO_2022_BASE = 31
  };

  static unsigned char GlobalDefault;
  static bool GlobalOverride;
};

VTKDICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMCharacterSet& a);

#endif /* vtkDICOMCharacterSet_h */
// VTK-HeaderTest-Exclude: vtkDICOMCharacterSet.h
