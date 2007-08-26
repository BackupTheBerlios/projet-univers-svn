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
#include <kernel/object.h>
#include <kernel/parameters.h>

#include <model/model.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/laser.h>
#include <model/laser_beam.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/implementation/logic.h>

#include <model/test/test_logic_laser_beam.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                LogicTestLaserBeam) ;


namespace ProjetUnivers {
  namespace Model {
    namespace Test {


      void LogicTestLaserBeam::testDisappearing()
      {
        InternalMessage("Model::LogicTestLaserBeam::testDisappearing entering") ;
        // we construct a complete system
        Model::init() ;
        
        // should be a PhysicalWorld
        Kernel::Object* system = createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = createObject("ship",system) ;
        addTrait(ship,new Positionned()) ;
        addTrait(ship,new Oriented()) ;
        addTrait(ship,new Mobile()) ;
        addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship,new Laser(Position(),Orientation())) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model::LogicTestLaserBeam::testDisappearing built ship") ;

//        CPPUNIT_ASSERT(Implementation::Logic::build(system)) ;
//        Implementation::Logic::init() ;

        ship->call("fire") ;

        InternalMessage("Model::LogicTestLaserBeam::testDisappearing fire") ;
        
        // check that system has a new laser beam child
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        
        // simulate Logic during at least 1 seconds : laser beam should still exist
        Model::update(Duration::Second(1)) ;
        
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        
        // simulate Logic during 5 seconds : laser beam should not exist anymore
        Model::update(Duration::Second(5)) ;
        
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==0) ;
        
        // ok
        Model::close() ;
        
      }

      void LogicTestLaserBeam::setUp()
      {
        Kernel::Parameters::load("demonstration.config") ;
       }

      void LogicTestLaserBeam::tearDown()
      {
      }


    }
  }
}
