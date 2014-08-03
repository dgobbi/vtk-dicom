/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "readquery.h"

#include "vtkDICOMSequence.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

typedef vtkDICOMVR VR;

// Build a tagpath
vtkDICOMTagPath path_append(const vtkDICOMTagPath& tpath, vtkDICOMTag tag)
{
  vtkDICOMTagPath result(tag);

  if (tpath.GetHead() != vtkDICOMTag())
    {
    if (tpath.HasTail())
      {
      result = vtkDICOMTagPath(
        tpath.GetHead(), tpath.GetIndex(),
        tpath.GetTail().GetHead(), 0, tag);
      }
    else
      {
      result = vtkDICOMTagPath(
        tpath.GetHead(), 0, tag);
      }
    }

  return result;
}

// Read a query file
vtkDICOMItem dicomcli_readquery(const char *fname, QueryTagList *ql)
{
  ifstream f(fname);
  if (!f.good())
    {
    fprintf(stderr, "Can't open query file %s\n\n", fname);
    exit(1);
    }

  // Each query line is either:
  // # a comment
  // GGGGEEEE                  # a tag to be returned
  // GGGGEEEE=PATTERN          # a pattern that must match
  // GGGGEEEE:VR=PATTERN       # search pattern with explicit VR
  // [PRIVATE_CREATOR]GGGGEEEE # private tag with creator name
  // GGGGEEEE\GGGGEEEE         # a tag nested within a sequence

  vtkDICOMItem query;

  int lineNumber = 0;
  while (f.good())
    {
    std::string line;
    std::getline(f, line);
    const char *cp = line.c_str();
    size_t n = line.size();
    unsigned int key = 0;
    lineNumber++;

    // strip leading whitespace
    size_t s = 0;
    while (s < n && isspace(cp[s]))
      {
      s++;
      }

    // skip line if it is a comment
    if (s == n || cp[s] == '#')
      {
      continue;
      }

    // read the tag path
    vtkDICOMTagPath tagPath;
    size_t tagDepth = 0;
    size_t lineStart = s;
    bool tagError = false;
    while (!tagError && tagDepth < 3)
      {
      // check for private creator in square brackets
      size_t creatorStart = s;
      size_t creatorEnd = s;
      if (cp[s] == '[')
        {
        s++;
        creatorStart = s;
        while (s < n && cp[s] != ']')
          {
          s++;
          }
        if (s == n)
          {
          fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
          fprintf(stderr, "Block is missing the final \"]\".\n");
          tagError = true;
          continue;
          }
        creatorEnd = s;
        s++;
        }

      std::string creator(&cp[creatorStart], creatorEnd - creatorStart);

      // read the DICOM tag
      size_t tagStart = s;
      while (s < n && isalnum(cp[s]))
        {
        s++;
        }
      size_t tagEnd = s;
      if (tagEnd - tagStart == 8)
        {
        char *cpe = const_cast<char *>(&cp[tagStart]);
        key = strtoul(&cp[tagStart], &cpe, 16);
        if (cpe - const_cast<char *>(&cp[tagStart]) != 8)
          {
          key = 0;
          }
        }

      vtkDICOMTag tag(key >> 16, key & 0xFFFF);

      // if creator, then resolve the tag now
      if (creator.length() > 0)
        {
        if (tagDepth == 0)
          {
          tag = query.ResolvePrivateTagForWriting(tag, creator);
          }
        else
          {
          vtkDICOMSequence seq = query.GetAttributeValue(tagPath);
          vtkDICOMItem item = seq.GetItem(0);
          tag = item.ResolvePrivateTagForWriting(tag, creator);
          vtkDICOMTag ctag(tag.GetGroup(), tag.GetElement() >> 8);
          vtkDICOMTagPath ctagPath = path_append(tagPath, ctag);
          query.SetAttributeValue(ctagPath, creator);
          }
        }

      // build the tag path
      tagPath = path_append(tagPath, tag);

      if (s < n && (cp[s] == '/' || cp[s] == '\\'))
        {
        // create an item for the next level of depth
        if (!query.GetAttributeValue(tagPath).IsValid())
          {
          query.SetAttributeValue(tagPath, vtkDICOMSequence(1));
          }
        s++;
        tagDepth++;
        }
      else
        {
        break;
        }
      }

    // if an error occurred while reading tag, skip to next line
    if (tagError || tagDepth > 2)
      {
      continue;
      }

    // read the DICOM vr
    vtkDICOMVR vr;

    size_t vrStart = s;
    size_t vrEnd = s;
    if (s < n && cp[s] == ':')
      {
      s++;
      vrStart = s;
      vrEnd = s;
      if (n - s >= 2)
        {
        s += 2;
        vrEnd = s;
        vr = vtkDICOMVR(&cp[vrStart]);
        if (!vr.IsValid() || vr == VR::OX || vr == VR::XS || vr == VR::UN)
          {
          int m = static_cast<int>(vrEnd - lineStart);
          m = (m > 40 ? 40 : m);
          fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
          fprintf(stderr, "Unrecognized DICOM VR \"%*.*s\"\n",
             m, m, &cp[lineStart]);
          }
        }
      }

    // dig down into the tag path
    const vtkDICOMItem *pitem = &query;
    vtkDICOMTag tag = tagPath.GetHead();
    vtkDICOMTagPath tmpPath = tagPath;
    while (tmpPath.HasTail())
      {
      pitem = pitem->GetAttributeValue(tag).GetSequenceData();
      tmpPath = tmpPath.GetTail();
      tag = tmpPath.GetHead();
      }

    // validate the tag and the vr against the dictionary
    vtkDICOMVR dictvr = pitem->FindDictVR(tag);
    if (!vr.IsValid())
      {
      vr = dictvr;
      }
    else if (dictvr.IsValid() && dictvr != VR::UN)
      {
      if (vr != dictvr &&
          !(((dictvr == VR::OX && (vr == VR::OW || vr == VR::OB))) ||
            ((dictvr == VR::XS && (vr == VR::SS || vr == VR::US)))))
        {
        int m = static_cast<int>(vrEnd - lineStart);
        m = (m > 40 ? 40 : m);
        fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
        fprintf(stderr, "VR of \"%*.*s\" doesn't match dictionary VR of %s\n",
           m, m, &cp[lineStart], dictvr.GetText());
        }
      }

    if (!vr.IsValid() || vr == VR::UN)
      {
      int m = static_cast<int>(s - lineStart);
      m = (m > 40 ? 40 : m);
      fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
      fprintf(stderr, "Unrecognized DICOM tag \"%*.*s\"\n",
              m, m, &cp[lineStart]);
      tagError = true;
      continue;
      }

    // check for a value or pattern following "="
    size_t valueStart = s;
    size_t valueEnd = s;
    bool valueContainsQuotes = false;
    if (s < n && cp[s] == '=')
      {
      s++;
      valueStart = s;
      valueEnd = s;
      if (s < n && cp[s] == '\"')
        {
        char delim = cp[s++];
        valueStart = s;
        while (s < n)
          {
          if (cp[s] == delim)
            {
            // a repeated quote becomes a literal quote
            if (s+1 < n && cp[s+1] == delim)
              {
              valueContainsQuotes = true;
              s++;
              }
            else
              {
              break;
              }
            }
          s++;
          }
        valueEnd = s;
        if (s < n)
          {
          s++;
          }
        }
      else
        {
        while (s < n && !isspace(cp[s]))
          {
          s++;
          }
        valueEnd = s;
        }
      }

    // add the tag and value to the query data set
    if (valueStart == valueEnd)
      {
      // empty value (always matches, always retrieved)
      query.SetAttributeValue(tagPath, vtkDICOMValue(vr));
      }
    else if (valueContainsQuotes)
      {
      // convert "" to "
      std::string sval;
      for (size_t t = valueStart; t < valueEnd; t++)
        {
        sval.push_back(cp[t]);
        if (cp[t] == '\"' && t+1 < valueEnd && cp[t+1] == '\"')
          {
          t++;
          }
        }
      query.SetAttributeValue(tagPath, vtkDICOMValue(vr, sval));
      }
    else
      {
      query.SetAttributeValue(tagPath,
        vtkDICOMValue(vr, &cp[valueStart], valueEnd - valueStart));
      }

    // add the tag path to the list
    if (ql)
      {
      ql->push_back(tagPath);
      }
    }

  return query;
}
