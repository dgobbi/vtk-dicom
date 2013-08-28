/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkNIFTIReader.h"
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIHeaderPrivate.h"
#include "vtkMatrix4x4.h"
#include "vtkStringArray.h"

#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// remove path portion of filename
const char *niftidump_basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// This program will convert
int main(int argc, char *argv[])
{
  int rval = 0;

  if (argc < 2)
    {
    printf("usage: %s file.nii\n", niftidump_basename(argv[0]));
    return rval;
    }

  vtkSmartPointer<vtkNIFTIReader> reader =
    vtkSmartPointer<vtkNIFTIReader>::New();
  reader->SetFileName(argv[1]);
  reader->UpdateInformation();

  nifti_1_header hdr;
  reader->GetNIFTIHeader()->GetHeader(&hdr);

  const char *datatypeName = "";
  switch (hdr.datatype)
    {
    case NIFTI_TYPE_UINT8:
      datatypeName = "uint8";
      break;
    case NIFTI_TYPE_INT16:
      datatypeName = "int16";
      break;
    case NIFTI_TYPE_INT32:
      datatypeName = "int32";
      break;
    case NIFTI_TYPE_FLOAT32:
      datatypeName = "float32";
      break;
    case NIFTI_TYPE_COMPLEX64:
      datatypeName = "complex64";
      break;
    case NIFTI_TYPE_FLOAT64:
      datatypeName = "float64";
      break;
    case NIFTI_TYPE_RGB24:
      datatypeName = "rgb24";
      break;
    case NIFTI_TYPE_INT8:
      datatypeName = "int8";
      break;
    case NIFTI_TYPE_UINT16:
      datatypeName = "uint16";
      break;
    case NIFTI_TYPE_UINT32:
      datatypeName = "uint32";
      break;
    case NIFTI_TYPE_INT64:
      datatypeName = "int64";
      break;
    case NIFTI_TYPE_UINT64:
      datatypeName = "uint64";
      break;
    case NIFTI_TYPE_FLOAT128:
      datatypeName = "float128";
      break;
    case NIFTI_TYPE_COMPLEX128:
      datatypeName = "complex128";
      break;
    case NIFTI_TYPE_COMPLEX256:
      datatypeName = "complex256";
      break;
    case NIFTI_TYPE_RGBA32:
      datatypeName = "rgba32";
      break;
    }

  static const char *intentCodes[25] = {
    "none", "unknown", "correl", "ttest",
    "ftest", "zscore", "chisq", "beta",
    "binom", "gamma", "poisson", "normal",
    "ftest_nonc", "chisq_nonc", "logistic", "laplace",
    "uniform", "ttest_nonc", "weibull", "chi",
    "invgauss", "extval", "pval", "logpval",
    "log10pval" };
  static const char *intentCodes1000[] = {
    "unknown", "estimate", "label", "neuro_name",
    "gen_matrix", "sym_matrix", "disp_vect", "vector",
    "point_set", "triangle", "quaternion", "dimless" };
  static const char *intentCodes2000[] = {
    "unknown", "time_series", "node_index", "rgb_vector",
    "rgba_vector", "shape" };

  short ic = hdr.intent_code;
  const char *intentCode = "unknown";
  if (ic >= 0 && ic <= 25)
    {
    intentCode = intentCodes[ic];
    }
  else if (ic >= 1000 && ic <= 1011)
    {
    intentCode = intentCodes1000[ic-1000];
    }
  else if (ic >= 2000 && ic <= 2005)
    {
    intentCode = intentCodes2000[ic-2000];
    }

  const char *spaceUnits = "unknown";
  switch (hdr.xyzt_units & 0x7)
    {
    case 1:
      spaceUnits = "meters";
      break;
    case 2:
      spaceUnits = "millimeters";
      break;
    case 3:
      spaceUnits = "microns";
      break;
    }

  const char *timeUnits = "unknown";
  switch (hdr.xyzt_units & 0x38)
    {
    case 8:
      timeUnits = "seconds";
      break;
    case 16:
      timeUnits = "milliseconds";
      break;
    case 24:
      timeUnits = "microseconds";
      break;
    case 32:
      timeUnits = "hertz";
      break;
    case 40:
      timeUnits = "ppm";
      break;
    case 48:
      timeUnits = "radians";
      break;
    }

  const char *sliceCode = "unknown";
  switch (hdr.slice_code)
    {
    case 1:
      sliceCode = "seq_inc";
      break;
    case 2:
      sliceCode = "seq_dec";
      break;
    case 3:
      sliceCode = "alt_inc";
      break;
    case 4:
      sliceCode = "alt_dec";
      break;
    case 5:
      sliceCode = "alt_inc2";
      break;
    case 6:
      sliceCode = "alt_dec2";
      break;
    }

  const char *xformCode[2] = { "unknown", "unknown" };
  short xc[2];
  xc[0] = hdr.qform_code;
  xc[1] = hdr.sform_code;
  for (int i = 0; i < 2; i++)
    {
    switch (xc[i])
      {
      case 1:
        xformCode[i] = "scanner_anat";
        break;
      case 2:
        xformCode[i] = "aligned_anat";
        break;
      case 3:
        xformCode[i] = "talairach";
        break;
      case 4:
        xformCode[i] = "mni_152";
        break;
      }
    }

  cout << "sizeof_hdr: " << hdr.sizeof_hdr << "\n";
  cout << "vox_offset: " << hdr.vox_offset << "\n";
  //cout << "data_type: " << hdr.data_type << "\n";
  //cout << "db_name: " << hdr.db_name << "\n";
  //cout << "extents: " << hdr.extents << "\n";
  //cout << "session_error: " << hdr.session_error << "\n";
  //cout << "regular: " << static_cast<int>(hdr.regular) << "\n";
  cout.setf(std::ios::hex, std::ios::basefield);
  cout << "dim_info: 0x" << static_cast<int>(hdr.dim_info);
  if (hdr.dim_info == 0)
    {
    cout << " (unknown)\n";
    }
  else
    {
    cout << " (freq_dim=" << (hdr.dim_info & 0x3)
         << ", phase_dim=" << ((hdr.dim_info >> 2) & 0x3)
         << ", slice_dim=" << ((hdr.dim_info >> 4) & 0x3) << ")\n";
    }
  cout.unsetf(std::ios::hex);
  cout << "dim:";
  for (int i = 0; i < 8; i++)
    {
    cout << " " << hdr.dim[i];
    }
  cout << "\n";
  cout << "pixdim:";
  for (int i = 0; i < 8; i++)
    {
    cout << " " << hdr.pixdim[i];
    }
  cout << "\n";
  cout.setf(std::ios::hex, std::ios::basefield);
  cout << "xyzt_units: 0x" << static_cast<int>(hdr.xyzt_units)
       << " (" << spaceUnits << ", " << timeUnits << ")\n";
  cout.unsetf(std::ios::hex);
  cout << "intent_code: " << hdr.intent_code
       << " (" << intentCode << ")\n";
  cout << "intent_name: \"";
  for (size_t j = 0;
       j < sizeof(hdr.intent_name) && hdr.intent_name[j] != '\0';
       j++)
    {
    cout << (isprint(hdr.intent_name[j]) ? hdr.intent_name[j] : '?');
    }
  cout << "\"\n";
  cout << "intent_p1: " << hdr.intent_p1 << "\n";
  cout << "intent_p2: " << hdr.intent_p2 << "\n";
  cout << "intent_p3: " << hdr.intent_p3 << "\n";
  cout << "datatype: " << hdr.datatype
     << " (" << datatypeName << ")\n";
  cout << "bitpix: " << hdr.bitpix << "\n";
  cout << "scl_slope: " << hdr.scl_slope << "\n";
  cout << "scl_inter: " << hdr.scl_inter << "\n";
  cout << "cal_max: " << hdr.cal_max << "\n";
  cout << "cal_min: " << hdr.cal_min << "\n";
  cout << "slice_code: " << static_cast<int>(hdr.slice_code)
       << " (" << sliceCode << ")\n";
  cout << "slice_start: " << hdr.slice_start << "\n";
  cout << "slice_end: " << hdr.slice_end << "\n";
  cout << "slice_duration: " << hdr.slice_duration << "\n";
  cout << "toffset: " << hdr.toffset << "\n";
  cout << "descrip: \"";
  for (size_t j = 0; j < sizeof(hdr.descrip) && hdr.descrip[j] != '\0'; j++)
    {
    cout << (isprint(hdr.descrip[j]) ? hdr.descrip[j] : '?');
    }
  cout << "\"\n";
  cout << "aux_file: \"";
  for (size_t j = 0; j < sizeof(hdr.aux_file) && hdr.aux_file[j] != '\0'; j++)
    {
    cout << (isprint(hdr.aux_file[j]) ? hdr.aux_file[j] : '?');
    }
  cout << "\"\n";
  cout << "qform_code: " << hdr.qform_code
       << " (" << xformCode[0] << ")\n";
  cout << "sform_code: " << hdr.sform_code
       << " (" << xformCode[1] << ")\n";
  cout << "quatern_b: " << hdr.quatern_b << "\n";
  cout << "quatern_c: " << hdr.quatern_c << "\n";
  cout << "quatern_d: " << hdr.quatern_d << "\n";
  cout << "qoffset_x: " << hdr.qoffset_x << "\n";
  cout << "qoffset_y: " << hdr.qoffset_y << "\n";
  cout << "qoffset_z: " << hdr.qoffset_z << "\n";
  cout << "srow_x:";
  for (int i = 0; i < 4; i++)
    {
    cout << " " << hdr.srow_x[i];
    }
  cout << "\n";
  cout << "srow_y:";
  for (int i = 0; i < 4; i++)
    {
    cout << " " << hdr.srow_y[i];
    }
  cout << "\n";
  cout << "srow_z:";
  for (int i = 0; i < 4; i++)
    {
    cout << " " << hdr.srow_z[i];
    }
  cout << "\n";
  cout << "magic: \"";
  for (size_t j = 0; j < sizeof(hdr.magic) && hdr.magic[j] != '\0'; j++)
    {
    cout << (isprint(hdr.magic[j]) ? hdr.magic[j] : '?');
    }
  cout << "\"" << endl;

  return rval;
}
