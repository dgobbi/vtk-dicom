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
  
  const char * inputImageFileName = "/Users/lucy_l/LUCYWORK/Develop/Data/SFMRC/Fast_SPGR_2/IM-0007-0006.dcm";
  
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
  
  vtkDICOMMetaData::Tag tagMeta(dataGroup,dataElement);
  
  vtkDICOMMetaData *metaData = vtkDICOMMetaData::New();  
  
  vtkDICOMMetaData::DictElement *de = metaData->FindDictElement(tagMeta);
  unsigned short r = de->vr;
  cerr << static_cast<char>(de->vr) << static_cast<char>(de->vr >> 8) << endl;
  
  metaData->InsertElement(tagMeta,r,l,data);
  
  vtkDICOMMetaData::Element *metaElement;
  metaElement = metaData->FindElement(tagMeta);
  
  cerr << "VR : " << static_cast<char>(metaElement->vr) << static_cast<char>(metaElement->vr >> 8) << "\n"
       << "VL : " << metaElement->vl << "\n"
       << "Data : " << metaElement->data << endl;
  
  return 0;
}
