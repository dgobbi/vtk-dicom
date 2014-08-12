// Test the vtkDICOMReader by displaying an image.

#include "vtkDICOMMetaData.h"
#include "vtkDICOMSorter.h"
#include "vtkDICOMReader.h"
#include "vtkDICOMCTRectifier.h"

#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkImageData.h"
#include "vtkImageReslice.h"
#include "vtkImageSliceMapper.h"
#include "vtkImageProperty.h"
#include "vtkImageSlice.h"
#include "vtkImageReader2.h"
#include "vtkSmartPointer.h"
#include "vtkStringArray.h"
#include "vtkIntArray.h"
#include "vtkMatrix4x4.h"
#include "vtkMath.h"

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  style->SetInteractionModeToImage3D();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  iren->SetRenderWindow(renWin);
  iren->SetInteractorStyle(style);

  vtkSmartPointer<vtkDICOMSorter> sorter =
    vtkSmartPointer<vtkDICOMSorter>::New();

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  const char *stackID = 0;

  for (int i = 1; i < argc; i++)
    {
    if (strcmp(argv[i], "--stack") == 0)
      {
      if (i+1 < argc)
        {
        stackID = argv[++i];
        }
      }
    else
      {
      files->InsertNextValue(argv[i]);
      }
    }

  sorter->SetInputFileNames(files);
  sorter->Update();

#if 0
  // find the series with the largest number of files
  int m = sorter->GetNumberOfStudies();
  int studyIdx = 0;
  int seriesIdx = 0;
  int kmax = 0;
  for (int i = 0; i < m; i++)
    {
    int fj = sorter->GetFirstSeriesInStudy(i);
    int lj = fj + sorter->GetNumberOfSeriesInStudy(i);
    for (int j = fj; j < lj; j++)
      {
      int k = sorter->GetFileNamesForSeries(j)->GetNumberOfValues();
      if (k > kmax)
        {
        kmax = k;
        seriesIdx = j;
        studyIdx = i;
        }
      }
    }

  // display the longest series
  //vtkStringArray *a = sorter->GetFileNamesForSeries(seriesIdx);
#endif

  // trust the user and display all the files, even if multiple series
  vtkStringArray *a = sorter->GetOutputFileNames();
  vtkSmartPointer<vtkImageReslice> reslice =
    vtkSmartPointer<vtkImageReslice>::New();
  vtkSmartPointer<vtkDICOMReader> reader =
    vtkSmartPointer<vtkDICOMReader>::New();
  reader->SetMemoryRowOrderToFileNative();
  //reader->TimeAsVectorOn();
  //reader->SetDesiredTimeIndex(5);
  if (stackID)
    {
    reader->SetDesiredStackID(stackID);
    }
  reader->SetFileNames(a);

  double range[2];
  int extent[6];
  reader->Update();
  reader->GetOutput()->GetScalarRange(range);
  reader->GetOutput()->GetExtent(extent);

  // get the output port to connect to the display pipeline
  vtkAlgorithmOutput *portToDisplay = reader->GetOutputPort();

#if 0
  // check if the matrix indicates a tilted CT gantry
  vtkSmartPointer<vtkMatrix4x4> pmat =
    vtkSmartPointer<vtkMatrix4x4>::New();
  pmat->DeepCopy(reader->GetPatientMatrix());
  double xvec[4] = { 1.0, 0.0, 0.0, 0.0 };
  double yvec[4] = { 0.0, 1.0, 0.0, 0.0 };
  double zvec[4] = { 0.0, 0.0, 1.0, 0.0 };
  pmat->MultiplyPoint(xvec, xvec);
  pmat->MultiplyPoint(yvec, yvec);
  pmat->MultiplyPoint(zvec, zvec);

  // create slice normal and compare to zvec
  double normal[3];
  vtkMath::Cross(xvec, yvec, normal);
  double checkvec[3];
  vtkMath::Cross(zvec, normal, checkvec);
  if (vtkMath::Norm(checkvec) > 1e-3)
    {
    // definite gantry tilt, the volume is trapezoid-shaped
    vtkSmartPointer<vtkMatrix4x4> rmat =
      vtkSmartPointer<vtkMatrix4x4>::New();
    rmat->DeepCopy(pmat);
    rmat->SetElement(0, 2, normal[0]);
    rmat->SetElement(1, 2, normal[1]);
    rmat->SetElement(2, 2, normal[2]);
    pmat->Invert();
    vtkMatrix4x4::Multiply4x4(pmat, rmat, rmat);

    // pure shear matrix will have only one element that is different
    // from the identity matrix:
    double shear = rmat->GetElement(1, 2);
    rmat->Identity();
    rmat->SetElement(1, 2, shear);

    double origin[3], spacing[3];
    reader->GetOutput()->GetOrigin(origin);
    reader->GetOutput()->GetSpacing(spacing);
    // adjust the origin to centre the new volume on the old trapezoid
    origin[1] -= shear*0.5*spacing[2]*(extent[5] - extent[4]);

    // use vtkImageReslice to eliminate any shear
    reslice->SetOutputOrigin(origin);
    reslice->SetOutputSpacing(spacing);
    reslice->SetOutputExtent(extent);
    reslice->SetResliceAxes(rmat);
    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetInterpolationModeToLinear();
    reslice->Update();

    // specify the port that the display pipeline will use
    portToDisplay = reslice->GetOutputPort();
    }
#else
  vtkSmartPointer<vtkDICOMCTRectifier> rect =
    vtkSmartPointer<vtkDICOMCTRectifier>::New();
  rect->SetVolumeMatrix(reader->GetPatientMatrix());
  rect->SetInputConnection(reader->GetOutputPort());
  rect->Update();
  portToDisplay = rect->GetOutputPort();
#endif

  static double viewport[3][4] = {
    { 0.67, 0.0, 1.0, 0.5 },
    { 0.67, 0.5, 1.0, 1.0 },
    { 0.0, 0.0, 0.67, 1.0 },
  };

  // check if image is 2D
  bool imageIs3D = (extent[5] > extent[4]);

  for (int i = 2*(imageIs3D == 0); i < 3; i++)
    {
    vtkSmartPointer<vtkImageSliceMapper> imageMapper =
      vtkSmartPointer<vtkImageSliceMapper>::New();
    if (i < 3)
      {
      imageMapper->SetInputConnection(portToDisplay);
      }
    imageMapper->SetOrientation(i % 3);
    imageMapper->SliceAtFocalPointOn();

    vtkSmartPointer<vtkImageSlice> image =
      vtkSmartPointer<vtkImageSlice>::New();
    image->SetMapper(imageMapper);

    image->GetProperty()->SetColorWindow(range[1] - range[0]);
    image->GetProperty()->SetColorLevel(0.5*(range[0] + range[1]));
    image->GetProperty()->SetInterpolationTypeToNearest();

    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddViewProp(image);
    renderer->SetBackground(0.0, 0.0, 0.0);
    if (imageIs3D)
      {
      renderer->SetViewport(viewport[i]);
      }

    renWin->AddRenderer(renderer);

    // use center point to set camera
    double *bounds = imageMapper->GetBounds();
    double point[3];
    point[0] = 0.5*(bounds[0] + bounds[1]);
    point[1] = 0.5*(bounds[2] + bounds[3]);
    point[2] = 0.5*(bounds[4] + bounds[5]);
    double maxdim = 0.0;
    for (int j = 0; j < 3; j++)
      {
      double s = 0.5*(bounds[2*j+1] - bounds[2*j]);
      maxdim = (s > maxdim ? s : maxdim);
      }

    vtkCamera *camera = renderer->GetActiveCamera();
    camera->SetFocalPoint(point);
    point[imageMapper->GetOrientation()] -= 500.0;
    camera->SetPosition(point);
    if (imageMapper->GetOrientation() == 2)
      {
      camera->SetViewUp(0.0, -1.0, 0.0);
      }
    else
      {
      camera->SetViewUp(0.0, 0.0, +1.0);
      }
    camera->ParallelProjectionOn();
    camera->SetParallelScale(maxdim);
    }

  if (imageIs3D)
    {
    renWin->SetSize(600, 400);
    }
  else
    {
    renWin->SetSize(400, 400);
    }

  renWin->Render();

  vtkStringArray *sarray = reader->GetStackIDs();
  if (sarray->GetNumberOfValues())
    {
    cout << "StackIDs (choose one with --stack):";
    for (vtkIdType ii = 0; ii < sarray->GetNumberOfValues(); ii++)
      {
      cout << " \"" << sarray->GetValue(ii) << "\"";
      }
    cout << "\n";
    }
  if (reader->GetTimeDimension() > 1)
    {
    cout << "TimeDimension: " << reader->GetTimeDimension() << "\n";
    cout << "TimeSpacing: " << reader->GetTimeSpacing() << "\n";
    }
  if (reader->GetFileIndexArray()->GetNumberOfComponents() > 1)
    {
    cout << "VectorDimension: "
         << reader->GetFileIndexArray()->GetNumberOfComponents() << "\n";
    }

  iren->Start();

  // code for generating a regression image
  //int retVal = vtkRegressionTestImage( renWin );
  //if ( retVal == vtkRegressionTester::DO_INTERACTOR )
  //  {
  //  iren->Start();
  //  }
  // return !retVal;

  return 0;
}
