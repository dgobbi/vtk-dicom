// Test the vtkDICOMReader by displaying an image.

#include "vtkDICOMMetaData.h"
#include "vtkDICOMDirectory.h"
#include "vtkDICOMReader.h"
#include "vtkDICOMCTRectifier.h"
#include "vtkDICOMApplyPalette.h"

#include "vtkCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkImageMapToColors.h"
#include "vtkImageData.h"
#include "vtkImageReslice.h"
#include "vtkImageResliceMapper.h"
#include "vtkImageProperty.h"
#include "vtkImageSlice.h"
#include "vtkImageStack.h"
#include "vtkImageReader2.h"
#include "vtkLookupTable.h"
#include "vtkSmartPointer.h"
#include "vtkStringArray.h"
#include "vtkIntArray.h"
#include "vtkMatrix4x4.h"
#include "vtkMath.h"
#include "vtkErrorCode.h"

class vtkDICOMPrinter : public vtkCommand
{
public:
  static vtkDICOMPrinter *New() { return new vtkDICOMPrinter; }
  vtkTypeMacro(vtkDICOMPrinter,vtkCommand);
#ifdef VTK_OVERRIDE
  void Execute(vtkObject *caller, unsigned long eventId, void *callData)
    VTK_OVERRIDE;
#else
  void Execute(vtkObject *caller, unsigned long eventId, void *callData);
#endif
protected:
  vtkDICOMPrinter() {};
  vtkDICOMPrinter(const vtkDICOMPrinter& c) : vtkCommand(c) {}
  void operator=(const vtkDICOMPrinter&) {}
};

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  style->SetInteractionModeToImageSlicing();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  iren->SetRenderWindow(renWin);
  iren->SetInteractorStyle(style);

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

  // find all DICOM files supplied by the user
  vtkSmartPointer<vtkDICOMDirectory> sorter =
    vtkSmartPointer<vtkDICOMDirectory>::New();
  sorter->RequirePixelDataOn();
  sorter->SetScanDepth(1);
  sorter->SetInputFileNames(files);
  sorter->Update();

  // find the series with the largest number of files
  int m = sorter->GetNumberOfStudies();
  int seriesIdx = 0;
  int kmax = 0;
  for (int i = 0; i < m; i++)
  {
    int fj = sorter->GetFirstSeriesForStudy(i);
    int lj = sorter->GetLastSeriesForStudy(i);
    for (int j = fj; j <= lj; j++)
    {
      int k = sorter->GetFileNamesForSeries(j)->GetNumberOfValues();
      if (k > kmax)
      {
        kmax = k;
        seriesIdx = j;
      }
    }
  }

  // exit if no files found
  if (kmax == 0)
  {
    fprintf(stderr, "No PixelData to display!\n");
    return 1;
  }

  // display the longest series
  vtkStringArray *a = sorter->GetFileNamesForSeries(seriesIdx);
  vtkSmartPointer<vtkImageReslice> reslice =
    vtkSmartPointer<vtkImageReslice>::New();
  vtkSmartPointer<vtkDICOMReader> reader =
    vtkSmartPointer<vtkDICOMReader>::New();
  reader->SetMemoryRowOrderToFileNative();
  if (stackID)
  {
    reader->SetDesiredStackID(stackID);
  }
  reader->SetFileNames(a);

  // update the meta data
  reader->UpdateInformation();
  vtkDICOMMetaData *meta = reader->GetMetaData();

  // check whether data has a palette
  bool hasPalette = false;
  if (meta->Get(DC::PhotometricInterpretation).Matches("PALETTE?COLOR") ||
      meta->Get(DC::PixelPresentation).Matches("COLOR") ||
      meta->Get(DC::PixelPresentation).Matches("MIXED") ||
      meta->Get(DC::PixelPresentation).Matches("TRUE_COLOR"))
  {
    hasPalette = true;
    // palette maps stored values, not slope/intercept rescaled values
    reader->AutoRescaleOff();
  }

  // update the data
  reader->Update();

  if (reader->GetErrorCode() != vtkErrorCode::NoError)
  {
    return 1;
  }

  // get the scalar range
  double range[2];
  reader->GetOutput()->GetScalarRange(range);

  // get the extent
  int extent[6];
  reader->GetOutput()->GetExtent(extent);

  // get the output port to connect to the display pipeline
  vtkAlgorithmOutput *portToDisplay = reader->GetOutputPort();

  // apply a palette if the image has one
  vtkSmartPointer<vtkDICOMApplyPalette> palette;
  if (hasPalette)
  {
    palette = vtkSmartPointer<vtkDICOMApplyPalette>::New();
    palette->SetInputConnection(reader->GetOutputPort());
    palette->Update();
    palette->GetOutput()->GetScalarRange(range);
    portToDisplay = palette->GetOutputPort();
  }

  // lookup table for the overlay
  vtkSmartPointer<vtkLookupTable> table =
    vtkSmartPointer<vtkLookupTable>::New();
  table->SetNumberOfColors(256);
  table->SetRange(0.0, 255.0);
  table->Build();
  table->SetTableValue(0, 0.0, 0.0, 0.0, 0.0);
  // first overlay is yellow
  table->SetTableValue(1, 1.0, 1.0, 0.0, 1.0);
  // second overlay is cyan
  for (int c = 2; c < 4; c++)
  {
    table->SetTableValue(c, 0.0, 1.0, 1.0, 1.0);
  }
  // third overlay is magenta
  for (int c = 4; c < 8; c++)
  {
    table->SetTableValue(c, 1.0, 0.0, 1.0, 1.0);
  }
  // all other overlays are red
  for (int c = 8; c < 256; c++)
  {
    table->SetTableValue(c, 1.0, 0.0, 0.0, 1.0);
  }

  // convert overlay to RGBA prior to display
  vtkSmartPointer<vtkImageMapToColors> colorOverlay =
    vtkSmartPointer<vtkImageMapToColors>::New();
  colorOverlay->SetLookupTable(table);
  colorOverlay->SetInputConnection(reader->GetOverlayOutputPort());
  colorOverlay->SetOutputFormatToRGBA();

  // check if image is 3D
  bool imageIs3D = (extent[5] > extent[4]);

  // use multiple viewports if image is 3D
  static double viewport[3][4] = {
    { 0.67, 0.0, 1.0, 0.5 },
    { 0.67, 0.5, 1.0, 1.0 },
    { 0.0, 0.0, 0.67, 1.0 },
  };

  for (int i = 2*(imageIs3D == 0); i < 3; i++)
  {
    // mapper for the image
    vtkSmartPointer<vtkImageResliceMapper> imageMapper =
      vtkSmartPointer<vtkImageResliceMapper>::New();
    imageMapper->SetInputConnection(portToDisplay);
    imageMapper->SliceFacesCameraOn();
    imageMapper->SliceAtFocalPointOn();
    imageMapper->ResampleToScreenPixelsOn();

    vtkSmartPointer<vtkImageSlice> image =
      vtkSmartPointer<vtkImageSlice>::New();
    image->SetMapper(imageMapper);

    image->GetProperty()->SetColorWindow(range[1] - range[0]);
    image->GetProperty()->SetColorLevel(0.5*(range[0] + range[1]));
    image->GetProperty()->SetInterpolationTypeToNearest();
    image->GetProperty()->SetLayerNumber(1);

    // mapper for the overlay
    vtkSmartPointer<vtkImageResliceMapper> overlayMapper =
      vtkSmartPointer<vtkImageResliceMapper>::New();
    overlayMapper->SetInputConnection(colorOverlay->GetOutputPort());
    overlayMapper->SliceFacesCameraOn();
    overlayMapper->SliceAtFocalPointOn();
    overlayMapper->ResampleToScreenPixelsOn();

    vtkSmartPointer<vtkImageSlice> overlay =
      vtkSmartPointer<vtkImageSlice>::New();
    overlay->SetMapper(overlayMapper);
    overlay->GetProperty()->SetInterpolationTypeToNearest();
    overlay->GetProperty()->SetLayerNumber(2);

    // combine the image and the overlay
    vtkSmartPointer<vtkImageStack> imageStack =
      vtkSmartPointer<vtkImageStack>::New();
    imageStack->AddImage(image);
    imageStack->AddImage(overlay);

    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddViewProp(imageStack);
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
    point[i % 3] -= 500.0;
    camera->SetPosition(point);
    if ((i % 3) == 2)
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

  // the preferred display size
  int xsize = extent[1] - extent[0] + 1;
  int ysize = extent[3] - extent[2] + 1;
  if (ysize < 400)
  {
    xsize *= 2;
    ysize *= 2;
  }
  if (ysize > 800)
  {
    xsize = xsize*800/ysize;
    ysize = 800;
  }
  if (xsize > 800)
  {
    xsize = 800;
  }

  if (imageIs3D)
  {
    renWin->SetSize(xsize + xsize/2, ysize);
  }
  else
  {
    renWin->SetSize(xsize, ysize);
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
