/*=========================================================================

  Copyright (c) 2015,2016 David Gobbi
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

  * Neither the name of David Gobbi nor the names of any contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

#include "mainmacro.h"

#include <stddef.h>

#ifdef _WIN32
#include <windows.h>
#endif

// A struct to arguments converted from UTF-16 to UTF-8.
#ifdef _WIN32
namespace {

class Arguments
{
public:
  // Construct with an empty argument list.
  Arguments() : m_Argc(0), m_Argv(0) {}

  // Destruct by freeing the memory.
  ~Arguments() {
    FreeStrings(&m_Argc, &m_Argv);
  }

  // Add the next arg (this is called by ExpandArgs).
  void Push(wchar_t *arg);

  // Expand args, result can be retrieved with GetArgc, GetArgv.
  bool ExpandArgs(int argc, wchar_t *argv[], const char *passthrough);

  // Get the argc and argv for the args.
  int GetArgc() { return m_Argc; }
  char **GetArgv() { return m_Argv; }

private:
  // Check if the given string matches the given wildcard pattern.
  static bool MatchesSpec(
    const wchar_t *val, size_t vl,
    const wchar_t *spec, size_t pl);

  // Get the power of two equal or greater than n.
  static size_t NearestPowerOfTwo(size_t n) {
    size_t m = ((n > 0) ? n - 1 : 0);
    m |= m >> 1;
    m |= m >> 2;
    m |= m >> 4;
    m |= m >> 8;
    m |= m >> 16;
#ifdef _WIN64
    m |= m >> 32;
#endif
    return m + 1;
  }

  // Check if n is a power of two.
  static bool IsPowerOfTwo(size_t n) {
    return (n > 0 && (n & (n - 1)) == 0);
  }

  // Create a string of length n and add it to the given array.
  template<class T>
  static T *NewString(size_t n, int *count, T ***strings) {
    T **array = *strings;
    (*count)++;
    if (array == 0) {
      size_t m = NearestPowerOfTwo(n);
      array = new T *[2];
      array[0] = new T[m];
      *strings = array;
    }
    else {
      if (IsPowerOfTwo(*count)) {
        T **newarray = new T *[*count * 2];
        for (int i = 0; i < *count; i++) {
          newarray[i] = array[i];
        }
        delete [] array;
        array = newarray;
        *strings = array;
      }
      size_t m = array[*count - 1] - array[0];
      if (m + n > NearestPowerOfTwo(m)) {
        T *cp = new T[NearestPowerOfTwo(m + n)];
        T *oldcp = array[0];
        for (size_t j = 0; j < m; j++) {
          cp[j] = oldcp[j];
        }
        for (int i = 0; i < *count; i++) {
          array[i] = cp + (array[i] - oldcp);
        }
        delete [] oldcp;
      }
    }

    array[*count] = array[*count - 1] + n;
    return array[*count - 1];
  }

  // Delete the array of strings.
  template<class T>
    static void FreeStrings(int *count, T ***strings) {
    if (*strings) {
      delete [] **strings;
      delete [] *strings;
    }
    *count = 0;
    *strings = 0;
  }

  int m_Argc;
  char **m_Argv;
};

bool Arguments::MatchesSpec(
  const wchar_t *val, size_t vl,
  const wchar_t *spec, size_t sl)
{
  // convert to lower case for case insensitivity
  wchar_t val_lower[MAX_PATH];
  wchar_t spec_lower[MAX_PATH];

  if (vl < MAX_PATH && sl < MAX_PATH) {
    for (size_t i = 0; i < vl; i++) {
      val_lower[i] = val[i];
    }
    for (size_t i = 0; i < sl; i++) {
      spec_lower[i] = spec[i];
    }

    if (CharLowerBuffW(val_lower, vl) == vl &&
        CharLowerBuffW(spec_lower, sl) == sl) {
      // if successful, use the lower-case strings
      spec = spec_lower;
      val = val_lower;
    }
  }

  // get pointers to the end of the strings
  const wchar_t *cp = spec;
  const wchar_t *ep = spec + sl;
  const wchar_t *dp = val;
  const wchar_t *fp = val + vl;

  while (cp != ep && dp != fp) {
    if (*cp == '*') {
      cp++;
      // if '*' is the final character, it matches the remainder of val
      if (cp == ep) {
        dp = fp;
      }
      else {
        while (dp != fp) {
          if (*cp == '?' || *dp == *cp) {
            // check if the remainder of val matches remainder of spec
            if (MatchesSpec(dp, fp-dp, cp, ep-cp)) {
              break;
            }
          }
          // else let the "*" eat one more codepoint of "val"
          if ((*dp++ & 0xFC00) == 0xD800) {
            if (dp != fp && (*dp & 0xFC00) == 0xDC00) {
              dp++;
            }
          }
        }
      }
    }
    else if (*cp == '?') {
      // the '?' matches a whole codepoint, not just one wchar
      cp++;
      if ((*dp++ & 0xFC00) == 0xD800) {
        if (dp != fp && (*dp & 0xFC00) == 0xDC00) {
          dp++;
        }
      }
    }
    else if (*cp == *dp) {
      // make sure the entire codepoint matches
      cp++;
      if ((*dp++ & 0xFC00) == 0xD800) {
        if (cp != ep && dp != fp &&
            ((*cp & 0xFC00) == 0xDC00 || (*dp & 0xFC00) == 0xDC00)) {
          if (*dp != *cp) {
            return false;
          }
          cp++;
          dp++;
        }
      }
    }
    else {
      return false;
    }
  }

  // skip over any remaining '*' wildcards
  while (cp != ep && *cp == '*') {
    cp++;
  }

  // make sure we've reached the end of both the spec and the value
  return (cp == ep && dp == fp);
}

void Arguments::Push(wchar_t *arg)
{
  int n = WideCharToMultiByte(
    CP_UTF8, 0, arg, -1, NULL, 0, NULL, NULL);
  char *cp = NewString(n, &m_Argc, &m_Argv);
  WideCharToMultiByte(
    CP_UTF8, 0, arg, -1, cp, n, NULL, NULL);
}

bool Arguments::ExpandArgs(int argc, wchar_t *argv[], const char *passthrough)
{
  WIN32_FIND_DATAW data;
  wchar_t *temp = 0;
  size_t tempsize = 0;
  bool expand_wildcards = true;

  for (int i = 0; i < argc; i++)
    {
    // for storing segments of the path that have wildcards
    int dirstart = 0;
    int dircount = 0;
    wchar_t **directories = 0;

    // check for wildcards
    bool has_wildcard = false;
    bool segment_has_wildcard = false;
    bool wildcard_expanded = false;
    bool path_is_complete = false;
    wchar_t *dp = argv[i];
    for (wchar_t *cp = dp; !path_is_complete; cp++) {
      if (expand_wildcards && (*cp == '\?' || *cp == '*')) {
        has_wildcard = true;
        segment_has_wildcard = true;
      }
      else if (*cp == '\\' || *cp == '/' || *cp == 0) {
        path_is_complete = (*cp == 0);
        // If path has a wildcard push all matching dirs onto a list.
        if (has_wildcard) {
          // Check if directory list is empty.
          if (dircount == 0) {
            // Push path segment (argv[i]..dp) onto the directory list.
            size_t l = dp - argv[i];
            wchar_t *ep = NewString(l, &dircount, &directories);
            for (size_t j = 0; j < l; j++) {
              ep[j] = argv[i][j];
            }
          }
          // Get the length of the path segment.
          size_t m = cp - dp;
          int prevcount = dircount;
          for (int k = dirstart; k < prevcount; k++) {
            // Length of the directory (including the "/").
            size_t l = directories[k + 1] - directories[k];
            if (l+m+1 > tempsize) {
              tempsize = l+m+9;
              delete [] temp;
              temp = new wchar_t[tempsize];
            }
            for (size_t j = 0; j < l; j++) {
              temp[j] = directories[k][j];
            }
            for (size_t j = 0; j < m; j++) {
              temp[l+j] = dp[j];
            }
            temp[l+m] = 0;
            // Find all existing directories.
            HANDLE hFile = FindFirstFileW(temp, &data);
            if (hFile != INVALID_HANDLE_VALUE) {
              do {
                if (!path_is_complete &&
                    (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                  // A directory was expected
                  continue;
                }
                if (data.cFileName[0] == '.' &&
                    (data.cFileName[1] == 0 ||
                     (data.cFileName[1] == '.' && data.cFileName[2] == 0))) {
                  // The found file was '.' or '..'
                  continue;
                }
                if (data.cFileName[0] == '.' && dp[0] != '.') {
                  // The found file began with '.' but the filespec did not.
                  continue;
                }
                // Append wildcard result to the directory.
                wchar_t *result;
                size_t n = 0;
                while (data.cFileName[n] != 0 && n < MAX_PATH) {
                  n++;
                }
                // Ensure that the true filename matches the wildcards.
                // (FindFirstFile, FindNextFile also match short filename)
                if (!MatchesSpec(data.cFileName, n, dp, cp-dp)) {
                  continue;
                }
                if (path_is_complete) {
                  // Expand into temporary string if path is complete.
                  if (l+n+1 > tempsize) {
                    tempsize = l+n+9;
                    delete [] temp;
                    temp = new wchar_t[tempsize];
                  }
                  result = temp;
                }
                else {
                  // Add result to directory list if path is not complete yet.
                  result = NewString(l+n+1, &dircount, &directories);
                }
                for (size_t j = 0; j < l; j++) {
                  result[j] = directories[k][j];
                }
                for (size_t j = 0; j < n; j++) {
                  result[l+j] = data.cFileName[j];
                }
                result[l+n] = *cp;
                // Push result onto the args if path is complete.
                if (path_is_complete) {
                  Push(result);
                  wildcard_expanded = true;
                }
              }
              while (FindNextFileW(hFile, &data));
              FindClose(hFile);
            }
          }
          dirstart = prevcount;
        }
        dp = cp + 1;
      }
    }
    // If no expansion could be done, push the argument as-is.
    if (!wildcard_expanded) {
      Push(argv[i]);
      if (passthrough) {
        expand_wildcards = true;
        // Check the arg against the expansion exclusion list.
        const char *arg = m_Argv[m_Argc-1];
        const char *ex = passthrough;
        while (*ex == ' ' || *ex == '\t') {
          ex++;
        }
        while (*ex != '\0') {
          const char *ee = ex;
          while (*ee != '\0' && *ee != ' ' && *ee != '\t') {
            ee++;
          }
          while (*arg != '\0' && ex != ee && *ex == *arg) {
            ex++;
            arg++;
          }
          if (*arg == '\0' && ex == ee) {
            // Do not expand wildcards in the next arg.
            expand_wildcards = false;
            break;
          }
          ex = ee;
          while (*ex == ' ' || *ex == '\t') {
            ex++;
          }
        }
      }
    }
    FreeStrings(&dircount, &directories);
  }
  delete [] temp;

  return true;
}

} // namespace

// A static variable to hold the arguments (will destruct on exit).
static Arguments mainmacro_arguments;
#endif /* _WIN32 */

// The function, with special definition for Windows.
#ifdef _WIN32
bool mainmacro_expandargs(
  int argc, wchar_t *argv[],
  int *argc_p, char ***argv_p,
  const char *passthrough)
{
  if (mainmacro_arguments.ExpandArgs(argc, argv, passthrough)) {
    *argc_p = mainmacro_arguments.GetArgc();
    *argv_p = mainmacro_arguments.GetArgv();
    return true;
  }
  return false;
}
#endif
