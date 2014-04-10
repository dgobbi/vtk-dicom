#! /usr/bin/env python2

import sys
import vtk
import vtkDICOMPython

# put everything into the vtk namespace
for a in dir(vtkDICOMPython):
    if a[0] != '_':
        setattr(vtk, a, getattr(vtkDICOMPython, a))

m = vtk.vtkDICOMMetaData()

if vtk.vtkVersion.GetVTKMajorVersion() < 6:
    sys.stderr.write("This test requires VTK 6 or higher.\n");
    sys.exit(0)

m.SetAttributeValue(vtk.vtkDICOMTag(0x0008, 0x0005), 'ISO_IR 100')

v = m.GetAttributeValue(vtk.vtkDICOMTag(0x0008, 0x0005))

if v.AsString() != 'ISO_IR 100':
    sys.exit(1)
