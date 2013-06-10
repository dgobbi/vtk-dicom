/* Export macros for shared libraries */

#ifndef __vtkDICOMModule_h
#define __vtkDICOMModule_h

#include <vtkABI.h>
#include "vtkDICOMConfig.h"

#if defined(DICOM_BUILD_SHARED_LIBS)
# if defined(vtkDICOM_EXPORTS)
#  define VTK_DICOM_EXPORT VTK_ABI_EXPORT
# else
#  define VTK_DICOM_EXPORT VTK_ABI_IMPORT
# endif
#else
# define VTK_DICOM_EXPORT
#endif

#endif
