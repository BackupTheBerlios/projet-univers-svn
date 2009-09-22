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
#include <model/guidance_controler.h>
#include <model/guidance_system.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/stick.h>

#include <model/test/test_guidance_control.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestGuidanceControl) ;

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {

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
        InternalMessage("Model","Model::TestGuidanceControl::basicTest entering") ;
        /// we construct a complete system on a ship
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestGuidanceControl::basicTest")) ;

        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positioned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;

        Kernel::Object* stick = ship->createObject() ;
        stick->addTrait(new Oriented()) ;

        Kernel::Object* guidance_system = ship->createObject() ;
        guidance_system->addTrait(new GuidanceSystem(1)) ;

        Kernel::Object* guidance_control = ship->createObject() ;
        guidance_control->addTrait(new GuidanceControler()) ;

        connectStickControler(stick,guidance_control) ;
        connectControlerGuidanceSystem(guidance_control,guidance_system) ;

        /// now we can test the control...
        {
          /// variables redefines to have direct access to interesting traits

          GuidanceSystem* guidance_system_trait = guidance_system->getTrait<GuidanceSystem>() ;
          CPPUNIT_ASSERT(guidance_system_trait) ;
          GuidanceControler* guidance_control_trait = guidance_control->getTrait<GuidanceControler>() ;
          CPPUNIT_ASSERT(guidance_control_trait) ;
          Oriented* stick_trait = stick->getTrait<Oriented>() ;
          CPPUNIT_ASSERT(stick_trait) ;

          /// basic init check
          CPPUNIT_ASSERT(guidance_system_trait->NewtonMeter() == Ogre::Vector3(0,0,0)) ;

          Ogre::Quaternion orientation(0,1,0,0) ;
          stick_trait->setOrientation(orientation) ;

          CPPUNIT_ASSERT(equal(guidance_system_trait->NewtonMeter().x,pi) &&
                         equal(guidance_system_trait->NewtonMeter().y,pi) &&
                         equal(guidance_system_trait->NewtonMeter().z,0)) ;

          /// reorient ship...
          ship->getTrait<Oriented>()->setOrientation(
            Ogre::Quaternion(sqrt(0.5),0,sqrt(0.5),0)) ;

          CPPUNIT_ASSERT(equal(guidance_system_trait->NewtonMeter().x,0) &&
                         equal(guidance_system_trait->NewtonMeter().y,pi) &&
                         equal(guidance_system_trait->NewtonMeter().z,-pi)) ;
        }
      }

      void TestGuidanceControl::fullRigth()
      {
        InternalMessage("Model","Model::TestGuidanceControl::basicTest entering") ;
        /// we construct a complete system on a ship
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestGuidanceControl::basicTest")) ;

        /// should be a PhysicalWorld
        Kernel::Object* system = model->createObject() ;
        CPPUNIT_ASSERT(system->getTrait<PhysicalWorld>()) ;

        Kernel::Object* ship = system->createObject() ;
        ship->addTrait(new Positioned()) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Mobile()) ;
        ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
        CPPUNIT_ASSERT(ship->getTrait<PhysicalObject>()) ;

        Kernel::Object* stick = ship->createObject() ;
        stick->addTrait(new Stick()) ;

        Kernel::Object* guidance_system = ship->createObject() ;
        guidance_system->addTrait(new GuidanceSystem(1)) ;

        Kernel::Object* guidance_control = ship->createObject() ;
        guidance_control->addTrait(new GuidanceControler()) ;

        connectStickControler(stick,guidance_control) ;
        connectControlerGuidanceSystem(guidance_control,guidance_system) ;

        // 100 on yaw means go rigth
        stick->call(Stick::Yaw,100) ;
        stick->getTrait<Stick>()->updateOrientation() ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().x == 0) ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().z == 0) ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().y < 0) ;

        stick->call(Stick::Yaw,0) ;
        stick->getTrait<Stick>()->updateOrientation() ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().x == 0) ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().z == 0) ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().y == 0) ;

        // 100 on pitch means go down
        stick->call(Stick::Pitch,100) ;
        stick->getTrait<Stick>()->updateOrientation() ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().x < 0) ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().z == 0) ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->NewtonMeter().y == 0) ;
      }

    }
  }
}

