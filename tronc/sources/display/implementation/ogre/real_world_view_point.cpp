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

        RegisterViewPoint(RealWorldViewPoint) ;

        RealWorldViewPoint::RealWorldViewPoint(Kernel::Model* model)
        : Kernel::ViewPoint(model),
          m_manager(NULL),
          m_observer(NULL),
          m_root(NULL)
        {
          InternalMessage("Display","Entering Ogre::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
          InternalMessage("Display","Leaving Ogre::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
        }
        
        bool RealWorldViewPoint::isVisible(Kernel::Object* object) const
        {
          
          if (! m_observer || !object)
            return true ;
          
          // objects must reside in the same Kernel::Model
          return object->getModel() == m_observer->getModel() ; 
          
          /*!
          @todo
            _modele is a parent of observer
            ou 
            _modele is near from observer (ratio size/distance is less that a 
            given value) 
          */
          
          
        }
          
        Kernel::Object* RealWorldViewPoint::getObserver() const
        {
          return m_observer ;
        }
          
        void RealWorldViewPoint::onInit()
        {
          InternalMessage("Display","RealWorldViewPoint::onInit Entering") ;
          
          Implementation::Ogre::init() ;
          
          CHECK(getRoot(),"RealWorldViewPoint::onInit no root") ;

          m_manager = Ogre::getManager() ;

          if (! m_manager)
          {
            ErrorMessage("initialisation of ogre failed") ;
            throw "initialisation of ogre failed" ;
          }
  
          InternalMessage("Display","RealWorldViewPoint::onInit Leaving") ;
        }
                
        void RealWorldViewPoint::onClose()
        {
          InternalMessage("Display","RealWorldViewPoint::onClose Entering") ;
          /// remove scene elements
          if (m_manager)
          {
            m_manager->clearScene() ;
          }

          getWindow()->removeViewport(0) ;
          
          InternalMessage("Display","RealWorldViewPoint::onClose Leaving") ;
        }

        ::Ogre::SceneManager* RealWorldViewPoint::getManager() const
        {
          return m_manager ;
        }

        void RealWorldViewPoint::setRootObject(Kernel::Object* root)
        {
          m_root = root ;
        }

        Kernel::Object* RealWorldViewPoint::getRootObject() const
        {
          return m_root ;
        }
      
        void RealWorldViewPoint::setObserver(Kernel::Object* observer)
        {
          if (m_observer)
          {
            getWindow()->removeViewport(0) ;
          }
          
          m_observer = observer ;
          if (m_observer)
          {
            Observer* observer_view = m_observer->getView<Observer>(this) ;
            CHECK(observer_view,"RealWorldViewPoint::activate no obeserve view") ;
            CHECK(observer_view->getCamera(),"RealWorldViewPoint::activate no camera") ;
            ::Ogre::Viewport* viewport = getWindow()->addViewport(observer_view->getCamera()) ;
          }
        }
        
        void RealWorldViewPoint::update(const float& seconds)
        {
          Implementation::Ogre::update(seconds) ;
        }
        
      }
    }
  }
}
