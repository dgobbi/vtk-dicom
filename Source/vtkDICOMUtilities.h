/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMUtilities_h
#define vtkDICOMUtilities_h

#include "vtkObject.h"
#include "vtkStdString.h" // For std::string
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMTag.h" // For method parameter

class vtkStringArray;

//! Utility functions for use with DICOM classes.
class VTKDICOM_EXPORT vtkDICOMUtilities : public vtkObject
{
public:
  //@{
  //! VTK new method (for Java and Tcl wrappers)
  static vtkDICOMUtilities *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMUtilities, vtkObject);

  //! Print a summary of the contents of this object.
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
#endif
  //@}

  //@{
  //! Set a UID prefix to use when generating UIDs.
  /*!
   *  This is optional, if you do not own a UID prefix then the publicly
   *  available 2.25 prefix will be used.
   */
  static void SetUIDPrefix(const char *prefix);
  static const char *GetUIDPrefix();
  //@}

  //@{
  //! Generate a UID for the provided tag.
  static std::string GenerateUID(vtkDICOMTag tag);

  //! Generate a series of UIDs, sorted from low to high.
  /*!
   *  Before passing the string array, call SetNumberOfValues() on
   *  the array to specify the number of UIDs that you want to be
   *  stored in it.  The stored UIDs will be sorted, low to high.
   *  Generating a batch of UIDs is more efficient than calling
   *  GenerateUID() repeatedly.
   */
  static void GenerateUIDs(vtkDICOMTag tag, vtkStringArray *uids);

  //! Numerically compare two UIDs, returns -1, 0, or +1.
  static int CompareUIDs(const char *u1, const char *u2);
  //@}

  //@{
  //! Generate a DICOM date time string in the given timezone.
  /*!
   *  The time zone is to be given in the DICOM format of
   *  +HHMM or -HHMM where HH is the hour offset and MM is the
   *  minute offset.  If no time zone is given, then local time
   *  is used (according to the computer's time zone preferences).
   */
  static std::string GenerateDateTime(const char *zone);

  //! Generate a DICOM date time string from long integer.
  /*!
   *  Given an integer number of microseconds since the UNIX epoch
   *  (00:00:00 UTC on 1 Jan 1970), return a DICOM date time string
   *  for the given time zone.  The time zone should be given in the
   *  format +HHMM or -HHMM.  If no time zone is given, then the local
   *  zone is used (according to the computer's time zone preferences).
   */
  static std::string GenerateDateTime(long long microsecs, const char *zone);

  //! Convert a DICOM data time string into a long integer.
  /*!
   *  Given a DICOM date time string, generate a long integer that counts
   *  microseconds since the UNIX epoch (00:00:00 UTC on 1 Jan 1970).
   *  If the datetime string contains a timezone offset, then that timezone
   *  is used to convert the time to UTC.  Otherwise, the local timezone
   *  (according to the computer's timezone preferences) is used to
   *  convert the time to UTC.  The return value is always intended to be
   *  interpreted as a UTC time.
   */
  static long long ConvertDateTime(const char *datetime);

  //! Get the current time in microseconds.
  /*!
   *  The time is in microseconds since the UNIX epoch (00:00:00 UTC on
   *  1 Jan 1970).
   */
  static long long GetUniversalTime();
  //@}

  //! Deprecated method, do not use.
  static long long GetUTC(long long *offset);

  //@{
  //! Check if the specified file is a DICOM file.
  /*!
   *  This will return true if the file exists, is readable, and
   *  if it has the DICM magic number or if the first few bytes of
   *  the file look like DICOM data elements.
   */
  static bool IsDICOMFile(const char *filename);
  //@}

  //@{
  //! Get the UID for this DICOM implementation.
  static const char *GetImplementationClassUID();

  //! Set the UID for this DICOM implementation.
  /*!
   *  The supplied UID will be copied into a static storage area,
   *  and used for all future calls to GetImplementationClassUID.
   *  The ImplementationClassUID appears in the DICOM meta header.
   */
  static void SetImplementationClassUID(const char *uid);

  //! Get the versioned name for this DICOM implementation.
  static const char *GetImplementationVersionName();

  //! Set the versioned name for this DICOM implementation.
  /*!
   *  The supplied name will be copied into a static storage area,
   *  and used for all future calls to GetImplementationVersionName.
   *  The ImplementationVersionName appears in the DICOM meta header.
   */
  static void SetImplementationVersionName(const char *name);
  //@}

  //@{
  //! Unpack one little-endian int from a stream of bytes.
  /*!
   *  This is a very common operation that is required in many different
   *  classes, so the code is centralized here.
   */
  static unsigned int UnpackUnsignedInt(const unsigned char *cp) {
    return cp[0] + (cp[1] << 8) + (cp[2] << 16) + (cp[3] << 24); }

  //! Pack one little-endian int into a stream of bytes.
  /*!
   *  This is a very common operation that is required in many different
   *  classes, so the code is centralized here.
   */
  static void PackUnsignedInt(unsigned int i, unsigned char *cp) {
    cp[0] = static_cast<unsigned char>(i);
    cp[1] = static_cast<unsigned char>(i >> 8);
    cp[2] = static_cast<unsigned char>(i >> 16);
    cp[3] = static_cast<unsigned char>(i >> 24); }
  //@}

  //@{
  //! Return true if the pattern matches the given string (utf-8).
  /*!
   *  This performs simple matching with "*" and "?" as the only wildcard.
   *  The input must either be ASCII or utf-8, and if it is utf-8, then
   *  matching will be done codepoint by codepoint.
   */
  static bool PatternMatches(const char *pattern, const char *val);

  //! Match patterns on non-terminated strings.
  static bool PatternMatches(
    const char *pattern, size_t pl, const char *val, size_t vl);
  //@}

  //@{
  //! Check that a string is valid utf-8.
  /*!
   *  The string is valid if it contains no NULL bytes and if it contains
   *  only valid 1-byte, 2-byte, 3-byte, or 4-byte utf-8 sequences.  Any
   *  overlength sequences or sequences that encode values above U+10FFFF
   *  or between U+D800 and U+DFFF are considered invalid.
   */
  static bool IsValidUTF8(const char *text, size_t l);
  //@}

  //@{
  //! Get the name associated with the given UID.
  static const char *GetUIDName(const char *uid);

  //! Get the CID from the UID.
  unsigned short GetCIDFromUID(const char *uid);
  //@}

protected:
  vtkDICOMUtilities() {}
  ~vtkDICOMUtilities() {}

  static long long GetLocalOffset(long long t);

  static char UIDPrefix[64];
  static char ImplementationClassUID[65];
  static char ImplementationVersionName[17];

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMUtilities(const vtkDICOMUtilities&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMUtilities&) VTK_DELETE_FUNCTION;
#elif __cplusplus >= 201103L
  vtkDICOMUtilities(const vtkDICOMUtilities&) = delete;
  void operator=(const vtkDICOMUtilities&) = delete;
#else
  vtkDICOMUtilities(const vtkDICOMUtilities&);
  void operator=(const vtkDICOMUtilities&);
#endif
};

#endif /* vtkDICOMUtilities_h */
