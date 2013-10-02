/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkNIFTIWriter.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkNIFTIWriter.h"
#include "vtkObjectFactory.h"
#include "vtkNIFTIReader.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkErrorCode.h"
#include "vtkByteSwap.h"
#include "vtkMatrix4x4.h"
#include "vtkMath.h"
#include "vtkCommand.h"
#include "vtkVersion.h"

#include "vtksys/SystemTools.hxx"
#include "vtksys/ios/sstream"

// Header for NIFTI
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIHeaderPrivate.h"

// Header for zlib
#include "vtk_zlib.h"

#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

vtkStandardNewMacro(vtkNIFTIWriter);
vtkCxxSetObjectMacro(vtkNIFTIWriter,QFormMatrix,vtkMatrix4x4);
vtkCxxSetObjectMacro(vtkNIFTIWriter,SFormMatrix,vtkMatrix4x4);
vtkCxxSetObjectMacro(vtkNIFTIWriter,NIFTIHeader,vtkNIFTIHeader);

//----------------------------------------------------------------------------
vtkNIFTIWriter::vtkNIFTIWriter()
{
  this->FileLowerLeft = 1;
  this->FileDimensionality = 3;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->QFac = 0.0;
  this->QFormMatrix = 0;
  this->SFormMatrix = 0;
  this->NIFTIHeader = 0;
  this->Description = new char[80];
  // Default description is "VTKX.Y.Z"
  strncpy(this->Description, "VTK", 3);
  strncpy(&this->Description[3], vtkVersion::GetVTKVersion(), 77);
}

//----------------------------------------------------------------------------
vtkNIFTIWriter::~vtkNIFTIWriter()
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
  delete [] this->Description;
}

//----------------------------------------------------------------------------
vtkNIFTIHeader *vtkNIFTIWriter::GetNIFTIHeader()
{
  if (!this->NIFTIHeader)
    {
    this->NIFTIHeader = vtkNIFTIHeader::New();
    }
  return this->NIFTIHeader;
}

//----------------------------------------------------------------------------
void vtkNIFTIWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "Description: " << this->Description << "\n";
  os << indent << "TimeDimension: " << this->TimeDimension << "\n";
  os << indent << "TimeSpacing: " << this->TimeSpacing << "\n";
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
char *vtkNIFTIWriter::ReplaceExtension(
  const char *filename, const char *ext1, const char *ext2)
{
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

  return newname;
}

//----------------------------------------------------------------------------
namespace {

// Initialize the NIFTI header with only the most basic information:
// - NIFTI data type is set from VTK data type
// - NIFTI pixdim set from VTK spacing
// - dimensionality is:
//  - 5 if number of components is greater than one
//  - 2 if Z dimension is one and number of components is one
//  - 3 if Z dimension is greater than one and number of components is one
// - units are NIFTI_UNITS_UNKNOWN
// - intent is NIFTI_INTENT_NONE
// - magic is "n+1" (i.e. a .nii file, header+image in one file)
// - vox_offset is set to the header size plus 64-bit alignment padding
// - everything else is initialized to zero
// After initialization, the following should be set:
// - if file is ".hdr", set magic to "ni1" and vox_offset to zero
// - intent should be set, if known
// - units should be set, if known
// - qform and sform should be set, if known
// - pixdim[0] should be set to qfac (1 or -1) if qform is known
// - slope and inter should be set, if known
// - descrip and intent_name should be set, if known
// - for RGB and RGBA images, header should be modified as necessary
// - for complex images, header should be modified as necessary

void vtkNIFTIWriterInitializeHeader(
  nifti_1_header *hdr)
{
  hdr->sizeof_hdr = static_cast<int>(sizeof(nifti_1_header));
  memset(hdr->data_type, '\0', sizeof(hdr->datatype)); // unused
  memset(hdr->db_name, '\0', sizeof(hdr->db_name)); // unused
  hdr->extents = 0; // unused
  hdr->session_error = 0; // unused
  hdr->regular = 0; // unused
  hdr->dim_info = 0; // MR acquisition, phase, and slice directions

  for (int i = 0; i < 8; i++)
    {
    hdr->dim[0] = 0;
    }

  hdr->intent_p1 = 0;
  hdr->intent_p2 = 0;
  hdr->intent_p3 = 0;
  hdr->intent_code = 0;

  hdr->datatype = 4;
  hdr->bitpix = 16;

  hdr->slice_start = 0;

  for (int i = 0; i < 8; i++)
    {
    hdr->pixdim[0] = 0.0;
    }

  hdr->vox_offset = 352.0; // divisible by 16 for alignment
  hdr->scl_slope = 1.0;
  hdr->scl_inter = 0.0;
  hdr->slice_end = 0;
  hdr->slice_code = 0;
  hdr->xyzt_units = 0;
  hdr->cal_max = 0.0;
  hdr->cal_min = 0.0;
  hdr->slice_duration = 0;
  hdr->toffset = 0;

  hdr->glmax = 0; // unused
  hdr->glmin = 0; // unused

  memset(hdr->descrip, '\0', sizeof(hdr->descrip));
  memset(hdr->aux_file, '\0', sizeof(hdr->aux_file));

  hdr->qform_code = 0;
  hdr->sform_code = 0;
  hdr->quatern_b = 0.0;
  hdr->quatern_c = 0.0;
  hdr->quatern_d = 0.0;
  hdr->qoffset_x = 0.0;
  hdr->qoffset_y = 0.0;
  hdr->qoffset_z = 0.0;

  for (int i = 0; i < 4; i++)
    {
    hdr->srow_x[i] = 0.0;
    hdr->srow_y[i] = 0.0;
    hdr->srow_z[i] = 0.0;
    }

  memset(hdr->intent_name, '\0', sizeof(hdr->intent_name));

  hdr->magic[0] = 'n';
  hdr->magic[1] = '+';
  hdr->magic[2] = '1';
  hdr->magic[3] = '\0';
}

double vtkNIFTIWriterFTZ(double d)
{
  // flush very small values to zero, to avoid having
  // values appear as "-0" in the header.
  if (fabs(d) < FLT_MIN)
    {
    d = 0.0;
    }
  return d;
}

void vtkNIFTIWriterSetInformation(
  nifti_1_header *hdr,
  vtkInformation *info)
{
  // get the scalar information
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(
    info, vtkDataObject::FIELD_ASSOCIATION_POINTS,
    vtkDataSetAttributes::SCALARS);

  int extent[6];
  info->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);

  double spacing[3];
  info->Get(vtkDataObject::SPACING(), spacing);

  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents = scalarInfo->Get(
    vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());

  // get the NIFTI data type:
  short datatype = 0;
  short databits = 0;

  switch (scalarType)
    {
    case VTK_CHAR:
#if VTK_TYPE_CHAR_IS_SIGNED
      datatype = NIFTI_TYPE_INT8;
#else
      datatype = NIFTI_TYPE_UINT8;
#endif
      databits = 8;
      break;
    case VTK_SIGNED_CHAR:
      datatype = NIFTI_TYPE_INT8;
      databits = 8;
      break;
    case VTK_UNSIGNED_CHAR:
      datatype = NIFTI_TYPE_UINT8;
      databits = 8;
      break;
    case VTK_SHORT:
      datatype = NIFTI_TYPE_INT16;
      databits = 16;
      break;
    case VTK_UNSIGNED_SHORT:
      datatype = NIFTI_TYPE_UINT16;
      databits = 16;
      break;
    case VTK_INT:
      datatype = NIFTI_TYPE_INT32;
      databits = 32;
      break;
    case VTK_UNSIGNED_INT:
      datatype = NIFTI_TYPE_UINT32;
      databits = 32;
      break;
    case VTK_FLOAT:
      datatype = NIFTI_TYPE_FLOAT32;
      databits = 32;
      break;
    case VTK_DOUBLE:
      datatype = NIFTI_TYPE_FLOAT64;
      databits = 64;
      break;
    default:
      break;
    }

  // number of spatial dimensions
  short spaceDim = (extent[4] == extent[5] ? 2 : 3);

  hdr->dim[0] = (numComponents == 1 ? spaceDim : 5);
  hdr->dim[1] = static_cast<short>(extent[1] - extent[0] + 1);
  hdr->dim[2] = static_cast<short>(extent[3] - extent[2] + 1);
  hdr->dim[3] = static_cast<short>(extent[5] - extent[4] + 1);
  hdr->dim[4] = 1;
  hdr->dim[5] = static_cast<short>(numComponents);
  hdr->dim[6] = 1;
  hdr->dim[7] = 1;

  hdr->datatype = datatype;
  hdr->bitpix = databits;

  hdr->slice_start = 0;
  hdr->pixdim[0] = 0.0;
  hdr->pixdim[1] = vtkNIFTIWriterFTZ(spacing[0]);
  hdr->pixdim[2] = vtkNIFTIWriterFTZ(spacing[1]);
  hdr->pixdim[3] = vtkNIFTIWriterFTZ(spacing[2]);
  hdr->pixdim[4] = 1.0;
  hdr->pixdim[5] = 1.0;
  hdr->pixdim[6] = 1.0;
  hdr->pixdim[7] = 1.0;
}

// Set the QForm from a 4x4 matrix
void vtkNIFTIWriterSetQForm(
  nifti_1_header *hdr, double mmat[16], double qfac)
{
  double rmat[3][3];
  rmat[0][0] = mmat[0];
  rmat[0][1] = mmat[1];
  rmat[0][2] = mmat[2];
  rmat[1][0] = mmat[4];
  rmat[1][1] = mmat[5];
  rmat[1][2] = mmat[6];
  rmat[2][0] = mmat[8];
  rmat[2][1] = mmat[9];
  rmat[2][2] = mmat[10];

  double quat[4];
  vtkMath::Matrix3x3ToQuaternion(rmat, quat);
  if (quat[0] < 0)
    {
    quat[0] = -quat[0];
    quat[1] = -quat[1];
    quat[2] = -quat[2];
    quat[3] = -quat[3];
    }

  if (qfac < 0)
    {
    // We will be reversing the order of the slices, so the first VTK
    // slice will be at the position of the last NIfTI slice, and we
    // must adjust the offset to compensate for this.
    mmat[3] -= rmat[0][2]*hdr->pixdim[3]*(hdr->dim[3] - 1);
    mmat[7] -= rmat[1][2]*hdr->pixdim[3]*(hdr->dim[3] - 1);
    mmat[11] -= rmat[2][2]*hdr->pixdim[3]*(hdr->dim[3] - 1);
    }

  hdr->pixdim[0] = qfac;
  hdr->quatern_b = vtkNIFTIWriterFTZ(quat[1]);
  hdr->quatern_c = vtkNIFTIWriterFTZ(quat[2]);
  hdr->quatern_d = vtkNIFTIWriterFTZ(quat[3]);
  hdr->qoffset_x = vtkNIFTIWriterFTZ(mmat[3]);
  hdr->qoffset_y = vtkNIFTIWriterFTZ(mmat[7]);
  hdr->qoffset_z = vtkNIFTIWriterFTZ(mmat[11]);
}

// Set the SForm from a 4x4 matrix
void vtkNIFTIWriterSetSForm(
  nifti_1_header *hdr, double mmat[16], double qfac)
{
  if (qfac < 0)
    {
    // If QFac is set to -1 (which only occurs if qform_code was set)
    // then the slices will be reversed, and we must reverse the slice
    // orientation vector (the third column of the matrix) to compensate.

    // adjust the offset to compensate for changed slice ordering
    mmat[3] -= mmat[2]*(hdr->dim[3] - 1);
    mmat[7] -= mmat[6]*(hdr->dim[3] - 1);
    mmat[11] -= mmat[10]*(hdr->dim[3] - 1);

    // reverse the slice orientation vector
    mmat[2] = -mmat[2];
    mmat[6] = -mmat[6];
    mmat[10] = -mmat[10];
    }

  // first row
  hdr->srow_x[0] = vtkNIFTIWriterFTZ(mmat[0] * hdr->pixdim[1]);
  hdr->srow_x[1] = vtkNIFTIWriterFTZ(mmat[1] * hdr->pixdim[2]);
  hdr->srow_x[2] = vtkNIFTIWriterFTZ(mmat[2] * hdr->pixdim[3]);
  hdr->srow_x[3] = vtkNIFTIWriterFTZ(mmat[3]);

  // second row
  hdr->srow_y[0] = vtkNIFTIWriterFTZ(mmat[4] * hdr->pixdim[1]);
  hdr->srow_y[1] = vtkNIFTIWriterFTZ(mmat[5] * hdr->pixdim[2]);
  hdr->srow_y[2] = vtkNIFTIWriterFTZ(mmat[6] * hdr->pixdim[3]);
  hdr->srow_y[3] = vtkNIFTIWriterFTZ(mmat[7]);

  // third row
  hdr->srow_z[0] = vtkNIFTIWriterFTZ(mmat[8] * hdr->pixdim[1]);
  hdr->srow_z[1] = vtkNIFTIWriterFTZ(mmat[9] * hdr->pixdim[2]);
  hdr->srow_z[2] = vtkNIFTIWriterFTZ(mmat[10] * hdr->pixdim[3]);
  hdr->srow_z[3] = vtkNIFTIWriterFTZ(mmat[11]);
}

void vtkNIFTIWriterMatrix(
  double mmat[16], vtkMatrix4x4 *matrix, const double origin[3])
{
  // find new offset by multiplying the origin by the matrix
  double offset[4];
  offset[0] = origin[0];
  offset[1] = origin[1];
  offset[2] = origin[2];
  offset[3] = 1.0;

  if (matrix)
    {
    matrix->MultiplyPoint(offset, offset);
    vtkMatrix4x4::DeepCopy(mmat, matrix);
    }
  else
    {
    vtkMatrix4x4::Identity(mmat);
    }

  mmat[3] = offset[0];
  mmat[7] = offset[1];
  mmat[11] = offset[2];
}

} // end anonymous namespace

//----------------------------------------------------------------------------
int vtkNIFTIWriter::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* vtkNotUsed(outputVector))
{
  this->SetErrorCode(vtkErrorCode::NoError);

  vtkInformation *info = inputVector[0]->GetInformationObject(0);
  vtkImageData *data =
    vtkImageData::SafeDownCast(info->Get(vtkDataObject::DATA_OBJECT()));

  if (data == NULL)
    {
    vtkErrorMacro("No input provided!");
    return 0;
    }

  const char *filename = this->GetFileName();
  if (filename == NULL)
    {
    vtkErrorMacro("A FileName must be provided");
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    return 0;
    }

  int extent[6];
  info->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  if (extent[1] - extent[0] + 1 > VTK_SHORT_MAX ||
      extent[3] - extent[2] + 1 > VTK_SHORT_MAX ||
      extent[5] - extent[4] + 1 > VTK_SHORT_MAX)
    {
    vtkErrorMacro("Image too large to store in NIFTI-1 format");
    return 0;
    }

  // use compression if name ends in .gz
  bool isCompressed = false;
  size_t n = strlen(filename);
  size_t m = n;
  if (n > 2 && filename[n-3] == '.' &&
      tolower(filename[n-2]) == 'g' &&
      tolower(filename[n-1]) == 'z')
    {
    m = n - 3;
    isCompressed = true;
    }

  // after the optional ".gz" is removed, is it a ".img/.hdr" file?
  bool singleFile = true;
  if (m > 4 && filename[m-4] == '.' &&
      ((tolower(filename[m-3]) == 'h' &&
        tolower(filename[m-2]) == 'd' &&
        tolower(filename[m-1]) == 'r') ||
       (tolower(filename[m-3]) == 'i' &&
        tolower(filename[m-2]) == 'm' &&
        tolower(filename[m-1]) == 'g')))
    {
    singleFile = false;
    }

  // if file is not .nii, then get .hdr and .img filenames
  char *hdrname = vtkNIFTIWriter::ReplaceExtension(
    filename, ".img", ".hdr");
  char *imgname = vtkNIFTIWriter::ReplaceExtension(
    filename, ".hdr", ".img");

  vtkDebugMacro(<< "Writing NIFTI file " << hdrname);

  // create the header
  nifti_1_header hdr;
  if (this->NIFTIHeader)
    {
    this->NIFTIHeader->GetHeader(&hdr);
    }
  else
    {
    vtkNIFTIWriterInitializeHeader(&hdr);
    }

  // copy the image information into the header
  vtkNIFTIWriterSetInformation(&hdr, info);

  // set the header size
  hdr.sizeof_hdr = static_cast<int>(sizeof(nifti_1_header));

  // modify magic number and voxel offset for .img files
  if (!singleFile)
    {
    strncpy(hdr.magic, "ni1", 4);
    hdr.vox_offset = 0;
    }
  else
    {
    strncpy(hdr.magic, "n+1", 4);
    hdr.vox_offset = 352;
    }

  // set the description
  if (this->Description)
    {
    strncpy(hdr.descrip, this->Description, 80);
    }

  // qfac dictates the slice ordering in the file
  double qfac = (this->QFac < 0 ? -1.0 : 1.0);

  // origin must be incorporated into qform and sform
  double origin[3];
  data->GetOrigin(origin);

  if (this->QFormMatrix ||
      (origin[0] != 0 || origin[1] != 0 || origin[2] != 0))
    {
    hdr.qform_code = 1; // SCANNER_ANAT
    double mat16[16];
    vtkNIFTIWriterMatrix(mat16, this->QFormMatrix, origin);
    vtkNIFTIWriterSetQForm(&hdr, mat16, qfac);
    }

  if (this->SFormMatrix)
    {
    hdr.sform_code = 2; // ALIGNED_ANAT
    double mat16[16];
    vtkNIFTIWriterMatrix(mat16, this->SFormMatrix, origin);
    vtkNIFTIWriterSetSForm(&hdr, mat16, qfac);
    }

  // base dimension not counting vector dimension
  short basedim = (hdr.dim[3] == 1 ? 2 : 3);

  if (this->TimeDimension)
    {
    short tdim = static_cast<short>(this->TimeDimension);
    if (hdr.dim[5] % tdim != 0)
      {
      vtkErrorMacro("Number of components in the image data must be "
                    "divisible by the TimeDimension");
      delete [] hdrname;
      delete [] imgname;
      return 0;
      }
    hdr.pixdim[4] = vtkNIFTIWriterFTZ(this->TimeSpacing);
    hdr.dim[4] = tdim;
    hdr.dim[5] /= tdim;
    hdr.dim[0] = (hdr.dim[5] > 1 ? 5 : 4);
    basedim = 4;
    }

  if (hdr.dim[5] == 2 && hdr.datatype == NIFTI_TYPE_FLOAT32)
    {
    // float with 2 components becomes COMPLEX64
    hdr.datatype = NIFTI_TYPE_COMPLEX64;
    hdr.dim[0] = basedim;
    hdr.dim[5] = 1;
    }
  else if (hdr.dim[5] == 2 && hdr.datatype == NIFTI_TYPE_FLOAT64)
    {
    // double with 2 components becomes COMPLEX128
    hdr.datatype = NIFTI_TYPE_COMPLEX128;
    hdr.dim[0] = basedim;
    hdr.dim[5] = 1;
    }
  else if (hdr.dim[5] == 3 && hdr.datatype == NIFTI_TYPE_UINT8)
    {
    // unsigned char with 3 components becomes RGB24
    hdr.datatype = NIFTI_TYPE_RGB24;
    hdr.dim[0] = basedim;
    hdr.dim[5] = 1;
    }
  else if (hdr.dim[5] == 4 && hdr.datatype == NIFTI_TYPE_UINT8)
    {
    // unsigned char with 4 components becomes RGBA32
    hdr.datatype = NIFTI_TYPE_RGBA32;
    hdr.dim[0] = basedim;
    hdr.dim[5] = 1;
    }

  // try opening file
  gzFile file = 0;
  FILE *ufile = 0;
  if (isCompressed)
    {
    file = gzopen(hdrname, "wb");
    }
  else
    {
    ufile = fopen(hdrname, "wb");
    }

  if (!file && !ufile)
    {
    vtkErrorMacro("Cannot open file " << hdrname);
    delete [] hdrname;
    delete [] imgname;
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    return 0;
    }

  this->InvokeEvent(vtkCommand::StartEvent);
  this->UpdateProgress(0.0);

  // write the header
  size_t bytesWritten = 0;
  if (isCompressed)
    {
    unsigned int hsize = static_cast<unsigned int>(sizeof(nifti_1_header));
    int code = gzwrite(file, &hdr, hsize);
    bytesWritten = (code < 0 ? 0 : code);
    }
  else
    {
    bytesWritten = fwrite(&hdr, 1, sizeof(nifti_1_header), ufile);
    }
  if (bytesWritten < sizeof(nifti_1_header))
    {
    vtkErrorMacro("Insufficient disk space to write file.");
    this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
    }

  if (singleFile && !this->ErrorCode)
    {
    // write 4 bytes of padding to the .nii file
    char padding[4] = { 0, 0, 0, 0 };
    if (isCompressed)
      {
      int code = gzwrite(file, padding, 4);
      bytesWritten = (code < 0 ? 0 : code);
      }
    else
      {
      bytesWritten = fwrite(padding, 1, 4, ufile);
      }
    if (bytesWritten < 4)
      {
      vtkErrorMacro("Insufficient disk space to write file.");
      this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
      }
    }
  else if (!this->ErrorCode)
    {
    // close the .hdr file and open the .img file
    if (isCompressed)
      {
      gzclose(file);
      file = gzopen(imgname, "wb");
      }
    else
      {
      fclose(ufile);
      ufile = fopen(imgname, "wb");
      }
    }

  if (!file && !ufile)
    {
    vtkErrorMacro("Cannot open file " << imgname);
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    }

  // write the image
  unsigned char *dataPtr =
    static_cast<unsigned char *>(data->GetScalarPointer());

  int swapBytes = 0;
  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();
  int outSizeX = hdr.dim[1];
  int outSizeY = hdr.dim[2];
  int outSizeZ = hdr.dim[3];
  int timeDim = hdr.dim[4];
  int vectorDim = hdr.dim[5];

  // for counting, include timeDim in vectorDim
  vectorDim *= timeDim;

  z_off_t fileVoxelIncr = scalarSize*numComponents/vectorDim;

  // add a buffer for planar-vector to packed-vector conversion
  unsigned char *rowBuffer = 0;
  if (vectorDim > 1 || swapBytes)
    {
    rowBuffer = new unsigned char[outSizeX*fileVoxelIncr];
    }

  // special increment to reverse the slices if needed
  vtkIdType sliceOffset = 0;

  if (qfac < 0)
    {
    // put slices in reverse order
    sliceOffset = scalarSize*numComponents;
    sliceOffset *= outSizeX;
    sliceOffset *= outSizeY;
    dataPtr += sliceOffset*(outSizeZ - 1);
    }

  // report progress every 2% of the way to completion
  vtkIdType target =
    static_cast<vtkIdType>(0.02*outSizeY*outSizeZ*vectorDim) + 1;
  vtkIdType count = 0;

  // write the data one row at a time, do planar-to-packed conversion
  // of vector components if NIFTI file has a vector dimension
  int rowSize = numComponents/vectorDim*outSizeX;
  int c = 0; // counter for vector components
  int j = 0; // counter for rows
  int k = 0; // counter for slices
  int t = 0; // counter for time

  unsigned char *ptr = dataPtr;

  while (!this->AbortExecute && !this->ErrorCode)
    {
    if (vectorDim == 1 && swapBytes == 0)
      {
      // write directly from input, instead of using a buffer
      rowBuffer = ptr;
      ptr += outSizeX*numComponents*scalarSize;
      }
    else
      {
      // create a vector plane from packed vector components
      unsigned char *tmpPtr = rowBuffer;
      z_off_t skipOther = scalarSize*numComponents - fileVoxelIncr;
      for (int i = 0; i < outSizeX; i++)
        {
        // write one vector component of one voxel
        z_off_t nn = fileVoxelIncr;
        do { *tmpPtr++ = *ptr++; } while (--nn);
        // skip past the other components
        ptr += skipOther;
        }
      }

    if (swapBytes != 0 && scalarSize > 1)
      {
      vtkByteSwap::SwapVoidRange(rowBuffer, rowSize, scalarSize);
      }

    if (isCompressed)
      {
      int code = gzwrite(file, rowBuffer, rowSize*scalarSize);
      bytesWritten = (code < 0 ? 0 : code);
      }
    else
      {
      bytesWritten = fwrite(rowBuffer, scalarSize, rowSize, ufile)*scalarSize;
      }
    if (bytesWritten < static_cast<size_t>(rowSize*scalarSize))
      {
      vtkErrorMacro("Insufficient disk space to write file.");
      this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
      break;
      }

    if (++count % target == 0)
      {
      this->UpdateProgress(0.02*count/target);
      }

    if (++j == outSizeY)
      {
      j = 0;
      ptr -= 2*sliceOffset; // for reverse slice order
      if (++k == outSizeZ)
        {
        k = 0;
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

        if (timeDim > 1)
          {
          // if timeDim is included in the vectorDim (and hence in the
          // VTK scalar components) then we have to make sure that
          // the vector components are packed before the time steps
          ptr = dataPtr + (c + t*(vectorDim - 1))/timeDim*fileVoxelIncr;
          }
        }
      }
    }

  if (vectorDim > 1 || swapBytes)
    {
    delete [] rowBuffer;
    }

  if (isCompressed)
    {
    gzclose(file);
    }
  else
    {
    fclose(ufile);
    }

  if (this->ErrorCode == vtkErrorCode::OutOfDiskSpaceError)
    {
    // erase the file, rather than leave a corrupt file on disk
    vtkErrorMacro("Removing incomplete file " << imgname);
    vtksys::SystemTools::RemoveFile(imgname);
    if (!singleFile)
      {
      vtkErrorMacro("Removing file " << hdrname);
      vtksys::SystemTools::RemoveFile(hdrname);
      }
    }

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  delete [] hdrname;
  delete [] imgname;

  return 1;
}
