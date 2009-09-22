/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/timer.h>
#include <kernel/log.h>
#include <kernel/string.h>

#include <model/model.h>
#include <model/listener.h>
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/background_sound.h>
#include <model/collision.h>

#include <sound/sound.h>
#include <sound/test/test_background_sound.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Sound::Test::TestBackgroundSound);

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      void TestBackgroundSound::basicTest()
      {
        std::cerr << "TestBackgroundSound::basicTest" << std::endl ;
        std::cerr.flush() ;
        
        /*!
         - build a background sound object wih a ogg
         - build an event colision  
         - build a listener
         - destroy the event  before the end of the sound
         - update the module for streaming during 10secondes
         -destroy all and clean sound module
         */

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestBackgroundSound::basicTest"));
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        listener->addTrait(new Model::Positioned()) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* emmiter = system->createObject() ;
        emmiter->addTrait(new Model::BackgroundSound("pu_comm_essai_1.ogg")) ;
        emmiter->addTrait(new Model::Positioned()) ;
        emmiter->addTrait(new Model::Oriented()) ;

        Kernel::Object* elm1 = system->createObject() ;
        Kernel::Object* elm2 = system->createObject() ;
        Kernel::Object* collision = system->createObject() ;
        collision->addTrait(new Model::Collision(elm1,elm2,Model::Energy::Joule(1))) ;
        collision->addTrait(new Model::Positioned()) ;

        InternalMessage("Sound", "fin definition world") ;

        model->destroyObject(collision) ;

        InternalMessage("Sound", "after destroy colision") ;

        Kernel::Timer global_timer;
        Kernel::Timer timer;
        int i = 0;
        while (global_timer.getSecond() <= 10.0)
        {
          ++i;
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }

        InternalMessage("Sound", "i=" + Kernel::toString(i)) ;
      }

      void TestBackgroundSound::wavSound()
      {
        std::cerr << "TestBackgroundSound::wavSound" << std::endl ;
        std::cerr.flush() ;
        InternalMessage("Sound","Enter TestBackgroundSound::wavSound") ;
        
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestBackgroundSound::basicTest"));
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        listener->addTrait(new Model::Positioned()) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* emmiter = system->createObject() ;
        emmiter->addTrait(new Model::BackgroundSound("test.wav")) ;
        emmiter->addTrait(new Model::Positioned()) ;
        emmiter->addTrait(new Model::Oriented()) ;

        Kernel::Timer global_timer;
        Kernel::Timer timer;
        int i = 0;
        while (global_timer.getSecond() <= 2.0)
        {
          ++i;
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        InternalMessage("Sound","Leave TestBackgroundSound::wavSound") ;

      }


    }
  }
}

