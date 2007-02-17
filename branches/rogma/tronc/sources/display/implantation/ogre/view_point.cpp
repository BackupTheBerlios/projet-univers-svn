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
#include <base/erreur.h>

#include <modele/systeme_stellaire.h>

#include <affichage/exception.h>
#include <affichage/implantation/ogre/ogre.h>
#include <affichage/implantation/ogre/univers.h>
#include <affichage/implantation/ogre/observateur.h>

#include <affichage/implantation/ogre/point_de_vue.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implantation {
      namespace Ogre {


        ViewPoint::ViewPoint(
          const Base::Association<Model::Object>& _observateur)
        : Display::ViewPoint(_observateur)
        {

          Base::Traceur::MessageInterne("Entering Ogre::ViewPoint::ViewPoint(const Base::Association<Model::Object>&)") ;
          

          Base::Traceur::MessageInterne("Leaving Ogre::ViewPoint::ViewPoint(const Base::Association<Model::Object>&)") ;
        
        }
        
        
        /// Vrai si l'objet est visible dans le point de vue
        /*!
        @par Etat
          Minimal
        */
        Base::Booleen ViewPoint::EstVisible
              (const Base::Association<Model::Object>& _modele) const
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
        */
        void ViewPoint::init()
        {
          Base::Traceur::MessageInterne("Entering ViewPoint::init") ;
          
          if (! initialise)
          {

            /// initialisation de Ogre
            VerifieCondition(Racine(),
                             Exception("Pas de racine")) ;

            gestionnaire = Racine()->createSceneManager(::Ogre::ST_GENERIC) ;

            if (! gestionnaire)
            {
              throw Exception("initialisation of ogre failed") ;
            }
            Base::Traceur::MessageInterne("Built scene manager") ;
  
            /// Initialise la racine.
            this->univers = this->vueObservateur->AccesParent<Univers>()->AccesObject() ;
            Base::Traceur::MessageInterne("got universe") ;
            VerifieCondition(this->univers,
                             Exception("pas d'univers pour le point de vue")) ;

            Base::Traceur::MessageInterne("Going to initialise Univers") ;
            this->univers->init() ;

            initialise = Base::VRAI ;
          }
          Base::Traceur::MessageInterne("Leaving ViewPoint::init") ;
          
        }
                
        /// Néttoie le point de vue.
        void ViewPoint::close()
        {
          /// Supprimme tous les éléments de la scène
          if (this->gestionnaire)
          {
            this->gestionnaire->clearScene() ;
          }
          
          /// Termine les objets un par un
          if (this->univers)
          {
            this->univers->close() ;
          }
        }

        void ViewPoint::Activer()
        {
          Base::Traceur::MessageInterne("Entering ViewPoint::Activer") ;
          
          Base::Association<Observateur> observateur(*vueObservateur) ;
          
          Fenetre()->addViewport(observateur->AccesCamera()) ;
        }

        /*!
          @todo
            trouver un truc plus subtil 
            removeViewport(zorder) ?
        */
        void ViewPoint::Desactiver()
        {
          Base::Association<Observateur> observateur(*vueObservateur) ;
         
          Fenetre()->removeAllViewports() ;
        }

          
        ::Ogre::SceneManager* ViewPoint::AccesGestionnaire() const
        {
          return this->gestionnaire ;
        }


        void ViewPoint::ChangerObservateur
          (const Base::Association<Model::Object>& _observateur)
        {
          if (_observateur != vueObservateur->AccesObserve())
          {
            this->Desactiver() ;
            this->vueObservateur = this->RechercherVue(_observateur) ;
            this->Activer() ;
          }
        }


      }
    }
  }
}
