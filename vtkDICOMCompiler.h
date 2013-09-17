/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMCompiler_h
#define __vtkDICOMCompiler_h

#include <vtkObject.h>
#include "vtkDICOMModule.h"

class vtkStringArray;
class vtkDICOMMetaData;
class vtkDICOMCompilerInternalFriendship;

//! A writer for DICOM meta data.
/*!
 *  This class provides routines for compiling a vtkDICOMMetaData
 *  object into a DICOM file.
 */
class VTK_DICOM_EXPORT vtkDICOMCompiler : public vtkObject
{
public:
  //! Create a new vtkDICOMCompiler instance.
  static vtkDICOMCompiler *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMCompiler, vtkObject);

  //! Print a summary of the contents of this object.
  void PrintSelf(ostream& os, vtkIndent indent);

  //! Set the file name.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  //! Set the SOP Instance UID.
  /*!
   *  If you do not supply a UID, a random UID will be generated.
   *  Each DICOM file must have a globally unique UID.
   */
  vtkSetStringMacro(SOPInstanceUID);
  vtkGetStringMacro(SOPInstanceUID);

  //! Set the Series Instance UID.
  /*!
   *  If you do not supply a UID, a random UID will be generated.
   *  Each DICOM series must have a globally unique UID.
   */
  vtkSetStringMacro(SeriesInstanceUID);
  vtkGetStringMacro(SeriesInstanceUID);

  //! Set the Study Instance UID.
  /*!
   *  If you do not supply a UID, a random UID will be generated.
   *  Each DICOM study must have a globally unique UID.
   */
  vtkSetStringMacro(StudyInstanceUID);
  vtkGetStringMacro(StudyInstanceUID);

  //! Set the Implementation Class UID.
  /*!
   *  If you do not supply a UID, a default one will be used.
   */
  vtkSetStringMacro(ImplementationClassUID);
  vtkGetStringMacro(ImplementationClassUID);

  //! Set the Implementation Version Name.
  /*!
   *  If you do not supply a name, a default one will be used.
   */
  vtkSetStringMacro(ImplementationVersionName);
  vtkGetStringMacro(ImplementationVersionName);

  //! Set the Source Application Entity Title.
  /*!
   *  Provide a short name (16 chars max) for the network node that
   *  is running the implementation.  The name should have no spaces
   *  or punctuation and should consist only of letters and digits.
   */
  vtkSetStringMacro(SourceApplicationEntityTitle);
  vtkGetStringMacro(SourceApplicationEntityTitle);

  //! Set the Transfer Syntax UID.
  /*!
   *  The transfer syntax should be left at its default value of
   *  1.2.840.10008.1.2.1 (uncompressed little-endian with explicit VR)
   *  unless you are cloning the PixelData byte for byte from another
   *  image, in which case you should use the transfer syntax from that
   *  image.
   */
  vtkSetStringMacro(TransferSyntaxUID);
  vtkGetStringMacro(TransferSyntaxUID);

  //! Set the metadata object to write to the file.
  void SetMetaData(vtkDICOMMetaData *);
  vtkDICOMMetaData *GetMetaData() { return this->MetaData; }

  //! Set the instance index to use when accessing vtkDICOMMataData.
  vtkSetMacro(Index, int);
  int GetIndex() { return this->Index; }

  //! Set the buffer size, the default is 8192 (8k).
  /*!
   *  A larger buffer size results in fewer IO calls.  The
   *  minimum buffer size is 256 bytes.
   */
  void SetBufferSize(int size);
  int GetBufferSize() { return this->BufferSize; }

  //! Write the metadata to the file.
  virtual void WriteHeader();

  //! Write all of the pixel data in one go.
  /*!
   *  This method assumes that the supplied buffer is already in
   *  the correct format (endianness, compression, fragments, etc)
   *  and writes it out to the file as the PixelData value.
   */
  virtual void WritePixelData(const char *cp, vtkIdType size);

  //! Write one frame to the end of the file.
  virtual void WriteFrame(const char *cp, vtkIdType size);

  //! Close the file.
  virtual void Close();

  //! Get the IO error code.
  unsigned long GetErrorCode() { return this->ErrorCode; }

  //! Generate a series UID and instance UIDs for the meta data.
  /*!
   *  This will be called automatically whenever you provide a
   *  new meta data object for the compiler.  Note that new UIDs
   *  will not be generated if you have already provided them with
   *  SetSOPInstanceUID() and SetSeriesUID().
   */
  void GenerateSeriesUIDs();

  //! Use the original PixelData VR when writing pixel data element.
  /*!
   *  This is really only useful when cloning data sets.  It ensures
   *  that the written data uses the same VR as the original data.
   */
  vtkSetMacro(KeepOriginalPixelDataVR, int);
  vtkBooleanMacro(KeepOriginalPixelDataVR, int);
  vtkGetMacro(KeepOriginalPixelDataVR, int);

protected:
  vtkDICOMCompiler();
  ~vtkDICOMCompiler();

  //! Internal method for flushing the IO buffer.
  /*!
   *  This is an internal method that flushes the buffer to the file.
   *  The pointer cp markes the current position in the buffer, and
   *  ep marks the end of the buffer.  By checking ep-cp, subroutines
   *  can check how much space is left in the buffer and call FlushBuffer
   *  only when the buffer is nearly full.
   */
  virtual bool FlushBuffer(unsigned char* &cp, unsigned char* &ep);

  //! Report an error while compiling the file.
  virtual void CompileError(const char *message);

  //! Set the error code.
  void SetErrorCode(unsigned long e) { this->ErrorCode = e; }

  //! Generate the file from the provided metadata object.
  virtual bool WriteFile(vtkDICOMMetaData *data, int idx);

  //! Write just the meta header (group 0x0002).
  bool WriteMetaHeader(
    unsigned char* &cp, unsigned char* &ep,
    vtkDICOMMetaData *data, int idx);

  //! Write the meta data following the meta header.
  bool WriteMetaData(
    unsigned char* &cp, unsigned char* &ep,
    vtkDICOMMetaData *data, int idx);

  //! Compute the size of the pixel data (0xffffffff if compressed).
  unsigned int ComputePixelDataSize();

  char *FileName;
  char *SOPInstanceUID;
  char *SeriesInstanceUID;
  char *StudyInstanceUID;
  char *ImplementationClassUID;
  char *ImplementationVersionName;
  char *SourceApplicationEntityTitle;
  char *TransferSyntaxUID;
  vtkDICOMMetaData *MetaData;
  vtkStringArray *SeriesUIDs;
  std::ostream *OutputStream;
  char *Buffer;
  int BufferSize;
  int ChunkSize;
  int Index;
  int FrameCounter;
  int BigEndian;
  int Compressed;
  int KeepOriginalPixelDataVR;
  unsigned long ErrorCode;

  static char StudyUID[64];

  // used to share FlushBuffer with internal classes
  friend class vtkDICOMCompilerInternalFriendship;

private:
  vtkDICOMCompiler(const vtkDICOMCompiler&);  // Not implemented.
  void operator=(const vtkDICOMCompiler&);  // Not implemented.
};

#endif /* __vtkDICOMCompiler_h */
