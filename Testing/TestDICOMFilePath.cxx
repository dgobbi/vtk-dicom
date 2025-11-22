#include "vtkDICOMFilePath.h"

#include <iostream>
#include <string>

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

int TestDICOMFilePath(int argc, char *argv[])
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
  TestAssert(path.IsRoot());
  TestAssert(!path.IsEmpty());
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
  TestAssert(path.IsEmpty());
  TestAssert(!path.IsRoot());
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
  { // test the various roots
  TestAssert(vtkDICOMFilePath("\\").IsRoot());
  TestAssert(vtkDICOMFilePath("/").IsRoot());
  TestAssert(vtkDICOMFilePath("f:").IsRoot());
  TestAssert(vtkDICOMFilePath("E:\\").IsRoot());
  TestAssert(vtkDICOMFilePath("E:/").IsRoot());
  TestAssert(vtkDICOMFilePath("\\\\server\\share").IsRoot());
  TestAssert(vtkDICOMFilePath("//server/share").IsRoot());
  }

  { // test stripping of trailing slash from root
  vtkDICOMFilePath path1("C:");
  TestAssert(path1.AsString() == "C:");
  vtkDICOMFilePath path2("C:\\");
  TestAssert(path2.AsString() == "C:\\");
  vtkDICOMFilePath path3("\\\\server\\share\\");
  TestAssert(path3.AsString() == "\\\\server\\share");
  }

  { // test separator
  vtkDICOMFilePath path1("");
  path1.PushBack("hello");
  path1.PushBack("there");
  TestAssert(path1.AsString() == "hello/there");
  vtkDICOMFilePath path2("\\");
  path2.PushBack("hello");
  path2.PushBack("there");
  TestAssert(path2.AsString() == "\\hello\\there");
  }

  { // test special rules for device paths
  vtkDICOMFilePath path1("E:\\hello");
  TestAssert(path1.Join("\\") == "E:\\");
  TestAssert(path1.Join("E:world") == "E:\\hello\\world");
  TestAssert(path1.Join("D:world") == "D:world");
  TestAssert(path1.Join("E:\\world") == "E:\\world");
  vtkDICOMFilePath path2("E:");
  TestAssert(path2.Join("\\world") == "E:\\world");
  TestAssert(path2.Join("\\") == "E:\\");
  path2.PushBack("D:");
  TestAssert(path2.AsString() == "E:");
  path2.PushBack("D:\\");
  TestAssert(path2.AsString() == "E:");
  path2.PushBack("D:\\hello");
  TestAssert(path2.AsString() == "E:");
  path2.PushBack("\\\\server\\share");
  TestAssert(path2.AsString() == "E:");
  path2.PushBack("\\hello");
  TestAssert(path2.AsString() == "E:\\hello");
  path2.PushBack("world");
  TestAssert(path2.AsString() == "E:\\hello\\world");
  }

  { // test UNC path names
  vtkDICOMFilePath path1("\\\\server\\share");
  TestAssert(path1.Join("\\") == "\\");
  TestAssert(path1.Join("\\dir") == "\\dir");
  TestAssert(path1.Join("dir") == "\\\\server\\share\\dir");
  vtkDICOMFilePath path2("//server/share");
  TestAssert(path2.Join("/") == "/");
  TestAssert(path2.Join("/dir") == "/dir");
  TestAssert(path2.Join("dir") == "//server/share/dir");
  vtkDICOMFilePath path3("//server/share/dir");
  path3.PopBack();
  TestAssert(path3.AsString() == "//server/share");
  path3.PopBack();
  TestAssert(path3.AsString() == "//server/share");
  }

  { // test the extended prefix
  TestAssert(vtkDICOMFilePath("\\\\\?\\").IsRoot());
  TestAssert(vtkDICOMFilePath("\\\\.\\").IsRoot());
  TestAssert(vtkDICOMFilePath("\\\\\?\\D:").IsRoot());
  TestAssert(vtkDICOMFilePath("\\\\\?\\D:\\").IsRoot());
  TestAssert(vtkDICOMFilePath("\\\\\?\\UNC\\server\\share").IsRoot());
  vtkDICOMFilePath path1("\\\\\?\\");
  path1.PushBack("D:/");
  TestAssert(path1.AsString() == "\\\\\?\\D:\\");
  path1.PushBack(".");
  TestAssert(path1.AsString() == "\\\\\?\\D:\\");
  path1.PushBack("..");
  TestAssert(path1.AsString() == "\\\\\?\\D:\\");
  path1.PushBack("hello");
  TestAssert(path1.AsString() == "\\\\\?\\D:\\hello");
  path1.PushBack("..");
  TestAssert(path1.AsString() == "\\\\\?\\D:\\");
  path1.PushBack("hello/../world/./");
  TestAssert(path1.AsString() == "\\\\\?\\D:\\world");
  }

#endif

  return rval;
}

#ifdef VTK_DICOM_SEPARATE_TESTS
int main(int argc, char *argv[])
{
  return TestDICOMFilePath(argc, argv);
}
#endif
