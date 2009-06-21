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
#include <math.h>
#include <ode/ode.h>

#include <kernel/parameters.h>
#include <kernel/model.h>
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/trait.h>

#include <model/model.h>
#include <model/observer.h>
#include <model/massive.h>
#include <model/mobile.h>
#include <model/physical_object.h>
#include <model/physical_world.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/stellar_system.h>
#include <model/solid.h>
#include <model/stabilizer.h>
#include <model/torque_generator.h>
#include <model/universe.h>
#include <model/guidance_system.h>
#include <model/guidance_controler.h>
#include <model/engine.h>
#include <model/engine_controler.h>
#include <model/stick.h>
#include <model/throttle.h>
#include <model/dragger.h>

#include <physic/physic.h>

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physical_object.h>

#include <physic/test/test_model_controler.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Physic::Test::TestModelControler) ;

using namespace ProjetUnivers::Kernel ;

namespace ProjetUnivers 
{
  namespace Physic 
  {
    namespace Test 
    {

      void TestModelControler::oneObjectWithTorqueGenerator()
      {
        InternalMessage("Physic","Physic::Test::TestModelControler::oneObjectWithTorqueGenerator Entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::oneObjectWithTorqueGenerator")) ;
        model->init() ;
        
        Kernel::Object* ship = model->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("toto"))) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        
        Model::Mobile* mobile = ship->getTrait<Model::Mobile>() ;
        CPPUNIT_ASSERT(mobile) ;

        Kernel::Object* st3 = ship->createObject() ;
        st3->addTrait(new Model::Stabilizer(0,3,0)) ;
        st3->addTrait(new Model::Component()) ;
        
        model->update(0.01) ;
        model->update(0.01) ;
        model->update(0.01) ;
        
      }

      void TestModelControler::oneObjectWithForceGenerator()
      {
        InternalMessage("Physic","Physic::Test::TestModelControler::oneObjectWithForceGenerator Entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelControler::oneObjectWithForceGenerator")) ;
        model->init() ;
        
        Kernel::Object* ship = model->createObject() ;
        ship->addTrait(new Model::Positionned()) ;
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile()) ;
        ship->addTrait(new Model::Solid(Model::Mesh("toto"))) ;
        ship->addTrait(new Model::Massive(Model::Mass::Kilogram(1))) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalObject>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Solid>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::PhysicalWorld>()) ;
        
        Model::Mobile* mobile = ship->getTrait<Model::Mobile>() ;
        CPPUNIT_ASSERT(mobile) ;

        Kernel::Object* st3 = ship->createObject() ;
        st3->addTrait(new Model::Engine(Model::Force::Newton(0,0,10))) ;
        st3->addTrait(new Model::Component()) ;
        
        model->update(0.01) ;
        model->update(0.01) ;
        model->update(0.01) ;
        
      }
      
    }
  }
}

