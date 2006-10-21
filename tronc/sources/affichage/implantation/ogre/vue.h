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
#ifndef PU_AFFICHAGE_IMPLANTATION_OGRE_VUE_H_
#define PU_AFFICHAGE_IMPLANTATION_OGRE_VUE_H_

#include <base/association.h>

#include <base/vue.h>

namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        class PointDeVue ;
                      
        /// Une vue Ogre.
        /*!
          Sert à factoriser certaines opérations.
        */
        template <class Modele> class Vue : public Base::Vue<Modele>
        {
        public:
    
          /// Objet de cette facette.          
          Base::Association<PointDeVue> AccesPointDeVue() const ;

          /// Mise à jour de la vue.
          virtual void Raffraichir() = 0 ;
    
          /// Destructeur de classe abstraite.    
          virtual ~Vue() ;
        
        protected: 
        
          /// Constructeur de classe abstraite.
          Vue(const Base::Association<Modele>& _modele) ;
        };
      }
    }
  }
}

#include <affichage/implantation/ogre/vue.cxx>

#endif /*PU_AFFICHAGE_IMPLANTATION_OGRE_VUE_H_*/
