/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMConfig.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMDirectory.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMUtilities.h"

// from dicomcli
#include "vtkConsoleOutputWindow.h"
#include "mainmacro.h"
#include "readquery.h"

#include "vtkSortFileNames.h"
#include "vtkStringArray.h"
#include "vtkSmartPointer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <algorithm> // for std::min

#define MAX_INDENT 24
#define INDENT_SIZE 2

// for convenience when specifying VRs
typedef vtkDICOMVR VR;

// print the version
void printVersion(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2025, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void printUsage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s file1.dcm [file2.dcm ...]\n\n", cp);
  fprintf(file, "options:\n"
    "  -k tag          Provide a tag or key to be printed.\n"
    "  -q <query.txt>  Provide a file that lists which elements to print.\n"
    "  --charset <cs>  Charset to use if SpecificCharacterSet is missing.\n"
    "  --force-charset <cs> Force override of SpecificCharacterSet with <cs>.\n"
    "  --maxlen <l>    Maximum number of characters to print for a value.\n"
    "  --help          Print a brief help message.\n"
    "  --version       Print the software version.\n");
}

// print the help
void printHelp(FILE *file, const char *cp)
{
  printUsage(file, cp);
  fprintf(file, "\n"
    "Dump the metadata from a set of DICOM files as text.\n"
    "\n"
    "By default, all the attributes are dumped.  However, If only a few\n"
    "attributes are to be dumped, then their tags can be given with \"-k\"\n"
    "(the \"-k\" option can be repeated as many times as needed).  Tags can\n"
    "be given in hexadecimal GGGG,EEEE format, or in text format as specified\n"
    "in the DICOM dictionary key.  Alternatively, the tags can be listed in\n"
    "a query file given with the \"-q\" option (one tag per line).\n"
    "Attributes nested within sequences can be specified by giving a tag\n"
    "path e.g. \"-k Tag1/Tag2/Tag3\".  Either a forward slash or a backslash\n"
    "can be used to separate the components of the path.\n"
    "\n"
    "For text attribute values, any unprintable bytes will be replaced with\n"
    "the four characters \"\\nnn\", where \"nnn\" is the three digit octal code\n"
    "for the byte.  Unprintable bytes are control characters or bytes that\n"
    "cannot be decoded with the SpecificCharacterSet of the DICOM file.  A\n"
    "backslash itself will be replaced by its byte value \"\\134\" if the VR is\n"
    "ST, LT or UT (that is, any VR where backslash isn't used as a separator\n"
    "for multi-valued attributes).\n"
    "\n"
    "The \"--maxlen\" option sets the maximum number of characters to print for\n"
    "a value (default 120).  If the value is over this length, then it will be\n"
    "truncated and \"...\" will be appended.\n"
    "\n"
    "A warning of the form \"#(gggg,eeee) XX/YY explict/dictionary VR mismatch\"\n"
    "will be printed if any dataset element has an explicit VR that differs\n"
    "from dicomdump's internal dictionary.  This warning occurs most often for\n"
    "private elements, especially for old datasets.  It could indicate that the\n"
    "dictionary is wrong, or that the dataset conformed to a different revision\n"
    "of the dictionary, or that the dataset VR was incorrectly set.\n\n");
}

// remove path portion of filename
const char *fileBasename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// count code points in the output from ToSafeUTF8 up to a limit:
//     l = number of bytes in string (must not split last utf-8 sequence)
//     m = desired number of utf-8 code points
//     *mp = gives number of utf-8 code points read
//     returns number of input bytes read
// if return value == l after execution, end of string was reached
// if *mp == m after execution, reached desired utf-8 count
size_t countSafeUTF8(const char *cp, size_t l, size_t m, size_t *mp=nullptr)
{
  size_t remainingOctalDigits = 0;
  size_t codeCount = 0;
  size_t i;
  for (i = 0; i < l; i++)
  {
    if (remainingOctalDigits && cp[i] >= '0' && cp[i] <= '7')
    {
      --remainingOctalDigits;
    }
    else if ((cp[i] & 0xC0) != 0x80) // not a utf-8 trail byte
    {
      if (codeCount == m)
      {
        break;
      }
      codeCount++;
      // for SafeUTF8, backslash starts a three-digit octal byte code
      remainingOctalDigits = 0;
      if (cp[i] == '\\')
      {
        remainingOctalDigits = 3;
      }
    }
  }

  if (mp != nullptr)
  {
    *mp = codeCount;
  }

  return i;
}

// Print out one data element
void printElement(
  vtkDICOMMetaData *meta, const vtkDICOMItem *item,
  const vtkDICOMDataElementIterator &iter, int depth,
  unsigned int pixelDataVL, size_t maxlen)
{
  vtkDICOMTag tag = iter->GetTag();
  int g = tag.GetGroup();
  int e = tag.GetElement();
  vtkDICOMVR vr = iter->GetVR();
  const char *name = "";
  vtkDICOMDictEntry d;

  // make an indentation string
  if (INDENT_SIZE*depth > MAX_INDENT)
  {
    depth = MAX_INDENT/INDENT_SIZE;
  }
  static const char spaces[MAX_INDENT+1] = "                        ";
  const char *indent = spaces + (MAX_INDENT - INDENT_SIZE*depth);

  if (item)
  {
    d = item->FindDictEntry(tag);
  }
  else if (meta)
  {
    d = meta->FindDictEntry(tag);
  }
  if (d.IsValid())
  {
    name = d.GetName();
    if (d.GetVR() != vr &&
        !(d.GetVR() == vtkDICOMVR::XS &&
          (vr == vtkDICOMVR::SS || vr == vtkDICOMVR::US)) &&
        !(d.GetVR() == vtkDICOMVR::OX &&
          (vr == vtkDICOMVR::OB || vr == vtkDICOMVR::OW)))
    {
      printf("%s#(%04X,%04X) %s/%s explicit/dictionary VR mismatch\n",
             indent, g, e, vr.GetText(), d.GetVR().GetText());
    }
  }
  else if ((tag.GetGroup() & 0xFFFE) != 0 && tag.GetElement() == 0)
  {
    // group is even, element is zero
    name = "GroupLength";
  }
  else if ((tag.GetGroup() & 0x0001) != 0 &&
           (tag.GetElement() & 0xFF00) == 0)
  {
    // group is odd, element is a creator element
    name = "PrivateCreator";
  }
  // allow multiple values (i.e. for each image in series)
  vtkDICOMValue v = iter->GetValue();
  size_t vn = v.GetNumberOfValues();
  const vtkDICOMValue *vp = v.GetMultiplexData();
  if (vp == nullptr)
  {
    vp = &v;
    vn = 1;
  }

  for (size_t vi = 0; vi < vn; vi++)
  {
    v = vp[vi];
    unsigned int vl = v.GetVL();
    if (tag == DC::PixelData ||
        tag == DC::FloatPixelData ||
        tag == DC::DoubleFloatPixelData)
    {
      vl = (depth == 0 && vl == 0 ? pixelDataVL : v.GetVL());
    }
    std::string s;
    if (vr == vtkDICOMVR::UN ||
        vr == vtkDICOMVR::SQ)
    {
      // sequences are printed later
      s = (vl > 0 ? "..." : "");
    }
    else if (vr == vtkDICOMVR::LT ||
             vr == vtkDICOMVR::ST ||
             vr == vtkDICOMVR::UT)
    {
      vtkDICOMCharacterSet cs = v.GetCharacterSet();
      bool simpleSingleByte = (cs.IsISO8859() ||
                               cs == vtkDICOMCharacterSet::ISO_IR_6 ||
                               cs == vtkDICOMCharacterSet::ISO_IR_13);
      const char *cp = v.GetCharData();
      size_t l = vl;
      while (l > 0 && cp[l-1] == ' ')
      {
        l--;
      }
      if (l > maxlen)
      {
        // loop, increasing ltry each time
        for (size_t ltry = maxlen;; ltry += std::min(l - ltry, maxlen))
        {
          if (!simpleSingleByte)
          {
            // ensure that 'ltry' does not split a character code, by
            // advancing to just before the next space or control code
            while (ltry < l && static_cast<unsigned char>(cp[ltry]) > 0x20)
            {
              ltry++;
            }
          }
          // create utf8 string and compare to max allowed output length
          s = cs.ToSafeUTF8(cp, ltry);
          size_t n;
          size_t m = countSafeUTF8(s.data(), s.size(), maxlen, &n);
          if (n == maxlen && (m < s.size() || ltry < l))
          {
            s.resize(m);
            s.append("...");
            break;
          }
          if (ltry == l)
          {
            break;
          }
        }
      }
      else
      {
        s = cs.ToSafeUTF8(cp, l);
      }
    }
    else if (vr.HasTextValue())
    {
      vtkDICOMCharacterSet cs = v.GetCharacterSet();
      const char *cp = v.GetCharData();
      const char *ep = cp + vl;
      size_t pos = 0;
      size_t posCount = 0;
      while (cp != ep && *cp != '\0')
      {
        // locate the next separator
        size_t n = cs.NextBackslash(cp, ep);
        // strip leading, trailing whitespace
        while (n > 0 && *cp == ' ') { cp++; n--; }
        size_t m = n;
        while (m > 0 && cp[m-1] == ' ') { m--; }
        // perform charset conversion (if needed) and advance
        s.append(cs.ToSafeUTF8(cp, m));
        cp += n;
        // count the number of unicode code points for this value
        size_t addCount;
        size_t ll = countSafeUTF8(s.data() + pos, s.size() - pos,
                                  maxlen - posCount, &addCount);
        // check if truncation is required
        if (s.size() > pos + ll)
        {
          s.resize(pos + ll);
          s.append("...");
          break;
        }
        // get current position in utf-8 string, and number of code points
        pos = s.size();
        posCount += addCount;
        // add the separator
        if (cp != ep && *cp == '\\')
        {
          if (posCount < maxlen)
          {
            s.append(cp, 1);
            cp++;
            posCount++;
          }
          else
          {
            s.append("...");
            break;
          }
        }
      }
    }
    else
    {
      // print any other VR via conversion to string
      size_t n = v.GetNumberOfValues();
      for (size_t i = 0; i < n; i++)
      {
        v.AppendValueToString(s, i);
        if (i < n - 1)
        {
          s.append("\\");
        }
        if (s.size() > maxlen)
        {
          s.resize(maxlen);
          s.append("...");
          break;
        }
      }
    }

    if (meta && vi == 0)
    {
      printf("%s(%04X,%04X) %s \"%s\" :", indent, g, e, vr.GetText(), name);
    }
    if (meta && vn > 1)
    {
      printf("%s%s  %4.4u",
        (vi == 0 ? " (multiple values)\n" : ""), indent,
        static_cast<unsigned int>(vi + 1));
    }
    if (vr == vtkDICOMVR::SQ)
    {
      size_t m = v.GetNumberOfValues();
      const vtkDICOMItem *items = v.GetSequenceData();
      printf(" (%u %s%s)\n",
        static_cast<unsigned int>(m), (m == 1 ? "item" : "items"),
        (vl == 0xffffffffu ? ", delimited" : ""));
      for (size_t j = 0; j < m; j++)
      {
        printf("%s%s---- SQ Item %04u at offset %u ----\n",
          indent, spaces+(MAX_INDENT - INDENT_SIZE),
          static_cast<unsigned int>(j+1),
          items[j].GetByteOffset());
        vtkDICOMDataElementIterator siter = items[j].Begin();
        vtkDICOMDataElementIterator siterEnd = items[j].End();

        for (; siter != siterEnd; ++siter)
        {
          printElement(meta, &items[j], siter, depth+1, pixelDataVL, maxlen);
        }
      }
    }
    else if (vl == 0xffffffffu)
    {
      if (tag == DC::PixelData ||
          tag == DC::FloatPixelData ||
          tag == DC::DoubleFloatPixelData)
      {
        printf(" [...] (compressed)\n");
      }
      else
      {
        printf(" [...] (delimited)\n");
      }
    }
    else
    {
      const char *uidName = "";
      if (vr == vtkDICOMVR::UI)
      {
        uidName = vtkDICOMUtilities::GetUIDName(s.c_str());
      }
      if (uidName[0] != '\0')
      {
        printf(" [%s] {%s} (%u bytes)\n", s.c_str(), uidName, vl);
      }
      else if (vr == vtkDICOMVR::OB ||
               vr == vtkDICOMVR::OW ||
               vr == vtkDICOMVR::OF ||
               vr == vtkDICOMVR::OD)
      {
        printf(" [%s] (%u bytes)\n", (vl == 0 ? "" : "..."), vl);
      }
      else
      {
        printf(" [%s] (%u bytes)\n", s.c_str(), vl);
      }
    }
  }
}

void printElementFromTagPathRecurse(
  const vtkDICOMItem *item, const vtkDICOMTagPath& tagPath,
  const vtkDICOMTagPath& fullPath, int *count, size_t maxlen)
{
  vtkDICOMTag tag = tagPath.GetHead();

  vtkDICOMDataElementIterator iter = item->Begin();
  while (iter != item->End() && iter->GetTag() != tag)
  {
    ++iter;
  }

  if (iter != item->End())
  {
    if (tagPath.HasTail())
    {
      const vtkDICOMItem *items = iter->GetValue().GetSequenceData();
      if (items)
      {
        size_t n = iter->GetValue().GetNumberOfValues();
        for (size_t i = 0; i < n; i++)
        {
          printElementFromTagPathRecurse(
            &items[i], tagPath.GetTail(), fullPath, count, maxlen);
        }
      }
    }
    else
    {
      ++(*count);
      fprintf(stdout, "  %04d", *count);
      printElement(nullptr, item, iter, 0, 0, maxlen);
    }
  }
}

void printElementFromTagPath(
  vtkDICOMMetaData *data, const vtkDICOMTagPath& tagPath,
  unsigned int pixelDataVL, size_t maxlen)
{
  int count = 0;
  vtkDICOMTag tag = tagPath.GetHead();
  vtkDICOMDataElementIterator iter = data->Find(tag);
  if (iter != data->End())
  {
    if (tagPath.HasTail())
    {
      for (vtkDICOMTagPath p = tagPath; ; p = p.GetTail())
      {
        int g = p.GetHead().GetGroup();
        int e = p.GetHead().GetElement();
        if (p.HasTail())
        {
          printf("(%04X,%04X)\\", g, e);
        }
        else
        {
          vtkDICOMDictEntry entry =
            vtkDICOMDictionary::FindDictEntry(p.GetHead());
          vtkDICOMVR vr = entry.GetVR();
          const char *name = entry.GetName();
          name = ((name && name[0]) ? name : "Unknown");
          printf("(%04X,%04X) %s \"%s\" : (nested)\n",
            g, e, vr.GetText(), name);
          break;
        }
      }
      if (iter->IsPerInstance())
      {
        for (int j = 0; j < iter->GetNumberOfInstances(); j++)
        {
          const vtkDICOMItem *items = iter->GetValue(j).GetSequenceData();
          if (items)
          {
            size_t n = iter->GetValue(j).GetNumberOfValues();
            for (size_t i = 0; i < n; i++)
            {
              printElementFromTagPathRecurse(
                &items[i], tagPath.GetTail(), tagPath, &count, maxlen);
            }
          }
        }
      }
      else
      {
        const vtkDICOMItem *items = iter->GetValue().GetSequenceData();
        if (items)
        {
          size_t n = iter->GetValue().GetNumberOfValues();
          for (size_t i = 0; i < n; i++)
          {
            printElementFromTagPathRecurse(
              &items[i], tagPath.GetTail(), tagPath, &count, maxlen);
          }
        }
      }
    }
    else
    {
      printElement(data, nullptr, iter, 0, pixelDataVL, maxlen);
    }
  }
}

// This program will dump all the metadata in the given file
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

  int rval = 0;

  // for the optional query file
  QueryTagList qtlist;
  vtkDICOMItem query;

  // always query SpecificCharacterSet
  query.Set(DC::SpecificCharacterSet, vtkDICOMValue(VR::CS));

  // for the default character set
  vtkDICOMCharacterSet charset;
  bool forceCharset = false;

  // for the maximum value length to print
  size_t maxlen = 120;

  if (argc < 2)
  {
    printUsage(stdout, fileBasename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
  {
    printHelp(stdout, fileBasename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--version") == 0)
  {
    printVersion(stdout, fileBasename(argv[0]));
    return rval;
  }

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  for (int argi = 1; argi < argc; argi++)
  {
    const char *arg = argv[argi];
    if (strcmp(arg, "-q") == 0 || strcmp(arg, "-o") == 0)
    {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
      {
        fprintf(stderr, "%s must be followed by a file.\n\n", arg);
        printUsage(stderr, fileBasename(argv[0]));
        return 1;
      }

      if (arg[1] == 'q')
      {
        const char *qfile = argv[++argi];
        if (!dicomcli_readquery(qfile, &query, &qtlist))
        {
          fprintf(stderr, "Can't read query file %s\n\n", qfile);
          return 1;
        }
      }
      else if (arg[1] == 'o')
      {
        fprintf(stderr, "unrecognized option %s.\n\n", arg);
        return 1;
      }
    }
    else if (strcmp(arg, "-k") == 0)
    {
      ++argi;
      if (argi == argc || argv[argi][0] == '-')
      {
        fprintf(stderr, "%s must be followed by gggg,eeee=value "
                        "where gggg,eeee is a DICOM tag.\n\n", arg);
        return 1;
      }
      if (!dicomcli_readkey(argv[argi], &query, &qtlist))
      {
        return 1;
      }
    }
    else if (strcmp(arg, "--charset") == 0 ||
             strcmp(arg, "--force-charset") == 0)
    {
      ++argi;
      if (argi == argc || argv[argi][0] == '-')
      {
        fprintf(stderr, "%s must be followed by a valid character set\n\n",
                arg);
        return 1;
      }
      if (strncmp(arg, "--force-", 8) == 0)
      {
        forceCharset = true;
      }
      charset = vtkDICOMCharacterSet(argv[argi]);
      if (charset.GetKey() == vtkDICOMCharacterSet::Unknown)
      {
        fprintf(stderr, "%s %s is not a known character set\n\n",
                arg, argv[argi]);
        return 1;
      }
    }
    else if (strcmp(arg, "--maxlen") == 0)
    {
      ++argi;
      if (argi == argc || argv[argi][0] == '-' ||
          argv[argi][0] < '0' || argv[argi][0] > '9')
      {
        fprintf(stderr, "%s must be followed by an integer\n\n",
                arg);
        return 1;
      }
      maxlen = atol(argv[argi]);
      if (maxlen >= 0xffffffff)
      {
        maxlen = 0xffffffff;
      }
    }
    else if (arg[0] == '-')
    {
      fprintf(stderr, "unrecognized option %s.\n\n", arg);
      printUsage(stderr, fileBasename(argv[0]));
      return 1;
    }
    else
    {
      files->InsertNextValue(arg);
    }
  }

  // sort the files by study and series
  vtkSmartPointer<vtkDICOMDirectory> sorter;
  bool useSorter = false;
  if (files->GetNumberOfValues() > 1)
  {
    useSorter = true;
    sorter = vtkSmartPointer<vtkDICOMDirectory>::New();
    sorter->RequirePixelDataOff();
    sorter->SetScanDepth(0);
    sorter->IgnoreDicomdirOn();
    if (!qtlist.empty())
    {
      sorter->SetFindQuery(query);
    }
    sorter->SetInputFileNames(files);
    sorter->Update();
  }

  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();
  parser->SetDefaultCharacterSet(charset);
  parser->SetOverrideCharacterSet(forceCharset);
  if (!qtlist.empty())
  {
    parser->SetQueryItem(query);
  }

  vtkSmartPointer<vtkDICOMMetaData> data =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  parser->SetMetaData(data);

  int m = (files->GetNumberOfValues() > 0 ? 1 : 0);
  if (useSorter)
  {
    m = sorter->GetNumberOfStudies();
  }
  for (int j = 0; j < m; j++)
  {
    int k = 0;
    int kmax = 0;
    if (useSorter)
    {
      k = sorter->GetFirstSeriesForStudy(j);
      kmax = sorter->GetLastSeriesForStudy(j);
    }
    for (; k <= kmax; k++)
    {
      vtkStringArray *a = files;
      if (useSorter)
      {
        a = sorter->GetFileNamesForSeries(k);
      }
      vtkIdType l = a->GetNumberOfValues();
      std::string fname = a->GetValue(0);
      if (l == 1)
      {
        printf("==== %s ====\n", fname.c_str());
      }
      else
      {
        // print the first and last filenames (sorted)
        vtkSmartPointer<vtkSortFileNames> fsort =
          vtkSmartPointer<vtkSortFileNames>::New();
        fsort->NumericSortOn();
        fsort->IgnoreCaseOn();
        fsort->GroupingOff();
        fsort->SetInputFileNames(a);
        fsort->Update();
        printf("==== %s .. %s (%d files) ====\n",
          fsort->GetFileNames()->GetValue(0).c_str(),
          fileBasename(fsort->GetFileNames()->GetValue(l-1).c_str()),
          static_cast<int>(l));
      }

      data->Clear();
      data->SetNumberOfInstances(static_cast<int>(l));

      unsigned int pixelDataVL = 0;
      for (vtkIdType i = 0; i < l; i++)
      {
        fname = a->GetValue(i);
        parser->SetIndex(i);
        parser->SetFileName(fname.c_str());
        parser->Update();
        pixelDataVL = parser->GetPixelDataVL();
      }

      if (!qtlist.empty())
      {
        for (size_t i = 0; i < qtlist.size(); i++)
        {
          // TODO: resolving the path here, instead of during
          // the iteration along the path, means that the
          // instance (or item #) used for resolution might
          // be different than the one being printed
          vtkDICOMTagPath mpath = dicomcli_resolve_tagpath(
            data, 0, qtlist[i], &query);
          printElementFromTagPath(data, mpath, pixelDataVL, maxlen);
        }
      }
      else
      {
        vtkDICOMDataElementIterator iter = data->Begin();
        vtkDICOMDataElementIterator iterEnd = data->End();

        for (; iter != iterEnd; ++iter)
        {
          printElement(data, nullptr, iter, 0, pixelDataVL, maxlen);
        }
      }
    }
  }

  return rval;
}
