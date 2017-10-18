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

#include "vtkSystemIncludes.h"
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
 *  allowed: 'ascii', 'latin1', 'latin2', 'latin3', 'latin4', 'latin5'
 *  'latin7', 'latin9', 'cyrillic' (iso-8859-5), 'arabic' (iso-8859-6),
 *  'greek' (iso-8859-7), 'hebrew' (iso-8859-8), 'tis-620', 'shift-jis',
 *  'euc-jp', 'iso-2022-jp', 'korean' (euc-kr), 'chinese' (gbk), 'gb18030',
 *  'big5', 'cp1250', 'cp1251', 'cp1252', 'cp1253', 'cp1254', 'cp1255',
 *  'cp1256', 'cp1257', and 'utf-8'.  Common aliases of these character
 *  sets can also be used.
 */
class VTKDICOM_EXPORT vtkDICOMCharacterSet
{
public:
  enum EnumType
  {
    ISO_IR_6   = 0,  // US_ASCII
    ISO_IR_13  = 1,  // JIS X 0201,  japanese romaji + katakana
    ISO_IR_100 = 8,  // ISO-8859-1,  latin1, western europe
    ISO_IR_101 = 9,  // ISO-8859-2,  latin2, central europe
    ISO_IR_109 = 10, // ISO-8859-3,  latin3, maltese
    ISO_IR_110 = 11, // ISO-8859-4,  latin4, baltic
    ISO_IR_144 = 12, // ISO-8859-5,  cyrillic
    ISO_IR_127 = 13, // ISO-8859-6,  arabic
    ISO_IR_126 = 14, // ISO-8859-7,  greek
    ISO_IR_138 = 15, // ISO-8859-8,  hebrew
    ISO_IR_148 = 16, // ISO-8859-9,  latin5, turkish
    X_LATIN6   = 17, // ISO-8859-10, latin6, nordic
    ISO_IR_166 = 18, // ISO-8859-11, thai
    X_LATIN7   = 19, // ISO-8859-13, latin7, baltic rim
    X_LATIN8   = 20, // ISO-8859-14, latin8, celtic
    X_LATIN9   = 21, // ISO-8859-15, latin9, western europe
    X_LATIN10  = 22, // ISO-8859-16, latin10, southeastern europe
    X_EUCKR    = 24, // euc-kr,      ISO_IR_149 without escape codes
    X_GB2312   = 25, // gb2312,      ISO_IR_58 without escape codes
    ISO_2022_IR_6   = 32, // US_ASCII
    ISO_2022_IR_13  = 33, // JIS X 0201,  japanese katakana
    ISO_2022_IR_87  = 34, // JIS X 0208,  japanese 94x94 primary
    ISO_2022_IR_159 = 36, // JIS X 0212,  japanese 94x94 secondary
    ISO_2022_IR_100 = 40, // ISO-8859-1,  latin1, western europe
    ISO_2022_IR_101 = 41, // ISO-8859-2,  latin2, central europe
    ISO_2022_IR_109 = 42, // ISO-8859-3,  latin3, maltese
    ISO_2022_IR_110 = 43, // ISO-8859-4,  latin4, baltic
    ISO_2022_IR_144 = 44, // ISO-8859-5,  cyrillic
    ISO_2022_IR_127 = 45, // ISO-8859-6,  arabic
    ISO_2022_IR_126 = 46, // ISO-8859-7,  greek
    ISO_2022_IR_138 = 47, // ISO-8859-8,  hebrew
    ISO_2022_IR_148 = 48, // ISO-8859-9,  latin5, turkish
    ISO_2022_IR_166 = 50, // ISO-8859-11, thai
    ISO_2022_IR_149 = 56, // the KS X 1001 part of ISO-2022-KR
    ISO_2022_IR_58  = 57, // the GB2312 part of ISO-2022-CN
    ISO_IR_192 = 64, // UTF-8,       unicode
    GB18030    = 65, // gb18030,     chinese with full unicode mapping
    GBK        = 66, // gbk,         chinese
    X_BIG5     = 67, // big5 + ETEN, traditional chinese
    X_EUCJP    = 69, // euc-jp,      unix encoding for japanese
    X_SJIS     = 70, // windows-31j, aka shift-jis, code page 932
    X_CP874    = 76, // cp1162,      thai (windows-874)
    X_CP1250   = 80, // cp1250,      central europe
    X_CP1251   = 81, // cp1251,      cyrillic
    X_CP1252   = 82, // cp1252,      western europe
    X_CP1253   = 83, // cp1253,      greek
    X_CP1254   = 84, // cp1254,      turkish
    X_CP1255   = 85, // cp1255,      hebrew
    X_CP1256   = 86, // cp1256,      arabic
    X_CP1257   = 87, // cp1257,      baltic rim
    X_KOI8     = 90, // koi8,        cyrillic
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
   *  nevertheless use a non-ASCII character encoding.  This method can be
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
  //! Convert text from UTF-8 to this encoding.
  /*!
   *  Attempt to convert from UTF-8 to this character set.  Every
   *  non-convertible character will be replaced with '?'.  If you
   *  pass a non-null value for the "lp" parameter, it will return
   *  the position in the input UTF-8 string where the first conversion
   *  error occurred.  If a successful conversion was returned, then
   *  lp will be set to the length of the input string.
  */
  std::string FromUTF8(const char *text, size_t l, size_t *lp=0) const;
  std::string FromUTF8(const std::string& text) const {
    return FromUTF8(text.data(), text.length()); }

  //! Convert text from this encoding to UTF-8.
  /*!
   *  This will convert text to UTF-8, which is generally a lossless
   *  process for western languages but not for the CJK languages.
   *  Characters that cannot be mapped to unicode, or whose place in
   *  unicode is not known, will be printed as unicode U+FFFD which
   *  appears as a question mark in a diamond.  If you pass a non-null
   *  value for the "lp" parameter, it will return the position in the
   *  input string where the first conversion error occurred.  If a
   *  successful conversion was returned, then lp will be set to the
   *  length of the input string.
   */
  std::string ToUTF8(const char *text, size_t l, size_t *lp=0) const;
  std::string ToUTF8(const std::string& text) const {
    return ToUTF8(text.data(), text.length()); }

  //! Obsolete method for converting to UTF8.
  std::string ConvertToUTF8(const char *text, size_t l) const;

  //! Convert text to UTF-8 that is safe to print to the console.
  /*!
   *  All control characters or unconvertible characters will be replaced
   *  by four-byte octal codes, e.g. '\033'.  Backslashes will be replaced
   *  by '\134' to avoid any potential ambiguity.
   */
  std::string ToSafeUTF8(const char *text, size_t l) const;
  std::string ToSafeUTF8(const std::string& text) const {
    return ToSafeUTF8(text.data(), text.length()); }

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
  std::string CaseFoldedUTF8(const std::string& text) const {
    return CaseFoldedUTF8(text.data(), text.length()); }

  //! Returns true if ISO 2022 escape codes are used.
  /*!
   *  If this method returns true, then escape codes can be used to
   *  switch between character sets.
   */
  bool IsISO2022() const {
    return ((this->Key & (ISO_2022 + ISO_2022 - 1)) == (this->Key | ISO_2022));
  }

  //! Returns true if this uses an ISO 8859 code page.
  bool IsISO8859() const {
    return (this->Key >= ISO_IR_100 && this->Key <= X_LATIN10);
  }

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
  size_t AnyToUTF8(const char *t, size_t l, std::string *s, int m) const;
  size_t UTF8ToSingleByte(const char *t, size_t l, std::string *s) const;
  size_t SingleByteToUTF8(const char *t, size_t l, std::string *s, int m) const;
  size_t ISO8859ToUTF8(const char *t, size_t l, std::string *s, int) const;
  size_t UTF8ToISO2022(const char *t, size_t l, std::string *s) const;
  size_t ISO2022ToUTF8(const char *t, size_t l, std::string *s, int m) const;
  static size_t UTF8ToEUCKR(const char *t, size_t l, std::string *s);
  static size_t EUCKRToUTF8(const char *t, size_t l, std::string *s, int m);
  static size_t UTF8ToGB2312(const char *t, size_t l, std::string *s);
  static size_t GB2312ToUTF8(const char *t, size_t l, std::string *s, int m);
  static size_t UTF8ToGB18030(const char *t, size_t l, std::string *s);
  static size_t GB18030ToUTF8(const char *t, size_t l, std::string *s, int m);
  static size_t UTF8ToGBK(const char *t, size_t l, std::string *s);
  static size_t GBKToUTF8(const char *t, size_t l, std::string *s, int m);
  static size_t UTF8ToBig5(const char *t, size_t l, std::string *s);
  static size_t Big5ToUTF8(const char *t, size_t l, std::string *s, int m);
  static size_t UTF8ToEUCJP(const char *t, size_t l, std::string *s);
  static size_t EUCJPToUTF8(const char *t, size_t l, std::string *s, int m);
  static size_t UTF8ToSJIS(const char *t, size_t l, std::string *s);
  static size_t SJISToUTF8(const char *t, size_t l, std::string *s, int m);
  static size_t UTF8ToJISX(
    int charset, const char *t, size_t l, std::string *s);
  static size_t JISXToUTF8(
    int csGL, int csGR, const char *t, size_t l, std::string *s, int m);
  static unsigned char KeyFromString(const char *name, size_t nl);

  unsigned char Key;

  enum {
    ISO_2022_JP_BASE = 7,
    ISO_2022_BASE = 31,
    ISO_2022 = 32
  };

  static unsigned char GlobalDefault;
  static bool GlobalOverride;

public:
  static const unsigned short *Table[256];
  static const unsigned short *Reverse[256];
};

VTKDICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMCharacterSet& a);

#endif /* vtkDICOMCharacterSet_h */
// VTK-HeaderTest-Exclude: vtkDICOMCharacterSet.h
