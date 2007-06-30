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
#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/ship_control_debug.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        RegisterView(Ogre::ShipControl,
                     Model::ShipControl,
                     Ogre::RealWorldViewPoint) ;


        ShipControl::ShipControl(Model::ShipControl* i_object,
                     RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::ShipControl,
                            RealWorldViewPoint>(i_object,i_viewpoint), 
          m_object(NULL)
        {}


      //@}
      /*!
        @name Mise à jour
      */
      // @{
      
        /// Crée une entité.
        void ShipControl::onInit()
        {
          InternalMessage("Entering ShipControl::onInit") ;

          Positionned* positionned(getView<Positionned>()) ;
          positionned->_init() ;
          
          Model::Oriented* oriented(getModel()->getStick()) ;
          
          /// on crée l'élément 3D
          m_object = this->getViewPoint()->getManager()
                  ->createEntity(Utility::getUniqueName(),"stick.mesh") ; 
            
          
          /// on le place sur le noeud
          positionned->getNode()->attachObject(m_object) ;

          InternalMessage("Leaving ShipControl::onInit") ;
        }
        
        void ShipControl::onClose()
        {
          InternalMessage("Display::ShipControl::onClose Entering") ;
          

          InternalMessage("Display::ShipControl::onClose Leaving") ;
        }
      
        /// 
        /*!
        @par Etat
          stub vide
        */
        void ShipControl::onUpdate()
        {
          
        }


      // @}
    
      }
    }
  }
}
