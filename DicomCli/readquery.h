/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef readquery_h
#define readquery_h

#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMTagPath.h"

#include <vector>

typedef std::vector<vtkDICOMTagPath> QueryTagList;

//! Read a query file, return 'true' on success.
/*!
 *  The query file is read into the supplied vtkDICOMItem as a set of
 *  attribute values.  If the ordering within the file is important,
 *  then a QueryTagList can also be provided.  The tags will be pushed
 *  onto the QueryTagList in the same order as they are encountered in
 *  the file.
 */
bool dicomcli_readquery(
  const char *fname, vtkDICOMItem *query, QueryTagList *ql=0);

//! Read a single query key, return 'true' on success.
bool dicomcli_readkey(
  const char *key, vtkDICOMItem *query, QueryTagList *ql=0);

//! Check if text looks like a query key (for error checking).
bool dicomcli_looks_like_key(const char *key);

//! Read a UID file, return 'true' on success.
/*!
 *  The first line of the file must contain a valid key, for example
 *  SeriesInstanceUID, and the remainder of the file should contain
 *  values, one value per line, without quotes.
 */
bool dicomcli_readuids(
  const char *fname, vtkDICOMItem *query, QueryTagList *ql=0);

//! Print brief info about a file for error messages.
/*!
 *  Sometimes a file that is found in an index doesn't actually exist,
 *  or cannot be read.  This method will print out the PatientID,
 *  StudyDate, StudyTime, StudyId, SeriesNumber, and InstanceNumber
 *  so that the user will have an idea of what file is missing, since
 *  the DICOM filenames themselves are usually not informative.
 */
void dicomcli_error_helper(vtkDICOMMetaData *meta, int i);

#endif /* readquery_h */
