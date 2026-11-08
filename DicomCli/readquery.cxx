/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
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

// A missing creator element does not make a block free if the query already
// addresses data in it by literal group and element.
unsigned int FindFreeBlock(const vtkDICOMItem& item, unsigned short group,
                           unsigned int preferred)
{
  bool used[256] = {};
  for (auto it = item.Begin(); it != item.End(); ++it)
  {
    vtkDICOMTag tag = it->GetTag();
    if (tag.GetGroup() > group) break;
    if (tag.GetGroup() != group) continue;
    unsigned int e = tag.GetElement();
    if (e >= 0x10 && e <= 0xff) used[e] = true;
    if (e >= 0x1000) used[e >> 8] = true;
  }
  if (preferred >= 0x10 && !used[preferred]) return preferred;
  for (unsigned int b = 0x10; b <= 0xff; ++b)
    if (!used[b]) return b;
  return 0;
}

// Replace one component of displayed paths (and any nested creator paths)
// when an automatic creator block moves. Keep the user-supplied order.
void RemapPaths(std::vector<vtkDICOMTagPath>& paths, const vtkDICOMTagPath& prefix,
                unsigned short group, unsigned int oldBlock, unsigned int newBlock)
{
  const unsigned int depth = prefix.GetSize();
  for (auto& path : paths)
  {
    if (path.GetSize() <= depth) continue;
    vtkDICOMTag tag = path.GetTag(depth);
    unsigned int e = tag.GetElement();
    if (tag.GetGroup() != group || (e != oldBlock && (e >> 8) != oldBlock)) continue;
    vtkDICOMTagPath parent;
    for (unsigned int i = 0; i < depth; ++i)
      parent = vtkDICOMTagPath(parent, i ? path.GetIndex(i-1) : 0, path.GetTag(i));
    if (parent != prefix || (depth && path.GetIndex(depth-1) != 0)) continue;
    unsigned int moved = e == oldBlock ? newBlock : ((newBlock << 8) | (e & 0xff));
    vtkDICOMTagPath replacement(parent, 0, vtkDICOMTag(group, moved));
    for (unsigned int i = depth+1; i < path.GetSize(); ++i)
      replacement = vtkDICOMTagPath(replacement, path.GetIndex(i-1), path.GetTag(i));
    path = replacement;
  }
}

bool ResolveQueryBlock(DICOMQueryItem *query, const vtkDICOMTagPath& prefix,
                       vtkDICOMTag& tag, const std::string& creator, QueryTagList *ql,
                       const vtkDICOMValue *replacement = nullptr)
{
  const unsigned short g = tag.GetGroup();
  const unsigned int e = tag.GetElement();
  vtkDICOMItem item = *query;
  if (prefix.GetSize())
  {
    vtkDICOMSequence seq = query->Get(prefix);
    item = seq.GetItem(0);
  }
  const unsigned int block = e >> 8;
  if (!creator.empty())
  {
    vtkDICOMTag resolved = item.ResolvePrivateTag(tag, creator);
    if (resolved == vtkDICOMTag(0xffff, 0xffff))
    {
      unsigned int b = FindFreeBlock(item, g, block);
      if (!b) return false;
      resolved = item.ResolvePrivateTagForWriting(vtkDICOMTag(g, (b << 8) | (e & 0xff)), creator);
      vtkDICOMTag ctag(g, b);
      vtkDICOMTagPath cp(prefix, 0, ctag);
      query->Set(cp, item.Get(ctag));
      query->AutoCreators.push_back(cp);
    }
    tag = resolved;
    return true;
  }
  vtkDICOMTagPath cp(prefix, 0, vtkDICOMTag(g, e < 0x100 ? e : block));
  auto pos = std::find(query->AutoCreators.begin(), query->AutoCreators.end(), cp);
  if (pos == query->AutoCreators.end()) return true;
  if (e < 0x100)
  {
    // Wait until the complete value (including query-file quotes) is parsed.
    if (!replacement) return true;
    if (item.Get(vtkDICOMTag(g, e)).AsString() == replacement->AsString())
    {
      // A matching explicit declaration pins this block to its literal address.
      query->AutoCreators.erase(pos);
      return true;
    }
  }
  const unsigned int sourceBlock = e < 0x100 ? e : block;
  unsigned int dest = FindFreeBlock(item, g, 0);
  if (!dest) return false;
  // 'item' is a copy-on-write snapshot; iterators stay valid while editing query.
  for (auto it = item.Begin(); it != item.End(); ++it)
  {
    vtkDICOMTag oldTag = it->GetTag();
    unsigned int n = oldTag.GetElement();
    if (oldTag.GetGroup() != g || (n != sourceBlock && (n >> 8) != sourceBlock)) continue;
    unsigned int moved = n == sourceBlock ? dest : ((dest << 8) | (n & 0xff));
    query->Set(vtkDICOMTagPath(prefix, 0, vtkDICOMTag(g, moved)), it->GetValue());
    query->Set(vtkDICOMTagPath(prefix, 0, oldTag), vtkDICOMValue());
  }
  if (ql) RemapPaths(*ql, prefix, g, sourceBlock, dest);
  RemapPaths(query->AutoCreators, prefix, g, sourceBlock, dest);
  return true;
}

}

// Prototype for function that reads one query key
bool dicomcli_readkey_query(
  const char *cp, DICOMQueryItem *query, QueryTagList *ql,
  bool ql_unique, bool qfile, vtkDICOMTagPath *result = nullptr);

// Read a query file
bool dicomcli_readquery(
  const char *fname, DICOMQueryItem *query, QueryTagList *ql, bool ql_unique)
{
  QueryTagList local;
  if (!ql) ql = &local;
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
  const char *cp, DICOMQueryItem *query, QueryTagList *ql,
  bool ql_unique, bool qfile, vtkDICOMTagPath *result)
{
  // read the tag path
  vtkDICOMTagPath tagPath;
  vtkDICOMTagPath parentPath;
  std::string creator;
  size_t s = 0;
  size_t lineStart = s;
  size_t n = strlen(cp);
  bool tagError = false;
  const int maxerrlen = 80;

  // set the default character set to utf-8
  vtkDICOMCharacterSet cs(vtkDICOMCharacterSet::ISO_IR_192);

  while (!tagError)
  {
    creator.clear();
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

    if ((tag.GetGroup() & 1) && (!creator.empty() || tag.GetElement() >= 0x10) &&
        !ResolveQueryBlock(query, tagPath, tag, creator, ql))
    {
      fprintf(stderr, "Error: No available block in private group %04x.\n", tag.GetGroup());
      return false;
    }

    // build the tag path
    parentPath = tagPath;
    tagPath = vtkDICOMTagPath(tagPath, 0, tag);

    if (s < n && (cp[s] == '/' || cp[s] == '\\'))
    {
      // create an item for the next level of depth
      if (!query->Get(tagPath).IsValid())
      {
        query->Set(tagPath, vtkDICOMSequence(1));
      }
      s++;
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

  // if no dictionary VR, use UT to hold raw text
  if (!vr.IsValid() || vr == VR::UN)
  {
    vr = VR::UT;
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

  // Parse the complete replacement before deciding whether an automatic
  // creator must move out of a literal creator slot.
  vtkDICOMValue value = query->Get(tagPath);
  bool setValue = true;
  if (valueStart == valueEnd)
  {
    // only overwrite previous value if '=' was explicitly used
    if (keyHasAssignment || !query->Get(tagPath).IsValid())
    {
      // empty value (always matches, always retrieved)
      value = vtkDICOMValue(vr);
    }
    else setValue = false;
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
      value = vtkDICOMValue(vr, cs, sval);
    }
    else
    {
      value = vtkDICOMValue(vr, sval);
    }
  }
  else
  {
    if (vr.HasSpecificCharacterSet())
    {
      value = vtkDICOMValue(vr, cs, &cp[valueStart], valueEnd - valueStart);
    }
    else
    {
      value = vtkDICOMValue(vr, &cp[valueStart], valueEnd - valueStart);
    }
  }

  unsigned int element = tag.GetElement();
  if (creator.empty() && (tag.GetGroup() & 1) && element >= 0x10 && element < 0x100 &&
      !ResolveQueryBlock(query, parentPath, tag, creator, ql, &value))
  {
    fprintf(stderr, "Error: No available block in private group %04x.\n", tag.GetGroup());
    return false;
  }
  if (setValue) query->Set(tagPath, value);

  if (result) *result = tagPath;

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
  const char *cp, DICOMQueryItem *query, QueryTagList *ql, bool ql_unique)
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
  const char *fname, DICOMQueryItem *query, QueryTagList *ql)
{
  vtkDICOMFile f(fname, vtkDICOMFile::In);

  // Basic file structure:
  // # one or more comments
  // GGGG,EEEE   # a tag or key (only one)
  // 1.185.234   # a UID, followed by more UIDs

  QueryTagList local;
  if (!ql) ql = &local;
  vtkDICOMTagPath uidPath;
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

    if (uidPath.GetSize() == 0)
    {
      // get the tag line, if not gotten yet
      if (!dicomcli_readkey_query(cp, query, ql, true, true, &uidPath))
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

  if (uidPath.GetSize() > 0)
  {
    query->Set(uidPath, val);
  }

  return (f.GetError() == 0);
}

vtkDICOMTagPath dicomcli_resolve_tagpath(vtkDICOMMetaData* meta, int i,
  const vtkDICOMTagPath& tpath, const vtkDICOMItem *query)
{
  // the output path (will be resolved to the "meta" dataset)
  vtkDICOMTagPath mpath;
  // for nesting within "meta" dataset and "query" dataset
  const vtkDICOMItem *mitem = nullptr;
  const vtkDICOMItem *qitem = query;

  for (unsigned int depth = 0; depth < tpath.GetSize(); depth++)
  {
    vtkDICOMTag qtag = tpath.GetTag(depth);
    vtkDICOMTag mtag = qtag;
    if ((qtag.GetGroup() & 0x0001) == 1)
    {
      vtkDICOMTag ctag(qtag.GetGroup(), qtag.GetElement() >> 8);
      const vtkDICOMValue& creatorValue = qitem->Get(ctag);
      if (creatorValue.IsValid())
      {
        std::string creator = creatorValue.AsString();
        if (depth == 0)
        {
          mtag = meta->ResolvePrivateTag(i, qtag, creator);
        }
        else if (mitem)
        {
          mtag = mitem->ResolvePrivateTag(qtag, creator);
        }
      }
    }
    if (depth == 0)
    {
      mpath = vtkDICOMTagPath(mtag);
    }
    else
    {
      mpath = vtkDICOMTagPath(mpath, 0, mtag);
    }

    if (depth + 1 < tpath.GetSize())
    {
      const vtkDICOMValue *vptr = nullptr;
      if (depth == 0)
      {
        vptr = &meta->Get(i, mtag);
      }
      else if (mitem)
      {
        vptr = &mitem->Get(mtag);
      }
      if (vptr && vptr->IsValid())
      {
        // go one level deeper into the meta data
        if (vptr->GetNumberOfValues() > 0)
        {
          mitem = vptr->GetSequenceData();
        }
      }
      // go one level deeper into the query
      if (qitem && qitem->Get(qtag).GetNumberOfValues() > 0)
      {
        qitem = qitem->Get(qtag).GetSequenceData();
      }
    }
  }

  return mpath;
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
