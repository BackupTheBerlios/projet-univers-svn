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
#include <model/duration.h>
#include <model/physical_world.h>
#include <model/mobile.h>

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
      const float delta = 1e-5 ;

      bool equal(float i1,float i2)
      {
        return (fabs(i1 - i2) <= delta) ;
      }


      void TestDemonstration::testBuild()
      {
        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        /// build a physical viewpoint        
        Kernel::ViewPoint* physic_viewpoint = Physic::buildRealWorldViewPoint(observer) ;
        physic_viewpoint->init() ;
        
        Kernel::Log::InternalMessage("Physic viewpoint initalised") ;
                
        /// check view constructions
        Model::PhysicalWorld* world(observer->getParent<Model::PhysicalWorld>()) ;
        CPPUNIT_ASSERT(world) ;

        Kernel::Log::InternalMessage("got Model::PhysicalWorld") ;
        /// check for the world
        CPPUNIT_ASSERT(world->getView<Implementation::Ode::PhysicalWorld>(physic_viewpoint)) ;
        CPPUNIT_ASSERT(
          world->getView<Implementation::Ode::PhysicalWorld>(physic_viewpoint)->getWorld()->id()) ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)) ;
        CPPUNIT_ASSERT(
          ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()->id()) ;
        
        dMass mass ;
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)
            ->getBody()->getMass(&mass) ;
        
        CPPUNIT_ASSERT(mass.mass) ;
        
        std::cout << "mass=" << mass.mass << std::endl ;
        physic_viewpoint->close() ;
        
        Physic::close() ;
        Model::close() ;
        
      }

      void TestDemonstration::testSimulateNoMove()
      {
        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        /// build a physical viewpoint        
        Kernel::ViewPoint* physic_viewpoint = Physic::buildRealWorldViewPoint(observer) ;
        physic_viewpoint->init() ;
        
        Kernel::Log::InternalMessage("Physic viewpoint initalised") ;

        /// get the ship
        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)) ;
        CPPUNIT_ASSERT(
          ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()->id()) ;

        /// store the position before simulation
        const dReal* old_position =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getPosition() ;

        dReal x = old_position[0] ;
        dReal y = old_position[1] ;
        dReal z = old_position[2] ;

        Kernel::Log::InternalMessage("Physic::Test::testSimulateNoMove got old position") ;
        
        Physic::update() ;

        Kernel::Log::InternalMessage("Physic::Test::testSimulateNoMove updated") ;


        const dReal* new_position =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getPosition() ;

        Kernel::Log::InternalMessage("Physic::Test::testSimulate got new position") ;
        
        // check that object has not moved
        CPPUNIT_ASSERT(( x == new_position[0] && 
                         y == new_position[1] &&
                         z == new_position[2])) ;

        Kernel::Log::InternalMessage("Physic::Test::testSimulate closing modules") ;

        Physic::close() ;
        Kernel::Log::InternalMessage("Physic::Test::testSimulate closed Physic") ;
        Model::close() ;
        Kernel::Log::InternalMessage("Physic::Test::testSimulate closed Model") ;

        Kernel::Log::InternalMessage("Physic::Test::testSimulate OK") ;
        
      }

      void TestDemonstration::testSimulateMoving()
      {
        Model::init() ;
        Model::load("TestDemonstration") ;
        Physic::init() ;
        Object* observer(Model::getObject("Observer")) ;
        
        /// build a physical viewpoint        
        Kernel::ViewPoint* physic_viewpoint = Physic::buildRealWorldViewPoint(observer) ;
        physic_viewpoint->init() ;
        
        Kernel::Log::InternalMessage("Physic viewpoint initalised") ;
        
        /// get the ship and apply a force
        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)) ;
        CPPUNIT_ASSERT(
          ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()->id()) ;

        /// store the position before "move"
        const dReal* old_position =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getPosition() ;

        dReal x = old_position[0] ;
        dReal y = old_position[1] ;
        dReal z = old_position[2] ;
        
        Kernel::Log::InformationMessage(std::string("testSimulateMoving initial position") 
                                        + " x=" + toString(old_position[0]) 
                                        + ",y=" + toString(old_position[1]) 
                                        + ",z=" + toString(old_position[2])) ; 
        
        /// give an impulse        
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->addForce(1,0,0) ;
        
        Physic::update(Model::Duration::Second(1)) ;
        
        const dReal* new_position =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getPosition() ;
        
        // check that object has moved
        CPPUNIT_ASSERT(!( x == new_position[0] && 
                          y == new_position[1] &&
                          z == new_position[2])) ;

        Kernel::Log::InformationMessage(std::string("testSimulateMoving new position") 
                                        + " x=" + toString(new_position[0]) 
                                        + ",y=" + toString(new_position[1]) 
                                        + ",z=" + toString(new_position[2])) ; 

        Physic::close() ;
        Model::close() ;
        
        
      }

      void TestDemonstration::testSimulateMovingInitialSpeed()
      {
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
                
        /// build a physical viewpoint        
        Kernel::ViewPoint* physic_viewpoint = Physic::buildRealWorldViewPoint(observer) ;
        physic_viewpoint->init() ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)) ;
        CPPUNIT_ASSERT(
          ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()->id()) ;

        /// store the position before "move"
        const dReal* old_position =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getPosition() ;

        dReal x = old_position[0] ;
        dReal y = old_position[1] ;
        dReal z = old_position[2] ;

        Physic::update(Model::Duration::Second(1)) ;
        
        const dReal* new_position =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getPosition() ;
        
        // check that object has moved
        CPPUNIT_ASSERT(!( x == new_position[0] && 
                          y == new_position[1] &&
                          z == new_position[2])) ;

        Kernel::Log::InformationMessage(std::string("testSimulateMovingInitialSpeed new position") 
                                        + " x=" + toString(new_position[0]) 
                                        + ",y=" + toString(new_position[1]) 
                                        + ",z=" + toString(new_position[2])) ; 
        Physic::close() ;
        Model::close() ;

      }
      

      void TestDemonstration::testSimulateMovingInitialRotation()
      {
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
        Kernel::ViewPoint* physic_viewpoint = Physic::buildRealWorldViewPoint(observer) ;
        physic_viewpoint->init() ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)) ;
        CPPUNIT_ASSERT(
          ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()->id()) ;

        /// store the orientation before "rotation"
        const dReal* old_orientation =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getQuaternion() ;
        
        dReal w = old_orientation[0] ;
        dReal x = old_orientation[1] ;
        dReal y = old_orientation[2] ;
        dReal z = old_orientation[3] ;

        Kernel::Log::InformationMessage(std::string("testSimulateMovingInitialSpeed initial orientation") 
                                        + " w=" + toString(old_orientation[0]) 
                                        + ",x=" + toString(old_orientation[1]) 
                                        + ",y=" + toString(old_orientation[2]) 
                                        + ",z=" + toString(old_orientation[3])) ; 
        
        /// because of approximation of ode, have to split the second in small steps
        const int steps_number = 100 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(1/steps_number)) ;
        }
        
        /// check new orientation
        const dReal* new_orientation =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getQuaternion() ;

        Kernel::Log::InformationMessage(std::string("testSimulateMovingInitialSpeed new orientation") 
                                        + " w=" + toString(new_orientation[0]) 
                                        + ",x=" + toString(new_orientation[1]) 
                                        + ",y=" + toString(new_orientation[2]) 
                                        + ",z=" + toString(new_orientation[3])) ; 
        
        // check that object has rotated a whole turn
        CPPUNIT_ASSERT(( w == new_orientation[0] &&
                         x == new_orientation[1] && 
                         y == new_orientation[2] &&
                         z == new_orientation[3])) ;

        Physic::close() ;
        Model::close() ;

      }
      
      void TestDemonstration::testSimulateRotatingHalfTurn()
      {
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
        Kernel::ViewPoint* physic_viewpoint = Physic::buildRealWorldViewPoint(observer) ;
        physic_viewpoint->init() ;

        Model::PhysicalObject* ship(Model::getObject("Vaisseau")->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship) ;
        CPPUNIT_ASSERT(ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)) ;
        CPPUNIT_ASSERT(
          ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()->id()) ;

        /// store the orientation before "rotation"
        const dReal* old_orientation =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getQuaternion() ;
        
        Kernel::Log::InformationMessage(std::string("testSimulateRotatingHalfTurn initial orientation") 
                                        + " w=" + toString(old_orientation[0]) 
                                        + ",x=" + toString(old_orientation[1]) 
                                        + ",y=" + toString(old_orientation[2]) 
                                        + ",z=" + toString(old_orientation[3])) ; 
        
        /// because of approximation of ode, have to split the second in small steps
        const int steps_number = 1000 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(0.5/steps_number)) ;
        }
        
        /// check new orientation
        const dReal* new_orientation =
        ship->getView<Implementation::Ode::PhysicalObject>(physic_viewpoint)->getBody()
            ->getQuaternion() ;

        Kernel::Log::InformationMessage(std::string("testSimulateRotatingHalfTurn new orientation") 
                                        + " w=" + toString(new_orientation[0]) 
                                        + ",x=" + toString(new_orientation[1]) 
                                        + ",y=" + toString(new_orientation[2]) 
                                        + ",z=" + toString(new_orientation[3])) ; 
        
        // check that object has rotated a whole turn
        CPPUNIT_ASSERT( equal(0,new_orientation[0]) &&
                        equal(0,new_orientation[1]) && 
                        equal(1,new_orientation[2]) &&
                        equal(0,new_orientation[3])) ;

        Physic::close() ;
        Model::close() ;

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

