#include "vtkDICOMReferenceCount.h"

#include <vtkWindows.h>

#if defined(_WIN32)
unsigned int vtkDICOMReferenceCount::operator--()
{
  return static_cast<unsigned int>(
    InterlockedDecrement(static_cast<LONG *>(&this->Counter)));
}
#endif

#if defined(_WIN32)
unsigned int vtkDICOMReferenceCount::operator++()
{
  return static_cast<unsigned int>(
    InterlockedIncrement(static_cast<LONG *>(&this->Counter)));
}
#endif
