/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMSCGenerator_h
#define __vtkDICOMSCGenerator_h

#include "vtkDICOMModule.h"
#include "vtkDICOMGenerator.h"

//! Generate DICOM data objects for Secondary Capture images.
/*!
 *  Generate a DICOM data set belonging to one of the Secondary Capture
 *  classes.  This is for images that were not directly captured by
 *  medical imaging equipment.  For example, a screen capture or a
 *  digital film scan should be considered to be a secondary capture.
 *  The specific IOD classes supported are as follows:
 *  - Secondary Capture, 1.2.840.10008.5.1.4.1.1.7
 *  - Multi-frame Grayscale Byte SC, 1.2.840.10008.5.1.4.1.1.7.2
 *  - Multi-frame Grayscale Word SC, 1.2.840.10008.5.1.4.1.1.7.3
 *  - Multi-frame True Color SC, 1.2.840.10008.5.1.4.1.1.7.4
 */
class VTK_DICOM_EXPORT vtkDICOMSCGenerator : public vtkDICOMGenerator
{
public:
  //! Static method for construction.
  static vtkDICOMSCGenerator *New();
  vtkTypeMacro(vtkDICOMSCGenerator, vtkDICOMGenerator);

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
  vtkDICOMSCGenerator();
  ~vtkDICOMSCGenerator();

  //! Generate the SC Equipment Module.
  virtual bool GenerateSCEquipmentModule(vtkDICOMMetaData *meta);

  //! Generate the SC Image Module.
  virtual bool GenerateSCImageModule(vtkDICOMMetaData *meta);

  //! Generate the SC Multi-Frame Image Module.
  virtual bool GenerateSCMultiFrameImageModule(vtkDICOMMetaData *meta);

  //! Instantiate a DICOM Secondary Capture Image object.
  virtual bool GenerateSCInstance(
    vtkInformation *info, vtkDICOMMetaData *meta);

  //! Instantiate a DICOM Secondary Capture Image object.
  virtual bool GenerateSCMultiFrameInstance(
    vtkInformation *info, vtkDICOMMetaData *meta);

private:
  vtkDICOMSCGenerator(const vtkDICOMSCGenerator&);  // Not implemented.
  void operator=(const vtkDICOMSCGenerator&);  // Not implemented.
};

#endif // __vtkDICOMSCGenerator_h
