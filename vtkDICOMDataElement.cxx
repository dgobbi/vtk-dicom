#include "vtkDICOMDataElement.h"

ostream& operator<<(ostream& os, const vtkDICOMDataElement& v)
{
  os << v.GetTag() << "," << v.GetVR() << "," << v.GetVL() << ","
     << v.GetValue();

  return os;
}
