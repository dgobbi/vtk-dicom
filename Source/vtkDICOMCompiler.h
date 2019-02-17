/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMCompiler_h
#define vtkDICOMCompiler_h

#include "vtkObject.h"
#include "vtkDICOMModule.h" // For export macro


class vtkStringArray;
class vtkDICOMFile;
class vtkDICOMMetaData;
class vtkDICOMCompilerInternalFriendship;

//! A writer for DICOM meta data.
/*!
 *  This class provides routines for compiling a vtkDICOMMetaData
 *  object into a DICOM file.
 */
class VTKDICOM_EXPORT vtkDICOMCompiler : public vtkObject
{
public:
  //! Create a new vtkDICOMCompiler instance.
  static vtkDICOMCompiler *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMCompiler, vtkObject);

  //! Print a summary of the contents of this object.
  void PrintSelf(ostream& os, vtkIndent indent) VTK_DICOM_OVERRIDE;

  //@{
  //! Set the file name.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);
  //@}

  //@{
  //! Set the SOP Instance UID.
  /*!
   *  If you do not supply a UID, a random UID will be generated.
   *  Each DICOM file must have a globally unique UID.
   */
  vtkSetStringMacro(SOPInstanceUID);
  vtkGetStringMacro(SOPInstanceUID);
  //@}

  //@{
  //! Set the Series Instance UID.
  /*!
   *  If you do not supply a UID, a random UID will be generated.
   *  Each DICOM series must have a globally unique UID.
   */
  vtkSetStringMacro(SeriesInstanceUID);
  vtkGetStringMacro(SeriesInstanceUID);
  //@}

  //@{
  //! Set the Study Instance UID.
  /*!
   *  If you do not supply a UID, a random UID will be generated.
   *  Each DICOM study must have a globally unique UID.
   */
  vtkSetStringMacro(StudyInstanceUID);
  vtkGetStringMacro(StudyInstanceUID);
  //@}

  //@{
  //! Set the Implementation Class UID.
  /*!
   *  If you do not supply a UID, a default one will be used.
   */
  vtkSetStringMacro(ImplementationClassUID);
  vtkGetStringMacro(ImplementationClassUID);
  //@}

  //@{
  //! Set the Implementation Version Name.
  /*!
   *  If you do not supply a name, a default one will be used.
   */
  vtkSetStringMacro(ImplementationVersionName);
  vtkGetStringMacro(ImplementationVersionName);
  //@}

  //@{
  //! Set the Source Application Entity Title.
  /*!
   *  Provide a short name (16 chars max) for the network node that
   *  is running the implementation.  The name should have no spaces
   *  or punctuation and should consist only of letters and digits.
   */
  vtkSetStringMacro(SourceApplicationEntityTitle);
  vtkGetStringMacro(SourceApplicationEntityTitle);
  //@}

  //@{
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
  //@}

  //@{
  //! Set the metadata object to write to the file.
  void SetMetaData(vtkDICOMMetaData *);
  vtkDICOMMetaData *GetMetaData() { return this->MetaData; }
  //@}

  //@{
  //! Set the instance index to use when accessing vtkDICOMMataData.
  vtkSetMacro(Index, int);
  int GetIndex() { return this->Index; }
  //@}

  //@{
  //! Set the buffer size, the default is 8192 (8k).
  /*!
   *  A larger buffer size results in fewer IO calls.  The
   *  minimum buffer size is 256 bytes.
   */
  void SetBufferSize(int size);
  int GetBufferSize() { return this->BufferSize; }
  //@}

  //@{
  //! Write the metadata to the file.
  virtual void WriteHeader();

  //! Write all of the pixel data in one go.
  /*!
   *  This method assumes that the supplied buffer is already in
   *  the correct format (endianness, compression, fragments, etc)
   *  and writes it out to the file as the PixelData value.
   */
  virtual void WritePixelData(const unsigned char *cp, vtkIdType size);

  //! Write one frame to the end of the file.
  virtual void WriteFrame(const unsigned char *cp, vtkIdType size);

  //! Close the file.
  virtual void Close();

  //! Close the file and delete it.
  /*!
   *  This method should be called if, for any reason, the writing
   *  of the file could not be completed.
   */
  virtual void CloseAndRemove();

  //! Get the IO error code.
  unsigned long GetErrorCode() { return this->ErrorCode; }
  //@}

  //@{
  //! Generate a series UID and instance UIDs for the meta data.
  /*!
   *  This will be called automatically whenever you provide a
   *  new meta data object for the compiler.  Note that new UIDs
   *  will not be generated if you have already provided them with
   *  SetSOPInstanceUID() and SetSeriesInstanceUID().
   */
  void GenerateSeriesUIDs();
  //@}

  //@{
  //! Use the original PixelData VR when writing pixel data element.
  /*!
   *  This is really only useful when cloning data sets.  It ensures
   *  that the written data uses the same VR as the original data.
   */
  vtkSetMacro(KeepOriginalPixelDataVR, bool);
  vtkBooleanMacro(KeepOriginalPixelDataVR, bool);
  vtkGetMacro(KeepOriginalPixelDataVR, bool);
  //@}

protected:
  vtkDICOMCompiler();
  ~vtkDICOMCompiler();

  //! Internal method for flushing the IO buffer.
  /*!
   *  This is an internal method that flushes the buffer to the file.
   *  If called with cp = 0, it will initialize cp to the beginning of
   *  the write buffer, and ep to the end of the buffer, without writing
   *  anything to the file.  The caller should then write to the buffer,
   *  incrementing the pointer cp while doing so.  When cp approaches the
   *  end of the buffer (which is stored in ep), FlushBuffer should be
   *  called to flush the buffer contents to the file.  Every call will
   *  reset cp to the beginning of the buffer and ep to the end of the
   *  buffer.
   */
  virtual bool FlushBuffer(unsigned char* &cp, unsigned char* &ep);

  //! Report an error while compiling the file.
  virtual void CompileError(const char *message);

  //! React to "disk full" by deleting file and reporting error.
  virtual void DiskFullError();

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

  //! Write the fragments of the compressed data
  bool WriteFragments();

  //! Free any fragments that are stored in memory.
  void FreeFragments();

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
  vtkDICOMFile *OutputFile;
  unsigned char *Buffer;
  unsigned char **FrameData;
  unsigned int *FrameLength;
  unsigned int FrameCounter;
  int BufferSize;
  int ChunkSize;
  int Index;
  bool BigEndian;
  bool Compressed;
  bool KeepOriginalPixelDataVR;
  unsigned long ErrorCode;

  static char StudyUID[64];

  // used to share FlushBuffer with internal classes
  friend class vtkDICOMCompilerInternalFriendship;

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMCompiler(const vtkDICOMCompiler&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMCompiler&) VTK_DELETE_FUNCTION;
#elif __cplusplus >= 201103L
  vtkDICOMCompiler(const vtkDICOMCompiler&) = delete;
  void operator=(const vtkDICOMCompiler&) = delete;
#else
  vtkDICOMCompiler(const vtkDICOMCompiler&);
  void operator=(const vtkDICOMCompiler&);
#endif
};

#endif /* vtkDICOMCompiler_h */
