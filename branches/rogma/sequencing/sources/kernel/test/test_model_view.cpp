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
#include <iostream>
using namespace std ;

#include <kernel/log.h>

#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/deduced_trait.h>
#include <kernel/trait_view.h>
#include <kernel/view_point.h>
#include <kernel/test/test_model_view.h>



CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestModelView) ;

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      /// local classes
      namespace ModelView
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

        class DeducedTrait1 : public Kernel::DeducedTrait
        {};
        DeclareDeducedTrait(DeducedTrait1,
                            And(HasTrait(Head),
                                HasTrait(Person),
                                HasTrait(Dummy))) ;

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

        class ViewDeducedTrait1 : public TraitView<DeducedTrait1,TestViewPoint>
        {
        public:

          ViewDeducedTrait1(DeducedTrait1* trait,TestViewPoint* i_viewpoint)
          : TraitView<DeducedTrait1,TestViewPoint>(trait,i_viewpoint)
          {}

        };


        class ViewHead : public TraitView<Head,TestViewPoint>
        {
        public:


          ViewHead()
          : updated(false),
            init_number(0),
            value()
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
            value = getTrait()->getValue() ;
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
            value = getTrait()->getValue() ;
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


          ViewPerson()
          : updated(false),
            init_number(0),
            value()
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
            value = getTrait()->getValue() ;
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
            value = getTrait()->getValue() ;
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


          ViewHead2()
          : updated(false),
            init_number(0),
            value()
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
            value = getTrait()->getValue() ;
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
            value = getTrait()->getValue() ;
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
        {};

        RegisterView(V1,T1,TestViewPoint) ;

        class V2 : public TraitView<T2,TestViewPoint>
        {};

        RegisterView(V2,T2,TestViewPoint) ;


        class Tv1 : virtual public Trait
        {};

        class Tv2 : virtual public Trait
        {};

        class TvFinal : public Tv1, public Tv2
        {};

        class Vv1 : public TraitView<Tv1,TestViewPoint>
        {};

        RegisterView(Vv1,Tv1,TestViewPoint) ;

        class Vv2 : public TraitView<Tv2,TestViewPoint>
        {};

        RegisterView(Vv2,Tv2,TestViewPoint) ;

        class VvFinal : public TraitView<TvFinal,TestViewPoint>
        {};

        RegisterView(VvFinal,TvFinal,TestViewPoint) ;


        class ManualViewPoint : public ViewPoint
        {
        public:

          ManualViewPoint(Model* i_model)
          : ViewPoint(i_model)
          {}

        };

        class ManualView : public TraitView<Person,ManualViewPoint>
        {
        public:


          ManualView()
          : updated(false),
            init_number(0),
            value()
          {
            ++number_of_instance ;
          }

          ~ManualView()
          {
            --number_of_instance ;
          }

          /// Called after the view is created on a initialised viewpoint.
          void onInit()
          {
            value = getTrait()->getValue() ;
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
            value = getTrait()->getValue() ;
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

        int ManualView::number_of_instance = 0 ;
        int ManualView::number_of_operation = 0 ;

      }

      using namespace ModelView ;

      void TestModelView::testBuildOnEmptyModel()
      {
        InternalMessage("Kernel","Kernel::Test::testBuildOnEmptyModel entering") ;
        {
          std::auto_ptr<Model> model(new Model()) ;
          ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;
          /// init the viewpoint
          viewpoint->init() ;

          //// fill the model
          Object* person = model->createObject() ;
          person->addTrait(new Person()) ;
          Object* head = person->createObject() ;
          head->addTrait(new Head()) ;

          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;

          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ViewHead* headview = headtrait->getView<ViewHead>(viewpoint) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;

          InformationMessage("Kernel","sizeof(Object)=" + toString(sizeof(*person))) ;
        }
        InternalMessage("Kernel","Kernel::Test::testBuildOnEmptyModel leaving") ;
      }

      void TestModelView::testBuildOnNonEmptyModel()
      {
        InternalMessage("Kernel","Kernel::Test::testBuildOnNonEmptyModel entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        /// check the views are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 1) ;

        ViewHead* headview = head->getView<ViewHead>(viewpoint) ;
        CPPUNIT_ASSERT(headview) ;
        CPPUNIT_ASSERT(headview->init_number == 1) ;
        InternalMessage("Kernel","Kernel::Test::testBuildOnNonEmptyModel leaving") ;
      }

      void TestModelView::testDestroyRootObject()
      {
        InternalMessage("Kernel","Kernel::Test::testDestroyRootObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        model->destroyObject(person) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ViewHead::number_of_instance == 0) ;
        InternalMessage("Kernel","Kernel::Test::testDestroyRootObject leaving") ;
      }

      void TestModelView::testDestroySubObject()
      {
        InternalMessage("Kernel","Kernel::Test::testDestroySubObject entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        model->destroyObject(head) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_instance == 1) ;
        CPPUNIT_ASSERT(ViewHead::number_of_instance == 0) ;
        InternalMessage("Kernel","Kernel::Test::testDestroySubObject leaving") ;
      }

      void TestModelView::testDestroyTrait()
      {
        InternalMessage("Kernel","Kernel::Test::testDestroyTrait entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;

        person->destroyTrait(persontrait) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_instance == 0) ;
        CPPUNIT_ASSERT(ViewHead::number_of_instance == 1) ;
        InternalMessage("Kernel","Kernel::Test::testDestroyTrait leaving") ;
      }

      void TestModelView::testchangeParent()
      {
        InternalMessage("Kernel","Kernel::Test::testchangeParent entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        Object* person2 = model->createObject() ;
        person2->addTrait(new Person()) ;
        Object* head2 = person->createObject() ;
        head2->addTrait(new Head()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        InternalMessage("Kernel","Kernel::Test::testchangeParent viewpoint initialised") ;

        Head* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ViewHead* headview = headtrait->getView<ViewHead>(viewpoint) ;
        CPPUNIT_ASSERT(headview) ;

        InternalMessage("Kernel","Kernel::Test::testchangeParent #1") ;

        Head* headtrait2 = head2->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait2) ;
        ViewHead* headview2 = headtrait2->getView<ViewHead>(viewpoint) ;
        CPPUNIT_ASSERT(headview2) ;

        InternalMessage("Kernel","Kernel::Test::testchangeParent #2") ;

        CPPUNIT_ASSERT(headview->getValue()== 0);
        CPPUNIT_ASSERT(headview2->getValue()== 0) ;

        InternalMessage("Kernel","Kernel::Test::testchangeParent #3") ;

        headtrait->change(1) ;
        headtrait2->change(2) ;

        CPPUNIT_ASSERT(headview->getValue()== 1) ;
        CPPUNIT_ASSERT(headview2->getValue()== 2) ;

        InternalMessage("Kernel","Kernel::Test::testchangeParent swapping heads ...") ;

        /// swap heads
        head->changeParent(person2) ;
        head2->changeParent(person) ;

        CPPUNIT_ASSERT(headview2->getTrait()->getObject()->getParent() == person) ;
        InternalMessage("Kernel","Kernel::Test::testchangeParent leaving") ;
      }

      void TestModelView::testUpdate()
      {
        InternalMessage("Kernel","Kernel::Test::testUpdate entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        Person* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;

        CPPUNIT_ASSERT(personview->getValue()==0) ;

        persontrait->changeValue(10) ;

        CPPUNIT_ASSERT(personview->getValue()==10) ;
        InternalMessage("Kernel","Kernel::Test::testUpdate leaving") ;

      }

      void TestModelView::testViewAccess()
      {
        InternalMessage("Kernel","Kernel::Test::testViewAccess entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        person->addTrait(new Head()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;
        ViewPerson* personview = person->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;
        ViewHead*   headview   = personview->getView<ViewHead>() ;
        CPPUNIT_ASSERT(headview) ;
        InternalMessage("Kernel","Kernel::Test::testViewAccess leaving") ;

      }

      void TestModelView::testCreateTwice()
      {
        InternalMessage("Kernel","Kernel::Test::testCreateTwice entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        /// first create
        Object* person = model->createObject() ;
        model->destroyObject(person) ;

        /// recreate
        person = model->createObject() ;
        CPPUNIT_ASSERT(person) ;
        InternalMessage("Kernel","Kernel::Test::testCreateTwice leaving") ;
      }

      void TestModelView::testCloseViewPoint()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;
        head->addTrait(new Dummy()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;
        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;

          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ViewHead* headview = headtrait->getView<ViewHead>(viewpoint) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }
        /// close the viewpoint
        viewpoint->close() ;
        {
          /// check the views are closed
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 0) ;

          Trait* headtrait = head->getTrait<Head>() ;
          CPPUNIT_ASSERT(headtrait) ;
          ViewHead* headview = headtrait->getView<ViewHead>(viewpoint) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 0) ;
        }

      }

      void TestModelView::testNotPresentTrait()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

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
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        InternalMessage("Kernel","Kernel::Test::testDestroyModel destroying model...") ;

        model.reset(NULL) ;
      }

      void TestModelView::testForAll()
      {
        InternalMessage("Kernel","Kernel::Test::testForAll entering") ;
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

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        ViewHead::number_of_operation = 0 ;
        forAll<ViewHead>(viewpoint,&ViewHead::operation) ;
        CPPUNIT_ASSERT(ViewHead::number_of_operation == 2) ;

        ViewPerson::number_of_operation = 0 ;
        forAll<ViewPerson>(viewpoint,&ViewPerson::operation) ;
        CPPUNIT_ASSERT(ViewPerson::number_of_operation == 3) ;

      }

      void TestModelView::testMultiViewPoint()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// create a viewpoint
        ViewPoint* viewpoint1(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint1->init() ;

        /// create a viewpoint
        ViewPoint* viewpoint2(model->addViewPoint(new TestViewPoint2(model.get()))) ;
        /// init the viewpoint
        viewpoint2->init() ;

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint1) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;

          ViewHead* headview = head->getView<ViewHead>(viewpoint1) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;

          ViewHead2* headview = head->getView<ViewHead2>(viewpoint2) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }

      }

      void TestModelView::testMultiViewPointOfTheSameKind()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// create a viewpoint
        ViewPoint* viewpoint1(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint1->init() ;

        /// create a viewpoint
        ViewPoint* viewpoint2(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint2->init() ;

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint1) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;

          ViewHead* headview = head->getView<ViewHead>(viewpoint1) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }

        {
          /// check the views are initialised
          Trait* persontrait = person->getTrait<Person>() ;
          CPPUNIT_ASSERT(persontrait) ;
          ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint2) ;
          CPPUNIT_ASSERT(personview) ;
          CPPUNIT_ASSERT(personview->init_number == 1) ;

          ViewHead* headview = head->getView<ViewHead>(viewpoint2) ;
          CPPUNIT_ASSERT(headview) ;
          CPPUNIT_ASSERT(headview->init_number == 1) ;
        }

      }

      void TestModelView::testTraitInheritance()
      {
        InternalMessage("Kernel","Kernel::Test::testTraitInheritance entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* o1 = model->createObject() ;
        o1->addTrait(new T2()) ;
        o1->addTrait(new T3()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;
        InternalMessage("Kernel","Kernel::Test::testTraitInheritance viewpoint initialised") ;
        V1* v1 = o1->getView<V1>(viewpoint) ;
        InternalMessage("Kernel","Kernel::Test::testTraitInheritance looked up view") ;
        CPPUNIT_ASSERT(v1) ;
        InternalMessage("Kernel","Kernel::Test::testTraitInheritance leaving") ;


      }

      void TestModelView::testTraitVitrualInheritance()
      {
        InternalMessage("Kernel","Kernel::Test::testTraitVitrualInheritance entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* o1 = model->createObject() ;
        o1->addTrait(new TvFinal()) ;

        /// create a view
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;

        /// init the viewpoint
        viewpoint->init() ;
        InternalMessage("Kernel","Kernel::Test::testTraitVitrualInheritance viewpoint initialised") ;
        Vv1* v1 = o1->getView<Vv1>(viewpoint.get()) ;
        InternalMessage("Kernel","Kernel::Test::testTraitVitrualInheritance looked up view") ;
        CPPUNIT_ASSERT(v1) ;
        Vv2* v2 = o1->getView<Vv2>(viewpoint.get()) ;
        InternalMessage("Kernel","Kernel::Test::testTraitVitrualInheritance looked up view") ;
        CPPUNIT_ASSERT(v2) ;
        VvFinal* vFinal = o1->getView<VvFinal>(viewpoint.get()) ;
        InternalMessage("Kernel","Kernel::Test::testTraitVitrualInheritance looked up view") ;
        CPPUNIT_ASSERT(vFinal) ;

        InternalMessage("Kernel","Kernel::Test::testTraitVitrualInheritance leaving") ;

      }

      namespace ModelView
      {
        class Trait1 : public Trait
        {};

        class View1 : public TraitView<Trait1,TestViewPoint>
        {
        public:

          View1()
          : changed_parent_number(0)
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
        InternalMessage("Kernel","Kernel::Test::testchangeParentIsAtomic entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        View1::metaInit() ;

        Object* parent1 = model->createObject() ;
        Object* parent2 = model->createObject() ;
        Object* child = parent1->createObject() ;
        child->addTrait(new Trait1()) ;

        /// create a view
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        /// there should only be one update.
        CPPUNIT_ASSERT(View1::total_number_of_instance == 1) ;
        CPPUNIT_ASSERT(View1::total_number_of_init == 1) ;
        CPPUNIT_ASSERT(View1::total_number_of_close == 0) ;

        child->changeParent(parent2) ;

        CPPUNIT_ASSERT(View1::total_number_of_instance == 1) ;
        CPPUNIT_ASSERT(View1::total_number_of_close == 0) ;
        CPPUNIT_ASSERT(View1::total_number_of_init == 1) ;

      }

      void TestModelView::testManualView()
      {
        ManualView::number_of_instance = 0 ;

        // create a model
        std::auto_ptr<Model> model(new Model()) ;

        // fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;

        // create a viewpoint
        ViewPoint* viewpoint(model->addViewPoint(new ManualViewPoint(model.get()))) ;

        // manual add of a view
        model->addManualView(person->getTrait<Person>(),
                             new ManualView(),
                             viewpoint) ;

        /// init the viewpoint
        viewpoint->init() ;

        CPPUNIT_ASSERT(ManualView::number_of_instance==1) ;

        Person* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ManualView* personview = persontrait->getView<ManualView>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;

        // test update
        CPPUNIT_ASSERT_EQUAL(0,personview->getValue()) ;
        persontrait->changeValue(10) ;
        CPPUNIT_ASSERT_EQUAL(10,personview->getValue()) ;

        // test delete
        CPPUNIT_ASSERT(ManualView::number_of_instance==1) ;
        person->destroyTrait(persontrait) ;
        CPPUNIT_ASSERT(ManualView::number_of_instance==0) ;

        InternalMessage("Kernel","Kernel::Test::testManualView leaving") ;
      }

      void TestModelView::testManualViewOnInitViewPoint()
      {
        ManualView::number_of_instance = 0 ;

        // create a model
        std::auto_ptr<Model> model(new Model()) ;

        // fill the model
        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;

        // create a viewpoint
        ViewPoint* viewpoint(model->addViewPoint(new ManualViewPoint(model.get()))) ;

        /// init the viewpoint
        viewpoint->init() ;

        // manual add of a view
        model->addManualView(person->getTrait<Person>(),
                             new ManualView(),
                             viewpoint) ;


        Person* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ManualView* personview = persontrait->getView<ManualView>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;

        // test update
        CPPUNIT_ASSERT(personview->getValue()==0) ;
        persontrait->changeValue(10) ;
        CPPUNIT_ASSERT(personview->getValue()==10) ;

        // test delete
        CPPUNIT_ASSERT(ManualView::number_of_instance==1) ;
        person->destroyTrait(persontrait) ;
        CPPUNIT_ASSERT(ManualView::number_of_instance==0) ;

        InternalMessage("Kernel","Kernel::Test::testManualViewOnInitViewPoint leaving") ;
      }

      void TestModelView::initViewPointWithNullModel()
      {
        InternalMessage("Kernel","Kernel::Test::initViewPointWithNullModel entering") ;
        std::auto_ptr<Model> model ;
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint->init() ;
        InternalMessage("Kernel","Kernel::Test::initViewPointWithNullModel leaving") ;
      }

      void TestModelView::setModelOnInitialisedViewPointWithNullModel()
      {
        InternalMessage("Kernel","Kernel::Test::setModelOnInitialisedViewPointWithNullModel entering") ;
        std::auto_ptr<Model> model ;
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint->init() ;

        model.reset(new Model()) ;
        viewpoint->setModel(model.get()) ;

        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;
        Object* head = person->createObject() ;
        head->addTrait(new Head()) ;

        /// check the views are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 1) ;

        Trait* headtrait = head->getTrait<Head>() ;
        CPPUNIT_ASSERT(headtrait) ;
        ViewHead* headview = headtrait->getView<ViewHead>(viewpoint) ;
        CPPUNIT_ASSERT(headview) ;
        CPPUNIT_ASSERT(headview->init_number == 1) ;

        InternalMessage("Kernel","Kernel::Test::setModelOnInitialisedViewPointWithNullModel leaving") ;
      }

      void TestModelView::changeModelOnInitialisedViewPoint()
      {
        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedViewPoint entering") ;
        std::auto_ptr<Model> model(new Model()) ;
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint->init() ;

        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;

        /// check the views are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 1) ;

        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedViewPoint#1") ;
        std::auto_ptr<Model> model2(new Model()) ;
        viewpoint->setModel(model2.get()) ;

        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedViewPoint#2") ;

        /// check the views where closed
        personview = persontrait->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 0) ;
        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedViewPoint leaving") ;
      }

      void TestModelView::changeModelOnViewPoint()
      {
        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedViewPoint entering") ;
        std::auto_ptr<Model> model(new Model()) ;
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint->init() ;

        Object* person = model->createObject() ;
        person->addTrait(new Person()) ;

        /// check the views are initialised
        Trait* persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        ViewPerson* personview = persontrait->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 1) ;

        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedViewPoint#1") ;
        std::auto_ptr<Model> model2(new Model()) ;
        viewpoint->setModel(model2.get()) ;

        person = model2->createObject() ;
        person->addTrait(new Person()) ;

        persontrait = person->getTrait<Person>() ;
        CPPUNIT_ASSERT(persontrait) ;
        personview = persontrait->getView<ViewPerson>(viewpoint) ;
        CPPUNIT_ASSERT(personview) ;
        CPPUNIT_ASSERT(personview->init_number == 1) ;

        InternalMessage("Kernel","Kernel::Test::changeModelOnInitialisedViewPoint leaving") ;
      }

      void TestModelView::destroyObjectWithDeducedTraits()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModelView::destroyObjectWithDeducedTraits")) ;
        ViewPoint* viewpoint(model->addViewPoint(new TestViewPoint(model.get()))) ;
        /// init the viewpoint
        viewpoint->init() ;

        Object* object1 = model->createObject() ;
        Object* object2 = object1->createObject() ;

        object1->addTrait(new Person()) ;
        object1->addTrait(new Head()) ;
        object1->addTrait(new Dummy()) ;

        model->destroyObject(object1) ;
      }

      namespace
      {
        class TraitDestroyViewPoint : public Trait
        {};

        class ViewPointDestroyViewPoint : public ViewPoint
        {
        public:

          ViewPointDestroyViewPoint(Model* model)
          : ViewPoint(model)
          {}

          void setValue(int i)
          {
            m_value = i ;
          }

          void onClose()
          {
            ++m_number_of_on_close ;
          }

          static int m_number_of_on_close ;

        private:

          int m_value ;

        };

        int ViewPointDestroyViewPoint::m_number_of_on_close = 0 ;

        class ViewDestroyViewPoint : public TraitView<TraitDestroyViewPoint,ViewPointDestroyViewPoint>
        {
        public:

          /// Called just before the view is destroyed.
          void onClose()
          {
            getViewPoint()->setValue(1) ;
          }

        };

        RegisterView(ViewDestroyViewPoint,TraitDestroyViewPoint,ViewPointDestroyViewPoint) ;

      }

      void TestModelView::detroyViewPoint()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModelView::detroyViewPoint")) ;
        Object* object = model->createObject() ;
        object->addTrait(new TraitDestroyViewPoint()) ;
        {
          ViewPointDestroyViewPoint* viewpoint(new ViewPointDestroyViewPoint(model.get())) ;
          delete viewpoint ;
        }
      }

      void TestModelView::destroyModelAndCloseViewPoint()
      {

        const int old_value = ViewPointDestroyViewPoint::m_number_of_on_close ;

        std::auto_ptr<Model> model(new Model("TestModelView::destroyModelAndCloseViewPoint")) ;
        ViewPointDestroyViewPoint* viewpoint(new ViewPointDestroyViewPoint(model.get())) ;
        viewpoint->init() ;

        model.reset(NULL) ;

        // viewpoint whould have been closed
        CPPUNIT_ASSERT(ViewPointDestroyViewPoint::m_number_of_on_close == old_value+1) ;

      }

      namespace
      {
        class AccessTrait1 : public Trait
        {};

        class AccessTrait2 : public Trait
        {};

        class AccesViewPoint : public ViewPoint
        {
        public:

          AccesViewPoint(Model* model)
          : ViewPoint(model)
          {}

        };

        class AccessView1 : public TraitView<AccessTrait1,AccesViewPoint>
        {
        public:

          static bool m_accessed ;

        protected:

          virtual void onInit()
          {
            AccessTrait2* t2 = getTrait<AccessTrait2>() ;
            if (t2)
            {
              m_accessed = true ;
            }
          }

        };

        bool AccessView1::m_accessed = false ;

        RegisterView(AccessView1,AccessTrait1,AccesViewPoint) ;

      }

      void TestModelView::accessOtherTrait()
      {
        AccessView1::m_accessed = false ;

        std::auto_ptr<Model> model(new Model("TestModelView::accessOtherTrait")) ;
        ViewPoint* viewpoint(new AccesViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* object1 = model->createObject() ;
        object1->addTrait(new AccessTrait2()) ;
        object1->addTrait(new AccessTrait1()) ;

        CPPUNIT_ASSERT(AccessView1::m_accessed == true) ;
      }

      namespace
      {
        class Pos : public Trait
        {
        public:

          void touch()
          {
            notify() ;
          }
        };
        class AncestorPos : public DeducedTrait
        {};
        DeclareDeducedTrait(AncestorPos,HasAncestor(Pos)) ;
        class AncestorViewPoint : public ViewPoint
        {
        public:

          AncestorViewPoint(Model* model)
          : ViewPoint(model)
          {}

        };

        class ViewAncestor : public TraitView<AncestorPos,AncestorViewPoint>
        {
        public:

          static int m_updates ;

        protected:

          virtual void onUpdate()
          {
            ++m_updates ;
          }

        };

        int ViewAncestor::m_updates = 0 ;

        RegisterView(ViewAncestor,AncestorPos,AncestorViewPoint) ;

      }

      void TestModelView::updateAncestor()
      {
        std::auto_ptr<Model> model(new Model("TestModelView::updateAncestor")) ;
        ViewPoint* viewpoint(new AncestorViewPoint(model.get())) ;
        viewpoint->init() ;

        ViewAncestor::m_updates = 0 ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        root->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(child->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(child->getTrait<AncestorPos>()->getView<ViewAncestor>(viewpoint)) ;

        CPPUNIT_ASSERT_EQUAL(0,ViewAncestor::m_updates) ;

        root->getTrait<Pos>()->touch() ;

        CPPUNIT_ASSERT_EQUAL(1,ViewAncestor::m_updates) ;
      }

      namespace
      {
        class RecursivePos : public DeducedTrait
        {};
        DeclareDeducedTrait(RecursivePos,Or(HasAncestor(RecursivePos),HasTrait(Pos))) ;

        class ViewRecursive : public TraitView<RecursivePos,AncestorViewPoint>
        {
        public:

          static int m_updates ;

        protected:

          virtual void onUpdate()
          {
            ++m_updates ;
          }

        };

        int ViewRecursive::m_updates = 0 ;

        RegisterView(ViewRecursive,RecursivePos,AncestorViewPoint) ;

      }

      void TestModelView::updateRecursiveAncestor()
      {
        std::auto_ptr<Model> model(new Model("TestModelView::updateRecursiveAncestor")) ;
        ViewPoint* viewpoint(new AncestorViewPoint(model.get())) ;
        viewpoint->init() ;

        ViewRecursive::m_updates = 0 ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        root->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(root->getTrait<RecursivePos>()) ;
        CPPUNIT_ASSERT(child->getTrait<RecursivePos>()) ;

        CPPUNIT_ASSERT(child->getTrait<RecursivePos>()->getView<ViewRecursive>(viewpoint)) ;

        CPPUNIT_ASSERT_EQUAL(0,ViewRecursive::m_updates) ;

        root->getTrait<Pos>()->touch() ;

        CPPUNIT_ASSERT_EQUAL(2,ViewRecursive::m_updates) ;

      }

      void TestModelView::updateRecursiveAncestorLevel2()
      {
        std::auto_ptr<Model> model(new Model("TestModelView::updateRecursiveAncestor")) ;
        ViewPoint* viewpoint(new AncestorViewPoint(model.get())) ;
        viewpoint->init() ;

        ViewRecursive::m_updates = 0 ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        root->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(root->getTrait<RecursivePos>()) ;
        CPPUNIT_ASSERT(child->getTrait<RecursivePos>()) ;

        Object* grand_child = child->createObject() ;
        CPPUNIT_ASSERT(grand_child->getTrait<RecursivePos>()) ;

        CPPUNIT_ASSERT_EQUAL(0,ViewRecursive::m_updates) ;

        root->getTrait<Pos>()->touch() ;

        CPPUNIT_ASSERT_EQUAL(3,ViewRecursive::m_updates) ;
      }


      namespace
      {
        class ParentPos : public DeducedTrait
        {};
        DeclareDeducedTrait(ParentPos,HasParent(Pos)) ;

        class ViewParentPos : public TraitView<ParentPos,AncestorViewPoint>
        {
        public:

          static int m_updates ;

        protected:

          virtual void onUpdate()
          {
            ++m_updates ;
          }

        };

        int ViewParentPos::m_updates = 0 ;

        RegisterView(ViewParentPos,ParentPos,AncestorViewPoint) ;

      }

      void TestModelView::updateParentTrait()
      {
        std::auto_ptr<Model> model(new Model("TestModelView::updateParentTrait")) ;
        ViewPoint* viewpoint(new AncestorViewPoint(model.get())) ;
        viewpoint->init() ;

        ViewParentPos::m_updates = 0 ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        root->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(child->getTrait<ParentPos>()) ;
        CPPUNIT_ASSERT(child->getTrait<ParentPos>()->getView<ViewParentPos>(viewpoint)) ;

        CPPUNIT_ASSERT_EQUAL(0,ViewParentPos::m_updates) ;

        root->getTrait<Pos>()->touch() ;

        // root and child are updated
        CPPUNIT_ASSERT_EQUAL(2,ViewParentPos::m_updates) ;
      }

      void TestModelView::updateRecursiveParentTrait()
      {
        std::auto_ptr<Model> model(new Model("TestModelView::updateParentTrait")) ;
        ViewPoint* viewpoint(new AncestorViewPoint(model.get())) ;
        viewpoint->init() ;


        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;
        root->addTrait(new Pos()) ;
        child->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(child->getTrait<ParentPos>()) ;
        CPPUNIT_ASSERT(child->getTrait<ParentPos>()->getView<ViewParentPos>(viewpoint)) ;

        ViewParentPos::m_updates = 0 ;

        root->getTrait<Pos>()->touch() ;

        // only root should be updated
        CPPUNIT_ASSERT_EQUAL(1,ViewParentPos::m_updates) ;
      }

      namespace
      {
        class NotAnything : public DeducedTrait
        {};

        DeclareDeducedTrait(NotAnything,Not(HasTrait(Head))) ;

        class ViewNotAnything : public TraitView<NotAnything,TestViewPoint>
        {
        public:

          void onInit()
          {
            ++number_of_init ;
          }

          static int number_of_init ;
        };

        int ViewNotAnything::number_of_init = 0 ;

        RegisterView(ViewNotAnything,NotAnything,TestViewPoint) ;
      }

      void TestModelView::initNotTrait()
      {
        ViewNotAnything::number_of_init = 0 ;
        std::auto_ptr<Model> model(new Model("TestModelView::updateParentTrait")) ;
        ViewPoint* viewpoint(new TestViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* root = model->createObject() ;

        CPPUNIT_ASSERT_EQUAL(1,ViewNotAnything::number_of_init) ;
      }

    }
  }
}
