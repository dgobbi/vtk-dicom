/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMCTGenerator_h
#define vtkDICOMCTGenerator_h

#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMGenerator.h"

//! Generate DICOM data objects for CT images.
/*!
 *  Generate a DICOM data set belonging to one of the CT SOP classes.
 *  The assumption is that images have been read into VTK as CT, and
 *  are being written out as derived images after being processed.
 *  The specific IOD classes supported are as follows:
 *  - CT Image, 1.2.840.10008.5.1.4.1.1.2
 */
class VTKDICOM_EXPORT vtkDICOMCTGenerator : public vtkDICOMGenerator
{
public:
  //! Static method for construction.
  static vtkDICOMCTGenerator *New();
  vtkTypeMacro(vtkDICOMCTGenerator, vtkDICOMGenerator);

  //! Print information about this object.
  void PrintSelf(ostream& os, vtkIndent indent) override;

  //! Generate an instance of one of the supported classes.
  /*!
   *  This is the primary interface method of this class.  Given the
   *  information for a vtkImageData object, it will populate the
   *  attributes of the supplied vtkDICOMMetaData object.
   */
  bool GenerateInstance(vtkInformation *info) override;

protected:
  vtkDICOMCTGenerator();
  ~vtkDICOMCTGenerator() override;

  //! Generate the Series Module.
  virtual bool GenerateCTSeriesModule(vtkDICOMMetaData *source);

  //! Generate the Image Module.
  virtual bool GenerateCTImageModule(vtkDICOMMetaData *source);

  //! Instantiate a DICOM Secondary Capture Image object.
  virtual bool GenerateCTInstance(vtkInformation *info);

private:
  vtkDICOMCTGenerator(const vtkDICOMCTGenerator&) = delete;
  void operator=(const vtkDICOMCTGenerator&) = delete;
};

#endif // vtkDICOMCTGenerator_h
// VTK-HeaderTest-Exclude: ABINAMESPACE
