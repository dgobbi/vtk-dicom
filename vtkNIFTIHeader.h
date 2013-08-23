/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkNIFTIHeader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkNIFTIHeader - Store NIfTI header information.
// .SECTION Description
// This class stores the header of a NIfTI file in a VTK-friendly format.
// By using this class, it is possible to specify the header information
// that will be stored in a file written by the vtkNIFTIWriter.  Note that
// the SForm and QForm orientation information in this class will be
// ignored by the writer if an SForm and QForm have been explicitly set
// via the writer's SetSForm and SetQForm methods.  Also note that all
// info like Dim, PixDim, DataType, etc. will be ignored by the writer
// because this information must instead be taken from the vtkImageData
// information.
// .SECTION Thanks
// This class was contributed to VTK by the Calgary Image Processing and
// Analysis Centre (CIPAC).
// .SECTION See Also
// vtkNIFTIReader, vtkNIFTIWriter

#ifndef __vtkNIFTIHeader_h
#define __vtkNIFTIHeader_h

#include <vtkObject.h>
#include "vtkDICOMModule.h"

struct nifti_1_header;

//----------------------------------------------------------------------------
class VTK_DICOM_EXPORT vtkNIFTIHeader : public vtkObject
{
public:
  // Description:
  // Static method for construction.
  static vtkNIFTIHeader *New();
  vtkTypeMacro(vtkNIFTIHeader, vtkObject);

  // Description:
  // Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the magic number for the NIFTI file as a null-terminated string.
  const char *GetMagic() { return this->Magic; }

  // Description:
  // Get the offset to the pixel data within the file.
  vtkIdType GetVoxOffset() { return this->VoxOffset; }

  // Description:
  // Get a null-terminated file descriptor, this usually gives the
  // name of the software that wrote the file. It will have a maximum
  // length of 80 characters.
  const char *GetDescrip() { return this->Descrip; }

  // Description:
  // Get the data type.
  int GetDataType() { return this->DataType; }

  // Description:
  // Get the number of bits per pixel.
  int GetBitPix() { return this->BitPix; }

  // Description:
  // Get the nth dimension of the data, where GetDim(0) returns the
  // number of dimensions that are defined for the file.
  int GetDim(int i) {
    return (i < 0 || i > 7 ? 0 : this->Dim[i]); }

  // Description:
  // Get the sample spacing in the nth dimension. If GetPixDim(0) is
  // negative, then the quaternion for the qform describes the correct
  // orientation only after the slice ordering has been reversed.
  double GetPixDim(int i) {
    return (i < 0 || i > 7 ? 0.0 : this->PixDim[i]); }

  // Description:
  // Get the NIFTI intent code.  This is an enumerated value in the NIFTI
  // header that states what the data is intended to be used for.
  vtkSetMacro(IntentCode, int);
  int GetIntentCode() { return this->IntentCode; }

  // Description:
  // Get the intent name.  This should match the intent code.
  void SetIntentName(const char *name);
  const char *GetIntentName() { return this->IntentName; }

  // Description:
  // Get one of the NIFTI intent parameters.  The definition of these
  // parameters varies according to the IntentCode.
  vtkSetMacro(IntentP1, double);
  double GetIntentP1() { return this->IntentP1; }
  vtkSetMacro(IntentP2, double);
  double GetIntentP2() { return this->IntentP2; }
  vtkSetMacro(IntentP3, double);
  double GetIntentP3() { return this->IntentP3; }

  // Description:
  // Get the scale and slope to apply to the data in order to get
  // the real-valued data values.
  vtkSetMacro(SclSlope, double);
  double GetSclSlope() { return this->SclSlope; }
  vtkSetMacro(SclInter, double);
  double GetSclInter() { return this->SclInter; }

  // Description:
  // Get the calibrated range of the data, i.e. the values stored in the
  // cal_min and cal_max fields in the header.
  vtkSetMacro(CalMin, double);
  double GetCalMin() { return this->CalMin; }
  vtkSetMacro(CalMax, double);
  double GetCalMax() { return this->CalMax; }

  // Description:
  // Get the slice_duration and toffset from the header.
  vtkSetMacro(SliceDuration, double);
  double GetSliceDuration() { return this->SliceDuration; }
  vtkSetMacro(TOffset, double);
  double GetTOffset() { return this->TOffset; }

  // Description:
  // Get the slice range for the data.
  vtkSetMacro(SliceStart, int);
  int GetSliceStart() { return this->SliceStart; }
  vtkSetMacro(SliceEnd, int);
  int GetSliceEnd() { return this->SliceEnd; }

  // Description:
  // Get the slice code for the data.
  vtkSetMacro(SliceCode, int);
  int GetSliceCode() { return this->SliceCode; }

  // Description:
  // Get a bitfield that describes the units for the first 4 dims.
  vtkSetMacro(XYZTUnits, int);
  int GetXYZTUnits() { return this->XYZTUnits; }

  // Description:
  // Get a bitfield with extra information about the dimensions, it
  // states which dimensions are the phase encode, frequency encode,
  // and slice encode dimensions for MRI acquisitions.
  vtkSetMacro(DimInfo, int);
  int GetDimInfo() { return this->DimInfo; }

  // Description:
  // Get an auxilliary file, e.g. a color table, that is associated
  // with this data.  The length of the filename must be a maximum of
  // 24 characters, and it will be assumed to be in the same directory
  // as the NIFTI file.
  void SetAuxFile(const char *auxfile);
  const char *GetAuxFile() { return this->AuxFile; }

  // Description:
  // Get the QForm or SForm code.
  vtkSetMacro(QFormCode, int);
  int GetQFormCode() { return this->QFormCode; }
  vtkSetMacro(SFormCode, int);
  int GetSFormCode() { return this->SFormCode; }

  // Description:
  // Get information about the quaternion transformation.  Note that
  // the vtkNIFTIWriter ignores this part of the header if a quaternion
  // has been set via vtkNIFTIWriter::SetQFormMatrix().
  vtkSetMacro(QuaternB, double);
  double GetQuaternB() { return this->QuaternB; }
  vtkSetMacro(QuaternC, double);
  double GetQuaternC() { return this->QuaternC; }
  vtkSetMacro(QuaternD, double);
  double GetQuaternD() { return this->QuaternD; }
  vtkSetMacro(QOffsetX, double);
  double GetQOffsetX() { return this->QOffsetX; }
  vtkSetMacro(QOffsetY, double);
  double GetQOffsetY() { return this->QOffsetY; }
  vtkSetMacro(QOffsetZ, double);
  double GetQOffsetZ() { return this->QOffsetZ; }

  // Description:
  // Get information about the matrix transformation.  Note that
  // the vtkNIFTIWriter ignores this part of the header if a matrix
  // has been set via vtkNIFTIWriter::SetSFormMatrix().
  vtkSetVector4Macro(SRowX, double);
  vtkGetVector4Macro(SRowX, double);
  vtkSetVector4Macro(SRowY, double);
  vtkGetVector4Macro(SRowY, double);
  vtkSetVector4Macro(SRowZ, double);
  vtkGetVector4Macro(SRowZ, double);

  // Description:
  // Initialize the header to default values.
  void Initialize();

  // Description:
  // Make a copy of the header.
  void DeepCopy(vtkNIFTIHeader *o);

  // Description:
  // Set the values from an existing nifti_1_header struct, or store
  // the values in an existing nifti_1_header struct.
  void SetHeader(const nifti_1_header *hdr);
  void GetHeader(nifti_1_header *hdr);

protected:
  vtkNIFTIHeader();
  ~vtkNIFTIHeader();

  char Magic[12];
  vtkIdType VoxOffset;
  int DataType;
  int BitPix;
  int Dim[8];
  double PixDim[8];
  int IntentCode;
  char IntentName[18];
  double IntentP1;
  double IntentP2;
  double IntentP3;
  double SclSlope;
  double SclInter;
  double CalMin;
  double CalMax;
  double SliceDuration;
  double TOffset;
  int SliceStart;
  int SliceEnd;
  int SliceCode;
  int XYZTUnits;
  int DimInfo;
  char Descrip[82];
  char AuxFile[26];
  int QFormCode;
  int SFormCode;
  double QuaternB;
  double QuaternC;
  double QuaternD;
  double QOffsetX;
  double QOffsetY;
  double QOffsetZ;
  double SRowX[4];
  double SRowY[4];
  double SRowZ[4];

  void SetStringValue(char *x, const char *y, size_t n);

private:
  vtkNIFTIHeader(const vtkNIFTIHeader&);  // Not implemented.
  void operator=(const vtkNIFTIHeader&);  // Not implemented.
};

#endif // __vtkNIFTIHeader_h
