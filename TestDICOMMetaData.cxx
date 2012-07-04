#include "vtkDICOMMetaData.h"

#include <gdcmReader.h>
#include <gdcmDataSet.h>
#include <gdcmFile.h>
#include <gdcmTag.h>
#include <gdcmVL.h>
#include <gdcmVR.h>

#include <bitset>
#include <limits>
#include <iostream>

int main(int argc, char *argv[])
{ /*int dataGroup = 20000;
   int dataElement = 10000;
   unsigned short r = 10;
   unsigned int l = 5;
   const char *data = "hello there";*/
  
  const char * inputImageFileName = "/Volumes/Work/CAIN/Data/SFMRC/Fast_SPGR_2/IM-0007-0006.dcm";
  
  gdcm::Reader tagreader;
  tagreader.SetFileName(inputImageFileName);
  cerr << "Can Read ? " << tagreader.CanRead() << endl;
  
  if( !tagreader.Read() )
  {
    std::cerr << "Could not read: " << std::endl;
  }
  
  int dataGroup, dataElement;
  
  gdcm::File &file = tagreader.GetFile();    
  gdcm::DataSet &ds = file.GetDataSet();
  
  std::stringstream strm;
  
  gdcm::Tag tag =  ds.GetDataElement(gdcm::Tag(0x0010,0x1010)).GetTag();
  gdcm::VL  vl = ds.GetDataElement(gdcm::Tag(0x0010,0x1010)).GetVL();
  const gdcm::VR vr = ds.GetDataElement(gdcm::Tag(0x0010,0x1010)).GetVR();
  ds.GetDataElement(gdcm::Tag(0x0010,0x1010)).GetValue().Print(strm);
  
  dataGroup = static_cast<int> (tag.GetGroup());
  dataElement = static_cast<int> (tag.GetElement());
  
  unsigned int l = static_cast<unsigned int> (vl);
  
  cerr << "Do I get the number? " << dataGroup << " " << dataElement << " " << l << endl;
  
  const char *data =  strm.str().c_str(); 
  cerr << "Data : " << data << endl;
  
  vtkDICOMTag tagMeta(dataGroup,dataElement);
  
  vtkDICOMMetaData *metaData = vtkDICOMMetaData::New();  
  
  vtkDICOMDictEntry de;
  if (metaData->FindDictEntry(tagMeta, de))
    {
    cerr << de.GetVR() << endl;
    }
  
  metaData->SetAttributeValue(tagMeta,data);
  
  vtkDICOMValue metaValue;
  metaData->GetAttributeValue(0, tagMeta, metaValue);
  
  cerr << "VR : " << metaValue.GetVR() << "\n"
       << "VL : " << metaValue.GetVL() << "\n"
       << "Data : " << metaValue.GetTextData() << endl;
  
  return 0;
}
