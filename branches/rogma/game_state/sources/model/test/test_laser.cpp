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
#include <kernel/model.h>
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
#include <model/shot.h>

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
        InternalMessage("Model","Model::TestLaser::testFire entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLaser::testFire")) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Laser(Position(),Orientation(),Energy::Joule(10))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","built ship") ;

        ship->call("fire") ;

        InternalMessage("Model","fire") ;
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        CPPUNIT_ASSERT(system->getDescendants<Shot>().size()==1) ;
      }

      void TestLaser::beamEnergy()
      {
        InternalMessage("Model","Model::TestLaser::beamEnergy entering") ;
        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLaser::testFire")) ;
        model->init() ;

        // should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positionned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        ship->addTrait(new Laser(Position(),Orientation(),Energy::Joule(10))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalWorld>()) ;

        CPPUNIT_ASSERT(system->getChildren().size()==1) ;

        InternalMessage("Model","built ship") ;

        ship->call("fire") ;

        InternalMessage("Model","fire") ;
        CPPUNIT_ASSERT(system->getDescendants<LaserBeam>().size()==1) ;
        CPPUNIT_ASSERT(system->getDescendants<Shot>().size()==1) ;

        std::set<LaserBeam*> beams = system->getDescendants<LaserBeam>() ;
        LaserBeam* beam = *(beams.begin()) ;
        
        CPPUNIT_ASSERT(beam->getEnergy().Joule()==10) ;
      }
      
      void TestLaser::setUp()
      {
        Kernel::Parameters::load("demonstration.config") ;
       }

      void TestLaser::tearDown()
      {
      }

    }
  }
}
