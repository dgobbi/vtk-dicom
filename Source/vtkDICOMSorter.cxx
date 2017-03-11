/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMSorter.h"
#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkDICOMSorter);

//----------------------------------------------------------------------------
vtkDICOMSorter::vtkDICOMSorter()
{
}

//----------------------------------------------------------------------------
vtkDICOMSorter::~vtkDICOMSorter()
{
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
int vtkDICOMSorter::GetFirstSeriesInStudy(int study)
{
  return this->GetFirstSeriesForStudy(study);
}

//----------------------------------------------------------------------------
int vtkDICOMSorter::GetNumberOfSeriesInStudy(int study)
{
  return (this->GetLastSeriesForStudy(study) -
          this->GetFirstSeriesForStudy(study) + 1);
}
