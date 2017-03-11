/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMMetaData.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationDataObjectKey.h"
#include "vtkInformationDoubleVectorKey.h"
#include "vtkImageData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkMatrix4x4.h"
#include "vtkAlgorithmOutput.h"
#include "vtkTrivialProducer.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"

vtkStandardNewMacro(vtkDICOMAlgorithm);

vtkInformationKeyMacro(vtkDICOMAlgorithm, PATIENT_MATRIX, DoubleVector);
vtkInformationKeyMacro(vtkDICOMAlgorithm, META_DATA, DataObject);

//----------------------------------------------------------------------------
vtkDICOMAlgorithm::vtkDICOMAlgorithm()
{
}

//----------------------------------------------------------------------------
vtkDICOMAlgorithm::~vtkDICOMAlgorithm()
{
}

//----------------------------------------------------------------------------
void vtkDICOMAlgorithm::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
vtkInformation *vtkDICOMAlgorithm::GetMetaDataInformation(
  vtkInformationVector** inputVector, int inputPort, int inputConnection)
{
  vtkInformation *inInfo =
    inputVector[inputPort]->GetInformationObject(inputConnection);

  // If SetInputConnection was used, meta data is attached to inInfo
  vtkInformation *metaInfo = inInfo;

  // If SetInputData was used, the meta data is attached to the data
  vtkAlgorithmOutput *sourceConnection = this->GetInputConnection(0, 0);
  if (sourceConnection)
  {
    // SetInputData causes a vtkTrivialProducer to be used
    vtkAlgorithm *producer = sourceConnection->GetProducer();
    if (producer && vtkTrivialProducer::SafeDownCast(producer))
    {
      vtkDataObject *inputData = producer->GetOutputDataObject(0);
      if (inputData)
      {
        metaInfo = inputData->GetInformation();
      }
    }
  }

  return metaInfo;
}

//----------------------------------------------------------------------------
void vtkDICOMAlgorithm::CopyMetaDataToOutputInformation(
  vtkInformationVector** inputVector, int inputPort, int inputConnection,
  vtkInformationVector* outputVector, int outputPort)
{
  // If SetInputConnection was used, meta data is attached to inInfo
  vtkInformation *metaInfo = this->GetMetaDataInformation(
    inputVector, inputPort, inputConnection);

  // Set the output port to copy the meta data to
  int firstPort = outputPort;
  int lastPort = outputPort;
  if (outputPort < 0)
  {
    firstPort = 0;
    lastPort = this->GetNumberOfOutputPorts() - 1;
  }

  // Copy the meta data downstream
  for (int port = firstPort; port <= lastPort; port++)
  {
    vtkInformation *outInfo = outputVector->GetInformationObject(port);
    // Matrix is stored as a vector of 16 doubles
    outInfo->CopyEntry(metaInfo, PATIENT_MATRIX());

    // MetaData object must be shallow-copied
    vtkDICOMMetaData *meta = vtkDICOMMetaData::SafeDownCast(
      metaInfo->Get(META_DATA()));
    if (meta)
    {
      vtkSmartPointer<vtkDICOMMetaData> outMeta =
        vtkSmartPointer<vtkDICOMMetaData>::New();
      outMeta->ShallowCopy(meta);
      outInfo->Set(META_DATA(), outMeta);
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMAlgorithm::CopyMetaDataToOutputData(
  vtkInformation *info, vtkDataObject *data)
{
  vtkInformation *dataInfo = data->GetInformation();
  dataInfo->CopyEntry(info, META_DATA());
  dataInfo->CopyEntry(info, PATIENT_MATRIX());
}

//----------------------------------------------------------------------------
int vtkDICOMAlgorithm::RequestInformation(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // Copy the meta data to the output information
  if (this->GetNumberOfInputPorts() > 0 &&
      this->GetNumberOfInputConnections(0) > 0)
  {
    this->CopyMetaDataToOutputInformation(
      inputVector, 0, 0, outputVector, -1);
  }

  return this->Superclass::RequestInformation(
    request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkDICOMAlgorithm::RequestData(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // Copy the meta data downstream
  int numPorts = this->GetNumberOfOutputPorts();
  for (int port = 0; port < numPorts; port++)
  {
    vtkInformation *outInfo = outputVector->GetInformationObject(port);
    vtkImageData *outData = vtkImageData::SafeDownCast(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));
    if (outData)
    {
      this->CopyMetaDataToOutputData(outInfo, outData);
    }
  }

  return this->Superclass::RequestData(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
void vtkDICOMAlgorithm::ThreadedRequestData(
  vtkInformation *, vtkInformationVector **, vtkInformationVector *,
  vtkImageData ***, vtkImageData **, int [6], int)
{
  vtkWarningMacro("ThreadedRequestData: This method was not implemented in "
                  << this->GetClassName());
}
