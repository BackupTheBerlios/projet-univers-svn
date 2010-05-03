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
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/parameters.h>
#include <model/model.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/laser.h>
#include <model/laser_beam.h>
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/destroyable.h>
#include <model/collision.h>
#include <model/shot.h>
#include <model/state.h>
#include <model/active.h>
#include <model/end_of_simulation.h>
#include <model/implementation/logic/logic_system.h>
#include <model/test/test_logic.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestLogic) ;

      void TestLogic::setUp()
      {
        Kernel::Parameters::load("model_demonstration.config") ;
      }

      void TestLogic::testLaserBeamDisappearing()
      {
        InternalMessage("Model","Model::TestLogic::testLaserBeamDisappearing entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positioned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Laser(Position(), Orientation(), Energy::Joule(10))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","Model::TestLogic::testLaserBeamDisappearing built ship") ;

        ship->call(Laser::Fire) ;

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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
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
        model->update(1) ;
        model->update(2) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int )0,system->getChildren().size()) ;
      }

      void TestLogic::testLaserBeamDestroyableCollision()
      {
        InternalMessage("Model","Model::TestLogic::testLaserBeamDestroyableCollision entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Kernel::ControlerSet* logic = model->getControlerSet<
            Implementation::Logic::LogicSystem> () ;
        float timestep = 1 ;
        logic->setTimeStep(1) ;

        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        Destroyable* destroyable = new Destroyable(Model::Energy::Joule(1)) ;
        ship->addTrait(destroyable) ;

        Kernel::Object* firing_ship = system->createObject() ;

        Kernel::Object* beam = system->createObject() ;
        beam->addTrait(new LaserBeam(firing_ship)) ;
        beam->addTrait(new Mobile(Speed::MeterPerSecond(1, 0, 0))) ;
        beam->addTrait(new Massive(Mass::Kilogram(1))) ;

        // a collision
        Kernel::Object* collision = system->createObject() ;
        collision->addTrait(new Collision(beam, ship, Energy::Joule(1))) ;
        collision->addTrait(new Positioned()) ;

        // simulate Logic : destructible should be at 50%
        model->update(1) ;

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5,ship->getTrait<Destroyable>()->getLife(),0.1) ;
      }

      void TestLogic::testShotDisappearing()
      {
        InternalMessage("Model","Model::TestLogic::testShotDisappearing entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model>
            model(
                  new Kernel::Model(
                                    "TestLogic::testLaserBeamDestroyableCollision")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* shot = system->createObject() ;
        shot->addTrait(new Shot()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","Model::TestLogic::testShotDisappearing built ship") ;

        model->update(1) ;

        CPPUNIT_ASSERT(system->getChildren().size()==0) ;
      }

      void TestLogic::endOfSimulation()
      {
        Kernel::Log::Block temp("Model", "TestLogic::endOfSimulation") ;

        std::auto_ptr<Kernel::Model>
            model(new Kernel::Model("TestLogic::endOfSimulation")) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        root->addTrait(new Active()) ;

        Kernel::Object* quit = root->createObject() ;
        quit->setName("quit") ;
        quit->addTrait(new EndOfSimulation()) ;
        quit->addTrait(new State()) ;

        quit->addTrait(new Active()) ;
      }

      void TestLogic::destroyedObjectAreNotThereAnymore()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::ObjectReference ship = system->createObject() ;
        Destroyable* destroyable = new Destroyable(Model::Energy::Joule(1)) ;
        ship->addTrait(destroyable) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        // damage the object
        destroyable->damage(Model::Energy::Joule(1)) ;

        model->update(0.1) ;

        CPPUNIT_ASSERT(!ship) ;
      }

    }
  }
}
