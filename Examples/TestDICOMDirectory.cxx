#include "vtkDICOMDirectory.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMDictionary.h"

#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

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

  vtkSmartPointer<vtkDICOMDirectory> ddir =
    vtkSmartPointer<vtkDICOMDirectory>::New();

  if (argc < 2 || argc > 3)
    {
    cout << "usage: " << exename << " <directory_name> [depth]" << endl;
    exit(0);
    }

  const char *dirname = argv[1];

  int depth = 1;
  if (argc > 2)
    {
    depth = static_cast<int>(atol(argv[2]));
    }

  ddir->SetDirectoryName(dirname);
  ddir->SetScanDepth(depth);
  ddir->Update();

  int n = ddir->GetNumberOfPatients();
  for (int i = 0; i < n; i++)
    {
    const vtkDICOMItem& patientItem = ddir->GetPatientRecord(i);
    cout << "Patient " << i << ": "
         << patientItem.GetAttributeValue(DC::PatientID).AsString() << "\n";
    int j0 = ddir->GetFirstStudyForPatient(i);
    int j1 = ddir->GetLastStudyForPatient(i);
    if (i == n-1)
      {
      TestAssert(j1 == ddir->GetNumberOfStudies() - 1);
      }
    for (int j = j0; j <= j1; j++)
      {
      const vtkDICOMItem& studyItem = ddir->GetStudyRecord(j);
      const vtkDICOMItem& studyPItem = ddir->GetPatientRecordForStudy(j);
      cout << " Study " << j << ": \""
           << studyItem.GetAttributeValue(DC::StudyDescription).AsString()
           << "\" \""
           << studyPItem.GetAttributeValue(DC::PatientName).AsString()
           << "\" "
           << studyItem.GetAttributeValue(DC::StudyDate).AsString() << "\n";
      int k0 = ddir->GetFirstSeriesForStudy(j);
      int k1 = ddir->GetLastSeriesForStudy(j);
      if (i == n-1 && j == j1)
        {
        TestAssert(k1 == ddir->GetNumberOfSeries() - 1);
        }
      for (int k = k0; k <= k1; k++)
        {
        const vtkDICOMItem& seriesItem = ddir->GetSeriesRecord(j);
        cout << "  Series " << k << ": \""
             << seriesItem.GetAttributeValue(DC::SeriesDescription).AsString()
             << "\" "
             << seriesItem.GetAttributeValue(DC::SeriesNumber).AsString()
             << " "
             << seriesItem.GetAttributeValue(DC::Modality).AsString() << "\n";
        vtkStringArray *a = ddir->GetFileNamesForSeries(k);
        for (vtkIdType kk = 0; kk < a->GetNumberOfValues(); kk++)
          {
          cout << "   " << a->GetValue(kk) << "\n";
          }
        }
      }
    }

  return rval;
}
