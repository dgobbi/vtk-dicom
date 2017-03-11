/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
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
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
#endif
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
  ~vtkDICOMSorter();

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMSorter(const vtkDICOMSorter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMSorter&) VTK_DELETE_FUNCTION;
#else
  vtkDICOMSorter(const vtkDICOMSorter&);
  void operator=(const vtkDICOMSorter&);
#endif
};

#endif
