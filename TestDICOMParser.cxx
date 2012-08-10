#include "vtkDICOMParser.h"
#include "vtkDICOMMetaData.h"
#include <vtkSmartPointer.h>

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

  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  for (int i = 1; i < argc; i++)
    {
    cout << "=========== " << argv[i] << " =========\n";

    vtkSmartPointer<vtkDICOMMetaData> data =
      vtkSmartPointer<vtkDICOMMetaData>::New();

    parser->SetFileName(argv[i]);
    parser->SetMetaData(data);

    parser->Update();
    }

  return rval;
}
