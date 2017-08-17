/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMTagPath.h"

//----------------------------------------------------------------------------
ostream& operator<<(ostream& o, const vtkDICOMTagPath& a)
{
  o << "[";
  o << a.GetHead();
  if (a.HasTail())
  {
    unsigned int i = a.GetIndex();
    vtkDICOMTagPath b = a.GetTail();
    for (;;)
    {
      o << ",";
      o << i;
      o << ",";
      o << b.GetHead();
      if (!b.HasTail())
      {
        break;
      }
      i = b.GetIndex();
      b = b.GetTail();
    }
  }
  o << "]";

  return o;
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator==(const vtkDICOMTagPath& b) const
{
  return (this->Head == b.Head &&
          this->Index == b.Index &&
          this->Tail == b.Tail &&
          this->Index2 == b.Index2 &&
          this->Tail2 == b.Tail2);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator!=(const vtkDICOMTagPath& b) const
{
  return !(*this == b);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator<(const vtkDICOMTagPath& b) const
{
  return (this->Head < b.Head ||
          (this->Head == b.Head &&
           (this->Index < b.Index ||
            (this->Index == b.Index &&
             (this->Tail < b.Tail ||
              (this->Tail == b.Tail &&
               (this->Index2 < b.Index2 ||
                (this->Index2 == b.Index2 &&
                 (this->Tail2 < b.Tail2)))))))));
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator>(const vtkDICOMTagPath& b) const
{
  return !(*this < b || *this == b);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator<=(const vtkDICOMTagPath& b) const
{
  return (*this < b || *this == b);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator>=(const vtkDICOMTagPath& b) const
{
  return !(*this < b);
}
