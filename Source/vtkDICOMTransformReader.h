/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDICOMTransformReader - Read DICOM spatial registration objects.
// .SECTION Description
// DICOM can store one or more spatial registrations within a DICOM
// Spatial Registration file.  Each registration is described as a
// transformation from either 1) a series of images, or 2) a set of
// fiducials, to the Frame of Reference defined in the file.
//
// In the case of an ordinary Spatial Registration file, each transformation
// can be a composite of more than one matrix.  These will automatically be
// concatenated for you, providing a single vtkTransform, but you can use
// the vtkTransform methods GetNumberOfConcatenatedTransforms() and
// GetConcatenatedTransform(i) to get the decomposition.
//
// In the case of a Deformable Spatial Registration file, the provided
// transformation will be a vtkGeneralTransform composite transformation
// object consisting of a vtkGridTransform, and a pre or post matrix
// (or both) stored as a vtkTransform.  The vtkGeneralTransform can be
// decomposed with the methods GetNumberOfConcatenatedTransforms() and
// GetConcatenatedTransform(i).

#ifndef vtkDICOMTransformReader_h
#define vtkDICOMTransformReader_h

#include "vtkAlgorithm.h"
#include "vtkDICOMModule.h"

class vtkAbstractTransform;
class vtkTransform;
class vtkDoubleArray;
class vtkStringArray;
class vtkCollection;
class vtkDICOMMetaData;

class VTKDICOM_EXPORT vtkDICOMTransformReader : public vtkAlgorithm
{
public:
  vtkTypeMacro(vtkDICOMTransformReader,vtkAlgorithm);

  static vtkDICOMTransformReader *New();
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the file name.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Get the entension for this file format.
  virtual const char* GetFileExtensions() {
    return ".dcm .sro"; }

  // Description:
  // Get the name of this file format.
  virtual const char* GetDescriptiveName() {
    return "DICOM Spatial Registration"; }

  // Description:
  // Test whether the specified file can be read.
  virtual int CanReadFile(const char* name);

  // Description:
  // Get the number of registrations stored in the file.
  // Usually there will only be one registration per file.
  virtual int GetNumberOfTransforms();

  // Description:
  // Get the transform from one of the registrations in the file.
  // For a Deformable Spatial Registration, this will return a
  // vtkGeneralTransform, and for a standard Spatial Registration,
  // this will return a vtkTransform.  For either, you can call the
  // GetNumberOfConcatenatedTransforms() method on the transform to
  // find out if it is a composite transform, and you can call
  // GetConcatenatedTransform(i) to decompose the transform.
  virtual vtkAbstractTransform *GetNthTransform(int i);

  // Description:
  // Get the transform that results from concatenating all of the
  // transforms in the file.  This will return null if you have not
  // specified a file name.
  virtual vtkAbstractTransform *GetTransform();

  // Description:
  // Get the meta data for the DICOM file.
  vtkDICOMMetaData *GetMetaData() { return this->MetaData; }

protected:
  vtkDICOMTransformReader();
  ~vtkDICOMTransformReader();

  char *FileName;
  vtkDICOMMetaData *MetaData;
  vtkAbstractTransform *Transform;
  vtkCollection *Transforms;

  virtual int ReadFile();

  void SetTransform(vtkAbstractTransform *transform);

  int CreateOutputTransform();

  virtual int ProcessRequest(vtkInformation* request,
                             vtkInformationVector** inInfo,
                             vtkInformationVector* outInfo);

  void RelayError(vtkObject *o, unsigned long e, void *data);

private:
  vtkDICOMTransformReader(const vtkDICOMTransformReader&); // Not implemented
  void operator=(const vtkDICOMTransformReader&);  // Not implemented
};

#endif
