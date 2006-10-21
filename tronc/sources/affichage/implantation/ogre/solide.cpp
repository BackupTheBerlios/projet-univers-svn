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

#include <base/traceur.h>

#include <modele/solide.h>

#include <affichage/implantation/ogre/positionne.h>

#include <affichage/implantation/ogre/solide.h>


namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        EnregistreVue(Ogre::Solide,Modele::Solide, Ogre::PointDeVue) ;


        /// Constructeur.
        Solide::Solide(const Base::Association<Modele::Solide>& _objet)
        : Vue<Modele::Solide>(_objet), modele(NULL)
        {}


      //@}
      /*!
        @name Mise à jour
      */
      // @{
      
        /// Crée une entité.
        void Solide::Initialiser()
        {
          Base::Traceur::MessageInterne("Entering Solide::Initialiser") ;

          if (! this->initialise)
          {
            Base::Association<Positionne> positionne(*(this->objet)) ;
            positionne->Initialiser() ;
            
            /// on crée l'élément 3D
            modele = this->AccesPointDeVue()->AccesGestionnaire()
                              ->createEntity("",(const char*)observe->AccesModele().AccesNom()) ;
            
            /// on le place sur le noeud
            positionne->AccesNoeud()->attachObject(modele) ;
            
            this->initialise = Base::VRAI ;
          }

          Base::Traceur::MessageInterne("Leaving Solide::Initialiser") ;

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
