/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMTagPath.h"

ostream& operator<<(ostream& o, const vtkDICOMTagPath& a)
{
  o << "[";
  o << a.GetHead();
  if (a.HasTail())
    {
    vtkDICOMTagPath b = a;
    while (b.HasTail())
      {
      o << ",";
      o << b.GetIndex();
      o << ",";
      o << b.GetHead();
      b = b.GetTail();
      }
    }
  o << "]";

  return o;
}
