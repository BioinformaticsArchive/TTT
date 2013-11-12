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

/** \addtogroup TTTAdherensJunctionSegmentation
 *  @{
 */

#ifndef ADHERENSJUNCTIONSEGMENTATIONCOMMAND_H_
#define ADHERENSJUNCTIONSEGMENTATIONCOMMAND_H_

#include "AppCommand.h"
#include "tttDescriptionDataTypes.h"
#include "itkPointSet.h"
#include "itkImage.h"
namespace ttt{
/**
 * TODO
 * \class AdherensJunctionSegmentationCommand
 */
class AdherensJunctionSegmentationCommand: public AppCommand {

public:
	/**
	 * TODO
	 */
	typedef itk::PointSet<float,3> PointSetType;
	/**
		 * TODO
		 */
	typedef itk::Image<float,3> PlatenessImageType;
private:
	/**
	 * TODO
	 */
	PointSetType::Pointer m_Locations;
	/**
	 * TODO
	 */
	PlatenessImageType::Pointer m_Plateness;
	/**
	 * TODO
	 */
	ttt::TissueDescriptor::Pointer m_Descriptor;
public:
	/**
	 * TODO
	 */
	AdherensJunctionSegmentationCommand(){
		m_Descriptor=ttt::TissueDescriptor::New();
	}
	/**
	 * TODO
	 */
	virtual ~AdherensJunctionSegmentationCommand(){

	}
	/**
	 * TODO
	 */
	virtual void Do(){
		InitDefGraph();
		DoPrimalComputation();
	}

	/**
	 * TODO
	 * @param locations
	 */
	inline void SetVertexLocations(const PointSetType::Pointer & locations){
		m_Locations=locations;
	}
	/**
	 * TODO
	 * @param plateness
	 */
	inline void SetPlatenessImage(const PlatenessImageType::Pointer & plateness){
		m_Plateness=plateness;
	}
	/**
	 * TODO
	 * @return
	 */
	inline ttt::TissueDescriptor::Pointer GetTissueDescriptor(){
		return m_Descriptor;
	}
private:
	/**
	 * TODO
	 */
	void InitDefGraph();
	/**
	 * TODO
	 */
	void DoPrimalComputation();
	/**
	 * TODO
	 * @param l1posA
	 * @param l1posB
	 * @param l2posA
	 * @param l2posB
	 * @return
	 */
	bool IntersectLine(itk::Point<float ,3> l1posA, itk::Point<float, 3> l1posB, itk::Point<float, 3> l2posA, itk::Point<float, 3> l2posB );
	/**
	 * TODO
	 */
	double angleBetween2Lines(itk::Point<double,3> srcpt, std::vector<itk::Point<double,3> > linepts);
	/**
	 * TODO
	 */
	double distitkpt(itk::Point<float,3> pta, itk::Point<float,3> ptb);
};
}

#endif /* VINODTHSEGMENTATIONCOMMAND_H_ */
/** @}*/
