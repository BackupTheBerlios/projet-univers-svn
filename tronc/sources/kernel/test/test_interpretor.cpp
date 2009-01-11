/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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
#include <kernel/trait.h>
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/implementation/interpretor.h>
#include <kernel/test/test_interpretor.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Kernel::Test::TestInterpretor) ;

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {

      namespace InterpretorModel
      {
        class T1 : public Trait
        {};
      }
      
      void TestInterpretor::addTrait()
      {
        using namespace InterpretorModel ;
        
        std::auto_ptr<Model> model(new Model()) ;
        std::auto_ptr<Implementation::Interpretor> interpretor(new Implementation::Interpretor(model.get())) ;
        
        Kernel::Object* object = model->createObject() ;
        
        interpretor->startTransaction() ;
        
        interpretor->startConcurrentBlock() ;
        
        interpretor->addTrait(object,new T1()) ;
        // during a block operations are performed
        CPPUNIT_ASSERT(interpretor->getTrait(object,getClassTypeIdentifier(T1))) ;
        
        interpretor->endConcurrentBlock() ;

        interpretor->startConcurrentBlock() ;

        // but in a concurrent block operations are not performed
        CPPUNIT_ASSERT(!interpretor->getTrait(object,getClassTypeIdentifier(T1))) ;
        
        interpretor->endConcurrentBlock() ;
        
        interpretor->endTransaction() ;
        
        // finally operations are performed at the end of the transaction
        CPPUNIT_ASSERT(interpretor->getTrait(object,getClassTypeIdentifier(T1))) ;
      }

      void TestInterpretor::destroyTrait()
      {
        using namespace InterpretorModel ;
        
        std::auto_ptr<Model> model(new Model()) ;
        std::auto_ptr<Implementation::Interpretor> interpretor(new Implementation::Interpretor(model.get())) ;
        
        Kernel::Object* object = model->createObject() ;
        object->addTrait(new T1()) ;
        
        interpretor->startTransaction() ;
        
        interpretor->startConcurrentBlock() ;
        
        interpretor->destroyTrait(object,interpretor->getTrait(object,getClassTypeIdentifier(T1))) ;
        // during a block operations are performed
        CPPUNIT_ASSERT(!interpretor->getTrait(object,getClassTypeIdentifier(T1))) ;
        
        interpretor->endConcurrentBlock() ;

        interpretor->startConcurrentBlock() ;

        // but in a concurrent block operations are not performed
        CPPUNIT_ASSERT(interpretor->getTrait(object,getClassTypeIdentifier(T1))) ;
        
        interpretor->endConcurrentBlock() ;
        
        interpretor->endTransaction() ;
        
        // finally operations are performed at the end of the transaction
        CPPUNIT_ASSERT(!interpretor->getTrait(object,getClassTypeIdentifier(T1))) ;
      }
     
      void TestInterpretor::destroyObject()
      {
        using namespace InterpretorModel ;
        
        std::auto_ptr<Model> model(new Model()) ;
        std::auto_ptr<Implementation::Interpretor> interpretor(new Implementation::Interpretor(model.get())) ;
        
        Kernel::Object* object = model->createObject() ;
        Kernel::Object* object2 = object->createObject() ;
        
        interpretor->startTransaction() ;
        
        interpretor->startConcurrentBlock() ;
        
        interpretor->destroyObject(object2) ;
        // during a block operations are performed
        CPPUNIT_ASSERT(interpretor->getChildren(object).empty()) ;
        
        interpretor->endConcurrentBlock() ;

        interpretor->startConcurrentBlock() ;

        // but in a concurrent block operations are not performed
        CPPUNIT_ASSERT(!interpretor->getChildren(object).empty()) ;
        
        interpretor->endConcurrentBlock() ;
        
        interpretor->endTransaction() ;
        
        // finally operations are performed at the end of the transaction
        CPPUNIT_ASSERT(interpretor->getChildren(object).empty()) ;
        
      }
      
    }
  }
}

