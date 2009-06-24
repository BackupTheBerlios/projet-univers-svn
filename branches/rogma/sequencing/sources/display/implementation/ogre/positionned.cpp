/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2008 Mathieu ROGER                                 *
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

#include <model/positionned.h>
#include <model/oriented.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/positionned.h>

using namespace ::Ogre ;

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Ogre::Positionned,
                     Implementation::Positionned,
                     Ogre::RealWorldViewPoint) ;

        /// Convert position to Ogre position
        ::Ogre::Vector3 convert(const Model::Position& _position)
        {
          Model::Distance x(_position.getXCoordinate()) ;
          Model::Distance y(_position.getYCoordinate()) ;
          Model::Distance z(_position.getZCoordinate()) ;

          /*!
            Ogre is right handed
            Ogre uses following conventions :
            +X = right
            -X = left
            +Y = up
            -Y = down
            -Z = going into the screen (forward)
            +Z = going away from the screen (into you)
          */


          float XMeters = x.Meter() ;
          float YMeters = y.Meter() ;
          float ZMeters = z.Meter() ;

          return ::Ogre::Vector3(XMeters/conversion_factor,
                                 YMeters/conversion_factor,
                                 ZMeters/conversion_factor) ;
        }

        ::Ogre::Real convert(const Model::Distance& distance)
        {
          return distance.Meter()/conversion_factor ;

        }

        Positionned::Positionned(Implementation::Positionned* object,
                                 RealWorldViewPoint*          viewpoint)
        : Kernel::TraitView<Implementation::Positionned,RealWorldViewPoint>(object,viewpoint),
          m_node(NULL)
        {
          InternalMessage("Display","Entering Ogre::Positionned::Positionned") ;
          InternalMessage("Display","Leaving Ogre::Positionned::Positionned") ;
        }

        /*!
        @pre
          Parent Positionned View is init.
        */
        void Positionned::onInit()
        {
          InternalMessage("Display","Entering Positionned::init") ;

          Positionned* parent_node(getAncestorView<Positionned>()) ;
          if (parent_node)
          {
            InternalMessage("Display",
              "creating scene node with parent " + parent_node->getNode()->getName()) ;

            m_node = static_cast<SceneNode*>(parent_node->getNode()->createChild()) ;

            InternalMessage("Display",
              "creating scene node " + m_node->getName() +
              " with parent " + parent_node->m_node->getName() +
              " with position " +
              ::Ogre::StringConverter::toString(m_node->getPosition())) ;

            setPosition() ;
            setOrientation() ;

            InternalMessage("Display",
              "modification of scene node " + m_node->getName() +
              " with position " +
              ::Ogre::StringConverter::toString(m_node->getPosition())) ;
          }
          else
          {
            InternalMessage("Display","root node") ;

            m_node = static_cast<SceneNode*>(this->getViewPoint()->getManager()->getRootSceneNode()->createChild()) ;
            getViewPoint()->setRootObject(getObject()) ;
          }

          InternalMessage("Display","Leaving Positionned::init") ;

        }

        void Positionned::onClose()
        {
          InternalMessage("Display","Display::Positionned::onClose Entering") ;

          /*!
            Ogre seams to refuse destroying root node !
          */
          if (getObject()->getAncestor<Implementation::Positionned>())
          {
            this->getViewPoint()->getManager()
                ->destroySceneNode(this->m_node->getName()) ;
          }
          InternalMessage("Display","Display::Positionned::onClose Leaving") ;
        }

        void Positionned::onUpdate()
        {
          // reposition object relativelly to its parent
          setOrientation() ;
          setPosition() ;

          m_node->_update(true,false) ;

          InternalMessage("Display",
            "modification of scene node " + m_node->getName() +
            " with position " +
            ::Ogre::StringConverter::toString(m_node->getPosition()) +
            " and orientation " +
            ::Ogre::StringConverter::toString(m_node->getOrientation())) ;
        }

        void Positionned::onChangeParent(Kernel::Object* old_parent)
        {
          InternalMessage("Display","Display::Positionned::onChangeParent Entering") ;
          if (old_parent)
          {
            Positionned* parent = old_parent->getView<Positionned>(getViewPoint()) ;
            if (parent && parent->getNode())
            {
              parent->getNode()->removeChild(m_node) ;
            }
          }

          if (getObject()->getParent())
          {
            Positionned* parent = getView<Positionned>() ;
            if (parent && parent->getNode())
            {
              parent->getNode()->addChild(m_node) ;
            }
          }
          else
          {
            /// error cannot create another root scene node
            ErrorMessage("cannot create another root node") ;
          }
          InternalMessage("Display","Display::Positionned::onChangeParent Leaving") ;
        }

        ::Ogre::SceneNode* Positionned::getNode()
        {
          if (m_node == NULL)
          {
            this->_init() ;
          }

          return m_node ;
        }

        void Positionned::setPosition()
        {
          Model::Positionned* positionned = getTrait<Model::Positionned>() ;
          if (positionned)
            m_node->setPosition(convert(positionned->getPosition())) ;
        }

        void Positionned::setOrientation()
        {
          Model::Oriented* oriented = getTrait<Model::Oriented>() ;
          if (oriented)
            m_node->setOrientation(oriented->getOrientation().getQuaternion()) ;
        }



      }
    }
  }
}
