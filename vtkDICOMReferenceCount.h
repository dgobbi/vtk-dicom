/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMReferenceCount_h
#define __vtkDICOMReferenceCount_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"

//! An object for holding an atomic reference count.
/*!
 *  The vtkDICOMValue class is a reference-counted container.
 *  In order to safely access values from multiple threads, all
 *  operations that modify the reference count must be atomic.
 */
class VTK_DICOM_EXPORT vtkDICOMReferenceCount
{
public:
  vtkDICOMReferenceCount(unsigned int i) : Counter(i) {};
  vtkDICOMReferenceCount() : Counter(0) {};

  unsigned int operator--();
  unsigned int operator++();

  bool operator==(unsigned int x) const {
    return this->Counter == x; }
  bool operator!=(unsigned int x) const {
    return this->Counter != x; }

private:
  unsigned int Counter;
};

#if !defined(_WIN32)
inline unsigned int vtkDICOMReferenceCount::operator--()
{
#if defined(VTK_HAVE_SYNC_BUILTINS)
  return __sync_sub_and_fetch(&this->Counter, 1);
#else
  return --this->Counter;
#endif
}
#endif

#if !defined(_WIN32)
inline unsigned int vtkDICOMReferenceCount::operator++()
{
#if defined(VTK_HAVE_SYNC_BUILTINS)
  return __sync_add_and_fetch(&this->Counter, 1);
#else
  return ++this->Counter;
#endif
}
#endif

#endif /* __vtkDICOMReferenceCount_h */
