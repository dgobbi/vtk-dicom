#include "readquery.h"
#include "vtkDICOMSequence.h"
#include <iostream>
#include <string>

// Compile the same regression source against the prior reviewed CLI as well.
#ifdef DICOMCLI_QUERY_ITEM
typedef DICOMQueryItem QueryItem;
#else
typedef vtkDICOMItem QueryItem;
#endif

static vtkDICOMItem itemAt(const vtkDICOMItem& query, bool nested)
{
  if (nested)
  {
    vtkDICOMSequence seq = query.Get(DC::IconImageSequence);
    if (seq.GetNumberOfItems() != 1) return vtkDICOMItem();
    return seq.GetItem(0);
  }
  return query;
}

static bool check(bool namedFirst, bool nested, bool sameLowByte, bool display)
{
  QueryItem query;
  QueryTagList paths;
  QueryTagList *p = display ? &paths : nullptr;
  const std::string prefix = nested ? "0088,0200/" : "";
  const std::string first = prefix + "0029,1034:CS=RAW";
  const std::string second = prefix + "0029,1134:CS=OTHER";
  const unsigned short low = sameLowByte ? 0x34 : 9;
  const std::string named = prefix + "[SYNTHETIC CREATOR]0029," +
    (sameLowByte ? "0034" : "0009") + ":CS=NAMED";
  if (namedFirst && !dicomcli_readkey(named.c_str(), &query, p)) return false;
  if (!dicomcli_readkey(first.c_str(), &query, p) ||
      !dicomcli_readkey(second.c_str(), &query, p)) return false;
  if (!namedFirst && !dicomcli_readkey(named.c_str(), &query, p)) return false;
  vtkDICOMItem item = itemAt(query, nested);
  vtkDICOMTag resolved = item.ResolvePrivateTag(vtkDICOMTag(0x29, low), "SYNTHETIC CREATOR");
  if (resolved.GetGroup() != 0x29 || (resolved.GetElement() >> 8) < 0x12) return false;
  if (item.Get(vtkDICOMTag(0x29, 0x10)).IsValid() ||
      item.Get(vtkDICOMTag(0x29, 0x11)).IsValid()) return false;
  if (item.Get(vtkDICOMTag(0x29, 0x1034)).AsString() != "RAW" ||
      item.Get(vtkDICOMTag(0x29, 0x1134)).AsString() != "OTHER" ||
      item.Get(resolved).AsString() != "NAMED") return false;
  if (!display) return paths.empty();
  return paths.size() == 3 &&
    query.Get(paths[namedFirst ? 0 : 2]).AsString() == "NAMED" &&
    query.Get(paths[namedFirst ? 1 : 0]).AsString() == "RAW" &&
    query.Get(paths[namedFirst ? 2 : 1]).AsString() == "OTHER";
}

static bool creatorCheck(bool namedFirst, bool nested, bool sameName, bool display)
{
  QueryItem query;
  QueryTagList paths;
  QueryTagList *p = display ? &paths : nullptr;
  const std::string prefix = nested ? "0088,0200/" : "";
  const std::string name = sameName ? "CREATOR A" : "CREATOR B";
  const std::string named = prefix + "[CREATOR A]0029,0009:CS=NAMED";
  const std::string literal = prefix + "0029,0010:LO=" + name;
  if (namedFirst && !dicomcli_readkey(named.c_str(), &query, p)) return false;
  if (!dicomcli_readkey(literal.c_str(), &query, p)) return false;
  if (!namedFirst && !dicomcli_readkey(named.c_str(), &query, p)) return false;
  // A literal declaration is pinned, so later raw data belongs to that slot.
  const std::string raw = prefix + "0029,100a:CS=RAW";
  if (!dicomcli_readkey(raw.c_str(), &query, p)) return false;
  vtkDICOMItem item = itemAt(query, nested);
  vtkDICOMTag resolved = item.ResolvePrivateTag(vtkDICOMTag(0x29, 9), "CREATOR A");
  if (resolved != vtkDICOMTag(0x29, sameName ? 0x1009 : 0x1109) ||
      item.Get(vtkDICOMTag(0x29, 0x10)).AsString() != name ||
      item.Get(resolved).AsString() != "NAMED" ||
      item.Get(vtkDICOMTag(0x29, 0x100a)).AsString() != "RAW") return false;
  if (!display) return paths.empty();
  return paths.size() == 3 &&
    query.Get(paths[namedFirst ? 0 : 1]).AsString() == "NAMED" &&
    query.Get(paths[namedFirst ? 1 : 0]).AsString() == name &&
    query.Get(paths[2]).AsString() == "RAW";
}

static bool copyAndClearCheck()
{
  QueryItem original;
  if (!dicomcli_readkey("[CREATOR A]0029,0009:CS=NAMED", &original)) return false;
  QueryItem copy = original;
  if (!dicomcli_readkey("0029,100a:CS=RAW", &copy)) return false;
  if (original.ResolvePrivateTag(vtkDICOMTag(0x29, 9), "CREATOR A") != vtkDICOMTag(0x29, 0x1009) ||
      copy.ResolvePrivateTag(vtkDICOMTag(0x29, 9), "CREATOR A") != vtkDICOMTag(0x29, 0x1109) ||
      original.Get(vtkDICOMTag(0x29, 0x100a)).IsValid()) return false;
  copy.Clear();
  return dicomcli_readkey("0029,100a:CS=RAW", &copy) &&
    dicomcli_readkey("[CREATOR A]0029,0009:CS=NAMED", &copy) &&
    copy.Get(vtkDICOMTag(0x29, 0x100a)).AsString() == "RAW" &&
    copy.ResolvePrivateTag(vtkDICOMTag(0x29, 9), "CREATOR A") == vtkDICOMTag(0x29, 0x1109);
}

int main(int argc, char *argv[])
{
  const std::string mode = argc > 1 ? argv[1] : "all";
  if (mode != "all" && mode != "ordinary" && mode != "creators") return 2;
  if (mode == "all" || mode == "ordinary")
    for (int display = 0; display < 2; ++display)
      for (int order = 0; order < 2; ++order)
        for (int nested = 0; nested < 2; ++nested)
          for (int overlap = 0; overlap < 2; ++overlap)
            if (!check(order != 0, nested != 0, overlap != 0, display != 0))
            {
              std::cerr << "Private query collision: order=" << order << " nested=" << nested
                        << " matching low byte=" << overlap << " display=" << display << "\n";
              return 1;
            }
  if (mode == "all" || mode == "creators")
    for (int display = 0; display < 2; ++display)
      for (int order = 0; order < 2; ++order)
        for (int nested = 0; nested < 2; ++nested)
          for (int matching = 0; matching < 2; ++matching)
            if (!creatorCheck(order != 0, nested != 0, matching != 0, display != 0))
            {
              std::cerr << "Literal creator collision: order=" << order << " nested=" << nested
                        << " matching name=" << matching << " display=" << display << "\n";
              return 1;
            }
  if (mode == "all" && !copyAndClearCheck())
  {
    std::cerr << "Query copy/clear provenance failure\n";
    return 1;
  }
  std::cout << "Private query controls passed: " << mode << "\n";
  return 0;
}
