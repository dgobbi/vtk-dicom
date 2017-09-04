/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMValue.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMUtilities.h"

#include <vtkMath.h>
#include <vtkTypeTraits.h>

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include <new>
#include <streambuf>
#include <limits>
#include <locale>

// For use by methods that must return an empty item
const vtkDICOMItem vtkDICOMValue::EmptyItem;

//----------------------------------------------------------------------------
// Use anonymous namespace to limit function scope to this file only
namespace {

// Cast an array of "n" values from type "IT" to type "OT".
template<class IT, class OT>
void NumericalConversion(IT *u, OT *v, size_t n)
{
  if (n != 0) { do { *v++ = static_cast<OT>(*u++); } while (--n); }
}

// Check for hexadecimal digits, plain ASCII (don't use locale)
bool IsHexDigit(char c)
{
  return ((c >= '0' && c <= '9') ||
          (c >= 'A' && c <= 'F') ||
          (c >= 'a' && c <= 'f'));
}

// Buffer for reading from character string
class InputString : public std::streambuf
{
public:
  InputString(const char *ccp, size_t l) {
    char *cp = const_cast<char *>(ccp);
    setg(cp, cp, cp+l);
  }
};

// Buffer for writing to a character string
class OutputString : public std::streambuf
{
public:
  OutputString(char *cp, size_t l) {
    setp(cp, cp+l);
  }
  size_t length() const { return pptr() - pbase(); }
  void adjust(int n) { pbump(n); }
};

// The input is a list of one or more numerical string values separated
// by backslashes, for example "1.23435\85234.0\2345.22".  Convert "n"
// values to type OT, starting at the "i"th backslash-separated value.
template<class OT>
void StringConversion(
  const char *cp, vtkDICOMVR vr, OT *v, size_t i, size_t n)
{
  if (vr == vtkDICOMVR::IS || vr == vtkDICOMVR::DS)
  {
    // create a stream for conversion with "C" locale
    InputString sb(cp, strlen(cp));
    std::istream sbs(&sb);
    sbs.imbue(std::locale::classic());

    for (size_t j = 0; j < i && !sbs.eof(); j++)
    {
      sbs.ignore(std::numeric_limits<std::streamsize>::max(), '\\');
    }

    for (size_t k = 0; k < n && !sbs.eof(); k++)
    {
      if (vr == vtkDICOMVR::DS)
      {
        double d = 0.0;
        sbs >> d;
        *v++ = static_cast<OT>(d);
      }
      else
      {
        int d = 0;
        sbs >> d;
        *v++ = static_cast<OT>(d);
      }
      if (k + 1 < n)
      {
        sbs.ignore(std::numeric_limits<std::streamsize>::max(), '\\');
      }
    }
  }
  else if (n > 0)
  {
    do { *v++ = 0; } while (--n);
  }
}

// specialize conversion for vtkDICOMTag
void StringConversionAT(const char *cp, vtkDICOMTag *v, size_t n)
{
  for (size_t k = 0; k < n && *cp != '\0'; k++)
  {
    unsigned short tag[2] = { 0, 0 };
    for (int j = 0; j < 2; j++)
    {
      while (!IsHexDigit(*cp) && *cp != '\\' && *cp != '\0')  { cp++; }
      for (int i = 0; i < 4; i++)
      {
        unsigned short d;
        if (*cp >= '0' && *cp <= '9') { d = *cp - '0'; }
        else if (*cp >= 'A' && *cp <= 'F') { d = *cp - ('A' - 10); }
        else if (*cp >= 'a' && *cp <= 'f') { d = *cp - ('a' - 10); }
        else { break; }
        tag[j] = tag[j]*16 + d;
        cp++;
      }
    }
    *v++ = vtkDICOMTag(tag[0], tag[1]);

    bool bk = false;
    do
    {
      bk = (*cp == '\\');
      cp++;
    }
    while (!bk && *cp != '\0');
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

#ifdef VTK_DICOM_USE_OVERFLOW_BYTE
#define OVERFLOW_BYTE(vn) static_cast<unsigned char>(vn >> 32)
#else
#define OVERFLOW_BYTE(vn) 0
#endif

//----------------------------------------------------------------------------
// Construct a numerical value.
template<class T>
vtkDICOMValue::ValueT<T>::ValueT(vtkDICOMVR vr, size_t vn)
{
  this->Type = static_cast<unsigned char>(vtkTypeTraits<T>::VTKTypeID());
  this->CharacterSet = 0;
  this->Overflow = OVERFLOW_BYTE(vn);
  this->VR = vr;
  this->VL = static_cast<unsigned int>(vn*sizeof(T));
  this->NumberOfValues = static_cast<unsigned int>(vn);
}

// Construct a string value.
template<>
vtkDICOMValue::ValueT<char>::ValueT(vtkDICOMVR vr, size_t vn)
{
  vn += (vn & 1); // pad VL to make it even
  this->Type = VTK_CHAR;
  this->CharacterSet = 0;
  this->Overflow = OVERFLOW_BYTE(vn);
  this->VR = vr;
  this->VL = static_cast<unsigned int>(vn);
  this->NumberOfValues = (vn > 0);
}

// Construct a "bytes" value.
template<>
vtkDICOMValue::ValueT<unsigned char>::ValueT(vtkDICOMVR vr, size_t vn)
{
  this->Type = VTK_UNSIGNED_CHAR;
  this->CharacterSet = 0;
  this->Overflow = OVERFLOW_BYTE(vn);
  this->VR = vr;
  // pad VL to make it even
  this->VL = static_cast<unsigned int>(vn + (vn & 1));
  this->NumberOfValues = static_cast<unsigned int>(vn);
}

// Construct a list of attribute tags.
template<>
vtkDICOMValue::ValueT<vtkDICOMTag>::ValueT(vtkDICOMVR vr, size_t vn)
{
  this->Type = VTK_DICOM_TAG;
  this->CharacterSet = 0;
  this->Overflow = OVERFLOW_BYTE(vn);
  this->VR = vr;
  this->VL = static_cast<unsigned int>(4*vn);
  this->NumberOfValues = static_cast<unsigned int>(vn);
  vtkDICOMTag *dp = this->Data;
  for (size_t i = 0; i < vn; i++)
  {
    // call constructor manually with placement new
    new(dp) vtkDICOMTag();
    dp++;
  }
}

// Construct a sequence of items.
template<>
vtkDICOMValue::ValueT<vtkDICOMItem>::ValueT(vtkDICOMVR vr, size_t vn)
{
  this->Type = VTK_DICOM_ITEM;
  this->CharacterSet = 0;
  this->Overflow = OVERFLOW_BYTE(vn);
  this->VR = vr; // better be SQ
  this->VL = 0;
  this->NumberOfValues = static_cast<unsigned int>(vn);
  vtkDICOMItem *dp = this->Data;
  for (size_t i = 0; i < vn; i++)
  {
    // call constructor manually with placement new
    new(dp) vtkDICOMItem();
    dp++;
  }
}

// Construct a list of values.
template<>
vtkDICOMValue::ValueT<vtkDICOMValue>::ValueT(vtkDICOMVR vr, size_t vn)
{
  this->Type = VTK_DICOM_VALUE;
  this->CharacterSet = 0;
  this->Overflow = OVERFLOW_BYTE(vn);
  this->VR = vr;
  this->VL = 0;
  this->NumberOfValues = static_cast<unsigned int>(vn);
  vtkDICOMValue *dp = this->Data;
  for (size_t i = 0; i < vn; i++)
  {
    // call constructor manually with placement new
    new(dp) vtkDICOMValue();
    dp++;
  }
}

//----------------------------------------------------------------------------
vtkDICOMValue::vtkDICOMValue(const vtkDICOMSequence &s)
{
  this->V = s.V.V;
  if (this->V) { ++(this->V->ReferenceCount); }
}

vtkDICOMValue& vtkDICOMValue::operator=(const vtkDICOMSequence& o)
{
  *this = o.V;
  return *this;
}

template<class T>
T *vtkDICOMValue::Allocate(vtkDICOMVR vr, size_t vn)
{
  this->Clear();
  // Use C++ "placement new" to allocate a single block of memory that
  // includes both the Value struct and the array of values.
  size_t n = vn + !vn; // add one if zero
  void *vp = ValueMalloc(sizeof(Value) + n*sizeof(T));
  ValueT<T> *v = new(vp) ValueT<T>(vr, vn);
  // Test the assumption that Data is at an offset of sizeof(Value)
  assert(static_cast<char *>(static_cast<void *>(v->Data)) ==
         static_cast<char *>(vp) + sizeof(Value));
  this->V = v;
  return v->Data;
}

template<>
unsigned char *vtkDICOMValue::Allocate(vtkDICOMVR vr, size_t vn)
{
  this->Clear();
  // Use C++ "placement new" to allocate a single block of memory that
  // includes both the Value struct and the array of values.
  size_t n = vn + !vn; // add one if zero
  void *vp = ValueMalloc(sizeof(Value) + n);
  ValueT<unsigned char> *v = new(vp) ValueT<unsigned char>(vr, vn);
  // Test the assumption that Data is at an offset of sizeof(Value)
  assert(static_cast<char *>(static_cast<void *>(v->Data)) ==
         static_cast<char *>(vp) + sizeof(Value));
  this->V = v;
  return v->Data;
}

template<>
char *vtkDICOMValue::Allocate<char>(vtkDICOMVR vr, size_t vn)
{
  this->Clear();
  // Strings of any type other than UI will be padded with spaces to
  // give an even number of chars.  All strings (including UI) need one
  // extra char for the null terminator to make them valid C strings.
  size_t pad = (vn & static_cast<size_t>(vr != vtkDICOMVR::UI));
  // Use C++ "placement new" to allocate a single block of memory that
  // includes both the Value struct and the array of values.
  void *vp = ValueMalloc(sizeof(Value) + vn + pad + 1);
  ValueT<char> *v = new(vp) ValueT<char>(vr, vn);
  // Test the assumption that Data is at an offset of sizeof(Value)
  assert(v->Data == static_cast<char *>(vp) + sizeof(Value));
  this->V = v;
  return v->Data;
}

char *vtkDICOMValue::AllocateCharData(vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<char>(vr, vn);
}

char *vtkDICOMValue::AllocateCharData(
  vtkDICOMVR vr, vtkDICOMCharacterSet cs, size_t vn)
{
  char *data = this->Allocate<char>(vr, vn);
  if (vr.HasSpecificCharacterSet() && this->V)
  {
    this->V->CharacterSet = cs.GetKey();
  }
  return data;
}

unsigned char *vtkDICOMValue::AllocateUnsignedCharData(
  vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<unsigned char>(vr, vn);
}

short *vtkDICOMValue::AllocateShortData(vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<short>(vr, vn);
}

unsigned short *vtkDICOMValue::AllocateUnsignedShortData(
  vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<unsigned short>(vr, vn);
}

int *vtkDICOMValue::AllocateIntData(vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<int>(vr, vn);
}

unsigned int *vtkDICOMValue::AllocateUnsignedIntData(
  vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<unsigned int>(vr, vn);
}

float *vtkDICOMValue::AllocateFloatData(vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<float>(vr, vn);
}

double *vtkDICOMValue::AllocateDoubleData(vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<double>(vr, vn);
}

vtkDICOMTag *vtkDICOMValue::AllocateTagData(
  vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<vtkDICOMTag>(vr, vn);
}

vtkDICOMItem *vtkDICOMValue::AllocateSequenceData(
  vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<vtkDICOMItem>(vr, vn);
}

vtkDICOMValue *vtkDICOMValue::AllocateMultiplexData(
  vtkDICOMVR vr, size_t vn)
{
  return this->Allocate<vtkDICOMValue>(vr, vn);
}

//----------------------------------------------------------------------------
void vtkDICOMValue::ComputeNumberOfValuesForCharData()
{
  if (this->V && this->V->Type == VTK_CHAR)
  {
    if (this->V->VL == 0)
    {
      this->V->NumberOfValues = 0;
    }
    else if (this->V->VR.HasSingleValue())
    {
      this->V->NumberOfValues = 1;
    }
    else
    {
      const char *ptr = static_cast<const ValueT<char> *>(this->V)->Data;
      unsigned int n = 1;
      size_t vl = this->V->VL;
      if (this->V->CharacterSet == 0)
      {
        do { n += (*ptr++ == '\\'); } while (--vl);
      }
      else
      {
        vtkDICOMCharacterSet cs = this->GetCharacterSet();
        n += cs.CountBackslashes(ptr, vl);
      }
      this->V->NumberOfValues = n;
    }
  }
}

//----------------------------------------------------------------------------
unsigned char *vtkDICOMValue::ReallocateUnsignedCharData(size_t vn)
{
  assert(this->V != 0);
  assert(this->V->VR == vtkDICOMVR::OB || this->V->VR == vtkDICOMVR::UN);
  assert(vn < 0xffffffffu);

  size_t n = this->GetNumberOfValues();
  unsigned char *ptr =
    static_cast<ValueT<unsigned char> *>(this->V)->Data;

  Value *v = this->V;
  const unsigned char *cptr = ptr;

  // increment ref count before reallocating
  ++(v->ReferenceCount);
  ptr = this->AllocateUnsignedCharData(v->VR, vn);
  n = (n < vn ? n : vn);
  if (n > 0) { memcpy(ptr, cptr, n); }
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
void vtkDICOMValue::CreateValue(vtkDICOMVR vr, const T *data, size_t n)
{
  typedef vtkDICOMVR VR; // shorthand

  assert(n*sizeof(T) < 0xffffffffu);
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
    OutputString sb(cp, 17*n);
    std::ostream sbs(&sb);
    sbs.imbue(std::locale::classic());
    sbs.precision(10);

    for (size_t i = 0; i < n; i++)
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
      else if (fabs(d) < 1e-99 || vtkMath::IsNan(d))
      {
        d = 0.0;
      }
      sbs << d;
      size_t dl = sb.length();
      // look for superfluous leading zero on 3-digit exponent,
      // this occurs for MSVC prior to MSVC 2015, and possibly
      // for compilers that mimic MSVC behavior
      if (dl >= 5 && (cp[dl-5] == 'e' || cp[dl-5] =='E') &&
          cp[dl-3] == '0' &&
          cp[dl-2] >= '0' && cp[dl-2] <= '9' &&
          cp[dl-1] >= '0' && cp[dl-1] <= '9')
      {
        cp[dl-3] = cp[dl-2];
        cp[dl-2] = cp[dl-1];
        sb.adjust(-1);
      }
      if (i + 1 < n) { sbs.put('\\'); }
    }

    // pad to even length and terminate
    if (sb.length() & 1) { sbs.put(' '); }
    sbs.put('\0');
    this->V->NumberOfValues = static_cast<unsigned int>(n);
    this->V->VL = static_cast<unsigned int>(sb.length()-1);
  }
  else if (vr == VR::IS)
  {
    char *cp = this->AllocateCharData(vr, 13*n);
    OutputString sb(cp, 13*n);
    std::ostream sbs(&sb);
    sbs.imbue(std::locale::classic());

    for (size_t i = 0; i < n; i++)
    {
      sbs << static_cast<int>(data[i]);;
      if (i + 1 < n) { sbs.put('\\'); }
    }

    // pad to even length and terminate
    if (sb.length() & 1) { sbs.put(' '); }
    sbs.put('\0');
    this->V->NumberOfValues = static_cast<unsigned int>(n);
    this->V->VL = static_cast<unsigned int>(sb.length()-1);
  }
  else if (vr == VR::OB || vr == VR::UN)
  {
    size_t m = n*sizeof(T);
    int pad = (m & 1);
    unsigned char *ptr = this->AllocateUnsignedCharData(vr, m + pad);
    memcpy(ptr, data, m);
    if (pad) { ptr[m] = 0; } // pad to even
    this->V->NumberOfValues = static_cast<unsigned int>(m);
  }
  else if (vr == VR::OW)
  {
    if (vt == VTK_SHORT)
    {
      short *ptr = this->AllocateShortData(vr, n);
      memcpy(ptr, data, n*2);
    }
    else
    {
      unsigned short *ptr = this->AllocateUnsignedShortData(vr, n*sizeof(T)/2);
      memcpy(ptr, data, n*sizeof(T));
    }
  }
  else if (vr == VR::OL)
  {
    if (vt == VTK_INT)
    {
      int *ptr = this->AllocateIntData(vr, n);
      memcpy(ptr, data, n*4);
    }
    else
    {
      unsigned int *ptr = this->AllocateUnsignedIntData(vr, n*sizeof(T)/4);
      memcpy(ptr, data, n*sizeof(T));
    }
  }
  else if (vr == VR::OF)
  {
    float *ptr = this->AllocateFloatData(vr, n*sizeof(T)/4);
    memcpy(ptr, data, n*sizeof(T));
  }
  else if (vr == VR::OD)
  {
    double *ptr = this->AllocateDoubleData(vr, n*sizeof(T)/8);
    memcpy(ptr, data, n*sizeof(T));
  }
  else if (vr == VR::AT)
  {
    if (sizeof(T) > 2)
    {
      // subsequent values represent 32-bit keys
      vtkDICOMTag *ptr = this->AllocateTagData(vr, n);
      for (size_t i = 0; i < n; i++)
      {
        unsigned int k = static_cast<unsigned int>(data[i]);
        unsigned short g = static_cast<unsigned short>(k >> 16);
        unsigned short e = static_cast<unsigned short>(k);
        ptr[i] = vtkDICOMTag(g,e);
      }
    }
    else
    {
      // subsequent values represent group,element pairs
      vtkDICOMTag *ptr = this->AllocateTagData(vr, n/2);
      for (size_t i = 0; i < n; i += 2)
      {
        unsigned short g = static_cast<unsigned short>(data[i]);
        unsigned short e = static_cast<unsigned short>(data[i+1]);
        ptr[i/2] = vtkDICOMTag(g,e);
      }
    }
  }
}

template<>
void vtkDICOMValue::CreateValue<vtkDICOMTag>(
  vtkDICOMVR vr, const vtkDICOMTag *data, size_t n)
{
  typedef vtkDICOMVR VR; // shorthand

  assert(n*4 < 0xffffffffu);

  this->V = 0;

  if (vr == VR::AT)
  {
    vtkDICOMTag *ptr = this->AllocateTagData(vr, n);
    for (size_t i = 0; i < n; i++)
    {
      ptr[i] = data[i];
    }
  }
}

template<>
void vtkDICOMValue::CreateValue<vtkDICOMItem>(
  vtkDICOMVR vr, const vtkDICOMItem *data, size_t n)
{
  typedef vtkDICOMVR VR; // shorthand

  assert(n*4 < 0xffffffffu);

  this->V = 0;

  if (vr == VR::SQ)
  {
    vtkDICOMItem *ptr = this->AllocateSequenceData(vr, n);
    for (size_t i = 0; i < n; i++)
    {
      ptr[i] = data[i];
    }
  }
}

template<>
void vtkDICOMValue::CreateValue<char>(
  vtkDICOMVR vr, const char *data, size_t m)
{
  typedef vtkDICOMVR VR;

  assert(m < 0xffffffffu);

  this->V = 0;

  // directly copy data into these VRs without conversion
  if (vr.HasSingleValue())
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
    unsigned short *ptr = this->AllocateUnsignedShortData(vr, m/2);
    memcpy(ptr, data, m);
  }
  else if (vr == VR::OL)
  {
    unsigned int *ptr = this->AllocateUnsignedIntData(vr, m/4);
    memcpy(ptr, data, m);
  }
  else if (vr == VR::OF)
  {
    float *ptr = this->AllocateFloatData(vr, m/4);
    memcpy(ptr, data, m);
  }
  else if (vr == VR::OD)
  {
    double *ptr = this->AllocateDoubleData(vr, m/8);
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

  if (this->V)
  {
    return;
  }

  // count the number of backslash-separated values
  size_t n = (m > 0);
  for (size_t i = 0; i < m; i++)
  {
    n += (data[i] == '\\');
  }

  // convert input string to the specified VR
  if (vr.HasTextValue())
  {
    int pad = (m & 1);
    char *cp = this->AllocateCharData(vr, m);
    strncpy(cp, data, m);
    // if not UI, then pad to even length with a space
    if (pad && vr != VR::UI) { cp[m++] = ' '; }
    cp[m] = '\0';
    this->V->NumberOfValues = static_cast<unsigned int>(n);
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
  else if (vr == VR::AT)
  {
    vtkDICOMTag *ptr = this->AllocateTagData(vr, n);
    StringConversionAT(data, ptr, n);
  }
}

//----------------------------------------------------------------------------
// Constructor methods call the factory to create the right internal type.
vtkDICOMValue::vtkDICOMValue(vtkDICOMVR vr, double v)
{
  this->CreateValue(vr, &v, 1);
}

vtkDICOMValue::vtkDICOMValue(vtkDICOMVR vr, const std::string& v)
{
  this->CreateValue(vr, v.data(), v.size());
}

vtkDICOMValue::vtkDICOMValue(vtkDICOMVR vr, vtkDICOMTag v)
{
  this->CreateValue(vr, &v, 1);
}

vtkDICOMValue::vtkDICOMValue(vtkDICOMTag v)
{
  this->CreateValue(vtkDICOMVR::AT, &v, 1);
}

vtkDICOMValue::vtkDICOMValue(vtkDICOMVR vr, const vtkDICOMItem& v)
{
  this->CreateValue(vr, &v, 1);
}

vtkDICOMValue::vtkDICOMValue(const vtkDICOMItem& v)
{
  this->CreateValue(vtkDICOMVR::SQ, &v, 1);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const char *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const unsigned char *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const short *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const unsigned short *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const int *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const unsigned int *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const float *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const double *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const vtkDICOMTag *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, const vtkDICOMItem *data, size_t count)
{
  this->CreateValue(vr, data, count);
}

//----------------------------------------------------------------------------
void vtkDICOMValue::CreateValueWithSpecificCharacterSet(
  vtkDICOMVR vr, vtkDICOMCharacterSet cs, const char *data, size_t l)
{
  this->CreateValue(vr, data, l);
  if (vr.HasSpecificCharacterSet() && this->V)
  {
    this->V->CharacterSet = cs.GetKey();
    // character set might change interpretation of backslashes
    if (l > 0 && !vr.HasSingleValue())
    {
      this->ComputeNumberOfValuesForCharData();
    }
  }
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, vtkDICOMCharacterSet cs, const char *data, size_t l)
{
  this->CreateValueWithSpecificCharacterSet(vr, cs, data, l);
}

vtkDICOMValue::vtkDICOMValue(
  vtkDICOMVR vr, vtkDICOMCharacterSet cs, const std::string& v)
{
  this->CreateValueWithSpecificCharacterSet(vr, cs, v.data(), v.size());
}

//----------------------------------------------------------------------------
size_t vtkDICOMValue::CreateValueFromUTF8(
  vtkDICOMVR vr, vtkDICOMCharacterSet cs, const char *text, size_t l)
{
  if (vr.HasSpecificCharacterSet())
  {
    std::string s;
    if (vr.HasSingleValue())
    {
      s = cs.FromUTF8(text, l, &l);
    }
    else
    {
      // convert each value separately
      const char *cp = text;
      const char *ep = cp + l;
      while (cp != ep && *cp != '\0')
      {
        const char *dp = cp;
        if (vr == vtkDICOMVR::PN)
        {
          for (; dp != ep && *cp != '\0'; dp++)
          {
            if (*dp == '\\' || *dp == '=' || *dp == '^') { break; }
          }
        }
        else
        {
          for (; dp != ep && *cp != '\0'; dp++)
          {
            if (*dp == '\\') { break; }
          }
        }
        size_t n = dp - cp;
        if (n > 0)
        {
          size_t i;
          size_t j = s.length();
          s.append(cs.FromUTF8(cp, n, &i));
          if (i < n)
          {
            // an encoding error occurred, record 1st occurrence
            i += cp - text;
            l = (i > l) ? l : i;
          }
          size_t k = s.length();
          while (j < k)
          {
            // it is an error for conversion to add a backslash
            j += cs.NextBackslash(&s[j], &s[k]);
            if (j < k && s[j] == '\\')
            {
              s[j] = '?'; // remove the backslash
              l = (j > l) ? l : j;
              j++;
            }
          }
          cp += n;
        }
        if (cp != ep && *cp != '\0')
        {
          s.append(cp, 1);
          cp++;
        }
      }
    }

    this->CreateValueWithSpecificCharacterSet(vr, cs, s.data(), s.size());
    return l;
  }

  char checkAscii = 0;
  for (size_t i = 0; i < l; i++)
  {
    checkAscii |= text[i];
  }

  if ((checkAscii & 0x80) != 0)
  {
    vtkDICOMCharacterSet csa(vtkDICOMCharacterSet::ISO_IR_6);
    std::string s = csa.FromUTF8(text, l, &l);
    this->CreateValue(vr, s.data(), s.size());
    return l;
  }

  this->CreateValue(vr, text, l);
  return l;
}

vtkDICOMValue vtkDICOMValue::FromUTF8String(
    vtkDICOMVR vr, vtkDICOMCharacterSet cs, const std::string& s)
{
  vtkDICOMValue v;
  v.CreateValueFromUTF8(vr, cs, s.data(), s.length());
  return v;
}

//----------------------------------------------------------------------------
vtkDICOMValue::vtkDICOMValue(vtkDICOMVR vr)
{
  typedef vtkDICOMVR VR;

  this->V = 0;

  if (vr.HasTextValue())
  {
    this->AllocateCharData(vr, 0);
  }
  else if (vr == VR::OW || vr == VR::OX)
  {
    this->AllocateUnsignedShortData(VR::OW, 0);
  }
  else if (vr == VR::OF || vr == VR::FL)
  {
    this->AllocateFloatData(vr, 0);
  }
  else if (vr == VR::OD || vr == VR::FD)
  {
    this->AllocateDoubleData(vr, 0);
  }
  else if (vr == VR::OB || vr == VR::UN)
  {
    this->AllocateUnsignedCharData(vr, 0);
  }
  else if (vr == VR::OL || vr == VR::UL)
  {
    this->AllocateUnsignedIntData(vr, 0);
  }
  else if (vr == VR::SL)
  {
    this->AllocateIntData(vr, 0);
  }
  else if (vr == VR::US)
  {
    this->AllocateUnsignedShortData(vr, 0);
  }
  else if (vr == VR::SS || vr == VR::XS)
  {
    this->AllocateShortData(VR::SS, 0);
  }
  else if (vr == VR::AT)
  {
    this->AllocateTagData(vr, 0);
  }
  else if (vr == VR::SQ)
  {
    this->AllocateSequenceData(vr, 0);
  }
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
      for (size_t i = 0; i < v->NumberOfValues; i++)
      {
        // placement new was used, so destructor must be called manually
        dp->~vtkDICOMItem();
        dp++;
      }
    }
    else if (v->Type == VTK_DICOM_VALUE)
    {
      vtkDICOMValue *dp = static_cast<ValueT<vtkDICOMValue> *>(v)->Data;
      for (size_t i = 0; i < v->NumberOfValues; i++)
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
template<class T>
void vtkDICOMValue::AppendInit(vtkDICOMVR vr)
{
  this->Clear();
  this->Allocate<T>(vr, 2);
  // mark as empty but growable
  this->V->NumberOfValues = 0;
  this->V->VL = 0xffffffff;
}

template void vtkDICOMValue::AppendInit<vtkDICOMItem>(vtkDICOMVR vr);

//----------------------------------------------------------------------------
template<class T>
void vtkDICOMValue::AppendValue(const T &item)
{
  // do nothing if not initialized yet
  if (this->V == 0)
  {
    return;
  }

  T *ptr = static_cast<vtkDICOMValue::ValueT<T> *>(this->V)->Data;

  size_t n = this->V->NumberOfValues;
  size_t nn = 0;
  // reallocate if not unique reference, or not yet growable
  if (this->V->ReferenceCount != 1 || this->V->VL != 0xffffffff)
  {
    // get next power of two that is greater than n
    nn = 1;
    do { nn <<= 1; } while (nn <= n);
  }
  // reallocate if n is a power of two
  else if (n > 1 && ((n - 1) & n) == 0)
  {
    nn = 2*n;
  }
  // reallocate the array
  if (nn != 0)
  {
    vtkDICOMValue::Value *v = this->V;
    ++(v->ReferenceCount);
    const T *cptr = ptr;
    ptr = this->Allocate<T>(v->VR, nn);
    this->V->NumberOfValues = static_cast<unsigned int>(n);
    for (size_t i = 0; i < n; i++)
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

template void vtkDICOMValue::AppendValue<vtkDICOMItem>(
  const vtkDICOMItem& item);

//----------------------------------------------------------------------------
template<class T>
void vtkDICOMValue::SetValue(size_t i, const T &item)
{
  assert(this->V != 0);
  assert(i < this->V->NumberOfValues);

  T *ptr = static_cast<vtkDICOMValue::ValueT<T> *>(this->V)->Data;

  // reallocate the array if we aren't the sole owner
  assert(this->V->ReferenceCount == 1);
  if (this->V->ReferenceCount != 1)
  {
    size_t m = this->V->NumberOfValues;
    const T *cptr = ptr;
    ptr = this->Allocate<T>(this->V->VR, m);
    for (size_t j = 0; j < m; j++)
    {
      ptr[j] = cptr[j];
    }
  }

  ptr[i] = item;
}

template void vtkDICOMValue::SetValue<vtkDICOMItem>(
  size_t i, const vtkDICOMItem& item);

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
  if (this->V)
  {
    if (this->V->Type == VTK_INT)
    {
      ptr = static_cast<const ValueT<int> *>(this->V)->Data;
    }
    else if (this->V->Type == VTK_UNSIGNED_INT &&
             this->V->VR == vtkDICOMVR::OL)
    {
      ptr = reinterpret_cast<const int *>(
        static_cast<const ValueT<unsigned int> *>(this->V)->Data);
    }
  }
  return ptr;
}

const unsigned int *vtkDICOMValue::GetUnsignedIntData() const
{
  const unsigned int *ptr = 0;
  if (this->V)
  {
    if (this->V->Type == VTK_UNSIGNED_INT)
    {
      ptr = static_cast<const ValueT<unsigned int> *>(this->V)->Data;
    }
    else if (this->V->Type == VTK_INT &&
             this->V->VR == vtkDICOMVR::OL)
    {
      ptr = reinterpret_cast<const unsigned int *>(
        static_cast<const ValueT<int> *>(this->V)->Data);
    }
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

const vtkDICOMTag *vtkDICOMValue::GetTagData() const
{
  const vtkDICOMTag *ptr = 0;
  if (this->V && this->V->Type == VTK_DICOM_TAG)
  {
    ptr = static_cast<const ValueT<vtkDICOMTag> *>(this->V)->Data;
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

vtkDICOMValue *vtkDICOMValue::GetMultiplex()
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
void vtkDICOMValue::GetValuesT(VT *v, size_t c, size_t s) const
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
    case VTK_DICOM_TAG:
    {
      const vtkDICOMTag *tptr =
        static_cast<const ValueT<vtkDICOMTag> *>(this->V)->Data + s;
      for (size_t i = 0; i < c; i += 2)
      {
        v[i] = tptr[i/2].GetGroup();
        v[i+1] = tptr[i/2].GetElement();
      }
    }
      break;
  }
}

template<>
void vtkDICOMValue::GetValuesT<std::string>(
  std::string *v, size_t c, size_t s) const
{
  for (size_t i = 0; i < c; i++)
  {
    v->clear();
    this->AppendValueToString(*v++, s++);
  }
}

template<>
void vtkDICOMValue::GetValuesT<vtkDICOMTag>(
  vtkDICOMTag *v, size_t c, size_t s) const
{
  if (this->V->Type == VTK_DICOM_TAG)
  {
    const vtkDICOMTag *ptr =
      static_cast<const ValueT<vtkDICOMTag> *>(this->V)->Data + s;
    for (size_t i = 0; i < c; i++)
    {
      *v++ = *ptr++;
    }
  }
}

//----------------------------------------------------------------------------
// These are interface methods that call the templated internal methods.
void vtkDICOMValue::GetValues(unsigned char *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(short *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(unsigned short *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(int *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(unsigned int *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(float *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(double *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(std::string *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

void vtkDICOMValue::GetValues(vtkDICOMTag *v, size_t c, size_t s) const
{
  assert((s + c) <= this->V->NumberOfValues);
  this->GetValuesT(v, c, s);
}

//----------------------------------------------------------------------------
unsigned char vtkDICOMValue::GetUnsignedChar(size_t i) const
{
  unsigned char v = 0;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

short vtkDICOMValue::GetShort(size_t i) const
{
  short v = 0;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

unsigned short vtkDICOMValue::GetUnsignedShort(size_t i) const
{
  unsigned short v = 0;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

int vtkDICOMValue::GetInt(size_t i) const
{
  int v = 0;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

unsigned int vtkDICOMValue::GetUnsignedInt(size_t i) const
{
  unsigned int v = 0;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

float vtkDICOMValue::GetFloat(size_t i) const
{
  float v = 0.0;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

double vtkDICOMValue::GetDouble(size_t i) const
{
  double v = 0.0;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

std::string vtkDICOMValue::GetUTF8String(size_t i) const
{
  if (this->V && this->V->CharacterSet != 0)
  {
    if (this->V && i < this->V->NumberOfValues)
    {
      std::string v;
      this->AppendValueToUTF8String(v, i);
      return v;
    }
  }

  return this->GetString(i);
}

std::string vtkDICOMValue::GetString(size_t i) const
{
  std::string v;
  if (this->V && i < this->V->NumberOfValues)
  {
    this->AppendValueToString(v, i);
  }
  return v;
}

vtkDICOMTag vtkDICOMValue::GetTag(size_t i) const
{
  vtkDICOMTag v;
  if (this->V && this->V->VR == vtkDICOMVR::AT &&
      i < this->V->NumberOfValues)
  {
    this->GetValuesT(&v, 1, i);
  }
  return v;
}

const vtkDICOMItem& vtkDICOMValue::GetItem(size_t i) const
{
  if (this->V && this->V->Type == VTK_DICOM_ITEM &&
      i < this->V->NumberOfValues)
  {
    const vtkDICOMItem *ptr =
      static_cast<const ValueT<vtkDICOMItem> *>(this->V)->Data;
    return ptr[i];
  }
  return vtkDICOMValue::EmptyItem;
}

//----------------------------------------------------------------------------
unsigned char vtkDICOMValue::AsUnsignedChar() const
{
  unsigned char v = 0;
  if (this->V && this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

short vtkDICOMValue::AsShort() const
{
  short v = 0;
  if (this->V && this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

unsigned short vtkDICOMValue::AsUnsignedShort() const
{
  unsigned short v = 0;
  if (this->V && this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

int vtkDICOMValue::AsInt() const
{
  int v = 0;
  if (this->V && this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

unsigned int vtkDICOMValue::AsUnsignedInt() const
{
  unsigned int v = 0;
  if (this->V && this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

float vtkDICOMValue::AsFloat() const
{
  float v = 0.0;
  if (this->V && this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

double vtkDICOMValue::AsDouble() const
{
  double v = 0.0;
  if (this->V && this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

std::string vtkDICOMValue::AsUTF8String() const
{
  const char *cp = this->GetCharData();
  if (cp)
  {
    vtkDICOMCharacterSet cs(this->V->CharacterSet);
    size_t l = this->V->VL;
    while (l > 0 && cp[l-1] == '\0') { l--; }
    if (this->V->VR.HasSingleValue())
    {
      while (l > 0 && cp[l-1] == ' ') { l--; }
      return cs.ToUTF8(cp, l);
    }
    else
    {
      // convert each value separately
      const char *ep = cp + l;
      std::string s;
      while (cp != ep && *cp != '\0')
      {
        size_t n = cs.NextBackslash(cp, ep);
        while (n > 0 && *cp == ' ') { cp++; n--; }
        size_t m = n;
        while (m > 0 && cp[m-1] == ' ') { m--; }
        s.append(cs.ToUTF8(cp, m));
        cp += n;
        if (cp != ep && *cp == '\\')
        {
          s.append(cp, 1);
          cp++;
        }
      }
      return s;
    }
  }

  return this->AsString();
}

std::string vtkDICOMValue::AsString() const
{
  const char *cp = this->GetCharData();
  if (cp)
  {
    size_t l = this->V->VL;
    while (l > 0 && cp[l-1] == '\0') { l--; }
    if (this->V->VR.HasSingleValue())
    {
      while (l > 0 && cp[l-1] == ' ') { l--; }
      return std::string(cp, l);
    }
    else
    {
      // convert each value separately
      vtkDICOMCharacterSet cs(this->V->CharacterSet);
      const char *ep = cp + l;
      std::string s;
      while (cp != ep && *cp != '\0')
      {
        size_t n = cs.NextBackslash(cp, ep);
        while (n > 0 && *cp == ' ') { cp++; n--; }
        size_t m = n;
        while (m > 0 && cp[m-1] == ' ') { m--; }
        s.append(cp, m);
        cp += n;
        if (cp != ep && *cp == '\\')
        {
          s.append(cp, 1);
          cp++;
        }
      }
      return s;
    }
  }

  std::string v;
  if (this->V && this->V->VR != vtkDICOMVR::UN &&
      this->V->VR != vtkDICOMVR::SQ &&
      this->V->VR != vtkDICOMVR::OW &&
      this->V->VR != vtkDICOMVR::OB &&
      this->V->VR != vtkDICOMVR::OL &&
      this->V->VR != vtkDICOMVR::OF &&
      this->V->VR != vtkDICOMVR::OD)
  {
    size_t n = this->V->NumberOfValues;
    for (size_t i = 0; i < n; i++)
    {
      if (i > 0)
      {
        v.append("\\");
      }
      this->AppendValueToString(v, i);
    }
  }
  return v;
}

vtkDICOMTag vtkDICOMValue::AsTag() const
{
  vtkDICOMTag v;
  if (this->V && this->V->VR == vtkDICOMVR::AT &&
      this->V->NumberOfValues >= 1)
  {
    this->GetValuesT(&v, 1, 0);
  }
  return v;
}

const vtkDICOMItem& vtkDICOMValue::AsItem() const
{
  return this->GetItem(0);
}

//----------------------------------------------------------------------------
// Get one of the backslash-separated substrings, requires a text value.
void vtkDICOMValue::Substring(
  size_t i, const char *&start, const char *&end) const
{
  const char *cp = static_cast<const ValueT<char> *>(this->V)->Data;
  const char *ep = cp + this->V->VL;

  // remove any trailing NULLs for UI values
  while (ep != cp && ep[-1] == '\0') { --ep; }
  const char *dp = ep;

  if (this->V->NumberOfValues > 1 && ++i > 0)
  {
    if (this->V->CharacterSet == 0)
    {
      dp = cp - 1;
      do
      {
        cp = dp + 1;
        do { dp++; } while (*dp != '\\' && dp != ep);
      }
      while (--i != 0 && dp != ep);
    }
    else
    {
      vtkDICOMCharacterSet cs(this->V->CharacterSet);
      for (;;)
      {
        dp = cp + cs.NextBackslash(cp, ep);
        if (--i == 0 || *dp != '\\') { break; }
        cp = dp + 1;
      }
    }
  }

  // remove any spaces used as padding
  if (!this->V->VR.HasSingleValue())
  {
    while (cp != dp && cp[0] == ' ') { cp++; }
  }
  while (cp != dp && dp[-1] == ' ') { dp--; }

  start = cp;
  end = dp;
}

//----------------------------------------------------------------------------
void vtkDICOMValue::AppendValueToSafeUTF8String(
  std::string& str, size_t i) const
{
  if (this->V && this->V->Type == VTK_CHAR)
  {
    const char *cp = static_cast<const ValueT<char> *>(this->V)->Data;
    size_t l = this->V->VL;
    if (this->V->VR.HasSingleValue())
    {
      while (l > 0 && cp[l-1] == '\0') { l--; }
      while (l > 0 && cp[l-1] == ' ') { l--; }
    }
    else
    {
      const char *dp;
      this->Substring(i, cp, dp);
      l = dp - cp;
    }
    vtkDICOMCharacterSet cs(this->V->CharacterSet);
    str += cs.ToSafeUTF8(cp, l);
  }
  else
  {
    this->AppendValueToString(str, i);
  }
}

//----------------------------------------------------------------------------
void vtkDICOMValue::AppendValueToUTF8String(
  std::string& str, size_t i) const
{
  if (this->V && this->V->Type == VTK_CHAR &&
      this->V->CharacterSet != 0)
  {
    const char *cp = static_cast<const ValueT<char> *>(this->V)->Data;
    size_t l = this->V->VL;
    if (this->V->VR.HasSingleValue())
    {
      while (l > 0 && cp[l-1] == '\0') { l--; }
      while (l > 0 && cp[l-1] == ' ') { l--; }
    }
    else
    {
      const char *dp;
      this->Substring(i, cp, dp);
      l = dp - cp;
    }
    vtkDICOMCharacterSet cs(this->V->CharacterSet);
    str += cs.ToUTF8(cp, l);
  }
  else
  {
    this->AppendValueToString(str, i);
  }
}

//----------------------------------------------------------------------------
// Convert one value to text and add it to the supplied string
void vtkDICOMValue::AppendValueToString(
  std::string& str, size_t i) const
{
  const char *cp = 0;
  const char *dp = 0;
  double f = 0.0;
  int d = 0;
  size_t u = 0;
  vtkDICOMTag a;

  if (this->V == 0)
  {
    return;
  }

  assert(i < this->V->NumberOfValues);

  switch (this->V->Type)
  {
    case VTK_CHAR:
      cp = static_cast<const ValueT<char> *>(this->V)->Data;
      dp = cp + (i == 0 ? this->V->VL : 0);
      if (this->V->VR.HasSingleValue())
      {
        // strip trailing spaces
        while (dp != cp && dp[-1] == '\0') { --dp; }
        while (dp != cp && dp[-1] == ' ') { --dp; }
      }
      else
      {
        // get just one of the values, strip leading & trailing spaces
        this->Substring(i, cp, dp);
      }
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
    case VTK_DICOM_TAG:
      a = static_cast<const ValueT<vtkDICOMTag> *>(this->V)->Data[i];
      break;
  }

  if (this->V->Type == VTK_CHAR)
  {
    while (cp != dp && dp[-1] == '\0') { --dp; }
    str.append(cp, dp);
  }
  else if (this->V->Type == VTK_FLOAT ||
           this->V->Type == VTK_DOUBLE)
  {
    // force consistent printing of "inf", "nan" regardless of platform
    if (vtkMath::IsNan(f))
    {
      str.append("nan");
    }
    else if (vtkMath::IsInf(f))
    {
      str.append((f < 0) ? "-inf" : "inf");
    }
    else
    {
      // create a stream that uses the "C" locale
      char text[32];
      OutputString sb(text, sizeof(text));
      std::ostream sbs(&sb);
      sbs.imbue(std::locale::classic());

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
          sbs.precision(16);
        }
        else
        {
          sbs.precision(8);
        }
      }
      else
      {
        sbs.setf(std::ios::scientific);

        if (this->V->Type == VTK_DOUBLE)
        {
          sbs.precision(15);
        }
        else
        {
          sbs.precision(7);
        }
      }

      // write the value
      sbs << f;
      size_t l = sb.length();

      if (l > 0)
      {
        // make sure there is a decimal point
        size_t tk = (text[0] == '-' || text[0] == '+');
        while (tk < l)
        {
          if (text[tk] < '0' || text[tk] > '9') { break; }
          tk++;
        }
        if (tk == l)
        {
          text[l++] = '.';
        }

        // make sure there is a zero after the decimal point
        if (text[l-1] == '.')
        {
          text[l++] = '0';
        }
      }

      // trim trailing zeros, except the one following decimal point
      size_t ti = 0;
      while (ti < l && text[ti] != 'e') { ti++; }
      size_t tj = ti;
      while (tj > 1 && text[tj-1] == '0' && text[tj-2] != '.') { tj--; }
      while (ti < l) { text[tj++] = text[ti++]; }
      l = tj;

      // if exponent has three digits, clear the first if it is zero
      if (l >= 5 && text[l-5] == 'e' && text[l-3] == '0')
      {
        text[l-3] = text[l-2];
        text[l-2] = text[l-1];
        l--;
      }

      str.append(text, l);
    }
  }
  else if (this->V->Type == VTK_UNSIGNED_CHAR ||
           this->V->Type == VTK_SHORT ||
           this->V->Type == VTK_UNSIGNED_SHORT ||
           this->V->Type == VTK_INT ||
           this->V->Type == VTK_UNSIGNED_INT)
  {
    // simple code to convert an integer to a string
    char text[16];
    size_t ti = 16;

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
  else if (this->V->Type == VTK_DICOM_TAG)
  {
    char text[12];
    int t[2];
    t[0] = a.GetGroup();
    t[1] = a.GetElement();
    char *tp = text;
    *tp++ = '(';
    for (int j = 0; j < 2; j++)
    {
      for (int k = 12; k >= 0; k -= 4)
      {
        char c = ((t[j] >> k) & 0x000F);
        *tp++ = (c < 10 ? '0' + c : 'A' - 10 + c);
      }
      *tp++ = ',';
    }
    tp[-1] = ')';
    *tp = '\0';
    str.append(text, &text[11]);
  }
}

//----------------------------------------------------------------------------
// These compare functions can only be safely used within "operator=="
// and "Matches()" because they require a pre-check that VL matches
// and that a, b are the correct type.
template<class T>
bool vtkDICOMValue::ValueT<T>::Compare(const Value *a, const Value *b)
{
  bool r = (a->VL == b->VL);
  size_t n = a->VL/sizeof(T);
  if (n != 0 && r)
  {
    const T *ap = static_cast<const ValueT<T> *>(a)->Data;
    const T *bp = static_cast<const ValueT<T> *>(b)->Data;
    do { r &= (*ap++ == *bp++); } while (r && --n);
  }
  return r;
}

template<>
bool vtkDICOMValue::ValueT<char>::Compare(
  const Value *a, const Value *b)
{
  bool r = (a->VL == b->VL);
  r &= (a->CharacterSet == b->CharacterSet);
  size_t n = a->VL;
  if (n != 0 && r)
  {
    const unsigned char *ap =
      static_cast<const ValueT<unsigned char> *>(a)->Data;
    const unsigned char *bp =
      static_cast<const ValueT<unsigned char> *>(b)->Data;
    do { r &= (*ap++ == *bp++); } while (r && --n);
  }
  return r;
}

template<>
bool vtkDICOMValue::ValueT<unsigned char>::Compare(
  const Value *a, const Value *b)
{
  bool r = (a->VL == b->VL);
  size_t n = a->VL;
  if (a->VL == 0xFFFFFFFF)
  {
    n = a->NumberOfValues;
    r &= (n == b->NumberOfValues);
#ifdef VTK_DICOM_USE_OVERFLOW_BYTE
    n += (static_cast<size_t>(a->Overflow) << 32);
    r &= (a->Overflow == b->Overflow);
#endif
  }
  if (n != 0 && r)
  {
    const unsigned char *ap =
      static_cast<const ValueT<unsigned char> *>(a)->Data;
    const unsigned char *bp =
      static_cast<const ValueT<unsigned char> *>(b)->Data;
    do { r &= (*ap++ == *bp++); } while (r && --n);
  }
  return r;
}

template<>
bool vtkDICOMValue::ValueT<vtkDICOMItem>::Compare(
  const Value *a, const Value *b)
{
  size_t n = a->NumberOfValues; // do not use VL/sizeof()
  bool r = (n == b->NumberOfValues);
  if (n != 0 && r)
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
  size_t n = a->NumberOfValues; // do not use VL/sizeof()
  bool r = (n == b->NumberOfValues);
  if (n != 0 && r)
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
// This CompareEach template is more limited than the Compare template:
// it can only be used for SS, US, SL, UL, FL, FD.  Its purpose it to
// support the Matches() method, and it shouldn't be used anywhere else.
template<class T>
bool vtkDICOMValue::ValueT<T>::CompareEach(const Value *a, const Value *b)
{
  bool r = true;
  if (a->NumberOfValues > 0 && b->NumberOfValues > 0)
  {
    size_t n = a->NumberOfValues;
    size_t mm = b->NumberOfValues;
    const T *ap = static_cast<const ValueT<T> *>(a)->Data;
    const T *bbp = static_cast<const ValueT<T> *>(b)->Data;
    do
    {
      size_t m = mm;
      const T *bp = bbp;
      do
      {
        r = (*ap == *bp);
        bp++;
      }
      while (--m && !r);
      if (r)
      {
        // set new start for inner loop
        bbp = bp;
        mm = m;
        if (mm == 0)
        {
          r = (n == 1);
          break;
        }
      }
      ap++;
    }
    while (--n && r);
  }

  return r;
}

//----------------------------------------------------------------------------
bool vtkDICOMValue::PatternMatchesMulti(
    const char *pattern, const char *val, vtkDICOMVR vr)
{
  typedef vtkDICOMVR VR;
  bool inclusive = (vr == VR::UI);
  bool ordered = (vr == VR::IS || vr == VR::DS);
  bool nowildcards = (vr == VR::UI || vr == VR::AS ||
                      vr == VR::IS || vr == VR::DS);
  bool match = !inclusive;

  const char *pp = pattern;
  while (match ^ inclusive)
  {
    // get pattern value start and end
    const char *pd = pp;
    while (*pd != '\0' && *pd != '\\') { pd++; }
    const char *pf = pd;
    // strip spaces
    while (*pp == ' ') { pp++; }
    while (pf != pp && pf[-1] == ' ') { --pf; }

    match = false;
    const char *vp = val;
    while (!match)
    {
      // get value start and end
      const char *vd = vp;
      while (*vd != '\0' && *vd != '\\') { vd++; }
      const char *vf = vd;
      // strip whitespace
      while (*vp == ' ') { vp++; }
      while (vf != vp && vf[-1] == ' ') { --vf; }

      if (nowildcards)
      {
        // if VR doesn't allow wildcards, use simple string comparison
        // (start at back, because UIDs often share the same prefix).
        const char *cf = pf;
        match = (pf-pp == vf-vp);
        while (match && cf != pp)
        {
          match = (*(--vf) == *(--cf));
        }
      }
      else
      {
        // use wildcard pattern matching
        match = vtkDICOMUtilities::PatternMatches(pp, pf-pp, vp, vf-vp);
      }

      // break if no values remain
      if (*vd == '\0') { break; }
      vp = vd + 1;
    }
    if (match && ordered)
    {
      // set inner loop start to current position
      val = vp;
    }

    // break if no patterns remain
    if (*pd == '\0') { break; }
    pp = pd + 1;
  }

  return match;
}

//----------------------------------------------------------------------------
bool vtkDICOMValue::PatternMatchesPersonName(
    const char *pattern, const char *val)
{
  bool match = false;

  char normalizedPattern[256];
  char normalizedName[256];

  const char *pp = pattern;
  while (!match)
  {
    // normalize the pattern
    vtkDICOMValue::NormalizePersonName(pp, normalizedPattern, true);

    const char *vp = val;
    while (!match)
    {
      // normalize the name
      vtkDICOMValue::NormalizePersonName(vp, normalizedName);

      match = vtkDICOMUtilities::PatternMatches(
        normalizedPattern, strlen(normalizedPattern),
        normalizedName, strlen(normalizedName));

      // break if no values remain
      while (*vp != '\0' && *vp != '\\') { vp++; }
      if (*vp == '\0') { break; }
      vp++;
    }

    // break if no patterns remain
    while (*pp != '\0' && *pp != '\\') { pp++; }
    if (*pp == '\0') { break; }
    pp++;
  }

  return match;
}

//----------------------------------------------------------------------------
void vtkDICOMValue::NormalizePersonName(
  const char *input, char output[256], bool isquery)
{
  // this normalizes a PN so that it consists of three component groups
  // of five components each

  const char *cp = input;
  char *dp = output;

  // loop over component groups
  for (int i = 0; i < 3; i++)
  {
    // set maximum length of extended component group to 85 bytes
    // (because 85*3 + 1 == 256, and 85 > 64 where 64 is max for PN)
    char *groupStart = dp;
    char *ep = dp + 85;

    // loop over components
    for (int j = 0; j < 5; j++)
    {
      // save start location
      char *componentStart = dp;
      // copy characters
      while (*cp != '^' && *cp != '=' && *cp != '\\' &&
             *cp != '\0' && dp != ep)
      {
        *dp++ = *cp++;
      }

      // strip trailing spaces and periods
      while (dp != componentStart && (dp[-1] == ' ' || dp[-1] == '.'))
      {
        --dp;
      }

      if (dp != ep)
      {
        // if query, replace empty components with wildcard
        if (isquery && dp == componentStart) { *dp++ = '*'; }

        // mark end of component
        if (j != 4) { *dp++ = '^'; }
      }
      else if (isquery && dp != componentStart)
      {
        // back up by one unicode code point, replace with wildcard
        do { --dp; } while (dp != componentStart && (*dp & 0xC0) == 0x80);
        *dp++ = '*';
      }

      // go to next component of input
      if (*cp == '^') { cp++; }
    }

    // collapse repeated wildcards
    if (isquery)
    {
      while (dp - groupStart > 2 && dp[-3] == '*' &&
             dp[-2] == '^' && dp[-1] == '*')
      {
        dp -= 2;
      }
    }

    // mark end of component group
    if (i != 2) { *dp++ = '='; }

    // go to next component group of input
    if (*cp == '=') { cp++; }
  }

  // collapse repeated wildcards
  if (isquery)
  {
    while (dp - output > 2 && dp[-3] == '*' &&
           dp[-2] == '=' && dp[-1] == '*')
    {
      dp -= 2;
    }
  }

  // terminate
  *dp = '\0';
}

//----------------------------------------------------------------------------
size_t vtkDICOMValue::NormalizeDateTime(
  const char *input, char output[22], vtkDICOMVR vr)
{
  // if the value is DT and has a timezone offset, we ignore it,
  // because timezone adjustment is only done if it is negotiated
  // as part of the query, otherwise timezones are ignored

  // use UNIX epoch as our arbitrary time base
  static const char epoch[22] = "19700101000000.000000";
  for (int i = 0; i < 22; i++)
  {
    output[i] = epoch[i];
  }

  char *tp = output;
  if (vr == vtkDICOMVR::TM)
  {
    tp += 8;
  }

  const char *cp = input;
  while (*tp != 0 && *cp >= '0' && *cp <= '9')
  {
    *tp++ = *cp++;
  }
  if (*tp == '.' && *cp == '.')
  {
    *tp++ = *cp++;
    while (*tp != 0 && *cp >= '0' && *cp <= '9')
    {
      *tp++ = *cp++;
    }
  }

  return static_cast<size_t>(tp - output);
}

//----------------------------------------------------------------------------
bool vtkDICOMValue::Matches(const vtkDICOMValue& value) const
{
  /* Attribute matching:
  1) Single Value Matching
  2) List of UID Matching (match if any UIDs in query list match)
  3) Universal Matching (if query value is empty)
  4) Wild Card Matching (with * and ?)
  5) Range Matching (range of dates or times)
  6) Sequence Matching (match if any items in sequence match)

  Notes:
  - Encoded strings should be converted to UTF8
  - PN matches should be case-insensitive, ideally normalized
  - All other queries are case-sensitive
  - List can be used for more than just UIDs
  - Numeric value comparisons can be templated
  */

  // keys with no value match (universal matching)
  if (value.V == 0)
  {
    return true;
  }
  if (value.V->Type != VTK_DICOM_ITEM)
  {
    // for everything but sequences, check if the length is zero
    if (value.V->VL == 0)
    {
      return true;
    }
  }
  else if (value.GetNumberOfValues() == 0 ||
           static_cast<const ValueT<vtkDICOMItem> *>(value.V)->Data
             ->GetNumberOfDataElements() == 0)
  {
    // empty sequences match
    return true;
  }

  if (this->V == 0 || this->V->VR != value.V->VR)
  {
    // match is impossible if VRs differ
    return false;
  }

  bool match = false;
  vtkDICOMVR vr = this->V->VR;
  int type = this->V->Type;

  // First, do comparisons for string values
  if (type == VTK_CHAR)
  {
    // Does the pattern string have wildcards?
    bool wildcard = false;
    const char *pattern = static_cast<const ValueT<char> *>(value.V)->Data;
    size_t pl = 0;
    while (pattern[pl] != '\0' && pl < value.V->VL)
    {
      char c = pattern[pl++];
      wildcard |= (c == '*');
      wildcard |= (c == '?');
    }
    while (pl > 0 && pattern[pl-1] == ' ') { pl--; }

    // Get string value and remove any trailing nulls and spaces
    const char *cp = static_cast<const ValueT<char> *>(this->V)->Data;
    size_t l = this->V->VL;
    while (l > 0 && cp[l-1] == '\0') { l--; }
    while (l > 0 && cp[l-1] == ' ') { l--; }

    if (!wildcard &&
        (vr == vtkDICOMVR::DA ||
         vr == vtkDICOMVR::TM ||
         vr == vtkDICOMVR::DT))
    {
      // Find the position of the hyphen
      size_t hp = 0;
      while (hp < pl && pattern[hp] != '-') { hp++; }
      if (vr == vtkDICOMVR::DT && hp + 5 < pl)
      {
        // Check if the hyphen was part of the timezone offset
        if (pattern[hp+5] == '-')
        {
          hp += 5;
        }
        else if (hp != 4 && pattern[hp+5] == '\0')
        {
          hp = 0;
        }
      }
      // Get a pointer to the part of pattern after the hyphen
      const char *dp = &pattern[hp];
      bool hyphen = (*dp == '-');
      dp += hyphen;

      // Normalize the dates/times and compare
      char r1[22], r2[22], d[22];
      size_t n1 = 0;
      size_t n2 = 0;
      vtkDICOMValue::NormalizeDateTime(cp, d, vr);
      r1[0] = '\0';
      if (pattern[0] != '\0' && pattern[0] != '-')
      {
        n1 = vtkDICOMValue::NormalizeDateTime(pattern, r1, vr);
      }
      r2[0] = '\0';
      if (dp[0] != '\0' && dp[0] != '-')
      {
        n2 = vtkDICOMValue::NormalizeDateTime(dp, r2, vr);
      }

      // Perform lexical comparison on normalized datetime
      if (!hyphen)
      {
        match = (strncmp(d, r1, n1) == 0);
      }
      else if (*r1 != '\0')
      {
        match = (strncmp(d, r1, n1) >= 0);
      }
      else if (*r2 != '\0')
      {
        match = (strncmp(r2, d, n2) >= 0);
      }
      else
      {
        match = (strncmp(r2, d, n2) >= 0 && strncmp(d, r1, n1) >= 0);
      }
    }
    else
    {
      // Perform wildcard matching and list matching
      std::string str;
      std::string pstr;
      if (vr == vtkDICOMVR::PN)
      {
        // Convert to lowercase UTF8 before matching
        vtkDICOMCharacterSet cs = this->GetCharacterSet();
        const char *ep = cp + l;
        while (cp != ep && *cp != '\0')
        {
          size_t n = cs.NextBackslash(cp, ep);
          str.append(cs.CaseFoldedUTF8(cp, n));
          cp += n;
          if (cp != ep && *cp == '\\')
          {
            str.append(cp, 1);
            cp++;
          }
        }
        cp = str.c_str();
        l = str.length();
        pstr = value.GetCharacterSet().CaseFoldedUTF8(pattern, pl);
        pattern = pstr.c_str();
        pl = pstr.length();
      }
      else if (vr.HasSpecificCharacterSet())
      {
        // Convert value and pattern to UTF8 before matching
        str = this->AsUTF8String();
        cp = str.c_str();
        l = str.length();
        pstr = value.AsUTF8String();
        pattern = pstr.c_str();
        pl = pstr.length();
      }

      if (vr == vtkDICOMVR::PN)
      {
        match = vtkDICOMValue::PatternMatchesPersonName(pattern, cp);
      }
      else if (vr.HasSingleValue())
      {
        match = vtkDICOMUtilities::PatternMatches(pattern, pl, cp, l);
      }
      else
      {
        match = vtkDICOMValue::PatternMatchesMulti(pattern, cp, vr);
      }
    }
  }
  else if (type == VTK_DICOM_VALUE)
  {
    // Match if any of the contained values match
    vtkDICOMValue *vp = static_cast<ValueT<vtkDICOMValue> *>(this->V)->Data;
    size_t vn = this->GetNumberOfValues();
    for (size_t i = 0; i < vn && !match; i++)
    {
      match = vp->Matches(value);
      vp++;
    }
  }
  else if (type == VTK_DICOM_ITEM)
  {
    // Match if any item matches
    vtkDICOMItem *item = static_cast<ValueT<vtkDICOMItem> *>(value.V)->Data;
    vtkDICOMItem *ip = static_cast<ValueT<vtkDICOMItem> *>(this->V)->Data;
    size_t n = this->GetNumberOfValues();
    for (size_t i = 0; i < n && !match; i++)
    {
      vtkDICOMDataElementIterator iter = item->Begin();
      vtkDICOMDataElementIterator iterEnd = item->End();
      match = true;
      while (match && iter != iterEnd)
      {
        vtkDICOMTag tag = iter->GetTag();
        // The SpecificCharacterSet is always considered to match.  Its
        // presence in the query describes the character encoding of the
        // query, so that query strings can be converted to utf-8 at the
        // point of comparison with the data set strings.
        if (tag != DC::SpecificCharacterSet)
        {
          match = ip->Get(tag).Matches(iter->GetValue());
        }
        ++iter;
      }
      ip++;
    }
  }
  else if (type == VTK_DICOM_TAG)
  {
    // Comparing tags between data sets should just always return "true"
    match = true;
  }
  else if (vr == vtkDICOMVR::OB || vr == vtkDICOMVR::UN)
  {
    // OB and UN must match exactly
    match = ValueT<unsigned char>::Compare(value.V, this->V);
  }
  else if (vr == vtkDICOMVR::OW)
  {
    // OW must match exactly
    match = ValueT<unsigned short>::Compare(value.V, this->V);
  }
  else if (vr == vtkDICOMVR::OL)
  {
    // OL must match exactly
    match = ValueT<unsigned int>::Compare(value.V, this->V);
  }
  else if (vr == vtkDICOMVR::OF)
  {
    // OF must match exactly
    match = ValueT<float>::Compare(value.V, this->V);
  }
  else if (vr == vtkDICOMVR::OD)
  {
    // OF must match exactly
    match = ValueT<double>::Compare(value.V, this->V);
  }
  else if (type == VTK_SHORT || type == VTK_UNSIGNED_SHORT)
  {
    // Match if any value matches
    match = ValueT<short>::CompareEach(value.V, this->V);
  }
  else if (type == VTK_INT || type == VTK_UNSIGNED_INT)
  {
    // Match if any value matches
    match = ValueT<int>::CompareEach(value.V, this->V);
  }
  else if (type == VTK_FLOAT)
  {
    // Match if any value matches
    match = ValueT<float>::CompareEach(value.V, this->V);
  }
  else if (type == VTK_DOUBLE)
  {
    // Match if any value matches
    match = ValueT<double>::CompareEach(value.V, this->V);
  }

  return match;
}

//----------------------------------------------------------------------------
bool vtkDICOMValue::Matches(const std::string& value) const
{
  if (value.length() == 0)
  {
    // to support universal matching
    return true;
  }

  if (this->V)
  {
    if (this->V->VR.HasTextValue())
    {
      return this->Matches(vtkDICOMValue(
        this->V->VR, this->V->CharacterSet, value));
    }
    else
    {
      vtkDICOMValue v(this->V->VR, value);
      return (v.AsString() == value && this->Matches(v));
    }
  }

  return false;
}

//----------------------------------------------------------------------------
bool vtkDICOMValue::Matches(double value) const
{
  if (this->V && this->V->VL > 0 && this->V->VR.HasNumericValue())
  {
    vtkDICOMValue v(this->V->VR, value);
    return (v.AsDouble() == value && this->Matches(v));
  }

  return false;
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
      if (a->VR == b->VR && a->VL == b->VL && a->Type == b->Type)
      {
        r = true;
        switch (a->Type)
        {
          case VTK_CHAR:
            r = ValueT<char>::Compare(a, b);
            break;
          case VTK_UNSIGNED_CHAR:
            r = ValueT<unsigned char>::Compare(a, b);
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
  const vtkDICOMValue *vp = v.GetMultiplexData();
  size_t m = v.GetNumberOfValues();

  if (!v.IsValid())
  {
    os << "empty[0]";
  }
  else if (vp)
  {
    // value is a multiplex of per-instance values
    os << "values[" << m << "]";
  }
  else if (vr == vtkDICOMVR::UN)
  {
    os << "unknown[" << m << "]";
  }
  else if (vr == vtkDICOMVR::ST ||
           vr == vtkDICOMVR::LT ||
           vr == vtkDICOMVR::UT)
  {
    // might have control characters, don't print it
    os << "text[" << v.GetVL() << "]";
  }
  else if (cp && !vr.HasSpecificCharacterSet())
  {
    const char *dp = cp + v.GetVL();
    while (cp != dp && *cp == ' ') { cp++; }
    while (cp != dp && dp[-1] == ' ') { dp--; }
    if (cp != dp)
    {
      if (dp[-1] == '\0' || *dp == '\0')
      {
        os << cp;
      }
      else
      {
        std::string s = std::string(cp, dp);
        os << s.c_str();
      }
    }
  }
  else if (vr == vtkDICOMVR::AT)
  {
    const vtkDICOMTag *tp = v.GetTagData();
    if (tp)
    {
      for (size_t j = 0; j < m; j++)
      {
        if (j > 0) { os << ","; }
        os << tp[j];
      }
    }
    else
    {
      os << "tags[" << m << "]";
    }
  }
  else if (vr == vtkDICOMVR::SQ)
  {
    os << "items[" << m << "]";
  }
  else if (vr == vtkDICOMVR::OB)
  {
    os << "bytes[" << m << "]";
  }
  else if (vr == vtkDICOMVR::OW)
  {
    os << "words[" << m << "]";
  }
  else if (vr == vtkDICOMVR::OL)
  {
    os << "longwords[" << m << "]";
  }
  else if (vr == vtkDICOMVR::OF)
  {
    os << "floats[" << m << "]";
  }
  else if (vr == vtkDICOMVR::OD)
  {
    os << "doubles[" << m << "]";
  }
  else
  {
    std::string s;
    size_t n = (m <= 16 ? m : 16);
    for (size_t i = 0; i < n; i++)
    {
      s.append((i == 0 ? "" : ","));
      v.AppendValueToSafeUTF8String(s, i);
    }
    if (m > n)
    {
      s.append(",...");
    }
    os << s.c_str();
  }

  return os;
}
