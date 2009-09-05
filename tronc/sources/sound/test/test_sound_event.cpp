/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#include <AL/al.h>

#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/timer.h>
#include <kernel/log.h>
#include <kernel/string.h>

#include <model/model.h>
#include <model/duration.h>
#include <model/positioned.h>
#include <model/position.h>
#include <model/oriented.h>
#include <model/orientation.h>
#include <model/listener.h>
#include <model/mobile.h>
#include <model/engine.h>
#include <model/force.h>
#include <model/background_sound.h>
#include <model/sound_environnement.h>
#include <model/collision.h>
#include <model/shot.h>

#include <sound/sound.h>
#include <sound/implementation/openal/openal.h>
#include <sound/test/test_sound_event.h>

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Sound::Test::TestSoundEvent);

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      void TestSoundEvent::collision()
      {
        std::cerr << "TestSoundEvent::collision" << std::endl;
        std::cerr.flush() ;

        /*!
         - build an event object plays ound and destroy it
         - check that the sound is still playing
         */

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSoundEvent::collision"));
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        listener->addTrait(new Model::Positioned()) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* collision = system->createObject() ;
        collision->addTrait(new Model::Collision(system,
            listener)) ;
        collision->addTrait(new Model::Positioned(Model::Position::Meter(10,10,10))) ;

        Kernel::Timer timer;
        Kernel::Timer global_timer;

        while (global_timer.getSecond() <= 1)
        {
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }

      }

      void TestSoundEvent::farCollision()
      {
        std::cerr << "TestSoundEvent::farCollision" << std::endl;
        std::cerr.flush() ;

        /*!
         - build an event object plays ound and destroy it
         - check that the sound is still playing
         */

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSoundEvent::farCollision"));
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        listener->addTrait(new Model::Positioned()) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* collision = system->createObject() ;
        collision->addTrait(new Model::Collision(system,listener)) ;
        collision->addTrait(new Model::Positioned(Model::Position::Meter(0,0,100))) ;

        Kernel::Timer timer;
        Kernel::Timer global_timer;

        while (global_timer.getSecond() <= 1)
        {
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }

      }

      void TestSoundEvent::shot()
      {
        std::cerr << "TestSoundEvent::shot" << std::endl;
        std::cerr.flush() ;

        /*!
         - build an event object plays ound and destroy it
         - check that the sound is still playing
         */

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSoundEvent::shot"));
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        listener->addTrait(new Model::Positioned()) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* collision = system->createObject() ;
        collision->addTrait(new Model::Shot()) ;
        collision->addTrait(new Model::Positioned(Model::Position::Meter(10,10,10))) ;

        Kernel::Timer timer;
        Kernel::Timer global_timer;

        while (global_timer.getSecond() <= 1)
        {
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
      }
      
    }
  }
}

