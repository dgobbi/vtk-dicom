/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMParser.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMFile.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include "vtkObjectFactory.h"
#include "vtkUnsignedShortArray.h"
#include "vtkErrorCode.h"

#include <ctype.h>
#include <assert.h>

#include <string>
#include <vector>
#include <algorithm>

vtkStandardNewMacro(vtkDICOMParser);
vtkCxxSetObjectMacro(vtkDICOMParser, MetaData, vtkDICOMMetaData);
vtkCxxSetObjectMacro(vtkDICOMParser, Query, vtkDICOMMetaData);
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

  static bool SeekBuffer(vtkDICOMParser *parser,
    const unsigned char* &cp, const unsigned char* &ep,
    vtkTypeInt64 offset)
  {
    return parser->SeekBuffer(cp, ep, offset);
  }

  static vtkTypeInt64 GetBytesRemaining(vtkDICOMParser *parser,
    const unsigned char *cp, const unsigned char *ep)
  {
    return parser->GetBytesRemaining(cp, ep);
  }

  static vtkTypeInt64 GetBytesProcessed(vtkDICOMParser *parser,
    const unsigned char *cp, const unsigned char *ep)
  {
    return parser->GetBytesProcessed(cp, ep);
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

//----------------------------------------------------------------------------
// Class that caches info about the current sequence item
class DecoderContext
{
public:
  // Construct the base info from the meta data.
  DecoderContext(vtkDICOMMetaData *meta, int index,
                 vtkDICOMCharacterSet dcs, bool ocs) :
    Prev(0), Item(0), MetaData(meta), Index(index),
    CurrentTag(0,0), DefaultCharacterSet(dcs),
    CharacterSet(ocs ? dcs :
                 vtkDICOMCharacterSet(vtkDICOMCharacterSet::Unknown)),
    VRForXS(vtkDICOMVR::XX) {}

  // Construct from the current item.
  DecoderContext(vtkDICOMItem *item, vtkDICOMCharacterSet dcs, bool ocs) :
    Prev(0), Item(item), MetaData(0), Index(0),
    CurrentTag(0,0), DefaultCharacterSet(dcs),
    CharacterSet(ocs ? dcs :
                 vtkDICOMCharacterSet(vtkDICOMCharacterSet::Unknown)),
    VRForXS(vtkDICOMVR::XX) {}

  // Find an element within the current context.  This is used
  // by FindDictVR() to disambiguate VRs that could be either US
  // or SS, or that could be either OB or OW.
  const vtkDICOMValue& Get(vtkDICOMTag tag);

  // Get the dictionary VR (for implicit VR elements).
  // If the tag is not found, UN (unknown) will be returned.
  vtkDICOMVR FindDictVR(vtkDICOMTag tag);

  // Get the character set that is currently active.
  vtkDICOMCharacterSet GetCharacterSet();

  // Get the VR to use for XS by checking PixelRepresentation.
  vtkDICOMVR GetVRForXS();

  // Set the previous context.
  void SetPrev(DecoderContext *context) { this->Prev = context; }
  DecoderContext *GetPrev() { return this->Prev; }

  // Get the current item.
  vtkDICOMItem *GetItem() { return this->Item; }

  // Set the current tag position for the context.
  void SetCurrentTag(vtkDICOMTag tag) { this->CurrentTag = tag; }

private:
  DecoderContext *Prev;
  vtkDICOMItem *Item;
  vtkDICOMMetaData *MetaData;
  int Index;
  vtkDICOMTag CurrentTag;
  vtkDICOMCharacterSet DefaultCharacterSet;
  vtkDICOMCharacterSet CharacterSet;
  vtkDICOMVR VRForXS;
};

//----------------------------------------------------------------------------
const vtkDICOMValue& DecoderContext::Get(vtkDICOMTag tag)
{
  if (this->Item)
  {
    return this->Item->Get(tag);
  }
  else
  {
    int idx = (this->Index == -1 ? 0 : this->Index);
    return this->MetaData->Get(idx, tag);
  }
}

//----------------------------------------------------------------------------
vtkDICOMCharacterSet DecoderContext::GetCharacterSet()
{
  vtkDICOMCharacterSet cs = this->CharacterSet;
  if (cs == vtkDICOMCharacterSet::Unknown)
  {
    const vtkDICOMValue& v = this->Get(DC::SpecificCharacterSet);
    if (v.IsValid())
    {
      cs = vtkDICOMCharacterSet(v.GetCharData(), v.GetVL());
    }
    else if (this->Prev)
    {
      cs = this->Prev->GetCharacterSet();
    }
    else
    {
      cs = this->DefaultCharacterSet;
    }
    if (this->CurrentTag > DC::SpecificCharacterSet)
    {
      this->CharacterSet = cs;
    }
  }

  return cs;
}

//----------------------------------------------------------------------------
vtkDICOMVR DecoderContext::GetVRForXS()
{
  vtkDICOMVR vr = this->VRForXS;
  if (vr == vtkDICOMVR::XX)
  {
    const vtkDICOMValue& v = this->Get(DC::PixelRepresentation);
    if (v.IsValid())
    {
      vr = (v.AsUnsignedShort() == 0 ? vtkDICOMVR::US : vtkDICOMVR::SS);
    }
    else if (this->Prev)
    {
      vr = this->Prev->GetVRForXS();
    }
    else
    {
      vr = vtkDICOMVR::US;
    }
    if (this->CurrentTag > DC::PixelRepresentation)
    {
      this->VRForXS = vr;
    }
  }
  return vr;
}

//----------------------------------------------------------------------------
vtkDICOMVR DecoderContext::FindDictVR(vtkDICOMTag tag)
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
        this->CurrentTag = tag;
        vr = this->GetVRForXS();
      }
      else if (vr == vtkDICOMVR::OX)
      {
        // disambiguate tags that may be either "OB" or "OW"
        vr = vtkDICOMVR::OW;
        vtkDICOMTag reftag = (tag.GetGroup() == 0x5400 ?
                              DC::WaveformBitsAllocated :
                              DC::BitsAllocated);
        const vtkDICOMValue& v = this->Get(reftag);
        if (v.IsValid() && v.AsUnsignedShort() <= 8)
        {
          vr = vtkDICOMVR::OB;
        }
      }
    }
  }

  return vr;
}

//----------------------------------------------------------------------------
// The base class for the decoder classes.
class DecoderBase
{
public:
  // Virtual destructor for completeness.
  virtual ~DecoderBase() {}

  // Whether to use implicit VRs (default: explicit VRs).
  void SetImplicitVR(bool i) { this->ImplicitVR = i; }

  // Set the current item context.
  void PushContext(DecoderContext *context, vtkDICOMTag tag);

  // Pop the current item context.
  void PopContext();

  // The query with which to filter the data.
  void SetQuery(
    const vtkDICOMDataElementIterator& iter,
    const vtkDICOMDataElementIterator& iterEnd);

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

  // Peek ahead to see what the next element is.
  virtual vtkDICOMTag Peek(
    const unsigned char* &cp, const unsigned char* &ep) = 0;

  // Copy bytes from sp to end marker cp into the value "v".
  // If the parameter "v" is NULL, then it will be ignored.
  void CopyBuffer(
    vtkDICOMValue *v, const unsigned char *sp, const unsigned char *cp);

  // If there are fewer than "n" bytes left in the buffer, then move
  // any data that hasn't yet been parsed to the start of the buffer,
  // and then read new data into the remainder of the buffer.
  bool CheckBuffer(
    const unsigned char* &cp, const unsigned char* &ep, size_t n);

  // This overload of CheckBuffer is used within SkipElements to
  // automatically copy the skipped bytes into the value "v".
  // If the parameter "v" is NULL, then it will be ignored.
  bool CheckBuffer(
    const unsigned char* &cp, const unsigned char* &ep, size_t n,
    vtkDICOMValue *v, const unsigned char* &sp);

  // Get the current byte offset from the start of the file.
  size_t GetByteOffset(
    const unsigned char *cp, const unsigned char *ep);

  // Get the last tag that was read.
  vtkDICOMTag GetLastTag() { return this->LastTag; }

  // Get the VR of the last data element (invalid if implicit)
  vtkDICOMVR GetLastVR() { return this->LastVR; }

  // Get the VL of the last data element.
  unsigned int GetLastVL() { return this->LastVL; }

  // Check for attributes missing from this instance, that were present
  // for instances in the series that were already parsed.
  void HandleMissingAttributes(vtkDICOMTag tag);

  // Advance the query iterator (this->Query) to the given tag,
  // and set this->QueryMatched to false if any unmatched query keys
  // were found, unless the keys support universal matching (i.e. the
  // key has no value), or unless the keys are private
  void AdvanceQueryIterator(vtkDICOMTag tag);

  // Returns true if the query contains the given tag.
  bool QueryContains(vtkDICOMTag tag);

  // Returns true if the value matches the query.
  bool QueryMatches(const vtkDICOMValue& v);

  // Returns true if all queries have matched so far.
  bool GetQueryMatched() { return this->QueryMatched; }

  // Finish the query (check for unused keys that must match).
  bool FinishQuery();

protected:
  // Constructor that initializes all of the members.
  DecoderBase(vtkDICOMParser *parser, vtkDICOMMetaData *data, int idx) :
    Parser(parser), BaseContext(data,idx,parser->GetDefaultCharacterSet(),
      parser->GetOverrideCharacterSet()),
    Item(0), MetaData(data), Index(idx), ImplicitVR(false),
    HasQuery(false), QueryMatched(false),
    LastVL(0) { this->Context = &this->BaseContext; }

  // an internal implicit little-endian decoder
  DefaultDecoder *ImplicitLE;
  // the vtkDICOMParser::FillBuffer method is used to refill the buffer
  vtkDICOMParser *Parser;
  // the current context (info about the current item being parsed)
  DecoderContext *Context;
  // the base context.
  DecoderContext BaseContext;
  // the sequence item to read the data into while parsing a sequence
  vtkDICOMItem *Item;
  // the metadata object to read the data into
  vtkDICOMMetaData *MetaData;
  // the instance index to use with the meta data
  int Index;
  // if this is set, then VRs are implicit
  bool ImplicitVR;
  // the query to apply while reading the data
  bool HasQuery;
  bool QueryMatched;
  vtkDICOMDataElementIterator Query;
  vtkDICOMDataElementIterator QueryEnd;
  vtkDICOMDataElementIterator QuerySave;
  // this is set to the last tag that was read.
  vtkDICOMTag LastTag;
  vtkDICOMVR  LastVR;
  unsigned int LastVL;
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
  static void GetValues(const unsigned char *ip, char *v, size_t n);
  static void GetValues(const unsigned char *ip, unsigned char *v, size_t n);
  static void GetValues(const unsigned char *ip, short *v, size_t n);
  static void GetValues(const unsigned char *ip, unsigned short *v, size_t n);
  static void GetValues(const unsigned char *ip, int *v, size_t n);
  static void GetValues(const unsigned char *ip, unsigned int *v, size_t n);
  static void GetValues(const unsigned char *ip, float *v, size_t n);
  static void GetValues(const unsigned char *ip, double *v, size_t n);
  static void GetValues(const unsigned char *ip, vtkDICOMTag *v, size_t n);

  // Read "n" values from the buffer into the provided pointer.
  // The number of bytes that were read from the buffer will be returned.
  // The buffer will be refilled as necessary.
  template<class T>
  size_t ReadData(
    const unsigned char* &cp, const unsigned char* &ep, T *ptr, size_t n);

  // Skip forward by "n" bytes.  The number of bytes skipped will be
  // returned.  If the end of the file is reached before the operation,
  // is complete, then the return value will be less than "n".
  size_t SkipData(
    const unsigned char* &cp, const unsigned char* &ep, size_t n);

  // Read l bytes of data, or until delimiter tag found.
  // Set l to 0xffffffff to ignore length completely.
  // If the delimiter is of the form (0xgggg,0x0000), ie. if the
  // "element" part is zero, then the reading will stop before
  // the first element that is not in the specified group.
  bool ReadElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter)
  {
    size_t bytesRead;
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
    unsigned int l, vtkDICOMTag delimiter, size_t &bytesRead);

  // Query the elements of one item within a sequence.
  bool QueryOneItem(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter, size_t &bytesRead);

  // A SkipElements that copies skipped bytes into value "v".
  // This method is used when parsing encapsulated data, it simply
  // reads the encapsulated data into the value as raw bytes.
  // If the parameter "v" is NULL, then it will be ignored.
  bool SkipElements(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int l, vtkDICOMTag delimiter, vtkDICOMValue *v);

  // Read the vr and vl and return the number of bytes read
  // (will return zero if an error occurred)
  size_t ReadElementHead(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMTag tag, vtkDICOMVR &vr, unsigned int &vl);

  // Read a value, given the vr and vl, where vl can be 0xffffffff
  // for SQ, UN, or OB to indicate tag-delimited data.
  // The number of bytes that were read will be returned.
  size_t ReadElementValue(
    const unsigned char* &cp, const unsigned char* &ep,
    vtkDICOMVR vr, unsigned int vl, vtkDICOMValue &v);

  // Peek ahead to see what the next element is.
  vtkDICOMTag Peek(
    const unsigned char* &cp, const unsigned char* &ep)
  {
    unsigned short g = 0;
    unsigned short e = 0;
    if (this->CheckBuffer(cp, ep, 4))
    {
      g = Decoder<E>::GetInt16(cp);
      e = Decoder<E>::GetInt16(cp + 2);
    }
    return vtkDICOMTag(g, e);
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
inline void DecoderBase::PushContext(DecoderContext *context, vtkDICOMTag tag)
{
  // ensure that "Item" is set for the ImplicitLE decoder, too
  this->Item = context->GetItem();
  this->ImplicitLE->Item = context->GetItem();

  // save the current position in the current context
  this->Context->SetCurrentTag(tag);

  // push the new context
  context->SetPrev(this->Context);
  this->Context = context;
}

//----------------------------------------------------------------------------
inline void DecoderBase::PopContext()
{
  this->Context = this->Context->GetPrev();
  this->Item = this->Context->GetItem();
  this->ImplicitLE->Item = this->Context->GetItem();
}

//----------------------------------------------------------------------------
void DecoderBase::SetQuery(
  const vtkDICOMDataElementIterator& iter,
  const vtkDICOMDataElementIterator& iterEnd)
{
  if (iter != iterEnd)
  {
    this->HasQuery = true;
    this->QueryMatched = true;
    this->Query = iter;
    this->QueryEnd = iterEnd;
    this->QuerySave = iter;
  }
  else
  {
    this->HasQuery = false;
    this->QueryMatched = false;
  }
}

//----------------------------------------------------------------------------
inline void DecoderBase::CopyBuffer(
  vtkDICOMValue *v, const unsigned char *sp, const unsigned char *cp)
{
  // append bytes from sp to cp into the supplied value "v"
  if (v && cp != sp)
  {
    size_t m = cp - sp;
    size_t n = v->GetNumberOfValues();
    unsigned char *ptr = v->ReallocateUnsignedCharData(n + m) + n;
    do { *ptr++ = *sp++; } while (--m);
  }
}

//----------------------------------------------------------------------------
inline bool DecoderBase::CheckBuffer(
  const unsigned char* &cp, const unsigned char* &ep, size_t n)
{
  bool r = true;
  if (n > static_cast<size_t>(ep - cp))
  {
    r = vtkDICOMParserInternalFriendship::FillBuffer(
          this->Parser, cp, ep);
    r &= (n <= static_cast<size_t>(ep - cp));
  }
  return r;
}

inline bool DecoderBase::CheckBuffer(
  const unsigned char* &cp, const unsigned char* &ep, size_t n,
  vtkDICOMValue *v, const unsigned char* &sp)
{
  bool r = true;
  if (n > static_cast<size_t>(ep - cp))
  {
    this->CopyBuffer(v, sp, cp);
    r = vtkDICOMParserInternalFriendship::FillBuffer(
          this->Parser, cp, ep);
    r &= (n <= static_cast<size_t>(ep - cp));
    sp = cp;
  }
  return r;
}

//----------------------------------------------------------------------------
inline size_t DecoderBase::GetByteOffset(
  const unsigned char *cp, const unsigned char *ep)
{
  return vtkDICOMParserInternalFriendship::GetBytesProcessed(
    this->Parser, cp, ep);
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
      this->MetaData->Set(this->Index, missing[i], vtkDICOMValue());
    }
    delete [] missing;
  }
  this->LastWrittenTag = tag;
}

//----------------------------------------------------------------------------
void DecoderBase::AdvanceQueryIterator(vtkDICOMTag tag)
{
  // advance the query iterator to the given tag
  while (this->Query != this->QueryEnd && this->Query->GetTag() < tag)
  {
    // for query keys that weren't in the data set, only match if:
    // 1) the key is SpecificCharacterSet (not used for matching), or
    // 2) the key is a group length element (gggg,0000)
    // 3) the key is a private creator tag, or
    // 4) the key supports universal matching, i.e. will even match null
    vtkDICOMTag qtag = this->Query->GetTag();
    if (qtag != DC::SpecificCharacterSet && qtag.GetElement() != 0 &&
        ((qtag.GetGroup() & 1) == 0 || qtag.GetElement() > 0x00ff))
    {
      vtkDICOMValue nullValue;
      bool matched = nullValue.Matches(this->Query->GetValue());

      // if query tag is private, need additional checks
      if (!matched && (qtag.GetGroup() & 1) != 0)
      {
        // compute creator tag, and search for it
        vtkDICOMTag ctag =
          vtkDICOMTag(qtag.GetGroup(), qtag.GetElement() >> 8);
        vtkDICOMDataElementIterator iter = this->QuerySave;
        while (iter != this->QueryEnd && iter->GetTag() < ctag)
        {
          ++iter;
        }
        if (iter != this->QueryEnd && iter->GetTag() == ctag)
        {
          // if we already read the element, we already checked whether it
          // but if we didn't read it, then it doesn't exist, so don't match
          if (this->Item)
          {
            vtkDICOMTag ptag = this->Item->ResolvePrivateTag(
              qtag, iter->GetValue().AsString());
            matched = (ptag != vtkDICOMTag(0xffff,0xffff) &&
                       this->Item->Get(ptag).IsValid());
          }
          else if (this->Index < 0)
          {
            vtkDICOMTag ptag = this->MetaData->ResolvePrivateTag(
              qtag, iter->GetValue().AsString());
            matched = (ptag != vtkDICOMTag(0xffff,0xffff) &&
                       this->MetaData->Has(ptag));
          }
          else
          {
            vtkDICOMTag ptag = this->MetaData->ResolvePrivateTag(
              this->Index, qtag, iter->GetValue().AsString());
            matched = (ptag != vtkDICOMTag(0xffff,0xffff) &&
                       this->MetaData->Get(this->Index, ptag).IsValid());
          }
        }
        else
        {
          // query has a private tag with no creator!
          if (this->Item)
          {
            matched = this->Item->Get(qtag).Matches(
              this->Query->GetValue());
          }
          else
          {
            matched = this->MetaData->Get(qtag).Matches(
              this->Query->GetValue());
          }
        }
      }

      this->QueryMatched &= matched;
    }
    ++this->Query;
  }
}

//----------------------------------------------------------------------------
bool DecoderBase::QueryContains(vtkDICOMTag tag)
{
  // if the tag isn't private
  if ((tag.GetGroup() & 1) == 0)
  {
    // advance the query iterator until the tag is found in the query
    this->AdvanceQueryIterator(tag);

    // return true if the tag exists in the query
    return (this->Query != this->QueryEnd && this->Query->GetTag() == tag);
  }

  // the remainder of this function handles private tags
  unsigned short g = tag.GetGroup();
  unsigned short e = tag.GetElement();

  // first, make sure this private group is present in the query,
  // and ignore any elements before (gggg,0010)
  vtkDICOMTag gtag = vtkDICOMTag(g, 0x0010);
  this->AdvanceQueryIterator(gtag);

  // save the query iterator
  if (this->QuerySave->GetTag() < gtag)
  {
    this->QuerySave = this->Query;
  }

  // if query doesn't contain any more keys in this group, return
  vtkDICOMDataElementIterator iter = this->Query;
  if (iter == this->QueryEnd || iter->GetTag().GetGroup() != g)
  {
    return false;
  }

  // if this is a creator element (e is 0x00XX), return true
  if (e >= 0x0010 && e <= 0x00FF)
  {
    return true;
  }

  // search for the creator element within the query
  vtkDICOMTag ctag = vtkDICOMTag(g, e >> 8);
  vtkDICOMValue creator = this->Context->Get(ctag);
  if (creator.IsValid())
  {
    // maximum possible creator element is (gggg,00FF)
    gtag = vtkDICOMTag(g, 0x00FF);
    while (iter != this->QueryEnd && iter->GetTag() <= gtag)
    {
      if (iter->GetValue().Matches(creator))
      {
        tag = vtkDICOMTag(
          g, (iter->GetTag().GetElement() << 8) | (e & 0x00FF));
        break;
      }
      ++iter;
    }
    // if creator not found in query, tag obviously won't be found
    if (iter == this->QueryEnd || iter->GetTag() > gtag)
    {
      return false;
    }
  }

  // finally, look for the private tag at its resolved location
  while (iter != this->QueryEnd && iter->GetTag() < tag)
  {
    ++iter;
  }
  if (iter != this->QueryEnd && iter->GetTag() == tag)
  {
    this->Query = iter;
    return true;
  }

  return false;
}

//----------------------------------------------------------------------------
bool DecoderBase::QueryMatches(const vtkDICOMValue& v)
{
  bool matched = true;
  vtkDICOMTag tag = this->Query->GetTag();

  if (v.GetVR() != vtkDICOMVR::SQ)
  {
    // a query match is always true for SpecificCharacterSet, because this
    // element exists to describe the character encoding of the query, not
    // because it is to be matched.
    if (tag != DC::SpecificCharacterSet && tag.GetElement() != 0 &&
        ((tag.GetGroup() & 1) == 0 || tag.GetElement() > 0x00ff))
    {
      // if above conditions don't apply, check if the query key matches
      matched = v.Matches(this->Query->GetValue());
    }
  }
  else
  {
    // if VR is SQ, then the matching was done when the sequence items were
    // parsed, and we just have to return the current value of QueryMatched
    matched = this->QueryMatched;
  }

  if ((tag.GetGroup() & 1) == 0)
  {
    // advance the query iterator
    ++this->Query;
  }
  else
  {
    // if private, restore to the start of the private group
    this->Query = this->QuerySave;
  }

  return matched;
}

//----------------------------------------------------------------------------
bool DecoderBase::FinishQuery()
{
  if (this->HasQuery && this->QueryMatched)
  {
    this->AdvanceQueryIterator(vtkDICOMTag(0xffff,0xffff));
  }
  return this->QueryMatched;
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
  unsigned int b = ip[4] + (ip[5] << 8) + ((ip[6] + (ip[7] << 8)) << 16);
  return (static_cast<unsigned long long>(b) << 32) + a;
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
  unsigned int a = (((((ip[0] << 8) + ip[1]) << 8) + ip[2]) << 8) + ip[3];
  unsigned int b = (((((ip[4] << 8) + ip[5]) << 8) + ip[6]) << 8) + ip[7];
  return (static_cast<unsigned long long>(a) << 32) + b;
}

//----------------------------------------------------------------------------
template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, char *op, size_t n)
{
  do { *op++ = static_cast<char>(*ip++); } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, unsigned char *op, size_t n)
{
  do { *op++ = *ip++; } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, short *op, size_t n)
{
  do { *op++ = static_cast<short>(Decoder<E>::GetInt16(ip)); ip += 2; }
  while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, unsigned short *op, size_t n)
{
  do { *op++ = Decoder<E>::GetInt16(ip); ip += 2; } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, int *op, size_t n)
{
  do { *op++ = static_cast<int>(Decoder<E>::GetInt32(ip)); ip += 4; }
  while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, unsigned int *op, size_t n)
{
  do { *op++ = Decoder<E>::GetInt32(ip); ip += 4; } while (--n);
}

template<int E>
void Decoder<E>::GetValues(
  const unsigned char *ip, float *op, size_t n)
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
  const unsigned char *ip, double *op, size_t n)
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
  const unsigned char *ip, vtkDICOMTag *op, size_t n)
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
size_t Decoder<E>::ReadData(
  const unsigned char* &cp, const unsigned char* &ep, T *ptr, size_t n)
{
  size_t l = n*sizeof(T);
  while (n != 0 && this->CheckBuffer(cp, ep, sizeof(T)))
  {
    size_t m = (ep - cp)/sizeof(T);
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
size_t Decoder<E>::SkipData(
  const unsigned char* &cp, const unsigned char* &ep, size_t l)
{
  // if the number of bytes to skip is larger than the buffer size
  if (l >= static_cast<size_t>(this->Parser->GetBufferSize()))
  {
    // seek forward within the file
    vtkTypeInt64 m = static_cast<vtkTypeInt64>(l);
    vtkTypeInt64 n = vtkDICOMParserInternalFriendship::GetBytesRemaining(
      this->Parser, cp, ep);
    m = (m <= n ? m : n);
    vtkDICOMParserInternalFriendship::SeekBuffer(this->Parser, cp, ep, m);
    return static_cast<size_t>(m);
  }

  // otherwise, read and ignore the specified number of bytes
  size_t n = l;
  while (n != 0 && this->CheckBuffer(cp, ep, 2))
  {
    size_t m = ep - cp;
    if (m > n) { m = n; }
    cp += m;
    n -= m;
  }

  return l - n;
}

//----------------------------------------------------------------------------
template<int E>
size_t Decoder<E>::ReadElementHead(
  const unsigned char* &cp, const unsigned char* &ep,
  vtkDICOMTag tag, vtkDICOMVR &vr, unsigned int &vl)
{
  // basic size is 4 bytes
  size_t l = 4;

  // sequence and item delimiters are always decoded as implicit
  if (this->ImplicitVR || tag.GetGroup() == HxFFFE)
  {
    // implicit VR
    vl = Decoder<E>::GetInt32(cp);
    // ignore vl in group length tags, it is corrupt in some files
    // and we know that it should always have a value of "4".
    if (tag.GetElement() == 0x0000) { vl = 4; }
    cp += 4;
  }
  else
  {
    // explicit VR
    bool implicit = false;
    vr = vtkDICOMVR(cp);
    vl = Decoder<E>::GetInt16(cp + 2);
    cp += 4;
    if (!vr.IsValid())
    {
      // invalid vr, try to get VR from dictionary instead
      vr = this->Context->FindDictVR(tag);
      // check that vr was composed of reasonable chars
      if (cp[-4] < 0x20 || cp[-4] >= 0x7f ||
          cp[-3] < 0x20 || cp[-3] >= 0x7f)
      {
        // if VR is not a printable character within the default character
        // set, assume implicit encoding for this particular element
        implicit = true;
        vl = Decoder<E>::GetInt32(cp - 4);
      }
    }
    if (!implicit && vr.HasLongVL())
    {
      // for OB, OD, OF, OL, OW, SQ, UC, UN, UR, UT, and unrecognized
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
size_t Decoder<E>::ReadElementValue(
  const unsigned char* &cp, const unsigned char* &ep,
  vtkDICOMVR vr, unsigned int vl, vtkDICOMValue &v)
{
  size_t l = 0;

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
  else if (static_cast<size_t>(ep - cp) < static_cast<size_t>(vl))
  {
    // value is larger than what remains in buffer,
    // make sure there are enough bytes left in file
    vtkTypeInt64 bytesRemaining =
      vtkDICOMParserInternalFriendship::GetBytesRemaining(
          this->Parser, cp, ep);
    if (static_cast<vtkTypeInt64>(vl) > bytesRemaining)
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
      char *ptr;
      if (vr.HasSpecificCharacterSet() &&
          this->LastTag > DC::SpecificCharacterSet)
      {
        ptr = v.AllocateCharData(vr, this->Context->GetCharacterSet(), vl);
      }
      else
      {
        ptr = v.AllocateCharData(vr, vl);
      }
      l = this->ReadData(cp, ep, ptr, vl);
      // AllocateCharData makes room for terminal null
      if (l == 0 || ptr[l-1] != '\0') { ptr[l] = '\0'; }
      v.ComputeNumberOfValuesForCharData();
      break;
    }
    case VTK_UNSIGNED_CHAR:
    {
      unsigned char *ptr = v.AllocateUnsignedCharData(vr, vl);
      l = this->ReadData(cp, ep, ptr, vl);
      break;
    }
    case VTK_SHORT:
    {
      unsigned int n = vl/sizeof(short);
      short *ptr = v.AllocateShortData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      break;
    }
    case VTK_UNSIGNED_SHORT:
    {
      unsigned int n = vl/sizeof(unsigned short);
      unsigned short *ptr = v.AllocateUnsignedShortData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      break;
    }
    case VTK_INT:
    {
      unsigned int n = vl/sizeof(int);
      int *ptr = v.AllocateIntData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      break;
    }
    case VTK_UNSIGNED_INT:
    {
      unsigned int n = vl/sizeof(unsigned int);
      unsigned int *ptr = v.AllocateUnsignedIntData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      break;
    }
    case VTK_FLOAT:
    {
      unsigned int n = vl/sizeof(float);
      float *ptr = v.AllocateFloatData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      break;
    }
    case VTK_DOUBLE:
    {
      unsigned int n = vl/sizeof(double);
      double *ptr = v.AllocateDoubleData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      break;
    }
    case VTK_DICOM_TAG:
    {
      unsigned int n = vl/sizeof(vtkDICOMTag);
      vtkDICOMTag *ptr = v.AllocateTagData(vr, n);
      l = this->ReadData(cp, ep, ptr, n);
      break;
    }
    case VTK_DICOM_ITEM:
    {
      vtkDICOMTag tag = this->LastTag;
      vtkDICOMSequence seq;
      bool queryMatched = false;
      l = 0;
      while (l < static_cast<size_t>(vl) || vl == HxFFFFFFFF)
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
          size_t offset = this->GetByteOffset(cp, ep) - 8;
          bool delimited = (il == HxFFFFFFFF);
          vtkDICOMTag endtag(HxFFFE, HxE00D);
          vtkDICOMItem item(this->Context->GetCharacterSet(),
                            this->Context->GetVRForXS(),
                            delimited, static_cast<unsigned int>(offset));
          DecoderContext context(&item, this->Parser->GetDefaultCharacterSet(),
                                 this->Parser->GetOverrideCharacterSet());
          this->PushContext(&context, tag);

          if (this->HasQuery)
          {
            if (this->QueryOneItem(cp, ep, il, endtag, l))
            {
              queryMatched = true;
              seq.AddItem(item);
            }
          }
          else
          {
            this->ReadElements(cp, ep, il, endtag, l);
            seq.AddItem(item);
          }

          this->PopContext();
        }
        else if (g == HxFFFE && e == HxE0DD)
        {
          // sequence delimiter found
          break;
        }
        else
        {
          // non-item tag found, skip to end if vl is known
          if (vl != HxFFFFFFFF)
          {
            l += this->SkipData(cp, ep, static_cast<size_t>(vl) - l);
          }
          break;
        }
      }
      if (vl != HxFFFFFFFF)
      {
        // if vl != 0xffffffff, then the sequence was fixed-size rather
        // than delimited, so let's make our own fixed-size sequence and
        // copy all of the items into it
        unsigned int n = static_cast<unsigned int>(seq.GetNumberOfItems());
        vtkDICOMSequence seq2(n);
        for (unsigned int i = 0; i < n; i++)
        {
          seq2.SetItem(i, seq.GetItem(i));
        }
        seq = seq2;
      }
      v = seq;

      // save whether query matched for any of the items
      if (this->HasQuery)
      {
        this->QueryMatched = queryMatched;
      }

      // reset the tag and VR as we step out of the sequence
      this->LastTag = tag;
      this->LastVR = vr;
      this->LastVL = vl;
      break;
    }
  }

  return l;
}

//----------------------------------------------------------------------------
template<int E>
bool Decoder<E>::ReadElements(
  const unsigned char* &cp, const unsigned char* &ep,
  unsigned int l, vtkDICOMTag delimiter, size_t &bytesRead)
{
  size_t tl = 0;

  // does delimiter specify a single group to read?
  unsigned short group = delimiter.GetGroup();
  bool readGroup = (delimiter.GetElement() == 0x0000);

  while (tl < static_cast<size_t>(l) || l == HxFFFFFFFF)
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
    size_t hl = this->ReadElementHead(cp, ep, tag, vr, vl);
    tl += 4 + hl;

    // return false if could not read element
    if (hl == 0) { return false; }

    // if VR wasn't in the element head (e.g. implicit), use dictionary
    if (!vr.IsValid()) { vr = this->Context->FindDictVR(tag); }

    // save this as the most recent tag
    this->LastTag = tag;
    this->LastVR = vr;
    this->LastVL = vl;

    // break if delimiter found
    if (!readGroup && tag == delimiter) { break; }

    // skip the value if this tag is not in the query
    if (this->HasQuery && !this->QueryContains(tag))
    {
      if (vl != HxFFFFFFFF)
      {
        // constant length item
        size_t sl = this->SkipData(cp, ep, vl);
        tl += sl;
        if (sl != static_cast<size_t>(vl)) { return false; }
      }
      else
      {
        // if vl == 0xffffffff, the value is delimited
        vtkDICOMTag newdelim(HxFFFE, HxE0DD);
        if (tag == vtkDICOMTag(HxFFFE, HxE000))
        { // if tag is item tag, use item delimiter
          newdelim = vtkDICOMTag(HxFFFE, HxE00D);
        }
        if (vr != vtkDICOMVR::UN)
        {
          // Value is either a sequence or is encapsulated data
          if (!this->SkipElements(cp, ep, vl, newdelim, NULL))
          {
            return false;
          }
        }
        else
        {
          // VR of UN indicates the value is an implicit LE sequence
          if (!this->ImplicitLE->SkipElements(cp, ep, vl, newdelim, NULL))
          {
            return false;
          }
        }
      }
      continue;
    }

    // read the value
    vtkDICOMValue v;
    size_t rl = 0;
    if (vr == vtkDICOMVR::UN && !this->ImplicitVR)
    {
      // if it was explicitly labeled 'UN' then check dictionary
      vr = this->Context->FindDictVR(tag);
      this->LastVR = vr; // save true VR, rather than recorded VR
      rl = this->ImplicitLE->ReadElementValue(cp, ep, vr, vl, v);
    }
    else
    {
      rl = this->ReadElementValue(cp, ep, vr, vl, v);
    }

    // was it a short read?
    if (rl < static_cast<size_t>(vl) && vl != HxFFFFFFFF)
    {
      size_t dl = static_cast<size_t>(vl) - rl;
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
      this->Item->Set(tag, v);
    }
    else if (this->Index < 0)
    {
      this->MetaData->Set(tag, v);
    }
    else
    {
      this->MetaData->Set(this->Index, tag, v);
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

    // check if the value matches the query
    if (this->HasQuery && !this->QueryMatches(v))
    {
      this->QueryMatched = false;
    }
  }

  // if reading by group, advance the query to the next group
  if (readGroup && this->HasQuery && this->QueryMatched)
  {
    this->AdvanceQueryIterator(vtkDICOMTag(group+1, 0x0000));
  }

  bytesRead += tl;

  return true;
}

//----------------------------------------------------------------------------
template<int E>
bool Decoder<E>::QueryOneItem(
  const unsigned char* &cp, const unsigned char* &ep,
  unsigned int l, vtkDICOMTag delimiter, size_t &bytesRead)
{
  assert(this->Query != this->QueryEnd);

  // save the current query state before going one level deeper
  bool queryMatched = this->QueryMatched;
  vtkDICOMDataElementIterator query = this->Query;
  vtkDICOMDataElementIterator queryEnd = this->QueryEnd;
  vtkDICOMDataElementIterator querySave = this->QuerySave;

  // if query element is empty, then use universal matching:
  // set default HasQuery to 'false' to match everything
  this->HasQuery = false;

  // if query sequence isn't empty, set HasQuery to 'true' and
  // use the sequence item as the new data set query
  if (query->GetValue().GetNumberOfValues() > 0)
  {
    const vtkDICOMItem *qitems = query->GetValue().GetSequenceData();
    if (qitems != 0 && qitems[0].GetNumberOfDataElements() != 0)
    {
      this->HasQuery = true;
      this->QueryMatched = true;
      this->Query = qitems[0].Begin();
      this->QueryEnd = qitems[0].End();
      this->QuerySave = this->Query;
    }
  }

  this->ReadElements(cp, ep, l, delimiter, bytesRead);

  // check query keys up to the end of the item
  if (this->HasQuery)
  {
    this->AdvanceQueryIterator(vtkDICOMTag(0xffff,0xffff));
  }

  bool matched = (this->QueryMatched & queryMatched);

  // restore the query state
  this->HasQuery = true;
  this->QueryMatched = queryMatched;
  this->Query = query;
  this->QueryEnd = queryEnd;
  this->QuerySave = querySave;

  return matched;
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
      vtkDICOMTag tag(g, e);
      unsigned int vl = 0;
      vtkDICOMVR vr;

      if (this->ReadElementHead(cp, ep, tag, vr, vl) == 0) { return false; }

      // save this as the most recent tag
      this->LastTag = tag;
      this->LastVR = vr;
      this->LastVL = vl;

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
        if (v != 0 && static_cast<size_t>(vl) > static_cast<size_t>(ep - cp))
        {
          // if vl is larger than number of bytes left in buffer,
          // then copy data from save point "sp" up to "cp" into v,
          // and read the value into "v".
          size_t m = cp - sp;
          size_t n = v->GetNumberOfValues();
          unsigned char *ptr = v->ReallocateUnsignedCharData(n + vl + m) + n;
          if (m) { do { *ptr++ = *sp++; } while (--m); }
          size_t tl = this->ReadData(cp, ep, ptr, vl);
          sp = cp;
          if (tl != static_cast<size_t>(vl)) { return false; }
        }
        else
        {
          size_t tl = this->SkipData(cp, ep, vl);
          if (tl != static_cast<size_t>(vl)) { return false; }
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
    size_t tl;
    if (v != 0)
    {
      // read bytes into the value "v"
      size_t n = v->GetNumberOfValues();
      unsigned char *ptr = v->ReallocateUnsignedCharData(n + l) + n;
      tl = this->ReadData(cp, ep, ptr, l);
      if (tl != static_cast<size_t>(l)) { return false; }
    }
    else
    {
      // simply skip "l" bytes
      tl = this->SkipData(cp, ep, l);
      if (tl != static_cast<size_t>(l)) { return false; }
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
  this->Query = NULL;
  this->QueryItem = NULL;
  this->Groups = NULL;
  this->InputFile = NULL;
  this->BytesRead = 0;
  this->FileOffset = 0;
  this->FileSize = 0;
  this->Buffer = NULL;
  this->BufferSize = 8192;
  this->ChunkSize = 0;
  this->Index = -1;
  this->PixelDataVL = 0;
  this->PixelDataFound = false;
  this->QueryMatched = false;
  this->DefaultCharacterSet = vtkDICOMCharacterSet::GetGlobalDefault();
  this->OverrideCharacterSet = vtkDICOMCharacterSet::GetGlobalOverride();
  this->ErrorCode = 0;
}

// Destructor
vtkDICOMParser::~vtkDICOMParser()
{
  delete [] this->FileName;
  delete this->QueryItem;

  if (this->MetaData)
  {
    this->MetaData->Delete();
  }
  if (this->Query)
  {
    this->Query->Delete();
  }
  if (this->Groups)
  {
    this->Groups->Delete();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMParser::SetQueryItem(const vtkDICOMItem& query)
{
  if (this->Query)
  {
    this->Query->Delete();
    this->Query = 0;
  }
  delete this->QueryItem;
  this->QueryItem = 0;
  if (query.GetNumberOfDataElements() > 0)
  {
    this->QueryItem = new vtkDICOMItem(query);
  }
}

//----------------------------------------------------------------------------
void vtkDICOMParser::SetDefaultCharacterSet(vtkDICOMCharacterSet cs)
{
  if (this->DefaultCharacterSet != cs)
  {
    this->DefaultCharacterSet = cs;
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMParser::SetOverrideCharacterSet(bool b)
{
  if (this->OverrideCharacterSet != b)
  {
    this->OverrideCharacterSet = b;
    this->Modified();
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
  if (this->MetaData)
  {
    this->MetaData->Modified();
  }
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::ReadFile(vtkDICOMMetaData *data, int idx)
{
  // Mark pixel data as not found yet
  this->PixelDataFound = false;
  this->QueryMatched = (this->Query != 0 || this->QueryItem != 0);
  this->FileOffset = 0;
  this->FileSize = 0;

  // Check that the file name has been set.
  if (!this->FileName)
  {
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    vtkErrorMacro("ReadFile: No file name has been set");
    return false;
  }

  // Make sure that the file is readable.
  vtkDICOMFile infile(this->FileName, vtkDICOMFile::In);
  if (infile.GetError())
  {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    const char *errText = "Can't open the file ";
    if (infile.GetError() == vtkDICOMFile::AccessDenied)
    {
      errText = "No permission to read the file ";
    }
    else if (infile.GetError() == vtkDICOMFile::FileIsDirectory)
    {
      errText = "The selected file is a directory ";
    }
    vtkErrorMacro("ReadFile: " << errText << this->FileName);
    return false;
  }

  this->InputFile = &infile;
  this->FileSize = infile.GetSize();
  this->Buffer = new unsigned char [this->BufferSize + 8];
  this->BytesRead = 0;
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
  infile.Close();
  this->InputFile = NULL;

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::ReadMetaHeader(
  const unsigned char* &cp, const unsigned char* &ep,
  vtkDICOMMetaData *meta, int idx)
{
  // get the meta information group length
  unsigned short g = Decoder<LE>::GetInt16(cp);
  unsigned short e = Decoder<LE>::GetInt16(cp + 2);
  vtkDICOMVR vr = vtkDICOMVR(cp + 4);
  unsigned int vl = Decoder<LE>::GetInt16(cp + 6);

  // verify that this is the right tag
  if (g == 0x0002)
  {
    // make a temporary MetaData object if none was provided
    bool tempMeta = false;
    if (meta == 0)
    {
      meta = vtkDICOMMetaData::New();
      tempMeta = true;
    }

    LittleEndianDecoder decoder(this, meta, idx);

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
    this->TransferSyntax = meta->Get(i, DC::TransferSyntaxUID).AsString();

    if (tempMeta)
    {
      meta->Delete();
    }
  }
  else
  {
    this->TransferSyntax = "";
  }

  this->FileOffset = this->GetBytesProcessed(cp, ep);

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
           tsyntax == "1.2.840.10008.1.20" || // Papyrus Implicit LE
           tsyntax == "1.2.840.113619.5.2")   // GE Implicit LE
  {
    decoder->SetImplicitVR(true);
  }
  else if (tsyntax == "1.2.840.10008.1.2.2") // Explicit BE
  {
    decoder = &decoderBE;
  }

  // get the Query
  vtkDICOMDataElementIterator iter;
  vtkDICOMDataElementIterator iterEnd;
  bool hasQuery = false;
  if (this->Query)
  {
    hasQuery = true;
    iter = this->Query->Begin();
    iterEnd = this->Query->End();
  }
  else if (this->QueryItem)
  {
    hasQuery = true;
    iter = this->QueryItem->Begin();
    iterEnd = this->QueryItem->End();
  }

  if (hasQuery)
  {
    // skip any elements in groups less than 0002
    while (iter != iterEnd && iter->GetTag().GetGroup() < 0x0002)
    {
      ++iter;
    }

    if (iter->GetTag() == vtkDICOMTag(0x0002,0x0000))
    {
      // if FileMetaInformationGroupLength is set, assume that the
      // query was read from a file and that we don't actually want
      // to query the meta header
      while (iter != iterEnd && iter->GetTag().GetGroup() <= 0x0002)
      {
        ++iter;
      }
    }
    else
    {
      // check the query against the meta header, which was already read
      bool matched = true;
      vtkDICOMDataElementIterator metaIter = meta->Begin();
      vtkDICOMDataElementIterator metaEnd = meta->End();
      while (metaIter != metaEnd && iter != iterEnd &&
             iter->GetTag().GetGroup() <= 0x0002)
      {
        if (metaIter->GetTag() == iter->GetTag())
        {
          matched &= metaIter->GetValue(this->Index).Matches(iter->GetValue());
          ++iter;
          ++metaIter;
        }
        else if (metaIter->GetTag() < iter->GetTag())
        {
          ++metaIter;
        }
        else
        {
          // this is a mismatch unless the query key is for universal matching
          vtkDICOMValue nullValue;
          matched &= nullValue.Matches(iter->GetValue());
          ++iter;
        }
      }
      this->QueryMatched &= matched;
    }

    // set the query for the decoder so it can scan the rest of the file
    decoder->SetQuery(iter, iterEnd);
  }

  // make a list of the groups of interest
  std::vector<unsigned short> groups;
  if (hasQuery)
  {
    unsigned short lastg = 0;
    while (iter != iterEnd)
    {
      unsigned short g = iter->GetTag().GetGroup();
      if (g > lastg)
      {
        lastg = g;
        groups.push_back(g);
      }
      ++iter;
    }
  }
  else if (this->Groups)
  {
    vtkIdType n = this->Groups->GetNumberOfTuples();
    for (vtkIdType i = 0; i < n; i++)
    {
      groups.push_back(this->Groups->GetValue(i));
    }
    std::sort(groups.begin(),groups.end());
    groups.erase(std::unique(groups.begin(),groups.end()), groups.end());
  }

  // iterator for going through the groups to read
  std::vector<unsigned short>::iterator giter = groups.begin();

  // read group-by-group
  bool readFailure = false;
  bool queryFailure = (hasQuery && !this->QueryMatched);
  bool bailOnQueryFailure = (meta && meta->GetNumberOfInstances() == 1);
  while (!readFailure && (!queryFailure || !bailOnQueryFailure))
  {
    vtkDICOMTag tag = decoder->Peek(cp, ep);

    // if there is no data left to decode, then break
    if (cp == ep) { break; }

    // do we want to read or skip this group?
    bool found = true;
    if (!groups.empty())
    {
      while (giter != groups.end() && *giter < tag.GetGroup())
      {
        ++giter;
      }
      found = (giter != groups.end() && *giter == tag.GetGroup());
    }

    // create a delimiter to read/skip only this group
    vtkDICOMTag delimiter(tag.GetGroup(), 0);

    // check for PixelData group 0x7fe0, or obsolete 0x7fxx
    unsigned int l = HxFFFFFFFF;
    if ((tag.GetGroup() & 0xff01) == 0x7f00)
    {
      if (tag.GetElement() == 0x0000)
      {
        // have to read "group length" before pixel data
        l = 12;
      }
      else
      {
        // set delimiter to pixel data tag
        delimiter = tag;
      }
    }

    if (found && meta)
    {
      readFailure = !decoder->ReadElements(cp, ep, l, delimiter);
      queryFailure = (hasQuery && !decoder->GetQueryMatched());
    }
    else
    {
      readFailure = !decoder->SkipElements(cp, ep, l, delimiter);
    }

    // check whether a PixelData element was found
    vtkDICOMTag lastTag = decoder->GetLastTag();
    if (!readFailure && lastTag == delimiter &&
        lastTag.GetElement() != 0x0000)
    {
      if (lastTag.GetGroup() == 0x7fe0)
      {
        this->FileOffset = this->GetBytesProcessed(cp, ep);
        this->PixelDataFound = true;
        this->PixelDataVL = decoder->GetLastVL();
      }

      if (meta)
      {
        // add PixelData as an empty attribute, since we did not read its
        // value (the FileOffset was saved so it can be read later)
        vtkDICOMVR lastVR = decoder->GetLastVR();
        if (!lastVR.IsValid())
        {
          lastVR = vtkDICOMVR::OW;
          const vtkDICOMValue& ba = meta->Get(idx, DC::BitsAllocated);
          if (ba.IsValid() && ba.AsUnsignedInt() <= 8)
          {
            lastVR = vtkDICOMVR::OB;
          }
        }

        if (idx >= 0)
        {
          meta->Set(idx, lastTag, vtkDICOMValue(lastVR));
          decoder->HandleMissingAttributes(lastTag);
        }
        else
        {
          meta->Set(lastTag, vtkDICOMValue(lastVR));
        }
      }

      // skip over the PixelData
      unsigned int vl = decoder->GetLastVL();
      vtkTypeInt64 r = this->GetBytesRemaining(cp, ep);
      if (vl != 0xFFFFFFFF && r == static_cast<vtkTypeInt64>(vl))
      {
        // end of pixel data is end of file
        break;
      }
      if ((vl != 0xFFFFFFFF && r < static_cast<vtkTypeInt64>(vl)) ||
          !this->SkipValue(cp, ep, vl))
      {
        this->ParseError(cp, ep,
          "Premature end of file while reading PixelData.");
        readFailure = true;
      }
    }
  }

  this->QueryMatched &= decoder->FinishQuery();

  if (!this->PixelDataFound)
  {
    // if no pixel data, set FileOffset to current file position
    this->FileOffset = this->GetBytesProcessed(cp, ep);
  }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::FillBuffer(
  const unsigned char* &ucp, const unsigned char* &ep)
{
  unsigned char *dp = this->Buffer;
  size_t n = ep - ucp;
  const unsigned char *cp = ucp;

  // number of bytes to read
  size_t nbytes = this->ChunkSize;
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
  else if (this->InputFile->GetError())
  {
    this->SetErrorCode(vtkErrorCode::UnknownError);
    vtkErrorMacro("FillBuffer: error reading from file " << this->FileName);
    return false;
  }
  else if (this->InputFile->EndOfFile())
  {
    // if buffer is drained, and eof, then done
    return false;
  }

  // read at most n bytes
  n = this->InputFile->Read(dp, nbytes);

  // get number of chars read
  this->BytesRead += n;

  // ep is recycled chars plus newly read chars
  ep = dp + n;
  ucp = this->Buffer;

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::SeekBuffer(
  const unsigned char* &ucp, const unsigned char* &ep, vtkTypeInt64 offset)
{
  // if we can advance within the buffer, then do so
  if (offset > 0 && static_cast<vtkTypeInt64>(ep - ucp) >= offset)
  {
    ucp += offset;
    return true;
  }

  // otherwise, seek within the file
  vtkTypeInt64 pos = this->GetBytesProcessed(ucp, ep);
  if (!this->InputFile->GetError() &&
      this->InputFile->SetPosition(pos + offset))
  {
    // read just 8 bytes at the new position, i.e. enough to take a peek
    // at the next element
    size_t n = this->InputFile->Read(this->Buffer, 8);
    ucp = this->Buffer;
    ep = ucp + n;
    this->BytesRead = pos + offset + n;
    return true;
  }

  return false;
}

//----------------------------------------------------------------------------
bool vtkDICOMParser::SkipValue(
    const unsigned char* &cp, const unsigned char* &ep,
    unsigned int vl)
{
  if (vl != 0xFFFFFFFF)
  {
    // reset buffer to new file position
    return this->SeekBuffer(cp, ep, vl);
  }

  // skip encapsulated data
  while ((ep - cp) >= 8 || this->FillBuffer(cp, ep))
  {
    unsigned int t = Decoder<LE>::GetInt32(cp);
    unsigned int l = Decoder<LE>::GetInt32(cp + 4);
    cp += 8;
    if (t == 0xE0DDFFFE)
    {
      return true;
    }
    if (t != 0xE000FFFE || !this->SkipValue(cp, ep, l))
    {
      break;
    }
  }

  return false;
}

//----------------------------------------------------------------------------
vtkTypeInt64 vtkDICOMParser::GetBytesRemaining(
  const unsigned char *cp, const unsigned char *ep)
{
  return static_cast<vtkTypeInt64>(
    this->FileSize - this->BytesRead + (ep - cp));
}

//----------------------------------------------------------------------------
vtkTypeInt64 vtkDICOMParser::GetBytesProcessed(
  const unsigned char* cp, const unsigned char* ep)
{
  // the offset is the number of bytes read minus
  // the number of bytes remaining in the buffer.
  return this->BytesRead - (ep - cp);
}

//----------------------------------------------------------------------------
void vtkDICOMParser::ParseError(
  const unsigned char* cp, const unsigned char* ep, const char* message)
{
  this->FileOffset = this->GetBytesProcessed(cp, ep);
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
  os << indent << "DefaultCharacterSet: "
     << this->DefaultCharacterSet << "\n";
  os << indent << "OverrideCharacterSet: "
     << (this->OverrideCharacterSet ? "On\n" : "Off\n");
  os << indent << "PixelDataFound: "
     << (this->PixelDataFound ? "True\n" : "False\n");
  os << indent << "PixelDataVL: " << this->PixelDataVL << "\n";
  os << indent << "FileOffset: " << this->FileOffset << "\n";
  os << indent << "FileSize: " << this->FileSize << "\n";
  os << indent << "MetaData: " << this->MetaData << "\n";
  os << indent << "Index: " << this->Index << "\n";
  os << indent << "BufferSize: " << this->BufferSize << "\n";
  os << indent << "Query: " << this->Query << "\n";
  os << indent << "QueryItem: " << this->QueryItem << "\n";
  os << indent << "QueryMatched: "
     << (this->QueryMatched ? "True\n" : "False\n");
  os << indent << "Groups: " << this->Groups << "\n";
}
