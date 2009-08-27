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

#include <model/targeting_system.h>
#include <model/computer.h>
#include <model/solid.h>
#include <model/positionned.h>
#include <model/observer.h>

#include <display/implementation/ogre/observer.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/head_up_display/target.h>

namespace ProjetUnivers 
{
  namespace Display 
  {
    namespace Implementation 
    {
      namespace Ogre 
      {
        namespace HUD 
        {

          RegisterRelationView(Target,
                               Implementation::Target,
                               RealWorldViewPoint) ;
          

          namespace 
          {
            float arrow_size = 0 ;
            std::string arrow_material ;
            std::string target_material ;
          }
          
          float getArrowSize()
          {
            if (arrow_size == 0 )
            {            
              arrow_size = Kernel::Parameters::getValue<float>("Display","ArrowSize",0.05) ;
            }
            return arrow_size ;
          }
          
          std::string getTargetMaterial()
          {
            if (target_material == "")
            {
              target_material = Kernel::Parameters::getValue<std::string>("Display","TargetMaterial","PU/material/target") ;
            }
            return target_material ;
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
            
            m_target_is_shown = false ;
            m_arrow_is_shown = false ;

            m_target_container = static_cast< ::Ogre::OverlayContainer* >(
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName())) ;
            getOverlay()->add2D(m_target_container) ;
            
            m_target_container->setPosition(0,0) ;
            m_target_container->setWidth(1) ;
            m_target_container->setHeight(1) ;

            m_target = 
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName()) ;

            // clone material because we will modify it 
            /*!
              @todo maybe we can share materials for targets (friend, neutral, foe) 
            */
            ::Ogre::MaterialPtr material = ::Ogre::MaterialManager::getSingleton().getByName(getTargetMaterial()); 
            material = material->clone(Utility::getUniqueName()) ;
            m_target->setMaterialName(material->getName()) ; 
            
            m_target->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
            m_target->setVerticalAlignment(::Ogre::GVA_CENTER) ;
            m_target_container->_addChild(m_target) ;
            m_target_container->hide() ;

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

            // clone material because we will modify it only for that object
            material = ::Ogre::MaterialManager::getSingleton().getByName(getArrowMaterial()); 
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

            // text displaying identification
            m_identification_container = static_cast< ::Ogre::OverlayContainer* >(
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName())) ;
            getOverlay()->add2D(m_identification_container) ;
            
            m_identification_container->setPosition(0,0) ;
            m_identification_container->setWidth(1) ;
            m_identification_container->setHeight(1) ;

            m_identification = 
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "TextArea", Utility::getUniqueName()) ;
            
            m_identification->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
            m_identification->setVerticalAlignment(::Ogre::GVA_CENTER) ;
            m_identification->setMetricsMode(::Ogre::GMM_PIXELS) ;
            m_identification->setParameter("font_name", "BlueHighway");
            m_identification->setParameter("char_height", "16");
            m_identification->setParameter("horz_align", "center");
            m_identification->setColour(::Ogre::ColourValue(1.0, 1.0, 1.0));            
            m_identification_container->_addChild(m_identification) ;
            m_identification_container->hide() ;
            m_identification->setCaption("unidentified") ;
            
            // text displaying identification
            m_target_text_container = static_cast< ::Ogre::OverlayContainer* >(
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName())) ;
            getOverlay()->add2D(m_target_text_container) ;
            
            m_target_text_container->setPosition(0,0) ;
            m_target_text_container->setWidth(1) ;
            m_target_text_container->setHeight(1) ;

            m_target_text = 
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "TextArea", Utility::getUniqueName()) ;
            
            m_target_text->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
            m_target_text->setVerticalAlignment(::Ogre::GVA_CENTER) ;
            m_target_text->setMetricsMode(::Ogre::GMM_PIXELS) ;
            m_target_text->setParameter("font_name", "BlueHighway");
            m_target_text->setParameter("char_height", "16");
            m_target_text->setParameter("horz_align", "center");
            m_target_text->setColour(::Ogre::ColourValue(1.0, 1.0, 1.0));            
            m_target_text_container->_addChild(m_target_text) ;
            m_target_text_container->hide() ;
            m_target_text->setCaption("target :") ;
            
            
            getOverlay()->show() ;
            
            onUpdate() ;
  
            InternalMessage("Display","Leaving Target::onInit") ;
          }
          
          void Target::onClose()
          {
            InternalMessage("Display","Entering Target::onClose") ;

            if (m_target_is_shown)
            {
              // hide the overlay
              m_target_container->hide() ;
              m_identification_container->hide() ;
              m_target_text_container->hide() ;
              m_target_is_shown = false ;
            }

            if (m_arrow_is_shown)
            {
              // hide the overlay
              m_arrow_container->hide() ;
              m_arrow_is_shown = false ;
            }

            if (m_target_container)
            {
              getOverlay()->remove2D(m_target_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_target) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_target_container) ;
              m_target_container = NULL ;
              m_target = NULL ;
            }
            if (m_arrow_container)
            {
              getOverlay()->remove2D(m_arrow_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_arrow) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_arrow_container) ;
              m_arrow_container = NULL ;
              m_arrow = NULL ;
            }
            if (m_identification_container)
            {
              getOverlay()->remove2D(m_identification_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_identification) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_identification_container) ;
              m_identification_container = NULL ;
              m_identification = NULL ;
            }
            if (m_target_text_container)
            {
              getOverlay()->remove2D(m_target_text_container) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_target_text) ;
              ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_target_text_container) ;
              m_target_text_container = NULL ;
              m_target_text = NULL ;
            }
            InternalMessage("Display","Leaving Target::onClose") ;
          }
          
          void Target::onUpdate()
          {
            InternalMessage("Display","Target::onUpdate calculating target position") ;

            ::Ogre::Camera* camera = getObjectFrom()->getChild<Implementation::Observer>()
                                     ->getView<Ogre::Observer>(getViewPoint())->getCamera() ;
            
            if (!camera)
            {
              ErrorMessage("Target::onUpdate no camera") ;
              return ;
            }
            
            // update target global position
            Model::Position pos = getObjectTo()->getTrait<Model::Positionned>()
                                  ->getPosition(getViewPoint()->getRootObject()) ;
            
            ::Ogre::Vector3 position = convert(pos) ;

            InternalMessage("Display","Target::onUpdate object absolute position="
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
            ::Ogre::Real radius = convert(getObjectTo()->getTrait<Model::Solid>()
                                                       ->getRadius()) ;

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
              x,y in -1/1 + screen size/2
              
              Otherwise we are in the case where we should print an arrow
              and we have the position...
              
              @see http://www.ogre3d.org/phpBB2/viewtopic.php?t=10131&highlight=rotate+overlay
              
            */
            if (eye_position.z < 0 &&
                fabs(screen_position.x) <= 1+spheresize.x/2 &&
                fabs(screen_position.y) <= 1+spheresize.y/2)
            {
              InternalMessage("Display","TargetView::updateHUD object is visible") ;
              /* 
                screen_position is in [-1,1]
                but actual screen values are between [-0.5,0.5] with 0 at center
                we need to invert y because y is down oriented on the screen 
                instead of up oriented in the 3d 
              */
              m_target_container->setPosition(screen_position.x/2,-screen_position.y/2) ;
              
              m_target->setLeft(-spheresize.x/2) ;
              m_target->setTop(-spheresize.y/2) ;
              m_target->setDimensions(spheresize.x,spheresize.y) ;
              
              m_identification_container->setPosition(screen_position.x/2,-screen_position.y/2-spheresize.y/2) ;
              m_identification->setLeft(-spheresize.x/2) ;
              m_identification->setTop(-spheresize.y/2) ;
              m_identification->setDimensions(spheresize.x,0.1) ;

              m_target_text_container->setPosition(screen_position.x/2,-screen_position.y/2+spheresize.y/2) ;
              m_target_text->setLeft(-spheresize.x/2) ;
              m_target_text->setTop(-spheresize.y/2) ;
              m_target_text->setDimensions(spheresize.x,0.1) ;
              
              if (!m_target_is_shown)
              {
                m_target_container->show() ;
                m_identification_container->show() ;
                m_target_text_container->show() ;
                m_target_is_shown = true ;
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

              // magic...
              if (eye_position.z > 0)
                screen_position.x = -screen_position.x ;
              
              ::Ogre::Degree angle = calculateRotation(screen_position.x,
                                                       screen_position.y) ;

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
                  screen_position.y = (screen_position.y<0)?-max_position:max_position ;
                }
                screen_position.x = (screen_position.x<0)?-max_position:max_position ;
              }
              else
              {
                screen_position.x /= fabs(screen_position.y) ;
                if (fabs(screen_position.x) > max_position)
                {
                  screen_position.x = (screen_position.x<0)?-max_position:max_position ;
                }
                screen_position.y = (screen_position.y<0)?-max_position:max_position ;
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
              ::Ogre::TextureUnitState* texture = pass->getTextureUnitState(0);
              
              // invert rotation because setTextureRotate is anti clockwize
              texture->setTextureRotate(-angle);                 

              if (m_target_is_shown)
              {
                m_target_container->hide() ;
                m_identification_container->hide() ;
                m_target_text_container->hide() ;
                m_target_is_shown = false ;
              }
              if (!m_arrow_is_shown)
              {
                // hide the overlay
                m_arrow_container->show() ;
                m_arrow_is_shown = true ;
              }
            }
          }
          
          void Target::setTargetColour(const ::Ogre::ColourValue& colour)
          {
            if (m_arrow)
              Utility::setColour(m_arrow,colour) ;
            if (m_target)
              Utility::setColour(m_target,colour) ;
            if (m_identification)
              Utility::setColour(m_identification,colour) ;
            if (m_target_text)
              Utility::setColour(m_target_text,colour) ;
          }
          
          void Target::setTargetIdentification(const std::string& identification)
          {
            if (m_target_text)
              m_target_text->setCaption("target : " + identification) ;
          }
          
          void Target::setIdentification(const std::string& identification)
          {
            if (m_identification)
              m_identification->setCaption(identification) ;
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
              result = (x>0)?90:270 ;
            }
            return result ;
          }
        }
      }
    }
  }
}
