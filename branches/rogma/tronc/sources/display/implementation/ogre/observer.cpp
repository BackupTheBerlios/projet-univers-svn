/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <display/implementation/ogre/view_point.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/observer.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        /// Indique que la cette vue s'applique au mod�le dans ce point de vue
        RegisterView(Ogre::Observer, Model::Observer, Ogre::ViewPoint) ;
        
        Observer::Observer(Model::Observer* _observer) 
        : View<Model::Observer>(_observer), camera(NULL)
        {
          Kernel::Log::InternalMessage("Building Ogre::Observer::Observer") ;
        }
        
        
        void Observer::init()
        {
          if (! this->initialised)
          {
            Positionned* positionned(this->object->getTrait<Positionned>()) ;
            positionned->init() ;
  
            camera = this->getViewPoint()->getManager()->createCamera("camera") ;
              
            /// on le place sur le noeud
            positionned->getNode()->attachObject(camera) ;
            
            camera->setFOVy(::Ogre::Degree(70)) ;
//            camera->setNearClipDistance() ;
                        
            this->initialised = true ;
          }
        }
          
        void Observer::close()
        {
          if (this->initialised)
          {
            this->getViewPoint()->getManager()->destroyCamera(this->camera) ;
            this->initialised = false ;

          }
        }
          
        
        void Observer::update(const Kernel::Event&)
        {
        }

        ::Ogre::Camera* Observer::getCamera() const
        {
          return this->camera ;
        }
        
        
      }
    }
  }
}

