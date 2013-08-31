/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMTagPath_h
#define __vtkDICOMTagPath_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"
#include "vtkDICOMTag.h"

//! A tag path for digging values out of sequence items.
/*!
 *  The tag path makes it easier to access data elements that are
 *  buried within sequences.  In the interest of creating a simple
 *  and efficient implementation, it can go at most two levels deep.
 */
class VTK_DICOM_EXPORT vtkDICOMTagPath
{
public:
  //! Construct a tag path with an empty head and tail.
  vtkDICOMTagPath() : Head(), Index(0), Tail(), Index2(0), Tail2() {}

  //! Construct a tag path from a sequence tag, item index, and item tag.
  vtkDICOMTagPath(vtkDICOMTag seqTag, unsigned int i, vtkDICOMTag tag) :
    Head(seqTag), Index(i), Tail(tag), Index2(0), Tail2() {}

  //! Construct a tag path that goes two levels deep.
  vtkDICOMTagPath(vtkDICOMTag seqTag, unsigned int i, vtkDICOMTag tag,
                  unsigned int j, vtkDICOMTag tag2) :
    Head(seqTag), Index(i), Tail(tag), Index2(j), Tail2(tag2) {}

  //! Construct a tag path from just a single tag.
  explicit vtkDICOMTagPath(vtkDICOMTag tag) :
    Head(tag), Index(0), Tail(), Index2(0), Tail2() {}

  //! If there is no tail, then Head is the end of the path.
  bool HasTail() const {
    return (this->Tail > vtkDICOMTag()); }

  //! Get the path head, which should be a sequence if HasTail() is true.
  vtkDICOMTag GetHead() const {
    return this->Head; }

  //! Get the index of the item within the sequence.
  unsigned int GetIndex() const {
    return this->Index; }

  //! Get the remainder of the path.
  vtkDICOMTagPath GetTail() const {
    return vtkDICOMTagPath(this->Tail, this->Index2, this->Tail2); }

private:
  vtkDICOMTag Head;
  unsigned int Index;
  vtkDICOMTag Tail;
  unsigned int Index2;
  vtkDICOMTag Tail2;
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMTagPath& a);

#endif /* __vtkDICOMTagPath_h */
