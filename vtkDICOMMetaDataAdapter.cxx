/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMMetaDataAdapter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

//----------------------------------------------------------------------------
vtkDICOMMetaDataAdapter::vtkDICOMMetaDataAdapter(vtkDICOMMetaData *meta)
{
  this->Meta = meta;
  this->PerFrame = 0;
  this->Shared = 0;
  this->NumberOfInstances = 0;

  if (meta)
    {
    meta->Register(0);
    vtkDICOMDataElementIterator iter;
    iter = meta->Find(DC::PerFrameFunctionalGroupsSequence);
    if (iter != meta->End())
      {
      this->PerFrame = &iter->GetValue();
      }
    iter = meta->Find(DC::SharedFunctionalGroupsSequence);
    if (iter != meta->End())
      {
      this->Shared = &iter->GetValue();
      }
    }

  if (this->Shared && this->PerFrame)
    {
    this->NumberOfInstances =
      meta->GetAttributeValue(DC::NumberOfFrames).AsInt();
    }
  else if (meta)
    {
    this->NumberOfInstances = meta->GetNumberOfInstances();
    this->Shared = 0;
    this->PerFrame = 0;
    }
}

// Destructor
vtkDICOMMetaDataAdapter::~vtkDICOMMetaDataAdapter()
{
  if (this->Meta)
    {
    this->Meta->Delete();
    }
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaDataAdapter::GetAttributeValue(
  int idx, vtkDICOMTag tag) const
{
  vtkDICOMMetaData *meta = this->Meta;

  if (this->PerFrame)
    {
    // search PerFrameFunctionalGroupsSequence first,
    // then search SharedFunctionalGroupsSequence
    for (int i = 0; i < 2; i++)
      {
      const vtkDICOMValue *seq = this->PerFrame;
      unsigned int f = idx;

      if (i == 1)
        {
        seq = this->Shared;
        f = 0;
        }

      if (seq && f < seq->GetNumberOfValues())
        {
        // search for the item that matches the frame
        const vtkDICOMItem *items = seq->GetSequenceData();
        const vtkDICOMValue &v = items[f].GetAttributeValue(tag);
        if (v.IsValid())
          {
          return v;
          }
        // search within all the sequences in the item
        vtkDICOMDataElementIterator iter = items[f].Begin();
        vtkDICOMDataElementIterator iterEnd = items[f].End();
        while (iter != iterEnd)
          {
          const vtkDICOMValue &u = iter->GetValue();
          if (u.GetNumberOfValues() == 1)
            {
            const vtkDICOMItem *item = u.GetSequenceData();
            if (item)
              {
              const vtkDICOMValue &w = item->GetAttributeValue(tag);
              if (w.IsValid())
                {
                return w;
                }
              }
            }
          ++iter;
          }
        }
      }

    // if it wasn't in a shared functional group
    return meta->GetAttributeValue(0, tag);
    }

  // if no per-frame data, use file instance
  return meta->GetAttributeValue(idx, tag);
}

//----------------------------------------------------------------------------
const vtkDICOMValue &vtkDICOMMetaDataAdapter::GetAttributeValue(
  vtkDICOMTag tag) const
{
  return this->GetAttributeValue(0, tag);
}

//----------------------------------------------------------------------------
bool vtkDICOMMetaDataAdapter::HasAttribute(
  vtkDICOMTag tag) const
{
  const vtkDICOMValue& v = this->GetAttributeValue(0, tag);
  return v.IsValid();
}
