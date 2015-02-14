#include "vtkDICOMMetaData.h"
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMReader.h"
#include "vtkDICOMTagPath.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

#include <sstream>

#include <string.h>
#include <stdlib.h>
#include <math.h>

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

  vtkSmartPointer<vtkDICOMFileSorter> sorter =
    vtkSmartPointer<vtkDICOMFileSorter>::New();

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  for (int i = 1; i < argc; i++)
    {
    files->InsertNextValue(argv[i]);
    }

  sorter->SetInputFileNames(files);
  sorter->Update();

  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();

  if (sorter->GetNumberOfSeries() > 0)
    {
    // read the meta data from the supplied image
    vtkStringArray *a = sorter->GetFileNamesForSeries(0);

    vtkSmartPointer<vtkDICOMReader> reader =
    vtkSmartPointer<vtkDICOMReader>::New();
    reader->SetFileNames(a);
    reader->UpdateInformation();

    meta = reader->GetMetaData();
    }
  else if (argc == 1)
    {
    // create a real world value mapping sequence by hand
    // 1) use Unified Code for Units of Measure (UCUM), version 1.9
    // 2) the CodeMeaning should be a copy of CodeValue unless:
    // 2a) CodeValue=1, in which case use CodeMeaning=unity
    vtkDICOMItem unitsItem;
    unitsItem.SetAttributeValue(DC::CodeValue, "m2/s");
    unitsItem.SetAttributeValue(DC::CodingSchemeDesignator, "UCUM");
    unitsItem.SetAttributeValue(DC::CodingSchemeVersion, "1.9");
    unitsItem.SetAttributeValue(DC::CodeMeaning, "m2/s");

    vtkDICOMItem mappingItem;
    mappingItem.SetAttributeValue(DC::LUTExplanation, "Hot Metal");
    mappingItem.SetAttributeValue(DC::MeasurementUnitsCodeSequence,
      vtkDICOMValue(vtkDICOMVR::SQ, unitsItem));
    mappingItem.SetAttributeValue(DC::LUTLabel, "HOT_METAL");
    // need to explicitly define the VR for these, because it depends
    // on whether the PixelRepresentation is signed or unsigned
    mappingItem.SetAttributeValue(DC::RealWorldValueFirstValueMapped,
                                  vtkDICOMValue(vtkDICOMVR::US, 0));
    mappingItem.SetAttributeValue(DC::RealWorldValueLastValueMapped,
                                  vtkDICOMValue(vtkDICOMVR::US, 4095));
    mappingItem.SetAttributeValue(DC::RealWorldValueIntercept, 0.234);
    mappingItem.SetAttributeValue(DC::RealWorldValueSlope, 0.438);

    meta->SetAttributeValue(DC::RealWorldValueMappingSequence,
      vtkDICOMValue(vtkDICOMVR::SQ, mappingItem));
    }
  else
    {
    cout << "The provided file is not DICOM!" << endl;
    }

  if (meta->HasAttribute(DC::RealWorldValueMappingSequence))
    {
    const vtkDICOMItem& mappingItem =
      meta->GetAttributeValue(DC::RealWorldValueMappingSequence).GetItem(0);

    std::string lutName =
      mappingItem.GetAttributeValue(DC::LUTLabel).AsString();

    std::string units = mappingItem.GetAttributeValue(vtkDICOMTagPath(
      DC::MeasurementUnitsCodeSequence, 0, DC::CodeValue)).AsString();

    double range[2];
    range[0] = mappingItem.GetAttributeValue(
      DC::RealWorldValueFirstValueMapped).AsDouble();
    range[1] = mappingItem.GetAttributeValue(
      DC::RealWorldValueLastValueMapped).AsDouble();

    double slope = mappingItem.GetAttributeValue(
      DC::RealWorldValueSlope).AsDouble();
    double inter = mappingItem.GetAttributeValue(
      DC::RealWorldValueIntercept).AsDouble();

    cout << "Map pixel values in the range " << range[0] << ", " << range[1] << endl;
    cout << "through the equation y = " << slope << " * x + " << inter << endl;
    cout << "to real values with units of " << units << endl;
    cout << "and display the result with color table " << lutName << endl;

    if (argc == 1)
      {
      TestAssert(range[0] == 0);
      TestAssert(range[1] == 4095);
      TestAssert(fabs(slope - 0.438) < 1e-16);
      TestAssert(fabs(inter - 0.234) < 1e-16);
      TestAssert(units == "m2/s");
      TestAssert(lutName == "HOT_METAL");
      }
    }
  else
    {
    cout << "Image has no real world value mapping!" << endl;
    }

  return rval;
}
