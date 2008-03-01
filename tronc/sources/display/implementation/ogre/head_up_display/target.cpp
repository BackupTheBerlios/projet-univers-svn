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
            m_reticule_is_shown(false),
            m_arrow_is_shown(false)
          {}

          namespace 
          {
            float arrow_size = 0 ;
            std::string arrow_material ;
            std::string reticule_material ;
          }
          
          float getArrowSize()
          {
            if (arrow_size == 0 )
            {            
              try
              {
                arrow_size = Kernel::Parameters::getValue<float>("Display","ArrowSize") ;
              }
              catch(...)
              {
                InternalMessage("Display","getArrowSize : error") ;
                arrow_size = 0.05 ;
              }
            }
            return arrow_size ;
          }
          
          std::string getReticuleMaterial()
          {
            if (reticule_material == "")
            {
              try
              {
                reticule_material = Kernel::Parameters::getValue<std::string>("Display","ReticuleMaterial") ;
              }
              catch(...)
              {
                InternalMessage("Display","getReticuleMaterial : error") ;
                reticule_material = "PU/material/reticule" ;
              }
            }
            return reticule_material ;
          }

          std::string getArrowMaterial()
          {
            if (arrow_material == "")
            {
              try
              {
                arrow_material = Kernel::Parameters::getValue<std::string>("Display","ArrowMaterial") ;
              }
              catch(...)
              {
                InternalMessage("Display","getArrowMaterial : error") ;
                arrow_material = "PU/material/arrow" ;
              }
            }
            return arrow_material ;
          }
          
          void Target::onInit()
          {
            InternalMessage("Display","Entering Target::onInit") ;
            
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
            m_reticule->setMaterialName(getReticuleMaterial()) ;
            m_reticule->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
            m_reticule->setVerticalAlignment(::Ogre::GVA_CENTER) ;
            m_reticule_container->_addChild(m_reticule) ;

            m_arrow_container = static_cast< ::Ogre::OverlayContainer* >(
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName())) ;
            getOverlay()->add2D(m_arrow_container) ;
            
            m_arrow_container->setPosition(0,0) ;
            m_arrow_container->setWidth(1) ;
            m_arrow_container->setHeight(1) ;

            m_arrow = 
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName()) ;

            ::Ogre::MaterialPtr material = ::Ogre::MaterialManager::getSingleton().getByName(getArrowMaterial()); 
            material = material->clone(Utility::getUniqueName()) ;
            m_arrow->setMaterialName(material->getName()) ; 
            
            m_arrow->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
            m_arrow->setVerticalAlignment(::Ogre::GVA_CENTER) ;
            m_arrow_container->_addChild(m_arrow) ;
            
            m_arrow->setWidth(getArrowSize()) ;
            m_arrow->setHeight(getArrowSize()) ;
            m_arrow->setLeft(-getArrowSize()/2) ;
            m_arrow->setTop(-getArrowSize()/2) ;
            
            m_arrow_container->hide() ;
            
            getOverlay()->show() ;
            
            if (isSelected())
            {
              onUpdate() ;
            }
  
            InternalMessage("Display","Leaving Target::onInit") ;
          }
          
          void Target::onClose()
          {
            if (m_reticule_container)
            {
              getOverlay()->remove2D(m_reticule_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_reticule_container) ;
            }
            if (m_arrow_container)
            {
              getOverlay()->remove2D(m_arrow_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_arrow) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_arrow_container) ;
            }
          }
          
          void Target::onUpdate()
          {
            if (! isSelected()) 
            {
              if (m_reticule_is_shown)
              {
                // hide the overlay
                m_reticule_container->hide() ;
                m_reticule_is_shown = false ;
              }

              if (m_arrow_is_shown)
              {
                // hide the overlay
                m_arrow_container->hide() ;
                m_arrow_is_shown = false ;
              }
              return ;
            }
            
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

              /*!
                it seems that x,y can get out of [-1,1]
                it means that it is out of the screen
                we can print it when 
                x,y in -1/1 + sceen size/2  
                
                otherwize we are in the case where we should print an arrow
                and we have the position...
                
                @see http://www.ogre3d.org/phpBB2/viewtopic.php?t=10131&highlight=rotate+overlay
                
              */
              if (fabs(screen_position.x) <= 1+spheresize.x/2 &&
                  fabs(screen_position.y) <= 1+spheresize.y/2)
              {
                /* 
                  screen_position is in [-1,1]
                  but actual screen values are between [-0.5,0.5] with 0 at center
                  we need to invert y because y is down oriented on the screen 
                  instead of up oriented in the 3d 
                */
                m_reticule_container->setPosition(screen_position.x/2,-screen_position.y/2) ;
                
                m_reticule->setLeft(-spheresize.x/2) ;
                m_reticule->setTop(-spheresize.y/2) ;
                m_reticule->setDimensions(spheresize.x,spheresize.y) ;
                
                if (!m_reticule_is_shown)
                {
                  m_reticule_container->show() ;
                  m_reticule_is_shown = true ;
                }
                if (m_arrow_is_shown)
                {
                  // hide the overlay
                  m_arrow_container->hide() ;
                  m_arrow_is_shown = false ;
                }
              }
              else
              {
                
                ::Ogre::Degree angle = calculateRotation(screen_position.x,screen_position.y) ;

                InternalMessage(
                  "Display","TargetView::updateHUD setting angle is "
                  + Kernel::toString(angle.valueDegrees())
                  ) ;
                
                const float max_position = 1 - getArrowSize() ;
                /// out of screen display an arrow
                if (fabs(screen_position.x) > fabs(screen_position.y))
                {
                  screen_position.y /= fabs(screen_position.x) ;
                  if (fabs(screen_position.y) > max_position)
                  {
                    screen_position.y = screen_position.y<0?-max_position:max_position ;
                  }
                  screen_position.x = screen_position.x<0?-max_position:max_position ;
                }
                else
                {
                  screen_position.x /= fabs(screen_position.y) ;
                  if (fabs(screen_position.x) > max_position)
                  {
                    screen_position.x = screen_position.x<0?-max_position:max_position ;
                  }
                  screen_position.y = screen_position.y<0?-max_position:max_position ;
                }

                InternalMessage(
                  "Display","TargetView::updateHUD setting arrow at x="
                  + Kernel::toString(screen_position.x)
                  + " y=" 
                  + Kernel::toString(screen_position.y)
                  ) ;
                
                m_arrow_container->setPosition(screen_position.x/2,-screen_position.y/2) ;

                ::Ogre::MaterialPtr material = m_arrow->getMaterial();
                ::Ogre::Technique* technique = material->getTechnique(0);
                ::Ogre::Pass* pass = technique->getPass(0);
                ::Ogre::TextureUnitState *texture = pass->getTextureUnitState(0);
                
                // invert rotation because setTextureRotate is anti clockwize
                texture->setTextureRotate(-angle);                 

                if (m_reticule_is_shown)
                {
                  m_reticule_container->hide() ;
                  m_reticule_is_shown = false ;
                }
                if (!m_arrow_is_shown)
                {
                  // hide the overlay
                  m_arrow_container->show() ;
                  m_arrow_is_shown = true ;
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
              if (m_arrow_is_shown)
              {
                // hide the overlay
                m_arrow_container->hide() ;
                m_arrow_is_shown = false ;
              }
            }
          }
          
          bool Target::isSelected() const
          {
            return getObject()->getTrait<Model::Selected>()
                              ->isSelected(getViewPoint()->getTargetingSystem()) ;
          }          

          ::Ogre::Degree Target::calculateRotation(float x,float y)
          {
            ::Ogre::Degree result ;
            if (y != 0)
            {
              result = ::Ogre::Math::ATan(x/y) ;
              if (y <0)
              {
                result = ::Ogre::Degree(180) + result ;
              }
            }
            else
            {
              result = x>0?90:270 ;
            }
            return result ;
          }
        }
      }
    }
  }
}
