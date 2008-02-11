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

#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/positionned.h>

using namespace ::Ogre ;

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        RegisterView(Ogre::Positionned,
                     Model::Positionned, 
                     Ogre::RealWorldViewPoint) ;
      
        /// Convert position to Ogre position
        ::Ogre::Vector3 convert(const Model::Position& _position)
        {
          Model::Distance x(_position.getXCoordinate()) ;
          Model::Distance y(_position.getYCoordinate()) ;
          Model::Distance z(_position.getZCoordinate()) ;
          
          /*!
            Ogre uses following conventions : 
            +X = right
            -X = left
            +Y = up
            -Y = down
            +Z = going into the screen
            -Z = going away from the screen
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
        
        Positionned::Positionned(Model::Positionned* i_object,
                                 RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Positionned,RealWorldViewPoint>(i_object,i_viewpoint), 
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
          
          Model::Positionned* positionned_ancestor 
            = getObject()->getAncestor<Model::Positionned>() ;

          if (positionned_ancestor)
          {
            Positionned* parent_node(positionned_ancestor->getView<Positionned>(getViewPoint())) ;
      
            m_node = static_cast<SceneNode*>(parent_node->m_node->createChild()) ;

            InternalMessage("Display",
              "creating scene node " + m_node->getName() + 
              " with parent " + parent_node->m_node->getName() +
              " with position " + 
              ::Ogre::StringConverter::toString(m_node->getPosition())) ;

            m_node->setPosition(convert(getTrait()->getPosition())) ;

            InternalMessage("Display",
              "modification of scene node " + m_node->getName() + 
              " with position " + 
              ::Ogre::StringConverter::toString(m_node->getPosition())) ;
          }
          else
          {
            InternalMessage("Display","root node") ;
            
            m_node = this->getViewPoint()->getManager()->getRootSceneNode() ;
            getViewPoint()->setRootObject(getObject()) ;
          }

          InternalMessage("Display","Leaving Positionned::init") ;

        }

        /// Termine la vue.
        void Positionned::onClose()
        {
          InternalMessage("Display","Display::Positionned::onClose Entering") ;
          
          /*!
            Ogre seams to refuse destroying root node !
          */
          if (getObject()->getAncestor<Model::Positionned>())
          {
            this->getViewPoint()->getManager()
                ->destroySceneNode(this->m_node->getName()) ;
          }
          InternalMessage("Display","Display::Positionned::onClose Leaving") ;
        }
        
        /// La position à changé
        /*!
        @par Etat actuel
          terminé
        */
        void Positionned::onUpdate()
        {
          /// on le replace par rapport à son parent
          m_node->setPosition(convert(getTrait()->getPosition())) ;

          InternalMessage("Display",
            "modification of scene node " + m_node->getName() + 
            " with position " + 
            ::Ogre::StringConverter::toString(m_node->getPosition())) ;
        }

        void Positionned::onChangeParent(Kernel::Object* i_old_parent)
        {
          if (i_old_parent)
          {
            Positionned* parent = i_old_parent->getView<Positionned>(getViewPoint()) ;
            parent->getNode()->removeChild(m_node) ;
          }

          if (getObject()->getParent())
          {
            Positionned* parent = getObject()->getParent()->getView<Positionned>(getViewPoint()) ;
            parent->getNode()->addChild(m_node) ;
          }
          else
          {
            /// error cannot create another root scene node
            ErrorMessage("cannot create another root node") ;
          }
        }
        
        ::Ogre::SceneNode* Positionned::getNode()
        {
          if (m_node == NULL)
          {
            this->_init() ;
          }
          
          return m_node ;
        }


      }      
    }
  }
}
