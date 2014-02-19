/*=========================================================================
This is an automatically generated file.  Do not edit.
=========================================================================*/

#include "vtkDICOMDictionary.h"
#include "vtkDICOMDictPrivate.h"

namespace {

typedef vtkDICOMVR VR;
typedef vtkDICOMVM VM;
typedef vtkDICOMDictEntry::Entry DictEntry;

// private dictionary hash tables go here

} // end anonymous namespace

static int vtkDICOMDictPrivateInitializerCounter;

vtkDICOMDictPrivateInitializer::vtkDICOMDictPrivateInitializer()
{
  if (vtkDICOMDictPrivateInitializerCounter++ == 0)
    {
    // private dictionaries are added to vtkDICOMDictionary here
    }
}

vtkDICOMDictPrivateInitializer::~vtkDICOMDictPrivateInitializer()
{
  --vtkDICOMDictPrivateInitializerCounter;
}
