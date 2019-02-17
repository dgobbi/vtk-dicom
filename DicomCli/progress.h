/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef progress_h
#define progress_h

#include "vtkCommand.h"
#include "vtkDICOMConfig.h"

// Capture progress events
class ProgressObserver : public vtkCommand
{
public:
  static ProgressObserver *New() { return new ProgressObserver; }
  vtkTypeMacro(ProgressObserver,vtkCommand);
  void Execute(
    vtkObject *caller, unsigned long eventId, void *callData)
    VTK_DICOM_OVERRIDE;
  void SetText(const char *text) { this->Text = text; }
protected:
  ProgressObserver() : Stage(0), Anim(0), LastTime(0), Text("") {}
  ProgressObserver(const ProgressObserver& c) : vtkCommand(c) {}
  void operator=(const ProgressObserver&) {}
  int Stage;
  int Anim;
  double LastTime;
  const char *Text;
};

#endif /* progress_h */
