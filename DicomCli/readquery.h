/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __readquery_h
#define __readquery_h

#include "vtkDICOMItem.h"

#include <vector>

// A class to identify a tag and possible a creator
class QueryTag
{
public:
  QueryTag() : m_tag(), m_creator() {}
  QueryTag(const vtkDICOMTag& t) : m_tag(t), m_creator() {}
  QueryTag(const vtkDICOMTag& t, const std::string& c)
    : m_tag(t), m_creator(c) {}

  vtkDICOMTag tag() const { return m_tag; }
  const std::string& creator() const { return m_creator; }

private:
  vtkDICOMTag m_tag;
  std::string m_creator;
};

typedef std::vector<QueryTag> QueryTagList;

// Read a query file
vtkDICOMItem dicomcli_readquery(const char *fname, QueryTagList *ql);

#endif /* __readquery_h */
