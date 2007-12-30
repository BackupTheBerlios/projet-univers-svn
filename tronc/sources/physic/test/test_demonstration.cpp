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
#include <kernel/model.h>
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/trait.h>

#include <model/model.h>
#include <model/observer.h>
#include <model/massive.h>
#include <model/mobile.h>
#include <model/physical_object.h>
#include <model/physical_world.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/stellar_system.h>
#include <model/solid.h>
#include <model/stabilizer.h>
#include <model/torque_generator.h>
#include <model/universe.h>
#include <model/guidance_system.h>
#include <model/guidance_controler.h>
#include <model/engine.h>
#include <model/engine_controler.h>
#include <model/stick.h>
#include <model/throttle.h>
#include <model/dragger.h>

#include <physic/physic.h>

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

#include <physic/test/test_demonstration.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Physic::Test::TestDemonstration) ;

using namespace ProjetUnivers::Kernel ;

namespace ProjetUnivers {
  namespace Physic {
    namespace Test {
      
      /// Acceptable variable for comparison 
      const float delta = 1e-4 ;

      bool equal(float i1,float i2)
      {
        return (fabs(i1 - i2) <= delta) ;
      }


      void TestDemonstration::testBuild()
      {
        InternalMessage("Physic","Physic::Test::TestDemonstration::testBuild Entering") ;
        Model::init() ;
        Model::load("TestDemonstration") ;
        InternalMessage("Physic","Model loaded") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;
        
        InternalMessage("Physic","Physic module initalised") ;
                
        /// check view constructions
        Model::PhysicalWorld* world(observer->getParent<Model::PhysicalWorld>()) ;
        CPPUNIT_ASSERT(world) ;

        InternalMessage("Physic","got Model::PhysicalWorld") ;
        /// check for the world
        CPPUNIT_ASSERT(world->getControler<Implementation::Ode::PhysicalWorld>(physics)) ;
        CPPUNIT_ASSERT(
          world->getControler<Implementation::Ode::PhysicalWorld>(physics)->getWorld()->id()) ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          ship->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;
        
        dMass mass ;
        ship->getControler<Implementation::Ode::PhysicalObject>(physics)
            ->getBody()->getMass(&mass) ;
        
        CPPUNIT_ASSERT(mass.mass) ;
        
        physics->close() ;
        
        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::TestDemonstration::testBuild Leaving") ;
      }

      void TestDemonstration::testSimulateNoMove()
      {
        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateNoMove entering") ;

        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testSimulateNoMove")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;
        
        InternalMessage("Physic","Physic viewpoint initalised") ;

        /// get the ship
        Model::Positionned* positionned(ship->getTrait<Model::Positionned>()) ; 
        CPPUNIT_ASSERT(positionned) ;
        
        Ogre::Vector3 initial_position(positionned->getPosition().Meter()) ;

        InternalMessage("Physic","Physic::Test::testSimulateNoMove got old position") ;
        
        Physic::update() ;

        InternalMessage("Physic","Physic::Test::testSimulateNoMove updated") ;


        Ogre::Vector3 final_position(positionned->getPosition().Meter()) ;

        InternalMessage("Physic","Physic::Test::testSimulate got new position") ;
        
        // check that object has not moved
        CPPUNIT_ASSERT(initial_position == final_position) ;

        InternalMessage("Physic","Physic::Test::testSimulate closing modules") ;

        Physic::close() ;
        InternalMessage("Physic","Physic::Test::testSimulate closed Physic") ;
        Model::close() ;
        InternalMessage("Physic","Physic::Test::testSimulate closed Model") ;

        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateNoMove Leaving") ;
      }

      void TestDemonstration::testSimulateMoving()
      {
        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMoving entering") ;

        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testSimulateMoving")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;
        
        InternalMessage("Physic","Physic viewpoint initalised") ;
        
        /// get the ship and apply a force
        Model::PhysicalObject* object(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(object) ;
        CPPUNIT_ASSERT(object->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          object->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;

        Model::Positionned* positionned(ship->getTrait<Model::Positionned>()) ; 
        CPPUNIT_ASSERT(positionned) ;
        Ogre::Vector3 initial_position(positionned->getPosition().Meter()) ;
        
        /// give an impulse        
        object->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()
              ->addForce(1,0,0) ;
        
        Physic::update(Model::Duration::Second(1)) ;

        InternalMessage("Physic","testSimulateMoving physic updated") ;
        
        dBody* body = object->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody() ;
        
        InternalMessage("Physic","testSimulateMoving body = " +toString((int)body)) ;
        
        CPPUNIT_ASSERT(body) ;
        
        Ogre::Vector3 final_position(positionned->getPosition().Meter()) ;
        
        // check that object has moved
        CPPUNIT_ASSERT(!( initial_position == final_position)) ;


        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMoving closing modules...") ;
        Physic::close() ;
        Model::close() ;
        
        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMoving Leaving") ;
      }

      void TestDemonstration::testRotationTorque()
      {
        InternalMessage("Physic","Physic::Test::testSimulate::testRotationTorque entering") ;

        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testRotationTorque")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned(Model::Position::Meter(100,100,100))) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;
        
        InternalMessage("Physic","Physic viewpoint initalised") ;
        
        /// get the ship and apply a force
        Model::PhysicalObject* object(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(object) ;
        CPPUNIT_ASSERT(object->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          object->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;

        Model::Oriented* oriented(ship->getTrait<Model::Oriented>()) ; 
        CPPUNIT_ASSERT(oriented) ;
        Ogre::Quaternion initial_orientation(oriented->getOrientation().getQuaternion()) ;

        dBody* body = object->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody() ;
        CPPUNIT_ASSERT(body) ;
        
        /// give an impulse        
        body->addTorque(1,0,0) ;
        
        Physic::update(Model::Duration::Second(1)) ;

        Ogre::Quaternion final_orientation(oriented->getOrientation().getQuaternion()) ;

//        std::cout << "final_orientation=" << final_orientation << std::endl ;
        // check that object has turned
        CPPUNIT_ASSERT(!( initial_orientation == final_orientation)) ;

        Physic::close() ;
        Model::close() ;
        
        InternalMessage("Physic","Physic::Test::testSimulate::testRotationTorque Leaving") ;
      }
      
      void TestDemonstration::testSimulateMovingInitialSpeed()
      {
        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMovingInitialSpeed entering") ;

        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testSimulateNoMove")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        /// get the ship and set initial speed
        Model::Mobile* mobile(ship->getTrait<Model::Mobile>()) ;
        CPPUNIT_ASSERT(mobile) ;
        mobile->setSpeed(Model::Speed::MeterPerSecond(1,0,0)) ;
                
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;

        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMovingInitialSpeed initialised physics") ;

        Model::PhysicalObject* object(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(object) ;
        CPPUNIT_ASSERT(object->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          object->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;

        /// store the position before "move"
        Model::Positionned* positionned(ship->getTrait<Model::Positionned>()) ; 
        CPPUNIT_ASSERT(positionned) ;
        Ogre::Vector3 initial_position(positionned->getPosition().Meter()) ;

        Physic::update(Model::Duration::Second(1)) ;

        Ogre::Vector3 final_position(positionned->getPosition().Meter()) ;

        // check that object has correctly moved
        CPPUNIT_ASSERT( initial_position[0]+1 == final_position[0] && 
                        initial_position[1] == final_position[1] &&
                        initial_position[2] == final_position[2]) ;

        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMovingInitialSpeed leaving") ;
      }

      void TestDemonstration::testSimulateMovingInitialRotation()
      {
        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMovingInitialRotation entering") ;

        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testSimulateNoMove")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        /// get the ship and set initial speed
        Model::Mobile* mobile(ship->getTrait<Model::Mobile>()) ;
        CPPUNIT_ASSERT(mobile) ;
        mobile->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,1,0)) ;
                
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;

        /// store the orientation before "rotation"
        Model::Oriented* oriented(ship->getTrait<Model::Oriented>()) ; 
        CPPUNIT_ASSERT(oriented) ;
        Ogre::Quaternion initial_orientation(oriented->getOrientation().getQuaternion()) ;
        
        /// because of approximation of ode, have to split the second in small steps
        const int steps_number = 1000 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(1.0/steps_number)) ;
        }
        
        /// check new orientation
        Ogre::Quaternion final_orientation(oriented->getOrientation().getQuaternion()) ;

        // check that object has rotated a whole turn
        CPPUNIT_ASSERT( equal(-1,final_orientation.w) &&
                        equal(0,final_orientation.x) && 
                        equal(0,final_orientation.y) &&
                        equal(0,final_orientation.z)) ;

        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateMovingInitialRotation leaving") ;
      }
      
      void TestDemonstration::testSimulateRotatingHalfTurn()
      {
        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateRotatingHalfTurn entering") ;

        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testSimulateNoMove")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        /// get the ship and set initial speed
        Model::Mobile* mobile(ship->getTrait<Model::Mobile>()) ;
        CPPUNIT_ASSERT(mobile) ;
        mobile->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,0.5,0)) ;
                
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;

        /// store the orientation before "rotation"
        Model::Oriented* oriented(ship->getTrait<Model::Oriented>()) ; 
        CPPUNIT_ASSERT(oriented) ;
        Ogre::Quaternion initial_orientation(oriented->getOrientation().getQuaternion()) ;
        
        /// because of approximation of ode, have to split the second in small steps
        const int steps_number = 1000 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(1.0/steps_number)) ;
        }
        
        /// check new orientation
        Ogre::Quaternion final_orientation(oriented->getOrientation().getQuaternion()) ;
        
        // check that object has rotated a whole turn
        CPPUNIT_ASSERT( equal(0,final_orientation.w) &&
                        equal(0,final_orientation.x) && 
                        equal(1,final_orientation.y) &&
                        equal(0,final_orientation.z)) ;

        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::testSimulate::testSimulateRotatingHalfTurn leaving") ;
      }

      void TestDemonstration::testStabilizer()
      {
        InternalMessage("Physic","Physic::Test::TestDemonstration::testStabilizer Entering") ;
        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testStabilizer")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        
        Model::Mobile* mobile = ship->getTrait<Model::Mobile>() ;
        CPPUNIT_ASSERT(mobile) ;
        mobile->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,1,0)) ;

        Model::addTrait(ship,new Model::Stabilizer(0,3,0)) ;
     
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;

        /// store the orientation before "rotation"
        Ogre::Quaternion initial_orientation =
          ship->getTrait<Model::Oriented>()
          ->getOrientation().getQuaternion() ;

        InternalMessage("Physic",std::string("testStabilizer initial orientation") 
                                        + " w=" + toString(initial_orientation.w) 
                                        + ",x=" + toString(initial_orientation.x) 
                                        + ",y=" + toString(initial_orientation.y) 
                                        + ",z=" + toString(initial_orientation.z)) ; 


        /// simulation during 1 seconds --> rotation should stop....
        const int steps_number = 10000 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(20.0/steps_number)) ;
        }
        
                
        /// check that angular speed is null.
        Ogre::Vector3 final_angular_speed = 
          ship->getTrait<Model::Mobile>()
          ->getAngularSpeed().TurnPerSecond() ;
        
        //std::cout <<"final_angular_speed=" << final_angular_speed << std::endl ;
        
        CPPUNIT_ASSERT(equal(0,final_angular_speed[0]) && 
                       equal(0,final_angular_speed[1]) &&
                       equal(0,final_angular_speed[2])) ;
        


        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::testSimulate::testStabilizer leaving") ;
        
      }

      void TestDemonstration::testNegativeStabilizer()
      {
        InternalMessage("Physic","Physic::Test::TestDemonstration::testNegativeStabilizer Entering") ;
        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testNegativeStabilizer")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        
        Model::Mobile* mobile = ship->getTrait<Model::Mobile>() ;
        CPPUNIT_ASSERT(mobile) ;
        mobile->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,1,0)) ;

        Model::addTrait(ship,new Model::Stabilizer(3,0,0)) ;
     
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;

        /// store the orientation before "rotation"
        Ogre::Quaternion initial_orientation =
          ship->getTrait<Model::Oriented>()
          ->getOrientation().getQuaternion() ;

        /// simulation during 1 seconds --> rotation should stop....
        const int steps_number = 100 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(5.0/steps_number)) ;
        }
        
                
        /// check that angular speed is still the same.
        Ogre::Vector3 final_angular_speed = 
          ship->getTrait<Model::Mobile>()
          ->getAngularSpeed().TurnPerSecond() ;
        
        //std::cout <<"final_angular_speed=" << final_angular_speed << std::endl ;
        
        CPPUNIT_ASSERT(equal(0,final_angular_speed[0]) && 
                       equal(1,final_angular_speed[1]) &&
                       equal(0,final_angular_speed[2])) ;
        


        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::TestDemonstration::testNegativeStabilizer leaving") ;
        
      }

      void TestDemonstration::testStabilizer2()
      {
        InternalMessage("Physic","Physic::Test::TestDemonstration::testStabilizer2 Entering") ;

        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testStabilizer2")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        
        Model::Mobile* mobile = ship->getTrait<Model::Mobile>() ;
        CPPUNIT_ASSERT(mobile) ;
        mobile->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,-1,0)) ;

        Model::addTrait(ship,new Model::Stabilizer(0,3,0)) ;
     
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;

        /// store the orientation before "rotation"
        Ogre::Quaternion initial_orientation =
          ship->getTrait<Model::Oriented>()
          ->getOrientation().getQuaternion() ;

        InternalMessage("Physic",std::string("testStabilizer initial orientation") 
                                        + " w=" + toString(initial_orientation.w) 
                                        + ",x=" + toString(initial_orientation.x) 
                                        + ",y=" + toString(initial_orientation.y) 
                                        + ",z=" + toString(initial_orientation.z)) ; 


        /// simulation during 1 seconds --> rotation should stop....
        const int steps_number = 10000 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(20.0/steps_number)) ;
        }
        
                
        /// check that angular speed is null.
        Ogre::Vector3 final_angular_speed = 
          ship->getTrait<Model::Mobile>()
          ->getAngularSpeed().TurnPerSecond() ;
        
        //std::cout <<"final_angular_speed=" << final_angular_speed << std::endl ;
        
        CPPUNIT_ASSERT(equal(0,final_angular_speed[0]) && 
                       equal(0,final_angular_speed[1]) &&
                       equal(0,final_angular_speed[2])) ;

        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::testSimulate::testStabilizer2 leaving") ;
        
      }

      void TestDemonstration::testEngine()
      {
        InternalMessage("Physic","Physic::Test::TestDemonstration::testEngine Entering") ;
        Model::init() ;
        Physic::init() ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDemonstration::testStabilizer")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned()) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("toto"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        /// get the ship 
        Model::Positionned* positionned(ship->getTrait<Model::Positionned>()) ;
        CPPUNIT_ASSERT(positionned) ;

        Kernel::Object* throttle = model->createObject("throttle",ship) ;
        model->addTrait(throttle,new Model::Throttle()) ;
        
        Kernel::Object* engine = model->createObject("engine",ship) ;
        model->addTrait(engine,new Model::Engine(Model::Force::Newton(0,0,5000))) ;

        Kernel::Object* engine_control = model->createObject("engine_control",ship) ;
        model->addTrait(engine_control,
                        new Model::EngineControler()) ;

        Model::connectThrottleControler(throttle,engine_control) ;
        Model::connectControlerEngine(engine_control,engine) ;                   
        
        CPPUNIT_ASSERT(throttle) ;
        Model::Throttle* throttle_trait = throttle->getTrait<Model::Throttle>() ;
        CPPUNIT_ASSERT(throttle_trait) ;
        
        throttle_trait->set(100) ;
        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(ship) ;
        physics->init() ;

        /// store the position before simulation
        Ogre::Vector3 initial_position(positionned->getPosition().Meter()) ;

//        std::cout <<"initial_position=" << initial_position << std::endl ;


        /// simulation during 1 seconds ...
        const int steps_number = 10 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(1.0/steps_number)) ;
        }
        
        Ogre::Vector3 final_position(positionned->getPosition().Meter()) ;
        
        CPPUNIT_ASSERT(final_position.z != initial_position.z) ;
        
//        std::cout <<"final_position=" << final_position << std::endl ;
        

        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic","Physic::Test::testSimulate::testEngine leaving") ;
        
      }

      void TestDemonstration::setUp() 
      {
        Kernel::Parameters::load("demonstration.config") ;
      }
      
      void TestDemonstration::tearDown() 
      {
      }

    }
  }
}

