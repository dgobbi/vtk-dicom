#include "vtkDICOMValue.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"

#include <vtkSmartPointer.h>

#include <sstream>

#include <string.h>
#include <stdlib.h>

// macro for performing tests
#define TestAssert(t) \
if (!(t)) \
{ \
  cout << exename << ": Assertion Failed: " << #t << "\n"; \
  cout << __FILE__ << ":" << __LINE__ << "\n"; \
  cout.flush(); \
  rval |= 1; \
}

// order is character set, utf-8, native encoding
static const char *ClunieText[][3] = {
{ "ISO_IR 138",
  "\xd7\xa9\xd7\xa8\xd7\x95\xd7\x9f^\xd7\x93\xd7\x91\xd7\x95\xd7\xa8\xd7\x94",
  "\xf9\xf8\xe5\xef^\xe3\xe1\xe5\xf8\xe4" },
{ "ISO_IR 144",
  "\xd0\x9b\xd1\x8e\xd0\xba\x63\x65\xd0\xbc\xd0\xb1yp\xd0\xb3",
  "\xbb\xee\xda\x63\x65\xdc\xd1yp\xd3" },
{ "ISO_IR 127",
  "\xd9\x82\xd8\xa8\xd8\xa7\xd9\x86\xd9\x8a^\xd9\x84\xd9\x86\xd8\xb2\xd8\xa7\xd8\xb1",
  "\xe2\xc8\xc7\xe6\xea^\xe4\xe6\xd2\xc7\xd1" },
{ "ISO_IR 100",
  "\xc3\x84neas^R\xc3\xbc\x64iger",
  "\xc4neas^R\xfc\x64iger" },
{ "ISO_IR 100",
  "Buc^J\xc3\xa9r\xc3\xb4me",
  "Buc^J\xe9r\xf4me" },
{ "ISO_IR 126",
  "\xce\x94\xce\xb9\xce\xbf\xce\xbd\xcf\x85\xcf\x83\xce\xb9\xce\xbf\xcf\x82",
  "\xc4\xe9\xef\xed\xf5\xf3\xe9\xef\xf2" },
{ "GB18030",
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe4\xb8\x9c=",
  "Wang^XiaoDong=\xcd\xf5^\xd0\xa1\xb6\xab=" },
{ "GBK",
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe4\xb8\x9c=",
  "Wang^XiaoDong=\xcd\xf5^\xd0\xa1\xb6\xab=" },
{ "\\ISO 2022 IR 58",
  "1. \xe7\xac\xac\xe4\xb8\x80\xe8\xa1\x8c\xe6\x96\x87\xe5\xad\x97\xe3\x80\x82\r\n",
  "1. \x1b$)A\xb5\xda\xd2\xbb\xd0\xd0\xce\xc4\xd7\xd6\xa1\xa3\x1b(B\r\n" },
{ "ISO_IR 192",
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe6\x9d\xb1=",
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe6\x9d\xb1=" },
{ "\\ISO 2022 IR 149",
  "Hong^Gildong=\xe6\xb4\xaa^\xe5\x90\x89\xe6\xb4\x9e=\xed\x99\x8d^\xea\xb8\xb8\xeb\x8f\x99",
  "Hong^Gildong=\x1b$)C\xfb\xf3^\x1b$)C\xd1\xce\xd4\xd7=\x1b$)C\xc8\xab^\x1b$)C\xb1\xe6\xb5\xbf" },
{ "ISO 2022 IR 13\\ISO 2022 IR 87",
  "\xef\xbe\x94\xef\xbe\x8f\xef\xbe\x80\xef\xbe\x9e^\xef\xbe\x80\xef\xbe\x9b\xef\xbd\xb3=\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e=\xe3\x82\x84\xe3\x81\xbe\xe3\x81\xa0^\xe3\x81\x9f\xe3\x82\x8d\xe3\x81\x86",
  "\xd4\xcf\xc0\xde^\xc0\xdb\xb3=\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J=\x1b$B$d$^$@\x1b(J^\x1b$B$\x3f$m$&\x1b(J" },
{ "\\ISO 2022 IR 87",
  "Yamada^Tarou=\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e=\xe3\x82\x84\xe3\x81\xbe\xe3\x81\xa0^\xe3\x81\x9f\xe3\x82\x8d\xe3\x81\x86",
  "Yamada^Tarou=\x1b$B;3ED\x1b(B^\x1b$BB@O:\x1b(B=\x1b$B$d$^$@\x1b(B^\x1b$B$\x3f$m$&\x1b(B" },
{ 0, 0, 0 }
};

// order is character set, utf-8, native encoding
static const char *OtherText[][3] = {
{ "GB18030",
  "Linear1: \xc2\x80 to \xef\xbf\xbd\n"
  "Linear2: \xf0\x90\x80\x80 to \xf4\x8f\xbf\xbf\n",
  "Linear1: \x81\x30\x81\x30 to \x84\x31\xa4\x37\n"
  "Linear2: \x90\x30\x81\x30 to \xe3\x32\x9a\x35\n" },
{ "ISO 2022 IR 13\\ISO 2022 IR 87\\ISO 2022 IR 159",
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "JISX0201: \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a\n",
  "JISX0208: \x1b$B855$\x1b(J\n"
  "JISX0212: \x1b$BqV\x1b$(DiQ\x1b(J\n"
  "JISX0201: \xba\xdd\xc6\xc1\xca\n" },
{ "iso-2022-jp-2",
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "Katakana: \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a\n"
  "Chinese:  \xe5\xbc\x80\xe5\x8f\x91\n"
  "Korean:   \xec\x95\x88\xeb\x85\x95\xed\x95\x98\xec\x84\xb8\xec\x9a\x94\n"
  "French:   Tr\xc3\xa8s bien\n"
  "Greek:    \xce\xbc\xce\xb5\xce\xb3\xce\xac\xce\xbb\xce\xb7\n",
  "JISX0208: \x1b$B855$\x1b(B\n"
  "JISX0212: \x1b$BqV\x1b$(DiQ\x1b(B\n"
  "Katakana: \x1b(I:]FAJ\x1b(B\n"
  "Chinese:  \x1b$A?*7\"\x1b(B\n"
  "Korean:   \x1b$(C>H3gGO<<?d\x1b(B\n"
  "French:   \x1b.ATr\x1bNhs bien\n"
  "Greek:    \x1b.F\x1bNl\x1bNe\x1bNc\x1bN\\\x1bNk\x1bNg\n" },
{ "euc-jp",
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "Katakana: \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a\n",
  "JISX0208: \xb8\xb5\xb5\xa4\n"
  "JISX0212: \xf1\xd6\x8f\xe9\xd1\n"
  "Katakana: \x8e\xba\x8e\xdd\x8e\xc6\x8e\xc1\x8e\xca\n" },
{ "shift-jis",
  "Shift-JIS (\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e) \xe3\x81\x93\xe3\x82\x93\xe3\x81\xab\xe3\x81\xa1\xe3\x81\xaf, \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a",
  "Shift-JIS (\x93\xfa\x96{\x8c\xea) \x82\xb1\x82\xf1\x82\xc9\x82\xbf\x82\xcd, \xba\xdd\xc6\xc1\xca" },
{ "BIG5",
  "BIG5: \xe5\xb8\xb8\xe7\x94\xa8\xe5\x9c\x8b\xe5\xad\x97\xe6\xa8\x99\xe6\xba\x96\xe5\xad\x97\xe9\xab\x94\xe8\xa1\xa8 + \xe6\xac\xa1\xe5\xb8\xb8\xe7\x94\xa8\xe5\x9c\x8b\xe5\xad\x97\xe6\xa8\x99\xe6\xba\x96\xe5\xad\x97\xe9\xab\x94\xe8\xa1\xa8\n"
  "ETEN: \xe7\xa2\x81\xe9\x8a\xb9\xe6\x81\x92\xe8\xa3\x8f\xe5\xa2\xbb\xe7\xb2\xa7\xe5\xab\xba",
  "BIG5: \xb1`\xa5\xce\xb0\xea\xa6r\xbc\xd0\xb7\xc7\xa6r\xc5\xe9\xaa\xed + \xa6\xb8\xb1`\xa5\xce\xb0\xea\xa6r\xbc\xd0\xb7\xc7\xa6r\xc5\xe9\xaa\xed\n"
  "ETEN: \xf9\xd6\xf9\xd7\xf9\xda\xf9\xd8\xf9\xd9\xf9\xdb\xf9\xdc" },
{ 0, 0, 0 }
};

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMCharacterSet");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  { // test the listed encodings
  for (int i = 0; ClunieText[i][0] != 0; i++)
  {
    std::string name = ClunieText[i][0];
    std::string utf = ClunieText[i][1];
    std::string raw = ClunieText[i][2];
    vtkDICOMCharacterSet cs(name);
    std::string s = cs.ToUTF8(raw);
    TestAssert(s == utf);
    std::string t = cs.FromUTF8(utf);
    if (name == "\\ISO 2022 IR 58" || name == "\\ISO 2022 IR 149")
    {
      // escape codes are placed differently, so just check round-trip
      std::string u = cs.ToUTF8(t);
      TestAssert(u == utf);
    }
    else
    {
      TestAssert(t == raw);
    }
  }

  for (int i = 0; OtherText[i][0] != 0; i++)
  {
    std::string name = OtherText[i][0];
    std::string utf = OtherText[i][1];
    std::string raw = OtherText[i][2];
    vtkDICOMCharacterSet cs(name);
    std::string s = cs.ToUTF8(raw);
    // if (s != utf) { cout << i << "\n" << s << "\n" << utf << "\n"; }
    TestAssert(s == utf);
    std::string t = cs.FromUTF8(utf);
    if (name != "iso-2022-jp-2")
    {
      TestAssert(t == raw);
    }
  }
  }

  { // test storing values in their native encoding in an item
  for (int i = 0; ClunieText[i][0] != 0; i++)
  {
    std::string name = ClunieText[i][0];
    std::string utf = ClunieText[i][1];
    std::string raw = ClunieText[i][2];
    vtkDICOMItem item;
    item.Set(DC::SpecificCharacterSet, name);
    item.Set(DC::PatientName, raw);
    std::string s = item.Get(DC::PatientName).AsUTF8String();
    // if (s != utf) { cout << i << "\n" << s << "\n" << utf << "\n"; }
    TestAssert(s == utf);
    std::string t = item.Get(DC::PatientName).GetUTF8String(0);
    // if (t != utf) { cout << i << "\n" << t << "\n" << utf << "\n"; }
    TestAssert(t == utf);
  }
  }

  { // test storing values in their native encoding in metadata
  for (int i = 0; ClunieText[i][0] != 0; i++)
  {
    std::string name = ClunieText[i][0];
    std::string utf = ClunieText[i][1];
    std::string raw = ClunieText[i][2];
    vtkSmartPointer<vtkDICOMMetaData> meta =
      vtkSmartPointer<vtkDICOMMetaData>::New();
    meta->Set(DC::SpecificCharacterSet, name);
    meta->Set(DC::PatientName, raw);
    std::string s = meta->Get(DC::PatientName).AsUTF8String();
    // if (s != utf) { cout << i << "\n" << s << "\n" << utf << "\n"; }
    TestAssert(s == utf);
    std::string t = meta->Get(DC::PatientName).GetUTF8String(0);
    // if (t != utf) { cout << i << "\n" << t << "\n" << utf << "\n"; }
    TestAssert(t == utf);
  }
  }

  { // test storing multiple values in their native encoding in metadata
  for (int i = 0; ClunieText[i][0] != 0; i++)
  {
    std::string name = ClunieText[i][0];
    std::string utf = ClunieText[i][1];
    std::string raw = ClunieText[i][2];
    vtkSmartPointer<vtkDICOMMetaData> meta =
      vtkSmartPointer<vtkDICOMMetaData>::New();
    meta->SetNumberOfInstances(2);
    meta->Set(DC::SpecificCharacterSet, name);
    meta->Set(0, DC::PatientName, "Doe^John");
    meta->Set(1, DC::PatientName, raw);
    std::string s = meta->Get(1, DC::PatientName).AsUTF8String();
    // if (s != utf) { cout << i << "\n" << s << "\n" << utf << "\n"; }
    TestAssert(s == utf);
  }
  }

  { // test "safe" conversions
  for (int i = 0; ClunieText[i][0] != 0; i++)
  {
    // ToSafeUTF8 == ToUTF8 if string is already "safe"
    std::string name = ClunieText[i][0];
    std::string raw = ClunieText[i][2];
    if (raw[raw.length()-1] == '\n') { continue; }
    vtkDICOMCharacterSet cs(name);
    TestAssert(cs.ToUTF8(raw) == cs.ToSafeUTF8(raw));
  }
  // test control codes (C0, C1, and DELETE)
  vtkDICOMCharacterSet cs(vtkDICOMCharacterSet::ISO_IR_100);
  TestAssert(cs.ToSafeUTF8("Hello\r\nWorld") == "Hello\\015\\012World");
  TestAssert(cs.ToSafeUTF8("\201Hello World") == "\\201Hello World");
  TestAssert(cs.ToSafeUTF8("Hello World\177") == "Hello World\\177");
  // test convertible characters for ISO 8859
  TestAssert(cs.ToSafeUTF8("\240 \377") == "\302\240 \303\277");
  // test unconvertible characters for ISO 8859
  cs = vtkDICOMCharacterSet::ISO_IR_109;
  TestAssert(cs.ToSafeUTF8("Hello \245World") == "Hello \\245World");
  // test unconvertible characters for other character sets
  cs = vtkDICOMCharacterSet::X_CP1253;
  TestAssert(cs.ToSafeUTF8("Hello\251 \252") == "Hello\302\251 \\252");
  }

  { // test for proper escaping of backslashes in GB18030
  std::string name = "GB18030";
  // the following string includes a multi-byte character where the
  // second byte has the same value as backslash
  std::string raw = "Wang^XiaoDong\\\xcd\xf5^\xd0\\\xb6\xab\\";
  vtkDICOMItem item;
  item.Set(DC::SpecificCharacterSet, name);
  item.Set(DC::OperatorsName, raw);
  vtkDICOMValue v = item.Get(DC::OperatorsName);
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.AsString() == raw);
  TestAssert(v.GetString(0) == "Wang^XiaoDong");
  TestAssert(v.GetString(1) == "\xcd\xf5^\xd0\\\xb6\xab");
  TestAssert(v.GetString(2) == "");
  }

  { // test for proper escaping of backslashes in iso-2022-jp
  std::string name = "ISO 2022 IR 13\\ISO 2022 IR 87";
  // the following string includes multi-byte characters where the
  // first and second bytes have the same value as backslash
  std::string raw = "\xd4\xcf\xc0\xde^\xc0\xdb\xb3\\"
                    "\x1b$B\\3ED\x1b(J^\x1b$B\\\\O\\\x1b(J\\"
                    "\x1b$B$d$^$@\x1b(J^\x1b$B$\x3f$m$&\x1b(J";
  vtkDICOMItem item;
  item.Set(DC::SpecificCharacterSet, name);
  item.Set(DC::OperatorsName, raw);
  vtkDICOMValue v = item.Get(DC::OperatorsName);
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.AsString() == raw);
  TestAssert(v.GetString(0) == "\xd4\xcf\xc0\xde^\xc0\xdb\xb3");
  TestAssert(v.GetString(1) == "\x1b$B\\3ED\x1b(J^\x1b$B\\\\O\\\x1b(J");
  TestAssert(v.GetString(2) == "\x1b$B$d$^$@\x1b(J^\x1b$B$\x3f$m$&\x1b(J");
  }

  { // test for handling of utf-16 surrogates encoded in utf-8
  vtkDICOMCharacterSet cs = vtkDICOMCharacterSet::ISO_IR_192;
  // the following string has a matched surrogate pair
  std::string raw = "\xed\xa1\x80\xed\xb3\x8c"; // D840 DCCC
  // case folding causes decoding + encoding
  std::string cooked = cs.CaseFoldedUTF8(raw.data(), raw.length());
  TestAssert(cooked == "\xf0\xa0\x83\x8c"); // 0200CC
  }

  { // test that all hangul will round-trip through EUC-KR, even the ones
    // that have to be encoded as 8-bytes.
  std::string hangul;
  for (unsigned int code = 0xAC00; code <= 0xD7A3; code++)
  {
    // create a long utf-8 string with all the hangul
    hangul.push_back(0xE0 | (code >> 12));
    hangul.push_back(0x80 | ((code >> 6) & 0x3F));
    hangul.push_back(0x80 | (code & 0x3F));
  }
  vtkDICOMCharacterSet cs = vtkDICOMCharacterSet::ISO_2022_IR_149;
  std::string t = cs.FromUTF8(hangul);
  std::string u = cs.ToUTF8(t);
  TestAssert(u == hangul);
  }

  { // test round-trip of JIS X 0201 through JIS X 0208
  std::string jisx0201;
  for (unsigned char c = 0x20; c < 0x7f; c++)
  {
    jisx0201.push_back(static_cast<char>(c));
  }
  for (unsigned char c = 0xa1; c <= 0xdf; c++)
  {
    jisx0201.push_back(static_cast<char>(c));
  }
  vtkDICOMCharacterSet cs1 = vtkDICOMCharacterSet::ISO_IR_13;
  vtkDICOMCharacterSet cs2 = vtkDICOMCharacterSet::ISO_2022_IR_87;
  std::string u = cs1.ToUTF8(jisx0201);
  std::string u2 = cs2.ToUTF8(cs2.FromUTF8(u));
  std::string t = cs1.FromUTF8(u2);
  TestAssert(t == jisx0201);
  }

  { // test compatibility mappings of jouyou kanji not in jis 0208
  std::string official =
    "\xf0\xa0\xae\x9f \xe5\xa1\xa1 \xe5\x89\x9d \xe9\xa0\xb0";
  std::string compat =
    "\xe5\x8f\xb1 \xe5\xa1\xab \xe5\x89\xa5 \xe9\xa0\xac";
  vtkDICOMCharacterSet cs = vtkDICOMCharacterSet::ISO_2022_IR_87;
  std::string t = cs.FromUTF8(official);
  std::string s = cs.FromUTF8(compat);
  TestAssert(t == s);
  // round trip expected to fail due to compatibility mapping
  std::string u = cs.ToUTF8(t);
  TestAssert(u == compat);
  }

  { // test round trip of single-byte character sets within valid ranges
  const char *sets[] = {
    "ISO_IR 13",  "\x01\x7f,\xa0\xdf,",
    "ISO_IR 100", "\x01\x7f,\xa0\xff,",
    "ISO_IR 101", "\x01\x7f,\xa0\xff,",
    "ISO_IR 109", "\x01\x7f,\xa0\xa4,\xa6\xad,\xaf\xbd,\xbf\xc2,\xc4\xcf,"
                  "\xd1\xe2,\xe4\xef,\xf1\xff,",
    "ISO_IR 110", "\x01\x7f,\xa0\xff,",
    "ISO_IR 144", "\x01\x7f,\xa0\xff,",
    "ISO_IR 127", "\x01\x7f,\xa0\xa0,\xa4\xa4,\xac\xad,\xbb\xbb,\xbf\xbf,"
                  "\xc1\xda,\xe0\xf2,",
    "ISO_IR 126", "\x01\x7f,\xa0\xad,\xaf\xd1,\xd3\xfe,",
    "ISO_IR 138", "\x01\x7f,\xa0\xa0,\xa2\xbe,\xdf\xfa,\xfd\xfe,",
    "ISO_IR 148", "\x01\x7f,\xa0\xff,",
    "LATIN6",     "\x01\x7f,\xa0\xff,",
    "ISO_IR 166", "\x01\x7f,\xa0\xda,\xdf\xfb,",
    "LATIN7",     "\x01\x7f,\xa0\xff,",
    "LATIN8",     "\x01\x7f,\xa0\xff,",
    "LATIN9",     "\x01\x7f,\xa0\xff,",
    "LATIN10",    "\x01\x7f,\xa0\xff,",
    "Windows-874","\x01\xda,\xdf\xfb,",
    "CP1250",     "\x01\xff,",
    "CP1251",     "\x01\xff,",
    "CP1252",     "\x01\xff,",
    "CP1253",     "\x01\xa9,\xab\xd1,\xd3\xfe,",
    "CP1254",     "\x01\xff,",
    "CP1255",     "\x01\xd8,\xe0\xfa,\xfd\xfe,",
    "CP1256",     "\x01\xff,",
    "CP1257",     "\x01\xa0,\xa2\xa4,\xa6\xff,",
    "KOI8",       "\x01\x7f,\x9a\x9a,\x9e\x9e,\xa3\xa4,\xa6\xa7,\xad\xae,"
                  "\xb3\xb4,\xb6\xb7,\xbd\xbe,\xbf\xff,",
    NULL, NULL
  };
  for (int i = 0; sets[i]; i += 2)
  {
    std::string codes;
    for (const char *r = sets[i+1]; *r; r += 3)
    {
      const unsigned char *range = reinterpret_cast<const unsigned char *>(r);
      for (int c = range[0]; c <= range[1]; c++)
      {
        codes.push_back(static_cast<char>(c));
      }
    }
    vtkDICOMCharacterSet cs(sets[i]);
    std::string u = cs.ToUTF8(codes);
    std::string t = cs.FromUTF8(u);
    if (t != codes)
    {
      std::cerr << "Failed round-trip for " << sets[i] << "\n";
      TestAssert(t == codes);
    }
  }
  }

  return rval;
}
