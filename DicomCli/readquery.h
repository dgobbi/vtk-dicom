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
#include "vtkDICOMTagPath.h"

#include <vector>

typedef std::vector<vtkDICOMTagPath> QueryTagList;

// Read a query file
vtkDICOMItem dicomcli_readquery(const char *fname, QueryTagList *ql=0);

#endif /* __readquery_h */
