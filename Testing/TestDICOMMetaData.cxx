#include "vtkDICOMMetaData.h"
#include "vtkDICOMValue.h"
#include "vtkDICOMDictionary.h"

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

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = argv[0];

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  vtkDICOMMetaData *metaData = vtkDICOMMetaData::New();

  // simple test of adding and removing attributes
  metaData->SetAttributeValue(DC::Modality, "CT");
  std::string modality = metaData->GetAttributeValue(DC::Modality).AsString();
  TestAssert(modality == "CT");
  TestAssert(metaData->HasAttribute(DC::Modality));
  TestAssert(!metaData->HasAttribute(DC::AcquisitionDateTime));
  TestAssert(!metaData->GetAttributeValue(DC::AcquisitionDateTime).IsValid());
  metaData->SetAttributeValue(DC::Modality, "MR");
  modality = metaData->GetAttributeValue(DC::Modality).AsString();
  TestAssert(modality == "MR");
  metaData->RemoveAttribute(DC::Modality);
  TestAssert(!metaData->HasAttribute(DC::Modality));
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  metaData->RemoveAttribute(DC::Modality);
  metaData->Clear();
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  metaData->SetAttributeValue(DC::Modality, "NM");
  modality = metaData->GetAttributeValue(DC::Modality).AsString();
  TestAssert(modality == "NM");
  TestAssert(metaData->GetNumberOfDataElements() == 1);
  metaData->Clear();
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  
  // test of multiple instances in a single meta data object
  metaData->SetNumberOfInstances(3);
  metaData->SetAttributeValue(DC::Modality, "CT");
  TestAssert(metaData->HasAttribute(DC::Modality));
  modality = metaData->GetAttributeValue(DC::Modality).AsString();
  TestAssert(modality == "CT");
  modality = metaData->GetAttributeValue(0, DC::Modality).AsString();
  TestAssert(modality == "CT");
  modality = metaData->GetAttributeValue(1, DC::Modality).AsString();
  TestAssert(modality == "CT");
  modality = metaData->GetAttributeValue(2, DC::Modality).AsString();
  TestAssert(modality == "CT");
  metaData->SetAttributeValue(1, DC::Modality, "MR");
  modality = metaData->GetAttributeValue(DC::Modality).AsString();
  TestAssert(modality == "CT");
  modality = metaData->GetAttributeValue(0, DC::Modality).AsString();
  TestAssert(modality == "CT");
  modality = metaData->GetAttributeValue(1, DC::Modality).AsString();
  TestAssert(modality == "MR");
  modality = metaData->GetAttributeValue(2, DC::Modality).AsString();
  TestAssert(modality == "CT");
  metaData->SetAttributeValue(DC::Modality, "MR");
  modality = metaData->GetAttributeValue(DC::Modality).AsString();
  TestAssert(modality == "MR");
  modality = metaData->GetAttributeValue(0, DC::Modality).AsString();
  TestAssert(modality == "MR");
  modality = metaData->GetAttributeValue(1, DC::Modality).AsString();
  TestAssert(modality == "MR");
  modality = metaData->GetAttributeValue(2, DC::Modality).AsString();
  TestAssert(modality == "MR");
  TestAssert(metaData->GetNumberOfDataElements() == 1);
  TestAssert(metaData->GetNumberOfInstances() == 3);
  metaData->RemoveAttribute(DC::Modality);
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  metaData->Clear();
  TestAssert(metaData->GetNumberOfInstances() == 1);

  // test iterating through the data elements
  vtkDICOMDataElementIterator iter =
    metaData->GetDataElementIterator();
  vtkDICOMDataElementIterator iterEnd =
    metaData->GetDataElementIteratorEnd();
  TestAssert(iter == iterEnd);
  metaData->SetAttributeValue(DC::Modality, "CT");
  const char *acquisitionTime = "20130126080000.000000+0700";
  metaData->SetAttributeValue(DC::AcquisitionDateTime, acquisitionTime);
  iter = metaData->GetDataElementIterator();
  iterEnd = metaData->GetDataElementIteratorEnd();
  int n = metaData->GetNumberOfDataElements();
  TestAssert(n == 2);
  for (int i = 0; i < n; i++)
    {
    if (i == 0)
      {
      TestAssert(iter->GetTag() == DC::AcquisitionDateTime);
      TestAssert(iter->GetValue().AsString() == acquisitionTime);
      TestAssert(iter->GetVR() == vtkDICOMVR::DT);
      TestAssert(iter->GetVL() == 26);
      }
    else
      {
      TestAssert(iter->GetTag() == DC::Modality);
      TestAssert(iter->GetValue().AsString() == "CT");
      TestAssert(iter->GetVR() == vtkDICOMVR::CS);
      TestAssert(iter->GetVL() == 2);
      }
    ++iter;
    }
  TestAssert(iter == iterEnd);
  metaData->Clear();

  // test iterating through the data elements with multiple instances
  metaData->SetNumberOfInstances(2);
  metaData->SetAttributeValue(0, DC::Modality, "CT");
  metaData->SetAttributeValue(1, DC::Modality, "MR");
  metaData->SetAttributeValue(DC::AcquisitionDateTime, acquisitionTime);
  iter = metaData->GetDataElementIterator();
  iterEnd = metaData->GetDataElementIteratorEnd();
  n = metaData->GetNumberOfDataElements();
  TestAssert(n == 2);
  for (int i = 0; i < n; i++)
    {
    if (i == 0)
      {
      TestAssert(iter->GetTag() == DC::AcquisitionDateTime);
      TestAssert(iter->GetValue().AsString() == acquisitionTime);
      }
    else
      {
      // two values multiplexed together in one value
      TestAssert(iter->GetTag() == DC::Modality);
      vtkDICOMValue v = iter->GetValue();
      TestAssert(v.GetNumberOfValues() == 2);
      vtkDICOMValue *vp = v.GetMultiplexData();
      TestAssert(vp[0].AsString() == "CT");
      TestAssert(vp[1].AsString() == "MR");
      }
    ++iter;
    }
  TestAssert(iter == iterEnd);
  metaData->Clear();

  metaData->Delete();

  return rval;
}
