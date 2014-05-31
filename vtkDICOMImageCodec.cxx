/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMImageCodec.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMUtilities.h"

#include <assert.h>

//----------------------------------------------------------------------------
const char *vtkDICOMImageCodec::UIDs[16] = {
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
  "1.2.840.10008.1.2.4.102", // MPEG2HP
  "1.2.840.10008.1.2.4.103", // MPEG2BD
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

  // the amount to advance after each output byte
  unsigned int outInc = (image.PlanarConfiguration ? 1 : n);
  // the amount to advance advance after each segment
  size_t segInc = (image.PlanarConfiguration ? segmentSize : 1);

  // loop over all RLE segments
  for (unsigned int i = 0; i < n; i++)
    {
    // get the offset for this segment
    unsigned int offset =
      vtkDICOMUtilities::UnpackUnsignedInt(inPtr + (i+1)*4);
    if (offset >= sourceSize)
      {
      break;
      }
    // loop over the segment and decompress it
    const signed char *cp =
      reinterpret_cast<const signed char *>(inPtr + offset);
    signed char *dp = reinterpret_cast<signed char *>(outPtr + i*segInc);
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
          c = remaining;
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
          c = remaining;
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

  // the number of segments
  unsigned int n = (image.BitsAllocated + 7)/8*image.SamplesPerPixel;
  if (n == 0 || n > 15)
    {
    *destP = 0;
    *destSizeP = 0;
    return BadPixelFormat;
    }

  // number of bytes per segment
  size_t segmentSize = sourceSize/n;

  // the amount to advance after each output byte
  unsigned int inInc = (image.PlanarConfiguration ? 1 : n);
  // the amount to advance advance after each segment
  size_t segInc = (image.PlanarConfiguration ? segmentSize : 1);

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

  // write the segments
  for (unsigned int i = 0; i < n; i++)
    {
    // write the offset into the table
    vtkDICOMUtilities::PackUnsignedInt(offset, dest + 4*(i + 1));
    const signed char *cp =
      reinterpret_cast<const signed char *>(source + i*segInc);
    signed char *dp = reinterpret_cast<signed char *>(dest + offset);

    for (size_t j = 0; j < numrows; j++)
      {
      const signed char *ep = cp + rowlen*inInc;
      while (cp != ep)
        {
        short maxcount = 128;
        ptrdiff_t remainder = ep - cp;
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
