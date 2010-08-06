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
#include <kernel/model.h>
#include <kernel/object.h>

#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/engine_controler.h>
#include <model/engine.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/throttle.h>
#include <model/test/test_engine_control.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestEngineControl) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      namespace {
        /// Acceptable variable for comparison 
        const float delta = 0.2 ;
  
        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }
      }

      void TestEngineControl::basicTest()
      {
        InternalMessage("Model","Model::TestEngineControl::basicTest entering") ;
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestEngineControl::basicTest")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positioned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;
        
        Kernel::Object* throttle = ship->createObject() ;
        throttle->addTrait(new Throttle()) ;
        
        Kernel::Object* engine = ship->createObject() ;
        engine->addTrait(new Engine(Force::Newton(0,0,10))) ;

        Kernel::Object* engine_control = ship->createObject() ;
        engine_control->addTrait(new EngineControler()) ;

        connectControlerEngine(engine_control,engine) ;
        connectThrottleControler(throttle,engine_control) ;
        /// now we can test the control...
        {
          /// variables redefines to have direct access to interesting traits
          
          ForceGenerator* engine_trait = engine->getTrait<ForceGenerator>() ;
          CPPUNIT_ASSERT(engine_trait) ;
          Throttle* throttle_trait = throttle->getTrait<Throttle>() ;
          CPPUNIT_ASSERT(throttle) ;
          
          /// basic init check          
          CPPUNIT_ASSERT(engine_trait->getAppliedForce().Newton() == Ogre::Vector3(0,0,0)) ;

          /// set throttle orientation at full thrust... 
          throttle_trait->set(100) ;

          Ogre::Vector3 force(engine_trait->getAppliedForce().Newton()) ;
          CPPUNIT_ASSERT(equal(force.z,10) &&
                         equal(force.x,0) &&
                         equal(force.y,0)) ;

          /// reorient ship...
          ship->getTrait<Oriented>()->setOrientation(
            Ogre::Quaternion(sqrt(0.5),0,sqrt(0.5),0)) ;
          
//          std::cout << engine_trait->getAppliedForce().Newton() ;
          
          CPPUNIT_ASSERT(equal(engine_trait->getAppliedForce().Newton().x,10) && 
                         equal(engine_trait->getAppliedForce().Newton().y,0) &&
                         equal(engine_trait->getAppliedForce().Newton().z,0)) ;

          // change throttle...
          throttle_trait->setOrientation(Ogre::Quaternion(Ogre::Degree(45),Ogre::Vector3::UNIT_X)) ;
          
          CPPUNIT_ASSERT(equal(engine_trait->getAppliedForce().Newton().x,5) && 
                         equal(engine_trait->getAppliedForce().Newton().y,0) &&
                         equal(engine_trait->getAppliedForce().Newton().z,0)) ;
          
        }
      }
      
    }
  }
}

