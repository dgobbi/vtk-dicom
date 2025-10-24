/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "progress.h"

#include "vtkDICOMUtilities.h"

void ProgressObserver::Execute(vtkObject *, unsigned long e, void *vp)
{
  const double initial = 2.0; // time until first report
  const double delta = 0.1; // time between reports
  double t = 1e-6*vtkDICOMUtilities::GetUTC(nullptr);

  if (e == vtkCommand::StartEvent)
  {
    this->LastTime = t;
    this->Stage = 0;
    this->Anim = 0;
  }
  else if (e == vtkCommand::ProgressEvent)
  {
    double *dp = static_cast<double *>(vp);
    int progress = static_cast<int>((*dp)*100.0 + 0.5);

    if (this->Stage == 0)
    {
      if (t - this->LastTime > initial)
      {
        std::cout << "\r                                   ";
        this->Stage = 1;
      }
    }
    if (t - this->LastTime > delta)
    {
      if (this->Stage == 1)
      {
        if (progress == 0)
        {
          const char *dots[] = { ".  ", ".. ", "..." };
          this->Anim = (this->Anim + 1) % 3;
          std::cout << "\r" << this->Text << dots[this->Anim];
          std::cout.flush();
          this->LastTime = t;
        }
        else
        {
          std::cout << "\r" << this->Text << " " << progress << "%";
          std::cout.flush();
          this->LastTime = t;
        }
      }
    }
  }
  else if (e == vtkCommand::EndEvent)
  {
    if (this->Stage > 0)
    {
      std::cout << "\r" << this->Text << " 100%";
      std::cout << std::endl;
    }
  }
}
