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
#include <kernel/parameters.h>
#include <model/positionned.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/head_up_display/ideal_target.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        namespace HeadUpDisplay {

          RegisterView(IdealTarget, 
                       Implementation::IdealTarget, 
                       TargetDisplayerViewPoint) ;
          
          IdealTarget::IdealTarget(
              Implementation::IdealTarget* object,
              TargetDisplayerViewPoint* viewpoint)
          : Kernel::TraitView<Implementation::IdealTarget,TargetDisplayerViewPoint>(object,viewpoint),
            m_reticule_is_shown(false)
          {}

          namespace 
          {
            float target_size = 0 ;
            std::string target_material ;
          }
          
          float getTargetSize()
          {
            if (target_size == 0 )
            {            
              try
              {
                target_size = Kernel::Parameters::getValue<float>("Display","TargetSize") ;
              }
              catch(...)
              {
                InternalMessage("Display","getTargetSize : error") ;
                target_size = 0.05 ;
              }
            }
            return target_size ;
          }
          
          std::string getTargetMaterial()
          {
            if (target_material == "")
            {
              try
              {
                target_material = Kernel::Parameters::getValue<std::string>("Display","TargetMaterial") ;
              }
              catch(...)
              {
                InternalMessage("Display","getTargetMaterial : error") ;
                target_material = "PU/material/target" ;
              }
            }
            return target_material ;
          }

          void IdealTarget::setColour(const ::Ogre::ColourValue& colour)
          {
            Utility::setColour(m_reticule,colour) ;
          }
          
          void IdealTarget::onInit()
          {
            InternalMessage("Display","Entering IdealTarget::onInit") ;
            
            getOverlay()->setZOrder(500) ;
            m_reticule_container = static_cast< ::Ogre::OverlayContainer* >(
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName())) ;
            getOverlay()->add2D(m_reticule_container) ;
            
            m_reticule_container->setPosition(0,0) ;
            m_reticule_container->setWidth(1) ;
            m_reticule_container->setHeight(1) ;

            m_reticule = 
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName()) ;

            // clone material because we will modify it 
            ::Ogre::MaterialPtr material = ::Ogre::MaterialManager::getSingleton().getByName(getTargetMaterial()); 
            material = material->clone(Utility::getUniqueName()) ;
            m_reticule->setMaterialName(material->getName()) ; 

            m_reticule->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
            m_reticule->setVerticalAlignment(::Ogre::GVA_CENTER) ;
            
            const float size = getTargetSize() ;
            
            m_reticule->setLeft(-size/2) ;
            m_reticule->setTop(-size/2) ;
            m_reticule->setDimensions(size,size) ;
            
            m_reticule_container->_addChild(m_reticule) ;
            
            getOverlay()->show() ;
            onUpdate() ;
  
            InternalMessage("Display","Leaving IdealTarget::onInit") ;
          }
          
          void IdealTarget::onClose()
          {
            if (m_reticule_container)
            {
              getOverlay()->remove2D(m_reticule_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule_container) ;
            }
          }
          
          void IdealTarget::onUpdate()
          {
            
            InternalMessage("Display","IdealTarget::onUpdate calculating reticule position") ;

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

              /*!
                it seems that x,y can get out of [-1,1]
                it means that it is out of the screen
                we can print it when 
                x,y in -1/1  
                
              */
              if (fabs(screen_position.x) <= 1 &&
                  fabs(screen_position.y) <= 1)
              {
                /* 
                  screen_position is in [-1,1]
                  but actual screen values are between [-0.5,0.5]
                  do not know why we need to invert y
                */
                m_reticule_container->setPosition(screen_position.x/2,-screen_position.y/2) ;
                
                if (!m_reticule_is_shown)
                {
                  m_reticule_container->show() ;
                  m_reticule_is_shown = true ;
                }
              }
              else
              {
                if (m_reticule_is_shown)
                {
                  m_reticule_container->hide() ;
                  m_reticule_is_shown = false ;
                }
              }
            }
            else
            {
              if (m_reticule_is_shown)
              {
                m_reticule_container->hide() ;
                m_reticule_is_shown = false ;
              }
            }
          }
          

        }
      }
    }
  }
}
