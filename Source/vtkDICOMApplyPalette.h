/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDICOMApplyPalette - Apply palette to PALETTE_COLOR images
// .SECTION Description

#ifndef vtkDICOMApplyPalette_h
#define vtkDICOMApplyPalette_h

#include <vtkThreadedImageAlgorithm.h>
#include "vtkDICOMModule.h"

class vtkLookupTable;
class vtkDICOMMetaData;
class vtkDICOMPerFilePalette;

//----------------------------------------------------------------------------
class VTK_DICOM_EXPORT vtkDICOMApplyPalette
  : public vtkThreadedImageAlgorithm
{
public:
  // Description:
  // Static method for construction.
  static vtkDICOMApplyPalette *New();
  vtkTypeMacro(vtkDICOMApplyPalette, vtkThreadedImageAlgorithm);

  // Description:
  // Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Generate the lookup table for the specified image in the series.
  // Usually, it will be the same for all images.
  static void FillLookupTable(
    vtkDICOMMetaData *meta, int fileIndex, vtkLookupTable *table);

protected:
  vtkDICOMApplyPalette();
  ~vtkDICOMApplyPalette();

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

  // Description:
  // Container for the lookup tables used.
  vtkDICOMPerFilePalette *Palette;

private:
  vtkDICOMApplyPalette(const vtkDICOMApplyPalette&);  // Not implemented.
  void operator=(const vtkDICOMApplyPalette&);  // Not implemented.
};

#endif // vtkDICOMApplyPalette_h
