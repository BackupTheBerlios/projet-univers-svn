/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/trait.h>

#include <model/model.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/duration.h>
#include <model/physical_world.h>
#include <model/mobile.h>
#include <model/stabilizer.h>

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
        InternalMessage("Physic::Test::TestDemonstration::testBuild Entering") ;
        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;
        
        InternalMessage("Physic module initalised") ;
                
        /// check view constructions
        Model::PhysicalWorld* world(observer->getParent<Model::PhysicalWorld>()) ;
        CPPUNIT_ASSERT(world) ;

        InternalMessage("got Model::PhysicalWorld") ;
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

        InternalMessage("Physic::Test::TestDemonstration::testBuild Leaving") ;
      }

      void TestDemonstration::testSimulateNoMove()
      {
        InternalMessage("Physic::Test::testSimulate::testSimulateNoMove entering") ;

        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;
        
        InternalMessage("Physic viewpoint initalised") ;

        /// get the ship
        Model::Positionned* ship(Model::getObject("Vaisseau")->getTrait<Model::Positionned>()) ; 
        CPPUNIT_ASSERT(ship) ;
        
        Ogre::Vector3 initial_position(ship->getPosition().Meter()) ;

        InternalMessage("Physic::Test::testSimulateNoMove got old position") ;
        
        Physic::update() ;

        InternalMessage("Physic::Test::testSimulateNoMove updated") ;


        Ogre::Vector3 final_position(ship->getPosition().Meter()) ;

        InternalMessage("Physic::Test::testSimulate got new position") ;
        
        // check that object has not moved
        CPPUNIT_ASSERT(initial_position == final_position) ;

        InternalMessage("Physic::Test::testSimulate closing modules") ;

        Physic::close() ;
        InternalMessage("Physic::Test::testSimulate closed Physic") ;
        Model::close() ;
        InternalMessage("Physic::Test::testSimulate closed Model") ;

        InternalMessage("Physic::Test::testSimulate::testSimulateNoMove Leaving") ;
      }

      void TestDemonstration::testSimulateMoving()
      {
        InternalMessage("Physic::Test::testSimulate::testSimulateMoving entering") ;

        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;
        
        InternalMessage("Physic viewpoint initalised") ;
        
        /// get the ship and apply a force
        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          ship->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;

        Model::Positionned* positionned(Model::getObject("Vaisseau")->getTrait<Model::Positionned>()) ; 
        CPPUNIT_ASSERT(positionned) ;
        Ogre::Vector3 initial_position(positionned->getPosition().Meter()) ;
        
        /// give an impulse        
        ship->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()
            ->addForce(1,0,0) ;
        
        Physic::update(Model::Duration::Second(1)) ;

        InternalMessage("testSimulateMoving physic updated") ;
        
        dBody* body = ship->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody() ;
        
        InternalMessage("testSimulateMoving body = " +toString((int)body)) ;
        
        CPPUNIT_ASSERT(body) ;
        
        Ogre::Vector3 final_position(positionned->getPosition().Meter()) ;
        
        // check that object has moved
        CPPUNIT_ASSERT(!( initial_position == final_position)) ;


        InternalMessage("Physic::Test::testSimulate::testSimulateMoving closing modules...") ;
        Physic::close() ;
        Model::close() ;
        
        InternalMessage("Physic::Test::testSimulate::testSimulateMoving Leaving") ;
      }

      void TestDemonstration::testSimulateMovingInitialSpeed()
      {
        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialSpeed entering") ;

        Model::init() ;
        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialSpeed model initialised") ;
        Model::load("TestDemonstration") ;

        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialSpeed loaded model") ;

        Physic::init() ;

        Object* observer(Model::getObject("Observer")) ;
        {        
          /// get the ship and set initial speed
          Model::Mobile* ship(Model::getObject("Vaisseau")->getTrait<Model::Mobile>()) ;
          CPPUNIT_ASSERT(ship) ;
          ship->setSpeed(Model::Speed::MeterPerSecond(1,0,0)) ;
        }
        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialSpeed built model") ;
                
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;

        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialSpeed initialised physics") ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          ship->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;

        /// store the position before "move"
        Model::Positionned* positionned(Model::getObject("Vaisseau")->getTrait<Model::Positionned>()) ; 
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

        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialSpeed leaving") ;
      }

      void TestDemonstration::testSimulateMovingInitialRotation()
      {
        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialRotation entering") ;

        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;

        {        
          /// get the ship and set initial angular speed
          Model::Mobile* ship(Model::getObject("Vaisseau")->getTrait<Model::Mobile>()) ;
          CPPUNIT_ASSERT(ship) ;
          
          /// one turn per second along the y axis
          ship->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,1,0)) ;
        }
     
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          ship->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;

        /// store the orientation before "rotation"
        Model::Oriented* oriented(Model::getObject("Vaisseau")->getTrait<Model::Oriented>()) ; 
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

        InternalMessage("Physic::Test::testSimulate::testSimulateMovingInitialRotation leaving") ;
      }
      
      void TestDemonstration::testSimulateRotatingHalfTurn()
      {
        InternalMessage("Physic::Test::testSimulate::testSimulateRotatingHalfTurn entering") ;

        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;

        {        
          /// get the ship and set initial angular speed
          Model::Mobile* ship(Model::getObject("Vaisseau")->getTrait<Model::Mobile>()) ;
          CPPUNIT_ASSERT(ship) ;
          
          /// one turn per second along the y axis
          ship->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,0.5,0)) ;
        }
     
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getControler<Implementation::Ode::PhysicalObject>(physics)) ;
        CPPUNIT_ASSERT(
          ship->getControler<Implementation::Ode::PhysicalObject>(physics)->getBody()->id()) ;

        /// store the orientation before "rotation"
        Model::Oriented* oriented(Model::getObject("Vaisseau")->getTrait<Model::Oriented>()) ; 
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

        InternalMessage("Physic::Test::testSimulate::testSimulateRotatingHalfTurn leaving") ;
      }

      void TestDemonstration::testModelPositionUpdate()
      {
        InternalMessage("Physic::Test::TestDemonstration::testModelPositionUpdate Entering") ;
        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        {        
          /// get the ship and set initial speed
          Model::Mobile* ship(Model::getObject("Vaisseau")->getTrait<Model::Mobile>()) ;
          CPPUNIT_ASSERT(ship) ;
          ship->setSpeed(Model::Speed::MeterPerSecond(1,0,0)) ;
        }
        
        /// store old position
        Ogre::Vector3 old_position ;
        {        
          /// get the ship and set initial speed
          Model::Positionned* ship(Model::getObject("Vaisseau")->getTrait<Model::Positionned>()) ;
          CPPUNIT_ASSERT(ship) ;
          old_position = ship->getPosition().Meter() ;
        }
        

        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;

        Physic::update(Model::Duration::Second(1)) ;

        /// get new position
        Ogre::Vector3 new_position ;
        {        
          /// get the ship and set initial speed
          Model::Positionned* ship(Model::getObject("Vaisseau")->getTrait<Model::Positionned>()) ;
          CPPUNIT_ASSERT(ship) ;
          new_position = ship->getPosition().Meter() ;
        }
        InternalMessage(std::string("TestDemonstration::testModelPositionUpdate new position") 
                                        + " x=" + toString(new_position[0]) 
                                        + ",y=" + toString(new_position[1]) 
                                        + ",z=" + toString(new_position[2])) ; 
        
        // check that object has moved
        CPPUNIT_ASSERT( old_position[0]+1 == new_position[0] && 
                        old_position[1] == new_position[1] &&
                        old_position[2] == new_position[2]) ;

        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic::Test::testSimulate::testModelPositionUpdate leaving") ;
      }

      void TestDemonstration::testStabilizer()
      {
        InternalMessage("Physic::Test::TestDemonstration::testStabilizer Entering") ;
        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;

        /// get the ship and set initial angular speed
        Model::Mobile* ship(Model::getObject("Vaisseau")->getTrait<Model::Mobile>()) ;
        CPPUNIT_ASSERT(ship) ;
        
        /// one turn per second along the y axis
        ship->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,1,0)) ;

        Model::addTrait(Model::getObject("Vaisseau"),new Model::Stabilizer(0,3,0)) ;
     
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;

        /// store the orientation before "rotation"
        Ogre::Quaternion initial_orientation =
          Model::getObject("Vaisseau")->getTrait<Model::Oriented>()
          ->getOrientation().getQuaternion() ;

        InternalMessage(std::string("testStabilizer initial orientation") 
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
          Model::getObject("Vaisseau")->getTrait<Model::Mobile>()
          ->getAngularSpeed().TurnPerSecond() ;
        
        std::cout <<"final_angular_speed=" << final_angular_speed << std::endl ;
        
        CPPUNIT_ASSERT(equal(0,final_angular_speed[0]) && 
                       equal(0,final_angular_speed[1]) &&
                       equal(0,final_angular_speed[2])) ;
        


        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic::Test::testSimulate::testStabilizer leaving") ;
        
      }

      void TestDemonstration::testNegativeStabilizer()
      {
        InternalMessage("Physic::Test::TestDemonstration::testStabilizer Entering") ;
        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;

        /// get the ship and set initial angular speed
        Model::Mobile* ship(Model::getObject("Vaisseau")->getTrait<Model::Mobile>()) ;
        CPPUNIT_ASSERT(ship) ;
        
        /// one turn per second along the y axis
        ship->setAngularSpeed(Model::AngularSpeed::TurnPerSecond(0,1,0)) ;
        
        /// a stabilizer in an orthogonal direction form rotation.
        Model::addTrait(Model::getObject("Vaisseau"),new Model::Stabilizer(3,0,0)) ;
     
        /// build a physical viewpoint        
        Kernel::ControlerSet* physics = Physic::build(observer) ;
        physics->init() ;

        /// simulation during 1 seconds --> rotation should stop....
        const int steps_number = 100 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(5.0/steps_number)) ;
        }
        
                
        /// check that angular speed is still the same.
        Ogre::Vector3 final_angular_speed = 
          Model::getObject("Vaisseau")->getTrait<Model::Mobile>()
          ->getAngularSpeed().TurnPerSecond() ;
        
        std::cout <<"final_angular_speed=" << final_angular_speed << std::endl ;
        
        CPPUNIT_ASSERT(equal(0,final_angular_speed[0]) && 
                       equal(1,final_angular_speed[1]) &&
                       equal(0,final_angular_speed[2])) ;
        


        Physic::close() ;
        Model::close() ;

        InternalMessage("Physic::Test::TestDemonstration::testStabilizer leaving") ;
        
      }

      void TestDemonstration::setUp() 
      {
      }
      
      void TestDemonstration::tearDown() 
      {
      }

    }
  }
}

