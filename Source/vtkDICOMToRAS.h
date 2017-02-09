/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2016 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*! \class vtkDICOMToRAS
 *  \brief Convert DICOM orientation to RAS orientation
 *
 *  This class will modify an image and its position-and-orientation matrix
 *  so that the patient coordinate system follows the conventions of NIFTI
 *  and MINC, i.e. the x, y, and z axes will point in the right, anterior,
 *  and superior directions respectively.  Optionally, the row and column
 *  ordering of the image will also be modified so that the row direction
 *  preferentially points right or anterior, and the column direction
 *  preferentially points superior or anterior.
 */

#ifndef vtkDICOMToRAS_h
#define vtkDICOMToRAS_h

#include <vtkThreadedImageAlgorithm.h>
#include "vtkDICOMModule.h" // For export macro

class vtkMatrix4x4;

//----------------------------------------------------------------------------
class VTKDICOM_EXPORT vtkDICOMToRAS : public vtkThreadedImageAlgorithm
{
public:
  //! Static method for construction.
  static vtkDICOMToRAS *New();
  vtkTypeMacro(vtkDICOMToRAS, vtkThreadedImageAlgorithm);

  //! Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

  //@{
  //! Perform RAS to DICOM instead of DICOM to RAS.
  void SetRASToDICOM(int v);
  void RASToDICOMOn() { this->SetRASToDICOM(1); }
  void RASToDICOMOff() { this->SetRASToDICOM(0); }
  int GetRASToDICOM() { return this->RASToDICOM; }
  //@}

  //@{
  //! Get a matrix to place the image within DICOM patient coords.
  /*!
   *  This matrix is constructed from the ImageOrientationPatient
   *  and ImagePositionPatient meta data attributes.  See the
   *  SetMemoryRowOrder method for additional information.
   */
  void SetPatientMatrix(vtkMatrix4x4 *matrix);
  vtkMatrix4x4 *GetPatientMatrix() { return this->PatientMatrix; }
  //@}

  //@{
  //! Get a matrix that follows the RAS convention that can be used
  /*!
   *  with the output image.  This matrix is only valid for the output
   *  image, it is not valid for the input image.
   */
  void SetRASMatrix(vtkMatrix4x4 *matrix);
  vtkMatrix4x4 *GetRASMatrix() { return this->RASMatrix; }
  //@}

  //@{
  //! Update the RAS matrix without updating the output data.
  /*!
   *  This requires that an input has been set, because the origin,
   *  spacing, and extent of the input data must be known in order
   *  to compute the matrix.
   */
  void UpdateMatrix();
  //@}

  //@{
  //! Specify whether the RAS matrix should include the position in its
  /*!
   *  final column (NIFTI style), or whether the final column should be
   *  zero and the position instead used to compute a new Origin for the
   *  output image.  If this option is On, then the Origin of the output
   *  image will be (0,0,0), and if it is Off, then the position stored
   *  the matrix will be (0,0,0).
   */
  void SetRASMatrixHasPosition(int v);
  void RASMatrixHasPositionOn() { this->SetRASMatrixHasPosition(1); }
  void RASMatrixHasPositionOff() { this->SetRASMatrixHasPosition(0); }
  int GetRASMatrixHasPosition() { return this->RASMatrixHasPosition; }
  //@}

  //@{
  //! Allow the columns to be reordered so that columns with higher indices
  /*!
   *  are further to the right or further anterior.  Note that if you turn
   *  this option on, then you are implicitly allowing slice reordering to
   *  occur as well.  If you turn both ColumnReordering and SliceReordering
   *  off, then the input data will be directly passed to the output.
   */
  void SetAllowColumnReordering(int v);
  void AllowColumnReorderingOn() { this->SetAllowColumnReordering(1); }
  void AllowColumnReorderingOff() { this->SetAllowColumnReordering(0); }
  int GetAllowColumnReordering() { return this->AllowColumnReordering; }
  //@}

  //@{
  //! Allow the rows to be reordered so that rows with higher indices
  /*!
   *  are further superior or further anterior.  Note that if you turn
   *  this option on, then you are implicitly allowing slice reordering to
   *  occur as well.  If you turn both ColumnReordering and SliceReordering
   *  off, then the input data will be directly passed to the output.
   */
  void SetAllowRowReordering(int v);
  void AllowRowReorderingOn() { this->SetAllowRowReordering(1); }
  void AllowRowReorderingOff() { this->SetAllowRowReordering(0); }
  int GetAllowRowReordering() { return this->AllowRowReordering; }
  //@}

protected:
  vtkDICOMToRAS();
  ~vtkDICOMToRAS();

  //! Check whether the data will be reordered in cols or rows.
  void CheckNeedToReorder();

  //! Compute the RAS matrix and store it in this->Matrix.
  /*!
   *  If extent doesn't start at zero, make it so that it does.
   *  Also change the origin if RASMatrixHasPosition is Off.
   */
  void ComputeMatrix(int extent[6], double spacing[3], double origin[3]);

  virtual int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  virtual int RequestUpdateExtent(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  virtual int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  virtual void ThreadedRequestData(
    vtkInformation *request, vtkInformationVector **inputVector,
    vtkInformationVector *outputVector, vtkImageData ***inData,
    vtkImageData **outData, int ext[6], int id) VTK_OVERRIDE;

  vtkMatrix4x4 *PatientMatrix;
  vtkMatrix4x4 *RASMatrix;

  int RASToDICOM;
  int AllowColumnReordering;
  int AllowRowReordering;
  int RASMatrixHasPosition;
  int ReorderColumns;
  int ReorderRows;
  double Matrix[16];

private:
  vtkDICOMToRAS(const vtkDICOMToRAS&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMToRAS&) VTK_DELETE_FUNCTION;
};

#endif // vtkDICOMToRAS_h
