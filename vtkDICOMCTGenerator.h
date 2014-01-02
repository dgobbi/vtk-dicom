/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMCTGenerator_h
#define __vtkDICOMCTGenerator_h

#include "vtkDICOMModule.h"
#include "vtkDICOMGenerator.h"

//! Generate DICOM data objects for CT images.
/*!
 *  Generate a DICOM data set belonging to one of the CT SOP classes.
 *  The assumption is that images have been read into VTK as CT, and
 *  are being written out as derived images after being processed.
 *  The specific IOD classes supported are as follows:
 *  - CT Image, 1.2.840.10008.5.1.4.1.1.2
 */
class VTK_DICOM_EXPORT vtkDICOMCTGenerator : public vtkDICOMGenerator
{
public:
  //! Static method for construction.
  static vtkDICOMCTGenerator *New();
  vtkTypeMacro(vtkDICOMCTGenerator, vtkDICOMGenerator);

  //! Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  //! Generate an instance of one of the supported classes.
  /*!
   *  This is the primary interface method of this class.  Given the
   *  information for a vtkImageData object, it will populate the
   *  attributes of the supplied vtkDICOMMetaData object.
   */
  virtual bool GenerateInstance(
    vtkInformation *info, vtkDICOMMetaData *meta);

protected:
  vtkDICOMCTGenerator();
  ~vtkDICOMCTGenerator();

  //! Generate the Series Module.
  virtual bool GenerateCTSeriesModule(vtkDICOMMetaData *meta);

  //! Generate the Image Module.
  virtual bool GenerateCTImageModule(vtkDICOMMetaData *meta);

  //! Instantiate a DICOM Secondary Capture Image object.
  virtual bool GenerateCTInstance(
    vtkInformation *info, vtkDICOMMetaData *meta);

private:
  vtkDICOMCTGenerator(const vtkDICOMCTGenerator&);  // Not implemented.
  void operator=(const vtkDICOMCTGenerator&);  // Not implemented.
};

#endif // __vtkDICOMCTGenerator_h
