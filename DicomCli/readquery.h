/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __readquery_h
#define __readquery_h

#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include <vector>

typedef std::vector<vtkDICOMTagPath> QueryTagList;

//! Read a query file, return 'true' on success.
/*!
 *  The query file is read into the supplied vtkDICOMItem as a set of attribute
 *  values.  If the ordering within the file is important, then a QueryTagList can
 *  also be provided.  The tags will be pushed onto the QueryTagList in the same
 *  order as they are encountered in the file.
 */
bool dicomcli_readquery(const char *fname, vtkDICOMItem *query, QueryTagList *ql=0);

#endif /* __readquery_h */
