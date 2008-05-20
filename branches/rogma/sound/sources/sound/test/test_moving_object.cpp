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
        /*!
          - build a engine
          - build a listener
          - move the engine position
          - update the module for streaming during 10secondes
          -destroy all and clean sound module
        */

        // we construct a complete system
        Model::init() ;
        
        Kernel::Object* system = Model::createObject("system") ;
        Model::addTrait(system, new Model::Positionned()) ;
        Model::addTrait(system, new Model::Oriented()) ;

        Kernel::Object* listener = Model::createObject(system) ;
        Model::addTrait(listener,new Model::Listener()) ;
        Model::Positionned* listenerPos = new Model::Positionned();
        Model::addTrait(listener,listenerPos) ;
        Model::addTrait(listener,new Model::Oriented()) ;
        Model::addTrait(listener,new Model::Mobile());

        Kernel::Object* engine = Model::createObject(system) ;
        Model::addTrait(engine,new Model::Engine(Model::Force::Newton(10,10,10))) ;
        Model::Positionned* enginePos = new Model::Positionned(Model::Position::Meter(0,0,-50));
        Model::addTrait(engine,enginePos);
        Model::addTrait(engine,new Model::Oriented()) ;
        Model::addTrait(engine,new Model::Mobile());
        
        /// build a sound viewpoint        
        Sound::init() ;
        Sound::build(listener, system) ;
        
        
        Kernel::Timer timer ;

        /// moving on Z axis
        while (timer.getSecond() <= 10)
        {
           enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0,0.005));
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          Model::update(elapsed) ;
          Sound::update() ;
        }
        
        /// moving on X axis
        timer.reset();
        enginePos->setPosition(Model::Position::Meter(-50,0,0));
        while (timer.getSecond() <= 10)
        {
           enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0.005,0,0));
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          Model::update(elapsed) ;
          Sound::update() ;
        }
        
        /// moving on Y axis
        timer.reset();
        enginePos->setPosition(Model::Position::Meter(0,-50,0));
        while (timer.getSecond() <= 10)
        {
           enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0.005,0));
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          Model::update(elapsed) ;
          Sound::update() ;
        }
        
        /// moving on X axis listener and source
        timer.reset();
        enginePos->setPosition(Model::Position::Meter(0,0,-100));
        while (timer.getSecond() <= 10)
        {
           listenerPos->setPosition(listenerPos->getPosition()+ Model::Position::Meter(0,0,-0.005));
           enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0,0.005));
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          Model::update(elapsed) ;
          Sound::update() ;
        }
        
        Sound::close();
        Model::close();
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

