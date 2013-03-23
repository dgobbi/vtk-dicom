#include "vtkDICOMValue.h"
#include "vtkDICOMItem.h"

#include <vtkTypeTraits.h>

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include <new>

//----------------------------------------------------------------------------
// Use anonymous namespace to limit function scope to this file only
namespace {

// Cast an array of "n" values from type "IT" to type "OT".
template<class IT, class OT>
void NumericalConversion(IT *u, OT *v, unsigned int n)
{
  if (n != 0) { do { *v++ = static_cast<OT>(*u++); } while (--n); }
}

// The input is a list of one or more numerical string values separated
// by backslashes, for example "1.23435\85234.0\2345.22".  Convert "n"
// values to type OT, starting at the "i"th backslash-separated value.
// If the VR is IS (integer string) then use strol(), if DS use strtod().
template<class OT>
void StringConversion(
  const char *cp, vtkDICOMVR vr, OT *v, unsigned int i, unsigned int n)
{
  if (vr == vtkDICOMVR::IS || vr == vtkDICOMVR::DS)
    {
    for (unsigned int j = 0; j < i && *cp != '\0'; j++)
      {
      bool bk = false;
      do
        {
        bk = (*cp == '\\');
        cp++;
        }
      while (!bk && *cp != '\0');
      }

    for (unsigned int k = 0; k < n && *cp != '\0'; k++)
      {
      if (vr == vtkDICOMVR::DS)
        {
        *v++ = static_cast<OT>(strtod(cp, NULL));
        }
      else
        {
        *v++ = static_cast<OT>(strtol(cp, NULL, 10));
        }
      bool bk = false;
      do
        {
        bk = (*cp == '\\');
        cp++;
        }
      while (!bk && *cp != '\0');
      }
    }
  else if (n > 0)
    {
    do { *v++ = 0; } while (--n);
    }
}

// custom allocator
void *ValueMalloc(size_t size)
{
  void *vp = 0;
  while ((vp = malloc(size)) == 0)
    {
    // for C++11, get_new_handler is preferred
    std::new_handler global_handler = std::set_new_handler(0);
    std::set_new_handler(global_handler);

    if (global_handler)
      {
      global_handler();
      }
    else
      {
      throw std::bad_alloc();
      }
    }

  return vp;
}

// custom deallocator
void ValueFree(void *vp)
{
  free(vp);
}

} // end anonymous namespace

//----------------------------------------------------------------------------
// Construct a numerical value.
template<class T>
vtkDICOMValue::ValueT<T>::ValueT(vtkDICOMVR vr, unsigned int vn)
{
  this->VR = vr;
  this->Type = static_cast<unsigned char>(vtkTypeTraits<T>::VTKTypeID());
  this->VL = vn*sizeof(T);
  this->NumberOfValues = vn;
}

// Construct a string value.
template<>
vtkDICOMValue::ValueT<char>::ValueT(vtkDICOMVR vr, unsigned int vn)
{
  this->VR = vr;
  this->Type = VTK_CHAR;
  this->VL = vn + (vn & 1); // pad VL to make it even
  this->NumberOfValues = 1;
}

// Construct a "bytes" value.
template<>
vtkDICOMValue::ValueT<unsigned char>::ValueT(vtkDICOMVR vr, unsigned int vn)
{
  this->VR = vr;
  this->Type = VTK_UNSIGNED_CHAR;
  this->VL = vn + (vn & 1); // pad VL to make it even
  this->NumberOfValues = vn;
}

// Construct a sequence of items.
template<>
vtkDICOMValue::ValueT<vtkDICOMItem>::ValueT(vtkDICOMVR vr, unsigned int vn)
{
  this->VR = vr; // better be SQ
  this->Type = VTK_DICOM_ITEM;
  this->VL = 0;
  this->NumberOfValues = vn;
  vtkDICOMItem *dp = this->Data;
  for (unsigned int i = 0; i < vn; i++)
    {
    // call constructor manually with placement new
    new(dp) vtkDICOMItem();
    dp++;
    }
}

// Construct a list of values.
template<>
vtkDICOMValue::ValueT<vtkDICOMValue>::ValueT(vtkDICOMVR vr, unsigned int vn)
{
  this->VR = vr;
  this->Type = VTK_DICOM_VALUE;
  this->VL = 0;
  this->NumberOfValues = vn;
  vtkDICOMValue *dp = this->Data;
  for (unsigned int i = 0; i < vn; i++)
    {
    // call constructor manually with placement new
    new(dp) vtkDICOMValue();
    dp++;
    }
}

//----------------------------------------------------------------------------
template<class T>
T *vtkDICOMValue::Allocate(vtkDICOMVR vr, unsigned int vn)
{
  this->Clear();
  // Use C++ "placement new" to allocate a single block of memory that
  // includes both the Value struct and the array of values.
  void *vp = ValueMalloc(sizeof(Value) + vn*sizeof(T));
  ValueT<T> *v = new(vp) ValueT<T>(vr, vn);
  // Test the assumption that Data is at an offset of sizeof(Value)
  assert(static_cast<char *>(static_cast<void *>(v->Data)) ==
         static_cast<char *>(vp) + sizeof(Value));
  this->V = v;
  return v->Data;
}

template<>
char *vtkDICOMValue::Allocate<char>(vtkDICOMVR vr, unsigned int vn)
{
  this->Clear();
  // Strings of any type other than UI will be padded with spaces to
  // give an even number of chars.  All strings (including UI) need one
  // extra char for the null terminator to make them valid C strings.
  unsigned int pad = (vn & (vr != vtkDICOMVR::UI));
  // Use C++ "placement new" to allocate a single block of memory that
  // includes both the Value struct and the array of values.
  void *vp = ValueMalloc(sizeof(Value) + vn + pad + 1);
  ValueT<char> *v = new(vp) ValueT<char>(vr, vn);
  // Test the assumption that Data is at an offset of sizeof(Value)
  assert(v->Data == static_cast<char *>(vp) + sizeof(Value));
  this->V = v;
  return v->Data;
}

char *vtkDICOMValue::AllocateCharData(vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<char>(vr, vn);
}

unsigned char *vtkDICOMValue::AllocateUnsignedCharData(
  vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<unsigned char>(vr, vn);
}

short *vtkDICOMValue::AllocateShortData(vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<short>(vr, vn);
}

unsigned short *vtkDICOMValue::AllocateUnsignedShortData(
  vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<unsigned short>(vr, vn);
}

int *vtkDICOMValue::AllocateIntData(vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<int>(vr, vn);
}

unsigned int *vtkDICOMValue::AllocateUnsignedIntData(
  vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<unsigned int>(vr, vn);
}

float *vtkDICOMValue::AllocateFloatData(vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<float>(vr, vn);
}

double *vtkDICOMValue::AllocateDoubleData(vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<double>(vr, vn);
}

vtkDICOMItem *vtkDICOMValue::AllocateSequenceData(
  vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<vtkDICOMItem>(vr, vn);
}

vtkDICOMValue *vtkDICOMValue::AllocateMultiplexData(
  vtkDICOMVR vr, unsigned int vn)
{
  return this->Allocate<vtkDICOMValue>(vr, vn);
}

//----------------------------------------------------------------------------
unsigned char *vtkDICOMValue::ReallocateUnsignedCharData(unsigned int vn)
{
  assert(this->V != 0);
  assert(this->V->VR == vtkDICOMVR::OB || this->V->VR == vtkDICOMVR::UN);

  unsigned int n = this->V->NumberOfValues;
  unsigned char *ptr =
    static_cast<const ValueT<unsigned char> *>(this->V)->Data;

  Value *v = this->V;
  const unsigned char *cptr = ptr;

  // increment ref count before reallocating
  ++(v->ReferenceCount);
  ptr = this->AllocateUnsignedCharData(v->VR, vn);
  n = (n < vn ? n : vn);
  if (n > 0) { memcpy(ptr, cptr, n); }
  // this is the new V after reallocating
  this->V->NumberOfValues = vn;
  // indicate encapsulated contents
  this->V->VL = 0xffffffff;

  // decrement the refcount of the old V
  if (--(v->ReferenceCount) == 0)
    {
    vtkDICOMValue::FreeValue(v);
    }

  return ptr;
}

//----------------------------------------------------------------------------
template<class T>
void vtkDICOMValue::CreateValue(vtkDICOMVR vr, const T *data, const T *end)
{
  typedef vtkDICOMVR VR; // shorthand

  size_t size = end - data;
  assert(size*sizeof(T) <= 0xffffffffu);
  unsigned int n = static_cast<unsigned int>(size);
  int vt = vtkTypeTraits<T>::VTKTypeID();

  this->V = 0;

  if (vr == VR::OX)
    {
    // OX means "OB or OW", use type to find out which
    vr = (vt == VTK_UNSIGNED_CHAR ? VR::OB : VR::OW);
    }
  else if (vr == VR::XS)
    {
    // XS means "SS or US", use type to find out which
    vr = (vt == VTK_UNSIGNED_SHORT ? VR::US : VR::SS);
    }

  // use VR to set data type, then convert input to that type
  if (vr == VR::FD)
    {
    double *ptr = this->AllocateDoubleData(vr, n);
    NumericalConversion(data, ptr, n);
    }
  else if (vr == VR::FL)
    {
    float *ptr = this->AllocateFloatData(vr, n);
    NumericalConversion(data, ptr, n);
    }
  else if (vr == VR::UL)
    {
    unsigned int *ptr = this->AllocateUnsignedIntData(vr, n);
    NumericalConversion(data, ptr, n);
    }
  else if (vr == VR::SL)
    {
    int *ptr = this->AllocateIntData(vr, n);
    NumericalConversion(data, ptr, n);
    }
  else if (vr == VR::US)
    {
    unsigned short *ptr = this->AllocateUnsignedShortData(vr, n);
    NumericalConversion(data, ptr, n);
    }
  else if (vr == VR::SS)
    {
    short *ptr = this->AllocateShortData(vr, n);
    NumericalConversion(data, ptr, n);
    }
  else if (vr == VR::DS)
    {
    char *cp = this->AllocateCharData(vr, 17*n);
    char *dp = cp;
    for (unsigned int i = 0; i < n; i++)
      {
      double d = static_cast<double>(data[i]);
      // clamp to the range allowed for DICOM decimal strings
      if (d > 9.999999999e+99)
        {
        d = 9.999999999e+99;
        }
      else if (d < -9.999999999e+99)
        {
        d = -9.999999999e+99;
        }
      else if (fabs(d) < 1e-99 || isnan(d))
        {
        d = 0.0;
        }
      // use a precision that will use 16 characters maximum
      sprintf(cp, "%.10g", d);
      cp += strlen(cp);
      *cp++ = '\\';
      }
    if (cp != dp) { --cp; }
    this->V->NumberOfValues = n;
    this->V->VL = static_cast<unsigned int>(cp - dp);
    if (this->V->VL & 1)
      { // pad to even number of chars
      *cp++ = ' ';
      this->V->VL++;
      }
    *cp = '\0';
    }
  else if (vr == VR::IS)
    {
    char *cp = this->AllocateCharData(vr, 13*n);
    char *dp = cp;
    for (unsigned int i = 0; i < n; i++)
      {
      sprintf(cp, "%i", static_cast<int>(data[i]));
      cp += strlen(cp);
      *cp++ = '\\';
      }
    if (cp != dp) { --cp; }
    this->V->NumberOfValues = n;
    this->V->VL = static_cast<unsigned int>(cp - dp);
    if (this->V->VL & 1)
      { // pad to even number of chars
      *cp++ = ' ';
      this->V->VL++;
      }
    *cp = '\0';
    }
  else if (vr == VR::OB || vr == VR::UN)
    {
    unsigned int m = n*sizeof(T);
    int pad = (m & 1);
    unsigned char *ptr = this->AllocateUnsignedCharData(vr, m + pad);
    memcpy(ptr, data, m);
    if (pad) { ptr[m] = 0; } // pad to even
    this->V->NumberOfValues = m;
    }
  else if (vr == VR::OW || vr == VR::AT)
    {
    if (vt == VTK_UNSIGNED_SHORT || vr == VR::AT)
      {
      unsigned short *ptr = this->AllocateUnsignedShortData(vr, n);
      memcpy(ptr, data, n*2);
      }
    else
      {
      short *ptr = this->AllocateShortData(vr, n*sizeof(T)/2);
      memcpy(ptr, data, n*sizeof(T));
      }
    }
  else if (vr == VR::OF)
    {
    float *ptr = this->AllocateFloatData(vr, n*sizeof(T)/4);
    memcpy(ptr, data, n*sizeof(T));
    }
}

template<>
void vtkDICOMValue::CreateValue<char>(
  vtkDICOMVR vr, const char *data, const char *end)
{
  typedef vtkDICOMVR VR;

  size_t size = end - data;
  assert(size <= 0xffffffffu);
  unsigned int m = static_cast<unsigned int>(size);

  this->V = 0;

  // directly copy data into these VRs without conversion
  if (vr == VR::ST || vr == VR::LT || vr == VR::UT)
    {
    int pad = (m & 1);
    char *ptr = this->AllocateCharData(vr, m + pad);
    memcpy(ptr, data, m);
    // pad to even length with a space
    if (pad) { ptr[m++] = ' '; }
    ptr[m] = '\0';
    this->V->NumberOfValues = 1;
    }
  else if (vr == VR::OW)
    {
    short *ptr = this->AllocateShortData(vr, m/2);
    memcpy(ptr, data, m);
    }
  else if (vr == VR::OF)
    {
    float *ptr = this->AllocateFloatData(vr, m/4);
    memcpy(ptr, data, m);
    }
  else if (vr == VR::UN || vr == VR::OB || vr == VR::OX)
    {
    int pad = (m & 1);
    unsigned char *ptr = this->AllocateUnsignedCharData(vr, m + pad);
    memcpy(ptr, data, m);
    // pad to even length with a null
    if (pad != 0) { ptr[m] = 0; }
    }
  else if (vr == VR::AT)
    {
    unsigned short *ptr = this->AllocateUnsignedShortData(vr, m/2);
    memcpy(ptr, data, m);
    }

  if (this->V)
    {
    return;
    }

  // count the number of backslash-separated values
  unsigned int n = 1;
  for (unsigned int i = 0; i < m; i++)
    {
    n += (data[i] == '\\');
    }

  // convert input string to the specified VR
  if (vr == VR::AE || vr == VR::AS || vr == VR::CS ||
      vr == VR::DA || vr == VR::DS || vr == VR::DT ||
      vr == VR::IS || vr == VR::LO || vr == VR::PN ||
      vr == VR::SH || vr == VR::TM || vr == VR::UI)
    {
    int pad = (m & 1);
    char *cp = this->AllocateCharData(vr, m);
    strncpy(cp, data, m);
    // if not UI, then pad to even length with a space
    if (pad && vr != VR::UI) { cp[m++] = ' '; }
    cp[m] = '\0';
    this->V->NumberOfValues = n;
    }
  else if (vr == VR::FD)
    {
    double *ptr = this->AllocateDoubleData(vr, n);
    StringConversion(data, VR::DS, ptr, 0, n);
    }
  else if (vr == VR::FL)
    {
    float *ptr = this->AllocateFloatData(vr, n);
    StringConversion(data, VR::DS, ptr, 0, n);
    }
  else if (vr == VR::UL)
    {
    unsigned int *ptr = this->AllocateUnsignedIntData(vr, n);
    StringConversion(data, VR::IS, ptr, 0, n);
    }
  else if (vr == VR::SL)
    {
    int *ptr = this->AllocateIntData(vr, n);
    StringConversion(data, VR::IS, ptr, 0, n);
    }
  else if (vr == VR::US)
    {
    unsigned short *ptr = this->AllocateUnsignedShortData(vr, n);
    StringConversion(data, VR::IS, ptr, 0, n);
    }
  else if (vr == VR::SS || vr == VR::XS)
    {
    short *ptr = this->AllocateShortData(vr, n);
    StringConversion(data, VR::IS, ptr, 0, n);
    }
}

//----------------------------------------------------------------------------
const vtkDICOMValue vtkDICOMValue::InvalidValue;

//----------------------------------------------------------------------------
// Constructor methods call the factory to create the right internal type.
vtkDICOMValue::vtkDICOMValue(vtkDICOMVR vr, double v)
{
  this->CreateValue(vr, &v, &v + 1);
}

vtkDICOMValue::vtkDICOMValue(vtkDICOMVR vr, const std::string& v)
{
  this->CreateValue(vr, v.data(), v.data() + v.size());
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const char *data, const char *end)
{
  this->CreateValue(vr, data, end);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const unsigned char *data, const unsigned char *end)
{
  this->CreateValue(vr, data, end);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const short *data, const short *end)
{
  this->CreateValue(vr, data, end);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const unsigned short *data, const unsigned short *end)
{
  this->CreateValue(vr, data, end);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const int *data, const int *end)
{
  this->CreateValue(vr, data, end);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const unsigned int *data, const unsigned int *end)
{
  this->CreateValue(vr, data, end);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const float *data, const float *end)
{
  this->CreateValue(vr, data, end);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const double *data, const double *end)
{
  this->CreateValue(vr, data, end);
}

//----------------------------------------------------------------------------
// It is necessary to check the Type so that the correct information can
// be freed.  The constructor guarantees that Type is always set correctly.
void vtkDICOMValue::FreeValue(Value *v)
{
  if (v)
    {
    if (v->Type == VTK_DICOM_ITEM)
      {
      vtkDICOMItem *dp = static_cast<ValueT<vtkDICOMItem> *>(v)->Data;
      for (unsigned int i = 0; i < v->NumberOfValues; i++)
        {
        // placement new was used, so destructor must be called manually
        dp->~vtkDICOMItem();
        dp++;
        }
      }
    else if (v->Type == VTK_DICOM_VALUE)
      {
      vtkDICOMValue *dp = static_cast<ValueT<vtkDICOMValue> *>(v)->Data;
      for (unsigned int i = 0; i < v->NumberOfValues; i++)
        {
        // placement new was used, so destructor must be called manually
        dp->~vtkDICOMValue();
        dp++;
        }
      }

    ValueFree(v);
    }
}

//----------------------------------------------------------------------------
const char *vtkDICOMValue::GetCharData() const
{
  const char *ptr = 0;
  if (this->V && this->V->Type == VTK_CHAR)
    {
    ptr = static_cast<const ValueT<char> *>(this->V)->Data;
    }
  return ptr;
}

const unsigned char *vtkDICOMValue::GetUnsignedCharData() const
{
  const unsigned char *ptr = 0;
  if (this->V && this->V->Type == VTK_UNSIGNED_CHAR)
    {
    ptr = static_cast<const ValueT<unsigned char> *>(this->V)->Data;
    }
  return ptr;
}

const short *vtkDICOMValue::GetShortData() const
{
  const short *ptr = 0;
  if (this->V)
    {
    if (this->V->Type == VTK_SHORT)
      {
      ptr = static_cast<const ValueT<short> *>(this->V)->Data;
      }
    else if (this->V->Type == VTK_UNSIGNED_SHORT &&
             this->V->VR == vtkDICOMVR::OW)
      {
      ptr = reinterpret_cast<const short *>(
        static_cast<const ValueT<unsigned short> *>(this->V)->Data);
      }
    }
  return ptr;
}

const unsigned short *vtkDICOMValue::GetUnsignedShortData() const
{
  const unsigned short *ptr = 0;
  if (this->V)
    {
    if (this->V->Type == VTK_UNSIGNED_SHORT)
      {
      ptr = static_cast<const ValueT<unsigned short> *>(this->V)->Data;
      }
    else if (this->V->Type == VTK_SHORT &&
             this->V->VR == vtkDICOMVR::OW)
      {
      ptr = reinterpret_cast<const unsigned short *>(
        static_cast<const ValueT<short> *>(this->V)->Data);
      }
    }
  return ptr;
}

const int *vtkDICOMValue::GetIntData() const
{
  const int *ptr = 0;
  if (this->V && this->V->Type == VTK_INT)
    {
    ptr = static_cast<const ValueT<int> *>(this->V)->Data;
    }
  return ptr;
}

const unsigned int *vtkDICOMValue::GetUnsignedIntData() const
{
  const unsigned int *ptr = 0;
  if (this->V && this->V->Type == VTK_UNSIGNED_INT)
    {
    ptr = static_cast<const ValueT<unsigned int> *>(this->V)->Data;
    }
  return ptr;
}

const float *vtkDICOMValue::GetFloatData() const
{
  const float *ptr = 0;
  if (this->V && this->V->Type == VTK_FLOAT)
    {
    ptr = static_cast<const ValueT<float> *>(this->V)->Data;
    }
  return ptr;
}

const double *vtkDICOMValue::GetDoubleData() const
{
  const double *ptr = 0;
  if (this->V && this->V->Type == VTK_DOUBLE)
    {
    ptr = static_cast<const ValueT<double> *>(this->V)->Data;
    }
  return ptr;
}

const vtkDICOMItem *vtkDICOMValue::GetSequenceData() const
{
  const vtkDICOMItem *ptr = 0;
  if (this->V && this->V->Type == VTK_DICOM_ITEM)
    {
    ptr = static_cast<const ValueT<vtkDICOMItem> *>(this->V)->Data;
    }
  return ptr;
}

const vtkDICOMValue *vtkDICOMValue::GetMultiplexData() const
{
  const vtkDICOMValue *ptr = 0;
  if (this->V && this->V->Type == VTK_DICOM_VALUE)
    {
    ptr = static_cast<const ValueT<vtkDICOMValue> *>(this->V)->Data;
    }
  return ptr;
}

vtkDICOMValue *vtkDICOMValue::GetMultiplexData()
{
  vtkDICOMValue *ptr = 0;
  if (this->V && this->V->Type == VTK_DICOM_VALUE)
    {
    ptr = static_cast<ValueT<vtkDICOMValue> *>(this->V)->Data;
    }
  return ptr;
}

//----------------------------------------------------------------------------
template<class VT>
void vtkDICOMValue::GetValuesT(VT *v, unsigned int s, unsigned int c) const
{
  switch (this->V->Type)
    {
    case VTK_CHAR:
      StringConversion(
        static_cast<const ValueT<char> *>(this->V)->Data, this->V->VR,
        v, s, c);
      break;
    case VTK_UNSIGNED_CHAR:
      NumericalConversion(
        static_cast<const ValueT<unsigned char> *>(this->V)->Data+s, v, c);
      break;
    case VTK_SHORT:
      NumericalConversion(
        static_cast<const ValueT<short> *>(this->V)->Data+s, v, c);
      break;
    case VTK_UNSIGNED_SHORT:
      NumericalConversion(
        static_cast<const ValueT<unsigned short> *>(this->V)->Data+s, v, c);
      break;
    case VTK_INT:
      NumericalConversion(
        static_cast<const ValueT<int> *>(this->V)->Data+s, v, c);
      break;
    case VTK_UNSIGNED_INT:
      NumericalConversion(
        static_cast<const ValueT<unsigned int> *>(this->V)->Data+s, v, c);
      break;
    case VTK_FLOAT:
      NumericalConversion(
        static_cast<const ValueT<float> *>(this->V)->Data+s, v, c);
      break;
    case VTK_DOUBLE:
      NumericalConversion(
        static_cast<const ValueT<double> *>(this->V)->Data+s, v, c);
      break;
    }
}

template<>
void vtkDICOMValue::GetValuesT<std::string>(
  std::string *v, unsigned int s, unsigned int c) const
{
  for (unsigned int i = 0; i < c; i++)
    {
    v->clear();
    this->AppendValueToString(*v++, i+s);
    }
}

//----------------------------------------------------------------------------
// These are interface methods that call the templated internal methods.
void vtkDICOMValue::GetValues(
  unsigned char *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

void vtkDICOMValue::GetValues(
  short *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

void vtkDICOMValue::GetValues(
  unsigned short *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

void vtkDICOMValue::GetValues(
  int *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

void vtkDICOMValue::GetValues(
  unsigned int *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

void vtkDICOMValue::GetValues(
  float *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

void vtkDICOMValue::GetValues(
  double *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

void vtkDICOMValue::GetValues(
  std::string *v, unsigned int s, unsigned int c) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, s, c);
}

//----------------------------------------------------------------------------
unsigned char vtkDICOMValue::GetUnsignedChar(unsigned int i) const
{
  unsigned char v = 0;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->GetValuesT(&v, i, 1);
    }
  return v;
}

short vtkDICOMValue::GetShort(unsigned int i) const
{
  short v = 0;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->GetValuesT(&v, i, 1);
    }
  return v;
}

unsigned short vtkDICOMValue::GetUnsignedShort(unsigned int i) const
{
  unsigned short v = 0;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->GetValuesT(&v, i, 1);
    }
  return v;
}

int vtkDICOMValue::GetInt(unsigned int i) const
{
  int v = 0;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->GetValuesT(&v, i, 1);
    }
  return v;
}

unsigned int vtkDICOMValue::GetUnsignedInt(unsigned int i) const
{
  unsigned int v = 0;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->GetValuesT(&v, i, 1);
    }
  return v;
}

float vtkDICOMValue::GetFloat(unsigned int i) const
{
  float v = 0.0;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->GetValuesT(&v, i, 1);
    }
  return v;
}

double vtkDICOMValue::GetDouble(unsigned int i) const
{
  double v = 0.0;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->GetValuesT(&v, i, 1);
    }
  return v;
}

std::string vtkDICOMValue::GetString(unsigned int i) const
{
  std::string v;
  if (this->V && i < this->V->NumberOfValues)
    {
    this->AppendValueToString(v, i);
    }
  return v;
}

//----------------------------------------------------------------------------
unsigned char vtkDICOMValue::AsUnsignedChar() const
{
  unsigned char v = 0;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->GetValuesT(&v, 0, 1);
    }
  return v;
}

short vtkDICOMValue::AsShort() const
{
  short v = 0;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->GetValuesT(&v, 0, 1);
    }
  return v;
}

unsigned short vtkDICOMValue::AsUnsignedShort() const
{
  unsigned short v = 0;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->GetValuesT(&v, 0, 1);
    }
  return v;
}

int vtkDICOMValue::AsInt() const
{
  int v = 0;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->GetValuesT(&v, 0, 1);
    }
  return v;
}

unsigned int vtkDICOMValue::AsUnsignedInt() const
{
  unsigned int v = 0;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->GetValuesT(&v, 0, 1);
    }
  return v;
}

float vtkDICOMValue::AsFloat() const
{
  float v = 0.0;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->GetValuesT(&v, 0, 1);
    }
  return v;
}

double vtkDICOMValue::AsDouble() const
{
  double v = 0.0;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->GetValuesT(&v, 0, 1);
    }
  return v;
}

std::string vtkDICOMValue::AsString() const
{
  std::string v;
  if (this->V && this->V->NumberOfValues == 1)
    {
    this->AppendValueToString(v, 0);
    }
  return v;
}

vtkDICOMTag vtkDICOMValue::AsTag() const
{
  unsigned int g = 0;
  unsigned int e = 0;
  if (this->V && this->V->VR == vtkDICOMVR::AT &&
      this->V->NumberOfValues == 2)
    {
    const unsigned short *p =
      static_cast<const ValueT<unsigned short> *>(this->V)->Data;
    e = p[0];
    g = p[1];
    }
  return vtkDICOMTag(g, e);
}

//----------------------------------------------------------------------------
// Get one of the backslash-separated substrings, requires a text value.
void vtkDICOMValue::Substring(
  unsigned int i, const char *&start, const char *&end) const
{
  const char *cp = static_cast<const ValueT<char> *>(this->V)->Data;
  const char *ep = cp + this->V->VL;
  const char *dp = ep;

  if (this->V->NumberOfValues > 1 && ++i > 0)
    {
    dp = cp - 1;
    do
      {
      cp = dp + 1;
      do { dp++; } while (*dp != '\\' && dp != ep);
      }
    while (--i != 0 && dp != ep);
    }

  // remove any spaces used as padding
  vtkDICOMVR vr = this->V->VR;
  if (vr != vtkDICOMVR::ST &&
      vr != vtkDICOMVR::LT &&
      vr != vtkDICOMVR::UT)
    {
    while (cp != dp && cp[0] == ' ') { cp++; }
    }
  while (cp != dp && dp[-1] == ' ') { dp--; }

  start = cp;
  end = dp;
}

//----------------------------------------------------------------------------
// Convert one value to text and add it to the supplied string
void vtkDICOMValue::AppendValueToString(
  std::string& str, unsigned int i) const
{
  const char *cp = 0;
  const char *dp = 0;
  double f = 0.0;
  int d = 0;
  unsigned int u = 0;

  if (this->V == 0)
    {
    return;
    }

  assert(i < this->V->NumberOfValues);

  switch (this->V->Type)
    {
    case VTK_CHAR:
      this->Substring(i, cp, dp);
      break;
    case VTK_UNSIGNED_CHAR:
      d = static_cast<const ValueT<unsigned char> *>(this->V)->Data[i];
      break;
    case VTK_SHORT:
      d = static_cast<const ValueT<short> *>(this->V)->Data[i];
      break;
    case VTK_UNSIGNED_SHORT:
      d = static_cast<const ValueT<unsigned short> *>(this->V)->Data[i];
      break;
    case VTK_INT:
      d = static_cast<const ValueT<int> *>(this->V)->Data[i];
      break;
    case VTK_UNSIGNED_INT:
      u = static_cast<const ValueT<unsigned int> *>(this->V)->Data[i];
      break;
    case VTK_FLOAT:
      f = static_cast<const ValueT<float> *>(this->V)->Data[i];
      break;
    case VTK_DOUBLE:
      f = static_cast<const ValueT<double> *>(this->V)->Data[i];
      break;
    }

  if (this->V->Type == VTK_CHAR)
    {
    while (cp != dp && dp[-1] == '\0') { --dp; }
    str.append(cp, dp);
    }
  else if (this->V->Type == VTK_FLOAT || this->V->Type == VTK_DOUBLE)
    {
    // force consistent printing of "inf", "nan" regardless of platform
    if (isnan(f))
      {
      str.append("nan");
      }
    else if (isinf(f))
      {
      str.append((f < 0) ? "-inf" : "inf");
      }
    else
      {
      char text[32];
      // guard against printing non-significant digits:
      // use exponential form if printing in "%f" format
      // would print an integer that is too large for the
      // float to accurately represent.
      if ((this->V->Type == VTK_DOUBLE &&
           fabs(f) <= 9007199254740992.0) || // 2^53
          (this->V->Type == VTK_FLOAT &&
           fabs(f) <= 16777216.0)) // 2^24
        {
        if (this->V->Type == VTK_DOUBLE)
          {
          sprintf(text, "%#.16g", f);
          }
        else
          {
          sprintf(text, "%#.8g", f);
          }
        // make sure there is a zero after the decimal point
        size_t l = strlen(text);
        if (l > 0 && text[l-1] == '.')
          {
          text[l++] = '0';
          text[l] = '\0';
          }
        }
      else
        {
        if (this->V->Type == VTK_DOUBLE)
          {
          sprintf(text, "%.15e", f);
          }
        else
          {
          sprintf(text, "%.7e", f);
          }
        }

      // trim trailing zeros, except the one following decimal point
      unsigned int ti = 0;
      while (text[ti] != '\0' && text[ti] != 'e') { ti++; }
      unsigned int tj = ti;
      while (tj > 1 && text[tj-1] == '0' && text[tj-2] != '.') { tj--; }
      while (text[ti] != '\0') { text[tj++] = text[ti++]; }
      text[tj] = '\0';

      str.append(text);
      }
    }
  else
    {
    // simple code to convert an integer to a string
    char text[16];
    unsigned int ti = 16;

    // if d is nonzero, set u to abs(d)
    if (d > 0)
      {
      u = d;
      }
    if (d < 0)
      {
      u = -d;
      }
    // convert u to a string
    do
      {
      text[--ti] = '0' + static_cast<char>(u % 10);
      u /= 10;
      }
    while (u != 0);
    // add sign
    if (d < 0)
      {
      text[--ti] = '-';
      }

    str.append(&text[ti], &text[16]);
    }
}

//----------------------------------------------------------------------------
// These compare functions can only be safely used within "operator=="
// because they require a pre-check that VL is not zero and that a, b
// are the correct type.
template<class T>
bool vtkDICOMValue::ValueT<T>::Compare(const Value *a, const Value *b)
{
  bool r = true;
  unsigned int n = a->VL/sizeof(T);
  if (n != 0)
    {
    const T *ap = static_cast<const ValueT<T> *>(a)->Data;
    const T *bp = static_cast<const ValueT<T> *>(b)->Data;
    do { r &= (*ap++ == *bp++); } while (r && --n);
    }
  return r;
}

template<>
bool vtkDICOMValue::ValueT<vtkDICOMItem>::Compare(
  const Value *a, const Value *b)
{
  bool r = true;
  unsigned int n = a->NumberOfValues; // do not use VL/sizeof()
  if (n != 0)
    {
    const vtkDICOMItem *ap =
      static_cast<const ValueT<vtkDICOMItem> *>(a)->Data;
    const vtkDICOMItem *bp =
      static_cast<const ValueT<vtkDICOMItem> *>(b)->Data;
    do { r &= (*ap++ == *bp++); } while (r && --n);
    }
  return r;
}

template<>
bool vtkDICOMValue::ValueT<vtkDICOMValue>::Compare(
  const Value *a, const Value *b)
{
  bool r = true;
  unsigned int n = a->NumberOfValues; // do not use VL/sizeof()
  if (n != 0)
    {
    const vtkDICOMValue *ap =
      static_cast<const ValueT<vtkDICOMValue> *>(a)->Data;
    const vtkDICOMValue *bp =
      static_cast<const ValueT<vtkDICOMValue> *>(b)->Data;
    do { r &= (*ap++ == *bp++); } while (r && --n);
    }
  return r;
}

//----------------------------------------------------------------------------
bool vtkDICOMValue::operator==(const vtkDICOMValue& o) const
{
  const vtkDICOMValue::Value *a = this->V;
  const vtkDICOMValue::Value *b = o.V;
  bool r = true;

  if (a != b)
    {
    r = false;
    if (a != 0 && b != 0)
      {
      if (a->VR == b->VR && a->VL == b->VL && a->Type == b->Type &&
          a->NumberOfValues == b->NumberOfValues)
        {
        r = true;
        switch (a->Type)
          {
          case VTK_CHAR:
          case VTK_UNSIGNED_CHAR:
            r = ValueT<char>::Compare(a, b);
            break;
          case VTK_SHORT:
          case VTK_UNSIGNED_SHORT:
            r = ValueT<short>::Compare(a, b);
            break;
          case VTK_INT:
          case VTK_UNSIGNED_INT:
            r = ValueT<int>::Compare(a, b);
            break;
          case VTK_FLOAT:
            r = ValueT<float>::Compare(a, b);
            break;
          case VTK_DOUBLE:
            r = ValueT<double>::Compare(a, b);
            break;
          case VTK_DICOM_ITEM:
            r = ValueT<vtkDICOMItem>::Compare(a, b);
            break;
          case VTK_DICOM_VALUE:
            r = ValueT<vtkDICOMValue>::Compare(a, b);
            break;
          }
        }
      }
    }

  return r;
}

//----------------------------------------------------------------------------
ostream& operator<<(ostream& os, const vtkDICOMValue& v)
{
  vtkDICOMVR vr = v.GetVR();
  const char *cp = v.GetCharData();

  if (!v.IsValid())
    {
    os << "empty[0]";
    }
  else if (vr == vtkDICOMVR::UN)
    {
    os << "unknown[" << v.GetNumberOfValues() << "]";
    }
  else if (vr == vtkDICOMVR::ST ||
           vr == vtkDICOMVR::LT ||
           vr == vtkDICOMVR::UT)
    {
    // might have control characters, don't print it
    os << "text[" << v.GetVL() << "]";
    }
  else if (cp)
    {
    const char *dp = cp + v.GetVL();
    while (cp != dp && *cp == ' ') { cp++; }
    while (cp != dp && dp[-1] == ' ') { dp--; }
    if ((cp != dp && dp[-1] == '\0') || *dp == '\0')
      {
      os << cp;
      }
    else
      {
      os << std::string(cp,dp);
      }
    }
  else if (vr == vtkDICOMVR::AT)
    {
    const unsigned short *usp = v.GetUnsignedShortData();
    unsigned int m = v.GetNumberOfValues();
    if (usp)
      {
      for (unsigned int j = 0; j < m; j += 2)
        {
        vtkDICOMTag t(usp[j], usp[j+1]);
        if (j > 0) { os << ","; }
        os << t;
        }
      }
    else
      {
      os << "tags[" << (m/2) << "]";
      }
    }
  else if (vr == vtkDICOMVR::SQ)
    {
    os << "items[" << v.GetNumberOfValues() << "]";
    }
  else if (vr == vtkDICOMVR::OB)
    {
    os << "bytes[" << v.GetNumberOfValues() << "]";
    }
  else if (vr == vtkDICOMVR::OW)
    {
    os << "words[" << v.GetNumberOfValues() << "]";
    }
  else if (vr == vtkDICOMVR::OF)
    {
    os << "floats[" << v.GetNumberOfValues() << "]";
    }
  else
    {
    const vtkDICOMValue *vp = v.GetMultiplexData();
    if (vp)
      {
      // value is a multiplex of per-instance values
      os << "values[" << v.GetNumberOfValues() << "]";
      }
    else
      {
      std::string s;
      unsigned int m = v.GetNumberOfValues();
      unsigned int n = (m <= 16 ? m : 16);
      for (unsigned int i = 0; i < n; i++)
        {
        s.append((i == 0 ? "" : ","));
        v.AppendValueToString(s, i);
        }
      if (m > n)
        {
        s.append(",...");
        }
      os << s;
      }
    }

  return os;
}
