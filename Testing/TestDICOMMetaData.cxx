#include "vtkDICOMMetaData.h"
#include "vtkDICOMValue.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

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
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMMetaData");

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
  metaData->Initialize();
  TestAssert(metaData->GetNumberOfInstances() == 1);

  // test iterating through the data elements
  vtkDICOMDataElementIterator iter =
    metaData->Begin();
  vtkDICOMDataElementIterator iterEnd =
    metaData->End();
  TestAssert(iter == iterEnd);
  metaData->SetAttributeValue(DC::Modality, "CT");
  const char *acquisitionTime = "20130126080000.000000+0700";
  metaData->SetAttributeValue(DC::AcquisitionDateTime, acquisitionTime);
  iter = metaData->Begin();
  iterEnd = metaData->End();
  int n = metaData->GetNumberOfDataElements();
  TestAssert(n == 2);
  for (int i = 0; i < n; i++)
    {
    if (i == 0)
      {
      TestAssert(iter->GetTag() == DC::AcquisitionDateTime);
      TestAssert(iter->GetVR() == vtkDICOMVR::DT);
      TestAssert(iter->GetValue().GetVL() == 26);
      TestAssert(iter->GetValue().AsString() == acquisitionTime);
      }
    else
      {
      TestAssert(iter->GetTag() == DC::Modality);
      TestAssert(iter->GetVR() == vtkDICOMVR::CS);
      TestAssert(iter->GetValue().GetVL() == 2);
      TestAssert(iter->GetValue().AsString() == "CT");
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
  iter = metaData->Begin();
  iterEnd = metaData->End();
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
      const vtkDICOMValue *vp = v.GetMultiplexData();
      TestAssert(vp[0].AsString() == "CT");
      TestAssert(vp[1].AsString() == "MR");
      }
    ++iter;
    }
  TestAssert(iter == iterEnd);
  metaData->Clear();

  // test the Find() method
  metaData->SetNumberOfInstances(2);
  metaData->SetAttributeValue(0, DC::Modality, "CT");
  metaData->SetAttributeValue(1, DC::Modality, "MR");
  metaData->SetAttributeValue(DC::AcquisitionDateTime, acquisitionTime);
  iter = metaData->Find(DC::AcquisitionDateTime);
  TestAssert(iter->GetValue().AsString() == acquisitionTime);
  iter = metaData->Find(DC::Modality);
  if (iter != metaData->End())
    {
    vtkDICOMValue v = iter->GetValue();
    const vtkDICOMValue *vp = v.GetMultiplexData();
    TestAssert(vp[0].AsString() == "CT");
    TestAssert(vp[1].AsString() == "MR");
    }
  iter = metaData->Find(DC::StudyDate);
  TestAssert(iter == metaData->End());
  metaData->Clear();

  // ------
  // test sequence access: some miscellaneous UIDs to use
  const char *classUID = "1.2.840.10008.5.1.4.1.1.4";
  const char *instanceUIDFormat =
    "1.2.840.113619.2.176.2025.4110284.7408.1276101323.%i";
  char instanceUID[54];

  // create the ReferencedSeriesSequence
  vtkDICOMSequence seq(1);

  // only add one item to the outer sequence
  for (int i = 0; i < 1; i++)
    {
    // add the first data element to the item
    vtkDICOMItem item(metaData);
    item.SetAttributeValue(DC::SeriesInstanceUID,
      vtkDICOMValue(vtkDICOMVR::UI,
        "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239"));

    // the second data element will be a nested sequence
    vtkDICOMSequence seq2;

    // add ten items to this sequence
    for (int j = 0; j < 10; j++)
      {
      // create a unique InstanceUID
      sprintf(instanceUID, instanceUIDFormat, 255+j);
      vtkDICOMItem item2(metaData);
      item2.SetAttributeValue(DC::ReferencedSOPClassUID,
        vtkDICOMValue(vtkDICOMVR::UI, classUID));
      item2.SetAttributeValue(DC::ReferencedSOPInstanceUID,
        vtkDICOMValue(vtkDICOMVR::UI, instanceUID));
      seq2.AddItem(item2);
      }

    // create the ReferencedInstanceSequence from the items
    item.SetAttributeValue(DC::ReferencedInstanceSequence, seq2);

    // add this sequence-containing item to the original sequence
    seq.SetItem(i, item);
    }

  // test nested access with tag path
  metaData->SetAttributeValue(DC::ReferencedSeriesSequence, seq);
  vtkDICOMValue v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(v2.GetCharData() != 0);
  if (v2.GetCharData())
    {
    TestAssert(
      strcmp(v2.GetCharData(),
             "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239") == 0);
    }

  // test access two levels deep
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::ReferencedInstanceSequence, 0,
                    DC::ReferencedSOPClassUID));
  TestAssert(v2.GetCharData() != 0);
  if (v2.GetCharData())
    {
    TestAssert(strcmp(v2.GetCharData(), "1.2.840.10008.5.1.4.1.1.4") == 0);
    }

  metaData->Clear();

  // ------
  // test setting sequences via tagpath
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID),
    vtkDICOMValue(vtkDICOMVR::UI,
                  "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239"));

  for (int j = 0; j < 10; j++)
    {
    // create a unique InstanceUID
    sprintf(instanceUID, instanceUIDFormat, 255+j);
    metaData->SetAttributeValue(
      vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                      DC::ReferencedInstanceSequence, j,
                      DC::ReferencedSOPClassUID),
      classUID);
    metaData->SetAttributeValue(
      vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                      DC::ReferencedInstanceSequence, j,
                      DC::ReferencedSOPInstanceUID),
      instanceUID);
    }

  // test nested access with tag path
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(v2.GetCharData() != 0);
  if (v2.GetCharData())
    {
    TestAssert(
      strcmp(v2.GetCharData(),
             "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239") == 0);
    }

  // test access two levels deep
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::ReferencedInstanceSequence, 9,
                    DC::ReferencedSOPClassUID));
  TestAssert(v2.GetCharData() != 0);
  if (v2.GetCharData())
    {
    TestAssert(strcmp(v2.GetCharData(), "1.2.840.10008.5.1.4.1.1.4") == 0);
    }
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::ReferencedInstanceSequence, 8,
                    DC::ReferencedSOPInstanceUID));
  TestAssert(v2.GetCharData() != 0);
  if (v2.GetCharData())
    {
    TestAssert(0 == strcmp(
      v2.GetCharData(),
      "1.2.840.113619.2.176.2025.4110284.7408.1276101323.263"));
    }

  metaData->Clear();

  // ------
  // test inheritance of XS=US,SS and CharacterSet

  // first, check default XS=US
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::RealWorldValueLastValueMapped), 4095);
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::RealWorldValueLastValueMapped));
  TestAssert(v2.GetVR() == vtkDICOMVR::US);

  // next, check default CharacterSet=ISO_IR_6
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation), "Too Hot");
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation));
  TestAssert(v2.GetCharacterSet() == vtkDICOMCharacterSet::ISO_IR_6);

  metaData->Clear();

  // next, check inheritance of XS=SS
  metaData->SetAttributeValue(DC::BitsAllocated, 16);
  metaData->SetAttributeValue(DC::PixelRepresentation, 1);
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::RealWorldValueLastValueMapped), 4095);
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::RealWorldValueLastValueMapped));
  TestAssert(v2.GetVR() == vtkDICOMVR::SS);

  // two levels deep
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::IconImageSequence, 0,
                    DC::RealWorldValueMappingSequence, 0,
                    DC::RealWorldValueLastValueMapped), 4095);
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::IconImageSequence, 0,
                    DC::RealWorldValueMappingSequence, 0,
                    DC::RealWorldValueLastValueMapped));
  TestAssert(v2.GetVR() == vtkDICOMVR::SS);

  metaData->Clear();

  // check inheritance of ISO_IR_100
  metaData->SetAttributeValue(DC::SpecificCharacterSet, "ISO_IR 100");
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation), "Too Hot");
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation));
  TestAssert(v2.GetCharacterSet() == vtkDICOMCharacterSet::ISO_IR_100);

  // override with new item-specific character set
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::SpecificCharacterSet), "\\ISO 2022 IR 149");
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation), "Too Hot");
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation));
  TestAssert(v2.GetCharacterSet() == vtkDICOMCharacterSet::ISO_2022_IR_149);

  // two levels deep
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::IconImageSequence, 0,
                    DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation), "Too Hot");
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::IconImageSequence, 0,
                    DC::RealWorldValueMappingSequence, 0,
                    DC::LUTExplanation));
  TestAssert(v2.GetCharacterSet() == vtkDICOMCharacterSet::ISO_IR_100);

  metaData->Clear();

  // ------
  // if a non-sequence is used in a path, the call is ignored
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::SeriesInstanceUID, 0,
                    DC::SeriesInstanceUID),
    vtkDICOMValue(vtkDICOMVR::UI,
                  "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239"));
  TestAssert(metaData->GetNumberOfDataElements() == 0);

  // ------
  // test using a non-sequence that already exists
  metaData->SetAttributeValue(DC::SeriesInstanceUID,
    "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239");
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::SeriesInstanceUID, 0,
                    DC::SeriesInstanceUID),
    vtkDICOMValue(vtkDICOMVR::UI,
                  "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239"));
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(DC::SeriesInstanceUID, 0,
                    DC::SeriesInstanceUID));
  TestAssert(!v2.IsValid());
  v2 = metaData->GetAttributeValue(vtkDICOMTagPath(DC::SeriesInstanceUID));
  if (v2.GetCharData())
    {
    TestAssert(
      strcmp(v2.GetCharData(),
             "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239") == 0);
    }

  // test using a tag path with a private sequence
  metaData->SetAttributeValue(
    vtkDICOMTagPath(vtkDICOMTag(0x0009, 0x1013), 0,
                    vtkDICOMTag(0x0009, 0x1014), 1,
                    vtkDICOMTag(0x0009, 0x1015)),
    vtkDICOMValue(vtkDICOMVR::UI, "1.2.840.113619.2.176.2025"));
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(vtkDICOMTag(0x0009, 0x1013), 0,
                    vtkDICOMTag(0x0009, 0x1014), 1,
                    vtkDICOMTag(0x0009, 0x1015)));
  TestAssert(v2.AsString() == "1.2.840.113619.2.176.2025");
  // make sure the "skipped" item returns nothing
  v2 = metaData->GetAttributeValue(
    vtkDICOMTagPath(vtkDICOMTag(0x0009, 0x1013), 0,
                    vtkDICOMTag(0x0009, 0x1014), 0,
                    vtkDICOMTag(0x0009, 0x1015)));
  TestAssert(!v2.IsValid());

  metaData->Clear();

  // ------
  // Test setting tag paths with indices
  metaData->SetNumberOfInstances(3);
  metaData->SetAttributeValue(0,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID),
    "1.2.840.113619.2.176.2025.4110284.747");
  metaData->SetAttributeValue(2,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID),
    "1.2.840.113619.2.176.2025.4110284.749");
  v2 = metaData->GetAttributeValue(0,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(v2.AsString() == "1.2.840.113619.2.176.2025.4110284.747");
  v2 = metaData->GetAttributeValue(1,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(!v2.IsValid());
  v2 = metaData->GetAttributeValue(2,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(v2.AsString() == "1.2.840.113619.2.176.2025.4110284.749");
  // Set without index
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID),
    "1.2.840.113619.2.176.2025.4110284.747");
  for (int i = 0; i < 3; i++)
    {
    v2 = metaData->GetAttributeValue(i,
      vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                      DC::SeriesInstanceUID));
    TestAssert(v2.AsString() == "1.2.840.113619.2.176.2025.4110284.747");
    }

  metaData->Clear();

  // ------
  // Test setting tag paths with indices after setting without indices
  metaData->SetNumberOfInstances(3);
  metaData->SetAttributeValue(
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID),
    "1.2.840.113619.2.176.2025.4110284.747");
  metaData->SetAttributeValue(1,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID),
    vtkDICOMValue());
  metaData->SetAttributeValue(2,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID),
    "1.2.840.113619.2.176.2025.4110284.749");
  v2 = metaData->GetAttributeValue(0,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(v2.AsString() == "1.2.840.113619.2.176.2025.4110284.747");
  v2 = metaData->GetAttributeValue(1,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(!v2.IsValid());
  v2 = metaData->GetAttributeValue(2,
    vtkDICOMTagPath(DC::ReferencedSeriesSequence, 0,
                    DC::SeriesInstanceUID));
  TestAssert(v2.AsString() == "1.2.840.113619.2.176.2025.4110284.749");

  metaData->Clear();

  // ------
  // Test setting invalid value attributes
  metaData->SetNumberOfInstances(3);
  metaData->SetAttributeValue(DC::Modality, "CT");
  metaData->SetAttributeValue(DC::Modality, "MR");
  TestAssert(metaData->GetNumberOfDataElements() == 1);
  metaData->SetAttributeValue(DC::Modality, vtkDICOMValue());
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  metaData->SetAttributeValue(0, DC::Modality, vtkDICOMValue());
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  metaData->SetAttributeValue(DC::Modality, "MR");
  metaData->SetAttributeValue(0, DC::Modality, "CT");
  TestAssert(metaData->GetAttributeValue(0, DC::Modality).AsString() == "CT");
  TestAssert(metaData->GetAttributeValue(1, DC::Modality).AsString() == "MR");
  TestAssert(metaData->GetAttributeValue(2, DC::Modality).AsString() == "MR");
  metaData->SetAttributeValue(1, DC::Modality, vtkDICOMValue());
  TestAssert(metaData->GetAttributeValue(0, DC::Modality).AsString() == "CT");
  TestAssert(metaData->GetAttributeValue(1, DC::Modality).IsValid() == false);
  TestAssert(metaData->GetAttributeValue(2, DC::Modality).AsString() == "MR");
  metaData->SetAttributeValue(0, DC::Modality, vtkDICOMValue());
  metaData->SetAttributeValue(2, DC::Modality, vtkDICOMValue());
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  metaData->SetAttributeValue(0, DC::Modality, "CT");
  TestAssert(metaData->GetAttributeValue(0, DC::Modality).AsString() == "CT");
  TestAssert(metaData->GetAttributeValue(1, DC::Modality).IsValid() == false);
  TestAssert(metaData->GetAttributeValue(2, DC::Modality).IsValid() == false);
  metaData->Clear();

  // ------
  // Test DeepCopy
  metaData->SetNumberOfInstances(3);
  metaData->SetAttributeValue(DC::Modality, "CT");
  metaData->SetAttributeValue(0, DC::Modality, "MR");
  metaData->SetAttributeValue(DC::AcquisitionDateTime, acquisitionTime);

  metaData->DeepCopy(metaData);
  TestAssert(metaData->GetNumberOfInstances() == 3);
  TestAssert(metaData->GetNumberOfDataElements() == 2);

  vtkDICOMMetaData *mcopy = vtkDICOMMetaData::New();
  mcopy->DeepCopy(metaData);
  metaData->DeepCopy(mcopy);
  mcopy->DeepCopy(metaData);
  metaData->DeepCopy(mcopy);
  mcopy->DeepCopy(metaData);
  TestAssert(mcopy->GetNumberOfInstances() == 3);
  TestAssert(mcopy->GetNumberOfDataElements() == 2);
  TestAssert(mcopy->GetAttributeValue(0, DC::Modality).AsString() == "MR");
  TestAssert(mcopy->GetAttributeValue(1, DC::Modality).AsString() == "CT");
  TestAssert(mcopy->GetAttributeValue(
    DC::AcquisitionDateTime).AsString() == acquisitionTime);

  mcopy->Initialize();
  metaData->DeepCopy(mcopy);
  TestAssert(metaData->GetNumberOfInstances() == 1);
  TestAssert(metaData->GetNumberOfDataElements() == 0);
  mcopy->Delete();

  metaData->Delete();

  return rval;
}
