#include <itkImageToVTKImageFilter.h>
#include <vtkSmartPointer.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>

#include "VertexnessImageDrawer.h"

ttt::VertexnessImageDrawer::VertexnessImageDrawer(){
    m_VolumeProperty =vtkSmartPointer<vtkVolumeProperty>::New();
    m_VolumeProperty->ShadeOff();
    m_VolumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);

     vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();

     compositeOpacity->AddPoint(0.0,0.0);
     compositeOpacity->AddPoint(0.1,1.0);
     compositeOpacity->AddPoint(1.0,0.0);

     m_VolumeProperty->SetScalarOpacity(compositeOpacity); // composite first.

     vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
     color->AddRGBPoint(0.0,1.0,0.0,0.0);
     color->AddRGBPoint(1.0,0.0,0.0,1.0);

     m_VolumeProperty->SetColor(color);
}



vtkSmartPointer<vtkVolumeProperty> ttt::VertexnessImageDrawer::GetVolumeProperty() {
	return m_VolumeProperty;
}

