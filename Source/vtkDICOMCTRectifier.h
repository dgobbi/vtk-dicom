/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*! \class vtkDICOMCTRectifier
 *  \brief Prepare a CT for 3D processing
 *
 *  This class will identify gantry-tilted CT images and resample them
 *  into a rectangular volume.  This is often a necessary step prior to
 *  volume rendering or other forms of 3D rendering.
 */

#ifndef vtkDICOMCTRectifier_h
#define vtkDICOMCTRectifier_h

#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMModule.h" // For export macro

class vtkMatrix4x4;

//----------------------------------------------------------------------------
class VTKDICOM_EXPORT vtkDICOMCTRectifier : public vtkDICOMAlgorithm
{
public:
  //! Static method for construction.
  static vtkDICOMCTRectifier *New();
  vtkTypeMacro(vtkDICOMCTRectifier, vtkDICOMAlgorithm);

  //! Print information about this object.
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
#endif

  //@{
  //! Reverse the default operation.
  /*!
   *  When this option is set, the filter takes a rectangular volume
   *  as input, and produces a volume whose geometry matches the
   *  VolumeMatrix.
   */
  void SetReverse(int v);
  void ReverseOn() { this->SetReverse(1); }
  void ReverseOff() { this->SetReverse(0); }
  int GetReverse() { return this->Reverse; }
  //@}

  //@{
  //! Set the matrix that describes the CT volume geometry.
  /*!
   *  This should be set to the PatientMatrix that comes from the
   *  vtkDICOMReader.
   */
  void SetVolumeMatrix(vtkMatrix4x4 *matrix);
  vtkMatrix4x4 *GetVolumeMatrix() { return this->VolumeMatrix; }
  //@}

  //@{
  //! Get the matrix that describes the rectified geometry.
  /*!
   *  This matrix is generated when any of these methods is called:
   *  Update(), UpdateInformation(), or UpdateMatrix().
   */
  vtkMatrix4x4 *GetRectifiedMatrix() { return this->RectifiedMatrix; }
  //@}

  //@{
  //! Update the RectifiedMatrix without updating the output data.
  /*!
   *  The input data must be set before this is called.
   */
  void UpdateMatrix();
  //@}

  //@{
  //! A static method to measure the tilt from a matrix.
  /*!
   *  This can be used to see whether it is necessary to rectify the
   *  volume.  It returns the Gantry Detector Tilt angle, in degrees,
   *  as computed from the shear in the volume matrix.
   */
  static double GetGantryDetectorTilt(vtkMatrix4x4 *volumeMatrix);
  //@}

protected:
  vtkDICOMCTRectifier();
  ~vtkDICOMCTRectifier();

  //! Compute the rectified matrix from the given volume matrix.
  /*!
   *  The extent, spacing, and origin of the image must also be given,
   *  and they will be adjusted as necessary.
   */
  void ComputeMatrix(
    const double matrix[16], const int extent[6], double spacing[3],
    double origin[3]);

#ifdef VTK_OVERRIDE
  int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  int RequestUpdateExtent(
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

  int RequestUpdateExtent(
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

  vtkMatrix4x4 *VolumeMatrix;
  vtkMatrix4x4 *RectifiedMatrix;
  vtkMatrix4x4 *Matrix;
  int Reverse;

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMCTRectifier(const vtkDICOMCTRectifier&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMCTRectifier&) VTK_DELETE_FUNCTION;
#else
  vtkDICOMCTRectifier(const vtkDICOMCTRectifier&);
  void operator=(const vtkDICOMCTRectifier&);
#endif
};

#endif // vtkDICOMCTRectifier_h
