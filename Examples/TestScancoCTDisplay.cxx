// Test the vtkScancoCTReader by displaying an image.

#include "vtkScancoCTReader.h"

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
#include "vtkErrorCode.h"

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

  const char *filename = nullptr;
  if (argc > 1)
  {
    filename = argv[1];
  }

  vtkSmartPointer<vtkScancoCTReader> reader =
    vtkSmartPointer<vtkScancoCTReader>::New();
  reader->SetFileName(filename);
  reader->Update();

  if (reader->GetErrorCode() != vtkErrorCode::NoError)
  {
    return 1;
  }

  double range[2];
  int extent[6];
  reader->GetOutput()->GetScalarRange(range);
  reader->GetOutput()->GetExtent(extent);

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
      imageMapper->SetInputConnection(reader->GetOutputPort());
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
    if ((i % 3) == 0)
    {
      point[i % 3] -= 500.0;
    }
    else
    {
      point[i % 3] += 500.0;
    }
    camera->SetPosition(point);
    if ((i % 3) == 2)
    {
      camera->SetViewUp(0.0, +1.0, 0.0);
    }
    else
    {
      camera->SetViewUp(0.0, 0.0, -1.0);
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
