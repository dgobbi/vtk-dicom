#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMSequence.h"
#include "vtkSmartPointer.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

namespace {
std::string little(size_t value, int bytes)
{
  std::string result;
  for (int i = 0; i < bytes; ++i)
  {
    result += static_cast<char>(value & 255);
    value >>= 8;
  }
  return result;
}

std::string element(unsigned int group, unsigned int tag, const std::string& data,
                    const char *longVR = nullptr)
{
  std::string head = little(group, 2) + little(tag, 2);
  if (longVR) { head += std::string(longVR) + little(0, 2); }
  return head + little(data.size(), 4) + data;
}

std::string attributes(bool local, const char *vr)
{
  std::string s;
  if (local) { s += element(8, 5, "ISO_IR 192", vr); }
  s += element(8, 0x1030, local ? "\xc3\xa9\xc3\xa9" : "\xe9\xe9", vr);
  if (local) { s += element(0x28, 0x0103, little(0, 2), vr); }
  s += element(0x28, 0x0106, little(0xfff5, 2), vr);
  return s;
}

bool correct(const vtkDICOMValue& text, const vtkDICOMValue& number,
             bool local, bool forceLatin1)
{
  const char *expected = (local && forceLatin1 ?
    "\xc3\x83\xc2\xa9\xc3\x83\xc2\xa9" : "\xc3\xa9\xc3\xa9");
  return text.AsUTF8String() == expected &&
    number.GetVR() == (local ? vtkDICOMVR::US : vtkDICOMVR::SS) &&
    number.AsInt() == (local ? 65525 : -11);
}
int checkFixture(bool explicitUN)
{
  const char *filename = explicitUN ? "TestDICOMQueryContextUN.dcm" : "TestDICOMQueryContext.dcm";
  std::string uid = explicitUN ? "1.2.840.10008.1.2.1" : "1.2.840.10008.1.2";
  uid.push_back('\0');
  const char *vr = explicitUN ? "UN" : nullptr;
  const std::string syntax = little(2, 2) + little(0x10, 2) + "UI" +
    little(uid.size(), 2) + uid;
  std::string bytes = std::string(128, '\0') + "DICM" + little(2, 2) +
    little(0, 2) + "UL" + little(4, 2) + little(syntax.size(), 4) + syntax;
  bytes += element(8, 5, "ISO_IR 100", vr);
  bytes += element(8, 0x1030, "\xe9\xe9", vr);
  bytes += element(0x28, 0x0103, little(1, 2), vr);
  bytes += element(0x28, 0x0106, little(0xfff5, 2), vr);
  bytes += element(0x88, 0x0200,
    element(0xfffe, 0xe000, attributes(true, vr)) +
    element(0xfffe, 0xe000, attributes(false, vr)), explicitUN ? "SQ" : nullptr);
  {
    std::ofstream file(filename, std::ios::binary);
    file.write(bytes.data(), bytes.size());
    if (!file) { return 2; }
  }

  vtkDICOMItem wanted;
  wanted.Set(DC::StudyDescription, vtkDICOMValue(vtkDICOMVR::LO));
  wanted.Set(DC::SmallestImagePixelValue, vtkDICOMValue(vtkDICOMVR::US));
  vtkDICOMItem query = wanted;
  vtkDICOMSequence nested;
  nested.AddItem(wanted);
  query.Set(DC::IconImageSequence, nested);

  bool fullReadsOk = true;
  bool selectiveReadsOk = true;
  for (int mode = 0; mode < 4; ++mode)
  {
    const bool selective = (mode & 1) != 0;
    const bool forceLatin1 = (mode & 2) != 0;
    vtkSmartPointer<vtkDICOMMetaData> meta = vtkSmartPointer<vtkDICOMMetaData>::New();
    vtkSmartPointer<vtkDICOMParser> parser = vtkSmartPointer<vtkDICOMParser>::New();
    parser->SetFileName(filename);
    parser->SetMetaData(meta);
    if (forceLatin1)
    {
      parser->SetDefaultCharacterSet(vtkDICOMCharacterSet::ISO_IR_100);
      parser->OverrideCharacterSetOn();
    }
    if (selective) { parser->SetQueryItem(query); }
    parser->Update();
    bool ok = parser->GetErrorCode() == 0 && (!selective || parser->GetQueryMatched());
    ok = ok && correct(meta->Get(DC::StudyDescription),
                       meta->Get(DC::SmallestImagePixelValue), false, forceLatin1);
    if (selective) {
      ok = ok && !meta->Get(DC::PixelRepresentation).IsValid() &&
        !meta->Get(DC::SpecificCharacterSet).IsValid();
    }
    vtkDICOMSequence seq = meta->Get(DC::IconImageSequence);
    ok = ok && seq.GetNumberOfItems() == 2;
    for (size_t i = 0; i < seq.GetNumberOfItems(); ++i)
    {
      const vtkDICOMItem& item = seq.GetItem(i);
      ok = ok && correct(item.Get(DC::StudyDescription),
                         item.Get(DC::SmallestImagePixelValue), i == 0, forceLatin1);
      if (selective) {
        ok = ok && !item.Get(DC::PixelRepresentation).IsValid() &&
          !item.Get(DC::SpecificCharacterSet).IsValid();
      }
    }
    if (!ok)
    {
      std::cerr << (selective ? "Selective" : "Full")
                << (explicitUN ? " explicit UN" : " implicit VR")
                << " read failed with forced Latin-1 " << (forceLatin1 ? "on" : "off") << "\n";
      if (selective) { selectiveReadsOk = false; }
      else { fullReadsOk = false; }
    }
  }
  // A requested interpretation tag with a mismatching value must still reject the file.
  vtkSmartPointer<vtkDICOMMetaData> meta = vtkSmartPointer<vtkDICOMMetaData>::New();
  vtkSmartPointer<vtkDICOMParser> parser = vtkSmartPointer<vtkDICOMParser>::New();
  vtkDICOMItem mismatch;
  mismatch.Set(DC::PixelRepresentation, vtkDICOMValue(vtkDICOMVR::US, 0.0));
  parser->SetFileName(filename);
  parser->SetMetaData(meta);
  parser->SetQueryItem(mismatch);
  parser->Update();
  const bool rejectedMismatch = parser->GetErrorCode() == 0 && !parser->GetQueryMatched();
  std::remove(filename);
  if (!fullReadsOk || !rejectedMismatch)
  {
    std::cerr << "Full-read or query-mismatch control failed\n";
    return 2;
  }
  if (!selectiveReadsOk)
  {
    std::cerr << "Incorrect signed-value or text context in query\n";
    return 1;
  }
  return 0;
}
}

int TestDICOMQueryContext(int, char *[])
{
  const int implicitResult = checkFixture(false);
  const int explicitResult = checkFixture(true);
  return implicitResult > explicitResult ? implicitResult : explicitResult;
}

#ifdef VTK_DICOM_SEPARATE_TESTS
int main(int argc, char *argv[])
{
  return TestDICOMQueryContext(argc, argv);
}
#endif
