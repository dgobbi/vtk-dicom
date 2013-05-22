/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
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
