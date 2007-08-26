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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_UNIVERSE_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_UNIVERSE_H_

#include <Ogre.h>

#include <kernel/trait_view.h>
#include <model/universe.h>
#include <display/implementation/ogre/real_world_view_point.h>



namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// La partie affichage du monde 3d.
        /*!
        @par Etat actuel
          Affiche un ciel étoilé.

        @par Etats futurs
          Peut être que c'est juste un fond noir et que les étoiles sont dûes 
          aux autres corps (galaxies et autres)... mais cela suposerait d'avoir 
          un gros univers.
        */
        class Universe : public Kernel::TraitView<Model::Universe,
                                                  RealWorldViewPoint>
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{
          
          /// Constructeur.
          Universe(Model::Universe* i_universe,
                   RealWorldViewPoint* i_viewpoint) ;

        protected:
        
        // @}
        /*!
          @name Updates
                      
        */  
        // @{
        
          /// Initialise la vue.
          virtual void onInit() ;

          /// Termine la vue.
          virtual void onClose() ;
        
          /// Le modèle a changé, on réactualise la vue.
          virtual void onUpdate() ;
            
        // @}
        private:
          
          /// Le ciel étoilé n'a pas besoin d'être stocké.
          ::Ogre::Light* light ;
          
        };
      }
    }
  }
}


#endif        

