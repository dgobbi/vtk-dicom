#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include <assert.h>

void vtkDICOMSequence::AddItem(const vtkDICOMItem& item)
{
  // if value is not a sequence, make it into a sequence
  if (this->V == 0 || this->V->Type != VTK_DICOM_ITEM)
    {
    this->AllocateSequenceData(vtkDICOMVR::SQ, 2);
    this->V->NumberOfValues = 0;
    this->V->VL = 0xffffffff;
    }

  vtkDICOMItem *ptr =
    static_cast<const ValueT<vtkDICOMItem> *>(this->V)->Data;

  unsigned int n = this->V->NumberOfValues;
  unsigned int nn = 0;
  // reallocate if n is a power of two
  if (n > 1 && ((n - 1) & n) == 0)
    {
    nn = 2*n;
    }
  // reallocate if not unique reference, or not yet growable
  else if (this->V->ReferenceCount != 1 || this->V->VL != 0xffffffff)
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
    const vtkDICOMItem *cptr = ptr;
    ptr = this->AllocateSequenceData(vtkDICOMVR::SQ, nn);
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

  // mark as growable
  this->V->VL = 0xffffffff;
  // add the item
  ptr[this->V->NumberOfValues++] = item;
}

void vtkDICOMSequence::SetItem(
  unsigned int i, const vtkDICOMItem& item)
{
  assert(this->V != 0 && this->V->Type == VTK_DICOM_ITEM);
  assert(i < this->V->NumberOfValues);

  vtkDICOMItem *ptr =
    static_cast<const ValueT<vtkDICOMItem> *>(this->V)->Data;

  // reallocate the array if we aren't the sole owner
  if (this->V->ReferenceCount != 1)
    {
    assert(this->V->ReferenceCount == 1);
    unsigned int m = this->V->NumberOfValues;
    const vtkDICOMItem *cptr = ptr;
    ptr = this->AllocateSequenceData(vtkDICOMVR::SQ, m);
    for (unsigned int j = 0; j < m; j++)
      {
      ptr[j] = cptr[j];
      }
    }

  ptr[i] = item;
}

const vtkDICOMItem &vtkDICOMSequence::GetItem(unsigned int i) const
{
  assert(this->V != 0 && this->V->Type == VTK_DICOM_ITEM);
  assert(i < this->V->NumberOfValues);

  vtkDICOMItem *ptr =
    static_cast<const ValueT<vtkDICOMItem> *>(this->V)->Data;

  return ptr[i];
}
