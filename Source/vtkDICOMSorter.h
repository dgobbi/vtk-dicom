/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMSorter_h
#define vtkDICOMSorter_h

#include "vtkDICOMFileSorter.h"

//! Deprecated class, please use vtkDICOMFileSorter instead.
class VTKDICOM_EXPORT vtkDICOMSorter : public vtkDICOMFileSorter
{
public:
  //@{
  vtkTypeMacro(vtkDICOMSorter,vtkDICOMFileSorter);
  void PrintSelf(ostream& os, vtkIndent indent) VTK_DICOM_OVERRIDE;
  static vtkDICOMSorter *New();
  //@}

  //@{
  //! Get the first series in a particular study.
  int GetFirstSeriesInStudy(int study);

  //! Get the number of series in a particular study.
  int GetNumberOfSeriesInStudy(int study);
  //@}

protected:
  vtkDICOMSorter();
  ~vtkDICOMSorter() VTK_DICOM_OVERRIDE;

private:
#ifdef VTK_DICOM_DELETE
  vtkDICOMSorter(const vtkDICOMSorter&) VTK_DICOM_DELETE;
  void operator=(const vtkDICOMSorter&) VTK_DICOM_DELETE;
#else
  vtkDICOMSorter(const vtkDICOMSorter&) = delete;
  void operator=(const vtkDICOMSorter&) = delete;
#endif
};

#endif
