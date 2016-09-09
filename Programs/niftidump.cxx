/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2016 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMConfig.h"
#include "vtkNIFTIReader.h"
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIPrivate.h"

#include <vtkMatrix4x4.h>
#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// from dicomcli
#include "vtkConsoleOutputWindow.h"
#include "mainmacro.h"

// print the version
void printVersion(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2016, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the help
void printUsage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s file.nii[.gz]\n", cp);
  fprintf(file, "options:\n"
    "  --help      Print a brief help message.\n"
    "  --version   Print the software version.\n");
}

// print the help
void printHelp(FILE *file, const char *cp)
{
  printUsage(file, cp);
  fprintf(file, "\n"
    "Dump the header from a NIfTI file.\n");
}

// sanitize a string (remove unprintable characters)
#define SANITIZE_BUFSIZE 82
const char *stringSanitize(
  char op[SANITIZE_BUFSIZE], const char *cp, size_t l)
{
  if (l >= SANITIZE_BUFSIZE)
  {
    l = SANITIZE_BUFSIZE - 1;
  }

  size_t i;
  for (i = 0; i < l && cp[i] != '\0'; i++)
  {
    if (isprint(cp[i]))
    {
      op[i] = cp[i];
    }
    else
    {
      op[i] = '?';
    }
  }

  op[i] = '\0';

  return op;
}

// remove path portion of filename
const char *fileBasename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// This program will convert
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

  int rval = 0;

  if (argc < 2)
  {
    printUsage(stdout, fileBasename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
  {
    printHelp(stdout, fileBasename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--version") == 0)
  {
    printVersion(stdout, fileBasename(argv[0]));
    return rval;
  }

  vtkSmartPointer<vtkNIFTIReader> reader =
    vtkSmartPointer<vtkNIFTIReader>::New();
  reader->SetFileName(argv[1]);
  reader->UpdateInformation();

  nifti_2_header hdr;
  reader->GetNIFTIHeader()->GetHeader(&hdr);
  int version = 0;
  if (hdr.magic[2] >= '0' && hdr.magic[2] <= '9')
  {
    version = hdr.magic[2] - '0';
  }

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

  // temporary space
  char buf[SANITIZE_BUFSIZE];

  printf("sizeof_hdr: %d\n", (version >= 2 ?
                              vtkNIFTIHeader::Nifti2HeaderSize :
                              vtkNIFTIHeader::Nifti1HeaderSize));
  printf("vox_offset: %lld\n", hdr.vox_offset);
  //printf("data_type: %.10s\n", hdr.data_type);
  //printf("db_name: %.18s\n", hdr.db_name);
  //printf("extents: %d\n", hdr.extents);
  //printf("session_error: %d\n", hdr.session_error);
  //printf("regular: %d\n", hdr.regular);
  printf("dim_info: 0x%x", hdr.dim_info);
  if (hdr.dim_info == 0)
  {
    printf(" (unknown)\n");
  }
  else
  {
    printf(" (freq_dim=%d, phase_dim=%d, slice_dim=%d\n",
           (hdr.dim_info & 0x3),
           ((hdr.dim_info >> 2) & 0x3),
           ((hdr.dim_info >> 4) & 0x3));
  }
  printf("dim:");
  for (int i = 0; i < 8; i++)
  {
    printf(" %lld", hdr.dim[i]);
  }
  printf("\n");
  printf("pixdim:");
  for (int i = 0; i < 8; i++)
  {
    printf(" %g", hdr.pixdim[i]);
  }
  printf("\n");
  printf("xyzt_units: 0x%x (%s, %s)\n",
         hdr.xyzt_units, spaceUnits, timeUnits);
  if (version > 0)
  {
    printf("intent_code: %d (%s)\n",
           hdr.intent_code, intentCode);
    printf("intent_name: \"%s\"\n",
           stringSanitize(buf, hdr.intent_name, sizeof(hdr.intent_name)));
    printf("intent_p1: %g\n", hdr.intent_p1);
    printf("intent_p2: %g\n", hdr.intent_p2);
    printf("intent_p3: %g\n", hdr.intent_p3);
  }
  printf("datatype: %d (%s)\n", hdr.datatype, datatypeName);
  printf("bitpix: %d\n", hdr.bitpix);
  if (version > 0)
  {
    printf("scl_slope: %g\n", hdr.scl_slope);
    printf("scl_inter: %g\n", hdr.scl_inter);
    printf("cal_max: %g\n", hdr.cal_max);
    printf("cal_min: %g\n", hdr.cal_min);
    printf("slice_code: %d (%s)\n", hdr.slice_code, sliceCode);
    printf("slice_start: %lld\n", hdr.slice_start);
    printf("slice_end: %lld\n", hdr.slice_end);
    printf("slice_duration: %g\n", hdr.slice_duration);
    printf("toffset: %g\n", hdr.toffset);
  }
  printf("descrip: \"%s\"\n",
         stringSanitize(buf, hdr.descrip, sizeof(hdr.descrip)));
  printf("aux_file: \"%s\"\n",
         stringSanitize(buf, hdr.aux_file, sizeof(hdr.aux_file)));
  if (version > 0)
  {
    printf("qform_code: %d (%s)\n", hdr.qform_code, xformCode[0]);
    printf("sform_code: %d (%s)\n", hdr.sform_code, xformCode[1]);
    printf("quatern_b: %g\n", hdr.quatern_b);
    printf("quatern_c: %g\n", hdr.quatern_c);
    printf("quatern_d: %g\n", hdr.quatern_d);
    printf("qoffset_x: %g\n", hdr.qoffset_x);
    printf("qoffset_y: %g\n", hdr.qoffset_y);
    printf("qoffset_z: %g\n", hdr.qoffset_z);
    printf("srow_x:");
    for (int i = 0; i < 4; i++)
    {
      printf(" %g", hdr.srow_x[i]);
    }
    printf("\n");
    printf("srow_y:");
    for (int i = 0; i < 4; i++)
    {
      printf(" %g", hdr.srow_y[i]);
    }
    printf("\n");
    printf("srow_z:");
    for (int i = 0; i < 4; i++)
    {
      printf(" %g", hdr.srow_z[i]);
    }
    printf("\n");
    printf("magic: \"%s\"\n",
           stringSanitize(buf, hdr.magic, sizeof(hdr.magic)));
    fflush(stdout);
  }

  return rval;
}
