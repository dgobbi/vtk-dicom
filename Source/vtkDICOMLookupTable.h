/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2016 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*! \class vtkDICOMLookupTable
 *  \brief Lookup tables from DICOM data.
 *
 *  This class can create VTK lookup tables from the information in a
 *  DICOM data set.  Lookup tables can be created from a palette LUT,
 *  or from standard DICOM LUTs such as HOT_IRON.
 */

#ifndef vtkDICOMLookupTable_h
#define vtkDICOMLookupTable_h

#include <vtkLookupTable.h>
#include "vtkDICOMModule.h" // For export macro

class vtkDICOMMetaData;

//----------------------------------------------------------------------------
class VTKDICOM_EXPORT vtkDICOMLookupTable : public vtkLookupTable
{
public:
  //! Static method for construction.
  static vtkDICOMLookupTable *New();
  vtkTypeMacro(vtkDICOMLookupTable, vtkLookupTable);

  //! Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  //! Build the a standard lookup table, given a code string.
  /*!
   *  The supported code strings are HOT_IRON, HOT_METAL_BLUE, PET,
   *  and PET_20_STEP.  This does not set the range of the table.
   */
  void BuildStandardPalette(const char *name);

  //! Build the lookup table from the supplied meta data.
  /*!
   *  An index may be given to specify which data set instance in the
   *  meta data will be used.  The range of the table will be set to
   *  the smallest and largest pixel values to be mapped.
   */
  void BuildImagePalette(vtkDICOMMetaData *meta, int idx=0);

protected:
  vtkDICOMLookupTable();
  ~vtkDICOMLookupTable();

private:
  vtkDICOMLookupTable(const vtkDICOMLookupTable&);  // Not implemented.
  void operator=(const vtkDICOMLookupTable&);  // Not implemented.
};

#endif // vtkDICOMLookupTable_h
