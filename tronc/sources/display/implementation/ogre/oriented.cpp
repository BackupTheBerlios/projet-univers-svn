/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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

#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/oriented.h>

using namespace ::Ogre ;

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        RegisterView(Ogre::Oriented,
                     Model::Oriented, 
                     Ogre::RealWorldViewPoint) ;
      
      
      
        Oriented::Oriented(Model::Oriented* i_object,
                           RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Oriented,RealWorldViewPoint>(i_object,i_viewpoint), 
          m_node(NULL)
        {
          InternalMessage("Entering Ogre::Positionned::Positionned") ;
          InternalMessage("Leaving Ogre::Positionned::Positionned") ;
        }
      
        /*!
        @pre
          Parent Positionned View is init.
        */
        void Oriented::onInit()
        {
          InternalMessage("Entering Positionned::init") ;
          
          Model::Positionned* model_positionned 
            = getObject()->getTrait<Model::Positionned>() ;
          
          if (model_positionned)
          {
            Positionned* positionned(
              model_positionned
              ->getView<Positionned>(getViewPoint())) ;
          
            if (positionned)
            {
  
              positionned->_init() ;
              
              m_node = positionned->getNode() ;
  
              InternalMessage(
                "intitalising scene node " + m_node->getName() + 
                " with orientation " + 
                ::Ogre::StringConverter::toString(m_node->getOrientation())) ;
  
              m_node->setOrientation(getModel()->getOrientation().getQuaternion()) ;
  
              InternalMessage(
                "modification of scene node " + m_node->getName() + 
                " with orientation " + 
                ::Ogre::StringConverter::toString(m_node->getOrientation())) ;
            }
          }
          InternalMessage("Leaving Positionned::init") ;

        }

        
        void Oriented::onUpdate()
        {
          m_node->setOrientation(getModel()->getOrientation().getQuaternion()) ;

          InternalMessage(
            "modification of scene node " + m_node->getName() + 
            " with orientation " + 
            ::Ogre::StringConverter::toString(m_node->getOrientation())
            ) ;
        }

      }      
    }
  }
}
