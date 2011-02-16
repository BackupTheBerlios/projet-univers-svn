/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2011 Mathieu ROGER                                 *
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
#include <model/plays.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/solid.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/observer.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Ogre::Observer,
                     Implementation::Observer,
                     Ogre::RealWorldViewPoint) ;

        void Observer::onInit()
        {
          InternalMessage("Display","Display::Observer::onInit Entering") ;

          // Positioned view must be initialized first
          Positioned* positioned(getView<Positioned>()) ;
          CHECK(positioned,"error") ;

          ::Ogre::SceneManager* manager = this->getViewPoint()->getManager() ;

          m_camera = manager->createCamera(Utility::getUniqueName()) ;

          Ogre::addCamera(m_camera) ;

          InternalMessage("Display","creating camera scene node with parent " +
                                    positioned->getNode()->getName()) ;

          m_node = static_cast< ::Ogre::SceneNode* >(positioned->getNode()->createChild()) ;
          m_node->attachObject(m_camera) ;

          // @todo configure in files
          m_camera->setFOVy(getObject()->getUniqueLinked<Kernel::Inverse<Model::Plays> >()->getTrait<Model::Observer>()->getFieldOfView()) ;

          // near clip distance is 1 cm
          m_camera->setNearClipDistance(0.01/conversion_factor) ;

          getViewPoint()->setObserver(getObject()) ;

          InternalMessage("Display","Display::Observer::onInit Leaving") ;
        }

        void Observer::onClose()
        {
          Ogre::removeCamera(m_camera) ;

          InternalMessage("Display","Display::Observer::onClose Entering") ;
          this->getViewPoint()->getManager()->destroyCamera(m_camera) ;
          getViewPoint()->setObserver(NULL) ;
          InternalMessage("Display","Display::Observer::onClose Leaving") ;
        }

        void Observer::onUpdate()
        {
          InternalMessage("Display","Display::Observer::onUpdate Entering") ;
          Positioned* positioned(getView<Positioned>()) ;

          // acts as a change parent like
          m_node->getParent()->removeChild(m_node) ;
          positioned->getNode()->addChild(m_node) ;

          InternalMessage("Display","moving camera scene node to parent " +
                                    positioned->getNode()->getName()) ;

          InternalMessage("Display","Display::Observer::onUpdate Leaving") ;
        }

        ::Ogre::Camera* Observer::getCamera() const
        {
          return m_camera ;
        }

      }
    }
  }
}

