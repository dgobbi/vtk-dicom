/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2022 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMTagPath_h
#define vtkDICOMTagPath_h

#include "vtkSystemIncludes.h"
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMTag.h"

//! A tag path for digging values out of sequence items.
/*!
 *  The tag path makes it easier to access data elements that are
 *  buried within sequences.
 */
class VTKDICOM_EXPORT vtkDICOMTagPath
{
public:
  //@{
  //! Construct a tag path with an empty head and tail.
  vtkDICOMTagPath() : Size(0), Head(), Index(0), Tail(), List(0) {}

  //! Construct a tag path from a sequence tag, item index, and item tag.
  vtkDICOMTagPath(vtkDICOMTag seqTag, unsigned int i, vtkDICOMTag tag)
    : Size(2), Head(seqTag), Index(i), Tail(tag), List(0) {}

  //! Construct a tag path that goes two levels deep.
  vtkDICOMTagPath(vtkDICOMTag seqTag, unsigned int i, vtkDICOMTag tag,
                  unsigned int j, vtkDICOMTag tag2)
    : Size(3), Head(seqTag), Index(i), Tail(tag) {
    Last.Index = j; Last.Tag.Key = tag2.GetKey(); }

  //! Construct a tag path by adding to an existing tag path.
  vtkDICOMTagPath(const vtkDICOMTagPath& path, unsigned int i,
                  vtkDICOMTag tag);

  //! Construct a tag path from just a single tag.
  explicit vtkDICOMTagPath(vtkDICOMTag tag)
    : Size(1), Head(tag), Index(0), Tail(), List(0) {}

  //! Copy constructor.
  vtkDICOMTagPath(const vtkDICOMTagPath& o)
    : Size(o.Size), Head(o.Head), Index(o.Index), Tail(o.Tail) {
    if (o.Size <= 3) {
      this->Last = o.Last; }
    else {
      this->List = vtkDICOMTagPath::CopyList(o.List, o.Size - 2); } }
  //@}

  //@{
  //! Destructor.
  ~vtkDICOMTagPath() {
    if (this->Size > 3) { delete [] this->List; } }
  //@}

  //@{
  //! Assignment operator.
  vtkDICOMTagPath& operator=(const vtkDICOMTagPath& o);
  //@}

  //@{
  //! If there is no tail, then Head is the end of the path.
  bool HasTail() const {
    return (this->Size > 1); }

  //! Get the path head, which should be a sequence if HasTail() is true.
  vtkDICOMTag GetHead() const {
    return this->Head; }

  //! Get the index of the item within the sequence.
  unsigned int GetIndex() const {
    return this->Index; }

  //! Get the nth index in the path.
  unsigned int GetIndex(unsigned int i) const;

  //! Get the nth tag in the path.
  vtkDICOMTag GetTag(unsigned int i) const;

  //! Get the number of tags in the path.
  unsigned int GetSize() const {
    return this->Size; }

  //! Get the remainder of the path (after Head and Index).
  vtkDICOMTagPath GetTail() const;
  //@}

  //@{
  bool operator==(const vtkDICOMTagPath& b) const;
  bool operator!=(const vtkDICOMTagPath& b) const;
  bool operator<=(const vtkDICOMTagPath& b) const;
  bool operator>=(const vtkDICOMTagPath& b) const;
  bool operator<(const vtkDICOMTagPath& b) const;
  bool operator>(const vtkDICOMTagPath& b) const;
  //@}

private:
  struct Pair
  {
    unsigned int Index;
    vtkDICOMTag::StaticTag Tag;
  };

  vtkDICOMTagPath(vtkDICOMTag seqTag, unsigned int i, vtkDICOMTag tag,
                  unsigned int n, Pair *l) :
    Size(n+2), Head(seqTag), Index(i), Tail(tag), List(l) {}

  static Pair *CopyList(const Pair *o, unsigned int n);

  unsigned int Size;
  vtkDICOMTag Head;
  unsigned int Index;
  vtkDICOMTag Tail;
  union {
    Pair Last;
    Pair *List;
  };
};

VTKDICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMTagPath& a);

#endif /* vtkDICOMTagPath_h */
// VTK-HeaderTest-Exclude: vtkDICOMTagPath.h
