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

#include <Ogre.h>

#include <base/traceur.h>
#include <base/erreur.h>

#include <affichage/exception.h>

#include <affichage/implantation/ogre/univers.h>


namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        EnregistreVue(Ogre::Univers,Modele::Univers, Ogre::PointDeVue) ;


        Univers::Univers(const Base::Association<Modele::Univers>& _univers)
        : Ogre::Vue<Modele::Univers>(_univers), lumiere(NULL)
        {
          Base::Traceur::MessageInterne("Built Ogre::Univers") ;
        }
        
        /// Initialise la vue.
        void Univers::Initialiser()
        {
          Base::Traceur::MessageInterne("Entering Univers::Initialiser") ;
          
          if (! this->initialise)
          {
            
            VerifieCondition(this->AccesPointDeVue(), 
                             Exception("Univers::Initialiser sans point de vue")) ;
            
            this->AccesPointDeVue()->AccesGestionnaire()
                  ->setSkyBox( true, "PU/SpaceSkyBox", 50000 );
            
            lumiere = 
                this->AccesPointDeVue()->AccesGestionnaire()
                  ->createLight("MainLight");
                  
            /// lumière
            this->AccesPointDeVue()->AccesGestionnaire()
                  ->setAmbientLight(::Ogre::ColourValue(0.5, 0.5, 0.5));

          
            this->initialise = Base::VRAI ;
          }
          Base::Traceur::MessageInterne("Leaving Univers::Initialiser") ;
                    
        }

        /// Termine la vue.
        void Univers::Terminer()
        {
          if (this->initialise)
          {
            VerifieCondition(this->AccesPointDeVue(), 
                             Exception("Univers::Terminer sans point de vue")) ;
            
            this->AccesPointDeVue()->AccesGestionnaire()->setSkyBox( false, "" );
            this->AccesPointDeVue()->AccesGestionnaire()
                 ->destroyLight(lumiere) ;

            this->initialise = Base::FAUX ;
          }          
          
        }

        void Univers::Rafraichir(const Base::Evenement&)
        {
          /*!
            Rien n'a faire
          */
        }

      }
    }
  }
}
       
        
