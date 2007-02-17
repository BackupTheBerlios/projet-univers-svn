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
  namespace Display {
    namespace Implantation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        EnregistreVue(Ogre::Univers,Model::Univers, Ogre::ViewPoint) ;


        Univers::Univers(const Base::Association<Model::Univers>& _univers)
        : Ogre::Vue<Model::Univers>(_univers), lumiere(NULL)
        {
          Base::Traceur::MessageInterne("Built Ogre::Univers") ;
        }
        
        /// Initialise la vue.
        void Univers::init()
        {
          Base::Traceur::MessageInterne("Entering Univers::init") ;
          
          if (! this->initialise)
          {
            
            VerifieCondition(this->AccesViewPoint(), 
                             Exception("Univers::init sans point de vue")) ;
            
            this->AccesViewPoint()->AccesGestionnaire()
                  ->setSkyBox( true, "PU/SpaceSkyBox", 50000 );
            
            lumiere = 
                this->AccesViewPoint()->AccesGestionnaire()
                  ->createLight("MainLight");
                  
            /// lumière
            this->AccesViewPoint()->AccesGestionnaire()
                  ->setAmbientLight(::Ogre::ColourValue(0.5, 0.5, 0.5));

          
            this->initialise = Base::VRAI ;
          }
          Base::Traceur::MessageInterne("Leaving Univers::init") ;
                    
        }

        /// Termine la vue.
        void Univers::close()
        {
          if (this->initialise)
          {
            VerifieCondition(this->AccesViewPoint(), 
                             Exception("Univers::close sans point de vue")) ;
            
            this->AccesViewPoint()->AccesGestionnaire()->setSkyBox( false, "" );
            this->AccesViewPoint()->AccesGestionnaire()
                 ->destroyLight(lumiere) ;

            this->initialise = Base::FAUX ;
          }          
          
        }

        void Univers::update(const Base::Evenement&)
        {
          /*!
            Rien n'a faire
          */
        }

      }
    }
  }
}
       
        
