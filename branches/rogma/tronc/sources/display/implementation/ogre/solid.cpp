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
        RegisterView(Ogre::Solid,Model::Solid, Ogre::ViewPoint) ;


        /// Constructeur.
        Solid::Solid(Model::Solid* _object)
        : View<Model::Solid>(_objet), model(NULL)
        {}


      //@}
      /*!
        @name Mise à jour
      */
      // @{
      
        /// Crée une entité.
        void Solid::init()
        {
          Kernel::Log::InternalMessage("Entering Solid::init") ;

          if (! this->initialised)
          {
            Positionned* positionned(this->objet->getTrait<Positionned>()) ;
            positionned->init() ;
            
            /// on crée l'élément 3D
            model = this->getViewPoint()->getManager()
                    ->createEntity((const char*)(std::string)observe->getObject()->getName(),
                                   (const char*)observed->getModel().getName()) ;
            
            /// on le place sur le noeud
            positionned->getNode()->attachObject(model) ;
            
            this->initialised = true ;
          }

          Kernel::Log::InternalMessage("Leaving Solid::init") ;

        }
        
        /// Détruit l'entité.
        void Solid::close()
        {
          if (this->initialised)
          {
            /// Positionne doit avoir été terminé
            Positionned* positionned(this->objet->getTrait<Positionned>()) ;
            if (positionned)
            {
              positionned->close() ;
            }  
            
            this->getViewPoint()->getManager()
                 ->destroyEntity(this->model) ;
           
            this->initialised = true ;
          }          
        }
      
        /// 
        /*!
        @par Etat
          stub vide
        */
        void Solid::update(const Kernel::Event&)
        {
          
        }


      // @}
    
      }
    }
  }
}
