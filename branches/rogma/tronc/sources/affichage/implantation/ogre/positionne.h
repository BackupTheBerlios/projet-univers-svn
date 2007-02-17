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


#ifndef _AFFICHAGE_IMPLANTATION_OGRE_POSITIONNE_H_
#define _AFFICHAGE_IMPLANTATION_OGRE_POSITIONNE_H_

#include <Ogre.h>

#include <base/association.h>

#include <modele/positionne.h>

#include <affichage/implantation/ogre/vue.h>
#include <affichage/facette.h>

namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        class PointDeVue ;
        
        /// Vue sur les éléments ayant une position.
        class Positionne : public Vue<Modele::Positionne>,
                            public Facette
        {
        public:

          /// Constructeur.
          Positionne(const Base::Association<Modele::Positionne>& _objet) ;
        
          /// Initialise la vue.
          virtual void Initialiser() ;

          /// Termine la vue.
          virtual void Terminer() ;
        
          /// Mise à jour.
          virtual void Rafraichir(const Base::Evenement&) ;
          
          /// Acces au noeud.
          /*!
            Initialise la vue si cela n'a pas été fait.
          */
          ::Ogre::SceneNode* AccesNoeud() ;
          
        private:
          
          /// Noeud dans la scène.
          ::Ogre::SceneNode* noeud ;

        };

      }      
    }
  }
}
#endif
