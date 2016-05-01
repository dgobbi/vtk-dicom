/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkConsoleOutputWindow.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkConsoleOutputWindow.h"

vtkConsoleOutputWindow *vtkConsoleOutputWindow::New()
{
  return new vtkConsoleOutputWindow;
}

vtkConsoleOutputWindow::vtkConsoleOutputWindow()
{
}

vtkConsoleOutputWindow::~vtkConsoleOutputWindow()
{
}

void vtkConsoleOutputWindow::Initialize()
{
}

void vtkConsoleOutputWindow::Install()
{
  vtkConsoleOutputWindow *win = vtkConsoleOutputWindow::New();
  vtkOutputWindow::SetInstance(win);
  win->Delete();
}

void vtkConsoleOutputWindow::DisplayText(const char* text)
{
  if (text)
    {
    fwrite(text, 1, strlen(text), stderr);
    fputc('\n', stderr);
    }
}

void vtkConsoleOutputWindow::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
