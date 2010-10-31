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
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/head_up_display/ideal_target.h>

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

          RegisterView(IdealTarget, 
                       Implementation::IdealTarget, 
                       HeadUpDisplayViewPoint) ;
          
          void IdealTarget::setColour(const ::Ogre::ColourValue& colour)
          {
            Utility::setColour(m_target,colour) ;
          }
          
          void IdealTarget::onInit()
          {
            InternalMessage("Display","Entering IdealTarget::onInit") ;
            
            m_target_is_shown = false ;

            m_overlay = getOverlay("PU/base/HUD/IdealTarget") ;
            CHECK(m_overlay,"no overlay") ;
            m_target_container = m_overlay->getChild("PU/base/HUD/IdealTarget/Container") ;
            CHECK(m_target_container,"no m_target_container") ;
            m_target = m_target_container->getChild("PU/base/HUD/IdealTarget/Target") ;
            CHECK(m_target,"no m_target") ;
            InternalMessage("Display","Entering IdealTarget::onInit") ;
            // clone material because we will modify it
            ::Ogre::MaterialPtr material = m_target->getMaterial() ;
            material = material->clone(Utility::getUniqueName()) ;
            m_target->setMaterialName(material->getName()) ;

            m_target_container->hide() ;
            
            m_overlay->show() ;
            onUpdate() ;
  
            InternalMessage("Display","Leaving IdealTarget::onInit") ;
          }
          
          void IdealTarget::onClose()
          {
            if (m_overlay)
            {
              m_overlay->hide() ;
            }
          }
          
          void IdealTarget::onUpdate()
          {
            InternalMessage("Display","IdealTarget::onUpdate calculating target position") ;

            ::Ogre::Camera* camera = getViewPoint()->getCamera() ;

            if (!camera)
              return ;
            
            Model::Computer* computer 
              = getViewPoint()->getTargetingSystem()->getTrait<Model::TargetingSystem>()
                ->getComputer()->getTrait<Model::Computer>() ;
            
            // update target position
            Model::Position pos = computer->getDataPosition(getObject(),
                                                            getViewPoint()->getWorldRoot()) ;
            
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
                m_target_container->setPosition(screen_position.x/2,-screen_position.y/2) ;
                
                if (!m_target_is_shown)
                {
                  m_target_container->show() ;
                  m_target_is_shown = true ;
                }
              }
              else
              {
                if (m_target_is_shown)
                {
                  m_target_container->hide() ;
                  m_target_is_shown = false ;
                }
              }
            }
            else
            {
              if (m_target_is_shown)
              {
                m_target_container->hide() ;
                m_target_is_shown = false ;
              }
            }
            InternalMessage("Display","IdealTarget::onUpdate leaving") ;
            
          }
          

        }
      }
    }
  }
}
