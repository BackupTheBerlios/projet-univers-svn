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
#include <kernel/log.h>
#include <kernel/error.h>

#include <model/stellar_system.h>

#include <display/exception.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/universe.h>
#include <display/implementation/ogre/observer.h>

#include <display/implementation/ogre/view_point.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {


        ViewPoint::ViewPoint(Model::Object* _observer)
        : Display::ViewPoint(_observer), universe(NULL)
        {

          Kernel::Log::InternalMessage("Entering Ogre::ViewPoint::ViewPoint(const Kernel::Association<Model::Object>&)") ;
          

          Kernel::Log::InternalMessage("Leaving Ogre::ViewPoint::ViewPoint(const Kernel::Association<Model::Object>&)") ;
        
        }
        
        
        /// Vrai si l'objet est visible dans le point de vue
        /*!
        @par Etat
          Minimal
        */
        bool ViewPoint::isVisible(Model::Object* _model) const
        {
          
          return true ;
          
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
          Kernel::Log::InternalMessage("Entering ViewPoint::init") ;
          
          if (! initialised)
          {

            /// initialisation de Ogre
            check(getRoot(),Exception("Pas de racine")) ;

            manager = getRoot()->createSceneManager(::Ogre::ST_GENERIC) ;

            if (! manager)
            {
              throw Exception("initialisation of ogre failed") ;
            }
            Kernel::Log::InternalMessage("Built scene manager") ;
  
            /// Initialise la racine.
            this->universe = this->observerView->getParent<Universe>()->getObject() ;
            Kernel::Log::InternalMessage("got universe") ;
            check(this->universe,
                             Exception("pas d'univers pour le point de vue")) ;

            Kernel::Log::InternalMessage("Going to initialise Univers") ;
            this->universe->init() ;

            initialised = true ;
          }
          Kernel::Log::InternalMessage("Leaving ViewPoint::init") ;
          
        }
                
        /// Néttoie le point de vue.
        void ViewPoint::close()
        {
          /// Supprimme tous les éléments de la scène
          if (this->manager)
          {
            this->manager->clearScene() ;
          }
          
          /// Termine les objets un par un
          if (this->universe)
          {
            this->universe->close() ;
          }
        }

        void ViewPoint::activate()
        {
          Kernel::Log::InternalMessage("Entering ViewPoint::activate") ;
          
          Observer* observer(observerView->getTrait<Observer>()) ;
          
          getWindow()->addViewport(observer->getCamera()) ;
        }

        /*!
          @todo
            trouver un truc plus subtil 
            removeViewport(zorder) ?
        */
        void ViewPoint::desactivate()
        {
          getWindow()->removeAllViewports() ;
        }

          
        ::Ogre::SceneManager* ViewPoint::getManager() const
        {
          return this->manager ;
        }


        void ViewPoint::changeObserver(Model::Object* _observer)
        {
          if (_observer != observerView->getModel())
          {
            this->desactivate() ;
            this->observerView = this->getView(_observer) ;
            this->activate() ;
          }
        }


      }
    }
  }
}
