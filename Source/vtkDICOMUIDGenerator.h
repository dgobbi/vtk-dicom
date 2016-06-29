/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2016 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMUIDGenerator_h
#define vtkDICOMUIDGenerator_h

#include <vtkObject.h>
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMTag.h" // For method parameter

class vtkStringArray;

//! Generate UIDs for written DICOM files.
/*!
 *  This class generates UIDs that begin with a specified prefix, and are
 *  are followed by a sequence of digits that are sufficiently random that
 *  the possibility of UID collisions is vanishingly small.  The default
 *  prefix 2.25. (which can be used by anyone) is followed by a 128-bit
 *  random number.  Other prefixes (which can only be used by a designated
 *  organization) are followed by a 128-bit random number if the prefix is
 *  shorter than 24 chars, or a 96-bit random number if the prefix is 24
 *  chars or longer.
 */
class VTKDICOM_EXPORT vtkDICOMUIDGenerator : public vtkObject
{
public:
  //! Static method for construction.
  //@{
  static vtkDICOMUIDGenerator *New();
  vtkTypeMacro(vtkDICOMUIDGenerator, vtkObject);
  //@}

  //! Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  //@{
  //! Set a UID prefix to use when generating UIDs.
  /*!
   *  If this is not set, or if it is set to NULL, then the default
   *  prefix set via vtkDICOMUtilities::SetUIDPrefix() will be used.
   *  Its default is the 2.25. prefix.
   */
  void SetUIDPrefix(const char *prefix);

  //! Get the current UID prefix.
  /*!
   *  If no prefix was set, then this will return the same value as
   *  vtkDICOMUtilities::GetUIDPrefix().
   */
  const char *GetUIDPrefix();
  //@}

  //@{
  //! Generate a UID for the provided tag.
  /*
   *  The generator uses the tag as a hint when generating the UIDs,
   *  for example the SOPInstanceUID might have a different format from
   *  the FrameOfReferenceUID.
   */
  virtual std::string GenerateUID(vtkDICOMTag tag);

  //! Generate a series of UIDs, sorted from low to high.
  /*!
   *  Before passing the string array, call SetNumberOfValues() on
   *  the array to specify the number of UIDs that you want to be
   *  stored in it.  The stored UIDs will be sorted, low to high.
   *  Generating a batch of UIDs is more efficient than calling
   *  GenerateUID() repeatedly.
   */
  virtual void GenerateUIDs(vtkDICOMTag tag, vtkStringArray *uids);
  //@}

  //@{
  //! Set the default UID generator.
  /*!
   *  This can be used to set an application-wide UID generator.
   */
  static void SetDefault(vtkDICOMUIDGenerator *uidgen);

  //! Get the default UID generator.
  static vtkDICOMUIDGenerator *GetDefault() {
    return vtkDICOMUIDGenerator::Default; }
  //@}

protected:
  vtkDICOMUIDGenerator();
  ~vtkDICOMUIDGenerator();

  char *UIDPrefix;
  char UIDPrefixStore[64];
  static vtkDICOMUIDGenerator *Default;

private:
  friend class vtkDICOMUIDGeneratorInitializer;

  vtkDICOMUIDGenerator(const vtkDICOMUIDGenerator&);  // Not implemented.
  void operator=(const vtkDICOMUIDGenerator&);  // Not implemented.
};

//! Initializer (Schwarz counter).
/*!
 *  This ensures that the vtkDICOMUIDGenerator module is initialized before
 *  any other module that includes this header file.
 */
class VTKDICOM_EXPORT vtkDICOMUIDGeneratorInitializer
{
public:
  vtkDICOMUIDGeneratorInitializer();
  ~vtkDICOMUIDGeneratorInitializer();
private:
  vtkDICOMUIDGeneratorInitializer(const vtkDICOMUIDGeneratorInitializer&);
  vtkDICOMUIDGeneratorInitializer& operator=(
    const vtkDICOMUIDGeneratorInitializer&);
};

static vtkDICOMUIDGeneratorInitializer vtkDICOMUIDGeneratorInitializerInstance;

#endif // vtkDICOMUIDGenerator_h
