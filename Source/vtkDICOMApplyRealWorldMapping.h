/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDICOMApplyRealWorldMapping - Convert pixels to real-world values.
// .SECTION Description
// This filter uses the information in the DICOM meta data to convert the
// pixel values to real-world values with known units.

#ifndef vtkDICOMApplyRealWorldMapping_h
#define vtkDICOMApplyRealWorldMapping_h

#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMModule.h"

class vtkDICOMRealWorldMapping;

class VTK_DICOM_EXPORT vtkDICOMApplyRealWorldMapping :
  public vtkDICOMAlgorithm
{
public:
  static vtkDICOMApplyRealWorldMapping *New();
  vtkTypeMacro(vtkDICOMApplyRealWorldMapping, vtkDICOMAlgorithm);

  // Description:
  // Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the output data type to float or double (default is double).
  void SetOutputScalarType(int t);
  void SetOutputScalarTypeToFloat() {
    this->SetOutputScalarType(VTK_FLOAT); }
  void SetOutputScalarTypeToDouble() {
    this->SetOutputScalarType(VTK_DOUBLE); }
  int GetOutputScalarType() {
    return this->OutputScalarType; }

protected:
  vtkDICOMApplyRealWorldMapping();
  ~vtkDICOMApplyRealWorldMapping();

  virtual int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  virtual int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  virtual void ThreadedRequestData(
    vtkInformation *request, vtkInformationVector **inputVector,
    vtkInformationVector *outputVector, vtkImageData ***inData,
    vtkImageData **outData, int ext[6], int id);

  vtkDICOMRealWorldMapping *Mapping;
  int OutputScalarType;

private:
  vtkDICOMApplyRealWorldMapping(const vtkDICOMApplyRealWorldMapping&);  // Not implemented.
  void operator=(const vtkDICOMApplyRealWorldMapping&);  // Not implemented.
};

#endif // vtkDICOMApplyRealWorldMapping_h
