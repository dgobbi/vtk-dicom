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
  return o;
}

//----------------------------------------------------------------------------
vtkDICOMTagPath::vtkDICOMTagPath(
  const vtkDICOMTagPath& p, unsigned int i, vtkDICOMTag tag)
  : Size(p.Size+1), Head(p.Head), Index(p.Index), Tail(p.Tail), List(0)
{
  if (this->Size == 1)
  {
    this->Head = tag;
  }
  else if (this->Size == 2)
  {
    this->Index = i;
    this->Tail = tag;
  }
  else if (this->Size == 3)
  {
    this->Last.Index = i;
    this->Last.Tag = tag;
  }
  else if (this->Size == 4)
  {
    Pair *l = new Pair[2];
    l[0] = p.Last;
    l[1].Index = i;
    l[1].Tag = tag;
    this->List = l;
  }
  else
  {
    unsigned int n = this->Size - 3;
    Pair *l = new Pair[n + 1];
    for (unsigned int j = 0; j < n; j++)
    {
      l[j] = p.List[j];
    }
    l[n].Index = i;
    l[n].Tag = tag;
    this->List = l;
  }
}

//----------------------------------------------------------------------------
vtkDICOMTagPath& vtkDICOMTagPath::operator=(const vtkDICOMTagPath& o)
{
  if (this != &o)
  {
    this->Size = o.Size;
    this->Head = o.Head;
    this->Index = o.Index;
    this->Tail = o.Tail;
    if (o.Size <= 3)
    {
      this->Last = o.Last;
    }
    else
    {
      this->List = vtkDICOMTagPath::CopyList(o.List, o.Size - 2);
    }
  }
  return *this;
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
  if (this->Size < 2)
  {
    return vtkDICOMTagPath();
  }
  if (this->Size == 2)
  {
    return vtkDICOMTagPath(this->Tail);
  }
  else if (this->Size == 3)
  {
    return vtkDICOMTagPath(this->Tail, this->Last.Index, this->Last.Tag);
  }
  else if (this->Size == 4)
  {
    return vtkDICOMTagPath(this->Tail,
                           this->List[0].Index, this->List[0].Tag,
                           this->List[1].Index, this->List[1].Tag);
  }

  unsigned int n = this->Size - 3;
  Pair *t = this->List;
  Pair *l = vtkDICOMTagPath::CopyList(&this->List[1], n);

  return vtkDICOMTagPath(this->Tail, t->Index, t->Tag, n, l);
}

//----------------------------------------------------------------------------
bool vtkDICOMTagPath::operator==(const vtkDICOMTagPath& b) const
{
  if (this->Size != b.Size)
  {
    return false;
  }
  if (this->Size > 0)
  {
    if (this->Head != b.Head)
    {
      return false;
    }
    if (this->Size > 1)
    {
      if (this->Index != b.Index || this->Tail != b.Tail)
      {
        return false;
      }
      if (this->Size == 3)
      {
        return (this->Last.Index == b.Last.Index &&
                this->Last.Tag == b.Last.Tag);
      }
      unsigned int n = this->Size - 2;
      for (unsigned int i = 0; i < n; i++)
      {
        if (this->List[i].Index != b.List[i].Index &&
            this->List[i].Tag != b.List[i].Tag)
        {
          return false;
        }
      }
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
  if (this->Size == 0 || b.Size == 0)
  {
    return (this->Size < b.Size);
  }
  if (this->Head != b.Head)
  {
    return (this->Head < b.Head);
  }
  unsigned int n = (this->Size < b.Size ? this->Size : b.Size);
  if (n > 1)
  {
    if (this->Index != b.Index)
    {
      return (this->Index < b.Index);
    }
    if (this->Tail != b.Tail)
    {
      return (this->Tail < b.Tail);
    }
  }
  if (n > 2)
  {
    Pair p1 = (this->Size == 3 ? this->Last : this->List[0]);
    Pair p2 = (b.Size == 3 ? b.Last : b.List[0]);

    unsigned int m = n-2;
    unsigned int i = 0;
    for (;;)
    {
      if (p1.Index != p2.Index)
      {
        return (p1.Index < p2.Index);
      }
      if (p1.Tag != p2.Tag)
      {
        return (p1.Tag < p2.Tag);
      }

      if (++i == m)
      {
        break;
      }

      p1 = this->List[i];
      p2 = b.List[i];
    }
  }
  return (this->Size < b.Size);
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
