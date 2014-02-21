/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
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
