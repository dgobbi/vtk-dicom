#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include <assert.h>

const vtkDICOMItem &vtkDICOMSequence::GetItem(unsigned int i) const
{
  const vtkDICOMItem *ptr = this->V.GetSequenceData();
  assert(ptr != 0 && i < this->V.GetNumberOfValues());

  return ptr[i];
}

ostream& operator<<(ostream& os, const vtkDICOMSequence& v)
{
  return os << vtkDICOMValue(v);
}
