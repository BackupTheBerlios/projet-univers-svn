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
#include <model/target_displayer.h>
#include <display/implementation/observer.h>
#include <display/implementation/ogre/observer.h>
#include <display/implementation/ogre/head_up_display/target_displayer_viewpoint.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        namespace HeadUpDisplay {
            
          TargetDisplayerViewPoint::TargetDisplayerViewPoint(
              Kernel::Object* target_display,
              RealWorldViewPoint* real_world)
          : Kernel::ViewPoint(NULL),
            m_target_displayer(target_display),
            m_real_world(real_world)
          {
             InternalMessage("Display","Entering TargetDisplayerViewPoint::TargetDisplayerViewPoint") ;
             update(0) ;
             InternalMessage("Display","Leaving TargetDisplayerViewPoint::TargetDisplayerViewPoint") ;
          }

          void TargetDisplayerViewPoint::update(const float&)
          {
            if (m_target_displayer)
            {
              Model::TargetDisplayer* target_displayer = m_target_displayer->getTrait<Model::TargetDisplayer>() ;
              if (target_displayer)
              {
                InternalMessage("Display","setting model to" + 
                                Kernel::toString((int)target_displayer->getComputerModel())) ;
                setModel(target_displayer->getComputerModel()) ;
              }
            }
          }
          
          Kernel::Object* TargetDisplayerViewPoint::getTargetingSystem() const
          {
            if (m_target_displayer)
            {
              return m_target_displayer->getTrait<Model::TargetDisplayer>()
                                       ->getTargetingSystem() ;
            }
            
            return NULL ;
          }

          ::Ogre::Camera* TargetDisplayerViewPoint::getCamera() const
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
            
          Kernel::Object* TargetDisplayerViewPoint::getWorldRoot() const
          {
            return m_real_world->getRootObject() ;
          }

          Kernel::Object* TargetDisplayerViewPoint::getObserver() const
          {
            return m_real_world->getObserver() ;
          }
        } 
      }
    }
  }
}
