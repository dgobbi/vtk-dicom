#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMDictionary.h"
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

namespace {

bool StringsEqual(const char *s1, const char *s2)
{
  bool result = true;
  if (s1 != s2)
    {
    result = false;
    if (s1 != 0 && s2 != 0)
      {
      result = (strcmp(s1, s2) == 0);
      }
    }
  return result;
}

}

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMSequence");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  // some miscellaneous UIDs to use
  const char *classUID = "1.2.840.10008.5.1.4.1.1.4";
  const char *instanceUIDFormat =
    "1.2.840.113619.2.176.2025.4110284.7408.1276101323.%i";
  char instanceUID[54];

  // create the ReferencedSeriesSequence
  vtkDICOMSequence seq(1);

  // only add one item to the sequence
  for (int i = 0; i < 1; i++)
    {
    // add the first data element to the item
    vtkDICOMItem item;
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
      vtkDICOMItem item2;
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

  // do the tests
  unsigned int n = seq.GetNumberOfItems();
  TestAssert(n == 1);

  // use iterator to go through the elements in each item
  vtkDICOMDataElementIterator iter;

  // use a plain old pointer to go through items in sequence
  const vtkDICOMItem *ip1 = seq.GetSequenceData();

  // test variables
  bool found1 = false;
  bool found2 = false;
  int fullcount = 0;

  // go through the item in ReferencedSeriesSequence
  for (iter = ip1->Begin(); iter != ip1->End(); ++iter)
    {
    // make sure SeriesInstanceUID was found
    if (iter->GetTag() == DC::SeriesInstanceUID)
      {
      found1 = true;
      TestAssert(StringsEqual(iter->GetValue().GetCharData(),
        "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239"));
      }
    // make sure ReferencedInstanceSequence was found
    if (iter->GetTag() == DC::ReferencedInstanceSequence)
      {
      found2 = true;
      vtkDICOMDataElementIterator iter2;

      // get the nested sequence
      vtkDICOMSequence v2 = iter->GetValue();
      unsigned int m = v2.GetNumberOfItems();
      TestAssert(m == 10);

      // go through the 10 items in the sequence
      for (unsigned int j = 0; j < m; j++)
        {
        // check the two elements in each item
        const vtkDICOMItem &item = v2.GetItem(j);
        TestAssert(item.GetNumberOfDataElements() == 2);
        vtkDICOMValue v3;
        v3 = item.GetAttributeValue(DC::ReferencedSOPClassUID);
        TestAssert(StringsEqual(v3.GetCharData(), "1.2.840.10008.5.1.4.1.1.4"));
        v3 = item.GetAttributeValue(DC::ReferencedSOPInstanceUID);
        sprintf(instanceUID, instanceUIDFormat, 255+j);
        TestAssert(StringsEqual(v3.GetCharData(), instanceUID));
        }
      }
    fullcount++;
    }

  // check that there were two elements in the ReferencedSeriesSequence item
  TestAssert(fullcount == 2);

  // test direct access with GetAttributeValue
  vtkDICOMValue v2 = seq.GetAttributeValue(0, DC::SeriesInstanceUID);
  TestAssert(StringsEqual(v2.GetCharData(),
                    "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239"));

  // test nested access with tag path
  v2 = seq.GetAttributeValue(
    0, vtkDICOMTagPath(DC::ReferencedInstanceSequence, 0,
                       DC::ReferencedSOPClassUID));
  TestAssert(StringsEqual(v2.GetCharData(), "1.2.840.10008.5.1.4.1.1.4"));

  // test appending to a sequence
  vtkDICOMSequence seq3;

  TestAssert(seq3.GetNumberOfItems() == 0);

  vtkDICOMValue val3 = seq3;

  TestAssert(val3.GetVR() == vtkDICOMVR::SQ);
  TestAssert(val3.GetVL() == 0xffffffffu);
  TestAssert(val3.GetNumberOfValues() == 0);

  for (int i = 0; i < 1; i++)
    {
    vtkDICOMItem item;
    item.SetAttributeValue(DC::SeriesInstanceUID,
      vtkDICOMValue(vtkDICOMVR::UI,
        "1.2.840.113619.2.176.2025.4110284.7478.1276100777.239"));
    seq3.AddItem(item);
    }

  TestAssert(seq3.GetNumberOfItems() == 1);

  // previously assigned value should be unchanged
  TestAssert(val3.GetVR() == vtkDICOMVR::SQ);
  TestAssert(val3.GetVL() == 0xffffffffu);
  TestAssert(val3.GetNumberOfValues() == 0);

  // update the value
  val3 = seq3;

  TestAssert(val3.GetVR() == vtkDICOMVR::SQ);
  TestAssert(val3.GetVL() == 0xffffffffu);
  TestAssert(val3.GetNumberOfValues() == 1);

  seq3.Clear();

  TestAssert(val3.GetVR() == vtkDICOMVR::SQ);
  TestAssert(val3.GetVL() == 0xffffffffu);
  TestAssert(val3.GetNumberOfValues() == 1);

  val3 = seq3;

  TestAssert(val3.GetVR() == vtkDICOMVR::SQ);
  TestAssert(val3.GetVL() == 0xffffffffu);
  TestAssert(val3.GetNumberOfValues() == 0);

  return rval;
}
