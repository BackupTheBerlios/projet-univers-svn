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

#include <model/solid.h>

#include <display/implementation/ogre/positionned.h>
#include <display/implementation/ogre/solid.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        RegisterView(Ogre::Solid,Model::Solid,Ogre::RealWorldViewPoint) ;


        /// Constructeur.
        Solid::Solid(Model::Solid* i_object,
                     RealWorldViewPoint* i_viewpoint)
        : Kernel::TraitView<Model::Solid,RealWorldViewPoint>(i_object,i_viewpoint), 
          mesh(NULL)
        {}


      //@}
      /*!
        @name Mise à jour
      */
      // @{
      
        /// Crée une entité.
        void Solid::onInit()
        {
          InternalMessage("Entering Solid::onInit") ;

          Positionned* positionned(getView<Positionned>()) ;
          positionned->_init() ;
          
          /// on crée l'élément 3D
          mesh = this->getViewPoint()->getManager()
                  ->createEntity(getObject()->getName(),
                                 getModel()->getMesh().getName()) ;
          
          /// on le place sur le noeud
          positionned->getNode()->attachObject(mesh) ;

          InternalMessage("Leaving Solid::onInit") ;
        }
        
        /// Détruit l'entité.
        void Solid::onClose()
        {
          InternalMessage("Display::Solid::onClose Entering") ;
          /// Positionne doit avoir été terminé
          /*!
            @why ???
              try without...
          */
          Positionned* positionned(getView<Positionned>()) ;
          if (positionned)
          {
            positionned->_close() ;
          }  
          
          this->getViewPoint()->getManager()
               ->destroyEntity(mesh) ;

          InternalMessage("Display::Solid::onClose Leaving") ;
        }
      
        /// 
        /*!
        @par Etat
          stub vide
        */
        void Solid::onUpdate()
        {
          
        }


      // @}
    
      }
    }
  }
}
