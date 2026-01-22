/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMMetaData.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include "vtkObjectFactory.h"
#include "vtkMatrix4x4.h"
#include "vtkAbstractArray.h"
#include "vtkIntArray.h"

#include <assert.h>
#include <vector>
#include <utility>

vtkStandardNewMacro(vtkDICOMMetaData);

// The hash table size, must be a power of two
#define METADATA_HASH_SIZE 512

//----------------------------------------------------------------------------
// Constructor
vtkDICOMMetaData::vtkDICOMMetaData()
{
  this->NumberOfInstances = 1;
  this->NumberOfDataElements = 0;
  this->Table = nullptr;
  this->Head.Prev = nullptr;
  this->Head.Next = &this->Tail;
  this->Tail.Prev = &this->Head;
  this->Tail.Next = nullptr;
  this->FileIndexArray = nullptr;
  this->FrameIndexArray = nullptr;
}

// Destructor
vtkDICOMMetaData::~vtkDICOMMetaData()
{
  this->Clear();
  if (this->FileIndexArray)
  {
    this->FileIndexArray->Delete();
  }
  if (this->FrameIndexArray)
  {
    this->FrameIndexArray->Delete();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::Clear()
{
  vtkDICOMDataElement **htable = this->Table;

  if (htable)
  {
    for (unsigned int i = 0; i < METADATA_HASH_SIZE; i++)
    {
      delete [] htable[i];
    }
    delete [] htable;
  }

  this->NumberOfDataElements = 0;
  this->Table = nullptr;
  this->Head.Next = &this->Tail;
  this->Tail.Prev = &this->Head;
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::Initialize()
{
  this->Clear();
  this->NumberOfInstances = 1;
  if (this->FileIndexArray)
  {
    this->FileIndexArray->Delete();
    this->FileIndexArray = nullptr;
  }
  if (this->FrameIndexArray)
  {
    this->FrameIndexArray->Delete();
    this->FrameIndexArray = nullptr;
  }
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::SetNumberOfInstances(int n)
{
  if (this->Table != nullptr)
  {
    vtkErrorMacro("SetNumberOfInstances: Cannot set NumberOfInstances after "
                  "attributes have been added");
  }
  else
  {
    this->NumberOfInstances = n;
  }
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::SetFileIndexArray(vtkIntArray *a)
{
  if (this->FileIndexArray != a)
  {
    if (this->FileIndexArray)
    {
      this->FileIndexArray->Delete();
    }
    this->FileIndexArray = a;
    if (this->FileIndexArray)
    {
      this->FileIndexArray->Register(this);
    }
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::SetFrameIndexArray(vtkIntArray *a)
{
  if (this->FrameIndexArray != a)
  {
    if (this->FrameIndexArray)
    {
      this->FrameIndexArray->Delete();
    }
    this->FrameIndexArray = a;
    if (this->FrameIndexArray)
    {
      this->FrameIndexArray->Register(this);
    }
    this->Modified();
  }
}

//----------------------------------------------------------------------------
// Erase an element from the hash table
void vtkDICOMMetaData::Erase(vtkDICOMTag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMDataElement **htable = this->Table;
  vtkDICOMDataElement *hptr;

  if (htable && (hptr = htable[i]) != nullptr)
  {
    while (hptr->Next != nullptr)
    {
      if (hptr->Tag == tag)
      {
        // remove from the linked list
        hptr->Next->Prev = hptr->Prev;
        hptr->Prev->Next = hptr->Next;
        // remove from the hash table
        hptr[0] = hptr[1];
        while (hptr->Next != nullptr)
        {
          // adjust links as necessary
          hptr->Prev->Next = hptr;
          hptr->Next->Prev = hptr;
          hptr++;
          hptr[0] = hptr[1];
        }
        this->NumberOfDataElements--;
        break;
      }
      hptr++;
    }
  }
}

//----------------------------------------------------------------------------
// Get an element from the hash table.
vtkDICOMDataElement *vtkDICOMMetaData::FindDataElement(
  vtkDICOMTag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMDataElement **htable = this->Table;
  vtkDICOMDataElement *hptr;

  if (htable && (hptr = htable[i]) != nullptr)
  {
    while (hptr->Next != nullptr)
    {
      if (hptr->Tag == tag)
      {
        return hptr;
      }
      hptr++;
    }
  }

  return nullptr;
}

//----------------------------------------------------------------------------
bool vtkDICOMMetaData::Has(vtkDICOMTag tag)
{
  return (this->FindDataElement(tag) != nullptr);
}

//----------------------------------------------------------------------------
const vtkDICOMValue *vtkDICOMMetaData::FindAttributeValue(
  int idx, vtkDICOMTag tag)
{
  vtkDICOMDataElement *a = this->FindDataElement(tag);
  const vtkDICOMValue *vptr = nullptr;

  if (a != nullptr)
  {
    vptr = &a->Value;
    // is this a sequence of values?
    const vtkDICOMValue *sptr = vptr->GetMultiplexData();
    if (sptr)
    {
      size_t n = vptr->GetNumberOfValues();
      vptr = nullptr;
      if (idx >= 0 && static_cast<size_t>(idx) < n)
      {
        if (sptr[idx].IsValid())
        {
          vptr = &sptr[idx];
        }
      }
    }
  }

  return vptr;
}

//----------------------------------------------------------------------------
const vtkDICOMValue *vtkDICOMMetaData::FindAttributeValue(
  int idx, const vtkDICOMTagPath& tagpath)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(idx, tagpath.GetHead());
  if (vptr != nullptr && tagpath.HasTail())
  {
    size_t i = tagpath.GetIndex();
    size_t n = vptr->GetNumberOfValues();
    const vtkDICOMItem *items = vptr->GetSequenceData();
    vptr = nullptr;
    if (items != nullptr && i < n)
    {
      vptr = &items[i].Get(tagpath.GetTail());
      if (!vptr->IsValid())
      {
        vptr = nullptr;
      }
    }
  }
  return vptr;
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::Get(vtkDICOMTag tag)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(0, tag);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::Get(int idx, vtkDICOMTag tag)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(idx, tag);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::Get(const vtkDICOMTagPath &tagpath)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(0, tagpath);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::Get(
  int idx, const vtkDICOMTagPath &tagpath)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(idx, tagpath);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::Get(
  int idx, int frame, const vtkDICOMTagPath &tagpath)
{
  // if either of these is present in an enhanced DICOM file, then they
  // will be searched before the root is searched
  const DC::EnumType fgs[2] = {
    DC::PerFrameFunctionalGroupsSequence,
    DC::SharedFunctionalGroupsSequence
  };

  // for temporarily saving location to private value (see below)
  const vtkDICOMValue *privateValue = nullptr;

  // search PerFrame and then Shared functional sequences, if present
  // (if frame is "-1", then only search SharedFunctionalGroups)
  int istart = (frame < 0 ? 1 : 0);
  for (int i = istart; i < 2; i++)
  {
    // we only need the frame number for the PerFrame sequence
    size_t f = (i == 0 ? frame : 0);
    const vtkDICOMValue *seq = this->FindAttributeValue(idx, fgs[i]);
    if (seq && f < seq->GetNumberOfValues())
    {
      // search for the item that matches the frame
      const vtkDICOMItem *items = seq->GetSequenceData();
      const vtkDICOMValue &v = items[f].Get(tagpath);
      if (v.IsValid())
      {
        return v;
      }
      // search within all the sequences in the item
      vtkDICOMDataElementIterator iter = items[f].Begin();
      vtkDICOMDataElementIterator iterEnd = items[f].End();
      while (iter != iterEnd)
      {
        const vtkDICOMValue &u = iter->GetValue();
        if (u.GetNumberOfValues() == 1)
        {
          const vtkDICOMItem *item = u.GetSequenceData();
          if (item)
          {
            const vtkDICOMValue &w = item->Get(tagpath);
            if (w.IsValid())
            {
              if ((iter->GetTag().GetGroup() & 1) == 0)
              {
                return w;
              }
              else if (privateValue == nullptr)
              {
                // if we found the attribute in a private sequence,
                // then save but and keep searching to see if it will
                // eventually be found somewhere public
                privateValue = &w;
              }
            }
          }
        }
        ++iter;
      }
    }
  }

  // search root last of all
  const vtkDICOMValue *vptr = this->FindAttributeValue(idx, tagpath);

  // try private value (see above) if attribute wasn't found
  vptr = (vptr ? vptr : privateValue);

  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::Get(int idx, int frame, vtkDICOMTag tag)
{
  return this->Get(idx, frame, vtkDICOMTagPath(tag));
}

//----------------------------------------------------------------------------
int vtkDICOMMetaData::GetFileIndex(int sliceIdx)
{
  if (this->FileIndexArray == nullptr || sliceIdx < 0 ||
      sliceIdx >= this->FileIndexArray->GetNumberOfTuples())
  {
    return -1;
  }

  int n = this->FileIndexArray->GetNumberOfComponents();
  return this->FileIndexArray->GetValue(sliceIdx*n);
}

//----------------------------------------------------------------------------
int vtkDICOMMetaData::GetFileIndex(int sliceIdx, int compIdx, int numComp)
{
  if (this->FileIndexArray == nullptr || sliceIdx < 0 ||
      sliceIdx >= this->FileIndexArray->GetNumberOfTuples() ||
      compIdx < 0 || compIdx >= numComp)
  {
    return -1;
  }

  int n = this->FileIndexArray->GetNumberOfComponents();
  return this->FileIndexArray->GetValue(sliceIdx*n + compIdx*n/numComp);
}

//----------------------------------------------------------------------------
int vtkDICOMMetaData::GetFrameIndex(int sliceIdx)
{
  if (this->FrameIndexArray == nullptr || sliceIdx < 0 ||
      sliceIdx >= this->FrameIndexArray->GetNumberOfTuples())
  {
    return -1;
  }

  int n = this->FrameIndexArray->GetNumberOfComponents();
  return this->FrameIndexArray->GetValue(sliceIdx*n);
}

//----------------------------------------------------------------------------
int vtkDICOMMetaData::GetFrameIndex(int sliceIdx, int compIdx, int numComp)
{
  if (this->FrameIndexArray == nullptr || sliceIdx < 0 ||
      sliceIdx >= this->FrameIndexArray->GetNumberOfTuples() ||
      compIdx < 0 || compIdx >= numComp)
  {
    return -1;
  }

  int n = this->FrameIndexArray->GetNumberOfComponents();
  return this->FrameIndexArray->GetValue(sliceIdx*n + compIdx*n/numComp);
}

//----------------------------------------------------------------------------
// Return a reference to the element within the hash table, which can
// be used to insert a new value.
vtkDICOMDataElement *vtkDICOMMetaData::FindDataElementOrInsert(
  vtkDICOMTag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMDataElement **htable = this->Table;
  vtkDICOMDataElement *hptr;

  if (htable == nullptr)
  {
    // allocate the hash table
    m = METADATA_HASH_SIZE;
    htable = new vtkDICOMDataElement *[METADATA_HASH_SIZE];
    this->Table = htable;
    do { *htable++ = nullptr; } while (--m);
    htable = this->Table;
  }

  hptr = htable[i];

  if (hptr == nullptr)
  {
    hptr = new vtkDICOMDataElement[4];
    htable[i] = hptr;
  }
  else if (hptr->Next != nullptr)
  {
    // see if item is already there
    unsigned int n = 0;
    do
    {
      if (hptr->Tag == tag)
      {
        return hptr;
      }
      n++;
      hptr++;
    }
    while (hptr->Next != nullptr);

    // if n+1 is a power of two, double allocated space
    if (n > 2 && (n & (n+1)) == 0)
    {
      vtkDICOMDataElement *oldptr = htable[i];
      hptr = new vtkDICOMDataElement[2*(n+1)];
      htable[i] = hptr;
      // copy the old list
      for (unsigned int j = 0; j < n; j++)
      {
        *hptr = oldptr[j];
        // link the new element into the list
        hptr->Next->Prev = hptr;
        hptr->Prev->Next = hptr;
        hptr++;
      }
      delete [] oldptr;
    }
  }

  // insert into the linked list
  vtkDICOMDataElement *tptr = &this->Tail;
  do
  {
    tptr = tptr->Prev;
  }
  while (tag < tptr->GetTag());

  hptr->Prev = tptr;
  hptr->Next = tptr->Next;
  hptr->Prev->Next = hptr;
  hptr->Next->Prev = hptr;
  this->NumberOfDataElements++;

  return hptr;
}

//----------------------------------------------------------------------------
int vtkDICOMMetaData::FindItemsOrInsert(
  int idx, bool useidx, const vtkDICOMTagPath& tagpath,
  vtkDICOMItem *itemarray[])
{
  vtkDICOMTag tag = tagpath.GetHead();

  vtkDICOMDataElement *loc = this->FindDataElementOrInsert(tag);
  if (loc == nullptr)
  {
    vtkErrorMacro("SetAttributeValue: tag group number must not be zero.");
    return 0;
  }

  loc->Tag = tag;
  vtkDICOMValue *vptr = &loc->Value;
  if (!vptr->IsValid())
  {
    vtkDICOMVR vr = this->FindDictVR(idx, tag);
    if (vr != vtkDICOMVR::SQ && vr != vtkDICOMVR::UN)
    {
      // we just inserted a non-SQ value, remove it
      this->Erase(tag);
      return 0;
    }
  }
  else if (vptr->GetVR() != vtkDICOMVR::SQ)
  {
    return 0;
  }

  // is this a series of values?
  int count = 1;
  vtkDICOMValue *sptr = vtkDICOMValueFriendMetaData::GetMultiplex(vptr);
  if (sptr != nullptr)
  {
    if (useidx)
    {
      assert(idx >= 0 && idx < this->NumberOfInstances);
      sptr = &sptr[idx];
    }
    else
    {
      count = this->NumberOfInstances;
    }
  }
  else if (useidx && this->NumberOfInstances > 1)
  {
    // create a multiplex
    assert(idx >= 0 && idx < this->NumberOfInstances);
    int n = this->NumberOfInstances;
    vtkDICOMValue l;
    sptr = l.AllocateMultiplexData(vtkDICOMVR::SQ, n);
    for (int i = 0; i < n; i++)
    {
      if (i != idx)
      {
        sptr[i] = *vptr;
      }
    }
    *vptr = l;
    sptr = &sptr[idx];
  }
  else
  {
    sptr = vptr;
  }

  size_t i = tagpath.GetIndex();
  for (int k = 0; k < count; k++)
  {
    size_t n = i+1;
    size_t m = 0;
    const vtkDICOMItem *oldItems = sptr[k].GetSequenceData();
    if (oldItems != nullptr)
    {
      m = sptr[k].GetNumberOfValues();
      n = (n > m ? n : m);
    }
    vtkDICOMValue seq;
    vtkDICOMItem *items = seq.AllocateSequenceData(vtkDICOMVR::SQ, n);
    // copy the old sequence into the new one (shallow copy)
    for (size_t j = 0; j < m; j++)
    {
      items[j] = oldItems[j];
    }
    // Get the character set and default VR for XS
    vtkDICOMCharacterSet cs = vtkDICOMCharacterSet::ISO_IR_6;
    vtkDICOMVR vrForXS = vtkDICOMVR::US;
    if (n > m)
    {
      const vtkDICOMValue& vcs = this->Get(DC::SpecificCharacterSet);
      if (vcs.IsValid())
      {
        cs = vtkDICOMCharacterSet(vcs.GetCharData(), vcs.GetVL());
      }
      const vtkDICOMValue &v = this->Get(DC::PixelRepresentation);
      if (v.IsValid())
      {
        vrForXS = (v.AsUnsignedShort() == 0 ?
                   vtkDICOMVR::US : vtkDICOMVR::SS);
      }
    }
    for (size_t j = m; j < n; j++)
    {
      items[j] = vtkDICOMItem(cs, vrForXS);
    }
    sptr[k] = seq;
    itemarray[k] = &items[i];
  }

  return count;
}

vtkDICOMItem *vtkDICOMMetaData::FindItemOrInsert(
  int idx, const vtkDICOMTagPath& tagpath)
{
  vtkDICOMItem *itemptr = nullptr;
  this->FindItemsOrInsert(idx, true, tagpath, &itemptr);
  return itemptr;
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::SplitAndSetValue(
  vtkDICOMValue *vptr, int idx, const vtkDICOMValue& v)
{
  // split a value that used to be the same for all indices so
  // that it has a different value for 'idx'
  int n = this->NumberOfInstances;
  vtkDICOMValue l;
  vtkDICOMVR vr = (vptr->IsValid() ? vptr->GetVR() : v.GetVR());
  vtkDICOMValue *sptr = l.AllocateMultiplexData(vr, n);
  for (int i = 0; i < n; i++)
  {
    if (i == idx)
    {
      sptr[i] = v;
    }
    else
    {
      sptr[i] = *vptr;
    }
  }
  *vptr = l;
}

//----------------------------------------------------------------------------
// Insert an attribute for a particular image
vtkDICOMDataElementIterator vtkDICOMMetaData::InsertOrAssign(
  int idx, vtkDICOMTag tag, const vtkDICOMValue& v)
{
  vtkDICOMDataElement *loc = this->FindDataElementOrInsert(tag);
  if (loc == nullptr)
  {
    vtkErrorMacro("InsertOrAssign: tag group number must not be zero.");
    return &this->Tail;
  }
  else if (!v.IsValid())
  {
    vtkErrorMacro("InsertOrAssign: a valid value is required.");
    return &this->Tail;
  }

  loc->Tag = tag;
  vtkDICOMValue *vptr = &loc->Value;

  assert(idx >= 0 && idx < this->NumberOfInstances);

  // is this a sequence of values?
  vtkDICOMValue *sptr = vtkDICOMValueFriendMetaData::GetMultiplex(vptr);
  if (sptr)
  {
    sptr[idx] = v;
  }
  else if (v != *vptr)
  {
    this->SplitAndSetValue(vptr, idx, v);
  }

  return vtkDICOMDataElementIterator(loc);
}

//----------------------------------------------------------------------------
// Insert an attribute into the hash table
void vtkDICOMMetaData::Set(vtkDICOMTag tag, const vtkDICOMValue& v)
{
  if (v.IsValid())
  {
    vtkDICOMDataElement *loc = this->FindDataElementOrInsert(tag);
    if (loc == nullptr)
    {
      vtkErrorMacro("SetAttributeValue: tag group number must not be zero.");
      return;
    }
    loc->Tag = tag;
    loc->Value = v;
  }
  else
  {
    this->Erase(tag);
  }
}

void vtkDICOMMetaData::Set(vtkDICOMTag tag, double v)
{
  vtkDICOMVR vr = this->FindDictVR(0, tag);
  if (vr != vtkDICOMVR::UN)
  {
    this->Set(tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

void vtkDICOMMetaData::Set(vtkDICOMTag tag, const std::string& v)
{
  vtkDICOMVR vr = this->FindDictVR(0, tag);
  if (vr.HasSpecificCharacterSet() && tag > DC::SpecificCharacterSet)
  {
    this->Set(tag, this->MakeValueWithSpecificCharacterSet(vr, v));
  }
  else if (vr != vtkDICOMVR::UN)
  {
    this->Set(tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

//----------------------------------------------------------------------------
// Insert an attribute for a particular image
void vtkDICOMMetaData::Set(int idx, vtkDICOMTag tag, const vtkDICOMValue& v)
{
  vtkDICOMDataElement *loc = this->FindDataElementOrInsert(tag);
  if (loc == nullptr)
  {
    vtkErrorMacro("SetAttributeValue: tag group number must not be zero.");
    return;
  }

  loc->Tag = tag;
  vtkDICOMValue *vptr = &loc->Value;

  assert(idx >= 0 && idx < this->NumberOfInstances);

  // is this a sequence of values?
  vtkDICOMValue *sptr = vtkDICOMValueFriendMetaData::GetMultiplex(vptr);
  if (sptr)
  {
    sptr[idx] = v;
    if (!v.IsValid())
    {
      // if invalid value was added, make sure valid values remain
      bool valid = false;
      for (int i = 0; i < this->NumberOfInstances; i++)
      {
        valid |= sptr[i].IsValid();
      }
      if (!valid)
      {
        this->Erase(tag);
      }
    }
    else
    {
      // if all values are the same, replace with a single value
      bool same = true;
      for (int i = 0; i < this->NumberOfInstances && same; i++)
      {
        same = (i == idx || sptr[i] == v);
      }
      if (same)
      {
        loc->Value = v;
      }
    }
  }
  else if (v != *vptr)
  {
    // differs from other instances, must turn value into a list,
    // so create a value that is actually a list of values
    this->SplitAndSetValue(vptr, idx, v);
  }
  else if (!vptr->IsValid())
  {
    this->Erase(tag);
  }
}

void vtkDICOMMetaData::Set(int idx, vtkDICOMTag tag, double v)
{
  vtkDICOMVR vr = this->FindDictVR(idx, tag);
  if (vr != vtkDICOMVR::UN)
  {
    this->Set(idx, tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

void vtkDICOMMetaData::Set(int idx, vtkDICOMTag tag, const std::string& v)
{
  vtkDICOMVR vr = this->FindDictVR(idx, tag);
  if (vr.HasSpecificCharacterSet() && tag > DC::SpecificCharacterSet)
  {
    this->Set(idx, tag, this->MakeValueWithSpecificCharacterSet(vr, v));
  }
  else if (vr != vtkDICOMVR::UN)
  {
    this->Set(idx, tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

//----------------------------------------------------------------------------
// Insert an attribute at a particular path
void vtkDICOMMetaData::Set(
  const vtkDICOMTagPath& tagpath, const vtkDICOMValue& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem **items = new vtkDICOMItem *[this->NumberOfInstances];
    int n = this->FindItemsOrInsert(0, false, tagpath, items);
    for (int i = 0; i < n; i++)
    {
      items[i]->Set(tagpath.GetTail(), v);
    }
    delete [] items;
  }
  else
  {
    this->Set(tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::Set(const vtkDICOMTagPath& tagpath, double v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem **items = new vtkDICOMItem *[this->NumberOfInstances];
    int n = this->FindItemsOrInsert(0, false, tagpath, items);
    for (int i = 0; i < n; i++)
    {
      items[i]->Set(tagpath.GetTail(), v);
    }
    delete [] items;
  }
  else
  {
    this->Set(tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::Set(
  const vtkDICOMTagPath& tagpath, const std::string& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem **items = new vtkDICOMItem *[this->NumberOfInstances];
    int n = this->FindItemsOrInsert(0, false, tagpath, items);
    for (int i = 0; i < n; i++)
    {
      items[i]->Set(tagpath.GetTail(), v);
    }
    delete [] items;
  }
  else
  {
    this->Set(tagpath.GetHead(), v);
  }
}

//----------------------------------------------------------------------------
// Insert an attribute for a particular image
void vtkDICOMMetaData::Set(
  int idx, const vtkDICOMTagPath& tagpath, const vtkDICOMValue& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem *item = this->FindItemOrInsert(idx, tagpath);
    if (item)
    {
      item->Set(tagpath.GetTail(), v);
    }
  }
  else
  {
    this->Set(idx, tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::Set(int idx, const vtkDICOMTagPath& tagpath, double v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem *item = this->FindItemOrInsert(idx, tagpath);
    if (item)
    {
      item->Set(tagpath.GetTail(), v);
    }
  }
  else
  {
    this->Set(idx, tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::Set(
  int idx, const vtkDICOMTagPath& tagpath, const std::string& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem *item = this->FindItemOrInsert(idx, tagpath);
    if (item)
    {
      item->Set(tagpath.GetTail(), v);
    }
  }
  else
  {
    this->Set(idx, tagpath.GetHead(), v);
  }
}

//----------------------------------------------------------------------------
vtkDICOMValue vtkDICOMMetaData::MakeValueWithSpecificCharacterSet(
  vtkDICOMVR vr, const std::string& v)
{
  // note that there is similar code in vtkDICOMItem
  vtkDICOMCharacterSet cs; // defaults to ASCII
  const vtkDICOMValue& vcs = this->Get(DC::SpecificCharacterSet);
  if (vcs.IsValid())
  {
    cs = vtkDICOMCharacterSet(vcs.GetCharData(), vcs.GetVL());
  }
  return vtkDICOMValue(vr, cs, v);
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::CopyAttributes(vtkDICOMMetaData *o)
{
  // note: this method does not check for collisions between
  // private tag blocks, so at most one of the two data sets
  // can safely have private tags when this method is called.

  if (o != nullptr && o != this)
  {
    vtkDICOMDataElement **otable = o->Table;
    if (otable != nullptr)
    {
      const vtkDICOMDataElement *iter = o->Head.Next;
      const vtkDICOMDataElement *iterEnd = &o->Tail;
      while (iter != iterEnd)
      {
        // if this is a per-instance element, then make a copy of it
        const vtkDICOMValue *vptr = iter->Value.GetMultiplexData();
        if (vptr == nullptr)
        {
          vtkDICOMDataElement *e = this->FindDataElementOrInsert(iter->Tag);
          e->Tag = iter->Tag;
          e->Value = iter->Value;
        }
        else if (this->NumberOfInstances == o->NumberOfInstances)
        {
          vtkDICOMDataElement *e = this->FindDataElementOrInsert(iter->Tag);
          e->Tag = iter->Tag;
          vtkDICOMValue *nvptr = e->Value.AllocateMultiplexData(
            iter->Value.GetVR(), this->NumberOfInstances);
          for (int i = 0; i < this->NumberOfInstances; i++)
          {
            nvptr[i] = vptr[i];
          }
        }
        iter = iter->Next;
      }
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::ShallowCopy(vtkDataObject *source)
{
  vtkDICOMMetaData *o = vtkDICOMMetaData::SafeDownCast(source);
  if (o != this)
  {
    this->Initialize();
    if (o != nullptr)
    {
      this->NumberOfInstances = o->NumberOfInstances;
      this->CopyAttributes(o);
      this->SetFileIndexArray(o->FileIndexArray);
      this->SetFrameIndexArray(o->FrameIndexArray);
    }
    this->vtkDataObject::ShallowCopy(source);
  }
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::DeepCopy(vtkDataObject *source)
{
  vtkDICOMMetaData *o = vtkDICOMMetaData::SafeDownCast(source);
  if (o != this)
  {
    this->Initialize();
    if (o != nullptr)
    {
      this->NumberOfInstances = o->NumberOfInstances;
      this->CopyAttributes(o);
      if (o->FileIndexArray)
      {
        this->FileIndexArray = vtkIntArray::New();
        this->FileIndexArray->DeepCopy(o->FileIndexArray);
      }
      if (o->FrameIndexArray)
      {
        this->FrameIndexArray = vtkIntArray::New();
        this->FrameIndexArray->DeepCopy(o->FrameIndexArray);
      }
    }
    this->vtkDataObject::DeepCopy(source);
  }
}

//----------------------------------------------------------------------------
// should only be called from SetAttributeValue
vtkDICOMVR vtkDICOMMetaData::FindDictVR(int idx, vtkDICOMTag tag)
{
  vtkDICOMVR vr = vtkDICOMVR::UN;
  vtkDICOMDictEntry e = this->FindDictEntry(tag);

  if (e.IsValid())
  {
    vr = e.GetVR();
    // use the dictionary VR
    if (vr == vtkDICOMVR::XS)
    {
      vr = vtkDICOMVR::US;
      const vtkDICOMValue &v = this->Get(idx, DC::PixelRepresentation);
      if (v.IsValid())
      {
        unsigned short r = v.AsUnsignedShort();
        vr = (r == 0 ? vtkDICOMVR::US : vtkDICOMVR::SS);
      }
      else if (tag > DC::PixelRepresentation)
      {
        vtkErrorMacro("SetAttributeValue: could not look up vr for (" <<
                      tag << ") because PixelRepresentation is not set.");
      }
    }
    else if (vr == vtkDICOMVR::OX)
    {
      vr = vtkDICOMVR::OW;
      if (tag.GetGroup() == 0x5400)
      {
        const vtkDICOMValue &v = this->Get(idx, DC::WaveformBitsAllocated);
        if (v.IsValid())
        {
          unsigned short s = v.AsUnsignedShort();
          vr = (s > 8 ? vtkDICOMVR::OW : vtkDICOMVR::OB);
        }
        else
        {
          vtkErrorMacro("SetAttributeValue: could not look up vr for (" <<
                        tag << ") because WaveformBitsAllocated is not set.");
        }
      }
      else
      {
        const vtkDICOMValue &v = this->Get(idx, DC::BitsAllocated);
        if (v.IsValid())
        {
          unsigned short s = v.AsUnsignedShort();
          vr = (s > 8 ? vtkDICOMVR::OW : vtkDICOMVR::OB);
        }
        else
        {
          vtkErrorMacro("SetAttributeValue: could not look up vr for (" <<
                        tag << ") because BitsAllocated is not set.");
        }
      }
    }
  }

  return vr;
}

//----------------------------------------------------------------------------
vtkDICOMTag vtkDICOMMetaData::ResolvePrivateTag(
  int idx, vtkDICOMTag ptag, const std::string& creator)
{
  unsigned short g = ptag.GetGroup();
  if ((g & 0x0001) == 0)
  {
    return ptag;
  }

  // if not resolved, the result will be (ffff,ffff)
  vtkDICOMTag otag(0xFFFF, 0xFFFF);
  vtkDICOMTag ctag(g, 0x0010);
  vtkDICOMTag etag(g, 0x00FF);

  vtkDICOMDataElementIterator iter = this->Begin();
  vtkDICOMDataElementIterator iterEnd = this->End();

  vtkDICOMDataElement *e = this->FindDataElement(ctag);
  if (e != nullptr)
  {
    // found (gggg,0010) in the hash table
    iter = vtkDICOMDataElementIterator(e);
  }
  else
  {
    // skip through list of elements until group is found
    while (iter != iterEnd && iter->GetTag() < ctag)
    {
      ++iter;
    }
  }

  // look for private creator elements within the group
  idx = (idx < 0 ? 0 : idx);
  while (iter != iterEnd && iter->GetTag() <= etag)
  {
    ctag = iter->GetTag();
    const vtkDICOMValue *vp = (iter->IsPerInstance() ?
                               &iter->GetValue(idx) : &iter->GetValue());
    if (vp->AsString() == creator)
    {
      otag = vtkDICOMTag(
        g, (ctag.GetElement() << 8) | (ptag.GetElement() & 0x00FF));
      break;
    }
    ++iter;
  }

  return otag;
}

//----------------------------------------------------------------------------
vtkDICOMTag vtkDICOMMetaData::ResolvePrivateTag(
  vtkDICOMTag ptag, const std::string& creator)
{
  return this->ResolvePrivateTag(0, ptag, creator);
}

//----------------------------------------------------------------------------
vtkDICOMTag vtkDICOMMetaData::ResolvePrivateTagForWriting(
  int idx, vtkDICOMTag ptag, const std::string& creator)
{
  vtkDICOMTag otag = this->ResolvePrivateTag(idx, ptag, creator);
  if (otag == vtkDICOMTag(0xFFFF, 0xFFFF))
  {
    unsigned short g = ptag.GetGroup();
    unsigned short pb = (ptag.GetElement() >> 8);
    for (unsigned short cb = 0x0010; cb <= 0x00FF; cb++)
    {
      // this code rearranges order so that pb (preferred block) is first
      unsigned short e = cb;
      if (pb > cb)
      {
        if (cb == 0x0010)
        {
          e = pb;
        }
        else
        {
          --e;
        }
      }
      vtkDICOMTag ctag(g, e);
      vtkDICOMDataElement *d = this->FindDataElementOrInsert(ctag);
      if (!d->Value.IsValid())
      {
        // if an empty slot was found, use it for this creator
        d->Tag = ctag;
        d->Value = this->MakeValueWithSpecificCharacterSet(
          vtkDICOMVR::LO, creator);
        otag = vtkDICOMTag(g, (e << 8) | (ptag.GetElement() & 0x00FF));
        break;
      }
    }
  }

  return otag;
}

//----------------------------------------------------------------------------
vtkDICOMTag vtkDICOMMetaData::ResolvePrivateTagForWriting(
  vtkDICOMTag ptag, const std::string& creator)
{
  return this->ResolvePrivateTagForWriting(0, ptag, creator);
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMMetaData::FindDictEntry(vtkDICOMTag tag)
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // note that there is similar code in vtkDICOMItem
  const char *dict = nullptr;
  if ((group & 1) != 0 && element > 0x00ffu)
  {
    unsigned short creatorElement = (element >> 8);
    vtkDICOMTag creatorTag(group, creatorElement);
    dict = this->Get(creatorTag).GetCharData();
    vtkDICOMDictEntry entry = vtkDICOMDictionary::FindDictEntry(
      vtkDICOMTag(group, (element & 0x00ffu)), dict);
    if (entry.IsValid())
    {
      return entry;
    }
  }

  return vtkDICOMDictionary::FindDictEntry(tag, dict);
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "NumberOfInstances: "
     << this->NumberOfInstances << "\n";
  os << indent << "NumberOfDataElements: "
     << this->NumberOfDataElements << "\n";
  os << indent << "FileIndexArray: " << this->FileIndexArray << "\n";
  os << indent << "FrameIndexArray: " << this->FrameIndexArray << "\n";
}
