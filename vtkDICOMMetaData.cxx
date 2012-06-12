#include "vtkDICOMMetaData.h"

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

#include <vector>
#include <utility>

vtkStandardNewMacro(vtkDICOMMetaData);

// The hash table size, must be a power of two
#define METADATA_HASH_SIZE 512

//----------------------------------------------------------------------------
// An Element is just a std::pair of smart pointers
// (smart pointers provide automatic reference counting)
class vtkDICOMMetaData::Element
{
public:
  unsigned int Tag;
};

//----------------------------------------------------------------------------
// The container is a simple hash table

class vtkDICOMMetaData::Container
{
public:
  Container();
  ~Container();

  vtkDICOMMetaData::Element *FindElement(unsigned int tag);
  void EraseElement(unsigned int tag);
  vtkDICOMMetaData::Element *&FindElementSlot(unsigned int tag);
  void InsertElement(
    unsigned int tag, unsigned int vr, unsigned int vl, void *data);

private:
  vtkDICOMMetaData::Element ***Table;
};

// Create an empty hash table
vtkDICOMMetaData::Container::Container()
{
  this->Table = NULL;
}

// Destruct the hash table
vtkDICOMMetaData::Container::~Container()
{
  vtkDICOMMetaData::Element ***htable = this->Table;

  if (htable)
    {
    for (unsigned int i = 0; i < METADATA_HASH_SIZE; i++)
      {
      delete [] htable[i];
      }
    delete [] htable;
    }

  this->Table = NULL;
}


// Get an element from the hash table.
vtkDICOMMetaData::Element *vtkDICOMMetaData::Container::FindElement(
  unsigned int tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = ((tag ^ (tag >> 12)) & m);
  vtkDICOMMetaData::Element ***htable = this->Table;
  vtkDICOMMetaData::Element **hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (*hptr)
      {
      if ((*hptr)->Tag == tag)
        {
        return *hptr;
        }
      hptr++;
      }
    }

  return NULL;
}

// Erase an element from the hash table
void vtkDICOMMetaData::Container::EraseElement(unsigned int tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = ((tag ^ (tag >> 12)) & m);
  vtkDICOMMetaData::Element ***htable = this->Table;
  vtkDICOMMetaData::Element **hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (*hptr)
      {
      if ((*hptr)->Tag == tag)
        {
        delete *hptr;
        *hptr = NULL;
        break;
        }
      }
    }
}

// Return a reference to the element within the hash table, which can
// be used to insert a new value.
vtkDICOMMetaData::Element *&vtkDICOMMetaData::Container::FindElementSlot(
  unsigned int tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = ((tag ^ (tag >> 12)) & m);
  vtkDICOMMetaData::Element ***htable = this->Table;
  vtkDICOMMetaData::Element **hptr;

  if (htable == NULL)
    {
    // allocate the hash table
    m = METADATA_HASH_SIZE;
    htable = new vtkDICOMMetaData::Element **[METADATA_HASH_SIZE];
    this->Table = htable;
    do { *htable++ = NULL; } while (--m);
    htable = this->Table;
    }

  hptr = htable[i];

  if (hptr == NULL)
    {
    hptr = new vtkDICOMMetaData::Element *[4];
    htable[i] = hptr;
    hptr[0] = NULL;
    hptr[1] = NULL;
    }
  else if (*hptr)
    {
    // see if item is already there
    unsigned int n = 0;
    do
      {
      if ((*hptr)->Tag == tag)
        {
        break;
        }
      n++;
      hptr++;
      }
    while (*hptr);

    if (*hptr == NULL)
      {
      // if n+1 is a power of two, double allocated space
      if (n > 1 && (n & (n+1)) == 0)
        {
        vtkDICOMMetaData::Element **oldptr = htable[i];
        hptr = new vtkDICOMMetaData::Element *[2*(n+1)];
        htable[i] = hptr;
        for (unsigned int j = 0; j < n; j++)
          {
          *hptr++ = *oldptr++;
          }
        delete [] oldptr;
        }

      // add a terminating null
      hptr[1] = NULL;
      }
    }

  return *hptr;
}

// Insert an element into the hash table
void vtkDICOMMetaData::Container::InsertElement(
  unsigned int tag, unsigned int vr, unsigned int vl, void *data)
{
  vtkDICOMMetaData::Element *&slot = this->FindElementSlot(tag);

  if (slot)
    {
    delete slot;
    }

  slot = NULL;
}

// Constructor
vtkDICOMMetaData::vtkDICOMMetaData()
{
  this->Contents = new Container;
}

// Destructor
vtkDICOMMetaData::~vtkDICOMMetaData()
{
  delete this->Contents;
}

void vtkDICOMMetaData::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

}
