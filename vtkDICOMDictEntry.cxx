#include "vtkDICOMDictEntry.h"

const vtkDICOMDictionary::Entry vtkDICOMDictEntry::InvalidEntry = {
  0, 0, 0, 0, 0, "" };

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
