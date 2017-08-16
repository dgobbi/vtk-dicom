/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMTagPath.h"

//----------------------------------------------------------------------------
ostream& operator<<(ostream& o, const vtkDICOMTagPath& a)
{
  o << "[";
  o << a.GetHead();
  if (a.HasTail())
  {
    unsigned int i = a.GetIndex();
    vtkDICOMTagPath b = a.GetTail();
    for (;;)
    {
      o << ",";
      o << i;
      o << ",";
      o << b.GetHead();
      if (!b.HasTail())
      {
        break;
      }
      i = b.GetIndex();
      b = b.GetTail();
    }
  }
  o << "]";

  return o;
}

//----------------------------------------------------------------------------
vtkDICOMTagPath::vtkDICOMTagPath(
  const vtkDICOMTagPath& pth, unsigned int i, vtkDICOMTag tag)
  : Head(pth.Head), Index(pth.Index), Tail(pth.Tail), More(pth.More)
{
  if (pth.GetHead() == vtkDICOMTag())
  {
    this->Head = tag;
    this->List = 0;
  }
  else if (!pth.HasTail())
  {
    this->Index = i;
    this->Tail = tag;
    this->List = 0;
  }
  else if (pth.More == 0)
  {
    this->More = (tag != vtkDICOMTag());
    this->Last.Index = i;
    this->Last.Tail = tag;
  }
  else if (tag == vtkDICOMTag())
  {
    if (pth.More == 1)
    {
      this->Last = pth.Last;
    }
    else
    {
      this->List = vtkDICOMTagPath::CopyList(pth.List, pth.More);
    }
  }
  else if (pth.More == 1)
  {
    Pair *l = new Pair[2];
    l[0] = pth.Last;
    l[1].Index = i;
    l[1].Tail = tag;
    this->More = 2;
    this->List = l;
  }
  else
  {
    unsigned int n = pth.More;
    Pair *l = new Pair[n + 1];
    for (unsigned int j = 0; j < n; j++)
    {
      l[j] = pth.List[j];
    }
    l[n].Index = i;
    l[n].Tail = tag;
    this->More = n + 1;
    this->List = l;
  }
}

//----------------------------------------------------------------------------
vtkDICOMTagPath::Pair *vtkDICOMTagPath::CopyList(const Pair *o, unsigned int n)
{
  Pair *l = new Pair[n];
  for (unsigned int i = 0; i < n; i++)
  {
    l[i] = o[i];
  }
  return l;
}

//----------------------------------------------------------------------------
vtkDICOMTagPath vtkDICOMTagPath::GetTail() const
{
  if (this->More == 0)
  {
    return vtkDICOMTagPath(this->Tail);
  }
  else if (this->More == 1)
  {
    return vtkDICOMTagPath(this->Tail, this->Last.Index, this->Last.Tail);
  }
  else if (this->More == 2)
  {
    return vtkDICOMTagPath(this->Tail,
                           this->List[0].Index, this->List[0].Tail,
                           this->List[1].Index, this->List[1].Tail);
  }

  unsigned int n = this->More-1;
  Pair *t = this->List;
  Pair *l = vtkDICOMTagPath::CopyList(&this->List[1], n);

  return vtkDICOMTagPath(this->Tail, t->Index, t->Tail, n, l);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator==(const vtkDICOMTagPath& b) const
{
  if (this->Head != b.Head)
  {
    return false;
  }
  if (!this->HasTail() || !b.HasTail())
  {
    return (this->HasTail() == b.HasTail());
  }
  if (this->Index != b.Index || this->Tail != b.Tail)
  {
    return false;
  }
  if (this->More != b.More)
  {
    return false;
  }
  if (this->More == 0)
  {
    return true;
  }
  if (this->More == 1)
  {
    return (this->Last.Index == b.Last.Index &&
            this->Last.Tail == b.Last.Tail);
  }
  for (unsigned int i = 0; i < this->More; i++)
  {
    if (this->List[i].Index != b.List[i].Index &&
        this->List[i].Tail != b.List[i].Tail)
    {
      return false;
    }
  }
  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator!=(const vtkDICOMTagPath& b) const
{
  return !(*this == b);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator<(const vtkDICOMTagPath& b) const
{
  if (this->Head != b.Head)
  {
    return (this->Head < b.Head);
  }
  if (!this->HasTail() || !b.HasTail())
  {
    return b.HasTail();
  }
  if (this->Index < b.Index ||
      (this->Index == b.Index &&
       (this->Tail != b.Tail)))
  {
    return (this->Tail < b.Tail);
  }
  if (this->More == 0 || b.More == 0)
  {
    return (this->More < b.More);
  }

  unsigned int aIndex;
  vtkDICOMTag aTail;
  unsigned int bIndex = 0;
  vtkDICOMTag bTail;

  if (this->More == 1)
  {
    aIndex = this->Last.Index;
    aTail = this->Last.Tail;
  }
  else
  {
    aIndex = this->List[0].Index;
    aTail = this->List[0].Tail;
  }
  if (b.More == 1)
  {
    bIndex = b.Last.Index;
    bTail = b.Last.Tail;
  }
  else
  {
    bIndex = b.List[0].Index;
    bTail = b.List[0].Tail;
  }

  unsigned int i = 0;
  for (;;)
  {
    if (aIndex < bIndex ||
        (aIndex == bIndex &&
         (aTail != bTail)))
    {
      return (aTail < bTail);
    }

    i++;
    if (i >= this->More || i >= b.More)
    {
      break;
    }

    aIndex = this->List[i].Index;
    aTail = this->List[i].Tail;
    bIndex = b.List[i].Index;
    bTail = b.List[i].Tail;
  }

  return (this->More < b.More);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator>(const vtkDICOMTagPath& b) const
{
  return !(*this < b || *this == b);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator<=(const vtkDICOMTagPath& b) const
{
  return (*this < b || *this == b);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator>=(const vtkDICOMTagPath& b) const
{
  return !(*this < b);
}
