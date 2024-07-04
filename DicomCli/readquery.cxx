/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2024 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "readquery.h"

#include "vtkDICOMFile.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMDictionary.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

typedef vtkDICOMVR VR;

namespace {

// A class for reading a text file line-by-line.
// It uses its own buffer, since the file is unbuffered.
class LineReader
{
public:
  LineReader(vtkDICOMFile *file);
  ~LineReader();

  size_t ReadLine(std::string *s);

private:
  LineReader(const LineReader&); // = delete;
  LineReader& operator=(const LineReader&); // = delete;

  vtkDICOMFile *File;
  size_t BufferSize;
  unsigned char *Buffer;
  const unsigned char *Pointer;
  const unsigned char *EndPointer;
};

LineReader::LineReader(vtkDICOMFile *file) :
  File(file), BufferSize(4096)
{
  this->Buffer = new unsigned char [this->BufferSize];
  this->Pointer = &this->Buffer[0];
  this->EndPointer = this->Pointer;
}

LineReader::~LineReader()
{
  delete [] this->Buffer;
  this->File->Close();
}

size_t LineReader::ReadLine(std::string *s)
{
  s->clear();

  size_t total = 0;
  while (!this->File->GetError() && !this->File->EndOfFile())
  {
    if (this->Pointer == this->EndPointer)
    {
      this->Pointer = this->Buffer;
      this->EndPointer = this->Buffer;
      this->EndPointer += this->File->Read(this->Buffer, this->BufferSize);
      if (this->Pointer == this->EndPointer)
      {
        break;
      }
    }

    const unsigned char *ucp = this->Pointer;
    const char *cp = reinterpret_cast<const char *>(ucp);
    size_t l = 0;
    while (ucp != this->EndPointer && *ucp != '\r' && *ucp != '\n')
    {
      ucp++;
      l++;
    }
    this->Pointer = ucp;
    if (ucp == this->EndPointer)
    {
      // append and continue
      s->append(cp, l);
      total += l;
    }
    else if (*ucp == '\n')
    {
      // newline means end of line
      this->Pointer++;
      l++;
      s->append(cp, l);
      total += l;
      break;
    }
    else if (*ucp == '\r')
    {
      // carriage return is end of line, also eat following newline
      this->Pointer++;
      l++;
      if (this->Pointer == this->EndPointer)
      {
        s->append(cp, l);
        total += l;
        l = 0;
        this->Pointer = this->Buffer;
        this->EndPointer = this->Buffer;
        this->EndPointer += this->File->Read(this->Buffer, this->BufferSize);
        cp = reinterpret_cast<const char *>(this->Pointer);
      }
      if (this->Pointer != this->EndPointer && *this->Pointer == '\n')
      {
        this->Pointer++;
        l++;
      }
      if (l != 0)
      {
        s->append(cp, l);
        total += l;
      }
      break;
    }
  }

  return total;
}

}

// Prototype for function that reads one query key
bool dicomcli_readkey_query(
  const char *cp, vtkDICOMItem *query, QueryTagList *ql,
  bool ql_unique, bool qfile);

// Read a query file
bool dicomcli_readquery(
  const char *fname, vtkDICOMItem *query, QueryTagList *ql, bool ql_unique)
{
  vtkDICOMFile f(fname, vtkDICOMFile::In);

  // Each query line is either:
  // # a comment
  // GGGG,EEEE                  # a tag to be returned
  // GGGG,EEEE=PATTERN          # a pattern that must match
  // GGGG,EEEE:VR=PATTERN       # search pattern with explicit VR
  // [PRIVATE_CREATOR]GGGG,EEEE # private tag with creator name
  // GGGG,EEEE\GGGG,EEEE         # a tag nested within a sequence

  int lineNumber = 0;
  std::string line;
  LineReader lr(&f);
  while (lr.ReadLine(&line))
  {
    const char *cp = line.c_str();
    size_t n = line.size();
    lineNumber++;

    // strip leading whitespace
    size_t s = 0;
    while (s < n && (cp[s] & 0x80) == 0 && isspace(cp[s]))
    {
      s++;
    }

    // skip line if it is a comment
    if (s == n || cp[s] == '#')
    {
      continue;
    }

    if (!dicomcli_readkey_query(cp, query, ql, ql_unique, true))
    {
      fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
      return false;
    }
  }

  return (f.GetError() == 0);
}

// If qfile is true, then key is being read from a query file
bool dicomcli_readkey_query(
  const char *cp, vtkDICOMItem *query, QueryTagList *ql,
  bool ql_unique, bool qfile)
{
  // read the tag path
  vtkDICOMTagPath tagPath;
  std::string creator;
  size_t tagDepth = 0;
  size_t s = 0;
  size_t lineStart = s;
  size_t n = strlen(cp);
  bool tagError = false;
  const int maxerrlen = 80;

  // set the default character set to utf-8
  vtkDICOMCharacterSet cs(vtkDICOMCharacterSet::ISO_IR_192);

  while (!tagError)
  {
    // check for private creator in square brackets
    if (cp[s] == '[')
    {
      size_t t = ++s;
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
      creator.assign(&cp[t], s++ - t);
    }

    // read the DICOM tag
    vtkDICOMTag tag(0x0000,0x0000);
    size_t tagStart = s;
    bool isHex = true;
    bool hasComma = false;
    size_t commaPos = 0;
    while (s < n && (cp[s] & 0x80) == 0 &&
           (isalnum(cp[s]) || (cp[s] == ',' && !hasComma)))
    {
      if (cp[s] == ',')
      {
        hasComma = true;
        commaPos = s - tagStart;
      }
      else if ((cp[s] & 0x80) != 0 || !isxdigit(cp[s]))
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
        unsigned int group = strtoul(&cp[tagStart], nullptr, 16);
        unsigned int element = strtoul(&cp[tagStart+commaPos+1], nullptr, 16);
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
    if (creator.length() > 0 && (tag.GetGroup() & 0x0001) != 0)
    {
      if (tagDepth == 0)
      {
        tag = query->ResolvePrivateTagForWriting(tag, creator);
      }
      else
      {
        // Since "item" is copy-on-write, we want to avoid creating
        // an unnecessary copy when the the creator element is added.
        // So we get the item, add the creator element, then get
        // the tag and value for that element, and let the item go
        // out of scope so that its reference count is decremented
        // (hopefully decremented to 1, so that the "copy" is not
        // performed).  Then we add the creator element to the
        // query data set (which may have become a copy due to
        // copy-on-write, if the reference count was greater than one).
        vtkDICOMTagPath ctagPath;
        vtkDICOMValue cval;
        {
          // this must be in its own scope in order to work...
          vtkDICOMSequence seq = query->Get(tagPath);
          vtkDICOMItem item = seq.GetItem(0);
          tag = item.ResolvePrivateTagForWriting(tag, creator);
          vtkDICOMTag ctag(tag.GetGroup(), tag.GetElement() >> 8);
          ctagPath = vtkDICOMTagPath(tagPath, 0, ctag);
          cval = item.Get(ctag);
        }
        // add the creator element
        query->Set(ctagPath, cval);
      }
    }

    // build the tag path
    tagPath = vtkDICOMTagPath(tagPath, 0, tag);

    if (s < n && (cp[s] == '/' || cp[s] == '\\'))
    {
      // create an item for the next level of depth
      if (!query->Get(tagPath).IsValid())
      {
        query->Set(tagPath, vtkDICOMSequence(1));
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
  if (tagError)
  {
    return false;
  }

  // read the DICOM vr
  vtkDICOMVR vr;

  size_t vrEnd = s;
  if (s < n && cp[s] == ':')
  {
    s++;
    size_t vrStart = s;
    vrEnd = s;
    if (n - s >= 2)
    {
      s += 2;
      vrEnd = s;
      vr = vtkDICOMVR(&cp[vrStart]);
      if (!vr.IsValid() || vr == VR::OX || vr == VR::XS || vr == VR::UN)
      {
        int m = static_cast<int>(vrEnd - lineStart);
        m = (m > maxerrlen ? maxerrlen : m);
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
    pitem = pitem->Get(tag).GetSequenceData();
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
      m = (m > maxerrlen ? maxerrlen : m);
      fprintf(stderr, "Error: VR of \"%*.*s\" doesn't match dict VR of %s\n",
         m, m, &cp[lineStart], dictvr.GetText());
    }
  }

  if (!vr.IsValid() || vr == VR::UN)
  {
    int m = static_cast<int>(s - lineStart);
    m = (m > maxerrlen ? maxerrlen : m);
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
    }
    else
    {
      while (s < n && (!qfile || (cp[s] & 0x80) != 0 || !isspace(cp[s])))
      {
        s++;
      }
      valueEnd = s;
    }
  }
  else if (s < n && (!qfile || (cp[s] & 0x80) != 0 || !isspace(cp[s])))
  {
    if ((cp[s] & 0x80) != 0 || isgraph(cp[s]))
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
    if (keyHasAssignment || !query->Get(tagPath).IsValid())
    {
      // empty value (always matches, always retrieved)
      query->Set(tagPath, vtkDICOMValue(vr));
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
    if (vr.HasSpecificCharacterSet())
    {
      query->Set(tagPath, vtkDICOMValue(vr, cs, sval));
    }
    else
    {
      query->Set(tagPath, vtkDICOMValue(vr, sval));
    }
  }
  else
  {
    if (vr.HasSpecificCharacterSet())
    {
    query->Set(tagPath,
      vtkDICOMValue(vr, cs, &cp[valueStart], valueEnd - valueStart));
    }
    else
    {
    query->Set(tagPath,
      vtkDICOMValue(vr, &cp[valueStart], valueEnd - valueStart));
    }
  }

  // add the tag path to the list, if it isn't already there
  if (ql)
  {
    if (!ql_unique || std::find(ql->begin(), ql->end(), tagPath) == ql->end())
    {
      ql->push_back(tagPath);
    }
  }

  return true;
}

bool dicomcli_readkey(
  const char *cp, vtkDICOMItem *query, QueryTagList *ql, bool ql_unique)
{
  return dicomcli_readkey_query(cp, query, ql, ql_unique, false);
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
    else if ((cp[l] & 0x80) == 0 && isxdigit(cp[l]))
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
  vtkDICOMFile f(fname, vtkDICOMFile::In);

  // Basic file structure:
  // # one or more comments
  // GGGG,EEEE   # a tag or key (only one)
  // 1.185.234   # a UID, followed by more UIDs

  QueryTagList ql2;
  std::string val;
  int lineNumber = 0;
  std::string line;
  LineReader lr(&f);
  while (lr.ReadLine(&line))
  {
    const char *cp = line.c_str();
    size_t n = line.size();
    lineNumber++;

    // strip leading whitespace
    size_t s = 0;
    while (s < n && (cp[s] & 0x80) == 0 && isspace(cp[s]))
    {
      s++;
    }

    // skip trailing whitespace
    if (n > s && (cp[n-1] & 0x80) == 0 && isspace(cp[n-1]))
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
      if (!dicomcli_readkey_query(cp, query, &ql2, true, true))
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
    query->Set(tagPath, val);

    if (ql && std::find(ql->begin(), ql->end(), tagPath) == ql->end())
    {
      ql->push_back(tagPath);
    }
  }

  return (f.GetError() == 0);
}

void dicomcli_error_helper(vtkDICOMMetaData *meta, int i)
{
  if (meta)
  {
    // print some useful identifying information about a DICOM file
    fprintf(stderr, "Cannot read the DICOM file for the following entry:\n");
    fprintf(stderr, "StudyInstanceUID=\"%s\",\n",
      meta->Get(DC::StudyInstanceUID).AsString().c_str());
    fprintf(stderr, "SeriesInstanceUID=\"%s\",\n",
      meta->Get(DC::SeriesInstanceUID).AsString().c_str());
    fprintf(stderr, "PatientID=\"%s\", StudyDate=\"%s\", StudyTime=\"%s\",\n",
      meta->Get(DC::PatientID).AsString().c_str(),
      meta->Get(DC::StudyDate).AsString().c_str(),
      meta->Get(DC::StudyTime).AsString().c_str());
    fprintf(stderr, "StudyID=\"%s\", SeriesNumber=\"%s\", InstanceNumber=\"%s\"\n",
      meta->Get(DC::StudyID).AsString().c_str(),
      meta->Get(DC::SeriesNumber).AsString().c_str(),
      meta->Get(i, DC::InstanceNumber).AsString().c_str());
  }
}
