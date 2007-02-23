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

#ifndef _PU_DISPLAY_IMPLEMENTATION_OGRE_OBSERVATEUR_H_
#define _PU_DISPLAY_IMPLEMENTATION_OGRE_OBSERVATEUR_H_

#include <Ogre.h>

#include <display/implementation/ogre/view.h>

#include <model/observer.h>

#include <display/trait.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        
        /// La propri�t� d'�tre observateur.
        /*!
        */
        class Observer : public View<Model::Observer>,
                         public Trait
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{


          /// Constructeur.
          Observer(Model::Observer*) ;


        // @}
        /*!
          @name Mise � jour
        */
        // @{
        
          /// Cr�e une cam�ra.
          void init() ;
          
          /// D�truit la cam�ra.
          void close() ;
        
          /// 
          /*!
          @par Etat
            stub vide
          
          Model::Observer ne contient pour l'instant aucune donn�e 
          susceptible de changer
          */
          void update(const Kernel::Event&) ;


        // @}
        
          ::Ogre::Camera* getCamera() const ;
          
        private:

          /// La cam�ra
          ::Ogre::Camera* camera ;

        };
      }
    }
  }
}


#endif
