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


#ifndef PU_AFFICHAGE_IMPLANTATION_OGRE_DESTRUCTIBLE_H_
#define PU_AFFICHAGE_IMPLANTATION_OGRE_DESTRUCTIBLE_H_

#include <kernel/trait_view.h>

#include <model/destroyable.h>

#include <display/implementation/ogre/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        
        /// Display d'un élément destructible.
        /*!
          Les éléments destructibles ont différents états selon leur 
          niveau de dégats.
          
          @par Etat
            planning
        */
        class Destroyable : public Kernel::TraitView<Model::Destroyable,
                                                     RealWorldViewPoint>
        {
        public:

          /// Constructeur.
          Destroyable(Model::Destroyable* i_object,
                      RealWorldViewPoint* i_viewpoint) ;

        protected:

          /// Initialise la vue.
          virtual void onInit() ;

          /// Termine la vue.
          virtual void onClose() ;
        
          /// Mise à jour.
          virtual void onUpdate() ;
          

        };
      }
    }
  }
}
#endif

