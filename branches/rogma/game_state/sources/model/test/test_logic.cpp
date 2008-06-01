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
#include <kernel/parameters.h>

#include <model/model.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/laser.h>
#include <model/laser_beam.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/destroyable.h>
#include <model/collision.h>
#include <model/shot.h>

#include <model/test/test_logic.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestLogic) ;


namespace ProjetUnivers {
  namespace Model {
    namespace Test {


      void TestLogic::testLaserBeamDisappearing()
      {
        InternalMessage("Model","Model::TestLogic::testLaserBeamDisappearing entering") ;
        // we construct a complete system
        Model::init() ;
        
        // should be a PhysicalWorld
        Kernel::Object* system = createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Laser(Position(),Orientation(),Energy::Joule(10))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","Model::TestLogic::testLaserBeamDisappearing built ship") ;

//        CPPUNIT_ASSERT(Implementation::Logic::build(system)) ;
//        Implementation::Logic::init() ;

        ship->call("fire") ;

        InternalMessage("Model","Model::TestLogic::testLaserBeamDisappearing fire") ;
        
        // check that system has a new laser beam child
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        
        // simulate Logic during at least 1 seconds : laser beam should still exist
        Model::update(Duration::Second(1)) ;
        
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        
        // simulate Logic during 5 seconds : laser beam should not exist anymore
        Model::update(Duration::Second(5)) ;
        
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==0) ;
        
        // ok
        Model::close() ;
        
      }

      void TestLogic::testDestroyable()
      {
        InternalMessage("Model","Model::TestLogic::testDestroyable entering") ;
        // we construct a complete system
        Model::init() ;
        
        // should be a PhysicalWorld
        Kernel::Object* system = createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = createObject("ship",system) ;
        Destroyable* destroyable = new Destroyable(Model::Energy::Joule(1)) ; 
        addTrait(ship,destroyable) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        // damage the object
        destroyable->damage(Model::Energy::Joule(0.5)) ;
        
        // simulate Logic : object should still exist
        Model::update(Duration::Second(1)) ;
        
        CPPUNIT_ASSERT(system->getChildren().size()==1) ;
        
        // damage the object --> a kill
        destroyable->damage(Model::Energy::Joule(1.5)) ;
        
        // simulate Logic : object  should not exist anymore
        Model::update(Duration::Second(2.5)) ;
        
        CPPUNIT_ASSERT(system->getChildren().size()==0) ;
        
        // ok
        Model::close() ;
        
      }

      void TestLogic::testLaserBeamDestroyableCollision()
      {
        InternalMessage("Model","Model::TestLogic::testLaserBeamDestroyableCollision entering") ;
        // we construct a complete system
        Model::init() ;
        
        Kernel::Object* system = createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = createObject("ship",system) ;
        Destroyable* destroyable = new Destroyable(Model::Energy::Joule(1)) ; 
        addTrait(ship,destroyable) ;

        Kernel::Object* beam = createObject("beam",system) ;
        addTrait(beam,new LaserBeam()) ;
        addTrait(beam,new Mobile(Speed::MeterPerSecond(1,0,0))) ;
        addTrait(beam,new Massive(Mass::Kilogram(1))) ;
        
        // a collision        
        Kernel::Object* collision = createObject("collision",system) ;
        addTrait(collision,new Collision(beam,ship,Position())) ;
        
        // simulate Logic : destroyable should be at 50%
        Model::update(Duration::Second(1)) ;

        CPPUNIT_ASSERT(ship->getTrait<Destroyable>()->getLife() == 0.5) ;
        
        // ok
        Model::close() ;
        
      }

      void TestLogic::testShotDisappearing()
      {
        InternalMessage("Model","Model::TestLogic::testShotDisappearing entering") ;
        // we construct a complete system
        Model::init() ;
        
        // should be a PhysicalWorld
        Kernel::Object* system = createObject("system") ;

        Kernel::Object* shot = createObject("shot",system) ;
        addTrait(shot,new Shot()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","Model::TestLogic::testShotDisappearing built ship") ;

        Model::update(Duration::Second(1)) ;
        
        CPPUNIT_ASSERT(system->getChildren().size()==0) ;
        
        // ok
        Model::close() ;
        
      }

      void TestLogic::setUp()
      {
        Kernel::Parameters::load("demonstration.config") ;
       }

      void TestLogic::tearDown()
      {
      }


    }
  }
}
