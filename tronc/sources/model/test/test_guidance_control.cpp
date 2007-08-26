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

#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/guidance_control.h>
#include <model/guidance_system.h>
#include <model/mobile.h>
#include <model/massive.h>

#include <model/test/test_guidance_control.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestGuidanceControl) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      namespace {
        /// Acceptable variable for comparison 
        const float delta = 0.2 ;
  
        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }
        
        const float pi = 3.1415926535 ;
      }


      void TestGuidanceControl::basicTest()
      {
        InternalMessage("Model::TestGuidanceControl::basicTest entering") ;
        /// we construct a complete system on a ship
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestGuidanceControl::basicTest")) ;
        
        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = model->createObject("ship",system) ;
        model->addTrait(ship,new Positionned()) ;
        model->addTrait(ship,new Oriented()) ;
        model->addTrait(ship,new Mobile()) ;
        model->addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;
        
        Kernel::Object* stick = model->createObject("stick",ship) ;
        model->addTrait(stick,new Oriented()) ;
        
        Kernel::Object* guidance_system = model->createObject("guidance_system",ship) ;
        model->addTrait(guidance_system,new GuidanceSystem(1)) ;

        Kernel::Object* guidance_control = model->createObject("guidance_control",ship) ;
        model->addTrait(guidance_control,
                        new GuidanceControl(
                          stick->getTrait<Oriented>(),
                          guidance_system->getTrait<GuidanceSystem>())) ;
        
        /// now we can test the control...
        {
          /// variables redefines to have direct access to interesting traits
          
          GuidanceSystem* guidance_system = model->getObject("guidance_system")->getTrait<GuidanceSystem>() ;
          CPPUNIT_ASSERT(guidance_system) ;
          GuidanceControl* guidance_control = model->getObject("guidance_control")->getTrait<GuidanceControl>() ;
          CPPUNIT_ASSERT(guidance_control) ;
          Oriented* stick = model->getObject("stick")->getTrait<Oriented>() ;
          CPPUNIT_ASSERT(stick) ;
          
          /// basic init check          
          CPPUNIT_ASSERT(guidance_system->NewtonMeter() == Ogre::Vector3(0,0,0)) ;

          /// set stick orientation at full thrust... 
          Ogre::Quaternion orientation(0,1,0,0) ;
          stick->setOrientation(orientation) ;

//          std::cout << guidance_system->NewtonMeter() ;

          CPPUNIT_ASSERT(equal(guidance_system->NewtonMeter().x,-pi) &&
                         equal(guidance_system->NewtonMeter().y,pi) &&
                         equal(guidance_system->NewtonMeter().z,0)) ;

          /// reorient ship...
          ship->getTrait<Oriented>()->setOrientation(
            Ogre::Quaternion(sqrt(0.5),0,sqrt(0.5),0)) ;
          
//          std::cout << guidance_system->NewtonMeter() ;
          
          CPPUNIT_ASSERT(equal(guidance_system->NewtonMeter().x,0) &&
                         equal(guidance_system->NewtonMeter().y,pi) &&
                         equal(guidance_system->NewtonMeter().z,pi)) ;
        }
      }
      
      void TestGuidanceControl::setUp() 
      {
      }
      
      void TestGuidanceControl::tearDown() 
      {
      }
      

    }
  }
}

