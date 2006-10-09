/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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

#ifndef _PU_AFFICHAGE_IMPLANTATION_OGRE_UNIVERS_H_
#define _PU_AFFICHAGE_IMPLANTATION_OGRE_UNIVERS_H_

#include <Ogre.h>

#include <base/association.h>
#include <base/composition.h>
#include <base/vue.h>

#include <modele/univers.h>

#include <affichage/implantation/ogre/facette.h>

namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
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
        class Univers : public Base::Vue<Modele::Univers>,
                         public Facette 
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{
          
          /// Constructeur.
          Univers(const Base::Association<Modele::Univers>& _univers) ;

          /// Initialise la vue.
          virtual void Initialiser() ;

          /// Termine la vue.
          virtual void Terminer() ;

          
        // @}
        /*!
          @name Raffraichissement
                      
        */  
        // @{
        
          /// Le modèle a changé, on réactualise la vue.
          virtual void Raffraichir() ;
            
        // @}
        
        private:
          
          /// Le ciel étoilé n'a pas besoin d'être stocké.
          
        };
      }
    }
  }
}


#endif
