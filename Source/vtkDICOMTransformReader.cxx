/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMTransformReader.h"

#include "vtkDICOMDictionary.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"

#include "vtkObjectFactory.h"

#include "vtkCollection.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkTransform.h"
#include "vtkGeneralTransform.h"
#include "vtkAbstractTransform.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkDemandDrivenPipeline.h"
#include "vtkSmartPointer.h"

#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string>

//--------------------------------------------------------------------------
vtkStandardNewMacro(vtkDICOMTransformReader);

//-------------------------------------------------------------------------
vtkDICOMTransformReader::vtkDICOMTransformReader()
{
  this->FileName = 0;
  this->MetaData = vtkDICOMMetaData::New();
  this->Transforms = vtkCollection::New();
  this->Transform = vtkTransform::New();
}

//-------------------------------------------------------------------------
vtkDICOMTransformReader::~vtkDICOMTransformReader()
{
  if (this->Transforms)
    {
    this->Transforms->Delete();
    }
  if (this->Transform)
    {
    this->Transform->Delete();
    }
  if (this->MetaData)
    {
    this->MetaData->Delete();
    }

  delete [] this->FileName;
}

//-------------------------------------------------------------------------
void vtkDICOMTransformReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "FileName: "
     << (this->FileName ? this->FileName : "none") << "\n";
  os << indent << "Transform: " << this->Transform << "\n";
  if (this->Transform)
    {
    this->Transform->PrintSelf(os, indent.GetNextIndent());
    }
  os << indent << "NumberOfTransforms: "
     << this->Transforms->GetNumberOfItems() << "\n";
}

//----------------------------------------------------------------------------
namespace {

// This silences error printing when CanReadFile is testing a file.
class vtkDICOMErrorSilencer : public vtkCommand
{
public:
  static vtkDICOMErrorSilencer *New() { return new vtkDICOMErrorSilencer; }
  vtkTypeMacro(vtkDICOMErrorSilencer,vtkCommand);
  virtual void Execute(vtkObject *, unsigned long, void *) {}
protected:
  vtkDICOMErrorSilencer() {}
  vtkDICOMErrorSilencer(const vtkDICOMErrorSilencer& c) : vtkCommand(c) {}
  void operator=(const vtkDICOMErrorSilencer&) {}
};

} // end anonymous namespace

//-------------------------------------------------------------------------
int vtkDICOMTransformReader::CanReadFile(const char* fname)
{
  if (fname == 0)
    {
    return 0;
    }

  // First make sure the file exists.
  struct stat fs;
  if(stat(fname, &fs) != 0)
    {
    return 0;
    }

  vtkSmartPointer<vtkDICOMErrorSilencer> command =
    vtkSmartPointer<vtkDICOMErrorSilencer>::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();
  vtkDICOMMetaData *meta = this->MetaData;

  // Add a dummy observer to silence errors
  unsigned long cid = parser->AddObserver(vtkCommand::ErrorEvent, command);
  parser->SetFileName(fname);
  parser->SetMetaData(meta);
  parser->Update();
  parser->RemoveObserver(cid);

  // Check for the correct IOD
  return meta->GetAttributeValue(DC::SOPClassUID).Matches(
                 "1.2.840.10008.5.1.4.1.1.66.1");
}

//-------------------------------------------------------------------------
int vtkDICOMTransformReader::ReadFile()
{
  this->Transforms->RemoveAllItems();
  this->MetaData->Initialize();

  // Check that the file name has been set.
  if (!this->FileName || this->FileName[0] == '\0')
    {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("ReadFile: No file name has been set");
    return 0;
    }

  // Make sure that the file exists.
  struct stat fs;
  if (stat(this->FileName, &fs) != 0)
    {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("ReadFile: Can't open file " << this->FileName);
    return 0;
    }

  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  parser->AddObserver(
    vtkCommand::ErrorEvent, this, &vtkDICOMTransformReader::RelayError);

  parser->SetFileName(this->FileName);
  parser->SetMetaData(meta);
  parser->Update();

  if (parser->GetErrorCode())
    {
    return 0;
    }

  std::string sop = meta->GetAttributeValue(DC::SOPClassUID).AsString();
  const char *stsop = "1.2.840.10008.5.1.4.1.1.66.1";

  if (sop != stsop)
    {
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    vtkErrorMacro("ReadFile: Data set is not a \"Spatial Transform\","
                  " required SOPClassUID is " << stsop <<
                  ", file SOPClassUID is " << sop.c_str());
    return 0;
    }

  std::string modality = meta->GetAttributeValue(DC::Modality).AsString();
  if (modality != "REG")
    {
    vtkWarningMacro("ReadFile: Expected modality \"REG\", but data set"
                    " modality is \"" << modality.c_str() << "\"");
    }

  // Read the RegistrationSequence
  const vtkDICOMValue& rs = meta->GetAttributeValue(DC::RegistrationSequence);
  const vtkDICOMItem *ri = rs.GetSequenceData();

  if (ri == 0)
    {
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    vtkErrorMacro("ReadFile: The RegistrationSequence attribute is missing!");
    return 0;
    }

  // Only read the first item in the sequence (ignore the rest)
  size_t n = rs.GetNumberOfValues();
  for (size_t i = 0; i < n; i++)
    {
    const vtkDICOMValue& mrs = ri[i].GetAttributeValue(
      DC::MatrixRegistrationSequence);
    const vtkDICOMItem *mri = mrs.GetSequenceData();
    if (mri == 0)
      {
      this->SetErrorCode(vtkErrorCode::FileFormatError);
      vtkErrorMacro("ReadFile: The MatrixRegistrationSequence attribute"
                    " is missing!");
      return 0;
      }

    // Only one item is allowed in the MatrixRegistrationSequence
    size_t m = mrs.GetNumberOfValues();
    m = (m < 1 ? m : 1);
    for (size_t j = 0; j < m; j++)
      {
      const vtkDICOMValue& ms = mri[j].GetAttributeValue(DC::MatrixSequence);
      const vtkDICOMItem *mi = ms.GetSequenceData();
      if (mi == 0)
        {
        this->SetErrorCode(vtkErrorCode::FileFormatError);
        vtkErrorMacro("ReadFile: The MatrixSequence attribute is missing!");
        return 0;
        }

      size_t mn = ms.GetNumberOfValues();
      for (size_t k = 0; k < mn; k++)
        {
        const vtkDICOMValue& matType = mi[k].GetAttributeValue(
          DC::FrameOfReferenceTransformationMatrixType);
        const vtkDICOMValue& mat = mi[k].GetAttributeValue(
          DC::FrameOfReferenceTransformationMatrix);
        if (!matType.Matches("RIGID") &&
            !matType.Matches("RIGID_SCALE") &&
            !matType.Matches("AFFINE"))
          {
          vtkWarningMacro("ReadFile: Unrecognized matrix type \"" <<
            matType.AsString().c_str() << "\"");
          }
        if (mat.GetNumberOfValues() != 16)
          {
          this->SetErrorCode(vtkErrorCode::FileFormatError);
          vtkErrorMacro("ReadFile: Invalid"
                        " FrameOfReferenceTransformationMatrix.");
          return 0;
          }

        double matrix[16];
        mat.GetValues(matrix, 16);

        // Create the transform
        vtkSmartPointer<vtkTransform> transform =
          vtkSmartPointer<vtkTransform>::New();

        transform->Concatenate(matrix); 
        this->Transforms->AddItem(transform);
        }
      }
    }

  return this->CreateOutputTransform();
}

//-------------------------------------------------------------------------
int vtkDICOMTransformReader::CreateOutputTransform()
{
  // Create the output transform.
  int n = this->Transforms->GetNumberOfItems();
  if (n == 1)
    {
    this->SetTransform(
      static_cast<vtkAbstractTransform *>(
        this->Transforms->GetItemAsObject(0)));
    }
  else
    {
    // Determine whether the full transform is linear
    int linear = 1;
    int i = 0;
    for (i = 0; i < n; i++)
      {
      if (!vtkLinearTransform::SafeDownCast(
            this->Transforms->GetItemAsObject(i)))
        {
        linear = 0;
        break;
        }
      }

    // If linear, use vtkTransform to concatenate,
    // else use vtkGeneralTransform.
    if (linear)
      {
      vtkTransform *transform = vtkTransform::New();
      transform->PostMultiply();
      for (i = 0; i < n; i++)
        {
        vtkLinearTransform *linearTransform =
          static_cast<vtkLinearTransform *>(
            this->Transforms->GetItemAsObject(i));
        transform->Concatenate(linearTransform->GetMatrix());
        }
      this->SetTransform(transform);
      transform->Delete();
      }
    else
      {
      vtkGeneralTransform *transform = vtkGeneralTransform::New();
      transform->PostMultiply();
      for (i = 0; i < n; i++)
        {
        vtkAbstractTransform *abstractTransform =
          (vtkAbstractTransform *)this->Transforms->GetItemAsObject(i);
        vtkLinearTransform *linearTransform =
          vtkLinearTransform::SafeDownCast(abstractTransform);
        if (linearTransform)
          {
          transform->Concatenate(linearTransform->GetMatrix());
          }
        else
          {
          transform->Concatenate(abstractTransform);
          }
        }
      }
    }

  return 1;
}

//-------------------------------------------------------------------------
int vtkDICOMTransformReader::ProcessRequest(vtkInformation *request,
                                    vtkInformationVector **inputVector,
                                    vtkInformationVector *outputVector)
{
  if (request->Has(vtkDemandDrivenPipeline::REQUEST_DATA()))
    {
    return this->ReadFile();
    }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

//-------------------------------------------------------------------------
void vtkDICOMTransformReader::SetTransform(vtkAbstractTransform *transform)
{
  if (this->Transform != transform)
    {
    if (strcmp(transform->GetClassName(),
               this->Transform->GetClassName()) == 0)
      {
      this->Transform->DeepCopy(transform);
      }
    else
      {
      this->Transform->Delete();
      transform->Register(this);
      this->Transform = transform;
      }
    }
}

//-------------------------------------------------------------------------
vtkAbstractTransform *vtkDICOMTransformReader::GetTransform()
{
  this->Update();

  return this->Transform;
}

//-------------------------------------------------------------------------
int vtkDICOMTransformReader::GetNumberOfTransforms()
{
  this->Update();

  return this->Transforms->GetNumberOfItems();
}

//-------------------------------------------------------------------------
vtkAbstractTransform *vtkDICOMTransformReader::GetNthTransform(int i)
{
  this->Update();

  if (i < 0 || i >= this->Transforms->GetNumberOfItems())
    {
    return 0;
    }

  return static_cast<vtkAbstractTransform *>(
    this->Transforms->GetItemAsObject(i));
}

//----------------------------------------------------------------------------
void vtkDICOMTransformReader::RelayError(
  vtkObject *o, unsigned long e, void *data)
{
  if (e == vtkCommand::ErrorEvent)
    {
    vtkDICOMParser *parser = vtkDICOMParser::SafeDownCast(o);
    if (parser)
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
