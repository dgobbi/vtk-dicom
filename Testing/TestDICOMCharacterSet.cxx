#include "vtkDICOMValue.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"

#include "vtkSmartPointer.h"

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
  // "שרון^דבורה"
  "\xd7\xa9\xd7\xa8\xd7\x95\xd7\x9f^\xd7\x93\xd7\x91\xd7\x95\xd7\xa8\xd7\x94",
  "\xf9\xf8\xe5\xef^\xe3\xe1\xe5\xf8\xe4" },

{ "ISO_IR 144",
  // "Люкceмбypг"
  "\xd0\x9b\xd1\x8e\xd0\xba\x63\x65\xd0\xbc\xd0\xb1yp\xd0\xb3",
  "\xbb\xee\xda\x63\x65\xdc\xd1yp\xd3" },

{ "ISO_IR 127",
  // "قباني^لنزار"
  "\xd9\x82\xd8\xa8\xd8\xa7\xd9\x86\xd9\x8a^\xd9\x84\xd9\x86\xd8\xb2\xd8\xa7\xd8\xb1",
  "\xe2\xc8\xc7\xe6\xea^\xe4\xe6\xd2\xc7\xd1" },

{ "ISO_IR 100",
  // "Äneas^Rüdiger"
  "\xc3\x84neas^R\xc3\xbc\x64iger",
  "\xc4neas^R\xfc\x64iger" },

{ "ISO_IR 100",
  // "Buc^Jérôme"
  "Buc^J\xc3\xa9r\xc3\xb4me",
  "Buc^J\xe9r\xf4me" },

{ "ISO_IR 126",
  // "Διονυσιος"
  "\xce\x94\xce\xb9\xce\xbf\xce\xbd\xcf\x85\xcf\x83\xce\xb9\xce\xbf\xcf\x82",
  "\xc4\xe9\xef\xed\xf5\xf3\xe9\xef\xf2" },

{ "GB18030",
  // "Wang^XiaoDong=王^小东="
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe4\xb8\x9c=",
  "Wang^XiaoDong=\xcd\xf5^\xd0\xa1\xb6\xab=" },

{ "GBK",
  // "Wang^XiaoDong=王^小东="
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe4\xb8\x9c=",
  "Wang^XiaoDong=\xcd\xf5^\xd0\xa1\xb6\xab=" },

{ "\\ISO 2022 IR 58",
  // "1. 第一行文字\r\n"
  "1. \xe7\xac\xac\xe4\xb8\x80\xe8\xa1\x8c\xe6\x96\x87\xe5\xad\x97\xe3\x80\x82\r\n",
  "1. \x1b$)A\xb5\xda\xd2\xbb\xd0\xd0\xce\xc4\xd7\xd6\xa1\xa3\x1b(B\r\n" },

{ "ISO_IR 192",
  // "Wang^XiaoDong=王^小东="
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe6\x9d\xb1=",
  "Wang^XiaoDong=\xe7\x8e\x8b^\xe5\xb0\x8f\xe6\x9d\xb1=" },

{ "\\ISO 2022 IR 149",
  // "Hong^Gildong=洪^吉洞=홍^길동"
  "Hong^Gildong=\xe6\xb4\xaa^\xe5\x90\x89\xe6\xb4\x9e=\xed\x99\x8d^\xea\xb8\xb8\xeb\x8f\x99",
  "Hong^Gildong=\x1b$)C\xfb\xf3^\x1b$)C\xd1\xce\xd4\xd7=\x1b$)C\xc8\xab^\x1b$)C\xb1\xe6\xb5\xbf" },

{ "ISO 2022 IR 13\\ISO 2022 IR 87",
  // "ﾔﾏﾀﾞ^ﾀﾛｳ=山田^太郎=やまだ^たろう"
  "\xef\xbe\x94\xef\xbe\x8f\xef\xbe\x80\xef\xbe\x9e^\xef\xbe\x80\xef\xbe\x9b\xef\xbd\xb3=\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e=\xe3\x82\x84\xe3\x81\xbe\xe3\x81\xa0^\xe3\x81\x9f\xe3\x82\x8d\xe3\x81\x86",
  "\xd4\xcf\xc0\xde^\xc0\xdb\xb3=\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J=\x1b$B$d$^$@\x1b(J^\x1b$B$\x3f$m$&\x1b(J" },

{ "\\ISO 2022 IR 87",
  // "Yamada^Tarou=山田^太郎=やまだ^たろう"
  "Yamada^Tarou=\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e=\xe3\x82\x84\xe3\x81\xbe\xe3\x81\xa0^\xe3\x81\x9f\xe3\x82\x8d\xe3\x81\x86",
  "Yamada^Tarou=\x1b$B;3ED\x1b(B^\x1b$BB@O:\x1b(B=\x1b$B$d$^$@\x1b(B^\x1b$B$\x3f$m$&\x1b(B" },

{ 0, 0, 0 }
};

// order is character set, utf-8, native encoding
static const char *OtherText[][3] = {
{ "GB18030",
  // "Linear1: \x80 to \ufffd\n"
  // "Linear2: \U00010000 to \U0010ffff\n"
  // "Ver2005: ḿ\n"
  // "Ver2022: ︐︒︑︓︔︕︖︗︘︙\n"
  // "Ver2022: 龴龵龶龷龸龹龺龻\n"
  "Linear1: \xc2\x80 to \xef\xbf\xbd\n"
  "Linear2: \xf0\x90\x80\x80 to \xf4\x8f\xbf\xbf\n"
  "Ver2005: \xe1\xb8\xbf\n"
  "Ver2022: \xef\xb8\x90\xef\xb8\x92\xef\xb8\x91\xef\xb8\x93\xef\xb8\x94\xef\xb8\x95\xef\xb8\x96\xef\xb8\x97\xef\xb8\x98\xef\xb8\x99\n"
  "Ver2022: \xe9\xbe\xb4\xe9\xbe\xb5\xe9\xbe\xb6\xe9\xbe\xb7\xe9\xbe\xb8\xe9\xbe\xb9\xe9\xbe\xba\xe9\xbe\xbb\n",
  "Linear1: \x81\x30\x81\x30 to \x84\x31\xa4\x37\n"
  "Linear2: \x90\x30\x81\x30 to \xe3\x32\x9a\x35\n"
  "Ver2005: \xa8\xbc\n"
  "Ver2022: \xa6\xd9\xa6\xda\xa6\xdb\xa6\xdc\xa6\xdd\xa6\xde\xa6\xdf\xa6\xec\xa6\xed\xa6\xf3\n"
  "Ver2022: \xfe\x59\xfe\x61\xfe\x66\xfe\x67\xfe\x6d\xfe\x7e\xfe\x90\xfe\xa0\n" },

{ "ISO 2022 IR 13\\ISO 2022 IR 87\\ISO 2022 IR 159",
  // "JISX0208: 元気\n"
  // "JISX0212: 騏驎\n"
  // "JISX0201: ｺﾝﾆﾁﾊ\n"
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "JISX0201: \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a\n",
  "JISX0208: \x1b$B855$\x1b(J\n"
  "JISX0212: \x1b$BqV\x1b$(DiQ\x1b(J\n"
  "JISX0201: \xba\xdd\xc6\xc1\xca\n" },

{ "iso-2022-jp",
  // "JISX0208: 元気\n"
  // "JISX0201: ¥‾\n"
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0201: \xc2\xa5\xe2\x80\xbe\n",
  "JISX0208: \x1b$B855$\x1b(B\n"
  "JISX0201: \x1b(J\x5c\x7e\x1b(B\n" },

{ "iso-2022-jp-1",
  // "JISX0208: 元気\n"
  // "JISX0212: 騏驎\n"
  // "JISX0201: ¥‾\n"
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "JISX0201: \xc2\xa5\xe2\x80\xbe\n",
  "JISX0208: \x1b$B855$\x1b(B\n"
  "JISX0212: \x1b$BqV\x1b$(DiQ\x1b(B\n"
  "JISX0201: \x1b(J\x5c\x7e\x1b(B\n" },

{ "iso-2022-jp-ext",
  // "JISX0208: 元気\n"
  // "JISX0212: 騏驎\n"
  // "JISX0201: ¥‾\n"
  // "Katakana: ｺﾝﾆﾁﾊ\n"
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "JISX0201: \xc2\xa5\xe2\x80\xbe\n"
  "Katakana: \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a\n",
  "JISX0208: \x1b$B855$\x1b(B\n"
  "JISX0212: \x1b$BqV\x1b$(DiQ\x1b(B\n"
  "JISX0201: \x1b(J\x5c\x7e\x1b(B\n"
  "Katakana: \x1b(I:]FAJ\x1b(B\n" },

{ "iso-2022-jp-2",
  // "JISX0208: 元気\n"
  // "JISX0212: 騏驎\n"
  // "Chinese:  开发\n"
  // "Korean:   안녕하세요\n"
  // "French:   Très bien\n"
  // "Greek:    μεγάλη\n"
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "Chinese:  \xe5\xbc\x80\xe5\x8f\x91\n"
  "Korean:   \xec\x95\x88\xeb\x85\x95\xed\x95\x98\xec\x84\xb8\xec\x9a\x94\n"
  "French:   Tr\xc3\xa8s bien\n"
  "Greek:    \xce\xbc\xce\xb5\xce\xb3\xce\xac\xce\xbb\xce\xb7\n",
  "JISX0208: \x1b$B855$\x1b(B\n"
  "JISX0212: \x1b$BqV\x1b$(DiQ\x1b(B\n"
  "Chinese:  \x1b$A?*7\"\x1b(B\n"
  "Korean:   \x1b$(C>H3gGO<<?d\x1b(B\n"
  "French:   \x1b.ATr\x1bNhs bien\n"
  "Greek:    \x1b.F\x1bNl\x1bNe\x1bNc\x1bN\\\x1bNk\x1bNg\n" },

{ "euc-jp",
  // "JISX0208: 元気\n"
  // "JISX0212: 騏驎\n"
  // "Katakana: ｺﾝﾆﾁﾊ\n"
  "JISX0208: \xe5\x85\x83\xe6\xb0\x97\n"
  "JISX0212: \xe9\xa8\x8f\xe9\xa9\x8e\n"
  "Katakana: \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a\n",
  "JISX0208: \xb8\xb5\xb5\xa4\n"
  "JISX0212: \xf1\xd6\x8f\xe9\xd1\n"
  "Katakana: \x8e\xba\x8e\xdd\x8e\xc6\x8e\xc1\x8e\xca\n" },

{ "shift-jis",
  // "Shift-JIS (日本語) こんにちは, ｺﾝﾆﾁﾊ"
  "Shift-JIS (\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e) \xe3\x81\x93\xe3\x82\x93\xe3\x81\xab\xe3\x81\xa1\xe3\x81\xaf, \xef\xbd\xba\xef\xbe\x9d\xef\xbe\x86\xef\xbe\x81\xef\xbe\x8a",
  "Shift-JIS (\x93\xfa\x96{\x8c\xea) \x82\xb1\x82\xf1\x82\xc9\x82\xbf\x82\xcd, \xba\xdd\xc6\xc1\xca" },

{ "BIG5",
  // "BIG5: 常用國字標準字體表 + 次常用國字標準字體表\n"
  // "ETEN: 碁銹恒裏墻粧嫺"
  "BIG5: \xe5\xb8\xb8\xe7\x94\xa8\xe5\x9c\x8b\xe5\xad\x97\xe6\xa8\x99\xe6\xba\x96\xe5\xad\x97\xe9\xab\x94\xe8\xa1\xa8 + \xe6\xac\xa1\xe5\xb8\xb8\xe7\x94\xa8\xe5\x9c\x8b\xe5\xad\x97\xe6\xa8\x99\xe6\xba\x96\xe5\xad\x97\xe9\xab\x94\xe8\xa1\xa8\n"
  "ETEN: \xe7\xa2\x81\xe9\x8a\xb9\xe6\x81\x92\xe8\xa3\x8f\xe5\xa2\xbb\xe7\xb2\xa7\xe5\xab\xba",
  "BIG5: \xb1`\xa5\xce\xb0\xea\xa6r\xbc\xd0\xb7\xc7\xa6r\xc5\xe9\xaa\xed + \xa6\xb8\xb1`\xa5\xce\xb0\xea\xa6r\xbc\xd0\xb7\xc7\xa6r\xc5\xe9\xaa\xed\n"
  "ETEN: \xf9\xd6\xf9\xd7\xf9\xda\xf9\xd8\xf9\xd9\xf9\xdb\xf9\xdc" },

{ 0, 0, 0 }
};

int TestDICOMCharacterSet(int argc, char *argv[])
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
    if (s != utf) { std::cerr << name << std::endl; }
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
    if (name == "iso-2022-jp-2")
    {
      // check japanese, korean (other esc codes don't round-trip)
      TestAssert(t.compare(0, 46, raw, 0, 46) == 0);
      TestAssert(t.compare(67, 28, raw, 67, 28) == 0);
    }
    else
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
  // test convertible characters "\xa0" and "\xff" for ISO-8859-1
  TestAssert(cs.ToSafeUTF8("\240 \377") == "\302\240 \303\277");
  // test unconvertible characters for ISO-8859-3
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
  // "ﾔﾏﾀﾞ^ﾀﾛｳ"
  // "目本^樛楹"
  // "ぼ^ボ"
  std::string raw = "\xd4\xcf\xc0\xde^\xc0\xdb\xb3\\"
                    "\x1b$BL\\K\\\x1b(J^\x1b$B\\\\\\3\x1b(J\\"
                    "\x1b$B$\\\x1b(J^\x1b$B%\\\x1b(J";
  vtkDICOMItem item;
  item.Set(DC::SpecificCharacterSet, name);
  item.Set(DC::OperatorsName, raw);
  vtkDICOMValue v = item.Get(DC::OperatorsName);
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.AsString() == raw);
  TestAssert(v.GetString(0) == "\xd4\xcf\xc0\xde^\xc0\xdb\xb3");
  TestAssert(v.GetString(1) == "\x1b$BL\\K\\\x1b(J^\x1b$B\\\\\\3\x1b(J");
  TestAssert(v.GetString(2) == "\x1b$B$\\\x1b(J^\x1b$B%\\\x1b(J");
  }

  { // test for proper escaping of backslashes in iso-2022-jp-2
  // the following string includes accented latin and greek characters
  // that when invoked in G0 have the same value as backslash
  // "GÜNTER"
  // "άέήί"
  std::string raw = "G\x1b.A\x1bN\\NTER\\"
                    "\x1b.F\x1bN\\\x1bN]\x1bN^\x1bN_";
  vtkDICOMItem item(vtkDICOMCharacterSet::X_ISO_2022_JP_2, vtkDICOMVR::SS);
  item.Set(DC::OperatorsName, raw);
  vtkDICOMValue v = item.Get(DC::OperatorsName);
  TestAssert(v.GetNumberOfValues() == 2);
  TestAssert(v.AsString() == raw);
  TestAssert(v.GetString(0) == "G\x1b.A\x1bN\\NTER");
  TestAssert(v.GetString(1) == "\x1b.F\x1bN\\\x1bN]\x1bN^\x1bN_");
  }

  // { // test for utf-8 in generic ISO-2022 decoder
  // std::string name = "ISO 2022 IR 6";
  // "Très bien, Jérôme"
  // std::string raw = "\x1b%/ITr\xc3\xa8s bien, J\xc3\xa9r\xc3\xb4me";
  // std::string utf = "Tr\xc3\xa8s bien, J\xc3\xa9r\xc3\xb4me";
  // vtkDICOMCharacterSet cs(name);
  // std::string s = cs.ToUTF8(raw);
  // TestAssert(s == utf);
  // }

  { // test for handling of utf-16 surrogates encoded in utf-8
  vtkDICOMCharacterSet cs = vtkDICOMCharacterSet::ISO_IR_192;
  // the following string has a matched surrogate pair
  std::string raw = "\xed\xa1\x80\xed\xb3\x8c"; // D840 DCCC
  // perform a UTF-8 to UTF-8 conversion
  std::string cooked = cs.ToUTF8(raw.data(), raw.length());
  TestAssert(cooked == "\xf0\xa0\x83\x8c"); // 0200CC
  // test low surrogate on its own
  raw = "\xed\xb3\x8c "; // DCCC
  cooked = cs.ToUTF8(raw.data(), raw.length());
  TestAssert(cooked == "\xef\xbf\xbd "); // REPLACEMENT CHARACTER
  // test high surrogate on its own
  raw = "\xed\xa1\x80 "; // D840
  cooked = cs.ToUTF8(raw.data(), raw.length());
  TestAssert(cooked == "\xef\xbf\xbd "); // REPLACEMENT CHARACTER
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
    // "𠮟 塡 剝 頰" are mapped to "叱 填 剥 頬" for jis 0208
  std::string official =
    "\xf0\xa0\xae\x9f \xe5\xa1\xa1 \xe5\x89\x9d \xe9\xa0\xb0";
  std::string compat =
    "\xe5\x8f\xb1 \xe5\xa1\xab \xe5\x89\xa5 \xe9\xa0\xac";
  vtkDICOMCharacterSet cs = vtkDICOMCharacterSet::ISO_2022_IR_87;
  std::string t = cs.FromUTF8(official);
  std::string s = cs.FromUTF8(compat);
  TestAssert(t == s);
  // round trip of "compat" will succeed, but not of "official"
  std::string u = cs.ToUTF8(t);
  TestAssert(u == compat);
  }

  { // test cp1258 encoding and decoding to NFC
  std::string raw = "Mu\xf4\xf2n nh\xe2\xect l\xe0 t\xfd\xcc n\xe3m 1867 "
    "\xf0\x61\xde c\xf3 ng\xfd\xf5\xcci go\xf2i ch\xfd\xde Latinh cho ti"
    "\xea\xecng Vi\xea\xf2t l\xe0 ch\xfd\xde qu\xf4\xec\x63 ng\xfd\xde.\n";
  std::string nfc = "Mu\xe1\xbb\x99n nh\xe1\xba\xa5t l\xc3\xa0 t\xe1\xbb\xab "
    "n\xc4\x83m 1867 \xc4\x91\xc3\xa3 c\xc3\xb3 ng\xc6\xb0\xe1\xbb\x9di g\xe1"
    "\xbb\x8di ch\xe1\xbb\xaf Latinh cho ti\xe1\xba\xbfng Vi\xe1\xbb\x87t "
    "l\xc3\xa0 ch\xe1\xbb\xaf qu\xe1\xbb\x91\x63 ng\xe1\xbb\xaf.\n";
  vtkDICOMCharacterSet cs = vtkDICOMCharacterSet::X_CP1258;
  std::string t = cs.FromUTF8(nfc);
  TestAssert(t == raw);
  std::string s = cs.ToUTF8(raw);
  TestAssert(s == nfc);
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
    "ISO_IR 203", "\x01\x7f,\xa0\xff,",
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
    "CP1258",     "\x01\xff,",
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

  { // test round trip of ISO 2022 japanese
  const char *sets[] = {
    "\\ISO 2022 IR 87",
    "ISO 2022 IR 13\\ISO 2022 IR 87",
    "\\ISO 2022 IR 87\\ISO 2022 IR 159",
    "ISO 2022 IR 13\\ISO 2022 IR 87\\ISO 2022 IR 159",
    NULL
  };
  const unsigned char keyJISX0201 = vtkDICOMCharacterSet::ISO_2022_IR_13;
  const unsigned char keys[2] = {
    vtkDICOMCharacterSet::ISO_2022_IR_87,
    vtkDICOMCharacterSet::ISO_2022_IR_159,
  };
  const char *escCodes[2] = {
    "\x1b$B",
    "\x1b$(D"
  };
  const char *ranges[2] = {
    "2121-222E,223A-2241,224A-2250,225C-226A,2272-2279,227E-227E,"
    "2330-2339,2341-235A,2361-237A,2421-2473,2521-2576,2621-2638,"
    "2641-2658,2721-2741,2751-2771,2821-2840,3021-4F53,5021-7426,",

    "222F-2239,2242-2244,226B-2271,2661-2665,2667-2667,2669-266A,"
    "266C-266C,2671-267C,2742-274E,2772-277E,2921-2922,2924-2924,"
    "2926-2926,2928-2929,292B-292D,292F-2930,2941-2950,2A21-2A38,"
    "2A3A-2A77,2B21-2B3B,2B3D-2B43,2B45-2B77,3021-6D63,"
  };

  for (int i = 0; sets[i]; i++)
  {
    vtkDICOMCharacterSet cs(sets[i]);

    bool hasJISX0201 = ((cs.GetKey() & keyJISX0201) == keyJISX0201);
    const char *escBase = (hasJISX0201 ? "\x1b(J" : "\x1b(B");
    std::string bytes;

    for (unsigned int c = 0x01; c <= 0x7F; c++)
    {
      if (c != 0x1B && c != 0x0E && c != 0x0F) // skip ESC SO SI
      {
        bytes.push_back(static_cast<char>(c));
      }
    }

    // The half-width katakana are supported by DICOM, even though
    // they aren't in iso-2022-jp or iso-2022-jp-2
    if (hasJISX0201)
    {
      for (unsigned int c = 0xA1; c <= 0xDF; c++)
      {
        bytes.push_back(static_cast<char>(c));
      }
    }

    for (int k = 0; k < 2; k++)
    {
      unsigned char key = keys[k];
      if ((cs.GetKey() & key) != key)
      {
        continue;
      }
      bytes.append(escCodes[k]);

      const char *r = ranges[k];
      while (*r != '\0')
      {
        unsigned int range[2];
        const char *rnext = r;
        while (isalnum(*rnext)) { ++rnext; }
        range[0] = static_cast<unsigned int>(strtoul(r, NULL, 16));
        TestAssert(*rnext == '-');
        r = ++rnext;
        while (isalnum(*rnext)) { ++rnext; }
        range[1] = static_cast<unsigned int>(strtoul(r, NULL, 16));
        TestAssert(*rnext == ',');
        r = ++rnext;

        for (unsigned int c = range[0]; c <= range[1]; c++)
        {
          unsigned int a = (c >> 8);
          unsigned int b = (c & 0xFF);
          if (a > 0x20 && a < 0x7F)
          {
            if (b > 0x20 && b < 0x7F)
            {
              bytes.push_back(static_cast<char>(a));
              bytes.push_back(static_cast<char>(b));
            }
          }
        }
      }
    }

    bytes.append(escBase);
    std::string u = cs.ToUTF8(bytes);
    std::string t = cs.FromUTF8(u);
    if (t != bytes)
    {
      std::cerr << "Failed round-trip for \"" << sets[i] << "\"\n";
      TestAssert(t == bytes);
    }
  }
  }

  { // test round trip of ISO 2022 korean and chinese
  const char *sets[] = {
    "\\ISO 2022 IR 149",
    "\x1b$)C",
    "A1A1-A2E7,A3A1-A4D3,A4D5-A5AA,A5B0-A5B9,A5C1-A5D8,A5E1-A5F8,"
    "A6A1-A6E4,A7A1-A7EF,A8A1-A8A4,A8A6-A8A6,A8A8-A8AF,A8B1-AAF3,"
    "ABA1-ABF6,ACA1-ACC1,ACD1-ACF1,B0A1-C8EF,CAA1-FDEF,",

    "\\ISO 2022 IR 58",
    "\x1b$)A",
    "A1A1-A1FE,A2B1-A2E2,A2E5-A2EE,A2F1-A2FC,A3A1-A4F3,A5A1-A5F6,"
    "A6A1-A6B8,A6C1-A6D8,A7A1-A7C1,A7D1-A7F1,A8A1-A8BA,A8C5-A8E9,"
    "A9A4-A9EF,B0A1-D7F9,D8A1-F7FE,",

    NULL, NULL, NULL
  };

  for (int i = 0; sets[i]; i += 3)
  {
    const char *charset = sets[i];
    const char *escCode = sets[i+1];
    const char *ranges = sets[i+2];

    vtkDICOMCharacterSet cs(charset);
    std::string bytes;

    for (unsigned int c = 0x01; c <= 0x7F; c++)
    {
      if (c != 0x1B && c != 0x0E && c != 0x0F) // skip ESC SO SI
      {
        bytes.push_back(static_cast<char>(c));
      }
    }

    bytes.append("\r\n");
    bytes.append(escCode);

    const char *r = ranges;
    while (*r != '\0')
    {
      unsigned int range[2];
      const char *rnext = r;
      while (isalnum(*rnext)) { ++rnext; }
      range[0] = static_cast<unsigned int>(strtoul(r, NULL, 16));
      TestAssert(*rnext == '-');
      r = ++rnext;
      while (isalnum(*rnext)) { ++rnext; }
      range[1] = static_cast<unsigned int>(strtoul(r, NULL, 16));
      TestAssert(*rnext == ',');
      r = ++rnext;

      for (unsigned int c = range[0]; c <= range[1]; c++)
      {
        unsigned int a = (c >> 8);
        unsigned int b = (c & 0xFF);
        if (a > 0xA0 && a < 0xFF)
        {
          if (b > 0xA0 && b < 0xFF)
          {
            bytes.push_back(static_cast<char>(a));
            bytes.push_back(static_cast<char>(b));
          }
        }
      }
    }
    std::string u = cs.ToUTF8(bytes);
    std::string t = cs.FromUTF8(u);
    if (t != bytes)
    {
      std::cerr << "Failed round-trip for \"" << sets[i] << "\"\n";
      TestAssert(t == bytes);
    }
  }
  }

  { // test round trip of GBK and GB18030
  const char *sets[] = {
    "GBK",
    "8140-A2AA,A2B1-A2E2,A2E5-A2EE,A2F1-A2FC,A340-A4F3,A540-A5F6,"
    "A640-A6B8,A6C1-A6D8,A6E0-A6EB,A6EE-A6F2,A6F4-A6F5,A740-A7C1,"
    "A7D1-A7F1,A840-A895,A8A1-A8C0,A8C5-A8E9,A940-A957,A959-A95A,"
    "A95C-A95C,A960-A996,A9A4-A9EF,AA40-D7F9,D840-FEFE,",

    "GB18030",
    "8140-FEFE,81308130-8139FE39,82308130-8239FE39,83308130-8339FE39,"
    "84308130-8431A439," // U+FFFF end of BMP
    "90308130-9039FE39,E3308130-E3329A35,", // U+10FFFF

    NULL, NULL
  };

  for (int i = 0; sets[i]; i += 2)
  {
    const char *charset = sets[i];
    const char *ranges = sets[i+1];

    vtkDICOMCharacterSet cs(charset);
    std::string bytes;

    for (unsigned int c = 0x01; c <= 0x7F; c++)
    {
      bytes.push_back(static_cast<char>(c));
    }

    const char *r = ranges;
    while (*r != '\0')
    {
      unsigned int range[2];
      const char *rnext = r;
      while (isalnum(*rnext)) { ++rnext; }
      range[0] = static_cast<unsigned int>(strtoul(r, NULL, 16));
      TestAssert(*rnext == '-');
      r = ++rnext;
      while (isalnum(*rnext)) { ++rnext; }
      range[1] = static_cast<unsigned int>(strtoul(r, NULL, 16));
      TestAssert(*rnext == ',');
      r = ++rnext;

      for (unsigned int c = range[0]; c <= range[1]; c++)
      {
        if (c > 0xFFFF)
        {
          unsigned int a = (c >> 24);
          unsigned int x = (c >> 16) & 0xFF;
          unsigned int b = (c >> 8) & 0xFF;
          unsigned int y = c & 0xFF;
          if (a > 0x80 && a < 0xFF && b > 0x80 && b < 0xFF)
          {
            if (x >= 0x30 && x <= 0x39 && y >= 0x30 && y <= 0x39)
            {
              bytes.push_back(static_cast<char>(a));
              bytes.push_back(static_cast<char>(x));
              bytes.push_back(static_cast<char>(b));
              bytes.push_back(static_cast<char>(y));
            }
          }
        }
        else
        {
          unsigned int a = (c >> 8);
          unsigned int b = c & 0xFF;
          if (a > 0x80 && a < 0xFF)
          {
            if (b >= 0x40 && b < 0xFF && b != 0x7F)
            {
              bytes.push_back(static_cast<char>(a));
              bytes.push_back(static_cast<char>(b));
            }
          }
        }
      }
    }
    std::string u = cs.ToUTF8(bytes);
    std::string t = cs.FromUTF8(u);
    if (t != bytes)
    {
      std::cerr << "Failed round-trip for \"" << sets[i] << "\"\n";
      TestAssert(t == bytes);
    }
  }
  }

  return rval;
}

#ifdef VTK_DICOM_SEPARATE_TESTS
int main(int argc, char *argv[])
{
  return TestDICOMCharacterSet(argc, argv);
}
#endif
