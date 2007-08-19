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

#include <kernel/parameters.h>
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/controler_set.h>

#include <model/duration.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/mobile.h>
#include <model/massive.h>

#include <physic/physic.h>

#include <physic/test/test_collision.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Physic::Test::TestCollision) ;

namespace ProjetUnivers {
  namespace Physic {
    namespace Test {

      namespace
      {
        /// Acceptable variable for comparison 
        const float delta = 1e-4 ;

        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }
        
      }

      void TestCollision::basicTest()
      {
        InternalMessage("Physic::Test::TestCollision::basicTest Entering") ;

        /*!
          - build two mesh ships 
          - send one against the other
          - check that the second has moved
        */

        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestCollision::basicTest")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Model::Positionned(Model::Position::Meter(100,0,0))) ;
        model->addTrait(ship,new Model::Oriented()) ;
        model->addTrait(ship,new Model::Mobile()) ;
        model->addTrait(ship,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        model->addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        
        Kernel::Object* ship2 = model->createObject("ship2",system) ;
        model->addTrait(ship2,new Model::Positionned(Model::Position::Meter(100,-200,0))) ;
        model->addTrait(ship2,new Model::Oriented()) ;
        model->addTrait(ship2,new Model::Mobile()) ;
        model->addTrait(ship2,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        model->addTrait(ship2,new Model::Massive(Model::Mass::Kilogram(1000))) ;

        CPPUNIT_ASSERT(ship2->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship2->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship2->getTrait<Model::PhysicalWorld>()) ;
        
        // send ship2 against ship 
        ship2->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,5,0)) ;
        
        /// build a physical viewpoint        
        Physic::init() ;
        Kernel::ControlerSet* physics = Physic::build(ship) ;

        {
          Model::Speed ship_speed = ship->getTrait<Model::Mobile>()->getSpeed() ;
          
          std::cout << std::endl << "initial ship speed = " << ship_speed.MeterPerSecond() 
                    << std::endl ;
        }

        const int steps_number = 100 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(0.1)) ;
        }
        
        /// check that collision has occured
        {
          Model::Speed ship_speed = ship->getTrait<Model::Mobile>()->getSpeed() ;
          
          std::cout << std::endl << "final ship speed = " << ship_speed.MeterPerSecond() 
                    << std::endl ;
        }

        /// again in another direction
        ship2->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-200)) ;
        ship2->getTrait<Model::Oriented>()->setOrientation(Model::Orientation()) ;

        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,0)) ;
        ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation()) ;

        ship2->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,0,5)) ;

        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(0.1)) ;
        }
        
        Physic::close() ;

        InternalMessage("Physic::Test::TestCollision::basicTest leaving") ;
        
      }

      void TestCollision::setUp() 
      {
        Kernel::Parameters::load("demonstration.config") ;
      }
      
      void TestCollision::tearDown() 
      {
      }

    }
  }
}
