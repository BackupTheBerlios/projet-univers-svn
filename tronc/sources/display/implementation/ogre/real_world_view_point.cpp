/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/universe.h>
#include <display/implementation/ogre/observer.h>

#include <display/implementation/ogre/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {


        RealWorldViewPoint::RealWorldViewPoint(Kernel::Object* i_observer)
        : Kernel::ViewPoint(i_observer ? i_observer->getModel() : NULL),
          m_manager(NULL),
          m_observer(i_observer),
          m_root(NULL)
        {
          InternalMessage("Display","Entering Ogre::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
          InternalMessage("Display","Leaving Ogre::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
        }
        
        bool RealWorldViewPoint::isVisible(Kernel::Object* object) const
        {
          // objects must reside in the same Kernel::Model
          return object->getModel() == m_observer->getModel() ; 
          
          /*!
          @todo
            _modele est un parent de l'observateur
            ou 
            _modele est proche de l'observateur (son rapport taille/distance 
            est sup�rieur � une constante)
          */
          
          
        }
          
        Kernel::Object* RealWorldViewPoint::getObserver() const
        {
          return m_observer ;
        }
          
        void RealWorldViewPoint::onInit()
        {
          InternalMessage("Display","RealWorldViewPoint::onInit Entering") ;
          CHECK(getRoot(),"RealWorldViewPoint::onInit no root") ;

          m_manager = getRoot()->createSceneManager(::Ogre::ST_GENERIC) ;

          if (! m_manager)
          {
            throw "initialisation of ogre failed" ;
          }
          
          getCEGUIRenderer()->setTargetSceneManager(m_manager) ;
  
          InternalMessage("Display","RealWorldViewPoint::onInit Leaving") ;
        }
                
        void RealWorldViewPoint::onClose()
        {
          InternalMessage("Display","RealWorldViewPoint::onClose Entering") ;
          /// Supprimme tous les �l�ments de la sc�ne
          if (m_manager)
          {
            m_manager->clearScene() ;
          }
          InternalMessage("Display","RealWorldViewPoint::onClose Leaving") ;
        }

        void RealWorldViewPoint::onChangeObserver(Kernel::Object* _observer)
        {
          /// @ todo
        }
          
        ::Ogre::SceneManager* RealWorldViewPoint::getManager() const
        {
          return m_manager ;
        }

        void RealWorldViewPoint::activate() 
        {
          InternalMessage("Display","Ogre::RealWorldViewPoint::activate Entering") ;
          Observer* observer_view = m_observer->getView<Observer>(this) ;
          CHECK(observer_view,"RealWorldViewPoint::activate no obeserve view") ;
          CHECK(observer_view->getCamera(),"RealWorldViewPoint::activate no camera") ;
          getWindow()->addViewport(observer_view->getCamera()) ;
          InternalMessage("Display","Ogre::RealWorldViewPoint::activate Leaving") ;
        }

        void RealWorldViewPoint::desactivate()
        {
          
        }

        void RealWorldViewPoint::setRootObject(Kernel::Object* root)
        {
          m_root = root ;
        }

        Kernel::Object* RealWorldViewPoint::getRootObject() const
        {
          return m_root ;
        }
      }
    }
  }
}
