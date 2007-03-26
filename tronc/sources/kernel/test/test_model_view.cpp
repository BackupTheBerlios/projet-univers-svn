/***************************************************************************
 *   Copyright (C) 2004 by Projet Univers                                  *
 *   rogma.boami@free.fr                                                   *
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
#include <kernel/trait_view.h>
#include <kernel/view_point.h>
#include <kernel/test/test_model_view.h>



CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestModelView) ;

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

        /// a trait without view
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
  

        class TestViewPoint : public ViewPoint
        {
        public:
          
          TestViewPoint(Model* i_model)
          : ViewPoint(i_model)
          {}
        
        protected:
        
          virtual void onInit()
          {
          }
          
          virtual void onClose()
          {
          }

        };

       
        class ViewHead : public TraitView<Head,TestViewPoint>
        {
        public:


          ViewHead(Head* i_head,TestViewPoint* i_viewpoint)
          : TraitView<Head,TestViewPoint>(i_head,i_viewpoint),
            value(i_head->getValue()),
            updated(false),
            init_number(0)
          {
            ++number_of_instance ;
          }
          
          ~ViewHead()
          {
            --number_of_instance ;
          }

          /// Called after the view is created on a initialised viewpoint.
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
          
          /// Called when the model trait has changed.
          void onUpdate()
          {
            value = getModel()->getValue() ;
            updated = true ;
          }
          
          int getValue() const 
          {
            return value ;
          }
          
          bool updated ;
          int init_number ;
          static int number_of_instance ;
          
        private:
          
          int value ;
        };

        int ViewHead::number_of_instance = 0 ;
        
        namespace reghead{
        RegisterView(ViewHead,Head,TestViewPoint) ;
        }
        
        class ViewPerson : public TraitView<Person,TestViewPoint>
        {
        public:


          ViewPerson(Person* i_person,TestViewPoint* i_viewpoint)
          : TraitView<Person,TestViewPoint>(i_person,i_viewpoint), 
            value(i_person->getValue()),
            updated(false),
            init_number(0)
          {
            ++number_of_instance ;
          }
          
          ~ViewPerson()
          {
            --number_of_instance ;
          }
          
          int getValue() const
          {
            return value ;
          }

          /// Called after the view is created on a initialised viewpoint.
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
          
          /// Called when the model trait has changed.
          void onUpdate()
          {
            value = getModel()->getValue() ;
            updated = true ;
          }

          
          bool updated ;
          int init_number ;
          static int number_of_instance ;
          
        private:
          int value ;

          
        };

        int ViewPerson::number_of_instance = 0 ;
        
        namespace regperson{
        RegisterView(ViewPerson,Person,TestViewPoint) ;
        }
        
      }

      void TestModelView::testBuildOnEmptyModel()
      {
        Log::InternalMessage("Kernel::Test::testBuildOnEmptyModel entering") ;

        std::auto_ptr<Model> model(new Model()) ;
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        /// init the viewpoint
        viewpoint->init() ;
      
        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;

        /// check the views are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint.get()) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 1) ;

        Trait* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ViewHead* headview = headtrait->getView<ViewHead>(viewpoint.get()) ;
        CPPUNIT_ASSERT(headview) ;
        CPPUNIT_ASSERT(headview->init_number == 1) ;
        
        std::cout << "sizeof(Object)=" << toString(sizeof(*person)) << std::endl ;

        Log::InternalMessage("Kernel::Test::testBuildOnEmptyModel leaving") ;
      }
      
      void TestModelView::testBuildOnNonEmptyModel()
      {
        Log::InternalMessage("Kernel::Test::testBuildOnNonEmptyModel entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        
        /// check the views are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint.get()) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 1) ;

        ViewHead* headview = head->getView<ViewHead>(viewpoint.get()) ;
        CPPUNIT_ASSERT(headview) ;
        CPPUNIT_ASSERT(headview->init_number == 1) ;
        Log::InternalMessage("Kernel::Test::testBuildOnNonEmptyModel leaving") ;
      }
      
      void TestModelView::testDestroyRootObject() 
      {
        Log::InternalMessage("Kernel::Test::testDestroyRootObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;

        model->destroyObject(person) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ViewHead::number_of_instance == 0) ;
        Log::InternalMessage("Kernel::Test::testDestroyRootObject leaving") ;
      }
      
      void TestModelView::testDestroySubObject()
      {
        Log::InternalMessage("Kernel::Test::testDestroySubObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;

        model->destroyObject(head) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_instance == 1) ;
        CPPUNIT_ASSERT(ViewHead::number_of_instance == 0) ;
        Log::InternalMessage("Kernel::Test::testDestroySubObject leaving") ;
      }
      
      void TestModelView::testDestroyTrait()
      {
        Log::InternalMessage("Kernel::Test::testDestroyTrait entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        
        model->destroyTrait(person,persontrait) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ViewHead::number_of_instance == 1) ;
        Log::InternalMessage("Kernel::Test::testDestroyTrait leaving") ;
      }
      
      void TestModelView::testchangeParent()
      {
        Log::InternalMessage("Kernel::Test::testchangeParent entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        Object* person2 = model->createObject("person2") ;
        model->addTrait(person2,new Person()) ;
        Object* head2 = model->createObject("head2",person) ;
        model->addTrait(head2,new Head()) ;
        
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;

        Log::InternalMessage("Kernel::Test::testchangeParent viewpoint initialised") ;

        Head* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ViewHead* headview = headtrait->getView<ViewHead>(viewpoint.get()) ;
        CPPUNIT_ASSERT(headview) ;
        
        Log::InternalMessage("Kernel::Test::testchangeParent #1") ;

        Head* headtrait2 = head2->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait2) ;
        ViewHead* headview2 = headtrait2->getView<ViewHead>(viewpoint.get()) ;
        CPPUNIT_ASSERT(headview2) ;

        Log::InternalMessage("Kernel::Test::testchangeParent #2") ;
        
        CPPUNIT_ASSERT(headview->getValue()== 0);
        CPPUNIT_ASSERT(headview2->getValue()== 0) ;

        Log::InternalMessage("Kernel::Test::testchangeParent #3") ;
        
        headtrait->change(1) ;
        headtrait2->change(2) ;

        CPPUNIT_ASSERT(headview->getValue()== 1) ;
        CPPUNIT_ASSERT(headview2->getValue()== 2) ;

        Log::InternalMessage("Kernel::Test::testchangeParent swapping heads ...") ;
        
        /// swap heads
        model->changeParent(head,person2) ;
        model->changeParent(head2,person) ;
        
        CPPUNIT_ASSERT(headview2->getModel()->getObject()->getParent() == person) ;
        Log::InternalMessage("Kernel::Test::testchangeParent leaving") ;
      }
      
      void TestModelView::testUpdate()
      {
        Log::InternalMessage("Kernel::Test::testUpdate entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        
        Person* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint.get()) ;
        CPPUNIT_ASSERT(personview) ;

        CPPUNIT_ASSERT(personview->getValue()==0) ;
        
        persontrait->changeValue(10) ;
        
        CPPUNIT_ASSERT(personview->getValue()==10) ;
        Log::InternalMessage("Kernel::Test::testUpdate leaving") ;
                
      }

      void TestModelView::testViewAccess()
      {
        Log::InternalMessage("Kernel::Test::testViewAccess entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        model->addTrait(person,new Head()) ;

        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        ViewPerson* personview = person->getView<ViewPerson>(viewpoint.get()) ;
        CPPUNIT_ASSERT(personview) ;
        ViewHead*   headview   = personview->getView<ViewHead>() ;
        CPPUNIT_ASSERT(headview) ;
        Log::InternalMessage("Kernel::Test::testViewAccess leaving") ;
                
      }

      void TestModelView::testCreateTwice()
      {
        Log::InternalMessage("Kernel::Test::testCreateTwice entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        /// first create  
        Object* person = model->createObject("person") ;
        model->destroyObject(person) ;
        
        /// recreate
        person = model->createObject("person") ;
        CPPUNIT_ASSERT(person) ;
        Log::InternalMessage("Kernel::Test::testCreateTwice leaving") ;
      }

      void TestModelView::testDestroyUnexisting()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;
        model->destroyObject("person") ;
        
      }
      
      void TestModelView::testCloseViewPoint()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        model->addTrait(head,new Dummy()) ;

        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint.get()) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ViewHead* headview = headtrait->getView<ViewHead>(viewpoint.get()) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }
        /// close the viewpoint
        viewpoint->close() ;
        {
          /// check the views are closed
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint.get()) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 0) ;
  
          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ViewHead* headview = headtrait->getView<ViewHead>(viewpoint.get()) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 0) ;
        }        
          
      }

      void TestModelView::testNotPresentTrait()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        /// get a not present trait :
        CPPUNIT_ASSERT(person->getTrait<Dummy>() == NULL) ;
        /// Then closes the viexpoint        
        viewpoint->close() ;
      }

      void TestModelView::testDestroyModel()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;

        Log::InternalMessage("Kernel::Test::testDestroyModel destroying model...") ;

        model.reset(NULL) ;
      }

      void TestModelView::setUp()
      {
      }

      void TestModelView::tearDown()
      {
      }

 
       
       
    }
  }
}
