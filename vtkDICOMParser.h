#ifndef __vtkDICOMParser_h
#define __vtkDICOMParser_h

#include <vtkObject.h>

class vtkDICOMMetaData;

//! A meta data reader for DICOM data.
/*!
 *  This class provides routines for parsing the DICOM
 *  file structure and creating a vtkDICOMParser object.
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

  //! Set the index to use when storing metadata.
  vtkSetMacro(Index, int);
  int GetIndex() { return this->Index; }

  //! Get the file offset after reading the metadata.
  vtkTypeInt64 GetFileOffset() { return this->FileOffset; }

  //! Set the buffer size, the default is 8192 (8k).
  void SetBufferSize(int size);
  int GetBufferSize() { return this->BufferSize; }

  //! Read the file.
  void Update() { this->ReadFile(this->MetaData, this->Index); }

  //! Internal method for filling the buffer, do not use.
  virtual bool FillBuffer(
    const unsigned char* &cp, const unsigned char* &ep);

protected:
  vtkDICOMParser();
  ~vtkDICOMParser();

  virtual bool ReadFile(vtkDICOMMetaData *data, int idx);

  bool ReadMetaHeader(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMMetaData *data, int idx);

  bool ReadMetaData(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMMetaData *data, int idx);

  void ComputeFileOffset(
    const unsigned char* cp, const unsigned char* ep);

  char *FileName;
  vtkDICOMMetaData *MetaData;
  std::istream *InputStream;
  std::streamsize BytesRead;
  vtkTypeInt64 FileOffset;
  char *Buffer;
  int BufferSize;
  int ChunkSize;
  int Index;

private:
  vtkDICOMParser(const vtkDICOMParser&);  // Not implemented.
  void operator=(const vtkDICOMParser&);  // Not implemented.
};

#endif /* __vtkDICOMParser_h */
