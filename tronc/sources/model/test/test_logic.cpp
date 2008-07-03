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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLogic::testLaserBeamDisappearing")) ;
        model->init() ;
        
        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Laser(Position(),Orientation(),Energy::Joule(10))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","Model::TestLogic::testLaserBeamDisappearing built ship") ;

        ship->call("fire") ;

        InternalMessage("Model","Model::TestLogic::testLaserBeamDisappearing fire") ;
        
        // check that system has a new laser beam child
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        
        // simulate Logic during at least 1 seconds : laser beam should still exist
        model->update(1) ;
        
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        
        // simulate Logic during 5 seconds : laser beam should not exist anymore
        model->update(5) ;
        
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==0) ;
      }

      void TestLogic::testDestroyable()
      {
        InternalMessage("Model","Model::TestLogic::testDestroyable entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLogic::testDestroyable")) ;
        model->init() ;
        
        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        Destroyable* destroyable = new Destroyable(Model::Energy::Joule(1)) ; 
        ship->addTrait(destroyable) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        // damage the object
        destroyable->damage(Model::Energy::Joule(0.5)) ;
        
        // simulate Logic : object should still exist
        model->update(1) ;
        
        CPPUNIT_ASSERT(system->getChildren().size()==1) ;
        
        // damage the object --> a kill
        destroyable->damage(Model::Energy::Joule(1.5)) ;
        
        // simulate Logic : object  should not exist anymore
        model->update(2.5) ;
        
        CPPUNIT_ASSERT(system->getChildren().size()==0) ;
      }

      void TestLogic::testLaserBeamDestroyableCollision()
      {
        InternalMessage("Model","Model::TestLogic::testLaserBeamDestroyableCollision entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLogic::testLaserBeamDestroyableCollision")) ;
        model->init() ;
        
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        Destroyable* destroyable = new Destroyable(Model::Energy::Joule(1)) ; 
        ship->addTrait(destroyable) ;

        Kernel::Object* beam = system->createObject() ;
        beam->addTrait(new LaserBeam()) ;
        beam->addTrait(new Mobile(Speed::MeterPerSecond(1,0,0))) ;
        beam->addTrait(new Massive(Mass::Kilogram(1))) ;
        
        // a collision        
        Kernel::Object* collision = system->createObject() ;
        collision->addTrait(new Collision(beam,ship)) ;
        collision->addTrait(new Positionned()) ;
        
        // simulate Logic : destroyable should be at 50%
        model->update(1) ;

        CPPUNIT_ASSERT(ship->getTrait<Destroyable>()->getLife() == 0.5) ;
      }

      void TestLogic::testShotDisappearing()
      {
        InternalMessage("Model","Model::TestLogic::testShotDisappearing entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLogic::testLaserBeamDestroyableCollision")) ;
        model->init() ;
        
        Kernel::Object* system = model->createObject() ;

        Kernel::Object* shot = system->createObject() ;
        shot->addTrait(new Shot()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","Model::TestLogic::testShotDisappearing built ship") ;

        model->update(1) ;
        
        CPPUNIT_ASSERT(system->getChildren().size()==0) ;
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
