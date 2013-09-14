// Test the vtkNIFTIReader by displaying an image.

#include "vtkNIFTIReader.h"

#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkImageData.h"
#include "vtkImageSliceMapper.h"
#include "vtkImageProperty.h"
#include "vtkImageSlice.h"
#include "vtkImageReader2.h"
#include "vtkSmartPointer.h"
#include "vtkStringArray.h"

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

  const char *filename = 0;
  if (argc > 1)
    {
    filename = argv[1];
    }

  vtkSmartPointer<vtkNIFTIReader> reader =
    vtkSmartPointer<vtkNIFTIReader>::New();
  reader->SetFileName(filename);

  double range[2];
  int extent[6];
  reader->Update();
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
    if (imageMapper->GetOrientation() == 2)
      {
      point[imageMapper->GetOrientation()] -= 500.0;
      camera->SetViewUp(0.0, +1.0, 0.0);
      }
    else
      {
      point[imageMapper->GetOrientation()] += 500.0;
      camera->SetViewUp(0.0, 0.0, +1.0);
      }
    camera->SetPosition(point);
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
