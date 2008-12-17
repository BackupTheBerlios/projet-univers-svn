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
      namespace ModelControler
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

      using namespace ModelControler ;
      
      void TestModelControler::testBuildOnEmptyModel()
      {
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testBuildOnEmptyModel entering") ;

        std::auto_ptr<Model> model(new Model()) ;
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        /// init the controler
        controler->init() ;
      
        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// check the controlers are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ControlerPerson* personcontroler 
          = persontrait->getControler<ControlerPerson>(controler) ;
        CPPUNIT_ASSERT(personcontroler) ;
        CPPUNIT_ASSERT(personcontroler->init_number == 1) ;

        Trait* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ControlerHead* headcontroler 
          = headtrait->getControler<ControlerHead>(controler) ;
        CPPUNIT_ASSERT(headcontroler) ;
        CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        
        InformationMessage("Kernel","sizeof(Object)=" + toString(sizeof(*person))) ;

        InternalMessage("Kernel","Kernel::Test::TestModelControler::testBuildOnEmptyModel leaving") ;
      }
      
      void TestModelControler::testBuildOnNonEmptyModel()
      {
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testBuildOnNonEmptyModel entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        
        /// create a controler set
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
        /// init the controler set
        controler->init() ;
        
        /// check the controlers are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ControlerPerson* personcontroler 
          = persontrait->getControler<ControlerPerson>(controler) ;
        CPPUNIT_ASSERT(personcontroler) ;
        CPPUNIT_ASSERT(personcontroler->init_number == 1) ;

        Trait* headtrait = head->getTrait<Head>() ;
        ControlerHead* headcontroler 
          = headtrait->getControler<ControlerHead>(controler) ;
        CPPUNIT_ASSERT(headcontroler) ;
        CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testBuildOnNonEmptyModel leaving") ;
      }
      
      void TestModelControler::testDestroyRootObject() 
      {
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testDestroyRootObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        
        /// create a controler set
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
        /// init the controler set
        controler->init() ;

        model->destroyObject(person) ;
        CPPUNIT_ASSERT(ControlerPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ControlerHead::number_of_instance == 0) ;
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testDestroyRootObject leaving") ;
      }
      
      void TestModelControler::testDestroySubObject()
      {
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testDestroySubObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        
        /// create a controler set
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
        /// init the controler set
        controler->init() ;

        model->destroyObject(head) ;
        CPPUNIT_ASSERT(ControlerPerson::number_of_instance == 1) ;
        CPPUNIT_ASSERT(ControlerHead::number_of_instance == 0) ;
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testDestroySubObject leaving") ;
      }
      
      void TestModelControler::testDestroyTrait()
      {
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testDestroyTrait entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        
        /// create a controler set
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
        /// init the controler set
        controler->init() ;
        
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        
        person->destroyTrait(persontrait) ;
        CPPUNIT_ASSERT(ControlerPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ControlerHead::number_of_instance == 1) ;
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testDestroyTrait leaving") ;
      }
      
      void TestModelControler::testCloseControlerSet()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        head->addTrait(new Dummy()) ;

        /// create a controler
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
        /// init the controlers
        controler->init() ;
        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler 
            = persontrait->getControler<ControlerPerson>(controler) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }
        /// close the coltroler set
        controler->close() ;
        {
          /// check the controlers are closed
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 0) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 0) ;
        }        
          
      }

      void TestModelControler::testDestroyModel()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        /// create a controler set
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
        /// init the controler set
        controler->init() ;

        InternalMessage("Kernel","Kernel::Test::TestModelControler::testDestroyModel destroying model...") ;

        model.reset(NULL) ;
      }

      void TestModelControler::testSimulateAll()
      {
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testSimulateAll entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        
        {
          Object* person2 = model->createObject() ;
          person2->addTrait(new Person()) ;
          Object* head2 = person->createObject() ;
          head2->addTrait(new Head()) ;
        }

        {
          Object* person2 = model->createObject() ;
          person2->addTrait(new Person()) ;
        }

        /// create a controler set
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
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
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        
        /// create a controler set
        ControlerSet* controler1(model->addControlerSet(new TestControlerSet(model.get()))) ;
        /// init the viewpoint
        controler1->init() ;

        /// create a controler set 
        ControlerSet* controler2(model->addControlerSet(new TestControlerSet2(model.get()))) ;
        /// init the controler set
        controler2->init() ;

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personconrtoler = persontrait->getControler<ControlerPerson>(controler1) ;
          CPPUNIT_ASSERT(personconrtoler) ;
          CPPUNIT_ASSERT(personconrtoler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler1) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead2* headcontroler = headtrait->getControler<ControlerHead2>(controler2) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }
        
      }

      void TestModelControler::testMultiControlerSetOfTheSameKind()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        
        /// create a controler set
        ControlerSet* controler1(model->addControlerSet(new TestControlerSet(model.get()))) ;
        /// init the controler set
        controler1->init() ;

        /// create a controler set
        ControlerSet* controler2(model->addControlerSet(new TestControlerSet(model.get()))) ;
        /// init the controler set
        controler2->init() ;

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler1) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler1) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }

        {
          /// check the controlers are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler2) ;
          CPPUNIT_ASSERT(personcontroler) ;
          CPPUNIT_ASSERT(personcontroler->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          ControlerHead* headcontroler= headtrait->getControler<ControlerHead>(controler2) ;
          CPPUNIT_ASSERT(headcontroler) ;
          CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        }
        
      } 

      void TestModelControler::testBaseTraitControler()
      {
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testBaseTraitControler entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject() ;
        object->addTrait(new Derived1()) ;
        object->addTrait(new Derived2()) ;
        
        /// create a controler set
        ControlerSet* controler(model->addControlerSet(new TestControlerSet(model.get()))) ;
        
        /// init the controler set
        controler->init() ;
        
        CPPUNIT_ASSERT(ControlerBase::number_of_instance == 2) ;
        
        InternalMessage("Kernel","Kernel::Test::TestModelControler::testBaseTraitControler leaving") ;
      }

      void TestModelControler::initControlerSetWithNullModel()
      {
        InternalMessage("Kernel","Kernel::Test::initControlerSetWithNullModel entering") ;
        std::auto_ptr<Model> model ;
        ControlerSet* controler_set(model->addControlerSet(new TestControlerSet(model.get()))) ;
        /// init the controler set
        controler_set->init() ;
        InternalMessage("Kernel","Kernel::Test::initControlerSetWithNullModel leaving") ;
      }
      
      void TestModelControler::setModelOnInitialisedControlerSetWithNullModel()
      {
        InternalMessage("Kernel","Kernel::Test::setModelOnInitialisedControlerSetWithNullModel entering") ;
        std::auto_ptr<Model> model ;
        ControlerSet* controler_set(model->addControlerSet(new TestControlerSet(model.get()))) ;
        /// init the controler set
        controler_set->init() ;
        
        model.reset(new Model()) ;
        controler_set->setModel(model.get()) ;
        
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// check the controlers are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler_set) ;
        CPPUNIT_ASSERT(personcontroler) ;
        CPPUNIT_ASSERT(personcontroler->init_number == 1) ;

        Trait* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ControlerHead* headcontroler = headtrait->getControler<ControlerHead>(controler_set) ;
        CPPUNIT_ASSERT(headcontroler) ;
        CPPUNIT_ASSERT(headcontroler->init_number == 1) ;
        
        InternalMessage("Kernel","Kernel::Test::setModelOnInitialisedViewPointWithNullModel leaving") ;
      }

      void TestModelControler::changeModelOnInitialisedControlerSet()
      {
        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedControlerSet entering") ;
        std::auto_ptr<Model> model(new Model()) ;
        ControlerSet* controler_set(model->addControlerSet(new TestControlerSet(model.get()))) ;
        /// init the viewpoint
        controler_set->init() ;
        
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;

        /// check the views are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ControlerPerson* personcontroler = persontrait->getControler<ControlerPerson>(controler_set) ;
        CPPUNIT_ASSERT(personcontroler) ;
        CPPUNIT_ASSERT(personcontroler->init_number == 1) ;

        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedControlerSet#1") ;
        std::auto_ptr<Model> model2(new Model()) ;
        controler_set->setModel(model2.get()) ;

        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedControlerSet#2") ;

        /// check the views where closed
        personcontroler = persontrait->getControler<ControlerPerson>(controler_set) ;
        CPPUNIT_ASSERT(personcontroler) ;                
        CPPUNIT_ASSERT(personcontroler->init_number == 0) ;        
        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedControlerSet leaving") ;
      }

      namespace ModelControler
      {
        class Trait1 : public Trait
        {};
        class Trait2 : public Trait
        {};
        class Trait3 : public Trait
        {};
        class Trait4 : public Trait
        {};
        
        class DestroyControlerSet : public ControlerSet
        {
        public:
          
          DestroyControlerSet(Model* model)
          : ControlerSet(model)
          {}
        };
        
        class ControlerTrait1 : public Controler<Trait1,DestroyControlerSet>
        {
        public:
          ControlerTrait1(Trait1* trait,DestroyControlerSet* controler_set)
          : Controler<Trait1,DestroyControlerSet>(trait,controler_set)
          {}
          
          virtual void simulate(const float&)
          {
            Trait2* trait2 = getObject()->getTrait<Trait2>() ;
            if (trait2)
            {
              getObject()->destroyTrait(trait2) ;
            }
          }
        };
        RegisterControler(ControlerTrait1,Trait1,DestroyControlerSet) ;

        class ControlerTrait2 : public Controler<Trait2,DestroyControlerSet>
        {
        public:
          ControlerTrait2(Trait2* trait,DestroyControlerSet* controler_set)
          : Controler<Trait2,DestroyControlerSet>(trait,controler_set)
          {}
          
          virtual void simulate(const float&)
          {
            Trait1* trait1 = getObject()->getTrait<Trait1>() ;
            if (trait1)
            {
              getObject()->destroyTrait(trait1) ;
            }
            Trait3* trait3 = getObject()->getTrait<Trait3>() ;
            if (trait3)
            {
              getObject()->destroyTrait(trait3) ;
            }
          }
        };
        RegisterControler(ControlerTrait2,Trait2,DestroyControlerSet) ;
        
        class ControlerTrait3 : public Controler<Trait3,DestroyControlerSet>
        {
        public:
          ControlerTrait3(Trait3* trait,DestroyControlerSet* controler_set)
          : Controler<Trait3,DestroyControlerSet>(trait,controler_set)
          {}
          
          virtual void simulate(const float&)
          {
            Trait1* trait1 = getObject()->getTrait<Trait1>() ;
            if (trait1)
            {
              getObject()->destroyTrait(trait1) ;
            }
            Trait2* trait2 = getObject()->getTrait<Trait2>() ;
            if (trait2)
            {
              getObject()->destroyTrait(trait2) ;
            }
          }
        };
        RegisterControler(ControlerTrait3,Trait3,DestroyControlerSet) ;
        
      }
      
      void TestModelControler::simulateDestroyTrait()
      {
        std::auto_ptr<Model> model(new Model()) ;
        ControlerSet* controler(model->addControlerSet(new DestroyControlerSet(model.get()))) ;
        controler->init() ;
      
        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Trait2()) ;
        person->addTrait(new Trait1()) ;
        person->addTrait(new Trait3()) ;
        
        controler->simulate(0) ;
        
        CPPUNIT_ASSERT(!person->getTrait<Trait1>()) ;
        CPPUNIT_ASSERT(!person->getTrait<Trait2>()) ;
      }

      namespace ModelControler
      {
        
        class AccessControlerSet : public ControlerSet
        {
        public:
          
          AccessControlerSet(Model* model)
          : ControlerSet(model)
          {}
        };
        
        class AccessTrait1Controler : public Controler<Trait1,AccessControlerSet>
        {
        public:
          
          
          static bool m_accessed ;
          
          AccessTrait1Controler(Trait1* trait,AccessControlerSet* controler_set)
          : Controler<Trait1,AccessControlerSet>(trait,controler_set)
          {}
          
          virtual void simulate(const float&)
          {
            Trait2* trait2 = getTrait<Trait2>() ;
            if (trait2)
            {
              m_accessed= true ;
            }
          }
        };
        
        bool AccessTrait1Controler::m_accessed = false ;
        
        RegisterControler(AccessTrait1Controler,Trait1,AccessControlerSet) ;

      }
      
      void TestModelControler::accessOtherTrait()
      {
        AccessTrait1Controler::m_accessed = false ;
        std::auto_ptr<Model> model(new Model()) ;
        ControlerSet* controler(model->addControlerSet(new AccessControlerSet(model.get()))) ;
        controler->init() ;
     
        //// fill the model
        Object* object = model->createObject() ;
        object->addTrait(new Trait2()) ;
        object->addTrait(new Trait1()) ;
        
        controler->simulate(0) ;

        CPPUNIT_ASSERT(AccessTrait1Controler::m_accessed) ;
      }
      
      namespace ModelControler
      {
        class DestroyObject : public ControlerSet
        {
        public:
          
          DestroyObject(Model* model)
          : ControlerSet(model)
          {}
        };
        
        class DestroyObjectTrait1 : public Controler<Trait1,DestroyObject>
        {
        public:
          DestroyObjectTrait1(Trait1* trait,DestroyObject* controler_set)
          : Controler<Trait1,DestroyObject>(trait,controler_set)
          {}
          
          virtual void simulate(const float&)
          {
            getObject()->destroyObject() ;
          }
        };
        
        RegisterControler(DestroyObjectTrait1,Trait1,DestroyObject) ;
        
        class DestroyObjectTrait2 : public Controler<Trait2,DestroyObject>
        {
        public:
          DestroyObjectTrait2(Trait2* trait,DestroyObject* controler_set)
          : Controler<Trait2,DestroyObject>(trait,controler_set)
          {}
          
          virtual void simulate(const float&)
          {
            getObject()->destroyObject() ;
          }
        };
        
        RegisterControler(DestroyObjectTrait2,Trait2,DestroyObject) ;
      }
      
      void TestModelControler::destroyObject()
      {
        std::auto_ptr<Model> model(new Model()) ;
        ControlerSet* controler(model->addControlerSet(new DestroyObject(model.get()))) ;
        controler->init() ;
      
        ObjectReference person = model->createObject() ;
        person->addTrait(new Trait1()) ;
         
        model->update(0) ;
        
        CPPUNIT_ASSERT(!person) ;
      }
      
      void TestModelControler::destroyObjectTwice()
      {
        std::auto_ptr<Model> model(new Model()) ;
        ControlerSet* controler(model->addControlerSet(new DestroyObject(model.get()))) ;
        controler->init() ;
      
        ObjectReference person = model->createObject() ;
        person->addTrait(new Trait1()) ;
        person->addTrait(new Trait2()) ;
         
        model->update(0) ;
        
        CPPUNIT_ASSERT(!person) ;
      }
      
    }
  }
}
