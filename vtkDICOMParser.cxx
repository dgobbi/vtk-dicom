/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMParser.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include <vtkObjectFactory.h>
#include <vtkUnsignedShortArray.h>
#include <vtkErrorCode.h>

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <assert.h>

#include <string>

vtkStandardNewMacro(vtkDICOMParser);
vtkCxxSetObjectMacro(vtkDICOMParser, MetaData, vtkDICOMMetaData);
vtkCxxSetObjectMacro(vtkDICOMParser, Groups, vtkUnsignedShortArray);

/*----------------------------------------------------------------------------
The top section of this file defines "Decoder" classes that parse the
DICOM tags and decode the values.  The decoder class hierarchy is as
follows:

DecoderBase (the base class)
    Decoder<LE> (template specialization for little-endian decoding)
        DefaultDecoder (decoder for implicit little-endian syntax)
        LittleEndianDecoder (decoder for explicit little-endian syntax)
    Decoder<GE> (template specialization for big-endian decoding)
        BigEndianDecoder (decoder for explicit big-endian syntax)

The vtkDICOMParser utilizes the DefaultDecoder, LittleEndianDecoder,
or the BigEndianDecoder depending on the transfer syntax.
----------------------------------------------------------------------------*/

class vtkDICOMParserInternalFriendship
{
public:
  static bool FillBuffer(vtkDICOMParser *parser,
    const unsigned char* &cp, const unsigned char* &ep)
  {
    return parser->FillBuffer(cp, ep);
  }

  static std::streamsize GetBytesRemaining(vtkDICOMParser *parser,
    const unsigned char *cp, const unsigned char *ep)
  {
    return parser->GetBytesRemaining(cp, ep);
  }

  static void ParseError(vtkDICOMParser *parser,
    const unsigned char *cp, const unsigned char *ep, const char *message)
  {
    return parser->ParseError(cp, ep, message);
  }

};

namespace {

// Useful constants to replace commonly-used literals.
const unsigned short HxFFFE = 0xFFFE; // sequence group
const unsigned short HxE000 = 0xE000; // item start
const unsigned short HxE00D = 0xE00D; // item end
const unsigned short HxE0DD = 0xE0DD; // sequence end
const unsigned int HxFFFFFFFF = 0xFFFFFFFF; // unknown length

// The decoder has two specializations: little-endian, big-endian.
const int LE = 0;
const int BE = 1;

// The decoder types that are available.
class DefaultDecoder;
class LittleEndianDecoder;
class BigEndianDecoder;

// The base class for the decoder classes.
class DecoderBase
{
public:
  // Whether to use implicit VRs (default: explicit VRs).
  void SetImplicitVR(bool i) { this->ImplicitVR = i; }

  // The Item member variable is set while a sequence is decoded.
  void SetItem(vtkDICOMItem *i);

  // Read l bytes of data, or until delimiter tag found.
  // Set l to 0xffffffff to ignore length completely.
  // If the delimiter is of the form (0xgggg,0x0000), ie. if the
  // "element" part is zero, then the reading will stop before
  // the first element that is not in the specified group.
  virtual bool ReadElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter) = 0;

  // Skip l bytes of data, or until delimiter tag found.
  // Set l to 0xffffffff to ignore length completely.
  // If the delimiter is of the form (0xgggg,0x0000), ie. if the
  // "element" part is zero, then the skip will stop before
  // the first element that is not in the specified group.
  virtual bool SkipElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter) = 0;

  // Peek ahead to see what the group of the next element is.
  virtual unsigned short PeekGroup(
    const unsigned char* &cp, const unsigned char* &ep) = 0;

  // Copy bytes from sp to end marker cp into the value "v".
  // If the parameter "v" is NULL, then it will be ignored.
  void CopyBuffer(
    vtkDICOMValue *v, const unsigned char *sp, const unsigned char *cp);

  // If there are fewer than "n" bytes left in the buffer, then move
  // any data that hasn't yet been parsed to the start of the buffer,
  // and then read new data into the remainder of the buffer.
  bool CheckBuffer(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int n);

  // This overload of CheckBuffer is used within SkipElements to
  // automatically copy the skipped bytes into the value "v".
  // If the parameter "v" is NULL, then it will be ignored.
  bool CheckBuffer(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int n, vtkDICOMValue *v, const unsigned char* &sp);

  // Find an element within the current context.  This is used
  // by FindDictVR() to disambiguate VRs that could be either US
  // or SS, or that could be either OB or OW.
  bool GetAttributeValue(vtkDICOMTag tag, vtkDICOMValue &v);
  bool GetAttributeValue(vtkDICOMTag tag, unsigned short &u);

  // Get the dictionary VR (for implicit VR elements).
  // If the tag is not found, UN (unknown) will be returned.
  vtkDICOMVR FindDictVR(vtkDICOMTag tag);

  // Get the last tag that was read.
  vtkDICOMTag GetLastTag() { return this->LastTag; }

  // Get the VR of the last data element.
  vtkDICOMVR GetLastVR() { return this->LastVR; }

  // Check for attributes missing from this instance, that were present
  // for instances in the series that were already parsed.
  void HandleMissingAttributes(vtkDICOMTag tag);

protected:
  // Constructor that initializes all of the members.
  DecoderBase(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Parser(parser), Item(0), MetaData(data), Index(idx), ImplicitVR(0) {}

  // an internal implicit little-endian decoder
  DefaultDecoder *ImplicitLE;
  // the vtkDICOMParser::FillBuffer method is used to refill the buffer
  vtkDICOMParser *Parser;
  // the sequence item to read the data into while parsing a sequence
  vtkDICOMItem *Item;
  // the metadata object to read the data into
  vtkDICOMMetaData *MetaData;
  // the instance index to use with the meta data
  int Index;
  // if this is set, then VRs are implicit
  bool ImplicitVR;
  // this is set to the last tag that was read.
  vtkDICOMVR  LastVR;
  vtkDICOMTag LastTag;
  // this is set to the last tag written to this->MetaData
  vtkDICOMTag LastWrittenTag;
};

//----------------------------------------------------------------------------
template<int E>
class Decoder : public DecoderBase
{
public:
  // Decode two, four, or eight bytes as unsigned integers.
  static unsigned short GetInt16(const unsigned char* ip);
  static unsigned int GetInt32(const unsigned char* ip);
  static unsigned long long GetInt64(const unsigned char* ip);

  // Read from "ip" and write "n" decoded values into "v".
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
  static void GetValues(const unsigned char *ip, vtkDICOMTag *v, unsigned int n);

  // Read "n" values from the buffer into the provided pointer.
  // The number of bytes that were read from the buffer will be returned.
  // The buffer will be refilled as necessary.
  template<class T>
  unsigned int ReadData(
    const unsigned char* &cp, const unsigned char* &ep,
    T *ptr, unsigned int n);

  // Skip forward by "n" bytes.  The number of bytes skipped will be
  // returned.  If the end of the file is reached before the operation,
  // is complete, then the return value will be less than "n".
  unsigned int SkipData(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int n);

  // Read l bytes of data, or until delimiter tag found.
  // Set l to 0xffffffff to ignore length completely.
  // If the delimiter is of the form (0xgggg,0x0000), ie. if the
  // "element" part is zero, then the reading will stop before
  // the first element that is not in the specified group.
  bool ReadElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter)
  {
    unsigned int bytesRead;
    return ReadElements(cp, ep, l, delimiter, bytesRead);
  }

  // Skip l bytes of data, or until delimiter tag found.
  // Set l to 0xffffffff to ignore length completely.
  // If the delimiter is of the form (0xgggg,0x0000), ie. if the
  // "element" part is zero, then the skip will stop before
  // the first element that is not in the specified group.
  bool SkipElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter)
  {
    return SkipElements(cp, ep, l, delimiter, 0);
  }

  // A ReadElements that returns the number of bytes read.
  bool ReadElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter, unsigned int &bytesRead);

  // A SkipElements that copies skipped bytes into value "v".
  // This method is used when parsing encapsulated data, it simply
  // reads the encapsulated data into the value as raw bytes.
  // If the parameter "v" is NULL, then it will be ignored.
  bool SkipElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter, vtkDICOMValue *v);

  // Read the vr and vl and return the number of bytes read
  // (will return zero if an error occurred)
  unsigned int ReadElementHead(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMTag tag, vtkDICOMVR &vr, unsigned int &vl);

  // Read a value, given the vr and vl, where vl can be 0xffffffff
  // for SQ, UN, or OB to indicate tag-delimited data.
  // The number of bytes that were read will be returned.
  unsigned int ReadElementValue(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMVR vr, unsigned int vl, vtkDICOMValue &v);

  // Peek ahead to see what the group of the next element is.
  unsigned short PeekGroup(
    const unsigned char* &cp, const unsigned char* &ep)
  {
    unsigned short g = 0;
    if (this->CheckBuffer(cp, ep, 2))
      {
      g = Decoder<E>::GetInt16(cp);
      }
    return g;
  }

protected:
  Decoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    DecoderBase(parser, data, idx) {}

private:
  Decoder() {};
};

//----------------------------------------------------------------------------
// The little-endian implicit-vr decoder.
class DefaultDecoder : public Decoder<LE>
{
public:
  DefaultDecoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Decoder<LE>(parser, data, idx)
  {
    this->ImplicitVR = true;
    this->ImplicitLE = this;
  }
};

// The little-endian explicit-vr decoder.
class LittleEndianDecoder : public Decoder<LE>
{
public:
  LittleEndianDecoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Decoder<LE>(parser, data, idx), ExtraDecoder(parser, data, idx)
  {
    this->ImplicitLE = &this->ExtraDecoder;
  }

private:
  // an internal implicit little-endian decoder.
  DefaultDecoder ExtraDecoder;
};

// The big-endian explicit-vr decoder.
class BigEndianDecoder : public Decoder<BE>
{
public:
  BigEndianDecoder(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Decoder<BE>(parser, data, idx), ExtraDecoder(parser, data, idx)
  {
    this->ImplicitLE = &this->ExtraDecoder;
  }

private:
  // an internal implicit little-endian decoder.
  DefaultDecoder ExtraDecoder;
};

//----------------------------------------------------------------------------
inline void DecoderBase::SetItem(vtkDICOMItem *i)
{
  // ensure that "Item" is set for the ImplicitLE decoder, too
  this->Item = i;
  this->ImplicitLE->Item = i;
}

//----------------------------------------------------------------------------
inline void DecoderBase::CopyBuffer(
  vtkDICOMValue *v, const unsigned char *sp, const unsigned char *cp)
{
  // append bytes from sp to cp into the supplied value "v"
  if (v && cp != sp)
    {
    unsigned int m = static_cast<unsigned int>(cp - sp);
    unsigned int n = v->GetNumberOfValues();
    unsigned char *ptr = v->ReallocateUnsignedCharData(n + m) + n;
    do { *ptr++ = *sp++; } while (--m);
    }
}

//----------------------------------------------------------------------------
inline bool DecoderBase::CheckBuffer(
  const unsigned char* &cp, const unsigned char* &ep,
  unsigned int n)
{
  bool r = true;
  if (n > static_cast<unsigned int>(ep - cp))
    {
    r = vtkDICOMParserInternalFriendship::FillBuffer(
          this->Parser, cp, ep);
    r &= (n <= static_cast<unsigned int>(ep - cp));
    }
  return r;
}

inline bool DecoderBase::CheckBuffer(
  const unsigned char* &cp, const unsigned char* &ep,
  unsigned int n, vtkDICOMValue *v, const unsigned char* &sp)
{
  bool r = true;
  if (n > static_cast<unsigned int>(ep - cp))
    {
    this->CopyBuffer(v, sp, cp);
    r = vtkDICOMParserInternalFriendship::FillBuffer(
          this->Parser, cp, ep);
    r &= (n <= static_cast<unsigned int>(ep - cp));
    sp = cp;
    }
  return r;
}

//----------------------------------------------------------------------------
bool DecoderBase::GetAttributeValue(vtkDICOMTag tag, vtkDICOMValue &v)
{
  v.Clear();
  if (this->Item)
    {
    v = this->Item->GetAttributeValue(tag);
    }
  else if (this->MetaData)
    {
    int idx = (this->Index == -1 ? 0 : this->Index);
    v = this->MetaData->GetAttributeValue(idx, tag);
    }
  return v.IsValid();
}

bool DecoderBase::GetAttributeValue(vtkDICOMTag tag, unsigned short &u)
{
  // get the value as an unsigned short
  vtkDICOMValue v;
  if (this->GetAttributeValue(tag, v))
    {
    u = v.AsShort();
    return true;
    }

  return false;
}

//----------------------------------------------------------------------------
vtkDICOMVR DecoderBase::FindDictVR(vtkDICOMTag tag)
{
  vtkDICOMVR vr = vtkDICOMVR::UN;

  if (tag.GetElement() == 0x0000)
    {
    // this is a group length element, which has VR of "UL"
    vr = vtkDICOMVR::UL;
    }
  else if ((tag.GetGroup() & 0x1) != 0 &&
           tag.GetElement() >= 0x0010 && tag.GetElement() < 0x0100)
    {
    // this is a private creator tag
    vr = vtkDICOMVR::LO;
    }
  else
    {
    vtkDICOMDictEntry de;
    if ((tag.GetGroup() & 0x1) == 0)
      {
      de = vtkDICOMDictionary::FindDictEntry(tag);
      }
    else if (this->Item)
      {
      de = this->Item->FindDictEntry(tag);
      }
    else if (this->MetaData)
      {
      de = this->MetaData->FindDictEntry(tag);
      }
    if (de.IsValid())
      {
      vr = de.GetVR();
      if (vr == vtkDICOMVR::XS)
        {
        // disambiguate tags that may be either "US" or "SS"
        unsigned short r;
        vr = vtkDICOMVR::US;
        if (this->GetAttributeValue(DC::PixelRepresentation, r))
          {
          vr = (r == 0 ? vtkDICOMVR::US : vtkDICOMVR::SS);
          }
        }
      else if (vr == vtkDICOMVR::OX)
        {
        // disambiguate tags that may be either "OB" or "OW"
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
    }

  return vr;
}

//----------------------------------------------------------------------------
void DecoderBase::HandleMissingAttributes(vtkDICOMTag tag)
{
  // insert null values for any attributes that were present for other
  // instances in this series but not present for this instance
  vtkDICOMDataElementIterator iter = this->MetaData->Find(tag);
  --iter;
  if (iter->GetTag() != this->LastWrittenTag &&
      iter->GetTag().GetGroup() != 0x0002)
    {
    int count = 0;
    do
      {
      count++;
      --iter;
      }
    while (iter->GetTag() != this->LastWrittenTag &&
           iter->GetTag().GetGroup() != 0x0002);

    vtkDICOMTag *missing = new vtkDICOMTag[count];
    for (int i = 0; i < count; i++)
      {
      missing[i] = (++iter)->GetTag();
      }
    for (int i = 0; i < count; i++)
      {
      this->MetaData->SetAttributeValue(
        this->Index, missing[i], vtkDICOMValue());
      }
    delete [] missing;
    }
  this->LastWrittenTag = tag;
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
  return (((((ip[0] << 8) + ip[1]) << 8) + ip[2]) << 8) + ip[3];
}

template<>
inline unsigned long long Decoder<BE>::GetInt64(const unsigned char *ip)
{
  long long a = (((((ip[0] << 8) + ip[1]) << 8) + ip[2]) << 8) + ip[3];
  unsigned int b = (((((ip[4] << 8) + ip[5]) << 8) + ip[6]) << 8) + ip[7];
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
    *op++ = u.f;
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

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, vtkDICOMTag *op, unsigned int n)
{
  do
    {
    unsigned short g = Decoder<E>::GetInt16(ip);
    unsigned short e = Decoder<E>::GetInt16(ip + 2);
    *op++ = vtkDICOMTag(g, e);
    ip += 4;
    }
  while (--n);
}

//----------------------------------------------------------------------------
// Read "n" elements of type "T" into the supplied array pointer.
template<int E>
template<class T>
unsigned int Decoder<E>::ReadData(
  const unsigned char* &cp, const unsigned char* &ep,
  T *ptr, unsigned int n)
{
  unsigned int l = n*sizeof(T);
  while (n != 0 && this->CheckBuffer(cp, ep, sizeof(T)))
    {
    unsigned int m = static_cast<unsigned int>((ep - cp)/sizeof(T));
    if (m > n) { m = n; }
    Decoder<E>::GetValues(cp, ptr, m);
    cp += m*sizeof(T);
    ptr += m;
    n -= m;
    }

  return l - n*sizeof(T);
}

//----------------------------------------------------------------------------
// Skip "l" bytes in the buffer, return the number of bytes actually skipped
template<int E>
unsigned int Decoder<E>::SkipData(
  const unsigned char* &cp, const unsigned char* &ep, unsigned int l)
{
  unsigned int n = l;

  while (n != 0 && this->CheckBuffer(cp, ep, 2))
    {
    unsigned int m = static_cast<unsigned int>(ep - cp);
    if (m > n) { m = n; }
    cp += m;
    n -= m;
    }

  return l - n;
}

//----------------------------------------------------------------------------
template<int E>
unsigned int Decoder<E>::ReadElementHead(
  const unsigned char* &cp, const unsigned char* &ep,
  vtkDICOMTag tag, vtkDICOMVR &vr, unsigned int &vl)
{
  // basic size is 4 bytes
  unsigned int l = 4;

  if (this->ImplicitVR)
    {
    // implicit VR
    vr = this->FindDictVR(tag);
    vl = Decoder<E>::GetInt32(cp);
    // ignore vl in group length tags, it is corrupt in some files
    // and we know that it should always have a value of "4".
    if (tag.GetElement() == 0x0000) { vl = 4; }
    cp += 4;
    }
  else
    {
    // explicit VR
    vr = vtkDICOMVR(cp);
    vl = Decoder<E>::GetInt16(cp + 2);
    cp += 4;
    if (!vr.IsValid())
      {
      // invalid vr, try to get VR from dictionary instead, assume
      // than an implicitly-encoded VR somehow slipped into the data
      vr = this->FindDictVR(tag);
      vl = Decoder<E>::GetInt32(cp - 4);
      }
    else if (vr.HasLongVL()) // for OB, OF, OW, SQ, UN, UT
      {
      // check that buffer has 4 bytes for 32-bit VL
      if (!this->CheckBuffer(cp, ep, 4))
        {
        vtkDICOMParserInternalFriendship::ParseError(this->Parser, cp, ep,
          "Unexpected end of file.");
        return 0;
        }
      vl = Decoder<E>::GetInt32(cp);
      cp += 4;
      l += 4;
      }
    }

  return l;
}

//----------------------------------------------------------------------------
template<int E>
unsigned int Decoder<E>::ReadElementValue(
  const unsigned char* &cp, const unsigned char* &ep,
  vtkDICOMVR vr, unsigned int vl, vtkDICOMValue &v)
{
  unsigned int l = 0;

  // handle elements of unknown length
  if (vl == HxFFFFFFFF)
    {
    if (vr == vtkDICOMVR::UN)
      {
      // if VR is UN then it is a sequence encoded as implicit LE
      // (see DICOM Part 5, Section 6.2.2, Unknown (UN) Value Representation
      v.AllocateUnsignedCharData(vr, 0);
      this->ImplicitLE->SkipElements(
        cp, ep, vl, vtkDICOMTag(HxFFFE,HxE0DD), &v);
      return v.GetNumberOfValues();
      }
    else if (vr == vtkDICOMVR::OB)
      {
      // make sure unknown length data is properly encapsulated
      if (!this->CheckBuffer(cp, ep, 8))
        {
        vtkDICOMParserInternalFriendship::ParseError(this->Parser, cp, ep,
          "Unexpected end of file.");
        return 0;
        }
      unsigned short g1 = Decoder<E>::GetInt16(cp);
      unsigned short e1 = Decoder<E>::GetInt16(cp + 2);
      if (g1 != HxFFFE || (e1 != HxE000 && e1 != HxE0DD))
        {
        vtkDICOMParserInternalFriendship::ParseError(this->Parser, cp, ep,
          "Encapsulated object is missing (FFFE,E000) tag.");
        return 0;
        }

      v.AllocateUnsignedCharData(vr, 0);
      this->SkipElements(
        cp, ep, vl, vtkDICOMTag(HxFFFE,HxE0DD), &v);
      return v.GetNumberOfValues();
      }
    else if (vr != vtkDICOMVR::SQ)
      {
      // only UN, OB, and SQ can have unknown length
      vtkDICOMParserInternalFriendship::ParseError(this->Parser, cp, ep,
        "Illegal item length FFFFFFFF encountered.");
      return 0;
      }
    }
  else if (static_cast<unsigned int>(ep - cp) < vl)
    {
    // value is larger than what remains in buffer,
    // make sure there are enough bytes left in file
    std::streamsize bytesRemaining =
      vtkDICOMParserInternalFriendship::GetBytesRemaining(
          this->Parser, cp, ep);
    if (static_cast<std::streamsize>(vl) > bytesRemaining)
      {
      vtkDICOMParserInternalFriendship::ParseError(this->Parser, cp, ep,
        "Item length exceeds the bytes remaining in file.");
      return 0;
      }
    }

  switch (vr.GetType())
    {
    case VTK_CHAR:
      {
      char *ptr = v.AllocateCharData(vr, vl);
      l = this->ReadData(cp, ep, ptr, vl);
      // AllocateCharData makes room for terminal null
      if (l == 0 || ptr[l-1] != '\0') { ptr[l] = '\0'; }
      v.ComputeNumberOfValuesForCharData();
      }
      break;
    case VTK_UNSIGNED_CHAR:
      {
      unsigned char *ptr = v.AllocateUnsignedCharData(vr, vl);
      l = this->ReadData(cp, ep, ptr, vl);
      }
      break;
    case VTK_SHORT:
      {
      unsigned int n = vl/sizeof(short);
      short *ptr = v.AllocateShortData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      }
      break;
    case VTK_UNSIGNED_SHORT:
      {
      unsigned int n = vl/sizeof(unsigned short);
      unsigned short *ptr = v.AllocateUnsignedShortData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      }
      break;
    case VTK_INT:
      {
      unsigned int n = vl/sizeof(int);
      int *ptr = v.AllocateIntData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      }
      break;
    case VTK_UNSIGNED_INT:
      {
      unsigned int n = vl/sizeof(unsigned int);
      unsigned int *ptr = v.AllocateUnsignedIntData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      }
      break;
    case VTK_FLOAT:
      {
      unsigned int n = vl/sizeof(float);
      float *ptr = v.AllocateFloatData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      }
      break;
    case VTK_DOUBLE:
      {
      unsigned int n = vl/sizeof(double);
      double *ptr = v.AllocateDoubleData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      }
      break;
    case VTK_DICOM_TAG:
      {
      unsigned int n = vl/sizeof(vtkDICOMTag);
      vtkDICOMTag *ptr = v.AllocateTagData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      }
      break;
    case VTK_DICOM_ITEM:
      {
      vtkDICOMSequence seq;
      l = 0;
      while (l < vl)
        {
        if (!this->CheckBuffer(cp, ep, 8)) { return l; }
        unsigned short g = Decoder<E>::GetInt16(cp);
        unsigned short e = Decoder<E>::GetInt16(cp + 2);
        unsigned int il = Decoder<E>::GetInt32(cp + 4);
        cp += 8;
        l += 8;

        if (g == HxFFFE && e == HxE000)
          {
          // read one item
          vtkDICOMTag endtag(HxFFFE, HxE00D);
          vtkDICOMItem item(il == HxFFFFFFFF);
          vtkDICOMItem *olditem = this->Item;
          this->SetItem(&item);
          this->ReadElements(cp, ep, il, endtag, l);
          seq.AddItem(item);
          this->SetItem(olditem);
          }
        else if (g == HxFFFE && e == HxE0DD)
          {
          // sequence delimiter found
          break;
          }
        else
          {
          // non-item tag found
          if (vl != HxFFFFFFFF)
            {
            l += this->SkipData(cp, ep, vl-l);
            }
          break;
          }
        }
      if (vl != HxFFFFFFFF)
        {
        // create a sequence with vl != 0xffffffff
        unsigned int n = seq.GetNumberOfItems();
        vtkDICOMSequence seq2(n);
        for (unsigned int i = 0; i < n; i++)
          {
          seq2.SetItem(i, seq.GetItem(i));
          }
        seq = seq2;
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

  // does delimiter specify a single group to read?
  unsigned short group = delimiter.GetGroup();
  bool readGroup = (delimiter.GetElement() == 0x0000);

  while (tl < l || l == HxFFFFFFFF)
    {
    // read the tag
    if (!this->CheckBuffer(cp, ep, 8)) { break; }
    unsigned short g = Decoder<E>::GetInt16(cp);
    unsigned short e = Decoder<E>::GetInt16(cp + 2);
    vtkDICOMTag tag(g,e);

    // break if element is not in the chosen group
    if (readGroup && group != g) { break; }

    // read the VR and VL
    cp += 4;
    vtkDICOMVR vr;
    unsigned int vl;
    unsigned int hl = this->ReadElementHead(cp, ep, tag, vr, vl);
    tl += 4 + hl;

    // return false if could not read element
    if (hl == 0) { return false; }

    // save this as the most recent tag
    this->LastTag = tag;
    this->LastVR = vr;

    // break if delimiter found
    if (!readGroup && tag == delimiter) { break; }

    // read the value
    vtkDICOMValue v;
    unsigned int rl = 0;
    if (vr == vtkDICOMVR::UN && !this->ImplicitVR)
      {
      // if it was explicitly labeled 'UN' then check dictionary
      vr = this->FindDictVR(tag);
      rl = this->ImplicitLE->ReadElementValue(cp, ep, vr, vl, v);
      }
    else
      {
      rl = this->ReadElementValue(cp, ep, vr, vl, v);
      }

    // was it a short read?
    if (rl < vl && vl != HxFFFFFFFF)
      {
      unsigned int dl = vl - rl;
      // is the difference small, and not due to buffer underrun?
      if (dl <= 8 && this->CheckBuffer(cp, ep, dl))
        {
        // treat the difference as if it is padding
        cp += dl;
        rl = vl;
        }
      else
        {
        return false;
        }
      }

    tl += rl;

    // store the value
    if (this->Item)
      {
      this->Item->SetAttributeValue(tag, v);
      }
    else if (this->Index < 0)
      {
      this->MetaData->SetAttributeValue(tag, v);
      }
    else
      {
      this->MetaData->SetAttributeValue(this->Index, tag, v);
      this->HandleMissingAttributes(tag);
      }

    /*
    cout << tag << " " << vr << " " << vl << " " << v;
    vtkDICOMDictEntry entry;
    if (this->MetaData->FindDictEntry(tag, entry))
      {
      cout << " \"" << entry.GetName() << "\"";
      }
    cout << "\n";
    */
    }

  bytesRead += tl;

  return true;
}

//----------------------------------------------------------------------------
template<int E>
bool Decoder<E>::SkipElements(
  const unsigned char* &cp, const unsigned char* &ep,
  unsigned int l, vtkDICOMTag delimiter, vtkDICOMValue *v)
{
  if (l == HxFFFFFFFF)
    {
    // save the current buffer position
    const unsigned char *sp = cp;

    // does delimiter specify a single group to read?
    unsigned short group = delimiter.GetGroup();
    bool readGroup = (delimiter.GetElement() == 0x0000);

    // skip until delimiter found
    for (;;)
      {
      if (!this->CheckBuffer(cp, ep, 8, v, sp)) { return false; }
      unsigned short g = Decoder<E>::GetInt16(cp);
      unsigned short e = Decoder<E>::GetInt16(cp + 2);

      // break if element is not in the chosen group
      if (readGroup && group != g) { break; }

      cp += 4;
      unsigned int tl = 8;
      unsigned int vl = 0;
      vtkDICOMVR vr;

      // sequence and item delimiters are always decoded as implicit
      if (g == HxFFFE || this->ImplicitVR)
        {
        vl = Decoder<E>::GetInt32(cp);
        // ignore vl in group length tags, it is corrupt in some files
        // and we know that it should always have a value of "4".
        if (e == 0x0000) { vl = 4; }
        cp += 4;
        }
      else
        {
        // explicit VR
        vr = vtkDICOMVR(cp);
        vl = Decoder<E>::GetInt16(cp + 2);
        cp += 4;
        if (vr.HasLongVL())
          {
          if (!this->CheckBuffer(cp, ep, 4, v, sp)) { return false; }
          vl = Decoder<E>::GetInt32(cp);
          cp += 4;
          tl += 4;
          }
        }

      // save this as the most recent tag
      this->LastTag = vtkDICOMTag(g, e);
      this->LastVR = vr;

      // break if delimiter found
      if (!readGroup && this->LastTag == delimiter) { break; }

      if (vl == HxFFFFFFFF)
        {
        // copy data up to current buffer position
        this->CopyBuffer(v, sp, cp);
        sp = cp;

        // use sequence delimiter
        vtkDICOMTag newdelim(HxFFFE, HxE0DD);
        if (g == HxFFFE && e == HxE000)
          {
          // use item delimiter
          newdelim = vtkDICOMTag(HxFFFE, HxE00D);
          }
        // skip internal segment until new delimiter found
        if (vr != vtkDICOMVR::UN)
          {
          if (!this->SkipElements(cp, ep, vl, newdelim, v))
            {
            return false;
            }
          }
        // if VR is explicit UN, sequence is implicit LE
        // (see DICOM Part 5, Section 6.2.2)
        else if (!this->ImplicitLE->SkipElements(
                   cp, ep, vl, newdelim, v))
          {
          return false;
          }
        sp = cp;
        }
      else
        {
        // fixed length element (vl != 0xffffffff)
        if (v != 0 && vl > static_cast<unsigned int>(ep - cp))
          {
          // if vl is larger than number of bytes left in buffer,
          // then copy data from save point "sp" up to "cp" into v,
          // and read the value into "v".
          unsigned int m = static_cast<unsigned int>(cp - sp);
          unsigned int n = v->GetNumberOfValues();
          unsigned char *ptr = v->ReallocateUnsignedCharData(n + vl + m) + n;
          if (m) { do { *ptr++ = *sp++; } while (--m); }
          tl = this->ReadData(cp, ep, ptr, vl);
          sp = cp;
          if (tl != vl) { return false; }
          }
        else
          {
          tl = this->SkipData(cp, ep, vl);
          if (tl != vl) { return false; }
          }
        }
      }

    // the for(;;) loop is done, copy data from the save point sp
    // up to current position cp into the value v
    this->CopyBuffer(v, sp, cp);
    }
  else if (l != 0) // l != 0xffffffff
    {
    // skipped a fixed number of bytes
    unsigned int tl;
    if (v != 0)
      {
      // read bytes into the value "v"
      unsigned int n = v->GetNumberOfValues();
      unsigned char *ptr = v->ReallocateUnsignedCharData(n + l) + n;
      tl = this->ReadData(cp, ep, ptr, l);
      if (tl != l) { return false; }
      }
    else
      {
      // simply skip "l" bytes
      tl = this->SkipData(cp, ep, l);
      if (tl != l) { return false; }
      }
    }

  return true;
}

} // end anonymous namespace

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Constructor
vtkDICOMParser::vtkDICOMParser()
{
  this->FileName = NULL;
  this->MetaData = NULL;
  this->Groups = NULL;
  this->InputStream = NULL;
  this->BytesRead = 0;
  this->FileOffset = 0;
  this->FileSize = 0;
  this->Buffer = NULL;
  this->BufferSize = 8192;
  this->ChunkSize = 0;
  this->Index = -1;
  this->PixelDataFound = false;
  this->ErrorCode = 0;
}

// Destructor
vtkDICOMParser::~vtkDICOMParser()
{
  delete [] this->FileName;

  if (this->MetaData)
    {
    this->MetaData->Delete();
    }
  if (this->Groups)
    {
    this->Groups->Delete();
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
void vtkDICOMParser::Update()
{
  int idx = -1;

  // Use default idx of -1 if we are writing to the meta data object for
  // the first time, or if the meta data is for only a single image.
  if (this->MetaData &&
      this->MetaData->GetNumberOfDataElements() > 0 &&
      this->MetaData->GetNumberOfInstances() > 1)
    {
    idx = this->Index;
    }

  this->ReadFile(this->MetaData, idx);
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::ReadFile(vtkDICOMMetaData *data, int idx)
{
  // Mark pixel data as not found yet
  this->PixelDataFound = false;
  this->FileOffset = 0;
  this->FileSize = 0;

  // Check that the file name has been set.
  if (!this->FileName)
    {
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    vtkErrorMacro("ReadFile: No file name has been set");
    return false;
    }

  // Make sure that the file exists.
  struct stat fs;
  if (stat(this->FileName, &fs) != 0)
    {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("ReadFile: Can't open file " << this->FileName);
    return false;
    }

  this->FileSize = fs.st_size;

  // Make sure that the file is readable.
  std::ifstream infile(this->FileName, ios::in | ios::binary);

  if (infile.fail())
    {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("ReadFile: Can't read the file " << this->FileName);
    return false;
    }

  this->InputStream = &infile;
  this->BytesRead = 0;
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
  bool tempMeta = false;
  if (meta == 0)
    {
    meta = vtkDICOMMetaData::New();
    tempMeta = true;
    }

  LittleEndianDecoder decoder(this, meta, idx);

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

    unsigned int l = HxFFFFFFFF;
    if (e == 0x0000 && vl == 4)
      {
      // get length from tag 0x0002,0x0000
      l = Decoder<LE>::GetInt32(cp + 8) + 12;
      }

    decoder.ReadElements(cp, ep, l, vtkDICOMTag(g,0));

    int i = (idx == -1 ? 0 : idx);
    this->TransferSyntax =
      meta->GetAttributeValue(i, DC::TransferSyntaxUID).AsString();
    }
  else
    {
    this->TransferSyntax = "";
    }

  this->ComputeFileOffset(cp, ep);

  if (tempMeta)
    {
    meta->Delete();
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

  std::string &tsyntax = this->TransferSyntax;
  if (tsyntax == "") // try to guess the syntax
    {
    if (!decoder->CheckBuffer(cp, ep, 8)) { return false; }
    if (cp[0] == 0x00 && cp[1] == 0x08)
      {
      tsyntax = "1.2.840.10008.1.2.2";
      decoder = &decoderBE;
      }
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
    }

  vtkUnsignedShortArray *groups = this->Groups;

  // read group-by-group
  bool foundPixelData = false;
  bool readFailure = false;
  while (!foundPixelData && !readFailure)
    {
    unsigned int g = decoder->PeekGroup(cp, ep);

    // if there is no data left to decode, then break
    if (cp == ep) { break; }

    // do we want to read or skip this group?
    bool found = true;
    if (groups)
      {
      found = false;
      vtkIdType n = groups->GetNumberOfTuples();
      for (vtkIdType i = 0; i < n && !found; i++)
        {
        found = (g == groups->GetValue(i));
        }
      }

    // create a delimiter to read/skip only this group
    vtkDICOMTag delimiter(g,0);

    // check for PixelData group 0x7fe0, or obsolete 0x7fxx
    if ((g & 0xff01) == 0x7f00)
      {
      // set delimiter to pixel data tag
      delimiter = vtkDICOMTag(g, 0x0010);
      foundPixelData = true;
      }

    if (found && meta)
      {
      readFailure = !decoder->ReadElements(cp, ep, HxFFFFFFFF, delimiter);
      }
    else
      {
      readFailure = !decoder->SkipElements(cp, ep, HxFFFFFFFF, delimiter);
      }
    }

  this->PixelDataFound = (decoder->GetLastTag() == DC::PixelData);
  if (meta && this->PixelDataFound)
    {
    // add the PixelData attribute, but make it empty
    unsigned short x;
    vtkDICOMValue v(decoder->GetLastVR(), &x, &x);
    if (idx >= 0)
      {
      meta->SetAttributeValue(idx, DC::PixelData, v);
      decoder->HandleMissingAttributes(DC::PixelData);
      }
    else
      {
      meta->SetAttributeValue(DC::PixelData, v);
      }
    }

  this->ComputeFileOffset(cp, ep);

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
    this->SetErrorCode(vtkErrorCode::UnknownError);
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
  this->BytesRead += n;

  // ep is recycled chars plus newly read chars
  ep = reinterpret_cast<unsigned char *>(dp + n);
  ucp = reinterpret_cast<unsigned char *>(this->Buffer);

  return true;
}

//----------------------------------------------------------------------------
std::streamsize vtkDICOMParser::GetBytesRemaining(
  const unsigned char *cp, const unsigned char *ep)
{
  return static_cast<std::streamsize>(
    this->FileSize - this->BytesRead + (ep - cp));
}

//----------------------------------------------------------------------------
void vtkDICOMParser::ComputeFileOffset(
  const unsigned char* cp, const unsigned char* ep)
{
  // the offset is the number of bytes read minus
  // the number of bytes remaining in the buffer.
  this->FileOffset = this->BytesRead - (ep - cp);
}

//----------------------------------------------------------------------------
void vtkDICOMParser::ParseError(
  const unsigned char* cp, const unsigned char* ep, const char* message)
{
  this->ComputeFileOffset(cp, ep);
  this->SetErrorCode(vtkErrorCode::FileFormatError);
  vtkErrorMacro("At byte offset " << this->FileOffset << " in file "
                << this->FileName << ": " << message);
}

//----------------------------------------------------------------------------
void vtkDICOMParser::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "FileName: "
     << (this->FileName ? this->FileName : "(NULL)") << "\n";
  os << indent << "PixelDataFound: "
     << (this->PixelDataFound ? "True\n" : "False\n");
  os << indent << "FileOffset: " << this->FileOffset << "\n";
  os << indent << "FileSize: " << this->FileSize << "\n";
  os << indent << "MetaData: " << this->MetaData << "\n";
  os << indent << "Index: " << this->Index << "\n";
  os << indent << "BufferSize: " << this->BufferSize << "\n";
  os << indent << "Groups: " << this->Groups << "\n";
}
