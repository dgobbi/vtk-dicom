#ifndef __vtkDICOMParser_h
#define __vtkDICOMParser_h

#include <vtkObject.h>

class vtkDICOMMetaData;
class vtkUnsignedShortArray;
class vtkDICOMParserInternalFriendship;

//! A meta data reader for DICOM data.
/*!
 *  This class provides routines for parsing a DICOM file
 *  and creating a vtkDICOMMetaData object.
 */
class vtkDICOMParser : public vtkObject
{
public:
  //! Create a new vtkDICOMParser instance.
  static vtkDICOMParser *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMParser, vtkObjectBase);

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
  void Update() { this->ReadFile(this->MetaData, this->Index); }

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

  // used to share FillBuffer with internal classes
  friend class vtkDICOMParserInternalFriendship;

private:
  vtkDICOMParser(const vtkDICOMParser&);  // Not implemented.
  void operator=(const vtkDICOMParser&);  // Not implemented.
};

#endif /* __vtkDICOMParser_h */
