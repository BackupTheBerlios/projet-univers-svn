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
#include <Ogre.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <model/head_up_display.h>
#include <display/implementation/observer.h>
#include <display/implementation/ogre/observer.h>
#include <display/implementation/ogre/head_up_display/head_up_display_viewpoint.h>

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
            
          HeadUpDisplayViewPoint::HeadUpDisplayViewPoint(
              Kernel::Object* target_display,
              RealWorldViewPoint* real_world)
          : Kernel::ViewPoint(NULL),
            m_head_up_display(target_display),
            m_real_world(real_world)
          {
             InternalMessage("Display","Entering HeadUpDisplayViewPoint::HeadUpDisplayViewPoint") ;
             update(0) ;
             InternalMessage("Display","Leaving HeadUpDisplayViewPoint::HeadUpDisplayViewPoint") ;
          }

          void HeadUpDisplayViewPoint::update(const float&)
          {
            if (m_head_up_display)
            {
              Model::HeadUpDisplay* target_displayer = m_head_up_display->getTrait<Model::HeadUpDisplay>() ;
              if (target_displayer)
              {
                InternalMessage("Display","setting model to" + 
                                Kernel::toString((int)target_displayer->getComputerModel())) ;
                setModel(target_displayer->getComputerModel()) ;
              }
            }
          }
          
          Kernel::Object* HeadUpDisplayViewPoint::getTargetingSystem() const
          {
            if (m_head_up_display)
            {
              return m_head_up_display->getTrait<Model::HeadUpDisplay>()
                                      ->getTargetingSystem() ;
            }
            
            return NULL ;
          }

          ::Ogre::Camera* HeadUpDisplayViewPoint::getCamera() const
          {
            Kernel::Object* observer = m_real_world->getObserver() ;
            if (! observer)
              return NULL ;
            
            Observer* temp = observer->getTrait<Implementation::Observer>()
                                     ->getView<Observer>(m_real_world) ;
            
            if (!temp)
              return NULL ;
            
            return temp->getCamera() ;
          }
            
          Kernel::Object* HeadUpDisplayViewPoint::getWorldRoot() const
          {
            return m_real_world->getRootObject() ;
          }

          Kernel::Object* HeadUpDisplayViewPoint::getObserver() const
          {
            return m_real_world->getObserver() ;
          }
        } 
      }
    }
  }
}
