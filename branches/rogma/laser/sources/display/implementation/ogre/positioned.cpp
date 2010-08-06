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

#include <model/positioned.h>
#include <model/oriented.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/ogre.h>

using namespace ::Ogre ;

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Ogre::Positioned,
                     Implementation::Positioned,
                     Ogre::RealWorldViewPoint) ;

        /*!
        @pre
          Parent Positioned View is init.
        */
        void Positioned::onInit()
        {
          InternalMessage("Display","Entering Positioned::init") ;

          Positioned* parent_node(getAncestorView<Positioned>()) ;
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

          InternalMessage("Display","Leaving Positioned::init") ;

        }

        void Positioned::onClose()
        {
          InternalMessage("Display","Display::Positioned::onClose Entering") ;

          /*!
            Ogre seams to refuse destroying root node !
          */
          if (getObject()->getAncestor<Implementation::Positioned>())
          {
            this->getViewPoint()->getManager()
                ->destroySceneNode(this->m_node->getName()) ;
          }
          InternalMessage("Display","Display::Positioned::onClose Leaving") ;
        }

        void Positioned::onUpdate()
        {
          // reposition object relatively to its parent
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

        void Positioned::onChangeParent(Kernel::Object* old_parent)
        {
          InternalMessage("Display","Display::Positioned::onChangeParent Entering") ;
          if (old_parent)
          {
            Positioned* parent = old_parent->getView<Positioned>(getViewPoint()) ;
            if (parent && parent->getNode())
            {
              parent->getNode()->removeChild(m_node) ;
            }
          }

          if (getObject()->getParent())
          {
            Positioned* parent = getView<Positioned>() ;
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
          InternalMessage("Display","Display::Positioned::onChangeParent Leaving") ;
        }

        ::Ogre::SceneNode* Positioned::getNode()
        {
          if (m_node == NULL)
          {
            this->_init() ;
          }

          return m_node ;
        }

        void Positioned::setPosition()
        {
          Model::Positioned* Positioned = getTrait<Model::Positioned>() ;
          if (Positioned)
            m_node->setPosition(convert(Positioned->getPosition())) ;
        }

        void Positioned::setOrientation()
        {
          Model::Oriented* oriented = getTrait<Model::Oriented>() ;
          if (oriented)
            m_node->setOrientation(oriented->getOrientation().getQuaternion()) ;
        }



      }
    }
  }
}
