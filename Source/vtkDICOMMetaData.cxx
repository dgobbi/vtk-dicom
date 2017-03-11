/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
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

#include <vtkObjectFactory.h>
#include <vtkMatrix4x4.h>
#include <vtkAbstractArray.h>
#include <vtkIntArray.h>

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
  this->Table = NULL;
  this->Head.Prev = NULL;
  this->Head.Next = &this->Tail;
  this->Tail.Prev = &this->Head;
  this->Tail.Next = NULL;
  this->FileIndexArray = NULL;
  this->FrameIndexArray = NULL;
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
  this->Table = NULL;
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
    this->FileIndexArray = 0;
  }
  if (this->FrameIndexArray)
  {
    this->FrameIndexArray->Delete();
    this->FrameIndexArray = 0;
  }
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::SetNumberOfInstances(int n)
{
  if (this->Table != NULL)
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
void vtkDICOMMetaData::RemoveAttribute(vtkDICOMTag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMDataElement **htable = this->Table;
  vtkDICOMDataElement *hptr;

  if (htable && (hptr = htable[i]) != NULL)
  {
    while (hptr->Next != 0)
    {
      if (hptr->Tag == tag)
      {
        // remove from the linked list
        hptr->Next->Prev = hptr->Prev;
        hptr->Prev->Next = hptr->Next;
        // remove from the hash table
        hptr[0] = hptr[1];
        while (hptr->Next != 0)
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

  if (htable && (hptr = htable[i]) != NULL)
  {
    while (hptr->Next != 0)
    {
      if (hptr->Tag == tag)
      {
        return hptr;
      }
      hptr++;
    }
  }

  return NULL;
}

//----------------------------------------------------------------------------
bool vtkDICOMMetaData::HasAttribute(vtkDICOMTag tag)
{
  return (this->FindDataElement(tag) != 0);
}

//----------------------------------------------------------------------------
const vtkDICOMValue *vtkDICOMMetaData::FindAttributeValue(
  int idx, vtkDICOMTag tag)
{
  vtkDICOMDataElement *a = this->FindDataElement(tag);
  const vtkDICOMValue *vptr = 0;

  if (a != 0)
  {
    vptr = &a->Value;
    // is this a sequence of values?
    const vtkDICOMValue *sptr = vptr->GetMultiplexData();
    if (sptr)
    {
      size_t n = vptr->GetNumberOfValues();
      vptr = 0;
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
  if (vptr != 0 && tagpath.HasTail())
  {
    size_t i = tagpath.GetIndex();
    size_t n = vptr->GetNumberOfValues();
    const vtkDICOMItem *items = vptr->GetSequenceData();
    vptr = 0;
    if (items != 0 && i < n)
    {
      vptr = &items[i].GetAttributeValue(tagpath.GetTail());
      if (!vptr->IsValid())
      {
        vptr = 0;
      }
    }
  }
  return vptr;
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(vtkDICOMTag tag)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(0, tag);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(
  int idx, vtkDICOMTag tag)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(idx, tag);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(
  const vtkDICOMTagPath &tagpath)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(0, tagpath);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(
  int idx, const vtkDICOMTagPath &tagpath)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(idx, tagpath);
  return (vptr ? *vptr : this->Tail.Value);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(
  int idx, int frame, const vtkDICOMTagPath &tagpath)
{
  // if either of these is present in an enhanced DICOM file, then they
  // will be searched before the root is searched
  const DC::EnumType fgs[2] = {
    DC::PerFrameFunctionalGroupsSequence,
    DC::SharedFunctionalGroupsSequence
  };

  // for temporarily saving location to private value (see below)
  const vtkDICOMValue *privateValue = 0;

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
      const vtkDICOMValue &v = items[f].GetAttributeValue(tagpath);
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
            const vtkDICOMValue &w = item->GetAttributeValue(tagpath);
            if (w.IsValid())
            {
              if ((iter->GetTag().GetGroup() & 1) == 0)
              {
                return w;
              }
              else if (privateValue == 0)
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
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(
  int idx, int frame, vtkDICOMTag tag)
{
  return this->GetAttributeValue(idx, frame, vtkDICOMTagPath(tag));
}

//----------------------------------------------------------------------------
int vtkDICOMMetaData::GetFileIndex(int sliceIdx)
{
  if (this->FileIndexArray == 0 || sliceIdx < 0 ||
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
  if (this->FileIndexArray == 0 || sliceIdx < 0 ||
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
  if (this->FrameIndexArray == 0 || sliceIdx < 0 ||
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
  if (this->FrameIndexArray == 0 || sliceIdx < 0 ||
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

  if (htable == NULL)
  {
    // allocate the hash table
    m = METADATA_HASH_SIZE;
    htable = new vtkDICOMDataElement *[METADATA_HASH_SIZE];
    this->Table = htable;
    do { *htable++ = NULL; } while (--m);
    htable = this->Table;
  }

  hptr = htable[i];

  if (hptr == NULL)
  {
    hptr = new vtkDICOMDataElement[4];
    htable[i] = hptr;
  }
  else if (hptr->Next != 0)
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
    while (hptr->Next != 0);

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
  if (loc == 0)
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
      this->RemoveAttribute(tag);
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
  if (sptr != 0)
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
    if (oldItems != 0)
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
      const vtkDICOMValue& vcs =
        this->GetAttributeValue(DC::SpecificCharacterSet);
      if (vcs.IsValid())
      {
        cs = vtkDICOMCharacterSet(vcs.GetCharData(), vcs.GetVL());
      }
      const vtkDICOMValue &v = this->GetAttributeValue(
        DC::PixelRepresentation);
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
  vtkDICOMItem *itemptr = 0;
  this->FindItemsOrInsert(idx, true, tagpath, &itemptr);
  return itemptr;
}

//----------------------------------------------------------------------------
// Insert an attribute into the hash table
void vtkDICOMMetaData::SetAttributeValue(
  vtkDICOMTag tag, const vtkDICOMValue& v)
{
  if (v.IsValid())
  {
    vtkDICOMDataElement *loc = this->FindDataElementOrInsert(tag);
    if (loc == 0)
    {
      vtkErrorMacro("SetAttributeValue: tag group number must not be zero.");
      return;
    }
    loc->Tag = tag;
    loc->Value = v;
  }
  else
  {
    this->RemoveAttribute(tag);
  }
}

void vtkDICOMMetaData::SetAttributeValue(vtkDICOMTag tag, double v)
{
  vtkDICOMVR vr = this->FindDictVR(0, tag);
  if (vr != vtkDICOMVR::UN)
  {
    this->SetAttributeValue(tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

void vtkDICOMMetaData::SetAttributeValue(vtkDICOMTag tag, const std::string& v)
{
  vtkDICOMVR vr = this->FindDictVR(0, tag);
  if (vr.HasSpecificCharacterSet() && tag > DC::SpecificCharacterSet)
  {
    this->SetAttributeValue(tag,
      this->MakeValueWithSpecificCharacterSet(vr, v));
  }
  else if (vr != vtkDICOMVR::UN)
  {
    this->SetAttributeValue(tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

//----------------------------------------------------------------------------
// Insert an attribute for a particular image
void vtkDICOMMetaData::SetAttributeValue(
  int idx, vtkDICOMTag tag, const vtkDICOMValue& v)
{
  vtkDICOMDataElement *loc = this->FindDataElementOrInsert(tag);
  if (loc == 0)
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
    // if invalid value was added, make sure valid values remain
    if (!v.IsValid())
    {
      bool valid = false;
      for (int i = 0; i < this->NumberOfInstances; i++)
      {
        valid |= sptr[i].IsValid();
      }
      if (!valid)
      {
        this->RemoveAttribute(tag);
      }
    }
  }
  else if (v != *vptr)
  {
    // differs from other instances, must turn value into a list,
    // so create a value that is actually a list of values
    int n = this->NumberOfInstances;
    vtkDICOMValue l;
    sptr = l.AllocateMultiplexData(vptr->GetVR(), n);
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
  else if (!vptr->IsValid())
  {
    this->RemoveAttribute(tag);
  }
}

void vtkDICOMMetaData::SetAttributeValue(
  int idx, vtkDICOMTag tag, double v)
{
  vtkDICOMVR vr = this->FindDictVR(idx, tag);
  if (vr != vtkDICOMVR::UN)
  {
    this->SetAttributeValue(idx, tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

void vtkDICOMMetaData::SetAttributeValue(
  int idx, vtkDICOMTag tag, const std::string& v)
{
  vtkDICOMVR vr = this->FindDictVR(idx, tag);
  if (vr.HasSpecificCharacterSet() && tag > DC::SpecificCharacterSet)
  {
    this->SetAttributeValue(idx, tag,
      this->MakeValueWithSpecificCharacterSet(vr, v));
  }
  else if (vr != vtkDICOMVR::UN)
  {
    this->SetAttributeValue(idx, tag, vtkDICOMValue(vr, v));
  }
  else
  {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
  }
}

//----------------------------------------------------------------------------
// Insert an attribute at a particular path
void vtkDICOMMetaData::SetAttributeValue(
  const vtkDICOMTagPath& tagpath, const vtkDICOMValue& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem **items = new vtkDICOMItem *[this->NumberOfInstances];
    int n = this->FindItemsOrInsert(0, false, tagpath, items);
    for (int i = 0; i < n; i++)
    {
      items[i]->SetAttributeValue(tagpath.GetTail(), v);
    }
    delete [] items;
  }
  else
  {
    this->SetAttributeValue(tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::SetAttributeValue(
  const vtkDICOMTagPath& tagpath, double v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem **items = new vtkDICOMItem *[this->NumberOfInstances];
    int n = this->FindItemsOrInsert(0, false, tagpath, items);
    for (int i = 0; i < n; i++)
    {
      items[i]->SetAttributeValue(tagpath.GetTail(), v);
    }
    delete [] items;
  }
  else
  {
    this->SetAttributeValue(tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::SetAttributeValue(
  const vtkDICOMTagPath& tagpath, const std::string& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem **items = new vtkDICOMItem *[this->NumberOfInstances];
    int n = this->FindItemsOrInsert(0, false, tagpath, items);
    for (int i = 0; i < n; i++)
    {
      items[i]->SetAttributeValue(tagpath.GetTail(), v);
    }
    delete [] items;
  }
  else
  {
    this->SetAttributeValue(tagpath.GetHead(), v);
  }
}

//----------------------------------------------------------------------------
// Insert an attribute for a particular image
void vtkDICOMMetaData::SetAttributeValue(
  int idx, const vtkDICOMTagPath& tagpath, const vtkDICOMValue& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem *item = this->FindItemOrInsert(idx, tagpath);
    if (item)
    {
      item->SetAttributeValue(tagpath.GetTail(), v);
    }
  }
  else
  {
    this->SetAttributeValue(idx, tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::SetAttributeValue(
  int idx, const vtkDICOMTagPath& tagpath, double v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem *item = this->FindItemOrInsert(idx, tagpath);
    if (item)
    {
      item->SetAttributeValue(tagpath.GetTail(), v);
    }
  }
  else
  {
    this->SetAttributeValue(idx, tagpath.GetHead(), v);
  }
}

void vtkDICOMMetaData::SetAttributeValue(
  int idx, const vtkDICOMTagPath& tagpath, const std::string& v)
{
  if (tagpath.HasTail())
  {
    vtkDICOMItem *item = this->FindItemOrInsert(idx, tagpath);
    if (item)
    {
      item->SetAttributeValue(tagpath.GetTail(), v);
    }
  }
  else
  {
    this->SetAttributeValue(idx, tagpath.GetHead(), v);
  }
}

//----------------------------------------------------------------------------
vtkDICOMValue vtkDICOMMetaData::MakeValueWithSpecificCharacterSet(
  vtkDICOMVR vr, const std::string& v)
{
  // note that there is similar code in vtkDICOMItem
  vtkDICOMCharacterSet cs; // defaults to ASCII
  const vtkDICOMValue& vcs =
    this->GetAttributeValue(DC::SpecificCharacterSet);
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

  if (o != 0 && o != this)
  {
    vtkDICOMDataElement **otable = o->Table;
    if (otable != 0)
    {
      const vtkDICOMDataElement *iter = o->Head.Next;
      const vtkDICOMDataElement *iterEnd = &o->Tail;
      while (iter != iterEnd)
      {
        // if this is a per-instance element, then make a copy of it
        const vtkDICOMValue *vptr = iter->Value.GetMultiplexData();
        if (vptr == 0)
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
    if (o != 0)
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
    if (o != 0)
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
      const vtkDICOMValue &v =
        this->GetAttributeValue(idx, DC::PixelRepresentation);
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
        const vtkDICOMValue &v =
          this->GetAttributeValue(idx, DC::WaveformBitsAllocated);
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
        const vtkDICOMValue &v =
          this->GetAttributeValue(idx, DC::BitsAllocated);
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
  vtkDICOMTag ptag, const std::string& creator)
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
  if (e != 0)
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
  while (iter != iterEnd && iter->GetTag() <= etag)
  {
    ctag = iter->GetTag();
    if (iter->GetValue().AsString() == creator)
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
vtkDICOMTag vtkDICOMMetaData::ResolvePrivateTagForWriting(
  vtkDICOMTag ptag, const std::string& creator)
{
  vtkDICOMTag otag = this->ResolvePrivateTag(ptag, creator);
  if (otag == vtkDICOMTag(0xFFFF, 0xFFFF))
  {
    unsigned short g = ptag.GetGroup();
    for (unsigned short e = 0x0010; e <= 0x00FF; e++)
    {
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
vtkDICOMDictEntry vtkDICOMMetaData::FindDictEntry(vtkDICOMTag tag)
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // note that there is similar code in vtkDICOMItem
  const char *dict = 0;
  if ((group & 1) != 0 && element > 0x00ffu)
  {
    unsigned short creatorElement = (element >> 8);
    element &= 0x00ffu;
    tag = vtkDICOMTag(group, element);
    vtkDICOMTag creatorTag(group, creatorElement);
    dict = this->GetAttributeValue(creatorTag).GetCharData();
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
