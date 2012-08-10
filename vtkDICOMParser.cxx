#include "vtkDICOMParser.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMSequenceItem.h"

#include <vtkObjectFactory.h>

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <assert.h>

#include <string>

vtkStandardNewMacro(vtkDICOMParser);
vtkCxxSetObjectMacro(vtkDICOMParser, MetaData, vtkDICOMMetaData);

//----------------------------------------------------------------------------
// Decode a byte stream as little-endian or big-endian

namespace {

// decoder has two specializations
const int LE = 0;
const int BE = 1;

// the decoder types
class DefaultDecoder;
class LittleEndianDecoder;
class BigEndianDecoder;

// base class for the decoder class template
class DecoderBase
{
public:
  // specify whether to use implicit VRs (default: explicit VRs)
  void SetImplicitVR(bool i) {this->ImplicitVR = i; }

  // set the Item member variable
  void SetItem(vtkDICOMSequenceItem *i);

  // read l bytes of data, or until delimiter tag found
  virtual bool ReadElements(
    const unsigned char* &data, const unsigned char* &enddata,
    unsigned int l, vtkDICOMTag delimiter, unsigned int &bytesRead) = 0;

  // skip l bytes of data, or until delimiter tag found
  virtual bool SkipElements(
    const unsigned char* &data, const unsigned char* &enddata,
    unsigned int l, vtkDICOMTag delimiter, unsigned int &bytesRead) = 0;

  // ensure that there are at least "n" chars left in buffer
  bool CheckBuffer(
    const unsigned char* &data, const unsigned char* &enddata,
    unsigned int n);

  // find an element within the current context, e.g. sequence.
  bool GetAttributeValue(vtkDICOMTag tag, vtkDICOMValue &v);
  bool GetAttributeValue(vtkDICOMTag tag, unsigned short &u);

  // get the dictionary VR (for implicit VR elements)
  vtkDICOMVR FindDictVR(vtkDICOMTag tag);

protected:
  // constructor that initializes all of the members
  DecoderBase(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Parser(parser), Item(0), MetaData(data), Index(idx), ImplicitVR(0) {}

  // an implicit little-endian decoder
  DefaultDecoder *ImplicitLE;
  // the parser has the stream to read from
  vtkDICOMParser *Parser;
  // the item to read the data into (has priority over MetaData)
  vtkDICOMSequenceItem *Item;
  // the metadata object to read the data into
  vtkDICOMMetaData *MetaData;
  // the index to use with the meta data
  int Index;
  // the VRs are implicit
  bool ImplicitVR;
};

//----------------------------------------------------------------------------
template<int E>
class Decoder : public DecoderBase
{
public:
  // decode two, four, or eight bytes
  static unsigned short GetInt16(const unsigned char* ip);
  static unsigned int GetInt32(const unsigned char* ip);
  static unsigned long long GetInt64(const unsigned char* ip);

  // decode n values of the specified type
  static void GetValues(const unsigned char *ip, char *v, unsigned int n);
  static void GetValues(const unsigned char *ip, unsigned char *v,
                        unsigned int n);
  static void GetValues(const unsigned char *ip, short *v, unsigned int n);
  static void GetValues(const unsigned char *ip, unsigned short *v,
                        unsigned int n);
  static void GetValues(const unsigned char *ip, int *v, unsigned int n);
  static void GetValues(const unsigned char *ip, unsigned int *v,
                        unsigned int n);
  static void GetValues(const unsigned char *ip, float *v, unsigned int n);
  static void GetValues(const unsigned char *ip, double *v, unsigned int n);

  // read n values, re-filling the buffer as necessary, and return the
  // number of bytes read.
  template<class T>
  unsigned int ReadData(
    const unsigned char* &data, const unsigned char* &enddata,
    T *ptr, unsigned int n);

  // skip n bytes and return the number of bytes actually skipped
  unsigned int SkipData(
    const unsigned char* &data, const unsigned char* &enddata,
    unsigned int n);

  // read l bytes of data, or until delimiter tag found
  bool ReadElements(
    const unsigned char* &data, const unsigned char* &enddata,
    unsigned int l, vtkDICOMTag delimiter, unsigned int &bytesRead);

  // skip l bytes of data, or skip until delimiter tag found
  bool SkipElements(
    const unsigned char* &data, const unsigned char* &enddata,
    unsigned int l, vtkDICOMTag delimiter, unsigned int &bytesRead);

  // read the tag, vr, and vl and return the number of bytes read (will
  // return zero if an error occurred)
  unsigned int ReadElementHead(
    const unsigned char* &data, const unsigned char* &enddata,
    vtkDICOMTag tag, vtkDICOMVR &vr, unsigned int &vl);

  // read one data element value of the specified vr and vl, where vl can
  // be 0xffffffff, and return the number of bytes read
  unsigned int ReadElementValue(
    const unsigned char* &data, const unsigned char* &enddata,
    vtkDICOMVR vr, unsigned int vl, vtkDICOMValue &v);

protected:
  Decoder() {};
  Decoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    DecoderBase(parser, data, idx) {}
};

//----------------------------------------------------------------------------
class DefaultDecoder : public Decoder<LE>
{
public:
  DefaultDecoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Decoder<LE>(parser, data, idx) {
    this->ImplicitVR = true;
    this->ImplicitLE = this; }
};

class LittleEndianDecoder : public Decoder<LE>
{
public:
  LittleEndianDecoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Decoder<LE>(parser, data, idx), ExtraDecoder(parser, data, idx) {
    this->ImplicitLE = &this->ExtraDecoder; }

private:
  DefaultDecoder ExtraDecoder;
};

class BigEndianDecoder : public Decoder<BE>
{
public:
  BigEndianDecoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Decoder<BE>(parser, data, idx), ExtraDecoder(parser, data, idx) {
    this->ImplicitLE = &this->ExtraDecoder; }

private:
  DefaultDecoder ExtraDecoder;
};

//----------------------------------------------------------------------------
inline void DecoderBase::SetItem(vtkDICOMSequenceItem *i)
{
  this->Item = i;
  this->ImplicitLE->Item = i;
}

//----------------------------------------------------------------------------
inline bool DecoderBase::CheckBuffer(
  const unsigned char* &data, const unsigned char* &enddata,
  unsigned int n)
{
  bool r = true;
  if (data + n >= enddata)
    {
    r = this->Parser->FillBuffer(data, enddata);
    r &= (data + n < enddata);
    }
   return r;
}

//----------------------------------------------------------------------------
bool DecoderBase::GetAttributeValue(vtkDICOMTag tag, vtkDICOMValue &v)
{
  if (this->Item)
    {
    vtkDICOMDataElementIterator iter = this->Item->GetData();
    vtkDICOMDataElementIterator iend = this->Item->GetDataEnd();

    while (iter != iend)
      {
      if (iter->GetTag() == tag)
        {
        v = iter->GetValue();
        return true;
        }
      ++iter;
      }
    }
  else if (this->MetaData)
    {
    int idx = (this->Index == -1 ? 0 : this->Index);
    return this->MetaData->GetAttributeValue(idx, tag, v);
    }

  return false;
}

bool DecoderBase::GetAttributeValue(vtkDICOMTag tag, unsigned short &u)
{
  vtkDICOMValue v;
  if (this->GetAttributeValue(tag, v))
    {
    v.GetValues(&u, 0, 1);
    return true;
    }

  return false;
}

//----------------------------------------------------------------------------
vtkDICOMVR DecoderBase::FindDictVR(vtkDICOMTag tag)
{
  vtkDICOMDictEntry de;
  vtkDICOMVR vr = vtkDICOMVR::UN;

  if (tag.GetElement() == 0x0000)
    {
    // group length element
    vr = vtkDICOMVR::UL;
    }
  else if (this->MetaData->FindDictEntry(tag, de))
    {
    vr = de.GetVR();
    if (vr == vtkDICOMVR::XS)
      {
      unsigned short r;
      vr = vtkDICOMVR::US;
      if (this->GetAttributeValue(DC::PixelRepresentation, r))
        {
        vr = (r == 0 ? vtkDICOMVR::US : vtkDICOMVR::SS);
        }
      }
    else if (vr == vtkDICOMVR::OX)
      {
      unsigned short s;
      vr = vtkDICOMVR::OW;
      if (tag.GetGroup() == 0x5400)
        {
        if (this->GetAttributeValue(DC::WaveformBitsAllocated, s))
          {
          vr = (s > 8 ? vtkDICOMVR::OW : vtkDICOMVR::OB);
          }
        }
      else
        {
        if (this->GetAttributeValue(DC::BitsAllocated, s))
          {
          vr = (s > 8 ? vtkDICOMVR::OW : vtkDICOMVR::OB);
          }
        }
      }
    }

  return vr;
}

//----------------------------------------------------------------------------
template<>
inline unsigned short Decoder<LE>::GetInt16(const unsigned char *ip)
{
  return ip[0] + (ip[1] << 8);
}

template<>
inline unsigned int Decoder<LE>::GetInt32(const unsigned char *ip)
{
  return ip[0] + (ip[1] << 8) + ((ip[2] + (ip[3] << 8)) << 16);
}

template<>
inline unsigned long long Decoder<LE>::GetInt64(const unsigned char *ip)
{
  unsigned int a = ip[0] + (ip[1] << 8) + ((ip[2] + (ip[3] << 8)) << 16);
  long long b = ip[4] + (ip[5] << 8) + ((ip[6] + (ip[7] << 8)) << 16);
  return (b << 32) + a;
}

template<>
inline unsigned short Decoder<BE>::GetInt16(const unsigned char *ip)
{
  return (ip[0] << 8) + ip[1];
}

template<>
inline unsigned int Decoder<BE>::GetInt32(const unsigned char *ip)
{
  return ((((ip[0] << 8) + ip[1]) << 8) + ip[2] << 8) + ip[3];
}

template<>
inline unsigned long long Decoder<BE>::GetInt64(const unsigned char *ip)
{
  long long a = ((((ip[0] << 8) + ip[1]) << 8) + ip[2]) << 8 + ip[3];
  unsigned int b = ((((ip[4] << 8) + ip[5]) << 8) + ip[6]) << 8 + ip[7];
  return (a << 32) + b;
}

//----------------------------------------------------------------------------
template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, char *op, unsigned int n)
{
  do { *op++ = static_cast<char>(*ip++); } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, unsigned char *op, unsigned int n)
{
  do { *op++ = *ip++; } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, short *op, unsigned int n)
{
  do { *op++ = static_cast<short>(Decoder<E>::GetInt16(ip)); ip += 2; }
  while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, unsigned short *op, unsigned int n)
{
  do { *op++ = Decoder<E>::GetInt16(ip); ip += 2; } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, int *op, unsigned int n)
{
  do { *op++ = static_cast<int>(Decoder<E>::GetInt32(ip)); ip += 4; }
  while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, unsigned int *op, unsigned int n)
{
  do { *op++ = Decoder<E>::GetInt32(ip); ip += 4; } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, float *op, unsigned int n)
{
  union { float f; unsigned int i; } u;

  do
    {
    u.i = Decoder<E>::GetInt32(ip);
    *op++ = u.i;
    ip += 4;
    }
  while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, double *op, unsigned int n)
{
  union { double d; unsigned long long l; } u;

  do
    {
    u.l = Decoder<E>::GetInt64(ip);
    *op++ = u.d;
    ip += 8;
    }
  while (--n);
}

//----------------------------------------------------------------------------
// Read "n" elements of type "T" into the supplied array pointer.
template<int E>
template<class T>
unsigned int Decoder<E>::ReadData(
  const unsigned char* &data, const unsigned char* &enddata,
  T *ptr, unsigned int n)
{
  unsigned int l = n*sizeof(T);
  while (n != 0 && this->CheckBuffer(data, enddata, sizeof(T)))
    {
    unsigned int m = static_cast<unsigned int>((enddata - data)/sizeof(T));
    if (m > n) { m = n; }
    Decoder<E>::GetValues(data, ptr, m);
    data += m*sizeof(T);
    ptr += m;
    n -= m;
    }

  return l - n*sizeof(T);
}

//----------------------------------------------------------------------------
// Skip "l" bytes in the buffer, return the number of bytes actually skipped
template<int E>
unsigned int Decoder<E>::SkipData(
  const unsigned char* &data, const unsigned char* &enddata, unsigned int l)
{
  unsigned int n = l;

  while (n != 0 && this->CheckBuffer(data, enddata, 2))
    {
    unsigned int m = static_cast<unsigned int>(enddata - data);
    if (m > n) { m = n; }
    data += m;
    n -= m;
    }

  return l - n;
}

//----------------------------------------------------------------------------
template<int E>
unsigned int Decoder<E>::ReadElementHead(
  const unsigned char* &data, const unsigned char* &enddata,
  vtkDICOMTag tag, vtkDICOMVR &vr, unsigned int &vl)
{
  unsigned int l = 4;

  if (this->ImplicitVR)
    {
    // implicit VR
    vr = this->FindDictVR(tag);
    vl = Decoder<E>::GetInt32(data);
    // force group length tags to have one 32-bit length value
    if (tag.GetElement() == 0x0000) { vl = 4; }
    data += 4;
    }
  else
    {
    // explicit VR
    vr = vtkDICOMVR(data);
    vl = Decoder<E>::GetInt16(data + 2);
    data += 4;
    if (!vr.IsValid())
      {
      // try to get VR from dictionary instead
      vr = this->FindDictVR(tag);
      vl = Decoder<E>::GetInt32(data - 4);
      }
    else if (vr.HasLongVL())
      {
      // check that buffer has 4 bytes for 32-bit VL
      if (!this->CheckBuffer(data, enddata, 4)) { return 0; }
      vl = Decoder<E>::GetInt32(data);
      data += 4;
      l += 4;
      }
    }

  return l;
}

//----------------------------------------------------------------------------
template<int E>
unsigned int Decoder<E>::ReadElementValue(
  const unsigned char* &data, const unsigned char* &enddata,
  vtkDICOMVR vr, unsigned int vl, vtkDICOMValue &v)
{
  unsigned int l = 0;

  // handle elements of unknown length
  if (vl == 0xffffffff)
    {
    // if VR is UN then it is a sequence encoded as implicit LE
    if (vr == vtkDICOMVR::UN)
      {
      v.Clear();
      unsigned int il = 0;
      this->ImplicitLE->SkipElements(
        data, enddata, vl, vtkDICOMTag(0xfffe,0xe0dd), il);
      return il;
      }
    else if (vr != vtkDICOMVR::SQ)
      {
      // make sure unknown length elements are proper sequences
      if (!this->CheckBuffer(data, enddata, 8)) { return 0; }
      unsigned short g1 = Decoder<E>::GetInt16(data);
      unsigned short e1 = Decoder<E>::GetInt16(data + 2);
      if (g1 != 0xfffe || (e1 != 0xe000 && e1 != 0xe0dd)) { return 0; }

      v.Clear();
      unsigned int il = 0;
      this->SkipElements(data, enddata, vl, vtkDICOMTag(0xfffe,0xe0dd), il);
      return il;
      }
    }

  switch (vr.GetType())
    {
    case VTK_CHAR:
      {
      char *ptr = v.AllocateTextData(vr, vl);
      l = this->ReadData(data, enddata, ptr, vl);
      // AllocateTextData makes room for terminal null
      if (l == 0 || ptr[l-1] != '\0') { ptr[l] = '\0'; }
      }
      break;
    case VTK_UNSIGNED_CHAR:
      {
      unsigned char *ptr = v.AllocateByteData(vr, vl);
      l = this->ReadData(data, enddata, ptr, vl);
      }
      break;
    case VTK_SHORT:
      {
      unsigned int n = vl/sizeof(short);
      short *ptr = v.AllocateShortData(vr, n);
      l = this->ReadData(data, enddata, ptr, n);
      }
      break;
    case VTK_UNSIGNED_SHORT:
      {
      unsigned int n = vl/sizeof(unsigned short);
      unsigned short *ptr = v.AllocateUShortData(vr, n);
      l = this->ReadData(data, enddata, ptr, n);
      }
      break;
    case VTK_INT:
      {
      unsigned int n = vl/sizeof(int);
      int *ptr = v.AllocateLongData(vr, n);
      l = this->ReadData(data, enddata, ptr, n);
      }
      break;
    case VTK_UNSIGNED_INT:
      {
      unsigned int n = vl/sizeof(unsigned int);
      unsigned int *ptr = v.AllocateULongData(vr, n);
      l = this->ReadData(data, enddata, ptr, n);
      }
      break;
    case VTK_FLOAT:
      {
      unsigned int n = vl/sizeof(float);
      float *ptr = v.AllocateFloatData(vr, n);
      l = this->ReadData(data, enddata, ptr, n);
      }
      break;
    case VTK_DOUBLE:
      {
      unsigned int n = vl/sizeof(double);
      double *ptr = v.AllocateDoubleData(vr, n);
      l = this->ReadData(data, enddata, ptr, n);
      }
      break;
    case VTK_DICOM_ITEM:
      {
      vtkDICOMSequence seq;
      l = 0;
      while (l < vl)
        {
        if (!this->CheckBuffer(data, enddata, 8)) { return l; }
        unsigned short g = Decoder<E>::GetInt16(data);
        unsigned short e = Decoder<E>::GetInt16(data + 2);
        unsigned int il = Decoder<E>::GetInt32(data + 4);
        data += 8;
        l += 8;

        if (g == 0xfffe && e == 0xe000)
          {
          // read one item
          vtkDICOMTag endtag(0xfffe, 0xe00d);
          vtkDICOMSequenceItem item;
          vtkDICOMSequenceItem *olditem = this->Item;
          this->SetItem(&item);
          this->ReadElements(data, enddata, il, endtag, l);
          seq.AddItem(item);
          this->SetItem(olditem);
          }
        else if (g == 0xfffe && e == 0xe0dd)
          {
          // sequence delimiter found
          break;
          }
        else
          {
          // non-item tag found
          if (vl != 0xffffffff)
            {
            l += this->SkipData(data, enddata, vl-l);
            }
          break;
          }
        }
      v = seq;
      }
      break;
    }

  return l;
}

//----------------------------------------------------------------------------
template<int E>
bool Decoder<E>::ReadElements(
  const unsigned char* &cp, const unsigned char* &ep,
  unsigned int l, vtkDICOMTag delimiter, unsigned int &bytesRead)
{
  unsigned int tl = 0;
  unsigned short group = 0x0000;

  // does delimiter specify a single group to read?
  if (delimiter.GetElement() == 0x0000)
    {
    group = delimiter.GetGroup();
    delimiter = vtkDICOMTag(0x0000,0x0000);
    }

  while (tl < l)
    {
    // read the tag
    if (!this->CheckBuffer(cp, ep, 8)) { break; }
    unsigned short g = Decoder<E>::GetInt16(cp);
    unsigned short e = Decoder<E>::GetInt16(cp + 2);
    vtkDICOMTag tag(g,e);

    // break if element is not in the chosen group
    if (group && group != g) { break; }

    // read the VR and VL
    cp += 4;
    vtkDICOMVR vr;
    unsigned int vl;
    unsigned int hl = this->ReadElementHead(cp, ep, tag, vr, vl);
    tl += 4 + hl;

    // break if end of file or if delimiter
    if (hl == 0 || tag == delimiter) { break; }

    // read the value
    vtkDICOMValue v;
    if (vr == vtkDICOMVR::UN && !this->ImplicitVR)
      {
      // if it was explicitly labeled 'UN' then check dictionary
      vr = this->FindDictVR(tag);
      tl += this->ImplicitLE->ReadElementValue(cp, ep, vr, vl, v);
      }
    else
      {
      tl += this->ReadElementValue(cp, ep, vr, vl, v);
      }

    // store the value
    if (this->Item)
      {
      this->Item->AddDataElement(tag, v);
      }
    else if (this->Index == -1)
      {
      this->MetaData->SetAttributeValue(tag, v);
      }
    else
      {
      this->MetaData->SetAttributeValue(this->Index, tag, v);
      }
    // cout << tag << " " << vr << " " << vl << " " << v << "\n";
    }

  bytesRead += tl;

  return true;
}

//----------------------------------------------------------------------------
template<int E>
bool Decoder<E>::SkipElements(
  const unsigned char* &data, const unsigned char* &enddata,
  unsigned int l, vtkDICOMTag delimiter, unsigned int &bytesRead)
{
  if (l == 0xffffffff)
    {
    unsigned short group = 0x0000;

    // does delimiter specify a single group to read?
    if (delimiter.GetElement() == 0x0000)
      {
      group = delimiter.GetGroup();
      delimiter = vtkDICOMTag(0x0000,0x0000);
      }

    for (;;)
      {
      if (!this->CheckBuffer(data, enddata, 8)) { return false; }
      unsigned short g = Decoder<E>::GetInt16(data);
      unsigned short e = Decoder<E>::GetInt16(data + 2);

      // break if element is not in the chosen group
      if (group && group != g) { break; }

      data += 4;
      unsigned int tl = 8;
      unsigned int vl = 0;
      vtkDICOMVR vr;

      if (g == 0xfffe || this->ImplicitVR)
        {
        vl = Decoder<E>::GetInt32(data);
        data += 4;
        }
      else
        {
        vr = vtkDICOMVR(data);
        vl = Decoder<E>::GetInt16(data + 2);
        data += 4;
        if (vr.HasLongVL())
          {
          if (!this->CheckBuffer(data, enddata, 4)) { return false; }
          vl = Decoder<E>::GetInt32(data);
          data += 4;
          tl += 4;
          }
        }

      bytesRead += tl;

      if (g == delimiter.GetGroup() &&
          e == delimiter.GetElement())
        {
        break;
        }

      if (vl == 0xffffffff)
        {
        // use sequence delimiter
        vtkDICOMTag newdelim(0xfffe, 0xe0dd);
        if (g == 0xfffe && e == 0xe000)
          {
          // use item delimiter
          newdelim = vtkDICOMTag(0xfffe, 0xe00d);
          }
        // skip internal segment until new delimiter found
        if (vr != vtkDICOMVR::UN)
          {
          if (!this->SkipElements(data, enddata, vl, newdelim, bytesRead))
            {
            return false;
            }
          }
        // if VR is explicit UN, sequence is implicit LE
        else if (!this->ImplicitLE->SkipElements(
                   data, enddata, vl, newdelim, bytesRead))
          {
          return false;
          }
        }
      else
        {
        tl = this->SkipData(data, enddata, vl);
        bytesRead += tl;
        if (tl != vl)
          {
          return false;
          }
        }
      }
    }
  else
    {
    unsigned int tl = this->SkipData(data, enddata, l);
    bytesRead += tl;
    if (tl != l)
      {
      return false;
      }
    }

  return true;
}

} // end anonymous namespace

//----------------------------------------------------------------------------
// Constructor
vtkDICOMParser::vtkDICOMParser()
{
  this->FileName = NULL;
  this->MetaData = NULL;
  this->InputStream = NULL;
  this->Buffer = NULL;
  this->BufferSize = 8192;
  this->ChunkSize = 0;
  this->Index = -1;
}

// Destructor
vtkDICOMParser::~vtkDICOMParser()
{
  delete [] this->FileName;

  if (this->MetaData)
    {
    this->MetaData->Delete();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMParser::SetBufferSize(int size)
{
  if (this->BufferSize != size)
    {
    if (size < 256) { size = 256; }
    if (size > (2147483647 - 8)) { size = (2147483647 - 8); }
    this->BufferSize = size;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::ReadFile(vtkDICOMMetaData *data, int idx)
{
  // Check that the file name has been set.
  if (!this->FileName)
    {
    vtkErrorMacro("ReadFile: No file name has been set");
    return false;
    }

  // Make sure that the file exists.
  struct stat fs;
  if (stat(this->FileName, &fs) != 0)
    {
    vtkErrorMacro("ReadFile: Can't open file " << this->FileName);
    return false;
    }

  // Make sure that the file is readable.
  ifstream infile(this->FileName, ios::in | ios::binary);

  if (infile.fail())
    {
    vtkErrorMacro("ReadFile: Can't read the file " << this->FileName);
    return false;
    }

  this->InputStream = &infile;
  this->Buffer = new char [this->BufferSize + 8];
  // guard against anyone changing BufferSize while reading
  this->ChunkSize = this->BufferSize;

  const unsigned char *cp = NULL;
  const unsigned char *ep = NULL;
  this->FillBuffer(cp, ep);

  if (ep - cp >= 132 &&
      cp[128] == 'D' && cp[129] == 'I' && cp[130] == 'C' && cp[131] == 'M')
    {
    // DICM magic number at offset 128, where it belongs in DICOM
    cp += 132;
    }
  else if (ep - cp >= 4 &&
           cp[0] == 'D' && cp[1] == 'I' && cp[2] == 'C' && cp[3] == 'M')
    {
    // DICM magic number at beginning of file, where it doesn't belong
    cp += 4;
    }

  this->ReadMetaHeader(cp, ep, data, idx);
  this->ReadMetaData(cp, ep, data, idx);

  delete [] this->Buffer;
  this->InputStream = NULL;
  infile.close();

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::ReadMetaHeader(
  const unsigned char* &cp, const unsigned char* &ep,
  vtkDICOMMetaData *meta, int idx)
{
  LittleEndianDecoder decoder(this, meta, idx);

  unsigned int bytesRead = 0;

  // get the meta information group length
  unsigned short g = Decoder<LE>::GetInt16(cp);
  unsigned short e = Decoder<LE>::GetInt16(cp + 2);
  vtkDICOMVR vr = vtkDICOMVR(cp + 4);
  unsigned int vl = Decoder<LE>::GetInt16(cp + 6);

  // verify that this is the right tag
  if (g == 0x0002)
    {
    // check for strange files with implicit VR meta header
    decoder.SetImplicitVR(!vr.IsValid());

    unsigned int l = 0xffffffff;
    if (e == 0x0000 && vl == 4)
      {
      // get length from tag 0x0002,0x0000
      l = Decoder<LE>::GetInt32(cp + 8) + 12;
      }

    decoder.ReadElements(cp, ep, l, vtkDICOMTag(g,0), bytesRead);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::ReadMetaData(
  const unsigned char* &cp, const unsigned char* &ep,
  vtkDICOMMetaData *meta, int idx)
{
  // the decoders to choose from
  LittleEndianDecoder decoderLE(this, meta, idx);
  BigEndianDecoder decoderBE(this, meta, idx);
  DecoderBase *decoder = &decoderLE;

  // make sure there is at least one data element
  if (ep - cp < 8)
    {
    this->FillBuffer(cp, ep);
    if (ep - cp < 8)
      {
      return false;
      }
    }

  std::string tsyntax;
  int i = (idx == -1 ? 0 : idx);
  this->MetaData->GetAttributeValue(i, DC::TransferSyntaxUID, tsyntax);

  if (tsyntax == "") // try to guess the syntax
    {
    if (!decoder->CheckBuffer(cp, ep, 8)) { return false; }
    decoder->SetImplicitVR(!vtkDICOMVR(cp + 4).IsValid());
    }
  else if (tsyntax == "1.2.840.10008.1.2" ||  // Implicit LE
           tsyntax == "1.2.840.10008.1.20")   // Papyrus Implicit LE
    {
    decoder->SetImplicitVR(true);
    }
  else if (tsyntax == "1.2.840.10008.1.2.2") // Explicit BE
    {
    decoder = &decoderBE;
    decoder->SetImplicitVR(false);
    }

  unsigned int bytesRead = 0;

  decoder->ReadElements(cp, ep, 0xffffffff, DC::PixelData, bytesRead);

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::FillBuffer(
  const unsigned char* &ucp, const unsigned char* &ep)
{
  char *dp = this->Buffer;
  std::streamsize n = static_cast<std::streamsize>(ep - ucp);
  const char *cp = reinterpret_cast<const char *>(ucp);

  // number of bytes to read
  std::streamsize nbytes = this->ChunkSize;
  if (n != 0)
    {
    // make sure read will not overflow the buffer
    if (n > 8)
      {
      nbytes -= (n - 8);
      }
    // recycle unused buffer chars to head of buffer
    do { *dp++ = *cp++; } while (--n);
    }
  else if (this->InputStream->bad())
    {
    vtkErrorMacro("FillBuffer: error reading from file " << this->FileName);
    return false;
    }
  else if (this->InputStream->eof())
    {
    // if buffer is drained, and eof, then done
    return false;
    }

  // read at most n bytes
  this->InputStream->read(dp, nbytes);

  // get number of chars read
  n = this->InputStream->gcount();

  // ep is recycled chars plus newly read chars
  ep = reinterpret_cast<unsigned char *>(dp + n);
  ucp = reinterpret_cast<unsigned char *>(this->Buffer);

  return true;
}

//----------------------------------------------------------------------------
void vtkDICOMParser::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "FileName: "
     << (this->FileName ? this->FileName : "(NULL)") << "\n";
  os << indent << "MetaData: " << this->MetaData << "\n";
  os << indent << "Index: " << this->Index << "\n";
  os << indent << "BufferSize: " << this->BufferSize << "\n";
}
