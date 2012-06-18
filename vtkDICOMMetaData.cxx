#include "vtkDICOMMetaData.h"

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
  Element ***htable = this->Table;

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
vtkDICOMMetaData::Element *vtkDICOMMetaData::FindElement(Tag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.hash() & m);
  vtkDICOMMetaData::Element ***htable = this->Table;
  vtkDICOMMetaData::Element **hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (*hptr)
      {
      if ((*hptr)->tag == tag)
        {
        return *hptr;
        }
      hptr++;
      }
    }

  return NULL;
}

// Erase an element from the hash table
void vtkDICOMMetaData::EraseElement(Tag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.hash() & m);
  vtkDICOMMetaData::Element ***htable = this->Table;
  vtkDICOMMetaData::Element **hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (*hptr)
      {
      if ((*hptr)->tag == tag)
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
vtkDICOMMetaData::Element **vtkDICOMMetaData::FindElementLocation(Tag tag)
{
  unsigned int m = METADATA_HASH_SIZE - 1;
  unsigned int i = (tag.hash() & m);
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
      if ((*hptr)->tag == tag)
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
        vtkDICOMMetaData::Element **oldptr = htable[i];
        hptr = new vtkDICOMMetaData::Element *[2*(n+1)];
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
  Tag tag, unsigned short vr, unsigned int vl, const char *data)
{
  vtkDICOMMetaData::Element **loc = this->FindElementLocation(tag);

  if (*loc)
    {
    delete *loc;
    }

  char *newdata = new char[strlen(data)+1];
  strcpy(newdata, data);

  *loc = new vtkDICOMMetaData::Element(tag, vr, vl, newdata);
}

vtkDICOMMetaData::DictElement *vtkDICOMMetaData::FindDictElement(Tag tag)
{
  unsigned int m = DICT_HASH_TABLE_SIZE - 1;
  unsigned int i = (tag.hash() & m);
  vtkDICOMMetaData::DictElement **htable = vtkDICOMMetaData::DictHashTable;
  vtkDICOMMetaData::DictElement *hptr;

  if (htable && (hptr = htable[i]) != NULL)
    {
    while (hptr->tg)
      {
      if (hptr->tg == tag.group() &&
          hptr->te == tag.element())
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
