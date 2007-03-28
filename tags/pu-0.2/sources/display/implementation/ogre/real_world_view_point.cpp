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
#include <kernel/object.h>

#include <model/stellar_system.h>

#include <display/exception.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/universe.h>
#include <display/implementation/ogre/observer.h>

#include <display/implementation/ogre/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {


        RealWorldViewPoint::RealWorldViewPoint(Kernel::Object* i_observer)
        : Display::Implementation::RealWorldViewPoint(i_observer), 
          universe(NULL)
        {

          Kernel::Log::InternalMessage("Entering Ogre::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
          Kernel::Log::InternalMessage("Leaving Ogre::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
        
        }
        
        
        /// Vrai si l'objet est visible dans le point de vue
        /*!
        @par Etat
          Minimal
        */
        bool RealWorldViewPoint::isVisible(Kernel::Object* _model) const
        {
          
          return true ;
          
          /*!
          @todo
            _modele est un parent de l'observateur
            ou 
            _modele est proche de l'observateur (son rapport taille/distance 
            est sup�rieur � une constante)
          */
          
          
        }
          
          
        /// Initialise le point de vue
        /*!
        */
        void RealWorldViewPoint::onInit()
        {
          Kernel::Log::InternalMessage("RealWorldViewPoint::onInit Entering") ;
          /// initialisation de Ogre
          check(getRoot(),Exception("Pas de racine")) ;

          manager = getRoot()->createSceneManager(::Ogre::ST_GENERIC) ;

          if (! manager)
          {
            throw Exception("initialisation of ogre failed") ;
          }
  
          Kernel::Log::InternalMessage("RealWorldViewPoint::onInit Leaving") ;
        }
                
        /// N�ttoie le point de vue.
        void RealWorldViewPoint::onClose()
        {
          Kernel::Log::InternalMessage("RealWorldViewPoint::onClose Entering") ;
          /// Supprimme tous les �l�ments de la sc�ne
          if (this->manager)
          {
            this->manager->clearScene() ;
          }
          Kernel::Log::InternalMessage("RealWorldViewPoint::onClose Leaving") ;
        }

        void RealWorldViewPoint::onChangeObserver(Kernel::Object* _observer)
        {
          /// @ todo
        }
          
        ::Ogre::SceneManager* RealWorldViewPoint::getManager() const
        {
          return this->manager ;
        }

        void RealWorldViewPoint::activate() 
        {
          Kernel::Log::InternalMessage("Ogre::RealWorldViewPoint::activate Entering") ;
          Observer* observer_view = observer->getView<Observer>(this) ;
          getWindow()->addViewport(observer_view->getCamera()) ;
          Kernel::Log::InternalMessage("Ogre::RealWorldViewPoint::activate Leaving") ;
        }
      }
    }
  }
}
