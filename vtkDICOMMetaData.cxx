#include "vtkDICOMMetaData.h"
#include "vtkDICOMElement.h"
#include "vtkDICOMTag.h"

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

#include <vector>
#include <utility>

vtkStandardNewMacro(vtkDICOMMetaData);

// The hash table size, must be a power of two
#define METADATA_HASH_SIZE 512

// Constructor
vtkDICOMMetaData::vtkDICOMMetaData()
{
  this->Table = NULL;
}

// Destructor
vtkDICOMMetaData::~vtkDICOMMetaData()
{
  vtkDICOMElement ***htable = this->Table;

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
vtkDICOMElement *vtkDICOMMetaData::FindElement(vtkDICOMTag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMElement ***htable = this->Table;
  vtkDICOMElement **hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (*hptr)
      {
      if ((*hptr)->GetTag() == tag)
        {
        return *hptr;
        }
      hptr++;
      }
    }

  return NULL;
}

// Erase an element from the hash table
void vtkDICOMMetaData::EraseElement(vtkDICOMTag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMElement ***htable = this->Table;
  vtkDICOMElement **hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (*hptr)
      {
      if ((*hptr)->GetTag() == tag)
        {
        delete *hptr;
        do
          {
          hptr[0] = hptr[1];
          }
        while (*hptr++);
        break;
        }
      hptr++;
      }
    }
}

// Return a reference to the element within the hash table, which can
// be used to insert a new value.
vtkDICOMElement **vtkDICOMMetaData::FindElementLocation(vtkDICOMTag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMElement ***htable = this->Table;
  vtkDICOMElement **hptr;

  if (htable == NULL)
    {
    // allocate the hash table
    m = METADATA_HASH_SIZE;
    htable = new vtkDICOMElement **[METADATA_HASH_SIZE];
    this->Table = htable;
    do { *htable++ = NULL; } while (--m);
    htable = this->Table;
    }

  hptr = htable[i];

  if (hptr == NULL)
    {
    hptr = new vtkDICOMElement *[4];
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
      if ((*hptr)->GetTag() == tag)
        {
        break;
        }
      // "n" includes the terminating null pointer
      n++;
      hptr++;
      }
    while (*hptr);

    if (*hptr == NULL)
      {
      // if n+1 is a power of two, double allocated space
      if (n > 1 && (n & (n+1)) == 0)
        {
        vtkDICOMElement **oldptr = htable[i];
        hptr = new vtkDICOMElement *[2*(n+1)];
        htable[i] = hptr;
        // copy the old list, including the terminating null
        for (unsigned int j = 0; j < n; j++)
          {
          *hptr++ = oldptr[j];
          }
        // go back to the terminating null
        hptr--;

        delete [] oldptr;
        }

      // add a new terminating null (after the current one)
      hptr[1] = NULL;
      }
    }

  return hptr;
}

// Insert an element into the hash table
void vtkDICOMMetaData::InsertElement(
  vtkDICOMTag tag, vtkDICOMVR vr, const char *data, vtkIdType l)
{
  vtkDICOMElement **loc = this->FindElementLocation(tag);

  if (*loc)
    {
    delete *loc;
    }

  char *newdata = new char[strlen(data)+1];
  strcpy(newdata, data);

  *loc = vtkDICOMElement::New(tag, vr, newdata, l);
}

vtkDICOMMetaData::DictEntry *vtkDICOMMetaData::FindDictEntry(vtkDICOMTag tag)
{
  unsigned int m = DICT_HASH_TABLE_SIZE - 1;
  unsigned int i = (tag.ComputeHash() & m);
  vtkDICOMMetaData::DictEntry **htable = vtkDICOMMetaData::DictHashTable;
  vtkDICOMMetaData::DictEntry *hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (hptr->GetName())
      {
      if (hptr->GetTag() == tag)
        {
        return hptr;
        }
      hptr++;
      }
    }

  return NULL;
}

void vtkDICOMMetaData::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
