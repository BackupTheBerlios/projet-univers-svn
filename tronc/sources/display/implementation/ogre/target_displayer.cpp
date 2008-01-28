/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <Ogre.h>
#include <kernel/string.h>
#include <kernel/log.h>
#include <model/detection_data.h>
#include <model/positionned.h>
#include <display/implementation/display_hud.h>
#include <display/implementation/ogre/solid.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/observer.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/target_displayer.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// This view will be automatically maintained.
        RegisterView(Ogre::TargetDisplayer,
                     Model::TargetDisplayer,
                     Ogre::RealWorldViewPoint) ;

        TargetDisplayer::TargetDisplayer(Model::TargetDisplayer* i_object,
                                         RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::TargetDisplayer,
                            RealWorldViewPoint>(i_object,i_viewpoint),
          m_container(NULL),
          m_reticule(NULL),
          m_is_reticule_active(false)
        {}

        void TargetDisplayer::onInit()
        {
          InternalMessage("Display","Entering TargetDisplayer::onInit") ;

          registerHUDSystem(this) ;

          m_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", "container")) ;
          getOverlay()->add2D(m_container) ;
          
          m_container->setPosition(0,0) ;
          m_container->setWidth(1) ;
          m_container->setHeight(1) ;
                                      
          m_reticule = 
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", "reticule") ;
          m_reticule->setMaterialName("PU/material/reticule") ;
          m_reticule->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
          m_reticule->setVerticalAlignment(::Ogre::GVA_CENTER) ;
          updateHUD() ;
          getOverlay()->setZOrder(500) ;
          getOverlay()->show() ;
          

          InternalMessage("Display","Leaving TargetDisplayer::onInit") ;
        }
        
        void TargetDisplayer::onClose()
        {
          if (m_container)
          {
            getOverlay()->remove2D(m_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_container) ;

            unRegisterHUDSystem(this) ;

          }
        }
      
        void TargetDisplayer::updateHUD()
        {
          InternalMessage("Display","Entering TargetDisplayer::updateHUD") ;
          /*!
            temporary code for test
            
            get the target position and projectit on the screen

          */
          Kernel::Object* target = getTrait()->getTarget() ;
          if (target)
          {
            // update reticule state if needed
            if (!m_is_reticule_active)
            {
              m_container->addChild(m_reticule) ;
              m_is_reticule_active = true ;
            }

            Model::DetectionData* 
              detection_data = target->getTrait<Model::DetectionData>() ;
            
            Kernel::Object* detected_object 
              = detection_data?detection_data->getDetectedObject():NULL ;
            
            InternalMessage(
              "Display","TargetDisplayer::updateHUD values are "
              + Kernel::toString((int)detection_data)
              + " " 
              + Kernel::toString((int)detected_object)
              ) ;
            
            if (detection_data && detected_object)
            {
              InternalMessage("Display","TargetDisplayer::updateHUD calculating reticule position") ;
              // update reticule position
              ::Ogre::Entity* entity 
                = detected_object->getTrait<Model::Solid>()
                  ->getView<Solid>(getViewPoint())->getEntity() ;
                  
              ::Ogre::Vector3 position 
                = detected_object->getTrait<Model::Positionned>()
                  ->getView<Positionned>(getViewPoint())->getNode()->getWorldPosition() ;
              
              Observer* observer = getViewPoint()->getObserver()
                                   ->getView<Observer>(getViewPoint()) ;

              InternalMessage("Display","TargetDisplayer::updateHUD detected object name ="
                              + detected_object->getName()
                              + " position="
                              + Kernel::toString(position.x)
                              +","
                              + Kernel::toString(position.y)
                              +","
                              + Kernel::toString(position.z)
                              ) ;
                                   
              ::Ogre::Vector3 eye_position = observer->getCamera()
                                             ->getViewMatrix(true) * position ;

              InternalMessage("Display","TargetDisplayer::updateHUD eye position="
                              + Kernel::toString(eye_position.x)
                              +","
                              + Kernel::toString(eye_position.y)
                              +","
                              + Kernel::toString(eye_position.z)
                              ) ;
  
              InternalMessage("Display","TargetDisplayer::updateHUD calculating reticule size") ;
              
              // update reticule size
              if (eye_position.z < 0)
              {
                InternalMessage("Display","TargetDisplayer::updateHUD object is visible") ;
                
                ::Ogre::Vector3 screen_position 
                  = observer->getCamera()->getProjectionMatrix() * eye_position ;
                
                InternalMessage(
                  "Display","TargetDisplayer::updateHUD setting position to x="
                  + Kernel::toString(screen_position.x)
                  + " y=" 
                  + Kernel::toString(screen_position.y)
                  + " z=" 
                  + Kernel::toString(screen_position.z)
                  ) ;
                
                /* 
                  screen_position is in [-1,1]
                  but actual screen values are between [-0.5,0.5]
                  do not why we need to invert y
                */
                m_container->setPosition(screen_position.x/2,-screen_position.y/2) ;
                
                // calculate projected size
                ::Ogre::Real radius = entity->getBoundingRadius() ; 

                InternalMessage(
                  "Display","TargetDisplayer::updateHUD radius="
                  + Kernel::toString(radius)
                  ) ;

                ::Ogre::Vector3 spheresize(radius,radius,eye_position.z) ;
                spheresize = observer->getCamera()->getProjectionMatrix() * spheresize ;

                InternalMessage(
                  "Display","TargetDisplayer::updateHUD dimension x="
                  + Kernel::toString(spheresize.x)
                  + " y=" 
                  + Kernel::toString(spheresize.y)
                  ) ;
                
                m_reticule->setLeft(-spheresize.x/2) ;
                m_reticule->setTop(-spheresize.y/2) ;
                m_reticule->setDimensions(spheresize.x,spheresize.y) ;
              }
            }          
          }
          else if (m_container && m_reticule && m_is_reticule_active)
          {
            // no target remove the reticule...
            m_container->_removeChild(m_reticule) ;
            m_is_reticule_active = false ;
          }
          InternalMessage("Display","Leaving TargetDisplayer::updateHUD") ;
        }


      }
    }
  }
}
