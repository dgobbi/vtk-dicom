/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef mainmacro_h
#define mainmacro_h

//! Expand command line arguments for Windows command line.
/*!
 *  This will expand any wildcards in the arguments, and should usually
 *  only be applied on Windows because most UNIX shells will handle the
 *  wildcard expansion automatically.
 */
bool dicomcli_expandargs(
  int wargc, wchar_t *wargv[],
  int *argc_p, char ***argv_p);

//! A macro to use wmain on Windows.
#ifdef _WIN32
#define MAINMACRO(argc, argv) \
int main_with_utf8_args(int argc, char *argv[]); \
int wmain(int wargc, wchar_t *wargv[]) \
{ \
  int argc = 0; \
  char **argv = 0; \
  dicomcli_expandargs(wargc, wargv, &argc, &argv); \
  return main_with_utf8_args(argc, argv); \
} \
int main_with_utf8_args(int argc, char *argv[])
#else
#define MAINMACRO(argc, argv) \
int main(int argc, char *argv[])
#endif

#endif /* mainmacro_h */
