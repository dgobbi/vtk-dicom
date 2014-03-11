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
    std::string s = cs.ConvertToUTF8(raw.c_str(), raw.length());
    TestAssert(s == utf);
    }
  }

  { // test storing values in their native encoding in an item
  for (int i = 0; ClunieText[i][0] != 0; i++)
    {
    std::string name = ClunieText[i][0];
    std::string utf = ClunieText[i][1];
    std::string raw = ClunieText[i][2];
    vtkDICOMItem item;
    item.SetAttributeValue(DC::SpecificCharacterSet, name);
    item.SetAttributeValue(DC::PatientName, raw);
    std::string s = item.GetAttributeValue(DC::PatientName).AsUTF8String();
    TestAssert(s == utf);
    std::string t = item.GetAttributeValue(DC::PatientName).GetUTF8String(0);
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
    meta->SetAttributeValue(DC::SpecificCharacterSet, name);
    meta->SetAttributeValue(DC::PatientName, raw);
    std::string s = meta->GetAttributeValue(DC::PatientName).AsUTF8String();
    TestAssert(s == utf);
    std::string t = meta->GetAttributeValue(DC::PatientName).GetUTF8String(0);
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
    meta->SetAttributeValue(DC::SpecificCharacterSet, name);
    meta->SetAttributeValue(0, DC::PatientName, "Doe^John");
    meta->SetAttributeValue(1, DC::PatientName, raw);
    std::string s = meta->GetAttributeValue(1, DC::PatientName).AsUTF8String();
    TestAssert(s == utf);
    }
  }

  { // test for proper escaping of backslashes in GB18030
  std::string name = "GB18030";
  // the following string includes a multi-byte character where the
  // second byte has the same value as backslash
  std::string raw = "Wang^XiaoDong\\\xcd\xf5^\xd0\\\xb6\xab\\";
  vtkDICOMItem item;
  item.SetAttributeValue(DC::SpecificCharacterSet, name);
  item.SetAttributeValue(DC::OperatorsName, raw);
  vtkDICOMValue v = item.GetAttributeValue(DC::OperatorsName);
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
  item.SetAttributeValue(DC::SpecificCharacterSet, name);
  item.SetAttributeValue(DC::OperatorsName, raw);
  vtkDICOMValue v = item.GetAttributeValue(DC::OperatorsName);
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.AsString() == raw);
  TestAssert(v.GetString(0) == "\xd4\xcf\xc0\xde^\xc0\xdb\xb3");
  TestAssert(v.GetString(1) == "\x1b$B\\3ED\x1b(J^\x1b$B\\\\O\\\x1b(J");
  TestAssert(v.GetString(2) == "\x1b$B$d$^$@\x1b(J^\x1b$B$\x3f$m$&\x1b(J");
  }

  return rval;
}
