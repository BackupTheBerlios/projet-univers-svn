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
#include <model/positioned.h>
#include <model/observer.h>

#include <display/implementation/ogre/observer.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
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
          
          void Target::onInit()
          {
            InternalMessage("Display","Entering Target::onInit") ;
            
            m_overlay = getOverlay("PU/base/HUD/Target") ;
            m_target_container = m_overlay->getChild("PU/base/HUD/Target/Container") ;
            m_target = (::Ogre::OverlayContainer*)m_target_container->getChild("PU/base/HUD/Target/Target") ;
            m_identification = m_target->getChild("PU/base/HUD/Target/TargetName") ;
            m_target_text = m_target->getChild("PU/base/HUD/Target/TargetsTargetName") ;
            // clone material because we will modify it 
            /*!
              @todo maybe we can share materials for targets (friend, neutral, foe) 
            */
            ::Ogre::MaterialPtr material = m_target->getMaterial() ;
            material = material->clone(Utility::getUniqueName()) ;
            m_target->setMaterialName(material->getName()) ; 
            
            m_arrow = m_target_container->getChild("PU/base/HUD/Target/Arrow") ;
            // clone material because we will modify it only for that object
            material = m_arrow->getMaterial() ;
            material = material->clone(Utility::getUniqueName()) ;
            m_arrow->setMaterialName(material->getName()) ; 

            m_overlay->show() ;

            m_target_is_shown = false ;
            m_target->hide() ;

            m_arrow_is_shown = false ;
            m_arrow->hide() ;
            
            onUpdate() ;
  
            InternalMessage("Display","Leaving Target::onInit") ;
          }
          
          void Target::onClose()
          {
            InternalMessage("Display","Entering Target::onClose") ;
            if (m_overlay)
            {
              m_overlay->hide() ;
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
            Model::Position pos = getObjectTo()->getTrait<Model::Positioned>()
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
              
              m_target->setLeft(-spheresize.x/2) ;
              m_target->setTop(-spheresize.y/2) ;
              m_target->setDimensions(spheresize.x,spheresize.y) ;
              
              if (!m_target_is_shown)
              {
                m_target->show() ;
                m_target_is_shown = true ;
              }
              if (m_arrow_is_shown)
              {
                // hide the overlay
                m_arrow->hide() ;
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
              
              ::Ogre::MaterialPtr material = m_arrow->getMaterial();
              ::Ogre::Technique* technique = material->getTechnique(0);
              ::Ogre::Pass* pass = technique->getPass(0);
              ::Ogre::TextureUnitState* texture = pass->getTextureUnitState(0);
              
              // invert rotation because setTextureRotate is anti clockwize
              texture->setTextureRotate(-angle);                 

              if (m_target_is_shown)
              {
                m_target->hide() ;
                m_target_is_shown = false ;
              }
              if (!m_arrow_is_shown)
              {
                // hide the overlay
                m_arrow->show() ;
                m_arrow_is_shown = true ;
              }
            }
            m_target_container->setPosition(screen_position.x/2,-screen_position.y/2) ;

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
