/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkConsoleOutputWindow.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkConsoleOutputWindow - Output errors to the console.
// .SECTION Description
// Writes debug/warning/error output to the console, even on Windows.
// To use this class, instantiate it and then call SetInstance(this).
//

#ifndef vtkConsoleOutputWindow_h
#define vtkConsoleOutputWindow_h

#include "vtkOutputWindow.h"

class vtkConsoleOutputWindow : public vtkOutputWindow
{
public:
  vtkTypeMacro(vtkConsoleOutputWindow, vtkOutputWindow);
  static vtkConsoleOutputWindow* New();
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
  void DisplayText(const char*) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
  void DisplayText(const char*);
#endif
  static void Install();

protected:
  vtkConsoleOutputWindow();
  virtual ~vtkConsoleOutputWindow();
  void Initialize();

private:
#ifdef VTK_DELETE_FUNCTION
  vtkConsoleOutputWindow(const vtkConsoleOutputWindow&) VTK_DELETE_FUNCTION;
  void operator=(const vtkConsoleOutputWindow&) VTK_DELETE_FUNCTION;
#else
  vtkConsoleOutputWindow(const vtkConsoleOutputWindow&);
  void operator=(const vtkConsoleOutputWindow&);
#endif
};

#endif
