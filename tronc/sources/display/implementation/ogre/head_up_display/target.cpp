/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <kernel/trait_view.h>
#include <model/selected.h>
#include <model/positionned.h>
#include <model/solid.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/head_up_display/target.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        namespace HeadUpDisplay {

          RegisterView(Target, 
                       Implementation::Target, 
                       TargetDisplayerViewPoint) ;
          
          Target::Target(
              Implementation::Target* object,
              TargetDisplayerViewPoint* viewpoint)
          : Kernel::TraitView<Implementation::Target,TargetDisplayerViewPoint>(object,viewpoint),
            m_is_shown(false)
          {}
          
          void Target::onInit()
          {
            InternalMessage("Display","Entering Target::onInit") ;
            
            m_container = static_cast< ::Ogre::OverlayContainer* >(
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName())) ;
            getOverlay()->add2D(m_container) ;
            
            m_container->setPosition(0,0) ;
            m_container->setWidth(1) ;
            m_container->setHeight(1) ;
                                        
            m_reticule = 
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName()) ;
            m_reticule->setMaterialName("PU/material/reticule") ;
            m_reticule->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
            m_reticule->setVerticalAlignment(::Ogre::GVA_CENTER) ;
            getOverlay()->setZOrder(500) ;
            m_container->_addChild(m_reticule) ;
            
            getOverlay()->show() ;
            
            if (isSelected())
            {
              onUpdate() ;
            }
  
            InternalMessage("Display","Leaving Target::onInit") ;
          }
          
          void Target::onClose()
          {
            if (m_container)
            {
              getOverlay()->remove2D(m_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_container) ;
            }
          }
          
          void Target::onUpdate()
          {
            if (isSelected())
            {
              InternalMessage("Display","Target::onUpdate calculating reticule position") ;

              ::Ogre::Camera* camera = getViewPoint()->getCamera() ;

              // update reticule position
              Model::Position pos 
                = getObject()->getTrait<Model::Positionned>()
                                             ->getPosition() +
                  Model::getRelativePosition(getViewPoint()->getTargetingSystem(),
                                             getViewPoint()->getObserver()) ;
              
              ::Ogre::Vector3 position = convert(pos) ;

              InternalMessage("Display","Target::onUpdate object position="
                              + Kernel::toString(position.x)
                              +","
                              + Kernel::toString(position.y)
                              +","
                              + Kernel::toString(position.z)
                              ) ;
              
              ::Ogre::Vector3 eye_position = camera->getViewMatrix(true) * position ;

              InternalMessage("Display","Target::updateHUD eye position="
                              + Kernel::toString(eye_position.x)
                              +","
                              + Kernel::toString(eye_position.y)
                              +","
                              + Kernel::toString(eye_position.z)
                              ) ;
  
              InternalMessage("Display","Target::updateHUD calculating reticule size") ;
              
              // update reticule size
              if (eye_position.z < 0)
              {
                InternalMessage("Display","TargetView::updateHUD object is visible") ;
                
                ::Ogre::Vector3 screen_position = camera->getProjectionMatrix()*eye_position ;
                
                InternalMessage(
                  "Display","TargetView::updateHUD setting position to x="
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
                ::Ogre::Real radius = convert(getObject()->getTrait<Model::Solid>()
                                                         ->getBoundingSphereRadius()) ; 

                InternalMessage(
                  "Display","Target::updateHUD radius="
                  + Kernel::toString(radius)
                  ) ;

                ::Ogre::Vector3 spheresize(radius,radius,eye_position.z) ;
                spheresize = camera->getProjectionMatrix() * spheresize ;

                InternalMessage(
                  "Display","Target::updateHUD dimension x="
                  + Kernel::toString(spheresize.x)
                  + " y=" 
                  + Kernel::toString(spheresize.y)
                ) ;
                
                m_reticule->setLeft(-spheresize.x/2) ;
                m_reticule->setTop(-spheresize.y/2) ;
                m_reticule->setDimensions(spheresize.x,spheresize.y) ;
                
                if (!m_is_shown)
                {
                  m_container->show() ;
                  m_is_shown = true ;
                }
              }
              else
              {
                if (m_is_shown)
                {
                  m_container->hide() ;
                  m_is_shown = false ;
                }
              }
            }
            else if (m_is_shown)
            {
              // hide the overlay
              m_container->hide() ;
              m_is_shown = false ;
            }
          }
          
          bool Target::isSelected() const
          {
            return getObject()->getTrait<Model::Selected>()
                              ->isSelected(getViewPoint()->getTargetingSystem()) ;
          }          

        }
      }
    }
  }
}
