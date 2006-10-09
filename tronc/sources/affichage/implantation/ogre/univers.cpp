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

#include <Ogre.h>

#include <base/erreur.h>

#include <affichage/implantation/ogre/univers.h>


namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        Univers::Univers(const Base::Association<Modele::Univers>& _univers)
        : Base::Vue<Modele::Univers>()
        {}
        
        /// Initialise la vue.
        void Univers::Initialiser()
        {
          VerifieCondition(this->pointdeVue, 
                           Exception("Univers::Initialiser sans point de vue")) ;
          
          this->pointdeVue->AccesGestionnaire()->setSkyBox( true, "Examples/SpaceSkyBox" );
          
        }

        /// Termine la vue.
        void Univers::Terminer()
        {
          VerifieCondition(this->pointdeVue, 
                           Exception("Univers::Terminer sans point de vue")) ;
          
          this->pointdeVue->AccesGestionnaire()->setSkyBox( false, "" );
          
        }

        void Univers::Raffraichir()
        {
          /*!
            Rien n'a faire
          */
        }

      }
    }
  }
}
       
        
