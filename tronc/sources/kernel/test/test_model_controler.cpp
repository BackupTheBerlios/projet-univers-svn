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
using namespace std ;

#include <kernel/log.h>

#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/controler.h>
#include <kernel/controler_set.h>
#include <kernel/test/test_model_controler.h>



CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestModelControler) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

      /// local classes
      namespace
      {
        
        /// Model
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
        
        /// Model
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

        /// a trait without controler
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

        /// a base trait.
        class Base : public Trait
        {
        public:
        
          Base()
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
          
          virtual ~Base()
          {}
          
        private:
        
          int value ;
          
        };

        /// a derived trait.
        class Derived1 : public Base
        {
        public:
        
          Derived1()
          : Base()
          {}
          
        };

        /// a derived trait.
        class Derived2 : public Base
        {
        public:
        
          Derived2()
          : Base()
          {}
          
        };

        /// A group of controler
        class TestControlerSet : public ControlerSet
        {
        public:
          
          TestControlerSet(Model* i_model)
          : ControlerSet(i_model)
          {}
        
        protected:
        
          virtual void onInit()
          {
          }
          
          virtual void onClose()
          {
          }

        };

       
        class ControlerHead : public Controler<Head,TestControlerSet>
        {
        public:


          ControlerHead(Head* i_head,TestControlerSet* i_controler_set)
          : Controler<Head,TestControlerSet>(i_head,i_controler_set),
            updated(false),
            init_number(0),
            value(i_head->getValue())
          {
            ++number_of_instance ;
          }
          
          ~ControlerHead()
          {
            --number_of_instance ;
          }

          virtual void simulate(const float&)
          {
            operation() ;
          }
          
          int getValue() const 
          {
            return value ;
          }

          void onInit()
          {
            ++init_number ;
          }
          
          /// Called just before the view is destroyed.
          void onClose()
          {
            --init_number ;
          }
      
          /// Called when parent changed.
          void onChangeParent(Object* i_old_parent)
          {
          }
          
          bool updated ;
          int init_number ;
          static int number_of_instance ;
          static int number_of_operation ;

          void operation()
          {
            ++number_of_operation ;
          }
          
        private:
          
          int value ;
        };

        int ControlerHead::number_of_instance = 0 ;
        int ControlerHead::number_of_operation = 0 ;
        
        RegisterControler(ControlerHead,Head,TestControlerSet) ;
        
        class ControlerPerson : public Controler<Person,TestControlerSet>
        {
        public:


          ControlerPerson(Person* i_person,TestControlerSet* i_controler_set)
          : Controler<Person,TestControlerSet>(i_person,i_controler_set), 
            updated(false),
            init_number(0),
            value(i_person->getValue())
          {
            ++number_of_instance ;
          }

          virtual void simulate(const float&)
          {
            operation() ;
          }
          
          ~ControlerPerson()
          {
            --number_of_instance ;
          }
          
          int getValue() const
          {
            return value ;
          }

          void onInit()
          {
            ++init_number ;
          }
          
          /// Called just before the view is destroyed.
          void onClose()
          {
            --init_number ;
          }
      
          /// Called when parent changed.
          void onChangeParent(Object* i_old_parent)
          {
          }
          
          bool updated ;
          int init_number ;
          static int number_of_instance ;
          static int number_of_operation ;

          void operation()
          {
            ++number_of_operation ;
          }
          
        private:
          int value ;

          
        };

        int ControlerPerson::number_of_instance = 0 ;
        int ControlerPerson::number_of_operation = 0 ;
        
        RegisterControler(ControlerPerson,Person,TestControlerSet) ;


        class ControlerBase : public Controler<Base,TestControlerSet>
        {
        public:


          ControlerBase(Base* i_object,TestControlerSet* i_controler_set)
          : Controler<Base,TestControlerSet>(i_object,i_controler_set), 
            updated(false),
            init_number(0),
            value(i_object->getValue())
          {
            ++number_of_instance ;
          }

          virtual void simulate(const float&)
          {
            operation() ;
          }
          
          ~ControlerBase()
          {
            --number_of_instance ;
          }
          
          int getValue() const
          {
            return value ;
          }

          void onInit()
          {
            ++init_number ;
          }
          
          /// Called just before the view is destroyed.
          void onClose()
          {
            --init_number ;
          }
      
          /// Called when parent changed.
          void onChangeParent(Object* i_old_parent)
          {
          }
          
          bool updated ;
          int init_number ;
          static int number_of_instance ;
          static int number_of_operation ;

          void operation()
          {
            ++number_of_operation ;
          }
          
        private:
          int value ;

          
        };

        int ControlerBase::number_of_instance = 0 ;
        int ControlerBase::number_of_operation = 0 ;

        RegisterControler(ControlerBase,Base,TestControlerSet) ;

        class TestControlerSet2 : public ControlerSet
        {
        public:
          
          TestControlerSet2(Model* i_model)
          : ControlerSet(i_model)
          {}
        
        protected:
        
          virtual void onInit()
          {
          }
          
          virtual void onClose()
          {
          }

        };

        class ControlerHead2 : public Controler<Head,TestControlerSet2>
        {
        public:


          ControlerHead2(Head* i_head,TestControlerSet2* i_controler_set)
          : Controler<Head,TestControlerSet2>(i_head,i_controler_set),
            updated(false),
            init_number(0),
            value(i_head->getValue())
          {
            ++number_of_instance ;
          }

          virtual void simulate(const float&)
          {
          }
          
          ~ControlerHead2()
          {
            --number_of_instance ;
          }

          int getValue() const 
          {
            return value ;
          }

          void onInit()
          {
            ++init_number ;
          }
          
          /// Called just before the view is destroyed.
          void onClose()
          {
            --init_number ;
          }
      
          /// Called when parent changed.
          void onChangeParent(Object* i_old_parent)
          {
          }
          
          bool updated ;
          int init_number ;
          static int number_of_instance ;
          static int number_of_operation ;

          void operation()
          {
            ++number_of_operation ;
          }
          
        private:
          
          int value ;
        };

        int ControlerHead2::number_of_instance = 0 ;
        int ControlerHead2::number_of_operation = 0 ;

        RegisterControler(ControlerHead2,Head,TestControlerSet2) ;
        
        
        
      }

      void TestModelControler::testBuildOnEmptyModel()
      {
        InternalMessage("Kernel::Test::TestModelControler::testBuildOnEmptyModel entering") ;

        std::auto_ptr<Model> model(new Model()) ;
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        /// init the controler
        controler->init() ;
      
        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;

        /// check the controlers are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ControlerPerson* personcontroler 
          = persontrait->getControler<ControlerPerson>(controler.get()) ;
        CPPUNIT_ASSERT(personcontroler) ;
        CPPUNIT_ASSERT(personcontroler->init_number == 1) ;

        Trait* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ControlerHead* headcontroler 
          = headtrait->getControler<ControlerHead>(controler.get()) ;
        CPPUNIT_ASSERT(headcontroler) ;
        CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        
        InformationMessage("sizeof(Object)=" + toString(sizeof(*person))) ;

        InternalMessage("Kernel::Test::TestModelControler::testBuildOnEmptyModel leaving") ;
      }
      
      void TestModelControler::testBuildOnNonEmptyModel()
      {
        InternalMessage("Kernel::Test::TestModelControler::testBuildOnNonEmptyModel entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controler set
        controler->init() ;
        
        /// check the controlers are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ControlerPerson* personcontroler 
          = persontrait->getControler<ControlerPerson>(controler.get()) ;
        CPPUNIT_ASSERT(personcontroler) ;
        CPPUNIT_ASSERT(personcontroler->init_number == 1) ;

        Trait* headtrait = head->getTrait<Head>() ;
        ControlerHead* headcontroler 
          = headtrait->getControler<ControlerHead>(controler.get()) ;
        CPPUNIT_ASSERT(headcontroler) ;
        CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        InternalMessage("Kernel::Test::TestModelControler::testBuildOnNonEmptyModel leaving") ;
      }
      
      void TestModelControler::testDestroyRootObject() 
      {
        InternalMessage("Kernel::Test::TestModelControler::testDestroyRootObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controler set
        controler->init() ;

        model->destroyObject(person) ;
        CPPUNIT_ASSERT(ControlerPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ControlerHead::number_of_instance == 0) ;
        InternalMessage("Kernel::Test::TestModelControler::testDestroyRootObject leaving") ;
      }
      
      void TestModelControler::testDestroySubObject()
      {
        InternalMessage("Kernel::Test::TestModelControler::testDestroySubObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controler set
        controler->init() ;

        model->destroyObject(head) ;
        CPPUNIT_ASSERT(ControlerPerson::number_of_instance == 1) ;
        CPPUNIT_ASSERT(ControlerHead::number_of_instance == 0) ;
        InternalMessage("Kernel::Test::TestModelControler::testDestroySubObject leaving") ;
      }
      
      void TestModelControler::testDestroyTrait()
      {
        InternalMessage("Kernel::Test::TestModelControler::testDestroyTrait entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controler set
        controler->init() ;
        
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        
        model->destroyTrait(person,persontrait) ;
        CPPUNIT_ASSERT(ControlerPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ControlerHead::number_of_instance == 1) ;
        InternalMessage("Kernel::Test::TestModelControler::testDestroyTrait leaving") ;
      }
      
      void TestModelControler::testCloseControlerSet()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        model->addTrait(head,new Dummy()) ;

        /// create a controler
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controlers
        controler->init() ;
        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler 
            = persontrait->getControler<ControlerPerson>(controler.get()) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler.get()) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }
        /// close the coltroler set
        controler->close() ;
        {
          /// check the controlers are closed
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler.get()) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 0) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler.get()) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 0) ;
        }        
          
      }

      void TestModelControler::testDestroyModel()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controler set
        controler->init() ;

        InternalMessage("Kernel::Test::TestModelControler::testDestroyModel destroying model...") ;

        model.reset(NULL) ;
      }

      void TestModelControler::testSimulateAll()
      {
        InternalMessage("Kernel::Test::TestModelControler::testSimulateAll entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        {
          Object* person2 = model->createObject("person2") ;
          model->addTrait(person2,new Person()) ;
          Object* head2 = model->createObject("head2",person) ;
          model->addTrait(head2,new Head()) ;
        }

        {
          Object* person2 = model->createObject("person3") ;
          model->addTrait(person2,new Person()) ;
        }

        /// create a controler set
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controler set
        controler->init() ;

        ControlerHead::number_of_operation = 0 ;
        controler->simulate(1) ;
        CPPUNIT_ASSERT(ControlerHead::number_of_operation == 2) ;

        ControlerPerson::number_of_operation = 0 ;
        controler->simulate(1) ;
        CPPUNIT_ASSERT(ControlerPerson::number_of_operation == 3) ;

      }      
      
      void TestModelControler::testMultiControlerSet() 
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler1(new TestControlerSet(model.get())) ;
        /// init the viewpoint
        controler1->init() ;

        /// create a controler set 
        std::auto_ptr<TestControlerSet2> controler2(new TestControlerSet2(model.get())) ;
        /// init the controler set
        controler2->init() ;

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personconrtoler = persontrait->getControler<ControlerPerson>(controler1.get()) ;
          CPPUNIT_ASSERT(personconrtoler) ;
          CPPUNIT_ASSERT(personconrtoler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler1.get()) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead2* headcontroler = headtrait->getControler<ControlerHead2>(controler2.get()) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }
        
      }

      void TestModelControler::testMultiControlerSetOfTheSameKind()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler1(new TestControlerSet(model.get())) ;
        /// init the controler set
        controler1->init() ;

        /// create a controler set
        std::auto_ptr<TestControlerSet> controler2(new TestControlerSet(model.get())) ;
        /// init the controler set
        controler2->init() ;

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler1.get()) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler1.get()) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler2.get()) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead* headcontroler= headtrait->getControler<ControlerHead>(controler2.get()) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }
        
      } 

      void TestModelControler::testBaseTraitControler()
      {
        InternalMessage("Kernel::Test::TestModelControler::testBaseTraitControler entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject("o1") ;
        model->addTrait(object,new Derived1()) ;
        model->addTrait(object,new Derived2()) ;
        
        /// create a controler set
        std::auto_ptr<TestControlerSet> controler(new TestControlerSet(model.get())) ;
        
        /// init the controler set
        controler->init() ;
        
        CPPUNIT_ASSERT(ControlerBase::number_of_instance == 2) ;
        
        InternalMessage("Kernel::Test::TestModelControler::testBaseTraitControler leaving") ;
      }
      
      void TestModelControler::setUp()
      {
      }

      void TestModelControler::tearDown()
      {
      }

 
       
       
    }
  }
}
