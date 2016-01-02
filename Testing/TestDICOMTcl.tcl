package require vtk
package require vtkdicom

vtkDICOMMetaData meta
vtkDICOMReader reader
vtkDICOMWriter writer
writer SetInputConnection [reader GetOutputPort]

meta Delete
reader Delete
writer Delete

exit 0
