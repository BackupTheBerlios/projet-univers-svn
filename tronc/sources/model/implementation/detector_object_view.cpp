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

#include <model/model.h>
#include <model/computer.h>
#include <model/positionned.h>
#include <model/solid.h>
#include <model/mobile.h>
#include <model/detection_data.h>
#include <model/transponder.h>
#include <model/implementation/detector_object_view.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      
      RegisterView(DetectorObjectView,Detectable,DetectorViewPoint) ;
      
      DetectorObjectView::DetectorObjectView(Detectable* object,
                                             DetectorViewPoint* viewpoint)
      : Kernel::TraitView<Detectable,DetectorViewPoint>(object,viewpoint),
        m_detection_information(NULL)
      {}
      
      void DetectorObjectView::check()
      {
        InternalMessage("Model","Model::DetectorObjectView::check entering") ;
        
        Detector* detector = getViewPoint()->getObserver() ;
        if (!detector)
          return ;
        bool in_range = detector ? detector->canDetect(getObject()) : false ;
        
        if (!detector->getComputer())
          return ;        
        
        Computer* computer = detector->getComputer()->getTrait<Computer>() ;
        if (! computer)
          return ;
                  
        if (!in_range && m_detection_information)
        {
          // destroy object
          computer->getMemoryModel()->destroyObject(m_detection_information) ;
          m_detection_information = NULL ;
        }
        else if (in_range)
        {
          InternalMessage(
            "Model",
            "Model::DetectorObjectView::check in range updating detection data") ;
          
          bool mobile = false ;
          
          if (! m_detection_information)
          {
            Solid* solid = getObject()->getTrait<Solid>() ;
            
            // create object 
            m_detection_information = computer->getMemoryModel()->createObject() ;
            computer->getMemoryModel()->addTrait(m_detection_information,
                                                 new DetectionData()) ;
            computer->getMemoryModel()->addTrait(m_detection_information,
                                                 new Positionned()) ;
            computer->getMemoryModel()->addTrait(m_detection_information,
                                                 new Solid(solid->getMesh())) ;
          }
          // update object position
          Position position = getRelativePosition(getObject(),
                                                  computer->getObject()) ;
          
          m_detection_information->getTrait<Positionned>()->setPosition(position) ;
          
          // update speed if exists
          Mobile* mobileTrait = getObject()->getTrait<Mobile>() ;
          
          if (mobileTrait)
          {
            Mobile* data = m_detection_information->getTrait<Mobile>() ;
            if (! data)
            {
              data = new Mobile() ;
              computer->getMemoryModel()->addTrait(m_detection_information,
                                                   data) ;
            }
            data->setSpeed(mobileTrait->getSpeed()) ;
            data->setAngularSpeed(mobileTrait->getAngularSpeed()) ;
          }

          // update identification
          Transponder* identified = 
              getObject()->getTrait<Transponder>() ; 
          
          Transponder* identifedData = 
              m_detection_information->getTrait<Transponder>() ; 
          
          if (identified)
          {
            if (! identifedData)
            {
              // gained identification
              addTrait(m_detection_information,
                       new Transponder(identified->getCode())) ;
            }
            else if (identifedData->getCode() != identified->getCode())
            {
              // changed identification
              identifedData->setCode(identified->getCode()) ;
            }
          }
          else if (identifedData)
          {
            // lost identification
            destroyTrait(m_detection_information,identifedData) ;
          }

        }
        
        InternalMessage("Model","Model::DetectorObjectView::check leaving") ;
      }

      void DetectorObjectView::onClose()
      {
        Kernel::Object* detection_information = m_detection_information ;
        // not detectable anymore
        if (detection_information)
        {
          detection_information->getModel()->destroyObject(detection_information) ;
        }
      }

    }
  }
}

