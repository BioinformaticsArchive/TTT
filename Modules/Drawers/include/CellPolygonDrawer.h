//    This file is part of TTT Tissue Tracker.
//
//    TTT Tissue Tracker is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    TTT Tissue Tracker is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with TTT Tissue Tracker.  If not, see <http://www.gnu.org/licenses/>.

/** \addtogroup TTTDrawer
 *  @{
 */
#ifndef TRACKINGDRAWER_H_
#define TRACKINGDRAWER_H_
#include <vtkPolygon.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <map>
#include "tttDescriptionDataTypes.h"
#include "Drawer.h"


namespace ttt{
template<class TissueDescriptor> class CellPolygonDrawer: public Drawer {

	typedef typename TissueDescriptor::DualGraphType CellGraph;
	typedef  typename ttt::TissueDescriptorTraits< TissueDescriptor >::CellVertexType CellVertexType;
	std::map<CellVertexType, vtkSmartPointer<vtkActor> > m_Actors;
	//typename ttt::TissueDescriptorTraits< TissueDescriptor >::CellVertexType vertex;
public:
	CellPolygonDrawer(){

	}
	virtual ~CellPolygonDrawer(){

	}

	inline void SetTissueDescriptor(const typename TissueDescriptor::Pointer & descriptor){
		m_Descriptor=descriptor;
	}

	virtual void Reset(){
		for(typename std::map<CellVertexType, vtkSmartPointer<vtkActor> >::iterator it= m_Actors.begin();it!=m_Actors.end();it++){
			m_Renderer->RemoveActor(it->second);
		}
		m_Actors.clear();
	}
	virtual void Draw(){
		this->Reset();
		BGL_FORALL_VERTICES_T(v,m_Descriptor->GetCellGraph(),CellGraph){
				vtkSmartPointer<vtkPoints> points =  vtkSmartPointer<vtkPoints>::New();
				int npoints=0;
				for( typename ttt::Cell<TissueDescriptor::NumDimensions>::PerimeterIterator it=boost::get(typename ttt::TissueDescriptorTraits<TissueDescriptor>::CellPropertyTagType(),m_Descriptor->GetCellGraph(),v).PerimeterBegin();
						it!= boost::get(typename ttt::TissueDescriptorTraits<TissueDescriptor>::CellPropertyTagType(),m_Descriptor->GetCellGraph(),v).PerimeterEnd();
						++it){

						points->InsertNextPoint(boost::get(typename ttt::TissueDescriptorTraits<TissueDescriptor>::SkeletonPointPropertyTagType(),m_Descriptor->GetAJGraph(),*it).position[0],
												boost::get(typename ttt::TissueDescriptorTraits<TissueDescriptor>::SkeletonPointPropertyTagType(),m_Descriptor->GetAJGraph(),*it).position[1],
												boost::get(typename ttt::TissueDescriptorTraits<TissueDescriptor>::SkeletonPointPropertyTagType(),m_Descriptor->GetAJGraph(),*it).position[2]);

						npoints++;
				}
				vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
				polygon->GetPointIds()->SetNumberOfIds(npoints); //make a quad
				for(int i=0;i<npoints;i++){
					  polygon->GetPointIds()->SetId(i, i);
				}
			  // Add the polygon to a list of polygons
				  vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();
				  polygons->InsertNextCell(polygon);

				  // Create a PolyData
				  vtkSmartPointer<vtkPolyData> polygonPolyData =  vtkSmartPointer<vtkPolyData>::New();
				  polygonPolyData->SetPoints(points);
				  polygonPolyData->SetPolys(polygons);

				  // Create a mapper and actor
				  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

				  mapper->SetInputData(polygonPolyData);

				  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

				  actor->SetMapper(mapper);
				  int trackID=boost::get(typename ttt::TissueDescriptorTraits<TissueDescriptor>::CellPropertyTagType(),m_Descriptor->GetCellGraph(),v).GetID();

				  std::vector<double> color;
				  if(m_TrackID2Color.count(trackID)){
					  color=m_TrackID2Color[trackID];
				  }else{
					  int parentID=boost::get(typename ttt::TissueDescriptorTraits<TissueDescriptor>::CellPropertyTagType(),m_Descriptor->GetCellGraph(),v).GetParentID();
					  if(parentID!=-1){
						  color=m_TrackID2Color[parentID];

					  }else{
						  //color=generator.generateRandomColor(rand());
						  color.push_back(rand() );
						  color.push_back(rand() );
						  color.push_back(rand() );
					  }
					  m_TrackID2Color[trackID]=color;
				  }
				  std::cout << trackID << "->" << color[0] << " " <<color[1] << " " << color[2] << std::endl;
				  actor->GetProperty()->SetColor(color[0]/RAND_MAX,color[1]/RAND_MAX,color[2]/RAND_MAX);
				  m_Renderer->AddActor(actor);
				  m_Actors[v]=actor;

			}
	}

	static CellPolygonDrawer * New(){
		return new CellPolygonDrawer;
	}

	virtual void Show(){
		for(typename std::map<CellVertexType, vtkSmartPointer<vtkActor> >::iterator it= m_Actors.begin();it!=m_Actors.end();it++){
			it->second->VisibilityOn();
		}

	}
	virtual void Hide(){
		for(typename std::map<CellVertexType, vtkSmartPointer<vtkActor> >::iterator it= m_Actors.begin();it!=m_Actors.end();it++){
			it->second->VisibilityOff();
		}
	}
private:
	typedef std::vector<double> Color ;

	std::map<int,Color> m_TrackID2Color;
	typename TissueDescriptor::Pointer m_Descriptor;

};


}
#endif /* TRACKINGDRAWER_H_ */
/** @}*/
