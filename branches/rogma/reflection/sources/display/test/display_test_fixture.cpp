/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <iostream>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>
#include <kernel/parameters.h>
#include <kernel/command_delegator.h>

#include <model/model.h>
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/universe.h>
#include <model/player.h>
#include <model/active.h>
#include <model/stellar_system.h>

#include <display/implementation/ogre/ogre.h>
#include <display/display.h>
#include <display/test/display_test_fixture.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Test
    {

      Kernel::Object* DisplayTestFixture::createUniverseAndSystem(Kernel::Model* model) const
      {
        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        return system ;
      }

      Kernel::Object* DisplayTestFixture::createObserver(Kernel::Object* parent) const
      {
        Kernel::Object* observer = parent->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->getTrait<Model::Observer>()->setFieldOfView(::Ogre::Degree(70)) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

        return observer ;
      }

      void DisplayTestFixture::simulate(Kernel::Model* model,const float& seconds)
      {
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < seconds)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }
      }

      ::Ogre::ParticleSystem* DisplayTestFixture::getUniqueParticleSystem() const
      {
        ::Ogre::SceneManager::MovableObjectIterator iterator = Implementation::Ogre::getManager()->getMovableObjectIterator(::Ogre::ParticleSystemFactory::FACTORY_TYPE_NAME) ;
        ::Ogre::ParticleSystem* result = NULL ;

        while (iterator.hasMoreElements())
        {
          if (!result)
          {
            result = static_cast< ::Ogre::ParticleSystem* >(iterator.getNext()) ;
            if (!result->isAttached())
              // do not 'count' if the element is not attached (because of pooling)
              result = NULL ;
          }
          else
            // several results
            return NULL ;
        }

        return result ;
      }

      bool DisplayTestFixture::hasOverlay(const std::string& name) const
      {
        // assert the indicator is set
        for (::Ogre::Overlay::Overlay2DElementsIterator element(Implementation::Ogre::getOverlay()->get2DElementsIterator()) ;
             element.hasMoreElements() ;element.moveNext())
        {
          if (element.peekNext()->getName() == name)
            return true ;
        }
        return false ;
      }
    }
  }
}

