#include "vtkDICOMVM.h"

ostream& operator<<(ostream& o, const vtkDICOMVM& a)
{
  int n = a.GetMin();
  int m = a.GetMax();
  int s = a.GetStep();
  o << n;
  if (m > n || m < 0)
    {
    o << "-";
    if (s > 1)
      {
      o << s;
      }
    if (m > 0)
      {
      o << m;
      }
    else
      {
      o << "n";
      }
    }

  return o;
}
