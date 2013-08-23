/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkNIFTIReader.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkNIFTIReader.h"
#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkDataArray.h"
#include "vtkByteSwap.h"
#include "vtkMatrix4x4.h"
#include "vtkMath.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkVersion.h"

#include "vtksys/SystemTools.hxx"
#include "vtksys/ios/sstream"

// Header for NIFTI
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIHeaderPrivate.h"

// Header for zlib
#include "vtk_zlib.h"

#include <ctype.h>
#include <string.h>
#include <string>

vtkStandardNewMacro(vtkNIFTIReader);

//----------------------------------------------------------------------------
vtkNIFTIReader::vtkNIFTIReader()
{
  for (int i = 0; i < 8; i++)
    {
    this->Dim[i] = 0;
    }
  for (int i = 0; i < 8; i++)
    {
    this->PixDim[i] = 1.0;
    }
  this->TimeAsVector = 0;
  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;
  this->QFac = 1.0;
  this->QFormMatrix = 0;
  this->SFormMatrix = 0;
  this->NIFTIHeader = 0;
}

//----------------------------------------------------------------------------
vtkNIFTIReader::~vtkNIFTIReader()
{
  if (this->QFormMatrix)
    {
    this->QFormMatrix->Delete();
    }
  if (this->SFormMatrix)
    {
    this->SFormMatrix->Delete();
    }
  if (this->NIFTIHeader)
    {
    this->NIFTIHeader->Delete();
    }
}

//----------------------------------------------------------------------------
namespace { // anonymous namespace

void vtkNIFTIReaderSwapHeader(nifti_1_header *hdr)
{
  // Common to NIFTI and Analyze 7.5
  vtkByteSwap::SwapVoidRange(&hdr->sizeof_hdr,    1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->extents,       1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->session_error, 1, 2);
  vtkByteSwap::SwapVoidRange(hdr->dim,            8, 2);
  vtkByteSwap::SwapVoidRange(&hdr->intent_p1,     1, 4); // unused in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->intent_p2,     1, 4); // unused in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->intent_p3,     1, 4); // unused in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->intent_code,   1, 2); // unused in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->datatype,      1, 2);
  vtkByteSwap::SwapVoidRange(&hdr->bitpix,        1, 2);
  vtkByteSwap::SwapVoidRange(&hdr->slice_start,   1, 2); // dim_un0 in 7.5
  vtkByteSwap::SwapVoidRange(hdr->pixdim,         8, 4);
  vtkByteSwap::SwapVoidRange(&hdr->vox_offset,    1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->scl_slope,     1, 4); // unused in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->scl_inter,     1, 4); // unused in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->slice_end,     1, 2); // unused in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->cal_max,       1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->cal_min,       1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->slice_duration,1, 4); // compressed in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->toffset,       1, 4); // verified in 7.5
  vtkByteSwap::SwapVoidRange(&hdr->glmax,         1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->glmin,         1, 4);

  // All NIFTI-specific (meaning is totally different in Analyze 7.5)
  vtkByteSwap::SwapVoidRange(&hdr->qform_code,    1, 2);
  vtkByteSwap::SwapVoidRange(&hdr->sform_code,    1, 2);
  vtkByteSwap::SwapVoidRange(&hdr->quatern_b,     1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->quatern_c,     1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->quatern_d,     1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->qoffset_x,     1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->qoffset_y,     1, 4);
  vtkByteSwap::SwapVoidRange(&hdr->qoffset_z,     1, 4);
  vtkByteSwap::SwapVoidRange(hdr->srow_x,         4, 4);
  vtkByteSwap::SwapVoidRange(hdr->srow_y,         4, 4);
  vtkByteSwap::SwapVoidRange(hdr->srow_z,         4, 4);
}

} // end anonymous namespace

//----------------------------------------------------------------------------
vtkNIFTIHeader *vtkNIFTIReader::GetNIFTIHeader()
{
  if (!this->NIFTIHeader)
    {
    this->NIFTIHeader = vtkNIFTIHeader::New();
    }
  return this->NIFTIHeader;
}

//----------------------------------------------------------------------------
void vtkNIFTIReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "TimeAsVector: "
     << (this->TimeAsVector ? "On\n" : "Off\n");
  os << indent << "TimeDimension: " << this->GetTimeDimension() << "\n";
  os << indent << "TimeSpacing: " << this->GetTimeSpacing() << "\n";
  os << indent << "RescaleSlope: " << this->RescaleSlope << "\n";
  os << indent << "RescaleIntercept: " << this->RescaleIntercept << "\n";
  os << indent << "QFac: " << this->QFac << "\n";

  os << indent << "QFormMatrix:";
  if (this->QFormMatrix)
    {
    double mat[16];
    vtkMatrix4x4::DeepCopy(mat, this->QFormMatrix);
    for (int i = 0; i < 16; i++)
      {
      os << " " << mat[i];
      }
    os << "\n";
    }
  else
    {
    os << " (none)\n";
    }

  os << indent << "SFormMatrix:";
  if (this->SFormMatrix)
    {
    double mat[16];
    vtkMatrix4x4::DeepCopy(mat, this->SFormMatrix);
    for (int i = 0; i < 16; i++)
      {
      os << " " << mat[i];
     }
    os << "\n";
    }
  else
    {
    os << " (none)\n";
    }

  os << indent << "NIFTIHeader:" << (this->NIFTIHeader ? "\n" : " (none)\n");
}

//----------------------------------------------------------------------------
char *vtkNIFTIReader::ReplaceExtension(
  const char *filename, const char *ext1, const char *ext2)
{
  if (strlen(ext1) != 4 || ext1[0] != '.' ||
      strlen(ext2) != 4 || ext2[0] != '.')
    {
    return 0;
    }

  size_t n = strlen(filename);
  size_t m = n;
  char *newname = new char[n+4];
  strcpy(newname, filename);

  if (n > 2 && filename[n-3] == '.' &&
      tolower(filename[n-2]) == 'g' &&
      tolower(filename[n-1]) == 'z')
    {
    m -= 3;
    }
  if (m > 3 && filename[m-4] == '.' &&
      tolower(filename[m-3]) == tolower(ext1[1]) &&
      tolower(filename[m-2]) == tolower(ext1[2]) &&
      tolower(filename[m-1]) == tolower(ext1[3]))
    {
    if (isupper(filename[m-3]))
      {
      newname[m-3] = toupper(ext2[1]);
      newname[m-2] = toupper(ext2[2]);
      newname[m-1] = toupper(ext2[3]);
      }
    else
      {
      newname[m-3] = tolower(ext2[1]);
      newname[m-2] = tolower(ext2[2]);
      newname[m-1] = tolower(ext2[3]);
      }
    }

  // existence of file
  for (int i = 0; i < 2; i++)
    {
    if (vtksys::SystemTools::FileExists(newname))
      {
      return newname;
      }
    if (i == 0)
      {
      if (m < n)
        {
        // try again without the ".gz"
        newname[m] = '\0';
        n = m;
        }
      else
        {
        // try again with the ".gz"
        newname[m] = '.';
        newname[m+1] = 'g';
        newname[m+2] = 'z';
        newname[m+3] = '\0';
        if (isupper(newname[m-3]))
          {
          newname[m+1] = toupper(newname[m+1]);
          newname[m+2] = toupper(newname[m+2]);
          }
        }
      }
    }

  delete [] newname;
  return 0;
}

//----------------------------------------------------------------------------
int vtkNIFTIReader::CanReadFile(const char *filename)
{
  vtkDebugMacro("Opening NIFTI file " << filename);

  char *hdrname = vtkNIFTIReader::ReplaceExtension(
    filename, ".img", ".hdr");

  if (hdrname == 0)
    {
    return 0;
    }

  // try opening file
  gzFile file = gzopen(hdrname, "rb");

  delete [] hdrname;

  if (!file)
    {
    return 0;
    }

  // read and check the header
  bool canRead = false;
  nifti_1_header hdr;
  int hsize = static_cast<int>(sizeof(nifti_1_header));
  int rsize = gzread(file, &hdr, hsize);
  if (rsize == hsize)
    {
    int version = NIFTI_VERSION(hdr);
    if (version > 0)
      {
      // NIFTI file
      canRead = true;
      }
    else if (version == 0 &&
             (hdr.sizeof_hdr == 348 || // Analyze 7.5 header size
              hdr.sizeof_hdr == 1543569408)) // byte-swapped 348
      {
      // Analyze 7.5 file
      canRead = true;
      }
    }

  gzclose(file);

  return canRead;
}

//----------------------------------------------------------------------------
int vtkNIFTIReader::RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  // Clear the error indicator.
  this->SetErrorCode(vtkErrorCode::NoError);

  const char *filename = this->GetFileName();

  if (!filename)
    {
    vtkErrorMacro("A FileName must be provided");
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    return 0;
    }

  char *hdrname = vtkNIFTIReader::ReplaceExtension(
    filename, ".img", ".hdr");

  if (hdrname == 0)
    {
    vtkErrorMacro("Unable to locate header for file " << filename);
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    return 0;
    }

  vtkDebugMacro("Opening NIFTI file " << hdrname);

  // try opening file
  gzFile file = gzopen(hdrname, "rb");

  if (!file)
    {
    vtkErrorMacro("Cannot open file " << hdrname);
    delete [] hdrname;
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    return 0;
    }

  // read and check the header
  bool canRead = false;
  int niftiVersion = 0;
  nifti_1_header *hdr = new nifti_1_header;
  int hsize = static_cast<int>(sizeof(nifti_1_header));
  int rsize = gzread(file, hdr, hsize);
  if (rsize == hsize)
    {
    niftiVersion = NIFTI_VERSION(*hdr);
    if (niftiVersion > 0)
      {
      // NIFTI file
      canRead = true;
      }
    else if (niftiVersion == 0 &&
             (hdr->sizeof_hdr == 348 || // Analyze 7.5 header size
              hdr->sizeof_hdr == 1543569408)) // byte-swapped 348
      {
      // Analyze 7.5 file
      canRead = true;
      }
    }

  gzclose(file);

  if (!canRead)
    {
    vtkErrorMacro("Bad NIfTI header in file " << hdrname);
    this->SetErrorCode(vtkErrorCode::UnrecognizedFileTypeError);
    delete [] hdrname;
    delete hdr;
    return 0;
    }

  delete [] hdrname;

  // default is native byte order
#ifdef VTK_WORDS_BIGENDIAN
  bool isLittleEndian = false;
#else
  bool isLittleEndian = true;
#endif

  if (NIFTI_NEEDS_SWAP(*hdr))
    {
    vtkNIFTIReaderSwapHeader(hdr);
    isLittleEndian = !isLittleEndian;
    }

  // number of dimensions
  int ndim = hdr->dim[0];

  // sanity checks
  for (int i = 0; i < 8; i++)
    {
    // voxel spacing cannot be zero
    if (hdr->pixdim[i] == 0)
      {
      hdr->pixdim[i] = 1.0;
      }
    // dimensions greater than ndim have size of 1
    if (i > ndim)
      {
      hdr->dim[i] = 1;
      }
    }

  if (niftiVersion > 0)
    {
    // pass rescale info to user (do not rescale in the reader)
    this->RescaleSlope = hdr->scl_slope;
    this->RescaleIntercept = hdr->scl_inter;
    }
  else
    {
    // rescale information not available for Analyze 7.5
    this->RescaleSlope = 1.0;
    this->RescaleIntercept = 0.0;
    }

  // header might be extended, vox_offset says where data starts
  this->SetHeaderSize(static_cast<int>(hdr->vox_offset));

  // endianness of data
  if (isLittleEndian)
    {
    this->SetDataByteOrderToLittleEndian();
    }
  else
    {
    this->SetDataByteOrderToBigEndian();
    }

  // NIFTI images are stored in a single file, not one file per slice
  this->SetFileDimensionality(3);

  // NIFTI uses a lower-left-hand origin
  this->FileLowerLeftOn();

  // dim
  this->SetDataExtent(0, hdr->dim[1]-1,
                      0, hdr->dim[2]-1,
                      0, hdr->dim[3]-1);

  // pixdim
  this->SetDataSpacing(hdr->pixdim[1],
                       hdr->pixdim[2],
                       hdr->pixdim[3]);

  // offset is part of the transform, so set origin to zero
  this->SetDataOrigin(0.0, 0.0, 0.0);

  // datatype
  int scalarType = 0;
  int numComponents = 1;
  switch(hdr->datatype)
    {
    case NIFTI_TYPE_INT8:
      scalarType = VTK_TYPE_INT8;
      break;
    case NIFTI_TYPE_UINT8:
      scalarType = VTK_TYPE_UINT8;
      break;
    case NIFTI_TYPE_INT16:
      scalarType = VTK_TYPE_INT16;
      break;
    case NIFTI_TYPE_UINT16:
      scalarType = VTK_TYPE_UINT16;
      break;
    case NIFTI_TYPE_INT32:
      scalarType = VTK_TYPE_INT32;
      break;
    case NIFTI_TYPE_UINT32:
      scalarType = VTK_TYPE_UINT32;
      break;
    case NIFTI_TYPE_FLOAT32:
      scalarType = VTK_TYPE_FLOAT32;
      break;
    case NIFTI_TYPE_FLOAT64:
      scalarType = VTK_TYPE_FLOAT64;
      break;
    case NIFTI_TYPE_COMPLEX64:
      scalarType = VTK_TYPE_FLOAT32;
      numComponents = 2;
      break;
    case NIFTI_TYPE_COMPLEX128:
      scalarType = VTK_TYPE_FLOAT64;
      numComponents = 2;
      break;
    case NIFTI_TYPE_RGB24:
      scalarType = VTK_TYPE_UINT8;
      numComponents = 3;
      break;
    case NIFTI_TYPE_RGBA32:
      scalarType = VTK_TYPE_UINT8;
      numComponents = 4;
      break;
    case 1:
      vtkErrorMacro("NIFTI files with one-bit-per-pixel not supported");
      this->SetErrorCode(vtkErrorCode::FileFormatError);
      delete hdr;
      return 0;
    default:
      vtkErrorMacro("Unrecognized NIFTI data type: " << hdr->datatype);
      this->SetErrorCode(vtkErrorCode::FileFormatError);
      delete hdr;
      return 0;
    }

  // vector planes become vector components
  if (ndim >= 5)
    {
    numComponents *= hdr->dim[5];
    }
  if (ndim >= 4 && this->TimeAsVector)
    {
    numComponents *= hdr->dim[4];
    }

  this->SetDataScalarType(scalarType);
  this->SetNumberOfScalarComponents(numComponents);

  // Set the output information.
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkDataObject::SetPointDataActiveScalarInfo(
    outInfo, this->DataScalarType, this->NumberOfScalarComponents);

  outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(),  this->DataOrigin, 3);

  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               this->DataExtent, 6);

  // copy dim for when RequestData is called
  for (int j = 0; j < 8; j++)
    {
    this->Dim[j] = hdr->dim[j];
    this->PixDim[j] = hdr->pixdim[j];
    }

  // === Image Orientation in NIfTI files ===
  //
  // The vtkImageData class does not provide a way of storing image
  // orientation.  So when we read a NIFTI file, we should also provide
  // the user with a 4x4 matrix that can transform VTK's data coordinates
  // into NIFTI's intended coordinate system for the image.  NIFTI defines
  // these coordinate systems as:
  // 1) NIFTI_XFORM_SCANNER_ANAT - equiv to DICOM Patient Coordinates
  // 2) NIFTI_XFORM_ALIGNED_ANAT - result of registration to another image
  // 3) NIFTI_XFORM_TALAIRACH - a brain-specific coordinate system
  // 4) NIFTI_XFORM_MNI_152 - a similar brain-specific coordinate system
  //
  // NIFTI images can store orientation in two ways:
  // 1) via a quaternion (used to store the original DICOM info)
  // 2) via a matrix (used to store e.g. the results of registration)
  //
  // A NIFTI file can have both a quaternion (qform) and matrix (xform)
  // stored in the same file.  The NIFTI documentation recommends that
  // the qform be used to record the "scanner anatomical" coordinates
  // and that the sform, if present, be used to define a secondary
  // coordinate system, e.g. a coordinate system derived through
  // registration to a template.
  //
  // -- Quaternion Representation --
  //
  // If the "quaternion" form is used, then the following equation
  // defines the transformation from voxel indices to the equivalent
  // of DICOM patient coordinates, where R is the rotation matrix
  // computed from the quaternion components:
  //
  //   [ x ]   [ R11 R12 R13 ] [ pixdim[1] * i        ]   [ qoffset_x ]
  //   [ y ] = [ R21 R22 R23 ] [ pixdim[2] * j        ] + [ qoffset_y ]
  //   [ z ]   [ R31 R32 R33 ] [ pixdim[3] * k * qfac ]   [ qoffset_z ]
  //
  // qfac is stored in pixdim[0], if it is equal to -1 then the slices
  // are stacked in reverse: VTK will have to reorder the slices in order
  // to maintain a right-handed coordinate transformation between indices
  // and coordinates.
  //
  // Let's call VTK data coordinates X,Y,Z to distinguish them from
  // the NIFTI coordinates x,y,z.  The relationship between X,Y,Z and
  // x,y,z is expressed by a 4x4 matrix M:
  //
  //   [ x ]   [ M11 M12 M13 M14 ] [ X ]
  //   [ y ] = [ M21 M22 M23 M24 ] [ Y ]
  //   [ z ]   [ M31 M32 M33 M34 ] [ Z ]
  //   [ 1 ]   [ 0   0   0   1   ] [ 1 ]
  //
  // where the VTK data coordinates X,Y,Z are related to the
  // VTK structured coordinates IJK (i.e. point indices) by:
  //
  //   X = I*Spacing[0] + Origin[0]
  //   Y = J*Spacing[1] + Origin[1]
  //   Z = K*Spacing[2] + Origin[2]
  //
  // Now let's consider: when we read a NIFTI image, how should we set
  // the Spacing, the Origin, and the matrix M?  Let's consider the
  // cases:
  //
  // 1) If there is no qform, then R is identity and qoffset is zero,
  //    and qfac will be 1 (never -1).  So:
  //      I,J,K = i,j,k, Spacing = pixdim, Origin = 0, M = Identity
  //
  // 2) If there is a qform, and qfac is 1, then:
  //
  //    I,J,K = i,j,k (i.e. voxel order in VTK same as in NIFTI)
  //
  //    Spacing[0] = pixdim[1]
  //    Spacing[1] = pixdim[2]
  //    Spacing[2] = pixdim[3]
  //
  //    Origin[0] = 0.0
  //    Origin[1] = 0.0
  //    Origin[2] = 0.0
  //
  //        [ R11 R12 R13 qoffset_x ]
  //    M = [ R21 R22 R23 qoffset_y ]
  //        [ R31 R32 R33 qoffset_z ]
  //        [ 0   0   0   1         ]
  //
  //    Note that we cannot store qoffset in the origin.  That would
  //    be mathematically incorrect.  It would only give us the right
  //    offset when R is the identity matrix.
  //
  // 3) If there is a qform and qfac is -1, then the situation is more
  //    compilcated.  We have three choices, each of which is a compromise:
  //    a) we can use Spacing[2] = qfac*pixdim[3], i.e. use a negative
  //       slice spacing, which might cause some VTK algorithms to
  //       misbehave (the VTK tests only use images with positive spacing).
  //    b) we can use M13 = -R13, M23 = -R23, M33 = -R33 i.e. introduce
  //       a flip into the matrix, which is very bad for VTK rendering
  //       algorithms and should definitely be avoided.
  //    c) we can reverse the order of the slices in VTK relative to
  //       NIFTI, which allows us to preserve positive spacing and retain
  //       a well-behaved rotation matrix, by using these equations:
  //
  //         J = number_of_slices - j - 1
  //
  //         M14 = qoffset_x - (number_of_slices - 1)*pixdim[3]*R13
  //         M24 = qoffset_y - (number_of_slices - 1)*pixdim[3]*R23
  //         M34 = qoffset_z - (number_of_slices - 1)*pixdim[3]*R33
  //
  //       This will give us data that will be well-behaved in VTK, at
  //       the expense of making VTK slice numbers not match with
  //       the original NIFTI slice numbers.  NIFTY slice 0 will become
  //       VTK slice N-1, and the order will be reversed.
  //
  // -- Matrix Representation --
  //
  // If the "matrix" form is used, then pixdim[] is ignored, and the
  // voxel spacing is implicitly stored in the matrix.  In addition,
  // the matrix may have a negative determinant, there is no "qfac"
  // flip-factor as there is in the quaternion representation.
  //
  // Let S be the matrix stored in the NIFTI header, and let M be our
  // desired coordinate tranformation from VTK data coordinates X,Y,Z
  // to NIFTI data coordinates x,y,z (see discussion above for more
  // information).  Let's consider the cases where the determinant
  // is positive, or negative.
  //
  // 1) If the determinant is positive, we will factor the spacing
  //    (but not the origin) out of the matrix.
  //
  //    Spacing[0] = pixdim[1]
  //    Spacing[1] = pixdim[2]
  //    Spacing[2] = pixdim[3]
  //
  //    Origin[0] = 0.0
  //    Origin[1] = 0.0
  //    Origin[2] = 0.0
  //
  //         [ S11/pixdim[1] S12/pixdim[2] S13/pixdim[3] S14 ]
  //    M  = [ S21/pixdim[1] S22/pixdim[2] S23/pixdim[3] S24 ]
  //         [ S31/pixdim[1] S32/pixdim[2] S33/pixdim[3] S34 ]
  //         [ 0             0             0             1   ]
  //
  // 2) If the determinant is negative, then we face the same choices
  //    as when qfac is -1 for the quaternion transformation.  We can:
  //    a) use a negative Z spacing and multiply the 3rd column of M by -1
  //    b) keep the matrix as is (with a negative determinant)
  //    c) reorder the slices, multiply the 3rd column by -1, and adjust
  //       the 4th column of the matrix:
  //
  //         M14 = S14 - (number_of_slices - 1)*S13
  //         M24 = S24 - (number_of_slices - 1)*S23
  //         M34 = S34 - (number_of_slices - 1)*S33
  //
  //       The third choice will provide a VTK image that has positive
  //       spacing and a matrix with a positive determinant.
  //
  // -- Analyze 7.5 Orientation --
  //
  // This reader provides only bare-bones backwards compatibility with
  // the Analyze 7.5 file header.  We do not orient these files.

  // Initialize
  this->QFac = 1.0;
  if (this->QFormMatrix)
    {
    this->QFormMatrix->Delete();
    this->QFormMatrix = NULL;
    }
  if (this->SFormMatrix)
    {
    this->SFormMatrix->Delete();
    this->SFormMatrix = NULL;
    }

  // Set the QFormMatrix from the quaternion data in the header.
  // See the long discussion above for more information.
  if (niftiVersion > 0 && hdr->qform_code > 0)
    {
    double mmat[16];
    double rmat[3][3];
    double quat[4];

    quat[1] = hdr->quatern_b;
    quat[2] = hdr->quatern_c;
    quat[3] = hdr->quatern_d;

    quat[0] = 1.0 - quat[1]*quat[1] - quat[2]*quat[2] - quat[3]*quat[3];
    if (quat[0] > 0.0)
      {
      quat[0] = sqrt(quat[0]);
      }
    else
      {
      quat[0] = 0.0;
      }

    vtkMath::QuaternionToMatrix3x3(quat, rmat);

    // first row
    mmat[0] = rmat[0][0];
    mmat[1] = rmat[0][1];
    mmat[2] = rmat[0][2];
    mmat[3] = hdr->qoffset_x;

    // second row
    mmat[4] = rmat[1][0];
    mmat[5] = rmat[1][1];
    mmat[6] = rmat[1][2];
    mmat[7] = hdr->qoffset_y;

    // third row
    mmat[8] = rmat[2][0];
    mmat[9] = rmat[2][1];
    mmat[10] = rmat[2][2];
    mmat[11] = hdr->qoffset_z;

    mmat[12] = 0.0;
    mmat[13] = 0.0;
    mmat[14] = 0.0;
    mmat[15] = 1.0;

    this->QFac = ((hdr->pixdim[0] < 0) ? -1.0 : 1.0);

    if (this->QFac < 0)
      {
      // We will be reversing the order of the slices, so the first VTK
      // slice will be at the position of the last NIfTI slice, and we
      // must adjust the offset to compensate for this.
      mmat[3] -= rmat[0][2]*hdr->pixdim[3]*(hdr->dim[3] - 1);
      mmat[7] -= rmat[1][2]*hdr->pixdim[3]*(hdr->dim[3] - 1);
      mmat[11] -= rmat[2][2]*hdr->pixdim[3]*(hdr->dim[3] - 1);
      }

    this->QFormMatrix = vtkMatrix4x4::New();
    this->QFormMatrix->DeepCopy(mmat);
    }

  // Set the SFormMatrix from the matrix information in the header.
  // See the long discussion above for more information.
  if (niftiVersion > 0 && hdr->sform_code > 0)
    {
    double mmat[16];

    // first row
    mmat[0] = hdr->srow_x[0]/hdr->pixdim[1];
    mmat[1] = hdr->srow_x[1]/hdr->pixdim[2];
    mmat[2] = hdr->srow_x[2]/hdr->pixdim[3];
    mmat[3] = hdr->srow_x[3];

    // second row
    mmat[4] = hdr->srow_y[0]/hdr->pixdim[1];
    mmat[5] = hdr->srow_y[1]/hdr->pixdim[2];
    mmat[6] = hdr->srow_y[2]/hdr->pixdim[3];
    mmat[7] = hdr->srow_y[3];

    // third row
    mmat[8] = hdr->srow_z[0]/hdr->pixdim[1];
    mmat[9] = hdr->srow_z[1]/hdr->pixdim[2];
    mmat[10] = hdr->srow_z[2]/hdr->pixdim[3];
    mmat[11] = hdr->srow_z[3];

    mmat[12] = 0.0;
    mmat[13] = 0.0;
    mmat[14] = 0.0;
    mmat[15] = 1.0;

    if (this->QFac < 0)
      {
      // If QFac is set to -1 (which only occurs if qform_code was set)
      // then the slices will be reversed, and we must reverse the slice
      // orientation vector (the third column of the matrix) to compensate.

      // reverse the slice orientation vector
      mmat[2] = -mmat[2];
      mmat[6] = -mmat[6];
      mmat[10] = -mmat[10];

      // adjust the offset to compensate for changed slice ordering
      mmat[3] -= hdr->srow_x[2]*(hdr->dim[3] - 1);
      mmat[7] -= hdr->srow_y[2]*(hdr->dim[3] - 1);
      mmat[11] -= hdr->srow_z[2]*(hdr->dim[3] - 1);
      }

    this->SFormMatrix = vtkMatrix4x4::New();
    this->SFormMatrix->DeepCopy(mmat);

    if (this->SFormMatrix->Determinant() < 0)
      {
      vtkWarningMacro("SFormMatrix has a negative determinant");
      }
    }

  // Save the header
  if (!this->NIFTIHeader)
    {
    this->NIFTIHeader = vtkNIFTIHeader::New();
    }
  this->NIFTIHeader->SetHeader(hdr);
  delete hdr;

  return 1;
}

//----------------------------------------------------------------------------
int vtkNIFTIReader::RequestData(
  vtkInformation* request,
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  // which output port did the request come from
  int outputPort =
    request->Get(vtkDemandDrivenPipeline::FROM_OUTPUT_PORT());

  // for now, this reader has only one output
  if (outputPort > 0)
    {
    return 1;
    }

  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  int extent[6];
  outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), extent);

  // get the data object, allocate memory
  vtkImageData *data =
    static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));
#if VTK_MAJOR_VERSION >= 6
  this->AllocateOutputData(data, outInfo, extent);
#else
  this->AllocateOutputData(data, extent);
#endif

  data->GetPointData()->GetScalars()->SetName("NIFTI");

  const char *filename = this->GetFileName();

  if (filename == NULL)
    {
    vtkErrorMacro("A FileName must be provided");
    return 0;
    }

  char *imgname = vtkNIFTIReader::ReplaceExtension(
    filename, ".hdr", ".img");

  if (imgname == 0)
    {
    vtkErrorMacro("Unable to locate image for file " << filename);
    return 0;
    }

  vtkDebugMacro("Opening NIFTI file " << imgname);

  data->GetPointData()->GetScalars()->SetName("NIFTI");

  unsigned char *dataPtr =
    static_cast<unsigned char *>(data->GetScalarPointer());

  gzFile file = gzopen(imgname, "rb");

  delete [] imgname;

  if (!file)
    {
    return 0;
    }

  int swapBytes = this->GetSwapBytes();
  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();
  int timeDim = (this->Dim[0] >= 4 ? this->Dim[4] : 1);
  int vectorDim = (this->Dim[0] >= 5 ? this->Dim[5] : 1);
  if (this->TimeAsVector)
    {
    vectorDim *= timeDim;
    }

  int outSizeX = extent[1] - extent[0] + 1;
  int outSizeY = extent[3] - extent[2] + 1;
  int outSizeZ = extent[5] - extent[4] + 1;

  z_off_t fileVoxelIncr = scalarSize*numComponents/vectorDim;
  z_off_t fileRowIncr = fileVoxelIncr*this->Dim[1];
  z_off_t fileSliceIncr = fileRowIncr*this->Dim[2];
  z_off_t fileTimeIncr = fileSliceIncr*this->Dim[3];
  z_off_t fileVectorIncr = fileTimeIncr*this->Dim[4];
  if (this->TimeAsVector)
    {
    fileVectorIncr = fileTimeIncr;
    }

  // add a buffer for planar-vector to packed-vector conversion
  unsigned char *rowBuffer = 0;
  if (vectorDim > 1)
    {
    rowBuffer = new unsigned char[outSizeX*fileVoxelIncr];
    }

  // special increment to reverse the slices if needed
  vtkIdType sliceOffset = 0;

  if (this->GetQFac() < 0)
    {
    // put slices in reverse order
    sliceOffset = scalarSize*numComponents;
    sliceOffset *= outSizeX;
    sliceOffset *= outSizeY;
    dataPtr += sliceOffset*(outSizeZ - 1);
    }

  // report progress every 2% of the way to completion
  this->InvokeEvent(vtkCommand::StartEvent);
  this->UpdateProgress(0.0);
  vtkIdType target =
    static_cast<vtkIdType>(0.02*outSizeY*outSizeZ*vectorDim) + 1;
  vtkIdType count = 0;

  // seek to the start of the data
  z_off_t offset = static_cast<z_off_t>(this->GetHeaderSize());
  offset += extent[0]*fileVoxelIncr;
  offset += extent[2]*fileRowIncr;
  offset += extent[4]*fileSliceIncr;

  // read the data one row at a time, do planar-to-packed conversion
  // of vector components if NIFTI file has a vector dimension
  int rowSize = numComponents/vectorDim*outSizeX;
  int t = 0; // counter for time
  int c = 0; // counter for vector components
  int j = 0; // counter for rows
  int k = 0; // counter for slices
  unsigned char *ptr = dataPtr;

  while (!this->AbortExecute)
    {
    if (offset)
      {
      int rval = gzseek(file, offset, SEEK_CUR);
      if (rval == -1)
        {
        if (gzeof(file))
          {
          vtkErrorMacro("NIFTI file is truncated, some data is missing.");
          this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
          }
        else
          {
          vtkErrorMacro("Error in NIFTI file, cannot read.");
          this->SetErrorCode(vtkErrorCode::FileFormatError);
          }
        break;
        }
      }

    if (vectorDim == 1)
      {
      // read directly into the output instead of into a buffer
      rowBuffer = ptr;
      }

    int code = gzread(file, rowBuffer, rowSize*scalarSize);
    if (code != rowSize*scalarSize)
      {
      if (gzeof(file))
        {
        vtkErrorMacro("NIFTI file is truncated, some data is missing.");
        this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
        }
      else
        {
        vtkErrorMacro("Error in NIFTI file, cannot read.");
        this->SetErrorCode(vtkErrorCode::FileFormatError);
        }
      break;
      }

    if (swapBytes != 0 && scalarSize > 1)
      {
      vtkByteSwap::SwapVoidRange(rowBuffer, rowSize, scalarSize);
      }

    if (vectorDim == 1)
      {
      // advance the pointer to the next row
      ptr += outSizeX*numComponents*scalarSize;
      rowBuffer = 0;
      }
    else
      {
      // write vector plane to packed vector component
      unsigned char *tmpPtr = rowBuffer;
      z_off_t skipOther = scalarSize*numComponents - fileVoxelIncr;
      for (int i = 0; i < outSizeX; i++)
        {
        // write one vector component of one voxel
        z_off_t n = fileVoxelIncr;
        do { *ptr++ = *tmpPtr++; } while (--n);
        // skip past the other components
        ptr += skipOther;
        }
      }

    if (++count % target == 0)
      {
      this->UpdateProgress(0.02*count/target);
      }

    // offset to skip unread sections of the file, for when
    // the update extent is less than the whole extent
    offset = fileRowIncr - outSizeX*fileVoxelIncr;
    if (++j == outSizeY)
      {
      j = 0;
      offset += fileSliceIncr - outSizeY*fileRowIncr;
      ptr -= 2*sliceOffset; // for reverse slice order
      if (++k == outSizeZ)
        {
        k = 0;
        offset += fileVectorIncr - outSizeZ*fileSliceIncr;
        if (++t == timeDim)
          {
          t = 0;
          }
        if (++c == vectorDim)
          {
          break;
          }
        // back up the ptr to the beginning of the image,
        // then increment to the next vector component
        ptr = dataPtr + c*fileVoxelIncr;

        if (this->TimeAsVector)
          {
          // if timeDim is included in the vectorDim (and hence in the
          // VTK scalar components) then we have to make sure that
          // the vector components are packed before the time steps
          ptr = dataPtr + (c + t*(vectorDim - 1))/timeDim*fileVoxelIncr;
          }
        }
      }
    }

  if (vectorDim > 1)
    {
    delete [] rowBuffer;
    }

  gzclose(file);

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}
