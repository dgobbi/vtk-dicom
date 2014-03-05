/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMItem.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMTagPath.h"

#include <assert.h>

//----------------------------------------------------------------------------
// For use by methods that must return an invalid value
const vtkDICOMValue vtkDICOMItem::InvalidValue;

//----------------------------------------------------------------------------
vtkDICOMItem::vtkDICOMItem(int delimited, unsigned int byteOffset)
{
  this->L = new List;
  this->L->Head.Next = &this->L->Tail;
  this->L->Tail.Prev = &this->L->Head;
  this->L->ByteOffset = byteOffset;
  this->L->Delimited = (delimited != 0);
}

//----------------------------------------------------------------------------
vtkDICOMDataElement *vtkDICOMItem::NewDataElement(vtkDICOMDataElement **iter)
{
  int n = this->L->NumberOfDataElements;

  // if no data elements yet, then allocate four
  if (this->L->DataElements == 0)
    {
    this->L->DataElements = new vtkDICOMDataElement[4];
    }
  // if n is a power of two, double allocated space
  else if (n >= 4 && (n & (n-1)) == 0)
    {
    // but first check if a free element exists
    do { --n; } while (n > 0 && this->L->DataElements[n].Next != 0);

    if (this->L->DataElements[n].Next != 0)
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
  this->L = 0;
}

//----------------------------------------------------------------------------
void vtkDICOMItem::CopyList(const List *o, List *t)
{
  t->ByteOffset = o->ByteOffset;
  t->Delimited = o->Delimited;

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
void vtkDICOMItem::SetAttributeValue(
  vtkDICOMTag tag, const vtkDICOMValue& v)
{
  // Make a container if we don't have one yet
  if (this->L == 0)
    {
    this->L = new List;
    this->L->Head.Next = &this->L->Tail;
    this->L->Tail.Prev = &this->L->Head;
    }
  // if we aren't the sole owner, copy before modifying
  else if (this->L->ReferenceCount != 1)
    {
    // assert, because this should never happen
    assert(this->L->ReferenceCount == 1);
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

  if (tag == tptr->GetTag())
    {
    tptr->Value = v;
    if (!v.IsValid())
      {
      // setting a value to the invalid value causes deletion
      tptr->Prev->Next = tptr->Next;
      tptr->Next->Prev = tptr->Prev;
      tptr->Next = 0;
      tptr->Prev = 0;
      this->L->NumberOfDataElements--;
      }
    }
  else if (v.IsValid())
    {
    // create a new data element
    vtkDICOMDataElement *e = this->NewDataElement(&tptr);
    e->Tag = tag;
    e->Value = v;

    e->Prev = tptr;
    e->Next = tptr->Next;
    e->Prev->Next = e;
    e->Next->Prev = e;

    this->L->NumberOfDataElements++;
    }
}

//----------------------------------------------------------------------------
template<class T>
void vtkDICOMItem::SetAttributeValueT(vtkDICOMTag tag, T v)
{
  vtkDICOMVR vr = this->FindDictVR(tag);
  assert(vr != vtkDICOMVR::UN);
  if (vr != vtkDICOMVR::UN)
    {
    this->SetAttributeValue(tag, vtkDICOMValue(vr, v));
    }
}

void vtkDICOMItem::SetAttributeValue(vtkDICOMTag tag, double v)
{
  this->SetAttributeValueT(tag, v);
}

void vtkDICOMItem::SetAttributeValue(vtkDICOMTag tag, const std::string& v)
{
  this->SetAttributeValueT(tag, v);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMItem::GetAttributeValue(
  vtkDICOMTag tag) const
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
const vtkDICOMValue &vtkDICOMItem::GetAttributeValue(
  const vtkDICOMTagPath &tagpath) const
{
  const vtkDICOMValue &v = this->GetAttributeValue(tagpath.GetHead());
  if (!tagpath.HasTail())
    {
    return v;
    }
  if (v.IsValid())
    {
    unsigned int i = tagpath.GetIndex();
    unsigned int n = v.GetNumberOfValues();
    const vtkDICOMItem *items = v.GetSequenceData();
    if (items != 0 && i < n)
      {
      return items[i].GetAttributeValue(tagpath.GetTail());
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
    // make sure the dict knows the concrete vr
    if (vr == vtkDICOMVR::XS || vr == vtkDICOMVR::OX)
      {
      vr = vtkDICOMVR::UN;
      }
    }

  return vr;
}

//----------------------------------------------------------------------------
vtkDICOMDictEntry vtkDICOMItem::FindDictEntry(vtkDICOMTag tag) const
{
  unsigned short group = tag.GetGroup();
  unsigned short element = tag.GetElement();

  // note that there is similar code in vtkDICOMMetaData
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
bool vtkDICOMItem::operator==(const vtkDICOMItem& ob) const
{
  List *t = this->L;
  List *o = ob.L;

  bool r = true;
  if (t != o)
    {
    r = false;
    if (t != 0 && o != 0 &&
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
