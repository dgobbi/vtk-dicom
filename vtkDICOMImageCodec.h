/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMImageCodec_h
#define __vtkDICOMImageCodec_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"

#include <string>

class vtkDICOMMetaData;

//! Codecs for encapsulated images.
/*!
 *  DICOM supports a wide variety of image compression methods.
 */
class VTK_DICOM_EXPORT vtkDICOMImageCodec
{
public:
  enum EnumType
  {
    LittleEndian,      // 1.2.1     Little endian
    BigEndian,         // 1.2.2     Big endian
    RLE,               // 1.2.5     RLE packbits
    JPEGBaseline,      // 1.2.4.50  JPEG baseline (1)
    JPEGExtended,      // 1.2.4.51  JPEG extended (1,2,4)
    JPEGLossless,      // 1.2.4.57  JPEG lossless (14)
    JPEGPrediction,    // 1.2.4.70  JPEG lossless prediction (14)
    JPEGLS,            // 1.2.4.80  JPEG-LS
    JPEGLSConstrained, // 1.2.4.81  JPEG-LS constrained error
    JPEG2K,            // 1.2.4.90  JPEG 2000 lossless
    JPEG2KLossless,    // 1.2.4.91  JPEG 2000 lossless/lossy
    MPEG2ML,           // 1.2.4.100 MPEG2 ML
    MPEG2HL,           // 1.2.4.101 MPEG2 HL
    MPEG2HP,           // 1.2.4.102 MPEG4 AVC/H.264 High Profile / Level 4.1
    MPEG2BD,           // 1.2.4.103 MPEG4 AVC/H.264 BD-compatible
    NumberOfCodecs
  };

  enum ErrorCode
  {
    NoError,
    MissingCodec,
    BadPixelFormat,
    MissingData,
    UnknownError
  };

  //! A struct to store basic image information for a codec
  struct ImageFormat
  {
    unsigned short Rows;
    unsigned short Columns;
    unsigned short BitsAllocated;
    unsigned short BitsStored;
    unsigned short PixelRepresentation;
    unsigned short SamplesPerPixel;
    unsigned short PlanarConfiguration;
    bool AllowLossyCompression;

    ImageFormat() : Rows(0), Columns(0), BitsAllocated(0), BitsStored(0),
                    PixelRepresentation(0), SamplesPerPixel(0),
                    PlanarConfiguration(0), AllowLossyCompression(false) {}

    ImageFormat(vtkDICOMMetaData *meta);
  };

  //! Construct an object for the default codec (little endian uncompressed).
  vtkDICOMImageCodec() : Key(0) {}

  //! Construct a codec object from the given code.
  /*!
   *  The code can be any of the enumerated code values.
   */
  vtkDICOMImageCodec(int k) : Key(static_cast<unsigned char>(k)) {}

  //! Get a codec for the specified transfer syntax UID.
  /*!
   *  This generates an 8-bit code that uniquely identifies a DICOM
   *  compression method, given the transfer syntax.
   */
  explicit vtkDICOMImageCodec(const std::string& syntax);

  //! Get the transfer syntax for this codec.
  std::string GetTransferSyntaxUID() const;
  /*!
   *  If the object is invalid, then an empty string is returned.
   */

  //! Get the numerical identifier for this codec.
  unsigned char GetKey() const { return this->Key; }

  //! Decode a compressed image into the given destination buffer.
  /*!
   *  The length of the source buffer must be provided.  The destination
   *  must be large enough to accept the entire decompressed frame.  On
   *  error, the error code is returned, and on success, zero is returned.
   */
  int Decode(const ImageFormat& image,
             const unsigned char *source, size_t sourceSize,
             unsigned char *dest, size_t destSize) const;

  //! Encode a compressed image, and return an allocated destination buffer.
  /*!
   *  The caller has the responsibility of calling "free" on the returned
   *  destination buffer.
   */
  int Encode(const ImageFormat& image,
             const unsigned char *source, size_t sourceSize,
             unsigned char **dest, size_t *destSize) const;

  bool operator==(vtkDICOMImageCodec b) const { return (this->Key == b.Key); }
  bool operator!=(vtkDICOMImageCodec b) const { return (this->Key != b.Key); }
  bool operator<=(vtkDICOMImageCodec a) const { return (this->Key <= a.Key); }
  bool operator>=(vtkDICOMImageCodec a) const { return (this->Key >= a.Key); }
  bool operator<(vtkDICOMImageCodec a) const { return (this->Key < a.Key); }
  bool operator>(vtkDICOMImageCodec a) const { return (this->Key > a.Key); }

private:
  unsigned char Key;
  static const char *UIDs[16];

  static int DecodeRLE(
    const ImageFormat& image,
    const unsigned char *source, size_t sourceSize,
    unsigned char *dest, size_t destSize);

  static int EncodeRLE(
    const ImageFormat& image,
    const unsigned char *source, size_t sourceSize,
    unsigned char **dest, size_t *destSize);

  //! Unpack one little-endian int.
  static unsigned int UnpackUnsignedInt(const void *source) {
    const unsigned char *cp = static_cast<const unsigned char *>(source);
    return cp[0] + (cp[1] << 8) + (cp[2] << 16) + (cp[3] << 24); }
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMImageCodec& a);

#endif /* __vtkDICOMImageCodec_h */
