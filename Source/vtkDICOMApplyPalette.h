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
// If an image contains a palette LUT, then this filter will apply that
// LUT to the image and produce an RGB image.  Images without a palette
// LUT will pass through unchanged.  If the image uses a supplemental
// palette that only applies to a specific range of pixel values, then
// pixel values outside of that range will be mapped to greyscale via
// the WindowWidth and WindowCenter specified in the image.

#ifndef vtkDICOMApplyPalette_h
#define vtkDICOMApplyPalette_h

#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMModule.h" // For export macro

class vtkDICOMMetaData;
class vtkDICOMPerFilePalette;

//----------------------------------------------------------------------------
class VTKDICOM_EXPORT vtkDICOMApplyPalette : public vtkDICOMAlgorithm
{
public:
  // Description:
  // Static method for construction.
  static vtkDICOMApplyPalette *New();
  vtkTypeMacro(vtkDICOMApplyPalette, vtkDICOMAlgorithm);

  // Description:
  // Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

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

  // Description:
  // True if palette is supplemental.
  bool IsSupplemental;

private:
  vtkDICOMApplyPalette(const vtkDICOMApplyPalette&);  // Not implemented.
  void operator=(const vtkDICOMApplyPalette&);  // Not implemented.
};

#endif // vtkDICOMApplyPalette_h
