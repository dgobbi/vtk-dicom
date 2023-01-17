#! /usr/bin/env python2

import sys
import vtk

try:
    import vtkdicom
except ImportError:
    # for backwards compabilitity, before VTK 9
    import vtkDICOMPython as vtkdicom

m = vtkdicom.vtkDICOMMetaData()

if vtk.vtkVersion.GetVTKMajorVersion() < 6:
    sys.stderr.write("This test requires VTK 6 or higher.\n");
    sys.exit(0)

m.Set(vtkdicom.vtkDICOMTag(0x0008, 0x0005), 'ISO_IR 100')

v = m.Get(vtkdicom.vtkDICOMTag(0x0008, 0x0005))

if v.AsString() != 'ISO_IR 100':
    sys.exit(1)
