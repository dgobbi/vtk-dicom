#include "vtkDICOMItem.h"

//----------------------------------------------------------------------------
void vtkDICOMItem::CopyList(const List *o, List *t)
{
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
}

//----------------------------------------------------------------------------
void vtkDICOMItem::SetAttributeValue(
  vtkDICOMTag tag, const vtkDICOMValue& v)
{
  // Make a container if we don't have one yet
  if (this->L == 0)
    {
    this->L = new List;
    }
  // if we aren't the sole owner, copy before modifying
  else if (this->L->ReferenceCount > 1)
    {
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
  return vtkDICOMValue::GetInvalidValue();
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
