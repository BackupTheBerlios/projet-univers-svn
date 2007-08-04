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
#include <kernel/model.h>
#include <kernel/object.h>

#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/laser.h>
#include <model/laser_beam.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>

#include <model/test/test_laser.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestLaser) ;


namespace ProjetUnivers {
  namespace Model {
    namespace Test {


      void TestLaser::testFire()
      {
        InternalMessage("Model::TestThrottle::basicTest entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLaser::testFire")) ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Positionned()) ;
        model->addTrait(ship,new Oriented()) ;
        model->addTrait(ship,new Mobile()) ;
        model->addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        model->addTrait(ship,new Laser(Position(),Orientation())) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        ship->call("fire") ;
        
        std::set<Kernel::Object*> objects(system->getChildren()) ;
        // check that system has a new laser beam child
        CPPUNIT_ASSERT(objects.size()==2) ;
        
        int found = 0 ;
                
        for(std::set<Kernel::Object*>::const_iterator object = objects.begin() ;
            object != objects.end() ;
            ++object)
        {
          if ((*object)->getTrait<LaserBeam>())
          {
            ++found ;
            // a laser beam must be a physical object
            CPPUNIT_ASSERT((*object)->getTrait<PhysicalObject>()) ;
            
          }
        }

        CPPUNIT_ASSERT(found==1) ;
        
        
      }
    
      void TestLaser::setUp()
      {
      }
    
      void TestLaser::tearDown()
      {
      }

    }
  }
}
