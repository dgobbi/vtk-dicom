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

class vtkDICOMMetaData;
class vtkDICOMCompilerInternalFriendship;

//! A writer for DICOM meta data.
/*!
 *  This class provides routines for compiling a a vtkDICOMMetaData
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
   *  and writes it out to the file as a PixelData element.
   */
  virtual void WritePixelData(const char *cp, vtkIdType size);

  //! Write one frame.
  virtual void WriteFrame(const char *cp, vtkIdType size);

  //! Close the file.
  virtual void Close();

  //! Get the IO error code.
  unsigned long GetErrorCode() { return this->ErrorCode; }

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

  //! Write the pixel data head (0x7FE0,0x0010)
  bool WritePixelDataHead();

  //! Compute the size of the pixel data (0xffffffff if compressed).
  unsigned int ComputePixelDataSize();

  char *FileName;
  std::string TransferSyntax;
  vtkDICOMMetaData *MetaData;
  std::ostream *OutputStream;
  char *Buffer;
  int BufferSize;
  int ChunkSize;
  int Index;
  int FrameCounter;
  int Compressed;
  int KeepOriginalPixelDataVR;
  unsigned long ErrorCode;

  // used to share FlushBuffer with internal classes
  friend class vtkDICOMCompilerInternalFriendship;

private:
  vtkDICOMCompiler(const vtkDICOMCompiler&);  // Not implemented.
  void operator=(const vtkDICOMCompiler&);  // Not implemented.
};

#endif /* __vtkDICOMCompiler_h */
