/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER rogma.boami@free.fr             *
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
#include <kernel/log.h>

#include <model/observer.h>

#include <display/exception.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/observer.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        RegisterView(Ogre::Observer, 
                     Model::Observer, 
                     Ogre::RealWorldViewPoint) ;
        
        Observer::Observer(Model::Observer*    i_observer,
                           RealWorldViewPoint* i_viewpoint) 
        : Kernel::TraitView<Model::Observer,RealWorldViewPoint>(i_observer,i_viewpoint), 
          m_camera(NULL)
        {
          InternalMessage("Building Ogre::Observer::Observer") ;
        }
        
        void Observer::onInit()
        {
          InternalMessage("Display::Observer::onInit Entering") ;

          /// positionned view must be initialised first
          Positionned* positionned(getView<Positionned>()) ;
          check(positionned,Exception("error")) ;
          positionned->_init() ;

          m_camera = this->getViewPoint()->getManager()->createCamera("camera") ;
            
          /// on le place sur le noeud
          positionned->getNode()->attachObject(m_camera) ;
          
          m_camera->setFOVy(::Ogre::Degree(70)) ;
          
          /// near clip distance is 1 cm
          m_camera->setNearClipDistance(0.01/conversion_factor) ;
                      
          InternalMessage("Display::Observer::onInit Leaving") ;
        }
          
        void Observer::onClose()
        {
          /// ?
//          Positionned* positionned(getView<Positionned>()) ;
//          check(positionned,Exception("error")) ;
//          positionned->getNode()->detachObject(camera) ;

          InternalMessage("Display::Observer::onClose Entering") ;
          this->getViewPoint()->getManager()->destroyCamera(m_camera) ;
          InternalMessage("Display::Observer::onClose Leaving") ;
        }
        
        void Observer::onUpdate()
        {
        }

        ::Ogre::Camera* Observer::getCamera() const
        {
          return m_camera ;
        }
        
      }
    }
  }
}

