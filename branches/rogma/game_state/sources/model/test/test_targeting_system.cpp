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
#include <model/massive.h>
#include <model/detector.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/solid.h>
#include <model/selected.h>
#include <model/detection_data.h>
#include <model/transponder.h>
#include <model/targeting_system.h>
#include <model/destroyable.h>
#include <model/team.h>

#include <model/test/test_targeting_system.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestTargetingSystem) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      void TestTargetingSystem::selectOneObject()
      {
        InternalMessage("Model","Model::TestTargetingSystem::selectOneObject entering") ;
        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTargetingSystem::selectOneObject")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(ship)) ;
        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("razor.mesh"))) ;

        model->update(0.1) ;
        
        //the second ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin()) ;
        
        CPPUNIT_ASSERT(data->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(data->getTrait<Solid>()) ;
        CPPUNIT_ASSERT(data->getTrait<DetectionData>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected(ship)) ;

        InternalMessage("Model","Model::TestTargetingSystem::selectOneObject leaving") ;
      }

      void TestTargetingSystem::changeSelection()
      {
        InternalMessage("Model","Model::TestTargetingSystem::changeSelection entering") ;
        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTargetingSystem::changeSelection")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(ship)) ;
        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        
        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("razor.mesh"))) ;
        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Positionned(Position::Meter(0,500,0))) ;
        ship3->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship3->addTrait(new Oriented()) ;
        ship3->addTrait(new Mobile()) ;
        ship3->addTrait(new Solid(Mesh("razor.mesh"))) ;
        
        model->update(0.1) ;
        
        // the ships have been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 2) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        
        CPPUNIT_ASSERT(data->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(data->getTrait<Solid>()) ;
        CPPUNIT_ASSERT(data->getTrait<DetectionData>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected(ship)) ;

        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        CPPUNIT_ASSERT(data->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(data->getTrait<Solid>()) ;
        CPPUNIT_ASSERT(data->getTrait<DetectionData>()) ;
        CPPUNIT_ASSERT(! data->getTrait<Selected>()) ;
        
        InternalMessage("Model","Model::TestTargetingSystem::changeSelection leaving") ;
      }

      void TestTargetingSystem::destroyComputer()
      {
        InternalMessage("Model","Model::TestTargetingSystem::destroyComputer entering") ;
        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTargetingSystem::destroyComputer")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(ship)) ;
        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("razor.mesh"))) ;

        model->update(0.1) ;
        
        //the second ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        ship->destroyTrait(ship->getTrait<Computer>()) ;
        
        InternalMessage("Model","Model::TestTargetingSystem::destroyComputer leaving") ;
      }

      void TestTargetingSystem::destroyDetector()
      {
        InternalMessage("Model","Model::TestTargetingSystem::destroyDetector entering") ;
        /*!
          We create a ship with a detector and a second object to detect. 
        */        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTargetingSystem::destroyDetector")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(ship)) ;
        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("razor.mesh"))) ;

        model->update(0.1) ;
        
        //the second ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        ship->destroyTrait(ship->getTrait<Detector>()) ;
        
        InternalMessage("Model","Model::TestTargetingSystem::destroyDetector leaving") ;
      }
      
      void TestTargetingSystem::selectNearestTarget()
      {
        InternalMessage("Model","Model::TestTargetingSystem::selectNearestTarget entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTargetingSystem::selectNearestTarget")) ;
        model->init() ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(ship)) ;
        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        
        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("razor.mesh"))) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Positionned(Position::Meter(0,0,50))) ;
        ship3->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship3->addTrait(new Oriented()) ;
        ship3->addTrait(new Mobile()) ;
        ship3->addTrait(new Solid(Mesh("razor.mesh"))) ;
        
        model->update(0.1) ;
        
        //the second ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 2) ;
        ship->getTrait<TargetingSystem>()->selectNearestTarget() ;

        Kernel::Object* data = ship->getTrait<TargetingSystem>()->getTarget() ;
        
        CPPUNIT_ASSERT(data->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(data->getTrait<Solid>()) ;
        CPPUNIT_ASSERT(data->getTrait<DetectionData>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected(ship)) ;
//        std::cout << data->getTrait<Positionned>()->getPosition().calculateDistance(Position()).Meter() ;
        CPPUNIT_ASSERT(data->getTrait<Positionned>()->getPosition().calculateDistance(Position()).Meter() == 50) ;
        InternalMessage("Model","Model::TestTargetingSystem::selectNearestTarget leaving") ;
      }

      void TestTargetingSystem::selectNearestEnemy()
      {
        InternalMessage("Model","Model::TestTargetingSystem::selectNearestEnemy entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTargetingSystem::selectNearestEnemy")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Team("team2")) ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(ship)) ;
        ship->addTrait(new Transponder(team1)) ;
        
        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        
        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship2->addTrait(new Transponder(team2)) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Positionned(Position::Meter(0,0,50))) ;
        ship3->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship3->addTrait(new Oriented()) ;
        ship3->addTrait(new Mobile()) ;
        ship3->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship3->addTrait(new Transponder(team1)) ;
        
        model->update(0.1) ;
        
        //the second ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 2) ;
        ship->getTrait<TargetingSystem>()->selectNearestEnemy() ;

        Kernel::Object* data = ship->getTrait<TargetingSystem>()->getTarget() ;
        
        CPPUNIT_ASSERT(data) ;
        CPPUNIT_ASSERT(data->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(data->getTrait<Solid>()) ;
        CPPUNIT_ASSERT(data->getTrait<DetectionData>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected(ship)) ;
        CPPUNIT_ASSERT(data->getTrait<Positionned>()->getPosition().calculateDistance(Position()).Meter() == 500) ;
        InternalMessage("Model","Model::TestTargetingSystem::selectNearestEnemy leaving") ;
      }
      
      void TestTargetingSystem::selectNearestEnemyAfterDestruction()
      {
        InternalMessage("Model","Model::TestTargetingSystem::selectNearestEnemyAfterDestruction entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTargetingSystem::selectNearestEnemyAfterDestruction")) ;
        model->init() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Team("team2")) ;

        Kernel::Object* system = model->createObject() ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship->addTrait(new Computer()) ;
        ship->addTrait(new Detector(ship,Distance(Distance::_Meter,10000))) ;
        ship->addTrait(new Transponder(team1)) ;
        
        ship->addTrait(new TargetingSystem()) ;
        TargetingSystem::connect(ship,ship) ;
        
        Kernel::ObjectReference ship2 = system->createObject() ;
        ship2->addTrait(new Positionned(Position::Meter(0,0,500))) ;
        ship2->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship2->addTrait(new Oriented()) ;
        ship2->addTrait(new Mobile()) ;
        ship2->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship2->addTrait(new Transponder(team2)) ;

        Kernel::Object* ship3 = system->createObject() ;
        ship3->addTrait(new Positionned(Position::Meter(0,0,5000))) ;
        ship3->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship3->addTrait(new Oriented()) ;
        ship3->addTrait(new Mobile()) ;
        ship3->addTrait(new Solid(Mesh("razor.mesh"))) ;
        ship3->addTrait(new Transponder(team2)) ;
        
        model->update(0.1) ;
        
        //the second ship has been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 2) ;
        ship->getTrait<TargetingSystem>()->selectNearestEnemy() ;

        Kernel::Object* data = ship->getTrait<TargetingSystem>()->getTarget() ;
        
        CPPUNIT_ASSERT(data) ;
        CPPUNIT_ASSERT(data->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(data->getTrait<Solid>()) ;
        CPPUNIT_ASSERT(data->getTrait<DetectionData>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected(ship)) ;
        CPPUNIT_ASSERT(data->getTrait<Positionned>()->getPosition().calculateDistance(Position()).Meter() == 500) ;
        
        model->destroyObject(ship2) ;
        model->update(0.1) ;

        CPPUNIT_ASSERT(!ship2) ;
        
        ship->getTrait<TargetingSystem>()->selectNearestEnemy() ;
        
        data = ship->getTrait<TargetingSystem>()->getTarget() ;
        CPPUNIT_ASSERT(data) ;
        CPPUNIT_ASSERT(data->getTrait<Positionned>()) ;
        CPPUNIT_ASSERT(data->getTrait<Solid>()) ;
        CPPUNIT_ASSERT(data->getTrait<DetectionData>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected()) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()->isSelected(ship)) ;
        CPPUNIT_ASSERT(data->getTrait<Positionned>()->getPosition().calculateDistance(Position()).Meter() == 5000) ;
        
        InternalMessage("Model","Model::TestTargetingSystem::selectNearestEnemyAfterDestruction leaving") ;
      }
      
      void TestTargetingSystem::setUp() 
      {
      }
      
      void TestTargetingSystem::tearDown() 
      {
      }
    }
  }
}

