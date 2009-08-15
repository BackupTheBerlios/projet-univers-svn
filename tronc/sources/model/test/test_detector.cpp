/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <model/detector.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/solid.h>
#include <model/massive.h>

#include <model/test/test_detector.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestDetector) ;

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {

      void TestDetector::detectOneObject()
      {
        InternalMessage("Model","Model::TestDetector::detectOneObject entering") ;
        /*!
          We create a ship with a detector and a second object to detect.
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDetector::detectOneObject")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector()) ;
        Detector::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("test_ship.mesh"))) ;

        std::set<Kernel::Object*> detected(ship->getTrait<Computer>()->getDetectedObjects()) ;

        CPPUNIT_ASSERT(!detected.empty()) ;
        CPPUNIT_ASSERT(detected.find(ship2) != detected.end()) ;

        InternalMessage("Model","Model::TestDetector::detectOneObject leaving") ;
      }

      void TestDetector::detectDisappeareance()
      {
        InternalMessage("Model","Model::TestDetector::detectDisappeareance entering") ;

        /*!
          We create a ship with a detector and a second object to detect.
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDetector::detectDisappeareance")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector()) ;
        Detector::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("test_ship.mesh"))) ;

        // the second ship has been detected.
        std::set<Kernel::Object*> detected(ship->getTrait<Computer>()->getDetectedObjects()) ;
        CPPUNIT_ASSERT(!detected.empty()) ;
        CPPUNIT_ASSERT(detected.find(ship2) != detected.end()) ;

        model->destroyObject(ship2) ;

        detected = ship->getTrait<Computer>()->getDetectedObjects() ;
        CPPUNIT_ASSERT(detected.empty()) ;


        InternalMessage("Model","Model::TestDetector::detectDisappeareance leaving") ;
      }

      void TestDetector::detectMovingObject()
      {
        InternalMessage("Model","Model::TestDetector::detectMovingObject entering") ;

        /*!
          We create a ship with a detector and a second object to detect.
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDetector::detectMovingObject")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector()) ;
        Detector::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("test_ship.mesh"))) ;

        // the second ship has been detected.
        std::set<Kernel::Object*> detected(ship->getTrait<Computer>()->getDetectedObjects()) ;
        CPPUNIT_ASSERT(!detected.empty()) ;
        CPPUNIT_ASSERT(detected.find(ship2) != detected.end()) ;

        ship2->getTrait<Positionned>()->setPosition(Position::Meter(0,100,0)) ;

        // the second ship has been detected.
        detected = ship->getTrait<Computer>()->getDetectedObjects() ;
        CPPUNIT_ASSERT(!detected.empty()) ;
        CPPUNIT_ASSERT(detected.find(ship2) != detected.end()) ;

        InternalMessage("Model","Model::TestDetector::detectMovingObject leaving") ;
      }

      void TestDetector::detectObjectMovingOutOfRange()
      {
        InternalMessage("Model","Model::TestDetector::detectObjectMovingOutOfRange entering") ;

        /*!
          We create a ship with a detector and a second object to detect.
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDetector::detectObjectMovingOutOfRange")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(Distance(Distance::_Meter,200))) ;
        Detector::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,100))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("test_ship.mesh"))) ;

        // the second ship has been detected.
        std::set<Kernel::Object*> detected(ship->getTrait<Computer>()->getDetectedObjects()) ;
        CPPUNIT_ASSERT(!detected.empty()) ;
        CPPUNIT_ASSERT(detected.find(ship2) != detected.end()) ;

        ship2->getTrait<Positionned>()->setPosition(Position::Meter(0,500,0)) ;

        // the second ship is out of range
        detected = ship->getTrait<Computer>()->getDetectedObjects() ;
        CPPUNIT_ASSERT(detected.empty()) ;

        InternalMessage("Model","Model::TestDetector::detectObjectMovingOutOfRange leaving") ;
      }

      void TestDetector::testComputerDestruction()
      {
        InternalMessage("Model","Model::TestDetector::testComputerDestruction entering") ;

        /*!
          We create a ship with a detector and a second object to detect.
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDetector::testComputerDestruction")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector()) ;
        Detector::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("test_ship.mesh"))) ;

        InternalMessage("Model","Model::TestDetector::testComputerDestruction destroying computer") ;
        ship->destroyTrait(ship->getTrait<Computer>()) ;
        model->update(0.1) ;

        InternalMessage("Model","Model::TestDetector::testComputerDestruction leaving") ;
      }

      void TestDetector::testDetectorDestruction()
      {
        InternalMessage("Model","Model::TestDetector::testDetectorDestruction entering") ;

        /*!
          We create a ship with a detector and a second object to detect.
        */
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDetector::testDetectorDestruction")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector()) ;
        Detector::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("test_ship.mesh"))) ;

        InternalMessage("Model","Model::TestDetector::testDetectorDestruction destroying computer") ;
        ship->destroyTrait(ship->getTrait<Detector>()) ;

        std::set<Kernel::Object*> detected(ship->getTrait<Computer>()->getDetectedObjects()) ;
        CPPUNIT_ASSERT(detected.empty()) ;

        InternalMessage("Model","Model::TestDetector::testDetectorDestruction leaving") ;
      }


    }
  }
}

