#include "vtkDICOMMetaData.h"
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMReader.h"

#include "vtkCommand.h"
#include "vtkSmartPointer.h"
#include "vtkStringArray.h"

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

class ReaderProgress : public vtkCommand
{
public:
  vtkTypeMacro(ReaderProgress, vtkCommand);

  static ReaderProgress *New() { return new ReaderProgress; }

  void Execute(vtkObject *object, unsigned long event, void *data) override;
};

void ReaderProgress::Execute(
  vtkObject *object, unsigned long event, void *data)
{
  if (event == vtkCommand::ProgressEvent)
  {
    if (data)
    {
      double progress = *static_cast<double *>(data);
      const char *text = "";
      vtkAlgorithm *algorithm = vtkAlgorithm::SafeDownCast(object);
      if (algorithm)
      {
        text = algorithm->GetProgressText();
      }
      if (text)
      {
        std::cout << text << ": ";
      }
      std::cout << static_cast<int>(100.0*progress + 0.5) << std::endl;
    }
  }
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
      vtkSmartPointer<ReaderProgress> progressCommand =
        vtkSmartPointer<ReaderProgress>::New();
      vtkSmartPointer<vtkDICOMReader> reader =
        vtkSmartPointer<vtkDICOMReader>::New();
      reader->AddObserver(vtkCommand::ProgressEvent, progressCommand);
      reader->SetFileNames(a);
      reader->Update();
    }
  }

  return rval;
}
