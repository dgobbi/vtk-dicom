/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2022 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMCharacterSet.h"
#include "vtkDICOMCharacterSetTables.h"

#include <algorithm>
#include <cstddef>
#include <sstream>
#include <vector>

// The global default is used when a DICOM lacks SpecificCharacterSet
unsigned char vtkDICOMCharacterSet::GlobalDefault =
  vtkDICOMCharacterSet::ISO_IR_6;
// This allows GlobalDefault to override SpecificCharacterSet
bool vtkDICOMCharacterSet::GlobalOverride = false;

namespace {

//----------------------------------------------------------------------------
//! This struct provides information about a character set.
struct CharsetInfo
{
  const char *Name; // the name we use for the charset
  const char *DefinedTerm; // the DICOM defined term for the charset
  const char *EscapeCode; // the ISO 2022 escape code for this charset
  const char *MIMEName; // the IANA mime name for the charset
};

//----------------------------------------------------------------------------
// This table gives the character sets that are defined in DICOM,
// plus additional legacy character sets of interest.
static const int CHARSET_TABLE_SIZE = 91;
static const CharsetInfo Charsets[91] = {
  { "ISO_IR_6",   "",           NULL, "US-ASCII" },
  { "ISO_IR_13",  "ISO_IR 13",  NULL, NULL }, // JIS_X0201 romaji + katakana
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { "ISO_IR_100", "ISO_IR 100", NULL, "ISO-8859-1" },
  { "ISO_IR_101", "ISO_IR 101", NULL, "ISO-8859-2" },
  { "ISO_IR_109", "ISO_IR 109", NULL, "ISO-8859-3" },
  { "ISO_IR_110", "ISO_IR 110", NULL, "ISO-8859-4" },
  { "ISO_IR_144", "ISO_IR 144", NULL, "ISO-8859-5" },
  { "ISO_IR_127", "ISO_IR 127", NULL, "ISO-8859-6" },
  { "ISO_IR_126", "ISO_IR 126", NULL, "ISO-8859-7" },
  { "ISO_IR_138", "ISO_IR 138", NULL, "ISO-8859-8" },
  { "ISO_IR_148", "ISO_IR 148", NULL, "ISO-8859-9" },
  { "latin6",     NULL,         NULL, "ISO-8859-10" },
  { "ISO_IR_166", "ISO_IR 166", NULL, "TIS-620" },
  { "latin7",     NULL,         NULL, "ISO-8859-13" },
  { "latin8",     NULL,         NULL, "ISO-8859-14" },
  { "ISO_IR_203", "ISO_IR 203", NULL, "ISO-8859-15" },
  { "latin10",    NULL,         NULL, "ISO-8859-16" },
  { NULL, NULL, NULL, NULL },
  { "euc-kr",     NULL,         NULL, "EUC-KR" },
  { "gb2312",     NULL,         NULL, "GB2312" },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { "ISO_2022_IR_6",   "ISO 2022 IR 6",   "(B", NULL }, // US-ASCII
  { "ISO_2022_IR_13",  "ISO 2022 IR 13",  "(J", NULL }, // JIS_X0201
  { "ISO_2022_IR_87", "\\ISO 2022 IR 87", "$B", "ISO-2022-JP" }, // JIS_X0208
  { "ISO_2022_IR_13_87", "ISO 2022 IR 13\\ISO 2022 IR 87", NULL, NULL },
  { "ISO_2022_IR_159", "\\ISO 2022 IR 159", "$(D", NULL }, // JIS_X0212
  { "ISO_2022_IR_13_159", "ISO 2022 IR 13\\ISO 2022 IR 159", NULL, NULL },
  { "ISO_2022_IR_87_159", "\\ISO 2022 IR 87\\ISO 2022 IR 159", NULL, NULL },
  { "ISO_2022_IR_13_87_159", "ISO 2022 IR 13\\ISO 2022 IR 87\\ISO 2022 IR 159",
    NULL, NULL },
  { "ISO_2022_IR_100", "ISO 2022 IR 100", "-A", NULL }, // ISO-8859-1
  { "ISO_2022_IR_101", "ISO 2022 IR 101", "-B", NULL }, // ISO-8859-2
  { "ISO_2022_IR_109", "ISO 2022 IR 109", "-C", NULL }, // ISO-8859-3
  { "ISO_2022_IR_110", "ISO 2022 IR 110", "-D", NULL }, // ISO-8859-4
  { "ISO_2022_IR_144", "ISO 2022 IR 144", "-L", NULL }, // ISO-8859-5
  { "ISO_2022_IR_127", "ISO 2022 IR 127", "-G", NULL }, // ISO-8859-6
  { "ISO_2022_IR_126", "ISO 2022 IR 126", "-F", NULL }, // ISO-8859-7
  { "ISO_2022_IR_138", "ISO 2022 IR 138", "-H", NULL }, // ISO-8859-8
  { "ISO_2022_IR_148", "ISO 2022 IR 148", "-M", NULL }, // ISO-8859-9
  { "iso-2022-latin6", NULL,              "-V", NULL }, // ISO-8859-10
  { "ISO_2022_IR_166", "ISO 2022 IR 166", "-T", NULL }, // TIS-620
  { "iso-2022-latin7", NULL,              "-Y", NULL }, // ISO-8859-13
  { "iso-2022-latin8", NULL,              "-_", NULL }, // ISO-8859-14
  { "ISO_2022_IR_203", "ISO 2022 IR 203", "-b", NULL }, // ISO-8859-15
  { "iso-2022-latin10", NULL,             "-f", NULL }, // ISO-8859-16
  { NULL, NULL, NULL, NULL },
  { "ISO_2022_IR_149", "\\ISO 2022 IR 149", "$)C", NULL }, // ~ISO-2022-KR
  { "ISO_2022_IR_58",  "\\ISO 2022 IR 58",  "$)A", NULL }, // ~ISO-2022-CN
  { "iso-2022-jp",     NULL,              NULL, "ISO-2022-JP" },
  { "iso-2022-jp-1",   NULL,              NULL, NULL },
  { "iso-2022-jp-2",   NULL,              NULL, "ISO-2022-JP-2" },
  { "iso-2022-jp-ext", NULL,              NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { "ISO_IR_192", "ISO_IR 192", NULL, "UTF-8" },
  { "GB18030",  "GB18030", NULL, "GB18030" },
  { "GBK",      "GBK",     NULL, "GBK" }, // subset of GB18030
  { "big5",     NULL,      NULL, "Big5" }, // ETEN, but no hkscs
  { NULL, NULL, NULL, NULL },
  { "euc-jp",   NULL,      NULL, "EUC-JP" },
  { "sjis",     NULL,      NULL, "Shift_JIS" },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { "cp874",    NULL, NULL, "windows-874" }, // thai
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { NULL, NULL, NULL, NULL },
  { "cp1250",   NULL, NULL, "windows-1250" }, // central europe
  { "cp1251",   NULL, NULL, "windows-1251" }, // cyrillic
  { "cp1252",   NULL, NULL, "windows-1252" }, // western europe
  { "cp1253",   NULL, NULL, "windows-1253" }, // greek
  { "cp1254",   NULL, NULL, "windows-1254" }, // turkish
  { "cp1255",   NULL, NULL, "windows-1255" }, // hebrew
  { "cp1256",   NULL, NULL, "windows-1256" }, // arabic
  { "cp1257",   NULL, NULL, "windows-1257" }, // baltic rim
  { "cp1258",   NULL, NULL, "windows-1258" }, // vietnamese
  { NULL, NULL, NULL, NULL },
  { "koi8",     NULL, NULL, "KOI8-U" }, // text only, no boxes
};

//----------------------------------------------------------------------------
//! This is a class for compressed lookup tables.
class CompressedTable
{
public:
  CompressedTable(const unsigned short *table) : M(table[0]), N(table[M+1]),
    HTable(table+1), LTable(HTable + M+1) {}

  //! Use table to convert "x", return RCHAR if "x" not in table.
  unsigned short operator[](unsigned short x)
  {
    // uptr will indicate the table range that "x" sits within,
    // i.e. we want uptr[0] <= x < uptr[1]
    const unsigned short *uptr;

    // check "hot" parts of the lookup table first with HTable
    for (size_t k = 0; k < M; k++)
    {
      uptr = LTable + HTable[k];
      if (x >= *uptr)
      {
        uptr++;
        if (uptr == LTable+N || x < *uptr)
        {
          // if found, skip the std::upper_bound() search
          goto found;
        }
      }
    }

    // use upper_bound to search LTable
    uptr = std::upper_bound(LTable, LTable+N, x);

  found:
    // we have uptr+1, where uptr[0] <= x < uptr[1]
    uptr--;

    // check if "x" is within a linearly compressed range
    unsigned short y = uptr[N];
    if (y != RCHAR)
    {
      // this part of the table is compressed as a linear offset
      y += x - *uptr;
    }
    else
    {
      // check if "x" is within an uncompressed range
      y = uptr[2*N];
      if (y != RCHAR)
      {
        // this part of the table is uncompressed, use DTable
        y += x - *uptr;
        y = LTable[3*N + y];
      }
    }

    return y;
  }

  //! Get the sub-table that starts at index "x" (no checks)
  const unsigned short *GetBlock(unsigned short x)
  {
    const unsigned short *uptr = 0;
    for (size_t k = 0; k < M; k++)
    {
      uptr = LTable + HTable[k];
      if (*uptr == x)
      {
        break;
      }
    }
    unsigned short y = uptr[2*N] + (x - uptr[0]);
    return &LTable[3*N + y];
  }

private:
  size_t M; // number of "hot" ranges declared for table
  size_t N; // total number of regions declared for table
  const unsigned short *HTable; // list of M values to define hot regions
  const unsigned short *LTable; // list of all regions
};

//----------------------------------------------------------------------------
// For reversed tables, accept an "unsigned int" index, since unicode
// is too large for "unsigned short".
class CompressedTableR
{
public:
  CompressedTableR(const unsigned short *table) : Table(table) {}
  unsigned short operator[](unsigned int x);

private:
  CompressedTable Table;
};

unsigned short CompressedTableR::operator[](unsigned int x)
{
  if (x <= 0xFFFD)
  {
    return this->Table[static_cast<unsigned short>(x)];
  }
  return 0xFFFD;
}

//----------------------------------------------------------------------------
// For reversed JIS X 0208/0212 table, include one compatibility
// code that is beyond the BMP
class CompressedTableJISXR
{
public:
  CompressedTableJISXR(const unsigned short *table) : Table(table) {}
  unsigned short operator[](unsigned int x);

private:
  CompressedTable Table;
};

unsigned short CompressedTableJISXR::operator[](unsigned int x)
{
  if (x <= 0xFFFD)
  {
    return this->Table[static_cast<unsigned short>(x)];
  }
  if (x == 0x20B9F) // jouyou kanji that is outside BMP
  {
    return 2561;
  }
  return 0xFFFD;
}

//----------------------------------------------------------------------------
// Convert a unicode code point to UTF-8
inline void UnicodeToUTF8(unsigned int code, std::string *s)
{
  if (code <= 0x007F)
  {
    s->push_back(code);
  }
  else if (code <= 0x07FF)
  {
    s->push_back(0xC0 | (code >> 6));
    s->push_back(0x80 | (code & 0x3F));
  }
  else if (code <= 0xFFFF)
  {
    s->push_back(0xE0 | (code >> 12));
    s->push_back(0x80 | ((code >> 6) & 0x3F));
    s->push_back(0x80 | (code & 0x3F));
  }
  else if (code <= 0x10FFFF)
  {
    s->push_back(0xF0 | (code >> 18));
    s->push_back(0x80 | ((code >> 12) & 0x3F));
    s->push_back(0x80 | ((code >> 6) & 0x3F));
    s->push_back(0x80 | (code & 0x3F));
  }
  else
  {
    // indicate bad code with U+FFFD
    s->push_back(0xEF);
    s->push_back(0xBF);
    s->push_back(0xBD);
  }
}

//----------------------------------------------------------------------------
// Convert one UTF8-encoded character to Unicode.
// If UTF8 sequence is malformed, return 0xFFFF.
// If UTF8 sequence at end of input is incomplete, return 0xFFFE.
// Paired encoded UTF-16 surrogates are combined to create one code.
unsigned int UTF8ToUnicode(const char **cpp, const char *cpEnd)
{
  const unsigned char *cp = reinterpret_cast<const unsigned char *>(*cpp);
  const unsigned char *ep = reinterpret_cast<const unsigned char *>(cpEnd);
  unsigned int code = 0;
  if (cp != ep)
  {
    code = *cp++;
  }

  // check for non-ASCII
  if ((code & 0x80) != 0)
  {
    ptrdiff_t good = 0;
    if ((code & 0xE0) == 0xC0)
    {
      // 2 bytes, 0x0080 to 0x07FF
      code &= 0x1F;
      code <<= 6;
      good = ((code & 0x0780) != 0);
      if (good)
      {
        good = -1;
        if (cp != ep)
        {
          unsigned int s = *cp;
          good = ((s & 0xC0) == 0x80);
          cp += good;
          code |= (s & 0x3F);
        }
      }
    }
    else if ((code & 0xF0) == 0xE0)
    {
      // 3 bytes, 0x0800 to 0xFFFF
      good = -1;
      if (cp != ep)
      {
        code &= 0x0F;
        code <<= 6;
        unsigned int s = *cp;
        good = ((code | (s & 0x20)) != 0);
        good &= ((s & 0xC0) == 0x80);
        if (good)
        {
          good = -1;
          cp++;
          code |= (s & 0x3F);
          code <<= 6;
          if (cp != ep)
          {
            s = *cp;
            good = ((s & 0xC0) == 0x80);
            cp += good;
            code |= (s & 0x3F);
            // is this a utf-16 surrogate?
            if ((code & 0xF800) == 0xD800 && good)
            {
              good = 0;
              // is it a high surrogate?
              if ((code & 0xFC00) == 0xD800)
              {
                // is it followed by a low surrogate?
                if (cp == ep)
                {
                  good = -1;
                }
                else if (cp[0] == 0xED)
                {
                  if (cp+1 == ep)
                  {
                    good = -1;
                  }
                  else if ((cp[1] & 0xF0) == 0xB0)
                  {
                    if (cp+2 == ep)
                    {
                      good = -1;
                    }
                    else if ((cp[2] & 0xC0) == 0x80)
                    {
                      // 6 bytes for paired surrogates
                      good = 1;
                      code &= 0x03FF;
                      code <<= 4;
                      code |= cp[1] & 0x0F;
                      code <<= 6;
                      code |= cp[2] & 0x3F;
                      code += 0x010000;
                      cp += 3;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else if ((code & 0xF8) == 0xF0)
    {
      // 4 bytes, 0x010000 to 0x10FFFF
      good = -1;
      if (cp != ep)
      {
        code &= 0x07;
        code <<= 6;
        unsigned int s = *cp;
        good = ((code | (s & 0x30)) != 0);
        good &= ((s & 0xC0) == 0x80);
        if (good)
        {
          good = -1;
          cp++;
          if (cp != ep)
          {
            code |= (s & 0x3F);
            code <<= 6;
            s = *cp;
            good = ((s & 0xC0) == 0x80);
            if (good)
            {
              good = -1;
              cp++;
              if (cp != ep)
              {
                code |= (s & 0x3F);
                code <<= 6;
                s = *cp;
                good = ((s & 0xC0) == 0x80);
                cp += good;
                code |= (s & 0x3F);
                good &= (code <= 0x10FFFF);
              }
            }
          }
        }
      }
    }

    if (good == 0)
    {
      // improperly formed character
      code = 0xFFFF;
    }
    else if (good < 0)
    {
      // premature termination of string
      code = 0xFFFE;
    }
  }

  *cpp = reinterpret_cast<const char *>(cp);
  return code;
}

//----------------------------------------------------------------------------
// Check if "code" is represented by the utf-8 sequence starting at  "cpp"
// and ending at "cpEnd".  This is meant to be used when UTF8ToUnicode()
// returns 0xFFFE or 0xFFFF, in order to check whether they were returned
// as error indicators or whether they were actually present in the string.
bool IsFFFX(unsigned int code, const char *cpp, const char *cpEnd)
{
  return (cpEnd - cpp == 3 &&
          static_cast<unsigned char>(cpp[0]) == 0xef &&
          static_cast<unsigned char>(cpp[1]) == 0xbf &&
          static_cast<unsigned char>(cpp[2]) == (code ^ 0xFF40));
}

//----------------------------------------------------------------------------
// Different ways to handle failed conversions:
// The "ESCAPE" is like Python's surrogatescape mode, it only applies
// to conversions to UTF-8
enum {
  UTF8_STRICT,  // For error checking, replace with <XX> or <U+XXXX>.
  UTF8_REPLACE, // Replace with '?' or unicode REPLACEMENT CHARACTER.
  UTF8_ESCAPE   // Use unpaired surrogates to store unconverted bytes
};

// This is a handler for incorrectly encoded characters
void BadCharsToUTF8(const char *cp, const char *ep, std::string *s,
                    int mode)
{
  if (mode == UTF8_STRICT)
  {
    // Replace each unconvertible sequence with <XX> hex char code
    char text[8];
    while (cp != ep)
    {
      unsigned int code = static_cast<unsigned char>(*cp);
      snprintf(text, sizeof(text), "<%02X>", code);
      s->append(text);
      cp++;
    }
  }
  else if (mode == UTF8_REPLACE)
  {
    // Replace each unconvertible sequence with the replacement character
    const unsigned int code = 0xFFFD;
    UnicodeToUTF8(code, s);
  }
  else if (mode == UTF8_ESCAPE)
  {
    // Store unconvertible characters as UTF-16 low surrogates.
    // These surrogates are invalid UTF-8 codes, but they can be
    // recognized and used for diagnostic purposes.
    while (cp != ep)
    {
      unsigned int code = 0xDC00 + static_cast<unsigned char>(*cp);
      UnicodeToUTF8(code, s);
      cp++;
    }
  }
}

//----------------------------------------------------------------------------
// Convert a string to its lower-case equivalent.
void CaseFoldUnicode(unsigned int code, std::string *s)
{
  // This has been tested against the Unicode CaseFolding.txt
  // published on 2015-01-13 for Unicode 8.
  unsigned int code2 = 0;
  unsigned int code3 = 0;

  if (code <= 0x7f)
  {
    if (code >= 'A' && code <= 'Z')
    { // ascii uppercase -> ascii lowercase
      code += 0x20;
    }
  }
  else if (code <= 0xff)
  {
    if (code >= 0xC0 && code <= 0xDE && code != 0xD7)
    { // latin1 uppercase -> latin1 lowercase
      code += 0x20;
    }
    else if (code == 0xDF)
    { // latin1 s-sharp -> lowercase ss
      code = 's';
      code2 = 's';
    }
    else if (code == 0xB5)
    { // latin1 micron -> greek lowercase mu
      code = 0x03BC;
    }
  }
  else if (code <= 0x017f)
  {
    if (code >= 0x0100 && code <= 0x012F)
    { // various accented latin characters
      code |= 0x0001;
    }
    else if (code == 0x0130)
    { // I with dot becomes lowercase i
      code = 'i';
      code2 = 0x0307;
    }
    else if (code >= 0x0132 && code <= 0x0137)
    { // IJ and various accented latin characters
      code |= 0x0001;
    }
    else if (code >= 0x139 && code <= 0x148)
    { // various accented latin characters
      code += (code & 0x0001);
    }
    else if (code == 0x0149)
    { // 'n -> two separate characters
      code = 0x02BC;
      code2 = 'n';
    }
    else if (code >= 0x014A && code <= 0x0177)
    { // eng and various accented latin characters
      code |= 0x0001;
    }
    else if (code == 0x0178)
    { // uppercase y with diaeresis becomes lowercase y with diaeresis
      code = 0xFF;
    }
    else if (code >= 0x0179 && code <= 0x017E)
    { // various accented latin characters
      code += (code & 0x0001);
    }
    else if (code == 0x017F)
    { // long s -> lowercase s
      code = 's';
    }
  }
  else if (code <= 0x036f)
  { // yet more latin with accents
    if (code >= 0x0180 && code <= 0x01CA)
    {
      const static unsigned short table[75] = {
        0x0180, 0x0253, 0x0183, 0x0183, 0x0185, 0x0185, 0x0254, 0x0188,
        0x0188, 0x0256, 0x0257, 0x018C, 0x018C, 0x018D, 0x01DD, 0x0259,
        0x025B, 0x0192, 0x0192, 0x0260, 0x0263, 0x0195, 0x0269, 0x0268,
        0x0199, 0x0199, 0x019A, 0x019B, 0x026F, 0x0272, 0x019E, 0x0275,
        0x01A1, 0x01A1, 0x01A3, 0x01A3, 0x01A5, 0x01A5, 0x0280, 0x01A8,
        0x01A8, 0x0283, 0x01AA, 0x01AB, 0x01AD, 0x01AD, 0x0288, 0x01B0,
        0x01B0, 0x028A, 0x028B, 0x01B4, 0x01B4, 0x01B6, 0x01B6, 0x0292,
        0x01B9, 0x01B9, 0x01BA, 0x01BB, 0x01BD, 0x01BD, 0x01BE, 0x01BF,
        0x01C0, 0x01C1, 0x01C2, 0x01C3, 0x01C6, 0x01C6, 0x01C6, 0x01C9,
        0x01C9, 0x01C9, 0x01CC };

      code = table[code - 0x0180];
    }
    else if (code >= 0x01CB && code <= 0x01DC)
    {
      code += (code & 0x0001);
    }
    else if (code >= 0x01DE && code <= 0x01EF)
    {
      code |= 0x0001;
    }
    else if (code == 0x01F0)
    {
      code = 0x006A;
      code2 = 0x030C;
    }
    else if (code >= 0x01F0 && code <= 0x024F)
    {
      const static unsigned short table[96] = {
        0x01F0, 0x01F3, 0x01F3, 0x01F3, 0x01F5, 0x01F5, 0x0195, 0x01BF,
        0x01F9, 0x01F9, 0x01FB, 0x01FB, 0x01FD, 0x01FD, 0x01FF, 0x01FF,
        0x0201, 0x0201, 0x0203, 0x0203, 0x0205, 0x0205, 0x0207, 0x0207,
        0x0209, 0x0209, 0x020B, 0x020B, 0x020D, 0x020D, 0x020F, 0x020F,
        0x0211, 0x0211, 0x0213, 0x0213, 0x0215, 0x0215, 0x0217, 0x0217,
        0x0219, 0x0219, 0x021B, 0x021B, 0x021D, 0x021D, 0x021F, 0x021F,
        0x019E, 0x0221, 0x0223, 0x0223, 0x0225, 0x0225, 0x0227, 0x0227,
        0x0229, 0x0229, 0x022B, 0x022B, 0x022D, 0x022D, 0x022F, 0x022F,
        0x0231, 0x0231, 0x0233, 0x0233, 0x0234, 0x0235, 0x0236, 0x0237,
        0x0238, 0x0239, 0x2C65, 0x023C, 0x023C, 0x019A, 0x2C66, 0x023F,
        0x0240, 0x0242, 0x0242, 0x0180, 0x0289, 0x028C, 0x0247, 0x0247,
        0x0249, 0x0249, 0x024B, 0x024B, 0x024D, 0x024D, 0x024F, 0x024F };

      code = table[code - 0x01F0];
    }
    else if (code == 0x0345)
    { // combining greek ypogegrammeni
      code = 0x03B9;
    }
  }
  else if (code <= 0x03ff)
  {
    // greek characters
    if (code >= 0x0370 && code <= 0x038F)
    {
      const static unsigned short table[32] = {
        0x0371, 0x0371, 0x0373, 0x0373, 0x0374, 0x0375, 0x0377, 0x0377,
        0x0378, 0x0379, 0x037A, 0x037B, 0x037C, 0x037D, 0x037E, 0x03F3,
        0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x03AC, 0x0387,
        0x03AD, 0x03AE, 0x03AF, 0x038B, 0x03CC, 0x038D, 0x03CD, 0x03CE };

      code = table[code - 0x0370];
    }
    else if ((code >= 0x0391 && code <= 0x03A1) ||
             (code >= 0x03A3 && code <= 0x03AB))
    {
      code += 0x20;
    }
    else if (code == 0x0390)
    {
      code = 0x03B9;
      code2 = 0x0308;
      code3 = 0x0301;
    }
    else if (code == 0x03B0)
    {
      code = 0x03C5;
      code2 = 0x0308;
      code3 = 0x0301;
    }
    else if (code == 0x03C2)
    {
      code += 0x01;
    }
    else if (code >= 0x03CF && code <= 0x03D6)
    {
      const static unsigned short table[8] = {
        0x03D7, 0x03B2, 0x03B8, 0x03D2, 0x03D3, 0x03D4, 0x03C6, 0x03C0 };

      code = table[code - 0x03CF];
    }
    else if (code >= 0x03D8 && code <= 0x03EF)
    {
      code |= 0x0001;
    }
    else if (code >= 0x03F0 && code <= 0x03FF)
    {
      const static unsigned short table[16] = {
        0x03BA, 0x03C1, 0x03F2, 0x03F3, 0x03B8, 0x03B5, 0x03F6, 0x03F8,
        0x03F8, 0x03F2, 0x03FB, 0x03FB, 0x03FC, 0x037B, 0x037C, 0x037D };

      code = table[code - 0x03F0];
    }
  }
  else if (code <= 0x052f)
  { // cyrillic
    if (code >= 0x0400 && code <= 0x040F)
    {
      code += 0x50;
    }
    else if (code >= 0x0410 && code <= 0x042F)
    {
      code += 0x20;
    }
    else if ((code >= 0x0460 && code <= 0x0481) ||
             (code >= 0x048A && code <= 0x04BF))
    {
      code |= 0x0001;
    }
    else if (code == 0x04C0)
    {
      code = 0x04CF;
    }
    else if (code >= 0x04C1 && code <= 0x04CE)
    {
      code += (code & 0x0001);
    }
    else if (code >= 0x04D0 && code <= 0x052F)
    {
      code |= 0x0001;
    }
  }
  else if (code <= 0x1000)
  { // armenian
    if (code >= 0x0531 && code <= 0x0556)
    {
      code += 0x30;
    }
    else if (code == 0x0587)
    {
      code = 0x0565;
      code2 = 0x0582;
    }
  }
  else if (code <= 0x13ff)
  {
    if ((code >= 0x10A0 && code <= 0x10C5) ||
        code == 0x10C7 || code == 0x10CD)
    { // georgian
      code += 0x1C60;
    }
    else if (code >= 0x13F8 && code <= 0x13FD)
    { // cherokee
      code -= 0x08;
    }
  }
  else if (code <= 0x1eff)
  { // vietnamese and other latin
    if (code >= 0x1E00 && code <= 0x1E95)
    {
      code |= 0x0001;
    }
    else if (code >= 0x1E96 && code <= 0x1E9B)
    {
      const static unsigned short table[6] = {
        'h',    't',    'w',    'y',    'a',    0x1E61 };
      const static unsigned short table2[6] = {
        0x0331, 0x0308, 0x030A, 0x030A, 0x02BE, 0,     };

      code2 = table2[code - 0x1E96];
      code = table[code - 0x1E96];
    }
    else if (code == 0x1E9E)
    { // capital s-sharp -> ss
      code = 's';
      code2 = 's';
    }
    else if (code >= 0x1EA0 && code <= 0x1EFE)
    {
      code |= 0x0001;
    }
  }
  else if (code <= 0x1fff)
  {
    // rare greek
    if ((code >= 0x1F08 && code <= 0x1F0F) ||
        (code >= 0x1F18 && code <= 0x1F1D) ||
        (code >= 0x1F28 && code <= 0x1F2F) ||
        (code >= 0x1F38 && code <= 0x1F3F) ||
        (code >= 0x1F48 && code <= 0x1F4D))
    {
      code -= 0x08;
    }
    else if (code >= 0x1F50 && code <= 0x1F56 && (code & 0x1) == 0)
    {
      const static unsigned short table3[7] = {
        0, 0, 0x0300, 0, 0x0301, 0, 0x0342 };

      code3 = table3[code - 0x1F50];
      code2 = 0x0313;
      code = 0x03C5;
    }
    else if ((code >= 0x1F59 && code <= 0x1F5F && (code & 0x1) != 0) ||
             (code >= 0x1F68 && code <= 0x1F6F))
    {
      code -= 0x08;
    }
    else if (code >= 0x1F80 && code <= 0x1FAF)
    {
      code2 = 0x03B9;
      if (code <= 0x1F87) { code -= 0x80; }
      else if (code <= 0x1F8F) { code -= 0x88; }
      else if (code <= 0x1F97) { code -= 0x70; }
      else if (code <= 0x1F9F) { code -= 0x78; }
      else if (code <= 0x1FA7) { code -= 0x40; }
      else { code -= 0x48; }
    }
    else if (code >= 0x1FB2 && code <= 0x1FFC)
    {
      const static unsigned short table[75] = {
        0x1F70, 0x03B1, 0x03AC, 0x1FB5, 0x03B1, 0x03B1, 0x1FB0, 0x1FB1,
        0x1F70, 0x1F71, 0x03B1, 0x1FBD, 0x03B9, 0x1FBF, 0x1FC0, 0x1FC1,
        0x1F74, 0x03B7, 0x03AE, 0x1FC5, 0x03B7, 0x03B7, 0x1F72, 0x1F73,
        0x1F74, 0x1F75, 0x03B7, 0x1FCD, 0x1FCE, 0x1FCF, 0x1FD0, 0x1FD1,
        0x03B9, 0x03B9, 0x1FD4, 0x1FD5, 0x03B9, 0x03B9, 0x1FD0, 0x1FD1,
        0x1F76, 0x1F77, 0x1FDC, 0x1FDD, 0x1FDE, 0x1FDF, 0x1FE0, 0x1FE1,
        0x03C5, 0x03C5, 0x03C1, 0x1FE5, 0x03C5, 0x03C5, 0x1FE0, 0x1FE1,
        0x1F7A, 0x1F7B, 0x1FE5, 0x1FED, 0x1FEE, 0x1FEF, 0x1FF0, 0x1FF1,
        0x1F7C, 0x03C9, 0x03CE, 0x1FF5, 0x03C9, 0x03C9, 0x1F78, 0x1F79,
        0x1F7C, 0x1F7D, 0x03C9 };

      if (code <= 0x1FB4 ||
          code == 0x1FBC || (code >= 0x1FC2 && code <= 0x1FC4) ||
          code == 0x1FCC || (code >= 0x1FF2 && code <= 0x1FF4) ||
          code == 0x1FFC)
      {
        code2 = 0x03B9;
      }
      else if (code == 0x1FB6 || code == 0x1FC6 || code == 0x1FD6 ||
               code == 0x1FE6 || code == 0x1FF6)
      {
        code2 = 0x0342;
      }
      else if (code == 0x1FB6 || code == 0x1FB7 || code == 0x1FC7 ||
               code == 0x1FF7)
      {
        code2 = 0x0342;
        code3 = 0x03B9;
      }
      else if (code >= 0x1FD2 && code <= 0x1FD3)
      {
        code2 = 0x0308;
        code3 = code - (0x1FD2 - 0x0300);
      }
      else if (code == 0x1FD7 || code == 0x1FE7)
      {
        code2 = 0x0308;
        code3 = 0x0342;
      }
      else if (code >= 0x1FE2 && code <= 0x1FE3)
      {
        code2 = 0x0308;
        code3 = code - (0x1FE2 - 0x0300);
      }
      else if (code == 0x1FE4)
      {
        code2 = 0x0313;
      }

      code = table[code - 0x1FB2];
    }
  }
  else if (code <= 0x24ff)
  { // symbols
    if (code == 0x2126)
    { // Ohm symbol becomes omega
      code = 0x03C9;
    }
    else if (code == 0x212A)
    { // Kelvin symbol becomes k
      code = 'k';
    }
    else if (code == 0x212B)
    { // Angstrom symbol becomes a with circle
      code = 0xE5;
    }
    else if (code == 0x2132)
    {
      code = 0x214E;
    }
    else if (code >= 0x2160 && code <= 0x216F)
    {
      code += 0x10;
    }
    else if (code == 0x2183)
    {
      code += 0x01;
    }
    else if (code >= 0x24B6 && code <= 0x24CF)
    {
      code += 0x1a;
    }
  }
  else if (code <= 0x2cff)
  {
    if (code >= 0x2C00 && code <= 0x2C2E)
    { // glagolitic
      code += 0x30;
    }
    else if (code >= 0x2C60 && code <= 0x2C7F)
    { // rare latin
      const static unsigned short table[32] = {
        0x2C61, 0x2C61, 0x026B, 0x1D7D, 0x027D, 0x2C65, 0x2C66, 0x2C68,
        0x2C68, 0x2C6A, 0x2C6A, 0x2C6C, 0x2C6C, 0x0251, 0x0271, 0x0250,
        0x0252, 0x2C71, 0x2C73, 0x2C73, 0x2C74, 0x2C76, 0x2C76, 0x2C77,
        0x2C78, 0x2C79, 0x2C7A, 0x2C7B, 0x2C7C, 0x2C7D, 0x023F, 0x0240 };

      code = table[code - 0x2C60];
    }
    else if (code >= 0x2C80 && code <= 0x2CF3)
    { // coptic
      if (code <= 0x2CE3)
      {
        code |= 0x0001;
      }
      else if (code == 0x2CEB || code == 0x2CED || code == 0x2CF2)
      {
        code += 0x0001;
      }
    }
  }
  else if (code <= 0x9fff)
  {
    // cjk ideograms
  }
  else if (code <= 0xabff)
  {
    if ((code >= 0xA640 && code <= 0xA66D) ||
        (code >= 0xA680 && code <= 0xA69B))
    { // rare cyrillic
      code |= 0x0001;
    }
    else if (code >= 0xA722 && code <= 0xA76F && code != 0xA730)
    { // rare latin
      code |= 0x0001;
    }
    else if (code >= 0xA779 && code <= 0xA77C)
    {
      code += (code & 0x0001);
    }
    else if (code == 0xA77D)
    {
      code = 0x1D79;
    }
    else if (code >= 0xA77E && code <= 0xA787)
    {
      code |= 0x0001;
    }
    else if (code == 0xA78B)
    {
      code += 0x0001;
    }
    else if (code == 0xA78D)
    {
      code = 0x0265;
    }
    else if (code >= 0xA790 && code <= 0xA7A9 && code != 0xA794)
    {
      code |= 0x0001;
    }
    else if (code >= 0xA7AA && code <= 0xA7B6)
    {
      const static unsigned short table[13] = {
        0x0266, 0x025C, 0x0261, 0x026C, 0xA7AE, 0xA7AF, 0x029E, 0x0287,
        0x029D, 0xAB53, 0xA7B5, 0xA7B5, 0xA7B7 };
      code = table[code - 0xA7AA];
    }
    else if (code >= 0xAB70 && code <= 0xABBF)
    { // cherokee
      code -= 0x97D0;
    }
  }
  else if (code <= 0xfaff)
  {
    // hangul, cjk, private use
  }
  else if (code <= 0xfbff)
  {
    if (code >= 0xFB00 && code <= 0xFB06)
    { // latin ligatures
      if (code <= 0xFB04)
      {
        if (code == 0xFB01)
        {
          code2 = 'i';
        }
        else if (code == 0xFB02)
        {
          code2 = 'l';
        }
        else
        {
          code2 = 'f';
          if (code == 0xFB03)
          {
            code3 = 'i';
          }
          else if (code == 0xFB04)
          {
            code3 = 'l';
          }
        }
        code = 'f';
      }
      else if (code <= 0xFB06)
      {
        code = 's';
        code2 = 't';
      }
    }
    else if (code >= 0xFB13 && code <= 0xFB17)
    { // armenian ligatures
      const static unsigned short table[5] = {
        0x0574, 0x0574, 0x0574, 0x057E, 0x0574 };
      const static unsigned short table2[5] = {
        0x0576, 0x0565, 0x056B, 0x0576, 0x056D };

      code2 = table2[code - 0xFB13];
      code = table[code - 0xFB13];
    }
  }
  else if (code <= 0xffff)
  {
    if (code >= 0xFF21 && code <= 0xFF3A)
    { // wide latin uppercase -> wide latin lowercase
      code += 0x20;
    }
  }
  else
  {
    if (code >= 0x10400 && code <= 0x10427 )
    {
      code += 0x28;
    }
    else if (code >= 0x10C80 && code <= 0x10CB2)
    {
      code += 0x40;
    }
    else if (code >= 0x118A0 && code <= 0x118BF)
    {
      code += 0x20;
    }
  }

  UnicodeToUTF8(code, s);

  if (code2)
  {
    UnicodeToUTF8(code2, s);

    if (code3)
    {
      UnicodeToUTF8(code3, s);
    }
  }
}

//----------------------------------------------------------------------------
size_t UTF8ToUTF8(const char *text, size_t l, std::string *s, int mode)
{
  // convert to unicode and back, this will insert U+FFFD
  // wherever a bad utf-8 sequence occurs
  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;

  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    // check for 0xFFFE and 0xFFFF invalid characters that were not present
    // in the original string, these are the error indicators
    if (code >= 0xFFFE && code <= 0xFFFF && !IsFFFX(code, lastpos, cp))
    {
      if (code == 0xFFFF || mode == UTF8_STRICT)
      {
        BadCharsToUTF8(lastpos, cp, s, mode);
        errpos = (errpos ? errpos : lastpos);
      }
      continue;
    }
    // check for paired utf-16 surrogates
    if (cp - lastpos == 6 && mode == UTF8_STRICT)
    {
      BadCharsToUTF8(lastpos, cp, s, mode);
      errpos = (errpos ? errpos : lastpos);
      continue;
    }
    UnicodeToUTF8(code, s);
  }
  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t ASCIIToUTF8(const char *text, size_t l, std::string *s, int mode)
{
  // count the number of bad characters
  const char *errpos = 0;
  size_t m = 0;
  for (size_t i = 0; i < l; i++)
  {
    m += static_cast<unsigned char>(text[i]) >> 7;
  }
  if (m == 0)
  {
    // pure ASCII is valid utf-8
    s->append(text, l);
  }
  else
  {
    // codes > 0x7f
    s->reserve(s->size() + l + 2*m);
    for (size_t i = 0; i < l; i++)
    {
      char c = text[i];
      if (static_cast<unsigned char>(c) <= 0x7f)
      {
        s->push_back(c);
      }
      else
      {
        BadCharsToUTF8(&text[i], &text[i+1], s, mode);
        errpos = (errpos ? errpos : &text[i]);
      }
    }
  }
  return (errpos ? errpos-text : l);
}

//----------------------------------------------------------------------------
size_t UnknownToUTF8(const char *text, size_t l, std::string *s, int mode)
{
  // assumes an iso2022 94-character replacement set
  const char *errpos = 0;
  size_t i = 0;
  while (i < l)
  {
    unsigned int code = static_cast<unsigned char>(text[i++]);
    if ((code >= 0x21 && code < 0x7F) || code > 0x7F)
    {
      BadCharsToUTF8(&text[i], &text[i+1], s, mode);
      errpos = (errpos ? errpos : &text[i]);
    }
    else
    {
      UnicodeToUTF8(code, s);
    }
  }
  return (errpos ? errpos-text : l);
}

//----------------------------------------------------------------------------
bool HandleReplacement(std::string *s, const char *cp, const char *ep,
                       int mode)
{
  // Handle unicode characters that don't exist in the target charset.
  // Also handle invalid utf-8 sequences.  The return value is "false"
  // for all replacement modes that have been implemented thus far.
  bool success = false;

  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    char text[24];
    const char *replacement = text;

    if (code < 0x20)
    {
      // consider C0 to be a bad bytes, not bad characters
      code = 0xFFFF;
    }

    if (mode == UTF8_STRICT)
    {
      // OxFFFE and 0xFFFF are UTF8ToUnicode error markers, but only if
      // they weren't present in the orginal utf-8 string
      if ((code == 0xFFFE || code == 0xFFFF) && !IsFFFX(code, lastpos, cp))
      {
        // show the bad bytes
        const char *bp = lastpos;
        for (size_t i = 0; bp != cp && i < sizeof(text); i += 4)
        {
          unsigned int x = static_cast<unsigned char>(*bp);
          snprintf(&text[i], sizeof(text) - i, "<%02X>", x);
          bp++;
        }
      }
      else
      {
        // show the code that did not convert
        snprintf(text, sizeof(text), "<U+%04X>", code);
      }
    }
    else
    {
      // default replacement character
      replacement = "?";
    }

    s->append(replacement);
  }

  return success;
}

// print a character escape code
void OctalCharCode(std::string *s, unsigned char c)
{
  char text[4];
  text[0] = '\\';
  text[1] = '0' + (c >> 6);
  text[2] = '0' + ((c >> 3) & 7);
  text[3] = '0' + (c & 7);
  s->append(text, 4);
}

// control characters that mark new line: NL VT FF CR
bool IsEndLine(char c)
{
  return (c >= '\n' && c <= '\r');
}

// set the position of the first decoding error
// (before decoding begins, initialize 'n' to the input buffer size)
void SetErrorPosition(size_t& n, size_t i)
{
  if (i < n)
  {
    n = i;
  }
}

// get length of an escape sequence (excluding the ESC character)
size_t EscapeCodeLength(const char *cp, size_t n)
{
  size_t l = 0;
  if (n > 0 && cp[0] == '[')
  {
    l++;
    while (l < n &&
           static_cast<unsigned char>(cp[l]) >= 0x30 &&
           static_cast<unsigned char>(cp[l]) <= 0x3F)
    {
      l++;
    }
  }
  while (l < n &&
         static_cast<unsigned char>(cp[l]) >= 0x20 &&
         static_cast<unsigned char>(cp[l]) <= 0x2F)
  {
    l++;
  }
  if (l < n &&
      static_cast<unsigned char>(cp[l]) >= 0x40 &&
      static_cast<unsigned char>(cp[l]) <= 0x7E)
  {
    l++;
  }
  else
  {
    l = 0;
  }
  return l;
}

// Search a table that gives ranges of invalid, valid codes
bool InvalidCode(const unsigned short *table, unsigned short t)
{
  size_t size = table[0];
  const unsigned short *tp = std::upper_bound(&table[1], &table[size], t);
  size_t offset = tp - table;
  return ((offset & 1) == 0);
}

// Invalid ranges for GB2312-1980
static const unsigned short GB2312InvalidRanges[30] = {
  30, 94, 110, 160, 162, 172, 174, 186, 188, 365, 376, 462,
  470, 494, 502, 526, 564, 597, 612, 645, 658, 684, 694, 731,
  755, 831, 1410, 5165, 5170, 8178
};

// Invalid ranges for GBK 1.0 (CP936 plus 95 additions, includes EUDC)
static const unsigned short GBKInvalidRanges[46] = {
  46, 104, 110, 160, 162, 172, 174, 186, 188, 365, 376, 462,
  470, 494, 502, 526, 533, 545, 547, 552, 553, 555, 564, 597,
  612, 645, 658, 690, 694, 731, 755, 831, 846, 5165, 5170,
  15673, 15684, 15708, 15709, 15711, 15712, 15713, 15716,
  15770, 15780, 23940
};

} // end anonymous namespace

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToSJIS(
  const char *text, size_t l, std::string *s, int mode)
{
  // windows-31j (the CP932 variant of shift-jis)
  CompressedTableJISXR table(vtkDICOMCharacterSet::Reverse[X_EUCJP]);
  CompressedTableR table2(vtkDICOMCharacterSet::Reverse[X_SJIS]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code < 0x80)
    {
      // windows-31j uses ASCII for these codes, not ISO-IR 14
      s->push_back(static_cast<char>(code));
      continue;
    }
    else if (code >= 0xFF61 && code <= 0xFF9F)
    {
      // half-width katakana maps to range 0xa1,0xdf like ISO-IR 13
      s->push_back(static_cast<char>(code - 0xFEC0));
      continue;
    }
    else
    {
      // Attempt to convert unicode character to JIS X 0208 or JIS X 0212
      // (if t < 8836, it is JIS X 0208, if t >= 8836, it is JIS X 0212)
      unsigned short t = table[code];
      if (t >= 8836)
      {
        // Since JIS X 0212 is not a part of shift-jis, try to convert
        // to a CP932 code instead
        t = table2[code];
      }
      if (t < 11280)
      {
        // Now apply the shift-jis math to generate two bytes
        unsigned char x = static_cast<unsigned char>(t / 94);
        unsigned char y = static_cast<unsigned char>(t % 94);
        if ((x & 1) == 0)
        {
          y += 0x40;
          if (y >= 0x7f) { y++; }
        }
        else
        {
          y += 0x9f;
        }
        x = 0x81 + x/2;
        if (x >= 0xa0) { x += 64; }
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
        continue;
      }
    }

    if (!HandleReplacement(s, lastpos, cp, mode))
    {
      errpos = (errpos ? errpos : lastpos);
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::SJISToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  // use the JIS X 0208 table with EUDC and CP 932 extensions
  CompressedTable table(vtkDICOMCharacterSet::Table[X_SJIS]);

  // windows-31j (shift-jis)
  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    char c = *cp++;
    if ((c & 0x80) == 0)
    {
      s->push_back(c); // ascii
    }
    else
    {
      unsigned int code = 0xFFFD;
      unsigned short x = static_cast<unsigned char>(c);

      if (x >= 0xA1 && x <= 0xDF)
      {
        code = x + 0xFEC0; // half-width katakana
      }
      else if (x != 0x80 && x != 0xA0 && x <= 0xFC && cp != ep)
      {
        // get second byte of a two-byte Shift-JIS sequence
        unsigned short y = static_cast<unsigned char>(*cp);
        if (y >= 0x40 && y <= 0xFC && y != 0x7F)
        {
          unsigned short a, b;
          if (y < 0x9F)
          {
            a = 0;
            b = y - (y < 0x7F ? 0x40 : 0x41);
          }
          else
          {
            a = 1;
            b = y - 0x9F;
          }

          if (x <= 0x9F)
          {
            a += (x - 0x81)*2;
          }
          else
          {
            a += (x - 0xC1)*2;
          }

          code = table[a*94+b];
          cp++;

          if (x == 0x81)
          {
            // substitutions to get correct code page 932 values
            switch (y)
            {
              case 0x5C: code = 0x2015; break; // HORIZONTAL BAR
              case 0x5F: code = 0xFF3C; break; // FULLWIDTH REVERSE SOLIDUS
              case 0x60: code = 0xFF5E; break; // FULLWIDTH TILDE
              case 0x61: code = 0x2225; break; // PARALLEL TO
              case 0x7C: code = 0xFF0D; break; // FULLWIDTH HYPHEN-MINUS
              case 0x91: code = 0xFFE0; break; // FULLWIDTH CENT SIGN
              case 0x92: code = 0xFFE1; break; // FULLWIDTH POUND SIGN
              case 0xCA: code = 0xFFE2; break; // FULLWIDTH NOT SIGN
            }
          }
        }
      }

      if (code == 0xFFFD)
      {
        BadCharsToUTF8(lastpos, cp, s, mode);
        errpos = (errpos ? errpos : lastpos);
      }
      else
      {
        UnicodeToUTF8(code, s);
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToEUCJP(
  const char *text, size_t l, std::string *s, int mode)
{
  CompressedTableJISXR table(vtkDICOMCharacterSet::Reverse[X_EUCJP]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code < 0x80)
    {
      s->push_back(static_cast<char>(code));
      continue;
    }
    else if (code >= 0xFF61 && code <= 0xFF9F)
    {
      // half-width katakana, as used by ISO-IR 13, a prefix byte 0x8e
      s->push_back(0x8e);
      s->push_back(static_cast<char>(code - 0xFEC0));
      continue;
    }
    else
    {
      // The table maps unicode to JIS X 0208 (0 <= t < 8836) or to
      // JIS X 0212 (8836 <= t < 2*8836), or to unknown (t >= 2*8836)
      unsigned short t = table[code];
      if (t < 2*8836)
      {
        if (t >= 8836)
        {
          // JIS X 0212 needs a 0x8f prefix byte in EUC-JP
          // (in the absence of a prefix byte, JIS X 0208 is assumed)
          s->push_back(0x8f);
          t -= 8836;
        }
        s->push_back(static_cast<char>(0xA1 + t / 94));
        s->push_back(static_cast<char>(0xA1 + t % 94));
        continue;
      }
    }

    if (!HandleReplacement(s, lastpos, cp, mode))
    {
      errpos = (errpos ? errpos : lastpos);
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::EUCJPToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  // UNIX encoding of JIS X 0201, JIS X 0208, and JIS X 0212
  CompressedTable jisx0208(vtkDICOMCharacterSet::Table[ISO_2022_IR_87]);
  CompressedTable jisx0212(vtkDICOMCharacterSet::Table[ISO_2022_IR_159]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    char c = *cp++;
    if ((c & 0x80) == 0)
    {
      s->push_back(c); // ascii
    }
    else
    {
      unsigned int code = 0xFFFD;
      unsigned short x = static_cast<unsigned char>(c);

      if (x >= 0x80 && x < 0xFF && cp != ep)
      {
        unsigned short y = static_cast<unsigned char>(*cp);
        if (y >= 0xA1 && y < 0xFF)
        {
          if (x >= 0xA1 && x < 0xFF) // JIS X 0208
          {
            code = jisx0208[(x - 0xA1)*94 + (y - 0xA1)];
            cp++;
          }
          else if (x == 0x8F) // JIS X 0212
          {
            if (cp+1 == ep)
            {
              break;
            }
            x = y;
            y = static_cast<unsigned char>(cp[1]);
            if (y >= 0xA1 && y < 0xFF)
            {
              code = jisx0212[(x - 0xA1)*94 + (y - 0xA1)];
              cp += 2;
            }
          }
          else if (x == 0x8E && y <= 0xDF) // JIS X 0201
          {
            code = y + 0xFEC0; // half-width katakana
            cp++;
          }
        }
      }

      if (code == 0xFFFD)
      {
        BadCharsToUTF8(lastpos, cp, s, mode);
        errpos = (errpos ? errpos : lastpos);
      }
      else
      {
        UnicodeToUTF8(code, s);
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToBig5(
  const char *text, size_t l, std::string *s, int mode)
{
  // traditional Chinese
  CompressedTableR table(vtkDICOMCharacterSet::Reverse[X_BIG5]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code < 0x80)
    {
      s->push_back(static_cast<char>(code));
    }
    else
    {
      unsigned short t = table[code];
      if (t >= 0xFFFD) switch (code)
      {
        // the table is restricted to the BMP, special-case big codes
        case 0x200CC: t = 11205; break;
        case 0x2008A: t = 11207; break;
        case 0x27607: t = 11213; break;
      }
      if (t < 19782)
      {
        unsigned char x = static_cast<unsigned char>(0x81 + t / 157);
        unsigned char y = static_cast<unsigned char>(0x40 + t % 157);
        if (y >= 0x7f) { y += 0x22; }
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
      }
      else if (!HandleReplacement(s, lastpos, cp, mode))
      {
        errpos = (errpos ? errpos : lastpos);
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::Big5ToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  // traditional Chinese, Big5 + ETEN extensions
  CompressedTable table(vtkDICOMCharacterSet::Table[X_BIG5]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    char c = *cp++;
    if ((c & 0x80) == 0)
    {
      s->push_back(c);
    }
    else
    {
      unsigned int code = 0xFFFD;
      unsigned short x = static_cast<unsigned char>(c);

      if (x >= 0x81 && x <= 0xFE && cp != ep)
      {
        unsigned short y = static_cast<unsigned char>(*cp);
        if ((y >= 0x40 && y <= 0x7E) || (y >= 0xA1 && y <= 0xFE))
        {
          cp++;
          unsigned short offset = (y < 0x7F ? 0x40 : 0x62);
          unsigned short t = (x - 0x81)*157 + (y - offset);
          switch (t)
          {
            case 11205: code = 0x200CC; break;
            case 11207: code = 0x2008A; break;
            case 11213: code = 0x27607; break;
            default: code = table[t];
          }
        }
      }

      if (code == 0xFFFD)
      {
        BadCharsToUTF8(lastpos, cp, s, mode);
        errpos = (errpos ? errpos : lastpos);
      }
      else
      {
        UnicodeToUTF8(code, s);
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
namespace {

// Each pair is PUA code <-> valid character code for GB18030-2022
static const unsigned short TweakTableForGB18030[38] = {
  0xE78D, 0xFE10, 0xE78E, 0xFE12, 0xE78F, 0xFE11, 0xE790, 0xFE13,
  0xE791, 0xFE14, 0xE792, 0xFE15, 0xE793, 0xFE16, 0xE794, 0xFE17,
  0xE795, 0xFE18, 0xE796, 0xFE19, 0xE7C7, 0x1E3F, 0xE81E, 0x9FB4,
  0xE826, 0x9FB5, 0xE82B, 0x9FB6, 0xE82C, 0x9FB7, 0xE832, 0x9FB8,
  0xE843, 0x9FB9, 0xE854, 0x9FBA, 0xE864, 0x9FBB
};

// Tweak GB18030 result to get GB18030-2022
unsigned int TweakGB18030(unsigned int code)
{
  // The GB18030 conversion tables have been revised twice:
  // 1. GB18030-2000 is the original
  // 2. GB18030-2005 requires the U+E7C7 <-> U+1E3F tweak
  // 3. GB18030-2022 requires all the tweaks in our tweak table

  // These indicate what portion of the table to search,
  // we only search relevant part of the table for efficiency
  int start = 0;
  int stop = 0;

  if (code >= 0xE78D && code <= 0xE864) // PUA
  {
    // if code is private, search whole tweak table
    stop = 38;
  }
  else if (code == 0x1E3F) // GB18030-2005 and GB18030-2022
  {
    start  = 21;
    stop = 22;
  }
  else if (code >= 0xFE10 && code <= 0xFE19) // GB18030-2022
  {
    start = 1;
    stop = 20;
  }
  else if (code >= 0x9FB4 && code <= 0x9FBB) // GB18030-2022
  {
    start = 23;
    stop = 38;
  }

  // If start is even, we're searching for even (private) codes,
  // if start is odd, we're searching for odd (non-private) codes.
  for (int i = start; i < stop; i += 2)
  {
    if (TweakTableForGB18030[i] == static_cast<unsigned short>(code))
    {
      // Use xor to swap private to valid character and vice-versa
      code = TweakTableForGB18030[i ^ 1];
      break;
    }
  }

  return code;
}

} // end namespace

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToGBK(
  const char *text, size_t l, std::string *s, int mode)
{
  // Chinese national encoding standard
  CompressedTableR table(vtkDICOMCharacterSet::Reverse[GB18030]);
  CompressedTableR table2(vtkDICOMCharacterSet::Reverse[GBK]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code < 0x80)
    {
      s->push_back(static_cast<char>(code));
      continue;
    }
    else
    {
      // the primary table is the GB18030 table
      unsigned short t = table[code];
      if (InvalidCode(GBKInvalidRanges, t))
      {
        // try additional compatibility mappings specific to GBK
        t = table2[code];
      }
      if (t < 23940)
      {
        unsigned char x;
        unsigned char y;
        if (t < 8836)
        {
          // GB2312
          x = static_cast<unsigned char>(0xA1 + t / 94);
          y = static_cast<unsigned char>(0xA1 + t % 94);
        }
        else if (t < 8836 + 6080)
        {
          // GBK region 3
          t -= 8836;
          x = static_cast<unsigned char>(0x81 + t / 190);
          y = static_cast<unsigned char>(0x40 + t % 190);
          if (y >= 0x7f) { y++; }
        }
        else
        {
          // GBK regions 4 & 5
          t -= 8836 + 6080;
          x = static_cast<unsigned char>(0xA1 + t / 96);
          y = static_cast<unsigned char>(0x40 + t % 96);
          if (y >= 0x7f) { y++; }
        }
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
        continue;
      }
    }

    if (!HandleReplacement(s, lastpos, cp, mode))
    {
      errpos = (errpos ? errpos : lastpos);
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::GBKToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  // Windows code page for simplified Chinese
  CompressedTable table(vtkDICOMCharacterSet::Table[GBK]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    char c = *cp++;
    if ((c & 0x80) == 0)
    {
      s->push_back(c);
    }
    else
    {
      unsigned int code = 0xFFFD;
      unsigned short a = static_cast<unsigned char>(c);

      if (a > 0x80 && a < 0xFF && cp != ep)
      {
        unsigned short b = static_cast<unsigned char>(*cp);
        if (b >= 0x40 && b < 0xFF && b != 0x7F)
        {
          // two-byte character
          if (a < 0xA1)
          {
            // GBK region 3
            if (b > 0x7F) { b--; }
            a = (a - 0x81)*190 + (b - 0x40) + 8836;
          }
          else if (b < 0xA1)
          {
            // GBK regions 4 & 5
            if (b > 0x7F) { b--; }
            a = (a - 0xA1)*96 + (b - 0x40) + 8836 + 6080;
          }
          else
          {
            // GBK regions 1 & 2 (GB2312)
            a = (a - 0xA1)*94 + (b - 0xA1);
          }
          code = table[a];

          // if code is PUA, then try to remap to a character
          if (code >= 0xE000 && code < 0xF900)
          {
            // use the mappings from the GB18030-2022 standard
            code = TweakGB18030(code);
          }

          cp++;
        }
      }
      else if (a == 0x80)
      {
        // EURO SIGN for CP936 compatibility
        code = 0x20AC;
      }

      if (code == 0xFFFD)
      {
        BadCharsToUTF8(lastpos, cp, s, mode);
        errpos = (errpos ? errpos : lastpos);
      }
      else
      {
        UnicodeToUTF8(code, s);
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToGB18030(
  const char *text, size_t l, std::string *s, int mode)
{
  // Chinese national encoding standard
  CompressedTableR table(vtkDICOMCharacterSet::Reverse[GB18030]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code < 0x80)
    {
      s->push_back(static_cast<char>(code));
      continue;
    }

    // GB18030-2000 to GB18030-2022
    code = TweakGB18030(code);

    unsigned int t;
    if (code <= 0xFFFD)
    {
      t = table[code];
      if (t < 23940)
      {
        unsigned char x;
        unsigned char y;
        if (t < 8836)
        {
          // GB2312
          x = static_cast<unsigned char>(0xA1 + t / 94);
          y = static_cast<unsigned char>(0xA1 + t % 94);
        }
        else if (t < 8836 + 6080)
        {
          // GBK region 3
          t -= 8836;
          x = static_cast<unsigned char>(0x81 + t / 190);
          y = static_cast<unsigned char>(0x40 + t % 190);
          if (y >= 0x7f) { y++; }
        }
        else
        {
          // GBK regions 4 & 5
          t -= 8836 + 6080;
          x = static_cast<unsigned char>(0xA1 + t / 96);
          y = static_cast<unsigned char>(0x40 + t % 96);
          if (y >= 0x7f) { y++; }
        }
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
        continue;
      }
      else
      {
        // other BMP codes -> 4 byte GB18030 code
        t -= 23940;
      }
    }
    else if (code >= 0x10000)
    {
      // non-BMP codes -> 4 byte GB18030 code
      t = code - 0x10000 + 150*1260;
    }
    else // (code == 0xFFFE || code == 0xFFFF)
    {
      if (IsFFFX(code, lastpos, cp))
      {
        // was a valid code, not an error indicator
        t = code - 0xFFFD + 39417;
      }
      else
      {
        if (!HandleReplacement(s, lastpos, ep, mode))
        {
          errpos = (errpos ? errpos : lastpos);
        }
        continue;
      }
    }

    // four bytes
    unsigned int a = t / 1260;
    unsigned int b = t % 1260;
    s->push_back(static_cast<char>(0x81 + a / 10));
    s->push_back(static_cast<char>(0x30 + a % 10));
    s->push_back(static_cast<char>(0x81 + b / 10));
    s->push_back(static_cast<char>(0x30 + b % 10));
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::GB18030ToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  // Chinese national encoding standard
  CompressedTable table(vtkDICOMCharacterSet::Table[GB18030]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    char c = *cp++;
    if ((c & 0x80) == 0)
    {
      s->push_back(c);
    }
    else
    {
      unsigned int code = 0xFFFD;
      unsigned short a = static_cast<unsigned char>(c);

      if (a > 0x80 && a < 0xFF && cp != ep)
      {
        unsigned short b = static_cast<unsigned char>(*cp);
        if (b >= 0x30 && b < 0xFF && b != 0x7F)
        {
          cp++;
          if (b >= 0x40)
          {
            // two-byte character
            if (a < 0xA1)
            {
              // GBK region 3
              if (b > 0x7F) { b--; }
              a = (a - 0x81)*190 + (b - 0x40) + 8836;
            }
            else if (b < 0xA1)
            {
              // GBK regions 4 & 5
              if (b > 0x7F) { b--; }
              a = (a - 0xA1)*96 + (b - 0x40) + (8836 + 6080);
            }
            else
            {
              // GBK regions 1 & 2 (GB2312)
              a = (a - 0xA1)*94 + (b - 0xA1);
            }
            code = table[a];
          }
          else if (cp != ep && cp+1 != ep)
          {
            // start of a four-byte code
            if (static_cast<unsigned char>(cp[0]) > 0x80 &&
                static_cast<unsigned char>(cp[0]) < 0xFF &&
                cp[1] >= '0' && cp[1] <= '9')
            {
              // four-byte GB18030 character
              unsigned short x = static_cast<unsigned char>(*cp++);
              unsigned short y = static_cast<unsigned char>(*cp++);
              a = (a - 0x81)*10 + (b - '0');
              b = (x - 0x81)*10 + (y - '0');
              if (a < 32)
              {
                // for unicode within the BMP
                a = a*1260 + b + 23940;
                code = table[a];
              }
              else if (a >= 150)
              {
                // for unicode beyond the BMP
                a -= 150;
                unsigned int g = a*1260 + b;
                if (g <= 0xFFFFF)
                {
                  code = g + 0x10000;
                }
              }
            }
          }
        }
      }
      else if (a == 0x80)
      {
        // EURO SIGN for CP936 compatibility (also at a=A2,b=E3)
        code = 0x20AC;
      }

      // the 4-byte code 0x84,0x31,0xA4,0x37 is the valid code for 0xFFFD
      if (code == 0xFFFD && !(cp-lastpos >= 4 && lastpos[0] == '\x84' &&
          lastpos[1] == '1' && lastpos[2] == '\xa4' && lastpos[3] == '7'))
      {
        BadCharsToUTF8(lastpos, cp, s, mode);
        errpos = (errpos ? errpos : lastpos);
      }
      else
      {
        // tweak GB18030-2000 to GB18030-2022
        code = TweakGB18030(code);
        UnicodeToUTF8(code, s);
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToGB2312(
  const char *text, size_t l, std::string *s, int mode)
{
  // Chinese national encoding standard
  CompressedTableR table(vtkDICOMCharacterSet::Reverse[GB18030]);
  CompressedTableR table2(vtkDICOMCharacterSet::Reverse[X_GB2312]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code < 0x80)
    {
      s->push_back(static_cast<char>(code));
      continue;
    }
    else
    {
      unsigned short t = table[code];
      if (InvalidCode(GB2312InvalidRanges, t))
      {
        // try additional compatibility mappings
        t = table2[code];
      }
      if (t < 8836)
      {
        unsigned char x = static_cast<unsigned char>(0xA1 + t / 94);
        unsigned char y = static_cast<unsigned char>(0xA1 + t % 94);
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
        continue;
      }
    }

    if (!HandleReplacement(s, lastpos, cp, mode))
    {
      errpos = (errpos ? errpos : lastpos);
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::GB2312ToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  // GB2312 chinese encoding
  CompressedTable table(vtkDICOMCharacterSet::Table[X_GB2312]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    char c = *cp++;
    if ((c & 0x80) == 0)
    {
      s->push_back(c);
    }
    else
    {
      unsigned int code = 0xFFFD;
      unsigned short a = static_cast<unsigned char>(c);
      if (a >= 0xA1 && a < 0xFF && cp != ep)
      {
        unsigned short b = static_cast<unsigned char>(*cp);

        // default to replacement character
        code = 0xFFFD;

        if (b >= 0xA1 && b < 0xFF)
        {
          a = (a - 0xA1)*94 + (b - 0xA1);

          if (!InvalidCode(GB2312InvalidRanges, a))
          {
            code = table[a];
          }

          cp++;
        }
      }

      if (code == 0xFFFD)
      {
        BadCharsToUTF8(lastpos, cp, s, mode);
        errpos = (errpos ? errpos : lastpos);
      }
      else
      {
        UnicodeToUTF8(code, s);
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToJISX(
  int charset, const char *text, size_t l, std::string *s, int mode)
{
  // table for JIS X 0208 and JIS X 0212
  CompressedTableJISXR table(vtkDICOMCharacterSet::Reverse[X_EUCJP]);
  // table for JIS X 0208 compatibility mappings
  CompressedTableR table2(vtkDICOMCharacterSet::Reverse[X_SJIS]);

  enum stateType { ASCII, X0201r, X0201k, X0208, X0212, XGB, XKS };
  stateType stateBase = ASCII;
  bool hasJISX0201 = true;
  bool hasKatakana = (charset == X_ISO_2022_JP_EXT);
  bool hasJISX0208 = true;
  bool hasJISX0212 = (charset != X_ISO_2022_JP);
  const char *escBase = "\033(B";
  const char *esc0201r = "\033(J";
  const char *esc0201k = "\033(I";
  const char *esc0208 = "\033$B";
  const char *esc0212 = "\033$(D";

  if ((charset & DICOM_JP_BITS) == charset)
  {
    // use DICOM defined terms to check support for charsets
    hasJISX0201 = ((charset & ISO_IR_13) == ISO_IR_13);
    hasKatakana = hasJISX0201;
    hasJISX0208 = ((charset & ISO_2022_IR_87) == ISO_2022_IR_87);
    hasJISX0212 = ((charset & ISO_2022_IR_159) == ISO_2022_IR_159);
    if (hasJISX0201)
    {
      stateBase = X0201r;
      escBase = esc0201r;
    }
  }

  stateType state = stateBase;
  bool latin1G2 = false;
  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (hasJISX0201)
    {
      if (hasKatakana && code >= 0xFF61 && code <= 0xFF9F)
      {
        // half-width katakana in G1
        unsigned int offset = 0xFEC0;
        if (charset == X_ISO_2022_JP_EXT)
        {
          offset += 0x80; // offset to put in G0
          if (state != X0201k)
          {
            s->append(esc0201k);
            state = X0201k;
          }
        }
        s->push_back(static_cast<char>(code - offset));
        continue;
      }

      if (code == 0xA5 || code == 0x203E) // YEN SIGN, OVERLINE
      {
        if (state != X0201r)
        {
          s->append(esc0201r);
          state = X0201r;
        }
        s->push_back(code == 0xA5 ? '\\' : '~');
        continue;
      }
    }

    if (code < 0x80)
    {
      if (code != 0x1B && code != 0x0E && code != 0x0F) // ESC SO SI
      {
        if (state != stateBase)
        {
          s->append(escBase);
          state = stateBase;
        }
        s->push_back(static_cast<char>(code));
        continue;
      }
    }
    else if (hasJISX0208 || hasJISX0212)
    {
      unsigned short t = table[code];
      if (t >= 8836 && t < 2*8836 && hasJISX0212)
      {
        t -= 8836;
        if (state != X0212)
        {
          s->append(esc0212);
          state = X0212;
        }
      }
      else if (hasJISX0208)
      {
        if (t >= 8836 &&
            ((code >= 0xFF61 && code <= 0xFF9F) || // JIS X 0201 katakana
             code == 0xFF5E || // fullwidth tilde from JIS X 0212
             code == 0x5861 || code == 0x9830)) // JIS X 0212
        {
          // JIS X 0208 compatibility mappings
          t = table2[code];
        }
        if (t < 8836 && state != X0208)
        {
          s->append(esc0208);
          state = X0208;
        }
      }
      if (t >= 8836 && charset == X_ISO_2022_JP_2)
      {
        stateType kcState = XGB;
        const char *escCode = "\033$A";
        CompressedTableR tableGB(vtkDICOMCharacterSet::Reverse[GB18030]);
        t = tableGB[code];
        if (InvalidCode(GB2312InvalidRanges, t))
        {
          kcState = XKS;
          escCode = "\033$(C";
          CompressedTableR tableKR(vtkDICOMCharacterSet::Reverse[X_EUCKR]);
          t = tableKR[code];
        }
        if (t < 8836)
        {
          if (state != kcState)
          {
            s->append(escCode);
            state = kcState;
          }
        }
        else if (code >= 0xA1 && code <= 0xFE)
        {
          if (!latin1G2) {
            s->append("\033.A"); // latin1 to G2
            latin1G2 = true;
          }
          s->append("\033N");  // SS2
          s->push_back(static_cast<char>(code & 0x7F));
          continue;
        }
      }
      if (t < 8836)
      {
        unsigned char x = static_cast<unsigned char>(0x21 + t / 94);
        unsigned char y = static_cast<unsigned char>(0x21 + t % 94);
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
        continue;
      }
    }

    // conversion of character failed
    size_t lastsize = s->size();
    if (state != stateBase)
    {
      s->append(escBase);
    }
    size_t checksize = s->size();
    if (!HandleReplacement(s, lastpos, cp, mode))
    {
      errpos = (errpos ? errpos : lastpos);
    }
    if (s->size() == checksize)
    {
      s->resize(lastsize);
    }
    else
    {
      state = stateBase;
    }
  }

  if (state != stateBase)
  {
    s->append(escBase);
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::JISXToUTF8(
  int csGL, int csGR, const char *text, size_t l, std::string *s, int mode)
{
  // this is a helper method for iso 2022 japanese decoding
  CompressedTable table(vtkDICOMCharacterSet::Table[csGL]);
  bool multibyte = (csGL == ISO_2022_IR_87 ||
                    csGL == ISO_2022_IR_159 ||
                    csGL == ISO_2022_IR_149 ||
                    csGL == ISO_2022_IR_58);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = 0xFFFD;
    unsigned short a = static_cast<unsigned char>(*cp++);
    if (a >= 0x21 && a < 0x7F)
    {
      bool good = true;
      if (multibyte)
      {
        if (cp != ep && *cp >= 0x21 && *cp < 0x7F)
        {
          // convert double-byte to character
          unsigned short b = static_cast<unsigned char>(*cp++);
          a = (a - 0x21)*94 + (b - 0x21);
        }
        else
        {
          good = false;
        }
      }
      else if (csGL == ISO_IR_13)
      {
        // shift to put half-width katakana in GL
        a += 0x80;
      }
      if (good)
      {
        code = table[a];
      }
    }
    else if (a <= 0x7F)
    {
      // control codes, space, or delete
      code = a;
    }
    else if (csGR == ISO_IR_13 &&
             a >= 0xA1 && a <= 0xDF)
    {
      // half-width katakana in GR
      code = a + 0xFEC0;
    }

    if (code == 0xFFFD)
    {
      BadCharsToUTF8(lastpos, cp, s, mode);
      errpos = (errpos ? errpos : lastpos);
    }
    else
    {
      UnicodeToUTF8(code, s);
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToEUCKR(
  const char *text, size_t l, std::string *s, int mode) const
{
  // EUC-KR encoding of KS X 1001 (and CP949 for compatibility)
  CompressedTableR table(vtkDICOMCharacterSet::Reverse[X_EUCKR]);

  // There are two ways we encode hangul that don't fit the 94x94 table:
  // 1) with the expanded table used by Windows CP949, also called UHC
  // 2) 8-byte sequences, which is the the only option for ISO 2022
  // We use (1) when invoked as EUCKR, (2) when invoked with ISO 2022

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code < 0x80)
    {
      s->push_back(static_cast<char>(code));
      continue;
    }
    else
    {
      unsigned short t = table[code];
      if (t < 8836)
      {
        unsigned char x = static_cast<unsigned char>(0xA1 + t / 94);
        unsigned char y = static_cast<unsigned char>(0xA1 + t % 94);
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
        continue;
      }
      else if (t < 17658 && this->Key != ISO_2022_IR_149)
      {
        // use CP949 if not limited to the ISO 2022 94x94 set
        unsigned char x, y;
        t -= 8836;
        if (t < 5696)
        {
          x = static_cast<unsigned char>(0x81 + t / 178);
          y = static_cast<unsigned char>(0x41 + t % 178);
        }
        else
        {
          t -= 5696;
          x = static_cast<unsigned char>(0xA1 + t / 84);
          y = static_cast<unsigned char>(0x41 + t % 84);
        }

        if (y > 0x5A)
        {
          y += 6;
          if (y > 0x7A)
          {
            y += 6;
          }
        }
        s->push_back(static_cast<char>(x));
        s->push_back(static_cast<char>(y));
        continue;
      }
      else if (code >= 0xAC00 && code <= 0xD7A3) // hangul block
      {
        // table for leading consonant
        static const unsigned char tableL[19] = {
           0, 1, 3, 6, 7, 8,16,17,18,20,21,22,23,24,25,26,
          27,28,29
        };
        // table for trailing consonant
        static const unsigned char tableT[28] = {
          51, 0, 1, 2, 3, 4, 5, 6, 8, 9,10,11,12,13,14,15,
          16,17,19,20,21,22,23,25,26,27,28,29
        };
        // use 8-byte jamo code for hangul that aren't in KS X 1001
        unsigned int z = code - 0xAC00;
        unsigned int T = z % 28;
        z /= 28;
        unsigned int V = z % 21;
        unsigned int L = z / 21;
        s->push_back(0xA4);
        s->push_back(0xD4);
        s->push_back(0xA4);
        s->push_back(0xA1 + tableL[L]);
        s->push_back(0xA4);
        s->push_back(0xBF + V);
        s->push_back(0xA4);
        s->push_back(0xA1 + tableT[T]);
        continue;
      }
    }

    if (!HandleReplacement(s, lastpos, cp, mode))
    {
      errpos = (errpos ? errpos : lastpos);
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::EUCKRToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  // EUC-KR encoding of KS X 1001 (and CP949 for compatibility)
  CompressedTable table(vtkDICOMCharacterSet::Table[X_EUCKR]);

  // Get the hangul block in KS X 1001 (codes 1410 to 3759)
  const unsigned short *hangul = table.GetBlock(1410);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = 0xFFFD;
    unsigned short x = static_cast<unsigned char>(*cp++);
    if (x <= 0x7F)
    {
      code = x;
    }
    else if (x >= 0x81 && x < 0xFF && cp != ep)
    {
      // convert two bytes into unicode
      unsigned short y = static_cast<unsigned char>(*cp);
      if (x >= 0xA1 && y >= 0xA1 && y < 0xFF)
      {
        unsigned short a = x - 0xA1;
        unsigned short b = y - 0xA1;
        a = a*94 + b;
        code = table[a];
        cp++;

        // check for hangul encoded as 8-byte jamo sequence
        if (x == 0xA4 && y == 0xD4 && ep - cp >= 6 &&
            static_cast<unsigned char>(cp[0]) == 0xA4 &&
            static_cast<unsigned char>(cp[1]) >= 0xA1 &&
            static_cast<unsigned char>(cp[2]) == 0xA4 &&
            static_cast<unsigned char>(cp[3]) >= 0xA1 &&
            static_cast<unsigned char>(cp[4]) == 0xA4 &&
            static_cast<unsigned char>(cp[5]) >= 0xA1)
        {
          // table to convert leading consonant to an index
          static const unsigned char tableL[52] = {
               1, 2, 0, 3, 0, 0, 4, 5, 6, 0, 0, 0, 0, 0, 0,
            0, 7, 8, 9, 0,10,11,12,13,14,15,16,17,18,19, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 20
          };
          // table to convert trailing consonant to an index
          static const unsigned char tableT[52] = {
               2, 3, 4, 5, 6, 7, 8, 0, 9,10,11,12,13,14,15,
           16,17,18, 0,19,20,21,22,23, 0,24,25,26,27,28, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1
          };
          // get the leading consonant, vowel, and trailing consonant
          unsigned short y1 = static_cast<unsigned char>(cp[1]);
          unsigned short y2 = static_cast<unsigned char>(cp[3]);
          unsigned short y3 = static_cast<unsigned char>(cp[5]);
          // check whether the sequence is valid
          if (y1 >= 0xA1 && y1 <= 0xD4 && tableL[y1-0xA1] != 0 &&
              y2 >= 0xBF && y2 <= 0xD4 &&
              y3 >= 0xA1 && y3 <= 0xD4 && tableT[y3-0xA1] != 0)
          {
            cp += 6;
            unsigned short L = tableL[y1-0xA1]-1;
            unsigned short V = y2 - 0xBF;
            unsigned short T = tableT[y3-0xA1]-1;
            if (L < 19 && V < 21)
            {
              // compute the composed unicode hangul
              code = 0xAC00 + (L*21 + V)*28 + T;
              // ensure this hangul is absent from KS X 1001
              if (std::binary_search(hangul, hangul+2350, code))
              {
                // if hangul has a precomposed form in KS X 1001,
                // ignore the composition and write out the sequence
                // using the Hangul Jamo Compatibility Block so
                // that it will round-trip back to KS X 1001
                UnicodeToUTF8(0x3164, s);
                UnicodeToUTF8(0x3090 + y1, s);
                UnicodeToUTF8(0x3090 + y2, s);
                code = 0x3090 + y3;
              }
            }
            else if (L < 19 || V < 21 || T > 0)
            {
              // produce decomposed hangul with filler
              code = (L < 19 ? 0x1100 + L : 0x115F);
              UnicodeToUTF8(code, s);
              code = (V < 21 ? 0x1161 + V : 0x1160);
              if (T > 0)
              {
                UnicodeToUTF8(code, s);
                code = 0x11A7 + T;
              }
            }
            else
            {
              // all components are filler, so a syllable cannot be
              // created: write the sequence as compatibility codes
              UnicodeToUTF8(0x3164, s);
              UnicodeToUTF8(0x3164, s);
              UnicodeToUTF8(0x3164, s);
              code = 0x3164;
            }
          }
        }
      }
      else if ((y >= 0x41 && y <= 0x5A) ||
               (y >= 0x61 && y <= 0x7A) ||
               (y >= 0x81 && y < 0xFF))
      {
        // possibly CP949 hangul extensions
        unsigned short a = x - 0x81;
        unsigned short b = y - 0x41;
        if (b >= 26)
        {
          b -= 6;
          if (b >= 52)
          {
            b -= 6;
          }
        }
        a = (a < 32 ? a*178 + b : a*84 + b + 3008);
        if (a < 8822)
        {
          code = table[a + 8836];
          cp++;
        }
      }
    }

    if (code == 0xFFFD)
    {
      BadCharsToUTF8(lastpos, cp, s, mode);
      errpos = (errpos ? errpos : lastpos);
    }
    else
    {
      UnicodeToUTF8(code, s);
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
namespace {

// CP1258 (Vietnamese) is unique in that it contains combining
// diacritics, which must be composed in order to produce NFC.
// This contrasts with Hebrew, which also uses combining chars
// but is excluded from composition (NFC Hebrew is decomposed).

// The real tricky thing is encoding to CP1258, which requires
// CP1258-specific partial decomposition (not the same as NFD).

// This is the combining table for all latin chars in CP1258
const int COMPOSITION_TABLE_SIZE = 258;
const unsigned short CompressedCompositionTable[516] = {
  // Each value represents a starter and a diacritic, algorithmically
  // compressed to 16 bits (10 bits for starter, 6 bits for diacritic)
  0x1040, 0x1041, 0x1042, 0x1043, 0x1046, 0x1048, 0x1049, 0x1063,
  0x10A3, 0x10C1, 0x10C2, 0x1123, 0x1140, 0x1141, 0x1142, 0x1143,
  0x1146, 0x1148, 0x1149, 0x1163, 0x11C1, 0x11C2, 0x11C6, 0x1202,
  0x1208, 0x1223, 0x1240, 0x1241, 0x1242, 0x1243, 0x1246, 0x1248,
  0x1249, 0x1263, 0x1282, 0x12C1, 0x12E3, 0x1301, 0x1323, 0x1341,
  0x1363, 0x1380, 0x1381, 0x1383, 0x13A3, 0x13C0, 0x13C1, 0x13C2,
  0x13C3, 0x13C6, 0x13C8, 0x13C9, 0x13DB, 0x13E3, 0x1401, 0x1481,
  0x14A3, 0x14C1, 0x14C2, 0x14E3, 0x1523, 0x1540, 0x1541, 0x1542,
  0x1543, 0x1546, 0x1548, 0x1549, 0x155B, 0x1563, 0x1583, 0x15A3,
  0x15C0, 0x15C1, 0x15C2, 0x15C8, 0x15E3, 0x1608, 0x1640, 0x1641,
  0x1642, 0x1643, 0x1648, 0x1649, 0x1663, 0x1681, 0x1682, 0x16A3,
  0x1840, 0x1841, 0x1842, 0x1843, 0x1846, 0x1848, 0x1849, 0x1863,
  0x18A3, 0x18C1, 0x18C2, 0x1923, 0x1940, 0x1941, 0x1942, 0x1943,
  0x1946, 0x1948, 0x1949, 0x1963, 0x19C1, 0x19C2, 0x19C6, 0x1A02,
  0x1A08, 0x1A23, 0x1A40, 0x1A41, 0x1A42, 0x1A43, 0x1A46, 0x1A48,
  0x1A49, 0x1A63, 0x1A82, 0x1AC1, 0x1AE3, 0x1B01, 0x1B23, 0x1B41,
  0x1B63, 0x1B80, 0x1B81, 0x1B83, 0x1BA3, 0x1BC0, 0x1BC1, 0x1BC2,
  0x1BC3, 0x1BC6, 0x1BC8, 0x1BC9, 0x1BDB, 0x1BE3, 0x1C01, 0x1C81,
  0x1CA3, 0x1CC1, 0x1CC2, 0x1CE3, 0x1D08, 0x1D23, 0x1D40, 0x1D41,
  0x1D42, 0x1D43, 0x1D46, 0x1D48, 0x1D49, 0x1D5B, 0x1D63, 0x1D83,
  0x1DA3, 0x1DC0, 0x1DC1, 0x1DC2, 0x1DC8, 0x1DE3, 0x1E08, 0x1E40,
  0x1E41, 0x1E42, 0x1E43, 0x1E48, 0x1E49, 0x1E63, 0x1E81, 0x1E82,
  0x1EA3, 0x3080, 0x3081, 0x3083, 0x3089, 0x3141, 0x31C1, 0x3280,
  0x3281, 0x3283, 0x3289, 0x33C1, 0x3500, 0x3501, 0x3503, 0x3509,
  0x3541, 0x3548, 0x3601, 0x3700, 0x3701, 0x3880, 0x3881, 0x3883,
  0x3889, 0x3941, 0x3981, 0x39C1, 0x3A80, 0x3A81, 0x3A83, 0x3A89,
  0x3BC1, 0x3D00, 0x3D01, 0x3D03, 0x3D09, 0x3D41, 0x3D48, 0x3E01,
  0x3F00, 0x3F01, 0x4080, 0x4081, 0x4083, 0x4089, 0x40C0, 0x40C1,
  0x40C3, 0x40C9, 0x5A01, 0x5A41, 0x6800, 0x6801, 0x6803, 0x6809,
  0x6823, 0x6840, 0x6841, 0x6843, 0x6849, 0x6863, 0x6BC0, 0x6BC1,
  0x6BC3, 0x6BC9, 0x6BE3, 0x6C00, 0x6C01, 0x6C03, 0x6C09, 0x6C23,
  0x8A06, 0x8A46, 0xE802, 0xE806, 0xE842, 0xE846, 0xEE02, 0xEE42,
  0xF302, 0xF342,

  // Each value for the 2nd half of the table is a composed character
  // (2nd half of table maps to 1st half, and vice-versa)
  0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x0102, 0x00C4, 0x1EA2, 0x1EA0,
  0x1E04, 0x0106, 0x0108, 0x1E0C, 0x00C8, 0x00C9, 0x00CA, 0x1EBC,
  0x0114, 0x00CB, 0x1EBA, 0x1EB8, 0x01F4, 0x011C, 0x011E, 0x0124,
  0x1E26, 0x1E24, 0x00CC, 0x00CD, 0x00CE, 0x0128, 0x012C, 0x00CF,
  0x1EC8, 0x1ECA, 0x0134, 0x1E30, 0x1E32, 0x0139, 0x1E36, 0x1E3E,
  0x1E42, 0x01F8, 0x0143, 0x00D1, 0x1E46, 0x00D2, 0x00D3, 0x00D4,
  0x00D5, 0x014E, 0x00D6, 0x1ECE, 0x01A0, 0x1ECC, 0x1E54, 0x0154,
  0x1E5A, 0x015A, 0x015C, 0x1E62, 0x1E6C, 0x00D9, 0x00DA, 0x00DB,
  0x0168, 0x016C, 0x00DC, 0x1EE6, 0x01AF, 0x1EE4, 0x1E7C, 0x1E7E,
  0x1E80, 0x1E82, 0x0174, 0x1E84, 0x1E88, 0x1E8C, 0x1EF2, 0x00DD,
  0x0176, 0x1EF8, 0x0178, 0x1EF6, 0x1EF4, 0x0179, 0x1E90, 0x1E92,
  0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x0103, 0x00E4, 0x1EA3, 0x1EA1,
  0x1E05, 0x0107, 0x0109, 0x1E0D, 0x00E8, 0x00E9, 0x00EA, 0x1EBD,
  0x0115, 0x00EB, 0x1EBB, 0x1EB9, 0x01F5, 0x011D, 0x011F, 0x0125,
  0x1E27, 0x1E25, 0x00EC, 0x00ED, 0x00EE, 0x0129, 0x012D, 0x00EF,
  0x1EC9, 0x1ECB, 0x0135, 0x1E31, 0x1E33, 0x013A, 0x1E37, 0x1E3F,
  0x1E43, 0x01F9, 0x0144, 0x00F1, 0x1E47, 0x00F2, 0x00F3, 0x00F4,
  0x00F5, 0x014F, 0x00F6, 0x1ECF, 0x01A1, 0x1ECD, 0x1E55, 0x0155,
  0x1E5B, 0x015B, 0x015D, 0x1E63, 0x1E97, 0x1E6D, 0x00F9, 0x00FA,
  0x00FB, 0x0169, 0x016D, 0x00FC, 0x1EE7, 0x01B0, 0x1EE5, 0x1E7D,
  0x1E7F, 0x1E81, 0x1E83, 0x0175, 0x1E85, 0x1E89, 0x1E8D, 0x1EF3,
  0x00FD, 0x0177, 0x1EF9, 0x00FF, 0x1EF7, 0x1EF5, 0x017A, 0x1E91,
  0x1E93, 0x1EA6, 0x1EA4, 0x1EAA, 0x1EA8, 0x01FA, 0x1E08, 0x1EC0,
  0x1EBE, 0x1EC4, 0x1EC2, 0x1E2E, 0x1ED2, 0x1ED0, 0x1ED6, 0x1ED4,
  0x1E4C, 0x1E4E, 0x01FE, 0x01DB, 0x01D7, 0x1EA7, 0x1EA5, 0x1EAB,
  0x1EA9, 0x01FB, 0x01FD, 0x1E09, 0x1EC1, 0x1EBF, 0x1EC5, 0x1EC3,
  0x1E2F, 0x1ED3, 0x1ED1, 0x1ED7, 0x1ED5, 0x1E4D, 0x1E4F, 0x01FF,
  0x01DC, 0x01D8, 0x1EB0, 0x1EAE, 0x1EB4, 0x1EB2, 0x1EB1, 0x1EAF,
  0x1EB5, 0x1EB3, 0x1E78, 0x1E79, 0x1EDC, 0x1EDA, 0x1EE0, 0x1EDE,
  0x1EE2, 0x1EDD, 0x1EDB, 0x1EE1, 0x1EDF, 0x1EE3, 0x1EEA, 0x1EE8,
  0x1EEE, 0x1EEC, 0x1EF0, 0x1EEB, 0x1EE9, 0x1EEF, 0x1EED, 0x1EF1,
  0x1E1C, 0x1E1D, 0x1EAC, 0x1EB6, 0x1EAD, 0x1EB7, 0x1EC6, 0x1EC7,
  0x1ED8, 0x1ED9,
};

// Combining values, used to sort the diacritics.
// 230 for ACUTE, GRAVE, CIRCUMFLEX, TILDE, etc.
// 220 for DOT BELOW, etc.
const unsigned char CombiningClassTable[64] = {
  230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
  230, 230, 230, 230, 230, 230, 230, 230, 230, 232, 220, 220,
  220, 220, 232, 216, 220, 220, 220, 220, 220, 202, 202, 220,
  220, 220, 220, 202, 202, 220, 220, 220, 220, 220, 220, 220,
  220, 220, 220, 220, 1, 1, 1, 1, 1, 220, 220, 220, 220, 230,
  230, 230,
};

// Combining values for use with CP1258, tonal marks last.
// 240 for ACUTE, GRAVE, TILDE, DOT BELOW
const unsigned char CombiningClassCP1258[64] = {
  240, 240, 230, 240, 230, 230, 230, 230, 230, 230, 230, 230,
  230, 230, 230, 230, 230, 230, 230, 230, 230, 232, 220, 220,
  220, 220, 232, 216, 220, 220, 220, 220, 220, 202, 202, 240,
  220, 220, 220, 202, 202, 220, 220, 220, 220, 220, 220, 220,
  220, 220, 220, 220, 1, 1, 1, 1, 1, 220, 220, 220, 220, 230,
  230, 230,
};

// Try to compose a character from two parts
bool Compose(unsigned short& starter, unsigned short diacritic)
{
  const unsigned short *table = CompressedCompositionTable;
  const unsigned short *tableEnd = table + COMPOSITION_TABLE_SIZE;

  // create a key for the composition table
  unsigned short comp = 0;
  if (starter < 0x0300)
  {
    comp = starter;
  }
  else if (starter >= 0x1E00 && starter < 0x1F00)
  {
    comp = starter - 0x1E00 + 0x0300;
  }
  comp = (comp << 6) + (diacritic & 0x3F);

  // search the sorted table for the decomposition
  const unsigned short *it = std::lower_bound(table, tableEnd, comp);
  if (it != tableEnd && *it == comp)
  {
    // the table gave us a new starter
    starter = *(it + COMPOSITION_TABLE_SIZE);
    return true;
  }

  return false;
}

// Try to decompose a character into two parts
bool Decompose(unsigned short& code, unsigned short& diacritic)
{
  const unsigned short *ctable = CompressedCompositionTable;
  const unsigned short *table = ctable + COMPOSITION_TABLE_SIZE;
  const unsigned short *tableEnd = table + COMPOSITION_TABLE_SIZE;

  // search the unsorted composed character table
  const unsigned short *it = std::find(table, tableEnd, code);
  if (it != tableEnd)
  {
    // convert the 16-bit result into starter and diacritic
    unsigned short comp = *(it - COMPOSITION_TABLE_SIZE);
    unsigned short starter = (comp & 0xFFC0) >> 6;
    if (starter >= 0x0300)
    {
      starter += 0x1E00 - 0x0300;
    }
    // return the starter and diacritic for the decomposition
    code = starter;
    diacritic = (comp & 0x3F) + 0x0300;
    return true;
  }

  return false;
}

// Get the combining class for a character
unsigned char CombiningClass(unsigned short a)
{
  // 0x0340 and 0x0341 alias to 0x0300 and 0x301
  if (a >= 0x0300 && a < 0x0342)
  {
    return CombiningClassTable[a & 0x3F];
  }
  return 0;
}

// For sorting diacritics, always use a stable sort
bool CompareDiacritic(unsigned short a, unsigned short b)
{
  return (CombiningClassTable[a & 0x3F] < CombiningClassTable[b & 0x3F]);
}

// For sorting diacritics, specifically for CP1258
bool CompareCP1258(unsigned short a, unsigned short b)
{
  return (CombiningClassCP1258[a & 0x3F] < CombiningClassCP1258[b & 0x3F]);
}

// Do NFC normalization for starter plus diacritics
void PerformNFC(unsigned short& s, std::vector<unsigned short>& diacritics)
{
  // decompose the starter recursively
  unsigned short diacritic;
  while (Decompose(s, diacritic))
  {
    diacritics.insert(diacritics.begin(), diacritic);
  }

  // sort the diacritics
  std::stable_sort(diacritics.begin(), diacritics.end(), &CompareDiacritic);

  // compose any starter + diacritic that will compose
  std::vector<unsigned short>::iterator di = diacritics.begin();
  while (di != diacritics.end())
  {
    if (Compose(s, *di))
    {
      // successful composition, remove diacritic from list
      di = diacritics.erase(di);
    }
    else
    {
      // skip uncombined diacritic and all diacritics of the same class
      unsigned char dclass = CombiningClass(*di);
      do
      {
        ++di;
      }
      while (di != diacritics.end() && CombiningClass(*di) == dclass);
    }
  }
}

// Push a one-byte character to output, with error handling
void PushSingleByteChar(
  std::string *s, unsigned short t,
  const char *tpos, const char *endpos, const char **errpos,
  int mode)
{
  if (t < 0xFFFD)
  {
    s->push_back(static_cast<char>(t));
  }
  else if (!HandleReplacement(s, tpos, endpos, mode))
  {
    *errpos = (*errpos ? *errpos : tpos);
  }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
// Windows-1258 (Vietnamese) contains combining diacritics,
// so we normalize to NFC as part of the decoding.
size_t vtkDICOMCharacterSet::CP1258ToUTF8(
  const char *text, size_t l, std::string *s, int mode)
{
  CompressedTable table(vtkDICOMCharacterSet::Table[X_CP1258]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  unsigned short starter = 0xFFFF;
  typedef std::vector<unsigned short>::iterator IterT;
  std::vector<unsigned short> diacritics;

  while (cp != ep)
  {
    unsigned short x = static_cast<unsigned char>(*cp++);
    unsigned short code = table[x];
    bool newStarter = true;

    // check if this is a combining diacritic
    if (CombiningClass(code) != 0)
    {
      newStarter = false;
      // if it comes immediately after the starter, see if it composes
      if (!diacritics.empty() || !Compose(starter, code))
      {
        // fast-path composition failed, save the diacritic for later
        diacritics.push_back(code);
      }
    }

    // new starter or end of string
    if (newStarter || cp == ep)
    {
      if (!diacritics.empty())
      {
        // use slow-path composition
        PerformNFC(starter, diacritics);
      }
      if (starter != 0xFFFF)
      {
        // output old starter, if there was one
        UnicodeToUTF8(starter, s);
      }
      for (IterT di = diacritics.begin(); di != diacritics.end(); ++di)
      {
        // output all uncombined diacritics
        UnicodeToUTF8(*di, s);
      }
      diacritics.clear();

      if (newStarter)
      {
        // set new starter
        starter = code;

        if (starter == 0xFFFD)
        {
          // new starter not valid
          errpos = (errpos ? errpos : cp);
          BadCharsToUTF8(cp, cp+1, s, mode);
          starter = 0xFFFF;
        }
        else if (cp == ep)
        {
          // end of string, output the starter
          UnicodeToUTF8(starter, s);
        }
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
// Windows-1258 (Vietnamese) contains combining chars, so it requires
// partial decomposition during its encoding
size_t vtkDICOMCharacterSet::UTF8ToCP1258(
  const char *text, size_t l, std::string *s, int mode)
{
  CompressedTableR table(vtkDICOMCharacterSet::Reverse[X_CP1258]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  unsigned short starter = 0xFFFF;
  const char *starterpos = cp;
  typedef std::vector<unsigned short>::iterator IterT;
  std::vector<unsigned short> diacritics;

  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    bool newStarter = true;

    // check if this is a combining diacritic
    if (CombiningClass(code) != 0)
    {
      newStarter = false;
      diacritics.push_back(code);
    }

    if (newStarter || cp == ep)
    {
      if (diacritics.empty() && starter != 0xFFFF)
      {
        // output old starter if it fits the table
        unsigned short t = table[starter];
        if (t < 0xFFFD)
        {
          s->push_back(static_cast<char>(t));
          starter = 0xFFFF;
        }
      }

      if (starter != 0xFFFF)
      {
        // decompose the starter recursively
        unsigned short diacritic;
        while (Decompose(starter, diacritic))
        {
          diacritics.insert(diacritics.begin(), diacritic);
        }

        if (!diacritics.empty())
        {
          // sort into an ordering appropriate for CP1258
          std::stable_sort(diacritics.begin(), diacritics.end(),
                           &CompareCP1258);
          // find the first diacritic that composes with starter
          for (IterT di = diacritics.begin(); di != diacritics.end(); ++di)
          {
            unsigned short temp = starter;
            if (Compose(temp, *di) && table[temp] < 0xFFFD)
            {
              diacritics.erase(di);
              starter = temp;
              break;
            }
          }
        }

        // output the starter
        PushSingleByteChar(s, table[starter], starterpos, ep, &errpos, mode);
      }

      for (IterT di = diacritics.begin(); di != diacritics.end(); ++di)
      {
        // output all uncombined diacritics
        PushSingleByteChar(s, table[*di], starterpos, ep, &errpos, mode);
      }
      diacritics.clear();

      if (newStarter)
      {
        // set new starter
        starter = code;
        starterpos = lastpos;

        // if end of string or bad starter, output the starter
        if (cp == ep || starter >= 0xFFFD)
        {
          PushSingleByteChar(s, table[starter], starterpos, ep, &errpos, mode);
          starter = 0xFFFF;
        }
      }
    }
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
unsigned char vtkDICOMCharacterSet::KeyFromString(const char *name, size_t nl)
{
  const char *cp = name;
  const char *ep = name;
  int key = Unknown;

  if (cp)
  {
    ep += nl;
  }

  // Loop over backslash-separated defined terms
  for (int n = 0; cp != ep && *cp != '\0'; n++)
  {
    // strip leading spaces
    while (cp != ep && *cp == ' ') { cp++; }
    // search for end of value
    const char *dp = cp;
    while (dp != ep && *dp != '\\' && *dp != '\0') { dp++; }
    // find length of value (strip trailing spaces)
    size_t l = dp - cp;
    while (l > 0 && cp[l-1] == ' ') { l--; }

    if (l == 0)
    {
      // empty value: default is ISO_IR 6
      if (key == Unknown)
      {
        key = ISO_IR_6;
      }
    }
    else
    {
      // search for other values
      for (int i = 0; i < CHARSET_TABLE_SIZE; i++)
      {
        const char *definedTerm = Charsets[i].DefinedTerm;
        bool beginsWithBackslash = false;
        if (definedTerm && definedTerm[0] == '\\')
        {
          beginsWithBackslash = true;
          ++definedTerm;
        }
        if (definedTerm && l == strlen(definedTerm) &&
            strncmp(definedTerm, cp, l) == 0)
        {
          if (n == 0)
          {
            // set key from first value of SpecificCharacterSet
            key = i;
          }
          else if (beginsWithBackslash)
          {
            if ((i & DICOM_JP_BITS) == i)
            {
              // combine key with 2nd, 3rd value of SpecificCharacterSet
              // (specific to ISO_2022_IR_87 and ISO_2022_IR_159, which
              // combine with ISO_2022_IR_13 and with each other)
              key = (key & DICOM_JP_BITS) | i;
            }
            else
            {
              // set key from 2nd value of SpecificCharacterSet
              // (specific to ISO_2022_IR_58 and ISO_2022_IR_149)
              key = i;
            }
          }
          break;
        }
      }
    }

    cp = dp;
    if (cp != ep && *cp == '\\')
    {
      // if multi-valued, turn ISO_IR 6 to ISO 2022
      if (key == ISO_IR_6)
      {
        key = ISO_2022_IR_6;
      }
      cp++;
    }
  }

  // if no defined terms matched, look for common character set names
  if (key == Unknown && name && *name)
  {
    size_t n = vtkDICOMCharacterSet::NumberOfAliases;
    const char *const *table = vtkDICOMCharacterSet::Aliases;

    // use lowercase comparison for case insensitivity
    std::string lowername;
    lowername.reserve(nl);
    for (size_t j = 0; j < nl; j++)
    {
      char c = name[j];
      lowername.push_back((c >= 'A' && c <= 'Z') ? c + 32 : c);
    }

    const char *const *iter = std::lower_bound(table, table + n, lowername);
    size_t i = iter - table;
    if (i < n && *iter == lowername)
    {
      key = vtkDICOMCharacterSet::AliasKeys[i];
      // always activate JISX0208 if JISX0212 is active
      if (key == ISO_2022_IR_159)
      {
        key |= ISO_2022_IR_87;
      }
    }
  }

  return static_cast<unsigned char>(key);
}

//----------------------------------------------------------------------------
std::string vtkDICOMCharacterSet::GetCharacterSetString() const
{
  unsigned char key = this->Key;

  // Use the DefinedTerm if present,
  // otherwise use Name if present,
  // fallback to the key as a string.

  if (key == ISO_IR_6)
  {
    return "";
  }
  if (key < CHARSET_TABLE_SIZE)
  {
    const char* name = Charsets[key].Name;
    const char* dt = Charsets[key].DefinedTerm;

    if (dt)
    {
      return dt;
    }
    else if (name)
    {
      return name;
    }
  }
  if (key == Unknown)
  {
    return "Unknown";
  }

  std::stringstream ss;
  ss << static_cast<int>(key);

  return ss.str();
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::SingleByteToUTF8(
  const char *text, size_t l, std::string *s, int mode) const
{
  const unsigned short *tptr = vtkDICOMCharacterSet::Table[this->Key];
  if (tptr == 0)
  {
    tptr = vtkDICOMCharacterSet::Table[ISO_IR_6];
  }
  CompressedTable table(tptr);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    unsigned short x = static_cast<unsigned char>(*cp);
    unsigned int code = table[x];
    if (code == 0xFFFD)
    {
      errpos = (errpos ? errpos : cp);
      BadCharsToUTF8(cp, cp+1, s, mode);
    }
    else
    {
      UnicodeToUTF8(code, s);
    }
    cp++;
  }

  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToSingleByte(
  const char *text, size_t l, std::string *s, int mode) const
{
  const unsigned short *tptr = vtkDICOMCharacterSet::Reverse[this->Key];
  tptr = (tptr ? tptr : vtkDICOMCharacterSet::Reverse[ISO_IR_6]);
  CompressedTableR table(tptr);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    unsigned int code = UTF8ToUnicode(&cp, ep);
    unsigned short t = table[code];
    if (t < 0xFFFD)
    {
      s->push_back(static_cast<char>(t));
    }
    else if (!HandleReplacement(s, lastpos, cp, mode))
    {
      errpos = (errpos ? errpos : lastpos);
    }
  }
  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::ISO8859ToUTF8(
  const char *text, size_t l, std::string *s, int mode) const
{
  // for compatibility with strings that were encoded with Windows code
  // pages, allow Windows extensions for codes 0x80 to 0x9F
  static const unsigned short wincodes[32] = {
    0x20AC, 0xFFFD, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
    0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0xFFFD, 0x017D, 0xFFFD,
    0xFFFD, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
    0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0xFFFD, 0x017E, 0x0178
  };

  // bitfield to say which of the 32 codes are to be used
  unsigned int wincodesUsed = 0;
  switch (this->Key)
  {
    case vtkDICOMCharacterSet::ISO_IR_100: // CP1252 latin1
      wincodesUsed = 0xDFFE5FFD;
      break;
    case vtkDICOMCharacterSet::ISO_IR_148: // CP1254 turkish
      wincodesUsed = 0x9FFE1FFD;
      break;
    case vtkDICOMCharacterSet::ISO_IR_166: // CP874 thai
      wincodesUsed = 0x00FE0021;
      break;
    default:
      break;
  }

  CompressedTable table(vtkDICOMCharacterSet::Table[this->Key]);

  const char *errpos = 0;
  const char *cp = text;
  const char *ep = text + l;
  while (cp != ep)
  {
    const char *lastpos = cp;
    char c = *cp++;
    if ((c & 0x80) == 0)
    {
      s->push_back(c); // ascii
    }
    else
    {
      unsigned short x = static_cast<unsigned char>(c);
      unsigned int code = table[x];
      // check for Windows extensions
      if (x < 0xA0)
      {
        x -= 0x80;
        if (((1u << x) & wincodesUsed) != 0)
        {
          code = wincodes[x];
        }
      }
      if (code == 0xFFFD)
      {
        errpos = (errpos ? errpos : lastpos);
        BadCharsToUTF8(lastpos, cp, s, mode);
      }
      else
      {
        UnicodeToUTF8(code, s);
      }
    }
  }
  return (errpos ? errpos-text : cp-text);
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::UTF8ToISO2022(
  const char *text, size_t l, std::string *s, int mode) const
{
  // check for iso-2022-jp encoding
  if ((this->Key & DICOM_JP_BITS) == this->Key ||
      (this->Key >= X_ISO_2022_JP && this->Key <= X_ISO_2022_JP_EXT))
  {
    return UTF8ToJISX(this->Key, text, l, s, mode);
  }

  // code for ISO 2022 encodings that use G1
  const char *escCode = "";
  if (this->Key == ISO_2022_IR_58)
  {
    escCode = "\033$)A";
  }
  else if (this->Key == ISO_2022_IR_149)
  {
    escCode = "\033$)C";
  }

  const char *cp = text;
  const char *ep = cp + l;
  while (cp != ep)
  {
    bool hasG1 = false;
    const char *dp = cp;
    char checkAscii = 0;
    // loop until the end of the current line
    while (dp != ep && !IsEndLine(*dp) && *dp != '\033' &&
           *dp != '\016' && *dp != '\017')
    {
      checkAscii |= *dp;
      dp++;
    }
    while (dp != ep && IsEndLine(*dp))
    {
      hasG1 = false;
      dp++;
    }

    size_t m = dp - cp;
    if ((checkAscii & 0x80) == 0)
    {
      // segment between delims is pure ascii
      s->append(cp, m);
    }
    else
    {
      // add the escape code
      if (!hasG1)
      {
        s->append(escCode);
        hasG1 = true;
      }
      // write the encoded text
      size_t n;
      if (this->Key == ISO_2022_IR_58)
      {
        n = this->UTF8ToGB2312(cp, m, s, mode);
      }
      else if (this->Key == ISO_2022_IR_149)
      {
        n = this->UTF8ToEUCKR(cp, m, s, mode);
      }
      else
      {
        n = this->UTF8ToSingleByte(cp, m, s, mode);
      }
      // check for conversion error
      if (n < m)
      {
        n += cp - text;
        SetErrorPosition(l, n);
      }
    }

    // guard against escape codes in original string
    if (dp != ep && (*dp == '\033' || *dp == '\016' || *dp == '\017'))
    {
      cp = dp++;
      if (!HandleReplacement(s, cp, dp, mode))
      {
        SetErrorPosition(l, cp - text);
      }
    }

    cp = dp;
  }

  return l;
}

//----------------------------------------------------------------------------
// For DICOM, ISO 2022 decoding does not start with a blank slate,
// for example if SpecificCharacterSet contains 'ISO 2022 IR 13'
// then G0 is ISO IR 14 and G1 is ISO IR 13 when decoding starts.
unsigned int vtkDICOMCharacterSet::InitISO2022(
  unsigned char charsetG[4]) const
{
  charsetG[0] = ISO_2022_IR_6;
  charsetG[1] = Unknown;
  charsetG[2] = Unknown;
  charsetG[3] = Unknown;

  // This tracks some ISO 2022 state information, such as whether the
  // active character sets are multi-byte.
  unsigned int state = 0;

  // Check that charsetG1 is within the enumerated range for ISO 2022
  if (this->Key <= ISO_2022_MAX)
  {
    // Mask with ISO_2022_BASE, which removes the ISO 2022 flag bit
    // (this is so we can use AnyToUTF8() to decode the G1 charset)
    charsetG[1] = (this->Key & ISO_2022_BASE);

    if (charsetG[1] >= X_EUCKR)
    {
      // ISO IR 149 (Korean) and beyond are 94x94 charsets
      state |= MULTIBYTE_G1;
    }
    else if (charsetG[1] >= ISO_IR_100)
    {
      // the ISO-8859 character sets contain 96 chars (0xA0 to 0xFF)
      state |= CHARSET96_G1;
    }

    // For Japanese in DICOM, if ISO IR 13 is set, then it is designated
    // to G1 immediately (with ISO IR 14 implicitly designated to G0).
    // But ISO IR 87 and ISO IR 159 are not designated to G0 until after
    // their escape codes.
    if ((charsetG[1] & DICOM_JP_BITS) == charsetG[1])
    {
      charsetG[1] &= ISO_IR_13;
      if (charsetG[1] == ISO_IR_13)
      {
        // implies ISO 2022 IR 14 (it has no distinct enum value)
        charsetG[0] = ISO_2022_IR_13;
      }
    }
  }
  else
  {
    // indicate any non-iso-2022 encoding in the state
    state = this->Key;
  }

  return state;
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::ISO2022ToUTF8(
  const char *text, size_t l, std::string *s, int mode) const
{
  // Decodes text that uses ISO-2022 escape codes to switch character sets.

  // Note that the SI/SO control characters (Shift Out, Shift In) are
  // not allowed, so this cannot be used for iso-2022-cn or iso-2022-kr.
  // Instead, the decoder expects DICOM's 8-bit form of these 7-bit encodings
  // where the character set is designated with an escape code, but the high
  // bit indicates the shift status.

  // Get the initial settings of the ISO 2022 decoder
  unsigned char charsetG[4]; // G0, G1, G2, G3 charsets
  unsigned int state = this->InitISO2022(charsetG);

  // loop through the string, looking for iso-2022 escape codes,
  // and when an escape code is found, change the charset
  size_t m;
  size_t n = l;
  size_t i = 0;
  while (i < l)
  {
    // search for the next control code (ESC CR NL VT FF SO SI),
    // which will be the delimiter for our conversion
    size_t j = i;
    for (; j < l; j++)
    {
      if (text[j] == '\033' || (text[j] >= '\012' && text[j] <= '\017'))
      {
        break;
      }
    }

    if (i < j)
    {
      // now we convert all characters between "i" and "j" exclusive
      if ((state & ALTERNATE_CS) != 0)
      {
        // The current encoding is not ISO-2022
        vtkDICOMCharacterSet cs(state & ALTERNATE_CS);
        m = cs.AnyToUTF8(&text[i], j-i, s, mode);
      }
      else if (charsetG[0] == ISO_2022_IR_6 && // <- ASCII in G0
               charsetG[1] != ISO_IR_13) // <- no katakana in G1
      {
        // When G0 is ASCII, simply apply G1 charset to this segment
        // (unless G1 is ISO_IR_13, which requires the JISXToUTF8 function)
        vtkDICOMCharacterSet cs(charsetG[1] & ISO_2022_BASE);
        m = cs.AnyToUTF8(&text[i], j-i, s, mode);
      }
      else if (charsetG[0] == ISO_IR_13 || // <- katakana in G0
               charsetG[0] == ISO_2022_IR_6 ||
               charsetG[0] == ISO_2022_IR_13 || // <- romaji in G0
               charsetG[0] == ISO_2022_IR_87 ||
               charsetG[0] == ISO_2022_IR_159 ||
               charsetG[0] == ISO_2022_IR_149 ||
               charsetG[0] == ISO_2022_IR_58)
      {
        // These are the G0 charsets that are supported by our JISX decoder,
        // all are part of iso-2022-jp-2 (and iso-2022-jp, of course)
        m = JISXToUTF8(charsetG[0], charsetG[1], &text[i], j-i, s, mode);
      }
      else if ((state & MULTIBYTE_G0) != 0)
      {
        // If G0 is a multibyte charset not supported by our JISX decoder,
        // then the only characters we will keep are the control chars and
        // space. All other characters will be marked invalid (0xFFFD).
        m = UnknownToUTF8(&text[i], j-i, s, mode);
      }
      else
      {
        // This branch is taken for unknown character sets, where we know
        // that G0 is not designated as a multibyte character set.  Here
        // we assume G0 is an ISO 646 character set that shares most of
        // its code points with ASCII.
        m = ASCIIToUTF8(&text[i], j-i, s, mode);
      }

      // If not all chars were decoded, there was a decoding error
      if (m != j - i)
      {
        SetErrorPosition(n, i + m);
      }
    }

    // Process any control codes
    i = j;
    while (i < l && (text[i] >= '\012' && text[i] <= '\015'))
    {
      if (text[i] == '\n' || text[i] == '\f')
      {
        // Clear G2/G3 (for iso-2022-jp-2, other encodings never set G2/G3)
        charsetG[2] = Unknown;
        charsetG[3] = Unknown;
      }
      i++;
    }
    if (j < i)
    {
      s->append(&text[j], i - j);
    }

    // SI SO (shift-in, shift-out) are not allowed
    if (i < l && (text[i] == '\016' || text[i] == '\017'))
    {
      SetErrorPosition(n, i);
      BadCharsToUTF8(&text[i], &text[i + 1], s, mode);
      i++;
    }

    // Process any escape codes
    while (i < l && text[i] == '\033')
    {
      // Save position and advance past ESC
      size_t savePos = i++;
      bool escapeFail = false;
      int shift = 0;

      // Parse the escape sequence
      const char *escapeCode = &text[i];
      size_t escapeLen = EscapeCodeLength(escapeCode, l-i);
      i += escapeLen;

      if ((state & ALTERNATE_CS) != 0)
      {
        // Encoding is not ISO 2022, pass escapes to output
        s->push_back('\033');
        s->append(escapeCode, escapeLen);
        break;
      }

      // Process ISO 2022 escape codes
      switch (EscapeCode(escapeCode, escapeLen, &state))
      {
        case CODE_ACS:
          // Announcer code sequence
          escapeFail = true;
          break;
        case CODE_CZD:
        case CODE_C1D:
          // C0 and C1 designate control set
          escapeFail = true;
          break;
        case CODE_GZD:
          // G0 designate character set
          charsetG[0] = CharacterSetFromEscapeCode(escapeCode, escapeLen);
          escapeFail = (charsetG[0] == Unknown);
          break;
        case CODE_G1D:
          // G1 designate character set
          charsetG[1] = CharacterSetFromEscapeCode(escapeCode, escapeLen);
          escapeFail = (charsetG[1] == Unknown);
          break;
        case CODE_G2D:
          // G2 designate character set
          charsetG[2] = CharacterSetFromEscapeCode(escapeCode, escapeLen);
          escapeFail = (charsetG[2] == Unknown);
          break;
        case CODE_G3D:
          // G3 designate character set
          charsetG[3] = CharacterSetFromEscapeCode(escapeCode, escapeLen);
          escapeFail = (charsetG[3] == Unknown);
          break;
        case CODE_DOCS:
          // Switch to other encoding, such as UTF-8
          // state ^= (state & ALTERNATE_CS);
          // state ^= CharacterSetFromEscapeCode(escapeCode, escapeLen);
          escapeFail = true;
          break;
        case CODE_CMD:
          // This indicates the end of ISO 2022 processing!
          escapeFail = true;
          break;
        case CODE_IRR:
          // Identify revised registration, e.g. ESC &@ ESC $B indicates
          // JIS X 0208:1990 should be used instead of JIS X 0208:1983
          escapeFail = (escapeCode[1] != '@' || i == l || text[i] != '\033');
          break;
        case CODE_SS2:
          // Single-shift two
          shift = 2;
          escapeFail = (charsetG[2] == Unknown);
          break;
        case CODE_SS3:
          // Single-shift three
          shift = 3;
          escapeFail = (charsetG[3] == Unknown);
          break;
        case CODE_LS2:
        case CODE_LS3:
        case CODE_LS1R:
        case CODE_LS2R:
        case CODE_LS3R:
          // Various locking shifts, we do not handle these
          escapeFail = true;
          break;
        case CODE_OTHER:
          // pass escape code verbatim to output
          s->push_back('\033');
          s->append(escapeCode, escapeLen);
          break;
        case CODE_ERROR:
          // illegal escape code
          escapeFail = true;
      }

      if (!escapeFail && shift != 0)
      {
        escapeFail = true;
        if (i < l && (state & ALTERNATE_CS) == 0)
        {
          // Perform a single-shift (one character).
          bool multibyte = ((state & (MULTIBYTE_G0 << shift)) != 0);
          bool charset96 = ((state & (CHARSET96_GX << shift)) != 0);
          char shiftchars[2] = { '\0', '\0' };
          size_t bytecount = (multibyte ? 2 : 1);
          size_t k;
          for (k = 0; i < l && k < bytecount; i++, k++)
          {
            // Make sure byte values are in the correct range
            unsigned char cGR = static_cast<unsigned char>(text[i] | 0x80);
            if ((cGR >= 0xA1 && cGR <= 0xAE) || (charset96 && cGR >= 0xA0))
            {
              shiftchars[k] = static_cast<char>(cGR);
              continue;
            }
            break;
          }
          if (k > 0)
          {
            // Attempt conversion of single character
            escapeFail = false;
            vtkDICOMCharacterSet cs(charsetG[shift]);
            m = cs.AnyToUTF8(shiftchars, k, s, mode);
            if (m != bytecount)
            {
              // Error due to bad character
              SetErrorPosition(n, i - k + m);
            }
          }
        }
      }

      if (escapeFail)
      {
        // Unhandled ISO 2022 escape codes are considered errors
        SetErrorPosition(n, savePos);
        BadCharsToUTF8(&text[savePos], &text[i], s, mode);
      }
    }
  }

  return n;
}

//----------------------------------------------------------------------------
std::string vtkDICOMCharacterSet::FromUTF8(
  const char *text, size_t l, size_t *lp) const
{
  int mode = (lp ? UTF8_STRICT : UTF8_REPLACE);
  std::string s;
  if (this->IsISO2022())
  {
    l = this->UTF8ToISO2022(text, l, &s, mode);
  }
  else switch (this->Key)
  {
    case X_EUCKR:
      l = UTF8ToEUCKR(text, l, &s, mode);
      break;
    case X_GB2312:
      l = UTF8ToGB2312(text, l, &s, mode);
      break;
    case ISO_IR_192: // UTF-8
      l = UTF8ToUTF8(text, l, &s, mode);
      break;
    case GB18030:
      l = UTF8ToGB18030(text, l, &s, mode);
      break;
    case GBK:
      l = UTF8ToGBK(text, l, &s, mode);
      break;
    case X_BIG5:
      l = UTF8ToBig5(text, l, &s, mode);
      break;
    case X_EUCJP:
      l = UTF8ToEUCJP(text, l, &s, mode);
      break;
    case X_SJIS:
      l = UTF8ToSJIS(text, l, &s, mode);
      break;
    case X_CP1258:
      l = UTF8ToCP1258(text, l, &s, mode);
      break;
    default:
      l = this->UTF8ToSingleByte(text, l, &s, mode);
      break;
  }
  if (lp) { *lp = l; }
  return s;
}

//----------------------------------------------------------------------------
std::string vtkDICOMCharacterSet::ToUTF8(
  const char *text, size_t l, size_t *lp) const
{
  std::string s;
  l = this->AnyToUTF8(text, l, &s, (lp ? UTF8_STRICT : UTF8_REPLACE));
  if (lp)
  {
    *lp = l;
  }
  return s;
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::AnyToUTF8(
  const char *text, size_t l, std::string *s, int mode) const
{
  if (this->Key == ISO_IR_6)
  {
    l = ASCIIToUTF8(text, l, s, mode);
  }
  else if (this->IsISO2022())
  {
    l = ISO2022ToUTF8(text, l, s, mode);
  }
  else if (this->IsISO8859())
  {
    l = ISO8859ToUTF8(text, l, s, mode);
  }
  else switch (this->Key)
  {
    case X_EUCKR:
      l = EUCKRToUTF8(text, l, s, mode);
      break;
    case X_GB2312:
      l = GB2312ToUTF8(text, l, s, mode);
      break;
    case ISO_IR_192: // UTF-8
      l = UTF8ToUTF8(text, l, s, mode);
      break;
    case GB18030:
      l = GB18030ToUTF8(text, l, s, mode);
      break;
    case GBK:
      l = GBKToUTF8(text, l, s, mode);
      break;
    case X_BIG5:
      l = Big5ToUTF8(text, l, s, mode);
      break;
    case X_EUCJP:
      l = EUCJPToUTF8(text, l, s, mode);
      break;
    case X_SJIS:
      l = SJISToUTF8(text, l, s, mode);
      break;
    case X_CP1258:
      l = CP1258ToUTF8(text, l, s, mode);
      break;
    default:
      l = SingleByteToUTF8(text, l, s, mode);
      break;
  }

  return l;
}

//----------------------------------------------------------------------------
// Obsolete method, kept for backwards compatibility
std::string vtkDICOMCharacterSet::ConvertToUTF8(
  const char *text, size_t l) const
{
  return ToUTF8(text, l);
}

//----------------------------------------------------------------------------
std::string vtkDICOMCharacterSet::ToSafeUTF8(
  const char *text, size_t l) const
{
  std::string s;
  this->AnyToUTF8(text, l, &s, UTF8_ESCAPE);
  std::string t;

  // scan the string for codes that are unsafe to print to a console
  const char *lp = s.data();
  const char *cp = lp;
  const char *ep = lp + s.length();
  while (cp != ep)
  {
    const char *dp = cp;
    unsigned char a = static_cast<unsigned char>(*cp++);
    if (a < 0x20 || a == 0x7f || a == '\\')
    {
      // C0 control code and backslash
      t.append(lp, dp);
      OctalCharCode(&t, a);
      lp = cp;
    }
    else if ((a & 0xC0) == 0xC0  && cp != ep)
    {
      unsigned char b = static_cast<unsigned char>(*cp++);
      if (a == 0xC2 && b < 0xA0)
      {
        // C1 control code
        t.append(lp, dp);
        OctalCharCode(&t, b);
        lp = cp;
      }
      else if ((a & 0xE0) == 0xE0 && cp != ep)
      {
        unsigned char c = static_cast<unsigned char>(*cp++);
        if (a == 0xED && (b & 0xF0) == 0xB0)
        {
          // UTF-16 low surrogate used to store bad char
          unsigned short d = ((b & 0x0F) << 6) | (c & 0x3F);
          if (d <= 0xFF)
          {
            t.append(lp, dp);
            OctalCharCode(&t, static_cast<unsigned char>(d));
            lp = cp;
          }
        }
        else if ((a & 0xF0) == 0xF0 && cp != ep)
        {
          cp++;
        }
      }
    }
  }

  // if scan didn't find anything to change, return the string
  if (lp == s.data())
  {
    return s;
  }

  // return the safetied string
  t.append(lp, ep);
  return t;
}

//----------------------------------------------------------------------------
std::string vtkDICOMCharacterSet::CaseFoldedUTF8(
  const char *text, size_t l) const
{
  std::string s;
  std::string t;

  const char *cp = text;
  const char *ep = text + l;

  if (this->Key != ISO_IR_192) // UTF-8
  {
    t = this->ToUTF8(text, l);
    cp = t.data();
    ep = cp + t.length();
  }

  while (cp != ep)
  {
    unsigned int code = UTF8ToUnicode(&cp, ep);
    if (code == 0xFFFF)
    {
      // Since 0xFFFF is not permitted, convert to 0xFFFD
      code = 0xFFFD;
    }
    if (code != 0xFFFE)
    {
      CaseFoldUnicode(code, &s);
    }
  }

  return s;
}

//----------------------------------------------------------------------------
size_t vtkDICOMCharacterSet::NextBackslash(
  const char *text, const char *ep) const
{
  const char *cp = text;

  if (this->Key == GB18030 || this->Key == GBK)
  {
    // ensure backslash isn't second part of a multi-byte character
    while (cp != ep && *cp != '\0')
    {
      if (static_cast<unsigned char>(*cp) >= 0x81)
      {
        cp++;
        if (cp != ep && static_cast<unsigned char>(*cp) >= 0x21)
        {
          cp++;
        }
      }
      else if (*cp != '\\')
      {
        cp++;
      }
      else
      {
        break;
      }
    }
  }
  else if (this->Key == X_SJIS)
  {
    // ensure backslash isn't second part of a Shift-JIS character
    while (cp != ep && *cp != '\0')
    {
      unsigned char x = static_cast<unsigned char>(*cp);
      if ((x >= 0x81 && x <= 0x9F) || (x >= 0xE0 && x <= 0xFC))
      {
        cp++;
        if (cp != ep && static_cast<unsigned char>(*cp) >= 0x40 &&
            static_cast<unsigned char>(*cp) <= 0xFC &&
            static_cast<unsigned char>(*cp) != 0x7F)
        {
          cp++;
        }
      }
      else if (*cp != '\\')
      {
        cp++;
      }
      else
      {
        break;
      }
    }
  }
  else if (this->Key == X_BIG5)
  {
    // ensure backslash isn't second part of a Big5 character
    while (cp != ep && *cp != '\0')
    {
      unsigned char x = static_cast<unsigned char>(*cp);
      if ((x >= 0x81 && x <= 0xFE))
      {
        cp++;
        if (cp != ep &&
            ((static_cast<unsigned char>(*cp) >= 0x40 &&
              static_cast<unsigned char>(*cp) <= 0x7E) ||
            ((static_cast<unsigned char>(*cp) >= 0xA1 &&
              static_cast<unsigned char>(*cp) <= 0xFE))))
        {
          cp++;
        }
      }
      else if (*cp != '\\')
      {
        cp++;
      }
      else
      {
        break;
      }
    }
  }
  else if (this->IsISO2022())
  {
    // ensure backslash isn't part of a G0 multi-byte code
    // or a shifted G2 or G3 character set, this code must
    // match behavior of ISO2022ToUTF8()
    unsigned char charsetG2 = Unknown;
    unsigned char charsetG3 = Unknown;
    unsigned int state = 0;
    int shiftcount = 0;
    bool charset96 = false;
    while (cp != ep && *cp != '\0')
    {
      // look for iso 2022 escape code
      if (*cp == '\033')
      {
        cp++;
        shiftcount = 0;
        size_t l = EscapeCodeLength(cp, ep-cp);
        switch(EscapeCode(cp, l, &state))
        {
          case CODE_G2D:
            charsetG2 = CharacterSetFromEscapeCode(cp, l);
            break;
          case CODE_G3D:
            charsetG3 = CharacterSetFromEscapeCode(cp, l);
            break;
          case CODE_SS2:
            if (charsetG2 != Unknown)
            {
              shiftcount = ((state & MULTIBYTE_G2) ? 2 : 1);
              charset96 = ((state & CHARSET96_G2) != 0);
            }
            break;
          case CODE_SS3:
            if (charsetG3 != Unknown)
            {
              shiftcount = ((state & MULTIBYTE_G3) ? 2 : 1);
              charset96 = ((state & CHARSET96_G3) != 0);
            }
            break;
          default:
            break;
        }
        // do not advance past backslashes in the escape sequence
        for (size_t i = 0; i < l; i++)
        {
          if (*cp == '\\')
          {
            break;
          }
          cp++;
        }
      }
      else if (IsEndLine(*cp))
      {
        // look for CRNL line ending, reset state if present
        char prevchar = *cp++;
        while (cp != ep && IsEndLine(*cp))
        {
          if (prevchar == '\r' && *cp == '\n')
          {
            charsetG2 = Unknown;
            charsetG3 = Unknown;
            state = 0;
            shiftcount = 0;
          }
          prevchar = *cp++;
        }
      }
      else if (shiftcount)
      {
        // skip over any single-shifted character, one octet at a time
        unsigned char cGL = static_cast<unsigned char>(*cp & 0x7F);
        if ((cGL >= 0x21 && cGL <= 0x7E) || (charset96 && cGL >= 0x20))
        {
          cp++;
          shiftcount--;
        }
        else
        {
          shiftcount = 0;
        }
      }
      else if ((state & MULTIBYTE_G0) != 0)
      {
        // when G0 is multibyte, any backslash is just half a character
        cp++;
      }
      else if (*cp != '\\')
      {
        // skip over non-backslash characters
        cp++;
      }
      else
      {
        // this indicates we found a valid backslash
        break;
      }
    }
  }
  else
  {
    // no special encoding, so backslash is backslash
    while (cp != ep && *cp != '\0')
    {
      if (*cp == '\\')
      {
        break;
      }
      cp++;
    }
  }

  return (cp - text);
}

//----------------------------------------------------------------------------
unsigned int vtkDICOMCharacterSet::CountBackslashes(
  const char *text, size_t l) const
{
  unsigned int count = 0;
  const char *cp = text;
  const char *ep = text + l;

  while (cp != ep && *cp != '\0')
  {
    cp += this->NextBackslash(cp, ep);
    if (cp != ep && *cp == '\\')
    {
      cp++;
      count++;
    }
  }

  return count;
}

//----------------------------------------------------------------------------
// Return an integer code that indicates the type of the escape code.
// Also update information about the ISO 2022 state: the state is maintained
// as a bitfield where e.g. MULTIBYTE_G0 indicates that G0 is a multibyte
// character set and e.g. CHARSET96_G1 indicates that G1 reserves 96
// graphical characters from 0x20 to 0x7F instead of 94 from 0x21 to 0x7E.
vtkDICOMCharacterSet::EscapeType vtkDICOMCharacterSet::EscapeCode(
  const char *cp, size_t l, unsigned int *state)
{
  if (l == 1)
  {
    switch (cp[0])
    {
      case 'N':
        return CODE_SS2;
      case 'O':
        return CODE_SS3;
      case 'n':
        return CODE_LS2;
      case 'o':
        return CODE_LS3;
      case '~':
        return CODE_LS1R;
      case '}':
        return CODE_LS2R;
      case '|':
        return CODE_LS3R;
      default:
        return CODE_OTHER;
    }
  }
  else if (l == 2)
  {
    switch (cp[0])
    {
      case ' ':
        return CODE_ACS;
      case '!':
        return CODE_CZD;
      case '\"':
        return CODE_C1D;
      case '%':
        return CODE_DOCS;
      case '&':
        return CODE_IRR;
      case '\'':
        return CODE_ERROR;
      case '$':
        *state |= MULTIBYTE_G0;
        return CODE_GZD;
      case '(':
        *state &= ~MULTIBYTE_G0;
        return CODE_GZD;
      case ')':
        *state &= ~(MULTIBYTE_G1 | CHARSET96_G1);
        return CODE_G1D;
      case '*':
        *state &= ~(MULTIBYTE_G2 | CHARSET96_G2);
        return CODE_G2D;
      case '+':
        *state &= ~(MULTIBYTE_G2 | CHARSET96_G2);
        return CODE_G3D;
      case ',':
        return CODE_ERROR;
      case '-':
        *state &= ~MULTIBYTE_G1;
        *state |= CHARSET96_G1;
        return CODE_G1D;
      case '.':
        *state &= ~MULTIBYTE_G2;
        *state |= CHARSET96_G2;
        return CODE_G2D;
      case '/':
        *state &= ~MULTIBYTE_G3;
        *state |= CHARSET96_G3;
        return CODE_G3D;
      default:
        return CODE_OTHER;
    }
  }
  else if (l == 3 && cp[0] == '$')
  {
    switch (cp[1])
    {
      case '(':
        *state |= MULTIBYTE_G0;
        return CODE_GZD;
      case ')':
        *state |= MULTIBYTE_G1;
        *state &= ~CHARSET96_G1;
        return CODE_G1D;
      case '*':
        *state |= MULTIBYTE_G2;
        *state &= ~CHARSET96_G1;
        return CODE_G2D;
      case '+':
        *state |= MULTIBYTE_G3;
        *state &= ~CHARSET96_G1;
        return CODE_G3D;
      case '-':
        *state |= (MULTIBYTE_G1 | CHARSET96_G1);
        return CODE_G1D;
      case '.':
        *state |= (MULTIBYTE_G2 | CHARSET96_G2);
        return CODE_G2D;
      case '/':
        *state |= (MULTIBYTE_G3 | CHARSET96_G3);
        return CODE_G3D;
      default:
        return CODE_ERROR;
    }
  }
  else if (l == 3 && cp[0] == '%' && cp[1] == '/')
  {
    return CODE_DOCS;
  }
  else if (l > 0)
  {
    switch (cp[0])
    {
      case ' ':
      case '!':
      case '\"':
      case '%':
      case '&':
      case '\'':
      case '$':
      case '(':
      case ')':
      case '*':
      case '+':
      case ',':
      case '-':
      case '.':
      case '/':
        return CODE_ERROR;
      default:
        return CODE_OTHER;
    }
  }

  return CODE_ERROR;
}

//----------------------------------------------------------------------------
unsigned char vtkDICOMCharacterSet::CharacterSetFromEscapeCodeJP(
  const char *code, size_t l) const
{
  // escape codes for the iso-2022-jp family of encodings
  if (l == 2)
  {
    if (code[0] == '(') // designate G0 94-set
    {
      switch (code[1])
      {
        case 'B': // ascii
          return ISO_2022_IR_6;
        case 'I': // katakana in G0
          return ISO_IR_13;
        case 'J': // JIS X 0201 romaji
          return ISO_2022_IR_13; // implies ISO 2022 IR 14
      }
    }
    else if (code[0] == '$') // designate G0 multibyte
    {
      switch (code[1])
      {
        case '@': // JIS X 0208-1978 (not used when encoding)
          return ISO_2022_IR_87;
        case 'A': // GB2312-1980 chinese
          return ISO_2022_IR_58;
        case 'B': // JIS X 0208-1983
          return ISO_2022_IR_87;
      }
    }
    else if (code[0] == '.' && this->Key == X_ISO_2022_JP_2) // designate G2
    {
      switch (code[1])
      {
        case 'A': // ISO-8859-1 latin1
          return ISO_2022_IR_100;
        case 'F': // ISO-8859-7 greek
          return ISO_2022_IR_126;
      }
    }
  }
  else if (l == 3 && code[0] == '$' && code[1] == '(')
  {
    switch (code[2])
    {
      case 'C': // JIS X 0212 japanese supplementary
        return ISO_2022_IR_149;
      case 'D': // KS X 1001-1992 korean
        return ISO_2022_IR_159;
    }
  }

  return Unknown;
}

//----------------------------------------------------------------------------
unsigned char vtkDICOMCharacterSet::CharacterSetFromEscapeCode(
  const char *code, size_t l) const
{
  if (this->Key >= X_ISO_2022_JP && this->Key <= X_ISO_2022_JP_EXT)
  {
    // check codes specific to the ISO 2022 JP encodings
    return CharacterSetFromEscapeCodeJP(code, l);
  }

  // look through the table for other known escape codes
  for (unsigned char k = ISO_2022_MIN; k <= ISO_2022_MAX; k++)
  {
    const char *escape = Charsets[k].EscapeCode;
    if (escape && strncmp(code, escape, l) == 0)
    {
      return k;
    }
  }

  if (l == 2 && code[0] == ')' && code[1] == 'I')
  {
    // designate half-width katakana to G1 (not in table)
    return ISO_IR_13;
  }

  return Unknown;
}

//----------------------------------------------------------------------------
ostream& operator<<(ostream& o, const vtkDICOMCharacterSet& a)
{
  std::string s = a.GetCharacterSetString();
  if (s.length() == 0)
  {
    s = (a.GetKey() == vtkDICOMCharacterSet::ISO_IR_6 ?
         "ISO_IR 6" :
         "Unknown");
  }
  else if (s[0] == '\\')
  {
    s.insert(0, "ISO 2022 IR 6");
  }
  return o << s.c_str();
}
