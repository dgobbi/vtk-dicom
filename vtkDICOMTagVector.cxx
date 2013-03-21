#include "vtkDICOMTagVector.h"

#include <assert.h>

void vtkDICOMTagVector::AddTag(vtkDICOMTag tag)
{
  // if value is not a tag list, make it into a tag list
  if (this->V == 0 || this->V->VR != vtkDICOMVR::AT)
    {
    this->AllocateUnsignedShortData(vtkDICOMVR::AT, 2);
    this->V->NumberOfValues = 0;
    }

  unsigned short *ptr =
    static_cast<ValueT<unsigned short> *>(this->V)->Data;

  unsigned int n = this->V->NumberOfValues;
  unsigned int nn = 0;
  // reallocate if n is a power of two
  if (n > 1 && ((n - 1) & n) == 0)
    {
    nn = 2*n;
    }
  // reallocate if not unique reference
  else if (this->V->ReferenceCount != 1)
    {
    assert(this->V->ReferenceCount == 1);
    // get next power of two that is greater than n
    nn = 1;
    do { nn <<= 1; } while (nn <= n);
    }
  // reallocate the array
  if (nn != 0)
    {
    Value *v = this->V;
    ++(v->ReferenceCount);
    const unsigned short *cptr = ptr;
    ptr = this->AllocateUnsignedShortData(vtkDICOMVR::AT, nn);
    this->V->NumberOfValues = n;
    for (unsigned int i = 0; i < n; i++)
      {
      ptr[i] = cptr[i];
      }
    if (--(v->ReferenceCount) == 0)
      {
      vtkDICOMValue::FreeValue(v);
      }
    }

  // add the tag
  ptr[this->V->NumberOfValues++] = tag.GetGroup();
  ptr[this->V->NumberOfValues++] = tag.GetElement();
}

void vtkDICOMTagVector::SetTag(unsigned int i, vtkDICOMTag tag)
{
  assert(this->V != 0 && this->V->VR == vtkDICOMVR::AT);
  assert(2*i < this->V->NumberOfValues);

  unsigned short *ptr =
    static_cast<ValueT<unsigned short> *>(this->V)->Data;

  // reallocate the array if we aren't the sole owner
  if (this->V->ReferenceCount != 1)
    {
    assert(this->V->ReferenceCount == 1);
    unsigned int m = this->V->NumberOfValues;
    const unsigned short *cptr = ptr;
    ptr = this->AllocateUnsignedShortData(vtkDICOMVR::SQ, m);
    for (unsigned int j = 0; j < m; j++)
      {
      ptr[j] = cptr[j];
      }
    }

  ptr[2*i] = tag.GetGroup();
  ptr[2*i+1] = tag.GetElement();
}

vtkDICOMTag vtkDICOMTagVector::GetTag(unsigned int i) const
{
  assert(this->V != 0 && this->V->VR == vtkDICOMVR::AT);
  assert(2*i < this->V->NumberOfValues);

  const unsigned short *ptr =
    static_cast<const ValueT<unsigned short> *>(this->V)->Data;

  return vtkDICOMTag(ptr[2*i], ptr[2*i+1]);
}
