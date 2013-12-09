/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMReader.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkIntArray.h"
#include "vtkTypeInt64Array.h"
#include "vtkByteSwap.h"
#include "vtkMatrix4x4.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkStringArray.h"
#include "vtkMath.h"
#include "vtkVariant.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"
#include "vtkTypeTraits.h"

#if defined(DICOM_USE_DCMTK)
#ifndef _WIN32
#define HAVE_CONFIG_H
#endif
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/dcmdata/dcrledrg.h"
#include "dcmtk/dcmjpeg/djdecode.h"
#include "dcmtk/dcmjpls/djdecode.h"
#ifndef _WIN32
#undef HAVE_CONFIG_H
#endif
#elif defined(DICOM_USE_GDCM)
#include "gdcmImageReader.h"
#endif

#include "vtksys/SystemTools.hxx"
#include "vtksys/ios/sstream"

#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

vtkStandardNewMacro(vtkDICOMReader);

//----------------------------------------------------------------------------
vtkDICOMReader::vtkDICOMReader()
{
  this->NeedsRescale = 0;
  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;
  this->Parser = 0;
  this->FileIndexArray = vtkIntArray::New();
  this->FrameIndexArray = vtkIntArray::New();
  this->StackIDs = vtkStringArray::New();
  this->FileOffsetArray = 0;
  this->MetaData = vtkDICOMMetaData::New();
  this->PatientMatrix = vtkMatrix4x4::New();
  this->MemoryRowOrder = vtkDICOMReader::BottomUp;
  this->NumberOfPackedComponents = 1;
  this->NumberOfPlanarComponents = 1;
  this->Sorting = 1;
  this->TimeAsVector = 0;
  this->DesiredTimeIndex = -1;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->DesiredStackID[0] = '\0';

  this->DataScalarType = VTK_SHORT;
  this->NumberOfScalarComponents = 1;
  this->FileLowerLeft = 0;
  this->FileDimensionality = 2;
#ifdef VTK_WORDS_BIGENDIAN
  this->SwapBytes = 1;
#else
  this->SwapBytes = 0;
#endif

#ifdef DICOM_USE_DCMTK
  DJDecoderRegistration::registerCodecs();
  DJLSDecoderRegistration::registerCodecs();
  DcmRLEDecoderRegistration::registerCodecs();
#endif
}

//----------------------------------------------------------------------------
vtkDICOMReader::~vtkDICOMReader()
{
#ifdef DICOM_USE_DCMTK
  DcmRLEDecoderRegistration::cleanup();
  DJLSDecoderRegistration::cleanup();
  DJDecoderRegistration::cleanup();
#endif

  if (this->Parser)
    {
    this->Parser->Delete();
    }
  if (this->FileOffsetArray)
    {
    this->FileOffsetArray->Delete();
    }
  if (this->FileIndexArray)
    {
    this->FileIndexArray->Delete();
    }
  if (this->FrameIndexArray)
    {
    this->FrameIndexArray->Delete();
    }
  if (this->StackIDs)
    {
    this->StackIDs->Delete();
    }
  if (this->MetaData)
    {
    this->MetaData->Delete();
    }
  if (this->PatientMatrix)
    {
    this->PatientMatrix->Delete();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "MetaData: ";
  if (this->MetaData)
    {
    os << this->MetaData << "\n";
    }
  else
    {
    os << "(none)\n";
    }

  os << indent << "DesiredStackID: "
     << (*this->DesiredStackID ? "(empty)" : this->DesiredStackID) << "\n";
  os << "StackIDs: " << this->StackIDs << "\n";

  os << indent << "FileIndexArray: " << this->FileIndexArray << "\n";
  os << indent << "FrameIndexArray: " << this->FrameIndexArray << "\n";

  os << indent << "Sorting: " << (this->Sorting ? "On\n" : "Off\n");
  os << indent << "TimeAsVector: "
     << (this->TimeAsVector ? "On\n" : "Off\n");
  os << indent << "TimeDimension: " << this->TimeDimension << "\n";
  os << indent << "TimeSpacing: " << this->TimeSpacing << "\n";
  os << indent << "DesiredTimeIndex: " << this->DesiredTimeIndex << "\n";

  os << indent << "RescaleSlope: " << this->RescaleSlope << "\n";
  os << indent << "RescaleIntercept: " << this->RescaleIntercept << "\n";

  os << indent << "PatientMatrix:";
  if (this->PatientMatrix)
    {
    double mat[16];
    vtkMatrix4x4::DeepCopy(mat, this->PatientMatrix);
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

  os << indent << "MemoryRowOrder: "
     << this->GetMemoryRowOrderAsString() << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMReader::SetDesiredStackID(const char *stackId)
{
  if (stackId == 0)
    {
    stackId = "";
    }

  // the maximum length of a stackId is 16
  if (strncmp(this->DesiredStackID, stackId, 16) != 0)
    {
    strncpy(this->DesiredStackID, stackId, 16);
    this->DesiredStackID[17] = '\0';
    this->Modified();
    }
}

//----------------------------------------------------------------------------
namespace {

// This silences error printing when CanReadFile is testing a file.
class vtkDICOMErrorSilencer : public vtkCommand
{
public:
  static vtkDICOMErrorSilencer *New() { return new vtkDICOMErrorSilencer; }
  vtkTypeMacro(vtkDICOMErrorSilencer,vtkCommand);
  virtual void Execute(
    vtkObject *caller, unsigned long eventId, void *callData);
protected:
  vtkDICOMErrorSilencer() {};
  vtkDICOMErrorSilencer(const vtkDICOMErrorSilencer& c) : vtkCommand(c) {}
  void operator=(const vtkDICOMErrorSilencer&) {}
};

void vtkDICOMErrorSilencer::Execute(vtkObject *, unsigned long, void *)
{
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMReader::SetMemoryRowOrder(int order)
{
  if (order >= 0 && order <= vtkDICOMReader::BottomUp)
    {
    if (order != this->MemoryRowOrder)
      {
      this->MemoryRowOrder = order;
      this->Modified();
      }
    }
}

//----------------------------------------------------------------------------
const char *vtkDICOMReader::GetMemoryRowOrderAsString()
{
  const char *text = "";
  switch (this->MemoryRowOrder)
    {
    case vtkDICOMReader::FileNative:
      text = "FileNative";
      break;
    case vtkDICOMReader::TopDown:
      text = "TopDown";
      break;
    case vtkDICOMReader::BottomUp:
      text = "BottomUp";
      break;
    }

  return text;
}

//----------------------------------------------------------------------------
int vtkDICOMReader::CanReadFile(const char *filename)
{
  vtkDebugMacro("Opening DICOM file " << filename);

  vtkDICOMErrorSilencer *command = vtkDICOMErrorSilencer::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  // add a dummy observer to silence errors
  unsigned long cid = parser->AddObserver(vtkCommand::ErrorEvent, command);
  parser->SetFileName(filename);
  parser->Update();
  parser->RemoveObserver(cid);
  command->Delete();

  // if an pixel data was found, the file is DICOM image
  return parser->GetPixelDataFound();
}

//----------------------------------------------------------------------------
namespace {

// a class and methods for sorting the files
struct vtkDICOMReaderSortInfo
{
  int FileNumber;
  int FrameNumber;
  int InstanceNumber;
  int PositionNumber;
  double ComputedLocation;
  double Time;

  vtkDICOMReaderSortInfo() :
    FileNumber(0), FrameNumber(0), InstanceNumber(0), PositionNumber(0),
    ComputedLocation(0.0), Time(0.0) {}

  vtkDICOMReaderSortInfo(int i, int j, int k, int s, double l, double t) :
    FileNumber(i), FrameNumber(j), InstanceNumber(k), PositionNumber(s),
    ComputedLocation(l), Time(t) {}

  vtkDICOMReaderSortInfo(int i, int k) :
    FileNumber(i), FrameNumber(0), InstanceNumber(k), PositionNumber(0),
    ComputedLocation(0), Time(0) {}

  // for sorting by by instance number
  static bool CompareInstance(
    const vtkDICOMReaderSortInfo &si1, const vtkDICOMReaderSortInfo &si2)
  {
    return (si1.InstanceNumber < si2.InstanceNumber);
  }

  // for sorting by position number
  static bool ComparePosition(
    const vtkDICOMReaderSortInfo &si1, const vtkDICOMReaderSortInfo &si2)
  {
    return (si1.PositionNumber < si2.PositionNumber);
  }

  // for sorting by spatial location
  static bool CompareLocation(
    const vtkDICOMReaderSortInfo &si1, const vtkDICOMReaderSortInfo &si2)
  {
    // locations must differ by at least the tolerance
    const double locationTolerance = 1e-3;
    return (si1.ComputedLocation + locationTolerance < si2.ComputedLocation);
  }
};

// get an attribute value for a particular frame
const vtkDICOMValue& vtkDICOMReaderGetFrameAttributeValue(
  const vtkDICOMSequence& frameSeq, const vtkDICOMSequence& sharedSeq,
  unsigned int i, vtkDICOMTag stag, vtkDICOMTag vtag)
{
  const vtkDICOMValue& v =
    frameSeq.GetAttributeValue(i, vtkDICOMTagPath(stag, 0, vtag));
  if (v.IsValid())
    {
    return v;
    }
  return sharedSeq.GetAttributeValue(0, vtkDICOMTagPath(stag, 0, vtag));
}

// compute spatial location from position and orientation
double vtkDICOMReaderComputeLocation(
  const vtkDICOMValue& pv, const vtkDICOMValue& ov,
  double checkOrientation[10], bool *checkPtr)
{
  double location = 0.0;

  if (pv.GetNumberOfValues() != 3 || ov.GetNumberOfValues() != 6)
    {
    *checkPtr = false;
    }
  else
    {
    double orientation[6], normal[3], position[3];
    pv.GetValues(position, position+3);
    ov.GetValues(orientation, orientation+6);

    // compute the cross product to get the slice normal
    vtkMath::Cross(&orientation[0], &orientation[3], normal);
    vtkMath::Normalize(normal);
    location = vtkMath::Dot(normal, position);

    if (checkOrientation[9] == 0)
      {
      // save the orientation and position for later checks
      for (int i = 0; i < 3; i++)
        {
        checkOrientation[i] = orientation[i];
        checkOrientation[3+i] = orientation[3+i];
        checkOrientation[6+i] = position[i];
        }
      // indicate that checkOrientation has been set
      checkOrientation[9] = 1.0;
      }
    else
      {
      const double directionTolerance = 1e-4;
      const double positionTolerance = 1e-3;
      for (int i = 0; i < 2; i++)
        {
        // make sure the orientation vectors stay the same
        double *vec = &orientation[3*i];
        double *checkVec = &checkOrientation[3*i];
        double a = vtkMath::Dot(vec, checkVec);
        double b = vtkMath::Dot(vec, vec);
        double c = vtkMath::Dot(checkVec, checkVec);
        // compute the sine of the angle between the normals
        // (actually compute the square of the sine, it's easier)
        double d = 1.0;
        if (b > 0 && c > 0)
          {
          d = 1.0 - (a*a)/(b*c);
          }
        // the tolerance is in radians (small angle approximation)
        if (d > directionTolerance*directionTolerance)
          {
          // not all slices have the same orientation
          *checkPtr = false;
          }
        }
      // make sure the positions line up
      double *checkPosition = &checkOrientation[6];
      double v[3];
      v[0] = position[0] - checkPosition[0];
      v[1] = position[1] - checkPosition[1];
      v[2] = position[2] - checkPosition[2];
      double t = vtkMath::Dot(v, normal);
      v[0] -= t*normal[0];
      v[1] -= t*normal[1];
      v[2] -= t*normal[2];
      double d = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
      // the position tolerance is in millimetres
      if (d > (positionTolerance*positionTolerance +
               t*t*directionTolerance*directionTolerance))
        {
        // positions don't line up along the normal
        *checkPtr = false;
        }
      }
    if (*checkPtr == false)
      {
      // re-set the check orientation to the current stack
      for (int i = 0; i < 3; i++)
        {
        checkOrientation[i] = orientation[i];
        checkOrientation[3+i] = orientation[3+i];
        checkOrientation[6+i] = position[i];
        }
      }
    }

  return location;
}

// a simple struct to provide info for each frame to be read
struct vtkDICOMReaderFrameInfo
{
  int FrameIndex;
  int SliceIndex;
  int ComponentIndex;

  vtkDICOMReaderFrameInfo(int i, int j, int k) :
    FrameIndex(i), SliceIndex(j), ComponentIndex(k) {}
};

// a simple struct to provide info for each file to be read
struct vtkDICOMReaderFileInfo
{
  int FileIndex;
  int FramesInFile; // total frames in file
  std::vector<vtkDICOMReaderFrameInfo> Frames; // the frames to read

  vtkDICOMReaderFileInfo(int i, int n) : FileIndex(i), FramesInFile(n) {}
};

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMReader::SortFiles(vtkIntArray *files, vtkIntArray *frames)
{
  // This function assumes that the meta data has already been read,
  // and that all files have the same StudyUID and SeriesUID.
  //
  // It tries two strategies to sort the DICOM files.
  //
  // First, it simply sorts the files by instance number.
  //
  // Next, if the Image Plane Module is present (DICOM Part 3 C.7.6.2)
  // then the images are sorted by ImagePositionPatient, so that the
  // position increases along the direction given by cross product of
  // the ImageOrientationPatient vectors.

  // For cardiac images, time sorting can be done with this tag:
  // - TriggerTime (0018,1060)
  // - CardiacNumberOfImages (0018,1090)

  // For relaxometry, time sorting can be done with this tag:
  // - EchoTime (0018,0091)

  // For functional images, the following tags can be used:
  // - NumberOfTemporalPositions (0020,0105)
  // - TemporalPositionIdentifier (0020,0100)
  // - TemporalResolution (0020,0110)

  // If the image has a StackID, then dimensional sorting
  // might be possible with these tags:
  // - TemporalPositionIndex (0020,9128) if present
  // - StackID (0020,9056)
  // - InStackPositionNumber (0020,9057)

  // If the multi-frame module is present, each file might have more than
  // one slice.  See DICOM Part 3 Appendix C 7.6.6 for details.
  // To identify the multi-frame module, look for these attributes:
  // - NumberOfFrames (0028,0008)
  // - FrameIncrementPointer (0028,0009)
  // Usually frames are used for cine, but in nuclear medicine (NM) they
  // are used to describe multi-dimensional files (Part 3 Appendix C 8.4.8):
  // - NumberOfSlices (0054,0081)
  // - NumberOfTimeSlots (0054,0071)
  // - NumberOfRRIntervals (0054,0061)
  // - NumberOfRotations (0054,0051)
  // - NumberOfPhases (0054,0031)
  // - NumberOfDetectors (0054,0021)
  // - NumberOfEnergyWindows (0054,0011)

  vtkDICOMMetaData *meta = this->MetaData;
  int numFiles = meta->GetNumberOfInstances();
  std::vector<vtkDICOMReaderSortInfo> info;

  // sort by instance first
  for (int i = 0; i < numFiles; i++)
    {
    int inst = meta->GetAttributeValue(i, DC::InstanceNumber).AsInt();
    info.push_back(vtkDICOMReaderSortInfo(i, inst));
    }
  std::stable_sort(info.begin(), info.end(),
    vtkDICOMReaderSortInfo::CompareInstance);
  std::vector<int> fileOrder(info.size());
  for (int i = 0; i < numFiles; i++)
    {
    fileOrder[i] = info[i].FileNumber;
    }
  info.clear();

  // important position-related variables
  std::vector<size_t> volumeBreaks;
  double checkOrientation[10] = {};
  bool canSortByLocation = true;
  double spacingBetweenSlices =
    meta->GetAttributeValue(DC::SpacingBetweenSlices).AsDouble();
  double spacingSign = 1.0;
  if (spacingBetweenSlices == 0)
    {
    spacingBetweenSlices = 1.0;
    }
  else if (spacingBetweenSlices < 0)
    {
    spacingBetweenSlices = -spacingBetweenSlices;
    spacingSign = -1.0;
    }

  // important time-related variables
  int temporalSpacing = 1.0;

  if (meta->HasAttribute(DC::SharedFunctionalGroupsSequence))
    {
    // a special stackInfo for the desired stack
    std::vector<vtkDICOMReaderSortInfo> stackInfo;
    vtkDICOMValue firstStackId;
    vtkDICOMValue desiredStackId =
      vtkDICOMValue(vtkDICOMVR::SH, this->DesiredStackID);
    double stackCheckNormal[10] = {};
    bool canSortStackByIPP = true;

    // files have enhanced frame information
    for (int ii = 0; ii < numFiles; ii++)
      {
      int i = fileOrder[ii];
      int inst = meta->GetAttributeValue(i, DC::InstanceNumber).AsInt();
      int numberOfFrames =
        meta->GetAttributeValue(i, DC::NumberOfFrames).AsInt();

      // from the MultiFrameFunctionalGroups module
      vtkDICOMSequence frameSeq =
        meta->GetAttributeValue(i, DC::PerFrameFunctionalGroupsSequence);
      vtkDICOMSequence sharedSeq =
        meta->GetAttributeValue(i, DC::SharedFunctionalGroupsSequence);

      if (ii == 0 && numberOfFrames > 0)
        {
        firstStackId = vtkDICOMReaderGetFrameAttributeValue(
          frameSeq, sharedSeq, 0, DC::FrameContentSequence,
          DC::StackID);
        }

      // attributes for getting time information
      vtkDICOMTag timeSequence;
      vtkDICOMTag timeTag;

      if (numberOfFrames > 0)
        {
        // time information can come from these attributes
        if (vtkDICOMReaderGetFrameAttributeValue(
              frameSeq, sharedSeq, 0, DC::CardiacSynchronizationSequence,
              DC::NominalCardiacTriggerDelayTime).IsValid())
          {
          timeSequence = DC::CardiacSynchronizationSequence;
          timeTag = DC::NominalCardiacTriggerDelayTime;
          }
        else if (vtkDICOMReaderGetFrameAttributeValue(
                   frameSeq, sharedSeq, 0, DC::TemporalPositionSequence,
                   DC::TemporalPositionTimeOffset).IsValid())
          {
          timeSequence = DC::TemporalPositionSequence;
          timeTag = DC::TemporalPositionTimeOffset;
          temporalSpacing = 1000.0; // convert seconds to milliseconds
          }
        else if (vtkDICOMReaderGetFrameAttributeValue(
                  frameSeq, sharedSeq, 0, DC::FrameContentSequence,
                  DC::TemporalPositionIndex).IsValid())
          {
          timeSequence = DC::FrameContentSequence;
          timeTag = DC::TemporalPositionIndex;
          }
        else if (vtkDICOMReaderGetFrameAttributeValue(
                  frameSeq, sharedSeq, 0, DC::MREchoSequence,
                  DC::EffectiveEchoTime).IsValid())
          {
          timeSequence = DC::MREchoSequence;
          timeTag = DC::EffectiveEchoTime;
          }
        }

      // position counter
      int position = 0;
      double lastTime = 0.0;

      for (int k = 0; k < numberOfFrames; k++)
        {
        // time: use chosen time tag, if present
        double t = 0.0;
        if (timeTag.GetGroup() != 0)
          {
          t = vtkDICOMReaderGetFrameAttributeValue(
            frameSeq, sharedSeq, k, timeSequence, timeTag).AsDouble();
          }

        // adjust position only if time did not change
        if (fabs(t - lastTime) < 1e-3 || k == 0)
          {
          position = k;
          lastTime = t;
          }

        // get the StackID
        vtkDICOMValue stackId = vtkDICOMReaderGetFrameAttributeValue(
          frameSeq, sharedSeq, k, DC::FrameContentSequence,
          DC::StackID);

        if (stackId.IsValid())
          {
          // append new StackIDs to this->StackIDs
          vtkIdType stacksFound = this->StackIDs->GetNumberOfValues();
          std::string stackName = stackId.AsString();
          vtkIdType si;
          for (si = 0; si < stacksFound; si++)
            {
            if (stackName == this->StackIDs->GetValue(si)) { break; }
            }
          if (si == stacksFound)
            {
            this->StackIDs->InsertNextValue(stackName);
            }

          // position: look for InStackPositionNumber
          position = vtkDICOMReaderGetFrameAttributeValue(
            frameSeq, sharedSeq, k, DC::FrameContentSequence,
            DC::InStackPositionNumber).AsInt();
          }

        // check for valid Image Plane Module information
        vtkDICOMValue pv = vtkDICOMReaderGetFrameAttributeValue(
          frameSeq, sharedSeq, k, DC::PlanePositionSequence,
          DC::ImagePositionPatient);
        vtkDICOMValue ov = vtkDICOMReaderGetFrameAttributeValue(
          frameSeq, sharedSeq, k, DC::PlaneOrientationSequence,
          DC::ImageOrientationPatient);

        // check if the StackId is the one the user specified
        if (stackId == desiredStackId)
          {
          // compute location from orientation and IPP
          double location = vtkDICOMReaderComputeLocation(
            pv, ov, stackCheckNormal, &canSortStackByIPP);

          location /= spacingBetweenSlices;

          stackInfo.push_back(
            vtkDICOMReaderSortInfo(i, k, inst, position, location, t));
          }
        else if (stackId == firstStackId)
          {
          // compute location from orientation and IPP
          double location = vtkDICOMReaderComputeLocation(
            pv, ov, checkOrientation, &canSortByLocation);
          location /= spacingBetweenSlices;

          // force output of one single volume
          if ((ii > 0 || k > 0) && !firstStackId.IsValid() &&
              pv.IsValid() && !canSortByLocation)
            {
            canSortByLocation = true;
            volumeBreaks.push_back(info.size());
            }

          info.push_back(
            vtkDICOMReaderSortInfo(i, k, inst, position, location, t));
          }
        }
      }

    // if frames with the desired stack ID were found, use them
    if (stackInfo.size() > 0)
      {
      canSortByLocation = canSortStackByIPP;
      info = stackInfo;
      }
    }
  else
    {
    // ways to get time information
    vtkDICOMTag timeTag;
    if (meta->GetAttributeValue(DC::CardiacNumberOfImages).AsInt() > 1)
      {
      timeTag = DC::TriggerTime;
      }
    else if (meta->GetAttributeValue(
              DC::NumberOfTemporalPositions).AsInt() > 1)
      {
      timeTag = DC::TemporalPositionIdentifier;
      temporalSpacing =
        meta->GetAttributeValue(DC::TemporalResolution).AsDouble();
      }
    else if (meta->HasAttribute(DC::TemporalPositionIndex))
      {
      timeTag = DC::TemporalPositionIndex;
      }
    else if (meta->HasAttribute(DC::EchoTime))
      {
      timeTag = DC::EchoTime;
      }

    // position counter
    int position = 0;
    double lastTime = 0.0;

    for (int ii = 0; ii < numFiles; ii++)
      {
      int i = fileOrder[ii];

      // get the instance number
      int inst = meta->GetAttributeValue(i, DC::InstanceNumber).AsInt();

      // check for valid Image Plane Module information
      // (for NM this information is per-detector and is put in
      // the Detector Information Sequence)
      double location = 0;
      vtkDICOMValue pv = meta->GetAttributeValue(
        i, DC::ImagePositionPatient);
      vtkDICOMValue ov = meta->GetAttributeValue(
        i, DC::ImageOrientationPatient);

      location = vtkDICOMReaderComputeLocation(
        pv, ov, checkOrientation, &canSortByLocation);
      location /= spacingBetweenSlices;

      // force output of one single rectilinear volume
      if (ii > 0 && !canSortByLocation && pv.IsValid())
        {
        canSortByLocation = true;
        volumeBreaks.push_back(info.size());
        }

      int numberOfFrames =
        meta->GetAttributeValue(i, DC::NumberOfFrames).AsInt();
      if (numberOfFrames <= 1)
        {
        double t = 0.0;
        if (timeTag.GetGroup() != 0)
          {
          t = meta->GetAttributeValue(i, timeTag).AsDouble();
          }

        // adjust position only if time did not change
        if (fabs(t - lastTime) < 1e-3 || ii == 0)
          {
          position = inst;
          lastTime = t;
          }

        info.push_back(
          vtkDICOMReaderSortInfo(i, 0, inst, position, location, t));
        }
      else
        {
        // multi-frame image
        double frameTimeSpacing = 0;
        vtkDICOMValue timeVector;
        vtkDICOMValue timeSlotVector;
        vtkDICOMValue sliceVector;
        vtkDICOMValue locationVector;
        vtkDICOMValue fip =
          meta->GetAttributeValue(i, DC::FrameIncrementPointer);
        unsigned int n = fip.GetNumberOfValues();
        for (unsigned int j = 0; j < n; j++)
          {
          vtkDICOMTag tag = fip.GetTag(j);
          if (tag == DC::FrameTime)
            { // for CINE
            frameTimeSpacing = meta->GetAttributeValue(i, tag).AsDouble();
            }
          else if (tag == DC::FrameTimeVector)
            { // for CINE
            timeVector = meta->GetAttributeValue(i, tag);
            }
          else if (tag == DC::SliceLocationVector)
            { // generic
            locationVector = meta->GetAttributeValue(i, tag);
            canSortByLocation = true;
            }
          else if (tag == DC::TimeSlotVector)
            { // for NM
            timeSlotVector = meta->GetAttributeValue(i, tag);
            }
          else if (tag == DC::SliceVector)
            { // for NM
            sliceVector = meta->GetAttributeValue(i, tag);
            }
          // in dynamic NM, the total number of time frames is the
          // sum of the number of frames in all collected phases,
          // we do not support dynamic NM yet
          }

        if (timeSlotVector.IsValid() || sliceVector.IsValid())
          {
          // tomographic NM
          for (int k = 0; k < numberOfFrames; k++)
            {
            double t = 0.0;
            double frameloc = location;
            if (k < static_cast<int>(timeSlotVector.GetNumberOfValues()))
              {
              t = (timeSlotVector.GetDouble(k) - 1.0)*frameTimeSpacing;
              }
            if (k < static_cast<int>(sliceVector.GetNumberOfValues()))
              {
              position = sliceVector.GetInt(k) - 1;
              frameloc += position*spacingSign;
              }
            info.push_back(
              vtkDICOMReaderSortInfo(i, k, inst, position, frameloc, t));
            }
          }
        else
          {
          // CINE
          double t = 0.0;
          for (int k = 0; k < numberOfFrames; k++)
            {
            if (k > 0)
              {
              if (k < static_cast<int>(timeVector.GetNumberOfValues()))
                {
                frameTimeSpacing = timeVector.GetDouble(k);
                }
              t += frameTimeSpacing;
              }
            if (k < static_cast<int>(locationVector.GetNumberOfValues()))
              {
              location = locationVector.GetDouble(k);
              location /= spacingBetweenSlices;
              }
            info.push_back(
              vtkDICOMReaderSortInfo(i, k, inst, inst, location, t));
            }
          }
        }
      }
    }

  // orientation changes suggest that multiple volumes are present
  if (volumeBreaks.size() > 0)
    {
    // count the number of unique positions
    size_t pcount = 0;
    for (size_t j = 0; j < info.size(); j++)
      {
      int p = info[j].PositionNumber;
      size_t k;
      for (k = 0; k < j; k++)
        {
        if (info[k].PositionNumber == p) { break; }
        }
      pcount += (k == j);
      }

    if (volumeBreaks.size() + 1 > pcount/2)
      {
      // too many unique volumes would be created, assume
      // that the acquisition was not rectilinear.
      canSortByLocation = false;
      }
    else
      {
      // load just one of the rectilinear stacks that are present
      size_t stt = strtoul(this->DesiredStackID, 0, 10);
      if (stt > volumeBreaks.size())
        {
        stt = 0;
        }
      volumeBreaks.push_back(info.size());
      info.erase(info.begin() + volumeBreaks[stt], info.end());
      if (stt > 0)
        {
        info.erase(info.begin(), info.begin() + volumeBreaks[stt-1]);
        }
      for (size_t k = 0; k < volumeBreaks.size(); k++)
        {
        vtkVariant var(k);
        this->StackIDs->InsertNextValue(var.ToString());
        }
      }
    }

  // sort by position, count the number of slices per location
  int numSlices = static_cast<int>(info.size());
  int slicesPerLocation = 0;
  if (numSlices > 1)
    {
    if (canSortByLocation)
      {
      std::stable_sort(info.begin(), info.end(),
        vtkDICOMReaderSortInfo::CompareLocation);
      }
    else
      {
      std::stable_sort(info.begin(), info.end(),
        vtkDICOMReaderSortInfo::ComparePosition);
      }

    // look for slices at the same location
    std::vector<vtkDICOMReaderSortInfo>::iterator iter = info.begin();
    int slicesAtThisLocation = 0;
    while (iter != info.end())
      {
      std::vector<vtkDICOMReaderSortInfo>::iterator nextIter = iter + 1;
      slicesAtThisLocation++;
      bool positionIncreased = false;
      if (nextIter != info.end())
        {
        // use the tolerance built into CompareLocation
        if (canSortByLocation)
          {
          positionIncreased =
            vtkDICOMReaderSortInfo::CompareLocation(*iter, *nextIter);
          }
        else
          {
          positionIncreased =
            vtkDICOMReaderSortInfo::ComparePosition(*iter, *nextIter);
          }
        }
      if (nextIter == info.end() || positionIncreased)
        {
        if (slicesPerLocation == 0)
          {
          slicesPerLocation = slicesAtThisLocation;
          }
        else if (slicesPerLocation != slicesAtThisLocation)
          {
          slicesPerLocation = -1;
          }
        slicesAtThisLocation = 0;
        }
      iter = nextIter;
      }
    }
  if (slicesPerLocation <= 0)
    {
    slicesPerLocation = static_cast<int>(info.size());
    }

  // count number of unique time points
  int temporalPositions = 0;
  double tMin = VTK_DOUBLE_MAX;
  double tMax = VTK_DOUBLE_MIN;
  for (int i = 0; i < slicesPerLocation; i++)
    {
    double d = info[i].Time;
    tMin = (d > tMin ? tMin : d);
    tMax = (d < tMax ? tMax : d);
    int u = 1;
    for (int j = 0; j < i; j++)
      {
      u &= !(fabs(info[j].Time - d) < 1e-3);
      }
    temporalPositions += u;
    }
  // compute temporalSpacing from the apparent time spacing
  if (temporalPositions > 1)
    {
    temporalSpacing *= (tMax - tMin)/(temporalPositions - 1);
    }

  // compute the number of slices in the output image
  int spatialLocations = numSlices/slicesPerLocation;
  int locations = spatialLocations;
  if (temporalPositions > 0 &&
      this->TimeAsVector == 0 &&
      this->DesiredTimeIndex < 0)
    {
    locations *= temporalPositions;
    }

  // recompute slice spacing from position info
  if (canSortByLocation)
    {
    double locDiff = 0;
    if (locations > 1)
      {
      double firstLocation = info.front().ComputedLocation;
      double finalLocation = info.back().ComputedLocation;
      locDiff = (finalLocation - firstLocation)/(locations - 1);
      }
    if (locDiff > 0)
      {
      spacingBetweenSlices *= locDiff;
      }
    }

  // write out the sorted indices
  bool flipOrder = (this->MemoryRowOrder == vtkDICOMReader::BottomUp);
  int filesPerOutputSlice = numSlices/locations;
  int locationsPerSpatialLocation = locations/spatialLocations;
  int numberOfComponents = filesPerOutputSlice;
  int desiredTimeIndex = this->DesiredTimeIndex;
  if (desiredTimeIndex < 0)
    {
    desiredTimeIndex = 0;
    }
  else
    {
    desiredTimeIndex %= temporalPositions;
    numberOfComponents /= temporalPositions;
    }

  files->SetNumberOfComponents(numberOfComponents);
  files->SetNumberOfTuples(locations);
  frames->SetNumberOfComponents(numberOfComponents);
  frames->SetNumberOfTuples(locations);

  for (int loc = 0; loc < locations; loc++)
    {
    int l = loc/locationsPerSpatialLocation;
    int j = loc - l*locationsPerSpatialLocation;
    if (flipOrder)
      {
      l = spatialLocations - l - 1;
      }
    for (int k = 0; k < numberOfComponents; k++)
      {
      int i = ((l*locationsPerSpatialLocation + j)*filesPerOutputSlice +
               desiredTimeIndex*numberOfComponents + k);
      files->SetComponent(loc, k, info[i].FileNumber);
      frames->SetComponent(loc, k, info[i].FrameNumber);
      }
    }

  // save the slice spacing and time information
  this->DataSpacing[2] = spacingBetweenSlices;
  this->TimeDimension = temporalPositions;
  this->TimeSpacing = temporalSpacing;
}

//----------------------------------------------------------------------------
void vtkDICOMReader::NoSortFiles(vtkIntArray *files, vtkIntArray *frames)
{
  vtkDICOMMetaData *meta = this->MetaData;
  int numFiles = meta->GetNumberOfInstances();

  files->Initialize();
  frames->Initialize();
  files->SetNumberOfComponents(1);
  frames->SetNumberOfComponents(1);

  for (int i = 0; i < numFiles; i++)
    {
    int numFrames = meta->GetAttributeValue(i, DC::NumberOfFrames).AsInt();
    numFrames = (numFrames > 0 ? numFrames : 1);

    for (int j = 0; j < numFrames; j++)
      {
      files->InsertNextValue(i);
      frames->InsertNextValue(j);
      }
    }
}

//----------------------------------------------------------------------------
int vtkDICOMReader::RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  // Clear the error indicator.
  this->SetErrorCode(vtkErrorCode::NoError);

  // How many files are to be loaded?
  if (this->FileNames)
    {
    vtkIdType numFileNames = this->FileNames->GetNumberOfValues();
    this->DataExtent[4] = 0;
    this->DataExtent[5] = static_cast<int>(numFileNames - 1);
    }
  else if (this->FileName)
    {
    this->DataExtent[4] = 0;
    this->DataExtent[5] = 0;
    }
  int numFiles = this->DataExtent[5] - this->DataExtent[4] + 1;

  if (numFiles <= 0)
    {
    if (this->FileNames)
      {
      vtkErrorMacro("No filenames were provided for reader.");
      }
    else
      {
      vtkErrorMacro("Bad DataExtent " << this->DataExtent[4]
                    << "," << this->DataExtent[5] << ".");
      }
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return 0;
    }

  // Reset the time information
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;

  // Clear the meta data, prepare the parser.
  this->MetaData->Clear();
  this->MetaData->SetNumberOfInstances(numFiles);

  if (this->Parser)
    {
    this->Parser->Delete();
    this->FileOffsetArray->Delete();
    }

  // Parser reads just the meta data, not the pixel data.
  this->Parser = vtkDICOMParser::New();
  this->Parser->SetMetaData(this->MetaData);
  this->Parser->AddObserver(
    vtkCommand::ErrorEvent, this, &vtkDICOMReader::RelayError);

  // First component is offset to pixel data, 2nd component is file size.
  this->FileOffsetArray = vtkTypeInt64Array::New();
  this->FileOffsetArray->SetNumberOfComponents(2);
  this->FileOffsetArray->SetNumberOfTuples(numFiles);

  for (int idx = 0; idx < numFiles; idx++)
    {
    this->ComputeInternalFileName(this->DataExtent[4] + idx);
    this->Parser->SetFileName(this->InternalFileName);
    this->Parser->SetIndex(idx);
    this->Parser->Update();

    if (this->Parser->GetErrorCode())
      {
      return 0;
      }

    // save the offset to the pixel data
    vtkTypeInt64 offset[2];
    offset[0] = this->Parser->GetFileOffset();
    offset[1] = this->Parser->GetFileSize();
    this->FileOffsetArray->SetTupleValue(idx, offset);
    }

  // Files are read in the order provided, but they might have
  // to be re-sorted to create a proper volume.  The FileIndexArray
  // holds the sorted order of the files.
  this->StackIDs->Initialize();
  if (this->Sorting)
    {
    this->SortFiles(this->FileIndexArray, this->FrameIndexArray);
    }
  else
    {
    this->NoSortFiles(this->FileIndexArray, this->FrameIndexArray);
    }

  // Get the file and frame for the first slice
  int fileIndex = this->FileIndexArray->GetComponent(0, 0);
  int frameIndex = this->FileIndexArray->GetComponent(0, 0);

  // image dimensions
  int columns = this->MetaData->GetAttributeValue(DC::Columns).AsInt();
  int rows = this->MetaData->GetAttributeValue(DC::Rows).AsInt();
  int slices = static_cast<int>(this->FileIndexArray->GetNumberOfTuples());

  int extent[6];
  extent[0] = 0;
  extent[1] = columns - 1;
  extent[2] = 0;
  extent[3] = rows - 1;
  extent[4] = 0;
  extent[5] = slices - 1;

  // set the x and y dimensions of the DataExtent
  this->DataExtent[0] = extent[0];
  this->DataExtent[1] = extent[1];
  this->DataExtent[2] = extent[2];
  this->DataExtent[3] = extent[3];

  // DICOM images are usually stored one-slice-per-file,
  // with the exception of nuclear medicine and ultrasound
  // (the DataExtent gives the number of files)
  this->FileDimensionality = 2;
  if (slices > this->DataExtent[5] - this->DataExtent[4] + 1)
    {
    this->FileDimensionality = 3;
    }

  // DICOM uses a upper-left origin
  this->FileLowerLeft = 0;

  // DataSpacing[2] was set in SortFiles, but pixel spacing is set here.
  this->DataSpacing[0] = 1.0;
  this->DataSpacing[1] = 1.0;

  if (this->MetaData->HasAttribute(DC::PixelAspectRatio))
    {
    double ratio = 1.0;
    vtkDICOMValue v = this->MetaData->GetAttributeValue(DC::PixelAspectRatio);
    if (v.GetNumberOfValues() == 2)
      {
      // use double, even though data is stored as integer strings
      double ya = v.GetDouble(0);
      double xa = v.GetDouble(1);
      if (xa > 0)
        {
        ratio = ya/xa;
        }
      }
    else
      {
      // ratio should be expressed as two values,
      // so this is only to support incorrect files
      ratio = v.AsDouble();
      }
    if (ratio > 0)
      {
      this->DataSpacing[0] = this->DataSpacing[1]/ratio;
      }
    }

  if (this->MetaData->HasAttribute(DC::PixelSpacing))
    {
    vtkDICOMValue v = this->MetaData->GetAttributeValue(DC::PixelSpacing);
    if (v.GetNumberOfValues() == 2)
      {
      v.GetValues(this->DataSpacing, this->DataSpacing + 2);
      }
    }

  if (this->MetaData->HasAttribute(DC::SharedFunctionalGroupsSequence))
    {
    vtkDICOMValue v = this->MetaData->GetAttributeValue(fileIndex,
      vtkDICOMTagPath(DC::SharedFunctionalGroupsSequence, 0,
                      DC::PixelMeasuresSequence, 0,
                      DC::PixelSpacing));
    if (!v.IsValid())
      {
      v = this->MetaData->GetAttributeValue(fileIndex,
        vtkDICOMTagPath(DC::PerFrameFunctionalGroupsSequence, frameIndex,
                        DC::PixelMeasuresSequence, 0,
                        DC::PixelSpacing));
      }
    if (v.GetNumberOfValues() == 2)
      {
      v.GetValues(this->DataSpacing, this->DataSpacing + 2);
      }
    }

  // offset is part of the transform, so set origin to zero
  this->DataOrigin[0] = 0.0;
  this->DataOrigin[1] = 0.0;
  this->DataOrigin[2] = 0.0;

  // get information related to the data type
  int bitsAllocated =
    this->MetaData->GetAttributeValue(DC::BitsAllocated).AsInt();
  int pixelRepresentation =
    this->MetaData->GetAttributeValue(DC::PixelRepresentation).AsInt();
  int numComponents =
    this->MetaData->GetAttributeValue(DC::SamplesPerPixel).AsInt();
  int planarConfiguration =
    this->MetaData->GetAttributeValue(DC::PlanarConfiguration).AsInt();

  // datatype
  int scalarType = 0;

  if (bitsAllocated == 8 || bitsAllocated == 1)
    {
    scalarType = (pixelRepresentation ? VTK_SIGNED_CHAR : VTK_UNSIGNED_CHAR);
    }
  else if (bitsAllocated == 16 || bitsAllocated == 12)
    {
    scalarType = (pixelRepresentation ? VTK_SHORT : VTK_UNSIGNED_SHORT);
    }
  else if (bitsAllocated == 32)
    {
    scalarType = (pixelRepresentation ? VTK_INT : VTK_UNSIGNED_INT);
    }
  else
    {
    vtkErrorMacro("Unrecognized DICOM BitsAllocated value: " << bitsAllocated);
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return 0;
    }

  // number of components
  if (numComponents <= 0)
    {
    numComponents = 1;
    }

  this->DataScalarType = scalarType;
  this->NumberOfPackedComponents =
    (planarConfiguration ? 1 : numComponents);
  this->NumberOfPlanarComponents =
    (planarConfiguration ? numComponents : 1);
  this->NumberOfScalarComponents =
    (numComponents * this->FileIndexArray->GetNumberOfComponents());

  // photometric interpretation
  // "MONOCHROME1" "MONOCHROME2"
  // "PALETTE_COLOR" "RGB" (convert palette color to RGB)
  // "HSV" "ARGB" "CMYK" (all three are retired)
  // "YBR_FULL" "YBR_FULL_422" (use CCIR 601-2 to convert to RGB)
  // "YBR_PARTIAL_422" "YBR_PARTIAL_420" (use CCIR 601-2 to convert to RGB)
  // "YBR_ICT" "YBR_RCT" (use ISO 10918-1 to convert to RGB)
  // See DICOM Ch. 3 Appendix C 7.6.3.1.2 for equations

  // endianness
  std::string transferSyntax =
    this->MetaData->GetAttributeValue(DC::TransferSyntaxUID).AsString();

  bool bigEndian = (transferSyntax == "1.2.840.10008.1.2.2" ||
                    transferSyntax == "1.2.840.113619.5.2");

#ifdef VTK_WORDS_BIGENDIAN
  this->SwapBytes = !bigEndian;
#else
  this->SwapBytes = bigEndian;
#endif

  // for CT and PET the rescale information might vary from file to file,
  // in which case the data will have to be rescaled while being read
  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;
  this->NeedsRescale = false;

  if (this->MetaData->HasAttribute(DC::RescaleSlope))
    {
    vtkDICOMMetaData *meta = this->MetaData;
    int n = meta->GetNumberOfInstances();
    double mMax = meta->GetAttributeValue(0, DC::RescaleSlope).AsDouble();
    double bMax = meta->GetAttributeValue(0, DC::RescaleIntercept).AsDouble();
    bool mismatch = false;

    for (int i = 1; i < n; i++)
      {
      double m = meta->GetAttributeValue(i, DC::RescaleSlope).AsDouble();
      double b = meta->GetAttributeValue(i, DC::RescaleIntercept).AsDouble();
      if (m != mMax || b != bMax)
        {
        mismatch = true;
        }
      if (m > mMax)
        {
        mMax = m;
        }
      if (b > bMax)
        {
        bMax = b;
        }
      }
    this->NeedsRescale = mismatch;
    this->RescaleSlope = mMax;
    this->RescaleIntercept = bMax;
    }

  if (this->MetaData->HasAttribute(DC::SharedFunctionalGroupsSequence))
    {
    vtkDICOMValue mv = this->MetaData->GetAttributeValue(fileIndex,
      vtkDICOMTagPath(DC::SharedFunctionalGroupsSequence, 0,
                      DC::PixelValueTransformationSequence, 0,
                      DC::RescaleSlope));
    vtkDICOMValue bv = this->MetaData->GetAttributeValue(fileIndex,
      vtkDICOMTagPath(DC::SharedFunctionalGroupsSequence, 0,
                      DC::PixelValueTransformationSequence, 0,
                      DC::RescaleIntercept));
   if (mv.IsValid() && bv.IsValid())
     {
     this->NeedsRescale = false;
     this->RescaleSlope = mv.AsDouble();
     this->RescaleIntercept = bv.AsDouble();
     }
   }

  // === Image Orientation in DICOM files ===
  //
  // The vtkImageData class does not provide a way of storing image
  // orientation.  So when we read a DICOM file, we should also provide
  // the user with a 4x4 matrix that can transform VTK's data coordinates
  // into DICOM's patient coordinates, as defined in the DICOM standard
  // Part 3 Appendix C 7.6.2 "Image Plane Module".
  vtkDICOMValue pv = this->MetaData->GetAttributeValue(
    fileIndex, frameIndex, DC::ImagePositionPatient);
  vtkDICOMValue ov = this->MetaData->GetAttributeValue(
    fileIndex, frameIndex, DC::ImageOrientationPatient);
  if (pv.GetNumberOfValues() == 3 && ov.GetNumberOfValues() == 6)
    {
    double orient[6], normal[3], point[3];
    pv.GetValues(point, point+3);
    ov.GetValues(orient, orient+6);

    if (this->MemoryRowOrder == vtkDICOMReader::BottomUp)
      {
      // calculate position of point at lower left
      double yspacing = this->DataSpacing[1];
      point[0] = point[0] + orient[3]*yspacing*(rows - 1);
      point[1] = point[1] + orient[4]*yspacing*(rows - 1);
      point[2] = point[2] + orient[5]*yspacing*(rows - 1);

      // measure orientation from lower left corner upwards
      orient[3] = -orient[3];
      orient[4] = -orient[4];
      orient[5] = -orient[5];
      }

    vtkMath::Cross(&orient[0], &orient[3], normal);
    double pm[16];
    pm[0] = orient[0]; pm[1] = orient[3]; pm[2] = normal[0]; pm[3] = point[0];
    pm[4] = orient[1]; pm[5] = orient[4]; pm[6] = normal[1]; pm[7] = point[1];
    pm[8] = orient[2]; pm[9] = orient[5]; pm[10] = normal[2]; pm[11] = point[2];
    pm[12] = 0.0; pm[13] = 0.0; pm[14] = 0.0; pm[15] = 1.0;
    this->PatientMatrix->DeepCopy(pm);
    }
  else
    {
    this->PatientMatrix->Identity();
    }

  // Set the output information.
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               extent, 6);

  outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(),  this->DataOrigin, 3);

  vtkDataObject::SetPointDataActiveScalarInfo(
    outInfo, this->DataScalarType, this->NumberOfScalarComponents);

  return 1;
}

namespace {

//----------------------------------------------------------------------------
// this rescales a series of data values
template<class T>
void vtkDICOMReaderRescaleBuffer(T *p, double m, double b, size_t bytecount)
{
  size_t n = bytecount/sizeof(T);
  if (n > 0 && (m != 1.0 || b != 0.0))
    {
    double minval = vtkTypeTraits<T>::Min();
    double maxval = vtkTypeTraits<T>::Max();
    do
      {
      double val = (*p)*m + b;
      if (val < minval)
        {
        val = minval;
        }
      if (val > maxval)
        {
        val = maxval;
        }
      *p++ = static_cast<T>(vtkMath::Round(val));
      }
    while (--n);
    }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMReader::RescaleBuffer(
  int fileIdx, void *buffer, vtkIdType bufferSize)
{
  vtkDICOMMetaData *meta = this->MetaData;
  double m = meta->GetAttributeValue(fileIdx, DC::RescaleSlope).AsDouble();
  double b = meta->GetAttributeValue(fileIdx, DC::RescaleIntercept).AsDouble();
  double m0 = this->RescaleSlope;
  double b0 = this->RescaleIntercept;

  // scale down to match the global slope and intercept
  b = (b - b0)/m0;
  m = m/m0;

  int bitsAllocated = meta->GetAttributeValue(DC::BitsAllocated).AsInt();
  int pixelRep = meta->GetAttributeValue(DC::PixelRepresentation).AsInt();

  if (bitsAllocated <= 8)
    {
    if (pixelRep == 0)
      {
      vtkDICOMReaderRescaleBuffer(
        static_cast<unsigned char *>(buffer), m, b, bufferSize);
      }
    else
      {
      vtkDICOMReaderRescaleBuffer(
        static_cast<signed char *>(buffer), m, b, bufferSize);
      }
    }
  else if (bitsAllocated <= 16)
    {
    if (pixelRep == 0)
      {
      vtkDICOMReaderRescaleBuffer(
        static_cast<unsigned short *>(buffer), m, b, bufferSize);
      }
    else
      {
      vtkDICOMReaderRescaleBuffer(
        static_cast<short *>(buffer), m, b, bufferSize);
      }
    }
  else if (bitsAllocated <= 32)
    {
    if (pixelRep == 0)
      {
      vtkDICOMReaderRescaleBuffer(
        static_cast<unsigned int *>(buffer), m, b, bufferSize);
      }
    else
      {
      vtkDICOMReaderRescaleBuffer(
        static_cast<int *>(buffer), m, b, bufferSize);
      }
    }
}

//----------------------------------------------------------------------------
void vtkDICOMReader::UnpackBits(
  const void *filePtr, void *buffer, vtkIdType bufferSize, int bits)
{
  if (bits == 12)
    {
    const unsigned char *readPtr =
      static_cast<const unsigned char *>(filePtr);
    unsigned char *writePtr =
      static_cast<unsigned char *>(buffer);
    for (vtkIdType n = bufferSize/2; n > 0; n -= 2)
      {
      unsigned int a1 = readPtr[0];
      unsigned int a2 = readPtr[1];
      unsigned int b1 = (a1 << 4) | (a2 & 0x0f);
      writePtr[0] = static_cast<unsigned char>(b1);
      writePtr[1] = static_cast<unsigned char>(b1 >> 8);

      if (n == 1) { break; }

      unsigned int a3 = readPtr[2];
      unsigned int b2 = ((a3 & 0x0f) << 8) | (a2 & 0xf0) | (a3 >> 4);
      writePtr[2] = static_cast<unsigned char>(b2);
      writePtr[3] = static_cast<unsigned char>(b2 >> 8);

      readPtr += 3;
      writePtr += 4;
      }
    }
  else if (bits == 1)
    {
    const unsigned char *readPtr =
      static_cast<const unsigned char *>(filePtr);
    unsigned char *writePtr =
      static_cast<unsigned char *>(buffer);
    for (vtkIdType n = bufferSize/8; n > 0; n--)
      {
      unsigned int a = *readPtr;
      for (int i = 0; i < 8; i++)
        {
        writePtr[i] = (a & 1);
        a >>= 1;
        }
      readPtr++;
      writePtr += 8;
      }
    size_t r = (bufferSize % 8);
    if (r > 0)
      {
      unsigned int a = *readPtr;
      for (size_t j = 0; j < r; j++)
        {
        writePtr[j] = static_cast<unsigned char>(a & 1);
        a >>= 1;
        }
      }
    }
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadUncompressedFile(
  const char *filename, int fileIdx, char *buffer, vtkIdType bufferSize)
{
  // get the offset to the PixelData in the file
  vtkTypeInt64 offsetAndSize[2];
  this->FileOffsetArray->GetTupleValue(fileIdx, offsetAndSize);
  vtkTypeInt64 offset = offsetAndSize[0];

  vtkDebugMacro("Opening DICOM file " << filename);
  std::ifstream infile(filename, ios::in | ios::binary);

  if (infile.fail())
    {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("ReadFile: Can't read the file " << filename);
    return false;
    }

  if (!infile.seekg(static_cast<std::streamoff>(offset), std::ios::beg))
    {
    this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
    vtkErrorMacro("DICOM file is truncated, some data is missing.");
    return false;
    }

  int bitsAllocated = this->MetaData->GetAttributeValue(
    fileIdx, DC::BitsAllocated).AsInt();

  if (bitsAllocated == 12)
    {
    // unpack 12 bits little endian into 16 bits little endian,
    // the result will have to be swapped if machine is BE (the
    // swapping is done at the end of this function)
    size_t fileSize = bufferSize/2 + (bufferSize+3)/4;
    char *filePtr = buffer + (bufferSize - fileSize);
    infile.read(filePtr, fileSize);

    vtkDICOMReader::UnpackBits(filePtr, buffer, bufferSize, bitsAllocated);
    }
  else if (bitsAllocated == 1)
    {
    // unpack 1 bit into 8 bits, source assumed to be either OB
    // or little endian OW, never big endian OW
    size_t fileSize = (bufferSize + 7)/8;
    char *filePtr = buffer + (bufferSize - fileSize);
    infile.read(filePtr, fileSize);

    vtkDICOMReader::UnpackBits(filePtr, buffer, bufferSize, bitsAllocated);
    }
  else
    {
    infile.read(buffer, bufferSize);
    }

  if (infile.eof())
    {
    this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
    vtkErrorMacro("DICOM file is truncated, some data is missing.");
    return false;
    }
  else if (infile.fail())
    {
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    vtkErrorMacro("Error in DICOM file, cannot read.");
    return false;
    }

  if (this->SwapBytes)
    {
    int scalarSize = vtkDataArray::GetDataTypeSize(this->DataScalarType);
    vtkByteSwap::SwapVoidRange(buffer, bufferSize/scalarSize, scalarSize);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadCompressedFile(
  const char *filename, int fileIdx, char *buffer, vtkIdType bufferSize)
{
#if defined(DICOM_USE_DCMTK)

  DcmFileFormat *fileformat = new DcmFileFormat();
  fileformat->loadFile(filename);
  OFCondition status = fileformat->getDataset()->chooseRepresentation(
    EXS_LittleEndianExplicit, NULL);

  if (!status.good())
    {
    vtkErrorMacro("DCMTK error: " << status.text());
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    delete fileformat;
    return false;
    }

  unsigned long count;
  const Uint8 *pixelData;
  status = fileformat->getDataset()->findAndGetUint8Array(
    DCM_PixelData, pixelData, &count, OFTrue);
  vtkIdType imageSize = static_cast<vtkIdType>(count);

  int bitsAllocated = this->MetaData->GetAttributeValue(
    fileIdx, DC::BitsAllocated).AsInt();

  if (bitsAllocated == 12 && imageSize >= bufferSize/2 + (bufferSize+3)/4)
    {
    vtkDICOMReader::UnpackBits(pixelData, buffer, bufferSize, bitsAllocated);
    }
  else if (bitsAllocated == 1 && imageSize >= (bufferSize + 7)/8)
    {
    vtkDICOMReader::UnpackBits(pixelData, buffer, bufferSize, bitsAllocated);
    }
  else if (imageSize >= bufferSize)
    {
    memcpy(buffer, pixelData, bufferSize);
    }
  else
    {
    vtkErrorMacro(<< filename << ": The uncompressed image size is "
                  << imageSize << " bytes, expected "
                  << bufferSize << " bytes.");
    delete fileformat;
    return false;
    }

  delete fileformat;
  return true;

#elif defined(DICOM_USE_GDCM)

  (void)fileIdx;

  gdcm::ImageReader reader;
  reader.SetFileName(filename);
  if(!reader.Read())
    {
    vtkErrorMacro("The GDCM ImageReader could not read the image.");
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return false;
    }

  gdcm::Image &image = reader.GetImage();
  if (static_cast<vtkIdType>(image.GetBufferLength()) < bufferSize)
    {
    vtkErrorMacro(<< filename << ": The uncompressed image size is "
                  << image.GetBufferLength() << " bytes, expected "
                  << bufferSize << " bytes.");
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return false;
    }

  image.GetBuffer(buffer);
  return true;

#else /* no DCMTK or GDCM, so no file decompression */

  (void)filename;
  (void)fileIdx;
  (void)buffer;
  (void)bufferSize;

  this->SetErrorCode(vtkErrorCode::FileFormatError);
  vtkErrorMacro("DICOM file is compressed, cannot read.");
  return false;

#endif
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadOneFile(
  const char *filename, int fileIdx, char *buffer, vtkIdType bufferSize)
{
  std::string transferSyntax = this->MetaData->GetAttributeValue(
    fileIdx, DC::TransferSyntaxUID).AsString();

  if (transferSyntax == "1.2.840.10008.1.2"   ||  // Implicit LE
      transferSyntax == "1.2.840.10008.1.20"  ||  // Papyrus Implicit LE
      transferSyntax == "1.2.840.10008.1.2.1" ||  // Explicit LE
      transferSyntax == "1.2.840.10008.1.2.2" ||  // Explicit BE
      transferSyntax == "1.2.840.113619.5.2"  ||  // GE LE with BE data
      transferSyntax == "")
    {
    return this->ReadUncompressedFile(filename, fileIdx, buffer, bufferSize);
    }

  return this->ReadCompressedFile(filename, fileIdx, buffer, bufferSize);
}

//----------------------------------------------------------------------------
int vtkDICOMReader::RequestData(
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
    return true;
    }

  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  int extent[6];
  outInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  if (this->FileDimensionality == 2)
    {
    // limit the number of slices to the requested update extent
    int uExtent[6];
    outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), uExtent);
    extent[4] = uExtent[4];
    extent[5] = uExtent[5];
    }

  // make a list of all the files inside the update extent
  std::vector<vtkDICOMReaderFileInfo> files;
  int nComp = this->FileIndexArray->GetNumberOfComponents();
  for (int sIdx = extent[4]; sIdx <= extent[5]; sIdx++)
    {
    for (int cIdx = 0; cIdx < nComp; cIdx++)
      {
      int fileIdx = this->FileIndexArray->GetComponent(sIdx, cIdx);
      int frameIdx = this->FrameIndexArray->GetComponent(sIdx, cIdx);
      std::vector<vtkDICOMReaderFileInfo>::iterator iter = files.begin();
      while (iter != files.end() && iter->FileIndex != fileIdx)
        {
        ++iter;
        }
      if (iter == files.end())
        {
        int n = this->MetaData->GetAttributeValue(
          fileIdx, DC::NumberOfFrames).AsInt();
        n = (n > 0 ? n : 1);
        files.push_back(vtkDICOMReaderFileInfo(fileIdx, n));
        iter = files.end();
        --iter;
        }
      iter->Frames.push_back(vtkDICOMReaderFrameInfo(frameIdx, sIdx, cIdx));
      }
    }

  // get the data object, allocate memory
  vtkImageData *data =
    static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));
#if VTK_MAJOR_VERSION >= 6
  this->AllocateOutputData(data, outInfo, extent);
#else
  this->AllocateOutputData(data, extent);
#endif

  data->GetPointData()->GetScalars()->SetName("PixelData");

  char *dataPtr = static_cast<char *>(data->GetScalarPointer());

  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();
  int numFileComponents = this->NumberOfPackedComponents;
  int numPlanes = this->NumberOfPlanarComponents;

  vtkIdType pixelSize = numComponents*scalarSize;
  vtkIdType rowSize = pixelSize*(extent[1] - extent[0] + 1);
  vtkIdType sliceSize = rowSize*(extent[3] - extent[2] + 1);
  vtkIdType filePixelSize = numFileComponents*scalarSize;
  vtkIdType fileRowSize = filePixelSize*(extent[1] - extent[0] + 1);
  vtkIdType filePlaneSize = fileRowSize*(extent[3] - extent[2] + 1);
  vtkIdType fileFrameSize = filePlaneSize*numPlanes;

  this->InvokeEvent(vtkCommand::StartEvent);

  bool flipImage = (this->MemoryRowOrder == vtkDICOMReader::BottomUp);
  bool planarToPacked = (filePixelSize != pixelSize);
  char *rowBuffer = 0;
  if (flipImage)
    {
    rowBuffer = new char[fileRowSize];
    }
  char *fileBuffer = 0;
  int framesInPreviousFile = -1;

  // loop through all files in the update extent
  for (size_t idx = 0; idx < files.size(); idx++)
    {
    if (this->AbortExecute) { break; }

    this->UpdateProgress(static_cast<double>(idx)/
                         static_cast<double>(files.size()));

    // get the index for this file
    int fileIdx = files[idx].FileIndex;
    int framesInFile = files[idx].FramesInFile;
    std::vector<vtkDICOMReaderFrameInfo>& frames = files[idx].Frames;
    int numFrames = static_cast<int>(frames.size());

    // we need a file buffer if input frames don't match output slices
    bool needBuffer = (planarToPacked || numFrames != framesInFile);
    for (int sIdx = 0; sIdx < numFrames && !needBuffer; sIdx++)
      {
      needBuffer = (sIdx != frames[sIdx].FrameIndex);
      }

    char *bufferPtr = 0;

    if (needBuffer)
      {
      if (numFrames != framesInPreviousFile)
        {
        // allocate a buffer for planar-to-packed conversion
        delete [] fileBuffer;
        fileBuffer = new char[fileFrameSize*framesInFile];
        framesInPreviousFile = numFrames;
        }
      bufferPtr = fileBuffer;
      }
    else
      {
      // read directly into the output
      int sliceIdx = frames[0].SliceIndex;
      int componentIdx = frames[0].ComponentIndex;
      bufferPtr = (dataPtr +
                   (sliceIdx - extent[4])*sliceSize +
                   componentIdx*filePixelSize*numPlanes);
      }

    this->ComputeInternalFileName(fileIdx);
    this->ReadOneFile(this->InternalFileName, fileIdx,
                      bufferPtr, framesInFile*fileFrameSize);

    // iterate through all frames contained in the file
    for (int sIdx = 0; sIdx < numFrames; sIdx++)
      {
      int frameIdx = frames[sIdx].FrameIndex;
      int sliceIdx = frames[sIdx].SliceIndex;
      int componentIdx = frames[sIdx].ComponentIndex;
      // go to the correct position in the input
      char *framePtr = bufferPtr + frameIdx*fileFrameSize;
      // go to the correct position in the output
      char *slicePtr = (dataPtr +
                        (sliceIdx - extent[4])*sliceSize +
                        componentIdx*filePixelSize*numPlanes);

      // rescale if Rescale was different for different files
      if (this->NeedsRescale)
        {
        this->RescaleBuffer(fileIdx, bufferPtr, sliceSize);
        }

      // iterate through all color planes in the slice
      char *planePtr = framePtr;
      for (int pIdx = 0; pIdx < numPlanes; pIdx++)
        {
        // flip the data if necessary
        if (flipImage)
          {
          int numRows = extent[3] - extent[2] + 1;
          int halfRows = numRows/2;
          for (int yIdx = 0; yIdx < halfRows; yIdx++)
            {
            char *row1 = planePtr + yIdx*fileRowSize;
            char *row2 = planePtr + (numRows-yIdx-1)*fileRowSize;
            memcpy(rowBuffer, row1, fileRowSize);
            memcpy(row1, row2, fileRowSize);
            memcpy(row2, rowBuffer, fileRowSize);
            }
          }

        // convert planes into vector components
        if (planarToPacked)
          {
          const char *tmpInPtr = planePtr;
          char *tmpOutPtr = slicePtr;
          int m = sliceSize/pixelSize;
          for (int i = 0; i < m; i++)
            {
            vtkIdType n = filePixelSize;
            do { *tmpOutPtr++ = *tmpInPtr++; } while (--n);
            tmpOutPtr += pixelSize - filePixelSize;
            }
          slicePtr += filePixelSize;
          }
        else if (slicePtr != planePtr)
          {
          memcpy(slicePtr, planePtr, filePlaneSize);
          }

        planePtr += filePlaneSize;
        }
      }
    }

  delete [] rowBuffer;
  delete [] fileBuffer;

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}

//----------------------------------------------------------------------------
void vtkDICOMReader::RelayError(vtkObject *o, unsigned long e, void *data)
{
  if (e == vtkCommand::ErrorEvent)
    {
    vtkDICOMParser *parser = vtkDICOMParser::SafeDownCast(o);
    if (parser && parser->GetErrorCode())
      {
      this->SetErrorCode(parser->GetErrorCode());
      }

    vtkErrorMacro(<< static_cast<char *>(data));
    }
  else
    {
    this->InvokeEvent(e, data);
    }
}
