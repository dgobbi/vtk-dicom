/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * \class vtkDICOMApplyRescale
 * \brief Convert pixels to real-world values.
 *
 * This filter uses the information in the DICOM meta data to convert the
 * pixel values to real-world values with known units.  It uses the DICOM
 * RealWorldValueMapping attributes, if present, otherwise it uses the
 * RescaleSlope and RescaleIntercept.  If no mapping information is present,
 * then the pixels are simply converted to floating-point.
 *
 * \warning If this filter is used, then AutoRescaleOff() should be set on
 * the reader to ensure that the reader does not rescale the data.
 */

#ifndef vtkDICOMApplyRescale_h
#define vtkDICOMApplyRescale_h

#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMModule.h" // For export macro

class vtkDICOMRealWorldMapping;

class VTKDICOM_EXPORT vtkDICOMApplyRescale :
  public vtkDICOMAlgorithm
{
public:
  vtkTypeMacro(vtkDICOMApplyRescale, vtkDICOMAlgorithm);

  //! Static method for construction.
  static vtkDICOMApplyRescale *New();

  //! Print information about this object.
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
#endif

  //@{
  //! Set the output data type to float or double (default is double).
  void SetOutputScalarType(int t);
  void SetOutputScalarTypeToFloat() {
    this->SetOutputScalarType(VTK_FLOAT); }
  void SetOutputScalarTypeToDouble() {
    this->SetOutputScalarType(VTK_DOUBLE); }
  int GetOutputScalarType() {
    return this->OutputScalarType; }
  //@}

protected:
  vtkDICOMApplyRescale();
  ~vtkDICOMApplyRescale();

#ifdef VTK_OVERRIDE
  int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  void ThreadedRequestData(
    vtkInformation *request, vtkInformationVector **inputVector,
    vtkInformationVector *outputVector, vtkImageData ***inData,
    vtkImageData **outData, int ext[6], int id) VTK_OVERRIDE;
#else
  int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  void ThreadedRequestData(
    vtkInformation *request, vtkInformationVector **inputVector,
    vtkInformationVector *outputVector, vtkImageData ***inData,
    vtkImageData **outData, int ext[6], int id);
#endif

  vtkDICOMRealWorldMapping *Mapping;
  int OutputScalarType;

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMApplyRescale(const vtkDICOMApplyRescale&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMApplyRescale&) VTK_DELETE_FUNCTION;
#elif __cplusplus >= 201103L
  vtkDICOMApplyRescale(const vtkDICOMApplyRescale&) = delete;
  void operator=(const vtkDICOMApplyRescale&) = delete;
#else
  vtkDICOMApplyRescale(const vtkDICOMApplyRescale&);
  void operator=(const vtkDICOMApplyRescale&);
#endif
};

#endif // vtkDICOMApplyRescale_h
