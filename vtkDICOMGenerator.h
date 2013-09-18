/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMGenerator_h
#define __vtkDICOMGenerator_h

#include <vtkObject.h>
#include "vtkDICOMModule.h"

class vtkMatrix4x4;
class vtkInformation;
class vtkDICOMMetaData;

//! Generate DICOM data series for specific IOD classes.
/*!
 *  Every DICOM data set must conform to a specific class, where the
 *  properties of all the classes are defined in the DICOM standard.
 *  There are specific IOD classes for MR, CT, ultrasound X-ray, etc., in
 *  fact there are several dozen classes in total.  IOD is the acronym
 *  for Information Object Description, and refers to the attributes that
 *  a data set belonging to a particular IOD class can or must have.  The
 *  vtkDICOMGenerator is an abstract base class that provides support
 *  for most of the common modules in the DICOM standard (i.e. modules
 *  that are shared between modalities).  Subclasses of vtkDICOMGenerator
 *  are concrete classes that provide generation of data sets belonging
 *  to specific modalities.
 */
class VTK_DICOM_EXPORT vtkDICOMGenerator : public vtkObject
{
public:
  //! Static method for construction.
  vtkTypeMacro(vtkDICOMGenerator, vtkObject);

  //! Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  //! Generate an instance of one of the supported classes.
  /*!
   *  This is the primary interface method of this class.  Given the
   *  information for a vtkImageData object, it will populate the
   *  attributes of the supplied vtkDICOMMetaData object.
   */
  virtual bool GenerateInstance(
    vtkInformation *, vtkDICOMMetaData *) = 0;

  //! Create a multi-frame object (default: Off).
  /*!
   *  If this is on, the one multi-frame data set will be created.  If
   *  this is off, then each slice will be put into a different data set.
   *  The latter is more likely to be compatible with older software.
   */
  vtkGetMacro(MultiFrame, int);
  vtkSetMacro(MultiFrame, int);
  vtkBooleanMacro(MultiFrame, int);

  //! Write scalar components as the time dimension (default: Off).
  /*!
   *  If this is on, then each time slot is stored in a different scalar
   *  component of the image data.  If it is off, then each block of N
   *  adjacent slices correspond to the N time slots of the time dimension.
   */
  vtkGetMacro(TimeAsVector, int);
  vtkSetMacro(TimeAsVector, int);
  vtkBooleanMacro(TimeAsVector, int);

  //! Set the time dimension to use in the DICOM file (or zero if none).
  /*!
   *  The number of components of the input data must be divisible by the
   *  time dimension if the time dimension is not set to zero.  The vector
   *  dimension will be set to the number of components divided by the time
   *  dimension.  This will be ignored if the SOP Class IOD does not permit
   *  a time dimension.
   */
  vtkGetMacro(TimeDimension, int);
  vtkSetMacro(TimeDimension, int);
  vtkGetMacro(TimeSpacing, double);
  vtkSetMacro(TimeSpacing, double);

  //! Set the matrix that places the image in DICOM patient coords.
  /*!
   *  The 3x3 portion of the matrix must be orthonormal, and the
   *  last column of the matrix is understood to be in millimetres.
   */
  void SetPatientMatrix(vtkMatrix4x4 *);
  vtkMatrix4x4 *GetPatientMatrix() { return this->PatientMatrix; }

  //! Set some meta data for the constructor to use as a hint.
  /*!
   *  The supplied meta data can provide some general properties
   *  of the data set, such as the patient information and study
   *  information.  Only portions of the meta data that are permitted
   *  by the generated IOD will be included.
   */
  void SetMetaData(vtkDICOMMetaData *);
  vtkDICOMMetaData *GetMetaData();

protected:
  vtkDICOMGenerator();
  ~vtkDICOMGenerator();

  //! Generate the DICOM SOP Common Module.
  virtual bool GenerateSOPCommonModule(
    vtkDICOMMetaData *meta, const char *SOPClass);

  //! Generate the DICOM Patient Module.
  virtual bool GeneratePatientModule(vtkDICOMMetaData *meta);

  //! Generate the DICOM Study Module.
  virtual bool GenerateGeneralStudyModule(vtkDICOMMetaData *meta);

  //! Generate the DICOM Series Module.
  virtual bool GenerateGeneralSeriesModule(vtkDICOMMetaData *meta);

  //! Generate the DICOM Image Module.
  virtual bool GenerateGeneralImageModule(vtkDICOMMetaData *meta);

  //! Generate the DICOM Pixel Module.
  virtual bool GenerateImagePixelModule(
    vtkDICOMMetaData *meta, vtkInformation *info);

  //! Generate The DICOM Multi-frame Module.
  virtual bool GenerateMultiFrameModule(
    vtkDICOMMetaData *meta, vtkInformation *info);

  //! Generate The DICOM Multi-frame Functional Groups Module.
  virtual bool GenerateMultiFrameFunctionalGroupsModule(
    vtkDICOMMetaData *meta, vtkInformation *info);

  //! Compute aspect ratio from spacing.
  static void ComputeAspectRatio(const double spacing[2], int aspect[2]);

  //! Compute the position and orientation for a slice.
  /*!
   *  Given the origin of a slice (the position of the corner of the slice
   *  in VTK data coordinates), and a 4x4 matrix (which may be NULL), compute
   *  the ImagePositionPatient and the ImageOrientationPatient.
   */
  static void ComputePositionAndOrientation(
    const double origin[3], vtkMatrix4x4 *matrix,
    double position[3], double orientation[6]);

  //! Compute the dimensions.
  void ComputeDimensions(
    vtkInformation *info, int *nframes, int dims[5], double spacing[5]);

  //! The meta data.
  vtkDICOMMetaData *MetaData;

  //! Whether to prefer multi-frame files over single-frame.
  int MultiFrame;

  //! Whether time is stored in slices or in scalar components.
  int TimeAsVector;

  //! Time dimension to use in the file.
  int TimeDimension;
  double TimeSpacing;

  //! The orientation matrix for the DICOM file.
  vtkMatrix4x4 *PatientMatrix;

private:
  vtkDICOMGenerator(const vtkDICOMGenerator&);  // Not implemented.
  void operator=(const vtkDICOMGenerator&);  // Not implemented.
};

#endif // __vtkDICOMGenerator_h
