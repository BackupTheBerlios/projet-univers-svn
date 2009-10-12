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
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/solid.h>
#include <model/laser.h>
#include <model/selection.h>
#include <model/detection_data.h>
#include <model/targeting_system.h>
#include <model/ideal_target.h>
#include <model/shooting_helper.h>
#include <model/has_in_line_of_sight.h>

#include <model/test/test_shooting_helper.h>
#include <model/data_connection.h>
#include <model/selection.h>
#include <model/implementation/logic/selection.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestShootingHelper) ;


namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {


      Kernel::Object* TestShootingHelper::createDetectedShip(Kernel::Object* parent)
      {
        Kernel::Object* ship = parent->createObject() ;
        ship->addTrait(new Positioned()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;

        return ship ;
      }

      Kernel::Object* TestShootingHelper::createDetectingShip(Kernel::Object* parent)
      {
        Kernel::Object* ship = parent->createObject() ;
        ship->addTrait(new Positioned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Laser(Position(),Orientation(),Energy::Joule(10))) ;
        ship->addTrait(new Detector()) ;
        Detector::connect(ship,ship) ;

        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        ship->addTrait(new ShootingHelper()) ;
        ShootingHelper::connect(ship,ship,ship) ;

        return ship ;
      }

      Kernel::Object* TestShootingHelper::getIdealTarget(Kernel::Object* ship)
      {
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;

        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;
        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;
        return (*(children.begin()))->getObject() ;
      }

      void TestShootingHelper::basicTest()
      {
        InternalMessage("Model","Model::TestShootingHelper::basicTest entering") ;
        /*!
          we construct a complete system :
          a main ship
          two ships for detection

          we select a target and check the property of the ideal target
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::basicTest")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        // the ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;

        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;
        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Positioned* positioned = child->getTrait<Positioned>() ;
        CPPUNIT_ASSERT(positioned) ;

        /// ideal position is ship position because it does not move
        CPPUNIT_ASSERT_EQUAL(Position::Meter(0,0,500),positioned->getPosition()) ;
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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testMovingFront")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,0,1)) ;

        // the ship has been detected.
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;

        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;

        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Positioned* positioned = child->getTrait<Positioned>() ;
        CPPUNIT_ASSERT(positioned) ;
        CPPUNIT_ASSERT(positioned->getPosition().Meter().z > 500) ;
//        std::cout << positioned->getPosition().Meter() << std::endl ;
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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testMovingUnshootable")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;
        float laser_speed_meter_per_second = ship->getTrait<Laser>()->getLaserSpeedMeterPerSecond() ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,-500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,0,laser_speed_meter_per_second)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        // no ideal target
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;
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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testMovingLateral")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,-500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;

        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;
        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Positioned* positioned = child->getTrait<Positioned>() ;
        CPPUNIT_ASSERT(positioned) ;
        CPPUNIT_ASSERT(positioned->getPosition().Meter().z == -500) ;
        CPPUNIT_ASSERT(positioned->getPosition().Meter().y > 0) ;
//        std::cout << positioned->getPosition().Meter() << std::endl ;
      }

      void TestShootingHelper::testMovingLateralWithRotation()
      {
        InternalMessage("Model","Model::TestShootingHelper::testMovingLateralWithRotation entering") ;
        /*!
          we construct a complete system :
          a main ship
          a ship for detection

          we select a target and check the property of the ideal target
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testMovingLateralWithRotation")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;
        ship->getTrait<Oriented>()->setOrientation(Orientation(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(10,0,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;

        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;
        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Positioned* positioned = child->getTrait<Positioned>() ;
        CPPUNIT_ASSERT(positioned) ;
//        std::cout << positioned->getPosition().Meter() << std::endl ;
        CPPUNIT_ASSERT(positioned->getPosition().Meter().z == 500) ;
        CPPUNIT_ASSERT(positioned->getPosition().Meter().y == 0) ;

        // in local ship space targeted ship goes -x
        CPPUNIT_ASSERT(positioned->getPosition().Meter().x < 0) ;
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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::destroyComputer")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        CPPUNIT_ASSERT(!Kernel::Relation::areLinked<Implementation::Selection>(ship,ship)) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(Kernel::Relation::getLinked<Selection>(ship).size() == 1) ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;
        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;

        CPPUNIT_ASSERT(Kernel::Relation::areLinked<Selection>(ship,ship2)) ;
        CPPUNIT_ASSERT(!Kernel::Relation::areLinked<Selection>(ship,ship)) ;
        CPPUNIT_ASSERT(!Kernel::Relation::areLinked<Implementation::Selection>(ship,ship)) ;

        ship->destroyTrait(ship->getTrait<Computer>()) ;

        CPPUNIT_ASSERT(!Selection::isSelected(ship,ship2)) ;
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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::destroyLaser")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;

        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;
        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;
        ship->destroyTrait(ship->getTrait<Laser>()) ;
      }

      void TestShootingHelper::deconnectComputer()
      {
        InternalMessage("Model","Model::TestShootingHelper::deconnectComputer entering") ;
        /*!
          we construct a complete system :
          a main ship
          a ship for detection

          we select a target and check the property of the ideal target
          then we deconnect the computer and pray that no crash happens
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::deconnectComputer")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;

        std::set<Kernel::Object*>::const_iterator data_pointer
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ;
        Kernel::Object* data = *(data_pointer) ;

        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getChildren<IdealTarget>() ;

        CPPUNIT_ASSERT(children.size()==1) ;

        Kernel::UnLink<DataConnection>(ship,ship) ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().empty()) ;

        InternalMessage("Model","Model::TestShootingHelper::deconnectComputer leaving") ;
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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testShootable")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,-500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(Kernel::Relation::areLinked<HasInLineOfSight>(ship,ship2)) ;

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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testShootableWithRotation")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Positioned()) ;

        Kernel::Object* ship = createDetectingShip(system) ;
        ship->getTrait<Oriented>()->setOrientation(Orientation(::Ogre::Quaternion(::Ogre::Degree(-45),::Ogre::Vector3::UNIT_Y))) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(100,0,-100)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(Kernel::Relation::areLinked<HasInLineOfSight>(ship,ship2)) ;

        Kernel::Object* ideal_target = getIdealTarget(ship) ;
        CPPUNIT_ASSERT(ideal_target) ;

        Positioned* positioned = ideal_target->getTrait<Positioned>() ;
        CPPUNIT_ASSERT(positioned) ;

        Position relative_position(positioned->getPosition()) ;
        Position absolute_position(ship->getTrait<Computer>()->getDataPosition(ideal_target,system)) ;

        CPPUNIT_ASSERT_EQUAL(relative_position+ship->getTrait<Positioned>()->getPosition(),
                             absolute_position) ;

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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testNotShootableBehind")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(!Kernel::Relation::areLinked<HasInLineOfSight>(ship,ship2)) ;

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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testNotShootableOnTheSide")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(ship2->getTrait<Solid>()->getRadius().Meter()+10,0,-400)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(!Kernel::Relation::areLinked<HasInLineOfSight>(ship,ship2)) ;

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
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::testShootableOnTheSide")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(ship2->getTrait<Solid>()->getRadius().Meter()-10,0,-400)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,10,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(Kernel::Relation::areLinked<HasInLineOfSight>(ship,ship2)) ;

        InternalMessage("Model","Model::TestShootingHelper::testShootableOnTheSide leaving") ;
      }

      void TestShootingHelper::idealTargetIsInvariantByRotation()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::idealTargetIsInvariantByRotation")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;
        ship->getTrait<Positioned>()->setPosition(Position::Meter(0,100,0)) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,80,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        // the ship has been detected.
        Kernel::Object* ideal_target = getIdealTarget(ship) ;
        CPPUNIT_ASSERT(ideal_target) ;

        Positioned* positioned = ideal_target->getTrait<Positioned>() ;
        CPPUNIT_ASSERT(positioned) ;

        Position position(positioned->getPosition()) ;

        // rotate detecting ship
        ship->getTrait<Oriented>()->setOrientation(Orientation(::Ogre::Quaternion(::Ogre::Degree(-45),::Ogre::Vector3::UNIT_Y))) ;
        CPPUNIT_ASSERT_EQUAL(position,positioned->getPosition()) ;

        // rotate detecting ship
        ship->getTrait<Oriented>()->setOrientation(Orientation(::Ogre::Quaternion(::Ogre::Degree(45),::Ogre::Vector3::UNIT_X))) ;
        CPPUNIT_ASSERT_EQUAL(position,positioned->getPosition()) ;
      }

      void TestShootingHelper::idealTargetIsInvariantByTranslation()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestShootingHelper::idealTargetIsInvariantByTranslation")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = createDetectingShip(system) ;
        ship->getTrait<Positioned>()->setPosition(Position::Meter(0,100,0)) ;

        Kernel::Object* ship2 = createDetectedShip(system) ;
        ship2->getTrait<Positioned>()->setPosition(Position::Meter(0,0,500)) ;
        ship2->getTrait<Mobile>()->setSpeed(Speed::MeterPerSecond(0,80,0)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        // the ship has been detected.
        Kernel::Object* ideal_target = getIdealTarget(ship) ;
        CPPUNIT_ASSERT(ideal_target) ;

        Positioned* positioned = ideal_target->getTrait<Positioned>() ;
        CPPUNIT_ASSERT(positioned) ;

        Position relative_position(positioned->getPosition()) ;

        Position delta(Position::Meter(10,10,0)) ;

        // translate both ships
        ship->getTrait<Positioned>()->setPosition(ship->getTrait<Positioned>()->getPosition()+delta) ;
        ship2->getTrait<Positioned>()->setPosition(ship2->getTrait<Positioned>()->getPosition()+delta) ;
        CPPUNIT_ASSERT_EQUAL(relative_position,positioned->getPosition()) ;
        CPPUNIT_ASSERT_EQUAL(relative_position,positioned->getPosition()) ;

        delta = Position::Meter(10,-100,-80) ;

        // translate both ships
        ship->getTrait<Positioned>()->setPosition(ship->getTrait<Positioned>()->getPosition()+delta) ;
        ship2->getTrait<Positioned>()->setPosition(ship2->getTrait<Positioned>()->getPosition()+delta) ;
        CPPUNIT_ASSERT_EQUAL(relative_position,positioned->getPosition()) ;
      }

    }
  }
}
