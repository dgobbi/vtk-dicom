#include "vtkDICOMAttributeTags.h"
#include "vtkDICOMTag.h"

#include <assert.h>

vtkDICOMTag vtkDICOMAttributeTags::GetTag(unsigned int i) const
{
  const unsigned short *ptr = this->V.GetUnsignedShortData();
  assert(ptr != 0 && 2*i+1 < this->V.GetNumberOfValues());

  return vtkDICOMTag(ptr[2*i], ptr[2*i+1]);
}
