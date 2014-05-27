/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include <assert.h>

//----------------------------------------------------------------------------
// For use by methods that must return an invalid value
const vtkDICOMValue vtkDICOMSequence::InvalidValue;

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMSequence::GetAttributeValue(
    size_t i, vtkDICOMTag tag) const
{
  const vtkDICOMItem *ptr = this->V.GetSequenceData();
  if (ptr != 0 && i < this->V.GetNumberOfValues())
    {
    return ptr[i].GetAttributeValue(tag);
    }
  return vtkDICOMSequence::InvalidValue;
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMSequence::GetAttributeValue(
    size_t i, const vtkDICOMTagPath &tagpath) const
{
  const vtkDICOMItem *ptr = this->V.GetSequenceData();
  if (ptr != 0 && i < this->V.GetNumberOfValues())
    {
    return ptr[i].GetAttributeValue(tagpath);
    }
  return vtkDICOMSequence::InvalidValue;
}

//----------------------------------------------------------------------------
const vtkDICOMItem &vtkDICOMSequence::GetItem(size_t i) const
{
  const vtkDICOMItem *ptr = this->V.GetSequenceData();
  assert(ptr != 0 && i < this->V.GetNumberOfValues());

  return ptr[i];
}

//----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const vtkDICOMSequence& v)
{
  return os << vtkDICOMValue(v);
}
