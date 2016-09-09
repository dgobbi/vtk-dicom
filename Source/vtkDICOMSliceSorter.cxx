/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMSliceSorter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMTagPath.h"

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkMath.h>

#include <algorithm>
#include <string>

#include <ctype.h>

vtkStandardNewMacro(vtkDICOMSliceSorter);

//----------------------------------------------------------------------------
vtkDICOMSliceSorter::vtkDICOMSliceSorter()
{
  this->FileIndexArray = vtkIntArray::New();
  this->FrameIndexArray = vtkIntArray::New();
  this->StackIDs = vtkStringArray::New();
  this->MetaData = 0;
  this->TimeAsVector = 0;
  this->DesiredTimeIndex = -1;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->SliceSpacing = 1.0;
  this->DesiredStackID[0] = '\0';
  this->ReverseSlices = 0;
}

//----------------------------------------------------------------------------
vtkDICOMSliceSorter::~vtkDICOMSliceSorter()
{
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
}

//----------------------------------------------------------------------------
void vtkDICOMSliceSorter::PrintSelf(ostream& os, vtkIndent indent)
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

  os << indent << "ReverseSlices: "
     << (this->ReverseSlices ? "On\n" : "Off\n");
  os << indent << "SliceSpacing: " << this->SliceSpacing << "\n";

  os << indent << "TimeAsVector: "
     << (this->TimeAsVector ? "On\n" : "Off\n");
  os << indent << "TimeDimension: " << this->TimeDimension << "\n";
  os << indent << "TimeSpacing: " << this->TimeSpacing << "\n";
  os << indent << "DesiredTimeIndex: " << this->DesiredTimeIndex << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMSliceSorter::SetMetaData(vtkDICOMMetaData *meta)
{
  if (this->MetaData != meta)
  {
    if (this->MetaData)
    {
      this->MetaData->Delete();
    }
    if (meta)
    {
      meta->Register(this);
    }
    this->MetaData = meta;
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMSliceSorter::SetDesiredStackID(const char *stackId)
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

// a class and methods for sorting the files
struct vtkDICOMSliceSorterSortInfo
{
  int FileNumber;
  int FrameNumber;
  int InstanceNumber;
  int PositionNumber;
  double ComputedLocation;
  double Time;

  vtkDICOMSliceSorterSortInfo() :
    FileNumber(0), FrameNumber(0), InstanceNumber(0), PositionNumber(0),
    ComputedLocation(0.0), Time(0.0) {}

  vtkDICOMSliceSorterSortInfo(int i, int j, int k, int s, double l, double t) :
    FileNumber(i), FrameNumber(j), InstanceNumber(k), PositionNumber(s),
    ComputedLocation(l), Time(t) {}

  vtkDICOMSliceSorterSortInfo(int i, int k) :
    FileNumber(i), FrameNumber(0), InstanceNumber(k), PositionNumber(0),
    ComputedLocation(0), Time(0) {}

  // for sorting by by instance number
  static bool CompareInstance(
    const vtkDICOMSliceSorterSortInfo &si1, const vtkDICOMSliceSorterSortInfo &si2)
  {
    return (si1.InstanceNumber < si2.InstanceNumber);
  }

  // for sorting by position number
  static bool ComparePosition(
    const vtkDICOMSliceSorterSortInfo &si1, const vtkDICOMSliceSorterSortInfo &si2)
  {
    return (si1.PositionNumber < si2.PositionNumber);
  }

  // for sorting by spatial location
  static bool CompareLocation(
    const vtkDICOMSliceSorterSortInfo &si1, const vtkDICOMSliceSorterSortInfo &si2)
  {
    // locations must differ by at least the tolerance
    const double locationTolerance = 1e-3;
    return (si1.ComputedLocation + locationTolerance < si2.ComputedLocation);
  }
};

// get an attribute value for a particular frame
const vtkDICOMValue& vtkDICOMSliceSorterGetFrameAttributeValue(
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
double vtkDICOMSliceSorterComputeLocation(
  const vtkDICOMValue& pv, const vtkDICOMValue& ov,
  double checkOrientation[14], bool *checkPtr)
{
  double location = 0.0;

  if (pv.GetNumberOfValues() != 3 || ov.GetNumberOfValues() != 6)
  {
    *checkPtr = false;
  }
  else
  {
    double orientation[6], normal[3], position[3];
    pv.GetValues(position, 3);
    ov.GetValues(orientation, 6);

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
        checkOrientation[10+i] = normal[i];
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
      double vdir = (vtkMath::Dot(v, normal) < 0 ? -1.0 : 1.0);

      // set the check vector if it isn't set yet
      if (checkOrientation[13] == 0 &&
          v[0]*v[0] + v[1]*v[1] + v[2]*v[2] >
          positionTolerance*positionTolerance)
      {
        for (int i = 0; i < 3; i++)
        {
          checkOrientation[10+i] = vdir*v[i];
        }
        vtkMath::Normalize(&checkOrientation[10]);
      }

      // compare vector to check vector
      double w = vtkMath::Norm(&checkOrientation[10]);
      double t = vtkMath::Dot(v, &checkOrientation[10])/w;
      double dv[3];
      dv[0] = v[0] - t*checkOrientation[10];
      dv[1] = v[1] - t*checkOrientation[11];
      dv[2] = v[2] - t*checkOrientation[12];
      double d = dv[0]*dv[0] + dv[1]*dv[1] + dv[2]*dv[2];
      // the position tolerance is in millimetres
      if (d > (positionTolerance*positionTolerance +
               t*t*directionTolerance*directionTolerance))
      {
        // positions don't line up along the normal
        *checkPtr = false;
      }
      else if (checkOrientation[13] != 0 && vtkMath::Norm(v) > w)
      {
        // use new vector as check vector if it is longer
        for (int i = 0; i < 3; i++)
        {
          checkOrientation[10+i] = vdir*v[i];
        }
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
        checkOrientation[10+i] = normal[i];
      }
      // mark the check vector as unset
      checkOrientation[13] = 0;
    }
  }

  return location;
}

// compute the spacing between slices
double vtkDICOMSliceSorterComputeSpacing(
  const std::vector<vtkDICOMSliceSorterSortInfo>& info,
  int *missing)
{
  double a = 0;
  double v = VTK_DOUBLE_MAX;
  size_t m = VTK_UNSIGNED_INT_MAX;
  int o = 0;

  while (m != 0)
  {
    // compute the mean spacing and the variance in spacing
    double s1 = 0.0;
    double s2 = 0.0;
    size_t n = 0;
    o = 0;
    for (size_t i = 1; i < info.size(); i++)
    {
      // first verify that locations aren't identical
      if (vtkDICOMSliceSorterSortInfo::CompareLocation(info[i-1], info[i]))
      {
        // compute the offset
        double d = info[i].ComputedLocation - info[i-1].ComputedLocation;
        double dd = (d - a)*(d - a);
        // make sure offset is within 3 sigma or 10% of average offset
        if (dd < 0.01*a*a || dd < 9*v)
        {
          s1 += d;
          s2 += d*d;
          n++;
        }
        else
        {
          o++;
        }
      }
    }

    // no results!
    if (n == 0)
    {
      break;
    }

    // compute the mean and variance
    a = s1 / n;
    v = s2/n - a*a;

    // break if within tolerance or if results haven't changed
    if (v/(a*a) < 1e-6 || n == m)
    {
      break;
    }

    // save count to use as check
    m = n;
  }

  *missing = o;
  return a;
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMSliceSorter::SortFiles(vtkIntArray *files, vtkIntArray *frames)
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
  std::vector<vtkDICOMSliceSorterSortInfo> info;

  // sort by instance first
  for (int i = 0; i < numFiles; i++)
  {
    int inst = meta->GetAttributeValue(i, DC::InstanceNumber).AsInt();
    info.push_back(vtkDICOMSliceSorterSortInfo(i, inst));
  }
  std::stable_sort(info.begin(), info.end(),
    vtkDICOMSliceSorterSortInfo::CompareInstance);
  std::vector<int> fileOrder(info.size());
  for (int i = 0; i < numFiles; i++)
  {
    fileOrder[i] = info[i].FileNumber;
  }
  info.clear();

  // important position-related variables
  std::vector<size_t> volumeBreaks;
  double checkOrientation[14] = {};
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
    std::vector<vtkDICOMSliceSorterSortInfo> stackInfo;
    vtkDICOMValue firstStackId;
    vtkDICOMValue desiredStackId =
      vtkDICOMValue(vtkDICOMVR::SH, this->DesiredStackID);
    double stackCheckNormal[14] = {};
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
        firstStackId = vtkDICOMSliceSorterGetFrameAttributeValue(
          frameSeq, sharedSeq, 0, DC::FrameContentSequence,
          DC::StackID);
      }

      // attributes for getting time information
      vtkDICOMTag timeSequence;
      vtkDICOMTag timeTag;

      if (numberOfFrames > 0)
      {
        // time information can come from these attributes
        if (vtkDICOMSliceSorterGetFrameAttributeValue(
              frameSeq, sharedSeq, 0, DC::CardiacSynchronizationSequence,
              DC::NominalCardiacTriggerDelayTime).IsValid())
        {
          timeSequence = DC::CardiacSynchronizationSequence;
          timeTag = DC::NominalCardiacTriggerDelayTime;
        }
        else if (vtkDICOMSliceSorterGetFrameAttributeValue(
                   frameSeq, sharedSeq, 0, DC::TemporalPositionSequence,
                   DC::TemporalPositionTimeOffset).IsValid())
        {
          timeSequence = DC::TemporalPositionSequence;
          timeTag = DC::TemporalPositionTimeOffset;
          temporalSpacing = 1000.0; // convert seconds to milliseconds
        }
        else if (vtkDICOMSliceSorterGetFrameAttributeValue(
                  frameSeq, sharedSeq, 0, DC::FrameContentSequence,
                  DC::TemporalPositionIndex).IsValid())
        {
          timeSequence = DC::FrameContentSequence;
          timeTag = DC::TemporalPositionIndex;
        }
        else if (vtkDICOMSliceSorterGetFrameAttributeValue(
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
          t = vtkDICOMSliceSorterGetFrameAttributeValue(
            frameSeq, sharedSeq, k, timeSequence, timeTag).AsDouble();
        }

        // adjust position only if time did not change
        if (fabs(t - lastTime) < 1e-3 || k == 0)
        {
          position = k;
          lastTime = t;
        }

        // get the StackID
        vtkDICOMValue stackId = vtkDICOMSliceSorterGetFrameAttributeValue(
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
          position = vtkDICOMSliceSorterGetFrameAttributeValue(
            frameSeq, sharedSeq, k, DC::FrameContentSequence,
            DC::InStackPositionNumber).AsInt();
        }

        // check for valid Image Plane Module information
        vtkDICOMValue pv = vtkDICOMSliceSorterGetFrameAttributeValue(
          frameSeq, sharedSeq, k, DC::PlanePositionSequence,
          DC::ImagePositionPatient);
        vtkDICOMValue ov = vtkDICOMSliceSorterGetFrameAttributeValue(
          frameSeq, sharedSeq, k, DC::PlaneOrientationSequence,
          DC::ImageOrientationPatient);

        // check if the StackId is the one the user specified
        if (stackId == desiredStackId)
        {
          // compute location from orientation and IPP
          double location = vtkDICOMSliceSorterComputeLocation(
            pv, ov, stackCheckNormal, &canSortStackByIPP);

          location /= spacingBetweenSlices;

          stackInfo.push_back(
            vtkDICOMSliceSorterSortInfo(i, k, inst, position, location, t));
        }
        else if (stackId == firstStackId)
        {
          // compute location from orientation and IPP
          double location = vtkDICOMSliceSorterComputeLocation(
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
            vtkDICOMSliceSorterSortInfo(i, k, inst, position, location, t));
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

      location = vtkDICOMSliceSorterComputeLocation(
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
          vtkDICOMSliceSorterSortInfo(i, 0, inst, position, location, t));
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
              vtkDICOMSliceSorterSortInfo(i, k, inst, position, frameloc, t));
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
              vtkDICOMSliceSorterSortInfo(i, k, inst, inst, location, t));
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
      // breaks will be used to indicate new stacks
      volumeBreaks.push_back(info.size());

      size_t stt = 0;
      size_t sttlen = volumeBreaks[0];
      for (size_t k = 0; k < volumeBreaks.size(); k++)
      {
        // build the list of StackIDs
        vtkVariant var(k);
        this->StackIDs->InsertNextValue(var.ToString());
        size_t len = volumeBreaks[k] - (k == 0 ? 0 : volumeBreaks[k-1]);
        // identify the first stack with multiple images
        if (sttlen == 1 && len > sttlen)
        {
          stt = k;
          sttlen = len;
        }
      }

      // if DesiredStackID is set, use it
      if (this->DesiredStackID[0] != '\0')
      {
        stt = strtoul(this->DesiredStackID, 0, 10);
      }

      // load just one of the rectilinear stacks that are present
      if (stt >= volumeBreaks.size())
      {
        stt = 0;
      }
      info.erase(info.begin() + volumeBreaks[stt], info.end());
      if (stt > 0)
      {
        info.erase(info.begin(), info.begin() + volumeBreaks[stt-1]);
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
        vtkDICOMSliceSorterSortInfo::CompareLocation);
    }
    else
    {
      std::stable_sort(info.begin(), info.end(),
        vtkDICOMSliceSorterSortInfo::ComparePosition);
    }

    // look for slices at the same location
    std::vector<vtkDICOMSliceSorterSortInfo>::iterator iter = info.begin();
    int slicesAtThisLocation = 0;
    while (iter != info.end())
    {
      std::vector<vtkDICOMSliceSorterSortInfo>::iterator nextIter = iter + 1;
      slicesAtThisLocation++;
      bool positionIncreased = false;
      if (nextIter != info.end())
      {
        // use the tolerance built into CompareLocation
        if (canSortByLocation)
        {
          positionIncreased =
            vtkDICOMSliceSorterSortInfo::CompareLocation(*iter, *nextIter);
        }
        else
        {
          positionIncreased =
            vtkDICOMSliceSorterSortInfo::ComparePosition(*iter, *nextIter);
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
  if (slicesPerLocation == 0)
  {
    slicesPerLocation = 1;
  }
  else if (slicesPerLocation == -1)
  {
    slicesPerLocation = 1;
    vtkWarningMacro("Multidimensional series appears to be missing slices,"
                    " representation will be inaccurate.");
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
      int missing = 0;
      locDiff = vtkDICOMSliceSorterComputeSpacing(info, &missing);
      if (missing > 0)
      {
        vtkWarningMacro("Series has " << missing <<
                        " gaps due to missing slices.");
      }
      if (locations > spatialLocations)
      {
        // squeeze time slices between spatial slices
        locDiff *= spatialLocations*1.0/locations;
      }
    }
    if (locDiff > 0)
    {
      spacingBetweenSlices *= locDiff;
    }
  }

  // write out the sorted indices
  bool flipOrder = (this->ReverseSlices != 0);
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
  this->SliceSpacing = spacingBetweenSlices;
  this->TimeDimension = temporalPositions;
  this->TimeSpacing = temporalSpacing;
}

//----------------------------------------------------------------------------
void vtkDICOMSliceSorter::Update()
{
  this->StackIDs->Initialize();
  this->SortFiles(this->FileIndexArray, this->FrameIndexArray);
}
