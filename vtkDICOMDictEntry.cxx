#include "vtkDICOMDictEntry.h"

ostream& operator<<(ostream& o, vtkDICOMDictEntry a)
{
  if (a.I == 0)
    {
    o << "INVALID";
    }
  else
    {
    o << a.GetTag() << "," << a.GetVR() << "," << a.GetVM() << ","
      << "\"" << a.GetName() << "\"";
    }

  return o;
}
