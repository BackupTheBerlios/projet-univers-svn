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

#include <base/vue.h>
#include <modele/solide.h>

#include <affichage/implantation/ogre/solide.h>


namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        /// Constructeur.
        Solide::Solide(const Base::Association<Modele::Solide>& _objet)
        : Base::Vue<Modele::Solide>(_objet), modele(NULL)
        {}


      //@}
      /*!
        @name Mise à jour
      */
      // @{
      
        /// Crée une entité.
        void Solide::Initialiser()
        {
          
          Base::Association<Positionne> positionne(*(this->objet)) ;
          
          /// on crée l'élément 3D
          modele = this->pointDeVue->AccesGestionnaire()
                            ->createEntity("",observe->AccesModele()) ;
          
          /// on le place sur le noeud
          positionne->AccesNoeud()->attachObject(modele) ;
        }
        
        /// Détruit l'entité.
        void Solide::Terminer()
        {
          
        }
      
        /// 
        /*!
        @par Etat
          stub vide
        */
        void Solide::Raffraichir()
        {
          
        }


      // @}
    
      }
    }
  }
}
