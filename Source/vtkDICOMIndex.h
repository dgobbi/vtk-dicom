/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMIndex_h
#define vtkDICOMIndex_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"

//! An index is an (file, frame) pair that identifies an image.
/*!
 *  Since DICOM data sets can be in legacy format (a series of files) or
 *  enhanced multi-frame format (one or more files with multiple frames),
 *  a reasonable way to identify a single image is with both a file index
 *  and a frame index.
 */
class VTK_DICOM_EXPORT vtkDICOMIndex
{
public:
  vtkDICOMIndex() : Key(0) {}

  //! Construct an index from a file index and frame index.
  vtkDICOMIndex(int file, int frame)
    : Key((static_cast<unsigned long long>(file) << 32) |
          static_cast<unsigned long long>(frame)) {}

  //! Get the file index.
  int GetFileIndex() const {
    return static_cast<int>(this->Key >> 32); }

  //! Get the frame index.
  int GetFrameIndex() const {
    return static_cast<int>(this->Key); }

  bool operator==(const vtkDICOMIndex& b) const {
    return (this->Key == b.Key); }

  bool operator!=(const vtkDICOMIndex& b) const {
    return (this->Key != b.Key); }

  bool operator<=(const vtkDICOMIndex& b) const {
    return ((this->GetFileIndex() < b.GetFileIndex()) ||
            ((this->GetFileIndex() == b.GetFileIndex()) &&
             (this->GetFrameIndex() <= b.GetFrameIndex()))); }

  bool operator>=(const vtkDICOMIndex& b) const {
    return ((this->GetFileIndex() > b.GetFileIndex()) ||
            ((this->GetFileIndex() == b.GetFileIndex()) &&
             (this->GetFrameIndex() >= b.GetFrameIndex()))); }

  bool operator<(const vtkDICOMIndex& b) const {
    return ((this->GetFileIndex() < b.GetFileIndex()) ||
            ((this->GetFileIndex() == b.GetFileIndex()) &&
             (this->GetFrameIndex() < b.GetFrameIndex()))); }

  bool operator>(const vtkDICOMIndex& b) const {
    return ((this->GetFileIndex() > b.GetFileIndex()) ||
            ((this->GetFileIndex() == b.GetFileIndex()) &&
             (this->GetFrameIndex() > b.GetFrameIndex()))); }

private:
  unsigned long long Key;
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMIndex& a);

#endif /* vtkDICOMIndex_h */
