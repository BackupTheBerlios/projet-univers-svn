/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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

#include <model/model.h>
#include <model/computer.h>
#include <model/massive.h>
#include <model/detector.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/solid.h>
#include <model/laser.h>
#include <model/selected.h>
#include <model/detection_data.h>
#include <model/targeting_system.h>
#include <model/ideal_target.h>
#include <model/shooting_helper.h>
#include <model/shootable.h>

#include <model/test/test_shooting_helper.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestShootingHelper) ;


namespace ProjetUnivers {
  namespace Model {
    namespace Test {


      void TestShootingHelper::basicTest()
      {
        InternalMessage("Model","Model::TestShootingHelper::basicTest entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          two ships for detection
          
          we select a target and check the property of the ideal target 
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile()) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getDescendants<IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Positionned* positionned = child->getTrait<Positionned>() ;
        CPPUNIT_ASSERT(positionned) ;
        
        /// ideal position is ship position because it does not move
        CPPUNIT_ASSERT(positionned->getPosition()==Position::Meter(0,0,500)) ;
        
        Model::close() ;
      }

      void TestShootingHelper::testMovingFront()
      {
        InternalMessage("Model","Model::TestShootingHelper::testMovingFront entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target 
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,0,1))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getDescendants<IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Positionned* positionned = child->getTrait<Positionned>() ;
        CPPUNIT_ASSERT(positionned) ;
        CPPUNIT_ASSERT(positionned->getPosition().Meter().z > 500) ;
//        std::cout << positionned->getPosition().Meter() << std::endl ;
        
        Model::close() ;
      }

      void TestShootingHelper::testMovingUnshootable()
      {
        InternalMessage("Model","Model::TestShootingHelper::testMovingUnshootable entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target 
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        float laser_speed_meter_per_second = ship->getTrait<Laser>()->getLaserSpeedMeterPerSecond() ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,0,laser_speed_meter_per_second))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;

        // no ideal target 
        CPPUNIT_ASSERT(data->getDescendants<IdealTarget>().size()==0) ;
        
        Model::close() ;
      }

      void TestShootingHelper::testMovingLateral()
      {
        InternalMessage("Model","Model::TestShootingHelper::testMovingLateral entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target 
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getDescendants<IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Positionned* positionned = child->getTrait<Positionned>() ;
        CPPUNIT_ASSERT(positionned) ;
        CPPUNIT_ASSERT(positionned->getPosition().Meter().z == 500) ;
        CPPUNIT_ASSERT(positionned->getPosition().Meter().y > 0) ;
//        std::cout << positionned->getPosition().Meter() << std::endl ;
        
        Model::close() ;
      }
      
      void TestShootingHelper::destroyComputer()
      {
        InternalMessage("Model","Model::TestShootingHelper::destroyComputer entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
          then we deconnect the computer and pray that no crash happens 
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getDescendants<IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        destroyTrait(ship,ship->getTrait<Computer>()) ;
        
        Model::close() ;
      }

      void TestShootingHelper::destroyLaser()
      {
        InternalMessage("Model","Model::TestShootingHelper::destroyLaser entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
          then we deconnect the laser and pray that no crash happens 
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getDescendants<IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        destroyTrait(ship,ship->getTrait<Laser>()) ;
        
        Model::close() ;
      }
      
      void TestShootingHelper::deconnectComputer()
      {
        InternalMessage("Model","Model::TestShootingHelper::destroyComputer entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
          then we deconnect the computer and pray that no crash happens 
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getDescendants<IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        
        ShootingHelper::connect(ship,NULL,ship) ;
        
        children = data->getDescendants<IdealTarget>() ; 
        CPPUNIT_ASSERT(children.size()==1) ;
        
        Model::close() ;
        InternalMessage("Model","Model::TestShootingHelper::destroyComputer leaving") ;
      }
      
      void TestShootingHelper::testShootable()
      {
        InternalMessage("Model","Model::TestShootingHelper::testShootable entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        CPPUNIT_ASSERT(data->getTrait<Shootable>()) ;
        
        InternalMessage("Model","Model::TestShootingHelper::testShootable leaving") ;
      }

      void TestShootingHelper::testShootableWithRotation()
      {
        InternalMessage("Model","Model::TestShootingHelper::testShootableWithRotation entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented(Orientation(Ogre::Quaternion(Ogre::Degree(-45),Ogre::Vector3::UNIT_Y)))) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(-100,0,100))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        CPPUNIT_ASSERT(data->getTrait<Shootable>()) ;
        
        InternalMessage("Model","Model::TestShootingHelper::testShootableWithRotation leaving") ;
      }
      
      void TestShootingHelper::testNotShootableBehind()
      {
        InternalMessage("Model","Model::TestShootingHelper::testNotShootableBehind entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,-500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;

        CPPUNIT_ASSERT(!data->getTrait<Shootable>()) ;
        
        InternalMessage("Model","Model::TestShootingHelper::testNotShootableBehind leaving") ;
      }

      void TestShootingHelper::testNotShootableOnTheSide()
      {
        InternalMessage("Model","Model::TestShootingHelper::testNotShootableOnTheSide entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship2,new Positionned(Position::Meter(ship2->getTrait<Solid>()->getRadius().Meter()+10,0,400))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;

        CPPUNIT_ASSERT(!data->getTrait<Shootable>()) ;
        
        InternalMessage("Model","Model::TestShootingHelper::testNotShootableOnTheSide leaving") ;
      }

      void TestShootingHelper::testShootableOnTheSide()
      {
        InternalMessage("Model","Model::TestShootingHelper::testShootableOnTheSide entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target
        */
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        addTrait(ship,new Detector(ship)) ;
        addTrait(ship,new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        addTrait(ship,new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship2,new Positionned(Position::Meter(ship2->getTrait<Solid>()->getRadius().Meter()-10,0,400))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile(Speed::MeterPerSecond(0,10,0))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;

        CPPUNIT_ASSERT(data->getTrait<Shootable>()) ;
        
        InternalMessage("Model","Model::TestShootingHelper::testShootableOnTheSide leaving") ;
      }

      void TestShootingHelper::setUp()
      {
      }

      void TestShootingHelper::tearDown()
      {
      }

    }
  }
}
