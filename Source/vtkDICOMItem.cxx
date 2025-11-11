/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMItem.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMTagPath.h"
#include "vtkDICOMMetaData.h"

#include <assert.h>

//----------------------------------------------------------------------------
// For use by methods that must return an invalid value
const vtkDICOMValue vtkDICOMItem::InvalidValue;

//----------------------------------------------------------------------------
vtkDICOMItem::vtkDICOMItem(vtkDICOMMetaData *meta)
{
  this->L = new List;
  this->L->Head.Next = &this->L->Tail;
  this->L->Tail.Prev = &this->L->Head;
  if (meta)
  {
    const vtkDICOMValue& vcs = meta->Get(DC::SpecificCharacterSet);
    if (vcs.IsValid())
    {
      this->L->CharacterSet =
        vtkDICOMCharacterSet(vcs.GetCharData(), vcs.GetVL());
    }
    const vtkDICOMValue &v = meta->Get(DC::PixelRepresentation);
    if (v.IsValid())
    {
      this->L->VRForXS = (v.AsUnsignedShort() == 0 ?
                          vtkDICOMVR::US : vtkDICOMVR::SS);
    }
  }
}

//----------------------------------------------------------------------------
vtkDICOMItem::vtkDICOMItem(
  vtkDICOMCharacterSet cs, vtkDICOMVR vrForXS,
  int delimited, unsigned int byteOffset)
{
  this->L = new List;
  this->L->Head.Next = &this->L->Tail;
  this->L->Tail.Prev = &this->L->Head;
  this->L->ByteOffset = byteOffset;
  this->L->Delimited = (delimited != 0);
  this->L->CharacterSet = cs;
  this->L->VRForXS = vrForXS;
}

//----------------------------------------------------------------------------
vtkDICOMDataElement *vtkDICOMItem::NewDataElement(vtkDICOMDataElement **iter)
{
  int n = this->L->NumberOfDataElements;

  // if no data elements yet, then allocate four
  if (this->L->DataElements == nullptr)
  {
    this->L->DataElements = new vtkDICOMDataElement[4];
  }
  // if n is a power of two, double allocated space
  else if (n >= 4 && (n & (n-1)) == 0)
  {
    // but first check if a free element exists
    do { --n; } while (n > 0 && this->L->DataElements[n].Next != nullptr);

    if (this->L->DataElements[n].Next != nullptr)
    {
      // make a new, larger list
      n = this->L->NumberOfDataElements;
      vtkDICOMDataElement *oldptr = this->L->DataElements;
      this->L->DataElements = new vtkDICOMDataElement[2*n];
      vtkDICOMItem::CopyDataElements(
        this->L->Head.Next, &this->L->Tail, this->L);
      if (iter)
      {
        // fix the address of the provided node, since it was re-alloced
        vtkDICOMDataElement *tptr = *iter;
        vtkDICOMDataElement *nptr = &this->L->Tail;
        do { tptr = tptr->Next; nptr = nptr->Prev; }
        while (tptr != &this->L->Tail);
        *iter = nptr;
      }
      delete [] oldptr;
    }
  }

  return &this->L->DataElements[n];
}

//----------------------------------------------------------------------------
void vtkDICOMItem::FreeList()
{
  delete [] this->L->DataElements;
  delete this->L;
  this->L = nullptr;
}

//----------------------------------------------------------------------------
void vtkDICOMItem::CopyList(const List *o, List *t)
{
  t->NumberOfDataElements = o->NumberOfDataElements;
  t->DataElements = nullptr;
  t->ByteOffset = o->ByteOffset;
  t->Delimited = o->Delimited;
  t->CharacterSet = o->CharacterSet;
  t->VRForXS = o->VRForXS;
  t->Head.Next = &t->Tail;
  t->Tail.Prev = &t->Head;

  int n = o->NumberOfDataElements;
  if (n > 0)
  {
    // round up to power of two
    int m = n - 1;
    m |= m >> 1;
    m |= m >> 2;
    m |= m >> 4;
    m |= m >> 8;
    m |= m >> 16;
    m += 1;

    // allocate a minimum of 4 elements
    if (m < 4) { m = 4; }
    t->DataElements = new vtkDICOMDataElement[m];
    vtkDICOMItem::CopyDataElements(o->Head.Next, &o->Tail, t);
  }
}

//----------------------------------------------------------------------------
void vtkDICOMItem::CopyDataElements(
  const vtkDICOMDataElement *begin, const vtkDICOMDataElement *end, List *t)
{
  vtkDICOMDataElement *e = t->DataElements;
  t->Head.Next = e;

  const vtkDICOMDataElement *ptr = begin;
  while (ptr != end)
  {
    e->Tag = ptr->Tag;
    e->Value = ptr->Value;
    e->Next = e + 1;
    e->Prev = e - 1;
    ptr = ptr->Next;
    e++;
  }

  t->Tail.Prev = e - 1;
  t->Head.Next->Prev = &t->Head;
  t->Tail.Prev->Next = &t->Tail;
}

//----------------------------------------------------------------------------
vtkDICOMDataElement *vtkDICOMItem::FindDataElementOrInsert(vtkDICOMTag tag)
{
  // make a container if we don't have one yet
  if (this->L == nullptr)
  {
    this->L = new List;
    this->L->Head.Next = &this->L->Tail;
    this->L->Tail.Prev = &this->L->Head;
  }
  // if we aren't the sole owner, copy before modifying
  else if (this->L->ReferenceCount != 1)
  {
    List *t = new List;
    vtkDICOMItem::CopyList(this->L, t);
    this->Clear();
    this->L = t;
  }

  // find the insert location in the linked list
  vtkDICOMDataElement *tptr = &this->L->Tail;
  do
  {
    tptr = tptr->Prev;
  }
  while (tag < tptr->GetTag());

  if (tag != tptr->GetTag())
  {
    // create a new data element
    vtkDICOMDataElement *e = this->NewDataElement(&tptr);
    e->Tag = tag;
    e->Prev = tptr;
    e->Next = tptr->Next;
    e->Prev->Next = e;
    e->Next->Prev = e;

    tptr = e;
    this->L->NumberOfDataElements++;
  }

  return tptr;
}

//----------------------------------------------------------------------------
vtkDICOMItem *vtkDICOMItem::FindItemOrInsert(
  const vtkDICOMTagPath& tagpath, vtkDICOMTag *tagptr)
{
  vtkDICOMItem *item = nullptr;

  if (tagpath.HasTail())
  {
    vtkDICOMTag tag = tagpath.GetHead();
    vtkDICOMDataElement *tptr = this->FindDataElementOrInsert(tag);
    vtkDICOMVR vr = tptr->Value.GetVR();
    if (!vr.IsValid())
    {
      vr = this->FindDictVR(tag);
      if (vr == vtkDICOMVR::UN)
      {
        // let it through if it isn't in the dictionary
        vr = vtkDICOMVR::SQ;
      }
    }
    // add the item to the sequence, or create a sequence
    if (vr == vtkDICOMVR::SQ)
    {
      size_t i = tagpath.GetIndex();
      size_t n = i+1;
      size_t m = 0;
      const vtkDICOMItem *oldItems = tptr->Value.GetSequenceData();
      if (oldItems != nullptr)
      {
        m = tptr->Value.GetNumberOfValues();
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
      vtkDICOMCharacterSet cs = this->L->CharacterSet;
      vtkDICOMVR vrForXS = this->L->VRForXS;
      if (n > m)
      {
        const vtkDICOMValue& vcs =
          this->Get(DC::SpecificCharacterSet);
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
        // Inherit properties that originally came from parent data set
        items[j] = vtkDICOMItem(cs, vrForXS);
      }
      tptr->Value = seq;
      item = items[i].FindItemOrInsert(tagpath.GetTail(), tagptr);
    }
    else if (!tptr->Value.IsValid())
    {
      // we just inserted a non-SQ value, remove it
      tptr->Prev->Next = tptr->Next;
      tptr->Next->Prev = tptr->Prev;
      tptr->Next = nullptr;
      tptr->Prev = nullptr;
      this->L->NumberOfDataElements--;
    }
  }
  else
  {
    item = this;
    *tagptr = tagpath.GetHead();
  }

  return item;
}

//----------------------------------------------------------------------------
void vtkDICOMItem::Set(vtkDICOMTag tag, const vtkDICOMValue& v)
{
  vtkDICOMDataElement *tptr = this->FindDataElementOrInsert(tag);

  tptr->Value = v;

  if (!v.IsValid())
  {
    // setting a value to the invalid value causes deletion
    tptr->Prev->Next = tptr->Next;
    tptr->Next->Prev = tptr->Prev;
    tptr->Next = nullptr;
    tptr->Prev = nullptr;
    this->L->NumberOfDataElements--;
  }
}

//----------------------------------------------------------------------------
void vtkDICOMItem::Set(const vtkDICOMTagPath& tagpath, const vtkDICOMValue& v)
{
  vtkDICOMTag tag;
  vtkDICOMItem *item = this->FindItemOrInsert(tagpath, &tag);
  // if item is NULL, the path was invalid
  if (item)
  {
    item->Set(tag, v);
  }
}

//----------------------------------------------------------------------------
void vtkDICOMItem::Set(const vtkDICOMTagPath& tagpath, double v)
{
  vtkDICOMTag tag;
  vtkDICOMItem *item = this->FindItemOrInsert(tagpath, &tag);
  // if item is NULL, the path was invalid
  if (item)
  {
    vtkDICOMVR vr = item->FindDictVR(tag);
    assert(vr != vtkDICOMVR::UN);
    if (vr != vtkDICOMVR::UN)
    {
      item->Set(tag, vtkDICOMValue(vr, v));
    }
  }
}

void vtkDICOMItem::Set(const vtkDICOMTagPath& tagpath, const std::string& v)
{
  vtkDICOMTag tag;
  vtkDICOMItem *item = this->FindItemOrInsert(tagpath, &tag);
  // if item is NULL, the path was invalid
  if (item)
  {
    vtkDICOMVR vr = item->FindDictVR(tag);
    assert(vr != vtkDICOMVR::UN);
    // note that there is similar code in vtkDICOMMetaData
    if (vr.HasSpecificCharacterSet() && item->L != nullptr)
    {
      vtkDICOMCharacterSet cs = item->L->CharacterSet;
      const vtkDICOMValue& vcs = item->Get(DC::SpecificCharacterSet);
      if (vcs.IsValid())
      {
        cs = vtkDICOMCharacterSet(vcs.GetCharData(), vcs.GetVL());
      }
      item->Set(tag, vtkDICOMValue(vr, cs, v));
    }
    else if (vr != vtkDICOMVR::UN)
    {
      item->Set(tag, vtkDICOMValue(vr, v));
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMItem::Set(vtkDICOMTag tag, double v)
{
  this->Set(vtkDICOMTagPath(tag), v);
}

void vtkDICOMItem::Set(vtkDICOMTag tag, const std::string& v)
{
  this->Set(vtkDICOMTagPath(tag), v);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMItem::Get(vtkDICOMTag tag) const
{
  if (this->L)
  {
    vtkDICOMDataElement *e = this->L->Head.Next;
    vtkDICOMDataElement *tail = &this->L->Tail;
    while (e != tail)
    {
      if (e->Tag == tag)
      {
        return e->Value;
      }
      e = e->Next;
    }
  }
  return vtkDICOMItem::InvalidValue;
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMItem::Get(const vtkDICOMTagPath &tagpath) const
{
  const vtkDICOMValue &v = this->Get(tagpath.GetHead());
  if (!tagpath.HasTail())
  {
    return v;
  }
  if (v.IsValid())
  {
    size_t i = tagpath.GetIndex();
    size_t n = v.GetNumberOfValues();
    const vtkDICOMItem *items = v.GetSequenceData();
    if (items != nullptr && i < n)
    {
      return items[i].Get(tagpath.GetTail());
    }
  }
  return vtkDICOMItem::InvalidValue;
}

//----------------------------------------------------------------------------
vtkDICOMVR vtkDICOMItem::FindDictVR(vtkDICOMTag tag) const
{
  vtkDICOMVR vr = vtkDICOMVR::UN;
  vtkDICOMDictEntry e = this->FindDictEntry(tag);

  if (e.IsValid())
  {
    vr = e.GetVR();
    // use the dictionary VR
    if (vr == vtkDICOMVR::XS)
    {
      const vtkDICOMValue &v = this->Get(DC::PixelRepresentation);
      if (v.IsValid())
      {
        unsigned short r = v.AsUnsignedShort();
        vr = (r == 0 ? vtkDICOMVR::US : vtkDICOMVR::SS);
      }
      else if (this->L)
      {
        vr = this->L->VRForXS;
      }
      else
      {
        vr = vtkDICOMVR::US;
      }
    }
    else if (vr == vtkDICOMVR::OX)
    {
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

  return vr;
}

//----------------------------------------------------------------------------
vtkDICOMTag vtkDICOMItem::ResolvePrivateTag(
  vtkDICOMTag ptag, const std::string& creator) const
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

  // search for the correct group
  while (iter != iterEnd && iter->GetTag() < ctag)
  {
    ++iter;
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
vtkDICOMTag vtkDICOMItem::ResolvePrivateTagForWriting(
  vtkDICOMTag ptag, const std::string& creator)
{
  vtkDICOMTag otag = this->ResolvePrivateTag(ptag, creator);
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
        // creator elements are LO, which uses SpecificCharacterSet
        vtkDICOMCharacterSet cs = this->L->CharacterSet;
        const vtkDICOMValue& vcs = this->Get(DC::SpecificCharacterSet);
        if (vcs.IsValid())
        {
          cs = vtkDICOMCharacterSet(vcs.GetCharData(), vcs.GetVL());
        }
        // if an empty slot was found, use it for this creator
        d->Tag = ctag;
        d->Value = vtkDICOMValue(vtkDICOMVR::LO, cs, creator);
        otag = vtkDICOMTag(g, (e << 8) | (ptag.GetElement() & 0x00FF));
        break;
      }
    }
  }

  return otag;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMItem::FindDictEntry(vtkDICOMTag tag) const
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // note that there is similar code in vtkDICOMMetaData
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
bool vtkDICOMItem::operator==(const vtkDICOMItem& ob) const
{
  List *t = this->L;
  List *o = ob.L;

  bool r = true;
  if (t != o)
  {
    r = false;
    if (t != nullptr && o != nullptr &&
        t->NumberOfDataElements == o->NumberOfDataElements)
    {
      r = true;
      int n = t->NumberOfDataElements;
      if (n > 0)
      {
        vtkDICOMDataElement *a = t->Head.Next;
        vtkDICOMDataElement *b = o->Head.Next;
        do
        {
          r &= (*a == *b);
          a = a->Next;
          b = b->Next;
        }
        while (r && --n);
      }
    }
  }
  return r;
}
