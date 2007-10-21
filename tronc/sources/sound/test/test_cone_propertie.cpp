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
#include <AL/al.h>

#include <OgreQuaternion.h>

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
#include <model/orientation.h>
#include <model/ear.h>
#include <model/mobile.h>
#include <model/engine.h>
#include <model/force.h>

#include <sound/sound.h>
#include <sound/test/test_cone_propertie.h>

#include <cmath>
#include <iostream>
#define PI 3.14

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestConePropertie) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

      void TestConePropertie::basicTest()
      {
        /*!
          - build a engine
          - build a listener
          - move the listener in a circle around the engine
            to heard the variation with the angle.
          
        */
      
        Model::init() ;
        
        Kernel::Object* system = Model::createObject("system") ;
        Model::addTrait(system, new Model::Positionned()) ;
        Model::addTrait(system, new Model::Oriented()) ;

        Kernel::Object* listener = Model::createObject(system) ;
        Model::addTrait(listener,new Model::Ear()) ;
        Model::Positionned* listenerPos = new Model::Positionned(Model::Position::Meter(0,0,0));
        Model::addTrait(listener,listenerPos) ;
        Model::addTrait(listener,new Model::Oriented(Model::Orientation(Ogre::Quaternion(1.0, 0.0, 10.0, 0.0)))) ;
        Model::addTrait(listener,new Model::Mobile());

        Kernel::Object* engine = Model::createObject(system) ;
        Model::addTrait(engine,new Model::Engine(Model::Force::Newton(10,10,10))) ;
        Model::Positionned* enginePos = new Model::Positionned(Model::Position::Meter(0,0,0));
        Model::addTrait(engine,enginePos);
        Model::addTrait(engine,new Model::Oriented(Model::Orientation(Ogre::Quaternion(1.0, 0.0, -10.0, 0.0)))) ;
        Model::addTrait(engine,new Model::Mobile());
        
        /// build a sound viewpoint        
        Sound::init() ;
        Sound::build(listener, system) ;
        
        
        Kernel::Timer timer ;

        float angle = 0;
        int tour = 0;
        while (timer.getSecond() <= 20)
        {
          //variation between 0 and 100% of 2PI
          angle += 0.00005;
          if (angle > 1)
          {
            angle = 0;
            tour++;
          }
          listenerPos->setPosition(Model::Position::Meter(0.0,5*std::cos(angle*2*PI),5*std::sin(angle*2*PI)));
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          Model::update(elapsed) ;
          Sound::update() ;
        }
        
        std::cout << "nbtour:" << tour << std::endl;
        

        
        
        Sound::close();
        Model::close();
        
      }

      void TestConePropertie::setUp() 
      {
      }
      
      void TestConePropertie::tearDown() 
      {
      }
      

    }
  }
}

