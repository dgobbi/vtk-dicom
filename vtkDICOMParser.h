/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMParser_h
#define __vtkDICOMParser_h

#include <vtkObject.h>
#include "vtkDICOMModule.h"

#include <string>

class vtkDICOMMetaData;
class vtkUnsignedShortArray;
class vtkDICOMParserInternalFriendship;

//! A meta data reader for DICOM data.
/*!
 *  This class provides routines for parsing a DICOM file
 *  and creating a vtkDICOMMetaData object.
 */
class VTK_DICOM_EXPORT vtkDICOMParser : public vtkObject
{
public:
  //! Create a new vtkDICOMParser instance.
  static vtkDICOMParser *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMParser, vtkObject);

  //! Print a summary of the contents of this object.
  void PrintSelf(ostream& os, vtkIndent indent);

  //! Set the file name.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  //! Set the metadata object for storing the data elements.
  void SetMetaData(vtkDICOMMetaData *);
  vtkDICOMMetaData *GetMetaData() { return this->MetaData; }

  //! Set the instance index to use when storing metadata.
  vtkSetMacro(Index, int);
  int GetIndex() { return this->Index; }

  //! Set specific metadata groups to read.
  /*!
   *  If group 0x0002 is present in the file, it will always be read.
   */
  void SetGroups(vtkUnsignedShortArray *groups);
  vtkUnsignedShortArray *GetGroups() { return this->Groups; }

  //! This is true only if PixelData was found in the file.
  bool GetPixelDataFound() { return this->PixelDataFound; }

  //! Get the byte offset to the end of the metadata.
  /*!
   *  After the metadata has been read, the file offset
   *  will be set to the position of the pixel data.
   */
  vtkTypeInt64 GetFileOffset() { return this->FileOffset; }

  //! Get the total file length (only valid after Update).
  vtkTypeInt64 GetFileSize() { return this->FileSize; }

  //! Set the buffer size, the default is 8192 (8k).
  /*!
   *  A larger buffer size results in fewer IO calls.  The
   *  minimum buffer size is 256 bytes.
   */
  void SetBufferSize(int size);
  int GetBufferSize() { return this->BufferSize; }

  //! Read the metadata from the file.
  virtual void Update();

  //! Get the error code.
  unsigned long GetErrorCode() { return this->ErrorCode; }

protected:
  vtkDICOMParser();
  ~vtkDICOMParser();

  //! Internal method for filling the buffer.
  /*!
   *  This is an internal method that refills the buffer
   *  by reading data from the file.  The pointers cp and
   *  ep mark the region of the buffer that has not been
   *  parsed yet.  The call to FillBuffer will move this
   *  region to the beginning of the buffer, and will then
   *  fill the remainder of the buffer with new data from
   *  the file.  The values of cp and ep will be set to the
   *  beginning and end of the buffer.
   */
  virtual bool FillBuffer(
    const unsigned char* &cp, const unsigned char* &ep);

  //! Get the bytes remaining in the file.
  virtual std::streamsize GetBytesRemaining(
    const unsigned char *cp, const unsigned char *ep);

  //! Report an error while parsing the file.
  virtual void ParseError(
    const unsigned char *cp, const unsigned char *ep, const char *message);

  //! Set the error code.
  void SetErrorCode(unsigned long e) { this->ErrorCode = e; }

  //! Read the file into the provided metadata object.
  virtual bool ReadFile(vtkDICOMMetaData *data, int idx);

  //! Read just the meta header (group 0x0002).
  bool ReadMetaHeader(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMMetaData *data, int idx);

  //! Read the meta data following the meta header.
  bool ReadMetaData(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMMetaData *data, int idx);

  //! Compute the file offset to the current position.
  void ComputeFileOffset(
    const unsigned char* cp, const unsigned char* ep);

  char *FileName;
  std::string TransferSyntax;
  vtkDICOMMetaData *MetaData;
  vtkUnsignedShortArray *Groups;
  std::istream *InputStream;
  std::streamsize BytesRead;
  vtkTypeInt64 FileOffset;
  vtkTypeInt64 FileSize;
  char *Buffer;
  int BufferSize;
  int ChunkSize;
  int Index;
  unsigned long ErrorCode;
  bool PixelDataFound;

  // used to share FillBuffer with internal classes
  friend class vtkDICOMParserInternalFriendship;

private:
  vtkDICOMParser(const vtkDICOMParser&);  // Not implemented.
  void operator=(const vtkDICOMParser&);  // Not implemented.
};

#endif /* __vtkDICOMParser_h */
