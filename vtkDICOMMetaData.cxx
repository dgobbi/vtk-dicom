#include "vtkDICOMMetaData.h"

#include <vtkObjectFactory.h>
#include <vtkMatrix4x4.h>
#include <vtkAbstractArray.h>

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
}

// Destructor
vtkDICOMMetaData::~vtkDICOMMetaData()
{
  this->Clear();
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

  this->NumberOfInstances = 1;
  this->Table = NULL;
  this->Head.Next = &this->Tail;
  this->Tail.Prev = &this->Head;
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
    if (n != this->NumberOfInstances)
      {
      this->Modified();
      }
    this->NumberOfInstances = n;
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
      assert(idx >= 0 && idx < static_cast<int>(vptr->GetNumberOfValues()));
      vptr = &sptr[idx];
      }
    }

  return vptr;
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(vtkDICOMTag tag)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(0, tag);
  return (vptr ? *vptr : vtkDICOMValue::GetInvalidValue());
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaData::GetAttributeValue(
  int idx, vtkDICOMTag tag)
{
  const vtkDICOMValue *vptr = this->FindAttributeValue(idx, tag);
  return (vptr ? *vptr : vtkDICOMValue::GetInvalidValue());
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
// Insert an attribute into the hash table
void vtkDICOMMetaData::SetAttributeValue(
  vtkDICOMTag tag, const vtkDICOMValue& v)
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

template<class T>
void vtkDICOMMetaData::SetAttributeValueT(vtkDICOMTag tag, T v)
{
  vtkDICOMVR vr = this->FindDictVR(0, tag);
  if (vr != vtkDICOMVR::UN)
    {
    this->SetAttributeValue(tag, vtkDICOMValue(vr, v));
    }
}

void vtkDICOMMetaData::SetAttributeValue(vtkDICOMTag tag, double v)
{
  this->SetAttributeValueT(tag, v);
}

void vtkDICOMMetaData::SetAttributeValue(vtkDICOMTag tag, const std::string& v)
{
  this->SetAttributeValueT(tag, v);
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

  assert(idx >= 0 && idx < static_cast<int>(vptr->GetNumberOfValues()));

  // first value for this attribute
  if (!vptr->IsValid())
    {
    *vptr = v;
    return;
    }

  // is this a sequence of values?
  vtkDICOMValue *sptr = vptr->GetMultiplexData();
  if (sptr)
    {
    sptr[idx] = v;
    }
  else if (v != *vptr)
    {
    // differs from other instances, must turn value into a list,
    // so create a value that is actually a list of values
    int n = this->NumberOfInstances;
    vtkDICOMValue l;
    sptr = l.AllocateMultiplexData(v.GetVR(), n);
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
}

template<class T>
void vtkDICOMMetaData::SetAttributeValueT(int idx, vtkDICOMTag tag, T v)
{
  vtkDICOMVR vr = this->FindDictVR(idx, tag);
  if (vr != vtkDICOMVR::UN)
    {
    this->SetAttributeValue(idx, tag, vtkDICOMValue(vr, v));
    }
}

void vtkDICOMMetaData::SetAttributeValue(
  int idx, vtkDICOMTag tag, double v)
{
  this->SetAttributeValueT(idx, tag, v);
}

void vtkDICOMMetaData::SetAttributeValue(
  int idx, vtkDICOMTag tag, const std::string& v)
{
  this->SetAttributeValueT(idx, tag, v);
}

//----------------------------------------------------------------------------
bool vtkDICOMMetaData::FindDictEntry(vtkDICOMTag tag, vtkDICOMDictEntry &e)
{
  unsigned int m = DICT_HASH_TABLE_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMDictEntry::Internal **htable = vtkDICOMMetaData::DictHashTable;
  vtkDICOMDictEntry::Internal *hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (hptr->Group || hptr->Element || hptr->VR)
      {
      if (hptr->Group == tag.GetGroup() &&
          hptr->Element == tag.GetElement())
        {
        e = vtkDICOMDictEntry(hptr);
        return true;
        }
      hptr++;
      }
    }

  e = vtkDICOMDictEntry();
  return false;
}

// should only be called from SetAttributeValue
vtkDICOMVR vtkDICOMMetaData::FindDictVR(int idx, vtkDICOMTag tag)
{
  vtkDICOMVR vr = vtkDICOMVR::UN;
  vtkDICOMDictEntry e;

  if (vtkDICOMMetaData::FindDictEntry(tag, e))
    {
    vr = e.GetVR();
    // use the dictionary VR
    if (vr == vtkDICOMVR::XS)
      {
      const vtkDICOMValue &v =
        this->GetAttributeValue(idx, vtkDICOMTag(0x0028,0x0103));
      if (v.IsValid())
        {
        unsigned short r = v.AsUnsignedShort();
        vr = (r == 0 ? vtkDICOMVR::US : vtkDICOMVR::SS);
        }
      else
        {
        vtkErrorMacro("SetAttributeValue: could not look up vr for (" <<
                      tag << ") because PixelRepresentation is not set.");
        }
      }
    else if (vr == vtkDICOMVR::OX)
      {
      if (tag.GetGroup() == 0x5400)
        {
        const vtkDICOMValue &v =
          this->GetAttributeValue(idx, vtkDICOMTag(0x5400,0x1004));
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
          this->GetAttributeValue(idx, vtkDICOMTag(0x0028,0x0100));
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
  else
    {
    vtkErrorMacro("SetAttributeValue: could not find tag (" <<
                  tag << ") in the dictionary");
    }

  return vr;
}

//----------------------------------------------------------------------------
void vtkDICOMMetaData::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "NumberOfInstances: "
     << this->NumberOfInstances << "\n";
  os << indent << "NumberOfDataElements: "
     << this->NumberOfDataElements << "\n";
}
