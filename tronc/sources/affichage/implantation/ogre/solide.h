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

#ifndef _PU_AFFICHAGE_IMPLANTATION_OGRE_SOLIDE_H_
#define _PU_AFFICHAGE_IMPLANTATION_OGRE_SOLIDE_H_

#include <base/vue.h>

#include <modele/solide.h>

#include <affichage/implantation/ogre/facette.h>

namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        /// Affichage des objets 3D.
        /*!
        @par Etat actuel
          planning
        */
        class Solide : public Base::Vue<Modele::Solide>, 
                        public Facette
        {
        public:
        
        // **********************
        /// @name Constructeur/Destructeur
        // **********************
        // @{

          /// Constructeur.
          Solide(const Base::Association<Modele::Solide>& _objet) ;


        //@}
        /*!
          @name Mise à jour
        */
        // @{
        
          /// Crée une entité.
          void Initialiser() ;
          
          /// Détruit l'entité.
          void Terminer() ;
        
          /// 
          /*!
          @par Etat
            stub vide
          */
          void Raffraichir() ;


        // @}
    
        private:
          
          /// Modèle 3D.
          ::Ogre::Entity* modele ;
      
        };
      }
    }
  }
}
#endif
