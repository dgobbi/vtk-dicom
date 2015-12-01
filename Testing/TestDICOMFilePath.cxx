#include "vtkDICOMFilePath.h"

#include <string>

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
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMFilePath");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  // Test common to all platforms

  { // test the constructor
  vtkDICOMFilePath path1("/hello/");
  TestAssert(path1.AsString() == "/hello");
  vtkDICOMFilePath path2("/");
  TestAssert(path2.AsString() == "/");
  vtkDICOMFilePath path3("");
  TestAssert(path3.AsString() == "");
  }

  { // test push and pop for absolute paths
  vtkDICOMFilePath path("/hello");
  path.PushBack("world");
  TestAssert(path.AsString() == "/hello/world");
  TestAssert(path.GetBack() == "world");
  path.PopBack();
  path.PushBack("world/");
  TestAssert(path.AsString() == "/hello/world");
  TestAssert(path.GetBack() == "world");
  path.PopBack();
  TestAssert(path.AsString() == "/hello");
  path.PushBack("/world");
  TestAssert(path.AsString() == "/hello");
  path.PushBack("world/");
  TestAssert(path.AsString() == "/hello/world");
  path.PushBack("/");
  TestAssert(path.AsString() == "/hello/world");
  path.PopBack();
  path.PopBack();
  TestAssert(path.AsString() == "/");
  path.PopBack();
  TestAssert(path.AsString() == "/");
  }

  { // test push and pop for relative paths
  vtkDICOMFilePath path("hello");
  path.PushBack("world");
  TestAssert(path.AsString() == "hello/world");
  TestAssert(path.GetBack() == "world");
  path.PopBack();
  TestAssert(path.AsString() == "hello");
  path.PopBack();
  TestAssert(path.AsString() == "");
  path.PopBack();
  TestAssert(path.AsString() == "");
  }

  { // test join
  vtkDICOMFilePath path("/hello");
  TestAssert(path.Join("world") == "/hello/world");
  TestAssert(path.Join("/world") == "/world");
  TestAssert(path.Join("/") == "/");
  }

  { // test extension
  vtkDICOMFilePath path("/hello");
  TestAssert(path.GetExtension() == "");
  path.PushBack("world.wld");
  TestAssert(path.GetExtension() == ".wld");
  path.PushBack("space.tar.gz");
  TestAssert(path.GetExtension() == ".gz");
  path.PopExtension();
  TestAssert(path.GetExtension() == ".tar");
  path.PopExtension();
  TestAssert(path.GetExtension() == "");
  TestAssert(path.AsString() == "/hello/world.wld/space");
  path.PushExtension("");
  TestAssert(path.AsString() == "/hello/world.wld/space");
  path.PushExtension(".");
  TestAssert(path.AsString() == "/hello/world.wld/space");
  path.PushExtension("/");
  TestAssert(path.AsString() == "/hello/world.wld/space");
  path.PushExtension("./");
  TestAssert(path.AsString() == "/hello/world.wld/space");
  path.PushExtension(".com");
  TestAssert(path.AsString() == "/hello/world.wld/space.com");
  }

#ifdef _WIN32
#endif

  return rval;
}
