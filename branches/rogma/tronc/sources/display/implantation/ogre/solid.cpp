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
  namespace Display {
    namespace Implantation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        EnregistreVue(Ogre::Solide,Model::Solide, Ogre::ViewPoint) ;


        /// Constructeur.
        Solide::Solide(const Base::Association<Model::Solide>& _objet)
        : Vue<Model::Solide>(_objet), modele(NULL)
        {}


      //@}
      /*!
        @name Mise à jour
      */
      // @{
      
        /// Crée une entité.
        void Solide::init()
        {
          Base::Traceur::MessageInterne("Entering Solide::init") ;

          if (! this->initialise)
          {
            Base::Association<Positionne> positionne(*(this->objet)) ;
            positionne->init() ;
            
            /// on crée l'élément 3D
            modele = this->AccesViewPoint()->AccesGestionnaire()
                     ->createEntity((const char*)(std::string)observe->AccesObject()->AccesNom(),
                                    (const char*)observe->AccesModel().AccesNom()) ;
            
            /// on le place sur le noeud
            positionne->AccesNoeud()->attachObject(modele) ;
            
            this->initialise = Base::VRAI ;
          }

          Base::Traceur::MessageInterne("Leaving Solide::init") ;

        }
        
        /// Détruit l'entité.
        void Solide::close()
        {
          if (this->initialise)
          {
            /// Positionne doit avoir été terminé
            Base::Association<Positionne> positionne(*(this->objet)) ;
            if (positionne)
            {
              positionne->close() ;
            }  
            
            this->AccesViewPoint()->AccesGestionnaire()
                 ->destroyEntity(this->modele) ;
           
            this->initialise = Base::VRAI ;
          }          
        }
      
        /// 
        /*!
        @par Etat
          stub vide
        */
        void Solide::update(const Base::Evenement&)
        {
          
        }


      // @}
    
      }
    }
  }
}
