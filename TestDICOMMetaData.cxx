#include "vtkDICOMMetaData.h"
#include <vtkSmartPointer.h>

#include <gdcmReader.h>
#include <gdcmDataSet.h>
#include <gdcmFile.h>
#include <gdcmTag.h>
#include <gdcmVL.h>
#include <gdcmVR.h>

#include <bitset>
#include <limits>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
  const char * inputImageFileName =
    "/Volumes/Work/CAIN/Data/SFMRC/Fast_SPGR_2/IM-0007-0006.dcm";

  gdcm::Reader tagreader;
  tagreader.SetFileName(inputImageFileName);

  if (!tagreader.Read())
    {
    std::cerr << "Could not read file." << std::endl;
    }

  gdcm::File &file = tagreader.GetFile();
  gdcm::DataSet &ds = file.GetDataSet();

  std::stringstream strm;

  vtkSmartPointer<vtkDICOMMetaData> metaData =
    vtkSmartPointer<vtkDICOMMetaData>::New();

  gdcm::DataSet::ConstIterator it;
  for (it = ds.Begin(); it != ds.End(); ++it)
    {
    const gdcm::DataElement &de = *it;
    if (!de.IsEmpty())
      {
      gdcm::Tag gtag = de.GetTag();
      std::stringstream strm;
      de.GetValue().Print(strm);
      vtkDICOMTag tag(gtag.GetGroup(),gtag.GetElement());
      vtkDICOMDictEntry dicte;
      if (vtkDICOMMetaData::FindDictEntry(tag, dicte))
        {
        metaData->SetAttributeValue(tag, strm.str());
        std::cerr << "adding " << tag << " \"" << dicte.GetName() << "\" "
                  << dicte.GetVR() << " " << strm.str() << "\n";
        }
      }
    }

  vtkDICOMDataElementIterator iter = metaData->GetData();
  vtkDICOMDataElementIterator iend = metaData->GetDataEnd();
  int counter = 0;
  while (iter != iend)
    {
    counter++;
    std::cerr << "getting " << *iter << "\n";
    ++iter;
    }
  std::cerr << "number of elements " << counter << " == "
            << metaData->GetNumberOfDataElements() << "\n";

  return 0;
}
