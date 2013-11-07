/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMCompiler.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMUtilities.h"
#include "vtkDICOMItem.h"

#include <vtkObjectFactory.h>
#include <vtkStringArray.h>
#include <vtkUnsignedShortArray.h>
#include <vtkErrorCode.h>

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined(_WIN32) && !defined(__CYGWIN__)
#include <io.h>
#include <direct.h>
#define _unlink unlink
#else
#include <unistd.h> // unlink
#endif

#include <assert.h>

#include <string>

vtkStandardNewMacro(vtkDICOMCompiler);
vtkCxxSetObjectMacro(vtkDICOMCompiler, MetaData, vtkDICOMMetaData);

char vtkDICOMCompiler::StudyUID[64] = {};

/*----------------------------------------------------------------------------
The top section of this file defines "Encoder" classes that compile
the meta data into data elements that can be written to a file.
The encoder class hierarchy is as follows:

EncoderBase (the base class)
    Encoder<LE> (template specialization for little-endian encoding)
        DefaultEncoder (encoder for implicit little-endian syntax)
        LittleEndianEncoder (encoder for explicit little-endian syntax)
    Encoder<GE> (template specialization for big-endian encoding)
        BigEndianEncoder (encoder for explicit big-endian syntax)

The vtkDICOMCompiler utilizes the DefaultEncoder, LittleEndianEncoder,
or the BigEndianEncoder depending on the transfer syntax.
----------------------------------------------------------------------------*/

class vtkDICOMCompilerInternalFriendship
{
public:
  static bool FlushBuffer(vtkDICOMCompiler *comp,
    unsigned char* &cp, unsigned char* &ep)
  {
    return comp->FlushBuffer(cp, ep);
  }

  static void CompileError(vtkDICOMCompiler *comp,
    const char *message)
  {
    return comp->CompileError(message);
  }

  static unsigned int ComputePixelDataSize(vtkDICOMCompiler *comp)
  {
    return comp->ComputePixelDataSize();
  }
};

namespace {

// Useful constants to replace commonly-used literals.
const unsigned short HxFFFE = 0xFFFE; // sequence group
const unsigned short HxE000 = 0xE000; // item start
const unsigned short HxE00D = 0xE00D; // item end
const unsigned short HxE0DD = 0xE0DD; // sequence end
const unsigned short Hx0000 = 0x0000; // empty element
const unsigned int HxFFFFFFFF = 0xFFFFFFFF; // unknown length

// The encoder has two specializations: little-endian, big-endian.
const int LE = 0;
const int BE = 1;

// The encoder types that are available.
class DefaultEncoder;
class LittleEndianEncoder;
class BigEndianEncoder;

// The base class for the encoder classes.
class EncoderBase
{
public:
  // Whether to use implicit VRs (default: explicit VRs).
  void SetImplicitVR(bool i) { this->ImplicitVR = i; }

  // Set the instance UID to use.
  void SetSOPInstanceUID(const char *uid) {
    this->SOPInstanceUID = uid; };

  // Set the series UID to use.
  void SetSeriesInstanceUID(const char *uid) {
    this->SeriesInstanceUID = uid; };

  // Set the study UID to use.
  void SetStudyInstanceUID(const char *uid) {
    this->StudyInstanceUID = uid; };

  // Write the data element head, return the length (8 or 12)
  virtual unsigned int WriteElementHead(
    unsigned char* cp, vtkDICOMTag tag, vtkDICOMVR vr, unsigned int vl) = 0;

  // Write all data elements between iter and iterend.
  virtual bool WriteElements(
    unsigned char* &cp, unsigned char* &ep,
    vtkDICOMDataElementIterator iter,
    vtkDICOMDataElementIterator iterend) = 0;

  // Copy bytes from sp to end marker cp into the value "v".
  // If the parameter "v" is NULL, then it will be ignored.
  void CopyBuffer(
    vtkDICOMValue *v, unsigned char *sp, unsigned char *cp);

  // If there are fewer than "n" bytes left in the buffer, then flush
  // the buffer and move the write pointer cp to the start of the buffer.
  bool CheckBuffer(
    unsigned char* &cp, unsigned char* &ep, unsigned int n);

  // Count the number of bytes required to write the specified data.
  unsigned int DataSize(
    vtkDICOMDataElementIterator iter,
    vtkDICOMDataElementIterator iterEnd);

protected:
  // Constructor that initializes all of the members.
  EncoderBase(vtkDICOMCompiler *comp, int idx) :
    Compiler(comp), SOPInstanceUID(0), SeriesInstanceUID(0),
    Index(idx), Depth(0), ImplicitVR(0) {}

  // the vtkDICOMCompiler::FlushBuffer method is used to refill the buffer
  vtkDICOMCompiler *Compiler;
  // the instance UID and series UID
  const char *SOPInstanceUID;
  const char *SeriesInstanceUID;
  const char *StudyInstanceUID;
  // the instance index to use with the meta data
  int Index;
  // the sequence depth
  int Depth;
  // if this is set, then VRs are implicit
  bool ImplicitVR;
};

//----------------------------------------------------------------------------
template<int E>
class Encoder : public EncoderBase
{
public:
  // Encode two, four, or eight bytes from unsigned integers.
  static void PutInt16(unsigned char* ip, unsigned short i);
  static void PutInt32(unsigned char* ip, unsigned int i);
  static void PutInt64(unsigned char* ip, unsigned long long i);

  // Write "n" values from "v" into "ip".
  static void PutValues(unsigned char *ip, const char *v, unsigned int n);
  static void PutValues(unsigned char *ip, const unsigned char *v,
                        unsigned int n);
  static void PutValues(unsigned char *ip, const short *v, unsigned int n);
  static void PutValues(unsigned char *ip, const unsigned short *v,
                        unsigned int n);
  static void PutValues(unsigned char *ip, const int *v, unsigned int n);
  static void PutValues(unsigned char *ip, const unsigned int *v,
                        unsigned int n);
  static void PutValues(unsigned char *ip, const float *v, unsigned int n);
  static void PutValues(unsigned char *ip, const double *v, unsigned int n);
  static void PutValues(unsigned char *ip, const vtkDICOMTag *v,
                        unsigned int n);

  // Write "n" values into the buffer from the provided pointer.
  // The buffer will be flushed as necessary.
  template<class T>
  bool WriteData(
    unsigned char* &cp, unsigned char* &ep, const T *ptr, unsigned int n);

  // write the head of a data element, return length (8 or 12)
  unsigned int WriteElementHead(
    unsigned char* cp, vtkDICOMTag tag, vtkDICOMVR vr, unsigned int vl);

  // write one data element
  bool WriteDataElement(
    unsigned char* &cp, unsigned char* &ep,
    const vtkDICOMDataElement &elem);

  // Write all elements from iter to iterend.
  bool WriteElements(
    unsigned char* &cp, unsigned char* &ep,
    vtkDICOMDataElementIterator iter,
    vtkDICOMDataElementIterator iterend);

protected:
  Encoder(vtkDICOMCompiler *comp, int idx) :
    EncoderBase(comp, idx) {}

private:
  Encoder() {};
};

//----------------------------------------------------------------------------
// The little-endian implicit-vr encoder.
class DefaultEncoder : public Encoder<LE>
{
public:
  DefaultEncoder(vtkDICOMCompiler *comp, int idx) :
    Encoder<LE>(comp, idx)
  {
    this->ImplicitVR = true;
  }
};

// The little-endian encoder.
class LittleEndianEncoder : public Encoder<LE>
{
public:
  LittleEndianEncoder(vtkDICOMCompiler *comp, int idx) :
    Encoder<LE>(comp, idx) {}
};

// The big-endian encoder.
class BigEndianEncoder : public Encoder<BE>
{
public:
  BigEndianEncoder(vtkDICOMCompiler *comp, int idx) :
    Encoder<BE>(comp, idx) {}
};

//----------------------------------------------------------------------------
inline bool EncoderBase::CheckBuffer(
  unsigned char* &cp, unsigned char* &ep, unsigned int n)
{
  bool r = true;
  if (n > static_cast<unsigned int>(ep - cp))
    {
    r = vtkDICOMCompilerInternalFriendship::FlushBuffer(
          this->Compiler, cp, ep);
    r &= (n <= static_cast<unsigned int>(ep - cp));
    }
  return r;
}

//----------------------------------------------------------------------------
unsigned int EncoderBase::DataSize(
  vtkDICOMDataElementIterator iter,
  vtkDICOMDataElementIterator iterEnd)
{
  unsigned int l = 0;

  while (iter != iterEnd)
    {
    const vtkDICOMValue &v = iter->GetValue(this->Index);
    vtkDICOMVR vr = v.GetVR();
    unsigned int vl = v.GetVL();

    if (vr == vtkDICOMVR::SQ)
      {
      unsigned int n = v.GetNumberOfValues();
      const vtkDICOMItem *ptr = v.GetSequenceData();
      for (unsigned int i = 0; i < n && vl != HxFFFFFFFF; i++)
        {
        unsigned int ll = this->DataSize(ptr[i].Begin(), ptr[i].End());
        vl = (ll != HxFFFFFFFF ? vl + ll + 8 : ll);
        }
      }

    // terminate if length is unknown
    if (vl == HxFFFFFFFF)
      {
      l = vl;
      break;
      }

    // force vl to even
    assert((vl & 1) == 0);
    vl += (vl & 1);
    l += vl;
    // add length of data element header
    l += 8;
    if (!this->ImplicitVR && vr.HasLongVL())
      {
      l += 4;
      }

    ++iter;
    }

  return l;
}

//----------------------------------------------------------------------------
template<>
inline void Encoder<LE>::PutInt16(unsigned char *op, unsigned short i)
{
  op[0] = static_cast<unsigned char>(i);
  op[1] = static_cast<unsigned char>(i >> 8);
}

template<>
inline void Encoder<LE>::PutInt32(unsigned char *op, unsigned int i)
{
  op[0] = static_cast<unsigned char>(i);
  op[1] = static_cast<unsigned char>(i >> 8);
  op[2] = static_cast<unsigned char>(i >> 16);
  op[3] = static_cast<unsigned char>(i >> 24);
}

template<>
inline void Encoder<LE>::PutInt64(unsigned char *op, unsigned long long i)
{
  op[0] = static_cast<unsigned char>(i);
  op[1] = static_cast<unsigned char>(i >> 8);
  op[2] = static_cast<unsigned char>(i >> 16);
  op[3] = static_cast<unsigned char>(i >> 24);
  i >>= 32;
  op[4] = static_cast<unsigned char>(i);
  op[5] = static_cast<unsigned char>(i >> 8);
  op[6] = static_cast<unsigned char>(i >> 16);
  op[7] = static_cast<unsigned char>(i >> 24);
}

template<>
inline void Encoder<BE>::PutInt16(unsigned char *op, unsigned short i)
{
  op[0] = static_cast<unsigned char>(i >> 8);
  op[1] = static_cast<unsigned char>(i);
}

template<>
inline void Encoder<BE>::PutInt32(unsigned char *op, unsigned int i)
{
  op[0] = static_cast<unsigned char>(i >> 24);
  op[1] = static_cast<unsigned char>(i >> 16);
  op[2] = static_cast<unsigned char>(i >> 8);
  op[3] = static_cast<unsigned char>(i);
}

template<>
inline void Encoder<BE>::PutInt64(unsigned char *op, unsigned long long i)
{
  unsigned int j = static_cast<unsigned int>(i >> 32);
  op[0] = static_cast<unsigned char>(j >> 24);
  op[1] = static_cast<unsigned char>(j >> 16);
  op[2] = static_cast<unsigned char>(j >> 8);
  op[3] = static_cast<unsigned char>(j);
  j = static_cast<unsigned int>(i);
  op[4] = static_cast<unsigned char>(j >> 24);
  op[5] = static_cast<unsigned char>(j >> 16);
  op[6] = static_cast<unsigned char>(j >> 8);
  op[7] = static_cast<unsigned char>(j);
}

//----------------------------------------------------------------------------
template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const char *ip, unsigned int n)
{
  do { *op++ = static_cast<unsigned char>(*ip++); } while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const unsigned char *ip, unsigned int n)
{
  do { *op++ = *ip++; } while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const short *ip, unsigned int n)
{
  do { Encoder<E>::PutInt16(op, *ip); ip++; op += 2; } while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const unsigned short *ip, unsigned int n)
{
  do { Encoder<E>::PutInt16(op, *ip); ip++; op += 2; } while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const int *ip, unsigned int n)
{
  do { Encoder<E>::PutInt32(op, *ip); ip++; op += 4; } while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const unsigned int *ip, unsigned int n)
{
  do { Encoder<E>::PutInt32(op, *ip); ip++; op += 4; } while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const float *ip, unsigned int n)
{
  union { float f; unsigned int i; } u;

  do
    {
    u.f = *ip;
    Encoder<E>::PutInt32(op, u.i);
    ip++;
    op += 4;
    }
  while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const double *ip, unsigned int n)
{
  union { double d; unsigned long long l; } u;

  do
    {
    u.d = *ip;
    Encoder<E>::PutInt64(op, u.l);
    ip++;
    op += 8;
    }
  while (--n);
}

template<int E>
void Encoder<E>::PutValues(
  unsigned char *op, const vtkDICOMTag *ip, unsigned int n)
{
  do
    {
    Encoder<E>::PutInt16(op, ip->GetGroup());
    Encoder<E>::PutInt16(op+2, ip->GetElement());
    ip++;
    op += 4;
    }
  while (--n);
}

//----------------------------------------------------------------------------
// Write "n" elements of type "T".
template<int E>
template<class T>
bool Encoder<E>::WriteData(
  unsigned char* &cp, unsigned char* &ep, const T *ptr, unsigned int n)
{
  while (n != 0 && this->CheckBuffer(cp, ep, sizeof(T)))
    {
    unsigned int m = static_cast<unsigned int>((ep - cp)/sizeof(T));
    if (m > n) { m = n; }
    Encoder<E>::PutValues(cp, ptr, m);
    cp += m*sizeof(T);
    ptr += m;
    n -= m;
    }

  return (n == 0);
}

//----------------------------------------------------------------------------
template<int E>
unsigned int Encoder<E>::WriteElementHead(
  unsigned char* cp, vtkDICOMTag tag, vtkDICOMVR vr, unsigned int vl)
{
  const char *vrt = vr.GetText();
  unsigned int hl = 8; // data element head length
  Encoder<E>::PutInt16(cp, tag.GetGroup());
  Encoder<E>::PutInt16(cp+2, tag.GetElement());
  cp[4] = vrt[0];
  cp[5] = vrt[1];
  Encoder<E>::PutInt16(cp+6, static_cast<unsigned short>(vl));
  if (this->ImplicitVR)
    {
    Encoder<E>::PutInt32(cp+4, vl);
    }
  else if (vr.HasLongVL())
    {
    hl = 12;
    cp[6] = 0;
    cp[7] = 0;
    Encoder<E>::PutInt32(cp+8, vl);
    }
  return hl;
}

//----------------------------------------------------------------------------
template<int E>
bool Encoder<E>::WriteDataElement(
  unsigned char* &cp, unsigned char* &ep,
  const vtkDICOMDataElement &elem)
{
  vtkDICOMTag tag = elem.GetTag();
  const vtkDICOMValue &v = elem.GetValue(this->Index);
  vtkDICOMVR vr = v.GetVR();
  unsigned int vl = v.GetVL();

  // do not write invalid values
  if (!v.IsValid())
    {
    return true;
    }

  // handle elements of unknown length
  if (vl == HxFFFFFFFF)
    {
    if (vr == vtkDICOMVR::UN || vr == vtkDICOMVR::OB)
      {
      // if VR is UN then it is a sequence encoded as implicit LE
      // (see DICOM Part 5, Section 6.2.2, Unknown (UN) Value Representation)
      // if VR is OB then it is a sequence of fragments
      // (see DICOM Part 5, Annex A.4 and Table A.4-1)
      const unsigned char *ptr = v.GetUnsignedCharData();
      vl = v.GetNumberOfValues();
      // force length to even
      assert((vl & 1) == 0);
      vl += (vl & 1);
      // make sure sequence end delimiter is present
      assert(vl > 4);
      assert(ptr[vl-4] + (ptr[vl-3] << 8) == HxFFFE &&
             ptr[vl-2] + (ptr[vl-1] << 8) == HxE0DD);
      }
    else if (vr != vtkDICOMVR::SQ)
      {
      // only UN, OB, and SQ can have unknown length
      vtkDICOMCompilerInternalFriendship::CompileError(
        this->Compiler, "Illegal item length 0xFFFFFFFF encountered.");
      return false;
      }
    }
  else if (vr == vtkDICOMVR::SQ)
    {
    // compute the true vl for the sequence
    unsigned int n = v.GetNumberOfValues();
    const vtkDICOMItem *ptr = v.GetSequenceData();
    for (unsigned int i = 0; i < n && vl != HxFFFFFFFF; i++)
      {
      unsigned int ll = this->DataSize(ptr[i].Begin(), ptr[i].End());
      vl = (ll != HxFFFFFFFF ? vl + ll + 8: ll);
      }
    }
  else
    {
    // vl must be even
    assert((vl & 1) == 0);
    vl += (vl & 1);
    }

  // write the data element head (tag, vr, vl)
  if (!this->CheckBuffer(cp, ep, 12))
    {
    return false;
    }
  cp += this->Encoder<E>::WriteElementHead(cp, tag, vr, vl);

  // write the value
  bool r = true;
  switch (vr.GetType())
    {
    case VTK_CHAR:
      {
      const char *ptr = v.GetCharData();
      r = this->WriteData(cp, ep, ptr, vl);
      }
      break;
    case VTK_UNSIGNED_CHAR:
      {
      const unsigned char *ptr = v.GetUnsignedCharData();
      r = this->WriteData(cp, ep, ptr, vl);
      }
      break;
    case VTK_SHORT:
      {
      unsigned int n = vl/sizeof(short);
      const short *ptr = v.GetShortData();
      r = this->WriteData(cp, ep, ptr, n);
      }
      break;
    case VTK_UNSIGNED_SHORT:
      {
      unsigned int n = vl/sizeof(unsigned short);
      const unsigned short *ptr = v.GetUnsignedShortData();
      r = this->WriteData(cp, ep, ptr, n);
      }
      break;
    case VTK_INT:
      {
      unsigned int n = vl/sizeof(int);
      const int *ptr = v.GetIntData();
      r = this->WriteData(cp, ep, ptr, n);
      }
      break;
    case VTK_UNSIGNED_INT:
      {
      unsigned int n = vl/sizeof(unsigned int);
      const unsigned int *ptr = v.GetUnsignedIntData();
      r = this->WriteData(cp, ep, ptr, n);
      }
      break;
    case VTK_FLOAT:
      {
      unsigned int n = vl/sizeof(float);
      const float *ptr = v.GetFloatData();
      r = this->WriteData(cp, ep, ptr, n);
      }
      break;
    case VTK_DOUBLE:
      {
      unsigned int n = vl/sizeof(double);
      const double *ptr = v.GetDoubleData();
      r = this->WriteData(cp, ep, ptr, n);
      }
      break;
    case VTK_DICOM_TAG:
      {
      unsigned int n = vl/sizeof(vtkDICOMTag);
      const vtkDICOMTag *ptr = v.GetTagData();
      r = this->WriteData(cp, ep, ptr, n);
      }
      break;
    case VTK_DICOM_ITEM:
      {
      unsigned int n = v.GetNumberOfValues();
      const vtkDICOMItem *ptr = v.GetSequenceData();

      for (unsigned int i = 0; i < n && r; i++)
        {
        unsigned int il = 0xFFFFFFFF;
        if (!ptr[i].IsDelimited())
          {
          // compute the bytes in the item
          il = this->DataSize(ptr[i].Begin(), ptr[i].End());
          }

        if ((r = this->CheckBuffer(cp, ep, 8)) == false)
          {
          break;
          }
        // item start
        Encoder<E>::PutInt16(cp, HxFFFE);
        Encoder<E>::PutInt16(cp+2, HxE000);
        Encoder<E>::PutInt32(cp+4, il);
        cp += 8;

        this->Depth++;
        r = this->WriteElements(cp, ep, ptr[i].Begin(), ptr[i].End());
        this->Depth--;

        if (il == HxFFFFFFFF && r)
          {
          if ((r = this->CheckBuffer(cp, ep, 8)) == false)
            {
            break;
            }
          // item delimiter
          Encoder<E>::PutInt16(cp, HxFFFE);
          Encoder<E>::PutInt16(cp+2, HxE00D);
          Encoder<E>::PutInt32(cp+4, 0);
          cp += 8;
          }
        }

      if (vl == HxFFFFFFFF && r)
        {
        if ((r = this->CheckBuffer(cp, ep, 8)) != false)
          {
          // sequence delimiter
          Encoder<E>::PutInt16(cp, HxFFFE);
          Encoder<E>::PutInt16(cp+2, HxE0DD);
          Encoder<E>::PutInt32(cp+4, 0);
          cp += 8;
          }
        }
      }
      break;
    }

  return r;
}

//----------------------------------------------------------------------------
template<int E>
bool Encoder<E>::WriteElements(
  unsigned char* &cp, unsigned char* &ep,
  vtkDICOMDataElementIterator iter,
  vtkDICOMDataElementIterator iterEnd)
{
  while (iter != iterEnd)
    {
    // check for group length tag
    if (iter->GetTag().GetElement() == Hx0000)
      {
      unsigned short group = iter->GetTag().GetGroup();
      vtkDICOMDataElementIterator groupEnd = ++iter;
      while (groupEnd != iterEnd && groupEnd->GetTag().GetGroup() == group)
        {
        ++groupEnd;
        }
      unsigned int l = this->DataSize(iter, groupEnd);
      // check for uncounted PixelData element size in 0x7FE0 group
      if (l != HxFFFFFFFF && group == 0x7FE0 && iter == groupEnd)
        {
        // add the size of the missing PixelData element
        unsigned int pl =
          vtkDICOMCompilerInternalFriendship::ComputePixelDataSize(
            this->Compiler);
        unsigned int hl = (this->ImplicitVR ? 8 : 12);
        l += (pl != HxFFFFFFFF ? l + pl + hl : pl);
        }
      if (l != HxFFFFFFFF)
        {
        // write out group length tag with correct value
        this->WriteDataElement(cp, ep,
          vtkDICOMDataElement(
            vtkDICOMTag(group, Hx0000),
            vtkDICOMValue(vtkDICOMVR::UL, l)));
        }
      // check for and remove retired LengthToEnd tag
      if (iter != iterEnd && iter->GetTag() == vtkDICOMTag(0x0008, 0x0001))
        {
        ++iter;
        }
      }
    else if (this->Depth == 0 && this->SOPInstanceUID &&
             iter->GetTag() == vtkDICOMTag(DC::SOPInstanceUID))
      {
      this->WriteDataElement(cp, ep,
        vtkDICOMDataElement(
          vtkDICOMTag(DC::SOPInstanceUID),
          vtkDICOMValue(vtkDICOMVR::UI, this->SOPInstanceUID)));
      ++iter;
      }
    else if (this->Depth == 0 && this->SeriesInstanceUID &&
             iter->GetTag() == vtkDICOMTag(DC::SeriesInstanceUID))
      {
      this->WriteDataElement(cp, ep,
        vtkDICOMDataElement(
          vtkDICOMTag(DC::SeriesInstanceUID),
          vtkDICOMValue(vtkDICOMVR::UI, this->SeriesInstanceUID)));
      ++iter;
      }
    else if (this->Depth == 0 && this->StudyInstanceUID &&
             iter->GetTag() == vtkDICOMTag(DC::StudyInstanceUID))
      {
      this->WriteDataElement(cp, ep,
        vtkDICOMDataElement(
          vtkDICOMTag(DC::StudyInstanceUID),
          vtkDICOMValue(vtkDICOMVR::UI, this->StudyInstanceUID)));
      ++iter;
      }
    else
      {
      this->WriteDataElement(cp, ep, *iter);
      ++iter;
      }
    }

  return true;
}

} // end anonymous namespace

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Constructor
vtkDICOMCompiler::vtkDICOMCompiler()
{
  this->FileName = NULL;
  this->SOPInstanceUID = NULL;
  this->SeriesInstanceUID = NULL;
  this->StudyInstanceUID = NULL;
  this->ImplementationClassUID = NULL;
  this->ImplementationVersionName = NULL;
  this->SourceApplicationEntityTitle = NULL;
  this->TransferSyntaxUID = NULL;
  this->MetaData = NULL;
  this->OutputStream = NULL;
  this->Buffer = NULL;
  this->BufferSize = 8192;
  this->ChunkSize = 0;
  this->Index = 0;
  this->FrameCounter = 0;
  this->BigEndian = 0;
  this->Compressed = 0;
  this->KeepOriginalPixelDataVR = 0;
  this->ErrorCode = 0;
  this->SeriesUIDs = 0;

  // This is our default implementation UID
  const char *impuid =
    vtkDICOMUtilities::GetImplementationClassUID();
  this->ImplementationClassUID = new char[strlen(impuid) + 1];
  strcpy(this->ImplementationClassUID, impuid);

  // This is our default implementation name
  const char *impname =
    vtkDICOMUtilities::GetImplementationVersionName();
  this->ImplementationVersionName = new char[strlen(impname) + 1];
  strcpy(this->ImplementationVersionName, impname);

  // This is our default transfer syntax
  const char *tsyntax = "1.2.840.10008.1.2.1";
  this->TransferSyntaxUID = new char[strlen(tsyntax) + 1];
  strcpy(this->TransferSyntaxUID, tsyntax);
}

//----------------------------------------------------------------------------
// Destructor
vtkDICOMCompiler::~vtkDICOMCompiler()
{
  this->Close();

  delete [] this->FileName;
  delete [] this->SOPInstanceUID;
  delete [] this->SeriesInstanceUID;
  delete [] this->StudyInstanceUID;
  delete [] this->ImplementationClassUID;
  delete [] this->ImplementationVersionName;
  delete [] this->SourceApplicationEntityTitle;
  delete [] this->TransferSyntaxUID;

  if (this->MetaData)
    {
    this->MetaData->Delete();
    }
  if (this->SeriesUIDs)
    {
    this->SeriesUIDs->Delete();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::SetBufferSize(int size)
{
  if (size < 256)
    {
    size = 256;
    }
  if (size > (2147483647 - 8))
    {
    size = (2147483647 - 8);
    }

  if (this->BufferSize != size)
    {
    this->BufferSize = size;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::GenerateSeriesUIDs()
{
  if (this->SeriesUIDs == 0)
    {
    this->SeriesUIDs = vtkStringArray::New();
    }

  this->SeriesUIDs->Initialize();
  if (this->MetaData)
    {
    int n = this->MetaData->GetNumberOfInstances();
    this->SeriesUIDs->SetNumberOfValues(n + 1); // allocate n+1
    this->SeriesUIDs->SetNumberOfValues(n); // but set to n values
    vtkDICOMUtilities::GenerateUIDs(DC::SOPInstanceUID, this->SeriesUIDs);
    this->SeriesUIDs->InsertNextValue(
      vtkDICOMUtilities::GenerateUID(DC::SeriesInstanceUID));
    }

  // study UID is only generated once per session
  if (vtkDICOMCompiler::StudyUID[0] == '\0')
    {
    std::string uid = vtkDICOMUtilities::GenerateUID(DC::StudyInstanceUID);
    strcpy(vtkDICOMCompiler::StudyUID, uid.c_str());
    }
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::WriteHeader()
{
  this->FrameCounter = 0;
  this->WriteFile(this->MetaData, this->Index);
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::Close()
{
  if (this->OutputStream)
    {
    delete this->OutputStream;
    this->OutputStream = NULL;
    }
}

//----------------------------------------------------------------------------
bool vtkDICOMCompiler::WriteFile(vtkDICOMMetaData *data, int idx)
{
  // Check that the file name has been set.
  if (!this->FileName)
    {
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    vtkErrorMacro("WriteFile: No file name has been set");
    return false;
    }

  // Generate fresh UIDs if at index zero
  if (idx == 0 || this->SeriesUIDs == 0 ||
      this->SeriesUIDs->GetNumberOfValues() !=
      data->GetNumberOfInstances() + 1)
    {
    this->GenerateSeriesUIDs();
    }

  // Remove the file if it exists, just in case it is a hard link
  // to a file elsewhere on the filesystem.
  struct stat fs;
  if (stat(this->FileName, &fs))
    {
    unlink(this->FileName);
    }

  this->OutputStream =
    new std::ofstream(this->FileName, ios::out | ios::binary);

  if (this->OutputStream->fail())
    {
    this->Close();
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("WriteFile: Can't open the file " << this->FileName);
    return false;
    }

  this->Buffer = new char [this->BufferSize];
  // guard against anyone changing BufferSize while compiling the file
  this->ChunkSize = this->BufferSize;

  unsigned char *cp = reinterpret_cast<unsigned char *>(this->Buffer);
  unsigned char *ep = cp + this->ChunkSize;

  // variable to keep track of return values
  bool r = true;

  // only write preamble and meta header if transfer syntax is set
  if (this->TransferSyntaxUID != 0)
    {
    // write the preamble
    memset(cp, '\0', 128);
    cp += 128;
    cp[0] = 'D';
    cp[1] = 'I';
    cp[2] = 'C';
    cp[3] = 'M';
    cp += 4;

    r = this->WriteMetaHeader(cp, ep, data, idx);
    }
  if (r)
    {
    r = this->WriteMetaData(cp, ep, data, idx);
    }
  if (r)
    {
    r = this->FlushBuffer(cp, ep);
    }

  delete [] this->Buffer;

  // delete the file if an error occurred
  if (!r)
    {
    this->Close();
    unlink(this->FileName);

    if (this->GetErrorCode() == vtkErrorCode::NoError)
      {
      this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
      vtkErrorMacro("Error while writing file "
                    << this->FileName << ": Out of disk space.");
      }
    }

  return r;
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::WritePixelData(const char *cp, vtkIdType size)
{
  this->OutputStream->write(cp, size);
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::WriteFrame(const char *cp, vtkIdType size)
{
  union { char c[2]; short s; } endiancheck;
  // this will set endiancheck.s to 1 on little endian architectures
  endiancheck.c[0] = 1;
  endiancheck.c[1] = 0;

  if (this->Compressed)
    {
    // Compressed frames

    // Offset table:
    // - Item tag (FFFE, E000)
    // - Length of table in bytes (4 bytes)
    // - Offset to frame 2 (4 bytes) ...

    // Fragment
    // - Item tag (FFFE, E000)
    // - Length of item in bytes (4 bytes)
    // - Fragment data

    // After final fragment:
    // - Sequence delimiter tag (FFFE, E0DD)
    // - Empty size (4 bytes of zeros)

    // The entire compressed PixelData must be buffered in memory
    // in order for the offset table to be filled in.

    if (this->ErrorCode == 0)
      {
      this->SetErrorCode(vtkErrorCode::FileFormatError);
      vtkErrorMacro("Writing compressed DICOM is not supported.");
      }
    }
  else if (((this->BigEndian != 0) ^ (endiancheck.s != 1)) &&
           this->MetaData->GetAttributeValue(DC::BitsAllocated).AsInt() > 8)
    {
    // Swap bytes before writing
    char *buf = new char[size];
    char *dp = buf;
    for (vtkIdType i = 0; i < size; i += 2)
      {
      dp[0] = cp[1];
      dp[1] = cp[0];
      dp += 2;
      cp += 2;
      }
    this->OutputStream->write(buf, size);
    delete [] buf;
    }
  else
    {
    // For uncompressed frames, write the data raw
    this->OutputStream->write(cp, size);
    }

  this->FrameCounter++;
}

//----------------------------------------------------------------------------
bool vtkDICOMCompiler::WriteMetaHeader(
  unsigned char* &cp, unsigned char* &ep,
  vtkDICOMMetaData *meta, int idx)
{
  // if no transfer syntax is set, do not write header
  if (this->TransferSyntaxUID == 0)
    {
    return true;
    }

  // create the encoder
  LittleEndianEncoder encoder(this, idx);

  unsigned int l = 0; // length will be computed later
  unsigned char metaver[2] = { 0, 1 }; // meta header version
  const char *instanceUID = this->SOPInstanceUID;
  const char *implementationUID = this->ImplementationClassUID;

  // use the same class as the input meta data
  // Secondary Capture is 1.2.840.10008.5.1.4.1.1.7
  std::string classUIDString =
    meta->GetAttributeValue(DC::SOPClassUID).AsString();
  const char *classUID = classUIDString.c_str();

  if (instanceUID == 0)
    {
    instanceUID = this->SeriesUIDs->GetValue(idx);
    }
  if (implementationUID == 0)
    {
    implementationUID =
      vtkDICOMUtilities::GetImplementationClassUID();
    }

  vtkDICOMItem item;
  item.SetAttributeValue(
    DC::FileMetaInformationGroupLength,
    vtkDICOMValue(vtkDICOMVR::UL, l));
  item.SetAttributeValue(
    DC::FileMetaInformationVersion,
    vtkDICOMValue(vtkDICOMVR::OB, metaver, metaver+2));
  item.SetAttributeValue(
    DC::MediaStorageSOPClassUID,
    vtkDICOMValue(vtkDICOMVR::UI, classUID));
  item.SetAttributeValue(
    DC::MediaStorageSOPInstanceUID,
    vtkDICOMValue(vtkDICOMVR::UI, instanceUID));
  item.SetAttributeValue(
    DC::TransferSyntaxUID,
    vtkDICOMValue(vtkDICOMVR::UI, this->TransferSyntaxUID));
  item.SetAttributeValue(
    DC::ImplementationClassUID,
    vtkDICOMValue(vtkDICOMVR::UI, implementationUID));

  if (this->ImplementationVersionName)
    {
    item.SetAttributeValue(
      DC::ImplementationVersionName,
      vtkDICOMValue(vtkDICOMVR::SH,
                    this->ImplementationVersionName));
    }

  if (this->SourceApplicationEntityTitle)
    {
    item.SetAttributeValue(
      DC::SourceApplicationEntityTitle,
      vtkDICOMValue(vtkDICOMVR::AE,
                    this->SourceApplicationEntityTitle));
    }

  vtkDICOMDataElementIterator iter = item.Begin();
  vtkDICOMDataElementIterator iterEnd = item.End();

  if (iter != iterEnd)
    {
    encoder.WriteElements(cp, ep, iter, iterEnd);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMCompiler::WriteMetaData(
  unsigned char* &cp, unsigned char* &ep,
  vtkDICOMMetaData *meta, int idx)
{
  // the encoders to choose from
  LittleEndianEncoder encoderLE(this, idx);
  BigEndianEncoder encoderBE(this, idx);
  EncoderBase *encoder = &encoderLE;
  this->Compressed = false;
  this->BigEndian = false;

  // anything not listed here is assumed to be Explicit LE
  std::string tsyntax =
    (this->TransferSyntaxUID ? this->TransferSyntaxUID : "");
  if (tsyntax == "" || // If no meta header, use Implicit LE
      tsyntax == "1.2.840.10008.1.2" ||  // Implicit LE
      tsyntax == "1.2.840.10008.1.20")   // Papyrus Implicit LE
    {
    encoder->SetImplicitVR(true);
    }
  else if (tsyntax == "1.2.840.10008.1.2.2") // Explicit BE
    {
    encoder = &encoderBE;
    this->BigEndian = true;
    }
  else if (tsyntax == "1.2.840.113619.5.2")  // GE LE with BE data
    {
    this->BigEndian = true;
    }
  else if (tsyntax != "1.2.840.10008.1.2.1") // Explicit LE
    {
    this->Compressed = true;
    }

  const char *instanceUID = this->SOPInstanceUID;
  const char *seriesUID = this->SeriesInstanceUID;
  const char *studyUID = this->StudyInstanceUID;

  if (instanceUID == 0)
    {
    instanceUID = this->SeriesUIDs->GetValue(idx);
    }
  if (seriesUID == 0)
    {
    seriesUID = this->SeriesUIDs->GetValue(this->SeriesUIDs->GetMaxId());
    }
  if (studyUID == 0 &&
      meta->GetAttributeValue(DC::StudyInstanceUID).AsString() == "")
    {
    studyUID = vtkDICOMCompiler::StudyUID;
    }

  encoder->SetSOPInstanceUID(instanceUID);
  encoder->SetSeriesInstanceUID(seriesUID);
  encoder->SetStudyInstanceUID(studyUID);

  vtkDICOMDataElementIterator iter = meta->Begin();
  vtkDICOMDataElementIterator iterEnd = meta->End();

  // skip past the meta header
  while (iter != iterEnd && iter->GetTag().GetGroup() == 0x0002)
    {
    ++iter;
    }

  // if last element is PixelData, don't write it yet
  bool hasPixelData = false;
  if (iterEnd != iter)
    {
    vtkDICOMDataElementIterator finalElement = iterEnd;
    --finalElement;
    if (finalElement->GetTag() == vtkDICOMTag(DC::PixelData))
      {
      iterEnd = finalElement;
      hasPixelData = true;
      }
    }

  // write the meta data, get boolean status value
  bool r = encoder->WriteElements(cp, ep, iter, iterEnd);

  // write the PixelData element head
  if (r && hasPixelData &&
      (r = encoder->CheckBuffer(cp, ep, 12)) != false)
    {
    vtkDICOMVR vr = vtkDICOMVR::OW;
    int bitsAllocated = this->MetaData->GetAttributeValue(
      DC::BitsAllocated).AsInt();
    if ((bitsAllocated > 0 && bitsAllocated <= 8) || this->Compressed)
      {
      vr = vtkDICOMVR::OB;
      }

    if (this->KeepOriginalPixelDataVR)
      {
      vtkDICOMVR vrOriginal = this->MetaData->GetAttributeValue(
        idx, DC::PixelData).GetVR();
      if (vrOriginal.IsValid())
        {
        vr = vrOriginal;
        }
      }

    unsigned int vl = this->ComputePixelDataSize();

    // write the data element head
    unsigned int l = encoder->WriteElementHead(
      cp, vtkDICOMTag(DC::PixelData), vr, vl);
    cp += l;
    }

  return r;
}

//----------------------------------------------------------------------------
unsigned int vtkDICOMCompiler::ComputePixelDataSize()
{
  unsigned int vl = HxFFFFFFFF;
  if (!this->Compressed)
    {
    // compute the size
    vtkDICOMMetaData *meta = this->MetaData;
    int bitsAllocated = meta->GetAttributeValue(
      this->Index, DC::BitsAllocated).AsInt();
    if (bitsAllocated > 0)
      {
      vl = meta->GetAttributeValue(
        this->Index, DC::Columns).AsUnsignedInt();
      vl *= meta->GetAttributeValue(
        this->Index, DC::Rows).AsUnsignedInt();
      unsigned int m = meta->GetAttributeValue(
        this->Index, DC::SamplesPerPixel).AsUnsignedInt();
      unsigned int n = meta->GetAttributeValue(
        this->Index, DC::NumberOfFrames).AsUnsignedInt();
      vl *= ((m > 1) ? m : 1);
      vl *= ((n > 1) ? n : 1);
      if (bitsAllocated % 8 == 0)
        {
        vl *= bitsAllocated/8;
        }
      else
        {
        // this will only occur in ancient data
        vl = (vl*bitsAllocated + 7)/8;
        vl += (vl & 1); // make it even
        }
      }
    }

  return vl;
}

//----------------------------------------------------------------------------
bool vtkDICOMCompiler::FlushBuffer(
  unsigned char* &ucp, unsigned char* &)
{
  const char *cp = reinterpret_cast<const char *>(ucp);
  char *dp = this->Buffer;
  ucp = reinterpret_cast<unsigned char *>(dp);
  std::streamsize n = static_cast<std::streamsize>(cp - dp);

  this->OutputStream->write(dp, n);

  return this->OutputStream->good();
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::CompileError(const char* message)
{
  this->SetErrorCode(vtkErrorCode::FileFormatError);
  vtkErrorMacro("Error while writing file "
                << this->FileName << ": " << message);
}

//----------------------------------------------------------------------------
void vtkDICOMCompiler::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "FileName: "
     << (this->FileName ? this->FileName : "(NULL)") << "\n";
  os << indent << "SOPInstanceUID: "
     << (this->SOPInstanceUID ? this->SOPInstanceUID : "(NULL)") << "\n";
  os << indent << "SeriesInstanceUID: "
     << (this->SeriesInstanceUID ? this->SeriesInstanceUID : "(NULL)")
     << "\n";
  os << indent << "StudyInstanceUID: "
     << (this->StudyInstanceUID ? this->StudyInstanceUID : "(NULL)")
     << "\n";
  os << indent << "ImplementationClassUID: "
     << (this->ImplementationClassUID ?
         this->ImplementationClassUID : "(NULL)") << "\n";
  os << indent << "ImplementationVersionName: "
     << (this->ImplementationVersionName ?
         this->ImplementationVersionName : "(NULL)") << "\n";
  os << indent << "SourceApplicationEntityTitle: "
     << (this->SourceApplicationEntityTitle ?
         this->SourceApplicationEntityTitle : "(NULL)") << "\n";
  os << indent << "TransferSyntaxUID: "
     << (this->TransferSyntaxUID ? this->TransferSyntaxUID : "(NULL)") << "\n";
  os << indent << "MetaData: " << this->MetaData << "\n";
  os << indent << "Index: " << this->Index << "\n";
  os << indent << "BufferSize: " << this->BufferSize << "\n";
  os << indent << "KeepOriginalPixelDataVR: "
     << (this->KeepOriginalPixelDataVR ? "On\n" : "Off\n");
}
