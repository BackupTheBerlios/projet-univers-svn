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
            updated(false),
            init_number(0),
            value(i_head->getValue())
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
          static int number_of_operation ;

          void operation()
          {
            ++number_of_operation ;
          }
          
        private:
          
          int value ;
        };

        int ViewHead::number_of_instance = 0 ;
        int ViewHead::number_of_operation = 0 ;
        
        RegisterView(ViewHead,Head,TestViewPoint) ;
        
        class ViewPerson : public TraitView<Person,TestViewPoint>
        {
        public:


          ViewPerson(Person* i_person,TestViewPoint* i_viewpoint)
          : TraitView<Person,TestViewPoint>(i_person,i_viewpoint), 
            updated(false),
            init_number(0),
            value(i_person->getValue())
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
          static int number_of_operation ;

          void operation()
          {
            ++number_of_operation ;
          }
          
        private:
          int value ;

          
        };

        int ViewPerson::number_of_instance = 0 ;
        int ViewPerson::number_of_operation = 0 ;
        
        RegisterView(ViewPerson,Person,TestViewPoint) ;

        class TestViewPoint2 : public ViewPoint
        {
        public:
          
          TestViewPoint2(Model* i_model)
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

        class ViewHead2 : public TraitView<Head,TestViewPoint2>
        {
        public:


          ViewHead2(Head* i_head,TestViewPoint2* i_viewpoint)
          : TraitView<Head,TestViewPoint2>(i_head,i_viewpoint),
            updated(false),
            init_number(0),
            value(i_head->getValue())
          {
            ++number_of_instance ;
          }
          
          ~ViewHead2()
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
          static int number_of_operation ;

          void operation()
          {
            ++number_of_operation ;
          }
          
        private:
          
          int value ;
        };

        int ViewHead2::number_of_instance = 0 ;
        int ViewHead2::number_of_operation = 0 ;

        RegisterView(ViewHead2,Head,TestViewPoint2) ;
        
        /// inheritance
        
        class T1 : public Trait
        {} ;
        
        class T2 : public T1 
        {} ;
        
        class T3 : public Trait
        {} ;
        
        class V1 : public TraitView<T1,TestViewPoint>
        {
        public:
        
          V1(T1* i_object,TestViewPoint* i_viewpoint)
          : TraitView<T1,TestViewPoint>(i_object,i_viewpoint)
          {}
          
        }; 
        
        RegisterView(V1,T1,TestViewPoint) ;

        class V2 : public TraitView<T2,TestViewPoint>
        {
        public:
        
          V2(T2* i_object,TestViewPoint* i_viewpoint)
          : TraitView<T2,TestViewPoint>(i_object,i_viewpoint)
          {}
          
        }; 
        
        RegisterView(V2,T2,TestViewPoint) ;

        
        class Tv1 : virtual public Trait
        {};
        
        class Tv2 : virtual public Trait
        {};
        
        class TvFinal : public Tv1, public Tv2
        {};
        
        class Vv1 : public TraitView<Tv1,TestViewPoint>
        {
        public:
        
          Vv1(Tv1* i_object,TestViewPoint* i_viewpoint)
          : TraitView<Tv1,TestViewPoint>(i_object,i_viewpoint)
          {}
          
        }; 
        
        RegisterView(Vv1,Tv1,TestViewPoint) ;

        class Vv2 : public TraitView<Tv2,TestViewPoint>
        {
        public:
        
          Vv2(Tv2* i_object,TestViewPoint* i_viewpoint)
          : TraitView<Tv2,TestViewPoint>(i_object,i_viewpoint)
          {}
          
        }; 
        
        RegisterView(Vv2,Tv2,TestViewPoint) ;

        class VvFinal : public TraitView<TvFinal,TestViewPoint>
        {
        public:
        
          VvFinal(TvFinal* i_object,TestViewPoint* i_viewpoint)
          : TraitView<TvFinal,TestViewPoint>(i_object,i_viewpoint)
          {}
          
        }; 
        
        RegisterView(VvFinal,TvFinal,TestViewPoint) ;

      }

      void TestModelView::testBuildOnEmptyModel()
      {
        InternalMessage("Kernel::Test::testBuildOnEmptyModel entering") ;
        {
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
          
          InformationMessage("sizeof(Object)=" + toString(sizeof(*person))) ;
        }
        InternalMessage("Kernel::Test::testBuildOnEmptyModel leaving") ;
      }
      
      void TestModelView::testBuildOnNonEmptyModel()
      {
        InternalMessage("Kernel::Test::testBuildOnNonEmptyModel entering") ;
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
        InternalMessage("Kernel::Test::testBuildOnNonEmptyModel leaving") ;
      }
      
      void TestModelView::testDestroyRootObject() 
      {
        InternalMessage("Kernel::Test::testDestroyRootObject entering") ;
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
        InternalMessage("Kernel::Test::testDestroyRootObject leaving") ;
      }
      
      void TestModelView::testDestroySubObject()
      {
        InternalMessage("Kernel::Test::testDestroySubObject entering") ;
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
        InternalMessage("Kernel::Test::testDestroySubObject leaving") ;
      }
      
      void TestModelView::testDestroyTrait()
      {
        InternalMessage("Kernel::Test::testDestroyTrait entering") ;
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
        InternalMessage("Kernel::Test::testDestroyTrait leaving") ;
      }
      
      void TestModelView::testchangeParent()
      {
        InternalMessage("Kernel::Test::testchangeParent entering") ;
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

        InternalMessage("Kernel::Test::testchangeParent viewpoint initialised") ;

        Head* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ViewHead* headview = headtrait->getView<ViewHead>(viewpoint.get()) ;
        CPPUNIT_ASSERT(headview) ;
        
        InternalMessage("Kernel::Test::testchangeParent #1") ;

        Head* headtrait2 = head2->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait2) ;
        ViewHead* headview2 = headtrait2->getView<ViewHead>(viewpoint.get()) ;
        CPPUNIT_ASSERT(headview2) ;

        InternalMessage("Kernel::Test::testchangeParent #2") ;
        
        CPPUNIT_ASSERT(headview->getValue()== 0);
        CPPUNIT_ASSERT(headview2->getValue()== 0) ;

        InternalMessage("Kernel::Test::testchangeParent #3") ;
        
        headtrait->change(1) ;
        headtrait2->change(2) ;

        CPPUNIT_ASSERT(headview->getValue()== 1) ;
        CPPUNIT_ASSERT(headview2->getValue()== 2) ;

        InternalMessage("Kernel::Test::testchangeParent swapping heads ...") ;
        
        /// swap heads
        model->changeParent(head,person2) ;
        model->changeParent(head2,person) ;
        
        CPPUNIT_ASSERT(headview2->getModel()->getObject()->getParent() == person) ;
        InternalMessage("Kernel::Test::testchangeParent leaving") ;
      }
      
      void TestModelView::testUpdate()
      {
        InternalMessage("Kernel::Test::testUpdate entering") ;
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
        InternalMessage("Kernel::Test::testUpdate leaving") ;
                
      }

      void TestModelView::testViewAccess()
      {
        InternalMessage("Kernel::Test::testViewAccess entering") ;
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
        InternalMessage("Kernel::Test::testViewAccess leaving") ;
                
      }

      void TestModelView::testCreateTwice()
      {
        InternalMessage("Kernel::Test::testCreateTwice entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        /// first create  
        Object* person = model->createObject("person") ;
        model->destroyObject(person) ;
        
        /// recreate
        person = model->createObject("person") ;
        CPPUNIT_ASSERT(person) ;
        InternalMessage("Kernel::Test::testCreateTwice leaving") ;
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

        InternalMessage("Kernel::Test::testDestroyModel destroying model...") ;

        model.reset(NULL) ;
      }

      void TestModelView::testForAll()
      {
        InternalMessage("Kernel::Test::testForAll entering") ;
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

        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;

        ViewHead::number_of_operation = 0 ;
        forAll<ViewHead>(viewpoint.get(),&ViewHead::operation) ;
        CPPUNIT_ASSERT(ViewHead::number_of_operation == 2) ;

        ViewPerson::number_of_operation = 0 ;
        forAll<ViewPerson>(viewpoint.get(),&ViewPerson::operation) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_operation == 3) ;

      }      
      
      void TestModelView::testMultiViewPoint() 
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a viewpoint
        std::auto_ptr<TestViewPoint> viewpoint1(new TestViewPoint(model.get())) ;
        /// init the viewpoint
        viewpoint1->init() ;

        /// create a viewpoint
        std::auto_ptr<TestViewPoint2> viewpoint2(new TestViewPoint2(model.get())) ;
        /// init the viewpoint
        viewpoint2->init() ;

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint1.get()) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;
  
          ViewHead* headview = head->getView<ViewHead>(viewpoint1.get()) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
  
          ViewHead2* headview = head->getView<ViewHead2>(viewpoint2.get()) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }
        
      }

      void TestModelView::testMultiViewPointOfTheSameKind()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        Object* head = model->createObject("head",person) ;
        model->addTrait(head,new Head()) ;
        
        /// create a viewpoint
        std::auto_ptr<TestViewPoint> viewpoint1(new TestViewPoint(model.get())) ;
        /// init the viewpoint
        viewpoint1->init() ;

        /// create a viewpoint
        std::auto_ptr<TestViewPoint> viewpoint2(new TestViewPoint(model.get())) ;
        /// init the viewpoint
        viewpoint2->init() ;

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint1.get()) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;
  
          ViewHead* headview = head->getView<ViewHead>(viewpoint1.get()) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint2.get()) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;
  
          ViewHead* headview = head->getView<ViewHead>(viewpoint2.get()) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }
        
      } 
      
      void TestModelView::testTraitInheritance()
      {
        InternalMessage("Kernel::Test::testTraitInheritance entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* o1 = model->createObject("o1") ;
        model->addTrait(o1,new T2()) ;
        model->addTrait(o1,new T3()) ;

        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        InternalMessage("Kernel::Test::testTraitInheritance viewpoint initialised") ;
        V1* v1 = o1->getView<V1>(viewpoint.get()) ;
        InternalMessage("Kernel::Test::testTraitInheritance looked up view") ;
        CPPUNIT_ASSERT(v1) ;
        InternalMessage("Kernel::Test::testTraitInheritance leaving") ;
                
        
      }
      
      void TestModelView::testTraitVitrualInheritance()
      {
        InternalMessage("Kernel::Test::testTraitVitrualInheritance entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* o1 = model->createObject("o1") ;
        model->addTrait(o1,new TvFinal()) ;

        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;
        InternalMessage("Kernel::Test::testTraitVitrualInheritance viewpoint initialised") ;
        Vv1* v1 = o1->getView<Vv1>(viewpoint.get()) ;
        InternalMessage("Kernel::Test::testTraitVitrualInheritance looked up view") ;
        CPPUNIT_ASSERT(v1) ;
        Vv2* v2 = o1->getView<Vv2>(viewpoint.get()) ;
        InternalMessage("Kernel::Test::testTraitVitrualInheritance looked up view") ;
        CPPUNIT_ASSERT(v2) ;
        VvFinal* vFinal = o1->getView<VvFinal>(viewpoint.get()) ;
        InternalMessage("Kernel::Test::testTraitVitrualInheritance looked up view") ;
        CPPUNIT_ASSERT(vFinal) ;

        InternalMessage("Kernel::Test::testTraitVitrualInheritance leaving") ;
        
      }

      namespace 
      {
        class Trait1 : public Trait
        {};

        class View1 : public TraitView<Trait1,TestViewPoint>
        {
        public:

          View1(Trait1* i_trait,TestViewPoint* i_viewpoint)
          : TraitView<Trait1,TestViewPoint>(i_trait,i_viewpoint),
            changed_parent_number(0)
          {
            ++total_number_of_instance ;
          }
          
          ~View1()
          {
          }

          /// Called after the view is created on a initialised viewpoint.
          void onInit()
          {
            ++total_number_of_init ;
          }
          
          /// Called just before the view is destroyed.
          void onClose()
          {
            ++total_number_of_close ;
          }
      
          /// Called when parent changed.
          void onChangeParent(Object* i_old_parent)
          {
          }
          
          /// Called when the model trait has changed.
          void onUpdate()
          {
          }
          
          /// reinit all
          static void metaInit()
          {
            total_number_of_instance = 0 ;
            total_number_of_init = 0 ;
            total_number_of_close = 0 ;
          }
          
          int changed_parent_number ;
          
          /// total number of created instances
          static int total_number_of_instance ;

          /// total number of init call
          static int total_number_of_init ;

          /// total number of close call
          static int total_number_of_close ;

        };

        int View1::total_number_of_instance = 0 ;
        int View1::total_number_of_init = 0 ;
        int View1::total_number_of_close = 0 ;
        
        RegisterView(View1,Trait1,TestViewPoint) ;
        
      }

      void TestModelView::testchangeParentIsAtomic()
      {
        InternalMessage("Kernel::Test::testchangeParentIsAtomic entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;
        
        View1::metaInit() ;
        
        Object* parent1 = model->createObject("parent1") ;
        Object* parent2 = model->createObject("parent2") ;
        Object* child = model->createObject("child",parent1) ;
        model->addTrait(child,new Trait1()) ;

        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        
        /// init the viewpoint
        viewpoint->init() ;

        /// there should only be one update.
        CPPUNIT_ASSERT(View1::total_number_of_instance == 1) ;
        CPPUNIT_ASSERT(View1::total_number_of_init == 1) ;
        CPPUNIT_ASSERT(View1::total_number_of_close == 0) ;
        
        model->changeParent(child,parent2) ;
        
        CPPUNIT_ASSERT(View1::total_number_of_instance == 1) ;
        CPPUNIT_ASSERT(View1::total_number_of_close == 0) ;
        CPPUNIT_ASSERT(View1::total_number_of_init == 1) ;
        
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
