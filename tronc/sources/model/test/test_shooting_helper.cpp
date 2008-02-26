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
        
        Kernel::Object* ship3 = createObject(system) ;
        addTrait(ship3,new Positionned(Position::Meter(0,500,0))) ;
        addTrait(ship3,new Massive(Mass::Kilogram(1000))) ;
        addTrait(ship3,new Oriented()) ;
        addTrait(ship3,new Mobile()) ;
        addTrait(ship3,new Solid(Mesh("razor.mesh"))) ;
        
        Model::update(Duration::Second(0.1)) ;
        
        // the ships have been detected.
        CPPUNIT_ASSERT(ship->getTrait<Computer>()->getMemoryModel()->getRoots().size() == 2) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Selected>()) ;
        
        // get the ideal target data and check it
        std::set<IdealTarget*> children = data->getDescendants<IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        
        Model::close() ;
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
