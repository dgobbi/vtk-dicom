#include "vtkDICOMValue.h"

#include <sstream>

#include <string.h>
#include <stdlib.h>

// macro for performing tests
#define TestAssert(t) \
if (!(t)) \
{ \
  cout << exename << ": Assertion Failed: " << #t << "\n"; \
  cout << __FILE__ << ":" << __LINE__ << "\n"; \
  cout.flush(); \
  rval |= 1; \
}

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMValue");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  { // test empty value
  vtkDICOMValue v;
  TestAssert(!v.IsValid());
  const char *sp = "hello";
  v = vtkDICOMValue(vtkDICOMVR::SH, sp, sp + strlen(sp));
  TestAssert(v.IsValid());
  v.Clear();
  TestAssert(!v.IsValid());
  }

  { // test VR and VL
  const char *sp = "HELLO\\THERE";
  vtkDICOMValue v = vtkDICOMValue(vtkDICOMVR::CS, sp, sp + strlen(sp));
  TestAssert(v.GetVR() == vtkDICOMVR::CS);
  TestAssert(v.GetVL() == 12); // padded to even
  }

  { // test constructors and number of values
  vtkDICOMValue v;
  // backslash-separated values
  const char *sp = "HELLO\\THERE";
  v = vtkDICOMValue(vtkDICOMVR::CS, sp, sp + strlen(sp));
  TestAssert(v.GetNumberOfValues() == 2);
  // numerical values
  static const double dbl[3] = { 1.0, 1.5, 1e200 };
  v = vtkDICOMValue(vtkDICOMVR::FD, dbl, dbl + 3);
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.GetVL() == 24);
  TestAssert(memcmp(v.GetDoubleData(), dbl, 24) == 0);
  // numerical values converted to strings
  static const short ssi[5] = { 1, 3, -2, 60, 13 };
  v = vtkDICOMValue(vtkDICOMVR::IS, ssi, ssi + 5);
  TestAssert(v.GetNumberOfValues() == 5);
  TestAssert(v.GetVL() == 12);
  TestAssert(strcmp(v.GetCharData(), "1\\3\\-2\\60\\13") == 0);
  // string values converted to numbers
  static const char *flts = "1\\2.5\\-1e-5\\-4.23460975";
  static const float flt[4] = { 1.0f, 2.5f, -1e-5f, -4.23460975f };
  v = vtkDICOMValue(vtkDICOMVR::FL, flts, flts + strlen(flts));
  TestAssert(v.GetNumberOfValues() == 4);
  TestAssert(v.GetVL() == 16);
  TestAssert(memcmp(v.GetFloatData(), flt, 16) == 0);
  // these text VRs should always report 1 value
  const char *hp = "he\\llo";
  const char *ep = hp + strlen(hp);
  v = vtkDICOMValue(vtkDICOMVR::ST, hp, ep);
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.GetVL() == 6);
  TestAssert(strcmp(v.GetCharData(), hp) == 0);
  v = vtkDICOMValue(vtkDICOMVR::LT, hp, ep);
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.GetVL() == 6);
  TestAssert(strcmp(v.GetCharData(), hp) == 0);
  v = vtkDICOMValue(vtkDICOMVR::UT, hp, ep);
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.GetVL() == 6);
  TestAssert(strcmp(v.GetCharData(), hp) == 0);
  // these data VRs should always report 1 value
  static const unsigned char uci[6] = { 1, 255, 12, 8, 9, 12 };
  v = vtkDICOMValue(vtkDICOMVR::UN, uci, uci + 6);
  TestAssert(v.GetNumberOfValues() == 6);
  TestAssert(v.GetVL() == 6);
  TestAssert(memcmp(v.GetUnsignedCharData(), uci, 6) == 0);
  v = vtkDICOMValue(vtkDICOMVR::OB, uci, uci + 6);
  TestAssert(v.GetNumberOfValues() == 6);
  TestAssert(v.GetVL() == 6);
  TestAssert(memcmp(v.GetUnsignedCharData(), uci, 6) == 0);
  static const short data[5] = { 1, 3, -2, 60, 13 };
  v = vtkDICOMValue(vtkDICOMVR::OW, data, data + 5);
  TestAssert(v.GetNumberOfValues() == 5);
  TestAssert(v.GetVL() == 10);
  TestAssert(memcmp(v.GetShortData(), data, 10) == 0);
  TestAssert(memcmp(v.GetUnsignedShortData(), data, 10) == 0);
  static const float fdata[5] = { 1.0, 3.5, -2.0, 6.0, 0.13 };
  v = vtkDICOMValue(vtkDICOMVR::OF, fdata, fdata + 5);
  TestAssert(v.GetNumberOfValues() == 5);
  TestAssert(v.GetVL() == 20);
  TestAssert(memcmp(v.GetFloatData(), fdata, 20) == 0);
  }

  { // test getting numerical values
  vtkDICOMValue v;
  static const float flt1[2] = { 1.0f, 2.5f };
  float flt2[2];
  short shrt[2];
  // store floats as doubles with VR=FD
  v = vtkDICOMValue(vtkDICOMVR::FD, flt1, flt1 + 2);
  v.GetValues(flt2, flt2 + 2, 0);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  flt2[0] = flt2[1] = 0;
  v.GetValues(&flt2[0], &flt2[1], 0);
  v.GetValues(&flt2[1], &flt2[2], 1);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  v.GetValues(shrt, shrt + 2, 0);
  TestAssert(static_cast<int>(flt1[0]) == shrt[0]);
  TestAssert(static_cast<int>(flt1[1]) == shrt[1]);
  // store floats as decimal strings with VR=DS
  v = vtkDICOMValue(vtkDICOMVR::DS, flt1, flt1 + 2);
  v.GetValues(flt2, flt2 + 2, 0);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  flt2[0] = flt2[1] = 0;
  v.GetValues(&flt2[0], &flt2[1], 0);
  v.GetValues(&flt2[1], &flt2[2], 1);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  v.GetValues(shrt, shrt + 2, 0);
  TestAssert(static_cast<int>(flt1[0]) == shrt[0]);
  TestAssert(static_cast<int>(flt1[1]) == shrt[1]);
  // store floats as integer strings with VR=IS
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, flt1 + 2);
  v.GetValues(flt2, flt2 + 2, 0);
  TestAssert(static_cast<float>(static_cast<int>(flt1[0])) == flt2[0] &&
             static_cast<float>(static_cast<int>(flt1[1])) == flt2[1]);
  flt2[0] = flt2[1] = 0;
  v.GetValues(&flt2[0], &flt2[1], 0);
  v.GetValues(&flt2[1], &flt2[2], 1);
  TestAssert(static_cast<float>(static_cast<int>(flt1[0])) == flt2[0] &&
             static_cast<float>(static_cast<int>(flt1[1])) == flt2[1]);
  v.GetValues(shrt, shrt + 2, 0);
  TestAssert(static_cast<int>(flt1[0]) == shrt[0]);
  TestAssert(static_cast<int>(flt1[1]) == shrt[1]);
  }

  { // test getting text values
  vtkDICOMValue v;
  std::string sa[2];
  static const float flt1[2] = { 1.0f, 2.5f };
  // store floats as doubles with VR=FD
  v = vtkDICOMValue(vtkDICOMVR::FD, flt1, flt1 + 2);
  v.GetValues(sa, sa + 2, 0);
  TestAssert(sa[0] == "1.0" && sa[1] == "2.5");
  // store floats as text with VR=DS
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::DS, flt1, flt1 + 2);
  v.GetValues(sa, sa + 2, 0);
  TestAssert(sa[0] == "1" && sa[1] == "2.5");
  // store floats as text with VR=IS
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, flt1 + 2);
  v.GetValues(sa, sa + 2, 0);
  TestAssert(sa[0] == "1" && sa[1] == "2");
  // get just the first value
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, flt1 + 2);
  v.GetValues(sa, sa + 1, 0);
  TestAssert(sa[0] == "1" && sa[1] == "");
  // get just the second value
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, flt1 + 2);
  v.GetValues(sa, sa + 1, 1);
  TestAssert(sa[0] == "2" && sa[1] == "");
  }

  { // test allowed range of decimal strings
  vtkDICOMValue v;
  static const double dbl[4] = { 1e200, -1e200, 1e-200, -1e-200 };
  static const char *dblt = "9.999999999e+99\\-9.999999999e+99\\0\\0";
  v = vtkDICOMValue(vtkDICOMVR::DS, dbl, dbl + 4);
  TestAssert(strcmp(v.GetCharData(), dblt) == 0);
  }

  { // test equality
  vtkDICOMValue v, u;
  v = vtkDICOMValue(vtkDICOMVR::CS, "hello");
  u = vtkDICOMValue(vtkDICOMVR::CS, "hello");
  TestAssert(u == v);
  v = vtkDICOMValue(vtkDICOMVR::CS, "hello");
  u = vtkDICOMValue(vtkDICOMVR::DS, "1.234");
  TestAssert(u != v);
  v = vtkDICOMValue(vtkDICOMVR::CS, "hello");
  u = vtkDICOMValue(vtkDICOMVR::CS, "there");
  TestAssert(u != v);
  v = vtkDICOMValue(vtkDICOMVR::CS, "hello");
  u = vtkDICOMValue(vtkDICOMVR::SH, "hello");
  TestAssert(u != v);
  short data[5] = { 1, 3, -2, 60, 13 };
  v = vtkDICOMValue(vtkDICOMVR::SS, data, data + 5);
  u = vtkDICOMValue(vtkDICOMVR::SS, data, data + 5);
  TestAssert(u == v);
  data[2] = 0;
  u = vtkDICOMValue(vtkDICOMVR::SS, data, data + 5);
  TestAssert(u != v);
  }

  { // test stream operator
  std::stringstream os;
  vtkDICOMValue v;
  static const float flt1[2] = { 1.0f, 2.5f };
  // print the invalid value
  os << v;
  TestAssert(os.str() == "empty[0]");
  os.str("");
  // store floats as doubles with VR=FD
  v = vtkDICOMValue(vtkDICOMVR::FD, flt1, flt1 + 2);
  os << v;
  TestAssert(os.str() == "1.0,2.5");
  os.str("");
  // store floats as decimal strings with VR=DS
  v = vtkDICOMValue(vtkDICOMVR::DS, flt1, flt1 + 2);
  os << v;
  TestAssert(os.str() == "1\\2.5");
  os.str("");
  // store floats as float data with VR=OF
  v = vtkDICOMValue(vtkDICOMVR::OF, flt1, flt1 + 2);
  os << v;
  TestAssert(os.str() == "floats[2]");
  os.str("");
  // store attribute tags
  static const unsigned short tags[4] = { 0x0002, 0x0020, 0xF001, 0x0001 };
  v = vtkDICOMValue(vtkDICOMVR::AT, tags, tags + 4);
  os << v;
  TestAssert(os.str() == "(0002,0020),(F001,0001)");
  os.str("");
  }

  { // test multiplexing
  vtkDICOMValue v;
  vtkDICOMValue *vptr = v.AllocateMultiplexData(vtkDICOMVR::DS, 3);
  vptr[0] = vtkDICOMValue(vtkDICOMVR::DS, "1.3234");
  vptr[1] = vtkDICOMValue(vtkDICOMVR::DS, "1.4");
  vptr[2] = vtkDICOMValue(vtkDICOMVR::DS, "-1e-5");
  vptr = v.GetMultiplexData();
  TestAssert(strcmp(vptr[0].GetCharData(),"1.3234") == 0);
  TestAssert(strcmp(vptr[1].GetCharData(),"1.4 ") == 0); // padded to even
  TestAssert(strcmp(vptr[2].GetCharData(),"-1e-5 ") == 0); // padded to even
  vtkDICOMValue u;
  vtkDICOMValue *uptr = u.AllocateMultiplexData(vtkDICOMVR::DS, 3);
  uptr[0] = vtkDICOMValue(vtkDICOMVR::DS, "1.3234");
  uptr[1] = vtkDICOMValue(vtkDICOMVR::DS, "1.4");
  uptr[2] = vtkDICOMValue(vtkDICOMVR::DS, "-1e-5");
  TestAssert(v == v);
  TestAssert(u == v);
  uptr[1] = vtkDICOMValue(vtkDICOMVR::DS, "1");
  TestAssert(u != v);
  vptr[1] = vtkDICOMValue(vtkDICOMVR::IS, "1");
  TestAssert(u != v);
  vptr[0] = uptr[0];
  vptr[1] = uptr[1];
  vptr[2] = uptr[2];
  TestAssert(u == v);
  u = v;
  TestAssert(u == v);
  }

  { // test AsString
  vtkDICOMValue v;
  v = vtkDICOMValue(vtkDICOMVR::US, "3\\2\\1");
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.AsString() == "3\\2\\1");
  TestAssert(v.AsInt() == 3);
  v = vtkDICOMValue(vtkDICOMVR::IS, "3\\2\\1");
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.AsString() == "3\\2\\1");
  TestAssert(v.AsInt() == 3);
  v = vtkDICOMValue(vtkDICOMVR::UT, "3\\2\\1");
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.AsString() == "3\\2\\1 ");
  TestAssert(v.AsInt() == 0);
  }

  return rval;
}
