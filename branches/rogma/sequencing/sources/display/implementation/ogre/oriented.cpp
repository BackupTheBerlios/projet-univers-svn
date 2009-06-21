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
#include <kernel/log.h>

#include <model/oriented.h>
#include <model/positionned.h>
#include <display/implementation/positionned.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/oriented.h>

using namespace ::Ogre ;

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        RegisterView(Ogre::Oriented,
                     Implementation::Oriented,
                     Ogre::RealWorldViewPoint) ;



        Oriented::Oriented(Implementation::Oriented* object,
                           RealWorldViewPoint*       viewpoint)
        : Kernel::TraitView<Implementation::Oriented,RealWorldViewPoint>(object,viewpoint),
          m_node(NULL)
        {
          InternalMessage("Display","Entering Ogre::Positionned::Positionned") ;
          InternalMessage("Display","Leaving Ogre::Positionned::Positionned") ;
        }

        /*!
        @pre
          Parent Positionned View is init.
        */
        void Oriented::onInit()
        {
          InternalMessage("Display","Entering Oriented::onInit") ;
          Positionned* positionned(getView<Positionned>()) ;

          if (positionned)
          {
            m_node = positionned->getNode() ;

            InternalMessage("Display",
              "intitalising scene node " + m_node->getName() +
              " with orientation " +
              ::Ogre::StringConverter::toString(m_node->getOrientation())) ;

            m_node->setOrientation(getObject()->getTrait<Model::Oriented>()->getOrientation().getQuaternion()) ;

            InternalMessage("Display",
              "modification of scene node " + m_node->getName() +
              " with orientation " +
              ::Ogre::StringConverter::toString(m_node->getOrientation())) ;
          }
          InternalMessage("Display","Leaving Oriented::onInit") ;
        }

        void Oriented::onUpdate()
        {
          if (m_node)
          {
            m_node->setOrientation(getObject()->getTrait<Model::Oriented>()->getOrientation().getQuaternion()) ;
            m_node->_update(true,false) ;

            InternalMessage("Display",
              "modification of scene node " + m_node->getName() +
              " with orientation " +
              ::Ogre::StringConverter::toString(m_node->getOrientation())
              ) ;
          }
        }

      }
    }
  }
}
