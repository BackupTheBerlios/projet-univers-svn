/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <OgreVector3.h>

#include <kernel/log.h>

#include <model/solid.h>

#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/solid.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        RegisterView(Ogre::Solid,DisplayedSolid,Ogre::RealWorldViewPoint) ;

        Solid::Solid(DisplayedSolid*     object,
                     RealWorldViewPoint* viewpoint)
        : Kernel::TraitView<DisplayedSolid,RealWorldViewPoint>(object,viewpoint),
          m_mesh(NULL)
        {}


        void Solid::onInit()
        {
          InternalMessage("Display","Entering Solid::onInit") ;

          Positionned* positionned(getView<Positionned>()) ;
          positionned->_init() ;

          // build 3D object
          m_mesh = this->getViewPoint()->getManager()
                   ->createEntity(Utility::getUniqueName(),
                                 getObject()->getTrait<Model::Solid>()->getMesh().getName()) ;

          // put it on the node
          positionned->getNode()->attachObject(m_mesh) ;

          // reset scale factor
          positionned->getNode()->setScale(::Ogre::Vector3(1.0/conversion_factor,
                                                           1.0/conversion_factor,
                                                           1.0/conversion_factor)) ;

          InternalMessage("Display","Leaving Solid::onInit") ;
        }

        void Solid::onClose()
        {
          InternalMessage("Display","Display::Solid::onClose Entering") ;

          this->getViewPoint()->getManager()
               ->destroyEntity(m_mesh) ;

          InternalMessage("Display","Display::Solid::onClose Leaving") ;
        }


        ::Ogre::Entity* Solid::getEntity() const
        {
          return m_mesh ;
        }
      }
    }
  }
}
