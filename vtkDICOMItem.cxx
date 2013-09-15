/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

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
vtkDICOMItem::vtkDICOMItem(int delimited)
{
  this->L = new List;
  this->L->NumberOfDataElements = 0;
  this->L->Delimited = (delimited != 0);
  this->L->Head.Prev = 0;
  this->L->Head.Next = &this->L->Tail;
  this->L->Tail.Prev = &this->L->Head;
  this->L->Tail.Next = 0;
}

//----------------------------------------------------------------------------
void vtkDICOMItem::FreeList()
{
  vtkDICOMDataElement *ptr = this->L->Head.Next;
  vtkDICOMDataElement *tail = &this->L->Tail;
  while (ptr != tail)
    {
    ptr = ptr->Next;
    delete ptr->Prev;
    }
  delete this->L;
  this->L = 0;
}

//----------------------------------------------------------------------------
void vtkDICOMItem::CopyList(const List *o, List *t)
{
  t->Head.Prev = 0;
  t->Head.Next = &t->Tail;
  t->Tail.Prev = &t->Head;
  t->Tail.Next = 0;

  vtkDICOMDataElement *ptr = o->Head.Next;
  while (ptr != &o->Tail)
    {
    vtkDICOMDataElement *e = new vtkDICOMDataElement;
    e->Tag = ptr->Tag;
    e->Value = ptr->Value;
    e->Next = &t->Tail;
    e->Prev = e->Next->Prev;
    e->Next->Prev = e;
    e->Prev->Next = e;
    ptr = ptr->Next;
    }

  t->NumberOfDataElements = o->NumberOfDataElements;
  t->Delimited = o->Delimited;
}

//----------------------------------------------------------------------------
void vtkDICOMItem::SetAttributeValue(
  vtkDICOMTag tag, const vtkDICOMValue& v)
{
  // Make a container if we don't have one yet
  if (this->L == 0)
    {
    this->L = new List;
    this->L->NumberOfDataElements = 0;
    this->L->Delimited = 0;
    this->L->Head.Prev = 0;
    this->L->Head.Next = &this->L->Tail;
    this->L->Tail.Prev = &this->L->Head;
    this->L->Tail.Next = 0;
    }
  // if we aren't the sole owner, copy before modifying
  else if (this->L->ReferenceCount != 1)
    {
    assert(this->L->ReferenceCount == 1);
    List *t = new List;
    this->CopyList(this->L, t);
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
    }
  else
    {
    // create a new data element
    vtkDICOMDataElement *e = new vtkDICOMDataElement;
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
  if (group & 1)
    {
    unsigned short creatorElement = element;
    if (element > 0x00ffu)
      {
      creatorElement = (element >> 8);
      element = (0x1000u | (element & 0x00ffu));
      }
    else
      {
      element = 0x0010u;
      }
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
