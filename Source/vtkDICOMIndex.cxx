/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMIndex.h"

ostream& operator<<(ostream& o, const vtkDICOMIndex& a)
{
  o << "(" << a.GetFileIndex() << "," << a.GetFrameIndex() << ")";

  return o;
}
