/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMReferenceCount.h"

#include <vtkWindows.h>

#if defined(_WIN32)
unsigned int vtkDICOMReferenceCount::operator--()
{
  return static_cast<unsigned int>(
    InterlockedDecrement(reinterpret_cast<LONG *>(&this->Counter)));
}
#endif

#if defined(_WIN32)
unsigned int vtkDICOMReferenceCount::operator++()
{
  return static_cast<unsigned int>(
    InterlockedIncrement(reinterpret_cast<LONG *>(&this->Counter)));
}
#endif
