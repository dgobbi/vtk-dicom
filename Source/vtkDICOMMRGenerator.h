/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMMRGenerator_h
#define vtkDICOMMRGenerator_h

#include "vtkDICOMGenerator.h"
#include "vtkDICOMModule.h" // For export macro

//! Generate DICOM data objects for MR images.
/*!
 *  Generate a DICOM data set belonging to one of the MR SOP classes.
 *  The assumption is that images have been read into VTK as MR, and
 *  are being written out as derived images after being processed.
 *  The specific IOD classes supported are as follows:
 *  - MR Image, 1.2.840.10008.5.1.4.1.1.4
 */
class VTKDICOM_EXPORT vtkDICOMMRGenerator : public vtkDICOMGenerator
{
public:
  //! Static method for construction.
  static vtkDICOMMRGenerator *New();
  vtkTypeMacro(vtkDICOMMRGenerator, vtkDICOMGenerator);

  //! Print information about this object.
  void PrintSelf(ostream& os, vtkIndent indent) VTK_DICOM_OVERRIDE;

  //! Generate an instance of one of the supported classes.
  /*!
   *  This is the primary interface method of this class.  Given the
   *  information for a vtkImageData object, it will populate the
   *  attributes of the supplied vtkDICOMMetaData object.
   */
  bool GenerateInstance(vtkInformation *info) VTK_DICOM_OVERRIDE;

protected:
  vtkDICOMMRGenerator();
  ~vtkDICOMMRGenerator();

  //! Generate the Series Module.
  virtual bool GenerateMRSeriesModule(vtkDICOMMetaData *source);

  //! Generate the Image Module.
  virtual bool GenerateMRImageModule(vtkDICOMMetaData *source);

  //! Instantiate a DICOM Secondary Capture Image object.
  virtual bool GenerateMRInstance(vtkInformation *info);

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMMRGenerator(const vtkDICOMMRGenerator&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMMRGenerator&) VTK_DELETE_FUNCTION;
#elif __cplusplus >= 201103L
  vtkDICOMMRGenerator(const vtkDICOMMRGenerator&) = delete;
  void operator=(const vtkDICOMMRGenerator&) = delete;
#else
  vtkDICOMMRGenerator(const vtkDICOMMRGenerator&);
  void operator=(const vtkDICOMMRGenerator&);
#endif
};

#endif // vtkDICOMMRGenerator_h
