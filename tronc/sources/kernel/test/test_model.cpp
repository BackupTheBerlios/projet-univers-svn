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
#include <kernel/deduced_trait.h>
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
  
        class DeducedTrait1 : public Kernel::DeducedTrait
        {}; 
        
        
        /// A deduced trait.
        DeclareDeducedTrait(DeducedTrait1,
                            And(HasTrait(Head),
                                HasTrait(Person),
                                HasTrait(Dummy))) ;
        
        
      }
      
      void TestModel::testGetDescendants()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testGetDescendants")) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        
        // create several heads
        {
          Object* head = person->createObject() ;
          head->addTrait(new Head()) ;
          
          head = head->createObject() ;
          head->addTrait(new Head()) ;
          
        }
        
        {
          Object* head = person->createObject() ;
          head->addTrait(new Head()) ;
        }        

        std::set<Head*> heads = person->getDescendants<Head>() ;
        
        CPPUNIT_ASSERT(heads.size() == 3) ;
        
      }

      void TestModel::testObjectReference()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testObjectReference")) ;

        //// fill the model
        Object* object = model->createObject() ;
        
        ObjectReference reference(object) ;
        
        {
          Object* object = reference ;
          CPPUNIT_ASSERT(object) ;
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
        
        CPPUNIT_ASSERT(!reference) ;
        
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
        Object* object = model->createObject() ;
        object->addTrait(new Person()) ;
        
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
        Object* object = model->createObject() ;
        object->addTrait(new Person()) ;
        
        TraitReference<Person> reference(object) ;
        object->destroyTrait(reference) ;
        
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
        Object* object = model->createObject() ;
        object->addTrait(new Person()) ;
        
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
          Object* object = model->createObject() ;
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
      
      void TestModel::destroyObjectWithDeducedTraits()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::destroyObjectWithDeducedTraits")) ;

        Object* object1 = model->createObject() ;
        Object* object2 = object1->createObject() ;
        
        object1->addTrait(new Person()) ;
        object1->addTrait(new Head()) ;
        object1->addTrait(new Dummy()) ;
        
        model->destroyObject(object1) ;
      }
      
      void TestModel::addTraitTwice()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::addTraitTwice")) ;

        Object* object = model->createObject() ;
        object->addTrait(new Person()) ;
        object->destroyTrait(object->getTrait<Person>()) ;
        object->addTrait(new Person()) ;
        
      }
      
      void TestModel::getByName()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::getByName")) ;

        Object* object1 = model->createObject() ;
        object1->setName("object1") ; 
        Object* object2 = model->createObject() ;
        object2->setName("object2") ; 
        Object* object3 = model->createObject() ;
        object3->setName("object3") ; 
       
        CPPUNIT_ASSERT(Object::get("toto") == NULL) ;
        CPPUNIT_ASSERT(Object::get("object1") == object1) ;
        CPPUNIT_ASSERT(Object::get("object2") == object2) ;
        CPPUNIT_ASSERT(Object::get("object3") == object3) ;
      }
    
      void TestModel::destroyObjects()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::destroyObjects")) ;

        Object* object1 = model->createObject() ;
        Object* object2 = object1->createObject() ;
        Object* object3 = object2->createObject() ;
        
        std::set<ObjectReference> objects_to_destroy ;
        objects_to_destroy.insert(object2) ;
        objects_to_destroy.insert(object3) ;
        
        object1->destroyObject() ;
        
        for (std::set<ObjectReference>::const_iterator object = objects_to_destroy.begin() ;
             object != objects_to_destroy.end() ;
             ++object)
        {
          if (*object)
          {
            InternalMessage("Kernel","destroying object " + toString((*object)->getIdentifier())) ;
            (*object)->destroyObject() ;
          }
        }
        
      }
      
      void TestModel::getDestroyedChild()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::getDestroyedObject")) ;

        Object* object1 = model->createObject() ;
        Object* object2 = object1->createObject() ;
        int identifier = object2->getIdentifier() ;
        model->destroyObject(object1) ;
        CPPUNIT_ASSERT(!model->getObject(identifier)) ;
      }
    
    }
  }
}
