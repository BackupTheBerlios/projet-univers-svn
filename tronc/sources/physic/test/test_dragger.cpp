/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <model/dragger.h>

#include <physic/physic.h>

#include <physic/test/test_dragger.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Physic::Test::TestDragger) ;

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

      void TestDragger::basicTest()
      {
        InternalMessage("Physic","Physic::Test::TestDragger::basicTest Entering") ;
        /// we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestDragger::basicTest")) ;
        model->init() ;

        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("toto"))) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* dragger = ship->createObject() ;
        dragger->addTrait(new Model::Dragger(1)) ;

        Model::Mobile* mobile = ship->getTrait<Model::Mobile>() ;
        CPPUNIT_ASSERT(mobile) ;

        mobile->setSpeed(Model::Speed::MeterPerSecond(1,0,0)) ;

        CPPUNIT_ASSERT(ship->getModel()) ;

        /// simulation during enought time seconds ...
        const int steps_number = 100 ;
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          model->update(0.1) ;
        }

        Ogre::Vector3 final_speed(mobile->getSpeed().MeterPerSecond()) ;

//        std::cout << "final_speed=" << final_speed << std::endl ;

        CPPUNIT_ASSERT(equal(final_speed.x,0) &&
                       equal(final_speed.y,0) &&
                       equal(final_speed.z,0)) ;


        InternalMessage("Physic","Physic::Test::TestDragger::basicTest leaving") ;
      }


    }
  }
}
