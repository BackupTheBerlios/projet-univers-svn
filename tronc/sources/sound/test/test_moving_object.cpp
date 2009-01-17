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
#include <model/duration.h>
#include <model/positionned.h>
#include <model/position.h>
#include <model/oriented.h>
#include <model/listener.h>
#include <model/mobile.h>
#include <model/engine.h>
#include <model/force.h>

#include <sound/sound.h>
#include <sound/test/test_moving_object.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestMovingObject) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

      void TestMovingObject::basicTest()
      {
        std::cerr << "TestMovingObject::basicTest" << std::endl ;
        std::cerr.flush() ;
        /*!
          - build a engine
          - build a listener
          - move the engine position
          - update the module for streaming during 10secondes
          -destroy all and clean sound module
        */

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMovingObject::basicTest")) ;
        model->init() ;
        
        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positionned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        Model::Positionned* listenerPos = new Model::Positionned();
        listener->addTrait(listenerPos) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* engine = system->createObject() ;
        engine->addTrait(new Model::Engine(Model::Force::Newton(10,10,10))) ;
        Model::Positionned* enginePos = new Model::Positionned(Model::Position::Meter(0,0,-50));
        engine->addTrait(enginePos);
        engine->addTrait(new Model::Oriented()) ;
        engine->addTrait(new Model::Mobile());
        
        
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;

        /// moving on Z axis
        while (global_timer.getSecond() <= 10)
        {
          enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0,0.005));
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        /// moving on X axis
        global_timer.reset();
        enginePos->setPosition(Model::Position::Meter(-50,0,0));
        while (global_timer.getSecond() <= 10)
        {
          enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0.005,0,0));
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        /// moving on Y axis
        global_timer.reset();
        enginePos->setPosition(Model::Position::Meter(0,-50,0));
        while (global_timer.getSecond() <= 10)
        {
          enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0.005,0));
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        /// moving on X axis listener and source
        global_timer.reset();
        enginePos->setPosition(Model::Position::Meter(0,0,-100));
        while (global_timer.getSecond() <= 10)
        {
          listenerPos->setPosition(listenerPos->getPosition()+ Model::Position::Meter(0,0,-0.005));
          enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0,0.005));
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        InternalMessage("Sound","after sound close") ;
      }

      void TestMovingObject::setUp() 
      {
      }
      
      void TestMovingObject::tearDown() 
      {
      }
      

    }
  }
}

