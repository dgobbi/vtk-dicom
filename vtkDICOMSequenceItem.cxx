#include "vtkDICOMSequenceItem.h"

//----------------------------------------------------------------------------
void vtkDICOMSequenceItem::CopyList(const List *o, List *t)
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
void vtkDICOMSequenceItem::AddDataElement(
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

  // add element to the list
  vtkDICOMDataElement *e = new vtkDICOMDataElement;
  e->Tag = tag;
  e->Value = v;
  e->Next = &this->L->Tail;
  e->Prev = e->Next->Prev;
  e->Next->Prev = e;
  e->Prev->Next = e;

  this->L->NumberOfDataElements++;
}

//----------------------------------------------------------------------------
bool vtkDICOMSequenceItem::operator==(const vtkDICOMSequenceItem& ob) const
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

//----------------------------------------------------------------------------
vtkDICOMSequenceItem& vtkDICOMSequenceItem::operator=(
  const vtkDICOMSequenceItem& o)
{
  // assignment with reference counting
  if (this->L != o.L)
    {
    if (this->L)
      {
      if (--this->L->ReferenceCount == 0)
        {
        delete this->L;
        }
      }
    this->L = o.L;
    if (this->L)
      {
      this->L->ReferenceCount++;
      }
    }
  return *this;
}
