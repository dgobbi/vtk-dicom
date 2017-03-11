/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMImageCodec.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMUtilities.h"

#include <stddef.h>

//----------------------------------------------------------------------------
const char *vtkDICOMImageCodec::UIDs[21] = {
  "1.2.840.10008.1.2.1",     // LittleEndian
  "1.2.840.10008.1.2.2",     // BigEndian
  "1.2.840.10008.1.2.5",     // RLE
  "1.2.840.10008.1.2.4.50",  // JPEGBaseline
  "1.2.840.10008.1.2.4.51",  // JPEGExtended
  "1.2.840.10008.1.2.4.57",  // JPEGLossless
  "1.2.840.10008.1.2.4.70",  // JPEGPrediction
  "1.2.840.10008.1.2.4.80",  // JPEGLS
  "1.2.840.10008.1.2.4.81",  // JPEGLSConstrained
  "1.2.840.10008.1.2.4.90",  // JPEG2K
  "1.2.840.10008.1.2.4.91",  // JPEG2KLossless
  "1.2.840.10008.1.2.4.100", // MPEG2ML
  "1.2.840.10008.1.2.4.101", // MPEG2HL
  "1.2.840.10008.1.2.4.102", // MPEG4HPL41
  "1.2.840.10008.1.2.4.103", // MPEG4HPL41BD
  "1.2.840.10008.1.2.4.104", // MPEG4HPL42V2D
  "1.2.840.10008.1.2.4.105", // MPEG4HPL42V3D
  "1.2.840.10008.1.2.4.106", // MPEG4HPL42Stereo
  "1.2.840.10008.1.2.4.107", // HEVCMPL51
  "1.2.840.10008.1.2.4.108", // HEVCM10PL51
  0
};

//----------------------------------------------------------------------------
vtkDICOMImageCodec::ImageFormat::ImageFormat(vtkDICOMMetaData *meta)
{
  this->Rows = meta->GetAttributeValue(DC::Rows).AsInt();
  this->Columns = meta->GetAttributeValue(DC::Columns).AsInt();
  this->BitsAllocated = meta->GetAttributeValue(DC::BitsAllocated).AsInt();
  this->BitsStored = meta->GetAttributeValue(DC::BitsStored).AsInt();
  this->PixelRepresentation =
    meta->GetAttributeValue(DC::PixelRepresentation).AsInt();
  this->SamplesPerPixel =
    meta->GetAttributeValue(DC::SamplesPerPixel).AsInt();
  this->PlanarConfiguration =
    meta->GetAttributeValue(DC::PlanarConfiguration).AsInt();
  const char *lossy =
    meta->GetAttributeValue(DC::AllowLossyCompression).GetCharData();
  this->AllowLossyCompression = (lossy && strncmp(lossy, "YES", 3) == 0);
}

//----------------------------------------------------------------------------
vtkDICOMImageCodec::vtkDICOMImageCodec(const std::string& tsyntax)
{
  int key = 255;
  const char *ts = tsyntax.c_str();

  for (int i = 0; i < NumberOfCodecs; i++)
  {
    if (strcmp(ts, vtkDICOMImageCodec::UIDs[i]) == 0)
    {
      key = i;
      break;
    }
  }

  this->Key = static_cast<unsigned char>(key);
}

//----------------------------------------------------------------------------
std::string vtkDICOMImageCodec::GetTransferSyntaxUID() const
{
  const char *result = "";

  if (this->Key < NumberOfCodecs)
  {
    result = vtkDICOMImageCodec::UIDs[this->Key];
  }

  return result;
}

//----------------------------------------------------------------------------
int vtkDICOMImageCodec::DecodeRLE(
  const ImageFormat& image,
  const unsigned char *source, size_t sourceSize,
  unsigned char *dest, size_t destSize)
{
  const unsigned char *inPtr = source;
  unsigned char *outPtr = dest;
  int errorCode = NoError;

  // get the number of segments and the segment size
  unsigned int n = vtkDICOMUtilities::UnpackUnsignedInt(inPtr);
  size_t segmentSize = destSize/n;

  // get the samples per pixel (spp) and bytes per sample (bps)
  unsigned int spp = image.SamplesPerPixel;
  spp = (spp == 0 ? 1 : spp);
  spp = (n % spp != 0 ? n : spp);
  unsigned int bps = n/spp;

  // the amount to advance after each output byte
  unsigned int outInc = (image.PlanarConfiguration ? bps : n);
  // the amount to advance advance after each sample
  size_t segInc = (image.PlanarConfiguration ? segmentSize : 1);
  segInc *= bps;

  // this will set endiancheck.s to 1 on little endian architectures
  union { char c[2]; short s; } endiancheck;
  endiancheck.c[0] = 1;
  endiancheck.c[1] = 0;

  // loop over all RLE segments
  for (unsigned int i = 0; i < n; i++)
  {
    // sample position in pixel
    unsigned int s = i / bps;
    // byte position in sample
    unsigned int b = i % bps;
    // compute the offset into the output buffer for this segment
    size_t outOffset = s*segInc + b; // big-endian
    if (endiancheck.s == 1) // little-endian
    {
      outOffset = s*segInc + (bps - b - 1);
    }
    // get the offset into the input buffer for this segment
    unsigned int offset =
      vtkDICOMUtilities::UnpackUnsignedInt(inPtr + (i+1)*4);
    if (offset >= sourceSize)
    {
      break;
    }
    // loop over the segment and decompress it
    const signed char *cp =
      reinterpret_cast<const signed char *>(inPtr + offset);
    signed char *dp = reinterpret_cast<signed char *>(outPtr + outOffset);
    size_t remaining = segmentSize;
    while (remaining > 0 && offset < sourceSize)
    {
      if (++offset == sourceSize)
      {
        break;
      }
      // check the indicator byte (use short to avoid overflow)
      short c = *cp++;
      if (c >= 0)
      {
        // do a literal run
        c = c + 1;
        if (sourceSize - offset < static_cast<size_t>(c))
        {
          // safety check: limit to the number available input bytes
          c = static_cast<short>(sourceSize - offset);
        }
        offset += c;
        if (static_cast<size_t>(c) > remaining)
        {
          // safety check: limit to the size of the output dest
          c = static_cast<short>(remaining);
        }
        remaining -= c;
        do
        {
          *dp = *cp++;
          dp += outInc;
        }
        while (--c);
      }
      else if (c > -128)
      {
        // do a replication run
        c = 1 - c;
        offset += 1;
        if (static_cast<size_t>(c) > remaining)
        {
          // safety check: limit to the size of the output dest
          c = static_cast<short>(remaining);
        }
        remaining -= c;
        do
        {
          *dp = *cp;
          dp += outInc;
        }
        while (--c);
        cp++;
      }
    }
    if (remaining > 0)
    {
      // short read, clear remainder of dest
      errorCode = MissingData;
      do
      {
        *dp = 0;
        dp += outInc;
      }
      while (--remaining);
    }
  }

  return errorCode;
}

//----------------------------------------------------------------------------
int vtkDICOMImageCodec::EncodeRLE(
  const ImageFormat& image,
  const unsigned char *source, size_t sourceSize,
  unsigned char **destP, size_t *destSizeP)
{
  int errorCode = NoError;

  // get the samples per pixel (spp) and bytes per sample (bps)
  unsigned int spp = image.SamplesPerPixel;
  spp = (spp == 0 ? 1 : spp);
  unsigned int bps = (image.BitsAllocated + 7)/8;
  bps = (bps == 0 ? 1 : bps);

  // the number of segments
  unsigned int n = spp*bps;
  if (n == 0 || n > 15)
  {
    *destP = 0;
    *destSizeP = 0;
    return BadPixelFormat;
  }

  // number of bytes per segment
  size_t segmentSize = sourceSize/n;

  // the amount to advance after each input byte
  unsigned int inInc = (image.PlanarConfiguration ? bps : n);
  // the amount to advance after each sample
  size_t segInc = (image.PlanarConfiguration ? segmentSize : 1);
  segInc *= bps;

  // allocate the destination buffer
  size_t destReserve = 4000;
  unsigned char *dest = new unsigned char[destReserve];

  // write the table
  vtkDICOMUtilities::PackUnsignedInt(n, dest);
  for (unsigned int i = 0; i < 15; i++)
  {
    vtkDICOMUtilities::PackUnsignedInt(0, dest + 4*(i + 1));
  }

  // the offset to the first segment
  unsigned int offset = 64;
  unsigned short rowlen = image.Columns;
  size_t numrows = sourceSize/(n*rowlen);

  // this will set endiancheck.s to 1 on little endian architectures
  union { char c[2]; short s; } endiancheck;
  endiancheck.c[0] = 1;
  endiancheck.c[1] = 0;

  // loop over all RLE segments
  // write the segments
  for (unsigned int i = 0; i < n; i++)
  {
    // write the offset into the table
    vtkDICOMUtilities::PackUnsignedInt(offset, dest + 4*(i + 1));
    // sample position in pixel
    unsigned int s = i / bps;
    // byte position in sample
    unsigned int b = i % bps;
    // compute the offset into the input buffer for this segment
    size_t inOffset = s*segInc + b; // big-endian
    if (endiancheck.s == 1) // little-endian
    {
      inOffset = s*segInc + (bps - b - 1);
    }
    const signed char *cp =
      reinterpret_cast<const signed char *>(source + inOffset);
    signed char *dp = reinterpret_cast<signed char *>(dest + offset);

    for (size_t j = 0; j < numrows; j++)
    {
      const signed char *ep = cp + rowlen*inInc;
      while (cp != ep)
      {
        short maxcount = 128;
        ptrdiff_t remainder = (ep - cp)/inInc;
        maxcount = (remainder < maxcount ? remainder : maxcount);
        short counter = maxcount;
        const signed char *sp = cp;

        // count repeated characters
        signed char prev = *cp;
        do
        {
          cp += inInc;
        }
        while (--counter != 0 && *cp == prev);

        if (maxcount - counter > 1)
        {
          // negative count for repeating
          counter = -(maxcount - counter - 1);
        }
        else if (counter > 0)
        {
          // count non-repeated bytes until a triplicate found
          signed char pprev;
          do
          {
            pprev = prev;
            prev = *cp;
            cp += inInc;
          }
          while (--counter != 0 && (*cp != prev || prev != pprev));

          // positive count for literal
          counter = maxcount - counter - 1;

          // remove repeats at the end that can join with next run
          if (remainder > counter + 1 && *cp == prev)
          {
            short reps = 1 + (prev == pprev);
            reps = (reps < counter ? reps : counter);
            counter -= reps;
            cp -= reps*inInc;
          }

          // increment for the next offset into the destination
          offset += counter;
        }

        // at least two bytes are always written to destination
        offset += 2;

        // check whether destination buffer is large enough
        if (offset > destReserve)
        {
          destReserve *= 2;
          unsigned char *newdest = new unsigned char[destReserve];
          size_t size = dp-reinterpret_cast<signed char *>(dest);
          memcpy(newdest, dest, size);
          delete [] dest;
          dest = newdest;
          dp = reinterpret_cast<signed char *>(dest + size);
        }

        // write the results
        *dp++ = counter;
        do
        {
          *dp++ = *sp;
          sp += inInc;
        }
        while (--counter >= 0);
      }
    }

    // add a pad byte to the segment if needed
    if ((offset & 1) != 0)
    {
      offset++;
      *dp = 0;
    }
  }

  *destP = dest;
  *destSizeP = offset;

#if 0
  // check code, to make sure it unpacks into an identical stream
  unsigned char *check = new unsigned char[sourceSize];
  DecodeRLE(image, dest, offset, check, sourceSize);

  for (size_t k = 0; k < sourceSize; k++)
  {
    assert(source[k] == check[k]);
  }
  delete [] check;
#endif

  return errorCode;
}

//----------------------------------------------------------------------------
int vtkDICOMImageCodec::Decode(
  const ImageFormat& image,
  const unsigned char *source, size_t sourceSize,
  unsigned char *dest, size_t destSize) const
{
  int code = MissingCodec;
  if (this->Key == RLE)
  {
    code = DecodeRLE(image, source, sourceSize, dest, destSize);
  }

  return code;
}

//----------------------------------------------------------------------------
int vtkDICOMImageCodec::Encode(
  const ImageFormat& image,
  const unsigned char *source, size_t sourceSize,
  unsigned char **dest, size_t *destSize) const
{
  int code = MissingCodec;
  if (this->Key == RLE)
  {
    code = EncodeRLE(image, source, sourceSize, dest, destSize);
  }

  return code;
}

//----------------------------------------------------------------------------
ostream& operator<<(ostream& o, const vtkDICOMImageCodec& a)
{
  std::string c = a.GetTransferSyntaxUID();
  if (c == "")
  {
    c = "Unknown";
  }
  return o << c;
}
