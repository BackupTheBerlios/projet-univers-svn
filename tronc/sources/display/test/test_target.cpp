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

#include <model/model.h>
#include <model/computer.h>
#include <model/positionned.h>
#include <model/detection_data.h>
#include <model/solid.h>
#include <model/selected.h>
#include <display/implementation/ogre/head_up_display/target.h>
#include <display/test/test_target.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Display::
                                Test::
                                TestTarget) ;

namespace ProjetUnivers {
  namespace Display {
    namespace Test {

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

        CPPUNIT_ASSERT(data->getTrait<Implementation::Ogre::HeadUpDisplay::Target>()) ;
        
        InternalMessage("Display","Display::TestTarget::testConstruct leaving") ;
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

