#include "vtkDICOMVR.h"

ostream& operator<<(ostream& o, const vtkDICOMVR& a)
{
  o << static_cast<char>(a.Key >> 8) << static_cast<char>(a.Key);
  return o;
}
