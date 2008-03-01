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

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      void TestDetector::detectOneObject()
      {
        InternalMessage("Model","Model::TestDetector::detectOneObject entering") ;
        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Detector(ship)) ;

        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile()) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;

        Model::update(Duration::Second(0.1)) ;
        
        // The second ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        
        CPPUNIT_ASSERT((*data_pointer)->getTrait<Positionned>()) ;
        Position position = (*data_pointer)->getTrait<Positionned>()->getPosition() ;
        float distance = position.Meter().length() ;
        CPPUNIT_ASSERT(distance != 0) ;
        
        InternalMessage("Model","Model::TestDetector::detectOneObject leaving") ;
      }

      void TestDetector::detectDisappeareance()
      {
        InternalMessage("Model","Model::TestDetector::detectDisappeareance entering") ;

        /*!
          We create a ship with a detector and a second object to detect. 
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
        addTrait(ship,new Detector(ship)) ;

        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile()) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
                

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;

        Model::update(Duration::Second(0.1)) ;
        
        //the second chip has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        destroyObject(ship2) ;
        Model::update(Duration::Second(0.1)) ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;
        
        InternalMessage("Model","Model::TestDetector::detectDisappeareance leaving") ;
        
      }

      void TestDetector::detectMovingObject()
      {
        InternalMessage("Model","Model::TestDetector::detectMovingObject entering") ;

        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Detector(ship)) ;

        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile()) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
                

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        //the second chip has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        Kernel::Object* detection 
          = *(ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin()) ;
        CPPUNIT_ASSERT(detection->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(detection->getTrait<Positionned>()->getPosition() == Position::Meter(0,0,500)) ;
        
        ship2->getTrait<Positionned>()->setPosition(Position::Meter(0,100,0)) ;
        Model::update(Duration::Second(0.1)) ;
        
        CPPUNIT_ASSERT(detection->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(detection->getTrait<Positionned>()->getPosition() == Position::Meter(0,100,0)) ;
        
        
        InternalMessage("Model","Model::TestDetector::detectMovingObject leaving") ;
      }

      void TestDetector::detectObjectMovingOutOfRange()
      {
        InternalMessage("Model","Model::TestDetector::detectObjectMovingOutOfRange entering") ;

        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Detector(ship,Distance(Distance::_Meter,200))) ;

        
        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,100))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile()) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;
                

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        //the second chip has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        Kernel::Object* detection 
          = *(ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin()) ;
        CPPUNIT_ASSERT(detection->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(detection->getTrait<Positionned>()->getPosition() == Position::Meter(0,0,100)) ;
        
        ship2->getTrait<Positionned>()->setPosition(Position::Meter(0,500,0)) ;
        Model::update(Duration::Second(0.1)) ;
        
        // there is no more object         
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;
        
        InternalMessage("Model","Model::TestDetector::detectObjectMovingOutOfRange leaving") ;
      }

      void TestDetector::testComputerDestruction()
      {
        InternalMessage("Model","Model::TestDetector::testComputerDestruction entering") ;

        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Detector(ship)) ;

        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile()) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;
        Model::update(Duration::Second(0.1)) ;

        InternalMessage("Model","Model::TestDetector::testComputerDestruction destroying computer") ;
        destroyTrait(ship,ship->getTrait<Computer>()) ;
        Model::update(Duration::Second(0.1)) ;

        InternalMessage("Model","Model::TestDetector::testComputerDestruction leaving") ;
      }
      
      void TestDetector::testDetectorDestruction()
      {
        InternalMessage("Model","Model::TestDetector::testDetectorDestruction entering") ;

        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        Model::init() ;

        Kernel::Object* system = createObject("system") ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
        addTrait(ship,new Computer()) ;
        addTrait(ship,new Detector(ship)) ;

        Kernel::Object* ship2 = createObject(system) ;
        addTrait(ship2,new Positionned(Position::Meter(0,0,500))) ;
        addTrait(ship2,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship2,new Oriented()) ;
        addTrait(ship2,new Mobile()) ;
        addTrait(ship2,new Solid(Mesh("razor.mesh"))) ;

        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 0) ;
        Model::update(Duration::Second(0.1)) ;

        InternalMessage("Model","Model::TestDetector::testDetectorDestruction destroying computer") ;
        destroyTrait(ship,ship->getTrait<Detector>()) ;
        Model::update(Duration::Second(0.1)) ;

        InternalMessage("Model","Model::TestDetector::testDetectorDestruction leaving") ;
      }

      void TestDetector::setUp() 
      {
      }
      
      void TestDetector::tearDown() 
      {
      }
      

    }
  }
}

