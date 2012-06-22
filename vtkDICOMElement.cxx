#include "vtkDICOMElement.h"

#include <vtkTypeTraits.h>

#include <math.h>
#include <stdlib.h>
#include <assert.h>

//----------------------------------------------------------------------------
//! Implementation class, templated over the internal array type.
/*!
 *  The real purpose of this class is to avoid the use of void
 *  pointers to store the data.
 */
template<class T>
class vtkDICOMElementT : public vtkDICOMElement
{
public:
  //! Get the data array.
  T *GetData() { return this->Data; };
  const T *GetData() const { return this->Data; };

  //! Copy values from the internal array, convert if necessary.
  template<class OT>
  void GetValues(OT *v, vtkIdType start, vtkIdType count) const;

protected:
  vtkDICOMElementT() {}
  T *Data;

private:
  vtkDICOMElementT(const vtkDICOMElementT&);
  void operator=(const vtkDICOMElementT&);
};

//----------------------------------------------------------------------------
//! Implementation class, templated over type and internal size.
/*!
 *  If only a few values need to be stored, this class makes it
 *  possible to store them directly in the element, instead of
 *  allocating an array.  The code that creates the elements
 *  (at the end of this file) sets N such that QuickData is 24
 *  bytes in length: 24 chars, 12 shorts, 6 ints, 3 doubles.
 */
template<class T, int N>
class vtkDICOMElementTN : public vtkDICOMElementT<T>
{
public:
  vtkDICOMElementTN(vtkDICOMTag tag, vtkDICOMVR vr,
                    const T *data, vtkIdType n);

protected:
  vtkDICOMElementTN() {};

  T QuickData[N];

private:
  vtkDICOMElementTN(const vtkDICOMElementTN&);
  void operator=(const vtkDICOMElementTN&);
};

//----------------------------------------------------------------------------
// Element destructor, does its own run-time type checking.
// To make the elements lightweight, the destructor is non-virtual.
// This means that it is necessary to check the Type so that the
// correct information can be freed.  The constructor guarantees
// that Type is always set correctly.
vtkDICOMElement::~vtkDICOMElement()
{
  if (this->NeedsFree)
    {
    switch (this->Type)
      {
      case VTK_CHAR:
        delete [] static_cast<vtkDICOMElementT<char> *>(
          this)->GetData();
        break;
      case VTK_UNSIGNED_CHAR:
        delete [] static_cast<vtkDICOMElementT<unsigned char> *>(
          this)->GetData();
        break;
      case VTK_SHORT:
        delete [] static_cast<vtkDICOMElementT<short> *>(
          this)->GetData();
        break;
      case VTK_UNSIGNED_SHORT:
        delete [] static_cast<vtkDICOMElementT<unsigned short> *>(
          this)->GetData();
        break;
      case VTK_INT:
        delete [] static_cast<vtkDICOMElementT<int> *>(
          this)->GetData();
        break;
      case VTK_UNSIGNED_INT:
        delete [] static_cast<vtkDICOMElementT<unsigned int> *>(
          this)->GetData();
        break;
      case VTK_FLOAT:
        delete [] static_cast<vtkDICOMElementT<float> *>(
          this)->GetData();
        break;
      case VTK_DOUBLE:
        delete [] static_cast<vtkDICOMElementT<double> *>(
          this)->GetData();
        break;
      default:
        if (this->VR == vtkDICOMVR::SQ)
          {
          vtkDICOMElement **sq =
            static_cast<vtkDICOMElementT<vtkDICOMElement *> *>(
               this)->GetData();

          vtkIdType n = this->GetNumberOfValues();
          for (vtkIdType i = 0; i < n; i++)
            {
            delete sq[i];
            }
          delete [] sq;
          }
        break;
      }
    }
}

//----------------------------------------------------------------------------
// Return char pointer if char data, else return null pointer
const char *vtkDICOMElement::GetStringData() const
{
  const char *s = NULL;

  if (this->Type == VTK_CHAR)
    {
    s = static_cast<const vtkDICOMElementT<char> *>(this)->GetData();
    }

  return s;
}

//----------------------------------------------------------------------------
// Delegate to subclass to get values from the data array
template<class VT>
void vtkDICOMElement::GetValuesT(VT *v, vtkIdType s, vtkIdType c) const
{
  switch (this->Type)
    {
    case VTK_CHAR:
      static_cast<const vtkDICOMElementT<char> *>(
        this)->GetValues(v, s, c);
      break;
    case VTK_UNSIGNED_CHAR:
      static_cast<const vtkDICOMElementT<unsigned char> *>(
        this)->GetValues(v, s, c);
      break;
    case VTK_SHORT:
      static_cast<const vtkDICOMElementT<short> *>(
        this)->GetValues(v, s, c);
      break;
    case VTK_UNSIGNED_SHORT:
      static_cast<const vtkDICOMElementT<unsigned short> *>(
        this)->GetValues(v, s, c);
      break;
    case VTK_INT:
      static_cast<const vtkDICOMElementT<int> *>(
        this)->GetValues(v, s, c);
      break;
    case VTK_UNSIGNED_INT:
      static_cast<const vtkDICOMElementT<unsigned int> *>(
        this)->GetValues(v, s, c);
      break;
    case VTK_FLOAT:
      static_cast<const vtkDICOMElementT<float> *>(
        this)->GetValues(v, s, c);
      break;
    case VTK_DOUBLE:
      static_cast<const vtkDICOMElementT<double> *>(
        this)->GetValues(v, s, c);
      break;
    }
}

//----------------------------------------------------------------------------
// Call templated methods with non-templated methods.
// This is done simply to avoid having any templated methods as
// part of the interface, because templated interface methods
// cause problems for wrapping.
void vtkDICOMElement::GetValues(
  unsigned char *v, vtkIdType s, vtkIdType c) const
{
  this->GetValuesT(v, s, c);
}

void vtkDICOMElement::GetValues(
  short *v, vtkIdType s, vtkIdType c) const
{
  this->GetValuesT(v, s, c);
}

void vtkDICOMElement::GetValues(
  unsigned short *v, vtkIdType s, vtkIdType c) const
{
  this->GetValuesT(v, s, c);
}

void vtkDICOMElement::GetValues(
  int *v, vtkIdType s, vtkIdType c) const
{
  this->GetValuesT(v, s, c);
}

void vtkDICOMElement::GetValues(
  unsigned int *v, vtkIdType s, vtkIdType c) const
{
  this->GetValuesT(v, s, c);
}

void vtkDICOMElement::GetValues(
  float *v, vtkIdType s, vtkIdType c) const
{
  this->GetValuesT(v, s, c);
}

void vtkDICOMElement::GetValues(
  double *v, vtkIdType s, vtkIdType c) const
{
  this->GetValuesT(v, s, c);
}

//----------------------------------------------------------------------------
// Convenient, wrappable Get methods.
std::string vtkDICOMElement::GetValueAsString(vtkIdType i)
{
  std::string s;
  this->AppendValueToString(s, i);
  return s;
}

int vtkDICOMElement::GetValueAsInt(vtkIdType i)
{
  int v;
  this->GetValuesT(&v, i, 1);
  return v;
}

unsigned int vtkDICOMElement::GetValueAsUnsignedInt(vtkIdType i)
{
  unsigned int v;
  this->GetValuesT(&v, i, 1);
  return v;
}

double vtkDICOMElement::GetValueAsDouble(vtkIdType i)
{
  double v;
  this->GetValuesT(&v, i, 1);
  return v;
}

//----------------------------------------------------------------------------
// If an element is a sequence, get a sub-element from it.
vtkDICOMElement *vtkDICOMElement::GetSequenceItem(vtkIdType i)
{
  vtkDICOMElement *e = 0;

  if (i >= 0 && i < this->NumberOfValues &&
      (this->VR == vtkDICOMVR::SQ || this->VR == vtkDICOMVR::XQ))
    {
    e = static_cast<vtkDICOMElementT<vtkDICOMElement *> *>(
          this)->GetData()[i];
    }

  return e;
}

const vtkDICOMElement *vtkDICOMElement::GetSequenceItem(vtkIdType i) const
{
  const vtkDICOMElement *e = 0;

  if (i >= 0 && i < this->NumberOfValues &&
      (this->VR == vtkDICOMVR::SQ || this->VR == vtkDICOMVR::XQ))
    {
    e = static_cast<const vtkDICOMElementT<vtkDICOMElement *> *>(
          this)->GetData()[i];
    }

  return e;
}

//----------------------------------------------------------------------------
// DICOM strings use backslashes as value separators
void vtkDICOMElement::Substring(
  vtkIdType i, const char *&start, const char *&end) const
{
  const char *cp = static_cast<const vtkDICOMElementT<char> *>(
                     this)->GetData();

  const char *ep = cp + this->VL;
  const char *dp = ep;

  if (this->NumberOfValues > 1)
    {
    // if 'i' is not negative, find the 'i'th backslash-delimited string
    vtkIdType j = i + 1;
    if (j > 0)
      {
      const char *ncp = cp;
      dp = cp;
      do
        {
        cp = ncp;
        while (dp != ep && *dp != '\\')
          {
          dp++;
          }
        ncp = dp + 1;
        }
      while (--j != 0 && dp != ep);
      }
    }

  start = cp;
  end = dp;
}

//----------------------------------------------------------------------------
// Convert one value to text and add it to the supplied string
void vtkDICOMElement::AppendValueToString(std::string& str, vtkIdType i) const
{
  const char *cp = 0;
  const char *dp = 0;
  double f = 0.0;
  int d = 0;
  unsigned int u = 0;

  assert(i >= 0 && i < static_cast<vtkIdType>(this->NumberOfValues));

  switch (this->Type)
    {
    case VTK_CHAR:
      this->Substring(i, cp, dp);
      break;
    case VTK_UNSIGNED_CHAR:
      d = static_cast<const vtkDICOMElementT<unsigned char> *>(
            this)->GetData()[i];
      break;
    case VTK_SHORT:
      d = static_cast<const vtkDICOMElementT<short> *>(
            this)->GetData()[i];
      break;
    case VTK_UNSIGNED_SHORT:
      d = static_cast<const vtkDICOMElementT<unsigned short> *>(
            this)->GetData()[i];
      break;
    case VTK_INT:
      d = static_cast<const vtkDICOMElementT<int> *>(
            this)->GetData()[i];
      break;
    case VTK_UNSIGNED_INT:
      u = static_cast<const vtkDICOMElementT<unsigned int> *>(
            this)->GetData()[i];
      break;
    case VTK_FLOAT:
      f = static_cast<const vtkDICOMElementT<float> *>(
            this)->GetData()[i];
      break;
    case VTK_DOUBLE:
      f = static_cast<const vtkDICOMElementT<double> *>(
            this)->GetData()[i];
      break;
    }

  if (this->Type == VTK_CHAR)
    {
    str.append(cp, dp);
    }
  else if (this->Type == VTK_FLOAT || this->Type == VTK_DOUBLE)
    {
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
      // guard against printing non-existent digits:
      // use exponential form if printing in "%g" format
      // would print an integer that is too large for the
      // float to accurately represent.
      if ((this->Type == VTK_DOUBLE &&
           fabs(f) <= 9007199254740992.0) || // 2^53
          (this->Type == VTK_FLOAT &&
           fabs(f) <= 16777216.0)) // 2^24
        {
        if (this->Type == VTK_DOUBLE)
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
        if (this->Type == VTK_DOUBLE)
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
// Templated data conversion method: numerical to numerical conversion
template<class T>
template<class OT>
void vtkDICOMElementT<T>::GetValues(
  OT *v, vtkIdType start, vtkIdType count) const
{
  assert(start >= 0 && start+count <= this->NumberOfValues);
  T *data = &this->Data[start];
  for (vtkIdType i = 0; i < count; i++)
    {
    v[i] = static_cast<OT>(data[i]);
    }
}

// Use either strol() or strod() to convert string to number
template<>
template<class OT>
void vtkDICOMElementT<char>::GetValues(
  OT *v, vtkIdType start, vtkIdType count) const
{
  assert(start >= 0 && start+count <= this->NumberOfValues);
  size_t l = this->VL;
  const char *cp = this->Data;
  const char *ep = cp + l;

  if (this->VR == vtkDICOMVR::IS || this->VR == vtkDICOMVR::DS)
    {
    for (vtkIdType j = 0; j < start && cp != ep; j++)
      {
      bool bk = false;
      while (!bk && cp != ep)
        {
        bk = (*cp == '\\');
        cp++;
        }
      }

    for (vtkIdType i = 0; i < count && cp != ep; i++)
      {
      if (this->VR == vtkDICOMVR::DS)
        {
        v[i] = static_cast<OT>(strtod(cp, NULL));
        }
      else
        {
        v[i] = static_cast<OT>(strtol(cp, NULL, 10));
        }
      bool bk = false;
      while (!bk && cp != ep)
        {
        bk = (*cp == '\\');
        cp++;
        }
      }
    }
  else
    {
    for (vtkIdType k = 0; k < count; k++)
      {
      v[k] = 0;
      }
    }
}

// Cannot convert "vtkDICOMElement *" to numerical, so clear supplied array.
template<>
template<class OT>
void vtkDICOMElementT<vtkDICOMElement *>::GetValues(
  OT *v, vtkIdType start, vtkIdType count) const
{
  assert(start >= 0 && start+count <= this->NumberOfValues);
  for (vtkIdType i = 0; i < count; i++)
    {
    v[i] = 0;
    }
}

// Copy "vtkDICOMElement *" to an array of vtkDICOMElement pointers.
template<>
template<>
void vtkDICOMElementT<vtkDICOMElement *>::GetValues(
  vtkDICOMElement **v, vtkIdType start, vtkIdType count) const
{
  assert(start >= 0 && start+count <= this->NumberOfValues);
  vtkDICOMElement **data = &this->Data[start];
  for (vtkIdType i = 0; i < count; i++)
    {
    v[i] = data[i];
    }
}

//----------------------------------------------------------------------------
// Construct a numerical element.
template<class T, int N>
vtkDICOMElementTN<T,N>::vtkDICOMElementTN(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const T *data, vtkIdType vn)
{
  this->Tag = tag;
  this->VR = vr;
  this->Type = static_cast<unsigned char>(vtkTypeTraits<T>::VTKTypeID());
  this->NeedsFree = 0;
  this->VL = static_cast<unsigned int>(vn)*sizeof(T);
  this->NumberOfValues = static_cast<unsigned int>(vn);
  this->Data = this->QuickData;

  // clear the array, just be tidy
  for (int j = 0; j < N; j++)
    {
    this->QuickData[j] = 0;
    }

  // allocate memory if necessary
  if (vn > N)
    {
    this->Data = new T[vn];
    this->NeedsFree = 1;
    }

  // copy the data
  for (vtkIdType i = 0; i < vn; i++)
    {
    this->Data[i] = data[i];
    }
}

// Construct a string-containing element.
template<>
vtkDICOMElementTN<char, 24>::vtkDICOMElementTN(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const char *data, vtkIdType vn)
{
  this->Tag = tag;
  this->VR = vr;
  this->Type = VTK_CHAR;
  this->NeedsFree = 0;
  this->VL = static_cast<unsigned int>(vn);
  this->NumberOfValues = static_cast<unsigned int>(vn);
  this->Data = this->QuickData;

  const int N = 24;

  // clear the array variable, just to be tidy
  for (int j = 0; j < N; j++)
    {
    this->QuickData[j] = 0;
    }

  // allocate enough space for a terminating null byte
  if (vn + 1 > N)
    {
    this->Data = new char[vn + 1];
    this->NeedsFree = 1;
    }

  // copy and count the number of backslash-separated values
  unsigned int n = 1;
  for (vtkIdType i = 0; i < vn; i++)
    {
    this->Data[i] = data[i];
    bool delim = (data[i] == '\\');
    n += delim;
    }
  this->Data[vn] = '\0';

  // these VRs always have a multiplicity of 1
  if (this->VR == vtkDICOMVR::ST ||
      this->VR == vtkDICOMVR::LT ||
      this->VR == vtkDICOMVR::UT ||
      this->VR == vtkDICOMVR::UN ||
      this->VR == vtkDICOMVR::OB)
    {
    n = 1;
    }

  this->NumberOfValues = n;
}

// Construct a sequence element.
template<>
vtkDICOMElementTN<vtkDICOMElement *, 1>::vtkDICOMElementTN(
  vtkDICOMTag tag, vtkDICOMVR vr,
  vtkDICOMElement *const *data, vtkIdType vn)
{
  this->Tag = tag;
  this->VR = vr;
  this->Type = 0;
  this->NeedsFree = 1; // always free
  this->VL = static_cast<unsigned int>(vn)*sizeof(vtkDICOMElement *);
  this->NumberOfValues = static_cast<unsigned int>(vn);
  this->Data = this->QuickData;

  // the one QuickData element is never used
  const int N = 1;

  // clear the array (never use it)
  for (int j = 0; j < N; j++)
    {
    this->QuickData[j] = 0;
    }

  // allocate and copy the data
  this->Data = new vtkDICOMElement *[vn];
  for (vtkIdType i = 0; i < vn; i++)
    {
    this->Data[i] = data[i];
    }

  this->NumberOfValues = 1;
}

//----------------------------------------------------------------------------
// Factory generator methods (always reserve 24 bytes)
vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const char *data, vtkIdType n)
{
  return new vtkDICOMElementTN<char, 24>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const unsigned char *data, vtkIdType n)
{
  return new vtkDICOMElementTN<unsigned char, 24>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const short *data, vtkIdType n)
{
  return new vtkDICOMElementTN<short, 12>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const unsigned short *data, vtkIdType n)
{
  return new vtkDICOMElementTN<unsigned short, 12>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const int *data, vtkIdType n)
{
  return new vtkDICOMElementTN<int, 6>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const unsigned int *data, vtkIdType n)
{
  return new vtkDICOMElementTN<unsigned int, 6>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const float *data, vtkIdType n)
{
  return new vtkDICOMElementTN<float, 6>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  const double *data, vtkIdType n)
{
  return new vtkDICOMElementTN<double, 3>(tag, vr, data, n);
}

vtkDICOMElement *vtkDICOMElement::New(
  vtkDICOMTag tag, vtkDICOMVR vr,
  vtkDICOMElement *const *data, vtkIdType n)
{
  return new vtkDICOMElementTN<vtkDICOMElement *, 1>(tag, vr, data, n);
}
