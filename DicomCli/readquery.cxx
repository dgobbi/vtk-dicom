/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "readquery.h"

#include "vtkDICOMSequence.h"
#include "vtkDICOMDictionary.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

typedef vtkDICOMVR VR;

// Prototype for function that reads one query key
bool dicomcli_readkey_query(
  const char *cp, vtkDICOMItem *query, QueryTagList *ql, bool qfile);

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
bool dicomcli_readquery(
  const char *fname, vtkDICOMItem *query, QueryTagList *ql)
{
#ifdef _WIN32
  int cn = MultiByteToWideChar(CP_UTF8, 0, fname, -1, NULL, 0);
  wchar_t *wfname = new wchar_t[cn];
  MultiByteToWideChar(CP_UTF8, 0, fname, -1, wfname, cn);
  ifstream f(wfname);
  delete [] wfname;
#else
  ifstream f(fname);
#endif
  if (!f.good())
  {
    return false;
  }

  // Each query line is either:
  // # a comment
  // GGGG,EEEE                  # a tag to be returned
  // GGGG,EEEE=PATTERN          # a pattern that must match
  // GGGG,EEEE:VR=PATTERN       # search pattern with explicit VR
  // [PRIVATE_CREATOR]GGGG,EEEE # private tag with creator name
  // GGGG,EEEE\GGGG,EEEE         # a tag nested within a sequence

  int lineNumber = 0;
  while (f.good())
  {
    std::string line;
    std::getline(f, line);
    const char *cp = line.c_str();
    size_t n = line.size();
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

    if (!dicomcli_readkey_query(cp, query, ql, true))
    {
      fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
      return false;
    }
  }

  return true;
}

// If qfile is true, then key is being read from a query file
bool dicomcli_readkey_query(
  const char *cp, vtkDICOMItem *query, QueryTagList *ql, bool qfile)
{
  // read the tag path
  vtkDICOMTagPath tagPath;
  size_t tagDepth = 0;
  size_t s = 0;
  size_t lineStart = s;
  size_t n = strlen(cp);
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
        fprintf(stderr, "Error: Block is missing the final \"]\".\n");
        tagError = true;
        continue;
      }
      creatorEnd = s;
      s++;
    }

    std::string creator(&cp[creatorStart], creatorEnd - creatorStart);

    // read the DICOM tag
    vtkDICOMTag tag(0x0000,0x0000);
    size_t tagStart = s;
    bool isHex = true;
    bool hasComma = false;
    size_t commaPos = 0;
    while (s < n && (isalnum(cp[s]) || (cp[s] == ',' && !hasComma)))
    {
      if (cp[s] == ',')
      {
        hasComma = true;
        commaPos = s - tagStart;
      }
      else if (!isxdigit(cp[s]))
      {
        isHex = false;
      }
      s++;
    }
    size_t tagEnd = s;
    if (hasComma)
    {
      if (isHex)
      {
        unsigned int group = strtoul(&cp[tagStart], NULL, 16);
        unsigned int element = strtoul(&cp[tagStart+commaPos+1], NULL, 16);
        if (group < 0xFFFF && element < 0xFFFF)
        {
          tag = vtkDICOMTag(group, element);
        }
      }
    }
    else
    {
      std::string key(&cp[tagStart], tagEnd - tagStart);
      vtkDICOMDictEntry de = vtkDICOMDictionary::FindDictEntry(
        key.c_str(), creator.c_str());
      if (de.IsValid())
      {
        tag = de.GetTag();
      }
      else
      {
        fprintf(stderr, "Error: Unrecognized key %s\n", key.c_str());
        tagError = true;
        continue;
      }
    }

    // if creator, then resolve the tag now
    if (creator.length() > 0)
    {
      if (tagDepth == 0)
      {
        tag = query->ResolvePrivateTagForWriting(tag, creator);
      }
      else
      {
        vtkDICOMSequence seq = query->GetAttributeValue(tagPath);
        vtkDICOMItem item = seq.GetItem(0);
        tag = item.ResolvePrivateTagForWriting(tag, creator);
        vtkDICOMTag ctag(tag.GetGroup(), tag.GetElement() >> 8);
        vtkDICOMTagPath ctagPath = path_append(tagPath, ctag);
        query->SetAttributeValue(ctagPath, creator);
      }
    }

    // build the tag path
    tagPath = path_append(tagPath, tag);

    if (s < n && (cp[s] == '/' || cp[s] == '\\'))
    {
      // create an item for the next level of depth
      if (!query->GetAttributeValue(tagPath).IsValid())
      {
        query->SetAttributeValue(tagPath, vtkDICOMSequence(1));
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
    return false;
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
        fprintf(stderr, "Error: Unrecognized DICOM VR \"%*.*s\"\n",
           m, m, &cp[lineStart]);
        return false;
      }
    }
  }

  // dig down into the tag path
  const vtkDICOMItem *pitem = query;
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
  // the above method returns UN for OX and XS if it cannot resolve them
  if (dictvr == VR::UN)
  {
    // try again, taking a more direct approach
    vtkDICOMDictEntry e = pitem->FindDictEntry(tag);
    if (e.IsValid())
    {
      dictvr = e.GetVR();
    }
  }
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
      fprintf(stderr, "Error: VR of \"%*.*s\" doesn't match dict VR of %s\n",
         m, m, &cp[lineStart], dictvr.GetText());
    }
  }

  if (!vr.IsValid() || vr == VR::UN)
  {
    int m = static_cast<int>(s - lineStart);
    m = (m > 40 ? 40 : m);
    fprintf(stderr, "Error: Unrecognized DICOM tag \"%*.*s\"\n",
            m, m, &cp[lineStart]);
    return false;
  }

  // check for a value or pattern following "="
  size_t valueStart = s;
  size_t valueEnd = s;
  bool valueContainsQuotes = false;
  bool keyHasAssignment = false;
  if (s < n && cp[s] == '=')
  {
    keyHasAssignment = true;
    s++;
    valueStart = s;
    valueEnd = s;
    if (s < n && qfile && cp[s] == '\"')
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
      while (s < n && (!qfile || !isspace(cp[s])))
      {
        s++;
      }
      valueEnd = s;
    }
  }
  else if (s < n && (!qfile || !isspace(cp[s])))
  {
    if (isgraph(cp[s]))
    {
      fprintf(stderr, "Error: Illegal character \"%c\" after tag.\n", cp[s]);
    }
    else
    {
      fprintf(stderr, "Error: Illegal character after tag.\n");
    }
    return false;
  }

  // add the tag and value to the query data set
  if (valueStart == valueEnd)
  {
    // only overwrite previous value if '=' was explicitly used
    if (keyHasAssignment || !query->GetAttributeValue(tagPath).IsValid())
    {
      // empty value (always matches, always retrieved)
      query->SetAttributeValue(tagPath, vtkDICOMValue(vr));
    }
  }
  else if (valueContainsQuotes)
  {
    // convert "" to ", which is the rule for csv files
    std::string sval;
    for (size_t t = valueStart; t < valueEnd; t++)
    {
      sval.push_back(cp[t]);
      if (cp[t] == '\"' && t+1 < valueEnd && cp[t+1] == '\"')
      {
        t++;
      }
    }
    query->SetAttributeValue(tagPath, vtkDICOMValue(vr, sval));
  }
  else
  {
    query->SetAttributeValue(tagPath,
      vtkDICOMValue(vr, &cp[valueStart], valueEnd - valueStart));
  }

  // add the tag path to the list, if it isn't already there
  if (ql)
  {
    if (std::find(ql->begin(), ql->end(), tagPath) == ql->end())
    {
      ql->push_back(tagPath);
    }
  }

  return !tagError;
}

bool dicomcli_readkey(
  const char *cp, vtkDICOMItem *query, QueryTagList *ql)
{
  return dicomcli_readkey_query(cp, query, ql, false);
}

bool dicomcli_looks_like_key(const char *cp)
{
  size_t s = 0;
  size_t l = 0;

  // Look for private dictionary specifier in square brackets
  if (*cp == '[')
  {
    while (cp[l] != ']' && cp[l] != '\0')
    {
      l++;
    }
    if (cp[l] == ']')
    {
      l++;
      s = l;
    }
    else
    {
      return false;
    }
  }

  // Look for hexadecimal tag
  bool istag = true;
  size_t commas = 0;
  size_t digitrun = 0;
  while (cp[l] != '\0' && cp[l] != ':' && cp[l] != '=')
  {
    if (cp[l] == ',')
    {
      commas++;
      if (digitrun > 4)
      {
        istag = false;
      }
      digitrun = 0;
    }
    else if (isxdigit(cp[l]))
    {
      digitrun++;
    }
    else
    {
      istag = false;
    }
    l++;
  }
  if (istag && digitrun > 0 &&
      ((commas == 0 && digitrun <= 8) ||
       (commas == 1 && digitrun <= 4)))
  {
    return true;
  }

  // Look for dictionary key
  if (l != s)
  {
    std::string key(&cp[s], l - s);
    std::string creator;
    if (s > 0)
    {
      creator = std::string(&cp[1], s-2);
    }
    vtkDICOMDictEntry de =
      vtkDICOMDictionary::FindDictEntry(key.c_str(), creator.c_str());
    if (de.IsValid())
    {
      return true;
    }
  }

  return false;
}

bool dicomcli_readuids(
  const char *fname, vtkDICOMItem *query, QueryTagList *ql)
{
#ifdef _WIN32
  int cn = MultiByteToWideChar(CP_UTF8, 0, fname, -1, NULL, 0);
  wchar_t *wfname = new wchar_t[cn];
  MultiByteToWideChar(CP_UTF8, 0, fname, -1, wfname, cn);
  ifstream f(wfname);
  delete [] wfname;
#else
  ifstream f(fname);
#endif
  if (!f.good())
  {
    return false;
  }

  // Basic file structure:
  // # one or more comments
  // GGGG,EEEE   # a tag or key (only one)
  // 1.185.234   # a UID, followed by more UIDs

  QueryTagList ql2;
  std::string val;
  int lineNumber = 0;
  while (f.good())
  {
    std::string line;
    std::getline(f, line);
    const char *cp = line.c_str();
    size_t n = line.size();
    lineNumber++;

    // strip leading whitespace
    size_t s = 0;
    while (s < n && isspace(cp[s]))
    {
      s++;
    }

    // skip trailing whitespace
    if (n > s && isspace(cp[n-1]))
    {
      --n;
    }

    // skip line if it is a comment
    if (s == n || cp[s] == '#')
    {
      continue;
    }

    if (ql2.size() == 0)
    {
      // get the tag line, if not gotten yet
      if (!dicomcli_readkey_query(cp, query, &ql2, true))
      {
        fprintf(stderr, "Error %s line %d: ", fname, lineNumber);
        fprintf(stderr, "Need Valid DICOM tag at top of file.\n");
        return false;
      }
    }
    else
    {
      // read and append a value
      if (val.length() > 0)
      {
        val.append("\\", 1);
      }
      val.append(&cp[s], n-s);
      if (val.length() >= 65535)
      {
        fprintf(stderr, "Error %s line %d: ", fname, lineNumber);
        fprintf(stderr, "Too many values (there is a 65535 byte limit)\n");
        return false;
      }
    }
  }

  if (ql2.size() > 0)
  {
    // add the key and value to the query
    vtkDICOMTagPath tagPath = ql2[0];
    query->SetAttributeValue(tagPath, val);

    if (ql && std::find(ql->begin(), ql->end(), tagPath) == ql->end())
    {
      ql->push_back(tagPath);
    }
  }

  return true;
}
