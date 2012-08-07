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

  const char * inputImageFileName =
    "/Volumes/Work/CAIN/Data/SFMRC/Fast_SPGR_2/IM-0007-0006.dcm";

  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  parser->SetFileName(inputImageFileName);
  parser->SetMetaData(vtkDICOMMetaData::New());

  parser->Update();

  return rval;
}
