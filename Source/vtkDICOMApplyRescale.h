/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDICOMApplyRescale - Convert pixels to real-world values.
// .SECTION Description
// This filter uses the information in the DICOM meta data to convert the
// pixel values to real-world values with known units.  It uses the DICOM
// RealWorldValueMapping attributes, if present, otherwise it uses the
// RescaleSlope and RescaleIntercept.  If no mapping information is present,
// then the pixels are simply converted to floating-point.  Note that if
// this filter is used, then AutoRescaleOff() should be set on the reader
// to ensure that the reader does not rescale the data.

#ifndef vtkDICOMApplyRescale_h
#define vtkDICOMApplyRescale_h

#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMModule.h"

class vtkDICOMRealWorldMapping;

class VTKDICOM_EXPORT vtkDICOMApplyRescale :
  public vtkDICOMAlgorithm
{
public:
  static vtkDICOMApplyRescale *New();
  vtkTypeMacro(vtkDICOMApplyRescale, vtkDICOMAlgorithm);

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
  vtkDICOMApplyRescale();
  ~vtkDICOMApplyRescale();

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
  vtkDICOMApplyRescale(const vtkDICOMApplyRescale&);  // Not implemented.
  void operator=(const vtkDICOMApplyRescale&);  // Not implemented.
};

#endif // vtkDICOMApplyRescale_h
