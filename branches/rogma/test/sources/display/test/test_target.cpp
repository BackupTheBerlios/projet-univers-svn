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
#include <iostream>
#include <kernel/model.h>
#include <kernel/object.h>

#include <model/model.h>
#include <model/computer.h>
#include <model/positionned.h>
#include <model/detection_data.h>
#include <model/solid.h>
#include <model/selected.h>
#include <display/implementation/target.h>
#include <display/implementation/ogre/head_up_display/target.h>
#include <display/test/test_target.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Display::
                                Test::
                                TestTarget) ;

namespace ProjetUnivers {
  namespace Display {
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
      
      void TestTarget::testConstruct()
      {
        InternalMessage("Display","Display::TestTarget::testConstruct entering") ;
        
        InternalMessage("Display",Kernel::DeducedTrait::printDeclarations()) ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTarget::testConstruct")) ;

        Kernel::Object* ship = model->createObject("ship") ;
        model->addTrait(ship,new Model::Computer()) ;
       
        Kernel::Model* memory = ship->getTrait<Model::Computer>()->getMemoryModel() ;
        
        Kernel::Object* data = memory->createObject("detection") ;
        memory->addTrait(data,new Model::Positionned()) ;
        memory->addTrait(data,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        memory->addTrait(data,new Model::DetectionData()) ;
        memory->addTrait(data,new Model::Selected()) ;

        CPPUNIT_ASSERT(data->getTrait<Implementation::Target>()) ;
        Model::close() ;
        InternalMessage("Display","Display::TestTarget::testConstruct leaving") ;
      }

      void TestTarget::testCalculateRotation()
      {
        using namespace Implementation::Ogre::HeadUpDisplay ;

        CPPUNIT_ASSERT(equal(Target::calculateRotation(0,1).valueDegrees(),0)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(1,1).valueDegrees(),45)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(1,0).valueDegrees(),90)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(1,-1).valueDegrees(),135)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(0,-1).valueDegrees(),180)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(-1,-1).valueDegrees(),225)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(-1,0).valueDegrees(),270)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(-1,1).valueDegrees(),315) ||
                       equal(Target::calculateRotation(-1,1).valueDegrees(),-45)) ;

      }
      
      void TestTarget::setUp() 
      {
      }
      
      void TestTarget::tearDown() 
      {
      }

    }
  }
}

