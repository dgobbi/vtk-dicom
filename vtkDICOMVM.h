/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMVM_h
#define __vtkDICOMVM_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"

//! VMs (Value Multiplicities)
class VTK_DICOM_EXPORT vtkDICOMVM
{
public:
  enum EnumType
  {
    M0    = 0x0000,
    M1    = 0x0101,
    M1T2  = 0x0102,
    M1T3  = 0x0103,
    M1T32 = 0x0120,
    M1T99 = 0x0163,
    M1TN  = 0x01FF,
    M2    = 0x0202,
    M2T2N = 0x02FE,
    M2TN  = 0x02FF,
    M3    = 0x0303,
    M3T3N = 0x03FD,
    M3TN  = 0x03FF,
    M4    = 0x0404,
    M5    = 0x0505,
    M6    = 0x0606,
    M6TN  = 0x06FF,
    M8    = 0x0808,
    M9    = 0x0909,
    M16   = 0x1010,
    M24   = 0x1818,
    M256  = 0x8100
  };

  //! Construct an empty, invalid VM.
  vtkDICOMVM() : Key(0) {}

  //! Construct a VM from a VM enum constant.
  vtkDICOMVM(EnumType vm) : Key(static_cast<unsigned short>(vm)) {};

  //! Check validity of this VM.
  bool IsValid() const { return (this->Key != 0); }

  //! Get the minimum allowed number of values
  int GetMin() const {
    if ((this->Key & 0x8000) != 0) { return (this->Key & 0x7fff); }
    else { return (this->Key >> 8); } }

  //! Get the maximum allowed number of values, -1 if unlimited
  int GetMax() const {
    if ((this->Key & 0x8000) != 0) { return (this->Key & 0x7fff); }
    else { return ((this->Key & 0x80) == 0 ? (this->Key & 0xff) : -1); } }

  //! Get the step between allowed values.
  int GetStep() const {
    if ((this->Key & 0x8000) != 0) { return 1; }
    else { return ((this->Key & 0x80) == 0 ? 1 : ((-this->Key) & 0xff)); } }

  bool operator==(vtkDICOMVM b) const { return (this->Key == b.Key); }
  bool operator!=(vtkDICOMVM b) const { return (this->Key != b.Key); }
  bool operator<=(vtkDICOMVM a) const { return (this->Key <= a.Key); }
  bool operator>=(vtkDICOMVM a) const { return (this->Key >= a.Key); }
  bool operator<(vtkDICOMVM a) const { return (this->Key < a.Key); }
  bool operator>(vtkDICOMVM a) const { return (this->Key > a.Key); }

private:
  unsigned short Key;
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMVM& a);

#endif /* __vtkDICOMVM_h */
