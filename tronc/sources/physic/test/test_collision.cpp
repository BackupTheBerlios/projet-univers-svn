/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <math.h>
#include <ode/ode.h>

#include <kernel/parameters.h>
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/controler_set.h>

#include <model/model.h>
#include <model/laser.h>
#include <model/laser_beam.h>
#include <model/duration.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/collision.h>

#include <physic/physic.h>
#include <physic/implementation/ode/physic_system.h>

#include <physic/test/test_collision.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Physic::Test::TestCollision) ;

namespace ProjetUnivers
{
  namespace Physic
  {
    namespace Test
    {

      namespace
      {
        /// Acceptable variable for comparison
        const float delta = 1e-4 ;

        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }

      }

      void TestCollision::basicTest()
      {
        InternalMessage("Physic","Physic::Test::TestCollision::basicTest Entering") ;

        /*!
          - build two mesh ships
          - send one against the other
          - check that collision occured
        */

        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCollision::basicTest")) ;
        model->init() ;

        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned(Model::Position::Meter(100,0,0))) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Model::Positionned(Model::Position::Meter(100,-200,0))) ;
        ship2->addTrait(new Model::Oriented()) ;
        ship2->addTrait(new Model::Mobile()) ;
        ship2->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship2->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship2->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship2->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship2->getTrait<Model::PhysicalWorld>()) ;

        /// get the physical viewpoint
        Kernel::ControlerSet* physics = model->getControlerSet<Implementation::Ode::PhysicSystem>() ;
        CPPUNIT_ASSERT(physics) ;

        // send ship2 against ship
        ship2->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,5,0)) ;

        {
          Model::Speed ship_speed = ship->getTrait<Model::Mobile>()->getSpeed() ;

//          std::cout << std::endl << "initial ship speed = " << ship_speed.MeterPerSecond()
//                    << std::endl ;
        }

        const int steps_number = 100 ;
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          physics->simulate(0.1) ;
        }

        /// check that collision has occurred
        unsigned int collision_number = system->getDescendants<Model::Collision>().size() ;
        CPPUNIT_ASSERT(collision_number!=0) ;

        /// again in another direction
        ship2->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-200)) ;
        ship2->getTrait<Model::Oriented>()->setOrientation(Model::Orientation()) ;

        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
        ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation()) ;

        ship2->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,0,5)) ;

        for(int i = 1 ; i <= steps_number ; ++i)
        {
          physics->simulate(0.2) ;
        }

        /// check that more collisions has occured
        CPPUNIT_ASSERT(system->getDescendants<Model::Collision>().size()>collision_number) ;

        InternalMessage("Physic","Physic::Test::TestCollision::basicTest leaving") ;
      }

      void TestCollision::testBugLaser()
      {
        InternalMessage("Physic","Physic::Test::TestCollision::testBugLaser Entering") ;

        /*!
          - build a mesh ship
          - fire
          - check that no collision object exists

          Not really satisfying, even at z=30 the two meshs whould not collide...
        */

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCollision::basicTest")) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship->addTrait(new Model::Laser(Model::Position::Meter(19.2,0,-100),
                                        Model::Orientation(),
                                        Model::Energy::Joule(10))) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        /// get the physical viewpoint
        Kernel::ControlerSet* physics = model->getControlerSet<Implementation::Ode::PhysicSystem>() ;
        CPPUNIT_ASSERT(physics) ;

        InternalMessage("Physic","Physic::Test::TestCollision::testBugLaser built ship") ;

        CPPUNIT_ASSERT(system->getDescendants<Model::Collision>().size()==0) ;

        ship->call("fire") ;

        InternalMessage("Physic","Physic::Test::TestCollision::testBugLaser fire") ;

        CPPUNIT_ASSERT(system->getDescendants<Model::LaserBeam>().size()==1) ;

        physics->simulate(0.1) ;

        // check that no collision occured
        CPPUNIT_ASSERT(system->getDescendants<Model::Collision>().size()==0) ;
        InternalMessage("Physic","Physic::Test::TestCollision::testBugLaser leaving") ;
      }

      void TestCollision::testLaserBeamSolidCollision()
      {
        InternalMessage("Physic","Physic::Test::TestCollision::testLaserBeamSolidCollision Entering") ;

        /*!
          - build a solid object ship
          - launch a laser beam against
          - check that collision object exists
        */

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCollision::testLaserBeamSolidCollision")) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* beam = system->createObject() ;
        beam->addTrait(new Model::Positionned(Model::Position::Meter(0,0,-100))) ;
        beam->addTrait(new Model::Oriented()) ;
        beam->addTrait(new Model::Mobile(Model::Speed::MeterPerSecond(0,0,50))) ;
        beam->addTrait(new Model::Massive(Model::Mass(Model::Energy::Joule(10),
                                                      beam->getTrait<Model::Mobile>()->getSpeed()))) ;
        beam->addTrait(new Model::LaserBeam()) ;
        CPPUNIT_ASSERT(beam->getTrait<Model::PhysicalObject>()) ;

        /// get the physical viewpoint
        Kernel::ControlerSet* physics = model->getControlerSet<Implementation::Ode::PhysicSystem>() ;
        CPPUNIT_ASSERT(physics) ;

        CPPUNIT_ASSERT(system->getDescendants<Model::Collision>().size()==0) ;

        // simulate during 10 seconds
        const int steps_number = 20 ;
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          physics->simulate(0.1) ;
        }

        /// check that collision has occured
        CPPUNIT_ASSERT(system->getDescendants<Model::Collision>().size()!=0) ;
      }

      void TestCollision::testLaserBeamLaserBeamNoCollision()
      {
        /*!
          - build a solid object ship
          - launch a laser beam against
          - check that collision object exists
        */

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCollision::testLaserBeamLaserBeamNoCollision")) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        {
          Kernel::Object* beam = system->createObject() ;
          beam->addTrait(new Model::Positionned(Model::Position::Meter(0,0,0))) ;
          beam->addTrait(new Model::Oriented()) ;
          beam->addTrait(new Model::Mobile()) ;
          beam->addTrait(new Model::LaserBeam()) ;
          beam->addTrait(new Model::Massive(Model::Mass(Model::Energy::Joule(10),
                                                        beam->getTrait<Model::Mobile>()->getSpeed()))) ;
        }

        {
          Kernel::Object* beam = system->createObject() ;
          beam->addTrait(new Model::Positionned(Model::Position::Meter(0,0,-20))) ;
          beam->addTrait(new Model::Oriented()) ;
          beam->addTrait(new Model::Mobile(Model::Speed::MeterPerSecond(0,0,10))) ;
          beam->addTrait(new Model::LaserBeam()) ;
          beam->addTrait(new Model::Massive(Model::Mass(Model::Energy::Joule(10),
                                                        beam->getTrait<Model::Mobile>()->getSpeed()))) ;
        }
        /// get the physical viewpoint
        Kernel::ControlerSet* physics = model->getControlerSet<Implementation::Ode::PhysicSystem>() ;
        CPPUNIT_ASSERT(physics) ;

        // simulate during 10 seconds
        const int steps_number = 100 ;
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          physics->simulate(0.1) ;
        }

        /// check that collision has occured
        unsigned int collision_number = system->getDescendants<Model::Collision>().size() ;
        CPPUNIT_ASSERT(collision_number==0) ;
      }

      void TestCollision::testFire()
      {
        InternalMessage("Physic","Physic::Test::TestCollision::testFire Entering") ;

        /*!
          - build two mesh ship
          - fire
          - check that collision object exists
        */

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCollision::testFire")) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
        ship->addTrait(new Model::Laser(Model::Position::Meter(19.2,0,35),
                                        Model::Orientation(),
                                        Model::Energy::Joule(10))) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        {
          Kernel::Object* ship = system->createObject() ;
          ship->addTrait(new Model::Positionned(Model::Position::Meter(0,0,200))) ;
          ship->addTrait(new Model::Oriented()) ;
          ship->addTrait(new Model::Mobile()) ;
          ship->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
          ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1000))) ;
          CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
          CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        }

        /// get the physical viewpoint
        Kernel::ControlerSet* physics = model->getControlerSet<Implementation::Ode::PhysicSystem>() ;
        CPPUNIT_ASSERT(physics) ;

        InternalMessage("Physic","Physic::Test::TestCollision::testFire built ship") ;

        ship->call("fire") ;

        InternalMessage("Physic","Physic::Test::TestCollision::testFire fire") ;

        CPPUNIT_ASSERT(system->getDescendants<Model::LaserBeam>().size()==1) ;

        Kernel::Object* beam = (*system->getDescendants<Model::LaserBeam>().begin())->getObject() ;
        Model::Positionned* positionned = beam->getTrait<Model::Positionned>() ;

        for(int i = 1 ; i <= 200 ; i++)
        {
          physics->simulate(0.01) ;

//          std::cout << positionned->getPosition().Meter() << std::endl ;
        }

        // check that no collision occured
        CPPUNIT_ASSERT(system->getDescendants<Model::Collision>().size()!=0) ;
        InternalMessage("Physic","Physic::Test::TestCollision::testFire leaving") ;
      }

    }
  }
}
