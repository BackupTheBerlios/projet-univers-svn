/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <model/implementation/detector_view_point.h>
#include <model/implementation/detector_object_view.h>

#include <model/positionned.h>
#include <model/detector.h>

namespace ProjetUnivers {
  namespace Model {

    Detector::Detector(Kernel::Object* computer)
    : m_implementation(),
      m_range(Distance::_Meter,1000),
      m_computer(computer)
    {}
    
    Detector::Detector(Kernel::Object* computer,const Distance& range)
    : m_implementation(),
      m_range(range),
      m_computer(computer)
    {}
    
    void Detector::detect()
    {
      InternalMessage("Model::Detector::detect entering") ;
      // perform detection pass on implementation
      Kernel::forAll<Implementation::DetectorObjectView>(
        m_implementation.get(),&Implementation::DetectorObjectView::check) ;
      InternalMessage("Model::Detector::detect leaving") ;
    }
    
    void Detector::init()
    {
      if (! m_implementation.get())
      {
        m_implementation.reset(new Implementation::DetectorViewPoint(this)) ;
        m_implementation->init() ;
      }
    }
    
    Distance Detector::getRange() const
    {
      // temp
      return m_range ;
    }
    
    bool Detector::canDetect(const Kernel::Object* object) const
    {
      // we do not detect parent objects :
      if (object->isAncestor(getObject()))
      {
        InternalMessage("Model::Detector::canDetect does not detect parent") ;
        return false ;
      }
      
      // range check 
      Position position = getRelativePosition(object,getObject()) ;
      bool in_range = position.calculateDistance(Position()) <=  getRange() ; 

      InternalMessage("Model::Detector::canDetect range test") ;
      // @todo add structure checks

      return in_range ;      
    }
    
    Kernel::Object* Detector::getComputer() const
    {
      return m_computer ;
    }    

  }     
}
