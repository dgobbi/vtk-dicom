/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include <assert.h>

// provide extern declarations for all the template methods we use
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1700)
extern template
void vtkDICOMValue::AppendInit<vtkDICOMItem>(vtkDICOMVR);

extern template
void vtkDICOMValue::AppendValue<vtkDICOMItem>(const vtkDICOMItem&);

extern template
void vtkDICOMValue::SetValue<vtkDICOMItem>(size_t, const vtkDICOMItem&);
#endif

//----------------------------------------------------------------------------
// For use by methods that must return an invalid value
const vtkDICOMValue vtkDICOMSequence::InvalidValue;

// For use by methods that must return an empty item
const vtkDICOMItem vtkDICOMSequence::EmptyItem;

//----------------------------------------------------------------------------
vtkDICOMSequence::vtkDICOMSequence()
{
  this->V.AppendInit<vtkDICOMItem>(vtkDICOMVR::SQ);
}

//----------------------------------------------------------------------------
vtkDICOMSequence::vtkDICOMSequence(unsigned int n)
{
  this->V.AllocateSequenceData(vtkDICOMVR::SQ, n);
}

//----------------------------------------------------------------------------
void vtkDICOMSequence::Clear()
{
  this->V.AppendInit<vtkDICOMItem>(vtkDICOMVR::SQ);
}

//----------------------------------------------------------------------------
void vtkDICOMSequence::AddItem(const vtkDICOMItem& item)
{
  this->V.AppendValue(item);
}

//----------------------------------------------------------------------------
void vtkDICOMSequence::SetItem(size_t i, const vtkDICOMItem& item)
{
  this->V.SetValue(i, item);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMSequence::Get(size_t i, vtkDICOMTag tag) const
{
  const vtkDICOMItem *ptr = this->V.GetSequenceData();
  if (ptr != nullptr && i < this->V.GetNumberOfValues())
  {
    return ptr[i].Get(tag);
  }
  return vtkDICOMSequence::InvalidValue;
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMSequence::Get(
    size_t i, const vtkDICOMTagPath &tagpath) const
{
  const vtkDICOMItem *ptr = this->V.GetSequenceData();
  if (ptr != nullptr && i < this->V.GetNumberOfValues())
  {
    return ptr[i].Get(tagpath);
  }
  return vtkDICOMSequence::InvalidValue;
}

//----------------------------------------------------------------------------
const vtkDICOMItem &vtkDICOMSequence::GetItem(size_t i) const
{
  const vtkDICOMItem *ptr = this->V.GetSequenceData();
  if (ptr != nullptr && i < this->V.GetNumberOfValues())
  {
    return ptr[i];
  }
  return vtkDICOMSequence::EmptyItem;
}

//----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const vtkDICOMSequence& v)
{
  return os << vtkDICOMValue(v);
}
