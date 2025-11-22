#include "vtkDICOMValue.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"

#include <iostream>
#include <sstream>

#include <string.h>
#include <stdlib.h>

// macro for performing tests
#define TestAssert(t) \
if (!(t)) \
{ \
  std::cout << exename << ": Assertion Failed: " << #t << "\n"; \
  std::cout << __FILE__ << ":" << __LINE__ << "\n"; \
  std::cout.flush(); \
  rval |= 1; \
}

int TestDICOMValue(int argc, char *argv[])
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
  v = vtkDICOMValue(vtkDICOMVR::SH, sp, strlen(sp));
  TestAssert(v.IsValid());
  v.Clear();
  TestAssert(!v.IsValid());
  }

  { // test VR and VL
  const char *sp = "HELLO\\THERE";
  vtkDICOMValue v = vtkDICOMValue(vtkDICOMVR::CS, sp, strlen(sp));
  TestAssert(v.GetVR() == vtkDICOMVR::CS);
  TestAssert(v.GetVL() == 12); // padded to even
  }

  { // test constructors and number of values
  vtkDICOMValue v;
  // backslash-separated values
  const char *sp = "HELLO\\THERE";
  v = vtkDICOMValue(vtkDICOMVR::CS, sp, strlen(sp));
  TestAssert(v.GetNumberOfValues() == 2);
  // numerical values
  static const double dbl[3] = { 1.0, 1.5, 1e200 };
  v = vtkDICOMValue(vtkDICOMVR::FD, dbl, 3);
  TestAssert(v.GetNumberOfValues() == 3);
  TestAssert(v.GetVL() == 24);
  TestAssert(memcmp(v.GetDoubleData(), dbl, 24) == 0);
  // numerical values converted to strings
  static const short ssi[5] = { 1, 3, -2, 60, 13 };
  v = vtkDICOMValue(vtkDICOMVR::IS, ssi, 5);
  TestAssert(v.GetNumberOfValues() == 5);
  TestAssert(v.GetVL() == 12);
  TestAssert(strcmp(v.GetCharData(), "1\\3\\-2\\60\\13") == 0);
  // string values converted to numbers
  static const char *flts = "1\\2.5\\-1e-5\\-4.23460975";
  static const float flt[4] = { 1.0f, 2.5f, -1e-5f, -4.23460975f };
  v = vtkDICOMValue(vtkDICOMVR::FL, flts, strlen(flts));
  TestAssert(v.GetNumberOfValues() == 4);
  TestAssert(v.GetVL() == 16);
  TestAssert(memcmp(v.GetFloatData(), flt, 16) == 0);
  // string values converted to tags
  static const char *tagstring = "(ff00,0123)\\(0FA2,0001)";
  v = vtkDICOMValue(vtkDICOMVR::AT, tagstring, strlen(tagstring));
  TestAssert(v.GetNumberOfValues() == 2);
  TestAssert(v.GetVL() == 8);
  TestAssert(v.GetTag(0) == vtkDICOMTag(0xff00,0x0123));
  TestAssert(v.GetTag(1) == vtkDICOMTag(0x0fa2,0x0001));
  // tags constructed from enums
  v = vtkDICOMValue(vtkDICOMVR::AT, DC::FrameTimeVector);
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.GetVL() == 4);
  TestAssert(v.AsTag() == vtkDICOMTag(0x0018,0x1065));
  // these text VRs should always report 1 value
  const char *hp = "he\\llo";
  size_t sl = strlen(hp);
  v = vtkDICOMValue(vtkDICOMVR::ST, hp, sl);
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.GetVL() == 6);
  TestAssert(strcmp(v.GetCharData(), hp) == 0);
  v = vtkDICOMValue(vtkDICOMVR::LT, hp, sl);
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.GetVL() == 6);
  TestAssert(strcmp(v.GetCharData(), hp) == 0);
  v = vtkDICOMValue(vtkDICOMVR::UT, hp, sl);
  TestAssert(v.GetNumberOfValues() == 1);
  TestAssert(v.GetVL() == 6);
  TestAssert(strcmp(v.GetCharData(), hp) == 0);
  // these data VRs should always report 1 value
  static const unsigned char uci[6] = { 1, 255, 12, 8, 9, 12 };
  v = vtkDICOMValue(vtkDICOMVR::UN, uci, 6);
  TestAssert(v.GetNumberOfValues() == 6);
  TestAssert(v.GetVL() == 6);
  TestAssert(memcmp(v.GetUnsignedCharData(), uci, 6) == 0);
  v = vtkDICOMValue(vtkDICOMVR::OB, uci, 6);
  TestAssert(v.GetNumberOfValues() == 6);
  TestAssert(v.GetVL() == 6);
  TestAssert(memcmp(v.GetUnsignedCharData(), uci, 6) == 0);
  static const short data[5] = { 1, 3, -2, 60, 13 };
  v = vtkDICOMValue(vtkDICOMVR::OW, data, 5);
  TestAssert(v.GetNumberOfValues() == 5);
  TestAssert(v.GetVL() == 10);
  TestAssert(memcmp(v.GetShortData(), data, 10) == 0);
  TestAssert(memcmp(v.GetUnsignedShortData(), data, 10) == 0);
  static const float fdata[5] = { 1.0f, 3.5f, -2.0f, 6.0f, 0.13f };
  v = vtkDICOMValue(vtkDICOMVR::OF, fdata, 5);
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
  v = vtkDICOMValue(vtkDICOMVR::FD, flt1, 2);
  v.GetValues(flt2, 2, 0);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  flt2[0] = flt2[1] = 0;
  v.GetValues(&flt2[0], 1, 0);
  v.GetValues(&flt2[1], 1, 1);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  v.GetValues(shrt, 2, 0);
  TestAssert(static_cast<int>(flt1[0]) == shrt[0]);
  TestAssert(static_cast<int>(flt1[1]) == shrt[1]);
  // store floats as decimal strings with VR=DS
  v = vtkDICOMValue(vtkDICOMVR::DS, flt1, 2);
  v.GetValues(flt2, 2, 0);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  flt2[0] = flt2[1] = 0;
  v.GetValues(&flt2[0], 1, 0);
  v.GetValues(&flt2[1], 1, 1);
  TestAssert(flt1[0] == flt2[0] && flt1[1] == flt2[1]);
  v.GetValues(shrt, 2, 0);
  TestAssert(static_cast<int>(flt1[0]) == shrt[0]);
  TestAssert(static_cast<int>(flt1[1]) == shrt[1]);
  // store floats as integer strings with VR=IS
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, 2);
  v.GetValues(flt2, 2, 0);
  TestAssert(static_cast<float>(static_cast<int>(flt1[0])) == flt2[0] &&
             static_cast<float>(static_cast<int>(flt1[1])) == flt2[1]);
  flt2[0] = flt2[1] = 0;
  v.GetValues(&flt2[0], 1, 0);
  v.GetValues(&flt2[1], 1, 1);
  TestAssert(static_cast<float>(static_cast<int>(flt1[0])) == flt2[0] &&
             static_cast<float>(static_cast<int>(flt1[1])) == flt2[1]);
  v.GetValues(shrt, 2, 0);
  TestAssert(static_cast<int>(flt1[0]) == shrt[0]);
  TestAssert(static_cast<int>(flt1[1]) == shrt[1]);
  }

  { // test getting text values
  vtkDICOMValue v;
  std::string sa[2];
  static const float flt1[2] = { 1.0f, 2.5f };
  // store floats as doubles with VR=FD
  v = vtkDICOMValue(vtkDICOMVR::FD, flt1, 2);
  v.GetValues(sa, 2, 0);
  TestAssert(sa[0] == "1.0" && sa[1] == "2.5");
  // store floats as text with VR=DS
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::DS, flt1, 2);
  v.GetValues(sa, 2, 0);
  TestAssert(sa[0] == "1" && sa[1] == "2.5");
  // store floats as text with VR=IS
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, 2);
  v.GetValues(sa, 2, 0);
  TestAssert(sa[0] == "1" && sa[1] == "2");
  // get just the first value
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, 2);
  v.GetValues(sa, 1, 0);
  TestAssert(sa[0] == "1" && sa[1] == "");
  // get just the second value
  sa[0] = "";
  sa[1] = "";
  v = vtkDICOMValue(vtkDICOMVR::IS, flt1, 2);
  v.GetValues(sa, 1, 1);
  TestAssert(sa[0] == "2" && sa[1] == "");
  }

  { // test allowed range of decimal strings
  vtkDICOMValue v;
  static const double dbl[4] = { 1e200, -1e200, 1e-200, -1e-200 };
  static const char *dblt = "9.999999999e+99\\-9.999999999e+99\\0\\0";
  v = vtkDICOMValue(vtkDICOMVR::DS, dbl, 4);
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
  v = vtkDICOMValue(vtkDICOMVR::SS, data, 5);
  u = vtkDICOMValue(vtkDICOMVR::SS, data, 5);
  TestAssert(u == v);
  data[2] = 0;
  u = vtkDICOMValue(vtkDICOMVR::SS, data, 5);
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
  v = vtkDICOMValue(vtkDICOMVR::FD, flt1, 2);
  os << v;
  TestAssert(os.str() == "1.0,2.5");
  os.str("");
  // store floats as decimal strings with VR=DS
  v = vtkDICOMValue(vtkDICOMVR::DS, flt1, 2);
  os << v;
  TestAssert(os.str() == "1\\2.5");
  os.str("");
  // store floats as float data with VR=OF
  v = vtkDICOMValue(vtkDICOMVR::OF, flt1, 2);
  os << v;
  TestAssert(os.str() == "floats[2]");
  os.str("");
  // store attribute tags
  static const unsigned short tags[4] = { 0x0002, 0x0020, 0xF001, 0x0001 };
  v = vtkDICOMValue(vtkDICOMVR::AT, tags, 4);
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
  const vtkDICOMValue *vptr2 = v.GetMultiplexData();
  TestAssert(strcmp(vptr2[0].GetCharData(),"1.3234") == 0);
  TestAssert(strcmp(vptr2[1].GetCharData(),"1.4 ") == 0); // padded to even
  TestAssert(strcmp(vptr2[2].GetCharData(),"-1e-5 ") == 0); // padded to even
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
  TestAssert(v.AsString() == "3\\2\\1");
  TestAssert(v.AsInt() == 0);
  }

  { // test AsUTF8String
  vtkDICOMValue v;
  std::string s;
  // backslash interpreted as backslash
  v = vtkDICOMValue(
    vtkDICOMVR::LO, vtkDICOMCharacterSet("ISO 2022 IR 13\\ISO 2022 IR 87"),
    "\xd4\xcf\xc0\xde^\xc0\xdb\xb3\\\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J");
  s = "\xef\xbe\x94\xef\xbe\x8f\xef\xbe\x80\xef\xbe\x9e^\xef\xbe\x80\xef\xbe\x9b\xef\xbd\xb3\\\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e";
  TestAssert(v.AsUTF8String() == s);
  // backslash interpreted according to character set
  v = vtkDICOMValue(
    vtkDICOMVR::LT, vtkDICOMCharacterSet("ISO 2022 IR 13\\ISO 2022 IR 87"),
    "\xd4\xcf\xc0\xde^\xc0\xdb\xb3\\\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J");
  s = "\xef\xbe\x94\xef\xbe\x8f\xef\xbe\x80\xef\xbe\x9e^\xef\xbe\x80\xef\xbe\x9b\xef\xbd\xb3\xc2\xa5\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e";
  TestAssert(v.AsUTF8String() == s);
  }

  { // test Matches for query matching
  vtkDICOMValue v;
  vtkDICOMValue u;

  // test comparison of null values
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELLO");
  TestAssert(!v.Matches(u));
  TestAssert(u.Matches(v));

  // test comparison of empty values
  v = vtkDICOMValue(vtkDICOMVR::CS, "");
  TestAssert(v.GetVL() == 0);
  TestAssert(u.Matches(v));
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "");
  TestAssert(v.Matches(u));

  // test comparison of identical values
  v = vtkDICOMValue(vtkDICOMVR::CS, "HELLO");
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELLO");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HEL");
  TestAssert(!v.Matches(u));
  v = vtkDICOMValue(vtkDICOMVR::US, 10);
  u = vtkDICOMValue(vtkDICOMVR::US, 10);
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::US, 9);
  TestAssert(!v.Matches(u));

  // test wildcards
  v = vtkDICOMValue(vtkDICOMVR::CS, "HELLO");
  u = vtkDICOMValue(vtkDICOMVR::CS, "*");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "*LO");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "H?LLO");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "H*?LLO");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "H?LO");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "H*P");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELL*");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELLO*");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELL?");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELLO?");
  TestAssert(!v.Matches(u));

  // test multiple values in the query
  v = vtkDICOMValue(vtkDICOMVR::UI, "10.3000.11.6");
  u = vtkDICOMValue(vtkDICOMVR::UI, "10.3000.11.6\\10.3000.10.6");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::UI, "10.3000.10.6\\10.3000.11.6");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::UI, "10.3000.11.7\\10.3000.10.6");
  TestAssert(!v.Matches(u));

  // test multiple values in the value
  v = vtkDICOMValue(vtkDICOMVR::CS, "HELLO\\THERE");
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELLO\\THERE");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "THERE\\HELLO");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELLO\\THER");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "HELLO");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "THERE");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "ELLO\\THER");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::CS, "ELLO");
  TestAssert(!v.Matches(u));

  // test string-encoded numbers
  v = vtkDICOMValue(vtkDICOMVR::IS, "5\\6\\10");
  u = vtkDICOMValue(vtkDICOMVR::IS, "5\\6\\10");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::IS, "5\\6");
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::IS, "6\\10");
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::IS, "5\\10");
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::IS, "6");
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::IS, "10\\5");
  TestAssert(!v.Matches(u));
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::IS, "6\\5");
  TestAssert(!v.Matches(u));
  TestAssert(!v.Matches(u));

  // test backslash on ST, LT, UT
  v = vtkDICOMValue(vtkDICOMVR::UT, "HELLO\\THERE");
  u = vtkDICOMValue(vtkDICOMVR::UT, "HELLO\\THERE");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::UT, "HELLO");
  TestAssert(!v.Matches(u));

  // test matches for binary data
  static const short vals[3] = { 10, 11, 12 };
  static const short vals2[2] = { 10, 11 };
  static const short vals3[2] = { 10, 12 };
  static const short vals4[2] = { 11, 10 };
  v = vtkDICOMValue(vtkDICOMVR::SS, vals, 3);
  u = vtkDICOMValue(vtkDICOMVR::SS, 10);
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::SS, 11);
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::SS, 12);
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::SS, 13);
  TestAssert(!v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::SS, vals2, 2);
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::SS, vals3, 2);
  TestAssert(v.Matches(u));
  TestAssert(!u.Matches(v));
  u = vtkDICOMValue(vtkDICOMVR::SS, vals4, 2);
  TestAssert(!v.Matches(u));
  TestAssert(!u.Matches(v));

  // test matches for binary data OW
  v = vtkDICOMValue(vtkDICOMVR::OW, vals, 3);
  u = vtkDICOMValue(vtkDICOMVR::OW, vals, 3);
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::OW, vals, 1);
  TestAssert(!v.Matches(u));
  TestAssert(!v.Matches(u));

  // test date
  v = vtkDICOMValue(vtkDICOMVR::DA, "20070125");
  u = vtkDICOMValue(vtkDICOMVR::DA, "20070124");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::DA, "2007");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::DA, "20070124-");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::DA, "20070124-20080124");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::DA, "20070126-20080124");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::DA, "-20070124");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::DA, "-20070126");
  TestAssert(v.Matches(u));

  // test time
  v = vtkDICOMValue(vtkDICOMVR::TM, "114501.00");
  u = vtkDICOMValue(vtkDICOMVR::TM, "114501");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::TM, "11");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::TM, "1145-");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::TM, "1146");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::TM, "-1146");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::TM, "0800-1146");
  TestAssert(v.Matches(u));

  // test sequences
  vtkDICOMSequence su(1);
  vtkDICOMItem item;
  item.Set(DC::ImageType, "ORIGINAL");
  item.Set(DC::StudyDate, "20070124-20080124");
  item.Set(DC::StudyTime, "");
  su.SetItem(0, item);
  u = su;
  vtkDICOMSequence sv;
  v = sv;
  TestAssert(!v.Matches(u));
  vtkDICOMItem item1;
  item1.Set(DC::ImageType, "DERIVED\\PRIMARY\\AXIAL");
  item1.Set(DC::StudyDate, "20070513");
  item1.Set(DC::StudyTime, "083045.210000");
  sv.AddItem(item1);
  v = sv;
  TestAssert(!v.Matches(u));
  vtkDICOMItem item2;
  item2.Set(DC::ImageType, "ORIGINAL\\PRIMARY\\AXIAL");
  item2.Set(DC::StudyDate, "20070513");
  item2.Set(DC::StudyTime, "083045.210000");
  sv.AddItem(item2);
  v = sv;
  TestAssert(v.Matches(u));
  vtkDICOMValue ve;
  vtkDICOMSequence su2;
  u = su2;
  TestAssert(v.Matches(u));
  TestAssert(ve.Matches(u));
  su2.AddItem(vtkDICOMItem());
  u = su2;
  TestAssert(v.Matches(u));
  TestAssert(ve.Matches(u));

  // test comparisons of encoded strings
  v = vtkDICOMValue(vtkDICOMVR::SH, vtkDICOMCharacterSet::ISO_IR_100,
    "p\373ddle");
  u = vtkDICOMValue(vtkDICOMVR::SH, vtkDICOMCharacterSet::ISO_IR_100,
    "puddle");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::SH, vtkDICOMCharacterSet::ISO_IR_6,
    "p?ddle");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::SH, vtkDICOMCharacterSet::ISO_IR_192,
    "p\303\273ddle");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::SH, vtkDICOMCharacterSet::ISO_IR_100,
    "puddle");
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::SH, vtkDICOMCharacterSet::ISO_IR_6,
    "p?ddle");
  TestAssert(v.Matches(u));

  // test comparisons of names
  const char *names[] = {
    "Gobbi", "Gobbi^David", "Gobbi^^Gregory^", "Gobbi^David^Gregory",
    "Gobb", "Gobbi^Kevin"
  };
  v = vtkDICOMValue(vtkDICOMVR::PN, names[3]);
  u = vtkDICOMValue(vtkDICOMVR::PN, names[0]);
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::PN, names[1]);
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::PN, names[2]);
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::PN, names[3]);
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::PN, names[4]);
  TestAssert(!v.Matches(u));
  u = vtkDICOMValue(vtkDICOMVR::PN, names[5]);
  TestAssert(!v.Matches(u));

  // test comparison with character sets
  v = vtkDICOMValue(
    vtkDICOMVR::LO, vtkDICOMCharacterSet("ISO 2022 IR 13\\ISO 2022 IR 87"),
    "\xd4\xcf\xc0\xde^\xc0\xdb\xb3\\\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J");
  u = vtkDICOMValue(
    vtkDICOMVR::LO, vtkDICOMCharacterSet("ISO_IR 13"),
    "\xd4\xcf\xc0\xde^\xc0\xdb\xb3");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(
    vtkDICOMVR::LO, vtkDICOMCharacterSet("ISO 2022 IR 13\\ISO 2022 IR 87"),
    "\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(
    vtkDICOMVR::LO, vtkDICOMCharacterSet("ISO_IR 192"),
    "\xef\xbe\x94\xef\xbe\x8f\xef\xbe\x80\xef\xbe\x9e^\xef\xbe\x80\xef\xbe\x9b\xef\xbd\xb3");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(
    vtkDICOMVR::LO, vtkDICOMCharacterSet("ISO_IR 192"),
    "\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e");

  // test comparison with character sets specifically for PN
  v = vtkDICOMValue(
    vtkDICOMVR::PN, vtkDICOMCharacterSet("ISO 2022 IR 13\\ISO 2022 IR 87"),
    "\xd4\xcf\xc0\xde^\xc0\xdb\xb3\\\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J");
  u = vtkDICOMValue(
    vtkDICOMVR::PN, vtkDICOMCharacterSet("ISO_IR 13"),
    "\xd4\xcf\xc0\xde^\xc0\xdb\xb3");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(
    vtkDICOMVR::PN, vtkDICOMCharacterSet("ISO 2022 IR 13\\ISO 2022 IR 87"),
    "\x1b$B;3ED\x1b(J^\x1b$BB@O:\x1b(J");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(
    vtkDICOMVR::PN, vtkDICOMCharacterSet("ISO_IR 192"),
    "\xef\xbe\x94\xef\xbe\x8f\xef\xbe\x80\xef\xbe\x9e^\xef\xbe\x80\xef\xbe\x9b\xef\xbd\xb3");
  TestAssert(v.Matches(u));
  u = vtkDICOMValue(
    vtkDICOMVR::PN, vtkDICOMCharacterSet("ISO_IR 192"),
    "\xe5\xb1\xb1\xe7\x94\xb0^\xe5\xa4\xaa\xe9\x83\x8e");
  TestAssert(v.Matches(u));
  }

  return rval;
}

#ifdef VTK_DICOM_SEPARATE_TESTS
int main(int argc, char *argv[])
{
  return TestDICOMValue(argc, argv);
}
#endif
