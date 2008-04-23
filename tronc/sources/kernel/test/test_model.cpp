/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/object_reference.h>
#include <kernel/trait.h>
#include <kernel/trait_view.h>
#include <kernel/view_point.h>
#include <kernel/trait_reference.h>

#include <kernel/test/test_model.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Kernel::Test::TestModel) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      /// local classes
      namespace
      {
        
        class Head : public Trait
        {
        public:
        
          Head()
          : Trait(), value(0)
          {}
        
          void change(const int& i_new_value) 
          {
            value = i_new_value ;
            notify() ;
          }  
          
          int getValue() const
          {
            return value ;
          }
          
        private:
        
          int value ;
          
        };
        
        class Person : public Trait
        {
        public:
        
          Person()
          : Trait(), value(0)
          {}
        
          void changeValue(const int& i_new_value) 
          {
            value = i_new_value ;
            notify() ;
          }  
          
          int getValue() const
          {
            return value ;
          }
          
        private:
        
          int value ;
          
        };

        class Dummy : public Trait
        {
        public:
        
          Dummy()
          : Trait(), value(0)
          {}
        
          void changeValue(const int& i_new_value) 
          {
            value = i_new_value ;
            notify() ;
          }  
          
          int getValue() const
          {
            return value ;
          }
          
        private:
        
          int value ;
          
        };
  
      }
      
      void TestModel::testGetDescendants()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testGetDescendants")) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        
        // create several heads
        {
          Object* head = model->createObject(person) ;
          model->addTrait(head,new Head()) ;
          
          head = model->createObject(head) ;
          model->addTrait(head,new Head()) ;
          
        }
        
        {
          Object* head = model->createObject(person) ;
          model->addTrait(head,new Head()) ;
        }        

        std::set<Head*> heads = person->getDescendants<Head>() ;
        
        CPPUNIT_ASSERT(heads.size() == 3) ;
        
      }

      void TestModel::testObjectReference()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testObjectReference")) ;

        //// fill the model
        Object* object = model->createObject("referenced object") ;
        
        ObjectReference reference(object) ;
        
        {
          Object* object = reference ;
          CPPUNIT_ASSERT(object->getName() == "referenced object") ;
        }
      }
        
      void TestModel::testObjectReferenceToDestroyedObject()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testObjectReferenceToDestroyedObject")) ;

        //// fill the model
        Object* object = model->createObject() ;
        ObjectReference reference(object) ;
        
        model->destroyObject(object) ;
        
        {
          Object* object = reference ;
          CPPUNIT_ASSERT(!object) ;
        }

      }

      void TestModel::testObjectReferenceAffectation()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testObjectReferenceAffectation")) ;

        //// fill the model
        Object* object = model->createObject() ;
        ObjectReference reference = object ;
        
        model->destroyObject(object) ;
        
        {
          Object* object = reference ;
          CPPUNIT_ASSERT(!object) ;
        }

      }
      
      void TestModel::testTraitReference()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testTraitReference")) ;

        //// fill the model
        Object* object = model->createObject("referenced object") ;
        model->addTrait(object,new Person()) ;
        
        TraitReference<Person> reference(object) ;
        
        {
          Person* person = reference ;
          CPPUNIT_ASSERT(person) ;
        }
      }
        
      void TestModel::testTraitReferenceToRemovedTrait()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testTraitReferenceToRemovedTrait")) ;

        //// fill the model
        Object* object = model->createObject("referenced object") ;
        model->addTrait(object,new Person()) ;
        
        TraitReference<Person> reference(object) ;
        model->destroyTrait(object,reference) ;
        
        {
          Person* person = reference ;
          CPPUNIT_ASSERT(!person) ;
        }
      }

      void TestModel::testTraitReferenceToDestroyedObject()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testTraitReferenceToDestroyedObject")) ;

        //// fill the model
        Object* object = model->createObject("referenced object") ;
        model->addTrait(object,new Person()) ;
        
        TraitReference<Person> reference(object) ;
        model->destroyObject(object) ;
        
        {
          Person* person = reference ;
          CPPUNIT_ASSERT(!person) ;
        }
      }

      void TestModel::conversionTestObjectReference()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::conversionTestObjectReference")) ;
        
        {
          Object* object = model->createObject("referenced object") ;
          ObjectReference reference(object) ;
          CPPUNIT_ASSERT(reference) ;
        }
        
        {        
          ObjectReference reference(NULL) ;
          CPPUNIT_ASSERT(!reference) ;
        }
      }

      void TestModel::testObjectReferenceToDestroyedModel()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testObjectReferenceToDestroyedModel")) ;

        Object* object = model->createObject() ;
        ObjectReference reference(object) ;
        
        model.reset(NULL) ;
        
        {
          Object* object = reference ;
          CPPUNIT_ASSERT(!object) ;
        }
      }      

      void TestModel::testSetOfObjectReferences()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testSetOfObjectReferences")) ;

        Object* object1 = model->createObject() ;
        Object* object2 = model->createObject() ;
        
        std::set<ObjectReference> set ;
        set.insert(object1) ;
        set.insert(object2) ;
        
        CPPUNIT_ASSERT(set.size()==2) ;
        
      }
      
      void TestModel::notifyOnNotAssignedTrait()
      {
        Head* head = new Head() ;
        head->change(10) ;
      }
      
      void TestModel::setUp()
      {
      }
      
      void TestModel::tearDown()
      {
      }

    }
  }
}
