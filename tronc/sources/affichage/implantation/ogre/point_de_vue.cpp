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
#include <base/traceur.h>
#include <base/erreur.h>

#include <modele/systeme_stellaire.h>

#include <affichage/exception.h>
#include <affichage/implantation/ogre/ogre.h>
#include <affichage/implantation/ogre/point_de_vue.h>

namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {


        PointDeVue::PointDeVue(
          const Base::Association<Modele::Objet>& _observateur)
        : Affichage::PointDeVue(_observateur)
        {

          Base::Traceur::MessageInterne("Entering Ogre::PointDeVue::PointDeVue(const Base::Association<Modele::Objet>&)") ;
          

          Base::Traceur::MessageInterne("Leaving Ogre::PointDeVue::PointDeVue(const Base::Association<Modele::Objet>&)") ;
        
        }
        
        
        /// Vrai si l'objet est visible dans le point de vue
        /*!
        @par Etat
          Minimal
        */
        Base::Booleen PointDeVue::EstVisible
              (const Base::Association<Modele::Objet>& _modele) const
        {
          
          return Base::VRAI ;
          
          /*!
          @todo
            _modele est un parent de l'observateur
            ou 
            _modele est proche de l'observateur (son rapport taille/distance 
            est supérieur à une constante)
          */
          
          
        }
          
          
        /// Initialise le point de vue
        /*!
        @par Etat
          stub null
        */
        void PointDeVue::Initialiser()
        {

          /// initialisation de Ogre
          surface = Racine()->initialise(true) ;
          gestionnaire = Racine()->createSceneManager(::Ogre::ST_GENERIC) ;

          /// Initialise la racine.
          this->univers->Initialiser() ;
        }
        
        /// Néttoie le point de vue.
        void PointDeVue::Terminer()
        {
          /// Supprimme tous les éléments de la scène
          this->gestionnaire->clearScene() ;
          
          /// Termine les objets un par un
          this->univers->Terminer() ;
        }
          
        ::Ogre::SceneManager* PointDeVue::AccesGestionnaire() const
        {
          return this->gestionnaire ;
        }


      }
    }
  }
}
