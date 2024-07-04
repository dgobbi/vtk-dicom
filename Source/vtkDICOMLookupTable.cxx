/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2024 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMLookupTable.h"
#include "vtkDICOMMetaData.h"

#include "vtkObjectFactory.h"

#include <string.h>

vtkStandardNewMacro(vtkDICOMLookupTable);

//----------------------------------------------------------------------------
vtkDICOMLookupTable::vtkDICOMLookupTable()
{
}

//----------------------------------------------------------------------------
vtkDICOMLookupTable::~vtkDICOMLookupTable()
{
}

//----------------------------------------------------------------------------
void vtkDICOMLookupTable::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
void vtkDICOMLookupTable::BuildStandardPalette(const char *cs)
{
  if (cs == nullptr)
  {
    vtkErrorMacro("Null string passed to BuildStandardPalette()!");
  }
  else if (strcmp(cs, "HOT_IRON") == 0)
  {
    // use small adjustments to exactly match the DICOM hot iron table,
    // while still maintaining the ability to create a table of any size
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      if (x < 0.5)
      {
        rgba[0] = 2.0*x;
      }
      else if (x < 0.5 + 0.5/255.0)
      {
        rgba[0] = 1.0;
      }
      else if (x < 0.75 - 0.25/255.0)
      {
        rgba[0] = 1.0;
        rgba[1] = 2.0*x - (1.0 + 1.0/255.0);
      }
      else if (x < 1.0 - 0.25/255.0)
      {
        rgba[0] = 1.0;
        rgba[1] = 2.0*x - (1.0 + 1.0/255.0);
        rgba[2] = 4.0*x - (3.0 - 1.0/255.0);
      }
      else if (x < 1.0)
      {
        rgba[0] = 1.0;
        rgba[1] = 2.0*x - (1.0 + 1.0/255.0);
        rgba[2] = 1.0;
      }
      else
      {
        rgba[0] = 1.0;
        rgba[1] = 1.0;
        rgba[2] = 1.0;
      }
      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
    this->Modified();
  }
  else if (strcmp(cs, "PET") == 0)
  {
    // algorithmically create the table, this uses linear segments that
    // have been fit to the numerical data in the standard table
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      if (x < 0.2475252060520769 - 0.5/(n - 1))
      {
        rgba[1] = 2.024199843871975*x - 0.001028608164577255;
        rgba[2] = 2.0*x - 0.00392156862745098;
      }
      else if (x < 0.2475252060520769 + 0.5/(n - 1))
      {
        rgba[1] = 0.5;
        rgba[2] = 2.0*x - 0.00392156862745098;
      }
      else if (x < 0.5019607843137255)
      {
        rgba[0] = 1.9792076771653557*x -0.49153398564149964;
        rgba[1] = -1.9765567765567764*x + 0.9892594986712628;
        rgba[2] = 2.0*x - 0.00392156862745098;
      }
      else if (x < 0.5029411764705882)
      {
        rgba[0] = 1.9792076771653557*x -0.49153398564149964;
        rgba[1] = -1.9765567765567764*x + 0.9892594986712628;
        rgba[2] = 1.0;
      }
      else if (x < 0.7531036189872085)
      {
        rgba[0] = 1.9792076771653557*x -0.49153398564149964;
        rgba[1] = 2.0*x - 1.00392156862745;
        rgba[2] = -4.0*x + 3.011764705882353;
      }
      else if (x < 1.0)
      {
        rgba[0] = 1.0;
        rgba[1] = 2.0*x - 1.00392156862745;
        rgba[2] = 4.0428344791115824*x - 3.045323047251687;
      }
      else
      {
        rgba[0] = 1.0;
        rgba[1] = 1.0;
        rgba[2] = 1.0;
      }
      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
    this->Modified();
  }
  else if (strcmp(cs, "HOT_METAL_BLUE") == 0)
  {
    // algorithmically create the "hot metal blue" table
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      if (x < 0.3333333333333333)
      {
        rgba[2] = 1.96*x;
      }
      else if (x < 0.4)
      {
        rgba[0] = 3.0*x - 1.0;
        rgba[2] = 1.96*x;
      }
      else if (x < 0.4666666666666666)
      {
        rgba[0] = 2.25*x - 0.7;
        rgba[2] = 1.96 - 2.94*x;
      }
      else if (x < 0.5333333333333333)
      {
        rgba[0] = 3.0*x - 1.05;
        rgba[1] = 1.875*x - 0.875;
        rgba[2] = 3.332 - 5.88*x;
      }
      else if (x < 0.6)
      {
        rgba[0] = 3.0*x - 1.05;
        rgba[1] = 1.875*x - 0.875;
        rgba[2] = 1.764 - 2.94*x;
      }
      else if (x < 0.6666666666666666)
      {
        rgba[0] = 3.75*x - 1.5;
        rgba[1] = 1.875*x - 0.875;
        rgba[2] = 0.0;
      }
      else if (x < 0.9333333333333333)
      {
        rgba[0] = 1.0;
        rgba[1] = 1.875*x - 0.875;
        rgba[2] = 2.95*x - 1.9666666666666666;
      }
      else if (x < 1.0)
      {
        rgba[0] = 1.0;
        rgba[1] = 1.875*x - 0.875;
        rgba[2] = 3.2*x - 2.2;
      }
      else
      {
        rgba[0] = 1.0;
        rgba[1] = 1.0;
        rgba[2] = 1.0;
      }
      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
    this->Modified();
  }
  else if (strcmp(cs, "PET_20_STEP") == 0)
  {
    // segment the table into 20 steps
    double values[20][4] = {
      { 0.0, 0.0, 0.0, 1.0 },
      { 0.3764705882352941, 0.0, 0.3137254901960784, 1.0 },
      { 0.18823529411764706, 0.18823529411764706, 0.3137254901960784, 1.0 },
      { 0.18823529411764706, 0.18823529411764706, 0.4392156862745098, 1.0 },
      { 0.3137254901960784, 0.3137254901960784, 0.5019607843137255, 1.0 },
      { 0.3764705882352941, 0.3764705882352941, 0.6901960784313725, 1.0 },
      { 0.4392156862745098, 0.4392156862745098, 0.7529411764705882, 1.0 },
      { 0.5019607843137255, 0.5019607843137255, 0.8784313725490196, 1.0 },
      { 0.18823529411764706, 0.3764705882352941, 0.18823529411764706, 1.0 },
      { 0.18823529411764706, 0.5647058823529412, 0.18823529411764706, 1.0 },
      { 0.3137254901960784, 0.7529411764705882, 0.3137254901960784, 1.0 },
      { 0.25098039215686274, 0.8784313725490196, 0.25098039215686274, 1.0 },
      { 0.8784313725490196, 0.8784313725490196, 0.3137254901960784, 1.0 },
      { 0.8156862745098039, 0.8156862745098039, 0.3764705882352941, 1.0 },
      { 0.8156862745098039, 0.6901960784313725, 0.25098039215686274, 1.0 },
      { 0.8156862745098039, 0.5647058823529412, 0.0, 1.0 },
      { 0.7529411764705882, 0.3764705882352941, 0.0, 1.0 },
      { 0.6901960784313725, 0.18823529411764706, 0.0, 1.0 },
      { 1.0, 0.0, 0.0, 1.0 },
      { 1.0, 1.0, 1.0, 1.0 }
    };
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      double *rgba;
      if (x < 0.05) { rgba = values[0]; }
      else if (x < 0.10) { rgba = values[1]; }
      else if (x < 0.15) { rgba = values[2]; }
      else if (x < 0.20) { rgba = values[3]; }
      else if (x < 0.25) { rgba = values[4]; }
      else if (x < 0.30) { rgba = values[5]; }
      else if (x < 0.35) { rgba = values[6]; }
      else if (x < 0.40) { rgba = values[7]; }
      else if (x < 0.45) { rgba = values[8]; }
      else if (x < 0.50) { rgba = values[9]; }
      else if (x < 0.55) { rgba = values[10]; }
      else if (x < 0.60) { rgba = values[11]; }
      else if (x < 0.65) { rgba = values[12]; }
      else if (x < 0.70) { rgba = values[13]; }
      else if (x < 0.75) { rgba = values[14]; }
      else if (x < 0.80) { rgba = values[15]; }
      else if (x < 0.85) { rgba = values[16]; }
      else if (x < 0.90) { rgba = values[17]; }
      else if (x < 0.95) { rgba = values[18]; }
      else { rgba = values[19]; }

      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
    this->Modified();
  }
  else if (strcmp(cs, "SPRING") == 0)
  {
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      rgba[0] = 1.0;
      rgba[1] = x;
      rgba[2] = 1.0 - x;

      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
    this->Modified();
  }
  else if (strcmp(cs, "SUMMER") == 0)
  {
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      rgba[0] = x;
      rgba[1] = 0.5 + 0.5*x;
      rgba[2] = 0.4;

      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
  }
  else if (strcmp(cs, "FALL") == 0)
  {
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      rgba[0] = 1.0;
      rgba[1] = x;
      rgba[2] = 0.0;

      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
    this->Modified();
  }
  else if (strcmp(cs, "WINTER") == 0)
  {
    int n = this->GetNumberOfColors();
    unsigned char *cptr = this->WritePointer(0, n);
    double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
    for (int i = 0; i < n; i++)
    {
      double x = static_cast<double>(i)/(n - 1);
      rgba[0] = 0.0;
      rgba[1] = x;
      rgba[2] = 1.0 - x*0.5;

      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMLookupTable::BuildImagePalette(
  vtkDICOMMetaData *meta, int fileIndex)
{
  const DC::EnumType descTag[] = {
    DC::RedPaletteColorLookupTableDescriptor,
    DC::GreenPaletteColorLookupTableDescriptor,
    DC::BluePaletteColorLookupTableDescriptor,
    DC::AlphaPaletteColorLookupTableDescriptor
  };
  const DC::EnumType dataTag[] = {
    DC::RedPaletteColorLookupTableData,
    DC::GreenPaletteColorLookupTableData,
    DC::BluePaletteColorLookupTableData,
    DC::AlphaPaletteColorLookupTableData
  };
  const DC::EnumType segTag[] = {
    DC::SegmentedRedPaletteColorLookupTableData,
    DC::SegmentedGreenPaletteColorLookupTableData,
    DC::SegmentedBluePaletteColorLookupTableData,
    DC::SegmentedAlphaPaletteColorLookupTableData
  };

  int isSigned = meta->Get(fileIndex, DC::PixelRepresentation).AsInt();
  int minValue = VTK_INT_MAX;
  int maxValue = VTK_INT_MIN;
  int firstValue[4] = { 0, 0, 0, 0 };
  int lastValue[4] = { 0, 0, 0, 0 };
  double divisor[4] = { 255.0, 255.0, 255.0, 255.0 };
  const unsigned short *spp[4] = { nullptr, nullptr, nullptr, nullptr };
  const unsigned char *cpp[4] = { nullptr, nullptr, nullptr, nullptr };
  const unsigned short *segpp[4] = { nullptr, nullptr, nullptr, nullptr };
  unsigned int segn[4] = { 0, 0, 0, 0 };

  for (int j = 0; j < 4; j++)
  {
    const vtkDICOMValue& v = meta->Get(fileIndex, descTag[j]);
    // Descriptor must have three values
    if (v.GetNumberOfValues() == 3)
    {
      // First value is number of entries in the this
      int n = v.GetUnsignedShort(0);
      n = (n == 0 ? 65536 : n);

      // Second value is the first pixel value that is mapped
      unsigned short f = v.GetUnsignedShort(1);
      firstValue[j] = (isSigned ? static_cast<short>(f) : f);

      // Compute the last pixel value that is mapped
      lastValue[j] = firstValue[j] + n - 1;
      minValue = (firstValue[j] < minValue ? firstValue[j] : minValue);
      maxValue = (lastValue[j] > maxValue ? lastValue[j] : maxValue);

      // Third value is the number of bits per lookup table entry
      int nbits = v.GetUnsignedShort(2);
      divisor[j] = (nbits == 0 ? 1.0 : (1u << nbits) - 1.0);

      // Get the lookup table data and confirm its size
      const vtkDICOMValue& d = meta->Get(fileIndex, dataTag[j]);
      if (d.IsValid())
      {
        if (d.GetVL() >= static_cast<unsigned int>(2*n))
        {
          spp[j] = d.GetUnsignedShortData();
        }
        else if (d.GetVL() >= static_cast<unsigned int>(n))
        {
          cpp[j] = d.GetUnsignedCharData();
          if (cpp[j] == nullptr)
          {
            cpp[j] = reinterpret_cast<const unsigned char *>(
              d.GetUnsignedShortData());
          }
        }
      }
      else
      {
        // Search for segmented table data
        const vtkDICOMValue& s = meta->Get(fileIndex, segTag[j]);
        segpp[j] = s.GetUnsignedShortData();
        segn[j] = s.GetVL()/2;
      }
    }
  }

  if (maxValue > minValue)
  {
    // Generate the lookup table
    this->SetRange(minValue, maxValue);
    this->SetNumberOfColors(maxValue - minValue + 1);
    unsigned char *cptr = this->WritePointer(0, maxValue - minValue + 1);
    for (int i = minValue; i <= maxValue; i++)
    {
      double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
      for (int j = 0; j < 4; j++)
      {
        int k = i - firstValue[j];
        if (i < firstValue[j]) { k = 0; }
        if (i > lastValue[j]) { k = lastValue[j] - firstValue[j]; }
        if (spp[j])
        {
          rgba[j] = spp[j][k] / divisor[j];
        }
        else if (cpp[j])
        {
          rgba[j] = cpp[j][k] / divisor[j];
        }
      }
      cptr[0] = static_cast<unsigned char>(rgba[0]*255.0 + 0.5);
      cptr[1] = static_cast<unsigned char>(rgba[1]*255.0 + 0.5);
      cptr[2] = static_cast<unsigned char>(rgba[2]*255.0 + 0.5);
      cptr[3] = static_cast<unsigned char>(rgba[3]*255.0 + 0.5);
      cptr += 4;
    }

    // Handle segmented lookup tables
    cptr = this->WritePointer(0, maxValue - minValue + 1);
    for (int j = 0; j < 4; j++)
    {
      if (segpp[j])
      {
        if (!vtkDICOMLookupTable::BuildSegmentedLUT(
          segpp[j], segn[j], divisor[j], cptr+j, 4, maxValue-minValue+1))
        {
        static const char *names[] = { "Red", "Green", "Blue", "Alpha" };
        vtkErrorMacro("Bad data in Segmented " << names[j]
                      << " PaletteColorLookupTableData");
        }
      }
    }
  }

  this->Modified();
}

//----------------------------------------------------------------------------
bool vtkDICOMLookupTable::BuildSegmentedLUT(
  const unsigned short *input, unsigned int n, double divisor,
  unsigned char *lut, unsigned int stride, unsigned int count)
{
  // i is position in input, j is position in output
  unsigned int i = 0;
  unsigned int j = 0;

  while (i+1 < n)
  {
    unsigned char opcode = input[i++];
    if (opcode == 0)
    {
      // discrete segment
      unsigned short l = input[i++];
      for (unsigned short k = 0; k < l && i < n && j < count; k++, j++, i++)
      {
        double y = input[i]/divisor;
        lut[j*stride] = static_cast<unsigned char>(y*255.0 + 0.5);
      }
    }
    else if (opcode == 1)
    {
      // linear segment
      unsigned short l = input[i++];
      double y0 = 0.0;
      if (j > 0)
      {
        // start of the ramp
        y0 = lut[(j - 1)*stride]/255.0;
      }
      if (i < n)
      {
        // end of the ramp
        double y1 = input[i++]/divisor;
        // generate the ramp
        for (unsigned short k = 0; k < l && j < count; k++, j++)
        {
          double y = y0 + (k + 1)*(y1 - y0)/l;
          lut[j*stride] = static_cast<unsigned char>(y*255.0 + 0.5);
        }
      }
    }
    else if (opcode == 2)
    {
      // indirect segment
      bool failed = true;
      unsigned short nseg = input[i++];
      if (i + 1 < n)
      {
        failed = false;
        // offset to first segment to use
        unsigned int offset = input[i++];
        offset += input[i++] << 16;
        // m is the number of input elements referred to, and
        // l is the number of lut entries that will be generated
        unsigned int m = 0;
        unsigned int l = 0;
        // compute m by looking at the segments
        for (unsigned int k = 0; k < nseg && offset + m + 1 < n; k++)
        {
          unsigned short opcode2 = input[offset + m++];
          if (opcode2 == 0)
          {
            // discrete
            l += input[offset + m];
            m += 1 + input[offset + m];
          }
          else if (opcode2 == 1)
          {
            // linear
            l += input[offset + m];
            m += 2;
          }
          else
          {
            // illegal opcode
            failed = true;
            break;
          }
        }

        if (offset + m <= n)
        {
          // add the referenced segments via recursion
          BuildSegmentedLUT(
            &input[offset], m, divisor, &lut[j*stride], stride, count-j);

          // increment the position in the output lut
          if (j + l > count)
          {
            l = count - j;
          }
          j += l;
        }
      }
      if (failed)
      {
        break;
      }
    }
    else
    {
      // unrecognized opcode
      break;
    }
  }

  if (j < count)
  {
    // If write was incomplete, fill the remainder of the lookup table
    // with alternating high and low to visually indicate that a
    // problem occurred.
    while (j < count)
    {
      lut[j*stride] = (j & 1)*255;
      j++;
    }

    return false;
  }

  return true;
}
