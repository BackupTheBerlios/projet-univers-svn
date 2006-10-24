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

#include <affichage/implantation/ogre/point_de_vue.h>
#include <affichage/implantation/ogre/positionne.h>

#include <affichage/implantation/ogre/observateur.h>

namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {
        
        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        EnregistreVue(Ogre::Observateur,Modele::Observateur, Ogre::PointDeVue) ;
        
        Observateur::Observateur(
          const Base::Association<Modele::Observateur>& _observateur) 
        : Vue<Modele::Observateur>(_observateur), camera(NULL)
        {
          Base::Traceur::MessageInterne("Building Ogre::Observateur::Observateur") ;
        }
        
        
        void Observateur::Initialiser()
        {
          if (! this->initialise)
          {
            Base::Association<Positionne> positionne(*(this->objet)) ;
            positionne->Initialiser() ;
  
            camera = this->AccesPointDeVue()->AccesGestionnaire()->createCamera("camera") ;
              
            /// on le place sur le noeud
            positionne->AccesNoeud()->attachObject(camera) ;
            
            camera->setFOVy(::Ogre::Degree(70)) ;
//            camera->setNearClipDistance() ;
                        
            this->initialise = Base::VRAI ;
          }
        }
          
        void Observateur::Terminer()
        {
          this->AccesPointDeVue()->AccesGestionnaire()->destroyCamera(this->camera) ;
        }
          
        
        void Observateur::Raffraichir()
        {
        }

        ::Ogre::Camera* Observateur::AccesCamera() const
        {
          return this->camera ;
        }
        
        
      }
    }
  }
}

