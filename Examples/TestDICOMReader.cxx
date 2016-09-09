#include "vtkDICOMMetaData.h"
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMReader.h"

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

  int m = sorter->GetNumberOfStudies();
  for (int j = 0; j < m; j++)
  {
    cout << "Study" << j << ":\n";
    int k = sorter->GetFirstSeriesForStudy(j);
    int kl = sorter->GetLastSeriesForStudy(j);
    for (; k <= kl; k++)
    {
      cout << "  Series " << k << ":\n";
      vtkStringArray *a = sorter->GetFileNamesForSeries(k);
      vtkDICOMReader *reader = vtkDICOMReader::New();
      reader->SetFileNames(a);
      reader->Update();
      reader->Delete();
    }
  }

  return rval;
}
